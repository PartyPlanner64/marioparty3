#include "common.h"
#include "game/overlays/minigame.h"

#define SPEED_SCALE 0.028935185185185185
#define ABS(x) ((x) > 0 ? (x) : -(x))
#define ABS_DIFF(a, b) (((a) - (b) > 0) ? (a) - (b) : (b) - (a))
#define SETTLE_ANGLE(angle) (((angle) < -10.0f) ? (angle) + 9.0f - (angle) * 0.1 : ((angle) > 10.0f) ? (angle) - 9.0f - (angle) * 0.1 \
                                                                                                     : 0.0f)
#define PEDAL_POWER(speed) (((speed) < 20.0f) ? 2.0f * (speed) - 20.0f : (speed))
#define ROWER_OFFSET()                              \
    ((m207_swimMotBlendLen == 0)             \
         ? rowerSpeeds[m207_swimMotCur] \
         : rowerSpeeds[m207_swimMotPrev] * (1.0f - (f32)m207_swimMotBlend / (f32)m207_swimMotBlendLen) + rowerSpeeds[m207_swimMotCur] * ((f32)m207_swimMotBlend / (f32)m207_swimMotBlendLen))

typedef struct RidiculousRelayPlayer {
    /* 0x00 */ s8 playerNo;
    /* 0x01 */ s8 group;
    /* 0x02 */ s8 pad;
    /* 0x03 */ s8 chr;
    /* 0x04 */ s8 cpuDifficulty; // -1 for human players
    /* 0x05 */ char unk_05[3];
    /* 0x08 */ s32 unk08; // run animation file
} RidiculousRelayPlayer;  // sizeof 0xC

extern Gfx *gMainGfxPos;

MinigameFlow m207_mgFlow = { 0 };

Gfx m207_backGfx[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTHI, SCREEN_HEIGHTI),
    gsSPEndDisplayList(),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTHI, SCREEN_HEIGHTI),
    gsSPEndDisplayList(),
};

u8 m207_frameToggleF = 0;
u32 m207_frameCnt = 0;
u32 m207_goalCntTbl[2] = { 0, 0 };
u8 m207_relayLegNo = 0;
u16 m207_hurdleHitTbl[18] = { 0 };
f32 m207_cameraPrevXTbl[2] = { 0.0f, 0.0f };
u16 m207_cameraHandoffCnt = 0;
f32 m207_distTbl[4] = { -142.5f, -142.5f, 653.125f, 1278.125f };
f32 m207_posYTbl[4] = { -60.0f, 0.0f, 0.0f, 0.0f };
f32 m207_speedTbl[4] = { 40.0f, 40.0f, 0.0f, 0.0f };
f32 m207_velYTbl[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
s16 m207_strokeTbl[4] = { 0, 0, 0, 0 };
s16 m207_motTimerTbl[4] = { 0, 0, 0, 0 };
u32 m207_flagCntTbl[2] = { 0, 0 };
u8 m207_soloComLane = 1;
f32 m207_soloComLaneDist = 16384.0f;
u8 m207_comWaitTbl[3] = { 0, 0, 0 };
u8 m207_swimMotPrev = 0;
u8 m207_swimMotCur = 0;
u8 m207_swimMotBlend = 0;
u8 m207_swimMotBlendLen = 1;
f32 m207_bikeBounce = 0.0f;
u8 m207_soloStunTimer = 0;
f32 m207_soloStunSpeed = 0.0f;
f32 m207_shotXTbl[2] = { -1000.0f, -1000.0f };
f32 m207_shotYTbl[2] = { 0.0f, 0.0f };
f32 m207_shotSpeedTbl[2] = { 75.0f, 75.0f };
u16 m207_shotWaitTbl[2] = { 0, 40 };
u8 m207_splashTimerTbl[4] = { 0, 0, 0, 0 };
u32 m207_goalFrameTbl[4] = { 0, 0, 0, 0 };
u8 m207_soloShotHitF = 0;
f32 m207_soloSpeedOfs = 0.0f;

f32 m207_cameraStep BSS;
u8 m207_cameraStepPad[4] BSS; /* Unreferenced. */
f32 m207_dropXTbl[18] BSS;
f32 m207_dropYTbl[18] BSS;
f32 m207_dropVelXTbl[18] BSS;
f32 m207_dropVelYTbl[18] BSS;
f32 m207_soloGoalX BSS;
f32 m207_soloGoalY BSS;
f32 m207_soloGoalVelX BSS;
f32 m207_soloGoalVelY BSS;
f32 m207_soloGoalRot BSS;
f32 m207_bikeGoalX BSS;
f32 m207_bikeGoalY BSS;
f32 m207_bikeGoalVelX BSS;
f32 m207_bikeGoalVelY BSS;
f32 m207_bikeGoalRot BSS;
RidiculousRelayPlayer m207_playerTbl[4] BSS;
RidiculousRelayPlayer *m207_groupPlayerTbl[4] BSS; // players indexed by group
f32 m207_promptXTbl[7] BSS;
f32 m207_scrollTbl[2] BSS;
u8 m207_scrollPad[4] BSS; /* Unreferenced. */
f32 m207_progressTbl[4] BSS;
u8 m207_playerGroupTbl[4] BSS; // group of each player
omObjData *m207_stageObj BSS;
s8 m207_winner BSS;
f32 m207_skyScrollStep BSS;
s32 m207_animCnt BSS;
u16 m207_exitF BSS;
f32 m207_waveScroll BSS;
s32 m207_phaseTimer BSS;
s16 m207_phase BSS;
u8 m207_quitCnt BSS;
f32 m207_waveY BSS;
s16 m207_sprAnimTbl[31] BSS;
omObjData *m207_playerObjTbl[4] BSS;
s32 m207_seNoTbl[3] BSS;
u8 m207_seNoPad[4] BSS; /* Unreferenced. */
u16 m207_sprMdlTbl[8] BSS;
f32 m207_skyScroll BSS;
u8 m207_skyScrollPad[4] BSS; /* Unreferenced. */
s16 m207_sprTbl[31] BSS;

const s16 m207_fontMesTbl[] = {
    0x8260, 0x8261, 0x8262, 0x8263, 0x8264, 0x8265, 0x8266, 0x8267, 0x8268, 0x8269, 0x826A, 0x826B, 0x826C, 0x826D,
    0x826E, 0x826F, 0x8270, 0x8271, 0x8272, 0x8273, 0x8274, 0x8275, 0x8276, 0x8277, 0x8278, 0x8279, 0x0000, 0x0000
};

void m207_MainObjInit(omObjData *object);
void m207_StageObjInit(omObjData *object);
void m207_Player0ObjInit(omObjData *object);
void m207_Player1ObjInit(omObjData *object);
void m207_Player2ObjInit(omObjData *object);
void m207_Player3ObjInit(omObjData *object);

void m207_MainObjMain(omObjData *object);
void m207_StageObjMain(omObjData *object);
void m207_BackDraw(omObjData *object);
void m207_PlayerInit(omObjData *object, s8 group);
void m207_PlayerObjMain(omObjData *object);
void m207_HudDraw(Gfx **gfxPos, s32 arg1, s32 arg2);
s16 m207_SePlay(s16 arg0, s16 arg1);
s16 m207_ChrSePlay(s16 seId, s16 playerIdx);

void m207_ObjectSetup(void) {
    omObjData *object;

    Hu3DSprModelInit(0x30);
    omInitObjMan(50, 0);
    omGameSysInit();
    Hu3DScreenClearF = 1;
    CamSetupInit(2);
    CamSetupMapCullAddMulti(2);
    ScissorSet(0, 0.0f, 0.0f, SCREEN_WIDTH, 120.0f);
    ScissorSet(1, 0.0f, 120.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 240.0f, 511.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 640.0f, 720.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 22.619865f, 375.0f, 1250.0f);
    Hu3DCameraPerspectiveSet(1, 22.619865f, 375.0f, 1250.0f);
    Hu3DGLightMaxSet(1);
    Hu3DGLightDirSet(0, 0.0f, 0.0f, 90.0f);
    Hu3DGLightColorSet(0, 0x90, 0x90, 0x90);
    Hu3DGLightDirSet(1, 0.0f, 40.0f, 110.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    CenterM[0].x = 0.0f;
    CenterM[0].y = 0.0f;
    CenterM[0].z = 0.0f;
    CRotM[0].x = 0.0f;
    CRotM[0].y = 0.0f;
    CRotM[0].z = 0.0f;
    CZoomM[0] = 468.75f;
    CenterM[1].x = 0.0f;
    CenterM[1].y = 0.0f;
    CenterM[1].z = 0.0f;
    CRotM[1].x = 0.0f;
    CRotM[1].y = 0.0f;
    CRotM[1].z = 0.0f;
    CZoomM[1] = 468.75f;
    omAddObj(0, 0, 0, -1, m207_MainObjInit);
    m207_stageObj = omAddObj(8, 35, 35, -1, m207_StageObjInit);
    omSetStatBit(m207_stageObj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    m207_playerObjTbl[0] = omAddObj(3, 3, 12, -1, m207_Player0ObjInit);
    m207_playerObjTbl[1] = omAddObj(3, 3, 12, -1, m207_Player1ObjInit);
    m207_playerObjTbl[2] = omAddObj(3, 3, 12, -1, m207_Player2ObjInit);
    m207_playerObjTbl[3] = omAddObj(3, 3, 12, -1, m207_Player3ObjInit);
    object = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    object->work[0] = 2;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    GMesFontMesCreate(m207_fontMesTbl, 1);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    m207_mgFlow.type = MINIGAME_2V2;
    m207_mgFlow.startDelay = -1;
    m207_mgFlow.startDelay = 45;
    m207_mgFlow.timer = 9000;
    m207_mgFlow.timeDisp = MG_TIME_DISP_NONE;
    m207_mgFlow.timerMode = MG_TIMER_COUNT_DOWN;
    m207_mgFlow.finishDelay = 45;
    m207_mgFlow.resultDelay = 165;
    m207_mgFlow.newRecord = FALSE;
    m207_mgFlow.gauge = MG_GAUGE_NONE;
    m207_mgFlow.timeLimit = -1;
    MgFlowInit(&m207_mgFlow);
}

void m207_MainObjInit(omObjData *object) {
    s32 group;
    s32 i;

    m207_exitF = 0;
    m207_phase = 0;
    m207_phaseTimer = 0;
    m207_animCnt = 0;
    m207_winner = 5;
    m207_quitCnt = 0;
    m207_scrollTbl[0] = m207_scrollTbl[1] = 0.0f;
    m207_skyScrollStep = 0.0f;
    m207_skyScroll = 0.0f;
    m207_waveY = 0.0f;
    m207_waveScroll = 0.0f;
    m207_progressTbl[0] = m207_progressTbl[1] = m207_progressTbl[2] = m207_progressTbl[3] = 0.0f;
    m207_promptXTbl[0] = m207_promptXTbl[1] = m207_promptXTbl[2] = m207_promptXTbl[3] =
        m207_promptXTbl[4] = m207_promptXTbl[5] = m207_promptXTbl[6] = 0.0f;
    m207_seNoTbl[0] = m207_seNoTbl[1] = m207_seNoTbl[2] = -1;
    for (i = 0; i < 4; i++) {
        m207_groupPlayerTbl[i] = &m207_playerTbl[i];
        bzero(m207_groupPlayerTbl[i], sizeof(RidiculousRelayPlayer));
    }
    for (i = 0; i < 4; i++) {
        group = GwPlayer[i].group;
        m207_playerGroupTbl[i] = group;
        m207_groupPlayerTbl[group]->playerNo = i;
        m207_groupPlayerTbl[group]->pad = GwPlayer[i].pad;
        m207_groupPlayerTbl[group]->chr = GwPlayer[i].chr;
        m207_groupPlayerTbl[group]->group = group;
        m207_groupPlayerTbl[group]->cpuDifficulty = (GwPlayer[i].stat & PLAYER_IS_CPU) ? GwPlayer[i].cpu_difficulty : -1;
    }
    Hu3DHookFuncCreate(0, m207_HudDraw, 2);
    object->func = m207_MainObjMain;
}

void m207_MainObjMain(omObjData *object) {
    s32 i;
    u8 j;

    m207_phaseTimer++;
    m207_animCnt++;
    if (m207_phase == 1 && m207_phaseTimer == 31 && m207_exitF == 0 && omSysExitReq == 0) {
        HuAudSeqPlay(0x32);
    }
    MgFlowMain();
    switch (m207_phase) {
        case 0:
            if (m207_phaseTimer == 1 && m207_exitF == 0 && omSysExitReq == 0) {
                m207_seNoTbl[0] = HuAudFXPlay(0x32D);
                m207_seNoTbl[1] = HuAudFXPlay(0x32E);
            }
            if (MgFlowStatGet() == MG_STATE_START) {
                m207_phase = 1;
                m207_phaseTimer = 0;
            }
            break;
        case 1:
            if (MgFlowStatGet() == MG_STATE_PLAY) {
                m207_phase = 2;
                m207_phaseTimer = 0;
            }
            break;
        case 2:
            if (m207_winner != 5 || MgFlowStatGet() == MG_STATE_FINISH) {
                if (m207_winner == 5) {
                    m207_phase = 5;
                    m207_winner = 4;
                } else {
                    m207_phase = 3;
                }
                m207_phaseTimer = 0;
            }
            if (m207_phase != 3) {
                break;
            }
        case 3:
            if (m207_phaseTimer == 0) {
                if (MgFlowStatGet() != MG_STATE_FINISH) {
                    MgFlowStatNext();
                }
                if (m207_seNoTbl[2] != -1) {
                    HuAudFXStop((s16)m207_seNoTbl[2]);
                    m207_seNoTbl[2] = -1;
                }
                if (m207_winner == 0) {
                    m207_mgFlow.resultType = MG_RESULT_WIN_1;
                    m207_mgFlow.winners[0] = m207_groupPlayerTbl[0]->playerNo;
                    GwPlayer[m207_groupPlayerTbl[0]->playerNo].bonusCoin = 10;
                } else {
                    m207_mgFlow.resultType = MG_RESULT_WIN_3;
                    m207_mgFlow.winners[0] = m207_groupPlayerTbl[3]->playerNo;
                    m207_mgFlow.winners[1] = m207_groupPlayerTbl[1]->playerNo;
                    m207_mgFlow.winners[2] = m207_groupPlayerTbl[2]->playerNo;
                    GwPlayer[m207_groupPlayerTbl[1]->playerNo].bonusCoin = 10;
                    GwPlayer[m207_groupPlayerTbl[2]->playerNo].bonusCoin = 10;
                    GwPlayer[m207_groupPlayerTbl[3]->playerNo].bonusCoin = 10;
                }
            }
            if (m207_phaseTimer == 2) {
                MgFlowResultWaitSet(30);
            }
            if (m207_phaseTimer == 15) {
                for (i = 0; i < 3; i++) {
                    if (m207_seNoTbl[i] != -1) {
                        HuAudFXFadeOut(m207_seNoTbl[i], 15);
                        m207_seNoTbl[i] = -1;
                    }
                }
            }
            if (MgFlowStatGet() == MG_STATE_RESULT) {
                m207_phase = 4;
                m207_phaseTimer = 0;
            }
            break;
        case 5:
            if (m207_phaseTimer == 1) {
                m207_mgFlow.resultType = MG_RESULT_DRAW;
                m207_mgFlow.finishDelay = 75;
                m207_mgFlow.resultDelay = 0x90;
            }
            if (MgFlowStatGet() == MG_STATE_RESULT) {
                m207_phase = 6;
                m207_phaseTimer = 0;
            }
            break;
        case 4:
            if (m207_phaseTimer == 30) {
                if (m207_winner == 0) {
                    Hu3DMotionModelSet(m207_playerObjTbl[0]->model[0], m207_playerObjTbl[0]->motion[3]);
                    Hu3DMotionAttrSet(m207_playerObjTbl[0]->model[0], 3, 0);
                    HuAudCharVoicePlay(m207_groupPlayerTbl[0]->unk08);
                } else if (m207_winner == 1) {
                    Hu3DMotionModelSet(m207_playerObjTbl[3]->model[0], m207_playerObjTbl[3]->motion[3]);
                    Hu3DMotionAttrSet(m207_playerObjTbl[3]->model[0], 3, 0);
                    HuAudCharVoicePlay(m207_groupPlayerTbl[3]->unk08);
                }
            }
        case 6:
            if (MgFlowStatGet() == MG_STATE_EXIT) {
                m207_phase = 7;
                m207_phaseTimer = 0;
            }
            break;
        case 7:
            if (m207_phaseTimer == 1) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            } else if (m207_phaseTimer >= 32) {
                m207_exitF = 1;
            }
            break;
    }
    if (_CheckFlag(FLAG_MG_PRACTICE) && omSysExitReq == 0 && m207_quitCnt == 0 && (u16)m207_phase == 2) {
        for (j = 0; j < 2; j++) {
            if (m207_groupPlayerTbl[j]->cpuDifficulty == -1 && (HuPadBtnDown[m207_groupPlayerTbl[j]->pad] & R_TRIG)) {
                m207_quitCnt = 1;
            }
        }
    }
    if (m207_exitF != 0 || omSysExitReq != 0 || m207_quitCnt != 0) {
        if (omSysExitReq != 0 && m207_quitCnt == 0) {
            m207_quitCnt = 1;
        }
        if (m207_quitCnt != 0) {
            if (m207_quitCnt == 1) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                HuAudSeqFadeOut(20);
                HuAudFXAllFadeOut(20);
            }
            m207_quitCnt++;
            if (m207_quitCnt < 25) {
                return;
            }
        }
        HuAudSeqFadeOut(30);
        omOvlReturnEx(1);
    }
}

s16 m207_SprMdlCreate(s32 file, u16 *sprite, u16 flags) {
    void *data = DataRead(file);
    s16 anim = Hu3DAnimDataCreate(data);
    u16 idx;

    HuMemMemoryFreePerm(data);
    *sprite = idx = Hu3DSprModelCreate((void *)-1, flags, 0);
    Hu3DSprModelData[idx].unk_02 = anim;
    return Hu3DSprModelData[idx].modelId;
}

void m207_StageObjInit(omObjData *object) {
    s32 files[31] = { 0x28001B, 0x28001C, 0x28001E, 0x28001F, 0x280020, 0x28001D, 0x280021, 0x280022,
                      0x280023, 0x210008, 0x210009, 0x21000A, 0x21000B, 0x21000C, 0x21000D, 0x21000E,
                      0x21000F, 0x280029, 0x280024, 0x280025, 0x280026, 0x280027, 0x280028, 0x280013,
                      0x280014, 0x280015, 0x280016, 0x280017, 0x280018, 0x280019, 0x28001A };
    s16 i;

    for (i = 0; i < 31; i++) {
        m207_sprTbl[i] = espEntry(m207_sprAnimTbl[i] = HuSprAnimDataRead(files[i]), 0, 0);
        espDispOff(m207_sprTbl[i]);
    }
    object->model[0] = Hu3DModelRead(0xA00E7, 0x4B9);
    omSetSca(object, 0.3125f, 0.3125f, 0.3125f);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    object->model[2] = Hu3DModelRead(0x28000E, 0x39);
    Hu3DModelPosSet(object->model[2], 3787.5f, -26.25f, 0.0f);
    Hu3DModelScaleSet(object->model[2], 0.125f, 0.125f, 0.125f);
    Hu3DModelCameraSet(object->model[2], HU3D_CAM0);
    object->model[3] = Hu3DModelRead(0x28000F, 0x4B9);
    Hu3DModelPosSet(object->model[3], 3787.5f, -31.25f, 0.0f);
    Hu3DModelScaleSet(object->model[3], 0.125f, 0.125f, 0.125f);
    Hu3DModelCameraSet(object->model[3], HU3D_CAM1);
    object->model[1] = Hu3DModelRead(0x280010, 0x4B9);
    Hu3DModelScaleSet(object->model[1], 0.125f, 0.125f, 0.125f);
    Hu3DModelCameraSet(object->model[1], HU3D_CAM1);
    for (i = 0; i < 5; i++) {
        object->model[12 + i] = m207_SprMdlCreate(0x280011, &m207_sprMdlTbl[i], 0x639);
        Hu3DModelCameraSet(object->model[12 + i], HU3D_CAM0);
        Hu3DModelScaleSet(object->model[12 + i], 0.7565625f, 0.7565625f, 0.7565625f);
    }
    for (i = 0; i < 2; i++) {
        object->model[10 + i] = m207_SprMdlCreate(0x280012, &m207_sprMdlTbl[5], 0x639);
        Hu3DModelCameraSet(object->model[10 + i], HU3D_CAM0);
        Hu3DModelScaleSet(object->model[10 + i], 0.7565625f, 0.7565625f, 0.7565625f);
    }
    object->model[4] = m207_SprMdlCreate(0xB, &m207_sprMdlTbl[7], 0x639);
    Hu3DModelAttrSet(object->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelScaleSet(object->model[4], 1.6549804f, 0.9457031f, 0.9457031f);
    Hu3DModelCameraSet(object->model[4], HU3D_CAM0);
    for (i = 0; i < 18; i++) {
        if (i == 0) {
            object->model[17] = Hu3DModelRead(0x280006, 0x4B9);
        } else {
            object->model[17 + i] = Hu3DModelLink(object->model[17]);
        }
        Hu3DModelAttrSet(object->model[17 + i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelObjAttrSet(object->model[17 + i], 0x70000000, 0x70000000);
        Hu3DModelScaleSet(object->model[17 + i], 0.15625f, 0.15625f, 0.15625f);
        Hu3DModelCameraSet(object->model[17 + i], HU3D_CAM1);
    }
    object->model[6] = Hu3DModelRead(0x28000C, 0x4B9);
    Hu3DModelAttrSet(object->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DMotionAttrSet(object->model[6], 2, 2);
    Hu3DModelScaleSet(object->model[6], 0.15625f, 0.15625f, 0.15625f);
    Hu3DModelCameraSet(object->model[6], HU3D_CAM1);
    object->model[7] = Hu3DModelRead(0x28000D, 0x4B9);
    Hu3DModelAttrSet(object->model[7], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelScaleSet(object->model[7], 0.15625f, 0.15625f, 0.15625f);
    Hu3DModelCameraSet(object->model[7], HU3D_CAM1);
    object->model[8] = Hu3DModelLink(object->model[7]);
    Hu3DModelAttrSet(object->model[8], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelScaleSet(object->model[8], 0.15625f, 0.15625f, 0.15625f);
    Hu3DModelCameraSet(object->model[8], HU3D_CAM1);
    Hu3DMotionAttrSet(object->model[8], 2, 2);
    object->model[9] = Hu3DModelRead(0x28000D, 0x839);
    Hu3DModelAttrSet(object->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelScaleSet(object->model[9], 0.15625f, 0.15625f, 0.15625f);
    Hu3DModelCameraSet(object->model[9], HU3D_CAM1);
    Hu3DMotionAttrSet(object->model[9], 2, 2);
    object->model[5] = Hu3DModelRead(0x370003, 0x82D);
    Hu3DModelTPLvlInit(object->model[5]);
    Hu3DModelCameraSet(object->model[5], HU3D_CAM0);
    Hu3DModelScaleSet(object->model[5], 0.125f, 0.125f, 0.125f);
    object->func = m207_StageObjMain;
}

void m207_StageObjMain(omObjData *object) {
    m207_BackDraw(object);
    omPauseChk();
}

void m207_BackDraw(omObjData *object) {
    f32 scales[3] = { 0.25f, 0.5f, 0.8f };
    s32 signSprites[15] = { 3, 2, 3, 4, 3, 4, 3, 4, 3, 4, 3, 4, 3, 2, 3 };
    u8 is8Bit[6] = { 1, 1, 1, 1, 1, 1 };
    HuSprAnimPat *frame;
    HuSprite *sprite;
    s32 layer;
    s32 idx;
    s32 offset;
    f32 x;
    f32 y;
    f32 x2;
    f32 y2;
    s32 xl;
    s32 yl;
    s32 xh;
    s32 yh;
    s32 i;
    s32 j;
    s32 k;
    s32 row;
    s32 dist;

    gSPDisplayList(gMainGfxPos++, m207_backGfx);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 224);
    idx = 0;
    sprite = HuSprGet(esprite[m207_sprTbl[idx]].unk04, 0);
    frame = &sprite->data->pat[sprite->patNo];
    for (layer = 0; layer < 3; layer++) {
        if (layer == 0) {
            idx = 0;
            sprite = HuSprGet(esprite[m207_sprTbl[idx]].unk04, 0);
            frame = &sprite->data->pat[sprite->patNo];
            if (is8Bit[idx]) {
                gDPLoadTLUT_pal256(gMainGfxPos++, sprite->data->pal);
            } else {
                gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
            }
        }
        if (layer == 1) {
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 15; j++) {
                    offset = -m207_scrollTbl[i] * scales[layer] + (j - 1) * 320;
                    if (offset <= -320 || offset > 320) {
                        continue;
                    }
                    for (k = 0; k < 6; k++) {
                        x = (k % 3) * 40;
                        x2 = x + ((k % 3 < 2) ? 41.0f : 32.0f);
                        for (row = 0; row < 3; row++) {
                            y = (i == 0) ? row * 40 + 31 : row * 40 + 120;
                            if (row == 2) {
                                y2 = y + ((i == 0) ? 9.0f : 27.0f);
                            } else {
                                y2 = y + 41.0f;
                            }
                            xl = (x + ((k < 3) ? 13.0f : 197.0f) + offset) * 4.0f;
                            yl = y * 4.0f;
                            xh = (x2 + ((k < 3) ? 13.0f : 197.0f) + offset) * 4.0f;
                            yh = (s32)(y2 * 4.0f) - (i == 1 && row == 2) * 3;
                            if (xl >= 1280 || yl >= 960 || xh < 0 || yh < 0) {
                                continue;
                            }
                            idx = (k < 3) ? 1 : 5;
                            sprite = HuSprGet(esprite[m207_sprTbl[idx]].unk04, 0);
                            frame = &sprite->data->pat[sprite->patNo];
                            gDPLoadTLUT_pal256(gMainGfxPos++, sprite->data->pal);
                            gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_CI, G_IM_SIZ_8b, 112, 0, (s32)x,
                                               (s32)(y - 31.0f), (s32)x2, (s32)(y2 - 31.0f), 0,
                                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                                               G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                            gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, x * 32.0f,
                                                    (y - 31.0f) * 32.0f, 1024, 1024);
                        }
                    }
                }
            }
        } else {
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 15; j++) {
                    offset = -m207_scrollTbl[i] * scales[layer] + (j - 1) * 320;
                    if (offset <= -320 || offset > 320) {
                        continue;
                    }
                    if (layer != 0 && layer != 1) {
                        idx = (layer == 2) ? signSprites[j] : 0;
                        sprite = HuSprGet(esprite[m207_sprTbl[idx]].unk04, 0);
                        frame = &sprite->data->pat[sprite->patNo];
                        if (is8Bit[idx]) {
                            gDPLoadTLUT_pal256(gMainGfxPos++, sprite->data->pal);
                        } else {
                            gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
                        }
                    }
                    for (k = 0; k < 8; k++) {
                        x = k * 40;
                        x2 = x + 40.0f + ((k < 7) ? 1.0f : 0.0f);
                        for (row = 0; row < 3; row++) {
                            y = (row + i * 3) * 40 + (layer == 2 && row == 0 && i == 0) * 34;
                            y2 = y + 40.0f + ((row == 2) ? ((i == 0) ? 0.0 : -0.75) : 1.0);
                            xl = (x + offset) * 4.0f;
                            yl = y * 4.0f;
                            xh = (x2 + offset) * 4.0f;
                            yh = y2 * 4.0f;
                            if (xl >= 1280 || yl >= 960 || xh < 0 || yh < 0) {
                                continue;
                            }
                            if (layer == 2) {
                                y -= 34.0f;
                                y2 -= 34.0f;
                                gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 0,
                                                   (s32)x, (s32)y, (s32)x2, (s32)y2, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                                                   G_TX_NOLOD);
                            } else if (is8Bit[idx]) {
                                gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 0,
                                                   (s32)x, (s32)y, (s32)x2, (s32)y2, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                                                   G_TX_NOLOD);
                            } else {
                                gDPLoadTextureTile_4b(gMainGfxPos++, frame->data, G_IM_FMT_CI, 320, 0, (s32)x,
                                                      (s32)y, (s32)x2, (s32)y2, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                                      G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                                      G_TX_NOLOD, G_TX_NOLOD);
                            }
                            gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, x * 32.0f,
                                                    y * 32.0f, 1024, 1024);
                        }
                    }
                    if (layer == 2) {
                        dist = (j - 1) * 50;
                        if (dist >= 50 && dist <= 550) {
                            for (k = 0; k < 3; k++) {
                                s16 digitX[4] = { 159, 159, 135, 135 };
                                s16 digitY[4] = { 47, 147, 47, 147 };
                                s16 px;
                                s16 py;
                                if (dist == 50 && k == 0) {
                                    continue;
                                }
                                sprite = HuSprGet(
                                    esprite[m207_sprTbl[(k == 0)   ? dist / 100 + 17
                                                                                : (k == 1) ? dist / 10 % 10 + 17
                                                                                           : 17]]
                                        .unk04,
                                    0);
                                frame = &sprite->data->pat[sprite->patNo];
                                gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
                                gDPLoadTextureTile_4b(gMainGfxPos++, frame->data, G_IM_FMT_CI, 10, 14, 0, 0, 10, 14,
                                                      0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                                                      G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                                px = digitX[(dist / 100 * 100 == dist - 50) ? i + 2 : i];
                                py = digitY[(dist / 100 * 100 == dist - 50) ? i + 2 : i];
                                xl = (px + offset + k * 8 - ((dist == 50) ? 4 : 0)) * 4;
                                yl = py * 4;
                                xh = (px + 10 + offset + k * 8 - ((dist == 50) ? 4 : 0)) * 4;
                                yh = (py + 14) * 4;
                                gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, 0, 0, 1024,
                                                        1024);
                            }
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < 1; i++) {
        gDPPipeSync(gMainGfxPos++);
        if (i == 0) {
            gDPSetRenderMode(gMainGfxPos++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
            gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
            gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 128);
        } else {
            gDPSetRenderMode(gMainGfxPos++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
            gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);
            gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 224);
            gDPSetPrimColor(gMainGfxPos++, 0, 0, 0, 0, 0, 160);
            gDPSetCombineLERP(gMainGfxPos++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0,
                              PRIMITIVE, 0);
        }
        sprite = HuSprGet(esprite[m207_sprTbl[(i == 0) ? 6 : 7]].unk04, 0);
        frame = &sprite->data->pat[sprite->patNo];
        gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
        for (j = 0; j < 2; j++) {
            f32 scroll = m207_scrollTbl[i] + m207_skyScroll + 640.0f;

            offset = -(scroll - (s32)(scroll / 320.0f) * 320) + j * 320;
            for (k = 0; k < 8; k++) {
                x = k * 40;
                x2 = x + 40.0f + ((k < 7) ? 1.0f : 0.0f);
                y2 = i * 10 + 26;
                xl = (x + offset) * 4.0f;
                yl = (i * 125 + 115 - (i * 10 + 26)) * 4;
                xh = (x2 + offset) * 4.0f - 1.0f;
                yh = (i * 125 + 115) * 4;
                if (xl >= 1280 || xh < 0) {
                    continue;
                }
                y = 0.0f;
                gDPLoadTextureTile_4b(gMainGfxPos++, frame->data, G_IM_FMT_CI, 320, 0, (s32)x, (s32)y, (s32)x2, (s32)y2,
                                      0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                                      G_TX_NOLOD);
                gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, x * 32.0f, y * 32.0f, 1024,
                                        1024);
            }
        }
    }
}

void m207_HudDraw(Gfx **gfxPos, s32 arg1, s32 arg2) {
    HuSprAnimPat *frame;
    HuSprite *sprite;
    f32 scroll;
    f32 x;
    f32 y;
    f32 x2;
    f32 y2;
    s32 offset;
    s32 width;
    s32 height;
    s32 tileWidth;
    s32 i;
    s32 j;
    s32 k;
    s32 row;

    m207_frameToggleF = !m207_frameToggleF;
    if (m207_frameToggleF != 0) {
        return;
    }
    gSPDisplayList(gMainGfxPos++, m207_backGfx);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    for (i = 1; i < 2; i++) {
        gDPPipeSync(gMainGfxPos++);
        if (i == 0) {
            gDPSetRenderMode(gMainGfxPos++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
            gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
            gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 128);
        } else {
            gDPSetRenderMode(gMainGfxPos++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
            gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
            gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 128);
            gDPSetPrimColor(gMainGfxPos++, 0, 0, 0, 0, 0, 160);
            gDPSetCombineLERP(gMainGfxPos++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0,
                              PRIMITIVE, 0);
        }
        sprite = HuSprGet(esprite[m207_sprTbl[(i == 0) ? 6 : 7]].unk04, 0);
        frame = &sprite->data->pat[sprite->patNo];
        gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
        for (j = 0; j < 2; j++) {
            scroll = m207_waveScroll * 16.0f + m207_scrollTbl[i] + 640.0f;
            offset = -(scroll - (s32)(scroll / 320.0f) * 320) + j * 320;
            for (k = 0; k < 8; k++) {
                s32 xl;
                s32 yl;
                s32 xh;
                s32 yh;

                x = k * 40;
                x2 = x + 40.0f + ((k < 7) ? 1.0f : 0.0f);
                y2 = i * 10 + 26;
                xl = (x + offset) * 4.0f;
                yl = (((m207_waveY * -16.0f + 120.0f) * i + 120.0f) - y2) * 4.0f;
                xh = (x2 + offset) * 4.0f - 1.0f;
                yh = ((m207_waveY * -16.0f + 240.0f) * i + 120.0f) * 4.0f;
                if (xl >= 1280 || xh < 0) {
                    continue;
                }
                y = 0.0f;
                gDPLoadTextureTile_4b(gMainGfxPos++, frame->data, G_IM_FMT_CI, 320, 0, (s32)x, (s32)y, (s32)x2, (s32)y2,
                                      0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, 5, G_TX_NOLOD,
                                      G_TX_NOLOD);
                gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, x * 32.0f, y * 32.0f, 1024,
                                        1024);
            }
        }
    }
    gDPSetCombineMode(gMainGfxPos++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 224);
    for (i = 0; i < 8; i++) {
        f32 offsets[8] = { 40.0f, -40.0f, 40.0f, -40.0f, 40.0f, -40.0f, 0.0f, 0.0f };
        f32 scales[8] = { 0.75f, 0.75f, 0.75f, 0.75f, 0.75f, 0.75f, 0.75f, 0.75f };
        s32 xl;
        s32 yl;
        s32 xh;
        s32 yh;
        s32 dsdx;
        s32 dtdy;

        if (m207_promptXTbl[(i < 7) ? i : 6] == 0.0f) {
            continue;
        }
        width = (i == 7) ? 20 : 50;
        height = (i == 7) ? 22 : 50;
        tileWidth = (i >= 2 && i < 6) ? 80 : width;
        if (i == 7) {
            scales[7] = sindf((m207_animCnt % 12) / 12.0 * 360.0) * 0.125 + 0.8125;
        }
        x = m207_promptXTbl[(i < 7) ? i : 6] + offsets[i] - (tileWidth / 2) * scales[i];
        x2 = m207_promptXTbl[(i < 7) ? i : 6] + offsets[i] + (tileWidth / 2) * scales[i];
        if (x > SCREEN_WIDTH || x2 < 0.0f) {
            continue;
        }
        sprite = HuSprGet(esprite[m207_sprTbl[23 + i]].unk04, 0);
        frame = &sprite->data->pat[sprite->patNo];
        if (!(i >= 2 && i < 6)) {
            gDPLoadTextureTile_4b(gMainGfxPos++, frame->data, G_IM_FMT_CI, width, height, 0, 0, width, height, 0,
                                  G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                  G_TX_NOLOD, G_TX_NOLOD);
            gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
            if (i >= 6) {
                y = sindf((m207_animCnt % 30) / 30.0 * 360.0) * 4.0f + 159.0f;
            } else {
                y = 159.0f;
            }
            xl = x * 4.0f;
            yl = (y - (height / 2) * scales[i] - ((i == 7) ? 3.0f : 0.0f)) * 4.0f;
            xh = x2 * 4.0f;
            yh = (y + (height / 2) * scales[i] - ((i == 7) ? 3.0f : 0.0f)) * 4.0f - 3.0f;
            dsdx = width * 4.0 / (xh - xl) * 1024.0;
            dtdy = height * 4.0 / (yh - yl) * 1024.0;
            gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, 0, 0, dsdx, dtdy);
        } else {
            for (row = 0; row < 3; row++) {
                y = (row == 0) ? 0.0f : (row == 1) ? 17.0f
                                                   : 34.0f;
                y2 = (row == 0) ? 19.0f : (row == 1) ? 36.0f
                                                     : 49.0f;
                gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_CI, G_IM_SIZ_8b, 80, 0, 0, (s32)y, 80, (s32)y2,
                                   0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
                gDPLoadTLUT_pal256(gMainGfxPos++, sprite->data->pal);
                xl = x * 4.0f;
                yl = (y * scales[i] + 134.0f + (1.0f - scales[i]) * 25.0f) * 4.0f;
                xh = x2 * 4.0f;
                yh = (y2 * scales[i] + 134.0f + (1.0f - scales[i]) * 25.0f) * 4.0f;
                dsdx = 80 * 4.0 / (xh - xl) * 1024.0;
                dtdy = (y2 - y) * 4.0 / (yh - yl) * 1024.0;
                yh -= 3;
                gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, 0, (s32)(y * 32.0f), dsdx,
                                        dtdy);
            }
        }
    }
    sprite = HuSprGet(esprite[m207_sprTbl[8]].unk04, 0);
    frame = &sprite->data->pat[sprite->patNo];
    gDPLoadTLUT_pal256(gMainGfxPos++, sprite->data->pal);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);
    gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 0);
    for (k = 0; k < 6; k++) {
        gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 28, k * 59, 0, k * 59 + 60, 28, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
        x = k * 59;
        x2 = k * 59 + 60;
        x2 = MIN(SCREEN_WIDTH, x2);
        gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
        gSPScisTextureRectangle(gMainGfxPos++, (s32)(x * 4.0f), 106 * 4, (s32)(x2 * 4.0f), 134 * 4, G_TX_RENDERTILE,
                                (s32)(x * 32.0f), 0, 1024, 1024);
    }
    gDPSetCombineMode(gMainGfxPos++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 224);
    for (i = 0; i < 4; i++) {
        sprite = HuSprGet(esprite[m207_sprTbl[9 + m207_groupPlayerTbl[i]->chr]].unk04, 0);
        frame = &sprite->data->pat[sprite->patNo];
        if (m207_groupPlayerTbl[i]->chr == CHAR_DAISY) {
            gDPLoadTLUT_pal256(gMainGfxPos++, sprite->data->pal);
        } else {
            gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
        }
        if (m207_groupPlayerTbl[i]->chr == CHAR_DAISY) {
            gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_CI, G_IM_SIZ_8b, 18, 18, 0, 0, 18, 18, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                               G_TX_NOLOD);
        } else {
            gDPLoadTextureTile_4b(gMainGfxPos++, frame->data, G_IM_FMT_CI, 18, 18, 0, 0, 18, 18, 0,
                                  G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                  G_TX_NOLOD, G_TX_NOLOD);
        }
        switch (i) {
            case 0:
                x = m207_progressTbl[0] * 255.0f + 24.0f;
                break;
            case 1:
                x = m207_progressTbl[1] * 79.0f + 24.0f;
                break;
            case 2:
                x = m207_progressTbl[2] * 61.0f + 120.0f;
                break;
            case 3:
                x = m207_progressTbl[3] * 79.0f + 200.0f;
                break;
        }
        y = (i > 0) ? 120.0f : 102.0f;
        gSPScisTextureRectangle(gMainGfxPos++, (s32)x * 4, (s32)(y * 4.0f), ((s32)x + 18) * 4, (y + 18.0f) * 4.0f,
                                G_TX_RENDERTILE, 0, 0, 1024, 1024);
    }
    gDPPipeSync(gMainGfxPos++);
    gDPSetBlendColor(gMainGfxPos++, 255, 255, 255, 0);
    gDPPipeSync(gMainGfxPos++);
}

void m207_Player0ObjInit(omObjData *object) {
    m207_PlayerInit(object, 0);
    object->func = m207_PlayerObjMain;
}

void m207_Player1ObjInit(omObjData *object) {
    m207_PlayerInit(object, 1);
    object->func = NULL;
}

void m207_Player2ObjInit(omObjData *object) {
    m207_PlayerInit(object, 2);
    object->func = NULL;
}

void m207_Player3ObjInit(omObjData *object) {
    m207_PlayerInit(object, 3);
    object->func = NULL;
}

void m207_PlayerInit(omObjData *object, s8 group) {
    s32 dirs[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
    s32 files[8] = { 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 3 };
    s32 shadowFiles[4] = { 0, 1, 3, 5 };
    u16 chr = m207_groupPlayerTbl[group]->chr;

    m207_groupPlayerTbl[group]->unk08 = (rand8() & 1) ? 0x2F : 0x30;
    object->model[0] = Hu3DModelRead((dirs[chr] << 16) | files[chr], 0x4B9);
    switch (group) {
        case 0:
        case 3:
            omObjMotionRead(object, 0, CharMotionDataNumGet(chr, 0));
            omObjMotionRead(object, 1, CharMotionDataNumGet(chr, (group != 0) ? 0x7D : 0x7C));
            omObjMotionRead(object, 3, CharMotionDataNumGet(chr, m207_groupPlayerTbl[group]->unk08));
            omObjMotionRead(object, 4, CharMotionDataNumGet(chr, 0x3A));
            omObjMotionRead(object, 5, CharMotionDataNumGet(chr, 4));
            omObjMotionRead(object, 6, CharMotionDataNumGet(chr, 0x1F));
            if (group == 3) {
                Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            Hu3DMotionAttrSet(object->model[0], 1, 1);
            break;
        case 1:
            omObjMotionRead(object, 1, CharMotionDataNumGet(chr, 0x7E));
            object->model[2] = Hu3DModelRead(0x280002, 0x4B9);
            Hu3DModelScaleSet(object->model[2], 0.15625f, 0.15625f, 0.15625f);
            Hu3DModelCameraSet(object->model[2], (group == 0) ? 1 : 2);
            Hu3DModelHookSet(object->model[2], object->model[0], "item_hook");
            Hu3DModelAttrSet(object->model[2], HU3D_ATTR_HOOK, HU3D_ATTR_HOOK);
            break;
        case 2:
            omObjMotionRead(object, 1, CharMotionDataNumGet(chr, 0x7F));
            omObjMotionRead(object, 2, CharMotionDataNumGet(chr, 0x80));
            Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            object->model[2] = Hu3DModelRead(0x280004, 0x4B9);
            Hu3DModelScaleSet(object->model[2], 0.15625f, 0.15625f, 0.15625f);
            Hu3DMotionAttrSet(object->model[2], 1, 1);
            Hu3DModelCameraSet(object->model[2], (group == 0) ? 1 : 2);
            break;
    }
    m207_groupPlayerTbl[group]->unk08 |= dirs[chr] << 16;
    omSetSca(object, 0.15625f, 0.15625f, 0.15625f);
    Hu3DMotionModelSet(object->model[0], object->motion[1]);
    Hu3DModelObjAttrSet(object->model[0], 0x600, 0x400);
    Hu3DModelCameraSet(object->model[0], (group != 0) ? 2 : 1);
    object->model[1] = Hu3DModelRead(shadowFiles[group] | 0x280000, 0x4B9);
    Hu3DModelScaleSet(object->model[1], 0.15625f, 0.15625f, 0.15625f);
    Hu3DModelCameraSet(object->model[1], (group == 0) ? 1 : 2);
    if (group == 2) {
        omObjMotionRead(object, 7, 0x280007);
        omObjMotionRead(object, 8, 0x280008);
        omObjMotionRead(object, 9, 0x280009);
        omObjMotionRead(object, 10, 0x28000A);
        omObjMotionRead(object, 11, 0x28000B);
    }
}

f32 m207_ScreenXGet(f32 x) {
    Vec pos;
    Vec2f out;

    pos.x = x;
    pos.y = 0.0f;
    pos.z = 0.0f;
    Hu3DCam3Dto2D(1, &pos, &out);
    return out.x;
}

// `float best` and `int i` (instead of f32/s32) are deliberate: the typedef variants change fold/cross-jumping.
void m207_PlayerObjMain(omObjData *object) {
    f32 hurdleX[18] = { 0.0f, 32.0f, 64.0f, 96.0f, 128.0f, 128.0f, 160.0f, 192.0f, 224.0f,
                        256.0f, 288.0f, 320.0f, 352.0f, 384.0f, 384.0f, 416.0f, 448.0f, 480.0f };
    f32 hurdleLane[18] = { 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, -1.0f,
                           1.0f, -1.0f, 1.0f, 0.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f };
    f32 visX[5];
    f32 visY[5];
    u8 visIdx[5];
    f32 prevCenter[2] = { CenterM[0].x, CenterM[1].x };
    s32 visCount = 0;
    s16 cpuParams[3][3][4] = {
        { { 4, 3, 3, 2 }, { 12, 10, 9, 8 }, { 3, 2, 2, 2 } },
        { { 2, 3, 2, 2 }, { 6, 7, 6, 6 }, { 3, 5, 4, 3 } },
        { { 0, 0, 0, 0 }, { 10, 15, 30, 40 }, { 0, 0, 0, 0 } },
    };
    f32 rowerSpeeds[5] = { 0.0f, 27.0f, 54.0f, 81.0f, 54.0f };
    f32 waves[3];
    omObjData *obj;
    RidiculousRelayPlayer *player;
    int i;
    s32 j;
    s32 lane;
    u8 mode;
    f32 stickX;
    f32 stickY;
    f32 x;
    f32 y;

    mode = ((m207_phase == 1 && m207_phaseTimer >= 63) || m207_phase == 2)  ? 1
           : ((m207_phase == 1 && m207_phaseTimer < 63) || m207_phase == 0) ? 2
                                                                                                                          : 0;
    for (i = 0; i < 7; i++) {
        m207_promptXTbl[i] = 0.0f;
    }
    m207_waveScroll = (m207_frameCnt % 1200) / 1200.0 * 20.0;
    m207_waveY = sindf(m207_frameCnt * 4) * 0.2;
    waves[0] = sindf(m207_frameCnt % 60 * 6) * 20.0f;
    waves[1] = sindf(m207_frameCnt % 60 * 6 + 120) * 20.0f;
    waves[2] = sindf(m207_frameCnt % 60 * 6 + 240) * 20.0f;

    for (i = 0; i < 18; i++) {
        f32 hx = 2.0 * (hurdleX[i] + 60.0f) * 100.0 / 4.0 * 0.125;

        if (CenterM[0].x - 137.5 < hx && hx < CenterM[0].x + 137.5) {
            if (visCount >= 5) {
                break;
            }
            visIdx[visCount] = i;
            visX[visCount] = hx;
            visY[visCount] = (hurdleLane[i] * 200.0 + waves[i % 3] + m207_hurdleHitTbl[i] * 10.5) * 0.125;
            Hu3DModelPosSet(m207_stageObj->model[visCount + 12], visX[visCount], visY[visCount], -250.0f);
            Hu3DModelPosSet(m207_stageObj->model[visCount + 12], visX[visCount], visY[visCount], 0.0f);
            Hu3DModelAttrSet(m207_stageObj->model[visCount + 12], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            visCount++;
        }
    }
    for (i = visCount; i < 5; i++) {
        Hu3DModelAttrSet(m207_stageObj->model[i + 12], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }

    for (j = 0; j < 2; j++) {
        if (m207_shotXTbl[j] <= -1000.0f && m207_shotWaitTbl[j] != 0 && m207_phase == 2 && m207_distTbl[0] >= 50.0 && m207_distTbl[0] < 1775.0) {
            // Saturating decrement (same form as the unguarded timers); reuses the tested value.
            m207_shotWaitTbl[j] -= (m207_shotWaitTbl[j] != 0) ? 1 : 0;
        }
        if (m207_shotXTbl[j] <= -1000.0f && m207_shotWaitTbl[j] == 0 && m207_phase == 2 && m207_distTbl[0] >= 50.0 && m207_distTbl[0] < 1775.0) {
            m207_shotXTbl[j] = CenterM[0].x + 125.0;
            HuAudFXPlay(0x332);
            i = rand8() % 9;
            if (m207_phase == 2 && m207_distTbl[0] > m207_distTbl[m207_relayLegNo + 1]) {
                f32 laneDist[3] = { 16382.0f, 16382.0f, 16382.0f };
                float best = 0.0f;
                s32 start = rand8() % 3;
                s32 playerLane = m207_playerObjTbl[0]->trans.y / 0.125 + 125.0;

                playerLane = (playerLane >= 100) ? 2 : (playerLane >= -99);

                for (i = 0; i < visCount; i++) {
                    lane = (s32)hurdleLane[visIdx[i]] + 1;
                    if (m207_hurdleHitTbl[visIdx[i]] == 0 && m207_playerObjTbl[0]->trans.x < visX[i] + 12.5) {
                        laneDist[lane] = MIN(visX[i] + 100.0f - m207_playerObjTbl[0]->trans.x, laneDist[lane]);
                    }
                }
                for (i = 0, lane = 0; i < 3; i++) {
                    if (best < laneDist[(i + start) % 3] + ((playerLane == (i + start) % 3) ? 1.0f : 0.0f)) {
                        lane = (i + start) % 3;
                        best = laneDist[(i + start) % 3] + ((playerLane == (i + start) % 3) ? 1.0f : 0.0f);
                    }
                }
                if (laneDist[0] != 16382.0f || laneDist[1] != 16382.0f || laneDist[2] != 16382.0f) {
                    i = lane * 3 + rand8() % 3;
                } else {
                    i = rand8() % 9;
                }
            }
            m207_shotYTbl[j] = ((i / 3 - 1) * 200 + (i % 3 - 1) * 40) * 0.125;
        }
        m207_shotXTbl[j] -= m207_shotSpeedTbl[j] * SPEED_SCALE;
        if (m207_shotXTbl[j] <= CenterM[0].x - 137.5 && m207_shotXTbl[j] > -1000.0f) {
            m207_shotXTbl[j] = -1000.0f;
            m207_shotWaitTbl[j] = (m207_distTbl[0] < 250.0)    ? 20
                                             : (m207_distTbl[0] > 1250.0) ? 0
                                                                                         : (s32)((1250.0 - m207_distTbl[0]) / 1000.0 * 20.0);
        }
        if (m207_shotXTbl[j] <= -1000.0f) {
            Hu3DModelAttrSet(m207_stageObj->model[j + 10], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        } else {
            Hu3DModelPosSet(m207_stageObj->model[j + 10], m207_shotXTbl[j], m207_shotYTbl[j], 0.0f);
            Hu3DModelAttrSet(m207_stageObj->model[j + 10], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
    }

    // Group 0: hurdle runner
    obj = m207_playerObjTbl[0];
    player = m207_groupPlayerTbl[0];
    m207_goalCntTbl[0] += (m207_goalCntTbl[0] != 0 && m207_goalCntTbl[0] != 99 && m207_goalCntTbl[0] != 199 && m207_goalCntTbl[0] != 299);
    if (m207_goalCntTbl[0] != 0 && m207_goalCntTbl[0] < 100 && m207_distTbl[0] > 1900.0) {
        m207_goalCntTbl[0] = 100;
        Hu3DModelPosSet(m207_stageObj->model[4], obj->trans.x + 12.5, obj->trans.y - 3.125, obj->trans.z);
        Hu3DModelAttrSet(m207_stageObj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    if (m207_goalCntTbl[0] >= 100) {
        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        if (m207_goalCntTbl[0] == 100) {
            m207_soloGoalX = obj->trans.x;
            m207_soloGoalY = obj->trans.y;
            m207_soloGoalVelY = 0.0f;
            m207_soloGoalRot = 90.0f;
            m207_soloGoalVelX = 2.0 * (m207_speedTbl[0] * SPEED_SCALE);
            Hu3DMotionModelSet(obj->model[0], obj->motion[5]);
            Hu3DMotionAttrSet(obj->model[0], 2, 0);
            Hu3DMotionTimeSet(obj->model[0], 14.0f);
        }
        if (m207_goalCntTbl[0] == 203) {
            Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 0, 30, 2);
        }
        if (m207_goalCntTbl[0] < 200) {
            m207_soloGoalX += m207_soloGoalVelX;
            m207_soloGoalY += m207_soloGoalVelY;
            m207_soloGoalVelY -= 0.8125;
            if (m207_soloGoalY <= -20.0) {
                m207_soloGoalY = -20.0f;
                m207_goalCntTbl[0] = 200;
                Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[6]].motId, 10, 4, 0);
            }
        } else if (m207_goalCntTbl[0] >= 215) {
            if (m207_winner == 0) {
                m207_soloGoalRot = SETTLE_ANGLE(m207_soloGoalRot);
            } else if (m207_goalCntTbl[0] >= 215) {
                if (m207_phase == 4 && ((m207_phaseTimer > 30 && m207_phaseTimer < 120 && m207_goalCntTbl[0] == 215) || (m207_phaseTimer == 30 && m207_phaseTimer < 120 && m207_goalCntTbl[0] >= 215))) {
                    m207_goalCntTbl[0] = 300;
                    Hu3DMotionModelSet(obj->model[0], obj->motion[4]);
                    Hu3DMotionAttrSet(obj->model[0], 3, 0);
                }
                if (m207_goalCntTbl[0] >= 300) {
                    m207_soloGoalRot = SETTLE_ANGLE(m207_soloGoalRot);
                }
            }
        }
        omSetTra(obj, m207_soloGoalX, m207_soloGoalY, 0.0f);
        omSetRot(obj, 0.0f, m207_soloGoalRot, 0.0f);
    } else {
        stickX = (mode == 1 && player->cpuDifficulty == -1) ? HuPadStkX[player->pad] : 0.0f;
        stickY = (mode == 1 && player->cpuDifficulty == -1) ? HuPadStkY[player->pad] : 0.0f;
        if (m207_goalCntTbl[0] != 0) {
            stickX = 0.0f;
            stickY = (m207_posYTbl[0] < -135.0f) ? 60.0f : 0.0f;
        } else {
            if (mode == 1 && player->cpuDifficulty != -1) {
                f32 targetSpeeds[4] = { 35.0f, 39.0f, 42.0f, 46.0f };
                f32 laneDist[3] = { m207_soloComLaneDist, m207_soloComLaneDist, m207_soloComLaneDist };
                float best = 0.0f;

                i = targetSpeeds[player->cpuDifficulty];
                stickX = (m207_speedTbl[0] < i - 1)   ? 50.0f
                         : (i + 1 < m207_speedTbl[0]) ? -50.0f
                                                                    : (m207_speedTbl[0] - i) * -50.0f;
                stickX = (stickX < 0.0f) ? 0.0f : stickX;
                for (i = 0; i < visCount; i++) {
                    lane = (s32)hurdleLane[visIdx[i]] + 1;
                    if (m207_hurdleHitTbl[visIdx[i]] == 0 && obj->trans.x < visX[i] + 12.5) {
                        laneDist[lane] = MIN(visX[i] + 100.0f - obj->trans.x, laneDist[lane]);
                    }
                }
                for (j = 0; j < 2; j++) {
                    f32 range[4] = { 100.0f, 115.0f, 130.0f, 150.0f };
                    f32 dx;
                    f32 move;

                    lane = (m207_shotYTbl[j] < -12.5) ? 0 : (m207_shotYTbl[j] < 12.5) ? 1
                                                                                                                  : 2;
                    dx = m207_shotXTbl[j] - obj->trans.x;
                    move = dx / ((m207_speedTbl[0] + m207_shotSpeedTbl[j]) * SPEED_SCALE);
                    move = move * -m207_shotSpeedTbl[j] * SPEED_SCALE;
                    // No braces: keeps range[] alive in this scope, which the original stack layout needs.
                    // NOLINTBEGIN(readability-braces-around-statements)
                    if (move < 0.0f && obj->trans.x < move + m207_shotXTbl[j] + 12.5 && dx < range[player->cpuDifficulty])
                        laneDist[lane] = MIN(move + m207_shotXTbl[j] + 100.0f - obj->trans.x, laneDist[lane]);
                    // NOLINTEND(readability-braces-around-statements)
                }
                lane = 0;
                for (i = 0; i < 3; i++) {
                    if (best < laneDist[i] - ABS_DIFF(m207_soloComLane, i)) {
                        best = laneDist[i] - ABS_DIFF(m207_soloComLane, i);
                        lane = i;
                    }
                }
                if (laneDist[0] != m207_soloComLaneDist || laneDist[1] != m207_soloComLaneDist || laneDist[2] != m207_soloComLaneDist) {
                    f32 laneMemory[4] = { 185.0f, 200.0f, 215.0f, 230.0f };
                    f32 laneTolerance[4] = { 30.0f, 37.0f, 44.0f, 50.0f };

                    if (m207_soloComLane != lane) {
                        m207_soloComLaneDist = laneMemory[player->cpuDifficulty];
                    }
                    m207_soloComLane = lane;
                    i = laneTolerance[player->cpuDifficulty];
                    if (((m207_soloComLane - 1) * 200.0 - i) * 0.125 > obj->trans.y + 15.625) {
                        stickY = i;
                    } else if (((m207_soloComLane - 1) * 200.0 + i) * 0.125 < obj->trans.y + 15.625) {
                        stickY = -i;
                    }
                }
            }
            stickX = (m207_motTimerTbl[0] != 0) ? -50.0f : (stickX < -50.0f) ? -50.0f
                                                                  : (stickX > 50.0f)    ? 50.0f
                                                                                        : stickX;
            stickY = (m207_motTimerTbl[0] != 0) ? 0.0f : (stickY < -50.0f) ? -50.0f
                                                                : (stickY > 50.0f)    ? 50.0f
                                                                                      : stickY;
            stickY = !(m207_posYTbl[0] >= 46.0f && stickY > 0.0f) ? (!(m207_posYTbl[0] <= -330.0f && stickY < 0.0f) ? stickY : 0.0f) : 0.0f;
        }
        if (m207_soloStunTimer < 31) {
            m207_speedTbl[0] += stickX / 50.0 * 5.0 / 30.0;
            m207_speedTbl[0] = (mode == 2)                                            ? 40.0f
                                             : (m207_speedTbl[0] < 35.0 - 5.0 / 30.0) ? m207_speedTbl[0] + 5.0 / 30.0
                                             : (m207_speedTbl[0] < 35.0f)             ? 35.0f
                                             : (m207_speedTbl[0] > 46.0f)             ? 46.0f
                                                                                                    : m207_speedTbl[0];
        }
        m207_distTbl[0] += m207_speedTbl[0] * SPEED_SCALE;
        if (m207_distTbl[0] > 1871.875 && m207_goalCntTbl[0] == 0) {
            m207_goalCntTbl[0] = 1;
            if (m207_winner == 5) {
                m207_winner = 0;
            }
            m207_goalFrameTbl[0] = m207_frameCnt;
        }
        m207_distTbl[0] -= m207_soloSpeedOfs;
        CenterM[0].x = 2.0 * m207_distTbl[0] + 56.25;
        m207_soloSpeedOfs = (m207_speedTbl[0] + -40.0f) * 3.0f;
        m207_distTbl[0] += m207_soloSpeedOfs;
        i = (m207_goalCntTbl[0] != 0) ? 6 : 3;
        m207_velYTbl[0] = (m207_velYTbl[0] < stickY - i)   ? m207_velYTbl[0] + i
                                         : (stickY + i < m207_velYTbl[0]) ? m207_velYTbl[0] - i
                                                                                         : stickY;
        m207_posYTbl[0] += m207_velYTbl[0] / 5.0;
        m207_posYTbl[0] = (m207_posYTbl[0] > 30.0f)     ? 30.0f
                                         : (m207_posYTbl[0] < -330.0f) ? -330.0f
                                                                                      : m207_posYTbl[0];
        omSetTra(obj, 2.0 * m207_distTbl[0], m207_posYTbl[0] * 0.125, 0.0f);
        omSetRot(obj, -90.0f, 90.0 - m207_velYTbl[0] / 8.0, m207_velYTbl[0] / 4.0 + -90.0);
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    }
    if (m207_goalCntTbl[0] < 100) {
        for (i = 0; i < visCount + 2; i++) {
            x = (i < visCount) ? visX[i] : m207_shotXTbl[i - visCount];
            y = (i < visCount) ? visY[i] : m207_shotYTbl[i - visCount];
            j = i - visCount;
            if ((i < visCount || !(m207_shotXTbl[j] <= -1000.0f)) && mode == 1 && m207_motTimerTbl[0] == 0 && (i >= visCount || m207_hurdleHitTbl[visIdx[i]] == 0) && m207_soloStunTimer == 0) {
                f32 dx = x - obj->trans.x;

                if (dx < 15.625 && dx > -15.625) {
                    f32 ax = ABS(dx) * 0.75;
                    f64 dy = ABS(y - (obj->trans.y + 15.625));
                    f32 ay;

                    if (i >= visCount) {
                        dy *= 0.875;
                    }
                    ay = dy;
                    if (HuSqrtf(ax * ax + ay * ay) < 11.25) {
                        s16 fx;

                        if (i < visCount) {
                            m207_hurdleHitTbl[visIdx[i]] = 1;
                        }
                        m207_soloStunSpeed = m207_speedTbl[0];
                        m207_motTimerTbl[0] = 60;
                        m207_soloStunTimer = 60;
                        m207_soloShotHitF = (i >= visCount);
                        Hu3DModelPosSet(m207_stageObj->model[5], x * 0.5 + obj->trans.x * 0.5, y * 0.5 + obj->trans.y * 0.5 + 5.0, 0.0f);
                        Hu3DModelRotSet(m207_stageObj->model[5], 0.0f, 0.0f, rand8() / 256.0 * 360.0);
                        Hu3DModelScaleSet(m207_stageObj->model[5], 0.1875f, 0.1875f, 0.1875f);
                        Hu3DModelAttrSet(m207_stageObj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        Hu3DModelTPLvlSet(m207_stageObj->model[5], 0xFF);
                        obj->trans.y += -0.75;
                        omVibrate(m207_groupPlayerTbl[0]->playerNo, 20, 0, 20);
                        m207_ChrSePlay(0x286, m207_groupPlayerTbl[0]->playerNo);
                        m207_SePlay(m207_groupPlayerTbl[0]->chr + 0x95, m207_groupPlayerTbl[0]->playerNo);
                        if (m207_soloShotHitF == 0) {
                            fx = HuAudFXPlay(0x333);
                            if (fx != -1) {
                                HuAudFXPanning(fx, (obj->trans.x - CenterM[0].x) / 90.0 * 32.0 + 64.0);
                            }
                        }
                    }
                }
            }
        }
        if (m207_motTimerTbl[0] == 58 || m207_motTimerTbl[0] == 56) {
            i = (m207_motTimerTbl[0] == 58);
            Hu3DModelTPLvlSet(m207_stageObj->model[5], i ? 0x80 : 0x30);
            Hu3DModelScaleSet(m207_stageObj->model[5], i ? 0.28125f : 0.34375f, i ? 0.28125f : 0.34375f,
                              i ? 0.28125f : 0.34375f);
            obj->trans.x += i ? 0.5 : -0.75;
        } else if (m207_motTimerTbl[0] == 54) {
            Hu3DModelAttrSet(m207_stageObj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            obj->trans.x += 0.25;
        }
        if (m207_motTimerTbl[0] != 0) {
            Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        }
        m207_motTimerTbl[0] = MAX((s16)(m207_motTimerTbl[0] - 2), 0);
        Hu3DMotionTimeSet(obj->model[0], (m207_motTimerTbl[0] != 0) ? (f32)(60 - m207_motTimerTbl[0]) : 0.0f);
        if (m207_soloStunTimer != 0) {
            // Saturating decrement (same form as the unguarded timers); reuses the tested value.
            m207_soloStunTimer -= (m207_soloStunTimer != 0) ? 1 : 0;
            if (m207_soloStunTimer >= 30) {
                f32 t = sindf((60 - m207_soloStunTimer) / 30.0 * 90.0);

                m207_speedTbl[0] = (1.0f - t) * m207_soloStunSpeed + t * 35.0f;
                m207_distTbl[0] -= (1.0f - sindf((60 - m207_soloStunTimer) / 30.0 * 90.0)) / 2.0f * (m207_soloShotHitF ? 4.0 : 2.5);
            }
            if (m207_soloStunTimer < 31) {
                Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, (m207_soloStunTimer % 2) * HU3D_ATTR_DISPOFF);
            }
        } else {
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        for (i = 0; i < 18; i++) {
            m207_hurdleHitTbl[i] += (m207_hurdleHitTbl[i] != 0 || m207_phase >= 3) && m207_hurdleHitTbl[i] < 0xFFFF;
        }
    }
    m207_progressTbl[0] = (m207_distTbl[0] < 0.0f) ? 0.0f : m207_distTbl[0] / 1868.75f;
    m207_progressTbl[0] = (m207_progressTbl[0] >= 1.0f) ? 1.0f : m207_progressTbl[0];

    // Group 1: rowing
    obj = m207_playerObjTbl[1];
    player = m207_groupPlayerTbl[1];
    if (m207_relayLegNo == 0 || (m207_relayLegNo == 1 && m207_distTbl[2] < 875.0)) {
        m207_comWaitTbl[0] -= m207_relayLegNo == 0 && m207_comWaitTbl[0] != 0;
        if (m207_relayLegNo == 0 && mode == 1) {
            u16 btn = HuPadBtnDown[player->pad];

            if ((m207_strokeTbl[1] ? (btn & (B_BUTTON | Z_TRIG)) : (btn & A_BUTTON)) || (player->cpuDifficulty != -1 && m207_comWaitTbl[0] == 0)) {
                m207_strokeTbl[1] = 1 - m207_strokeTbl[1];
                m207_motTimerTbl[1] = (m207_motTimerTbl[1] != 0) ? m207_motTimerTbl[1] : 60;
                m207_speedTbl[1] += 40.0 / 9.0;
                if (player->cpuDifficulty != -1) {
                    m207_comWaitTbl[0] = cpuParams[0][0][player->cpuDifficulty] + rand8() % cpuParams[1][0][player->cpuDifficulty];
                }
            }
        }
        if (mode == 2 && m207_frameCnt % 24 == 15) {
            m207_motTimerTbl[1] = (m207_motTimerTbl[1] != 0) ? m207_motTimerTbl[1] : 60;
        }
        m207_distTbl[1] += m207_speedTbl[1] * SPEED_SCALE;
        m207_speedTbl[1] -= m207_speedTbl[1] / 6.0 / 5.0 * (29.0 / 30.0);
        m207_speedTbl[1] = (mode == 2)                                ? 40.0f
                                         : (m207_speedTbl[1] > 43.5)  ? 43.5f
                                         : (m207_speedTbl[1] < -43.5) ? -43.5f
                                                                                    : m207_speedTbl[1];
        if (m207_distTbl[1] > 626.25) {
            m207_distTbl[1] = 626.25f;
            m207_speedTbl[1] *= (m207_speedTbl[1] > 0.0f) ? -0.25 : 1.0;
            if (m207_relayLegNo == 0) {
                m207_relayLegNo = 1;
                m207_flagCntTbl[0] = 1;
                m207_cameraHandoffCnt = 1;
                m207_cameraStep = (m207_cameraStep < 0.5) ? 0.5f : m207_cameraStep;
                m207_goalFrameTbl[1] = m207_frameCnt;
                omVibrate(m207_groupPlayerTbl[2]->playerNo, 2, 3, 10);
            }
        }
        if (m207_relayLegNo == 0) {
            f32 camX = 2.0 * m207_distTbl[1] + 56.25;

            m207_cameraStep = prevCenter[1] - m207_cameraPrevXTbl[1];
            CenterM[1].x = camX;
        }
        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        omSetTra(obj, 2.0 * m207_distTbl[1], m207_waveY * 100.0f * 0.125 + -25.0, 0.0f);
        omSetRot(obj, 0.0f, 90.0f, 0.0f);
        Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
        {
            s32 prev = m207_motTimerTbl[1];

            i = prev >= 58;
            m207_motTimerTbl[1] = prev - ((m207_speedTbl[1] < 0.0f) ? 1.0 : m207_speedTbl[1] / 15.0);
            m207_motTimerTbl[1] = MAX(m207_motTimerTbl[1], 0);
            if (m207_motTimerTbl[1] < 58 && i) {
                HuAudFXPlay(0x32F);
            }
        }
        Hu3DMotionTimeSet(obj->model[0], (m207_motTimerTbl[1] != 0) ? (f32)(60 - m207_motTimerTbl[1]) : 0.0f);
        if (m207_relayLegNo == 0 && mode == 1) {
            m207_promptXTbl[m207_strokeTbl[1]] = obj->trans.x;
        }
    } else {
        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    if (m207_splashTimerTbl[0] == 1) {
        Hu3DModelAttrSet(m207_stageObj->model[7], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    m207_splashTimerTbl[0] -= (m207_splashTimerTbl[0] != 0) ? 1 : 0;
    m207_progressTbl[1] = (m207_relayLegNo != 0)        ? 1.0f
                                     : (m207_distTbl[1] < 0.0f) ? 0.0f
                                                                               : m207_distTbl[1] / 626.5625f;
    m207_progressTbl[1] = (m207_progressTbl[1] >= 1.0f) ? 1.0f : m207_progressTbl[1];

    // Group 2: swimming
    obj = m207_playerObjTbl[2];
    player = m207_groupPlayerTbl[2];
    if (m207_relayLegNo == 1 || (m207_relayLegNo == 0 && m207_distTbl[1] > 375.0) || (m207_relayLegNo == 2 && m207_distTbl[3] < 1500.0)) {
        f32 step;

        m207_comWaitTbl[1] -= m207_relayLegNo == 1 && m207_comWaitTbl[1] != 0;
        if (m207_relayLegNo == 1 && mode == 1 && (((HuPadBtnDown[player->pad] & ((m207_strokeTbl[2] / 2) ? B_BUTTON : A_BUTTON)) && ((m207_strokeTbl[2] & 1) ? -1 : 1) * HuPadStkY[player->pad] > 32) || (player->cpuDifficulty != -1 && m207_comWaitTbl[1] == 0))) {
            m207_swimMotPrev = m207_swimMotCur;
            m207_swimMotCur = m207_strokeTbl[2];
            m207_swimMotBlend = 0;
            m207_swimMotBlendLen = 2;
            Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[m207_strokeTbl[2] + 7]].motId,
                               (m207_strokeTbl[2] == 3) ? 7 : 5, 4, 0);
            m207_strokeTbl[2]++;
            m207_strokeTbl[2] %= 4;
            if (m207_strokeTbl[2] == 0) {
                m207_motTimerTbl[2] = 50;
                m207_speedTbl[2] = 53.0f;
                if (m207_relayLegNo == 1) {
                    Hu3DModelAttrSet(m207_stageObj->model[8], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DModelScaleSet(m207_stageObj->model[8], 0.234375f, 0.234375f, 0.234375f);
                    Hu3DMotionTimeSet(m207_stageObj->model[8], 0.0f);
                    Hu3DMotionSpeedSet(m207_stageObj->model[8], 1.5f);
                    Hu3DModelAttrSet(m207_stageObj->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DModelScaleSet(m207_stageObj->model[9], 0.234375f, 0.234375f, 0.234375f);
                    Hu3DMotionTimeSet(m207_stageObj->model[9], 0.0f);
                    Hu3DMotionSpeedSet(m207_stageObj->model[9], 1.5f);
                    m207_splashTimerTbl[1] = 10;
                    HuAudFXPlay(0x330);
                }
            }
            Hu3DModelPosSet(m207_stageObj->model[8], obj->trans.x - 31.25, obj->trans.y - 3.90625, obj->trans.z);
            Hu3DModelPosSet(m207_stageObj->model[9], obj->trans.x + 23.4375, obj->trans.y - 1.953125, obj->trans.z);
            if (player->cpuDifficulty != -1) {
                m207_comWaitTbl[1] = cpuParams[0][1][player->cpuDifficulty] + rand8() % cpuParams[1][1][player->cpuDifficulty];
            }
        } else if (m207_relayLegNo == 1 && mode == 1 && m207_swimMotCur != 4 && player->cpuDifficulty == -1 && (HuPadBtnDown[player->pad] & (A_BUTTON | B_BUTTON))) {
            m207_swimMotPrev = m207_swimMotCur;
            m207_swimMotCur = 4;
            m207_swimMotBlend = 0;
            m207_swimMotBlendLen = 3;
            Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[11]].motId, 0, 6, 0);
            omVibrate(m207_groupPlayerTbl[2]->playerNo, 10, 0, 10);
        }
        // About 125 / 60, but the original constant is one ulp below the correctly rounded quotient.
        step = m207_speedTbl[2] / 60.0 * 2.083333333333333;
        m207_distTbl[2] += step;
        m207_speedTbl[2] = (m207_speedTbl[2] > 1.0f)    ? m207_speedTbl[2] - 1.0f
                                         : (m207_speedTbl[2] < -1.0f) ? m207_speedTbl[2] + 1.0f
                                                                                    : 0.0f;
        if (m207_distTbl[2] > 1245.3125) {
            m207_distTbl[2] = 1245.3125f;
            m207_speedTbl[2] *= (m207_speedTbl[2] > 0.0f) ? -0.2 : 1.0;
            if (m207_relayLegNo < 2) {
                m207_relayLegNo = 2;
                m207_flagCntTbl[1] = 1;
                m207_cameraHandoffCnt = 1;
                m207_cameraStep = (m207_cameraStep < 0.5) ? 0.5f : m207_cameraStep;
                if (m207_phase == 2) {
                    m207_seNoTbl[2] = HuAudFXPlay(0x331);
                    HuAudFXVolSet(m207_seNoTbl[2], 127);
                }
                m207_goalFrameTbl[2] = m207_frameCnt;
                omVibrate(m207_groupPlayerTbl[3]->playerNo, 2, 3, 10);
            }
        }
        if (m207_relayLegNo == 1) {
            f32 camX = 2.0 * m207_distTbl[2] + 56.25;

            m207_cameraHandoffCnt = (m207_cameraHandoffCnt != 0 && CenterM[1].x + m207_cameraStep <= camX) ? m207_cameraHandoffCnt + 1 : 0;
            if (m207_cameraHandoffCnt != 0) {
                m207_cameraStep = (m207_cameraStep < 2.0 * step) ? 2.0 * step : m207_cameraStep;
                CenterM[1].x += m207_cameraStep;
            } else {
                m207_cameraStep = prevCenter[1] - m207_cameraPrevXTbl[1];
                CenterM[1].x = camX;
            }
        }
        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        m207_swimMotBlend = (m207_swimMotPrev == m207_swimMotCur) ? 0 : m207_swimMotBlend + 1;
        if (m207_swimMotBlend > m207_swimMotBlendLen) {
            u8 prevAnim = m207_swimMotPrev;

            m207_swimMotPrev = m207_swimMotCur;
            m207_swimMotBlend = 0;
            if (m207_swimMotCur == 4) {
                m207_swimMotCur = prevAnim;
                m207_swimMotBlendLen = 10;
                Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[m207_swimMotCur + 7]].motId, 60, 20, 0);
            } else {
                m207_swimMotBlendLen = 0;
            }
        }
        omSetTra(obj, 2.0 * m207_distTbl[2], m207_waveY * 100.0f * 0.125 + -25.0 + 25.0, 0.0f);
        omSetRot(obj, 0.0f, 90.0f, 0.0f);
        Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
        obj->trans.x -= ROWER_OFFSET() * 0.125 * 1.25;
        obj->trans.y -= ROWER_OFFSET() * 0.125 * 1.25;
        obj->trans.y += 1.875;
        Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[2], obj->rot.x, obj->rot.y, obj->rot.z);
        if (m207_motTimerTbl[2] > 0) {
            if (m207_motTimerTbl[2] == 2) {
                m207_motTimerTbl[2] = 0;
                Hu3DMotionModelSet(obj->model[0], obj->motion[1]);
                Hu3DMotionTimeSet(obj->model[2], 0.0f);
            } else {
                if (m207_motTimerTbl[2] == 50) {
                    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[2]].motId, 0, 6, 2);
                }
                m207_motTimerTbl[2] = MAX((s16)(m207_motTimerTbl[2] - 2), 0);
                Hu3DMotionTimeSet(obj->model[0], (m207_motTimerTbl[2] != 0) ? (f32)(50 - m207_motTimerTbl[2]) : 0.0f);
                Hu3DMotionTimeSet(obj->model[2], (m207_motTimerTbl[2] == 0)   ? 0.0f
                                                 : (m207_motTimerTbl[2] < 25) ? (f32)m207_motTimerTbl[2]
                                                                                         : (f32)(50 - m207_motTimerTbl[2]));
            }
        }
        Hu3DMotionAttrSet(obj->model[0], 3, 2);
        Hu3DMotionAttrSet(obj->model[2], 3, 1);
        if (m207_relayLegNo == 1 && mode == 1) {
            m207_promptXTbl[m207_strokeTbl[2] + 2] = Hu3DData[obj->model[1]].pos.x;
        }
        if (m207_swimMotPrev == 4 && (m207_swimMotBlend == 0 || m207_swimMotBlend == 4)) {
            for (i = (m207_swimMotBlend != 0) ? 9 : 0; i < ((m207_swimMotBlend == 0) ? 9 : 18); i++) {
                Hu3DModelAttrSet(m207_stageObj->model[i + 17], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                m207_dropXTbl[i] = Hu3DData[obj->model[1]].pos.x + ((m207_swimMotBlend == 0) ? -31.25 : 27.5);
                m207_dropYTbl[i] = m207_waveY * 100.0f * 0.125 + -25.0;
                m207_dropVelXTbl[i] = (rand8() / 256.0 * 30.0 - 10.0) * 0.125 * ((m207_swimMotBlend != 0) ? 1 : -1);
                m207_dropVelYTbl[i] = (rand8() / 256.0 * 30.0 + 20.0) * 0.125;
                Hu3DModelPosSet(m207_stageObj->model[i + 17], m207_dropXTbl[i], m207_dropYTbl[i], 0.0f);
            }
        }
    } else {
        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    if (m207_splashTimerTbl[1] == 1) {
        Hu3DModelAttrSet(m207_stageObj->model[8], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(m207_stageObj->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    m207_splashTimerTbl[1] -= (m207_splashTimerTbl[1] != 0) ? 1 : 0;
    m207_progressTbl[2] = (m207_relayLegNo >= 2)        ? 1.0f
                                     : (m207_distTbl[2] < 0.0f) ? 0.0f
                                                                               : (m207_distTbl[2] - 650.0) / 601.5625;
    m207_progressTbl[2] = (m207_progressTbl[2] >= 1.0f)  ? 1.0f
                                     : (m207_progressTbl[2] < 0.0f) ? 0.0f
                                                                               : m207_progressTbl[2];
    for (i = 0; i < 18; i++) {
        if (m207_dropYTbl[i] == -1000.0f) {
            continue;
        }
        m207_dropXTbl[i] += m207_dropVelXTbl[i];
        m207_dropYTbl[i] += m207_dropVelYTbl[i];
        m207_dropVelYTbl[i] -= 0.625;
        if (m207_dropVelYTbl[i] < 0.0f && m207_dropYTbl[i] < m207_waveY * 100.0f * 0.125 + -25.0) {
            Hu3DModelAttrSet(m207_stageObj->model[i + 17], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            m207_dropYTbl[i] = -1000.0f;
        } else {
            Hu3DModelPosSet(m207_stageObj->model[i + 17], m207_dropXTbl[i], m207_dropYTbl[i], 0.0f);
        }
    }

    // Group 3: bicycle
    obj = m207_playerObjTbl[3];
    player = m207_groupPlayerTbl[3];
    if (m207_relayLegNo == 2 || m207_relayLegNo == 3 || (m207_relayLegNo == 1 && m207_distTbl[2] > 1000.0)) {
        f32 step;

        m207_comWaitTbl[2] -= m207_relayLegNo == 2 && m207_comWaitTbl[2] != 0;
        if (m207_relayLegNo >= 2 && mode == 1) {
            if ((HuPadBtnDown[player->pad] & A_BUTTON) || (player->cpuDifficulty != -1 && m207_comWaitTbl[2] == 0)) {
                m207_speedTbl[3] += 5.0f;
                if (player->cpuDifficulty != -1) {
                    m207_comWaitTbl[2] = cpuParams[0][2][player->cpuDifficulty] + rand8() % cpuParams[1][2][player->cpuDifficulty];
                }
            }
        }
        step = m207_speedTbl[3] * SPEED_SCALE;
        m207_distTbl[3] = step + m207_distTbl[3];
        m207_speedTbl[3] -= m207_speedTbl[3] / 6.0 / 5.0;
        m207_speedTbl[3] = (m207_speedTbl[3] > 50.0f)    ? 50.0f
                                         : (m207_speedTbl[3] < -50.0f) ? -50.0f
                                                                                     : m207_speedTbl[3];
        if (m207_seNoTbl[2] != -1) {
            HuAudFXPitchSet((s16)m207_seNoTbl[2], (s16)(m207_speedTbl[3] / 50.0 * 400.0 - 400.0));
        }
        if (m207_distTbl[3] > 1865.625 && m207_goalCntTbl[1] == 0) {
            if (m207_winner == 5 || (m207_winner == 0 && m207_goalCntTbl[0] == 1 && m207_distTbl[0] < m207_distTbl[3])) {
                m207_winner = 1;
                m207_goalCntTbl[1] = 1;
            }
            if (m207_goalFrameTbl[3] == 0) {
                m207_goalFrameTbl[3] = m207_frameCnt;
            }
            m207_distTbl[3] = 1865.625f;
            m207_speedTbl[3] *= (m207_speedTbl[3] > 0.0f) ? -0.125 : 1.0;
        }
        if (m207_relayLegNo == 2) {
            f32 camX = 2.0 * m207_distTbl[3] + 56.25;

            m207_cameraHandoffCnt = (m207_cameraHandoffCnt != 0 && CenterM[1].x + m207_cameraStep <= camX) ? m207_cameraHandoffCnt + 1 : 0;
            if (m207_cameraHandoffCnt != 0) {
                m207_cameraStep = (m207_cameraStep < 2.0 * step) ? 2.0 * step : m207_cameraStep;
                CenterM[1].x += m207_cameraStep;
            } else {
                m207_cameraStep = prevCenter[1] - m207_cameraPrevXTbl[1];
                CenterM[1].x = camX;
            }
        }
        m207_strokeTbl[3] = m207_strokeTbl[3] * 0.875 + m207_speedTbl[3] / 50.0 * 10.0 * 1000.0 * 0.125;
        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        omSetTra(obj, 2.0 * m207_distTbl[3], m207_waveY * 100.0f * 0.125 + -25.0, 0.0f);
        omSetRot(obj, 0.0f, 90.0f, m207_strokeTbl[3] / 1000.0);
        Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
        m207_motTimerTbl[3] += ABS(m207_speedTbl[3]) / 50.0 * 350.0;
        m207_motTimerTbl[3] %= 3000;
        m207_bikeBounce = (m207_bikeBounce - 4.0 / 47.5 < PEDAL_POWER(m207_speedTbl[3]) / 47.5)
                                          ? PEDAL_POWER(m207_speedTbl[3]) / 47.5
                                          : m207_bikeBounce - 4.0 / 47.5;
        m207_bikeBounce = (m207_bikeBounce < 0.0f) ? 0.0f : m207_bikeBounce;
        Hu3DMotionTimeSet(obj->model[1], m207_motTimerTbl[3] / 100.0);
        Hu3DModelAttrSet(m207_stageObj->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelPosSet(m207_stageObj->model[6], obj->trans.x - (m207_bikeBounce * 40.0f + 200.0f) * 1.25 * 0.125,
                        obj->trans.y + m207_bikeBounce * 100.0f * 1.25 * 0.125, obj->trans.z);
        Hu3DModelScaleSet(m207_stageObj->model[6], m207_bikeBounce * 1.25 * 0.125 * 1.3,
                          m207_bikeBounce * 1.25 * 0.125, m207_bikeBounce * 1.25 * 0.125);
        if (m207_goalCntTbl[1] != 0) {
            if (m207_goalCntTbl[1] == 15) {
                m207_bikeGoalY = obj->trans.y + 4.375;
                m207_bikeGoalVelY = 7.5f;
                for (i = 0; i < 85; i++) {
                    m207_bikeGoalY += m207_bikeGoalVelY;
                    m207_bikeGoalVelY -= 0.8125;
                    if (m207_bikeGoalVelY < 0.0f && m207_bikeGoalY <= -13.75) {
                        break;
                    }
                }
                m207_bikeGoalX = obj->trans.x + 4.375;
                m207_bikeGoalY = obj->trans.y + 4.375;
                m207_bikeGoalRot = 90.0f;
                m207_bikeGoalVelX = (3768.75 - obj->trans.x) / (f32)i;
                m207_bikeGoalVelY = 7.5f;
                Hu3DMotionModelSet(obj->model[0], obj->motion[5]);
                Hu3DMotionAttrSet(obj->model[0], 3, 0);
                m207_speedTbl[3] -= 2.0;
            }
            if (m207_goalCntTbl[1] >= 16 && m207_goalCntTbl[1] < 100) {
                m207_bikeGoalX += m207_bikeGoalVelX;
                m207_bikeGoalY += m207_bikeGoalVelY;
                m207_bikeGoalVelY -= 0.8125;
                if ((m207_bikeGoalVelY < 0.0f && m207_bikeGoalY <= -13.75) || m207_bikeGoalY < -1875.0) {
                    m207_bikeGoalY = -13.75f;
                    m207_goalCntTbl[1] = 100;
                } else if (m207_bikeGoalVelY < 0.0f && m207_bikeGoalY + m207_bikeGoalVelY <= -13.75) {
                    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[6]].motId, 10, 4, 0);
                }
            }
            if (m207_goalCntTbl[1] == 102) {
                Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 0, 30, 2);
            }
            if (m207_goalCntTbl[1] >= 115 && m207_winner == 1) {
                m207_bikeGoalRot = SETTLE_ANGLE(m207_bikeGoalRot);
            }
            if (m207_goalCntTbl[1] >= 16) {
                omSetTra(obj, m207_bikeGoalX, m207_bikeGoalY, 0.0f);
                omSetRot(obj, 0.0f, m207_bikeGoalRot, 0.0f);
            }
            m207_goalCntTbl[1]++;
        } else {
            Hu3DMotionAttrSet(obj->model[0], 3, 2);
        }
        if (m207_relayLegNo >= 2 && mode == 1) {
            m207_promptXTbl[6] = obj->trans.x;
        }
    } else {
        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    m207_progressTbl[3] = (m207_relayLegNo >= 3)        ? 1.0f
                                     : (m207_distTbl[3] < 0.0f) ? 0.0f
                                                                               : (m207_distTbl[3] - 1275.0) / 593.75;
    m207_progressTbl[3] = (m207_progressTbl[3] >= 1.0f || m207_goalCntTbl[1] != 0) ? 1.0f
                                     : (m207_progressTbl[3] < 0.0f)                                       ? 0.0f
                                                                                                                     : m207_progressTbl[3];

    // Camera and finish line flags
    CenterM[0].x = (CenterM[0].x > 3750.0) ? 3750.0f : CenterM[0].x;
    CenterM[1].x = (CenterM[1].x > 3750.0) ? 3750.0f : CenterM[1].x;
    i = (CenterM[1].x < 1875.0) ? 0 : 1;
    omSetTra(m207_stageObj, (2.0 * ((i + 1) * 5000) + 950.0) * 0.125,
             ((m207_flagCntTbl[i] < 10)
                  ? 0.125 * (m207_flagCntTbl[i] * m207_flagCntTbl[i] / 100.0 * 100.0)
                  : ((m207_flagCntTbl[i] < 30) ? (m207_flagCntTbl[i] - 10) * 36 + 100
                     : ((m207_flagCntTbl[i] - 30) * (m207_flagCntTbl[i] - 30) * 2 < 460)
                         ? 460 - (m207_flagCntTbl[i] - 30) * (m207_flagCntTbl[i] - 30) * 2
                         : 0) *
                        0.125) +
                 -46.875,
             0.0f);
    Hu3DModelPosSet(m207_stageObj->model[1], (2.0 * ((i + 1) * 5000) + 150.0) * 0.125, -25.0f, 0.0f);
    m207_flagCntTbl[0] += (m207_flagCntTbl[0] != 0 && m207_flagCntTbl[0] < 24) || (m207_flagCntTbl[0] >= 30 && m207_flagCntTbl[0] < 45);
    if (m207_flagCntTbl[1] == 44) {
        HuAudFXPlay(0x334);
    }
    m207_flagCntTbl[1] += (m207_flagCntTbl[1] != 0 && m207_flagCntTbl[1] < 20) || (m207_flagCntTbl[1] >= 30 && m207_flagCntTbl[1] < 45);
    if (m207_flagCntTbl[1] == 20 && CenterM[1].x > 2721.875) {
        m207_flagCntTbl[1] = 30;
    }
    if (m207_frameCnt < 123) {
        CenterM[0].x = CenterM[0].x * 0.75 + 14.5718165;
        CenterM[1].x = CenterM[1].x * 0.75 + 14.5718165;
    }
    m207_distTbl[0] = (m207_distTbl[0] < -2000.0f) ? -2000.0f : m207_distTbl[0];
    m207_scrollTbl[0] = CenterM[0].x / 0.125 / 100.0 * 16.0;
    if (CenterM[0].x < 3750.0) {
        m207_skyScrollStep = (m207_speedTbl[0] - 35.0f) / 10.0 * 0.25 - 0.5;
    }
    m207_skyScrollStep = 0.0f;
    m207_skyScroll += m207_skyScrollStep;
    m207_skyScroll -= (m207_skyScroll >= 320.0f) ? 320.0f : 0.0f;
    m207_skyScroll += (m207_skyScroll < 0.0f) ? 320.0f : 0.0f;
    m207_scrollTbl[1] = CenterM[1].x / 0.125 / 100.0 * 16.0;
    for (i = 0; i < 7; i++) {
        if (m207_promptXTbl[i] != 0.0f) {
            m207_promptXTbl[i] = m207_ScreenXGet(m207_promptXTbl[i]);
        }
    }
    m207_frameCnt++;
    m207_cameraPrevXTbl[0] = prevCenter[0];
    m207_cameraPrevXTbl[1] = prevCenter[1];
}

s16 m207_SePlay(s16 arg0, s16 arg1) {
    if (HuAudSeEnableF == 0) {
        return 0;
    }
    if (arg0 == 0) {
        return 0;
    }
    return _HuAudPlayerFXPlay(arg0, 0);
}

s16 m207_ChrSePlay(s16 seId, s16 playerIdx) {
    if (HuAudSeEnableF == 0) {
        return 0;
    }
    if (seId == 0) {
        return 0;
    }
    return _HuAudPlayerFXPlay(seId + GwPlayer[playerIdx].chr + 1, 0);
}
