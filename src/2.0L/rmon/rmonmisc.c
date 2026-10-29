#include "common.h"
#include "rmonint.h"

static OSThread rmonIOThread;
static OSMesg rmonMsgs[8];
static u64 rmonIOStack[2048];
static OSMesg rmonPiMsgs[8];
static OSMesgQueue rmonPiMQ;

int __rmonSetFault(KKHeader *req) {
    KKFaultRequest *request = (KKFaultRequest *)req;
    KKObjectEvent reply;

    reply.header.code = request->header.code;
    reply.header.error = TV_ERROR_NO_ERROR;
    reply.object = request->tid;

    __rmonSendReply(&reply.header, sizeof(reply), KK_TYPE_REPLY);
    return TV_ERROR_NO_ERROR;
}

void __rmonInit(void) {
    osCreateMesgQueue(&__rmonMQ, rmonMsgs, ARRAY_COUNT(rmonMsgs));
    osSetEventMesg(OS_EVENT_CPU_BREAK, &__rmonMQ, (OSMesg)RMON_MESG_CPU_BREAK);
    osSetEventMesg(OS_EVENT_SP_BREAK, &__rmonMQ, (OSMesg)RMON_MESG_SP_BREAK);
    osSetEventMesg(OS_EVENT_FAULT, &__rmonMQ, (OSMesg)RMON_MESG_FAULT);
    osSetEventMesg(OS_EVENT_THREADSTATUS, &__rmonMQ, NULL);
    osCreateThread(&rmonIOThread, 0, (void (*)(void *))__rmonIOhandler, NULL, rmonIOStack + ARRAY_COUNT(rmonIOStack),
                   OS_PRIORITY_MAX);
    osCreatePiManager(OS_PRIORITY_PIMGR, &rmonPiMQ, rmonPiMsgs, ARRAY_COUNT(rmonPiMsgs));
    osStartThread(&rmonIOThread);
}

void __rmonPanic(void) {
    for (;;) {}
}

int __rmonSetComm(KKHeader *req) {
    KKObjectEvent reply;

    reply.header.code = req->code;
    reply.object = 0;
    reply.header.error = TV_ERROR_NO_ERROR;

    __rmonSendReply(&reply.header, sizeof(reply), KK_TYPE_REPLY);

    return TV_ERROR_NO_ERROR;
}
