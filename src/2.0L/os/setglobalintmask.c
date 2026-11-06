#include "common.h"

extern u32 __osDisableInt(void);
extern void __osRestoreInt(u32);

extern u32 __OSGlobalIntMask;

void __osSetGlobalIntMask(OSHWIntr mask) {
    u32 int_disabled;

    int_disabled = __osDisableInt();
    __OSGlobalIntMask |= mask;
    __osRestoreInt(int_disabled);
}
