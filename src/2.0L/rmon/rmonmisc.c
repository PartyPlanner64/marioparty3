#include "common.h"
#include "rmonint.h"

extern OSThread D_800C4D20_main;    // rmonIOThread
extern OSMesg D_800C4ED0_main[8];   // rmonMsgs
extern OSMesg D_800C8EF0_main[8];   // rmonPiMsgs
extern OSMesgQueue D_800C8F10_main; // rmonPiMQ

int __rmonSetFault(KKHeader *req) {
    KKFaultRequest *request = (KKFaultRequest *)req;
    KKObjectEvent reply;

    reply.header.code = request->header.code;
    reply.header.error = TV_ERROR_NO_ERROR;
    reply.object = request->tid;

    __rmonSendReply(&reply.header, sizeof(reply), KK_TYPE_REPLY);
    return TV_ERROR_NO_ERROR;
}

#ifdef NON_MATCHING
/* Matches once rmonIOStack (0x800C4EF0, 0x4000 bytes) is split out of the merged D_800C4ED0_main bss symbol. */
extern u64 D_800C4EF0_main[2048]; // rmonIOStack

void __rmonInit(void) {
    osCreateMesgQueue(&D_800D6A60_main, D_800C4ED0_main, ARRAY_COUNT(D_800C4ED0_main));
    osSetEventMesg(OS_EVENT_CPU_BREAK, &D_800D6A60_main, (OSMesg)RMON_MESG_CPU_BREAK);
    osSetEventMesg(OS_EVENT_SP_BREAK, &D_800D6A60_main, (OSMesg)RMON_MESG_SP_BREAK);
    osSetEventMesg(OS_EVENT_FAULT, &D_800D6A60_main, (OSMesg)RMON_MESG_FAULT);
    osSetEventMesg(OS_EVENT_THREADSTATUS, &D_800D6A60_main, NULL);
    osCreateThread(&D_800C4D20_main, 0, (void (*)(void *))__rmonIOhandler, NULL, D_800C4EF0_main + ARRAY_COUNT(D_800C4EF0_main),
                   OS_PRIORITY_MAX);
    osCreatePiManager(OS_PRIORITY_PIMGR, &D_800C8F10_main, D_800C8EF0_main, ARRAY_COUNT(D_800C8EF0_main));
    osStartThread(&D_800C4D20_main);
}
#else
INCLUDE_ASM("asm/nonmatchings/2.0L/rmon/rmonmisc", __rmonInit);
#endif

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
