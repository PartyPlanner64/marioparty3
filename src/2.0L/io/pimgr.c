#include "common.h"
#include "piint.h"
#include "PR/rdb.h"

#define OS_RAMROM_STACKSIZE 1024

extern OSDevMgr __osPiDevMgr;
extern s32 __osEPiRawStartDma(OSPiHandle *pihandle, s32 direction, u32 devAddr, void *dramAddr, u32 size);
extern void __osDevMgrMain(void *args);
void __osPiCrateAccessQueue(void);

extern u32 D_800A2A70_main;                       /* __osPiAccessQueueEnabled */
extern OSMesgQueue D_800D0550_main;               /* __osPiAccessQueue */
extern OSThread D_800C2180_main;                  /* piThread */
extern u8 piThreadStack[OS_PIM_STACKSIZE];        /* 0x800C2330, not yet split from D_800C2180_main */
extern OSThread D_800C3330_main;                  /* ramromThread */
extern u8 ramromThreadStack[OS_RAMROM_STACKSIZE]; /* 0x800C34E0, not yet split from D_800C3330_main */
extern OSMesgQueue D_800C38E0_main;               /* getRamromQ */
extern OSMesg D_800C38F8_main[1];                 /* getRamromBuf */
extern OSMesgQueue D_800C3900_main;               /* freeRamromQ */
extern OSMesg D_800C3918_main[1];                 /* freeRamromBuf */
extern OSMesgQueue D_800C3920_main;               /* piEventQueue */
extern OSMesg D_800C3938_main[1];                 /* piEventBuf */

static void ramromMain(void *arg);

// Matches once the thread stacks get their own symbols (piThreadStack and
// ramromThreadStack); the original references them separately from the
// threads that follow them in bss.
#ifdef NON_MATCHING
void osCreatePiManager(OSPri pri, OSMesgQueue *cmdQ, OSMesg *cmdBuf, s32 cmdMsgCnt) {
    u32 savedMask;
    OSPri oldPri;
    OSPri myPri;

    if (!__osPiDevMgr.active) {
        osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
        osCreateMesgQueue(&D_800C3920_main, D_800C3938_main, 1);
        if (!D_800A2A70_main) {
            __osPiCrateAccessQueue();
        }
        osSetEventMesg(OS_EVENT_PI, &D_800C3920_main, (OSMesg)0x22222222);
        oldPri = -1;
        myPri = osGetThreadPri(NULL);
        if (myPri < pri) {
            oldPri = myPri;
            osSetThreadPri(NULL, pri);
        }
        savedMask = __osDisableInt();
        __osPiDevMgr.active = 1;
        __osPiDevMgr.thread = &D_800C2180_main;
        __osPiDevMgr.cmdQueue = cmdQ;
        __osPiDevMgr.evtQueue = &D_800C3920_main;
        __osPiDevMgr.acsQueue = &D_800D0550_main;
        __osPiDevMgr.dma = osPiRawStartDma;
        __osPiDevMgr.edma = __osEPiRawStartDma;
        osCreateThread(&D_800C2180_main, 0, __osDevMgrMain, &__osPiDevMgr,
                       &piThreadStack[OS_PIM_STACKSIZE], pri);
        osStartThread(&D_800C2180_main);
        osCreateThread(&D_800C3330_main, 0, ramromMain, NULL, &ramromThreadStack[OS_RAMROM_STACKSIZE],
                       pri - 1);
        osStartThread(&D_800C3330_main);
        __osRestoreInt(savedMask);
        if (oldPri != -1) {
            osSetThreadPri(NULL, oldPri);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/2.0L/io/pimgr", osCreatePiManager);
#endif

static void ramromMain(void *arg) {
    u8 dummy[1];
    u32 sent;

    osCreateMesgQueue(&D_800C38E0_main, D_800C38F8_main, 1);
    osCreateMesgQueue(&D_800C3900_main, D_800C3918_main, 1);
    osSetEventMesg(OS_EVENT_RDB_REQ_RAMROM, &D_800C38E0_main, NULL);
    osSetEventMesg(OS_EVENT_RDB_FREE_RAMROM, &D_800C3900_main, NULL);
    while (TRUE) {
        osRecvMesg(&D_800C38E0_main, NULL, OS_MESG_BLOCK);
        __osPiGetAccess();
        sent = 0;
        while (sent == 0) {
            sent += __osRdbSend(dummy, 1, RDB_TYPE_GtoH_RAMROM);
        }
        osRecvMesg(&D_800C3900_main, NULL, OS_MESG_BLOCK);
        __osPiRelAccess();
    }
}
