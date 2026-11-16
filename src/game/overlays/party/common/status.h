#ifndef _PARTY_COMMON_STATUS_H
#define _PARTY_COMMON_STATUS_H

#include "common_board.h"
#include "game/board.h"

extern s32 mbItemIconSprTbl[];
extern s16 mbItemCursorGrpId;

void MBStatusCreate(void); // start MBStatusMain process
void MBStatusKill(void);
void MBStatusColorSet(u32 playerNo, s32 turnStatus);
s32 MBStatusColorGet(s32 playerNo);
void MBStatusParamSet(s32 playerNo, s32 arg1);
void MBStatusPosSet(s32 playerIndex, s16 arg1, s16 arg2);
void MBStatusDispSideSet(s32 playerNo, s32 arg1);
void MBStatusSideSet(s32 playerNo, s32 arg1);
s32 MBStatusDispMoveSet(s32 arg0);
s32 MBStatusItemDispGet(s32 playerNo);
s32 MBStatusMoveCheck(void);
s32 MBMgTypeCalc(void);
void MBVsSprCreate(void);
void MBVsSprCreateY(f32 arg0, f32 arg1);
void MBVsSprKill(void);
void MBStatusPulseStop(s32 arg0);
void MBCoinTakeCreateSound(s32 playerIndex, s32 coinAmount, s32 arg2);
void MBCoinTakeCreate(s32 playerNo, s32 arg1);
s32 MBCoinTakeCheck(s32 playerNo);
s32 MBStatusHideCheck(void);
void MBStatusHideAll(void);
void MBStatusShowAll(void);
void MBStatusVsPlayerBSet(s32 arg0);
// Declared without a prototype: chancetime calls this with two arguments.
void MBStatusCreateHidden();
void MBStatusVsKill(void);
void MBStatusVsPlayerSet(s32 arg0, s32 arg1);
void MBStatusVsAMove(void);
void MBStatusVsBMove(void);
void MBStatusItemIconSprReinit(s32 arg0);
void MBStatusItemSprKill(s32 playerIndex);
void MBStatusItemDispSet(s32 playerNo, s32 arg1);
void MBStatusItemDispSetAll(s32 arg0);
void MBStatusSprPosGet(s16 arg0, s16 arg1, f32 *arg2, f32 *arg3);
void MBStatusItemOfsApply(s32 playerNo, s32 arg1, f32 arg2, f32 arg3);
void MBStatusItemSprPosGet(s32 playerNo, s32 arg1, f32 *arg2, f32 *arg3);
void MBStatusItemPosSet(s32 playerNo, s32 arg1, s16 arg2, s16 arg3);
void MBStatusItemTPLvlSet(s32 playerNo, s32 arg1, s16 arg2);
void MBStatusItemRotSet(s32 playerNo, s32 arg1, f32 arg2);
void MBStatusItemScaleSet(s32 playerNo, s32 arg1, f32 arg2, f32 arg3);
void MBStatusItemPriSet(s32 playerNo, s32 arg1, u16 arg2);
void MBStatusItemAttrSet(s32 playerNo, s32 arg1, u16 arg2);
void MBStatusItemAttrReset(s32 playerNo, s32 arg1, u16 arg2);
void MBSprGrpFlagSet(s16 arg0, u16 arg1);
void MBStatusSprBmpClear(s16 arg0, s16 arg1);
void MBStatusScaleSet(s32 arg0, f32 xScale, f32 yScale);
void MBStatusShrink(s32 playerNo);
void MBStatusItemPosGet(s32 playerIndex, s32 itemIndex, s32 *xPos, s32 *yPos);
void MBStatusGrow(s32 playerNo);
void MBStatusItemDispOn(void);
void MBStatusItemDispOff(void);
void MBStatusTeamPlayerSet(s32 arg0, s32 arg1);

#endif //_PARTY_COMMON_STATUS_H
