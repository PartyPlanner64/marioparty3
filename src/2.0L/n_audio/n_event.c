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

ALMicroTime n_alEvtqNextEvent(ALEventQueue *evtq, N_ALEvent *evt) {
    N_ALEventListItem *item;
    ALMicroTime delta;
    OSIntMask mask;

    mask = osSetIntMask(OS_IM_NONE);

    item = (N_ALEventListItem *)evtq->allocList.next;

    if (item != NULL) {
        alUnlink((ALLink *)item);
        bcopy(&item->evt, evt, sizeof(*evt));
        alLink((ALLink *)item, &evtq->freeList);
        delta = item->delta;
    } else {
        /* If we get here, most likely the event queue overflowed. */
        evt->type = -1;
        delta = 0;
    }

    osSetIntMask(mask);

    return delta;
}

void n_alEvtqPostEvent(ALEventQueue *evtq, N_ALEvent *evt, ALMicroTime delta) {
    N_ALEventListItem *item;
    N_ALEventListItem *nextItem;
    ALLink *node;
    s32 postAtEnd = 0;
    OSIntMask mask;

    mask = osSetIntMask(OS_IM_NONE);

    item = (N_ALEventListItem *)evtq->freeList.next;
    if (item == NULL) {
        osSetIntMask(mask);
        return;
    }

    alUnlink((ALLink *)item);
    bcopy(evt, &item->evt, sizeof(*evt));

    if (delta == AL_EVTQ_END) {
        postAtEnd = -1;
    }

    for (node = &evtq->allocList; node != NULL; node = node->next) {
        if (node->next == NULL) { /* end of the list */
            if (postAtEnd) {
                item->delta = 0;
            } else {
                item->delta = delta;
            }
            alLink((ALLink *)item, node);
            break;
        } else {
            nextItem = (N_ALEventListItem *)node->next;

            if (delta < nextItem->delta) {
                item->delta = delta;
                nextItem->delta -= delta;

                alLink((ALLink *)item, node);
                break;
            }

            delta -= nextItem->delta;
        }
    }

    osSetIntMask(mask);
}

/* n_alEvtqFlushType: flushes events according to their type. */
void n_alEvtqFlushType(ALEventQueue *evtq, s16 type) {
    ALLink *thisNode;
    ALLink *nextNode;
    N_ALEventListItem *thisItem, *nextItem;
    OSIntMask mask;

    mask = osSetIntMask(OS_IM_NONE);

    thisNode = evtq->allocList.next;
    while (thisNode != NULL) {
        nextNode = thisNode->next;
        thisItem = (N_ALEventListItem *)thisNode;
        nextItem = (N_ALEventListItem *)nextNode;
        if (thisItem->evt.type == type) {
            if (nextItem != NULL) {
                nextItem->delta += thisItem->delta;
            }
            alUnlink(thisNode);
            alLink(thisNode, &evtq->freeList);
        }
        thisNode = nextNode;
    }

    osSetIntMask(mask);
}
