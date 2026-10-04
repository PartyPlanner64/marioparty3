#include "common.h"

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/event", func_800757B0_main);

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/event", func_8007582C_main);

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/event", func_800758C4_main);

void func_800759D0_main(ALEventQueue *evtq) {
    ALEventListItem *item;
    ALEventListItem *nextItem;
    OSIntMask mask = osSetIntMask(OS_IM_NONE);

    item = (ALEventListItem *)evtq->allocList.next;

    while (item != NULL) {
        nextItem = (ALEventListItem *)item->node.next;
        alUnlink(&item->node);
        alLink(&item->node, &evtq->freeList);
        item = nextItem;
    }

    osSetIntMask(mask);
}

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/event", func_80075A48_main);
