#ifndef _PARTY_COMMON_COM_H
#define _PARTY_COMMON_COM_H

#include "common_board.h"
#include "game/board.h"

s16 MBComTreeExec(DecisionTreeNonLeafNode *arg0);
void MBComItemDecideHookSet(s32 (*arg0)(void));
s32 MBComItemDecide(void);
void func_800DA778_shared_board(s32 arg0);

#endif //_PARTY_COMMON_COM_H
