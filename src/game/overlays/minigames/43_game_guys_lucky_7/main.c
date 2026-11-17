#include "common.h"
#include "game_guys_lucky_7.h"

typedef struct GameGuysLucky7SpriteDef {
    /* 0x00 */ s32 dataNum;
    /* 0x04 */ s32 priority;
    /* 0x08 */ s32 x;
    /* 0x0C */ s32 y;
} GameGuysLucky7SpriteDef;

typedef struct GameGuysLucky7SpritePos {
    /* 0x00 */ s32 dataNum;
    /* 0x04 */ s32 x;
    /* 0x08 */ s32 y;
} GameGuysLucky7SpritePos;

typedef struct GameGuysLucky7PadValues {
    /* 0x00 */ s16 v[4]; // one entry per controller port
} GameGuysLucky7PadValues;

typedef struct GameGuysLucky7HudWork { // 0x14 bytes
    /* 0x00 */ u16 playerInfo[7];
    /* 0x0E */ u16 sprites[3];
} GameGuysLucky7HudWork;

s16 m267_winPosTbl[9][3] = {
    { 190, 150, 13 },
    { 220, 165, 15 },
    { 195, 150, 15 },
    { 170, 140, 15 },
    { 190, 115, 13 },
    { 155, 115, 14 },
    { 130, 105, 14 },
    { 100, 100, 14 },
    { 50, 190, 14 },
}; // window x, y, lines
s16 m267_comKeyWaitTbl[3] = { 5, 25, 60 }; // COM key wait frames, indexed by CPU difficulty
u16 m267_mainPhase = 0;                // main state
u16 m267_mainTimer = 0;                // main state timer

char m267_mesBuf[0x100] BSS;
s16 m267_resultMesId BSS;
Process *m267_ruleProc BSS;
Process *m267_choiceProc BSS;
// [0] player index, [1] pad, [2] chr, [3] cpu flag, [4] cpu difficulty, [5] coins, [6] coins
GameGuysLucky7HudWork m267_hudWork BSS;
extern u16 m267_playerInfo[7]; // m267_hudWork.playerInfo
extern u16 m267_backSprTbl[3]; // m267_hudWork.sprites
u16 m267_stepSprTbl[7] BSS;
f32 m267_stepScaleTbl[7] BSS;
u16 m267_coinSprTbl[5] BSS;
u16 m267_gambleEffReq BSS;
u16 m267_gambleMoveF BSS;
f32 m267_gamblePosX BSS;
f32 m267_gamblePosY BSS;
f32 m267_gamblePosZ BSS;
f32 m267_gambleRotY BSS;
u16 m267_gambleMotNo BSS;
u16 m267_gambleMotSpeed BSS;
s16 m267_gambleMotFrame BSS;
u16 m267_playerEffReq BSS;
u16 m267_playerMoveF BSS;
u16 m267_playerMotNo BSS; // player motion
f32 m267_playerFallF BSS;
f32 m267_playerPosX BSS;
f32 m267_playerPosY BSS;
f32 m267_playerRotY BSS;
u16 m267_saiState BSS;
f32 m267_saiPosX BSS;
f32 m267_saiPosY BSS;
f32 m267_saiPosZ BSS;
u16 m267_saiNumState BSS;
u16 m267_saiNo BSS;
u16 m267_hitEffReq BSS;
u16 m267_bustEffReq BSS;
u16 m267_hitEff2Req BSS;
u16 m267_turnNo BSS;
u16 m267_gambleStep BSS;
u16 m267_playerStep BSS;
u16 m267_gambleDoneF BSS;
u16 m267_winF BSS;
u16 m267_procResult BSS;
u8 m267_procResultPad[0x18] BSS; /* Unreferenced. */
s16 m267_confettiMdlTbl[52] BSS;  // spark models
s16 m267_gambleActNo BSS;
s16 m267_comLevel BSS;
s16 m267_confettiTimer BSS;
extern const GameGuysLucky7PadValues m267_comKeyTbl; // COM keys
extern const GameGuysLucky7PadValues m267_activePlayerTbl; // active players
extern s32 omCharModelNoTbl[][6];

void m267_ObjectSetup(void);
void m267_LightInit(void);
void m267_CameraInit(void);
void m267_WinInit(void);
void m267_PlayerInfoInit(void);
void m267_MainObjInit(omObjData *object);
void m267_MainObjMain(omObjData *object);
void m267_IntroObjMain(omObjData *object);
void m267_RuleProc(void);
void m267_GambleEnterObjMain(omObjData *object);
void m267_TurnObjMain(omObjData *object);
void m267_RollObjMain(omObjData *object);
void m267_MoveObjMain(omObjData *object);
void m267_GambleChoiceProc(void);
void m267_PlayerChoiceProc(void);
void m267_ResultObjMain(omObjData *object);
void m267_GambleBustObjMain(omObjData *object);
void m267_PlayerBustObjMain(omObjData *object);
void m267_ExitStartObjMain(omObjData *object);
void m267_ExitObjMain(omObjData *object);
void m267_ExitCheckObjMain(omObjData *object);
void m267_TurnInit(void);
void m267_HudObjInit(omObjData *object);
void m267_BackSprInit(void);
void m267_StepSprInit(void);
void m267_CoinSprInit(void);
void m267_HudObjMain(omObjData *object);
void m267_BannerUpdate(void);
void m267_StepSprUpdate(void);
void m267_CoinSprUpdate(void);
void m267_PlayerObjInit(omObjData *object);
void m267_PlayerObjMain(omObjData *object);
void m267_GambleObjInit(omObjData *object);
void m267_GambleObjMain(omObjData *object);
void m267_HitEffObjInit(omObjData *object);
void m267_HitEffObjMain(omObjData *object);
void m267_BustEffObjInit(omObjData *object);
void m267_BustEffObjMain(omObjData *object);
void m267_HitEff2ObjInit(omObjData *object);
void m267_HitEff2ObjMain(omObjData *object);
void m267_SaiObjInit(omObjData *object);
void m267_SaiObjMain(omObjData *object);
void m267_SaiNumObjInit(omObjData *object);
void m267_SaiNumObjMain(omObjData *object);
void m267_ConfettiCreate(void);
void m267_ConfettiObjMain(omObjData *object);
void m267_ConfettiEmit(s16 model);
void m267_ConfettiParticleUpdate(s16 model);
s16 m267_WinCreate(s16 x, s16 y, s16 lines);
void m267_WinClose(s16 win);
void m267_WinKeyWait(s16 win, s16 player, s16 mode);
s16 m267_WinChoiceGet(s16 win, s16 player, s16 mode, s16 count);
s16 m267_WinChoiceGetEx(s16 win, s16 player, s16 mode, s16 count);

void m267_Executor(void) {
    m267_ObjectSetup();
}

s32 m267_Rand(f32 arg0) {
    u8 randomByte1 = rand8();
    u8 randomByte2 = rand8();
    s32 shiftedByte1 = (randomByte1 << 8);
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;

    return scaledRandom;
}

void m267_ObjectSetup(void) {
    MapCollInit(32);
    Hu3DSprModelInit(32);
    omInitObjMan(32, 32);
    omGameSysInit();
    m267_LightInit();
    m267_CameraInit();
    m267_WinInit();
    m267_PlayerInfoInit();
    omAddObj(1000, 0, 0, -1, m267_MainObjInit);
    omAddObj(2000, 0, 0, -1, m267_ExitCheckObjMain);
}

void m267_LightInit(void) {
}

void m267_CameraInit(void) {
    s32 camIndex;

    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(camIndex, 6.57f, 2000.0f, 8500.0f);
    CZoom = 8075.0f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 350.0f;
    Center.z = 0.0f;
}

void m267_WinInit(void) {
    HuWinInit();
}

void m267_PlayerInfoInit(void) {
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    switch (i) {
        case 0:
            m267_playerInfo[0] = 0;
            break;
        case 1:
            m267_playerInfo[0] = 1;
            break;
        case 2:
            m267_playerInfo[0] = 2;
            break;
        case 3:
            m267_playerInfo[0] = 3;
            break;
        default:
            m267_playerInfo[0] = 0;
            break;
    }
    m267_playerInfo[1] = GwPlayer[m267_playerInfo[0]].pad;
    m267_playerInfo[2] = GwPlayer[m267_playerInfo[0]].chr;
    if (GwPlayer[m267_playerInfo[0]].stat & 1) {
        m267_playerInfo[3] = 1;
        m267_playerInfo[4] = GwPlayer[m267_playerInfo[0]].cpu_difficulty;
        m267_comLevel = GwCommon.unkA0;
        if (m267_comLevel <= 0) {
            m267_comLevel = 0;
        } else if (m267_comLevel >= 2) {
            m267_comLevel = 2;
        }
    } else {
        m267_playerInfo[3] = 0;
        m267_playerInfo[4] = 0;
    }
    m267_playerInfo[5] = m267_playerInfo[6] =
        GwPlayer[m267_playerInfo[0]].gameCoin;
    if (m267_playerInfo[5] >= 999) {
        m267_playerInfo[5] = 999;
        m267_playerInfo[6] = 999;
    } else if (m267_playerInfo[5] == 0) {
        m267_playerInfo[5] = 0;
        m267_playerInfo[6] = 0;
    }
}

void m267_MainObjInit(omObjData *object) {
    m267_TurnInit();
    m267_SpotIntroInit(160, 194);
    omAddObj(10, 10, 10, -1, m267_HudObjInit);
    omAddObj(20, 10, 20, -1, m267_PlayerObjInit);
    omAddObj(30, 10, 20, -1, m267_GambleObjInit);
    omAddObj(40, 10, 10, -1, m267_SaiObjInit);
    omAddObj(41, 10, 10, -1, m267_HitEffObjInit);
    omAddObj(42, 10, 10, -1, m267_BustEffObjInit);
    omAddObj(42, 10, 10, -1, m267_HitEff2ObjInit);
    omAddObj(50, 10, 10, -1, m267_SaiNumObjInit);
    object->func = m267_MainObjMain;
}

char *m267_chrNameTbl[] = {
    "\x82\x6C\x82\x60\x82\x71\x82\x68\x82\x6E",                 // ＭＡＲＩＯ
    "\x82\x6B\x82\x74\x82\x68\x82\x66\x82\x68",                 // ＬＵＩＧＩ
    "\x82\x6F\x82\x64\x82\x60\x82\x62\x82\x67",                 // ＰＥＡＣＨ
    "\x82\x78\x82\x6E\x82\x72\x82\x67\x82\x68",                 // ＹＯＳＨＩ
    "\x82\x76\x82\x60\x82\x71\x82\x68\x82\x6E",                 // ＷＡＲＩＯ
    "\x82\x63\x82\x6A",                                         // ＤＫ
    "\x82\x76\x82\x60\x82\x6B\x82\x74\x82\x68\x82\x66\x82\x68", // ＷＡＬＵＩＧＩ
    "\x82\x63\x82\x60\x82\x68\x82\x72\x82\x78",                 // ＤＡＩＳＹ
}; // character names

s16 m267_introPhase = 0; // state
s16 m267_introTimer = 0; // timer
u16 m267_gambleEnterPhase = 0; // state
u16 m267_spotDoneF = 0;
f32 m267_gambleEnterVel = 0.0f;
u16 m267_gambleEnterWait = 0;
u16 m267_turnPhase = 0; // state
u16 m267_turnTimer = 0;
u16 m267_rollPhase = 0;  // state
u16 m267_rollTimer = 0;  // timer
u16 m267_countTimer = 0;  // countdown tick timer
u16 m267_countNum = 10; // countdown seconds
u16 m267_moveCnt = 0;
u16 m267_moveWait = 0;
u16 m267_resultPhase = 0; // state
u16 m267_gambleBustPhase = 0; // state
f32 m267_gambleBustVel = 0.0f;
u16 m267_playerBustPhase = 1; // state
f32 m267_playerBustVel = 0.0f;
u16 m267_playerBustTimer = 0;
u16 m267_bannerTimer = 0;   // timer
u16 m267_bannerFrame = 0;   // state
u16 m267_playerMotPrev = 999; // previous player motion
u16 m267_playerJumpPhase = 0;   // state
u16 m267_playerJumpTimer = 0;   // timer
f32 m267_playerJumpVel = 0.0f;
u16 m267_playerJumpStepNo = 0;
f32 m267_playerStepUnused = 250.0f; /* Unreferenced. */
Vec m267_playerStepPosTbl[7] = {
    { 75.0f, 0.0f, 150.0f },
    { 125.0f, 0.0f, 50.0f },
    { 175.0f, 0.0f, -50.0f },
    { 225.0f, 0.0f, -150.0f },
    { 275.0f, 0.0f, -250.0f },
    { 325.0f, 0.0f, -350.0f },
    { 375.0f, 0.0f, -450.0f },
};
f32 m267_playerStepPosTblEnd[2] = { 425.0f, 0.0f }; // read as m267_playerStepPosTbl[7].x
u16 m267_gambleMotPrev = 999;                 // previous motion
u16 m267_gambleJumpPhase = 0;                   // state
u16 m267_gambleJumpTimer = 0;                   // timer
f32 m267_gambleJumpVel = 0.0f;
u16 m267_gambleJumpStepNo = 0;
f32 m267_gambleStepUnused = 300.0f; /* Unreferenced. */
Vec m267_gambleStepPosTbl[7] = {
    { 100.0f, -100.0f, 200.0f },
    { 150.0f, -100.0f, 100.0f },
    { 200.0f, -100.0f, 0.0f },
    { 250.0f, -100.0f, -100.0f },
    { 300.0f, -100.0f, -200.0f },
    { 350.0f, -100.0f, -300.0f },
    { 375.0f, -100.0f, -450.0f },
};
f32 m267_gambleStepPosTblEnd[2] = { 425.0f, -100.0f }; // read as m267_gambleStepPosTbl[7].x
u16 m267_saiPhase = 0;
f32 m267_saiRotX = 0.0f;
f32 m267_saiRotY = 0.0f;
f32 m267_saiScaleX = 0.0f;
f32 m267_saiScaleY = 0.0f;
f32 m267_saiTimer = 0.0f;
u16 m267_saiNumPhase = 0;
f32 m267_saiNumY = 0.0f;
f32 m267_saiNumScale = 0.0f;
u16 m267_saiNumTimer = 0;
s32 m267_confettiMdlFileTbl[] = { 0xB002B, 0xB002C, 0xB002D, 0xB002E }; // spark model files

void m267_MainObjMain(omObjData *object) {
    switch (m267_mainPhase) {
        case 0:
            WipeCreateIn(WIPE_TYPE_PREV, 0x10);
            m267_mainPhase++;
            break;
        case 1:
            object->func = m267_IntroObjMain;
            m267_mainPhase++;
            break;
        case 2:
            if (m267_mainTimer++ == 0) {
                GMesCreate(9);
                m267_mainTimer = 1;
            } else if (GMesStatGet() == 0) {
                m267_mainTimer = 0;
                m267_mainPhase++;
            }
            break;
        case 3:
            object->func = m267_TurnObjMain;
            m267_mainPhase++;
            break;
        case 4:
            if (m267_mainTimer++ == 0) {
                GMesCreate(0x14);
                HuAudSeqFadeOut(120);
            } else if (m267_mainTimer == 15) {
                if (m267_playerStep >= 8) {
                    object->func = m267_PlayerBustObjMain;
                }
            } else if (GMesStatGet() == 0) {
                m267_mainTimer = 0;
                m267_mainPhase++;
            }
            break;
        case 5:
            object->func = m267_ResultObjMain;
            m267_mainPhase++;
            break;
        case 6:
            if (m267_mainTimer++ == 0) {
                switch (m267_winF) {
                    case 1:
                        HuAudSeqPlay(0x73);
                        m267_resultMesId = GMesCreate(0x16, m267_playerInfo[2]);
                        GMesTimeMaxSet(m267_resultMesId, 0x78);
                        break;
                    case 0:
                        HuAudSeqPlay(0x71);
                        sprintf(m267_mesBuf,
                                "%s\x81\x40\x82\x6B\x82\x6E\x82\x72\x82\x73\x81\x49",
                                m267_chrNameTbl[m267_playerInfo[2]]);
                        m267_resultMesId =
                            GMesCreate(0x19, m267_mesBuf, 0xA0, 0x78, 1.0, 1.0, 1);
                        GMesTimeMaxSet(m267_resultMesId, 0x78);
                        break;
                }
            } else if (m267_mainTimer >= 135) {
                m267_mainPhase++;
            }
            break;
        case 7:
            object->func = m267_ExitStartObjMain;
            break;
        case 999:
            break;
        case 1000:
            m267_SpotBeamUpdate(0x44);
            break;
    }
}

void m267_IntroObjMain(omObjData *object) {
    switch (m267_introPhase) {
        case 0:
            m267_introPhase = m267_SpotIntroUpdate();
            if (m267_introTimer++ >= 115) {
                m267_introPhase++;
            }
            break;
        case 1:
            m267_procResult = 0;
            m267_ruleProc = omAddPrcObj(m267_RuleProc, 0x3F00, 0x800, 0);
            m267_introPhase++;
            break;
        case 2:
            if (m267_procResult != 0) {
                HuPrcKill(m267_ruleProc);
                m267_procResult = 0;
                m267_introPhase++;
            }
            break;
        case 3:
            object->func = m267_GambleEnterObjMain;
            m267_introPhase++;
            break;
        case 4:
            object->func = m267_MainObjMain;
            break;
        case 999:
            break;
    }
}

void m267_RuleProc(void) {
    s16 win;
    s16 choice;
    s16 done = FALSE;

    win = m267_WinCreate(m267_winPosTbl[0][0], m267_winPosTbl[0][1],
                                          m267_winPosTbl[0][2]);
    HuAudFXPlay(0x11D);
    HuWinExOpen(win, 1);
    HuWinMesSet(win, 0x2B00, -1, -1);
    m267_WinKeyWait(win, m267_playerInfo[1], m267_playerInfo[3]);
    HuWinMesSet(win, 0x2B01, -1, -1);
    while (done == FALSE) {
        choice = m267_WinChoiceGet(win, m267_playerInfo[1], m267_playerInfo[3], 1);
        if (choice == 0) {
            HuWinMesSet(win, 0x2B02, -1, -1);
            m267_WinKeyWait(win, m267_playerInfo[1], m267_playerInfo[3]);
            done = TRUE;
        } else if (choice == 1) {
            done = TRUE;
        }
        HuPrcVSleep();
    }
    HuWinMesSet(win, 0x2B03, -1, -1);
    m267_WinKeyWait(win, m267_playerInfo[1], m267_playerInfo[3]);
    m267_WinClose(win);
    m267_procResult = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m267_GambleEnterObjMain(omObjData *object) {
    f32 speedSq;

    if (m267_spotDoneF == 0) {
        m267_spotDoneF = m267_SpotIntroUpdate();
    }
    switch (m267_gambleEnterPhase) {
        case 0:
            m267_gambleEnterVel = -1.7f;
            m267_gambleMotNo = 7;
            m267_playerMotNo = 1;
            m267_playerPosX = 1000.0f;
            m267_playerRotY = 270.0f;
            m267_gambleEnterPhase++;
            break;
        case 1:
            if (m267_playerPosX > 350.0f) {
                m267_playerPosX -= 10.0f;
            } else if (m267_playerRotY < 360.0f) {
                m267_playerRotY += 10.0f;
            } else {
                m267_playerMotNo = 0;
                m267_playerRotY = 360.0f;
            }
            if (m267_gambleMotFrame >= 25 && m267_gambleMotSpeed != 0.0f) {
                m267_gambleEnterVel += 0.11f;
                if (m267_gambleEnterVel > 1.7f) {
                    m267_gambleEnterVel = 1.7f;
                }
                speedSq = m267_gambleEnterVel * m267_gambleEnterVel;
                if (m267_gambleEnterVel >= 0.0f) {
                    m267_gamblePosY += speedSq * -17.5f;
                } else {
                    m267_gamblePosY += speedSq * 26.0f;
                }
            } else if (m267_gambleMotSpeed == 0.0f) {
                if (m267_gambleEnterWait++ >= 30) {
                    m267_gambleMotSpeed = 1;
                }
            }
            if (m267_gambleMotFrame == 30) {
                m267_gambleMotSpeed = 0;
                m267_gambleEnterVel = 0.0f;
                m267_gamblePosX = 450.0f;
                m267_gamblePosY = 800.0f;
                m267_gamblePosZ = -100.0f;
                m267_gambleRotY = 360.0f;
            }
            if (m267_gamblePosY <= 0.0f) {
                m267_playerRotY = 360.0f;
                m267_gambleMotNo = 0;
                m267_gamblePosY = 0.0f;
                m267_gambleEffReq = 2;
                m267_gambleEnterPhase++;
            }
            break;
        case 2:
            object->func = m267_IntroObjMain;
            break;
    }
}

void m267_TurnObjMain(omObjData *object) {
    switch (m267_turnPhase) {
        case 0:
            object->func = m267_RollObjMain;
            m267_turnPhase++;
            break;
        case 1:
            m267_procResult = 0;
            m267_choiceProc = omAddPrcObj(m267_GambleChoiceProc, 0x3F00, 0x800, 0);
            m267_turnPhase++;
            break;
        case 2:
            if (m267_procResult != 0) {
                HuPrcKill(m267_choiceProc);
                if (m267_procResult == 2) {
                    m267_turnNo = 0;
                    object->func = m267_RollObjMain;
                }
                m267_turnPhase++;
                m267_procResult = 0;
            }
            break;
        case 3:
            m267_procResult = 0;
            m267_turnNo = 1;
            m267_choiceProc = omAddPrcObj(m267_PlayerChoiceProc, 0x3F00, 0x800, 0);
            m267_turnPhase++;
            break;
        case 4:
            if (m267_procResult != 0 && m267_turnTimer++ >= 15) {
                HuPrcKill(m267_choiceProc);
                if (m267_procResult == 1) {
                    if (m267_gambleStep >= 8) {
                        m267_gambleMotNo = m267_gambleActNo = 5;
                    }
                    object->func = m267_RollObjMain;
                } else if (m267_procResult == 2) {
                    object->func = m267_MainObjMain;
                }
            }
            break;
    }
}

void m267_RollObjMain(omObjData *object) {
    switch (m267_rollPhase) {
        case 0:
            m267_saiState = 1;
            if (m267_turnNo == 1) {
                GMesCreate(0x1A, 10, 0x9C, 0x38);
            }
            m267_rollPhase++;
            break;
        case 1:
            if (m267_rollTimer++ >= 10) {
                m267_rollTimer = 0;
                m267_rollPhase++;
            }
            break;
        case 2:
            if (m267_turnNo == 0) {
                if (m267_rollTimer++ >= 30) {
                    m267_gambleMotNo = 2;
                    m267_rollTimer = 0;
                    m267_rollPhase++;
                }
            } else if (m267_turnNo == 1) {
                if (m267_countTimer++ >= 30) {
                    m267_countNum--;
                    m267_countTimer = 0;
                }
                GMesTimerValueSet(m267_countNum);
                switch (m267_playerInfo[3]) {
                    case 0:
                        if ((HuPadBtnDown[m267_playerInfo[1]] & A_BUTTON) ||
                            m267_countNum == 0) {
                            m267_playerMotNo = 3;
                            m267_rollTimer = 0;
                            m267_rollPhase++;
                        }
                        break;
                    case 1:
                        if (m267_rollTimer++ >= 60) {
                            m267_playerMotNo = 3;
                            m267_rollTimer = 0;
                            m267_rollPhase++;
                        }
                        break;
                }
            }
            break;
        case 3:
            if (m267_rollTimer++ >= 31) {
                m267_rollTimer = 0;
                m267_rollPhase++;
            } else if (m267_rollTimer == 5) {
                m267_saiNumState = m267_hitEff2Req = m267_hitEffReq = 1;
                m267_saiState = 2;
                m267_saiNo = m267_Rand(6.0f);
                if (m267_turnNo == 1) {
                    GMesTimerEnd();
                }
            }
            break;
        case 4:
            m267_countTimer = 0;
            m267_countNum = 10;
            m267_rollPhase = 0;
            m267_rollTimer = 0;
            object->func = m267_MoveObjMain;
            break;
        case 999:
            if (HuPadBtnDown[0] & L_CBUTTONS) {
                m267_rollPhase = 0;
            }
            break;
    }
}

void m267_MoveObjMain(omObjData *object) {
    if (m267_turnNo == 0) {
        if (m267_moveCnt != m267_saiNo + 1 && m267_gambleMoveF == 0 &&
            m267_gambleStep < 8) {
            m267_gambleMoveF = 1;
            m267_moveCnt++;
        } else if ((m267_moveCnt == m267_saiNo + 1 ||
                    m267_gambleStep == 8) &&
                   m267_gambleMoveF == 0) {
            if (m267_gambleStep >= 8) {
                m267_moveCnt = 0;
                m267_turnNo = 1;
                m267_moveWait = 0;
                object->func = m267_GambleBustObjMain;
            } else if (m267_moveWait++ >= 6) {
                if (m267_gambleRotY <= 360.0f) {
                    m267_gambleMotNo = 0;
                    m267_gambleRotY += 10.0f;
                } else {
                    m267_moveCnt = 0;
                    m267_gambleRotY = 360.0f;
                    m267_turnNo = 1;
                    m267_moveWait = 0;
                    if (m267_gambleDoneF == 0) {
                        object->func = m267_RollObjMain;
                    } else if (m267_gambleDoneF == 1) {
                        object->func = m267_TurnObjMain;
                    }
                }
            }
        }
    } else if (m267_turnNo == 1) {
        if (m267_moveCnt != m267_saiNo + 1 && m267_playerMoveF == 0 &&
            m267_playerStep < 8) {
            m267_playerMoveF = 1;
            m267_moveCnt++;
        } else if ((m267_moveCnt == m267_saiNo + 1 ||
                    m267_playerStep == 8) &&
                   m267_playerMoveF == 0) {
            if (m267_playerStep >= 8) {
                CharFXPlay(0x286, m267_playerInfo[2]);
                m267_playerMotNo = 7;
                object->func = m267_MainObjMain;
            } else if (m267_moveWait++ >= 6) {
                if (m267_playerRotY <= 360.0f) {
                    m267_playerMotNo = 1;
                    m267_playerRotY += 10.0f;
                } else {
                    if (m267_playerStep == 7) {
                        omVibrate(m267_playerInfo[0], 30, 0, 30);
                    }
                    m267_playerMotNo = 0;
                    m267_moveWait = 0;
                    m267_moveCnt = 0;
                    m267_playerRotY = 360.0f;
                    m267_turnNo = 0;
                    if (m267_gambleDoneF == 0) {
                        m267_gambleDoneF = 1;
                        object->func = m267_TurnObjMain;
                    } else if (m267_gambleDoneF == 1) {
                        object->func = m267_MainObjMain;
                    }
                }
            }
        }
    }
}

void m267_GambleChoiceProc(void) {
    s16 win;
    s16 success = FALSE;

    if (m267_playerStep >= m267_gambleStep) {
        success = TRUE;
    } else {
        switch (m267_gambleStep) {
            case 1:
                if (m267_Rand(100.0f) < 100) {
                    success = TRUE;
                }
                break;
            case 2:
                if (m267_Rand(100.0f) < 100) {
                    success = TRUE;
                }
                break;
            case 3:
                if (m267_Rand(100.0f) < 100) {
                    success = TRUE;
                }
                break;
            case 4:
                if (m267_Rand(100.0f) < 30) {
                    success = TRUE;
                }
                break;
            case 5:
                if (m267_Rand(100.0f) < 10) {
                    success = TRUE;
                }
                break;
        }
    }
    win = m267_WinCreate(m267_winPosTbl[m267_gambleStep][0],
                                          m267_winPosTbl[m267_gambleStep][1],
                                          m267_winPosTbl[m267_gambleStep][2]);
    HuAudFXPlay(0x11D);
    HuWinExOpen(win, 1);
    if (success == TRUE) {
        HuWinMesSet(win, 0x2B04, -1, -1);
    } else {
        HuWinMesSet(win, 0x2B05, -1, -1);
    }
    m267_WinKeyWait(win, m267_playerInfo[1], m267_playerInfo[3]);
    m267_WinClose(win);
    if (success == FALSE) {
        m267_procResult = 1;
    } else if (success == TRUE) {
        m267_procResult = 2;
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m267_PlayerChoiceProc(void) {
    s16 cursor = TRUE;
    s16 cpuBonus[4] = { 30, 20, 10, 0 };
    s16 win;
    s16 choice;
    s16 mode = 0;

    if (m267_playerInfo[3] == 1) {
        if (m267_playerStep < m267_gambleStep && m267_gambleStep < 8) {
            cursor = FALSE;
        } else {
            switch (m267_playerStep) {
                case 1:
                    if (m267_Rand(100.0f) < cpuBonus[m267_playerInfo[4]] + 100) {
                        cursor = FALSE;
                    }
                    break;
                case 2:
                    if (m267_Rand(100.0f) < cpuBonus[m267_playerInfo[4]] + 100) {
                        cursor = FALSE;
                    }
                    break;
                case 3:
                    if (m267_Rand(100.0f) < cpuBonus[m267_playerInfo[4]] + 100) {
                        cursor = FALSE;
                    }
                    break;
                case 4:
                    if (m267_Rand(100.0f) < cpuBonus[m267_playerInfo[4]] + 30) {
                        cursor = FALSE;
                    }
                    break;
                case 5:
                    if (m267_Rand(100.0f) < cpuBonus[m267_playerInfo[4]] + 10) {
                        cursor = FALSE;
                    }
                    break;
                case 6:
                    if (m267_Rand(100.0f) < cpuBonus[m267_playerInfo[4]]) {
                        cursor = FALSE;
                    }
                    break;
            }
        }
    }
    win = m267_WinCreate(m267_winPosTbl[m267_gambleStep][0],
                                          m267_winPosTbl[m267_gambleStep][1],
                                          m267_winPosTbl[m267_gambleStep][2]);
    HuAudFXPlay(0x11D);
    HuWinExOpen(win, 1);
    if (m267_gambleStep <= m267_playerStep || m267_gambleStep >= 8) {
        if (m267_playerStep == 1) {
            HuWinMesSet(win, 0x2B09, -1, -1);
            m267_WinKeyWait(win, m267_playerInfo[1], m267_playerInfo[3]);
            HuWinMesSet(win, 0x2B0A, -1, -1);
        } else {
            HuWinMesSet(win, 0x2B07, -1, -1);
            HuWinInsertMesSet(win, m267_playerStep + 0x2B09, 0);
            m267_WinKeyWait(win, m267_playerInfo[1], m267_playerInfo[3]);
            HuWinMesSet(win, 0x2B08, -1, -1);
        }
        mode = 1;
        cursor = (cursor != TRUE);
    } else {
        HuWinMesSet(win, 0x2B06, -1, -1);
    }
    while (m267_procResult == 0) {
        if (mode == 0) {
            choice = m267_WinChoiceGet(win, m267_playerInfo[1],
                                                     m267_playerInfo[3], cursor);
        } else {
            choice = m267_WinChoiceGetEx(win, m267_playerInfo[1],
                                                     m267_playerInfo[3], cursor);
        }
        switch (choice) {
            case 0:
                m267_procResult = 1;
                m267_WinClose(win);
                break;
            case 1:
                m267_procResult = 2;
                m267_WinClose(win);
                break;
        }
        HuPrcVSleep();
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m267_ResultObjMain(omObjData *object) {
    switch (m267_resultPhase) {
        case 0:
            if (m267_playerStep < 8) {
                if (m267_playerStep >= m267_gambleStep) {
                    m267_winF = 1;
                }
                if (m267_gambleStep >= 8) {
                    m267_winF = 1;
                }
            } else {
                m267_winF = 0;
            }
            m267_resultPhase++;
            break;
        case 1:
            if (m267_winF == 1) {
                if (m267_playerStep == 7) {
                    HuAudFXPlay(0x522);
                } else {
                    HuAudFXPlay(0x535);
                }
            } else {
                HuAudFXPlay(0x518);
            }
            m267_resultPhase++;
            break;
        case 2:
            if (m267_playerStep == 7) {
                m267_SpotBeamInit();
                m267_resultPhase++;
            } else {
                m267_resultPhase += 2;
            }
        case 3:
            m267_resultPhase += m267_SpotBeamUpdate(0x44);
            break;
        case 4:
            if (m267_winF == 1) {
                if (m267_playerStep == 7) {
                    m267_ConfettiCreate();
                }
                m267_playerMotNo = 5;
                m267_gambleMotNo = 4;
            } else if (m267_winF == 0) {
                m267_gambleMotNo = 3;
                if (m267_playerStep < 8) {
                    m267_playerMotNo = 6;
                }
            }
            m267_resultPhase++;
            break;
        case 5:
            object->func = m267_MainObjMain;
            break;
    }
}

void m267_GambleBustObjMain(omObjData *object) {
    f32 speedSq;

    switch (m267_gambleBustPhase) {
        case 0:
            m267_gambleBustVel = 0.0f;
            HuAudFXPlay(0x51D);
            m267_gambleBustPhase = 2;
            break;
        case 1:
            break;
        case 2:
            m267_gambleBustVel += 0.11f;
            if (m267_gambleBustVel >= 1.7f) {
                m267_gambleBustVel = 1.7f;
            }
            m267_gamblePosY += m267_gambleBustVel * m267_gambleBustVel * -17.75f;
            if (m267_gamblePosY <= 0.0f) {
                HuAudFXPlay(0x520);
                m267_gambleEffReq = 1;
                m267_gambleBustPhase++;
                m267_gambleBustVel = -1.47f;
            }
            break;
        case 3:
            m267_gambleBustVel += 0.22f;
            if (m267_gambleBustVel >= 1.7f) {
                m267_gambleBustVel = 1.7f;
            }
            speedSq = m267_gambleBustVel * m267_gambleBustVel;
            if (m267_gambleBustVel >= 0.0f) {
                m267_gamblePosY += speedSq * -17.5f;
            } else {
                m267_gamblePosY += speedSq * 17.5f;
            }
            if (m267_gambleRotY < 360.0f) {
                m267_gambleRotY += 10.0f;
            } else {
                m267_gambleRotY = 360.0f;
            }
            if (m267_gamblePosY <= 0.0f && m267_gambleBustVel >= 0.0f) {
                m267_gambleActNo = 4;
                m267_gamblePosY = 0.0f;
                m267_gambleBustPhase++;
            }
            break;
        case 4:
            if (m267_gambleMotNo == 0) {
                object->func = m267_TurnObjMain;
            }
            break;
    }
}

void m267_PlayerBustObjMain(omObjData *object) {
    f32 speedSq;

    switch (m267_playerBustPhase) {
        case 0:
            m267_playerMotNo = 7;
            HuAudFXPlay(0x51D);
            m267_playerBustVel = 0.0f;
            m267_playerBustPhase++;
            break;
        case 1:
            m267_playerFallF = 1.0f;
            m267_playerMotNo = 8;
            m267_playerBustPhase++;
            break;
        case 2:
            m267_playerBustVel += 0.11f;
            if (m267_playerBustVel >= 1.7f) {
                m267_playerBustVel = 1.7f;
            }
            m267_playerPosY += m267_playerBustVel * m267_playerBustVel * -17.5f;
            if (m267_playerPosY < 0.0f) {
                HuAudFXPlay(0x520);
                m267_playerPosY = 0.0f;
                m267_playerEffReq = 1;
                m267_playerBustPhase++;
                m267_playerBustVel = -1.47f;
                omVibrate(m267_playerInfo[0], 2, 2, 20);
            }
            break;
        case 3:
            m267_playerBustVel += 0.15f;
            if (m267_playerBustVel >= 1.7f) {
                m267_playerBustVel = 1.7f;
            }
            speedSq = m267_playerBustVel * m267_playerBustVel;
            if (m267_playerBustVel >= 0.0f) {
                m267_playerPosY += speedSq * -17.5f;
            } else {
                m267_playerPosY += speedSq * 17.5f;
            }
            if (m267_playerRotY < 360.0f) {
                m267_playerRotY += 10.0f;
            } else {
                m267_playerRotY = 360.0f;
            }
            if (m267_playerPosY <= 0.0f && m267_playerBustVel >= 0.0f) {
                HuAudFXPlay(0x51E);
                CharFXPlay(0x31, m267_playerInfo[2]);
                m267_bustEffReq = 1;
                m267_playerPosY = 0.0f;
                m267_playerFallF = 0.0f;
                m267_playerMotNo = 9;
                object->func = m267_MainObjMain;
                m267_playerBustTimer = 0;
                m267_playerBustPhase = 0;
            }
            break;
    }
}

void m267_ExitStartObjMain(omObjData *object) {
    GwPlayer[m267_playerInfo[0]].gameCoin = m267_playerInfo[6];
    if (m267_winF == 0) {
        GwPlayer[m267_playerInfo[0]].bonusCoin = 0;
    } else if (m267_winF == 1) {
        if (m267_playerStep == 7) {
            GwPlayer[m267_playerInfo[0]].bonusCoin = 10;
        } else {
            GwPlayer[m267_playerInfo[0]].bonusCoin = 2;
        }
    }
    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
    HuAudSeqFadeOut(30);
    HuAudFXAllFadeOut(30);
    object->func = m267_ExitObjMain;
}

void m267_ExitObjMain(omObjData *object) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        m267_SpotDispOff();
        GMesClose();
        HuWinAllKill();
        HuSprAnimAllKill();
        omOvlReturnEx(1);
    }
}

void m267_ExitCheckObjMain(omObjData *object) {
    if (omSysExitReq == 1) {
        object->func = m267_ExitStartObjMain;
    }
}

void m267_TurnInit(void) {
    m267_turnNo = 0;
    m267_gambleStep = 0;
    m267_playerStep = 0;
    m267_gambleDoneF = 0;
    m267_winF = 0;
}

void m267_HudObjInit(omObjData *object) {
    m267_BackSprInit();
    m267_StepSprInit();
    m267_CoinSprInit();
    object->func = m267_HudObjMain;
}

void m267_BackSprInit(void) {
    GameGuysLucky7SpriteDef defs[3] = {
        { 0x640000, 1000, 160, 120 },
        { 0x640001, 900, 160, 57 },
        { 0x640002, 900, 160, 57 },
    };
    u16 i;

    for (i = 0; i < 3; i++) {
        m267_backSprTbl[i] = espEntry(HuSprAnimDataRead(defs[i].dataNum), 0, 0);
        espAttrSet(m267_backSprTbl[i], 0x4000);
        espPriSet(m267_backSprTbl[i], (u16)defs[i].priority);
        espPosSet(m267_backSprTbl[i], defs[i].x, defs[i].y);
    }
    espDispOff(m267_backSprTbl[1]);
    espDispOff(m267_backSprTbl[2]);
}

void m267_StepSprInit(void) {
    GameGuysLucky7SpritePos defs[7] = {
        { 0x640003, 225, 202 },
        { 0x640004, 199, 202 },
        { 0x640005, 173, 202 },
        { 0x640006, 147, 202 },
        { 0x640007, 121, 202 },
        { 0x640008, 95, 202 },
        { 0x640009, 68, 200 },
    };
    u16 i;

    for (i = 0; i < 7; i++) {
        m267_stepSprTbl[i] = espEntry(HuSprAnimDataRead(defs[i].dataNum), 0, 0);
        if (i != 0) {
            espAttrSet(m267_stepSprTbl[i], 0x4000);
        }
        espPriSet(m267_stepSprTbl[i], 700);
        espPosSet(m267_stepSprTbl[i], defs[i].x, defs[i].y);
        espScaleSet(m267_stepSprTbl[i], 0.5f, 0.5f);
    }
    for (i = 0; i < 7; i++) {
        m267_stepScaleTbl[i] = 0.5f;
    }
}

void m267_CoinSprInit(void) {
    GameGuysLucky7SpritePos defs[5] = {
        { 0x21001A, 30, 22 },
        { 0x21001B, 42, 22 },
        { 0x31, 54, 22 },
        { 0x31, 66, 22 },
        { 0x31, 78, 22 },
    };
    u16 i;

    for (i = 0; i < 5; i++) {
        m267_coinSprTbl[i] = espEntry(HuSprAnimDataRead(defs[i].dataNum), 0, 0);
        espPriSet(m267_coinSprTbl[i], 700);
        espPosSet(m267_coinSprTbl[i], defs[i].x, defs[i].y);
    }
}

void m267_HudObjMain(omObjData *object) {
    m267_BannerUpdate();
    m267_StepSprUpdate();
    m267_CoinSprUpdate();
}

void m267_BannerUpdate(void) {
    if (m267_bannerTimer >= 10) {
        switch (m267_bannerFrame) {
            case 0:
                espDispOn(m267_backSprTbl[1]);
                espDispOff(m267_backSprTbl[2]);
                m267_bannerFrame++;
                break;
            case 1:
                espDispOff(m267_backSprTbl[1]);
                espDispOn(m267_backSprTbl[2]);
                m267_bannerFrame++;
                break;
            case 2:
                espDispOff(m267_backSprTbl[1]);
                espDispOff(m267_backSprTbl[2]);
                m267_bannerFrame = 0;
                break;
        }
        m267_bannerTimer = 0;
    } else {
        m267_bannerTimer++;
    }
}

void m267_StepSprUpdate(void) {
    u16 i;

    for (i = 0; i < 7; i++) {
        if (i == m267_playerStep - 1) {
            if (m267_stepScaleTbl[m267_playerStep - 1] < 1.0f) {
                m267_stepScaleTbl[m267_playerStep - 1] += 0.125f;
            } else {
                m267_stepScaleTbl[m267_playerStep - 1] = 1.0f;
            }
        } else if (m267_stepScaleTbl[i] > 0.5f) {
            m267_stepScaleTbl[i] -= 0.1f;
        } else {
            m267_stepScaleTbl[i] = 0.5f;
        }
    }
    for (i = 0; i < 7; i++) {
        espScaleSet(m267_stepSprTbl[i], m267_stepScaleTbl[i], m267_stepScaleTbl[i]);
    }
}

void m267_CoinSprUpdate(void) {
    s16 x;
    u16 hundreds;
    u16 tens;
    u16 *coins;

    x = 0;
    coins = &m267_playerInfo[5];
    if (*coins >= 999) {
        *coins = 999;
    } else if (*coins == 0) {
        *coins = 0;
    }

    if ((hundreds = m267_playerInfo[5] / 100) == 0) {
        espDispOff(m267_coinSprTbl[2]);
    } else {
        espPatNoSet(m267_coinSprTbl[2], hundreds);
        espPosSet(m267_coinSprTbl[2], 54, 22);
        espDispOn(m267_coinSprTbl[2]);
        x += 12;
    }

    if ((tens = (u16)(m267_playerInfo[5] % 100) / 10) == 0 &&
        (u16)(m267_playerInfo[5] / 100) == 0) {
        espDispOff(m267_coinSprTbl[3]);
    } else {
        espPatNoSet(m267_coinSprTbl[3], tens);
        espPosSet(m267_coinSprTbl[3], x + 54, 22);
        espDispOn(m267_coinSprTbl[3]);
        x += 12;
    }

    espPatNoSet(m267_coinSprTbl[4], m267_playerInfo[5] % 10);
    espPosSet(m267_coinSprTbl[4], x + 54, 22);
    espDispOn(m267_coinSprTbl[4]);
}

void m267_PlayerObjInit(omObjData *object) {
    s32 attr = 0x2A9;
    s32 chr = m267_playerInfo[2];
    s32 bodyFile = omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][1];
    s32 files[4] = { bodyFile, 9, 0x82, 0x83 };
    s32 motions[10] = {
        CharMotionDataNumGet(chr, 0x00),
        CharMotionDataNumGet(chr, 0x01),
        CharMotionDataNumGet(chr, 0x04),
        CharMotionDataNumGet(chr, 0x2B),
        CharMotionDataNumGet(chr, 0x1F),
        CharMotionDataNumGet(chr, 0x2F),
        CharMotionDataNumGet(chr, 0x36),
        CharMotionDataNumGet(chr, 0x29),
        CharMotionDataNumGet(chr, 0x0F),
        CharMotionDataNumGet(chr, 0x15),
    };
    u16 i;

    object->model[0] = Hu3DModelRead(files[0], attr);
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 10; i++) {
        omObjMotionRead(object, i, motions[i]);
    }
    Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[0]].motId, 0, 4, 2);
    for (i = 1; i < 4; i++) {
        object->model[i] = Hu3DModelRead(files[i], attr);
    }
    Hu3DModelPosSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(object->model[1], 15.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[2], 1.0f, 1.0f, 1.0f);
    Hu3DModelPosSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(object->model[2], 15.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[2], 1.0f, 1.0f, 1.0f);
    m267_playerEffReq = 0;
    m267_playerMoveF = 0;
    m267_playerMotNo = 0;
    m267_playerPosX = 1340.0f;
    m267_playerPosY = 0.0f;
    m267_playerRotY = 270.0f;
    object->func = m267_PlayerObjMain;
}

void m267_PlayerObjMain(omObjData *object) {
    f32 speedSq;
    f32 scale;
    u16 i;

    if (m267_playerMotPrev != m267_playerMotNo) {
        switch (m267_playerMotNo) {
            case 4:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[m267_playerMotNo]].motId, 0,
                                   10, 0);
                break;
            case 0:
            case 1:
            case 9:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[m267_playerMotNo]].motId, 0,
                                   4, 2);
                break;
            case 2:
            case 3:
                Hu3DMotionModelSet(object->model[0], object->motion[m267_playerMotNo]);
                break;
            case 5:
                Hu3DMotionModelSet(object->model[0], object->motion[5]);
                HuAudCharVoicePlay(omCharModelNoTbl[m267_playerInfo[2]][0] | 0x2F);
                break;
            case 6:
                Hu3DMotionModelSet(object->model[0], object->motion[6]);
                HuAudCharVoicePlay(omCharModelNoTbl[m267_playerInfo[2]][0] | 0x36);
                break;
            case 7:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[m267_playerMotNo]].motId, 0,
                                   10, 2);
                break;
            case 8:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[m267_playerMotNo]].motId, 0,
                                   30, 1);
                break;
        }
        m267_playerMotPrev = m267_playerMotNo;
    }
    if (m267_playerMoveF == 1) {
        switch (m267_playerJumpPhase) {
            case 0:
                m267_playerJumpVel = -1.47f;
                if (m267_playerRotY != 270.0f) {
                    m267_playerMotNo = 1;
                    m267_playerJumpPhase++;
                } else {
                    m267_playerJumpPhase += 2;
                }
                break;
            case 1:
                m267_playerRotY -= 10.0f;
                if (m267_playerRotY <= 270.0f) {
                    m267_playerRotY = 270.0f;
                    m267_playerJumpPhase++;
                }
                break;
            case 2:
                if (m267_playerJumpTimer++ == 0) {
                    m267_playerMotNo = 2;
                    CharFXPlay(0x3A, m267_playerInfo[2]);
                } else if (m267_playerJumpTimer >= 5) {
                    m267_playerJumpTimer = 0;
                    m267_playerJumpPhase++;
                }
                break;
            case 3:
                if (m267_playerJumpVel >= 1.7f) {
                    m267_playerJumpVel = 1.7f;
                }
                if (m267_playerJumpStepNo == 7 && m267_playerJumpVel >= 0.5f) {
                    m267_playerMotNo = 7;
                }
                m267_playerPosX -= 7.14f;
                speedSq = m267_playerJumpVel * m267_playerJumpVel;
                m267_playerPosY +=
                    (m267_playerJumpVel >= 0.0f) ? speedSq * -35.0f : speedSq * 35.0f;
                if (m267_playerPosY < m267_playerStepPosTbl[m267_playerJumpStepNo].x &&
                    m267_playerJumpVel >= 0.0f) {
                    m267_playerPosY = m267_playerStepPosTbl[m267_playerJumpStepNo].x;
                    m267_playerStep++;
                    if (m267_playerJumpStepNo != 7) {
                        m267_playerMotNo = 4;
                        HuAudFXPlay(m267_playerStep + 0x523);
                    }
                    m267_playerJumpPhase += 2;
                }
                m267_playerJumpVel += 0.22f;
                break;
            case 4:
                if (m267_playerJumpTimer++ != 0) {
                    m267_playerJumpTimer = 0;
                    m267_playerJumpPhase++;
                }
                break;
            case 5:
                m267_playerJumpVel = 0.0f;
                m267_playerJumpPhase = 0;
                m267_playerJumpTimer = 0;
                m267_playerJumpStepNo++;
                m267_playerMoveF = 0;
                break;
        }
    }
    omSetTra(object, m267_playerPosX, m267_playerPosY, 0.0f);
    omSetRot(object, 0.0f, m267_playerRotY, 0.0f);
    if (m267_playerEffReq == 1) {
        for (i = 2; i < 4; i++) {
            Hu3DMotionTimeSet(object->model[i], 0.0f);
        }
        m267_playerEffReq = 0;
    }
    scale = (1340.0f - m267_playerPosY) * 0.00074626866f;
    if (m267_playerPosX >= 300.0f || m267_playerPosX <= -400.0f) {
        for (i = 1; i < 4; i++) {
            Hu3DModelPosSet(object->model[i], m267_playerPosX, 0.0f, 10.0f);
        }
        Hu3DModelScaleSet(object->model[1], scale, scale, scale);
    } else {
        Hu3DModelPosSet(object->model[1], m267_playerPosX, 5000.0f, 0.0f);
    }
}

void m267_GambleObjInit(omObjData *object) {
    s32 attr = 0x2A9;
    s32 files[4] = { 0xA0063, 9, 0x82, 0x83 };
    s32 motions[10] = {
        0xA0065,
        0xA006A,
        0xA0069,
        0xA0067,
        0xA006B,
        0xA0073,
        0xA0074,
        0xA006E,
        0xA006D,
        0xA0070,
    };
    u16 i;

    object->model[0] = Hu3DModelRead(files[0], attr);
    omSetTra(object, 0.0f, 190.0f, 5100.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 10; i++) {
        omObjMotionRead(object, i, motions[i]);
    }
    for (i = 1; i < 4; i++) {
        object->model[i] = Hu3DModelRead(files[i], attr);
    }
    Hu3DModelPosSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(object->model[1], 15.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[2], 1.0f, 1.0f, 1.0f);
    Hu3DModelPosSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(object->model[2], 15.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[2], 1.0f, 1.0f, 1.0f);
    m267_gambleEffReq = 0;
    m267_gambleMoveF = 0;
    m267_gamblePosX = 0.0f;
    m267_gamblePosY = 190.0f;
    m267_gamblePosZ = 5100.0f;
    m267_gambleRotY = 0.0f;
    m267_gambleMotNo = 0;
    m267_gambleMotSpeed = 1;
    object->func = m267_GambleObjMain;
}

void m267_GambleObjMain(omObjData *object) {
    f32 speedSq;
    f32 scale;
    u16 i;

    if (m267_gambleMotPrev != m267_gambleMotNo) {
        switch (m267_gambleMotNo) {
            case 9:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[m267_gambleMotNo]].motId, 0,
                                   10, 0);
                break;
            case 0:
            case 3:
            case 5:
            case 8:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[m267_gambleMotNo]].motId, 0,
                                   4, 2);
                break;
            case 1:
            case 2:
            case 4:
            case 7:
                Hu3DMotionModelSet(object->model[0], object->motion[m267_gambleMotNo]);
                break;
            case 6:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[m267_gambleMotNo]].motId, 0,
                                   15, 0);
                break;
        }
        m267_gambleMotPrev = m267_gambleMotNo;
    }
    if (m267_gambleActNo == 3) {
        if (m267_gambleMotNo == 6 && Hu3DData[object->model[0]].motTime >= 30.0f) {
            Hu3DMotionTimeSet(object->model[0], 15.0f);
            m267_gambleMotSpeed = 0;
            Hu3DMotionSpeedSet(object->model[0], 0.0f);
            m267_gambleActNo = 0;
        }
    }
    if (m267_gambleActNo == 4) {
        m267_gambleMotSpeed = 1;
        Hu3DMotionSpeedSet(object->model[0], 1.0f);
        if (Hu3DData[object->model[0]].motTime == Hu3DMotion[Hu3DData[object->model[0]].motId].unk02) {
            m267_gambleMotNo = 0;
            m267_gambleActNo = 0;
        }
    }
    if (m267_gambleMoveF == 1) {
        switch (m267_gambleJumpPhase) {
            case 0:
                m267_gambleJumpVel = -1.47f;
                if (m267_gambleRotY != 270.0f) {
                    m267_gambleMotNo = 0;
                    m267_gambleJumpPhase++;
                } else {
                    m267_gambleJumpPhase += 2;
                }
                break;
            case 1:
                m267_gambleRotY -= 10.0f;
                if (m267_gambleRotY <= 270.0f) {
                    m267_gambleRotY = 270.0f;
                    m267_gambleMotNo = 0;
                    m267_gambleJumpPhase++;
                }
                break;
            case 2:
                if (m267_gambleJumpTimer >= 4) {
                    m267_gambleJumpTimer = 0;
                    m267_gambleJumpPhase++;
                    HuAudFXPlay(0x519);
                    m267_gambleMotNo = 3;
                } else {
                    m267_gambleJumpTimer++;
                }
                break;
            case 3:
                if (m267_gambleJumpVel >= 1.7f) {
                    m267_gambleJumpVel = 1.7f;
                }
                if (m267_gambleJumpStepNo == 7 && m267_gambleJumpVel >= 0.8f) {
                    m267_gambleStep++;
                    m267_gambleJumpPhase += 2;
                    m267_gambleActNo = 3;
                    m267_gambleMotNo = 6;
                    break;
                }
                if (m267_gambleJumpStepNo == 0) {
                    m267_gamblePosX -= 11.5f;
                } else if (m267_gambleJumpStepNo == 7) {
                    m267_gamblePosX -= 17.0f;
                    m267_gambleRotY += 5.0f;
                } else {
                    m267_gamblePosX -= 7.14f;
                }
                speedSq = m267_gambleJumpVel * m267_gambleJumpVel;
                m267_gamblePosY +=
                    (m267_gambleJumpVel >= 0.0f) ? speedSq * -35.0f : speedSq * 35.0f;
                if (m267_gamblePosY < m267_gambleStepPosTbl[m267_gambleJumpStepNo].x &&
                    m267_gambleJumpVel >= 0.0f) {
                    m267_gamblePosY = m267_gambleStepPosTbl[m267_gambleJumpStepNo].x;
                    HuAudFXPlay(0x51A);
                    if (m267_gambleStep != 7) {
                        m267_gambleMotNo = 9;
                    }
                    m267_gambleStep++;
                    m267_gambleJumpPhase += 2;
                }
                m267_gambleJumpVel += 0.22f;
                break;
            case 4:
                if (m267_gambleJumpTimer >= 3) {
                    m267_gambleJumpTimer = 0;
                    m267_gambleJumpPhase++;
                    m267_gambleMotNo = 0;
                } else {
                    m267_gambleJumpTimer++;
                }
                break;
            case 5:
                m267_gambleJumpVel = 0.0f;
                m267_gambleJumpPhase = 0;
                m267_gambleJumpTimer = 0;
                m267_gambleJumpStepNo++;
                m267_gambleMoveF = 0;
                break;
        }
    }
    omSetTra(object, m267_gamblePosX, m267_gamblePosY, m267_gamblePosZ);
    omSetRot(object, 0.0f, m267_gambleRotY, 0.0f);
    Hu3DMotionSpeedSet(object->model[0], m267_gambleMotSpeed);
    if (m267_gambleEffReq == 1) {
        for (i = 2; i < 4; i++) {
            Hu3DMotionTimeSet(object->model[i], 0.0f);
        }
        m267_gambleEffReq = 0;
    }
    if (m267_gambleEffReq == 2) {
        Hu3DMotionTimeSet(object->model[2], 0.0f);
        m267_gambleEffReq = 0;
        Hu3DModelPosSet(object->model[2], m267_gamblePosX, m267_gamblePosY, -100.0f);
    }
    scale = (1340.0f - m267_gamblePosY) * 0.00074626866f;
    if (m267_gamblePosX >= 350.0f || m267_gamblePosX <= -400.0f) {
        for (i = 1; i < 4; i++) {
            Hu3DModelPosSet(object->model[i], m267_gamblePosX, 0.0f, -100.0f);
        }
        Hu3DModelScaleSet(object->model[1], scale, scale, scale);
    } else {
        Hu3DModelPosSet(object->model[1], m267_gamblePosX, 5000.0f, -100.0f);
    }
    m267_gambleMotFrame = (s16)Hu3DData[object->model[0]].motTime / 2;
    if (m267_gambleActNo == 5) {
        if (object->trans.z < 900.0f) {
            m267_gamblePosZ = object->trans.z += 100.0f;
        } else if (object->trans.x < 0.0f) {
            m267_gambleRotY = object->rot.y = 90.0f;
            m267_gamblePosX = object->trans.x += 15.0f;
        } else if (object->rot.y > 0.0f) {
            m267_gambleRotY = object->rot.y -= 10.0f;
            if (object->rot.y <= 0.0f) {
                m267_gambleRotY = object->rot.y = 0.0f;
                m267_gambleActNo = 0;
                m267_gambleMotNo = 0;
            }
        }
    }
}

void m267_HitEffObjInit(omObjData *object) {
    object->model[0] = Hu3DModelRead(0x83, 0x2A9);
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    omObjMotionRead(object, 0, 0x83);
    Hu3DMotionModelSet(object->model[0], object->motion[0]);
    m267_hitEffReq = 0;
    object->func = m267_HitEffObjMain;
}

void m267_HitEffObjMain(omObjData *object) {
    if (m267_hitEffReq == 1) {
        Hu3DMotionModelSet(object->model[0], object->motion[0]);
        m267_hitEffReq = 0;
    }
    omSetTra(object, m267_saiPosX, m267_saiPosY - 50.0f,
             m267_saiPosZ + 120.0f);
}

void m267_BustEffObjInit(omObjData *object) {
    object->model[0] = Hu3DModelRead(0xB002F, 0x2A9);
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    omObjMotionRead(object, 0, 0xB002F);
    Hu3DMotionModelSet(object->model[0], object->motion[0]);
    Hu3DModelCameraSet(object->model[0], 0);
    m267_bustEffReq = 0;
    object->func = m267_BustEffObjMain;
}

void m267_BustEffObjMain(omObjData *object) {
    if (m267_bustEffReq == 1) {
        Hu3DModelCameraSet(object->model[0], 1);
        Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[0]].motId, 0, 10, 2);
        m267_bustEffReq = 0;
        if (m267_playerStep >= 8) {
            omSetTra(object, m267_playerPosX, 125.0f, 0.0f);
        } else if (m267_gambleStep >= 8) {
            omSetTra(object, m267_gamblePosX, 125.0f, -100.0f);
        }
    }
}

void m267_HitEff2ObjInit(omObjData *object) {
    object->model[0] = Hu3DModelRead(0xB0006, 0x2A9);
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 2.0f, 2.0f, 2.0f);
    omObjMotionRead(object, 0, 0xB0006);
    Hu3DMotionModelSet(object->model[0], object->motion[0]);
    m267_hitEff2Req = 0;
    object->func = m267_HitEff2ObjMain;
}

void m267_HitEff2ObjMain(omObjData *object) {
    if (m267_hitEff2Req == 1) {
        Hu3DMotionModelSet(object->model[0], object->motion[0]);
        m267_hitEff2Req = 0;
    }
    omSetTra(object, m267_saiPosX, m267_saiPosY - 50.0f,
             m267_saiPosZ + 120.0f);
}

void m267_SaiObjInit(omObjData *object) {
    object->model[0] = Hu3DModelRead(0x64000B, 0x2A9);
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    m267_saiState = 0;
    m267_saiPosX = 0.0f;
    m267_saiPosY = 0.0f;
    m267_saiPosZ = 0.0f;
    object->func = m267_SaiObjMain;
}

void m267_SaiObjMain(omObjData *object) {
    if (m267_saiState == 1) {
        switch (m267_saiPhase) {
            case 0:
                m267_saiRotX = m267_Rand(4.0f) * 90;
                m267_saiRotY = m267_Rand(4.0f) * 90;
                m267_saiScaleX = 0.0f;
                m267_saiScaleY = 0.0f;
                if (m267_turnNo == 0) {
                    m267_saiPosX = m267_gamblePosX;
                    m267_saiPosY = m267_gamblePosY + 250.0f;
                    m267_saiPosZ = -100.0f;
                } else if (m267_turnNo == 1) {
                    m267_saiPosX = m267_playerPosX;
                    m267_saiPosY = m267_playerPosY + 250.0f;
                    m267_saiPosZ = 0.0f;
                }
                m267_saiPhase++;
                break;
            case 1:
                m267_saiScaleX =
                    (m267_saiScaleX < 0.99f) ? m267_saiScaleX + 0.4f : 1.0f;
                m267_saiScaleY =
                    (m267_saiScaleY < 0.99f) ? m267_saiScaleY + 0.8f : 1.0f;
                if (m267_saiTimer++ >= 10.0f) {
                    m267_saiTimer = 0.0f;
                    m267_saiRotX = 0.0f;
                    m267_saiRotY = 0.0f;
                    HuAudFXPlay(0x51B);
                    m267_saiPhase++;
                }
                break;
            case 2:
                m267_saiRotX += 36.0f;
                if (m267_saiRotX >= 360.0f) {
                    m267_saiRotX -= 360.0f;
                } else if (m267_saiRotX < 0.0f) {
                    m267_saiRotX += 360.0f;
                }
                break;
        }
    } else if (m267_saiState == 2) {
        HuAudFXPlay(0x51C);
        m267_saiState = 0;
    } else if (m267_saiState == 0) {
        if (m267_saiScaleX > 0.0f) {
            m267_saiScaleX -= 0.2f;
        } else {
            m267_saiScaleX = 0.0f;
        }
        if (m267_saiScaleY > 0.0f) {
            m267_saiScaleY -= 0.2f;
        } else {
            m267_saiScaleY = 0.0f;
        }
        m267_saiPhase = 0;
    }
    omSetTra(object, m267_saiPosX, m267_saiPosY, m267_saiPosZ);
    omSetRot(object, m267_saiRotX, m267_saiRotY, 0.0f);
    omSetSca(object, m267_saiScaleX, m267_saiScaleY, m267_saiScaleY);
}

void m267_SaiNumObjInit(omObjData *object) {
    u16 i = 0; // initialized early to match register allocation
    s32 attr = 0x2A9;
    s32 files[6] = { 0x64000C, 0x64000D, 0x64000E, 0x64000F, 0x640010, 0x640011 };

    for (i = 0; i < 6; i++) {
        object->model[i] = Hu3DModelRead(files[i], attr);
    }
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    for (i = 1; i < 6; i++) {
        Hu3DModelPosSet(object->model[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(object->model[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(object->model[i], 1.0f, 1.0f, 1.0f);
    }
    for (i = 0; i < 6; i++) {
        Hu3DModelCameraSet(object->model[i], 0);
    }
    m267_saiNumState = 0;
    m267_saiNo = 0;
    object->func = m267_SaiNumObjMain;
}

void m267_SaiNumObjMain(omObjData *object) {
    if (m267_saiNumState == 1) {
        switch (m267_saiNumPhase) {
            case 0:
                m267_saiNumY = m267_saiPosY;
                m267_saiNumScale = 0.0f;
                m267_saiNumTimer = 0;
                Hu3DModelCameraSet(object->model[m267_saiNo], 1);
                m267_saiNumPhase++;
                break;
            case 1:
                if (m267_saiNumScale < 1.0f) {
                    m267_saiNumScale += 0.1f;
                } else {
                    m267_saiNumScale = 1.0f;
                    m267_saiNumPhase++;
                }
                m267_saiNumY += 0.0f;
                break;
            case 2:
                if (m267_saiNumTimer >= 15) {
                    m267_saiNumTimer = 0;
                    m267_saiNumPhase++;
                } else {
                    m267_saiNumTimer++;
                }
                break;
            case 3:
                m267_saiNumPhase = 0;
                m267_saiNumState = 0;
                break;
        }
    } else if (m267_saiNumState == 0) {
        if (m267_saiNumScale > 0.0f) {
            m267_saiNumScale -= 0.1f;
        } else {
            m267_saiNumScale = 0.0f;
            Hu3DModelCameraSet(object->model[m267_saiNo], 0);
        }
    }
    if (m267_saiNo == 0) {
        omSetTra(object, m267_saiPosX, m267_saiNumY, m267_saiPosZ);
        omSetSca(object, m267_saiNumScale, m267_saiNumScale, m267_saiNumScale);
    } else {
        Hu3DModelPosSet(object->model[m267_saiNo], m267_saiPosX,
                        m267_saiNumY, m267_saiPosZ);
        Hu3DModelScaleSet(object->model[m267_saiNo], m267_saiNumScale,
                          m267_saiNumScale, m267_saiNumScale);
    }
}

s16 m267_WinCreate(s16 x, s16 y, s16 lines) {
    s16 win;

    win = HuWinExCreateStyled(x, y, lines);
    HuWinAttrSet(win, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
    HuWinExPriSet(win, 1);
    HuWinMesSpeedSet(win, 0);
    HuWinHomeClear(win);
    return win;
}

void m267_WinClose(s16 win) {
    HuWinHomeClear(win);
    HuWinExClose(win, 1);
    HuWinExCleanup(win);
}

void m267_WinKeyWait(s16 win, s16 player, s16 mode) {
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
                                    m267_comKeyWaitTbl[m267_comLevel]);
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

s16 m267_WinChoiceGet(s16 win, s16 player, s16 mode, s16 count) {
    GameGuysLucky7PadValues keys;
    GameGuysLucky7PadValues players;
    s16 i;

    keys = m267_comKeyTbl;
    players = m267_activePlayerTbl;
    switch (mode) {
        case 0:
            keys.v[player] = -1;
            HuWinAttrSet(win, HUWIN_ATTR_COMKEY, HUWIN_ATTR_NONE);
            HuWinActivePlayerSet(win, players.v[player]);
            HuWinComKeySet(keys.v[0], keys.v[1], keys.v[2], keys.v[3]);
            break;
        case 1:
            for (i = 0; i < count; i++) {
                keys.v[player] = 0x400;
                HuWinComKeyWait(keys.v[0], keys.v[1], keys.v[2], keys.v[3],
                                m267_comKeyWaitTbl[m267_comLevel]);
            }
            keys.v[player] = -0x8000;
            HuWinComKeyWait(keys.v[0], keys.v[1], keys.v[2], keys.v[3],
                            m267_comKeyWaitTbl[m267_comLevel]);
            break;
    }
    return HuWinChoiceGet(win, 0, 1);
}

s16 m267_WinChoiceGetEx(s16 win, s16 player, s16 mode, s16 count) {
    GameGuysLucky7PadValues keys;
    GameGuysLucky7PadValues players;
    s16 i;

    keys = m267_comKeyTbl;
    players = m267_activePlayerTbl;
    switch (mode) {
        case 0:
            keys.v[player] = -1;
            HuWinAttrSet(win, HUWIN_ATTR_COMKEY, HUWIN_ATTR_NONE);
            HuWinActivePlayerSet(win, players.v[player]);
            HuWinComKeySet(keys.v[0], keys.v[1], keys.v[2], keys.v[3]);
            break;
        case 1:
            for (i = 0; i < count; i++) {
                keys.v[player] = 0x400;
                HuWinComKeyWait(keys.v[0], keys.v[1], keys.v[2], keys.v[3],
                                m267_comKeyWaitTbl[m267_comLevel]);
            }
            keys.v[player] = -0x8000;
            HuWinComKeyWait(keys.v[0], keys.v[1], keys.v[2], keys.v[3],
                            m267_comKeyWaitTbl[m267_comLevel]);
            break;
    }
    return HuWinChoiceGet(win, 1, 1);
}

const GameGuysLucky7PadValues m267_comKeyTbl = { { 0, 0, 0, 0 } }; // COM keys

const GameGuysLucky7PadValues m267_activePlayerTbl = { { 1, 2, 4, 8 } }; // active players

void m267_ConfettiCreate(void) {
    s16 i;
    s16 model;

    for (i = 0; i < 4; i++) {
        model = Hu3DModelRead(m267_confettiMdlFileTbl[i], 0x2A9);
        m267_confettiMdlTbl[i] = model;
        Hu3DAnmNoSet(Hu3DAnimRead(Hu3DData[model].hmf, 0xB0048, "e268p01_I8"), i * 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelObjAttrSet(model, 0x20000, 0x20000);
        Hu3DModelRemakeStatic(model);
        Hu3DModelVtxBufMake(model);
        Hu3DModelDynamicFree(model);
        Hu3DParticleCreate(model, -1, NULL, m267_ConfettiParticleUpdate);
    }
    omAddObj(10, 10, 10, -1, m267_ConfettiObjMain);
}

void m267_ConfettiObjMain(omObjData *object) {
    s16 i;

    for (i = 0; i < 4; i++) {
        if (((m267_confettiTimer + i) & 7) == 0) {
            m267_ConfettiEmit(m267_confettiMdlTbl[i]);
        }
    }
    m267_confettiTimer++;
}

void m267_ConfettiEmit(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = effect->unk58;
    s16 i;
    s16 count = hmf->unk1A;
    f32 temp;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk10 <= 0.0f) {
            temp = rand8() % 200 + -450.0f;
            particle->unk0C = temp;
            particle->unk10 = 1000.0f;
            temp = (rand8() * 1000 >> 8) - 500;
            particle->unk14 = temp;
            temp = ((rand8() * 10 >> 8) - 5) / 2.0f;
            particle->unk18 = temp;
            particle->unk1C = 0.0f;
            temp = ((rand8() * 10 >> 8) - 5) / 2.0f;
            particle->unk20 = temp;
            particle->unk08 = 5.0f;
            break;
        }
    }
}

void m267_ConfettiParticleUpdate(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 i;
    s16 count = hmf->unk1A;

    if (effect->unk02 == 0) {
        effect->unk04 &= ~4;
        particle = effect->unk58;
        for (i = 0; i < count; i++, particle++) {
            particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
            particle->unk24 = particle->unk28 = particle->unk2C = 0.0f;
            particle->unk08 = 0.0f;
            particle->unk04 = 1.0f;
        }
        effect->unk02++;
    }
    particle = effect->unk58;
    for (i = 0; i < count; i++, particle++) {
        if (particle->unk10 > 0.0f) {
            particle->unk0C += particle->unk18;
            particle->unk10 += particle->unk1C - 10.0f;
            particle->unk14 += particle->unk20;
        } else {
            particle->unk08 = 0.0f;
        }
    }
}
