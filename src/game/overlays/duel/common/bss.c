#define NO_EXTERN_VARIABLES
#include "common_duel.h"
#include "game/gamemes.h"
#include "game/hvq.h"
#include "ovl_81.h"

/*
 * Some halfword arrays in this overlay's BSS are only halfword aligned, which
 * GCC won't produce for standalone arrays. They are grouped into structs here,
 * and the field symbols used by the original code are aliased in
 * undefined_syms.txt.
 */
typedef struct {
    /* 0x00 */ s16 sprGrp;
    /* 0x02 */ s16 sprAnims[2]; // mbdTelopPlayerAnim
} NameBss2CA8;

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x02 */ s16 sprGrps[2]; // mbdTelopLast5Grp
    /* 0x06 */ s16 sprAnims[2]; // mbdTelopLast5Anim
} NameBss2CB8;

// model.c
Object *mbdModelListHead BSS;
u16 mbdModelNum BSS;
s16 mbdMotionRefTbl[130] BSS;
u8 mbdModelPad[4] BSS; /* Unreferenced. */

// effect.c
Object *mbdEffBurstObjTbl[32] BSS;
s16 mbdEffSwirlMdl BSS;
omObjData *mbdEffSwirlObj BSS;
Vec mbdEffSwirlPos BSS;
Vec mbdEffSwirlPad BSS; /* Unreferenced. */

// mgcall.c
UnkC5770B70 mbdMgCallSlotTbl[5] BSS;
omObjData *mbdMgCallListObj BSS;
s8 mbdMgCallMgList[5] BSS;
s8 mbdMgCallType BSS;
s8 mbdMgCallPackOfs BSS;
s16 mbdMgCallBgGrp BSS;
s16 mbdMgCallBgAnim BSS;
s16 mbdMgCallCursorGrp BSS;
s16 mbdMgCallCursorAnim BSS;
s32 mbdMgCallMode BSS;
u8 mbdMgCallBssPad[4] BSS; /* Unreferenced. */
s16 mbdCoinChangeGrp[2] BSS;
s16 mbdCoinChangeAnimTbl[2][2] BSS;
omObjData *mbdCoinChangeObj[2] BSS;
u8 mbdCoinChangeMode BSS;
f32 mbdCoinChangePosTbl[2][2] BSS;
u8 mbdCoinChangePad[8] BSS; /* Unreferenced. */

// warp.c
s16 mbdItemWarpPlayerA BSS;
s16 mbdItemWarpPlayerB BSS;
s16 mbdWarpLink BSS;
s16 mbdWarpIdx BSS;
s16 mbdWarpBackLink BSS;
s16 mbdWarpBackIdx BSS;
u8 mbdWarpPad[4] BSS; /* Unreferenced. */
Vec mbdWarpPosA BSS;
Vec mbdWarpPosB BSS;
Vec mbdWarpPosC BSS;
Vec mbdWarpPosPad BSS; /* Unreferenced. */

// telop.c
GAMEMES mbdTelopMes BSS;
s16 mbdTelopMgTypeStrNo BSS;
u8 mbdTelopFlag BSS;
NameBss2CA8 mbdTelopPlayerGrp BSS;
omObjData *mbdTelopPlayerObj BSS;
omObjData *mbdTelopLast5Obj BSS;
NameBss2CB8 mbdTelopLast5StopF BSS;
s32 mbdTelopLast5Turn BSS;
s32 mbdTelopMgTypeY BSS;
UnkBoard4 *mbdTelopTitleSpr BSS;
UnkBoard4 *mbdTelopTitleShadowSpr BSS;
u8 mbdTelopPad[0xC] BSS; /* Unreferenced. */
Vec mbdGuideCameraEye BSS;
Vec mbdGuideCameraAt BSS;
Vec mbdGuideCameraUp BSS;
Vec mbdGuideCameraViewSize BSS;
Vec mbdGuideCameraViewPos BSS;
u8 mbdGuidePad[4] BSS; /* Unreferenced. */

// back.c
u32 mbdBackArcAddr BSS;
s32 mbdBackArcNum BSS;
u32 mbdBackFileAddr BSS;
f32 mbdCameraSpeed BSS;
u16 mbdBackFlag BSS;
s16 mbdBackOfsX BSS;
s16 mbdBackOfsY BSS;
s16 mbdBackHalfW BSS;
s16 mbdBackHalfH BSS;
u8 *mbdBackHvqWork BSS;
HvqHeader *mbdBackHvqCur BSS;
u8 mbdBackHvqPad[4] BSS; /* Unreferenced. */
OverlayBgEntry mbdBackTileTbl[50] BSS;
OverlayBgEntry *mbdBackTileMap[6][6] BSS;
HvqFileHeader *mbdBackHvqFileHdr BSS;
Process *mbdCameraUpdateProc BSS;
Process *mbdCameraZoomProc BSS;
f32 mbdCameraSpeedDiv BSS;
f32 mbdBackScale BSS;
Vec mbdCameraEye BSS;
Vec mbdCameraAt BSS;
Vec mbdCameraUp BSS;
Vec mbdCameraViewportSize BSS;
Vec mbdBackOrigin BSS;
OSMesgQueue mbdBackDmaMesgQ BSS;
OSMesg mbdBackDmaMesgBuf[50] BSS;
OSThread mbdBackDmaThread BSS;
u8 mbdBackDmaStack[0x800] BSS; // Stack of the mbdBackDmaThread thread.
OSThread mbdBackDecodeThread BSS;
OSPri mbdBackThreadPri BSS;
u8 mbdBackDecodeStack[0x80C] BSS; // Stack of the mbdBackDecodeThread thread.
OSMesgQueue mbdBackDecodeMesgQ BSS;
OSMesg mbdBackDecodeMesgBuf[50] BSS;
OSMesgQueue mbdBackDoneMesgQ BSS;
OSMesg mbdBackDoneMesgBuf[50] BSS;
OSMesgQueue mbdBackExitMesgQ BSS;
OSMesg mbdBackExitMesgBuf[2] BSS;
Vec2f mbdCameraScrTarget BSS;
f32 mbdCameraScrPos[2] BSS;
UnkBoard7 mbdBackSprTbl[64] BSS;
s32 mbdBackSprNum BSS;
u8 mbdBackSprPad[4] BSS; /* Unreferenced. */
Object *mbdBackMdlTbl[16] BSS;
u8 mbdBackMdlPad[8] BSS; /* Unreferenced. */

// masu.c
u16 mbdMasuNum BSS;
u16 mbdMasuLinkNum BSS;
SpaceData *mbdMasuTbl BSS;
LinkData *mbdMasuLinkTbl BSS;
u8 mbdMasuLinkPad[4] BSS; /* Unreferenced. */
MasuBmp *mbdMasuBmpDataTbl[MBD_MASU_TYPE_MAX] BSS;
s16 mbdMasuBmpMode BSS;
u16 mbdMasuDispF BSS;
u8 mbdMasuTypeNumTbl[MBD_MASU_TYPE_MAX] BSS;
event_list_entry *mbdMasuEventBoardStartTbl BSS;
event_list_entry *mbdMasuEventRoundEndTbl BSS;
event_list_entry *mbdMasuEventTurnStartTbl BSS;
event_list_entry *mbdMasuEventTurnTelopTbl BSS;
s32 mbdMasuEventResult BSS;
f32 mbdMasuArrowAngleTbl[8] BSS;
s32 mbdMasuArrowAngleNum BSS;
u8 mbdMasuArrowPad[4] BSS; /* Unreferenced. */
s16 mbdMasuBlockExtTbl[255] BSS;
s16 mbdMasuBlockExtNum BSS;
s16 mbdMasuBlockTbl[16] BSS;
s16 mbdMasuBlockNum BSS;
s16 mbdMasuBlockUnused BSS; /* Unreferenced. */
u8 mbdMasuBlockPad[4] BSS; /* Unreferenced. */
s32 mbdMasuFlagTbl[0x13] BSS;
u8 mbdMasuFlagPad[4] BSS; /* Unreferenced. */
s16 mbdMasuStarTbl[12] BSS;

// pause.c
UnkOvl81_2 *mbdPauseGuide BSS;
s16 mbdPauseStat BSS;
s16 mbdPauseQuitF BSS;
s32 mbdPauseHelpWinL BSS;
s32 mbdPauseHelpWinR BSS;
s16 mbdPauseHelpWinSize[2] BSS;
s16 mbdPauseCursorBlinkF BSS;
s16 mbdPauseUnused BSS; /* Unreferenced. */
u8 mbdPausePad[8] BSS; /* Unreferenced. */

// sprgrp.c
UnkBoard4 *mbdSprGrpListHead BSS;
u16 mbdSprGrpNum BSS;
s16 mbdSprGrpUnused BSS; /* Unreferenced. */
u8 mbdSprGrpPad[8] BSS; /* Unreferenced. */

// status.c
Process *mbdStatusProc BSS;
NameSpriteIds mbdStatusAnim BSS;
s16 mbdVsSprGrp BSS;
s16 mbdVsSprAnim BSS;
f32 mbdVsSprScale BSS;
Vec2f mbdVsSprPos BSS;
Vec2f mbdVsSprVel BSS;
Vec2f mbdVsSprAccel BSS;
s16 mbdVsSprMoveTime BSS;
omObjData *mbdCoinTakeObjTbl[3] BSS;

// partner.c
Object *mbdPartnerObj[MBD_MAX_PLAYERS][PARTNEROBJINDEX_MAX] BSS;
Vec mbdPartnerCameraPos BSS;
u8 mbdPartnerPad[4] BSS; /* Unreferenced. */
s16 mbdPartnerAttackMotTbl[8] BSS;
s16 mbdPartnerExtMotTbl[8] BSS;

// main.c
s32 mbdWalkEventResult BSS;
s16 mbdExitFlag BSS;
s16 mbdExitMusFadeF BSS;
s32 mbdExitOvlNo BSS;
s16 mbdExitOvlEvent BSS;
s16 mbdCameraFocusMode BSS;
Vec mbdCameraFocusStaticPos BSS;
Vec *mbdCameraFocusVec BSS;
UnkE3CD0 *mbdCameraFocusObj BSS;
u8 mbdPlayerFixPad[4] BSS; /* Unreferenced. */
Vec mbdPlayerFixPosTbl[2] BSS;
Vec mbdPartnerFixPosTbl[2][2] BSS;

// scroll.c
omObjData *mbdMapScrollArrowObj BSS;
UnkBoard4 *mbdMapScrollArrow BSS;
s16 mbdMapScrollArrowPos[4][2] BSS;
UnkBoard4 *mbdMapScrollMiniMap BSS;
Process *mbdMapScrollMiniMapProc BSS;
Object *mbdMapScrollMdlTbl[MBD_MAX_PLAYERS] BSS;
f32 mbdMapScrollZoom BSS;
Vec2f mbdMapScrollPos BSS;
u8 mbdMapScrollPad[0xC] BSS; /* Unreferenced. */

// Shared between files.
Vec mbdAttackCameraPos BSS;
s32 mbdCounterResult BSS;
s32 mbdAttackHpDamage BSS;
u8 mbdSaiMode BSS;
u8 mbdSaiDispF BSS;
s32 mbdAttackStarDamage BSS;
s16 mbdDlgWinId BSS;
UnkD6B00 mbdMotShiftTbl[16] BSS;
s32 mbdAttackType BSS;
s16 mbdModelDispFlag BSS;
s32 mbdPartnerUnusedWork BSS;
u8 mbdKakusiWaitF BSS;
NamePlayerData mbdStatusPlayerTbl[2] BSS;
f32 mbdSaiHeight BSS;
s32 mbdAttackOtherIdParam BSS;
u8 mbdSaiReadyF BSS;
s16 mbdWinId BSS;
u8 mbdAttackPad[4] BSS; /* Unreferenced. */
s32 mbdAttackResult BSS;
s32 mbdAttackTargetIdParam BSS;
