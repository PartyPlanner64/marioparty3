#include "common.h"
#include "PR/os_internal.h"

extern u32 __OSGlobalIntMask;

void __osResetGlobalIntMask(OSHWIntr mask) {
    u32 int_disabled;

    int_disabled = __osDisableInt();
    __OSGlobalIntMask &= (~mask | 0x401);
    __osRestoreInt(int_disabled);
}
