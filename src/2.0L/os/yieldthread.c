#include "common.h"
#include "PR/osint.h"

extern OSThread *__osRunningThread;
extern OSThread *__osRunQueue;

void osYieldThread(void) {
    register u32 int_disabled;

    int_disabled = __osDisableInt();
    __osRunningThread->state = OS_STATE_RUNNABLE;
    __osEnqueueAndYield(&__osRunQueue);
    __osRestoreInt(int_disabled);
}
