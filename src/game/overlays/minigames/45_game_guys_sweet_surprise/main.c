#include "common.h"
#include "game_guys_sweet_surprise.h"

typedef struct GameGuysSweetSurprisePadValues {
    /* 0x00 */ s16 v[4]; // one entry per controller port
} GameGuysSweetSurprisePadValues;

typedef struct GameGuysSweetSurprisePos {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
} GameGuysSweetSurprisePos;

typedef struct GameGuysSweetSurpriseRewardTable {
    /* 0x00 */ s16 v[6];
} GameGuysSweetSurpriseRewardTable;

typedef struct GameGuysSweetSurpriseResultWork { // 0xC bytes
    /* 0x00 */ s16 winningSide;
    /* 0x02 */ s16 unk_02[2];
    /* 0x06 */ s16 unk_06[3];
} GameGuysSweetSurpriseResultWork;

s16 m269_comKeyWaitTbl[3] = { 5, 25, 60 }; // COM key wait frames, indexed by CPU difficulty
s16 m269_mainPhase = 0;                // main state
s16 m269_mainTimer = 0;                // main state timer
s16 m269_resultMesId = 0;                // message window

const GameGuysSweetSurprisePadValues m269_playerNoTbl = { { 0, 1, 2, 3 } }; // player slots
const GameGuysSweetSurpriseRewardTable m269_payoutChoiceTbl = { { 2, 4, 8, 16, 32, 64 } };
const GameGuysSweetSurpriseRewardTable m269_oddsTbl = { { 0, 5, 6, 7, 8, 9 } };

char m269_mesBuf[0x100] BSS;
Process *m269_mesProc BSS;
Process *m269_choiceWinProc BSS;
s16 m269_playerInfo[7] BSS; // player, pad, chr, is CPU, CPU difficulty, coins, coins
s16 m269_winF BSS;
s16 m269_choiceNo BSS;
s16 m269_comChoiceNo BSS;
GameGuysSweetSurpriseResultWork m269_resultWork BSS;
extern s16 m269_winSide;    // m269_resultWork.winningSide
extern s16 m269_sidePayoutTbl[2]; // m269_resultWork.unk_02
extern s16 m269_sideMesTbl[2]; // m269_resultWork.unk_06
s16 m269_sprTbl[36] BSS;   // sprite IDs
omObjData *m269_hudObj BSS;
omObjData *m269_markerObj BSS;
omObjData *m269_gambleObj BSS;
omObjData *m269_wanwanLObj BSS;
omObjData *m269_wanwanRObj BSS;
omObjData *m269_bellObj BSS;
omObjData *m269_crumbObj BSS;
s16 m269_procDoneF BSS; // process done flag
s16 m269_portraitDispF BSS;
s16 m269_choiceF BSS; // choice active
s16 m269_cakeDropF BSS;
s16 m269_eatCntTbl[2] BSS; // per-side score
s16 m269_crumbRReq BSS;
s16 m269_crumbLReq BSS;
s16 m269_markerDropF BSS;
s16 m269_gambleMotNo BSS;
s16 m269_gambleActF BSS;
s16 m269_wanwanLMotNo BSS;
s16 m269_wanwanLActNo BSS;
s16 m269_wanwanRMotNo BSS;
s16 m269_wanwanRActNo BSS;
s16 m269_bellRingReq BSS;
s16 m269_smokeReq BSS;
s16 m269_oddsMax BSS;
s16 m269_oddsNum BSS;
s16 m269_comLevel BSS; // COM difficulty
s16 m269_wanwanMdl BSS; // linked model source

void m269_ObjectSetup(void);
void m269_CameraInit(void);
void m269_WinInit(void);
void m269_PlayerInfoInit(void);
void m269_MainObjInit(omObjData *object);
void m269_OddsInit(void);
void m269_MainObjMain(omObjData *object);
void m269_IntroObjMain(omObjData *object);
void m269_RuleProc(void);
void m269_ChoiceWinProc(void);
void m269_ChoiceObjMain(omObjData *object);
void m269_ChoiceMesProc(void);
void m269_CakeSetObjMain(omObjData *object);
void m269_EatStartObjMain(omObjData *object);
void m269_EatObjMain(omObjData *object);
void m269_JudgeObjMain(omObjData *object);
void m269_ExitStartObjMain(omObjData *object);
void m269_ExitObjMain(omObjData *object);
void m269_ExitCheckObjMain(omObjData *object);
void m269_HudObjInit(omObjData *object);
void m269_BackSprInit(void);
void m269_PanelSprInit(void);
void m269_PayoutSprInit(void);
void m269_ChoiceSprInit(void);
void m269_PortraitSprInit(void);
void m269_CakeSprInit(void);
void m269_CoinSprInit(void);
void m269_HudObjMain(omObjData *object);
void m269_BannerUpdate(void);
void m269_ChoiceSprUpdate(void);
void m269_PortraitSprUpdate(void);
void m269_CakeSprUpdate(void);
void m269_CoinSprUpdate(void);
void m269_MarkerObjInit(omObjData *object);
void m269_MarkerObjMain(omObjData *object);
void m269_GambleObjInit(omObjData *object);
void m269_GambleObjMain(omObjData *object);
void m269_WanwanLObjInit(omObjData *object);
void m269_WanwanLObjMain(omObjData *object);
void m269_WanwanRObjInit(omObjData *object);
void m269_WanwanRObjMain(omObjData *object);
void m269_BellObjInit(omObjData *object);
void m269_SmokeObjInit(omObjData *object);
void m269_BellObjMain(omObjData *object);
void m269_SmokeObjMain(omObjData *object);
void m269_CrumbObjCreate(omObjData *object);
void m269_CrumbLObjInit(omObjData *object);
void m269_CrumbRObjInit(omObjData *object);
void m269_CrumbLObjMain(omObjData *object);
void m269_CrumbRObjMain(omObjData *object);
s16 m269_EspCreate(s32 dataNum, u16 attr, u16 priority, s16 x, s16 y);
s16 m269_WinCreate(s16 x, s16 y, s16 lines);
void m269_WinKeyWait(s16 win, s16 player, s16 mode);
s16 m269_WinChoiceGet(s16 win, s16 player, s16 mode, s16 count);
void m269_WinClose(s16 win);
Vec2f m269_ScreenPosGet(f32 x, f32 y, f32 z);

void m269_Executor(void) {
    m269_ObjectSetup();
}

s32 m269_Rand(f32 arg0) {
    u8 randomByte1 = rand8();
    u8 randomByte2 = rand8();
    s32 shiftedByte1 = (randomByte1 << 8);
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;

    return scaledRandom;
}

void m269_ObjectSetup(void) {
    MapCollInit(32);
    Hu3DSprModelInit(32);
    omInitObjMan(32, 32);
    omGameSysInit();
    m269_CameraInit();
    m269_WinInit();
    m269_PlayerInfoInit();
    omAddObj(1000, 0, 0, -1, m269_MainObjInit);
    omAddObj(2000, 0, 0, -1, m269_ExitCheckObjMain);
}

void m269_CameraInit(void) {
    s32 camIndex;

    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(camIndex, 12.37f, 2000.0f, 8000.0f);
    CZoom = 3275.61f;
    CRot.x = -8.7f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 187.6f;
    Center.z = -16.89f;
}

void m269_WinInit(void) {
    HuWinInit();
}

void m269_PlayerInfoInit(void) {
    s16 i = 0;
    GameGuysSweetSurprisePadValues players = m269_playerNoTbl;

    for (; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    if (i < 4) {
        m269_playerInfo[0] = players.v[i];
    } else {
        m269_playerInfo[0] = players.v[0];
    }
    m269_playerInfo[1] = GwPlayer[m269_playerInfo[0]].pad;
    m269_playerInfo[2] = GwPlayer[m269_playerInfo[0]].chr;
    if (GwPlayer[m269_playerInfo[0]].stat & 1) {
        m269_playerInfo[3] = 1;
        m269_playerInfo[4] = GwPlayer[m269_playerInfo[0]].cpu_difficulty;
        m269_comLevel = GwCommon.unkA0;
        if (m269_comLevel <= 0) {
            m269_comLevel = 0;
        } else if (m269_comLevel >= 2) {
            m269_comLevel = 2;
        }
    } else {
        m269_playerInfo[3] = 0;
        m269_playerInfo[4] = 0;
    }
    m269_playerInfo[5] = m269_playerInfo[6] = GwPlayer[m269_playerInfo[0]].gameCoin;
}

void m269_MainObjInit(omObjData *object) {
    m269_SpotIntroInit(160, 180);
    m269_OddsInit();
    m269_hudObj = omAddObj(10, 10, 10, -1, m269_HudObjInit);
    m269_markerObj = omAddObj(20, 10, 10, -1, m269_MarkerObjInit);
    m269_gambleObj = omAddObj(30, 10, 20, -1, m269_GambleObjInit);
    m269_wanwanLObj = omAddObj(40, 10, 20, -1, m269_WanwanLObjInit);
    m269_wanwanRObj = omAddObj(50, 10, 20, -1, m269_WanwanRObjInit);
    m269_bellObj = omAddObj(60, 10, 10, -1, m269_BellObjInit);
    m269_crumbObj = omAddObj(70, 10, 10, -1, m269_CrumbObjCreate);
    object->func = m269_MainObjMain;
}

void m269_OddsInit(void) {
    GameGuysSweetSurpriseRewardTable table1 = m269_payoutChoiceTbl;
    GameGuysSweetSurpriseRewardTable table2 = m269_oddsTbl;
    s16 index;

    m269_winF = 0;
    m269_choiceNo = 0;
    if (m269_playerInfo[3] == 1) {
        m269_comChoiceNo = 0;
        if (m269_playerInfo[4] == 0) {
            m269_comChoiceNo = m269_Rand(2.0f);
        } else if (m269_playerInfo[4] == 1) {
            if (m269_Rand(4.0f) == 0) {
                m269_comChoiceNo = 1;
            }
        } else if (m269_playerInfo[4] == 2) {
            if (m269_Rand(8.0f) == 0) {
                m269_comChoiceNo = 1;
            }
        } else if (m269_playerInfo[4] == 3) {
            if (m269_Rand(16.0f) == 0) {
                m269_comChoiceNo = 1;
            }
        }
    }
    index = m269_Rand(5.0f) + 1;
    m269_sidePayoutTbl[0] = 2;
    m269_sidePayoutTbl[1] = table1.v[index];
    while (m269_sideMesTbl[0] == m269_sideMesTbl[1]) {
        m269_sideMesTbl[0] = m269_Rand(10.0f);
        m269_sideMesTbl[1] = m269_Rand(10.0f);
    }
    m269_oddsMax = 10;
    m269_oddsNum = table2.v[index];
}

char *m269_chrNameTbl[] = {
    "\x82\x6C\x82\x60\x82\x71\x82\x68\x82\x6E",                 // ＭＡＲＩＯ
    "\x82\x6B\x82\x74\x82\x68\x82\x66\x82\x68",                 // ＬＵＩＧＩ
    "\x82\x6F\x82\x64\x82\x60\x82\x62\x82\x67",                 // ＰＥＡＣＨ
    "\x82\x78\x82\x6E\x82\x72\x82\x67\x82\x68",                 // ＹＯＳＨＩ
    "\x82\x76\x82\x60\x82\x71\x82\x68\x82\x6E",                 // ＷＡＲＩＯ
    "\x82\x63\x82\x6A",                                         // ＤＫ
    "\x82\x76\x82\x60\x82\x6B\x82\x74\x82\x68\x82\x66\x82\x68", // ＷＡＬＵＩＧＩ
    "\x82\x63\x82\x60\x82\x68\x82\x72\x82\x78",                 // ＤＡＩＳＹ
}; // character names

s16 m269_introPhase = 0;  // state
s16 m269_choicePhase = 0;  // state
s16 m269_inputWait = 30; // input cooldown
s16 m269_countNum = 10; // countdown seconds
s16 m269_countTimer = 0;  // countdown tick timer
s16 m269_cakeSetPhase = 0;  // state
s16 m269_eatStartPhase = 0;  // state
s16 m269_eatStartTimer = 0;  // timer
s16 m269_bellCnt = 0;  // sound counter
s16 m269_eatTimer = 0;  // timer
s16 m269_eatPhase = 0;  // state
s16 m269_judgeWaitF = 0;
s16 m269_bannerFrame = 0;    // state
s16 m269_bannerTimer = 0;    // timer
f32 m269_choiceSprScale = 1.1f; // scale
s16 m269_choiceSprState = 0;    // state
s16 m269_choiceSprTimer = 0;
s16 m269_choicePrev = 999;  // previous choice
f32 m269_portraitScale = 0.0f; // scale
s16 m269_portraitState = 0;    // state
GameGuysSweetSurprisePos m269_portraitPosTbl[2] = { { 230, 23 }, { 230, 46 } };
s16 m269_cakeDropState = 0;      // state
f32 m269_cakeDropVel = 0.0f;   // time
f32 m269_cakeY = 600.0f; // y position
s16 m269_markerState = 0;      // state
f32 m269_markerVel = 0.0f;   // velocity
Vec m269_markerPosTbl[2] = { { -362.5f, 200.0f, -150.0f }, { 362.5f, 150.0f, -150.0f } };
s16 m269_gambleMotPrev = 999;  // previous motion
s16 m269_gambleActState = 0;    // state
s16 m269_gambleActTimer = 0;    // timer
f32 m269_gambleJumpVel = 0.0f; // velocity
f32 m269_gambleShadowScale = 1.0f; // shadow scale
s16 m269_wanwanLBobDir = -1;   // bob direction
s16 m269_wanwanLBobOfs = 0;    // bob offset
s16 m269_wanwanLMotPrev = 999;  // previous motion
f32 m269_wanwanLShadowScale = 2.0f; // shadow scale
s16 m269_wanwanLActState = 0;    // state
s16 m269_wanwanLActTimer = 0;    // timer
f32 m269_wanwanLSwaySpeed = 2.0f; // sway speed
f32 m269_wanwanLSwayAngle = 0.0f; // sway angle
f32 m269_wanwanLStartX = 0.0f; // start x
s16 m269_wanwanRBobDir = -1;   // bob direction
s16 m269_wanwanRBobOfs = 0;    // bob offset
f32 m269_wanwanRChainSpacing = 0.0f; // segment spacing
f32 m269_wanwanRBobAmp = 0.0f; // bob amplitude
s16 m269_wanwanRMotPrev = 999;  // previous motion
f32 m269_wanwanRShadowScale = 2.0f; // shadow scale
s16 m269_wanwanRActState = 0;    // state
s16 m269_wanwanRActTimer = 0;    // timer
f32 m269_wanwanRSwaySpeed = 2.0f; // sway speed
f32 m269_wanwanRSwayAngle = 0.0f; // sway angle
f32 m269_wanwanRStartX = 0.0f; // start x
s16 m269_bellState = 0;    // state
s16 m269_bellTimer = 0;    // timer
f32 m269_bellScale = 1.5f; // scale

void m269_MainObjMain(omObjData *object) {
    switch (m269_mainPhase) {
        case 0:
            WipeCreateIn(0xFF, 0x10);
            m269_mainPhase++;
            break;
        case 1:
            object->func = m269_IntroObjMain;
            m269_mainPhase++;
            break;
        case 2:
            if (++m269_mainTimer == 1) {
                GMesCreate(9);
            } else if (m269_mainTimer == 70) {
                m269_gambleMotNo = 3;
            } else if (m269_mainTimer == 80) {
                m269_bellRingReq = 1;
                HuAudFXPlay(0x538);
            } else if (GMesStatGet() == 0) {
                m269_gambleMotNo = 2;
                m269_mainPhase++;
                m269_mainTimer = 0;
            }
            break;
        case 3:
            object->func = m269_EatStartObjMain;
            m269_mainPhase++;
            break;
        case 4:
            if (++m269_mainTimer == 1) {
                m269_wanwanRActNo = m269_wanwanLActNo = 3;
                GMesCreate(0x14);
                HuAudSeqFadeOut(120);
            } else if (GMesStatGet() == 0) {
                m269_mainPhase++;
                m269_mainTimer = 0;
            }
            break;
        case 5:
            object->func = m269_JudgeObjMain;
            m269_mainPhase++;
            break;
        case 6:
            if (++m269_mainTimer == 1) {
                switch (m269_winF) {
                    case 1:
                        HuAudFXPlay(0x517);
                        HuAudSeqPlay(0x73);
                        m269_resultMesId = GMesCreate(0x16, (u16)m269_playerInfo[2]);
                        GMesTimeMaxSet(m269_resultMesId, 0x78);
                        break;
                    case 0:
                        HuAudFXPlay(0x518);
                        HuAudSeqPlay(0x71);
                        sprintf(m269_mesBuf, "%s\x81\x40\x82\x6B\x82\x6E\x82\x72\x82\x73\x81\x49",
                                m269_chrNameTbl[(u16)m269_playerInfo[2]]);
                        m269_resultMesId = GMesCreate(0x19, m269_mesBuf, 0xA0, 0x78, 1.0, 1.0, 1);
                        GMesTimeMaxSet(m269_resultMesId, 0x78);
                        break;
                }
            } else if (m269_mainTimer >= 135) {
                m269_mainPhase++;
                m269_mainTimer = 0;
            }
            break;
        case 7:
            object->func = m269_ExitStartObjMain;
            break;
    }
}

void m269_IntroObjMain(omObjData *object) {
    switch (m269_introPhase) {
        case 0:
            if (WipeStatGet() != 1) {
                m269_introPhase++;
            }
            break;
        case 1:
            m269_introPhase += m269_SpotIntroUpdate();
            break;
        case 2:
            m269_procDoneF = 0;
            m269_mesProc = omAddPrcObj(m269_RuleProc, 0x3F00, 0x800, 0);
            m269_introPhase++;
            break;
        case 3:
            if (m269_procDoneF == 1) {
                HuPrcKill(m269_mesProc);
                m269_procDoneF = 0;
                m269_introPhase++;
            }
            break;
        case 4:
            m269_choiceWinProc = omAddPrcObj(m269_ChoiceWinProc, 0x3F00, 0x800, 0);
            m269_introPhase++;
            break;
        case 5:
            object->func = m269_ChoiceObjMain;
            m269_introPhase++;
            break;
        case 6:
            m269_procDoneF = 0;
            m269_mesProc = omAddPrcObj(m269_ChoiceMesProc, 0x3F00, 0x800, 0);
            m269_introPhase++;
            break;
        case 7:
            if (m269_procDoneF == 1) {
                HuPrcKill(m269_mesProc);
                m269_procDoneF = 0;
                m269_introPhase++;
            }
            break;
        case 8:
            object->func = m269_CakeSetObjMain;
            m269_introPhase++;
            break;
        case 9:
            HuPrcKill(m269_choiceWinProc);
            object->func = m269_MainObjMain;
            break;
    }
}

void m269_RuleProc(void) {
    s16 win;
    s16 choice;
    s16 done = FALSE;

    m269_procDoneF = 0;
    win = m269_WinCreate(130, 150, 12);
    HuAudFXPlay(0x11D);
    HuWinExOpen(win, 1);
    HuWinMesSet(win, 0x2E00, -1, -1);
    m269_WinKeyWait(win, m269_playerInfo[1], m269_playerInfo[3]);
    HuWinMesSet(win, 0x2E01, -1, -1);
    while (done == FALSE) {
        choice = m269_WinChoiceGet(win, m269_playerInfo[1], m269_playerInfo[3], 1);
        switch (choice) {
            case 0:
                HuWinMesSet(win, 0x2E02, -1, -1);
                m269_WinKeyWait(win, m269_playerInfo[1], m269_playerInfo[3]);
                /* fallthrough */
            case 1:
                done = TRUE;
                break;
        }
        HuPrcVSleep();
    }
    HuWinMesSet(win, 0x2E03, -1, -1);
    m269_WinKeyWait(win, m269_playerInfo[1], m269_playerInfo[3]);
    m269_WinClose(win);
    m269_procDoneF = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m269_ChoiceWinProc(void) {
    s16 done = FALSE;
    s16 leftWin;
    s16 rightWin;

    leftWin = HuWinCreate(37, 180, 106, 34, 0, 1);
    HuWinBGColSet(leftWin, 0, 0, 255);
    HuWinBGTPLvlSet(leftWin, 150);
    HuWinMesSet(leftWin, m269_sideMesTbl[0] + 0x2E07, -1, -1);
    rightWin = HuWinCreate(177, 180, 106, 34, 0, 1);
    HuWinBGColSet(rightWin, 255, 0, 0);
    HuWinBGTPLvlSet(rightWin, 150);
    HuWinMesSet(rightWin, m269_sideMesTbl[1] + 0x2E07, -1, -1);
    HuWinDispOff(leftWin);
    HuWinDispOff(rightWin);
    while (done == FALSE) {
        if (m269_choiceF == 1) {
            switch (m269_choiceNo) {
                case 0:
                    HuWinDispOn(leftWin);
                    HuWinDispOff(rightWin);
                    break;
                case 1:
                    HuWinDispOff(leftWin);
                    HuWinDispOn(rightWin);
                    break;
            }
        } else if (m269_choiceF == 0) {
            if (m269_portraitDispF == 1) {
                done = TRUE;
            }
        }
        HuPrcVSleep();
    }
    HuWinKill(leftWin);
    HuWinKill(rightWin);
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m269_ChoiceObjMain(omObjData *object) {
    s16 input = 0;

    switch (m269_choicePhase) {
        case 0:
            GMesCreate(0x1A, 10, 0x9C, 0x38);
            m269_countNum = 10;
            m269_countTimer = 0;
            omSysPauseDisableF = 0;
            m269_choiceF = 1;
            m269_choicePhase++;
            break;
        case 1:
            if (m269_inputWait <= 0) {
                switch (m269_playerInfo[3]) {
                    case 0:
                        if (HuPadStkY[m269_playerInfo[1]] < -64 && m269_choiceNo != 1) {
                            input = 1;
                            m269_inputWait = 5;
                        }
                        if (HuPadStkY[m269_playerInfo[1]] > 64 && m269_choiceNo != 0) {
                            input = -1;
                            m269_inputWait = 5;
                        }
                        if (HuPadBtnDown[m269_playerInfo[1]] & A_BUTTON) {
                            input = 10;
                        }
                        break;
                    case 1:
                        if (m269_comChoiceNo == m269_choiceNo) {
                            input = 10;
                        } else {
                            input = 1;
                            m269_inputWait = 30;
                        }
                        break;
                }
            } else {
                m269_inputWait--;
            }
            if (m269_countTimer++ >= 30) {
                m269_countNum--;
                m269_countTimer = 0;
                GMesTimerValueSet(m269_countNum);
                if (m269_countNum == 0) {
                    input = 10;
                } else if (m269_countNum < 6) {
                    HuAudFXPlay(8);
                }
            }
            switch (input) {
                case 1:
                    HuAudFXPlay(1);
                    m269_choiceNo = 1;
                    break;
                case -1:
                    HuAudFXPlay(1);
                    m269_choiceNo = 0;
                    break;
                case 10:
                    HuAudFXPlay(3);
                    omVibrate(m269_playerInfo[0], 10, 0, 10);
                    m269_markerDropF = 1;
                    m269_choiceF = 0;
                    m269_choicePhase++;
                    break;
            }
            break;
        case 2:
            omSysPauseDisableF = 1;
            GMesTimerEnd();
            object->func = m269_IntroObjMain;
            break;
    }
}

void m269_ChoiceMesProc(void) {
    s16 win;

    win = m269_WinCreate(130, 150, 12);
    HuWinExOpen(win, 1);
    HuWinMesSet(win, 0x2E04, -1, -1);
    HuWinInsertMesSet(win, m269_choiceNo + 0x2E05, 0);
    m269_WinKeyWait(win, m269_playerInfo[1], m269_playerInfo[3]);
    m269_WinClose(win);
    m269_procDoneF = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m269_CakeSetObjMain(omObjData *object) {
    switch (m269_cakeSetPhase) {
        case 0:
            m269_gambleActF = 1;
            m269_smokeReq = 1;
            m269_cakeSetPhase++;
            break;
        case 1:
            if (m269_gambleActF == 0) {
                m269_cakeDropF = 1;
                m269_cakeSetPhase++;
            }
            break;
        case 2:
            object->func = m269_IntroObjMain;
            break;
    }
}

void m269_EatStartObjMain(omObjData *object) {
    switch (m269_eatStartPhase) {
        case 0:
            object->func = m269_EatObjMain;
            m269_eatStartPhase++;
            break;
        case 1:
            if (m269_eatStartTimer++ >= 8 && m269_eatStartTimer % 5 == 0) {
                if (m269_bellCnt == 0) {
                    HuAudFXPlay(0x539);
                }
                if (m269_bellCnt++ < 4) {
                    m269_bellRingReq = 1;
                }
            }
            if (Hu3DMotion[Hu3DData[m269_gambleObj->model[0]].motId].unk02 <=
                Hu3DData[m269_gambleObj->model[0]].motTime) {
                m269_eatStartPhase++;
            }
            break;
        case 2:
            m269_gambleMotNo = 0;
            object->func = m269_MainObjMain;
            break;
    }
}

void m269_EatObjMain(omObjData *object) {
    s16 i;

    switch (m269_eatPhase) {
        case 0:
            m269_wanwanRMotNo = m269_wanwanLMotNo = 2;
            m269_eatPhase++;
            break;
        case 1:
            if (m269_eatTimer++ >= 30) {
                if (m269_Rand(m269_oddsMax) < m269_oddsNum) {
                    if (m269_Rand(10.0f) < 6) {
                        m269_eatCntTbl[0] += 1;
                    } else {
                        m269_eatCntTbl[0] += 2;
                    }
                    if (m269_choiceNo == 0) {
                        omVibrate(m269_playerInfo[0], 10, 0, 10);
                    }
                    m269_wanwanLMotNo = 3;
                    m269_wanwanRMotNo = 2;
                } else {
                    if (m269_Rand(10.0f) < 6) {
                        m269_eatCntTbl[1] += 1;
                    } else {
                        m269_eatCntTbl[1] += 2;
                    }
                    if (m269_choiceNo == 1) {
                        omVibrate(m269_playerInfo[0], 10, 0, 10);
                    }
                    m269_crumbRReq = 1;
                    m269_wanwanLMotNo = 2;
                    m269_wanwanRMotNo = 3;
                }
                m269_eatTimer = 0;
            } else if (m269_eatTimer % 7 == 0) {
                if (m269_Rand(2.0f) == 0) {
                    m269_crumbLReq = 1;
                } else {
                    m269_crumbRReq = 1;
                }
            }
            break;
    }
    for (i = 0; i < 2; i++) {
        if (m269_eatCntTbl[i] >= 6) {
            m269_eatCntTbl[i] = 6;
        }
    }
    for (i = 0; i < 2; i++) {
        if (m269_eatCntTbl[i] == 6) {
            m269_wanwanLMotNo = 0;
            m269_wanwanRMotNo = 0;
            m269_winSide = i;
            m269_gambleMotNo = 4;
            object->func = m269_EatStartObjMain;
        }
    }
}

void m269_JudgeObjMain(omObjData *object) {
    if (m269_judgeWaitF == 0) {
        if (m269_winSide == 0) {
            m269_wanwanRMotNo = 1;
            m269_wanwanLActNo = 1;
            m269_wanwanRActNo = 2;
        } else {
            m269_wanwanLMotNo = 1;
            m269_wanwanLActNo = 2;
            m269_wanwanRActNo = 1;
        }
        if (m269_choiceNo == m269_winSide) {
            m269_winF = 1;
        } else {
            m269_winF = 0;
        }
        HuAudSeqFadeOut(30);
        object->func = m269_MainObjMain;
    }
}

void m269_ExitStartObjMain(omObjData *object) {
    GwPlayer[m269_playerInfo[0]].gameCoin = m269_playerInfo[6];
    switch (m269_winF) {
        case 1:
            GwPlayer[m269_playerInfo[0]].bonusCoin = m269_sidePayoutTbl[m269_choiceNo];
            break;
        case 0:
            GwPlayer[m269_playerInfo[0]].bonusCoin = 0;
            break;
    }
    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
    HuAudSeqFadeOut(30);
    HuAudFXAllFadeOut(30);
    object->func = m269_ExitObjMain;
}

void m269_ExitObjMain(omObjData *object) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        m269_SpotDispOff();
        GMesClose();
        HuWinAllKill();
        HuSprAnimAllKill();
        omOvlReturnEx(1);
    }
}

void m269_ExitCheckObjMain(omObjData *object) {
    if (omSysExitReq == 1) {
        object->func = m269_ExitStartObjMain;
    }
}

void m269_HudObjInit(omObjData *object) {
    m269_BackSprInit();
    m269_PanelSprInit();
    m269_PayoutSprInit();
    m269_ChoiceSprInit();
    m269_PortraitSprInit();
    m269_CakeSprInit();
    m269_CoinSprInit();
    object->func = m269_HudObjMain;
}

void m269_BackSprInit(void) {
    m269_sprTbl[0] = m269_EspCreate(0x660000, 0x4000, 1000, 160, 120);
    m269_sprTbl[1] = m269_EspCreate(0x660001, 0x4000, 1000, 160, 120);
    m269_sprTbl[2] = m269_EspCreate(0x660002, 0x4000, 1000, 160, 120);
    espDispOff(m269_sprTbl[1]);
    espDispOff(m269_sprTbl[2]);
}

void m269_PanelSprInit(void) {
    m269_sprTbl[5] = m269_EspCreate(0x660003, 0, 900, 269, 44);
}

void m269_PayoutSprInit(void) {
    s16 i = 0;
    s16 y = 33;
    s16 x = 280;
    s16 base = 10;

    for (; i < 2; i++) {
        switch (m269_sidePayoutTbl[i]) {
            case 4:
                m269_sprTbl[base + i] = m269_EspCreate(0x66000A, 0, 800, x, y + i * 22);
                break;
            case 8:
                m269_sprTbl[base + i] = m269_EspCreate(0x660006, 0, 800, x, y + i * 22);
                break;
            case 16:
                m269_sprTbl[base + i] = m269_EspCreate(0x660007, 0, 800, x, y + i * 22);
                break;
            case 32:
                m269_sprTbl[base + i] = m269_EspCreate(0x660008, 0, 800, x, y + i * 22);
                break;
            case 64:
                m269_sprTbl[base + i] = m269_EspCreate(0x660009, 0, 800, x, y + i * 22);
                break;
        }
    }
}

void m269_ChoiceSprInit(void) {
    s16 i = 15;

    m269_sprTbl[i] = m269_EspCreate(0x660004, 0, 800, 257, 33);
    m269_sprTbl[i + 1] = m269_EspCreate(0x660005, 0, 800, 257, 55);
    espDispOff(m269_sprTbl[i]);
    espDispOff(m269_sprTbl[i + 1]);
    m269_portraitDispF = 0;
}

void m269_PortraitSprInit(void) {
    s32 chr = GwPlayer[m269_playerInfo[0]].chr;
    s32 files[8] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 };
    s16 i = 20;

    m269_sprTbl[i] = m269_EspCreate(files[chr] | 0x210000, 0, 700, 0, 0);
    espDispOff(m269_sprTbl[i]);
    m269_choiceF = 0;
}

void m269_CakeSprInit(void) {
    Vec2f pos;
    void *data;
    s16 anim;
    s16 i;
    s16 base = 25;

    for (i = 0; i < 2; i++) {
        data = DataRead(0x66000B);
        anim = HuSprAnimRead(data);
        DataClose(data);
        m269_sprTbl[base + i] = HuSprGrpCreate(1, 0);
        HuSprGrpMemberSet(m269_sprTbl[base + i], 0, anim, 0);
        HuSprPriSet(m269_sprTbl[base + i], 0, 100);
        if (i == 0) {
            HuSprAttrReset(m269_sprTbl[base + i], 0, 0xFFFF);
            HuSprAttrSet(m269_sprTbl[base + i], 0, 0);
            pos = m269_ScreenPosGet(-80.0f, 600.0f, -400.0f);
            HuSprPosSet(m269_sprTbl[base + i], 0, pos.x, pos.y);
        } else if (i == 1) {
            HuSprAttrReset(m269_sprTbl[base + i], 0, 0xFFFF);
            HuSprAttrSet(m269_sprTbl[base + i], 0, 1);
            pos = m269_ScreenPosGet(80.0f, 600.0f, -400.0f);
            HuSprPosSet(m269_sprTbl[base + i], 0, pos.x, pos.y);
        }
        m269_eatCntTbl[i] = 0;
    }
}

void m269_CoinSprInit(void) {
    s16 i = 30;

    m269_sprTbl[i] = m269_EspCreate(0x21001A, 0, 600, 30, 22);
    m269_sprTbl[i + 1] = m269_EspCreate(0x21001B, 0, 600, 42, 22);
    m269_sprTbl[i + 2] = m269_EspCreate(0x31, 0, 600, 54, 22);
    m269_sprTbl[i + 3] = m269_EspCreate(0x31, 0, 600, 66, 22);
    m269_sprTbl[i + 4] = m269_EspCreate(0x31, 0, 600, 78, 22);
}

void m269_HudObjMain(omObjData *object) {
    m269_BannerUpdate();
    m269_ChoiceSprUpdate();
    m269_PortraitSprUpdate();
    m269_CakeSprUpdate();
    m269_CoinSprUpdate();
}

void m269_BannerUpdate(void) {
    s16 i = 0;

    if (m269_bannerTimer++ >= 5) {
        m269_bannerTimer = 0;
        switch (m269_bannerFrame) {
            case 0:
                espDispOn(m269_sprTbl[i + 1]);
                espDispOff(m269_sprTbl[i + 2]);
                m269_bannerFrame++;
                break;
            case 1:
                espDispOff(m269_sprTbl[i + 1]);
                espDispOn(m269_sprTbl[i + 2]);
                m269_bannerFrame++;
                break;
            case 2:
                espDispOff(m269_sprTbl[i + 1]);
                espDispOff(m269_sprTbl[i + 2]);
                m269_bannerFrame = 0;
                break;
        }
    }
}

void m269_ChoiceSprUpdate(void) {
    s16 i = 15;

    if (m269_portraitDispF == 1) {
        switch (m269_choiceSprState) {
            case 0:
                m269_choiceSprScale = 1.0f;
                m269_choiceSprTimer = 0;
                m269_choiceSprState++;
                break;
            case 1:
                espScaleSet(m269_sprTbl[i + m269_choiceNo],
                            m269_choiceSprScale, m269_choiceSprScale);
                if (m269_choiceSprScale < 1.5f) {
                    m269_choiceSprScale += 0.1f;
                } else {
                    m269_choiceSprState++;
                }
                break;
            case 2:
                espScaleSet(m269_sprTbl[i + m269_choiceNo],
                            m269_choiceSprScale, m269_choiceSprScale);
                if (m269_choiceSprScale > 1.1f) {
                    m269_choiceSprScale -= 0.1f;
                } else {
                    m269_choiceSprState--;
                }
                break;
        }
        if (m269_choiceF == 0) {
            m269_choiceSprScale = 1.5f;
            m269_choiceSprState += 2;
            espScaleSet(m269_sprTbl[i + m269_choiceNo],
                        m269_choiceSprScale, m269_choiceSprScale);
        }
        if (m269_choicePrev != m269_choiceNo) {
            switch (m269_choiceNo) {
                case 0:
                    espDispOn(m269_sprTbl[i]);
                    espDispOff(m269_sprTbl[i + 1]);
                    m269_choiceSprState = 0;
                    break;
                case 1:
                    espDispOff(m269_sprTbl[i]);
                    espDispOn(m269_sprTbl[i + 1]);
                    m269_choiceSprState = 0;
                    break;
            }
            espScaleSet(m269_sprTbl[i], 1.0f, 1.0f);
            espScaleSet(m269_sprTbl[i + 1], 1.0f, 1.0f);
            m269_choicePrev = m269_choiceNo;
        }
    }
}

void m269_PortraitSprUpdate(void) {
    s16 i = 20;

    if (m269_choiceF == 1) {
        switch (m269_portraitState) {
            case 0:
                espPosSet(m269_sprTbl[i],
                          m269_portraitPosTbl[m269_choiceNo].x,
                          m269_portraitPosTbl[m269_choiceNo].y);
                espScaleSet(m269_sprTbl[i], 0.0f, 0.0f);
                espDispOn(m269_sprTbl[i]);
                m269_portraitDispF = 1;
                m269_portraitState++;
                break;
            case 1:
                m269_portraitScale += 0.25f;
                espScaleSet(m269_sprTbl[i], m269_portraitScale,
                            m269_portraitScale);
                if (m269_portraitScale >= 1.0f) {
                    m269_portraitScale = 1.0f;
                    m269_portraitState++;
                }
                break;
            case 2:
                espPosSet(m269_sprTbl[i],
                          m269_portraitPosTbl[m269_choiceNo].x,
                          m269_portraitPosTbl[m269_choiceNo].y);
                break;
        }
    } else if (m269_choiceF == 0) {
        switch (m269_portraitState) {
            case 2:
                espPosSet(m269_sprTbl[i],
                          m269_portraitPosTbl[m269_choiceNo].x,
                          m269_portraitPosTbl[m269_choiceNo].y);
                espScaleSet(m269_sprTbl[i], 1.0f, 1.0f);
                m269_portraitState++;
                break;
            case 3:
                m269_portraitScale -= 0.25f;
                espScaleSet(m269_sprTbl[i], m269_portraitScale,
                            m269_portraitScale);
                if (m269_portraitScale <= 0.0f) {
                    m269_portraitScale = 0.0f;
                    m269_portraitState++;
                }
                break;
            case 4:
                espDispOff(m269_sprTbl[i]);
                m269_portraitState++;
                break;
        }
    }
}

void m269_CakeSprUpdate(void) {
    Vec2f pos;
    s16 i = 0;
    s16 base = 25;

    for (; i < 2; i++) {
        if (m269_eatCntTbl[i] == 6) {
            HuSprAttrReset(m269_sprTbl[base + i], 0, 0xFFFF);
            HuSprAttrSet(m269_sprTbl[base + i], 0, 0x8000);
        } else {
            HuSprAttrReset(m269_sprTbl[base + i], 0, 0x8000);
            HuSprBankSet(m269_sprTbl[base + i], 0, m269_eatCntTbl[i], 0);
            HuSprAnimModeSet(m269_sprTbl[base + i], 0, HUSPR_ANIM_MODE_BANK);
        }
    }
    if (m269_cakeDropF == 1) {
        switch (m269_cakeDropState) {
            case 0:
                m269_cakeY = 600.0f;
                m269_cakeDropVel = 0.0f;
                HuAudFXPlay(0x53C);
                m269_cakeDropState++;
                break;
            case 1:
                m269_cakeY += m269_cakeDropVel * m269_cakeDropVel * -17.5f;
                if (m269_cakeDropVel >= 1.47f) {
                    m269_cakeDropVel = 1.47f;
                } else {
                    m269_cakeDropVel += 0.22f;
                }
                if (m269_cakeY <= 0.0f) {
                    m269_cakeDropState++;
                    m269_cakeY = 0.0f;
                }
                break;
            case 2:
                m269_cakeDropF = 0;
                break;
        }
        pos = m269_ScreenPosGet(-80.0f, m269_cakeY, -400.0f);
        HuSprPosSet(m269_sprTbl[base], 0, pos.x, pos.y);
        pos = m269_ScreenPosGet(80.0f, m269_cakeY, -400.0f);
        HuSprPosSet(m269_sprTbl[base + 1], 0, pos.x, pos.y);
    }
}

void m269_CoinSprUpdate(void) {
    s16 i = 30;
    s16 x = 54;
    s16 y = 22;
    s16 *coins = &m269_playerInfo[5];
    s16 hundreds;
    s16 tens;

    if (*coins >= 999) {
        *coins = 999;
    } else if (*coins <= 0) {
        *coins = 0;
    }

    if ((hundreds = m269_playerInfo[5] / 100) == 0) {
        espDispOff(m269_sprTbl[i + 2]);
    } else {
        espPatNoSet(m269_sprTbl[i + 2], hundreds);
        espPosSet(m269_sprTbl[i + 2], x, y);
        espDispOn(m269_sprTbl[i + 2]);
        x += 12;
    }

    if ((tens = (s16)(m269_playerInfo[5] % 100) / 10) == 0 &&
        (s16)(m269_playerInfo[5] / 100) == 0) {
        espDispOff(m269_sprTbl[i + 3]);
    } else {
        espPatNoSet(m269_sprTbl[i + 3], tens);
        espPosSet(m269_sprTbl[i + 3], x, y);
        espDispOn(m269_sprTbl[i + 3]);
        x += 12;
    }

    espPatNoSet(m269_sprTbl[i + 4], m269_playerInfo[5] % 10);
    espPosSet(m269_sprTbl[i + 4], x, y);
    espDispOn(m269_sprTbl[i + 4]);
}

void m269_MarkerObjInit(omObjData *object) {
    s32 files[8] = { 0x21001C, 0x21001D, 0x21001E, 0x21001F, 0x210020, 0x210021, 0x210022, 0x210023 };

    object->model[0] = Hu3DModelRead(files[(u16)m269_playerInfo[2]], 0x2A9);
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 90.0f, 0.0f, 0.0f);
    omSetSca(object, 2.0f, 2.0f, 2.0f);
    Hu3DModelCameraSet(object->model[0], 0);
    m269_markerDropF = 0;
    object->func = m269_MarkerObjMain;
}

void m269_MarkerObjMain(omObjData *object) {
    if (m269_markerDropF == 1) {
        switch (m269_markerState) {
            case 0:
                Hu3DModelCameraSet(object->model[0], 1);
                object->trans.x = m269_markerPosTbl[m269_choiceNo].x;
                object->trans.y = 600.0f;
                object->trans.z = m269_markerPosTbl[m269_choiceNo].z;
                object->rot.y = 0.0f;
                m269_markerVel = 0.0f;
                m269_markerState++;
                break;
            case 1:
            case 2:
            case 3:
                if (m269_markerState == 1 || m269_markerState == 2) {
                    object->trans.y += m269_markerVel * m269_markerVel *
                                       (m269_markerVel >= 0.0f ? -17.5f : 17.5f);
                } else {
                    object->trans.y += m269_markerVel * m269_markerVel *
                                       (m269_markerVel >= 0.0f ? -8.75f : 8.75f);
                }
                if (m269_markerVel < 1.7f) {
                    m269_markerVel += 0.11f;
                } else {
                    m269_markerVel = 1.7f;
                }
                if (object->trans.y < m269_markerPosTbl[m269_choiceNo].y &&
                    m269_markerVel >= 0.0f) {
                    object->trans.y = m269_markerPosTbl[m269_choiceNo].y;
                    if (m269_markerState != 3) {
                        m269_markerVel = -1.47f;
                    } else {
                        m269_markerVel = 0.0f;
                    }
                    m269_markerState++;
                }
                break;
        }
        object->rot.y += 10.0f;
    }
}

void m269_GambleObjInit(omObjData *object) {
    s16 i = 0; // initialized early to match register allocation
    s32 attr = 0x2A9;
    s32 files[3] = { 0xA0063, 0xA0064, 9 };
    s32 motions[5] = { 0xA0065, 0xA006E, 0xA006C, 0xA006F, 0xA0071 };

    for (i = 0; i < 3; i++) {
        object->model[i] = Hu3DModelRead(files[i], attr);
    }
    omSetTra(object, 0.0f, 0.0f, 200.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    Hu3DModelPosSet(object->model[2], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelRotSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[2], 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 5; i++) {
        omObjMotionRead(object, i, motions[i]);
    }
    m269_gambleMotNo = 0;
    Hu3DModelCameraSet(object->model[1], 0);
    Hu3DModelObjCopy(object->model[1], "c203n30-r_hand", object->model[0], "c203_000_new-r_hand");
    m269_gambleActF = 0;
    object->func = m269_GambleObjMain;
}

void m269_GambleObjMain(omObjData *object) {
    if (m269_gambleMotPrev != m269_gambleMotNo) {
        switch (m269_gambleMotNo) {
            case 0:
            case 2:
                Hu3DMotionShiftSet(object->model[0],
                                   Hu3DData[object->motion[m269_gambleMotNo]].motId, 0, 30, 2);
                break;
            case 1:
            case 3:
            case 4:
                Hu3DMotionModelSet(object->model[0], object->motion[m269_gambleMotNo]);
                break;
        }
        m269_gambleMotPrev = m269_gambleMotNo;
    }
    if (m269_gambleActF == 1) {
        switch (m269_gambleActState) {
            case 0:
                m269_gambleMotNo = 1;
                m269_gambleJumpVel = -1.47f;
                m269_gambleActTimer = 0;
                object->trans.y = 0.0f;
                object->trans.z = 200.0f;
                m269_gambleActState++;
                break;
            case 1:
                if (m269_gambleActTimer++ >= 25) {
                    m269_gambleActState++;
                }
                break;
            case 2:
                object->trans.y += m269_gambleJumpVel * m269_gambleJumpVel *
                                   (m269_gambleJumpVel >= 0.0f ? -35.0f : 35.0f);
                if (object->trans.y <= 0.0f && m269_gambleJumpVel >= 0.0f) {
                    m269_gambleActState++;
                    object->trans.y = 0.0f;
                }
                if (m269_gambleJumpVel >= 1.47f) {
                    m269_gambleJumpVel = 1.47f;
                } else {
                    m269_gambleJumpVel += 0.11f;
                }
                object->trans.z -= 22.5f;
                break;
            case 3:
                m269_gambleMotNo = 0;
                m269_gambleActF = 0;
                break;
        }
    }
    m269_gambleShadowScale = 1.0f - object->trans.y * 0.001f;
    Hu3DModelPosSet(object->model[2], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[2], m269_gambleShadowScale, m269_gambleShadowScale,
                      m269_gambleShadowScale);
}

void m269_WanwanLObjInit(omObjData *object) {
    s16 i = 0; // initialized early to match register allocation
    s32 attr = 0x2A9;
    s32 files[3] = { 0xA00D9, 9, 0xA00E4 };
    s32 motions[4] = { 0xA00DA, 0xA00DE, 0xA00E1, 0xA00E2 };
    void *data;
    s16 anim;

    m269_wanwanMdl = object->model[0] = Hu3DModelRead(files[0], 0x2A9);
    object->model[1] = Hu3DModelRead(files[1], 0x2A9);
    omSetTra(object, -210.0f, 0.0f, -50.0f);
    omSetRot(object, 0.0f, 90.0f, 0.0f);
    omSetSca(object, 0.6f, 0.6f, 0.6f);
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 2.0f, 1.0f, 2.0f);
    for (i = 0; i < 4; i++) {
        omObjMotionRead(object, i, motions[i]);
    }
    m269_wanwanLMotNo = 0;
    data = DataRead(0xA00E5);
    anim = Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, data, 0, "c165n_4_DEF");
    DataClose(data);
    Hu3DModelRemakeStatic(object->model[0]);
    Hu3DAnimBankSet(anim, 0);
    Hu3DAnimAttrSet(anim, 1, 0);
    for (i = 0; i < 4; i++) {
        object->model[i + 2] = Hu3DModelRead(files[2], attr);
        Hu3DModelRotSet(object->model[i + 2], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(object->model[i + 2], 0.5f, 0.5f, 0.5f);
    }
    Hu3DModelPosSet(object->model[2], -350.0f, 0.0f, -150.0f);
    Hu3DModelPosSet(object->model[3], -320.0f, 0.0f, -149.0f);
    Hu3DModelPosSet(object->model[4], -290.0f, 0.0f, -148.0f);
    Hu3DModelPosSet(object->model[5], -290.0f, 0.0f, -147.0f);
    object->func = m269_WanwanLObjMain;
}

void m269_WanwanLObjMain(omObjData *object) {
    f32 delta;
    f32 angle;
    f32 amplitude;

    if (m269_wanwanLMotPrev != m269_wanwanLMotNo) {
        switch (m269_wanwanLMotNo) {
            case 0:
            case 1:
            case 2:
            case 3:
                Hu3DMotionShiftSet(object->model[0],
                                   Hu3DData[object->motion[m269_wanwanLMotNo]].motId, 0, 30, 2);
                break;
        }
        m269_wanwanLMotPrev = m269_wanwanLMotNo;
    }
    if (m269_wanwanLActNo == 0) {
        if (m269_wanwanLMotNo == 2 || m269_wanwanLMotNo == 3) {
            if (object->trans.x < -190.0f) {
                object->trans.x += 5.0f;
            } else {
                m269_wanwanLSwayAngle += m269_wanwanLSwaySpeed;
                if (m269_wanwanLSwayAngle <= -20.0f || m269_wanwanLSwayAngle >= 20.0f) {
                    m269_wanwanLSwaySpeed = -m269_wanwanLSwaySpeed;
                }
                object->rot.y = m269_wanwanLSwayAngle + 90.0f;
                if (m269_wanwanLSwayAngle > 0.0f) {
                    object->trans.x = m269_wanwanLSwayAngle / 2.0f + -190.0f;
                } else {
                    object->trans.x = -190.0f - m269_wanwanLSwayAngle / 2.0f;
                }
            }
        }
        if (m269_wanwanLMotNo == 2) {
            if (Hu3DData[object->model[0]].motTime == 4.0f) {
                HuAudFXPlay(0x53A);
            }
        } else if (m269_wanwanLMotNo == 3) {
            if (Hu3DData[object->model[0]].motTime == 8.0f) {
                HuAudFXPlay(0x53A);
            }
        }
    }
    m269_wanwanLShadowScale = 2.0f - object->trans.y * 0.002f;
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[1], m269_wanwanLShadowScale, m269_wanwanLShadowScale,
                      m269_wanwanLShadowScale);
    delta = (object->trans.x - 90.0f - Hu3DData[object->model[2]].pos.x) / 3.0f;
    Hu3DData[object->model[3]].pos.x = delta + Hu3DData[object->model[2]].pos.x;
    Hu3DData[object->model[4]].pos.x = delta + Hu3DData[object->model[3]].pos.x;
    Hu3DData[object->model[5]].pos.x = delta + Hu3DData[object->model[4]].pos.x;
    if (m269_wanwanLBobOfs >= 4) {
        m269_wanwanLBobDir = -1;
    } else if (m269_wanwanLBobOfs < -3) {
        m269_wanwanLBobDir = 1;
    }
    m269_wanwanLBobOfs += m269_wanwanLBobDir;
    amplitude = 10.0f;
    angle = delta * 3.0f * 0.45f;
    Hu3DData[object->model[3]].pos.y = sindf(sindf(angle) * 30.0f) * amplitude + m269_wanwanLBobOfs;
    Hu3DData[object->model[4]].pos.y = sindf(sindf(angle) * 60.0f) * 20.0f - m269_wanwanLBobOfs;
    Hu3DData[object->model[5]].pos.y = sindf(sindf(angle) * 90.0f) * 30.0f + m269_wanwanLBobOfs;
    if (m269_wanwanLActNo == 1) {
        switch (m269_wanwanLActState) {
            case 0:
                m269_wanwanLActTimer = 0;
                m269_wanwanLStartX = object->trans.x;
                m269_wanwanLActState++;
                break;
            case 1:
                object->trans.x = sindf(m269_wanwanLActTimer++ * 4.5f) * 100.0f +
                                  m269_wanwanLStartX;
                if (m269_wanwanLActTimer >= 21) {
                    m269_wanwanLActTimer = 0;
                    m269_wanwanLActState++;
                }
                break;
            case 2:
                object->rot.y = 90.0f - sindf(m269_wanwanLActTimer++ * 9.0f) * 90.0f;
                if (object->rot.y <= 0.0f || m269_wanwanLActTimer >= 11) {
                    m269_wanwanLActState++;
                }
                break;
            case 3:
                HuAudFXPlay(0x53E);
                m269_wanwanLMotNo = 2;
                m269_wanwanLActState++;
                break;
        }
    }
    if (m269_wanwanLActNo == 3) {
        if (object->rot.y == 90.0f) {
            m269_wanwanLActNo = 0;
        } else if (object->rot.y > 90.0f) {
            object->rot.y -= 1.0f;
            if (object->rot.y <= 90.0f) {
                object->rot.y = 90.0f;
                m269_wanwanLActNo = 0;
            }
        } else if (object->rot.y < 90.0f) {
            object->rot.y += 1.0f;
            if (object->rot.y >= 90.0f) {
                object->rot.y = 90.0f;
                m269_wanwanLActNo = 0;
            }
        }
    }
}

void m269_WanwanRObjInit(omObjData *object) {
    s16 i = 0; // initialized early to match register allocation
    s32 attr = 0x2A9;
    s32 files[4] = { 0xA00D9, 9, 0xA00E4, 0 };
    s32 motions[4] = { 0xA00DA, 0xA00DE, 0xA00E1, 0xA00E2 };
    void *data;
    s16 anim;

    object->model[0] = Hu3DModelLink(m269_wanwanMdl);
    object->model[1] = Hu3DModelRead(files[1], 0x2A9);
    omSetTra(object, 195.0f, 0.0f, -100.0f);
    omSetRot(object, 0.0f, 270.0f, 0.0f);
    omSetSca(object, 0.3f, 0.3f, 0.3f);
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 4; i++) {
        omObjMotionRead(object, i, motions[i]);
    }
    m269_wanwanRMotNo = 0;
    data = DataRead(0xA00E5);
    anim = Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, data, 0, "c165n_4_DEF");
    DataClose(data);
    Hu3DModelRemakeStatic(object->model[0]);
    Hu3DAnimBankSet(anim, 0);
    Hu3DAnimAttrSet(anim, 1, 0);
    for (i = 0; i < 4; i++) {
        object->model[i + 2] = Hu3DModelRead(files[2], attr);
    }
    for (i = 0; i < 4; i++) {
        Hu3DModelRotSet(object->model[i + 2], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(object->model[i + 2], 0.3f, 0.3f, 0.3f);
    }
    Hu3DModelPosSet(object->model[2], 350.0f, 0.0f, -150.0f);
    Hu3DModelPosSet(object->model[3], 320.0f, 0.0f, -150.0f);
    Hu3DModelPosSet(object->model[4], 290.0f, 0.0f, -150.0f);
    Hu3DModelPosSet(object->model[5], 280.0f, 70.0f, -150.0f);
    object->func = m269_WanwanRObjMain;
}

void m269_WanwanRObjMain(omObjData *object) {
    if (m269_wanwanRMotPrev != m269_wanwanRMotNo) {
        switch (m269_wanwanRMotNo) {
            case 0:
            case 1:
            case 2:
            case 3:
                Hu3DMotionShiftSet(object->model[0],
                                   Hu3DData[object->motion[m269_wanwanRMotNo]].motId, 0, 30, 2);
                break;
        }
        m269_wanwanRMotPrev = m269_wanwanRMotNo;
    }
    if (m269_wanwanRActNo == 0) {
        if (m269_wanwanRMotNo == 2 || m269_wanwanRMotNo == 3) {
            if (object->trans.x > 175.0f) {
                object->trans.x -= 5.0f;
            } else {
                m269_wanwanRSwayAngle += m269_wanwanRSwaySpeed;
                if (m269_wanwanRSwayAngle <= -20.0f || m269_wanwanRSwayAngle >= 20.0f) {
                    m269_wanwanRSwaySpeed = -m269_wanwanRSwaySpeed;
                }
                object->rot.y = m269_wanwanRSwayAngle + 270.0f;
                if (m269_wanwanRSwayAngle > 0.0f) {
                    object->trans.x = 175.0f - m269_wanwanRSwayAngle / 2.0f;
                } else {
                    object->trans.x = m269_wanwanRSwayAngle / 2.0f + 175.0f;
                }
            }
        }
        if (m269_wanwanRMotNo == 2) {
            if (Hu3DData[object->model[0]].motTime == 4.0f) {
                HuAudFXPlay(0x53B);
            }
        } else if (m269_wanwanRMotNo == 3) {
            if (Hu3DData[object->model[0]].motTime == 8.0f) {
                HuAudFXPlay(0x53B);
            }
        }
    }
    m269_wanwanRShadowScale = 1.0f - object->trans.y * 0.001f;
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[1], m269_wanwanRShadowScale, m269_wanwanRShadowScale,
                      m269_wanwanRShadowScale);
    m269_wanwanRChainSpacing = (object->trans.x + 60.0f - Hu3DData[object->model[2]].pos.x) / 3.0f;
    Hu3DData[object->model[3]].pos.x = Hu3DData[object->model[2]].pos.x + m269_wanwanRChainSpacing;
    Hu3DData[object->model[4]].pos.x = Hu3DData[object->model[3]].pos.x + m269_wanwanRChainSpacing;
    Hu3DData[object->model[5]].pos.x = Hu3DData[object->model[4]].pos.x + m269_wanwanRChainSpacing;
    if (m269_wanwanRBobOfs >= 2) {
        m269_wanwanRBobDir = -1;
    } else if (m269_wanwanRBobOfs < -1) {
        m269_wanwanRBobDir = 1;
    }
    m269_wanwanRBobOfs += m269_wanwanRBobDir;
    m269_wanwanRBobAmp = 20.0f / 3.0f;
    Hu3DData[object->model[3]].pos.y =
        sindf(sindf(m269_wanwanRChainSpacing * 3.0f * -0.225f) * 30.0f) * m269_wanwanRBobAmp +
        m269_wanwanRBobOfs;
    Hu3DData[object->model[4]].pos.y =
        m269_wanwanRBobAmp * 2.0f *
            sindf(sindf(m269_wanwanRChainSpacing * 3.0f * -0.225f) * 60.0f) -
        m269_wanwanRBobOfs;
    Hu3DData[object->model[5]].pos.y =
        m269_wanwanRBobAmp * 3.0f *
            sindf(sindf(m269_wanwanRChainSpacing * 3.0f * -0.225f) * 90.0f) +
        m269_wanwanRBobOfs;
    if (m269_wanwanRActNo == 1) {
        switch (m269_wanwanRActState) {
            case 0:
                m269_wanwanRActTimer = 0;
                m269_wanwanRStartX = object->trans.x;
                m269_wanwanRActState++;
                break;
            case 1:
                object->trans.x = m269_wanwanRStartX -
                                  sindf(m269_wanwanRActTimer++ * 4.5f) * 100.0f;
                if (m269_wanwanRActTimer >= 21) {
                    m269_wanwanRActTimer = 0;
                    m269_wanwanRActState++;
                }
                break;
            case 2:
                object->rot.y = sindf(m269_wanwanRActTimer++ * 9.0f) * 90.0f + 270.0f;
                if (object->rot.y >= 360.0f || m269_wanwanRActTimer >= 11) {
                    m269_wanwanRActState++;
                }
                break;
            case 3:
                HuAudFXPlay(0x53F);
                m269_wanwanRMotNo = 2;
                m269_wanwanRActState++;
                break;
        }
    }
    if (m269_wanwanRActNo == 3) {
        if (object->rot.y == 270.0f) {
            m269_wanwanRActNo = 0;
        } else if (object->rot.y > 270.0f) {
            object->rot.y -= 1.0f;
            if (object->rot.y <= 270.0f) {
                object->rot.y = 270.0f;
                m269_wanwanRActNo = 0;
            }
        } else if (object->rot.y < 270.0f) {
            object->rot.y += 1.0f;
            if (object->rot.y >= 270.0f) {
                object->rot.y = 270.0f;
                m269_wanwanRActNo = 0;
            }
        }
    }
}

void m269_BellObjInit(omObjData *object) {
    s16 i = 0; // initialized early to match register allocation
    s32 attr = 0x2A9;
    s32 files[2] = { 0x66000D, 9 };

    for (i = 0; i < 2; i++) {
        object->model[i] = Hu3DModelRead(files[i], attr);
    }
    omSetTra(object, 125.0f, 200.0f, -430.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 1.0f, 1.0f, 1.0f);
    omAddObj(0x64, 0xA, 0xA, -1, m269_SmokeObjInit);
    Hu3DModelCameraSet(object->model[0], 0);
    Hu3DModelCameraSet(object->model[1], 0);
    m269_bellRingReq = 0;
    object->func = m269_BellObjMain;
}

void m269_SmokeObjInit(omObjData *object) {
    object->model[0] = Hu3DModelRead(0xB0006, 0x2A9);
    omSetTra(object, 125.0f, 125.0f, -400.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 2.0f, 2.0f, 2.0f);
    omObjMotionRead(object, 0, 0xB0006);
    object->func = m269_SmokeObjMain;
    m269_smokeReq = 0;
}

void m269_BellObjMain(omObjData *object) {
    f32 shadowScale;

    if (m269_bellRingReq == 1) {
        m269_bellScale = 1.5f;
        object->scale.x = object->scale.y = object->scale.z = m269_bellScale;
        m269_bellTimer = 0;
        m269_bellRingReq = 0;
    }
    if (m269_gambleActF == 1) {
        switch (m269_bellState) {
            case 0:
                HuAudFXPlay(0x53D);
                object->scale.x = object->scale.y = object->scale.z = 0.0f;
                Hu3DModelCameraSet(object->model[0], 1);
                Hu3DModelCameraSet(object->model[1], 1);
                m269_bellState++;
                break;
            case 1:
                if (object->scale.x < 2.0f) {
                    object->scale.x = object->scale.y = object->scale.z = object->scale.z + 1.0f;
                } else {
                    m269_bellState++;
                }
                break;
            case 2:
                if (object->scale.x > 1.0f) {
                    object->scale.x = object->scale.y = object->scale.z = object->scale.z - 0.5f;
                } else {
                    object->scale.x = object->scale.y = object->scale.z = 1.0f;
                    m269_bellState++;
                }
                break;
        }
    } else if (m269_bellScale > 1.0f) {
        if ((m269_bellTimer++ & 1) == 0) {
            object->scale.x = object->scale.y = object->scale.z = 1.0f;
        } else {
            m269_bellScale -= 0.05f;
            object->scale.x = object->scale.y = object->scale.z = m269_bellScale;
        }
    } else {
        m269_bellScale = 1.0f;
        object->scale.x = object->scale.y = object->scale.z = m269_bellScale;
    }
    shadowScale = 1.0f - object->trans.y * 0.001f;
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[1], shadowScale, shadowScale, shadowScale);
}

void m269_SmokeObjMain(omObjData *object) {
    if (m269_smokeReq == 1) {
        Hu3DMotionModelSet(object->model[0], object->motion[0]);
        m269_smokeReq = 0;
    }
}

void m269_CrumbObjCreate(omObjData *object) {
    omAddObj(0xC8, 0xA, 0xA, -1, m269_CrumbLObjInit);
    omAddObj(0x12C, 0xA, 0xA, -1, m269_CrumbRObjInit);
    object->func = NULL;
}

void m269_CrumbLObjInit(omObjData *object) {
    object->model[0] = Hu3DModelRead(0x66000E, 0x2A9);
    omSetTra(object, -80.0f, 0.0f, -400.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 2.0f, 2.0f, 2.0f);
    omObjMotionRead(object, 0, 0x66000E);
    object->func = m269_CrumbLObjMain;
    m269_crumbLReq = 0;
}

void m269_CrumbRObjInit(omObjData *object) {
    object->model[0] = Hu3DModelRead(0x66000E, 0x2A9);
    omSetTra(object, 80.0f, 0.0f, -400.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 2.0f, 2.0f, 2.0f);
    omObjMotionRead(object, 0, 0x66000E);
    object->func = m269_CrumbRObjMain;
    m269_crumbRReq = 0;
}

void m269_CrumbLObjMain(omObjData *object) {
    if (m269_crumbLReq == 1) {
        if (m269_Rand(3.0f) == 0) {
            object->scale.x = object->scale.y = object->scale.z = 1.5f;
        } else {
            object->scale.x = object->scale.y = object->scale.z = 1.0f;
        }
        Hu3DMotionModelSet(object->model[0], object->motion[0]);
        m269_crumbLReq = 0;
    }
}

void m269_CrumbRObjMain(omObjData *object) {
    if (m269_crumbRReq == 1) {
        if (m269_Rand(3.0f) == 0) {
            object->scale.x = object->scale.y = object->scale.z = 1.25f;
        } else {
            object->scale.x = object->scale.y = object->scale.z = 1.0f;
        }
        Hu3DMotionModelSet(object->model[0], object->motion[0]);
        m269_crumbRReq = 0;
    }
}

s16 m269_EspCreate(s32 dataNum, u16 attr, u16 priority, s16 x, s16 y) {
    s16 sprite = espEntry(HuSprAnimDataRead(dataNum), 0, 0);

    espAttrSet(sprite, attr | 8);
    espPriSet(sprite, priority);
    espPosSet(sprite, x, y);
    return sprite;
}

s16 m269_WinCreate(s16 x, s16 y, s16 lines) {
    s16 win;

    win = HuWinExCreateStyled(x, y, lines);
    HuWinAttrSet(win, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
    HuWinExPriSet(win, 1);
    HuWinMesSpeedSet(win, 0);
    HuWinHomeClear(win);
    return win;
}

void m269_WinKeyWait(s16 win, s16 player, s16 mode) {
    s16 i;

    HuWinComKeyReset();
    while (HuWinStatGet(win) != 0) {
        switch (mode) {
            case 0:
                if (HuPadBtnDown[player] & A_BUTTON) {
                    HuWinComKeySet(-0x8000, -0x8000, -0x8000, -0x8000);
                }
                break;
            case 1:
                for (i = 0; i < 10; i++) {
                    HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000,
                                    m269_comKeyWaitTbl[m269_comLevel]);
                }
                while (HuWinStatGet(win) != 0) {
                    HuPrcVSleep();
                }
                break;
        }
        HuPrcVSleep();
    }
    HuWinComKeyReset();
}

s16 m269_WinChoiceGet(s16 win, s16 player, s16 mode, s16 count) {
    s16 keys[4] = { 0, 0, 0, 0 };
    s16 players[4] = { 1, 2, 4, 8 };
    s16 i;

    switch (mode) {
        case 0:
            keys[player] = -1;
            HuWinAttrSet(win, HUWIN_ATTR_COMKEY, HUWIN_ATTR_NONE);
            HuWinActivePlayerSet(win, players[player]);
            HuWinComKeySet(keys[0], keys[1], keys[2], keys[3]);
            break;
        case 1:
            for (i = 0; i < count; i++) {
                HuWinComKeyWait(0x400, 0x400, 0x400, 0x400,
                                m269_comKeyWaitTbl[m269_comLevel]);
            }
            HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000,
                            m269_comKeyWaitTbl[m269_comLevel]);
            break;
    }
    return HuWinChoiceGet(win, 0, 1);
}

void m269_WinClose(s16 win) {
    HuWinHomeClear(win);
    HuWinExClose(win, 1);
    HuWinExCleanup(win);
}

Vec2f m269_ScreenPosGet(f32 x, f32 y, f32 z) {
    Vec pos;
    Vec2f screenPos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    Hu3D3Dto2D(0, &pos, &screenPos);
    return screenPos;
}
