#include "common.h"
#include "game/camera.h"
#include "game/camsetup.h"
#include "game/util.h"
#include "game/esprite.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"
#include "humath.h"
#include "overlays/minigame.h"

// Grid cell value marking a cell that was just filled.
#define ETCH_N_CATCH_CELL_FILLED 0x21

#define ABS(x) ((x) > 0.0f ? (x) : 0.0f - (x))

// Per-player record. D_801113D8_etch_n_catch points at one 0x100-entry array of
// these per player, and a record is free for reuse while unk_00 is zero.
// Records are chained through unk_04/unk_08/unk_0C.
typedef struct EtchNCatchNode {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ struct EtchNCatchNode *unk_04;
    /* 0x08 */ struct EtchNCatchNode *unk_08;
    /* 0x0C */ struct EtchNCatchNode *unk_0C;
    /* 0x10 */ char unk_10[0x28];
} EtchNCatchNode; // sizeof 0x38

// Heap-allocated (0x20 bytes) work block; unk_0C is the head of a linked list
// of nodes (func_80108B64 inserts, func_80108BCC removes, func_80108C08 walks).
typedef struct EtchNCatchWork {
    /* 0x00 */ char unk_00[0xC];
    /* 0x0C */ struct EtchNCatchNode *unk_0C;
    /* 0x10 */ char unk_10[0x10];
} EtchNCatchWork; // sizeof 0x20

// Byte grid of player slots: D_8010C84C_etch_n_catch is the base address and
// D_8010C846_etch_n_catch the row stride in bytes.
extern u8 *D_8010C84C_etch_n_catch;
extern s16 D_8010C846_etch_n_catch;
extern EtchNCatchNode *D_801113D8_etch_n_catch[4];

// Heap-allocated list of grid cells touched this frame, one pointer per entry.
extern u8 **D_8010C878_etch_n_catch;

// Minigame object owning the etch/catch models. unk_40 points at the three model
// handles, unk_18/unk_30 are the position and scale triples written to them.
typedef struct EtchNCatchObj {
    /* 0x00 */ char unk_00[0x18];
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ char unk_24[0xC];
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ char unk_3C[4];
    /* 0x40 */ s16 *unk_40;
} EtchNCatchObj; // sizeof 0x44

// Per-object data of the player objects created by func_80109A54_etch_n_catch.
typedef struct EtchNCatchPlayerData {
    /* 0x000 */ func_800E1BA8_minigame_ObjData base;
    /* 0x15C */ s32 unk15C;
    /* 0x160 */ u8 unk160; // Index into D_801113E8_etch_n_catch
    /* 0x161 */ u8 unk161;
    /* 0x164 */ f32 unk164;
    /* 0x168 */ s32 unk168;
    /* 0x16C */ f32 unk16C;
    /* 0x170 */ f32 unk170;
    /* 0x174 */ char unk174[0x1B8 - 0x174];
} EtchNCatchPlayerData; // sizeof 0x1B8

// Per-object data of the objects created by func_8010B24C_etch_n_catch.
typedef struct EtchNCatchBoardWork {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
} EtchNCatchBoardWork; // sizeof 0xC

extern s16 D_8010C6A4_etch_n_catch[2][2];
extern f32 D_8010C6B0_etch_n_catch;
extern f32 D_8010C6B8_etch_n_catch;
extern u8 D_8010C840_etch_n_catch;
extern u16 D_801113E8_etch_n_catch[4];
extern s8 D_8010C6AC_etch_n_catch;
extern s8 D_8010C6AD_etch_n_catch;
extern omObjData *D_8010C858_etch_n_catch[2];
extern omObjData *D_8010C860_etch_n_catch[2];
extern void *D_8010C868_etch_n_catch[4];
extern void *D_8010C87C_etch_n_catch[2];
extern u16 D_801113A8_etch_n_catch[2];
extern D_80111B50_vine_with_me_Struct D_801113B0_etch_n_catch;

void func_80105CD0_etch_n_catch(D_80111B50_vine_with_me_Struct *arg0);
void func_80105D5C_etch_n_catch(void);
void func_80105ED4_etch_n_catch(omObjData *object);
void func_80106334_etch_n_catch(omObjData *object);
void func_80109A54_etch_n_catch(omObjData *object);
void func_8010B24C_etch_n_catch(omObjData *object);
void func_8010B3B4_etch_n_catch(omObjData *object);
void func_8010BBE4_etch_n_catch(omObjData *object);
void func_8010BE84_etch_n_catch(omObjData *object);
void func_8010C390_etch_n_catch(omObjData *object);
void func_8010C444_etch_n_catch(omObjData *object);
f32 func_8010C4F8_etch_n_catch(f32 arg0);

void func_801059A0_etch_n_catch(void) {
    s32 i;

    func_8001FE20_main(32);
    func_80021BE0_main(&D_800EBEB0_minigame, 64);
    func_800142A0_main(64);
    omInitObjMan(32, 0);
    func_8004A208_main();
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E1804_minigame();
    func_80105CD0_etch_n_catch(&D_801113B0_etch_n_catch);
    func_800E5EA0_minigame(&D_801113B0_etch_n_catch);
    Hu3DGLightColorSet(1, 64, 64, 64);
    Hu3DGLightDirSet(1, 0.0f, 0.0f, 100.0f);
    omSetStatBit(omAddObj(0, 0, 0, -1, func_80105ED4_etch_n_catch), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_80105D5C_etch_n_catch();
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(2, 1, 0, -1, func_8010C390_etch_n_catch);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(2, 1, 0, -1, func_8010C444_etch_n_catch);
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(1, 0, 0, -1, func_8010BE84_etch_n_catch);
    func_800E18D8_minigame();
    D_800EB740_minigame = 0.5f;
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 5, 60, -1, func_80106334_etch_n_catch);
        omSetStatBit(D_800EC598_minigame[i], OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
        D_801113D8_etch_n_catch[i] = HuMemAllocTag(0x100 * sizeof(EtchNCatchNode), TAG_OVERLAY);
        memset(D_801113D8_etch_n_catch[i], 0, 0x100 * sizeof(EtchNCatchNode));
    }
    for (i = 0; i < 2; i++) {
        D_8010C860_etch_n_catch[i] = omAddObj(2, 3, 0, -1, func_8010B24C_etch_n_catch);
        D_8010C858_etch_n_catch[i] = omAddObj(2, 7, 2, -1, func_80109A54_etch_n_catch);
    }
    omAddObj(3, 0, 0, -1, func_8010BBE4_etch_n_catch);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
}

void func_80105CD0_etch_n_catch(D_80111B50_vine_with_me_Struct *arg0) {
    s32 i;

    D_800EB932_minigame = 60;
    arg0->unk00 = 0;
    arg0->unk01 = 1;
    arg0->unk02 = 1;
    arg0->unk03 = 2;
    arg0->unk04 = 0;
    arg0->unk05 = 0;
    arg0->unk06 = 0;
    arg0->unk1C = 90;
    arg0->unk1E = 900;
    arg0->unk20 = -1;
    arg0->unk22 = 75;
    arg0->unk24 = 150;
    for (i = 0; i < 4; i++) {
        arg0->unk08[i] = 0;
        arg0->unk18[i] = 0xFF;
    }
}

void func_80105D5C_etch_n_catch(void) {
    s32 camIndex;
    HuCamera *camera;

    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(camIndex, 27.211f, 80.0f, 8000.0f);
    camera = &gCameraList[camIndex];
    camera->pos.x = -1.965f;
    camera->pos.y = 1392.72f;
    camera->pos.z = 1374.455f;
    camera->at.x = -1.965f;
    camera->at.y = 60.495f;
    camera->at.z = 20.66f;
    camera->up.x = 0.0f;
    camera->up.y = 0.5f;
    camera->up.z = -0.8660254f;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80105ED4_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80106334_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80106A64_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80107D38_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80107EA4_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010880C_etch_n_catch);

void func_80108B20_etch_n_catch(EtchNCatchWork *arg0) {
    arg0->unk_0C = NULL;
}

EtchNCatchNode *func_80108B28_etch_n_catch(s8 playerId) {
    EtchNCatchNode *node = D_801113D8_etch_n_catch[playerId];
    s32 i;

    for (i = 0; i < 0x100; i++) {
        if (node->unk_00 == 0) {
            break;
        }
        node++;
    }
    return node;
}

void func_80108B64_etch_n_catch(EtchNCatchNode **head, EtchNCatchNode *node) {
    EtchNCatchNode *prev = *head;

    if (prev != NULL) {
        while (prev->unk_08 != NULL) {
            prev = prev->unk_08;
        }
        node->unk_08 = prev->unk_08;
        node->unk_04 = prev;
        prev->unk_08 = node;
        if (node->unk_08 != NULL) {
            node->unk_08->unk_04 = node;
        }
        return;
    }

    node->unk_08 = *head;
    node->unk_04 = NULL;
    *head = node;
    if (prev != NULL) {
        prev->unk_04 = node;
    }
}

void func_80108BCC_etch_n_catch(EtchNCatchNode **head, EtchNCatchNode *node) {
    if (node->unk_08 != NULL) {
        node->unk_08->unk_04 = node->unk_04;
    }
    if (node->unk_04 != NULL) {
        node->unk_04->unk_08 = node->unk_08;
    } else {
        *head = node->unk_08;
    }
    node->unk_00 = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80108C08_etch_n_catch);

// Undoes the "filled" mark on every grid cell appended to the touched-cell list
// up to (but not including) arg0.
void func_80108D84_etch_n_catch(u8 **arg0) {
    u8 **cellPtr = D_8010C878_etch_n_catch;
    // arg0 points one past the last appended cell, so the difference is a byte offset.
    s32 count = ((s32)arg0 - (s32)cellPtr) >> 2;
    s32 i;

    for (i = 0; i < count; i++) {
        u8 *cell = *cellPtr++;
        if (cell[0] == ETCH_N_CATCH_CELL_FILLED) {
            cell[0] = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80108DD0_etch_n_catch);

u8 *func_801090E0_etch_n_catch(s16 x, s16 y) {
    return D_8010C84C_etch_n_catch + D_8010C846_etch_n_catch * y + x;
}

u8 func_80109114_etch_n_catch(s16 x, s16 y) {
    u8 *p = D_8010C84C_etch_n_catch + D_8010C846_etch_n_catch * y + x;
    return *p;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010914C_etch_n_catch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C740_etch_n_catch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C758_etch_n_catch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C770_etch_n_catch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C788_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80109370_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_801097B4_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80109A54_etch_n_catch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C7BC_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80109EB8_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010AB7C_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010AD6C_etch_n_catch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C7F0_etch_n_catch);

void func_8010AEE4_etch_n_catch(EtchNCatchPlayerData *data) {
    if (data->unk15C < 16) {
        data->unk164 -= 0.01f;
    } else if (data->unk15C < 8) {
        data->unk164 += 0.01f;
    } else if (data->unk15C < 10) {
        data->unk164 -= 0.01;
    } else {
        data->unk164 += 0.01;
    }
    espScaleSet(D_801113E8_etch_n_catch[data->unk160], data->unk164, data->unk164);
}

void func_8010AFB8_etch_n_catch(EtchNCatchPlayerData *data) {
    f32 diff;

    data->unk170 = func_8010C4F8_etch_n_catch(data->unk170);
    diff = data->unk16C - data->unk170;
    if (ABS(diff) > 5.0f) {
        if ((diff > 0.0f && diff < 180.0f) || (diff < -180.0f && diff > -360.0f)) {
            data->unk170 += 5.0f;
        } else {
            data->unk170 -= 5.0f;
        }
    } else {
        data->unk170 += diff;
    }
    data->unk170 = func_8010C4F8_etch_n_catch(data->unk170);
    espZRotSet(D_801113E8_etch_n_catch[data->unk160], data->unk170);
}

s32 func_8010B154_etch_n_catch(s16 x, s16 y) {
    s32 count = 0;
    s32 result;

    if (func_80109114_etch_n_catch(x, y) != 0) {
        result = TRUE;
    } else {
        count += func_80109114_etch_n_catch(x - 1, y) != 0;
        count += func_80109114_etch_n_catch(x + 1, y) != 0;
        count += func_80109114_etch_n_catch(x, y - 1) != 0;
        count += func_80109114_etch_n_catch(x, y + 1) != 0;
        result = count >= 3;
    }
    return result;
}

void func_8010B24C_etch_n_catch(omObjData *object) {
    EtchNCatchBoardWork *work;

    object->data = HuMemAllocTag(sizeof(EtchNCatchBoardWork), TAG_OVERLAY);
    memset(object->data, 0, sizeof(EtchNCatchBoardWork));
    work = object->data;
    work->unk01 = 0;
    work->unk00 = D_8010C840_etch_n_catch;
    work->unk04 = 0;
    work->unk08 = 0;
    work->unk02 = 0;
    object->work[0] = 0;
    switch (work->unk00) {
        case 0:
            object->trans.x = D_8010C6B0_etch_n_catch;
            break;
        case 1:
            object->trans.x = -D_8010C6B0_etch_n_catch;
            break;
    }
    object->trans.y = 800.0f;
    object->trans.z = D_8010C6B8_etch_n_catch;
    object->model[0] = func_8000B108_main(0x330002, 0x8B9);
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    object->model[1] = func_8000B108_main(0x330008, 0x89D);
    object->model[2] = func_8000B108_main(9, 0x8B9);
    Hu3DModelPosSet(object->model[2], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[2], 0.0f, 0.0f, 0.0f);
    object->func = func_8010B3B4_etch_n_catch;
    D_8010C840_etch_n_catch++;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010B3B4_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010BBE4_etch_n_catch);

void func_8010BD98_etch_n_catch(void) {
    func_8000BD50_main(D_801113A8_etch_n_catch[0], (s8)(D_8010C6AC_etch_n_catch % 10));
    espPosSet(D_801113A8_etch_n_catch[0], D_8010C6A4_etch_n_catch[0][0], D_8010C6A4_etch_n_catch[0][1]);
    func_8000BD50_main(D_801113A8_etch_n_catch[1], (s8)(D_8010C6AD_etch_n_catch % 10));
    espPosSet(D_801113A8_etch_n_catch[1], D_8010C6A4_etch_n_catch[1][0], D_8010C6A4_etch_n_catch[1][1]);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010BE84_etch_n_catch);

void func_8010C2F4_etch_n_catch(void) {
    s32 i;

    HuMemFree(D_8010C878_etch_n_catch);
    HuMemFree(D_8010C87C_etch_n_catch[0]);
    HuMemFree(D_8010C87C_etch_n_catch[1]);
    for (i = 0; i < 4; i++) {
        void *mem = D_8010C868_etch_n_catch[i];

        HuMemFree(D_801113D8_etch_n_catch[i]);
        HuMemFree(mem);
    }
}

void func_8010C390_etch_n_catch(omObjData *object) {
    D_800EC1C0_minigame_ObjData *work;

    object->model[0] = -1;
    object->func = NULL;
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 0;
    work->unk08 = 0.5f;
    func_800E139C_minigame(object, 0.0f, -450.0f, -400.0f, -80.0f, 300.0f);
    func_800E1468_minigame(object);
}

void func_8010C444_etch_n_catch(omObjData *object) {
    D_800EC1C0_minigame_ObjData *work;

    object->model[0] = -1;
    object->func = NULL;
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 1;
    work->unk08 = 0.5f;
    func_800E139C_minigame(object, 0.0f, 80.0f, -400.0f, 450.0f, 300.0f);
    func_800E1468_minigame(object);
}

f32 func_8010C4F8_etch_n_catch(f32 arg0) {
    while (arg0 >= 360.0f) {
        arg0 -= 360.0f;
    }
    while (arg0 < 0.0f) {
        arg0 += 360.0f;
    }
    return arg0;
}

Vec2f func_8010C574_etch_n_catch(s32 x0, s32 y0, s32 x1, s32 y1) {
    Vec2f dir;
    f32 len;

    dir.x = x1 - x0;
    dir.y = y1 - y0;
    len = HuSqrtf(dir.x * dir.x + dir.y * dir.y);
    if (len == 0.0f) {
        dir.y = 0.0f;
        dir.x = 0.0f;
    } else {
        dir.x /= len;
        dir.y /= len;
    }
    return dir;
}

void func_8010C628_etch_n_catch(EtchNCatchObj *obj, f32 scale) {
    obj->unk_38 = scale;
    obj->unk_34 = scale;
    obj->unk_30 = scale;
    Hu3DModelScaleSet(obj->unk_40[0], scale, obj->unk_34, obj->unk_38);
    Hu3DModelScaleSet(obj->unk_40[1], obj->unk_30, obj->unk_34, obj->unk_38);
    Hu3DModelScaleSet(obj->unk_40[2], obj->unk_30, obj->unk_34, obj->unk_38);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C820_etch_n_catch);
