#include "tick_tock_hop.h"
#include "game/overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/hu3d.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "game/mallocblock.h"
#include "game/hmfcoll.h"
#include "game/camsetup.h"
#include "game/hmfspr.h"

#define PLAYERS_TOTAL 2
#define JUMPS_MAX 99

// camsetup

// hmfspr

// hmfcoll

// 8EFF0

// 8FB20

// pad
extern s8 HuPadStkX[];
extern u16 HuPadBtn[];
extern s8 HuPadStkY[];

// unknown
extern s32 omCharModelNoTbl[][6];
extern u16 omSysExitReq;

// LOCAL

enum {
    FGRP_CAMERA,
    FGRP_MINIGAME,
    FGRP_CLOCK,
    FGRP_PLAYER_1,
    FGRP_PLAYER_2
};

enum {
    MDL_PLATFORM,
    MDL_OBSTACLE,
    MDL_DISK_SMALL,
    MDL_DISK_LARGE
};

enum {
    HAND_PLATFORM,
    HAND_OBSTACLE
};

typedef struct {
    /* 0x00 */ f32 clockHandRot[2];
    /* 0x08 */ f32 clockBaseSpeed[2];
    /* 0x10 */ s16 clockHandModel[2];
    /* 0x14 */ s16 tensSpriteId;
    /* 0x16 */ s16 unitsSpriteId;
    /* 0x18 */ s16 obstacleColliderId;
    /* 0x1A */ s16 obstacleProximityColliderId;
    /* 0x1C */ s16 jumpCount;
    /* 0x1E */ s16 jumpsSinceSpeedChange;
    /* 0x20 */ s16 jumpsForSpeedChange;
    /* 0x24 */ f32 clockSpeedMultiplier;
    /* 0x28 */ s8 finished;
    /* 0x2C */ Work work;
} MinigameData; // Size 0x5C

#define PLAYER_STAT_01 1
#define PLAYER_STAT_JUMPING 2
#define PLAYER_STAT_LOST 8
#define PLAYER_STAT_WON 0x10
#define PLAYER_STAT_FROZEN 0x20
#define PLAYER_STAT_FINISHED (PLAYER_STAT_LOST | PLAYER_STAT_WON)

#define PLAYER_STATE_IDLE 0
#define PLAYER_STATE_WALK 2
#define PLAYER_STATE_JUMP 6
#define PLAYER_STATE_WON 13
#define PLAYER_STATE_KNOCKED 14
#define PLAYER_STATE_LAND 21
#define PLAYER_STATE_LOST 38

typedef struct {
    /* 0x00 */ s16 padId;
    /* 0x02 */ s16 chr;
    /* 0x04 */ s32 stat;
    /* 0x08 */ s8 updateAnimation;
    /* 0x0A */ s16 state;
    /* 0x0C */ s16 nextState;
    /* 0x0E */ char unk0E[0x12];
    /* 0x20 */ s16 resetInputGroupId;
    /* 0x22 */ s16 resetInputId;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char unk26[0x1A];
    /* 0x40 */ ModelTracker *obstacleCollisionTracker;
    /* 0x44 */ ModelTracker *obstacleProximityTracker;
    /* 0x48 */ f32 accelY;
    /* 0x4C */ s16 comReactionDelay;
    /* 0x4E */ s16 comShortJumpBias;
    /* 0x50 */ s16 comFreezeThreshold;
    /* 0x52 */ s16 dustBillId;
    /* 0x54 */ char unk54[8];
} PlayerData; // Size 0x5C

void m257_ObjectSetup(void);
void m257_WorkCreate(void);
void m257_ExitCheckObjMain(omObjData *object);
void m257_ExitObjMain(omObjData *object);
void m257_ExitWaitObjMain(omObjData *object);
void m257_MainObjInit(omObjData *object);
void m257_MainObjMain(omObjData *object);
void m257_ClockObjInit(omObjData *object);
void m257_ClockObjMain(omObjData *object);
void m257_PlayerObjInit(omObjData *object);
void m257_PlayerObjMain(omObjData *object);
void m257_CameraViewInit(FuncGroupContext *groupCtx, FuncContext *ctx);
void m257_FinishCheckUpdate(FuncGroupContext *groupCtx, FuncContext *ctx);
void m257_DrawExec(FuncGroupContext *groupCtx, FuncContext *ctx);
void m257_ClockIntroExec(FuncGroupContext *groupCtx, FuncContext *ctx);
void m257_ClockSpeedUpdate(FuncGroupContext *groupCtx, FuncContext *ctx);
void m257_ClockObstacleRotUpdate(FuncGroupContext *groupCtx, FuncContext *ctx);
void m257_ClockPlatformRotUpdate(FuncGroupContext *groupCtx, FuncContext *ctx);
f32 m257_RandRangeGet(s16 min, s16 max);
void m257_PlayerJumpStartUpdate(FuncGroupContext *groupCtx, FuncContext *ctx);
void m257_PlayerPosUpdate(FuncGroupContext *groupCtx, FuncContext *ctx);
void m257_PlayerRotUpdate(FuncGroupContext *groupCtx, FuncContext *ctx);
void m257_PlayerJumpExec(FuncGroupContext *groupCtx, FuncContext *ctx);
void m257_PlayerHitUpdate(FuncGroupContext *groupCtx, FuncContext *ctx);
void m257_PlayerIntroExec(FuncGroupContext *groupCtx, FuncContext *ctx);
void m257_PlayerWinExec(FuncGroupContext *groupCtx, FuncContext *ctx);
void m257_PlayerKnockExec(FuncGroupContext *groupCtx, FuncContext *ctx);
void m257_PlayerMotUpdate(FuncGroupContext *groupCtx, FuncContext *ctx);
void m257_PlayerStateSet(PlayerData *player, s32 state, s32 updateAnimation);
void m257_PlayerNextStateSet(PlayerData *player, s32 state);
void m257_PlayerComInit(FuncGroupContext *groupCtx, FuncContext *ctx);
void m257_PlayerPadClear(FuncGroupContext *groupCtx, FuncContext *ctx);
void m257_PlayerComInput(FuncGroupContext *groupCtx, FuncContext *ctx);

const s16 m257_startMesTbl[] = {
    0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0x0000
};

const s16 m257_finishMesTbl[] = {
    0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0x0000, 0x0000
};

const s16 m257_drawMesTbl[] = {
    0x8263, 0x8271, 0x8260, 0x8276, 0x0000, 0x0000
};

static MinigameData *m257_gameWork;
static PlayerData *m257_playerTbl;
static s16 m257_playerNoTbl[PLAYERS_TOTAL];
static s16 m257_playerOrderTbl[PLAYERS_TOTAL];

s16 m257_jumpEnableF = TRUE;
s16 m257_startF = FALSE;
s16 m257_musicTimer = 0;
s16 m257_bothWinPhase = 0;
s16 m257_drawPhase = 0;
s16 m257_winPhase = 0;

void m257_Executor(void) {
    m257_ObjectSetup();
}

void m257_ObjectSetup(void) {
    s32 camIndex;

    MapCollInit(50);
    Hu3DSprModelInit(0x30);
    omInitObjMan(50, 0);
    omGameSysInit();
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -56.0f, 50.0f, 56.0f);
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 60.0f, 80.0f, 4000.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    m257_SystemCreate();
    m257_WorkCreate();
    omAddObj(1000, 0, 0, -1, m257_MainObjInit);
    omAddObj(2000, 0, 0, -1, m257_ExitCheckObjMain);
    GMesFontMesCreate(m257_startMesTbl, 1); // gamemes
    GMesFontMesCreate(m257_finishMesTbl, 1);
    GMesFontMesCreate(m257_drawMesTbl, 1);
}

void m257_WorkCreate(void) {
    s16 player1Set = FALSE;
    s16 player2Set = FALSE;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            if (!player1Set) {
                m257_playerNoTbl[0] = i;
                player1Set = TRUE;
            }
        } else if (GwPlayer[i].group == 1) {
            if (!player2Set) {
                m257_playerNoTbl[1] = i;
                player2Set = TRUE;
            }
        }
    }
    m257_gameWork = HuMemAllocTag(sizeof(MinigameData), TAG_OVERLAY);
    memset(m257_gameWork, 0, sizeof(MinigameData));
    m257_playerTbl = HuMemAllocTag(PLAYERS_TOTAL * sizeof(PlayerData), TAG_OVERLAY);
    memset(m257_playerTbl, 0, PLAYERS_TOTAL * sizeof(PlayerData));
}

void m257_ExitCheckObjMain(omObjData *object) {
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        object->func = m257_ExitWaitObjMain;
    }
}

void m257_ExitWaitObjMain(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = m257_ExitObjMain;
    }
}

void m257_ExitObjMain(omObjData *object) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void m257_CameraUpdate(void) {
    if (CRot.x > 360.0f) {
        CRot.x -= 360.0f;
    } else if (CRot.x < 0.0f) {
        CRot.x += 360.0f;
    }
    if (CRot.y > 360.0f) {
        CRot.y -= 360.0f;
    } else if (CRot.y < 0.0f) {
        CRot.y += 360.0f;
    }
    m257_FuncGroupUpdate(FGRP_CAMERA);
}

void m257_MainObjInit(omObjData *object) {
    FuncContext *createCollidersCtx;
    s16 createCollidersId;
    s16 i;

    MgPlayerParamReset();
    MgShadowAltSet(1);
    m257_FuncGroupCreate(NULL, FGRP_CAMERA, 0, 4);
    m257_FuncSet(FGRP_CAMERA, 0, NULL, m257_CameraViewInit, 0);
    object->work[1] = FGRP_MINIGAME;
    m257_FuncGroupCreate(object, object->work[1], 0, 4);
    createCollidersId = m257_FuncSet(object->work[1], 0xFFFF, NULL, m257_ColliderInit, object->work[1]);
    createCollidersCtx = &m257_funcGroupTbl[object->work[1]].funcCtx[createCollidersId];
    createCollidersCtx->func(NULL, createCollidersCtx);
    m257_RandPermCreate(m257_playerOrderTbl, PLAYERS_TOTAL);
    for (i = 0; i < PLAYERS_TOTAL; i++) {
        mgPlayerObjTbl[i] = omAddObj(300, 9, 39, -1, m257_PlayerObjInit);
    }
    mgMapObjTbl[0] = omAddObj(10, 5, 0, -1, m257_ClockObjInit);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    object->func = m257_MainObjMain;
}

void m257_MainObjMain(omObjData *object) {
    m257_FuncGroupUpdate(FGRP_MINIGAME);
    m257_CameraUpdate();
    m257_SprUpdate();
    m257_AnimMdlUpdate();
    m257_BillboardUpdate();
}

void m257_ClockObjInit(omObjData *object) {
    FuncGroupContext *groupCtx;
    s32 var_s4 = 0xB9;
    s32 spriteAttr = 0x4000;
    Quad obstacleQuad = { { { 30.000002f, 0.0f, 100.0f },
                            { -30.000002f, 0.0f, 100.0f },
                            { -30.000002f, 0.0f, 400.0f },
                            { 30.000002f, 0.0f, 400.0f } } };
    Quad obstacleProximityQuad = { { { 90.0f, 0.0f, 100.0f },
                                     { -90.0f, 0.0f, 100.0f },
                                     { -90.0f, 0.0f, 400.0f },
                                     { 90.0f, 0.0f, 400.0f } } };
    f32 starAngle[] = { 35.0f, 60.0f, 120.0f, 145.0f, 215.0f, 240.0f, 300.0f, 325.0f };
    s16 id;
    s16 i;

    groupCtx = m257_FuncGroupCreate(object, FGRP_CLOCK, 5, 16)->groupCtx;
    groupCtx->modelIds[MDL_PLATFORM] = m257_gameWork->clockHandModel[HAND_PLATFORM] = Hu3DModelRead(0x5A0000, var_s4);
    groupCtx->modelIds[MDL_OBSTACLE] = m257_gameWork->clockHandModel[HAND_OBSTACLE] = Hu3DModelRead(0x5A0001, var_s4);
    groupCtx->modelIds[MDL_DISK_SMALL] = Hu3DModelRead(0x5A0002, var_s4);
    groupCtx->modelIds[MDL_DISK_LARGE] = Hu3DModelRead(0x5A0003, var_s4);
    m257_SprDispOn(m257_SprCreate(0xFFFF, 0x5A, 6, 0, spriteAttr), 160, 120);
    for (i = 0; i < 8; i++) {
        f32 starPosX = sindf(starAngle[i]) * 600.0f;
        f32 starPosZ = cosdf(starAngle[i]) * 600.0f;

        if (i % 2 != 0) {
            // Yellow star.
            id = m257_AnimMdlCreate(0x5A, 5, 0.25f, ANIMMDL_ATTR_DISPON, var_s4);
        } else {
            // Red star.
            id = m257_AnimMdlCreate(0x5A, 4, 0.25f, ANIMMDL_ATTR_DISPON, var_s4);
        }
        m257_AnimMdlDispOn(id, starPosX, -25.0f, starPosZ, 0.0f, 0.0f, 0.0f, 0.4f, rand16() % 31);
        Hu3DModelAttrSet(m257_animMdlTbl[id].modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
    m257_gameWork->tensSpriteId = m257_SprCreate(0xF, 0, 0x2D, 0, 0);
    m257_gameWork->unitsSpriteId = id = m257_SprCreate(0xF, 0, 0x2D, 0, 0);
    m257_SprDispOn(id, 280, 32);
    m257_gameWork->clockHandRot[HAND_PLATFORM] = 270.0f;
    m257_gameWork->clockHandRot[HAND_OBSTACLE] = 0.0f;
    Hu3DModelRotSet(groupCtx->modelIds[MDL_PLATFORM], 0.0f, m257_gameWork->clockHandRot[HAND_PLATFORM], 0.0f);
    Hu3DModelRotSet(groupCtx->modelIds[MDL_OBSTACLE], 0.0f, m257_gameWork->clockHandRot[HAND_OBSTACLE], 0.0f);
    Hu3DModelPosSet(groupCtx->modelIds[MDL_PLATFORM], 0.0f, 25.0f, 0.0f);
    Hu3DModelPosSet(groupCtx->modelIds[MDL_OBSTACLE], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(groupCtx->modelIds[MDL_DISK_SMALL], 0.0f, 30.0f, 0.0f);
    Hu3DModelPosSet(groupCtx->modelIds[MDL_DISK_LARGE], 0.0f, -40.0f, 0.0f);
    m257_FuncSet(FGRP_CLOCK, 0xF, NULL, m257_ClockPlatformRotUpdate, 0);
    m257_FuncSet(FGRP_CLOCK, 0xF, NULL, m257_ClockObstacleRotUpdate, 0);
    m257_gameWork->obstacleColliderId = m257_ColliderCreate(groupCtx->modelIds[MDL_PLATFORM], &obstacleQuad, 25.0f, PLAYERS_TOTAL, COLLIDER_ATTR_DISABLED);
    m257_gameWork->obstacleProximityColliderId = m257_ColliderCreate(groupCtx->modelIds[MDL_PLATFORM], &obstacleProximityQuad, 0.0f, PLAYERS_TOTAL, COLLIDER_ATTR_HEIGHT_DISABLED);
    m257_gameWork->clockBaseSpeed[HAND_PLATFORM] = 0.0f;
    m257_gameWork->clockBaseSpeed[HAND_OBSTACLE] = 0.0f;
    m257_gameWork->finished = FALSE;
    object->model[0] = groupCtx->modelIds[MDL_PLATFORM];
    m257_MdlSync(object);
    m257_FuncSet(FGRP_CLOCK, 0, NULL, m257_ClockIntroExec, 0);
    object->func = m257_ClockObjMain;
}

void m257_ClockObjMain(omObjData *object) {
    m257_FuncGroupUpdate(FGRP_CLOCK);
    m257_MdlSync(object);
}

void m257_PlayerObjInit(omObjData *object) {
    PlayerData *player;
    s32 var_a0 = 0x2B9;
    s32 temp_a1;
    s32 temp_a2;

    object->work[0] = mgPlayerObjNum;
    player = &m257_playerTbl[object->work[0]];
    player->chr = GwPlayer[m257_playerNoTbl[object->work[0]]].chr;
    temp_a1 = omCharModelNoTbl[player->chr][0];
    temp_a2 = omCharModelNoTbl[player->chr][1];
    MgPlayerCreate(object, temp_a1, temp_a2, m257_playerNoTbl[object->work[0]], var_a0, var_a0);
    object->model[7] = Hu3DModelRead(8, var_a0);
    Hu3DModelAttrSet(object->model[7], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    player->dustBillId = m257_BillboardCreate(0x57, 0x10, BILL_ATTR_01 | BILL_ATTR_ANIM | BILL_ATTR_DISPOFF);
    MgPlayerMotLoad(object, PLAYER_STATE_IDLE, CharMotionDataNumGet(player->chr, 0), 1, 0);
    MgPlayerMotLoad(object, PLAYER_STATE_WALK, CharMotionDataNumGet(player->chr, 2), 1, 0);
    MgPlayerMotLoad(object, PLAYER_STATE_JUMP, CharMotionDataNumGet(player->chr, 4), 1, 19);
    MgPlayerMotLoad(object, PLAYER_STATE_LAND, CharMotionDataNumGet(player->chr, 0x1F), 1, 999);
    MgPlayerMotLoad(object, PLAYER_STATE_WON, CharMotionDataNumGet(player->chr, 0x30), 1, 999);
    MgPlayerMotLoad(object, PLAYER_STATE_KNOCKED, CharMotionDataNumGet(player->chr, 0x1A), 1, 0);
    MgPlayerMotLoad(object, PLAYER_STATE_LOST, CharMotionDataNumGet(player->chr, 0x36), 1, 999);
    m257_PlayerStateSet(player, PLAYER_STATE_IDLE, TRUE);
    player->nextState = -1;
    player->padId = ((s8 *)object->data)[0x57]; // TODO: figure out type.
    player->stat = PLAYER_STAT_01;
    object->rot.x = object->rot.y = object->rot.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    mgPlayerObjNum++;
    player->obstacleCollisionTracker = m257_ColliderTrackerCreate(m257_gameWork->obstacleColliderId, object->model[0]);
    player->obstacleProximityTracker = m257_ColliderTrackerCreate(m257_gameWork->obstacleProximityColliderId, object->model[0]);
    object->work[1] = FGRP_PLAYER_1 + object->work[0];
    m257_FuncGroupCreate(object, object->work[1], 0, 10);
    player->resetInputGroupId = object->work[1];
    player->resetInputId = m257_FuncSet(object->work[1], 0, player, m257_PlayerPadClear, 0);
    m257_FuncSet(object->work[1], 0xF, player, m257_PlayerJumpStartUpdate, 0);
    m257_FuncSet(object->work[1], 0x1F, player, m257_PlayerPosUpdate, 0);
    m257_FuncSet(object->work[1], 0x1F, player, m257_PlayerRotUpdate, 0);
    m257_FuncSet(object->work[1], 0xEFFF, player, m257_PlayerHitUpdate, 0);
    m257_FuncSet(object->work[1], 0xFFFF, player, m257_PlayerMotUpdate, 0);
    object->func = m257_PlayerObjMain;
}

void m257_PlayerObjMain(omObjData *object) {
    m257_FuncGroupUpdate(object->work[1]);
    MgPlayerMotUpdate(object);
}

void m257_CameraViewInit(FuncGroupContext *groupCtx, FuncContext *ctx) {
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = -137.0f;
    CRot.x = 298.0f;
    CRot.y = 180.0f;
    CRot.z = 0.0f;
    CZoom = 990.0f;
    m257_FuncReset(FGRP_CAMERA, ctx);
}

void m257_JumpCntUpdate(FuncGroupContext *groupCtx, FuncContext *ctx) {
    s16 units = m257_gameWork->jumpCount % 10;
    s16 tens = m257_gameWork->jumpCount * 0.1f;

    if (tens != 0) {
        m257_SprDispOn(m257_gameWork->tensSpriteId, 264, 32);
    } else {
        m257_SprDispOff(m257_gameWork->tensSpriteId);
    }
    HuSprPatNoSet(m257_sprTbl[m257_gameWork->tensSpriteId].groupId, 0, tens);
    HuSprPatNoSet(m257_sprTbl[m257_gameWork->unitsSpriteId].groupId, 0, units);
}

void m257_StartExec(FuncGroupContext *groupCtx, FuncContext *ctx) {
    s16 i;

    if (ctx->state == 0) {
        ctx->work.s16[0] = 0;
        ctx->state = 1;
    }
    ctx->work.s16[0]++;
    switch (ctx->work.s16[0]) {
        case 5:
            GMesCreate(GMES_MES_MG_START);
            HuAudFXPlay(0xE); // plays whistle fx
            m257_musicTimer = 1;
            break;
        case 30:
            m257_startF = TRUE;
            break;
        default:
            if (m257_startF && GMesStatGet() == GMES_STAT_TIMEEND) { // GMES_STAT_TIMEEND?
                m257_jumpEnableF = TRUE;
                m257_gameWork->clockBaseSpeed[HAND_PLATFORM] = 0.0f;
                m257_gameWork->clockBaseSpeed[HAND_OBSTACLE] = 3.0f;
                for (i = 0; i < PLAYERS_TOTAL; i++) {
                    if (GwPlayer[m257_playerNoTbl[i]].stat & PLAYER_IS_CPU) {
                        m257_FuncSet(FGRP_PLAYER_1 + i, 0, &m257_playerTbl[i], m257_PlayerComInit, 0);
                    } else {
                        m257_FuncReset(m257_playerTbl[i].resetInputGroupId, &m257_funcGroupTbl[m257_playerTbl[i].resetInputGroupId].funcCtx[m257_playerTbl[i].resetInputId]);
                    }
                }
                m257_FuncSet(FGRP_MINIGAME, 0, NULL, m257_JumpCntUpdate, 0);
                ctx->func = m257_FinishCheckUpdate;
            }
            break;
    }
    if (m257_musicTimer != 0 && GMesStatGet() != GMES_STAT_NONE) {
        m257_musicTimer++;
        if (m257_musicTimer >= 45) {
            HuAudSeqPlay(0x2F);
            m257_musicTimer = 0;
        }
    }
}

void m257_WipeExitExec(FuncGroupContext *groupCtx, FuncContext *ctx) {
    switch (ctx->state) {
        case 0:
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            ctx->state = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                omOvlReturnEx(1);
            }
            break;
    }
}

void m257_FinishCheckUpdate(FuncGroupContext *groupCtx, FuncContext *ctx) {
    PlayerData *player = m257_playerTbl;
    s16 losers[2] = { -1, -1 };
    s16 loserCount;
    f32 clockObstacleRot;
    f32 clockPlatformRot;
    s16 i;

    if (m257_gameWork->jumpCount == JUMPS_MAX) {
        if (!m257_gameWork->finished) {
            m257_gameWork->finished = TRUE;
        }
        clockObstacleRot = Hu3DData[m257_gameWork->clockHandModel[HAND_OBSTACLE]].rot.y;
        clockPlatformRot = Hu3DData[m257_gameWork->clockHandModel[HAND_PLATFORM]].rot.y;
        m257_AngleDiffMinimize(&clockObstacleRot, &clockPlatformRot);
        if (ABS(clockObstacleRot - clockPlatformRot) > 90.0f) {
            m257_gameWork->clockBaseSpeed[HAND_PLATFORM] = m257_gameWork->clockBaseSpeed[HAND_OBSTACLE] = 0.0f;
            HuAudSeqFadeOut(120);
            GMesCreate(GMES_MES_MG_FINISH);
            m257_FuncSet(FGRP_MINIGAME, 0, NULL, m257_DrawExec, 0);
            for (i = 0; i < PLAYERS_TOTAL; i++) {
                m257_playerTbl[i].stat |= PLAYER_STAT_LOST;
            }
            m257_FuncReset(FGRP_MINIGAME, ctx);
        }
    } else {
        loserCount = 0;
        for (i = 0; i < PLAYERS_TOTAL; i++, player++) {
            if (player->stat & PLAYER_STAT_LOST) {
                losers[loserCount] = i;
                loserCount++;
            }
        }
        if (loserCount == 0) {
            return;
        }
        if (!m257_gameWork->finished) {
            m257_gameWork->finished = TRUE;
        }
        clockObstacleRot = Hu3DData[m257_gameWork->clockHandModel[HAND_OBSTACLE]].rot.y;
        clockPlatformRot = Hu3DData[m257_gameWork->clockHandModel[HAND_PLATFORM]].rot.y;
        m257_AngleDiffMinimize(&clockObstacleRot, &clockPlatformRot);
        if (ABS(clockObstacleRot - clockPlatformRot) > 90.0f) {
            m257_gameWork->clockBaseSpeed[HAND_PLATFORM] = m257_gameWork->clockBaseSpeed[HAND_OBSTACLE] = 0.0f;
            HuAudSeqFadeOut(120);
            GMesCreate(GMES_MES_MG_FINISH);
            if (loserCount == PLAYERS_TOTAL) {
                m257_FuncReset(FGRP_MINIGAME, ctx);
                m257_FuncSet(FGRP_MINIGAME, 0, NULL, m257_DrawExec, 0);
            } else {
                s16 winner = !losers[0];

                m257_playerTbl[winner].stat |= PLAYER_STAT_WON;
                m257_FuncSet(FGRP_PLAYER_1 + winner, 0xFF, &m257_playerTbl[winner], m257_PlayerWinExec, 0);
                m257_FuncReset(FGRP_MINIGAME, ctx);
            }
        }
    }
}

void m257_BothWinExec(FuncGroupContext *groupCtx, FuncContext *ctx) {
    PlayerData *player1 = &m257_playerTbl[0];
    PlayerData *player2 = &m257_playerTbl[1];

    if (ctx->state == 0) {
        ctx->work.s16[0] = 0;
        ctx->state = 1;
    }
    if (m257_bothWinPhase == 0) {
        if (GMesStatGet() == GMES_STAT_NONE) {
            m257_bothWinPhase = 1;
        }
    } else if (m257_bothWinPhase >= 2) {
        if (GMesStatGet() == GMES_STAT_NONE) {
            m257_bothWinPhase = 3;
        }
        if (m257_bothWinPhase == 3) {
            ctx->work.s16[0]++;
            if (ctx->work.s16[0] >= 15) {
                m257_FuncReset(FGRP_MINIGAME, ctx);
                m257_FuncSet(FGRP_MINIGAME, 0, NULL, m257_WipeExitExec, 0);
            }
        }
    } else {
        ctx->work.s16[0]++;
        if (ctx->work.s16[0] == 15) {
            HuAudSeqPlay(0x67);
            m257_PlayerStateSet(player1, PLAYER_STATE_WON, TRUE);
            m257_PlayerStateSet(player2, PLAYER_STATE_WON, TRUE);
            HuAudPlayerFXPlay(0x290 + GwPlayer[m257_playerNoTbl[0]].chr, m257_playerNoTbl[0]);
            HuAudPlayerFXPlay(0x290 + GwPlayer[m257_playerNoTbl[1]].chr, m257_playerNoTbl[1]);
            GMesCreate(GMES_MES_MG_WINNERS_2, player1->chr, player2->chr);
            GwPlayer[m257_playerNoTbl[mgPlayerObjTbl[0]->work[0]]].bonusCoin += 10;
            GwPlayer[m257_playerNoTbl[mgPlayerObjTbl[1]->work[0]]].bonusCoin += 10;
        }
        if (GMesStatGet() != GMES_STAT_NONE) {
            ctx->work.s16[0] = 0;
            m257_bothWinPhase = 2;
        }
    }
}

void m257_DrawExec(FuncGroupContext *groupCtx, FuncContext *ctx) {
    if (ctx->state == 0) {
        ctx->work.s16[0] = 0;
        ctx->state = 1;
    }
    if (m257_drawPhase == 0) {
        if (GMesStatGet() == GMES_STAT_NONE) {
            m257_drawPhase = 1;
        }
    } else if (m257_drawPhase >= 2) {
        if (GMesStatGet() == GMES_STAT_NONE) {
            m257_drawPhase = 3;
        }
        if (m257_drawPhase == 3) {
            ctx->work.s16[0]++;
            if (ctx->work.s16[0] >= 15) {
                m257_FuncReset(FGRP_MINIGAME, ctx);
                m257_FuncSet(FGRP_MINIGAME, 0, NULL, m257_WipeExitExec, 0);
            }
        }
    } else {
        ctx->work.s16[0]++;
        if (ctx->work.s16[0] == 15) {
            m257_PlayerStateSet(&m257_playerTbl[0], PLAYER_STATE_LOST, TRUE);
            m257_PlayerStateSet(&m257_playerTbl[1], PLAYER_STATE_LOST, TRUE);
            GMesCreate(GMES_MES_MG_DRAW);
            HuAudSeqPlay(0x6C);
        }
        if (GMesStatGet() != GMES_STAT_NONE) {
            ctx->work.s16[0] = 0;
            m257_drawPhase = 2;
        }
    }
}

void m257_ClockIntroExec(FuncGroupContext *groupCtx, FuncContext *ctx) {
    s16 i;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.s16[3] = 0;
            for (i = 0; i < PLAYERS_TOTAL; i++) {
                ctx->work.s16[i] = m257_FuncSet(FGRP_PLAYER_1 + i, 0xF, &m257_playerTbl[i], m257_PlayerIntroExec, 0);
            }
            ctx->state = 1;
            break;
        case 1:
            ctx->work.s16[3]++;
            if (ctx->work.s16[3] < 30.0f) {
                return;
            }
            ctx->state = 2;
            HuAudFXPlay(0x4BB);
            ctx->work.s16[4] = HuAudFXPlay(0x4BC);
            HuAudFXPitchSet(ctx->work.s16[4], 0);
            break;
    }
    if (ctx->work.s8[0] == 0) {
        m257_gameWork->clockHandRot[HAND_OBSTACLE] -= 4.0f;
        if (m257_gameWork->clockHandRot[HAND_OBSTACLE] < 0.0f) {
            m257_gameWork->clockHandRot[HAND_OBSTACLE] += 360.0f;
        }
        if (m257_gameWork->clockHandRot[HAND_OBSTACLE] < 180.0f) {
            HuAudFXStop(ctx->work.s16[4]);
            ctx->work.s8[4] = 0;
            ctx->work.s8[0] = 1;
        }
    } else if (++ctx->work.s8[0] >= 11) {
        if (ctx->work.s8[1] == 0) {
            ctx->work.s16[4] = HuAudFXPlay(0x4BC);
            HuAudFXPitchSet(ctx->work.s16[4], 0);
            HuAudFXPlay(0x4BB);
            ctx->work.s8[1] = 1;
        }
        ctx->work.s8[0] = 10;
        m257_gameWork->clockHandRot[HAND_OBSTACLE] += 4.0f;
        if (m257_gameWork->clockHandRot[HAND_OBSTACLE] > 360.0f) {
            m257_FuncSet(FGRP_MINIGAME, 0, NULL, m257_StartExec, 0);
            for (i = 0; i < PLAYERS_TOTAL; i++) {
                m257_FuncReset(FGRP_PLAYER_1 + i, &m257_funcGroupTbl[FGRP_PLAYER_1 + i].funcCtx[ctx->work.s16[i]]);
            }
            m257_jumpEnableF = FALSE;
            m257_colliderTbl[m257_gameWork->obstacleColliderId].attr &= ~COLLIDER_ATTR_DISABLED;
            m257_colliderTbl[m257_gameWork->obstacleColliderId].attr |= COLLIDER_ATTR_ENABLED;
            HuAudFXStop(ctx->work.s16[4]);
            ctx->work.s8[1] = 0;
            ctx->func = m257_ClockSpeedUpdate;
            ctx->state = 0;
        }
    }
}

void m257_ClockSpeedUpdate(FuncGroupContext *groupCtx, FuncContext *ctx) {
    PlayerData *player1 = &m257_playerTbl[0];
    f32 clockObstacleRot;
    f32 clockPlatformRot;
    s16 fxPlayed;

    if (m257_gameWork->finished) {
        return;
    }
    if (ctx->state == 0) {
        ctx->work.s8[0] = FALSE;
        m257_gameWork->clockSpeedMultiplier = 1.0f;
        m257_gameWork->jumpCount = 0;
        m257_gameWork->jumpsSinceSpeedChange = 0;
        m257_gameWork->jumpsForSpeedChange = rand16() % 3 + 1;
        ctx->state = 1;
    }
    if (player1->obstacleProximityTracker->colliding) {
        if (!ctx->work.s8[0]) {
            ctx->work.s8[0] = TRUE;
        }
    } else {
        if (ctx->work.s8[0]) {
            m257_gameWork->jumpsSinceSpeedChange++;
            m257_gameWork->jumpCount++;
            m257_gameWork->clockSpeedMultiplier = 1.0f + m257_gameWork->jumpCount * 0.03f;
        }
        ctx->work.s8[0] = FALSE;
    }
    if (m257_gameWork->jumpsSinceSpeedChange > m257_gameWork->jumpsForSpeedChange) {
        if (!ctx->work.s8[1]) {
            fxPlayed = FALSE;
            ctx->work.s8[1] = TRUE;
            ctx->work.f32[3] = 120 + rand16() % 60;
            switch (rand16() % 3) {
                case 0:
                    if (rand16() & 1) {
                        ctx->work.f32[0] = 0.0f;
                        ctx->work.f32[1] = m257_RandRangeGet(3, 4);
                    } else {
                        ctx->work.f32[0] = m257_RandRangeGet(3, 4);
                        ctx->work.f32[1] = 0.0f;
                    }
                    break;
                case 1:
                    if (rand16() & 1) {
                        if (rand16() & 1) {
                            ctx->work.f32[0] = 3.0f;
                            ctx->work.f32[1] = 1.0f;
                        } else {
                            ctx->work.f32[0] = 1.0f;
                            ctx->work.f32[1] = 3.0f;
                        }
                    } else {
                        if (rand16() & 1) {
                            ctx->work.f32[0] = -3.0f;
                            ctx->work.f32[1] = -1.0f;
                        } else {
                            ctx->work.f32[0] = -1.0f;
                            ctx->work.f32[1] = -3.0f;
                        }
                    }
                    break;
                case 2:
                    ctx->work.f32[0] = m257_RandRangeGet(2, 3);
                    if (ctx->work.f32[0] > 0.0f) {
                        ctx->work.f32[1] = -(f32)(2 + (rand16() & 1));
                    } else {
                        ctx->work.f32[1] = (f32)(2 + (rand16() & 1));
                    }
                    break;
            }
        } else {
            fxPlayed = FALSE;
            clockObstacleRot = Hu3DData[groupCtx->modelIds[MDL_OBSTACLE]].rot.y;
            clockPlatformRot = Hu3DData[groupCtx->modelIds[MDL_PLATFORM]].rot.y;
            m257_AngleDiffMinimize(&clockObstacleRot, &clockPlatformRot);
            if (ABS(clockObstacleRot - clockPlatformRot) > ctx->work.f32[3]) {
                if (m257_gameWork->clockBaseSpeed[HAND_OBSTACLE] > 0.0f) {
                    if (ctx->work.f32[0] < 0.0f) {
                        HuAudFXPlay(0x4BB);
                        fxPlayed = TRUE;
                    }
                } else if (m257_gameWork->clockBaseSpeed[HAND_OBSTACLE] < 0.0f) {
                    if (ctx->work.f32[0] > 0.0f) {
                        HuAudFXPlay(0x4BB);
                        fxPlayed = TRUE;
                    }
                } else {
                    if (ctx->work.f32[0] != 0.0f) {
                        HuAudFXPlay(0x4BB);
                        fxPlayed = TRUE;
                    }
                }
                if (!fxPlayed) {
                    if (m257_gameWork->clockBaseSpeed[HAND_PLATFORM] > 0.0f) {
                        if (ctx->work.f32[1] < 0.0f) {
                            HuAudFXPlay(0x4BB);
                        }
                    } else if (m257_gameWork->clockBaseSpeed[HAND_PLATFORM] < 0.0f) {
                        if (ctx->work.f32[1] > 0.0f) {
                            HuAudFXPlay(0x4BB);
                        }
                    } else {
                        if (ctx->work.f32[1] != 0.0f) {
                            HuAudFXPlay(0x4BB);
                        }
                    }
                }
                m257_gameWork->clockBaseSpeed[HAND_OBSTACLE] = ctx->work.f32[0];
                m257_gameWork->clockBaseSpeed[HAND_PLATFORM] = ctx->work.f32[1];
                ctx->work.s8[1] = FALSE;
                m257_gameWork->jumpsSinceSpeedChange = 0;
                m257_gameWork->jumpsForSpeedChange = 2 + (rand16() & 1);
            }
        }
    }
}

void m257_ClockObstacleRotUpdate(FuncGroupContext *groupCtx, FuncContext *ctx) {
    s32 seNo;
    s16 currSeNo;
    s16 pitch;
    s16 basePitch;

    currSeNo = ctx->work.s16[0];
    m257_gameWork->clockHandRot[HAND_OBSTACLE] += m257_gameWork->clockBaseSpeed[HAND_OBSTACLE] * m257_gameWork->clockSpeedMultiplier;
    if (m257_gameWork->clockHandRot[HAND_OBSTACLE] < 0.0f) {
        m257_gameWork->clockHandRot[HAND_OBSTACLE] += 360.0f;
    } else if (m257_gameWork->clockHandRot[HAND_OBSTACLE] > 360.0f) {
        m257_gameWork->clockHandRot[HAND_OBSTACLE] -= 360.0f;
    }
    Hu3DModelRotSet(groupCtx->modelIds[MDL_PLATFORM], 0.0f, m257_gameWork->clockHandRot[HAND_OBSTACLE], 0.0f);
    if (m257_gameWork->clockBaseSpeed[HAND_OBSTACLE] != 0.0f) {
        if (ctx->work.s8[0] == 0) {
            currSeNo = ctx->work.s16[0] = HuAudFXPlay(0x4BC);
            ctx->work.s8[0] = 1;
        }
        basePitch = m257_gameWork->clockSpeedMultiplier * 150.0f;
        switch ((s16)ABS(m257_gameWork->clockBaseSpeed[HAND_OBSTACLE])) {
            case 1:
                seNo = currSeNo;
                pitch = basePitch;
                HuAudFXPitchSet(seNo, pitch);
                break;
            case 2:
                seNo = currSeNo;
                pitch = basePitch + 150;
                HuAudFXPitchSet(seNo, pitch);
                break;
            case 3:
                seNo = currSeNo;
                pitch = basePitch + 300;
                HuAudFXPitchSet(seNo, pitch);
                break;
            case 4:
                seNo = currSeNo;
                pitch = basePitch + 450;
                HuAudFXPitchSet(seNo, pitch);
                break;
        }
    } else {
        if (ctx->work.s8[0] != 0) {
            HuAudFXStop(currSeNo);
            ctx->work.s8[0] = 0;
        }
    }
}

void m257_ClockPlatformRotUpdate(FuncGroupContext *groupCtx, FuncContext *ctx) {
    s32 seNo;
    s16 currSeNo;
    s16 pitch;
    s16 basePitch;

    currSeNo = ctx->work.s16[0];
    m257_gameWork->clockHandRot[HAND_PLATFORM] += m257_gameWork->clockBaseSpeed[HAND_PLATFORM] * m257_gameWork->clockSpeedMultiplier;
    if (m257_gameWork->clockHandRot[HAND_PLATFORM] < 0.0f) {
        m257_gameWork->clockHandRot[HAND_PLATFORM] += 360.0f;
    } else if (m257_gameWork->clockHandRot[HAND_PLATFORM] > 360.0f) {
        m257_gameWork->clockHandRot[HAND_PLATFORM] -= 360.0f;
    }
    Hu3DModelRotSet(groupCtx->modelIds[MDL_OBSTACLE], 0.0f, m257_gameWork->clockHandRot[HAND_PLATFORM], 0.0f);
    if (m257_gameWork->clockBaseSpeed[HAND_PLATFORM] != 0.0f) {
        if (ctx->work.s8[0] == 0) {
            currSeNo = ctx->work.s16[0] = HuAudFXPlay(0x4BD);
            ctx->work.s8[0] = 1;
        }
        basePitch = m257_gameWork->clockSpeedMultiplier * 150.0f;
        switch ((s16)ABS(m257_gameWork->clockBaseSpeed[HAND_PLATFORM])) {
            case 1:
                seNo = currSeNo;
                pitch = basePitch;
                HuAudFXPitchSet(seNo, pitch);
                break;
            case 2:
                seNo = currSeNo;
                pitch = basePitch + 150;
                HuAudFXPitchSet(seNo, pitch);
                break;
            case 3:
                seNo = currSeNo;
                pitch = basePitch + 300;
                HuAudFXPitchSet(seNo, pitch);
                break;
            case 4:
                seNo = currSeNo;
                pitch = basePitch + 450;
                HuAudFXPitchSet(seNo, pitch);
                break;
        }
    } else {
        if (ctx->work.s8[0] != 0) {
            HuAudFXStop(currSeNo);
            ctx->work.s8[0] = 0;
        }
    }
}

f32 m257_RandRangeGet(s16 min, s16 max) {
    f32 rand;

    rand = rand16() % (max - min + 1) + min;
    if (rand16() & 1) {
        rand = -rand;
    }
    return rand;
}

void m257_PlayerJumpStartUpdate(FuncGroupContext *groupCtx, FuncContext *ctx) {
    PlayerData *player = ctx->data;
    omObjData *object = groupCtx->object;
    FuncContext *playerJumpCtx;
    s16 playerJumpId;

    if (!m257_jumpEnableF) {
        return;
    }
    if (player->stat & PLAYER_STAT_FINISHED) {
        m257_FuncReset(object->work[1], ctx);
        return;
    }
    if (HuPadBtn[player->padId] & A_BUTTON) {
        if (ctx->work.s8[0] == 0 && !(player->stat & PLAYER_STAT_JUMPING) && player->state != PLAYER_STATE_LAND) {
            ctx->work.s8[0] = 1;
            player->stat |= PLAYER_STAT_JUMPING;
            playerJumpId = m257_FuncSet(object->work[1], 0xEFFF, player, m257_PlayerJumpExec, 0);
            playerJumpCtx = &m257_funcGroupTbl[object->work[1]].funcCtx[playerJumpId];
            playerJumpCtx->func(groupCtx, playerJumpCtx);
        }
    } else {
        ctx->work.s8[0] = 0;
    }
}

void m257_PlayerPosUpdate(FuncGroupContext *groupCtx, FuncContext *ctx) {
    PlayerData *player = ctx->data;
    omObjData *object = groupCtx->object;
    f32 clockPlatformRot = m257_gameWork->clockHandRot[HAND_PLATFORM];

    if (player->stat & PLAYER_STAT_LOST) {
        return;
    }
    if (ctx->state == 0) {
        if (m257_playerOrderTbl[object->work[0]] == 0) {
            ctx->work.f32[0] = 185.0f;
            ctx->work.f32[1] = 185.0f;
        } else {
            ctx->work.f32[0] = 315.0f;
            ctx->work.f32[1] = 315.0f;
        }
        ctx->state = 1;
    }
    object->trans.x = sindf(clockPlatformRot) * ctx->work.f32[0];
    object->trans.z = cosdf(clockPlatformRot) * ctx->work.f32[1];
    Hu3DData[object->model[1]].pos.x = object->trans.x;
    Hu3DData[object->model[1]].pos.z = object->trans.z;
    if (ABS(m257_gameWork->clockHandRot[HAND_PLATFORM] - m257_gameWork->clockHandRot[HAND_OBSTACLE]) < 10.0f) {
        Hu3DData[object->model[1]].pos.y = 30.0f;
    } else {
        Hu3DData[object->model[1]].pos.y = 5.0f;
    }
}

void m257_PlayerRotUpdate(FuncGroupContext *groupCtx, FuncContext *ctx) {
    PlayerData *player = ctx->data;
    omObjData *object = groupCtx->object;
    Vec direction;
    Vec origin;
    f32 rotAngles[3];

    if (player->stat & PLAYER_STAT_FINISHED) {
        m257_FuncReset(object->work[1], ctx);
        return;
    }
    if (player->state == PLAYER_STATE_LAND || player->state == PLAYER_STATE_JUMP) {
        return;
    }
    if (HuPadStkX[player->padId] == 0 && HuPadStkY[player->padId] == 0) {
        m257_PlayerStateSet(player, PLAYER_STATE_IDLE, TRUE);
    } else {
        m257_PlayerStateSet(player, PLAYER_STATE_WALK, TRUE);
        direction.x = -HuPadStkX[player->padId];
        direction.y = 0.0f;
        direction.z = HuPadStkY[player->padId];
        origin.x = 0.0f;
        origin.y = 0.0f;
        origin.z = 0.0f;
        m257_PitchYawCalc(origin, direction, rotAngles);
        object->rot.y = rotAngles[1];
    }
}

// TODO: doesn't work with -Wa,--vr4300mul-off.
void m257_PlayerJumpExec(FuncGroupContext *groupCtx, FuncContext *ctx) {
    PlayerData *player = ctx->data;
    omObjData *object = groupCtx->object;
    f32 var_f2;
    f32 accelY;
    f32 scale;

    if (object->trans.y == 0.0f && (player->stat & PLAYER_STAT_LOST)) {
        m257_FuncReset(object->work[1], ctx);
        return;
    }
    if (ctx->state == 0) {
        player->accelY = -1.47f;
        m257_BillboardDispOnRef(player->dustBillId, &object->trans.x, NULL, &object->trans.z);
        m257_PlayerStateSet(player, PLAYER_STATE_JUMP, TRUE);
        CharFXPlay(0x3A, GwPlayer[m257_playerNoTbl[object->work[0]]].chr);
        ctx->state = 1;
    }
    var_f2 = Hu3DMotionShiftTimeGet(object->model[0]);
    if (var_f2 == -1.0f) {
        var_f2 = Hu3DData[object->model[0]].motTime;
    }
    if (var_f2 > 5.0f && var_f2 < 7.0f && !(HuPadBtn[player->padId] & A_BUTTON)) {
        player->accelY = -0.294f;
    }
    accelY = player->accelY;
    if (accelY > 1.7f) {
        accelY = 1.7f;
    }
    object->trans.y += accelY * accelY * (accelY >= 0.0f ? -35.0f : 35.0f);
    player->accelY += 0.15f;
    scale = 1.0f - object->trans.y / 300.0f;
    if (scale > 1.0f) {
        scale = 1.0f;
    } else if (scale < 0.5f) {
        scale = 0.5f;
    }
    Hu3DModelScaleSet(object->model[1], scale, scale, scale);
    if (object->trans.y < 0.0f) {
        object->trans.y = 0.0f;
        player->stat &= ~PLAYER_STAT_JUMPING;
        player->stat |= PLAYER_STAT_01;
        m257_BillboardDispOnRef(player->dustBillId, &object->trans.x, NULL, &object->trans.z);
        CharFXPlay(0x31, GwPlayer[m257_playerNoTbl[object->work[0]]].chr);
        m257_PlayerStateSet(player, PLAYER_STATE_LAND, TRUE);
        m257_PlayerNextStateSet(player, PLAYER_STATE_IDLE);
        m257_FuncReset(object->work[1], ctx);
    }
}

void m257_PlayerHitUpdate(FuncGroupContext *groupCtx, FuncContext *ctx) {
    PlayerData *player = ctx->data;
    omObjData *object = groupCtx->object;

    if ((player->stat & PLAYER_STAT_FINISHED) || m257_gameWork->jumpCount == JUMPS_MAX) {
        return;
    }
    if (player->obstacleCollisionTracker->colliding) {
        Hu3DModelAttrSet(object->model[7], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelPosSet(object->model[7], object->trans.x, 10.0f, object->trans.z);
        m257_PlayerStateSet(player, PLAYER_STATE_KNOCKED, TRUE);
        m257_FuncSet(object->work[1], 0xFF, player, m257_PlayerKnockExec, 0);
        player->stat |= PLAYER_STAT_LOST;
        if (!(GwPlayer[m257_playerNoTbl[object->work[0]]].stat & PLAYER_IS_CPU)) {
            omVibrate(object->work[0], 2, 2, 0x14);
        }
    }
}

void m257_PlayerIntroExec(FuncGroupContext *groupCtx, FuncContext *ctx) {
    PlayerData *player = ctx->data;

    HuPadBtn[player->padId] = 0;
    HuPadStkX[player->padId] = 0;
    HuPadStkY[player->padId] = 0;
    if (player->obstacleProximityTracker->colliding) {
        ctx->work.s8[1] = 1;
        ctx->work.s8[0]++;
        if (ctx->work.s8[0] < 5) {
            HuPadBtn[player->padId] = A_BUTTON;
        }
    } else {
        ctx->work.s8[0] = 0;
        if (ctx->work.s8[1] != 0 && ctx->work.s8[2] == 0) {
            HuPadStkX[player->padId] = sindf(ctx->work.f32[0]) * 70.0f;
            HuPadStkY[player->padId] = cosdf(ctx->work.f32[0]) * 70.0f;
            ctx->work.f32[0] += 10.0f;
            if (ctx->work.f32[0] > 180.0f) {
                ctx->work.f32[0] = 180.0f;
                ctx->work.s8[2] = 1;
            }
        }
    }
}

void m257_PlayerWinExec(FuncGroupContext *groupCtx, FuncContext *ctx) {
    PlayerData *player = ctx->data;
    omObjData *object = groupCtx->object;
    f32 lerpT;

    ctx->work.s16[3]++;
    if (ctx->work.s16[3] < 40) {
        return;
    }
    switch (ctx->state) {
        case 0:
            if (player->state == PLAYER_STATE_IDLE || player->state == PLAYER_STATE_WALK) {
                ctx->work.s16[0] = 0;
                ctx->work.f32[0] = object->rot.y;
                if (object->rot.y != 180.0f) {
                    m257_PlayerStateSet(player, PLAYER_STATE_WALK, TRUE);
                    ctx->state = 1;
                } else {
                    m257_PlayerStateSet(player, PLAYER_STATE_IDLE, TRUE);
                    ctx->state = 2;
                }
            }
            break;
        case 1: // Face the camera.
            lerpT = ctx->work.s16[0] / 10.0f;
            if (lerpT > 1.0f) {
                lerpT = 1.0f;
            }
            object->rot.y = (180.0f - ctx->work.f32[0]) * lerpT + ctx->work.f32[0];
            ctx->work.s16[0]++;
            if (ctx->work.s16[0] >= 11) {
                ctx->work.s16[0] = 0;
                object->rot.y = 180.0f;
                m257_PlayerStateSet(player, PLAYER_STATE_IDLE, TRUE);
                ctx->state = 2;
            }
            break;
        default:
            if (m257_gameWork->jumpCount == JUMPS_MAX) { // Always false?
                m257_FuncSet(FGRP_MINIGAME, 0, NULL, m257_BothWinExec, 0);
                m257_FuncReset(object->work[1], ctx);
                break;
            }
            if (m257_winPhase == 0) {
                if (GMesStatGet() == GMES_STAT_NONE) {
                    m257_winPhase = 1;
                }
            } else if (m257_winPhase >= 2) {
                if (GMesStatGet() == GMES_STAT_NONE) {
                    m257_winPhase = 3;
                }
                if (m257_winPhase == 3) {
                    ctx->work.s16[0]++;
                    if (ctx->work.s16[0] >= 15) {
                        m257_FuncReset(FGRP_MINIGAME, ctx);
                        m257_FuncSet(FGRP_MINIGAME, 0, NULL, m257_WipeExitExec, 0);
                    }
                }
            } else {
                ctx->work.s16[0]++;
                if (ctx->work.s16[0] == 15) {
                    HuAudSeqPlay(0x67);
                    m257_PlayerStateSet(player, PLAYER_STATE_WON, TRUE);
                    GMesCreate(GMES_MES_MG_WINNER, player->chr);
                    GwPlayer[m257_playerNoTbl[object->work[0]]].bonusCoin += 10;
                }
                if (GMesStatGet() != GMES_STAT_NONE) {
                    ctx->work.s16[0] = 0;
                    m257_winPhase = 2;
                }
            }
            break;
    }
}

// TODO: doesn't work with -Wa,--vr4300mul-off.
void m257_PlayerKnockExec(FuncGroupContext *groupCtx, FuncContext *ctx) {
    omObjData *object = groupCtx->object;
    f32 rotDirection;
    f32 scale;
    f32 transY;

    if (ctx->state == 0) {
        if (m257_gameWork->clockBaseSpeed[HAND_OBSTACLE] == 0.0f) {
            if (m257_gameWork->clockBaseSpeed[HAND_PLATFORM] < 0.0f) {
                rotDirection = 1.0f;
            } else {
                rotDirection = -1.0f;
            }
        } else {
            if (m257_gameWork->clockBaseSpeed[HAND_OBSTACLE] < 0.0f) {
                rotDirection = -1.0f;
            } else {
                rotDirection = 1.0f;
            }
        }
        ctx->work.f32[0] = m257_gameWork->clockHandRot[HAND_PLATFORM] + rotDirection * 90.0f;
        while (ctx->work.f32[0] < 0.0f) {
            ctx->work.f32[0] += 360.0f;
        }
        while (ctx->work.f32[0] > 360.0f) {
            ctx->work.f32[0] -= 360.0f;
        }
        ctx->work.f32[1] = ctx->work.f32[2] = sindf(45.0f) * 60.000004f;
        ctx->work.s16[0] = 0;
        HuAudPlayerFXPlay(0x287 + GwPlayer[m257_playerNoTbl[object->work[0]]].chr, m257_playerNoTbl[object->work[0]]);
        HuAudPlayerFXPlay(0x4BE, object->work[0]);
        ctx->state = 1;
    }
    object->trans.y += ctx->work.f32[1];
    ctx->work.f32[1] = ctx->work.f32[2] - ctx->work.s16[0] * 2.45f;
    ctx->work.s16[0]++;
    object->trans.x += sindf(ctx->work.f32[0]) * 20.0f * 5.0f * 0.25f;
    object->trans.z += cosdf(ctx->work.f32[0]) * 20.0f * 5.0f * 0.25f;
    transY = object->trans.y;
    scale = 300.0f;
    scale = 1.0f - transY / scale;
    if (scale > 1.0f) {
        scale = 1.0f;
    } else if (scale < 0.5f) {
        scale = 0.5f;
    }
    Hu3DModelScaleSet(object->model[1], scale, scale, scale);
    Hu3DData[object->model[1]].pos.x = object->trans.x;
    Hu3DData[object->model[1]].pos.z = object->trans.z;
    if (object->trans.y < 10.0f) {
        ctx->work.s16[0] = 0;
        object->trans.y = 10.0f;
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        m257_FuncReset(object->work[1], ctx);
    }
}

void m257_PlayerMotUpdate(FuncGroupContext *groupCtx, FuncContext *ctx) {
    PlayerData *player = ctx->data;
    omObjData *object = groupCtx->object;
    HmfModel *model = &Hu3DData[object->model[0]];

    if (Hu3DMotion[model->motId].unk02 - 1 <= model->motTime) {
        player->updateAnimation = TRUE;
    }
    if (player->updateAnimation) {
        MgPlayerMotSet(object, player->state);
        if (player->state == PLAYER_STATE_WON) {
            HuAudCharVoicePlayPlayer(omCharModelNoTbl[GwPlayer[m257_playerNoTbl[object->work[0]]].chr][0] | 0x30, -1, m257_playerNoTbl[object->work[0]]);
        }
        player->updateAnimation = FALSE;
        if (player->nextState != -1) {
            player->state = player->nextState;
            player->nextState = -1;
        }
    }
}

void m257_PlayerStateSet(PlayerData *player, s32 state, s32 updateAnimation) {
    player->updateAnimation = updateAnimation;
    player->state = state;
}

void m257_PlayerNextStateSet(PlayerData *player, s32 state) {
    player->nextState = state;
}

void m257_PlayerComInit(FuncGroupContext *groupCtx, FuncContext *ctx) {
    PlayerData *player = ctx->data;
    omObjData *object = groupCtx->object;
    Quad obstacleProximityQuad = { { { 90.0f, 0.0f, 100.0f },
                                     { -90.0f, 0.0f, 100.0f },
                                     { -90.0f, 0.0f, 400.0f },
                                     { 90.0f, 0.0f, 400.0f } } };

    switch (GwPlayer[m257_playerNoTbl[object->work[0]]].cpu_difficulty) {
        case 0:
            player->comReactionDelay = 4;
            player->comShortJumpBias = 0;
            player->comFreezeThreshold = 10;
            break;
        case 1:
            player->comReactionDelay = 3;
            player->comShortJumpBias = 2;
            player->comFreezeThreshold = 20;
            break;
        case 2:
            player->comReactionDelay = 1;
            player->comShortJumpBias = 10;
            player->comFreezeThreshold = 30;
            break;
        case 3:
            player->comReactionDelay = 0;
            player->comShortJumpBias = 99;
            player->comFreezeThreshold = 40;
            break;
    }
    m257_ColliderVtxSet(m257_gameWork->obstacleProximityColliderId, &obstacleProximityQuad, 0.0f);
    ctx->func = m257_PlayerComInput;
}

void m257_PlayerPadClear(FuncGroupContext *groupCtx, FuncContext *ctx) {
    PlayerData *player = ctx->data;

    if (player->unk24 != 99) {
        HuPadBtn[player->padId] = 0;
        HuPadStkX[player->padId] = 0;
        HuPadStkY[player->padId] = 0;
    }
}

void m257_PlayerComInput(FuncGroupContext *groupCtx, FuncContext *ctx) {
    PlayerData *player = ctx->data;

    player->unk24 = 99;
    HuPadBtn[player->padId] = 0;
    HuPadStkX[player->padId] = 0;
    HuPadStkY[player->padId] = 0;
    if (player->stat & PLAYER_STAT_FROZEN) {
        return;
    }
    if (ctx->work.s8[0] == 0) {
        if (player->obstacleProximityTracker->colliding) {
            if (m257_gameWork->jumpCount > player->comFreezeThreshold && rand16() % 6 == 0) {
                player->stat |= PLAYER_STAT_FROZEN;
            }
            if (ctx->work.s8[1] == 0) {
                ctx->work.s8[0] = 1;
                ctx->work.s8[1] = 1;
            }
        } else {
            ctx->work.s8[1] = 0;
        }
    }
    if (ctx->work.s8[0] == 1) {
        ctx->work.s16[0]++;
        if (ctx->work.s16[0] > rand16() % (player->comReactionDelay + 1)) {
            ctx->work.s16[0] = 0;
            ctx->work.s8[0] = 2;
            if (rand16() % (player->comShortJumpBias + 1) != 0 && ABS(m257_gameWork->clockBaseSpeed[HAND_PLATFORM] - m257_gameWork->clockBaseSpeed[HAND_OBSTACLE]) > 2.0f) {
                ctx->work.s16[1] = 1;
            } else {
                ctx->work.s16[1] = 6;
            }
        }
    }
    if (ctx->work.s8[0] == 2) {
        ctx->work.s16[0]++;
        if (ctx->work.s16[0] <= ctx->work.s16[1]) {
            HuPadBtn[player->padId] = A_BUTTON;
        } else {
            ctx->work.s16[0] = 0;
            ctx->work.s8[0] = 0;
        }
    }
}
