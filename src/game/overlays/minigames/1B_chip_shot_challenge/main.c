#include "common.h"
#include "game/pause.h"
#include "game/mallocblock.h"
#include "game/overlays/minigame.h"
#include "gcc/memory.h"
#include "game/hmfmath.h"

// Per-object work block, reached via ObjData->data
typedef struct ChipShotChallengeWork {
    /* 0x00 */ char pad_00[0x34];
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;
    /* 0x4C */ char pad_4C[4];
    /* 0x50 */ s16 unk_50;
    /* 0x52 */ s8 unk_52;
    /* 0x53 */ s8 unk_53;
    /* 0x54 */ s8 unk_54;
    /* 0x55 */ char pad_55[4];
    /* 0x59 */ s8 playerIndex;
    /* 0x5A */ char pad_5A[2];
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ f32 unk_60;
    /* 0x64 */ f32 unk_64;
    /* 0x68 */ char pad_68[0xC];
    /* 0x74 */ f32 unk_74;
    /* 0x78 */ s32 unk_78;
    /* 0x7C */ s32 unk_7C;
    /* 0x80 */ char pad_80[4];
    /* 0x84 */ s32 unk_84[9];
    /* 0xA8 */ char pad_A8[4];
} ChipShotChallengeWork; // Size 0xAC

// Work block for the course object, reached via ObjData->data
typedef struct ChipShotChallengeCourseWork {
    /* 0x00 */ char pad_00[3];
    /* 0x03 */ s8 unk_03;
    /* 0x04 */ s8 unk_04;
    /* 0x05 */ char pad_05[0xAF];
} ChipShotChallengeCourseWork; // Size 0xB4

typedef struct ChipShotChallengeSphere {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 radius;
} ChipShotChallengeSphere; // Size 0x10

extern f32 Hu3DMatColScale;
extern f32 Hu3DMatAmbScale;
extern s32 omCharModelNoTbl[][6];
extern u8 omAllPauseF;

s32 m227_ballMoveF = 0;
s32 m227_aimF = 0;
f32 m227_aimAngle = 0.0f;
f32 m227_aimPower = 0.0f;
f32 m227_aimPowerRate = 0.0f;
f32 m227_slopeAccel = 5.0f;
f32 m227_ballSpeed = 0.0f;
s32 m227_cupInF = 0;
s32 m227_ballStopTimer = 0;
s32 m227_shooterNo = -1;
s32 m227_ballOutF = 1;
s32 m227_resultPosTbl[4][3] = {
    { -200, 0, 100 },
    { -80, 0, 100 },
    { 80, 0, 100 },
    { 200, 0, 100 }
};
f32 m227_cloudAngleTbl[5] = { 125.0f, 155.0f, 180.0f, 215.0f, 245.0f };
f32 m227_cloudYTbl[5] = { 600.0f, 800.0f, 400.0f, 900.0f, 200.0f };
f32 m227_cloudDistTbl[5] = { 2500.0f, 3000.0f, 3500.0f, 4000.0f, 4500.0f };
f32 m227_cloudSpeedTbl[5] = { 0.075f, 0.1f, 0.15f, 0.2f, 0.15f };
f32 m227_cloudScaleAngleTbl[5] = { 0.0f, 270.0f, 180.0f, 30.0f, 190.0f };
s32 m227_playerLoseTbl[4] = { 1, 1, 1, 1 };
f32 m227_holeDistTbl[4] = { 10000.0f, 10000.0f, 10000.0f, 10000.0f };
MinigameFlow m227_mgFlow = {
    MG_STATE_OPENING, MINIGAME_4P, MG_TIMER_COUNT_DOWN, MG_TIME_DISP_NONE, FALSE, MG_GAUGE_NONE, MG_RESULT_WIN_1, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    96, -1, -1, 75, 135
};
s32 m227_shooterPlayerTbl[4] = { -1, -1, -1, -1 };
f32 m227_flagY = -1000.0f;
f32 m227_flagSwayAngle = -30.0f;
f32 m227_flagSwayAmp = 0.0f;
f32 m227_flagVelY = -0.8f;
s32 m227_flagSeF = -1;
s32 m227_winnerNum = 0;
s32 m227_winner = -1;
f32 m227_lakituBobAngle = 0.0f;
s32 m227_lakituSeF = -1;
f32 m227_playerStartXTbl[4] = { -300.0f, -600.0f, -900.0f, -1200.0f }; /* Unreferenced. */
u8 m227_swingLevel = 240;
f32 m227_arcRot = 0.0f;
f32 m227_arcWaveAngle = 0.0f;
f32 m227_ballRotX = 0.0f;
f32 m227_ballRotZ = 0.0f;
s32 m227_cupInSeF = -1;
f32 m227_comAngleOfsTbl[4] = { 1000.0f, 1000.0f, 1000.0f, 1000.0f };
f32 m227_comPowerOfsTbl[4] = { 1000.0f, 1000.0f, 1000.0f, 1000.0f };
f32 m227_comErrorScaleTbl[4] = { 1.0f, 0.7f, 0.5f, 0.3f };

f32 m227_introCameraSpeed BSS;
Vec m227_introCameraDir BSS;
Vec m227_lakituPos BSS;
Vec m227_flagPos BSS;
f32 m227_cameraReturnSpeed BSS;
Vec m227_cameraReturnDir BSS;
s32 m227_swingTimer BSS;
s32 m227_aimTimer BSS;
s32 m227_floorHitF BSS;
Vec m227_holePos BSS;
Vec m227_holeNormal BSS;
f32 m227_ballCurve BSS;
s32 m227_distDigitGrp BSS;
s32 m227_distUnitGrp BSS;
s32 m227_cupInSignMdl BSS;
s32 m227_missSignMdl BSS;
s32 m227_lakituMdl BSS;
u8 m227_lakituMdlPad[4] BSS; /* Unreferenced. */
s32 m227_confettiMdlTbl[4] BSS;
s16 m227_confettiFrame BSS;
u8 m227_confettiFramePad[4] BSS; /* Unreferenced. */
omObjData *m227_ballObj BSS;

s32 m227_PlayerRankCalc(s32 playerIndex);
void m227_MapObjInit(omObjData *object);
void m227_MainObjMain(omObjData *object);
void m227_ConfettiCreate(void);
void m227_DistDisp(s16 value);
void m227_CupInLakituUpdate(void);
void m227_MissLakituUpdate(void);
f32 m227_BallCollide(omObjData *object, f32 x, f32 y, f32 z);
void m227_Player0ObjInit(omObjData *object);
void m227_Player1ObjInit(omObjData *object);
void m227_Player2ObjInit(omObjData *object);
void m227_Player3ObjInit(omObjData *object);
void m227_ArcObjInit(omObjData *object);
void m227_BallObjInit(omObjData *object);
void m227_ConfettiUpdate(void);
void m227_ConfettiHook(s16 model);
void m227_ConfettiEmit(s16 model);
void m227_PlayerObjMain(omObjData *object);
void m227_ArcObjMain(omObjData *object);
void m227_BallObjMain(omObjData *object);
void m227_BallCupCheck(omObjData *object, f32 x, f32 y, f32 z);
f32 m227_BallFloorCheck(omObjData *object, ChipShotChallengeSphere *sphere);
void m227_BallShadowSet(omObjData *object, f32 x, f32 y, f32 z, f32 floorY, Vec *normal);
f32 m227_FloorYGet(ChipShotChallengeSphere *sphere, Vec *normal);
void m227_BallSlopeSet(omObjData *object, Vec *arg1);
void m227_PlayerComInputGet(omObjData *object, s32 *stickX, s32 *stickY, s32 *buttons);

void m227_ObjectSetup(void) {
    u8 camIndex;
    u16 sprite;
    s32 rank;
    s32 i;

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
    Hu3DCameraPerspectiveSet(0, 40.0f, 80.0f, 8000.0f);
    Hu3DGLightDirSet(1, 32.0f, 99.0f, 59.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    MgPlayerParamReset();
    MgShadowAltSet(1);
    mgPlayerFallInit = 0.0f;
    MgMapBaseSet(mgMapObjNum);
    mgMapObjTbl[mgMapObjNum++] = omAddObj(1, 12, 0, -1, m227_MapObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(2, 10, 10, -1, m227_Player0ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(2, 10, 10, -1, m227_Player1ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(2, 10, 10, -1, m227_Player2ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(2, 10, 10, -1, m227_Player3ObjInit);
    omAddObj(3, 25, 10, -1, m227_ArcObjInit);
    m227_ballObj = omAddObj(3, 10, 0, -1, m227_BallObjInit);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    sprite = espEntry(HuSprAnimDataRead(0x3C001E), 0, 1);
    espDispOn(sprite);
    espPosSet(sprite, 160, 120);
    espAttrSet(sprite, 0x4000);
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
    MgFlowInit(&m227_mgFlow);
    mgFlowSeqNo = 45;
    mgFlowSeqTime = 60;
    Center.x = 0.0f;
    Center.y = 200.0f;
    Center.z = 0.0f;
    CRot.x = 350.0f;
    CRot.y = 0.0f;
    CZoom = 750.0f;
    for (i = 0; i < 4; i++) {
        rank = m227_PlayerRankCalc(i);
        while (m227_shooterPlayerTbl[rank] != -1) {
            rank++;
        }
        m227_shooterPlayerTbl[rank] = i;
    }
}

s32 m227_PlayerRankCalc(s32 playerIndex) {
    s32 scores[4];
    s32 rank;
    s32 i;

    for (i = 0; i < 4; i++) {
        scores[i] = GwPlayer[i].star * 1000 + GwPlayer[i].coin;
    }
    for (i = 0, rank = 0; i < 4; i++) {
        if (i != playerIndex) {
            rank += scores[playerIndex] < scores[i];
        }
    }
    return rank;
}

void m227_ExitObjMain(omObjData *object) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

void m227_IntroUpdate(omObjData *object) {
    s32 time = MgFlowStatTimeGet();
    f32 velocity;
    f32 speedSq;

    if (time == 1) {
        HuAudFXPlay(0x3E0);
    }
    if (time < 5) {
        Center.x = m227_holePos.x;
        Center.y = m227_holePos.y + 200.0f;
        Center.z = m227_holePos.z;
        m227_lakituPos.x = m227_holePos.x + 1000.0f;
        m227_lakituPos.y = m227_holePos.y + 300.0f;
        m227_lakituPos.z = m227_holePos.z;
        Hu3DModelPosSet(object->model[5], m227_lakituPos.x, m227_lakituPos.y,
                        m227_lakituPos.z);
    } else if (time < 35) {
        Hu3DModelAttrSet(object->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(object->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelPosSet(object->model[6], m227_lakituPos.x, m227_lakituPos.y,
                        m227_lakituPos.z);
        Hu3DModelPosSet(object->model[5], m227_lakituPos.x, m227_lakituPos.y,
                        m227_lakituPos.z);
        m227_lakituPos.x -= 100.0f / 3.0f;
        m227_lakituPos.y -= 10.0f / 3.0f;
        m227_lakituPos.z += 0.0f;
        if (time < 21) {
            m227_flagY = m227_lakituPos.y;
            m227_flagPos.x -= 200.0f / 3.0f;
            m227_flagSwayAmp = 30.0f;
        } else {
            m227_flagPos.x = m227_lakituPos.x;
            m227_flagPos.y = m227_lakituPos.y;
            m227_flagPos.z = m227_lakituPos.z;
        }
    } else if (time < 65) {
        Hu3DModelPosSet(object->model[6], m227_lakituPos.x, m227_lakituPos.y,
                        m227_lakituPos.z);
        m227_introCameraDir.x = m227_holePos.x;
        m227_introCameraDir.y = m227_holePos.y;
        m227_introCameraDir.z = m227_holePos.z;
        MapVecNormalize(&m227_introCameraDir);
        m227_introCameraSpeed =
            HuSqrtf(m227_holePos.x * m227_holePos.x +
                    m227_holePos.y * m227_holePos.y +
                    m227_holePos.z * m227_holePos.z) /
            30.0f;
        m227_lakituPos.x -= 100.0f / 3.0f;
        m227_lakituPos.y += 10.0f / 3.0f;
        m227_lakituPos.z += 0.0f;
        m227_flagPos.x -= 200.0f / 3.0f;
        if (m227_flagPos.x < m227_holePos.x) {
            m227_flagPos.x = m227_holePos.x;
            if (m227_flagSeF != 0) {
                HuAudPlayerFXPlay(0x3DE, 0);
                m227_flagSeF = 0;
            }
        }
    } else {
        Hu3DModelAttrSet(object->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Center.x -= m227_introCameraDir.x * m227_introCameraSpeed;
        Center.y -= m227_introCameraDir.y * m227_introCameraSpeed;
        Center.z -= m227_introCameraDir.z * m227_introCameraSpeed;
    }
    if (m227_flagY > -1000.0f) {
        velocity = m227_flagVelY;
        speedSq = velocity * velocity;
        if (velocity >= 0.0f) {
            m227_flagY += speedSq * -37.5f;
        } else {
            m227_flagY += speedSq * 37.5f;
        }
        m227_flagVelY += mgItemGravity;
        if (m227_flagVelY > 1.2f) {
            m227_flagVelY = 1.2f;
        }
        if (m227_flagY < 0.0f) {
            m227_flagY = 0.0f;
        }
        if (m227_flagY == 0.0f) {
            m227_flagSwayAmp *= 0.9f;
            m227_flagSwayAngle += 50.0f;
        }
        m227_flagPos.y = m227_flagY;
        Hu3DModelRotSet(object->model[5], 0.0f, 0.0f, sindf(m227_flagSwayAngle) * m227_flagSwayAmp);
        Hu3DModelPosSet(object->model[5], m227_flagPos.x,
                        m227_holePos.y + m227_flagPos.y,
                        m227_flagPos.z);
    } else {
        Hu3DModelPosSet(object->model[6], m227_lakituPos.x, m227_lakituPos.y,
                        m227_lakituPos.z);
        Hu3DModelRotSet(object->model[5], 0.0f, 0.0f, 30.0f);
    }
}

void m227_MainObjMain(omObjData *object) {
    omObjData *player;
    ChipShotChallengeWork *work;
    f32 best;
    f32 x;
    f32 scale;
    s32 time;
    s32 chrData;
    s32 chr;
    s32 i;
    s32 j;

    if (omPauseChk() + omAllPauseF != 0) {
        return;
    }
    time = MgFlowStatTimeGet();
    switch (MgFlowMain()) {
        case 0:
            m227_IntroUpdate(object);
            break;
        case 1:
            Hu3DModelRotSet(object->model[5], 0.0f, 0.0f, 0.0f);
            break;
        case 2:
            if (m227_shooterNo < 0) {
                m227_shooterNo = 0;
            }
            m227_cameraReturnDir.x = Center.x;
            m227_cameraReturnDir.y = Center.y - 200.0f;
            m227_cameraReturnDir.z = Center.z;
            MapVecNormalize(&m227_cameraReturnDir);
            m227_cameraReturnSpeed = HuSqrtf(Center.x * Center.x + Center.y * Center.y + Center.z * Center.z) / 30.0f;
            break;
        case 3:
            if (time == 0) {
                best = 10000.0f;
                for (i = 0; i < 4; i++) {
                    if (m227_holeDistTbl[i] < best) {
                        best = m227_holeDistTbl[i];
                        m227_winner = i;
                    }
                    if (m227_holeDistTbl[i] == 0.0f) {
                        m227_winnerNum++;
                        m227_playerLoseTbl[i] = 0;
                    }
                }
                if (m227_winnerNum != 0) {
                    m227_mgFlow.resultType = m227_winnerNum - 1;
                    for (i = 0, j = 0; i < 4; i++) {
                        if (m227_holeDistTbl[i] == 0.0f) {
                            m227_mgFlow.winners[j++] = i;
                        }
                    }
                } else {
                    for (i = 0; i < 4; i++) {
                        if (i != m227_winner &&
                            (s32)best == (s32)m227_holeDistTbl[i]) {
                            m227_winner = -1;
                        }
                    }
                    if (m227_winner == -1) {
                        m227_mgFlow.resultType = MG_RESULT_DRAW;
                    } else {
                        m227_mgFlow.resultType = MG_RESULT_WIN_1;
                        m227_mgFlow.winners[0] = m227_winner;
                        m227_playerLoseTbl[m227_winner] = 0;
                        m227_winnerNum++;
                    }
                }
            }
            Center.x -= m227_cameraReturnDir.x * m227_cameraReturnSpeed;
            Center.y -= m227_cameraReturnDir.y * m227_cameraReturnSpeed;
            Center.z -= m227_cameraReturnDir.z * m227_cameraReturnSpeed;
            CRot.y *= 0.9f;
            if (Center.z >= 0.0f) {
                Center.x = 0.0f;
                Center.y = 200.0f;
                Center.z = 0.0f;
                CRot.y = 0.0f;
            }
            break;
        case 4:
            if (mgFlowResultF == 1) {
                for (i = 0; i < 4; i++) {
                    player = mgPlayerObjTbl[i];
                    if (m227_playerLoseTbl[m227_shooterPlayerTbl[i]] == 0) {
                        work = player->data;
                        MgPlayerMotSet(player, 5);
                        chr = GwPlayer[work->playerIndex].chr;
                        chrData = omCharModelNoTbl[chr][0];
                        CharAnimSet(player->model[0], 2, chr, player->model[4]);
                        HuAudCharVoicePlay(chrData | 0x2F);
                        GwPlayer[work->playerIndex].bonusCoin += 10;
                    } else {
                        MgPlayerMotSet(player, 6);
                    }
                }
            }
            break;
        case 5:
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            object->func = m227_ExitObjMain;
            break;
    }
    MgShadowSlopeSet(object->model[4], &m227_holeNormal);
    for (i = 0; i < 5; i++) {
        x = sindf(m227_cloudAngleTbl[i]) * m227_cloudDistTbl[i];
        Hu3DModelPosSet(object->model[7 + i], x, m227_cloudYTbl[i],
                        cosdf(m227_cloudAngleTbl[i]) * m227_cloudDistTbl[i] - 1000.0f);
        Hu3DModelRotSet(object->model[7 + i], 0.0f, CRot.y, 0.0f);
        scale = sindf(m227_cloudScaleAngleTbl[i]) * 0.25f + 2.5f;
        Hu3DModelScaleSet(object->model[7 + i], scale, scale, scale);
        m227_cloudScaleAngleTbl[i] =
            HuAngleWrap(m227_cloudSpeedTbl[i] * 30.0f + m227_cloudScaleAngleTbl[i]);
        m227_cloudAngleTbl[i] =
            HuAngleWrap(m227_cloudAngleTbl[i] + m227_cloudSpeedTbl[i]);
        if (m227_cloudAngleTbl[i] > 260.0f) {
            m227_cloudAngleTbl[i] = 100.0f;
        }
    }
    for (i = 0; i < mgPlayerObjNum; i++) {
        ((ChipShotChallengeWork *)mgPlayerObjTbl[i]->data)->unk_60 = CRot.y;
    }
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
        object->func = m227_ExitObjMain;
    }
}

void m227_MapObjInit(omObjData *object) {
    ChipShotChallengeCourseWork *work;
    ChipShotChallengeSphere sphere;
    f32 angle;
    f32 dist;
    s32 tag = 0x2B9;

    mgPlayerAccel = 20.0f;
    if (rand8() > 128) {
        object->model[0] = Hu3DModelRead2(0x3C0000, tag);
    } else {
        object->model[0] = Hu3DModelRead2(0x3C0001, tag);
    }
    object->model[1] = Hu3DModelRead2(0x3C0002, tag);
    object->model[2] = Hu3DModelRead2(0x3C0003, tag);
    object->model[3] = Hu3DModelRead2(0x3C0004, tag);
    object->model[4] = Hu3DModelRead2(0x3C0005, tag);
    object->model[5] = Hu3DModelRead2(0x3C0009, tag);
    MgShadowMdlInit(object->model[4]);
    m227_lakituMdl = object->model[6] = Hu3DModelRead2(0xA0089, tag);
    object->model[7] = Hu3DModelRead2(0x210029, tag);
    object->model[8] = Hu3DModelLink(object->model[7]);
    object->model[9] = Hu3DModelLink(object->model[7]);
    object->model[10] = Hu3DModelLink(object->model[7]);
    object->model[11] = Hu3DModelLink(object->model[7]);
    Hu3DModelScaleSet(object->model[7], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(object->model[8], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(object->model[9], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(object->model[10], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(object->model[11], 2.0f, 2.0f, 2.0f);
    object->trans.x = 0.0f;
    object->trans.y = 0.0f;
    object->trans.z = -1000.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    work = HuMemAllocTag(sizeof(ChipShotChallengeCourseWork), TAG_OVERLAY);
    object->data = work;
    memset(work, 0, sizeof(ChipShotChallengeCourseWork));
    object->func = m227_MainObjMain;
    work->unk_03 = 1;
    MgMapTiltOn(object);
    MgMapAttrSet(object, 1, 0.0f);
    MgMapFrictionSet(object, 0.1f);
    MgMapAccelSet(object, mgPlayerAccel);
    MgMapSlideSet(object, 25.0f);
    MgMapNoBumpOn(object);
    work->unk_04 = 0;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    while (TRUE) {
        angle = rand8() * (360.0f / 255.0f);
        if (angle > 10.0f && (!(angle > 170.0f) | !(angle < 190.0f)) && angle < 350.0f) {
            break;
        }
    }
    dist = rand8() * 1.5f;
    if (dist < 200.0f) {
        dist = 200.0f;
    }
    m227_holePos.x = sindf(angle) * dist;
    m227_holePos.y = 50.0f;
    m227_holePos.z = cosdf(angle) * dist + -1000.0f;
    sphere.pos.x = m227_holePos.x;
    sphere.pos.y = 50.0f;
    sphere.pos.z = m227_holePos.z;
    m227_holePos.y = m227_FloorYGet(&sphere, &m227_holeNormal);
    Hu3DModelScaleSet(object->model[4], 0.625f, 0.625f, 0.625f);
    Hu3DModelPosSet(object->model[4], m227_holePos.x, m227_holePos.y + 5.0f,
                    m227_holePos.z);
    Hu3DModelPosSet(object->model[5], m227_holePos.x, m227_holePos.y - 10.0f,
                    m227_holePos.z);
    m227_ConfettiCreate();
}

void m227_ConfettiCreate(void) {
    s32 files[4] = { 0xB002B, 0xB002C, 0xB002D, 0xB002E };
    s16 model;
    s16 i;

    for (i = 0; i < 4; i++) {
        model = Hu3DModelRead(files[i], 0xAA9);
        m227_confettiMdlTbl[i] = model;
        Hu3DAnmNoSet(Hu3DAnimRead(Hu3DData[model].hmf, 0xB0048, "e268p01_I8"), i * 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelObjAttrSet(model, 0x20000, 0x20000);
        Hu3DModelRemakeStatic(model);
        Hu3DModelVtxBufMake(model);
        Hu3DModelDynamicFree(model);
        Hu3DParticleCreate(model, -1, 0, m227_ConfettiHook);
    }
}

void m227_ConfettiUpdate(void) {
    s32 *entries;
    s16 i;

    for (i = 0, entries = m227_confettiMdlTbl; i < 4; i++) {
        if (((m227_confettiFrame + i) & 3) == 0) {
            m227_ConfettiEmit(entries[i]);
        }
    }
    m227_confettiFrame++;
}

void m227_ConfettiEmit(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = effect->unk58;
    s16 count = hmf->unk1A;
    s16 i;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk10 <= 0.0f) {
            particle->unk0C = (rand8() - 127.0f) * 2.0f;
            particle->unk10 = m227_holePos.y + 700.0f;
            particle->unk14 = ((rand8() * 125) >> 5) - 500;
            particle->unk18 = ((s32)((rand8() * 5U) >> 7) - 5) / 2.0f;
            particle->unk1C = 0.0f;
            particle->unk20 = ((s32)((rand8() * 5U) >> 7) - 5) / 2.0f;
            particle->unk08 = 5.0f;
            break;
        }
    }
}

void m227_ConfettiHook(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 count = hmf->unk1A;
    s16 i;

    if (effect->unk02 == 0) {
        effect->unk04 &= ~4;
        for (i = 0, particle = effect->unk58; i < count; i++, particle++) {
            particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
            particle->unk24 = particle->unk28 = particle->unk2C = 0.0f;
            particle->unk08 = 0.0f;
            particle->unk04 = 1.0f;
        }
        effect->unk02++;
    }
    for (i = 0, particle = effect->unk58; i < count; i++, particle++) {
        if (particle->unk10 > 0.0f) {
            particle->unk0C += particle->unk18;
            particle->unk10 += particle->unk1C - 15.0f;
            particle->unk14 += particle->unk20;
        } else {
            particle->unk08 = 0.0f;
        }
    }
}

void m227_ArcObjInit(omObjData *object) {
    void *data;
    s16 image1;
    s16 image2;
    s16 group;
    s16 i;
    s16 x;

    Hu3DMatAmbScale = Hu3DMatColScale = 0.0f;
    object->model[1] = Hu3DModelRead2(0x3C0007, 0xAD9);
    object->model[2] = Hu3DModelRead2(0x3C0007, 0xAD9);
    object->model[3] = Hu3DModelRead2(0x3C0007, 0xAD9);
    object->model[4] = Hu3DModelRead2(0x3C0007, 0xAD9);
    object->model[5] = Hu3DModelRead2(0x3C0007, 0xAD9);
    object->model[6] = Hu3DModelRead2(0x3C0007, 0xAD9);
    object->model[7] = Hu3DModelRead2(0x3C0007, 0xAD9);
    object->model[8] = Hu3DModelRead2(0x3C0007, 0xAD9);
    object->model[9] = Hu3DModelRead2(0x3C0007, 0xAD9);
    object->model[10] = Hu3DModelRead2(0x3C0007, 0xAD9);
    Hu3DMatColScale = 1.0f;
    Hu3DMatAmbScale = 1.0f;
    object->func = m227_ArcObjMain;

    data = DataRead(0x2D);
    image1 = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x3C001F);
    image2 = HuSprAnimRead(data);
    DataClose(data);

    group = m227_distDigitGrp = HuSprGrpCreate(4, 5);
    HuSprGrpMemberSet(group, 0, image1, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprDispOff(group, 0);
    HuSprPosSet(group, 0, 0x80, 0x64);
    HuSprPriSet(group, 0, 1);
    x = 15;
    for (i = 1; i < 4; i++) {
        HuSprPriSet(group, i, 1);
        HuSprGrpMemberSet(group, i, image1, 0);
        HuSprPosSet(group, i, x, 0);
        HuSprAttrReset(group, i, 0xFFFF);
        HuSprDispOff(group, i);
        if (i == 1) {
            x += 20;
        } else {
            x += 15;
        }
        HuSprParentSet(group, i, 0);
    }
    HuSprDispOn(group, 2);

    group = m227_distUnitGrp = HuSprGrpCreate(2, 5);
    HuSprGrpMemberSet(group, 0, image2, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprDispOff(group, 0);
    HuSprPosSet(group, 0, 0x9F, 0x64);
    HuSprPriSet(group, 0, 1);
    HuSprPriSet(group, 1, 1);
    HuSprGrpMemberSet(group, 1, image2, 0);
    HuSprPosSet(group, 1, 0x23, 0);
    HuSprAttrReset(group, 1, 0xFFFF);
    HuSprDispOff(group, 1);
    HuSprParentSet(group, 1, 0);
    HuSprDispOn(group, 2);

    m227_missSignMdl = Hu3DModelRead2(0x3C001D, 0xAD9);
    m227_cupInSignMdl = Hu3DModelRead2(0x3C001C, 0xAD9);
}

void m227_DistDisp(s16 value) {
    s16 digit;

    if ((s16)(value / 1000) != 0) {
        HuSprDispOn(m227_distDigitGrp, 0);
        HuSprBankSet(m227_distDigitGrp, 0, value / 1000, 0);
        HuSprAnimModeSet(m227_distDigitGrp, 0, HUSPR_ANIM_MODE_BANK);
    }
    value -= (s16)(value / 1000) * 1000;
    HuSprDispOn(m227_distDigitGrp, 1);
    digit = value / 100;
    HuSprBankSet(m227_distDigitGrp, 1, digit, 0);
    HuSprAnimModeSet(m227_distDigitGrp, 1, HUSPR_ANIM_MODE_BANK);
    value -= digit * 100;
    HuSprDispOn(m227_distDigitGrp, 2);
    digit = value / 10;
    HuSprBankSet(m227_distDigitGrp, 2, digit, 0);
    HuSprAnimModeSet(m227_distDigitGrp, 2, HUSPR_ANIM_MODE_BANK);
    value -= digit * 10;
    HuSprDispOn(m227_distDigitGrp, 3);
    HuSprBankSet(m227_distDigitGrp, 3, value, 0);
    HuSprAnimModeSet(m227_distDigitGrp, 3, HUSPR_ANIM_MODE_BANK);
    HuSprDispOn(m227_distUnitGrp, 0);
    HuSprPatNoSet(m227_distUnitGrp, 0, 1);
    HuSprDispOn(m227_distUnitGrp, 1);
    HuSprPatNoSet(m227_distUnitGrp, 1, 0);
}

void m227_CupInLakituUpdate(void) {
    Vec dir;
    f32 x, y, z;

    x = dir.x = m227_ballObj->trans.x;
    dir.y = m227_ballObj->trans.y;
    z = dir.z = m227_ballObj->trans.z;
    MapVecNormalize(&dir);
    if (m227_ballStopTimer < 31) {
        y = m227_holePos.y + 700.0f - m227_ballStopTimer * 10.0f;
        Center.y *= 1.02f;
        m227_lakituBobAngle = -9.0f;
        if (m227_lakituSeF != 0) {
            HuAudFXPlay(0x3DF);
            m227_lakituSeF = 0;
        }
    } else {
        y = m227_holePos.y + 400.0f + sindf(m227_lakituBobAngle) * 100.0f;
        m227_lakituBobAngle -= 9.0f;
        Center.y *= 1.02f;
        m227_lakituSeF = -1;
    }
    if (m227_ballStopTimer < 101) {
        m227_ConfettiUpdate();
    }
    Hu3DModelPosSet(m227_confettiMdlTbl[0], m227_holePos.x,
                    m227_holePos.y, m227_holePos.z);
    Hu3DModelPosSet(m227_confettiMdlTbl[1], m227_holePos.x,
                    m227_holePos.y, m227_holePos.z);
    Hu3DModelPosSet(m227_confettiMdlTbl[2], m227_holePos.x,
                    m227_holePos.y, m227_holePos.z);
    Hu3DModelPosSet(m227_confettiMdlTbl[3], m227_holePos.x,
                    m227_holePos.y, m227_holePos.z);
    if (m227_holePos.y + 400.0f < Center.y) {
        Center.y = m227_holePos.y + 400.0f;
    }
    Hu3DModelPosSet((s16)m227_lakituMdl, x, y, z);
    Hu3DModelPosSet(m227_cupInSignMdl, x, y, z);
    Hu3DModelRotSet((s16)m227_lakituMdl, 0.0f, CRot.y, 0.0f);
    Hu3DModelRotSet(m227_cupInSignMdl, 0.0f, CRot.y, 0.0f);
    Hu3DModelAttrSet(m227_cupInSignMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet((s16)m227_lakituMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void m227_MissLakituUpdate(void) {
    Vec dir;
    f32 x, y, z;

    x = dir.x = m227_ballObj->trans.x;
    dir.y = m227_ballObj->trans.y;
    z = dir.z = m227_ballObj->trans.z;
    MapVecNormalize(&dir);
    if (m227_ballStopTimer == 1) {
        HuAudPlayerFXPlay(0x3DC, (s16)m227_shooterNo);
    }
    if (m227_ballStopTimer < 31) {
        y = m227_ballStopTimer * 10.0f + -200.0f;
    } else {
        y = 100.0f;
    }
    x += dir.x * 200.0f;
    z += dir.z * 200.0f;
    Hu3DModelPosSet((s16)m227_lakituMdl, x, y, z);
    Hu3DModelPosSet(m227_missSignMdl, x, y, z);
    Hu3DModelRotSet((s16)m227_lakituMdl, 0.0f, CRot.y, 0.0f);
    Hu3DModelRotSet(m227_missSignMdl, 0.0f, CRot.y, 0.0f);
    Hu3DModelAttrSet(m227_missSignMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet((s16)m227_lakituMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void m227_SignDispOff(void) {
    HuSprDispOff(m227_distDigitGrp, 0);
    HuSprDispOff(m227_distDigitGrp, 1);
    HuSprDispOff(m227_distDigitGrp, 2);
    HuSprDispOff(m227_distDigitGrp, 3);
    HuSprDispOff(m227_distUnitGrp, 0);
    HuSprDispOff(m227_distUnitGrp, 1);
    Hu3DModelAttrSet(m227_missSignMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(m227_cupInSignMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    if (MgFlowStatGet() >= MG_STATE_PLAY) {
        Hu3DModelAttrSet((s16)m227_lakituMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
}

void m227_BallObjInit(omObjData *object) {
    ChipShotChallengeWork *work;
    s32 i;

    object->data = HuMemAllocTag(sizeof(ChipShotChallengeWork), TAG_OVERLAY);
    memset(object->data, 0, sizeof(ChipShotChallengeWork));
    work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);
    object->model[0] = Hu3DModelRead2(0x3C0008, 0xAB9);
    object->model[1] = Hu3DModelRead3(9, 0xAB9);
    MgShadowMdlInit(object->model[1]);
    work->unk_44 = 0.3f;
    work->unk_48 = 60.0f;
    work->unk_34 = 50.0f;
    work->unk_3C = 0.0f;
    work->unk_78 = 0;
    work->unk_52 = 7;
    work->unk_7C = 0;
    work->unk_50 = 0;
    work->unk_40 = 0.0f;
    work->unk_38 = 1000.0f;
    work->unk_74 = 0.5f;
    work->unk_54 = 1;
    for (i = 0; i < 9; i++) {
        work->unk_84[i] = 0;
    }
    MgPlayerMapAttrSet(object, 0, 2);
    object->scale.x = object->scale.y = object->scale.z = 0.5f;
    Hu3DModelScaleSet(object->model[1], 0.4f, 0.4f, 0.4f);
    object->func = m227_BallObjMain;
}

MgPlayerWork *m227_PlayerInit(omObjData *object, s32 player) {
    MgPlayerWork *data;
    s32 i;
    s32 chr;
    s32 model;
    s32 motion;
    s32 tag;

    motion = omCharModelNoTbl[GwPlayer[player].chr][2];
    model = omCharModelNoTbl[GwPlayer[player].chr][0];
    tag = 0xAA9;
    chr = GwPlayer[player].chr;
    for (i = 0; i < object->mdlcnt; i++) {
        object->model[i] = 0;
    }
    data = HuMemAllocTag(0x15C, TAG_OVERLAY);
    object->data = data;
    memset(data, 0, 0x15C);
    data->unkE8 = HuMemAllocTag(object->mtncnt * 3 * sizeof(s32), TAG_OVERLAY);
    object->model[0] = Hu3DModelRead2(model | motion, tag);
    object->model[1] = Hu3DModelRead2(9, tag);
    CharAnimCreate(object->model[0], 2, chr, CharMotionDataNumGetTbl(chr, 2, 0));
    object->model[4] = Hu3DAnimDataRead(CharMotionDataNumGetTbl(chr, 2, 1));
    MgPlayerMotRead(object, 0, CharMotionDataNumGet(chr, 0), 1, 0);
    MgPlayerMotRead(object, 1, CharMotionDataNumGet(chr, 1), 1, 0);
    MgPlayerMotRead(object, 2, CharMotionDataNumGet(chr, 0x5E), 1, 0);
    MgPlayerMotRead(object, 3, CharMotionDataNumGet(chr, 0x5F), 0, 0);
    MgPlayerMotRead(object, 5, CharMotionDataNumGet(chr, 0x2F), 0, 0);
    MgPlayerMotRead(object, 6, CharMotionDataNumGet(chr, 0x36), 0, 0);
    object->model[2] = Hu3DModelRead2((chr + 10) | 0x3C0000, tag);
    object->model[3] = Hu3DModelRead2((chr + 0x12) | 0x3C0000, 0x4AD);
    Hu3DModelHookSet(object->model[2], object->model[0], "item_hook");
    Hu3DModelAttrSet(object->model[2], 0x4000, 0x4000);
    Hu3DModelTPLvlInit(object->model[3]);
    Hu3DModelTPLvlSet(object->model[3], 0x80);
    data->unk40 = 50.0f;
    object->func = m227_PlayerObjMain;
    data->unk50 = 0;
    Hu3DMotionModelSet(object->model[0], object->motion[0]);
    Hu3DMotionAttrSet(object->model[0], 2, 2);
    object->rot.y = 90.0f;
    data->unk59 = player;
    data->unk57 = GwPlayer[player].pad;
    return data;
}

void m227_Player0ObjInit(omObjData *object) {
    MgPlayerWork *data = m227_PlayerInit(object, m227_shooterPlayerTbl[0]);

    object->trans.x = -300.0f;
    object->trans.z = 20.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    data->unk53[0] = 0;
}

void m227_Player1ObjInit(omObjData *object) {
    MgPlayerWork *data = m227_PlayerInit(object, m227_shooterPlayerTbl[1]);

    object->trans.x = -600.0f;
    object->trans.z = 20.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    data->unk53[0] = 1;
}

void m227_Player2ObjInit(omObjData *object) {
    MgPlayerWork *data = m227_PlayerInit(object, m227_shooterPlayerTbl[2]);

    object->trans.x = -900.0f;
    object->trans.z = 20.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    data->unk53[0] = 2;
}

void m227_Player3ObjInit(omObjData *object) {
    MgPlayerWork *data = m227_PlayerInit(object, m227_shooterPlayerTbl[3]);

    object->trans.x = -1200.0f;
    object->trans.z = 20.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    data->unk53[0] = 3;
}

void m227_PlayerObjMain(omObjData *object) {
    MgPlayerWork *data = OM_GET_DATA_PTR(object, MgPlayerWork);
    // z is left implicit so GCC doesn't merge this with the identical initializer in m227_BallFloorCheck
    Vec pos = { .x = 0.0f, .y = 1.0f };
    s32 stickX;
    s32 stickY;
    s32 buttons;
    ChipShotChallengeWork *shot;
    ChipShotChallengeWork *ball;
    s32 pad;
    s32 player;
    s32 i;

    pad = data->unk57;
    player = data->unk59;
    if (MgFlowStatGet() == MG_STATE_PLAY) {
        stickX = HuPadStkX[pad];
        stickY = HuPadStkY[pad];
        buttons = (u16)HuPadBtn[pad];
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
    } else {
        stickX = stickY = buttons = 0;
    }
    if (m227_shooterNo == data->unk53[0]) {
        m227_PlayerComInputGet(object, &stickX, &stickY, &buttons);
        switch (data->unk50) {
            case 0:
                MgPlayerMotSet(object, 1);
                data->unk50 = 1;
                break;
            case 1:
                object->trans.x += 5.0f;
                if (object->trans.x > -90.0f) {
                    MgPlayerMotSet(object, 2);
                    data->unk50 = 2;
                    m227_aimF = 1;
                    object->trans.x = -90.0f;
                    GMesCreate(GMES_MES_TIMER, 10, 0xA0, 0x18);
                    m227_aimTimer = 300;
                }
                MgShadowSlopeSet(m227_ballObj->model[1], &pos);
                m227_swingLevel -= 5;
                if (m227_swingLevel < 100) {
                    m227_swingLevel = 100;
                }
                break;
            case 2:
                GMesTimerValueSet(m227_aimTimer / 30 + 1);
                if ((buttons & A_BUTTON) || m227_aimTimer == 0) {
                    MgPlayerMotSet(object, 3);
                    data->unk50 = 3;
                    m227_aimF = 0;
                    m227_swingTimer = 0;
                    GMesTimerEnd();
                }
                data->unk3C -= stickX / 50.0f;
                if (data->unk3C > 30.0f) {
                    data->unk3C = 30.0f;
                }
                if (data->unk3C < -30.0f) {
                    data->unk3C = -30.0f;
                }
                data->unk40 -= stickY / 50.0f;
                if (data->unk40 > 100.0f) {
                    data->unk40 = 100.0f;
                }
                if (data->unk40 < 60.0f) {
                    data->unk40 = 60.0f;
                }
                m227_aimAngle = data->unk3C;
                m227_aimPower = data->unk40;
                m227_aimPowerRate = m227_aimPower / 20.0f;
                object->trans.x = sindf(data->unk3C + 90.0f) * -90.0f;
                object->trans.z = cosdf(data->unk3C + 90.0f) * -90.0f + 20.0f;
                object->rot.y = data->unk3C + 90.0f;
                CRot.y = data->unk3C / 40.0f;
                m227_aimTimer--;
                break;
            case 3:
                if (m227_swingTimer == 38) {
                    data->unk50 = 4;
                    shot = OM_GET_DATA_PTR(m227_ballObj, ChipShotChallengeWork);
                    shot->unk_40 = data->unk40 / 5.0f;
                    shot->unk_3C = data->unk3C + 180.0f;
                    shot->unk_38 = -1.2f - data->unk40 / 300.0f;
                    m227_ballMoveF = 1;
                    m227_cupInF = 0;
                    m227_ballOutF = 0;
                    HuAudPlayerFXPlay(0x3DA, player);
                    omVibrate(player, 5, 0, 5);
                }
                m227_swingTimer++;
                m227_swingLevel += 2;
                if (m227_swingLevel > 240) {
                    m227_swingLevel = 240;
                }
                break;
            case 4:
                if (fabs(CRot.y) < fabs(data->unk3C)) {
                    CRot.y *= 1.05f;
                }
                m227_swingLevel += 2;
                if (m227_swingLevel > 240) {
                    m227_swingLevel = 240;
                }
                m227_aimAngle -= m227_ballCurve;
                Center.x += sindf(m227_aimAngle + 180.0f) * m227_ballSpeed;
                Center.z += cosdf(m227_aimAngle + 180.0f) * m227_ballSpeed;
                if (m227_ballStopTimer < 70) {
                    break;
                }
                ball = OM_GET_DATA_PTR(m227_ballObj, ChipShotChallengeWork);
                if (m227_cupInF == 1 && m227_ballStopTimer < 151) {
                    break;
                }
                m227_shooterNo++;
                ball->unk_5C = 0.0f;
                ball->unk_60 = 0.0f;
                ball->unk_64 = 0.0f;
                if (m227_shooterNo == 4) {
                    MgFlowStatSet(MG_STATE_FINISH);
                    for (i = 0; i < 4; i++) {
                        mgPlayerObjTbl[i]->trans.x = m227_resultPosTbl[i][0];
                        mgPlayerObjTbl[i]->trans.y = m227_resultPosTbl[i][1];
                        mgPlayerObjTbl[i]->trans.z = m227_resultPosTbl[i][2];
                        mgPlayerObjTbl[i]->rot.y = 0.0f;
                        Hu3DModelPosSet(mgPlayerObjTbl[i]->model[1], m227_resultPosTbl[i][0],
                                        m227_resultPosTbl[i][1], m227_resultPosTbl[i][2]);
                        Hu3DModelAttrSet(mgPlayerObjTbl[i]->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        Hu3DModelAttrSet(mgPlayerObjTbl[i]->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        Hu3DModelAttrSet(mgPlayerObjTbl[i]->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        if (m227_ballOutF != 1) {
                            Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                            Hu3DModelPosSet(object->model[3], m227_ballObj->trans.x,
                                            m227_ballObj->trans.y - 50.0f,
                                            m227_ballObj->trans.z);
                        }
                    }
                    Hu3DModelAttrSet(m227_ballObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(m227_ballObj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                } else {
                    mgPlayerObjTbl[m227_shooterNo]->trans.x = -200.0f;
                    data->unk50 = 5;
                    Hu3DModelPosSet(m227_ballObj->model[1], 0.0f, 3.0f, 0.0f);
                    MgShadowSlopeSet(m227_ballObj->model[1], &pos);
                    Hu3DModelAttrSet(m227_ballObj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    if (m227_ballOutF != 1) {
                        Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        Hu3DModelPosSet(object->model[3], m227_ballObj->trans.x,
                                        m227_ballObj->trans.y - 50.0f,
                                        m227_ballObj->trans.z);
                    }
                    m227_ballMoveF = 0;
                    object->trans.x = -90.0f;
                    m227_ballObj->trans.x = m227_ballObj->trans.y =
                        m227_ballObj->trans.z = 0.0f;
                    ball->unk_3C = ball->unk_40 = 0.0f;
                    ball->unk_38 = 1000.0f;
                    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Center.x = 0.0f;
                    Center.y = 200.0f;
                    Center.z = 0.0f;
                    CRot.y = 0.0f;
                }
                MgPlayerMotSet(object, 0);
                m227_ballStopTimer = 0;
                m227_aimAngle = m227_aimPower = 0.0f;
                break;
            case 5:
            case 6:
                break;
        }
        Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    }
    MgPlayerMotUpdate(object);
    if (m227_ballStopTimer == 0) {
        m227_SignDispOff();
    }
}

void m227_ArcObjMain(omObjData *object) {
    Vec delta;
    f32 rotX;
    f32 x;
    f32 y;
    f32 z;
    f32 step;
    f32 baseScale;
    f32 scaleStep;
    f32 scale;
    s32 i;

    if (m227_aimF == 1) {
        rotX = 90.0f;
        x = z = 0.0f;
        y = 20.0f;
        step = m227_aimPower / 3.0f;
        baseScale = (m227_aimPower - 60.0f) / 40.0f * 20.0f;
        scaleStep = m227_aimPower / 100.0f;
        for (i = 0; i < 10; i++) {
            Hu3DModelAttrSet(object->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            delta.x = x;
            delta.y = y;
            delta.z = z;
            y += step;
            step -= 0.1f;
            x += sindf(m227_aimAngle + 180.0f) * step;
            z += cosdf(m227_aimAngle + 180.0f) * step;
            delta.x -= x;
            delta.y -= y;
            delta.z -= z;
            Hu3DModelPosSet(object->model[i + 1], x, y, z);
            Hu3DModelRotSet(object->model[i + 1], rotX, 0.0f, 0.0f);
            scale = baseScale + scaleStep * i + sindf(m227_arcWaveAngle) * 0.5f;
            if (scale >= 30.0f) {
                scale = 30.0f;
            }
            Hu3DMotionTimeSet(object->model[i + 1], scale);
            rotX -= 7.0f;
        }
        m227_arcWaveAngle += m227_aimPower / 10.0f;
        m227_arcRot = HuAngleWrap(m227_arcRot + 10.0f);
    } else {
        for (i = 0; i < 20; i++) {
            Hu3DModelAttrSet(object->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
    }
}

void m227_BallObjMain(omObjData *object) {
    ChipShotChallengeWork *work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);
    f32 x, y, z;
    f32 angle;
    f32 floorY;
    u8 bounce = TRUE;

    HuTranslateF(Hu3DData[object->model[0]].mtx, 0.0f, 30.0f, 0.0f);
    if (MgFlowStatGet() != MG_STATE_PLAY) {
        return;
    }
    mgMoveOfsX = mgMoveOfsZ = 0.0f;
    if (m227_ballMoveF != 1) {
        m227_cupInSeF = -1;
        return;
    }
    x = object->trans.x;
    y = object->trans.y;
    z = object->trans.z;
    angle = work->unk_3C;
    if (work->unk_38 != 1000.0f) {
        work->unk_40 -= 0.08f;
    } else {
        work->unk_40 -= 0.2f;
    }
    if (work->unk_40 < 0.0f) {
        work->unk_40 = 0.0f;
    }
    x += sindf(angle) * work->unk_40;
    z += cosdf(angle) * work->unk_40;
    if (work->unk_40 != 0.0f) {
        x += work->unk_5C;
        z += work->unk_64;
    }
    m227_ballSpeed = work->unk_40;
    if (work->unk_38 != 1000.0f) {
        y += work->unk_38 * work->unk_38 * (work->unk_38 >= 0.0f ? -25.0f : 25.0f);
        work->unk_38 += mgItemGravity;
        if (work->unk_38 > mgItemFallMax) {
            work->unk_38 = mgItemFallMax;
        }
        if (m227_cupInF == 1) {
            if (y <= m227_holePos.y - 40.0f) {
                work->unk_40 = 0.0f;
            }
            Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        } else {
            floorY = m227_BallCollide(object, x, y, z);
            if (y < floorY) {
                y = floorY;
                HuAudPlayerFXPlay(0x3DD, (s16)m227_shooterNo);
                if (bounce) {
                    work->unk_38 = -work->unk_38 * 0.45f;
                    if (work->unk_38 >= -0.3f) {
                        work->unk_38 = 1000.0f;
                    }
                }
            }
        }
    } else {
        y = m227_BallCollide(object, x, y, z);
    }
    MgObjPosSet(object, x + mgMoveOfsX, y, z + mgMoveOfsZ);
    m227_ballRotX -= cosdf(angle) * work->unk_40 + mgMoveOfsZ;
    m227_ballRotX = HuAngleWrap(m227_ballRotX);
    m227_ballRotZ = HuAngleWrap(m227_ballRotZ);
    object->rot.y = angle;
    mtxRotCat(Hu3DData[object->model[0]].mtx, m227_ballRotX, 0.0f, 0.0f);
    if (m227_ballObj->trans.y < -100.0f ||
        (m227_ballSpeed == 0.0f && m227_cupInF != 1)) {
        m227_ballStopTimer++;
        if (!(m227_ballObj->trans.y < -100.0f) && m227_floorHitF == 1) {
            x -= m227_holePos.x;
            y -= m227_holePos.y;
            z -= m227_holePos.z;
            m227_DistDisp(HuSqrtf(x * x + y * y + z * z));
        } else if (m227_cupInF == 1) {
            m227_CupInLakituUpdate();
            if (m227_cupInSeF == -1) {
                HuAudPlayerFXPlay(0x3DE, (s16)m227_shooterNo);
                m227_cupInSeF = 0;
                omVibrate(OM_GET_DATA_PTR(mgPlayerObjTbl[m227_shooterNo], ChipShotChallengeWork)
                              ->playerIndex,
                          10, 0, 10);
            }
        } else {
            m227_MissLakituUpdate();
            m227_holeDistTbl[m227_shooterPlayerTbl[m227_shooterNo]] = 10000.0f;
        }
    }
    if (m227_ballObj->trans.y < -100.0f) {
        m227_ballOutF = 1;
    }
}

f32 m227_BallCollide(omObjData *object, f32 x, f32 y, f32 z) {
    MgPlayerWork *data = object->data;
    ChipShotChallengeSphere sphere;

    sphere.pos.x = x;
    sphere.pos.y = y;
    sphere.pos.z = z;
    sphere.radius = data->unk48;
    m227_BallCupCheck(object, x, y, z);
    return m227_BallFloorCheck(object, &sphere);
}

void m227_BallCupCheck(omObjData *object, f32 x, f32 y, f32 z) {
    ChipShotChallengeWork *work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);
    f32 dx = m227_holePos.x - x;
    f32 dy = m227_holePos.y - y;
    f32 dz = m227_holePos.z - z;
    f32 dist = HuSqrtf(dx * dx + dy * dy + dz * dz);
    f32 angle;
    f32 sinAngle;

    if (dist < 11.875f) {
        if (m227_cupInF != 1) {
            work->unk_40 = 0.5f;
            m227_cupInF = 1;
        }
        if (work->unk_38 == 1000.0f) {
            work->unk_38 = 0.0f;
        }
        m227_ballCurve = 0.0f;
        m227_holeDistTbl[m227_shooterPlayerTbl[m227_shooterNo]] = 0.0f;
    } else if (dist < 25.0f) {
        m227_holeDistTbl[m227_shooterPlayerTbl[m227_shooterNo]] = dist;
        if (work->unk_38 == 1000.0f) {
            dist = 1.0f - (25.0f - dist) / 13.125f;
            angle = work->unk_3C - 90.0f;
            sinAngle = sindf(angle);
            m227_ballCurve = MgDirDot(dx, dz, sinAngle, cosdf(angle)) * dist * 20.0f;
            work->unk_3C -= m227_ballCurve;
            work->unk_40 -= dist * 0.5f;
            if (work->unk_40 < 2.0f) {
                work->unk_3C = atan2df(dx, dz);
                work->unk_40 = 5.0f;
                m227_ballCurve = 0.0f;
            }
        }
    } else {
        m227_holeDistTbl[m227_shooterPlayerTbl[m227_shooterNo]] = dist;
        m227_ballCurve = 0.0f;
    }
}

f32 m227_BallFloorCheck(omObjData *object, ChipShotChallengeSphere *sphere) {
    ChipShotChallengeWork *work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);
    Vec normal = { 0.0f, 1.0f, 0.0f };
    f32 y = sphere->pos.y;
    f32 floorY = m227_FloorYGet(sphere, &normal);
    f32 resultY = floorY;

    if (floorY < y - work->unk_34 || y + work->unk_34 <= floorY) {
        if (work->unk_38 == 1000.0f) {
            work->unk_38 = 0.0f;
        }
        resultY = y;
    }
    m227_BallSlopeSet(object, &normal);
    m227_BallShadowSet(object, sphere->pos.x, resultY, sphere->pos.z, floorY, &normal);
    return resultY;
}

void m227_BallShadowSet(omObjData *object, f32 x, f32 y, f32 z, f32 floorY, Vec *normal) {
    ChipShotChallengeWork *work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);
    f32 scale = 0.5f;
    f32 height = y - floorY;

    if (floorY == -65536.0f) {
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        return;
    }
    if (height != 0.0f) {
        if (height > 400.0f) {
            scale = 0.1f;
        } else {
            scale = 0.5 - fabs(height) / 1000.0;
        }
        work->unk_53 = -1;
    }
    Hu3DModelPosSet(object->model[1], x, floorY + 3.0f, z);
    Hu3DModelScaleSet(object->model[1], scale, 0.5f, scale);
    MgShadowSlopeSet(object->model[1], normal);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

f32 m227_FloorYGet(ChipShotChallengeSphere *sphere, Vec *normal) {
    Vec pos;
    Vec tmp;
    Vec dir;
    omObjData *object;
    Hu3DPoint *points;
    Hu3DQuad *quad;
    f32 x, y, z;
    f32 floorY;
    f32 hitY;
    s16 model;
    u8 transformed;

    m227_floorHitF = 0;
    object = mgMapObjTbl[0];
    x = sphere->pos.x;
    y = sphere->pos.y;
    z = sphere->pos.z;
    pos.x = x;
    pos.y = y;
    pos.z = z;
    MgMapPosLocalGet(mgMapMtx, mgMapInvMtx, &pos, object);
    floorY = -65536.0f;
    model = object->model[0];
    points = (Hu3DPoint *)Hu3DData[model].hmf->unk50;
    Hu3DQuadPoolCollect(model, &mgQuadPool, MgFloorFaceFilter, &pos);
    for (quad = Hu3DQuadPoolNext(&mgQuadPool); quad != NULL; quad = Hu3DQuadPoolNext(&mgQuadPool)) {
        transformed = FALSE;
        if (Hu3DData[model].pos.x != 0.0f || Hu3DData[model].pos.y != 0.0f ||
            Hu3DData[model].pos.z != 0.0f || Hu3DData[model].rot.x != 0.0f ||
            Hu3DData[model].rot.y != 0.0f || Hu3DData[model].rot.z != 0.0f) {
            tmp.x = x;
            tmp.y = y + 10.0f;
            tmp.z = z;
            MgMtxPosMult(mgMapInvMtx, &tmp);
            dir.x = tmp.x - pos.x;
            dir.y = tmp.y - pos.y;
            dir.z = tmp.z - pos.z;
            MapVecNormalize(&dir);
            MgFaceRayCross(pos.x, pos.y, pos.z, points, quad, &dir, &pos);
            MgMtxPosYMult(mgMapMtx, &pos);
            hitY = pos.y;
            transformed = TRUE;
        } else {
            hitY = MapCalcPoint(pos.x, pos.y, pos.z, points, quad);
        }
        if (floorY <= hitY && hitY < y + 150.0f) {
            m227_floorHitF = 1;
            floorY = hitY;
            if (normal != NULL) {
                MapTriNormalGet(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]], normal);
                if (transformed == TRUE) {
                    tmp.x = normal->x;
                    tmp.y = normal->y;
                    tmp.z = normal->z;
                    MgMtxDirMult(mgMapMtx, &tmp);
                    normal->x = tmp.x;
                    normal->y = tmp.y;
                    normal->z = tmp.z;
                    MapVecNormalize(normal);
                }
            }
        }
    }
    return floorY;
}

void m227_BallSlopeSet(omObjData *object, Vec *arg1) {
    ChipShotChallengeWork *work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);

    if (m227_floorHitF == 1 && work->unk_38 == 1000.0f) {
        work->unk_5C = arg1->x * m227_slopeAccel;
        work->unk_60 = arg1->y;
        work->unk_64 = arg1->z * m227_slopeAccel;
    } else {
        work->unk_5C = 0.0f;
        work->unk_60 = 0.0f;
        work->unk_64 = 0.0f;
    }
}

void m227_PlayerComInputGet(omObjData *object, s32 *stickX, s32 *stickY, s32 *buttons) {
    ChipShotChallengeWork *work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);
    f32 x, y, z;
    f32 angle;
    f32 dist;
    s32 playerIndex;
    s32 difficulty;

    if (GwPlayer[work->playerIndex].stat & 1) {
        *buttons = 0;
        *stickY = 0;
        *stickX = 0;
        x = m227_holePos.x;
        y = m227_holePos.y;
        z = m227_holePos.z;
        playerIndex = work->playerIndex;
        difficulty = GwPlayer[playerIndex].cpu_difficulty;
        if (m227_comAngleOfsTbl[playerIndex] == 1000.0f) {
            angle = (rand8() - 127.0f) / 128.0f * 5.0f * m227_comErrorScaleTbl[difficulty];
            m227_comAngleOfsTbl[playerIndex] = angle;
        }
        if (m227_comPowerOfsTbl[playerIndex] == 1000.0f) {
            dist = (rand8() - 127.0f) / 128.0f * 10.0f * m227_comErrorScaleTbl[difficulty];
            m227_comPowerOfsTbl[playerIndex] = dist;
        }
        dist = HuSqrtf(x * x + y * y + z * z);
        angle = atan2df(x, z) + m227_comAngleOfsTbl[playerIndex];
        if (angle < 0.0f) {
            angle += 180.0f;
        } else {
            angle -= 180.0f;
        }
        if (fabs(angle - work->unk_3C) > 1.0) {
            if (work->unk_3C < angle) {
                *stickX = -30;
            }
            if (angle < work->unk_3C) {
                *stickX = 30;
            }
        }
        dist = (dist - 150.0f) / 10.0f + m227_comPowerOfsTbl[playerIndex];
        dist *= 1.1f;
        if (dist < 65.0f) {
            dist = 65.0f;
        }
        if (dist > 100.0f) {
            dist = 100.0f;
        }
        if (fabs(dist - work->unk_40) > 10.0) {
            *stickY = !(work->unk_40 < dist) ? 30 : -30;
        }
        if (*stickX == 0 && *stickY == 0) {
            *buttons |= A_BUTTON;
        }
    }
}
