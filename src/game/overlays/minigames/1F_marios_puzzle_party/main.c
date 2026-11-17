#include "common.h"
#include "game/audio.h"
#include "game/camsetup.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamework.h"
#include "game/hmfcoll.h"
#include "game/hmfspr.h"
#include "game/input.h"
#include "game/mallocblock.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/window.h"
#include "game/wipe.h"
#include "game/overlays/minigame.h"

// 0x14 byte entry for one space of a Mario's Puzzle Party board path
typedef struct MarioPuzzlePartyPathSpace {
    /* 0x00 */ s32 sprite;
    /* 0x04 */ s32 x;
    /* 0x08 */ s32 y;
    /* 0x0C */ s32 ownerId;
    /* 0x10 */ s32 type;
} MarioPuzzlePartyPathSpace;

// one board path of 40 spaces
typedef struct MarioPuzzlePartyPath {
    /* 0x00 */ MarioPuzzlePartyPathSpace spaces[40];
} MarioPuzzlePartyPath;

// a sparkle effect drifting around the background
typedef struct MarioPuzzlePartySparkle {
    /* 0x00 */ s32 sprGroup;
    /* 0x04 */ s32 spawnMode;
    /* 0x08 */ s32 moveMode;
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ f32 vx;
    /* 0x1C */ f32 vy;
    /* 0x20 */ f32 scale;
} MarioPuzzlePartySparkle; // sizeof 0x24

// initial values for MarioPuzzlePartySparkle
typedef struct MarioPuzzlePartySparkleInit {
    /* 0x00 */ s32 spawnMode;
    /* 0x04 */ s32 moveMode;
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 y;
    /* 0x10 */ f32 vx;
    /* 0x14 */ f32 vy;
} MarioPuzzlePartySparkleInit; // sizeof 0x18

// per-player cursor state
typedef struct MarioPuzzlePartyCursor {
    /* 0x00 */ s32 sprite;
    /* 0x04 */ s32 board;
    /* 0x08 */ s32 blockSprites[2];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 pathIdx;
    /* 0x18 */ s32 spaceIdx;
    /* 0x1C */ s32 blockOwners[2];
    /* 0x24 */ s32 moveDir;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ f32 x;
    /* 0x30 */ f32 y;
} MarioPuzzlePartyCursor; // sizeof 0x34

// a block falling after the spaces beneath it were cleared
typedef struct MarioPuzzlePartyFallingBlock {
    /* 0x00 */ s32 board;
    /* 0x04 */ s32 sprite;
    /* 0x08 */ s32 x;
    /* 0x0C */ s32 y;
    /* 0x10 */ s32 ownerId;
    /* 0x14 */ s32 type;
    /* 0x18 */ s32 unk_18;
} MarioPuzzlePartyFallingBlock; // sizeof 0x1C

// state for a block being squashed by a garbage block landing on it
typedef struct MarioPuzzlePartySquash {
    /* 0x00 */ s32 board;
    /* 0x04 */ s32 pathIdx;
    /* 0x08 */ s32 sprGroup;
    /* 0x0C */ s32 x;
    /* 0x10 */ MarioPuzzlePartyCursor *cursor;
    /* 0x14 */ char unk_14[8];
} MarioPuzzlePartySquash; // sizeof 0x1C

// a piece of debris thrown off a cleared block
typedef struct MarioPuzzlePartyDebris {
    /* 0x00 */ s32 sprite;
    /* 0x04 */ s32 active;
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 y;
    /* 0x10 */ f32 vx;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 vy;
} MarioPuzzlePartyDebris; // sizeof 0x1C

// user data for the score display process
typedef struct MarioPuzzlePartyScoreDisplay {
    /* 0x00 */ s32 board;
    /* 0x04 */ s32 sprGroup;
} MarioPuzzlePartyScoreDisplay;

// a board space queued for removal
typedef struct MarioPuzzlePartyMatch {
    /* 0x00 */ s32 pathIdx;
    /* 0x04 */ s32 spaceIdx;
    /* 0x08 */ s32 type;
} MarioPuzzlePartyMatch; // sizeof 0xC

// colour and scale of the score display for one chain length
typedef struct MarioPuzzlePartyChainColor {
    /* 0x00 */ s32 r;
    /* 0x04 */ s32 g;
    /* 0x08 */ s32 b;
    /* 0x0C */ f32 scale;
} MarioPuzzlePartyChainColor; // sizeof 0x10

// per-player input state; CPU players read their input from here rather than a controller
typedef struct MarioPuzzlePartyPlayerInput {
    /* 0x00 */ s32 heights[4];
    /* 0x10 */ s32 scores[2][4];
    /* 0x30 */ s32 mode;
    /* 0x34 */ s32 targetPath;
    /* 0x38 */ s32 swap;
    /* 0x3C */ s32 delay;
    /* 0x40 */ u16 direction;
    /* 0x42 */ u16 buttons;
} MarioPuzzlePartyPlayerInput; // sizeof 0x44

extern u8 storySceneNo;
extern u8 omAllPauseF;

// screen origin of each player's board
s32 m231_fieldPosTbl[4][2] = { { 16, 224 }, { 84, 224 }, { 152, 224 }, { 220, 224 } };
// board origins used in the endless mode
s32 m231_fieldPosEndlessTbl[4][2] = { { 118, 224 }, { 500, 224 }, { 500, 224 }, { 500, 224 } };
// indexed by chain length - 1
MarioPuzzlePartyChainColor m231_chainColorTbl[8] = {
    { 0, 0, 255, 0.8f },
    { 0, 255, 255, 0.9f },
    { 0, 255, 0, 1.0f },
    { 128, 255, 128, 1.1f },
    { 255, 255, 0, 1.2f },
    { 255, 128, 0, 1.3f },
    { 255, 0, 0, 1.4f },
    { 255, 0, 255, 1.5f }
};
MinigameFlow m231_mgFlow = {
    MG_STATE_OPENING, MINIGAME_4P, MG_TIMER_NONE, MG_TIME_DISP_NONE, FALSE, MG_GAUGE_NONE, MG_RESULT_WIN_1, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    -30, -30, 0, 90, 150
};
MarioPuzzlePartySparkleInit m231_sparkleInitTbl[8] = {
    { 0, 0, 160.0f, -20.0f, 0.0f, 3.0f },
    { 2, 2, 330.0f, -10.0f, -2.0f, 2.0f },
    { 1, 1, 330.0f, 120.0f, -3.0f, 0.0f },
    { 2, 2, 330.0f, 250.0f, -2.0f, -2.0f },
    { 0, 0, 160.0f, 260.0f, 0.0f, -3.0f },
    { 2, 2, -10.0f, 250.0f, 2.0f, -2.0f },
    { 1, 1, -20.0f, 120.0f, 3.0f, 0.0f },
    { 2, 2, -10.0f, -10.0f, 2.0f, 2.0f }
};

MarioPuzzlePartyPath m231_fieldTbl[4][6] BSS;
MarioPuzzlePartyPlayerInput m231_comInputTbl[4] BSS;
MarioPuzzlePartyDebris m231_debrisTbl[160] BSS;

// sprite animations
s32 m231_blockAnimTbl[7] BSS;
s32 m231_sparkleAnim BSS;
s32 m231_signAnim BSS;
s32 m231_loseSignAnim BSS;
s32 m231_fieldBackAnim BSS;
s32 m231_fieldFrameAnim BSS;
s32 m231_recordDigitAnim BSS;
s32 m231_recordLabelAnim BSS;
s32 m231_timerDigitAnim BSS;
s32 m231_bigBlockAnim BSS;
s32 m231_scoreFlyAnim BSS;
s32 m231_headAnim BSS;
s32 m231_headPartAnim BSS;
u8 m231_headPartAnimPad[4] BSS; /* Unreferenced. */
s32 m231_chrFaceAnimTbl[4] BSS;
s32 m231_scoreDigitAnim BSS;
s32 m231_scoreUnitAnim BSS;
s32 m231_chainDigitAnim BSS;
s32 m231_chainLabelAnim BSS;
s32 m231_chainUnitAnim BSS;

s32 m231_winner BSS;

// set once the minigame is ending
s32 m231_exitF BSS;
u8 m231_exitFPad[4] BSS; /* Unreferenced. */

s32 m231_bigBlockFirstTbl[4] BSS;

// number of players that took part in the game
s32 m231_playerNum BSS;
u8 m231_playerNumPad[4] BSS; /* Unreferenced. */

s32 m231_chainTbl[4] BSS;
s32 m231_garbageTbl[4] BSS;
s32 m231_scoreTbl[4] BSS;
s32 m231_clearCntTbl[4] BSS;
s32 m231_chainScoreTbl[4] BSS;

s32 m231_mode BSS;
s32 m231_goalScore BSS;
s32 m231_timer BSS;
u8 m231_timerPad[4] BSS; /* Unreferenced. */

// per-player "still waiting for its turn to finish" flag
s32 m231_doneTbl[4] BSS;

s32 m231_gameOverTbl[4] BSS;
s32 m231_bigBlockCntTbl[4] BSS;
s32 m231_fieldOfsXTbl[4] BSS;
s32 m231_fieldOfsYTbl[4] BSS;
s32 m231_fieldShakeTbl[4] BSS;
s32 m231_fieldSlideTbl[4] BSS;
s32 m231_headGrpTbl[4] BSS;
s32 m231_signGrpTbl[4] BSS;
s32 m231_fieldBackGrpTbl[4] BSS;
s32 m231_fieldFrameGrpTbl[4] BSS;
s32 m231_chrFaceGrpTbl[4] BSS;
s32 m231_bigBlockGrpTbl[4] BSS;
MarioPuzzlePartyCursor m231_cursorTbl[4] BSS;
MarioPuzzlePartyCursor m231_nextTbl[4] BSS;

// per-player process spawned by the minigame setup
Process *m231_playerPrcTbl[4] BSS;

// spaces queued for removal
s32 m231_matchNum BSS;
u8 m231_matchNumPad[4] BSS; /* Unreferenced. */
MarioPuzzlePartyMatch m231_matchTbl[80] BSS;

// sequence of block owner pairs dealt to every player
s32 m231_pairTbl[30][2] BSS;
// per-player position in m231_pairTbl
s32 m231_pairNoTbl[4] BSS;

/* Low halves of the s32 sprite animation ids above (aliased in undefined_syms.txt). */
extern s16 m231_sparkleAnimLo;
extern s16 m231_loseSignAnimLo;
extern s16 m231_recordDigitAnimLo;
extern s16 m231_recordLabelAnimLo;
extern s16 m231_timerDigitAnimLo;
extern s16 m231_bigBlockAnimLo;
extern s16 m231_scoreFlyAnimLo;
extern s16 m231_scoreDigitAnimLo;
extern s16 m231_scoreUnitAnimLo;
extern s16 m231_chainDigitAnimLo;
extern s16 m231_chainLabelAnimLo;
extern s16 m231_chainUnitAnimLo;

void m231_ExitProc(void);
void m231_GameInit(void);
s32 m231_BlockSprCreate(s32 board, s32 ownerId, s32 type, s32 x, s32 y);
void m231_MatchAdd(s32 board, s32 pathIdx, s32 spaceIdx, s32 ownerId, s32 type);
void m231_GarbageClear(s32 board, s32 pathIdx, s32 spaceIdx, s32 ownerId, s32 type);
void m231_MatchClearAll(s32 board);
void m231_ChainDispProc(void);
void m231_ChainResolve(s32 board, s32 arg1);
void m231_BlockFallProc(void);
void m231_BlockSet(s32 board, s32 ownerId, s32 type, s32 pathIdx, s32 spaceIdx);
s32 m231_ColumnHeightGet(s32 board, s32 pathIdx);
s32 m231_ColumnBlockCntGet(s32 board, s32 pathIdx);
s32 m231_ColumnPairCntGet(s32 board, s32 pathIdx);
void m231_SquashKill(void);
void m231_SquashProc(void);
void m231_LoseProc(void);
void m231_PlayerProc(void);
void m231_FieldShakeProc(void);
void m231_FieldDropProc(void);
void m231_DebrisObjMain(omObjData *obj);
void m231_DebrisCreate(s32 board, s32 pathIdx, s32 spaceIdx);
void m231_SparkleKill(void);
void m231_SparkleProc(void);
void m231_CursorDispProc(void);
void m231_FieldSwayProc(void);
void m231_RecordProc(void);
void m231_TimerDisp(s32 group, s32 time);
void m231_TimerProc(void);
void m231_BigBlockFallProc(void);
void m231_MainProc(void);
void m231_SprBatchInit(s16 blockCount);
void m231_SprBatchAdd(s32 spriteData, s16 count);
s16 m231_SprBatchEntryAdd(s16 group, f32 x, f32 y);
void m231_SprBatchPosSet(s16 index, f32 x, f32 y);
void m231_SprBatchScaleSet(s16 index, f32 width, f32 height);
void m231_SprBatchEntryKill(s16 index);
void m231_SprBatchOfsYSet(s32 board, s32 offset);

void m231_ObjectSetup(void) {
    Process *process;
    MarioPuzzlePartySparkle *sparkle;
    s32 camIndex;
    s32 i;

    MapCollInit(50);
    Hu3DQuadPoolInit(&mgQuadPool, 64);
    Hu3DSprModelInit(32);
    omInitObjMan(170, 200);
    omGameSysInit();
    MgFieldStatClear();
    HuWinInit();
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd() & 0xFF;
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 16.0f, 500.0f, 5000.0f);
    CZoom = 800.0f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = 0.0f;
    omAddPrcObj(m231_MainProc, 0x4001, 0x800, 0);
    for (i = 0; i < 4; i++) {
        m231_playerPrcTbl[i] = process = omAddPrcObj(m231_PlayerProc, 0x4001, 0x3000, 0);
        process->user_data = (void *)i;
    }
    m231_playerNum = i;
    omAddPrcObj(m231_FieldSwayProc, 0x4001, 0x800, 0);
    for (i = 0; i < 8; i++) {
        process = omAddPrcObj(m231_SparkleProc, 0x4001, 0x800, 0);
        sparkle = process->user_data = HuMemAlloc(sizeof(MarioPuzzlePartySparkle));
        sparkle->x = m231_sparkleInitTbl[i].x;
        sparkle->y = m231_sparkleInitTbl[i].y;
        sparkle->vx = m231_sparkleInitTbl[i].vx;
        sparkle->vy = m231_sparkleInitTbl[i].vy;
        sparkle->spawnMode = m231_sparkleInitTbl[i].spawnMode;
        sparkle->moveMode = m231_sparkleInitTbl[i].moveMode;
    }
    m231_GameInit();
    omAddPrcObj(m231_ExitProc, 0x4001, 0x800, 0);
    omPrcSetStatBit(omAddPrcObj(m231_CursorDispProc, 0x4001, 0x800, 0), 0xA0);
    MgFlowInit(&m231_mgFlow);
    mgFlowSeqNo = 56;
    WipeCreateIn(WIPE_TYPE_PREV, 16);
}

void m231_ExitProc(void) {
    s32 done = FALSE;

    while (TRUE) {
        if (omSysExitReq == 1) {
            done = TRUE;
        }
        if (done) {
            m231_exitF = 1;
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            HuAudSeqFadeOut(30);
            HuAudFXAllFadeOut(30);
            while (WipeStatGet()) {
                HuPrcVSleep();
            }
            Hu3DBGColorSet(0, 0, 0);
            HuWinAllKill();
            omOvlKill();
            omOvlReturnEx(1);
        }
        HuPrcVSleep();
    }
}

void m231_BlockSet(s32 board, s32 ownerId, s32 type, s32 pathIdx, s32 spaceIdx) {
    MarioPuzzlePartyPathSpace *space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx];
    MarioPuzzlePartyPathSpace *next;

    space->ownerId = ownerId;
    space->x = m231_fieldPosTbl[board][0] + pathIdx * 14;
    space->y = m231_fieldPosTbl[board][1] - spaceIdx * 7;
    space->type = type;
    space->sprite = m231_BlockSprCreate(board, space->ownerId, space->type, space->x, space->y);
    if (type == 1) {
        next = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx + 1];
        next->ownerId = ownerId;
        next->x = space->x;
        next->y = space->y - 7;
        next->type = 2;
        next->sprite = space->sprite;
    }
}

u16 m231_InputBtnGet(s32 playerIndex) {
    u16 buttons;

    if (!(GwPlayer[playerIndex].stat & PLAYER_IS_CPU)) {
        buttons = HuPadBtn[GwPlayer[playerIndex].pad];
        buttons &= ~(U_JPAD | D_JPAD | L_JPAD | R_JPAD);
        if (HuPadStkX[GwPlayer[playerIndex].pad] > 30.0f) {
            buttons |= R_JPAD;
        }
        if (HuPadStkX[GwPlayer[playerIndex].pad] < -30.0f) {
            buttons |= L_JPAD;
        }
        if (HuPadStkY[GwPlayer[playerIndex].pad] < -30.0f) {
            buttons |= D_JPAD;
        }
    } else {
        buttons = m231_comInputTbl[playerIndex].direction;
    }
    return buttons;
}

u16 m231_InputBtnDownGet(s32 playerIndex, u16 bits) {
    u16 result;

    if (!(GwPlayer[playerIndex].stat & PLAYER_IS_CPU)) {
        result = HuPadBtnDown[GwPlayer[playerIndex].pad];
        result &= bits;
    } else {
        MarioPuzzlePartyPlayerInput *input = &m231_comInputTbl[playerIndex];
        result = input->buttons;
        result &= bits;
        input->buttons &= ~bits;
    }
    return result;
}

void m231_GameInit(void) {
    void *data;
    s32 i;
    s32 j;
    s32 k;
    u16 sprite;
    s32 swap;
    MarioPuzzlePartyPathSpace *space;
    s32 *pair;

    switch (storySceneNo) {
        case 1:
            m231_mode = 1;
            m231_goalScore = mgModeCoinRate;
            break;
        case 2:
            m231_mode = 2;
            m231_goalScore = 9999;
            break;
        default:
            m231_mode = 0;
            m231_goalScore = 100;
            break;
    }
    sprite = espEntry(HuSprAnimDataRead(0x400000), 0, 1);
    espAttrSet(sprite, HUSPR_ATTR_BG);
    espPosSet(sprite, 160, 120);
    espPriSet(sprite, 0xFFFF);
    data = DataRead(0x210028);
    m231_sparkleAnim = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x400001);
    m231_signAnim = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x400002);
    m231_loseSignAnim = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x400003);
    m231_fieldBackAnim = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x400004);
    m231_fieldFrameAnim = HuSprAnimRead(data);
    DataClose(data);
    for (i = 0; i < 4; i++) {
        data = DataRead((GwPlayer[i].chr + 5) | 0x400000);
        m231_chrFaceAnimTbl[i] = HuSprAnimRead(data);
        DataClose(data);
    }
    data = DataRead(0x400014);
    m231_bigBlockAnim = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x400015);
    m231_scoreFlyAnim = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x400016);
    m231_headAnim = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x400017);
    m231_headPartAnim = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x40001A);
    m231_scoreDigitAnim = HuSprAnimRead(data);
    DataClose(data);
    if (m231_mode == 0) {
        data = DataRead(0x400019);
    } else {
        data = DataRead(0x400018);
    }
    m231_scoreUnitAnim = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x40001B);
    m231_chainDigitAnim = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x40001C);
    m231_chainLabelAnim = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x40001D);
    m231_chainUnitAnim = HuSprAnimRead(data);
    DataClose(data);
    m231_SprBatchInit(29);
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 7; i++) {
            m231_SprBatchAdd((i + 13) | 0x400000, 50);
        }
    }
    m231_SprBatchAdd(0x40001E, 160);
    for (i = 0; i < 7; i++) {
        data = DataRead((i + 13) | 0x400000);
        m231_blockAnimTbl[i] = HuSprAnimRead(data);
        DataClose(data);
    }
    if (m231_mode == 2) {
        data = DataRead(0x31);
        m231_recordDigitAnim = HuSprAnimRead(data);
        DataClose(data);
        espPalColorSet(m231_recordDigitAnimLo, 0.0f, 1.0f, 0.0f);
        data = DataRead(0x40001F);
        m231_recordLabelAnim = HuSprAnimRead(data);
        DataClose(data);
        espPalColorSet(m231_recordLabelAnimLo, 0.0f, 1.0f, 0.0f);
        omAddPrcObj(m231_RecordProc, 0x4001, 0, 0);
        data = DataRead(0x31);
        m231_timerDigitAnim = HuSprAnimRead(data);
        DataClose(data);
        omAddPrcObj(m231_TimerProc, 0x4001, 0, 0);
        omAddPrcObj(m231_BigBlockFallProc, 0x4001, 0, 0)->user_data = (void *)30;
        omAddPrcObj(m231_BigBlockFallProc, 0x4001, 0, 0)->user_data = (void *)70;
        omAddPrcObj(m231_BigBlockFallProc, 0x4001, 0, 0)->user_data = (void *)100;
        omAddPrcObj(m231_BigBlockFallProc, 0x4001, 0, 0)->user_data = (void *)220;
        omAddPrcObj(m231_BigBlockFallProc, 0x4001, 0, 0)->user_data = (void *)270;
        omAddPrcObj(m231_BigBlockFallProc, 0x4001, 0, 0)->user_data = (void *)300;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 6; j++) {
            for (k = 0; k < 40; k++) {
                space = &m231_fieldTbl[i][j].spaces[k];
                space->ownerId = -1;
                if (j == 0 || j == 5 || k == 0) {
                    space->type = -1;
                } else {
                    space->type = 0;
                }
            }
        }
    }
    m231_exitF = 0;
    for (i = 0; i < 4; i++) {
        m231_garbageTbl[i] = 0;
        m231_doneTbl[i] = 0;
        m231_gameOverTbl[i] = 0;
        m231_bigBlockCntTbl[i] = 0;
        m231_fieldOfsXTbl[i] = m231_fieldOfsYTbl[i] = 0;
        m231_pairNoTbl[i] = 0;
        m231_fieldSlideTbl[i] = 0;
    }
    for (i = 0; i < 30; i++) {
        pair = m231_pairTbl[i];
        pair[0] = (u8)(rand8() % 6);
        do {
            pair[1] = (u8)(rand8() % 6);
        } while (pair[0] == pair[1]);
    }
    for (i = 0; i < 8; i++) {
        j = rand8() & 3;
        do {
            k = rand8() & 3;
        } while (j == k);
        swap = m231_fieldPosTbl[j][0];
        m231_fieldPosTbl[j][0] = m231_fieldPosTbl[k][0];
        m231_fieldPosTbl[k][0] = swap;
    }
    if (m231_mode == 2) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 2; j++) {
                m231_fieldPosTbl[i][j] = m231_fieldPosEndlessTbl[i][j];
            }
        }
        for (i = 1; i < m231_playerNum; i++) {
            for (j = 1; j < 20; j += 2) {
                m231_BlockSet(i, 1, 3, 1, j);
                m231_BlockSet(i, 0, 3, 2, j);
                m231_BlockSet(i, 1, 3, 3, j);
                m231_BlockSet(i, 0, 3, 4, j);
                m231_BlockSet(i, 0, 3, 1, j + 1);
                m231_BlockSet(i, 1, 3, 2, j + 1);
                m231_BlockSet(i, 0, 3, 3, j + 1);
                m231_BlockSet(i, 1, 3, 4, j + 1);
            }
        }
    }
}

s32 m231_BlockSprCreate(s32 board, s32 ownerId, s32 type, s32 x, s32 y) {
    s32 sprite = m231_SprBatchEntryAdd(board * 7 + ownerId, x, y);

    if (type != 1) {
        m231_SprBatchScaleSet(sprite, 1.0f, 0.5f);
    }
    return sprite;
}

s32 m231_PairMoveCheck(s32 board, MarioPuzzlePartyCursor *cursor, s32 dir) {
    s32 result = TRUE;
    MarioPuzzlePartyPath *path;
    s32 offset;
    s32 pathIdx;
    s32 spaceIdx;

    if (dir > 0) {
        offset = 14;
    } else {
        offset = -14;
    }
    pathIdx = (offset + cursor->x - m231_fieldPosTbl[board][0]) / 14.0f;
    spaceIdx = (m231_fieldPosTbl[board][1] - cursor->y) / 7.0f;

    path = &m231_fieldTbl[board][pathIdx];
    if (path->spaces[spaceIdx].type == 0) {
        result = FALSE;
    }
    return result;
}

s32 m231_BigBlockMoveCheck(s32 board, MarioPuzzlePartyCursor *cursor, s32 dir) {
    s32 result = TRUE;
    MarioPuzzlePartyPath *path;
    s32 offset;
    s32 pathIdx;
    s32 spaceIdx;

    if (dir > 0) {
        offset = 14;
    } else {
        offset = -28;
    }
    pathIdx = (offset + cursor->x - m231_fieldPosTbl[board][0]) / 14.0f;
    spaceIdx = (m231_fieldPosTbl[board][1] - (cursor->y + 14.0f)) / 7.0f;

    path = &m231_fieldTbl[board][pathIdx];
    if (path->spaces[spaceIdx].type == 0) {
        result = FALSE;
    }
    return result;
}

s32 m231_PairFallCheck(s32 board, MarioPuzzlePartyCursor *cursor, s32 dy) {
    s32 result = TRUE;
    MarioPuzzlePartyPathSpace *space;
    MarioPuzzlePartyPathSpace *other;
    s32 pathIdx;
    s32 spaceIdx;
    s32 otherIdx;

    cursor->y += dy;
    pathIdx = (cursor->x - m231_fieldPosTbl[board][0]) / 14.0f;
    spaceIdx = (m231_fieldPosTbl[board][1] - cursor->y) / 7.0f;
    space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx];
    if (cursor->moveDir != 0) {
        if (pathIdx * 14 - cursor->x > 0.0f) {
            otherIdx = pathIdx - 1;
        } else {
            otherIdx = pathIdx + 1;
        }
        other = &m231_fieldTbl[board][otherIdx].spaces[spaceIdx];
        if (space->type == 0 && other->type == 0) {
            cursor->pathIdx = pathIdx;
            cursor->spaceIdx = spaceIdx;
            result = FALSE;
        }
    } else if (space->type == 0) {
        cursor->pathIdx = pathIdx;
        cursor->spaceIdx = spaceIdx;
        result = FALSE;
    }
    if (result) {
        cursor->y -= dy;
    }
    return result;
}

s32 m231_BigBlockFallCheck(s32 board, MarioPuzzlePartyCursor *cursor, s32 dy) {
    s32 result = TRUE;
    MarioPuzzlePartyPathSpace *left;
    MarioPuzzlePartyPathSpace *right;
    MarioPuzzlePartyPathSpace *other;
    s32 pathIdx;
    s32 spaceIdx;
    s32 otherIdx;

    cursor->y += dy;
    spaceIdx = (m231_fieldPosTbl[board][1] - cursor->y - 14.0f) / 7.0f;
    pathIdx = (cursor->x - (m231_fieldPosTbl[board][0] + 22)) / 14.0f + 1.0f;
    left = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx];
    right = &m231_fieldTbl[board][pathIdx + 1].spaces[spaceIdx];
    if (cursor->moveDir != 0) {
        if (cursor->moveDir < 0) {
            otherIdx = pathIdx - 1;
        } else {
            otherIdx = pathIdx + 2;
        }
        other = &m231_fieldTbl[board][otherIdx].spaces[spaceIdx];
        if (left->type == 0 && right->type == 0 && other->type == 0) {
            result = FALSE;
        }
    } else if (left->type == 0 && right->type == 0) {
        result = FALSE;
    }
    if (result) {
        cursor->y -= dy;
    }
    return result;
}

s32 m231_ColumnHeightGet(s32 board, s32 pathIdx) {
    s32 i = 1;
    MarioPuzzlePartyPath *path = &m231_fieldTbl[board][pathIdx];

    for (; i < 40; i++) {
        if (path->spaces[i].type == 0) {
            break;
        }
    }
    return i;
}

s32 m231_ColumnBlockCntGet(s32 board, s32 pathIdx) {
    s32 i = 1;
    s32 count = 0;
    MarioPuzzlePartyPath *path = &m231_fieldTbl[board][pathIdx];
    MarioPuzzlePartyPathSpace *space;

    for (; i < 40; i++) {
        space = &path->spaces[i];
        if (space->type == 0) {
            break;
        }
        if (space->type == 1) {
            i++;
            count++;
        }
        if (space->type == 3) {
            count++;
        }
    }
    return count;
}

s32 m231_ColumnPairCntGet(s32 board, s32 pathIdx) {
    s32 i = 1;
    s32 count = 0;
    MarioPuzzlePartyPath *path = &m231_fieldTbl[board][pathIdx];

    for (; i < 40; i++) {
        if (path->spaces[i].type == 0) {
            break;
        }
        if (path->spaces[i].type == 1) {
            count++;
            i++;
        }
    }
    return count;
}

s32 m231_MatchFind(s32 pathIdx, s32 spaceIdx) {
    s32 i;

    for (i = 0; i < m231_matchNum; i++) {
        MarioPuzzlePartyMatch *match = &m231_matchTbl[i];

        if (pathIdx == match->pathIdx && spaceIdx == match->spaceIdx) {
            return TRUE;
        }
        if (match->type == 1 && pathIdx == match->pathIdx && spaceIdx == match->spaceIdx + 1) {
            return TRUE;
        }
    }
    return FALSE;
}

void m231_BlockClear(s32 board, s32 pathIdx, s32 spaceIdx) {
    MarioPuzzlePartyPathSpace *space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx];

    if (space->ownerId != 6) {
        m231_bigBlockCntTbl[board]++;
    }
    m231_DebrisCreate(board, pathIdx, spaceIdx);
    if (space->type == 2) {
        spaceIdx--;
        space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx];
    }
    m231_SprBatchEntryKill(space->sprite);
    space->sprite = -1;
    if (space->type == 1) {
        space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx + 1];
        space->ownerId = -1;
        space->type = 0;
    }
    space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx];
    space->ownerId = -1;
    space->type = 0;
}

void m231_MatchAdd(s32 board, s32 pathIdx, s32 spaceIdx, s32 ownerId, s32 type) {
    MarioPuzzlePartyPathSpace *space;

    if (type == 2) {
        spaceIdx--;
        type = 1;
    }
    m231_matchTbl[m231_matchNum].pathIdx = pathIdx;
    m231_matchTbl[m231_matchNum].spaceIdx = spaceIdx;
    m231_matchTbl[m231_matchNum].type = type;
    m231_matchNum++;
    if (m231_matchNum >= 80) {
        osSyncPrintf("BlockDelete Over\n");
        while (TRUE) {
            HuPrcVSleep();
        }
    }
    if (ownerId == 6) {
        return;
    }
    if (!m231_MatchFind(pathIdx - 1, spaceIdx)) {
        space = &m231_fieldTbl[board][pathIdx - 1].spaces[spaceIdx];
        if (space->ownerId == ownerId) {
            m231_MatchAdd(board, pathIdx - 1, spaceIdx, ownerId, space->type);
        }
    }
    if (!m231_MatchFind(pathIdx + 1, spaceIdx)) {
        space = &m231_fieldTbl[board][pathIdx + 1].spaces[spaceIdx];
        if (space->ownerId == ownerId) {
            m231_MatchAdd(board, pathIdx + 1, spaceIdx, ownerId, space->type);
        }
    }
    if (!m231_MatchFind(pathIdx, spaceIdx - 1)) {
        space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx - 1];
        if (space->ownerId == ownerId) {
            m231_MatchAdd(board, pathIdx, spaceIdx - 1, ownerId, space->type);
        }
    }
    if (type == 1) {
        if (!m231_MatchFind(pathIdx - 1, spaceIdx + 1)) {
            space = &m231_fieldTbl[board][pathIdx - 1].spaces[spaceIdx + 1];
            if (space->ownerId == ownerId) {
                m231_MatchAdd(board, pathIdx - 1, spaceIdx + 1, ownerId, space->type);
            }
        }
        if (!m231_MatchFind(pathIdx + 1, spaceIdx + 1)) {
            space = &m231_fieldTbl[board][pathIdx + 1].spaces[spaceIdx + 1];
            if (space->ownerId == ownerId) {
                m231_MatchAdd(board, pathIdx + 1, spaceIdx + 1, ownerId, space->type);
            }
        }
        if (!m231_MatchFind(pathIdx, spaceIdx + 2)) {
            space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx + 2];
            if (space->ownerId == ownerId) {
                m231_MatchAdd(board, pathIdx, spaceIdx + 2, ownerId, space->type);
            }
        }
    } else {
        if (!m231_MatchFind(pathIdx, spaceIdx + 1)) {
            space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx + 1];
            if (space->ownerId == ownerId) {
                m231_MatchAdd(board, pathIdx, spaceIdx + 1, ownerId, space->type);
            }
        }
    }
}

void m231_GarbageClear(s32 board, s32 pathIdx, s32 spaceIdx, s32 ownerId, s32 type) {
    MarioPuzzlePartyPathSpace *space;

    if (type == 2) {
        spaceIdx--;
        type = 1;
    }
    space = &m231_fieldTbl[board][pathIdx - 1].spaces[spaceIdx];
    if (space->ownerId == ownerId) {
        m231_BlockClear(board, pathIdx - 1, spaceIdx);
    }
    space = &m231_fieldTbl[board][pathIdx + 1].spaces[spaceIdx];
    if (space->ownerId == ownerId) {
        m231_BlockClear(board, pathIdx + 1, spaceIdx);
    }
    space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx - 1];
    if (space->ownerId == ownerId) {
        m231_BlockClear(board, pathIdx, spaceIdx - 1);
    }
    if (type == 1) {
        space = &m231_fieldTbl[board][pathIdx - 1].spaces[spaceIdx + 1];
        if (space->ownerId == ownerId) {
            m231_BlockClear(board, pathIdx - 1, spaceIdx + 1);
        }
        space = &m231_fieldTbl[board][pathIdx + 1].spaces[spaceIdx + 1];
        if (space->ownerId == ownerId) {
            m231_BlockClear(board, pathIdx + 1, spaceIdx + 1);
        }
        space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx + 2];
        if (space->ownerId == ownerId) {
            m231_BlockClear(board, pathIdx, spaceIdx + 2);
        }
    } else {
        space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx + 1];
        if (space->ownerId == ownerId) {
            m231_BlockClear(board, pathIdx, spaceIdx + 1);
        }
    }
}

void m231_MatchClearAll(s32 board) {
    s32 i;

    for (i = 0; i < m231_matchNum; i++) {
        MarioPuzzlePartyMatch *match = &m231_matchTbl[i];

        m231_BlockClear(board, match->pathIdx, match->spaceIdx);
        m231_chainScoreTbl[board] += m231_chainTbl[board] + 1;
        m231_clearCntTbl[board] += m231_chainTbl[board] + 1;
        m231_GarbageClear(board, match->pathIdx, match->spaceIdx, 6, match->type);
    }
}

void m231_ChainDispProc(void) {
    s32 lastChain = -1;
    s32 group;
    s32 r = 0;
    s32 g = 0;
    s32 b = 0;
    f32 scale = 0.0f;
    MarioPuzzlePartyChainColor *color = NULL;
    s32 board = (s32)HuPrcCurrentGet()->user_data;
    s32 chain;
    s32 digits;
    s32 digit;
    s32 divisor;
    s32 started;
    s32 flash;
    s32 alpha;
    s32 x;
    s32 i;

    group = HuSprGrpCreate(6, 5);
    HuSprGrpMemberSet(group, 1, m231_chainLabelAnimLo, 0);
    HuSprAnimModeSet(group, 1, HUSPR_ANIM_MODE_STOP);
    HuSprPosSet(group, 1, 0, 0);
    HuSprAttrReset(group, 1, 0xFFFF);
    HuSprAttrSet(group, 1, HUSPR_ATTR_XLU | HUSPR_ATTR_FILTER_BILERP);
    HuSprPriSet(group, 1, 0x100);
    HuSprColorSet(group, 1, 255, 255, 255);
    HuSprTPLvlSet(group, 1, 255);
    HuSprParentSet(group, 1, 0);
    for (i = 2; i < 5; i++) {
        HuSprGrpMemberSet(group, i, m231_chainDigitAnimLo, 0);
        HuSprAnimModeSet(group, i, HUSPR_ANIM_MODE_STOP);
        HuSprPosSet(group, i, 0, 0);
        HuSprAttrReset(group, i, 0xFFFF);
        HuSprAttrSet(group, i, HUSPR_ATTR_XLU | HUSPR_ATTR_FILTER_BILERP);
        HuSprPriSet(group, i, 0x100);
        HuSprColorSet(group, i, 255, 255, 255);
        HuSprTPLvlSet(group, i, 255);
        HuSprParentSet(group, i, 0);
    }
    HuSprGrpMemberSet(group, 5, m231_chainUnitAnimLo, 0);
    HuSprAnimModeSet(group, 5, HUSPR_ANIM_MODE_STOP);
    HuSprPosSet(group, 5, 0, 0);
    HuSprAttrReset(group, 5, 0xFFFF);
    HuSprAttrSet(group, 5, HUSPR_ATTR_XLU | HUSPR_ATTR_FILTER_BILERP);
    HuSprPriSet(group, 5, 0x100);
    HuSprColorSet(group, 5, 255, 255, 255);
    HuSprTPLvlSet(group, 5, 255);
    HuSprParentSet(group, 5, 0);
    HuSprGrpMemberSet(group, 0, m231_chainLabelAnimLo, 0);
    HuSprDispOff(group, 0);
    HuSprParentSet(group, 0, -1);
    HuSprPosSet(group, 0, m231_fieldPosTbl[board][0] + 42, m231_fieldPosTbl[board][1] - 70);
    HuSprScaleSet(group, 0, scale, scale);
    flash = TRUE;
    while (TRUE) {
        if (m231_clearCntTbl[board] == 0 || m231_gameOverTbl[board] == 1) {
            break;
        }
        chain = m231_chainTbl[board];
        if (chain > 8) {
            chain = 8;
        }
        color = &m231_chainColorTbl[chain - 1];
        r = color->r;
        g = color->g;
        b = color->b;
        scale = color->scale;
        if (chain == 1 && GwPlayer[0].coin == 11) {
            r = GwPlayer[1].coin;
            g = GwPlayer[2].coin;
            b = GwPlayer[3].coin;
        }
        for (i = 10, digits = 1; i <= 1000; i *= 10) {
            if (i < m231_chainScoreTbl[board]) {
                digits++;
            }
        }
        x = -(digits * 18 + 54) / 2 + 9;
        HuSprPosSet(group, 1, x, 0);
        HuSprScaleSet(group, 1, scale, scale);
        if (flash) {
            HuSprTPLvlSet(group, 1, 255);
            HuSprColorSet(group, 1, r, g, b);
        } else {
            HuSprTPLvlSet(group, 1, 128);
        }
        for (i = 2; i < 5; i++) {
            HuSprDispOff(group, i);
        }
        for (i = 4, divisor = 100, started = FALSE; i >= 2; divisor /= 10) {
            digit = (m231_chainScoreTbl[board] / divisor) % 10;
            if (digit > 0 || divisor == 1 || started) {
                started = TRUE;
                HuSprDispOn(group, i);
                HuSprGrpMemberSet(group, i, m231_chainDigitAnimLo, digit);
                x += 18;
                HuSprPosSet(group, i, x, 0);
                HuSprScaleSet(group, i, scale, scale);
                if (flash) {
                    HuSprTPLvlSet(group, i, 255);
                    HuSprColorSet(group, i, r, g, b);
                } else {
                    HuSprTPLvlSet(group, i, 128);
                }
            }
            i--;
        }
        x += 27;
        HuSprPosSet(group, 5, x, 0);
        HuSprScaleSet(group, 5, scale, scale);
        if (flash) {
            HuSprTPLvlSet(group, 5, 255);
            HuSprColorSet(group, 5, r, g, b);
        } else {
            HuSprTPLvlSet(group, 5, 128);
        }
        flash = (flash + 1) & 1;
        if (lastChain != m231_chainTbl[board]) {
            lastChain = m231_chainTbl[board];
            m231_scoreTbl[board] += m231_chainScoreTbl[board];
        }
        HuPrcVSleep();
    }
    for (alpha = 255; alpha > 0; alpha -= 10) {
        scale += 0.15f;
        HuSprTPLvlSet(group, 1, alpha);
        HuSprScaleSet(group, 1, color->scale, scale);
        HuSprColorSet(group, 1, r, g, b);
        for (i = 2; i < 5; i++) {
            HuSprTPLvlSet(group, i, alpha);
            HuSprScaleSet(group, i, color->scale, scale);
            HuSprColorSet(group, i, r, g, b);
        }
        HuSprTPLvlSet(group, 5, alpha);
        HuSprScaleSet(group, 5, color->scale, scale);
        HuSprColorSet(group, 5, r, g, b);
        HuPrcVSleep();
    }
    HuSprGrpKill(group);
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m231_ChainResolve(s32 board, s32 arg1) {
    MarioPuzzlePartyPathSpace *space;
    MarioPuzzlePartyFallingBlock *block;
    Process *process;
    s32 first = TRUE;
    s32 found;
    s32 saved;
    s32 pathIdx;
    s32 spaceIdx;
    s32 chain;

    while (TRUE) {
        saved = m231_chainScoreTbl[board];
        m231_chainScoreTbl[board] = 0;
        for (pathIdx = 1, found = FALSE; pathIdx < 5; pathIdx++) {
            for (spaceIdx = 1; spaceIdx < 40; spaceIdx++) {
                space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx];
                if (space->type == 1 || space->type == 3) {
                    m231_matchNum = 0;
                    m231_MatchAdd(board, pathIdx, spaceIdx, space->ownerId, space->type);
                    if (m231_matchNum >= 2) {
                        m231_MatchClearAll(board);
                        found = TRUE;
                        if (first && arg1) {
                            first = FALSE;
                            omAddPrcObj(m231_ChainDispProc, 0x4001, 0x800, 0)->user_data = (void *)board;
                        }
                    }
                }
            }
        }
        if (found) {
            m231_chainTbl[board]++;
            HuAudPlayerFXPlay(0x3F8, board);
            chain = m231_chainTbl[board] - 1;
            if (chain < 0 || chain > 4) {
                chain = 4;
            }
            HuAudPlayerFXPlay(chain + 0x400, board);
            omVibrate(board, 2, 3, 10);
            for (pathIdx = 1; pathIdx < 5; pathIdx++) {
                for (spaceIdx = 1; spaceIdx < 40; spaceIdx++) {
                    space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx];
                    if (space->type == 0) {
                        break;
                    }
                }
                for (; spaceIdx < 40; spaceIdx++) {
                    space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx];
                    if (space->type == 1 || space->type == 3) {
                        process = omAddPrcObj(m231_BlockFallProc, 0x4001, 0x800, 0);
                        HuPrcChildLink(HuPrcCurrentGet(), process);
                        block = process->user_data = HuMemAlloc(sizeof(MarioPuzzlePartyFallingBlock));
                        block->board = board;
                        block->sprite = space->sprite;
                        block->x = m231_fieldPosTbl[board][0] + pathIdx * 14;
                        block->y = m231_fieldPosTbl[board][1] - spaceIdx * 7;
                        block->ownerId = space->ownerId;
                        block->type = space->type;
                        block->unk_18 = 0;
                    }
                }
            }
            HuPrcChildWatch();
        } else {
            m231_chainScoreTbl[board] = saved;
            break;
        }
    }
}

void m231_PairLand(s32 board, MarioPuzzlePartyCursor *cursor) {
    MarioPuzzlePartyPathSpace *space;
    s32 i;

    for (i = 0; i < 2; i++) {
        space = &m231_fieldTbl[board][cursor->pathIdx].spaces[i + cursor->spaceIdx];
        space->sprite = cursor->blockSprites[0];
        space->x = cursor->x;
        space->y = cursor->y;
        space->ownerId = cursor->blockOwners[0];
        space->type = i + 1;
    }
    for (i = 0; i < 2; i++) {
        space = &m231_fieldTbl[board][cursor->pathIdx].spaces[cursor->spaceIdx + 2 + i];
        space->sprite = cursor->blockSprites[1];
        space->x = cursor->x;
        space->y = cursor->y - 14.0f;
        space->ownerId = cursor->blockOwners[1];
        space->type = i + 1;
    }
    m231_ChainResolve(board, 1);
}

s32 m231_NeighborMatchCnt(s32 board, s32 type, s32 ownerId, s32 pathIdx, s32 spaceIdx) {
    MarioPuzzlePartyPathSpace *space;
    s32 count = 0;

    if (ownerId != 6) {
        space = &m231_fieldTbl[board][pathIdx - 1].spaces[spaceIdx];
        count = space->ownerId == ownerId;
        space = &m231_fieldTbl[board][pathIdx + 1].spaces[spaceIdx];
        count += space->ownerId == ownerId;
        space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx - 1];
        count += space->ownerId == ownerId;
        if (type == 1) {
            space = &m231_fieldTbl[board][pathIdx - 1].spaces[spaceIdx + 1];
            count += space->ownerId == ownerId;
            space = &m231_fieldTbl[board][pathIdx + 1].spaces[spaceIdx + 1];
            count += space->ownerId == ownerId;
            space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx + 2];
            count += space->ownerId == ownerId;
        } else {
            space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx + 1];
            count += space->ownerId == ownerId;
        }
    }
    return count;
}

void m231_BlockFallKill(void) {
    MarioPuzzlePartyFallingBlock *block = HuPrcCurrentGet()->user_data;

    if (m231_winner == block->board && m231_gameOverTbl[m231_winner] != 0) {
        m231_DebrisCreate(m231_winner,
                                          (block->x - m231_fieldPosTbl[m231_winner][0]) / 14,
                                          (m231_fieldPosTbl[m231_winner][1] - block->y) / 7);
        m231_SprBatchEntryKill(block->sprite);
    }
    HuMemDelayFree(HuPrcCurrentGet()->user_data);
}

void m231_BlockFallProc(void) {
    MarioPuzzlePartyFallingBlock *block = HuPrcCurrentGet()->user_data;
    MarioPuzzlePartyPathSpace *space;
    MarioPuzzlePartyPathSpace *below;
    s32 landed;
    s32 row;
    s32 pathIdx;
    s32 spaceIdx;
    s32 type;
    s32 ownerId;
    f32 speed;

    omPrcSetDestructor(HuPrcCurrentGet(), m231_BlockFallKill);
    pathIdx = (block->x - m231_fieldPosTbl[block->board][0]) / 14;
    spaceIdx = (m231_fieldPosTbl[block->board][1] - block->y) / 7;
    space = &m231_fieldTbl[block->board][pathIdx].spaces[spaceIdx];
    type = space->type;
    ownerId = space->ownerId;
    space->ownerId = -1;
    space->type = 0;
    if (type == 1) {
        below = &m231_fieldTbl[block->board][pathIdx].spaces[spaceIdx + 1];
        below->ownerId = -1;
        below->type = 0;
    }
    landed = FALSE;
    while (TRUE) {
        pathIdx = (block->x - m231_fieldPosTbl[block->board][0]) / 14;
        spaceIdx = (m231_fieldPosTbl[block->board][1] - block->y) / 7;
        below = &m231_fieldTbl[block->board][pathIdx].spaces[spaceIdx - 1];
        if (below->type == 0) {
            speed = 1.0f;
            while (TRUE) {
                block->y = block->y + speed;
                speed += 0.5f;
                if (speed > 6.0f) {
                    speed = 6.0f;
                }
                row = (m231_fieldPosTbl[block->board][1] - block->y) / 7;
                below = &m231_fieldTbl[block->board][pathIdx].spaces[row];
                if (below->type != 0) {
                    space = &m231_fieldTbl[block->board][pathIdx].spaces[row + 1];
                    block->y = m231_fieldPosTbl[block->board][1] - (row + 1) * 7;
                    space->y = block->y;
                    m231_SprBatchPosSet(block->sprite, block->x, block->y);
                    space->sprite = block->sprite;
                    space->ownerId = ownerId;
                    space->type = type;
                    if (type == 1) {
                        space = &m231_fieldTbl[block->board][pathIdx].spaces[row + 2];
                        space->sprite = block->sprite;
                        space->ownerId = ownerId;
                        space->type = 2;
                    }
                    break;
                } else {
                    m231_SprBatchPosSet(block->sprite, block->x, block->y);
                    HuPrcVSleep();
                }
            }
        } else {
            landed = TRUE;
        }
        HuPrcVSleep();
        if (landed) {
            break;
        }
    }
    pathIdx = (block->x - m231_fieldPosTbl[block->board][0]) / 14;
    spaceIdx = (m231_fieldPosTbl[block->board][1] - block->y) / 7;
    if ((spaceIdx >= 20 && type == 1) || (spaceIdx >= 21 && type == 3)) {
        m231_BlockClear(block->board, pathIdx, spaceIdx);
    } else if (block->unk_18 != 0) {
        HuAudPlayerFXPlay(0x3F9, block->board);
    }
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m231_SquashKill(void) {
    HuMemDelayFree(HuPrcCurrentGet()->user_data);
}

void m231_SquashProc(void) {
    MarioPuzzlePartySquash *squash = HuPrcCurrentGet()->user_data;
    MarioPuzzlePartyPathSpace *space;
    MarioPuzzlePartyPathSpace *other;
    s32 i = 1;
    s32 j;
    s32 squashing;
    s32 more;
    f32 scale;

    omPrcSetDestructor(HuPrcCurrentGet(), m231_SquashKill);
    while (TRUE) {
        space = &m231_fieldTbl[squash->board][squash->pathIdx].spaces[i];
        if (space->type == 0 || space->type == 1) {
            break;
        }
        i++;
    }
    if (space->type != 0) {
        squashing = TRUE;
        scale = 1.0f;
        do {
            scale -= 0.2f;
            if (scale <= 0.5f) {
                scale = 0.5f;
                squashing = FALSE;
            }
            m231_SprBatchScaleSet(space->sprite, 1.0f, scale);
            j = i + 2;
            more = TRUE;
            do {
                other = &m231_fieldTbl[squash->board][squash->pathIdx].spaces[j];
                switch (other->type) {
                    case 1:
                        other->y = space->y - scale * 7.0f * 2.0f - (j - (i + 2)) * 7;
                        j++;
                        m231_SprBatchPosSet(
                            other->sprite, m231_fieldPosTbl[squash->board][0] + squash->pathIdx * 14,
                            other->y);
                        j++;
                        break;
                    case 3:
                        other->y = space->y - scale * 7.0f * 2.0f - (j - (i + 2)) * 7;
                        j++;
                        m231_SprBatchPosSet(
                            other->sprite, m231_fieldPosTbl[squash->board][0] + squash->pathIdx * 14,
                            other->y);
                        break;
                    case 0:
                        more = FALSE;
                        j++;
                        break;
                    default:
                        j++;
                        break;
                }
            } while (more);
            squash->cursor->y = space->y - scale * 7.0f * 2.0f - (j - (i + 2)) * 7 - 7.0f;
            HuSprPosSet(squash->sprGroup, 0, squash->x,
                        squash->cursor->y + m231_fieldOfsYTbl[squash->board]);
            HuPrcVSleep();
        } while (squashing);
        space = &m231_fieldTbl[squash->board][squash->pathIdx].spaces[i];
        i++;
        space->type = 3;
        j = i + 1;
        while (TRUE) {
            space = &m231_fieldTbl[squash->board][squash->pathIdx].spaces[i];
            other = &m231_fieldTbl[squash->board][squash->pathIdx].spaces[j];
            space->sprite = other->sprite;
            space->x = other->x;
            space->y = other->y;
            space->ownerId = other->ownerId;
            space->type = other->type;
            i++;
            if (other->type == 0) {
                break;
            }
            j++;
        }
    }
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 m231_BigBlockLand(s32 board, s32 x, s32 sprGroup, MarioPuzzlePartyCursor *cursor, s32 arg4) {
    MarioPuzzlePartySquash *squash;
    Process *process;
    s32 count[2];
    s32 height[2];
    s32 pathIdx;
    s32 side;
    s32 prevScore;

    pathIdx = x - 22;
    pathIdx = (pathIdx - m231_fieldPosTbl[board][0]) / 14 + 1;
    omAddPrcObj(m231_FieldShakeProc, 0x4001, 0x800, 0)->user_data = (void *)board;
    HuAudPlayerFXPlay(0x3FA, board);
    omVibrate(board, 20, 0, 20);
    while (TRUE) {
        count[0] = m231_ColumnBlockCntGet(board, pathIdx);
        count[1] = m231_ColumnBlockCntGet(board, pathIdx + 1);
        side = !(count[1] < count[0]);
        if (m231_ColumnPairCntGet(board, pathIdx + side) == 0) {
            count[0] = m231_ColumnHeightGet(board, pathIdx);
            count[1] = m231_ColumnHeightGet(board, pathIdx + 1);
            if (side == 0 ? count[1] <= count[0] : count[0] <= count[1]) {
                break;
            }
        }
        height[0] = m231_ColumnHeightGet(board, pathIdx) - 1;
        height[1] = m231_ColumnHeightGet(board, pathIdx + 1) - 1;
        if (height[1] <= height[0]) {
            process = omAddPrcObj(m231_SquashProc, 0x4001, 0x800, 0);
            HuPrcChildLink(HuPrcCurrentGet(), process);
            squash = process->user_data = HuMemAlloc(sizeof(MarioPuzzlePartySquash));
            squash->board = board;
            squash->sprGroup = sprGroup;
            squash->pathIdx = pathIdx;
            squash->x = x;
            squash->cursor = cursor;
        }
        if (height[0] <= height[1]) {
            HuAudPlayerFXPlay(0x3FB, board);
            process = omAddPrcObj(m231_SquashProc, 0x4001, 0x800, 0);
            HuPrcChildLink(HuPrcCurrentGet(), process);
            squash = process->user_data = HuMemAlloc(sizeof(MarioPuzzlePartySquash));
            squash->board = board;
            squash->sprGroup = sprGroup;
            squash->pathIdx = pathIdx + 1;
            squash->x = x;
            squash->cursor = cursor;
        }
        HuPrcChildWatch();
    }
    prevScore = m231_clearCntTbl[board];
    m231_ChainResolve(board, arg4);
    return prevScore < m231_clearCntTbl[board];
}

void m231_ScoreDispProc(void) {
    MarioPuzzlePartyScoreDisplay *display = HuPrcCurrentGet()->user_data;
    s32 board = display->board;
    s32 group = display->sprGroup;
    s32 started;
    s32 divisor;
    s32 digit;
    s32 i;

    m231_scoreTbl[board] = 0;
    for (i = 1; i < 6; i++) {
        HuSprGrpMemberSet(group, i, m231_scoreDigitAnimLo, 0);
        if (m231_mode == 0) {
            HuSprPosSet(group, i, -(i * 8) + 16, 12);
        } else {
            HuSprPosSet(group, i, -(i * 8) + 24, 12);
        }
        HuSprAttrReset(group, i, 0xFFFF);
        HuSprAttrSet(group, i, HUSPR_ATTR_BG);
        HuSprPriSet(group, i, 0x1FE);
        HuSprParentSet(group, i, 0);
    }
    HuSprGrpMemberSet(group, 8, m231_scoreUnitAnimLo, 0);
    HuSprPosSet(group, 8, 0, 12);
    HuSprAttrReset(group, 8, 0xFFFF);
    HuSprAttrSet(group, 8, HUSPR_ATTR_BG);
    HuSprPriSet(group, 8, 0x1FF);
    HuSprParentSet(group, 8, 0);
    while (TRUE) {
        if (m231_scoreTbl[board] < 0) {
            m231_scoreTbl[board] = 0;
        }
        if (m231_scoreTbl[board] > 99999) {
            m231_scoreTbl[board] = 99999;
        }
        HuSprGrpMemberSet(group, 1, m231_scoreDigitAnimLo, m231_scoreTbl[board] % 10);
        for (i = 5; i >= 2; i--) {
            HuSprAttrSet(group, i, HUSPR_ATTR_DISPOFF);
        }
        for (i = 5, divisor = 10000, started = FALSE; i >= 2; i--, divisor /= 10) {
            digit = (m231_scoreTbl[board] / divisor) % 10;
            if (digit > 0 || divisor == 1 || started) {
                started = TRUE;
                HuSprAttrReset(group, i, HUSPR_ATTR_DISPOFF);
                HuSprGrpMemberSet(group, i, m231_scoreDigitAnimLo, digit);
            }
        }
        HuPrcVSleep();
    }
}

void m231_BlockDropCreate(s32 board, s32 ownerId, s32 type, s32 pathIdx, s32 spaceIdx, s32 arg5) {
    MarioPuzzlePartyPathSpace *space;
    MarioPuzzlePartyFallingBlock *block;
    Process *process;

    m231_BlockSet(board, ownerId, type, pathIdx, spaceIdx);
    space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx];
    if (space->type == 1 || space->type == 3) {
        process = omAddPrcObj(m231_BlockFallProc, 0x4001, 0x800, 0);
        HuPrcChildLink(HuPrcCurrentGet(), process);
        block = process->user_data = HuMemAlloc(sizeof(MarioPuzzlePartyFallingBlock));
        block->board = board;
        block->sprite = space->sprite;
        block->x = space->x;
        block->y = space->y;
        block->ownerId = space->ownerId;
        block->type = space->type;
        block->unk_18 = arg5;
    }
}

void m231_NextPairProc(void) {
    MarioPuzzlePartyCursor *cursor = HuPrcCurrentGet()->user_data;
    s32 board = cursor->board;
    s32 falling;

    if (m231_bigBlockCntTbl[board] < 10) {
        cursor->blockOwners[0] = m231_pairTbl[m231_pairNoTbl[board]][0];
        cursor->blockOwners[1] = m231_pairTbl[m231_pairNoTbl[board]][1];
        m231_pairNoTbl[board]++;
        if (m231_pairNoTbl[board] >= 30) {
            m231_pairNoTbl[board] = 0;
        }
        cursor->x = m231_fieldPosTbl[board][0] + 35;
        cursor->y = m231_fieldPosTbl[board][1] - 231;
        cursor->blockSprites[0] =
            m231_BlockSprCreate(board, cursor->blockOwners[0], 1, cursor->x, cursor->y);
        cursor->blockSprites[1] =
            m231_BlockSprCreate(board, cursor->blockOwners[1], 1, cursor->x, cursor->y - 14.0f);
    } else {
        cursor->x = m231_fieldPosTbl[board][0] + 42;
        cursor->y = m231_fieldPosTbl[board][1] - 231;
        cursor->blockOwners[0] = 7;
        cursor->blockSprites[0] = HuSprGrpCreate(1, 5);
        HuSprGrpMemberSet(cursor->blockSprites[0], 0, m231_bigBlockAnimLo, 0);
        HuSprPosSet(cursor->blockSprites[0], 0, cursor->x, m231_fieldOfsYTbl[board] + cursor->y);
        HuSprAttrReset(cursor->blockSprites[0], 0, 0xFFFF);
        HuSprAttrSet(cursor->blockSprites[0], 0, HUSPR_ATTR_FILTER_BILERP);
    }
    falling = TRUE;
    do {
        cursor->y += 5.0f;
        if (cursor->blockOwners[0] != 7) {
            if (cursor->y > m231_fieldPosTbl[board][1] - 182) {
                cursor->y = m231_fieldPosTbl[board][1] - 182;
                falling = FALSE;
            }
            m231_SprBatchPosSet(cursor->blockSprites[0], cursor->x, cursor->y);
            m231_SprBatchPosSet(cursor->blockSprites[1], cursor->x, cursor->y - 14.0f);
        } else {
            if (cursor->y > m231_fieldPosTbl[board][1] - 196) {
                cursor->y = m231_fieldPosTbl[board][1] - 196;
                falling = FALSE;
            }
            HuSprPosSet(cursor->blockSprites[0], 0, cursor->x, m231_fieldOfsYTbl[board] + cursor->y);
        }
        HuPrcVSleep();
    } while (falling);
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m231_ScoreFlyProc(void) {
    f32 xOffsets[5] = { -95.0f, -30.0f, 30.0f, 95.0f, 0.0f };
    s32 board = (s32)HuPrcCurrentGet()->user_data;
    s32 i;
    s32 group0;
    s32 group1;
    s32 group2;
    f32 angle;
    f32 y;
    f32 z;

    if (board == 4) {
        HuAudPlayerFXPlay(0x3FE, 0);
    } else {
        HuAudPlayerFXPlay(0x3FE, board);
    }
    group0 = HuSprGrpCreate(1, 5);
    HuSprGrpMemberSet(group0, 0, m231_scoreFlyAnimLo, 0);
    HuSprAttrReset(group0, 0, 0xFFFF);
    HuSprPriSet(group0, 0, 0x200);
    HuSprAttrSet(group0, 0, HUSPR_ATTR_BG);
    group1 = HuSprGrpCreate(1, 5);
    HuSprGrpMemberSet(group1, 0, m231_scoreDigitAnimLo, 0);
    HuSprAttrReset(group1, 0, 0xFFFF);
    HuSprPriSet(group1, 0, 0x1FE);
    HuSprAttrSet(group1, 0, HUSPR_ATTR_BG);
    group2 = HuSprGrpCreate(1, 5);
    HuSprGrpMemberSet(group2, 0, m231_scoreUnitAnimLo, 0);
    HuSprAttrReset(group2, 0, 0xFFFF);
    HuSprPriSet(group2, 0, 0x1FF);
    HuSprAttrSet(group2, 0, HUSPR_ATTR_BG);
    z = -5000.0f;
    angle = 0.0f;
    for (i = 0; i < 45; i++) {
        y = sindf(angle) * 150.0f;
        angle += 6.0f;
        z += 111.111115f;
        HuSpr3Dto2D(group0, 0, 0, xOffsets[board], y, z);
        HuSpr3DPosSet(group0, 0, 0, xOffsets[board], y, z);
        if (m231_mode == 0) {
            HuSpr3Dto2D(group1, 0, 0, xOffsets[board] + 8.0f, y - 12.0f, z);
            HuSpr3DPosSet(group1, 0, 0, xOffsets[board] + 8.0f, y - 12.0f, z);
        } else {
            HuSpr3Dto2D(group1, 0, 0, xOffsets[board] + 16.0f, y - 12.0f, z);
            HuSpr3DPosSet(group1, 0, 0, xOffsets[board] + 16.0f, y - 12.0f, z);
        }
        HuSpr3Dto2D(group2, 0, 0, xOffsets[board], y - 12.0f, z);
        HuSpr3DPosSet(group2, 0, 0, xOffsets[board], y - 12.0f, z);
        HuPrcVSleep();
    }
    HuSprGrpKill(group0);
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 m231_SpawnSpaceCheck(s32 board, s32 x, s32 y) {
    s32 pathIdx = (x - m231_fieldPosTbl[board][0]) / 14;
    s32 spaceIdx = (m231_fieldPosTbl[board][1] - y) / 7;
    MarioPuzzlePartyPathSpace *space;
    s32 i;

    for (i = 0; i < 4; i++) {
        space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx + i];
        if (space->type != 0) {
            break;
        }
    }
    return !(i < 4);
}

void m231_LoseProc(void) {
    s32 board = (s32)HuPrcCurrentGet()->user_data;
    MarioPuzzlePartyCursor *next = &m231_nextTbl[board];
    s32 group;
    s32 x;
    s32 y;
    f32 angle;

    if (next->blockOwners[0] != 7) {
        m231_DebrisCreate(board, (next->x - m231_fieldPosTbl[board][0]) / 14.0f,
                                          (m231_fieldPosTbl[board][1] - next->y) / 7.0f);
        m231_SprBatchEntryKill(next->blockSprites[0]);
        m231_SprBatchEntryKill(next->blockSprites[1]);
    } else {
        HuSprAttrSet(next->blockSprites[0], 0, HUSPR_ATTR_DISPOFF);
    }
    for (angle = 0.0f; angle != 360.0f;) {
        angle += 10.0f;
        if (angle > 360.0f) {
            angle = 360.0f;
        }
        HuSprZRotSet(m231_headGrpTbl[board], 0, sindf(angle) * 45.0f);
        HuPrcVSleep();
    }
    HuSprGrpKill(m231_signGrpTbl[board]);
    group = m231_signGrpTbl[board] = HuSprGrpCreate(1, 5);
    HuSprGrpMemberSet(group, 0, m231_loseSignAnimLo, 0);
    HuSprPosSet(group, 0, m231_fieldPosTbl[board][0] + 42,
                m231_fieldPosTbl[board][1] - 161 + m231_fieldOfsYTbl[board]);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, HUSPR_ATTR_BG | HUSPR_ATTR_FILTER_BILERP);
    HuSprPriSet(group, 0, 0x300);
    omAddPrcObj(m231_FieldDropProc, 0x4001, 0x800, 0)->user_data = (void *)board;
    HuPrcSleep(10);
    x = m231_fieldPosTbl[board][0] + 42;
    y = m231_fieldPosTbl[board][1] - 181;
    while (y < 130) {
        y += 3;
        HuSprPosSet(m231_headGrpTbl[board], 0, x, y);
        HuPrcVSleep();
    }
    y = 130;
    // do-while (0) adds loop weight to x's refs so it wins s2 in global alloc.
    do {
        HuSprPosSet(m231_headGrpTbl[board], 0, x, y);
    } while (0);
    angle = 0.0f;
    while (TRUE) {
        angle += 8.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        HuSprPosSet(m231_headGrpTbl[board], 0, x, y + sindf(angle) * 3.0f);
        HuPrcVSleep();
    }
}

void m231_PlayerEnd(void) {
    s32 board = (s32)HuPrcCurrentGet()->user_data;
    MarioPuzzlePartyCursor *cursor = &m231_cursorTbl[board];
    MarioPuzzlePartyCursor *next = &m231_nextTbl[board];
    MarioPuzzlePartyPathSpace *space;
    s32 pathIdx;
    s32 spaceIdx;

    if (m231_winner != board) {
        if (m231_exitF == 0) {
            if (m231_mode != 2) {
                omVibrate(board, 10, 0, 10);
            } else if (board == 0) {
                omVibrate(0, 10, 0, 10);
            }
            m231_doneTbl[board] = 1;
            omAddPrcObj(m231_LoseProc, 0x4001, 0x1000, 0)->user_data =
                HuPrcCurrentGet()->user_data;
        }
    }
    if (m231_exitF == 0) {
        HuSprBankSet(m231_headGrpTbl[board], 0, 0, 2);
        HuSprAnimModeSet(m231_headGrpTbl[board], 0, HUSPR_ANIM_MODE_BANK);
        HuSprAttrReset(m231_headGrpTbl[board], 0, HUSPR_ATTR_DISPOFF);
        HuSprAttrSet(m231_headGrpTbl[board], 9, HUSPR_ATTR_DISPOFF);
        if (m231_exitF == 0) {
            if (next->blockOwners[0] != 7) {
                m231_DebrisCreate(board,
                                                  (next->x - m231_fieldPosTbl[board][0]) / 14.0f,
                                                  (m231_fieldPosTbl[board][1] - next->y) / 7.0f);
                m231_SprBatchEntryKill(next->blockSprites[0]);
                m231_SprBatchEntryKill(next->blockSprites[1]);
            } else {
                HuSprAttrSet(next->blockSprites[0], 0, HUSPR_ATTR_DISPOFF);
            }
        }
    }
    m231_gameOverTbl[board] = 1;
    if (m231_winner == board) {
        HuAudFXPlay(0x3FF);
        for (spaceIdx = 1; spaceIdx < 40; spaceIdx++) {
            for (pathIdx = 1; pathIdx < 5; pathIdx++) {
                space = &m231_fieldTbl[board][pathIdx].spaces[spaceIdx];
                if (space->type == 3 || space->type == 1) {
                    m231_BlockClear(board, pathIdx, spaceIdx);
                }
            }
        }
        if (m231_exitF == 0) {
            if (cursor->blockOwners[0] != 7) {
                m231_DebrisCreate(board,
                                                  (cursor->x - m231_fieldPosTbl[board][0]) / 14.0f,
                                                  (m231_fieldPosTbl[board][1] - cursor->y) / 7.0f);
                m231_SprBatchEntryKill(cursor->blockSprites[0]);
                m231_SprBatchEntryKill(cursor->blockSprites[1]);
            } else if (m231_bigBlockGrpTbl[board] != -1) {
                HuSprAttrSet(m231_bigBlockGrpTbl[board], 0, HUSPR_ATTR_DISPOFF);
            }
        }
    }
}

void m231_PlayerProc(void) {
    MarioPuzzlePartyScoreDisplay display;
    s32 heights[4];
    s32 canDrop[4];
    s32 k = 0;
    s32 board;
    s32 sprite1;
    s32 speed;
    s32 level = 1;
    MarioPuzzlePartyCursor *next;
    MarioPuzzlePartyPlayerInput *input = NULL;
    MarioPuzzlePartyCursor *cursor;
    MarioPuzzlePartyPathSpace *space;
    MarioPuzzlePartyPath *path;
    Process *process;
    s32 sprite0;
    s32 timer;
    s32 group;
    // i and j are also the entry position of a piece and the fall distance / landed flag while it drops
    s32 i;
    s32 j;
    s32 count;
    s32 best;
    s32 done;
    // also the height of a column in the CPU logic
    s32 row;
    s32 spaceIdx;
    f32 nextStepX;
    f32 nextStepY;
    f32 stepX;
    f32 stepY;

    board = (s32)HuPrcCurrentGet()->user_data;
    omPrcSetDestructor(HuPrcCurrentGet(), m231_PlayerEnd);
    m231_headGrpTbl[board] = display.sprGroup = HuSprGrpCreate(10, 5);
    HuSprGrpMemberSet(display.sprGroup, 0, m231_headAnim, 0);
    HuSprAnimModeSet(display.sprGroup, 0, HUSPR_ANIM_MODE_STOP);
    HuSprPosSet(display.sprGroup, 0, m231_fieldPosTbl[board][0] + 42,
                m231_fieldPosTbl[board][1] - 182 + m231_fieldOfsYTbl[board]);
    HuSprAttrReset(display.sprGroup, 0, 0xFFFF);
    HuSprAttrSet(display.sprGroup, 0, HUSPR_ATTR_BG);
    HuSprPriSet(display.sprGroup, 0, 0x200);
    HuSprGrpMemberSet(display.sprGroup, 9, m231_headPartAnim, 0);
    HuSprAnimModeSet(display.sprGroup, 9, HUSPR_ANIM_MODE_STOP);
    HuSprPosSet(display.sprGroup, 9, 0, 0);
    HuSprAttrReset(display.sprGroup, 9, 0xFFFF);
    HuSprAttrSet(display.sprGroup, 9, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_BG);
    HuSprPriSet(display.sprGroup, 9, 0x200);
    HuSprParentSet(display.sprGroup, 9, 0);
    process = omAddPrcObj(m231_ScoreDispProc, 0x4001, 0x800, 0);
    display.board = board;
    process->user_data = &display;

    m231_signGrpTbl[board] = sprite0 = HuSprGrpCreate(1, 5);
    group = sprite0;
    HuSprGrpMemberSet(group, 0, m231_signAnim, 0);
    HuSprPosSet(group, 0, m231_fieldPosTbl[board][0] + 42,
                m231_fieldPosTbl[board][1] - 161 + m231_fieldOfsYTbl[board]);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, HUSPR_ATTR_BG | HUSPR_ATTR_FILTER_BILERP);
    HuSprPriSet(group, 0, 0x300);

    m231_fieldBackGrpTbl[board] = sprite0 = HuSprGrpCreate(1, 5);
    group = sprite0;
    HuSprGrpMemberSet(group, 0, m231_fieldBackAnim, 0);
    HuSprPosSet(group, 0, m231_fieldPosTbl[board][0] + 42,
                m231_fieldPosTbl[board][1] - 78 + m231_fieldOfsYTbl[board]);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, HUSPR_ATTR_BG | HUSPR_ATTR_FILTER_BILERP);
    HuSprPriSet(group, 0, 0x600);

    m231_fieldFrameGrpTbl[board] = sprite0 = HuSprGrpCreate(1, 5);
    group = sprite0;
    HuSprGrpMemberSet(group, 0, m231_fieldFrameAnim, 0);
    HuSprPosSet(group, 0, m231_fieldPosTbl[board][0] + 42,
                m231_fieldPosTbl[board][1] - 78 + m231_fieldOfsYTbl[board]);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, HUSPR_ATTR_BG | HUSPR_ATTR_XLU | HUSPR_ATTR_FILTER_BILERP);
    HuSprPriSet(group, 0, 0x600);
    HuSprTPLvlSet(group, 0, 0x80);

    m231_chrFaceGrpTbl[board] = sprite0 = HuSprGrpCreate(1, 5);
    group = sprite0;
    HuSprGrpMemberSet(group, 0, m231_chrFaceAnimTbl[board], 0);
    HuSprPosSet(group, 0, m231_fieldPosTbl[board][0] + 42,
                m231_fieldPosTbl[board][1] - 105 + m231_fieldOfsYTbl[board]);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, HUSPR_ATTR_BG | HUSPR_ATTR_XLU | HUSPR_ATTR_FILTER_BILERP);
    HuSprPriSet(group, 0, 0x500);
    HuSprTPLvlSet(group, 0, 0x9A);

    cursor = &m231_cursorTbl[board];
    cursor->sprite = espEntry(HuSprAnimDataRead(GwPlayer[board].chr + 0x6A), 0, 1);
    cursor->x = cursor->unk_10 = m231_fieldPosTbl[board][0] + 28;
    cursor->y = m231_fieldPosTbl[board][1] - 70;
    cursor->pathIdx = 2;
    cursor->spaceIdx = 10;
    cursor->moveDir = 0;
    espPosSet(cursor->sprite, cursor->x + 7.0f, m231_fieldOfsYTbl[board] + cursor->y);
    espPriSet(cursor->sprite, 0x200);
    espDispOn(cursor->sprite);
    HuSprBankSet(display.sprGroup, 0, 0, 2);
    HuSprAnimModeSet(display.sprGroup, 0, HUSPR_ANIM_MODE_BANK);
    HuPrcVSleep();
    HuSprAnimModeSet(display.sprGroup, 0, HUSPR_ANIM_MODE_STOP);
    while (TRUE) {
        if (MgFlowStatGet() == MG_STATE_PLAY) {
            break;
        }
        HuPrcVSleep();
    }
    process = omAddPrcObj(m231_NextPairProc, 0x4001, 0x800, 0);
    HuPrcChildLink(HuPrcCurrentGet(), process);
    process->user_data = next = &m231_nextTbl[board];
    next->board = board;
    HuPrcVSleep();
    if (next->blockOwners[0] != 7) {
        HuSprBankSet(display.sprGroup, 0, 0, 0);
        HuSprAnimModeSet(display.sprGroup, 0, HUSPR_ANIM_MODE_BANK);
        HuSprAttrReset(display.sprGroup, 0, HUSPR_ATTR_DISPOFF);
        HuSprAttrSet(display.sprGroup, 9, HUSPR_ATTR_DISPOFF);
        HuPrcVSleep();
        HuSprAnimModeSet(display.sprGroup, 0, HUSPR_ANIM_MODE_STOP);
    } else {
        HuSprBankSet(display.sprGroup, 9, 0, 0);
        HuSprAnimModeSet(display.sprGroup, 9, HUSPR_ANIM_MODE_BANK);
        HuSprAttrReset(display.sprGroup, 9, HUSPR_ATTR_DISPOFF);
        HuSprAttrSet(display.sprGroup, 0, HUSPR_ATTR_DISPOFF);
        HuPrcVSleep();
        HuSprAnimModeSet(display.sprGroup, 9, HUSPR_ANIM_MODE_STOP);
    }
    HuPrcChildWatch();
    while (TRUE) {
        // send garbage to the other players for the chain that just ended
        if (m231_chainTbl[board] >= 2) {
            for (j = 0; j < 4; j++) {
                if (j != board) {
                    m231_garbageTbl[j] += m231_chainTbl[board];
                }
            }
        }
        m231_chainTbl[board] = 0;
        m231_clearCntTbl[board] = 0;
        if (m231_mode == 2 && level * 100 <= m231_scoreTbl[board]) {
            HuAudFXPlay(0x3FC);
            level++;
            m231_garbageTbl[board] = level + 3;
            if (m231_garbageTbl[board] >= 10) {
                m231_garbageTbl[board] = 9;
            }
        }
        // drop the garbage blocks this player received
        count = m231_garbageTbl[board];
        m231_garbageTbl[board] = 0;
        if (count >= 2) {
            for (i = 0; i < 4; i++) {
                heights[i] = 21 - m231_ColumnHeightGet(board, i + 1);
            }
            for (i = 0, j = 0; i < 4; i++) {
                if (heights[i] >= 2) {
                    canDrop[i] = TRUE;
                    j++;
                } else {
                    canDrop[i] = FALSE;
                }
            }
            if (j == 0) {
                break;
            }
            for (k = count - 1, row = 0; k != 0; k--) {
                // pick one of the j columns that still have room
                s32 target = rand8() * (1.0f / 256.0f) * j;

                for (i = 0, count = 0; i < 4; i++) {
                    if (canDrop[i]) {
                        if (target == count) {
                            s32 playSound = (row == 0);

                            m231_BlockDropCreate(board, 6, 1, i + 1, row + 29, playSound);
                            heights[i] -= 2;
                            canDrop[i] = FALSE;
                        }
                        count++;
                    }
                }
                if (--j <= 0) {
                    row += 2;
                    if (row >= 6) {
                        break;
                    }
                    for (i = 0, j = 0; i < 4; i++) {
                        if (heights[i] >= 2) {
                            canDrop[i] = TRUE;
                            j++;
                        } else {
                            canDrop[i] = FALSE;
                        }
                    }
                    if (j == 0) {
                        break;
                    }
                }
            }
        }
        HuPrcChildWatch();
        speed = 2;
        HuPrcChildWatch();
        // pick the position (i, j) where the next piece enters the board
        if (next->blockOwners[0] != 7) {
            i = m231_fieldPosTbl[board][0] + 28;
            j = m231_fieldPosTbl[board][1] - 119;
            if (!m231_SpawnSpaceCheck(board, i, j)) {
                i = m231_fieldPosTbl[board][0] + 42;
                if (!m231_SpawnSpaceCheck(board, i, j)) {
                    i = m231_fieldPosTbl[board][0] + 14;
                    if (!m231_SpawnSpaceCheck(board, i, j)) {
                        i = m231_fieldPosTbl[board][0] + 56;
                        if (!m231_SpawnSpaceCheck(board, i, j)) {
                            break;
                        }
                    }
                }
            }
        } else {
            s32 top;

            m231_bigBlockCntTbl[board] = 0;
            for (count = 0; count < 4; count++) {
                space = m231_fieldTbl[board][2].spaces;
                if (space[count + 17].type == 0) {
                    break;
                }
            }
            for (k = 0; k < 4; k++) {
                space = m231_fieldTbl[board][3].spaces;
                if (space[k + 17].type == 0) {
                    break;
                }
            }
            if (k < count) {
                top = count + 19;
            } else {
                top = k + 19;
            }
            i = m231_fieldPosTbl[board][0] + 42;
            j = m231_fieldPosTbl[board][1] - top * 7;
        }
        // move the waiting piece and the cursor to the entry position
        nextStepX = (i - next->x) / 10.0f;
        nextStepY = (j - next->y) / 10.0f;
        stepX = (i - cursor->x) / 10.0f;
        stepY = (j - cursor->y) / 10.0f;
        if (next->blockOwners[0] != 7) {
            HuSprAnimModeSet(display.sprGroup, 0, HUSPR_ANIM_MODE_BANK);
        } else {
            HuSprAnimModeSet(display.sprGroup, 9, HUSPR_ANIM_MODE_BANK);
        }
        do {
            next->x = nextStepX + next->x;
            next->y = nextStepY + next->y;
            cursor->x = stepX + cursor->x;
            cursor->y = stepY + cursor->y;
            if (next->y >= j) {
                cursor->unk_10 = i;
                next->x = cursor->x = i;
                next->y = cursor->y = j;
            }
            if (next->blockOwners[0] != 7) {
                m231_SprBatchPosSet(next->blockSprites[0], next->x, next->y);
                m231_SprBatchPosSet(next->blockSprites[1], next->x, next->y - 14.0f);
            } else {
                HuSprPosSet(next->blockSprites[0], 0, next->x, m231_fieldOfsYTbl[board] + next->y);
            }
            espPosSet(cursor->sprite, cursor->x + 7.0f, m231_fieldOfsYTbl[board] + cursor->y);
            cursor->pathIdx = (cursor->x - m231_fieldPosTbl[board][0]) / 14.0f;
            HuPrcVSleep();
        } while (next->y != j);
        if (m231_mode == 2) {
            HuAudPlayerFXPlay(0x3FD, board);
        }
        espBankSet(cursor->sprite, 1, 0);
        espAnimModeSet(cursor->sprite, 1);
        // the waiting piece becomes the active one
        sprite0 = cursor->blockSprites[0] = next->blockSprites[0];
        sprite1 = cursor->blockSprites[1] = next->blockSprites[1];
        cursor->blockOwners[0] = next->blockOwners[0];
        cursor->blockOwners[1] = next->blockOwners[1];
        cursor->moveDir = 0;
        m231_bigBlockGrpTbl[board] = sprite0;
        process = omAddPrcObj(m231_NextPairProc, 0x4001, 0x800, 0);
        HuPrcChildLink(HuPrcCurrentGet(), process);
        process->user_data = next = &m231_nextTbl[board];
        next->board = board;
        HuPrcVSleep();
        if (next->blockOwners[0] != 7) {
            HuSprBankSet(display.sprGroup, 0, 0, 0);
            HuSprAnimModeSet(display.sprGroup, 0, HUSPR_ANIM_MODE_BANK);
            HuPrcVSleep();
            HuSprAnimModeSet(display.sprGroup, 0, HUSPR_ANIM_MODE_STOP);
            HuSprAttrReset(display.sprGroup, 0, HUSPR_ATTR_DISPOFF);
            HuSprAttrSet(display.sprGroup, 9, HUSPR_ATTR_DISPOFF);
        } else {
            HuSprBankSet(display.sprGroup, 9, 0, 0);
            HuSprAnimModeSet(display.sprGroup, 9, HUSPR_ANIM_MODE_BANK);
            HuPrcVSleep();
            HuSprAnimModeSet(display.sprGroup, 9, HUSPR_ANIM_MODE_STOP);
            HuSprAttrReset(display.sprGroup, 9, HUSPR_ATTR_DISPOFF);
            HuSprAttrSet(display.sprGroup, 0, HUSPR_ATTR_DISPOFF);
        }
        // CPU players decide where to put the piece
        if (GwPlayer[board].stat & PLAYER_IS_CPU) {
            input = &m231_comInputTbl[board];
            input->direction = 0;
            input->buttons = 0;
            if (cursor->blockOwners[0] != 7) {
                for (i = 1; i < 5; i++) {
                    j = 1;
                    while (TRUE) {
                        path = &m231_fieldTbl[board][i];
                        if (path->spaces[j].type == 0) {
                            break;
                        }
                        j++;
                    }
                    input->heights[i - 1] = j;
                    input->scores[0][i - 1] =
                        m231_NeighborMatchCnt(board, 1, cursor->blockOwners[0], i, j);
                    input->scores[1][i - 1] =
                        m231_NeighborMatchCnt(board, 1, cursor->blockOwners[1], i, input->heights[i - 1]);
                }
                for (i = 0, j = 0; i < 4; i++) {
                    j += m231_ColumnBlockCntGet(board, i + 1);
                }
                if (m231_goalScore - 10 < m231_scoreTbl[board]) {
                    best = 5;
                } else if (m231_goalScore - 20 < m231_scoreTbl[board]) {
                    best = 10;
                } else {
                    best = 25;
                }
                if (best < j) {
                    input->mode = 0;
                } else {
                    input->mode = 1;
                }
                switch (input->mode) {
                    case 0:
                        // lowest column that touches a matching block
                        for (i = 0, best = 999, k = 0; i < 2; i++) {
                            for (j = 0; j < 4; j++) {
                                if (input->scores[i][j] > 0) {
                                    k = m231_ColumnHeightGet(board, j + 1);
                                    if (k < best) {
                                        best = k;
                                        input->swap = i;
                                        input->targetPath = j + 1;
                                    }
                                }
                            }
                        }
                        if (best == 999) {
                            for (i = 1, j = 0, k = 0; i < 5; i++) {
                                best = m231_ColumnHeightGet(board, i);
                                if (j < best) {
                                    j = best;
                                    k = i;
                                }
                            }
                            input->swap = 0;
                            input->targetPath = k;
                        }
                        break;
                    case 1:
                        for (i = 0, best = 999, k = 0; i < 2; i++) {
                            for (j = 0; j < 4; j++) {
                                if (input->scores[i][j] < best) {
                                    best = input->scores[i][j];
                                    row = m231_ColumnHeightGet(board, j + 1);
                                    input->swap = i;
                                    input->targetPath = j + 1;
                                    if (k < row && row < 18) {
                                        k = row;
                                    }
                                } else if (input->scores[i][j] == best) {
                                    row = m231_ColumnHeightGet(board, j + 1);
                                    if (k < row && row < 18) {
                                        k = row;
                                        input->swap = i;
                                        input->targetPath = j + 1;
                                    }
                                }
                            }
                        }
                        break;
                    case 2:
                        for (i = 0, best = 0; i < 2; i++) {
                            for (j = 0; j < 4; j++) {
                                if (best < input->scores[i][j]) {
                                    best = input->scores[i][j];
                                    input->swap = i;
                                    input->targetPath = j + 1;
                                }
                            }
                        }
                        if (best == 0) {
                            for (i = 1, j = 0; i < 5; i++) {
                                best = m231_ColumnHeightGet(board, i);
                                if (j < best) {
                                    j = best;
                                    k = i;
                                }
                            }
                            input->swap = 0;
                            input->targetPath = k;
                        }
                        break;
                }
            } else {
                for (i = 0; i < 3; i++) {
                    input->scores[0][i] = m231_ColumnPairCntGet(board, i + 1);
                    input->scores[0][i] += m231_ColumnPairCntGet(board, i + 2);
                }
                for (i = 0, j = -1, best = 0; i < 3; i++) {
                    if (best < input->scores[0][i]) {
                        best = input->scores[0][i];
                        j = i;
                    }
                }
                if (j != -1) {
                    input->targetPath = j + 2;
                } else {
                    input->targetPath = (u8)(rand8() % 3) + 2;
                }
            }
            switch (GwPlayer[board].cpu_difficulty) {
                case 0:
                    i = rand8() & 1;
                    input->delay = (u8)(rand8() % 30) + 30;
                    break;
                case 1:
                    i = (u8)(rand8() % 3);
                    input->delay = (u8)(rand8() % 20) + 20;
                    break;
                case 2:
                    i = rand8() & 3;
                    input->delay = (u8)(rand8() % 10) + 10;
                    break;
                default:
                    i = (u8)(rand8() % 10);
                    input->delay = (u8)(rand8() % 10) + 1;
                    break;
            }
            if (i == 0) {
                // occasionally miss the chosen column
                input->targetPath += (u8)(rand8() % 3) - 1;
            }
        }
        cursor->unk_28 = 0;
        timer = 0;
        if (cursor->blockOwners[0] != 7) {
            while (TRUE) {
                cursor->pathIdx = (cursor->x - m231_fieldPosTbl[board][0]) / 14.0f;
                cursor->spaceIdx = (m231_fieldPosTbl[board][1] - cursor->y) / 7.0f;
                if (GwPlayer[board].stat & PLAYER_IS_CPU) {
                    input->direction = 0;
                    input->buttons = 0;
                    if (cursor->pathIdx > input->targetPath) {
                        input->direction |= L_JPAD;
                    }
                    if (cursor->pathIdx < input->targetPath) {
                        input->direction |= R_JPAD;
                    }
                    if (input->swap != 0) {
                        input->swap = 0;
                        input->buttons |= 0x8000;
                    }
                    row = m231_ColumnHeightGet(board, input->targetPath);
                    if (input->delay-- <= 0) {
                        if ((cursor->pathIdx == input->targetPath && input->buttons == 0) ||
                            cursor->spaceIdx < row) {
                            input->buttons |= 0x2000;
                        }
                        switch (GwPlayer[board].cpu_difficulty) {
                            case 2:
                                if (input->delay < -60) {
                                    input->buttons |= 0x2000;
                                }
                                break;
                            case 3:
                                if (input->delay < -30) {
                                    input->buttons |= 0x2000;
                                }
                                break;
                        }
                    }
                }
                i = speed;
                j = FALSE;
                while (i >= 8) {
                    j |= m231_PairFallCheck(board, cursor, 7);
                    i -= 7;
                }
                j |= m231_PairFallCheck(board, cursor, i);
                if (j) {
                    spaceIdx = (m231_fieldPosTbl[board][1] - cursor->y) / 7.0f;
                    cursor->y = m231_fieldPosTbl[board][1] - spaceIdx * 7;
                    if (cursor->moveDir == 0) {
                        m231_SprBatchPosSet(sprite0, cursor->x, cursor->y);
                        m231_SprBatchPosSet(sprite1, cursor->x, cursor->y - 14.0f);
                        if (timer++ >= 6 || speed != 2) {
                            m231_PairLand(board, cursor);
                            break;
                        }
                    }
                }
                if (cursor->moveDir == 0 && speed != 7 && cursor->unk_28 == 0) {
                    if ((m231_InputBtnGet(board) & L_JPAD) &&
                        !m231_PairMoveCheck(board, cursor, -1)) {
                        cursor->moveDir = -1;
                    }
                    if ((m231_InputBtnGet(board) & R_JPAD) &&
                        !m231_PairMoveCheck(board, cursor, 1)) {
                        cursor->moveDir = 1;
                    }
                }
                if (cursor->moveDir > 0) {
                    cursor->x += 5.0f;
                    if (cursor->x > cursor->unk_10 + 14) {
                        cursor->unk_10 += 14;
                        cursor->x = cursor->unk_10;
                        cursor->moveDir = 0;
                    }
                }
                if (cursor->moveDir < 0) {
                    cursor->x -= 5.0f;
                    if (cursor->x < cursor->unk_10 - 14) {
                        cursor->unk_10 -= 14;
                        cursor->x = cursor->unk_10;
                        cursor->moveDir = 0;
                    }
                }
                if (cursor->unk_28 == 0) {
                    speed = (m231_InputBtnGet(board) & D_JPAD) ? 7 : 2;
                }
                if (m231_InputBtnDownGet(board, Z_TRIG)) {
                    timer = 5;
                    cursor->unk_28 = 1;
                    speed = 14;
                }
                if (m231_InputBtnDownGet(board, A_BUTTON) && cursor->unk_28 == 0) {
                    i = cursor->blockOwners[0];
                    cursor->blockOwners[0] = cursor->blockOwners[1];
                    cursor->blockOwners[1] = i;
                    i = sprite0;
                    cursor->blockSprites[0] = sprite0 = sprite1;
                    cursor->blockSprites[1] = sprite1 = i;
                }
                espPosSet(cursor->sprite, cursor->x + 7.0f, m231_fieldOfsYTbl[board] + cursor->y);
                m231_SprBatchPosSet(sprite0, cursor->x, cursor->y);
                m231_SprBatchPosSet(sprite1, cursor->x, cursor->y - 14.0f);
                HuPrcVSleep();
            }
        } else {
            done = FALSE;
            m231_bigBlockGrpTbl[board] = sprite0;
            m231_bigBlockFirstTbl[board] = 1;
            while (TRUE) {
                if (GwPlayer[board].stat & PLAYER_IS_CPU) {
                    input->direction = 0;
                    input->buttons = 0;
                    cursor->pathIdx = (cursor->x - m231_fieldPosTbl[board][0]) / 14.0f;
                    if (cursor->pathIdx > input->targetPath) {
                        input->direction |= L_JPAD;
                    }
                    if (cursor->pathIdx < input->targetPath) {
                        input->direction |= R_JPAD;
                    }
                    m231_ColumnHeightGet(board, input->targetPath);
                    if (input->delay-- <= 0) {
                        if (cursor->pathIdx == input->targetPath) {
                            input->buttons |= 0x2000;
                        }
                        switch (GwPlayer[board].cpu_difficulty) {
                            case 2:
                                if (input->delay < -60) {
                                    input->buttons |= 0x2000;
                                }
                                break;
                            case 3:
                                if (input->delay < -30) {
                                    input->buttons |= 0x2000;
                                }
                                break;
                        }
                    }
                }
                if (cursor->moveDir == 0 && speed != 7 && !done && cursor->unk_28 == 0) {
                    if ((m231_InputBtnGet(board) & L_JPAD) &&
                        !m231_BigBlockMoveCheck(board, cursor, -1)) {
                        cursor->moveDir = -1;
                    }
                    if ((m231_InputBtnGet(board) & R_JPAD) &&
                        !m231_BigBlockMoveCheck(board, cursor, 1)) {
                        cursor->moveDir = 1;
                    }
                }
                if (cursor->moveDir > 0) {
                    cursor->x += 5.0f;
                    if (cursor->x > cursor->unk_10 + 14) {
                        cursor->unk_10 += 14;
                        cursor->x = cursor->unk_10;
                        cursor->moveDir = 0;
                    }
                }
                if (cursor->moveDir < 0) {
                    cursor->x -= 5.0f;
                    if (cursor->x < cursor->unk_10 - 14) {
                        cursor->unk_10 -= 14;
                        cursor->x = cursor->unk_10;
                        cursor->moveDir = 0;
                    }
                }
                i = speed;
                j = FALSE;
                while (i >= 8) {
                    j |= m231_BigBlockFallCheck(board, cursor, 7);
                    i -= 7;
                }
                j |= m231_BigBlockFallCheck(board, cursor, i);
                if (j) {
                    spaceIdx = (m231_fieldPosTbl[board][1] - cursor->y) / 7.0f;
                    cursor->y = m231_fieldPosTbl[board][1] - spaceIdx * 7;
                    if (cursor->moveDir == 0) {
                        if (timer++ >= 6 || speed != 2) {
                            if (!m231_BigBlockLand(board, cursor->x, sprite0, cursor,
                                                                   m231_bigBlockFirstTbl[board])) {
                                m231_bigBlockGrpTbl[board] = -1;
                                HuSprGrpKill(sprite0);
                                break;
                            }
                            done = TRUE;
                            m231_bigBlockFirstTbl[board] = 0;
                            speed = 7;
                        }
                    }
                }
                if (cursor->unk_28 == 0) {
                    speed = (m231_InputBtnGet(board) & D_JPAD) ? 7 : 2;
                }
                if ((m231_InputBtnGet(board) & Z_TRIG) || done) {
                    timer = 5;
                    cursor->unk_28 = 1;
                    speed = 14;
                }
                espPosSet(cursor->sprite, cursor->x + 7.0f,
                          cursor->y + 7.0f + m231_fieldOfsYTbl[board]);
                HuSprPosSet(sprite0, 0, cursor->x, m231_fieldOfsYTbl[board] + cursor->y);
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
    m231_doneTbl[board] = 1;
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m231_FieldDropProc(void) {
    s32 board = (s32)HuPrcCurrentGet()->user_data;
    f32 speed = 0.0f;

    m231_fieldSlideTbl[board] = 0;
    while (m231_fieldSlideTbl[board] < 300) {
        speed += 0.5f;
        m231_fieldSlideTbl[board] = m231_fieldSlideTbl[board] + speed;
        HuPrcVSleep();
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m231_DebrisObjMain(omObjData *obj) {
    MarioPuzzlePartyDebris *debris = &m231_debrisTbl[obj->work[0]];

    switch (obj->work[1]) {
        case 0:
            switch (obj->work[2]) {
                case 0:
                    debris->vy = -3.0f;
                    debris->vx = -1.0f - (rand8() % 10) * 0.1f;
                    break;
                case 1:
                    debris->vy = -5.0f;
                    debris->vx = -1.0f - (rand8() % 10) * 0.1f;
                    break;
                case 2:
                    debris->vy = -3.0f;
                    debris->vx = (rand8() % 10) * 0.1f + 1.0f;
                    break;
                default:
                    debris->vy = -5.0f;
                    debris->vx = (rand8() % 10) * 0.1f + 1.0f;
                    break;
            }
            obj->work[1] = 1;
        case 1:
            debris->vy += 1.0f;
            debris->y += debris->vy;
            debris->x += debris->vx;
            m231_SprBatchPosSet(debris->sprite, debris->x, debris->y);
            if (debris->y > 250.0f) {
                obj->work[1] = 2;
            }
            break;
        case 2:
            m231_SprBatchEntryKill(debris->sprite);
            debris->active = FALSE;
            obj->work[1] = 100;
            omDelObj(obj);
            break;
    }
}

void m231_DebrisCreate(s32 board, s32 pathIdx, s32 spaceIdx) {
    MarioPuzzlePartyDebris *debris;
    omObjData *obj;
    s32 slots[4];
    s32 count;
    s32 i;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;

    debris = m231_debrisTbl;
    count = 0;
    for (i = 0; i < 160; i++, debris++) {
        if (debris->active == FALSE) {
            slots[count] = i;
            count++;
            if (count >= 4) {
                break;
            }
        }
    }
    if (i < 160) {
        x = m231_fieldPosTbl[board][0] + pathIdx * 14;
        y = m231_fieldPosTbl[board][1] - spaceIdx * 7;
        i = 0;
        for (dx = 0; dx < 8; dx += 7) {
            for (dy = 0; dy >= -7; dy -= 7) {
                debris = &m231_debrisTbl[slots[i]];
                debris->active = TRUE;
                debris->x = x + dx;
                debris->y = y + dy;
                debris->unk_14 = 1.0f;
                debris->sprite = m231_SprBatchEntryAdd(28, debris->x, debris->y);
                obj = omAddObj(100, 0, 0, -1, m231_DebrisObjMain);
                obj->work[0] = slots[i];
                obj->work[1] = 0;
                obj->work[2] = i;
                i++;
            }
        }
    }
}

void m231_SparkleKill(void) {
    HuMemDelayFree(HuPrcCurrentGet()->user_data);
}

void m231_SparkleProc(void) {
    MarioPuzzlePartySparkle *sparkle = HuPrcCurrentGet()->user_data;
    f32 baseX;
    f32 baseY;
    f32 vx;
    f32 vy;
    f32 scale;

    omPrcSetDestructor(HuPrcCurrentGet(), m231_SparkleKill);
    sparkle->sprGroup = HuSprGrpCreate(1, 5);
    HuSprGrpMemberSet(sparkle->sprGroup, 0, m231_sparkleAnimLo, 0);
    HuSprAttrReset(sparkle->sprGroup, 0, 0xFFFF);
    HuSprAttrSet(sparkle->sprGroup, 0, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_BG | HUSPR_ATTR_FILTER_BILERP);
    HuSprPriSet(sparkle->sprGroup, 0, 0x1000);
    baseX = sparkle->x;
    baseY = sparkle->y;
    while (TRUE) {
        HuPrcSleep(rand8() % 90);
        HuSprAttrReset(sparkle->sprGroup, 0, HUSPR_ATTR_DISPOFF);
        sparkle->x = baseX;
        sparkle->y = baseY;
        vx = sparkle->vx;
        vy = sparkle->vy;
        switch (sparkle->spawnMode) {
            case 0:
                sparkle->x = baseX + rand8() % 40 - 20.0f;
                break;
            case 1:
                sparkle->y = baseY + rand8() % 40 - 20.0f;
                break;
            default:
                sparkle->x = baseX + rand8() % 20 - 10.0f;
                sparkle->y = baseY + rand8() % 20 - 10.0f;
                break;
        }
        switch (rand8() & 1) {
            case 0:
            default:
                scale = 1.2f;
                break;
            case 1:
                scale = 2.0f;
                if (vx != 0.0f) {
                    if (vx > 0.0f) {
                        vx -= 1.0f;
                    } else {
                        vx += 1.0f;
                    }
                }
                if (vy != 0.0f) {
                    if (vy > 0.0f) {
                        vy -= 1.0f;
                    } else {
                        vy += 1.0f;
                    }
                }
                break;
        }
        sparkle->scale = scale;
        while (sparkle->scale > 0.0f) {
            switch (sparkle->moveMode) {
                case 0:
                    sparkle->y = vy + sparkle->y;
                    break;
                case 1:
                    sparkle->x = vx + sparkle->x;
                    break;
                default:
                    sparkle->x = vx + sparkle->x;
                    sparkle->y = vy + sparkle->y;
                    break;
            }
            HuSprPosSet(sparkle->sprGroup, 0, sparkle->x, sparkle->y);
            HuSprScaleSet(sparkle->sprGroup, 0, sparkle->scale, sparkle->scale);
            HuPrcVSleep();
            sparkle->scale -= 0.03f;
        }
        HuSprAttrSet(sparkle->sprGroup, 0, HUSPR_ATTR_DISPOFF);
    }
}

void m231_FieldShakeProc(void) {
    s32 board = (s32)HuPrcCurrentGet()->user_data;
    f32 angle = 0.0f;

    while (TRUE) {
        angle += 90.0f;
        if (angle > 1080.0f) {
            break;
        }
        m231_fieldShakeTbl[board] = sindf(angle) * 2.0f;
        HuPrcVSleep();
    }
    m231_fieldShakeTbl[board] = 0;
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m231_CursorDispProc(void) {
    MarioPuzzlePartyCursor *cursor;
    MarioPuzzlePartyCursor *next;
    s32 i;

    while (TRUE) {
        for (i = 0; i < 4; i++) {
            cursor = &m231_cursorTbl[i];
            if (cursor->blockOwners[0] == 7 && m231_bigBlockGrpTbl[i] != -1) {
                if (omPauseChk() + omAllPauseF != 0 || m231_gameOverTbl[i] != 0) {
                    HuSprAttrSet(m231_bigBlockGrpTbl[i], 0, HUSPR_ATTR_DISPOFF);
                } else {
                    HuSprAttrReset(m231_bigBlockGrpTbl[i], 0, HUSPR_ATTR_DISPOFF);
                }
            }
            next = &m231_nextTbl[i];
            if (next->blockOwners[0] == 7) {
                if (omPauseChk() + omAllPauseF != 0 || m231_gameOverTbl[i] != 0) {
                    HuSprAttrSet(next->blockSprites[0], 0, HUSPR_ATTR_DISPOFF);
                } else {
                    HuSprAttrReset(next->blockSprites[0], 0, HUSPR_ATTR_DISPOFF);
                }
            }
            if (omPauseChk() + omAllPauseF != 0 || m231_gameOverTbl[i] != 0) {
                espDispOff(cursor->sprite);
            } else {
                espDispOn(cursor->sprite);
            }
        }
        HuPrcVSleep();
    }
}

void m231_FieldSwayProc(void) {
    s32 stopped[4];
    f32 angle[4];
    f32 offset[4];
    MarioPuzzlePartyCursor *cursor;
    s32 i;

    for (i = 0; i < 4; i++) {
        offset[i] = 0.0f;
        angle[i] = 0.0f;
        stopped[i] = FALSE;
    }
    while (TRUE) {
        for (i = 0; i < 4; i++) {
            if (stopped[i] == FALSE && MgFlowStatGet() != MG_STATE_OPENING) {
                angle[i] += 8.0f;
                offset[i] = sindf(i * 45.0f + angle[i]) * 3.0f;
                if (angle[i] > 360.0f) {
                    angle[i] -= 360.0f;
                }
                if ((angle[i] > 360.0f || angle[i] > 180.0f) && m231_doneTbl[i] != 0) {
                    stopped[i] = TRUE;
                    offset[i] = 0.0f;
                }
            }
            m231_fieldOfsYTbl[i] =
                (s32)offset[i] + m231_fieldShakeTbl[i] + m231_fieldSlideTbl[i];
            m231_SprBatchOfsYSet(i, m231_fieldOfsYTbl[i]);
            if (stopped[i] == FALSE) {
                HuSprPosSet(m231_headGrpTbl[i], 0, m231_fieldPosTbl[i][0] + 42,
                            m231_fieldOfsYTbl[i] + m231_fieldPosTbl[i][1] - 181);
            }
            HuSprPosSet(m231_signGrpTbl[i], 0, m231_fieldPosTbl[i][0] + 42,
                        m231_fieldOfsYTbl[i] + m231_fieldPosTbl[i][1] - 160);
            HuSprPosSet(m231_fieldBackGrpTbl[i], 0, m231_fieldPosTbl[i][0] + 42,
                        m231_fieldOfsYTbl[i] + m231_fieldPosTbl[i][1] - 76);
            HuSprPosSet(m231_fieldFrameGrpTbl[i], 0, m231_fieldPosTbl[i][0] + 42,
                        m231_fieldOfsYTbl[i] + m231_fieldPosTbl[i][1] - 76);
            HuSprPosSet(m231_chrFaceGrpTbl[i], 0, m231_fieldPosTbl[i][0] + 42,
                        m231_fieldOfsYTbl[i] + m231_fieldPosTbl[i][1] - 104);
            cursor = &m231_cursorTbl[i];
            if (cursor->blockOwners[0] != 7) {
                espPosSet(cursor->sprite, cursor->x + 7.0f, m231_fieldOfsYTbl[i] + cursor->y);
            } else {
                if (m231_bigBlockGrpTbl[i] != -1) {
                    HuSprPosSet(cursor->blockSprites[0], 0, cursor->x, m231_fieldOfsYTbl[i] + cursor->y);
                    if (omPauseChk() + omAllPauseF != 0) {
                        HuSprAttrSet(cursor->blockSprites[0], 0, HUSPR_ATTR_DISPOFF);
                    } else {
                        HuSprAttrReset(cursor->blockSprites[0], 0, HUSPR_ATTR_DISPOFF);
                    }
                }
                espPosSet(cursor->sprite, cursor->x + 7.0f, cursor->y + 7.0f + m231_fieldOfsYTbl[i]);
            }
            cursor = &m231_nextTbl[i];
            if (cursor->blockOwners[0] == 7) {
                HuSprPosSet(cursor->blockSprites[0], 0, cursor->x, m231_fieldOfsYTbl[i] + cursor->y);
                if (omPauseChk() + omAllPauseF != 0) {
                    HuSprAttrSet(cursor->blockSprites[0], 0, HUSPR_ATTR_DISPOFF);
                } else {
                    HuSprAttrReset(cursor->blockSprites[0], 0, HUSPR_ATTR_DISPOFF);
                }
            }
        }
        HuPrcVSleep();
    }
}

void m231_RecordProc(void) {
    s32 group = HuSprGrpCreate(6, 5);
    s32 unused[8]; // Retain the original stack frame.
    s32 record;
    s32 started;
    s32 j;
    s32 xOffset;
    s32 newXOffset;
    s32 newWidth;
    s32 i;
    f32 angle;

    HuSprGrpMemberSet(group, 0, m231_recordDigitAnimLo, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, HUSPR_ATTR_DISPOFF);
    HuSprParentSet(group, 0, -1);
    HuSprPriSet(group, 0, 0x100);
    record = GWMgRecordGet(8);

    // j is the place value divisor, i is the digit sprite member.
    for (i = 1, j = 1000, started = FALSE; i < 5; i++, j /= 10) {
        HuSprGrpMemberSet(group, i, m231_recordDigitAnimLo, (record / j) % 10);
        HuSprAnimModeSet(group, i, HUSPR_ANIM_MODE_BANK);
        HuSprAttrReset(group, i, 0xFFFF);
        HuSprAttrSet(group, i, HUSPR_ATTR_FILTER_BILERP);
        if (!started) {
            if ((record / j) % 10 == 0 && i != 4) {
                HuSprAttrSet(group, i, HUSPR_ATTR_DISPOFF);
            } else {
                started = TRUE;
            }
        }
        HuSprPriSet(group, i, 0x100);
        HuSprParentSet(group, i, 0);
    }
    // j is the digit count, i is the place value divisor.
    for (j = 4, i = 1000; j >= 2; j--, i /= 10) {
        if (record / i != 0) {
            break;
        }
    }
    xOffset = 58;
    j = j * 12 + 10; // Total width.
    for (i = 1; i < 5; i++) {
        HuSprPosSet(group, i, i * 12 - xOffset + (j >> 1), 0);
    }
    HuSprPosSet(group, 5, 65 - xOffset + (j >> 1), 0);
    HuSprPosSet(group, 0, 90 - (j >> 1), 30);

    HuSprGrpMemberSet(group, 5, m231_recordLabelAnimLo, 0);
    HuSprAnimModeSet(group, 5, HUSPR_ANIM_MODE_STOP);
    HuSprAttrReset(group, 5, 0xFFFF);
    HuSprAttrSet(group, 5, HUSPR_ATTR_FILTER_BILERP);
    HuSprPriSet(group, 5, 0x100);
    HuSprParentSet(group, 5, 0);
    while (m231_mgFlow.state != MG_STATE_RESULT) {
        HuPrcVSleep();
    }

    if (m231_winner != -1 && record < m231_scoreTbl[0]) {
        record = m231_scoreTbl[0];
        for (i = 1, j = 1000, started = FALSE; i < 5; i++, j /= 10) {
            HuSprGrpMemberSet(group, i, m231_recordDigitAnimLo, (record / j) % 10);
            HuSprAnimModeSet(group, i, HUSPR_ANIM_MODE_BANK);
            HuSprAttrReset(group, i, 0xFFFF);
            HuSprAttrSet(group, i, HUSPR_ATTR_FILTER_BILERP);
            if (!started) {
                if ((record / j) % 10 == 0 && i != 4) {
                    HuSprAttrSet(group, i, HUSPR_ATTR_DISPOFF);
                } else {
                    started = TRUE;
                }
            }
            HuSprPriSet(group, i, 0x100);
            HuSprParentSet(group, i, 0);
        }
        for (j = 4, i = 1000; j >= 2; j--, i /= 10) {
            if (record / i != 0) {
                break;
            }
        }
        newXOffset = 58;
        newWidth = j * 12 + 10;
        for (i = 1; i < 5; i++) {
            HuSprPosSet(group, i, i * 12 - newXOffset + (newWidth >> 1), 0);
        }
        HuSprPosSet(group, 5, 65 - newXOffset + (newWidth >> 1), 0);
        HuSprPosSet(group, 0, 90 - (newWidth >> 1), 30);

        for (angle = 0.0f; angle < 180.0f; angle += 9.0f) {
            for (i = 0; i < 6; i++) {
                HuSprScaleSet(group, i, sindf(angle) + 1.0f, sindf(angle) + 1.0f);
            }
            HuPrcVSleep();
        }
        for (i = 0; i < 6; i++) {
            HuSprScaleSet(group, i, 1.0f, 1.0f);
        }
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m231_TimerDisp(s32 group, s32 time) {
    s32 minutes;
    s32 tens;
    s32 seconds;
    s32 tenths;

    HuSprBankSet(group, 1, minutes = time / 3600, 0);
    HuSprAnimModeSet(group, 1, HUSPR_ANIM_MODE_BANK);
    time -= minutes * 3600;
    HuSprBankSet(group, 2, 10, 0);
    HuSprAnimModeSet(group, 2, HUSPR_ANIM_MODE_BANK);
    HuSprBankSet(group, 3, tens = time / 600, 0);
    HuSprAnimModeSet(group, 3, HUSPR_ANIM_MODE_BANK);
    time -= tens * 600;
    HuSprBankSet(group, 4, seconds = time / 60, 0);
    HuSprAnimModeSet(group, 4, HUSPR_ANIM_MODE_BANK);
    time = time * 100 / 60 - seconds * 100;
    HuSprBankSet(group, 5, 11, 0);
    HuSprAnimModeSet(group, 5, HUSPR_ANIM_MODE_BANK);
    HuSprBankSet(group, 6, tenths = time / 10, 0);
    HuSprAnimModeSet(group, 6, HUSPR_ANIM_MODE_BANK);
    HuSprBankSet(group, 7, time - tenths * 10, 0);
    HuSprAnimModeSet(group, 7, HUSPR_ANIM_MODE_BANK);
}

void m231_TimerProc(void) {
    s32 group = HuSprGrpCreate(8, 5);
    s32 i;
    s16 x;

    HuSprGrpMemberSet(group, 0, m231_timerDigitAnimLo, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, HUSPR_ATTR_DISPOFF);
    HuSprParentSet(group, 0, -1);
    HuSprPriSet(group, 0, 0x100);
    HuSprPosSet(group, 0, 215, 30);
    m231_timer = 5400;
    for (i = 1, x = 0; i < 8; i++) {
        HuSprAnimModeSet(group, i, HUSPR_ANIM_MODE_BANK);
        HuSprGrpMemberSet(group, i, m231_timerDigitAnimLo, 0);
        HuSprAttrReset(group, i, 0xFFFF);
        HuSprAttrSet(group, i, HUSPR_ATTR_FILTER_BILERP);
        HuSprPriSet(group, i, 0x100);
        HuSprParentSet(group, i, 0);
        HuSprPosSet(group, i, x, 0);
        switch (i) {
            case 1:
                x += 4;
                break;
            case 4:
                x += 8;
                break;
            default:
                x += 12;
                break;
        }
    }
    m231_TimerDisp(group, m231_timer * 2);
    while (MgFlowStatGet() != MG_STATE_PLAY) {
        HuPrcVSleep();
    }
    while (m231_timer != 0 && m231_doneTbl[0] == 0) {
        m231_TimerDisp(group, m231_timer * 2);
        HuPrcVSleep();
        m231_timer--;
    }
    m231_TimerDisp(group, m231_timer * 2);
    omDelPrcObj(NULL);
}

void m231_BigBlockFallProc(void) {
    s32 startX = (s32)HuPrcCurrentGet()->user_data;
    s32 group = HuSprGrpCreate(1, 5);
    f32 x;
    f32 y;
    f32 speed;

    HuSprGrpMemberSet(group, 0, m231_bigBlockAnimLo, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, HUSPR_ATTR_FILTER_BILERP);
    HuSprScaleSet(group, 0, 0.8f, 0.8f);
    x = startX;
    while (TRUE) {
        HuPrcSleep(rand8() % 30 + 300);
        if (m231_timer < 300 || m231_doneTbl[0] != 0) {
            break;
        }
        y = -30.0f;
        speed = 0.0f;
        do {
            speed += 0.3f;
            if (speed > 7.0f) {
                speed = 7.0f;
            }
            y += speed;
            HuSprPosSet(group, 0, x, y);
            HuPrcVSleep();
        } while (y < 270.0f);
    }
    omDelPrcObj(NULL);
}

void m231_PlayerPrcKillAll(void) {
    s32 i;

    for (i = 0; i < m231_playerNum; i++) {
        if (m231_doneTbl[i] == 0) {
            omDelPrcObj(m231_playerPrcTbl[i]);
        }
    }
}

void m231_MainProc(void) {
    s32 flag = FALSE; // Tie flag while picking the winner, then the "new record" flag
    s32 timer = 0;
    MinigameFlow *flow;
    s32 running;
    Process *process;
    s32 best;
    s32 winner;
    s32 count;
    s32 pick;
    s32 i;
    s32 j;

    m231_winner = -1;
    flow = &m231_mgFlow;
    MgFlowStartDelaySet(0);
    mgFlowSeqTime = 60;
    for (i = 0; i < 4; i++) {
        m231_fieldSlideTbl[i] = 240;
    }
    if (m231_mode == 2) {
        i = 4;
        process = omAddPrcObj(m231_ScoreFlyProc, 0x4001, 0x800, 0);
        HuPrcChildLink(HuPrcCurrentGet(), process);
        process->user_data = (void *)i;
    } else {
        for (i = 0; i < 4; i++) {
            process = omAddPrcObj(m231_ScoreFlyProc, 0x4001, 0x800, 0);
            HuPrcChildLink(HuPrcCurrentGet(), process);
            process->user_data = (void *)i;
        }
    }
    HuPrcChildWatch();
    while (m231_fieldSlideTbl[0] > 0) {
        for (i = 0; i < 4; i++) {
            m231_fieldSlideTbl[i] -= 5;
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        m231_fieldSlideTbl[i] = 0;
    }
    running = TRUE;
    while (running) {
        switch (MgFlowMain()) {
            case 0:
                MgFlowStatNext();
                break;
            case 1:
                break;
            case 2:
                j = 0;
                best = 0;
                winner = 0;
                flag = FALSE;
                for (; j < m231_playerNum; j++) {
                    if (m231_scoreTbl[j] >= m231_goalScore) {
                        if (best < m231_scoreTbl[j]) {
                            best = m231_scoreTbl[j];
                            winner = j;
                            flag = FALSE;
                        } else if (best == m231_scoreTbl[j]) {
                            flag = TRUE;
                        }
                    }
                }
                if (best != 0) {
                    if (!flag) {
                        m231_winner = winner;
                        m231_PlayerPrcKillAll();
                        MgFlowStatNext();
                    } else {
                        for (j = 0, count = 0; j < 4; j++) {
                            if (m231_scoreTbl[j] == best) {
                                count++;
                            }
                        }
                        pick = rand8() * (1.0f / 256.0f) * count;
                        for (j = 0, count = 0; j < 4; j++) {
                            if (m231_scoreTbl[j] == best) {
                                if (pick == count) {
                                    m231_winner = j;
                                    m231_PlayerPrcKillAll();
                                    MgFlowStatNext();
                                    break;
                                }
                                count++;
                            }
                        }
                    }
                }
                if (m231_mode != 2) {
                    for (j = 0, count = 0; j < m231_playerNum; j++) {
                        if (m231_doneTbl[j] == 0) {
                            winner = j;
                            count++;
                        }
                    }
                    if (count == 1) {
                        m231_winner = winner;
                        m231_PlayerPrcKillAll();
                        MgFlowStatNext();
                    }
                }
                for (j = 0; j < m231_playerNum; j++) {
                    if (m231_doneTbl[j] == 0) {
                        break;
                    }
                }
                if (j >= m231_playerNum) {
                    m231_PlayerPrcKillAll();
                    MgFlowStatNext();
                }
                if (m231_mode == 2 && m231_timer == 0) {
                    m231_winner = 0;
                    m231_PlayerPrcKillAll();
                    MgFlowStatNext();
                }
                break;
            case 3:
                if (MgFlowStatTimeGet() == 1) {
                    if (m231_mode == 2) {
                        if (m231_scoreTbl[0] > m231_goalScore) {
                            m231_scoreTbl[0] = m231_goalScore;
                        }
                        if (m231_winner != -1) {
                            if (GWMgRecordGet(8) < m231_scoreTbl[0]) {
                                flag = TRUE;
                                flow->newRecord = TRUE;
                                GWMgRecordSet(8, (u16)m231_scoreTbl[0]);
                                timer = 0;
                                m231_mgFlow.resultDelay = 0x73;
                            } else {
                                flag = FALSE;
                                timer = 0;
                                m231_mgFlow.resultDelay = 0x64;
                            }
                        } else {
                            timer = 0;
                            m231_mgFlow.resultDelay = 0x6B;
                        }
                        flow->resultType = MG_RESULT_NONE;
                    } else if (m231_winner != -1) {
                        m231_mgFlow.resultDelay = 0x96;
                        flow->resultType = MG_RESULT_WIN_1;
                        flow->winners[0] = m231_winner;
                        GwPlayer[m231_winner].bonusCoin += 10;
                    } else {
                        m231_mgFlow.resultDelay = 0xA0;
                        flow->resultType = MG_RESULT_DRAW;
                    }
                }
                break;
            case 4:
                if (m231_mode == 2) {
                    if (--timer == -1) {
                        if (m231_winner != -1) {
                            if (flag) {
                                HuAudSeqPlay(0x6A);
                            } else {
                                HuAudSeqPlay(0x65);
                            }
                        } else {
                            HuAudSeqPlay(0x6B);
                        }
                    }
                }
                break;
            case 5:
                running = FALSE;
                break;
        }
        HuPrcVSleep();
    }
    omSysExitReq = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}
