#include "common.h"

extern OSMesgQueue __osSiAccessQueue;
extern OSMesg D_800C3990_main[1];
extern s32 D_800A2DA0_main;

void func_8007C720_main(void) {
    OSMesgQueue *queue = &__osSiAccessQueue;

    D_800A2DA0_main = 1;
    osCreateMesgQueue(queue, D_800C3990_main, 1);
    osSendMesg(queue, NULL, OS_MESG_NOBLOCK);
}

void __osSiGetAccess(void) {
    OSMesg msg;

    if (D_800A2DA0_main == 0) {
        D_800A2DA0_main = 1;
        osCreateMesgQueue(&__osSiAccessQueue, D_800C3990_main, 1);
        osSendMesg(&__osSiAccessQueue, NULL, OS_MESG_NOBLOCK);
    }
    osRecvMesg(&__osSiAccessQueue, &msg, OS_MESG_BLOCK);
}

void __osSiRelAccess(void) {
    osSendMesg(&__osSiAccessQueue, NULL, OS_MESG_NOBLOCK);
}
