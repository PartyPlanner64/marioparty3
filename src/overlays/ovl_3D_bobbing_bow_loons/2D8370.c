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

extern f32 D_80109748_bobbing_bow_loons[];
extern s32 D_80109768_bobbing_bow_loons[];
extern char *D_80109788_bobbing_bow_loons[];
extern s32 D_801097A8_bobbing_bow_loons[];
extern s32 D_80109B0C_bobbing_bow_loons;
extern s16 D_80109B20_bobbing_bow_loons[2];
extern omObjData *D_80109B28_bobbing_bow_loons;
extern s16 D_80109B18_bobbing_bow_loons;
extern omObjData *D_80109B1C_bobbing_bow_loons;
extern omObjData *D_80109B2C_bobbing_bow_loons;
extern omObjData *D_80109B58_bobbing_bow_loons;
extern omObjData *D_80109B60_bobbing_bow_loons;
extern D_80111B50_vine_with_me_Struct D_80109720_bobbing_bow_loons;
extern u8 D_80109B04_bobbing_bow_loons;
extern s16 D_80109B06_bobbing_bow_loons;
extern s32 D_80109B10_bobbing_bow_loons;

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

    sprite = espEntry(func_8000B838_main(0x5E0000), 0, 1);
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

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_801097D0_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_801097E4_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_801097F8_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_8010980C_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109820_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109834_bobbing_bow_loons);

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

#ifdef NON_MATCHING
// The original recomputes the work entry address after the two rand8 calls;
// GCC keeps it live across them in a saved register, shifting register usage.
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
        rand8();
        rand8();
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
            Hu3DModelPosSet(obj->model[i + 5], work->pos_x[i % 5], work->pos_y[i % 5], work->pos_z[i % 5]);
        }
    }
    work->rise = 0.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80106CC0_bobbing_bow_loons);
#endif

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80107174_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_8010728C_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80107368_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801074CC_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80107830_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801079E8_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80107A7C_bobbing_bow_loons);

void func_80107C48_bobbing_bow_loons(void) {
    omAddPrcObj(func_80107C74_bobbing_bow_loons, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80107C74_bobbing_bow_loons);

void func_80107D4C_bobbing_bow_loons(void) {
    omAddPrcObj(func_80107D78_bobbing_bow_loons, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80107D78_bobbing_bow_loons);

void func_80107E68_bobbing_bow_loons(void) {
    omAddPrcObj(func_80107E94_bobbing_bow_loons, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80107E94_bobbing_bow_loons);

void func_80107F68_bobbing_bow_loons(void) {
    omAddPrcObj(func_80107F94_bobbing_bow_loons, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80107F94_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_801099A8_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_8010805C_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_8010817C_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_8010829C_bobbing_bow_loons);

void func_80108328_bobbing_bow_loons(void) {
    omAddPrcObj(func_80108354_bobbing_bow_loons, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80108354_bobbing_bow_loons);

void func_80108894_bobbing_bow_loons(void) {
    omAddPrcObj(func_801088C0_bobbing_bow_loons, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801088C0_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_801099F4_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109A14_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109A34_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109A54_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109A68_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80108C18_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80108E5C_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80108F2C_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80109044_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801090EC_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801091FC_bobbing_bow_loons);

void func_8010934C_bobbing_bow_loons(void) {
    BobbingBowLoonsLoon *loons = OM_GET_DATA_PTR(D_80109B60_bobbing_bow_loons, BobbingBowLoonsLoon);
    BobbingBowLoonsPlayer *player = OM_GET_DATA_PTR(D_80109B1C_bobbing_bow_loons, BobbingBowLoonsPlayer);

    loons->x[0] = player->pos.x;
    loons->y[0] = player->pos.y + 50.0f;
    loons->z[0] = player->pos.z + 2.0f;
    func_8001C258_main(D_80109B60_bobbing_bow_loons->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionTimeSet(D_80109B60_bobbing_bow_loons->model[0], 0.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801093DC_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801094B0_bobbing_bow_loons);

void func_80109568_bobbing_bow_loons(void) {
    omAddPrcObj(func_80109594_bobbing_bow_loons, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80109594_bobbing_bow_loons);

void func_80109680_bobbing_bow_loons(void) {
    omObjData *object = omAddObj(0xFF, 1, 0, -1, NULL);

    D_80109B58_bobbing_bow_loons = object;
    object->data = HuMemAllocTag(8, TAG_OVERLAY);
    object->model[0] = func_8000B108_main(0xB0003, 0x6DD);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801096E8_bobbing_bow_loons);
