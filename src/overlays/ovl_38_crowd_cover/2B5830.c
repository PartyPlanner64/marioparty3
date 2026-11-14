#include "common.h"
#include "overlays/minigame.h"
#include "game/hmfmath.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"
#include "game/texload.h"

#define PLAYER_WORK(obj) ((UnkCrowdCoverWork *)((func_800E1BA8_minigame_ObjData *)(obj)->data)->unk158)

#define CROWD_CC_PRIM_DECALA 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0
#define CROWD_CC_PRIM_MODULATEA 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0
#define CROWD_CC_BLEND_DECALA 1, PRIMITIVE, TEXEL0, PRIMITIVE, 0, 0, 0, TEXEL0
#define CROWD_CC_BLEND_MODULATEA 1, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0
#define CROWD_CC_MODULATEI_PRIMA TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0
#define CROWD_CC_MODULATEI_PASSA2 COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED

typedef struct UnkCrowdCover {
    /* 0x00 */ Gfx *displayList;
    /* 0x04 */ Vtx_t *vtx;
    /* 0x08 */ HuSprite_Unk84_Struct *sprite;
    /* 0x0C */ struct UnkCrowdCover *prev;
    /* 0x10 */ struct UnkCrowdCover *next;
    /* 0x14 */ void (*callback)(struct UnkCrowdCover *);
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19;
    /* 0x1A */ u8 unk_1A;
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
    /* 0x00 */ Vec pos;
    /* 0x0C */ char unk0C[8];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
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

typedef struct {
    u8 values[8];
} CrowdCoverCharMotions;

// Crowd member state, updated by func_80108238_crowd_cover
typedef struct {
    /* 0x00 */ s16 crowdIndex;
    /* 0x02 */ s16 model;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ u8 state;
    /* 0x09 */ u8 timer;
    /* 0x0A */ char pad0A[2];
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec offset;
    /* 0x28 */ Vec vel;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
} CrowdCoverMember; // sizeof 0x44

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
extern s16 D_8010C6C0_crowd_cover;
extern s16 D_8010C6C4_crowd_cover[3][2];
extern s32 D_8010C6D0_crowd_cover;
extern s32 D_8010C6D4_crowd_cover;
extern s32 D_8010C6D8_crowd_cover;
extern u8 D_8010C6E4_crowd_cover;
extern s16 D_8010C6EC_crowd_cover[][3];
extern f32 D_8010C704_crowd_cover[];
extern s32 D_800A178C_main[][6];
extern s16 D_8010C714_crowd_cover[][13];
extern s32 D_8010C804_crowd_cover[];
extern s16 D_8010C814_crowd_cover[];
extern s16 D_8010C94C_crowd_cover[];
extern s16 D_8010CA84_crowd_cover[];
extern s16 D_8010CA8C_crowd_cover[];
extern s16 D_8010CA94_crowd_cover[];
extern s16 D_8010CF80_crowd_cover;
extern s16 D_8010CF82_crowd_cover;
extern s16 D_8010CF88_crowd_cover[];
extern s16 D_8010CFA8_crowd_cover[];
extern s16 D_8010CFB8_crowd_cover[16];
extern s16 D_8010CFD8_crowd_cover;
extern s16 D_8010D860_crowd_cover;
extern s16 D_8010D862_crowd_cover;
extern s16 D_8010D864_crowd_cover;
extern s16 D_8010D866_crowd_cover;
extern CrowdCoverMember D_8010CFE0_crowd_cover[];

void func_80105B58_crowd_cover(omObjData *object);
void func_80105CD4_crowd_cover(HuMtx4F src, HuMtx4F dst);
void func_801060C4_crowd_cover(void);
void func_80106144_crowd_cover(omObjData *object);
void func_80106580_crowd_cover(omObjData *object);
void func_80106CB8_crowd_cover(void);
void func_80106D4C_crowd_cover(omObjData *object);
void func_80107298_crowd_cover(omObjData *object, s32 arg1, s32 arg2, u16 player, u16 tag);
void func_80107554_crowd_cover(omObjData *object);
u16 func_80107C5C_crowd_cover(omObjData *arg0);
void func_80107E0C_crowd_cover(void);
void func_80107E40_crowd_cover(omObjData *);
void func_80108238_crowd_cover(omObjData *object);
s32 func_80108F1C_crowd_cover(void);
s16 func_801091FC_crowd_cover(s32 dataNum);
s16 func_80109244_crowd_cover(s16 spriteId, s16 count);
void func_80109044_crowd_cover(Vec *dir, f32 *rot);
void func_801090CC_crowd_cover(s16 model, char *hook, s16 time, Vec *pos);
void func_80109354_crowd_cover(u16 count);
s16 func_8010980C_crowd_cover(UnkCrowdCover *crowd);
s16 func_8010A12C_crowd_cover(s16 spriteId, s32 flags);
void func_8010ADBC_crowd_cover(s16 index, f32 y, f32 z, f32 unk_3C);
void func_8010AE5C_crowd_cover(s16 index, f32 x, f32 y, f32 z);
void func_8010AF14_crowd_cover(s16 index, f32 x, f32 y, f32 z);
void func_8010AD3C_crowd_cover(s16 index, s16 value);
void func_8010AFB4_crowd_cover(s16 index, s32 value);
void func_8010B1DC_crowd_cover(s16 index, s8 value1, s8 value2, s8 value3, s16 value4);
f32 func_80108F74_crowd_cover(f32 y, f32 x);
f32 func_80108FDC_crowd_cover(Vec *arg0, Vec *arg1);
void func_8010B228_crowd_cover(s16 index);
void func_8010B754_crowd_cover(void);
void func_8010B8A8_crowd_cover(HuCamera *camera, HuMtx4F lookAt);
Gfx *func_8010BD74_crowd_cover(Gfx *gfx, UnkCrowdCover *crowd, HuMtx4F lookAt, Vec *rot);
void func_8010BB4C_crowd_cover(Gfx **gfxP, s32 arg1, s32 arg2);
void func_8010C45C_crowd_cover(void);
void func_8010C61C_crowd_cover(void);

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

void func_80106580_crowd_cover(omObjData *object) {
    s16 sounds[3] = { 0x4B8, 0x4B9, 0x4BA };

    if (Hu3DPauseF) {
        HuSprAttrSet(D_8010CFA8_crowd_cover[1], 0, 0x8000);
        return;
    }
    HuSprAttrReset(D_8010CFA8_crowd_cover[1], 0, 0x8000);
    switch (D_8010CFD8_crowd_cover) {
        case 0:
            Hu3DHookFuncCreate(0xC0, func_8010BB4C_crowd_cover, 2);
            D_8010CF80_crowd_cover = 0;
            HuSprTPLvlSet(D_8010CFA8_crowd_cover[1], 0, 0);
            GMesCreate(6);
            D_8010C6C0_crowd_cover = 900;
            D_8010CFD8_crowd_cover++;
            HuAudFXPlay(sounds[D_8010D860_crowd_cover]);
            D_8010CF82_crowd_cover = 45;
        case 1:
            if (--D_8010CF82_crowd_cover == 0) {
                HuAudSeqPlay(0x31);
            }
            if (GMesStatGet() == 0) {
                D_8010CFD8_crowd_cover++;
                GMesCreate(0x1A, (D_8010C6C0_crowd_cover + 29) / 30, 0xA0, 0x20);
                HuAudFXPlay(0xE);
            }
            break;
        case 2:
            if (D_8010CF80_crowd_cover < 0x100) {
                D_8010CF80_crowd_cover += 8;
                HuSprTPLvlSet(D_8010CFA8_crowd_cover[1], 0, D_8010CF80_crowd_cover);
            } else {
                HuSprTPLvlSet(D_8010CFA8_crowd_cover[1], 0, 0x100);
            }
            D_8010C6C0_crowd_cover--;
            func_8003F578_main((D_8010C6C0_crowd_cover + 29) / 30);
            if (D_8010C6C0_crowd_cover == 0) {
                D_8010CFD8_crowd_cover = 3;
            }
            if (PLAYER_WORK(D_800EC598_minigame[0])->unk32 | PLAYER_WORK(D_800EC598_minigame[1])->unk32) {
                D_8010CFD8_crowd_cover = 3;
                if (PLAYER_WORK(D_800EC598_minigame[0])->unk32 != 0 &&
                    PLAYER_WORK(D_800EC598_minigame[1])->unk32 != 0) {
                    PLAYER_WORK(D_800EC598_minigame[func_80108F1C_crowd_cover() & 1])->unk32 = 0;
                }
            }
            break;
        case 3:
            if (PLAYER_WORK(D_800EC598_minigame[0])->unk32 != 0) {
                if (PLAYER_WORK(D_800EC598_minigame[0])->unk32 == D_8010D862_crowd_cover + 1) {
                    D_8010C6D4_crowd_cover = 0;
                    PLAYER_WORK(D_800EC598_minigame[0])->unk2C = 1;
                    PLAYER_WORK(D_800EC598_minigame[1])->unk2C = 0;
                } else {
                    D_8010C6D4_crowd_cover = 1;
                    D_8010C6D8_crowd_cover = PLAYER_WORK(D_800EC598_minigame[0])->unk32;
                    PLAYER_WORK(D_800EC598_minigame[0])->unk2C = 0;
                    PLAYER_WORK(D_800EC598_minigame[1])->unk2C = 1;
                }
                D_8010C6D0_crowd_cover = 36;
            } else if (PLAYER_WORK(D_800EC598_minigame[1])->unk32 != 0) {
                if (PLAYER_WORK(D_800EC598_minigame[1])->unk32 == D_8010D862_crowd_cover + 1) {
                    D_8010C6D4_crowd_cover = 1;
                    PLAYER_WORK(D_800EC598_minigame[0])->unk2C = 0;
                    PLAYER_WORK(D_800EC598_minigame[1])->unk2C = 1;
                } else {
                    D_8010C6D4_crowd_cover = 0;
                    D_8010C6D8_crowd_cover = PLAYER_WORK(D_800EC598_minigame[1])->unk32;
                    PLAYER_WORK(D_800EC598_minigame[0])->unk2C = 1;
                    PLAYER_WORK(D_800EC598_minigame[1])->unk2C = 0;
                }
            } else {
                D_8010C6D4_crowd_cover = -1;
            }
            D_8010C6D0_crowd_cover = 15;
            func_8003F5C0_main();
            GMesCreate(0x11);
            HuAudSeqFadeOut(0x78);
            D_8010CFD8_crowd_cover++;
            break;
        case 4:
            if (D_8010CF80_crowd_cover < 0x100) {
                D_8010CF80_crowd_cover += 8;
                HuSprTPLvlSet(D_8010CFA8_crowd_cover[1], 0, D_8010CF80_crowd_cover);
            } else {
                HuSprTPLvlSet(D_8010CFA8_crowd_cover[1], 0, 0x100);
            }
            D_8010C6C0_crowd_cover -= 10;
            if (D_8010C6C0_crowd_cover > 0) {
                break;
            }
            D_8010C6C0_crowd_cover = 0;
            if (GMesStatGet() != 0) {
                break;
            }
            if (D_8010C6D0_crowd_cover == 15) {
                HuSprAttrReset(D_8010CFA8_crowd_cover[5], 0, 0x8000);
                if (D_8010C6D8_crowd_cover == 0) {
                    HuAudFXPlay(D_8010C6D4_crowd_cover == -1 ? 0x4B6 : 0x4B5);
                    HuSprPosSet(D_8010CFA8_crowd_cover[5], 0, D_8010C6C4_crowd_cover[D_8010D862_crowd_cover][0],
                                D_8010C6C4_crowd_cover[D_8010D862_crowd_cover][1]);
                } else {
                    HuAudFXPlay(0x4B6);
                    func_80054FF8_main(D_8010CFA8_crowd_cover[5], 0, 1);
                    HuSprPosSet(D_8010CFA8_crowd_cover[5], 0, D_8010C6C4_crowd_cover[D_8010C6D8_crowd_cover - 1][0],
                                D_8010C6C4_crowd_cover[D_8010C6D8_crowd_cover - 1][1]);
                }
            }
            if (--D_8010C6D0_crowd_cover == 0) {
                if (D_8010C6D4_crowd_cover == -1) {
                    GMesCreate(0x20);
                    HuAudSeqPlay(0x6C);
                } else {
                    GMesCreate(0x16, PLAYER_WORK(D_800EC598_minigame[D_8010C6D4_crowd_cover])->unk29);
                    HuAudSeqPlay(0x67);
                }
                D_8010C6D0_crowd_cover = 15;
                D_8010CFD8_crowd_cover++;
            }
            break;
        case 5:
            if (GMesStatGet() != 0) {
                break;
            }
            if (--D_8010C6D0_crowd_cover == 0) {
                D_8010CFD8_crowd_cover++;
            }
            break;
        case 6:
            if (D_8010C6D0_crowd_cover != 0) {
                if (--D_8010C6D0_crowd_cover == 0) {
                    D_8010CFD8_crowd_cover++;
                }
            } else {
                D_8010C6D0_crowd_cover = 16;
                WipeCreateOut(WIPE_TYPE_NORMAL, D_8010C6D0_crowd_cover);
                HuAudSeqFadeOut(D_8010C6D0_crowd_cover);
                func_8004AB0C_main((s16)D_8010C6D0_crowd_cover);
            }
            break;
        case 7:
            HuAudSeqStop();
            omOvlReturnEx(1);
            func_8010C61C_crowd_cover();
            break;
    }
    if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010C6D0_crowd_cover = 0;
        D_8010CFD8_crowd_cover = 6;
    }
}

void func_80106CB8_crowd_cover(void) {
    s32 i;

    func_800E18D8_minigame();
    D_800EC280_minigame = 0;
    for (i = 0; i < 2; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 0xB, 0x32, -1, func_80106D4C_crowd_cover);
    }
}

const CrowdCoverCharMotions D_8010CB70_crowd_cover = { { 0, 1, 2, 3, 4, 5, 6, 7 } };

void func_80106D4C_crowd_cover(omObjData *object) {
    CrowdCoverCharMotions motions = D_8010CB70_crowd_cover;
    s32 anims[3][8] = {
        { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C },
        { 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0x1D },
        { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B },
    };
    s16 itemModels[3] = { 14, 13, 12 };
    s32 unused[4]; // Unreferenced, but present in the stack frame.
    func_800E1BA8_minigame_ObjData *data;
    UnkCrowdCoverWork *work;
    s32 i;
    u8 player;
    s8 character;
    s32 model;
    s32 linkModel;
    u16 tag;
    s32 slot;

    for (i = 0; i < 4; i++) {
        if (D_8010C6E4_crowd_cover == GwPlayer[i].group) {
            break;
        }
    }
    player = i;
    character = GwPlayer[player].chr;
    model = D_800A178C_main[character][0];
    linkModel = D_800A178C_main[character][2];
    func_800E19F0_minigame(1);
    func_80107298_crowd_cover(object, model, linkModel, player, 0x2C9);
    data = object->data;
    object->trans.x = D_8010C6EC_crowd_cover[D_8010C6E4_crowd_cover][0];
    object->trans.y = D_8010C6EC_crowd_cover[D_8010C6E4_crowd_cover][1];
    object->trans.z = D_8010C6EC_crowd_cover[D_8010C6E4_crowd_cover][2];
    data->unk3C = D_8010C704_crowd_cover[D_8010C6E4_crowd_cover];
    object->rot.y = object->rot.x = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 0.65f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y - 4.0, object->trans.z);
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelRotSet(object->model[1], -50.0f, object->rot.y, object->rot.z);
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);
    Hu3DModelScaleSet(object->model[1], object->scale.x, object->scale.y, object->scale.z);
    work = data->unk158;
    work->unk28 = i;
    work->unk29 = character;
    work->unk2A = D_8010C6E4_crowd_cover;
    work->unk18 = work->unk14 = data->unk3C;
    work->unk2D = GwPlayer[player].stat & 1;
    work->unk2E = 0;
    work->unk2B = GwPlayer[player].cpu_difficulty;
    work->unk24 = model | 0x2F;
    work->unk2C = 0;
    work->unk1C = 11.0f;
    work->pos.x = object->trans.x;
    work->pos.y = object->trans.y;
    work->pos.z = object->trans.z;
    work->unk20 = 0;
    work->unk31 = func_80017790_main(object->model[0], 2, motions.values[character], model | anims[2][character]);
    work->unk2F = func_80017AD8_main(model | anims[0][character]);
    work->unk30 = func_80017AD8_main(model | anims[1][character]);
    func_8001C514_main(object->model[0]);
    tag = 0x2BD;
    for (i = 0; i < 3; i++) {
        slot = i + 2;
        object->model[slot] = func_8000B108_main(itemModels[i] | 0x590000, tag);
        Hu3DModelHookSet(object->model[slot], object->model[0], "item_hook");
        func_8001C258_main(object->model[slot], 0x4000, 0x4000);
    }
    func_8001C258_main(object->model[2], 4, 0);
    object->model[9] = func_8000B0A0_main(7, 0x2DD);
    object->func = func_80107554_crowd_cover;
    func_800E5A00_minigame(object, 0, func_80017BB8_main(character, 0), 1, 0);
    func_800E5A00_minigame(object, 0x26, func_80017BB8_main(character, 0x66), 1, 0);
    func_800E5A00_minigame(object, 0x27, func_80017BB8_main(character, 0x67), 1, 0x3C);
    func_800E5A00_minigame(object, 0xD, func_80017BB8_main(character, 0x2F), 2, 0x78);
    func_800E5A00_minigame(object, 0xE, func_80017BB8_main(character, 0x36), 2, 0x78);
    func_800E5690_minigame(object, 0x26);
    D_8010C6E4_crowd_cover++;
}

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

void func_80107554_crowd_cover(omObjData *object) {
    CrowdCoverCharMotions motions = D_8010CB70_crowd_cover;
    s16 cpuDelays[4] = { 450, 240, 150, 90 };
    s16 unusedDelays[4] = { 180, 150, 90, 60 }; // Initialized but never read.
    u16 buttons[3] = { 0x8000, 0x4000, 0x2000 };
    s32 unused[4]; // Unreferenced, but present in the stack frame.
    Vec pos;
    func_800E1BA8_minigame_ObjData *data;
    UnkCrowdCoverWork *work;
    u8 pad;
    f32 rot;
    u16 input;
    s32 model;
    HuMtx4F *mtx;

    data = object->data;
    work = data->unk158;
    pad = data->unk57;
    rot = data->unk3C;
    func_800E4A90_minigame(object);
    switch (D_8010CFD8_crowd_cover) {
        case 0:
            if (!work->unk2D) {
                break;
            }
            work->unk34 = cpuDelays[work->unk2B] +
                          (s32)((f32)func_80108F1C_crowd_cover() * 1.52587890625e-05 * cpuDelays[work->unk2B]);
            if ((s32)((f32)func_80108F1C_crowd_cover() * 1.52587890625e-05 * 100.0) < (work->unk2B + 1) * 20) {
                work->unk36 = buttons[D_8010D862_crowd_cover];
            } else {
                work->unk36 = buttons[(s32)((f32)func_80108F1C_crowd_cover() * 1.52587890625e-05 * 3.0)];
            }
            break;
        case 2:
            if (!work->unk2D) {
                input = D_800D5558_main[(s8)pad];
            } else {
                input = func_80107C5C_crowd_cover(object);
            }
            if (input & 0xE000) {
                if (input & 0x8000) {
                    work->unk32 = 3;
                } else if (input & 0x4000) {
                    work->unk32 = 2;
                } else if (input & 0x2000) {
                    work->unk32 = 1;
                }
            }
            break;
        case 3:
            if (work->unk32 != 0) {
                HuAudFXPlay(0x4B4);
                func_8001C258_main(object->model[2], 4, 4);
                func_8001C258_main(object->model[work->unk32 + 1], 4, 0);
            } else {
                func_800E5690_minigame(object, 0);
                model = object->model[9];
                func_801090CC_crowd_cover(object->model[0], "item_hook", Hu3DData[object->model[0]].motTime, &pos);
                func_8001C258_main(model, 4, 0);
                Hu3DModelPosSet(model, pos.x, pos.y, pos.z + 10.0);
                Hu3DModelScaleSet(model, 0.4f, 0.4f, 0.4f);
                Hu3DMotionTimeSet(model, 0.0f);
                Hu3DMotionSpeedSet(model, 2.0f);
                func_8001C814_main(model, 1, 0);
                func_8001C258_main(object->model[2], 4, 4);
            }
        case 4:
            if (rot > 0.0) {
                rot -= 30.0;
                break;
            }
            if (work->unk32 == 0) {
                break;
            }
            rot = 0.0f;
            func_800E5690_minigame(object, 0x27);
            if (Hu3DData[object->model[0]].motTime ==
                D_800CCF58_main[Hu3DData[object->model[0]].motId].unk02 - 2.0) {
                omVibrate(data->unk59, 2, 3, 10);
            }
            break;
        case 5:
            if (work->unk20 != 0) {
                break;
            }
            if (work->unk32 != 0) {
                model = object->model[9];
                func_801090CC_crowd_cover(object->model[0], "item_hook", Hu3DData[object->model[0]].motTime, &pos);
                func_8001C258_main(model, 4, 0);
                Hu3DModelPosSet(model, pos.x, pos.y, pos.z + 10.0);
                Hu3DModelScaleSet(model, 0.4f, 0.4f, 0.4f);
                Hu3DMotionTimeSet(model, 0.0f);
                Hu3DMotionSpeedSet(model, 2.0f);
                func_8001C814_main(model, 1, 0);
                func_8001C258_main(object->model[work->unk32 + 1], 4, 4);
            }
            if (work->unk2C) {
                GwPlayer[data->unk59].bonusCoin += 10;
                func_80017954_main(object->model[0], 2, motions.values[work->unk29], work->unk2F);
                func_800E5690_minigame(object, 0xD);
                func_80045F1C_main(work->unk24, -1, work->unk2A);
            } else {
                func_80017954_main(object->model[0], 2, motions.values[work->unk29], work->unk30);
                func_800E5690_minigame(object, 0xE);
            }
            work->unk20++;
            break;
        case 6:
            if (data != NULL) {
                HuMemFree(data->unkE8);
                HuMemFree(data->unk158);
                HuMemFree(data);
                object->data = NULL;
                object->func = NULL;
            }
            return;
        case 7:
            return;
    }
    mtx = &Hu3DData[object->model[0]].mtx;
    guMtxIdentF(*mtx);
    func_8008A120_main(*mtx, -50.0f);
    mtxRotCat(*mtx, 0.0f, rot, 0.0f);
    data->unk3C = rot;
    func_800E4E30_minigame(object);
}

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

void func_80107E40_crowd_cover(omObjData *object) {
    Vec positions[30] = {
        { 180.0f, 0.0f, -80.0f },
        { 170.0f, 0.0f, -160.0f },
        { 160.0f, 0.0f, -280.0f },
        { 136.0f, 0.0f, -140.0f },
        { 120.0f, 0.0f, -110.0f },
        { 120.0f, 0.0f, -180.0f },
        { 100.0f, 0.0f, -300.0f },
        { 90.0f, 0.0f, -210.0f },
        { 80.0f, 0.0f, -80.0f },
        { 80.0f, 0.0f, -260.0f },
        { 80.0f, 0.0f, -320.0f },
        { 50.0f, 0.0f, -240.0f },
        { 40.0f, 0.0f, -80.0f },
        { 10.0f, 0.0f, -320.0f },
        { 0.0f, 0.0f, -120.0f },
        { 0.0f, 0.0f, -260.0f },
        { -10.0f, 0.0f, -200.0f },
        { -40.0f, 0.0f, -320.0f },
        { -50.0f, 0.0f, -80.0f },
        { -86.0f, 0.0f, -140.0f },
        { -90.0f, 0.0f, -64.0f },
        { -80.0f, 0.0f, -220.0f },
        { -100.0f, 0.0f, -170.0f },
        { -120.0f, 0.0f, -360.0f },
        { -130.0f, 0.0f, -180.0f },
        { -136.0f, 0.0f, -240.0f },
        { -124.0f, 0.0f, -290.0f },
        { -140.0f, 0.0f, -240.0f },
        { -160.0f, 0.0f, -140.0f },
        { -190.0f, 0.0f, -100.0f },
    };
    s16 order[30];
    u16 dataNums[3] = { 1, 2, 3 };
    CrowdCoverMember *member;
    s32 i;
    s16 j;
    s16 temp;

    D_8010D864_crowd_cover = func_801091FC_crowd_cover(dataNums[D_8010D860_crowd_cover] | 0x590000);
    D_8010D866_crowd_cover = 30;
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 0.8f;
    for (i = 0; i < D_8010D866_crowd_cover; i++) {
        order[i] = i;
    }
    for (i = D_8010D866_crowd_cover; i > 0; i--) {
        j = (f32)func_80108F1C_crowd_cover() * 1.52587890625e-05 * i;
        temp = order[i - 1];
        order[i - 1] = order[j];
        order[j] = temp;
    }
    member = D_8010CFE0_crowd_cover;
    for (i = 0; i < D_8010D866_crowd_cover; i++, member++) {
        member->crowdIndex = func_8010A12C_crowd_cover(D_8010D864_crowd_cover, 0x401808);
        member->model = func_8000B0D4_main(9, 0x2C9);
        func_8001FA68_main(member->model);
        func_8001F9E4_main(member->model, 0xFF);
        member->pos.x = positions[order[i]].x;
        member->pos.y = positions[order[i]].y;
        member->pos.z = positions[order[i]].z;
        member->state = 1;
        member->unk04 = 0;
        member->timer = (s32)((f32)func_80108F1C_crowd_cover() * 1.52587890625e-05 * 30.0) + 1;
        member->vel.x = member->vel.y = member->vel.z = 0.0f;
        member->unk06 = member->unk07 = 0;
        member->unk0C = 0.0f;
        member->unk34 = (f32)func_80108F1C_crowd_cover() * 1.52587890625e-05 * 360.0;
        member->unk38 = member->unk3C = member->unk40 = 0.0f;
        if (D_8010D860_crowd_cover == 1) {
            member->unk34 = func_8000B0A0_main(0x10013, 0x2DD);
        } else if (D_8010D860_crowd_cover == 2) {
            member->unk3C = member->unk04 * 4;
        }
        func_8010ADBC_crowd_cover(member->crowdIndex, 16.0f, 32.0f, 0.0f);
        func_8010AE5C_crowd_cover(member->crowdIndex, member->pos.x, member->pos.y, member->pos.z);
        func_8010AF14_crowd_cover(member->crowdIndex, 2.5f, 2.5f, 1.0f);
        Hu3DModelScaleSet(member->model, 0.45f, 0.45f, 0.45f);
    }
    object->func = func_80108238_crowd_cover;
}

void func_80108238_crowd_cover(omObjData *object) {
    CrowdCoverMember *member;
    CrowdCoverMember *other;
    s32 i;
    s32 j;
    s32 model;
    s32 frame;
    f32 scale;
    f32 angle;

    member = D_8010CFE0_crowd_cover;
    for (i = 0; i < D_8010D866_crowd_cover; i++, member++) {
        member->timer--;
        switch (member->state) {
            case 0:
                member->timer = (s32)((f32)func_80108F1C_crowd_cover() * 1.52587890625e-05 * 10.0) + 15;
                member->state = 1;
                member->vel.x = member->vel.z = 0.0f;
                if (func_80108F1C_crowd_cover() & 1) {
                    break;
                }
                member->unk04 = (f32)func_80108F1C_crowd_cover() * 1.52587890625e-05 * 8.0;
                if (func_80108F1C_crowd_cover() & 1) {
                    break;
                }
            case 2:
                member->vel.x = sindf(member->unk04 * 45.0) * 4.0;
                member->vel.z = cosdf(member->unk04 * 45.0) * 4.0;
                member->timer = 20;
                member->state = 3;
                break;
            case 1:
                member->unk06 = member->unk04 & 7;
                if (member->timer == 0) {
                    member->state = 0;
                }
                break;
            case 3:
                member->unk0C += 0.5;
                if (member->timer == 0) {
                    member->state = 0;
                }
                break;
            case 4:
                switch (D_8010D860_crowd_cover) {
                    case 0:
                        if (member->pos.x >= 0.0) {
                            member->vel.x = 8.0f;
                            member->unk04 = 2;
                            if (member->pos.x >= 500.0) {
                                member->state = 6;
                            }
                        } else {
                            member->vel.x = -8.0f;
                            member->unk04 = 6;
                            if (member->pos.x <= -500.0) {
                                member->state = 6;
                            }
                        }
                        member->unk0C += 1.0;
                        break;
                    case 1:
                        member->unk04 = 8;
                        member->unk0C += 0.5;
                        member->unk07 = member->unk0C;
                        scale = member->unk0C * 0.1 + 2.5;
                        func_8010AF14_crowd_cover(member->crowdIndex, scale, scale, 1.0f);
                        if (member->unk07 >= 8) {
                            func_8010AFB4_crowd_cover(member->crowdIndex, 0x8000);
                            func_8001C258_main(member->model, 4, 4);
                            model = member->unk34;
                            HuAudFXPlay(0x4B7);
                            func_8001C258_main(model, 4, 0);
                            Hu3DModelPosSet(model, member->pos.x, member->pos.y + 40.0, member->pos.z);
                            Hu3DModelScaleSet(model, object->scale.x, object->scale.y, object->scale.z);
                            Hu3DMotionTimeSet(model, 0.0f);
                            Hu3DMotionSpeedSet(model, 1.5f);
                            func_8001C814_main(model, 1, 0);
                            member->state = 5;
                        }
                        break;
                    case 2:
                        member->unk04 = 0;
                        member->pos.y += 8.0;
                        member->unk34 = 0.0f;
                        member->unk38 += 20.0;
                        if (member->unk38 >= 360.0) {
                            member->unk38 -= 360.0;
                        }
                        member->offset.x = sindf(member->unk38) * 6.0;
                        member->timer -= 9;
                        func_8010B1DC_crowd_cover(member->crowdIndex, 0, 0, 0, member->timer);
                        func_8001F9E4_main(member->model, member->timer);
                        if (member->timer == 0) {
                            member->state = 6;
                        }
                        break;
                }
                break;
            case 5:
                model = member->unk34;
                if (Hu3DData[model].motTime >= D_800CCF58_main[Hu3DData[model].motId].unk02) {
                    Hu3DModelKill(model);
                    member->state = 6;
                }
                continue;
            case 6:
                func_8010AFB4_crowd_cover(member->crowdIndex, 0x8000);
                func_8001C258_main(member->model, 4, 4);
                continue;
        }
        member->pos.x += member->vel.x;
        member->pos.z += member->vel.z;
        if (member->state < 4) {
            if (i >= (s16)(D_8010C6C0_crowd_cover / 30)) {
                member->vel.x = member->vel.z = 0.0f;
                member->state = 4;
                member->unk0C = 0.0f;
                member->unk38 = 0.0f;
                member->timer = 250;
            }
            for (j = 0; j < D_8010D866_crowd_cover; j++) {
                if (i == j) {
                    continue;
                }
                other = &D_8010CFE0_crowd_cover[j];
                if (other->state >= 4) {
                    continue;
                }
                if (func_80108FDC_crowd_cover(&member->pos, &other->pos) >= 40.0) {
                    continue;
                }
                angle = func_80108F74_crowd_cover(other->pos.x - member->pos.x, other->pos.z - member->pos.z) + 180.0;
                member->state = 0;
                if (angle >= 360.0) {
                    angle -= 360.0;
                }
                member->pos.x = other->pos.x + sindf(angle) * 42.0;
                member->pos.z = other->pos.z + cosdf(angle) * 42.0;
            }
            if (member->pos.x > 200.0) {
                member->state = func_80108F1C_crowd_cover() & 1;
                member->unk04 = (s32)((f32)func_80108F1C_crowd_cover() * 1.52587890625e-05 * 3.0) + 5;
                member->pos.x = 200.0f;
            } else if (member->pos.x < -200.0) {
                member->state = func_80108F1C_crowd_cover() & 1;
                member->unk04 = (s32)((f32)func_80108F1C_crowd_cover() * 1.52587890625e-05 * 3.0) + 1;
                member->pos.x = -200.0f;
            }
            if (member->pos.z > -60.0) {
                member->state = func_80108F1C_crowd_cover() & 1;
                member->unk04 = (s32)((f32)func_80108F1C_crowd_cover() * 1.52587890625e-05 * 3.0) + 3;
                member->pos.z = -60.0f;
            } else if (member->pos.z < -500.0) {
                member->state = func_80108F1C_crowd_cover() & 1;
                member->unk04 = ((s32)((f32)func_80108F1C_crowd_cover() * 1.52587890625e-05 * 3.0) + 7) & 7;
                member->pos.z = -500.0f;
            }
        }
        member->unk06 = member->unk04;
        member->unk07 = member->unk0C;
        frame = D_8010C714_crowd_cover[member->unk06][member->unk07];
        if (frame == -1) {
            member->unk07 = 0;
            member->unk0C = 0.0f;
            frame = D_8010C714_crowd_cover[member->unk06][member->unk07];
        }
        if (D_8010D860_crowd_cover == 2) {
            member->unk34 += 10.0;
            if (member->unk34 >= 360.0) {
                member->unk34 -= 360.0;
            }
            member->offset.y = sindf(member->unk34) * 8.0 + 20.0;
            member->pos.x -= member->vel.x * 0.5;
            member->pos.z -= member->vel.z * 0.5;
            frame = member->unk04 * 4;
            if (frame != (s32)member->unk3C) {
                if ((s32)member->unk3C < frame) {
                    if (frame - (s32)member->unk3C < 16) {
                        member->unk3C += 1.0;
                    } else {
                        member->unk3C -= 1.0;
                    }
                } else if (frame < (s32)member->unk3C) {
                    if (frame - (s32)member->unk3C > -16) {
                        member->unk3C -= 1.0;
                    } else {
                        member->unk3C += 1.0;
                    }
                }
                if (member->unk3C >= 30.0) {
                    member->unk3C -= 30.0;
                } else if (member->unk3C < 0.0) {
                    member->unk3C += 30.0;
                }
                frame = member->unk3C;
            }
        }
        func_8010AE5C_crowd_cover(member->crowdIndex, member->pos.x + member->offset.x,
                                  member->pos.y + member->offset.y, member->pos.z);
        func_8010AD3C_crowd_cover(member->crowdIndex, frame);
        Hu3DModelPosSet(member->model, member->pos.x, 0.0f, member->pos.z - 5.0);
    }
}

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

s16 func_8010980C_crowd_cover(UnkCrowdCover *crowd) {
    HuSprite_Unk84_Unk00_Struct segCel;
    Gfx *gfx;
    Gfx *buf;
    Gfx *start;
    HuSprite_Unk84_Unk00_Struct *cel;
    s32 fmt;
    s32 mode;
    s32 alignedWidth;
    u32 rows;
    u32 count;
    s32 siz;
    s32 remainder;
    s32 cms;
    s32 cmt;
    s32 masks;
    s32 maskt;
    u32 i;

    cel = crowd->sprite->unk00;
    buf = HuMemAlloc(0x1000);
    gfx = buf;
    gSPSegment(gfx++, 0x0C, cel->unk00);
    gSPSegment(gfx++, 0x0E, crowd->vtx);
    start = gfx;
    gDPPipeSync(gfx++);
    switch (crowd->sprite->unk18) {
        case 4:
            siz = G_IM_SIZ_4b;
            if (crowd->sprite->unk1A == 1) {
                fmt = G_IM_FMT_IA;
                gDPSetTextureLUT(gfx++, G_TT_NONE);
            } else {
                fmt = G_IM_FMT_CI;
                gDPLoadTLUT_pal16(gfx++, 0, crowd->sprite->unk0C);
                gDPSetTextureLUT(gfx++, G_TT_RGBA16);
            }
            mode = 0;
            break;
        case 8:
            siz = G_IM_SIZ_8b;
            if (crowd->sprite->unk1A == 1) {
                fmt = G_IM_FMT_IA;
                gDPSetTextureLUT(gfx++, G_TT_NONE);
            } else {
                fmt = G_IM_FMT_CI;
                gDPLoadTLUT_pal256(gfx++, crowd->sprite->unk0C);
                gDPSetTextureLUT(gfx++, G_TT_RGBA16);
            }
            mode = 2;
            break;
        case 16:
            siz = G_IM_SIZ_16b;
            if (crowd->sprite->unk1A == 1) {
                fmt = G_IM_FMT_IA;
            } else {
                fmt = G_IM_FMT_RGBA;
            }
            gDPSetTextureLUT(gfx++, G_TT_NONE);
            mode = 2;
            break;
        case 32:
            siz = G_IM_SIZ_32b;
            fmt = G_IM_FMT_RGBA;
            gDPSetTextureLUT(gfx++, G_TT_NONE);
            mode = 2;
            break;
        case 0x8004:
            siz = G_IM_SIZ_4b;
            fmt = G_IM_FMT_I;
            gDPSetTextureLUT(gfx++, G_TT_NONE);
            mode = 0;
            break;
        case 0x8008:
            siz = G_IM_SIZ_8b;
            fmt = G_IM_FMT_I;
            gDPSetTextureLUT(gfx++, G_TT_NONE);
            mode = 2;
            break;
    }
    alignedWidth = (((cel->unk04 << siz) >> 4) << 4) >> siz;
    if (alignedWidth < cel->unk04) {
        alignedWidth += 16 >> siz;
    }
    switch (fmt) {
        case G_IM_FMT_CI:
            if ((4096 >> siz) >= cel->unk06 * alignedWidth) {
                rows = cel->unk06;
            } else {
                rows = (4096 >> siz) / alignedWidth;
            }
            break;
        case G_IM_FMT_I:
            if (4096 >= cel->unk06 * alignedWidth) {
                rows = cel->unk06;
            } else {
                rows = 4096 / alignedWidth;
            }
            break;
        default:
            if ((8192 >> siz) >= cel->unk06 * alignedWidth) {
                rows = cel->unk06;
            } else {
                rows = (8192 >> siz) / alignedWidth;
            }
            break;
    }
    count = cel->unk06 / rows;
    remainder = cel->unk06 - count * rows;
    // Aligned strips can use the block loader when its DXT rounding is exact.
    if (cel->unk04 % (16 >> siz) == 0) {
        if (((rows * cel->unk04) << siz) <= 4096) {
            if (D_8010C814_crowd_cover[cel->unk04 >> D_8010C804_crowd_cover[siz]] >= rows ||
                rows == D_8010C94C_crowd_cover[cel->unk04 >> D_8010C804_crowd_cover[siz]]) {
                mode++;
            }
        }
    }
    // The differing masks/maskt byte conversions are required to match register allocation.
    if (crowd->unk_28 & 0xC0000) {
        masks = crowd->unk_1B & 0xFF;
        cms = (crowd->unk_28 >> 18) - 1;
    } else {
        masks = 0;
        cms = 0;
    }
    if (crowd->unk_28 & 0x300000) {
        maskt = (u8)crowd->unk_1C;
        cmt = (crowd->unk_28 >> 20) - 1;
    } else {
        maskt = 0;
        cmt = 0;
    }
    gDPPipeSync(gfx++);
    segCel = *cel;
    segCel.unk00 = (void *)0x0C000000;
    if ((u32)crowd->unk_28 >= 0x80000000 && count == 1 && remainder == 0) {
        func_8010949C_crowd_cover(&gfx, &segCel, fmt, siz, rows, 0, 0, cel->unk04 - 1, cel->unk06 - 1, cms, cmt, masks,
                                  maskt, mode);
        gSPVertex(gfx++, (Vtx *)0x0E000000, 5, 0);
        gSP2Triangles(gfx++, 0, 2, 4, 0, 2, 3, 4, 0);
        gSP2Triangles(gfx++, 0, 4, 1, 0, 4, 3, 1, 0);
    } else {
        for (i = 0; i < count; i++) {
            func_8010949C_crowd_cover(&gfx, &segCel, fmt, siz, rows, 0, i * rows, cel->unk04 - 1, (i + 1) * rows - 1,
                                      cms, cmt, masks, maskt, mode);
            gSPVertex(gfx++, (Vtx *)0x0E000000 + i * 2, 4, 0);
            gSP2Triangles(gfx++, 0, 2, 3, 0, 0, 3, 1, 0);
        }
        if (remainder != 0) {
            func_8010949C_crowd_cover(&gfx, &segCel, fmt, siz, remainder, 0, i * rows, cel->unk04 - 1,
                                      cel->unk06 - 1, cms, cmt, masks, maskt, mode);
            gSPVertex(gfx++, (Vtx *)0x0E000000 + i * 2, 4, 0);
            gSP2Triangles(gfx++, 0, 2, 3, 0, 0, 3, 1, 0);
        }
    }
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    crowd->unk_22 = gfx - start;
    crowd->displayList = HuMemAlloc(crowd->unk_22 * sizeof(Gfx));
    memcpy(crowd->displayList, start, crowd->unk_22 * sizeof(Gfx));
    HuMemFree(buf);
    return 1;
}

s16 func_8010A12C_crowd_cover(s16 spriteId, s32 flags) {
    UnkCrowdCover *crowd;
    HuSprite_Unk84_Unk00_Struct *cel;
    s32 index;
    s32 siz;
    s32 fmt;
    s32 alignedWidth;
    u32 rows;
    u32 count;
    s32 remainder;
    u32 i;
    s32 j;

    for (index = 0; index < D_8010D904_crowd_cover; index++) {
        if (D_8010D8EC_crowd_cover[index].sprite == NULL) {
            break;
        }
    }
    if (index == D_8010D904_crowd_cover) {
        return -1;
    }
    crowd = &D_8010D8EC_crowd_cover[index];
    crowd->sprite = D_800C9530_main[spriteId];
    crowd->unk_28 = flags;
    crowd->unk_1A = 7;
    cel = crowd->sprite->unk00;
    switch (crowd->sprite->unk18) {
        case 4:
            siz = G_IM_SIZ_4b;
            fmt = (crowd->sprite->unk1A == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 8:
            siz = G_IM_SIZ_8b;
            fmt = (crowd->sprite->unk1A == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 16:
            siz = G_IM_SIZ_16b;
            fmt = (crowd->sprite->unk1A == 1) ? G_IM_FMT_IA : G_IM_FMT_RGBA;
            break;
        case 32:
            siz = G_IM_SIZ_32b;
            fmt = G_IM_FMT_RGBA;
            break;
        case 0x8004:
            siz = G_IM_SIZ_4b;
            fmt = G_IM_FMT_I;
            break;
        case 0x8008:
            siz = G_IM_SIZ_8b;
            fmt = G_IM_FMT_I;
            break;
    }
    alignedWidth = (((cel->unk04 << siz) >> 4) << 4) >> siz;
    if (alignedWidth < cel->unk04) {
        alignedWidth += 16 >> siz;
    }
    switch (fmt) {
        case G_IM_FMT_CI:
            if ((4096 >> siz) >= cel->unk06 * alignedWidth) {
                rows = cel->unk06;
            } else {
                rows = (4096 >> siz) / alignedWidth;
            }
            break;
        case G_IM_FMT_I:
            if (4096 >= cel->unk06 * alignedWidth) {
                rows = cel->unk06;
            } else {
                rows = 4096 / alignedWidth;
            }
            break;
        default:
            if ((8192 >> siz) >= cel->unk06 * alignedWidth) {
                rows = cel->unk06;
            } else {
                rows = (8192 >> siz) / alignedWidth;
            }
            break;
    }
    count = cel->unk06 / rows;
    remainder = cel->unk06 - count * rows;
    crowd->unk_18 = count + 2;
    crowd->unk_19 = rows;
    crowd->vtx = HuMemAlloc((count + 2) * 2 * sizeof(Vtx));
    for (i = 0; i < count + 1; i++) {
        crowd->vtx[i * 2].ob[0] = 0;
        crowd->vtx[i * 2 + 1].ob[0] = cel->unk04;
        crowd->vtx[i * 2].ob[1] = crowd->vtx[i * 2 + 1].ob[1] = -i * rows;
        crowd->vtx[i * 2].tc[0] = 0;
        crowd->vtx[i * 2 + 1].tc[0] = cel->unk04 << 6;
        crowd->vtx[i * 2].tc[1] = (i * rows) << 6;
        crowd->vtx[i * 2 + 1].tc[1] = (i * rows) << 6;
        for (j = 0; j < 2; j++) {
            crowd->vtx[i * 2 + j].ob[2] = 0;
            crowd->vtx[i * 2 + j].cn[0] = 0xFF;
            crowd->vtx[i * 2 + j].cn[1] = 0xFF;
            crowd->vtx[i * 2 + j].cn[2] = 0xFF;
            crowd->vtx[i * 2 + j].cn[3] = 0xFF;
        }
    }
    if (remainder != 0) {
        crowd->vtx[i * 2].ob[0] = 0;
        crowd->vtx[i * 2 + 1].ob[0] = cel->unk04;
        crowd->vtx[i * 2].ob[1] = crowd->vtx[i * 2 + 1].ob[1] = cel->unk06;
        crowd->vtx[i * 2].tc[0] = 0;
        crowd->vtx[i * 2 + 1].tc[0] = cel->unk04 << 6;
        crowd->vtx[i * 2].tc[1] = crowd->vtx[i * 2 + 1].tc[1] = cel->unk06 << 6;
        for (j = 0; j < 2; j++) {
            crowd->vtx[i * 2 + j].ob[2] = 0;
            crowd->vtx[i * 2 + j].cn[0] = 0xFF;
            crowd->vtx[i * 2 + j].cn[1] = 0xFF;
            crowd->vtx[i * 2 + j].cn[2] = 0xFF;
            crowd->vtx[i * 2 + j].cn[3] = 0xFF;
        }
    } else if (count == 1) {
        crowd->vtx[4].ob[0] = cel->unk04 * 0.5;
        crowd->vtx[4].ob[1] = -cel->unk06 * 0.5;
        crowd->vtx[4].ob[2] = 0;
        crowd->vtx[4].tc[0] = cel->unk04 * 0.5 * 64.0;
        crowd->vtx[4].tc[1] = cel->unk06 * 0.5 * 64.0;
        crowd->vtx[4].cn[0] = 0xFF;
        crowd->vtx[4].cn[1] = 0xFF;
        crowd->vtx[4].cn[2] = 0xFF;
        crowd->vtx[4].cn[3] = 0xFF;
    }
    if (!func_8010980C_crowd_cover(crowd)) {
        HuMemFree(crowd->vtx);
        index = -1;
    }
    return index;
}

void func_8010A734_crowd_cover(s16 index, s16 spriteId) {
    UnkCrowdCover *crowd;
    HuSprite_Unk84_Unk00_Struct *cel;
    s32 siz;
    s32 fmt;
    s32 alignedWidth;
    u32 rows;
    u32 count;
    s32 remainder;
    u32 i;
    s32 j;

    crowd = &D_8010D8EC_crowd_cover[index];
    crowd->sprite = D_800C9530_main[spriteId];
    cel = crowd->sprite->unk00;
    HuMemFree(crowd->vtx);
    HuMemFree(crowd->displayList);
    switch (crowd->sprite->unk18) {
        case 4:
            siz = G_IM_SIZ_4b;
            fmt = (crowd->sprite->unk1A == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 8:
            siz = G_IM_SIZ_8b;
            fmt = (crowd->sprite->unk1A == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 16:
            siz = G_IM_SIZ_16b;
            fmt = (crowd->sprite->unk1A == 1) ? G_IM_FMT_IA : G_IM_FMT_RGBA;
            break;
        case 32:
            siz = G_IM_SIZ_32b;
            fmt = G_IM_FMT_RGBA;
            break;
        case 0x8004:
            siz = G_IM_SIZ_4b;
            fmt = G_IM_FMT_I;
            break;
        case 0x8008:
            siz = G_IM_SIZ_8b;
            fmt = G_IM_FMT_I;
            break;
    }
    alignedWidth = (((cel->unk04 << siz) >> 4) << 4) >> siz;
    if (alignedWidth < cel->unk04) {
        alignedWidth += 16 >> siz;
    }
    switch (fmt) {
        case G_IM_FMT_CI:
            if ((4096 >> siz) >= cel->unk06 * alignedWidth) {
                rows = cel->unk06;
            } else {
                rows = (4096 >> siz) / alignedWidth;
            }
            break;
        case G_IM_FMT_I:
            if (4096 >= cel->unk06 * alignedWidth) {
                rows = cel->unk06;
            } else {
                rows = 4096 / alignedWidth;
            }
            break;
        default:
            if ((8192 >> siz) >= cel->unk06 * alignedWidth) {
                rows = cel->unk06;
            } else {
                rows = (8192 >> siz) / alignedWidth;
            }
            break;
    }
    count = cel->unk06 / rows;
    remainder = cel->unk06 - count * rows;
    crowd->unk_18 = count + 2;
    crowd->unk_19 = rows;
    crowd->vtx = HuMemAlloc((count + 2) * 2 * sizeof(Vtx));
    for (i = 0; i < count + 1; i++) {
        crowd->vtx[i * 2].ob[0] = 0;
        crowd->vtx[i * 2 + 1].ob[0] = cel->unk04;
        crowd->vtx[i * 2].ob[1] = crowd->vtx[i * 2 + 1].ob[1] = -i * rows;
        crowd->vtx[i * 2].tc[0] = 0;
        crowd->vtx[i * 2 + 1].tc[0] = cel->unk04 << 6;
        crowd->vtx[i * 2].tc[1] = (i * rows) << 6;
        crowd->vtx[i * 2 + 1].tc[1] = (i * rows) << 6;
        for (j = 0; j < 2; j++) {
            crowd->vtx[i * 2 + j].ob[2] = 0;
            crowd->vtx[i * 2 + j].cn[0] = 0xFF;
            crowd->vtx[i * 2 + j].cn[1] = 0xFF;
            crowd->vtx[i * 2 + j].cn[2] = 0xFF;
            crowd->vtx[i * 2 + j].cn[3] = 0xFF;
        }
    }
    if (remainder != 0) {
        crowd->vtx[i * 2].ob[0] = 0;
        crowd->vtx[i * 2 + 1].ob[0] = cel->unk04;
        crowd->vtx[i * 2].ob[1] = crowd->vtx[i * 2 + 1].ob[1] = cel->unk06;
        crowd->vtx[i * 2].tc[0] = 0;
        crowd->vtx[i * 2 + 1].tc[0] = cel->unk04 << 6;
        crowd->vtx[i * 2].tc[1] = crowd->vtx[i * 2 + 1].tc[1] = cel->unk06 << 6;
        for (j = 0; j < 2; j++) {
            crowd->vtx[i * 2 + j].ob[2] = 0;
            crowd->vtx[i * 2 + j].cn[0] = 0xFF;
            crowd->vtx[i * 2 + j].cn[1] = 0xFF;
            crowd->vtx[i * 2 + j].cn[2] = 0xFF;
            crowd->vtx[i * 2 + j].cn[3] = 0xFF;
        }
    } else if (count == 1) {
        crowd->vtx[4].ob[0] = cel->unk04 * 0.5;
        crowd->vtx[4].ob[1] = -cel->unk06 * 0.5;
        crowd->vtx[4].ob[2] = 0;
        crowd->vtx[4].tc[0] = cel->unk04 * 0.5 * 64.0;
        crowd->vtx[4].tc[1] = cel->unk06 * 0.5 * 64.0;
        crowd->vtx[4].cn[0] = 0xFF;
        crowd->vtx[4].cn[1] = 0xFF;
        crowd->vtx[4].cn[2] = 0xFF;
        crowd->vtx[4].cn[3] = 0xFF;
    }
    func_8010980C_crowd_cover(crowd);
}

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

Gfx *func_8010BD74_crowd_cover(Gfx *gfx, UnkCrowdCover *crowd, HuMtx4F lookAt, Vec *rot) {
    HuMtx4F scale;
    HuMtx4F mtx;
    HuMtx4F billboard;
    HuMtx4F inverse;
    HuSprite_Unk84_Unk00_Struct *cel;
    u16 format;
    u32 blend;
    u32 mode;
    Vtx *vtx;
    Mtx *mtxL;
    Gfx *dl;

    cel = &crowd->sprite->unk00[crowd->unk_24];
    gDPPipeSync(gfx++);
    gDPSetTextureFilter(gfx++, D_8010CA8C_crowd_cover[(crowd->unk_28 >> 2) & 3]);
    gDPSetColorDither(gfx++, D_8010CA84_crowd_cover[(crowd->unk_28 >> 4) & 3]);
    gDPSetAlphaCompare(gfx++, D_8010CA94_crowd_cover[(crowd->unk_28 >> 22) & 3]);
    if (crowd->unk_28 & 0x10000) {
        gSPSetGeometryMode(gfx++, G_LIGHTING);
    } else {
        gSPClearGeometryMode(gfx++, G_LIGHTING);
    }
    format = crowd->sprite->unk18;
    blend = 0x110000;
    if (crowd->unk_28 & 0x8000000) {
        blend = 0xC8004000;
    }
    if (crowd->unk_28 & 0x1000) {
        if (format & 0x8000) {
            mode = 0x4850;
            blend = 0x100000;
            if (crowd->unk_20 == 0x100) {
                gDPSetCombineMode(gfx++, CROWD_CC_PRIM_DECALA, CROWD_CC_MODULATEI_PASSA2);
            } else {
                gDPSetCombineMode(gfx++, CROWD_CC_PRIM_MODULATEA, G_CC_MODULATEIA2);
            }
        } else if (crowd->unk_20 == 0x100) {
            mode = 0x3038;
            if (crowd->unk_28 & 0x2000000) {
                gDPSetCombineMode(gfx++, CROWD_CC_BLEND_DECALA, CROWD_CC_MODULATEI_PASSA2);
            } else {
                gDPSetCombineMode(gfx++, G_CC_MODULATEIDECALA, CROWD_CC_MODULATEI_PASSA2);
            }
        } else {
            mode = 0x4850;
            blend = 0x100000;
            if (crowd->unk_28 & 0x2000000) {
                gDPSetCombineMode(gfx++, CROWD_CC_BLEND_MODULATEA, G_CC_MODULATEIA2);
            } else {
                gDPSetCombineMode(gfx++, CROWD_CC_MODULATEI_PRIMA, G_CC_MODULATEIA2);
            }
        }
    } else {
        mode = 0x2030;
        if (crowd->unk_28 & 0x2000000) {
            gDPSetCombineMode(gfx++, CROWD_CC_BLEND_MODULATEA, G_CC_PASS2);
        } else {
            gDPSetCombineMode(gfx++, CROWD_CC_MODULATEI_PRIMA, G_CC_PASS2);
        }
    }
    switch ((crowd->unk_28 >> 10) & 3) {
        case 0:
            mode |= 0x200;
            break;
        case 2:
            mode |= 0x40;
            if (crowd->unk_28 & 0x1000) {
                mode |= 0x180;
            }
        case 1:
            mode |= 0x8;
            break;
    }
    if (crowd->unk_28 & 0x2000) {
        mode |= 0xC00;
    }
    if (crowd->unk_28 & 0x8000000) {
        gSPSetGeometryMode(gfx++, G_FOG);
        gDPSetRenderMode(gfx++, G_RM_FOG_SHADE_A, mode | blend);
    } else {
        gSPClearGeometryMode(gfx++, G_FOG);
        gDPSetRenderMode(gfx++, G_RM_PASS, mode | blend);
    }
    gDPSetPrimColor(gfx++, 0, 0, crowd->unk_1D, crowd->unk_1E, crowd->unk_1F, crowd->unk_20);
    vtx = D_8010D8FC_crowd_cover;
    mtxL = (Mtx *)&vtx[crowd->unk_18 * 2];
    dl = (Gfx *)&mtxL[1];
    D_8010D8FC_crowd_cover = &dl[crowd->unk_22];
    guMtxIdentF(billboard);
    if (crowd->unk_28 & 0x4000000) {
        billboard[3][0] = -crowd->unk_30.y;
        billboard[3][1] = crowd->unk_30.z;
    } else {
        billboard[3][0] = -(u16)cel->unk08;
        billboard[3][1] = (u16)cel->unk0A;
    }
    billboard[3][2] = crowd->unk_3C;
    func_8002367C_main(mtx, lookAt);
    mtxTransCat(mtx, crowd->unk_40.x, crowd->unk_40.y, crowd->unk_40.z);
    mtxRotCat(mtx, crowd->unk_58.x, crowd->unk_58.y, crowd->unk_58.z);
    mtxScaleCat(mtx, crowd->unk_4C.x, crowd->unk_4C.y, crowd->unk_4C.z);
    switch (crowd->unk_1A) {
        case 1:
            func_8008A120_main(mtx, rot->x);
            break;
        case 2:
            func_8008A2A0_main(mtx, rot->y);
            break;
        case 4:
            break;
        case 7:
            scale[0][0] = crowd->unk_4C.x;
            scale[1][1] = crowd->unk_4C.y;
            scale[2][2] = crowd->unk_4C.z;
            scale[3][3] = 1.0f;
            scale[0][1] = scale[0][2] = scale[0][3] = scale[1][0] = scale[1][2] = scale[1][3] = scale[2][0] =
                scale[2][1] = scale[2][3] = scale[3][0] = scale[3][1] = scale[3][2] = 0.0f;
            func_80018544_main(mtx, inverse);
            func_80018044_main(scale, inverse, mtx);
            break;
    }
    guMtxCatF(billboard, mtx, mtx);
    guMtxF2L(mtx, mtxL);
    gDPPipeSync(gfx++);
    gSPMatrix(gfx++, osVirtualToPhysical(mtxL), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPPipeSync(gfx++);
    gSPSegment(gfx++, 0x0C, cel->unk00);
    gSPSegment(gfx++, 0x0E, vtx);
    gDPPipeSync(gfx++);
    memcpy(vtx, crowd->vtx, crowd->unk_18 * 2 * sizeof(Vtx));
    memcpy(dl, crowd->displayList, crowd->unk_22 * sizeof(Gfx));
    if (!(crowd->unk_28 & 0x8000)) {
        gSPDisplayList(gfx++, dl);
    }
    return gfx;
}

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
