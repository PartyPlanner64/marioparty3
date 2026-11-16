#ifndef _PARTY_COMMON_MAPFULL_H
#define _PARTY_COMMON_MAPFULL_H

#include "common_board.h"
#include "game/board.h"

typedef struct UnkBoard6 {
    /* 0x00 */ s8 unk_00;
    /* 0x04 */ Object* unk4;
    /* 0x08 */ Process *process;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ Vec unk10;
} UnkBoard6;

void MBMapFullInit(s32 arg0);
void MBMapFullClose(void);
s32 MBMapFullIconMdlAdd(s8 arg0, Object *arg1, s16 arg2, s16 arg3);
void MBMapFullIconRemove(s32 arg0);
void MBMapFullIconPosAdd(s8 arg0, Vec *arg1, s16 arg2, s16 arg3);
void MBMapFullExec(s32 playerPadNo);

#endif //_PARTY_COMMON_MAPFULL_H
