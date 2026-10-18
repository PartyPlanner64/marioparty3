#include "common.h"

extern u32 __osDisableInt(void);
extern void __osRestoreInt(u32);
extern void __osEnqueueAndYield(OSThread **);

extern OSThread *__osRunningThread;
extern OSThread *__osRunQueue;

void osYieldThread(void) {
    register u32 int_disabled;

    int_disabled = __osDisableInt();
    __osRunningThread->state = OS_STATE_RUNNABLE;
    __osEnqueueAndYield(&__osRunQueue);
    __osRestoreInt(int_disabled);
}
