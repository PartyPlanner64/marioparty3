#include "common.h"
#include <PR/viint.h>

void osViSwapBuffer(void *vaddr) {
    u32 intMask;
    __OSViContext *ctx;

    intMask = __osDisableInt();
    ctx = __osViNext;
    ctx->state |= VI_STATE_10;
    ctx->framep = vaddr;
    __osRestoreInt(intMask);
}
