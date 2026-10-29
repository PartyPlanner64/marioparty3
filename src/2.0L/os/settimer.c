#include "common.h"
#include "PR/osint.h"

extern OSTimer *D_800A2DD0_main;
extern u32 D_800D2000_main;

int osSetTimer(OSTimer *t, OSTime value, OSTime interval, OSMesgQueue *mq, OSMesg msg) {
    OSTime tim;
    OSTimer *spC;
    u32 count;
    u32 saveMask;

    t->next = NULL;
    t->prev = NULL;
    t->value = value;
    t->interval = interval;
    if (value == 0) {
        t->value = interval;
    }
    t->mq = mq;
    t->msg = msg;

    saveMask = __osDisableInt();
    if (D_800A2DD0_main->next != D_800A2DD0_main) {
        spC = D_800A2DD0_main->next;
        count = osGetCount();
        tim = count - D_800D2000_main;
        if (tim < spC->value) {
            spC->value -= tim;
        } else {
            spC->value = 1;
        }
    }
    __osInsertTimer(t);
    __osSetTimerIntr(D_800A2DD0_main->next->value);
    __osRestoreInt(saveMask);
    return 0;
}
