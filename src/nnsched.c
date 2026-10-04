#include "common.h"
#include "graphics.h"

extern unkSchedStruct *D_800BBAC0_main;

INCLUDE_ASM("asm/nonmatchings/nnsched", InitSchedulerEvent);

INCLUDE_ASM("asm/nonmatchings/nnsched", InitScheduler);

INCLUDE_ASM("asm/nonmatchings/nnsched", AddSchedulerClient);

void RemoveSchedulerClient(unkSchedStruct *client) {
    OSIntMask mask = osSetIntMask(OS_IM_NONE);
    unkSchedStruct *prevClient = NULL;
    unkSchedStruct *currClient = D_800BBAC0_main;

    while (currClient != NULL) {
        if (currClient == client) {
            if (prevClient != NULL) {
                prevClient->unk00 = currClient->unk00;
            } else {
                D_800BBAC0_main = client->unk00;
            }
            break;
        }
        prevClient = currClient;
        currClient = currClient->unk00;
    }

    osSetIntMask(mask);
}

void EventBroadcast(s32 msg) {
    unkSchedStruct *client = D_800BBAC0_main;

    while (client != NULL) {
        if (msg & client->unk08) {
            osSendMesg(client->unk04, (OSMesg)msg, OS_MESG_NOBLOCK);
        }
        client = client->unk00;
    }
}

INCLUDE_ASM("asm/nonmatchings/nnsched", EventHandler);

INCLUDE_ASM("asm/nonmatchings/nnsched", ScExecuteAudio);

INCLUDE_ASM("asm/nonmatchings/nnsched", ScExecuteGraphics);
