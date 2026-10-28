#include "common.h"
#include <PR/viint.h>

extern __OSViContext D_800A40A0_main[2]; // vi
extern __OSViContext *D_800A4100_main;   // __osViCurr
extern OSViMode D_800A4110_main;         // osViModeNtscLan1
extern OSViMode D_800A4160_main;         // osViModePalLan1
extern OSViMode D_800A41B0_main;         // osViModeMpalLan1

extern void osViSwapContext(void);

void __osViInit(void) {
    bzero(D_800A40A0_main, sizeof(D_800A40A0_main));
    D_800A4100_main = &D_800A40A0_main[0];
    __osViNext = &D_800A40A0_main[1];
    __osViNext->retraceCount = 1;
    D_800A4100_main->retraceCount = 1;
    __osViNext->framep = (void *)K0BASE;
    D_800A4100_main->framep = (void *)K0BASE;

    if (osTvType == OS_TV_TYPE_PAL) {
        __osViNext->modep = &D_800A4160_main;
    } else if (osTvType == OS_TV_TYPE_MPAL) {
        __osViNext->modep = &D_800A41B0_main;
    } else {
        __osViNext->modep = &D_800A4110_main;
    }

    __osViNext->state = VI_STATE_BLACK;
    __osViNext->control = __osViNext->modep->comRegs.ctrl;
    while (IO_READ(VI_CURRENT_REG) > 10) {
    }
    IO_WRITE(VI_CONTROL_REG, 0);
    osViSwapContext();
}
