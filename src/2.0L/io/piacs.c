#include "common.h"

extern OSMesgQueue D_800D0550_main;
extern OSMesg D_800C3940_main[1];
extern s32 D_800A2A70_main;

void __osPiCrateAccessQueue(void) {
    OSMesgQueue *queue = &D_800D0550_main;

    D_800A2A70_main = 1;
    osCreateMesgQueue(queue, D_800C3940_main, 1);
    osSendMesg(queue, NULL, OS_MESG_NOBLOCK);
}

void __osPiGetAccess(void) {
    OSMesg msg;

    if (D_800A2A70_main == 0) {
        D_800A2A70_main = 1;
        osCreateMesgQueue(&D_800D0550_main, D_800C3940_main, 1);
        osSendMesg(&D_800D0550_main, NULL, OS_MESG_NOBLOCK);
    }
    osRecvMesg(&D_800D0550_main, &msg, OS_MESG_BLOCK);
}

void __osPiRelAccess(void) {
    osSendMesg(&D_800D0550_main, NULL, OS_MESG_NOBLOCK);
}
