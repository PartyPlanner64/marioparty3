#include "common.h"
#include "PR/n_libaudio.h"

void n_alEvtqNew(ALEventQueue *evtq, N_ALEventListItem *items, s32 itemCount) {
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

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_event", n_alEvtqNextEvent);

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_event", n_alEvtqPostEvent);

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_event", n_alEvtqFlushType);
