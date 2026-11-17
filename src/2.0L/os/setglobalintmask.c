#include "common.h"
#include "PR/os_internal.h"

extern u32 __OSGlobalIntMask;

void __osSetGlobalIntMask(OSHWIntr mask) {
    u32 int_disabled;

    int_disabled = __osDisableInt();
    __OSGlobalIntMask |= mask;
    __osRestoreInt(int_disabled);
}
