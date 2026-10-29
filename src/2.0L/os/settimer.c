#include "common.h"
#include "PR/osint.h"

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
    if (__osTimerList->next != __osTimerList) {
        spC = __osTimerList->next;
        count = osGetCount();
        tim = count - __osTimerCounter;
        if (tim < spC->value) {
            spC->value -= tim;
        } else {
            spC->value = 1;
        }
    }
    __osInsertTimer(t);
    __osSetTimerIntr(__osTimerList->next->value);
    __osRestoreInt(saveMask);
    return 0;
}
