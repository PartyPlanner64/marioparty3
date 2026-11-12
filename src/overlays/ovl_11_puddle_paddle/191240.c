#include "common.h"
#include "gcc/memory.h"
#include "game/hu3d.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "game/mallocblock.h"
#include "game/hmfspr.h"
#include "game/hmfmath.h"
#include "overlays/minigame.h"

#define ABS(x) ((x) > 0 ? (x) : -(x))

typedef struct RGBA {
    /* 0x00 */ u8 r;
    /* 0x01 */ u8 g;
    /* 0x02 */ u8 b;
    /* 0x03 */ u8 a;
} RGBA;

typedef struct PuddlePaddleSlot { // 0xC bytes
    /* 0x00 */ omObjData *unk_00;
    /* 0x04 */ s16 *unk_04; // model indices
    /* 0x08 */ s16 unk_08;
} PuddlePaddleSlot; // Size 0xC

typedef struct PuddlePaddleHandler {
    /* 0x00 */ s8 unk_00;
    /* 0x01 */ char unk_01;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s8 unk_04;
    /* 0x05 */ s8 unk_05;
    /* 0x06 */ char unk_06[2];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s8 unk_0C[16];
    /* 0x1C */ s16 unk_1C[8];
    /* 0x2C */ f32 unk_2C[4];
    /* 0x3C */ void *unk_3C;
    /* 0x40 */ void (*unk_40)();
} PuddlePaddleHandler; // Size 0x44

typedef struct PuddlePaddleOrder {
    /* 0x00 */ u32 priority;
    /* 0x04 */ s16 next;
    /* 0x06 */ s16 previous;
    /* 0x08 */ s16 handler;
    /* 0x0A */ char unk_0A[2];
} PuddlePaddleOrder; // Size 0xC

typedef struct UnkPuddlePaddleEntry { // size 0x24, sixteen entries
    /* 0x00 */ s8 unk_00;
    /* 0x01 */ char pad01[3];
    /* 0x04 */ s32 unk_04; // flags
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ char pad0B[1];
    /* 0x0C */ s16 unk_0C; // hmf model index
    /* 0x0E */ s16 unk_0E; // frame count
    /* 0x10 */ s16 unk_10; // current frame
    /* 0x12 */ s16 unk_12; // frame tick
    /* 0x14 */ s16 unk_14; // ticks per frame
    /* 0x16 */ char pad16[2];
    /* 0x18 */ f32 *unk_18;
    /* 0x1C */ f32 *unk_1C;
    /* 0x20 */ f32 *unk_20;
} UnkPuddlePaddleEntry; // size = 0x24

typedef struct UnkPuddlePaddleObj { // size = 0x14, eight entries
    /* 0x00 */ PuddlePaddleSlot *unk_00;
    /* 0x04 */ PuddlePaddleHandler *unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ char pad0A[2];
    /* 0x0C */ PuddlePaddleOrder *unk_0C;
    /* 0x10 */ s8 unk_10;
    /* 0x11 */ char pad11[3];
} UnkPuddlePaddleObj;

typedef struct UnkPuddlePaddleModel { // size = 0x28, sixteen entries
    /* 0x00 */ s8 unk_00;
    /* 0x01 */ char pad01[3];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s8 unk_08;
    /* 0x09 */ char pad09[1];
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ char pad0E[2];
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ Vec unk_1C;
} UnkPuddlePaddleModel; // size = 0x28

typedef struct UnkPuddlePaddleSpr { // size = 0x8, twenty entries
    /* 0x00 */ s8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ char pad03[1];
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
} UnkPuddlePaddleSpr;

typedef struct PuddlePaddlePlane {
    /* 0x00 */ Vec normal;
    /* 0x0C */ f32 constant;
    /* 0x10 */ s8 axis;
    /* 0x11 */ char padding[3];
} PuddlePaddlePlane; // Size 0x14

typedef struct PuddlePaddleBoat { // 0xE4 bytes
    /* 0x00 */ s32 unk_00;        // flags
    /* 0x04 */ s8 unk_04;
    /* 0x05 */ char unk_05[3];
    /* 0x08 */ f32 *x;
    /* 0x0C */ f32 *y;
    /* 0x10 */ f32 *z;
    /* 0x14 */ f32 *rx;
    /* 0x18 */ f32 *ry;
    /* 0x1C */ f32 *rz;
    /* 0x20 */ HuMtx4F matrix;
    /* 0x60 */ Vec vertices[4];
    /* 0x90 */ Vec transformed[4];
    /* 0xC0 */ s16 vertexCount;
    /* 0xC2 */ char unk_C2[2];
    /* 0xC4 */ f32 unk_C4;
    /* 0xC8 */ PuddlePaddlePlane plane;
    /* 0xDC */ f32 unk_DC;
    /* 0xE0 */ s16 source;
    /* 0xE2 */ char unk_E2[2];
} PuddlePaddleBoat; // Size 0xE4

typedef struct PuddlePaddleShip { // 0x34 bytes
    /* 0x00 */ s32 unk_00;        // flags
    /* 0x04 */ s16 *unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ char unk_0A[2];
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec facing;
    /* 0x24 */ f32 unk_24; // radius
    /* 0x28 */ s16 unk_28; // hmf model index
    /* 0x2A */ s16 unk_2A;
    /* 0x2C */ s16 unk_2C;
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ s16 unk_30;
    /* 0x32 */ char unk_32[2];
} PuddlePaddleShip; // Size 0x34

typedef struct PuddlePaddlePlayer {
    /* 0x00 */ s16 unk_00; // player index
    /* 0x02 */ char unk_02[2];
    /* 0x04 */ s32 unk_04; // flags
    /* 0x08 */ s8 unk_08;
    /* 0x09 */ char unk_09;
    /* 0x0A */ s16 unk_0A; // current motion
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E; // queued motion
    /* 0x10 */ s8 unk_10;
    /* 0x11 */ s8 unk_11;
    /* 0x12 */ char unk_12[0x3A];
    /* 0x4C */ f32 unk_4C; // paddle power
    /* 0x50 */ s16 team;
    /* 0x52 */ s16 unk_52;
    /* 0x54 */ s16 unk_54;
    /* 0x56 */ s16 unk_56; // won
    /* 0x58 */ s16 unk_58;
    /* 0x5A */ char unk_5A[2];
} PuddlePaddlePlayer; // Size 0x5C

typedef struct PuddlePaddleTeam {
    /* 0x00 */ char unk_00[0x20];
    /* 0x20 */ s8 count;
    /* 0x21 */ char unk_21;
    /* 0x22 */ s16 players[2];
    /* 0x26 */ s16 tensSprite;
    /* 0x28 */ s16 onesSprite;
    /* 0x2A */ s16 score;
    /* 0x2C */ s16 unk_2C; // human player
    /* 0x2E */ char unk_2E[0x36];
} PuddlePaddleTeam; // Size 0x64

typedef struct PuddlePaddlePositions {
    /* 0x00 */ Vec points[2];
} PuddlePaddlePositions; // Size 0x18

typedef struct PuddlePaddleItem {
    /* 0x00 */ s16 type;
    /* 0x02 */ s16 model;
    /* 0x04 */ u8 state;
    /* 0x05 */ char unk_05[3];
    /* 0x08 */ Vec velocity;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ s16 timer;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ char unk_1E[6];
    /* 0x24 */ f32 spin;
    /* 0x28 */ f32 spinSpeed;
    /* 0x2C */ char unk_2C[8];
} PuddlePaddleItem; // Size 0x34

typedef struct PuddlePaddleGame {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ f32 timer;
    /* 0x08 */ char unk_08[0x30];
    /* 0x38 */ PuddlePaddleItem *items;
    /* 0x3C */ char unk_3C[4];
    /* 0x40 */ s16 unk_40;
    /* 0x42 */ char unk_42[2];
} PuddlePaddleGame; // Size 0x44

extern s16 D_800CDD6A_main;
extern u8 D_800D2008_main;

extern UnkPuddlePaddleEntry *D_80111668_puddle_paddle;
extern UnkPuddlePaddleModel *D_80111660_puddle_paddle;
extern UnkPuddlePaddleSpr *D_80111664_puddle_paddle;
extern UnkPuddlePaddleObj *D_8011166C_puddle_paddle;
extern PuddlePaddleBoat *D_80111670_puddle_paddle;
extern PuddlePaddleTeam *D_80111650_puddle_paddle;
extern PuddlePaddlePlayer *D_80111654_puddle_paddle;
extern PuddlePaddleGame *D_80111658_puddle_paddle;

extern u8 D_800D6A90_main;

extern f32 D_80111220_puddle_paddle;
extern f32 D_80111224_puddle_paddle;
extern f32 D_80111228_puddle_paddle;
extern s16 D_8011122E_puddle_paddle;
extern s16 D_80111230_puddle_paddle;
extern s16 D_80111232_puddle_paddle;
extern s16 D_80111234_puddle_paddle;

extern PuddlePaddlePositions D_80111614_puddle_paddle;

extern Gfx D_80111330_puddle_paddle[];

extern const s16 D_80111370_puddle_paddle[];
extern const s16 D_8011137C_puddle_paddle[];
extern const s16 D_8011138C_puddle_paddle[];

void func_801059BC_puddle_paddle(void);
void func_80105B94_puddle_paddle(void);
void func_80105C3C_puddle_paddle(omObjData *object);
void func_80105CE0_puddle_paddle(void);
void func_80105DBC_puddle_paddle(omObjData *object);
void func_80106028_puddle_paddle(omObjData *object);
void func_80106064_puddle_paddle(omObjData *object);
void func_80106988_puddle_paddle(omObjData *object);
void func_80106CE4_puddle_paddle(omObjData *object);
void func_801073E4_puddle_paddle(omObjData *object);
void func_801075B8_puddle_paddle(void);
void func_80107638_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_801079D4_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_80107B2C_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_8010788C_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_80107588_puddle_paddle(omObjData *object);
void func_80107DB0_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_80109804_puddle_paddle(PuddlePaddlePlayer *arg0, s16 arg1, u8 arg2);
void func_80109BD4_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_801091F8_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_8010981C_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_80108E2C_puddle_paddle(s16 index, s16 type, f32 angle, f32 pitch, s16 model);
s16 func_8010910C_puddle_paddle(s16 type);
void func_8010A224_puddle_paddle(void);
void func_80108D10_puddle_paddle(void);
s16 func_8010C42C_puddle_paddle(s16 type);
s32 func_8010C4D0_puddle_paddle(s16 index, f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 scale, f32 delay);
void func_80110BBC_puddle_paddle(f32 *angle, f32 *target);
void func_8010A398_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_8010ABCC_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_8010B574_puddle_paddle(void);
void func_8010B820_puddle_paddle(void);
UnkPuddlePaddleObj *func_8010B8B4_puddle_paddle(omObjData *object, s8 index, s16 count, s16 handlers);
s16 func_8010BA04_puddle_paddle(s8 index, s32 priority, void *data, void (*callback)(), s8 tag);
void func_8010C16C_puddle_paddle(void);
s16 func_8010C98C_puddle_paddle(s16 type);
void func_8010CA30_puddle_paddle(s16 index, f32 x, f32 y, f32 z);
void func_8010C664_puddle_paddle(void);
void func_8010CCF0_puddle_paddle(void);

void func_80105C84_puddle_paddle(omObjData *object);
void func_80105CBC_puddle_paddle(omObjData *object);
void func_801069FC_puddle_paddle(omObjData *object);
void func_8010BAA8_puddle_paddle(s8 arg0, PuddlePaddleHandler *arg1);
void func_8010BD18_puddle_paddle(UnkPuddlePaddleObj *group);
void func_8010C088_puddle_paddle(s16 index, s16 x, s16 y);
void func_8010C11C_puddle_paddle(s16 arg0);
s16 func_8010CE74_puddle_paddle(HuSprite_Unk84_Struct *sprite, f32 alpha);
s16 func_8010D5E4_puddle_paddle(HuSprite_Unk84_Struct *sprite, f32 alpha);
s16 func_8010EFEC_puddle_paddle(HuSprite_Unk84_Struct *sprite, HmfData *hmf, f32 scale, u16 arg3, u16 arg4);
void func_8010EDE8_puddle_paddle(u16 model, HuSprite_Unk84_Struct *sprite, u16 frame);
s32 func_8010F80C_puddle_paddle(PuddlePaddleBoat *boat, PuddlePaddleShip *ship);
s32 func_8010F9FC_puddle_paddle(PuddlePaddleBoat *boat, PuddlePaddleShip *ship);
s32 func_8010FBD4_puddle_paddle(PuddlePaddleBoat *boat, PuddlePaddleShip *ship);
s16 func_8010FEC0_puddle_paddle(PuddlePaddleBoat *boat, Vec *point);
f32 func_801101E0_puddle_paddle(PuddlePaddleBoat *boat, Vec *point);
s32 func_80110284_puddle_paddle(PuddlePaddleBoat *boat, PuddlePaddleShip *ship);
f32 func_801104C8_puddle_paddle(PuddlePaddleShip *arg0, Vec *arg1, Vec *arg2);
void func_80110888_puddle_paddle(Vec *vertices, PuddlePaddlePlane *plane);
void func_80110D3C_puddle_paddle(f32 *mtx);
void func_8010BC14_puddle_paddle(s8 index);
void func_80110714_puddle_paddle(omObjData *object);

void func_801059A0_puddle_paddle(void) {
    func_801059BC_puddle_paddle();
}

void func_801059BC_puddle_paddle(void) {
    u8 camera;

    func_8001FE20_main(0x32);
    func_800142A0_main(0x30);
    omInitObjMan(0x32, 0);
    func_8004A208_main();
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -56.0f, 50.0f, 56.0f);
    func_8000B5F0_main(1);
    camera = func_8000B638_main();
    ScissorSet(camera, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camera, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 30.0f, 80.0f, 5000.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_8010B820_puddle_paddle();
    func_80105B94_puddle_paddle();
    omAddObj(0x3E8, 0, 0, -1, func_80105DBC_puddle_paddle);
    omAddObj(0x7D0, 0, 0, -1, func_80105C3C_puddle_paddle);
    func_80045010_main(D_80111370_puddle_paddle, 1);
    func_80045010_main(D_8011137C_puddle_paddle, 1);
    func_80045010_main(D_8011138C_puddle_paddle, 1);
}

void func_80105B94_puddle_paddle(void) {
    D_80111658_puddle_paddle = HuMemAllocTag(sizeof(PuddlePaddleGame), TAG_OVERLAY);
    memset(D_80111658_puddle_paddle, 0, sizeof(PuddlePaddleGame));
    D_80111658_puddle_paddle->items = HuMemAllocTag(16 * sizeof(PuddlePaddleItem), TAG_OVERLAY);
    memset(D_80111658_puddle_paddle->items, 0, 16 * sizeof(PuddlePaddleItem));
    D_80111654_puddle_paddle = HuMemAllocTag(4 * sizeof(PuddlePaddlePlayer), TAG_OVERLAY);
    memset(D_80111654_puddle_paddle, 0, 4 * sizeof(PuddlePaddlePlayer));
    D_80111650_puddle_paddle = HuMemAllocTag(2 * sizeof(PuddlePaddleTeam), TAG_OVERLAY);
    memset(D_80111650_puddle_paddle, 0, 2 * sizeof(PuddlePaddleTeam));
}

void func_80105C3C_puddle_paddle(omObjData *object) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        object->func = func_80105C84_puddle_paddle;
    }
}

void func_80105C84_puddle_paddle(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = func_80105CBC_puddle_paddle;
    }
}

void func_80105CBC_puddle_paddle(omObjData *object) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_80105CE0_puddle_paddle(void) {
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
    func_8010BC14_puddle_paddle(0);
}

void func_80105DBC_puddle_paddle(omObjData *object) {
    s16 i;
    PuddlePaddleTeam *team;

    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    func_8010B8B4_puddle_paddle(NULL, 0, 0, 4);
    func_8010BA04_puddle_paddle(0, 0, 0, func_801075B8_puddle_paddle, 0);
    object->work[1] = 1;
    func_8010B8B4_puddle_paddle(object, (s8)object->work[1], 0, 4);
    D_800EC1C0_minigame[0] = omAddObj(10, 1, 2, -1, func_80106064_puddle_paddle);
    D_800EC1C0_minigame[1] = omAddObj(10, 1, 0, -1, func_80106988_puddle_paddle);
    omSetStatBit(D_800EC1C0_minigame[1], OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    for (i = 0; i < 4; i++) {
        team = &D_80111650_puddle_paddle[D_80111654_puddle_paddle[i].team = GwPlayer[i].group];
        D_80111654_puddle_paddle[i].unk_10 = team->count;
        team->players[team->count++] = i;
    }
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[i] = omAddObj(300, 11, 42, -1, func_80106CE4_puddle_paddle);
    }
    omAddObj(500, 2, 0, -1, func_801073E4_puddle_paddle);
    D_80111658_puddle_paddle->unk_00 = 1;
    func_8010BA04_puddle_paddle((s8)object->work[1], 0xF, 0, func_801079D4_puddle_paddle, 0);
    func_8010BA04_puddle_paddle((s8)object->work[1], 0x1F, 0, func_80107638_puddle_paddle, 0);
    WipeCreateIn(WIPE_TYPE_PREV, 20);
    object->func = func_80106028_puddle_paddle;
}

void func_80106028_puddle_paddle(omObjData *object) {
    func_8010BC14_puddle_paddle((s8)object->work[1]);
    func_80105CE0_puddle_paddle();
    func_8010C16C_puddle_paddle();
    func_8010C664_puddle_paddle();
    func_8010CCF0_puddle_paddle();
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80106064_puddle_paddle);

void func_80106958_puddle_paddle(omObjData *object) {
    func_8010BC14_puddle_paddle(2);
    func_80110714_puddle_paddle(object);
}

void func_80106988_puddle_paddle(omObjData *object) {
    object->model[0] = func_8000B108_main(0x320001, 0x20099);
    Hu3DModelPosSet(object->model[0], 0.0f, 200.0f, 0.0f);
    func_8001C954_main(object->model[0]);
    func_80110714_puddle_paddle(object);
    object->func = func_801069FC_puddle_paddle;
}

void func_801069FC_puddle_paddle(omObjData *object) {
    func_8001E65C_main(object->model[0], sindf(D_80111220_puddle_paddle) * 15.0f, -D_80111224_puddle_paddle, 64, 64);
    if (omPauseChk() + D_800D6A90_main == 0) {
        D_80111220_puddle_paddle += 0.5f;
        if (D_80111220_puddle_paddle >= 360.0f) {
            D_80111220_puddle_paddle -= 360.0f;
        }
        D_80111224_puddle_paddle += 0.2f;
        if (D_80111224_puddle_paddle >= 64.0f) {
            D_80111224_puddle_paddle -= 64.0f;
        }
        D_80111228_puddle_paddle += 2.4f;
        if (D_80111228_puddle_paddle >= 360.0f) {
            D_80111228_puddle_paddle -= 360.0f;
        }
    }
    func_80110714_puddle_paddle(object);
}

void func_80106B6C_puddle_paddle(s16 srcModel, s16 dstModel, u16 dstObj) {
    HmfData *dst = Hu3DData[dstModel].hmf;
    HmfData *src = Hu3DData[srcModel].hmf;
    s16 srcObj = 0;
    s16 i, j;

    if (dst->unk80 == (HmfMotionNode *)-1) {
        for (i = 0; i < dst->unk64; i++) {
            HmfSkeletonNode *skel = &dst->unk68[i];

            if (skel->unk00 == dstObj) {
                skel->unk48 = src;
                skel->unk00 = srcObj;
            }
        }
    } else {
        for (i = 0; i < dst->unk16; i++) {
            HmfMotionNode *node = &dst->unk80[i];

            for (j = 0; j < node->unk00; j++) {
                if (node->unk50[j] == dstObj) {
                    node->unk54 = src;
                    node->unk50[j] = srcObj;
                    break;
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80106CE4_puddle_paddle);

void func_801073AC_puddle_paddle(omObjData *object) {
    func_8010BC14_puddle_paddle(object->work[1]);
    func_800E4E30_minigame(object);
    func_80110714_puddle_paddle(object);
}

void func_801073E4_puddle_paddle(omObjData *object) {
    s32 flags = 0x99;
    PuddlePaddlePositions positions = D_80111614_puddle_paddle;
    PuddlePaddleSlot *slot;
    s16 i;

    object->work[1] = 7;
    slot = func_8010B8B4_puddle_paddle(object, (s8)object->work[1], 2, 6)->unk_00;
    for (i = 0; i < 2; i++) {
        slot->unk_04[i] = func_8000B108_main(0x320002, flags);
        Hu3DModelPosSet(slot->unk_04[i], positions.points[i].x, positions.points[i].y, positions.points[i].z);
    }
    func_8010BA04_puddle_paddle((s8)object->work[1], 0xFF, 0, func_8010A398_puddle_paddle, 0);
    func_8010BA04_puddle_paddle((s8)object->work[1], 0xFFF, 0, func_80109BD4_puddle_paddle, 0);
    func_8010BA04_puddle_paddle((s8)object->work[1], 0x1FFF, 0, func_8010A224_puddle_paddle, 0);
    func_8010BA04_puddle_paddle((s8)object->work[1], 0xFFFF, 0, func_8010ABCC_puddle_paddle, 0);
    object->model[0] = slot->unk_04[0];
    func_80110714_puddle_paddle(object);
    object->func = func_80107588_puddle_paddle;
}

void func_80107588_puddle_paddle(omObjData *object) {
    func_8010BC14_puddle_paddle(object->work[1]);
    func_80110714_puddle_paddle(object);
}

void func_801075B8_puddle_paddle(void) {
    // The original call omits the buffer argument.
    void (*initBuffer)() = (void (*)())func_8010BAA8_puddle_paddle;

    Center.x = 0.0f;
    Center.y = 280.0f;
    Center.z = 102.0f;
    CRot.x = 321.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2970.0f;
    initBuffer(0);
}

void func_80107638_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    s16 i;
    s16 score;
    s16 tens, ones;

    for (i = 0; i < 2; i++) {
        score = D_80111650_puddle_paddle[i].score;
        if (score < 100) {
            ones = score % 10;
            tens = score * 0.1f;
            if (tens != 0) {
                func_8010C088_puddle_paddle(D_80111650_puddle_paddle[i].tensSprite, i * 160 + 104, 32);
            } else {
                func_8010C11C_puddle_paddle(D_80111650_puddle_paddle[i].tensSprite);
            }
            func_80054FF8_main(D_80111664_puddle_paddle[D_80111650_puddle_paddle[i].tensSprite].unk_01, 0, tens);
            func_80054FF8_main(D_80111664_puddle_paddle[D_80111650_puddle_paddle[i].onesSprite].unk_01, 0, ones);
        } else {
            func_80054FF8_main(D_80111664_puddle_paddle[D_80111650_puddle_paddle[i].tensSprite].unk_01, 0, 9);
            func_80054FF8_main(D_80111664_puddle_paddle[D_80111650_puddle_paddle[i].onesSprite].unk_01, 0, 9);
        }
    }
}

// NON_MATCHING: code matches, but the 30.0 double literal lives at D_80111630, which the
// splat config currently places in .data instead of the start of this file's .rodata.
#ifdef NON_MATCHING
void func_8010788C_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    if (handler->unk_04 == 0) {
        D_80111658_puddle_paddle->timer = 900.0f;
        GMesCreate(26, D_80111658_puddle_paddle->timer / 30.0f, 160, 28);
        handler->unk_04 = 1;
    }
    D_80111658_puddle_paddle->timer -= 1.0f;
    func_8003F578_main((s16)((D_80111658_puddle_paddle->timer + 29.0f) * (1.0f / 30.0f)));
    if (D_80111658_puddle_paddle->timer < 0.0f) {
        D_80111658_puddle_paddle->unk_00 = 4;
        HuAudSeqFadeOut(120);
        GMesCreate(16);
        func_8003F5C0_main();
        func_8010BA04_puddle_paddle((s8)slot->unk_00->work[1], 0, 0, func_80107B2C_puddle_paddle, 0);
        func_8010BAA8_puddle_paddle((s8)slot->unk_00->work[1], handler);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010788C_puddle_paddle);
#endif

void func_801079D4_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    s32 status;

    switch (++handler->unk_1C[0]) {
        case 5:
            HuAudFXPlay(0x374);
            break;
        case 30:
            GMesCreate(5);
            HuAudFXPlay(14);
            break;
        case 50:
            D_8011122E_puddle_paddle = 1;
            break;
        default:
            if (D_8011122E_puddle_paddle == 1 && (status = GMesStatGet()) == 2) {
                func_8010B574_puddle_paddle();
                func_8010BA04_puddle_paddle((s8)slot->unk_00->work[1], 0xF, 0, func_8010788C_puddle_paddle, 0);
                D_80111658_puddle_paddle->unk_00 = status;
                func_8010BAA8_puddle_paddle((s8)slot->unk_00->work[1], handler);
            }
            break;
    }
    if (D_80111230_puddle_paddle == 0 && GMesStatGet() != 0) {
        HuAudSeqPlay(0x30);
        D_80111230_puddle_paddle = 1;
    }
}

void func_80107B2C_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    s16 won[2];
    s16 i, j;

    if (GMesStatGet() == 0) {
        D_80111232_puddle_paddle = 1;
    }
    if (D_80111232_puddle_paddle == 0) {
        return;
    }
    switch (++handler->unk_1C[0]) {
        case 15:
            won[0] = won[1] = 0;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 2; j++) {
                    if (D_80111654_puddle_paddle[D_80111650_puddle_paddle[i].players[j]].unk_56 != 0) {
                        func_80109804_puddle_paddle(&D_80111654_puddle_paddle[D_80111650_puddle_paddle[i].players[j]], 13, 1);
                        func_8004AC98_main(GwPlayer[D_80111650_puddle_paddle[i].players[j]].chr + 0x290,
                                           D_80111650_puddle_paddle[i].players[j]);
                        D_80111654_puddle_paddle[D_80111650_puddle_paddle[i].players[j]].unk_58 = -1;
                        D_80111654_puddle_paddle[D_80111650_puddle_paddle[i].players[j]].unk_0E = -1;
                        won[i] = 1;
                    }
                }
            }
            if (won[0] != 0 && won[1] != 0) {
                HuAudSeqPlay(0x66);
            } else if (won[0] != 0 || won[1] != 0) {
                HuAudSeqPlay(0x65);
            } else {
                HuAudSeqPlay(0x6C);
            }
            break;
        case 140:
            func_8010BA04_puddle_paddle((s8)slot->unk_00->work[1], 0, 0, func_80107DB0_puddle_paddle, 0);
            func_8010BAA8_puddle_paddle((s8)slot->unk_00->work[1], handler);
            break;
    }
}

void func_80107DB0_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    switch (handler->unk_04) {
        case 0:
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            handler->unk_04 = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                omOvlReturnEx(1);
            }
            break;
    }
}

void func_80107E1C_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    HmfModel *model = &Hu3DData[slot->unk_04[0]];
    f32 angle, target;

    if (D_80111658_puddle_paddle->unk_00 & 1) {
        return;
    }
    if (D_80111658_puddle_paddle->unk_40 != 0) {
        return;
    }
    if (D_80111658_puddle_paddle->unk_00 & 4) {
        if (handler->unk_1C[0] != 0) {
            return;
        }
        angle = model->rot.y;
        target = 0.0f;
        func_80110BBC_puddle_paddle(&angle, &target);
        if (model->rot.y >= 360.0f) {
            model->rot.y -= 360.0f;
        } else if (model->rot.y < 0.0f) {
            model->rot.y += 360.0f;
        }
        if (ABS(model->rot.y) <= 2.0f) {
            handler->unk_1C[0] = 1;
        }
        if (angle - target > 0.0f) {
            model->rot.y -= 2.0f;
        } else if (angle - target < 0.0f) {
            model->rot.y += 2.0f;
        }
    } else {
        if (handler->unk_0C[0] == 0) {
            handler->unk_0C[0] = 1;
            handler->unk_2C[0] = rand16() % 361;
        }
        angle = model->rot.y;
        target = handler->unk_2C[0];
        func_80110BBC_puddle_paddle(&angle, &target);
        if (ABS(model->rot.y - handler->unk_2C[0]) < 5.0f) {
            handler->unk_0C[0] = 0;
        }
        if (angle - target > 0.0f) {
            model->rot.y -= 1.0f;
        } else if (angle - target < 0.0f) {
            model->rot.y += 1.0f;
        }
    }
}

void func_80108178_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    omObjData *object = slot->unk_00;
    f32 time;

    if (!(D_80111658_puddle_paddle->unk_00 & 2)) {
        handler->unk_1C[0] = 0;
    }
    if (handler->unk_04 == 0) {
        handler->unk_1C[0] = 0;
        handler->unk_1C[1] = 10;
        D_80111658_puddle_paddle->unk_40 = 0;
        handler->unk_04 = 1;
    }
    if (D_80111658_puddle_paddle->unk_40 == 0) {
        if (++handler->unk_1C[0] > handler->unk_1C[1]) {
            func_8001C5B4_main(slot->unk_04[0], object->motion[1]);
            Hu3DMotionSpeedSet(slot->unk_04[0], 2.0f);
            Hu3DMotionTimeSet(object->model[0], 0.0f);
            D_80111658_puddle_paddle->unk_40 = 1;
            handler->unk_1C[0] = 0;
            handler->unk_1C[1] = (f32)(rand16() % 61 + 40);
        }
        time = Hu3DData[object->model[0]].motTime;
        if (time >= D_800CCF58_main[Hu3DData[object->model[0]].motId].unk02) {
            func_8001C5B4_main(slot->unk_04[0], object->motion[0]);
            Hu3DMotionSpeedSet(slot->unk_04[0], 1.0f);
        }
    }
}

// NON_MATCHING: register allocation differs (the target spills `count` to the stack and
// hoists the inner loop's entry test).
#ifdef NON_MATCHING
void func_80108368_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    omObjData *object = slot->unk_00;
    f32 angles[5];
    f32 time;
    f32 angle;
    f32 pitch;
    s16 count;
    s16 chance;
    s16 type;
    s16 i, j;
    s32 overlap;

    if (D_80111658_puddle_paddle->unk_40 == 0) {
        return;
    }
    time = Hu3DData[object->model[0]].motTime;
    if ((time >= 30.0f) & (time <= 35.0f)) {
        D_80111658_puddle_paddle->unk_40 = 0;
        count = rand16() % 3 + 2;
        for (i = 0; i < count; i++) {
            chance = 65;
            if (D_80111234_puddle_paddle < 11) {
                chance = rand16() % 101;
            }
            pitch = rand16() % 41 + 30;
            do {
                if (i == 0) {
                    angle = angles[0] = Hu3DData[slot->unk_04[0]].rot.y;
                } else {
                    angle = angles[i] = rand16() % 360;
                }
                overlap = 0;
                for (j = 0; j < i; j++) {
                    if (i != j && ABS(angles[i] - angles[j]) < 45.0f) {
                        overlap = 1;
                    }
                }
            } while (overlap);
            type = 0;
            if (chance < 61) {
                D_80111234_puddle_paddle++;
            } else if (chance < 71) {
                D_80111234_puddle_paddle = 0;
                type = 1;
            } else if (chance < 101) {
                type = 2;
            }
            func_80108E2C_puddle_paddle(func_8010910C_puddle_paddle(type), type, angle, pitch, slot->unk_04[0]);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80108368_puddle_paddle);
#endif

void func_801087DC_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    PuddlePaddleItem *item = D_80111658_puddle_paddle->items;
    HmfModel *model;
    f32 t;
    s16 i;
    s16 index;

    for (i = 0; i < 16; i++, item++) {
        if (item->state == 0) {
            continue;
        }
        model = &Hu3DData[item->model];
        model->rot.x = CRot.x;
        model->rot.y = CRot.y;
        if (item->type == 2) {
            item->spin += item->spinSpeed;
            if (item->spin > 360.0f) {
                item->spin -= 360.0f;
            }
            if (item->spin < 0.0f) {
                item->spin += 360.0f;
            }
            func_80088910_main(Hu3DData[item->model].mtx, 0.0f, 0.0f, item->spin);
        }
        if (D_80111658_puddle_paddle->unk_00 & 4) {
            func_8010BA04_puddle_paddle((s8)slot->unk_00->work[1], 0xFFF, 0, func_80108D10_puddle_paddle, 0);
            func_8010BAA8_puddle_paddle((s8)slot->unk_00->work[1], handler);
            return;
        }
        switch (item->state) {
            case 1:
                model->pos.x += item->velocity.x;
                model->pos.y += item->velocity.y;
                model->pos.z += item->velocity.z;
                item->velocity.y = item->unk_14 - ++item->timer * 2.45f;
                if (model->pos.y < 170.0f) {
                    index = func_8010C42C_puddle_paddle(0);
                    if (index != -1) {
                        func_8010C4D0_puddle_paddle(index, model->pos.x, 170.0f, model->pos.z, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
                    }
                    if (item->type != 2) {
                        item->state = 2;
                        item->timer = 0;
                        item->velocity.y *= 0.25f;
                    } else {
                        item->timer = 0;
                        item->unk_1C = 3;
                        item->state = 4;
                        item->velocity.y = 2.45f;
                    }
                    switch (item->type) {
                        case 0:
                            HuAudFXPlay(0x376);
                            break;
                        case 1:
                            HuAudFXPlay(0x377);
                            break;
                        case 2:
                            HuAudFXPlay(0x37A);
                            break;
                    }
                }
                break;
            case 2:
                model->pos.y += item->velocity.y;
                item->velocity.y += 2.45f;
                if (model->pos.y >= 170.0f) {
                    item->state = 3;
                    item->velocity.y = model->pos.y;
                }
                break;
            case 3:
                t = item->timer / 50.0f;
                if (t > 1.0f) {
                    t = 1.0f;
                }
                model->pos.y = sindf(t * 180.0f) * 20.0f * 5.0f * 0.4f + item->velocity.y;
                if (++item->timer >= 51) {
                    item->timer = 0;
                }
                if (++item->unk_1C > item->unk_1A) {
                    item->timer = 0;
                    item->unk_1C = 3;
                    item->state = 4;
                    item->velocity.y = 2.45f * 1.5f;
                }
                break;
            case 4:
                if (++item->timer < item->unk_1C) {
                    func_8001C258_main(item->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                } else {
                    item->timer = 0;
                    func_8001C258_main(item->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                }
                model->pos.y -= item->velocity.y;
                if (model->pos.y < 0.0f) {
                    item->state = 0;
                    func_8001C258_main(item->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
                break;
        }
    }
}

void func_80108D10_puddle_paddle(void) {
    PuddlePaddleItem *item = D_80111658_puddle_paddle->items;
    HmfModel *model;
    s16 i;
    s16 index;

    for (i = 0; i < 16; i++, item++) {
        if (item->state == 0) {
            continue;
        }
        model = &Hu3DData[item->model];
        if (item->state == 5) {
            if (++item->timer >= 6) {
                func_8001C258_main(item->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                item->state = 0;
            }
        } else {
            item->state = 5;
            item->timer = 0;
            index = func_8010C98C_puddle_paddle(0);
            if (index != -1) {
                func_8010CA30_puddle_paddle(index, model->pos.x, model->pos.y - 20.0f, model->pos.z);
            }
        }
    }
}

void func_80108E2C_puddle_paddle(s16 index, s16 type, f32 angle, f32 pitch, s16 model) {
    PuddlePaddleItem *item;
    f32 speed;
    f32 dx, dz;

    if (index == -1) {
        return;
    }
    item = &D_80111658_puddle_paddle->items[index];
    speed = (rand16() % 6 + 20) * 0.01f;
    item->velocity.x = sindf(angle) * 20.0f * 5.0f * speed;
    item->velocity.z = cosdf(angle) * 20.0f * 5.0f * speed;
    item->unk_14 = item->velocity.y = sindf(pitch) * 20.0f * 5.0f * 0.3f;
    item->type = type;
    item->state = 1;
    item->timer = 0;
    item->unk_1C = 0;
    switch (type) {
        case 0:
            item->unk_1A = 250;
            break;
        case 1:
            item->unk_1A = 150;
            break;
        case 2:
            if (angle < 180.0f) {
                item->spinSpeed = -20.0f;
            } else {
                item->spinSpeed = 20.0f;
            }
            break;
    }
    dx = sindf(Hu3DData[model].rot.y) * 75.0f;
    dz = cosdf(Hu3DData[model].rot.y) * 75.0f;
    func_8001C258_main(item->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelPosSet(item->model, Hu3DData[model].pos.x + dx, Hu3DData[model].pos.y + 50.0f, Hu3DData[model].pos.z + dz);
}

s16 func_8010910C_puddle_paddle(s16 type) {
    s16 end = 0;
    s16 start = 0;
    s16 i;

    switch (type) {
        case 2:
            start += 4;
            end += 4;
        case 1:
            start += 8;
            end += 4;
        case 0:
            end += 8;
    }
    for (i = start; i < end; i++) {
        if (D_80111658_puddle_paddle->items[i].state == 0) {
            break;
        }
    }
    if (i == end) {
        return -1;
    }
    return i;
}

void func_801091F8_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    omObjData *object = slot->unk_00;
    PuddlePaddlePlayer *players[2]; // [0] = this CPU, [1] = the team's human player

    if (!(D_80111658_puddle_paddle->unk_00 & 2)) {
        return;
    }
    players[0] = (PuddlePaddlePlayer *)handler->unk_3C;
    players[1] = &D_80111654_puddle_paddle[D_80111650_puddle_paddle[players[0]->team].unk_2C];
    if (handler->unk_04 == 0) {
        switch (GwPlayer[object->work[0]].cpu_difficulty) {
            case 0:
                handler->unk_0C[0] = 4;
                handler->unk_0C[1] = 8;
                players[0]->unk_52 = 20;
                players[0]->unk_54 = 15;
                break;
            case 1:
                handler->unk_0C[0] = 4;
                handler->unk_0C[1] = 7;
                players[0]->unk_52 = 30;
                players[0]->unk_54 = 13;
                break;
            case 2:
                handler->unk_0C[0] = 3;
                handler->unk_0C[1] = 6;
                players[0]->unk_52 = 40;
                players[0]->unk_54 = 11;
                break;
            case 3:
                handler->unk_0C[0] = 3;
                handler->unk_0C[1] = 5;
                players[0]->unk_52 = 99;
                players[0]->unk_54 = 9;
                break;
        }
        handler->unk_04 = 1;
    }
    D_800CBB6E_main[players[0]->unk_00] = 0;
    D_800D20A1_main[players[0]->unk_00] = 0;
    D_800CDA7C_main[players[0]->unk_00] = 0;
    if (object->work[0] == D_80111650_puddle_paddle[players[0]->team].unk_2C || (players[1]->unk_04 & 8)) {
        if (++handler->unk_1C[0] > handler->unk_1C[1]) {
            handler->unk_1C[0] = 0;
            handler->unk_1C[1] = rand16() % (handler->unk_0C[1] - handler->unk_0C[0] + 1) + handler->unk_0C[0];
            ((u16 *)D_800CDA7C_main)[players[0]->unk_00] = A_BUTTON;
        }
    }
}

void func_801094C4_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    PuddlePaddlePlayer *player = (PuddlePaddlePlayer *)handler->unk_3C;
    s16 stickX;

    player->unk_04 &= ~6;
    if (player->unk_04 & 0x10) {
        return;
    }
    if (D_80111658_puddle_paddle->unk_00 & 2) {
        if (++handler->unk_0C[2] >= 7) {
            handler->unk_0C[2] = 6;
            player->unk_04 &= ~8;
        }
        if ((u16)D_800CDA7C_main[player->unk_00] & A_BUTTON) {
            if (handler->unk_0C[0] == 0) {
                handler->unk_0C[0] = 1;
                handler->unk_0C[2] = 0;
                player->unk_4C += 0.05f;
                player->unk_04 |= 8;
                if (player->unk_4C > 1.0f) {
                    player->unk_4C = 1.0f;
                }
            }
        } else {
            handler->unk_0C[0] = 0;
        }
        if (handler->unk_0C[1] == 0) {
            handler->unk_0C[1] = 1;
            player->unk_4C -= sindf(player->unk_4C * 90.0f) * 0.025f;
            if (player->unk_4C < 0.0f) {
                player->unk_4C = 0.0f;
            }
        } else {
            handler->unk_0C[1] = 0;
        }
        stickX = D_800CBB6E_main[player->unk_00];
        if ((stickX == 0) & (D_800D20A1_main[player->unk_00] == 0)) {
            return;
        }
        if (stickX < -7) {
            player->unk_04 |= 4;
        } else if (stickX >= 8) {
            player->unk_04 |= 2;
        }
    } else {
        player->unk_04 &= ~8;
        if (handler->unk_0C[1] == 0) {
            handler->unk_0C[1] = 1;
            player->unk_4C -= sindf(player->unk_4C * 90.0f) * 0.1f;
            if (player->unk_4C < 0.0f) {
                player->unk_4C = 0.0f;
            }
        } else {
            handler->unk_0C[1] = 0;
        }
    }
}

void func_80109718_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    PuddlePaddlePlayer *player = (PuddlePaddlePlayer *)handler->unk_3C;
    omObjData *object = slot->unk_00;
    HmfModel *model = &Hu3DData[object->model[0]];

    if (player->unk_58 == 1) {
        return;
    }
    if (model->motTime >= D_800CCF58_main[model->motId].unk02 - 1) {
        player->unk_08 = 1;
    }
    if (player->unk_08 != 0) {
        func_800E5690_minigame(object, player->unk_0A);
        player->unk_08 = 0;
        if (player->unk_58 == -1) {
            player->unk_58 = 1;
        }
        if (player->unk_0E != -1) {
            player->unk_0A = player->unk_0E;
            player->unk_0E = -1;
        }
    }
}

void func_80109804_puddle_paddle(PuddlePaddlePlayer *arg0, s16 arg1, u8 arg2) {
    arg0->unk_08 = arg2;
    arg0->unk_0A = arg0->unk_0C = arg1;
}

void func_80109814_puddle_paddle(PuddlePaddlePlayer *arg0, s16 arg1) {
    arg0->unk_0E = arg1;
}

// NON_MATCHING: the target keeps `closest` in a stack slot and computes dist/angle in $f12.
#ifdef NON_MATCHING
void func_8010981C_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    PuddlePaddleTeam *team = (PuddlePaddleTeam *)handler->unk_3C;
    PuddlePaddleItem *item = D_80111658_puddle_paddle->items;
    PuddlePaddlePlayer *player = &D_80111654_puddle_paddle[team->unk_2C];
    HmfModel *models[2]; // [0] = boat, [1] = item
    Vec boatPos;
    Vec itemPos;
    Vec diff;
    f32 minDist;
    f32 distSq;
    f32 dist;
    f32 angle;
    s16 closest;
    s16 i;

    player->unk_04 &= ~6;
    if (player->unk_04 & 0x10) {
        return;
    }
    if (!(D_80111658_puddle_paddle->unk_00 & 2)) {
        return;
    }
    models[0] = &Hu3DData[slot->unk_04[handler->unk_05]];
    boatPos.x = models[0]->pos.x;
    boatPos.y = models[0]->pos.y;
    boatPos.z = models[0]->pos.z;
    minDist = 9999.0f;
    closest = -1;
    for (i = 0; i < 16; i++, item++) {
        if (item->state == 3 && item->type != 2) {
            models[1] = &Hu3DData[item->model];
            itemPos.x = models[1]->pos.x;
            itemPos.y = models[1]->pos.y;
            itemPos.z = models[1]->pos.z;
            diff.x = itemPos.x - boatPos.x;
            diff.y = itemPos.y - boatPos.y;
            diff.z = itemPos.z - boatPos.z;
            distSq = diff.x * diff.x + diff.z * diff.z;
            if (distSq == 0.0f) {
                dist = 0.0f;
            } else {
                dist = HuSqrtf(distSq);
            }
            if (dist < minDist) {
                minDist = dist;
                closest = i;
            }
        }
    }
    if (closest == -1) {
        return;
    }
    models[1] = &Hu3DData[D_80111658_puddle_paddle->items[closest].model];
    itemPos.x = models[1]->pos.x;
    itemPos.y = models[1]->pos.y;
    itemPos.z = models[1]->pos.z;
    diff.x = itemPos.x - boatPos.x;
    diff.z = itemPos.z - boatPos.z;
    angle = atan2df(-diff.z, diff.x) + 90.0f;
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    if (angle > 360.0f) {
        angle -= 360.0f;
    }
    diff.x = models[0]->rot.y;
    diff.y = angle;
    func_80110BBC_puddle_paddle(&diff.x, &diff.y);
    if (ABS(diff.x - diff.y) < 6.0f) {
        return;
    }
    if (diff.x - diff.y > 0.0f) {
        player->unk_04 |= 2;
    } else if (diff.x - diff.y < 0.0f) {
        player->unk_04 |= 4;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010981C_puddle_paddle);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80109BD4_puddle_paddle);

void func_8010A224_puddle_paddle(void) {
    PuddlePaddleTeam *team = D_80111650_puddle_paddle;
    PuddlePaddlePlayer *player;
    omObjData *object;
    s16 i, j;
    s16 index;

    for (i = 0; i < 2; i++, team++) {
        for (j = 0; j < 2; j++) {
            index = team->players[j];
            player = &D_80111654_puddle_paddle[index];
            object = D_800EC598_minigame[index];
            if (!(player->unk_04 & 0x10)) {
                continue;
            }
            if (++player->unk_10 < 3) {
                func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            } else {
                player->unk_10 = 0;
                func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            if (++player->unk_11 >= 21) {
                func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                player->unk_04 &= ~0x10;
                player->unk_11 = 0;
                player->unk_10 = 0;
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010A398_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010ABCC_puddle_paddle);

void func_8010B574_puddle_paddle(void) {
    PuddlePaddleTeam *team = D_80111650_puddle_paddle;
    s16 isCpu[2];
    s16 difficulty[2];
    s16 i, j;
    s16 index;

    for (i = 0; i < 2; i++, team++) {
        isCpu[0] = GwPlayer[D_80111650_puddle_paddle[i].players[0]].stat & 1;
        isCpu[1] = GwPlayer[D_80111650_puddle_paddle[i].players[1]].stat & 1;
        if (isCpu[0] && isCpu[1]) {
            difficulty[0] = GwPlayer[team->players[0]].cpu_difficulty;
            difficulty[1] = GwPlayer[team->players[1]].cpu_difficulty;
            if (difficulty[1] < difficulty[0]) {
                team->unk_2C = team->players[0];
            } else {
                team->unk_2C = team->players[1];
            }
            for (j = 0; j < 2; j++) {
                index = team->players[j];
                func_8010BA04_puddle_paddle(index + 3, 0, &D_80111654_puddle_paddle[index], func_801091F8_puddle_paddle, 0);
            }
            func_8010BA04_puddle_paddle(7, 0, &D_80111650_puddle_paddle[i], func_8010981C_puddle_paddle, i);
        } else if (isCpu[0] || isCpu[1]) {
            if (isCpu[0]) {
                team->unk_2C = team->players[1];
            } else {
                team->unk_2C = team->players[0];
            }
            for (j = 0; j < 2; j++) {
                index = team->players[j];
                if (index != team->unk_2C) {
                    func_8010BA04_puddle_paddle(index + 3, 0, &D_80111654_puddle_paddle[index], func_801091F8_puddle_paddle, 0);
                }
            }
        }
    }
}

void func_8010B820_puddle_paddle(void) {
    D_80111664_puddle_paddle = HuMemAllocTag(20 * sizeof(UnkPuddlePaddleSpr), TAG_OVERLAY);
    memset(D_80111664_puddle_paddle, 0, 20 * sizeof(UnkPuddlePaddleSpr));
    D_80111660_puddle_paddle = HuMemAllocTag(16 * sizeof(UnkPuddlePaddleModel), TAG_OVERLAY);
    memset(D_80111660_puddle_paddle, 0, 16 * sizeof(UnkPuddlePaddleModel));
    D_80111668_puddle_paddle = HuMemAllocTag(16 * sizeof(UnkPuddlePaddleEntry), TAG_OVERLAY);
    memset(D_80111668_puddle_paddle, 0, 16 * sizeof(UnkPuddlePaddleEntry));
    D_8011166C_puddle_paddle = HuMemAllocTag(8 * sizeof(UnkPuddlePaddleObj), TAG_OVERLAY);
}

UnkPuddlePaddleObj *func_8010B8B4_puddle_paddle(omObjData *object, s8 index, s16 count, s16 handlers) {
    UnkPuddlePaddleObj *group;

    if (index >= 8) {
        return NULL;
    }
    group = &D_8011166C_puddle_paddle[index];
    if (handlers != 0) {
        group->unk_04 = HuMemAllocTag(handlers * sizeof(PuddlePaddleHandler), TAG_OVERLAY);
        memset(group->unk_04, 0, handlers * sizeof(PuddlePaddleHandler));
        group->unk_0C = HuMemAllocTag((handlers + 1) * sizeof(PuddlePaddleOrder), TAG_OVERLAY);
    }
    group->unk_08 = handlers;
    group->unk_00 = HuMemAllocTag(sizeof(PuddlePaddleSlot), TAG_OVERLAY);
    if (count != 0) {
        group->unk_00->unk_04 = HuMemAllocTag(count * sizeof(s16), TAG_OVERLAY);
        memset(group->unk_00->unk_04, 0, count * sizeof(s16));
    }
    group->unk_00->unk_08 = count;
    group->unk_10 = 1;
    group->unk_00->unk_00 = object;
    return group;
}

s16 func_8010BA04_puddle_paddle(s8 index, s32 priority, void *data, void (*callback)(), s8 tag) {
    UnkPuddlePaddleObj *group = &D_8011166C_puddle_paddle[index];
    PuddlePaddleHandler *handler = group->unk_04;
    s16 i;
    s16 count = group->unk_08;

    for (i = 0; i < count; i++, handler++) {
        if (handler->unk_00 == 0) {
            handler->unk_00 = 1;
            handler->unk_08 = priority;
            handler->unk_02 = i;
            handler->unk_05 = tag;
            handler->unk_04 = 0;
            handler->unk_3C = data;
            handler->unk_40 = callback;
            break;
        }
    }
    group->unk_10 = 1;
    return i;
}

void func_8010BAA8_puddle_paddle(s8 arg0, PuddlePaddleHandler *arg1) {
    memset(arg1, 0, sizeof(PuddlePaddleHandler));
    D_8011166C_puddle_paddle[arg0].unk_10 = 1;
}

void func_8010BB00_puddle_paddle(s8 index, s8 tag) {
    UnkPuddlePaddleObj *group = &D_8011166C_puddle_paddle[index];
    PuddlePaddleHandler *handler = group->unk_04;
    s16 i;

    for (i = 0; i < group->unk_08; i++, handler++) {
        if (handler->unk_05 == tag) {
            func_8010BAA8_puddle_paddle(index, handler);
        }
    }
}

void func_8010BBB4_puddle_paddle(s8 arg0) {
    UnkPuddlePaddleObj *obj = &D_8011166C_puddle_paddle[arg0];

    memset(obj->unk_04, 0, obj->unk_08 * sizeof(PuddlePaddleHandler));
    obj->unk_10 = 1;
}

void func_8010BC14_puddle_paddle(s8 index) {
    UnkPuddlePaddleObj *group = &D_8011166C_puddle_paddle[index];
    PuddlePaddleHandler *handler;
    s8 i;

    if (group->unk_10 != 0) {
        func_8010BD18_puddle_paddle(group);
    }
    i = 0;
    while (group->unk_0C[i].next != -1) {
        i = group->unk_0C[i].next;
        handler = &group->unk_04[group->unk_0C[i].handler];
        if (handler->unk_00 != 0) {
            handler->unk_40(group->unk_00, handler);
        }
    }
}

void func_8010BD18_puddle_paddle(UnkPuddlePaddleObj *group) {
    PuddlePaddleOrder *order = group->unk_0C;
    PuddlePaddleHandler *handler = group->unk_04;
    s16 entry;
    s16 tail;
    s16 i;
    s16 insert;
    s16 current;
    s16 found;

    order[0].next = -1;
    entry = 1;
    tail = 0;
    for (i = 0; i < group->unk_08; i++, handler++) {
        if (handler->unk_00 != 0) {
            insert = tail;
            found = 0;
            current = 0;
            while (order[current].next != -1) {
                current = order[current].next;
                if ((u32)handler->unk_08 < order[current].priority) {
                    insert = current;
                    found = 1;
                    break;
                }
            }
            order[entry].handler = i;
            order[entry].priority = handler->unk_08;
            if (found != 0) {
                order[entry].next = order[order[insert].previous].next;
                order[entry].previous = order[insert].previous;
                order[order[insert].previous].next = entry;
                order[order[entry].next].previous = entry;
            } else {
                order[entry].next = order[insert].next;
                order[entry].previous = insert;
                order[insert].next = entry;
                tail = entry;
            }
            entry++;
        }
    }
    group->unk_10 = 0;
}

s16 func_8010BEE8_puddle_paddle(s16 priority, s32 directory, s32 file, u16 bank, s32 attr) {
    UnkPuddlePaddleSpr *sprite = D_80111664_puddle_paddle;
    HuSprite *data;
    s16 i;

    for (i = 0; i < 20; i++, sprite++) {
        if (sprite->unk_00 == 0) {
            sprite->unk_02 = func_8000B838_main((directory << 16) | file);
            sprite->unk_01 = HuSprGrpCreate(1, 0);
            sprite->unk_06 = 255;
            HuSprAttrReset(sprite->unk_01, 0, -1);
            HuSprGrpMemberSet(sprite->unk_01, 0, sprite->unk_02, 0);
            HuSprAttrSet(sprite->unk_01, 0, attr);
            func_800550F4_main(sprite->unk_01, 0, bank);
            HuSprPriSet(sprite->unk_01, 0, (u16)priority);
            func_80054FF8_main(sprite->unk_01, 0, 0);
            HuSprSpeedSet(sprite->unk_01, 0, 1.0f);
            HuSprScaleSet(sprite->unk_01, 0, 1.0f, 1.0f);
            HuSprPosSet(sprite->unk_01, 0, 100, 100);
            data = HuSprGet(sprite->unk_01, 0);
            if (bank == 0) {
                sprite->unk_04 = 99;
            } else {
                sprite->unk_04 = data->unk_84->unk10;
            }
            sprite->unk_00 = 2;
            func_8010C11C_puddle_paddle(i);
            break;
        }
    }
    return i;
}

void func_8010C088_puddle_paddle(s16 index, s16 x, s16 y) {
    UnkPuddlePaddleSpr *sprite = &D_80111664_puddle_paddle[index];

    if (sprite->unk_00 != 0) {
        func_80054FF8_main(sprite->unk_01, 0, 0);
        HuSprDispOn(sprite->unk_01, 0);
        HuSprPosSet(sprite->unk_01, 0, x, y);
        sprite->unk_00 = 2;
    }
}

void func_8010C11C_puddle_paddle(s16 arg0) {
    UnkPuddlePaddleSpr *spr = &D_80111664_puddle_paddle[arg0];

    if (spr->unk_00 != 0) {
        HuSprDispOff(spr->unk_01, 0);
        spr->unk_00 = 1;
    }
}

void func_8010C16C_puddle_paddle(void) {
    UnkPuddlePaddleSpr *sprite = D_80111664_puddle_paddle;
    s16 i;

    for (i = 0; i < 20; i++, sprite++) {
        if (sprite->unk_00 == 2) {
            if (HuSprGet(sprite->unk_01, 0)->unk_90 + 1 >= (u16)sprite->unk_04) {
                HuSprDispOff(sprite->unk_01, 0);
                func_80054FF8_main(sprite->unk_01, 0, 0);
            }
        }
    }
}

s16 func_8010C214_puddle_paddle(s32 directory, s32 file, f32 speed, s16 type, s32 flags, s32 attr) {
    UnkPuddlePaddleModel *work = D_80111660_puddle_paddle;
    HmfModel *model;
    s16 i;

    for (i = 0; i < 16; i++, work++) {
        if (work->unk_00 == 0) {
            work->unk_0C = func_8000B108_main((directory << 16) | file, attr);
            func_8001C258_main(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            model = &Hu3DData[work->unk_0C];
            model->motTime = 0;
            model->motSpeed = 0;
            if (model->hmf->unk98 != NULL) {
                model->hmf->unk98->unk08 = 0;
            }
            work->unk_0A = type;
            work->unk_04 = flags;
            work->unk_10 = speed;
            work->unk_08 = -1;
            work->unk_00 = 1;
            break;
        }
    }
    return i;
}

s16 func_8010C324_puddle_paddle(s16 arg0, f32 arg1, s16 arg2, s32 arg3) {
    UnkPuddlePaddleModel *work = D_80111660_puddle_paddle;
    HmfModel *model;
    s16 i;

    for (i = 0; i < 16; i++, work++) {
        if (work->unk_00 == 0) {
            work->unk_0C = Hu3DModelLink(arg0);
            func_8001C258_main(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            model = &Hu3DData[work->unk_0C];
            model->motTime = 0;
            model->motSpeed = 0;
            if (model->hmf->unk98 != NULL) {
                model->hmf->unk98->unk08 = 0;
            }
            work->unk_0A = arg2;
            work->unk_04 = arg3;
            work->unk_10 = arg1;
            work->unk_08 = -1;
            work->unk_00 = 1;
            break;
        }
    }
    return i;
}

s16 func_8010C42C_puddle_paddle(s16 type) {
    UnkPuddlePaddleModel *work = D_80111660_puddle_paddle;
    HmfModel *model;
    s16 i;

    for (i = 0; i < 16; i++, work++) {
        if (work->unk_00 != 0 && work->unk_0A == type) {
            model = &Hu3DData[work->unk_0C];
            if ((model->attr & HU3D_ATTR_DISPOFF) != 0 && work->unk_08 == -1) {
                break;
            }
        }
    }
    if (i == 16) {
        return -1;
    }
    return i;
}

s32 func_8010C4D0_puddle_paddle(s16 index, f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 scale, f32 delay) {
    UnkPuddlePaddleModel *work;
    HmfModel *model;

    if (index >= 16) {
        return 0;
    }
    if (D_80111660_puddle_paddle[index].unk_00 == 0) {
        return 0;
    }
    work = &D_80111660_puddle_paddle[index];
    model = &Hu3DData[work->unk_0C];
    if ((model->attr & HU3D_ATTR_DISPOFF) != 0 && work->unk_08 == -1) {
        Hu3DModelPosSet(work->unk_0C, x, y, z);
        Hu3DModelScaleSet(work->unk_0C, scale, scale, scale);
        work->unk_1C.x = rx;
        work->unk_1C.y = ry;
        work->unk_1C.z = rz;
        if (delay == 0.0f) {
            func_8001C258_main(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            work->unk_08 = 1;
            work->unk_18 = 0.0f;
            work->unk_14 = 0.0f;
            model->motSpeed = work->unk_10;
        } else {
            work->unk_08 = 0;
            work->unk_18 = delay;
            work->unk_14 = 0;
        }
        return 1;
    }
    return 0;
}

void func_8010C664_puddle_paddle(void) {
    UnkPuddlePaddleModel *work = D_80111660_puddle_paddle;
    HmfModel *model;
    s16 i;

    for (i = 0; i < 16; i++, work++) {
        if (work->unk_00 != 0 && work->unk_08 != -1) {
            model = &Hu3DData[work->unk_0C];
            func_80088910_main(model->mtx, work->unk_1C.x, work->unk_1C.y, work->unk_1C.z);
            if (work->unk_08 != 0) {
                if (model->motTime >= D_800CCF58_main[Hu3DData[work->unk_0C].motId].unk02) {
                    model->motTime = 0;
                    if (model->hmf->unk98 != NULL) {
                        model->hmf->unk98->unk08 = 0;
                    }
                    if (!(work->unk_04 & 1)) {
                        func_8001C258_main(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        work->unk_08 = -1;
                        model->motSpeed = 0;
                    }
                }
            } else {
                if (work->unk_14++ >= work->unk_18) {
                    func_8001C258_main(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    work->unk_08 = 1;
                    model->motSpeed = work->unk_10;
                }
            }
        }
    }
}

s16 func_8010C804_puddle_paddle(s32 directory, s32 file, s16 interval, s16 type, s32 flags) {
    UnkPuddlePaddleEntry *work = D_80111668_puddle_paddle;
    s16 frame;
    s16 i;

    for (i = 0; i < 16; i++, work++) {
        if (work->unk_00 == 0) {
            frame = func_8000B838_main((directory << 16) | file);
            work->unk_0A = frame;
            if (flags & 1) {
                work->unk_0C = func_8010D5E4_puddle_paddle(func_80055194_main(frame), 1.0f);
            } else {
                work->unk_0C = func_8010CE74_puddle_paddle(func_80055194_main(frame), 1.0f);
            }
            if (flags & 8) {
                func_8001C258_main(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            work->unk_18 = &Hu3DData[work->unk_0C].pos.x;
            work->unk_1C = &Hu3DData[work->unk_0C].pos.y;
            work->unk_20 = &Hu3DData[work->unk_0C].pos.z;
            work->unk_08 = type;
            work->unk_04 = flags;
            work->unk_0E = func_80055194_main(frame)->unk10;
            work->unk_10 = 0;
            work->unk_12 = 0;
            work->unk_14 = interval;
            work->unk_00 = 1;
            break;
        }
    }
    return i;
}

s16 func_8010C98C_puddle_paddle(s16 type) {
    UnkPuddlePaddleEntry *work = D_80111668_puddle_paddle;
    HmfModel *model;
    s16 i;

    for (i = 0; i < 16; i++, work++) {
        if (work->unk_00 != 0 && work->unk_08 == type) {
            model = &Hu3DData[work->unk_0C];
            if ((model->attr & HU3D_ATTR_DISPOFF) != 0 && (work->unk_04 & 8) != 0) {
                break;
            }
        }
    }
    if (i == 16) {
        return -1;
    }
    return i;
}

void func_8010CA30_puddle_paddle(s16 index, f32 x, f32 y, f32 z) {
    HmfModel *model;

    if (index < 16) {
        model = &Hu3DData[D_80111668_puddle_paddle[index].unk_0C];
        model->pos.x = x;
        model->pos.y = y;
        model->pos.z = z;
        func_8001C258_main(D_80111668_puddle_paddle[index].unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        D_80111668_puddle_paddle[index].unk_04 &= ~0x18;
    }
}

void func_8010CAD4_puddle_paddle(s16 index, f32 *x, f32 *y, f32 *z) {
    HmfModel *model;

    if (index < 16) {
        model = &Hu3DData[D_80111668_puddle_paddle[index].unk_0C];
        if (x != NULL) {
            D_80111668_puddle_paddle[index].unk_18 = x;
        } else {
            D_80111668_puddle_paddle[index].unk_18 = &model->pos.x;
        }
        if (y != NULL) {
            D_80111668_puddle_paddle[index].unk_1C = y;
        } else {
            D_80111668_puddle_paddle[index].unk_1C = &model->pos.y;
        }
        if (z != NULL) {
            D_80111668_puddle_paddle[index].unk_20 = z;
        } else {
            D_80111668_puddle_paddle[index].unk_20 = &model->pos.z;
        }
        func_8001C258_main(D_80111668_puddle_paddle[index].unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        D_80111668_puddle_paddle[index].unk_04 = (D_80111668_puddle_paddle[index].unk_04 & ~0x18) | 0x10;
    }
}

UnkPuddlePaddleEntry *func_8010CC64_puddle_paddle(s16 arg0) {
    UnkPuddlePaddleEntry *ret;

    if (arg0 < 0x10) {
        ret = &D_80111668_puddle_paddle[arg0];
    } else {
        ret = 0;
    }
    return ret;
}

HmfModel *func_8010CC9C_puddle_paddle(s16 arg0) {
    HmfModel *ret;

    if (arg0 < 0x10) {
        ret = &Hu3DData[D_80111668_puddle_paddle[arg0].unk_0C];
    } else {
        ret = 0;
    }
    return ret;
}

void func_8010CCF0_puddle_paddle(void) {
    UnkPuddlePaddleEntry *work = D_80111668_puddle_paddle;
    HmfModel *model;
    s16 i;

    for (i = 0; i < 16; i++, work++) {
        if (work->unk_00 != 0 && !(work->unk_04 & 8)) {
            model = &Hu3DData[work->unk_0C];
            if (work->unk_04 & 0x10) {
                model->pos.x = *work->unk_18;
                model->pos.y = *work->unk_1C;
                model->pos.z = *work->unk_20;
            }
            model->rot.x = CRot.x;
            model->rot.y = CRot.y;
            if (work->unk_04 & 1) {
                if (work->unk_04 & 2) {
                    if (++work->unk_12 > work->unk_14) {
                        work->unk_12 = 0;
                        func_8010EDE8_puddle_paddle(work->unk_0C, func_80055194_main(work->unk_0A), work->unk_10);
                        if (++work->unk_10 >= work->unk_0E) {
                            if (work->unk_04 & 4) {
                                work->unk_10 = 0;
                            } else {
                                work->unk_10 = 0;
                                work->unk_04 |= 8;
                                func_8001C258_main(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                            }
                        }
                    }
                }
            }
        }
    }
}

s16 func_8010CE74_puddle_paddle(HuSprite_Unk84_Struct *sprite, f32 alpha) {
    HmfData *hmf;
    Gfx *dlBuf;
    Gfx *gfx;
    u32 frameCount;
    s32 size;
    s32 frameSize;
    s16 model;
    s16 i;

    dlBuf = gfx = HuMemAlloc(0x10000);
    model = func_8001A894_main(0x4C1, dlBuf, 4);
    hmf = Hu3DData[model].hmf;
    hmf->unk60->unk50 |= 0x01010000;
    frameCount = func_8010EFEC_puddle_paddle(sprite, hmf, 1.0f, 0, 0x64);
    gSPDisplayList(gfx++, osVirtualToPhysical(D_80111330_puddle_paddle));
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_FRONT | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH);
    gDPSetColorDither(gfx++, G_CD_NOISE);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetTextureConvert(gfx++, G_TC_FILT);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 0x01, 0x01, 0x01, 0x01);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_ZB_XLU_SURF, G_RM_NOOP2);
    gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, alpha * 255.0f);
    gDPPipeSync(gfx++);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    if (sprite->unk1A >= 2) {
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
        frameSize = 0x800;
        if (sprite->unk18 == 4) {
            gDPLoadTLUT_pal16(gfx++, 0, sprite->unk0C);
        } else {
            gDPLoadTLUT_pal256(gfx++, sprite->unk0C);
        }
    } else {
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        frameSize = 0x1000;
    }
    gDPPipeSync(gfx++);
    for (i = 0; i < frameCount; i++) {
        gSPSegment(gfx++, 0x02, osVirtualToPhysical(sprite->unk08 + frameSize * i));
        gDPLoadTextureBlock(gfx++, 0x02000000, G_IM_FMT_CI, G_IM_SIZ_8b,
                            sprite->unk00->unk04, sprite->unk00->unk06 / frameCount, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 0x01, osVirtualToPhysical(&hmf->unk44[0][i * 4]));
        gSPVertex(gfx++, 0x01000000, 4, 0);
        gSP2Triangles(gfx++, 0, 1, 2, 0, 1, 3, 2, 0);
    }
    gSPClearGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u32)gfx - (u32)dlBuf;
    hmf->unk3C->unk00[0] = HuMemAllocTag(size, hmf->unk0E);
    bcopy(dlBuf, hmf->unk3C->unk00[0], size);
    HuMemFree(dlBuf);
    return model;
}

s16 func_8010D5E4_puddle_paddle(HuSprite_Unk84_Struct *sprite, f32 alpha) {
    HmfData *hmf;
    Gfx *dlBuf;
    Gfx *gfx;
    s32 size;
    s16 model;
    s16 format;
    s16 i;

    dlBuf = gfx = HuMemAlloc(0x10000);
    model = func_8001A894_main(0x4C1, dlBuf, 4);
    hmf = Hu3DData[model].hmf;
    hmf->unk60->unk50 |= 0x01010000;
    HuMemFree(hmf->unk3C);
    hmf->unk3C = HuMemAllocTag(0x14, D_800CDD6A_main);
    func_8010EFEC_puddle_paddle(sprite, hmf, 1.0f, 0, 0x1E);
    gSPDisplayList(gfx++, osVirtualToPhysical(D_80111330_puddle_paddle));
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_CULL_FRONT | G_TEXTURE_GEN_LINEAR);
    gDPSetColorDither(gfx++, G_CD_NOISE);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetTextureConvert(gfx++, G_TC_FILT);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 0x01, 0x01, 0x01, 0x01);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_ZB_XLU_SURF, G_RM_NOOP2);
    if (sprite->unk1A >= 2) {
        gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, alpha * 255.0f);
    } else {
        if (sprite->unk18 & 0x8000) {
            gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
        } else {
            gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        }
        gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, alpha * 255.0f);
    }
    gDPPipeSync(gfx++);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    if (sprite->unk1A >= 2) {
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
        if (sprite->unk18 == 4) {
            gDPLoadTLUT_pal16(gfx++, 0, sprite->unk0C);
        } else {
            gDPLoadTLUT_pal256(gfx++, sprite->unk0C);
        }
        gDPPipeSync(gfx++);
        format = 2;
    } else {
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        gDPPipeSync(gfx++);
        format = (sprite->unk18 & 0x8000) ? 4 : 0;
    }
    switch (sprite->unk18 & 0xFFF) {
        case 4:
            gDPLoadTextureBlock_4b(gfx++, 0x02000000, format,
                                   sprite->unk00->unk04, sprite->unk00->unk06, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 8:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_8b,
                                sprite->unk00->unk04, sprite->unk00->unk06, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 16:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_16b,
                                sprite->unk00->unk04, sprite->unk00->unk06, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
    gDPPipeSync(gfx++);
    gSPSegment(gfx++, 0x01, osVirtualToPhysical(hmf->unk44[0]));
    gSPVertex(gfx++, 0x01000000, 4, 0);
    gSP2Triangles(gfx++, 0, 1, 2, 0, 1, 3, 2, 0);
    gSPClearGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u32)gfx - (u32)dlBuf;
    hmf->unk3C->unk00[0] = hmf->unk3C->unk10 = HuMemAllocTag(size, hmf->unk0E);
    bcopy(dlBuf, hmf->unk3C->unk00[0], size);
    HuMemFree(dlBuf);
    for (i = 0; i < D_800D1FF0_main; i++) {
        gfx = *(hmf->unk3C->unk00 + (i + 1)) = HuMemAllocTag(0x100, hmf->unk0E);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 0x02, osVirtualToPhysical(sprite->unk00->unk00));
        gSPDisplayList(gfx++, osVirtualToPhysical(hmf->unk3C->unk10));
        gSPEndDisplayList(gfx++);
    }
    hmf->unk3C->unk00[0] = hmf->unk3C->unk00[D_800D2008_main + 1];
    return model;
}

s16 func_8010E1FC_puddle_paddle(HuSprite_Unk84_Struct *sprite, RGBA *color) {
    HmfData *hmf;
    Gfx *dlBuf;
    Gfx *gfx;
    s32 size;
    s32 model;
    s32 format;
    s32 i;

    dlBuf = gfx = HuMemAlloc(0x10000);
    model = func_8001A894_main(0x8C1, dlBuf, 4);
    hmf = Hu3DData[model].hmf;
    hmf->unk60->unk50 |= 0x01010000;
    HuMemFree(hmf->unk3C);
    hmf->unk3C = HuMemAllocTag(0x18, D_800CDD6A_main);
    func_8010EFEC_puddle_paddle(sprite, hmf, 1.0f, 0, 0);
    gSPDisplayList(gfx++, osVirtualToPhysical(D_80111330_puddle_paddle));
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_CULL_FRONT | G_TEXTURE_GEN_LINEAR);
    gDPSetColorDither(gfx++, G_CD_NOISE);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetTextureConvert(gfx++, G_TC_FILT);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 0x01, 0x01, 0x01, 0x01);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_ZB_XLU_SURF, G_RM_NOOP2);
    if (sprite->unk18 & 0x8000) {
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    } else {
        gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    }
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u32)gfx - (u32)dlBuf;
    hmf->unk3C->unk10 = HuMemAllocTag(size, hmf->unk0E);
    bcopy(dlBuf, hmf->unk3C->unk10, size);
    HuMemFree(dlBuf);
    dlBuf = gfx = HuMemAlloc(0x10000);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    if (sprite->unk1A >= 2) {
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
        if (sprite->unk18 == 4) {
            gDPLoadTLUT_pal16(gfx++, 0, sprite->unk0C);
        } else {
            gDPLoadTLUT_pal256(gfx++, sprite->unk0C);
        }
        gDPPipeSync(gfx++);
        format = 2;
    } else {
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        gDPPipeSync(gfx++);
        format = (sprite->unk18 & 0x8000) ? 4 : 0;
    }
    switch (sprite->unk18 & 0xFFF) {
        case 4:
            gDPLoadTextureBlock_4b(gfx++, 0x02000000, format,
                                   sprite->unk00->unk04, sprite->unk00->unk06, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 8:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_8b,
                                sprite->unk00->unk04, sprite->unk00->unk06, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 16:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_16b,
                                sprite->unk00->unk04, sprite->unk00->unk06, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
    gDPPipeSync(gfx++);
    gSPSegment(gfx++, 0x01, osVirtualToPhysical(hmf->unk44[0]));
    gSPVertex(gfx++, 0x01000000, 4, 0);
    gSP2Triangles(gfx++, 0, 1, 2, 0, 1, 3, 2, 0);
    gSPClearGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u32)gfx - (u32)dlBuf;
    hmf->unk3C->unk14 = HuMemAllocTag(size, hmf->unk0E);
    bcopy(dlBuf, hmf->unk3C->unk14, size);
    HuMemFree(dlBuf);
    for (i = 0; i < D_800D1FF0_main; i++) {
        gfx = hmf->unk3C->unk00[i + 1] = HuMemAllocTag(0x100, hmf->unk0E);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 0x02, osVirtualToPhysical(sprite->unk00->unk00));
        gSPDisplayList(gfx++, osVirtualToPhysical(hmf->unk3C->unk10));
        gDPSetPrimColor(gfx++, 0, 0, color->r, color->g, color->b, color->a);
        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, osVirtualToPhysical(hmf->unk3C->unk14));
        gDPPipeSync(gfx++);
        gSPEndDisplayList(gfx++);
    }
    hmf->unk3C->unk00[0] = hmf->unk3C->unk00[D_800D2008_main + 1];
    return model;
}

void func_8010EDE8_puddle_paddle(u16 model, HuSprite_Unk84_Struct *sprite, u16 frame) {
    HmfModel *modelData = Hu3DData + model;
    HmfData *data = modelData->hmf;
    Gfx *gfx = data->unk3C->unk00[D_800D2008_main + 1];

    data->unk3C->unk00[0] = gfx;
    gDPPipeSync(gfx);
    gSPSegment(gfx + 1, 2, osVirtualToPhysical(sprite->unk00[frame].unk00));
    gSPDisplayList(gfx + 2, osVirtualToPhysical(data->unk3C->unk10));
    gDPPipeSync(gfx + 3);
    gSPEndDisplayList(gfx + 4);
}

void func_8010EEB8_puddle_paddle(u16 model, HuSprite_Unk84_Struct *sprite, u16 frame, u8 *color) {
    HmfModel *modelData = Hu3DData + model;
    HmfData *data = modelData->hmf;
    Gfx *gfx = data->unk3C->unk00[D_800D2008_main + 1];

    data->unk3C->unk00[0] = gfx;
    gDPPipeSync(gfx);
    gSPSegment(gfx + 1, 2, osVirtualToPhysical(sprite->unk00[frame].unk00));
    gSPDisplayList(gfx + 2, osVirtualToPhysical(data->unk3C->unk10));
    gDPSetPrimColor(gfx + 3, 0, 0, color[0], color[1], color[2], color[3]);
    gDPPipeSync(gfx + 4);
    gSPDisplayList(gfx + 5, osVirtualToPhysical(data->unk3C->unk14));
    gDPPipeSync(gfx + 6);
    gSPEndDisplayList(gfx + 7);
}

s16 func_8010EFEC_puddle_paddle(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4) {
    Vtx *temp_s7;
    Vtx *var_s1;
    Vtx_t *var_t0;
    Vtx_t *var_a3;
    s32 var_a2;
    s32 temp_s4;
    s32 temp_a1;
    s32 sp24;
    s32 temp_f2;
    s32 var_s0;
    s32 var_s2;
    s32 sp2C;
    s32 temp_lo;
    s32 temp_s3;
    s32 var_s0_2;
    s32 var_a2_2;

    if (arg0->unk1A >= 2) {
        var_a2 = 0x800;
    } else {
        var_a2 = 0x1000;
    }
    temp_s4 = arg0->unk00->unk04;
    temp_a1 = arg0->unk00->unk06;
    sp24 = (f64)(temp_s4 * 0x64) * arg2 / 32.0;
    temp_f2 = (f64)(temp_a1 * 0x64) * arg2 / 32.0;
    if ((arg0->unk18 & 0xFFF) == 4) {
        var_s0 = ((temp_s4 + 1) & 0xFFFE) * temp_a1 * 4;
    } else {
        var_s0 = temp_s4 * temp_a1 * arg0->unk18;
    }
    var_s0 = (var_s0 < 0) ? (var_s0 + 7) : var_s0;
    var_s0 >>= 3;
    var_s2 = var_s0 / var_a2;
    if (var_s2 <= 0) {
        var_s2 = 1;
    }
    sp2C = temp_a1 / var_s2;
    temp_lo = temp_f2 / var_s2;
    temp_s3 = var_s2 * 4;
    temp_s7 = var_s1 = HuMemAllocTag(temp_s3 * sizeof(Vtx), arg1->unk0E);
    memset(temp_s7, 0, temp_s3 * sizeof(Vtx));
    for (var_s0_2 = 0; var_s0_2 < var_s2; var_s0_2++, var_s1 += 4) {
        var_s1[0].v.ob[0] = (s32)(sp24 * 0.5);
        var_s1[0].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * var_s0_2);
        var_s1[0].v.tc[0] = (temp_s4 - 1) * 64;
        var_s1[0].v.tc[1] = 0;
        var_s1[1].v.ob[0] = (s32)(sp24 * 0.5);
        var_s1[1].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * (var_s0_2 + 1));
        var_s1[1].v.tc[0] = (temp_s4 - 1) * 64;
        var_s1[1].v.tc[1] = (sp2C - 1) * 64;
        var_s1[2].v.ob[0] = (s32) - (sp24 * 0.5);
        var_s1[2].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * var_s0_2);
        var_s1[2].v.tc[0] = 0;
        var_s1[2].v.tc[1] = 0;
        var_s1[3].v.ob[0] = (s32) - (sp24 * 0.5);
        var_s1[3].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * (var_s0_2 + 1));
        var_s1[3].v.tc[0] = 0;
        var_s1[3].v.tc[1] = (sp2C - 1) * 64;
        for (var_a2_2 = 0; var_a2_2 < 4; var_a2_2++) {
            var_s1[var_a2_2].v.ob[0] += arg3;
            var_s1[var_a2_2].v.ob[1] += arg4;
            var_s1[var_a2_2].v.ob[2] = 0;
            var_s1[var_a2_2].v.flag = 0;
            var_s1[var_a2_2].v.cn[3] = 0xFF;
            var_s1[var_a2_2].v.cn[0] = var_s1[var_a2_2].v.cn[1] = var_s1[var_a2_2].v.cn[2] = 0;
        }
    }
    var_s1 = temp_s7;
    for (var_s0_2 = 0; var_s0_2 < D_800D1FF0_main; var_s0_2++) {
        arg1->unk44[var_s0_2] = HuMemAllocTag(temp_s3 * sizeof(Vtx), arg1->unk0E);
        var_t0 = &arg1->unk44[var_s0_2]->v;
        var_a3 = &var_s1->v;
        for (var_a2_2 = 0; var_a2_2 < temp_s3; var_a2_2++) {
            *(var_t0++) = *(var_a3++);
        }
    }
    HuMemFree(temp_s7);
    return var_s2;
}

void func_8010F410_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    func_8010BAA8_puddle_paddle(handler->unk_05, handler);
}

s32 func_8010F42C_puddle_paddle(void) {
    s32 unused[6]; // Unreferenced, but present in the stack frame.

    return 0;
}

s32 func_8010F43C_puddle_paddle(void) {
    s32 unused[6]; // Unreferenced, but present in the stack frame.

    return 0;
}

void func_8010F44C_puddle_paddle(s16 index, Vec *vertices, f32 arg2) {
    PuddlePaddleBoat *boat;
    Vec *destination;

    if (index >= 0) {
        return;
    }
    if (D_80111670_puddle_paddle[index].unk_04 == 0) {
        return;
    }
    boat = &D_80111670_puddle_paddle[index];
    destination = boat->vertices;
    memcpy(destination, vertices, boat->vertexCount * sizeof(Vec));
    boat->unk_C4 = arg2;
    func_80110888_puddle_paddle(destination, &boat->plane);
}

void func_8010F4DC_puddle_paddle(void) {
    s32 unused[8]; // Unreferenced, but present in the stack frame.
}

void func_8010F4E8_puddle_paddle(PuddlePaddleShip *ship, s16 count, f32 radius, s16 model) {
    if (ship != NULL) {
        ship->unk_08 = count + 1;
        ship->unk_04 = HuMemAllocTag(ship->unk_08 * sizeof(s16), TAG_OVERLAY);
        memset(ship->unk_04, -1, ship->unk_08 * sizeof(s16));
        ship->pos.x = ship->pos.y = ship->pos.z = 0.0f;
        ship->facing.x = ship->facing.y = ship->facing.z = 0.0f;
        ship->unk_24 = radius;
        ship->unk_28 = model;
    }
}

void func_8010F580_puddle_paddle(PuddlePaddleShip *ship) {
    PuddlePaddleBoat *boat;
    s16 i;

    ship->unk_30 = 0;
    ship->unk_2A = 0;
    ship->unk_2C = 0;
    ship->unk_2E = 0;
    ship->unk_00 &= ~1;
    if (ship->unk_28 != -1) {
        ship->pos.x = Hu3DData[ship->unk_28].pos.x;
        ship->pos.y = Hu3DData[ship->unk_28].pos.y;
        ship->pos.z = Hu3DData[ship->unk_28].pos.z;
    }
    for (i = 1; i < ship->unk_08; i++) {
        if (ship->unk_04[i] != -1) {
            boat = &D_80111670_puddle_paddle[ship->unk_04[i]];
            if (!(boat->unk_00 & 1)) {
                if (boat->unk_00 & 0x400) {
                    if ((s16)func_8010F80C_puddle_paddle(boat, ship) != 0) {
                        if (boat->unk_00 & 0x80) {
                            ship->unk_00 |= 1;
                        } else {
                            ship->unk_30 = i;
                        }
                    }
                } else if (boat->unk_00 & 0x200) {
                    if ((s16)func_8010F9FC_puddle_paddle(boat, ship) != 0) {
                        if (boat->unk_00 & 0x80) {
                            ship->unk_00 |= 1;
                        } else {
                            ship->unk_2E = i;
                        }
                    }
                } else if (boat->unk_00 & 0x100) {
                    if ((s16)func_8010FBD4_puddle_paddle(boat, ship) != 0) {
                        ship->unk_2A = i;
                    }
                } else {
                    if ((s16)func_80110284_puddle_paddle(boat, ship) != 0) {
                        if (boat->unk_00 & 0x80) {
                            ship->unk_00 |= 1;
                        } else {
                            ship->unk_2C = i;
                        }
                    }
                }
            }
        }
    }
    ship->pos.x += ship->facing.x;
    ship->pos.y += ship->facing.y;
    ship->pos.z += ship->facing.z;
    if (ship->unk_28 != -1) {
        Hu3DData[ship->unk_28].pos.x = ship->pos.x;
        Hu3DData[ship->unk_28].pos.y = ship->pos.y;
        Hu3DData[ship->unk_28].pos.z = ship->pos.z;
    }
}

s32 func_8010F80C_puddle_paddle(PuddlePaddleBoat *boat, PuddlePaddleShip *ship) {
    f32 bounds[2];
    Vec position;
    Vec movement;
    Vec next;
    Vec difference;
    f32 distance;
    f32 radius;

    position.x = ship->pos.x;
    position.y = ship->pos.y;
    position.z = ship->pos.z;
    movement.x = ship->facing.x;
    movement.y = ship->facing.y;
    movement.z = ship->facing.z;
    next.x = position.x + movement.x;
    next.y = position.y + movement.y;
    next.z = position.z + movement.z;
    radius = ship->unk_24;
    bounds[0] = boat->transformed[0].y - radius * 0.5f;
    bounds[1] = boat->transformed[0].y + boat->unk_C4 + radius * 0.5f;
    if (next.y < bounds[0] || next.y > bounds[1]) {
        return 0;
    } else {
        difference.x = boat->transformed[0].x - next.x;
        difference.z = boat->transformed[0].z - next.z;
        distance = HuSqrtf(difference.x * difference.x + difference.z * difference.z);
        if (distance <= ship->unk_24 + boat->unk_DC) {
            if (boat->unk_00 & 0x10) {
                return 1;
            }
            if (distance != 0.0f) {
                difference.x /= distance;
                difference.x = (ship->unk_24 + boat->unk_DC) * difference.x;
                difference.z /= distance;
                difference.z = (ship->unk_24 + boat->unk_DC) * difference.z;
            }
            next.x = boat->transformed[0].x - difference.x;
            next.z = boat->transformed[0].z - difference.z;
        } else {
            return 0;
        }
    }
    movement.x = next.x - position.x;
    movement.z = next.z - position.z;
    ship->facing.x = movement.x;
    ship->facing.y = movement.y;
    ship->facing.z = movement.z;
    return 1;
}

s32 func_8010F9FC_puddle_paddle(PuddlePaddleBoat *boat, PuddlePaddleShip *ship) {
    Vec position;
    Vec movement;
    Vec next;
    Vec difference;
    f32 distance;

    position.x = ship->pos.x;
    position.y = ship->pos.y;
    position.z = ship->pos.z;
    movement.x = ship->facing.x;
    movement.y = ship->facing.y;
    movement.z = ship->facing.z;
    next.x = position.x + movement.x;
    next.y = position.y + movement.y;
    next.z = position.z + movement.z;
    difference.x = boat->transformed[0].x - next.x;
    difference.y = boat->transformed[0].y - next.y;
    difference.z = boat->transformed[0].z - next.z;
    distance = HuSqrtf(difference.x * difference.x + difference.y * difference.y + difference.z * difference.z);
    if (distance <= ship->unk_24 + boat->unk_DC) {
        if (boat->unk_00 & 0x10) {
            return 1;
        }
        if (distance != 0.0f) {
            difference.x /= distance;
            difference.x *= ship->unk_24 + boat->unk_DC;
            difference.y /= distance;
            difference.y *= ship->unk_24 + boat->unk_DC;
            difference.z /= distance;
            difference.z *= ship->unk_24 + boat->unk_DC;
        }
        next.x = boat->transformed[0].x - difference.x;
        next.y = boat->transformed[0].y - difference.y;
        next.z = boat->transformed[0].z - difference.z;
    } else {
        return 0;
    }
    movement.x = next.x - position.x;
    movement.y = next.y - position.y;
    movement.z = next.z - position.z;
    ship->facing.x = movement.x;
    ship->facing.y = movement.y;
    ship->facing.z = movement.z;
    return 1;
}

s32 func_8010FBD4_puddle_paddle(PuddlePaddleBoat *boat, PuddlePaddleShip *ship) {
    Vec normal;
    Vec position;
    Vec movement;
    Vec next;
    Vec contact;
    f32 constant;
    f32 side;
    f32 distance;
    f32 radius;
    s16 result;

    normal.x = boat->plane.normal.x;
    normal.y = boat->plane.normal.y;
    normal.z = boat->plane.normal.z;
    constant = -boat->plane.constant;
    position.x = ship->pos.x;
    position.y = ship->pos.y;
    position.z = ship->pos.z;
    movement.x = ship->facing.x;
    movement.y = ship->facing.y;
    movement.z = ship->facing.z;
    if (!(boat->unk_00 & 0x20)) {
        side = normal.x * position.x + normal.y * position.y + normal.z * position.z + constant;
        if (side < 0.0f) {
            return 0;
        }
    }
    next.x = position.x + movement.x;
    next.y = position.y + movement.y;
    next.z = position.z + movement.z;
    if (!(boat->unk_00 & 0x20)) {
        side = normal.x * next.x + normal.y * next.y + normal.z * next.z + constant;
        distance = func_801101E0_puddle_paddle(boat, &next);
        if (side > 0.0f) {
            radius = ship->unk_24;
            if (distance > 0.0f ? radius <= distance : radius <= -distance) {
                return 0;
            }
        }
    } else {
        distance = func_801101E0_puddle_paddle(boat, &next);
        radius = ship->unk_24;
        if (distance > 0.0f ? radius <= distance : radius <= -distance) {
            return 0;
        }
    }
    contact.x = -normal.x * distance + next.x;
    contact.y = -normal.y * distance + next.y;
    contact.z = -normal.z * distance + next.z;
    result = func_8010FEC0_puddle_paddle(boat, &contact);
    if (result != 0) {
        if (boat->unk_00 & 0x10) {
            return 1;
        }
        next.x = normal.x * ship->unk_24 * 1.01f + contact.x;
        next.y = normal.y * ship->unk_24 * 1.01f + contact.y;
        next.z = normal.z * ship->unk_24 * 1.01f + contact.z;
        movement.x = next.x - position.x;
        movement.y = next.y - position.y;
        movement.z = next.z - position.z;
        ship->facing.x = movement.x;
        ship->facing.y = movement.y;
        ship->facing.z = movement.z;
    }
    return result;
}

s16 func_8010FEC0_puddle_paddle(PuddlePaddleBoat *boat, Vec *point) {
    Vec edge;
    Vec offset;
    f32 cross;
    s16 i;
    s16 next;

    switch (boat->plane.axis) {
        case 0:
            for (i = 0; i < boat->vertexCount; i++) {
                next = i + 1;
                next = next != boat->vertexCount ? next : 0;
                edge.y = boat->transformed[next].y - boat->transformed[i].y;
                edge.z = boat->transformed[next].z - boat->transformed[i].z;
                offset.y = point->y - boat->transformed[i].y;
                offset.z = point->z - boat->transformed[i].z;
                cross = edge.y * offset.z - edge.z * offset.y;
                if (cross * boat->plane.normal.x < 0.0f) {
                    return 0;
                }
            }
            break;
        case 1:
            for (i = 0; i < boat->vertexCount; i++) {
                next = i + 1;
                next = next != boat->vertexCount ? next : 0;
                edge.x = boat->transformed[next].x - boat->transformed[i].x;
                edge.z = boat->transformed[next].z - boat->transformed[i].z;
                offset.x = point->x - boat->transformed[i].x;
                offset.z = point->z - boat->transformed[i].z;
                cross = edge.z * offset.x - edge.x * offset.z;
                if (cross * boat->plane.normal.y < 0.0f) {
                    return 0;
                }
            }
            // The Y-axis case also checks the polygon's XY projection.
            // Fall through.
        case 2:
            for (i = 0; i < boat->vertexCount; i++) {
                next = i + 1;
                next = next != boat->vertexCount ? next : 0;
                edge.x = boat->transformed[next].x - boat->transformed[i].x;
                edge.y = boat->transformed[next].y - boat->transformed[i].y;
                offset.x = point->x - boat->transformed[i].x;
                offset.y = point->y - boat->transformed[i].y;
                cross = edge.x * offset.y - edge.y * offset.x;
                if (cross * boat->plane.normal.z < 0.0f) {
                    return 0;
                }
            }
            break;
    }
    return 1;
}

f32 func_801101E0_puddle_paddle(PuddlePaddleBoat *boat, Vec *point) {
    f32 x = point->x;
    f32 y = point->y;
    f32 z = point->z;
    Vec normal;
    f32 length;

    normal.x = boat->plane.normal.x;
    normal.y = boat->plane.normal.y;
    normal.z = boat->plane.normal.z;
    length = HuSqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    return (x * normal.x + y * normal.y + z * normal.z - boat->plane.constant) / length;
}

s32 func_80110284_puddle_paddle(PuddlePaddleBoat *boat, PuddlePaddleShip *ship) {
    f32 side;
    f32 edge;
    s16 i;
    s16 next;

    if (!(boat->unk_00 & 2) && ship->pos.y > boat->unk_C4) {
        return 0;
    }
    side = func_801104C8_puddle_paddle(ship, &boat->transformed[0], &boat->transformed[1]);
    if (side == 0.0f) {
        return 0;
    }
    if (side > 0.0f) {
        for (i = 1; i < boat->vertexCount; i++) {
            next = i + 1;
            next = next != boat->vertexCount ? next : 0;
            edge = func_801104C8_puddle_paddle(ship, &boat->transformed[i], &boat->transformed[next]);
            if (edge == 0.0f) {
                return 1;
            }
            if (edge < 0.0f) {
                return 0;
            }
        }
    } else {
        for (i = 1; i < boat->vertexCount; i++) {
            next = i + 1;
            next = next != boat->vertexCount ? next : 0;
            edge = func_801104C8_puddle_paddle(ship, &boat->transformed[i], &boat->transformed[next]);
            if (edge == 0.0f) {
                return 1;
            }
            if (edge > 0.0f) {
                return 0;
            }
        }
    }
    return 1;
}

f32 func_801104C8_puddle_paddle(PuddlePaddleShip *arg0, Vec *arg1, Vec *arg2) {
    Vec pos, v1, v2;

    pos.x = arg0->pos.x;
    pos.z = arg0->pos.z;
    v1.x = arg1->x - pos.x;
    v1.z = arg1->z - pos.z;
    v2.x = arg2->x - pos.x;
    v2.z = arg2->z - pos.z;
    return v1.z * v2.x - v1.x * v2.z;
}

s32 func_80110524_puddle_paddle(f32 *outPos, u8 *tickPtr, f32 posA, f32 posB, f32 numTicks) {
    f32 frac = (f32)*tickPtr / numTicks;
    u8 tick;

    *outPos = posA + ((posB - posA) * frac);
    tick = *tickPtr + 1;
    *tickPtr = tick;
    if (numTicks < tick) {
        *tickPtr = 0;
        *outPos = posB;
        return 1;
    }
    return 0;
}

f32 func_8011059C_puddle_paddle(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 t = arg0;
    f32 a;

    if (1.0f < t) {
        t = 1.0f;
    }
    a = 1.0f - t;
    return a * a * arg1 + (a + a) * t * arg2 + t * t * arg3;
}

void func_80110608_puddle_paddle(u16 *order, s16 count) {
    s16 i;
    s16 index;
    s32 random;
    u16 temp;

    for (i = 0; i < count; i++) {
        order[i] = i;
    }
    for (i = count - 1; i >= 0; i--) {
        random = rand16();
        index = random % (i + 1);
        temp = order[i];
        order[i] = order[index];
        order[index] = temp;
    }
}

void func_80110714_puddle_paddle(omObjData *object) {
    HmfModel *model = &Hu3DData[object->model[0]];

    object->scale.x = model->scale.x;
    object->scale.y = model->scale.y;
    object->scale.z = model->scale.z;
    object->trans.x = model->pos.x;
    object->trans.y = model->pos.y;
    object->trans.z = model->pos.z;
    if (model->rot.x >= 360.0f) {
        model->rot.x -= 360.0f;
    }
    if (model->rot.x < 0.0f) {
        model->rot.x += 360.0f;
    }
    if (model->rot.y >= 360.0f) {
        model->rot.y -= 360.0f;
    }
    if (model->rot.y < 0.0f) {
        model->rot.y += 360.0f;
    }
    if (model->rot.z >= 360.0f) {
        model->rot.z -= 360.0f;
    }
    if (model->rot.z < 0.0f) {
        model->rot.z += 360.0f;
    }
    object->rot.x = model->rot.x;
    object->rot.y = model->rot.y;
    object->rot.z = model->rot.z;
}

void func_80110888_puddle_paddle(Vec *vertices, PuddlePaddlePlane *plane) {
    f32 firstX, firstY, firstZ, secondX, secondY, secondZ;
    f32 normal[3];
    f32 length;
    f32 magnitude;
    s16 axis, i;

    firstX = vertices[1].x - vertices[0].x;
    firstY = vertices[1].y - vertices[0].y;
    firstZ = vertices[1].z - vertices[0].z;
    secondX = vertices[2].x - vertices[0].x;
    secondY = vertices[2].y - vertices[0].y;
    secondZ = vertices[2].z - vertices[0].z;
    normal[0] = firstY * secondZ - firstZ * secondY;
    normal[1] = firstZ * secondX - firstX * secondZ;
    normal[2] = firstX * secondY - firstY * secondX;
    length = HuSqrtf(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
    if (length != 0.0f) {
        normal[0] /= length;
        normal[1] /= length;
        normal[2] /= length;
    }
    plane->constant = normal[0] * vertices[0].x + normal[1] * vertices[0].y + normal[2] * vertices[0].z;
    axis = 0;
    for (i = 1; i < 3; i++) {
        magnitude = normal[axis] > 0.0f ? normal[axis] : -normal[axis];
        if (normal[i] > 0.0f ? magnitude < normal[i] : magnitude < -normal[i]) {
            axis = i;
        }
    }
    plane->normal.x = normal[0];
    plane->normal.y = normal[1];
    plane->normal.z = normal[2];
    plane->axis = axis;
}

void func_80110A8C_puddle_paddle(Vec from, Vec to, f32 *angles) {
    Vec difference;
    f32 angle;
    f32 fullRotation = 360.0f;

    difference.x = to.x - from.x;
    difference.y = to.y - from.y;
    difference.z = to.z - from.z;
    angle = atan2df(difference.y, sqrtf(difference.x * difference.x + difference.z * difference.z));
    if (angle < 0.0f) {
        angle += fullRotation;
    } else if (angle >= fullRotation) {
        angle -= fullRotation;
    }
    *angles++ = angle;
    angle = atan2df(difference.x, difference.z);
    if (angle < 0.0f) {
        angle += fullRotation;
    } else if (angle >= fullRotation) {
        angle -= fullRotation;
    }
    *angles = angle;
}

void func_80110BBC_puddle_paddle(f32 *angle, f32 *target) {
    f32 difference;

    while (*target < 0.0f) {
        *target += 360.0f;
    }
    while (*target >= 360.0f) {
        *target -= 360.0f;
    }
    while (*angle < 0.0f) {
        *angle += 360.0f;
    }
    while (*angle >= 360.0f) {
        *angle -= 360.0f;
    }
    difference = *target - *angle;
    if (!(difference > 0.0f)) {
        difference = -difference;
    }
    if (difference > 180.0f) {
        if (*angle < *target) {
            *target -= 360.0f;
        } else {
            *angle -= 360.0f;
        }
    }
}

void func_80110D3C_puddle_paddle(f32 *mtx) {
    s16 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            mtx[i * 4 + j] = 0.0f;
        }
        mtx[i * 4 + i] = 1.0f;
    }
}

void func_80110DC4_puddle_paddle(f32 *matrix, f32 x, f32 y, f32 z) {
    func_80110D3C_puddle_paddle(matrix);
    matrix[12] = x;
    matrix[13] = y;
    matrix[14] = z;
}

void func_80110E1C_puddle_paddle(f32 *matrix, f32 angle) {
    func_80110D3C_puddle_paddle(matrix);
    matrix[5] = cosdf(angle);
    matrix[6] = sindf(angle);
    matrix[9] = -sindf(angle);
    matrix[10] = cosdf(angle);
}

void func_80110E84_puddle_paddle(f32 *matrix, f32 angle) {
    func_80110D3C_puddle_paddle(matrix);
    matrix[0] = cosdf(angle);
    matrix[2] = -sindf(angle);
    matrix[8] = sindf(angle);
    matrix[10] = cosdf(angle);
}

void func_80110EEC_puddle_paddle(f32 *left, f32 *right, f32 *output) {
    s16 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            output[i * 4 + j] = left[i * 4] * right[j] + left[i * 4 + 1] * right[4 + j] +
                                left[i * 4 + 2] * right[8 + j] + left[i * 4 + 3] * right[12 + j];
        }
    }
}

void func_80110FA0_puddle_paddle(f32 *matrix, f32 *output) {
    *output++ = matrix[12] * matrix[0] + matrix[13] * matrix[4] + matrix[14] * matrix[8];
    *output++ = matrix[12] * matrix[1] + matrix[13] * matrix[5] + matrix[14] * matrix[9];
    *output = matrix[12] * matrix[2] + matrix[13] * matrix[6] + matrix[14] * matrix[10];
}

void func_80111038_puddle_paddle(f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 *matrix) {
    f32 translation[16];
    f32 rotationX[16];
    f32 rotationY[16];
    f32 rotation[16];

    func_80110DC4_puddle_paddle(translation, x, y, z);
    func_80110E1C_puddle_paddle(rotationX, rx);
    func_80110E84_puddle_paddle(rotationY, ry);
    func_80110EEC_puddle_paddle(rotationX, rotationY, rotation);
    func_80110EEC_puddle_paddle(rotation, translation, matrix);
}

void func_801110F0_puddle_paddle(Vec *vertices, s16 count, f32 *matrix, Vec *output) {
    s16 i;

    for (i = 0; i < count; i++) {
        output[i].x = (matrix[12] + vertices[i].x) * matrix[0] +
                      (matrix[13] + vertices[i].y) * matrix[4] +
                      (matrix[14] + vertices[i].z) * matrix[8];
        output[i].y = (matrix[12] + vertices[i].x) * matrix[1] +
                      (matrix[13] + vertices[i].y) * matrix[5] +
                      (matrix[14] + vertices[i].z) * matrix[9];
        output[i].z = (matrix[12] + vertices[i].x) * matrix[2] +
                      (matrix[13] + vertices[i].y) * matrix[6] +
                      (matrix[14] + vertices[i].z) * matrix[10];
    }
}
