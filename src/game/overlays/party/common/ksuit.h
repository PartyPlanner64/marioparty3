#ifndef _PARTY_COMMON_KSUIT_H
#define _PARTY_COMMON_KSUIT_H

#include "common_board.h"
#include "game/board.h"

extern Object *D_801011FC_shared_board;

Object* MBKSuitCreate(void);
void MBKSuitKill(void);
void MBKSuitInit(void);
void MBKSuitClose(void);
void MBKSuitMotionSet(s16 arg0, s32 arg1);
void MBKSuitMotionShiftSet(s16 arg0, s16 arg1, s16 arg2, s32 arg3);
void func_800E648C_shared_board(void);
void MBKSuitMotionLoad(s32 arg0, s32 arg1);

#endif //_PARTY_COMMON_KSUIT_H
