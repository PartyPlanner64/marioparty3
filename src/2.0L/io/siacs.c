#include "common.h"

extern OSMesgQueue __osSiAccessQueue;
extern OSMesg D_800C3990_main[1];
extern s32 D_800A2DA0_main;

void func_8007C720_main(void) {
    D_800A2DA0_main = 1;
    osCreateMesgQueue(&__osSiAccessQueue, D_800C3990_main, 1);
    osSendMesg(&__osSiAccessQueue, NULL, OS_MESG_NOBLOCK);
}

INCLUDE_ASM("asm/nonmatchings/2.0L/io/siacs", __osSiGetAccess);

void __osSiRelAccess(void) {
    osSendMesg(&__osSiAccessQueue, NULL, OS_MESG_NOBLOCK);
}
