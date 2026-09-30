#include "common.h"
#include <PR/viint.h>

void osViSetMode(OSViMode *mode) {
    u32 intMask;
    __OSViContext *ctx;

    intMask = __osDisableInt();
    ctx = __osViNext;
    ctx->modep = mode;
    ctx->state = VI_STATE_01;
    ctx->control = ctx->modep->comRegs.ctrl;
    __osRestoreInt(intMask);
}
