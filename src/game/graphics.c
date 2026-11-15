#include "ultra64.h"
#include "types.h"
#include "macros.h"
#include "humath.h"
#include "game/profiler.h"
#include "game/graphics.h"

s32 HuDbgStatus = 0xFF88FF88;

static u64 swapChainStack[0x1800 / sizeof(u64)];
static u8 D_800AE000_main[0x3800]; // unreferenced
static swapChainTaskQueue swapChainTask;
static OSMesgQueue gSwapChainMesgQueue;
static OSMesg gSwapChainInitMesg[0x40];
static OSMesgQueue gMesgQueue;
static OSMesg gMesgQueueInitMesg[8];
static void **frameBufferPool;
static u16 frameBufferCount;
static u16 frameBufferSegmentID;
static u32 HuGfxRetraceNum; // message count?

extern OSThread swapChainThread;

extern graphicsMessage gMesgRingBuffer[0x40];
extern s16 ringBufferIndex;

extern u64 *gThreadOutStackSize;
extern u64 *gThreadYieldStack;
extern u64 *gThreadOutStack;
extern u64 *gThread3Stack;

extern Gfx gTaskDataPointers[];

extern s32 HuGfxFrameCnt;
extern void *nextFrameBuffer;
extern void *currFrameBuffer;

extern s32 *gUCodeAddresses;

extern s16 gSwapChainMesgTotal;

extern u32 scRetraceCnt;         // Unk
extern OSMesgQueue scGraphicsTaskQueue; // Another system's message queue

/* Initialize Graphics SwapChain */

void HuGfxInit(void **arg1, s32 arg2, s32 arg3, u64 **arg4, s32 *arg5) {
    HuGfxFBPoolSet(arg1, arg2, arg3);
    HuGfxStackSet(arg4);
    HuGfxUcodeSet(arg5);
    HuGfxModeSet(0);

    swapChainTask.completionQueue = &gMesgQueue;
    swapChainTask.task.t.type = 1;
    swapChainTask.task.t.flags = 2;
    swapChainTask.task.t.ucode_boot = (u64 *)rspbootTextStart;
    swapChainTask.task.t.ucode_boot_size = (u32)rspbootTextEnd - (u32)rspbootTextStart;
    swapChainTask.task.t.ucode_size = 0x1000;
    swapChainTask.task.t.ucode_data_size = 0x800;
    swapChainTask.task.t.dram_stack_size = 0x400;
    swapChainTask.task.t.data_ptr = (u64 *)&gTaskDataPointers;
    swapChainTask.task.t.data_size = 2;
    swapChainTask.task.t.yield_data_size = 0xC00;

    gSwapChainMesgTotal = 0;
    ringBufferIndex = 0;
    HuGfxFrameCnt = 0;
    nextFrameBuffer = 0;
    currFrameBuffer = 0;
    osCreateMesgQueue(&gSwapChainMesgQueue, gSwapChainInitMesg, 0x40);
    osCreateMesgQueue(&gMesgQueue, gMesgQueueInitMesg, 8);
    osCreateThread(&swapChainThread, 0x10, &HuGfxThreadMain, NULL, &swapChainStack[ARRAY_COUNT(swapChainStack)], 0x64);
    osStartThread(&swapChainThread);
}

/* Retrieve available frame buffer (triple buffering?) */
void *HuGfxFBNextGet(void) {
    void *current;
    void *next;
    void *fBuffer;
    s16 i;

    current = osViGetCurrentFramebuffer();
    next = osViGetNextFramebuffer();

    for (i = 0; i < frameBufferCount; i++) {
        fBuffer = frameBufferPool[i];
        if (fBuffer != current) {
            if (fBuffer != next) {
                return fBuffer;
            }
        }
    }
    return NULL;
}

/* Swap Chain Loop */
void HuGfxThreadMain(void *arg0) {
    unkSchedStruct sp10;
    OSMesgQueue mesgQueue;
    unkGraphicsMessage2 sp38;
    unkSchedStruct sp58;
    OSMesgQueue mesgQueue2;
    unkGraphicsMessage2 sp68;
    graphicsMessage *recvdMesg;
    void *pAvailableFrameBuffer;
    s32 var_s4;
    u32 i;

    swapChainTaskQueue *pSwapChain;
    OSTask *pTask;

    recvdMesg = NULL;
    pSwapChain = &swapChainTask;
    pTask = &swapChainTask.task;
    var_s4 = 0;

    osCreateMesgQueue(&mesgQueue, (OSMesg *)&sp38, 8);
    AddSchedulerClient(&sp10, &mesgQueue, 1);
    osCreateMesgQueue(&mesgQueue2, (OSMesg *)&sp68, 8);
    AddSchedulerClient(&sp58, &mesgQueue2, 2);

    while (TRUE) {
        do {
        recvmesg:
            osRecvMesg(&mesgQueue, NULL, 1);
            if (osRecvMesg(&mesgQueue2, NULL, 0) == 0) {
                while (TRUE)
                    ;
            } // Infinite loop?
            if ((scRetraceCnt - var_s4) < HuGfxRetraceNum) {
                goto recvmesg;
            }

            var_s4 = scRetraceCnt;
            HuProfRspReset();
            pAvailableFrameBuffer = HuGfxFBNextGet();
        } while (pAvailableFrameBuffer == NULL);

        currFrameBuffer = nextFrameBuffer;
        nextFrameBuffer = pAvailableFrameBuffer;

        /* Need redundant do for regalloc? */
        do {
            do {

                osRecvMesg(&gSwapChainMesgQueue, (OSMesg)&recvdMesg, 1);
                if (osRecvMesg(&mesgQueue2, NULL, 0) == 0) {
                    while (TRUE)
                        ;
                } else {
                    u32 intMask;
                    Gfx *dl = gTaskDataPointers;
                    gSPSegment(dl++, frameBufferSegmentID, pAvailableFrameBuffer);
                    gSPBranchList(dl++, recvdMesg->unk00);
                    pSwapChain->completionMsg = (OSMesg)recvdMesg->unk08;
                    pTask->t.dram_stack = gThread3Stack;
                    pTask->t.output_buff = gThreadOutStack;
                    pTask->t.output_buff_size = gThreadOutStackSize;
                    pTask->t.yield_data_ptr = gThreadYieldStack;
                    pTask->t.ucode = (u64 *)*((recvdMesg->unk04 * 2) + gUCodeAddresses);            // offset     (data pairs?)
                    pTask->t.ucode_data = (u64 *)*(((recvdMesg->unk04 * 2) | 1) + gUCodeAddresses); // offset + 1

                    osSendMesg(&scGraphicsTaskQueue, (OSMesg)pSwapChain, 1);
                    osRecvMesg(&gMesgQueue, NULL, 1);

                    intMask = osSetIntMask(1);
                    gSwapChainMesgTotal -= 1;
                    osSetIntMask(intMask);

                    if (recvdMesg->unk0C != NULL) {
                        osSendMesg(recvdMesg->unk0C, (OSMesg)recvdMesg->unk10, 1);
                    }
                }

            } while (!(recvdMesg->unk08 & 1));
        } while (FALSE);

        for (i = 1; i < HuGfxRetraceNum; i++) {
            osRecvMesg(&mesgQueue, NULL, 1);
        }

        osViSwapBuffer(pAvailableFrameBuffer);
        if (HuGfxFrameCnt == 0) {
            if (osRecvMesg(&mesgQueue2, NULL, 0) == 0) {
                while (TRUE)
                    ;
            }
            osViSetYScale(1.0f);
            osViBlack(0);
        }
        HuGfxFrameCnt++;
        HuProfDummy(); // empty function
    }
}

/* Retrieve graphics OSMesg from ring buffer */
graphicsMessage *HuGfxMesgAlloc(void) {
    if (ringBufferIndex >= 0x40) {
        ringBufferIndex = 0;
    }
    return &gMesgRingBuffer[ringBufferIndex++];
}

/* Send graphics OSMesg */
u8 HuGfxTaskSend(Gfx *arg0, u16 arg1, s32 arg2, OSMesgQueue *arg3, s32 arg4) {
    graphicsMessage *mesg;
    u32 intMask;

    if (gSwapChainMesgTotal >= 0x40) {
        return FALSE;
    }

    intMask = osSetIntMask(1);
    gSwapChainMesgTotal++;
    osSetIntMask(intMask);
    mesg = HuGfxMesgAlloc();

    /* Initialize message. */
    mesg->unk00 = arg0;
    mesg->unk04 = arg1;
    mesg->unk08 = arg2;
    mesg->unk0C = arg3;
    mesg->unk10 = arg4;

    osSendMesg(&gSwapChainMesgQueue, mesg, 1);
    return TRUE;
}

/* Init graphics frame buffer pool */
void HuGfxFBPoolSet(void **pool, u16 size, u16 segment) {
    frameBufferPool = pool;
    frameBufferCount = size;
    frameBufferSegmentID = segment;
}

/* Reset frame buffer pool size. (Switch between double and triple buffering) */
void HuGfxFBCountSet(u16 size) {
    frameBufferCount = size;
}

/* Initialize gThreadStacks */
void HuGfxStackSet(u64 **threadStacks) {
    gThread3Stack = *threadStacks++;
    gThreadOutStack = *threadStacks++;
    gThreadOutStackSize = *threadStacks++;
    gThreadYieldStack = *threadStacks;
}

/* Set pointer to swapchain task's ucode addresses */
void HuGfxUcodeSet(s32 *uCodeAdresses) {
    gUCodeAddresses = uCodeAdresses;
}

/* Swap chain state set? */
void HuGfxModeSet(u32 arg0) {
    HuGfxRetraceNum = arg0;
}
