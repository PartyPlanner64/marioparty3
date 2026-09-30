#include "common.h"

extern OSMesgQueue D_800D0550_main;
extern OSMesg D_800C3940_main[1];
extern s32 D_800A2A70_main;

void __osPiCrateAccessQueue(void) {
    D_800A2A70_main = 1;
    osCreateMesgQueue(&D_800D0550_main, D_800C3940_main, 1);
    osSendMesg(&D_800D0550_main, NULL, OS_MESG_NOBLOCK);
}

INCLUDE_ASM("asm/nonmatchings/2.0L/io/piacs", __osPiGetAccess);

void __osPiRelAccess(void) {
    osSendMesg(&D_800D0550_main, NULL, OS_MESG_NOBLOCK);
}
