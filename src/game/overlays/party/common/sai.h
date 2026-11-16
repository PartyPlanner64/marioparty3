#ifndef _PARTY_COMMON_SAI_H
#define _PARTY_COMMON_SAI_H

#include "common_board.h"
#include "game/board.h"

void MBSaiSePlay(s32 arg0);
void MBSaiValueClear(void);
void MBSaiInit(void);
void MBSaiNumSprCreate(s32 arg0);
void MBSaiNumShow(s32 arg0);
void MBSaiNumObjKill(s32 arg0);
s32 MBSaiNumKill(s32 arg0);
void MBSaiNumCountDown(s32 arg0);
void MBSaiMdlDispOff(s32 arg0);
void MBSaiDispOff(s32 arg0);
void MBSaiMdlDispOn(s32 arg0);
void MBSaiDispOn(s32 arg0);
void MBSaiTypeSet(s32 arg0, s8 arg1);
s16 MBSaiCreate(s32 arg0);
void MBSaiKill(s32 arg0);
void MBSaiClose(void);
void MBSaiHit(s32 arg0);
s32 MBSaiExistCheck(s32 arg0);
void MBSaiValueSet(s32 arg0, s32 arg1);
void MBSaiValueForceSet(s32 arg0, s32 arg1);
s32 MBSaiValueGet(s32 arg0);
Process* MBSaiPlayerCreate(s32 playerNo);
Process* MBKakusiStarBlockCreate(s32 arg0);
Process* MBKakusiItemBlockCreate(s32 arg0, s32 arg1);
Process* MBKakusiCoinBlockCreate(s32 arg0);
u8 MBKakusiWaitCheck(void);
void MBKakusiWaitOn(void);
void MBKakusiWaitOff(void);
void MBSaiSeStop(s32 arg0);
void MBSaiSeResume(s32 arg0);
void MBSaiModeSet(s8 arg0);
void MBSaiValueNoSet(s32 arg0, s32 arg1);
void MBSaiNumSet(s32 arg0, s32 arg1);
s32 MBSaiTypeGet(s32 arg0);
void MBSeqVolDownStart(void); //unused
void MBSeqVolUpStart(void);

#endif //_PARTY_COMMON_SAI_H