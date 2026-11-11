#include "common.h"
#include "overlays/minigame.h"

typedef struct {
    /* 0x00 */ char unk_00[0xC];
    /* 0x0C */ u8 unk_0C;
    /* 0x0D */ u8 unk_0D;
    /* 0x0E */ u8 unk_0E;
    /* 0x0F */ u8 unk_0F;
} CrowdCoverEntry; // Size 0x10

typedef struct UnkCrowdCover {
    /* 0x00 */ Gfx *displayList;
    /* 0x04 */ CrowdCoverEntry *entries;
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
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ char pad_26[2];
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
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

extern HuSprite_Unk84_Struct *D_800C9530_main[];

extern u32 D_8010C800_crowd_cover;

extern UnkCrowdCoverVec D_8010CC70_crowd_cover;

extern u8 D_800CE20A_main;
extern s16 D_8010C6C4_crowd_cover[3][2];
extern s16 D_8010CF88_crowd_cover[];
extern s16 D_8010CFA8_crowd_cover[];
extern s16 D_8010CFD8_crowd_cover;
extern s16 D_8010D860_crowd_cover;
extern s16 D_8010D862_crowd_cover;

void func_80105B58_crowd_cover(omObjData *object);
void func_80105CD4_crowd_cover(HuMtx4F src, HuMtx4F dst);
void func_801060C4_crowd_cover(void);
void func_80106144_crowd_cover(omObjData *object);
void func_80106580_crowd_cover(omObjData *object);
void func_80106CB8_crowd_cover(void);
void func_80107E0C_crowd_cover(void);
void func_80107E40_crowd_cover(omObjData *);
s32 func_80108F1C_crowd_cover(void);
s16 func_801091FC_crowd_cover(s32 dataNum);
s16 func_80109244_crowd_cover(s16 spriteId, s16 count);
void func_80109354_crowd_cover(s32 arg0);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80106CB8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CB70_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CB78_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CBD8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CBE0_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80106D4C_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80107298_crowd_cover);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80107CE0_crowd_cover);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80108F74_crowd_cover);

f32 func_80108FDC_crowd_cover(Vec *arg0, Vec *arg1) {
    return sqrtf(((arg0->x - arg1->x) * (arg0->x - arg1->x)) +
                 ((arg0->y - arg1->y) * (arg0->y - arg1->y)) +
                 ((arg0->z - arg1->z) * (arg0->z - arg1->z)));
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80109044_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_801090CC_crowd_cover);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80109354_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010949C_crowd_cover);

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

CrowdCoverEntry *func_8010B0FC_crowd_cover(s16 index) {
    UnkCrowdCover *crowd;
    s32 i = index;

    if (i == -1) {
        return NULL;
    }
    crowd = &D_8010D8EC_crowd_cover[i];
    return crowd->entries;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B140_crowd_cover);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B228_crowd_cover);

void func_8010B308_crowd_cover(s32 index, s32 flag) {
    UnkCrowdCover *crowd = &D_8010D8EC_crowd_cover[index];
    s32 i;

    if (flag != 0) {
        crowd->unk_28 |= 0x10000;
        for (i = 0; i < crowd->unk_18; i++) {
            crowd->entries[i].unk_0C = 0;
            crowd->entries[i].unk_0D = 0;
            crowd->entries[i].unk_0E = 0x80;
        }
        return;
    }
    crowd->unk_28 &= ~0x10000;
    for (i = 0; i < crowd->unk_18; i++) {
        crowd->entries[i].unk_0C = 0xFF;
        crowd->entries[i].unk_0D = 0xFF;
        crowd->entries[i].unk_0E = 0xFF;
        crowd->entries[i].unk_0F = 0xFF;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B408_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B4D8_crowd_cover);

void func_8010B610_crowd_cover(s16 index, void (*callback)(struct UnkCrowdCover *)) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->callback = callback;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B64C_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B6BC_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B754_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B8A8_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010BB4C_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010BD74_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010C45C_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010C61C_crowd_cover);
