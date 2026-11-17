#include "common.h"
#include "game/audio.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/input.h"
#include "game/object.h"
#include "game/mallocblock.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "gcc/memory.h"
#include "game/wipe.h"
#include "math.h"
#include "game/overlays/minigame.h"

typedef struct PictureImperfectWork {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ s8 unk03;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ s8 unk05;
    /* 0x06 */ s8 unk06;
    /* 0x07 */ s8 unk07;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ char unk1A[0x2];
} PictureImperfectWork; // Size 0x1C

typedef struct PictureImperfectGameData {
    /* 0x00 */ u8 unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ u8 unk0C[0xA8];
} PictureImperfectGameData; // Size 0xB4

typedef struct PictureImperfectScorePos {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} PictureImperfectScorePos; // Size 0x4

// Grouped BSS variables; individual fields are aliased in undefined_syms.txt.
typedef struct PictureImperfectStat {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s8 unk02[4];
    /* 0x06 */ s8 unk06[4];
    /* 0x0A */ s16 unk0A[4];
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
} PictureImperfectStat; // Size 0x18

typedef struct PictureImperfectSpr {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02[5];
    /* 0x0C */ s16 unk0C[5];
    /* 0x16 */ s16 unk16[5];
    /* 0x20 */ s16 unk20[5];
    /* 0x2A */ s16 unk2A[5];
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E[4];
    /* 0x46 */ s16 unk46[4];
    /* 0x4E */ s16 unk4E[4];
    /* 0x56 */ s16 unk56[4];
    /* 0x5E */ s16 unk5E[4];
    /* 0x66 */ s16 unk66[4];
    /* 0x6E */ s16 unk6E[4];
    /* 0x76 */ s16 unk76;
    /* 0x78 */ s16 unk78;
    /* 0x7A */ s16 unk7A;
} PictureImperfectSpr; // Size 0x7C

extern u32 omCharModelNoTbl[][6];
extern s32 omCharMotTbl[][6];
extern u8 storySceneNo;
extern u8 omAllPauseF;

s16 m230_cycleSe = -1;
s16 m230_cycleSeF = 1;
u8 m230_resultPhase = 0;
PictureImperfectScorePos m230_scorePosTbl[4] = { { 80, 60 }, { 240, 60 }, { 80, 180 }, { 240, 180 } };
s8 m230_winnerTbl[4] = { -1, -1, -1, -1 };
s8 m230_partChoiceTbl[4][5] = {
    { -1, -1, -1, -1, -1 },
    { -1, -1, -1, -1, -1 },
    { -1, -1, -1, -1, -1 },
    { -1, -1, -1, -1, -1 }
};
s32 m230_exitTimer = 0;
s8 m230_exitF = 0;
PictureImperfectScorePos m230_picturePosTbl[4] = { { 59, 55 }, { 219, 55 }, { 59, 175 }, { 219, 175 } };
s8 m230_playerCreateNo = 0;
s32 m230_blockHitCnt = 0;
u8 m230_partOrderTbl[4][5] = {
    { 0, 1, 2, 3, 4 },
    { 4, 2, 0, 3, 1 },
    { 2, 3, 1, 4, 0 },
    { 1, 4, 2, 0, 3 }
};
u32 m230_frameCnt = 0;
s8 m230_popOfsYTbl[8] = { -20, -10, 0, 10, 20, 0, 0, 0 };
f32 m230_sampleScale = 1.0f;
u8 m230_introPhase = 0;
u8 m230_sampleAlpha = 0xFF;
u8 m230_introTimer = 0;

PictureImperfectStat m230_stat BSS;
MinigameFlow m230_mgFlow BSS;
u8 m230_pictureNo BSS;
u8 m230_partOrderNo BSS;
s16 m230_frameGrp BSS;
s16 m230_screenGrp BSS;
s16 m230_sampleFrameSpr BSS;
s16 m230_sampleSpr BSS;
s16 m230_sampleCoverSpr BSS;
s16 m230_pictureGrpTbl[4] BSS;
u8 m230_pictureGrpTblPad[4] BSS; /* Unreferenced. */
s16 m230_part0SprTbl[4][5] BSS;
s16 m230_part1SprTbl[4][5] BSS;
s16 m230_part2SprTbl[4][5] BSS;
s16 m230_part3SprTbl[4][5] BSS;
s16 m230_part4SprTbl[4][5] BSS;
PictureImperfectSpr m230_spr BSS;
s8 m230_partCycleTbl[5] BSS;

/* Fields of m230_stat, m230_mgFlow and m230_spr (aliased in undefined_syms.txt). */
extern s8 m230_winnerNum;
extern s8 m230_partDoneCnt;
extern s8 m230_popTimerTbl[4];
extern s8 m230_popBlinkTbl[4];
extern s16 m230_scoreTimerTbl[4];
extern s16 m230_sprAnim;
extern s16 m230_shrinkSe;
extern u8 m230_mgFlowWinnerTbl[4];
extern s16 m230_pictureAnim;
extern s16 m230_part0AnimTbl[5];
extern s16 m230_part1AnimTbl[5];
extern s16 m230_part2AnimTbl[5];
extern s16 m230_part3AnimTbl[5];
extern s16 m230_part4AnimTbl[5];
extern s16 m230_popPlusAnim;
extern s16 m230_popDigitAnim;
extern s16 m230_popPtAnim;
extern s16 m230_digitAnim;
extern s16 m230_ptAnim;
extern s16 m230_popPlusTbl[4];
extern s16 m230_popTensTbl[4];
extern s16 m230_popOnesTbl[4];
extern s16 m230_popPtTbl[4];
extern s16 m230_scoreTensTbl[4];
extern s16 m230_scoreOnesTbl[4];
extern s16 m230_scorePtTbl[4];
extern s16 m230_maxScoreTensSpr;
extern s16 m230_maxScoreOnesSpr;
extern s16 m230_maxScorePtSpr;

void m230_PictureAnimRead(void);
void m230_FlowInit(MinigameFlow *flow);
void m230_CameraInit(void);
void m230_MainObjMain(omObjData *object);
void m230_PlayerObjInit(omObjData *object);
void m230_PlayerComInput(omObjData *object);
void m230_PartCycleUpdate(s8 player);
void m230_PartUpdate(omObjData *object);
void m230_PartDispOff(PictureImperfectWork *work, s8 player);
void m230_PointPopUpdate(PictureImperfectWork *work, s8 player);
void m230_ScoreDispUpdate(PictureImperfectWork *work, s8 player);
void m230_MapObjInit(omObjData *object);
void m230_PlayerObjMain(omObjData *object);
void m230_MapObjMain(omObjData *object);

void m230_ObjectSetup(void) {
    omObjData *object;
    s32 i;

    MapCollInit(0x20);
    Hu3DQuadPoolInit(&mgQuadPool, 0x40);
    Hu3DSprModelInit(0x40);
    omInitObjMan(0x20, 0);
    omGameSysInit();
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    MgFieldStatClear();
    m230_CameraInit();
    m230_pictureNo = 2 - storySceneNo;
    m230_PictureAnimRead();
    m230_FlowInit(&m230_mgFlow);
    MgFlowInit(&m230_mgFlow);
    Hu3DGLightColorSet(1, 0x40, 0x40, 0x40);
    Hu3DGLightDirSet(1, 0.0f, 0.0f, 100.0f);
    m230_partOrderNo = rand8() >> 6;
    object = omAddObj(0, 0, 0, -1, m230_MainObjMain);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    MgMapBaseSet(mgMapObjNum);
    mgMapObjTbl[mgMapObjNum++] = omAddObj(0, 1, 0, -1, m230_MapObjInit);
    for (i = 0; i < 4; i++) {
        mgPlayerObjTbl[i] = omAddObj(1, 4, 60, -1, m230_PlayerObjInit);
        omSetStatBit(mgPlayerObjTbl[i], OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    }
    object = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    object->work[0] = 4;
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
}

void m230_PictureAnimRead(void) {
    s32 i;

    switch (m230_pictureNo) {
        case 0:
            m230_pictureAnim = HuSprAnimDataRead(0x3F0005);
            for (i = 0; i < 5; i++) {
                m230_part0AnimTbl[i] = HuSprAnimDataRead((i + 14) | 0x3F0000);
                m230_part1AnimTbl[i] = HuSprAnimDataRead((i + 19) | 0x3F0000);
                m230_part2AnimTbl[i] = HuSprAnimDataRead((i + 24) | 0x3F0000);
                m230_part3AnimTbl[i] = HuSprAnimDataRead((i + 29) | 0x3F0000);
                m230_part4AnimTbl[i] = HuSprAnimDataRead((i + 34) | 0x3F0000);
            }
            break;
        case 1:
            m230_pictureAnim = HuSprAnimDataRead(0x3F0006);
            for (i = 0; i < 5; i++) {
                m230_part0AnimTbl[i] = HuSprAnimDataRead((i + 39) | 0x3F0000);
                m230_part1AnimTbl[i] = HuSprAnimDataRead((i + 44) | 0x3F0000);
                m230_part2AnimTbl[i] = HuSprAnimDataRead((i + 49) | 0x3F0000);
                m230_part3AnimTbl[i] = HuSprAnimDataRead((i + 54) | 0x3F0000);
            }
            break;
        case 2:
        default:
            m230_pictureAnim = HuSprAnimDataRead(0x3F0007);
            for (i = 0; i < 5; i++) {
                m230_part0AnimTbl[i] = HuSprAnimDataRead((i + 59) | 0x3F0000);
                m230_part1AnimTbl[i] = HuSprAnimDataRead((i + 64) | 0x3F0000);
                m230_part2AnimTbl[i] = HuSprAnimDataRead((i + 69) | 0x3F0000);
            }
            break;
    }
    m230_popPlusAnim = HuSprAnimDataRead(0x40001C);
    m230_popDigitAnim = HuSprAnimDataRead(0x40001B);
    m230_popPtAnim = HuSprAnimDataRead(0x40001D);
    m230_digitAnim = HuSprAnimDataRead(0x2E);
    m230_ptAnim = HuSprAnimDataRead(0x3E0019);
}

void m230_FlowInit(MinigameFlow *flow) {
    s32 i;

    mgFlowSeqTime = 10;
    flow->state = MG_STATE_OPENING;
    flow->type = MINIGAME_4P;
    flow->timerMode = MG_TIMER_COUNT_DOWN;
    flow->timeDisp = MG_TIME_DISP_COUNTDOWN;
    flow->newRecord = FALSE;
    flow->gauge = MG_GAUGE_NONE;
    flow->resultType = MG_RESULT_NONE;
    flow->startDelay = -1;
    flow->timer = 1800;
    flow->timeLimit = -1;
    flow->finishDelay = 360;
    flow->resultDelay = 162;
    for (i = 0; i < 4; i++) {
        flow->gaugeValue[i] = 0;
        flow->winners[i] = 0xFF;
    }
}

void m230_CameraInit(void) {
    s32 i;

    CamSetupMapCullAddMulti(4);
    CamSetupInit(4);
    for (i = 0; i < 4; i++) {
        CenterM[i].x = -200.0f;
        CenterM[i].y = 100.0f;
        CenterM[i].z = 0.0f;
        CRotM[i].x = CRotM[i].y = CRotM[i].z = 0.0f;
        CZoomM[i] = 2100.0f;
        Hu3DCameraPerspectiveSet(i, 30.0f, 80.0f, 8000.0f);
    }
    ScissorSet(0, 0.0f, 0.0f, 160.0f, 120.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 240.0f, 511.0f);
    ScissorSet(1, 160.0f, 0.0f, 320.0f, 120.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 240.0f, 511.0f);
    ScissorSet(2, 0.0f, 120.0f, 160.0f, 240.0f);
    ViewportSet(2, 640.0f, 480.0f, 511.0f, 320.0f, 720.0f, 511.0f);
    ScissorSet(3, 160.0f, 120.0f, 320.0f, 240.0f);
    ViewportSet(3, 640.0f, 480.0f, 511.0f, 960.0f, 720.0f, 511.0f);
}

void m230_MainObjMain(omObjData *object) {
    if (omPauseChk() + omAllPauseF == 0) {
        if (m230_exitF == 0 && omSysExitReq == 1) {
            HuAudFXAllStop();
            if (!(HuAudStat & 4)) {
                HuAudSeqFadeOut(30);
            } else {
                HuAudSeqStop();
            }
            MgFlowStatSet(MG_STATE_EXIT);
            m230_exitF = 1;
        }
        MgFieldStatUpdate();
        switch (MgFlowMain()) {
            case 0:
                mgFlowSeqNo = 49;
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                if (m230_exitTimer == 0) {
                    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                } else if (WipeStatGet() == 0 && !(HuAudStat & 4)) {
                    GameMesStub();
                    omOvlReturnEx(1);
                }
                m230_exitTimer++;
                break;
        }
    }
}

void m230_PlayerObjInit(omObjData *object) {
    MgPlayerWork *playerData;
    PictureImperfectWork *work;
    s8 character;
    u32 model;
    s32 motion;
    s32 camera;
    s32 i;

    character = GwPlayer[m230_playerCreateNo].chr;
    model = omCharModelNoTbl[character][0];
    motion = omCharMotTbl[character][0];
    MgShadowAltSet(1);
    MgPlayerCreate(object, model, motion, m230_playerCreateNo, 0x2A9, 0x2B9);
    playerData = object->data;
    playerData->unk158 = HuMemAllocTag(sizeof(PictureImperfectWork), TAG_OVERLAY);
    memset(playerData->unk158, 0, sizeof(PictureImperfectWork));
    work = playerData->unk158;
    object->rot.x = object->rot.y = object->rot.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    object->trans.x = 0.0f;
    object->trans.y = -8.0f;
    object->trans.z = 0.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[1], object->scale.x, object->scale.y, object->scale.z);
    work->unk10 = 272.0f;
    object->model[2] = Hu3DModelRead(0x3F0000, 0x2B9);
    Hu3DModelPosSet(object->model[2], object->trans.x, work->unk10, object->trans.z);
    Hu3DModelScaleSet(object->model[2], 1.2f, 1.2f, 1.2f);
    object->model[3] = Hu3DModelRead(8, 0x88D);
    switch (m230_playerCreateNo) {
        case 0:
        default:
            camera = 1;
            break;
        case 1:
            camera = 2;
            break;
        case 2:
            camera = 4;
            break;
        case 3:
            camera = 8;
            break;
    }
    Hu3DModelCameraSet(object->model[0], camera);
    Hu3DModelCameraSet(object->model[1], camera);
    Hu3DModelCameraSet(object->model[2], camera);
    Hu3DModelCameraSet(object->model[3], camera);
    MgPlayerMapAttrSet(object, 0, 2);
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(character, 0), 1, 0);
    MgPlayerMotLoad(object, 6, CharMotionDataNumGet(character, 4), 1, 19);
    MgPlayerMotLoad(object, 21, CharMotionDataNumGet(character, 0x1F), 0, 0);
    MgPlayerMotLoad(object, 13, CharMotionDataNumGet(character, 0x2F), 1, 120);
    MgPlayerMotLoad(object, 14, CharMotionDataNumGet(character, 0x36), 1, 120);
    MgPlayerMotSet(object, 0);
    object->func = m230_PlayerObjMain;
    work->unk00 = 0;
    work->unk01 = 0;
    work->unk02 = 0;
    work->unk08 = 0;
    work->unk03 = 0;
    work->unk04 = 0;
    work->unk0A = 0xFF;
    work->unk0C = 1.0f;
    work->unk14 = 0.0f;
    work->unk05 = 0;
    work->unk06 = 0;
    work->unk07 = 0;
    work->unk18 = ((rand8() * 15) >> 7) + 30;
    switch (m230_pictureNo) {
        case 0:
            m230_pictureGrpTbl[m230_playerCreateNo] = HuSprGrpCreate(1, 0);
            HuSprGrpMemberSet(m230_pictureGrpTbl[m230_playerCreateNo], 0, m230_pictureAnim, 0);
            HuSprAttrReset(m230_pictureGrpTbl[m230_playerCreateNo], 0, 0xFFFF);
            HuSprAttrSet(m230_pictureGrpTbl[m230_playerCreateNo], 0, HUSPR_ATTR_BG | HUSPR_ATTR_XLU);
            HuSprPosSet(m230_pictureGrpTbl[m230_playerCreateNo], 0,
                        m230_picturePosTbl[m230_playerCreateNo].x,
                        m230_picturePosTbl[m230_playerCreateNo].y);
            HuSprPriSet(m230_pictureGrpTbl[m230_playerCreateNo], 0, 0xFFFF);
            for (i = 0; i < 5; i++) {
                m230_part0SprTbl[m230_playerCreateNo][i] = espEntry(m230_part0AnimTbl[i], 0, 1);
                espPosSet(m230_part0SprTbl[m230_playerCreateNo][i],
                          m230_picturePosTbl[m230_playerCreateNo].x,
                          m230_picturePosTbl[m230_playerCreateNo].y);
                espAttrSet(m230_part0SprTbl[m230_playerCreateNo][i], HUSPR_ATTR_BG | HUSPR_ATTR_XLU);
                espPriSet(m230_part0SprTbl[m230_playerCreateNo][i], 0xFFF0);
                espDispOff(m230_part0SprTbl[m230_playerCreateNo][i]);
                m230_part1SprTbl[m230_playerCreateNo][i] = espEntry(m230_part1AnimTbl[i], 0, 1);
                espPosSet(m230_part1SprTbl[m230_playerCreateNo][i],
                          m230_picturePosTbl[m230_playerCreateNo].x,
                          m230_picturePosTbl[m230_playerCreateNo].y);
                espAttrSet(m230_part1SprTbl[m230_playerCreateNo][i], HUSPR_ATTR_BG | HUSPR_ATTR_XLU);
                espPriSet(m230_part1SprTbl[m230_playerCreateNo][i], 0xFFF0);
                espDispOff(m230_part1SprTbl[m230_playerCreateNo][i]);
                m230_part2SprTbl[m230_playerCreateNo][i] = espEntry(m230_part2AnimTbl[i], 0, 1);
                espPosSet(m230_part2SprTbl[m230_playerCreateNo][i],
                          m230_picturePosTbl[m230_playerCreateNo].x,
                          m230_picturePosTbl[m230_playerCreateNo].y);
                espAttrSet(m230_part2SprTbl[m230_playerCreateNo][i], HUSPR_ATTR_BG | HUSPR_ATTR_XLU);
                espPriSet(m230_part2SprTbl[m230_playerCreateNo][i], 0xFFF0);
                espDispOff(m230_part2SprTbl[m230_playerCreateNo][i]);
                m230_part3SprTbl[m230_playerCreateNo][i] = espEntry(m230_part3AnimTbl[i], 0, 1);
                espPosSet(m230_part3SprTbl[m230_playerCreateNo][i],
                          m230_picturePosTbl[m230_playerCreateNo].x,
                          m230_picturePosTbl[m230_playerCreateNo].y);
                espAttrSet(m230_part3SprTbl[m230_playerCreateNo][i], HUSPR_ATTR_BG | HUSPR_ATTR_XLU);
                espPriSet(m230_part3SprTbl[m230_playerCreateNo][i], 0xFFF0);
                espDispOff(m230_part3SprTbl[m230_playerCreateNo][i]);
                m230_part4SprTbl[m230_playerCreateNo][i] = espEntry(m230_part4AnimTbl[i], 0, 1);
                espPosSet(m230_part4SprTbl[m230_playerCreateNo][i],
                          m230_picturePosTbl[m230_playerCreateNo].x,
                          m230_picturePosTbl[m230_playerCreateNo].y);
                espAttrSet(m230_part4SprTbl[m230_playerCreateNo][i], HUSPR_ATTR_BG | HUSPR_ATTR_XLU);
                espPriSet(m230_part4SprTbl[m230_playerCreateNo][i], 0xFFF0);
                espDispOff(m230_part4SprTbl[m230_playerCreateNo][i]);
            }
            break;
        case 1:
            m230_pictureGrpTbl[m230_playerCreateNo] = HuSprGrpCreate(1, 0);
            HuSprGrpMemberSet(m230_pictureGrpTbl[m230_playerCreateNo], 0, m230_pictureAnim, 0);
            HuSprAttrReset(m230_pictureGrpTbl[m230_playerCreateNo], 0, 0xFFFF);
            HuSprAttrSet(m230_pictureGrpTbl[m230_playerCreateNo], 0, HUSPR_ATTR_BG | HUSPR_ATTR_XLU);
            HuSprPosSet(m230_pictureGrpTbl[m230_playerCreateNo], 0,
                        m230_picturePosTbl[m230_playerCreateNo].x,
                        m230_picturePosTbl[m230_playerCreateNo].y);
            HuSprPriSet(m230_pictureGrpTbl[m230_playerCreateNo], 0, 0xFFFF);
            for (i = 0; i < 5; i++) {
                m230_part0SprTbl[m230_playerCreateNo][i] = espEntry(m230_part0AnimTbl[i], 0, 1);
                espPosSet(m230_part0SprTbl[m230_playerCreateNo][i],
                          m230_picturePosTbl[m230_playerCreateNo].x,
                          m230_picturePosTbl[m230_playerCreateNo].y);
                espAttrSet(m230_part0SprTbl[m230_playerCreateNo][i], HUSPR_ATTR_BG | HUSPR_ATTR_XLU);
                espPriSet(m230_part0SprTbl[m230_playerCreateNo][i], 0xFFF0);
                espDispOff(m230_part0SprTbl[m230_playerCreateNo][i]);
                m230_part1SprTbl[m230_playerCreateNo][i] = espEntry(m230_part1AnimTbl[i], 0, 1);
                espPosSet(m230_part1SprTbl[m230_playerCreateNo][i],
                          m230_picturePosTbl[m230_playerCreateNo].x,
                          m230_picturePosTbl[m230_playerCreateNo].y);
                espAttrSet(m230_part1SprTbl[m230_playerCreateNo][i], HUSPR_ATTR_BG | HUSPR_ATTR_XLU);
                espPriSet(m230_part1SprTbl[m230_playerCreateNo][i], 0xFFF0);
                espDispOff(m230_part1SprTbl[m230_playerCreateNo][i]);
                m230_part2SprTbl[m230_playerCreateNo][i] = espEntry(m230_part2AnimTbl[i], 0, 1);
                espPosSet(m230_part2SprTbl[m230_playerCreateNo][i],
                          m230_picturePosTbl[m230_playerCreateNo].x,
                          m230_picturePosTbl[m230_playerCreateNo].y);
                espAttrSet(m230_part2SprTbl[m230_playerCreateNo][i], HUSPR_ATTR_BG | HUSPR_ATTR_XLU);
                espPriSet(m230_part2SprTbl[m230_playerCreateNo][i], 0xFFF0);
                espDispOff(m230_part2SprTbl[m230_playerCreateNo][i]);
                m230_part3SprTbl[m230_playerCreateNo][i] = espEntry(m230_part3AnimTbl[i], 0, 1);
                espPosSet(m230_part3SprTbl[m230_playerCreateNo][i],
                          m230_picturePosTbl[m230_playerCreateNo].x,
                          m230_picturePosTbl[m230_playerCreateNo].y);
                espAttrSet(m230_part3SprTbl[m230_playerCreateNo][i], HUSPR_ATTR_BG | HUSPR_ATTR_XLU);
                espPriSet(m230_part3SprTbl[m230_playerCreateNo][i], 0xFFF0);
                espDispOff(m230_part3SprTbl[m230_playerCreateNo][i]);
            }
            break;
        case 2:
        default:
            m230_pictureGrpTbl[m230_playerCreateNo] = HuSprGrpCreate(1, 0);
            HuSprGrpMemberSet(m230_pictureGrpTbl[m230_playerCreateNo], 0, m230_pictureAnim, 0);
            HuSprAttrReset(m230_pictureGrpTbl[m230_playerCreateNo], 0, 0xFFFF);
            HuSprAttrSet(m230_pictureGrpTbl[m230_playerCreateNo], 0, HUSPR_ATTR_BG | HUSPR_ATTR_XLU);
            HuSprPosSet(m230_pictureGrpTbl[m230_playerCreateNo], 0,
                        m230_picturePosTbl[m230_playerCreateNo].x,
                        m230_picturePosTbl[m230_playerCreateNo].y);
            HuSprPriSet(m230_pictureGrpTbl[m230_playerCreateNo], 0, 0xFFFF);
            for (i = 0; i < 5; i++) {
                m230_part0SprTbl[m230_playerCreateNo][i] = espEntry(m230_part0AnimTbl[i], 0, 1);
                espPosSet(m230_part0SprTbl[m230_playerCreateNo][i],
                          m230_picturePosTbl[m230_playerCreateNo].x,
                          m230_picturePosTbl[m230_playerCreateNo].y);
                espAttrSet(m230_part0SprTbl[m230_playerCreateNo][i], HUSPR_ATTR_BG | HUSPR_ATTR_XLU);
                espPriSet(m230_part0SprTbl[m230_playerCreateNo][i], 0xFFF0);
                espDispOff(m230_part0SprTbl[m230_playerCreateNo][i]);
                m230_part1SprTbl[m230_playerCreateNo][i] = espEntry(m230_part1AnimTbl[i], 0, 1);
                espPosSet(m230_part1SprTbl[m230_playerCreateNo][i],
                          m230_picturePosTbl[m230_playerCreateNo].x,
                          m230_picturePosTbl[m230_playerCreateNo].y);
                espAttrSet(m230_part1SprTbl[m230_playerCreateNo][i], HUSPR_ATTR_BG | HUSPR_ATTR_XLU);
                espPriSet(m230_part1SprTbl[m230_playerCreateNo][i], 0xFFF0);
                espDispOff(m230_part1SprTbl[m230_playerCreateNo][i]);
                m230_part2SprTbl[m230_playerCreateNo][i] = espEntry(m230_part2AnimTbl[i], 0, 1);
                espPosSet(m230_part2SprTbl[m230_playerCreateNo][i],
                          m230_picturePosTbl[m230_playerCreateNo].x,
                          m230_picturePosTbl[m230_playerCreateNo].y);
                espAttrSet(m230_part2SprTbl[m230_playerCreateNo][i], HUSPR_ATTR_BG | HUSPR_ATTR_XLU);
                espPriSet(m230_part2SprTbl[m230_playerCreateNo][i], 0xFFF0);
                espDispOff(m230_part2SprTbl[m230_playerCreateNo][i]);
            }
            break;
    }
    m230_popPlusTbl[m230_playerCreateNo] = espEntry(m230_popPlusAnim, 0, 1);
    espPosSet(m230_popPlusTbl[m230_playerCreateNo],
              m230_picturePosTbl[m230_playerCreateNo].x,
              m230_picturePosTbl[m230_playerCreateNo].y);
    espAttrSet(m230_popPlusTbl[m230_playerCreateNo], HUSPR_ATTR_XLU);
    espPriSet(m230_popPlusTbl[m230_playerCreateNo], 15);
    espDispOff(m230_popPlusTbl[m230_playerCreateNo]);
    m230_popTensTbl[m230_playerCreateNo] = espEntry(m230_popDigitAnim, 0, 1);
    espPosSet(m230_popTensTbl[m230_playerCreateNo],
              m230_picturePosTbl[m230_playerCreateNo].x,
              m230_picturePosTbl[m230_playerCreateNo].y);
    espAttrSet(m230_popTensTbl[m230_playerCreateNo], HUSPR_ATTR_XLU);
    espPriSet(m230_popTensTbl[m230_playerCreateNo], 15);
    espDispOff(m230_popTensTbl[m230_playerCreateNo]);
    m230_popOnesTbl[m230_playerCreateNo] = espEntry(m230_popDigitAnim, 0, 1);
    espPosSet(m230_popOnesTbl[m230_playerCreateNo],
              m230_picturePosTbl[m230_playerCreateNo].x,
              m230_picturePosTbl[m230_playerCreateNo].y);
    espAttrSet(m230_popOnesTbl[m230_playerCreateNo], HUSPR_ATTR_XLU);
    espPriSet(m230_popOnesTbl[m230_playerCreateNo], 15);
    espDispOff(m230_popOnesTbl[m230_playerCreateNo]);
    m230_popPtTbl[m230_playerCreateNo] = espEntry(m230_popPtAnim, 0, 1);
    espPosSet(m230_popPtTbl[m230_playerCreateNo],
              m230_picturePosTbl[m230_playerCreateNo].x,
              m230_picturePosTbl[m230_playerCreateNo].y);
    espAttrSet(m230_popPtTbl[m230_playerCreateNo], HUSPR_ATTR_XLU);
    espPriSet(m230_popPtTbl[m230_playerCreateNo], 15);
    espDispOff(m230_popPtTbl[m230_playerCreateNo]);
    m230_scoreTensTbl[m230_playerCreateNo] = espEntry(m230_digitAnim, 0, 1);
    espPosSet(m230_scoreTensTbl[m230_playerCreateNo],
              m230_picturePosTbl[m230_playerCreateNo].x,
              m230_picturePosTbl[m230_playerCreateNo].y);
    espAttrSet(m230_scoreTensTbl[m230_playerCreateNo], HUSPR_ATTR_XLU);
    espPriSet(m230_scoreTensTbl[m230_playerCreateNo], 15);
    espDispOff(m230_scoreTensTbl[m230_playerCreateNo]);
    m230_scoreOnesTbl[m230_playerCreateNo] = espEntry(m230_digitAnim, 0, 1);
    espPosSet(m230_scoreOnesTbl[m230_playerCreateNo],
              m230_picturePosTbl[m230_playerCreateNo].x,
              m230_picturePosTbl[m230_playerCreateNo].y);
    espAttrSet(m230_scoreOnesTbl[m230_playerCreateNo], HUSPR_ATTR_XLU);
    espPriSet(m230_scoreOnesTbl[m230_playerCreateNo], 15);
    espDispOff(m230_scoreOnesTbl[m230_playerCreateNo]);
    m230_scorePtTbl[m230_playerCreateNo] = espEntry(m230_ptAnim, 0, 1);
    espPosSet(m230_scorePtTbl[m230_playerCreateNo],
              m230_picturePosTbl[m230_playerCreateNo].x,
              m230_picturePosTbl[m230_playerCreateNo].y);
    espAttrSet(m230_scorePtTbl[m230_playerCreateNo], HUSPR_ATTR_XLU);
    espPriSet(m230_scorePtTbl[m230_playerCreateNo], 15);
    espDispOff(m230_scorePtTbl[m230_playerCreateNo]);
    m230_playerCreateNo++;
}

void m230_PlayerObjMain(omObjData *object) {
    MgPlayerWork *playerData;
    PictureImperfectWork *work;
    PictureImperfectWork *otherWork;
    s16 sound;
    s32 rounds;
    s32 character;
    s8 i;
    s8 count;

    playerData = object->data;
    work = playerData->unk158;
    switch (MgFlowStatGet()) {
        case MG_STATE_OPENING:
            MgPlayerObjMain(object);
            break;
        case MG_STATE_PLAY:
            HuPadStkX[playerData->unk57] = HuPadStkY[playerData->unk57] = 0;
            if (omPauseChk() + omAllPauseF != 0) {
                m230_PartUpdate(object);
                break;
            }
            if (GwPlayer[playerData->unk59].stat & PLAYER_IS_CPU) {
                m230_PlayerComInput(object);
            }
            if (work->unk05 == 0 && work->unk06 == 0 && playerData->unk38 != 1000.0f &&
                200.0f - playerData->unk34 <= object->trans.y) {
                sound = HuAudPlayerFXPlay(0x3F3, playerData->unk59);
                if (playerData->unk59 & 1) {
                    HuAudFXPanning(sound, 92);
                } else {
                    HuAudFXPanning(sound, 32);
                }
                omVibrate(playerData->unk59, 2, 3, 10);
                MgPlayerEffSet(object, 3, object->trans.x, work->unk10 - 25.0f, object->trans.z, 180.0f, 0.0f);
                work->unk14 = 0.0f;
                work->unk05 = 1;
                m230_blockHitCnt++;
                switch (m230_pictureNo) {
                    case 0:
                    default:
                        rounds = 5;
                        break;
                    case 1:
                        rounds = 4;
                        break;
                    case 2:
                        rounds = 3;
                        break;
                }
                if (rounds * 4 == m230_blockHitCnt && m230_cycleSe != -1) {
                    HuAudFXStop(m230_cycleSe);
                    m230_cycleSe = -1;
                    m230_cycleSeF = 0;
                }
            }
            if (work->unk05 == 1) {
                if (work->unk14 == 180.0f) {
                    work->unk10 = 272.0f;
                    work->unk14 = 0.0f;
                    work->unk05 = 0;
                } else {
                    work->unk14 += 20.0f;
                    work->unk10 = sindf(work->unk14) * 100.0f + 272.0f;
                }
                Hu3DModelPosSet(object->model[2], object->trans.x, work->unk10, object->trans.z);
            }
            if (work->unk06 == 1 || work->unk03 != 0) {
                HuPadBtn[playerData->unk57] &= ~A_BUTTON;
                HuPadBtnDown[playerData->unk57] &= ~A_BUTTON;
            }
            m230_PartCycleUpdate(playerData->unk59);
            m230_PartUpdate(object);
            m230_PointPopUpdate(work, playerData->unk59);
            mgPlayerGravity = 0.7f;
            MgPlayerObjMain(object);
            break;
        case MG_STATE_FINISH:
            if (m230_cycleSe != -1) {
                HuAudFXStop(m230_cycleSe);
                m230_cycleSe = -1;
                m230_cycleSeF = 0;
            }
            if (omPauseChk() + omAllPauseF != 0) {
                break;
            }
            if (work->unk03 == 0) {
                m230_PartDispOff(work, playerData->unk59);
            }
            switch (m230_resultPhase) {
                case 1:
                    m230_ScoreDispUpdate(work, playerData->unk59);
                    break;
                case 2:
                    for (i = 0; i < 4; i++) {
                        if (object != mgPlayerObjTbl[i]) {
                            otherWork = ((MgPlayerWork *)mgPlayerObjTbl[i]->data)->unk158;
                            if (work->unk04 < otherWork->unk04) {
                                work->unk07++;
                            }
                        }
                    }
                    if (playerData->unk59 == 3) {
                        count = 0;
                        m230_winnerNum = 0;
                        for (i = 0; i < 4; i++) {
                            otherWork = ((MgPlayerWork *)mgPlayerObjTbl[i]->data)->unk158;
                            if (otherWork->unk07 == 0) {
                                m230_winnerNum++;
                                m230_winnerTbl[count] = i;
                                count++;
                            }
                        }
                        m230_resultPhase = 8;
                    }
                    break;
                case 8:
                    if (playerData->unk59 == 3) {
                        if (m230_winnerNum == 1) {
                            m230_mgFlowWinnerTbl[0] = m230_winnerTbl[0];
                        } else if (m230_winnerNum == 2) {
                            m230_mgFlowWinnerTbl[0] = m230_winnerTbl[0];
                            m230_mgFlowWinnerTbl[1] = m230_winnerTbl[1];
                        } else if (m230_winnerNum == 3) {
                            m230_mgFlowWinnerTbl[0] = m230_winnerTbl[0];
                            m230_mgFlowWinnerTbl[1] = m230_winnerTbl[1];
                            m230_mgFlowWinnerTbl[2] = m230_winnerTbl[2];
                        } else if (work->unk04 != 0) {
                            m230_mgFlowWinnerTbl[0] = m230_winnerTbl[0];
                            m230_mgFlowWinnerTbl[1] = m230_winnerTbl[1];
                            m230_mgFlowWinnerTbl[2] = m230_winnerTbl[2];
                            m230_mgFlowWinnerTbl[3] = m230_winnerTbl[3];
                        } else {
                            m230_winnerTbl[0] = m230_winnerTbl[1] =
                                m230_winnerTbl[2] = m230_winnerTbl[3] = -1;
                        }
                        m230_resultPhase = 16;
                        if (playerData->unk59 == 3) {
                            MgFlowStatSet(MG_STATE_RESULT);
                        }
                    }
                    break;
            }
            MgPlayerObjMain(object);
            break;
        case MG_STATE_RESULT:
            if (MgFlowStatTimeGet() == 12) {
                if (m230_resultPhase == 16) {
                    if (playerData->unk59 == m230_winnerTbl[0] ||
                        playerData->unk59 == m230_winnerTbl[1] ||
                        playerData->unk59 == m230_winnerTbl[2] ||
                        playerData->unk59 == m230_winnerTbl[3]) {
                        MgPlayerMotSet(object, 13);
                        switch (GwPlayer[playerData->unk59].chr) {
                            case 0:
                            default:
                                character = 2;
                                break;
                            case 1:
                                character = 3;
                                break;
                            case 2:
                                character = 7;
                                break;
                            case 3:
                                character = 4;
                                break;
                            case 4:
                                character = 5;
                                break;
                            case 5:
                                character = 6;
                                break;
                            case 6:
                                character = 8;
                                break;
                            case 7:
                                character = 9;
                                break;
                        }
                        HuAudCharVoicePlay((character << 16) | 0x2F);
                        GwPlayer[playerData->unk59].bonusCoin += 10;
                    } else {
                        MgPlayerMotSet(object, 14);
                    }
                    MgPlayerObjMain(object);
                }
                if (playerData->unk59 == 3) {
                    if (m230_winnerNum == 1) {
                        GMesCreate(GMES_MES_MG_WINNER, GwPlayer[m230_mgFlowWinnerTbl[0]].chr);
                        HuAudSeqPlay(0x65);
                    } else if (m230_winnerNum == 2) {
                        GMesCreate(GMES_MES_MG_WINNERS_2, GwPlayer[m230_mgFlowWinnerTbl[0]].chr,
                                   GwPlayer[m230_mgFlowWinnerTbl[1]].chr);
                        HuAudSeqPlay(0x66);
                    } else if (m230_winnerNum == 3) {
                        GMesCreate(GMES_MES_MG_WINNERS_3, GwPlayer[m230_mgFlowWinnerTbl[0]].chr,
                                   GwPlayer[m230_mgFlowWinnerTbl[1]].chr,
                                   GwPlayer[m230_mgFlowWinnerTbl[2]].chr);
                        HuAudSeqPlay(0x66);
                    } else if (work->unk04 != 0) {
                        GMesCreate(GMES_MES_MG_WINNERS_4, GwPlayer[m230_mgFlowWinnerTbl[0]].chr,
                                   GwPlayer[m230_mgFlowWinnerTbl[1]].chr,
                                   GwPlayer[m230_mgFlowWinnerTbl[2]].chr,
                                   GwPlayer[m230_mgFlowWinnerTbl[3]].chr);
                        HuAudSeqPlay(0x66);
                    } else {
                        GMesCreate(GMES_MES_MG_DRAW);
                        HuAudSeqPlay(0x6C);
                    }
                    m230_mgFlow.resultType = MG_RESULT_NONE;
                }
            } else {
                m230_mgFlow.resultType = MG_RESULT_NONE;
            }
            break;
    }
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void m230_PlayerComInput(omObjData *object) {
    PictureImperfectWork *work;
    MgPlayerWork *playerData;
    s32 chance3;
    s32 chance2;
    s32 chance1;
    u8 roll;

    playerData = object->data;
    work = playerData->unk158;
    if (work->unk18 != 0) {
        work->unk18--;
        return;
    }
    switch (GwPlayer[playerData->unk59].cpu_difficulty) {
        case 3:
            chance3 = 9;
            chance2 = 7;
            chance1 = 5;
            break;
        case 2:
            chance3 = 30;
            chance2 = 10;
            chance1 = 5;
            break;
        case 1:
        default:
            chance3 = 75;
            chance2 = 40;
            chance1 = 20;
            break;
        case 0:
            chance3 = 90;
            chance2 = 70;
            chance1 = 40;
            break;
    }
    roll = (rand8() * 100) >> 8;
    if (roll < chance1) {
        if (work->unk01 == 4) {
            HuPadBtnDown[playerData->unk57] |= A_BUTTON;
            work->unk18 = ((rand8() * 15) >> 6) + 30;
        }
    } else if (roll < chance2) {
        if (work->unk01 == 3) {
            HuPadBtnDown[playerData->unk57] |= A_BUTTON;
            work->unk18 = ((rand8() * 15) >> 6) + 30;
        }
    } else if (roll < chance3) {
        if (work->unk01 == 2) {
            HuPadBtnDown[playerData->unk57] |= A_BUTTON;
            work->unk18 = ((rand8() * 15) >> 6) + 30;
        }
    } else if (roll < chance2) {
        if (work->unk01 == 1) {
            HuPadBtnDown[playerData->unk57] |= A_BUTTON;
            work->unk18 = ((rand8() * 15) >> 6) + 30;
        }
    } else if (work->unk01 == 0) {
        HuPadBtnDown[playerData->unk57] |= A_BUTTON;
        work->unk18 = ((rand8() * 15) >> 6) + 30;
    }
}

void m230_PartCycleUpdate(s8 player) {
    if (player == 0) {
        if (m230_frameCnt % 10 == 9) {
            if (++m230_partCycleTbl[0] >= 5) {
                m230_partCycleTbl[0] = 0;
            }
            if (m230_cycleSe == -1 && m230_cycleSeF == 1) {
                m230_cycleSe = HuAudFXPlay(0x3F4);
            }
        }
        if (m230_frameCnt % 8 == 7) {
            if (++m230_partCycleTbl[2] >= 5) {
                m230_partCycleTbl[2] = 0;
            }
            if (m230_cycleSe == -1 && m230_cycleSeF == 1) {
                m230_cycleSe = HuAudFXPlay(0x3F4);
            }
        }
        if (m230_frameCnt % 6 == 5) {
            if (++m230_partCycleTbl[3] >= 5) {
                m230_partCycleTbl[3] = 0;
            }
            if (m230_cycleSe == -1 && m230_cycleSeF == 1) {
                m230_cycleSe = HuAudFXPlay(0x3F4);
            }
        }
        if (m230_frameCnt % 4 == 3) {
            if (++m230_partCycleTbl[4] >= 5) {
                m230_partCycleTbl[4] = 0;
            }
            if (m230_cycleSe == -1 && m230_cycleSeF == 1) {
                m230_cycleSe = HuAudFXPlay(0x3F4);
            }
        }
        if (m230_frameCnt % 2 == 1) {
            if (++m230_partCycleTbl[1] >= 5) {
                m230_partCycleTbl[1] = 0;
            }
            if (m230_cycleSe == -1 && m230_cycleSeF == 1) {
                m230_cycleSe = HuAudFXPlay(0x3F4);
            }
        }
    } else if (player == 3) {
        m230_frameCnt++;
    }
}

void m230_PartUpdate(omObjData *object) {
    MgPlayerWork *playerData;
    PictureImperfectWork *work;
    s8 player;
    s16(*sprites)[5];
    s16 delay;
    s8 i;

    playerData = object->data;
    work = playerData->unk158;
    player = playerData->unk59;
    switch (work->unk00) {
        case 0:
            sprites = m230_part0SprTbl;
            switch (m230_pictureNo) {
                case 0:
                default:
                    delay = 10;
                    break;
                case 1:
                    delay = 8;
                    break;
                case 2:
                    delay = 6;
                    break;
            }
            break;
        case 1:
            sprites = m230_part1SprTbl;
            delay = 2;
            break;
        case 2:
            sprites = m230_part2SprTbl;
            switch (m230_pictureNo) {
                case 0:
                default:
                    delay = 8;
                    break;
                case 1:
                    delay = 6;
                    break;
                case 2:
                    delay = 4;
                    break;
            }
            break;
        case 3:
            sprites = m230_part3SprTbl;
            if (m230_pictureNo == 0) {
                delay = 6;
            } else {
                delay = 4;
            }
            break;
        case 4:
            sprites = m230_part4SprTbl;
            delay = 4;
            break;
        default:
            if (playerData->unk38 == 1000.0f) {
                work->unk06 = 1;
            }
            return;
    }
    if (omPauseChk() + omAllPauseF != 0) {
        for (i = 0; i < 5; i++) {
            espDispOff(sprites[player][i]);
        }
        return;
    }
    work->unk01 = m230_partOrderTbl[m230_partOrderNo][m230_partCycleTbl[work->unk00]];
    if (work->unk08 == 0) {
        work->unk08 = delay;
    } else {
        work->unk08--;
    }
    for (i = 0; i < 5; i++) {
        if (work->unk01 == i) {
            espDispOn(sprites[player][work->unk01]);
        } else {
            espDispOff(sprites[player][i]);
        }
    }
    if (HuPadBtnDown[playerData->unk57] & A_BUTTON) {
        work->unk08 = delay - 2;
        switch (work->unk01) {
            case 0:
                work->unk03 = 10;
                break;
            case 1:
                work->unk03 = 7;
                break;
            case 2:
                work->unk03 = 5;
                break;
            case 3:
                work->unk03 = 3;
                break;
            case 4:
                work->unk03 = 1;
                break;
        }
        work->unk04 += work->unk03;
        m230_partChoiceTbl[player][work->unk00] = work->unk01;
        work->unk01 = (rand8() * 5) >> 8;
        if (work->unk00 == 0) {
            work->unk00 = 2;
        } else if (work->unk00 == 1) {
            work->unk00 = 10;
        } else {
            work->unk00++;
            switch (m230_pictureNo) {
                case 0:
                    if (work->unk00 >= 5) {
                        work->unk00 = 1;
                    }
                    break;
                case 1:
                    if (work->unk00 >= 4) {
                        work->unk00 = 1;
                    }
                    break;
                case 2:
                default:
                    if (work->unk00 >= 3) {
                        work->unk00 = 1;
                    }
                    break;
            }
        }
    }
}

void m230_PartDispOff(PictureImperfectWork *work, s8 player) {
    s32 i;

    switch (work->unk00) {
        case 0:
            for (i = 0; i < 5; i++) {
                espDispOff(m230_part0SprTbl[player][i]);
            }
            break;
        case 1:
            for (i = 0; i < 5; i++) {
                espDispOff(m230_part1SprTbl[player][i]);
            }
            break;
        case 2:
            for (i = 0; i < 5; i++) {
                espDispOff(m230_part2SprTbl[player][i]);
            }
            break;
        case 3:
            for (i = 0; i < 5; i++) {
                espDispOff(m230_part3SprTbl[player][i]);
            }
            break;
        case 4:
            for (i = 0; i < 5; i++) {
                espDispOff(m230_part4SprTbl[player][i]);
            }
            break;
    }
}

void m230_PointPopUpdate(PictureImperfectWork *work, s8 player) {
    u8 color[3];
    s32 y;
    s32 offset;
    s32 rounds;

    if (work->unk03 != 0) {
        switch (work->unk03) {
            case 1:
                if (m230_popBlinkTbl[player]) {
                    color[0] = 0;
                    color[1] = 0;
                    color[2] = 0x80;
                } else {
                    color[0] = 0;
                    color[1] = 0;
                    color[2] = 0xFF;
                }
                break;
            case 3:
                if (m230_popBlinkTbl[player]) {
                    color[0] = 0;
                    color[1] = 0x80;
                    color[2] = 0x80;
                } else {
                    color[0] = 0;
                    color[1] = 0xFF;
                    color[2] = 0xFF;
                }
                break;
            case 5:
                if (m230_popBlinkTbl[player]) {
                    color[0] = 0;
                    color[1] = 0x80;
                    color[2] = 0;
                } else {
                    color[0] = 0;
                    color[1] = 0xFF;
                    color[2] = 0;
                }
                break;
            case 7:
                if (m230_popBlinkTbl[player]) {
                    color[0] = 0x80;
                    color[1] = 0x40;
                    color[2] = 0;
                } else {
                    color[0] = 0xFF;
                    color[1] = 0x80;
                    color[2] = 0;
                }
                break;
            case 10:
                if (m230_popBlinkTbl[player]) {
                    color[0] = 0x80;
                    color[1] = 0;
                    color[2] = 0;
                } else {
                    color[0] = 0xFF;
                    color[1] = 0;
                    color[2] = 0;
                }
                break;
        }
        switch (m230_pictureNo) {
            case 0:
                offset = work->unk00 - 1;
                break;
            case 1:
                if (work->unk00 == 1) {
                    offset = 0;
                } else if (work->unk00 == 2) {
                    offset = 1;
                } else if (work->unk00 == 3) {
                    offset = 2;
                } else {
                    offset = 4;
                }
                break;
            case 2:
            default:
                if (work->unk00 == 1) {
                    offset = 1;
                } else if (work->unk00 == 2) {
                    offset = 3;
                } else {
                    offset = 4;
                }
                break;
        }
        y = m230_scorePosTbl[player].y + m230_popOfsYTbl[offset];
        espColorSet(m230_popPlusTbl[player], color[0], color[1], color[2]);
        espScaleSet(m230_popPlusTbl[player], work->unk0C, work->unk0C);
        espTPLvlSet(m230_popPlusTbl[player], work->unk0A);
        espPosSet(m230_popPlusTbl[player], m230_scorePosTbl[player].x - 25, y);
        espDispOn(m230_popPlusTbl[player]);
        if (work->unk03 == 10) {
            espColorSet(m230_popTensTbl[player], color[0], color[1], color[2]);
            espScaleSet(m230_popTensTbl[player], work->unk0C, work->unk0C);
            espTPLvlSet(m230_popTensTbl[player], work->unk0A);
            espPatNoSet(m230_popTensTbl[player], work->unk03 / 10);
            espPosSet(m230_popTensTbl[player], m230_scorePosTbl[player].x - 14, y);
            espDispOn(m230_popTensTbl[player]);
        } else {
            espDispOff(m230_popTensTbl[player]);
        }
        espColorSet(m230_popOnesTbl[player], color[0], color[1], color[2]);
        espScaleSet(m230_popOnesTbl[player], work->unk0C, work->unk0C);
        espTPLvlSet(m230_popOnesTbl[player], work->unk0A);
        espPatNoSet(m230_popOnesTbl[player], work->unk03 % 10);
        espPosSet(m230_popOnesTbl[player], m230_scorePosTbl[player].x + 2, y);
        espDispOn(m230_popOnesTbl[player]);
        espColorSet(m230_popPtTbl[player], color[0], color[1], color[2]);
        espScaleSet(m230_popPtTbl[player], work->unk0C, work->unk0C);
        espTPLvlSet(m230_popPtTbl[player], work->unk0A);
        espPosSet(m230_popPtTbl[player], m230_scorePosTbl[player].x + 30, y);
        espDispOn(m230_popPtTbl[player]);
        if (m230_popTimerTbl[player] > 10) {
            work->unk0C += 0.05f;
            work->unk0A -= 10;
            m230_popBlinkTbl[player] = 0;
        } else {
            m230_popTimerTbl[player]++;
            m230_popBlinkTbl[player] ^= 1;
        }
        if (work->unk0A <= 0) {
            work->unk0C = 1.0f;
            work->unk0A = 0xFF;
            work->unk03 = 0;
            m230_popTimerTbl[player] = 0;
            m230_popBlinkTbl[player] = 0;
            switch (m230_pictureNo) {
                case 0:
                default:
                    rounds = 5;
                    break;
                case 1:
                    rounds = 4;
                    break;
                case 2:
                    rounds = 3;
                    break;
            }
            m230_partDoneCnt++;
            if (rounds * 4 == m230_partDoneCnt) {
                MgFlowStatSet(MG_STATE_FINISH);
            }
        }
    } else {
        espDispOff(m230_popPlusTbl[player]);
        espDispOff(m230_popTensTbl[player]);
        espDispOff(m230_popOnesTbl[player]);
        espDispOff(m230_popPtTbl[player]);
    }
}

void m230_ScoreDispUpdate(PictureImperfectWork *work, s8 player) {
    if (m230_scoreTimerTbl[player] < 30) {
        if (m230_scoreTimerTbl[player] == 0) {
            HuAudFXPlay(0x3EC);
        }
        espPatNoSet(m230_scoreTensTbl[player], (rand8() * 10U) >> 8);
        espPosSet(m230_scoreTensTbl[player], m230_scorePosTbl[player].x - 32,
                  m230_scorePosTbl[player].y);
        espDispOn(m230_scoreTensTbl[player]);
        espPatNoSet(m230_scoreOnesTbl[player], (rand8() * 10U) >> 8);
        espPosSet(m230_scoreOnesTbl[player], m230_scorePosTbl[player].x - 12,
                  m230_scorePosTbl[player].y);
        espDispOn(m230_scoreOnesTbl[player]);
        espPosSet(m230_scorePtTbl[player], m230_scorePosTbl[player].x + 20,
                  m230_scorePosTbl[player].y + 4);
        espDispOn(m230_scorePtTbl[player]);
    } else if (m230_scoreTimerTbl[player] == 30) {
        HuAudFXPlay(0x3ED);
        if (work->unk04 >= 10) {
            espPatNoSet(m230_scoreTensTbl[player], work->unk04 / 10);
            espPosSet(m230_scoreTensTbl[player], m230_scorePosTbl[player].x - 32,
                      m230_scorePosTbl[player].y);
        } else {
            espDispOff(m230_scoreTensTbl[player]);
        }
        espPatNoSet(m230_scoreOnesTbl[player], work->unk04 % 10);
        espPosSet(m230_scoreOnesTbl[player], m230_scorePosTbl[player].x - 12,
                  m230_scorePosTbl[player].y);
    } else if (m230_scoreTimerTbl[player] == 90) {
        espDispOff(m230_scoreOnesTbl[player]);
        espDispOff(m230_scoreTensTbl[player]);
        espDispOff(m230_scorePtTbl[player]);
        if (player == 3) {
            m230_resultPhase = 2;
        }
    }
    m230_scoreTimerTbl[player]++;
}

void m230_MapObjInit(omObjData *object) {
    PictureImperfectGameData *data;
    s32 i;
    s32 x;
    s32 y;

    object->func = m230_MapObjMain;
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            m230_sprAnim = HuSprAnimDataRead(0x3F0002);
        }
        m230_frameGrp = HuSprGrpCreate(1, 0);
        HuSprGrpMemberSet(m230_frameGrp, 0, m230_sprAnim, 0);
        HuSprAttrReset(m230_frameGrp, 0, 0xFFFF);
        HuSprAttrSet(m230_frameGrp, 0, HUSPR_ATTR_BG | HUSPR_ATTR_XLU);
        HuSprPosSet(m230_frameGrp, 0, m230_scorePosTbl[i].x,
                    m230_scorePosTbl[i].y);
        HuSprPriSet(m230_frameGrp, 0, 0xFF);
    }
    m230_sprAnim = HuSprAnimDataRead(0x3F0003);
    m230_screenGrp = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(m230_screenGrp, 0, m230_sprAnim, 0);
    HuSprAttrReset(m230_screenGrp, 0, 0xFFFF);
    HuSprAttrSet(m230_screenGrp, 0, HUSPR_ATTR_XLU);
    HuSprPosSet(m230_screenGrp, 0, 160, 120);
    HuSprPriSet(m230_screenGrp, 0, 0xF0);
    m230_sprAnim = HuSprAnimDataRead(0x3F0001);
    m230_sampleFrameSpr = espEntry(m230_sprAnim, 0, 1);
    espPosSet(m230_sampleFrameSpr, 160, 120);
    espAttrSet(m230_sampleFrameSpr, HUSPR_ATTR_XLU);
    espPriSet(m230_sampleFrameSpr, 15);
    espDispOn(m230_sampleFrameSpr);
    x = 128;
    y = 108;
    switch (m230_pictureNo) {
        case 0:
        default:
            m230_sprAnim = HuSprAnimDataRead(0x3F0008);
            break;
        case 1:
            m230_sprAnim = HuSprAnimDataRead(0x3F000A);
            break;
        case 2:
            m230_sprAnim = HuSprAnimDataRead(0x3F000C);
            break;
    }
    m230_sampleSpr = espEntry(m230_sprAnim, 0, 1);
    espPosSet(m230_sampleSpr, x, y);
    espAttrSet(m230_sampleSpr, HUSPR_ATTR_XLU);
    espPriSet(m230_sampleSpr, 15);
    espDispOn(m230_sampleSpr);
    switch (m230_pictureNo) {
        case 0:
        default:
            m230_sprAnim = HuSprAnimDataRead(0x3F0009);
            break;
        case 1:
            m230_sprAnim = HuSprAnimDataRead(0x3F000B);
            break;
        case 2:
            m230_sprAnim = HuSprAnimDataRead(0x3F000D);
            break;
    }
    m230_sampleCoverSpr = espEntry(m230_sprAnim, 0, 1);
    espPosSet(m230_sampleCoverSpr, x, y);
    espAttrSet(m230_sampleCoverSpr, HUSPR_ATTR_XLU);
    espPriSet(m230_sampleCoverSpr, 15);
    espDispOn(m230_sampleCoverSpr);
    m230_maxScoreTensSpr = espEntry(m230_digitAnim, 0, 1);
    espPosSet(m230_maxScoreTensSpr, 225, 100);
    espAttrSet(m230_maxScoreTensSpr, HUSPR_ATTR_XLU);
    espPriSet(m230_maxScoreTensSpr, 15);
    espDispOff(m230_maxScoreTensSpr);
    m230_maxScoreOnesSpr = espEntry(m230_digitAnim, 0, 1);
    espPosSet(m230_maxScoreOnesSpr, 245, 100);
    espAttrSet(m230_maxScoreOnesSpr, HUSPR_ATTR_XLU);
    espPriSet(m230_maxScoreOnesSpr, 15);
    espDispOff(m230_maxScoreOnesSpr);
    m230_maxScorePtSpr = espEntry(m230_ptAnim, 0, 1);
    espPosSet(m230_maxScorePtSpr, 277, 104);
    espAttrSet(m230_maxScorePtSpr, HUSPR_ATTR_XLU);
    espPriSet(m230_maxScorePtSpr, 15);
    espDispOff(m230_maxScorePtSpr);
    data = object->data = HuMemAllocTag(sizeof(PictureImperfectGameData), TAG_OVERLAY);
    memset(data, 0, sizeof(PictureImperfectGameData));
    data->unk03 = 1;
    data->unk04 = 0;
    data->unk08 = 0.5f;
    MgMapAttrSet(object, 2, -8.0f);
}

void m230_MapObjMain(omObjData *object) {
    f32 t;
    s32 x;
    s32 y;

    if (MgFlowStatGet() == MG_STATE_OPENING) {
        switch (m230_pictureNo) {
            case 0:
            default:
                espPatNoSet(m230_maxScoreTensSpr, 5);
                break;
            case 1:
                espPatNoSet(m230_maxScoreTensSpr, 4);
                break;
            case 2:
                espPatNoSet(m230_maxScoreTensSpr, 3);
                break;
        }
        espPatNoSet(m230_maxScoreOnesSpr, 0);
        if (MgFlowStatTimeGet() == 1) {
            espDispOn(m230_maxScoreTensSpr);
            espDispOn(m230_maxScoreOnesSpr);
            espDispOn(m230_maxScorePtSpr);
        } else if (MgFlowStatTimeGet() > 26) {
            switch (m230_introPhase) {
                case 0:
                    if (m230_sampleAlpha == 0xFF) {
                        HuAudFXPlay(0x3F6);
                    }
                    espTPLvlSet(m230_sampleCoverSpr, m230_sampleAlpha);
                    m230_sampleAlpha -= 5;
                    if (m230_sampleAlpha == 0) {
                        espDispOff(m230_maxScoreTensSpr);
                        espDispOff(m230_maxScoreOnesSpr);
                        espDispOff(m230_maxScorePtSpr);
                        m230_introPhase++;
                    }
                    break;
                case 1:
                    m230_sampleScale -= 0.04f;
                    t = m230_introTimer / 50.0f;
                    x = (1.0f - t) * 128.0f + t * 160.0f;
                    y = (1.0f - t) * 108.0f + t * 120.0f;
                    if (m230_introTimer == 0) {
                        m230_shrinkSe = HuAudFXPlay(0x3F5);
                    }
                    m230_introTimer++;
                    if (m230_sampleScale > 0.02f) {
                        espScaleSet(m230_sampleFrameSpr, m230_sampleScale,
                                    m230_sampleScale);
                        espScaleSet(m230_sampleSpr, m230_sampleScale,
                                    m230_sampleScale);
                        espPosSet(m230_sampleSpr, x, y);
                    } else {
                        m230_sampleScale = 0.0f;
                        m230_introTimer = 0;
                        m230_introPhase++;
                    }
                    break;
                case 2:
                    espDispOff(m230_sampleFrameSpr);
                    espDispOff(m230_sampleSpr);
                    espDispOff(m230_sampleCoverSpr);
                    if (m230_introTimer > 10) {
                        m230_introPhase++;
                    } else {
                        m230_introTimer++;
                    }
                    break;
                case 3:
                    m230_introTimer = 0;
                    MgFlowStatSet(MG_STATE_START);
                    HuAudFXStop(m230_shrinkSe);
                    break;
            }
        }
    } else if (MgFlowStatGet() == MG_STATE_FINISH) {
        if (GMesStatGet() == 0 && MgFlowStatTimeGet() > 10) {
            m230_sampleScale += 0.04f;
            if (m230_sampleScale > 0.5f) {
                m230_sampleScale = 0.5f;
                if (m230_resultPhase == 0) {
                    m230_resultPhase = 1;
                }
            }
        }
        switch (m230_resultPhase) {
            case 4:
            case 8:
            case 16:
                HuSprAttrSet(m230_screenGrp, 0, HUSPR_ATTR_BG | HUSPR_ATTR_XLU);
                break;
            default:
                espScaleSet(m230_sampleSpr, m230_sampleScale, m230_sampleScale);
                espPosSet(m230_sampleSpr, 160, 120);
                espDispOn(m230_sampleSpr);
                espScaleSet(m230_sampleCoverSpr, m230_sampleScale, m230_sampleScale);
                espTPLvlSet(m230_sampleCoverSpr, 0xFF);
                espPosSet(m230_sampleCoverSpr, 160, 120);
                espDispOn(m230_sampleCoverSpr);
                break;
        }
    }
}
