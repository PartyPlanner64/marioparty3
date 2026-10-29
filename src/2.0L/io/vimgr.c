#include "common.h"
#include "PR/viint.h"
#include "PR/osint.h"

extern OSDevMgr __osViDevMgr;
extern u32 __additional_scanline;
extern OSThread viThread;
extern u8 viThreadStack[OS_VIM_STACKSIZE]; /* 0x800C3B60, not yet split from viThread */
extern OSMesgQueue viEventQueue;
extern OSMesg viEventBuf[5];
extern OSIoMesg viRetraceMsg;
extern OSIoMesg viCounterMsg;
extern u16 D_800C39A0_main; /* retrace */

extern void osViSwapContext(void);

void viMgrMain(void *arg);

// Matches once viThreadStack gets its own symbol; the original references it
// separately from viEventQueue, which immediately follows it in bss.
#ifdef NON_MATCHING
void osCreateViManager(OSPri pri) {
    u32 savedMask;
    OSPri oldPri;
    OSPri myPri;

    if (__osViDevMgr.active == 0) {
        __osTimerServicesInit();
        __additional_scanline = 0;
        osCreateMesgQueue(&viEventQueue, viEventBuf, 5);
        viRetraceMsg.hdr.type = OS_MESG_TYPE_VRETRACE;
        viRetraceMsg.hdr.pri = OS_MESG_PRI_NORMAL;
        viRetraceMsg.hdr.retQueue = NULL;
        viCounterMsg.hdr.type = OS_MESG_TYPE_COUNTER;
        viCounterMsg.hdr.pri = OS_MESG_PRI_NORMAL;
        viCounterMsg.hdr.retQueue = NULL;
        osSetEventMesg(OS_EVENT_VI, &viEventQueue, &viRetraceMsg);
        osSetEventMesg(OS_EVENT_COUNTER, &viEventQueue, &viCounterMsg);
        oldPri = -1;
        myPri = osGetThreadPri(NULL);
        if (myPri < pri) {
            oldPri = myPri;
            osSetThreadPri(NULL, pri);
        }
        savedMask = __osDisableInt();
        __osViDevMgr.active = 1;
        __osViDevMgr.thread = &viThread;
        __osViDevMgr.cmdQueue = &viEventQueue;
        __osViDevMgr.evtQueue = &viEventQueue;
        __osViDevMgr.acsQueue = NULL;
        __osViDevMgr.dma = NULL;
        __osViDevMgr.edma = NULL;
        osCreateThread(&viThread, 0, viMgrMain, &__osViDevMgr, &viThreadStack[OS_VIM_STACKSIZE], pri);
        __osViInit();
        osStartThread(&viThread);
        __osRestoreInt(savedMask);
        if (oldPri != -1) {
            osSetThreadPri(NULL, oldPri);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/2.0L/io/vimgr", osCreateViManager);
#endif

void viMgrMain(void *arg) {
    __OSViContext *vc;
    OSDevMgr *dm;
    OSIoMesg *mb = NULL;
    s32 first = 0;
    u32 count;

    vc = __osViGetCurrentContext();
    D_800C39A0_main = vc->retraceCount;
    if (D_800C39A0_main == 0) {
        D_800C39A0_main = 1;
    }
    dm = (OSDevMgr *)arg;
    while (TRUE) {
        osRecvMesg(dm->evtQueue, (OSMesg *)&mb, OS_MESG_BLOCK);
        switch (mb->hdr.type) {
            case OS_MESG_TYPE_VRETRACE:
                osViSwapContext();
                D_800C39A0_main--;
                if (D_800C39A0_main == 0) {
                    vc = __osViGetCurrentContext();
                    if (vc->msgq != NULL) {
                        osSendMesg(vc->msgq, vc->msg, OS_MESG_NOBLOCK);
                    }
                    D_800C39A0_main = vc->retraceCount;
                }
                __osViIntrCount++;
                if (first) {
                    count = osGetCount();
                    __osCurrentTime = count;
                    first = 0;
                }
                count = __osBaseCounter;
                __osBaseCounter = osGetCount();
                count = __osBaseCounter - count;
                __osCurrentTime = __osCurrentTime + count;
                break;
            case OS_MESG_TYPE_COUNTER:
                __osTimerInterrupt();
                break;
        }
    }
}
