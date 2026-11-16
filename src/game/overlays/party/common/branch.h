#ifndef _PARTY_COMMON_BRANCH_H
#define _PARTY_COMMON_BRANCH_H

#include "common_board.h"
#include "game/board.h"

s32 MBBranchSelMesSend(UnkEA790Struct* arg0, s32 arg1);
s32 MBBranchSelStart(UnkEA790Struct* arg0, s16 playerNo, s32 arg2);
s32 MBBranchSelWait(UnkEA790Struct* arg0);
void MBBranchArrowPosSet(UnkBoard2* arg0, Vec* arg1, Vec* arg2, f32 arg3);
UnkEA790Struct* MBBranchArrowLinkCreate(s16 arg0, s16* arg1);

#endif //_PARTY_COMMON_BRANCH_H