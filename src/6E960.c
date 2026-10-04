#include "common.h"

void func_8006DD60_main(ALEventQueue *evtq, ALEventListItem *items, s32 itemCount) {
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

INCLUDE_ASM("asm/nonmatchings/6E960", func_8006DDDC_main);

INCLUDE_ASM("asm/nonmatchings/6E960", alEvtqPostEvent);

INCLUDE_ASM("asm/nonmatchings/6E960", func_8006DF80_main);
