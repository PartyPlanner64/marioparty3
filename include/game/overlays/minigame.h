#ifndef _OVL_MINIGAME_H
#define _OVL_MINIGAME_H

#include "ultra64.h"
#include "common_structs.h"
#include "enums.h"
#include "humath.h"
#include "game/object.h"
#include "game/process.h"
#include "game/hu3d.h"
#include "game/hmfcoll.h"

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x08 */ s32 unk08;
} MgMotAttr; // Size 0xC

typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ char unk04[2];
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ f32 unk0C;
} MgMotReq; // Size 0x10

typedef struct {
    /* 0x000 */ char unk00[6];
    u16 unk06;
    /* 0x008 */ f32 unk08;
    /* 0x00C */ f32 unk0C;
    /* 0x010 */ f32 unk10;
    /* 0x014 */ f32 unk14;
    /* 0x018 */ char unk18[9];
    /* 0x021 */ u8 unk21[4];
    /* 0x025 */ char unk25[0xF];
    /* 0x034 */ f32 unk34;
    /* 0x038 */ f32 unk38;
    /* 0x03C */ f32 unk3C;
    /* 0x040 */ f32 unk40;
    /* 0x044 */ f32 unk44;
    /* 0x048 */ f32 unk48;
    /* 0x04C */ f32 unk4C;
    /* 0x050 */ u16 unk50;
    /* 0x052 */ u8 unk52;
    /* 0x053 */ s8 unk53[4];
    /* 0x057 */ s8 unk57;
    /* 0x058 */ u8 unk58;
    /* 0x059 */ s8 unk59;
    /* 0x05A */ u8 unk5A;
    /* 0x05B */ u8 unk5B;
    /* 0x05C */ s32 unk5C;
    /* 0x060 */ f32 unk60;
    /* 0x064 */ f32 unk64;
    /* 0x068 */ f32 unk68;
    /* 0x06C */ f32 unk6C;
    /* 0x070 */ f32 unk70;
    /* 0x074 */ s32 unk74[6];
    /* 0x08C */ f32 unk8C;
    /* 0x090 */ f32 unk90;
    /* 0x094 */ f32 unk94;
    /* 0x098 */ f32 unk98;
    /* 0x09C */ f32 unk9C;
    /* 0x0A0 */ f32 unkA0;
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ union {
        f32 f;
        u16 u16;
    } unkA8;
    /* 0x0AC */ f32 unkAC;
    /* 0x0B0 */ f32 unkB0;
    /* 0x0B4 */ f32 unkB4;
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u16 unkBC;
    /* 0x0BE */ u16 unkBE;
    /* 0x0C0 */ u16 unkC0;
    /* 0x0C2 */ u8 unkC2;
    /* 0x0C3 */ s8 unkC3;
    /* 0x0C4 */ s8 unkC4;
    /* 0x0C5 */ s8 unkC5;
    /* 0x0C6 */ s16 unkC6;
    /* 0x0C8 */ omObjData *unkC8; // Held item object
    /* 0x0CC */ f32 unkCC;
    /* 0x0D0 */ u16 unkD0;
    /* 0x0D2 */ u16 unkD2;
    /* 0x0D4 */ u16 unkD4;
    /* 0x0D6 */ u16 unkD6;
    /* 0x0D8 */ MgMotReq unkD8;
    /* 0x0E8 */ MgMotAttr *unkE8;
    /* 0x0EC */ s32 (*unkEC)(omObjData *, omObjData *);
    /* 0x0F0 */ s16 unkF0;
    /* 0x0F2 */ s8 unkF2[0x12];
    /* 0x104 */ s32 (*unk104[21])();
    /* 0x158 */ void *unk158;
} MgPlayerWork; // Size 0x15C

typedef struct MgItemWork MgItemWork;

// Per-object data (omObjData.data) of the item objects driven by objphys.c.
struct MgItemWork {
    /* 0x00 */ char unk00[0x21];
    /* 0x21 */ u8 unk21[4];
    /* 0x25 */ char unk25[0xF];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ char unk4C[4];
    /* 0x50 */ u16 unk50;
    /* 0x52 */ u8 unk52;
    /* 0x53 */ s8 unk53;
    /* 0x54 */ u8 unk54;
    /* 0x55 */ u8 unk55;
    /* 0x56 */ u16 unk56;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ char unk6C[4];
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ omObjData *unk80; // Object holding this one
    /* 0x84 */ s32 (*unk84[9])(omObjData *);
    /* 0xA8 */ void *unkA8;
}; // Size 0xAC

// Common header of the per-object data of the minigame objects registered in
// mgMapObjTbl.
typedef struct {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ HuMtx4F unk18;
    /* 0x58 */ HuMtx4F unk58;
    /* 0x98 */ f32 unk98;
    /* 0x9C */ f32 unk9C;
    /* 0xA0 */ f32 unkA0;
    /* 0xA4 */ f32 unkA4;
    /* 0xA8 */ f32 unkA8;
    /* 0xAC */ f32 unkAC;
} MgMapWork; // Size >= 0xB0

typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
} MgWallPos; // Size 0xC

// Per-minigame-field work allocated in MgGaugeInit, stored at mgGaugeTbl
typedef struct MgGauge {
    /* 0x00 */ s16 *unk_00;
    /* 0x04 */ s16 *unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u16 unk_16;
} MgGauge; // Size 0x18

// MinigameFlow.state
#define MG_STATE_OPENING 0 // waiting for the wipe, then startDelay frames
#define MG_STATE_START 1   // "Start!" message
#define MG_STATE_PLAY 2
#define MG_STATE_FINISH 3 // "Finish!" message, then finishDelay frames
#define MG_STATE_RESULT 4 // winner announcement, then resultDelay frames
#define MG_STATE_EXIT 5

// MinigameFlow.timerMode
#define MG_TIMER_COUNT_UP 0   // timer counts up to timeLimit
#define MG_TIMER_COUNT_DOWN 1 // timer counts down to 0
#define MG_TIMER_NONE 2

// MinigameFlow.timeDisp
#define MG_TIME_DISP_NONE 0
#define MG_TIME_DISP_RECORD 1    // elapsed time with the saved best record
#define MG_TIME_DISP_COUNTDOWN 2 // seconds left in timer

// MinigameFlow.gauge: layout in the high nibble, segment count in the low nibble.
#define MG_GAUGE_LAYOUT_MASK 0xF0
#define MG_GAUGE_LENGTH_MASK 0x0F
#define MG_GAUGE_NONE 0x00
#define MG_GAUGE_RIGHT_2 0x20   // two gauges stacked on the right
#define MG_GAUGE_TOP_2 0x40     // two gauges along the top
#define MG_GAUGE_CORNERS_4 0x80 // one gauge in each corner

// MinigameFlow.resultType, chooses the announcement in MG_STATE_RESULT.
#define MG_RESULT_WIN_1 0 // winners[0]
#define MG_RESULT_WIN_2 1 // winners[0..1]
#define MG_RESULT_WIN_3 2 // winners[0..2]
#define MG_RESULT_WIN_4 3 // winners[0..3]
#define MG_RESULT_DRAW 4
#define MG_RESULT_GOT_ITEM 5
#define MG_RESULT_GOT_ITEM_ALT 6
#define MG_RESULT_GAME_OVER 7
#define MG_RESULT_LOSER 8
#define MG_RESULT_NONE 9

// Each minigame overlay defines one of these and passes it to
// MgFlowInit, which keeps a pointer in mgFlow.
// MgFlowMain then advances it once per frame through the
// MG_STATE_* sequence. Delays and timers are in frames; -1 disables them
// (a -1 delay waits until the overlay changes state itself).
typedef struct MinigameFlow {
    /* 0x00 */ u8 state;        // MG_STATE_*
    /* 0x01 */ u8 type;         // MINIGAME_TYPE; picks the start/finish messages
    /* 0x02 */ u8 timerMode;    // MG_TIMER_*
    /* 0x03 */ u8 timeDisp;     // MG_TIME_DISP_*
    /* 0x04 */ u8 newRecord;
    /* 0x05 */ u8 gauge;        // MG_GAUGE_*
    /* 0x06 */ u8 resultType;   // MG_RESULT_*
    /* 0x07 */ char unk07;
    /* 0x08 */ f32 gaugeValue[4];
    /* 0x18 */ u8 winners[4];   // player indices for MG_RESULT_WIN_*
    /* 0x1C */ s16 startDelay;
    /* 0x1E */ s16 timer;
    /* 0x20 */ s16 timeLimit;   // also starts the last-30-seconds countdown
    /* 0x22 */ s16 finishDelay;
    /* 0x24 */ s16 resultDelay;
} MinigameFlow; // Size 0x28

typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 radius;
    /* 0x10 */ Vec prev;
} MgHitSphere; // Size 0x1C

// objphys.c
void MgItemObjMain(omObjData *arg0);
f32 MgItemCollide(omObjData *arg0, f32 x, f32 y, f32 z);
void MgItemFloorVelSet(omObjData *arg0, Vec *arg1);
void MgItemTiltSet(omObjData *arg0, Vec *arg1);
void MgItemFloorMoveAdd(MgItemWork *arg0);
void MgItemSpeedDec(omObjData *arg0);
void MgItemDirUpdate(omObjData *arg0);
f32 MgItemFloorCheck(omObjData *arg0, Hu3DSphere *arg1);
void MgItemShadowSet(omObjData *arg0, f32 x, f32 y, f32 z, f32 floorY, Vec *normal);
f32 MgItemFloorGet(omObjData *arg0, Hu3DSphere *arg1, Vec *normal);
void MgItemPlayerPush(omObjData *arg0, f32 x, f32 y, f32 z);
void MgItemWallCheck(omObjData *arg0, Hu3DSphere *arg1);
void MgItemWallReflect(omObjData *arg0);
void MgItemLifeUpdate(omObjData *arg0);
void MgItemCoinGet(omObjData *arg0, omObjData *arg1);
void MgItemInit(omObjData *arg0, s32 arg1);
void MgItemRelease(omObjData *arg0, omObjData *arg1);
void MgItemHookSet(MgItemWork *arg0, s32 arg1, s32 (*arg2)(omObjData *));

// mapcoll.c
f32 MgMapPrimHeightGet(omObjData *arg0, MgPlayerWork *arg1, f32 arg2);
f32 MgMapCeilCheck(omObjData *arg0, MgPlayerWork *arg1, f32 arg2, f32 arg3, Vec *arg4);
f32 MgFaceRayCross(f32 x, f32 y, f32 z, Hu3DPoint *points, Hu3DQuad *quad, Vec *dir, Vec *out);
f32 MgPlayerFloorGet(omObjData *arg0, f32 x, f32 y, f32 z, Vec *normal);
f32 MgPlayerAirMove(omObjData *arg0, f32 x, f32 y, f32 z, f32 prevY);
f32 MgPlayerGroundMove(omObjData *arg0, f32 angle, f32 x, f32 y, f32 z);
f32 MgPlayerSnapYGet(omObjData *arg0, f32 arg1);
s32 MgFaceSideGet(Vec *pos, Hu3DQuad *quad, Hu3DPoint *points);
s32 MgFaceSphereProject(Hu3DSphere *sphere, Hu3DQuad *quad, Hu3DPoint *points);
f32 MgTriCross(f32 x, f32 y, f32 z, Hu3DPoint *p, Hu3DPoint *q, Vec *normal);
s32 MgFaceInsideCheck(Vec *pos, s16 *face, Hu3DPoint *points, Vec *normal);
s32 MgFaceInsideXZCheck(Vec *pos, s16 *face, Hu3DPoint *points);
s32 MgPlayerObjHitCheck(omObjData *arg0, f32 x, f32 y, f32 z);
void MgMoveOfsClamp(omObjData *arg0);
s32 MgFloorFaceFilter(s32 count, s16 *vtx, Hu3DPoint *points, Vec *pos);
s32 MgWallFaceHit(s32 count, s16 *vtx, Hu3DPoint *points, Hu3DSphere *arg3);
s32 MgWallFaceHitEx(s32 count, s16 *vtx, Hu3DPoint *points, MgHitSphere *arg3);
void MgMapBoxBoundsHit(omObjData *arg0, Hu3DSphere *arg1, Vec *arg2);
void MgMapCircleBoundsHit(omObjData *arg0, Hu3DSphere *arg1);
void MgMapCylinderHit(omObjData *arg0, Hu3DSphere *arg1, f32 arg2);
s32 MgMapBlockCornerHit(Hu3DSphere *arg0, MgPlayerWork *data);
void MgMapBlockHit(omObjData *arg0, Hu3DSphere *arg1, Vec *arg2, f32 arg3);
void MgPlayerWallBump(omObjData *obj, Vec *pos, f32 arg2);
s8 MgPlayerWallCheck(omObjData *arg0, Hu3DSphere *arg1, f32 arg2);
void MgPlayerTiltSet(omObjData *obj, Vec *dir);
void MgPlayerPrevPosSet(omObjData *arg0);
void MgPlayerObjMain(omObjData *arg0);
void MgMoveOfsAdd(f32 x, f32 z, f32 scale);
f32 MgPlayerSpeedSnap(f32 arg0);
void MgPlayerSinkStart(omObjData *arg0, f32 x, f32 y, f32 z);
void MgPlayerThrowRelease(omObjData *arg0);
void MgPlayerPunchHit(omObjData *arg0, f32 x, f32 y, f32 z);
void MgWallNorSet(f32 x, f32 y, f32 z);
void MgWallPosSet(f32 arg0, f32 arg1, f32 arg2);
void MgDebugParamExec(omObjData *arg0, s32 arg1);

// player.c
void MgCharMdlCreate(omObjData *arg0, u16 arg1, u16 player, s32 arg3, s32 arg4, f32 arg5);
void MgObjLODMdlCreate(omObjData *arg0, u16 arg1, s32 arg2, s32 arg3, f32 arg4);
void MgPlayerDirSet(omObjData *arg0, f32 arg1);
void MgPlayerSpeedSet(omObjData *arg0, f32 arg1);
void MgPlayerVelYSet(omObjData *arg0, f32 arg1);
void MgPlayerResvSet(omObjData *arg0, f32 arg1);
void MgMapFrictionSet(omObjData *arg0, f32 arg1);
void MgMapAccelSet(omObjData *arg0, f32 arg1);
void MgMapSlideSet(omObjData *arg0, f32 arg1);
void MgPlayerRadiusSet(omObjData *arg0, f32 arg1);
void MgPlayerHeightSet(omObjData *arg0, f32 arg1);
void MgPlayerPunchRadiusSet(omObjData *arg0, f32 arg1);
void MgPlayerAttackParamSet(omObjData *arg0, f32 arg1);
void MgPlayerReachSet(omObjData *arg0, f32 arg1);
void MgPlayerHitRadiusSet(omObjData *arg0, f32 arg1);
void MgMapAttrSet(omObjData *arg0, s32 arg1, f32 arg2);
void MgMapBoxSet(omObjData *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
void MgMapBlockSet(omObjData *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void MgMapCircleSet(omObjData *arg0, f32 arg1, f32 arg2);
void MgMapCylinderSet(omObjData *arg0, f32 arg1, f32 arg2, f32 arg3);
void MgMapMtxStaticOn(omObjData *arg0);
void MgMapMdlMtxOn(omObjData *arg0);
void MgMapNoBumpOn(omObjData *arg0);
void MgMapTiltOn(omObjData *arg0);
void MgMapBaseSet(s32 arg0);
void MgPlayerMapAttrSet(omObjData *arg0, u8 arg1, s8 arg2);
void MgObjMdlDispSet(omObjData *arg0, s32 arg1, s32 arg2);
s32 MgMapBumpCheck(s8 arg0);
void MgObjSprMdlCreate(omObjData *arg0, s32 arg1, s32 arg2, s32 arg3);
void MgObjAnimMdlCreate(omObjData *arg0, u8 arg1, s32 arg2, s32 arg3, char *arg4, s32 arg5);
void MgObjSprCreate(omObjData *arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4);
void MgObjPosSet(omObjData *arg0, f32 x, f32 y, f32 z);
void MgObjRotSet(omObjData *arg0, f32 x, f32 y, f32 z);
void MgObjScaleSet(omObjData *arg0, f32 x, f32 y, f32 z);
void MgFieldStatClear(void);
void MgFieldStatLand(void);
void MgFieldStatEnd(void);
void MgFieldStatStart(void);
void MgFieldStatUpdate(void);
s32 MgMapObjNoGet(s32 arg0);
void MgDummy(void);
void MgPlayerParamReset(void);
void MgCharMdlSet(s32 arg0);
void MgShadowAltSet(s8 arg0);
void MgPlayerSePlay(MgPlayerWork *arg0, s32 arg1);
void MgPlayerSeReq(MgPlayerWork *arg0, s32 arg1);
void MgPlayerSeStopAll(void);
void MgPlayerCreate(omObjData *arg0, u32 arg1, s32 arg2, u16 arg3, s32 arg4, s32 arg5);
void MgPlayerCharAnimCreate(omObjData *arg0, s16 arg1, s16 arg2);
void MgPlayerAnimRead(omObjData *arg0, s32 arg1, s32 arg2);
s32 MgPlayerStickAvgGet(omObjData *arg0, s16 arg1, s16 arg2);
void MgStickClamp(s16 *arg0, s16 *arg1);
void MgPlayerStickReset(omObjData *arg0);
s16 MgStickRotGet(s16 idx, s16 arg1, s8 x, s8 y);
void MgMapMtxUpdate(omObjData *obj);
void MgMapPosLocalGet(HuMtx4F mtx, HuMtx4F result, Vec *pos, omObjData *obj);
void MgMtxDirMult(HuMtx4F mtx, Vec *arg1);
void MgMtxPosMult(HuMtx4F mtx, Vec *arg1);
void MgMtxPosYMult(HuMtx4F mtx, Vec *arg1);
void MgPlayerItemThrow(omObjData *arg0, f32 arg1);
s32 MgPlayerItemHold(omObjData *arg0, omObjData *item);
void MgPlayerItemShapeReset(omObjData *arg0);
f32 MgDirDot(f32 x1, f32 z1, f32 x2, f32 z2);
s32 MgBoundsCheck(HmfModelData_Unk64_Unk60_Struct *obj, Vec *pos);
s32 MgBoundsMarginCheck(HmfModelData_Unk64_Unk60_Struct *obj, Vec *pos, f32 margin);
s32 MgMapAreaCheck(Vec *pos, MgMapWork *data);
void MgPlayerBounce(omObjData *arg0, f32 x, f32 z);
void MgPlayerRepel(MgPlayerWork *arg0, f32 x, f32 z);
void MgPlayerRepelPair(omObjData *arg0, omObjData *arg1);
void MgPlayerHookSet(MgPlayerWork *arg0, s32 index, s32 (*func)());
void MgShadowMdlInit(s16 model);
void MgShadowSlopeSet(s16 model, Vec *normal);

// playermode.c
void MgPlayerJumpStart(omObjData *arg0, MgPlayerWork *arg1);
void MgPlayerActStart(omObjData *arg0, MgPlayerWork *arg1);
void MgPlayerJump(omObjData *arg0, MgPlayerWork *arg1);
void MgPlayerLand(omObjData *arg0, MgPlayerWork *arg1, MgMapWork *arg2, s16 arg3, s16 arg4);
void MgPlayerHipDrop(omObjData *arg0, MgPlayerWork *arg1);
void MgPlayerHipDropLand(omObjData *arg0, MgPlayerWork *arg1, MgMapWork *arg2, f32 arg3, f32 arg4, f32 arg5);
void MgPlayerHipDropEnd(omObjData *arg0, MgPlayerWork *arg1, MgMapWork *arg2, f32 arg3, f32 arg4, f32 arg5);
void MgPlayerAirAttack(omObjData *arg0, MgPlayerWork *arg1);
void MgPlayerAirAttackUpdate(omObjData *arg0, f32 arg1, f32 arg2, f32 arg3);
void MgPlayerAttack(omObjData *arg0, MgPlayerWork *arg1);
void MgPlayerAttackUpdate(omObjData *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
void MgPlayerPoundHit(omObjData *arg0, f32 x, f32 y, f32 z);
void MgPlayerSwingHit(omObjData *arg0, f32 x, f32 y, f32 z);
s32 MgPlayerAttackCheck(omObjData *arg0, omObjData *arg1);
void MgPlayerHit(omObjData *arg0, omObjData *arg1, f32 x, f32 z, u16 arg4);
void MgPlayerCeilHit(omObjData *arg0, f32 arg1);
void MgPlayerShadowSet(omObjData *arg0, f32 x, f32 y, f32 z, f32 groundY, Vec *normal);

// motion.c
s32 MgPlayerMotNoGet(omObjData *arg0);
u32 MgPlayerMotStatGet(omObjData *arg0);
void MgEffMdlUpdate(s32 arg0);
void MgPlayerEffUpdate(omObjData *arg0);
void MgPlayerEffSet(omObjData *arg0, u8 arg1, f32 x, f32 y, f32 z, f32 rotX, f32 rotY);
void MgPlayerShapeApply(omObjData *arg0);
void MgPlayerMotUpdate(omObjData *arg0);
void MgPlayerScaleUpdate(omObjData *arg0);
void MgPlayerSquashSet(omObjData *arg0, u8 arg1);
void MgMotReqSet(MgMotReq *arg0, u16 arg1, u16 arg2, u16 arg3, s16 arg4);
s32 MgPlayerMotCheck(omObjData *arg0, u16 arg1);
s32 MgPlayerWorkMotCheck(MgPlayerWork *arg0, u16 arg1);
s32 MgPlayerMotSet(omObjData *arg0, u16 arg1);
s32 MgPlayerMotForceSet(omObjData *arg0, s32 arg1);
s32 MgPlayerMotShapeStart(omObjData *arg0, u16 arg1, u16 arg2);
void MgPlayerMotCopy(omObjData *arg0, s32 arg1, s32 arg2);
void MgPlayerMotAttrSet(omObjData *arg0, s32 arg1, s16 arg2, s16 arg3);
void MgPlayerMotSwap(omObjData *arg0, s32 arg1, s32 arg2);
void MgPlayerMotRead(omObjData *arg0, u16 arg1, s32 arg2, u16 arg3, u16 arg4);
void MgPlayerMotLoad(omObjData *arg0, u16 arg1, s32 arg2, s32 arg3, u16 arg4);
s16 MgPlayerAnimGet(omObjData *arg0, s32 arg1);
void MgPlayerMotReadEx(omObjData *arg0, u16 arg1, s32 arg2, u16 arg3, u16 arg4, s16 arg5);
void MgPlayerMotLoadEx(omObjData *arg0, u16 arg1, s32 arg2, s32 arg3, u16 arg4, s16 arg5);

// rand.c
u32 MgRandSeedCalc(u32 seed);
u32 MgRand(void);
u32 MgRandMod(u32 max);

// seqman.c
void MgFlowInit(MinigameFlow *flow);
void MgRecordPosSet(s32 arg0, s32 arg1);
void MgRecordPrioSet(s32 arg0);
void MgTimeSprLoad(void);
void MgRecordSprLoad(void);
s16 MgTimeGrpCreate(s32 x, s32 y);
s16 MgRecordGrpCreate(s32 x, s32 y);
void MgTimeDispSet(s16 index, s16 time);
void MgTimeDispZoomSet(s16 index, s16 time);
void MgFlowStartDelaySet(s16 arg0);
void MgFlowTimerSet(s16 arg0);
void MgFlowResultDelaySet(s16 arg0);
void MgFlowTypeSet(s8 arg0);
u8 MgFlowStatGet(void);
u16 MgFlowStatTimeGet(void);
void MgFlowStatSet(u8 arg0);
void MgFlowStatNext(void);
void MgFlowResultWaitSet(s32 arg0);
// Unprototyped: Dorrie Dip passes an object argument that the other callers omit.
u8 MgFlowMain();

// pause.c
void MgStoryStatSprSet(s16 group, s16 member, s16 graphic, s16 prio, s16 x, s16 y);
void MgStoryStatExec(void);
Process *MgStoryStatCreate(u16 arg0, s16 arg1);
s32 MgStoryStatKill(Process *prc);
s16 MgStoryStatModeSet(Process *prc, s16 value);
s16 MgStoryStatModeGet(Process *prc);
void MgStoryStatModeWait(Process *prc, s16 value);
s16 MgStoryRankGet(s16 arg0);
void MgStoryStatViewProc(void);
void MgStoryStageGoto(void);

// score.c
void MgGaugeInit(s16 count, u16 length);
void MgGaugeClose(void);
void MgGaugePosSet(s16 arg0, s16 x, s16 y, s16 arg3);
void MgGaugeRangeSet(s16 arg0, f32 arg1, f32 arg2);
void MgGaugeRateSet(s16 arg0, f32 arg1);
void MgGaugeValueSet(s16 arg0, f32 arg1);
void MgGaugePriSet(s16 arg0, s32 arg1);
void MgGaugeDispOn(s16 arg0);
void MgGaugeDispOff(s16 arg0);
void MgGaugeUpdate(void);

// shadow.c
void MgBoxMdlReset(void);
omObjData *MgBoxObjCreate(s16 prio, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void MgBoxPosSet(omObjData *obj, f32 x, f32 y, f32 z);
void MgBoxRotSet(omObjData *obj, f32 x, f32 y, f32 z);
void MgBoxScaleSet(omObjData *obj, f32 arg1, f32 arg2, f32 arg3);
void MgBoxShadowYSet(omObjData *obj, f32 value);
void MgBoxTargetSet(omObjData *obj, f32 x, f32 y, f32 z);
void MgBoxStatSet(omObjData *obj, s32 value);
s32 MgBoxStatGet(omObjData *obj);
void MgBoxDispSet(omObjData *obj, u16 arg1);
void MgBoxObjInit(omObjData *obj);
void MgBoxObjMain(omObjData *arg0);
s32 MgBoxSparkleUpdate(omObjData *obj);
void MgBoxOpenUpdate(omObjData *obj);
void MgBoxShadowUpdate(omObjData *obj);

#ifndef NO_EXTERN_VARIABLES
extern f32 mgItemFallMax;
extern f32 mgItemGravity;
extern u8 mgPlayerBounceF;
extern s16 mgWallNum;
extern f32 mgPlayerAccel;
extern f32 mgPlayerFriction;
extern f32 mgPlayerJumpPower;
extern f32 mgPlayerGravity;
extern f32 mgPlayerFallMax;
extern f32 mgPlayerFallInit;
extern s16 mgPlayerSeTbl[][14];
extern u16 mgFlowOpeningTime;
extern u16 mgFlowStartTime;
extern u16 mgFlowPlayTime;
extern u16 mgFlowFinishTime;
extern u16 mgFlowResultTime;
extern s16 mgFlowSeqNo;
extern s16 mgFlowSeqTime;
extern s16 mgFlowResultF;
extern MinigameFlow *mgFlow;
extern s32 mgFieldStat;
extern u16 mgMapObjNum;
extern f32 mgMoveOfsX;
extern HuMtx4F mgMapInvMtx;
extern Hu3DQuadPool mgQuadPool;
extern MgWallPos mgWallPosTbl[64];
extern u16 mgItemObjNum;
/* Indexed by mgMapObjNum one slot before mgMapObjTbl, only read
   by the stardust battle overlay. */
extern omObjData *mgMapObjLastTbl[];
extern omObjData *mgMapObjTbl[];
extern HuMtx4F mgMapMtx;
extern u16 mgPlayerObjNum;
extern omObjData *mgPlayerObjTbl[];
extern f32 mgMoveOfsZ;
#endif

#endif
