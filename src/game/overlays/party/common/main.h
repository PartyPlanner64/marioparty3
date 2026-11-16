#ifndef _PARTY_COMMON_MAIN_H
#define _PARTY_COMMON_MAIN_H

#include "common_board.h"
#include "game/board.h"

void MBOvlCall(s32 id, s16 event, u16 stat);
void MBOvlCallInit(void);
void MBOvlCallExec(void);
void MBBoardReturnOff(void);
s16 MBOvlCallCheck(void);
void MBObjectSetup(s32 arg0, s16 arg1, s32 arg2, s32 unused);
void MBExit(void);
void MBHatenaFuncSet(void (*arg0)(void));
void MBExitHookSet(void (*arg0)(void));
void MBKinokoEffKillHookSet(void (*arg0)());
void MBBoardParamSet(s32 arg0);
void MBCameraFocusModeSet(s16 arg0);
s16 MBCameraFocusModeGet(void);
void MBCameraFocusStaticPosSet(Vec *arg0);
void MBCameraFocusVecSet(Vec *arg0);
void MBPlayerPosFixSet(s32 playerNo, s32 arg1);
void MBKettouResultExec(void);
void MBKettouComResultSet(void);
s32 MBKettouPlayerBitGet(s32 arg0);
s32 MBPlayerJumpCheck(s32 arg0);
// Parameters unspecified to preserve item.c's original one-argument call to this two-argument function.
s32 MBKettouExec(); // Unprototyped: some callers omit the second argument.
s32 MBTurnTierGet(s32 turn);
void MBTurnHelpCreate(void);
void MBTurnHelpKill(void);
void MBGameModeWarpSet(void);
void MBGameModeKettouSet(void);
void MBGameModeMgSet(void);
void MBGameModeMajinLampSet(void);
void MBGameModeReloadSet(void);
void MBGameModeKoopaSet(void);
void MBStart(u32 arg0);
void MBExitOvlCallEx(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void MBExitOvlCall(s32 arg0, s16 arg1, s16 arg2);
void MBExitReq(s32 arg0);
void MBExitBoardSet(s16 arg0, s16 arg1); //unused
s16 MBExitFlagGet(void);
void MBCameraRefresh(Vec *arg0);

#endif //_PARTY_COMMON_MAIN_H