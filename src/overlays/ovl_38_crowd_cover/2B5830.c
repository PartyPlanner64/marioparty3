#include "common.h"
#include "overlays/minigame.h"
#include "game/hmfmath.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"
#include "game/texload.h"

typedef struct UnkCrowdCover {
    /* 0x00 */ Gfx *displayList;
    /* 0x04 */ Vtx_t *vtx;
    /* 0x08 */ HuSprite_Unk84_Struct *sprite;
    /* 0x0C */ struct UnkCrowdCover *prev;
    /* 0x10 */ struct UnkCrowdCover *next;
    /* 0x14 */ void (*callback)(struct UnkCrowdCover *);
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19;
    /* 0x1A */ s8 unk_1A;
    /* 0x1B */ s8 unk_1B;
    /* 0x1C */ s8 unk_1C;
    /* 0x1D */ u8 unk_1D;
    /* 0x1E */ u8 unk_1E;
    /* 0x1F */ u8 unk_1F;
    /* 0x20 */ u16 unk_20;
    /* 0x22 */ u16 unk_22;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ char pad_26[2];
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ Vec unk_30;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ Vec unk_40;
    /* 0x4C */ Vec unk_4C;
    /* 0x58 */ Vec unk_58;
    /* 0x64 */ f32 unk_64;
} UnkCrowdCover; // sizeof 0x68

typedef struct {
    /* 0x00 */ s16 unk00[9];
} UnkCrowdCoverVec; // sizeof 0x12

// Per-player work allocated in func_80107298_crowd_cover, stored at ObjData->unk158
typedef struct {
    /* 0x00 */ char unk00[0x20];
    /* 0x20 */ s16 unk20;
    /* 0x22 */ char unk22[2];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 unk29;
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ u8 unk2C;
    /* 0x2D */ u8 unk2D;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 unk2F;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ u16 unk34;
    /* 0x36 */ u16 unk36;
    /* 0x38 */ char unk38[0x1C];
} UnkCrowdCoverWork; // sizeof 0x54

extern f32 D_8010D868_crowd_cover[4][4];
extern f32 D_8010D8A0_crowd_cover;
extern f32 D_8010D8A8_crowd_cover[4][4];
extern f32 D_8010D8E8_crowd_cover;
extern UnkCrowdCover *D_8010D8EC_crowd_cover;
extern void *D_8010D8F0_crowd_cover[3];
extern UnkCrowdCover D_8010D918_crowd_cover; // List head of opaque entries
extern UnkCrowdCover D_8010D980_crowd_cover; // List head of translucent entries
extern void *D_8010D8FC_crowd_cover;
extern s32 D_8010D900_crowd_cover;
extern s32 D_8010D904_crowd_cover;
extern s32 D_8010CA9C_crowd_cover;

extern HuSprite_Unk84_Struct *D_800C9530_main[];

extern u32 D_8010C800_crowd_cover;

extern UnkCrowdCoverVec D_8010CC70_crowd_cover;

extern u8 D_800CE20A_main;
extern s16 D_8010C6C4_crowd_cover[3][2];
extern s16 D_8010CF88_crowd_cover[];
extern s16 D_8010CFA8_crowd_cover[];
extern s16 D_8010CFB8_crowd_cover[16];
extern s16 D_8010CFD8_crowd_cover;
extern s16 D_8010D860_crowd_cover;
extern s16 D_8010D862_crowd_cover;

void func_80105B58_crowd_cover(omObjData *object);
void func_80105CD4_crowd_cover(HuMtx4F src, HuMtx4F dst);
void func_801060C4_crowd_cover(void);
void func_80106144_crowd_cover(omObjData *object);
void func_80106580_crowd_cover(omObjData *object);
void func_80106CB8_crowd_cover(void);
void func_80106D4C_crowd_cover(omObjData *object);
void func_80107E0C_crowd_cover(void);
void func_80107E40_crowd_cover(omObjData *);
s32 func_80108F1C_crowd_cover(void);
s16 func_801091FC_crowd_cover(s32 dataNum);
s16 func_80109244_crowd_cover(s16 spriteId, s16 count);
void func_80109044_crowd_cover(Vec *dir, f32 *rot);
void func_80109354_crowd_cover(u16 count);
void func_8010980C_crowd_cover(UnkCrowdCover *crowd);
void func_8010B228_crowd_cover(s16 index);
void func_8010B754_crowd_cover(void);
void func_8010B8A8_crowd_cover(HuCamera *camera, HuMtx4F lookAt);
Gfx *func_8010BD74_crowd_cover(Gfx *gfx, UnkCrowdCover *crowd, HuMtx4F lookAt, Vec *rot);
void func_8010C45C_crowd_cover(void);

void func_801059A0_crowd_cover(void) {
    omObjData *obj;
    u8 camIndex;
    s32 count;

    func_8001FE20_main(1);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    omInitObjMan(0x10, 0);
    func_8004A208_main();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 45.0f, 80.0f, 8000.0f);
    func_800E1804_minigame();
    func_80105B58_crowd_cover(obj);
    func_801060C4_crowd_cover();
    func_80109354_crowd_cover(0x80);
    func_80106CB8_crowd_cover();
    func_80107E0C_crowd_cover();
    count = (f32)func_80108F1C_crowd_cover() * 1.52587890625e-05 * 16.0;
    while (--count != 0) {
        func_80108F1C_crowd_cover();
    }
    Hu3DBGColorSet(180, 180, 180);
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
}

void func_80105B58_crowd_cover(omObjData *object) {
    HuCamera *camera;
    f32 sinFov;
    f32 cosFov;

    CZoom = 400.0f;
    CRot.x = -45.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 200.0f;
    Center.z = 0.0f;
    omOutView(object);

    camera = gCameraList;
    sinFov = sindf(camera->fov / 2.0);
    cosFov = cosdf(camera->fov / 2.0);
    D_8010D8E8_crowd_cover = sinFov / cosFov;
    guMtxL2F(D_8010D868_crowd_cover, &camera->mtxs[0].lookAtMtx);
    guMtxL2F(D_8010D8A8_crowd_cover, &camera->mtxs[0].lookAtMtx);
    func_80105CD4_crowd_cover(D_8010D8A8_crowd_cover, D_8010D8A8_crowd_cover);
}

void func_80105C54_crowd_cover(HuMtx4F mtx, f32 x, f32 y, f32 z, f32 *dst) {
    dst[0] = ((x * mtx[0][0]) + (y * mtx[1][0])) + (z * mtx[2][0]);
    dst[1] = ((x * mtx[0][1]) + (y * mtx[1][1])) + (z * mtx[2][1]);
    dst[2] = ((x * mtx[0][2]) + (y * mtx[1][2])) + (z * mtx[2][2]);
}

void func_80105CD4_crowd_cover(HuMtx4F src, HuMtx4F dst) {
    f32 mtx[4][4];
    f32 t0;
    f32 t1;
    f32 t2;
    f32 det;
    f32 *dstRow3;

    func_8002367C_main(mtx, src);

    t0 = mtx[1][1] * mtx[2][2] - mtx[1][2] * mtx[2][1];
    t1 = mtx[1][2] * mtx[2][0] - mtx[1][0] * mtx[2][2];

    t2 = mtx[1][0] * mtx[2][1] - mtx[1][1] * mtx[2][0];

    det = t0 * mtx[0][0] + t1 * mtx[0][1] + t2 * mtx[0][2];

    dstRow3 = &dst[3][0];
    if (det != 0.0f) {
        det = 1.0f / det;

        dst[0][0] = t0 * det;
        dst[1][0] = t1 * det;
        dst[2][0] = t2 * det;

        dst[0][1] = (mtx[0][2] * mtx[2][1] - mtx[0][1] * mtx[2][2]) * det;
        dst[0][2] = (mtx[0][1] * mtx[1][2] - mtx[0][2] * mtx[1][1]) * det;
        dst[1][1] = (mtx[0][0] * mtx[2][2] - mtx[0][2] * mtx[2][0]) * det;

        dst[1][2] = (mtx[0][2] * mtx[1][0] - mtx[0][0] * mtx[1][2]) * det;
        dst[2][1] = (mtx[0][1] * mtx[2][0] - mtx[0][0] * mtx[2][1]) * det;
        dst[2][2] = (mtx[0][0] * mtx[1][1] - mtx[0][1] * mtx[1][0]) * det;

        dst[2][3] = 0.0f;
        dst[1][3] = 0.0f;
        dst[0][3] = 0.0f;
        dst[3][3] = 1.0f;

        func_80105C54_crowd_cover(dst, -mtx[3][0], -mtx[3][1], -mtx[3][2], dstRow3);
    }
}

void func_80105EC4_crowd_cover(f32 *pos, f32 *dst) {
    f32 mtx[4][4];
    f32 depth;
    f32 scale;

    guTranslateF(mtx, pos[0], pos[1], pos[2]);
    guMtxCatF(mtx, D_8010D868_crowd_cover, mtx);
    depth = mtx[3][2] * D_8010D8E8_crowd_cover;
    scale = fabsf(depth);
    if (scale != 0.0) {
        dst[0] = mtx[3][0] * 160.0f / scale / 1.3333333333333333;
        dst[1] = -mtx[3][1] * 120.0f / scale;
    }
    dst[0] += 160.0;
    dst[1] += 120.0;
    dst[2] = scale;
}

void func_80105FD0_crowd_cover(f32 x, f32 y, f32 z, f32 *dst) {
    f32 depth = z + D_8010D8A0_crowd_cover;
    f32 scale = fabsf(depth * D_8010D8E8_crowd_cover);
    f32 mtx[4][4];

    x -= 160.0;
    y -= 120.0;
    guTranslateF(mtx, (x + x) * scale * 1.3333333333333333 / 320.0, -((y + y) * scale / 240.0f), depth);
    guMtxCatF(mtx, D_8010D8A8_crowd_cover, mtx);
    dst[0] = mtx[3][0];
    dst[1] = mtx[3][1];
    dst[2] = mtx[3][2];
}

void func_801060C4_crowd_cover(void) {
    D_800EBE28_minigame = 0;
    func_800E1490_minigame(0);
    D_8010D860_crowd_cover = D_800CE20A_main;
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(5, 1, 0, -1, func_80106144_crowd_cover);
    D_8010CFD8_crowd_cover = 0;
}

void func_80106144_crowd_cover(omObjData *object) {
    u16 sp10[3] = { 4, 5, 6 };
    u16 sp18[3] = { 7, 8, 9 };
    s16 orders[6][3] = { { 0, 1, 2 }, { 0, 2, 1 }, { 1, 0, 2 }, { 1, 2, 0 }, { 2, 1, 0 }, { 2, 0, 1 } };
    s16 unused[16]; // Unreferenced, but present in the stack frame.
    s16 order;
    s32 i;

    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_8010CF88_crowd_cover[0] = func_801091FC_crowd_cover(0x590000);
    D_8010CFA8_crowd_cover[0] = func_80109244_crowd_cover(D_8010CF88_crowd_cover[0], 1);
    HuSprPosSet(D_8010CFA8_crowd_cover[0], 0, 160, 120);
    HuSprAttrSet(D_8010CFA8_crowd_cover[0], 0, 0x4000);
    D_8010CF88_crowd_cover[3] = func_801091FC_crowd_cover(0x59000A);
    D_8010CFA8_crowd_cover[4] = func_80109244_crowd_cover(D_8010CF88_crowd_cover[3], 1);
    HuSprPosSet(D_8010CFA8_crowd_cover[4], 0, 160, 198);
    HuSprAttrSet(D_8010CFA8_crowd_cover[4], 0, 0x100C);
    D_8010CF88_crowd_cover[2] = func_801091FC_crowd_cover(sp18[D_8010D860_crowd_cover] | 0x590000);
    D_8010CFA8_crowd_cover[2] = func_80109244_crowd_cover(D_8010CF88_crowd_cover[2], 3);
    order = (f32)func_80108F1C_crowd_cover() * 1.52587890625e-05 * 6.0;
    for (i = 0; i < 3; i++) {
        HuSprPosSet(D_8010CFA8_crowd_cover[2], i, D_8010C6C4_crowd_cover[i][0], D_8010C6C4_crowd_cover[i][1]);
        HuSprAttrSet(D_8010CFA8_crowd_cover[2], i, 0x1008);
        func_80054FF8_main(D_8010CFA8_crowd_cover[2], i, orders[order][i]);
    }
    D_8010CF88_crowd_cover[1] = func_801091FC_crowd_cover(sp10[D_8010D860_crowd_cover] | 0x590000);
    D_8010CFA8_crowd_cover[1] = func_80109244_crowd_cover(D_8010CF88_crowd_cover[1], 1);
    HuSprPosSet(D_8010CFA8_crowd_cover[1], 0, 160, 110);
    D_8010D862_crowd_cover = (f32)func_80108F1C_crowd_cover() * 1.52587890625e-05 * 3.0;
    func_80054FF8_main(D_8010CFA8_crowd_cover[1], 0, orders[order][D_8010D862_crowd_cover]);
    HuSprAttrSet(D_8010CFA8_crowd_cover[1], 0, 0x405808);
    D_8010CF88_crowd_cover[4] = func_801091FC_crowd_cover(0x59000B);
    D_8010CFA8_crowd_cover[5] = func_80109244_crowd_cover(D_8010CF88_crowd_cover[4], 1);
    HuSprPosSet(D_8010CFA8_crowd_cover[5], 0, 160, 110);
    HuSprScaleSet(D_8010CFA8_crowd_cover[5], 0, 1.2f, 1.2f);
    HuSprAttrSet(D_8010CFA8_crowd_cover[5], 0, 0x940C);
    object->func = func_80106580_crowd_cover;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CB48_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80106580_crowd_cover);

void func_80106CB8_crowd_cover(void) {
    s32 i;

    func_800E18D8_minigame();
    D_800EC280_minigame = 0;
    for (i = 0; i < 2; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 0xB, 0x32, -1, func_80106D4C_crowd_cover);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CB70_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CB78_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CBD8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CBE0_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80106D4C_crowd_cover);

void func_80107298_crowd_cover(omObjData *object, s32 arg1, s32 arg2, u16 player, u16 tag) {
    func_800E1BA8_minigame_ObjData *data;
    s32 i;
    u32 character;
    f32 zero;
    func_800E1BA8_minigame_UnkE8_ObjData *entry;

    for (i = 0; i < object->mdlcnt; i++) {
        object->model[i] = 0;
    }
    object->data = HuMemAllocTag(sizeof(func_800E1BA8_minigame_ObjData), TAG_OVERLAY);
    memset(object->data, 0, sizeof(func_800E1BA8_minigame_ObjData));
    data = object->data;
    data->unkE8 = HuMemAllocTag(object->mtncnt * 3 * sizeof(s32), TAG_OVERLAY);
    memset(data->unkE8, 0, object->mtncnt * 3 * sizeof(s32));
    data->unk158 = HuMemAllocTag(sizeof(UnkCrowdCoverWork), TAG_OVERLAY);
    memset(data->unk158, 0, sizeof(UnkCrowdCoverWork));

    object->model[0] = func_8000B108_main(arg1 | arg2, tag);
    object->model[1] = func_8000B0D4_main(9, tag);
    func_800E3584_minigame(object->model[1]);
    for (i = 0; i < object->mtncnt; i++) {
        object->motion[i] = -1;
    }
    for (i = 0; i < object->mtncnt; i++) {
        entry = data->unkE8;
        entry[i].unk02 = 0;
        entry[i].unk00 = 0;
    }

    data->unk57 = GwPlayer[player].pad;
    data->unk52 = 0;
    data->unkB4 = 1.0f;
    data->unkD0 = -1;
    data->unk4C = 0.5f;
    data->unkCC = 1.0f;
    zero = 0.0f;
    data->unkA4 = zero;
    data->unk9C = zero;
    data->unkA0 = zero;
    data->unk59 = player;

    data->unk3C = atan2df(-object->trans.x, -object->trans.z);
    func_800E1328_minigame(object, 60.0f);
    func_800E1334_minigame(object, 150.0f);
    func_800E1340_minigame(object, 20.0f);
    func_800E12EC_minigame(object, 1000.0f);

    character = (u32)arg1 >> 16;
    switch (character) {
        case 6:
            data->unkAC = 0.8f;
            break;
        case 5:
            data->unkAC = 0.9f;
            break;
        case 0:
        default:
            data->unkAC = 1.0f;
            break;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CBF8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CC00_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CC08_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80107554_crowd_cover);

u16 func_80107C5C_crowd_cover(omObjData *arg0) {
    UnkCrowdCoverVec vec = D_8010CC70_crowd_cover;
    UnkCrowdCoverWork *work;
    s16 remaining;
    u16 result = 0;

    work = OM_GET_DATA_PTR(arg0, func_800E1BA8_minigame_ObjData)->unk158;
    remaining = --work->unk34;
    if (remaining == 0) {
        result = work->unk36;
    }
    return result;
}

s16 func_80107CE0_crowd_cover(s16 spriteId, s16 x, s16 y, f32 rot) {
    s16 group; // Never assigned; the original passes an uninitialized value.
    s32 i;

    if (spriteId == -1) {
        return -1;
    }
    for (i = 0; i < 16; i++) {
        if (D_8010CFB8_crowd_cover[i] == 0) {
            break;
        }
    }
    if (i >= 16) {
        return -1;
    }
    D_8010CFB8_crowd_cover[i] = 1;
    HuSprGrpMemberSet(group, i, spriteId, 0);
    func_800550F4_main(group, i, 2);
    HuSprPosSet(group, i, x, y);
    HuSprZRotSet(group, i, rot);
    HuSprAttrReset(group, i, 0x8000);
    return i;
}

void func_80107E0C_crowd_cover(void) {
    omAddObj(3, 0xB, 0x32, -1, func_80107E40_crowd_cover);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CC70_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CC84_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CDEC_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80107E40_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80108238_crowd_cover);

s32 func_80108F1C_crowd_cover(void) {
    D_8010C800_crowd_cover = D_8010C800_crowd_cover * 0x41C64E6D + 0x3039;
    D_8010C800_crowd_cover += rand8();
    return D_8010C800_crowd_cover >> 16;
}

f32 func_80108F74_crowd_cover(f32 y, f32 x) {
    f32 fullCircle = 360.0f;
    f32 angle = atan2df(y, x);

    if (angle < 0.0f) {
        angle += fullCircle;
    } else if (angle >= fullCircle) {
        angle -= fullCircle;
    }
    return angle;
}

f32 func_80108FDC_crowd_cover(Vec *arg0, Vec *arg1) {
    return sqrtf(((arg0->x - arg1->x) * (arg0->x - arg1->x)) +
                 ((arg0->y - arg1->y) * (arg0->y - arg1->y)) +
                 ((arg0->z - arg1->z) * (arg0->z - arg1->z)));
}

void func_80109044_crowd_cover(Vec *dir, f32 *rot) {
    *rot++ = func_80108F74_crowd_cover(sqrtf(dir->x * dir->x + dir->z * dir->z), -dir->y);
    *rot++ = func_80108F74_crowd_cover(dir->z, dir->x);
    *rot = 0.0f;
}

void func_801090CC_crowd_cover(s16 model, char *hook, s16 time, Vec *pos) {
    HuMtx4F transform;
    HuMtx4F result;
    HuMtx4F hookTransform;
    HmfModel *modelData;

    func_80016B00_main(model, time, hook, &hookTransform);
    modelData = &Hu3DData[model];
    func_8002367C_main(transform, modelData->mtx);
    mtxTransCat(transform, modelData->pos.x, modelData->pos.y, modelData->pos.z);
    mtxRotCat(transform, modelData->rot.x, modelData->rot.y, modelData->rot.z);
    mtxScaleCat(transform, modelData->scale.x, modelData->scale.y, modelData->scale.z);
    func_80018044_main(hookTransform, transform, result);
    pos->x = result[0][0] + result[1][0] + result[2][0] + result[3][0];
    pos->y = result[0][1] + result[1][1] + result[2][1] + result[3][1];
    pos->z = result[0][2] + result[1][2] + result[2][2] + result[3][2];
}

s16 func_801091FC_crowd_cover(s32 dataNum) {
    void *data;
    s16 spriteId;

    data = DataRead(dataNum);
    spriteId = HuSprAnimRead(data);
    DataClose(data);
    return spriteId;
}

s16 func_80109244_crowd_cover(s16 spriteId, s16 count) {
    s16 groupId;
    s32 i;

    if (spriteId == -1) {
        return -1;
    }
    groupId = HuSprGrpCreate(count, 0);
    if (groupId == -1) {
        return -1;
    }
    for (i = 0; i < count; i++) {
        HuSprGrpMemberSet(groupId, i, spriteId, 0);
    }
    return groupId;
}

HuSprite_Unk84_Unk00_Struct *func_8010930C_crowd_cover(s16 groupId, s16 member) {
    return &func_80055194_main(groupId)->unk00[member];
}

void func_80109354_crowd_cover(u16 count) {
    UnkCrowdCover *crowd;
    s16 i;

    D_8010D904_crowd_cover = count;
    D_8010D8EC_crowd_cover = HuMemAlloc(count * sizeof(UnkCrowdCover));
    for (i = 0; i < 3; i++) {
        D_8010D8F0_crowd_cover[i] = NULL;
    }
    for (i = 0; i < D_8010D904_crowd_cover; i++) {
        crowd = &D_8010D8EC_crowd_cover[i];
        crowd->sprite = NULL;
        crowd->callback = NULL;
        crowd->unk_28 = 0;
        crowd->unk_20 = 0x100;
        crowd->unk_1F = 0xFF;
        crowd->unk_1E = 0xFF;
        crowd->unk_1D = 0xFF;
        crowd->unk_2C = 0;
        crowd->unk_24 = 0;
        crowd->unk_30.x = 1.0f;
        crowd->unk_1C = 0;
        crowd->unk_1B = 0;
        crowd->unk_30.y = crowd->unk_30.z = crowd->unk_3C = 0.0f;
        crowd->unk_40.x = crowd->unk_40.y = crowd->unk_40.z = 0.0f;
        crowd->unk_4C.x = crowd->unk_4C.y = crowd->unk_4C.z = 1.0f;
        crowd->unk_58.x = crowd->unk_58.y = crowd->unk_58.z = 0.0f;
    }
}

void func_8010949C_crowd_cover(Gfx **gfx, HuSprite_Unk84_Unk00_Struct *cel, u8 fmt, u8 siz, u16 height, u16 uls,
                               u16 ult, u16 lrs, u16 lrt, u16 cms, u16 cmt, u16 masks, u16 maskt, s32 mode) {
    Gfx *gdl = *gfx;

    switch (mode) {
        case 0:
            gDPLoadTextureTile_4b(gdl++, (void *)0x0C000000, fmt, cel->unk04, height, uls, ult, lrs, lrt, 0, cms,
                                  cmt, masks, maskt, 0, 0);
            break;
        case 1:
            func_80034998_main(&gdl, (void *)0x0C000000, fmt, cel->unk04, height, uls, ult, lrs, lrt, 0, cms, cmt,
                               masks, maskt, 0, 0);
            break;
        case 2:
            func_800341D0_main(&gdl, (u16 *)0x0C000000, fmt, siz, cel->unk04, cel->unk06, uls, ult, lrs, lrt, 0,
                               cms, cmt, masks, maskt, 0, 0);
            break;
        case 3:
            func_8003465C_main(&gdl, (void *)0x0C000000, fmt, siz, cel->unk04, height, uls, ult, lrs, lrt, 0, cms,
                               cmt, masks, maskt, 0, 0);
            break;
    }
    *gfx = gdl;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010980C_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE38_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE3C_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", jtbl_8010CE40_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE60_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE68_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE70_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE78_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE80_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE88_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE90_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE98_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEA0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEA8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEB0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEB8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEC0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEC8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CED0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CED8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEE0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEE8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEF0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEF8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF00_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF08_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF10_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF18_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF20_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF28_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF30_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF38_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF40_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF48_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010A12C_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010A734_crowd_cover);

void func_8010ACBC_crowd_cover(s16 index, s16 spriteId) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->sprite = D_800C9530_main[spriteId];
        crowd->unk_20 = 0x100;
        crowd->unk_1F = 0xFF;
        crowd->unk_1E = 0xFF;
        crowd->unk_1D = 0xFF;
        crowd->unk_2C = 0;
        crowd->unk_24 = 0;
        crowd->unk_30.x = 1.0f;
    }
}

void func_8010AD3C_crowd_cover(s16 index, s16 value) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_24 = value;
        crowd->unk_2C = 0;
    }
}

void func_8010AD7C_crowd_cover(s16 index, f32 value) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_30.x = value;
    }
}

void func_8010ADBC_crowd_cover(s16 index, f32 y, f32 z, f32 unk_3C) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_28 |= 0x4000000;
        crowd->unk_30.y = y;
        crowd->unk_30.z = z;
        crowd->unk_3C = unk_3C;
    }
}

void func_8010AE1C_crowd_cover(s16 index, f32 value) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_3C = value;
    }
}

void func_8010AE5C_crowd_cover(s16 index, f32 x, f32 y, f32 z) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_40.x = x;
        crowd->unk_40.y = y;
        crowd->unk_40.z = z;
    }
}

void func_8010AEAC_crowd_cover(s16 index, f32 x, f32 y, f32 z) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_40.x += x;
        crowd->unk_40.y += y;
        crowd->unk_40.z += z;
    }
}

void func_8010AF14_crowd_cover(s16 index, f32 x, f32 y, f32 z) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_4C.x = x;
        crowd->unk_4C.y = y;
        crowd->unk_4C.z = z;
    }
}

void func_8010AF64_crowd_cover(s16 index, f32 x, f32 y, f32 z) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_58.x = x;
        crowd->unk_58.y = y;
        crowd->unk_58.z = z;
    }
}

void func_8010AFB4_crowd_cover(s16 index, s32 value) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_28 |= value;
    }
}

void func_8010AFF8_crowd_cover(s16 index, s32 value) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_28 &= ~value;
    }
}

s32 func_8010B040_crowd_cover(s16 index) {
    UnkCrowdCover *crowd;
    s32 i = index;

    if (i != -1) {
        crowd = &D_8010D8EC_crowd_cover[i];
        return crowd->unk_28;
    }
    return -1;
}

void func_8010B080_crowd_cover(s16 index, s8 value) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_1A = value;
    }
}

UnkCrowdCover *func_8010B0BC_crowd_cover(s16 index) {
    UnkCrowdCover *crowd;
    s32 i = index;

    if (i == -1) {
        return NULL;
    }
    crowd = &D_8010D8EC_crowd_cover[i];
    return crowd;
}

Vtx_t *func_8010B0FC_crowd_cover(s16 index) {
    UnkCrowdCover *crowd;
    s32 i = index;

    if (i == -1) {
        return NULL;
    }
    crowd = &D_8010D8EC_crowd_cover[i];
    return crowd->vtx;
}

#ifdef NON_MATCHING
// Index sign extension is computed in a different register than the original.
s32 func_8010B140_crowd_cover(s16 index, s16 x, s16 y) {
    UnkCrowdCover *crowd;
    Vtx_t *vtx;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        if (crowd->unk_18 == 3) {
            crowd->unk_28 |= 0x80000000;
            vtx = &crowd->vtx[4];
            vtx->ob[0] = x;
            vtx->ob[1] = -y;
            vtx->ob[2] = 0;
            vtx->tc[0] = x * 64;
            vtx->tc[1] = y * 64;
            return 1;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B140_crowd_cover);
#endif

void func_8010B1DC_crowd_cover(s16 index, s8 value1, s8 value2, s8 value3, s16 value4) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_1D = value1;
        crowd->unk_1E = value2;
        crowd->unk_1F = value3;
        crowd->unk_20 = value4;
    }
}

void func_8010B228_crowd_cover(s16 index) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        if (crowd->sprite != NULL) {
            HuMemFree(crowd->displayList);
            HuMemFree(crowd->vtx);
            crowd->sprite = NULL;
            crowd->unk_28 = 0;
            crowd->unk_20 = 0x100;
            crowd->unk_1F = 0xFF;
            crowd->unk_1E = 0xFF;
            crowd->unk_1D = 0xFF;
            crowd->unk_2C = 0;
            crowd->unk_24 = 0;
            crowd->unk_1C = 0;
            crowd->unk_1B = 0;
            crowd->unk_30.y = crowd->unk_30.z = crowd->unk_3C = 0.0f;
            crowd->unk_40.x = crowd->unk_40.y = crowd->unk_40.z = 0.0f;
            crowd->unk_4C.x = crowd->unk_4C.y = crowd->unk_4C.z = 1.0f;
            crowd->unk_58.x = crowd->unk_58.y = crowd->unk_58.z = 0.0f;
            crowd->unk_30.x = 1.0f;
        }
    }
}

void func_8010B308_crowd_cover(s32 index, s32 flag) {
    UnkCrowdCover *crowd = &D_8010D8EC_crowd_cover[index];
    s32 i;

    if (flag != 0) {
        crowd->unk_28 |= 0x10000;
        for (i = 0; i < crowd->unk_18; i++) {
            crowd->vtx[i].cn[0] = 0;
            crowd->vtx[i].cn[1] = 0;
            crowd->vtx[i].cn[2] = 0x80;
        }
        return;
    }
    crowd->unk_28 &= ~0x10000;
    for (i = 0; i < crowd->unk_18; i++) {
        crowd->vtx[i].cn[0] = 0xFF;
        crowd->vtx[i].cn[1] = 0xFF;
        crowd->vtx[i].cn[2] = 0xFF;
        crowd->vtx[i].cn[3] = 0xFF;
    }
}

void func_8010B408_crowd_cover(s32 index, s32 flip) {
    UnkCrowdCover *crowd = &D_8010D8EC_crowd_cover[index];
    s32 i;

    if (flip) {
        for (i = 0; i < crowd->unk_18; i++) {
            crowd->vtx[i * 2].tc[0] = crowd->sprite->unk00->unk04 << 6;
            crowd->vtx[i * 2 + 1].tc[0] = 0;
        }
    } else {
        for (i = 0; i < crowd->unk_18; i++) {
            crowd->vtx[i * 2].tc[0] = 0;
            crowd->vtx[i * 2 + 1].tc[0] = crowd->sprite->unk00->unk04 << 6;
        }
    }
}

void func_8010B4D8_crowd_cover(s32 index, s32 flip) {
    UnkCrowdCover *crowd = &D_8010D8EC_crowd_cover[index];
    s32 remainder = crowd->sprite->unk00->unk06 - (crowd->unk_18 - 2) * crowd->unk_19;
    s32 i;

    if (flip) {
        for (i = 0; i < crowd->unk_18 - 1; i++) {
            crowd->vtx[i * 2].tc[1] = crowd->vtx[i * 2 + 1].tc[1] =
                crowd->sprite->unk00->unk06 - i * crowd->unk_19;
        }
        if (remainder != 0) {
            crowd->vtx[i * 2].tc[1] = crowd->vtx[i * 2 + 1].tc[1] = 0;
        }
    } else {
        for (i = 0; i < crowd->unk_18 - 1; i++) {
            crowd->vtx[i * 2].ob[1] = crowd->vtx[i * 2 + 1].ob[1] = i * crowd->unk_19;
        }
        if (remainder != 0) {
            crowd->vtx[i * 2].ob[1] = crowd->vtx[i * 2 + 1].ob[1] = crowd->sprite->unk00->unk06;
        }
    }
}

void func_8010B610_crowd_cover(s16 index, void (*callback)(struct UnkCrowdCover *)) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->callback = callback;
    }
}

void func_8010B64C_crowd_cover(s16 index, s8 arg1, s8 arg2, s32 flags) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_1B = arg1;
        crowd->unk_1C = arg2;
        crowd->unk_28 |= flags;
        HuMemFree(crowd->displayList);
        func_8010980C_crowd_cover(crowd);
    }
}

void func_8010B6BC_crowd_cover(s16 index, s32 flag) {
    UnkCrowdCover *crowd;
    s8 color;
    s8 blue;
    s32 i;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        if (flag) {
            color = 0;
            blue = 0x70;
        } else {
            color = 0xFF;
            blue = 0xFF;
        }
        for (i = 0; i < crowd->unk_18; i++) {
            crowd->vtx[i].cn[0] = crowd->vtx[i].cn[1] = crowd->vtx[i].cn[3] = color;
            crowd->vtx[i].cn[2] = blue;
        }
    }
}

void func_8010B754_crowd_cover(void) {
    UnkCrowdCover *crowd;
    s32 i;

    if (++D_8010CA9C_crowd_cover >= 3) {
        D_8010CA9C_crowd_cover = 0;
    }
    D_8010D900_crowd_cover = 0;
    for (i = 0; i < D_8010D904_crowd_cover; i++) {
        crowd = &D_8010D8EC_crowd_cover[i];
        if (crowd->sprite != NULL) {
            D_8010D900_crowd_cover += 0x40 + (crowd->unk_22 * sizeof(Gfx) + crowd->unk_18 * 2 * sizeof(Vtx));
        }
    }
    if (D_8010D8F0_crowd_cover[D_8010CA9C_crowd_cover] != NULL) {
        HuMemFree(D_8010D8F0_crowd_cover[D_8010CA9C_crowd_cover]);
    }
    if (D_8010D900_crowd_cover != 0) {
        D_8010D8F0_crowd_cover[D_8010CA9C_crowd_cover] = HuMemAlloc(D_8010D900_crowd_cover);
    } else {
        D_8010D8F0_crowd_cover[D_8010CA9C_crowd_cover] = NULL;
    }
    D_8010D8FC_crowd_cover = D_8010D8F0_crowd_cover[D_8010CA9C_crowd_cover];
}

void func_8010B8A8_crowd_cover(HuCamera *camera, HuMtx4F lookAt) {
    UnkCrowdCover tailOpaque;
    UnkCrowdCover tailTranslucent;
    HuMtx4F unused[16]; // Unreferenced, but present in the stack frame.
    HuMtx4F mtx;
    UnkCrowdCover *crowd;
    UnkCrowdCover *node;
    f32 minX;
    f32 maxX;
    f32 minZ;
    f32 maxZ;
    s32 i;

    minX = camera->at.x - 640.0;
    maxX = camera->at.x + 640.0;
    minZ = camera->at.z - 640.0;
    maxZ = camera->at.z + 640.0;
    D_8010D918_crowd_cover.unk_64 = 0.0f;
    D_8010D980_crowd_cover.unk_64 = 99999.9f;
    tailOpaque.unk_64 = -99999.9f;
    tailTranslucent.unk_64 = 0.0f;
    D_8010D980_crowd_cover.prev = NULL;
    D_8010D918_crowd_cover.prev = NULL;
    D_8010D918_crowd_cover.next = &tailOpaque;
    D_8010D980_crowd_cover.next = &tailTranslucent;
    tailOpaque.prev = &D_8010D918_crowd_cover;
    tailTranslucent.prev = &D_8010D980_crowd_cover;
    tailTranslucent.next = NULL;
    tailOpaque.next = NULL;
    for (i = 0; i < D_8010D904_crowd_cover; i++) {
        crowd = &D_8010D8EC_crowd_cover[i];
        if (crowd->sprite == NULL) {
            continue;
        }
        if (crowd->unk_40.x < minX || maxX < crowd->unk_40.x) {
            continue;
        }
        if (crowd->unk_40.z < minZ || maxZ < crowd->unk_40.z) {
            continue;
        }
        guTranslateF(mtx, crowd->unk_40.x, crowd->unk_40.y, crowd->unk_40.z);
        guMtxCatF(mtx, lookAt, mtx);
        crowd->unk_64 = mtx[3][2];
        if (crowd->unk_64 > 0.0) {
            continue;
        }
        if ((crowd->unk_28 & 0x1000) && crowd->unk_20 < 0x100) {
            crowd->unk_64 *= -1.0;
            node = &D_8010D980_crowd_cover;
        } else {
            node = &D_8010D918_crowd_cover;
        }
        for (node = node->next; node->unk_64 > crowd->unk_64; node = node->next) {}
        node->prev->next = crowd;
        crowd->prev = node->prev;
        crowd->next = node;
        node->prev = crowd;
    }
    tailOpaque.prev->next = tailTranslucent.prev->next = NULL;
}

void func_8010BB4C_crowd_cover(Gfx **gfxP, s32 arg1, s32 arg2) {
    HuCamera *camera = (HuCamera *)arg2;
    Gfx *gfx = *gfxP;
    HuMtx4F unused1[2]; // Unreferenced, but present in the stack frame.
    HuMtx4F lookAt;
    HuMtx4F unused2[4]; // Unreferenced, but present in the stack frame.
    Vec rot;
    Vec dir;
    HuMtx4F unused3[32]; // Unreferenced, but present in the stack frame.
    UnkCrowdCover *crowd;

    guLookAtF(lookAt, camera->pos.x, camera->pos.y, camera->pos.z, camera->at.x, camera->at.y, camera->at.z,
              camera->up.x, camera->up.y, camera->up.z);
    dir.x = camera->pos.x - camera->at.x;
    dir.y = camera->pos.y - camera->at.y;
    dir.z = camera->pos.z - camera->at.z;
    func_80109044_crowd_cover(&dir, (f32 *)&rot);
    func_8010B754_crowd_cover();
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_2CYCLE);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING | G_TEXTURE_GEN);
    gSPSetGeometryMode(gfx++, G_SHADE | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    func_8010B8A8_crowd_cover(camera, lookAt);
    for (crowd = D_8010D918_crowd_cover.next; crowd != NULL; crowd = crowd->next) {
        gfx = func_8010BD74_crowd_cover(gfx, crowd, lookAt, &rot);
    }
    for (crowd = D_8010D980_crowd_cover.next; crowd != NULL; crowd = crowd->next) {
        gfx = func_8010BD74_crowd_cover(gfx, crowd, lookAt, &rot);
    }
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    *gfxP = gfx;
    if (!Hu3DPauseF) {
        func_8010C45C_crowd_cover();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010BD74_crowd_cover);

void func_8010C45C_crowd_cover(void) {
    UnkCrowdCover *crowd;
    s32 frameCount;
    s32 i;

    for (i = 0; i < D_8010D904_crowd_cover; i++) {
        crowd = &D_8010D8EC_crowd_cover[i];
        if (crowd->callback != NULL) {
            crowd->callback(crowd);
        }
        if (crowd->sprite == NULL) {
            continue;
        }
        if (crowd->unk_28 & 0x8000) {
            continue;
        }
        if (crowd->unk_28 & 0x10000000) {
            continue;
        }
        frameCount = crowd->sprite->unk10;
        crowd->unk_2C += crowd->unk_30.x;
        while (crowd->unk_2C >= 1.0) {
            crowd->unk_24++;
            crowd->unk_2C -= 1.0f;
            if (crowd->unk_24 >= frameCount) {
                if (crowd->unk_28 & 0x20000000) {
                    crowd->unk_28 |= 0x8000;
                    crowd->unk_24--;
                    crowd->unk_2C += 1.0f;
                    if (crowd->unk_28 & 0x40000000) {
                        func_8010B228_crowd_cover(i);
                    }
                    break;
                }
                if (crowd->unk_28 & 0x40000000) {
                    crowd->unk_24--;
                    break;
                }
                crowd->unk_24 = 0;
            }
        }
    }
}

void func_8010C61C_crowd_cover(void) {
    s32 i;

    for (i = 0; i < D_8010D904_crowd_cover; i++) {
        func_8010B228_crowd_cover(i);
    }
    for (i = 0; i < 3; i++) {
        if (D_8010D8F0_crowd_cover[i] != NULL) {
            HuMemFree(D_8010D8F0_crowd_cover[i]);
        }
    }
    HuMemFree(D_8010D8EC_crowd_cover);
}
