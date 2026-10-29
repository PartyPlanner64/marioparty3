#include "common.h"
#include "PR/osint.h"
#include "PR/R4300.h"

#define THPROF_IDMAX 64

extern void D_80080930_main(void);
extern __OSThreadprofile_s D_800D55E0_main[THPROF_IDMAX];

void osCreateThread(OSThread *t, OSId id, void (*entry)(void *), void *arg, void *sp, OSPri p) {
    register u32 saveMask;
    OSIntMask mask;

    t->id = id;
    t->priority = p;
    t->next = NULL;
    t->queue = NULL;
    t->context.pc = (u32)entry;
    t->context.a0 = (s64)(s32)arg;
    t->context.sp = (s64)(s32)sp - 16;
    t->context.ra = (s64)(s32)D_80080930_main;
    mask = OS_IM_ALL;
    t->context.sr = SR_IMASK | SR_EXL | SR_IE;
    t->context.rcp = (mask & RCP_IMASK) >> RCP_IMASKSHIFT;
    t->context.fpcsr = (u32)(FPCSR_FS | FPCSR_EV);
    t->fp = 0;
    t->state = OS_STATE_STOPPED;
    t->flags = 0;
    if (id < THPROF_IDMAX) {
        t->thprof = &D_800D55E0_main[id];
    } else {
        t->thprof = &D_800D55E0_main[THPROF_IDMAX - 1];
    }
    saveMask = __osDisableInt();
    t->tlnext = __osActiveQueue;
    __osActiveQueue = t;
    __osRestoreInt(saveMask);
}
