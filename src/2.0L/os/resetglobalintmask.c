#include "common.h"

extern u32 __osDisableInt(void);
extern void __osRestoreInt(u32);

extern u32 __OSGlobalIntMask;

void __osResetGlobalIntMask(OSHWIntr mask) {
    u32 int_disabled;

    int_disabled = __osDisableInt();
    __OSGlobalIntMask &= (~mask | 0x401);
    __osRestoreInt(int_disabled);
}
