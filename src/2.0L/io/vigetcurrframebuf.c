#include "common.h"
#include <PR/viint.h>

void *osViGetCurrentFramebuffer(void) {
    u32 intMask;
    void *frameBuffer;

    intMask = __osDisableInt();
    frameBuffer = __osViCurr->framep;
    __osRestoreInt(intMask);
    return frameBuffer;
}
