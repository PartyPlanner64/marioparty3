#ifndef _GAME_NNSCHED_H
#define _GAME_NNSCHED_H

#include "ultra64.h"

typedef struct unkSchedStruct {
    struct unkSchedStruct *unk00; // next client in list
    OSMesgQueue *unk04;
    s32 unk08;    // event mask
} unkSchedStruct; // sizeof 0xC

void InitSchedulerEvent(void);
void InitScheduler(u8 mode, u8 retraceCount);
void AddSchedulerClient(unkSchedStruct *client, OSMesgQueue *queue, s32 eventMask);
void RemoveSchedulerClient(unkSchedStruct *client);
void EventBroadcast(s32 msg);
void EventHandler(void *arg);
void ScExecuteAudio(void *arg);
void ScExecuteGraphics(void *arg);

#endif
