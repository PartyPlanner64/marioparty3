#include "common.h"
#include <PR/viint.h>

void *osViGetNextFramebuffer(void) {
    u32 intMask;
    void *frameBuffer;

    intMask = __osDisableInt();
    frameBuffer = __osViNext->framep;
    __osRestoreInt(intMask);
    return frameBuffer;
}
