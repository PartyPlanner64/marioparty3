#include "common.h"

void alEvtqNew(ALEventQueue *evtq, ALEventListItem *items, s32 itemCount) {
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

ALMicroTime alEvtqNextEvent(ALEventQueue *evtq, ALEvent *evt) {
    ALEventListItem *item;
    ALMicroTime delta;
    OSIntMask mask;

    mask = osSetIntMask(OS_IM_NONE);

    item = (ALEventListItem *)evtq->allocList.next;

    if (item) {
        alUnlink((ALLink *)item);
        alCopy((u8 *)&item->evt, (u8 *)evt, sizeof(*evt));
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

void alEvtqPostEvent(ALEventQueue *evtq, ALEvent *evt, ALMicroTime delta) {
    ALEventListItem *item;
    ALEventListItem *nextItem;
    ALLink *node;
    s32 postAtEnd = 0;
    OSIntMask mask;

    mask = osSetIntMask(OS_IM_NONE);

    item = (ALEventListItem *)evtq->freeList.next;
    if (!item) {
        osSetIntMask(mask);
        return;
    }

    alUnlink((ALLink *)item);
    alCopy((u8 *)evt, (u8 *)&item->evt, sizeof(*evt));

    if (delta == AL_EVTQ_END) {
        postAtEnd = -1;
    }

    for (node = &evtq->allocList; node != 0; node = node->next) {
        if (!node->next) { /* end of the list */
            if (postAtEnd) {
                item->delta = 0;
            } else {
                item->delta = delta;
            }
            alLink((ALLink *)item, node);
            break;
        } else {
            nextItem = (ALEventListItem *)node->next;

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

void alEvtqFlush(ALEventQueue *evtq) {
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

/* alEvtqFlushType: flushes events according to their type. */
void alEvtqFlushType(ALEventQueue *evtq, s16 type) {
    ALLink *thisNode;
    ALLink *nextNode;
    ALEventListItem *thisItem, *nextItem;
    OSIntMask mask;

    mask = osSetIntMask(OS_IM_NONE);

    thisNode = evtq->allocList.next;
    while (thisNode != 0) {
        nextNode = thisNode->next;
        thisItem = (ALEventListItem *)thisNode;
        nextItem = (ALEventListItem *)nextNode;
        if (thisItem->evt.type == type) {
            if (nextItem) {
                nextItem->delta += thisItem->delta;
            }
            alUnlink(thisNode);
            alLink(thisNode, &evtq->freeList);
        }
        thisNode = nextNode;
    }

    osSetIntMask(mask);
}
