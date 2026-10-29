#include "common.h"
#include "piint.h"

extern OSMesg D_800C3940_main[1];

void __osPiCreateAccessQueue(void) {
    OSMesgQueue *queue = &__osPiAccessQueue;

    __osPiAccessQueueEnabled = 1;
    osCreateMesgQueue(queue, D_800C3940_main, 1);
    osSendMesg(queue, NULL, OS_MESG_NOBLOCK);
}

void __osPiGetAccess(void) {
    OSMesg msg;

    if (__osPiAccessQueueEnabled == 0) {
        __osPiAccessQueueEnabled = 1;
        osCreateMesgQueue(&__osPiAccessQueue, D_800C3940_main, 1);
        osSendMesg(&__osPiAccessQueue, NULL, OS_MESG_NOBLOCK);
    }
    osRecvMesg(&__osPiAccessQueue, &msg, OS_MESG_BLOCK);
}

void __osPiRelAccess(void) {
    osSendMesg(&__osPiAccessQueue, NULL, OS_MESG_NOBLOCK);
}
