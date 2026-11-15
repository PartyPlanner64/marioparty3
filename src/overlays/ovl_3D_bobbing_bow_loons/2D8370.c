#include "common.h"
#include "game/mallocblock.h"
#include "overlays/minigame.h"

// Per-object work block for D_80109B2C_bobbing_bow_loons, allocated in
// func_80106CC0_bobbing_bow_loons. Holds five parallel per-item arrays.
typedef struct BobbingBowLoonsWork {
    /* 0x00 */ s32 state[5];
    /* 0x14 */ f32 pos_x[5];
    /* 0x28 */ f32 pos_y[5];
    /* 0x3C */ f32 pos_z[5];
    /* 0x50 */ f32 unk_50[5];
    /* 0x64 */ f32 unk_64[5];
    /* 0x78 */ f32 rise;
} BobbingBowLoonsWork; // Size 0x7C

// Per-loon positions tracked for the five chained bow loons of the player object
// held in D_80109B60_bobbing_bow_loons. Each axis is a parallel array of five.
typedef struct BobbingBowLoonsLoon {
    /* 0x00 */ f32 x[5];
    /* 0x14 */ f32 y[5];
    /* 0x28 */ f32 z[5];
} BobbingBowLoonsLoon; // Size 0x3C

// Object data for the player object held in D_80109B1C_bobbing_bow_loons,
// created in func_80105D04_bobbing_bow_loons.
typedef struct BobbingBowLoonsPlayer {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ Vec pos;
    /* 0x10 */ f32 scale;
    /* 0x14 */ f32 unk_14;
} BobbingBowLoonsPlayer; // Size 0x18

// Object data for the stage object created in func_801065C8_bobbing_bow_loons.
// Holds the positions of its eight models.
typedef struct BobbingBowLoonsStage {
    /* 0x00 */ f32 x[8];
    /* 0x20 */ f32 y[8];
    /* 0x40 */ f32 z[8];
} BobbingBowLoonsStage; // Size 0x60

// Object data for the hook object held in D_80109B30_bobbing_bow_loons,
// created in func_8010805C_bobbing_bow_loons.
typedef struct BobbingBowLoonsHook {
    /* 0x00 */ s32 flags;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ f32 rotZ;
} BobbingBowLoonsHook; // Size 0x14

// Object data for the string object held in D_80109B34_bobbing_bow_loons,
// created in func_8010728C_bobbing_bow_loons. Holds the positions of its seven models.
typedef struct BobbingBowLoonsStrings {
    /* 0x00 */ f32 x[7];
    /* 0x1C */ f32 y[7];
    /* 0x38 */ f32 z[7];
} BobbingBowLoonsStrings; // Size 0x54

// Object data for the effect object held in D_80109B5C_bobbing_bow_loons,
// created in func_80108C18_bobbing_bow_loons.
typedef struct BobbingBowLoonsEffect {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ s32 flags;
    /* 0x10 */ f32 scale;
    /* 0x14 */ s32 timer;
    /* 0x18 */ s32 unk_18;
} BobbingBowLoonsEffect; // Size 0x1C

// Object data for the host object held in D_80109B64_bobbing_bow_loons,
// created in func_801093DC_bobbing_bow_loons.
typedef struct BobbingBowLoonsHost {
    /* 0x00 */ f32 y;
    /* 0x04 */ f32 headRot;
} BobbingBowLoonsHost; // Size 0x8

// Object data for the item object held in D_80109B38_bobbing_bow_loons,
// created in func_801074CC_bobbing_bow_loons. One item hangs from each loon.
typedef struct BobbingBowLoonsItems {
    /* 0x00 */ f32 x[5];
    /* 0x14 */ f32 y[5];
    /* 0x28 */ f32 z[5];
    /* 0x3C */ s32 state[5];
    /* 0x50 */ f32 angle;
    /* 0x54 */ f32 heldX;
    /* 0x58 */ f32 heldY;
} BobbingBowLoonsItems; // Size 0x5C

extern u16 D_800A11D0_main[];
extern u16 D_800A11DC_main[];

D_80111B50_vine_with_me_Struct D_80109720_bobbing_bow_loons = { 0, 3, 2, 0, 0, 0, 5, 0, { 0.0f, 0.0f, 0.0f, 0.0f }, { 0, 0, 0, 0 }, 30, 300, -1, 90, 135 };
f32 D_80109748_bobbing_bow_loons[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
s32 D_80109768_bobbing_bow_loons[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
char *D_80109788_bobbing_bow_loons[8] = {
    "migi-te3_2_1",
    "c001_000-migi-te2_3",
    "C002_000b-bmerge16",
    "c003_000-bmerge1_8",
    "Luigi1-migi-te1_1",
    "c005_000-bmerge6",
    "c001_000-migi-te2_3",
    "C002_000b-bmerge16",
};
s32 D_801097A8_bobbing_bow_loons[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

u8 D_80109B00_bobbing_bow_loons[4] BSS; /* Unreferenced. */
u8 D_80109B04_bobbing_bow_loons BSS;
s16 D_80109B06_bobbing_bow_loons BSS;
s16 D_80109B08_bobbing_bow_loons BSS;
s16 D_80109B0A_bobbing_bow_loons BSS; /* Unreferenced. */
s32 D_80109B0C_bobbing_bow_loons BSS;
s32 D_80109B10_bobbing_bow_loons BSS;
s32 D_80109B14_bobbing_bow_loons BSS;
s16 D_80109B18_bobbing_bow_loons BSS;
s16 D_80109B1A_bobbing_bow_loons BSS; /* Unreferenced. */
omObjData *D_80109B1C_bobbing_bow_loons BSS;
s16 D_80109B20_bobbing_bow_loons[2] BSS;
u8 D_80109B24_bobbing_bow_loons[4] BSS; /* Unreferenced. */
omObjData *D_80109B28_bobbing_bow_loons BSS;
omObjData *D_80109B2C_bobbing_bow_loons BSS;
omObjData *D_80109B30_bobbing_bow_loons BSS;
omObjData *D_80109B34_bobbing_bow_loons BSS;
omObjData *D_80109B38_bobbing_bow_loons BSS;
u8 D_80109B3C_bobbing_bow_loons[4] BSS; /* Unreferenced. */
s32 D_80109B40_bobbing_bow_loons[5] BSS;
s32 D_80109B54_bobbing_bow_loons BSS;
omObjData *D_80109B58_bobbing_bow_loons BSS;
omObjData *D_80109B5C_bobbing_bow_loons BSS;
omObjData *D_80109B60_bobbing_bow_loons BSS;
omObjData *D_80109B64_bobbing_bow_loons BSS;

void func_8004BCE4_main(struct CameraViewData *data);
void func_80105AE8_bobbing_bow_loons(void);
void func_80105B64_bobbing_bow_loons(void);
void func_80105D04_bobbing_bow_loons(void);
void func_80106F44_bobbing_bow_loons(omObjData *obj);
void func_80107C48_bobbing_bow_loons(void);
void func_80107F68_bobbing_bow_loons(void);
void func_8010829C_bobbing_bow_loons(void);
void func_80108894_bobbing_bow_loons(void);
void func_801091FC_bobbing_bow_loons(void);
void func_8010934C_bobbing_bow_loons(void);
void func_801068B0_bobbing_bow_loons(omObjData *obj);
void func_80106260_bobbing_bow_loons(omObjData *obj);
void func_801065C8_bobbing_bow_loons(void);
void func_80106A34_bobbing_bow_loons(omObjData *obj);
void func_80106CC0_bobbing_bow_loons(void);
void func_801074CC_bobbing_bow_loons(void);
void func_8010728C_bobbing_bow_loons(void);
void func_8010805C_bobbing_bow_loons(void);
void func_80109044_bobbing_bow_loons(void);
void func_801093DC_bobbing_bow_loons(void);
void func_80109680_bobbing_bow_loons(void);
void func_80107C74_bobbing_bow_loons(void);
void func_80107D78_bobbing_bow_loons(void);
void func_80107E94_bobbing_bow_loons(void);
void func_80107F94_bobbing_bow_loons(void);
void func_80108354_bobbing_bow_loons(void);
void func_801088C0_bobbing_bow_loons(void);
void func_80109594_bobbing_bow_loons(void);
void func_80107368_bobbing_bow_loons(omObjData *obj);
void func_80107830_bobbing_bow_loons(omObjData *obj);
void func_80107A7C_bobbing_bow_loons(void);
void func_80107D4C_bobbing_bow_loons(void);
void func_80108F2C_bobbing_bow_loons(f32 x, f32 y);
void func_80108E5C_bobbing_bow_loons(omObjData *obj);
void func_801090EC_bobbing_bow_loons(omObjData *obj);
void func_801094B0_bobbing_bow_loons(omObjData *obj);
void func_8010817C_bobbing_bow_loons(omObjData *obj);
void func_80108328_bobbing_bow_loons(void);
void func_80109568_bobbing_bow_loons(void);
void func_801096E8_bobbing_bow_loons(void);

void func_801059A0_bobbing_bow_loons(void) {
    omInitObjMan(30, 10);
    func_8001FE20_main(16);
    func_80021BE0_main(&D_800EBEB0_minigame, 64);
    func_800142A0_main(64);
    func_80105AE8_bobbing_bow_loons();
    func_8004A208_main();
    Hu3DBGColorSet(0, 0, 0);
    func_800E5EA0_minigame(&D_80109720_bobbing_bow_loons);
    WipeCreateIn(0xFF, 16);
    func_80105B64_bobbing_bow_loons();
    func_80105D04_bobbing_bow_loons();
    func_801065C8_bobbing_bow_loons();
    func_80106CC0_bobbing_bow_loons();
    func_801074CC_bobbing_bow_loons();
    func_801093DC_bobbing_bow_loons();
    D_80109B06_bobbing_bow_loons = 0;
    D_800EBE24_minigame = 0;
    D_80109B04_bobbing_bow_loons = 0;
    D_80109B10_bobbing_bow_loons = -1;
    omAddObj(0x50, 0, 0, -1, func_80106A34_bobbing_bow_loons);
    func_8010728C_bobbing_bow_loons();
    func_8010805C_bobbing_bow_loons();
    func_80109044_bobbing_bow_loons();
    func_80109680_bobbing_bow_loons();
    CZoom = 1000.0f;
    Center.x = 200.0f;
    Center.y = 80.0f;
    Center.z = 0.0f;
}

void func_80105AE8_bobbing_bow_loons(void) {
    s16 camIndex;

    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    D_80109B18_bobbing_bow_loons = camIndex;
    Hu3DCameraPerspectiveSet(camIndex, 30.0f, 80.0f, 8000.0f);
    CZoom = 500.0f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = 0.0f;
}

void func_80105B64_bobbing_bow_loons(void) {
    omObjData *obj;
    Vec pos;
    Vec target;
    s16 sprite;

    sprite = espEntry(HuSprAnimDataRead(0x5E0000), 0, 1);
    espDispOff(sprite);
    pos.x = 0.0f;
    pos.y = 1.0f;
    pos.z = 1500.0f;
    target.x = 0.0f;
    target.y = 0.0f;
    target.z = 0.0f;
    func_8004B760_main(100, D_800CD1DC_main[sprite].unk04, func_8004BCE4_main, 30.0f, &pos, &target);
    obj = omAddObj(0x50, 3, 0, -1, NULL);
    obj->model[0] = func_8000B108_main(0x5E0003, 0x6D9);
    obj->model[1] = Hu3DModelLink(obj->model[0]);
    obj->model[2] = func_8000B108_main(0x5E0004, 0x6D9);
    omSetTra(obj, -550.0f, -400.0f, 10.0f);
    omSetSca(obj, 1.5f, 1.5f, 1.5f);
    Hu3DModelPosSet(obj->model[1], 400.0f, -400.0f, 4.0f);
    Hu3DModelPosSet(obj->model[2], 340.0f, -50.0f, -100.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 2.0f, 1.0f);
}

void func_80105D04_bobbing_bow_loons(void) {
    // Copied onto the stack but never read.
    s32 unused[8] = { 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 3 };
    s32 modelFiles[8] = { 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0 };
    s32 motions[8][3] = {
        { 0x6E, 0x6F, 0x29 },
        { 0x6E, 0x6F, 0x29 },
        { 0x6E, 0x6F, 0x29 },
        { 0x6E, 0x6F, 0x29 },
        { 0x6E, 0x6F, 0x29 },
        { 0x6E, 0x6F, 0x29 },
        { 0x6E, 0x6F, 0x29 },
        { 0x6E, 0x6F, 0x29 },
    };
    s32 markerFiles[8] = { 8, 9, 10, 11, 12, 13, 14, 15 };
    s32 handFiles[8] = { 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C };
    s32 spriteFiles[8] = { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B };
    s32 spriteFiles2[8] = { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C };
    BobbingBowLoonsPlayer *player;
    omObjData *obj;
    s32 dir;
    s32 file;
    s16 chr;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            D_80109B0C_bobbing_bow_loons = i;
            break;
        }
    }
    obj = omAddObj(0x50, 4, 10, -1, func_80106260_bobbing_bow_loons);
    obj->data = HuMemAllocTag(sizeof(BobbingBowLoonsPlayer), 0x7918);
    D_80109B1C_bobbing_bow_loons = obj;
    player = obj->data;
    player->unk_00 = 1;
    player->scale = 1.0f;
    player->unk_00 = 1;
    chr = GwPlayer[D_80109B0C_bobbing_bow_loons].chr;
    dir = D_80109768_bobbing_bow_loons[chr] << 16;
    file = dir | modelFiles[chr];
    obj->model[0] = func_8000B108_main(file, 0x6A9);
    obj->model[2] = func_8000B108_main(handFiles[chr] | 0x5E0000, 0x6BD);
    obj->model[3] = func_8000B108_main(file, 0x6BD);
    player->pos.x = 400.0f;
    player->pos.y = 0.0f;
    player->pos.z = 80.0f;
    player->unk_14 = 0.0f;
    omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
    omSetRot(obj, 0.0f, 270.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    Hu3DModelRotSet(obj->model[3], 0.0f, 270.0f, 0.0f);
    D_80109B20_bobbing_bow_loons[0] =
        func_80017790_main(obj->model[0], 1, D_801097A8_bobbing_bow_loons[chr], dir | spriteFiles[chr]);
    D_80109B20_bobbing_bow_loons[1] = func_80017AD8_main(dir | spriteFiles2[chr]);
    func_8001C514_main(obj->model[0]);
    for (i = 0; i < 4; i++) {
        func_8000B460_main(obj, i, func_80017BB8_main(chr, motions[chr][i]));
    }
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_80017358_main(obj->model[2], D_80109788_bobbing_bow_loons[chr], obj->model[0],
                       D_80109788_bobbing_bow_loons[chr]);
    obj->model[1] = func_8000B108_main(markerFiles[chr] | 0x5E0000, 0x6B9);
    Hu3DModelPosSet(obj->model[1],
                    player->pos.x + D_80109748_bobbing_bow_loons[GwPlayer[D_80109B0C_bobbing_bow_loons].chr],
                    player->pos.y + 150.0f, player->pos.z + 0.0f);
    Hu3DModelScaleSet(obj->model[1], 1.5f, 1.5f, 1.5f);
}

void func_80106260_bobbing_bow_loons(omObjData *obj) {
    BobbingBowLoonsPlayer *player = obj->data;
    f32 scale;

    omSetSca(obj, player->scale, player->scale, player->scale);
    omSetTra(obj, player->pos.x, player->pos.y - 50.0f, player->pos.z);
    Hu3DModelPosSet(obj->model[1],
                    player->pos.x + D_80109748_bobbing_bow_loons[GwPlayer[D_80109B0C_bobbing_bow_loons].chr],
                    player->pos.y + 150.0f, player->pos.z + 0.0f);
    Hu3DModelPosSet(obj->model[3], player->pos.x, player->pos.y - 50.0f, player->pos.z + 2.0f);
    scale = player->scale * 1.5f;
    Hu3DModelScaleSet(obj->model[1], scale, scale, scale);
    if (player->unk_00 & 1) {
        player->pos.y = sindf(player->unk_14) * 10.0f;
        player->unk_14 += 10.0f;
        if (player->unk_14 >= 360.0f) {
            player->unk_14 -= 360.0f;
        }
    }
}

void func_801063F8_bobbing_bow_loons(void) {
    s16 chr = GwPlayer[D_80109B0C_bobbing_bow_loons].chr;

    Hu3DMotionShiftSet(D_80109B1C_bobbing_bow_loons->model[0], Hu3DData[D_80109B1C_bobbing_bow_loons->motion[1]].motId,
                       0, 10, 0);
    func_80017954_main(D_80109B1C_bobbing_bow_loons->model[0], 1, D_801097A8_bobbing_bow_loons[chr],
                       D_80109B20_bobbing_bow_loons[1]);
    func_80045ED0_main((D_80109768_bobbing_bow_loons[chr] << 16) | 0x6F);
}

void func_801064C0_bobbing_bow_loons(void) {
    s16 chr = GwPlayer[D_80109B0C_bobbing_bow_loons].chr;

    func_8001C258_main(D_80109B1C_bobbing_bow_loons->model[0], 4, 4);
    func_8001C258_main(D_80109B1C_bobbing_bow_loons->model[3], 4, 0);
    Hu3DMotionShiftSet(D_80109B1C_bobbing_bow_loons->model[3], Hu3DData[D_80109B1C_bobbing_bow_loons->motion[2]].motId,
                       0, 10, 0);
    func_8001C814_main(D_80109B1C_bobbing_bow_loons->model[3], 2, 2);
    func_80017358_main(D_80109B1C_bobbing_bow_loons->model[3], D_80109788_bobbing_bow_loons[chr],
                       D_80109B1C_bobbing_bow_loons->model[0], D_80109788_bobbing_bow_loons[chr]);
    func_8010934C_bobbing_bow_loons();
}

void func_801065C8_bobbing_bow_loons(void) {
    s32 attrs[2];
    s32 files[2] = { 0x13, 0x14 };
    s32 alphas[2] = { 0x40, 0xB3 };
    BobbingBowLoonsStage *stage;
    omObjData *obj;
    s32 i;
    s32 j;

    attrs[0] = 0xAC9;
    attrs[1] = 0x2C9;

    obj = omAddObj(0xFF, 8, 0, -1, func_801068B0_bobbing_bow_loons);
    D_80109B28_bobbing_bow_loons = obj;
    stage = obj->data = HuMemAllocTag(sizeof(BobbingBowLoonsStage), 0x7918);
    stage->x[0] = 0.0f;
    stage->x[1] = 1000.0f;
    stage->x[2] = 0.0f;
    stage->x[3] = 1000.0f;
    stage->x[4] = 50.0f;
    stage->x[5] = -950.0f;
    stage->x[6] = 50.0f;
    stage->x[7] = -950.0f;
    stage->y[0] = -400.0f;
    stage->y[1] = -400.0f;
    stage->y[2] = -400.0f;
    stage->y[3] = -400.0f;
    stage->y[4] = -400.0f;
    stage->y[5] = -400.0f;
    stage->y[6] = -400.0f;
    stage->y[7] = -400.0f;
    stage->z[0] = 16.0f;
    stage->z[1] = 16.0f;
    stage->z[2] = 2.0f;
    stage->z[3] = 2.0f;
    stage->z[4] = 18.0f;
    stage->z[5] = 18.0f;
    stage->z[6] = 0.0f;
    stage->z[7] = 0.0f;
    obj->model[0] = func_8000B108_main(0x5E0001, 0x1699);
    obj->model[1] = Hu3DModelLink(obj->model[0]);
    obj->model[2] = func_8000B108_main(0x5E0002, 0x699);
    obj->model[3] = Hu3DModelLink(obj->model[2]);
    for (j = 0, i = 4; i < 8; j++, i += 2) {
        obj->model[i] = func_8000B108_main(files[j] | 0x5E0000, attrs[j]);
        func_8001C2FC_main(obj->model[i], 0x20000, 0x20000);
        func_8001C954_main(obj->model[i]);
        func_8001FA68_main(obj->model[i]);
        func_8001F9E4_main(obj->model[i], alphas[j]);
        Hu3DModelRemakeStatic(obj->model[i]);
        func_8001C514_main(obj->model[i]);
        obj->model[i + 1] = Hu3DModelLink(obj->model[i]);
    }
    omSetTra(obj, stage->x[0], stage->y[0], stage->z[0]);
    for (i = 1; i < 8; i++) {
        Hu3DModelPosSet(obj->model[i], stage->x[i], stage->y[i], stage->z[i]);
    }
}

void func_801068B0_bobbing_bow_loons(omObjData *obj) {
    BobbingBowLoonsStage *stage = obj->data;
    s32 i;

    for (i = 0; i < 8; i++) {
        if (i == 0) {
            omSetTra(obj, stage->x[0], stage->y[0], stage->z[0]);
        } else {
            Hu3DModelPosSet(obj->model[i], stage->x[i], stage->y[i], stage->z[i]);
        }
    }
    stage->x[0] += -3.0f;
    stage->x[1] += -3.0f;
    stage->x[2] += -1.0f;
    stage->x[3] += -1.0f;
    stage->x[4] += -3.0f;
    stage->x[5] += -3.0f;
    stage->x[6] += -1.0f;
    stage->x[7] += -1.0f;
    for (i = 0; i < 8; i++) {
        if (stage->x[i] <= -1000.0f) {
            stage->x[i] += 2000.0f;
        }
    }
}

void func_80106A00_bobbing_bow_loons(omObjData *obj) {
    if (WipeStatGet() == 0) {
        HuWinAllKill();
        omOvlReturnEx(1);
    }
}

void func_80106A34_bobbing_bow_loons(omObjData *obj) {
    f32 cueFrames[8] = { 40.0f, 40.0f, 40.0f, 40.0f, 40.0f, 40.0f, 40.0f, 40.0f };

    if (D_800D530C_main != 0) {
        HuAudFXAllStop();
        HuAudSeqFadeOut(30);
        WipeCreateOut(0, 20);
    }
    switch (func_800E6F40_minigame(obj)) {
        case 0:
            if (func_800E6E9C_minigame() == 1) {
                HuAudSeqPlay(0x44);
            }
            if (Hu3DData[D_80109B1C_bobbing_bow_loons->model[0]].motTime ==
                cueFrames[GwPlayer[D_80109B0C_bobbing_bow_loons].chr]) {
                HuAudFXPlay(0x4DA);
            }
            if (func_800E6E9C_minigame() == 15) {
                func_80107C48_bobbing_bow_loons();
                HuAudFXPlay(0x4E0);
            }
            break;
        case 1:
            break;
        case 2:
            if (func_800E6E9C_minigame() == 0) {
                func_80107F68_bobbing_bow_loons();
                func_80108894_bobbing_bow_loons();
            }
            if (D_80109B04_bobbing_bow_loons == 2 || D_80109B04_bobbing_bow_loons == 3) {
                if (D_80109B04_bobbing_bow_loons == 2) {
                    func_801091FC_bobbing_bow_loons();
                }
                func_8010829C_bobbing_bow_loons();
                D_80109B04_bobbing_bow_loons = 4;
            }
            break;
        case 3:
            break;
        case 4:
            if (D_80109B10_bobbing_bow_loons != -1) {
                D_80109720_bobbing_bow_loons.unk06 = 5;
            } else {
                D_80109720_bobbing_bow_loons.unk06 = 7;
            }
            break;
        case 5:
            if (D_80109B10_bobbing_bow_loons != -1) {
                GwPlayer[D_80109B0C_bobbing_bow_loons].bonusCoin = D_80109B10_bobbing_bow_loons;
            } else {
                GwPlayer[D_80109B0C_bobbing_bow_loons].bonusCoin = -1;
            }
            WipeCreateOut(0, 20);
            obj->func = func_80106A00_bobbing_bow_loons;
            break;
    }
}

void func_80106CC0_bobbing_bow_loons(void) {
    s32 attr = 0x699;
    BobbingBowLoonsWork *work;
    BobbingBowLoonsPlayer *player;
    omObjData *obj;
    s32 i;

    obj = omAddObj(0xFF, 10, 0, -1, func_80106F44_bobbing_bow_loons);
    D_80109B2C_bobbing_bow_loons = obj;
    work = obj->data = HuMemAllocTag(sizeof(BobbingBowLoonsWork), 0x7918);
    player = D_80109B1C_bobbing_bow_loons->data;
    for (i = 0; i < 5; i++) {
        work->state[i] = 1;
        work->pos_x[i] = i * 120.0f - 280.0f;
        work->pos_y[i] = 0.0f;
        work->pos_z[i] = player->pos.z;
        work->unk_50[i] = 0.0f;
        // The do-while(0) block ends a CSE block, needed to match register allocation.
        do {
            rand8();
            rand8();
        } while (0);
        work->unk_64[i] = (i + 1) * 1.3f;
        if (i == 0) {
            obj->model[0] = func_8000B108_main(0x5E0007, attr);
            omSetTra(obj, work->pos_x[0], work->pos_y[0], work->pos_z[0]);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
            Hu3DModelPosSet(obj->model[i], work->pos_x[i % 5], work->pos_y[i % 5], work->pos_z[i % 5]);
        }
    }
    for (i = 0; i < 5; i++) {
        if (i == 0) {
            obj->model[5] = func_8000B108_main(0x5E0010, attr);
            omSetTra(obj, work->pos_x[0], work->pos_y[0], work->pos_z[0]);
        } else {
            obj->model[i + 5] = Hu3DModelLink(obj->model[5]);
            Hu3DModelPosSet(obj->model[i], work->pos_x[i % 5], work->pos_y[i % 5], work->pos_z[i % 5]);
        }
    }
    work->rise = 0.0f;
}

void func_80106F44_bobbing_bow_loons(omObjData *obj) {
    BobbingBowLoonsWork *work = obj->data;
    s32 i;

    for (i = 0; i < 5; i++) {
        if (i == 0) {
            omSetTra(obj, work->pos_x[0], work->pos_y[0], work->pos_z[0]);
        } else {
            Hu3DModelPosSet(obj->model[i], work->pos_x[i], work->pos_y[i], work->pos_z[i]);
        }
        Hu3DModelPosSet(obj->model[i + 5], work->pos_x[i], work->pos_y[i], work->pos_z[i] - 4.0f);
        if (work->state[i] & 1) {
            work->pos_y[i] = sindf(work->unk_50[i]) * 200.0f;
            work->unk_50[i] += work->unk_64[i];
            if (work->unk_50[i] >= 360.0f) {
                work->unk_50[i] -= 360.0f;
            }
            if (work->unk_50[i] <= 0.0f) {
                work->unk_50[i] += 360.0f;
            }
        }
        if (work->state[i] & 2) {
            work->pos_y[i] += work->rise;
            work->rise += 0.1f;
            if (work->pos_y[i] >= 500.0f) {
                work->state[i] &= ~2;
            }
        }
    }
}

void func_80107130_bobbing_bow_loons(void) {
    BobbingBowLoonsWork *work = D_80109B2C_bobbing_bow_loons->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(work->state); i++) {
        work->state[i] = (work->state[i] | 2) & ~1;
    }
    work->rise = 0;
}

s32 func_80107174_bobbing_bow_loons(void) {
    s32 hit = -1;
    BobbingBowLoonsWork *work = D_80109B2C_bobbing_bow_loons->data;
    BobbingBowLoonsHook *hook = D_80109B30_bobbing_bow_loons->data;
    f32 x = hook->x - 25.0f;
    f32 y = hook->y - 100.0f;
    f32 loonX;
    f32 loonY;
    s16 fx;
    s32 i;

    for (i = 0; i < 5; i++) {
        loonX = work->pos_x[i];
        loonY = work->pos_y[i] - 50.0f;
        if (fabs(x - loonX) < 50.0 && fabs(y - loonY) < 50.0) {
            hit = i;
            fx = HuAudFXPlay(0x4DC);
            if (fx >= 0) {
                HuAudFXPanning(fx, hit * 10 + 44);
            }
            return hit;
        }
    }
    return hit;
}

void func_8010728C_bobbing_bow_loons(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x50, 7, 0, -1, func_80107368_bobbing_bow_loons);
    obj->data = HuMemAllocTag(sizeof(BobbingBowLoonsStrings), 0x7918);
    D_80109B34_bobbing_bow_loons = obj;
    obj->model[0] = func_8000B108_main(0x5E0006, 0x4B9);
    for (i = 1; i < 7; i++) {
        obj->model[i] = Hu3DModelLink(obj->model[0]);
    }
    Hu3DData[obj->model[5]].scale.y = 1.2f;
}

void func_80107368_bobbing_bow_loons(omObjData *obj) {
    BobbingBowLoonsStrings *strings = obj->data;
    BobbingBowLoonsWork *work = D_80109B2C_bobbing_bow_loons->data;
    BobbingBowLoonsPlayer *player = D_80109B1C_bobbing_bow_loons->data;
    s32 i;

    for (i = 0; i < 5; i++) {
        strings->x[i] = work->pos_x[i];
        strings->y[i] = work->pos_y[i] - 100.0f;
        strings->z[i] = work->pos_z[i] - 2.0f;
    }
    strings->x[5] = player->pos.x + D_80109748_bobbing_bow_loons[GwPlayer[D_80109B0C_bobbing_bow_loons].chr];
    strings->y[5] = player->pos.y + 42.0f;
    strings->z[5] = player->pos.z - 2.0f;
    omSetTra(obj, strings->x[0], strings->y[0], strings->z[0]);
    for (i = 1; i < 7; i++) {
        Hu3DModelPosSet(obj->model[i], strings->x[i], strings->y[i], strings->z[i]);
    }
    func_8001C258_main(obj->model[6], 4, 4);
}

void func_801074CC_bobbing_bow_loons(void) {
    s32 counts[16];
    s32 itemFiles[16] = { 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60 };
    BobbingBowLoonsItems *items;
    BobbingBowLoonsWork *work;
    omObjData *obj;
    void *spriteData;
    s16 sprite;
    s32 total;
    s32 value; // Item index, then reused for the random roll
    s32 i;
    s32 j;

    obj = omAddObj(0xFE, 5, 0, -1, func_80107830_bobbing_bow_loons);
    obj->data = HuMemAllocTag(sizeof(BobbingBowLoonsItems), 0x7918);
    D_80109B38_bobbing_bow_loons = obj;
    items = obj->data;
    work = D_80109B2C_bobbing_bow_loons->data;
    for (i = 0; i < 16; i++) {
        counts[i] = 0;
    }
    for (i = 0; i < 5; i++) {
        value = D_800A11D0_main[4 - i];
        counts[value]++;
        D_80109B40_bobbing_bow_loons[i] = value;
        spriteData = DataRead(itemFiles[value] | 0x210000);
        sprite = Hu3DSprModelCreate(spriteData, 0x699, 8);
        DataClose(spriteData);
        obj->model[i] = D_800CBB60_main[sprite].modelId;
        items->x[i] = work->pos_x[i];
        items->y[i] = work->pos_y[i];
        items->z[i] = work->pos_z[i] - 2.0f;
        if (i == 0) {
            omSetTra(obj, items->x[0], items->y[0], items->z[0]);
            omSetSca(obj, 1.8f, 1.8f, 1.8f);
        } else {
            Hu3DModelPosSet(obj->model[i], items->x[i], items->y[i], items->z[i]);
            Hu3DModelScaleSet(obj->model[i], 1.8f, 1.8f, 1.8f);
        }
        items->state[i] = 1;
    }
    items->angle = 0.0f;
    items->heldX = 0.0f;
    items->heldY = 0.0f;
    if (GwPlayer[D_80109B0C_bobbing_bow_loons].stat & 1) {
        value = (u8)(rand8() % 100);
        for (j = 0, total = 0; j < 5; j++) {
            if (value >= total && value < total + D_800A11DC_main[j]) {
                break;
            }
            total += D_800A11DC_main[j];
        }
        if (j == 5) {
            j = 4;
        }
        D_80109B14_bobbing_bow_loons = j;
    }
}

void func_80107830_bobbing_bow_loons(omObjData *obj) {
    BobbingBowLoonsItems *items = obj->data;
    BobbingBowLoonsWork *work = D_80109B2C_bobbing_bow_loons->data;
    BobbingBowLoonsPlayer *player = D_80109B1C_bobbing_bow_loons->data;
    s32 i;

    for (i = 0; i < 5; i++) {
        if (items->state[i] & 1) {
            items->y[i] = work->pos_y[i] + 50.0f;
        }
        if (items->state[i] & 2) {
            items->x[i] = items->heldX;
            items->y[i] = sindf(items->angle) * 20.0f + items->heldY;
            items->z[i] = player->pos.z + 2.0f;
            items->angle += 10.0f;
            if (items->angle >= 360.0f) {
                items->angle -= 360.0f;
            }
            func_8000CFA4_main(D_80109B08_bobbing_bow_loons, items->x[i], items->y[i], items->z[i]);
        }
        if (i == 0) {
            omSetTra(obj, items->x[0], items->y[0], items->z[0]);
        } else {
            Hu3DModelPosSet(obj->model[i], items->x[i], items->y[i], items->z[i]);
        }
    }
}

void func_801079E8_bobbing_bow_loons(s32 idx) {
    BobbingBowLoonsItems *items = D_80109B38_bobbing_bow_loons->data;

    items->state[idx] |= 2;
    items->angle = 0.0f;
    items->heldX = 0.0f;
    items->heldY = 0.0f;
    D_80109B54_bobbing_bow_loons = idx;
    D_80109B10_bobbing_bow_loons = D_80109B40_bobbing_bow_loons[idx];
    D_80109B08_bobbing_bow_loons = func_8000CED8_main(0xB0004, 0x6A9);
    omAddPrcObj(func_80107A7C_bobbing_bow_loons, 0x50, 0, 0);
    HuAudFXPlay(0x4DD);
}

void func_80107A7C_bobbing_bow_loons(void) {
    BobbingBowLoonsWork *work = D_80109B2C_bobbing_bow_loons->data;
    BobbingBowLoonsItems *items = D_80109B38_bobbing_bow_loons->data;
    BobbingBowLoonsPlayer *player = D_80109B1C_bobbing_bow_loons->data;
    f32 dx;
    f32 dy;
    s32 i;

    func_80107130_bobbing_bow_loons();
    func_8001C258_main(D_80109B2C_bobbing_bow_loons->model[D_80109B54_bobbing_bow_loons], 4, 4);
    func_8001C258_main(D_80109B2C_bobbing_bow_loons->model[D_80109B54_bobbing_bow_loons + 5], 4, 4);
    func_8001C258_main(D_80109B34_bobbing_bow_loons->model[D_80109B54_bobbing_bow_loons], 4, 4);
    func_8001C258_main(D_80109B30_bobbing_bow_loons->model[0], 4, 4);
    func_80108F2C_bobbing_bow_loons(work->pos_x[D_80109B54_bobbing_bow_loons],
                                    work->pos_y[D_80109B54_bobbing_bow_loons] + 50.0f);
    items->heldX = items->x[D_80109B54_bobbing_bow_loons];
    items->heldY = items->y[D_80109B54_bobbing_bow_loons] + 50.0f;
    dx = (player->pos.x - items->x[D_80109B54_bobbing_bow_loons]) / 30.0f;
    dy = (player->pos.y + 150.0f - items->y[D_80109B54_bobbing_bow_loons]) / 30.0f;
    for (i = 0; i < 30; i++) {
        items->heldX += dx;
        items->heldY += dy;
        HuPrcVSleep();
    }
    func_80107D4C_bobbing_bow_loons();
    omDelPrcObj(NULL);
}

void func_80107C48_bobbing_bow_loons(void) {
    omAddPrcObj(func_80107C74_bobbing_bow_loons, 0x50, 0, 0);
}

void func_80107C74_bobbing_bow_loons(void) {
    s32 i;

    for (i = 0; i < 30; i++) {
        CZoom += (1500.0f - 1000.0f) / 30.0f;
        Center.x += (0.0f - 200.0f) / 30.0f;
        Center.y += (0.0f - 80.0f) / 30.0f;
        HuPrcVSleep();
    }
    CZoom = 1500.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    omDelPrcObj(NULL);
}

void func_80107D4C_bobbing_bow_loons(void) {
    omAddPrcObj(func_80107D78_bobbing_bow_loons, 0x50, 0, 0);
}

void func_80107D78_bobbing_bow_loons(void) {
    s32 i;

    for (i = 0; i < 30; i++) {
        CZoom -= (1500.0f - 1000.0f) / 30.0f;
        Center.x -= (0.0f - 200.0f) / 30.0f;
        Center.y -= (0.0f - 80.0f) / 30.0f;
        HuPrcVSleep();
    }
    CZoom = 1000.0f;
    Center.x = 200.0f;
    Center.y = 80.0f;
    func_801063F8_bobbing_bow_loons();
    omDelPrcObj(NULL);
}

void func_80107E68_bobbing_bow_loons(void) {
    omAddPrcObj(func_80107E94_bobbing_bow_loons, 0x50, 0, 0);
}

void func_80107E94_bobbing_bow_loons(void) {
    s32 i;

    for (i = 0; i < 20; i++) {
        CZoom -= (1500.0f - 1250.0f) / 20.0f;
        Center.x -= (0.0f - 100.0f) / 20.0f;
        Center.y -= (0.0f - 0.0f) / 20.0f;
        HuPrcVSleep();
    }
    CZoom = 1250.0f;
    Center.x = 100.0f;
    Center.y = 0.0f;
    omDelPrcObj(NULL);
}

void func_80107F68_bobbing_bow_loons(void) {
    omAddPrcObj(func_80107F94_bobbing_bow_loons, 0x50, 0, 0);
}

void func_80107F94_bobbing_bow_loons(void) {
    s32 seconds = 10;
    s32 frames = 30;

    GMesPosSet(GMesCreate(26, 10, 160, 28), 160.0f, 28.0f);
    do {
        frames--;
        if (frames == 0) {
            frames = 30;
            seconds--;
        }
        func_8003F578_main(seconds);
        HuPrcVSleep();
        if (D_80109B04_bobbing_bow_loons == 4) {
            break;
        }
    } while (seconds > 0);
    if (D_80109B04_bobbing_bow_loons == 0) {
        D_80109B04_bobbing_bow_loons = 2;
    }
    func_8003F5C0_main();
    omDelPrcObj(NULL);
}

void func_8010805C_bobbing_bow_loons(void) {
    BobbingBowLoonsHook *hook;
    BobbingBowLoonsPlayer *player;
    omObjData *obj;

    obj = omAddObj(0xFF, 1, 0, -1, func_8010817C_bobbing_bow_loons);
    D_80109B30_bobbing_bow_loons = obj;
    hook = HuMemAllocTag(sizeof(BobbingBowLoonsHook), 0x7918);
    obj->data = hook;
    player = D_80109B1C_bobbing_bow_loons->data;
    obj->model[0] = func_8000B108_main(0x5E0005, 0x699);
    hook->flags = 0;
    hook->x = 0.0f;
    hook->y = 50.0f;
    hook->z = player->pos.z;
    hook->rotZ = 270.0f;
    omSetTra(obj, hook->x, hook->y, hook->z);
    omSetRot(obj, 0.0f, 0.0f, hook->rotZ);
    Hu3DModelHookSet(obj->model[0], D_80109B1C_bobbing_bow_loons->model[0], "item_hook");
    func_8001C258_main(obj->model[0], 0x4000, 0x4000);
}

void func_8010817C_bobbing_bow_loons(omObjData *obj) {
    BobbingBowLoonsHook *hook = obj->data;
    s32 hit;

    omSetTra(obj, hook->x, hook->y, hook->z);
    omSetRot(obj, 0.0f, 0.0f, hook->rotZ);
    if (hook->flags & 1) {
        hook->x -= 23.0f;
        hit = func_80107174_bobbing_bow_loons();
        if (hit != -1) {
            func_800E6F0C_minigame(3);
            func_801079E8_bobbing_bow_loons(hit);
            hook->flags &= ~1;
            omVibrate(D_80109B0C_bobbing_bow_loons, 2, 2, 20);
        } else if (hook->x <= -290.0f) {
            D_80109B04_bobbing_bow_loons = 0;
            func_800E6F0C_minigame(3);
            func_80108328_bobbing_bow_loons();
            hook->flags &= ~1;
            omVibrate(D_80109B0C_bobbing_bow_loons, 20, 0, 20);
        }
    }
}

void func_8010829C_bobbing_bow_loons(void) {
    BobbingBowLoonsHook *hook = D_80109B30_bobbing_bow_loons->data;

    hook->x = D_80109B1C_bobbing_bow_loons->trans.x;
    hook->y = D_80109B1C_bobbing_bow_loons->trans.y + 100.0f;
    hook->flags |= 1;
    func_8001C258_main(D_80109B30_bobbing_bow_loons->model[0], 4, 0);
    func_8001C258_main(D_80109B30_bobbing_bow_loons->model[0], 0x4000, 0);
    HuAudFXPlay(0x4DB);
}

void func_80108328_bobbing_bow_loons(void) {
    omAddPrcObj(func_80108354_bobbing_bow_loons, 0x50, 0, 0);
}

void func_80108354_bobbing_bow_loons(void) {
    f32 offsetX[8] = { -20.0f, 0.0f, -15.0f, 31.5f, 5.0f, 19.2f, -15.0f, 0.0f };
    f32 offsetY[8] = { 100.0f, -19.0f, 70.0f, -106.2f, -18.0f, -107.1f, 70.0f, -16.0f };
    f32 offsetZ[8] = { 15.0f, -2.5f, 0.0f, 20.5f, 0.0f, 36.2f, 0.0f, 3.0f };
    BobbingBowLoonsHook *hook = D_80109B30_bobbing_bow_loons->data;
    BobbingBowLoonsPlayer *player = D_80109B1C_bobbing_bow_loons->data;
    BobbingBowLoonsWork *work = D_80109B2C_bobbing_bow_loons->data;
    f32 speed;
    s32 i;

    if (D_80109B04_bobbing_bow_loons != 2) {
        func_801091FC_bobbing_bow_loons();
    }
    for (i = 0; i < 5; i++) {
        work->state[i] &= ~1;
    }
    omSetTra(D_80109B58_bobbing_bow_loons, hook->x + 30.0f, hook->y - 30.0f, hook->z);
    func_801096E8_bobbing_bow_loons();
    HuAudFXPlay(0x4DE);
    hook->rotZ = 150.0f;
    while (hook->y < 400.0f) {
        hook->x += sindf(30.0f) * 23.0f;
        hook->y += cosdf(30.0f) * 23.0f;
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    hook->rotZ = 180.0f;
    hook->x = D_80109B1C_bobbing_bow_loons->trans.x;
    while (D_80109B1C_bobbing_bow_loons->trans.y + 300.0f <= hook->y) {
        hook->y -= 23.0f;
        HuPrcVSleep();
    }
    hook->y = D_80109B1C_bobbing_bow_loons->trans.y - 200.0f;
    func_8001C258_main(D_80109B30_bobbing_bow_loons->model[0], 4, 4);
    func_8001C258_main(D_80109B34_bobbing_bow_loons->model[5], 4, 4);
    func_8001C258_main(D_80109B1C_bobbing_bow_loons->model[1], 4, 4);
    func_80108F2C_bobbing_bow_loons(
        player->pos.x + D_80109748_bobbing_bow_loons[GwPlayer[D_80109B0C_bobbing_bow_loons].chr],
        player->pos.y + 230.0f);
    HuAudFXPlay(0x4DF);
    HuAudFXPlay(GwPlayer[D_80109B0C_bobbing_bow_loons].chr + 0x2AC);
    player->unk_00 &= ~1;
    player->pos.x -= offsetX[GwPlayer[D_80109B0C_bobbing_bow_loons].chr];
    player->pos.y -= offsetY[GwPlayer[D_80109B0C_bobbing_bow_loons].chr];
    player->pos.z -= offsetZ[GwPlayer[D_80109B0C_bobbing_bow_loons].chr];
    func_801064C0_bobbing_bow_loons();
    HuPrcSleep(30);
    func_8004AC98_main(GwPlayer[D_80109B0C_bobbing_bow_loons].chr + 0x287, D_80109B0C_bobbing_bow_loons);
    func_8001C814_main(D_80109B1C_bobbing_bow_loons->model[3], 1, 1);
    speed = -20.0f;
    while (player->pos.y >= -500.0f) {
        player->pos.y = speed + player->pos.y;
        speed -= 5.0f;
        HuPrcVSleep();
    }
    func_80109568_bobbing_bow_loons();
    func_800E6F0C_minigame(3);
    omDelPrcObj(NULL);
}

void func_80108894_bobbing_bow_loons(void) {
    omAddPrcObj(func_801088C0_bobbing_bow_loons, 0x50, 0, 0);
}

void func_801088C0_bobbing_bow_loons(void) {
    f32 angles[5];
    f32 minAngles[5] = { 120.0f, 300.0f, 120.0f, 320.0f, 160.0f };
    f32 maxAngles[5] = { 140.0f, 320.0f, 140.0f, 340.0f, 180.0f };
    f32 targetAngles[5];
    BobbingBowLoonsWork *work;
    s32 done = FALSE;
    s32 range;
    s32 hit;
    s32 i;
    f32 y;

    work = D_80109B2C_bobbing_bow_loons->data;
    do {
        if (GwPlayer[D_80109B0C_bobbing_bow_loons].stat & 1) {
            range = (4 - GwPlayer[D_80109B0C_bobbing_bow_loons].cpu_difficulty) * 5;
            for (i = 0; i < 5; i++) {
                targetAngles[i] = (rand8() % (range * 2) - range) + minAngles[i];
            }
            angles[D_80109B14_bobbing_bow_loons] = work->unk_50[D_80109B14_bobbing_bow_loons];
            hit = 0;
            if (maxAngles[D_80109B14_bobbing_bow_loons] < 360.0f) {
                if (targetAngles[D_80109B14_bobbing_bow_loons] <= angles[D_80109B14_bobbing_bow_loons] &&
                    angles[D_80109B14_bobbing_bow_loons] < maxAngles[D_80109B14_bobbing_bow_loons]) {
                    hit++;
                }
            } else if ((angles[D_80109B14_bobbing_bow_loons] >= 0.0f &&
                        angles[D_80109B14_bobbing_bow_loons] < maxAngles[D_80109B14_bobbing_bow_loons] - 360.0f) ||
                       (angles[D_80109B14_bobbing_bow_loons] >= minAngles[D_80109B14_bobbing_bow_loons] &&
                        angles[D_80109B14_bobbing_bow_loons] < 360.0f)) {
                hit++;
            }
            if (hit != 0) {
                hit = 0;
                y = work->pos_y[D_80109B14_bobbing_bow_loons];
                for (i = D_80109B14_bobbing_bow_loons + 1; i < 5; i++) {
                    if (work->pos_y[i] >= y - 20.0f && work->pos_y[i] < y + 20.0f) {
                        hit++;
                        break;
                    }
                }
                if (hit == 0) {
                    D_80109B04_bobbing_bow_loons = 3;
                    break;
                }
            }
        } else if (D_800D5558_main[GwPlayer[D_80109B0C_bobbing_bow_loons].pad] & 0x8000) {
            D_80109B04_bobbing_bow_loons = 3;
            break;
        }
        HuPrcVSleep();
    } while (!done);
    omDelPrcObj(NULL);
}

void func_80108C18_bobbing_bow_loons(s32 recolor) {
    BobbingBowLoonsEffect *effect;
    omObjData *obj;

    obj = omAddObj(0xFF, 2, 0, -1, func_80108E5C_bobbing_bow_loons);
    D_80109B5C_bobbing_bow_loons = obj;
    effect = obj->data = HuMemAllocTag(sizeof(BobbingBowLoonsEffect), 0x7918);
    obj->model[0] = func_8000B108_main(0x5E0011, 0x6CD);
    func_8001C2FC_main(obj->model[0], 0x20000, 0x20000);
    func_8001C954_main(obj->model[0]);
    obj->model[1] = func_8000B108_main(0x5E0012, 0x6DD);
    if (recolor) {
        switch (GwPlayer[D_80109B0C_bobbing_bow_loons].chr) {
            case 0:
                func_8001E500_main(obj->model[0], "c0_DEF", "c1_DEF");
                break;
            case 1:
                func_8001E500_main(obj->model[0], "c0_DEF", "c2_DEF");
                break;
            case 2:
                func_8001E500_main(obj->model[0], "c0_DEF", "c3_DEF");
                break;
            case 3:
                func_8001E500_main(obj->model[0], "c0_DEF", "c4_DEF");
                break;
            case 4:
                func_8001E500_main(obj->model[0], "c0_DEF", "c5_DEF");
                break;
            case 5:
                func_8001E500_main(obj->model[0], "c0_DEF", "c6_DEF");
                break;
            case 6:
                func_8001E500_main(obj->model[0], "c0_DEF", "c7_DEF");
                break;
            case 7:
                func_8001E500_main(obj->model[0], "c0_DEF", "c8_DEF");
                break;
        }
    }
    func_8001FA68_main(obj->model[0]);
    func_8001F9E4_main(obj->model[0], 0xA0);
    Hu3DModelRemakeStatic(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    effect->x = 0.0f;
    effect->y = 0.0f;
    effect->z = 0.0f;
    effect->flags = 0;
    effect->timer = 0;
    effect->scale = 0.1f;
}

void func_80108E5C_bobbing_bow_loons(omObjData *obj) {
    BobbingBowLoonsEffect *effect = obj->data;

    omSetTra(obj, effect->x, effect->y, effect->z);
    if (effect->flags & 1) {
        effect->scale += 0.03f;
        func_8001D558_main(obj->model[0], effect->scale, effect->scale * 25.0f, 2);
        if (++effect->timer == 30) {
            func_8001C258_main(D_80109B5C_bobbing_bow_loons->model[0], 4, 4);
            effect->flags &= ~1;
        }
    }
}

void func_80108F2C_bobbing_bow_loons(f32 x, f32 y) {
    BobbingBowLoonsPlayer *player = D_80109B1C_bobbing_bow_loons->data;
    BobbingBowLoonsEffect *effect;
    s32 recolor;
    f32 scale;

    if (x == player->pos.x + D_80109748_bobbing_bow_loons[GwPlayer[D_80109B0C_bobbing_bow_loons].chr]) {
        scale = 1.5f;
        recolor = TRUE;
    } else {
        recolor = FALSE;
        scale = 1.0f;
    }
    func_80108C18_bobbing_bow_loons(recolor);
    effect = D_80109B5C_bobbing_bow_loons->data;
    effect->flags |= 1;
    func_8001C258_main(D_80109B5C_bobbing_bow_loons->model[0], 4, 0);
    effect->x = x;
    effect->y = y;
    effect->z = 16.0f;
    omSetSca(D_80109B5C_bobbing_bow_loons, scale, scale, scale);
}

void func_80109044_bobbing_bow_loons(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0xFF, 2, 0, -1, func_801090EC_bobbing_bow_loons);
    D_80109B60_bobbing_bow_loons = obj;
    obj->data = HuMemAllocTag(sizeof(BobbingBowLoonsLoon), 0x7918);
    obj->model[0] = func_8000B108_main(0x5D0008, 0xA3D);
    for (i = 1; i < 5; i++) {
        obj->model[i] = Hu3DModelLink(obj->model[0]);
    }
}

void func_801090EC_bobbing_bow_loons(omObjData *obj) {
    BobbingBowLoonsLoon *loons = obj->data;
    s32 i;

    omSetTra(obj, loons->x[0], loons->y[0], loons->z[0]);
    for (i = 1; i < 5; i++) {
        Hu3DModelPosSet(obj->model[i], loons->x[i], loons->y[i], loons->z[i]);
    }
    if (D_800CCF58_main[Hu3DData[obj->model[0]].motId].unk02 <= Hu3DData[obj->model[0]].motTime) {
        for (i = 0; i < 5; i++) {
            func_8001C258_main(obj->model[i], 4, 4);
        }
    }
}

void func_801091FC_bobbing_bow_loons(void) {
    BobbingBowLoonsLoon *loons = D_80109B60_bobbing_bow_loons->data;
    BobbingBowLoonsWork *work = D_80109B2C_bobbing_bow_loons->data;
    s32 i;

    for (i = 0; i < 5; i++) {
        func_8001C258_main(D_80109B2C_bobbing_bow_loons->model[i], 4, 4);
        func_8001C258_main(D_80109B34_bobbing_bow_loons->model[i], 4, 4);
        func_8001C258_main(D_80109B38_bobbing_bow_loons->model[i], 4, 4);
        loons->x[i] = work->pos_x[i];
        loons->y[i] = work->pos_y[i] + 50.0f;
        loons->z[i] = work->pos_z[i] + 2.0f;
        work->state[i] &= ~1;
        work->pos_y[i] = -1000.0f;
        func_8001C258_main(D_80109B60_bobbing_bow_loons->model[i], 4, 0);
    }
}

void func_8010934C_bobbing_bow_loons(void) {
    BobbingBowLoonsLoon *loons = OM_GET_DATA_PTR(D_80109B60_bobbing_bow_loons, BobbingBowLoonsLoon);
    BobbingBowLoonsPlayer *player = OM_GET_DATA_PTR(D_80109B1C_bobbing_bow_loons, BobbingBowLoonsPlayer);

    loons->x[0] = player->pos.x;
    loons->y[0] = player->pos.y + 50.0f;
    loons->z[0] = player->pos.z + 2.0f;
    func_8001C258_main(D_80109B60_bobbing_bow_loons->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionTimeSet(D_80109B60_bobbing_bow_loons->model[0], 0.0f);
}

void func_801093DC_bobbing_bow_loons(void) {
    BobbingBowLoonsHost *host;
    omObjData *obj;

    obj = omAddObj(0xFF, 2, 0, -1, func_801094B0_bobbing_bow_loons);
    D_80109B64_bobbing_bow_loons = obj;
    host = HuMemAllocTag(sizeof(BobbingBowLoonsHost), 0x7918);
    obj->data = host;
    obj->model[0] = func_8000B108_main(0xA00EE, 0x6D9);
    omSetSca(obj, 0.7f, 0.7f, 0.7f);
    omSetRot(obj, 0.0f, 325.0f, 0.0f);
    func_8001C814_main(obj->model[0], 2, 2);
    host->y = -130.0f;
    host->headRot = 0.0f;
}

void func_801094B0_bobbing_bow_loons(omObjData *obj) {
    BobbingBowLoonsHost *host = obj->data;
    HmfMotionNode *node;
    s16 model;

    omSetTra(obj, 370.0f, host->y, -70.0f);
    model = obj->model[0];
    func_8002FD8C_main(model, Hu3DData[model].motId, "c162_000-atama", 0x4C, 0x45);
    node = func_8001D33C_main(model, "c162_000-atama");
    node->baseRot.x = host->headRot;
    node->rot.x = host->headRot;
    func_8001C814_main(obj->model[0], 1, 1);
}

void func_80109568_bobbing_bow_loons(void) {
    omAddPrcObj(func_80109594_bobbing_bow_loons, 0x50, 0, 0);
}

void func_80109594_bobbing_bow_loons(void) {
    BobbingBowLoonsHost *host = D_80109B64_bobbing_bow_loons->data;
    s32 i;
    s32 j;

    for (i = 0; i < 10; i++) {
        host->y += 10.0f;
        HuPrcVSleep();
    }
    func_80107E68_bobbing_bow_loons();
    HuPrcSleep(20);
    HuAudFXPlay(0x2A0);
    for (i = 0; i < 30; i++) {
        for (j = 0; j < 2; j++) {
            host->headRot += 8.0f;
            HuPrcVSleep();
        }
        for (j = 0; j < 2; j++) {
            host->headRot -= 8.0f;
            HuPrcVSleep();
        }
    }
    omDelPrcObj(NULL);
}

void func_80109680_bobbing_bow_loons(void) {
    omObjData *object = omAddObj(0xFF, 1, 0, -1, NULL);

    D_80109B58_bobbing_bow_loons = object;
    object->data = HuMemAllocTag(8, TAG_OVERLAY);
    object->model[0] = func_8000B108_main(0xB0003, 0x6DD);
}

void func_801096E8_bobbing_bow_loons(void) {
    func_8001C258_main(D_80109B58_bobbing_bow_loons->model[0], 4, 0);
}
