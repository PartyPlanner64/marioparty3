#include "common.h"
#include "game/overlays/minigame.h"

#define FLAG_IDLE 0x1
#define FLAG_SPINNING 0x2
#define FLAG_PLUMMETING 0x200

// Per-player work allocated in func_80105EC0_parasol_plummet, stored at ObjData->data
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

// Object data for the falling item objects held in D_8010AB70_parasol_plummet,
// created in func_80109B38_parasol_plummet.
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

// Object data for the object held in D_8010ABCC_parasol_plummet,
// created in func_80107D30_parasol_plummet.
typedef struct ParasolPlummetGoalWork {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 angle;
    /* 0x10 */ s32 flags;
} ParasolPlummetGoalWork; // Size 0x14

// Object data for the scrolling background sprites held in D_8010AC6C_parasol_plummet,
// created in func_80108178_parasol_plummet.
typedef struct ParasolPlummetBgWork {
    /* 0x00 */ f32 posY[2];
    /* 0x08 */ s16 spriteFileId;
    /* 0x0A */ s16 espId[2];
    /* 0x0E */ char unk_0E[6];
} ParasolPlummetBgWork; // Size 0x14

// Object data for the cloud sprite objects created in func_801086F0_parasol_plummet.
typedef struct ParasolPlummetCloudWork {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 velY;
    /* 0x0C */ f32 baseScale;
    /* 0x10 */ f32 scaleAmp;
    /* 0x14 */ f32 angle;
    /* 0x18 */ s32 index;
} ParasolPlummetCloudWork; // Size 0x1C

// Object data for the background sprites object, created in func_801089E0_parasol_plummet.
typedef struct ParasolPlummetBg2Work {
    /* 0x00 */ f32 x[6];
    /* 0x18 */ f32 y[6];
    /* 0x30 */ s16 unk_30;
    /* 0x32 */ s16 espId[6];
    /* 0x3E */ char unk_3E[2];
} ParasolPlummetBg2Work; // Size 0x40

// Object data for the objects held in D_8010AC80_parasol_plummet,
// created in func_801092B0_parasol_plummet.
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
} ParasolPlummetBssAC74;

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02[4];
    /* 0x0A */ s16 unk0A[4];
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E[4];
} ParasolPlummetBssACC0;

MinigameFlow D_8010A8A0_parasol_plummet = {
    MG_STATE_OPENING, MINIGAME_4P, MG_TIMER_COUNT_DOWN, MG_TIME_DISP_COUNTDOWN, FALSE, MG_GAUGE_NONE, MG_RESULT_NONE, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    180, 900, -1, 210, 60
};
s32 D_8010A8C8_parasol_plummet[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };

s32 D_8010AB50_parasol_plummet BSS;
u8 D_8010AB54_parasol_plummet BSS;
f32 D_8010AB58_parasol_plummet BSS;
u8 D_8010AB5C_parasol_plummet[4] BSS; /* Unreferenced. */
omObjData *D_8010AB60_parasol_plummet[4] BSS;
omObjData *D_8010AB70_parasol_plummet[0x12] BSS;
u8 D_8010ABB8_parasol_plummet[0x14] BSS;
omObjData *D_8010ABCC_parasol_plummet BSS;
u16 D_8010ABD0_parasol_plummet BSS;
u8 D_8010ABD4_parasol_plummet[4] BSS; /* Unreferenced. */
s16 D_8010ABD8_parasol_plummet[60] BSS;
f32 D_8010AC50_parasol_plummet[4] BSS;
s32 D_8010AC60_parasol_plummet BSS;
s16 D_8010AC64_parasol_plummet BSS;
u8 D_8010AC66_parasol_plummet BSS;
f32 D_8010AC68_parasol_plummet BSS;
omObjData *D_8010AC6C_parasol_plummet BSS;
f32 D_8010AC70_parasol_plummet BSS;
ParasolPlummetBssAC74 parasolPlummetBssAC74 BSS;
u8 D_8010AC7C_parasol_plummet[4] BSS; /* Unreferenced. */
omObjData *D_8010AC80_parasol_plummet[5] BSS;
f32 D_8010AC94_parasol_plummet BSS;
f32 D_8010AC98_parasol_plummet BSS;
s32 D_8010AC9C_parasol_plummet BSS;
s16 D_8010ACA0_parasol_plummet[3] BSS;
s16 D_8010ACA8_parasol_plummet[12] BSS;
ParasolPlummetBssACC0 parasolPlummetBssACC0 BSS;
u8 D_8010ACE8_parasol_plummet[8] BSS; /* Unreferenced. */
s16 D_8010ACF0_parasol_plummet[5] BSS;
s16 D_8010ACFA_parasol_plummet BSS;
u8 D_8010ACFC_parasol_plummet[5] BSS;

/* Fields of parasolPlummetBssAC74 and parasolPlummetBssACC0 (aliased in undefined_syms.txt). */
extern u8 D_8010AC74_parasol_plummet;
extern u8 D_8010AC75_parasol_plummet[5];
extern s16 D_8010ACC0_parasol_plummet;
extern s16 D_8010ACC2_parasol_plummet[4];
extern s16 D_8010ACCA_parasol_plummet[4];
extern s16 D_8010ACD2_parasol_plummet;
extern s16 D_8010ACD4_parasol_plummet[4];
extern s16 D_8010ACDC_parasol_plummet;
extern s16 D_8010ACDE_parasol_plummet[4];

void func_80105B94_parasol_plummet(omObjData *object);
void func_80105E94_parasol_plummet(omObjData *object);
void func_80105EC0_parasol_plummet(s32 playerIndex);
void func_80106418_parasol_plummet(omObjData *object);
void func_80106788_parasol_plummet(omObjData *object);
void func_8010687C_parasol_plummet(omObjData *object);
void func_801069E4_parasol_plummet(omObjData *object);
void func_80106AB4_parasol_plummet(omObjData *object);
void func_80106CDC_parasol_plummet(omObjData *object);
void func_80106DB0_parasol_plummet(omObjData *object);
void func_80106E14_parasol_plummet(omObjData *object);
void func_801071B4_parasol_plummet(omObjData *object);
s32 func_801074CC_parasol_plummet(omObjData *object);
u16 func_801076D4_parasol_plummet(omObjData *object);
f32 func_801079D8_parasol_plummet(omObjData *arg0, s32 arg1);
void func_80107A44_parasol_plummet(omObjData *object);
void func_80107B5C_parasol_plummet(omObjData *object);
void func_80107B78_parasol_plummet(omObjData *object);
void func_80107C30_parasol_plummet(omObjData *object);
void func_80107C94_parasol_plummet(omObjData *object);
void func_80107CD4_parasol_plummet(omObjData *object);
void func_80107D14_parasol_plummet(omObjData *object);
void func_80107D30_parasol_plummet(void);
void func_80107E6C_parasol_plummet(omObjData *object);
void func_8010803C_parasol_plummet(void);
void func_80108178_parasol_plummet(omObjData *object);
void func_801082CC_parasol_plummet(omObjData *object);
void func_801083F8_parasol_plummet(void);
void func_8010856C_parasol_plummet(void);
void func_801086F0_parasol_plummet(s32 index);
void func_80108878_parasol_plummet(omObjData *object);
void func_801089E0_parasol_plummet(omObjData *object);
void func_80108C1C_parasol_plummet(omObjData *object);
void func_80108DD0_parasol_plummet(void);
void func_80108F6C_parasol_plummet(void);
void func_80108FFC_parasol_plummet(void);
void func_801090A8_parasol_plummet(s32 index);
void func_801092B0_parasol_plummet(s32 index);
void func_801093D4_parasol_plummet(omObjData *object);
void func_80109604_parasol_plummet(void);
void func_801096BC_parasol_plummet(void);
void func_8010995C_parasol_plummet(s32 index);
void func_80109B38_parasol_plummet(s32 index);
void func_80109D74_parasol_plummet(omObjData *object);
s16 func_80109F7C_parasol_plummet(omObjData *object, s32 isItem);
void func_8010A160_parasol_plummet(void);
void func_8010A484_parasol_plummet(void);
void func_8010A75C_parasol_plummet(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ);

void func_801059A0_parasol_plummet(void) {
    omObjData *obj;
    s32 i;

    omInitObjMan(40, 10);
    MapCollInit(16);
    Hu3DQuadPoolInit(&mgQuadPool, 64);
    Hu3DSprModelInit(64);
    omGameSysInit();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_8010A75C_parasol_plummet(2500.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    omOutView(obj);
    Hu3DBGColorSet(0, 0, 0);
    MgFlowInit(&D_8010A8A0_parasol_plummet);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    for (i = 0; i < 4; i++) {
        D_8010AC50_parasol_plummet[i] = 0.0f;
    }
    for (i = 0; i < 4; i++) {
        D_8010AB60_parasol_plummet[i] = NULL;
        func_80105EC0_parasol_plummet(i);
    }
    func_80107D30_parasol_plummet();
    omAddObj(0x50, 0, 0, -1, func_80108178_parasol_plummet);
    omAddObj(0x50, 0, 0, -1, func_801089E0_parasol_plummet);
    omAddObj(0x50, 0, 0, -1, func_80105B94_parasol_plummet);
    omAddPrcObj(func_8010856C_parasol_plummet, 0x50, 0x2000, 0);
    func_80108F6C_parasol_plummet();
    func_80109604_parasol_plummet();
    D_8010AB54_parasol_plummet = 0;
    D_8010ABD0_parasol_plummet = 0;
    func_8010A160_parasol_plummet();
    D_8010AC64_parasol_plummet = EffectGroupStarCreate(0x2A9, 4);
}

void func_80105B94_parasol_plummet(omObjData *object) {
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
        WipeCreateOut(0, 20);
    }
    switch (D_8010AC66_parasol_plummet = MgFlowMain(object)) {
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
            if (D_8010ABD0_parasol_plummet == 0) {
                for (i = 0; i < 4; i++) {
                    work = OM_GET_DATA_PTR(D_8010AB60_parasol_plummet[i], ParasolPlummetWork);
                    if (!(work->flags & FLAG_IDLE)) {
                        work->flags |= FLAG_IDLE;
                    }
                }
                D_8010ABD0_parasol_plummet++;
            }
            break;
        case 3:
            work = OM_GET_DATA_PTR(D_8010AB60_parasol_plummet[0], ParasolPlummetWork);
            if (!(work->flags & 0x40)) {
                for (i = 0; i < 4; i++) {
                    work = OM_GET_DATA_PTR(D_8010AB60_parasol_plummet[i], ParasolPlummetWork);
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
                    work = OM_GET_DATA_PTR(D_8010AB60_parasol_plummet[i], ParasolPlummetWork);
                    work->lane = lane[i];
                }
            }
            for (i = 0; i < 4; i++) {
                work = OM_GET_DATA_PTR(D_8010AB60_parasol_plummet[i], ParasolPlummetWork);
                if (!(work->flags & 0x40)) {
                    func_80107C30_parasol_plummet(D_8010AB60_parasol_plummet[i]);
                    func_80107D14_parasol_plummet(D_8010AB60_parasol_plummet[i]);
                    func_80107D14_parasol_plummet(D_8010AB60_parasol_plummet[i]);
                    work->flags = (work->flags | 0x40) & ~FLAG_IDLE;
                    func_8010687C_parasol_plummet(D_8010AB60_parasol_plummet[i]);
                }
            }
            D_8010A8A0_parasol_plummet.resultType = MG_RESULT_NONE;
            if (MgFlowStatTimeGet() == 135) {
                HuAudSeqPlay(0x66);
            }
            break;
        case 4:
            break;
        case 5:
            WipeCreateOut(0, 20);
            object->func = func_80105E94_parasol_plummet;
            break;
    }
}

void func_80105E94_parasol_plummet(omObjData *object) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

void func_80105EC0_parasol_plummet(s32 playerIndex) {
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

    object = omAddObj(0x50, 5, 10, -1, func_80106418_parasol_plummet);
    object->data = HuMemAllocTag(sizeof(ParasolPlummetWork), 0x7918);
    D_8010AB60_parasol_plummet[playerIndex] = object;
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
    group = D_8010A8C8_parasol_plummet[chr] << 16;
    modelId = modelIds[chr];
    while (TRUE) {
        lane = rand8() & 3;
        if (D_8010AC50_parasol_plummet[lane] == 0.0f) {
            work->lane = lane;
            D_8010AC50_parasol_plummet[lane] += 1.0f;
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
    Hu3DModelAttrSet(object->model[1], 4, 4);
    omObjMotionRead(object, 8, 0x3D0000);
    Hu3DMotionModelSet(object->model[1], object->motion[8]);
    Hu3DMotionAttrSet(object->model[1], 2, 2);
    omObjMotionRead(object, 9, 0x3D0001);

    object->model[2] = Hu3DModelRead(0x3D0007, 0x6D9);
    Hu3DModelPosSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[2], 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrSet(object->model[2], 4, 4);

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

void func_80106418_parasol_plummet(omObjData *object) {
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
    func_80106AB4_parasol_plummet(object);
    func_80107A44_parasol_plummet(object);
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
            func_8010687C_parasol_plummet(object);
            Hu3DModelAttrSet(object->model[1], 4, 0);
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
        func_8010687C_parasol_plummet(object);
        func_80107C94_parasol_plummet(object);
    }
    if (screenY >= 240) {
        work->coords.y -= -24.0f;
        if (work->flags & 0x40) {
            if (work->coords.y <= OM_GET_DATA_PTR(D_8010ABCC_parasol_plummet, ParasolPlummetGoalWork)->pos.y) {
                work->flags |= 0x20;
                work->flags &= ~4;
                work->flags &= ~0x80;
                work->flags &= ~FLAG_SPINNING;
                work->flags &= ~FLAG_IDLE;
                work->driftTimer = 0;
                work->angle = 0.0f;
                Hu3DModelAttrSet(object->model[1], 4, 4);
            }
        } else if (!(work->flags & FLAG_SPINNING)) {
            func_80106788_parasol_plummet(object);
        }
    }
    func_801071B4_parasol_plummet(object);
    func_801069E4_parasol_plummet(object);
    func_80107B78_parasol_plummet(object);
    func_80106CDC_parasol_plummet(object);
    func_80106E14_parasol_plummet(object);
    func_80106DB0_parasol_plummet(object);
    func_80107CD4_parasol_plummet(object);
}

void func_80106788_parasol_plummet(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    if (!(work->flags & 0x20)) {
        Hu3DMotionModelSet(object->model[0], object->motion[1]);
        Hu3DMotionAttrSet(object->model[0], 2, 2);
        Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[8]].motId, 0, 10, 2);
        Hu3DModelAttrSet(object->model[1], 4, 0);
        work->unk_10 = 1;
        work->flags &= ~4;
        if (MgFlowStatGet() == MG_STATE_PLAY) {
            _HuAudPlayerFXPlay(0x3E1, work->playerIndex);
        }
    }
}

void func_8010687C_parasol_plummet(omObjData *object) {
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

void func_8010693C_parasol_plummet(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    if (!(work->flags & 0x40)) {
        work->spinTimer = 30;
        work->flags = (work->flags & ~FLAG_IDLE) | FLAG_SPINNING;
        func_8010687C_parasol_plummet(object);
        Hu3DMotionModelSet(object->model[0], object->motion[4]);
        Hu3DMotionAttrSet(object->model[0], 2, 2);
        PlayerFXPlay(0x286, work->playerIndex);
        HuAudFXPlay(0x3E6);
        omVibrate(work->playerIndex, 2, 2, 20);
    }
}

void func_801069E4_parasol_plummet(omObjData *object) {
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

void func_80106AB4_parasol_plummet(omObjData *object) {
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
    if (GwPlayer[work->playerIndex].stat & 1) {
        stickX = func_801074CC_parasol_plummet(object);
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

void func_80106CDC_parasol_plummet(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);
    u16 pressed;

    if (work->flags & FLAG_IDLE) {
        if (GwPlayer[work->playerIndex].stat & 1) {
            pressed = func_801076D4_parasol_plummet(object);
        } else {
            pressed = HuPadBtnDown[GwPlayer[work->playerIndex].pad];
        }
        if (pressed & A_BUTTON) {
            if (work->flags & 4) {
                func_80106788_parasol_plummet(object);
            } else {
                func_8010687C_parasol_plummet(object);
            }
        }
    }
}

void func_80106DB0_parasol_plummet(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    if (work->angle > work->tiltAngleLimit) {
        work->angle -= 10.0f;
    }
    if (work->angle < work->tiltAngleLimit) {
        work->angle += 10.0f;
    }
}

void func_80106E14_parasol_plummet(omObjData *object) {
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

    hit = func_80109F7C_parasol_plummet(object, 0);
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
        other = OM_GET_DATA_PTR(D_8010AB60_parasol_plummet[hit & 0xF], ParasolPlummetWork);
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
        item = OM_GET_DATA_PTR(D_8010AB70_parasol_plummet[hit], ParasolPlummetItemWork);
        switch (item->type) {
            case 1:
                HuAudFXPlay(9);
                GwPlayer[work->playerIndex].gameCoin += 1;
                Hu3DModelAttrSet(D_8010AB70_parasol_plummet[hit]->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                EffectGroupEmit(D_8010AC64_parasol_plummet, item->x, item->y, 0.0f);
                D_8010ABB8_parasol_plummet[item->slot] = 0;
                break;
            case 2:
                HuAudFXPlay(0x15);
                GwPlayer[work->playerIndex].gameCoin += 5;
                Hu3DModelAttrSet(D_8010AB70_parasol_plummet[hit]->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                EffectGroupEmit(D_8010AC64_parasol_plummet, item->x, item->y, 0.0f);
                D_8010ABB8_parasol_plummet[item->slot] = 0;
                break;
            case 3:
                func_8010693C_parasol_plummet(object);
                func_80107B5C_parasol_plummet(object);
                break;
        }
    }
}

void func_801071B4_parasol_plummet(omObjData *object) {
    f32 startX[4] = { -260.0f, -100.0f, 100.0f, 260.0f };
    f32 laneX[4] = { -210.0f, -70.0f, 70.0f, 210.0f };
    s32 modelIds[8] = { 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 1 };
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);
    ParasolPlummetGoalWork *goal = OM_GET_DATA_PTR(D_8010ABCC_parasol_plummet, ParasolPlummetGoalWork);
    s32 group;

    if (!(work->flags & 0x20)) {
        return;
    }
    if (D_8010AC66_parasol_plummet == 0) {
        work->coords.x = goal->pos.x + startX[work->lane];
        work->coords.y = goal->pos.y + 300.0f;
        work->coords.z = goal->pos.z + 200.0f;
        if (fabs(work->coords.x) <= 500.0 && fabs(work->coords.z) <= 100.0) {
            work->coords.z = 0.0f;
            work->flags = (work->flags | 0x10) & ~0x20;
            work->unk_2C = 130.0f;
            Hu3DMotionModelSet(object->model[0], object->motion[3]);
            Hu3DModelAttrSet(object->model[4], 4, 0);
            Hu3DModelPosSet(object->model[4], object->trans.x, object->trans.y, object->trans.z);
        }
    } else {
        if (work->driftTimer == 0) {
            Hu3DMotionModelSet(object->model[0], object->motion[0]);
            Hu3DMotionAttrSet(object->model[0], 2, 2);
        }
        if (work->driftTimer == 120) {
            group = D_8010A8C8_parasol_plummet[GwPlayer[work->playerIndex].chr] << 16;
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

s32 func_801074CC_parasol_plummet(omObjData *object) {
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
        d = func_801079D8_parasol_plummet(object, i);
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
            item = OM_GET_DATA_PTR(D_8010AB70_parasol_plummet[itemIndex[0]], ParasolPlummetItemWork);
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
            item = OM_GET_DATA_PTR(D_8010AB70_parasol_plummet[itemIndex[0]], ParasolPlummetItemWork);
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
            item = OM_GET_DATA_PTR(D_8010AB70_parasol_plummet[itemIndex[0]], ParasolPlummetItemWork);
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
            item = OM_GET_DATA_PTR(D_8010AB70_parasol_plummet[itemIndex[0]], ParasolPlummetItemWork);
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

u16 func_801076D4_parasol_plummet(omObjData *object) {
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
        d = func_801079D8_parasol_plummet(object, i);
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
            item = OM_GET_DATA_PTR(D_8010AB70_parasol_plummet[itemIndex[0]], ParasolPlummetItemWork);
            if (work->coords.y > item->y && !(work->flags & 4)) {
                buttons = A_BUTTON;
            }
            if (work->coords.y < item->y && (work->flags & 4)) {
                buttons = A_BUTTON;
            }
            work->cpuTimer = (rand8() & 0x1F) + 32;
            break;
        case 2:
            item = OM_GET_DATA_PTR(D_8010AB70_parasol_plummet[itemIndex[0]], ParasolPlummetItemWork);
            if (work->coords.y > item->y && !(work->flags & 4)) {
                buttons = A_BUTTON;
            }
            if (work->coords.y < item->y && (work->flags & 4)) {
                buttons = A_BUTTON;
            }
            work->cpuTimer = (rand8() & 0xF) + 16;
            break;
        case 3:
            item = OM_GET_DATA_PTR(D_8010AB70_parasol_plummet[itemIndex[0]], ParasolPlummetItemWork);
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

f32 func_801079D8_parasol_plummet(omObjData *arg0, s32 arg1) {
    f32 dist = -1.0f;
    ParasolPlummetWork *work = OM_GET_DATA_PTR(arg0, ParasolPlummetWork);
    f32 x = work->coords.x;
    f32 y = work->coords.y;

    if (D_8010ABB8_parasol_plummet[arg1]) {
        ParasolPlummetItemWork *item = OM_GET_DATA_PTR(D_8010AB70_parasol_plummet[arg1], ParasolPlummetItemWork);
        f32 px = item->x;
        f32 py = item->y;
        dist = HuSqrtf((px - x) * (px - x) + (py - y) * (py - y));
    }

    return dist;
}

void func_80107A44_parasol_plummet(omObjData *object) {
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

void func_80107B5C_parasol_plummet(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    work->flags |= 0x100;
    work->blinkTimer = 45;
}

void func_80107B78_parasol_plummet(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    if (!(work->flags & 0x100)) {
        return;
    }
    if (work->flags & 0x40) {
        return;
    }
    if (--work->blinkTimer == 0) {
        func_80107C30_parasol_plummet(object);
    }
    if (work->blinkTimer & 1) {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    } else {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
}

void func_80107C30_parasol_plummet(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    work->flags &= ~0x100;
}

void func_80107C94_parasol_plummet(omObjData *object) {
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

void func_80107CD4_parasol_plummet(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    if (work->flags & FLAG_PLUMMETING) {
        if (--work->plummetTimer <= 0) {
            func_80107D14_parasol_plummet(object);
        }
    }
}

void func_80107D14_parasol_plummet(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    work->flags = (work->flags & ~FLAG_PLUMMETING) | FLAG_IDLE;
}

void func_80107D30_parasol_plummet(void) {
    omObjData *obj;
    ParasolPlummetGoalWork *work;

    omAddPrcObj(func_8010803C_parasol_plummet, 0x50, 0x2000, 0);
    obj = omAddObj(0x50, 1, 2, -1, func_80107E6C_parasol_plummet);
    obj->data = HuMemAllocTag(sizeof(ParasolPlummetGoalWork), 0x7918);
    D_8010ABCC_parasol_plummet = obj;
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

void func_80107E6C_parasol_plummet(omObjData *object) {
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

void func_8010803C_parasol_plummet(void) {
    omObjData *obj = D_8010ABCC_parasol_plummet;
    ParasolPlummetGoalWork *work = OM_GET_DATA_PTR(obj, ParasolPlummetGoalWork);
    s32 i;

    work->flags |= 1;
    HuPrcSleep(120);
    Hu3DMotionAttrSet(obj->model[0], 4, 4);
    work->flags &= ~1;
    while (D_8010AC66_parasol_plummet != 3) {
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

void func_80108178_parasol_plummet(omObjData *object) {
    ParasolPlummetBgWork *work;
    s32 i;

    object->data = HuMemAllocTag(sizeof(ParasolPlummetBgWork), 0x7918);
    D_8010AC6C_parasol_plummet = object;
    work = OM_GET_DATA_PTR(object, ParasolPlummetBgWork);
    work->posY[0] = 120.0f;
    work->posY[1] = 359.0f;
    work->spriteFileId = HuSprAnimDataRead(0x3D0002);
    for (i = 0; i < 2; i++) {
        work->espId[i] = espEntry(work->spriteFileId, 0, 1);
        espAttrSet(work->espId[i], 0x4008);
        espPosSet(work->espId[i], 160, work->posY[i]);
        espDispOn(work->espId[i]);
        espScaleSet(work->espId[i], 1.0f, 1.0f);
        espPriSet(work->espId[i], 255);
    }
    D_8010AC68_parasol_plummet = 0.0f;
    omAddPrcObj(func_801083F8_parasol_plummet, 0x50, 0x2000, 0);
    object->func = func_801082CC_parasol_plummet;
}

void func_801082CC_parasol_plummet(omObjData *object) {
    ParasolPlummetBgWork *work = OM_GET_DATA_PTR(object, ParasolPlummetBgWork);
    s32 i;
    s32 y;

    for (i = 0; i < 2; i++) {
        y = work->posY[i];
        espPosSet(work->espId[i], 160, y);
        work->posY[i] += D_8010AC68_parasol_plummet;
        if (D_8010AC68_parasol_plummet < 0.0f && work->posY[i] <= -120.0f) {
            work->posY[i] += 478.0f;
        }
        if (D_8010AC68_parasol_plummet > 0.0f && work->posY[i] >= 360.0f) {
            work->posY[i] -= 478.0f;
        }
    }
}

void func_801083F8_parasol_plummet(void) {
    s32 i;

    D_8010AC68_parasol_plummet = 0.0f;
    HuPrcSleep(90);
    for (i = 0; i < 11; i++) {
        D_8010AC68_parasol_plummet = i * -5.0f / 10.0f;
        HuPrcVSleep();
    }
    while (D_8010AC66_parasol_plummet != 3) {
        HuPrcVSleep();
    }
    for (i = 0; i < 31; i++) {
        D_8010AC68_parasol_plummet = (30.0f - i) * -5.0f / 30.0f;
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    D_8010AC68_parasol_plummet = -2.5f;
    HuPrcSleep(50);
    D_8010AC68_parasol_plummet = 0.0f;
    HuPrcSleep(30);
    for (i = 0; i < 11; i++) {
        D_8010AC68_parasol_plummet = i * 5.0f / 10.0f;
        HuPrcVSleep();
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_8010856C_parasol_plummet(void) {
    s32 i;

    D_8010ACFA_parasol_plummet = HuSprAnimDataRead(0x210028);
    for (i = 0; i < 5; i++) {
        D_8010ACFC_parasol_plummet[i] = 0;
        D_8010ACF0_parasol_plummet[i] = espEntry(D_8010ACFA_parasol_plummet, 0, 1);
        espAttrSet(D_8010ACF0_parasol_plummet[i], 0x4008);
        espDispOff(D_8010ACF0_parasol_plummet[i]);
        espScaleSet(D_8010ACF0_parasol_plummet[i], 1.0f, 1.0f);
        espPosSet(D_8010ACF0_parasol_plummet[i], 160, 300);
        espPriSet(D_8010ACF0_parasol_plummet[i], 50);
    }
    while (TRUE) {
        if (rand8() % 50 == 0 && D_8010AC68_parasol_plummet == -5.0f) {
            for (i = 0; i < 5; i++) {
                if (D_8010ACFC_parasol_plummet[i] == 0) {
                    func_801086F0_parasol_plummet(i);
                    break;
                }
            }
        }
        HuPrcVSleep();
    }
}

void func_801086F0_parasol_plummet(s32 index) {
    omObjData *obj;
    ParasolPlummetCloudWork *work;
    s32 x;
    s32 y;

    obj = omAddObj(10, 0, 0, -1, func_80108878_parasol_plummet);
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
    espPosSet(D_8010ACF0_parasol_plummet[work->index], x, y);
    espDispOn(D_8010ACF0_parasol_plummet[index]);
    D_8010ACFC_parasol_plummet[index] = 1;
}

void func_80108878_parasol_plummet(omObjData *object) {
    ParasolPlummetCloudWork *work = OM_GET_DATA_PTR(object, ParasolPlummetCloudWork);
    s32 x;
    s32 y;
    f32 scale;

    x = work->x;
    y = work->y;
    espPosSet(D_8010ACF0_parasol_plummet[work->index], x, y);
    work->y += -5.0f - D_8010AC68_parasol_plummet + work->velY;
    work->angle += 10.0f;
    if (work->angle >= 360.0f) {
        work->angle -= 360.0f;
    }
    scale = sindf(work->angle) * work->scaleAmp + work->baseScale;
    espScaleSet(D_8010ACF0_parasol_plummet[work->index], scale, scale);
    if (work->y <= -40.0f) {
        espDispOff(D_8010ACF0_parasol_plummet[work->index]);
        D_8010ACFC_parasol_plummet[work->index] = 0;
        omDelObj(object);
    }
}

void func_801089E0_parasol_plummet(omObjData *object) {
    s32 spriteIndex[3] = { 0, 1, 1 };
    s32 posX[2] = { 24, 296 };
    s32 posY[3] = { 360, 600, 840 };
    s32 spriteIds[2];
    ParasolPlummetBg2Work *work;
    s32 i;
    s16 x;
    s16 y;

    object->data = HuMemAllocTag(sizeof(ParasolPlummetBg2Work), 0x7918);
    work = OM_GET_DATA_PTR(object, ParasolPlummetBg2Work);
    spriteIds[0] = HuSprAnimDataRead(0x3D0005);
    spriteIds[1] = HuSprAnimDataRead(0x3D0003);
    for (i = 0; i < 6; i++) {
        work->espId[i] = espEntry(spriteIds[spriteIndex[i % 3]], 0, 1);
        work->x[i] = posX[i / 3];
        work->y[i] = posY[i % 3];
        x = work->x[i];
        y = work->y[i];
        espAttrSet(work->espId[i], 0x4008);
        if (i >= 3) {
            espAttrSet(work->espId[i], 1);
        }
        espPosSet(work->espId[i], x, y);
        espDispOn(work->espId[i]);
        espScaleSet(work->espId[i], 1.0f, 1.0f);
        espPriSet(work->espId[i], 30);
    }
    espAttrReset(work->espId[3], 0x4000);
    D_8010AC74_parasol_plummet = 0;
    D_8010AC70_parasol_plummet = 0.0f;
    omAddPrcObj(func_80108DD0_parasol_plummet, 0x50, 0x2000, 0);
    object->func = func_80108C1C_parasol_plummet;
}

void func_80108C1C_parasol_plummet(omObjData *object) {
    ParasolPlummetBg2Work *work = OM_GET_DATA_PTR(object, ParasolPlummetBg2Work);
    s32 i;
    s32 x;
    s32 y;

    for (i = 0; i < 6; i++) {
        x = work->x[i];
        y = work->y[i];
        espPosSet(work->espId[i], x, y);
        work->y[i] += D_8010AC70_parasol_plummet;
        if (D_8010AC70_parasol_plummet < 0.0f && work->y[i] <= -120.0f) {
            if (i % 3 == 0) {
                espDispOff(work->espId[i]);
            }
            work->y[i] += 480.0f;
        }
        if (D_8010AC70_parasol_plummet > 0.0f && work->y[i] >= 360.0f) {
            work->y[i] -= 480.0f;
        }
    }
    if (OM_GET_DATA_PTR(D_8010ABCC_parasol_plummet, ParasolPlummetGoalWork)->pos.z >= 0.0f) {
        espAttrSet(work->espId[3], 0x4000);
    }
}

void func_80108DD0_parasol_plummet(void) {
    s32 i;

    D_8010AC70_parasol_plummet = 0.0f;
    HuPrcSleep(30);
    D_8010AC70_parasol_plummet = -4.0f;
    HuPrcSleep(30);
    D_8010AC70_parasol_plummet = 0.0f;
    HuPrcSleep(30);
    for (i = 0; i < 10; i++) {
        D_8010AC70_parasol_plummet = i * -8.0f / 10.0f;
        HuPrcVSleep();
    }
    while (D_8010AC66_parasol_plummet != 3) {
        HuPrcVSleep();
    }
    for (i = 0; i < 31; i++) {
        D_8010AC70_parasol_plummet = (30.0f - i) * -8.0f / 30.0f;
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    D_8010AC70_parasol_plummet = -4.0f;
    HuPrcSleep(50);
    D_8010AC70_parasol_plummet = 0.0f;
    HuPrcSleep(30);
    for (i = 0; i < 11; i++) {
        D_8010AC70_parasol_plummet = i * 8.0f / 10.0f;
        HuPrcVSleep();
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_80108F6C_parasol_plummet(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        D_8010AC75_parasol_plummet[i] = 0;
        func_801092B0_parasol_plummet(i);
    }
    D_8010AC94_parasol_plummet = 341.0f;
    D_8010AC98_parasol_plummet = 6.0f;
    omAddPrcObj(func_80108FFC_parasol_plummet, 0x50, 0x2000, 0);
    D_8010AC9C_parasol_plummet = rand8() & 1;
}

void func_80108FFC_parasol_plummet(void) {
    s32 i;
    s32 j;

    HuPrcSleep(270);
    for (i = 0; i < 29; i++) {
        for (j = 0; j < 5; j++) {
            if (D_8010AC75_parasol_plummet[j] == 0) {
                func_801090A8_parasol_plummet(j);
                break;
            }
        }
        HuPrcSleep(30);
    }
    while (D_8010AC66_parasol_plummet != 4) {
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void func_801090A8_parasol_plummet(s32 index) {
    omObjData *obj = D_8010AC80_parasol_plummet[index];
    ParasolPlummetFlyerWork *work = OM_GET_DATA_PTR(obj, ParasolPlummetFlyerWork);
    Vec2f screen;
    Vec pos;
    f32 x;
    f32 y;

    if (D_8010AC9C_parasol_plummet) {
        work->rotY = 90.0f;
        work->x = 30.0f;
    } else {
        work->rotY = 270.0f;
        work->x = 290.0f;
    }
    D_8010AC9C_parasol_plummet = (D_8010AC9C_parasol_plummet + 1) & 1;
    work->y = D_8010AC94_parasol_plummet;
    D_8010AC94_parasol_plummet -= 43.2f;
    if (D_8010AC94_parasol_plummet <= 281.0f) {
        D_8010AC94_parasol_plummet += 60.0f;
    }
    screen.x = work->x;
    screen.y = work->y;
    Hu3D2Dto3D(0, CZoom, &screen, &pos);
    x = pos.x;
    y = pos.y;
    work->flags |= 1;
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    D_8010AC75_parasol_plummet[index] = 1;
    work->index = index;
    work->timer = D_8010AC98_parasol_plummet;
    D_8010AC98_parasol_plummet -= 1.0f;
    if (D_8010AC98_parasol_plummet <= 0.0f) {
        D_8010AC98_parasol_plummet = 5.0f;
    }
    omSetTra(obj, x, y, 0.0f);
    omSetRot(obj, 0.0f, work->rotY, 0.0f);
}

void func_801092B0_parasol_plummet(s32 index) {
    omObjData *obj;
    ParasolPlummetFlyerWork *work;

    obj = omAddObj(10, 1, 2, -1, func_801093D4_parasol_plummet);
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
    D_8010AC80_parasol_plummet[index] = obj;
    work->flags = 0;
    work->index = index;
}

void func_801093D4_parasol_plummet(omObjData *object) {
    ParasolPlummetFlyerWork *work;
    Vec2f screen;
    Vec pos;
    f32 x;
    f32 y;
    f32 motTime;

    if (D_8010AC66_parasol_plummet == 4) {
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
        D_8010AB58_parasol_plummet = y + 70.0f;
    }
    omSetTra(object, x, y, 0.0f);
    work->y += D_8010AC70_parasol_plummet;
    work->timer--;
    if (work->y <= 250.0f && !(work->flags & 2)) {
        Hu3DMotionModelSet(object->model[0], object->motion[1]);
        Hu3DMotionTimeSet(object->model[0], 30.0f);
        work->flags |= 2;
    }
    if (work->flags & 2) {
        motTime = Hu3DData[object->model[0]].motTime;
        if (motTime >= 37.0f && motTime < 39.0f) {
            D_8010AB54_parasol_plummet |= 1;
            D_8010AC60_parasol_plummet = work->index;
        }
    }
    if (work->y <= 20.0f) {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        D_8010AC75_parasol_plummet[work->index] = 0;
        work->flags = 0;
    }
}

void func_80109604_parasol_plummet(void) {
    s32 i;

    for (i = 0; i < 18; i++) {
        D_8010ABB8_parasol_plummet[i] = 0;
        func_80109B38_parasol_plummet(i);
    }
    omAddPrcObj(func_801096BC_parasol_plummet, 0x50, 0x2000, 0);
    for (i = 0; i < 58; i++) {
        if (i < 8) {
            D_8010ABD8_parasol_plummet[i] = 3;
        } else if (i < 53) {
            D_8010ABD8_parasol_plummet[i] = 1;
        } else {
            D_8010ABD8_parasol_plummet[i] = 2;
        }
    }
}

void func_801096BC_parasol_plummet(void) {
    s32 spawnedType[4];
    s32 done;
    s32 i;
    s32 j;
    s32 tries;
    s32 r;

    while (D_8010AC66_parasol_plummet != 4) {
        if (D_8010AB54_parasol_plummet & 1) {
            for (i = 0; i < 2; i++) {
                done = 0;
                tries = 0;
                do {
                    r = rand8() % 58;
                    switch (D_8010ABD8_parasol_plummet[r]) {
                        case 1:
                            for (j = 0; j < 6; j++) {
                                if (D_8010ABB8_parasol_plummet[j] == 0) {
                                    func_8010995C_parasol_plummet(j);
                                    done++;
                                    spawnedType[i] = D_8010ABD8_parasol_plummet[r];
                                    D_8010ABD8_parasol_plummet[r] = -1;
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
                                if (D_8010ABB8_parasol_plummet[j] == 0) {
                                    func_8010995C_parasol_plummet(j);
                                    done++;
                                    spawnedType[i] = D_8010ABD8_parasol_plummet[r];
                                    D_8010ABD8_parasol_plummet[r] = -1;
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
                                if (D_8010ABB8_parasol_plummet[j] == 0) {
                                    func_8010995C_parasol_plummet(j);
                                    done++;
                                    spawnedType[i] = D_8010ABD8_parasol_plummet[r];
                                    D_8010ABD8_parasol_plummet[r] = -1;
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
            D_8010AB54_parasol_plummet &= ~1;
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void func_8010995C_parasol_plummet(s32 index) {
    omObjData *obj = D_8010AB70_parasol_plummet[index];
    ParasolPlummetItemWork *item = OM_GET_DATA_PTR(obj, ParasolPlummetItemWork);
    ParasolPlummetFlyerWork *flyer;
    Vec2f screen;
    Vec pos;
    f32 x;
    f32 y;

    item->flags |= 1;
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    D_8010ABB8_parasol_plummet[index] = 1;
    item->slot = index;
    flyer = OM_GET_DATA_PTR(D_8010AC80_parasol_plummet[D_8010AC60_parasol_plummet], ParasolPlummetFlyerWork);
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

void func_80109B38_parasol_plummet(s32 index) {
    f32 scales[3] = { 3.0f, 3.0f, 3.0f };
    s8 types[3] = { 1, 2, 3 };
    s32 files[3] = { 0x210026, 0x210027, 0x3D0004 };
    omObjData *obj;
    ParasolPlummetItemWork *item;
    void *data;
    s16 model;

    obj = omAddObj(11, 1, 0, -1, func_80109D74_parasol_plummet);
    item = obj->data = HuMemAllocTag(sizeof(ParasolPlummetItemWork), 0x7918);
    item->type = types[index / 6];
    if (index % 6 == 0) {
        data = DataRead(files[index / 6]);
        model = Hu3DSprModelCreate(data, 0x6DD, 8);
        DataClose(data);
        D_8010ACA0_parasol_plummet[index / 6] = model;
    } else {
        model = Hu3DSprModelLink(D_8010ACA0_parasol_plummet[index / 6], 8);
    }
    obj->model[0] = Hu3DSprModelData[model].modelId;
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    item->scale = scales[index / 6];
    omSetSca(obj, item->scale, item->scale, item->scale);
    D_8010AB70_parasol_plummet[index] = obj;
    item->flags = 0;
}

void func_80109D74_parasol_plummet(omObjData *object) {
    ParasolPlummetItemWork *item = OM_GET_DATA_PTR(object, ParasolPlummetItemWork);
    Vec2f screen;
    Vec pos;

    if (!(item->flags & 1)) {
        return;
    }
    if (D_8010AC66_parasol_plummet == 4) {
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
        D_8010ABB8_parasol_plummet[item->slot] = 0;
        item->flags &= ~1;
    }
    if (D_8010AC66_parasol_plummet != 1 && D_8010AC66_parasol_plummet != 2) {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        D_8010ABB8_parasol_plummet[item->slot] = 0;
        item->y = item->x = -10000.0f;
    }
}

s16 func_80109F7C_parasol_plummet(omObjData *object, s32 isItem) {
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
        if (D_8010AB60_parasol_plummet[i] == object) {
            continue;
        }
        other = OM_GET_DATA_PTR(D_8010AB60_parasol_plummet[i], ParasolPlummetWork);
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
            if (D_8010ABB8_parasol_plummet[i] != 1) {
                continue;
            }
            if (D_8010AB70_parasol_plummet[i] == object) {
                continue;
            }
            item = OM_GET_DATA_PTR(D_8010AB70_parasol_plummet[i], ParasolPlummetItemWork);
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

void func_8010A160_parasol_plummet(void) {
    s16 posX[4] = { 32, 224, 32, 224 };
    s16 posY[4] = { 24, 24, 216, 216 };
    s32 charIcons[8] = { 8, 9, 10, 11, 12, 13, 14, 15 };
    s16 i;
    s16 j;
    s16 x;
    s16 y;

    D_8010ACC0_parasol_plummet = HuSprAnimDataRead(0x31);
    D_8010ACDC_parasol_plummet = HuSprAnimDataRead(0x21001B);
    D_8010ACD2_parasol_plummet = HuSprAnimDataRead(0x21001A);
    for (i = 0; i < 4; i++) {
        x = posX[i];
        y = posY[i];
        D_8010ACC2_parasol_plummet[i] = HuSprAnimDataRead(0x210000 | charIcons[GwPlayer[i].chr]);
        D_8010ACCA_parasol_plummet[i] = espEntry(D_8010ACC2_parasol_plummet[i], 0, 1);
        espPosSet(D_8010ACCA_parasol_plummet[i], x, y);
        D_8010ACD4_parasol_plummet[i] = espEntry(D_8010ACD2_parasol_plummet, 0, 1);
        espPosSet(D_8010ACD4_parasol_plummet[i], x + 16, y);
        D_8010ACDE_parasol_plummet[i] = espEntry(D_8010ACDC_parasol_plummet, 0, 1);
        espPosSet(D_8010ACDE_parasol_plummet[i], x + 32, y);
        for (j = 0; j < 3; j++) {
            D_8010ACA8_parasol_plummet[i * 3 + j] = espEntry(D_8010ACC0_parasol_plummet, 0, 1);
            espPriSet(D_8010ACA8_parasol_plummet[i * 3 + j], 10);
            espAttrSet(D_8010ACA8_parasol_plummet[i * 3 + j], 0x1000);
            espPosSet(D_8010ACA8_parasol_plummet[i * 3 + j], x + 32 + j * 12, y);
        }
    }
    omPrcSetStatBit(omAddPrcObj(func_8010A484_parasol_plummet, 0, 0, 0), 0x80);
}

void func_8010A484_parasol_plummet(void) {
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
            espPosSet(D_8010ACCA_parasol_plummet[i], x, y);
            espPosSet(D_8010ACD4_parasol_plummet[i], x + 16, y);
            espPosSet(D_8010ACDE_parasol_plummet[i], x + 32, y);
            divisor = 100;
            total = GwPlayer[i].gameCoin;
            coins = total;
            for (j = 0; j < 3; j++) {
                espPosSet(D_8010ACA8_parasol_plummet[i * 3 + j], x + 32 + j * 12, y);
                digit = coins / divisor;
                coins -= digit * divisor;
                espDispOn(D_8010ACA8_parasol_plummet[i * 3 + j]);
                if (divisor == 100 && total < 100) {
                    espDispOff(D_8010ACA8_parasol_plummet[i * 3 + j]);
                }
                if (divisor == 10 && total < 10) {
                    espDispOff(D_8010ACA8_parasol_plummet[i * 3 + j]);
                }
                if (total >= 100) {
                    espDispOff(D_8010ACDE_parasol_plummet[i]);
                }
                espAnimModeSet(D_8010ACA8_parasol_plummet[i * 3 + j], 1);
                espBankSet(D_8010ACA8_parasol_plummet[i * 3 + j], (u16)digit, 0);
                divisor /= 10;
            }
        }
        HuPrcVSleep();
    }
}

void func_8010A75C_parasol_plummet(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ) {
    CamSetupInit(1);
    D_8010AB50_parasol_plummet = CamSetupMapCullAdd();
    ScissorSet(D_8010AB50_parasol_plummet, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(D_8010AB50_parasol_plummet, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    CZoom = zoom;
    CRot.x = rotX;
    CRot.y = rotY;
    CRot.z = rotZ;
    Center.x = centerX;
    Center.y = centerY;
    Center.z = centerZ;
    Hu3DCameraPerspectiveSet(D_8010AB50_parasol_plummet, 30.0f, 80.0f, 8000.0f);
}
