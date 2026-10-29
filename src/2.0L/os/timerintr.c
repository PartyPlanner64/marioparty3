#include "common.h"
#include "PR/osint.h"

extern OSTimer *D_800A2DD0_main;
extern OSTime D_800CE2B8_main;
extern u32 D_800CB898_main;
extern u32 D_800CD1D8_main;
extern u32 D_800D2000_main;
extern OSMesgQueue D_800D41A8_main;
extern OSProf *D_800CCF24_main;
extern OSProf *D_800D4190_main;
extern u32 D_800CC0B0_main;

void __osTimerServicesInit(void) {
    OSTimer *timer = D_800A2DD0_main;

    D_800CE2B8_main = 0;
    D_800CB898_main = 0;
    D_800CD1D8_main = 0;

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

    if (D_800A2DD0_main->next == D_800A2DD0_main) {
        return;
    }
    while (TRUE) {
        t = D_800A2DD0_main->next;
        if (t == D_800A2DD0_main) {
            __osSetCompare(0);
            D_800D2000_main = 0;
            break;
        }
        count = osGetCount();
        elapsed_cycles = count - D_800D2000_main;
        D_800D2000_main = count;
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
                if (t->mq != &D_800D41A8_main) {
                    osSendMesg(t->mq, t->msg, OS_MESG_NOBLOCK);
                } else {
                    pc = __osRunQueue->context.pc;
                    for (prof = D_800CCF24_main; prof < D_800D4190_main; prof++) {
                        offset = pc - (u32)prof->text_start;
                        if (offset >= 0 && (s32)prof->text_end - (s32)pc > 0) {
                            prof->histo_base[offset >> 2]++;
                            goto profDone;
                        }
                    }
                    D_800CC0B0_main++;
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
    D_800D2000_main = osGetCount();
    NewTime = D_800D2000_main + tim;
    __osSetCompare(NewTime);
    __osRestoreInt(savedMask);
}

OSTime __osInsertTimer(OSTimer *t) {
    OSTimer *timep;
    OSTime tim;
    u32 savedMask;

    savedMask = __osDisableInt();
    for (timep = D_800A2DD0_main->next, tim = t->value;
         timep != D_800A2DD0_main && tim > timep->value;
         tim -= timep->value, timep = timep->next) {
    }
    t->value = tim;
    if (timep != D_800A2DD0_main) {
        timep->value -= tim;
    }
    t->next = timep;
    t->prev = timep->prev;
    timep->prev->next = t;
    timep->prev = t;
    __osRestoreInt(savedMask);
    return tim;
}
