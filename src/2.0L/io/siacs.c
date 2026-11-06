#include "common.h"

#define SI_Q_BUF_LEN 1

u32 __osSiAccessQueueEnabled = 0;

extern OSMesgQueue __osSiAccessQueue;
static OSMesg siAccessBuf[SI_Q_BUF_LEN];

void __osSiCreateAccessQueue(void) {
    OSMesgQueue *queue = &__osSiAccessQueue;

    __osSiAccessQueueEnabled = 1;
    osCreateMesgQueue(queue, siAccessBuf, SI_Q_BUF_LEN);
    osSendMesg(queue, NULL, OS_MESG_NOBLOCK);
}

void __osSiGetAccess(void) {
    OSMesg msg;

    if (__osSiAccessQueueEnabled == 0) {
        __osSiAccessQueueEnabled = 1;
        osCreateMesgQueue(&__osSiAccessQueue, siAccessBuf, SI_Q_BUF_LEN);
        osSendMesg(&__osSiAccessQueue, NULL, OS_MESG_NOBLOCK);
    }
    osRecvMesg(&__osSiAccessQueue, &msg, OS_MESG_BLOCK);
}

void __osSiRelAccess(void) {
    osSendMesg(&__osSiAccessQueue, NULL, OS_MESG_NOBLOCK);
}
