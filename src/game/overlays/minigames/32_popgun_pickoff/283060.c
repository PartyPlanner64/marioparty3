#include "common.h"
#include "overlays/minigame.h"
#include "game/hmfmath.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"
#include "game/texload.h"

#define PLAYER_WORK(obj) ((PopgunPickoffPlayerWork *)((func_800E1BA8_minigame_ObjData *)(obj)->data)->unk158)

#define POPGUN_CC_PRIM_DECALA 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0
#define POPGUN_CC_PRIM_MODULATEA 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0
#define POPGUN_CC_BLEND_DECALA 1, PRIMITIVE, TEXEL0, PRIMITIVE, 0, 0, 0, TEXEL0
#define POPGUN_CC_BLEND_MODULATEA 1, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0
#define POPGUN_CC_MODULATEI_PRIMA TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0
#define POPGUN_CC_MODULATEI_PASSA2 COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED

typedef struct PopgunPickoffPlayer {
    /* 0x00 */ Gfx *displayList;
    /* 0x04 */ Vtx_t *vtx;
    /* 0x08 */ HuSprAnimData *sprite;
    /* 0x0C */ struct PopgunPickoffPlayer *prev;
    /* 0x10 */ struct PopgunPickoffPlayer *next;
    /* 0x14 */ void (*callback)(struct PopgunPickoffPlayer *);
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
} PopgunPickoffPlayer; // Size 0x68

typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ s16 screenX;
    /* 0x12 */ s16 screenY;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 playerId;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ char unk1D[3];
} PopgunPickoffTarget; // Size 0x20

typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec vel;
    /* 0x18 */ u8 target;
    /* 0x19 */ u8 active;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 playerId;
    /* 0x1D */ char unk1D[3];
} PopgunPickoffShot; // Size 0x20

typedef struct {
    u16 rgb[8][3];
} PopgunPickoffCharColors;

typedef struct {
    u8 values[8];
} PopgunPickoffCharMotions;

// Per-player work allocated in func_801080DC_popgun_pickoff, stored at ObjData->unk158
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
    /* 0x29 */ u8 unk29; // Character
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ u8 unk2C;
    /* 0x2D */ u8 unk2D;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 unk2F;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ u8 unk32;
    /* 0x33 */ u8 unk33;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ char unk36[0x1E];
} PopgunPickoffPlayerWork; // Size 0x54

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02[2];
} PopgunPickoffBssCC20; // Size 0x6

extern HuSprAnimData *D_800C9530_main[];
extern s32 D_800A178C_main[][6];

s32 D_8010C590_popgun_pickoff = 0;
u16 D_8010C594_popgun_pickoff = 0;
s32 D_8010C598_popgun_pickoff = -1;
s32 D_8010C59C_popgun_pickoff = 25;
s16 D_8010C5A0_popgun_pickoff = 0;
s16 D_8010C5A2_popgun_pickoff = 1;
s16 D_8010C5A4_popgun_pickoff = 0;
s16 D_8010C5A8_popgun_pickoff[4] = { 0, 1, 2, 3 }; /* Unreferenced. */
u8 D_8010C5B0_popgun_pickoff = 0;
s32 D_8010C5B4_popgun_pickoff = 0; /* Unreferenced. */
s16 D_8010C5B8_popgun_pickoff[4][3] = {
    { -140, 20, 0 },
    { 140, 20, 0 },
    { 85, -75, -200 },
    { 85, 75, -200 }
};
f32 D_8010C5D0_popgun_pickoff[4] = { 180.0f, 180.0f, -45.0f, -135.0f };
s16 D_8010C5E0_popgun_pickoff[3] = { -20, -10, 0 };
s16 D_8010C5E8_popgun_pickoff[2][3] = {
    { 0, -20, -30 },
    { 30, 20, 0 }
};
u32 D_8010C5F4_popgun_pickoff = 0x41C64E6D;
s32 D_8010C5F8_popgun_pickoff[] = { 4, 3, 2, 1 };
s16 D_8010C608_popgun_pickoff[] = {
    0, 512, 256, 170, 128, 102, 85, 73, 64, 56, 51, 20, 42, 26, 14, 19,
    32, 13, 28, 26, 8, 9, 4, 4, 5, 20, 13, 18, 3, 6, 3, 2,
    16, 2, 2, 3, 14, 2, 13, 2, 1, 12, 4, 2, 2, 2, 2, 2,
    2, 4, 10, 0, 1, 2, 9, 0, 1, 8, 0, 2, 0, 1, 0, 1,
    8, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 0, 6, 0, 0, 4,
    0, 0, 6, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 4, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0,
    0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0
};
s16 D_8010C740_popgun_pickoff[] = {
    0, 512, 256, 170, 128, 102, 85, 73, 64, 56, 51, 46, 42, 39, 36, 34,
    32, 30, 28, 26, 25, 24, 23, 22, 21, 20, 19, 19, 18, 18, 17, 17,
    16, 16, 15, 15, 14, 14, 13, 13, 13, 12, 12, 12, 11, 11, 11, 10,
    10, 10, 10, 10, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8,
    8, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0
};
s16 D_8010C878_popgun_pickoff[] = { G_CD_DISABLE, G_CD_NOISE, G_CD_BAYER, G_CD_MAGICSQ };
s16 D_8010C880_popgun_pickoff[] = { G_TF_POINT, G_TF_POINT, G_TF_BILERP, G_TF_AVERAGE };
s16 D_8010C888_popgun_pickoff[] = { G_AC_THRESHOLD, G_AC_NONE, G_AC_DITHER, G_AC_NONE };
s32 D_8010C890_popgun_pickoff = 0;

s16 D_8010CBD0_popgun_pickoff[16] BSS;
s16 D_8010CBF0_popgun_pickoff[8] BSS;
s16 D_8010CC00_popgun_pickoff[16] BSS;
PopgunPickoffBssCC20 popgunPickoffBssCC20 BSS;
PopgunPickoffTarget D_8010CC28_popgun_pickoff[9] BSS;
u8 D_8010CD48_popgun_pickoff[8] BSS; /* Unreferenced. */
PopgunPickoffShot D_8010CD50_popgun_pickoff[128] BSS;
f32 D_8010DD50_popgun_pickoff[4][4] BSS;
f32 D_8010DD90_popgun_pickoff[4][4] BSS;
f32 D_8010DDD0_popgun_pickoff BSS;
u8 D_8010DDD4_popgun_pickoff BSS;
PopgunPickoffPlayer *D_8010DDD8_popgun_pickoff BSS;
void *D_8010DDDC_popgun_pickoff[3] BSS;
void *D_8010DDE8_popgun_pickoff BSS;
s32 D_8010DDEC_popgun_pickoff BSS;
s32 D_8010DDF0_popgun_pickoff BSS;
u8 D_8010DDF4_popgun_pickoff[0xC] BSS;             /* Unreferenced. */
PopgunPickoffPlayer D_8010DE00_popgun_pickoff BSS; // List head of opaque entries
PopgunPickoffPlayer D_8010DE68_popgun_pickoff BSS; // List head of translucent entries
u8 D_8010DED0_popgun_pickoff[0x10] BSS;            /* Unreferenced. */

/* Fields of popgunPickoffBssCC20, aliased in undefined_syms.txt. */
extern s16 D_8010CC20_popgun_pickoff;
extern s16 D_8010CC22_popgun_pickoff[2];

void func_80105AFC_popgun_pickoff(omObjData *object);
s32 func_80108E1C_popgun_pickoff(void);
f32 func_80108E74_popgun_pickoff(f32 y, f32 x);
f32 func_80108EF4_popgun_pickoff(Vec *arg0, Vec *arg1);
u8 func_801068D0_popgun_pickoff(s16 x, s16 y);
void func_8010AEAC_popgun_pickoff(s16 playerId, s32 value);
void func_8010AEF0_popgun_pickoff(s16 playerId, s32 value);
void func_8010B120_popgun_pickoff(s16 playerId);
void func_80105BF8_popgun_pickoff(HuMtx4F mtx, f32 x, f32 y, f32 z, f32 *dst);
void func_80105C78_popgun_pickoff(HuMtx4F src, HuMtx4F dst);
void func_80106068_popgun_pickoff(void);
void func_801060E8_popgun_pickoff(omObjData *object);
void func_80106A44_popgun_pickoff(omObjData *object);
void func_8010704C_popgun_pickoff(omObjData *object);
void func_80107A54_popgun_pickoff(void);
void func_80107B20_popgun_pickoff(omObjData *object);
void func_801080DC_popgun_pickoff(omObjData *object, s32 arg1, s32 arg2, u16 player, u16 tag);
void func_80108398_popgun_pickoff(omObjData *object);
u16 func_8010880C_popgun_pickoff(omObjData *object);
u8 func_80108A78_popgun_pickoff(omObjData *object, s32 targetIndex);
void func_80108FE4_popgun_pickoff(s16 model, char *hook, s16 time, Vec *pos);
s16 func_80109108_popgun_pickoff(s32 dataNum);
s16 func_80109150_popgun_pickoff(s16 spriteId, s16 count);
HuSprAnimPat *func_80109218_popgun_pickoff(s16 groupId, s16 member);
s16 func_80109718_popgun_pickoff(PopgunPickoffPlayer *player);
void func_80108F5C_popgun_pickoff(Vec *dir, f32 *rot);
void func_8010B64C_popgun_pickoff(void);
void func_8010B7A0_popgun_pickoff(HuCamera *camera, HuMtx4F lookAt);
Gfx *func_8010BC6C_popgun_pickoff(Gfx *gfx, PopgunPickoffPlayer *player, HuMtx4F lookAt, Vec *rot);
void func_8010C32C_popgun_pickoff(void);
s16 func_8010A024_popgun_pickoff(s16 spriteId, s32 flags);
void func_8010ACB4_popgun_pickoff(s16 playerId, f32 x, f32 y, f32 z);
void func_8010AD54_popgun_pickoff(s16 playerId, f32 x, f32 y, f32 z);
void func_8010AC34_popgun_pickoff(s16 playerId, s16 value);
void func_8010AE0C_popgun_pickoff(s16 playerId, f32 x, f32 y, f32 z);
void func_8010AE5C_popgun_pickoff(s16 playerId, f32 x, f32 y, f32 z);
void func_8010AF78_popgun_pickoff(s16 playerId, s8 value);
void func_8010B0D4_popgun_pickoff(s16 playerId, s8 value1, s8 value2, s8 value3, s16 value4);
void func_8010BA44_popgun_pickoff(Gfx **gfxP, s32 arg1, s32 arg2);
void func_8010C4EC_popgun_pickoff(void);
void func_80109260_popgun_pickoff(u16 count);

void func_801059A0_popgun_pickoff(void) {
    omObjData *obj;
    u8 camIndex;

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
    func_80105AFC_popgun_pickoff(obj);
    func_80106068_popgun_pickoff();
    func_80109260_popgun_pickoff(0x80);
    func_80107A54_popgun_pickoff();
    Hu3DBGColorSet(180, 180, 180);
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
}

void func_80105AFC_popgun_pickoff(omObjData *object) {
    HuCamera *camera;
    f32 sinFov;
    f32 cosFov;

    CZoom = 500.0f;
    CRot.x = 5.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 250.0f;
    Center.z = 0.0f;
    omOutView(object);

    camera = gCameraList;
    sinFov = sindf(camera->fov / 2.0);
    cosFov = cosdf(camera->fov / 2.0);
    D_8010DDD0_popgun_pickoff = sinFov / cosFov;
    guMtxL2F(D_8010DD50_popgun_pickoff, &camera->mtxs[0].lookAtMtx);
    guMtxL2F(D_8010DD90_popgun_pickoff, &camera->mtxs[0].lookAtMtx);
    func_80105C78_popgun_pickoff(D_8010DD90_popgun_pickoff, D_8010DD90_popgun_pickoff);
}

void func_80105BF8_popgun_pickoff(HuMtx4F mtx, f32 x, f32 y, f32 z, f32 *dst) {
    dst[0] = ((x * mtx[0][0]) + (y * mtx[1][0])) + (z * mtx[2][0]);
    dst[1] = ((x * mtx[0][1]) + (y * mtx[1][1])) + (z * mtx[2][1]);
    dst[2] = ((x * mtx[0][2]) + (y * mtx[1][2])) + (z * mtx[2][2]);
}

void func_80105C78_popgun_pickoff(HuMtx4F src, HuMtx4F dst) {
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

        func_80105BF8_popgun_pickoff(dst, -mtx[3][0], -mtx[3][1], -mtx[3][2], dstRow3);
    }
}

void func_80105E68_popgun_pickoff(f32 *pos, f32 *dst) {
    f32 mtx[4][4];
    f32 depth;
    f32 scale;

    guTranslateF(mtx, pos[0], pos[1], pos[2]);
    guMtxCatF(mtx, D_8010DD50_popgun_pickoff, mtx);
    depth = mtx[3][2] * D_8010DDD0_popgun_pickoff;
    scale = fabsf(depth);
    if (scale != 0.0) {
        dst[0] = mtx[3][0] * 160.0f / scale / 1.3333333333333333;
        dst[1] = -mtx[3][1] * 120.0f / scale;
    }
    dst[0] += 160.0;
    dst[1] += 120.0;
    dst[2] = scale;
}

void func_80105F74_popgun_pickoff(f32 x, f32 y, f32 z, f32 *dst) {
    f32 depth = z + D_8010DD50_popgun_pickoff[3][2];
    f32 scale = fabsf(depth * D_8010DDD0_popgun_pickoff);
    f32 mtx[4][4];

    x -= 160.0;
    y -= 120.0;
    guTranslateF(mtx, (x + x) * scale * 1.3333333333333333 / 320.0, -((y + y) * scale / 240.0f), depth);
    guMtxCatF(mtx, D_8010DD90_popgun_pickoff, mtx);
    dst[0] = mtx[3][0];
    dst[1] = mtx[3][1];
    dst[2] = mtx[3][2];
}

void func_80106068_popgun_pickoff(void) {
    D_800EBE28_minigame = 0;
    func_800E1490_minigame(0);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(5, 10, 0, -1, func_801060E8_popgun_pickoff);
    D_8010CC20_popgun_pickoff = 0;
    D_8010CC22_popgun_pickoff[0] = D_8010CC22_popgun_pickoff[1] = 0;
}

void func_801060E8_popgun_pickoff(omObjData *object) {
    f32 positions[9][2] = {
        { 115.0f, 93.0f },
        { 160.0f, 93.0f },
        { 204.0f, 93.0f },
        { 115.0f, 128.0f },
        { 160.0f, 128.0f },
        { 204.5f, 128.0f },
        { 114.0f, 163.0f },
        { 159.5f, 163.0f },
        { 205.0f, 163.0f },
    };
    u16 characterSprites[8] = { 8, 9, 10, 11, 12, 13, 14, 15 };
    f32 pos[3];
    f32 screen[3];
    HuSprAnimPat *spr;
    PopgunPickoffTarget *target;
    PopgunPickoffShot *shot;
    s32 attr;
    s32 i;

    D_8010CBD0_popgun_pickoff[0] = func_80109108_popgun_pickoff(0x530000);
    D_8010CBF0_popgun_pickoff[0] = func_80109150_popgun_pickoff(D_8010CBD0_popgun_pickoff[0], 1);
    HuSprPosSet(D_8010CBF0_popgun_pickoff[0], 0, 160, 120);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[0], 0, 0x4000);
    D_8010CBD0_popgun_pickoff[1] = func_80109108_popgun_pickoff(0x530001);
    spr = func_80109218_popgun_pickoff(D_8010CBD0_popgun_pickoff[1], 0);
    D_8010CBF0_popgun_pickoff[1] = func_8010A024_popgun_pickoff(D_8010CBD0_popgun_pickoff[1], 0x1808);
    func_8010AD54_popgun_pickoff(D_8010CBF0_popgun_pickoff[1], 0.0f, -70.0f, -400.0f);
    func_8010AE0C_popgun_pickoff(D_8010CBF0_popgun_pickoff[1], 3.0f, 3.0f, 1.0f);
    func_8010ACB4_popgun_pickoff(D_8010CBF0_popgun_pickoff[1], spr->sizeX * 0.5, spr->sizeY, 0.0f);
    func_8010AF78_popgun_pickoff(D_8010CBF0_popgun_pickoff[1], 0);
    D_8010CBD0_popgun_pickoff[4] = func_80109108_popgun_pickoff(0x530004);
    D_8010CBD0_popgun_pickoff[5] = func_80109108_popgun_pickoff(0x530005);
    for (i = 0; i < 9; i++) {
        target = &D_8010CC28_popgun_pickoff[i];
        pos[0] = target->pos.x = (positions[i][0] - spr->sizeX * 0.5) * 3.0;
        pos[1] = target->pos.y = (spr->sizeY - positions[i][1]) * 3.0 + -70.0;
        pos[2] = target->pos.z = -400.0f;
        func_80105E68_popgun_pickoff(pos, screen);
        target->screenX = screen[0];
        target->screenY = screen[1];
        target->unk0C = -90.0f;
        target->unk14 = -1;
        target->unk16 = 0;
        target->unk1B = 0;
        target->playerId = func_8010A024_popgun_pickoff(D_8010CBD0_popgun_pickoff[4], 0x12009808);
        func_8010ACB4_popgun_pickoff(target->playerId, 16.0f, 32.0f, 0.0f);
        func_8010AD54_popgun_pickoff(target->playerId, target->pos.x, target->pos.y - 42.0, target->pos.z - 10.0);
        func_8010AE0C_popgun_pickoff(target->playerId, 3.0f, 3.0f, 1.0f);
        func_8010AE5C_popgun_pickoff(target->playerId, 90.0f, 0.0f, 0.0f);
        func_8010AF78_popgun_pickoff(target->playerId, 0);
        func_8010B0D4_popgun_pickoff(target->playerId, 0, 0, 0, 0x100);
    }
    for (i = 0; i < 0x80; i++) {
        shot = &D_8010CD50_popgun_pickoff[i];
        shot->active = 0;
    }
    attr = 0x2D9;
    for (i = 0; i < 9; i++) {
        if (i == 0) {
            object->model[i] = func_8000B108_main(0x530009, attr);
            object->trans.x = D_8010CC28_popgun_pickoff[i].pos.x;
            object->trans.y = D_8010CC28_popgun_pickoff[i].pos.y;
            object->trans.z = D_8010CC28_popgun_pickoff[i].pos.z + 10.0;
            object->scale.x = object->scale.z = 0.66f;
            object->scale.y = 0.63f;
        } else {
            object->model[i] = Hu3DModelLink(object->model[0]);
            Hu3DModelPosSet(object->model[i], D_8010CC28_popgun_pickoff[i].pos.x, D_8010CC28_popgun_pickoff[i].pos.y,
                            D_8010CC28_popgun_pickoff[i].pos.z + 10.0);
        }
        Hu3DModelScaleSet(object->model[i], object->scale.x, object->scale.y, object->scale.z);
        Hu3DMotionSpeedSet(object->model[i], 0.0f);
    }
    D_8010CBD0_popgun_pickoff[6] = func_80109108_popgun_pickoff(0x530007);
    D_8010CBF0_popgun_pickoff[2] = func_80109150_popgun_pickoff(D_8010CBD0_popgun_pickoff[6], 2);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[2], 0, 0x1000);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[2], 1, 0x1000);
    func_80055484_main(D_8010CBF0_popgun_pickoff[2], 0, 0, 0, 0, 0xC2);
    func_80055484_main(D_8010CBF0_popgun_pickoff[2], 1, 0, 0, 0, 0xC2);
    HuSprPosSet(D_8010CBF0_popgun_pickoff[2], 0, 60, 48);
    HuSprPosSet(D_8010CBF0_popgun_pickoff[2], 1, 260, 48);
    D_8010CBD0_popgun_pickoff[11] =
        func_80109108_popgun_pickoff(characterSprites[PLAYER_WORK(D_800EC598_minigame[0])->unk29] | 0x210000);
    D_8010CBD0_popgun_pickoff[12] =
        func_80109108_popgun_pickoff(characterSprites[PLAYER_WORK(D_800EC598_minigame[1])->unk29] | 0x210000);
    D_8010CBF0_popgun_pickoff[6] = func_80109150_popgun_pickoff(D_8010CBD0_popgun_pickoff[11], 2);
    HuSprGrpMemberSet(D_8010CBF0_popgun_pickoff[6], 1, D_8010CBD0_popgun_pickoff[12], 0);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[6], 0, 0x1000);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[6], 1, 0x1000);
    HuSprPosSet(D_8010CBF0_popgun_pickoff[6], 0, 36, 48);
    HuSprPosSet(D_8010CBF0_popgun_pickoff[6], 1, 236, 48);
    D_8010CBD0_popgun_pickoff[8] = func_80109108_popgun_pickoff(0x2D);
    D_8010CBD0_popgun_pickoff[9] = func_80109108_popgun_pickoff(0x2F);
    D_8010CBF0_popgun_pickoff[4] = func_80109150_popgun_pickoff(D_8010CBD0_popgun_pickoff[8], 6);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[4], 0, 0x1000);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[4], 1, 0x1000);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[4], 2, 0x1000);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[4], 3, 0x1000);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[4], 4, 0x1000);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[4], 5, 0x1000);
    HuSprPosSet(D_8010CBF0_popgun_pickoff[4], 0, 80, 48);
    HuSprPosSet(D_8010CBF0_popgun_pickoff[4], 1, 67, 48);
    HuSprPosSet(D_8010CBF0_popgun_pickoff[4], 2, 53, 48);
    HuSprPosSet(D_8010CBF0_popgun_pickoff[4], 3, 280, 48);
    HuSprPosSet(D_8010CBF0_popgun_pickoff[4], 4, 267, 48);
    HuSprPosSet(D_8010CBF0_popgun_pickoff[4], 5, 253, 48);
    object->func = func_80106A44_popgun_pickoff;
}

u8 func_801068D0_popgun_pickoff(s16 x, s16 y) {
    u8 group = HuSprGrpCreate(3, 2);

    HuSprGrpMemberSet(group, 0, D_8010CBD0_popgun_pickoff[8], 0);
    HuSprGrpMemberSet(group, 1, D_8010CBD0_popgun_pickoff[8], 0);
    HuSprGrpMemberSet(group, 2, D_8010CBD0_popgun_pickoff[9], 0);
    HuSprAttrSet(group, 0, 0x1000);
    HuSprAttrSet(group, 1, 0x1000);
    HuSprAttrSet(group, 2, 0x1000);
    HuSprAnimModeSet(group, 0, HUSPR_ANIM_MODE_STOP);
    HuSprAnimModeSet(group, 1, HUSPR_ANIM_MODE_STOP);
    HuSprAnimModeSet(group, 2, HUSPR_ANIM_MODE_STOP);
    HuSprPosSet(group, 0, x, y);
    HuSprPosSet(group, 1, 12, 0);
    HuSprPosSet(group, 2, -12, 0);
    func_80054FF8_main(group, 0, 1);
    func_80054FF8_main(group, 1, 0);
    func_80054FF8_main(group, 2, 4);
    return group;
}

void func_80106A44_popgun_pickoff(omObjData *object) {
    s32 i;

    switch (D_8010CC20_popgun_pickoff) {
        case 0:
            Hu3DHookFuncCreate(0xC0, func_8010BA44_popgun_pickoff, 2);
            GMesCreate(6);
            D_8010C594_popgun_pickoff = 900;
            D_8010CC20_popgun_pickoff++;
        case 1:
            if (WipeStatGet() == 0 && ++D_8010C5A0_popgun_pickoff == 1) {
                HuAudSeqPlay(0x36);
            }
            if (GMesStatGet() == 0) {
                D_8010CC20_popgun_pickoff++;
                GMesCreate(0x1A, (D_8010C594_popgun_pickoff + 29) / 30, 0xA0, 0x20);
                HuAudFXPlay(0xE);
            }
            break;
        case 2:
            D_8010C594_popgun_pickoff--;
            func_8003F578_main((D_8010C594_popgun_pickoff + 29) / 30);
            if (D_8010C594_popgun_pickoff == 0) {
                D_8010CC20_popgun_pickoff = 3;
                func_8003F5C0_main();
                GMesCreate(0x11);
                HuAudSeqFadeOut(0x78);
            }
            break;
        case 3:
            if (D_8010C59C_popgun_pickoff != 0) {
                D_8010C59C_popgun_pickoff--;
                Center.y -= 2.9;
                HuSprPosSet(D_8010CBF0_popgun_pickoff[0], 0, 160, D_8010C59C_popgun_pickoff + 95);
                break;
            }
            if (D_8010DDD4_popgun_pickoff != 0) {
                break;
            }
            if (D_8010CC22_popgun_pickoff[0] > D_8010CC22_popgun_pickoff[1]) {
                D_8010C598_popgun_pickoff = 0;
                PLAYER_WORK(D_800EC598_minigame[0])->unk2C = 1;
                PLAYER_WORK(D_800EC598_minigame[1])->unk2C = 0;
            } else if (D_8010CC22_popgun_pickoff[0] < D_8010CC22_popgun_pickoff[1]) {
                D_8010C598_popgun_pickoff = 1;
                PLAYER_WORK(D_800EC598_minigame[0])->unk2C = 0;
                PLAYER_WORK(D_800EC598_minigame[1])->unk2C = 1;
            } else {
                D_8010C598_popgun_pickoff = -1;
                PLAYER_WORK(D_800EC598_minigame[0])->unk2C = PLAYER_WORK(D_800EC598_minigame[1])->unk2C = 0;
            }
            D_8010C590_popgun_pickoff = 15;
            D_8010CC20_popgun_pickoff++;
            break;
        case 4:
            if (GMesStatGet() != 0) {
                break;
            }
            if (--D_8010C590_popgun_pickoff == 0) {
                if (D_8010C598_popgun_pickoff == -1) {
                    GMesCreate(0x20);
                    HuAudSeqPlay(0x6C);
                } else {
                    GMesCreate(0x16, PLAYER_WORK(D_800EC598_minigame[D_8010C598_popgun_pickoff])->unk29);
                    HuAudSeqPlay(0x67);
                }
                D_8010C590_popgun_pickoff = 15;
                D_8010CC20_popgun_pickoff++;
            }
            break;
        case 5:
            if (GMesStatGet() != 0) {
                break;
            }
            if (--D_8010C590_popgun_pickoff == 0) {
                D_8010CC20_popgun_pickoff++;
            }
            break;
        case 6:
            if (D_8010C590_popgun_pickoff != 0) {
                if (--D_8010C590_popgun_pickoff == 0) {
                    D_8010CC20_popgun_pickoff++;
                }
            } else {
                D_8010C590_popgun_pickoff = 16;
                WipeCreateOut(WIPE_TYPE_NORMAL, D_8010C590_popgun_pickoff);
                HuAudSeqFadeOut(D_8010C590_popgun_pickoff);
                func_8004AB0C_main((s16)D_8010C590_popgun_pickoff);
            }
            break;
        case 7:
            HuAudSeqStop();
            omOvlReturnEx(1);
            func_8010C4EC_popgun_pickoff();
            break;
    }
    func_8010704C_popgun_pickoff(object);
    for (i = 0; i < 2; i++) {
        HuSprAttrReset(D_8010CBF0_popgun_pickoff[4], i * 3 + 1, 0x8000);
        HuSprAttrReset(D_8010CBF0_popgun_pickoff[4], i * 3 + 2, 0x8000);
        func_80054FF8_main(D_8010CBF0_popgun_pickoff[4], i * 3, D_8010CC22_popgun_pickoff[i] % 10);
        func_80054FF8_main(D_8010CBF0_popgun_pickoff[4], i * 3 + 1, D_8010CC22_popgun_pickoff[i] / 10 % 10);
        func_80054FF8_main(D_8010CBF0_popgun_pickoff[4], i * 3 + 2, D_8010CC22_popgun_pickoff[i] / 100);
    }
    if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010CC20_popgun_pickoff = 6;
    }
}

void func_8010704C_popgun_pickoff(omObjData *object) {
    PopgunPickoffShot *shot;
    PopgunPickoffTarget *target;
    s16 effect;
    f32 scale;
    s32 count;
    s32 index;
    s32 i;

    D_8010DDD4_popgun_pickoff = 0;
    for (i = 0; i < 0x80; i++) {
        shot = &D_8010CD50_popgun_pickoff[i];
        switch (shot->active) {
            case 0:
                continue;
            case 1:
                target = &D_8010CC28_popgun_pickoff[shot->target];
                if (func_80108EF4_popgun_pickoff(&target->pos, &shot->pos) <= 48.0) {
                    shot->pos.x = target->pos.x;
                    shot->pos.y = target->pos.y;
                    shot->pos.z = target->pos.z + 40.0;
                    shot->vel.x = shot->vel.x * 0.2 +
                                  (f32)(func_80108E1C_popgun_pickoff() - 0x8000) * 3.0517578125e-05 * (shot->vel.x * 0.2);
                    shot->vel.y = (f32)func_80108E1C_popgun_pickoff() * 1.52587890625e-05 * 6.0 + 15.0;
                    shot->vel.z = -shot->vel.z * 0.1 -
                                  (f32)func_80108E1C_popgun_pickoff() * 1.52587890625e-05 * (shot->vel.z * 0.05);
                    shot->unk1B = 120;
                    shot->active++;
                    if (target->unk1B == 2) {
                        target->unk0C = -50.0f;
                        func_8010AC34_popgun_pickoff(target->playerId, target->unk1A * 2 + 1);
                        if (target->unk1A == 0) {
                            func_8010B0D4_popgun_pickoff(target->playerId, -1, -1, -1, 0x100);
                            if (target->unk16 != 0) {
                                target->unk16--;
                            }
                            D_8010CC22_popgun_pickoff[shot->unk1A]++;
                            effect = func_8010A024_popgun_pickoff(D_8010CBD0_popgun_pickoff[10], 0x60001808);
                            func_8010AD54_popgun_pickoff(effect, target->pos.x, target->pos.y, target->pos.z + 20.0f);
                            func_8010B0D4_popgun_pickoff(target->playerId, -1, -1, -1, 0xC6);
                            func_8010AE0C_popgun_pickoff(effect, 2.0f, 2.0f, 1.0f);
                            HuAudFXPlay(0x497);
                        } else {
                            if (D_8010CC22_popgun_pickoff[shot->unk1A] > 10) {
                                D_8010CC22_popgun_pickoff[shot->unk1A] -= 10;
                            } else {
                                D_8010CC22_popgun_pickoff[shot->unk1A] = 0;
                            }
                            target->unk14 = func_801068D0_popgun_pickoff(target->screenX, target->screenY);
                            func_8010B0D4_popgun_pickoff(target->playerId, -1, 0, 0, 0x100);
                            HuAudFXPlay(0x498);
                            omVibrate(PLAYER_WORK(D_800EC598_minigame[shot->unk1A])->unk28, 10, 0, 10);
                            target->unk16 = 0;
                            target->unk1B++;
                        }
                    }
                }
                D_8010DDD4_popgun_pickoff++;
                break;
            case 2:
                if (--shot->unk1B == 0) {
                    shot->active++;
                }
                break;
            case 3:
                shot->active = 0;
                func_8010B120_popgun_pickoff(shot->playerId);
                shot->playerId = 0xFF;
                continue;
        }
        shot->vel.y += -2.0f;
        shot->pos.x += shot->vel.x;
        shot->pos.y += shot->vel.y;
        shot->pos.z += shot->vel.z;
        func_8010AD54_popgun_pickoff(shot->playerId, shot->pos.x, shot->pos.y, shot->pos.z);
        scale = 1.5 - shot->pos.z / -400.0f;
        func_8010AE0C_popgun_pickoff(shot->playerId, scale, scale, 1.0f);
    }
    for (i = 0; i < 9; i++) {
        target = &D_8010CC28_popgun_pickoff[i];
        switch (target->unk1B) {
            case 0:
                break;
            case 1:
                func_8010AEF0_popgun_pickoff(target->playerId, 0x8000);
                target->unk1B++;
                break;
            case 2:
                target->unk0C += 15.0;
                if (target->unk0C > 0.0) {
                    target->unk0C = 0.0f;
                    func_8010AC34_popgun_pickoff(target->playerId, target->unk1A * 2);
                } else if (target->unk0C > -30.0) {
                    func_8010B0D4_popgun_pickoff(target->playerId, 0, 0, 0, 0x100);
                }
                if ((--target->unk1C == 0) | (target->unk16 == 0)) {
                    target->unk1B++;
                }
                break;
            case 3:
                func_8010B0D4_popgun_pickoff(target->playerId, 0, 0, 0, 0x100);
                if (target->unk0C <= -90.0) {
                    func_8010AEAC_popgun_pickoff(target->playerId, 0x8000);
                } else {
                    target->unk0C -= 10.0;
                }
                if (target->unk1C-- != 0) {
                    break;
                }
                Hu3DMotionTimeSet(object->model[i], 4.2f);
                Hu3DMotionSpeedSet(object->model[i], -0.2f);
                target->unk1C = 9;
                target->unk1B++;
            case 4:
                if (target->unk0C <= -90.0) {
                    func_8010AEAC_popgun_pickoff(target->playerId, 0x8000);
                } else {
                    target->unk0C -= 10.0;
                }
                if (--target->unk1C == 0) {
                    Hu3DMotionSpeedSet(object->model[i], 0.0f);
                    Hu3DMotionTimeSet(object->model[i], 0.0f);
                    target->unk1B = 0;
                }
                break;
        }
        if (target->unk14 != -1) {
            if (target->unk0C > -90.0) {
                scale = 1.0 - target->unk0C * 0.005;
                HuSprScaleSet(target->unk14, 0, scale, scale);
                HuSprScaleSet(target->unk14, 1, scale, scale);
                HuSprScaleSet(target->unk14, 2, scale, scale);
            } else if (target->unk0C > -180.0) {
                target->unk0C -= 15.0;
                scale = (target->unk0C + 180.0) * 0.005 + 1.0;
                HuSprScaleSet(target->unk14, 0, scale, scale);
                HuSprScaleSet(target->unk14, 1, scale, scale);
                HuSprScaleSet(target->unk14, 2, scale, scale);
            } else {
                HuSprGrpKill(target->unk14);
                target->unk0C = 0.0f;
                target->unk14 = -1;
            }
        }
        func_8010AE5C_popgun_pickoff(target->playerId, target->unk0C, 0.0f, 0.0f);
    }
    if (D_8010CC20_popgun_pickoff == 2 && --D_8010C5A2_popgun_pickoff == 0) {
        D_8010C5A2_popgun_pickoff = 120;
        count = ++D_8010C5A4_popgun_pickoff / 2 + 2;
        if (count >= 9) {
            count = 9;
        }
        for (i = 0; i < count;) {
            index = (f32)func_80108E1C_popgun_pickoff() * 1.52587890625e-05 * 8.0;
            target = &D_8010CC28_popgun_pickoff[index];
            if (target->unk1B == 0) {
                target->unk1C = (s32)((f32)func_80108E1C_popgun_pickoff() * 1.52587890625e-05 * 20.0) + 60;
                target->unk16 = 10;
                target->unk1B = 1;
                target->unk0C = -90.0f;
                target->unk14 = -1;
                if (i != 0) {
                    target->unk1A = func_80108E1C_popgun_pickoff() & 1;
                } else {
                    target->unk1A = 0;
                }
                func_8010AC34_popgun_pickoff(target->playerId, target->unk1A * 2);
                Hu3DMotionSpeedSet(object->model[index], 1.0f);
                i++;
                HuAudFXPlay(0x499);
            }
        }
    }
}

void func_80107A54_popgun_pickoff(void) {
    s32 i;

    func_800E18D8_minigame();
    D_8010CBD0_popgun_pickoff[2] = func_80109108_popgun_pickoff(0x530002);
    D_8010CBD0_popgun_pickoff[3] = func_80109108_popgun_pickoff(0x530003);
    D_8010CBD0_popgun_pickoff[10] = func_80109108_popgun_pickoff(0x530006);
    D_800EC280_minigame = 0;
    for (i = 0; i < 2; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 0xB, 0x32, -1, func_80107B20_popgun_pickoff);
    }
}

const PopgunPickoffCharColors D_8010CA78_popgun_pickoff = { {
    { 0xFF, 0x00, 0x00 },
    { 0x00, 0x40, 0xFF },
    { 0xFF, 0x80, 0xFF },
    { 0x00, 0xFF, 0x00 },
    { 0x80, 0x00, 0xFF },
    { 0xFF, 0x80, 0x80 },
    { 0x80, 0x80, 0x80 },
    { 0xFF, 0xFF, 0x00 },
} };

const PopgunPickoffCharMotions D_8010CAA8_popgun_pickoff = { { 0, 1, 2, 3, 4, 5, 6, 7 } };

void func_80107B20_popgun_pickoff(omObjData *object) {
    PopgunPickoffCharColors colors = D_8010CA78_popgun_pickoff;
    PopgunPickoffCharMotions motions = D_8010CAA8_popgun_pickoff;
    s32 anims[3][8] = {
        { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C },
        { 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0x1D },
        { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B },
    };
    func_800E1BA8_minigame_ObjData *data;
    PopgunPickoffPlayerWork *work;
    s32 i;
    u8 player;
    s8 character;
    s32 model;
    s32 linkModel;

    for (i = 0; i < 4; i++) {
        if (D_8010C5B0_popgun_pickoff == GwPlayer[i].group) {
            break;
        }
    }
    player = i;
    character = GwPlayer[player].chr;
    model = D_800A178C_main[character][0];
    linkModel = D_800A178C_main[character][2];
    func_800E19F0_minigame(1);
    func_801080DC_popgun_pickoff(object, model, linkModel, player, 0x2C9);
    data = object->data;
    object->trans.x = D_8010C5B8_popgun_pickoff[D_8010C5B0_popgun_pickoff][0];
    object->trans.y = D_8010C5B8_popgun_pickoff[D_8010C5B0_popgun_pickoff][1];
    object->trans.z = D_8010C5B8_popgun_pickoff[D_8010C5B0_popgun_pickoff][2];
    object->rot.y = D_8010C5D0_popgun_pickoff[D_8010C5B0_popgun_pickoff];
    data->unk3C = object->rot.y + 180.0;
    object->scale.x = object->scale.y = object->scale.z = data->unkAC;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y - 5.0, object->trans.z);
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);
    work = data->unk158;
    work->unk28 = i;
    work->unk29 = character;
    work->unk2A = D_8010C5B0_popgun_pickoff;
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
    work->unk2F = func_80109150_popgun_pickoff(D_8010CBD0_popgun_pickoff[2], 1);
    HuSprAttrSet(work->unk2F, 0, 0x9008);
    func_80055484_main(work->unk2F, 0, colors.rgb[character][0], colors.rgb[character][1],
                       colors.rgb[character][2], 0x100);
    work->unk33 = func_80017790_main(object->model[0], 2, motions.values[character], model | anims[2][character]);
    work->unk31 = func_80017AD8_main(model | anims[0][character]);
    work->unk32 = func_80017AD8_main(model | anims[1][character]);
    func_8001C514_main(object->model[0]);
    if (D_8010C5B0_popgun_pickoff == 0) {
        object->model[2] = func_8000B108_main(0x530008, 0x2C9);
    } else {
        object->model[2] = func_8000B108_main(0x530008, 0x2C9);
        HuSprZRotSet(work->unk2F, 0, 45.0f);
    }
    Hu3DModelHookSet(object->model[2], object->model[0], "item_hook");
    func_8001C258_main(object->model[2], 0x4000, 0x4000);
    object->func = func_80108398_popgun_pickoff;
    func_800E5A00_minigame(object, 0, func_80017BB8_main(character, 0x4B), 1, 0);
    func_800E5A00_minigame(object, 0x26, func_80017BB8_main(character, 0x4C), 2, 0);
    func_800E5A00_minigame(object, 0x27, func_80017BB8_main(character, 0x4D), 0, 0);
    func_800E5A00_minigame(object, 0xD, func_80017BB8_main(character, 0x2F), 2, 0x78);
    func_800E5A00_minigame(object, 0xE, func_80017BB8_main(character, 0x36), 2, 0x78);
    func_800E5690_minigame(object, 0);
    D_8010C5B0_popgun_pickoff++;
}

void func_801080DC_popgun_pickoff(omObjData *object, s32 arg1, s32 arg2, u16 player, u16 tag) {
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
    data->unk158 = HuMemAllocTag(sizeof(PopgunPickoffPlayerWork), TAG_OVERLAY);
    memset(data->unk158, 0, sizeof(PopgunPickoffPlayerWork));

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

void func_80108398_popgun_pickoff(omObjData *object) {
    PopgunPickoffCharMotions motions = D_8010CAA8_popgun_pickoff;
    s32 unused[4]; // Unreferenced, but present in the stack frame.
    func_800E1BA8_minigame_ObjData *data;
    PopgunPickoffPlayerWork *work;
    u8 pad;
    f32 rotX;
    f32 rot;
    u16 input;
    s32 target;
    s16 stickX;
    s16 stickY;

    input = 0;
    target = 0;
    data = object->data;
    work = data->unk158;
    pad = data->unk57;
    rotX = object->rot.x;
    rot = data->unk3C;
    func_800E4A90_minigame(object);
    switch (D_8010CC20_popgun_pickoff) {
        case 0:
            func_800E5690_minigame(object, 0x26);
            break;
        case 1:
            work->unk30 = 0xFF;
            break;
        case 2:
            if (!work->unk2D) {
                stickX = D_800CBB6E_main[(s8)pad];
                stickY = D_800D20A1_main[(s8)pad];
                input = D_800D5558_main[(s8)pad];
                if (stickY >= 24) {
                    target = 1;
                } else if (stickY <= -24) {
                    target = 7;
                } else {
                    target = 4;
                }
                if (stickX >= 24) {
                    target += 1;
                } else if (stickX <= -24) {
                    target -= 1;
                }
            } else {
                input = func_8010880C_popgun_pickoff(object);
                target = work->unk34;
            }
            HuSprAttrReset(work->unk2F, 0, 0x8000);
            HuSprPosSet(work->unk2F, 0, D_8010CC28_popgun_pickoff[target].screenX,
                        D_8010CC28_popgun_pickoff[target].screenY);
            rotX = D_8010C5E0_popgun_pickoff[target / 3];
            rot = D_8010C5E8_popgun_pickoff[work->unk2A][target % 3];
            break;
        case 3:
            HuSprAttrSet(work->unk2F, 0, 0x8000);
            func_800E5690_minigame(object, 0);
        case 4:
            func_800E5690_minigame(object, 0);
            func_8001C258_main(object->model[2], 4, 4);
            rotX = 0.0f;
            if (work->unk2A != 0) {
                if (rot > -180.0) {
                    rot -= 20.0;
                } else {
                    rot = -180.0f;
                }
            } else {
                if (rot < 180.0) {
                    rot += 20.0;
                } else {
                    rot = 180.0f;
                }
            }
            break;
        case 5:
            if (work->unk20 != 0) {
                break;
            }
            rot = 180.0f;
            if (work->unk2C) {
                GwPlayer[data->unk59].bonusCoin += 10;
                func_800E5690_minigame(object, 0xD);
                func_80045F1C_main(work->unk24, -1, work->unk2A);
                func_80017954_main(object->model[0], 2, motions.values[work->unk29], work->unk31);
            } else {
                func_800E5690_minigame(object, 0xE);
                func_80017954_main(object->model[0], 2, motions.values[work->unk29], work->unk32);
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
    if (input & 0x8000) {
        if (func_80108A78_popgun_pickoff(object, target) != 0) {
            func_8004AC5C_main(0x496, data->unk59);
            Hu3DMotionTimeSet(object->model[0], 0.0f);
            func_800E5798_minigame(object, 0x27);
        }
    }
    data->unk3C = rot;
    object->rot.y = rot + 180.0;
    object->rot.x = rotX;
    func_800E4E30_minigame(object);
}

u16 func_8010880C_popgun_pickoff(omObjData *object) {
    s16 candidates[9] = { -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    PopgunPickoffPlayerWork *work;
    PopgunPickoffTarget *target;
    u16 input;
    u8 count;
    s32 i;

    count = 0;
    work = PLAYER_WORK(object);
    input = 0;
    switch (work->unk2E) {
        case 0:
            for (i = 0; i < 9; i++) {
                target = &D_8010CC28_popgun_pickoff[i];
                if (target->unk1B != 0) {
                    candidates[count] = i;
                    count++;
                }
            }
            if (count != 0) {
                work->unk34 = candidates[func_80108E1C_popgun_pickoff() % count];
                work->unk2E++;
            }
            break;
        case 1:
            target = &D_8010CC28_popgun_pickoff[work->unk34];
            if (target->unk1A != 0 && func_80108E1C_popgun_pickoff() % (work->unk2B + 2) != 0) {
                work->unk2E = 0;
                break;
            }
            if (func_80108E1C_popgun_pickoff() % (8 - work->unk2B) == 0) {
                input = 0x8000;
            }
            if (target->unk1B != 2 && func_80108E1C_popgun_pickoff() % (work->unk2B + 2) != 0) {
                work->unk2E = 0;
            }
            break;
    }
    return input;
}

u8 func_80108A78_popgun_pickoff(omObjData *object, s32 targetIndex) {
    Vec pos;
    f32 unused[4][4]; // Unreferenced, but present in the stack frame.
    f64 delta[3];
    f64 drop;
    PopgunPickoffPlayerWork *work;
    PopgunPickoffTarget *target;
    PopgunPickoffShot *shot;
    s32 steps;
    s32 i;

    drop = 0.0;
    work = PLAYER_WORK(object);
    target = &D_8010CC28_popgun_pickoff[targetIndex];
    for (i = 0; i < 0x80; i++) {
        if (D_8010CD50_popgun_pickoff[i].active == 0) {
            break;
        }
    }
    if (i == 0x80) {
        return 0;
    }
    shot = &D_8010CD50_popgun_pickoff[i];
    func_80108FE4_popgun_pickoff(object->model[0], "item_hook", Hu3DData[object->model[0]].motTime, &pos);
    shot->pos.x = pos.x;
    shot->pos.y = pos.y;
    shot->pos.z = pos.z - 20.0f;
    delta[0] = target->pos.x - shot->pos.x;
    delta[1] = target->pos.y - shot->pos.y;
    delta[2] = target->pos.z - shot->pos.z;
    steps = sqrtf(delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2]) / 60.0;
    for (i = 1; i <= steps; i++) {
        drop += i * -2.0f;
    }
    shot->vel.x = delta[0] / steps;
    shot->vel.y = (delta[1] - drop) / steps;
    shot->vel.z = delta[2] / steps;
    shot->target = targetIndex;
    shot->unk1A = work->unk2A;
    shot->active = 1;
    shot->playerId = func_8010A024_popgun_pickoff(D_8010CBD0_popgun_pickoff[3], 0x10001808);
    func_8010AC34_popgun_pickoff(shot->playerId, work->unk29);
    func_8010AE0C_popgun_pickoff(shot->playerId, 1.8f, 1.8f, 1.0f);
    return 1;
}

s16 func_80108CF0_popgun_pickoff(s16 spriteId, s16 x, s16 y, f32 rot) {
    s16 group; // Never assigned; the original passes an uninitialized value.
    s32 i;

    if (spriteId == -1) {
        return -1;
    }
    for (i = 0; i < 16; i++) {
        if (D_8010CC00_popgun_pickoff[i] == 0) {
            break;
        }
    }
    if (i >= 16) {
        return -1;
    }
    D_8010CC00_popgun_pickoff[i] = 1;
    HuSprGrpMemberSet(group, i, spriteId, 0);
    HuSprAnimModeSet(group, i, HUSPR_ANIM_MODE_PAT_LOOP);
    HuSprPosSet(group, i, x, y);
    HuSprZRotSet(group, i, rot);
    HuSprAttrReset(group, i, 0x8000);
    return i;
}

s32 func_80108E1C_popgun_pickoff(void) {
    D_8010C5F4_popgun_pickoff = D_8010C5F4_popgun_pickoff * 0x41C64E6D + 0x3039;
    D_8010C5F4_popgun_pickoff += rand8();
    return D_8010C5F4_popgun_pickoff >> 16;
}

f32 func_80108E74_popgun_pickoff(f32 y, f32 x) {
    f32 fullCircle = 360.0f;
    f32 angle = atan2df(x, y) * 57.29577951308232;

    if (angle < 0.0f) {
        angle += fullCircle;
    } else if (angle >= fullCircle) {
        angle -= fullCircle;
    }
    return angle;
}

f32 func_80108EF4_popgun_pickoff(Vec *arg0, Vec *arg1) {
    return sqrtf(((arg0->x - arg1->x) * (arg0->x - arg1->x)) +
                 ((arg0->y - arg1->y) * (arg0->y - arg1->y)) +
                 ((arg0->z - arg1->z) * (arg0->z - arg1->z)));
}

void func_80108F5C_popgun_pickoff(Vec *dir, f32 *rot) {
    *rot++ = func_80108E74_popgun_pickoff(sqrtf(dir->x * dir->x + dir->z * dir->z), -dir->y);
    *rot++ = func_80108E74_popgun_pickoff(dir->z, dir->x);
    *rot = 0.0f;
}

void func_80108FE4_popgun_pickoff(s16 model, char *hook, s16 time, Vec *pos) {
    HuMtx4F transform;
    HuMtx4F result;
    HuMtx4F hookTransform;
    HmfModel *modelData;

    func_80016B00_main(model, time, hook, &hookTransform);
    modelData = &Hu3DData[model];
    func_80088800_main(transform, modelData->pos.x, modelData->pos.y, modelData->pos.z);
    mtxRotCat(transform, modelData->rot.x, modelData->rot.y, modelData->rot.z);
    mtxScaleCat(transform, modelData->scale.x, modelData->scale.y, modelData->scale.z);
    func_80018044_main(hookTransform, transform, result);
    pos->x = result[0][0] + result[1][0] + result[2][0] + result[3][0];
    pos->y = result[0][1] + result[1][1] + result[2][1] + result[3][1];
    pos->z = result[0][2] + result[1][2] + result[2][2] + result[3][2];
}

s16 func_80109108_popgun_pickoff(s32 dataNum) {
    void *data;
    s16 spriteId;

    data = DataRead(dataNum);
    spriteId = HuSprAnimRead(data);
    DataClose(data);
    return spriteId;
}

s16 func_80109150_popgun_pickoff(s16 spriteId, s16 count) {
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

HuSprAnimPat *func_80109218_popgun_pickoff(s16 groupId, s16 member) {
    return &func_80055194_main(groupId)->pat[member];
}

void func_80109260_popgun_pickoff(u16 count) {
    PopgunPickoffPlayer *player;
    s16 i;

    D_8010DDF0_popgun_pickoff = count;
    D_8010DDD8_popgun_pickoff = HuMemAlloc(count * sizeof(PopgunPickoffPlayer));
    for (i = 0; i < 3; i++) {
        D_8010DDDC_popgun_pickoff[i] = NULL;
    }
    for (i = 0; i < D_8010DDF0_popgun_pickoff; i++) {
        player = &D_8010DDD8_popgun_pickoff[i];
        player->sprite = NULL;
        player->callback = NULL;
        player->unk_28 = 0;
        player->unk_20 = 0x100;
        player->unk_1F = 0xFF;
        player->unk_1E = 0xFF;
        player->unk_1D = 0xFF;
        player->unk_2C = 0;
        player->unk_24 = 0;
        player->unk_30.x = 1.0f;
        player->unk_1C = 0;
        player->unk_1B = 0;
        player->unk_30.y = player->unk_30.z = player->unk_3C = 0.0f;
        player->unk_40.x = player->unk_40.y = player->unk_40.z = 0.0f;
        player->unk_4C.x = player->unk_4C.y = player->unk_4C.z = 1.0f;
        player->unk_58.x = player->unk_58.y = player->unk_58.z = 0.0f;
    }
}

void func_801093A8_popgun_pickoff(Gfx **gfx, HuSprAnimPat *cel, u8 fmt, u8 siz, u16 height, u16 uls,
                                  u16 ult, u16 lrs, u16 lrt, u16 cms, u16 cmt, u16 masks, u16 maskt, s32 mode) {
    Gfx *gdl = *gfx;

    switch (mode) {
        case 0:
            gDPLoadTextureTile_4b(gdl++, (void *)0x0C000000, fmt, cel->sizeX, height, uls, ult, lrs, lrt, 0, cms,
                                  cmt, masks, maskt, 0, 0);
            break;
        case 1:
            func_80034998_main(&gdl, (void *)0x0C000000, fmt, cel->sizeX, height, uls, ult, lrs, lrt, 0, cms, cmt,
                               masks, maskt, 0, 0);
            break;
        case 2:
            func_800341D0_main(&gdl, (u16 *)0x0C000000, fmt, siz, cel->sizeX, cel->sizeY, uls, ult, lrs, lrt, 0,
                               cms, cmt, masks, maskt, 0, 0);
            break;
        case 3:
            func_8003465C_main(&gdl, (void *)0x0C000000, fmt, siz, cel->sizeX, height, uls, ult, lrs, lrt, 0, cms,
                               cmt, masks, maskt, 0, 0);
            break;
    }
    *gfx = gdl;
}

s16 func_80109718_popgun_pickoff(PopgunPickoffPlayer *player) {
    HuSprAnimPat segCel;
    Gfx *gfx;
    Gfx *buf;
    Gfx *start;
    HuSprAnimPat *cel;
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

    cel = player->sprite->pat;
    buf = HuMemAlloc(0x1000);
    gfx = buf;
    gSPSegment(gfx++, 0x0C, cel->data);
    gSPSegment(gfx++, 0x0E, player->vtx);
    start = gfx;
    gDPPipeSync(gfx++);
    switch (player->sprite->pixelBits) {
        case 4:
            siz = G_IM_SIZ_4b;
            if (player->sprite->palNum == 1) {
                fmt = G_IM_FMT_IA;
                gDPSetTextureLUT(gfx++, G_TT_NONE);
            } else {
                fmt = G_IM_FMT_CI;
                gDPLoadTLUT_pal16(gfx++, 0, player->sprite->pal);
                gDPSetTextureLUT(gfx++, G_TT_RGBA16);
            }
            mode = 0;
            break;
        case 8:
            siz = G_IM_SIZ_8b;
            if (player->sprite->palNum == 1) {
                fmt = G_IM_FMT_IA;
                gDPSetTextureLUT(gfx++, G_TT_NONE);
            } else {
                fmt = G_IM_FMT_CI;
                gDPLoadTLUT_pal256(gfx++, player->sprite->pal);
                gDPSetTextureLUT(gfx++, G_TT_RGBA16);
            }
            mode = 2;
            break;
        case 16:
            siz = G_IM_SIZ_16b;
            if (player->sprite->palNum == 1) {
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
    alignedWidth = (((cel->sizeX << siz) >> 4) << 4) >> siz;
    if (alignedWidth < cel->sizeX) {
        alignedWidth += 16 >> siz;
    }
    switch (fmt) {
        case G_IM_FMT_CI:
            if ((4096 >> siz) >= cel->sizeY * alignedWidth) {
                rows = cel->sizeY;
            } else {
                rows = (4096 >> siz) / alignedWidth;
            }
            break;
        case G_IM_FMT_I:
            if (4096 >= cel->sizeY * alignedWidth) {
                rows = cel->sizeY;
            } else {
                rows = 4096 / alignedWidth;
            }
            break;
        default:
            if ((8192 >> siz) >= cel->sizeY * alignedWidth) {
                rows = cel->sizeY;
            } else {
                rows = (8192 >> siz) / alignedWidth;
            }
            break;
    }
    count = cel->sizeY / rows;
    remainder = cel->sizeY - count * rows;
    // Aligned strips can use the block loader when its DXT rounding is exact.
    if (cel->sizeX % (16 >> siz) == 0) {
        if (((rows * cel->sizeX) << siz) <= 4096) {
            if (D_8010C608_popgun_pickoff[cel->sizeX >> D_8010C5F8_popgun_pickoff[siz]] >= rows ||
                rows == D_8010C740_popgun_pickoff[cel->sizeX >> D_8010C5F8_popgun_pickoff[siz]]) {
                mode++;
            }
        }
    }
    // The differing masks/maskt byte conversions are required to match register allocation.
    if (player->unk_28 & 0xC0000) {
        masks = player->unk_1B & 0xFF;
        cms = (player->unk_28 >> 18) - 1;
    } else {
        masks = 0;
        cms = 0;
    }
    if (player->unk_28 & 0x300000) {
        maskt = (u8)player->unk_1C;
        cmt = (player->unk_28 >> 20) - 1;
    } else {
        maskt = 0;
        cmt = 0;
    }
    gDPPipeSync(gfx++);
    segCel = *cel;
    segCel.data = (void *)0x0C000000;
    if ((u32)player->unk_28 >= 0x80000000 && count == 1 && remainder == 0) {
        func_801093A8_popgun_pickoff(&gfx, &segCel, fmt, siz, rows, 0, 0, cel->sizeX - 1, cel->sizeY - 1, cms, cmt, masks,
                                     maskt, mode);
        gSPVertex(gfx++, (Vtx *)0x0E000000, 5, 0);
        gSP2Triangles(gfx++, 0, 2, 4, 0, 2, 3, 4, 0);
        gSP2Triangles(gfx++, 0, 4, 1, 0, 4, 3, 1, 0);
    } else {
        for (i = 0; i < count; i++) {
            func_801093A8_popgun_pickoff(&gfx, &segCel, fmt, siz, rows, 0, i * rows, cel->sizeX - 1, (i + 1) * rows - 1,
                                         cms, cmt, masks, maskt, mode);
            gSPVertex(gfx++, (Vtx *)0x0E000000 + i * 2, 4, 0);
            gSP2Triangles(gfx++, 0, 2, 3, 0, 0, 3, 1, 0);
        }
        if (remainder != 0) {
            func_801093A8_popgun_pickoff(&gfx, &segCel, fmt, siz, remainder, 0, i * rows, cel->sizeX - 1,
                                         cel->sizeY - 1, cms, cmt, masks, maskt, mode);
            gSPVertex(gfx++, (Vtx *)0x0E000000 + i * 2, 4, 0);
            gSP2Triangles(gfx++, 0, 2, 3, 0, 0, 3, 1, 0);
        }
    }
    gSPEndDisplayList(gfx++);
    player->unk_22 = gfx - start;
    player->displayList = HuMemAlloc(player->unk_22 * sizeof(Gfx));
    memcpy(player->displayList, start, player->unk_22 * sizeof(Gfx));
    HuMemFree(buf);
    return 1;
}

s16 func_8010A024_popgun_pickoff(s16 spriteId, s32 flags) {
    PopgunPickoffPlayer *player;
    HuSprAnimPat *cel;
    s32 index;
    s32 siz;
    s32 fmt;
    s32 alignedWidth;
    u32 rows;
    u32 count;
    s32 remainder;
    u32 i;
    s32 j;

    for (index = 0; index < D_8010DDF0_popgun_pickoff; index++) {
        if (D_8010DDD8_popgun_pickoff[index].sprite == NULL) {
            break;
        }
    }
    if (index == D_8010DDF0_popgun_pickoff) {
        return -1;
    }
    player = &D_8010DDD8_popgun_pickoff[index];
    player->sprite = D_800C9530_main[spriteId];
    player->unk_28 = flags;
    player->unk_1A = 7;
    cel = player->sprite->pat;
    switch (player->sprite->pixelBits) {
        case 4:
            siz = G_IM_SIZ_4b;
            fmt = (player->sprite->palNum == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 8:
            siz = G_IM_SIZ_8b;
            fmt = (player->sprite->palNum == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 16:
            siz = G_IM_SIZ_16b;
            fmt = (player->sprite->palNum == 1) ? G_IM_FMT_IA : G_IM_FMT_RGBA;
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
    alignedWidth = (((cel->sizeX << siz) >> 4) << 4) >> siz;
    if (alignedWidth < cel->sizeX) {
        alignedWidth += 16 >> siz;
    }
    switch (fmt) {
        case G_IM_FMT_CI:
            if ((4096 >> siz) >= cel->sizeY * alignedWidth) {
                rows = cel->sizeY;
            } else {
                rows = (4096 >> siz) / alignedWidth;
            }
            break;
        case G_IM_FMT_I:
            if (4096 >= cel->sizeY * alignedWidth) {
                rows = cel->sizeY;
            } else {
                rows = 4096 / alignedWidth;
            }
            break;
        default:
            if ((8192 >> siz) >= cel->sizeY * alignedWidth) {
                rows = cel->sizeY;
            } else {
                rows = (8192 >> siz) / alignedWidth;
            }
            break;
    }
    count = cel->sizeY / rows;
    remainder = cel->sizeY - count * rows;
    player->unk_18 = count + 2;
    player->unk_19 = rows;
    player->vtx = HuMemAlloc((count + 2) * 2 * sizeof(Vtx));
    for (i = 0; i < count + 1; i++) {
        player->vtx[i * 2].ob[0] = 0;
        player->vtx[i * 2 + 1].ob[0] = cel->sizeX;
        player->vtx[i * 2].ob[1] = player->vtx[i * 2 + 1].ob[1] = -i * rows;
        player->vtx[i * 2].tc[0] = 0;
        player->vtx[i * 2 + 1].tc[0] = cel->sizeX << 6;
        player->vtx[i * 2].tc[1] = (i * rows) << 6;
        player->vtx[i * 2 + 1].tc[1] = (i * rows) << 6;
        for (j = 0; j < 2; j++) {
            player->vtx[i * 2 + j].ob[2] = 0;
            player->vtx[i * 2 + j].cn[0] = 0xFF;
            player->vtx[i * 2 + j].cn[1] = 0xFF;
            player->vtx[i * 2 + j].cn[2] = 0xFF;
            player->vtx[i * 2 + j].cn[3] = 0xFF;
        }
    }
    if (remainder != 0) {
        player->vtx[i * 2].ob[0] = 0;
        player->vtx[i * 2 + 1].ob[0] = cel->sizeX;
        player->vtx[i * 2].ob[1] = player->vtx[i * 2 + 1].ob[1] = cel->sizeY;
        player->vtx[i * 2].tc[0] = 0;
        player->vtx[i * 2 + 1].tc[0] = cel->sizeX << 6;
        player->vtx[i * 2].tc[1] = player->vtx[i * 2 + 1].tc[1] = cel->sizeY << 6;
        for (j = 0; j < 2; j++) {
            player->vtx[i * 2 + j].ob[2] = 0;
            player->vtx[i * 2 + j].cn[0] = 0xFF;
            player->vtx[i * 2 + j].cn[1] = 0xFF;
            player->vtx[i * 2 + j].cn[2] = 0xFF;
            player->vtx[i * 2 + j].cn[3] = 0xFF;
        }
    } else if (count == 1) {
        player->vtx[4].ob[0] = cel->sizeX * 0.5;
        player->vtx[4].ob[1] = -cel->sizeY * 0.5;
        player->vtx[4].ob[2] = 0;
        player->vtx[4].tc[0] = cel->sizeX * 0.5 * 64.0;
        player->vtx[4].tc[1] = cel->sizeY * 0.5 * 64.0;
        player->vtx[4].cn[0] = 0xFF;
        player->vtx[4].cn[1] = 0xFF;
        player->vtx[4].cn[2] = 0xFF;
        player->vtx[4].cn[3] = 0xFF;
    }
    if (!func_80109718_popgun_pickoff(player)) {
        HuMemFree(player->vtx);
        index = -1;
    }
    return index;
}

void func_8010A62C_popgun_pickoff(s16 index, s16 spriteId) {
    PopgunPickoffPlayer *player;
    HuSprAnimPat *cel;
    s32 siz;
    s32 fmt;
    s32 alignedWidth;
    u32 rows;
    u32 count;
    s32 remainder;
    u32 i;
    s32 j;

    player = &D_8010DDD8_popgun_pickoff[index];
    player->sprite = D_800C9530_main[spriteId];
    cel = player->sprite->pat;
    HuMemFree(player->vtx);
    HuMemFree(player->displayList);
    switch (player->sprite->pixelBits) {
        case 4:
            siz = G_IM_SIZ_4b;
            fmt = (player->sprite->palNum == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 8:
            siz = G_IM_SIZ_8b;
            fmt = (player->sprite->palNum == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 16:
            siz = G_IM_SIZ_16b;
            fmt = (player->sprite->palNum == 1) ? G_IM_FMT_IA : G_IM_FMT_RGBA;
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
    alignedWidth = (((cel->sizeX << siz) >> 4) << 4) >> siz;
    if (alignedWidth < cel->sizeX) {
        alignedWidth += 16 >> siz;
    }
    switch (fmt) {
        case G_IM_FMT_CI:
            if ((4096 >> siz) >= cel->sizeY * alignedWidth) {
                rows = cel->sizeY;
            } else {
                rows = (4096 >> siz) / alignedWidth;
            }
            break;
        case G_IM_FMT_I:
            if (4096 >= cel->sizeY * alignedWidth) {
                rows = cel->sizeY;
            } else {
                rows = 4096 / alignedWidth;
            }
            break;
        default:
            if ((8192 >> siz) >= cel->sizeY * alignedWidth) {
                rows = cel->sizeY;
            } else {
                rows = (8192 >> siz) / alignedWidth;
            }
            break;
    }
    count = cel->sizeY / rows;
    remainder = cel->sizeY - count * rows;
    player->unk_18 = count + 2;
    player->unk_19 = rows;
    player->vtx = HuMemAlloc((count + 2) * 2 * sizeof(Vtx));
    for (i = 0; i < count + 1; i++) {
        player->vtx[i * 2].ob[0] = 0;
        player->vtx[i * 2 + 1].ob[0] = cel->sizeX;
        player->vtx[i * 2].ob[1] = player->vtx[i * 2 + 1].ob[1] = -i * rows;
        player->vtx[i * 2].tc[0] = 0;
        player->vtx[i * 2 + 1].tc[0] = cel->sizeX << 6;
        player->vtx[i * 2].tc[1] = (i * rows) << 6;
        player->vtx[i * 2 + 1].tc[1] = (i * rows) << 6;
        for (j = 0; j < 2; j++) {
            player->vtx[i * 2 + j].ob[2] = 0;
            player->vtx[i * 2 + j].cn[0] = 0xFF;
            player->vtx[i * 2 + j].cn[1] = 0xFF;
            player->vtx[i * 2 + j].cn[2] = 0xFF;
            player->vtx[i * 2 + j].cn[3] = 0xFF;
        }
    }
    if (remainder != 0) {
        player->vtx[i * 2].ob[0] = 0;
        player->vtx[i * 2 + 1].ob[0] = cel->sizeX;
        player->vtx[i * 2].ob[1] = player->vtx[i * 2 + 1].ob[1] = cel->sizeY;
        player->vtx[i * 2].tc[0] = 0;
        player->vtx[i * 2 + 1].tc[0] = cel->sizeX << 6;
        player->vtx[i * 2].tc[1] = player->vtx[i * 2 + 1].tc[1] = cel->sizeY << 6;
        for (j = 0; j < 2; j++) {
            player->vtx[i * 2 + j].ob[2] = 0;
            player->vtx[i * 2 + j].cn[0] = 0xFF;
            player->vtx[i * 2 + j].cn[1] = 0xFF;
            player->vtx[i * 2 + j].cn[2] = 0xFF;
            player->vtx[i * 2 + j].cn[3] = 0xFF;
        }
    } else if (count == 1) {
        player->vtx[4].ob[0] = cel->sizeX * 0.5;
        player->vtx[4].ob[1] = -cel->sizeY * 0.5;
        player->vtx[4].ob[2] = 0;
        player->vtx[4].tc[0] = cel->sizeX * 0.5 * 64.0;
        player->vtx[4].tc[1] = cel->sizeY * 0.5 * 64.0;
        player->vtx[4].cn[0] = 0xFF;
        player->vtx[4].cn[1] = 0xFF;
        player->vtx[4].cn[2] = 0xFF;
        player->vtx[4].cn[3] = 0xFF;
    }
    func_80109718_popgun_pickoff(player);
}

void func_8010ABB4_popgun_pickoff(s16 playerId, s16 spriteId) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->sprite = D_800C9530_main[spriteId];
        player->unk_1F = 0xFF;
        player->unk_1E = 0xFF;
        player->unk_1D = 0xFF;
        player->unk_20 = 0xFF;
        player->unk_2C = 0;
        player->unk_24 = 0;
        player->unk_30.x = 1.0f;
    }
}

void func_8010AC34_popgun_pickoff(s16 playerId, s16 value) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_24 = value;
        player->unk_2C = 0;
    }
}

void func_8010AC74_popgun_pickoff(s16 playerId, f32 value) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_30.x = value;
    }
}

void func_8010ACB4_popgun_pickoff(s16 playerId, f32 x, f32 y, f32 z) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_28 |= 0x4000000;
        player->unk_30.y = x;
        player->unk_30.z = y;
        player->unk_3C = z;
    }
}

void func_8010AD14_popgun_pickoff(s16 playerId, f32 value) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_3C = value;
    }
}

void func_8010AD54_popgun_pickoff(s16 playerId, f32 x, f32 y, f32 z) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_40.x = x;
        player->unk_40.y = y;
        player->unk_40.z = z;
    }
}

void func_8010ADA4_popgun_pickoff(s16 playerId, f32 x, f32 y, f32 z) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_40.x += x;
        player->unk_40.y += y;
        player->unk_40.z += z;
    }
}

void func_8010AE0C_popgun_pickoff(s16 playerId, f32 x, f32 y, f32 z) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_4C.x = x;
        player->unk_4C.y = y;
        player->unk_4C.z = z;
    }
}

void func_8010AE5C_popgun_pickoff(s16 playerId, f32 x, f32 y, f32 z) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_58.x = x;
        player->unk_58.y = y;
        player->unk_58.z = z;
    }
}

void func_8010AEAC_popgun_pickoff(s16 playerId, s32 value) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_28 |= value;
    }
}

void func_8010AEF0_popgun_pickoff(s16 playerId, s32 value) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_28 &= ~value;
    }
}

s32 func_8010AF38_popgun_pickoff(s16 playerId) {
    PopgunPickoffPlayer *player;
    s32 id = playerId;

    if (id != -1) {
        player = D_8010DDD8_popgun_pickoff + id;
        return player->unk_28;
    }
    return -1;
}

void func_8010AF78_popgun_pickoff(s16 playerId, s8 value) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_1A = value;
    }
}

PopgunPickoffPlayer *func_8010AFB4_popgun_pickoff(s16 playerId) {
    if (playerId == -1) {
        return NULL;
    }
    return D_8010DDD8_popgun_pickoff + playerId;
}

Vtx_t *func_8010AFF4_popgun_pickoff(s16 playerId) {
    PopgunPickoffPlayer *player;
    s32 id = playerId;

    if (id == -1) {
        return NULL;
    }
    player = D_8010DDD8_popgun_pickoff + id;
    return player->vtx;
}

s32 func_8010B038_popgun_pickoff(s16 playerId, s16 x, s16 y) {
    PopgunPickoffPlayer *player;
    Vtx_t *vtx;

    if (playerId == -1) {
        return 0;
    }
    player = D_8010DDD8_popgun_pickoff + playerId;
    if (player->unk_18 != 3) {
        return 0;
    }
    player->unk_28 |= 0x80000000;
    vtx = &player->vtx[4];
    vtx->ob[0] = x;
    vtx->ob[1] = -y;
    vtx->ob[2] = 0;
    vtx->tc[0] = x * 64;
    vtx->tc[1] = y * 64;
    return 1;
}

void func_8010B0D4_popgun_pickoff(s16 playerId, s8 value1, s8 value2, s8 value3, s16 value4) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_1D = value1;
        player->unk_1E = value2;
        player->unk_1F = value3;
        player->unk_20 = value4;
    }
}

void func_8010B120_popgun_pickoff(s16 index) {
    PopgunPickoffPlayer *player;

    if (index != -1) {
        player = &D_8010DDD8_popgun_pickoff[index];
        if (player->sprite != NULL) {
            HuMemFree(player->displayList);
            HuMemFree(player->vtx);
            player->sprite = NULL;
            player->unk_28 = 0;
            player->unk_20 = 0x100;
            player->unk_1F = 0xFF;
            player->unk_1E = 0xFF;
            player->unk_1D = 0xFF;
            player->unk_2C = 0;
            player->unk_24 = 0;
            player->unk_1C = 0;
            player->unk_1B = 0;
            player->unk_30.y = player->unk_30.z = player->unk_3C = 0.0f;
            player->unk_40.x = player->unk_40.y = player->unk_40.z = 0.0f;
            player->unk_4C.x = player->unk_4C.y = player->unk_4C.z = 1.0f;
            player->unk_58.x = player->unk_58.y = player->unk_58.z = 0.0f;
            player->unk_30.x = 1.0f;
        }
    }
}

void func_8010B200_popgun_pickoff(s32 playerId, s32 flag) {
    PopgunPickoffPlayer *player = D_8010DDD8_popgun_pickoff + playerId;
    s32 i;

    if (flag != 0) {
        player->unk_28 |= 0x10000;
        for (i = 0; i < player->unk_18; i++) {
            player->vtx[i].cn[0] = 0;
            player->vtx[i].cn[1] = 0;
            player->vtx[i].cn[2] = 0x80;
        }
        return;
    }
    player->unk_28 &= ~0x10000;
    for (i = 0; i < player->unk_18; i++) {
        player->vtx[i].cn[0] = 0xFF;
        player->vtx[i].cn[1] = 0xFF;
        player->vtx[i].cn[2] = 0xFF;
        player->vtx[i].cn[3] = 0xFF;
    }
}

void func_8010B300_popgun_pickoff(s32 index, s32 flip) {
    PopgunPickoffPlayer *player = &D_8010DDD8_popgun_pickoff[index];
    s32 i;

    if (flip) {
        for (i = 0; i < player->unk_18; i++) {
            player->vtx[i * 2].tc[0] = player->sprite->pat->sizeX << 6;
            player->vtx[i * 2 + 1].tc[0] = 0;
        }
    } else {
        for (i = 0; i < player->unk_18; i++) {
            player->vtx[i * 2].tc[0] = 0;
            player->vtx[i * 2 + 1].tc[0] = player->sprite->pat->sizeX << 6;
        }
    }
}

void func_8010B3D0_popgun_pickoff(s32 index, s32 flip) {
    PopgunPickoffPlayer *player = &D_8010DDD8_popgun_pickoff[index];
    s32 remainder = player->sprite->pat->sizeY - (player->unk_18 - 2) * player->unk_19;
    s32 i;

    if (flip) {
        for (i = 0; i < player->unk_18 - 1; i++) {
            player->vtx[i * 2].tc[1] = player->vtx[i * 2 + 1].tc[1] =
                player->sprite->pat->sizeY - i * player->unk_19;
        }
        if (remainder != 0) {
            player->vtx[i * 2].tc[1] = player->vtx[i * 2 + 1].tc[1] = 0;
        }
    } else {
        for (i = 0; i < player->unk_18 - 1; i++) {
            player->vtx[i * 2].ob[1] = player->vtx[i * 2 + 1].ob[1] = i * player->unk_19;
        }
        if (remainder != 0) {
            player->vtx[i * 2].ob[1] = player->vtx[i * 2 + 1].ob[1] = player->sprite->pat->sizeY;
        }
    }
}

void func_8010B508_popgun_pickoff(s16 playerId, void (*callback)(PopgunPickoffPlayer *)) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->callback = callback;
    }
}

void func_8010B544_popgun_pickoff(s16 index, s8 arg1, s8 arg2, s32 flags) {
    PopgunPickoffPlayer *player;

    if (index != -1) {
        player = &D_8010DDD8_popgun_pickoff[index];
        player->unk_1B = arg1;
        player->unk_1C = arg2;
        player->unk_28 |= flags;
        HuMemFree(player->displayList);
        func_80109718_popgun_pickoff(player);
    }
}

void func_8010B5B4_popgun_pickoff(s16 index, s32 flag) {
    PopgunPickoffPlayer *player;
    s8 color;
    s8 blue;
    s32 i;

    if (index != -1) {
        player = &D_8010DDD8_popgun_pickoff[index];
        if (flag) {
            color = 0;
            blue = 0x70;
        } else {
            color = 0xFF;
            blue = 0xFF;
        }
        for (i = 0; i < player->unk_18; i++) {
            player->vtx[i].cn[0] = player->vtx[i].cn[1] = player->vtx[i].cn[3] = color;
            player->vtx[i].cn[2] = blue;
        }
    }
}

void func_8010B64C_popgun_pickoff(void) {
    PopgunPickoffPlayer *player;
    s32 i;

    if (++D_8010C890_popgun_pickoff >= 3) {
        D_8010C890_popgun_pickoff = 0;
    }
    D_8010DDEC_popgun_pickoff = 0;
    for (i = 0; i < D_8010DDF0_popgun_pickoff; i++) {
        player = &D_8010DDD8_popgun_pickoff[i];
        if (player->sprite != NULL) {
            D_8010DDEC_popgun_pickoff += 0x40 + (player->unk_22 * sizeof(Gfx) + player->unk_18 * 2 * sizeof(Vtx));
        }
    }
    if (D_8010DDDC_popgun_pickoff[D_8010C890_popgun_pickoff] != NULL) {
        HuMemFree(D_8010DDDC_popgun_pickoff[D_8010C890_popgun_pickoff]);
    }
    if (D_8010DDEC_popgun_pickoff != 0) {
        D_8010DDDC_popgun_pickoff[D_8010C890_popgun_pickoff] = HuMemAlloc(D_8010DDEC_popgun_pickoff);
    } else {
        D_8010DDDC_popgun_pickoff[D_8010C890_popgun_pickoff] = NULL;
    }
    D_8010DDE8_popgun_pickoff = D_8010DDDC_popgun_pickoff[D_8010C890_popgun_pickoff];
}

void func_8010B7A0_popgun_pickoff(HuCamera *camera, HuMtx4F lookAt) {
    PopgunPickoffPlayer tailOpaque;
    PopgunPickoffPlayer tailTranslucent;
    HuMtx4F unused[16]; // Unreferenced, but present in the stack frame.
    HuMtx4F mtx;
    PopgunPickoffPlayer *player;
    PopgunPickoffPlayer *node;
    f32 minX;
    f32 maxX;
    f32 minZ;
    f32 maxZ;
    s32 i;

    minX = camera->at.x - 640.0;
    maxX = camera->at.x + 640.0;
    minZ = camera->at.z - 640.0;
    maxZ = camera->at.z + 640.0;
    D_8010DE00_popgun_pickoff.unk_64 = 0.0f;
    D_8010DE68_popgun_pickoff.unk_64 = 99999.9f;
    tailOpaque.unk_64 = -99999.9f;
    tailTranslucent.unk_64 = 0.0f;
    D_8010DE68_popgun_pickoff.prev = NULL;
    D_8010DE00_popgun_pickoff.prev = NULL;
    D_8010DE00_popgun_pickoff.next = &tailOpaque;
    D_8010DE68_popgun_pickoff.next = &tailTranslucent;
    tailOpaque.prev = &D_8010DE00_popgun_pickoff;
    tailTranslucent.prev = &D_8010DE68_popgun_pickoff;
    tailTranslucent.next = NULL;
    tailOpaque.next = NULL;
    for (i = 0; i < D_8010DDF0_popgun_pickoff; i++) {
        player = &D_8010DDD8_popgun_pickoff[i];
        if (player->sprite == NULL) {
            continue;
        }
        if (player->unk_40.x < minX || maxX < player->unk_40.x) {
            continue;
        }
        if (player->unk_40.z < minZ || maxZ < player->unk_40.z) {
            continue;
        }
        guTranslateF(mtx, player->unk_40.x, player->unk_40.y, player->unk_40.z);
        guMtxCatF(mtx, lookAt, mtx);
        player->unk_64 = mtx[3][2];
        if (player->unk_64 > 0.0) {
            continue;
        }
        if ((player->unk_28 & 0x1000) && player->unk_20 < 0x100) {
            player->unk_64 *= -1.0;
            node = &D_8010DE68_popgun_pickoff;
        } else {
            node = &D_8010DE00_popgun_pickoff;
        }
        for (node = node->next; node->unk_64 > player->unk_64; node = node->next) {}
        node->prev->next = player;
        player->prev = node->prev;
        player->next = node;
        node->prev = player;
    }
    tailOpaque.prev->next = tailTranslucent.prev->next = NULL;
}

void func_8010BA44_popgun_pickoff(Gfx **gfxP, s32 arg1, s32 arg2) {
    HuCamera *camera = (HuCamera *)arg2;
    Gfx *gfx = *gfxP;
    HuMtx4F unused1[2]; // Unreferenced, but present in the stack frame.
    HuMtx4F lookAt;
    HuMtx4F unused2[4]; // Unreferenced, but present in the stack frame.
    Vec rot;
    Vec dir;
    HuMtx4F unused3[32]; // Unreferenced, but present in the stack frame.
    PopgunPickoffPlayer *player;

    guLookAtF(lookAt, camera->pos.x, camera->pos.y, camera->pos.z, camera->at.x, camera->at.y, camera->at.z,
              camera->up.x, camera->up.y, camera->up.z);
    dir.x = camera->pos.x - camera->at.x;
    dir.y = camera->pos.y - camera->at.y;
    dir.z = camera->pos.z - camera->at.z;
    func_80108F5C_popgun_pickoff(&dir, (f32 *)&rot);
    func_8010B64C_popgun_pickoff();
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_2CYCLE);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING | G_TEXTURE_GEN);
    gSPSetGeometryMode(gfx++, G_SHADE | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    func_8010B7A0_popgun_pickoff(camera, lookAt);
    for (player = D_8010DE00_popgun_pickoff.next; player != NULL; player = player->next) {
        gfx = func_8010BC6C_popgun_pickoff(gfx, player, lookAt, &rot);
    }
    for (player = D_8010DE68_popgun_pickoff.next; player != NULL; player = player->next) {
        gfx = func_8010BC6C_popgun_pickoff(gfx, player, lookAt, &rot);
    }
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    *gfxP = gfx;
    if (!Hu3DPauseF) {
        func_8010C32C_popgun_pickoff();
    }
}

Gfx *func_8010BC6C_popgun_pickoff(Gfx *gfx, PopgunPickoffPlayer *player, HuMtx4F lookAt, Vec *rot) {
    HuMtx4F scale;
    HuMtx4F mtx;
    HuMtx4F billboard;
    HuMtx4F inverse;
    HuSprAnimPat *cel;
    u16 format;
    u32 blend;
    u32 mode;
    Vtx *vtx;
    Mtx *mtxL;
    Gfx *dl;

    cel = &player->sprite->pat[player->unk_24];
    gDPPipeSync(gfx++);
    gDPSetTextureFilter(gfx++, D_8010C880_popgun_pickoff[(player->unk_28 >> 2) & 3]);
    gDPSetColorDither(gfx++, D_8010C878_popgun_pickoff[(player->unk_28 >> 4) & 3]);
    gDPSetAlphaCompare(gfx++, D_8010C888_popgun_pickoff[(player->unk_28 >> 22) & 3]);
    if (player->unk_28 & 0x10000) {
        gSPSetGeometryMode(gfx++, G_LIGHTING);
    } else {
        gSPClearGeometryMode(gfx++, G_LIGHTING);
    }
    format = player->sprite->pixelBits;
    blend = 0x110000;
    if (player->unk_28 & 0x8000000) {
        blend = 0xC8004000;
    }
    if (player->unk_28 & 0x1000) {
        if (format & 0x8000) {
            mode = 0x4850;
            blend = 0x100000;
            if (player->unk_20 == 0x100) {
                gDPSetCombineMode(gfx++, POPGUN_CC_PRIM_DECALA, POPGUN_CC_MODULATEI_PASSA2);
            } else {
                gDPSetCombineMode(gfx++, POPGUN_CC_PRIM_MODULATEA, G_CC_MODULATEIA2);
            }
        } else if (player->unk_20 == 0x100) {
            mode = 0x3038;
            if (player->unk_28 & 0x2000000) {
                gDPSetCombineMode(gfx++, POPGUN_CC_BLEND_DECALA, POPGUN_CC_MODULATEI_PASSA2);
            } else {
                gDPSetCombineMode(gfx++, G_CC_MODULATEIDECALA, POPGUN_CC_MODULATEI_PASSA2);
            }
        } else {
            mode = 0x4850;
            blend = 0x100000;
            if (player->unk_28 & 0x2000000) {
                gDPSetCombineMode(gfx++, POPGUN_CC_BLEND_MODULATEA, G_CC_MODULATEIA2);
            } else {
                gDPSetCombineMode(gfx++, POPGUN_CC_MODULATEI_PRIMA, G_CC_MODULATEIA2);
            }
        }
    } else {
        mode = 0x2030;
        if (player->unk_28 & 0x2000000) {
            gDPSetCombineMode(gfx++, POPGUN_CC_BLEND_MODULATEA, G_CC_PASS2);
        } else {
            gDPSetCombineMode(gfx++, POPGUN_CC_MODULATEI_PRIMA, G_CC_PASS2);
        }
    }
    switch ((player->unk_28 >> 10) & 3) {
        case 0:
            mode |= 0x200;
            break;
        case 2:
            mode |= 0x40;
            if ((player->unk_28 & 0x1000) && player->unk_20 != 0x100) {
                mode |= 0x180;
            }
        case 1:
            mode |= 0x8;
            break;
    }
    if (player->unk_28 & 0x2000) {
        mode |= 0xC00;
    }
    if (player->unk_28 & 0x8000000) {
        gSPSetGeometryMode(gfx++, G_FOG);
        gDPSetRenderMode(gfx++, G_RM_FOG_SHADE_A, mode | blend);
    } else {
        gSPClearGeometryMode(gfx++, G_FOG);
        gDPSetRenderMode(gfx++, G_RM_PASS, mode | blend);
    }
    gDPSetPrimColor(gfx++, 0, 0, player->unk_1D, player->unk_1E, player->unk_1F, player->unk_20);
    vtx = D_8010DDE8_popgun_pickoff;
    mtxL = (Mtx *)&vtx[player->unk_18 * 2];
    dl = (Gfx *)&mtxL[1];
    D_8010DDE8_popgun_pickoff = &dl[player->unk_22];
    guMtxIdentF(billboard);
    if (player->unk_28 & 0x4000000) {
        billboard[3][0] = -player->unk_30.y;
        billboard[3][1] = player->unk_30.z;
    } else {
        billboard[3][0] = -(u16)cel->centerX;
        billboard[3][1] = (u16)cel->centerY;
    }
    billboard[3][2] = player->unk_3C;
    func_8002367C_main(mtx, lookAt);
    mtxTransCat(mtx, player->unk_40.x, player->unk_40.y, player->unk_40.z);
    mtxRotCat(mtx, player->unk_58.x, player->unk_58.y, player->unk_58.z);
    mtxScaleCat(mtx, player->unk_4C.x, player->unk_4C.y, player->unk_4C.z);
    switch (player->unk_1A) {
        case 1:
            func_8008A120_main(mtx, rot->x);
            break;
        case 2:
            func_8008A2A0_main(mtx, rot->y);
            break;
        case 4:
            break;
        case 7:
            scale[0][0] = player->unk_4C.x;
            scale[1][1] = player->unk_4C.y;
            scale[2][2] = player->unk_4C.z;
            scale[3][3] = 1.0f;
            scale[0][1] = scale[0][2] = scale[0][3] = scale[1][0] = scale[1][2] = scale[1][3] = scale[2][0] =
                scale[2][1] = scale[2][3] = scale[3][0] = scale[3][1] = scale[3][2] = 0.0f;
            func_80018544_main(mtx, inverse);
            func_80018044_main(scale, inverse, mtx);
            break;
    }
    guMtxCatF(billboard, mtx, mtx);
    guMtxF2L(mtx, mtxL);
    gSPMatrix(gfx++, osVirtualToPhysical(mtxL), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPSegment(gfx++, 0x0C, cel->data);
    gSPSegment(gfx++, 0x0E, vtx);
    memcpy(vtx, player->vtx, player->unk_18 * 2 * sizeof(Vtx));
    memcpy(dl, player->displayList, player->unk_22 * sizeof(Gfx));
    if (!(player->unk_28 & 0x8000)) {
        gSPDisplayList(gfx++, dl);
    }
    return gfx;
}

void func_8010C32C_popgun_pickoff(void) {
    PopgunPickoffPlayer *player;
    s32 frameCount;
    s32 i;

    for (i = 0; i < D_8010DDF0_popgun_pickoff; i++) {
        player = &D_8010DDD8_popgun_pickoff[i];
        if (player->callback != NULL) {
            player->callback(player);
        }
        if (player->sprite == NULL) {
            continue;
        }
        if (player->unk_28 & 0x8000) {
            continue;
        }
        if (player->unk_28 & 0x10000000) {
            continue;
        }
        frameCount = player->sprite->patNum;
        player->unk_2C += player->unk_30.x;
        while (player->unk_2C >= 1.0) {
            player->unk_24++;
            player->unk_2C -= 1.0f;
            if (player->unk_24 >= frameCount) {
                if (player->unk_28 & 0x20000000) {
                    player->unk_28 |= 0x8000;
                    player->unk_24--;
                    player->unk_2C += 1.0f;
                    if (player->unk_28 & 0x40000000) {
                        func_8010B120_popgun_pickoff(i);
                    }
                    break;
                }
                if (player->unk_28 & 0x40000000) {
                    player->unk_24--;
                    break;
                }
                player->unk_24 = 0;
            }
        }
    }
}

void func_8010C4EC_popgun_pickoff(void) {
    s32 i;

    for (i = 0; i < D_8010DDF0_popgun_pickoff; i++) {
        func_8010B120_popgun_pickoff(i);
    }
    for (i = 0; i < 3; i++) {
        if (D_8010DDDC_popgun_pickoff[i] != NULL) {
            HuMemFree(D_8010DDDC_popgun_pickoff[i]);
        }
    }
    HuMemFree(D_8010DDD8_popgun_pickoff);
}
