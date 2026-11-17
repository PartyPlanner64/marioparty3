#include "common.h"
#include "game/mallocblock.h"
#include "game/pause.h"
#include "gcc/memory.h"
#include "game/overlays/minigame.h"

// Per-object work block of the hockey puck objects, reached via ObjData->data
typedef struct IceRinkRiskPuckWork {
    /* 0x00 */ char pad_00[0x34];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ char pad_4C[4];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s8 unk52;
    /* 0x53 */ s8 unk53;
    /* 0x54 */ s8 unk54;
    /* 0x55 */ char pad_55[1];
    /* 0x56 */ u16 unk56; // Puck index
    /* 0x58 */ char pad_58[0x1C];
    /* 0x74 */ f32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ char pad_80[4];
    /* 0x84 */ s32 unk84[9];
    /* 0xA8 */ char pad_A8[4];
} IceRinkRiskPuckWork; // Size 0xAC

// Most recent puck to puck collision, per puck
typedef struct IceRinkRiskPuckHit {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec pos;
} IceRinkRiskPuckHit; // Size 0x14

extern s32 omCharModelNoTbl[][6];
extern u8 omAllPauseF;
extern f32 mgPlayerSpeedMax;
extern omObjData *mgItemObjTbl[];
extern Vec mgWallNorTbl[];

Vec m225_player0StartPos = { -150.0f, 100.0f, -150.0f };
Vec m225_player1StartPos = { -150.0f, 100.0f, 150.0f };
Vec m225_player2StartPos = { 150.0f, 100.0f, -150.0f };
Vec m225_player3StartPos = { 150.0f, 100.0f, 150.0f };
f32 m225_puckStartTbl[4][3] = {
    { 40.0f, 900.0f, 10.0f },
    { 30.0f, 900.0f, 20.0f },
    { 20.0f, 900.0f, 30.0f },
    { 10.0f, 900.0f, 40.0f },
};
IceRinkRiskPuckHit m225_puckHitTbl[3] = {
    { -1, 20, { 0.0f, 0.0f, 0.0f } },
    { -1, 20, { 0.0f, 0.0f, 0.0f } },
    { -1, 20, { 0.0f, 0.0f, 0.0f } },
};
s32 m225_puckActiveTbl[3] = { 0, 0, 0 };
s32 m225_puckNum = 0;
s32 m225_playerAliveTbl[4] = { 1, 1, 1, 1 };
MinigameFlow m225_mgFlow = {
    MG_STATE_OPENING, MINIGAME_4P, MG_TIMER_COUNT_DOWN, MG_TIME_DISP_COUNTDOWN, FALSE, MG_GAUGE_NONE, MG_RESULT_WIN_1, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    60, 900, -1, 75, 135
};
s32 m225_puckDispF = 1;
s32 m225_timer = 0;
s32 m225_playerFlyTimeTbl[4] = { 0, 0, 0, 0 };
s32 m225_playerOutTbl[4] = { 0, 0, 0, 0 };
s8 m225_comStickTbl[4][2] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };
f32 m225_comStickScaleTbl[4] = { 0.75f, 0.8f, 0.9f, 1.0f };
f32 m225_comDodgeDistTbl[4] = { 30.0f, 20.0f, 10.0f, 0.0f };
s32 m225_puckCreateCnt = 0;
f32 m225_puckRotTbl[10] = { 0 };

Vec m225_cameraViewPos BSS;
Vec m225_cameraViewTarget BSS;
s32 m225_comBtnSave BSS;
s32 m225_comBtnDownSave BSS;
s32 m225_comStickXSave BSS;
s32 m225_comStickYSave BSS;

void m225_ExitObjMain(omObjData *object);
void m225_PuckStart(void);
void m225_PuckEndAll(void);
void m225_HitEffUpdate(omObjData *object);
void m225_MainObjMain(omObjData *object);
void m225_MapObjInit(omObjData *object);
void m225_PlayerInit(omObjData *object, s32 model, s32 motion, s32 player);
s32 m225_PlayerHitHook(omObjData *object, omObjData *other);
void m225_PlayerFlyObjMain(omObjData *object);
s32 m225_PlayerPadRestore(omObjData *object);
s32 m225_PlayerComInput(omObjData *object);
void m225_Player0ObjInit(omObjData *object);
void m225_Player1ObjInit(omObjData *object);
void m225_Player2ObjInit(omObjData *object);
void m225_Player3ObjInit(omObjData *object);
void m225_PuckObjInit(omObjData *object);
void m225_PuckObjMain(omObjData *object);
f32 m225_PuckCollide(omObjData *object, f32 x, f32 y, f32 z);
f32 m225_PuckFloorCheck(omObjData *object, Hu3DSphere *sphere);
void m225_PuckShadowSet(omObjData *object, f32 x, f32 y, f32 z, f32 floorY, Vec *normal);
f32 m225_PuckFloorGet(omObjData *object, Hu3DSphere *sphere, Vec *normal);
void m225_PuckHitCheck(omObjData *object, f32 x, f32 y, f32 z);
void m225_PuckWallCheck(omObjData *object, Hu3DSphere *sphere);
void m225_PuckWallReflect(omObjData *object);
void m225_PuckHitReflect(omObjData *object, f32 dx, f32 dz);

void m225_ObjectSetup(void) {
    u8 camIndex;
    s16 sprite;

    MapCollInit(50);
    Hu3DQuadPoolInit(&mgQuadPool, 0x40);
    Hu3DSprModelInit(32);
    omInitObjMan(50, 0);
    omGameSysInit();
    MgFieldStatClear();
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 41.539f, 80.0f, 13000.0f);
    Hu3DGLightDirSet(1, -79.0f, -10.0f, 89.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    MgPlayerParamReset();
    MgShadowAltSet(1);
    mgPlayerFallInit = 0.0f;
    MgMapBaseSet(mgMapObjNum);
    mgMapObjTbl[mgMapObjNum++] = omAddObj(1, 10, 0, -1, m225_MapObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(3, 10, 60, -1, m225_Player0ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(3, 10, 60, -1, m225_Player1ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(3, 10, 60, -1, m225_Player2ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(3, 10, 60, -1, m225_Player3ObjInit);
    mgItemObjTbl[mgItemObjNum++] = omAddObj(2, 4, 0, -1, m225_PuckObjInit);
    mgItemObjTbl[mgItemObjNum++] = omAddObj(2, 4, 0, -1, m225_PuckObjInit);
    mgItemObjTbl[mgItemObjNum++] = omAddObj(2, 4, 0, -1, m225_PuckObjInit);
    m225_cameraViewTarget.x = 0.0f;
    m225_cameraViewTarget.y = 18.995f;
    m225_cameraViewTarget.z = -31.245f;
    m225_cameraViewPos.x = 0.0f;
    m225_cameraViewPos.y = 1100.0f;
    m225_cameraViewPos.z = 710.785f;
    sprite = espEntry(HuSprAnimDataRead(0x3A0003), 0, 1);
    espDispOn(sprite);
    espPosSet(sprite, 160, 120);
    espAttrSet(sprite, 0x4000);
    omCameraViewCreate(100, sprite, NULL, 41.539f, &m225_cameraViewPos, &m225_cameraViewTarget);
    CZoom *= 1.25f;
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
    MgFlowInit(&m225_mgFlow);
    mgFlowSeqNo = 53;
    mgFlowSeqTime = 20;
}

void m225_ExitObjMain(omObjData *object) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

void m225_PuckStart(void) {
    m225_puckActiveTbl[m225_puckNum] = 1;
    m225_puckNum++;
    HuAudFXPlay(0x3D3);
}

void m225_PuckEndAll(void) {
    omObjData *puck;
    s32 i;

    for (i = 0; i < m225_puckNum; i++) {
        puck = mgItemObjTbl[i];
        Hu3DModelAttrSet(puck->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionTimeSet(puck->model[2], 0);
        Hu3DModelPosSet(puck->model[2], puck->trans.x, puck->trans.y, puck->trans.z);
        Hu3DModelScaleSet(puck->model[2], 1.2f, 1.2f, 1.2f);
        Hu3DModelAttrSet(puck->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(puck->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        puck->func = NULL;
    }
    m225_puckDispF = 0;
}

void m225_HitEffUpdate(omObjData *object) {
    s32 hidden;
    s32 i;
    s32 j;

    for (i = 0; i < 3; i++) {
        if (m225_puckHitTbl[i].unk04 == 0) {
            hidden = FALSE;
            for (j = 0; j < 3; j++) {
                if (j != i && m225_puckHitTbl[j].unk00 == i) {
                    if (m225_puckHitTbl[i].unk04 == m225_puckHitTbl[j].unk04) {
                        m225_puckHitTbl[j].unk04 = 5;
                        m225_puckHitTbl[j].unk00 = -1;
                    } else {
                        hidden = TRUE;
                    }
                }
            }
            if (!hidden) {
                Hu3DModelAttrSet(object->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelPosSet(object->model[i + 1], m225_puckHitTbl[i].pos.x,
                                m225_puckHitTbl[i].pos.y, m225_puckHitTbl[i].pos.z);
                Hu3DMotionTimeSet(object->model[i + 1], 0);
            }
            m225_puckHitTbl[i].unk04++;
        } else {
            m225_puckHitTbl[i].unk04++;
            if (m225_puckHitTbl[i].unk04 >= 16) {
                m225_puckHitTbl[i].unk00 = -1;
            }
        }
    }
}

void m225_MainObjMain(omObjData *object) {
    MgPlayerWork *data;
    omObjData *obj;
    s32 count = 0;
    u16 time;
    s32 i;
    s32 j;

    if (omPauseChk() + omAllPauseF != 0) {
        return;
    }
    for (i = 0; i < 4; i++) {
        if (m225_playerAliveTbl[i] == 1) {
            count += m225_playerAliveTbl[i];
        }
    }
    time = MgFlowStatTimeGet();
    switch (MgFlowMain()) {
        case 0:
            if (time == 5) {
                HuAudFXPlay(0x3D5);
            }
            break;
        case 1:
            break;
        case 2:
            m225_HitEffUpdate(object);
            switch (m225_timer) {
                case 0:
                case 300:
                case 600:
                    m225_PuckStart();
                    break;
            }
            if (count < 2) {
                MgFlowStatSet(MG_STATE_FINISH);
            }
            m225_timer++;
            break;
        case 3:
            if (m225_puckDispF == 1) {
                m225_PuckEndAll();
            }
            if (count == 0) {
                m225_mgFlow.resultType = MG_RESULT_DRAW;
            } else {
                m225_mgFlow.resultType = count - 1;
                for (j = 0, i = 0; i < 4; i++) {
                    if (m225_playerAliveTbl[i] == 1) {
                        m225_mgFlow.winners[j++] = i;
                    }
                }
            }
            for (i = 0; i < 4; i++) {
                if (m225_playerAliveTbl[i] == 1) {
                    obj = mgPlayerObjTbl[i];
                    OM_GET_DATA_PTR(obj, MgPlayerWork)->unk3C *= 0.8f;
                }
            }
            break;
        case 4:
            if (mgFlowResultF == 1) {
                for (i = 0; i < 4; i++) {
                    if (m225_playerAliveTbl[i] == 1) {
                        obj = mgPlayerObjTbl[i];
                        data = obj->data;
                        MgPlayerMotForceSet(obj, 0xD);
                        GwPlayer[data->unk59].bonusCoin += 10;
                        HuAudCharVoicePlay(omCharModelNoTbl[GwPlayer[data->unk59].chr][0] | 0x2F);
                    }
                }
            }
            break;
        case 5:
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            object->func = m225_ExitObjMain;
            break;
    }
    for (i = 0; i < mgPlayerObjNum; i++) {
        OM_GET_DATA_PTR(mgPlayerObjTbl[i], MgPlayerWork)->unk60 = CRot.y;
    }
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
        object->func = m225_ExitObjMain;
    }
}

void m225_MapObjInit(omObjData *object) {
    MgMapWork *work;

    mgPlayerAccel = 20.0f;
    object->model[0] = Hu3DModelRead2(0x3A0001, 0x80019);
    object->model[1] = Hu3DModelRead(8, 0x88D);
    object->model[2] = Hu3DModelRead(8, 0x88D);
    object->model[3] = Hu3DModelRead(8, 0x88D);
    object->trans.x = 0.0f;
    object->trans.y = 0.0f;
    object->trans.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    object->func = m225_MainObjMain;
    work->unk03 = 1;
    MgMapTiltOn(object);
    MgMapCircleSet(object, 100.0f, 500.0f);
    MgMapFrictionSet(object, 0.1f);
    MgMapAccelSet(object, mgPlayerAccel);
    MgMapSlideSet(object, 25.0f);
    MgMapNoBumpOn(object);
    work->unk04 = 0;
    object->scale.x = object->scale.z = 1.25f;
    Hu3DModelScaleSet(object->model[1], 0.75f, 0.75f, 0.75f);
    Hu3DModelScaleSet(object->model[2], 0.75f, 0.75f, 0.75f);
    Hu3DModelScaleSet(object->model[3], 0.75f, 0.75f, 0.75f);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void m225_PlayerInit(omObjData *object, s32 model, s32 motion, s32 player) {
    MgPlayerWork *data;
    s32 chr;

    MgPlayerCreate(object, model, motion, player, 0xA99, 0xA99);
    data = object->data;
    chr = GwPlayer[data->unk59].chr;
    object->model[3] = Hu3DModelRead(3, 0x88D);
    object->model[4] = Hu3DModelRead(4, 0x88D);
    object->model[5] = Hu3DModelRead(6, 0x88D);
    object->model[7] = Hu3DModelRead(8, 0x88D);
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(chr, 0), 1, 0);
    MgPlayerMotLoad(object, 1, CharMotionDataNumGet(chr, 1), 1, 0);
    MgPlayerMotLoad(object, 2, CharMotionDataNumGet(chr, 2), 1, 0);
    MgPlayerMotLoad(object, 6, CharMotionDataNumGet(chr, 4), 1, 0x13);
    MgPlayerMotLoad(object, 9, CharMotionDataNumGet(chr, 7), 1, 0x27);
    MgPlayerMotLoad(object, 0x11, CharMotionDataNumGet(chr, 0xE), 1, 0xF);
    MgPlayerMotLoad(object, 0xA, CharMotionDataNumGet(chr, 0x11), 1, 0x27);
    MgPlayerMotLoad(object, 0x15, CharMotionDataNumGet(chr, 0x1F), 0, 0);
    MgPlayerMotLoad(object, 3, CharMotionDataNumGet(chr, 0x1D), 1, 0);
    MgPlayerMotLoad(object, 4, CharMotionDataNumGet(chr, 0x1E), 1, 0);
    MgPlayerMotLoad(object, 0x1E, CharMotionDataNumGet(chr, 0x20), 2, 0);
    MgPlayerMotLoad(object, 0x1F, CharMotionDataNumGet(chr, 0x21), 2, 0);
    MgPlayerMotLoad(object, 0x20, CharMotionDataNumGet(chr, 0x22), 0, 0);
    MgPlayerMotLoad(object, 0x26, CharMotionDataNumGet(chr, 0x1A), 1, 0);
    MgPlayerMotRead(object, 0xD, CharMotionDataNumGet(chr, 0x2F), 1, 0x78);
    MgPlayerMotRead(object, 0xE, CharMotionDataNumGet(chr, 0x36), 1, 0x78);
    data->unkEC = m225_PlayerHitHook;
    MgPlayerMapAttrSet(object, 0, 2);
    MgPlayerHookSet(data, 0, m225_PlayerComInput);
    MgPlayerHookSet(data, 1, m225_PlayerPadRestore);
}

s32 m225_PlayerHitHook(omObjData *object, omObjData *other) {
    MgPlayerWork *data = object->data;
    Vec dir;
    f32 x, y, z;
    f32 half;

    if (MgFlowStatGet() != MG_STATE_PLAY) {
        return 1;
    }
    x = object->trans.x;
    y = object->trans.y;
    z = object->trans.z;
    dir.x = x - other->trans.x;
    dir.y = object->trans.y - other->trans.y;
    dir.z = object->trans.z - other->trans.z;
    half = HuSqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z) * 0.5f;
    MapVecNormalize(&dir);
    x += half * dir.x;
    y += half * dir.y;
    z += half * dir.z;
    HuAudPlayerFXPlay(0x3D4, data->unk59);
    PlayerFXPlay(0x286, data->unk59);
    MgPlayerMotForceSet(object, 0x26);
    data->unk38 = -mgPlayerJumpPower;
    data->unk3C = atan2df(object->trans.x, object->trans.z);
    data->unk40 = mgPlayerSpeedMax * 0.8f;
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    MgPlayerEffSet(object, 7, x, y, z, 0.0f, 0.0f);
    m225_playerAliveTbl[data->unk59] = 0;
    object->func = m225_PlayerFlyObjMain;
    data->unk50 |= 0x400;
    m225_playerOutTbl[data->unk59] = 1;
    omVibrate(data->unk59, 2, 2, 20);
    return 1;
}

void m225_PlayerFlyObjMain(omObjData *object) {
    MgPlayerWork *data = object->data;
    f32 x = object->trans.x;
    f32 y = object->trans.y;
    f32 z = object->trans.z;
    f32 velocity;
    f32 speedSq;

    if (m225_playerFlyTimeTbl[data->unk59] == 0 && data->unk38 != -mgPlayerJumpPower) {
        data->unk38 = -mgPlayerJumpPower;
    }
    velocity = data->unk38;
    if (velocity > mgPlayerFallMax) {
        velocity = mgPlayerFallMax;
    }
    speedSq = velocity * velocity;
    if (data->unk38 >= 0.0f) {
        y += speedSq * -35.0f;
    } else {
        y += speedSq * 35.0f;
    }
    data->unk38 += mgPlayerGravity * 0.5f;
    x += sindf(data->unk3C) * data->unk40;
    z += cosdf(data->unk3C) * data->unk40;
    if (HuSqrtf(x * x + y * y + z * z) > 2000.0f) {
        object->func = NULL;
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    m225_playerFlyTimeTbl[data->unk59]++;
    object->trans.x = x;
    object->trans.y = y;
    object->trans.z = z;
}

s32 m225_PlayerPadRestore(omObjData *object) {
    MgPlayerWork *data = object->data;

    if (GwPlayer[data->unk59].stat & 1) {
        HuPadBtnDown[data->unk57] = m225_comBtnDownSave;
        HuPadBtn[data->unk57] = m225_comBtnSave;
        HuPadStkX[data->unk57] = m225_comStickXSave;
        HuPadStkY[data->unk57] = m225_comStickYSave;
    }
    if (object->trans.y < -2000.0f) {
        object->func = NULL;
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    if (m225_playerOutTbl[data->unk59] == 1) {
        MgPlayerMotForceSet(object, 0x26);
        data->unk38 = -mgPlayerJumpPower;
        data->unk3C = atan2df(object->trans.x, object->trans.z);
        data->unk40 = mgPlayerSpeedMax * 0.8f;
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        m225_playerAliveTbl[data->unk59] = 0;
        object->func = m225_PlayerFlyObjMain;
        data->unk50 |= 0x400;
    }
    return 1;
}

s32 m225_PlayerComInput(omObjData *object) {
    MgPlayerWork *data = object->data;
    omObjData *puck;
    Vec dir;
    s32 player = data->unk59;
    s32 pad = data->unk57;
    s32 difficulty;
    s32 best;
    s32 i;
    f32 bestDist;
    f32 dist;
    f32 plusDist;
    f32 angle;
    f32 dx, dy, dz;

    if (MgFlowStatGet() == MG_STATE_PLAY && !(GwPlayer[player].stat & 1)) {
        return 1;
    }
    m225_comBtnDownSave = HuPadBtnDown[pad];
    m225_comBtnSave = (u16)HuPadBtn[pad];
    m225_comStickXSave = HuPadStkX[pad];
    m225_comStickYSave = HuPadStkY[pad];
    HuPadStkY[pad] = 0;
    HuPadStkX[pad] = 0;
    HuPadBtnDown[pad] = 0;
    HuPadBtn[pad] = 0;
    difficulty = GwPlayer[data->unk59].cpu_difficulty;
    if (data->unk38 != 1000.0f) {
        HuPadStkX[pad] = m225_comStickTbl[player][0];
        HuPadStkY[pad] = m225_comStickTbl[player][1];
        HuPadBtn[pad] |= A_BUTTON;
    } else {
        bestDist = 20000.0f;
        best = -1;
        for (i = 0; i < m225_puckNum; i++) {
            puck = mgItemObjTbl[i];
            dx = object->trans.x - puck->trans.x;
            dy = object->trans.y - puck->trans.y;
            dz = object->trans.z - puck->trans.z;
            dist = HuSqrtf(dx * dx + dy * dy + dz * dz);
            if (dist < bestDist) {
                bestDist = dist;
                best = i;
            }
        }
        if (bestDist < m225_comDodgeDistTbl[difficulty] + 150.0f) {
            puck = mgItemObjTbl[best];
            dir.x = object->trans.x - puck->trans.x;
            dir.y = 0.0f;
            dir.z = object->trans.z - puck->trans.z;
            MapVecNormalize(&dir);
            HuPadStkX[pad] = dir.x * 60.0f * m225_comStickScaleTbl[difficulty];
            HuPadStkY[pad] = dir.z * -60.0f * m225_comStickScaleTbl[difficulty];
            HuPadBtnDown[pad] |= A_BUTTON;
        } else if (bestDist < 400.0f) {
            puck = mgItemObjTbl[best];
            dx = object->trans.x;
            dz = object->trans.z;
            dist = HuSqrtf(dx * dx + dz * dz);
            angle = atan2df(dx, dz);
            dx = sindf(angle + 10.0f) * dist - puck->trans.x;
            dz = cosdf(angle + 10.0f) * dist - puck->trans.z;
            plusDist = HuSqrtf(dx * dx + dz * dz);
            dx = sindf(angle - 10.0f) * dist - puck->trans.x;
            dz = cosdf(angle - 10.0f) * dist - puck->trans.z;
            if (HuSqrtf(dx * dx + dz * dz) < plusDist) {
                dx = sindf(angle + 10.0f) * dist;
                dz = cosdf(angle + 10.0f) * dist;
            } else {
                dx = sindf(angle - 10.0f) * dist;
                dz = cosdf(angle - 10.0f) * dist;
            }
            dir.x = dx - object->trans.x;
            dir.y = 0.0f;
            dir.z = dz - object->trans.z;
            MapVecNormalize(&dir);
            HuPadStkX[pad] = dir.x * 60.0f * m225_comStickScaleTbl[difficulty];
            HuPadStkY[pad] = dir.z * -60.0f * m225_comStickScaleTbl[difficulty];
        } else {
            dx = object->trans.x;
            dz = object->trans.z;
            if (HuSqrtf(dx * dx + dz * dz) > 350.0f) {
                dir.x = -object->trans.x;
                dir.y = 0.0f;
                dir.z = -object->trans.z;
                MapVecNormalize(&dir);
                HuPadStkX[pad] = dir.x * 60.0f * m225_comStickScaleTbl[difficulty];
                HuPadStkY[pad] = dir.z * -60.0f * m225_comStickScaleTbl[difficulty];
            }
        }
    }
    m225_comStickTbl[player][0] = HuPadStkX[pad];
    m225_comStickTbl[player][1] = HuPadStkY[pad];
    return 1;
}

void m225_Player0ObjInit(omObjData *object) {
    m225_PlayerInit(object, omCharModelNoTbl[GwPlayer[0].chr][0], omCharModelNoTbl[GwPlayer[0].chr][2], 0);
    object->trans.x = m225_player0StartPos.x;
    object->trans.y = m225_player0StartPos.y;
    object->trans.z = m225_player0StartPos.z;
}

void m225_Player1ObjInit(omObjData *object) {
    m225_PlayerInit(object, omCharModelNoTbl[GwPlayer[1].chr][0], omCharModelNoTbl[GwPlayer[1].chr][2], 1);
    object->trans.x = m225_player1StartPos.x;
    object->trans.y = m225_player1StartPos.y;
    object->trans.z = m225_player1StartPos.z;
}

void m225_Player2ObjInit(omObjData *object) {
    m225_PlayerInit(object, omCharModelNoTbl[GwPlayer[2].chr][0], omCharModelNoTbl[GwPlayer[2].chr][2], 2);
    object->trans.x = m225_player2StartPos.x;
    object->trans.y = m225_player2StartPos.y;
    object->trans.z = m225_player2StartPos.z;
}

void m225_Player3ObjInit(omObjData *object) {
    m225_PlayerInit(object, omCharModelNoTbl[GwPlayer[3].chr][0], omCharModelNoTbl[GwPlayer[3].chr][2], 3);
    object->trans.x = m225_player3StartPos.x;
    object->trans.y = m225_player3StartPos.y;
    object->trans.z = m225_player3StartPos.z;
}

void m225_PuckObjInit(omObjData *object) {
    IceRinkRiskPuckWork *work;
    s32 i;

    object->data = HuMemAllocTag(sizeof(IceRinkRiskPuckWork), TAG_OVERLAY);
    memset(object->data, 0, sizeof(IceRinkRiskPuckWork));
    work = OM_GET_DATA_PTR(object, IceRinkRiskPuckWork);
    object->model[0] = Hu3DModelRead2(0x3A0000, 0x899);
    object->model[1] = Hu3DModelRead3(9, 0xADD);
    object->model[2] = Hu3DModelRead(0x3A0002, 0xADD);
    MgShadowMdlInit(object->model[1]);
    object->func = m225_PuckObjMain;
    work->unk44 = 0.3f;
    work->unk48 = 60.0f;
    work->unk34 = 50.0f;
    work->unk3C = rand8() * (360.0f / 255.0f);
    work->unk78 = 0;
    work->unk52 = 7;
    work->unk7C = 0;
    work->unk50 = 0;
    work->unk40 = 11.0f;
    work->unk74 = 0.5f;
    work->unk56 = m225_puckCreateCnt;
    work->unk54 = 1;
    for (i = 0; i < 9; i++) {
        work->unk84[i] = 0;
    }
    MgPlayerMapAttrSet(object, 0, 2);
    object->trans.x = rand8() / 4;
    object->trans.y = m225_puckStartTbl[m225_puckCreateCnt][1];
    object->trans.z = rand8() / 4;
    object->scale.x = object->scale.y = object->scale.z = 1.2f;
    m225_puckCreateCnt++;
}

void m225_PuckObjMain(omObjData *object) {
    IceRinkRiskPuckWork *work = OM_GET_DATA_PTR(object, IceRinkRiskPuckWork);
    f32 x, y, z;
    f32 angle;
    f32 floorY;
    u8 bounce = TRUE;
    s32 i;

    if (m225_puckActiveTbl[work->unk56] != 0) {
        mgMoveOfsX = mgMoveOfsZ = 0.0f;
        x = object->trans.x;
        y = object->trans.y;
        z = object->trans.z;
        angle = work->unk3C;
        if (work->unk40 > 25.0f) {
            work->unk40 = 25.0f;
        }
        x += sindf(angle) * work->unk40;
        z += cosdf(angle) * work->unk40;
        if (work->unk38 != 1000.0f) {
            y += work->unk38 * work->unk38 * (work->unk38 >= 0.0f ? -35.0f : 35.0f);
            work->unk38 += mgItemGravity;
            if (work->unk38 > mgItemFallMax) {
                work->unk38 = mgItemFallMax;
            }
            floorY = m225_PuckCollide(object, x, y, z);
            if (y < floorY) {
                y = floorY;
                if (bounce) {
                    work->unk38 = -work->unk38 * 0.7f;
                    if (work->unk38 >= -0.4f) {
                        work->unk38 = 1000.0f;
                    }
                    for (i = 0; i < 4; i++) {
                        // The original reads the player index without going through ->data.
                        if (m225_playerAliveTbl[((MgPlayerWork *)mgPlayerObjTbl[i])->unk59] == 1) {
                            omVibrate(((MgPlayerWork *)mgPlayerObjTbl[i])->unk59, 2, 3, 10);
                        }
                    }
                }
            }
        } else {
            y = m225_PuckCollide(object, x, y, z);
        }
        MgObjPosSet(object, x + mgMoveOfsX, y, z + mgMoveOfsZ);
        m225_puckRotTbl[work->unk56] += work->unk40 / 5.0f;
        m225_puckRotTbl[work->unk56] = HuAngleWrap(m225_puckRotTbl[work->unk56]);
        HuRotateRPYF(Hu3DData[object->model[0]].mtx, 0.0f, m225_puckRotTbl[work->unk56], 0.0f);
    }
}

f32 m225_PuckCollide(omObjData *object, f32 x, f32 y, f32 z) {
    IceRinkRiskPuckWork *work = OM_GET_DATA_PTR(object, IceRinkRiskPuckWork);
    Hu3DSphere sphere;

    sphere.pos.x = x;
    sphere.pos.y = y;
    sphere.pos.z = z;
    sphere.radius = work->unk48;
    m225_PuckHitCheck(object, x, y, z);
    m225_PuckWallCheck(object, &sphere);
    return m225_PuckFloorCheck(object, &sphere);
}

f32 m225_PuckFloorCheck(omObjData *object, Hu3DSphere *sphere) {
    IceRinkRiskPuckWork *work = OM_GET_DATA_PTR(object, IceRinkRiskPuckWork);
    Vec normal;
    f32 y = sphere->pos.y;
    f32 floorY = m225_PuckFloorGet(object, sphere, &normal);
    f32 resultY = floorY;

    if (floorY < y - work->unk34 || y + work->unk34 <= floorY) {
        if (work->unk38 == 1000.0f) {
            work->unk38 = 0.0f;
        }
        resultY = y;
    }
    m225_PuckShadowSet(object, sphere->pos.x, resultY, sphere->pos.z, floorY, &normal);
    return resultY;
}

void m225_PuckShadowSet(omObjData *object, f32 x, f32 y, f32 z, f32 floorY, Vec *normal) {
    IceRinkRiskPuckWork *work = OM_GET_DATA_PTR(object, IceRinkRiskPuckWork);
    f32 scale = 1.0f;
    f32 height;

    if (object->model[1] != 0) {
        height = y - floorY;
        if (height != 0.0f) {
            if (height > 900.0f) {
                scale = 0.1f;
            } else {
                scale = 1.0f - fabsf(height) / 1000.0f;
            }
            work->unk53 = -1;
        }
        Hu3DModelPosSet(object->model[1], x, floorY + 5.0f, z);
        Hu3DModelScaleSet(object->model[1], scale, 1.0f, scale);
        MgShadowSlopeSet(object->model[1], normal);
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
}

f32 m225_PuckFloorGet(omObjData *object, Hu3DSphere *sphere, Vec *normal) {
    IceRinkRiskPuckWork *work = OM_GET_DATA_PTR(object, IceRinkRiskPuckWork);
    f32 floorY;

    work->unk53 = 0;
    floorY = OM_GET_DATA_PTR(mgMapObjTbl[0], MgMapWork)->unk14;
    normal->x = 0.0f;
    normal->y = 1.0f;
    normal->z = 0.0f;
    return floorY;
}

// NON_MATCHING: the target hoists the mgItemObjTbl address (s5), 0.0f
// ($f24) and 1000.0f (s4) out of the loop, in that order, after the entry test.
// With direct indexing the address is the first loop.c movable (threshold
// 61 -> 58), and the loop has at least 59 insns at loop time (56 in the final
// loop + 3 movables), so 0.0f (savings 1, life 1) can never pass
// threshold * savings * lifetime >= insn_count. Only something giving 0.0f
// savings/lifetime >= 2 (e.g. a matched duplicate 0.0f compare, which leaves
// an extra bc1f) could hoist it; none of the natural forms tried do. The
// direct form is otherwise identical apart from that one hoist.
// Reading through a local pointer (below) hoists 0.0f, but the pointer is set
// before the loop entry test and 0.0f/1000.0f swap register classes. The two
// do-while(0) wrappers only lower the diff score (740 -> 625).
// Also tried: if/continue/early-continue forms, compare spellings, a `zero`
// local, `unk48 * 2`/`2.0f * unk48`, splitting the dist computation,
// `dist < 0.0f && unk38 == 1000.0f` plus a second `dist < 0.0f` block.
#ifdef NON_MATCHING
void m225_PuckHitCheck(omObjData *object, f32 x, f32 y, f32 z) {
    IceRinkRiskPuckWork *work = OM_GET_DATA_PTR(object, IceRinkRiskPuckWork);
    IceRinkRiskPuckWork *otherWork;
    omObjData *other;
    f32 dx, dy, dz;
    f32 dist;
    s32 i;
    omObjData **objs = mgItemObjTbl;

    for (i = 0; i < m225_puckNum; i++) {
        if (i == work->unk56) {
            continue;
        }
        other = objs[i];
        otherWork = other->data;
        dx = other->trans.x - (x + mgMoveOfsX);
        dy = other->trans.y - y;
        dz = other->trans.z - (z + mgMoveOfsZ);
        dist = HuSqrtf(dx * dx + dy * dy + dz * dz) - (work->unk48 + work->unk48);
        if (dist < 0.0f) {
            do {
                if (work->unk38 == 1000.0f) {
                    MgMoveOfsAdd(dx, dz, dist);
                }
            } while (0);
            m225_PuckHitReflect(object, dx, dz);
            if (m225_puckHitTbl[work->unk56].unk04 >= 16) {
                m225_puckHitTbl[work->unk56].unk00 = otherWork->unk56;
                do {
                    m225_puckHitTbl[work->unk56].unk04 = 0;
                } while (0);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game/overlays/minigames/19_ice_rink_risk/main", m225_PuckHitCheck);
#endif

void m225_PuckWallCheck(omObjData *object, Hu3DSphere *arg1) {
    IceRinkRiskPuckWork *work = OM_GET_DATA_PTR(object, IceRinkRiskPuckWork);
    Hu3DSphere sphere;
    MgHitSphere local;
    omObjData *obj;

    sphere.pos.x = arg1->pos.x;
    sphere.pos.y = work->unk34 / 2 + arg1->pos.y;
    sphere.pos.z = arg1->pos.z;
    sphere.radius = arg1->radius;
    mgWallNum = 0;
    obj = mgMapObjTbl[0];
    local.pos.x = local.prev.x = arg1->pos.x;
    local.pos.y = local.prev.y = work->unk34 / 2 + arg1->pos.y;
    local.pos.z = local.prev.z = arg1->pos.z;
    local.radius = sphere.radius = arg1->radius;
    MgMapPosLocalGet(mgMapMtx, mgMapInvMtx, &local.pos, obj);
    local.pos.x += mgMoveOfsX;
    local.pos.y += mgMoveOfsZ;
    MgMapCircleBoundsHit(obj, (Hu3DSphere *)&local);
    if (mgWallNum != 0) {
        MgMtxDirMult(mgMapMtx, mgWallNorTbl);
    }
    m225_PuckWallReflect(object);
}

void m225_PuckWallReflect(omObjData *object) {
    IceRinkRiskPuckWork *work;
    Vec normal;
    Vec dir;
    Vec reflect;
    f32 dot;

    if (mgWallNum != 0) {
        work = OM_GET_DATA_PTR(object, IceRinkRiskPuckWork);
        HuAudFXPlay(0x3D2);
        normal.x = mgWallNorTbl[0].x;
        normal.y = dir.y = 0.0f;
        normal.z = mgWallNorTbl[0].z;
        dir.x = sindf(work->unk3C + 180.0f);
        dir.z = cosdf(work->unk3C + 180.0f);
        dot = HuVecDot3F(&normal, &dir);
        normal.x = dot * normal.x;
        normal.z = dot * normal.z;
        HuVecSubtract(&reflect, &normal, &dir);
        HuVecAdd(&reflect, &normal, &reflect);
        work->unk3C = atan2df(reflect.x, reflect.z);
        work->unk40 += 1.0f;
    }
}

void m225_PuckHitReflect(omObjData *object, f32 dx, f32 dz) {
    IceRinkRiskPuckWork *work = OM_GET_DATA_PTR(object, IceRinkRiskPuckWork);
    Vec normal;
    Vec dir;
    Vec reflect;
    f32 dot;
    f32 angle;

    HuAudFXPlay(0x3D2);
    normal.x = dx;
    normal.y = dir.y = 0.0f;
    normal.z = dz;
    MapVecNormalize(&normal);
    dir.x = sindf(work->unk3C + 180.0f);
    dir.z = cosdf(work->unk3C + 180.0f);
    dot = HuVecDot3F(&normal, &dir);
    normal.x = dot * normal.x;
    normal.z = dot * normal.z;
    HuVecSubtract(&reflect, &normal, &dir);
    HuVecAdd(&reflect, &normal, &reflect);
    angle = atan2df(reflect.x, reflect.z);
    work->unk3C = angle + (rand8() - 128.0f) / 64.0f;
    work->unk40 += 1.0f;
    m225_puckHitTbl[work->unk56].pos.x = dx + object->trans.x;
    m225_puckHitTbl[work->unk56].pos.y = object->trans.y;
    m225_puckHitTbl[work->unk56].pos.z = dz + object->trans.z;
}
