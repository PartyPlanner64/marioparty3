#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/audiomgr.h"
#include "game/msm.h"
#include "macros.h"
#include "game/graphics.h"
#include "PR/n_libaudio.h"
#include "PR/ucode.h"

/*
 * Audio manager, derived from the N64 SDK demo audiomgr.c sample and adapted
 * by Hudson. It is not part of the libultra archive; it is compiled with the
 * game's flags as part of the game code. Builds an audio command list each
 * retrace and hands it to the Hudson scheduler.
 */

#define NUM_ACMD_LISTS 2
#define NUM_OUTPUT_BUFFERS 3
#define MAX_MESGS 8
#define NUM_DMA_MESSAGES 32
#define EXTRA_SAMPLES 184

typedef struct {
    /* 0x00 */ s16 type;
    /* 0x04 */ void *info;
} AudioMsg; // size: 0x8

typedef struct {
    /* 0x00 */ s16 *data;
    /* 0x04 */ s16 frameSamples;
    /* 0x08 */ swapChainTaskQueue task;
    /* 0x50 */ AudioMsg msg;
} AudioInfo; // size: 0x58

typedef struct {
    /* 0x000 */ Acmd *ACMDList[NUM_ACMD_LISTS];
    /* 0x008 */ AudioInfo *audioInfo[NUM_OUTPUT_BUFFERS];
    /* 0x018 */ OSThread thread;
    /* 0x1C8 */ OSMesgQueue audioFrameMsgQ;
    /* 0x1E0 */ OSMesg audioFrameMsgBuf[MAX_MESGS];
    /* 0x200 */ OSMesgQueue audioReplyMsgQ;
    /* 0x218 */ OSMesg audioReplyMsgBuf[MAX_MESGS];
    /* 0x238 */ N_ALGlobals g;
} AMAudioMgr; // size: 0x298

typedef struct {
    /* 0x00 */ ALLink node;
    /* 0x08 */ u32 startAddr;
    /* 0x0C */ u32 lastFrame;
    /* 0x10 */ char *ptr;
} AMDMABuffer; // size: 0x14

typedef struct {
    /* 0x00 */ AMDMABuffer *firstUsed;
    /* 0x04 */ AMDMABuffer *firstFree;
} AMDMAState;

static unkSchedStruct audSchedClient; // scheduler client
static u64 audMgrStack[0x400];     // audio thread stack
static OSMesgQueue *audTaskQueue;   // scheduler command queue
static AMAudioMgr __am;
static AMDMAState dmaState;
static u32 audFrameCt;
static u32 nextDMA;
static s32 audDmaBufSize;            // DMA buffer length
static s32 audDmaBufLife;            // frames before a DMA buffer is freed
static s32 curAcmdList;
static s32 minFrameSize;
static s32 maxFrameSize;
static u32 frameSize;
static s32 audSampleMin;
static OSIoMesg audDMAIOMesgBuf[NUM_DMA_MESSAGES];
static OSMesgQueue audDMAMessageQ;
static OSMesg audDMAMessageBuf[NUM_DMA_MESSAGES];
static OSPiHandle *audPiHandle;
static s32 audFrameAdjF; // use the short frame next
extern OSMesgQueue scAudioTaskQueue;

s32 __amHandleFrameMsg(AudioInfo *info, AudioInfo *lastInfo);
void __amHandleDoneMsg(AudioInfo *info);
ALDMAproc __amDmaNew(AMDMAState **state);
void __amTaskSetup(swapChainTaskQueue *task, AudioMsg *msg, Acmd *cmdp);

s32 amCreateAudioMgr(str800D5298 *cfg, ALHeap *heap) {
    ALSynConfig c;
    f32 fsize;
    AMDMABuffer *dmaBuffs;
    s32 i;

    c.outputRate = osAiSetFrequency(cfg->unk1C);
    audSampleMin = cfg->unk48;
    fsize = (f32)cfg->unk40 * (f32)c.outputRate / (f32)cfg->unk44;
    frameSize = (s32)fsize;
    if (frameSize < fsize) {
        frameSize++;
    }
    frameSize = (frameSize / EXTRA_SAMPLES + 1) * EXTRA_SAMPLES;
    minFrameSize = frameSize - EXTRA_SAMPLES;
    maxFrameSize = frameSize;
    audFrameAdjF = 1;
    if (cfg->unk2C != NULL) {
        c.fxType = AL_FX_CUSTOM;
        c.params = (s32 *)cfg->unk2C;
    } else {
        c.fxType = AL_FX_NONE;
        c.params = NULL;
    }
    c.maxVVoices = c.maxPVoices = cfg->unk20;
    c.maxUpdates = cfg->unk24;
    c.dmaproc = __amDmaNew;
    c.heap = heap;
    c.maxFXbusses = 0;
    n_alInit(&__am.g, &c);

    curAcmdList = 0;
    nextDMA = 0;
    audFrameCt = 0;
    audDmaBufSize = cfg->unk38;
    audDmaBufLife = cfg->unk3C;

    dmaBuffs = msmMemAlloc(cfg->unk34 * sizeof(AMDMABuffer));
    if (dmaBuffs == NULL) {
        return 1;
    }
    dmaBuffs[cfg->unk34 - 1].node.next = NULL;
    dmaBuffs[0].node.next = NULL;
    dmaBuffs[0].node.prev = NULL;
    for (i = 0; i < cfg->unk34 - 1; i++) {
        alLink(&dmaBuffs[i + 1].node, &dmaBuffs[i].node);
        if ((dmaBuffs[i].ptr = msmMemAlloc(audDmaBufSize)) == NULL) {
            return 1;
        }
    }
    if ((dmaBuffs[i].ptr = msmMemAlloc(audDmaBufSize)) == NULL) {
        return 1;
    }
    dmaState.firstUsed = NULL;
    dmaState.firstFree = dmaBuffs;
    audPiHandle = cfg->unk68;

    for (i = 0; i < NUM_ACMD_LISTS; i++) {
        if ((__am.ACMDList[i] = msmMemAlloc(cfg->unk30 * sizeof(Acmd))) == NULL) {
            return 2;
        }
    }
    for (i = 0; i < NUM_OUTPUT_BUFFERS; i++) {
        if ((__am.audioInfo[i] = msmMemAlloc(sizeof(AudioInfo))) == NULL) {
            return 3;
        }
        __am.audioInfo[i]->msg.type = 0;
        __am.audioInfo[i]->msg.info = __am.audioInfo[i];
        __am.audioInfo[i]->data = msmMemAlloc(maxFrameSize * 4);
        if (__am.audioInfo[i]->data == NULL) {
            return 4;
        }
    }
    return 0;
}

void amStart(str800D5298 *cfg) {
    osCreateMesgQueue(&__am.audioReplyMsgQ, __am.audioReplyMsgBuf, MAX_MESGS);
    osCreateMesgQueue(&audDMAMessageQ, audDMAMessageBuf, NUM_DMA_MESSAGES);
    amSchedClientSet(cfg->unk64, 0);
    osCreateThread(&__am.thread, cfg->unk60, __amMain, NULL,
                   audMgrStack + ARRAY_COUNT(audMgrStack), cfg->unk5C);
    osStartThread(&__am.thread);
}

void amDestroyAudioMgr(str800D5298 *cfg) {
    osDestroyThread(&__am.thread);
    n_alClose(&__am.g);
    amSchedClientSet(cfg->unk64, 1);
}

void __amMain(void *arg) {
    s32 done = FALSE;
    AudioInfo *lastInfo = NULL;
    OSMesg msg;
    AudioMsg *doneMsg;

    while (!done) {
        osRecvMesg(&__am.audioFrameMsgQ, &msg, OS_MESG_BLOCK);
        switch ((u32)msg) {
            case 1:
                if (__amHandleFrameMsg(__am.audioInfo[audFrameCt % NUM_OUTPUT_BUFFERS],
                                       lastInfo)) {
                    osRecvMesg(&__am.audioReplyMsgQ, (OSMesg *)&doneMsg, OS_MESG_BLOCK);
                    __amHandleDoneMsg(doneMsg->info);
                    lastInfo = doneMsg->info;
                    msmMusPeriodicProc();
                    msmSePeriodicProc();
                }
                break;
            case 2:
                msmMusDeleteAll();
                done = TRUE;
                msmSeStopAllSounds();
                break;
            case 10:
                done = TRUE;
                break;
        }
    }
    n_alClose(&__am.g);
}

s32 __amHandleFrameMsg(AudioInfo *info, AudioInfo *lastInfo) {
    s16 *audioPtr;
    Acmd *cmdp;
    s32 cmdLen;
    s32 samplesLeft;

    samplesLeft = osAiGetLength() >> 2;
    __clearAudioDMA();
    audioPtr = (s16 *)osVirtualToPhysical(info->data);
    if (lastInfo != NULL) {
        osAiSetNextBuffer(lastInfo->data, lastInfo->frameSamples << 2);
    }
    if (audSampleMin + EXTRA_SAMPLES < samplesLeft && audFrameAdjF) {
        info->frameSamples = minFrameSize;
        audFrameAdjF = 0;
    } else {
        info->frameSamples = frameSize;
        audFrameAdjF = 1;
    }
    cmdp = n_alAudioFrame(__am.ACMDList[curAcmdList], &cmdLen, audioPtr, info->frameSamples);
    if (cmdLen == 0) {
        return 0;
    }
    __amTaskSetup(&info->task, &info->msg, cmdp);
    osSendMesg(audTaskQueue, &info->task, OS_MESG_BLOCK);
    curAcmdList ^= 1;
    return 1;
}

void __amHandleDoneMsg(AudioInfo *info) {
}

s32 __amDMA(s32 addr, s32 len, void *state) {
    char *foundBuffer;
    s32 delta;
    s32 addrEnd;
    s32 buffEnd;
    AMDMABuffer *dmaPtr;
    AMDMABuffer *lastDmaPtr;
    OSIoMesg *ioMesg;

    lastDmaPtr = NULL;
    dmaPtr = dmaState.firstUsed;
    addrEnd = addr + len;

    while (dmaPtr != NULL) {
        buffEnd = dmaPtr->startAddr + audDmaBufSize;
        if (dmaPtr->startAddr > addr) {
            break;
        } else if (addrEnd <= buffEnd) {
            dmaPtr->lastFrame = audFrameCt;
            foundBuffer = dmaPtr->ptr + addr - dmaPtr->startAddr;
            return osVirtualToPhysical(foundBuffer);
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = (AMDMABuffer *)dmaPtr->node.next;
    }

    dmaPtr = dmaState.firstFree;
    if (dmaPtr == NULL) {
        return osVirtualToPhysical(dmaState.firstUsed);
    }

    dmaState.firstFree = (AMDMABuffer *)dmaPtr->node.next;
    alUnlink(&dmaPtr->node);

    if (lastDmaPtr != NULL) {
        alLink(&dmaPtr->node, &lastDmaPtr->node);
    } else if (dmaState.firstUsed != NULL) {
        lastDmaPtr = dmaState.firstUsed;
        dmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = &lastDmaPtr->node;
        dmaPtr->node.prev = NULL;
        lastDmaPtr->node.prev = &dmaPtr->node;
    } else {
        dmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = NULL;
        dmaPtr->node.prev = NULL;
    }

    foundBuffer = dmaPtr->ptr;
    delta = addr & 1;
    addr -= delta;
    dmaPtr->startAddr = addr;
    dmaPtr->lastFrame = audFrameCt;

    ioMesg = &audDMAIOMesgBuf[nextDMA++];
    ioMesg->hdr.pri = OS_MESG_PRI_NORMAL;
    ioMesg->hdr.retQueue = &audDMAMessageQ;
    ioMesg->dramAddr = foundBuffer;
    ioMesg->devAddr = addr;
    ioMesg->size = audDmaBufSize;
    osEPiStartDma(audPiHandle, ioMesg, OS_READ);

    return osVirtualToPhysical(foundBuffer) + delta;
}

ALDMAproc __amDmaNew(AMDMAState **state) {
    *state = &dmaState;
    return __amDMA;
}

void __clearAudioDMA(void) {
    u32 i;
    OSIoMesg *iomsg;
    AMDMABuffer *dmaPtr;
    AMDMABuffer *nextPtr;

    for (i = 0; i < nextDMA; i++) {
        osRecvMesg(&audDMAMessageQ, (OSMesg *)&iomsg, OS_MESG_NOBLOCK);
    }

    dmaPtr = dmaState.firstUsed;
    while (dmaPtr != NULL) {
        nextPtr = (AMDMABuffer *)dmaPtr->node.next;
        if (dmaPtr->lastFrame + audDmaBufLife < audFrameCt) {
            if (dmaState.firstUsed == dmaPtr) {
                dmaState.firstUsed = nextPtr;
            }
            alUnlink(&dmaPtr->node);
            if (dmaState.firstFree != NULL) {
                alLink(&dmaPtr->node, &dmaState.firstFree->node);
            } else {
                dmaState.firstFree = dmaPtr;
                dmaPtr->node.next = NULL;
                dmaPtr->node.prev = NULL;
            }
        }
        dmaPtr = nextPtr;
    }
    nextDMA = 0;
    audFrameCt++;
}

void amSchedClientSet(s32 arg0, s32 remove) {
    if (remove) {
        RemoveSchedulerClient(&audSchedClient);
    } else {
        osCreateMesgQueue(&__am.audioFrameMsgQ, __am.audioFrameMsgBuf, MAX_MESGS);
        audTaskQueue = &scAudioTaskQueue;
        AddSchedulerClient(&audSchedClient, &__am.audioFrameMsgQ, 3);
    }
}

void __amTaskSetup(swapChainTaskQueue *task, AudioMsg *msg, Acmd *cmdp) {
    task->completionQueue = &__am.audioReplyMsgQ;
    task->completionMsg = msg;
    task->task.t.data_ptr = (u64 *)__am.ACMDList[curAcmdList];
    task->task.t.data_size = (cmdp - __am.ACMDList[curAcmdList]) * sizeof(Acmd);
    task->task.t.type = M_AUDTASK;
    task->task.t.ucode_boot = (u64 *)rspbootTextStart;
    task->task.t.ucode_boot_size = (u32)gspF3DEX2_fifoTextStart - (u32)rspbootTextStart;
    task->task.t.flags = 0;
    task->task.t.ucode = (u64 *)n_aspMainTextStart;
    task->task.t.ucode_data = (u64 *)n_aspMainDataStart;
    task->task.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    task->task.t.dram_stack = NULL;
    task->task.t.dram_stack_size = 0;
    task->task.t.output_buff = NULL;
    task->task.t.output_buff_size = NULL;
    task->task.t.yield_data_ptr = NULL;
    task->task.t.yield_data_size = 0;
}
