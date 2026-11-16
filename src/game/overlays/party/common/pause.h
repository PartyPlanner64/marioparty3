#ifndef _PARTY_COMMON_PAUSE_H
#define _PARTY_COMMON_PAUSE_H

#include "common_board.h"
#include "game/board.h"

void MBModelJumpWait(Object*);
void MBMesWaitSet(s32 arg0);
s32 MBMesWaitGet(void);
void MBWinComKeyWait(s32 arg0, s32 arg1);
void MBWinComKeyWaitKeep(s32 arg0, s32 arg1);
void MBWinComKey2Wait(s32 arg0, s32 arg1, s32 arg2); //unused
void MBWinComKey2WaitKeep(s32 arg0, s32 arg1, s32 arg2); //unused
void MBWinComKeyAllWait(s32 arg0);
void MBWinComKeyAllWaitKeep(s32 arg0);
void MBWinComKeyAnyWait(s32 arg0);
void MBModelJumpSet(Object* arg0, f32 arg1, f32 arg2);
s32 MBModelJumpCheck(Object* arg0);
u32 MBMotionEndShiftSet(Object* arg0, s16 arg1, s16 arg2);
void MBMotionShiftSetDef(Object *arg0, s16 arg1, s32 arg2); //unused
void MBModelMotionWait(Object *arg0);
s32 MBPlayerRankCalc(s32 player);
s32 MBPlayerStealRankGet(s32 arg0);
s32 MBPlayerScoreGet(s32 arg0);
s32 MBPlayerBonusScoreGet(s32 arg0); //unused
s32 MBRand(f32 arg0);
void MBGuideFaceCreate(Object *arg0, s16 arg1, s16 arg2, s32 arg3);
void MBGuideFaceSet(Object* arg0, s32 arg1);
s32 MBPlayerRankRandGet(s32 arg0);
s32 MBPauseMesNumGet(s32 arg0);
void MBPauseCreate(s32 arg0);
void MBMotShiftInit(void);
void MBMotShiftClose(void);

#endif //_PARTY_COMMON_PAUSE_H