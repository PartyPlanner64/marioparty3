#include "common.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/camsetup.h"
#include "game/effect.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/hmfanim.h"
#include "game/hmfparticle.h"
#include "game/hmfspr.h"
#include "game/object.h"
#include "game/pause.h"
#include "game/wipe.h"
#include "math.h"

typedef struct HeyBatterBatterBase {
    /* 0x00 */ s16 base;
    /* 0x02 */ s16 shadow;
} HeyBatterBatterBase; // Size 0x4

typedef struct HeyBatterBatterCamera {
    /* 0x00 */ f32 zoom;
    /* 0x04 */ Vec rot;
    /* 0x10 */ Vec center;
} HeyBatterBatterCamera; // Size 0x1C

typedef struct HeyBatterBatterStateWork {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02[2];
    /* 0x06 */ s16 unk06[2];
    /* 0x0A */ s16 unk0A;
} HeyBatterBatterStateWork; // Size 0xC

extern s32 omCharModelNoTbl[][6];
extern u16 mgInstColumnTbl[5];
extern u16 mgInstSlotTbl[5];

s16 m260_playerActNo = 0;
Vec m260_cameraRotTbl[4] = { { -15.0f, 0.0f, 0.0f }, { 5.0f, 90.0f, 0.0f }, { 5.0f, -90.0f, 0.0f }, { 10.0f, 0.0f, 0.0f } };
Vec m260_cameraCenterTbl[4] = { { 0.0f, 175.0f, -200.0f }, { -800.0f, 170.0f, 0.0f }, { 890.0f, 170.0f, -10.0f }, { 0.0f, 225.0f, -1700.0f } };
Vec m260_winCameraRotTbl[2] = { { 5.0f, 0.0f, 0.0f }, { 5.0f, 0.0f, 0.0f } };
Vec m260_winCameraCenterTbl[2] = { { -110.0f, 200.0f, -575.0f }, { 110.0f, 200.0f, -575.0f } };
Vec m260_prizePosTbl[5] = {
    { 600.0f, 250.0f, -1000.0f },
    { 400.0f, 250.0f, -1400.0f },
    { 0.0f, 250.0f, -1600.0f },
    { -400.0f, 250.0f, -1400.0f },
    { -600.0f, 250.0f, -1000.0f },
};
s16 m260_phase = 0;
s16 m260_resultMesId = 0;
s16 m260_phaseTimer = 0;
s16 m260_introPhase = 0;
s16 m260_introTimer = 0;
f32 m260_introCameraTime = 0.0f;
s16 m260_playPhase = 0;
s16 m260_playTimer = 0;
s16 m260_timerMesId = 0;
s16 m260_playTime = 4;
s16 m260_resultPhase = 0;
s16 m260_resultCameraTime = 0;
Vec m260_decoPosTbl[5] = {
    { 600.0f, 500.0f, -2200.0f },
    { -600.0f, 700.0f, -2200.0f },
    { -2000.0f, 500.0f, -700.0f },
    { -2000.0f, 1000.0f, 0.0f },
    { -2000.0f, 800.0f, 800.0f },
};
s16 m260_playerMotNoPrev = 999;
s16 m260_playerActPhase = 0;
s16 m260_playerActTimer = 0;
s16 m260_koopaMotNoPrev = 999;
f32 m260_ballTime = 0.0f;
s16 m260_ballPhase = 0;
s16 m260_ballHitTimer = 0;
f32 m260_ballDuration = 30.0f;
f32 m260_ballDist = 1000.0f;
f32 m260_ballHeight = 100.0f;
s16 m260_ballHitF = 0;
Vec m260_ballTargetPosTbl[7] = {
    { 4.0f, 0.0f, 0.05f },
    { 575.0f, 225.0f, -999.0f },
    { 375.0f, 225.0f, -1399.0f },
    { 0.0f, 225.0f, -1599.0f },
    { -375.0f, 225.0f, -1399.0f },
    { -575.0f, 225.0f, -999.0f },
    { -3.0f, 0.0f, 2.0f },
};
s16 m260_ballTargetNo = 0;
f32 m260_ballFallVel = 1.47f;
Vec m260_basePosTbl[5] = {
    { 600.0f, 5.0f, -1000.0f },
    { 400.0f, 5.0f, -1400.0f },
    { 0.0f, 5.0f, -1600.0f },
    { -400.0f, 5.0f, -1400.0f },
    { -600.0f, 5.0f, -1000.0f },
};
s32 m260_itemSprFileTbl[20] = {
    0x0021002D, 0x0021002E, 0x0021002F, 0x00210030, 0x00210031,
    0x00210032, 0x00210033, 0x00210034, 0x00210035, 0x00210036,
    0x00210037, 0x00210038, 0x00210039, 0x0021003A, 0x0021003B,
    0x0021003C, 0x0021003D, 0x0021003E, 0x0021003F, 0x00210040
};
s16 m260_prizeBaseNo = 0;
s16 m260_prizeBaseMdl = 0;
s16 m260_prizeTimer = 0;
s16 m260_prizePhase = 0;
s16 m260_prizeSprMdl = 0;

s16 m260_ballPosX BSS;
s16 m260_ballPosY BSS;
s16 m260_ballPosZ BSS;
s16 m260_ballVelX BSS;
s16 m260_ballVelY BSS;
s16 m260_ballVelZ BSS;
s16 m260_ballFlyTimer BSS;
s16 m260_swingF BSS;
u8 m260_swingFPad[4] BSS; /* Unreferenced. */
HeyBatterBatterCamera m260_cameraWork BSS;
s16 m260_playerNo BSS;
s16 m260_playerMotNo BSS;
s16 m260_resultNo BSS;
s16 m260_comSwingTime BSS;
s16 m260_pitchF BSS;
s16 m260_koopaMotNo BSS;
s16 m260_effShowF BSS;
s16 m260_ballState BSS;
s16 m260_missF BSS;
s16 m260_unusedNo BSS;
HeyBatterBatterStateWork m260_stateWork BSS;
s16 m260_prizeNo BSS;
omObjData *m260_playerObj BSS;
s16 m260_playerAnimTbl[4] BSS;
s16 m260_decoMdlTbl[5] BSS;
s16 m260_decoTimerTbl[5] BSS;
HeyBatterBatterBase m260_baseTbl[5] BSS;
s16 m260_baseItemMdlTbl[5] BSS;

extern s16 m260_unusedState;
extern s16 m260_effMotTbl[2];
extern s16 m260_effReqTbl[2];
extern s16 m260_prizeState;

void m260_ObjectSetup(void);
void m260_LightInit(void);
void m260_CameraInit(void);
void m260_PlayerNoInit(void);
void m260_MainObjInit(omObjData *object);
void m260_ComSwingInit(void);
void m260_MainObjMain(omObjData *object);
void m260_IntroObjMain(omObjData *object);
void m260_PlayObjMain(omObjData *object);
void m260_ResultObjMain(omObjData *object);
void m260_ExitStartObjMain(omObjData *object);
void m260_ExitObjMain(omObjData *object);
void m260_ExitCheckObjMain(omObjData *object);
void m260_DecoObjInit(omObjData *object);
void m260_DecoObjMain(omObjData *object);
void m260_StageObjInit(omObjData *object);
void m260_PlayerObjInit(omObjData *object);
void m260_PlayerObjMain(omObjData *object);
void m260_KoopaObjInit(omObjData *object);
void m260_KoopaObjMain(omObjData *object);
void m260_BaseObjInit(omObjData *object);
void m260_BaseObjMain(omObjData *object);
void m260_EffObjInit(omObjData *object);
void m260_EffObjMain(omObjData *object);
void m260_CameraMoveSet(f32 startZoom, Vec startRot, Vec startCenter, f32 endZoom, Vec endRot,
                                     Vec endCenter, f32 duration, f32 time);
s16 m260_EspCreate(s32 spriteId, u16 attr, u16 priority, s16 x, s16 y);
s16 m260_MotMdlRead(s32 arg0);

void m260_Executor(void) {
    m260_ObjectSetup();
}

void m260_ObjectSetup(void) {
    MapCollInit(32);
    Hu3DSprModelInit(32);
    omInitObjMan(32, 32);
    omGameSysInit();
    m260_LightInit();
    m260_CameraInit();
    m260_PlayerNoInit();
    omAddObj(1000, 0, 0, -1, m260_MainObjInit);
    omAddObj(2000, 0, 0, -1, m260_ExitCheckObjMain);
}

void m260_LightInit(void) {
    Hu3DGLightMaxSet(3);
    Hu3DGLightDirSet(1, -10.0f, -10.0f, 150.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(2, -82.0f, 255.0f, -60.0f);
    Hu3DGLightColorSet(2, 0xFF, 0xFF, 0xFF);
}

void m260_CameraInit(void) {
    s16 camIndex;

    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(camIndex, 45.0f, 80.0f, 8000.0f);
    m260_cameraWork.zoom = CZoom = 1065.0f;
    CRot.x = -15.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    m260_cameraWork.rot = CRot;
    Center.x = 0.0f;
    Center.y = 175.0f;
    Center.z = -200.0f;
    m260_cameraWork.center = Center;
}

void m260_PlayerNoInit(void) {
    s16 i = 0;
    s16 players[4] = { 0, 1, 2, 3 };

    for (; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    if (i < 4) {
        m260_playerNo = players[i];
    } else {
        m260_playerNo = players[0];
    }
}

void m260_MainObjInit(omObjData *object) {
    m260_ComSwingInit();
    omAddObj(10, 10, 0, -1, m260_DecoObjInit);
    omAddObj(20, 10, 0, -1, m260_StageObjInit);
    m260_playerObj = omAddObj(30, 10, 10, -1, m260_PlayerObjInit);
    omAddObj(40, 10, 10, -1, m260_KoopaObjInit);
    omAddObj(50, 20, 5, -1, m260_BaseObjInit);
    omAddObj(60, 10, 10, -1, m260_EffObjInit);
    object->func = m260_MainObjMain;
}

void m260_ComSwingInit(void) {
    s16 thresholds[5];
    s16 i;
    s16 roll;

    m260_missF = 1;
    m260_unusedNo = 0;
    m260_unusedState = 0;
    if (GwPlayer[m260_playerNo].stat & 1) {
        thresholds[0] = mgInstSlotTbl[0];
        for (i = 1; i < 5; i++) {
            thresholds[i] = thresholds[i - 1] + mgInstSlotTbl[i];
        }
        roll = rand8() % 100;
        for (i = 0; i < 5; i++) {
            if (roll < thresholds[i]) {
                break;
            }
        }
        m260_comSwingTime = i + 20;
        if (GwPlayer[m260_playerNo].cpu_difficulty == 0) {
            if ((rand8() & 3) == 0) {
                if ((rand8() & 1) == 0) {
                    m260_comSwingTime = 19 - rand8() % 3;
                } else {
                    m260_comSwingTime = rand8() % 3 + 25;
                }
            }
        } else if (GwPlayer[m260_playerNo].cpu_difficulty == 1) {
            if ((rand8() & 15) == 0) {
                if ((rand8() & 1) == 0) {
                    m260_comSwingTime = 19 - (rand8() & 1);
                } else {
                    m260_comSwingTime = (rand8() & 1) + 25;
                }
            }
        }
    }
}

void m260_MainObjMain(omObjData *object) {
    switch (m260_phase) {
        case 0:
            WipeCreateIn(WIPE_TYPE_PREV, 16);
            m260_phase++;
            break;
        case 1:
            object->func = m260_IntroObjMain;
            m260_phase++;
            break;
        case 2:
            if (++m260_phaseTimer == 1) {
                GMesCreate(8);
            } else if (GMesStatGet() == 0) {
                m260_phaseTimer = 0;
                m260_phase++;
            }
            break;
        case 3:
            object->func = m260_PlayObjMain;
            m260_phase++;
            break;
        case 4:
            if (++m260_phaseTimer == 1) {
                CharAnimSet(m260_playerObj->model[0], 1,
                                   GwPlayer[m260_playerNo].chr, m260_playerAnimTbl[1]);
                m260_playerActNo = 1;
                GMesCreate(0x13);
                HuAudSeqFadeOut(120);
            } else if (GMesStatGet() == 0) {
                m260_phaseTimer = 0;
                m260_phase++;
            }
            break;
        case 5:
            object->func = m260_ResultObjMain;
            m260_phase++;
            break;
        case 6:
            if (++m260_phaseTimer == 1) {
                switch (m260_missF) {
                    case 0:
                        HuAudSeqPlay(0x68);
                        m260_resultMesId = GMesCreate(0x24);
                        GwPlayer[m260_playerNo].bonusCoin =
                            mgInstColumnTbl[m260_prizeNo];
                        break;
                    case 1:
                        HuAudSeqPlay(0x6B);
                        m260_resultMesId = GMesCreate(0x1D);
                        GwPlayer[m260_playerNo].bonusCoin = -1;
                        break;
                }
                GMesTimeMaxSet(m260_resultMesId, 120);
            } else if (m260_phaseTimer >= 135) {
                m260_phaseTimer = 0;
                m260_phase++;
            }
            break;
        case 7:
            object->func = m260_ExitStartObjMain;
            break;
        case 8:
            break;
    }
}

void m260_IntroObjMain(omObjData *object) {
    switch (m260_introPhase) {
        case 0:
            if (WipeStatGet() != 1) {
                HuAudSeqPlay(0x44);
                HuAudFXPlay(0x4D5);
                m260_introCameraTime = 0.0f;
                m260_introTimer = 0;
                m260_introPhase = 1;
            }
            break;
        case 1:
            if (m260_introTimer++ >= 5) {
                m260_introPhase++;
                m260_introTimer = 0;
            }
            break;
        case 2:
            m260_CameraMoveSet(m260_cameraWork.zoom, m260_cameraRotTbl[0],
                                            m260_cameraCenterTbl[0], m260_cameraWork.zoom,
                                            m260_cameraRotTbl[1], m260_cameraCenterTbl[1], 20.0f,
                                            m260_introCameraTime);
            if (sindf(m260_introCameraTime * 4.5f) >= 1.0f) {
                m260_introPhase++;
                m260_introCameraTime = 0.0f;
                m260_playerActNo = 2;
            } else {
                m260_introCameraTime += 1.0f;
            }
            break;
        case 3:
            if (m260_introTimer++ >= 30) {
                m260_introPhase++;
                m260_introTimer = 0;
            }
            break;
        case 4:
            m260_CameraMoveSet(m260_cameraWork.zoom, m260_cameraRotTbl[1],
                                            m260_cameraCenterTbl[1], m260_cameraWork.zoom,
                                            m260_cameraRotTbl[3], m260_cameraCenterTbl[3], 20.0f,
                                            m260_introCameraTime);
            if (sindf(m260_introCameraTime * 4.5f) >= 1.0f) {
                m260_introPhase++;
                m260_introCameraTime = 0.0f;
            } else {
                m260_introCameraTime += 1.0f;
            }
            break;
        case 5:
            if (m260_introTimer++ >= 20) {
                m260_introPhase++;
                m260_introTimer = 0;
                m260_playerMotNo = 6;
            }
            break;
        case 6:
            m260_CameraMoveSet(m260_cameraWork.zoom, m260_cameraRotTbl[3],
                                            m260_cameraCenterTbl[3], m260_cameraWork.zoom,
                                            m260_cameraRotTbl[0], m260_cameraCenterTbl[0], 30.0f,
                                            m260_introCameraTime);
            if (sindf(m260_introCameraTime * 3.0f) == 1.0f) {
                m260_introPhase++;
                m260_introCameraTime = 0.0f;
            } else {
                m260_introCameraTime += 1.0f;
            }
            break;
        case 7:
            m260_introCameraTime = 0.0f;
            m260_introTimer = 0;
            m260_introPhase = 0;
            object->func = m260_MainObjMain;
            break;
        case 8:
            break;
    }
}

void m260_PlayObjMain(omObjData *object) {
    switch (m260_playPhase) {
        case 0:
            m260_playTimer = 0;
            m260_playPhase = 0;
            m260_timerMesId = 0;
            m260_playTime = 91;
            m260_playPhase = 1;
            break;
        case 1:
            if (m260_playTimer++ >= 30) {
                m260_koopaMotNo = 3;
                m260_playPhase++;
            }
            break;
        case 2:
            HuAudFXPlay(8);
            m260_timerMesId = GMesCreate(0x1A, 3, 150, 160);
            GMesPosSet(m260_timerMesId, 150.0f, 160.0f);
            m260_playPhase++;
            break;
        case 3:
            if (m260_playTime-- >= 0) {
                GMesTimerValueSet((m260_playTime + 29) / 30);
            } else {
                GMesTimerEnd();
                m260_koopaMotNo = 4;
                m260_playPhase++;
            }
            break;
        case 4:
            m260_pitchF = 1;
            m260_playPhase++;
            break;
        case 5:
            if (m260_ballState == 2) {
                if ((m260_resultNo == 1 && m260_playTimer++ >= 30) ||
                    m260_resultNo == 2) {
                    object->func = m260_MainObjMain;
                }
            }
            break;
        case 6:
            break;
    }
}

void m260_ResultObjMain(omObjData *object) {
    switch (m260_resultPhase) {
        case 0:
            switch (m260_resultNo) {
                case 1:
                    m260_missF = 0;
                    break;
                case 2:
                    m260_missF = 1;
                    break;
            }
            m260_resultPhase++;
            break;
        case 1:
            if (m260_missF == 0) {
                m260_prizeState = 3;
                m260_CameraMoveSet(m260_cameraWork.zoom, m260_cameraRotTbl[0],
                                                m260_cameraCenterTbl[0], m260_cameraWork.zoom,
                                                m260_winCameraRotTbl[0], m260_winCameraCenterTbl[0], 30.0f,
                                                m260_resultCameraTime);
                if (sindf(m260_resultCameraTime * 3.0f) >= 1.0f) {
                    m260_resultPhase++;
                    m260_resultCameraTime = 0;
                } else {
                    m260_resultCameraTime++;
                }
            } else if (m260_missF == 1) {
                m260_resultPhase++;
            }
            break;
        case 2:
            if (m260_missF == 1) {
                CharAnimSet(m260_playerObj->model[0], 1,
                                   GwPlayer[m260_playerNo].chr, m260_playerAnimTbl[3]);
                m260_playerMotNo = 3;
                m260_koopaMotNo = 1;
                HuAudFXPlay(0x4D8);
            } else if (m260_missF == 0) {
                CharAnimSet(m260_playerObj->model[0], 1,
                                   GwPlayer[m260_playerNo].chr, m260_playerAnimTbl[2]);
                m260_playerMotNo = 2;
                m260_koopaMotNo = 2;
            }
            m260_resultPhase++;
            break;
        case 3:
            object->func = m260_MainObjMain;
            break;
    }
}

void m260_ExitStartObjMain(omObjData *object) {
    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
    HuAudSeqFadeOut(30);
    HuAudFXAllFadeOut(30);
    object->func = m260_ExitObjMain;
}

void m260_ExitObjMain(omObjData *object) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        GMesClose();
        HuWinAllKill();
        HuSprAnimAllKill();
        omOvlReturnEx(1);
    }
}

void m260_ExitCheckObjMain(omObjData *object) {
    if (omSysExitReq == 1) {
        object->func = m260_ExitStartObjMain;
    }
}

void m260_DecoObjInit(omObjData *object) {
    s16 i;
    s16 model;

    m260_EspCreate(0x5D0000, 0x4000, 1000, 160, 120);
    for (i = 0; i < 2; i++) {
        model = m260_decoMdlTbl[i] = Hu3DModelRead(0x5D0003, 0x2A9);
        Hu3DModelPosSet(model, m260_decoPosTbl[i].x, m260_decoPosTbl[i].y,
                        m260_decoPosTbl[i].z);
        Hu3DModelScaleSet(model, 2.0f, 2.0f, 2.0f);
        Hu3DData[model].rot.x = 20.0f;
        m260_decoTimerTbl[i] = rand8() % 90;
    }
    for (; i < 5; i++) {
        model = m260_decoMdlTbl[i] = Hu3DModelRead(0x5D0003, 0x2A9);
        Hu3DModelPosSet(model, m260_decoPosTbl[i].x, m260_decoPosTbl[i].y,
                        m260_decoPosTbl[i].z);
        Hu3DModelScaleSet(model, 2.0f, 2.0f, 2.0f);
        Hu3DData[model].rot.x = 20.0f;
        Hu3DData[model].rot.y = 90.0f;
        m260_decoTimerTbl[i] = rand8() % 90;
    }
    object->func = m260_DecoObjMain;
}

void m260_DecoObjMain(omObjData *object) {
    s16 i;
    s16 model;

    for (i = 0; i < 5; i++) {
        model = m260_decoMdlTbl[i];
        Hu3DData[model].scale.x = Hu3DData[model].scale.y = Hu3DData[model].scale.z =
            sindf(m260_decoTimerTbl[i] * 2.0f) * 0.5f + 2.0f;
        if (m260_decoTimerTbl[i]++ >= 180.0f) {
            m260_decoTimerTbl[i] = 0;
        }
    }
}

void m260_StageObjInit(omObjData *object) {
    object->model[0] = Hu3DModelRead(0x5D0001, 0x2A9);
    object->model[1] = Hu3DModelRead(0x5D0002, 0x2A9);
    Hu3DModelPosSet(object->model[1], 0.0f, 0.0f, -1000.0f);
    object->func = NULL;
}

void m260_PlayerObjInit(omObjData *object) {
    s32 chr = GwPlayer[m260_playerNo].chr;

    object->model[0] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][2], 0x6A8);
    object->model[1] = Hu3DModelRead(0x5D0005, 0x6A9);
    object->model[2] = Hu3DModelRead(9, 0x2A9);
    omObjMotionRead(object, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(object, 1, CharMotionDataNumGet(chr, 0x82));
    omObjMotionRead(object, 2, CharMotionDataNumGet(chr, 0x35));
    omObjMotionRead(object, 3, CharMotionDataNumGet(chr, 0x38));
    omObjMotionRead(object, 4, CharMotionDataNumGet(chr, 0x83));
    omObjMotionRead(object, 5, CharMotionDataNumGet(chr, 1));
    if (chr == 5) {
        omObjMotionRead(object, 6, 0x5D000A);
    }
    Hu3DModelAttrSet(object->model[1], 0x4000, 0x4000);
    Hu3DModelHookSet(object->model[1], object->model[0], "item_hook");
    omSetTra(object, -150.0f, 15.0f, 0.0f);
    omSetRot(object, 0.0f, 180.0f, 0.0f);
    Hu3DModelPosSet(object->model[2], -150.0f, 15.0f, 0.0f);
    GwPlayer[m260_playerNo].bonusCoin = -1;
    Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[1]].motId, 0, 2, 2);
    m260_playerMotNo = 1;
    m260_playerAnimTbl[0] = CharAnimCreate(object->model[0], 1, chr, CharMotionDataNumGet(chr, 0xAA));
    m260_playerAnimTbl[1] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA4));
    m260_playerAnimTbl[2] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA5));
    m260_playerAnimTbl[3] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA6));
    Hu3DModelDynamicFree(object->model[0]);
    CharAnimSet(object->model[0], 1, GwPlayer[m260_playerNo].chr,
                       m260_playerAnimTbl[0]);
    object->func = m260_PlayerObjMain;
}

void m260_PlayerObjMain(omObjData *object) {
    if (m260_playerMotNoPrev != m260_playerMotNo) {
        switch (m260_playerMotNo) {
            case 0:
            case 1:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[m260_playerMotNo]].motId, 0,
                                   30, 2);
                break;
            case 2:
                Hu3DMotionModelSet(object->model[0], object->motion[2]);
                HuAudCharVoicePlay(omCharModelNoTbl[GwPlayer[m260_playerNo].chr][0] | 0x35);
                break;
            case 3:
                Hu3DMotionModelSet(object->model[0], object->motion[3]);
                HuAudCharVoicePlay(omCharModelNoTbl[GwPlayer[m260_playerNo].chr][0] | 0x38);
                break;
            case 4:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[m260_playerMotNo]].motId, 0,
                                   15, 0);
                break;
            case 5:
                Hu3DMotionModelSet(object->model[0], object->motion[4]);
                Hu3DMotionTimeSet(object->model[0], Hu3DMotion[Hu3DData[object->model[0]].motId].unk02);
                Hu3DMotionSpeedSet(object->model[0], -0.9f);
                break;
            case 6:
                Hu3DMotionSpeedSet(object->model[0], 1.0f);
                break;
            case 7:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[5]].motId, 0, 10, 2);
                break;
            case 8:
                Hu3DMotionModelSet(object->model[0], object->motion[6]);
                break;
        }
        m260_playerMotNoPrev = m260_playerMotNo;
    }
    if (m260_playerActNo == 1) {
        switch (m260_playerActPhase) {
            case 0:
                m260_effReqTbl[1] = 1;
                if (GwPlayer[m260_playerNo].chr == CHAR_DK && m260_playerMotNo == 4) {
                    m260_playerMotNo = 8;
                } else {
                    m260_playerMotNo = 0;
                }
                Hu3DModelCameraSet(object->model[1], 0);
                m260_playerActPhase++;
                break;
            case 1:
                if (m260_playerActTimer++ >= 45) {
                    m260_playerActPhase++;
                }
                break;
            case 2:
                if (object->rot.y > 0.0f) {
                    m260_playerMotNo = 7;
                    object->rot.y -= 10.0f;
                } else {
                    m260_playerMotNo = 0;
                    m260_playerActPhase++;
                }
                break;
        }
    }
    if (m260_playerActNo == 2) {
        switch (m260_playerActPhase) {
            case 0:
                HuAudFXPlay(0x4D0);
                m260_playerMotNo = 4;
                m260_playerActPhase++;
                break;
            case 1:
                if (Hu3DMotion[Hu3DData[object->model[0]].motId].unk02 == Hu3DData[object->model[0]].motTime) {
                    m260_playerMotNo = 5;
                    m260_playerActPhase++;
                }
                break;
            case 2:
                if (Hu3DData[object->model[0]].motTime <= 3.0f) {
                    m260_playerMotNo = 1;
                    Hu3DMotionSpeedSet(object->model[0], 0.0f);
                    Hu3DMotionTimeSet(object->model[0], 0.0f);
                    m260_playerActPhase = 0;
                    m260_playerActNo = 0;
                }
                break;
        }
    }
}

void m260_KoopaObjInit(omObjData *object) {
    void *data;
    s16 anim;

    object->model[0] = Hu3DModelRead(0xA00EE, 0x2A9);
    object->model[1] = Hu3DModelRead(0x5D0009, 0x2A9);
    object->model[2] = Hu3DModelRead(9, 0x6A9);
    object->model[3] = Hu3DModelRead(0x5D0004, 0x2A9);
    object->model[4] = Hu3DModelRead(9, 0x6A9);
    data = DataRead(0xA0100);
    anim = Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, data, 0, "c162n_0_DEF");
    DataClose(data);
    Hu3DModelRemakeStatic(object->model[0]);
    Hu3DAnimBankSet(anim, 0);
    Hu3DAnimAttrSet(anim, 1, 0);
    omObjMotionRead(object, 0, 0xA00F7);
    omObjMotionRead(object, 1, 0xA00F6);
    omObjMotionRead(object, 2, 0xA00F2);
    omObjMotionRead(object, 3, 0xA00F8);
    omObjMotionRead(object, 4, 0xA00F9);
    omObjMotionRead(object, 5, 0xA00FA);
    Hu3DModelAttrSet(object->model[1], 0x4000, 0x4000);
    Hu3DModelHookSet(object->model[1], object->model[0], "c162_000-te2");
    Hu3DModelCameraSet(object->model[1], 1);
    omSetTra(object, 0.0f, 5.5f, -1000.0f);
    Hu3DModelPosSet(object->model[2], 0.0f, 4.0f, -1000.0f);
    Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[0]].motId, 0, 2, 2);
    m260_koopaMotNo = 0;
    Hu3DModelCameraSet(object->model[3], 0);
    Hu3DModelCameraSet(object->model[4], 0);
    object->func = m260_KoopaObjMain;
}

void m260_KoopaObjMain(omObjData *object) {
    f32 scale;

    if (m260_koopaMotNoPrev != m260_koopaMotNo) {
        switch (m260_koopaMotNo) {
            case 2:
            case 4:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[m260_koopaMotNo]].motId, 0,
                                   30, 0);
                break;
            case 0:
            case 1:
            case 3:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[m260_koopaMotNo]].motId, 0,
                                   30, 2);
                break;
            case 5:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[m260_koopaMotNo]].motId, 0,
                                   10, 0);
                Hu3DMotionSpeedSet(object->model[0], 0.0f);
                Hu3DMotionTimeSet(object->model[0], 0.0f);
                break;
        }
        m260_koopaMotNoPrev = m260_koopaMotNo;
    }
    if (m260_pitchF == 1 && Hu3DData[object->model[0]].motTime >= 26.0f) {
        HuAudFXPlay(0x4D1);
        Hu3DModelCameraSet(object->model[1], 0);
        m260_ballState = 1;
        m260_pitchF = 0;
        m260_ballDuration = 30.0f;
        m260_ballHeight = rand8() % 50 + 100.0f;
    }
    if (m260_ballState == 1) {
        switch (m260_ballPhase) {
            case 0:
                Hu3DModelPosSet(object->model[3], -30.0f, 70.0f, -1015.0f);
                Hu3DModelCameraSet(object->model[3], 1);
                Hu3DModelCameraSet(object->model[4], 1);
                m260_ballTime = 1.0f;
                m260_ballHitTimer = 0;
                m260_swingF = 0;
                m260_ballPhase++;
                break;
            case 1:
                Hu3DData[object->model[3]].pos.z += m260_ballDist / m260_ballDuration;
                if (Hu3DData[object->model[3]].pos.y > 50.0f) {
                    Hu3DData[object->model[3]].pos.y =
                        sindf(90.0f / (m260_ballDuration / 2.0f) * m260_ballTime) *
                            m260_ballHeight +
                        70.0f;
                } else {
                    Hu3DData[object->model[3]].pos.y = 50.0f;
                }
                Hu3DData[object->model[3]].rot.x += 30.0f;
                if (m260_swingF == 0) {
                    if (GwPlayer[m260_playerNo].stat & 1) {
                        if (m260_ballTime == m260_comSwingTime) {
                            m260_swingF = 1;
                            HuAudFXPlay(0x4D0);
                            m260_playerMotNo = 4;
                            if (m260_ballDuration - 11.0f <= m260_ballTime &&
                                m260_ballTime < m260_ballDuration - 4.0f) {
                                m260_ballTargetNo =
                                    m260_ballDuration - m260_ballTime - 5.0f;
                                m260_ballHitF = 1;
                            } else {
                                m260_ballHitF = 0;
                            }
                        }
                    } else if (HuPadBtnDown[GwPlayer[m260_playerNo].pad] & A_BUTTON) {
                        m260_swingF = 1;
                        HuAudFXPlay(0x4D0);
                        m260_playerMotNo = 4;
                        if (m260_ballDuration - 11.0f <= m260_ballTime &&
                            m260_ballTime < m260_ballDuration - 4.0f) {
                            omVibrate(m260_playerNo, 2, 2, 20);
                            m260_ballTargetNo =
                                m260_ballDuration - m260_ballTime - 5.0f;
                            m260_ballHitF = 1;
                        } else {
                            m260_ballHitF = 0;
                        }
                    }
                }
                if (m260_ballHitF == 1 && ++m260_ballHitTimer == 8) {
                    m260_ballPhase++;
                    break;
                }
                if (Hu3DData[object->model[3]].pos.z >= 500.0f) {
                    Hu3DModelCameraSet(object->model[3], 0);
                    m260_ballPhase++;
                }
                m260_ballTime += 1.0f;
                break;
            case 2:
                if (m260_ballHitF == 1) {
                    if (m260_ballTargetNo == 0 || m260_ballTargetNo == 6) {
                        HuAudFXPlay(0x4D9);
                    } else {
                        HuAudFXPlay(0x4D2);
                    }
                    HuAudFXPlay(0x4D6);
                    m260_ballPhase++;
                } else if (m260_ballHitF == 0) {
                    m260_ballState = 2;
                    m260_resultNo = 2;
                    break;
                }
            case 3:
                m260_ballPosX = Hu3DData[object->model[3]].pos.x;
                m260_ballPosY = Hu3DData[object->model[3]].pos.y;
                m260_ballPosZ = Hu3DData[object->model[3]].pos.z;
                Hu3DModelPosSet(object->model[3], m260_ballPosX, m260_ballPosY,
                                m260_ballPosZ);
                m260_ballVelX = (m260_ballTargetPosTbl[m260_ballTargetNo].x + rand8() % 50 -
                                                m260_ballPosX) /
                                               10.0f;
                m260_ballVelY = (m260_ballTargetPosTbl[m260_ballTargetNo].y + rand8() % 50 -
                                                m260_ballPosY) /
                                               10.0f;
                m260_ballVelZ =
                    (m260_ballTargetPosTbl[m260_ballTargetNo].z - m260_ballPosZ) / 10.0f;
                m260_ballDuration = 10.0f;
                m260_ballTime = 0.0f;
                m260_ballHeight = rand8() % 200;
                m260_ballPhase++;
                m260_ballFallVel = -2.0f;
                m260_ballFlyTimer = 0;
            case 4:
            case 6:
                if (m260_ballTargetNo >= 1 && m260_ballTargetNo <= 5) {
                    Hu3DData[object->model[3]].pos.x += m260_ballVelX;
                    Hu3DData[object->model[3]].pos.y += m260_ballVelY;
                    Hu3DData[object->model[3]].pos.z += m260_ballVelZ;
                    Hu3DData[object->model[3]].rot.x -= 50.0f;
                    if (m260_ballDuration == m260_ballTime) {
                        HuAudFXPlay(0x4D3);
                        m260_ballPhase++;
                        break;
                    }
                    m260_ballTime += 1.0f;
                    break;
                }
                if (m260_ballFlyTimer == 10) {
                    m260_koopaMotNo = 5;
                }
                if (m260_ballTargetNo == 0) {
                    Hu3DData[object->model[3]].pos.z =
                        m260_ballPosZ +
                        sindf(m260_ballFlyTimer * 0.75f) * (m260_ballPosZ + -1300.0f);
                } else {
                    Hu3DData[object->model[3]].pos.z =
                        m260_ballPosZ +
                        sindf(m260_ballFlyTimer * 0.75f) * (m260_ballPosZ + -860.0f);
                }
                if (Hu3DData[object->model[3]].pos.y >= 0.0f) {
                    Hu3DData[object->model[3]].pos.y +=
                        m260_ballFallVel * m260_ballFallVel *
                        (m260_ballFallVel >= 0.0f ? -35.0f : 35.0f);
                    if (m260_ballFallVel >= 1.4f) {
                        m260_ballFallVel = 1.4f;
                    } else {
                        m260_ballFallVel += 0.055f;
                    }
                }
                if (m260_ballFlyTimer == 75) {
                    Hu3DMotionSpeedSet(object->model[0], 1.0f);
                }
                if (m260_ballFlyTimer == 80) {
                    HuAudFXPlay(0x4D4);
                    Hu3DModelCameraSet(object->model[1], 1);
                    Hu3DModelCameraSet(object->model[4], 0);
                    Hu3DModelCameraSet(object->model[3], 0);
                }
                if (m260_ballFlyTimer++ >= 85) {
                    m260_ballPhase = 5;
                    Hu3DModelCameraSet(object->model[1], 1);
                }
                break;
            case 5:
                if (m260_ballTargetNo >= 1 && m260_ballTargetNo <= 5) {
                    Hu3DModelCameraSet(object->model[3], 0);
                    Hu3DModelCameraSet(object->model[4], 0);
                    m260_resultNo = 1;
                    m260_prizeNo = m260_ballTargetNo - 1;
                    m260_prizeState = 1;
                } else {
                    m260_resultNo = 2;
                }
                m260_ballState = 2;
                m260_ballPhase = 0;
                m260_ballTime = 0.0f;
                break;
        }
    }
    scale = 1.0f - Hu3DData[object->model[3]].pos.y * 0.0005f;
    Hu3DModelPosSet(object->model[4], Hu3DData[object->model[3]].pos.x, 10.0f, Hu3DData[object->model[3]].pos.z);
    Hu3DModelScaleSet(object->model[4], scale, scale, scale);
}

void m260_BaseObjInit(omObjData *object) {
    s16 i;
    HeyBatterBatterBase *base;
    s16 sprite;
    s16 model;

    for (i = 0; i < 5; i++) {
        model = Hu3DModelRead(0x5D0006, 0x6A9);
        base = &m260_baseTbl[i];
        base->base = model;
        Hu3DModelPosSet(base->base, m260_basePosTbl[i].x,
                        m260_basePosTbl[i].y + 1.0f, m260_basePosTbl[i].z);
        base->shadow = Hu3DModelRead(0x5D0007, 0x2A9);
        Hu3DModelPosSet(base->shadow, m260_basePosTbl[i].x,
                        m260_basePosTbl[i].y, m260_basePosTbl[i].z);
        sprite = SprModelRead(0x21002C, 0xA0, 0x10);
        model = m260_baseItemMdlTbl[i] = Hu3DSprModelData[sprite].modelId;
        Hu3DSprModelPointSet(sprite, mgInstColumnTbl[i]);
        Hu3DModelPosSet(model, m260_basePosTbl[i].x, m260_basePosTbl[i].y + 250.0f,
                        m260_basePosTbl[i].z + 2.0f);
        Hu3DModelScaleSet(model, 6.0f, 6.0f, 6.0f);
    }
    object->model[2] = Hu3DModelRead(9, 0x6A9);
    Hu3DModelCameraSet(object->model[2], 0);
    object->model[3] = EffectCreate(0xB0004, 0x6A9);
    Hu3DParticleAttrSet(object->model[3], 1, 0);
    m260_prizeState = 0;
    object->func = m260_BaseObjMain;
}

void m260_BaseObjMain(omObjData *object) {
    s16 i = 0;
    f32 scale;

    if (m260_prizeState == 1) {
        m260_prizeBaseNo = m260_prizeNo;
        m260_prizeBaseMdl = m260_baseItemMdlTbl[m260_prizeBaseNo];
        m260_effReqTbl[0] = 1;
        for (; i < 5; i++) {
            if (i != m260_prizeBaseNo) {
                Hu3DModelCameraSet(m260_baseTbl[i].base, 0);
            }
            Hu3DModelCameraSet(m260_baseItemMdlTbl[i], 0);
        }
        m260_prizeSprMdl =
            SprModelRead(m260_itemSprFileTbl[mgInstColumnTbl[m260_prizeBaseNo]], 0xA0, 0x10);
        object->model[1] = Hu3DSprModelData[m260_prizeSprMdl].modelId;
        Hu3DModelPosSet(object->model[1], Hu3DData[m260_prizeBaseMdl].pos.x,
                        Hu3DData[m260_prizeBaseMdl].pos.y,
                        Hu3DData[m260_prizeBaseMdl].pos.z + 1.0f);
        Hu3DModelScaleSet(object->model[1], 6.0f, 6.0f, 6.0f);
        Hu3DModelCameraSet(object->model[2], 1);
        Hu3DModelPosSet(object->model[2], Hu3DData[object->model[1]].pos.x, 10.0f, Hu3DData[object->model[1]].pos.z);
        Hu3DParticleAttrSet(object->model[3], 1, 1);
        EffectParamSet(object->model[3], 5.0f, 20.0f, 10.0f);
        EffectRangeSet(object->model[3], 100.0f);
        EffectPosSet(object->model[3], Hu3DData[object->model[1]].pos.x, Hu3DData[object->model[1]].pos.y,
                           Hu3DData[object->model[1]].pos.z);
        omVibrate(m260_playerNo, 2, 2, 20);
        m260_prizeState = 2;
    }
    if (m260_prizeState == 2) {
        Hu3DData[object->model[1]].pos.y = sindf(m260_prizeTimer * 12.0f) * 10.0f + 250.0f;
        if (m260_prizeTimer++ >= 30) {
            m260_prizeTimer = 0;
        }
    }
    if (m260_prizeState == 3) {
        switch (m260_prizePhase) {
            case 0:
                Hu3DData[object->model[1]].pos.y = sindf(m260_prizeTimer * 12.0f) * 10.0f + 250.0f;
                if (Hu3DData[object->model[1]].pos.y == 250.0f) {
                    m260_prizeTimer = 0;
                    m260_prizePhase++;
                    HuAudFXPlay(0x4D7);
                }
                if (m260_prizeTimer++ >= 30) {
                    m260_prizeTimer = 0;
                }
                break;
            case 1:
                Hu3DData[object->model[1]].pos.x =
                    m260_prizePosTbl[m260_prizeBaseNo].x -
                    sindf(m260_prizeTimer * 3.0f) *
                        (m260_prizePosTbl[m260_prizeBaseNo].x + 150.0f);
                Hu3DData[object->model[1]].pos.y =
                    m260_prizePosTbl[m260_prizeBaseNo].y -
                    sindf(m260_prizeTimer * 3.0f) *
                        (m260_prizePosTbl[m260_prizeBaseNo].y - 275.0f);
                Hu3DData[object->model[1]].pos.z =
                    m260_prizePosTbl[m260_prizeBaseNo].z -
                    sindf(m260_prizeTimer * 3.0f) *
                        (m260_prizePosTbl[m260_prizeBaseNo].z - 0.0f);
                scale = 6.0f - sindf(m260_prizeTimer * 3.0f) * 4.0f;
                Hu3DModelScaleSet(object->model[1], scale, scale, scale);
                if (sindf(m260_prizeTimer * 3.0f) == 1.0f) {
                    m260_prizePhase++;
                } else {
                    m260_prizeTimer++;
                }
                break;
            case 2:
                Hu3DData[object->model[1]].pos.y = sindf(m260_prizeTimer * 12.0f) * 10.0f + 275.0f;
                if (m260_prizeTimer++ >= 30) {
                    m260_prizeTimer = 0;
                }
                break;
        }
        Hu3DModelPosSet(object->model[2], Hu3DData[object->model[1]].pos.x, 10.0f, Hu3DData[object->model[1]].pos.z);
        EffectPosSet(object->model[3], Hu3DData[object->model[1]].pos.x, Hu3DData[object->model[1]].pos.y,
                           Hu3DData[object->model[1]].pos.z);
    }
}

void m260_EffObjInit(omObjData *object) {
    s16 i;

    object->model[0] = Hu3DModelRead(0xB0006, 0x6A9);
    Hu3DModelCameraSet(object->model[0], 0);
    for (i = 1; i < 6; i++) {
        object->model[i] = Hu3DModelRead(0x5D0008, 0x6A9);
        Hu3DModelCameraSet(object->model[i], 0);
    }
    object->model[6] = Hu3DModelRead(0xB0006, 0x6A9);
    Hu3DModelCameraSet(object->model[6], 0);
    m260_effMotTbl[0] = m260_MotMdlRead(0xB0006);
    m260_effMotTbl[1] = m260_MotMdlRead(0x5D0008);
    m260_effReqTbl[0] = 0;
    m260_effReqTbl[1] = 0;
    object->func = m260_EffObjMain;
}

void m260_EffObjMain(omObjData *object) {
    s16 i;
    s16 batter = m260_prizeNo;

    if (m260_effReqTbl[0] == 1) {
        for (i = 0; i < 5; i++) {
            if (i == batter) {
                omSetTra(object, m260_prizePosTbl[i].x, m260_prizePosTbl[i].y,
                         m260_prizePosTbl[i].z);
                omSetSca(object, 3.0f, 3.0f, 3.0f);
                Hu3DMotionModelSet(object->model[0], m260_effMotTbl[0]);
                Hu3DModelCameraSet(object->model[0], 1);
            } else {
                Hu3DModelPosSet(object->model[i + 1], m260_prizePosTbl[i].x,
                                m260_prizePosTbl[i].y, m260_prizePosTbl[i].z);
                Hu3DModelScaleSet(object->model[i + 1], 3.0f, 3.0f, 3.0f);
                Hu3DMotionModelSet(object->model[i + 1], m260_effMotTbl[1]);
                Hu3DModelCameraSet(object->model[i + 1], 1);
            }
        }
        m260_effShowF = 1;
        m260_effReqTbl[0] = 0;
    }
    for (i = 0; i < 7; i++) {
        if (Hu3DMotion[Hu3DData[object->model[i]].motId].unk02 == Hu3DData[object->model[i]].motTime) {
            Hu3DModelCameraSet(object->model[i], 0);
        }
    }
    if (m260_effReqTbl[1] == 1) {
        Hu3DModelPosSet(object->model[6], -170.0f, 100.0f, 0.0f);
        Hu3DModelScaleSet(object->model[6], 1.0f, 1.0f, 1.0f);
        Hu3DMotionModelSet(object->model[6], m260_effMotTbl[0]);
        Hu3DModelCameraSet(object->model[6], 1);
        m260_effReqTbl[1] = 0;
    }
}

void m260_CameraMoveSet(f32 startZoom, Vec startRot, Vec startCenter, f32 endZoom, Vec endRot,
                                     Vec endCenter, f32 duration, f32 time) {
    f32 angle = 90.0f / duration * time;

    CZoom = startZoom - sindf(angle) * (startZoom - endZoom);
    CRot.x = startRot.x - sindf(angle) * (startRot.x - endRot.x);
    CRot.y = startRot.y - sindf(angle) * (startRot.y - endRot.y);
    CRot.z = startRot.z - sindf(angle) * (startRot.z - endRot.z);
    Center.x = startCenter.x - sindf(angle) * (startCenter.x - endCenter.x);
    Center.y = startCenter.y - sindf(angle) * (startCenter.y - endCenter.y);
    Center.z = startCenter.z - sindf(angle) * (startCenter.z - endCenter.z);
    m260_cameraWork.zoom = CZoom;
    m260_cameraWork.rot = CRot;
    m260_cameraWork.center = Center;
}

s16 m260_EspCreate(s32 spriteId, u16 attr, u16 priority, s16 x, s16 y) {
    s16 espriteSlot;

    espriteSlot = espEntry(HuSprAnimDataRead(spriteId), 0, 0);
    espAttrSet(espriteSlot, attr);
    espPriSet(espriteSlot, priority);
    espPosSet(espriteSlot, x, y);
    return espriteSlot;
}

s16 m260_MotMdlRead(s32 arg0) {
    s16 temp = Hu3DMotionModelRead(arg0);

    if (temp < 0) {
        temp = -1;
    }
    return temp;
}
