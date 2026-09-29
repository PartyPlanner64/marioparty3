#include "common.h"
#include <PR/viint.h>

void osViSetYScale(f32 scale) {
    u32 intMask;
    __OSViContext *ctx;

    intMask = __osDisableInt();
    ctx = __osViNext;
    ctx->y.factor = scale;
    ctx->state |= VI_STATE_YSCALE_UPDATED;
    __osRestoreInt(intMask);
}
