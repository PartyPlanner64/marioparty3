#ifndef _PARTY_COMMON_MOVE_H
#define _PARTY_COMMON_MOVE_H

#include "common_board.h"
#include "game/board.h"

void MBPlayerPosMasuSet(s16 playerNo, s16 spaceIdx);
void MBVecDirGet(Vec *arg0, Vec *arg1, Vec *arg2);
void MBPlayerDirPosSet(s16 playerIdx, Vec* arg1);
void MBModelDirMasuSet(Object* arg0, s16 arg1);
void MBVecForwardSet(Vec* out);
void MBPlayerForwardSet(s16 playerNo);
void MBModelBillboardSet(Object* obj);
void MBPlayerMasuSwap(s16 playerNoOne, s16 playerNoTwo);
void MBPlayerMasuColorSet(s16 playerNo, s16 spaceType);
s16 MBTotalStarGet(void);
s16 MBRandCheck100(s8 arg0);
s16 MBTurnRemain(void);
s16 MBPadStkCheck(s16 arg0, f32 arg1);
void MBMesSpeedSet(s16 arg0);
Process* MBVecRotLerpCreate(Vec* arg0, Vec* arg1, Vec* arg2, s32 arg3);
Process* MBVecRotLerpSpinCreate(Vec* arg0, Vec* arg1, Vec* arg2, s32 arg3);
void MBPlayerRotMasuStart(s16 playerNo, s32 arg1, s16 masuAbsIndex);
Process *MBPlayerPosMoveCreate(Vec *arg0, Vec *arg1, Vec *outVec, s32 interpolationTime);
void MBPlayerPosMoveSet(s16 playerNo, s32 interpolationFrameTotal);
Process* MBVecSpeedMoveCreate(Vec* arg0, Vec* arg1, Vec* arg2, f32 arg3);
Process* MBVecSpeedMove2Create(Vec* arg0, Vec* arg1, Vec* arg2, f32 arg3);
void MBMoveMasuSet(s16 playerNo, s16 link, s16 idx);
void MBMoveNextMasuSet(s16 playerNo, s16 arg1, s16 arg2);
void MBMoveBackMasuSet(s16 playerNo, s16 arg1, s16 arg2);
s32 MBBoardRestartSet(void);
Process* MBModelHoverCreate(Object* arg0, f32 arg1, f32 arg2);

#endif //_PARTY_COMMON_MOVE_H