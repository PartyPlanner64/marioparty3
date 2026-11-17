#include "common.h"
#include "game_guys_roulette.h"

typedef struct GameGuysRoulettePlayerInfo { // 0x8 bytes
    /* 0x00 */ u8 player;
    /* 0x01 */ u8 pad;
    /* 0x02 */ u8 chr;
    /* 0x03 */ u8 cpu;
    /* 0x04 */ u8 difficulty;
    /* 0x06 */ u16 coins;
} GameGuysRoulettePlayerInfo;

typedef struct GameGuysRouletteSprite { // 0x20 bytes
    /* 0x00 */ u8 slot;
    /* 0x04 */ s32 priority;
    /* 0x08 */ s32 x;
    /* 0x0C */ s32 y;
    /* 0x10 */ u32 width;
    /* 0x14 */ u32 height;
    /* 0x18 */ f32 scaleX;
    /* 0x1C */ f32 scaleY;
} GameGuysRouletteSprite;

typedef struct GameGuysRoulettePrizeFiles { // 0x18 bytes
    /* 0x00 */ s32 ids[6];
} GameGuysRoulettePrizeFiles;

typedef struct GameGuysRouletteCharFiles { // 0x20 bytes
    /* 0x00 */ s32 ids[8];                 // per-character sprite index (low half)
} GameGuysRouletteCharFiles;

typedef struct GameGuysRouletteHudWork { // 0xE bytes
    /* 0x00 */ u16 coinDigits[3];
    /* 0x06 */ GameGuysRoulettePlayerInfo playerInfo;
} GameGuysRouletteHudWork;

s16 m266_comKeyWaitTbl[3] = { 5, 25, 60 }; // COM key wait frames, indexed by CPU difficulty
u8 m266_introDoneF = 0;
u8 m266_cursorUpF = 0;     // selection moved left
u8 m266_cursorStep = 2;     // cursor step
f32 m266_prizeScale = 1.1f; // selected prize scale
f32 m266_prizeScaleStep = 0.1f; // selected prize scale step
u8 m266_cursorMoveTimer = 0;     // cursor move frames
u8 m266_comWait = 0;     // COM decision timer
u8 m266_countTimer = 0;     // countdown frame timer
u8 m266_countNum = 10;    // countdown
f32 m266_portraitScale = 0.0f; // portrait scale
s16 m266_startMesTimer = 0;
u8 m266_spinStartTimer = 0;       // spin start timer
u8 m266_gambleMotState = 0;       // spin start state
u8 m266_spinF = 0;       // spinning
u8 m266_spinState = 0;       // spin state
f32 m266_ballSpeed = 0.0f;   // wheel speed
f32 m266_ballAngle = 270.0f; // wheel angle
f32 m266_ballRotY = 0.0f;   // ball rotation
s16 m266_spinSeNo = 0;      // spin sound
u8 m266_ballSectionNo = 0;       // current slot
s16 m266_spinSePitch = 900;    // spin sound pitch
u8 m266_ballSectionPrev = 0;       // previous slot
s16 m266_finishMesTimer = 0;
u8 m266_resultTimer = 0;  // result timer
u8 m266_resultState = 0;  // result state
s16 m266_resultMesId = 0; // result message

const GameGuysRoulettePrizeFiles m266_prizeSprFileTbl = { { 4, 5, 6, 7, 8, 9 } };
const GameGuysRouletteCharFiles m266_chrSprFileTbl = { { 16, 17, 18, 19, 20, 21, 22, 23 } };
const GameGuysRoulettePrizeFiles m266_prizeMdlFileTbl = { { 16, 17, 18, 15, 19, 14 } };
const GameGuysRouletteCharFiles m266_chrMdlFileTbl = { { 28, 29, 30, 31, 32, 33, 34, 35 } };

char m266_mesBuf[0x100] BSS;
omObjData *m266_hudObj BSS;
omObjData *m266_wheelObj BSS;
omObjData *m266_gambleObj BSS;
omObjData *m266_markerObj BSS;
omObjData *m266_ballObj BSS;
Process *m266_ruleProc BSS;
Process *m266_prizeMesProc BSS;
u8 m266_prizeMesProcPad[4] BSS;                  /* Unreferenced. */
GameGuysRouletteSprite m266_backSpr BSS; // background
GameGuysRouletteSprite m266_bannerSprA BSS;
GameGuysRouletteSprite m266_bannerSprB BSS;
GameGuysRouletteSprite m266_prizePanelSpr BSS;    // prize panel
GameGuysRouletteSprite m266_prizeSprTbl[6] BSS; // prize icons
GameGuysRouletteSprite m266_portraitSpr BSS;    // character portrait
GameGuysRouletteSprite m266_coinIconSpr BSS;
GameGuysRouletteSprite m266_coinCrossSpr BSS;
GameGuysRouletteHudWork m266_hudWork BSS;
extern u16 m266_coinDigitTbl[3];                     // m266_hudWork.coinDigits
extern GameGuysRoulettePlayerInfo m266_playerInfo; // m266_hudWork.playerInfo
u16 m266_winId BSS;                           // window
u16 m266_ruleDoneF BSS;
u16 m266_prizeMesDoneF BSS;
f32 m266_ballSpeedStart BSS;
f32 m266_ballDecel BSS;
f32 m266_ballDistExtra BSS;
u16 m266_slotAngleTbl[24] BSS; // wheel slot angles
f32 m266_sectionAngleTbl[6] BSS;
f32 m266_prizeAngleTbl[6] BSS;
u8 m266_mainPhase BSS;
u8 m266_prizeNo BSS;
s16 m266_comPrizeNo BSS;
s16 m266_timerMesId BSS; // message window
u8 m266_winSlotNo BSS;  // winning slot
u8 m266_winPrizeNo BSS;  // winning prize
u8 m266_winF BSS;
s16 m266_comLevel BSS; // CPU difficulty

void m266_LightInit(void);
void m266_CameraInit(void);
void m266_WinInit(void);
void m266_ObjectSetup(void);
void m266_MainObjInit(omObjData *object);
void m266_PlayerInfoInit(GameGuysRoulettePlayerInfo *info);
void m266_WheelInit(void);
void m266_HudObjInit(omObjData *object);
void m266_IntroUpdate(void);
void m266_RuleProc(void);
void m266_WinKeyWait(s16 win);
void m266_PrizeSelectUpdate(void);
void m266_PrizeMesProc(void);
void m266_StartMesUpdate(void);
void m266_SpinUpdate(void);
void m266_FinishMesUpdate(void);
void m266_ResultUpdate(void);
void m266_HudObjMain(omObjData *object);
void m266_EspSlotCreate(u8 *espriteSlot, s32 spriteIndex, u16 visibility);
void m266_SprParamSet(GameGuysRouletteSprite *sprite, s32 priority, s32 x, s32 y, u32 width, u32 height,
                                      f32 scaleX, f32 scaleY);
void m266_SprDispSet(GameGuysRouletteSprite *sprite, u8 visible);
void m266_GambleObjInit(omObjData *object);
void m266_WheelObjInit(omObjData *object);
void m266_MarkerObjInit(omObjData *object);
void m266_BallObjInit(omObjData *object);
void m266_StageObjInit(omObjData *object);
void m266_MainObjMain(omObjData *object);
void m266_ExitStartObjMain(omObjData *object);
s16 m266_WinChoiceGet(s16 win, s16 player, s16 mode, s16 count);
void m266_ExitObjMain(omObjData *object);
void m266_ExitCheckObjMain(omObjData *object);

void m266_Executor(void) {
    m266_ObjectSetup();
}

s32 m266_Rand(f32 arg0) {
    u8 randomByte1 = rand8();
    u8 randomByte2 = rand8();
    s32 shiftedByte1 = (randomByte1 << 8);
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;

    return scaledRandom;
}

void m266_LightInit(void) {
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, 0.0f, 0.0f, 95.0f);
}

void m266_CameraInit(void) {
    s32 camIndex;

    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(camIndex, 19.03f, 80.0f, 8000.0f);
    CZoom = 1498.69f;
    CRot.x = 334.75f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 10.82f;
    Center.z = -505.55f;
}

void m266_WinInit(void) {
    HuWinInit();
    m266_winId = HuWinExCreateStyled(130, 110, 9);
    HuWinAttrSet(m266_winId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
    HuWinExPriSet(m266_winId, 1);
    HuWinExClose(m266_winId, 1);
}

void m266_ObjectSetup(void) {
    MapCollInit(32);
    Hu3DSprModelInit(32);
    omInitObjMan(32, 32);
    omGameSysInit();
    m266_LightInit();
    m266_CameraInit();
    m266_WinInit();
    omAddObj(1000, 0, 0, -1, m266_MainObjInit);
    omAddObj(2000, 0, 0, -1, m266_ExitCheckObjMain);
}

void m266_MainObjInit(omObjData *object) {
    m266_SpotIntroInit(160, 86);
    m266_PlayerInfoInit(&m266_playerInfo);
    m266_WheelInit();
    m266_hudObj = omAddObj(0, 10, 10, -1, m266_HudObjInit);
    m266_gambleObj = omAddObj(1, 10, 10, -1, m266_GambleObjInit);
    m266_wheelObj = omAddObj(2, 10, 10, -1, m266_WheelObjInit);
    m266_markerObj = omAddObj(3, 10, 10, -1, m266_MarkerObjInit);
    m266_ballObj = omAddObj(4, 10, 10, -1, m266_BallObjInit);
    omAddObj(5, 10, 10, -1, m266_StageObjInit);
    WipeCreateIn(255, 16);
    object->func = m266_MainObjMain;
}

void m266_PlayerInfoInit(GameGuysRoulettePlayerInfo *info) {
    u8 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    switch (i) {
        case 0:
            i = 0;
            break;
        case 1:
            i = 1;
            break;
        case 2:
            i = 2;
            break;
        case 3:
            i = 3;
            break;
        default:
            i = 0;
            break;
    }
    info->player = i;
    info->pad = GwPlayer[i].pad;
    info->chr = GwPlayer[i].chr;
    if (GwPlayer[i].stat & 1) {
        info->cpu = 1;
        info->difficulty = GwPlayer[i].cpu_difficulty;
        m266_comLevel = GwCommon.unkA0;
        if (m266_comLevel <= 0) {
            m266_comLevel = 0;
        } else if (m266_comLevel >= 2) {
            m266_comLevel = 2;
        }
    } else {
        info->cpu = 0;
        info->difficulty = 0;
    }
    info->coins = GwPlayer[i].gameCoin;
}

void m266_WheelInit(void) {
    f32 slice = 17.142857f;
    f32 halfSlice = 8.571428f;
    u32 angle;
    u8 i;

    m266_winSlotNo = m266_Rand(21.0f);
    if (m266_winSlotNo == 0) {
        m266_winPrizeNo = 5;
    } else if (m266_winSlotNo < 5) {
        m266_winPrizeNo = 2;
    } else if (m266_winSlotNo < 7) {
        m266_winPrizeNo = 4;
    } else if (m266_winSlotNo < 13) {
        m266_winPrizeNo = 0;
    } else if (m266_winSlotNo < 16) {
        m266_winPrizeNo = 3;
    } else if (m266_winSlotNo < 21) {
        m266_winPrizeNo = 1;
    }
    if (m266_playerInfo.cpu == 1) {
        m266_comPrizeNo = m266_Rand(6.0f);
        if (m266_playerInfo.difficulty != 0) {
            m266_comPrizeNo -= m266_Rand(m266_playerInfo.difficulty);
            if (m266_comPrizeNo <= 0) {
                m266_comPrizeNo = 0;
            }
        }
        if (m266_winPrizeNo == m266_comPrizeNo) {
            m266_winF = 1;
        } else {
            m266_winF = 0;
        }
    }
    m266_prizeNo = 0;
    for (i = 0; i < 21; i++) {
        angle = (slice * i + 270.0f) * 100.0f;
        if (angle % 100 >= 50) {
            m266_slotAngleTbl[i] = (angle / 100 + 1) % 360;
        } else {
            m266_slotAngleTbl[i] = (angle / 100) % 360;
        }
    }
    m266_ballSpeedStart = (m266_slotAngleTbl[m266_winSlotNo] + 2520.0f) * 2 / 450.0f;
    m266_ballDecel = m266_ballSpeedStart / 450.0f;
    m266_ballDistExtra = (m266_ballSpeedStart + m266_ballDecel) *
                                        (m266_ballSpeedStart / m266_ballDecel) / 2.0f -
                                    (m266_slotAngleTbl[m266_winSlotNo] + 2520.0f);
    m266_ballSpeedStart =
        (m266_slotAngleTbl[m266_winSlotNo] + 2520.0f - m266_ballDistExtra) * 2 / 450.0f;
    m266_ballDecel = m266_ballSpeedStart / 450.0f;
    m266_sectionAngleTbl[0] = 270.0f - halfSlice;
    m266_sectionAngleTbl[1] = slice + m266_sectionAngleTbl[0];
    m266_sectionAngleTbl[2] = slice * 4 + m266_sectionAngleTbl[1];
    m266_sectionAngleTbl[3] = slice * 2 + m266_sectionAngleTbl[2] - 360.0f;
    m266_sectionAngleTbl[4] = slice * 6 + m266_sectionAngleTbl[3];
    m266_sectionAngleTbl[5] = slice * 3 + m266_sectionAngleTbl[4];
    m266_prizeAngleTbl[0] = m266_slotAngleTbl[9] + halfSlice;
    m266_prizeAngleTbl[1] = m266_slotAngleTbl[18];
    m266_prizeAngleTbl[2] = m266_slotAngleTbl[2] + halfSlice;
    m266_prizeAngleTbl[3] = m266_slotAngleTbl[14];
    m266_prizeAngleTbl[4] = m266_slotAngleTbl[5] + halfSlice;
    m266_prizeAngleTbl[5] = 270.0f;
    m266_mainPhase = 0;
}

void m266_HudObjInit(omObjData *object) {
    GameGuysRoulettePrizeFiles prizeFiles = m266_prizeSprFileTbl;
    s32 chr = GwPlayer[m266_playerInfo.player].chr;
    GameGuysRouletteCharFiles charFiles = m266_chrSprFileTbl;
    s16 sprite;
    u8 i;

    m266_EspSlotCreate(&m266_backSpr.slot, 0x630000, 0x4008);
    m266_SprParamSet(&m266_backSpr, 1000, 0, 0, 320, 240, 1.0f, 1.0f);
    m266_SprDispSet(&m266_backSpr, 1);
    m266_EspSlotCreate(&m266_bannerSprA.slot, 0x630001, 0x4008);
    m266_SprParamSet(&m266_bannerSprA, 900, 0, 0, 320, 128, 1.0f, 1.0f);
    m266_SprDispSet(&m266_bannerSprA, 0);
    m266_EspSlotCreate(&m266_bannerSprB.slot, 0x630002, 0x4008);
    m266_SprParamSet(&m266_bannerSprB, 900, 0, 0, 320, 128, 1.0f, 1.0f);
    m266_SprDispSet(&m266_bannerSprB, 0);
    m266_EspSlotCreate(&m266_prizePanelSpr.slot, 0x630003, 8);
    m266_SprParamSet(&m266_prizePanelSpr, 800, 242, 16, 54, 144, 1.0f, 1.0f);
    m266_SprDispSet(&m266_prizePanelSpr, 1);
    for (i = 0; i < 6; i++) {
        m266_EspSlotCreate(&m266_prizeSprTbl[i].slot, prizeFiles.ids[i] | 0x630000, 8);
        m266_SprParamSet(&m266_prizeSprTbl[i], 700, 246, i * 22 + 22, 22, 22, 1.0f, 1.0f);
        m266_SprDispSet(&m266_prizeSprTbl[i], 0);
    }
    m266_EspSlotCreate(&m266_portraitSpr.slot, charFiles.ids[chr] | 0x210000, 8);
    m266_SprParamSet(&m266_portraitSpr, 600, 206, 1, 46, 46, 1.0f, 1.0f);
    m266_SprDispSet(&m266_portraitSpr, 0);
    m266_EspSlotCreate(&m266_coinIconSpr.slot, 0x21001A, 8);
    m266_SprParamSet(&m266_coinIconSpr, 500, 24, 16, 12, 12, 1.0f, 1.0f);
    m266_SprDispSet(&m266_coinIconSpr, 1);
    m266_EspSlotCreate(&m266_coinCrossSpr.slot, 0x21001B, 8);
    m266_SprParamSet(&m266_coinCrossSpr, 500, 36, 16, 12, 12, 1.0f, 1.0f);
    m266_SprDispSet(&m266_coinCrossSpr, 1);
    sprite = HuSprAnimDataRead(0x31);
    m266_coinDigitTbl[0] = espEntry(sprite, 0, 1);
    espPosSet(m266_coinDigitTbl[0], 54, 22);
    espPriSet(m266_coinDigitTbl[0], 500);
    m266_coinDigitTbl[1] = espEntry(sprite, 0, 1);
    espPosSet(m266_coinDigitTbl[1], 66, 22);
    espPriSet(m266_coinDigitTbl[1], 500);
    m266_coinDigitTbl[2] = espEntry(sprite, 0, 1);
    espPosSet(m266_coinDigitTbl[2], 78, 22);
    espPriSet(m266_coinDigitTbl[2], 500);
    object->func = m266_HudObjMain;
}

void m266_GambleObjInit(omObjData *object) {
    object->model[0] = Hu3DModelRead(0xA0063, 0x2B9);
    omSetTra(object, 0.0f, 193.0f, -117.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    omObjMotionRead(object, 0, 0xA0063);
    omObjMotionRead(object, 1, 0xA0066);
    omObjMotionRead(object, 2, 0xA0067);
    Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[0]].motId, 0, 30, 2);
    object->func = NULL;
}

void m266_WheelObjInit(omObjData *object) {
    GameGuysRoulettePrizeFiles modelFiles = m266_prizeMdlFileTbl;
    u8 i;

    object->model[0] = Hu3DModelRead(0x63000D, 0x2B9);
    omSetTra(object, 0.0f, 100.0f, 0.0f);
    omSetRot(object, 15.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    for (i = 1; i < 7; i++) {
        object->model[i] = Hu3DModelRead(modelFiles.ids[i - 1] | 0x630000, 0x2B9);
        Hu3DModelPosSet(object->model[i], 0.0f, 100.0f, 0.0f);
        Hu3DModelRotSet(object->model[i], 15.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(object->model[i], 1.0f, 1.0f, 1.0f);
    }
    object->func = NULL;
}

void m266_MarkerObjInit(omObjData *object) {
    GameGuysRouletteCharFiles charFiles = m266_chrMdlFileTbl;

    object->model[0] = Hu3DModelRead(charFiles.ids[m266_playerInfo.chr] | 0x210000, 0x2B9);
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 15.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    Hu3DModelCameraSet(object->model[0], 0);
    object->func = NULL;
}

void m266_BallObjInit(omObjData *object) {
    f32 x, y, z;

    object->model[0] = Hu3DModelRead(0x63000B, 0x2B9);
    object->model[1] = Hu3DModelRead(0x63000C, 0x2B9);
    x = cosdf(270.0f) * 85.0f;
    y = cosdf(15.0f) * 100.0f - sindf(270.0f) * 85.0f * sindf(15.0f);
    z = sindf(15.0f) * 100.0f + sindf(270.0f) * 85.0f * cosdf(15.0f);
    omSetTra(object, x, y + 100.0f, z);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    object->func = NULL;
}

void m266_StageObjInit(omObjData *object) {
    object->model[0] = Hu3DModelRead(0x630014, 0x2B9);
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    omObjMotionRead(object, 0, 0x630014);
    Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[0]].motId, 0, 30, 2);
    object->func = NULL;
}

void m266_MainObjMain(omObjData *object) {
    switch (m266_mainPhase) {
        case 0:
            m266_IntroUpdate();
            break;
        case 1:
            m266_ruleProc = omAddPrcObj(m266_RuleProc, 0x3F00, 0x800, 0);
            m266_mainPhase = 2;
            break;
        case 2:
            if (m266_ruleDoneF == 1) {
                m266_mainPhase = 5;
                m266_ruleDoneF = 0;
                omDelPrcObj(m266_ruleProc);
                omSysPauseDisableF = 0;
                m266_timerMesId = GMesCreate(0x1A, 10, 156, 56);
            }
            break;
        case 5:
            m266_PrizeSelectUpdate();
            break;
        case 6:
            m266_prizeMesProc = omAddPrcObj(m266_PrizeMesProc, 0x3F00, 0x800, 0);
            m266_mainPhase = 7;
            break;
        case 7:
            if (m266_portraitSpr.scaleX > 0.0f) {
                m266_portraitSpr.scaleX = m266_portraitSpr.scaleY -= 0.25f;
                m266_SprDispSet(&m266_portraitSpr, 1);
            } else {
                m266_portraitSpr.scaleX = m266_portraitSpr.scaleY = 0.0f;
                m266_SprDispSet(&m266_portraitSpr, 0);
            }
            if (m266_prizeMesDoneF == 1 && m266_portraitSpr.scaleX <= 0.0f) {
                m266_mainPhase = 8;
                m266_prizeMesDoneF = 0;
                omDelPrcObj(m266_prizeMesProc);
            }
            break;
        case 8:
            m266_StartMesUpdate();
            break;
        case 9:
            m266_SpinUpdate();
            break;
        case 10:
            m266_FinishMesUpdate();
            break;
        case 11:
            m266_ResultUpdate();
            break;
        case 12:
            object->func = m266_ExitStartObjMain;
            break;
    }
}

void m266_IntroUpdate(void) {
    m266_introDoneF = m266_SpotIntroUpdate();
    if (m266_introDoneF == 1) {
        m266_mainPhase = 1;
    }
}

void m266_RuleProc(void) {
    s16 done = FALSE;
    s16 choice;

    HuWinHomeClear(m266_winId);
    HuAudFXPlay(0x11D);
    HuWinExOpen(m266_winId, 1);
    HuWinMesSet(m266_winId, 0x2D00, -1, -1);
    m266_WinKeyWait(m266_winId);
    HuWinMesSet(m266_winId, 0x2D01, -1, -1);
    while (done == FALSE) {
        choice = m266_WinChoiceGet(m266_winId, m266_playerInfo.pad,
                                                  m266_playerInfo.cpu, 1);
        if (choice == 0) {
            HuWinMesSet(m266_winId, 0x2D02, -1, -1);
            m266_WinKeyWait(m266_winId);
            done = TRUE;
        } else if (choice == 1) {
            done = TRUE;
        }
        HuPrcVSleep();
    }
    HuWinMesSet(m266_winId, 0x2D03, -1, -1);
    m266_WinKeyWait(m266_winId);
    HuWinHomeClear(m266_winId);
    HuWinExClose(m266_winId, 1);
    m266_ruleDoneF = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m266_WinKeyWait(s16 win) {
    s16 i;

    HuWinComKeyReset();
    while (HuWinStatGet(win) != 0) {
        switch (m266_playerInfo.cpu) {
            case 0:
                if (HuPadBtnDown[m266_playerInfo.pad] & A_BUTTON) {
                    HuWinComKeySet(-0x8000, -0x8000, -0x8000, -0x8000);
                }
                break;
            case 1:
                for (i = 0; i < 10; i++) {
                    HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000,
                                    m266_comKeyWaitTbl[m266_comLevel]);
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

void m266_PrizeSelectUpdate(void) {
    u8 decide = FALSE;
    u8 dir = 0;
    u8 i;
    f32 x;
    f32 y;
    f32 z;
    f32 rotY;
    f32 rotZ;

    if (m266_playerInfo.cpu == 0) {
        decide = HuPadBtnDown[m266_playerInfo.pad] >> 15;
        dir = HuPadStkY[m266_playerInfo.pad] > 64;
        if (HuPadStkY[m266_playerInfo.pad] < -64) {
            dir = 2;
        }
    } else if (m266_playerInfo.cpu == 1) {
        if (m266_comWait >= 16) {
            if (m266_prizeNo == m266_comPrizeNo) {
                decide = TRUE;
            } else {
                dir = 2;
            }
            m266_comWait = 0;
        } else {
            m266_comWait++;
        }
    }

    if (m266_countTimer < 30) {
        m266_countTimer++;
    } else {
        m266_countNum--;
        m266_countTimer = 0;
        if (m266_countNum == 0) {
            decide = TRUE;
        }
    }
    GMesTimerValueSet(m266_countNum);

    if (m266_cursorMoveTimer == 0) {
        if (dir == 1 && m266_prizeNo != 0) {
            m266_prizeNo--;
            m266_cursorMoveTimer = 5;
            m266_prizeScale = 1.1f;
            m266_prizeScaleStep = 0.1f;
            m266_cursorUpF = 1;
            HuAudFXPlay(1);
        } else if (dir == 2 && m266_prizeNo < 5) {
            m266_prizeNo++;
            m266_cursorMoveTimer = 5;
            m266_prizeScale = 1.1f;
            m266_prizeScaleStep = 0.1f;
            m266_cursorUpF = 0;
            HuAudFXPlay(1);
        }
    } else {
        if (m266_cursorMoveTimer == 5 || m266_cursorMoveTimer == 1) {
            m266_cursorStep = 2;
        } else {
            m266_cursorStep = 6;
        }
        if (m266_cursorUpF == 0) {
            m266_portraitSpr.y += m266_cursorStep;
        } else {
            m266_portraitSpr.y -= m266_cursorStep;
        }
        m266_cursorMoveTimer--;
    }

    for (i = 0; i < 6; i++) {
        m266_SprDispSet(&m266_prizeSprTbl[i], 0);
        Hu3DModelCameraSet(m266_wheelObj->model[i + 1], 1);
    }
    m266_prizeSprTbl[m266_prizeNo].scaleX =
        m266_prizeSprTbl[m266_prizeNo].scaleY = m266_prizeScale;
    m266_SprDispSet(&m266_prizeSprTbl[m266_prizeNo], 1);
    if (m266_portraitScale < 1.0f) {
        m266_portraitScale += 0.25f;
    }
    m266_portraitSpr.scaleX = m266_portraitSpr.scaleY = m266_portraitScale;
    m266_SprDispSet(&m266_portraitSpr, 1);
    Hu3DModelCameraSet(m266_wheelObj->model[m266_prizeNo + 1], 0);
    m266_prizeScale += m266_prizeScaleStep;
    if (m266_prizeScale >= 1.5f || m266_prizeScale <= 1.1f) {
        m266_prizeScaleStep = -m266_prizeScaleStep;
    }

    if (decide == TRUE) {
        GMesTimerEnd();
        omSysPauseDisableF = 1;
        HuAudFXPlay(3);
        omVibrate(m266_playerInfo.player, 10, 0, 10);
        m266_prizeSprTbl[m266_prizeNo].scaleX =
            m266_prizeSprTbl[m266_prizeNo].scaleY = 1.5f;
        m266_SprDispSet(&m266_prizeSprTbl[m266_prizeNo], 1);
        Hu3DModelCameraSet(m266_wheelObj->model[m266_prizeNo + 1], 1);
        x = cosdf(m266_prizeAngleTbl[m266_prizeNo]) * 40.0f;
        y = 102.5f;
        z = sindf(m266_prizeAngleTbl[m266_prizeNo]) * 40.0f;
        rotY = y * cosdf(15.0f) - z * sindf(15.0f);
        rotZ = y * sindf(15.0f) + z * cosdf(15.0f);
        omSetTra(m266_markerObj, x, rotY + 100.0f, rotZ);
        Hu3DModelCameraSet(m266_markerObj->model[0], 1);
        if (m266_prizeNo == m266_winPrizeNo) {
            m266_winF = 1;
        } else {
            m266_winF = 0;
        }
        m266_mainPhase = 6;
    }
}

void m266_PrizeMesProc(void) {
    HuWinHomeClear(m266_winId);
    HuWinExOpen(m266_winId, 1);
    HuWinMesSet(m266_winId, 0x2D04, -1, -1);
    HuWinInsertMesSet(m266_winId, m266_prizeNo + 0x2D05, 0);
    m266_WinKeyWait(m266_winId);
    HuWinHomeClear(m266_winId);
    HuWinExClose(m266_winId, 1);
    m266_prizeMesDoneF = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m266_StartMesUpdate(void) {
    if (++m266_startMesTimer == 1) {
        GMesCreate(9);
    } else if (GMesStatGet() == GMES_STAT_NONE) {
        HuAudSeqFadeOut(0x1E);
        m266_mainPhase = 9;
        m266_startMesTimer = 0;
    }
}

void m266_SpinUpdate(void) {
    u8 i;
    f32 x;
    f32 y;
    f32 z;

    if (m266_spinStartTimer <= 30) {
        m266_spinStartTimer++;
        return;
    }

    if (m266_gambleMotState == 0) {
        Hu3DMotionModelSet(m266_gambleObj->model[0], m266_gambleObj->motion[1]);
        m266_gambleMotState = 1;
    } else if (m266_gambleMotState == 1) {
        if (m266_spinF == 0 &&
            Hu3DData[m266_gambleObj->model[0]].motTime >= 30.0f) {
            m266_spinF = 1;
        } else if (m266_spinF == 1) {
            if (Hu3DData[m266_gambleObj->model[0]].motTime >= 64.0f) {
                Hu3DMotionTimeSet(m266_gambleObj->model[0], 64.0f);
                m266_spinStartTimer++;
                if (m266_spinStartTimer >= 40) {
                    HuAudSeqPlay(0x48);
                    Hu3DMotionShiftSet(m266_gambleObj->model[0],
                                       Hu3DData[m266_gambleObj->motion[2]].motId, 0, 30, 2);
                    m266_gambleMotState = 2;
                }
            }
        } else {
            return;
        }
    }

    if (m266_spinF != 1) {
        return;
    }

    if (m266_spinState == 0) {
        m266_spinSeNo = HuAudFXPlay(0x512);
        m266_ballSpeed += 2.0f;
        if (m266_ballSpeed >= 10.0f) {
            m266_spinState = 1;
        }
    } else if (m266_spinState == 1) {
        if (m266_ballAngle == 0.0f) {
            m266_spinState = 2;
            m266_ballSpeed = m266_ballSpeedStart;
        }
    } else if (m266_spinState == 2) {
        m266_ballSpeed -= m266_ballDecel;
        HuAudFXPitchSet(m266_spinSeNo, m266_spinSePitch -= 10);
        if (m266_ballSpeed <= 0.0f) {
            HuAudFXStop(m266_spinSeNo);
            if (m266_winF == 1) {
                HuAudFXPlay(0x514);
                if (m266_prizeNo == 5) {
                    omVibrate(m266_playerInfo.player, 30, 0, 30);
                } else {
                    omVibrate(m266_playerInfo.player, 2, 2, 20);
                }
            } else {
                HuAudFXPlay(0x518);
            }
            m266_ballSpeed = 0.0f;
            Hu3DMotionShiftSet(m266_gambleObj->model[0],
                               Hu3DData[m266_gambleObj->motion[0]].motId, 0, 30, 2);
            m266_mainPhase = 10;
        }
    }

    x = cosdf(m266_ballAngle) * 85.0f;
    y = 100.0f * cosdf(15.0f) - sindf(m266_ballAngle) * 85.0f * sindf(15.0f);
    z = 100.0f * sindf(15.0f) + sindf(m266_ballAngle) * 85.0f * cosdf(15.0f);
    omSetTra(m266_ballObj, x, y + 100.0f, z);
    omSetRot(m266_ballObj, 0.0f, m266_ballRotY, 0.0f);
    Hu3DModelPosSet(m266_ballObj->model[1], Hu3DData[m266_ballObj->model[0]].pos.x,
                    Hu3DData[m266_ballObj->model[0]].pos.y,
                    Hu3DData[m266_ballObj->model[0]].pos.z);
    Hu3DData[m266_ballObj->model[1]].rot.y = Hu3DData[m266_ballObj->model[0]].rot.y;
    if (m266_ballSpeed - 0.5f > 0.0f) {
        m266_ballRotY -= (m266_ballSpeed - 0.5f) * 3.0;
    }
    m266_ballAngle += m266_ballSpeed;
    if (m266_ballAngle >= 360.0f) {
        m266_ballAngle -= 360.0f;
    }

    for (i = 1; i < 7; i++) {
        Hu3DModelCameraSet(m266_wheelObj->model[i], 1);
    }
    if (m266_sectionAngleTbl[0] <= m266_ballAngle &&
        m266_ballAngle < m266_sectionAngleTbl[1]) {
        Hu3DModelCameraSet(m266_wheelObj->model[6], 0);
        m266_ballSectionNo = 1;
    } else if (m266_sectionAngleTbl[1] <= m266_ballAngle &&
               m266_ballAngle < m266_sectionAngleTbl[2]) {
        Hu3DModelCameraSet(m266_wheelObj->model[3], 0);
        m266_ballSectionNo = 2;
    } else if ((m266_sectionAngleTbl[2] <= m266_ballAngle &&
                m266_ballAngle < 360.0f) ||
               (0.0f <= m266_ballAngle &&
                m266_ballAngle < m266_sectionAngleTbl[3])) {
        Hu3DModelCameraSet(m266_wheelObj->model[5], 0);
        m266_ballSectionNo = 3;
    } else if (m266_sectionAngleTbl[3] <= m266_ballAngle &&
               m266_ballAngle < m266_sectionAngleTbl[4]) {
        Hu3DModelCameraSet(m266_wheelObj->model[1], 0);
        m266_ballSectionNo = 4;
    } else if (m266_sectionAngleTbl[4] <= m266_ballAngle &&
               m266_ballAngle < m266_sectionAngleTbl[5]) {
        Hu3DModelCameraSet(m266_wheelObj->model[4], 0);
        m266_ballSectionNo = 5;
    } else if (m266_sectionAngleTbl[5] <= m266_ballAngle &&
               m266_ballAngle < m266_sectionAngleTbl[0]) {
        Hu3DModelCameraSet(m266_wheelObj->model[2], 0);
        m266_ballSectionNo = 6;
    }
    if (m266_ballSectionPrev != m266_ballSectionNo) {
        HuAudFXPlay(0x513);
        m266_ballSectionPrev = m266_ballSectionNo;
    }
}

void m266_FinishMesUpdate(void) {
    if (++m266_finishMesTimer == 1) {
        GMesCreate(0x14);
        HuAudSeqFadeOut(0x78);
    } else if (GMesStatGet() == GMES_STAT_NONE) {
        m266_mainPhase = 0xB;
    }
}

char *m266_chrNameTbl[] = {
    "\x82\x6C\x82\x60\x82\x71\x82\x68\x82\x6E",                 // ＭＡＲＩＯ
    "\x82\x6B\x82\x74\x82\x68\x82\x66\x82\x68",                 // ＬＵＩＧＩ
    "\x82\x6F\x82\x64\x82\x60\x82\x62\x82\x67",                 // ＰＥＡＣＨ
    "\x82\x78\x82\x6E\x82\x72\x82\x67\x82\x68",                 // ＹＯＳＨＩ
    "\x82\x76\x82\x60\x82\x71\x82\x68\x82\x6E",                 // ＷＡＲＩＯ
    "\x82\x63\x82\x6A",                                         // ＤＫ
    "\x82\x76\x82\x60\x82\x6B\x82\x74\x82\x68\x82\x66\x82\x68", // ＷＡＬＵＩＧＩ
    "\x82\x63\x82\x60\x82\x68\x82\x72\x82\x78",                 // ＤＡＩＳＹ
};

u8 m266_bannerTimer = 0;                                              // banner blink timer
u8 m266_bannerFrame = 1;                                              // banner blink frame
u8 m266_prizeMulTbl[6] = { 2, 4, 8, 16, 32, 64 }; // prize multipliers

void m266_ResultUpdate(void) {
    if (m266_resultState == 0) {
        HuAudFXAllFadeOut(30);
        if (m266_winF == 1) {
            HuAudSeqPlay(0x73);
            m266_resultMesId = GMesCreate(0x16, m266_playerInfo.chr);
            GMesTimeMaxSet(m266_resultMesId, 0x78);
        } else {
            HuAudSeqPlay(0x71);
            sprintf(m266_mesBuf, "%s\x81\x40\x82\x6B\x82\x6E\x82\x72\x82\x73\x81\x49",
                    m266_chrNameTbl[m266_playerInfo.chr]);
            m266_resultMesId = GMesCreate(0x19, m266_mesBuf, 0xA0, 0x78, 1.0, 1.0, 1);
            GMesTimeMaxSet(m266_resultMesId, 0x78);
        }
        m266_resultState = 1;
    } else if (m266_resultState == 1) {
        if (m266_resultTimer++ >= 135) {
            m266_mainPhase = 12;
        }
    }
}

void m266_HudObjMain(omObjData *object) {
    u16 digit;
    s16 x = 0;

    if (m266_bannerTimer >= 5) {
        if (m266_bannerFrame == 0) {
            m266_SprDispSet(&m266_bannerSprA, 0);
            m266_SprDispSet(&m266_bannerSprB, 0);
        } else if (m266_bannerFrame == 1) {
            m266_SprDispSet(&m266_bannerSprA, 1);
            m266_SprDispSet(&m266_bannerSprB, 0);
        } else if (m266_bannerFrame == 2) {
            m266_SprDispSet(&m266_bannerSprA, 0);
            m266_SprDispSet(&m266_bannerSprB, 1);
        }
        m266_bannerFrame++;
        if (m266_bannerFrame >= 3) {
            m266_bannerFrame = 0;
        }
        m266_bannerTimer = 0;
    }
    m266_bannerTimer++;
    if (m266_playerInfo.coins >= 999) {
        m266_playerInfo.coins = 999;
    }
    if (m266_playerInfo.coins == 0) {
        m266_playerInfo.coins = 0;
    }

    espDispOn(m266_coinDigitTbl[2]);
    if ((digit = m266_playerInfo.coins / 100) == 0) {
        espDispOff(m266_coinDigitTbl[2]);
    }
    espPatNoSet(m266_coinDigitTbl[2], digit);
    espPosSet(m266_coinDigitTbl[2], x + 54, 22);
    if (digit != 0) {
        x += 12;
    }

    espDispOn(m266_coinDigitTbl[1]);
    if ((digit = (u16)(m266_playerInfo.coins % 100) / 10) == 0 &&
        (u16)(m266_playerInfo.coins / 100) == 0) {
        espDispOff(m266_coinDigitTbl[1]);
    }
    espPatNoSet(m266_coinDigitTbl[1], digit);
    espPosSet(m266_coinDigitTbl[1], x + 54, 22);
    if (digit != 0 || (u16)(m266_playerInfo.coins / 100) != 0) {
        x += 12;
    }

    espPatNoSet(m266_coinDigitTbl[0], m266_playerInfo.coins % 10);
    espPosSet(m266_coinDigitTbl[0], x + 54, 22);
}

void m266_ExitStartObjMain(omObjData *object) {
    GwPlayer[m266_playerInfo.player].gameCoin = m266_playerInfo.coins;
    if (m266_winF == 1) {
        GwPlayer[m266_playerInfo.player].bonusCoin = m266_prizeMulTbl[m266_prizeNo];
    } else if (m266_winF == 0) {
        GwPlayer[m266_playerInfo.player].bonusCoin = 0;
    }
    WipeCreateOut(0, 20);
    HuAudSeqFadeOut(30);
    HuAudFXAllFadeOut(30);
    object->func = m266_ExitObjMain;
}

void m266_ExitObjMain(omObjData *object) {
    if (WipeStatGet() == 0) {
        osViBlack(0);
        m266_SpotDispOff();
        GMesClose();
        HuWinAllKill();
        HuSprAnimAllKill();
        omOvlReturnEx(1);
    }
}

void m266_ExitCheckObjMain(omObjData *object) {
    if (omSysExitReq == 1) {
        object->func = m266_ExitStartObjMain;
    }
}

void m266_EspSlotCreate(u8 *espriteSlot, s32 spriteIndex, u16 visibility) {
    *espriteSlot = espEntry(HuSprAnimDataRead(spriteIndex), 0, 1);
    espAttrSet(*espriteSlot, visibility);
}

void m266_SprParamSet(GameGuysRouletteSprite *sprite, s32 priority, s32 x, s32 y, u32 width, u32 height,
                                      f32 scaleX, f32 scaleY) {
    sprite->priority = priority;
    sprite->x = x;
    sprite->y = y;
    sprite->width = width;
    sprite->height = height;
    sprite->scaleX = scaleX;
    sprite->scaleY = scaleY;
}

void m266_SprDispSet(GameGuysRouletteSprite *sprite, u8 visible) {
    espPosSet(sprite->slot, sprite->x + sprite->width / 2, sprite->y + sprite->height / 2);
    espScaleSet(sprite->slot, sprite->scaleX, sprite->scaleY);
    espPriSet(sprite->slot, (u16)sprite->priority);
    if (visible == 1) {
        espDispOn(sprite->slot);
    } else {
        espDispOff(sprite->slot);
    }
}

s16 m266_WinChoiceGet(s16 win, s16 player, s16 mode, s16 count) {
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
                keys[player] = 0x400;
                HuWinComKeyWait(keys[0], keys[1], keys[2], keys[3], m266_comKeyWaitTbl[m266_comLevel]);
            }
            HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, m266_comKeyWaitTbl[m266_comLevel]);
            break;
    }
    return HuWinChoiceGet(win, 0, 1);
}
