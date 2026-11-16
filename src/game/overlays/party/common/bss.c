#define NO_EXTERN_VARIABLES
#include "common_board.h"
#include "game/board.h"
#include "game/gamemes.h"
#include "game/hvq.h"
#include "mapfull.h"
#include "mgcall.h"
#include "back.h"

/*
 * Some halfword arrays in this overlay's BSS are only halfword aligned, which
 * GCC won't produce for standalone arrays. They are grouped into structs here,
 * and the field symbols used by the original code are aliased in
 * undefined_syms.txt.
 */
typedef struct {
    /* 0x00 */ s16 sprGrp;
    /* 0x02 */ s16 sprAnims[2]; // mbTelopPlayerAnim
} SharedBoardBss2D38;

// mapfull.c
s32 mbMapFullBackNo BSS;
s16 mbMapFullIconNum BSS;
UnkBoard6 mbMapFullIconTbl[32] BSS;
s16 mbMapFullPlayerScrXTbl[4] BSS;
s16 mbMapFullPlayerScrYTbl[4] BSS;
UnkBoard8 *mbMapFullLineTbl[4] BSS;
s16 mbMapFullSel BSS;
u8 mbMapFullPad[4] BSS; /* Unreferenced. */

// model.c
Object *mbModelListHead BSS;
u16 mbModelNum BSS;
s16 mbMotionRefTbl[128] BSS;
u8 mbModelPad[8] BSS; /* Unreferenced. */

// com.c
s32 mbComTreePlayerNo BSS;
s32 (*mbComItemDecideHook)(void) BSS;
u8 mbComPad[8] BSS; /* Unreferenced. */

// mgcall.c
ItemSlotEntry mbMgCallSlotTbl[5] BSS; // [0].y is mbMgCallSlotBaseY
omObjData *mbMgCallListObj BSS;
s8 mbMgCallMgList[5] BSS;
s8 mbMgCallType BSS;
s16 mbMgCallBgGrp BSS;
s16 mbMgCallBgAnim BSS;
s16 mbMgCallCursorGrp BSS;
s16 mbMgCallCursorAnim BSS;
u8 mbMgCallPad[8] BSS; /* Unreferenced. */

// coinchange.c
s16 mbCoinChangeGrp[4] BSS;
s16 mbCoinChangeAnimTbl[4][2] BSS;
omObjData *mbCoinChangeObj[4] BSS;
u8 mbCoinChangeFollowF BSS;
u8 mbCoinChangePad[4] BSS; /* Unreferenced. */

// item.c
s16 mbItemWarpPlayerA BSS;
s16 mbItemWarpPlayerB BSS;
u8 mbItemWarpPad[4] BSS; /* Unreferenced. */
void (*MBItemSubFunctions[22])(void) BSS;
s32 mbItemSelComNo BSS;
s32 mbItemScaleEffF BSS;
u8 mbItemPad[8] BSS; /* Unreferenced. */
GAMEMES mbTelopMes BSS;
s16 mbTelopMgTypeStrNo BSS;
u8 mbTelopFlag BSS;
SharedBoardBss2D38 mbTelopPlayerGrp BSS;
omObjData *mbTelopPlayerObj BSS;
omObjData *mbTelopLast5Obj BSS;
s16 mbTelopLast5Grp[2] BSS;
s16 mbTelopLast5Anim[2] BSS;
s32 mbTelopLast5Turn BSS;
Object *mbTelopMgTypeMdl BSS;
s32 mbTelopMgTypeY BSS;
u8 mbTelopPad[4] BSS; /* Unreferenced. */
Vec mbGuideCameraEye BSS;
Vec mbGuideCameraAt BSS;
Vec mbGuideCameraUp BSS;
Vec mbGuideCameraViewSize BSS;
Vec mbGuideCameraViewPos BSS;
u8 mbGuidePad[4] BSS; /* Unreferenced. */

// ksuit.c
s16 mbKoopaMasuId BSS;
u8 mbKoopaPad[0xC] BSS; /* Unreferenced. */

// back.c
u32 mbBackArcAddr BSS;
s32 mbBackArcNum BSS;
s32 mbBackFileAddr BSS;
f32 mbCameraSpeed BSS;
u16 mbBackFlag BSS;
s16 mbBackOfsX BSS;
s16 mbBackOfsY BSS;
s16 mbBackHalfW BSS;
s16 mbBackHalfH BSS;
u8 *mbBackHvqWork BSS;
HvqHeader *mbBackHvqCur BSS;
u8 mbBackHvqPad[4] BSS; /* Unreferenced. */
OverlayBgEntry mbBackTileTbl[36] BSS;
OverlayBgEntry *mbBackTileMap[6][6] BSS;
HvqFileHeader *mbBackHvqFileHdr BSS;
u8 mbBackHvqFilePad[4] BSS; /* Unreferenced. */
OverlayBgEntry mbBackAltTileTbl[36] BSS;
Process *mbCameraUpdateProc BSS;
Process *mbCameraZoomProc BSS;
f32 mbCameraSpeedDiv BSS;
f32 mbBackScale BSS;
Vec mbCameraEye BSS;
Vec mbCameraAt BSS;
Vec mbCameraUp BSS;
Vec mbCameraViewportSize BSS;
Vec mbBackOrigin BSS;
s32 mbBackAltBank BSS;
s32 mbBackAltNo BSS;
UnkFAF78 *mbBackAltTbl BSS;
OSMesgQueue mbBackDmaMesgQ BSS;
OSMesg mbBackDmaMesgBuf[36] BSS;
OSThread mbBackDmaThread BSS;
u64 mbBackDmaStack[0x100] BSS; /* Thread stack, top is mbBackDecodeThread. */
OSThread mbBackDecodeThread BSS;
s32 mbBackThreadPri BSS;
u8 mbBackThreadPad[0xC] BSS; /* Unreferenced. */
u64 mbBackDecodeStack[0x100] BSS; /* Thread stack, top is mbBackDecodeMesgQ. */
OSMesgQueue mbBackDecodeMesgQ BSS;
OSMesg mbBackDecodeMesgBuf[36] BSS;
OSMesgQueue mbBackDoneMesgQ BSS;
OSMesg mbBackDoneMesgBuf[36] BSS;
OSMesgQueue mbBackExitMesgQ BSS;
OSMesg mbBackExitMesgBuf[2] BSS;
Vec2f mbCameraScrTarget BSS;
f32 mbCameraScrPos[2] BSS;
UnkBoard7 mbBackSprTbl[64] BSS;
s32 mbBackSprNum BSS;
u8 mbBackSprPad[0xC] BSS; /* Unreferenced. */
u16 gTotalSpaces BSS;
u16 mbMasuLinkNum BSS;
SpaceData *mbMasuTbl BSS;
LinkData *mbMasuLinkTbl BSS;
u8 mbMasuLinkPad[4] BSS; /* Unreferenced. */
u8 *mbMasuBmpDataTbl[16] BSS;
s16 mbMasuBmpMode BSS;
u16 mbMasuDispF BSS;
u8 mbMasuDispPad[4] BSS; /* Unreferenced. */
u8 mbMasuTypeNumTbl[16] BSS;
void *mbMasuEventBoardStartTbl BSS;
void *mbMasuEventRoundEndTbl BSS;
void *mbMasuEventTurnStartTbl BSS;
void *mbMasuEventTurnTelopTbl BSS;
s32 mbMasuEventResult BSS;
u8 mbMasuEventPad[4] BSS; /* Unreferenced. */
f32 mbMasuArrowAngleTbl[8] BSS;
s32 mbMasuArrowAngleNum BSS;
u8 mbMasuArrowPad[4] BSS; /* Unreferenced. */
s16 mbMasuBlockExtTbl[255] BSS;
s16 mbMasuBlockExtNum BSS;
s16 mbMasuBlockTbl[32] BSS;
s16 mbMasuBlockNum BSS;
u8 mbMasuBlockPad[4] BSS; /* Unreferenced. */
s32 mbMasuFlagTbl[16] BSS;
s16 mbMasuStarTbl[8] BSS;

// pause.c
UnkMBGuideData *mbPauseGuide BSS;
s16 mbPauseStat BSS;
s16 mbPauseQuitF BSS;
s32 mbPauseHelpWinL BSS;
s32 mbPauseHelpWinR BSS;
s16 mbPauseHelpWinSize[2] BSS;
s16 mbPauseCursorBlinkF BSS;
u8 mbPausePad[8] BSS; /* Unreferenced. */

// sprgrp.c
UnkBoard8 *mbSprGrpListHead BSS;
u16 mbSprGrpNum BSS;
u8 mbSprGrpPad[8] BSS; /* Unreferenced. */

// status.c
Process *mbStatusProc BSS;
u8 mbStatusPad[4] BSS; /* Unreferenced. */
s16 mbStatusAnimTbl[29] BSS;
s16 mbVsSprGrp BSS;
s16 mbVsSprAnim BSS;
f32 mbVsSprScale BSS;
Vec2f mbVsSprPos BSS;
Vec2f mbVsSprVel BSS;
Vec2f mbVsSprAccel BSS;
s16 mbVsSprMoveTime BSS;
omObjData *mbCoinTakeObjTbl[4] BSS;
s32 mbMgTypeSoloPlayer BSS;
s16 mbStatusUnusedTbl[4] BSS;
u8 mbStatusUnusedPad[4] BSS; /* Unreferenced. */
s16 mbStatusUnusedTbl2[4][3] BSS;

// itemmasu.c
Object *mbItemMasuNpcMdl BSS;
Object *mbItemMasuCloudMdl BSS;
Object *mbItemMasuBoxMdl BSS;
u8 mbItemMasuPad[4] BSS; /* Unreferenced. */
s32 mbItemMasuGiveTbl[3] BSS; // [1] is mbItemMasuGive1, [2] is mbItemMasuGive2
u8 mbItemMasuGivePad[0x14] BSS; /* Unreferenced. */
f32 mbItemMasuBoxRot BSS;
s32 mbItemMasuKinopioF BSS;
s32 mbItemMasuEff BSS;
s32 mbItemMasuRareItem BSS;

// main.c
s32 mbBoardStartResult BSS;
s16 mbExitFlag BSS;
s16 mbExitMusFadeF BSS;
s32 mbExitOvlNo BSS;
s16 mbExitOvlEvent BSS;
s16 mbCameraFocusMode BSS;
Vec mbCameraFocusStaticPos BSS;
Vec *mbCameraFocusVec BSS;
Vec mbPlayerFixPosTbl[4] BSS;
Object *mbBattleKuriboMdl BSS;
Object *mbBattleKuriboUpperMdl BSS;
omObjData *mbBattleKuriboObj BSS;
u8 mbBattleKuriboPad[4] BSS; /* Unreferenced. */

// scroll.c
omObjData *mbMapScrollArrowObj BSS;
UnkBoard8 *mbMapScrollArrow BSS;
s16 mbMapScrollArrowPos[4][2] BSS;
Object *mbMapScrollMdlTbl[4] BSS;
f32 mbMapScrollZoom BSS;
Vec2f mbMapScrollPos BSS;
u8 mbMapScrollPad[0xC] BSS; /* Unreferenced. */

// Variables shared between files
u8 mbSaiRotDir BSS;
s16 mbDlgWinId BSS;
s8 mbSaiIdleF BSS;
s16 mbModelDispFlag BSS;
f32 mbSaiHeight BSS;
s16 mbItemCursorGrpId BSS;
u8 mbSaiNum BSS;
u8 mbSaiMode BSS;
Object *mbKoopaPosMdl BSS;
s16 mbWinId BSS;
UnkBoard mbMotShiftTbl[16] BSS;
u8 mbSaiDispF BSS;
u8 mbKakusiWaitF BSS;
u8 mbKakusiPad[4] BSS; /* Unreferenced. */
BoardStatus mbStatusData[MB_MAX_PLAYERS] BSS;
s32 mbBackNo BSS;
