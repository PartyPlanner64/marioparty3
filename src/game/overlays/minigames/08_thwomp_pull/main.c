#include "common.h"
#include "game/overlays/minigame.h"

typedef struct ThwompPullPlayer {
    /* 0x00 */ s8 playerNo;
    /* 0x01 */ s8 group;
    /* 0x02 */ s8 pad;
    /* 0x03 */ s8 chr;
    /* 0x04 */ s8 cpuDifficulty; // -1 for human players
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0C */ s32 unk_0C;
} ThwompPullPlayer; // sizeof 0x10

extern Gfx *gMainGfxPos;

MinigameFlow m208_mgFlow = { 0 };
u32 m208_winAnimCnt = 0;

Gfx m208_backGfx[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 320, 240),
    gsSPEndDisplayList(),
};

/* Unreferenced. */
Gfx m208_backGfxB[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 320, 240),
    gsSPEndDisplayList(),
};

u8 m208_frameToggleF = 0;
u32 m208_frameCnt = 0;
f32 m208_distTbl[2] = { -20.0f, -20.0f };
u8 m208_hopTimerTbl[2] = { 0 };
u8 m208_missTimerTbl[2][3] = { 0 };
u16 m208_promptTimerTbl[2] = { 0 };
u8 m208_promptLockTbl[2] = { 0 };
u8 m208_promptNoTbl[2] = { 0 };
u8 m208_promptOrderTbl[2][3] = { { 0, 1, 2 }, { 0, 1, 2 } };
u8 m208_dustNoTbl[2] = { 0 };
f32 m208_dustZTbl[2][2] = { 0 };
u8 m208_dustTimerTbl[2][2] = { 0 };
f32 m208_rockXTbl[2][4] = { 0 };
f32 m208_rockYTbl[2][4] = { 0 };
f32 m208_rockZTbl[2][4] = { 0 };
f32 m208_rockVelXTbl[2][4] = { 0 };
f32 m208_rockVelYTbl[2][4] = { 0 };
f32 m208_rockVelZTbl[2][4] = { 0 };
u8 m208_rockStateTbl[2] = { 0 };
f32 m208_rockTimerTbl[2] = { 0 };
u8 m208_throwTimerTbl[2] = { 0 };
s8 m208_comWaitTbl[4] = { 0 };
u8 m208_comHitFTbl[4] = { 0 };
u8 m208_stunTimerTbl[4] = { 0 };
u8 m208_pullMotTimerTbl[4] = { 0 };
u16 m208_throwFrameTbl[2] = { 30, 30 };
u8 m208_landTimerTbl[2][3] = { 0 };
f32 m208_landZTbl[2][3] = { 0 };
u8 m208_rockBreakTimerTbl[2] = { 0 };
f32 m208_hopCurveTbl[21] = { 0 };

f32 m208_winJumpXTbl[3] BSS;
f32 m208_winJumpYTbl[3] BSS;
f32 m208_winJumpZTbl[3] BSS;
f32 m208_winJumpVelXTbl[3] BSS;
f32 m208_winJumpVelYTbl[3] BSS;
f32 m208_winJumpVelZTbl[3] BSS;
ThwompPullPlayer m208_playerTbl[4] BSS;
ThwompPullPlayer *m208_groupPlayerTbl[4] BSS; // players indexed by group
u8 m208_groupPlayerPad[8] BSS; /* Unreferenced. */
f32 m208_playerYTbl[4] BSS;
f32 m208_progressTbl[2] BSS;
HmfModelSet *m208_pullMotBake BSS;
omObjData *m208_stageObj BSS;
s16 m208_phase BSS;
f32 m208_shakeOfsTbl[2] BSS;
s32 m208_animCnt BSS;
f32 m208_playerZTbl[4] BSS;
s16 m208_sprAnimTbl[10] BSS; // sprite data ids
u8 m208_shakeTimerTbl[2] BSS;
s8 m208_winner BSS;
omObjData *m208_sideObjTbl[2] BSS;
u16 m208_exitF BSS;
u8 m208_exitPad[4] BSS; /* Unreferenced. */
f32 m208_playerXTbl[4] BSS;
f32 m208_winZoomRate BSS;
u8 m208_winZoomPad[4] BSS; /* Unreferenced. */
s16 m208_sprTbl[10] BSS; // sprite ids
s32 m208_phaseTimer BSS;
u8 m208_quitCnt BSS;
HmfModelSet *m208_throwMotBakeTbl[2] BSS;
u8 m208_playerGroupTbl[4] BSS; // group of each player

const s16 m208_fontMesTbl[] = {
    0x8260, 0x8261, 0x8262, 0x8263, 0x8264, 0x8265, 0x8266, 0x8267, 0x8268, 0x8269, 0x826A, 0x826B, 0x826C, 0x826D,
    0x826E, 0x826F, 0x8270, 0x8271, 0x8272, 0x8273, 0x8274, 0x8275, 0x8276, 0x8277, 0x8278, 0x8279, 0x0000, 0x0000
};

void m208_MainObjInit(omObjData *object);
void m208_StageObjInit(omObjData *object);
void m208_SoloObjInit(omObjData *object);
void m208_TeamObjInit(omObjData *object);

void m208_MainObjMain(omObjData *object);
void m208_StageObjMain(omObjData *object);
void m208_BackDraw(s16 *left, s16 *top, s16 *right, s16 *bottom);
void m208_HudDraw(Gfx **gfxPos, s32 arg1, s32 arg2);
void m208_SideInit(omObjData *object, s8 group);
void m208_SideObjMain(omObjData *object);

void m208_ObjectSetup(void) {
    omObjData *object;

    Hu3DSprModelInit(0x20);
    omInitObjMan(50, 0);
    omGameSysInit();
    Hu3DScreenClearF = 1;
    CamSetupInit(2);
    CamSetupMapCullAddMulti(2);
    ScissorSet(0, 0.0f, 0.0f, 140.0f, 240.0f);
    ScissorSet(1, 180.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 65.0f, 500.0f, 3000.0f);
    Hu3DCameraPerspectiveSet(1, 65.0f, 500.0f, 3000.0f);
    Hu3DFogSet(950, 1000, 0xFF, 0xFF, 0xFF);
    Hu3DBGColorSet(0xFF, 0xFF, 0xFF);
    Hu3DGLightMaxSet(2);
    Hu3DGLightDirSet(0, 0.0f, 0.0f, 90.0f);
    Hu3DGLightColorSet(0, 0x90, 0x90, 0x90);
    Hu3DGLightDirSet(1, -39.0f, 45.0f, 104.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    CenterM[0].x = 0.0f;
    CenterM[0].y = 115.0f;
    CenterM[0].z = -500.0f;
    CRotM[0].x = -16.0f;
    CRotM[0].y = 0.0f;
    CRotM[0].z = 0.0f;
    CZoomM[0] = 1260.0f;
    CenterM[1].x = 0.0f;
    CenterM[1].y = 115.0f;
    CenterM[1].z = -500.0f;
    CRotM[1].x = -16.0f;
    CRotM[1].y = 0.0f;
    CRotM[1].z = 0.0f;
    CZoomM[1] = 1260.0f;
    omAddObj(0, 0, 0, -1, m208_MainObjInit);
    m208_stageObj = omAddObj(8, 1, 1, -1, m208_StageObjInit);
    omSetStatBit(m208_stageObj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    m208_sideObjTbl[0] = omAddObj(3, 52, 21, -1, m208_SoloObjInit);
    m208_sideObjTbl[1] = omAddObj(3, 52, 21, -1, m208_TeamObjInit);
    object = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    object->work[0] = 2;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    GMesFontMesCreate(m208_fontMesTbl, 1);
    WipeCreateIn(0xFF, 16);
    m208_mgFlow.type = MINIGAME_2V2;
    m208_mgFlow.startDelay = -1;
    m208_mgFlow.startDelay = 75;
    m208_mgFlow.timer = 1800;
    m208_mgFlow.timeDisp = MG_TIME_DISP_COUNTDOWN;
    m208_mgFlow.timerMode = MG_TIMER_COUNT_DOWN;
    m208_mgFlow.finishDelay = 45;
    m208_mgFlow.resultDelay = 165;
    m208_mgFlow.newRecord = FALSE;
    m208_mgFlow.gauge = MG_GAUGE_NONE;
    m208_mgFlow.timeLimit = -1;
    MgFlowInit(&m208_mgFlow);
}

void m208_MainObjInit(omObjData *object) {
    s32 group;
    s32 i;

    m208_exitF = 0;
    m208_phase = 0;
    m208_phaseTimer = 0;
    m208_animCnt = 0;
    m208_winner = 5;
    m208_quitCnt = 0;
    m208_progressTbl[0] = m208_progressTbl[1] = m208_progressTbl[2] = m208_progressTbl[3] = 0.0f;
    m208_winZoomRate = 0.0f;
    m208_shakeTimerTbl[0] = m208_shakeTimerTbl[1] = 0;
    for (i = 0; i < 4; i++) {
        m208_groupPlayerTbl[i] = &m208_playerTbl[i];
        bzero(m208_groupPlayerTbl[i], sizeof(ThwompPullPlayer));
    }
    for (i = 0; i < 4; i++) {
        group = GwPlayer[i].group;
        group = (group == 3) ? 1 : (group == 1) ? 3
                                                : group;
        m208_playerGroupTbl[i] = group;
        m208_groupPlayerTbl[group]->playerNo = i;
        m208_groupPlayerTbl[group]->pad = GwPlayer[i].pad;
        m208_groupPlayerTbl[group]->chr = GwPlayer[i].chr;
        m208_groupPlayerTbl[group]->group = group;
        m208_groupPlayerTbl[group]->cpuDifficulty = (GwPlayer[i].stat & 1) ? GwPlayer[i].cpu_difficulty : -1;
    }
    Hu3DHookFuncCreate(0, m208_HudDraw, 2);
    object->func = m208_MainObjMain;
}

void m208_MainObjMain(omObjData *object) {
    omObjData *winner;
    s32 i;
    s32 j;
    u8 k;

    m208_phaseTimer++;
    m208_animCnt++;
    MgFlowMain();
    switch (m208_phase) {
        case 0:
            if (m208_phaseTimer == 1 && m208_exitF == 0 && omSysExitReq == 0) {
                HuAudFXPlay(0x335);
            }
            if (MgFlowStatGet() == MG_STATE_START) {
                m208_phase = 1;
                m208_phaseTimer = 0;
            }
            break;
        case 1:
            if (m208_phaseTimer == 31 && m208_exitF == 0 && omSysExitReq == 0) {
                HuAudSeqPlay(0x2E);
            }
            if (MgFlowStatGet() == MG_STATE_PLAY) {
                m208_phase = 2;
                m208_phaseTimer = 0;
            }
            break;
        case 2:
            if (m208_winner != 5 || MgFlowStatGet() == MG_STATE_FINISH) {
                if (m208_winner == 5) {
                    m208_phase = 5;
                    m208_winner = 4;
                } else {
                    m208_phase = 3;
                }
                m208_phaseTimer = 0;
            }
            if (m208_phase != 3) {
                break;
            }
        case 3:
        case 4:
            if (m208_phaseTimer == 0) {
                if (MgFlowStatGet() != MG_STATE_FINISH) {
                    MgFlowStatNext();
                }
                if (m208_winner == 0) {
                    m208_mgFlow.resultType = MG_RESULT_WIN_1;
                    m208_mgFlow.winners[0] = m208_groupPlayerTbl[0]->playerNo;
                    GwPlayer[m208_groupPlayerTbl[0]->playerNo].bonusCoin = 10;
                } else {
                    m208_mgFlow.resultType = MG_RESULT_WIN_3;
                    m208_mgFlow.winners[0] = m208_groupPlayerTbl[1]->playerNo;
                    m208_mgFlow.winners[1] = m208_groupPlayerTbl[3]->playerNo;
                    m208_mgFlow.winners[2] = m208_groupPlayerTbl[2]->playerNo;
                    GwPlayer[m208_groupPlayerTbl[1]->playerNo].bonusCoin = 10;
                    GwPlayer[m208_groupPlayerTbl[2]->playerNo].bonusCoin = 10;
                    GwPlayer[m208_groupPlayerTbl[3]->playerNo].bonusCoin = 10;
                }
            }
            if (m208_phaseTimer == 2) {
                MgFlowResultWaitSet(30);
            }
            if (m208_phaseTimer >= 31 && m208_phaseTimer <= 61) {
                m208_winZoomRate = (m208_phaseTimer - 31) / 30.0;
            }
            if (m208_phaseTimer >= 32 && m208_phaseTimer < 80 && m208_winner < 2) {
                winner = m208_sideObjTbl[m208_winner];
                if (m208_winAnimCnt == 0) {
                    for (i = 0; i < m208_winner * 2 + 1; i++) {
                        m208_winJumpXTbl[i] = m208_playerXTbl[m208_winner + i];
                        m208_winJumpYTbl[i] = m208_playerYTbl[m208_winner + i];
                        m208_winJumpZTbl[i] = m208_playerZTbl[m208_winner + i];
                        m208_winJumpVelXTbl[i] = (m208_winner != 0) ? (1 - i) * 1.5 : 0.0;
                        m208_winJumpVelYTbl[i] = 38.0f;
                        m208_winJumpVelZTbl[i] = 20.0f;
                        Hu3DModelAttrSet(winner->model[i + 1], 4, 4);
                        Hu3DModelAttrSet(winner->model[i + 39], 4, 0);
                        Hu3DModelPosSet(winner->model[i + 39], m208_winJumpXTbl[i], m208_winJumpYTbl[i],
                                        m208_winJumpZTbl[i]);
                        Hu3DModelRotSet(winner->model[i + 39], 0.0f, 0.0f, 0.0f);
                        Hu3DMotionShiftSet(winner->model[i + 39], Hu3DData[winner->motion[i + 15]].motId, 8, 4, 1);
                    }
                } else if (m208_winAnimCnt > 0 && m208_winAnimCnt < 100) {
                    for (i = 0; i < m208_winner * 2 + 1; i++) {
                        if (m208_winAnimCnt < 5) {
                            f32 dy[4] = { -23.0f, -98.0f, -86.0f, -98.0f };
                            f32 dz[4] = { -46.0f, -3.0f, -35.0f, -3.0f };

                            m208_playerYTbl[m208_winner + i] += dy[m208_winner + i] / 4.0;
                            m208_playerZTbl[m208_winner + i] += dz[m208_winner + i] / 4.0;
                            if (m208_winner == 1 && i == 0) {
                                m208_playerZTbl[m208_winner + i] = dz[m208_winner + i];
                            }
                        }
                        m208_winJumpXTbl[i] += m208_winJumpVelXTbl[i];
                        m208_winJumpYTbl[i] += m208_winJumpVelYTbl[i];
                        m208_winJumpZTbl[i] += m208_winJumpVelZTbl[i];
                        m208_winJumpVelYTbl[i] -= 4.0f;
                        Hu3DModelPosSet(winner->model[i + 39], m208_winJumpXTbl[i], m208_winJumpYTbl[i],
                                        m208_winJumpZTbl[i]);
                        Hu3DModelPosSet(winner->model[i + 42], m208_winJumpXTbl[i],
                                        (m208_winAnimCnt == 1) ? 30.0f : 0.0f, m208_winJumpZTbl[i]);
                        if (m208_winAnimCnt == 2) {
                            Hu3DModelLayerSet(winner->model[i + 42], 0x400);
                        }
                        if (m208_winAnimCnt == 1) {
                            Hu3DMotionShiftSet(winner->model[i + 39], Hu3DData[winner->motion[i + 12]].motId, 14, 4, 0);
                        }
                    }
                    if (m208_winJumpYTbl[0] <= 0.0f) {
                        m208_winAnimCnt = 100;
                        m208_winJumpYTbl[2] = m208_winJumpYTbl[1] = m208_winJumpYTbl[0] = 0.0f;
                        for (i = 0; i < m208_winner * 2 + 1; i++) {
                            Hu3DMotionShiftSet(winner->model[i + 39], Hu3DData[winner->motion[i + 15]].motId, 10, 4, 0);
                            Hu3DModelPosSet(winner->model[i + 39], m208_winJumpXTbl[i], 0.0f,
                                            m208_winJumpZTbl[i]);
                            Hu3DModelPosSet(winner->model[i + 42], m208_winJumpXTbl[i], 0.0f,
                                            m208_winJumpZTbl[i]);
                        }
                    }
                } else if (m208_winAnimCnt == 102) {
                    for (i = 0; i < m208_winner * 2 + 1; i++) {
                        Hu3DMotionShiftSet(winner->model[i + 39], Hu3DData[winner->motion[i]].motId, 0, 30, 2);
                    }
                }
                m208_winAnimCnt += (m208_winAnimCnt != 99);
            }
            if (mgFlowResultF != 0) {
                s32 slots[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

                if (m208_winner == 0) {
                    CharAnimSet(m208_sideObjTbl[0]->model[39], 1, slots[m208_groupPlayerTbl[0]->chr],
                                       m208_groupPlayerTbl[0]->unk_08);
                    Hu3DMotionModelSet(m208_sideObjTbl[0]->model[39], m208_sideObjTbl[0]->motion[9]);
                    Hu3DMotionAttrSet(m208_sideObjTbl[0]->model[39], 3, 0);
                    HuAudCharVoicePlay(m208_groupPlayerTbl[0]->unk_0C);
                } else if (m208_winner == 1) {
                    for (j = 0; j < 3; j++) {
                        CharAnimSet(m208_sideObjTbl[1]->model[j + 39], 1,
                                           slots[m208_groupPlayerTbl[1 + j]->chr],
                                           m208_groupPlayerTbl[1 + j]->unk_08);
                        Hu3DMotionModelSet(m208_sideObjTbl[1]->model[j + 39],
                                           m208_sideObjTbl[1]->motion[j + 9]);
                        Hu3DMotionAttrSet(m208_sideObjTbl[1]->model[j + 39], 3, 0);
                        HuAudCharVoicePlayPlayer(m208_groupPlayerTbl[1 + j]->unk_0C, -1,
                                           m208_groupPlayerTbl[1 + j]->playerNo);
                    }
                }
            }
            if (m208_phase == 3 && MgFlowStatGet() == MG_STATE_RESULT) {
                m208_phase = 4;
            }
            if (MgFlowStatGet() == MG_STATE_EXIT) {
                m208_phase = 7;
                m208_phaseTimer = 0;
            }
            break;
        case 5:
            if (m208_phaseTimer == 1) {
                m208_mgFlow.resultType = MG_RESULT_DRAW;
                m208_mgFlow.finishDelay = 75;
                m208_mgFlow.resultDelay = 0x90;
            }
            if (MgFlowStatGet() == MG_STATE_RESULT) {
                m208_phase = 6;
                m208_phaseTimer = 0;
            }
            break;
        case 6:
            if (MgFlowStatGet() == MG_STATE_EXIT) {
                m208_phase = 7;
                m208_phaseTimer = 0;
            }
            break;
        case 7:
            if (m208_phaseTimer == 1) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            } else if (m208_phaseTimer >= 32) {
                m208_exitF = 1;
            }
            break;
    }
    if (_CheckFlag(15) && omSysExitReq == 0 && m208_quitCnt == 0 && (u16)m208_phase == 2) {
        for (k = 0; k < 2; k++) {
            if (m208_groupPlayerTbl[k]->cpuDifficulty == -1 &&
                (HuPadBtnDown[m208_groupPlayerTbl[k]->pad] & R_TRIG)) {
                m208_quitCnt = 1;
            }
        }
    }
    if (m208_exitF != 0 || omSysExitReq != 0 || m208_quitCnt != 0) {
        if (omSysExitReq != 0 && m208_quitCnt == 0) {
            m208_quitCnt = 1;
        }
        if (m208_quitCnt != 0) {
            if (m208_quitCnt == 1) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                HuAudSeqFadeOut(20);
                HuAudFXAllFadeOut(20);
            }
            m208_quitCnt++;
            if (m208_quitCnt < 25) {
                return;
            }
        }
        HuAudSeqFadeOut(30);
        Hu3DMotionBakeFree(m208_pullMotBake);
        Hu3DMotionBakeFree(m208_throwMotBakeTbl[0]);
        Hu3DMotionBakeFree(m208_throwMotBakeTbl[1]);
        omOvlReturnEx(1);
    }
}

void m208_StageObjInit(omObjData *object) {
    s32 spriteFiles[10] = { 0x29001F, 0x290020, 0x210008, 0x210009, 0x21000A, 0x21000B, 0x21000C, 0x21000D, 0x21000E, 0x21000F };
    s16 i;

    for (i = 0; i < 10; i++) {
        m208_sprTbl[i] = espEntry(m208_sprAnimTbl[i] = HuSprAnimDataRead(spriteFiles[i]), 0, 0);
        espDispOff(m208_sprTbl[i]);
    }
    object->func = m208_StageObjMain;
}

void m208_StageObjMain(omObjData *object) {
    s16 left[2] = { 0, 160 };
    s16 top[2] = { 0, 0 };
    s16 right[2] = { 160, 320 };
    s16 bottom[2] = { 240, 240 };
    s32 other;
    s32 i;

    if (m208_animCnt == 100) {
        CenterM[0].x = CenterM[1].x = 0.0f;
        CenterM[0].y = CenterM[1].y = 115.0f;
        CenterM[0].z = CenterM[1].z = -500.0f;
        CRotM[0].x = CRotM[1].x = -16.0f;
        CRotM[0].y = CRotM[1].y = 0.0f;
        CRotM[0].z = CRotM[1].z = 0.0f;
        CZoomM[0] = CZoomM[1] = 1260.0f;
        Hu3DCameraPerspectiveSet(0, 65.0f, 500.0f, 3000.0f);
        Hu3DCameraPerspectiveSet(1, 65.0f, 500.0f, 3000.0f);
    }
    if (m208_winZoomRate > 0.0f && m208_winner < 2) {
        f32 progress = m208_winZoomRate;
        f32 remain = 1.0f - progress;
        f32 scissorLeft[2] = { 0.0f, 180.0f };
        f32 scissorRight[2] = { 140.0f, 320.0f };
        f32 viewScale[2] = { 1.0f, 1.0f };
        f32 viewX[2] = { 320.0f, 960.0f };
        f32 viewY[2] = { 480.0f, 480.0f };
        s32 offset;

        CenterM[m208_winner].y = remain * 115.0f - progress * 80.0f;
        CRotM[m208_winner].x = remain * -16.0f - progress * 6.0f;
        CZoomM[m208_winner] = remain * 1260.0f + (m208_winner * 150 + 1600) * progress;
        viewScale[m208_winner] = progress + 1.0f;
        scissorLeft[m208_winner] = remain * scissorLeft[m208_winner] + progress * 0.0f;
        scissorRight[m208_winner] = remain * scissorRight[m208_winner] + progress * 320.0f;
        viewX[m208_winner] = remain * viewX[m208_winner] + progress * 640.0f;
        viewY[m208_winner] = remain * viewY[m208_winner] + progress * ((m208_winner != 0) ? 780.0 : 720.0);
        left[m208_winner] = left[m208_winner] * remain + progress * 0.0f;
        right[m208_winner] = right[m208_winner] * remain + progress * 320.0f;
        top[m208_winner] =
            top[m208_winner] * remain + progress * ((m208_winner != 0) ? -30.0f : -60.0f);
        bottom[m208_winner] =
            bottom[m208_winner] * remain + progress * ((m208_winner != 0) ? 450.0f : 420.0f);
        if (m208_winner == 0) {
            scissorLeft[1] = remain * scissorLeft[1] + progress * 318.0f;
            scissorRight[1] = remain * scissorRight[1] + progress * 320.0f;
            viewX[1] = progress * 712.0f + viewX[1];
            offset = progress * 178.0f;
            left[1] += offset;
            right[1] += offset;
        } else {
            scissorLeft[0] = remain * scissorLeft[0] + progress * 0.0f;
            scissorRight[0] = remain * scissorRight[0] + progress * 2.0f;
            viewX[0] = viewX[0] - progress * 712.0f;
            offset = progress * 178.0f;
            left[0] -= offset;
            right[0] -= offset;
        }
        ScissorSet(0, scissorLeft[0], 0.0f, scissorRight[0], 240.0f);
        ScissorSet(1, scissorLeft[1], 0.0f, scissorRight[1], 240.0f);
        ViewportSet(0, viewScale[0] * 640.0f, viewScale[0] * 480.0f, 511.0f, viewX[0], viewY[0], 511.0f);
        ViewportSet(1, viewScale[1] * 640.0f, viewScale[1] * 480.0f, 511.0f, viewX[1], viewY[1], 511.0f);
        m208_BackDraw(left, top, right, bottom);
        if (m208_winZoomRate == 1.0f) {
            object = m208_sideObjTbl[1 - m208_winner];
            other = 1 - m208_winner;
            Hu3DModelAttrSet(object->model[7], 4, 4);
            for (i = 0; i < other * 2 + 1; i++) {
                Hu3DModelAttrSet(object->model[i + 1], 4, 4);
            }
            for (i = 0; i < 3; i++) {
                Hu3DModelAttrSet(object->model[i + 4], 4, 4);
            }
            for (i = 0; i < 4; i++) {
                Hu3DModelAttrSet(object->model[i + 12], 4, 4);
                Hu3DModelAttrSet(object->model[i + 18], 4, 4);
            }
        }
    } else if (m208_animCnt < 100) {
        f32 progress;
        f32 remain;

        if (m208_animCnt < 80) {
            progress = m208_animCnt / 80.0;
        } else {
            progress = 1.0f;
        }
        remain = 1.0f - progress;
        CenterM[0].x = CenterM[1].x = progress * 435.0f - remain * 60.0f;
        CenterM[0].y = CenterM[1].y = 140.0f;
        CenterM[0].z = CenterM[1].z = -660.0f;
        CRotM[0].x = CRotM[1].x = -8.0f;
        CRotM[0].y = CRotM[1].y = -225.0f;
        CRotM[0].z = CRotM[1].z = 0.0f;
        CZoomM[0] = CZoomM[1] = 100.0f;
        CenterM[1].x = -CenterM[1].x;
        CRotM[1].y = -CRotM[1].y;
        Hu3DCameraPerspectiveSet(0, 65.0f, 50.0f, 4000.0f);
        Hu3DCameraPerspectiveSet(1, 65.0f, 50.0f, 4000.0f);
        top[0] += m208_shakeOfsTbl[0];
        bottom[0] += m208_shakeOfsTbl[0];
        top[1] += m208_shakeOfsTbl[1];
        bottom[1] += m208_shakeOfsTbl[1];
        m208_BackDraw(left, top, right, bottom);
        ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, m208_shakeOfsTbl[0] * 4.0f + 480.0f, 511.0f);
        ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, m208_shakeOfsTbl[1] * 4.0f + 480.0f, 511.0f);
    } else if (m208_animCnt < 150) {
        f32 scale;
        f32 remain;

        if (m208_animCnt >= 100) {
            if (m208_animCnt < 115) {
                scale = (m208_animCnt - 100) / 15.0;
            } else {
                scale = 1.0f;
            }
        } else {
            scale = 0.0f;
        }
        remain = 1.0f - scale;
        scale = (remain * remain * remain * 0.75 + remain * 0.25) * 0.5 + 1.0;
        ViewportSet(0, scale * 640.0f, scale * 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
        ViewportSet(1, scale * 640.0f, scale * 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
        left[0] = (left[0] - 80) * scale + 80.0f;
        top[0] = (top[0] - 120) * scale + 120.0f;
        right[0] = (right[0] - 80) * scale + 80.0f;
        bottom[0] = (bottom[0] - 120) * scale + 120.0f;
        left[1] = (left[1] - 240) * scale + 240.0f;
        top[1] = (top[1] - 120) * scale + 120.0f;
        right[1] = (right[1] - 240) * scale + 240.0f;
        bottom[1] = (bottom[1] - 120) * scale + 120.0f;
        Hu3DCameraPerspectiveSet(0, 65.0f, 500.0f, 3000.0f);
        Hu3DCameraPerspectiveSet(1, 65.0f, 500.0f, 3000.0f);
        m208_BackDraw(left, top, right, bottom);
    } else {
        f32 scale;

        if (m208_animCnt >= 90) {
            if (m208_animCnt < 120) {
                scale = 2.5 - (m208_animCnt - 90) / 30.0 * 1.5;
            } else {
                scale = 1.0f;
            }
        } else {
            scale = 2.5f;
        }
        ViewportSet(0, scale * 640.0f, scale * 480.0f, 511.0f, 320.0f, m208_shakeOfsTbl[0] * 4.0f + 480.0f,
                    511.0f);
        ViewportSet(1, scale * 640.0f, scale * 480.0f, 511.0f, 960.0f, m208_shakeOfsTbl[1] * 4.0f + 480.0f,
                    511.0f);
        left[0] = (left[0] - 80) * scale + 80.0f;
        top[0] = (top[0] - 120) * scale + 120.0f;
        right[0] = (right[0] - 80) * scale + 80.0f;
        bottom[0] = (bottom[0] - 120) * scale + 120.0f;
        left[1] = (left[1] - 240) * scale + 240.0f;
        top[1] = (top[1] - 120) * scale + 120.0f;
        right[1] = (right[1] - 240) * scale + 240.0f;
        bottom[1] = (bottom[1] - 120) * scale + 120.0f;
        top[0] += m208_shakeOfsTbl[0];
        bottom[0] += m208_shakeOfsTbl[0];
        top[1] += m208_shakeOfsTbl[1];
        bottom[1] += m208_shakeOfsTbl[1];
        m208_BackDraw(left, top, right, bottom);
    }
    if (!omPauseChk()) {
        s32 shake;

        shake = m208_shakeTimerTbl[0];
        m208_shakeOfsTbl[0] = ((shake & 1) ? -shake : shake) * 0.5;
        m208_shakeTimerTbl[0] -= (m208_shakeTimerTbl[0] != 0) ? 1 : 0;
        shake = m208_shakeTimerTbl[1];
        m208_shakeOfsTbl[1] = ((shake & 1) ? -shake : shake) * 0.5;
        m208_shakeTimerTbl[1] -= (m208_shakeTimerTbl[1] != 0) ? 1 : 0;
    }
}

void m208_BackDraw(s16 *left, s16 *top, s16 *right, s16 *bottom) {
    s32 scissorLeft[2];
    s32 scissorRight[2];
    f32 scaleX[2];
    f32 offsetX[2];
    f32 scaleY[2];
    f32 offsetY[2];
    s32 dsdx[2];
    s32 dtdy[2];
    HuSprAnimPat *frame;
    HuSprite *sprite;
    f32 progress;
    f32 remain;
    f32 s0;
    f32 t0;
    f32 s1;
    f32 t1;
    s32 xl;
    s32 yl;
    s32 xh;
    s32 yh;
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < 2; i++) {
        scaleX[i] = (right[i] - left[i]) / 160.0;
        offsetX[i] = left[i];
        dsdx[i] = (1.0 / scaleX[i]) * 1024.0;
        scaleY[i] = (bottom[i] - top[i]) / 240.0;
        offsetY[i] = top[i];
        dtdy[i] = (1.0 / scaleY[i]) * 1024.0;
        scissorLeft[i] = (i == 0) ? 0 : 180;
        scissorRight[i] = (i != 0) ? 320 : 140;
    }
    if (m208_winZoomRate > 0.0f && m208_winner < 2) {
        progress = m208_winZoomRate;
        remain = 1.0f - progress;
        i = m208_winner;
        scissorLeft[i] = scissorLeft[i] * remain + progress * 0.0f;
        scissorRight[i] = scissorRight[i] * remain + progress * 320.0f;
        if (i == 0) {
            scissorLeft[1] = scissorLeft[1] * remain + progress * 318.0f;
            scissorRight[1] = scissorRight[1] * remain + progress * 320.0f;
        } else {
            scissorLeft[0] = scissorLeft[0] * remain + progress * 0.0f;
            scissorRight[0] = scissorRight[0] * remain + progress * 2.0f;
        }
    }

    gSPDisplayList(gMainGfxPos++, m208_backGfx);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    sprite = HuSprGet(esprite[m208_sprTbl[0]].unk04, 0);
    frame = &sprite->data->pat[sprite->patNo];
    gDPLoadTLUT_pal256(gMainGfxPos++, sprite->data->pal);
    for (j = 0; j < 3; j++) {
        t0 = j * 40;
        t1 = t0 + 40.0f + ((j == 2) ? -0.75 : 1.0);
        for (k = 0; k < 4; k++) {
            s0 = k * 40;
            s1 = s0 + 40.0f + ((k < 3) ? 1.0f : 0.0f);
            gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_CI, G_IM_SIZ_8b, 160, 120, (s32)s0, (s32)t0, (s32)s1,
                               (s32)t1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
            for (i = 0; i < 2; i++) {
                if (m208_winZoomRate == 1.0f && i != m208_winner) {
                    continue;
                }
                xl = (s0 * scaleX[i] + offsetX[i]) * 4.0f;
                yl = ((t0 - 1.0f) * scaleY[i] + offsetY[i]) * 4.0f;
                xh = (s1 * scaleX[i] + offsetX[i]) * 4.0f;
                yh = ((t1 - 1.0f) * scaleY[i] + offsetY[i]) * 4.0f;
                if (xl > 1280 || yl > 960) {
                    continue;
                }
                if (xh < 0 || yh < 0) {
                    continue;
                }
                gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, scissorLeft[i], 0, scissorRight[i], 240);
                gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, s0 * 32.0f, t0 * 32.0f, dsdx[i],
                                        dtdy[i]);
            }
        }
    }
}

void m208_HudDraw(Gfx **gfxPos, s32 arg1, s32 arg2) {
    HuSprAnimPat *frame;
    HuSprite *sprite;
    f32 *gauge;
    f32 slide;
    f32 scale;
    f32 x;
    f32 y;
    f32 x2;
    f32 y2;
    s32 offset = 0;
    s32 group;
    s32 i;
    s32 j;

    m208_frameToggleF = !m208_frameToggleF;
    if (m208_frameToggleF != 0) {
        return;
    }
    if (m208_winZoomRate > 0.0f) {
        slide = m208_winZoomRate * 178.0f;
        if (m208_winner != 0) {
            offset = -slide * 4.0f;
        } else {
            offset = slide * 4.0f;
        }
    }
    gSPDisplayList(gMainGfxPos++, m208_backGfx);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    sprite = HuSprGet(esprite[m208_sprTbl[1]].unk04, 0);
    frame = &sprite->data->pat[sprite->patNo];
    gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);
    gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 0);
    for (j = 0; j < 4; j++) {
        gDPLoadTextureTile_4b(gMainGfxPos++, frame->data, G_IM_FMT_CI, 40, 240, 0, j * 60, 40, j * 60 + 60, 0,
                              G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                              G_TX_NOLOD);
        y = j * 60;
        y2 = j * 60 + 61;
        y2 = MIN(240.0f, y2);
        gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
        gSPScisTextureRectangle(gMainGfxPos++, offset + 140 * 4, (s32)(y * 4.0f), offset + 180 * 4, (s32)(y2 * 4.0f),
                                G_TX_RENDERTILE, 0, j * 60 * 32, 1024, 1024);
    }
    gDPSetCombineMode(gMainGfxPos++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 224);
    for (i = 0; i < 4; i++) {
        s32 order[4] = { 3, 1, 2, 0 };

        group = order[i];
        sprite = HuSprGet(esprite[m208_sprTbl[2 + m208_groupPlayerTbl[group]->chr]].unk04, 0);
        frame = &sprite->data->pat[sprite->patNo];
        if (m208_groupPlayerTbl[group]->chr == 7) {
            gDPLoadTLUT_pal256(gMainGfxPos++, sprite->data->pal);
        } else {
            gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
        }
        if (m208_groupPlayerTbl[group]->chr == 7) {
            gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_CI, G_IM_SIZ_8b, 18, 18, 0, 0, 18, 18, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                               G_TX_NOLOD);
        } else {
            gDPLoadTextureTile_4b(gMainGfxPos++, frame->data, G_IM_FMT_CI, 18, 18, 0, 0, 18, 18, 0,
                                  G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                  G_TX_NOLOD, G_TX_NOLOD);
        }
        if (group > 0) {
            x = (3 - group) * 7 + 151;
        } else {
            x = 136.0f;
        }
        gauge = (group == 0) ? &m208_progressTbl[0] : &m208_progressTbl[1];
        y = *gauge * 165.0f + 35.0f;
        switch (group) {
            case 0:
                y = (s32)y;
                break;
            case 2:
                y = (s32)y - 3;
                break;
            case 1:
            case 3:
                y = (s32)y + 6;
                break;
        }
        x2 = x + 18.0f;
        y2 = y + 18.0f;
        scale = 1024.0f;
        gSPScisTextureRectangle(gMainGfxPos++, x * 4.0f + offset, (s32)(y * 4.0f), x2 * 4.0f + offset,
                                y2 * 4.0f - 3.0f, G_TX_RENDERTILE, 0, 0, (s32)scale, (s32)scale);
    }
    gDPPipeSync(gMainGfxPos++);
    gDPSetBlendColor(gMainGfxPos++, 255, 255, 255, 0);
    gDPPipeSync(gMainGfxPos++);
}

void m208_SoloObjInit(omObjData *object) {
    m208_SideInit(object, 0);
    object->func = m208_SideObjMain;
}

void m208_TeamObjInit(omObjData *object) {
    m208_SideInit(object, 1);
    object->func = NULL;
}

void m208_SideInit(omObjData *object, s8 group) {
    s32 dirs[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
    s32 files[8] = { 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 3 };
    s32 shadowFiles[8] = { 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 1 };
    s32 slots[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    s32 motionFiles[2][8] = {
        { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B },
        { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C },
    };
    s32 attr;
    u16 i;
    u16 chr;

    attr = 0x8B9;
    for (i = 0; i < ((group != 0) ? 3 : 1); i++) {
        chr = m208_groupPlayerTbl[group + i]->chr;
        object->model[i + 1] = Hu3DModelRead((dirs[chr] << 16) | files[chr], attr);
        Hu3DModelCameraSet(object->model[i + 1], (group != 0) ? 2 : 1);
        object->model[i + 39] = Hu3DModelRead((dirs[chr] << 16) | shadowFiles[chr], 0x8AD);
        Hu3DModelCameraSet(object->model[i + 39], (group != 0) ? 2 : 1);
        m208_groupPlayerTbl[group + i]->unk_06 = CharAnimCreate(
            object->model[i + 39], 1, slots[chr], (dirs[chr] << 16) | motionFiles[0][chr]);
        m208_groupPlayerTbl[group + i]->unk_08 =
            Hu3DAnimDataRead((dirs[chr] << 16) | motionFiles[1][chr]);
        Hu3DModelAnimStop(Hu3DData[object->model[i + 39]].hmf);
        Hu3DModelDynamicFree(object->model[i + 39]);
        m208_groupPlayerTbl[group + i]->unk_0C = (rand8() & 1) ? 0x2F : 0x30;
        omObjMotionRead(object, i, CharMotionDataNumGet(chr, 0));
        omObjMotionRead(object, i + 3, CharMotionDataNumGet(chr, 0x84));
        omObjMotionRead(object, i + 6, CharMotionDataNumGet(chr, 0x21));
        omObjMotionRead(object, i + 12, CharMotionDataNumGet(chr, 4));
        omObjMotionRead(object, i + 15, CharMotionDataNumGet(chr, 0x1F));
        omObjMotionRead(object, i + 9, CharMotionDataNumGet(chr, m208_groupPlayerTbl[group + i]->unk_0C));
        m208_groupPlayerTbl[group + i]->unk_0C |= dirs[chr] << 16;
        m208_playerXTbl[group + i] = (group != 0) ? (1 - i) * 125 : 0.0f;
        m208_playerYTbl[group + i] = 25.0f;
        m208_playerZTbl[group + i] = (group != 0) ? -((i % 2) * 20) : 0.0f;
        Hu3DModelPosSet(object->model[i + 1], m208_playerXTbl[group + i], m208_playerYTbl[group + i],
                        m208_playerZTbl[group + i]);
        Hu3DModelRotSet(object->model[i + 1], 0.0f, 180.0f, 0.0f);
        Hu3DMotionModelSet(object->model[i + 1], object->motion[i + 3]);
        Hu3DMotionAttrSet(object->model[i + 1], 3, 1);
        Hu3DMotionModelSet(object->model[i + 39], object->motion[i + 3]);
        Hu3DModelObjAttrSet(object->model[1], 0x600, 0x400);
    }

    attr = 0x8B9;
    object->model[7] = Hu3DModelRead((group == 0) ? 0x290009 : 0x29000A, attr);
    Hu3DModelCameraSet(object->model[7], (group != 0) ? 2 : 1);
    Hu3DModelPosSet(object->model[7], 0.0f, 0.0f, (group != 0) ? -25.0f : 35.0f);
    Hu3DModelRotSet(object->model[7], 0.0f, 180.0f, 0.0f);

    attr = 0xAB9;
    for (i = 0; i < 3; i++) {
        object->model[i + 8] = Hu3DModelRead(0x290007, attr);
        Hu3DModelCameraSet(object->model[i + 8], (group != 0) ? 2 : 1);
        Hu3DMotionAttrSet(object->model[i + 8], 3, 1);
        Hu3DMotionReset(object->model[i + 8]);
    }
    if (group == 0) {
        omObjMotionRead(object, 20, 0x290008);
        Hu3DMotionModelSet(object->model[8], object->motion[20]);
        m208_pullMotBake = Hu3DMotionBake(object->model[8], 1);
        Hu3DModelKill(object->motion[20]);
    }
    for (i = 0; i < 3; i++) {
        Hu3DMotionModelSet(object->model[i + 8], m208_sideObjTbl[0]->motion[20]);
    }

    attr = 0x8B9;
    for (i = 0; i < 3; i++) {
        if (group == 0 && i == 0) {
            object->model[4] = Hu3DModelRead(0x290012, attr);
        } else {
            object->model[i + 4] = Hu3DModelLink(m208_sideObjTbl[0]->model[4]);
        }
        Hu3DModelPosSet(object->model[i + 4], (1 - i) * (group * 60 + 200), 0.0f, -300.0f);
        Hu3DModelRotSet(object->model[i + 4], 0.0f, 180.0f, 0.0f);
        Hu3DModelScaleSet(object->model[i + 4], group * 0.5 + 1.0, group * 0.5 + 1.0, group * 0.5 + 1.0);
        Hu3DModelCameraSet(object->model[i + 4], (group != 0) ? 2 : 1);
        Hu3DModelObjAttrSet(object->model[i + 4], 0x600, 0);
    }

    attr = 0xABD;
    for (i = 0; i < 3; i++) {
        s32 lightFiles[2][3] = { { 0x13, 0x14, 0x15 }, { 0x16, 0x17, 0x18 } };

        object->model[i + 46] = Hu3DModelRead(lightFiles[group][i] | 0x290000, attr);
        Hu3DModelPosSet(object->model[i + 46], (1 - i) * (group * 60 + 200), 0.0f, -300.0f);
        Hu3DModelRotSet(object->model[i + 46], -16.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(object->model[i + 46], group * 0.5 + 1.0, group * 0.5 + 1.0, group * 0.5 + 1.0);
        Hu3DModelCameraSet(object->model[i + 46], (group != 0) ? 2 : 1);
        Hu3DModelObjAttrSet(object->model[i + 46], 0x600, 0);
        Hu3DModelObjAttrSet(object->model[i + 46], 0x70000000, 0x70000000);
        Hu3DLLightCreate(object->model[i + 46], 1);
        Hu3DLLightColorSet(object->model[i + 46], 255, 255, 255);
        Hu3DLLightDirSet(object->model[i + 46], 0.0f, 0.0f, 127.0f);
    }

    attr = 0x8BD;
    for (i = 0; i < 3; i++) {
        if (group == 0) {
            object->model[i + 30] =
                Hu3DModelRead((i == 0) ? 0x29000B : (i == 1) ? 0x29000C
                                                                  : 0x29000D,
                                   attr);
        } else {
            object->model[i + 30] = Hu3DModelLink(m208_sideObjTbl[0]->model[i + 30]);
        }
        Hu3DModelPosSet(object->model[i + 30],
                        ((1 - i) * 175 + 50) - (i == 2) * ((group == 0) ? 10 : 60), 300.0f, -300.0f);
        Hu3DModelScaleSet(object->model[i + 30], 1.6820346f, 1.6820346f, 1.6820346f);
        Hu3DModelObjAttrSet(object->model[i + 30], 0x70000000, 0x70000000);
        Hu3DModelCameraSet(object->model[i + 30], (group != 0) ? 2 : 1);
    }

    if (group >= 0) {
        object->model[33] = Hu3DModelRead(0x29001C, 0x4DD);
    } else {
        object->model[33] = Hu3DModelLink(m208_sideObjTbl[0]->model[33]);
    }
    Hu3DModelCameraSet(object->model[33], (group != 0) ? 2 : 1);
    Hu3DModelScaleSet(object->model[33], 4.0f, 4.0f, 4.0f);
    Hu3DModelRotSet(object->model[33], 0.0f, 45.0f, 0.0f);
    Hu3DMotionReset(object->model[33]);
    if (group == 0) {
        omObjMotionRead(object, 18, 0x29001D);
        Hu3DMotionModelSet(object->model[33], object->motion[18]);
        m208_throwMotBakeTbl[0] = Hu3DMotionBake(object->model[33], 2);
        Hu3DModelKill(object->motion[18]);
        omObjMotionRead(object, 19, 0x29001E);
        Hu3DMotionModelSet(object->model[33], object->motion[19]);
        m208_throwMotBakeTbl[1] = Hu3DMotionBake(object->model[33], 2);
        Hu3DModelKill(object->motion[19]);
    }
    Hu3DMotionModelSet(object->model[33], m208_sideObjTbl[0]->motion[18]);
    Hu3DMotionBakeApply(object->model[33], m208_throwMotBakeTbl[0], 0);

    object->model[34] = Hu3DModelRead(0x29001A, 0x8DD);
    Hu3DModelCameraSet(object->model[34], (group != 0) ? 2 : 1);
    Hu3DModelScaleSet(object->model[34], 1.0f, 1.0f, 1.0f);
    Hu3DMotionAttrSet(object->model[34], 3, 1);
    Hu3DModelObjAttrSet(object->model[34], 0x600, 0x400);

    object->model[36] = Hu3DModelRead(0x29001B, 0x8CD);
    Hu3DModelCameraSet(object->model[36], (group != 0) ? 2 : 1);
    Hu3DModelScaleSet(object->model[36], 2.5f, 2.5f, 2.5f);
    Hu3DModelObjAttrSet(object->model[36], 0x600, 0x400);

    for (i = 0; i < 1; i++) {
        object->model[35] = Hu3DModelRead(0x29001A, 0x8CD);
        Hu3DModelTPLvlInit(object->model[35]);
        Hu3DModelTPLvlSet(object->model[35], 255);
        Hu3DModelCameraSet(object->model[i + 35], (group != 0) ? 2 : 1);
        Hu3DModelScaleSet(object->model[i + 35], 0.25f, 0.25f, 0.25f);
        Hu3DMotionAttrSet(object->model[i + 35], 3, 1);
        Hu3DModelObjAttrSet(object->model[i + 35], 0x600, 0x400);
    }

    object->model[38] = Hu3DModelRead(9, 0x4CD);
    Hu3DModelScaleSet(object->model[38], 3.5f, 3.5f, 3.0f);
    Hu3DModelCameraSet(object->model[38], (group != 0) ? 2 : 1);
    Hu3DModelTPLvlInit(object->model[38]);
    Hu3DModelTPLvlSet(object->model[38], 128);

    for (i = 0; i < group * 2 + 1; i++) {
        if (i == 0) {
            object->model[42] = Hu3DModelRead(9, 0x4C9);
            Hu3DModelTPLvlInit(object->model[42]);
            Hu3DModelTPLvlSet(object->model[42], 128);
            Hu3DModelLayerSet(object->model[42], 0x800);
        } else {
            object->model[i + 42] = Hu3DModelLink(object->model[42]);
        }
        Hu3DModelPosSet(object->model[i + 42], m208_playerXTbl[group + i], 28.0f,
                        m208_playerZTbl[group + i]);
        Hu3DModelCameraSet(object->model[i + 42], (group != 0) ? 2 : 1);
    }

    if (group == 0) {
        object->model[22] = Hu3DModelRead(0x290003, 0x4BD);
    } else {
        object->model[22] = Hu3DModelLink(m208_sideObjTbl[0]->model[22]);
    }
    Hu3DModelCameraSet(object->model[22], (group != 0) ? 2 : 1);
    Hu3DLLightCreate(object->model[22], 1);
    Hu3DLLightColorSet(object->model[22], 255, 255, 255);
    Hu3DLLightDirSet(object->model[22], 0.0f, 0.0f, 127.0f);

    for (i = 0; i < 4; i++) {
        if (group == 0 && i == 0) {
            object->model[18] = Hu3DModelRead(0x290004, 0x4BD);
        } else {
            object->model[i + 18] = Hu3DModelLink(m208_sideObjTbl[0]->model[18]);
        }
        Hu3DModelCameraSet(object->model[i + 18], (group != 0) ? 2 : 1);
        Hu3DModelObjAttrSet(object->model[i + 18], 0x600, 0);
        Hu3DLLightCreate(object->model[i + 18], 1);
        Hu3DLLightColorSet(object->model[i + 18], 255, 255, 255);
        Hu3DLLightDirSet(object->model[i + 18], 0.0f, 0.0f, 127.0f);
    }

    if (group == 0) {
        object->model[23] = Hu3DModelRead(0x290005, 0x4DD);
    } else {
        object->model[23] = Hu3DModelLink(m208_sideObjTbl[0]->model[23]);
    }
    Hu3DModelCameraSet(object->model[23], (group != 0) ? 2 : 1);
    Hu3DLLightCreate(object->model[23], 1);
    Hu3DLLightColorSet(object->model[23], 255, 255, 255);
    Hu3DLLightDirSet(object->model[23], 0.0f, 0.0f, 127.0f);

    attr = 0x41D;
    for (i = 0; i < 2; i++) {
        object->model[i + 24] = Hu3DModelRead((group == 0) ? 0x29000E : 0x29000F, attr);
        Hu3DModelCameraSet(object->model[i + 24], (group != 0) ? 2 : 1);
    }
    Hu3DModelAttrSet(object->model[24], 4, 0);
    Hu3DModelPosSet(object->model[24], 0.0f, 0.0f, -315.0f);

    object->model[11] = Hu3DModelRead((group == 0) ? 0x290010 : 0x290011, 0x4D9);
    Hu3DModelPosSet(object->model[11], 0.0f, 10.0f, 0.0f);
    Hu3DModelScaleSet(object->model[11], 1.0f, 1.0f, 12.0f);
    Hu3DModelObjAttrSet(object->model[11], 0x600, 0);
    Hu3DModelCameraSet(object->model[11], (group != 0) ? 2 : 1);

    attr = 0x6CD;
    for (i = 0; i < 3; i++) {
        object->model[i + 49] = Hu3DModelRead(0x290019, attr);
        Hu3DModelCameraSet(object->model[i + 49], (group != 0) ? 2 : 1);
        Hu3DModelScaleSet(object->model[i + 49], group * 0.5 + 1.75, group * 0.5 + 1.75, group * 0.5 + 1.75);
    }

    if (group == 0) {
        object->model[16] = Hu3DModelRead(0x290000, 0x45D);
    } else {
        object->model[16] = Hu3DModelLink(m208_sideObjTbl[0]->model[16]);
    }
    Hu3DModelCameraSet(object->model[16], (group != 0) ? 2 : 1);
    Hu3DModelObjAttrSet(object->model[16], 0x600, 0);

    for (i = 0; i < 4; i++) {
        if (group == 0 && i == 0) {
            object->model[12] = Hu3DModelRead(0x290001, 0x41D);
        } else {
            object->model[i + 12] = Hu3DModelLink(m208_sideObjTbl[0]->model[12]);
        }
        Hu3DModelCameraSet(object->model[i + 12], (group != 0) ? 2 : 1);
        Hu3DModelObjAttrSet(object->model[i + 12], 0x600, 0);
        Hu3DModelObjAttrSet(object->model[i + 12], 0x600, 0);
    }

    if (group == 0) {
        object->model[17] = Hu3DModelRead(0x290002, 0x45D);
    } else {
        object->model[17] = Hu3DModelLink(m208_sideObjTbl[0]->model[17]);
    }
    Hu3DModelCameraSet(object->model[17], (group != 0) ? 2 : 1);
    Hu3DModelObjAttrSet(object->model[17], 0x600, 0);
}

void m208_MotTimeSet(s16 arg0, s16 arg1) {
    HmfModel *model = &Hu3DData[arg0];
    f32 value = arg1;

    Hu3DMotionTimeSet(arg0, value);
    model->hmf->unk98->unk08 = value;
}

void m208_SideObjMain(omObjData *object) {
    s32 pressed[4][3];
    s32 buttons[3] = { A_BUTTON, B_BUTTON, Z_TRIG };
    s16 cpuParams[5][4] = {
        { 17, 15, 13, 14 },
        { 5, 3, 2, 1 },
        { 1006, 1012, 1030, 1024 },
        { 12, 12, 8, 2 },
        { 5, 5, 6, 1 },
    };
    u8 visible[3];
    HmfMotionNode *node;
    s32 group;
    s32 i;
    s32 j;
    s32 k;

    if (m208_frameCnt == 0) {
        for (i = 0; i < 2; i++) {
            m208_promptOrderTbl[i][0] = rand8() % 3;
            m208_promptOrderTbl[i][1] = (m208_promptOrderTbl[i][0] + (rand8() & 1) + 1) % 3;
            m208_promptOrderTbl[i][2] = 3 - (m208_promptOrderTbl[i][0] + m208_promptOrderTbl[i][1]);
        }
        for (i = 0; i < 4; i++) {
            m208_comWaitTbl[i] = cpuParams[0][m208_groupPlayerTbl[i]->cpuDifficulty] +
                                        rand8() % cpuParams[1][m208_groupPlayerTbl[i]->cpuDifficulty];
        }
    }
    Hu3DScreenClearF = (m208_phase < 2 || m208_winZoomRate > 0.0f);
    for (group = 0; group < 2; group++) {
        object = m208_sideObjTbl[group];
        for (i = 0; i < 3; i++) {
            for (j = group; j < group * 3 + 1; j++) {
                pressed[j][i] =
                    m208_stunTimerTbl[j] == 0 && m208_phase == 2 &&
                    ((m208_groupPlayerTbl[j]->cpuDifficulty == -1)
                         ? (HuPadBtnDown[m208_groupPlayerTbl[j]->pad] & buttons[i]) != 0
                         : (m208_comHitFTbl[j] != 0 &&
                            i == m208_promptOrderTbl[group][m208_promptNoTbl[group]] &&
                            m208_promptLockTbl[group] == 1 && m208_promptTimerTbl[group] == 18));
            }
            visible[i] =
                (Hu3DData[object->model[30 + m208_promptOrderTbl[group][m208_promptNoTbl[group]]]].attr & 4) !=
                0;
            Hu3DModelAttrSet(object->model[30 + i], 4, 4);
        }
        m208_promptTimerTbl[group]++;
        if (m208_promptLockTbl[group] == 1 && m208_promptTimerTbl[group] >= 20) {
            m208_promptLockTbl[group] = 0;
            m208_promptTimerTbl[group] = 0;
        }
        if (m208_promptLockTbl[group] == 0 &&
            m208_missTimerTbl[group][0] + m208_missTimerTbl[group][1] + m208_missTimerTbl[group][2] == 0) {
            if (m208_phase == 2 &&
                m208_stunTimerTbl[(group != 0) ? m208_promptOrderTbl[group][m208_promptNoTbl[group]] + 1 : 0] == 0) {
                if (visible[m208_promptOrderTbl[group][m208_promptNoTbl[group]]]) {
                    HuAudFXPlay((group != 0) ? 0x33F : 0x33E);
                }
                Hu3DModelAttrSet(object->model[30 + m208_promptOrderTbl[group][m208_promptNoTbl[group]]], 4, 0);
            }
            j = group + m208_promptOrderTbl[group][m208_promptNoTbl[group]] * group;
            if (m208_groupPlayerTbl[j]->cpuDifficulty == 3 && m208_promptNoTbl[group] == 2 &&
                m208_comWaitTbl[j] >= 3) {
                m208_comWaitTbl[j] = (rand8() & 1) + 1;
            }
            m208_comWaitTbl[j] -=
                (m208_comWaitTbl[j] > 0 && m208_stunTimerTbl[j] == 0 && m208_phase == 2);
            if ((m208_groupPlayerTbl[j]->cpuDifficulty == -1)
                    ? pressed[j][m208_promptOrderTbl[group][m208_promptNoTbl[group]]]
                    : m208_comWaitTbl[j] <= 0) {
                pressed[j][m208_promptOrderTbl[group][m208_promptNoTbl[group]]] = FALSE;
                m208_comWaitTbl[j] = cpuParams[0][m208_groupPlayerTbl[j]->cpuDifficulty] +
                                            rand8() % cpuParams[1][m208_groupPlayerTbl[j]->cpuDifficulty];
                m208_comHitFTbl[j] = rand8() % cpuParams[2][m208_groupPlayerTbl[j]->cpuDifficulty] == 1;
                m208_promptLockTbl[group] = 1;
                m208_promptTimerTbl[group] = 0;
                m208_hopTimerTbl[group] = 1;
                m208_dustNoTbl[group]++;
                m208_dustNoTbl[group] %= 2;
                m208_pullMotTimerTbl[j] = 20;
                HuAudFXPlay((group != 0) ? 0x33B : 0x33A);
                m208_promptNoTbl[group]++;
                m208_promptNoTbl[group] %= 3;
                if (m208_promptNoTbl[group] == 0) {
                    m208_promptOrderTbl[group][0] = rand8() % 3;
                    m208_promptOrderTbl[group][1] = (m208_promptOrderTbl[group][0] + (rand8() & 1) + 1) % 3;
                    m208_promptOrderTbl[group][2] =
                        3 - (m208_promptOrderTbl[group][0] + m208_promptOrderTbl[group][1]);
                }
            }
            if (m208_promptLockTbl[group] == 0 && m208_phase == 2 &&
                m208_stunTimerTbl[(group != 0) ? m208_promptOrderTbl[group][m208_promptNoTbl[group]] + 1 : 0] == 0) {
                if (visible[m208_promptOrderTbl[group][m208_promptNoTbl[group]]]) {
                    HuAudFXPlay((group != 0) ? 0x33F : 0x33E);
                }
                Hu3DModelAttrSet(object->model[30 + m208_promptOrderTbl[group][m208_promptNoTbl[group]]], 4, 0);
            }
        }
        for (j = group; j < group * 3 + 1; j++) {
            m208_pullMotTimerTbl[j] -= (m208_pullMotTimerTbl[j] != 0) ? 1 : 0;
            if (m208_pullMotTimerTbl[j] == 19) {
                Hu3DMotionShiftSet(object->model[1 + j - group], Hu3DData[object->motion[3 + j - group]].motId, 2, 1, 0);
            }
        }
        if (m208_missTimerTbl[group][0] + m208_missTimerTbl[group][1] + m208_missTimerTbl[group][2] == 0) {
            for (i = 0; i < 3; i++) {
                for (j = group; j < group * 3 + 1; j++) {
                    if (pressed[j][i]) {
                        m208_missTimerTbl[group][(group != 0) ? j - 1 : i] = 15;
                        HuAudFXPlay((group != 0) ? 0x339 : 0x338);
                        if (m208_groupPlayerTbl[j]->cpuDifficulty != -1) {
                            m208_comHitFTbl[j] = 0;
                            m208_comWaitTbl[j] = cpuParams[3][m208_groupPlayerTbl[j]->cpuDifficulty] +
                                                        rand8() % cpuParams[4][m208_groupPlayerTbl[j]->cpuDifficulty];
                        }
                    }
                }
            }
        }
        if (-m208_distTbl[group] <= 1500.0f || ((s32)-m208_distTbl[group] - 1000) % 3000 < 500) {
            i = ((s32)-m208_distTbl[group] - 1000) / 3000;
            i = (i == 0 || m208_distTbl[1 - group] < m208_distTbl[group]) ? 80 : (i == 1) ? 17
                                                                                                              : 7;
            m208_throwFrameTbl[group] = (i + m208_frameCnt + rand8() % 10 - 5) % 90;
        }
        if (m208_frameCnt % 90 == m208_throwFrameTbl[group] && m208_rockStateTbl[group] == 0 &&
            m208_phase == 2 && !(Hu3DData[object->model[33]].attr & 4) &&
            -m208_distTbl[group] >= 1500.0f &&
            ((s32)-m208_distTbl[group] - 1000) % 3000 >= 500 &&
            ((s32)-m208_distTbl[group] - 1000) % 3000 <= 2900) {
            m208_throwTimerTbl[group] = 1;
            m208_rockStateTbl[group] = 1;
            Hu3DMotionModelSet(object->model[33], m208_sideObjTbl[0]->motion[18]);
            Hu3DModelAttrSet(object->model[35], 4, 0);
            Hu3DModelAttrSet(object->model[35], 0x4000, 0);
            Hu3DModelTPLvlSet(object->model[35], 255);
        }
        if (m208_throwTimerTbl[group] != 0) {
            if (m208_throwTimerTbl[group] < 16) {
                Hu3DMotionBakeApply(object->model[33], m208_throwMotBakeTbl[0], m208_throwTimerTbl[group] * 2 - 2);
            }
            if (m208_throwTimerTbl[group] >= 8 && m208_throwTimerTbl[group] < 16) {
                f32 t;
                f32 u;

                t = (m208_throwTimerTbl[group] - 8) / 8.0;
                t = (t > 1.0f) ? 1.0f : t;
                u = 1.0f - t;
                m208_rockXTbl[group][0] = u * u * -35.0f - (1.0f - u * u) * 176.0f;
                m208_rockYTbl[group][0] = (1.0f - t * t) * 140.0f + t * t * 190.0f;
                m208_rockZTbl[group][0] = (1.0f - t * t) * -130.0f;
                Hu3DModelScaleSet(object->model[35], (1.0f - u * u) * 0.5 + 0.5, (1.0f - u * u) * 0.5 + 0.5,
                                  (1.0f - u * u) * 0.5 + 0.5);
                Hu3DModelTPLvlSet(object->model[35], (s32)((1.0f - u * u) * 191.0f) + 64);
            } else if (m208_throwTimerTbl[group] < 16) {
                m208_rockXTbl[group][0] = m208_rockYTbl[group][0] = m208_rockZTbl[group][0] =
                    0.0f;
                Hu3DModelScaleSet(object->model[35], 0.0f, 0.0f, 0.0f);
                Hu3DModelTPLvlSet(object->model[35], 16);
            }
            if (m208_throwTimerTbl[group] == 16) {
                Hu3DMotionModelSet(object->model[33], m208_sideObjTbl[0]->motion[19]);
                Hu3DModelAttrSet(object->model[35], 4, 0);
                Hu3DModelHookSet(object->model[35], object->model[33], "srowman-item_fook");
                Hu3DModelAttrSet(object->model[35], 0x4000, 0x4000);
                Hu3DModelTPLvlSet(object->model[35], 255);
            }
            if (m208_throwTimerTbl[group] >= 16 && m208_throwTimerTbl[group] < 46) {
                Hu3DMotionBakeApply(object->model[33], m208_throwMotBakeTbl[1], (m208_throwTimerTbl[group] - 16) * 2);
            }
            if (m208_throwTimerTbl[group] < 26) {
                node = Hu3DModelObjPtrGet(object->model[33], "srowman-item_fook");
                node->baseScale.x = 0.25f;
                node->baseScale.y = 0.25f;
                node->baseScale.z = 0.25f;
                node->basePos.x = 300.0f;
                node->basePos.y = 150.0f;
                node->basePos.z = 150.0f;
                node->unk4C = 0;
            }
            if (m208_throwTimerTbl[group] == 26) {
                m208_rockStateTbl[group] = 2;
                Hu3DModelAttrSet(object->model[35], 0x4000, 0);
                Hu3DModelAttrSet(object->model[35], 4, 4);
                Hu3DModelAttrSet(object->model[34], 4, 0);
                Hu3DModelAttrSet(object->model[38], 4, 0);
                m208_rockXTbl[group][0] = Hu3DData[object->model[33]].pos.x + -105.0f;
                m208_rockYTbl[group][0] = Hu3DData[object->model[33]].pos.y + 219.0f;
                m208_rockZTbl[group][0] = Hu3DData[object->model[33]].pos.z + -18.0f + m208_distTbl[group];
                m208_rockVelXTbl[group][0] = 20.0f;
                m208_rockVelYTbl[group][0] = 50.0f;
                m208_rockVelZTbl[group][0] = 0.0f;
            }
            if (m208_throwTimerTbl[group] >= 27 && m208_throwTimerTbl[group] < 76) {
                for (k = 0; (m208_rockStateTbl[group] == 3) ? k < 3 : k < 1; k++) {
                    if (m208_rockYTbl[group][k] > 0.0f) {
                        m208_rockXTbl[group][k] += m208_rockVelXTbl[group][k];
                        m208_rockYTbl[group][k] += m208_rockVelYTbl[group][k];
                        m208_rockZTbl[group][k] += m208_rockVelZTbl[group][k];
                        m208_rockVelYTbl[group][k] -= (m208_rockStateTbl[group] == 3) ? 0 : 4;
                    } else {
                        m208_rockYTbl[group][k] = 0.0f;
                    }
                }
                if (m208_rockStateTbl[group] == 2) {
                    j = m208_rockZTbl[group][0] - m208_distTbl[group];
                    if (j >= -549 && j <= -251) {
                        j = 1;
                        i = m208_rockYTbl[group][0] <= Hu3DData[object->model[5]].pos.y + 90.0f + group * 55;
                    } else if (j >= -249 && j < 100) {
                        j = 2;
                        i = m208_rockYTbl[group][0] <= 100.0f;
                    } else {
                        j = 0;
                        i = m208_rockYTbl[group][0] <= 0.0f;
                    }
                    if (i) {
                        m208_rockStateTbl[group] = 3;
                        if (j == 2) {
                            HuAudFXPlay((group != 0) ? 0x33D : 0x33C);
                        } else {
                            s32 seNo = HuAudFXPlay((group != 0) ? 0x33D : 0x33C);

                            if (seNo != -1) {
                                f32 vol = m208_rockZTbl[group][0] - m208_distTbl[group] - 200.0f;

                                vol = (vol > 0.0f) ? 0.0f : vol / 2000.0 * 26.0;
                                HuAudFXVolSet(seNo, (s32)vol + 127);
                            }
                        }
                        Hu3DModelAttrSet(object->model[34], 4, 4);
                        Hu3DModelAttrSet(object->model[38], 4, 4);
                        m208_rockXTbl[group][3] = m208_rockXTbl[group][0];
                        m208_rockYTbl[group][3] = m208_rockYTbl[group][0];
                        m208_rockZTbl[group][3] = m208_rockZTbl[group][0];
                        if (j == 2) {
                            m208_rockZTbl[group][0] =
                                (m208_rockZTbl[group][0] < m208_distTbl[group] + 35.0f)
                                    ? m208_distTbl[group] + 35.0f
                                    : m208_rockZTbl[group][0];
                        }
                        if (j == 2 && m208_phase == 2) {
                            for (i = 0; i < group * 2 + 1; i++) {
                                m208_stunTimerTbl[i + group] = 31;
                                Hu3DMotionShiftSet(object->model[i + 1], Hu3DData[object->motion[i + 6]].motId, 0, 14, 0);
                                omVibrate(m208_groupPlayerTbl[i + group]->playerNo, 20, 0, 20);
                            }
                        }
                        i = rand8() / 255.0 * 360.0;
                        for (k = 0; k < 1; k++) {
                            f32 dir;

                            m208_rockTimerTbl[group] = 0.0f;
                            j = rand8() / 3 - 42;
                            dir = i + k * 120 + j;
                            m208_rockVelXTbl[group][k] = sindf(dir) * 20.0f;
                            m208_rockVelZTbl[group][k] = cosdf(dir) * 20.0f;
                            m208_rockVelYTbl[group][k] = rand8() / 255.0 * 30.0 + 20.0;
                            m208_rockVelXTbl[group][k] = m208_rockVelYTbl[group][k] =
                                m208_rockVelZTbl[group][k] = 0.0f;
                            m208_rockXTbl[group][k] =
                                m208_rockXTbl[group][0] + m208_rockVelXTbl[group][k] * 2.0f;
                            m208_rockYTbl[group][k] =
                                m208_rockYTbl[group][0] + m208_rockVelYTbl[group][k] * 2.0f;
                            m208_rockZTbl[group][k] =
                                m208_rockZTbl[group][0] + m208_rockVelZTbl[group][k] * 2.0f;
                            Hu3DModelAttrSet(object->model[34], 4, 4);
                            Hu3DModelAttrSet(object->model[35], 4, 4);
                            Hu3DModelAttrSet(object->model[36], 4, 0);
                            Hu3DModelPosSet(object->model[36], m208_rockXTbl[group][0],
                                            m208_rockYTbl[group][0] + 100.0f,
                                            m208_rockZTbl[group][0] - m208_distTbl[group]);
                            Hu3DModelRotSet(object->model[36], 0.0f, rand8() / 256.0 * 360.0, 0.0f);
                            m208_MotTimeSet(object->model[36], 4);
                            m208_rockBreakTimerTbl[group] = 20;
                        }
                    }
                }
            }
            if (m208_throwTimerTbl[group] == 76) {
                m208_throwTimerTbl[group] = 0;
                m208_rockStateTbl[group] = 0;
                Hu3DModelAttrSet(object->model[34], 4, 4);
                Hu3DModelAttrSet(object->model[35], 4, 4);
            }
            if (m208_rockStateTbl[group] >= 2 &&
                m208_rockZTbl[group][0] - m208_distTbl[group] + 35.0f >= 378.0f) {
                m208_throwTimerTbl[group] = 0;
                m208_rockStateTbl[group] = 0;
                Hu3DModelAttrSet(object->model[34], 4, 4);
                Hu3DModelAttrSet(object->model[35], 4, 4);
                Hu3DModelAttrSet(object->model[38], 4, 4);
                Hu3DModelAttrSet(object->model[36], 4, 4);
            }
            m208_throwTimerTbl[group] += (m208_throwTimerTbl[group] != 0) ? 1 : 0;
        }
        m208_rockBreakTimerTbl[group] += (m208_rockBreakTimerTbl[group] != 0) ? 1 : 0;
        Hu3DModelAttrSet(object->model[36], 4, (m208_rockBreakTimerTbl[group] == 0) ? 4 : 0);
        m208_hopTimerTbl[group] += (m208_hopTimerTbl[group] != 0) ? 1 : 0;
        if (m208_hopTimerTbl[group] > 20) {
            m208_hopTimerTbl[group] = 0;
            omVibrate(m208_groupPlayerTbl[group]->playerNo, 10, 0, 10);
            if (group == 1) {
                omVibrate(m208_groupPlayerTbl[2]->playerNo, 10, 0, 10);
                omVibrate(m208_groupPlayerTbl[3]->playerNo, 10, 0, 10);
            }
        }
        m208_distTbl[group] -=
            (m208_hopTimerTbl[group] != 0 &&
             m208_missTimerTbl[group][0] + m208_missTimerTbl[group][1] + m208_missTimerTbl[group][2] == 0) *
            450 / 20.0;
        for (i = 0; i < 3; i++) {
            m208_missTimerTbl[group][i] -= (m208_missTimerTbl[group][i] != 0) ? 1 : 0;
            if (m208_phase == 0) {
                f32 time;
                f32 fall;
                f32 height;

                if (group == 0) {
                    time = m208_phaseTimer - (2 - i) * 20;
                } else {
                    time = m208_phaseTimer - i * 20;
                }
                fall = (time >= 28.0f && time < 34.0f) ? (time - 28.0f) / 6.0 : 0.0f;
                if (time < 0.0f) {
                    height = 0.0f;
                } else if (time < 20.0f) {
                    height = time / 20.0 * 120.0;
                } else if (time < 28.0f) {
                    height = 120.0f;
                } else if (time < 34.0f) {
                    fall = 1.0f - fall * fall;
                    height = fall * 120.0f;
                } else {
                    height = 0.0f;
                }
                if (Hu3DData[object->model[i + 4]].pos.y > 0.0f && height <= 0.0f) {
                    m208_shakeTimerTbl[group] = 4;
                    HuAudFXPlay((group != 0) ? 0x337 : 0x336);
                    Hu3DModelAttrSet(object->model[i + 49], 4, 0);
                    m208_MotTimeSet(object->model[i + 49], 6);
                    m208_landTimerTbl[group][i] = 27;
                    m208_landZTbl[group][i] = m208_distTbl[group];
                }
                Hu3DData[object->model[i + 4]].pos.y = height;
                m208_dustZTbl[group][0] = m208_distTbl[group] - 300.0f;
            } else {
                if (m208_hopCurveTbl[m208_hopTimerTbl[group]] == 0.0f && m208_hopTimerTbl[group] != 0 &&
                    m208_hopTimerTbl[group] < 20) {
                    m208_hopCurveTbl[m208_hopTimerTbl[group]] =
                        sindf(m208_hopTimerTbl[group] / 20.0 * 180.0);
                }
                Hu3DData[object->model[i + 4]].pos.y =
                    (m208_hopTimerTbl[group] != 0) ? m208_hopCurveTbl[m208_hopTimerTbl[group]] * 100.0f
                                                         : 0.0f;
                if (m208_hopTimerTbl[group] == 20) {
                    if (i == 0) {
                        m208_shakeTimerTbl[group] = 2;
                        HuAudFXPlay((group != 0) ? 0x337 : 0x336);
                    }
                    Hu3DModelAttrSet(object->model[i + 49], 4, 0);
                    m208_MotTimeSet(object->model[i + 49], 0);
                    m208_dustZTbl[group][m208_dustNoTbl[group]] = m208_distTbl[group] - 300.0f;
                    m208_dustTimerTbl[group][m208_dustNoTbl[group]] = 0;
                    m208_dustTimerTbl[group][(m208_dustNoTbl[group] + 1) % 2] = 1;
                    Hu3DModelAttrSet(object->model[m208_dustNoTbl[group] + 24], 4, 0);
                    m208_MotTimeSet(object->model[m208_dustNoTbl[group] + 24], 0);
                    m208_landTimerTbl[group][i] = 22;
                    m208_landZTbl[group][i] = m208_distTbl[group];
                }
            }
            if (m208_missTimerTbl[group][i] != 0) {
                if ((m208_frameCnt & 1) == group % 2) {
                    f32 shake;
                    f64 rot;

                    shake = m208_missTimerTbl[group][i] / 15.0;
                    shake = 1.0f - (1.0f - shake) * (1.0f - shake);
                    shake = shake * 0.5 + 0.5;
                    rot = rand8() / 256.0 * 10.0 * shake;
                    shake = ((m208_frameCnt & 3) >= 2) ? -rot : rot;
                    Hu3DData[object->model[i + 4]].rot.z = shake;
                } else {
                    Hu3DData[object->model[i + 4]].rot.z *= 0.5;
                }
            } else {
                Hu3DData[object->model[i + 4]].rot.z = 0.0f;
            }
        }
        for (i = 0; i < 3; i++) {
            Hu3DModelPosSet(object->model[i + 49], Hu3DData[object->model[i + 4]].pos.x, 0.0f,
                            Hu3DData[object->model[i + 4]].pos.z + m208_landZTbl[group][i] -
                                m208_distTbl[group]);
            if (m208_landTimerTbl[group][i] == 1) {
                Hu3DModelAttrSet(object->model[i + 49], 4, 4);
            }
            m208_landTimerTbl[group][i] -= (m208_landTimerTbl[group][i] != 0) ? 1 : 0;
        }
        for (i = 0; i < group * 2 + 1; i++) {
            if (m208_stunTimerTbl[i + group] == 11) {
                Hu3DMotionShiftSet(object->model[i + 1], Hu3DData[object->motion[i + 3]].motId, 0, 20, 1);
            }
            m208_stunTimerTbl[i + group] -= (m208_stunTimerTbl[i + group] != 0) ? 1 : 0;
            Hu3DModelAttrSet(object->model[i + 1], 4,
                               ((m208_stunTimerTbl[i + group] & 1) ||
                                (m208_winner == group && m208_winZoomRate > 0.0f))
                                   ? 4
                                   : 0);
            Hu3DModelAttrSet(object->model[i + 42], 4,
                               ((m208_stunTimerTbl[i + group] & 1) &&
                                !(m208_winner == group && m208_winZoomRate != 0.0f))
                                   ? 4
                                   : 0);
        }
        if (group == 1) {
            i = rand8() & 1;
            if (m208_distTbl[i] <= -10210.0f) {
                j = i;
            } else if (m208_distTbl[1 - i] <= -10210.0f) {
                j = 1 - i;
            } else {
                j = -1;
            }
            if (j != -1 && m208_winner == 5) {
                m208_winner = j;
            }
        }
        m208_distTbl[group] =
            (m208_distTbl[group] < -10950.0f) ? -10950.0f : m208_distTbl[group];
        m208_progressTbl[group] = m208_distTbl[group] / 10280.0f + 1.0f;
        m208_progressTbl[group] = (m208_progressTbl[group] < 0.0f) ? 0.0f : m208_progressTbl[group];
        for (i = 0; i < 1; i++) {
            for (j = 0; j < 2; j++) {
                Hu3DModelPosSet(object->model[j + 24], 0.0f, 0.0f,
                                m208_dustZTbl[group][j] - m208_distTbl[group] - 0.0f);
                if (m208_dustTimerTbl[group][j] < 60 && m208_dustTimerTbl[group][j] + 1 >= 60) {
                    Hu3DModelAttrSet(object->model[j + 24], 4, 4);
                    Hu3DMotionTimeSet(object->model[j + 24], 0.0f);
                }
                m208_dustTimerTbl[group][j] +=
                    (m208_dustTimerTbl[group][j] != 0 && m208_dustTimerTbl[group][j] < 60 &&
                     m208_hopTimerTbl[group] != 0 && m208_hopTimerTbl[group] < 20) *
                    3;
                if (m208_dustTimerTbl[group][j] < 60) {
                    Hu3DMotionTimeSet(object->model[j + 24], m208_dustTimerTbl[group][j]);
                }
            }
        }
        for (i = 0; i < group * 2 + 1; i++) {
            HmfModel *model = &Hu3DData[object->model[1]];
            f32 pullOffsets[8] = { 23.0f, 56.0f, 0.0f, 35.0f, 7.0f, 19.0f, 23.0f, 0.0f };
            f32 walkOffsets[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -40.0f, 0.0f, 0.0f };
            f32 from;
            f32 to;
            f32 blend;

            if (model->motId == Hu3DData[object->motion[3]].motId) {
                from = pullOffsets[m208_groupPlayerTbl[group + i]->chr];
            } else if (model->motId == Hu3DData[object->motion[6]].motId) {
                from = walkOffsets[m208_groupPlayerTbl[group + i]->chr];
            } else {
                from = 0.0f;
            }
            if (model->motIdShift != 0xFF) {
                if (model->motIdShift == Hu3DData[object->motion[3]].motId) {
                    to = pullOffsets[m208_groupPlayerTbl[group + i]->chr];
                } else if (model->motIdShift == Hu3DData[object->motion[6]].motId) {
                    to = walkOffsets[m208_groupPlayerTbl[group + i]->chr];
                } else {
                    to = 0.0f;
                }
            } else {
                to = from;
            }
            if (model->unk0E < model->unk0C && model->unk0C > 0) {
                blend = (f32)model->unk0E / (f32)model->unk0C;
            } else {
                blend = 1.0f;
            }
            blend = from * (1.0f - blend) + to * blend;
            Hu3DModelPosSet(object->model[i + 1], m208_playerXTbl[group + i], m208_playerYTbl[group + i],
                            blend + m208_playerZTbl[group + i]);
        }
        for (i = 0; i < 3; i++) {
            f32 x = m208_playerXTbl[group + group * i];
            f32 y = m208_playerYTbl[group + group * i] + 75.0f -
                    ((m208_winner == 0) ? m208_winZoomRate * 105.0f : 0.0f);
            f32 z = m208_playerZTbl[group + group * i] - 50.0f;
            f32 px;
            f32 py;
            f32 pz;
            f32 dx;
            f32 dy;
            f32 dz;
            f32 dist;
            f32 yaw;
            f32 pitch;
            f32 rotX;
            f32 frac;

            px = Hu3DData[object->model[i + 4]].pos.x -
                 ((Hu3DData[object->model[i + 4]].rot.z != 0.0f)
                      ? sindf(Hu3DData[object->model[i + 4]].rot.z) * 20.6426 * 5.0
                      : 0.0) *
                     ((group != 0) ? 1.5 : 1.0);
            py = Hu3DData[object->model[i + 4]].pos.y +
                 ((Hu3DData[object->model[i + 4]].rot.z != 0.0f)
                      ? cosdf(Hu3DData[object->model[i + 4]].rot.z) * 20.6426 * 5.0
                      : 20.6426 * 5.0) *
                     ((group != 0) ? 1.5 : 1.0);
            pz = Hu3DData[object->model[i + 4]].pos.z + 79.0315 * ((group != 0) ? 1.5 : 1.0);
            dx = px - x;
            dy = py - y;
            dz = pz - z;
            dist = HuSqrtf(dx * dx + dy * dy + dz * dz);
            yaw = atan2df(-dx, -dz);
            pitch = atan2df(dy, -dz);
            rotX = pitch * (1.0f - ((yaw > 0.0f) ? yaw : -yaw) / 90.0f / 2.0f);
            Hu3DModelPosSet(object->model[i + 8], x, y, z);
            Hu3DModelRotSet(object->model[i + 8], 360.0f - (rotX + 90.0f), yaw + 180.0f, 0.0f);
            {
                f32 far[2][3] = { { 282.0f, 199.0f, 282.0f }, { 268.0f, 187.0f, 268.0f } };
                f32 near[2][3] = { { 276.0f, 170.0f, 276.0f }, { 183.0f, 92.0f, 183.0f } };

                far[group][i] = far[group][i] * 0.625 + near[group][i] * 0.375;
                near[group][i] *= (i != 0) ? 0.5 : 0.625;
                if (dist < near[group][i]) {
                    frac = 1.0f;
                } else if (far[group][i] < dist) {
                    frac = 0.0f;
                } else {
                    frac = 1.0f - (dist - near[group][i]) / (far[group][i] - near[group][i]);
                }
            }
            Hu3DModelScaleSet(object->model[i + 8], 1.0f, dist / 500.0, 1.0f);
            Hu3DMotionBakeApply(object->model[i + 8], m208_pullMotBake, frac * 60.0f);
        }
        Hu3DModelAttrSet(object->model[16], 4, 4);
        Hu3DModelAttrSet(object->model[22], 4, 4);
        Hu3DModelAttrSet(object->model[17], 4, 4);
        Hu3DModelAttrSet(object->model[23], 4, 4);
        Hu3DModelAttrSet(object->model[33], 4, 4);
        for (i = 0; i < 4; i++) {
            f32 rem = (m208_distTbl[group] - 3000.0f) -
                      (s32)((m208_distTbl[group] - 3000.0f) / 1000.0f) * 1000;
            s32 seg = (m208_distTbl[group] - 3000.0f) / 1000.0f + 3.0f - i;

            if (seg >= -11 && seg <= 0) {
                if (seg == -4 || seg == -7 || seg == -10) {
                    f32 z = (500 - i * 1000) - rem;

                    if (z + 750.0f > -3000.0f) {
                        Hu3DModelAttrSet(object->model[33], 4, 0);
                        Hu3DModelPosSet(object->model[33], -515.0f, 85.0f, z - 250.0f);
                        switch (m208_rockStateTbl[group]) {
                            case 1:
                                Hu3DModelPosSet(object->model[35], m208_rockXTbl[group][0] + -515.0f,
                                                m208_rockYTbl[group][0] + 85.0f,
                                                (500 - i * 1000) - rem - 250.0f + m208_rockZTbl[group][0]);
                                break;
                            case 2:
                                Hu3DModelPosSet(object->model[34], m208_rockXTbl[group][0],
                                                m208_rockYTbl[group][0],
                                                m208_rockZTbl[group][0] - m208_distTbl[group]);
                                Hu3DModelPosSet(object->model[38], m208_rockXTbl[group][0], 0.0f,
                                                m208_rockZTbl[group][0] - m208_distTbl[group]);
                                break;
                            case 3:
                                Hu3DModelPosSet(object->model[36], 0.0f, 0.0f,
                                                m208_rockZTbl[group][0] - m208_distTbl[group] + 35.0f);
                                m208_rockTimerTbl[group] += 1.0f;
                                break;
                        }
                    }
                }
                Hu3DModelAttrSet(object->model[i + 12], 4, 4);
                Hu3DModelAttrSet(object->model[i + 18], 4, 4);
                seg = (seg == 0) ? 16 : (seg == -11) ? 17
                                                     : i + 12;
                if (m208_winZoomRate < 1.0f || m208_winner == group) {
                    Hu3DModelAttrSet(object->model[seg], 4, 0);
                }
                Hu3DModelPosSet(object->model[seg], 0.0f, 0.0f, (500 - i * 1000) - rem);
                seg = (seg == 45) ? i + 18 : seg + 6;
                if (m208_winZoomRate < 1.0f || m208_winner == group) {
                    Hu3DModelAttrSet(object->model[seg], 4, 0);
                }
                Hu3DModelPosSet(object->model[seg], 0.0f, 0.0f, (500 - i * 1000) - rem);
            }
        }
    }
    for (group = 0; group < 2; group++) {
        f32 lightOfsX[2][3] = { { 3.0f, 1.0f, -6.5f }, { 11.0f, -0.5f, -11.0f } };
        f32 lightOfsY[2][3] = { { 76.0f, 81.5f, 76.0f }, { 106.5f, 107.0f, 110.0f } };
        f32 lightScaleXZ[2][3] = { { 0.813f, 0.781f, 0.828f }, { 0.008f, -0.188f, -0.117f } };
        f32 lightScaleY[2][3] = { { 0.883f, 0.773f, 0.906f }, { -0.117f, -0.141f, -0.117f } };

        object = m208_sideObjTbl[group];
        for (i = 0; i < 3; i++) {
            Hu3DModelPosSet(object->model[i + 46], Hu3DData[object->model[i + 4]].pos.x + lightOfsX[group][i],
                            Hu3DData[object->model[i + 4]].pos.y + lightOfsY[group][i],
                            Hu3DData[object->model[i + 4]].pos.z);
            Hu3DModelScaleSet(object->model[i + 46], Hu3DData[object->model[i + 4]].scale.x + lightScaleXZ[group][i],
                              Hu3DData[object->model[i + 4]].scale.y + lightScaleY[group][i],
                              Hu3DData[object->model[i + 4]].scale.z + lightScaleXZ[group][i]);
            if (m208_winZoomRate == 0.0f && CRotM[group].x == -16.0f &&
                Hu3DData[object->model[i + 4]].rot.z == 0.0f) {
                Hu3DModelAttrSet(object->model[i + 46], 4, 0);
                Hu3DModelAttrSet(object->model[i + 4], 4, 4);
            } else {
                Hu3DModelAttrSet(object->model[i + 4], 4, 0);
                Hu3DModelAttrSet(object->model[i + 46], 4, 4);
            }
        }
    }
    m208_frameCnt++;
}
