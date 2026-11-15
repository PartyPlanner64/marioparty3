#ifndef _PARTY_COMMON_BRANCH_H
#define _PARTY_COMMON_BRANCH_H

#include "common_board.h"
#include "game/board.h"

s32 func_800D7250_shared_board(UnkEA790Struct* arg0, s32 arg1);
s32 func_800D742C_shared_board(UnkEA790Struct* arg0, s16 playerNo, s32 arg2);
s32 func_800D7518_shared_board(UnkEA790Struct* arg0);
void func_800D7568_shared_board(UnkBoard2* arg0, Vec* arg1, Vec* arg2, f32 arg3);
UnkEA790Struct* func_800D76A0_shared_board(s16 arg0, s16* arg1);

#endif //_PARTY_COMMON_BRANCH_H