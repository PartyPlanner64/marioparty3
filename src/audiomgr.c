#include "common.h"
#include "graphics.h"
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

extern unkSchedStruct D_800A97C0_main; // scheduler client
extern u64 D_800A97D0_main[0x400];     // audio thread stack
extern OSMesgQueue *D_800AB7D0_main;   // scheduler command queue
extern AMAudioMgr D_800AB7D8_main;     // __am
extern AMDMAState D_800ABA70_main;     // dmaState
extern u32 D_800ABA78_main;            // audFrameCt
extern u32 D_800ABA7C_main;            // nextDMA
extern s32 D_800ABA80_main;            // DMA buffer length
extern s32 D_800ABA84_main;            // frames before a DMA buffer is freed
extern s32 D_800ABA88_main;            // curAcmdList
extern s32 D_800ABA8C_main;            // minFrameSize
extern s32 D_800ABA90_main;            // maxFrameSize
extern u32 D_800ABA94_main;            // frameSize
extern s32 D_800ABA98_main;
extern OSIoMesg D_800ABAA0_main[NUM_DMA_MESSAGES];
extern OSMesgQueue D_800ABDA0_main; // audDMAMessageQ
extern OSMesg D_800ABDB8_main[NUM_DMA_MESSAGES];
extern OSPiHandle *D_800ABE38_main;
extern s32 D_800ABE3C_main; // use the short frame next
extern OSMesgQueue D_800CC3A0_main;

extern u8 n_aspMain_code[];
extern u8 n_aspMain_data[];

void *func_800010B8_main(s32 size);
void func_800023B4_main(void);
void func_80002528_main(void);
void func_80006E30_main(void);
void func_80006FC4_main(void);
void RemoveSchedulerClient(unkSchedStruct *client);
void __amMain(void *arg);
s32 __amHandleFrameMsg(AudioInfo *info, AudioInfo *lastInfo);
void __amHandleDoneMsg(AudioInfo *info);
s32 __amDMA(s32 addr, s32 len, void *state);
ALDMAproc __amDmaNew(AMDMAState **state);
void __clearAudioDMA(void);
void func_80008CC0_main(s32 arg0, s32 remove);
void func_80008D28_main(swapChainTaskQueue *task, AudioMsg *msg, Acmd *cmdp);

s32 amCreateAudioMgr(str800D5298 *cfg, ALHeap *heap) {
    ALSynConfig c;
    f32 fsize;
    AMDMABuffer *dmaBuffs;
    s32 i;

    c.outputRate = osAiSetFrequency(cfg->unk1C);
    D_800ABA98_main = cfg->unk48;
    fsize = (f32)cfg->unk40 * (f32)c.outputRate / (f32)cfg->unk44;
    D_800ABA94_main = (s32)fsize;
    if (D_800ABA94_main < fsize) {
        D_800ABA94_main++;
    }
    D_800ABA94_main = (D_800ABA94_main / EXTRA_SAMPLES + 1) * EXTRA_SAMPLES;
    D_800ABA8C_main = D_800ABA94_main - EXTRA_SAMPLES;
    D_800ABA90_main = D_800ABA94_main;
    D_800ABE3C_main = 1;
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
    n_alInit(&D_800AB7D8_main.g, &c);

    D_800ABA88_main = 0;
    D_800ABA7C_main = 0;
    D_800ABA78_main = 0;
    D_800ABA80_main = cfg->unk38;
    D_800ABA84_main = cfg->unk3C;

    dmaBuffs = func_800010B8_main(cfg->unk34 * sizeof(AMDMABuffer));
    if (dmaBuffs == NULL) {
        return 1;
    }
    dmaBuffs[cfg->unk34 - 1].node.next = NULL;
    dmaBuffs[0].node.next = NULL;
    dmaBuffs[0].node.prev = NULL;
    for (i = 0; i < cfg->unk34 - 1; i++) {
        alLink(&dmaBuffs[i + 1].node, &dmaBuffs[i].node);
        if ((dmaBuffs[i].ptr = func_800010B8_main(D_800ABA80_main)) == NULL) {
            return 1;
        }
    }
    if ((dmaBuffs[i].ptr = func_800010B8_main(D_800ABA80_main)) == NULL) {
        return 1;
    }
    D_800ABA70_main.firstUsed = NULL;
    D_800ABA70_main.firstFree = dmaBuffs;
    D_800ABE38_main = cfg->unk68;

    for (i = 0; i < NUM_ACMD_LISTS; i++) {
        if ((D_800AB7D8_main.ACMDList[i] = func_800010B8_main(cfg->unk30 * sizeof(Acmd))) == NULL) {
            return 2;
        }
    }
    for (i = 0; i < NUM_OUTPUT_BUFFERS; i++) {
        if ((D_800AB7D8_main.audioInfo[i] = func_800010B8_main(sizeof(AudioInfo))) == NULL) {
            return 3;
        }
        D_800AB7D8_main.audioInfo[i]->msg.type = 0;
        D_800AB7D8_main.audioInfo[i]->msg.info = D_800AB7D8_main.audioInfo[i];
        D_800AB7D8_main.audioInfo[i]->data = func_800010B8_main(D_800ABA90_main * 4);
        if (D_800AB7D8_main.audioInfo[i]->data == NULL) {
            return 4;
        }
    }
    return 0;
}

void func_80008678_main(str800D5298 *cfg) {
    osCreateMesgQueue(&D_800AB7D8_main.audioReplyMsgQ, D_800AB7D8_main.audioReplyMsgBuf, MAX_MESGS);
    osCreateMesgQueue(&D_800ABDA0_main, D_800ABDB8_main, NUM_DMA_MESSAGES);
    func_80008CC0_main(cfg->unk64, 0);
    osCreateThread(&D_800AB7D8_main.thread, cfg->unk60, __amMain, NULL,
                   D_800A97D0_main + ARRAY_COUNT(D_800A97D0_main), cfg->unk5C);
    osStartThread(&D_800AB7D8_main.thread);
}

void func_8000870C_main(str800D5298 *cfg) {
    osDestroyThread(&D_800AB7D8_main.thread);
    n_alClose(&D_800AB7D8_main.g);
    func_80008CC0_main(cfg->unk64, 1);
}

void __amMain(void *arg) {
    s32 done = FALSE;
    AudioInfo *lastInfo = NULL;
    OSMesg msg;
    AudioMsg *doneMsg;

    while (!done) {
        osRecvMesg(&D_800AB7D8_main.audioFrameMsgQ, &msg, OS_MESG_BLOCK);
        switch ((u32)msg) {
            case 1:
                if (__amHandleFrameMsg(D_800AB7D8_main.audioInfo[D_800ABA78_main % NUM_OUTPUT_BUFFERS],
                                       lastInfo)) {
                    osRecvMesg(&D_800AB7D8_main.audioReplyMsgQ, (OSMesg *)&doneMsg, OS_MESG_BLOCK);
                    __amHandleDoneMsg(doneMsg->info);
                    lastInfo = doneMsg->info;
                    func_800023B4_main();
                    func_80006E30_main();
                }
                break;
            case 2:
                func_80002528_main();
                done = TRUE;
                func_80006FC4_main();
                break;
            case 10:
                done = TRUE;
                break;
        }
    }
    n_alClose(&D_800AB7D8_main.g);
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
    if (D_800ABA98_main + EXTRA_SAMPLES < samplesLeft && D_800ABE3C_main) {
        info->frameSamples = D_800ABA8C_main;
        D_800ABE3C_main = 0;
    } else {
        info->frameSamples = D_800ABA94_main;
        D_800ABE3C_main = 1;
    }
    cmdp = n_alAudioFrame(D_800AB7D8_main.ACMDList[D_800ABA88_main], &cmdLen, audioPtr, info->frameSamples);
    if (cmdLen == 0) {
        return 0;
    }
    func_80008D28_main(&info->task, &info->msg, cmdp);
    osSendMesg(D_800AB7D0_main, &info->task, OS_MESG_BLOCK);
    D_800ABA88_main ^= 1;
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
    dmaPtr = D_800ABA70_main.firstUsed;
    addrEnd = addr + len;

    while (dmaPtr != NULL) {
        buffEnd = dmaPtr->startAddr + D_800ABA80_main;
        if (dmaPtr->startAddr > addr) {
            break;
        } else if (addrEnd <= buffEnd) {
            dmaPtr->lastFrame = D_800ABA78_main;
            foundBuffer = dmaPtr->ptr + addr - dmaPtr->startAddr;
            return osVirtualToPhysical(foundBuffer);
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = (AMDMABuffer *)dmaPtr->node.next;
    }

    dmaPtr = D_800ABA70_main.firstFree;
    if (dmaPtr == NULL) {
        return osVirtualToPhysical(D_800ABA70_main.firstUsed);
    }

    D_800ABA70_main.firstFree = (AMDMABuffer *)dmaPtr->node.next;
    alUnlink(&dmaPtr->node);

    if (lastDmaPtr != NULL) {
        alLink(&dmaPtr->node, &lastDmaPtr->node);
    } else if (D_800ABA70_main.firstUsed != NULL) {
        lastDmaPtr = D_800ABA70_main.firstUsed;
        D_800ABA70_main.firstUsed = dmaPtr;
        dmaPtr->node.next = &lastDmaPtr->node;
        dmaPtr->node.prev = NULL;
        lastDmaPtr->node.prev = &dmaPtr->node;
    } else {
        D_800ABA70_main.firstUsed = dmaPtr;
        dmaPtr->node.next = NULL;
        dmaPtr->node.prev = NULL;
    }

    foundBuffer = dmaPtr->ptr;
    delta = addr & 1;
    addr -= delta;
    dmaPtr->startAddr = addr;
    dmaPtr->lastFrame = D_800ABA78_main;

    ioMesg = &D_800ABAA0_main[D_800ABA7C_main++];
    ioMesg->hdr.pri = OS_MESG_PRI_NORMAL;
    ioMesg->hdr.retQueue = &D_800ABDA0_main;
    ioMesg->dramAddr = foundBuffer;
    ioMesg->devAddr = addr;
    ioMesg->size = D_800ABA80_main;
    osEPiStartDma(D_800ABE38_main, ioMesg, OS_READ);

    return osVirtualToPhysical(foundBuffer) + delta;
}

ALDMAproc __amDmaNew(AMDMAState **state) {
    *state = &D_800ABA70_main;
    return __amDMA;
}

void __clearAudioDMA(void) {
    u32 i;
    OSIoMesg *iomsg;
    AMDMABuffer *dmaPtr;
    AMDMABuffer *nextPtr;

    for (i = 0; i < D_800ABA7C_main; i++) {
        osRecvMesg(&D_800ABDA0_main, (OSMesg *)&iomsg, OS_MESG_NOBLOCK);
    }

    dmaPtr = D_800ABA70_main.firstUsed;
    while (dmaPtr != NULL) {
        nextPtr = (AMDMABuffer *)dmaPtr->node.next;
        if (dmaPtr->lastFrame + D_800ABA84_main < D_800ABA78_main) {
            if (D_800ABA70_main.firstUsed == dmaPtr) {
                D_800ABA70_main.firstUsed = nextPtr;
            }
            alUnlink(&dmaPtr->node);
            if (D_800ABA70_main.firstFree != NULL) {
                alLink(&dmaPtr->node, &D_800ABA70_main.firstFree->node);
            } else {
                D_800ABA70_main.firstFree = dmaPtr;
                dmaPtr->node.next = NULL;
                dmaPtr->node.prev = NULL;
            }
        }
        dmaPtr = nextPtr;
    }
    D_800ABA7C_main = 0;
    D_800ABA78_main++;
}

void func_80008CC0_main(s32 arg0, s32 remove) {
    if (remove) {
        RemoveSchedulerClient(&D_800A97C0_main);
    } else {
        osCreateMesgQueue(&D_800AB7D8_main.audioFrameMsgQ, D_800AB7D8_main.audioFrameMsgBuf, MAX_MESGS);
        D_800AB7D0_main = &D_800CC3A0_main;
        AddSchedulerClient(&D_800A97C0_main, &D_800AB7D8_main.audioFrameMsgQ, 3);
    }
}

void func_80008D28_main(swapChainTaskQueue *task, AudioMsg *msg, Acmd *cmdp) {
    task->completionQueue = &D_800AB7D8_main.audioReplyMsgQ;
    task->completionMsg = msg;
    task->task.t.data_ptr = (u64 *)D_800AB7D8_main.ACMDList[D_800ABA88_main];
    task->task.t.data_size = (cmdp - D_800AB7D8_main.ACMDList[D_800ABA88_main]) * sizeof(Acmd);
    task->task.t.type = M_AUDTASK;
    task->task.t.ucode_boot = (u64 *)rspbootTextStart;
    task->task.t.ucode_boot_size = (u32)gspF3DEX2_fifoTextStart - (u32)rspbootTextStart;
    task->task.t.flags = 0;
    task->task.t.ucode = (u64 *)n_aspMain_code;
    task->task.t.ucode_data = (u64 *)n_aspMain_data;
    task->task.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    task->task.t.dram_stack = NULL;
    task->task.t.dram_stack_size = 0;
    task->task.t.output_buff = NULL;
    task->task.t.output_buff_size = NULL;
    task->task.t.yield_data_ptr = NULL;
    task->task.t.yield_data_size = 0;
}
