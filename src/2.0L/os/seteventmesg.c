#include "common.h"
#include "PR/osint.h"

extern u32 _osPreNMI;
u32 _osShutdown = 0;

void osSetEventMesg(OSEvent event, OSMesgQueue *mq, OSMesg msg) {
    register u32 saveMask = __osDisableInt();
    __OSEventState *es;

    es = &__osEventStateTab[event];
    es->messageQueue = mq;
    es->message = msg;

    if (event == OS_EVENT_PRENMI) {
        if (_osPreNMI && _osShutdown == 0) {
            osSendMesg(mq, msg, OS_MESG_NOBLOCK);
        }
        _osShutdown = 1;
    }
    __osRestoreInt(saveMask);
}
