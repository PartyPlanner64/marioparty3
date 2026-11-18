#include "common.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/hmfcoll.h"
#include "game/input.h"
#include "game/mallocblock.h"
#include "game/object.h"
#include "game/wipe.h"
#include "gcc/memory.h"
#include "humath.h"
#include "math.h"
#include "game/overlays/minigame.h"

extern s32 omCharModelNoTbl[][6];
extern f32 CFanOfs;
extern u8 storySceneNo;
extern u8 Hu3DBufNo;
extern f32 CFanLen;
extern u8 omAllPauseF;

Vec m270_startPosTbl[3] = {
    { 4500.0f, 0.0f, 7300.0f },
    { 6500.0f, 0.0f, 2300.0f },
    { 5500.0f, 0.0f, 6300.0f },
};
f32 m270_startRotX = 180.0f; /* Unreferenced. */
f32 m270_startRotY = 180.0f;
f32 m270_startRotZ = 0.0f; /* Unreferenced. */
f32 m270_speedMax = 80.0f;
f32 m270_throttleAccel = 1.1f;
f32 m270_speedDecay = 0.975f;
f32 m270_hitDecayUnused = 0.925f; /* Unreferenced. */
f32 m270_hitDecay = 0.925f;
f32 m270_hitDecayHard = 0.775f;
Vec m270_moveDelta = { 0.0f, 0.0f, 0.0f };
Vec m270_prevPos = { 0.0f, 0.0f, 0.0f };
Vec m270_bumpDir = { 0.0f, 0.0f, 0.0f };
f32 m270_bumpPower = 0.0f;
f32 m270_throttle = 0.1f;
f32 m270_waveTimeA = 0.0f;
f32 m270_wavePeriodA = 0.2f;
f32 m270_waveLenA = 50.0f;
f32 m270_waveAmpA = 55.0f;
f32 m270_waveTimeB = 0.0f;
f32 m270_wavePeriodB = 0.13f;
f32 m270_waveLenB = 40.0f;
f32 m270_waveAmpB = 40.0f;
s32 m270_goalF = 0;
f32 m270_waterScrollU = 0.0f;
f32 m270_waterScrollV = 0.0f;
f32 m270_cameraDist = 300.0f;
f32 m270_headScale = 2.0f;
s32 m270_engineSeNo = -1;
s32 m270_courseNo = 0;
Vec m270_course0ObstaclePosTbl[17] = {
    { 3800.0f, 112.5f, 7200.0f },
    { 5200.0f, 112.5f, 7200.0f },
    { 5200.0f, 112.5f, 4600.0f },
    { 3700.0f, 112.5f, 2700.0f },
    { 4600.0f, 112.5f, -900.0f },
    { 3500.0f, 112.5f, -2800.0f },
    { 5900.0f, 112.5f, -7100.0f },
    { 1600.0f, 112.5f, -8400.0f },
    { -1100.0f, 112.5f, -9100.0f },
    { -3400.0f, 112.5f, -8400.0f },
    { -5200.0f, 112.5f, -9400.0f },
    { -4500.0f, 112.5f, -3600.0f },
    { -3600.0f, 112.5f, -1300.0f },
    { -4700.0f, 112.5f, 600.0f },
    { -3700.0f, 112.5f, 3100.0f },
    { -5200.0f, 112.5f, 7300.0f },
    { -3800.0f, 112.5f, 7200.0f },
};
Vec m270_course0ObstacleRotTbl[17] = {
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 225.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
};
s8 m270_course0ObstacleTypeTbl[18] = { 0, 0, 1, 2, 1, 1, 0, 1, 2, 1, 0, 1, 2, 1, 2, 0, 0, -1 };
Vec m270_course1ObstaclePosTbl[19] = {
    { 5800.0f, 112.5f, 2100.0f },
    { 7200.0f, 112.5f, 2100.0f },
    { 5700.0f, 112.5f, -1000.0f },
    { 7200.0f, 112.5f, -3500.0f },
    { 6600.0f, 112.5f, -7000.0f },
    { 1900.0f, 112.5f, -6200.0f },
    { 4500.0f, 112.5f, -5700.0f },
    { 3200.0f, 112.5f, -900.0f },
    { 1500.0f, 112.5f, 3700.0f },
    { 200.0f, 112.5f, 0.0f },
    { 900.0f, 112.5f, -2100.0f },
    { 1300.0f, 112.5f, -7400.0f },
    { -2700.0f, 112.5f, -9200.0f },
    { -5400.0f, 112.5f, -7900.0f },
    { -3300.0f, 112.5f, -4200.0f },
    { -3500.0f, 112.5f, -2000.0f },
    { -1900.0f, 112.5f, 300.0f },
    { -3200.0f, 112.5f, 5300.0f },
    { -1800.0f, 112.5f, 5200.0f },
};
Vec m270_course1ObstacleRotTbl[19] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 180.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
};
s8 m270_course1ObstacleTypeTbl[20] = { 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 2, 1, 0, 2, 0, 1, 0, 0, -1 };
Vec m270_course2ObstaclePosTbl[18] = {
    { 4600.0f, -150.0f, 6200.0f },
    { 6400.0f, -150.0f, 6200.0f },
    { 5300.0f, -150.0f, 1000.0f },
    { 7200.0f, 0.0f, -4000.0f },
    { 3000.0f, -150.0f, -6800.0f },
    { 2100.0f, -150.0f, -1700.0f },
    { 2600.0f, -150.0f, 2300.0f },
    { 2100.0f, 0.0f, 7200.0f },
    { -300.0f, -150.0f, 8200.0f },
    { -2800.0f, -150.0f, 8000.0f },
    { -3600.0f, -150.0f, 4600.0f },
    { -4600.0f, 0.0f, 200.0f },
    { -800.0f, 0.0f, -3800.0f },
    { -1500.0f, -150.0f, -7000.0f },
    { -6200.0f, -150.0f, -3600.0f },
    { -5400.0f, -150.0f, -200.0f },
    { -7500.0f, -150.0f, 3900.0f },
    { -5500.0f, -150.0f, 3900.0f },
};
Vec m270_course2ObstacleRotTbl[18] = {
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { -40.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { -40.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { -40.0f, 45.0f, 0.0f },
    { -40.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
};
s8 m270_course2ObstacleTypeTbl[19] = { 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, -1 };
MinigameFlow m270_mgFlow = {
    MG_STATE_OPENING, 7, MG_TIMER_COUNT_DOWN, MG_TIME_DISP_RECORD, FALSE, MG_GAUGE_NONE, MG_RESULT_WIN_1, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    75, -1, 5400, 90, 135
};
Vec m270_lightDir = { 101.0f, -51.0f, 38.0f }; /* Unreferenced. */
f32 m270_lakituOfsX = -2000.0f;
f32 m270_lakituRotZ = -20.0f;
f32 m270_signalSwingAngle = -90.0f;
f32 m270_signalSwingAmp = 20.0f;
f32 m270_lakituLeaveY = 5.0f;
s32 m270_obstacleMdlFileTbl[3][3] = {
    { 0x000A0000, 0x000A008E, 0x000A00A5 },
    { 0x000A00C3, 0x000A00E7, 0x000A00CE },
    { 0x000A0086, 0x000A0059, 0x000A0154 },
};
s32 m270_obstacleMotFileTbl[3][3] = {
    { 0x000A0017, 0x000A0095, 0x000A00B2 },
    { 0x000A00BC, 0x000A00ED, 0x000A00D0 },
    { 0x000A0088, 0x000A005A, 0x000A0154 },
};

Vec m270_wakePosTbl[6] BSS;
f32 m270_wakeSpeedTbl[6] BSS;
Vec m270_wakeDirTbl[6] BSS;
f32 m270_wakeScaleTbl[6] BSS;
s32 m270_boatType BSS;
u8 m270_boatTypePad[4] BSS; /* Unreferenced. */
Vec m270_moveHistTbl[20] BSS;
s32 m270_btnSave BSS;
s32 m270_stkXSave BSS;
u8 m270_stkXSavePad[0x30] BSS; /* Unreferenced. */

void m270_CameraObjMain(omObjData *object);
void m270_WaterWaveUpdate(omObjData *object);
void m270_ObstacleDispUpdate(omObjData *object);
void m270_MainObjMain(omObjData *object);
void m270_MainObjInit(omObjData *object);
void m270_PlayerInit(omObjData *object, u16 player);
void m270_Player0ObjInit(omObjData *object);
void m270_PlayerObjMain(omObjData *object);
void m270_PlayerTiltUpdate(omObjData *object, f32 x, f32 z);
f32 m270_PlayerCollide(omObjData *object, f32 x, f32 y, f32 z);
void m270_GoalCheck(omObjData *object);
void m270_HudObjInit(omObjData *object);
void m270_NormalCalc(Vec *origin, Vec *p, Vec *q, Vec *out);

void m270_ObjectSetup(void) {
    u8 camIndex;

    MapCollInit(50);
    Hu3DQuadPoolInit(&mgQuadPool, 0x40);
    Hu3DSprModelInit(32);
    omInitObjMan(50, 0);
    omGameSysInit();
    MgFieldStatClear();
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 20.0f, 80.0f, 8000.0f);
    CFanLen = 20000.0f;
    CFanOfs = 12000.0f;
    Hu3DBGColorSet(0, 0, 64);
    Hu3DGLightMaxSet(2);
    Hu3DGLightDirSet(1, -98.0f, 14.0f, 66.0f);
    Hu3DGLightDirSet(2, -84.0f, 83.0f, 12.0f);
    Hu3DGLightColorSet(1, 64, 64, 64);
    Hu3DGLightColorSet(2, 230, 230, 230);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    MgPlayerParamReset();
    mgPlayerFallInit = 0.0f;
    MgMapBaseSet(mgMapObjNum);
    mgMapObjTbl[mgMapObjNum++] = omAddObj(1, 40, 0, -1, m270_MainObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(3, 13, 0, -1, m270_Player0ObjInit);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omSetStatBit(omAddObj(4, 0, 0, -1, m270_CameraObjMain), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omSetStatBit(omAddObj(100, 0, 0, -1, m270_HudObjInit), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    mgPlayerAccel = 10.0f;
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    MgFlowInit(&m270_mgFlow);
    mgFlowSeqNo = 50;
    mgFlowSeqTime = 72;
    m270_courseNo = storySceneNo;
}

void m270_CameraObjMain(omObjData *object) {
    MgPlayerWork *work = mgPlayerObjTbl[0]->data;
    f32 angle = work->unk3C;
    f32 dist = m270_throttle * 100.0f + m270_cameraDist + work->unk40 * 2.0f;

    Center.x = mgPlayerObjTbl[0]->trans.x + sindf(angle) * dist;
    Center.y = 0.0f;
    Center.z = mgPlayerObjTbl[0]->trans.z + cosdf(angle) * dist;
}

void m270_ExitObjMain(omObjData *object) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

f32 m270_WaveHeightGet(f32 x, f32 z) {
    f32 height;

    height = sindf((m270_waveTimeA / m270_wavePeriodA - HuSqrtf(x * x + z * z) / m270_waveLenA) *
                   (2 * M_PI)) *
             m270_waveAmpA;
    x += 8000.0f;
    z += 5000.0f;
    height += sindf((m270_waveTimeB / m270_wavePeriodB - HuSqrtf(x * x + z * z) / m270_waveLenB) *
                    (2 * M_PI)) *
              m270_waveAmpB;
    return height / 2.0f;
}

void m270_WaterWaveUpdate(omObjData *object) {
    HmfData *hmf;
    Vtx *vtx;
    Vtx *src;
    f32 boatX;
    f32 boatZ;
    f32 x, z;
    f32 height;
    s32 i;

    boatX = mgPlayerObjTbl[0]->trans.x;
    boatZ = mgPlayerObjTbl[0]->trans.z;
    hmf = Hu3DData[object->model[1]].hmf;
    vtx = hmf->unk44[Hu3DBufNo];
    src = hmf->unk40;
    for (i = 0; i < hmf->unk18; i++, vtx++, src++) {
        x = src->v.ob[0] + boatX;
        z = src->v.ob[2] + boatZ;
        height = sindf((m270_waveTimeA / m270_wavePeriodA - HuSqrtf(x * x + z * z) / m270_waveLenA) *
                       (2 * M_PI)) *
                 m270_waveAmpA;
        x += 8000.0f;
        z += 5000.0f;
        height = (height + sindf((m270_waveTimeB / m270_wavePeriodB - HuSqrtf(x * x + z * z) / m270_waveLenB) *
                                 (2 * M_PI)) *
                               m270_waveAmpB) /
                 2.0f;
        vtx->v.ob[1] = height;
        if (height > 0.0) {
            height = 256.0f - height;
            vtx->v.cn[1] = vtx->v.cn[0] = 170;
            vtx->v.cn[2] = height;
        } else {
            height = 175.0f - height;
            if (height > 255.0f) {
                height = 255.0f;
            }
            vtx->v.cn[0] = height;
            vtx->v.cn[1] = height;
            vtx->v.cn[2] = 255;
        }
    }
    if (omPauseChk() + omAllPauseF == 0) {
        m270_waveTimeA += 0.11f;
        m270_waveTimeB += 0.09f;
        Hu3DModelPosSet(object->model[1], boatX, 0.0f, boatZ);
    }
    Hu3DModelTexScroll(object->model[1], m270_waterScrollU, m270_waterScrollV, 32, 32);
    if (HuPadBtn[1] & U_CBUTTONS) {
        m270_wavePeriodA += 0.001f;
    }
    if (HuPadBtn[1] & D_CBUTTONS) {
        m270_wavePeriodA -= 0.001f;
    }
    if (m270_wavePeriodA < 0.01f) {
        m270_wavePeriodA = 0.01f;
    }
    if (HuPadBtn[1] & R_CBUTTONS) {
        m270_waveLenA += 0.1f;
    }
    if (HuPadBtn[1] & L_CBUTTONS) {
        m270_waveLenA -= 0.1f;
    }
    if (HuPadBtn[1] & R_TRIG) {
        m270_waveAmpA -= 0.1f;
    }
    if (HuPadBtn[1] & L_TRIG) {
        m270_waveAmpA += 0.1f;
    }
    m270_wavePeriodB = m270_wavePeriodA - 0.3f;
    m270_waveLenB = m270_waveLenA - 5.0f;
    m270_waveAmpB = m270_waveAmpA - 20.0f;
}

void m270_CameraWinUpdate(void) {
    omObjData *obj;

    if (m270_goalF == 1) {
        obj = mgPlayerObjTbl[0];
        Center.x -= (Center.x - obj->trans.x) * 0.25f;
        Center.z -= (Center.z - obj->trans.z) * 0.25f;
        Center.y -= (Center.y - obj->trans.y) * 0.25f;
        CZoom *= 0.95f;
        if (CZoom < 2000.0f) {
            CZoom = 2000.0f;
        }
    }
}

void m270_LakituStartUpdate(omObjData *object) {
    f32 x, y, z;
    s32 time;

    x = m270_startPosTbl[m270_courseNo].x + 400.0f + m270_lakituOfsX;
    y = m270_startPosTbl[m270_courseNo].y + 500.0f;
    z = m270_startPosTbl[m270_courseNo].z;
    Hu3DModelPosSet(object->model[3], x, y, z);
    x += cosdf(m270_lakituRotZ + 90.0f) * 77.65f;
    Hu3DModelPosSet(object->model[2], x, y + sindf(m270_lakituRotZ + 90.0f) * 77.65f, z + 140.0f);
    Hu3DModelRotSet(object->model[3], 0.0f, 0.0f, m270_lakituRotZ);
    Hu3DModelRotSet(object->model[2], 0.0f, 0.0f, sindf(m270_signalSwingAngle) * m270_signalSwingAmp);
    m270_lakituOfsX *= 0.9f;
    if (m270_lakituOfsX > -300.0f) {
        m270_signalSwingAngle += 10.0f;
        m270_signalSwingAmp *= 0.98f;
        m270_lakituRotZ *= 0.8f;
    }
    time = MgFlowStatTimeGet();
    if (MgFlowStatGet() == MG_STATE_OPENING) {
        if (time == 60) {
            Hu3DMotionAttrSet(object->model[2], 1, 0);
        }
    } else if (time == 15.0 || time == 45.0) {
        HuAudFXPlay(0x426);
    }
}

void m270_LakituLeaveUpdate(omObjData *object) {
    f32 x, y, z;

    if (m270_lakituLeaveY < 2000.0f) {
        x = m270_startPosTbl[m270_courseNo].x + 400.0f;
        y = m270_startPosTbl[m270_courseNo].y + 500.0f + m270_lakituLeaveY;
        z = m270_startPosTbl[m270_courseNo].z;
        m270_lakituLeaveY *= 1.15f;
        Hu3DModelPosSet(object->model[3], x, y, z);
        Hu3DModelPosSet(object->model[2], x, y + 77.65f, z + 140.0f);
    } else {
        Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
}

void m270_ObstacleDispUpdate(omObjData *object) {
    f32 x, y, z;
    f32 rotX, rotY, rotZ;
    f32 dx, dz;
    f32 scale;
    s32 type;
    s32 count0;
    s32 count1;
    s32 count2;
    s32 i;

    count2 = 0;
    count1 = 0;
    count0 = 0;
    for (i = 0; i < 30; i++) {
        Hu3DModelAttrSet(object->model[i + 9], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    for (i = 0;; i++) {
        switch (m270_courseNo) {
            case 0:
                type = m270_course0ObstacleTypeTbl[i];
                x = m270_course0ObstaclePosTbl[i].x;
                y = m270_course0ObstaclePosTbl[i].y;
                z = m270_course0ObstaclePosTbl[i].z;
                rotX = m270_course0ObstacleRotTbl[i].x;
                rotY = m270_course0ObstacleRotTbl[i].y;
                rotZ = m270_course0ObstacleRotTbl[i].z;
                break;
            case 1:
                type = m270_course1ObstacleTypeTbl[i];
                x = m270_course1ObstaclePosTbl[i].x;
                y = m270_course1ObstaclePosTbl[i].y;
                z = m270_course1ObstaclePosTbl[i].z;
                rotX = m270_course1ObstacleRotTbl[i].x;
                rotY = m270_course1ObstacleRotTbl[i].y;
                rotZ = m270_course1ObstacleRotTbl[i].z;
                break;
            case 2:
                type = m270_course2ObstacleTypeTbl[i];
                x = m270_course2ObstaclePosTbl[i].x;
                y = m270_course2ObstaclePosTbl[i].y;
                z = m270_course2ObstaclePosTbl[i].z;
                rotX = m270_course2ObstacleRotTbl[i].x;
                rotY = m270_course2ObstacleRotTbl[i].y;
                rotZ = m270_course2ObstacleRotTbl[i].z;
                break;
        }
        if (type == -1) {
            break;
        }
        dx = Center.x - x;
        dz = Center.z - z;
        if (HuSqrtf(dx * dx + dz * dz) < 2500.0f) {
            switch (type) {
                case 0:
                    if (count0 < 5) {
                        Hu3DModelPosSet(object->model[count0 + 9], x, y, z);
                        Hu3DModelRotSet(object->model[count0 + 9], rotX, rotY, rotZ);
                        Hu3DModelScaleSet(object->model[count0 + 9], 1.5f, 1.5f, 1.5f);
                        Hu3DModelAttrSet(object->model[count0 + 9], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        count0++;
                    }
                    break;
                case 1:
                    if (count1 < 5) {
                        Hu3DModelPosSet(object->model[count1 + 19], x, y, z);
                        Hu3DModelRotSet(object->model[count1 + 19], rotX, rotY, rotZ);
                        Hu3DModelScaleSet(object->model[count1 + 19], 1.5f, 1.5f, 1.5f);
                        Hu3DModelAttrSet(object->model[count1 + 19], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        count1++;
                    }
                    break;
                case 2:
                    if (count2 < 5) {
                        if (m270_courseNo == 1) {
                            scale = 0.8f;
                        } else {
                            scale = 1.5f;
                        }
                        Hu3DModelPosSet(object->model[count2 + 29], x, y, z);
                        Hu3DModelRotSet(object->model[count2 + 29], rotX, rotY, rotZ);
                        Hu3DModelScaleSet(object->model[count2 + 29], scale, scale, scale);
                        Hu3DModelAttrSet(object->model[count2 + 29], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        count2++;
                    }
                    break;
            }
        }
    }
}

void m270_MainObjMain(omObjData *object) {
    MgPlayerWork *work;
    s32 time;
    s32 i;

    m270_WaterWaveUpdate(object);
    if (omPauseChk() + omAllPauseF != 0) {
        return;
    }
    time = MgFlowStatTimeGet();
    switch (MgFlowMain()) {
        case 0:
            if (time == 5) {
                HuAudFXPlay(0x424);
                m270_engineSeNo = HuAudPlayerFXPlay(m270_boatType + 0x428, 0);
            }
        case 1:
            m270_LakituStartUpdate(object);
            break;
        case 2:
            if (time == 0) {
                HuAudFXPlay(0x427);
            }
            m270_LakituLeaveUpdate(object);
            break;
        case 3:
            if (time == 15.0) {
                HuAudFXFadeOut(m270_engineSeNo, 30);
                m270_engineSeNo = -1;
            }
            if (time == 1) {
                m270_speedDecay -= 0.025f;
            }
            m270_cameraDist *= 0.95f;
            m270_mgFlow.resultType = MG_RESULT_NONE;
        case 4:
            if (mgFlowResultF == 1) {
                if (m270_goalF == 0) {
                    HuAudSeqPlay(0x6B);
                } else if (m270_mgFlow.newRecord == TRUE) {
                    HuAudSeqPlay(0x6A);
                } else {
                    HuAudSeqPlay(0x65);
                }
            }
            break;
        case 5:
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            object->func = m270_ExitObjMain;
            HuAudFXAllFadeOut(30);
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
        object->func = m270_ExitObjMain;
    }
    m270_ObstacleDispUpdate(object);
}

void m270_MainObjInit(omObjData *object) {
    MgMapWork *work;
    s16 motion;

    object->model[0] = Hu3DModelRead2((m270_courseNo + 3) | 0x670000, 0x4B9);
    object->model[1] = Hu3DModelRead2(0x670006, 0x4A9);
    object->model[2] = Hu3DModelRead2(0x670007, 0x8C9);
    object->model[3] = Hu3DModelRead2(0xA0089, 0x8C9);
    object->model[9] = Hu3DModelRead2(m270_obstacleMdlFileTbl[m270_courseNo][0], 0x4DD);
    object->model[10] = Hu3DModelLink(object->model[9]);
    object->model[11] = Hu3DModelLink(object->model[9]);
    object->model[12] = Hu3DModelLink(object->model[9]);
    motion = Hu3DMotionModelRead(m270_obstacleMotFileTbl[m270_courseNo][0]);
    Hu3DMotionModelSet(object->model[9], motion);
    Hu3DMotionModelSet(object->model[10], motion);
    Hu3DMotionModelSet(object->model[11], motion);
    Hu3DMotionModelSet(object->model[12], motion);
    Hu3DMotionAttrSet(object->model[9], 2, 2);
    Hu3DMotionAttrSet(object->model[10], 2, 2);
    Hu3DMotionAttrSet(object->model[11], 2, 2);
    Hu3DMotionAttrSet(object->model[12], 2, 2);
    object->model[19] = Hu3DModelRead2(m270_obstacleMdlFileTbl[m270_courseNo][1], 0x4DD);
    object->model[20] = Hu3DModelLink(object->model[19]);
    object->model[21] = Hu3DModelLink(object->model[19]);
    object->model[22] = Hu3DModelLink(object->model[19]);
    motion = Hu3DMotionModelRead(m270_obstacleMotFileTbl[m270_courseNo][1]);
    Hu3DMotionModelSet(object->model[19], motion);
    Hu3DMotionModelSet(object->model[20], motion);
    Hu3DMotionModelSet(object->model[21], motion);
    Hu3DMotionModelSet(object->model[22], motion);
    Hu3DMotionAttrSet(object->model[19], 2, 2);
    Hu3DMotionAttrSet(object->model[20], 2, 2);
    Hu3DMotionAttrSet(object->model[21], 2, 2);
    Hu3DMotionAttrSet(object->model[22], 2, 2);
    object->model[29] = Hu3DModelRead2(m270_obstacleMdlFileTbl[m270_courseNo][2], 0x4DD);
    object->model[30] = Hu3DModelLink(object->model[29]);
    object->model[31] = Hu3DModelLink(object->model[29]);
    object->model[32] = Hu3DModelLink(object->model[29]);
    motion = Hu3DMotionModelRead(m270_obstacleMotFileTbl[m270_courseNo][2]);
    Hu3DMotionModelSet(object->model[29], motion);
    Hu3DMotionModelSet(object->model[30], motion);
    Hu3DMotionModelSet(object->model[31], motion);
    Hu3DMotionModelSet(object->model[32], motion);
    Hu3DMotionAttrSet(object->model[29], 2, 2);
    Hu3DMotionAttrSet(object->model[30], 2, 2);
    Hu3DMotionAttrSet(object->model[31], 2, 2);
    Hu3DMotionAttrSet(object->model[32], 2, 2);
    object->trans.x = 0.0f;
    object->trans.y = 0.0f;
    object->trans.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    work = object->data = HuMemAllocTag(0xB4, TAG_OVERLAY);
    memset(work, 0, 0xB4);
    object->func = m270_MainObjMain;
    work->unk03 = 1;
    Center.x = -224.0f;
    Center.y = 300.0f;
    Center.z = 300.0f;
    CRot.x = 330.0f;
    CRot.y = 5.0f;
    CZoom = 4500.0f;
    MgMapTiltOn(object);
    MgMapAttrSet(object, 1, 0.0f);
    MgMapFrictionSet(object, 0.2f);
    MgMapAccelSet(object, mgPlayerAccel);
    MgMapSlideSet(object, 25.0f);
    work->unk04 = 0;
    Hu3DLLightCreate(object->model[1], 1);
    Hu3DLLightDirSet(object->model[1], -66.0f, -99.0f, -9.0f);
    Hu3DModelObjAttrSet(object->model[1], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(object->model[1]);
    Hu3DModelVtxBufMake(object->model[1]);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DModelPosSet(object->model[2], m270_startPosTbl[m270_courseNo].x + 500.0f,
                    m270_startPosTbl[m270_courseNo].y + 500.0f,
                    m270_startPosTbl[m270_courseNo].z);
    Hu3DModelPosSet(object->model[3], m270_startPosTbl[m270_courseNo].x + 500.0f,
                    m270_startPosTbl[m270_courseNo].y + 500.0f,
                    m270_startPosTbl[m270_courseNo].z);
    Hu3DModelScaleSet(object->model[2], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(object->model[3], 2.0f, 2.0f, 2.0f);
    Hu3DMotionAttrSet(object->model[2], 1, 1);
    Hu3DMotionAttrSet(object->model[3], 2, 2);
}

// Defined here (not at the top) so that the initialiser strings are emitted into
// .rodata after the preceding functions' constants, matching the original layout.
char *m270_chrHeadNameTbl[11] = {
    "atama_2",
    "c001_000-atama_2",
    "C002_000b-bmerge10_1",
    "c003_000-head_1",
    "Luigi1-atama_1",
    "c005_000-bmerge1",
    "c001_000-atama_2",
    "C002_000b-bmerge10_1",
    "atama_2",
    "atama_2",
    "atama_2",
};
s8 m270_startSlotTbl[4] = { -1, -1, -1, -1 };
s16 m270_wakeMdl0 = -1;
s16 m270_wakeMdl1 = -1;
s16 m270_wakeMdl2 = -1;
s32 m270_wakeNo = 0;
s16 m270_stickHistTbl[20] = { 0 };
s32 m270_moveHistNo = 0;
s32 m270_stickHistNo = 0;
f32 m270_unusedScale = 1.0f; /* Unreferenced. */
s32 m270_vibTimer = 0;
s32 m270_goalSeNo = -1;
Vec m270_goalPlaneTbl[3][3] = {
    { { -4000.0f, 100.0f, 7000.0f }, { -5000.0f, 100.0f, 7000.0f }, { 0.0f, -500.0f, 7000.0f } },
    { { -2000.0f, 100.0f, 5000.0f }, { -3000.0f, 100.0f, 5000.0f }, { 0.0f, -500.0f, 5000.0f } },
    { { -5800.0f, 100.0f, 4000.0f }, { -7200.0f, 100.0f, 4000.0f }, { 0.0f, -500.0f, 4000.0f } },
};

void m270_PlayerInit(omObjData *object, u16 player) {
    MgPlayerWork *work;
    s32 tag;
    s32 charModel;
    s32 model;
    s32 motion;
    s32 boatType;
    s32 i;

    tag = 0x6D9;
    for (i = 0; i < object->mdlcnt; i++) {
        object->model[i] = 0;
    }
    object->data = HuMemAllocTag(0x15C, TAG_OVERLAY);
    memset(object->data, 0, 0x15C);
    work = object->data;
    motion = omCharModelNoTbl[GwPlayer[player].chr][2];
    model = omCharModelNoTbl[GwPlayer[player].chr][0];
    charModel = Hu3DModelRead(model | motion, tag | 4);
    m270_boatType = boatType = mgModeCoinRate;
    object->model[0] = Hu3DModelRead(boatType | 0x670000, tag);
    Hu3DModelObjCopy(charModel, m270_chrHeadNameTbl[GwPlayer[player].chr], object->model[0],
                       "atama_2");
    switch (boatType) {
        case 0:
            m270_speedMax = 80.0f;
            m270_throttleAccel = 1.1f;
            m270_speedDecay = 0.975f;
            m270_hitDecay = 0.925f;
            m270_hitDecayHard = 0.775f;
            break;
        case 1:
            m270_speedMax = 85.0f;
            m270_throttleAccel = 1.025f;
            m270_speedDecay = 0.97f;
            m270_hitDecay = 0.92f;
            m270_hitDecayHard = 0.76f;
            break;
        case 2:
        default:
            m270_speedMax = 90.0f;
            m270_throttleAccel = 1.0125f;
            m270_speedDecay = 0.96f;
            m270_hitDecay = 0.9125f;
            m270_hitDecayHard = 0.75f;
            break;
    }
    work->unk57 = GwPlayer[player].pad;
    object->func = m270_PlayerObjMain;
    work->unk52 = 0;
    work->unkB4 = 1.0f;
    work->unk8C = 65536.0f;
    work->unkD0 = 0xFFFF;
    work->unk4C = 0.5f;
    work->unkCC = 1.0f;
    work->unk60 = 0.0f;
    MgPlayerRadiusSet(object, 100.0f);
    MgPlayerHeightSet(object, 150.0f);
    MgPlayerPunchRadiusSet(object, 20.0f);
    MgPlayerAttackParamSet(object, 30.0f);
    MgPlayerVelYSet(object, 1000.0f);
    work->unk9C = work->unkA0 = work->unkA4 = 0.0f;
    work->unk59 = player;
    work->unkC3 = -1;
    work->unkC4 = -1;
    work->unkAC = work->unkB0 = 1.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    for (i = 0; i < 6; i++) {
        if (i == 3 || i == 0) {
            if (m270_wakeMdl0 < 0) {
                object->model[i + 1] = m270_wakeMdl0 = Hu3DModelRead(0x440006, 0x889);
            } else {
                object->model[i + 1] = Hu3DModelLink(m270_wakeMdl0);
            }
        } else if (i == 4 || i == 1) {
            if (m270_wakeMdl1 < 0) {
                object->model[i + 1] = m270_wakeMdl1 = Hu3DModelRead(0x440007, 0x889);
            } else {
                object->model[i + 1] = Hu3DModelLink(m270_wakeMdl1);
            }
        } else {
            if (m270_wakeMdl2 < 0) {
                object->model[i + 1] = m270_wakeMdl2 = Hu3DModelRead(0x440008, 0x889);
            } else {
                object->model[i + 1] = Hu3DModelLink(m270_wakeMdl2);
            }
        }
        Hu3DModelObjAttrSet(object->model[i + 1], 0x70000000, 0x70000000);
    }
    if (boatType == 2) {
        for (i = 0; i < 6; i++) {
            if (i == 3 || i == 0) {
                object->model[i + 7] = Hu3DModelLink(m270_wakeMdl0);
            } else if (i == 4 || i == 1) {
                object->model[i + 7] = Hu3DModelLink(m270_wakeMdl1);
            } else {
                object->model[i + 7] = Hu3DModelLink(m270_wakeMdl2);
            }
            Hu3DModelObjAttrSet(object->model[i + 7], 0x70000000, 0x70000000);
        }
    }
    work = object->data;
    work->unk3C = m270_startRotY;
    MgPlayerMapAttrSet(object, 0, 2);
    do {
        i = rand8() & 3;
    } while (m270_startSlotTbl[i] != -1);
    object->trans.x = m270_startPosTbl[m270_courseNo].x;
    object->trans.y = m270_startPosTbl[m270_courseNo].y;
    object->trans.z = m270_startPosTbl[m270_courseNo].z;
    Center.x = m270_startPosTbl[m270_courseNo].x;
    Center.y = m270_startPosTbl[m270_courseNo].y;
    Center.z = m270_startPosTbl[m270_courseNo].z;
    Hu3DMotionTimeSet(object->model[0], 5.0f);
    Hu3DMotionAttrSet(object->model[0], 1, 1);
    switch (GwPlayer[player].chr) {
        case 2:
        case 6:
        case 7:
            m270_headScale = 3.0f;
            break;
        case 4:
            m270_headScale = 1.8f;
            break;
    }
}

void m270_Player0ObjInit(omObjData *object) {
    m270_PlayerInit(object, 0);
}

void m270_WakeUpdate(omObjData *object, f32 speed) {
    f32 angle;
    f32 offset;
    f32 backAngle;
    f32 scale;
    f32 leftX, leftZ;
    f32 rightX, rightZ;
    s32 idx;
    s32 i;

    angle = ((MgPlayerWork *)object->data)->unk3C;
    idx = m270_wakeNo + 1;
    idx = (idx != 6) ? idx : 0;
    m270_wakeNo = idx;
    m270_wakeScaleTbl[idx] = 1.0f;
    m270_wakeSpeedTbl[idx] = speed * 10.0f;
    offset = (rand8() - 128) / 4;
    m270_wakePosTbl[idx].x = sindf(angle + 180.0f) * 150.0f + object->trans.x + sindf(angle + 90.0f) + offset;
    m270_wakePosTbl[idx].y = object->trans.y;
    m270_wakePosTbl[idx].z = cosdf(angle + 180.0f) * 150.0f + object->trans.z + sindf(angle + 90.0f) + offset;
    offset = (rand8() - 128) / 4;
    backAngle = angle + 180.0f + offset;
    m270_wakeDirTbl[idx].x = sindf(backAngle);
    m270_wakeDirTbl[idx].z = cosdf(backAngle);
    if (m270_boatType == 2) {
        for (i = 0; i < 6; i++) {
            if (m270_wakeSpeedTbl[i] > 0.0f) {
                leftX = sindf(angle + 90.0f) * 60.0f;
                leftZ = cosdf(angle + 90.0f) * 60.0f;
                rightX = sindf(angle + 90.0f) * -60.0f;
                rightZ = cosdf(angle + 90.0f) * -60.0f;
                m270_wakePosTbl[i].x += m270_wakeDirTbl[i].x * m270_wakeSpeedTbl[i] * speed;
                m270_wakePosTbl[i].y -= 20.0f;
                m270_wakePosTbl[i].z += m270_wakeDirTbl[i].z * m270_wakeSpeedTbl[i] * speed;
                m270_wakeScaleTbl[i] *= 1.3f;
                scale = speed * m270_wakeScaleTbl[i];
                Hu3DModelPosSet(object->model[i + 1], leftX + m270_wakePosTbl[i].x,
                                m270_wakePosTbl[i].y, leftZ + m270_wakePosTbl[i].z);
                Hu3DModelScaleSet(object->model[i + 1], scale, scale, scale);
                Hu3DModelAttrSet(object->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelPosSet(object->model[i + 7], rightX + m270_wakePosTbl[i].x,
                                m270_wakePosTbl[i].y, rightZ + m270_wakePosTbl[i].z);
                Hu3DModelScaleSet(object->model[i + 7], scale, scale, scale);
                Hu3DModelAttrSet(object->model[i + 7], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            } else {
                Hu3DModelAttrSet(object->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(object->model[i + 7], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
        }
    } else {
        for (i = 0; i < 6; i++) {
            if (m270_wakeSpeedTbl[i] > 0.0f) {
                m270_wakePosTbl[i].x += m270_wakeDirTbl[i].x * m270_wakeSpeedTbl[i] * speed;
                m270_wakePosTbl[i].y -= 20.0f;
                m270_wakePosTbl[i].z += m270_wakeDirTbl[i].z * m270_wakeSpeedTbl[i] * speed;
                Hu3DModelPosSet(object->model[i + 1], m270_wakePosTbl[i].x, m270_wakePosTbl[i].y,
                                m270_wakePosTbl[i].z);
                m270_wakeScaleTbl[i] *= 1.3f;
                scale = speed * m270_wakeScaleTbl[i];
                Hu3DModelScaleSet(object->model[i + 1], scale, scale, scale);
                Hu3DModelAttrSet(object->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            } else {
                Hu3DModelAttrSet(object->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
        }
    }
}

s32 m270_StickAvgCalc(s32 player, s16 value) {
    s32 sum;
    u8 i;

    m270_stickHistTbl[m270_stickHistNo] = value;
    if (++m270_stickHistNo >= 20) {
        m270_stickHistNo = 0;
    }
    sum = 0;
    for (i = 0; i < 20; i++) {
        sum += m270_stickHistTbl[i];
    }
    return sum / 20;
}

void m270_MoveAvgCalc(s32 player, f32 speed, Vec *out) {
    s32 i;

    out->x = out->y = out->z = 0.0f;
    m270_moveHistTbl[m270_moveHistNo].x = m270_moveDelta.x;
    m270_moveHistTbl[m270_moveHistNo].z = m270_moveDelta.z;
    if (++m270_moveHistNo >= 20) {
        m270_moveHistNo = 0;
    }
    for (i = 0; i < 20; i++) {
        out->x += m270_moveHistTbl[i].x;
        out->z += m270_moveHistTbl[i].z;
    }
    out->x /= 20.0f;
    out->z /= 20.0f;
}

void m270_PlayerObjMain(omObjData *object) {
    MgPlayerWork *work;
    HmfMotionNode *node;
    Vec vel;
    Vec drift;
    s16 stickX;
    s16 stickY;
    s32 player;
    s32 pad;
    s32 mode;
    f32 speed;
    f32 turn;
    f32 avg;
    f32 x, y, z;
    f32 dist;
    f32 motTime;

    work = object->data;
    mgMoveOfsX = mgMoveOfsZ = 0.0f;
    player = work->unk59;
    pad = work->unk57;
    speed = work->unk40;
    m270_prevPos.x = x = object->trans.x;
    m270_prevPos.y = y = object->trans.y;
    m270_prevPos.z = z = object->trans.z;
    m270_btnSave = (u16)HuPadBtn[pad];
    m270_stkXSave = HuPadStkX[pad];
    HuPadStkX[pad] = 0;
    HuPadBtn[pad] = 0;
    mode = MgFlowStatGet();
    if (mode == MG_STATE_PLAY) {
        stickX = m270_stkXSave;
        stickY = 0;
        if (stickX > 60) {
            stickX = 60;
        }
        if (stickY > 60) {
            stickY = 60;
        }
        if (stickX < -60) {
            stickX = -60;
        }
        if (stickY < -60) {
            stickY = -60;
        }
        MgStickClamp(&stickX, &stickY);
    } else {
        stickY = 0;
        stickX = 0;
        m270_btnSave = 0;
        if (mode == 3) {
            if (work->unk3C > 180.0f) {
                work->unk3C += 2.0f;
                if (work->unk3C > 360.0f) {
                    work->unk3C = 0.0f;
                }
            } else {
                work->unk3C -= 2.0f;
                if (work->unk3C < 0.0f) {
                    work->unk3C = 0.0f;
                }
            }
        }
    }
    if (m270_btnSave & A_BUTTON) {
        if (speed == 0.0f) {
            speed = 1.0f;
        }
        speed *= 1.08f;
        m270_throttle *= m270_throttleAccel;
    } else {
        speed *= m270_speedDecay;
        m270_throttle *= 0.9f;
    }
    avg = m270_StickAvgCalc(player, stickX);
    turn = avg / 15.0f;
    if (speed < 1.0f) {
        speed = 0.0f;
    }
    if (speed > m270_speedMax) {
        speed = m270_speedMax;
    }
    if (m270_throttle < 0.05f) {
        m270_throttle = 0.05f;
    }
    if (m270_throttle > 1.0f) {
        m270_throttle = 1.0f;
    }
    if (m270_engineSeNo != -1) {
        HuAudFXPitchSet((s16)m270_engineSeNo, (s16)(m270_throttle * 400.0f + -400.0f));
    }
    work->unk40 = speed;
    vel.x = sindf(work->unk3C) * (speed * m270_throttle);
    vel.y = 0.0f;
    vel.z = cosdf(work->unk3C) * (speed * m270_throttle);
    work->unk3C = HuAngleWrap(work->unk3C - turn);
    m270_MoveAvgCalc(player, speed, &drift);
    drift.x += vel.x;
    drift.z += vel.z;
    dist = HuSqrtf(drift.x * drift.x + drift.z * drift.z);
    if (speed < dist) {
        drift.x *= speed / dist;
        drift.z *= speed / dist;
    }
    x += m270_bumpDir.x * m270_bumpPower + drift.x;
    z += m270_bumpDir.z * m270_bumpPower + drift.z;
    y = m270_PlayerCollide(object, x, 0.0f, z);
    m270_moveDelta.x = x - m270_prevPos.x;
    m270_moveDelta.y = 0.0f;
    m270_moveDelta.z = z - m270_prevPos.z;
    x += mgMoveOfsX;
    z += mgMoveOfsZ;
    m270_waterScrollU -= (object->trans.x - x) * 32.0f / 1000.0f;
    m270_waterScrollV += (object->trans.z - z) * 32.0f / 1000.0f;
    m270_PlayerTiltUpdate(object, x, z);
    speed = work->unk40;
    HuRotateRPYF(Hu3DData[object->model[0]].mtx, 0.0f, work->unk3C, 0.0f);
    MgObjPosSet(object, x, y - 40.0f, z);
    m270_WakeUpdate(object, m270_throttle);
    if (m270_bumpPower != 0.0f) {
        m270_bumpPower *= 0.9f;
        if (m270_bumpPower < 1.0f) {
            m270_bumpPower = 0.0f;
        }
    }
    motTime = Hu3DData[object->model[0]].motTime;
    if (abs(stickX) < 10) {
        if (motTime > 5.0f) {
            motTime *= 0.9f;
            if (motTime < 5.0f) {
                motTime = 5.0f;
            }
        } else {
            motTime *= 1.1f;
            if (motTime > 5.0f) {
                motTime = 5.0f;
            }
            if (motTime < 1.0f) {
                motTime = 1.0f;
            }
        }
    } else {
        motTime -= stickX / 100.0f;
    }
    if (motTime < 0.0f) {
        motTime = 0.0f;
    }
    if (motTime > 10.0f) {
        motTime = 10.0f;
    }
    Hu3DMotionTimeSet(object->model[0], motTime);
    m270_GoalCheck(object);
    HuPadBtn[pad] = m270_btnSave;
    HuPadStkX[pad] = m270_stkXSave;
    node = Hu3DModelObjPtrGet(object->model[0], "atama_2");
    if (node != (HmfMotionNode *)-1) {
        node->scale.x = node->scale.y = node->scale.z = node->baseScale.x = node->baseScale.y = node->baseScale.z =
            m270_headScale;
    }
    MgGaugeValueSet(0, speed);
}

void m270_NormalCalc(Vec *origin, Vec *p, Vec *q, Vec *out) {
    f32 ax = p->x - origin->x;
    f32 ay = p->y - origin->y;
    f32 az = p->z - origin->z;
    f32 bx = q->x - origin->x;
    f32 by = q->y - origin->y;
    f32 bz = q->z - origin->z;

    out->x = ay * bz - az * by;
    out->y = az * bx - ax * bz;
    out->z = ax * by - ay * bx;
    MapVecNormalize(out);
}

void m270_PlayerTiltUpdate(omObjData *object, f32 x, f32 z) {
    MgPlayerWork *work;
    Vec a;
    Vec b;
    Vec c;
    Vec normal;

    a.x = x;
    a.y = m270_WaveHeightGet(x, z);
    a.z = z;
    b.x = x + sindf(0.0f) * 10.0f;
    b.z = z + cosdf(0.0f) * 10.0f;
    b.y = m270_WaveHeightGet(b.x, b.z);
    c.x = x + sindf(90.0f) * 10.0f;
    c.z = z + cosdf(90.0f) * 10.0f;
    c.y = m270_WaveHeightGet(c.x, c.z);
    m270_NormalCalc(&a, &b, &c, &normal);
    normal.y = 0.0f;
    MapVecNormalize(&normal);
    work = object->data;
    normal.x *= 5.0f;
    normal.z *= 20.0f;
    if (work->unk90 < normal.x) {
        work->unk90 += 1.0f;
    } else if (normal.x < work->unk90) {
        work->unk90 -= 1.0f;
    }
    if (work->unk98 < normal.z) {
        work->unk98 += 1.0f;
    } else if (normal.z < work->unk98) {
        work->unk98 -= 1.0f;
    }
    object->rot.x = work->unk90;
    object->rot.z = work->unk98;
}

void m270_PushClamp(omObjData *object, f32 x, f32 z) {
    MgPlayerWork *work = object->data;
    f32 limit = work->unk48;
    f32 mag = HuSqrtf(mgMoveOfsX * mgMoveOfsX + mgMoveOfsZ * mgMoveOfsZ);

    if (mag > limit || fabs(mgMoveOfsX) > limit || fabs(mgMoveOfsZ) > limit) {
        mgMoveOfsX = m270_prevPos.x - x;
        mgMoveOfsZ = m270_prevPos.z - z;
    }
    if (MgFlowStatGet() == MG_STATE_PLAY) {
        if (m270_vibTimer == 0) {
            if (0.0f < mag) {
                if (mag < limit / 3.0f) {
                    omVibrate(work->unk59, 2, 3, 10);
                } else {
                    omVibrate(work->unk59, 10, 0, 10);
                }
                m270_vibTimer = 10;
            }
        } else {
            m270_vibTimer--;
        }
    }
}

f32 m270_PlayerCollide(omObjData *object, f32 x, f32 y, f32 z) {
    MgPlayerWork *work = object->data;
    f32 speed = work->unk40;
    Hu3DSphere sphere;
    f32 dist;

    sphere.pos.x = x + sindf(work->unk3C) * speed + mgMoveOfsX;
    sphere.pos.y = y;
    sphere.pos.z = z + cosdf(work->unk3C) * speed + mgMoveOfsZ;
    sphere.radius = work->unk48;
    work->unk53[0] = work->unk53[1] = -1;
    sphere.pos.x += mgMoveOfsX;
    sphere.pos.z += mgMoveOfsZ;
    MgPlayerWallCheck(object, &sphere, 0.0f);
    dist = HuSqrtf(mgMoveOfsX * mgMoveOfsX + mgMoveOfsZ * mgMoveOfsZ);
    if (dist != 0.0f) {
        if (dist > m270_speedMax * 0.5f) {
            work->unk40 *= m270_hitDecayHard;
        } else {
            work->unk40 *= m270_hitDecay;
        }
        if (dist > m270_bumpPower) {
            m270_bumpDir.x = mgMoveOfsX;
            m270_bumpDir.y = 0.0f;
            m270_bumpDir.z = mgMoveOfsZ;
            MapVecNormalize(&m270_bumpDir);
            m270_bumpPower = 16.0f;
        }
    }
    m270_PushClamp(object, x, z);
    return m270_WaveHeightGet(sphere.pos.x, sphere.pos.z);
}

void m270_HudObjInit(omObjData *object) {
    s32 pos[4];
    s16 frameSprite;
    void *data;
    u16 sprite;
    s32 i;

    pos[0] = 62;
    pos[1] = 32;
    pos[2] = 44;
    pos[3] = 28;
    frameSprite = HuSprAnimDataRead(0x670008);
    HuSprAnimDataRead(0x440014);
    HuSprAnimDataRead(0x440015);
    data = DataRead(0x440013);
    HuSprAnimRead(data);
    DataClose(data);
    for (i = 0; i < 1; i++) {
        sprite = espEntry(frameSprite, 0, 1);
        espDispOn(sprite);
        espPosSet(sprite, pos[0], pos[1]);
        espPriSet(sprite, 0xFFFF);
        espTPLvlSet(sprite, 200);
        sprite = espEntry(HuSprAnimDataRead((GwPlayer[i].chr + 8) | 0x210000), 0, 1);
        espDispOn(sprite);
        espPosSet(sprite, pos[2] - 10, pos[3] + 4);
        espPriSet(sprite, 100);
        MgGaugeInit(1, 5);
        MgGaugeRangeSet(0, 0.0f, m270_speedMax);
        MgGaugePosSet(0, 44, 27, 0);
        MgGaugeDispOn(0);
    }
    object->func = NULL;
}

void m270_GoalCheck(omObjData *object) {
    Vec normal;
    f32 dx, dy, dz;
    s32 inside;

    m270_NormalCalc(&m270_goalPlaneTbl[m270_courseNo][0],
                                 &m270_goalPlaneTbl[m270_courseNo][1],
                                 &m270_goalPlaneTbl[m270_courseNo][2], &normal);
    dx = object->trans.x - m270_goalPlaneTbl[m270_courseNo][0].x;
    dy = object->trans.y - m270_goalPlaneTbl[m270_courseNo][0].y;
    dz = object->trans.z - m270_goalPlaneTbl[m270_courseNo][0].z;
    inside = (dx * normal.x + dy * normal.y + dz * normal.z >= 0.0f) ? 1 : 0;
    if (HuSqrtf(dx * dx + dz * dz) > 1400.0f) {
        inside = 0;
    }
    if (inside == 1 && MgFlowStatGet() == MG_STATE_PLAY) {
        MgFlowStatSet(MG_STATE_FINISH);
        m270_goalF = inside;
        m270_goalSeNo = HuAudFXPlay(0x425);
    }
}
