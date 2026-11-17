#include "common.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/hmfcoll.h"
#include "game/mallocblock.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "gcc/memory.h"
#include "humath.h"
#include "math.h"
#include "game/overlays/minigame.h"

extern u8 Hu3DBufNo;
extern f32 CFanLen;
extern u8 omAllPauseF;

Vec m235_startPosTbl[4] = {
    { -300.0f, 0.0f, 325.0f },
    { -250.0f, 0.0f, 575.0f },
    { -200.0f, 0.0f, 825.0f },
    { -150.0f, 0.0f, 1075.0f }
};
f32 m235_speedMaxTbl[4] = { 40.0f, 40.0f, 40.0f, 40.0f };
Vec m235_playerMoveTbl[4] = { 0 };
Vec m235_playerPosTbl[4] = { 0 };
Vec m235_bumpDirTbl[4] = { 0 };
f32 m235_bumpPowerTbl[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
s32 m235_sectionCntTbl[4] = { -1, -1, -1, -1 };
f32 m235_waveTimeA = 0.0f;
f32 m235_wavePeriodA = 0.15f;
f32 m235_waveLenA = 30.0f;
f32 m235_waveAmpA = 80.0f;
f32 m235_waveTimeB = 0.0f;
f32 m235_wavePeriodB = 0.13f;
f32 m235_waveLenB = 40.0f;
f32 m235_waveAmpB = 40.0f;
s32 m235_lapTbl[4] = { 0, 0, 0, 0 };
s32 m235_winner = -1;
s32 m235_finalLapSeNo = 0;
s32 m235_finalLapSeVol = 0;
s32 m235_engineSeTbl[4] = { -1, -1, -1, -1 };
s32 m235_vibTimerTbl[4] = { 0, 0, 0, 0 };
MinigameFlow m235_mgFlow = {
    MG_STATE_OPENING, MINIGAME_4P, MG_TIMER_COUNT_DOWN, MG_TIME_DISP_RECORD, FALSE, MG_GAUGE_CORNERS_4 | 4, MG_RESULT_WIN_1, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    120, -1, 5400, 75, 135
};
Vec m235_lightDir = { 101.0f, -51.0f, 38.0f };
f32 m235_rankSpeedMaxTbl[4] = { 45.0f, 42.5f, 41.0f, 40.0f };
s8 m235_startSlotTbl[4] = { -1, -1, -1, -1 };
s16 m235_wakeMdl0 = -1;
s16 m235_wakeMdl1 = -1;
s16 m235_wakeMdl2 = -1;
s32 m235_wakeNoTbl[4] = { 0, 0, 0, 0 };
s16 m235_stickHistTbl[4][20] = { 0 };
s32 m235_moveHistNoTbl[4] = { 0, 0, 0, 0 };
s32 m235_stickHistNoTbl[4] = { 0, 0, 0, 0 };
f32 m235_throttleTbl[4] = { 0.1f, 0.1f, 0.1f, 0.1f };
s32 m235_engineFrameTbl[4] = { 0, 0, 0, 0 };
s32 m235_reverseBlinkTbl[4] = { 0, 0, 0, 0 };
f32 m235_comLaneOfsTbl[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 m235_comRadiusOfsTbl[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 m235_comRandScaleTbl[4] = { 2.5f, 0.9f, 0.5f, 0.2f };
s32 m235_sectionTbl[4] = { 0, 0, 0, 0 };
s32 m235_sectionSideTbl[4] = { 0, 0, 0, 0 };
Vec m235_gatePlaneTbl[4][3] = {
    { { 0.0f, 100.0f, 0.0f }, { 0.0f, 100.0f, 800.0f }, { 0.0f, -500.0f, 800.0f } },
    { { 1000.0f, 100.0f, 0.0f }, { 1800.0f, 100.0f, 0.0f }, { 1800.0f, -500.0f, 0.0f } },
    { { 0.0f, 100.0f, 0.0f }, { 0.0f, 100.0f, -800.0f }, { 0.0f, -500.0f, -800.0f } },
    { { -1000.0f, 100.0f, 0.0f }, { -1800.0f, 100.0f, 0.0f }, { -1800.0f, -500.0f, 0.0f } }
};

Vec m235_wakePosTbl[4][6] BSS;
f32 m235_wakeSpeedTbl[4][6] BSS;
Vec m235_wakeDirTbl[4][6] BSS;
f32 m235_wakeScaleTbl[4][6] BSS;
Vec2f m235_comTarget BSS;
u8 m235_comTargetPad[0x18] BSS; /* Unreferenced. */
Vec m235_moveHistTbl[4][20] BSS;
s32 m235_btnSave BSS;
s32 m235_stkXSave BSS;
s32 m235_lapGrpTbl[4] BSS;
s32 m235_reverseSprTbl[4] BSS;
s32 m235_lapSprTbl[4] BSS;
s32 m235_goalSprTbl[4] BSS;

void m235_CameraObjMain(omObjData *object);
void m235_ExitObjMain(omObjData *object);
void m235_WaterWaveUpdate(omObjData *object);
void m235_CameraIntroUpdate(void);
void m235_CameraWinUpdate(void);
void m235_RankSpeedUpdate(void);
void m235_MainObjMain(omObjData *object);
void m235_CameraPosUpdate(void);
f32 m235_WaveHeightGet(f32 x, f32 z);
void m235_MainObjInit(omObjData *object);
void m235_PlayerInit(omObjData *object, u16 player);
void m235_Player0ObjInit(omObjData *object);
void m235_Player1ObjInit(omObjData *object);
void m235_Player2ObjInit(omObjData *object);
void m235_Player3ObjInit(omObjData *object);
void m235_PlayerObjMain(omObjData *object);
void m235_NormalCalc(Vec *origin, Vec *p, Vec *q, Vec *out);
void m235_PlayerPushCalc(omObjData *object, Vec *pos);
void m235_PushClamp(omObjData *object, f32 x, f32 z);
void m235_LapDispSet(s16 player, s16 bank);
void m235_ReverseDispSet(s16 player);
void m235_GoalDispSet(s16 player);
s32 m235_SectionGet(omObjData *object);
void m235_HudObjInit(omObjData *object);
void m235_PlayerTiltUpdate(omObjData *object, f32 x, f32 z);
f32 m235_PlayerCollide(omObjData *object, f32 x, f32 y, f32 z);
void m235_PlayerDirCalc(omObjData *object);
void m235_PlayerComInput(omObjData *object);
void m235_LapUpdate(omObjData *object);

void m235_ObjectSetup(void) {
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
    CFanLen = 30000.0f;
    Hu3DCameraPerspectiveSet(0, 20.0f, 80.0f, 16000.0f);
    Hu3DGLightDirSet(1, -35.0f, -114.0f, -3.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    MgPlayerParamReset();
    mgPlayerFallInit = 0.0f;
    MgMapBaseSet(mgMapObjNum);
    mgMapObjTbl[mgMapObjNum++] = omAddObj(1, 10, 0, -1, m235_MainObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(3, 7, 0, -1, m235_Player0ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(3, 7, 0, -1, m235_Player1ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(3, 7, 0, -1, m235_Player2ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(3, 7, 0, -1, m235_Player3ObjInit);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omSetStatBit(omAddObj(4, 0, 0, -1, m235_CameraObjMain), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omSetStatBit(omAddObj(100, 0, 0, -1, m235_HudObjInit), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    mgPlayerAccel = 10.0f;
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    MgFlowInit(&m235_mgFlow);
    mgFlowSeqNo = 50;
    mgFlowSeqTime = 60;
    MgGaugeRangeSet(0, 0.0f, m235_speedMaxTbl[0]);
    MgGaugeRangeSet(1, 0.0f, m235_speedMaxTbl[1]);
    MgGaugeRangeSet(2, 0.0f, m235_speedMaxTbl[2]);
    MgGaugeRangeSet(3, 0.0f, m235_speedMaxTbl[3]);
    Hu3DGLightDirSet(1, m235_lightDir.x, m235_lightDir.y, m235_lightDir.z);
}

void m235_CameraPosUpdate(void) {
    Vec pos;
    Vec at;
    Vec up;
    f32 rotX = CRot.x;
    f32 rotY = CRot.y;

    pos.x = Center.x + sindf(rotY) * cosdf(rotX) * CZoom;
    pos.y = -sindf(rotX) * CZoom + Center.y;
    pos.z = cosdf(rotY) * cosdf(rotX) * CZoom + Center.z;
    at.x = Center.x;
    at.y = Center.y;
    at.z = Center.z;
    up.x = sindf(rotY) * sindf(rotX);
    up.y = cosdf(rotX);
    up.z = cosdf(rotY) * sindf(rotX);
    Hu3DCameraPosSetV(0, &pos, &at, &up);
}

void m235_CameraObjMain(omObjData *object) {
    Vec worldPos;
    Vec2f screenPos;
    f32 min;
    f32 max;
    s32 i;

    if (MgFlowStatGet() == MG_STATE_PLAY) {
        min = 50000.0f;
        max = -50000.0f;
        for (i = 0; i < 4; i++) {
            if (m235_playerPosTbl[i].x < min) {
                min = m235_playerPosTbl[i].x;
            }
            if (max < m235_playerPosTbl[i].x) {
                max = m235_playerPosTbl[i].x;
            }
        }
        Center.x = (min + max) * 0.5f;
        min = 50000.0f;
        max = -50000.0f;
        for (i = 0; i < 4; i++) {
            if (m235_playerPosTbl[i].z < min) {
                min = m235_playerPosTbl[i].z;
            }
            if (max < m235_playerPosTbl[i].z) {
                max = m235_playerPosTbl[i].z;
            }
        }
        Center.z = (min + max) * 0.5f;
        CZoom = 12000.0f;
        m235_CameraPosUpdate();
        max = 0.0f;
        for (i = 0; i < 4; i++) {
            worldPos.x = m235_playerPosTbl[i].x;
            worldPos.y = 0.0f;
            worldPos.z = m235_playerPosTbl[i].z;
            Hu3DCam3Dto2D(0, &worldPos, &screenPos);
            screenPos.x = fabsf(screenPos.x - 160.0f);
            screenPos.y = fabsf(screenPos.y - 120.0f);
            screenPos.x = (screenPos.x + 40.0f) / 160.0f;
            screenPos.y = (screenPos.y + 20.0f) / 120.0f;
            if (max < screenPos.x) {
                max = screenPos.x;
            }
            if (max < screenPos.y) {
                max = screenPos.y;
            }
        }
        CZoom = max * 12000.0f;
        if (CZoom < 7000.0f) {
            CZoom = 7000.0f;
        }
    }
}

void m235_ExitObjMain(omObjData *object) {
    if (m235_finalLapSeVol != 0) {
        m235_finalLapSeVol = m235_finalLapSeVol * 0.75f;
        HuAudFXVolSet(m235_finalLapSeNo, m235_finalLapSeVol);
    }
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

f32 m235_WaveHeightGet(f32 x, f32 z) {
    f32 wave;

    wave = sindf((m235_waveTimeA / m235_wavePeriodA -
                  HuSqrtf(x * x + z * z) / m235_waveLenA) *
                 (M_PI * 2)) *
           m235_waveAmpA;
    x += 8000.0f;
    z += 5000.0f;
    wave += sindf((m235_waveTimeB / m235_wavePeriodB -
                   HuSqrtf(x * x + z * z) / m235_waveLenB) *
                  (M_PI * 2)) *
            m235_waveAmpB;
    return wave / 2.0f;
}

void m235_WaterWaveUpdate(omObjData *object) {
    HmfData *hmf;
    Vtx *vtx;
    Vtx *src;
    f32 x, z;
    f32 height;
    s32 i;

    hmf = Hu3DData[object->model[1]].hmf;
    vtx = hmf->unk44[Hu3DBufNo];
    src = hmf->unk40;
    for (i = 0; i < hmf->unk18; vtx++, i++, src++) {
        x = src->v.ob[0];
        z = src->v.ob[2];
        height = sindf((m235_waveTimeA / m235_wavePeriodA -
                        HuSqrtf(x * x + z * z) / m235_waveLenA) *
                       (2 * M_PI)) *
                 m235_waveAmpA;
        x += 8000.0f;
        z += 5000.0;
        height = (height + sindf((m235_waveTimeB / m235_wavePeriodB -
                                  HuSqrtf(x * x + z * z) / m235_waveLenB) *
                                 (2 * M_PI)) *
                               m235_waveAmpB) /
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
        m235_waveTimeA += 0.11f;
        m235_waveTimeB += 0.09f;
    }
}

void m235_CameraIntroUpdate(void) {
    s32 time = MgFlowStatTimeGet();

    if (MgFlowStatGet() == MG_STATE_OPENING) {
        if (time < 15) {
            CRot.y = 100.0f;
            CRot.x = 350.0f;
            Center.z = 300.0f;
            Center.y = 0.0f;
            CZoom = 2500.0f;
            return;
        }
        if (time < 75.0) {
            Center.z += 10.0f;
            if (Center.z > 1000.0f) {
                Center.z = 1000.0f;
            }
            if (time == 30) {
                HuAudSeqPlay(0x6D);
            }
            return;
        }
        if (time < 90) {
            return;
        }
    }
    m235_lightDir.x -= 8.0f;
    m235_lightDir.z += 3.0f;
    if (m235_lightDir.x < -85.0f) {
        m235_lightDir.x = -85.0f;
    }
    if (m235_lightDir.z > 64.0f) {
        m235_lightDir.z = 64.0f;
    }
    Hu3DGLightDirSet(1, m235_lightDir.x, m235_lightDir.y, m235_lightDir.z);
    CRot.x *= 0.995f;
    CRot.y -= 2.0f;
    CZoom *= 1.025f;
    Center.z *= 0.98f;
    Center.y += 5.0f;
    if (CRot.x < 319.0f) {
        CRot.x = 319.0f;
    }
    if (CRot.y < 1.0f) {
        CRot.y = 0.0f;
    }
    if (CZoom > 7000.0f) {
        CZoom = 7000.0f;
    }
    if (Center.z < 700.0f) {
        Center.z = 700.0f;
    }
}

void m235_CameraWinUpdate(void) {
    omObjData *target;

    if (m235_winner != -1) {
        target = mgPlayerObjTbl[m235_winner];
        Center.x -= (Center.x - target->trans.x) * 0.25f;
        Center.z -= (Center.z - target->trans.z) * 0.25f;
        Center.y -= (Center.y - target->trans.y) * 0.25f;
        CZoom *= 0.95f;
        if (CZoom < 2000.0f) {
            CZoom = 2000.0f;
        }
    }
}

void m235_RankSpeedUpdate(void) {
    s32 order[4];
    f32 progress[4];
    f32 x;
    f32 z;
    f32 angle;
    f32 tempProgress;
    s32 tempOrder;
    s32 swapped;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        progress[i] = m235_sectionCntTbl[i] * 1500.0f;
        x = mgPlayerObjTbl[i]->trans.x;
        z = mgPlayerObjTbl[i]->trans.z;
        if (x > 0.0f) {
            if (z > 0.0f) {
                if (x > 1000.0f) {
                    progress[i] += atan2df(x - 1000.0f, z) / 90.0f * 500.0f + 1000.0f;
                } else {
                    progress[i] += x;
                }
            } else {
                if (x > 1000.0f) {
                    progress[i] += (atan2df(x - 1000.0f, z) - 90.0f) / 90.0f * 500.0f;
                } else {
                    progress[i] += 1000.0f - x + 500.0f;
                }
            }
        } else {
            angle = HuAngleWrap(atan2df(x + 1000.0f, z));
            if (z > 0.0f) {
                if (x < -1000.0f) {
                    progress[i] += (angle - 270.0f) / 90.0f * 500.0f;
                } else {
                    progress[i] += x + 1000.0f + 500.0f;
                }
            } else {
                if (x < -1000.0f) {
                    progress[i] += (angle - 180.0f) / 90.0f * 500.0f + 1000.0f;
                } else {
                    progress[i] -= x;
                }
            }
        }
        order[i] = i;
    }
    do {
        swapped = FALSE;
        for (i = 0; i < 3; i++) {
            for (j = i + 1; j < 4; j++) {
                // Redundant with the loop condition, but required to match.
                if (j == 4) {
                    break;
                }
                if (progress[i] > progress[j]) {
                    tempProgress = progress[j];
                    progress[j] = progress[i];
                    progress[i] = tempProgress;
                    tempOrder = order[j];
                    order[j] = order[i];
                    order[i] = tempOrder;
                    swapped = TRUE;
                }
            }
        }
    } while (swapped);
    for (i = 0; i < 4; i++) {
        m235_speedMaxTbl[order[i]] = m235_rankSpeedMaxTbl[i];
    }
}

void m235_MainObjMain(omObjData *object) {
    MgPlayerWork *work;
    s32 time;
    s32 i;

    m235_WaterWaveUpdate(object);
    if (omPauseChk() + omAllPauseF != 0) {
        return;
    }
    time = MgFlowStatTimeGet();
    switch (MgFlowMain()) {
        case 0:
            if (time == 1) {
                m235_engineSeTbl[0] = PlayerFXPlay(0x41A, 0);
                m235_engineSeTbl[1] = PlayerFXPlay(0x41A, 1);
                m235_engineSeTbl[2] = PlayerFXPlay(0x41A, 2);
                m235_engineSeTbl[3] = PlayerFXPlay(0x41A, 3);
                HuAudFXPlay(0x424);
            }
        case 1:
            m235_CameraIntroUpdate();
            break;
        case 2:
            for (i = 0; i < 4; i++) {
                if (m235_lapTbl[i] == 5) {
                    m235_winner = i;
                    MgFlowStatSet(MG_STATE_FINISH);
                    m235_mgFlow.winners[0] = m235_winner;
                    m235_mgFlow.resultType = MG_RESULT_WIN_1;
                    work = mgPlayerObjTbl[m235_winner]->data;
                    GwPlayer[work->unk59].bonusCoin += 10;
                    break;
                }
            }
            if (m235_finalLapSeNo != 0) {
                m235_finalLapSeVol += 7;
                if (m235_finalLapSeVol > 110) {
                    m235_finalLapSeVol = 110;
                }
            }
            m235_RankSpeedUpdate();
            break;
        case 3:
            if (time == 15.0) {
                HuAudFXFadeOut(m235_engineSeTbl[0], 30);
                HuAudFXFadeOut(m235_engineSeTbl[1], 30);
                HuAudFXFadeOut(m235_engineSeTbl[2], 30);
                HuAudFXFadeOut(m235_engineSeTbl[3], 30);
                m235_engineSeTbl[0] = -1;
                m235_engineSeTbl[1] = -1;
                m235_engineSeTbl[2] = -1;
                m235_engineSeTbl[3] = -1;
            }
            if (m235_winner == -1) {
                m235_mgFlow.resultType = MG_RESULT_DRAW;
            } else {
                m235_finalLapSeVol += 3;
                if (m235_finalLapSeVol > 127) {
                    m235_finalLapSeVol = 127;
                }
            }
            m235_CameraWinUpdate();
            break;
        case 4:
            if (m235_winner != -1 && mgFlowResultF == 1) {
                HuAudPlayerFXPlay(GwPlayer[m235_winner].chr + 0x290, m235_winner);
            }
            if (time >= 150) {
                m235_finalLapSeVol -= 4;
                if (m235_finalLapSeVol < 0) {
                    m235_finalLapSeVol = 0;
                }
            }
            m235_CameraWinUpdate();
            break;
        case 5:
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            object->func = m235_ExitObjMain;
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
        object->func = m235_ExitObjMain;
    }
    if (m235_finalLapSeNo != 0) {
        HuAudFXVolSet(m235_finalLapSeNo, m235_finalLapSeVol);
    }
}

void m235_MainObjInit(omObjData *object) {
    MgMapWork *work;

    object->model[0] = Hu3DModelRead2(0x440000, 0x4C9);
    object->model[1] = Hu3DModelRead2(0x440001, 0x4C9);
    object->model[2] = Hu3DModelRead2(0x440003, 0x8C9);
    object->model[3] = Hu3DModelLink(object->model[2]);
    object->model[4] = Hu3DModelRead2(0x440004, 0x8C9);
    object->model[5] = Hu3DModelLink(object->model[4]);
    object->model[6] = Hu3DModelRead2(0x440005, 0x8C9);
    object->model[7] = Hu3DModelLink(object->model[6]);
    object->trans.x = 0.0f;
    object->trans.y = 0.0f;
    object->trans.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    work = object->data = HuMemAllocTag(0xB4, TAG_OVERLAY);
    memset(work, 0, 0xB4);
    object->func = m235_MainObjMain;
    work->unk03 = 1;
    CZoom = 12000.0f;
    CRot.x = 319.0f;
    CRot.y = 0.0f;
    Center.x = -224.0f;
    Center.y = 300.0f;
    Center.z = 300.0f;
    MgMapTiltOn(object);
    MgMapAttrSet(object, 1, 0.0f);
    MgMapFrictionSet(object, 0.2f);
    MgMapAccelSet(object, mgPlayerAccel);
    MgMapSlideSet(object, 25.0f);
    work->unk04 = 0;
    Hu3DModelObjAttrSet(object->model[1], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(object->model[1]);
    Hu3DModelVtxBufMake(object->model[1]);
    Hu3DModelPosSet(object->model[2], -2400.0f, 0.0f, -1400.0f);
    Hu3DModelPosSet(object->model[3], 2700.0f, 0.0f, -900.0f);
    Hu3DModelPosSet(object->model[4], 1000.0f, 300.0f, -1950.0f);
    Hu3DModelPosSet(object->model[5], -2400.0f, 500.0f, -2000.0f);
    Hu3DModelPosSet(object->model[6], -1300.0f, 500.0f, -2050.0f);
    Hu3DModelPosSet(object->model[7], 2000.0f, 100.0f, -2500.0f);
    Hu3DMotionAttrSet(object->model[2], 2, 2);
    Hu3DMotionAttrSet(object->model[3], 2, 2);
    Hu3DMotionAttrSet(object->model[4], 2, 2);
    Hu3DMotionAttrSet(object->model[5], 2, 2);
    Hu3DMotionAttrSet(object->model[6], 2, 2);
    Hu3DMotionAttrSet(object->model[7], 2, 2);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void m235_PlayerInit(omObjData *object, u16 player) {
    MgPlayerWork *work;
    s32 i;

    for (i = 0; i < object->mdlcnt; i++) {
        object->model[i] = 0;
    }
    object->data = HuMemAllocTag(0x15C, TAG_OVERLAY);
    memset(object->data, 0, 0x15C);
    work = object->data;
    object->model[0] = Hu3DModelRead((GwPlayer[player].chr + 9) | 0x440000, 0x6D9);
    work->unk57 = GwPlayer[player].pad;
    object->func = m235_PlayerObjMain;
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
    object->scale.x = object->scale.y = object->scale.z = 1.1f;
    for (i = 0; i < 6; i++) {
        if (i == 3 || i == 0) {
            if (m235_wakeMdl0 < 0) {
                object->model[i + 1] = m235_wakeMdl0 = Hu3DModelRead(0x440006, 0x889);
            } else {
                object->model[i + 1] = Hu3DModelLink(m235_wakeMdl0);
            }
        } else if (i == 4 || i == 1) {
            if (m235_wakeMdl1 < 0) {
                object->model[i + 1] = m235_wakeMdl1 = Hu3DModelRead(0x440007, 0x889);
            } else {
                object->model[i + 1] = Hu3DModelLink(m235_wakeMdl1);
            }
        } else {
            if (m235_wakeMdl2 < 0) {
                object->model[i + 1] = m235_wakeMdl2 = Hu3DModelRead(0x440008, 0x889);
            } else {
                object->model[i + 1] = Hu3DModelLink(m235_wakeMdl2);
            }
        }
        Hu3DModelObjAttrSet(object->model[i + 1], 0x70000000, 0x70000000);
    }
    work = object->data;
    work->unk3C = 90.0f;
    MgPlayerMapAttrSet(object, 0, 2);
    do {
        i = rand8() & 3;
    } while (m235_startSlotTbl[i] != -1);
    m235_startSlotTbl[i] = player;
    object->trans.x = m235_startPosTbl[i].x;
    object->trans.y = m235_startPosTbl[i].y;
    object->trans.z = m235_startPosTbl[i].z;
}

void m235_Player0ObjInit(omObjData *object) {
    m235_PlayerInit(object, 0);
}

void m235_Player1ObjInit(omObjData *object) {
    m235_PlayerInit(object, 1);
}

void m235_Player2ObjInit(omObjData *object) {
    m235_PlayerInit(object, 2);
}

void m235_Player3ObjInit(omObjData *object) {
    m235_PlayerInit(object, 3);
}

void m235_WakeUpdate(omObjData *object, f32 speed) {
    MgPlayerWork *work = object->data;
    s32 player = work->unk59;
    f32 angle = work->unk3C;
    f32 offset;
    f32 backAngle;
    f32 scale;
    s32 idx;
    s32 i;

    idx = m235_wakeNoTbl[player] + 1;
    idx = (idx != 6) ? idx : 0;
    m235_wakeNoTbl[player] = idx;
    m235_wakeScaleTbl[player][idx] = 1.0f;
    m235_wakeSpeedTbl[player][idx] = speed * 10.0f;
    offset = (rand8() - 128) / 4;
    m235_wakePosTbl[player][idx].x =
        sindf(angle + 180.0f) * 75.0f + object->trans.x + sindf(angle + 90.0f) + offset;
    m235_wakePosTbl[player][idx].y = object->trans.y;
    m235_wakePosTbl[player][idx].z =
        cosdf(angle + 180.0f) * 75.0f + object->trans.z + sindf(angle + 90.0f) + offset;
    offset = (rand8() - 128) / 4;
    backAngle = angle + 180.0f + offset;
    m235_wakeDirTbl[player][idx].x = sindf(backAngle);
    m235_wakeDirTbl[player][idx].z = cosdf(backAngle);
    for (i = 0; i < 6; i++) {
        if (m235_wakeSpeedTbl[player][i] > 0.0f) {
            m235_wakePosTbl[player][i].x +=
                m235_wakeDirTbl[player][i].x * m235_wakeSpeedTbl[player][i] * speed;
            m235_wakePosTbl[player][i].y -= 20.0f;
            m235_wakePosTbl[player][i].z +=
                m235_wakeDirTbl[player][i].z * m235_wakeSpeedTbl[player][i] * speed;
            Hu3DModelPosSet(object->model[i + 1], m235_wakePosTbl[player][i].x,
                            m235_wakePosTbl[player][i].y, m235_wakePosTbl[player][i].z);
            m235_wakeScaleTbl[player][i] *= 1.3f;
            scale = speed * m235_wakeScaleTbl[player][i];
            Hu3DModelScaleSet(object->model[i + 1], scale, scale, scale);
            Hu3DModelAttrSet(object->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        } else {
            Hu3DModelAttrSet(object->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
    }
}

s32 m235_StickAvgCalc(s32 index, s16 value) {
    s32 sum;
    u8 i;

    m235_stickHistTbl[index][m235_stickHistNoTbl[index]] = value;
    if (++m235_stickHistNoTbl[index] >= 20) {
        m235_stickHistNoTbl[index] = 0;
    }
    sum = 0;
    for (i = 0; i < 20; i++) {
        sum += m235_stickHistTbl[index][i];
    }
    return sum / 20;
}

void m235_MoveAvgCalc(s32 index, f32 unused, Vec *out) {
    s32 i;

    out->x = out->y = out->z = 0.0f;
    m235_moveHistTbl[index][m235_moveHistNoTbl[index]].x = m235_playerMoveTbl[index].x;
    m235_moveHistTbl[index][m235_moveHistNoTbl[index]].z = m235_playerMoveTbl[index].z;
    if (++m235_moveHistNoTbl[index] >= 20) {
        m235_moveHistNoTbl[index] = 0;
    }
    for (i = 0; i < 20; i++) {
        out->x += m235_moveHistTbl[index][i].x;
        out->z += m235_moveHistTbl[index][i].z;
    }
    out->x /= 20.0f;
    out->z /= 20.0f;
}

void m235_PlayerObjMain(omObjData *object) {
    MgPlayerWork *work = object->data;
    s32 player;
    s32 pad;
    s32 mode;
    f32 speed;
    f32 x;
    f32 y;
    f32 z;
    f32 turn;
    f32 stickAvg;
    f32 dist;
    f32 scale;
    s16 stickX;
    s16 stickY;
    Vec vel;
    Vec drift;

    mgMoveOfsX = mgMoveOfsZ = 0.0f;
    player = work->unk59;
    pad = work->unk57;
    speed = work->unk40;
    m235_playerPosTbl[player].x = x = object->trans.x;
    m235_playerPosTbl[player].y = y = object->trans.y;
    m235_playerPosTbl[player].z = z = object->trans.z;
    m235_btnSave = (u16)HuPadBtn[pad];
    m235_stkXSave = HuPadStkX[pad];
    HuPadStkX[pad] = 0;
    HuPadBtn[pad] = 0;
    mode = MgFlowStatGet();
    if (mode >= MG_STATE_PLAY) {
        m235_PlayerComInput(object);
        stickX = m235_stkXSave;
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
        m235_btnSave = 0;
    }
    if (m235_btnSave & A_BUTTON) {
        if (speed == 0.0f) {
            speed = 1.0f;
        }
        speed *= 1.08f;
        m235_throttleTbl[player] *= 1.1f;
    } else {
        speed *= 0.98f;
        m235_throttleTbl[player] *= 0.9f;
    }
    stickAvg = m235_StickAvgCalc(player, stickX);
    turn = stickAvg / 15.0f;
    if (speed < 1.0f) {
        speed = 0.0f;
    }
    if (m235_speedMaxTbl[player] < speed) {
        speed = m235_speedMaxTbl[player];
    }
    if (m235_throttleTbl[player] < 0.05f) {
        m235_throttleTbl[player] = 0.05f;
    }
    if (1.0f < m235_throttleTbl[player]) {
        m235_throttleTbl[player] = 1.0f;
    }
    if (m235_engineSeTbl[player] != -1 && (m235_engineFrameTbl[player] & 1)) {
        HuAudFXPitchSet((s16)m235_engineSeTbl[player],
                        (s16)(m235_throttleTbl[player] * 400.0f + -400.0f));
        HuAudFXVolSet(m235_engineSeTbl[player], m235_throttleTbl[player] * 43.0f + 84.0f);
    }
    m235_engineFrameTbl[player]++;
    work->unk40 = speed;
    vel.x = sindf(work->unk3C) * (speed * m235_throttleTbl[player]);
    vel.y = 0.0f;
    vel.z = cosdf(work->unk3C) * (speed * m235_throttleTbl[player]);
    work->unk3C = HuAngleWrap(work->unk3C - turn);
    m235_MoveAvgCalc(player, speed, &drift);
    drift.x += vel.x;
    drift.z += vel.z;
    dist = HuSqrtf(drift.x * drift.x + drift.z * drift.z);
    if (speed < dist) {
        scale = speed / dist;
        drift.x *= scale;
        drift.z *= scale;
    }
    x += m235_bumpDirTbl[player].x * m235_bumpPowerTbl[player] + drift.x;
    z += m235_bumpDirTbl[player].z * m235_bumpPowerTbl[player] + drift.z;
    y = m235_PlayerCollide(object, x, 0.0f, z);
    m235_playerMoveTbl[player].x = x - m235_playerPosTbl[player].x;
    m235_playerMoveTbl[player].y = 0.0f;
    m235_playerMoveTbl[player].z = z - m235_playerPosTbl[player].z;
    x += mgMoveOfsX;
    z += mgMoveOfsZ;
    m235_PlayerTiltUpdate(object, x, z);
    speed = work->unk40;
    object->trans.x -= m235_throttleTbl[player] * 50.0f;
    HuRotateRPYF(Hu3DData[object->model[0]].mtx, 0.0f, work->unk3C, 0.0f);
    MgObjPosSet(object, x, y - 40.0f, z);
    m235_WakeUpdate(object, m235_throttleTbl[player]);
    if (m235_bumpPowerTbl[player] != 0.0f) {
        if ((m235_bumpPowerTbl[player] *= 0.9f) < 1.0f) {
            m235_bumpPowerTbl[player] = 0.0f;
        }
    }
    m235_mgFlow.gaugeValue[player] = speed;
    m235_PlayerDirCalc(object);
    m235_LapUpdate(object);
    HuPadBtn[pad] = m235_btnSave;
    HuPadStkX[pad] = m235_stkXSave;
}

void m235_NormalCalc(Vec *origin, Vec *p, Vec *q, Vec *out) {
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

void m235_PlayerTiltUpdate(omObjData *object, f32 x, f32 z) {
    MgPlayerWork *work;
    Vec a;
    Vec b;
    Vec c;
    Vec normal;

    a.x = x;
    a.y = m235_WaveHeightGet(x, z);
    a.z = z;
    b.x = x + sindf(0.0f) * 10.0f;
    b.z = z + cosdf(0.0f) * 10.0f;
    b.y = m235_WaveHeightGet(b.x, b.z);
    c.x = x + sindf(90.0f) * 10.0f;
    c.z = z + cosdf(90.0f) * 10.0f;
    c.y = m235_WaveHeightGet(c.x, c.z);
    m235_NormalCalc(&a, &b, &c, &normal);
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

void m235_PlayerPushCalc(omObjData *object, Vec *pos) {
    MgPlayerWork *work = object->data;
    MgPlayerWork *otherWork;
    omObjData *other;
    f32 x = pos->x;
    f32 z = pos->z;
    f32 dx;
    f32 dz;
    f32 dist;
    s32 i;

    for (i = 0; i < mgPlayerObjNum; i++) {
        other = mgPlayerObjTbl[i];
        otherWork = other->data;
        if (work == otherWork) {
            continue;
        }
        dx = other->trans.x - (x + mgMoveOfsX);
        dz = other->trans.z - (z + mgMoveOfsZ);
        dist = HuSqrtf(dx * dx + dz * dz) - (otherWork->unk48 + work->unk48);
        if (dist < 0.0f) {
            MgMoveOfsAdd(dx, dz, dist);
            work->unk53[1] = i;
        }
    }
}

void m235_PushClamp(omObjData *object, f32 x, f32 z) {
    MgPlayerWork *work = object->data;
    f32 radius = work->unk48;
    f32 dist = HuSqrtf(mgMoveOfsX * mgMoveOfsX + mgMoveOfsZ * mgMoveOfsZ);

    if (dist > radius || fabs(mgMoveOfsX) > radius || fabs(mgMoveOfsZ) > radius) {
        mgMoveOfsX = m235_playerPosTbl[work->unk59].x - x;
        mgMoveOfsZ = m235_playerPosTbl[work->unk59].z - z;
    }
    if (MgFlowStatGet() == MG_STATE_PLAY) {
        if (m235_vibTimerTbl[work->unk59] == 0) {
            if (dist > 0.0f) {
                if (dist < radius / 3.0f) {
                    omVibrate(work->unk59, 2, 3, 10);
                } else {
                    omVibrate(work->unk59, 10, 0, 10);
                }
                m235_vibTimerTbl[work->unk59] = 10;
            }
        } else {
            m235_vibTimerTbl[work->unk59]--;
        }
    }
}

f32 m235_PlayerCollide(omObjData *object, f32 x, f32 y, f32 z) {
    MgPlayerWork *work = object->data;
    f32 speed = work->unk40;
    s32 player = work->unk59;
    Hu3DSphere sphere;
    f32 dist;

    sphere.pos.x = x + sindf(work->unk3C) * speed + mgMoveOfsX;
    sphere.pos.y = y;
    sphere.pos.z = z + cosdf(work->unk3C) * speed + mgMoveOfsZ;
    sphere.radius = work->unk48;
    work->unk53[0] = work->unk53[1] = -1;
    m235_PlayerPushCalc(object, &sphere.pos);
    m235_PushClamp(object, x, z);
    sphere.pos.x += mgMoveOfsX;
    sphere.pos.z += mgMoveOfsZ;
    MgPlayerWallCheck(object, &sphere, 0.0f);
    dist = HuSqrtf(mgMoveOfsX * mgMoveOfsX + mgMoveOfsZ * mgMoveOfsZ);
    if (dist != 0.0f) {
        if (dist > m235_speedMaxTbl[player] * 0.5f) {
            work->unk40 *= 0.8f;
        } else {
            work->unk40 *= 0.98f;
        }
        if (dist > m235_bumpPowerTbl[player]) {
            m235_bumpDirTbl[player].x = mgMoveOfsX;
            m235_bumpDirTbl[player].y = 0.0f;
            m235_bumpDirTbl[player].z = mgMoveOfsZ;
            MapVecNormalize(&m235_bumpDirTbl[player]);
            m235_bumpPowerTbl[player] = 16.0f;
        }
    }
    m235_PushClamp(object, x, z);
    return m235_WaveHeightGet(sphere.pos.x, sphere.pos.z);
}

void m235_HudObjInit(omObjData *object) {
    s32 framePos[4][2] = { { 56, 31 }, { 265, 31 }, { 56, 209 }, { 265, 209 } };
    s32 iconPos[4][2] = { { 43, 32 }, { 253, 32 }, { 43, 210 }, { 253, 210 } };
    s16 frameSprite;
    s16 lapSprite;
    s16 finalLapSprite;
    s16 goalSprite;
    s16 digitAnim;
    s16 grp;
    u16 sprite;
    void *data;
    s32 x;
    s32 y;
    s32 i;
    s32 j;

    sprite = espEntry(HuSprAnimDataRead(0x440011), 0, 1);
    espDispOn(sprite);
    espPosSet(sprite, 160, 120);
    espAttrSet(sprite, HUSPR_ATTR_BG);
    espScaleSet(sprite, 2.0f, 2.0f);
    // do-while(0) needed to match register allocation.
    do {
        frameSprite = HuSprAnimDataRead(0x440012);
    } while (0);
    lapSprite = HuSprAnimDataRead(0x440014);
    finalLapSprite = HuSprAnimDataRead(0x440015);
    goalSprite = HuSprAnimDataRead(0x440016);
    data = DataRead(0x440013);
    digitAnim = HuSprAnimRead(data);
    DataClose(data);
    for (i = 0; i < 4; i++) {
        sprite = espEntry(frameSprite, 0, 1);
        espDispOn(sprite);
        espPosSet(sprite, framePos[i][0], framePos[i][1]);
        espPriSet(sprite, 0xFFFF);
        espTPLvlSet(sprite, 200);
        sprite = espEntry(HuSprAnimDataRead((GwPlayer[i].chr + 8) | 0x210000), 0, 1);
        espDispOn(sprite);
        espPosSet(sprite, iconPos[i][0] - 10, iconPos[i][1] + 4);
        espPriSet(sprite, 100);
        m235_lapSprTbl[i] = espEntry(lapSprite, 0, 1);
        espDispOn(m235_lapSprTbl[i]);
        espPosSet(m235_lapSprTbl[i], iconPos[i][0] + 28, iconPos[i][1] - 9);
        espPriSet(m235_lapSprTbl[i], 100);
        m235_reverseSprTbl[i] = espEntry(finalLapSprite, 0, 1);
        espDispOff(m235_reverseSprTbl[i]);
        espPosSet(m235_reverseSprTbl[i], iconPos[i][0] + 13, iconPos[i][1] - 9);
        espPriSet(m235_reverseSprTbl[i], 100);
        m235_goalSprTbl[i] = espEntry(goalSprite, 0, 1);
        espDispOff(m235_goalSprTbl[i]);
        espPosSet(m235_goalSprTbl[i], iconPos[i][0] + 13, iconPos[i][1] - 9);
        espPriSet(m235_goalSprTbl[i], 100);
        x = iconPos[i][0] - 8;
        y = iconPos[i][1] - 9;
        grp = m235_lapGrpTbl[i] = HuSprGrpCreate(3, 5);
        HuSprGrpMemberSet(grp, 0, digitAnim, 0);
        HuSprAttrReset(grp, 0, 0xFFFF);
        HuSprAttrSet(grp, 0, HUSPR_ATTR_DISPOFF);
        HuSprPosSet(grp, 0, x, y);
        HuSprPriSet(grp, 0, 100);
        x = 8;
        for (j = 1; j < 3; j++) {
            HuSprPriSet(grp, j, 100);
            HuSprGrpMemberSet(grp, j, digitAnim, 0);
            HuSprPosSet(grp, j, x, 0);
            HuSprAttrReset(grp, j, 0xFFFF);
            HuSprAttrSet(grp, j, HUSPR_ATTR_DISPOFF);
            x += 8;
            HuSprParentSet(grp, j, 0);
        }
        HuSprDispOn(grp, 2);
        MgGaugePosSet(i, iconPos[i][0], iconPos[i][1], 0);
    }
    object->func = NULL;
}

void m235_LapDispSet(s16 player, s16 bank) {
    s16 grp = m235_lapGrpTbl[player];

    espDispOn(m235_lapSprTbl[player]);
    HuSprDispOn(grp, 0);
    HuSprBankSet(grp, 0, bank, 0);
    HuSprAnimModeSet(grp, 0, HUSPR_ANIM_MODE_BANK);
    HuSprDispOn(grp, 1);
    HuSprBankSet(grp, 1, 10, 0);
    HuSprAnimModeSet(grp, 1, HUSPR_ANIM_MODE_BANK);
    HuSprDispOn(grp, 2);
    HuSprBankSet(grp, 2, 5, 0);
    HuSprAnimModeSet(grp, 2, HUSPR_ANIM_MODE_BANK);
    espDispOff(m235_reverseSprTbl[player]);
    espDispOff(m235_goalSprTbl[player]);
}

void m235_ReverseDispSet(s16 player) {
    s16 grp = m235_lapGrpTbl[player];

    espDispOff(m235_lapSprTbl[player]);
    HuSprDispOff(grp, 0);
    HuSprDispOff(grp, 1);
    HuSprDispOff(grp, 2);
    if (m235_reverseBlinkTbl[player] >= 0) {
        espDispOn(m235_reverseSprTbl[player]);
        if (m235_reverseBlinkTbl[player] >= 4) {
            m235_reverseBlinkTbl[player] = -4;
        }
    } else {
        espDispOff(m235_reverseSprTbl[player]);
    }
    m235_reverseBlinkTbl[player]++;
    espDispOff(m235_goalSprTbl[player]);
}

void m235_GoalDispSet(s16 player) {
    s16 grp = m235_lapGrpTbl[player];

    espDispOff(m235_lapSprTbl[player]);
    HuSprDispOff(grp, 0);
    HuSprDispOff(grp, 1);
    HuSprDispOff(grp, 2);
    espDispOff(m235_reverseSprTbl[player]);
    espDispOn(m235_goalSprTbl[player]);
}

s32 m235_SectionGet(omObjData *object) {
    f32 x = object->trans.x;
    f32 z = object->trans.z;

    if ((x > -550.0f) & (x < 550.0f)) {
        if (z > 0.0f) {
            return 0;
        }
        return 2;
    }
    if (x > 0.0f) {
        return 1;
    }
    return 3;
}

void m235_PlayerDirCalc(omObjData *object) {
    MgPlayerWork *work = object->data;
    f32 x = object->trans.x;
    f32 z = object->trans.z;
    Vec dir;
    f32 angle;

    if ((x > -1000.0f) & (x < 1000.0f)) {
        if (z > 0.0f) {
            dir.x = 1.0f;
            dir.y = 0.0f;
            dir.z = 0.0f;
        } else {
            dir.x = -1.0f;
            dir.y = 0.0f;
            dir.z = 0.0f;
        }
    } else {
        if (x > 0.0f) {
            angle = atan2df(object->trans.x - 1000.0f, object->trans.z);
            dir.x = sindf(angle + 10.0f) - sindf(angle);
            dir.y = 0.0f;
            dir.z = cosdf(angle + 10.0f) - cosdf(angle);
        } else {
            angle = atan2df(object->trans.x + 1000.0f, object->trans.z);
            dir.x = sindf(angle + 10.0f) - sindf(angle);
            dir.y = 0.0f;
            dir.z = cosdf(angle + 10.0f) - cosdf(angle);
        }
    }
    angle = work->unk3C;
    work->unk60 = MgDirDot(dir.x, dir.z, sindf(angle), cosdf(angle));
}

void m235_PlayerComInput(omObjData *object) {
    MgPlayerWork *work = object->data;
    s32 player = work->unk59;
    s32 accelerate;
    s32 section;
    f32 dx;
    f32 dz;
    f32 angle;
    f32 dir;
    f32 radius;

    if (MgFlowStatGet() == MG_STATE_PLAY && !(GwPlayer[player].stat & PLAYER_IS_CPU)) {
        return;
    }
    m235_btnSave = 0;
    m235_stkXSave = 0;
    section = m235_SectionGet(object);
    accelerate = TRUE;
    switch (section) {
        case 0:
            m235_comTarget.x = object->trans.x + 100.0f;
            m235_comTarget.y = object->trans.z - 50.0f;
            if (m235_comTarget.y < m235_comLaneOfsTbl[player] + 400.0f) {
                m235_comTarget.y = m235_comLaneOfsTbl[player] + 400.0f;
            }
            m235_comRadiusOfsTbl[player] = rand8() * m235_comRandScaleTbl[GwPlayer[player].cpu_difficulty];
            break;
        case 1:
            dx = object->trans.x - 700.0f;
            dz = object->trans.z;
            angle = atan2df(dx, dz);
            radius = HuSqrtf(dx * dx + dz * dz) - 150.0f + m235_comRadiusOfsTbl[player];
            m235_comTarget.x = sindf(angle + 15.0f) * radius + 700.0f;
            m235_comTarget.y = cosdf(angle + 15.0f) * radius;
            if (object->trans.x < 800.0f && object->trans.z > 0.0f && work->unk40 > 20.0f) {
                accelerate = FALSE;
            }
            m235_comLaneOfsTbl[player] = rand8() * m235_comRandScaleTbl[GwPlayer[player].cpu_difficulty];
            break;
        case 2:
            m235_comTarget.x = object->trans.x - 100.0f;
            m235_comTarget.y = object->trans.z + 50.0f;
            if (m235_comTarget.y > m235_comLaneOfsTbl[player] + -400.0f) {
                m235_comTarget.y = m235_comLaneOfsTbl[player] + -400.0f;
            }
            m235_comRadiusOfsTbl[player] = rand8() * m235_comRandScaleTbl[GwPlayer[player].cpu_difficulty];
            break;
        case 3:
            dx = object->trans.x + 700.0f;
            dz = object->trans.z;
            angle = atan2df(dx, dz);
            radius = HuSqrtf(dx * dx + dz * dz) - 150.0f + m235_comRadiusOfsTbl[player];
            m235_comTarget.x = sindf(angle + 15.0f) * radius + -700.0f;
            m235_comTarget.y = cosdf(angle + 15.0f) * radius;
            if (object->trans.x > -800.0f && object->trans.z < 0.0f && work->unk40 > 20.0f) {
                accelerate = FALSE;
            }
            m235_comLaneOfsTbl[player] = rand8() * m235_comRandScaleTbl[GwPlayer[player].cpu_difficulty];
            break;
    }
    angle = work->unk3C - 90.0f;
    dx = m235_comTarget.x - object->trans.x;
    dz = m235_comTarget.y - object->trans.z;
    m235_stkXSave = (s8)(MgDirDot(dx, dz, sindf(angle), cosdf(angle)) * 120.0f);
    // do-while(0) needed for float register allocation of dir.
    do {
        dir = work->unk3C;
        dx = m235_comTarget.x;
        dz = m235_comTarget.y;
        dx -= object->trans.x;
        dz -= object->trans.z;
    } while (0);
    if (MgDirDot(dx, dz, sindf(dir), cosdf(dir)) < 0.0f) {
        m235_stkXSave = 60;
    } else if (accelerate == TRUE) {
        m235_btnSave |= A_BUTTON;
    } else if (m235_stkXSave > 0) {
        m235_stkXSave = 60;
    } else {
        m235_stkXSave = -60;
    }
}

void m235_LapUpdate(omObjData *object) {
    MgPlayerWork *work = object->data;
    s32 player = work->unk59;
    s32 section = m235_SectionGet(object);
    Vec normal;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 side;

    m235_NormalCalc(&m235_gatePlaneTbl[section][0], &m235_gatePlaneTbl[section][1],
                                &m235_gatePlaneTbl[section][2], &normal);
    dx = object->trans.x - m235_gatePlaneTbl[section][0].x;
    dy = object->trans.y - m235_gatePlaneTbl[section][0].y;
    dz = object->trans.z - m235_gatePlaneTbl[section][0].z;
    side = dx * normal.x + dy * normal.y + dz * normal.z >= 0.0f;
    if (section == m235_sectionTbl[player]) {
        if (m235_sectionSideTbl[player] == 0) {
            if (side == 1) {
                m235_sectionCntTbl[player]++;
            }
        } else if (side == 0) {
            m235_sectionCntTbl[player]--;
        }
        if (m235_sectionCntTbl[player] < 0) {
            switch (section) {
                case 0:
                    m235_sectionCntTbl[player] = -1;
                    break;
                case 1:
                    m235_sectionCntTbl[player] = -4;
                    break;
                case 2:
                    m235_sectionCntTbl[player] = -3;
                    break;
                case 3:
                    m235_sectionCntTbl[player] = -2;
                    break;
            }
        }
        m235_sectionSideTbl[player] = side;
    } else {
        m235_sectionSideTbl[player] = side;
    }
    m235_sectionTbl[player] = section;
    m235_lapTbl[player] = m235_sectionCntTbl[player] / 4;
    if (m235_lapTbl[player] < 0) {
        m235_lapTbl[player] = 0;
    }
    if (m235_finalLapSeNo == 0 && m235_lapTbl[player] == 4) {
        m235_finalLapSeNo = HuAudFXPlay(0x425);
    }
    if (m235_lapTbl[player] >= 5) {
        m235_GoalDispSet(player);
    } else if (work->unk60 >= 0.0f) {
        m235_LapDispSet(player, m235_lapTbl[player] < 5 ? m235_lapTbl[player] + 1 : 5);
    } else {
        m235_ReverseDispSet(player);
    }
}
