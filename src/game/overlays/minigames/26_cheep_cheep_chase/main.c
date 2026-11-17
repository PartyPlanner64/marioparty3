#include "common.h"
#include "gcc/memory.h"
#include "game/hu3d.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/mallocblock.h"
#include "game/audio.h"
#include "game/camsetup.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmfcoll.h"
#include "game/hmfspr.h"
#include "game/wipe.h"
#include "math.h"
#include "game/overlays/minigame.h"

#define FUNC_GRP_MAX 8
#define FUNC_PRIO_MAX 10
#define SPRITES_MAX 0
#define ANIMMDL_MAX 40

typedef struct {
    /* 0x00 */ s8 s8[16];
    /* 0x10 */ s16 s16[8];
    /* 0x20 */ f32 f32[4];
} Work; // Size 0x30

typedef struct func_context {
    /* 0x00 */ s8 set;
    /* 0x01 */ s8 state;
    /* 0x04 */ void *data;
    /* 0x08 */ s16 param;
    /* 0x0A */ s8 prio;
    /* 0x0B */ s8 next;
    /* 0x0C */ Work work;
    /* 0x3C */ void (*func)(struct func_context *);
} FuncContext; // Size 0x40

typedef struct {
    /* 0x00 */ FuncContext *funcCtx;
    /* 0x04 */ s8 maxFuncs;
    /* 0x05 */ u8 sort;
    /* 0x06 */ s8 order[FUNC_PRIO_MAX];
} FuncGroup; // Size 0x10

#define SPRITE_STATE_NOTSET 0
#define SPRITE_STATE_INVISIBLE 1
#define SPRITE_STATE_VISIBLE 2

typedef struct {
    /* 0x00 */ s8 state;
    /* 0x01 */ u8 groupId;
    /* 0x02 */ u8 unk02;
    /* 0x04 */ u16 unk04;
} SpriteData; // Size 6

#define ANIMMDL_STATE_INVISIBLE -1
#define ANIMMDL_STATE_WAIT 0
#define ANIMMDL_STATE_ANIM 1

typedef struct {
    /* 0x00 */ s8 set;
    /* 0x04 */ s32 attr;
    /* 0x08 */ s8 state;
    /* 0x0A */ s16 modelId;
    /* 0x0C */ f32 freq;
    /* 0x10 */ f32 animTimer;
    /* 0x14 */ f32 animStart;
} AnimModelData; // Size 0x18

typedef struct {
    /* 0x00 */ s16 model;
    /* 0x02 */ char unk_02[0x2];
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 length;
} CheepCheepChaseSegment; // sizeof 0x10

typedef struct {
    /* 0x00 */ s16 model;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ char unk_06[0x2];
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
} CheepCheepChaseObstacle; // sizeof 0x10

typedef struct CheepCheepChaseGame {
    /* 0x00 */ CheepCheepChaseSegment *segments;
    /* 0x04 */ CheepCheepChaseObstacle *unk_04;
    /* 0x08 */ u8 *segmentOrder;
    /* 0x0C */ u8 *unk_0C;
    /* 0x10 */ omObjData *unk_10;
    /* 0x14 */ s16 zTick;
    /* 0x16 */ char unk_16[0x2];
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ s16 scaleIndex;
    /* 0x1E */ s16 xTick;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ char unk_26[0x2];
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ s16 unk_2C;
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ s16 unk_30;
} CheepCheepChaseGame; // sizeof 0x34

typedef struct {
    /* 0x00 */ u8 padId;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ char unk_02[0x2];
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ s8 unk_08;
    /* 0x09 */ char unk_09[0x7];
    /* 0x10 */ s8 updateMotion;
    /* 0x12 */ s16 motion;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ char unk_1E[0x2];
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ char unk_24[0x4];
} CheepCheepChasePlayer; // sizeof 0x28

typedef struct {
    /* 0x00 */ s16 model;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ f32 unk_04;
} CheepCheepChaseCheep; // sizeof 0x8

extern u8 omAllPauseF;
extern s32 omCharModelNoTbl[][6];

u8 m238_ctrlMode = 0;
f32 m238_waterScrollY = 0.0f;
f32 m238_floatAngle = 0.0f;
s16 m238_readyCnt = 0;
s16 m238_startPhase = 0;
s16 m238_startFrame = 0;
s16 m238_startTimer = 0;
s16 m238_resultPhase = 1;
s16 m238_drawPhase = 0;
s32 m238_winAnimTbl[8] = { 0x000200A5, 0x000300A5, 0x000700A5, 0x000400A5, 0x000500A5, 0x000600A5, 0x000800A5, 0x0009001C };
s16 m238_swallowF = 0;

CheepCheepChaseGame *m238_gameWork BSS;
CheepCheepChasePlayer *m238_playerTbl BSS;
CheepCheepChaseCheep *m238_cheepWork BSS;
u8 m238_cheepWorkPad[4] BSS; /* Unreferenced. */
f32 m238_laneTbl[4] BSS;
s16 m238_seNoTbl[8] BSS;
SpriteData *m238_sprTbl BSS;
AnimModelData *m238_animMdlTbl BSS;
FuncGroup *m238_funcGroupTbl BSS;

const s16 m238_fontMesTbl[] = { 0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0x0000 };

const s16 m238_fontMesTbl2[] = { 0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0x0000, 0x0000 };

const s16 m238_fontMesTbl3[] = { 0x8263, 0x8271, 0x8260, 0x8276, 0x0000, 0x0000 };

void m238_ObjectSetup(void);
void m238_WorkCreate(void);
void m238_ExitCheckObjMain(omObjData *object);
void m238_ExitWaitObjMain(omObjData *object);
void m238_ExitObjMain(omObjData *object);
void m238_CameraUpdate(void);
void m238_MainObjInit(omObjData *object);
void m238_MainObjMain(omObjData *object);
void m238_RiverObjInit(omObjData *object);
void m238_WaterObjInit(omObjData *object);
void m238_SideObjInit(omObjData *object);
void m238_ObstacleObjInit(omObjData *object);
void m238_PlayerObjInit(omObjData *object);
void m238_CheepObjInit(omObjData *object);
void m238_CameraViewInit(FuncContext *ctx);
void m238_RiverObjMain(omObjData *object);
void m238_StartExec(FuncContext *ctx);
void m238_RiverInit(FuncContext *ctx);
void m238_RiverUpdate(FuncContext *ctx);
void m238_RiverStartHide(FuncContext *ctx);
void m238_SystemCreate(void);
void m238_PlayerStateSet(CheepCheepChasePlayer *player, s16 motion, s8 updateMotion);
void m238_FinishSeFade(FuncContext *ctx);
void m238_SegmentPlace(u8 index);
void m238_ObstacleSwallowExec(FuncContext *ctx);
void m238_FuncGroupCreate(FuncGroup *group, s16 maxFuncs);
s16 m238_FuncSet(s8 groupId, s8 prio, s16 param, s8 state, void *data, void (*func)(FuncContext *), u8 sort, s8 execFunc);
void m238_FuncReset(s8 groupId, FuncContext *ctx);
void m238_FuncGroupUpdate(s8 groupId);
void m238_FuncGroupSort(FuncGroup *group);
s16 m238_AnimMdlCreate(s32 dir, s32 file, f32 freq, s32 arg3);
void m238_AnimMdlUpdate(void);
void m238_MdlVtxMorph(s16 model1, s16 model2, f32 t, s32 node1, s32 node2, s32 full);
u8 m238_LerpCalc(f32 *outPos, u8 *tickPtr, f32 posA, f32 posB, f32 numTicks);
void m238_WaterObjMain(omObjData *object);
void m238_WaterTilePlace(s32 arg0);
void m238_SidePlace(s32 arg0);
void m238_SideObjMain(omObjData *object);
void m238_ObstacleObjMain(omObjData *object);
void m238_ObstacleRowPlace(omObjData *object, s16 offset);
void m238_CheepObjMain(omObjData *object);
void m238_PlayerStunExec(FuncContext *ctx);
s16 m238_AnimMdlDispOn(s16 animModelId, f32 posX, f32 posY, f32 posZ, f32 rotX, f32 rotY, f32 rotZ, f32 scale, f32 animStart);
void m238_DrawExec(FuncContext *ctx);
void m238_PlayerGoalExec(FuncContext *ctx);
void m238_FuncGroupReset(s8 groupId);
void m238_CameraFollowUpdate(FuncContext *ctx);
void m238_CheepMorphUpdate(FuncContext *ctx);
void m238_CheepMotUpdate(FuncContext *ctx);
void m238_CheepEffUpdate(FuncContext *ctx);
void m238_CheepObstacleCheck(FuncContext *ctx);
void m238_PadClear(s32 arg0);
void m238_PlayerEffUpdate(FuncContext *ctx);
void m238_PlayerMotUpdate(FuncContext *ctx);
void m238_PlayerObstacleHit(FuncContext *ctx);
void m238_PlayerObjMain(omObjData *object);
void m238_GoalCheckUpdate(FuncContext *ctx);
void m238_PlayerDiveExec(FuncContext *ctx);
void m238_StartMdlPlay(FuncContext *ctx);
void m238_PlayerStartExec(FuncContext *ctx);
void m238_PlayerComInput(FuncContext *ctx);
void m238_PlayerComInputB(FuncContext *ctx);
void m238_PlayerInputUpdate(FuncContext *ctx);
void m238_PlayerInputUpdateB(FuncContext *ctx);
void m238_PlayerMove(FuncContext *ctx);
void m238_PlayerJumpUpdate(FuncContext *ctx);
void m238_CheepUpdate(FuncContext *ctx);

void m238_Executor(void) {
    m238_ObjectSetup();
}

void m238_ObjectSetup(void) {
    u8 camera;

    MapCollInit(50);
    Hu3DSprModelInit(0x20);
    omInitObjMan(50, 0);
    omGameSysInit();
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -56.0f, 50.0f, 56.0f);
    CamSetupInit(1);
    camera = CamSetupMapCullAdd();
    ScissorSet(camera, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camera, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 30.0f, 80.0f, 4000.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    m238_SystemCreate();
    m238_WorkCreate();
    m238_FuncSet(0, 0, -1, 0, NULL, m238_CameraViewInit, FALSE, FALSE);
    omAddObj(100, 0, 0, -1, m238_MainObjInit);
    omAddObj(1000, 0, 0, -1, m238_ExitCheckObjMain);
    GMesFontMesCreate(m238_fontMesTbl, 1);
    GMesFontMesCreate(m238_fontMesTbl2, 1);
    GMesFontMesCreate(m238_fontMesTbl3, 1);
}

void m238_WorkCreate(void) {
    s16 i;
    s16 j;

    m238_gameWork = HuMemAllocTag(sizeof(CheepCheepChaseGame), TAG_OVERLAY);
    memset(m238_gameWork, 0, sizeof(CheepCheepChaseGame));
    m238_gameWork->segments = HuMemAllocTag(6 * sizeof(CheepCheepChaseSegment), TAG_OVERLAY);
    memset(m238_gameWork->segments, 0, 6 * sizeof(CheepCheepChaseSegment));
    m238_gameWork->unk_04 = HuMemAllocTag(8 * sizeof(CheepCheepChaseObstacle), TAG_OVERLAY);
    memset(m238_gameWork->unk_04, 0, 8 * sizeof(CheepCheepChaseObstacle));
    m238_gameWork->segmentOrder = HuMemAllocTag(7, TAG_OVERLAY);
    memset(m238_gameWork->segmentOrder, 0, 7);
    m238_gameWork->unk_0C = HuMemAllocTag(7, TAG_OVERLAY);
    memset(m238_gameWork->unk_0C, 0, 7);
    m238_playerTbl = HuMemAllocTag(4 * sizeof(CheepCheepChasePlayer), TAG_OVERLAY);
    memset(m238_playerTbl, 0, 4 * sizeof(CheepCheepChasePlayer));
    m238_cheepWork = HuMemAllocTag(8, TAG_OVERLAY);
    memset(m238_cheepWork, 0, 8);
    for (i = 0; i < 4; i++) {
        m238_laneTbl[i] = rand16() % 4;
        for (j = 0; j < i; j++) {
            if (m238_laneTbl[j] == m238_laneTbl[i]) {
                i--;
                break;
            }
        }
    }
}

void m238_ExitCheckObjMain(omObjData *object) {
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        object->func = m238_ExitWaitObjMain;
    }
}

void m238_ExitWaitObjMain(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = m238_ExitObjMain;
    }
}

void m238_ExitObjMain(omObjData *object) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void m238_CameraUpdate(void) {
    if (CRot.x > 360.0f) {
        CRot.x -= 360.0f;
    } else if (CRot.x < 0.0f) {
        CRot.x += 360.0f;
    }
    if (CRot.y > 360.0f) {
        CRot.y -= 360.0f;
    } else if (CRot.y < 0.0f) {
        CRot.y += 360.0f;
    }
    m238_FuncGroupUpdate(0);
}

void m238_MainObjInit(omObjData *object) {
    s32 attr = 0x499;
    u8 i;

    omAddObj(10, 7, 0, -1, m238_RiverObjInit);
    omSetStatBit(omAddObj(10, 4, 0, -1, m238_WaterObjInit), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omAddObj(10, 3, 0, -1, m238_SideObjInit);
    omAddObj(10, 8, 0, -1, m238_ObstacleObjInit);
    MgPlayerParamReset();
    MgShadowAltSet(1);
    for (i = 0; i < 4; i++) {
        mgPlayerObjTbl[i] = omAddObj(200, 10, 44, -1, m238_PlayerObjInit);
    }
    omSetStatBit(omAddObj(300, 2, 2, -1, m238_CheepObjInit), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    for (i = 0; i < 18; i++) {
        m238_AnimMdlCreate(0x47, 5, 1.0f, attr);
    }
    for (i = 0; i < 4; i++) {
        m238_AnimMdlCreate(1, 0x13, 2.0f, attr);
    }
    for (i = 0; i < 8; i++) {
        m238_AnimMdlCreate(0x47, 7, 1.0f, attr);
    }
    for (i = 0; i < 8; i++) {
        m238_AnimMdlCreate(0x47, 6, 1.0f, attr);
    }
    m238_FuncSet(1, 0, -1, 0, NULL, m238_StartExec, TRUE, FALSE);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    object->func = m238_MainObjMain;
}

void m238_MainObjMain(omObjData *object) {
    m238_FuncGroupUpdate(1);
    m238_AnimMdlUpdate();
    m238_CameraUpdate();
}

void m238_RiverObjInit(omObjData *object) {
    s16 i;

    object->model[0] = m238_gameWork->segments[0].model = Hu3DModelRead(0x470000, 0x9D);
    object->model[1] = m238_gameWork->segments[1].model = Hu3DModelRead(0x470002, 0x9D);
    object->model[2] = m238_gameWork->segments[2].model = Hu3DModelRead(0x470001, 0x9D);
    for (i = 0; i < 3; i++) {
        object->model[i + 3] = m238_gameWork->segments[i + 3].model = Hu3DModelLink(object->model[2]);
    }
    object->model[6] = Hu3DModelRead(0x470008, 0x9D);
    m238_FuncSet(2, 0, object->model[6], 0, NULL, m238_RiverInit, FALSE, TRUE);
    m238_FuncSet(2, 1, -1, 0, NULL, m238_RiverUpdate, FALSE, TRUE);
    m238_FuncSet(2, 0, -1, 1, NULL, m238_RiverStartHide, TRUE, FALSE);
    object->func = m238_RiverObjMain;
}

void m238_RiverObjMain(omObjData *object) {
    m238_FuncGroupUpdate(2);
}

void m238_WaterObjInit(omObjData *object) {
    u16 i;

    object->model[0] = Hu3DModelRead(0x470003, 0x2009D);
    for (i = 1; i < 4; i++) {
        object->model[i] = Hu3DModelLink(object->model[0]);
    }
    Hu3DModelVtxBufMake(object->model[0]);
    object->trans.x = 0.0f;
    object->trans.z = -250.0f;
    object->trans.y = 110.0f;
    m238_gameWork->zTick++;
    for (i = 1; i < 4; i++) {
        m238_WaterTilePlace(object->model[i]);
    }
    object->func = m238_WaterObjMain;
}

void m238_WaterObjMain(omObjData *object) {
    HmfModel *model;
    s16 i;

    Hu3DModelTexScroll(object->model[0], 0.0f, m238_waterScrollY, 64, 64);
    if (omPauseChk() + omAllPauseF == 0) {
        m238_waterScrollY += m238_gameWork->unk_18;
    }
    for (i = 0; i < 4; i++) {
        model = &Hu3DData[object->model[i]];
        if (Center.z - 900.0f <= model->pos.z) {
            Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        if (Center.z + 1000.0f <= model->pos.z) {
            Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            if (i != 0) {
                m238_WaterTilePlace(object->model[i]);
            } else {
                object->trans.z = -250.0 - (m238_gameWork->zTick * 500.0);
                m238_gameWork->zTick++;
            }
        }
    }
}

void m238_SideObjInit(omObjData *object) {
    u16 i;

    object->model[0] = Hu3DModelRead(0x470009, 0x9D);
    for (i = 1; i < 3; i++) {
        object->model[i] = Hu3DModelLink(object->model[0]);
    }
    object->trans.x = -325.0f;
    object->trans.y = 200.0f;
    object->trans.z = -800.0f;
    m238_gameWork->xTick++;
    for (i = 1; i < 3; i++) {
        m238_SidePlace(object->model[i]);
    }
    m238_gameWork->unk_20 = Hu3DMotion[Hu3DData[object->model[0]].motId].unk02;
    object->func = m238_SideObjMain;
}

void m238_SideObjMain(omObjData *object) {
    HmfModel *model;
    s16 i;

    for (i = 0; i < 3; i++) {
        model = &Hu3DData[object->model[i]];
        if (model->pos.z >= Center.z - 800.0) {
            Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        if (model->pos.z >= Center.z + 700.0) {
            Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            if (i != 0) {
                m238_SidePlace(object->model[i]);
            } else {
                object->trans.z = 200.0 - (m238_gameWork->xTick * 1000.0);
                m238_gameWork->xTick++;
            }
        }
        if (Hu3DData[object->model[i]].motTime >= m238_gameWork->unk_20) {
            Hu3DData[object->model[i]].motTime = 0.0f;
        }
    }
}

void m238_ObstacleObjInit(omObjData *object) {
    u16 i;

    object->model[0] = m238_gameWork->unk_04[0].model = Hu3DModelRead(0x470004, 0x2008D);
    for (i = 1; i < 8; i++) {
        object->model[i] = m238_gameWork->unk_04[i].model = Hu3DModelLink(object->model[0]);
    }
    for (i = 0; i < 8; i++) {
        Hu3DModelScaleSet(object->model[i], 0.9f, 0.9f, 0.9f);
    }
    m238_ObstacleRowPlace(object, 0);
    m238_ObstacleRowPlace(object, 4);
    m238_gameWork->unk_10 = object;
    object->func = m238_ObstacleObjMain;
}

void m238_ObstacleObjMain(omObjData *object) {
    HmfModel *model;
    s16 i;

    for (i = 0; i < 8; i++) {
        model = &Hu3DData[object->model[i]];
        if (!m238_gameWork->unk_04[i].unk_03) {
            if (!m238_gameWork->unk_04[i].unk_02) {
                m238_floatAngle += 0.25f;
                if (m238_floatAngle > 180.0f) {
                    m238_floatAngle = 0.0f;
                }
                if (i == 0) {
                    object->trans.y = 105.0 - sindf(m238_floatAngle) * 20.0f * 5.0f * 0.1;
                } else {
                    model->pos.y = 105.0 - sindf(m238_floatAngle) * 20.0f * 5.0f * 0.1;
                }
                m238_gameWork->unk_04[i].unk_0C += 0.75f;
                if (m238_gameWork->unk_04[i].unk_0C >= 360.0f) {
                    m238_gameWork->unk_04[i].unk_0C -= 360.0f;
                }
                m238_gameWork->unk_04[i].unk_08 =
                    sindf(m238_gameWork->unk_04[i].unk_0C) * (m238_gameWork->unk_04[i].unk_04 * 15.0);
                if (i == 0) {
                    object->trans.z = -(m238_gameWork->unk_0C[m238_gameWork->unk_04[i].unk_04] * 100) +
                                      m238_gameWork->unk_04[i].unk_08;
                } else {
                    model->pos.z = -(m238_gameWork->unk_0C[m238_gameWork->unk_04[i].unk_04] * 100) +
                                   m238_gameWork->unk_04[i].unk_08;
                }
                if (Center.z - 1000.0f <= model->pos.z) {
                    Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                }
            } else {
                Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
        }
        if (Center.z + 700.0f <= model->pos.z) {
            Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            if (i == 0 || i == 4) {
                m238_ObstacleRowPlace(object, i);
            }
        }
    }
}

void m238_PlayerObjInit(omObjData *object) {
    s32 attr = 0x2A9;
    f32 chrTable[8] = { -0.2f, 0.1f, 0.0f, 0.0f, 0.0f, 0.1f, 0.0f, 0.0f };
    MgPlayerWork *data;
    s32 chr;
    s32 model;
    s32 motion;

    object->work[0] = mgPlayerObjNum;
    chr = GwPlayer[object->work[0]].chr;
    model = omCharModelNoTbl[chr][0];
    motion = omCharModelNoTbl[chr][2];
    MgPlayerCreate(object, model, motion, mgPlayerObjNum, attr, 0x2BD);
    object->model[9] = Hu3DModelRead(0x47000A, 0x2B9);
    Hu3DModelAttrSet(object->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(chr, 0), 1, 0);
    MgPlayerMotLoad(object, 1, CharMotionDataNumGet(chr, 1), 1, 0);
    MgPlayerMotLoad(object, 0x26, CharMotionDataNumGet(chr, 0xD), 1, 0);
    MgPlayerMotLoad(object, 0x27, CharMotionDataNumGet(chr, 0x3B), 1, 0);
    MgPlayerMotLoad(object, 0x28, CharMotionDataNumGet(chr, 0x3C), 1, 0);
    MgPlayerMotLoad(object, 0x2A, CharMotionDataNumGet(chr, 0x59), 1, 0);
    MgPlayerMotLoad(object, 0x2B, CharMotionDataNumGet(chr, 0x5D), 1, 0);
    MgPlayerMotLoad(object, 0xD, CharMotionDataNumGet(chr, 0x2F), 1, 999);
    Hu3DModelScaleSet(object->model[0], 0.7f, 0.7f, 0.7f);
    object->trans.x = 300.0 - (m238_laneTbl[mgPlayerObjNum] + 1.0f) * 120.0;
    object->trans.y = 1060.0f;
    object->trans.z = -600.0f;
    object->rot.y = 180.0f;
    MgPlayerMotSet(object, 0x2A);
    Hu3DModelPosSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    mgPlayerObjNum++;
    data = object->data;
    m238_playerTbl[object->work[0]].padId = data->unk57;
    m238_playerTbl[object->work[0]].unk_01 = 0;
    m238_playerTbl[object->work[0]].unk_04 = chrTable[GwPlayer[object->work[0]].chr] * 20.0f * 5.0f;
    m238_playerTbl[object->work[0]].unk_20 = Hu3DMotion[Hu3DData[object->model[9]].motId].unk02;
    m238_FuncSet(object->work[0] + 4, 9, object->model[0], 0, NULL, m238_PlayerMotUpdate, FALSE, FALSE);
    m238_FuncSet(object->work[0] + 4, 8, object->model[0], 1, NULL, m238_PlayerObstacleHit, TRUE, FALSE);
    object->func = m238_PlayerObjMain;
}

void m238_PlayerObjMain(omObjData *object) {
    FuncGroup *group = &m238_funcGroupTbl[object->work[0] + 4];
    FuncContext *ctx = group->funcCtx;
    s8 i;

    if (group->sort) {
        m238_FuncGroupSort(group);
    }
    for (i = 0; i < FUNC_PRIO_MAX; i++) {
        s8 funcId = group->order[i];

        while (funcId != -1) {
            group->funcCtx[funcId].work.s16[0] = object->work[0];
            group->funcCtx[funcId].func(&ctx[funcId]);
            funcId = group->funcCtx[funcId].next;
        }
    }
    MgPlayerMotUpdate(object);
}

void m238_CheepObjInit(omObjData *object) {
    s16 ctxId;

    object->model[1] = m238_cheepWork->model = Hu3DModelRead(0xA0086, 0x289);
    object->model[0] = Hu3DModelRead(0xA0087, 0x28D);
    object->motion[0] = Hu3DModelRead(0xA0088, 0x28D);
    Hu3DMotionModelSet(object->model[1], object->motion[0]);
    Hu3DMotionAttrSet(object->motion[0], 2, 2);
    Hu3DModelVtxBufMake(object->model[1]);
    Hu3DModelObjAttrSet(object->model[1], 0x20000, 0x20000);
    Hu3DModelObjAttrSet(object->model[0], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(object->model[1]);
    Hu3DModelRemakeStatic(object->model[0]);
    Hu3DModelDynamicFree(object->model[1]);
    Hu3DModelDynamicFree(object->model[0]);
    Hu3DModelScaleSet(object->model[1], 1.4f, 1.4f, 1.4f);
    Hu3DModelPosSet(object->model[1], 0.0f, 40.0f, 0.0f);
    Hu3DModelRotSet(object->model[1], 0.0f, 180.0f, 0.0f);
    ctxId = m238_FuncSet(3, 7, -1, 0, NULL, m238_CheepMorphUpdate, FALSE, FALSE);
    m238_funcGroupTbl[3].funcCtx[ctxId].work.s16[0] = object->model[1];
    m238_funcGroupTbl[3].funcCtx[ctxId].work.s16[1] = object->model[0];
    m238_FuncSet(3, 8, object->model[1], 0, NULL, m238_CheepMotUpdate, FALSE, TRUE);
    m238_FuncSet(3, 9, object->model[1], 1, NULL, m238_CheepEffUpdate, FALSE, FALSE);
    m238_FuncSet(3, 1, object->model[1], 1, NULL, m238_CheepObstacleCheck, TRUE, FALSE);
    object->func = m238_CheepObjMain;
}

void m238_CheepObjMain(omObjData *object) {
    m238_FuncGroupUpdate(3);
}

void m238_CameraViewInit(FuncContext *ctx) {
    if (ctx->state == 0) {
        Center.x = -26.0f;
        Center.y = 327.0f;
        Center.z = -485.0f;
        CRot.x = 320.0f;
        CRot.y = 180.0f;
        CRot.z = 0.0f;
        CZoom = 1670.0f;
        m238_FuncReset(0, ctx);
    }
}

void m238_CameraDebugPad(FuncContext *ctx) {
    u16 buttons;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 1;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->state = 1;
            break;
        case 1:
            if (ctx->work.s8[1] != 0) {
                if (ctx->work.s8[1] == 1) {
                    sprintf(omDBGStrBuf, "C: TRANSLATE ADD: %d", ctx->work.s8[0]);
                } else {
                    sprintf(omDBGStrBuf, "C: ROTATE");
                }
                print8(16, 56, omDBGStrBuf);
                sprintf(omDBGStrBuf, "CZOOMM %.2f", CZoom);
                print8(16, 64, omDBGStrBuf);
                sprintf(omDBGStrBuf, "CCENTER_X %.2f Y %.2f Z %.2f", Center.x, Center.y, Center.z);
                print8(16, 72, omDBGStrBuf);
                sprintf(omDBGStrBuf, "CROTATE_X %.2f Y %.2f Z %.2f", CRot.x, CRot.y, CRot.z);
                print8(16, 80, omDBGStrBuf);
            }
            buttons = HuPadBtn[0];
            if (HuPadBtnDown[0] & Z_TRIG) {
                ctx->work.s8[1]++;
            }
            if (ctx->work.s8[1] >= 3) {
                ctx->work.s8[1] = 0;
            }
            if (ctx->work.s8[1] == 1) {
                if (buttons & D_JPAD) {
                    Center.z += ctx->work.s8[0];
                }
                if (buttons & L_JPAD) {
                    Center.x += ctx->work.s8[0];
                }
                if (buttons & U_JPAD) {
                    Center.z -= ctx->work.s8[0];
                }
                if (buttons & R_JPAD) {
                    Center.x -= ctx->work.s8[0];
                }
                if (buttons & U_CBUTTONS) {
                    Center.y += ctx->work.s8[0];
                }
                if (buttons & D_CBUTTONS) {
                    Center.y -= ctx->work.s8[0];
                }
                if (ctx->work.s8[2] == 15) {
                    ctx->work.s8[2] = 0;
                    if (buttons & A_BUTTON) {
                        ctx->work.s8[0]++;
                    }
                    if (buttons & B_BUTTON) {
                        ctx->work.s8[0]--;
                    }
                    if (ctx->work.s8[0] >= 125) {
                        ctx->work.s8[0] = 0;
                    }
                } else {
                    ctx->work.s8[2]++;
                }
            } else if (ctx->work.s8[1] == 2) {
                if (buttons & D_JPAD) {
                    CRot.x += 1.0f;
                }
                if (buttons & U_JPAD) {
                    CRot.x -= 1.0f;
                }
                if (buttons & L_JPAD) {
                    CRot.y -= 1.0f;
                }
                if (buttons & R_JPAD) {
                    CRot.y += 1.0f;
                }
                if (buttons & U_CBUTTONS) {
                    CZoom += 10.0f;
                }
                if (buttons & D_CBUTTONS) {
                    CZoom -= 10.0f;
                }
            }
            break;
    }
}

void m238_CameraStartMove(FuncContext *ctx) {
    f32 t;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->state = 1;
            break;
        case 1:
            t = ctx->work.s8[0] * 0.025f * 90.0f;
            t = sindf(t);
            CZoom = t * 230.0f + 1670.0f;
            Center.x = t * -244.0f + -26.0f;
            Center.y = t * -343.0f + 327.0f;
            Center.z = t * 30.0f + -485.0f;
            CRot.x = t * -5.0f + 320.0f;
            CRot.y = t * -90.0f + 180.0f;
            if (++ctx->work.s8[0] > 40.0f) {
                CZoom = 1900.0f;
                Center.x = -270.0f;
                Center.y = -16.0f;
                Center.z = -455.0f;
                CRot.x = 315.0f;
                CRot.y = 90.0f;
                m238_FuncReset(0, ctx);
                m238_FuncSet(0, 2, -1, 0, NULL, m238_CameraFollowUpdate, FALSE, FALSE);
            }
            break;
    }
}

void m238_CameraWinMove(FuncContext *ctx) {
    omObjData *object = mgPlayerObjTbl[0];
    CheepCheepChasePlayer *player = m238_playerTbl;
    s16 i;
    f32 t;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            for (i = 0; i < 4; i++, object++, player++) {
                if (player->unk_01 == 6) {
                    ctx->work.f32[0] = object->trans.x - 450.0;
                    ctx->work.f32[1] = object->trans.z - 80.0;
                }
            }
            ctx->state = 1;
            break;
        case 1:
            t = ctx->work.s8[0] * 0.025f * 90.0f;
            t = sindf(t);
            CZoom = t * -770.0f + 1900.0f;
            Center.x = (ctx->work.f32[0] - -270.0f) * t + -270.0f;
            Center.y = t * 101.0f + -16.0f;
            Center.z = (ctx->work.f32[1] - -455.0f) * t + -455.0f;
            CRot.x = t * 25.0f + 315.0f;
            CRot.y = t * 31.0f + 90.0f;
            if (++ctx->work.s8[0] > 40.0f) {
                CZoom = 1130.0f;
                Center.x = ctx->work.f32[0];
                Center.y = 85.0f;
                Center.z = ctx->work.f32[1];
                CRot.x = 340.0f;
                CRot.y = 121.0f;
                m238_FuncReset(0, ctx);
            }
            break;
    }
}

void m238_CameraFollowUpdate(FuncContext *ctx) {
    s16 i;

    switch (ctx->state) {
        case 0:
            ctx->work.f32[0] = Center.z;
            ctx->state = 1;
            break;
        case 1:
            for (i = 0; i < 4; i++) {
                if (mgPlayerObjTbl[i]->trans.z + 255.0f < ctx->work.f32[0]) {
                    ctx->work.f32[0] = mgPlayerObjTbl[i]->trans.z + 255.0f;
                }
            }
            Center.z = ctx->work.f32[0];
            break;
        case 2:
            break;
    }
}

void m238_StartExec(FuncContext *ctx) {
    omObjData *object = mgPlayerObjTbl[0];
    s16 i;

    if (m238_readyCnt >= 4) {
        HuAudSeqPlay(0x34);
    }
    switch (ctx->state) {
        case 0:
            m238_seNoTbl[0] = HuAudFXPlay(0x433);
            ctx->work.s16[0] = 0;
            ctx->state = 1;
            break;
        case 1:
            switch (ctx->work.s16[0]++) {
                case 10:
                    for (i = 0; i < 4; i++, object++) {
                        m238_FuncSet(i + 4, 0, object->model[0], 0, NULL, m238_PlayerDiveExec, FALSE, FALSE);
                    }
                    break;
                case 80:
                    m238_FuncSet(2, 0, m238_gameWork->unk_24, 0, NULL, m238_StartMdlPlay, FALSE, FALSE);
                    break;
                case 90:
                    object = mgPlayerObjTbl[0];
                    for (i = 0; i < 4; i++, object++) {
                        m238_FuncSet(i + 4, 4, object->model[0], 0, NULL, m238_PlayerStartExec, FALSE, FALSE);
                    }
                    break;
                case 70:
                    m238_FuncSet(0, 0, -1, 0, NULL, m238_CameraStartMove, FALSE, FALSE);
                    break;
                case 110:
                    GMesCreate(GMES_MES_3);
                    HuAudFXPlay(0xE);
                    m238_startPhase = 1;
                    break;
                default:
                    if (m238_startPhase == 1) {
                        if (++m238_startTimer > 60) {
                            for (i = 0; i < 4; i++, object++) {
                                if (GwPlayer[object->work[0]].stat & 1) {
                                    if (m238_ctrlMode == 0) {
                                        m238_FuncSet(i + 4, 0, object->model[0], 0, NULL, m238_PlayerComInput, FALSE, FALSE);
                                    } else {
                                        m238_FuncSet(i + 4, 0, object->model[0], 0, NULL, m238_PlayerComInputB, FALSE, FALSE);
                                    }
                                }
                                if (m238_ctrlMode == 0) {
                                    m238_FuncSet(i + 4, 1, object->model[0], 0, NULL, m238_PlayerInputUpdate, FALSE, FALSE);
                                } else {
                                    m238_FuncSet(i + 4, 1, object->model[0], 0, NULL, m238_PlayerInputUpdateB, FALSE, FALSE);
                                }
                                m238_FuncSet(i + 4, 2, object->model[0], 0, NULL, m238_PlayerMove, FALSE, FALSE);
                                m238_FuncSet(i + 4, 3, object->model[0], 0, NULL, m238_PlayerJumpUpdate, FALSE, FALSE);
                            }
                            m238_startFrame = ctx->work.s16[0] + 10;
                            m238_startPhase = 2;
                        }
                    } else if (m238_startPhase == 2) {
                        if (ctx->work.s16[0] >= m238_startFrame) {
                            m238_FuncSet(3, 0, m238_cheepWork->model, 0, NULL, m238_CheepUpdate, FALSE, FALSE);
                            m238_FuncReset(1, ctx);
                            m238_FuncSet(1, 0, -1, 1, NULL, m238_GoalCheckUpdate, FALSE, FALSE);
                        }
                    }
                    break;
            }
            break;
    }
}

void m238_GoalCheckUpdate(FuncContext *ctx) {
    omObjData *object = mgPlayerObjTbl[0];
    CheepCheepChasePlayer *player = m238_playerTbl;
    s16 caughtCount = 0;
    s16 caught[4] = { -1, -1, -1, -1 };
    s16 index;
    s16 i;

    switch (ctx->state) {
        case 0:
            break;
        case 1:
            if (m238_gameWork->unk_2E == 4) {
                m238_FuncGroupReset(1);
                m238_FuncSet(1, 0, -1, 0, NULL, m238_DrawExec, FALSE, TRUE);
                break;
            }
            if (m238_gameWork->unk_30 == 4) {
                break;
            }
            if (m238_gameWork->unk_28 != 0.0f) {
                for (i = 0; i < 4; i++, object++) {
                    if (object->trans.z < m238_gameWork->unk_28 - 350.0) {
                        caught[caughtCount++] = i;
                    }
                }
            }
            if (caughtCount == 0) {
                break;
            }
            index = rand16() % caughtCount;
            for (i = 0; i < 4; i++, player++) {
                if (player->unk_01 == 4) {
                    continue;
                }
                if (i == caught[index]) {
                    m238_gameWork->unk_2C = i;
                    player->unk_01 = 6;
                } else {
                    player->unk_01 = 7;
                }
                m238_FuncGroupReset(i + 4);
                m238_FuncSet(i + 4, 0, object->model[0], 0, NULL, m238_PlayerGoalExec, FALSE, FALSE);
            }
            m238_FuncReset(1, ctx);
            HuAudSeqFadeOut(120);
            GMesCreate(GMES_MES_14);
            m238_FuncSet(1, 0, -1, 0, NULL, m238_FinishSeFade, FALSE, TRUE);
            m238_gameWork->unk_18 = 0.4f;
            break;
    }
}

void m238_FinishSeFade(FuncContext *ctx) {
    if (ctx->state == 0) {
        ctx->work.s16[0] = 0;
        ctx->state = 1;
    }
    if (++ctx->work.s16[0] >= 16) {
        ctx->work.s16[0] = 15;
        HuAudFXFadeOut(m238_seNoTbl[0], 15);
        m238_FuncReset(1, ctx);
    }
}

void m238_WinExec(FuncContext *ctx) {
    switch (ctx->state) {
        case 0:
            ctx->work.s16[0] = 0;
            ctx->state = 1;
            break;
        case 1:
            if (m238_resultPhase >= 2) {
                if (GMesStatGet() == 0) {
                    m238_resultPhase = 3;
                }
                if (m238_resultPhase == 3) {
                    if (++ctx->work.s16[0] >= 15) {
                        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                        ctx->state = 2;
                    }
                }
            } else {
                if ((u16)ctx->work.s16[0]++ == 0) {
                    GMesCreate(GMES_MES_MG_WINNER, GwPlayer[m238_gameWork->unk_2C].chr);
                    HuAudSeqPlay(0x65);
                    GwPlayer[m238_gameWork->unk_2C].bonusCoin += 10;
                }
                if (GMesStatGet() != 0) {
                    ctx->work.s16[0] = 0;
                    m238_resultPhase = 2;
                }
            }
            break;
        case 2:
            if (WipeStatGet() == 0) {
                omOvlReturnEx(1);
            }
            break;
    }
}

void m238_DrawExec(FuncContext *ctx) {
    if (m238_drawPhase == 1 && GMesStatGet() == 0) {
        ctx->state = 99;
        ctx->work.s16[0] = 0;
        m238_drawPhase = 2;
    }
    switch (ctx->state) {
        case 0:
            ctx->work.s16[0] = 0;
            ctx->state = 1;
            break;
        case 1:
            switch (ctx->work.s16[0]++) {
                case 0:
                    HuAudSeqFadeOut(120);
                    GMesCreate(GMES_MES_14);
                    m238_FuncSet(1, 0, -1, 0, NULL, m238_FinishSeFade, FALSE, TRUE);
                    ctx->state = 3;
                    break;
                case 15:
                    GMesCreate(GMES_MES_MG_DRAW);
                    HuAudSeqPlay(0x6C);
                    m238_drawPhase = 1;
                    break;
            }
            break;
        case 2:
            if (WipeStatGet() == 0) {
                omOvlReturnEx(1);
            }
            break;
        case 3:
            if (GMesStatGet() == 0) {
                ctx->state = 1;
            }
            break;
        case 99:
            if (++ctx->work.s16[0] == 15) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                ctx->state = 2;
            }
            break;
    }
}

void m238_RiverInit(FuncContext *ctx) {
    s16 i;

    if (ctx->state == 0) {
        m238_gameWork->segments[0].unk_04 = 1200.0f;
        m238_gameWork->segments[0].unk_08 = 600.0f;
        m238_gameWork->segments[0].length = 1000.0f;
        m238_gameWork->segments[1].unk_04 = 1200.0f;
        m238_gameWork->segments[1].unk_08 = 600.0f;
        m238_gameWork->segments[1].length = 1000.0f;
        for (i = 0; i < 4; i++) {
            m238_gameWork->segments[i + 2].unk_04 = 1200.0f;
            m238_gameWork->segments[i + 2].unk_08 = 600.0f;
            m238_gameWork->segments[i + 2].length = 1000.0f;
        }
        m238_gameWork->zTick = 0;
        m238_gameWork->xTick = 0;
        m238_gameWork->scaleIndex = 0;
        m238_gameWork->unk_28 = 0.0f;
        m238_gameWork->unk_18 = 0.4f;
        m238_gameWork->unk_2C = -1;
        m238_gameWork->unk_2E = 0;
        m238_gameWork->unk_30 = 0;
        m238_gameWork->segmentOrder[0] = 0;
        m238_gameWork->segmentOrder[1] = 2;
        m238_gameWork->segmentOrder[2] = 3;
        m238_gameWork->segmentOrder[3] = 4;
        m238_gameWork->segmentOrder[4] = 5;
        m238_gameWork->segmentOrder[5] = 2;
        m238_gameWork->segmentOrder[6] = 1;
        for (i = 0; i < 5; i++) {
            m238_SegmentPlace(i);
        }
        m238_SegmentPlace(6);
        m238_gameWork->unk_0C[0] = 10;
        m238_gameWork->unk_0C[1] = 18;
        m238_gameWork->unk_0C[2] = 28;
        m238_gameWork->unk_0C[3] = 32;
        m238_gameWork->unk_0C[4] = 40;
        m238_gameWork->unk_0C[5] = 47;
        m238_gameWork->unk_0C[6] = 56;
        m238_gameWork->unk_24 = ctx->param;
        Hu3DModelScaleSet(ctx->param, 1.4f, 1.4f, 1.4f);
        Hu3DModelPosSet(ctx->param, 0.0f, -100.0f, 0.0f);
        Hu3DModelAttrSet(ctx->param, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DData[ctx->param].motSpeed = 0.0f;
        Hu3DData[ctx->param].motTime = 0.0f;
        m238_FuncReset(2, ctx);
    }
}

void m238_RiverUpdate(FuncContext *ctx) {
    CheepCheepChaseSegment *segment = &m238_gameWork->segments[1];
    HmfModel *model;
    s16 i;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 5;
            ctx->state = 1;
            break;
        case 1:
            for (i = 1; i < 6; i++, segment++) {
                model = &Hu3DData[segment->model];
                if (Center.z - 700.0f <= model->pos.z) {
                    Hu3DModelAttrSet(segment->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                }
                if (Center.z + 1700.0f <= model->pos.z) {
                    Hu3DModelAttrSet(segment->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    if (i >= 2 && ctx->work.s8[0] < 7) {
                        m238_SegmentPlace(ctx->work.s8[0]++);
                    }
                }
            }
            break;
        case 2:
            break;
    }
}

void m238_RiverStartHide(FuncContext *ctx) {
    CheepCheepChaseSegment *segment = m238_gameWork->segments;
    HmfModel *model = &Hu3DData[segment->model];

    switch (ctx->state) {
        case 0:
            break;
        case 1:
            if (Center.z - 700.0f <= model->pos.z) {
                Hu3DModelAttrSet(segment->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            if (model->pos.z >= Center.z + 1700.0f + 400.0) {
                Hu3DModelAttrSet(segment->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                m238_FuncReset(2, ctx);
                Hu3DModelAttrSet(m238_gameWork->unk_24, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            break;
        case 2:
            break;
    }
}

void m238_SegmentPlace(u8 index) {
    f32 z = 0.0f;
    CheepCheepChaseSegment *segment;
    s16 i;

    if (index != 0) {
        for (i = 0; i < index; i++) {
            segment = &m238_gameWork->segments[m238_gameWork->segmentOrder[i]];
            z -= segment->length;
        }
    }
    segment = &m238_gameWork->segments[m238_gameWork->segmentOrder[index]];
    if (m238_gameWork->segmentOrder[index] == 1) {
        m238_gameWork->unk_28 = z;
    }
    Hu3DModelPosSet(segment->model, 0.0f, 0.0f, z);
}

void m238_StartMdlPlay(FuncContext *ctx) {
    HmfModel *model = &Hu3DData[ctx->param];

    switch (ctx->state) {
        case 0:
            HuAudFXPlay(0x435);
            ctx->work.f32[0] = Hu3DMotion[Hu3DData[ctx->param].motId].unk02 - 1.0f;
            model->motSpeed = 1.0f;
            ctx->state = 1;
            break;
        case 1:
            if (Hu3DData[ctx->param].motTime >= ctx->work.f32[0]) {
                m238_FuncReset(2, ctx);
            }
            break;
    }
}

void m238_WaterTilePlace(s32 arg0) {
    Hu3DModelPosSet(arg0, 0.0f, 110.0f, -250.0 - (m238_gameWork->zTick * 500.0));
    m238_gameWork->zTick++;
}

void m238_SidePlace(s32 arg0) {
    Hu3DModelPosSet(arg0, -325.0f, 200.0f, 200.0 - (m238_gameWork->xTick * 1000.0));
    m238_gameWork->xTick++;
}

void m238_ObstacleRowPlace(omObjData *object, s16 offset) {
    s16 i;

    if (m238_gameWork->scaleIndex < 7) {
        for (i = 0; i < 4; i++) {
            if (offset + i == 0) {
                object->trans.x = 300.0 - (i + 1) * 120.0;
                object->trans.y = 110.0f;
                object->trans.z = -(m238_gameWork->unk_0C[m238_gameWork->scaleIndex] * 100);
            } else {
                Hu3DModelPosSet(object->model[offset + i], 300.0 - (i + 1) * 120.0, 110.0f,
                                -(m238_gameWork->unk_0C[m238_gameWork->scaleIndex] * 100));
            }
            m238_gameWork->unk_04[offset + i].unk_04 = m238_gameWork->scaleIndex;
            m238_gameWork->unk_04[offset + i].unk_02 = 0;
            m238_gameWork->unk_04[offset + i].unk_03 = 0;
            m238_gameWork->unk_04[offset + i].unk_05 = 0;
            m238_gameWork->unk_04[offset + i].unk_0C = rand16() % 361;
        }
        m238_gameWork->scaleIndex++;
    }
}

void m238_PlayerDiveExec(FuncContext *ctx) {
    omObjData *object = mgPlayerObjTbl[ctx->work.s16[0]];
    f32 chrTable[8] = { 65.0f, 58.0f, 45.0f, 60.0f, 84.0f, 102.0f, 44.0f, 45.0f };
    f32 accel;
    f32 x;
    f32 z;
    s16 start;
    s16 i;
    s16 j;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.f32[1] = object->trans.y = 1060.0f;
            ctx->work.f32[2] = 0.0f;
            MgPlayerMotSet(object, 0x2A);
            CharFXPlay(0xB8, GwPlayer[object->work[0]].chr);
            ctx->state = 1;
            break;
        case 1:
            switch (ctx->work.s8[0]) {
                case 0:
                    ctx->work.f32[2] += 0.1;
                    accel = chrTable[GwPlayer[object->work[0]].chr] * -9.8f;
                    object->trans.y = accel * 0.5 * ctx->work.f32[2] * ctx->work.f32[2] + ctx->work.f32[1];
                    if (object->trans.y <= 60.0) {
                        CharFXPlay(0x70, GwPlayer[object->work[0]].chr);
                        ctx->work.s8[0] = 1;
                        ctx->work.f32[2] = 0.0f;
                        for (i = 0; i < 2; i++) {
                            x = ((rand16() % 9) - 4) * 0.1;
                            z = ((rand16() % 9) - 4) * 0.1;
                            start = 30;
                            for (j = start; j < start + 18; j++) {
                                if (m238_AnimMdlDispOn(j, x * 100.0f + object->trans.x, 160.0f, z * 100.0f + object->trans.z, 0.0f, 90.0f, 0.0f, 1.0f, i) != 0) {
                                    break;
                                }
                            }
                        }
                    }
                    break;
                case 1:
                    if (ctx->work.f32[2] >= 90.0f) {
                        ctx->work.f32[2] += 5.0f;
                    } else {
                        ctx->work.f32[2] += 10.0f;
                    }
                    accel = chrTable[GwPlayer[object->work[0]].chr] * -9.8f;
                    object->trans.y = sindf(ctx->work.f32[2]) * accel * 0.15f;
                    if (object->trans.y >= m238_playerTbl[object->work[0]].unk_04 + 60.0) {
                        ctx->work.s8[0] = 2;
                        ctx->work.f32[2] = 0.0f;
                        CharFXPlay(0x82, GwPlayer[object->work[0]].chr);
                        object->trans.y = m238_playerTbl[object->work[0]].unk_04 + 60.0;
                    }
                    break;
            }
            if (ctx->work.s8[0] == 2) {
                MgPlayerMotSet(object, 0x26);
                m238_FuncReset(ctx->work.s16[0] + 4, ctx);
            }
            break;
    }
}

void m238_PlayerStartExec(FuncContext *ctx) {
    omObjData *object = mgPlayerObjTbl[ctx->work.s16[0]];
    f32 scale = 0.0f;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->work.s8[3] = 0;
            ctx->state = 1;
            break;
        case 1:
            switch (ctx->work.s8[0]) {
                case 0:
                    MgPlayerMotSet(object, 0x2B);
                    ctx->work.s8[0] = 1;
                    break;
                case 1:
                    if (++ctx->work.s8[1] > 7.0f) {
                        if (ctx->work.s16[4] == 0) {
                            omVibrate(ctx->work.s16[0], 10, 0, 10);
                            ctx->work.s16[4] = 1;
                        }
                        switch (ctx->work.s8[3]) {
                            case 0:
                                if (m238_LerpCalc(&scale, (u8 *)&ctx->work.s8[2], 1.2f, 2.5f, 3.0f)) {
                                    ctx->work.s8[2] = 0;
                                    ctx->work.s8[3] = 1;
                                }
                                Hu3DModelAttrSet(object->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                                break;
                            case 1:
                                if (m238_LerpCalc(&scale, (u8 *)&ctx->work.s8[2], 2.5f, 0.8f, 3.0f)) {
                                    Hu3DData[object->model[0]].motSpeed = 0.75f;
                                    ctx->work.s8[2] = 0;
                                    ctx->work.s8[3] = 2;
                                    Hu3DModelAttrSet(object->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                                    m238_readyCnt++;
                                }
                                break;
                        }
                        Hu3DModelPosSet(object->model[9], object->trans.x - 10.0, object->trans.y + 200.0, object->trans.z - 30.0);
                        Hu3DModelScaleSet(object->model[9], scale, scale, scale);
                        Hu3DData[object->model[9]].rot.y = CRot.y - 90.0f;
                    }
                    break;
            }
            if (ctx->work.s8[1]++ > 40.0f) {
                ctx->work.s8[0] = 2;
            }
            if (ctx->work.s8[0] == 2) {
                m238_PlayerStateSet(&m238_playerTbl[object->work[0]], 0x26, TRUE);
                Hu3DData[object->model[0]].motSpeed = 1.0f;
                Hu3DData[object->model[9]].rot.y = 0.0f;
                m238_FuncReset(ctx->work.s16[0] + 4, ctx);
                m238_FuncSet(object->work[0] + 4, 4, object->model[0], 0, NULL, m238_PlayerEffUpdate, FALSE, FALSE);
            }
            break;
    }
}

void m238_PlayerGoalExec(FuncContext *ctx) {
    omObjData *object = mgPlayerObjTbl[ctx->work.s16[0]];
    CheepCheepChasePlayer *player = &m238_playerTbl[ctx->work.s16[0]];

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->work.s8[3] = 0;
            ctx->work.s8[4] = 0;
            ctx->work.f32[0] = object->trans.z;
            ctx->work.f32[1] = object->trans.x;
            Hu3DModelAttrSet(object->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            ctx->state = 1;
            break;
        case 1:
            switch (player->unk_01) {
                case 7:
                    MgPlayerMotSet(object, 0x2A);
                    object->trans.z += 5.0;
                    ctx->work.s8[0] += 0.5;
                    if (ctx->work.s8[0] >= 180.0f) {
                        ctx->work.s8[0] -= 180.0f;
                    }
                    object->trans.y = sindf(ctx->work.s8[0]) * 20.0f * 5.0f * 0.05f + 80.0;
                    break;
                case 6:
                    if (++ctx->work.s8[3] >= 5) {
                        MgPlayerMotSet(object, 1);
                        if (Hu3DData[object->model[0]].motTime == 0.0f) {
                            CharFXPlay(0x1F, GwPlayer[object->work[0]].chr);
                        }
                        if (ctx->work.s8[2] == 0) {
                            if (m238_LerpCalc(&object->trans.y, (u8 *)&ctx->work.s8[0], player->unk_04 + 60.0, 210.0f, 20.0f)) {
                                ctx->work.s8[2] = 1;
                            }
                        }
                        if (m238_LerpCalc(&object->trans.z, (u8 *)&ctx->work.s8[1], ctx->work.f32[0], m238_gameWork->unk_28 - 700.0, 70.0f)) {
                            ctx->work.s8[1] = 70;
                        }
                        if (m238_LerpCalc(&object->trans.x, (u8 *)&ctx->work.s8[4], ctx->work.f32[1], 0.0f, 70.0f)) {
                            MgPlayerMotSet(object, 0);
                            ctx->state = 2;
                            m238_FuncSet(0, 0, -1, 0, NULL, m238_CameraWinMove, FALSE, FALSE);
                            ctx->work.s8[1] = 0;
                        }
                    }
                    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y - 5.0f, object->trans.z);
                    break;
            }
            break;
        case 2:
            if (m238_LerpCalc(&object->rot.y, (u8 *)&ctx->work.s8[1], 180.0f, 121.0f, 40.0f)) {
                ctx->state = 3;
                ctx->work.s8[1] = 0;
            }
            break;
        case 3:
            if (++ctx->work.s8[1] >= 6) {
                s16 playerNo = ctx->work.s16[0];
                s32 dataNum = m238_winAnimTbl[GwPlayer[playerNo].chr];

                CharAnimCreate(object->model[0], 2, GwPlayer[playerNo].chr, dataNum);
                m238_FuncReset(ctx->work.s16[0] + 4, ctx);
                MgPlayerMotSet(object, 0xD);
                HuAudCharVoicePlay(omCharModelNoTbl[GwPlayer[playerNo].chr][0] | 0x2F);
                m238_FuncSet(1, 0, -1, 0, NULL, m238_WinExec, FALSE, FALSE);
            }
            break;
    }
}

void m238_PlayerComInput(FuncContext *ctx) {
    omObjData *object = mgPlayerObjTbl[ctx->work.s16[0]];
    CheepCheepChasePlayer *player = &m238_playerTbl[ctx->work.s16[0]];
    s16 found = FALSE;
    CheepCheepChaseObstacle *item;
    s16 i;

    switch (ctx->state) {
        case 0:
            switch (GwPlayer[object->work[0]].cpu_difficulty) {
                case 0:
                    ctx->work.s8[0] = 2;
                    ctx->work.s8[2] = 3;
                    break;
                case 1:
                    ctx->work.s8[0] = 1;
                    ctx->work.s8[2] = 3;
                    break;
                case 2:
                    ctx->work.s8[0] = 0;
                    ctx->work.s8[2] = 3;
                    break;
                case 3:
                    ctx->work.s8[0] = 0;
                    ctx->work.s8[2] = 2;
                    break;
            }
            ctx->work.s8[1] = 0;
            ctx->work.s8[3] = rand16() % (ctx->work.s8[2] + 1);
            ctx->state = 1;
            break;
        case 1:
            if (player->unk_01 == 3) {
                break;
            }
            m238_PadClear(player->padId);
            for (i = 0; i < 2; i++) {
                item = &m238_gameWork->unk_04[i * 4 + (s16)m238_laneTbl[ctx->work.s16[0]]];
                if (item->unk_05 != 0 || (Hu3DData[item->model].attr & HU3D_ATTR_DISPOFF)) {
                    continue;
                }
                if (ctx->work.s8[0] == 0) {
                    if (-(m238_gameWork->unk_0C[item->unk_04] * 100) + item->unk_08 + 140.0 > object->trans.z) {
                        found = TRUE;
                        item->unk_05 = 1;
                    }
                } else {
                    if (-(m238_gameWork->unk_0C[item->unk_04] * 100) + 140.0 > object->trans.z) {
                        found = TRUE;
                        item->unk_05 = 1;
                    }
                }
            }
            if (found) {
                HuPadBtn[player->padId] = B_BUTTON;
                break;
            }
            if (ctx->work.s8[1]++ > ctx->work.s8[0] + ctx->work.s8[3]) {
                ctx->work.s8[1] = 0;
                ctx->work.s8[3] = rand16() % (ctx->work.s8[2] + 1);
                ((u16 *)HuPadBtn)[player->padId] = A_BUTTON;
            } else {
                HuPadBtn[player->padId] = 0;
            }
            break;
        case 2:
            break;
    }
}

void m238_PlayerComInputB(FuncContext *ctx) {
    omObjData *object = mgPlayerObjTbl[ctx->work.s16[0]];
    CheepCheepChasePlayer *player = &m238_playerTbl[ctx->work.s16[0]];
    s16 found = FALSE;
    CheepCheepChaseObstacle *item;
    s16 i;

    switch (ctx->state) {
        case 0:
            switch (GwPlayer[object->work[0]].cpu_difficulty) {
                case 0:
                    ctx->work.s8[0] = 3;
                    ctx->work.s8[2] = 3;
                    break;
                case 1:
                    ctx->work.s8[0] = 2;
                    ctx->work.s8[2] = 3;
                    break;
                case 2:
                    ctx->work.s8[0] = 1;
                    ctx->work.s8[2] = 3;
                    break;
                case 3:
                    ctx->work.s8[0] = 0;
                    ctx->work.s8[2] = 3;
                    break;
            }
            ctx->work.s8[1] = 0;
            ctx->work.s8[3] = rand16() % (ctx->work.s8[2] + 1);
            ctx->state = 1;
            break;
        case 1:
            if (player->unk_01 == 3) {
                break;
            }
            m238_PadClear(player->padId);
            for (i = 0; i < 2; i++) {
                item = &m238_gameWork->unk_04[i * 4 + (s16)m238_laneTbl[ctx->work.s16[0]]];
                if (item->unk_05 != 0 || (Hu3DData[item->model].attr & HU3D_ATTR_DISPOFF)) {
                    continue;
                }
                if (ctx->work.s8[0] == 0) {
                    if (object->trans.z < -(m238_gameWork->unk_0C[item->unk_04] * 100) + item->unk_08 + 100.0f) {
                        found = TRUE;
                        item->unk_05 = 1;
                    }
                } else {
                    if (object->trans.z < -(m238_gameWork->unk_0C[item->unk_04] * 100) + 100) {
                        found = TRUE;
                        item->unk_05 = 1;
                    }
                }
            }
            if (found) {
                HuPadBtnDown[player->padId] = Z_TRIG;
                break;
            }
            if (ctx->work.s8[1]++ > ctx->work.s8[0] + ctx->work.s8[3]) {
                ctx->work.s8[1] = 0;
                ctx->work.s8[3] = rand16() % (ctx->work.s8[2] + 1);
                ((u16 *)HuPadBtn)[player->padId] = A_BUTTON;
            } else {
                HuPadBtn[player->padId] = B_BUTTON;
            }
            break;
        case 2:
            break;
    }
}

void m238_PadClear(s32 arg0) {
    arg0 &= 0xFF;
    HuPadStkX[arg0] = 0;
    HuPadStkY[arg0] = 0;
    HuPadBtn[arg0] = 0;
    HuPadBtnDown[arg0] = 0;
}

void m238_PlayerInputUpdate(FuncContext *ctx) {
    CheepCheepChasePlayer *player = &m238_playerTbl[ctx->work.s16[0]];
    omObjData *object = mgPlayerObjTbl[ctx->work.s16[0]];

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->work.s8[3] = 0;
            ctx->state = 1;
            break;
        case 1:
            if (player->unk_01 == 3) {
                break;
            }
            if (ctx->work.s8[0] == 0) {
                if ((u16)HuPadBtn[player->padId] & A_BUTTON) {
                    if (player->unk_01 == 0) {
                        player->unk_14 = 7.0f;
                        player->unk_01 = 1;
                    } else if (player->unk_14 < 90.0f) {
                        player->unk_14 += 4.0f;
                    } else {
                        player->unk_1C++;
                        player->unk_14 = 90.0f;
                        if (player->unk_1C - 4 > 0) {
                            player->unk_18 = (player->unk_1C - 4) * 0.5f;
                            if (player->unk_18 >= 4.0f) {
                                player->unk_18 = 4.0f;
                            }
                        }
                    }
                    ctx->work.s8[0] = 1;
                }
            } else if (!((u16)HuPadBtn[player->padId] & A_BUTTON)) {
                ctx->work.s8[0] = 0;
            }
            if (player->unk_01 == 1 && -(m238_gameWork->unk_0C[6] + 2) * 100 < object->trans.z) {
                if ((u16)HuPadBtn[player->padId] & B_BUTTON) {
                    player->unk_08 = 1;
                }
                if ((u16)HuPadBtn[player->padId] & Z_TRIG) {
                    player->unk_08 = 1;
                }
            }
            if (++ctx->work.s8[1] >= 30) {
                ctx->work.s8[1] = 0;
                player->unk_1C = 0;
            }
            break;
        case 2:
            break;
    }
}

void m238_PlayerInputUpdateB(FuncContext *ctx) {
    CheepCheepChasePlayer *player = &m238_playerTbl[ctx->work.s16[0]];

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->work.s8[3] = 0;
            ctx->state = 1;
            break;
        case 1:
            if (player->unk_01 == 3) {
                break;
            }
            if (ctx->work.s8[0] == 0) {
                if ((u16)HuPadBtn[player->padId] & A_BUTTON) {
                    if (player->unk_01 == 0) {
                        player->unk_14 = 7.0f;
                        player->unk_01 = 1;
                    } else if (player->unk_14 < 90.0f) {
                        player->unk_14 += 4.0f;
                    } else {
                        player->unk_1C++;
                        player->unk_14 = 90.0f;
                        if (player->unk_1C - 1 > 0) {
                            player->unk_18 = (player->unk_1C - 1) * 0.5f;
                            if (player->unk_18 >= 4.0f) {
                                player->unk_18 = 4.0f;
                            }
                        }
                    }
                    ctx->work.s8[0] = 1;
                }
            } else if ((u16)HuPadBtn[player->padId] & B_BUTTON) {
                ctx->work.s8[0] = 0;
            }
            if (player->unk_01 == 1 && (HuPadBtnDown[player->padId] & Z_TRIG)) {
                player->unk_08 = 1;
            }
            if (++ctx->work.s8[1] >= 30) {
                ctx->work.s8[1] = 0;
                player->unk_1C = 0;
            }
            break;
        case 2:
            break;
    }
}

void m238_PlayerMove(FuncContext *ctx) {
    omObjData *object = mgPlayerObjTbl[ctx->work.s16[0]];
    CheepCheepChasePlayer *player = &m238_playerTbl[ctx->work.s16[0]];

    if (player->unk_01 == 4) {
        return;
    }
    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->state = 1;
            break;
        case 1:
            if (player->unk_01 != 1) {
                break;
            }
            if (!player->unk_08) {
                ctx->work.s8[2] = 0;
                object->trans.z -= sindf(player->unk_14) * (player->unk_18 + 6.0f);
                if (Hu3DData[object->model[0]].motTime == 0.0f) {
                    HuAudPlayerFXPlay(GwPlayer[object->work[0]].chr + 0x7A, object->work[0] + 4);
                }
            } else {
                object->trans.z -= sindf(player->unk_14) * (player->unk_18 + 6.0f) - 1.0f;
            }
            player->unk_14 += 4.0f;
            if (player->unk_14 >= 180.0f) {
                player->unk_14 = 0.0f;
                player->unk_01 = 0;
                m238_PlayerStateSet(player, 0x26, FALSE);
            } else {
                player->unk_01 = 1;
                m238_PlayerStateSet(player, 0x27, TRUE);
            }
            break;
        case 2:
            break;
    }
}

void m238_PlayerJumpUpdate(FuncContext *ctx) {
    omObjData *object = mgPlayerObjTbl[ctx->work.s16[0]];
    CheepCheepChasePlayer *player = &m238_playerTbl[ctx->work.s16[0]];

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->work.f32[0] = 0.0f;
            ctx->state = 1;
            break;
        case 1:
            if (!player->unk_08) {
                break;
            }
            ctx->work.f32[0] += 3.6f;
            if (ctx->work.f32[0] >= 180.0f) {
                ctx->work.s8[0] = 0;
                ctx->work.s8[1] = 0;
                ctx->work.f32[0] = 0.0f;
                player->unk_08 = 0;
            }
            object->trans.y = player->unk_04 + 60.0 - sindf(ctx->work.f32[0]) * 150.0;
            switch (ctx->work.s8[1]) {
                case 0:
                    if (m238_LerpCalc(&object->rot.x, (u8 *)&ctx->work.s8[0], 0.0f, 45.0f, 8.0f)) {
                        ctx->work.s8[1] = 1;
                    }
                    break;
                case 1:
                    if (m238_LerpCalc(&object->rot.x, (u8 *)&ctx->work.s8[0], 45.0f, -45.0f, 24.0f)) {
                        ctx->work.s8[1] = 2;
                    }
                    break;
                case 2:
                    if (m238_LerpCalc(&object->rot.x, (u8 *)&ctx->work.s8[0], -45.0f, 0.0f, 17.0f)) {
                        ctx->work.s8[1] = 3;
                    }
                    break;
            }
            break;
        case 2:
            break;
    }
}

void m238_PlayerMotUpdate(FuncContext *ctx) {
    HmfModel *model = &Hu3DData[ctx->param];
    omObjData *object = mgPlayerObjTbl[ctx->work.s16[0]];
    CheepCheepChasePlayer *player = &m238_playerTbl[ctx->work.s16[0]];

    switch (ctx->state) {
        case 0:
            player->updateMotion = FALSE;
            ctx->state = 1;
            break;
        case 1:
            if (Hu3DMotion[Hu3DData[ctx->param].motId].unk02 - 1 <= model->motTime) {
                player->updateMotion = TRUE;
            }
            if (player->updateMotion) {
                MgPlayerMotSet(object, player->motion);
                player->updateMotion = FALSE;
            }
            break;
        case 2:
            break;
    }
}

void m238_PlayerStateSet(CheepCheepChasePlayer *player, s16 motion, s8 updateMotion) {
    player->updateMotion = updateMotion;
    player->motion = motion;
}

void m238_PlayerEffUpdate(FuncContext *ctx) {
    omObjData *object = mgPlayerObjTbl[ctx->work.s16[0]];
    CheepCheepChasePlayer *player = &m238_playerTbl[ctx->work.s16[0]];
    f32 scale = 0.0f;
    f32 chrTable[8] = { 0.3f, 0.2f, 0.2f, 0.2f, 0.2f, 0.0f, 0.2f, 0.2f };
    f32 offset;
    s16 i;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->state = 1;
            break;
        case 1:
            if (player->unk_01 == 1) {
                offset = chrTable[GwPlayer[object->work[0]].chr];
                if (player->unk_08 == 0) {
                    if (ctx->work.s8[0]++ > 10) {
                        ctx->work.s8[0] = 0;
                        for (i = 0; i < 18; i++) {
                            if (m238_AnimMdlDispOn(i, object->trans.x - 0.0, 160.0f, object->trans.z + (0.7 - offset) * 100.0, 0.0f, 90.0f, 0.0f, 1.0f, 0.0f) != 0) {
                                break;
                            }
                        }
                        for (i = 0; i < 18; i++) {
                            if (m238_AnimMdlDispOn(i, object->trans.x + 40.0, 160.0f, object->trans.z + (0.4 - offset) * 100.0, 0.0f, 90.0f, 0.0f, 1.0f, 5.0f) != 0) {
                                break;
                            }
                        }
                    }
                }
            }
            if (player->unk_01 != 4) {
                if (Hu3DData[m238_cheepWork->model].pos.z - object->trans.z <= 350.0f) {
                    switch (ctx->work.s8[1]) {
                        case 0:
                            if (m238_LerpCalc(&scale, (u8 *)&ctx->work.s8[2], 1.2f, 3.0f, 3.0f)) {
                                ctx->work.s8[2] = 1;
                                ctx->work.s8[1] = 1;
                            }
                            Hu3DModelAttrSet(object->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                            break;
                        case 1:
                            if (m238_LerpCalc(&scale, (u8 *)&ctx->work.s8[2], 3.0f, 0.8f, 3.0f)) {
                                ctx->work.s8[2] = 0;
                                ctx->work.s8[1] = 2;
                                Hu3DData[object->model[9]].motSpeed = 1.0f;
                            }
                            break;
                        case 2:
                            scale = 1.2f;
                            if (Hu3DData[object->model[9]].motTime >= player->unk_20) {
                                Hu3DData[object->model[9]].motTime = 0.0f;
                            }
                            break;
                    }
                    Hu3DModelPosSet(object->model[9], object->trans.x - 10.0, object->trans.y + 130.0, object->trans.z - 60.0);
                    Hu3DModelScaleSet(object->model[9], scale, scale, scale);
                } else {
                    ctx->work.s8[1] = 0;
                    Hu3DModelAttrSet(object->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DData[object->model[9]].motSpeed = 0.0f;
                    Hu3DData[object->model[9]].motTime = 0.0f;
                }
            }
            break;
    }
}

void m238_PlayerObstacleHit(FuncContext *ctx) {
    omObjData *object = mgPlayerObjTbl[ctx->work.s16[0]];
    CheepCheepChasePlayer *player = &m238_playerTbl[ctx->work.s16[0]];
    CheepCheepChaseObstacle *item;
    s16 i;
    s16 j;

    if (ctx->state != 1 || player->unk_08 != 0 || player->unk_01 == 4) {
        return;
    }
    for (i = 0; i < 2; i++) {
        item = &m238_gameWork->unk_04[i * 4 + (s16)m238_laneTbl[ctx->work.s16[0]]];
        if (item->unk_03 != 0 || (Hu3DData[item->model].attr & HU3D_ATTR_DISPOFF)) {
            continue;
        }
        if (abs(object->trans.z - (-(m238_gameWork->unk_0C[item->unk_04] * 100) + item->unk_08)) < 90.0) {
            CharFXPlay(0x9D, GwPlayer[object->work[0]].chr);
            player->unk_01 = 3;
            for (j = 18; j < 22; j++) {
                if (m238_AnimMdlDispOn(j, object->trans.x, 110.0f, -(m238_gameWork->unk_0C[item->unk_04] * 100) + item->unk_08, 0.0f, 90.0f, 0.0f, 1.0f, 0.0f)) {
                    break;
                }
            }
            item->unk_02 = 1;
            omVibrate(ctx->work.s16[0], 2, 2, 20);
            PlayerFXPlay(0x286, ctx->work.s16[0]);
            _HuAudPlayerFXPlay(0x434, ctx->work.s16[0]);
            m238_FuncSet(ctx->work.s16[0] + 4, 0, -1, 0, NULL, m238_PlayerStunExec, FALSE, FALSE);
        }
    }
}

void m238_PlayerStunExec(FuncContext *ctx) {
    omObjData *object = mgPlayerObjTbl[ctx->work.s16[0]];
    CheepCheepChasePlayer *player = &m238_playerTbl[ctx->work.s16[0]];

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 30;
            ctx->work.s8[1] = 0;
            m238_PlayerStateSet(player, 0x28, TRUE);
            ctx->state = 1;
            break;
        case 1:
            if (!(ctx->work.s8[0] & 1)) {
                object->trans.y = player->unk_04 + 60.0 - 10.0;
            } else {
                object->trans.y = player->unk_04 + 60.0 + 10.0;
            }
            if (--ctx->work.s8[0] == 0) {
                if (player->unk_01 != 4) {
                    player->unk_01 = 0;
                    m238_PlayerStateSet(player, 0x26, TRUE);
                    object->trans.y = player->unk_04 + 60.0;
                }
                m238_FuncReset(object->work[0] + 4, ctx);
            }
            break;
    }
}

void m238_PlayerSwallowExec(FuncContext *ctx) {
    omObjData *object = mgPlayerObjTbl[ctx->work.s16[0]];
    f32 x;
    f32 z;
    s16 i;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->work.s8[3] = 4;
            ctx->work.s8[4] = 0;
            ctx->work.f32[0] = object->trans.x;
            ctx->work.f32[1] = 0.0f;
            ctx->work.f32[2] = object->trans.y;
            HuAudFXPlay(0x432);
            PlayerFXPlay(0x286, ctx->work.s16[0]);
            ctx->state = 1;
            break;
        case 1:
            if (!ctx->work.s8[1]) {
                if (m238_LerpCalc(&object->trans.x, (u8 *)&ctx->work.s8[0], ctx->work.f32[0], ctx->work.f32[1], 15.0f)) {
                    ctx->work.s8[1] = 1;
                }
                m238_LerpCalc(&object->trans.y, (u8 *)&ctx->work.s8[4], ctx->work.f32[2], 40.0f, 15.0f);
            }
            if (ctx->work.s8[0] < 11) {
                object->trans.z += 10.0;
            } else {
                if (m238_swallowF == 0) {
                    m238_swallowF = 1;
                }
                object->trans.z += 50.0;
            }
            if (ctx->work.s8[0] >= 5) {
                object->scale.x = object->scale.y = object->scale.z = 1.0f - (ctx->work.s8[0] - 5) * 0.035f;
            }
            if (++ctx->work.s8[3] >= 2) {
                ctx->work.s8[3] = 0;
                x = rand16() % 5 * 0.1;
                z = (rand16() % 15 - 10) * 0.1;
                for (i = 0; i < 18; i++) {
                    if (m238_AnimMdlDispOn(i, object->trans.x - x * 100.0f, 160.0f, z * 100.0f + object->trans.z, 0.0f, 90.0f, 0.0f, 1.0f, 0.0f)) {
                        break;
                    }
                }
            }
            if (!ctx->work.s8[2]) {
                if (Hu3DData[m238_cheepWork->model].pos.z - 40.0 <= object->trans.z) {
                    ctx->work.s8[2] = 1;
                    m238_cheepWork->unk_02 = 1;
                }
            } else if (Hu3DData[m238_cheepWork->model].pos.z <= object->trans.z) {
                Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                m238_swallowF = 0;
                m238_FuncGroupReset(ctx->work.s16[0] + 4);
                m238_gameWork->unk_2E++;
            }
            break;
    }
}

void m238_CheepUpdate(FuncContext *ctx) {
    omObjData *object = mgPlayerObjTbl[0];
    CheepCheepChasePlayer *player = m238_playerTbl;
    HmfModel *model = &Hu3DData[ctx->param];
    f32 speed = 0.0f;
    f32 scale = 1.4f;
    f32 amplitude[2] = { 0.4f, 0.1f };
    s16 count = 0;
    s16 i;

    if (omPauseChk() + omAllPauseF != 0) {
        return;
    }
    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.s8[1] = 0;
            ctx->state = 1;
            break;
        case 1:
            for (i = 0; i < 4; i++, object++, player++) {
                if (player->unk_01 == 4) {
                    continue;
                }
                if (player->unk_01 == 6) {
                    continue;
                }
                if (model->pos.z - object->trans.z <= 300.0f) {
                    omVibrate(i, 20, 0, 20);
                    m238_gameWork->unk_30++;
                    player->unk_01 = 4;
                    m238_PlayerStateSet(player, 0x2A, TRUE);
                    m238_FuncSet(i + 4, 0, -1, 0, NULL, m238_PlayerSwallowExec, FALSE, FALSE);
                    Hu3DModelAttrSet(object->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
                speed += player->unk_18 + 6.0f;
                count++;
            }
            if (count >= 2) {
                speed = speed / count * 0.7f;
            } else if (count != 0) {
                speed = (f32)(rand16() % 26) * 0.1 + 6.0;
            }
            model->pos.x = 0.0f;
            model->pos.y = 40.0f;
            if (ctx->work.s8[8]) {
                model->pos.z -= speed;
                if (model->pos.z > Center.z + 300.0) {
                    model->pos.z = Center.z + 300.0;
                }
            } else {
                model->pos.z -= 10.0f;
                if (model->pos.z < Center.z + 300.0) {
                    ctx->work.s8[8] = 1;
                }
            }
            if (m238_gameWork->unk_28 != 0.0f) {
                if (model->pos.z < m238_gameWork->unk_28 - 100.0f) {
                    model->pos.z = m238_gameWork->unk_28 - 100.0f;
                }
            }
            if (m238_cheepWork->unk_02 != 0) {
                scale += sindf(m238_cheepWork->unk_04) * amplitude[ctx->work.s8[1]];
                m238_cheepWork->unk_04 += 15.0f;
                if (m238_cheepWork->unk_04 >= 180.0f) {
                    m238_cheepWork->unk_04 = 0.0f;
                    scale = 1.4f;
                    if (++ctx->work.s8[1] >= 2) {
                        m238_cheepWork->unk_02 = 0;
                        ctx->work.s8[1] = 0;
                    }
                }
                Hu3DModelScaleSet(m238_cheepWork->model, scale, scale, scale);
            }
            break;
    }
}

void m238_MdlVtxMorph(s16 model1, s16 model2, f32 t, s32 node1, s32 node2, s32 full) {
    HmfData *hmf1 = Hu3DData[model1].hmf;
    HmfData *hmf2 = Hu3DData[model2].hmf;

    if (node1 == -1 || node2 == -1) {
        return;
    }
    HmfObjVtxMorph(hmf1, hmf2, t, node1, node2, full);
}

void m238_CheepMorphUpdate(FuncContext *ctx) {
    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.f32[0] = 0.0f;
            ctx->state = 1;
            break;
        case 1:
            switch (ctx->work.s8[0]) {
                case 0:
                    if (omPauseChk() + omAllPauseF == 0) {
                        ctx->work.f32[0] += 0.1f;
                    }
                    if (ctx->work.f32[0] >= 1.0f) {
                        ctx->work.s8[0] = 1;
                    }
                    break;
                case 1:
                    if (omPauseChk() + omAllPauseF == 0) {
                        ctx->work.f32[0] -= 0.1f;
                    }
                    if (ctx->work.f32[0] <= 0.0f) {
                        ctx->work.s8[0] = 0;
                    }
                    break;
            }
            break;
        case 2:
            break;
    }
    m238_MdlVtxMorph(ctx->work.s16[0], ctx->work.s16[1], ctx->work.f32[0], 0, 0, 0);
}

void m238_CheepMotUpdate(FuncContext *ctx) {
    if (omPauseChk() + omAllPauseF != 0) {
        return;
    }
    switch (ctx->state) {
        case 0:
            ctx->work.f32[0] = Hu3DMotion[Hu3DData[ctx->param].motId].unk02;
            ctx->state = 1;
            break;
        case 1:
            if (Hu3DData[ctx->param].motTime >= ctx->work.f32[0]) {
                Hu3DData[ctx->param].motTime = 0.0f;
            }
            break;
        case 2:
            break;
    }
}

void m238_CheepEffUpdate(FuncContext *ctx) {
    HmfModel *model = &Hu3DData[ctx->param];
    s16 start;
    f32 x;
    f32 z;
    f32 animStart;
    s16 i;
    s16 j;

    if (omPauseChk() + omAllPauseF != 0) {
        return;
    }
    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->state = 1;
            break;
        case 1:
            start = 22;
            if (ctx->work.s8[0]++ < 6) {
                break;
            }
            ctx->work.s8[0] = 0;
            for (j = 0; j < 2; j++) {
                for (i = start; i < start + 8; i++) {
                    x = (rand16() % 5 + 4) * 0.1;
                    z = (rand16() % 7 - 5) * 0.1f;
                    animStart = rand16() % 6;
                    if (m238_AnimMdlDispOn(i, x * 100.0f + model->pos.x, -10.0f, model->pos.z + 100.0f + z, 0.0f, 90.0f, 0.0f, 1.0f, animStart)) {
                        break;
                    }
                }
                for (i = start; i < start + 8; i++) {
                    x = (rand16() % 5 - 2) * 0.1f;
                    z = (rand16() % 16 + 15) * 0.1;
                    animStart = rand16() % 6;
                    if (m238_AnimMdlDispOn(i, x * 100.0f + model->pos.x, 20.0f, z * 100.0f + model->pos.z, 0.0f, 90.0f, 0.0f, 1.0f, animStart)) {
                        break;
                    }
                }
            }
            break;
    }
}

void m238_CheepObstacleCheck(FuncContext *ctx) {
    HmfModel *model = &Hu3DData[ctx->param];
    CheepCheepChaseObstacle *unk;
    s16 i;

    if (omPauseChk() + omAllPauseF != 0) {
        return;
    }
    if (ctx->state == 1) {
        for (i = 0; i < 2; i++) {
            unk = &m238_gameWork->unk_04[i * 4];
            if (unk->unk_03 == 0) {
                if (model->pos.z - (Hu3DData[unk->model].pos.z - unk->unk_08) <= 200.0f) {
                    m238_FuncSet(3, 2, ctx->param, 0, (void *)(i * 4), m238_ObstacleSwallowExec, FALSE, FALSE);
                    unk->unk_03 = 1;
                    unk++;
                    unk->unk_03 = 1;
                    unk++;
                    unk->unk_03 = 1;
                    unk++;
                    unk->unk_03 = 1;
                }
            }
        }
    }
}

void m238_ObstacleSwallowExec(FuncContext *ctx) {
    CheepCheepChaseObstacle *item = &m238_gameWork->unk_04[(s32)ctx->data];
    s16 active = FALSE;
    HmfModel *model;
    s16 i;

    if (omPauseChk() + omAllPauseF != 0) {
        return;
    }
    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->work.s8[3] = 0;
            ctx->work.s8[4] = 0;
            ctx->work.s8[5] = 0;
            ctx->work.s8[6] = 0;
            ctx->work.s8[7] = 0;
            ctx->work.s8[8] = 0;
            ctx->work.f32[0] = 180.0f;
            ctx->work.f32[1] = 60.0f;
            ctx->work.f32[2] = -60.0f;
            ctx->work.f32[3] = -180.0f;
            ctx->state = 1;
            break;
        case 1:
            for (i = 0; i < 4; i++, item++) {
                model = &Hu3DData[item->model];
                if (model->attr & 4) {
                    continue;
                }
                active = TRUE;
                if (i + (s32)ctx->data == 0) {
                    if (!ctx->work.s8[i + 4]) {
                        if (m238_LerpCalc(&m238_gameWork->unk_10->trans.x, (u8 *)&ctx->work.s8[i], ctx->work.f32[i], 0.0f, 10.0f)) {
                            ctx->work.s8[i + 4] = 1;
                        }
                    }
                    if (ctx->work.s8[i] < 7) {
                        m238_gameWork->unk_10->trans.z += 10.0;
                    } else {
                        m238_gameWork->unk_10->trans.z += 50.0;
                    }
                } else {
                    if (!ctx->work.s8[i + 4]) {
                        if (m238_LerpCalc(&model->pos.x, (u8 *)&ctx->work.s8[i], ctx->work.f32[i], 0.0f, 10.0f)) {
                            ctx->work.s8[i + 4] = 1;
                        }
                    }
                    if (ctx->work.s8[i] < 7) {
                        model->pos.z += 10.0;
                    } else {
                        model->pos.z += 50.0;
                    }
                }
                if (!ctx->work.s8[8]) {
                    if (Hu3DData[m238_cheepWork->model].pos.z - 40.0 <= model->pos.z) {
                        ctx->work.s8[8] = 1;
                        m238_cheepWork->unk_02 = 1;
                        HuAudFXPlay(0x432);
                    }
                } else if (Hu3DData[m238_cheepWork->model].pos.z <= model->pos.z) {
                    Hu3DModelAttrSet(item->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    item->unk_02 = 1;
                    item->unk_03 = 1;
                }
            }
            if (!active) {
                m238_FuncReset(3, ctx);
            }
            break;
    }
}

void m238_SystemCreate(void) {
    s8 maxFuncs[FUNC_GRP_MAX] = { 4, 5, 4, 6, 12, 12, 12, 12 };
    s16 i;

    m238_animMdlTbl = HuMemAllocTag(ANIMMDL_MAX * sizeof(AnimModelData), TAG_OVERLAY);
    memset(m238_animMdlTbl, 0, ANIMMDL_MAX * sizeof(AnimModelData));
    m238_funcGroupTbl = HuMemAllocTag(FUNC_GRP_MAX * sizeof(FuncGroup), TAG_OVERLAY);
    for (i = 0; i < FUNC_GRP_MAX; i++) {
        m238_FuncGroupCreate(&m238_funcGroupTbl[i], maxFuncs[i]);
    }
}

void m238_FuncGroupCreate(FuncGroup *group, s16 maxFuncs) {
    s16 i;

    group->funcCtx = HuMemAllocTag(maxFuncs * sizeof(FuncContext), TAG_OVERLAY);
    memset(group->funcCtx, 0, maxFuncs * sizeof(FuncContext));
    memset(group->order, -1, sizeof(group->order));
    for (i = 0; i < maxFuncs; i++) {
        group->funcCtx[i].next = -1;
    }
    group->sort = FALSE;
    group->maxFuncs = maxFuncs;
}

s16 m238_FuncSet(s8 groupId, s8 prio, s16 param, s8 state, void *data, void (*func)(FuncContext *), u8 sort, s8 execFunc) {
    FuncGroup *group = &m238_funcGroupTbl[groupId];
    FuncContext *ctx = group->funcCtx;
    s16 i = 0;
    s16 maxFuncs = group->maxFuncs;

    for (i = 0; i < maxFuncs; i++, ctx++) {
        if (!ctx->set) {
            ctx->set = TRUE;
            if (prio > FUNC_PRIO_MAX - 1) {
                prio = FUNC_PRIO_MAX - 1;
            }
            ctx->prio = prio;
            ctx->param = param;
            ctx->state = state;
            ctx->data = data;
            ctx->func = func;
            break;
        }
    }
    if (execFunc) {
        ctx->func(ctx);
    }
    if (sort) {
        m238_FuncGroupSort(group);
        group->sort = FALSE;
    } else {
        group->sort = TRUE;
    }
    return i;
}

void m238_FuncReset(s8 groupId, FuncContext *ctx) {
    s8 next = ctx->next;

    memset(ctx, 0, sizeof(FuncContext));
    ctx->next = next;
    m238_funcGroupTbl[groupId].sort = TRUE;
}

void m238_FuncGroupReset(s8 groupId) {
    FuncGroup *group = &m238_funcGroupTbl[groupId];
    s8 i = 0;

    memset(group->funcCtx, 0, group->maxFuncs * sizeof(FuncContext));
    memset(group->order, -1, sizeof(group->order));
    for (i = 0; i < group->maxFuncs; i++) {
        group->funcCtx[i].next = -1;
    }
}

void m238_FuncGroupUpdate(s8 groupId) {
    FuncGroup *group = &m238_funcGroupTbl[groupId];
    FuncContext *ctx = group->funcCtx;
    s8 i;

    if (group->sort) {
        m238_FuncGroupSort(group);
    }
    for (i = 0; i < FUNC_PRIO_MAX; i++) {
        s8 funcId = group->order[i];

        while (funcId != -1) {
            group->funcCtx[funcId].func(&ctx[funcId]);
            funcId = group->funcCtx[funcId].next;
        }
    }
}

void m238_FuncGroupSort(FuncGroup *group) {
    FuncContext *currCtx = group->funcCtx;
    s8 prio;
    s8 i;

    for (i = 0; i < FUNC_PRIO_MAX; i++) {
        group->order[i] = -1;
    }
    for (i = 0; i < group->maxFuncs; i++, currCtx++) {
        if (!currCtx->set) {
            continue;
        }
        prio = currCtx->prio;
        currCtx->next = group->order[prio];
        group->order[prio] = i;
    }
    group->sort = FALSE;
}

s16 m238_SprCreate(s32 dir, s32 file, u16 arg2, s32 attr) {
    SpriteData *sprite;
    HuSprite *spr;
    s16 i;

    sprite = m238_sprTbl;
    for (i = 0; i < SPRITES_MAX; i++, sprite++) {
        if (sprite->state == SPRITE_STATE_NOTSET) {
            sprite->unk02 = HuSprAnimDataRead((dir << 16) | file);
            sprite->groupId = HuSprGrpCreate(1, 0);
            HuSprAttrReset(sprite->groupId, 0, -1);
            HuSprGrpMemberSet(sprite->groupId, 0, sprite->unk02, 0);
            HuSprAttrSet(sprite->groupId, 0, attr);
            HuSprAnimModeSet(sprite->groupId, 0, arg2);
            HuSprPriSet(sprite->groupId, 0, 0xFFF0);
            HuSprPatNoSet(sprite->groupId, 0, 0);
            HuSprSpeedSet(sprite->groupId, 0, 1.0f);
            HuSprScaleSet(sprite->groupId, 0, 1.0f, 1.0f);
            HuSprPosSet(sprite->groupId, 0, 100, 100);
            spr = HuSprGet(sprite->groupId, 0);
            if (arg2 == 0) {
                sprite->unk04 = 99;
            } else {
                sprite->unk04 = spr->data->patNum;
            }
            sprite->state = SPRITE_STATE_INVISIBLE;
            break;
        }
    }
    return i;
}

void m238_SprDispOn(s16 spriteId, s32 posX, s32 posY) {
    SpriteData *sprite = &m238_sprTbl[spriteId];

    if (sprite->state != SPRITE_STATE_NOTSET) {
        HuSprPatNoSet(sprite->groupId, 0, 0);
        HuSprDispOn(sprite->groupId, 0);
        HuSprPosSet(sprite->groupId, 0, posX, posY);
        sprite->state = SPRITE_STATE_VISIBLE;
    }
}

void m238_SprDispOff(s16 arg0) {
    SpriteData *sprite = &m238_sprTbl[arg0];

    if (sprite->state != SPRITE_STATE_NOTSET) {
        HuSprDispOff(sprite->groupId, 0);
        sprite->state = SPRITE_STATE_INVISIBLE;
    }
}

void m238_SprUpdate(void) {
    SpriteData *sprite;
    s16 i;

    sprite = m238_sprTbl;
    for (i = 0; i < SPRITES_MAX; i++, sprite++) {
        switch (sprite->state) {
            case SPRITE_STATE_VISIBLE:
                if (HuSprGet(sprite->groupId, 0)->patNo + 1 >= sprite->unk04) {
                    HuSprDispOff(sprite->groupId, 0);
                    HuSprPatNoSet(sprite->groupId, 0, 0);
                }
                break;
        }
    }
}

s16 m238_AnimMdlCreate(s32 dir, s32 file, f32 freq, s32 arg3) {
    AnimModelData *animModel;
    HmfModel *hmfModel;
    s16 i;

    animModel = m238_animMdlTbl;
    for (i = 0; i < ANIMMDL_MAX; i++, animModel++) {
        if (!animModel->set) {
            animModel->modelId = Hu3DModelRead((dir << 16) | file, arg3);
            Hu3DModelAttrSet(animModel->modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            hmfModel = &Hu3DData[animModel->modelId];
            hmfModel->motTime = 0.0f;
            hmfModel->motSpeed = 0.0f;
            if (hmfModel->hmf->unk98 != NULL) {
                hmfModel->hmf->unk98->unk08 = 0;
            }
            animModel->freq = freq;
            animModel->state = ANIMMDL_STATE_INVISIBLE;
            animModel->set = TRUE;
            break;
        }
    }
    return i;
}

s16 m238_AnimMdlDispOn(s16 animModelId, f32 posX, f32 posY, f32 posZ, f32 rotX, f32 rotY, f32 rotZ, f32 scale, f32 animStart) {
    AnimModelData *animModel;
    HmfModel *hmfModel;

    if (animModelId >= ANIMMDL_MAX) {
        return FALSE;
    }
    if (!m238_animMdlTbl[animModelId].set) {
        return FALSE;
    }
    animModel = &m238_animMdlTbl[animModelId];
    hmfModel = &Hu3DData[animModel->modelId];
    if ((hmfModel->attr & 4) && animModel->state == ANIMMDL_STATE_INVISIBLE) {
        Hu3DModelPosSet(animModel->modelId, posX, posY, posZ);
        Hu3DModelRotSet(animModel->modelId, rotX, rotY, rotZ);
        Hu3DModelScaleSet(animModel->modelId, scale, scale, scale);
        if (animStart == 0.0f) {
            Hu3DModelAttrSet(animModel->modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            animModel->state = ANIMMDL_STATE_ANIM;
            animModel->animStart = 0.0f;
            animModel->animTimer = 0.0f;
            hmfModel->motSpeed = animModel->freq;
        } else {
            animModel->state = ANIMMDL_STATE_WAIT;
            animModel->animStart = animStart;
            animModel->animTimer = 0.0f;
        }
        return TRUE;
    }
    return FALSE;
}

void m238_AnimMdlUpdate(void) {
    AnimModelData *animModel;
    HmfModel *hmfModel;
    s16 i;

    animModel = m238_animMdlTbl;
    for (i = 0; i < ANIMMDL_MAX; i++, animModel++) {
        if (!animModel->set || animModel->state == ANIMMDL_STATE_INVISIBLE) {
            continue;
        }
        hmfModel = &Hu3DData[animModel->modelId];
        switch (animModel->state) {
            default:
                if (Hu3DMotion[hmfModel->motId].unk02 <= hmfModel->motTime) {
                    Hu3DModelAttrSet(animModel->modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    hmfModel->motTime = 0.0f;
                    hmfModel->motSpeed = 0.0f;
                    if (hmfModel->hmf->unk98 != NULL) {
                        hmfModel->hmf->unk98->unk08 = 0;
                    }
                    animModel->state = ANIMMDL_STATE_INVISIBLE;
                }
                break;
            case ANIMMDL_STATE_WAIT:
                if (animModel->animStart <= animModel->animTimer++) {
                    Hu3DModelAttrSet(animModel->modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    animModel->state = ANIMMDL_STATE_ANIM;
                    hmfModel->motSpeed = animModel->freq;
                }
                break;
        }
    }
}

u8 m238_LerpCalc(f32 *outPos, u8 *tickPtr, f32 posA, f32 posB, f32 numTicks) {
    u8 ticks;
    f32 frac = (f32)*tickPtr / numTicks;

    *outPos = posA + ((posB - posA) * frac);
    ticks = *tickPtr + 1;
    *tickPtr = ticks;
    if (numTicks < ticks) {
        *tickPtr = 0;
        *outPos = posB;
        return 1;
    }
    return 0;
}

f32 m238_BezierCalc(f32 t, f32 p0, f32 p1, f32 p2) {
    f32 u = 1.0f - t;
    f32 ret;

    ret = u * u * p0;
    ret += 2.0f * u * t * p1;
    ret += u * u * p2;
    return ret;
}
