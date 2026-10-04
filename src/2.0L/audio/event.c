#include "common.h"

void func_800757B0_main(ALEventQueue *evtq, ALEventListItem *items, s32 itemCount) {
    s32 i;

    evtq->eventCount = 0;
    evtq->allocList.next = NULL;
    evtq->allocList.prev = NULL;
    evtq->freeList.next = NULL;
    evtq->freeList.prev = NULL;

    for (i = 0; i < itemCount; i++) {
        alLink(&items[i].node, &evtq->freeList);
    }
}

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
