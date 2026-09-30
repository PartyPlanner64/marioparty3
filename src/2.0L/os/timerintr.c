#include "common.h"

extern OSTimer *D_800A2DD0_main;
extern OSTime D_800CE2B8_main;
extern u32 D_800CB898_main;
extern u32 D_800CD1D8_main;

void __osTimerServicesInit(void) {
    OSTimer *timer = D_800A2DD0_main;

    D_800CE2B8_main = 0;
    D_800CB898_main = 0;
    D_800CD1D8_main = 0;

    timer->value = 0;
    timer->interval = timer->value;
    timer->prev = timer;
    timer->next = timer->prev;
    timer->mq = NULL;
    timer->msg = 0;
}

INCLUDE_ASM("asm/nonmatchings/2.0L/os/timerintr", __osTimerInterrupt);

INCLUDE_ASM("asm/nonmatchings/2.0L/os/timerintr", __osSetTimerIntr);

INCLUDE_ASM("asm/nonmatchings/2.0L/os/timerintr", __osInsertTimer);
