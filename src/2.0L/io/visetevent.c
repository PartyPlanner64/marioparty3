#include "common.h"
#include <PR/viint.h>

void osViSetEvent(OSMesgQueue *mq, OSMesg msg, u32 retraceCount) {
    u32 intMask;
    __OSViContext *ctx;

    intMask = __osDisableInt();
    ctx = __osViNext;
    ctx->msgq = mq;
    ctx->msg = msg;
    ctx->retraceCount = retraceCount;
    __osRestoreInt(intMask);
}
