#include "common.h"
#include "game_guys_magic_boxes.h"

typedef struct GameGuysMagicBoxesCamera { // 0x20 bytes
    f32 unk_00;                           // perspective camera id
    f32 unk_04;                           // zoom
    f32 unk_08;                           // CRot x
    f32 unk_0C;                           // CRot y
    f32 unk_10;                           // CRot z
    f32 unk_14;                           // Center x
    f32 unk_18;                           // Center y
    f32 unk_1C;                           // Center z
} GameGuysMagicBoxesCamera;

typedef struct GameGuysMagicBoxesBonus { // 0x6 bytes
    s16 amount[3];
} GameGuysMagicBoxesBonus;

typedef struct GameGuysMagicBoxesSprite { // 0x1C bytes
    /* 0x00 */ s16 unk_00;                // esprite slot, written by func_80109C98
    /* 0x02 */ u16 priority;              // lower 8 bits given to HuSprPriSet
    /* 0x04 */ s16 unk_04;                // given to func_8000BBFC
    /* 0x06 */ s16 x;
    /* 0x08 */ s16 y;
    /* 0x0A */ s16 xSub;   // added to x, halved
    /* 0x0C */ s16 ySub;   // added to y, halved
    /* 0x10 */ f32 unk_10; // given to func_8000BF00
    /* 0x14 */ f32 scaleX;
    /* 0x18 */ f32 scaleY;
} GameGuysMagicBoxesSprite;

typedef struct GameGuysMagicBoxesPadValues { // 0x8 bytes
    s16 v[4];                                // one entry per controller port
} GameGuysMagicBoxesPadValues;

typedef struct GameGuysMagicBoxesCharSprites { // 0x20 bytes
    s32 ids[8];                                // per-character sprite index (low half)
} GameGuysMagicBoxesCharSprites;

typedef struct GameGuysMagicBoxesPlayerInfo { // 0x8 bytes
    /* 0x00 */ u8 player;
    /* 0x01 */ u8 pad;
    /* 0x02 */ u8 chr;
    /* 0x03 */ u8 cpu;
    /* 0x04 */ u8 difficulty;
    /* 0x06 */ s16 coins;
} GameGuysMagicBoxesPlayerInfo;

typedef struct GameGuysMagicBoxesStateWork { // 0x10 bytes
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03[3][2];
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B[3];
    /* 0x0E */ u8 unk_0E;
    /* 0x0F */ u8 unk_0F;
} GameGuysMagicBoxesStateWork;

f32 m268_boxScaleL = 1.0f;
f32 m268_boxScaleR = 1.0f;
s16 m268_comKeyWaitTbl[3] = { 5, 25, 60 }; // COM key wait frames, indexed by CPU difficulty
u8 m268_introDoneF = 0;
u8 m268_boxDropState = 0; // drop state
u16 m268_boxDropTimer = 0;
f32 m268_boxDropVel = 0.0f;
u16 m268_shuffleTimer = 0;
u8 m268_startMesState = 0;
u8 m268_startMesStatePad = 0;
u8 m268_selectState = 0;   // choice state
s16 m268_countTimer = 0;  // countdown tick timer
s16 m268_countNum = 10; // countdown seconds
s16 m268_comWait = 0;  // CPU decision timer
f32 m268_portraitScale = 0.0f;
u16 m268_selectPrev = 0;
u8 m268_finishMesState = 0;
f32 m268_portraitScaleOut = 1.0f;
u8 m268_boxSpotState = 0;
u16 m268_boxSpotTPLvl = 0;
s16 m268_boxSpotX = 0;
s16 m268_boxSpotY = 0;
u8 m268_boxOpenState = 0;
u16 m268_boxOpenTimer = 0;
u8 m268_nextRoundState = 0;     // state
u16 m268_nextRoundTPLvl = 0x80; // sprite alpha timer
u8 m268_resultTimer = 0;
s16 m268_resultState = -1;
s16 m268_resultMesId = 0;
extern s16 m268_bannerTimer;
extern u8 m268_bannerFrame;
extern f32 m268_curtainScale; // box scale
extern u8 m268_gambleMotPrev;  // current motion
extern u8 m268_kinopioMotPrev;  // current motion
extern u8 m268_kinopioShadowScale;  // scale
extern u8 m268_koopaJrMotPrev;  // current motion
extern u8 m268_koopaJrShadowScale;  // scale

const GameGuysMagicBoxesCharSprites m268_chrSprFileTbl = { { 16, 17, 18, 19, 20, 21, 22, 23 } };
extern const GameGuysMagicBoxesBonus m268_bonusTbl;
extern const GameGuysMagicBoxesPadValues m268_comKeyTbl; // COM keys
extern const GameGuysMagicBoxesPadValues m268_activePlayerTbl; // active players

u8 m268_comResultTbl[4] BSS;
s16 m268_boxSpotUnused BSS;
u16 m268_boxSpotDropTPLvl BSS;
Vec m268_boxSpotPosTbl[2] BSS;
Vec2f m268_boxSpotScreenPosTbl[2] BSS;
Vec2f m268_boxSpotHistoryTbl[3][2] BSS;
char m268_mesBuf[0x100] BSS;
GameGuysMagicBoxesCamera m268_cameraParam BSS;
GameGuysMagicBoxesPlayerInfo m268_playerInfo BSS;
extern u8 m268_playerInfoNo[5]; // [0] player index, [1] pad, [2] chr, [3] cpu, [4] difficulty
extern u8 m268_playerInfoPad[3]; // [0] pad, [1] chr, [2] cpu flag (mode for the window helpers)
extern u8 m268_playerInfoCom[2]; // [0] cpu flag, [1] cpu difficulty
extern s16 m268_playerInfoCoin[]; // [0] coins
omObjData *m268_hudObj BSS;
omObjData *m268_curtainObj BSS;
omObjData *m268_gambleObj BSS;
omObjData *m268_kinopioObj BSS;
omObjData *m268_boxObj BSS;
omObjData *m268_koopaJrObj BSS;
omObjData *m268_box2Obj BSS;
Process *m268_ruleProc BSS;
Process *m268_shuffleMesProc BSS;
Process *m268_continueProc BSS;
GameGuysMagicBoxesSprite m268_backSpr BSS;
u8 m268_backSprPad[4] BSS; /* Unreferenced. */
GameGuysMagicBoxesSprite m268_bannerSpr BSS;
GameGuysMagicBoxesSprite m268_bannerSprA BSS;
GameGuysMagicBoxesSprite m268_bannerSprB BSS;
u8 m268_bannerSprBPad[4] BSS; /* Unreferenced. */
GameGuysMagicBoxesSprite m268_sideSprL BSS;
u8 m268_sideSprLPad[4] BSS; /* Unreferenced. */
GameGuysMagicBoxesSprite m268_sideSprR BSS;
u8 m268_sideSprRPad[4] BSS; /* Unreferenced. */
GameGuysMagicBoxesSprite m268_roundPanelSpr BSS;
u8 m268_roundPanelSprPad[4] BSS; /* Unreferenced. */
GameGuysMagicBoxesSprite m268_roundLampSprTbl[3][2] BSS;
GameGuysMagicBoxesSprite m268_coinIconSpr BSS;
GameGuysMagicBoxesSprite m268_coinCrossSpr BSS;
GameGuysMagicBoxesSprite m268_coinDigitSprTbl[3] BSS;
u8 m268_coinDigitSprTblPad[4] BSS; /* Unreferenced. */
GameGuysMagicBoxesSprite m268_portraitSpr BSS;
u8 m268_portraitSprPad[4] BSS; /* Unreferenced. */
Vec m268_boxPosTbl[2] BSS;
u8 m268_kinopioMotNo BSS;
u8 m268_koopaJrMotNo BSS;
u8 m268_gambleMotNo BSS;
s16 m268_gambleMotFrame BSS;
f32 m268_curtainXL BSS;
f32 m268_curtainXR BSS;
GameGuysMagicBoxesStateWork m268_stateWork BSS;
extern u8 m268_curtainState;       // m268_stateWork
extern u8 m268_bannerStopF;       // m268_stateWork
extern u8 m268_continueCursor;       // m268_stateWork
extern u8 m268_kinopioSideTbl[3][2]; // m268_stateWork
extern u8 m268_selectNo;       // m268_stateWork
extern u8 m268_winF;       // m268_stateWork
extern u8 m268_comSelectTbl[];     // m268_stateWork
extern u8 m268_comWinF;       // m268_stateWork
extern u8 m268_roundNo;       // m268_stateWork
u8 m268_mainPhase BSS;
HuSprite *m268_boxSpotSpr BSS;
s16 m268_boxSpotGrp BSS;
u8 *m268_boxSpotBufTbl[3] BSS;
u8 m268_boxSpotBufNo BSS;
s16 m268_comPayout BSS;
s16 m268_comRoundMax BSS;
u8 m268_shadowGrowF BSS;
s32 m268_coinStart BSS;
s16 m268_startMesId BSS;
s16 m268_procResult BSS;
s16 m268_boxMdl BSS;
s16 m268_boxLidMdl BSS;
s16 m268_comLevel BSS;

void m268_ObjectSetup(void);
void m268_LightInit(void);
void m268_CameraInit(void);
void m268_WinInit(void);
void m268_MainObjInit(omObjData *object);
void m268_RoundInit(void);
void m268_HudObjInit(omObjData *object);
void m268_HudObjMain(omObjData *object);
void m268_CurtainObjInit(omObjData *object);
void m268_GambleObjInit(omObjData *object);
void m268_KinopioObjInit(omObjData *object);
void m268_BoxObjInit(omObjData *object);
void m268_KoopaJrObjInit(omObjData *object);
void m268_Box2ObjInit(omObjData *object);
void m268_MainObjMain(omObjData *object);
void m268_RuleProc(void);
void m268_BoxDropUpdate(void);
void m268_ShuffleUpdate(void);
void m268_ShuffleMesProc(void);
void m268_StartMesUpdate(void);
void m268_BoxSelectUpdate(void);
void m268_FinishMesUpdate(void);
void m268_BoxSpotUpdate(void);
void m268_BoxOpenUpdate(void);
void m268_ContinueProc(void);
void m268_NextRoundUpdate(void);
void m268_ResultUpdate(void);
void m268_KinopioObjMain(omObjData *object);
void m268_BoxObjMain(omObjData *object);
void m268_KoopaJrObjMain(omObjData *object);
void m268_Box2ObjMain(omObjData *object);
void m268_CurtainObjMain(omObjData *object);
void m268_GambleObjMain(omObjData *object);
void m268_ExitStartObjMain(omObjData *object);
void m268_ExitObjMain(omObjData *object);
void m268_ExitCheckObjMain(omObjData *object);
void m268_CameraSetup(void);
void m268_CameraParamSet(GameGuysMagicBoxesCamera *cam, f32 camId, f32 zoom, f32 rotX, f32 rotY,
                                         f32 rotZ, f32 centerX, f32 centerY, f32 centerZ);
void m268_CameraApply(GameGuysMagicBoxesCamera *cam);
void m268_PlayerInfoInit(void);
void m268_BoxSpotLayerInit(void);
void m268_EspSlotCreate(GameGuysMagicBoxesSprite *sprite, s32 spriteIndex, u16 numSlots,
                                         u16 visibility);
void m268_SprParamSet(GameGuysMagicBoxesSprite *sprite, s16 priority, s16 unk04, s16 x,
                                         s16 y, s16 xSub, s16 ySub, f32 unk10, f32 scaleX, f32 scaleY);
void m268_SprDispSet(GameGuysMagicBoxesSprite *sprite, u8 visible);
void m268_BoxSpotDraw(s16 x, s16 y, s16 radius);
void m268_BoxSpotErase(s16 x, s16 y, s16 radius);
s16 m268_WinCreate(s16 x, s16 y, s16 lines);
void m268_WinKeyWait(s16 win, s16 player, s16 mode);
s16 m268_WinChoiceGet(s16 win, s16 player, s16 mode, s16 count, u16 cancel);
void m268_WinClose(s16 win);
void m268_BoxSpotReset(void);

void m268_Executor(void) {
    m268_ObjectSetup();
}

s32 m268_Rand(f32 arg0) {
    u8 randomByte1 = rand8();
    u8 randomByte2 = rand8();
    s32 shiftedByte1 = (randomByte1 << 8);
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;

    return scaledRandom;
}

void m268_ObjectSetup(void) {
    MapCollInit(32);
    Hu3DSprModelInit(32);
    omInitObjMan(32, 32);
    omGameSysInit();
    m268_LightInit();
    m268_CameraInit();
    m268_PlayerInfoInit();
    m268_WinInit();
    omAddObj(1000, 0, 0, -1, m268_MainObjInit);
    omAddObj(10000, 0, 0, -1, m268_ExitCheckObjMain);
}

void m268_LightInit(void) {
}

void m268_CameraInit(void) {
    m268_CameraSetup();
    m268_CameraParamSet(&m268_cameraParam, 19.03f, 1498.69f, 334.75f, 0.0f, 0.0f,
                                        0.0f, 10.82f, -505.55f);
    m268_CameraApply(&m268_cameraParam);
}

void m268_WinInit(void) {
    HuWinInit();
}

void m268_MainObjInit(omObjData *object) {
    m268_SpotIntroInit(160, 190);
    m268_RoundInit();
    m268_BoxSpotLayerInit();
    m268_hudObj = omAddObj(1, 10, 10, -1, m268_HudObjInit);
    m268_curtainObj = omAddObj(2, 10, 10, -1, m268_CurtainObjInit);
    m268_gambleObj = omAddObj(3, 10, 10, -1, m268_GambleObjInit);
    m268_kinopioObj = omAddObj(4, 10, 10, -1, m268_KinopioObjInit);
    m268_boxObj = omAddObj(5, 10, 10, -1, m268_BoxObjInit);
    m268_koopaJrObj = omAddObj(6, 10, 10, -1, m268_KoopaJrObjInit);
    m268_box2Obj = omAddObj(7, 10, 10, -1, m268_Box2ObjInit);
    WipeCreateIn(0xFF, 0x10);
    object->func = m268_MainObjMain;
}

void m268_RoundInit(void) {
    u8 i;

    m268_boxPosTbl[0].x = -150.0f;
    m268_boxPosTbl[0].y = 0.0f;
    m268_boxPosTbl[0].z = -1500.0f;
    m268_boxPosTbl[1].x = 150.0f;
    m268_boxPosTbl[1].y = 0.0f;
    m268_boxPosTbl[1].z = -1500.0f;
    m268_shadowGrowF = 0;
    m268_curtainXL = -260.0f;
    m268_curtainXR = 260.0f;
    m268_curtainState = 0;
    m268_bannerStopF = 0;
    m268_boxScaleL = 1.0f;
    m268_boxScaleR = 1.0f;
    for (i = 0; i < 3; i++) {
        m268_kinopioSideTbl[i][0] = m268_Rand(2.0f);
        if (m268_kinopioSideTbl[i][0] == 0) {
            m268_kinopioSideTbl[i][1] = 1;
        } else {
            m268_kinopioSideTbl[i][1] = 0;
        }
    }
    if (m268_playerInfoCom[0] == 0) {
        m268_selectNo = 0;
    } else if (m268_playerInfoCom[0] == 1) {
        m268_comRoundMax = m268_Rand(3.0f);
        if (m268_playerInfoCom[1] != 0) {
            m268_comRoundMax = m268_Rand(m268_playerInfoCom[1]);
            if (m268_comRoundMax <= 0) {
                m268_comRoundMax = 0;
            }
        }
        for (i = 0; i <= m268_comRoundMax; i++) {
            m268_comSelectTbl[i] = m268_Rand(2.0f);
        }
        m268_comWinF = 1;
        for (i = 0; i <= m268_comRoundMax; i++) {
            if (m268_kinopioSideTbl[i][m268_comSelectTbl[i]] == 0) {
                m268_comResultTbl[i] = 0;
                m268_comWinF = 0;
            } else {
                m268_comResultTbl[i] = 1;
            }
        }
        if (m268_comWinF == 0) {
            m268_comPayout = 0;
        } else {
            m268_comPayout = m268_playerInfoCoin[0] * ((m268_comRoundMax + 1) << 1);
        }
    }
    m268_roundNo = 0;
    m268_mainPhase = 0;
}

void m268_HudObjInit(omObjData *object) {
    GameGuysMagicBoxesCharSprites charSprites;
    u8 chr;
    u8 i;

    chr = GwPlayer[m268_playerInfoNo[0]].chr;
    charSprites = m268_chrSprFileTbl;
    m268_EspSlotCreate(&m268_backSpr, 0x650000, 0, 0x4000);
    m268_SprParamSet(&m268_backSpr, 1000, 0x100, 0, 0, 320, 240, 0.0f, 1.0f,
                                        1.0f);
    m268_SprDispSet(&m268_backSpr, 1);
    m268_EspSlotCreate(&m268_bannerSpr, 0x650001, 0, 0);
    m268_SprParamSet(&m268_bannerSpr, 800, 0x100, 0, 0, 320, 186, 0.0f, 1.0f,
                                        1.0f);
    m268_SprDispSet(&m268_bannerSpr, 1);
    m268_EspSlotCreate(&m268_bannerSprA, 0x650002, 0, 0);
    m268_SprParamSet(&m268_bannerSprA, 800, 0x100, 0, 0, 320, 186, 0.0f, 1.0f,
                                        1.0f);
    m268_SprDispSet(&m268_bannerSprA, 0);
    m268_EspSlotCreate(&m268_bannerSprB, 0x650003, 0, 0);
    m268_SprParamSet(&m268_bannerSprB, 800, 0x100, 0, 0, 320, 186, 0.0f, 1.0f,
                                        1.0f);
    m268_SprDispSet(&m268_bannerSprB, 0);
    m268_EspSlotCreate(&m268_roundPanelSpr, 0x650004, 0, 0);
    m268_SprParamSet(&m268_roundPanelSpr, 800, 0x100, 242, 16, 54, 54, 0.0f, 1.0f,
                                        1.0f);
    m268_SprDispSet(&m268_roundPanelSpr, 1);
    for (i = 0; i < 3; i++) {
        m268_EspSlotCreate(&m268_roundLampSprTbl[i][0], 0x21002A, 0, 0);
        m268_SprParamSet(&m268_roundLampSprTbl[i][0], 99, 0x100, i * 16 + 24, 32, 16,
                                            16, 0.0f, 1.0f, 1.0f);
        m268_SprDispSet(&m268_roundLampSprTbl[i][0], 0);
        m268_EspSlotCreate(&m268_roundLampSprTbl[i][1], 0x21002B, 0, 0);
        m268_SprParamSet(&m268_roundLampSprTbl[i][1], 100, 0x100, i * 16 + 24, 32, 16,
                                            16, 0.0f, 1.0f, 1.0f);
        m268_SprDispSet(&m268_roundLampSprTbl[i][1], 1);
    }
    m268_SprDispSet(&m268_roundLampSprTbl[0][0], 1);
    m268_EspSlotCreate(&m268_coinIconSpr, 0x21001A, 0, 0);
    m268_SprParamSet(&m268_coinIconSpr, 100, 0x100, 24, 16, 12, 12, 0.0f, 1.0f,
                                        1.0f);
    m268_SprDispSet(&m268_coinIconSpr, 1);
    m268_EspSlotCreate(&m268_coinCrossSpr, 0x21001B, 0, 0);
    m268_SprParamSet(&m268_coinCrossSpr, 100, 0x100, 36, 16, 12, 12, 0.0f, 1.0f,
                                        1.0f);
    m268_SprDispSet(&m268_coinCrossSpr, 1);
    for (i = 0; i < 3; i++) {
        m268_EspSlotCreate(&m268_coinDigitSprTbl[i], 0x31, 1, 0);
        m268_SprParamSet(&m268_coinDigitSprTbl[i], 100, 0x100, i * 12 + 48, 16, 12, 12,
                                            0.0f, 1.0f, 1.0f);
        m268_SprDispSet(&m268_coinDigitSprTbl[i], 1);
    }
    m268_EspSlotCreate(&m268_portraitSpr, charSprites.ids[chr] | 0x210000, 0, 0);
    m268_SprParamSet(&m268_portraitSpr, 100, 0x100, 55, 70, 46, 46, 0.0f, 1.0f,
                                        1.0f);
    m268_SprDispSet(&m268_portraitSpr, 0);
    object->func = m268_HudObjMain;
}

void m268_CurtainObjInit(omObjData *object) {
    object->model[0] = Hu3DModelRead(0x650006, 0x2B9);
    omSetTra(object, 330.0f, -400.0f, -1000.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    object->model[1] = Hu3DModelLink(object->model[0]);
    Hu3DModelPosSet(object->model[1], 460.0f, -400.0f, -1000.0f);
    Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 1.0f, 1.0f, 1.0f);
    object->model[2] = Hu3DModelRead(0x650007, 0x2B9);
    object->model[3] = Hu3DModelLink(object->model[2]);
    Hu3DModelPosSet(object->model[2], 460.0f, -400.0f, -999.0f);
    Hu3DModelRotSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[2], 1.0f, 1.0f, 1.0f);
    Hu3DModelPosSet(object->model[3], 460.0f, -400.0f, -999.0f);
    Hu3DModelRotSet(object->model[3], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[3], 1.0f, 1.0f, 1.0f);
    object->func = m268_CurtainObjMain;
}

void m268_GambleObjInit(omObjData *object) {
    object->model[0] = Hu3DModelRead(0xA0063, 0x2B9);
    Hu3DMotionSpeedSet(object->model[0], 1.0f);
    omSetTra(object, 0.0f, 0.0f, -150.0f);
    omSetRot(object, -10.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    omObjMotionRead(object, 0, 0xA0063);
    omObjMotionRead(object, 1, 0xA0068);
    omObjMotionRead(object, 2, 0xA006C);
    m268_gambleMotNo = 0;
    object->model[1] = Hu3DModelRead(9, 0x2B9);
    Hu3DModelPosSet(object->model[1], 0.0f, 0.0f, -150.0f);
    Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 1.0f, 1.0f, 1.0f);
    object->func = m268_GambleObjMain;
}

void m268_KinopioObjInit(omObjData *object) {
    void *data;
    s16 anim;

    object->model[0] = Hu3DModelRead(0xA0000, 0x2A9);
    Hu3DMotionSpeedSet(object->model[0], 1.0f);
    omSetTra(object, m268_boxPosTbl[0].x, m268_boxPosTbl[0].y,
             m268_boxPosTbl[0].z);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    omObjMotionRead(object, 0, 0xA0001);
    omObjMotionRead(object, 1, 0xA000A);
    omObjMotionRead(object, 2, 0xA000B);
    omObjMotionRead(object, 3, 0xA001F);
    omObjMotionRead(object, 4, 0xA0020);
    data = DataRead(0xA002B);
    anim = Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, data, 0, "c160n_0_DEF");
    DataClose(data);
    Hu3DModelRemakeStatic(object->model[0]);
    Hu3DModelDynamicFree(object->model[0]);
    Hu3DAnimAttrSet(anim, 1, 0);
    Hu3DAnimBankSet(anim, 0);
    m268_kinopioMotNo = 1;
    object->model[1] = Hu3DModelRead(9, 0x2B9);
    Hu3DModelPosSet(object->model[1], -150.0f, -700.0f, -1500.0f);
    Hu3DModelRotSet(object->model[1], -15.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 1.0f, 1.0f, 1.0f);
    object->func = m268_KinopioObjMain;
}

void m268_BoxObjInit(omObjData *object) {
    m268_boxMdl = object->model[0] = Hu3DModelRead(0x650009, 0x2B9);
    Hu3DMotionSpeedSet(object->model[0], 1.0f);
    omSetTra(object, m268_boxPosTbl[0].x, m268_boxPosTbl[0].y,
             m268_boxPosTbl[0].z);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    omObjMotionRead(object, 0, 0x65000A);
    m268_boxLidMdl = object->model[1] = Hu3DModelRead(0x650008, 0x2B9);
    Hu3DModelPosSet(object->model[1], m268_boxPosTbl[0].x, m268_boxPosTbl[0].y,
                    m268_boxPosTbl[0].z);
    Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 1.0f, 1.0f, 1.0f);
    object->func = m268_BoxObjMain;
}

void m268_KoopaJrObjInit(omObjData *object) {
    object->model[0] = Hu3DModelRead(0xA00EE, 0x2B9);
    Hu3DMotionSpeedSet(object->model[0], 1.0f);
    omSetTra(object, m268_boxPosTbl[1].x, m268_boxPosTbl[1].y,
             m268_boxPosTbl[1].z);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    omObjMotionRead(object, 0, 0xA00EE);
    omObjMotionRead(object, 1, 0xA00F4);
    omObjMotionRead(object, 2, 0xA00F5);
    omObjMotionRead(object, 3, 0xA00FD);
    omObjMotionRead(object, 4, 0xA00FE);
    m268_koopaJrMotNo = 1;
    object->model[1] = Hu3DModelRead(9, 0x2B9);
    Hu3DModelPosSet(object->model[1], 150.0f, -700.0f, -1500.0f);
    Hu3DModelRotSet(object->model[1], -15.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 1.0f, 1.0f, 1.0f);
    object->func = m268_KoopaJrObjMain;
}

void m268_Box2ObjInit(omObjData *object) {
    object->model[0] = Hu3DModelLink(m268_boxMdl);
    Hu3DMotionSpeedSet(object->model[0], 1.0f);
    omSetTra(object, m268_boxPosTbl[1].x, m268_boxPosTbl[1].y,
             m268_boxPosTbl[1].z);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    omObjMotionRead(object, 0, 0x65000A);
    object->model[1] = Hu3DModelLink(m268_boxLidMdl);
    Hu3DModelPosSet(object->model[1], m268_boxPosTbl[1].x, m268_boxPosTbl[1].y,
                    m268_boxPosTbl[1].z);
    Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 1.0f, 1.0f, 1.0f);
    object->func = m268_Box2ObjMain;
}

void m268_MainObjMain(omObjData *object) {
    switch (m268_mainPhase) {
        case 0:
            m268_introDoneF = m268_SpotIntroUpdate();
            if (m268_introDoneF == 1) {
                m268_mainPhase = 1;
            }
            break;
        case 1:
            m268_ruleProc = omAddPrcObj(m268_RuleProc, 0x3F00, 0x800, 0);
            m268_mainPhase = 2;
            break;
        case 2:
            if (m268_procResult == 1) {
                m268_mainPhase = 3;
                m268_procResult = 0;
                omDelPrcObj(m268_ruleProc);
            }
            break;
        case 3:
            m268_BoxDropUpdate();
            break;
        case 4:
            m268_ShuffleUpdate();
            break;
        case 5:
            m268_shuffleMesProc = omAddPrcObj(m268_ShuffleMesProc, 0x3F00, 0x800, 0);
            m268_mainPhase = 6;
            break;
        case 6:
            if (m268_procResult == 1) {
                m268_mainPhase = 7;
                m268_procResult = 0;
                omDelPrcObj(m268_shuffleMesProc);
            }
            break;
        case 7:
            m268_StartMesUpdate();
            break;
        case 8:
            m268_BoxSelectUpdate();
            break;
        case 9:
            m268_FinishMesUpdate();
            break;
        case 10:
            m268_BoxSpotUpdate();
            break;
        case 11:
            m268_BoxOpenUpdate();
            break;
        case 12:
            m268_continueProc = omAddPrcObj(m268_ContinueProc, 0x3F00, 0x800, 0);
            m268_mainPhase = 13;
            break;
        case 13:
            if (m268_procResult == 1) {
                m268_mainPhase = 14;
                m268_procResult = 0;
                omDelPrcObj(m268_continueProc);
            } else if (m268_procResult == 2) {
                HuAudSeqFadeOut(14);
                m268_mainPhase = 15;
                m268_procResult = 0;
                omDelPrcObj(m268_continueProc);
            }
            break;
        case 14:
            m268_NextRoundUpdate();
            break;
        case 15:
            m268_ResultUpdate();
            break;
        case 16:
            object->func = m268_ExitStartObjMain;
            break;
    }
}

void m268_RuleProc(void) {
    s16 win;
    s16 choice;
    s16 done = FALSE;

    m268_procResult = 0;
    win = m268_WinCreate(130, 160, 12);
    HuAudFXPlay(0x11D);
    HuWinExOpen(win, 1);
    HuWinMesSet(win, 0x2C00, -1, -1);
    m268_WinKeyWait(win, m268_playerInfoPad[0], m268_playerInfoPad[2]);
    HuWinMesSet(win, 0x2C01, -1, -1);
    while (done == FALSE) {
        choice = m268_WinChoiceGet(win, m268_playerInfoPad[0], m268_playerInfoPad[2], 1, 0);
        switch (choice) {
            case 0:
                HuWinMesSet(win, 0x2C02, -1, -1);
                m268_WinKeyWait(win, m268_playerInfoPad[0], m268_playerInfoPad[2]);
                /* fallthrough */
            case 1:
                done = TRUE;
                break;
        }
        HuPrcVSleep();
    }
    HuWinMesSet(win, 0x2C03, -1, -1);
    m268_WinKeyWait(win, m268_playerInfoPad[0], m268_playerInfoPad[2]);
    m268_WinClose(win);
    m268_procResult = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m268_BoxDropUpdate(void) {
    m268_boxPosTbl[0].y -= m268_boxDropVel;
    m268_boxPosTbl[1].y -= m268_boxDropVel;
    m268_boxSpotPosTbl[0].x = m268_boxPosTbl[0].x;
    m268_boxSpotPosTbl[0].y = m268_boxPosTbl[0].y + 100.0f;
    m268_boxSpotPosTbl[0].z = m268_boxPosTbl[0].z;
    m268_boxSpotPosTbl[1].x = m268_boxPosTbl[1].x;
    m268_boxSpotPosTbl[1].y = m268_boxPosTbl[1].y + 100.0f;
    m268_boxSpotPosTbl[1].z = m268_boxPosTbl[1].z;
    Hu3D3Dto2D(0, &m268_boxSpotPosTbl[0], &m268_boxSpotScreenPosTbl[0]);
    Hu3D3Dto2D(0, &m268_boxSpotPosTbl[1], &m268_boxSpotScreenPosTbl[1]);

    switch (m268_boxDropState) {
        case 0:
            m268_boxSpotUnused = 0;
            m268_boxSpotDropTPLvl = 0;
            m268_bannerStopF = 1;
            m268_boxDropState++;
            break;
        case 1:
            if (m268_boxSpotDropTPLvl >= 0x80) {
                m268_boxDropVel = 8.0f;
                m268_shadowGrowF = 0;
            } else {
                m268_boxSpotDropTPLvl += 8;
            }
            HuSprTPLvlSet(m268_boxSpotGrp, 0, m268_boxSpotDropTPLvl);
            if (m268_boxPosTbl[0].y == -128.0f) {
                HuAudFXPlay(0x535);
            }
            if (m268_boxPosTbl[0].y <= -450.0f) {
                HuAudFXPlay(0x531);
                HuAudFXPlay(0x530);
                m268_boxDropState++;
            }
            break;
        case 2:
            m268_boxDropVel -= 0.4f;
            if (m268_boxDropVel < 0.0f) {
                omVibrate(m268_playerInfoNo[0], 2, 3, 10);
                m268_boxDropVel = 0.0f;
                m268_boxDropState++;
            }
            break;
        case 3:
            if (m268_boxSpotDropTPLvl == 0) {
                m268_boxDropState = 4;
            } else {
                m268_boxSpotDropTPLvl -= 8;
            }
            HuSprTPLvlSet(m268_boxSpotGrp, 0, m268_boxSpotDropTPLvl);
            break;
        case 4:
            if (m268_winF != 0) {
                HuAudFXPlay(0x531);
                HuAudFXPlay(0x530);
            }
            HuAudFXPlay(0x52E);
            Hu3DMotionSpeedSet(m268_boxObj->model[0], -1.2f);
            Hu3DMotionSpeedSet(m268_box2Obj->model[0], -1.2f);
            m268_boxDropState = 5;
            m268_bannerStopF = 0;
            break;
        case 5:
            if (m268_boxDropTimer >= 13) {
                m268_kinopioMotNo = 0;
                if (m268_roundNo == 0) {
                    m268_koopaJrMotNo = 0;
                }
            } else {
                m268_boxDropTimer++;
            }
            if (Hu3DData[m268_boxObj->model[0]].motTime < 0.0f) {
                Hu3DMotionSpeedSet(m268_boxObj->model[0], 0.0f);
                m268_boxDropState = 6;
            }
            if (Hu3DData[m268_box2Obj->model[0]].motTime < 0.0f) {
                Hu3DMotionSpeedSet(m268_box2Obj->model[0], 0.0f);
                m268_boxDropState = 6;
            }
            break;
        case 6:
            Hu3DModelCameraSet(m268_koopaJrObj->model[0], 0);
            Hu3DModelCameraSet(m268_kinopioObj->model[0], 0);
            m268_boxDropTimer = 0;
            m268_boxDropState = 4;
            m268_boxDropVel = 0.0f;
            Hu3DMotionSpeedSet(m268_boxObj->model[0], 0.0f);
            Hu3DMotionSpeedSet(m268_box2Obj->model[0], 0.0f);
            m268_gambleMotNo = 1;
            m268_mainPhase = 4;
            break;
    }

    if (m268_boxDropState < 4) {
        m268_BoxSpotErase(m268_boxSpotHistoryTbl[m268_boxSpotBufNo][0].x,
                                            m268_boxSpotHistoryTbl[m268_boxSpotBufNo][0].y, 50);
        m268_BoxSpotErase(m268_boxSpotHistoryTbl[m268_boxSpotBufNo][1].x,
                                            m268_boxSpotHistoryTbl[m268_boxSpotBufNo][1].y, 50);
        m268_boxSpotHistoryTbl[m268_boxSpotBufNo][0].x = m268_boxSpotScreenPosTbl[0].x;
        m268_boxSpotHistoryTbl[m268_boxSpotBufNo][1].x = m268_boxSpotScreenPosTbl[1].x;
        m268_boxSpotHistoryTbl[m268_boxSpotBufNo][0].y = m268_boxSpotScreenPosTbl[0].y;
        m268_boxSpotHistoryTbl[m268_boxSpotBufNo][1].y = m268_boxSpotScreenPosTbl[1].y;
        m268_BoxSpotDraw(m268_boxSpotScreenPosTbl[0].x, m268_boxSpotScreenPosTbl[0].y,
                                            50);
        m268_BoxSpotDraw(m268_boxSpotScreenPosTbl[1].x, m268_boxSpotScreenPosTbl[1].y,
                                            50);
        m268_boxSpotSpr->data->pat->data =
            m268_boxSpotBufTbl[m268_boxSpotBufNo];
        m268_boxSpotBufNo = (u8)(m268_boxSpotBufNo + 1) % 3;
    }
}

void m268_ShuffleUpdate(void) {
    switch (m268_shuffleTimer) {
        case 10:
            HuAudFXPlay(0x532);
            break;
        case 18:
            m268_curtainState = 1;
            break;
        case 30:
            if (m268_kinopioSideTbl[m268_roundNo][0] == 1) {
                m268_boxPosTbl[0].x = -150.0f;
                m268_boxPosTbl[1].x = 150.0f;
            } else {
                m268_boxPosTbl[0].x = 150.0f;
                m268_boxPosTbl[1].x = -150.0f;
            }
            break;
        case 27:
            HuAudFXPlay(0x52D);
            break;
        case 43:
            m268_gambleMotNo = 2;
            break;
        case 45:
            Hu3DMotionSpeedSet(m268_gambleObj->model[0], 0.0f);
            break;
        case 48:
            Hu3DMotionSpeedSet(m268_gambleObj->model[0], 1.0f);
            break;
        case 91:
            m268_gambleMotNo = 1;
            break;
        case 94:
            HuAudFXPlay(0x52D);
            Hu3DMotionTimeSet(m268_gambleObj->model[0], 90.0f);
            Hu3DMotionSpeedSet(m268_gambleObj->model[0], -1.0f);
            break;
        case 122:
            HuAudFXPlay(0x533);
            m268_curtainState = 2;
            break;
        case 138:
            m268_gambleMotNo = 0;
            break;
        case 140:
            Hu3DMotionSpeedSet(m268_gambleObj->model[0], 1.0f);
            m268_sideSprL.x = -58;
            m268_sideSprR.x = 250;
            m268_shuffleTimer = 0;
            m268_mainPhase = 5;
            break;
        // Empty cases; needed for the jump table.
        case 11:
        case 12:
            break;
    }
    m268_shuffleTimer++;
}

void m268_ShuffleMesProc(void) {
    s16 win;

    m268_procResult = 0;
    win = m268_WinCreate(130, 160, 12);
    HuAudFXPlay(0x11D);
    HuWinExOpen(win, 1);
    HuWinMesSet(win, 0x2C04, -1, -1);
    m268_WinKeyWait(win, m268_playerInfoPad[0], m268_playerInfoPad[2]);
    m268_WinClose(win);
    m268_procResult = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m268_StartMesUpdate(void) {
    if (m268_startMesState == 0) {
        GMesClose();
        m268_startMesId = GMesCreate(GMES_MES_9);
        m268_startMesState = 1;
    } else if (m268_startMesState == 1) {
        if (GMesStatGet() == GMES_STAT_NONE) {
            m268_mainPhase = 8;
            m268_startMesState = 0;
            m268_startMesStatePad = 0;
        }
    }
}

void m268_BoxSelectUpdate(void) {
    u8 dir = 0;
    s32 confirm = FALSE;
    u16 buttons;

    switch (m268_selectState) {
        case 0:
            GMesCreate(26, 10, 156, 56);
            m268_selectNo = 0;
            m268_selectPrev = 0;
            m268_selectState = 10;
            break;
        case 10:
            m268_portraitSpr.x = 55;
            m268_portraitSpr.scaleY = m268_portraitScale;
            m268_portraitSpr.scaleX = m268_portraitScale;
            if (m268_portraitScale < 1.0f) {
                m268_portraitScale += 0.25f;
            } else {
                m268_selectState = 1;
            }
            m268_SprDispSet(&m268_portraitSpr, 1);
            if (m268_kinopioSideTbl[m268_roundNo][m268_selectNo] == 0) {
                if (m268_boxScaleL > 1.0f) {
                    m268_boxScaleL -= 0.05f;
                }
                if (m268_boxScaleR < 1.1f) {
                    m268_boxScaleR += 0.05f;
                }
            } else {
                if (m268_boxScaleL < 1.1f) {
                    m268_boxScaleL += 0.05f;
                }
                if (m268_boxScaleR > 1.0f) {
                    m268_boxScaleR -= 0.05f;
                }
            }
            omSetSca(m268_boxObj, m268_boxScaleL, m268_boxScaleL,
                     m268_boxScaleL);
            Hu3DModelScaleSet(m268_boxObj->model[1], m268_boxScaleL,
                              m268_boxScaleL, m268_boxScaleL);
            omSetSca(m268_box2Obj, m268_boxScaleR, m268_boxScaleR,
                     m268_boxScaleR);
            Hu3DModelScaleSet(m268_box2Obj->model[1], m268_boxScaleR,
                              m268_boxScaleR, m268_boxScaleR);
            break;
        case 1:
            if (m268_playerInfoPad[2] == 0) {
                if (HuPadStkX[m268_playerInfoPad[0]] > 64) {
                    dir = 1;
                }
                if (HuPadStkX[m268_playerInfoPad[0]] < -64) {
                    dir = 2;
                }
                buttons = HuPadBtn[m268_playerInfoPad[0]];
                if (buttons & A_BUTTON) {
                    confirm = TRUE;
                }
                if (dir == 1) {
                    m268_selectNo = 1;
                } else if (dir == 2) {
                    m268_selectNo = 0;
                }
            } else if (m268_playerInfoPad[2] == 1) {
                if (m268_comWait >= 35) {
                    if (m268_comSelectTbl[m268_roundNo] !=
                        m268_selectNo) {
                        m268_selectNo = 1;
                        m268_comWait = 0;
                    } else {
                        m268_comWait = 0;
                        confirm = TRUE;
                    }
                } else {
                    m268_comWait++;
                }
            }
            if (m268_selectPrev != m268_selectNo) {
                if (m268_selectNo == 1) {
                    HuAudFXPlay(1);
                    m268_portraitSpr.x = 140;
                } else if (m268_selectNo == 0) {
                    HuAudFXPlay(1);
                    m268_portraitSpr.x = 55;
                }
                m268_selectPrev = m268_selectNo;
            }
            if (m268_kinopioSideTbl[m268_roundNo][m268_selectNo] == 0) {
                if (m268_boxScaleL > 1.0f) {
                    m268_boxScaleL -= 0.05f;
                }
                if (m268_boxScaleR < 1.1f) {
                    m268_boxScaleR += 0.05f;
                }
            } else {
                if (m268_boxScaleL < 1.1f) {
                    m268_boxScaleL += 0.05f;
                }
                if (m268_boxScaleR > 1.0f) {
                    m268_boxScaleR -= 0.05f;
                }
            }
            omSetSca(m268_boxObj, m268_boxScaleL, m268_boxScaleL,
                     m268_boxScaleL);
            Hu3DModelScaleSet(m268_boxObj->model[1], m268_boxScaleL,
                              m268_boxScaleL, m268_boxScaleL);
            omSetSca(m268_box2Obj, m268_boxScaleR, m268_boxScaleR,
                     m268_boxScaleR);
            Hu3DModelScaleSet(m268_box2Obj->model[1], m268_boxScaleR,
                              m268_boxScaleR, m268_boxScaleR);
            m268_SprDispSet(&m268_portraitSpr, 1);
            if (m268_countTimer >= 30) {
                m268_countNum--;
                m268_countTimer = 0;
                GMesTimerValueSet(m268_countNum);
            } else {
                m268_countTimer++;
            }
            if ((confirm == TRUE) | (m268_countNum < 1)) {
                m268_portraitScale = 0.0f;
                m268_selectState = 2;
            }
            break;
        case 2:
            if (m268_kinopioSideTbl[m268_roundNo][m268_selectNo] == 1) {
                m268_winF = 1;
            } else {
                m268_winF = 0;
            }
            HuAudFXPlay(3);
            omSysPauseDisableF = 1;
            GMesTimerEnd();
            m268_mainPhase = 9;
            m268_selectState = 0;
            m268_countTimer = 0;
            m268_countNum = 10;
            m268_portraitScale = 0.0f;
            break;
    }
}

void m268_FinishMesUpdate(void) {
    if (m268_portraitScaleOut > 0.0f) {
        m268_portraitScaleOut -= 0.25f;
        m268_SprDispSet(&m268_portraitSpr, 1);
    } else {
        m268_SprDispSet(&m268_portraitSpr, 0);
    }
    m268_portraitSpr.scaleX = m268_portraitSpr.scaleY =
        m268_portraitScaleOut;
    if (m268_boxScaleL > 1.0f) {
        m268_boxScaleL -= 0.05f;
    }
    if (m268_boxScaleR > 1.0f) {
        m268_boxScaleR -= 0.05f;
    }
    omSetSca(m268_boxObj, m268_boxScaleL, m268_boxScaleL,
             m268_boxScaleL);
    Hu3DModelScaleSet(m268_boxObj->model[1], m268_boxScaleL,
                      m268_boxScaleL, m268_boxScaleL);
    omSetSca(m268_box2Obj, m268_boxScaleR, m268_boxScaleR,
             m268_boxScaleR);
    Hu3DModelScaleSet(m268_box2Obj->model[1], m268_boxScaleR,
                      m268_boxScaleR, m268_boxScaleR);
    if (m268_finishMesState == 0) {
        HuAudSeqVolFadeOut(120);
        GMesCreate(20);
        m268_finishMesState = 1;
    } else if (m268_finishMesState == 1) {
        if (GMesStatGet() == GMES_STAT_NONE) {
            m268_mainPhase = 10;
            m268_portraitScaleOut = 1.0f;
            m268_finishMesState = 0;
            m268_portraitSpr.x = 55;
        }
    }
}

void m268_BoxSpotUpdate(void) {
    u8 *pixels;
    s32 i;

    switch (m268_boxSpotState) {
        case 0:
            HuAudSubSeqPlay(0x49);
            GMesClose();
            m268_bannerStopF = 1;
            m268_boxSpotTPLvl = 0;
            if (m268_selectNo == 1) {
                m268_boxSpotX = 203;
            } else {
                m268_boxSpotX = 117;
            }
            m268_boxSpotY = 120;
            pixels = m268_boxSpotBufTbl[0];
            for (i = 0; i < 0x9600; i++) {
                *pixels++ = 0;
            }
            m268_boxSpotBufNo = 0;
            m268_BoxSpotDraw(m268_boxSpotX, m268_boxSpotY, 50);
            m268_boxSpotSpr->data->pat->data = m268_boxSpotBufTbl[0];
            m268_boxSpotState = 1;
            break;
        case 1:
            if (m268_boxSpotTPLvl >= 0x80) {
                m268_boxSpotState = 2;
            } else {
                m268_boxSpotTPLvl += 8;
            }
            HuSprTPLvlSet(m268_boxSpotGrp, 0, m268_boxSpotTPLvl);
            break;
        case 2:
            m268_boxSpotState = 0;
            m268_boxSpotX = 0;
            m268_boxSpotY = 0;
            m268_mainPhase = 11;
            break;
    }
}

void m268_BoxOpenUpdate(void) {
    switch (m268_boxOpenState) {
        case 0:
            if (m268_boxOpenTimer >= 30) {
                HuAudSubSeqVolFadeOut(1);
                m268_boxOpenTimer = 0;
                m268_boxOpenState = 1;
            } else {
                m268_boxOpenTimer++;
            }
            break;
        case 1:
            HuAudFXPlay(0x52F);
            Hu3DModelCameraSet(m268_koopaJrObj->model[0], 1);
            Hu3DModelCameraSet(m268_kinopioObj->model[0], 1);
            Hu3DMotionSpeedSet(m268_boxObj->model[0], 1.0f);
            Hu3DMotionSpeedSet(m268_box2Obj->model[0], 1.0f);
            m268_kinopioMotNo = 2;
            m268_koopaJrMotNo = 2;
            m268_boxOpenState = 2;
            if (m268_winF == 1) {
                if (m268_roundNo == 2) {
                    omVibrate(m268_playerInfoNo[0], 30, 0, 30);
                } else {
                    omVibrate(m268_playerInfoNo[0], 10, 0, 10);
                }
            } else {
                omVibrate(m268_playerInfoNo[0], 2, 2, 20);
            }
            break;
        case 2:
            if (m268_boxOpenTimer >= 45) {
                if (m268_winF == 0) {
                    HuAudFXPlay(0x534);
                } else {
                    HuAudFXPlay(0x535);
                }
                m268_boxOpenTimer = 0;
                m268_boxOpenState = 3;
            } else {
                m268_boxOpenTimer++;
            }
            if (m268_boxOpenTimer == 23) {
                if (m268_winF == 1) {
                    m268_kinopioMotNo = 4;
                    m268_koopaJrMotNo = 4;
                } else {
                    m268_kinopioMotNo = 3;
                    m268_koopaJrMotNo = 3;
                }
            }
            if (m268_boxOpenTimer == 25) {
                if (m268_winF == 1) {
                    HuAudFXPlay(0x531);
                } else {
                    HuAudFXPlay(0x530);
                }
            }
            break;
        case 3:
            if (m268_winF == 1 && m268_roundNo != 2) {
                HuAudSubSeqPlay(0x70);
                m268_mainPhase = 12;
                m268_boxOpenState = 0;
                m268_boxOpenTimer = 0;
            } else if (m268_winF == 0 || m268_roundNo == 2) {
                m268_mainPhase = 15;
            }
            break;
    }
}

void m268_ContinueProc(void) {
    s16 win;
    s16 done = FALSE;
    s16 choice = 0;

    HuPrcSleep(50);
    HuAudSubSeqParamSet(10);
    m268_procResult = 0;
    win = m268_WinCreate(130, 160, 12);
    HuAudFXPlay(0x11D);
    HuWinExOpen(win, 1);
    HuWinMesSet(win, 0x2C05, -1, -1);
    m268_WinKeyWait(win, m268_playerInfoPad[0], m268_playerInfoPad[2]);
    HuWinMesSet(win, 0x2C06, -1, -1);
    if (m268_comRoundMax != m268_roundNo) {
        m268_continueCursor = 0;
    } else {
        m268_continueCursor = 1;
    }
    while (done == FALSE) {
        choice = m268_WinChoiceGet(win, m268_playerInfoPad[0], m268_playerInfoPad[2],
                                                     m268_continueCursor, 1);
        switch (choice) {
            case 0:
                HuWinMesSet(win, 0x2C07, -1, -1);
                m268_WinKeyWait(win, m268_playerInfoPad[0], m268_playerInfoPad[2]);
                /* fallthrough */
            case 1:
                done = TRUE;
                break;
        }
        HuPrcVSleep();
    }
    m268_WinClose(win);
    if (choice == 0) {
        m268_procResult = 1;
    } else if (choice == 1) {
        m268_procResult = 2;
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m268_NextRoundUpdate(void) {
    switch (m268_nextRoundState) {
        case 0:
            m268_roundNo++;
            m268_playerInfoCoin[0] *= 2;
            m268_selectNo = 0;
            m268_nextRoundState++;
            break;
        case 1:
            if (m268_nextRoundTPLvl == 0) {
                m268_nextRoundState = 2;
            } else {
                m268_nextRoundTPLvl -= 8;
            }
            HuSprTPLvlSet(m268_boxSpotGrp, 0, m268_nextRoundTPLvl);
            break;
        case 2:
            m268_bannerStopF = 0;
            m268_mainPhase = 3;
            m268_nextRoundState = 0;
            m268_nextRoundTPLvl = 0x80;
            break;
    }
}

char *m268_chrNameTbl[] = {
    "\x82\x6C\x82\x60\x82\x71\x82\x68\x82\x6E",                 // ＭＡＲＩＯ
    "\x82\x6B\x82\x74\x82\x68\x82\x66\x82\x68",                 // ＬＵＩＧＩ
    "\x82\x6F\x82\x64\x82\x60\x82\x62\x82\x67",                 // ＰＥＡＣＨ
    "\x82\x78\x82\x6E\x82\x72\x82\x67\x82\x68",                 // ＹＯＳＨＩ
    "\x82\x76\x82\x60\x82\x71\x82\x68\x82\x6E",                 // ＷＡＲＩＯ
    "\x82\x63\x82\x6A",                                         // ＤＫ
    "\x82\x76\x82\x60\x82\x6B\x82\x74\x82\x68\x82\x66\x82\x68", // ＷＡＬＵＩＧＩ
    "\x82\x63\x82\x60\x82\x68\x82\x72\x82\x78",                 // ＤＡＩＳＹ
}; // character names

s16 m268_bannerTimer = 0;
u8 m268_bannerFrame = 0;
f32 m268_curtainScale = 0.0f; // box scale
u8 m268_gambleMotPrev = 0xFF;  // current motion
u8 m268_kinopioMotPrev = 0xFF;  // current motion
u8 m268_kinopioShadowScale = 1;     // scale
u8 m268_koopaJrMotPrev = 0xFF;  // current motion
u8 m268_koopaJrShadowScale = 1;     // scale

void m268_ResultUpdate(void) {
    if (m268_resultState == -1) {
        if (m268_resultTimer++ >= 15) {
            m268_resultTimer = 0;
            m268_resultState = 0;
        }
        if (m268_winF == 0) {
            m268_resultState = 0;
            m268_resultTimer = 0;
        }
    } else if (m268_resultState == 0) {
        if (m268_winF == 1) {
            HuAudSeqPlay(0x73);
            m268_resultMesId = GMesCreate(0x16, m268_playerInfoPad[1]);
            GMesTimeMaxSet(m268_resultMesId, 0x78);
        } else {
            HuAudSeqPlay(0x71);
            sprintf(m268_mesBuf, "%s\x81\x40\x82\x6B\x82\x6E\x82\x72\x82\x73\x81\x49",
                    m268_chrNameTbl[m268_playerInfoPad[1]]);
            m268_resultMesId = GMesCreate(0x19, m268_mesBuf, 0xA0, 0x78, 1.0, 1.0, 1);
            GMesTimeMaxSet(m268_resultMesId, 0x78);
        }
        m268_resultState = 1;
    } else if (m268_resultState == 1) {
        if (m268_resultTimer++ == 135) {
            m268_mainPhase = 16;
        }
    }
}

void m268_HudObjMain(omObjData *object) {
    s16 x;
    s16 hundreds;
    s16 tens;
    u8 i;

    x = 0;
    if (m268_bannerTimer >= 5) {
        m268_bannerFrame++;
        if (m268_bannerFrame >= 3) {
            m268_bannerFrame = 0;
        }
        switch (m268_bannerFrame) {
            case 0:
                m268_SprDispSet(&m268_bannerSprA, 0);
                m268_SprDispSet(&m268_bannerSprB, 0);
                break;
            case 1:
                m268_SprDispSet(&m268_bannerSprA, 1);
                m268_SprDispSet(&m268_bannerSprB, 0);
                break;
            case 2:
                m268_SprDispSet(&m268_bannerSprA, 0);
                m268_SprDispSet(&m268_bannerSprB, 1);
                break;
        }
        m268_bannerTimer = 0;
    }
    if (m268_bannerStopF != 1 || m268_bannerFrame != 0) {
        m268_bannerTimer++;
    }

    if (m268_playerInfoCoin[0] >= 999) {
        m268_playerInfoCoin[0] = 999;
    } else if (m268_playerInfoCoin[0] <= 0) {
        m268_playerInfoCoin[0] = 0;
    }

    if ((hundreds = m268_playerInfoCoin[0] / 100) == 0) {
        m268_SprDispSet(&m268_coinDigitSprTbl[2], 0);
    } else {
        espPatNoSet(m268_coinDigitSprTbl[2].unk_00, hundreds);
        m268_coinDigitSprTbl[2].x = x + 48;
        m268_SprDispSet(&m268_coinDigitSprTbl[2], 1);
        x += 12;
    }

    if ((tens = (s16)(m268_playerInfoCoin[0] % 100) / 10) == 0 &&
        (s16)(m268_playerInfoCoin[0] / 100) == 0) {
        m268_SprDispSet(&m268_coinDigitSprTbl[1], 0);
    } else {
        espPatNoSet(m268_coinDigitSprTbl[1].unk_00, tens);
        m268_coinDigitSprTbl[1].x = x + 48;
        m268_SprDispSet(&m268_coinDigitSprTbl[1], 1);
        x += 12;
    }

    espPatNoSet(m268_coinDigitSprTbl[0].unk_00, m268_playerInfoCoin[0] % 10);
    m268_coinDigitSprTbl[0].x = x + 48;
    m268_SprDispSet(&m268_coinDigitSprTbl[0], 1);

    for (i = 0; i <= m268_roundNo; i++) {
        m268_SprDispSet(&m268_roundLampSprTbl[i][0], 1);
    }
}

void m268_CurtainObjMain(omObjData *object) {
    if (m268_curtainState == 1) {
        if (m268_curtainXL < -200.0f) {
            m268_curtainXR -= 12.0f;
            m268_curtainXL += 12.0f;
            m268_curtainScale += 0.2f;
        } else {
            m268_curtainState = 0;
            m268_curtainXL = -200.0f;
            m268_curtainXR = 200.0f;
            m268_curtainScale = 1.0f;
        }
    } else if (m268_curtainState == 2) {
        if (m268_curtainScale > 0.0f) {
            m268_curtainXR += 9.0f;
            m268_curtainXL -= 9.0f;
            m268_curtainScale -= 0.03f;
        } else {
            m268_curtainState = 0;
            m268_curtainXL = -260.0f;
            m268_curtainXR = 260.0f;
            m268_curtainScale = 0.0f;
        }
    }
    omSetTra(object, m268_curtainXL, -440.0f, -1000.0f);
    omSetSca(object, m268_curtainScale, 1.0f, 1.0f);
    Hu3DModelPosSet(object->model[1], m268_curtainXR, -440.0f, -1000.0f);
    Hu3DModelScaleSet(object->model[1], m268_curtainScale, 1.0f, 1.0f);
    Hu3DModelPosSet(object->model[2], m268_curtainXL, -440.0f, -999.0f);
    Hu3DModelScaleSet(object->model[2], m268_curtainScale, 1.0f, 1.0f);
    Hu3DModelPosSet(object->model[3], m268_curtainXR, -440.0f, -999.0f);
    Hu3DModelScaleSet(object->model[3], m268_curtainScale, 1.0f, 1.0f);
}

void m268_GambleObjMain(omObjData *object) {
    if (m268_gambleMotPrev != m268_gambleMotNo) {
        Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[m268_gambleMotNo]].motId, 0, 4, 2);
        m268_gambleMotPrev = m268_gambleMotNo;
    }
    m268_gambleMotFrame = Hu3DData[object->model[0]].motTime / 2.0f;
}

void m268_KinopioObjMain(omObjData *object) {
    if (m268_kinopioMotPrev != m268_kinopioMotNo) {
        if (m268_kinopioMotNo != 3) {
            Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[m268_kinopioMotNo]].motId, 0,
                               10, 2);
        } else {
            Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[m268_kinopioMotNo]].motId, 0,
                               10, 0);
        }
        m268_kinopioMotPrev = m268_kinopioMotNo;
    }
    omSetTra(object, m268_boxPosTbl[0].x, m268_boxPosTbl[0].y,
             m268_boxPosTbl[0].z);
    if (m268_shadowGrowF == 1 && m268_kinopioShadowScale < 2.0) {
        m268_kinopioShadowScale = m268_kinopioShadowScale + 0.01f;
    }
    Hu3DModelScaleSet(object->model[1], m268_kinopioShadowScale, 1.0f, m268_kinopioShadowScale);
}

void m268_BoxObjMain(omObjData *object) {
    omSetTra(object, m268_boxPosTbl[0].x, m268_boxPosTbl[0].y,
             m268_boxPosTbl[0].z);
    Hu3DModelPosSet(object->model[1], m268_boxPosTbl[0].x, m268_boxPosTbl[0].y,
                    m268_boxPosTbl[0].z);
}

void m268_KoopaJrObjMain(omObjData *object) {
    if (m268_koopaJrMotPrev != m268_koopaJrMotNo) {
        if (m268_koopaJrMotNo != 4) {
            Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[m268_koopaJrMotNo]].motId, 0,
                               10, 2);
        } else {
            Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[m268_koopaJrMotNo]].motId, 0,
                               10, 0);
        }
        m268_koopaJrMotPrev = m268_koopaJrMotNo;
    }
    omSetTra(object, m268_boxPosTbl[1].x, m268_boxPosTbl[1].y,
             m268_boxPosTbl[1].z);
    if (m268_shadowGrowF == 1 && m268_koopaJrShadowScale < 2.0) {
        m268_koopaJrShadowScale = m268_koopaJrShadowScale + 0.01f;
    }
    Hu3DModelScaleSet(object->model[1], m268_koopaJrShadowScale, 1.0f, m268_koopaJrShadowScale);
}

void m268_Box2ObjMain(omObjData *object) {
    omSetTra(object, m268_boxPosTbl[1].x, m268_boxPosTbl[1].y,
             m268_boxPosTbl[1].z);
    Hu3DModelPosSet(object->model[1], m268_boxPosTbl[1].x,
                    m268_boxPosTbl[1].y, m268_boxPosTbl[1].z);
}

void m268_ExitStartObjMain(omObjData *object) {
    GameGuysMagicBoxesBonus bonus;
    u8 *playerIdx;

    bonus = m268_bonusTbl;
    playerIdx = &m268_playerInfoNo[0];
    GwPlayer[*playerIdx].gameCoin = m268_coinStart;
    if (m268_winF == 1) {
        GwPlayer[*playerIdx].bonusCoin = bonus.amount[m268_roundNo];
    } else {
        GwPlayer[m268_playerInfoNo[0]].bonusCoin = 0;
    }
    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
    HuAudSeqFadeOut(30);
    HuAudFXAllFadeOut(30);
    object->func = m268_ExitObjMain;
}

void m268_ExitObjMain(omObjData *object) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        m268_SpotDispOff();
        m268_BoxSpotReset();
        GMesClose();
        HuWinAllKill();
        HuSprAnimAllKill();
        omOvlReturnEx(1);
    }
}

void m268_ExitCheckObjMain(omObjData *object) {
    if (omSysExitReq == 1) {
        object->func = m268_ExitStartObjMain;
    }
}

void m268_CameraSetup(void) {
    u8 camIndex;

    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
}

void m268_CameraParamSet(GameGuysMagicBoxesCamera *cam, f32 camId, f32 zoom, f32 rotX,
                                         f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ) {
    cam->unk_00 = camId;
    cam->unk_04 = zoom;
    cam->unk_08 = rotX;
    cam->unk_0C = rotY;
    cam->unk_10 = rotZ;
    cam->unk_14 = centerX;
    cam->unk_18 = centerY;
    cam->unk_1C = centerZ;
}

void m268_CameraApply(GameGuysMagicBoxesCamera *cam) {
    if (cam->unk_08 >= 360.0f) {
        cam->unk_08 -= 360.0f;
    } else if (cam->unk_08 < 0.0f) {
        cam->unk_08 += 360.0f;
    }
    if (cam->unk_0C >= 360.0f) {
        cam->unk_0C -= 360.0f;
    } else if (cam->unk_0C < 0.0f) {
        cam->unk_0C += 360.0f;
    }
    if (cam->unk_10 >= 360.0f) {
        cam->unk_10 -= 360.0f;
    } else if (cam->unk_10 < 0.0f) {
        cam->unk_10 += 360.0f;
    }
    Hu3DCameraPerspectiveSet(0, cam->unk_00, 80.0f, 8000.0f);
    CZoom = cam->unk_04;
    CRot.x = cam->unk_08;
    CRot.y = cam->unk_0C;
    CRot.z = cam->unk_10;
    Center.x = cam->unk_14;
    Center.y = cam->unk_18;
    Center.z = cam->unk_1C;
}

void m268_EspSlotCreate(GameGuysMagicBoxesSprite *sprite, s32 spriteIndex, u16 numSlots,
                                         u16 visibility) {
    sprite->unk_00 = espEntry(HuSprAnimDataRead(spriteIndex), 0, numSlots);
    espAttrSet(sprite->unk_00, visibility);
}

void m268_SprParamSet(GameGuysMagicBoxesSprite *sprite, s16 priority, s16 unk04, s16 x,
                                         s16 y, s16 xSub, s16 ySub, f32 unk10, f32 scaleX, f32 scaleY) {
    sprite->priority = priority;
    sprite->unk_04 = unk04;
    sprite->x = x;
    sprite->y = y;
    sprite->xSub = xSub;
    sprite->ySub = ySub;
    sprite->unk_10 = unk10;
    sprite->scaleX = scaleX;
    sprite->scaleY = scaleY;
}

void m268_SprDispSet(GameGuysMagicBoxesSprite *sprite, u8 visible) {
    espPriSet(sprite->unk_00, sprite->priority);
    espTPLvlSet(sprite->unk_00, sprite->unk_04);
    espPosSet(sprite->unk_00, sprite->x + sprite->xSub / 2, sprite->y + sprite->ySub / 2);
    espZRotSet(sprite->unk_00, sprite->unk_10);
    espScaleSet(sprite->unk_00, sprite->scaleX, sprite->scaleY);
    if (visible == 1) {
        espDispOn(sprite->unk_00);
    } else {
        espDispOff(sprite->unk_00);
    }
}

void m268_PlayerInfoInit(void) {
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
    m268_playerInfoNo[0] = i;
    m268_playerInfoNo[1] = GwPlayer[i].pad;
    m268_playerInfoNo[2] = GwPlayer[i].chr;
    if (GwPlayer[i].stat & 1) {
        m268_playerInfoNo[3] = 1;
        m268_playerInfoNo[4] = GwPlayer[i].cpu_difficulty;
        m268_comLevel = GwCommon.unkA0;
        if (m268_comLevel <= 0) {
            m268_comLevel = 0;
        } else if (m268_comLevel >= 2) {
            m268_comLevel = 2;
        }
    } else {
        m268_playerInfoCom[0] = 0;
        m268_playerInfoCom[1] = 0;
    }

    m268_coinStart = m268_playerInfoCoin[0] = GwPlayer[i].gameCoin;
    if (m268_playerInfoCoin[0] >= 999) {
        m268_playerInfoCoin[0] = 999;
    } else if (m268_playerInfoCoin[0] <= 0) {
        m268_playerInfoCoin[0] = 0;
    }
    if (m268_coinStart >= 999) {
        m268_coinStart = 999;
    } else if (m268_coinStart <= 0) {
        m268_coinStart = 0;
    }
}

void m268_BoxSpotLayerInit(void) {
    s16 spriteIndex;
    u16 *pal;
    u8 *pixels;
    s32 i;
    s32 j;

    spriteIndex = HuSprAnimDataRead(0x650005);
    m268_boxSpotGrp = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(m268_boxSpotGrp, 0, spriteIndex, 0);
    HuSprAttrReset(m268_boxSpotGrp, 0, 0xFFFF);
    HuSprAttrSet(m268_boxSpotGrp, 0, 0x1000);
    HuSprPosSet(m268_boxSpotGrp, 0, 160, 120);
    HuSprTPLvlSet(m268_boxSpotGrp, 0, 0);
    HuSprPriSet(m268_boxSpotGrp, 0, 10);
    m268_boxSpotSpr = HuSprGet(m268_boxSpotGrp, 0);
    m268_boxSpotBufTbl[0] = m268_boxSpotSpr->data->pat->data;
    pal = m268_boxSpotSpr->data->pal;
    m268_boxSpotBufTbl[1] = HuMemAllocTag(0x9600, 0x7918);
    m268_boxSpotBufTbl[2] = HuMemAllocTag(0x9600, 0x7918);
    pal[0] = 0x0001;
    pal[1] = 0x003F;
    pal[2] = 0x07C1;
    pal[3] = 0x07FF;
    pal[4] = 0xF801;
    pal[5] = 0xF83F;
    pal[6] = 0xFFC1;
    pal[7] = 0xFFFE;
    for (i = 0; i < 3; i++) {
        pixels = m268_boxSpotBufTbl[i];
        for (j = 0; j < 0x9600; j++) {
            *pixels++ = 0;
        }
    }
    m268_boxSpotBufNo = 0;
}

void m268_BoxSpotDraw(s16 x, s16 y, s16 radius) {
    s32 radiusSq;
    s16 distYSq;
    s16 px;
    s16 py;
    u8 *pixels;

    radiusSq = radius * radius;
    for (py = y - radius; py < y + radius; py++) {
        pixels = m268_boxSpotBufTbl[m268_boxSpotBufNo] + (x - radius) / 2 + py * 160;
        distYSq = (py - y) * (py - y);
        for (px = x - radius; px < x + radius; px++) {
            if (px >= 0 && px < 320 && py >= 0 && py < 240) {
                if ((px - x) * (px - x) + distYSq < radiusSq) {
                    if (px & 1) {
                        *pixels |= 7;
                    } else {
                        *pixels |= 0x70;
                    }
                }
            }
            pixels += px & 1;
        }
    }
}

void m268_BoxSpotErase(s16 x, s16 y, s16 radius) {
    s16 px;
    s16 py;
    u8 *pixels;

    for (py = y - radius; py < y + radius; py++) {
        pixels = m268_boxSpotBufTbl[m268_boxSpotBufNo] + (x - radius) / 2 + py * 160;
        for (px = x - radius; px < x + radius + 1; px += 2) {
            if (px >= 0 && px < 320 && py >= 0 && py < 240) {
                *pixels = 0;
            }
            pixels++;
        }
    }
}

void m268_BoxSpotReset(void) {
    m268_boxSpotSpr->data->pat->data =
        m268_boxSpotBufTbl[0];
}

s16 m268_WinCreate(s16 x, s16 y, s16 lines) {
    s16 win;

    win = HuWinExCreateStyled(x, y, lines);
    HuWinAttrSet(win, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
    HuWinExPriSet(win, 1);
    HuWinMesSpeedSet(win, 0);
    HuWinHomeClear(win);
    return win;
}

void m268_WinKeyWait(s16 win, s16 player, s16 mode) {
    s16 i;

    HuWinComKeyReset();
    while (HuWinStatGet(win) != 0) {
        switch (mode) {
            case 0:
                if (HuPadBtnDown[player] & 0x8000) {
                    HuWinComKeySet(-0x8000, -0x8000, -0x8000, -0x8000);
                }
                break;
            case 1:
                for (i = 0; i < 10; i++) {
                    HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000,
                                    m268_comKeyWaitTbl[m268_comLevel]);
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

s16 m268_WinChoiceGet(s16 win, s16 player, s16 mode, s16 count, u16 cancel) {
    GameGuysMagicBoxesPadValues keys;
    GameGuysMagicBoxesPadValues players;
    s16 i;

    keys = m268_comKeyTbl;
    players = m268_activePlayerTbl;
    switch (mode) {
        case 0:
            keys.v[player] = -1;
            HuWinAttrSet(win, HUWIN_ATTR_COMKEY, HUWIN_ATTR_NONE);
            HuWinActivePlayerSet(win, players.v[player]);
            HuWinComKeySet(keys.v[0], keys.v[1], keys.v[2], keys.v[3]);
            break;
        case 1:
            for (i = 0; i < count; i++) {
                HuWinComKeyWait(0x400, 0x400, 0x400, 0x400,
                                m268_comKeyWaitTbl[m268_comLevel]);
            }
            HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000,
                            m268_comKeyWaitTbl[m268_comLevel]);
            break;
    }
    if (cancel == 0) {
        return HuWinChoiceGet(win, 0, 1);
    } else {
        return HuWinChoiceGet(win, 1, 1);
    }
}

void m268_WinClose(s16 win) {
    HuWinHomeClear(win);
    HuWinExClose(win, 1);
    HuWinExCleanup(win);
}

const GameGuysMagicBoxesBonus m268_bonusTbl = { { 2, 4, 8 } };
const GameGuysMagicBoxesPadValues m268_comKeyTbl = { { 0, 0, 0, 0 } }; // COM keys
const GameGuysMagicBoxesPadValues m268_activePlayerTbl = { { 1, 2, 4, 8 } }; // active players
