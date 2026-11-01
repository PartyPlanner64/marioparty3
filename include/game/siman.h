#ifndef _GAME_SIMAN_H
#define _GAME_SIMAN_H

#include "ultra64.h"
#include "game/nnsched.h"

#define HOS_PRIORITY_SIMGR 0x5A

typedef s32 (*HuSiFuncVoid)(void);
typedef s32 (*HuSiFunc)(void *);

typedef struct functionListEntryt {
    struct functionListEntryt *child;
    HuSiFuncVoid func;
    s16 type;
} functionListEntry;

typedef struct {
    HuSiFunc func;
    //functionListEntry *pFuncListEntry;
    void* arg;
    s32 ret;
    OSMesgQueue *recvQueue;
} unkMesg;

typedef struct {
    unkSchedStruct client;
    s32 unk0C;
    unkMesg* unkMsg;
} unkMesgWrapper;

void InitSI(void);
functionListEntry ** GetSIClientListTable(functionListEntry* entry);
s32 _AddSIClient(functionListEntry* node);
void AddSIClient(functionListEntry* entry, s16 type, void* func);
s32 _RemoveSIClient(functionListEntry* arg0);
void RemoveSIClient(void* entry);
void CallSIClient(s16 type);
s32 RequestSIFunction(unkMesg* siMessg, void* func, void* arg, s32 type);
void SIProc(void* arg0);

extern OSMesgQueue D_800CE1A0_main;
extern OSMesgQueue D_800D1220_main;

#endif
