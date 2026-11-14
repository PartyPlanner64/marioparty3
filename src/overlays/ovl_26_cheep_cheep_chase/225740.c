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
#include "overlays/minigame.h"

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
} CheepCheepChaseGameUnk04; // sizeof 0x10

typedef struct CheepCheepChaseGame {
    /* 0x00 */ CheepCheepChaseSegment *segments;
    /* 0x04 */ CheepCheepChaseGameUnk04 *unk_04;
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
} CheepCheepChaseUnk368; // sizeof 0x8

extern u8 D_800D6A90_main;
extern s32 D_800A178C_main[][6];

extern f32 D_8010E014_cheep_cheep_chase;
extern f32 D_8010E018_cheep_cheep_chase;
extern u8 D_8010E010_cheep_cheep_chase;
extern s16 D_8010E01C_cheep_cheep_chase;
extern s16 D_8010E01E_cheep_cheep_chase;
extern s16 D_8010E020_cheep_cheep_chase;
extern s16 D_8010E022_cheep_cheep_chase;
extern s16 D_8010E024_cheep_cheep_chase;
extern s16 D_8010E026_cheep_cheep_chase;
extern s32 D_8010E028_cheep_cheep_chase[8];
extern s16 D_8010E048_cheep_cheep_chase;

extern CheepCheepChaseGame *D_8010E360_cheep_cheep_chase;
extern CheepCheepChasePlayer *D_8010E364_cheep_cheep_chase;
extern CheepCheepChaseUnk368 *D_8010E368_cheep_cheep_chase;
extern f32 D_8010E370_cheep_cheep_chase[4];
extern s16 D_8010E380_cheep_cheep_chase[8];
extern SpriteData *D_8010E390_cheep_cheep_chase;
extern AnimModelData *D_8010E394_cheep_cheep_chase;
extern FuncGroup *D_8010E398_cheep_cheep_chase;

const s16 D_8010E050_cheep_cheep_chase[] = { 0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0x0000 };

const s16 D_8010E05C_cheep_cheep_chase[] = { 0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0x0000, 0x0000 };

const s16 D_8010E06C_cheep_cheep_chase[] = { 0x8263, 0x8271, 0x8260, 0x8276, 0x0000, 0x0000 };

void func_801059BC_cheep_cheep_chase(void);
void func_80105BBC_cheep_cheep_chase(void);
void func_80105DD0_cheep_cheep_chase(omObjData *object);
void func_80105E18_cheep_cheep_chase(omObjData *object);
void func_80105E50_cheep_cheep_chase(omObjData *object);
void func_80105E74_cheep_cheep_chase(void);
void func_80105F50_cheep_cheep_chase(omObjData *object);
void func_8010619C_cheep_cheep_chase(omObjData *object);
void func_801061C8_cheep_cheep_chase(omObjData *object);
void func_80106388_cheep_cheep_chase(omObjData *object);
void func_8010665C_cheep_cheep_chase(omObjData *object);
void func_80106978_cheep_cheep_chase(omObjData *object);
void func_80106E80_cheep_cheep_chase(omObjData *object);
void func_80107440_cheep_cheep_chase(omObjData *object);
void func_801076B4_cheep_cheep_chase(FuncContext *ctx);
void func_8010636C_cheep_cheep_chase(omObjData *object);
void func_80108170_cheep_cheep_chase(FuncContext *ctx);
void func_80108C98_cheep_cheep_chase(FuncContext *ctx);
void func_80108F78_cheep_cheep_chase(FuncContext *ctx);
void func_801090E0_cheep_cheep_chase(FuncContext *ctx);
void func_8010D560_cheep_cheep_chase(void);
void func_8010B63C_cheep_cheep_chase(CheepCheepChasePlayer *player, s16 motion, s8 updateMotion);
void func_801088F8_cheep_cheep_chase(FuncContext *ctx);
void func_801091FC_cheep_cheep_chase(u8 index);
void func_8010D198_cheep_cheep_chase(FuncContext *ctx);
void func_8010D62C_cheep_cheep_chase(FuncGroup *group, s16 maxFuncs);
s16 func_8010D6F4_cheep_cheep_chase(s8 groupId, s8 prio, s16 param, s8 state, void *data, void (*func)(FuncContext *), u8 sort, s8 execFunc);
void func_8010D7F4_cheep_cheep_chase(s8 groupId, FuncContext *ctx);
void func_8010D8FC_cheep_cheep_chase(s8 groupId);
void func_8010D9E8_cheep_cheep_chase(FuncGroup *group);
s16 func_8010DB8C_cheep_cheep_chase(s32 dir, s32 file, f32 freq, s32 arg3);
void func_8010DDF4_cheep_cheep_chase(void);
void func_8010C8EC_cheep_cheep_chase(s16 model1, s16 model2, f32 t, s32 node1, s32 node2, s32 full);
u8 func_8010DF48_cheep_cheep_chase(f32 *outPos, u8 *tickPtr, f32 posA, f32 posB, f32 numTicks);
void func_80106484_cheep_cheep_chase(omObjData *object);
void func_801093CC_cheep_cheep_chase(s32 arg0);
void func_80109444_cheep_cheep_chase(s32 arg0);
void func_801067B0_cheep_cheep_chase(omObjData *object);
void func_80106AA0_cheep_cheep_chase(omObjData *object);
void func_801094C0_cheep_cheep_chase(omObjData *object, s16 offset);
void func_80107698_cheep_cheep_chase(omObjData *object);
void func_8010BEA4_cheep_cheep_chase(FuncContext *ctx);
s16 func_8010DC7C_cheep_cheep_chase(s16 animModelId, f32 posX, f32 posY, f32 posZ, f32 rotX, f32 rotY, f32 rotZ, f32 scale, f32 animStart);
void func_80108AF4_cheep_cheep_chase(FuncContext *ctx);
void func_8010A08C_cheep_cheep_chase(FuncContext *ctx);
void func_8010D85C_cheep_cheep_chase(s8 groupId);
void func_801080C8_cheep_cheep_chase(FuncContext *ctx);
void func_8010C988_cheep_cheep_chase(FuncContext *ctx);
void func_8010CAD4_cheep_cheep_chase(FuncContext *ctx);
void func_8010CBBC_cheep_cheep_chase(FuncContext *ctx);
void func_8010D02C_cheep_cheep_chase(FuncContext *ctx);
void func_8010ACD8_cheep_cheep_chase(s32 arg0);
void func_8010B648_cheep_cheep_chase(FuncContext *ctx);
void func_8010B52C_cheep_cheep_chase(FuncContext *ctx);
void func_8010BB9C_cheep_cheep_chase(FuncContext *ctx);
void func_8010732C_cheep_cheep_chase(omObjData *object);
void func_801085FC_cheep_cheep_chase(FuncContext *ctx);
void func_80109750_cheep_cheep_chase(FuncContext *ctx);
void func_801092B8_cheep_cheep_chase(FuncContext *ctx);
void func_80109CAC_cheep_cheep_chase(FuncContext *ctx);
void func_8010A57C_cheep_cheep_chase(FuncContext *ctx);
void func_8010A938_cheep_cheep_chase(FuncContext *ctx);
void func_8010AD14_cheep_cheep_chase(FuncContext *ctx);
void func_8010AF70_cheep_cheep_chase(FuncContext *ctx);
void func_8010B148_cheep_cheep_chase(FuncContext *ctx);
void func_8010B33C_cheep_cheep_chase(FuncContext *ctx);
void func_8010C440_cheep_cheep_chase(FuncContext *ctx);

void func_801059A0_cheep_cheep_chase(void) {
    func_801059BC_cheep_cheep_chase();
}

void func_801059BC_cheep_cheep_chase(void) {
    u8 camera;

    func_8001FE20_main(50);
    func_800142A0_main(0x20);
    omInitObjMan(50, 0);
    func_8004A208_main();
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -56.0f, 50.0f, 56.0f);
    func_8000B5F0_main(1);
    camera = func_8000B638_main();
    ScissorSet(camera, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camera, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 30.0f, 80.0f, 4000.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_8010D560_cheep_cheep_chase();
    func_80105BBC_cheep_cheep_chase();
    func_8010D6F4_cheep_cheep_chase(0, 0, -1, 0, NULL, func_801076B4_cheep_cheep_chase, FALSE, FALSE);
    omAddObj(100, 0, 0, -1, func_80105F50_cheep_cheep_chase);
    omAddObj(1000, 0, 0, -1, func_80105DD0_cheep_cheep_chase);
    func_80045010_main(D_8010E050_cheep_cheep_chase, 1);
    func_80045010_main(D_8010E05C_cheep_cheep_chase, 1);
    func_80045010_main(D_8010E06C_cheep_cheep_chase, 1);
}

void func_80105BBC_cheep_cheep_chase(void) {
    s16 i;
    s16 j;

    D_8010E360_cheep_cheep_chase = HuMemAllocTag(sizeof(CheepCheepChaseGame), TAG_OVERLAY);
    memset(D_8010E360_cheep_cheep_chase, 0, sizeof(CheepCheepChaseGame));
    D_8010E360_cheep_cheep_chase->segments = HuMemAllocTag(6 * sizeof(CheepCheepChaseSegment), TAG_OVERLAY);
    memset(D_8010E360_cheep_cheep_chase->segments, 0, 6 * sizeof(CheepCheepChaseSegment));
    D_8010E360_cheep_cheep_chase->unk_04 = HuMemAllocTag(8 * sizeof(CheepCheepChaseGameUnk04), TAG_OVERLAY);
    memset(D_8010E360_cheep_cheep_chase->unk_04, 0, 8 * sizeof(CheepCheepChaseGameUnk04));
    D_8010E360_cheep_cheep_chase->segmentOrder = HuMemAllocTag(7, TAG_OVERLAY);
    memset(D_8010E360_cheep_cheep_chase->segmentOrder, 0, 7);
    D_8010E360_cheep_cheep_chase->unk_0C = HuMemAllocTag(7, TAG_OVERLAY);
    memset(D_8010E360_cheep_cheep_chase->unk_0C, 0, 7);
    D_8010E364_cheep_cheep_chase = HuMemAllocTag(4 * sizeof(CheepCheepChasePlayer), TAG_OVERLAY);
    memset(D_8010E364_cheep_cheep_chase, 0, 4 * sizeof(CheepCheepChasePlayer));
    D_8010E368_cheep_cheep_chase = HuMemAllocTag(8, TAG_OVERLAY);
    memset(D_8010E368_cheep_cheep_chase, 0, 8);
    for (i = 0; i < 4; i++) {
        D_8010E370_cheep_cheep_chase[i] = rand16() % 4;
        for (j = 0; j < i; j++) {
            if (D_8010E370_cheep_cheep_chase[j] == D_8010E370_cheep_cheep_chase[i]) {
                i--;
                break;
            }
        }
    }
}

void func_80105DD0_cheep_cheep_chase(omObjData *object) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        object->func = func_80105E18_cheep_cheep_chase;
    }
}

void func_80105E18_cheep_cheep_chase(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = func_80105E50_cheep_cheep_chase;
    }
}

void func_80105E50_cheep_cheep_chase(omObjData *object) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_80105E74_cheep_cheep_chase(void) {
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
    func_8010D8FC_cheep_cheep_chase(0);
}

void func_80105F50_cheep_cheep_chase(omObjData *object) {
    s32 attr = 0x499;
    u8 i;

    omAddObj(10, 7, 0, -1, func_801061C8_cheep_cheep_chase);
    omSetStatBit(omAddObj(10, 4, 0, -1, func_80106388_cheep_cheep_chase), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omAddObj(10, 3, 0, -1, func_8010665C_cheep_cheep_chase);
    omAddObj(10, 8, 0, -1, func_80106978_cheep_cheep_chase);
    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[i] = omAddObj(200, 10, 44, -1, func_80106E80_cheep_cheep_chase);
    }
    omSetStatBit(omAddObj(300, 2, 2, -1, func_80107440_cheep_cheep_chase), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    for (i = 0; i < 18; i++) {
        func_8010DB8C_cheep_cheep_chase(0x47, 5, 1.0f, attr);
    }
    for (i = 0; i < 4; i++) {
        func_8010DB8C_cheep_cheep_chase(1, 0x13, 2.0f, attr);
    }
    for (i = 0; i < 8; i++) {
        func_8010DB8C_cheep_cheep_chase(0x47, 7, 1.0f, attr);
    }
    for (i = 0; i < 8; i++) {
        func_8010DB8C_cheep_cheep_chase(0x47, 6, 1.0f, attr);
    }
    func_8010D6F4_cheep_cheep_chase(1, 0, -1, 0, NULL, func_80108170_cheep_cheep_chase, TRUE, FALSE);
    WipeCreateIn(0xFF, 16);
    object->func = func_8010619C_cheep_cheep_chase;
}

void func_8010619C_cheep_cheep_chase(omObjData *object) {
    func_8010D8FC_cheep_cheep_chase(1);
    func_8010DDF4_cheep_cheep_chase();
    func_80105E74_cheep_cheep_chase();
}

void func_801061C8_cheep_cheep_chase(omObjData *object) {
    s16 i;

    object->model[0] = D_8010E360_cheep_cheep_chase->segments[0].model = func_8000B108_main(0x470000, 0x9D);
    object->model[1] = D_8010E360_cheep_cheep_chase->segments[1].model = func_8000B108_main(0x470002, 0x9D);
    object->model[2] = D_8010E360_cheep_cheep_chase->segments[2].model = func_8000B108_main(0x470001, 0x9D);
    for (i = 0; i < 3; i++) {
        object->model[i + 3] = D_8010E360_cheep_cheep_chase->segments[i + 3].model = Hu3DModelLink(object->model[2]);
    }
    object->model[6] = func_8000B108_main(0x470008, 0x9D);
    func_8010D6F4_cheep_cheep_chase(2, 0, object->model[6], 0, NULL, func_80108C98_cheep_cheep_chase, FALSE, TRUE);
    func_8010D6F4_cheep_cheep_chase(2, 1, -1, 0, NULL, func_80108F78_cheep_cheep_chase, FALSE, TRUE);
    func_8010D6F4_cheep_cheep_chase(2, 0, -1, 1, NULL, func_801090E0_cheep_cheep_chase, TRUE, FALSE);
    object->func = func_8010636C_cheep_cheep_chase;
}

void func_8010636C_cheep_cheep_chase(omObjData *object) {
    func_8010D8FC_cheep_cheep_chase(2);
}

void func_80106388_cheep_cheep_chase(omObjData *object) {
    u16 i;

    object->model[0] = func_8000B108_main(0x470003, 0x2009D);
    for (i = 1; i < 4; i++) {
        object->model[i] = Hu3DModelLink(object->model[0]);
    }
    func_8001C954_main(object->model[0]);
    object->trans.x = 0.0f;
    object->trans.z = -250.0f;
    object->trans.y = 110.0f;
    D_8010E360_cheep_cheep_chase->zTick++;
    for (i = 1; i < 4; i++) {
        func_801093CC_cheep_cheep_chase(object->model[i]);
    }
    object->func = func_80106484_cheep_cheep_chase;
}

void func_80106484_cheep_cheep_chase(omObjData *object) {
    HmfModel *model;
    s16 i;

    func_8001E65C_main(object->model[0], 0.0f, D_8010E014_cheep_cheep_chase, 64, 64);
    if (omPauseChk() + D_800D6A90_main == 0) {
        D_8010E014_cheep_cheep_chase += D_8010E360_cheep_cheep_chase->unk_18;
    }
    for (i = 0; i < 4; i++) {
        model = &Hu3DData[object->model[i]];
        if (Center.z - 900.0f <= model->pos.z) {
            func_8001C258_main(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        if (Center.z + 1000.0f <= model->pos.z) {
            func_8001C258_main(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            if (i != 0) {
                func_801093CC_cheep_cheep_chase(object->model[i]);
            } else {
                object->trans.z = -250.0 - (D_8010E360_cheep_cheep_chase->zTick * 500.0);
                D_8010E360_cheep_cheep_chase->zTick++;
            }
        }
    }
}

void func_8010665C_cheep_cheep_chase(omObjData *object) {
    u16 i;

    object->model[0] = func_8000B108_main(0x470009, 0x9D);
    for (i = 1; i < 3; i++) {
        object->model[i] = Hu3DModelLink(object->model[0]);
    }
    object->trans.x = -325.0f;
    object->trans.y = 200.0f;
    object->trans.z = -800.0f;
    D_8010E360_cheep_cheep_chase->xTick++;
    for (i = 1; i < 3; i++) {
        func_80109444_cheep_cheep_chase(object->model[i]);
    }
    D_8010E360_cheep_cheep_chase->unk_20 = D_800CCF58_main[Hu3DData[object->model[0]].motId].unk02;
    object->func = func_801067B0_cheep_cheep_chase;
}

void func_801067B0_cheep_cheep_chase(omObjData *object) {
    HmfModel *model;
    s16 i;

    for (i = 0; i < 3; i++) {
        model = &Hu3DData[object->model[i]];
        if (model->pos.z >= Center.z - 800.0) {
            func_8001C258_main(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        if (model->pos.z >= Center.z + 700.0) {
            func_8001C258_main(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            if (i != 0) {
                func_80109444_cheep_cheep_chase(object->model[i]);
            } else {
                object->trans.z = 200.0 - (D_8010E360_cheep_cheep_chase->xTick * 1000.0);
                D_8010E360_cheep_cheep_chase->xTick++;
            }
        }
        if (Hu3DData[object->model[i]].motTime >= D_8010E360_cheep_cheep_chase->unk_20) {
            Hu3DData[object->model[i]].motTime = 0.0f;
        }
    }
}

void func_80106978_cheep_cheep_chase(omObjData *object) {
    u16 i;

    object->model[0] = D_8010E360_cheep_cheep_chase->unk_04[0].model = func_8000B108_main(0x470004, 0x2008D);
    for (i = 1; i < 8; i++) {
        object->model[i] = D_8010E360_cheep_cheep_chase->unk_04[i].model = Hu3DModelLink(object->model[0]);
    }
    for (i = 0; i < 8; i++) {
        Hu3DModelScaleSet(object->model[i], 0.9f, 0.9f, 0.9f);
    }
    func_801094C0_cheep_cheep_chase(object, 0);
    func_801094C0_cheep_cheep_chase(object, 4);
    D_8010E360_cheep_cheep_chase->unk_10 = object;
    object->func = func_80106AA0_cheep_cheep_chase;
}

void func_80106AA0_cheep_cheep_chase(omObjData *object) {
    HmfModel *model;
    s16 i;

    for (i = 0; i < 8; i++) {
        model = &Hu3DData[object->model[i]];
        if (!D_8010E360_cheep_cheep_chase->unk_04[i].unk_03) {
            if (!D_8010E360_cheep_cheep_chase->unk_04[i].unk_02) {
                D_8010E018_cheep_cheep_chase += 0.25f;
                if (D_8010E018_cheep_cheep_chase > 180.0f) {
                    D_8010E018_cheep_cheep_chase = 0.0f;
                }
                if (i == 0) {
                    object->trans.y = 105.0 - sindf(D_8010E018_cheep_cheep_chase) * 20.0f * 5.0f * 0.1;
                } else {
                    model->pos.y = 105.0 - sindf(D_8010E018_cheep_cheep_chase) * 20.0f * 5.0f * 0.1;
                }
                D_8010E360_cheep_cheep_chase->unk_04[i].unk_0C += 0.75f;
                if (D_8010E360_cheep_cheep_chase->unk_04[i].unk_0C >= 360.0f) {
                    D_8010E360_cheep_cheep_chase->unk_04[i].unk_0C -= 360.0f;
                }
                D_8010E360_cheep_cheep_chase->unk_04[i].unk_08 =
                    sindf(D_8010E360_cheep_cheep_chase->unk_04[i].unk_0C) * (D_8010E360_cheep_cheep_chase->unk_04[i].unk_04 * 15.0);
                if (i == 0) {
                    object->trans.z = -(D_8010E360_cheep_cheep_chase->unk_0C[D_8010E360_cheep_cheep_chase->unk_04[i].unk_04] * 100) +
                                      D_8010E360_cheep_cheep_chase->unk_04[i].unk_08;
                } else {
                    model->pos.z = -(D_8010E360_cheep_cheep_chase->unk_0C[D_8010E360_cheep_cheep_chase->unk_04[i].unk_04] * 100) +
                                   D_8010E360_cheep_cheep_chase->unk_04[i].unk_08;
                }
                if (Center.z - 1000.0f <= model->pos.z) {
                    func_8001C258_main(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                }
            } else {
                func_8001C258_main(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
        }
        if (Center.z + 700.0f <= model->pos.z) {
            func_8001C258_main(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            if (i == 0 || i == 4) {
                func_801094C0_cheep_cheep_chase(object, i);
            }
        }
    }
}

void func_80106E80_cheep_cheep_chase(omObjData *object) {
    s32 attr = 0x2A9;
    f32 chrTable[8] = { -0.2f, 0.1f, 0.0f, 0.0f, 0.0f, 0.1f, 0.0f, 0.0f };
    func_800E1BA8_minigame_ObjData *data;
    s32 chr;
    s32 model;
    s32 motion;

    object->work[0] = D_800EC280_minigame;
    chr = GwPlayer[object->work[0]].chr;
    model = D_800A178C_main[chr][0];
    motion = D_800A178C_main[chr][2];
    func_800E1BA8_minigame(object, model, motion, D_800EC280_minigame, attr, 0x2BD);
    object->model[9] = func_8000B108_main(0x47000A, 0x2B9);
    func_8001C258_main(object->model[9], 4, 4);
    func_800E5A00_minigame(object, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(object, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(object, 0x26, func_80017BB8_main(chr, 0xD), 1, 0);
    func_800E5A00_minigame(object, 0x27, func_80017BB8_main(chr, 0x3B), 1, 0);
    func_800E5A00_minigame(object, 0x28, func_80017BB8_main(chr, 0x3C), 1, 0);
    func_800E5A00_minigame(object, 0x2A, func_80017BB8_main(chr, 0x59), 1, 0);
    func_800E5A00_minigame(object, 0x2B, func_80017BB8_main(chr, 0x5D), 1, 0);
    func_800E5A00_minigame(object, 0xD, func_80017BB8_main(chr, 0x2F), 1, 999);
    Hu3DModelScaleSet(object->model[0], 0.7f, 0.7f, 0.7f);
    object->trans.x = 300.0 - (D_8010E370_cheep_cheep_chase[D_800EC280_minigame] + 1.0f) * 120.0;
    object->trans.y = 1060.0f;
    object->trans.z = -600.0f;
    object->rot.y = 180.0f;
    func_800E5690_minigame(object, 0x2A);
    Hu3DModelPosSet(object->model[1], 0.0f, 0.0f, 0.0f);
    func_8001C258_main(object->model[1], 4, 4);
    D_800EC280_minigame++;
    data = object->data;
    D_8010E364_cheep_cheep_chase[object->work[0]].padId = data->unk57;
    D_8010E364_cheep_cheep_chase[object->work[0]].unk_01 = 0;
    D_8010E364_cheep_cheep_chase[object->work[0]].unk_04 = chrTable[GwPlayer[object->work[0]].chr] * 20.0f * 5.0f;
    D_8010E364_cheep_cheep_chase[object->work[0]].unk_20 = D_800CCF58_main[Hu3DData[object->model[9]].motId].unk02;
    func_8010D6F4_cheep_cheep_chase(object->work[0] + 4, 9, object->model[0], 0, NULL, func_8010B52C_cheep_cheep_chase, FALSE, FALSE);
    func_8010D6F4_cheep_cheep_chase(object->work[0] + 4, 8, object->model[0], 1, NULL, func_8010BB9C_cheep_cheep_chase, TRUE, FALSE);
    object->func = func_8010732C_cheep_cheep_chase;
}

void func_8010732C_cheep_cheep_chase(omObjData *object) {
    FuncGroup *group = &D_8010E398_cheep_cheep_chase[object->work[0] + 4];
    FuncContext *ctx = group->funcCtx;
    s8 i;

    if (group->sort) {
        func_8010D9E8_cheep_cheep_chase(group);
    }
    for (i = 0; i < FUNC_PRIO_MAX; i++) {
        s8 funcId = group->order[i];

        while (funcId != -1) {
            group->funcCtx[funcId].work.s16[0] = object->work[0];
            group->funcCtx[funcId].func(&ctx[funcId]);
            funcId = group->funcCtx[funcId].next;
        }
    }
    func_800E4E30_minigame(object);
}

void func_80107440_cheep_cheep_chase(omObjData *object) {
    s16 ctxId;

    object->model[1] = D_8010E368_cheep_cheep_chase->model = func_8000B108_main(0xA0086, 0x289);
    object->model[0] = func_8000B108_main(0xA0087, 0x28D);
    object->motion[0] = func_8000B108_main(0xA0088, 0x28D);
    func_8001C5B4_main(object->model[1], object->motion[0]);
    func_8001C814_main(object->motion[0], 2, 2);
    func_8001C954_main(object->model[1]);
    func_8001C2FC_main(object->model[1], 0x20000, 0x20000);
    func_8001C2FC_main(object->model[0], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(object->model[1]);
    Hu3DModelRemakeStatic(object->model[0]);
    func_8001C514_main(object->model[1]);
    func_8001C514_main(object->model[0]);
    Hu3DModelScaleSet(object->model[1], 1.4f, 1.4f, 1.4f);
    Hu3DModelPosSet(object->model[1], 0.0f, 40.0f, 0.0f);
    Hu3DModelRotSet(object->model[1], 0.0f, 180.0f, 0.0f);
    ctxId = func_8010D6F4_cheep_cheep_chase(3, 7, -1, 0, NULL, func_8010C988_cheep_cheep_chase, FALSE, FALSE);
    D_8010E398_cheep_cheep_chase[3].funcCtx[ctxId].work.s16[0] = object->model[1];
    D_8010E398_cheep_cheep_chase[3].funcCtx[ctxId].work.s16[1] = object->model[0];
    func_8010D6F4_cheep_cheep_chase(3, 8, object->model[1], 0, NULL, func_8010CAD4_cheep_cheep_chase, FALSE, TRUE);
    func_8010D6F4_cheep_cheep_chase(3, 9, object->model[1], 1, NULL, func_8010CBBC_cheep_cheep_chase, FALSE, FALSE);
    func_8010D6F4_cheep_cheep_chase(3, 1, object->model[1], 1, NULL, func_8010D02C_cheep_cheep_chase, TRUE, FALSE);
    object->func = func_80107698_cheep_cheep_chase;
}

void func_80107698_cheep_cheep_chase(omObjData *object) {
    func_8010D8FC_cheep_cheep_chase(3);
}

void func_801076B4_cheep_cheep_chase(FuncContext *ctx) {
    if (ctx->state == 0) {
        Center.x = -26.0f;
        Center.y = 327.0f;
        Center.z = -485.0f;
        CRot.x = 320.0f;
        CRot.y = 180.0f;
        CRot.z = 0.0f;
        CZoom = 1670.0f;
        func_8010D7F4_cheep_cheep_chase(0, ctx);
    }
}

void func_80107760_cheep_cheep_chase(FuncContext *ctx) {
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
                    sprintf(D_800D5218_main, "C: TRANSLATE ADD: %d", ctx->work.s8[0]);
                } else {
                    sprintf(D_800D5218_main, "C: ROTATE");
                }
                print8(16, 56, D_800D5218_main);
                sprintf(D_800D5218_main, "CZOOMM %.2f", CZoom);
                print8(16, 64, D_800D5218_main);
                sprintf(D_800D5218_main, "CCENTER_X %.2f Y %.2f Z %.2f", Center.x, Center.y, Center.z);
                print8(16, 72, D_800D5218_main);
                sprintf(D_800D5218_main, "CROTATE_X %.2f Y %.2f Z %.2f", CRot.x, CRot.y, CRot.z);
                print8(16, 80, D_800D5218_main);
            }
            buttons = D_800CDA7C_main[0];
            if (D_800D5558_main[0] & Z_TRIG) {
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

void func_80107BDC_cheep_cheep_chase(FuncContext *ctx) {
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
                func_8010D7F4_cheep_cheep_chase(0, ctx);
                func_8010D6F4_cheep_cheep_chase(0, 2, -1, 0, NULL, func_801080C8_cheep_cheep_chase, FALSE, FALSE);
            }
            break;
    }
}

void func_80107E3C_cheep_cheep_chase(FuncContext *ctx) {
    omObjData *object = D_800EC598_minigame[0];
    CheepCheepChasePlayer *player = D_8010E364_cheep_cheep_chase;
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
                func_8010D7F4_cheep_cheep_chase(0, ctx);
            }
            break;
    }
}

void func_801080C8_cheep_cheep_chase(FuncContext *ctx) {
    s16 i;

    switch (ctx->state) {
        case 0:
            ctx->work.f32[0] = Center.z;
            ctx->state = 1;
            break;
        case 1:
            for (i = 0; i < 4; i++) {
                if (D_800EC598_minigame[i]->trans.z + 255.0f < ctx->work.f32[0]) {
                    ctx->work.f32[0] = D_800EC598_minigame[i]->trans.z + 255.0f;
                }
            }
            Center.z = ctx->work.f32[0];
            break;
        case 2:
            break;
    }
}

void func_80108170_cheep_cheep_chase(FuncContext *ctx) {
    omObjData *object = D_800EC598_minigame[0];
    s16 i;

    if (D_8010E01C_cheep_cheep_chase >= 4) {
        HuAudSeqPlay(0x34);
    }
    switch (ctx->state) {
        case 0:
            D_8010E380_cheep_cheep_chase[0] = HuAudFXPlay(0x433);
            ctx->work.s16[0] = 0;
            ctx->state = 1;
            break;
        case 1:
            switch (ctx->work.s16[0]++) {
                case 10:
                    for (i = 0; i < 4; i++, object++) {
                        func_8010D6F4_cheep_cheep_chase(i + 4, 0, object->model[0], 0, NULL, func_80109750_cheep_cheep_chase, FALSE, FALSE);
                    }
                    break;
                case 80:
                    func_8010D6F4_cheep_cheep_chase(2, 0, D_8010E360_cheep_cheep_chase->unk_24, 0, NULL, func_801092B8_cheep_cheep_chase, FALSE, FALSE);
                    break;
                case 90:
                    object = D_800EC598_minigame[0];
                    for (i = 0; i < 4; i++, object++) {
                        func_8010D6F4_cheep_cheep_chase(i + 4, 4, object->model[0], 0, NULL, func_80109CAC_cheep_cheep_chase, FALSE, FALSE);
                    }
                    break;
                case 70:
                    func_8010D6F4_cheep_cheep_chase(0, 0, -1, 0, NULL, func_80107BDC_cheep_cheep_chase, FALSE, FALSE);
                    break;
                case 110:
                    GMesCreate(3);
                    HuAudFXPlay(0xE);
                    D_8010E01E_cheep_cheep_chase = 1;
                    break;
                default:
                    if (D_8010E01E_cheep_cheep_chase == 1) {
                        if (++D_8010E022_cheep_cheep_chase > 60) {
                            for (i = 0; i < 4; i++, object++) {
                                if (GwPlayer[object->work[0]].stat & 1) {
                                    if (D_8010E010_cheep_cheep_chase == 0) {
                                        func_8010D6F4_cheep_cheep_chase(i + 4, 0, object->model[0], 0, NULL, func_8010A57C_cheep_cheep_chase, FALSE, FALSE);
                                    } else {
                                        func_8010D6F4_cheep_cheep_chase(i + 4, 0, object->model[0], 0, NULL, func_8010A938_cheep_cheep_chase, FALSE, FALSE);
                                    }
                                }
                                if (D_8010E010_cheep_cheep_chase == 0) {
                                    func_8010D6F4_cheep_cheep_chase(i + 4, 1, object->model[0], 0, NULL, func_8010AD14_cheep_cheep_chase, FALSE, FALSE);
                                } else {
                                    func_8010D6F4_cheep_cheep_chase(i + 4, 1, object->model[0], 0, NULL, func_8010AF70_cheep_cheep_chase, FALSE, FALSE);
                                }
                                func_8010D6F4_cheep_cheep_chase(i + 4, 2, object->model[0], 0, NULL, func_8010B148_cheep_cheep_chase, FALSE, FALSE);
                                func_8010D6F4_cheep_cheep_chase(i + 4, 3, object->model[0], 0, NULL, func_8010B33C_cheep_cheep_chase, FALSE, FALSE);
                            }
                            D_8010E020_cheep_cheep_chase = ctx->work.s16[0] + 10;
                            D_8010E01E_cheep_cheep_chase = 2;
                        }
                    } else if (D_8010E01E_cheep_cheep_chase == 2) {
                        if (ctx->work.s16[0] >= D_8010E020_cheep_cheep_chase) {
                            func_8010D6F4_cheep_cheep_chase(3, 0, D_8010E368_cheep_cheep_chase->model, 0, NULL, func_8010C440_cheep_cheep_chase, FALSE, FALSE);
                            func_8010D7F4_cheep_cheep_chase(1, ctx);
                            func_8010D6F4_cheep_cheep_chase(1, 0, -1, 1, NULL, func_801085FC_cheep_cheep_chase, FALSE, FALSE);
                        }
                    }
                    break;
            }
            break;
    }
}

void func_801085FC_cheep_cheep_chase(FuncContext *ctx) {
    omObjData *object = D_800EC598_minigame[0];
    CheepCheepChasePlayer *player = D_8010E364_cheep_cheep_chase;
    s16 caughtCount = 0;
    s16 caught[4] = { -1, -1, -1, -1 };
    s16 index;
    s16 i;

    switch (ctx->state) {
        case 0:
            break;
        case 1:
            if (D_8010E360_cheep_cheep_chase->unk_2E == 4) {
                func_8010D85C_cheep_cheep_chase(1);
                func_8010D6F4_cheep_cheep_chase(1, 0, -1, 0, NULL, func_80108AF4_cheep_cheep_chase, FALSE, TRUE);
                break;
            }
            if (D_8010E360_cheep_cheep_chase->unk_30 == 4) {
                break;
            }
            if (D_8010E360_cheep_cheep_chase->unk_28 != 0.0f) {
                for (i = 0; i < 4; i++, object++) {
                    if (object->trans.z < D_8010E360_cheep_cheep_chase->unk_28 - 350.0) {
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
                    D_8010E360_cheep_cheep_chase->unk_2C = i;
                    player->unk_01 = 6;
                } else {
                    player->unk_01 = 7;
                }
                func_8010D85C_cheep_cheep_chase(i + 4);
                func_8010D6F4_cheep_cheep_chase(i + 4, 0, object->model[0], 0, NULL, func_8010A08C_cheep_cheep_chase, FALSE, FALSE);
            }
            func_8010D7F4_cheep_cheep_chase(1, ctx);
            HuAudSeqFadeOut(120);
            GMesCreate(0xE);
            func_8010D6F4_cheep_cheep_chase(1, 0, -1, 0, NULL, func_801088F8_cheep_cheep_chase, FALSE, TRUE);
            D_8010E360_cheep_cheep_chase->unk_18 = 0.4f;
            break;
    }
}

void func_801088F8_cheep_cheep_chase(FuncContext *ctx) {
    if (ctx->state == 0) {
        ctx->work.s16[0] = 0;
        ctx->state = 1;
    }
    if (++ctx->work.s16[0] >= 16) {
        ctx->work.s16[0] = 15;
        func_8004AEF0_main(D_8010E380_cheep_cheep_chase[0], 15);
        func_8010D7F4_cheep_cheep_chase(1, ctx);
    }
}

void func_8010896C_cheep_cheep_chase(FuncContext *ctx) {
    switch (ctx->state) {
        case 0:
            ctx->work.s16[0] = 0;
            ctx->state = 1;
            break;
        case 1:
            if (D_8010E024_cheep_cheep_chase >= 2) {
                if (GMesStatGet() == 0) {
                    D_8010E024_cheep_cheep_chase = 3;
                }
                if (D_8010E024_cheep_cheep_chase == 3) {
                    if (++ctx->work.s16[0] >= 15) {
                        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                        ctx->state = 2;
                    }
                }
            } else {
                if ((u16)ctx->work.s16[0]++ == 0) {
                    GMesCreate(0x16, GwPlayer[D_8010E360_cheep_cheep_chase->unk_2C].chr);
                    HuAudSeqPlay(0x65);
                    GwPlayer[D_8010E360_cheep_cheep_chase->unk_2C].bonusCoin += 10;
                }
                if (GMesStatGet() != 0) {
                    ctx->work.s16[0] = 0;
                    D_8010E024_cheep_cheep_chase = 2;
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

void func_80108AF4_cheep_cheep_chase(FuncContext *ctx) {
    if (D_8010E026_cheep_cheep_chase == 1 && GMesStatGet() == 0) {
        ctx->state = 99;
        ctx->work.s16[0] = 0;
        D_8010E026_cheep_cheep_chase = 2;
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
                    GMesCreate(0xE);
                    func_8010D6F4_cheep_cheep_chase(1, 0, -1, 0, NULL, func_801088F8_cheep_cheep_chase, FALSE, TRUE);
                    ctx->state = 3;
                    break;
                case 15:
                    GMesCreate(0x20);
                    HuAudSeqPlay(0x6C);
                    D_8010E026_cheep_cheep_chase = 1;
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

void func_80108C98_cheep_cheep_chase(FuncContext *ctx) {
    s16 i;

    if (ctx->state == 0) {
        D_8010E360_cheep_cheep_chase->segments[0].unk_04 = 1200.0f;
        D_8010E360_cheep_cheep_chase->segments[0].unk_08 = 600.0f;
        D_8010E360_cheep_cheep_chase->segments[0].length = 1000.0f;
        D_8010E360_cheep_cheep_chase->segments[1].unk_04 = 1200.0f;
        D_8010E360_cheep_cheep_chase->segments[1].unk_08 = 600.0f;
        D_8010E360_cheep_cheep_chase->segments[1].length = 1000.0f;
        for (i = 0; i < 4; i++) {
            D_8010E360_cheep_cheep_chase->segments[i + 2].unk_04 = 1200.0f;
            D_8010E360_cheep_cheep_chase->segments[i + 2].unk_08 = 600.0f;
            D_8010E360_cheep_cheep_chase->segments[i + 2].length = 1000.0f;
        }
        D_8010E360_cheep_cheep_chase->zTick = 0;
        D_8010E360_cheep_cheep_chase->xTick = 0;
        D_8010E360_cheep_cheep_chase->scaleIndex = 0;
        D_8010E360_cheep_cheep_chase->unk_28 = 0.0f;
        D_8010E360_cheep_cheep_chase->unk_18 = 0.4f;
        D_8010E360_cheep_cheep_chase->unk_2C = -1;
        D_8010E360_cheep_cheep_chase->unk_2E = 0;
        D_8010E360_cheep_cheep_chase->unk_30 = 0;
        D_8010E360_cheep_cheep_chase->segmentOrder[0] = 0;
        D_8010E360_cheep_cheep_chase->segmentOrder[1] = 2;
        D_8010E360_cheep_cheep_chase->segmentOrder[2] = 3;
        D_8010E360_cheep_cheep_chase->segmentOrder[3] = 4;
        D_8010E360_cheep_cheep_chase->segmentOrder[4] = 5;
        D_8010E360_cheep_cheep_chase->segmentOrder[5] = 2;
        D_8010E360_cheep_cheep_chase->segmentOrder[6] = 1;
        for (i = 0; i < 5; i++) {
            func_801091FC_cheep_cheep_chase(i);
        }
        func_801091FC_cheep_cheep_chase(6);
        D_8010E360_cheep_cheep_chase->unk_0C[0] = 10;
        D_8010E360_cheep_cheep_chase->unk_0C[1] = 18;
        D_8010E360_cheep_cheep_chase->unk_0C[2] = 28;
        D_8010E360_cheep_cheep_chase->unk_0C[3] = 32;
        D_8010E360_cheep_cheep_chase->unk_0C[4] = 40;
        D_8010E360_cheep_cheep_chase->unk_0C[5] = 47;
        D_8010E360_cheep_cheep_chase->unk_0C[6] = 56;
        D_8010E360_cheep_cheep_chase->unk_24 = ctx->param;
        Hu3DModelScaleSet(ctx->param, 1.4f, 1.4f, 1.4f);
        Hu3DModelPosSet(ctx->param, 0.0f, -100.0f, 0.0f);
        func_8001C258_main(ctx->param, 4, 0);
        Hu3DData[ctx->param].motSpeed = 0.0f;
        Hu3DData[ctx->param].motTime = 0.0f;
        func_8010D7F4_cheep_cheep_chase(2, ctx);
    }
}

void func_80108F78_cheep_cheep_chase(FuncContext *ctx) {
    CheepCheepChaseSegment *segment = &D_8010E360_cheep_cheep_chase->segments[1];
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
                    func_8001C258_main(segment->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                }
                if (Center.z + 1700.0f <= model->pos.z) {
                    func_8001C258_main(segment->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    if (i >= 2 && ctx->work.s8[0] < 7) {
                        func_801091FC_cheep_cheep_chase(ctx->work.s8[0]++);
                    }
                }
            }
            break;
        case 2:
            break;
    }
}

void func_801090E0_cheep_cheep_chase(FuncContext *ctx) {
    CheepCheepChaseSegment *segment = D_8010E360_cheep_cheep_chase->segments;
    HmfModel *model = &Hu3DData[segment->model];

    switch (ctx->state) {
        case 0:
            break;
        case 1:
            if (Center.z - 700.0f <= model->pos.z) {
                func_8001C258_main(segment->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            if (model->pos.z >= Center.z + 1700.0f + 400.0) {
                func_8001C258_main(segment->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                func_8010D7F4_cheep_cheep_chase(2, ctx);
                func_8001C258_main(D_8010E360_cheep_cheep_chase->unk_24, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            break;
        case 2:
            break;
    }
}

void func_801091FC_cheep_cheep_chase(u8 index) {
    f32 z = 0.0f;
    CheepCheepChaseSegment *segment;
    s16 i;

    if (index != 0) {
        for (i = 0; i < index; i++) {
            segment = &D_8010E360_cheep_cheep_chase->segments[D_8010E360_cheep_cheep_chase->segmentOrder[i]];
            z -= segment->length;
        }
    }
    segment = &D_8010E360_cheep_cheep_chase->segments[D_8010E360_cheep_cheep_chase->segmentOrder[index]];
    if (D_8010E360_cheep_cheep_chase->segmentOrder[index] == 1) {
        D_8010E360_cheep_cheep_chase->unk_28 = z;
    }
    Hu3DModelPosSet(segment->model, 0.0f, 0.0f, z);
}

void func_801092B8_cheep_cheep_chase(FuncContext *ctx) {
    HmfModel *model = &Hu3DData[ctx->param];

    switch (ctx->state) {
        case 0:
            HuAudFXPlay(0x435);
            ctx->work.f32[0] = D_800CCF58_main[Hu3DData[ctx->param].motId].unk02 - 1.0f;
            model->motSpeed = 1.0f;
            ctx->state = 1;
            break;
        case 1:
            if (Hu3DData[ctx->param].motTime >= ctx->work.f32[0]) {
                func_8010D7F4_cheep_cheep_chase(2, ctx);
            }
            break;
    }
}

void func_801093CC_cheep_cheep_chase(s32 arg0) {
    Hu3DModelPosSet(arg0, 0.0f, 110.0f, -250.0 - (D_8010E360_cheep_cheep_chase->zTick * 500.0));
    D_8010E360_cheep_cheep_chase->zTick++;
}

void func_80109444_cheep_cheep_chase(s32 arg0) {
    Hu3DModelPosSet(arg0, -325.0f, 200.0f, 200.0 - (D_8010E360_cheep_cheep_chase->xTick * 1000.0));
    D_8010E360_cheep_cheep_chase->xTick++;
}

void func_801094C0_cheep_cheep_chase(omObjData *object, s16 offset) {
    s16 i;

    if (D_8010E360_cheep_cheep_chase->scaleIndex < 7) {
        for (i = 0; i < 4; i++) {
            if (offset + i == 0) {
                object->trans.x = 300.0 - (i + 1) * 120.0;
                object->trans.y = 110.0f;
                object->trans.z = -(D_8010E360_cheep_cheep_chase->unk_0C[D_8010E360_cheep_cheep_chase->scaleIndex] * 100);
            } else {
                Hu3DModelPosSet(object->model[offset + i], 300.0 - (i + 1) * 120.0, 110.0f,
                                -(D_8010E360_cheep_cheep_chase->unk_0C[D_8010E360_cheep_cheep_chase->scaleIndex] * 100));
            }
            D_8010E360_cheep_cheep_chase->unk_04[offset + i].unk_04 = D_8010E360_cheep_cheep_chase->scaleIndex;
            D_8010E360_cheep_cheep_chase->unk_04[offset + i].unk_02 = 0;
            D_8010E360_cheep_cheep_chase->unk_04[offset + i].unk_03 = 0;
            D_8010E360_cheep_cheep_chase->unk_04[offset + i].unk_05 = 0;
            D_8010E360_cheep_cheep_chase->unk_04[offset + i].unk_0C = rand16() % 361;
        }
        D_8010E360_cheep_cheep_chase->scaleIndex++;
    }
}

void func_80109750_cheep_cheep_chase(FuncContext *ctx) {
    omObjData *object = D_800EC598_minigame[ctx->work.s16[0]];
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
            func_800E5690_minigame(object, 0x2A);
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
                                if (func_8010DC7C_cheep_cheep_chase(j, x * 100.0f + object->trans.x, 160.0f, z * 100.0f + object->trans.z, 0.0f, 90.0f, 0.0f, 1.0f, i) != 0) {
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
                    if (object->trans.y >= D_8010E364_cheep_cheep_chase[object->work[0]].unk_04 + 60.0) {
                        ctx->work.s8[0] = 2;
                        ctx->work.f32[2] = 0.0f;
                        CharFXPlay(0x82, GwPlayer[object->work[0]].chr);
                        object->trans.y = D_8010E364_cheep_cheep_chase[object->work[0]].unk_04 + 60.0;
                    }
                    break;
            }
            if (ctx->work.s8[0] == 2) {
                func_800E5690_minigame(object, 0x26);
                func_8010D7F4_cheep_cheep_chase(ctx->work.s16[0] + 4, ctx);
            }
            break;
    }
}

void func_80109CAC_cheep_cheep_chase(FuncContext *ctx) {
    omObjData *object = D_800EC598_minigame[ctx->work.s16[0]];
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
                    func_800E5690_minigame(object, 0x2B);
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
                                if (func_8010DF48_cheep_cheep_chase(&scale, (u8 *)&ctx->work.s8[2], 1.2f, 2.5f, 3.0f)) {
                                    ctx->work.s8[2] = 0;
                                    ctx->work.s8[3] = 1;
                                }
                                func_8001C258_main(object->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                                break;
                            case 1:
                                if (func_8010DF48_cheep_cheep_chase(&scale, (u8 *)&ctx->work.s8[2], 2.5f, 0.8f, 3.0f)) {
                                    Hu3DData[object->model[0]].motSpeed = 0.75f;
                                    ctx->work.s8[2] = 0;
                                    ctx->work.s8[3] = 2;
                                    func_8001C258_main(object->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                                    D_8010E01C_cheep_cheep_chase++;
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
                func_8010B63C_cheep_cheep_chase(&D_8010E364_cheep_cheep_chase[object->work[0]], 0x26, TRUE);
                Hu3DData[object->model[0]].motSpeed = 1.0f;
                Hu3DData[object->model[9]].rot.y = 0.0f;
                func_8010D7F4_cheep_cheep_chase(ctx->work.s16[0] + 4, ctx);
                func_8010D6F4_cheep_cheep_chase(object->work[0] + 4, 4, object->model[0], 0, NULL, func_8010B648_cheep_cheep_chase, FALSE, FALSE);
            }
            break;
    }
}

void func_8010A08C_cheep_cheep_chase(FuncContext *ctx) {
    omObjData *object = D_800EC598_minigame[ctx->work.s16[0]];
    CheepCheepChasePlayer *player = &D_8010E364_cheep_cheep_chase[ctx->work.s16[0]];

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->work.s8[3] = 0;
            ctx->work.s8[4] = 0;
            ctx->work.f32[0] = object->trans.z;
            ctx->work.f32[1] = object->trans.x;
            func_8001C258_main(object->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            ctx->state = 1;
            break;
        case 1:
            switch (player->unk_01) {
                case 7:
                    func_800E5690_minigame(object, 0x2A);
                    object->trans.z += 5.0;
                    ctx->work.s8[0] += 0.5;
                    if (ctx->work.s8[0] >= 180.0f) {
                        ctx->work.s8[0] -= 180.0f;
                    }
                    object->trans.y = sindf(ctx->work.s8[0]) * 20.0f * 5.0f * 0.05f + 80.0;
                    break;
                case 6:
                    if (++ctx->work.s8[3] >= 5) {
                        func_800E5690_minigame(object, 1);
                        if (Hu3DData[object->model[0]].motTime == 0.0f) {
                            CharFXPlay(0x1F, GwPlayer[object->work[0]].chr);
                        }
                        if (ctx->work.s8[2] == 0) {
                            if (func_8010DF48_cheep_cheep_chase(&object->trans.y, (u8 *)&ctx->work.s8[0], player->unk_04 + 60.0, 210.0f, 20.0f)) {
                                ctx->work.s8[2] = 1;
                            }
                        }
                        if (func_8010DF48_cheep_cheep_chase(&object->trans.z, (u8 *)&ctx->work.s8[1], ctx->work.f32[0], D_8010E360_cheep_cheep_chase->unk_28 - 700.0, 70.0f)) {
                            ctx->work.s8[1] = 70;
                        }
                        if (func_8010DF48_cheep_cheep_chase(&object->trans.x, (u8 *)&ctx->work.s8[4], ctx->work.f32[1], 0.0f, 70.0f)) {
                            func_800E5690_minigame(object, 0);
                            ctx->state = 2;
                            func_8010D6F4_cheep_cheep_chase(0, 0, -1, 0, NULL, func_80107E3C_cheep_cheep_chase, FALSE, FALSE);
                            ctx->work.s8[1] = 0;
                        }
                    }
                    func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y - 5.0f, object->trans.z);
                    break;
            }
            break;
        case 2:
            if (func_8010DF48_cheep_cheep_chase(&object->rot.y, (u8 *)&ctx->work.s8[1], 180.0f, 121.0f, 40.0f)) {
                ctx->state = 3;
                ctx->work.s8[1] = 0;
            }
            break;
        case 3:
            if (++ctx->work.s8[1] >= 6) {
                s16 playerNo = ctx->work.s16[0];
                s32 dataNum = D_8010E028_cheep_cheep_chase[GwPlayer[playerNo].chr];

                func_80017790_main(object->model[0], 2, GwPlayer[playerNo].chr, dataNum);
                func_8010D7F4_cheep_cheep_chase(ctx->work.s16[0] + 4, ctx);
                func_800E5690_minigame(object, 0xD);
                func_80045ED0_main(D_800A178C_main[GwPlayer[playerNo].chr][0] | 0x2F);
                func_8010D6F4_cheep_cheep_chase(1, 0, -1, 0, NULL, func_8010896C_cheep_cheep_chase, FALSE, FALSE);
            }
            break;
    }
}

void func_8010A57C_cheep_cheep_chase(FuncContext *ctx) {
    omObjData *object = D_800EC598_minigame[ctx->work.s16[0]];
    CheepCheepChasePlayer *player = &D_8010E364_cheep_cheep_chase[ctx->work.s16[0]];
    s16 found = FALSE;
    CheepCheepChaseGameUnk04 *item;
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
            func_8010ACD8_cheep_cheep_chase(player->padId);
            for (i = 0; i < 2; i++) {
                item = &D_8010E360_cheep_cheep_chase->unk_04[i * 4 + (s16)D_8010E370_cheep_cheep_chase[ctx->work.s16[0]]];
                if (item->unk_05 != 0 || (Hu3DData[item->model].attr & 4)) {
                    continue;
                }
                if (ctx->work.s8[0] == 0) {
                    if (-(D_8010E360_cheep_cheep_chase->unk_0C[item->unk_04] * 100) + item->unk_08 + 140.0 > object->trans.z) {
                        found = TRUE;
                        item->unk_05 = 1;
                    }
                } else {
                    if (-(D_8010E360_cheep_cheep_chase->unk_0C[item->unk_04] * 100) + 140.0 > object->trans.z) {
                        found = TRUE;
                        item->unk_05 = 1;
                    }
                }
            }
            if (found) {
                D_800CDA7C_main[player->padId] = B_BUTTON;
                break;
            }
            if (ctx->work.s8[1]++ > ctx->work.s8[0] + ctx->work.s8[3]) {
                ctx->work.s8[1] = 0;
                ctx->work.s8[3] = rand16() % (ctx->work.s8[2] + 1);
                ((u16 *)D_800CDA7C_main)[player->padId] = A_BUTTON;
            } else {
                D_800CDA7C_main[player->padId] = 0;
            }
            break;
        case 2:
            break;
    }
}

void func_8010A938_cheep_cheep_chase(FuncContext *ctx) {
    omObjData *object = D_800EC598_minigame[ctx->work.s16[0]];
    CheepCheepChasePlayer *player = &D_8010E364_cheep_cheep_chase[ctx->work.s16[0]];
    s16 found = FALSE;
    CheepCheepChaseGameUnk04 *item;
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
            func_8010ACD8_cheep_cheep_chase(player->padId);
            for (i = 0; i < 2; i++) {
                item = &D_8010E360_cheep_cheep_chase->unk_04[i * 4 + (s16)D_8010E370_cheep_cheep_chase[ctx->work.s16[0]]];
                if (item->unk_05 != 0 || (Hu3DData[item->model].attr & 4)) {
                    continue;
                }
                if (ctx->work.s8[0] == 0) {
                    if (object->trans.z < -(D_8010E360_cheep_cheep_chase->unk_0C[item->unk_04] * 100) + item->unk_08 + 100.0f) {
                        found = TRUE;
                        item->unk_05 = 1;
                    }
                } else {
                    if (object->trans.z < -(D_8010E360_cheep_cheep_chase->unk_0C[item->unk_04] * 100) + 100) {
                        found = TRUE;
                        item->unk_05 = 1;
                    }
                }
            }
            if (found) {
                D_800D5558_main[player->padId] = Z_TRIG;
                break;
            }
            if (ctx->work.s8[1]++ > ctx->work.s8[0] + ctx->work.s8[3]) {
                ctx->work.s8[1] = 0;
                ctx->work.s8[3] = rand16() % (ctx->work.s8[2] + 1);
                ((u16 *)D_800CDA7C_main)[player->padId] = A_BUTTON;
            } else {
                D_800CDA7C_main[player->padId] = B_BUTTON;
            }
            break;
        case 2:
            break;
    }
}

void func_8010ACD8_cheep_cheep_chase(s32 arg0) {
    arg0 &= 0xFF;
    D_800CBB6E_main[arg0] = 0;
    D_800D20A1_main[arg0] = 0;
    D_800CDA7C_main[arg0] = 0;
    D_800D5558_main[arg0] = 0;
}

void func_8010AD14_cheep_cheep_chase(FuncContext *ctx) {
    CheepCheepChasePlayer *player = &D_8010E364_cheep_cheep_chase[ctx->work.s16[0]];
    omObjData *object = D_800EC598_minigame[ctx->work.s16[0]];

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
                if ((u16)D_800CDA7C_main[player->padId] & A_BUTTON) {
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
            } else if (!((u16)D_800CDA7C_main[player->padId] & A_BUTTON)) {
                ctx->work.s8[0] = 0;
            }
            if (player->unk_01 == 1 && -(D_8010E360_cheep_cheep_chase->unk_0C[6] + 2) * 100 < object->trans.z) {
                if ((u16)D_800CDA7C_main[player->padId] & B_BUTTON) {
                    player->unk_08 = 1;
                }
                if ((u16)D_800CDA7C_main[player->padId] & Z_TRIG) {
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

void func_8010AF70_cheep_cheep_chase(FuncContext *ctx) {
    CheepCheepChasePlayer *player = &D_8010E364_cheep_cheep_chase[ctx->work.s16[0]];

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
                if ((u16)D_800CDA7C_main[player->padId] & A_BUTTON) {
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
            } else if ((u16)D_800CDA7C_main[player->padId] & B_BUTTON) {
                ctx->work.s8[0] = 0;
            }
            if (player->unk_01 == 1 && (D_800D5558_main[player->padId] & Z_TRIG)) {
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

void func_8010B148_cheep_cheep_chase(FuncContext *ctx) {
    omObjData *object = D_800EC598_minigame[ctx->work.s16[0]];
    CheepCheepChasePlayer *player = &D_8010E364_cheep_cheep_chase[ctx->work.s16[0]];

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
                    func_8004AC98_main(GwPlayer[object->work[0]].chr + 0x7A, object->work[0] + 4);
                }
            } else {
                object->trans.z -= sindf(player->unk_14) * (player->unk_18 + 6.0f) - 1.0f;
            }
            player->unk_14 += 4.0f;
            if (player->unk_14 >= 180.0f) {
                player->unk_14 = 0.0f;
                player->unk_01 = 0;
                func_8010B63C_cheep_cheep_chase(player, 0x26, FALSE);
            } else {
                player->unk_01 = 1;
                func_8010B63C_cheep_cheep_chase(player, 0x27, TRUE);
            }
            break;
        case 2:
            break;
    }
}

void func_8010B33C_cheep_cheep_chase(FuncContext *ctx) {
    omObjData *object = D_800EC598_minigame[ctx->work.s16[0]];
    CheepCheepChasePlayer *player = &D_8010E364_cheep_cheep_chase[ctx->work.s16[0]];

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
                    if (func_8010DF48_cheep_cheep_chase(&object->rot.x, (u8 *)&ctx->work.s8[0], 0.0f, 45.0f, 8.0f)) {
                        ctx->work.s8[1] = 1;
                    }
                    break;
                case 1:
                    if (func_8010DF48_cheep_cheep_chase(&object->rot.x, (u8 *)&ctx->work.s8[0], 45.0f, -45.0f, 24.0f)) {
                        ctx->work.s8[1] = 2;
                    }
                    break;
                case 2:
                    if (func_8010DF48_cheep_cheep_chase(&object->rot.x, (u8 *)&ctx->work.s8[0], -45.0f, 0.0f, 17.0f)) {
                        ctx->work.s8[1] = 3;
                    }
                    break;
            }
            break;
        case 2:
            break;
    }
}

void func_8010B52C_cheep_cheep_chase(FuncContext *ctx) {
    HmfModel *model = &Hu3DData[ctx->param];
    omObjData *object = D_800EC598_minigame[ctx->work.s16[0]];
    CheepCheepChasePlayer *player = &D_8010E364_cheep_cheep_chase[ctx->work.s16[0]];

    switch (ctx->state) {
        case 0:
            player->updateMotion = FALSE;
            ctx->state = 1;
            break;
        case 1:
            if (D_800CCF58_main[Hu3DData[ctx->param].motId].unk02 - 1 <= model->motTime) {
                player->updateMotion = TRUE;
            }
            if (player->updateMotion) {
                func_800E5690_minigame(object, player->motion);
                player->updateMotion = FALSE;
            }
            break;
        case 2:
            break;
    }
}

void func_8010B63C_cheep_cheep_chase(CheepCheepChasePlayer *player, s16 motion, s8 updateMotion) {
    player->updateMotion = updateMotion;
    player->motion = motion;
}

void func_8010B648_cheep_cheep_chase(FuncContext *ctx) {
    omObjData *object = D_800EC598_minigame[ctx->work.s16[0]];
    CheepCheepChasePlayer *player = &D_8010E364_cheep_cheep_chase[ctx->work.s16[0]];
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
                            if (func_8010DC7C_cheep_cheep_chase(i, object->trans.x - 0.0, 160.0f, object->trans.z + (0.7 - offset) * 100.0, 0.0f, 90.0f, 0.0f, 1.0f, 0.0f) != 0) {
                                break;
                            }
                        }
                        for (i = 0; i < 18; i++) {
                            if (func_8010DC7C_cheep_cheep_chase(i, object->trans.x + 40.0, 160.0f, object->trans.z + (0.4 - offset) * 100.0, 0.0f, 90.0f, 0.0f, 1.0f, 5.0f) != 0) {
                                break;
                            }
                        }
                    }
                }
            }
            if (player->unk_01 != 4) {
                if (Hu3DData[D_8010E368_cheep_cheep_chase->model].pos.z - object->trans.z <= 350.0f) {
                    switch (ctx->work.s8[1]) {
                        case 0:
                            if (func_8010DF48_cheep_cheep_chase(&scale, (u8 *)&ctx->work.s8[2], 1.2f, 3.0f, 3.0f)) {
                                ctx->work.s8[2] = 1;
                                ctx->work.s8[1] = 1;
                            }
                            func_8001C258_main(object->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                            break;
                        case 1:
                            if (func_8010DF48_cheep_cheep_chase(&scale, (u8 *)&ctx->work.s8[2], 3.0f, 0.8f, 3.0f)) {
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
                    func_8001C258_main(object->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DData[object->model[9]].motSpeed = 0.0f;
                    Hu3DData[object->model[9]].motTime = 0.0f;
                }
            }
            break;
    }
}

void func_8010BB9C_cheep_cheep_chase(FuncContext *ctx) {
    omObjData *object = D_800EC598_minigame[ctx->work.s16[0]];
    CheepCheepChasePlayer *player = &D_8010E364_cheep_cheep_chase[ctx->work.s16[0]];
    CheepCheepChaseGameUnk04 *item;
    s16 i;
    s16 j;

    if (ctx->state != 1 || player->unk_08 != 0 || player->unk_01 == 4) {
        return;
    }
    for (i = 0; i < 2; i++) {
        item = &D_8010E360_cheep_cheep_chase->unk_04[i * 4 + (s16)D_8010E370_cheep_cheep_chase[ctx->work.s16[0]]];
        if (item->unk_03 != 0 || (Hu3DData[item->model].attr & 4)) {
            continue;
        }
        if (abs(object->trans.z - (-(D_8010E360_cheep_cheep_chase->unk_0C[item->unk_04] * 100) + item->unk_08)) < 90.0) {
            CharFXPlay(0x9D, GwPlayer[object->work[0]].chr);
            player->unk_01 = 3;
            for (j = 18; j < 22; j++) {
                if (func_8010DC7C_cheep_cheep_chase(j, object->trans.x, 110.0f, -(D_8010E360_cheep_cheep_chase->unk_0C[item->unk_04] * 100) + item->unk_08, 0.0f, 90.0f, 0.0f, 1.0f, 0.0f)) {
                    break;
                }
            }
            item->unk_02 = 1;
            omVibrate(ctx->work.s16[0], 2, 2, 20);
            PlayerFXPlay(0x286, ctx->work.s16[0]);
            func_8004AC5C_main(0x434, ctx->work.s16[0]);
            func_8010D6F4_cheep_cheep_chase(ctx->work.s16[0] + 4, 0, -1, 0, NULL, func_8010BEA4_cheep_cheep_chase, FALSE, FALSE);
        }
    }
}

void func_8010BEA4_cheep_cheep_chase(FuncContext *ctx) {
    omObjData *object = D_800EC598_minigame[ctx->work.s16[0]];
    CheepCheepChasePlayer *player = &D_8010E364_cheep_cheep_chase[ctx->work.s16[0]];

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 30;
            ctx->work.s8[1] = 0;
            func_8010B63C_cheep_cheep_chase(player, 0x28, TRUE);
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
                    func_8010B63C_cheep_cheep_chase(player, 0x26, TRUE);
                    object->trans.y = player->unk_04 + 60.0;
                }
                func_8010D7F4_cheep_cheep_chase(object->work[0] + 4, ctx);
            }
            break;
    }
}

void func_8010C004_cheep_cheep_chase(FuncContext *ctx) {
    omObjData *object = D_800EC598_minigame[ctx->work.s16[0]];
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
                if (func_8010DF48_cheep_cheep_chase(&object->trans.x, (u8 *)&ctx->work.s8[0], ctx->work.f32[0], ctx->work.f32[1], 15.0f)) {
                    ctx->work.s8[1] = 1;
                }
                func_8010DF48_cheep_cheep_chase(&object->trans.y, (u8 *)&ctx->work.s8[4], ctx->work.f32[2], 40.0f, 15.0f);
            }
            if (ctx->work.s8[0] < 11) {
                object->trans.z += 10.0;
            } else {
                if (D_8010E048_cheep_cheep_chase == 0) {
                    D_8010E048_cheep_cheep_chase = 1;
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
                    if (func_8010DC7C_cheep_cheep_chase(i, object->trans.x - x * 100.0f, 160.0f, z * 100.0f + object->trans.z, 0.0f, 90.0f, 0.0f, 1.0f, 0.0f)) {
                        break;
                    }
                }
            }
            if (!ctx->work.s8[2]) {
                if (Hu3DData[D_8010E368_cheep_cheep_chase->model].pos.z - 40.0 <= object->trans.z) {
                    ctx->work.s8[2] = 1;
                    D_8010E368_cheep_cheep_chase->unk_02 = 1;
                }
            } else if (Hu3DData[D_8010E368_cheep_cheep_chase->model].pos.z <= object->trans.z) {
                func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                D_8010E048_cheep_cheep_chase = 0;
                func_8010D85C_cheep_cheep_chase(ctx->work.s16[0] + 4);
                D_8010E360_cheep_cheep_chase->unk_2E++;
            }
            break;
    }
}

void func_8010C440_cheep_cheep_chase(FuncContext *ctx) {
    omObjData *object = D_800EC598_minigame[0];
    CheepCheepChasePlayer *player = D_8010E364_cheep_cheep_chase;
    HmfModel *model = &Hu3DData[ctx->param];
    f32 speed = 0.0f;
    f32 scale = 1.4f;
    f32 amplitude[2] = { 0.4f, 0.1f };
    s16 count = 0;
    s16 i;

    if (omPauseChk() + D_800D6A90_main != 0) {
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
                    D_8010E360_cheep_cheep_chase->unk_30++;
                    player->unk_01 = 4;
                    func_8010B63C_cheep_cheep_chase(player, 0x2A, TRUE);
                    func_8010D6F4_cheep_cheep_chase(i + 4, 0, -1, 0, NULL, func_8010C004_cheep_cheep_chase, FALSE, FALSE);
                    func_8001C258_main(object->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
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
            if (D_8010E360_cheep_cheep_chase->unk_28 != 0.0f) {
                if (model->pos.z < D_8010E360_cheep_cheep_chase->unk_28 - 100.0f) {
                    model->pos.z = D_8010E360_cheep_cheep_chase->unk_28 - 100.0f;
                }
            }
            if (D_8010E368_cheep_cheep_chase->unk_02 != 0) {
                scale += sindf(D_8010E368_cheep_cheep_chase->unk_04) * amplitude[ctx->work.s8[1]];
                D_8010E368_cheep_cheep_chase->unk_04 += 15.0f;
                if (D_8010E368_cheep_cheep_chase->unk_04 >= 180.0f) {
                    D_8010E368_cheep_cheep_chase->unk_04 = 0.0f;
                    scale = 1.4f;
                    if (++ctx->work.s8[1] >= 2) {
                        D_8010E368_cheep_cheep_chase->unk_02 = 0;
                        ctx->work.s8[1] = 0;
                    }
                }
                Hu3DModelScaleSet(D_8010E368_cheep_cheep_chase->model, scale, scale, scale);
            }
            break;
    }
}

void func_8010C8EC_cheep_cheep_chase(s16 model1, s16 model2, f32 t, s32 node1, s32 node2, s32 full) {
    HmfData *hmf1 = Hu3DData[model1].hmf;
    HmfData *hmf2 = Hu3DData[model2].hmf;

    if (node1 == -1 || node2 == -1) {
        return;
    }
    func_8001CF1C_main(hmf1, hmf2, t, node1, node2, full);
}

void func_8010C988_cheep_cheep_chase(FuncContext *ctx) {
    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.f32[0] = 0.0f;
            ctx->state = 1;
            break;
        case 1:
            switch (ctx->work.s8[0]) {
                case 0:
                    if (omPauseChk() + D_800D6A90_main == 0) {
                        ctx->work.f32[0] += 0.1f;
                    }
                    if (ctx->work.f32[0] >= 1.0f) {
                        ctx->work.s8[0] = 1;
                    }
                    break;
                case 1:
                    if (omPauseChk() + D_800D6A90_main == 0) {
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
    func_8010C8EC_cheep_cheep_chase(ctx->work.s16[0], ctx->work.s16[1], ctx->work.f32[0], 0, 0, 0);
}

void func_8010CAD4_cheep_cheep_chase(FuncContext *ctx) {
    if (omPauseChk() + D_800D6A90_main != 0) {
        return;
    }
    switch (ctx->state) {
        case 0:
            ctx->work.f32[0] = D_800CCF58_main[Hu3DData[ctx->param].motId].unk02;
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

void func_8010CBBC_cheep_cheep_chase(FuncContext *ctx) {
    HmfModel *model = &Hu3DData[ctx->param];
    s16 start;
    f32 x;
    f32 z;
    f32 animStart;
    s16 i;
    s16 j;

    if (omPauseChk() + D_800D6A90_main != 0) {
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
                    if (func_8010DC7C_cheep_cheep_chase(i, x * 100.0f + model->pos.x, -10.0f, model->pos.z + 100.0f + z, 0.0f, 90.0f, 0.0f, 1.0f, animStart)) {
                        break;
                    }
                }
                for (i = start; i < start + 8; i++) {
                    x = (rand16() % 5 - 2) * 0.1f;
                    z = (rand16() % 16 + 15) * 0.1;
                    animStart = rand16() % 6;
                    if (func_8010DC7C_cheep_cheep_chase(i, x * 100.0f + model->pos.x, 20.0f, z * 100.0f + model->pos.z, 0.0f, 90.0f, 0.0f, 1.0f, animStart)) {
                        break;
                    }
                }
            }
            break;
    }
}

void func_8010D02C_cheep_cheep_chase(FuncContext *ctx) {
    HmfModel *model = &Hu3DData[ctx->param];
    CheepCheepChaseGameUnk04 *unk;
    s16 i;

    if (omPauseChk() + D_800D6A90_main != 0) {
        return;
    }
    if (ctx->state == 1) {
        for (i = 0; i < 2; i++) {
            unk = &D_8010E360_cheep_cheep_chase->unk_04[i * 4];
            if (unk->unk_03 == 0) {
                if (model->pos.z - (Hu3DData[unk->model].pos.z - unk->unk_08) <= 200.0f) {
                    func_8010D6F4_cheep_cheep_chase(3, 2, ctx->param, 0, (void *)(i * 4), func_8010D198_cheep_cheep_chase, FALSE, FALSE);
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

void func_8010D198_cheep_cheep_chase(FuncContext *ctx) {
    CheepCheepChaseGameUnk04 *item = &D_8010E360_cheep_cheep_chase->unk_04[(s32)ctx->data];
    s16 active = FALSE;
    HmfModel *model;
    s16 i;

    if (omPauseChk() + D_800D6A90_main != 0) {
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
                        if (func_8010DF48_cheep_cheep_chase(&D_8010E360_cheep_cheep_chase->unk_10->trans.x, (u8 *)&ctx->work.s8[i], ctx->work.f32[i], 0.0f, 10.0f)) {
                            ctx->work.s8[i + 4] = 1;
                        }
                    }
                    if (ctx->work.s8[i] < 7) {
                        D_8010E360_cheep_cheep_chase->unk_10->trans.z += 10.0;
                    } else {
                        D_8010E360_cheep_cheep_chase->unk_10->trans.z += 50.0;
                    }
                } else {
                    if (!ctx->work.s8[i + 4]) {
                        if (func_8010DF48_cheep_cheep_chase(&model->pos.x, (u8 *)&ctx->work.s8[i], ctx->work.f32[i], 0.0f, 10.0f)) {
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
                    if (Hu3DData[D_8010E368_cheep_cheep_chase->model].pos.z - 40.0 <= model->pos.z) {
                        ctx->work.s8[8] = 1;
                        D_8010E368_cheep_cheep_chase->unk_02 = 1;
                        HuAudFXPlay(0x432);
                    }
                } else if (Hu3DData[D_8010E368_cheep_cheep_chase->model].pos.z <= model->pos.z) {
                    func_8001C258_main(item->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    item->unk_02 = 1;
                    item->unk_03 = 1;
                }
            }
            if (!active) {
                func_8010D7F4_cheep_cheep_chase(3, ctx);
            }
            break;
    }
}

void func_8010D560_cheep_cheep_chase(void) {
    s8 maxFuncs[FUNC_GRP_MAX] = { 4, 5, 4, 6, 12, 12, 12, 12 };
    s16 i;

    D_8010E394_cheep_cheep_chase = HuMemAllocTag(ANIMMDL_MAX * sizeof(AnimModelData), TAG_OVERLAY);
    memset(D_8010E394_cheep_cheep_chase, 0, ANIMMDL_MAX * sizeof(AnimModelData));
    D_8010E398_cheep_cheep_chase = HuMemAllocTag(FUNC_GRP_MAX * sizeof(FuncGroup), TAG_OVERLAY);
    for (i = 0; i < FUNC_GRP_MAX; i++) {
        func_8010D62C_cheep_cheep_chase(&D_8010E398_cheep_cheep_chase[i], maxFuncs[i]);
    }
}

void func_8010D62C_cheep_cheep_chase(FuncGroup *group, s16 maxFuncs) {
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

s16 func_8010D6F4_cheep_cheep_chase(s8 groupId, s8 prio, s16 param, s8 state, void *data, void (*func)(FuncContext *), u8 sort, s8 execFunc) {
    FuncGroup *group = &D_8010E398_cheep_cheep_chase[groupId];
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
        func_8010D9E8_cheep_cheep_chase(group);
        group->sort = FALSE;
    } else {
        group->sort = TRUE;
    }
    return i;
}

void func_8010D7F4_cheep_cheep_chase(s8 groupId, FuncContext *ctx) {
    s8 next = ctx->next;

    memset(ctx, 0, sizeof(FuncContext));
    ctx->next = next;
    D_8010E398_cheep_cheep_chase[groupId].sort = TRUE;
}

void func_8010D85C_cheep_cheep_chase(s8 groupId) {
    FuncGroup *group = &D_8010E398_cheep_cheep_chase[groupId];
    s8 i = 0;

    memset(group->funcCtx, 0, group->maxFuncs * sizeof(FuncContext));
    memset(group->order, -1, sizeof(group->order));
    for (i = 0; i < group->maxFuncs; i++) {
        group->funcCtx[i].next = -1;
    }
}

void func_8010D8FC_cheep_cheep_chase(s8 groupId) {
    FuncGroup *group = &D_8010E398_cheep_cheep_chase[groupId];
    FuncContext *ctx = group->funcCtx;
    s8 i;

    if (group->sort) {
        func_8010D9E8_cheep_cheep_chase(group);
    }
    for (i = 0; i < FUNC_PRIO_MAX; i++) {
        s8 funcId = group->order[i];

        while (funcId != -1) {
            group->funcCtx[funcId].func(&ctx[funcId]);
            funcId = group->funcCtx[funcId].next;
        }
    }
}

void func_8010D9E8_cheep_cheep_chase(FuncGroup *group) {
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

s16 func_8010DA74_cheep_cheep_chase(s32 dir, s32 file, u16 arg2, s32 attr) {
    SpriteData *sprite;
    HuSprite *spr;
    s16 i;

    sprite = D_8010E390_cheep_cheep_chase;
    for (i = 0; i < SPRITES_MAX; i++, sprite++) {
        if (sprite->state == SPRITE_STATE_NOTSET) {
            sprite->unk02 = func_8000B838_main((dir << 16) | file);
            sprite->groupId = HuSprGrpCreate(1, 0);
            HuSprAttrReset(sprite->groupId, 0, -1);
            HuSprGrpMemberSet(sprite->groupId, 0, sprite->unk02, 0);
            HuSprAttrSet(sprite->groupId, 0, attr);
            func_800550F4_main(sprite->groupId, 0, arg2);
            HuSprPriSet(sprite->groupId, 0, 0xFFF0);
            func_80054FF8_main(sprite->groupId, 0, 0);
            HuSprSpeedSet(sprite->groupId, 0, 1.0f);
            HuSprScaleSet(sprite->groupId, 0, 1.0f, 1.0f);
            HuSprPosSet(sprite->groupId, 0, 100, 100);
            spr = HuSprGet(sprite->groupId, 0);
            if (arg2 == 0) {
                sprite->unk04 = 99;
            } else {
                sprite->unk04 = spr->unk_84->unk10;
            }
            sprite->state = SPRITE_STATE_INVISIBLE;
            break;
        }
    }
    return i;
}

void func_8010DA84_cheep_cheep_chase(s16 spriteId, s32 posX, s32 posY) {
    SpriteData *sprite = &D_8010E390_cheep_cheep_chase[spriteId];

    if (sprite->state != SPRITE_STATE_NOTSET) {
        func_80054FF8_main(sprite->groupId, 0, 0);
        HuSprAttrReset(sprite->groupId, 0, 0x8000);
        HuSprPosSet(sprite->groupId, 0, posX, posY);
        sprite->state = SPRITE_STATE_VISIBLE;
    }
}

void func_8010DB24_cheep_cheep_chase(s16 arg0) {
    SpriteData *sprite = &D_8010E390_cheep_cheep_chase[arg0];

    if (sprite->state != SPRITE_STATE_NOTSET) {
        HuSprDispOff(sprite->groupId, 0);
        sprite->state = SPRITE_STATE_INVISIBLE;
    }
}

void func_8010DB80_cheep_cheep_chase(void) {
    SpriteData *sprite;
    s16 i;

    sprite = D_8010E390_cheep_cheep_chase;
    for (i = 0; i < SPRITES_MAX; i++, sprite++) {
        switch (sprite->state) {
            case SPRITE_STATE_VISIBLE:
                if (HuSprGet(sprite->groupId, 0)->unk_90 + 1 >= sprite->unk04) {
                    HuSprDispOff(sprite->groupId, 0);
                    func_80054FF8_main(sprite->groupId, 0, 0);
                }
                break;
        }
    }
}

s16 func_8010DB8C_cheep_cheep_chase(s32 dir, s32 file, f32 freq, s32 arg3) {
    AnimModelData *animModel;
    HmfModel *hmfModel;
    s16 i;

    animModel = D_8010E394_cheep_cheep_chase;
    for (i = 0; i < ANIMMDL_MAX; i++, animModel++) {
        if (!animModel->set) {
            animModel->modelId = func_8000B108_main((dir << 16) | file, arg3);
            func_8001C258_main(animModel->modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
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

s16 func_8010DC7C_cheep_cheep_chase(s16 animModelId, f32 posX, f32 posY, f32 posZ, f32 rotX, f32 rotY, f32 rotZ, f32 scale, f32 animStart) {
    AnimModelData *animModel;
    HmfModel *hmfModel;

    if (animModelId >= ANIMMDL_MAX) {
        return FALSE;
    }
    if (!D_8010E394_cheep_cheep_chase[animModelId].set) {
        return FALSE;
    }
    animModel = &D_8010E394_cheep_cheep_chase[animModelId];
    hmfModel = &Hu3DData[animModel->modelId];
    if ((hmfModel->attr & 4) && animModel->state == ANIMMDL_STATE_INVISIBLE) {
        Hu3DModelPosSet(animModel->modelId, posX, posY, posZ);
        Hu3DModelRotSet(animModel->modelId, rotX, rotY, rotZ);
        Hu3DModelScaleSet(animModel->modelId, scale, scale, scale);
        if (animStart == 0.0f) {
            func_8001C258_main(animModel->modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
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

void func_8010DDF4_cheep_cheep_chase(void) {
    AnimModelData *animModel;
    HmfModel *hmfModel;
    s16 i;

    animModel = D_8010E394_cheep_cheep_chase;
    for (i = 0; i < ANIMMDL_MAX; i++, animModel++) {
        if (!animModel->set || animModel->state == ANIMMDL_STATE_INVISIBLE) {
            continue;
        }
        hmfModel = &Hu3DData[animModel->modelId];
        switch (animModel->state) {
            default:
                if (D_800CCF58_main[hmfModel->motId].unk02 <= hmfModel->motTime) {
                    func_8001C258_main(animModel->modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
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
                    func_8001C258_main(animModel->modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    animModel->state = ANIMMDL_STATE_ANIM;
                    hmfModel->motSpeed = animModel->freq;
                }
                break;
        }
    }
}

u8 func_8010DF48_cheep_cheep_chase(f32 *outPos, u8 *tickPtr, f32 posA, f32 posB, f32 numTicks) {
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

f32 func_8010DFC0_cheep_cheep_chase(f32 t, f32 p0, f32 p1, f32 p2) {
    f32 u = 1.0f - t;
    f32 ret;

    ret = u * u * p0;
    ret += 2.0f * u * t * p1;
    ret += u * u * p2;
    return ret;
}
