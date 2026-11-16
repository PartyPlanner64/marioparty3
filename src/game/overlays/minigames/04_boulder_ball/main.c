#include "common.h"
#include "game/hmfmath.h"
#include "game/mallocblock.h"
#include "game/pause.h"
#include "gcc/memory.h"
#include "game/overlays/minigame.h"

extern s32 omCharModelNoTbl[][6];
extern u8 omAllPauseF;
extern f32 mgItemSpeedMax;
extern u16 mgHitSkipCnt;
extern Vec mgWallNorTbl[];
extern omObjData *mgItemObjTbl[];

s32 m204_boulderStateTbl[8] = { 2, 0, 0, 0, 0, 0, 0, 0 };
Vec m204_runnerStartPosA = { 320.0f, 0.0f, 1000.0f };
Vec m204_runnerStartPosB = { 0.0f, 0.0f, 1000.0f };
Vec m204_runnerStartPosC = { -320.0f, 0.0f, 1000.0f };
s32 m204_boulderSeTbl[4] = { -1, -1, -1, -1 };
f32 m204_stageBounceVel = 1000.0f;
s32 m204_boulderReadyF = 1;
s32 m204_runnerGoalF = 0;
MinigameFlow m204_mgFlow = {
    MG_STATE_OPENING, MINIGAME_2V2, MG_TIMER_COUNT_DOWN, MG_TIME_DISP_COUNTDOWN, FALSE, MG_GAUGE_NONE, MG_RESULT_WIN_1, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    135, 900, -1, 75, 150
};
s32 m204_mgFlowPad[3] = { 0, 0, 0 }; /* Unreferenced. */
s32 m204_introThrowF = 0;
f32 m204_stageBounceY = 0.0f;
s32 m204_stageBounceYPad = 0; /* Unreferenced. */
s32 m204_finishInitF = 0;
f32 m204_runnerLaneXTbl[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
s32 m204_runnerComStateTbl[4] = { 0, 0, 0, 0 };
s32 m204_runnerPlayerNo = 0;
s32 m204_pusherComTarget = 5;
s32 m204_pusherWinTimer = 0;
s32 m204_boulderNum = 0;
f32 m204_boulderSpinTbl[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
s32 m204_boulderNextNo = 0;

f32 m204_cameraRotXStep BSS;
f32 m204_cameraYStep BSS;
f32 m204_cameraZStep BSS;
s32 m204_padBtn BSS;
s32 m204_padBtnDown BSS;
s32 m204_padStkX BSS;
s32 m204_padStkY BSS;
s32 m204_pusherPlayerNo BSS;
omObjData *m204_boulderObj BSS;
omObjData *m204_pusherObj BSS;
u8 m204_pusherObjPad[8] BSS; /* Unreferenced. */

void m204_ExitObjMain(omObjData *object);
void m204_CameraFollow(void);
void m204_IntroUpdate(void);
void m204_MainObjMain(omObjData *object);
void m204_MapObjInit(omObjData *object);
void m204_MapSubObjInit(omObjData *object);
void m204_RunnerInit(omObjData *object, s32 model, s32 motion, u16 player);
s32 m204_RunnerHit(omObjData *object, omObjData *other);
s32 m204_RunnerGoalCheck(omObjData *object);
s32 m204_RunnerComInput(omObjData *object);
void m204_Runner0ObjInit(omObjData *object);
void m204_Runner1ObjInit(omObjData *object);
void m204_Runner2ObjInit(omObjData *object);
void m204_PusherObjInit(omObjData *object);
void m204_PusherComInput(omObjData *object);
void m204_PusherWinObjMain(omObjData *object);
void m204_PusherObjMain(omObjData *object);
void m204_BoulderObjInit(omObjData *object);
s32 m204_BoulderHitHook(omObjData *object);
void m204_BoulderDustUpdate(omObjData *object);
s32 m204_BoulderUpdate(omObjData *object);
void m204_BoulderAccel(omObjData *object);
s32 m204_BoulderBounce(omObjData *object);
s32 m204_BoulderWallHit(omObjData *object);

void m204_ObjectSetup(void) {
    u8 camIndex;

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
    Hu3DCameraPerspectiveSet(0, 32.0f, 80.0f, 5000.0f);
    Hu3DGLightDirSet(1, -94.0f, 65.0f, 34.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    MgPlayerParamReset();
    MgShadowAltSet(1);
    mgPlayerFallInit = 0.0f;
    MgMapBaseSet(mgMapObjNum);
    mgMapObjTbl[mgMapObjNum++] = omAddObj(1, 10, 0, -1, m204_MapObjInit);
    mgMapObjTbl[mgMapObjNum++] = omAddObj(1, 5, 0, -1, m204_MapSubObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(3, 10, 60, -1, m204_Runner0ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(3, 10, 60, -1, m204_Runner1ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(3, 10, 60, -1, m204_Runner2ObjInit);
    m204_pusherObj = omAddObj(3, 10, 60, -1, m204_PusherObjInit);
    m204_boulderObj = mgItemObjTbl[mgItemObjNum++] =
        omAddObj(2, 4, 0, -1, m204_BoulderObjInit);
    mgItemObjTbl[mgItemObjNum++] = omAddObj(2, 10, 0, -1, m204_BoulderObjInit);
    mgItemObjTbl[mgItemObjNum++] = omAddObj(2, 10, 0, -1, m204_BoulderObjInit);
    mgItemObjTbl[mgItemObjNum++] = omAddObj(2, 10, 0, -1, m204_BoulderObjInit);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Center.x = 0.0f;
    Center.y = 200.0f;
    Center.z = 900.0f;
    CRot.x = 358.0f;
    CRot.y = 0.0f;
    CZoom = 1400.0f;
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    MgFlowInit(&m204_mgFlow);
    if (GwPlayer[0].group == 0) {
        m204_pusherPlayerNo = 0;
    }
    if (GwPlayer[1].group == 0) {
        m204_pusherPlayerNo = 1;
    }
    if (GwPlayer[2].group == 0) {
        m204_pusherPlayerNo = 2;
    }
    if (GwPlayer[3].group == 0) {
        m204_pusherPlayerNo = 3;
    }
    mgFlowSeqNo = 47;
    mgFlowSeqTime = 36;
}

void m204_ExitObjMain(omObjData *object) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

void m204_CameraFollow(void) {
    f32 minY = 2000.0f;
    f32 maxZ = 0.0f;
    s32 i;

    for (i = 0; i < mgPlayerObjNum; i++) {
        if (maxZ < mgPlayerObjTbl[i]->trans.z) {
            maxZ = mgPlayerObjTbl[i]->trans.z;
        }
        if (mgPlayerObjTbl[i]->trans.y < minY) {
            minY = mgPlayerObjTbl[i]->trans.y;
        }
    }
    Center.x = 0.0f;
    Center.y = minY + 200.0f;
    Center.z = maxZ;
    if (890.0f < maxZ) {
        Center.z = 890.0f;
    }
    if (Center.y < 325.0f) {
        Center.y = 325.0f;
    }
    if (Center.y > 550.0f) {
        Center.y = 550.0f;
    }
    CRot.x = 362.0f - (Center.z - 600.0f) / 60.0f;
    CZoom = 1500.0f - (Center.y - 325.0f);
    if (CRot.x > 370.0f) {
        CRot.x = 370.0f;
    }
    if (CRot.x < 358.0f) {
        CRot.x = 358.0f;
    }
    if (CZoom < 1300.0f) {
        CZoom = 1300.0f;
    }
}

void m204_IntroUpdate(void) {
    s32 time = MgFlowStatTimeGet();
    MgPlayerWork *playerData = m204_pusherObj->data;
    MgItemWork *boulderData = m204_boulderObj->data;

    if (time < 5) {
        Center.x = 0.0f;
        Center.y = 800.0f;
        Center.z = -700.0f;
        CZoom = 1000.0f;
        m204_boulderObj->trans.x = sindf(m204_pusherObj->rot.y) * 150.0f + 0.0f;
        m204_boulderObj->trans.y = 700.0f;
        m204_boulderObj->trans.z = cosdf(m204_pusherObj->rot.y) * 150.0f + -900.0f;
    } else if (time < 40 && m204_introThrowF == 0) {
        m204_pusherObj->rot.y -= 1.5f;
        if (m204_pusherObj->rot.y < -26.0f) {
            m204_pusherObj->rot.y = -26.0f;
        }
        if (m204_pusherObj->rot.y == -26.0f) {
            Hu3DMotionTimeSet(m204_pusherObj->model[1], 0.0f);
            playerData->unk50 = 0;
            m204_boulderReadyF = 0;
            m204_boulderObj->rot.y = boulderData->unk3C = m204_pusherObj->rot.y;
            boulderData->unk40 = 7.0f;
            boulderData->unk78 = 0;
            boulderData->unk38 = -0.75f;
            m204_introThrowF = 1;
            HuAudPlayerFXPlay(0x31F, m204_pusherPlayerNo);
        }
        m204_boulderObj->trans.x = sindf(m204_pusherObj->rot.y) * 150.0f + 0.0f;
        m204_boulderObj->trans.y = 700.0f;
        m204_boulderObj->trans.z = cosdf(m204_pusherObj->rot.y) * 150.0f + -900.0f;
    } else {
        m204_pusherObj->rot.y *= 0.8f;
        Center.y -= 6.6666665f;
        Center.z += 17.777779f;
        CZoom += 4.4444447f;
        if (Center.y < 325.0f) {
            Center.y = 325.0f;
        }
        if (Center.z > 890.0f) {
            Center.z = 890.0f;
        }
        if (CZoom > 1500.0f) {
            CZoom = 1500.0f;
        }
    }
    Hu3DModelRotSet(m204_pusherObj->model[1], 0.0f, m204_pusherObj->rot.y, 0.0f);
}

void m204_MainObjMain(omObjData *object) {
    MgPlayerWork *data;
    MgPlayerWork *work;
    omObjData *player;
    f32 velocity;
    f32 speedSq;
    f32 y;
    s32 i;
    s32 j;

    if (omPauseChk() + omAllPauseF != 0) {
        return;
    }
    MgFlowStatTimeGet();
    switch (MgFlowMain()) {
        case 0:
            m204_IntroUpdate();
            break;
        case 2:
            m204_CameraFollow();
            break;
        case 3:
            if (m204_finishInitF == 0) {
                m204_pusherObj->func = m204_PusherWinObjMain;
                MgMapSlideSet(mgMapObjTbl[0], 0.0f);
                for (i = 0; i < mgItemObjNum; i++) {
                    Hu3DModelAttrSet(mgItemObjTbl[i]->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(mgItemObjTbl[i]->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    if (m204_boulderSeTbl[i] != -1) {
                        HuAudFXStop((s16)m204_boulderSeTbl[i]);
                        m204_boulderSeTbl[i] = -1;
                    }
                }
                if (m204_runnerGoalF == 0) {
                    m204_mgFlow.resultType = MG_RESULT_WIN_1;
                    m204_mgFlow.winners[0] = m204_pusherPlayerNo;
                    Hu3DModelAttrSet(m204_pusherObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DModelAttrSet(m204_pusherObj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    MgPlayerMotForceSet(m204_pusherObj, 6);
                    work = m204_pusherObj->data;
                    work->unk38 = -mgPlayerJumpPower;
                } else {
                    m204_mgFlow.resultType = MG_RESULT_WIN_3;
                    for (j = 0, i = 0; i < 4; i++) {
                        if (m204_pusherPlayerNo != i) {
                            m204_mgFlow.winners[j++] = i;
                        }
                    }
                }
                m204_cameraRotXStep = (CRot.x - 340.0f) / 60.0f;
                m204_cameraYStep = (Center.y - 700.0f) / 60.0f;
                m204_cameraZStep = (Center.z - -800.0f) / 60.0f;
                m204_finishInitF = 1;
            }
            for (i = 0; i < 3; i++) {
                player = mgPlayerObjTbl[i];
                work = player->data;
                work->unk3C *= 0.8f;
            }
            m204_pusherObj->rot.y *= 0.8f;
            if (m204_runnerGoalF == 0) {
                CRot.x -= m204_cameraRotXStep;
                if (CRot.x < 340.0f) {
                    CRot.x = 340.0f;
                }
                Center.y -= m204_cameraYStep;
                if (Center.y > 700.0f) {
                    Center.y = 700.0f;
                }
                Center.z -= m204_cameraZStep;
                if (Center.z < -800.0f) {
                    Center.z = -800.0f;
                }
            }
            break;
        case 4:
            if (mgFlowResultF == 1) {
                if (m204_runnerGoalF == 1) {
                    for (i = 0; i < 3; i++) {
                        player = mgPlayerObjTbl[i];
                        data = player->data;
                        MgPlayerMotForceSet(player, 0xD);
                        HuAudCharVoicePlay(omCharModelNoTbl[GwPlayer[data->unk59].chr][0] | 0x2F);
                        GwPlayer[data->unk59].bonusCoin += 10;
                    }
                } else {
                    GwPlayer[m204_pusherPlayerNo].bonusCoin += 10;
                    for (i = 0; i < 3; i++) {
                        MgPlayerMotForceSet(mgPlayerObjTbl[i], 0xE);
                    }
                    MgPlayerMotForceSet(m204_pusherObj, 0xD);
                    HuAudCharVoicePlay(omCharModelNoTbl[GwPlayer[m204_pusherPlayerNo].chr][0] | 0x2F);
                }
            }
            break;
        case 5:
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            object->func = m204_ExitObjMain;
            break;
    }
    for (i = 0; i < mgPlayerObjNum; i++) {
        work = mgPlayerObjTbl[i]->data;
        work->unk60 = CRot.y;
    }
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
        object->func = m204_ExitObjMain;
    }
    if (m204_stageBounceVel != 1000.0f) {
        velocity = m204_stageBounceVel;
        if (velocity > mgPlayerFallMax) {
            velocity = mgPlayerFallMax;
        }
        speedSq = velocity * velocity;
        y = m204_stageBounceY + speedSq * (m204_stageBounceVel >= 0.0f ? -36.75f : 36.75f);
        m204_stageBounceY = y;
        m204_stageBounceVel = velocity = m204_stageBounceVel + mgPlayerGravity;
        if (y < 0.0f) {
            m204_stageBounceY = 0.0f;
            if (velocity > 0.5f) {
                m204_stageBounceVel = -velocity * 0.5f;
            } else {
                m204_stageBounceVel = 1000.0f;
            }
        }
        Hu3DModelPosSet(object->model[1], 0.0f, m204_stageBounceY, 0.0f);
    }
}

void m204_MapObjInit(omObjData *object) {
    MgMapWork *work;

    mgPlayerAccel = 15.0f;
    object->model[0] = Hu3DModelRead2(0x250000, 0x6B9);
    object->model[1] = Hu3DModelRead2(0x250003, 0xAB9);
    object->trans.x = 0.0f;
    object->trans.y = 0.0f;
    object->trans.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    object->func = m204_MainObjMain;
    work->unk03 = 1;
    MgMapTiltOn(object);
    MgMapAttrSet(object, 1, 0.0f);
    MgMapFrictionSet(object, 0.2f);
    MgMapAccelSet(object, mgPlayerAccel);
    MgMapSlideSet(object, 22.5f);
    MgMapNoBumpOn(object);
    work->unk04 = 0;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void m204_MapSubObjInit(omObjData *object) {
    MgMapWork *work;

    mgPlayerAccel = 15.0f;
    object->model[0] = Hu3DModelRead2(0x250001, 0x29D);
    object->trans.x = 0.0f;
    object->trans.y = 0.0f;
    object->trans.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    object->func = NULL;
    work->unk03 = 1;
    MgMapTiltOn(object);
    MgMapAttrSet(object, 1, 0.0f);
    MgMapFrictionSet(object, 0.2f);
    MgMapAccelSet(object, mgPlayerAccel);
    MgMapSlideSet(object, 22.5f);
    MgMapNoBumpOn(object);
    work->unk04 = 1;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void m204_RunnerInit(omObjData *object, s32 model, s32 motion, u16 player) {
    MgPlayerWork *data;
    s32 chr;
    s32 attr1 = 0xAC9;
    s32 attr2 = 0xA99;

    MgPlayerCreate(object, model, motion, player, attr1, attr2);
    data = object->data;
    chr = GwPlayer[data->unk59].chr;
    object->model[3] = Hu3DModelRead(3, 0x88D);
    object->model[4] = Hu3DModelRead(4, 0x88D);
    object->model[5] = Hu3DModelRead(6, 0x88D);
    object->model[7] = Hu3DModelRead(8, 0x88D);
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(chr, 0), 1, 0);
    MgPlayerMotLoad(object, 1, CharMotionDataNumGet(chr, 1), 1, 0);
    MgPlayerMotLoad(object, 2, CharMotionDataNumGet(chr, 2), 1, 0);
    MgPlayerMotLoad(object, 0x11, CharMotionDataNumGet(chr, 0xE), 1, 0xF);
    MgPlayerMotLoad(object, 3, CharMotionDataNumGet(chr, 0x1D), 1, 0);
    MgPlayerMotLoad(object, 4, CharMotionDataNumGet(chr, 0x1E), 1, 0);
    MgPlayerMotLoad(object, 0x1E, CharMotionDataNumGet(chr, 0x20), 2, 0);
    MgPlayerMotLoad(object, 0x1F, CharMotionDataNumGet(chr, 0x21), 2, 0);
    MgPlayerMotLoad(object, 0x20, CharMotionDataNumGet(chr, 0x22), 0, 0);
    MgPlayerMotRead(object, 0xD, CharMotionDataNumGet(chr, 0x2F), 1, 0x78);
    MgPlayerMotRead(object, 0xE, CharMotionDataNumGet(chr, 0x36), 1, 0x78);
    data->unk4C = 0.05f;
    data->unkB4 = 0.8f;
    data->unkEC = m204_RunnerHit;
    MgPlayerMapAttrSet(object, 0, 2);
    MgPlayerMapAttrSet(object, 1, 1);
    MgPlayerHookSet(data, 0, m204_RunnerComInput);
    MgPlayerHookSet(data, 1, m204_RunnerGoalCheck);
}

s32 m204_RunnerHit(omObjData *object, omObjData *other) {
    MgPlayerWork *data = object->data;
    f32 x, y, z;

    if (MgFlowStatGet() == MG_STATE_PLAY) {
        if (data->unkBE != 0) {
            mgHitSkipCnt++;
        } else {
            x = object->trans.x;
            y = object->trans.y;
            z = object->trans.z;
            HuAudPlayerFXPlay(GwPlayer[data->unk59].chr + 0x287, data->unk59);
            HuAudPlayerFXPlay(0x320, data->unk59);
            MgPlayerSquashSet(object, 1);
            MgPlayerMotSet(object, 0);
            MgPlayerEffSet(object, 7, x, y, z, 0.0f, 0.0f);
            data->unkBE = 105;
            omVibrate(data->unk59, 20, 0, 20);
        }
    }
    return 1;
}

s32 m204_RunnerGoalCheck(omObjData *object) {
    MgPlayerWork *data = object->data;

    if (GwPlayer[data->unk59].stat & 1) {
        HuPadBtnDown[data->unk57] = m204_padBtnDown;
        HuPadBtn[data->unk57] = m204_padBtn;
        HuPadStkX[data->unk57] = m204_padStkX;
        HuPadStkY[data->unk57] = m204_padStkY;
    }
    if (MgFlowStatGet() == MG_STATE_PLAY && object->trans.z <= -600.0f) {
        MgFlowStatSet(MG_STATE_FINISH);
        m204_runnerGoalF = 1;
    }
    return 0;
}

s32 m204_RunnerComInput(omObjData *object) {
    Vec dir;
    f32 ranges[4] = { 70.0f, 80.0f, 90.0f, 100.0f };
    f32 speeds[4] = { 0.5f, 0.55f, 0.6f, 0.65f };
    MgPlayerWork *data = object->data;
    s32 player = data->unk59;
    s32 pad = data->unk57;
    MgItemWork *boulderData;
    omObjData *boulder;
    s32 difficulty;
    s32 target;
    f32 x;
    f32 z;
    f32 angle;
    f32 speed;
    f32 dist;
    s32 i;

    if (MgFlowStatGet() != MG_STATE_PLAY) {
        return 0;
    }
    if (!(GwPlayer[player].stat & 1)) {
        return 0;
    }
    m204_padBtnDown = HuPadBtnDown[pad];
    m204_padBtn = (u16)HuPadBtn[pad];
    m204_padStkX = HuPadStkX[pad];
    m204_padStkY = HuPadStkY[pad];
    HuPadStkY[pad] = 0;
    HuPadStkX[pad] = 0;
    HuPadBtnDown[pad] = 0;
    HuPadBtn[pad] = 0;
    difficulty = GwPlayer[player].cpu_difficulty;
    x = z = dir.x = dir.y = dir.z = 0.0f;
    target = -1;
    speed = 30000.0f;
    for (i = 0; i < mgItemObjNum; i++) {
        boulder = mgItemObjTbl[i];
        boulderData = boulder->data;
        if (m204_boulderStateTbl[boulderData->unk56] == 3) {
            x = boulder->trans.x;
            z = boulder->trans.z;
            dist = HuSqrtf(x * x + z * z);
            if (dist < speed) {
                speed = dist;
                target = i;
            }
        }
    }
    if (target != -1) {
        boulderData = mgItemObjTbl[target]->data;
        x = mgItemObjTbl[target]->trans.x;
        z = mgItemObjTbl[target]->trans.z;
        angle = mgItemObjTbl[target]->rot.y;
        speed = boulderData->unk40;
        for (i = 0; i < 100; i++) {
            x += sindf(angle) * speed;
            z += cosdf(angle) * speed;
            speed += 0.3f;
            if (speed > 35.0f) {
                speed = 35.0f;
            }
            if (fabs(x) > 450.0f - boulderData->unk48) {
                angle = -angle;
            }
            if (z > object->trans.z) {
                break;
            }
        }
        dir.x = object->trans.x - x;
        dir.z = object->trans.z - z;
        dir.y = 0.0f;
        MapVecNormalize(&dir);
    }
    switch (m204_runnerComStateTbl[player]) {
        case 0:
            HuPadStkY[pad] = 60;
            if (target == -1) {
                return 0;
            }
            x = object->trans.x - x;
            z = object->trans.z - z;
            if (HuSqrtf(x * x + z * z) < data->unk48 + boulderData->unk48 + ranges[difficulty]) {
                HuPadStkX[pad] = dir.x * 60.0f * speeds[difficulty];
                m204_runnerComStateTbl[player] = 1;
            }
            break;
        case 1:
            dir.x = object->trans.x - x;
            dir.z = object->trans.z - z;
            dir.y = 0.0f;
            MapVecNormalize(&dir);
            HuPadStkX[pad] = dir.x * 60.0f * speeds[difficulty];
            HuPadStkY[pad] = 60;
            x = object->trans.x - x;
            z = object->trans.z - z;
            dist = HuSqrtf(x * x + z * z);
            if (target == -1) {
                m204_runnerComStateTbl[player] = 2;
            } else if (data->unk48 + boulderData->unk48 + ranges[difficulty] < dist) {
                m204_runnerComStateTbl[player] = 2;
            }
            break;
        case 2:
            HuPadStkY[pad] = 60;
            dir.x = object->trans.x - m204_runnerLaneXTbl[player];
            dir.z = 0.0f;
            dir.y = 0.0f;
            MapVecNormalize(&dir);
            HuPadStkX[pad] = -dir.x * 60.0f * speeds[difficulty];
            if (m204_runnerLaneXTbl[player] - 50.0f < object->trans.x &&
                object->trans.x < m204_runnerLaneXTbl[player] + 50.0f) {
                m204_runnerComStateTbl[player] = 0;
            }
            if (target == -1) {
                return 0;
            }
            x = object->trans.x - x;
            z = object->trans.z - z;
            if (HuSqrtf(x * x + z * z) < data->unk48 + boulderData->unk48 + ranges[difficulty]) {
                m204_runnerComStateTbl[player] = 1;
            }
            break;
    }
    return 0;
}

void m204_Runner0ObjInit(omObjData *object) {
    if (GwPlayer[m204_runnerPlayerNo].group == 0) {
        m204_runnerPlayerNo++;
    }
    m204_RunnerInit(object, omCharModelNoTbl[GwPlayer[m204_runnerPlayerNo].chr][0],
                               omCharModelNoTbl[GwPlayer[m204_runnerPlayerNo].chr][2], m204_runnerPlayerNo);
    m204_runnerLaneXTbl[m204_runnerPlayerNo] = m204_runnerStartPosA.x - 80.0f;
    object->trans.x = m204_runnerStartPosA.x;
    object->trans.y = m204_runnerStartPosA.y;
    object->trans.z = m204_runnerStartPosA.z;
    m204_runnerPlayerNo++;
}

void m204_Runner1ObjInit(omObjData *object) {
    if (GwPlayer[m204_runnerPlayerNo].group == 0) {
        m204_runnerPlayerNo++;
    }
    m204_RunnerInit(object, omCharModelNoTbl[GwPlayer[m204_runnerPlayerNo].chr][0],
                               omCharModelNoTbl[GwPlayer[m204_runnerPlayerNo].chr][2], m204_runnerPlayerNo);
    m204_runnerLaneXTbl[m204_runnerPlayerNo] = m204_runnerStartPosB.x;
    object->trans.x = m204_runnerStartPosB.x;
    object->trans.y = m204_runnerStartPosB.y;
    object->trans.z = m204_runnerStartPosB.z;
    m204_runnerPlayerNo++;
}

void m204_Runner2ObjInit(omObjData *object) {
    if (GwPlayer[m204_runnerPlayerNo].group == 0) {
        m204_runnerPlayerNo++;
    }
    m204_RunnerInit(object, omCharModelNoTbl[GwPlayer[m204_runnerPlayerNo].chr][0],
                               omCharModelNoTbl[GwPlayer[m204_runnerPlayerNo].chr][2], m204_runnerPlayerNo);
    m204_runnerLaneXTbl[m204_runnerPlayerNo] = m204_runnerStartPosC.x + 80.0f;
    object->trans.x = m204_runnerStartPosC.x;
    object->trans.y = m204_runnerStartPosC.y;
    object->trans.z = m204_runnerStartPosC.z;
    m204_runnerPlayerNo++;
}

void m204_PusherObjInit(omObjData *object) {
    MgPlayerWork *data;
    s32 effectAttr = 0x89D;
    s32 motion = omCharModelNoTbl[GwPlayer[m204_pusherPlayerNo].chr][2];
    s32 model = omCharModelNoTbl[GwPlayer[m204_pusherPlayerNo].chr][0];
    s32 attr = 0xAD9;
    s32 chr;
    s32 i;

    for (i = 0; i < object->mdlcnt; i++) {
        object->model[i] = 0;
    }
    object->data = HuMemAllocTag(sizeof(MgPlayerWork), TAG_OVERLAY);
    memset(object->data, 0, sizeof(MgPlayerWork));
    data = object->data;
    data->unkE8 = HuMemAllocTag(object->mtncnt * sizeof(MgMotAttr), TAG_OVERLAY);
    for (i = 0; i < object->mtncnt; i++) {
        object->motion[i] = -1;
    }
    for (i = 0; i < object->mtncnt; i++) {
        data->unkE8[i].unk00 = 0;
        data->unkE8[i].unk02 = 0;
        data->unkE8[i].unk04 = -1;
        data->unkE8[i].unk08 = -1;
    }
    chr = GwPlayer[m204_pusherPlayerNo].chr;
    object->model[0] = Hu3DModelRead(model | motion, attr | 4);
    object->model[1] = Hu3DModelRead((GwPlayer[m204_pusherPlayerNo].chr + 4) | 0x250000, attr);
    object->model[5] = Hu3DModelRead3(9, attr);
    object->model[2] = Hu3DModelRead(4, effectAttr);
    object->model[3] = Hu3DModelRead(4, effectAttr);
    object->model[4] = Hu3DModelRead(4, effectAttr);
    Hu3DModelScaleSet(object->model[2], 2.1f, 2.1f, 2.1f);
    Hu3DModelScaleSet(object->model[3], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(object->model[4], 2.2f, 2.2f, 2.2f);
    MgPlayerMotRead(object, 6, CharMotionDataNumGet(chr, 4), 1, 0x13);
    MgPlayerMotRead(object, 0, CharMotionDataNumGet(chr, 0), 1, 0);
    MgPlayerMotRead(object, 0xD, CharMotionDataNumGet(chr, 0x2F), 1, 0x78);
    data->unk57 = GwPlayer[m204_pusherPlayerNo].pad;
    data->unk59 = m204_pusherPlayerNo;
    data->unk50 = 0;
    object->func = m204_PusherObjMain;
    object->trans.x = 0.0f;
    object->trans.y = 700.0f;
    object->trans.z = -900.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelScaleSet(object->model[1], 1.5f, 1.5f, 1.5f);
    Hu3DMotionSpeedSet(object->model[1], 1.5f);
    Hu3DModelPosSet(object->model[5], object->trans.x, object->trans.y, object->trans.z);
}

void m204_PusherComInput(omObjData *object) {
    MgPlayerWork *data = object->data;
    f32 speeds[4] = { 0.8f, 0.85f, 0.9f, 1.0f };
    f32 ranges[4] = { 100.0f, 75.0f, 50.0f, 0.0f };
    omObjData *player;
    s32 difficulty;
    s32 target;
    f32 targetX;
    f32 targetZ;
    f32 maxY;
    f32 angle;
    s32 i;

    if (data->unk50 != 1) {
        return;
    }
    target = -1;
    difficulty = GwPlayer[data->unk59].cpu_difficulty;
    m204_padStkX = 0;
    m204_padBtn = 0;
    m204_padBtnDown = 0;
    targetX = targetZ = 0.0f;
    maxY = -10.0f;
    for (i = 0; i < mgPlayerObjNum; i++) {
        player = mgPlayerObjTbl[i];
        if (((MgPlayerWork *)player->data)->unkBE == 0 && maxY < player->trans.y) {
            targetX = player->trans.x;
            maxY = player->trans.y;
            targetZ = player->trans.z;
            target = i;
        }
    }
    if (m204_pusherComTarget == 5) {
        if (maxY < ranges[difficulty] + 300.0f) {
            if (rand8() > 128) {
                m204_pusherComTarget = 3;
            } else {
                m204_pusherComTarget = 4;
            }
        } else {
            m204_pusherComTarget = target;
        }
    }
    switch (m204_pusherComTarget) {
        case 0:
        case 1:
        case 2:
            angle = atan2df(targetX, targetZ - object->trans.z);
            if (angle > 0.0f) {
                m204_padStkX = speeds[difficulty] * 60.0f;
                if (data->unk3C > 30.0f) {
                    m204_padBtnDown |= A_BUTTON;
                }
                if (data->unk3C > angle) {
                    m204_padBtnDown |= A_BUTTON;
                }
            } else {
                m204_padStkX = speeds[difficulty] * -60.0f;
                if (data->unk3C < -30.0f) {
                    m204_padBtnDown |= A_BUTTON;
                }
                if (data->unk3C < angle) {
                    m204_padBtnDown |= A_BUTTON;
                }
            }
            break;
        case 3:
            m204_padStkX = speeds[difficulty] * 60.0f;
            if (data->unk3C > speeds[difficulty] * 55.0f) {
                m204_padBtnDown |= A_BUTTON;
            }
            break;
        case 4:
            m204_padStkX = speeds[difficulty] * -60.0f;
            if (data->unk3C < speeds[difficulty] * -55.0f) {
                m204_padBtnDown |= A_BUTTON;
            }
            break;
    }
    if (m204_padBtnDown != 0) {
        m204_pusherComTarget = 5;
    }
}

void m204_PusherObjMain(omObjData *object) {
    MgPlayerWork *data = object->data;
    s32 player = data->unk59;
    s32 pad = data->unk57;
    MgItemWork *boulderData;

    if (MgFlowStatGet() != MG_STATE_PLAY) {
        return;
    }
    m204_padBtnDown = HuPadBtnDown[pad];
    m204_padBtn = (u16)HuPadBtn[pad];
    m204_padStkX = HuPadStkX[pad];
    m204_padStkY = HuPadStkY[pad];
    HuPadStkY[pad] = 0;
    HuPadStkX[pad] = 0;
    HuPadBtnDown[pad] = 0;
    HuPadBtn[pad] = 0;
    if (GwPlayer[player].stat & 1) {
        m204_PusherComInput(object);
    }
    switch (data->unk50) {
        case 0:
            data->unk3C *= 0.8f;
            if (fabs(data->unk3C) < 1.0) {
                data->unk3C = 0.0f;
            }
            if (fabs(data->unk3C) < 1.0) {
                data->unk3C = 0.0f;
            }
            if (m204_boulderReadyF == 1) {
                data->unk50 = 1;
            }
            break;
        case 1:
            boulderData = m204_boulderObj->data;
            data->unk3C += m204_padStkX / 15.0f;
            if (data->unk3C > 60.0f) {
                data->unk3C = 60.0f;
            }
            if (data->unk3C < -60.0f) {
                data->unk3C = -60.0f;
            }
            if (m204_padBtnDown & A_BUTTON) {
                Hu3DMotionTimeSet(object->model[1], 0.0f);
                data->unk50 = 0;
                m204_boulderReadyF = 0;
                boulderData->unk3C = data->unk3C;
                boulderData->unk40 = rand8() / 64.0f + 7.0f;
                boulderData->unk78 = 0;
                boulderData->unk38 = -0.75f;
                HuAudPlayerFXPlay(0x31F, player);
            }
            m204_boulderObj->trans.x = sindf(data->unk3C) * 150.0f + 0.0f;
            m204_boulderObj->trans.y = 700.0f;
            m204_boulderObj->trans.z = cosdf(data->unk3C) * 150.0f + -900.0f;
            Hu3DModelPosSet(m204_boulderObj->model[1], m204_boulderObj->trans.x, 705.0f,
                            m204_boulderObj->trans.z);
            boulderData->unk3C = data->unk3C;
            break;
    }
    object->rot.y = data->unk3C;
    Hu3DModelRotSet(object->model[1], 0.0f, object->rot.y, 0.0f);
    HuPadBtnDown[pad] = m204_padBtnDown;
    HuPadBtn[pad] = m204_padBtn;
    HuPadStkX[pad] = m204_padStkX;
    HuPadStkY[pad] = m204_padStkY;
}

void m204_PusherWinObjMain(omObjData *object) {
    MgPlayerWork *data;
    f32 y;
    f32 velocity;
    f32 speedSq;

    if (MgPlayerMotStatGet(object) & 0x20) {
        data = object->data;
        velocity = data->unk38;
        y = object->trans.y;
        if (velocity > mgPlayerFallMax) {
            velocity = mgPlayerFallMax;
        }
        speedSq = velocity * velocity;
        if (data->unk38 >= 0.0f) {
            y += speedSq * -35.0f;
        } else {
            y += speedSq * 35.0f;
        }
        data->unk38 += mgPlayerGravity;
        if (y < 700.0f) {
            MgPlayerMotSet(object, 0);
            y = 700.0f;
        }
        object->trans.y = y;
    }
    switch (m204_pusherWinTimer) {
        case 1:
            Hu3DModelPosSet(object->model[2], object->trans.x - 10.0f, object->trans.y + 20.0f,
                            object->trans.z + 30.0f);
            Hu3DMotionTimeSet(object->model[2], 0.0f);
            Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            break;
        case 4:
            Hu3DModelPosSet(object->model[3], object->trans.x + 10.0f, object->trans.y + 40.0f,
                            object->trans.z + 30.0f);
            Hu3DMotionTimeSet(object->model[3], 0.0f);
            Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            break;
        case 6:
            Hu3DModelPosSet(object->model[4], object->trans.x, object->trans.y + 30.0f, object->trans.z + 30.0f);
            Hu3DMotionTimeSet(object->model[4], 0.0f);
            Hu3DModelAttrSet(object->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            break;
    }
    MgPlayerMotUpdate(object);
    m204_pusherWinTimer++;
}

void m204_BoulderObjInit(omObjData *object) {
    MgItemWork *data;
    s32 i;

    object->data = HuMemAllocTag(sizeof(MgItemWork), TAG_OVERLAY);
    memset(object->data, 0, sizeof(MgItemWork));
    data = object->data;
    object->model[0] = Hu3DModelRead2(0x250002, 0xAD9);
    object->model[1] = Hu3DModelRead3(9, 0xAD9);
    MgShadowMdlInit(object->model[1]);
    object->model[2] = Hu3DModelRead(4, 0x89D);
    object->model[3] = Hu3DModelRead(4, 0x89D);
    object->model[4] = Hu3DModelRead(4, 0x89D);
    object->model[5] = Hu3DModelRead(4, 0x89D);
    Hu3DModelScaleSet(object->model[2], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(object->model[3], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(object->model[4], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(object->model[5], 2.0f, 2.0f, 2.0f);
    object->func = MgItemObjMain;
    data->unk44 = 0.3f;
    data->unk48 = 70.0f;
    data->unk34 = 180.0f;
    data->unk3C = 0.0f;
    data->unk78 = 0;
    data->unk52 = 7;
    data->unk7C = 0;
    data->unk50 = 0;
    data->unk40 = 0.0f;
    data->unk74 = 0.5f;
    data->unk56 = m204_boulderNum;
    data->unk54 = 1;
    for (i = 0; i < 9; i++) {
        data->unk84[i] = NULL;
    }
    MgPlayerMapAttrSet(object, 0, 1);
    MgPlayerMapAttrSet(object, 1, 2);
    object->trans.x = 0.0f;
    object->trans.y = 700.0f;
    object->trans.z = -600.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    func_80088700_main(Hu3DData[object->model[1]].mtx, 2.0f, 2.0f, 2.0f);
    m204_boulderNum++;
    MgItemHookSet(data, 2, m204_BoulderHitHook);
    MgItemHookSet(data, 0, m204_BoulderUpdate);
    // The return value of slot 1 is ignored by MgItemObjMain.
    MgItemHookSet(data, 1, (void *)m204_BoulderAccel);
    MgItemHookSet(data, 4, m204_BoulderBounce);
    MgItemHookSet(data, 5, m204_BoulderWallHit);
    mgItemSpeedMax = 35.0f;
}

s32 m204_BoulderHitHook(omObjData *object) {
    return 1;
}

void m204_BoulderDustUpdate(omObjData *object) {
    MgItemWork *data = object->data;
    s32 slot = data->unk56;
    s32 time;
    f32 maxTime;
    f32 motTime;
    s32 i;

    if (m204_boulderStateTbl[slot] < 4) {
        if (m204_boulderStateTbl[slot] > 0) {
            time = MgFlowStatTimeGet();
            switch (time) {
                case 1:
                case 6:
                    maxTime = 0.0f;
                    for (i = 0; i < 4; i++) {
                        motTime = Hu3DData[object->model[i + 2]].motTime;
                        if (motTime == 0.0f) {
                            slot = i;
                            break;
                        }
                        if (maxTime < motTime) {
                            maxTime = motTime;
                            slot = i;
                        }
                    }
                    Hu3DModelPosSet(object->model[slot + 2], object->trans.x, time * 10.0f + object->trans.y,
                                    object->trans.z);
                    Hu3DMotionTimeSet(object->model[slot + 2], 0.0f);
                    Hu3DModelAttrSet(object->model[slot + 2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    break;
            }
        }
    }
}

s32 m204_BoulderUpdate(omObjData *object) {
    MgItemWork *data;
    s32 slot;
    s32 result = 0;
    f32 spin;
    f32 pan;
    s16 panning;
    s32 i;

    switch (MgFlowStatGet()) {
        case MG_STATE_OPENING:
        case MG_STATE_PLAY:
            break;
        case MG_STATE_FINISH:
            m204_BoulderDustUpdate(object);
            return 1;
        default:
            return 1;
    }
    data = object->data;
    slot = data->unk56;
    func_80088800_main(Hu3DData[object->model[0]].mtx, 0.0f, 90.0f, 0.0f);
    mtxRotCat(Hu3DData[object->model[0]].mtx, m204_boulderSpinTbl[slot], 0.0f, 0.0f);
    object->rot.y = data->unk3C;
    switch (m204_boulderStateTbl[slot]) {
        case 0:
            object->trans.x = 0.0f;
            object->trans.y = 1500.0f;
            object->trans.z = -900.0f;
            data->unk38 = 0.0f;
            data->unk40 = 0.0f;
            data->unk3C = 0.0f;
            m204_boulderSpinTbl[slot] = 0.0f;
            Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            if (m204_boulderNextNo == slot) {
                data->unk78++;
                if (data->unk78 >= 26) {
                    m204_boulderStateTbl[slot] = 1;
                    data->unk78 = 0;
                    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                }
            }
            result = 1;
            break;
        case 1:
            if (object->trans.y == 700.0f) {
                m204_boulderStateTbl[slot] = 2;
                m204_boulderReadyF = 1;
                m204_boulderObj = mgItemObjTbl[m204_boulderNextNo];
                m204_stageBounceVel = -mgPlayerJumpPower * 0.5f;
                for (i = 0; i < 4; i++) {
                    omVibrate(i, 2, 2, 20);
                }
            }
            break;
        case 2:
            if (m204_boulderReadyF == 0) {
                m204_boulderStateTbl[slot] = 3;
                m204_boulderNextNo++;
                if (m204_boulderNextNo == mgItemObjNum) {
                    m204_boulderNextNo = 0;
                }
                m204_boulderSeTbl[slot] = HuAudFXPlay(0x31D);
            }
            result = 1;
            break;
        case 3:
            spin = data->unk40 / 502.64f * 360.0f;
            m204_boulderSpinTbl[slot] += spin;
            if (m204_boulderSeTbl[slot] != -1) {
                if (data->unk38 > 0.0f) {
                    HuAudFXVolSet(m204_boulderSeTbl[slot], 0x7F);
                } else {
                    HuAudFXVolSet(m204_boulderSeTbl[slot], 0x60);
                }
                pan = object->trans.x / 400.0f;
                if (pan > 1.0f) {
                    pan = 1.0f;
                } else if (pan < -1.0f) {
                    pan = -1.0f;
                }
                panning = pan * 32.0f + 64.0f;
                HuAudFXPanning(m204_boulderSeTbl[slot], panning);
            }
            if (object->trans.z > 1400.0f) {
                m204_boulderStateTbl[slot] = 4;
                data->unk40 = 0.0f;
                m204_boulderSpinTbl[slot] = 0.0f;
                Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(object->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(object->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                HuAudFXStop((s16)m204_boulderSeTbl[slot]);
                m204_boulderSeTbl[slot] = -1;
            }
            break;
        case 4:
            data->unk78++;
            if (data->unk78 >= 11) {
                m204_boulderStateTbl[slot] = 0;
                data->unk78 = 0;
            }
            result = 1;
            break;
    }
    return result;
}

void m204_BoulderAccel(omObjData *arg0) {
    MgItemWork *data = arg0->data;

    data->unk40 += 0.3f;
    data->unk78++;
    if (35.0f < data->unk40) {
        data->unk40 = 35.0f;
    }
}

s32 m204_BoulderBounce(omObjData *object) {
    MgItemWork *data = object->data;
    s32 slot = data->unk56;
    f32 maxTime;
    f32 motTime;
    s32 i;

    if (m204_boulderStateTbl[slot] == 3 && data->unk38 > 0.4f) {
        slot = 0;
        maxTime = 0.0f;
        for (i = 0; i < 4; i++) {
            motTime = Hu3DData[object->model[i + 2]].motTime;
            if (motTime == 0.0f) {
                slot = i;
                break;
            }
            if (maxTime < motTime) {
                maxTime = motTime;
                slot = i;
            }
        }
        Hu3DModelPosSet(object->model[slot + 2], object->trans.x, object->trans.y + 10.0f, object->trans.z);
        Hu3DMotionTimeSet(object->model[slot + 2], 0.0f);
        Hu3DModelAttrSet(object->model[slot + 2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
    data->unk38 = rand8() / 500.0f + 0.0f;
    return 1;
}

s32 m204_BoulderWallHit(omObjData *object) {
    MgItemWork *data = object->data;
    Vec pos;
    Vec dir;
    Vec out;
    f32 dot;
    s32 i;

    pos.x = mgWallNorTbl[0].x;
    pos.y = dir.y = 0.0f;
    pos.z = mgWallNorTbl[0].z;
    dir.x = sindf(data->unk3C + 180.0f);
    dir.z = cosdf(data->unk3C + 180.0f);
    dot = HuVecDot3F(&pos, &dir);
    pos.x = dot * pos.x;
    pos.z = dot * pos.z;
    HuVecSubtract(&out, &pos, &dir);
    HuVecAdd(&out, &pos, &out);
    data->unk3C = atan2df(out.x, out.z);
    for (i = 0; i < 4; i++) {
        omVibrate(i, 2, 3, 10);
    }
    HuAudFXPanning(HuAudFXPlay(0x31E), pos.x > 0.0f ? 0x20 : 0x60);
    return 1;
}
