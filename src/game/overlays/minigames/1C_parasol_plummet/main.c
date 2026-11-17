#include "common.h"
#include "game/overlays/minigame.h"

#define FLAG_IDLE 0x1
#define FLAG_SPINNING 0x2
#define FLAG_PLUMMETING 0x200

// Per-player work allocated in m228_PlayerObjCreate, stored at ObjData->data
typedef struct ParasolPlummetWork {
    /* 0x00 */ Vec coords;
    /* 0x0C */ f32 angle;
    /* 0x10 */ u8 unk_10;
    /* 0x14 */ s32 flags;
    /* 0x18 */ s32 driftTimer;
    /* 0x1C */ char pad_1C[8];
    /* 0x24 */ s32 playerIndex;
    /* 0x28 */ f32 velY;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 driftVelX;
    /* 0x38 */ s32 cpuTimer;
    /* 0x3C */ s32 blinkTimer;
    /* 0x40 */ s32 spinTimer;
    /* 0x44 */ s32 plummetTimer;
    /* 0x48 */ f32 tiltAngleLimit;
    /* 0x4C */ s32 lane;
} ParasolPlummetWork; // Size 0x50

// Object data for the falling item objects held in m228_itemObjTbl,
// created in m228_ItemCreate.
typedef struct ParasolPlummetItemWork {
    /* 0x00 */ f32 rotSpeed;
    /* 0x04 */ s32 slot;
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 y;
    /* 0x10 */ f32 velX;
    /* 0x14 */ f32 velY;
    /* 0x18 */ f32 rotZ;
    /* 0x1C */ u16 flags;
    /* 0x20 */ f32 scale;
    /* 0x24 */ u8 type;
} ParasolPlummetItemWork; // Size 0x28

// Object data for the object held in m228_goalObj,
// created in m228_GoalCreate.
typedef struct ParasolPlummetGoalWork {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 angle;
    /* 0x10 */ s32 flags;
} ParasolPlummetGoalWork; // Size 0x14

// Object data for the scrolling background sprites held in m228_backObj,
// created in m228_BackObjInit.
typedef struct ParasolPlummetBgWork {
    /* 0x00 */ f32 posY[2];
    /* 0x08 */ s16 spriteFileId;
    /* 0x0A */ s16 espId[2];
    /* 0x0E */ char unk_0E[6];
} ParasolPlummetBgWork; // Size 0x14

// Object data for the cloud sprite objects created in m228_CloudCreate.
typedef struct ParasolPlummetCloudWork {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 velY;
    /* 0x0C */ f32 baseScale;
    /* 0x10 */ f32 scaleAmp;
    /* 0x14 */ f32 angle;
    /* 0x18 */ s32 index;
} ParasolPlummetCloudWork; // Size 0x1C

// Object data for the background sprites object, created in m228_SideObjInit.
typedef struct ParasolPlummetSideWork {
    /* 0x00 */ f32 x[6];
    /* 0x18 */ f32 y[6];
    /* 0x30 */ s16 unk_30;
    /* 0x32 */ s16 espId[6];
    /* 0x3E */ char unk_3E[2];
} ParasolPlummetSideWork; // Size 0x40

// Object data for the objects held in m228_flyerObjTbl,
// created in m228_FlyerCreate.
typedef struct ParasolPlummetFlyerWork {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ char unk_08[0x10];
    /* 0x18 */ s32 index;
    /* 0x1C */ f32 rotY;
    /* 0x20 */ u16 flags;
    /* 0x22 */ s16 timer;
} ParasolPlummetFlyerWork; // Size 0x24

typedef struct {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01[5];
} ParasolPlummetFlyerStat;

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02[4];
    /* 0x0A */ s16 unk0A[4];
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E[4];
} ParasolPlummetHud;

MinigameFlow m228_mgFlow = {
    MG_STATE_OPENING, MINIGAME_4P, MG_TIMER_COUNT_DOWN, MG_TIME_DISP_COUNTDOWN, FALSE, MG_GAUGE_NONE, MG_RESULT_NONE, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    180, 900, -1, 210, 60
};
s32 m228_voiceChrTbl[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };

s32 m228_cameraNo BSS;
u8 m228_itemThrowF BSS;
f32 m228_flyerThrowY BSS;
u8 m228_flyerThrowYPad[4] BSS; /* Unreferenced. */
omObjData *m228_playerObjTbl[4] BSS;
omObjData *m228_itemObjTbl[0x12] BSS;
u8 m228_itemActiveTbl[0x14] BSS;
omObjData *m228_goalObj BSS;
u16 m228_playStartF BSS;
u8 m228_playStartFPad[4] BSS; /* Unreferenced. */
s16 m228_itemPoolTbl[60] BSS;
f32 m228_laneUsedTbl[4] BSS;
s32 m228_flyerThrowNo BSS;
s16 m228_starEffGrp BSS;
u8 m228_flowStat BSS;
f32 m228_backScrollSpeed BSS;
omObjData *m228_backObj BSS;
f32 m228_sideScrollSpeed BSS;
ParasolPlummetFlyerStat m228_flyerStat BSS;
u8 m228_flyerStatPad[4] BSS; /* Unreferenced. */
omObjData *m228_flyerObjTbl[5] BSS;
f32 m228_flyerNextY BSS;
f32 m228_flyerNextTimer BSS;
s32 m228_flyerSideF BSS;
s16 m228_itemMdlTbl[3] BSS;
s16 m228_hudDigitTbl[12] BSS;
ParasolPlummetHud m228_hud BSS;
u8 m228_hudPad[8] BSS; /* Unreferenced. */
s16 m228_cloudSprTbl[5] BSS;
s16 m228_cloudAnim BSS;
u8 m228_cloudActiveTbl[5] BSS;

/* Fields of m228_flyerStat and m228_hud (aliased in undefined_syms.txt). */
extern u8 m228_flyerStatFlag;
extern u8 m228_flyerActiveTbl[5];
extern s16 m228_hudDigitAnim;
extern s16 m228_hudChrIconAnimTbl[4];
extern s16 m228_hudChrIconTbl[4];
extern s16 m228_hudCoinAnim;
extern s16 m228_hudCoinTbl[4];
extern s16 m228_hudCrossAnim;
extern s16 m228_hudCrossTbl[4];

void m228_MainObjMain(omObjData *object);
void m228_ExitObjMain(omObjData *object);
void m228_PlayerObjCreate(s32 playerIndex);
void m228_PlayerObjMain(omObjData *object);
void m228_ParasolOpen(omObjData *object);
void m228_ParasolClose(omObjData *object);
void m228_PlayerSpinUpdate(omObjData *object);
void m228_PlayerMoveUpdate(omObjData *object);
void m228_PlayerParasolUpdate(omObjData *object);
void m228_PlayerTiltUpdate(omObjData *object);
void m228_PlayerHitUpdate(omObjData *object);
void m228_PlayerGoalUpdate(omObjData *object);
s32 m228_PlayerComStickGet(omObjData *object);
u16 m228_PlayerComBtnGet(omObjData *object);
f32 m228_ItemDistGet(omObjData *arg0, s32 arg1);
void m228_PlayerBumpUpdate(omObjData *object);
void m228_PlayerBlinkStart(omObjData *object);
void m228_PlayerBlinkUpdate(omObjData *object);
void m228_PlayerBlinkEnd(omObjData *object);
void m228_PlayerPlummetStart(omObjData *object);
void m228_PlayerPlummetUpdate(omObjData *object);
void m228_PlayerPlummetEnd(omObjData *object);
void m228_GoalCreate(void);
void m228_GoalObjMain(omObjData *object);
void m228_GoalProc(void);
void m228_BackObjInit(omObjData *object);
void m228_BackObjMain(omObjData *object);
void m228_BackScrollProc(void);
void m228_CloudProc(void);
void m228_CloudCreate(s32 index);
void m228_CloudObjMain(omObjData *object);
void m228_SideObjInit(omObjData *object);
void m228_SideObjMain(omObjData *object);
void m228_SideScrollProc(void);
void m228_FlyerCreateAll(void);
void m228_FlyerSpawnProc(void);
void m228_FlyerStart(s32 index);
void m228_FlyerCreate(s32 index);
void m228_FlyerObjMain(omObjData *object);
void m228_ItemCreateAll(void);
void m228_ItemThrowProc(void);
void m228_ItemThrow(s32 index);
void m228_ItemCreate(s32 index);
void m228_ItemObjMain(omObjData *object);
s16 m228_PlayerHitGet(omObjData *object, s32 isItem);
void m228_HudCreate(void);
void m228_HudProc(void);
void m228_CameraInit(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ);

void m228_ObjectSetup(void) {
    omObjData *obj;
    s32 i;

    omInitObjMan(40, 10);
    MapCollInit(16);
    Hu3DQuadPoolInit(&mgQuadPool, 64);
    Hu3DSprModelInit(64);
    omGameSysInit();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    m228_CameraInit(2500.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    omOutView(obj);
    Hu3DBGColorSet(0, 0, 0);
    MgFlowInit(&m228_mgFlow);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    for (i = 0; i < 4; i++) {
        m228_laneUsedTbl[i] = 0.0f;
    }
    for (i = 0; i < 4; i++) {
        m228_playerObjTbl[i] = NULL;
        m228_PlayerObjCreate(i);
    }
    m228_GoalCreate();
    omAddObj(0x50, 0, 0, -1, m228_BackObjInit);
    omAddObj(0x50, 0, 0, -1, m228_SideObjInit);
    omAddObj(0x50, 0, 0, -1, m228_MainObjMain);
    omAddPrcObj(m228_CloudProc, 0x50, 0x2000, 0);
    m228_FlyerCreateAll();
    m228_ItemCreateAll();
    m228_itemThrowF = 0;
    m228_playStartF = 0;
    m228_HudCreate();
    m228_starEffGrp = EffectGroupStarCreate(0x2A9, 4);
}

void m228_MainObjMain(omObjData *object) {
    ParasolPlummetWork *work;
    s32 lane[4];
    f32 x[4];
    s32 i;
    s32 j;
    f32 tempX;
    s32 tempLane;

    if (omSysExitReq != 0) {
        HuAudFXAllStop();
        HuAudSeqFadeOut(30);
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
    }
    switch (m228_flowStat = MgFlowMain(object)) {
        case 0:
            if (MgFlowStatTimeGet() == 20) {
                HuAudFXPlay(0x3E5);
            }
            if (MgFlowStatTimeGet() == 150) {
                HuAudSeqPlay(0x33);
            }
            break;
        case 1:
            break;
        case 2:
            if (m228_playStartF == 0) {
                for (i = 0; i < 4; i++) {
                    work = OM_GET_DATA_PTR(m228_playerObjTbl[i], ParasolPlummetWork);
                    if (!(work->flags & FLAG_IDLE)) {
                        work->flags |= FLAG_IDLE;
                    }
                }
                m228_playStartF++;
            }
            break;
        case 3:
            work = OM_GET_DATA_PTR(m228_playerObjTbl[0], ParasolPlummetWork);
            if (!(work->flags & 0x40)) {
                for (i = 0; i < 4; i++) {
                    work = OM_GET_DATA_PTR(m228_playerObjTbl[i], ParasolPlummetWork);
                    x[i] = work->coords.x;
                    lane[i] = i;
                }
                for (i = 0; i < 4; i++) {
                    for (j = 0; j < 4; j++) {
                        if (x[i] < x[j]) {
                            tempX = x[i];
                            x[i] = x[j];
                            x[j] = tempX;
                            tempLane = lane[i];
                            lane[i] = lane[j];
                            lane[j] = tempLane;
                        }
                    }
                }
                for (i = 0; i < 4; i++) {
                    work = OM_GET_DATA_PTR(m228_playerObjTbl[i], ParasolPlummetWork);
                    work->lane = lane[i];
                }
            }
            for (i = 0; i < 4; i++) {
                work = OM_GET_DATA_PTR(m228_playerObjTbl[i], ParasolPlummetWork);
                if (!(work->flags & 0x40)) {
                    m228_PlayerBlinkEnd(m228_playerObjTbl[i]);
                    m228_PlayerPlummetEnd(m228_playerObjTbl[i]);
                    m228_PlayerPlummetEnd(m228_playerObjTbl[i]);
                    work->flags = (work->flags | 0x40) & ~FLAG_IDLE;
                    m228_ParasolClose(m228_playerObjTbl[i]);
                }
            }
            m228_mgFlow.resultType = MG_RESULT_NONE;
            if (MgFlowStatTimeGet() == 135) {
                HuAudSeqPlay(0x66);
            }
            break;
        case 4:
            break;
        case 5:
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            object->func = m228_ExitObjMain;
            break;
    }
}

void m228_ExitObjMain(omObjData *object) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

void m228_PlayerObjCreate(s32 playerIndex) {
    s32 unusedModelIds[8] = { 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 3 };
    s32 modelIds[8] = { 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 1 };
    s32 motionIds[8][7] = {
        { 0x00, 0x44, 0x45, 0x04, 0x46, 0x2F, 0x36 },
        { 0x00, 0x44, 0x45, 0x04, 0x46, 0x2F, 0x36 },
        { 0x00, 0x44, 0x45, 0x04, 0x46, 0x2F, 0x36 },
        { 0x00, 0x44, 0x45, 0x04, 0x46, 0x2F, 0x36 },
        { 0x00, 0x44, 0x45, 0x04, 0x46, 0x2F, 0x36 },
        { 0x00, 0x44, 0x45, 0x04, 0x46, 0x2F, 0x36 },
        { 0x00, 0x44, 0x45, 0x04, 0x46, 0x2F, 0x36 },
        { 0x00, 0x44, 0x45, 0x04, 0x46, 0x2F, 0x36 },
    };
    omObjData *object;
    ParasolPlummetWork *work;
    s16 chr;
    s32 group;
    s32 modelId;
    s32 lane;
    s32 i;

    object = omAddObj(0x50, 5, 10, -1, m228_PlayerObjMain);
    object->data = HuMemAllocTag(sizeof(ParasolPlummetWork), 0x7918);
    m228_playerObjTbl[playerIndex] = object;
    work = OM_GET_DATA_PTR(object, ParasolPlummetWork);
    work->coords.x = 0.0f;
    work->coords.y = 0.0f;
    work->coords.z = 0.0f;
    work->angle = 0.0f;
    work->velY = 0.0f;
    work->unk_30 = 0.0f;
    work->unk_2C = 0.0f;
    work->driftVelX = 0.0f;
    work->playerIndex = playerIndex;
    work->unk_10 = 1;
    work->cpuTimer = 0;
    work->blinkTimer = 0;
    work->spinTimer = 0;
    work->driftTimer = 0;
    work->plummetTimer = 0;
    work->tiltAngleLimit = 0.0f;
    work->flags = 0x20;
    chr = GwPlayer[playerIndex].chr;
    group = m228_voiceChrTbl[chr] << 16;
    modelId = modelIds[chr];
    while (TRUE) {
        lane = rand8() & 3;
        if (m228_laneUsedTbl[lane] == 0.0f) {
            work->lane = lane;
            m228_laneUsedTbl[lane] += 1.0f;
            break;
        }
    }
    object->model[0] = Hu3DModelRead(group | modelId, 0x6D9);
    omSetTra(object, work->coords.x, work->coords.y, work->coords.z);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 7; i++) {
        omObjMotionRead(object, i, CharMotionDataNumGet(chr, motionIds[chr][i]));
    }
    Hu3DMotionModelSet(object->model[0], object->motion[0]);
    Hu3DMotionAttrSet(object->model[0], 2, 2);

    object->model[1] = Hu3DModelRead(0x3D0006, 0x6C9);
    Hu3DModelPosSet(object->model[1], work->coords.x, work->coords.y, work->coords.z);
    Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    omObjMotionRead(object, 8, 0x3D0000);
    Hu3DMotionModelSet(object->model[1], object->motion[8]);
    Hu3DMotionAttrSet(object->model[1], 2, 2);
    omObjMotionRead(object, 9, 0x3D0001);

    object->model[2] = Hu3DModelRead(0x3D0007, 0x6D9);
    Hu3DModelPosSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[2], 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);

    switch (GwPlayer[playerIndex].chr) {
        case 1:
            Hu3DModelTexAnimChange(object->model[1], "ma01_DEF", "ru_DEF");
            break;
        case 2:
            Hu3DModelTexAnimChange(object->model[1], "ma01_DEF", "pi_DEF");
            break;
        case 3:
            Hu3DModelTexAnimChange(object->model[1], "ma01_DEF", "yo_DEF");
            break;
        case 4:
            Hu3DModelTexAnimChange(object->model[1], "ma01_DEF", "wa_DEF");
            break;
        case 5:
            Hu3DModelTexAnimChange(object->model[1], "ma01_DEF", "do_DEF");
            break;
        case 6:
            Hu3DModelTexAnimChange(object->model[1], "ma01_DEF", "waru_DEF");
            break;
        case 7:
            Hu3DModelTexAnimChange(object->model[1], "ma01_DEF", "di_DEF");
            break;
    }
    Hu3DModelRemakeStatic(object->model[1]);
    Hu3DModelDynamicFree(object->model[1]);
}

void m228_PlayerObjMain(omObjData *object) {
    Vec2f screen;
    Vec pos;
    f32 laneX[4] = { -450.0f, -150.0f, 150.0f, 450.0f };
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);
    f32 offsetX;
    f32 offsetY;
    s32 screenY;

    offsetX = -sindf(work->angle) * 80.0f;
    offsetY = cosdf(work->angle) * 80.0f;
    omSetTra(object, work->coords.x - offsetX, work->coords.y - offsetY, work->coords.z);
    omSetRot(object, 0.0f, 0.0f, work->angle);
    Hu3DModelPosSet(object->model[1], work->coords.x - offsetX, work->coords.y - offsetY, work->coords.z);
    Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, work->angle);
    m228_PlayerMoveUpdate(object);
    m228_PlayerBumpUpdate(object);
    work->velY = 12.0f;
    if (work->flags & 0x16) {
        work->velY = -24.0f;
    }
    if (work->flags & 0x10) {
        work->velY += work->unk_2C;
        work->unk_2C -= 5.0f;
        if (work->unk_2C == 0.0f) {
            work->flags &= ~0x10;
            work->coords.x = laneX[work->lane];
            m228_ParasolClose(object);
            Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
    }
    if ((work->flags & 0x60) == 0x40) {
        work->velY += work->unk_30;
        work->unk_30 -= 2.0f;
        work->angle = 0.0f;
    }
    work->coords.y += work->velY;
    pos.x = work->coords.x;
    pos.y = work->coords.y;
    pos.z = work->coords.z;
    Hu3D3Dto2D(0, &pos, &screen);
    screenY = screen.y;
    if (screenY <= 20) {
        m228_ParasolClose(object);
        m228_PlayerPlummetStart(object);
    }
    if (screenY >= 240) {
        work->coords.y -= -24.0f;
        if (work->flags & 0x40) {
            if (work->coords.y <= OM_GET_DATA_PTR(m228_goalObj, ParasolPlummetGoalWork)->pos.y) {
                work->flags |= 0x20;
                work->flags &= ~4;
                work->flags &= ~0x80;
                work->flags &= ~FLAG_SPINNING;
                work->flags &= ~FLAG_IDLE;
                work->driftTimer = 0;
                work->angle = 0.0f;
                Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
        } else if (!(work->flags & FLAG_SPINNING)) {
            m228_ParasolOpen(object);
        }
    }
    m228_PlayerGoalUpdate(object);
    m228_PlayerSpinUpdate(object);
    m228_PlayerBlinkUpdate(object);
    m228_PlayerParasolUpdate(object);
    m228_PlayerHitUpdate(object);
    m228_PlayerTiltUpdate(object);
    m228_PlayerPlummetUpdate(object);
}

void m228_ParasolOpen(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    if (!(work->flags & 0x20)) {
        Hu3DMotionModelSet(object->model[0], object->motion[1]);
        Hu3DMotionAttrSet(object->model[0], 2, 2);
        Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[8]].motId, 0, 10, 2);
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        work->unk_10 = 1;
        work->flags &= ~4;
        if (MgFlowStatGet() == MG_STATE_PLAY) {
            _HuAudPlayerFXPlay(0x3E1, work->playerIndex);
        }
    }
}

void m228_ParasolClose(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    if (!(work->flags & 0x20)) {
        Hu3DMotionModelSet(object->model[0], object->motion[2]);
        Hu3DMotionAttrSet(object->model[0], 2, 2);
        Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[9]].motId, 0, 10, 2);
        work->unk_10 = 0;
        work->tiltAngleLimit = 0.0f;
        work->flags = (work->flags | 4) & ~8;
    }
}

void m228_PlayerSpinStart(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    if (!(work->flags & 0x40)) {
        work->spinTimer = 30;
        work->flags = (work->flags & ~FLAG_IDLE) | FLAG_SPINNING;
        m228_ParasolClose(object);
        Hu3DMotionModelSet(object->model[0], object->motion[4]);
        Hu3DMotionAttrSet(object->model[0], 2, 2);
        PlayerFXPlay(0x286, work->playerIndex);
        HuAudFXPlay(0x3E6);
        omVibrate(work->playerIndex, 2, 2, 20);
    }
}

void m228_PlayerSpinUpdate(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    if (!(work->flags & FLAG_SPINNING)) {
        return;
    }
    if (work->flags & 0x40) {
        return;
    }
    work->angle += 30.0f;
    if (work->angle >= 360.0f) {
        work->angle -= 360.0f;
    }
    if (--work->spinTimer == 0) {
        work->flags = (work->flags | FLAG_IDLE) & ~FLAG_SPINNING;
        Hu3DMotionModelSet(object->model[0], object->motion[1]);
        Hu3DMotionAttrSet(object->model[0], 2, 2);
        work->angle = 0.0f;
    }
}

void m228_PlayerMoveUpdate(omObjData *object) {
    Vec2f screen;
    Vec pos;
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);
    s16 stickX;
    f32 speed;
    s32 screenX;

    work->tiltAngleLimit = 0.0f;
    if (!(work->flags & FLAG_IDLE)) {
        return;
    }
    if (work->flags & 4) {
        return;
    }
    if (GwPlayer[work->playerIndex].stat & PLAYER_IS_CPU) {
        stickX = m228_PlayerComStickGet(object);
    } else {
        stickX = HuPadStkX[GwPlayer[work->playerIndex].pad];
    }
    speed = (fabs((f32)stickX) - 30.0) / 5.0;
    if (stickX >= 30) {
        work->coords.x = speed + work->coords.x;
        work->tiltAngleLimit = -30.0f;
        pos.x = work->coords.x;
        pos.y = work->coords.y;
        pos.z = work->coords.z;
        Hu3D3Dto2D(0, &pos, &screen);
        screenX = screen.x;
        if (screenX >= 256) {
            work->coords.x -= speed;
        }
        work->flags &= ~8;
    }
    if (stickX <= -30) {
        work->coords.x -= speed;
        work->tiltAngleLimit = 30.0f;
        pos.x = work->coords.x;
        pos.y = work->coords.y;
        pos.z = work->coords.z;
        Hu3D3Dto2D(0, &pos, &screen);
        screenX = screen.x;
        if (screenX <= 64) {
            work->coords.x = speed + work->coords.x;
        }
        work->flags &= ~8;
    }
    if (abs(stickX) < 30 && !(work->flags & FLAG_SPINNING)) {
        work->tiltAngleLimit = 0.0f;
    }
}

void m228_PlayerParasolUpdate(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);
    u16 pressed;

    if (work->flags & FLAG_IDLE) {
        if (GwPlayer[work->playerIndex].stat & PLAYER_IS_CPU) {
            pressed = m228_PlayerComBtnGet(object);
        } else {
            pressed = HuPadBtnDown[GwPlayer[work->playerIndex].pad];
        }
        if (pressed & A_BUTTON) {
            if (work->flags & 4) {
                m228_ParasolOpen(object);
            } else {
                m228_ParasolClose(object);
            }
        }
    }
}

void m228_PlayerTiltUpdate(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    if (work->angle > work->tiltAngleLimit) {
        work->angle -= 10.0f;
    }
    if (work->angle < work->tiltAngleLimit) {
        work->angle += 10.0f;
    }
}

void m228_PlayerHitUpdate(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);
    ParasolPlummetWork *other;
    ParasolPlummetItemWork *item;
    Vec2f screen;
    Vec pos;
    s32 screenX;
    f32 offset;
    f32 dx;
    f32 dy;
    s16 hit;

    hit = m228_PlayerHitGet(object, 0);
    if (work->flags & FLAG_SPINNING) {
        return;
    }
    if (work->flags & 0x100) {
        return;
    }
    if (work->flags & 0x20) {
        return;
    }
    if (work->flags & 0x80) {
        return;
    }
    if (hit == -1) {
        return;
    }

    if (hit & 0x10) {
        other = OM_GET_DATA_PTR(m228_playerObjTbl[hit & 0xF], ParasolPlummetWork);
        if (work->flags & 4) {
            offset = 0.0f;
            while (TRUE) {
                dx = work->coords.x - other->coords.x + offset;
                dy = work->coords.y - other->coords.y;
                if (HuSqrtf(dx * dx + dy * dy) >= 150.0f) {
                    break;
                }
                pos.x = offset + work->coords.x;
                pos.y = work->coords.y;
                pos.z = work->coords.z;
                Hu3D3Dto2D(0, &pos, &screen);
                screenX = screen.x;
                if (dx >= 0.0f) {
                    if (screenX > 256) {
                        offset = other->coords.x - work->coords.x - 1.0f;
                    } else {
                        offset += 1.0f;
                    }
                } else {
                    if (screenX < 64) {
                        offset = other->coords.x - work->coords.x + 1.0f;
                    } else {
                        offset -= 1.0f;
                    }
                }
            }
            work->coords.x += offset;
        } else {
            if (other->flags & 4) {
                return;
            }
            if (work->flags & 0x80) {
                return;
            }
            work->flags = (work->flags | 0x80) & ~FLAG_IDLE;
            work->driftTimer = 5;
            work->driftVelX = 48.0f;
            dx = work->coords.x - other->coords.x;
            omVibrate(work->playerIndex, 10, 0, 10);
            if (dx < 0.0f) {
                work->driftVelX = -work->driftVelX;
            }
            other->flags = (other->flags | 0x80) & ~FLAG_IDLE;
            other->driftTimer = 5;
            omVibrate(other->playerIndex, 10, 0, 10);
            other->driftVelX = -work->driftVelX;
        }
    } else {
        item = OM_GET_DATA_PTR(m228_itemObjTbl[hit], ParasolPlummetItemWork);
        switch (item->type) {
            case 1:
                HuAudFXPlay(9);
                GwPlayer[work->playerIndex].gameCoin += 1;
                Hu3DModelAttrSet(m228_itemObjTbl[hit]->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                EffectGroupEmit(m228_starEffGrp, item->x, item->y, 0.0f);
                m228_itemActiveTbl[item->slot] = 0;
                break;
            case 2:
                HuAudFXPlay(0x15);
                GwPlayer[work->playerIndex].gameCoin += 5;
                Hu3DModelAttrSet(m228_itemObjTbl[hit]->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                EffectGroupEmit(m228_starEffGrp, item->x, item->y, 0.0f);
                m228_itemActiveTbl[item->slot] = 0;
                break;
            case 3:
                m228_PlayerSpinStart(object);
                m228_PlayerBlinkStart(object);
                break;
        }
    }
}

void m228_PlayerGoalUpdate(omObjData *object) {
    f32 startX[4] = { -260.0f, -100.0f, 100.0f, 260.0f };
    f32 laneX[4] = { -210.0f, -70.0f, 70.0f, 210.0f };
    s32 modelIds[8] = { 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 1 };
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);
    ParasolPlummetGoalWork *goal = OM_GET_DATA_PTR(m228_goalObj, ParasolPlummetGoalWork);
    s32 group;

    if (!(work->flags & 0x20)) {
        return;
    }
    if (m228_flowStat == 0) {
        work->coords.x = goal->pos.x + startX[work->lane];
        work->coords.y = goal->pos.y + 300.0f;
        work->coords.z = goal->pos.z + 200.0f;
        if (fabs(work->coords.x) <= 500.0 && fabs(work->coords.z) <= 100.0) {
            work->coords.z = 0.0f;
            work->flags = (work->flags | 0x10) & ~0x20;
            work->unk_2C = 130.0f;
            Hu3DMotionModelSet(object->model[0], object->motion[3]);
            Hu3DModelAttrSet(object->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelPosSet(object->model[4], object->trans.x, object->trans.y, object->trans.z);
        }
    } else {
        if (work->driftTimer == 0) {
            Hu3DMotionModelSet(object->model[0], object->motion[0]);
            Hu3DMotionAttrSet(object->model[0], 2, 2);
        }
        if (work->driftTimer == 120) {
            group = m228_voiceChrTbl[GwPlayer[work->playerIndex].chr] << 16;
            if (GwPlayer[work->playerIndex].gameCoin != 0) {
                Hu3DMotionModelSet(object->model[0], object->motion[5]);
                HuAudCharVoicePlay(group | 0x2F);
            } else {
                Hu3DMotionModelSet(object->model[0], object->motion[6]);
            }
        }
        work->coords.x = goal->pos.x + laneX[work->lane];
        work->coords.y = goal->pos.y + 300.0f;
        work->coords.z = goal->pos.z + 200.0f;
        work->driftTimer++;
    }
}

s32 m228_PlayerComStickGet(omObjData *object) {
    s32 stickX = 0;
    f32 dist[18];
    s32 itemIndex[18];
    ParasolPlummetWork *work;
    ParasolPlummetItemWork *item;
    s32 count = 0;
    s32 i;
    s32 j;
    f32 d;
    s32 tmp;

    for (i = 0; i < 18; i++) {
        d = m228_ItemDistGet(object, i);
        if (d != -1.0f) {
            dist[count] = d;
            itemIndex[count] = i;
            count++;
        }
    }
    if (count == 0) {
        return 0;
    }
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count; j++) {
            if (dist[i] < dist[j]) {
                d = dist[i];
                dist[i] = dist[j];
                dist[j] = d;
                tmp = itemIndex[i];
                itemIndex[i] = itemIndex[j];
                itemIndex[j] = tmp;
            }
        }
    }
    work = OM_GET_DATA_PTR(object, ParasolPlummetWork);
    switch (GwPlayer[work->playerIndex].cpu_difficulty) {
        case 0:
            if (rand8() == 0) {
                return 0;
            }
            item = OM_GET_DATA_PTR(m228_itemObjTbl[itemIndex[0]], ParasolPlummetItemWork);
            if (work->coords.x < item->x) {
                stickX = 70;
            }
            if (work->coords.x > item->x) {
                stickX = -70;
            }
            break;
        case 1:
            if (rand8() == 0) {
                return 0;
            }
            item = OM_GET_DATA_PTR(m228_itemObjTbl[itemIndex[0]], ParasolPlummetItemWork);
            if (work->coords.x < item->x) {
                stickX = 70;
            }
            if (work->coords.x > item->x) {
                stickX = -70;
            }
            break;
        case 2:
            if (rand8() == 0) {
                return 0;
            }
            item = OM_GET_DATA_PTR(m228_itemObjTbl[itemIndex[0]], ParasolPlummetItemWork);
            if (work->coords.x < item->x) {
                stickX = 70;
            }
            if (work->coords.x > item->x) {
                stickX = -70;
            }
            break;
        case 3:
            if (rand8() == 0) {
                return 0;
            }
            item = OM_GET_DATA_PTR(m228_itemObjTbl[itemIndex[0]], ParasolPlummetItemWork);
            if (work->coords.x < item->x) {
                stickX = 70;
            }
            if (work->coords.x > item->x) {
                stickX = -70;
            }
            break;
    }
    return stickX;
}

u16 m228_PlayerComBtnGet(omObjData *object) {
    f32 dist[18];
    s32 itemIndex[18];
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);
    ParasolPlummetItemWork *item;
    u16 buttons = 0;
    s32 count;
    s32 i;
    s32 j;
    f32 d;
    s32 tmp;

    if (work->cpuTimer > 0) {
        work->cpuTimer--;
    }
    if (work->cpuTimer != 0) {
        return 0;
    }
    count = 0;
    for (i = 0; i < 18; i++) {
        d = m228_ItemDistGet(object, i);
        if (d != -1.0f) {
            dist[count] = d;
            itemIndex[count] = i;
            count++;
        }
    }
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count; j++) {
            if (dist[i] < dist[j]) {
                d = dist[i];
                dist[i] = dist[j];
                dist[j] = d;
                tmp = itemIndex[i];
                itemIndex[i] = itemIndex[j];
                itemIndex[j] = tmp;
            }
        }
    }
    work = OM_GET_DATA_PTR(object, ParasolPlummetWork);
    switch (GwPlayer[work->playerIndex].cpu_difficulty) {
        case 0:
            break;
        case 1:
            item = OM_GET_DATA_PTR(m228_itemObjTbl[itemIndex[0]], ParasolPlummetItemWork);
            if (work->coords.y > item->y && !(work->flags & 4)) {
                buttons = A_BUTTON;
            }
            if (work->coords.y < item->y && (work->flags & 4)) {
                buttons = A_BUTTON;
            }
            work->cpuTimer = (rand8() & 0x1F) + 32;
            break;
        case 2:
            item = OM_GET_DATA_PTR(m228_itemObjTbl[itemIndex[0]], ParasolPlummetItemWork);
            if (work->coords.y > item->y && !(work->flags & 4)) {
                buttons = A_BUTTON;
            }
            if (work->coords.y < item->y && (work->flags & 4)) {
                buttons = A_BUTTON;
            }
            work->cpuTimer = (rand8() & 0xF) + 16;
            break;
        case 3:
            item = OM_GET_DATA_PTR(m228_itemObjTbl[itemIndex[0]], ParasolPlummetItemWork);
            if (work->coords.y > item->y && !(work->flags & 4)) {
                buttons = A_BUTTON;
            }
            if (work->coords.y < item->y && (work->flags & 4)) {
                buttons = A_BUTTON;
            }
            work->cpuTimer = (rand8() & 7) + 8;
            break;
    }
    return buttons;
}

f32 m228_ItemDistGet(omObjData *arg0, s32 arg1) {
    f32 dist = -1.0f;
    ParasolPlummetWork *work = OM_GET_DATA_PTR(arg0, ParasolPlummetWork);
    f32 x = work->coords.x;
    f32 y = work->coords.y;

    if (m228_itemActiveTbl[arg1]) {
        ParasolPlummetItemWork *item = OM_GET_DATA_PTR(m228_itemObjTbl[arg1], ParasolPlummetItemWork);
        f32 px = item->x;
        f32 py = item->y;
        dist = HuSqrtf((px - x) * (px - x) + (py - y) * (py - y));
    }

    return dist;
}

void m228_PlayerBumpUpdate(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);
    Vec2f screen;
    Vec pos;
    s32 screenX;

    if (work->flags & 0x80) {
        work->coords.x += work->driftVelX;
        pos.x = work->coords.x;
        pos.y = work->coords.y;
        pos.z = work->coords.z;
        Hu3D3Dto2D(0, &pos, &screen);
        screenX = screen.x;
        if (screenX >= 256) {
            work->coords.x -= work->driftVelX;
        }
        if (screenX < 65) {
            work->coords.x -= work->driftVelX;
        }
        work->driftTimer--;
        if (work->driftVelX >= 0.0f) {
            work->driftVelX -= 8.0f;
        } else {
            work->driftVelX += 8.0f;
        }
        if (work->driftTimer == 0) {
            work->flags = (work->flags & ~0x80) | FLAG_IDLE;
            work->driftVelX = 0.0f;
        }
    }
}

void m228_PlayerBlinkStart(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    work->flags |= 0x100;
    work->blinkTimer = 45;
}

void m228_PlayerBlinkUpdate(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    if (!(work->flags & 0x100)) {
        return;
    }
    if (work->flags & 0x40) {
        return;
    }
    if (--work->blinkTimer == 0) {
        m228_PlayerBlinkEnd(object);
    }
    if (work->blinkTimer & 1) {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    } else {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
}

void m228_PlayerBlinkEnd(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    work->flags &= ~0x100;
}

void m228_PlayerPlummetStart(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);
    s32 flags = work->flags;

    if (flags & FLAG_SPINNING) {
        return;
    }
    if (flags & FLAG_PLUMMETING) {
        return;
    }
    if (!(flags & FLAG_IDLE)) {
        return;
    }

    work->flags = (flags | FLAG_PLUMMETING) & ~FLAG_IDLE;
    work->plummetTimer = 10;
}

void m228_PlayerPlummetUpdate(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    if (work->flags & FLAG_PLUMMETING) {
        if (--work->plummetTimer <= 0) {
            m228_PlayerPlummetEnd(object);
        }
    }
}

void m228_PlayerPlummetEnd(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    work->flags = (work->flags & ~FLAG_PLUMMETING) | FLAG_IDLE;
}

void m228_GoalCreate(void) {
    omObjData *obj;
    ParasolPlummetGoalWork *work;

    omAddPrcObj(m228_GoalProc, 0x50, 0x2000, 0);
    obj = omAddObj(0x50, 1, 2, -1, m228_GoalObjMain);
    obj->data = HuMemAllocTag(sizeof(ParasolPlummetGoalWork), 0x7918);
    m228_goalObj = obj;
    work = OM_GET_DATA_PTR(obj, ParasolPlummetGoalWork);
    obj->model[0] = Hu3DModelRead(0xA011A, 0x6D9);
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    work->angle = 90.0f;
    work->pos.x = sindf(work->angle) * 3000.0f + 3000.0f;
    work->pos.y = cosdf(work->angle) * 2000.0f;
    work->pos.z = cosdf(work->angle) * 3000.0f;
    work->flags = 1;
}

void m228_GoalObjMain(omObjData *object) {
    ParasolPlummetGoalWork *work = OM_GET_DATA_PTR(object, ParasolPlummetGoalWork);

    omSetTra(object, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    if (work->flags & 1) {
        work->pos.x = sindf(work->angle) * 3000.0f + 3000.0f;
        work->pos.y = cosdf(work->angle) * 1000.0f - 500.0f;
        work->pos.z = cosdf(work->angle) * 3000.0f;
        work->angle += 2.5f;
        if (work->angle >= 360.0f) {
            work->angle -= 360.0f;
        }
    }
    if (work->flags & 2) {
        work->pos.y = sindf(work->angle) * 1000.0f + -300.0f;
        work->pos.z += 8.0f;
    }
    if (work->flags & 4) {
        work->pos.y = sindf(work->angle) * 100.0f + -300.0f;
        work->angle += 3.0f;
        if (work->angle >= 360.0f) {
            work->angle -= 360.0f;
        }
    }
}

void m228_GoalProc(void) {
    omObjData *obj = m228_goalObj;
    ParasolPlummetGoalWork *work = OM_GET_DATA_PTR(obj, ParasolPlummetGoalWork);
    s32 i;

    work->flags |= 1;
    HuPrcSleep(120);
    Hu3DMotionAttrSet(obj->model[0], 4, 4);
    work->flags &= ~1;
    while (m228_flowStat != 3) {
        HuPrcVSleep();
    }
    Hu3DMotionAttrSet(obj->model[0], 4, 0);
    work->pos.x = 0.0f;
    work->pos.y = -2000.0f;
    work->pos.z = 0.0f;
    work->angle = 0.0f;
    work->flags |= 2;
    work->angle = 270.0f;
    for (i = 0; i < 90; i++) {
        work->angle += 1.0f;
        HuPrcVSleep();
    }
    work->flags = (work->flags & ~2) | 4;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m228_BackObjInit(omObjData *object) {
    ParasolPlummetBgWork *work;
    s32 i;

    object->data = HuMemAllocTag(sizeof(ParasolPlummetBgWork), 0x7918);
    m228_backObj = object;
    work = OM_GET_DATA_PTR(object, ParasolPlummetBgWork);
    work->posY[0] = 120.0f;
    work->posY[1] = 359.0f;
    work->spriteFileId = HuSprAnimDataRead(0x3D0002);
    for (i = 0; i < 2; i++) {
        work->espId[i] = espEntry(work->spriteFileId, 0, 1);
        espAttrSet(work->espId[i], HUSPR_ATTR_BG | HUSPR_ATTR_FILTER_BILERP);
        espPosSet(work->espId[i], 160, work->posY[i]);
        espDispOn(work->espId[i]);
        espScaleSet(work->espId[i], 1.0f, 1.0f);
        espPriSet(work->espId[i], 255);
    }
    m228_backScrollSpeed = 0.0f;
    omAddPrcObj(m228_BackScrollProc, 0x50, 0x2000, 0);
    object->func = m228_BackObjMain;
}

void m228_BackObjMain(omObjData *object) {
    ParasolPlummetBgWork *work = OM_GET_DATA_PTR(object, ParasolPlummetBgWork);
    s32 i;
    s32 y;

    for (i = 0; i < 2; i++) {
        y = work->posY[i];
        espPosSet(work->espId[i], 160, y);
        work->posY[i] += m228_backScrollSpeed;
        if (m228_backScrollSpeed < 0.0f && work->posY[i] <= -120.0f) {
            work->posY[i] += 478.0f;
        }
        if (m228_backScrollSpeed > 0.0f && work->posY[i] >= 360.0f) {
            work->posY[i] -= 478.0f;
        }
    }
}

void m228_BackScrollProc(void) {
    s32 i;

    m228_backScrollSpeed = 0.0f;
    HuPrcSleep(90);
    for (i = 0; i < 11; i++) {
        m228_backScrollSpeed = i * -5.0f / 10.0f;
        HuPrcVSleep();
    }
    while (m228_flowStat != 3) {
        HuPrcVSleep();
    }
    for (i = 0; i < 31; i++) {
        m228_backScrollSpeed = (30.0f - i) * -5.0f / 30.0f;
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    m228_backScrollSpeed = -2.5f;
    HuPrcSleep(50);
    m228_backScrollSpeed = 0.0f;
    HuPrcSleep(30);
    for (i = 0; i < 11; i++) {
        m228_backScrollSpeed = i * 5.0f / 10.0f;
        HuPrcVSleep();
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m228_CloudProc(void) {
    s32 i;

    m228_cloudAnim = HuSprAnimDataRead(0x210028);
    for (i = 0; i < 5; i++) {
        m228_cloudActiveTbl[i] = 0;
        m228_cloudSprTbl[i] = espEntry(m228_cloudAnim, 0, 1);
        espAttrSet(m228_cloudSprTbl[i], HUSPR_ATTR_BG | HUSPR_ATTR_FILTER_BILERP);
        espDispOff(m228_cloudSprTbl[i]);
        espScaleSet(m228_cloudSprTbl[i], 1.0f, 1.0f);
        espPosSet(m228_cloudSprTbl[i], 160, 300);
        espPriSet(m228_cloudSprTbl[i], 50);
    }
    while (TRUE) {
        if (rand8() % 50 == 0 && m228_backScrollSpeed == -5.0f) {
            for (i = 0; i < 5; i++) {
                if (m228_cloudActiveTbl[i] == 0) {
                    m228_CloudCreate(i);
                    break;
                }
            }
        }
        HuPrcVSleep();
    }
}

void m228_CloudCreate(s32 index) {
    omObjData *obj;
    ParasolPlummetCloudWork *work;
    s32 x;
    s32 y;

    obj = omAddObj(10, 0, 0, -1, m228_CloudObjMain);
    work = HuMemAllocTag(sizeof(ParasolPlummetCloudWork), 0x7918);
    obj->data = work;
    work->velY = rand8() % 1 + -6.0f;
    work->x = (rand8() * 2) % 240 + 40;
    work->y = 280.0f;
    work->index = index;
    work->angle = 0.0f;
    work->baseScale = rand8() % 1 + 1.0f;
    work->scaleAmp = ((rand8() & 1) + 1) / 10.0f;
    x = work->x;
    y = work->y;
    espPosSet(m228_cloudSprTbl[work->index], x, y);
    espDispOn(m228_cloudSprTbl[index]);
    m228_cloudActiveTbl[index] = 1;
}

void m228_CloudObjMain(omObjData *object) {
    ParasolPlummetCloudWork *work = OM_GET_DATA_PTR(object, ParasolPlummetCloudWork);
    s32 x;
    s32 y;
    f32 scale;

    x = work->x;
    y = work->y;
    espPosSet(m228_cloudSprTbl[work->index], x, y);
    work->y += -5.0f - m228_backScrollSpeed + work->velY;
    work->angle += 10.0f;
    if (work->angle >= 360.0f) {
        work->angle -= 360.0f;
    }
    scale = sindf(work->angle) * work->scaleAmp + work->baseScale;
    espScaleSet(m228_cloudSprTbl[work->index], scale, scale);
    if (work->y <= -40.0f) {
        espDispOff(m228_cloudSprTbl[work->index]);
        m228_cloudActiveTbl[work->index] = 0;
        omDelObj(object);
    }
}

void m228_SideObjInit(omObjData *object) {
    s32 spriteIndex[3] = { 0, 1, 1 };
    s32 posX[2] = { 24, 296 };
    s32 posY[3] = { 360, 600, 840 };
    s32 spriteIds[2];
    ParasolPlummetSideWork *work;
    s32 i;
    s16 x;
    s16 y;

    object->data = HuMemAllocTag(sizeof(ParasolPlummetSideWork), 0x7918);
    work = OM_GET_DATA_PTR(object, ParasolPlummetSideWork);
    spriteIds[0] = HuSprAnimDataRead(0x3D0005);
    spriteIds[1] = HuSprAnimDataRead(0x3D0003);
    for (i = 0; i < 6; i++) {
        work->espId[i] = espEntry(spriteIds[spriteIndex[i % 3]], 0, 1);
        work->x[i] = posX[i / 3];
        work->y[i] = posY[i % 3];
        x = work->x[i];
        y = work->y[i];
        espAttrSet(work->espId[i], HUSPR_ATTR_BG | HUSPR_ATTR_FILTER_BILERP);
        if (i >= 3) {
            espAttrSet(work->espId[i], HUSPR_ATTR_FLIPX);
        }
        espPosSet(work->espId[i], x, y);
        espDispOn(work->espId[i]);
        espScaleSet(work->espId[i], 1.0f, 1.0f);
        espPriSet(work->espId[i], 30);
    }
    espAttrReset(work->espId[3], HUSPR_ATTR_BG);
    m228_flyerStatFlag = 0;
    m228_sideScrollSpeed = 0.0f;
    omAddPrcObj(m228_SideScrollProc, 0x50, 0x2000, 0);
    object->func = m228_SideObjMain;
}

void m228_SideObjMain(omObjData *object) {
    ParasolPlummetSideWork *work = OM_GET_DATA_PTR(object, ParasolPlummetSideWork);
    s32 i;
    s32 x;
    s32 y;

    for (i = 0; i < 6; i++) {
        x = work->x[i];
        y = work->y[i];
        espPosSet(work->espId[i], x, y);
        work->y[i] += m228_sideScrollSpeed;
        if (m228_sideScrollSpeed < 0.0f && work->y[i] <= -120.0f) {
            if (i % 3 == 0) {
                espDispOff(work->espId[i]);
            }
            work->y[i] += 480.0f;
        }
        if (m228_sideScrollSpeed > 0.0f && work->y[i] >= 360.0f) {
            work->y[i] -= 480.0f;
        }
    }
    if (OM_GET_DATA_PTR(m228_goalObj, ParasolPlummetGoalWork)->pos.z >= 0.0f) {
        espAttrSet(work->espId[3], HUSPR_ATTR_BG);
    }
}

void m228_SideScrollProc(void) {
    s32 i;

    m228_sideScrollSpeed = 0.0f;
    HuPrcSleep(30);
    m228_sideScrollSpeed = -4.0f;
    HuPrcSleep(30);
    m228_sideScrollSpeed = 0.0f;
    HuPrcSleep(30);
    for (i = 0; i < 10; i++) {
        m228_sideScrollSpeed = i * -8.0f / 10.0f;
        HuPrcVSleep();
    }
    while (m228_flowStat != 3) {
        HuPrcVSleep();
    }
    for (i = 0; i < 31; i++) {
        m228_sideScrollSpeed = (30.0f - i) * -8.0f / 30.0f;
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    m228_sideScrollSpeed = -4.0f;
    HuPrcSleep(50);
    m228_sideScrollSpeed = 0.0f;
    HuPrcSleep(30);
    for (i = 0; i < 11; i++) {
        m228_sideScrollSpeed = i * 8.0f / 10.0f;
        HuPrcVSleep();
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m228_FlyerCreateAll(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        m228_flyerActiveTbl[i] = 0;
        m228_FlyerCreate(i);
    }
    m228_flyerNextY = 341.0f;
    m228_flyerNextTimer = 6.0f;
    omAddPrcObj(m228_FlyerSpawnProc, 0x50, 0x2000, 0);
    m228_flyerSideF = rand8() & 1;
}

void m228_FlyerSpawnProc(void) {
    s32 i;
    s32 j;

    HuPrcSleep(270);
    for (i = 0; i < 29; i++) {
        for (j = 0; j < 5; j++) {
            if (m228_flyerActiveTbl[j] == 0) {
                m228_FlyerStart(j);
                break;
            }
        }
        HuPrcSleep(30);
    }
    while (m228_flowStat != 4) {
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void m228_FlyerStart(s32 index) {
    omObjData *obj = m228_flyerObjTbl[index];
    ParasolPlummetFlyerWork *work = OM_GET_DATA_PTR(obj, ParasolPlummetFlyerWork);
    Vec2f screen;
    Vec pos;
    f32 x;
    f32 y;

    if (m228_flyerSideF) {
        work->rotY = 90.0f;
        work->x = 30.0f;
    } else {
        work->rotY = 270.0f;
        work->x = 290.0f;
    }
    m228_flyerSideF = (m228_flyerSideF + 1) & 1;
    work->y = m228_flyerNextY;
    m228_flyerNextY -= 43.2f;
    if (m228_flyerNextY <= 281.0f) {
        m228_flyerNextY += 60.0f;
    }
    screen.x = work->x;
    screen.y = work->y;
    Hu3D2Dto3D(0, CZoom, &screen, &pos);
    x = pos.x;
    y = pos.y;
    work->flags |= 1;
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    m228_flyerActiveTbl[index] = 1;
    work->index = index;
    work->timer = m228_flyerNextTimer;
    m228_flyerNextTimer -= 1.0f;
    if (m228_flyerNextTimer <= 0.0f) {
        m228_flyerNextTimer = 5.0f;
    }
    omSetTra(obj, x, y, 0.0f);
    omSetRot(obj, 0.0f, work->rotY, 0.0f);
}

void m228_FlyerCreate(s32 index) {
    omObjData *obj;
    ParasolPlummetFlyerWork *work;

    obj = omAddObj(10, 1, 2, -1, m228_FlyerObjMain);
    work = HuMemAllocTag(sizeof(ParasolPlummetFlyerWork), 0x7918);
    obj->data = work;
    obj->model[0] = Hu3DModelRead(0xA0117, 0x6DD);
    omObjMotionRead(obj, 0, 0xA0118);
    Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[0], 2, 2);
    omObjMotionRead(obj, 1, 0xA0119);
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    m228_flyerObjTbl[index] = obj;
    work->flags = 0;
    work->index = index;
}

void m228_FlyerObjMain(omObjData *object) {
    ParasolPlummetFlyerWork *work;
    Vec2f screen;
    Vec pos;
    f32 x;
    f32 y;
    f32 motTime;

    if (m228_flowStat == 4) {
        omDelObj(object);
        return;
    }
    work = OM_GET_DATA_PTR(object, ParasolPlummetFlyerWork);
    if (work->flags == 0) {
        return;
    }
    screen.x = work->x;
    screen.y = work->y;
    Hu3D2Dto3D(0, CZoom, &screen, &pos);
    x = pos.x;
    y = pos.y;
    if (work->flags & 2) {
        m228_flyerThrowY = y + 70.0f;
    }
    omSetTra(object, x, y, 0.0f);
    work->y += m228_sideScrollSpeed;
    work->timer--;
    if (work->y <= 250.0f && !(work->flags & 2)) {
        Hu3DMotionModelSet(object->model[0], object->motion[1]);
        Hu3DMotionTimeSet(object->model[0], 30.0f);
        work->flags |= 2;
    }
    if (work->flags & 2) {
        motTime = Hu3DData[object->model[0]].motTime;
        if (motTime >= 37.0f && motTime < 39.0f) {
            m228_itemThrowF |= 1;
            m228_flyerThrowNo = work->index;
        }
    }
    if (work->y <= 20.0f) {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        m228_flyerActiveTbl[work->index] = 0;
        work->flags = 0;
    }
}

void m228_ItemCreateAll(void) {
    s32 i;

    for (i = 0; i < 18; i++) {
        m228_itemActiveTbl[i] = 0;
        m228_ItemCreate(i);
    }
    omAddPrcObj(m228_ItemThrowProc, 0x50, 0x2000, 0);
    for (i = 0; i < 58; i++) {
        if (i < 8) {
            m228_itemPoolTbl[i] = 3;
        } else if (i < 53) {
            m228_itemPoolTbl[i] = 1;
        } else {
            m228_itemPoolTbl[i] = 2;
        }
    }
}

void m228_ItemThrowProc(void) {
    s32 spawnedType[4];
    s32 done;
    s32 i;
    s32 j;
    s32 tries;
    s32 r;

    while (m228_flowStat != 4) {
        if (m228_itemThrowF & 1) {
            for (i = 0; i < 2; i++) {
                done = 0;
                tries = 0;
                do {
                    r = rand8() % 58;
                    switch (m228_itemPoolTbl[r]) {
                        case 1:
                            for (j = 0; j < 6; j++) {
                                if (m228_itemActiveTbl[j] == 0) {
                                    m228_ItemThrow(j);
                                    done++;
                                    spawnedType[i] = m228_itemPoolTbl[r];
                                    m228_itemPoolTbl[r] = -1;
                                    break;
                                }
                            }
                            break;
                        case 2:
                            for (j = 0; j < i; j++) {
                                if (spawnedType[j] == 2) {
                                    break;
                                }
                            }
                            if (j != i) {
                                break;
                            }
                            for (j = 6; j < 12; j++) {
                                if (m228_itemActiveTbl[j] == 0) {
                                    m228_ItemThrow(j);
                                    done++;
                                    spawnedType[i] = m228_itemPoolTbl[r];
                                    m228_itemPoolTbl[r] = -1;
                                    break;
                                }
                            }
                            break;
                        case 3:
                            for (j = 0; j < i; j++) {
                                if (spawnedType[j] == 3) {
                                    break;
                                }
                            }
                            if (j != i) {
                                break;
                            }
                            for (j = 12; j < 18; j++) {
                                if (m228_itemActiveTbl[j] == 0) {
                                    m228_ItemThrow(j);
                                    done++;
                                    spawnedType[i] = m228_itemPoolTbl[r];
                                    m228_itemPoolTbl[r] = -1;
                                    break;
                                }
                            }
                            break;
                    }
                    tries++;
                    if (tries == 1000) {
                        done++;
                    }
                } while (done == 0);
                HuPrcSleep(3);
            }
            m228_itemThrowF &= ~1;
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void m228_ItemThrow(s32 index) {
    omObjData *obj = m228_itemObjTbl[index];
    ParasolPlummetItemWork *item = OM_GET_DATA_PTR(obj, ParasolPlummetItemWork);
    ParasolPlummetFlyerWork *flyer;
    Vec2f screen;
    Vec pos;
    f32 x;
    f32 y;

    item->flags |= 1;
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    m228_itemActiveTbl[index] = 1;
    item->slot = index;
    flyer = OM_GET_DATA_PTR(m228_flyerObjTbl[m228_flyerThrowNo], ParasolPlummetFlyerWork);
    screen.x = flyer->x;
    screen.y = flyer->y;
    Hu3D2Dto3D(0, CZoom, &screen, &pos);
    x = pos.x;
    y = pos.y;
    if (x >= 0.0f) {
        item->x = x - 100.0f;
    } else {
        item->x = x + 100.0f;
    }
    item->y = y + 70.0f;
    item->rotZ = 0.0f;
    item->velX = rand8() % 5 + 5;
    item->rotSpeed = -20.0f;
    if (item->x > 0.0f) {
        item->velX = -item->velX;
        item->rotSpeed = -item->rotSpeed;
    }
    item->velY = rand8() % 3 + 45;
}

void m228_ItemCreate(s32 index) {
    f32 scales[3] = { 3.0f, 3.0f, 3.0f };
    s8 types[3] = { 1, 2, 3 };
    s32 files[3] = { 0x210026, 0x210027, 0x3D0004 };
    omObjData *obj;
    ParasolPlummetItemWork *item;
    void *data;
    s16 model;

    obj = omAddObj(11, 1, 0, -1, m228_ItemObjMain);
    item = obj->data = HuMemAllocTag(sizeof(ParasolPlummetItemWork), 0x7918);
    item->type = types[index / 6];
    if (index % 6 == 0) {
        data = DataRead(files[index / 6]);
        model = Hu3DSprModelCreate(data, 0x6DD, 8);
        DataClose(data);
        m228_itemMdlTbl[index / 6] = model;
    } else {
        model = Hu3DSprModelLink(m228_itemMdlTbl[index / 6], 8);
    }
    obj->model[0] = Hu3DSprModelData[model].modelId;
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    item->scale = scales[index / 6];
    omSetSca(obj, item->scale, item->scale, item->scale);
    m228_itemObjTbl[index] = obj;
    item->flags = 0;
}

void m228_ItemObjMain(omObjData *object) {
    ParasolPlummetItemWork *item = OM_GET_DATA_PTR(object, ParasolPlummetItemWork);
    Vec2f screen;
    Vec pos;

    if (!(item->flags & 1)) {
        return;
    }
    if (m228_flowStat == 4) {
        omDelObj(object);
        return;
    }
    omSetTra(object, item->x, item->y, 0.0f);
    omSetRot(object, 0.0f, 0.0f, item->rotZ);
    item->x += item->velX;
    item->y += item->velY;
    item->velY -= 1.0f;
    if (item->velY < -20.0f) {
        item->velY = -20.0f;
    }
    if (item->type == 3) {
        item->rotZ += item->rotSpeed;
        if (item->rotZ >= 360.0f) {
            item->rotZ -= 360.0f;
        }
        if (item->rotZ < 0.0f) {
            item->rotZ += 360.0f;
        }
    }
    pos.x = item->x;
    pos.y = item->y;
    pos.z = 0.0f;
    Hu3D3Dto2D(0, &pos, &screen);
    if ((s32)screen.y >= 240) {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        m228_itemActiveTbl[item->slot] = 0;
        item->flags &= ~1;
    }
    if (m228_flowStat != 1 && m228_flowStat != 2) {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        m228_itemActiveTbl[item->slot] = 0;
        item->y = item->x = -10000.0f;
    }
}

s16 m228_PlayerHitGet(omObjData *object, s32 isItem) {
    ParasolPlummetWork *work;
    ParasolPlummetWork *other;
    ParasolPlummetItemWork *item;
    f32 minDist;
    f32 dist;
    f32 x;
    f32 y;
    f32 otherX;
    f32 otherY;
    f32 ofs;
    s32 hit;
    s32 i;

    minDist = 100.0f;
    hit = -1;
    if (isItem == 0) {
        work = OM_GET_DATA_PTR(object, ParasolPlummetWork);
        ofs = 0.0f;
        x = work->coords.x - ofs;
        y = work->coords.y - ofs + ofs;
    } else {
        x = OM_GET_DATA_PTR(object, ParasolPlummetItemWork)->x;
        y = OM_GET_DATA_PTR(object, ParasolPlummetItemWork)->y;
    }
    for (i = 0; i < 4; i++) {
        if (m228_playerObjTbl[i] == object) {
            continue;
        }
        other = OM_GET_DATA_PTR(m228_playerObjTbl[i], ParasolPlummetWork);
        ofs = 0.0f;
        otherX = other->coords.x - ofs;
        otherY = other->coords.y - ofs;
        dist = HuSqrtf((otherX - x) * (otherX - x) + (otherY - y) * (otherY - y));
        if (dist < minDist) {
            hit = i | 0x10;
            minDist = dist;
        }
    }
    if (isItem == 0) {
        for (i = 0; i < 18; i++) {
            if (m228_itemActiveTbl[i] != 1) {
                continue;
            }
            if (m228_itemObjTbl[i] == object) {
                continue;
            }
            item = OM_GET_DATA_PTR(m228_itemObjTbl[i], ParasolPlummetItemWork);
            otherX = item->x;
            otherY = item->y;
            dist = HuSqrtf((otherX - x) * (otherX - x) + (otherY - y) * (otherY - y));
            if (dist < minDist && dist < 80.0f) {
                hit = i;
                minDist = dist;
            }
        }
    }
    return hit;
}

void m228_HudCreate(void) {
    s16 posX[4] = { 32, 224, 32, 224 };
    s16 posY[4] = { 24, 24, 216, 216 };
    s32 charIcons[8] = { 8, 9, 10, 11, 12, 13, 14, 15 };
    s16 i;
    s16 j;
    s16 x;
    s16 y;

    m228_hudDigitAnim = HuSprAnimDataRead(0x31);
    m228_hudCrossAnim = HuSprAnimDataRead(0x21001B);
    m228_hudCoinAnim = HuSprAnimDataRead(0x21001A);
    for (i = 0; i < 4; i++) {
        x = posX[i];
        y = posY[i];
        m228_hudChrIconAnimTbl[i] = HuSprAnimDataRead(0x210000 | charIcons[GwPlayer[i].chr]);
        m228_hudChrIconTbl[i] = espEntry(m228_hudChrIconAnimTbl[i], 0, 1);
        espPosSet(m228_hudChrIconTbl[i], x, y);
        m228_hudCoinTbl[i] = espEntry(m228_hudCoinAnim, 0, 1);
        espPosSet(m228_hudCoinTbl[i], x + 16, y);
        m228_hudCrossTbl[i] = espEntry(m228_hudCrossAnim, 0, 1);
        espPosSet(m228_hudCrossTbl[i], x + 32, y);
        for (j = 0; j < 3; j++) {
            m228_hudDigitTbl[i * 3 + j] = espEntry(m228_hudDigitAnim, 0, 1);
            espPriSet(m228_hudDigitTbl[i * 3 + j], 10);
            espAttrSet(m228_hudDigitTbl[i * 3 + j], HUSPR_ATTR_XLU);
            espPosSet(m228_hudDigitTbl[i * 3 + j], x + 32 + j * 12, y);
        }
    }
    omPrcSetStatBit(omAddPrcObj(m228_HudProc, 0, 0, 0), 0x80);
}

void m228_HudProc(void) {
    s16 posX[4] = { 32, 236, 32, 236 };
    s16 posY[4] = { 24, 24, 216, 216 };
    s32 i;
    s32 j;
    s32 x;
    s32 y;
    s32 total;
    s32 coins;
    s32 divisor;
    s32 digit;

    while (TRUE) {
        for (i = 0; i < 4; i++) {
            x = posX[i];
            y = posY[i];
            espPosSet(m228_hudChrIconTbl[i], x, y);
            espPosSet(m228_hudCoinTbl[i], x + 16, y);
            espPosSet(m228_hudCrossTbl[i], x + 32, y);
            divisor = 100;
            total = GwPlayer[i].gameCoin;
            coins = total;
            for (j = 0; j < 3; j++) {
                espPosSet(m228_hudDigitTbl[i * 3 + j], x + 32 + j * 12, y);
                digit = coins / divisor;
                coins -= digit * divisor;
                espDispOn(m228_hudDigitTbl[i * 3 + j]);
                if (divisor == 100 && total < 100) {
                    espDispOff(m228_hudDigitTbl[i * 3 + j]);
                }
                if (divisor == 10 && total < 10) {
                    espDispOff(m228_hudDigitTbl[i * 3 + j]);
                }
                if (total >= 100) {
                    espDispOff(m228_hudCrossTbl[i]);
                }
                espAnimModeSet(m228_hudDigitTbl[i * 3 + j], 1);
                espBankSet(m228_hudDigitTbl[i * 3 + j], (u16)digit, 0);
                divisor /= 10;
            }
        }
        HuPrcVSleep();
    }
}

void m228_CameraInit(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ) {
    CamSetupInit(1);
    m228_cameraNo = CamSetupMapCullAdd();
    ScissorSet(m228_cameraNo, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(m228_cameraNo, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    CZoom = zoom;
    CRot.x = rotX;
    CRot.y = rotY;
    CRot.z = rotZ;
    Center.x = centerX;
    Center.y = centerY;
    Center.z = centerZ;
    Hu3DCameraPerspectiveSet(m228_cameraNo, 30.0f, 80.0f, 8000.0f);
}
