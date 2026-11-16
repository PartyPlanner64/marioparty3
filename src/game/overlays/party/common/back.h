#ifndef _PARTY_COMMON_BACK_H
#define _PARTY_COMMON_BACK_H

#include "common_board.h"
#include "game/board.h"

typedef struct UnkFAF78 {
    /* 0x00 */ s32 unk_00;   /* count */
    /* 0x04 */ s32 *unk_04;  /* id list */
    /* 0x08 */ char pad08[4];
} UnkFAF78; /* size = 0xC */

void MBBackArcInit(u32 arg0);
void MBBackReset(void);
void MBBackClose(void);
void MBBackCreate(s32 arg0, s32 arg1);
void MBBackLoad(s32 arg0);
void MBBackKill(void);
void MBBackThreadPriHighSet(void);
void MBBackThreadPriLowSet(void);
void MBBackStreamStart(void);
void MBBackStreamStop(void);
f32 MBBackMdlScaleGet(void);
f32 MBCameraZoomGet(void);
void MBCameraZoomSet(f32 zoom);
Process* MBCameraZoomMotStart(f32 arg0);
Process* MBCameraZoomMotFastStart(f32 arg0);
void MBCameraKill(void);
void MBCameraNearFarSet(f32 arg0, f32 arg1);
void MBCameraSpeedDivSet(f32 arg0);
f32 MBCameraSpeedDivGet(void);
u16 MBCameraPos3DSet(Vec *arg0);
u16 MBCameraPos2DSet(Vec2f* arg0);
void MBCameraPos3DGet(Vec2f* arg0);
void MBCameraPos2DGet(Vec2f *arg0);
void MBCamera3Dto2D(Vec* arg0, f32* arg1);
void MBBackTPLvlSet(u8 arg0);
void MBCameraSpeedSet(f32 arg0);
f32 MBCameraSpeedGet(void);
s32 MBCameraStopCheck(void);
void MBBackRefresh(Vec* arg0, s32 arg1);
void MBBackSprInit(void);
void MBBackSprKillAll(void);
void MBBackSprDispOn(void);
void MBBackSprDispOff(void);
void MBMasuInit(void);
void MBMasuArrowAngleAdd(f32 arg0);
void MBMasuClose(void);
void MBMasuBmpModeSet(s16 arg0);
void MBMasuStarSet(s32 arg0, s16 arg1);
s32 MBMasuCreate(s32 arg0, s32 arg1);
void MBMasuKill(void);

//file split?
SpaceData *MBMasuGet(s16 arg0);
s16 MBMasuLinkMasuIdGet(u16 linkIdx, u16 spaceIdx);
s16 MBMasuLinkNumGet(u16 arg0);
void MBMasuLinkIdxGet(s16 arg0, s8 *chainOut, s8 *linkOut);
void MBMasuTypeSet(s16 spaceIdx, s32 newSpaceType);
void MBMasuLinkTypeSet(u16 linkNo, u16 curSpaceType, u8 newSpaceType);
void MBMasuBounceCreate(s16 arg0);
void MBMasuEventTblAdd(event_table_entry *arg0);
s32 MBMasuEventCall(s16 arg0, s16 arg1);
void MBMasuCurSet(s16 arg0);
s16 MBMasuCurGet(void);
s16 MBMasuKakusiBlockGet(u8 arg0);
void MBMasuBlockTblExtSet(s16 *arg0);
void MBMasuBlockTblSet(s16 *arg0);
void MBMasuTypeListCreate(void);
u8 MBMasuTypeListGet(s32 arg0, s32 arg1);
void MBMasuDispOn(void);
void MBMasuDispOff(void);

#endif //_PARTY_COMMON_BACK_H