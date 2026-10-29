#include "common.h"

extern u32 __osDisableInt(void);
extern void __osRestoreInt(u32);

extern u32 D_800A3FB0_main;

void __osSetGlobalIntMask(OSHWIntr mask) {
    u32 int_disabled;

    int_disabled = __osDisableInt();
    D_800A3FB0_main |= mask;
    __osRestoreInt(int_disabled);
}
