#ifndef _ovl_80_EB2F0
#define _ovl_80_EB2F0

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

void func_800D76D0_shared_board(s32 arg0);
void func_800D7714_shared_board(void);
s32 func_800D771C_shared_board(s8 arg0, Object *arg1, s16 arg2, s16 arg3);
void func_800D7770_shared_board(s32 arg0);
void func_800D7790_shared_board(s8 arg0, Vec *arg1, s16 arg2, s16 arg3);
void MBMapFullExec(s32 playerPadNo);

#endif //_ovl_80_EB2F0
