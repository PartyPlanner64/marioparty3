#include "common.h"
#include "piint.h"

#define PI_Q_BUF_LEN 1

static OSMesg piAccessBuf[PI_Q_BUF_LEN];

void __osPiCreateAccessQueue(void) {
    OSMesgQueue *queue = &__osPiAccessQueue;

    __osPiAccessQueueEnabled = 1;
    osCreateMesgQueue(queue, piAccessBuf, PI_Q_BUF_LEN);
    osSendMesg(queue, NULL, OS_MESG_NOBLOCK);
}

void __osPiGetAccess(void) {
    OSMesg msg;

    if (__osPiAccessQueueEnabled == 0) {
        __osPiAccessQueueEnabled = 1;
        osCreateMesgQueue(&__osPiAccessQueue, piAccessBuf, PI_Q_BUF_LEN);
        osSendMesg(&__osPiAccessQueue, NULL, OS_MESG_NOBLOCK);
    }
    osRecvMesg(&__osPiAccessQueue, &msg, OS_MESG_BLOCK);
}

void __osPiRelAccess(void) {
    osSendMesg(&__osPiAccessQueue, NULL, OS_MESG_NOBLOCK);
}
