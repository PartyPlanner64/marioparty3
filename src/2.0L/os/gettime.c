#include "common.h"

extern u32 D_800CB898_main;
extern OSTime D_800CE2B8_main;

extern u32 __osDisableInt(void);
extern void __osRestoreInt(u32);

OSTime osGetTime(void) {
    u32 tmptime;
    u32 elapseCount;
    OSTime currentCount;
    register u32 saveMask;

    saveMask = __osDisableInt();
    tmptime = osGetCount();
    elapseCount = tmptime - D_800CB898_main;
    currentCount = D_800CE2B8_main;
    __osRestoreInt(saveMask);
    return currentCount + elapseCount;
}
