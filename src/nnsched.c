#include "common.h"
#include "graphics.h"

extern unkSchedStruct *D_800BBAC0_main;

INCLUDE_ASM("asm/nonmatchings/nnsched", InitSchedulerEvent);

INCLUDE_ASM("asm/nonmatchings/nnsched", InitScheduler);

INCLUDE_ASM("asm/nonmatchings/nnsched", AddSchedulerClient);

INCLUDE_ASM("asm/nonmatchings/nnsched", RemoveSchedulerClient);

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
