#ifndef _PARTY_COMMON_BRANCHARROW_H
#define _PARTY_COMMON_BRANCHARROW_H

#include "common_board.h"
#include "game/board.h"

UnkBoard2 *MBBranchArrowCreate(s32 arg0);
UnkEA790Struct* MBBranchArrowGrpCreate(void);
void MBBranchArrowGrpKill(UnkEA790Struct* arg0);
void MBBranchArrowGrpAdd(UnkEA790Struct *arg0, UnkBoard2 *arg1, u16 arg2);
void MBBranchArrowGrpRemove(UnkEA790Struct *arg0, UnkBoard2* arg1); //unused
UnkBoard2* MBBranchArrowGrpArrowGet(UnkEA790Struct* arg0, s16 arg1);

#endif //_PARTY_COMMON_BRANCHARROW_H