#include "common.h"

INCLUDE_ASM("asm/nonmatchings/6C9F0", func_8006BDF0_main);

INCLUDE_ASM("asm/nonmatchings/6C9F0", func_8006BF60_main);

INCLUDE_ASM("asm/nonmatchings/6C9F0", func_8006C408_main);

INCLUDE_ASM("asm/nonmatchings/6C9F0", func_8006C4C8_main);

INCLUDE_ASM("asm/nonmatchings/6C9F0", func_8006CD00_main);

void func_8006CE90_main(ALEventQueue *evtq, ALEventListItem *item) {
    ALLink *cur;
    ALLink *next;
    OSIntMask mask;

    mask = osSetIntMask(1);

    for (cur = &evtq->allocList; cur != NULL; cur = cur->next) {
        next = cur->next;

        if (next == NULL) {
            alLink(&item->node, cur);
            break;
        }
        if (item->delta < ((ALEventListItem *)next)->delta) {
            ((ALEventListItem *)next)->delta -= item->delta;
            alLink(&item->node, cur);
            break;
        }
        item->delta -= ((ALEventListItem *)next)->delta;
    }

    osSetIntMask(mask);
}

void func_8006CF20_main(ALCSPlayer *seqp, f32 scale) {
    if (seqp->target != NULL) {
        seqp->uspt = (s32)(scale * seqp->target->qnpt);
    } else {
        seqp->uspt = 0x1E8;
    }
}

INCLUDE_ASM("asm/nonmatchings/6C9F0", func_8006CF54_main);
