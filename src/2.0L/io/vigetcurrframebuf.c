#include "common.h"
#include <PR/viint.h>

extern __OSViContext *D_800A4100_main;

void *osViGetCurrentFramebuffer(void) {
    u32 intMask;
    void *frameBuffer;

    intMask = __osDisableInt();
    frameBuffer = D_800A4100_main->framep;
    __osRestoreInt(intMask);
    return frameBuffer;
}
