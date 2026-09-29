#include "common.h"

extern u32 __osDisableInt(void);
extern void __osRestoreInt(u32);
extern void __osEnqueueAndYield(OSThread **);

extern OSThread *__osRunningThread;
extern OSThread *D_800A2DB8_main;

void osYieldThread(void) {
    register u32 int_disabled;

    int_disabled = __osDisableInt();
    __osRunningThread->state = OS_STATE_RUNNABLE;
    __osEnqueueAndYield(&D_800A2DB8_main);
    __osRestoreInt(int_disabled);
}
