#include "common.h"

extern u32 __osDisableInt(void);
extern void __osRestoreInt(u32);

extern u32 D_800A3FB0_main;

void func_80080A10_main(OSHWIntr mask) {
    u32 int_disabled;

    int_disabled = __osDisableInt();
    D_800A3FB0_main &= (~mask | 0x401);
    __osRestoreInt(int_disabled);
}
