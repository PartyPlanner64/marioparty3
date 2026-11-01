#include "common.h"
#include "piint.h"
#include "PR/rdb.h"

#define OS_RAMROM_STACKSIZE 1024

extern s32 __osEPiRawStartDma(OSPiHandle *pihandle, s32 direction, u32 devAddr, void *dramAddr, u32 size);

static OSThread piThread;
static u8 piThreadStack[OS_PIM_STACKSIZE];
static OSThread ramromThread;
static u8 ramromThreadStack[OS_RAMROM_STACKSIZE];
static OSMesgQueue getRamromQ;
static OSMesg getRamromBuf[1];
static OSMesgQueue freeRamromQ;
static OSMesg freeRamromBuf[1];
static OSMesgQueue piEventQueue;
static OSMesg piEventBuf[1];

static void ramromMain(void *arg);

void osCreatePiManager(OSPri pri, OSMesgQueue *cmdQ, OSMesg *cmdBuf, s32 cmdMsgCnt) {
    u32 savedMask;
    OSPri oldPri;
    OSPri myPri;

    if (!__osPiDevMgr.active) {
        osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
        osCreateMesgQueue(&piEventQueue, piEventBuf, 1);
        if (!__osPiAccessQueueEnabled) {
            __osPiCreateAccessQueue();
        }
        osSetEventMesg(OS_EVENT_PI, &piEventQueue, (OSMesg)0x22222222);
        oldPri = -1;
        myPri = osGetThreadPri(NULL);
        if (myPri < pri) {
            oldPri = myPri;
            osSetThreadPri(NULL, pri);
        }
        savedMask = __osDisableInt();
        __osPiDevMgr.active = 1;
        __osPiDevMgr.thread = &piThread;
        __osPiDevMgr.cmdQueue = cmdQ;
        __osPiDevMgr.evtQueue = &piEventQueue;
        __osPiDevMgr.acsQueue = &__osPiAccessQueue;
        __osPiDevMgr.dma = osPiRawStartDma;
        __osPiDevMgr.edma = __osEPiRawStartDma;
        osCreateThread(&piThread, 0, __osDevMgrMain, &__osPiDevMgr,
                       &piThreadStack[OS_PIM_STACKSIZE], pri);
        osStartThread(&piThread);
        osCreateThread(&ramromThread, 0, ramromMain, NULL, &ramromThreadStack[OS_RAMROM_STACKSIZE],
                       pri - 1);
        osStartThread(&ramromThread);
        __osRestoreInt(savedMask);
        if (oldPri != -1) {
            osSetThreadPri(NULL, oldPri);
        }
    }
}

static void ramromMain(void *arg) {
    u8 dummy[1];
    u32 sent;

    osCreateMesgQueue(&getRamromQ, getRamromBuf, 1);
    osCreateMesgQueue(&freeRamromQ, freeRamromBuf, 1);
    osSetEventMesg(OS_EVENT_RDB_REQ_RAMROM, &getRamromQ, NULL);
    osSetEventMesg(OS_EVENT_RDB_FREE_RAMROM, &freeRamromQ, NULL);
    while (TRUE) {
        osRecvMesg(&getRamromQ, NULL, OS_MESG_BLOCK);
        __osPiGetAccess();
        sent = 0;
        while (sent == 0) {
            sent += __osRdbSend(dummy, 1, RDB_TYPE_GtoH_RAMROM);
        }
        osRecvMesg(&freeRamromQ, NULL, OS_MESG_BLOCK);
        __osPiRelAccess();
    }
}
