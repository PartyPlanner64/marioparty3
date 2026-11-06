#include "common.h"

u32 __osThprofFlag = 0;
void (*__osThprofFunc)(OSThread *) = NULL;

extern u32 __osThprofCount;
extern u32 __osThprofLastTimer;

void osThreadProfileCallback(OSThread *t) {
    u32 now, diff;
    __OSThreadprofile_s *p;

    now = osGetCount();
    diff = now - __osThprofLastTimer;
    p = t->thprof;
    __osThprofLastTimer = now;
    __osThprofCount++;
    p->time += diff;
    p->count++;
}
