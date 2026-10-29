#include "common.h"
#include "PR/osint.h"

extern OSMesgQueue __osProfTimerQ;
extern OSProf *__osProfileList;
extern OSProf *__osProfileListEnd;
extern u32 __osProfileOverflowBin;

void __osTimerServicesInit(void) {
    OSTimer *timer = __osTimerList;

    __osCurrentTime = 0;
    __osBaseCounter = 0;
    __osViIntrCount = 0;

    timer->value = 0;
    timer->interval = timer->value;
    timer->prev = timer;
    timer->next = timer->prev;
    timer->mq = NULL;
    timer->msg = 0;
}

void __osTimerInterrupt(void) {
    OSTimer *t;
    u32 count;
    u32 elapsed_cycles;
    u32 pc;
    s32 offset;
    OSProf *prof;

    if (__osTimerList->next == __osTimerList) {
        return;
    }
    while (TRUE) {
        t = __osTimerList->next;
        if (t == __osTimerList) {
            __osSetCompare(0);
            __osTimerCounter = 0;
            break;
        }
        count = osGetCount();
        elapsed_cycles = count - __osTimerCounter;
        __osTimerCounter = count;
        if (elapsed_cycles < t->value) {
            t->value -= elapsed_cycles;
            __osSetTimerIntr(t->value);
            return;
        } else {
            t->prev->next = t->next;
            t->next->prev = t->prev;
            t->next = NULL;
            t->prev = NULL;
            if (t->mq != NULL) {
                if (t->mq != &__osProfTimerQ) {
                    osSendMesg(t->mq, t->msg, OS_MESG_NOBLOCK);
                } else {
                    pc = __osRunQueue->context.pc;
                    for (prof = __osProfileList; prof < __osProfileListEnd; prof++) {
                        offset = pc - (u32)prof->text_start;
                        if (offset >= 0 && (s32)prof->text_end - (s32)pc > 0) {
                            prof->histo_base[offset >> 2]++;
                            goto profDone;
                        }
                    }
                    __osProfileOverflowBin++;
                }
            }
        profDone:
            if (t->interval != 0) {
                t->value = t->interval;
                __osInsertTimer(t);
            }
        }
    }
}

void __osSetTimerIntr(OSTime tim) {
    OSTime NewTime;
    u32 savedMask;

    if (tim < 468) {
        tim = 468;
    }
    savedMask = __osDisableInt();
    __osTimerCounter = osGetCount();
    NewTime = __osTimerCounter + tim;
    __osSetCompare(NewTime);
    __osRestoreInt(savedMask);
}

OSTime __osInsertTimer(OSTimer *t) {
    OSTimer *timep;
    OSTime tim;
    u32 savedMask;

    savedMask = __osDisableInt();
    for (timep = __osTimerList->next, tim = t->value;
         timep != __osTimerList && tim > timep->value;
         tim -= timep->value, timep = timep->next) {
    }
    t->value = tim;
    if (timep != __osTimerList) {
        timep->value -= tim;
    }
    t->next = timep;
    t->prev = timep->prev;
    timep->prev->next = t;
    timep->prev = t;
    __osRestoreInt(savedMask);
    return tim;
}
