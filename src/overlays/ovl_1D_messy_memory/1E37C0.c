#include "common.h"
#include "math.h"
#include "overlays/minigame.h"

// Sets the CPU cursor's movement direction towards its target position
// (unk1C, unk20): 1.0f moves negatively along an axis, 2.0f positively.
#define MM_CPU_STEER(work)                        \
    (work)->unk24 = 0.0f;                         \
    (work)->unk28 = 0.0f;                         \
    if ((work)->unk1C + 5.0f < (work)->unk44.x) { \
        (work)->unk24 = 1.0f;                     \
    }                                             \
    if ((work)->unk44.x < (work)->unk1C - 5.0f) { \
        (work)->unk24 = 2.0f;                     \
    }                                             \
    if ((work)->unk20 + 5.0f < (work)->unk44.y) { \
        (work)->unk28 = 1.0f;                     \
    }                                             \
    if ((work)->unk44.y < (work)->unk20 - 5.0f) { \
        (work)->unk28 = 2.0f;                     \
    }

// Whether the cursor is within 5 units of the given position on both axes.
#define MM_CPU_NEAR(work, posX, posY)                                        \
    ((posX) - 5.0f <= (work)->unk44.x && (posX) + 5.0f >= (work)->unk44.x && \
     (posY) - 5.0f <= (work)->unk44.y && (posY) + 5.0f >= (work)->unk44.y)

// Generic per-object work entry. The overlay keeps a pool of 0x88 of these in
// D_80111700_messy_memory; several sub-ranges of the pool have their own
// symbols (e.g. D_80113A94_messy_memory is entry 69).
typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ s16 unk42;
    /* 0x44 */ Vec unk44;
    /* 0x50 */ Vec unk50;
    /* 0x5C */ Vec unk5C;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ Vec unk78;
} MessyMemoryWork; // sizeof 0x84

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 fileId;
} MessyMemorySpriteEntry; // sizeof 0x8

typedef struct {
    /* 0x00 */ f32 scissorX;
    /* 0x04 */ f32 scissorY;
    /* 0x08 */ f32 scissorWidth;
    /* 0x0C */ f32 scissorHeight;
    /* 0x10 */ Vec viewportScale;
    /* 0x1C */ Vec viewportTranslate;
    /* 0x28 */ f32 fov;
} MessyMemoryCamera; // sizeof 0x2C

typedef struct {
    /* 0x00 */ s16 unk00;   // D_80115D70
    /* 0x02 */ u8 unk02[4]; // D_80115D72
    /* 0x06 */ u8 unk06[4]; // D_80115D76
} MessyMemoryBss5D70;       // sizeof 0xA

// Fields of messyMemoryBss5D70 (aliased in undefined_syms.txt).
extern s16 D_80115D70_messy_memory;
extern u8 D_80115D72_messy_memory[4];
extern u8 D_80115D76_messy_memory[4];

// Sub-ranges of the D_80111700_messy_memory work pool (aliased in undefined_syms.txt).
extern MessyMemoryWork D_80111910_messy_memory[2];
extern MessyMemoryWork D_80111A9C_messy_memory[1];
extern MessyMemoryWork D_801134E8_messy_memory[7];
extern MessyMemoryWork D_80113884_messy_memory[4];
extern MessyMemoryWork D_80113A94_messy_memory[1];
extern MessyMemoryWork D_80113B18_messy_memory[4];

extern const s16 D_801115F4_messy_memory[];

void func_80105B88_messy_memory(Gfx **gfxPos, s32 arg1, s32 arg2);
void func_8010622C_messy_memory(omObjData *obj);
void func_801063FC_messy_memory(omObjData *obj);
Gfx **func_80106620_messy_memory(Gfx **gfx);
Gfx **func_80106704_messy_memory(Gfx **gfx);
Gfx **func_801067D0_messy_memory(Gfx **gfx, u8 alpha);
void func_80106800_messy_memory(Gfx **gfxPos, s32 arg1, s32 arg2);
void func_80106C60_messy_memory(omObjData *obj);
void func_80107C88_messy_memory(omObjData *obj);
void func_8010ACE4_messy_memory(omObjData *obj);
void func_8010AD40_messy_memory(omObjData *obj);
void func_8010B32C_messy_memory(omObjData *obj);
void func_8010B5C8_messy_memory(omObjData *obj);
void func_8010C03C_messy_memory(omObjData *obj);
void func_8010C478_messy_memory(omObjData *obj);
void func_8010D55C_messy_memory(omObjData *obj);
void func_8010DA64_messy_memory(omObjData *obj);
void func_8010E29C_messy_memory(omObjData *obj);
void func_8010E654_messy_memory(omObjData *obj);
void func_8010EBB0_messy_memory(omObjData *obj);
void func_8010F04C_messy_memory(omObjData *obj);
void func_8010F19C_messy_memory(omObjData *obj);
void func_8010F3DC_messy_memory(omObjData *obj);
void func_8010F6E8_messy_memory(omObjData *obj);
void func_8010FA38_messy_memory(omObjData *obj);
void func_8010FDF0_messy_memory(omObjData *obj);
void func_801109BC_messy_memory(omObjData *obj);
void func_80110D50_messy_memory(void);
void func_80110EC4_messy_memory(void);

s32 D_80110FC0_messy_memory[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };

s16 D_80110FE0_messy_memory[5][2] = {
    { 0, 0 },
    { 144, 0 },
    { 0, 112 },
    { 144, 112 },
    { 0, 0 },
};

s16 D_80110FF4_messy_memory[20][2] = {
    { 46, 67 },
    { 112, 59 },
    { 160, 59 },
    { 208, 59 },
    { 274, 67 },
    { 46, 125 },
    { 112, 117 },
    { 160, 117 },
    { 208, 117 },
    { 274, 125 },
    { 72, 160 },
    { 122, 153 },
    { 176, 155 },
    { 222, 153 },
    { 264, 160 },
    { 52, 196 },
    { 102, 190 },
    { 146, 196 },
    { 204, 194 },
    { 248, 196 },
};

s16 D_80111044_messy_memory[20][2] = {
    { 31, 38 },
    { 64, 34 },
    { 88, 34 },
    { 112, 34 },
    { 145, 38 },
    { 31, 67 },
    { 64, 63 },
    { 88, 63 },
    { 112, 63 },
    { 145, 67 },
    { 44, 87 },
    { 69, 82 },
    { 96, 86 },
    { 119, 83 },
    { 140, 88 },
    { 34, 102 },
    { 59, 99 },
    { 81, 102 },
    { 110, 101 },
    { 132, 102 },
};

s16 D_80111094_messy_memory[4][2] = {
    { 46, 107 },
    { 70, 107 },
    { 95, 107 },
    { 121, 107 },
};

f32 D_801110A4_messy_memory[20][2] = {
    { 1.14f, 0.53f },
    { 0.48f, 0.61f },
    { 0.0f, 0.61f },
    { -0.48f, 0.61f },
    { -1.14f, 0.53f },
    { 1.14f, -0.05f },
    { 0.48f, 0.03f },
    { 0.0f, 0.03f },
    { -0.48f, 0.03f },
    { -1.14f, -0.05f },
    { 0.88f, -0.4f },
    { 0.38f, -0.33f },
    { -0.16f, -0.35f },
    { -0.62f, -0.33f },
    { -1.04f, -0.4f },
    { 1.08f, -0.76f },
    { 0.58f, -0.7f },
    { 0.14f, -0.76f },
    { -0.44f, -0.74f },
    { -0.88f, -0.76f },
};

s32 D_80111144_messy_memory = 0; /* Unreferenced. */

MessyMemorySpriteEntry D_80111148_messy_memory[10] = {
    { 0, 0x3E000F },
    { 0, 0x3E0010 },
    { 0, 0x3E0011 },
    { 0, 0x3E0012 },
    { 0, 0x3E0013 },
    { 0, 0x3E0014 },
    { 0, 0x3E0015 },
    { 0, 0x3E0016 },
    { 0, 0x3E0017 },
    { 0, 0x3E0018 },
};

MessyMemorySpriteEntry D_80111198_messy_memory[10] = {
    { 0, 0x3E0005 },
    { 0, 0x3E0006 },
    { 0, 0x3E0007 },
    { 0, 0x3E0008 },
    { 0, 0x3E0009 },
    { 0, 0x3E000A },
    { 0, 0x3E000B },
    { 0, 0x3E000C },
    { 0, 0x3E000D },
    { 0, 0x3E000E },
};

MessyMemorySpriteEntry D_801111E8_messy_memory[8] = {
    { 0, 0x6A },
    { 0, 0x6B },
    { 0, 0x6C },
    { 0, 0x6D },
    { 0, 0x6E },
    { 0, 0x6F },
    { 0, 0x70 },
    { 0, 0x71 },
};

f32 D_80111228_messy_memory[7][4] = {
    { -5.0f, -3.0f, -170.0f, 240.0f },
    { -5.0f, 2.5f, -170.0f, 120.0f },
    { -5.0f, -0.5f, -200.0f, 200.0f },
    { -5.0f, 0.5f, -200.0f, 160.0f },
    { -5.0f, -1.5f, -70.0f, 240.0f },
    { -5.0f, 0.0f, -130.0f, 180.0f },
    { -5.0f, 1.5f, -70.0f, 140.0f },
};

f32 D_80111298_messy_memory[4][2] = {
    { 10.0f, -300.0f },
    { -10.0f, 300.0f },
    { 10.0f, -250.0f },
    { -10.0f, 250.0f },
};

// x/y pairs
f32 D_801112B8_messy_memory[4][6] = {
    { 65.0f, 40.0f, 85.0f, 40.0f, 115.0f, 45.0f },
    { 210.0f, 40.0f, 230.0f, 40.0f, 260.0f, 45.0f },
    { 65.0f, 150.0f, 85.0f, 150.0f, 115.0f, 155.0f },
    { 210.0f, 150.0f, 230.0f, 150.0f, 260.0f, 155.0f },
};

char *D_80111318_messy_memory[8] = {
    "\x82\x6C\x82\x60\x82\x71\x82\x68\x82\x6E",                 // ＭＡＲＩＯ
    "\x82\x6B\x82\x74\x82\x68\x82\x66\x82\x68",                 // ＬＵＩＧＩ
    "\x82\x6F\x82\x64\x82\x60\x82\x62\x82\x67",                 // ＰＥＡＣＨ
    "\x82\x78\x82\x6E\x82\x72\x82\x67\x82\x68",                 // ＹＯＳＨＩ
    "\x82\x76\x82\x60\x82\x71\x82\x68\x82\x6E",                 // ＷＡＲＩＯ
    "\x82\x63\x82\x6E\x82\x6D\x82\x6A\x82\x64\x82\x78",         // ＤＯＮＫＥＹ
    "\x82\x76\x82\x60\x82\x6B\x82\x74\x82\x68\x82\x66\x82\x68", // ＷＡＬＵＩＧＩ
    "\x82\x63\x82\x60\x82\x68\x82\x72\x82\x78",                 // ＤＡＩＳＹ
}; /* Unreferenced. */

s16 D_80111338_messy_memory = 999;
s16 D_8011133A_messy_memory = 1000;
s16 D_8011133C_messy_memory = 40;

// Only the first two cameras are used.
MessyMemoryCamera D_80111340_messy_memory[4] = {
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 34.71f },
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 34.71f },
    { 0.0f, 120.0f, 160.0f, 240.0f, { 320.0f, 240.0f, 511.0f }, { 320.0f, 720.0f, 511.0f }, 45.0f },
    { 160.0f, 120.0f, 320.0f, 240.0f, { 320.0f, 240.0f, 511.0f }, { 960.0f, 720.0f, 511.0f }, 45.0f },
};

f32 D_80111600_messy_memory BSS;
u8 D_80111604_messy_memory[4] BSS; /* Unreferenced. */
s32 D_80111608_messy_memory[10] BSS;
u8 D_80111630_messy_memory[4] BSS;
s32 D_80111634_messy_memory BSS;
u8 D_80111638_messy_memory BSS;
u8 D_80111639_messy_memory BSS;
u8 D_8011163A_messy_memory BSS;
u8 D_8011163B_messy_memory BSS;
s32 D_8011163C_messy_memory BSS;
s32 D_80111640_messy_memory[4] BSS;
s16 D_80111650_messy_memory BSS;
HuSprAnimData *D_80111654_messy_memory BSS;
u8 D_80111658_messy_memory[4] BSS;
f32 D_8011165C_messy_memory BSS;
HuSprAnimData *D_80111660_messy_memory[4] BSS;
u8 D_80111670_messy_memory[4] BSS;
u8 D_80111674_messy_memory BSS;
u8 D_80111675_messy_memory BSS;
u8 D_80111678_messy_memory[4][10] BSS;
f32 D_801116A0_messy_memory BSS;
u8 D_801116A4_messy_memory[10] BSS;
u8 D_801116B0_messy_memory[40] BSS;
HuSprAnimData *D_801116D8_messy_memory BSS;
u8 D_801116DC_messy_memory[4] BSS; /* Unreferenced. */
u8 D_801116E0_messy_memory[20] BSS;
u8 D_801116F4_messy_memory[12] BSS; /* Unreferenced. */
MessyMemoryWork D_80111700_messy_memory[0x88] BSS;
f32 D_80115D20_messy_memory[10][2] BSS;
MessyMemoryBss5D70 messyMemoryBss5D70 BSS;
f32 D_80115D7C_messy_memory BSS;
u8 D_80115D80_messy_memory[4] BSS;
s16 D_80115D84_messy_memory[4] BSS;
u8 D_80115D8C_messy_memory BSS;
s16 D_80115D8E_messy_memory BSS;
u8 D_80115D90_messy_memory[10] BSS;
u8 D_80115D9A_messy_memory BSS;

void func_801059A0_messy_memory(void) {
    func_80110EC4_messy_memory();
}

f32 func_801059BC_messy_memory(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

void func_80105A3C_messy_memory(void) {
    MessyMemoryWork *work;
    u32 i;

    for (i = 0, work = D_80111700_messy_memory; i < 0x88; i++, work++) {
        work->obj = NULL;
        work->unk04 = 0;
        work->unk06 = 0;
        work->unk08 = 0;
        work->unk0A = 0;
        work->unk0C = 0;
        work->unk0E = 0;
        work->unk10 = 0;
        work->unk12 = 0;
        work->unk14 = 0;
        work->unk16 = 0;
        work->unk18 = 0;
        work->unk1C = 0;
        work->unk20 = 0;
        work->unk24 = 0;
        work->unk28 = 0;
        work->unk2C = 0;
        work->unk30 = 0;
        work->unk34 = 0;
        work->unk38 = 0;
        work->unk3C = 0;
        work->unk40 = -1;
        work->unk42 = -1;
        work->unk44.x = work->unk44.y = work->unk44.z = 0.0f;
        work->unk50.x = work->unk50.y = work->unk50.z = 0.0f;
        work->unk5C.x = work->unk5C.y = work->unk5C.z = 0.0f;
        work->unk68 = 0.0f;
        work->unk6C = 0.0f;
        work->unk70 = 0.0f;
        work->unk74 = 0.0f;
        work->unk78.x = work->unk78.y = work->unk78.z = 0.0f;
    }
}

void func_80105B04_messy_memory(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

void func_80105B7C_messy_memory(u8 arg0) {
    D_80115D8C_messy_memory = arg0;
}

void func_80105B88_messy_memory(Gfx **gfxPos, s32 arg1, s32 arg2) {
    Gfx *gfx = *gfxPos;
    s32 i;
    s32 x;
    s32 y;

    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gfx++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                                    G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gfx++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);
    gDPSetRenderMode(gfx++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);

    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(gfx++, 0, D_80111654_messy_memory->pal);
    for (i = 0, x = 0, y = 108; i < 24; i += 6) {
        gDPLoadTextureTile_4b(gfx++, D_80111654_messy_memory->data, G_IM_FMT_CI, 320, 24, 0, i, 320, i + 6, 0,
                              G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                              G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 320 << G_TEXTURE_IMAGE_FRAC, 6 << G_TEXTURE_IMAGE_FRAC);
        gSPTextureRectangle(gfx++, x << 2, (y + i) << 2, (x + 320) << 2, (y + i + 6) << 2, G_TX_RENDERTILE, 0, 0,
                            1 << 10, 1 << 10);
    }

    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(gfx++, 0, D_801116D8_messy_memory->pal);
    for (i = 0, x = 148, y = 0; i < 240; i += 16) {
        gDPLoadTextureTile_4b(gfx++, D_801116D8_messy_memory->data, G_IM_FMT_CI, 24, 240, 0, i, 24, i + 16, 0,
                              G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                              G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 24 << G_TEXTURE_IMAGE_FRAC, 16 << G_TEXTURE_IMAGE_FRAC);
        gSPTextureRectangle(gfx++, x << 2, (y + i) << 2, (x + 24) << 2, (y + i + 16) << 2, G_TX_RENDERTILE, 0, 0,
                            1 << 10, 1 << 10);
    }
    *gfxPos = gfx;
}

void func_801060E0_messy_memory(omObjData *obj) {
    switch (D_80115D8C_messy_memory) {
        case 8:
            func_8001C258_main(*obj->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            break;
        case 0xC:
            func_8001C258_main(*obj->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            break;
    }
}

void func_80106140_messy_memory(omObjData *obj) {
    *obj->model = Hu3DHookFuncCreate(0, func_80105B88_messy_memory, 2);
    Hu3DModelCameraSet(*obj->model, HU3D_CAM1);
    func_8001C258_main(*obj->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->func = func_801060E0_messy_memory;
}

void func_801061AC_messy_memory(void) {
    omObjData *obj;
    D_80111654_messy_memory = func_80055194_main(func_8000B838_main(0x3E0002));
    D_801116D8_messy_memory = func_80055194_main(func_8000B838_main(0x3E0004));
    obj = omAddObj(0xC8, 1, 0, -1, func_80106140_messy_memory);
    obj->work[0] = 0;
    D_80111A9C_messy_memory[0].obj = obj;
}

void func_8010622C_messy_memory(omObjData *obj) {
    MessyMemoryWork *work;

    switch (D_80115D8C_messy_memory) {
        case 4:
            if (obj->work[0] == 0) {
                espAttrReset(D_80111910_messy_memory[0].unk42, 0x4000);
            }
            break;
        case 5:
            if (obj->work[0] == 0) {
                work = &D_80111910_messy_memory[obj->work[0]];
                if (work->unk04 == 0) {
                    HuAudFXPlay(0x3F1);
                    work->unk04 = 1;
                }
                work->unk5C.x = work->unk5C.y = D_8011165C_messy_memory;
                espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
                if (work->unk5C.x <= 0.01 || work->unk5C.y <= 0.01) {
                    D_80115D9A_messy_memory = 5;
                    espDispOff(work->unk42);
                }
            }
            break;
        case 12:
            if (obj->work[0] == 0) {
                work = &D_80111910_messy_memory[obj->work[0]];
                work->unk5C.x = work->unk5C.y = D_8011165C_messy_memory;
                espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
                espDispOn(work->unk42);
                espAttrSet(work->unk42, 0x4000);
                if (work->unk5C.x >= 0.23f || work->unk5C.y >= 0.23f) {
                    D_80115D9A_messy_memory = 12;
                }
            }
            break;
    }
}

void func_801063FC_messy_memory(omObjData *obj) {
    MessyMemoryWork *work = &D_80111910_messy_memory[obj->work[0]];

    if (obj->work[0] == 0) {
        work->unk44.x = 160.0f;
        work->unk44.y = 120.0f;
        work->unk40 = func_8000B838_main(0x3E0000);
        work->unk42 = espEntry(work->unk40, 0, 0);
        espAttrSet(work->unk42, 0x4000);
        espPosSet(work->unk42, work->unk44.x, work->unk44.y);
        espPriSet(work->unk42, 0x5555);
    }
    if (obj->work[0] == 1) {
        work->unk44.x = 160.0f;
        work->unk44.y = 120.0f;
        work->unk40 = func_8000B838_main(0x3E0001);
        work->unk42 = espEntry(work->unk40, 0, 0);
        espAttrSet(work->unk42, 0x4000);
        espPosSet(work->unk42, work->unk44.x, work->unk44.y);
        espPriSet(work->unk42, 0xFFFF);
    }
    obj->func = func_8010622C_messy_memory;
}

void func_80106588_messy_memory(void) {
    MessyMemoryWork *work;
    omObjData *obj;
    u8 i;

    for (i = 0; i < 2; i++) {
        work = &D_80111910_messy_memory[i];
        obj = omAddObj(0x3B6, 0, 0, -1, func_801063FC_messy_memory);
        obj->work[0] = i;
        work->obj = obj;
    }
}

Gfx **func_80106620_messy_memory(Gfx **gfx) {
    u32 geometryMode = G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH;
    Gfx *gdl = *gfx;

    gDPPipeSync(gdl++);
    gDPSetCycleType(gdl++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gdl++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                                    G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gdl++, geometryMode);
    gDPSetCombineMode(gdl++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(gdl++, G_TP_NONE);
    gDPSetPrimColor(gdl++, 0, 0, 0, 0, 0, 255);
    gDPSetRenderMode(gdl++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    *gfx = gdl;
    return gfx;
}

Gfx **func_80106704_messy_memory(Gfx **gfx) {
    u32 geometryMode = G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH;
    Gfx *gdl = *gfx;

    gDPPipeSync(gdl++);
    gDPSetCycleType(gdl++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gdl++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                                    G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gdl++, geometryMode);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetTexturePersp(gdl++, G_TP_NONE);
    gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    *gfx = gdl;
    return gfx;
}

Gfx **func_801067D0_messy_memory(Gfx **gfx, u8 alpha) {
    Gfx *gdl = *gfx;

    gDPSetPrimColor(gdl++, 0, 0, 255, 255, 255, alpha);
    *gfx = gdl;
    return gfx;
}

void func_80106800_messy_memory(Gfx **gfxPos, s32 arg1, s32 arg2) {
    MessyMemoryWork *work;
    omObjData *obj;
    HuSprAnimPat *frame;
    Gfx *gfx;
    s32 height;
    s32 i;

    for (i = 0; i < 4; i++) {
        work = &D_80111700_messy_memory[i];
        obj = work->obj;
        if (obj->work[0] < 2) {
            if (work->unk44.y - 98.0f > 0.0f) {
                height = work->unk44.y - 98.0f;
            } else {
                height = 0;
            }
        } else {
            height = 0;
        }
        height = height * work->unk18;
        if (D_80111658_messy_memory[obj->work[0]] == 0) {
            continue;
        }
        if (D_80115D72_messy_memory[obj->work[0]] < 255) {
            gfxPos = func_801067D0_messy_memory(func_80106704_messy_memory(gfxPos),
                                                D_80115D72_messy_memory[obj->work[0]]);
        } else {
            gfxPos = func_80106620_messy_memory(gfxPos);
        }
        gfx = *gfxPos;
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
        gDPLoadTLUT_pal16(gfx++, 0, D_80111660_messy_memory[obj->work[0]]->pal);
        frame = &D_80111660_messy_memory[obj->work[0]]->pat[D_80111640_messy_memory[obj->work[0]]];
        gDPLoadTextureTile_4b(gfx++, frame->data, G_IM_FMT_CI, 32, 32, 0, 0, 32, 32 - height, 0, G_TX_NOMIRROR | G_TX_WRAP,
                              G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 32 << G_TEXTURE_IMAGE_FRAC, (32 - height) << G_TEXTURE_IMAGE_FRAC);
        gSPTextureRectangle(gfx++, (s32)(work->unk44.x - 8.0f + 16.0f - work->unk18 * 16.0f) << 2,
                            (s32)(work->unk44.y - 8.0f + 16.0f - work->unk18 * 16.0f) << 2,
                            (s32)(work->unk44.x - 8.0f + 16.0f + work->unk18 * 16.0f) << 2,
                            (s32)(work->unk44.y - 8.0f + 16.0f + work->unk18 * 16.0f - height) << 2, G_TX_RENDERTILE,
                            0, 0, (s32)(1024.0f / work->unk18), (s32)(1024.0f / work->unk18));
        *gfxPos = gfx;
    }
}

void func_80106C60_messy_memory(omObjData *obj) {
    u16 playerNo = obj->work[0];
    MessyMemoryWork *work = &D_80111700_messy_memory[playerNo];
    MessyMemoryWork *item;
    MessyMemoryWork *other;
    omObjData *itemObj;
    u8 outside;
    u8 blocked;
    u8 i;
    u8 j;
    u8 k;

    if (D_800D5558_main[GwPlayer[playerNo].pad] & Z_TRIG) {
        switch (D_80115D80_messy_memory[playerNo]) {
            case 0:
                D_80115D80_messy_memory[playerNo] = 1;
                break;
            case 1:
                D_80115D80_messy_memory[playerNo] = 2;
                break;
        }
    }
    if (D_80115D80_messy_memory[playerNo] != 0) {
        return;
    }
    outside = TRUE;
    blocked = FALSE;
    D_80115D72_messy_memory[obj->work[0]] = 0xFF;
    for (i = 0; i < 10; i++) {
        if (D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[playerNo][0] - 7.0f <= work->unk44.x &&
            D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[playerNo][0] + 7.0f >= work->unk44.x &&
            D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[playerNo][1] - 15.0f <= work->unk44.y &&
            D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[playerNo][1] + 6.0f >= work->unk44.y) {
            outside = FALSE;
        }
    }
    for (i = 10; i < 20; i++) {
        if (D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[playerNo][0] - 7.0f <= work->unk44.x &&
            D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[playerNo][0] + 7.0f >= work->unk44.x &&
            D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[playerNo][1] - 7.0f <= work->unk44.y &&
            D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[playerNo][1] + 6.0f >= work->unk44.y) {
            outside = FALSE;
        }
    }
    if (D_80111670_messy_memory[playerNo] == 1) {
        for (k = 0; k < 10; k++) {
            s32 base = playerNo * 10 + 8;

            item = &D_80111700_messy_memory[k + base];
            itemObj = item->obj;
            if (work->unk44.x == item->unk44.x && work->unk44.y == item->unk44.y) {
                for (i = 0; i < 10; i++) {
                    other = &D_80111700_messy_memory[i + base];
                    if (itemObj->work[1] * 10 + itemObj->work[0] == other->obj->work[1] * 10 + other->obj->work[0]) {
                        continue;
                    }
                    for (j = 0; j < 20; j++) {
                        if (D_80111044_messy_memory[j][0] + D_80110FE0_messy_memory[playerNo][0] <= other->unk44.x &&
                            D_80111044_messy_memory[j][0] + D_80110FE0_messy_memory[playerNo][0] >= other->unk44.x) {
                            if (j < 10) {
                                if (other->unk44.x - 7.0f <= work->unk44.x && other->unk44.x + 7.0f >= work->unk44.x &&
                                    other->unk44.y - 15.0f <= work->unk44.y && other->unk44.y + 6.0f >= work->unk44.y) {
                                    blocked = TRUE;
                                }
                            } else {
                                if (other->unk44.x - 7.0f <= work->unk44.x && other->unk44.x + 7.0f >= work->unk44.x &&
                                    other->unk44.y - 7.0f <= work->unk44.y && other->unk44.y + 6.0f >= work->unk44.y) {
                                    blocked = TRUE;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (outside | blocked) {
        D_80115D72_messy_memory[obj->work[0]] = 150;
    }
    if (D_800D5558_main[GwPlayer[playerNo].pad] & A_BUTTON) {
        switch (D_80111670_messy_memory[playerNo]) {
            case 0:
                for (k = 0; k < 10; k++) {
                    for (i = 0; i < 4; i++) {
                        s32 base = i * 10 + 8;

                        item = &D_80111700_messy_memory[k + base];
                        for (j = 0; j < 20; j++) {
                            if (D_80111044_messy_memory[j][0] + D_80110FE0_messy_memory[playerNo][0] <= item->unk44.x &&
                                D_80111044_messy_memory[j][0] + D_80110FE0_messy_memory[playerNo][0] >= item->unk44.x) {
                                if (j < 10) {
                                    if (item->unk44.x - 7.0f <= work->unk44.x && item->unk44.x + 7.0f >= work->unk44.x &&
                                        item->unk44.y - 15.0f <= work->unk44.y && item->unk44.y + 6.0f >= work->unk44.y) {
                                        D_801116B0_messy_memory[i * 10 + k] = 1;
                                        D_80111640_messy_memory[obj->work[0]] = 1;
                                        func_8004AC98_main(D_80111338_messy_memory, obj->work[0]);
                                        D_80111670_messy_memory[playerNo] = 1;
                                        omVibrate(playerNo, 5, 0, 5);
                                    }
                                } else {
                                    if (item->unk44.x - 7.0f <= work->unk44.x && item->unk44.x + 7.0f >= work->unk44.x &&
                                        item->unk44.y - 7.0f <= work->unk44.y && item->unk44.y + 6.0f >= work->unk44.y) {
                                        D_801116B0_messy_memory[i * 10 + k] = 1;
                                        D_80111640_messy_memory[obj->work[0]] = 1;
                                        func_8004AC98_main(D_80111338_messy_memory, obj->work[0]);
                                        D_80111670_messy_memory[playerNo] = 1;
                                        omVibrate(playerNo, 5, 0, 5);
                                    }
                                }
                            }
                        }
                    }
                }
                break;
            case 1:
                blocked = FALSE;
                for (k = 0; k < 10; k++) {
                    s32 base = playerNo * 10 + 8;

                    item = &D_80111700_messy_memory[k + base];
                    itemObj = item->obj;
                    if (work->unk44.x == item->unk44.x && work->unk44.y == item->unk44.y) {
                        for (i = 0; i < 10; i++) {
                            other = &D_80111700_messy_memory[i + base];
                            if (itemObj->work[1] * 10 + itemObj->work[0] == other->obj->work[1] * 10 + other->obj->work[0]) {
                                continue;
                            }
                            for (j = 0; j < 20; j++) {
                                if (D_80111044_messy_memory[j][0] + D_80110FE0_messy_memory[playerNo][0] <= other->unk44.x &&
                                    D_80111044_messy_memory[j][0] + D_80110FE0_messy_memory[playerNo][0] >= other->unk44.x) {
                                    if (j < 10) {
                                        if (other->unk44.x - 7.0f <= work->unk44.x && other->unk44.x + 7.0f >= work->unk44.x &&
                                            other->unk44.y - 15.0f <= work->unk44.y && other->unk44.y + 6.0f >= work->unk44.y) {
                                            blocked = TRUE;
                                        }
                                    } else {
                                        if (other->unk44.x - 7.0f <= work->unk44.x && other->unk44.x + 7.0f >= work->unk44.x &&
                                            other->unk44.y - 7.0f <= work->unk44.y && other->unk44.y + 6.0f >= work->unk44.y) {
                                            blocked = TRUE;
                                        }
                                    }
                                }
                            }
                        }

                        if (!blocked) {
                            for (i = 0; i < 10; i++) {
                                if (D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[playerNo][0] - 7.0f <= work->unk44.x &&
                                    D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[playerNo][0] + 7.0f >= work->unk44.x &&
                                    D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[playerNo][1] - 15.0f <= work->unk44.y &&
                                    D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[playerNo][1] + 6.0f >= work->unk44.y) {
                                    D_801116B0_messy_memory[obj->work[0] * 10 + k] = 0;
                                    item->unk44.x = D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[playerNo][0];
                                    item->unk44.y = D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[playerNo][1];
                                    D_80111640_messy_memory[obj->work[0]] = 0;
                                    func_8004AC98_main(D_8011133A_messy_memory, obj->work[0]);
                                    D_80111670_messy_memory[playerNo] = 0;
                                    omVibrate(playerNo, 2, 3, 10);
                                }
                            }
                            for (i = 10; i < 20; i++) {
                                if (D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[playerNo][0] - 7.0f <= work->unk44.x &&
                                    D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[playerNo][0] + 7.0f >= work->unk44.x &&
                                    D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[playerNo][1] - 7.0f <= work->unk44.y &&
                                    D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[playerNo][1] + 6.0f >= work->unk44.y) {
                                    D_801116B0_messy_memory[obj->work[0] * 10 + k] = 0;
                                    item->unk44.x = D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[playerNo][0];
                                    item->unk44.y = D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[playerNo][1];
                                    D_80111640_messy_memory[obj->work[0]] = 0;
                                    func_8004AC98_main(D_8011133A_messy_memory, obj->work[0]);
                                    D_80111670_messy_memory[playerNo] = 0;
                                    omVibrate(playerNo, 2, 3, 10);
                                }
                            }
                        }
                    }
                }
                break;
        }
    }
    if (D_800CBB6E_main[GwPlayer[playerNo].pad] < -29) {
        work->unk44.x -= 2.0f;
        if (work->unk44.x < D_80110FE0_messy_memory[playerNo][0] + 30.0f) {
            work->unk44.x = D_80110FE0_messy_memory[playerNo][0] + 30.0f;
        }
    }
    if (D_800CBB6E_main[GwPlayer[playerNo].pad] >= 30) {
        work->unk44.x += 2.0f;
        if (work->unk44.x > D_80110FE0_messy_memory[playerNo][0] + 140.0f) {
            work->unk44.x = D_80110FE0_messy_memory[playerNo][0] + 140.0f;
        }
    }
    if (D_800D20A1_main[GwPlayer[playerNo].pad] >= 30) {
        work->unk44.y -= 2.0f;
        if (work->unk44.y < D_80110FE0_messy_memory[playerNo][1] + 20.0f) {
            work->unk44.y = D_80110FE0_messy_memory[playerNo][1] + 20.0f;
        }
    }
    if (D_800D20A1_main[GwPlayer[playerNo].pad] < -29) {
        work->unk44.y += 2.0f;
        if (work->unk44.y > D_80110FE0_messy_memory[playerNo][1] + 108.0f) {
            work->unk44.y = D_80110FE0_messy_memory[playerNo][1] + 108.0f;
        }
    }
}

void func_80107C88_messy_memory(omObjData *obj) {
    u16 playerNo = obj->work[0];
    MessyMemoryWork *work = &D_80111700_messy_memory[playerNo];
    MessyMemoryWork *item;
    MessyMemoryWork *other;
    omObjData *itemObj;
    u8 outside;
    u8 blocked;
    u8 found;
    u8 slot;
    u8 i;
    u8 j;
    u8 k;

    if (work->unk14 >= 7) {
        if (work->unk12 == 0) {
            switch (GwPlayer[playerNo].cpu_difficulty) {
                case 0:
                    if (rand8() < 30) {
                        work->unk12 = 1;
                    }
                    break;
                case 1:
                    if (rand8() < 20) {
                        work->unk12 = 1;
                    }
                    break;
                case 2:
                    if (rand8() < 20) {
                        work->unk12 = 1;
                    }
                    break;
                case 3:
                    if (rand8() < 30) {
                        work->unk12 = 1;
                    }
                    break;
            }
        }
        if (work->unk12 == 2) {
            if (D_80115D8E_messy_memory == 300 || D_80115D8E_messy_memory == 210) {
                switch (GwPlayer[playerNo].cpu_difficulty) {
                    case 0:
                        if (rand8() < 250) {
                            work->unk12 = 3;
                        }
                        break;
                    case 1:
                        if (rand8() < 200) {
                            work->unk12 = 3;
                        }
                        break;
                    case 2:
                        if (rand8() < 150) {
                            work->unk12 = 3;
                        }
                        break;
                    case 3:
                        if (rand8() < 50) {
                            work->unk12 = 3;
                        }
                        break;
                }
            }
        }
        if (work->unk12 == 5) {
            switch (GwPlayer[playerNo].cpu_difficulty) {
                case 0:
                    if (rand8() < 250) {
                        work->unk12 = 6;
                    }
                    break;
                case 1:
                    if (rand8() < 250) {
                        work->unk12 = 6;
                    }
                    break;
                case 2:
                    if (rand8() < 250) {
                        work->unk12 = 6;
                    }
                    break;
                case 3:
                    if (rand8() < 250) {
                        work->unk12 = 6;
                    }
                    break;
            }
        }
    }
    if (work->unk12 == 1 || work->unk12 == 3 || work->unk12 == 6) {
        switch (D_80115D80_messy_memory[playerNo]) {
            case 0:
                D_80115D80_messy_memory[playerNo] = 1;
                work->unk12++;
                work->unk06 = 0;
                break;
            case 1:
                D_80115D80_messy_memory[playerNo] = 2;
                work->unk12++;
                work->unk06 = 0;
                break;
        }
    }
    if (D_80115D80_messy_memory[playerNo] != 0) {
        return;
    }
    outside = TRUE;
    blocked = FALSE;
    D_80115D72_messy_memory[obj->work[0]] = 0xFF;
    for (i = 0; i < 10; i++) {
        if (D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[playerNo][0] - 7.0f <= work->unk44.x &&
            D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[playerNo][0] + 7.0f >= work->unk44.x &&
            D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[playerNo][1] - 15.0f <= work->unk44.y &&
            D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[playerNo][1] + 6.0f >= work->unk44.y) {
            outside = FALSE;
        }
    }
    for (i = 10; i < 20; i++) {
        if (D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[playerNo][0] - 7.0f <= work->unk44.x &&
            D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[playerNo][0] + 7.0f >= work->unk44.x &&
            D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[playerNo][1] - 7.0f <= work->unk44.y &&
            D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[playerNo][1] + 6.0f >= work->unk44.y) {
            outside = FALSE;
        }
    }
    if (D_80111670_messy_memory[playerNo] == 1) {
        for (k = 0; k < 10; k++) {
            s32 base = playerNo * 10 + 8;

            item = &D_80111700_messy_memory[k + base];
            itemObj = item->obj;
            if (work->unk44.x == item->unk44.x && work->unk44.y == item->unk44.y) {
                for (i = 0; i < 10; i++) {
                    other = &D_80111700_messy_memory[i + base];
                    if (itemObj->work[1] * 10 + itemObj->work[0] == other->obj->work[1] * 10 + other->obj->work[0]) {
                        continue;
                    }
                    for (j = 0; j < 20; j++) {
                        if (D_80111044_messy_memory[j][0] + D_80110FE0_messy_memory[playerNo][0] <= other->unk44.x &&
                            D_80111044_messy_memory[j][0] + D_80110FE0_messy_memory[playerNo][0] >= other->unk44.x) {
                            if (j < 10) {
                                if (other->unk44.x - 7.0f <= work->unk44.x && other->unk44.x + 7.0f >= work->unk44.x &&
                                    other->unk44.y - 15.0f <= work->unk44.y && other->unk44.y + 6.0f >= work->unk44.y) {
                                    blocked = TRUE;
                                }
                            } else {
                                if (other->unk44.x - 7.0f <= work->unk44.x && other->unk44.x + 7.0f >= work->unk44.x &&
                                    other->unk44.y - 7.0f <= work->unk44.y && other->unk44.y + 6.0f >= work->unk44.y) {
                                    blocked = TRUE;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (outside | blocked) {
        D_80115D72_messy_memory[obj->work[0]] = 150;
    }

    if (work->unk12 == 0) {
        switch (work->unk06) {
            case 0:
                slot = rand8() % 10;
                item = &D_80111700_messy_memory[slot + 8 + playerNo * 10];
                if (D_80110FE0_messy_memory[playerNo][1] + 80.0f < item->unk44.y) {
                    work->unk08 = slot;
                    work->unk1C = item->unk44.x;
                    work->unk20 = item->unk44.y;
                    work->unk06 = 1;
                }
                if (work->unk06 != 1 && D_80111678_messy_memory[playerNo][slot] == 0 &&
                    D_80115D8E_messy_memory > 450) {
                    work->unk08 = slot;
                    work->unk1C = item->unk44.x;
                    work->unk20 = item->unk44.y;
                    work->unk06 = 10;
                }
                break;
            case 10:
                MM_CPU_STEER(work);
                item = &D_80111700_messy_memory[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, item->unk44.x, item->unk44.y)) {
                    work->unk06 = 0;
                }
                break;
            case 9:
                for (k = 0; k < 10; k++) {
                    if (k != work->unk08) {
                        item = &D_80111700_messy_memory[k + 8 + playerNo * 10];
                        if (D_80110FE0_messy_memory[playerNo][1] + 80.0f < item->unk44.y) {
                            work->unk08 = k;
                            work->unk1C = item->unk44.x;
                            work->unk20 = item->unk44.y;
                            work->unk06 = 1;
                        }
                    }
                }
                if (work->unk06 != 1) {
                    work->unk06 = 0;
                }
                break;
            case 1:
                MM_CPU_STEER(work);
                item = &D_80111700_messy_memory[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, item->unk44.x, item->unk44.y)) {
                    D_801116B0_messy_memory[playerNo * 10 + work->unk08] = 1;
                    D_80111640_messy_memory[obj->work[0]] = 1;
                    func_8004AC98_main(D_80111338_messy_memory, obj->work[0]);
                    D_80111670_messy_memory[playerNo] = 1;
                    if (D_80111678_messy_memory[playerNo][work->unk08] == 1) {
                        work->unk06 = 2;
                    } else {
                        work->unk06 = 3;
                    }
                }
                break;
            case 2:
                itemObj = D_80111700_messy_memory[work->unk08 + 8 + playerNo * 10].obj;
                for (k = 0; k < 10; k++) {
                    if (D_801116A4_messy_memory[k] == itemObj->work[0]) {
                        work->unk1C = D_80111044_messy_memory[k][0] + D_80110FE0_messy_memory[playerNo][0];
                        work->unk20 = D_80111044_messy_memory[k][1] + D_80110FE0_messy_memory[playerNo][1];
                        work->unk0A = k;
                        work->unk06 = 4;
                    }
                }
                break;
            case 3:
                item = &D_80111700_messy_memory[work->unk08 + 8 + playerNo * 10];
                itemObj = item->obj;
                slot = rand8() % 10;
                found = FALSE;
                for (k = 0; k < 10; k++) {
                    other = &D_80111700_messy_memory[k + 8 + playerNo * 10];
                    if (D_80111044_messy_memory[slot][0] + D_80110FE0_messy_memory[playerNo][0] == other->unk44.x &&
                        D_80111044_messy_memory[slot][1] + D_80110FE0_messy_memory[playerNo][1] == other->unk44.y) {
                        found = TRUE;
                    }
                }
                for (k = 0; k < 10; k++) {
                    if (D_80111678_messy_memory[playerNo][k] == 1 && D_801116A4_messy_memory[slot] == k) {
                        found = TRUE;
                    }
                }
                if (!found && D_801116A4_messy_memory[slot] != itemObj->work[0]) {
                    work->unk1C = D_80111044_messy_memory[slot][0] + D_80110FE0_messy_memory[playerNo][0];
                    work->unk20 = D_80111044_messy_memory[slot][1] + D_80110FE0_messy_memory[playerNo][1];
                    work->unk0A = slot;
                    work->unk06 = 4;
                    work->unk0E = 0;
                }
                if (!found && D_801116A4_messy_memory[slot] == itemObj->work[0] && work->unk14 >= 6) {
                    work->unk1C = D_80111044_messy_memory[10][0] + D_80110FE0_messy_memory[playerNo][0];
                    work->unk20 = D_80111044_messy_memory[10][1] + D_80110FE0_messy_memory[playerNo][1];
                    work->unk0A = slot;
                    work->unk0C = 10;
                    work->unk06 = 5;
                    work->unk0E = 0;
                }
                if (++work->unk0E >= 50) {
                    work->unk0E = 0;
                    work->unk06 = 9;
                    for (i = 0; i < 20; i++) {
                        if (D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[playerNo][0] - 7.0f <= work->unk44.x &&
                            D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[playerNo][0] + 7.0f >= work->unk44.x &&
                            D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[playerNo][1] - 7.0f <= work->unk44.y &&
                            D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[playerNo][1] + 6.0f >= work->unk44.y) {
                            D_801116B0_messy_memory[playerNo * 10 + work->unk08] = 0;
                            item->unk44.x = D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[playerNo][0];
                            item->unk44.y = D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[playerNo][1];
                            D_80111640_messy_memory[obj->work[0]] = 0;
                            func_8004AC98_main(D_8011133A_messy_memory, obj->work[0]);
                            D_80111670_messy_memory[playerNo] = 0;
                        }
                    }
                }
                break;
            case 4:
                MM_CPU_STEER(work);
                if (D_80115D8E_messy_memory > 150) {
                    switch (GwPlayer[playerNo].cpu_difficulty) {
                        case 0:
                            if (rand8() < 30) {
                                work->unk06 = 8;
                            }
                            break;
                        case 1:
                            if (rand8() < 7) {
                                work->unk06 = 8;
                            }
                            break;
                        case 2:
                            if (rand8() < 5) {
                                work->unk06 = 8;
                            }
                            break;
                        case 3:
                            if (rand8() < 3) {
                                work->unk06 = 8;
                            }
                            break;
                    }
                }
                item = &D_80111700_messy_memory[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, work->unk1C, work->unk20)) {
                    D_801116B0_messy_memory[playerNo * 10 + work->unk08] = 0;
                    D_80111640_messy_memory[obj->work[0]] = 0;
                    func_8004AC98_main(D_8011133A_messy_memory, obj->work[0]);
                    D_80111670_messy_memory[playerNo] = 0;
                    item->unk44.x = D_80111044_messy_memory[work->unk0A][0] + D_80110FE0_messy_memory[playerNo][0];
                    item->unk44.y = D_80111044_messy_memory[work->unk0A][1] + D_80110FE0_messy_memory[playerNo][1];
                    work->unk06 = 0;
                    work->unk14++;
                }
                break;
            case 8:
                if (++work->unk10 % 10 == 0) {
                    work->unk24 = 0.0f;
                    work->unk28 = 0.0f;
                    slot = rand8();
                    if (slot % 2 == 0) {
                        work->unk24 = 1.0f;
                    }
                    if (slot % 2 == 1) {
                        work->unk24 = 2.0f;
                    }
                    if (slot % 3 == 0) {
                        work->unk28 = 1.0f;
                    }
                    if (slot % 3 == 1) {
                        work->unk28 = 2.0f;
                    }
                }
                if (work->unk10 > 30) {
                    work->unk10 = 0;
                    work->unk06 = 4;
                }
                break;
            case 5:
                MM_CPU_STEER(work);
                item = &D_80111700_messy_memory[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, work->unk1C, work->unk20)) {
                    D_801116B0_messy_memory[playerNo * 10 + work->unk08] = 0;
                    D_80111640_messy_memory[obj->work[0]] = 0;
                    func_8004AC98_main(D_8011133A_messy_memory, obj->work[0]);
                    D_80111670_messy_memory[playerNo] = 0;
                    item->unk44.x = D_80111044_messy_memory[work->unk0C][0] + D_80110FE0_messy_memory[playerNo][0];
                    item->unk44.y = D_80111044_messy_memory[work->unk0C][1] + D_80110FE0_messy_memory[playerNo][1];
                    work->unk06 = 6;
                }
                break;
            case 6:
                slot = rand8() % 10;
                item = &D_80111700_messy_memory[slot + 8 + playerNo * 10];
                if (item->unk44.y < D_80110FE0_messy_memory[playerNo][1] + 80.0f &&
                    D_80111678_messy_memory[playerNo][slot] != 1) {
                    work->unk08 = slot;
                    work->unk1C = item->unk44.x;
                    work->unk20 = item->unk44.y;
                    work->unk06 = 7;
                }
                break;
            case 7:
                MM_CPU_STEER(work);
                item = &D_80111700_messy_memory[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, item->unk44.x, item->unk44.y)) {
                    D_801116B0_messy_memory[playerNo * 10 + work->unk08] = 1;
                    D_80111640_messy_memory[obj->work[0]] = 1;
                    func_8004AC98_main(D_80111338_messy_memory, obj->work[0]);
                    D_80111670_messy_memory[playerNo] = 1;
                    work->unk1C = D_80111044_messy_memory[work->unk0A][0] + D_80110FE0_messy_memory[playerNo][0];
                    work->unk20 = D_80111044_messy_memory[work->unk0A][1] + D_80110FE0_messy_memory[playerNo][1];
                    work->unk06 = 4;
                    work->unk14--;
                }
                break;
        }
    }

    if (work->unk12 == 4) {
        switch (work->unk06) {
            case 0:
                slot = rand8() % 10;
                item = &D_80111700_messy_memory[slot + 8 + playerNo * 10];
                if (item->unk44.y < D_80110FE0_messy_memory[playerNo][1] + 80.0f) {
                    work->unk08 = slot;
                    work->unk38 = work->unk1C = item->unk44.x;
                    work->unk3C = work->unk20 = item->unk44.y;
                    work->unk06 = 1;
                }
                break;
            case 1:
                MM_CPU_STEER(work);
                item = &D_80111700_messy_memory[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, item->unk44.x, item->unk44.y)) {
                    D_801116B0_messy_memory[playerNo * 10 + work->unk08] = 1;
                    D_80111640_messy_memory[obj->work[0]] = 1;
                    func_8004AC98_main(D_80111338_messy_memory, obj->work[0]);
                    D_80111670_messy_memory[playerNo] = 1;
                    work->unk14--;
                    work->unk06 = 2;
                }
                break;
            case 2:
                slot = rand8() % 10;
                work->unk1C = D_80111044_messy_memory[slot + 10][0] + D_80110FE0_messy_memory[playerNo][0];
                work->unk20 = D_80111044_messy_memory[slot + 10][1] + D_80110FE0_messy_memory[playerNo][1];
                work->unk0A = slot + 10;
                work->unk06 = 3;
                break;
            case 3:
                MM_CPU_STEER(work);
                item = &D_80111700_messy_memory[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, work->unk1C, work->unk20)) {
                    D_801116B0_messy_memory[playerNo * 10 + work->unk08] = 0;
                    D_80111640_messy_memory[obj->work[0]] = 0;
                    func_8004AC98_main(D_8011133A_messy_memory, obj->work[0]);
                    D_80111670_messy_memory[playerNo] = 0;
                    item->unk44.x = D_80111044_messy_memory[work->unk0A][0] + D_80110FE0_messy_memory[playerNo][0];
                    item->unk44.y = D_80111044_messy_memory[work->unk0A][1] + D_80110FE0_messy_memory[playerNo][1];
                    work->unk06 = 4;
                }
                break;
            case 4:
                slot = rand8() % 10;
                item = &D_80111700_messy_memory[slot + 8 + playerNo * 10];
                if (item->unk44.y < D_80110FE0_messy_memory[playerNo][1] + 80.0f) {
                    work->unk08 = slot;
                    work->unk1C = item->unk44.x;
                    work->unk20 = item->unk44.y;
                    work->unk06 = 5;
                }
                break;
            case 5:
                MM_CPU_STEER(work);
                item = &D_80111700_messy_memory[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, item->unk44.x, item->unk44.y)) {
                    D_801116B0_messy_memory[playerNo * 10 + work->unk08] = 1;
                    D_80111640_messy_memory[obj->work[0]] = 1;
                    func_8004AC98_main(D_80111338_messy_memory, obj->work[0]);
                    D_80111670_messy_memory[playerNo] = 1;
                    work->unk14--;
                    work->unk06 = 6;
                }
                break;
            case 6:
                for (k = 0; k < 10; k++) {
                    if (work->unk38 == D_80111044_messy_memory[k][0] + D_80110FE0_messy_memory[playerNo][0] &&
                        work->unk3C == D_80111044_messy_memory[k][1] + D_80110FE0_messy_memory[playerNo][1]) {
                        work->unk1C = D_80111044_messy_memory[k][0] + D_80110FE0_messy_memory[playerNo][0];
                        work->unk20 = D_80111044_messy_memory[k][1] + D_80110FE0_messy_memory[playerNo][1];
                        work->unk0A = k;
                        work->unk06 = 7;
                    }
                }
                break;
            case 7:
                MM_CPU_STEER(work);
                item = &D_80111700_messy_memory[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, work->unk1C, work->unk20)) {
                    D_801116B0_messy_memory[playerNo * 10 + work->unk08] = 0;
                    D_80111640_messy_memory[obj->work[0]] = 0;
                    func_8004AC98_main(D_8011133A_messy_memory, obj->work[0]);
                    D_80111670_messy_memory[playerNo] = 0;
                    item->unk44.x = D_80111044_messy_memory[work->unk0A][0] + D_80110FE0_messy_memory[playerNo][0];
                    item->unk44.y = D_80111044_messy_memory[work->unk0A][1] + D_80110FE0_messy_memory[playerNo][1];
                    work->unk06 = 8;
                    work->unk14++;
                }
                break;
            case 8:
                for (k = 0; k < 10; k++) {
                    item = &D_80111700_messy_memory[k + 8 + playerNo * 10];
                    if (D_80110FE0_messy_memory[playerNo][1] + 80.0f < item->unk44.y) {
                        work->unk08 = k;
                        work->unk1C = item->unk44.x;
                        work->unk20 = item->unk44.y;
                        work->unk06 = 9;
                    }
                }
                break;
            case 9:
                MM_CPU_STEER(work);
                item = &D_80111700_messy_memory[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, item->unk44.x, item->unk44.y)) {
                    D_801116B0_messy_memory[playerNo * 10 + work->unk08] = 1;
                    D_80111640_messy_memory[obj->work[0]] = 1;
                    func_8004AC98_main(D_80111338_messy_memory, obj->work[0]);
                    D_80111670_messy_memory[playerNo] = 1;
                    work->unk06 = 10;
                }
                break;
            case 10:
                for (k = 0; k < 10; k++) {
                    found = FALSE;
                    for (i = 0; i < 10; i++) {
                        other = &D_80111700_messy_memory[i + 8 + playerNo * 10];
                        if (D_80111044_messy_memory[k][0] + D_80110FE0_messy_memory[playerNo][0] == other->unk44.x &&
                            D_80111044_messy_memory[k][1] + D_80110FE0_messy_memory[playerNo][1] == other->unk44.y) {
                            found = TRUE;
                        }
                    }
                    if (!found) {
                        work->unk1C = D_80111044_messy_memory[k][0] + D_80110FE0_messy_memory[playerNo][0];
                        work->unk20 = D_80111044_messy_memory[k][1] + D_80110FE0_messy_memory[playerNo][1];
                        work->unk0A = k;
                        work->unk06 = 11;
                    }
                }
                break;
            case 11:
                MM_CPU_STEER(work);
                item = &D_80111700_messy_memory[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, work->unk1C, work->unk20)) {
                    D_801116B0_messy_memory[playerNo * 10 + work->unk08] = 0;
                    D_80111640_messy_memory[obj->work[0]] = 0;
                    func_8004AC98_main(D_8011133A_messy_memory, obj->work[0]);
                    D_80111670_messy_memory[playerNo] = 0;
                    item->unk44.x = D_80111044_messy_memory[work->unk0A][0] + D_80110FE0_messy_memory[playerNo][0];
                    item->unk44.y = D_80111044_messy_memory[work->unk0A][1] + D_80110FE0_messy_memory[playerNo][1];
                    work->unk06 = 12;
                    work->unk14++;
                    work->unk12 = 5;
                }
                break;
        }
    }

    if (work->unk24 == 1.0f) {
        work->unk44.x -= 2.0f;
        if (work->unk44.x < D_80110FE0_messy_memory[playerNo][0] + 30.0f) {
            work->unk44.x = D_80110FE0_messy_memory[playerNo][0] + 30.0f;
        }
    }
    if (work->unk24 == 2.0f) {
        work->unk44.x += 2.0f;
        if (work->unk44.x > D_80110FE0_messy_memory[playerNo][0] + 140.0f) {
            work->unk44.x = D_80110FE0_messy_memory[playerNo][0] + 140.0f;
        }
    }
    if (work->unk28 == 1.0f) {
        work->unk44.y -= 2.0f;
        if (work->unk44.y < D_80110FE0_messy_memory[playerNo][1] + 20.0f) {
            work->unk44.y = D_80110FE0_messy_memory[playerNo][1] + 20.0f;
        }
    }
    if (work->unk28 == 2.0f) {
        work->unk44.y += 2.0f;
        if (work->unk44.y > D_80110FE0_messy_memory[playerNo][1] + 108.0f) {
            work->unk44.y = D_80110FE0_messy_memory[playerNo][1] + 108.0f;
        }
    }
}

void func_8010ACE4_messy_memory(omObjData *obj) {
    s32 playerIndex = (u16)obj->work[0];

    if (D_80115D8C_messy_memory == 9) {
        switch (GwPlayer[playerIndex].cpu_difficulty) {
            case 0:
            case 1:
            case 2:
            case 3:
                func_80107C88_messy_memory(obj);
                break;
        }
    }
}

void func_8010AD40_messy_memory(omObjData *obj) {
    u16 playerNo = obj->work[0];
    MessyMemoryWork *work = &D_80111700_messy_memory[playerNo];
    s8 found;
    s8 count;
    s8 i;
    s8 j;
    s8 chance;

    switch (D_80115D8C_messy_memory) {
        case 8:
            D_80111658_messy_memory[obj->work[0]] = 1;
            work->unk18 += 0.05;
            if (work->unk18 > 1.0f) {
                work->unk18 = 1.0f;
            }
            if ((GwPlayer[playerNo].stat & 1) && work->unk16 == 0) {
                work->unk16 = 1;
                count = 0;
                chance = rand8() % 100;
                if (GwPlayer[playerNo].cpu_difficulty == 0) {
                    if (chance > 0 && chance < 30) {
                        work->unk04 = 0;
                    }
                    if (chance >= 30 && chance < 80) {
                        work->unk04 = 1;
                    }
                    if (chance >= 80 && chance < 90) {
                        work->unk04 = 2;
                    }
                    if (chance >= 90 && chance < 95) {
                        work->unk04 = 3;
                    }
                    if (chance >= 95 && chance < 98) {
                        work->unk04 = 4;
                    }
                    if (chance >= 98 && chance < 100) {
                        work->unk04 = 5;
                    }
                }
                if (GwPlayer[playerNo].cpu_difficulty == 1) {
                    if (chance > 0 && chance < 10) {
                        work->unk04 = 0;
                    }
                    if (chance >= 10 && chance < 40) {
                        work->unk04 = 1;
                    }
                    if (chance >= 40 && chance < 65) {
                        work->unk04 = 2;
                    }
                    if (chance >= 65 && chance < 85) {
                        work->unk04 = 3;
                    }
                    if (chance >= 85 && chance < 95) {
                        work->unk04 = 4;
                    }
                    if (chance >= 95 && chance < 100) {
                        work->unk04 = 5;
                    }
                }
                if (GwPlayer[playerNo].cpu_difficulty == 2) {
                    if (chance >= 0 && chance < 10) {
                        work->unk04 = 1;
                    }
                    if (chance >= 10 && chance < 30) {
                        work->unk04 = 2;
                    }
                    if (chance >= 30 && chance < 55) {
                        work->unk04 = 3;
                    }
                    if (chance >= 55 && chance < 80) {
                        work->unk04 = 4;
                    }
                    if (chance >= 80 && chance < 95) {
                        work->unk04 = 5;
                    }
                    if (chance >= 95 && chance < 100) {
                        work->unk04 = 7;
                    }
                }
                if (GwPlayer[playerNo].cpu_difficulty == 3) {
                    if (chance > 0 && chance < 5) {
                        work->unk04 = 2;
                    }
                    if (chance >= 5 && chance < 15) {
                        work->unk04 = 3;
                    }
                    if (chance >= 15 && chance < 30) {
                        work->unk04 = 4;
                    }
                    if (chance >= 30 && chance < 80) {
                        work->unk04 = 5;
                    }
                    if (chance >= 80 && chance < 100) {
                        work->unk04 = 7;
                    }
                }
                for (i = 0; i < 10; i++) {
                    for (j = 0; j < 10; j++) {
                        if (D_801116E0_messy_memory[j] == i) {
                            D_80111678_messy_memory[playerNo][i] = 1;
                        }
                    }
                }
                for (i = 9; i >= 0; i--) {
                    found = FALSE;
                    if (count >= work->unk04) {
                        break;
                    }
                    for (j = 0; j < 10; j++) {
                        if (D_801116E0_messy_memory[j] == i) {
                            found = TRUE;
                        }
                    }
                    if (!found && D_80111678_messy_memory[playerNo][i] != 1) {
                        D_80111678_messy_memory[playerNo][i] = 1;
                        count++;
                    }
                }
            }
            break;
        case 9:
            if (D_80115D8E_messy_memory > 0) {
                if (GwPlayer[playerNo].stat & 1) {
                    func_8010ACE4_messy_memory(obj);
                } else {
                    func_80106C60_messy_memory(obj);
                }
            }
            break;
        case 11:
            work->unk18 -= 0.03;
            if (work->unk18 <= 0.05f) {
                work->unk18 = 0.05f;
                D_80111658_messy_memory[obj->work[0]] = 0;
            }
            break;
    }
}

void func_8010B32C_messy_memory(omObjData *obj) {
    s32 chr = GwPlayer[obj->work[0]].chr;
    MessyMemoryWork *work = &D_80111700_messy_memory[obj->work[0]];
    s16 i;

    work->unk40 = func_8000B838_main(D_801111E8_messy_memory[chr].fileId);
    D_80111660_messy_memory[obj->work[0]] = func_80055194_main(work->unk40);
    for (i = 0; i < 4; i++) {
        if (obj->work[0] == i) {
            work->unk44.x = D_80110FE0_messy_memory[obj->work[0]][0] + 88.0f;
            work->unk44.y = D_80110FE0_messy_memory[obj->work[0]][1] + 63.0f;
        }
    }
    work->unk5C.x = work->unk5C.y = work->unk18 = 0.1f;
    D_80115D72_messy_memory[obj->work[0]] = 0xFF;
    D_80111658_messy_memory[obj->work[0]] = 0;
    if (obj->work[0] == 3) {
        Hu3DModelCameraSet(Hu3DHookFuncCreate(0, func_80106800_messy_memory, 2), HU3D_CAM0);
    }
    obj->func = func_8010AD40_messy_memory;
}

void func_8010B4CC_messy_memory(void) {
    s32 unused[2]; // Unreferenced, but present in the stack frame.
    MessyMemoryWork *work;
    omObjData *obj;
    s32 playerNo;
    s16 i;

    for (i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                playerNo = 0;
                break;
            case 1:
                playerNo = 1;
                break;
            case 2:
                playerNo = 2;
                break;
            case 3:
                playerNo = 3;
                break;
            default:
                playerNo = 0;
                break;
        }
        work = &D_80111700_messy_memory[i];
        obj = omAddObj(0x96, 4, 1, -1, func_8010B32C_messy_memory);
        obj->work[0] = playerNo;
        work->obj = obj;
    }
}

void func_8010B5C8_messy_memory(omObjData *obj) {
    u16 index = obj->work[0];
    MessyMemoryWork *work = &D_80113B18_messy_memory[obj->work[0]];
    s16 near;
    s16 i;

    switch (D_80115D8C_messy_memory) {
        case 5:
            func_8001C258_main(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            break;
        case 6:
            func_8001C258_main(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            switch (work->unk04) {
                case 0:
                    func_8001C5B4_main(*obj->model, obj->motion[2]);
                    work->unk04 = 1;
                    break;
                case 1:
                    if (index == 0 || index == 2) {
                        obj->rot.y = func_801059BC_messy_memory(obj->rot.y, 20.0f);
                    } else {
                        obj->rot.y = func_801059BC_messy_memory(obj->rot.y, -20.0f);
                    }
                    if ((s16)obj->rot.y == 180) {
                        work->unk04 = 2;
                        obj->rot.y = 180.0f;
                        func_8001C5B4_main(*obj->model, obj->motion[0]);
                    }
                    break;
                case 2:
                    work->unk08++;
                    if (work->unk08 >= 5) {
                        work->unk04 = 3;
                        func_8001C5B4_main(*obj->model, obj->motion[5]);
                        PlayerFXPlay(0x286, obj->work[0]);
                    }
                    break;
                case 3:
                    if (Hu3DData[*obj->model].motTime >= D_800CCF58_main[Hu3DData[*obj->model].motId].unk02) {
                        work->unk04 = 4;
                        func_8001C5B4_main(*obj->model, obj->motion[2]);
                        func_8001C814_main(*obj->model, 2, 2);
                    }
                    break;
                case 4:
                    if (index == 0 || index == 2) {
                        obj->rot.y = func_801059BC_messy_memory(obj->rot.y, 15.0f);
                    } else {
                        obj->rot.y = func_801059BC_messy_memory(obj->rot.y, -15.0f);
                    }
                    if ((s16)obj->rot.y == 90 || (s16)obj->rot.y == 270) {
                        work->unk04 = 5;
                    }
                    break;
                case 5:
                    obj->trans.x -= D_80111298_messy_memory[index][0];
                    if (obj->work[0] == 3) {
                        near = FALSE;
                        for (i = 0; i < 4; i++) {
                            if (abs((&D_80113B18_messy_memory[i])->obj->trans.x) < 651) {
                                near = TRUE;
                            }
                        }
                        if (!near) {
                            D_80115D9A_messy_memory = 6;
                            for (i = 0; i < 4; i++) {
                                func_8001C258_main(*(&D_80113B18_messy_memory[i])->obj->model, HU3D_ATTR_DISPOFF,
                                                   HU3D_ATTR_DISPOFF);
                            }
                        }
                    }
                    break;
            }
            break;
        case 13:
            switch (index) {
                case 0:
                    obj->trans.x = -650.0f;
                    obj->trans.y = -180.0f;
                    obj->trans.z = -1000.0f;
                    obj->rot.y = 90.0f;
                    break;
                case 1:
                    obj->trans.x = 650.0f;
                    obj->trans.y = -180.0f;
                    obj->trans.z = -1000.0f;
                    obj->rot.y = 270.0f;
                    break;
                case 2:
                    obj->trans.x = -650.0f;
                    obj->trans.y = -435.0f;
                    obj->trans.z = -610.0f;
                    obj->rot.y = 90.0f;
                    break;
                case 3:
                    obj->trans.x = 650.0f;
                    obj->trans.y = -435.0f;
                    obj->trans.z = -610.0f;
                    obj->rot.y = 270.0f;
                    break;
            }
            obj->rot.x = 0.0f;
            obj->rot.z = 0.0f;
            Hu3DModelRotSet(*obj->model, obj->rot.x, obj->rot.y, obj->rot.z);
            work->unk04 = 0;
            break;
        case 14:
            func_8001C258_main(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            switch (work->unk04) {
                case 0:
                    obj->trans.x += D_80111298_messy_memory[index][0];
                    if (work->unk06 >= 8) {
                        if (D_80115D84_messy_memory[obj->work[0]] != -1) {
                            HuAudFXStop(D_80115D84_messy_memory[obj->work[0]]);
                        }
                        D_80115D84_messy_memory[obj->work[0]] = PlayerFXPlay(D_8011133C_messy_memory, obj->work[0]);
                        work->unk06 = 0;
                    } else {
                        work->unk06++;
                    }
                    if (abs(obj->trans.x) <= abs(D_80111298_messy_memory[index][1])) {
                        obj->trans.x = D_80111298_messy_memory[index][1];
                        work->unk04 = 1;
                        func_8001C5B4_main(*obj->model, obj->motion[1]);
                    }
                    break;
                case 1:
                    if (obj->rot.y >= 270.0f) {
                        obj->rot.y = func_801059BC_messy_memory(obj->rot.y, 15.0f);
                    } else if (obj->rot.y <= 90.0f) {
                        obj->rot.y = func_801059BC_messy_memory(obj->rot.y, -15.0f);
                    }
                    if ((s16)obj->rot.y == 0) {
                        work->unk04 = 2;
                        func_8001C5B4_main(*obj->model, obj->motion[0]);
                        if (index == 3) {
                            D_80115D9A_messy_memory = 14;
                        }
                    }
                    break;
            }
            break;
        case 16:
            if (D_80115D8E_messy_memory >= 0 && work->unk04 == 2) {
                if (D_8011163B_messy_memory == 0) {
                    if (index == D_80111630_messy_memory[0]) {
                        func_8001C5B4_main(*obj->model, obj->motion[3]);
                        func_80045ED0_main((D_80110FC0_messy_memory[GwPlayer[obj->work[0]].chr] << 16) | 0x2F);
                    } else {
                        func_8001C5B4_main(*obj->model, obj->motion[4]);
                    }
                }
                if (D_8011163B_messy_memory == 1) {
                    if (index == D_80111630_messy_memory[0] || index == D_80111630_messy_memory[1]) {
                        func_8001C5B4_main(*obj->model, obj->motion[3]);
                        func_80045ED0_main((D_80110FC0_messy_memory[GwPlayer[obj->work[0]].chr] << 16) | 0x2F);
                    } else {
                        func_8001C5B4_main(*obj->model, obj->motion[4]);
                    }
                }
                if (D_8011163B_messy_memory == 2) {
                    if (index == D_80111630_messy_memory[0] || index == D_80111630_messy_memory[1] ||
                        index == D_80111630_messy_memory[2]) {
                        func_8001C5B4_main(*obj->model, obj->motion[3]);
                        func_80045ED0_main((D_80110FC0_messy_memory[GwPlayer[obj->work[0]].chr] << 16) | 0x2F);
                    } else {
                        func_8001C5B4_main(*obj->model, obj->motion[4]);
                    }
                }
                if (D_8011163B_messy_memory == 3) {
                    func_8001C5B4_main(*obj->model, obj->motion[3]);
                    func_80045ED0_main((D_80110FC0_messy_memory[GwPlayer[obj->work[0]].chr] << 16) | 0x2F);
                }
                if (D_8011163B_messy_memory == 4) {
                    func_8001C5B4_main(*obj->model, obj->motion[4]);
                }
                work->unk04 = 3;
            }
            break;
    }
    if (GwPlayer[obj->work[0]].chr != 5) {
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y - 5.0f, obj->trans.z);
    } else {
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y - 10.0f, obj->trans.z + 30.0f);
    }
}

void func_8010C03C_messy_memory(omObjData *obj) {
    u32 playerNo = obj->work[0];
    u16 index = obj->work[0];
    s8 chr = GwPlayer[playerNo].chr;

    *obj->model = func_8000B108_main(D_800A1788_main[chr].model | D_800A1788_main[chr].motion[0], 0x2A9);
    Hu3DModelRemakeStatic(*obj->model);
    func_8001C514_main(*obj->model);
    obj->model[1] = func_8000B0A0_main(0, 0x14C9);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80088800_main(Hu3DData[obj->model[1]].mtx, 0.0f, 15.0f, 0.0f);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 2));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x36));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x7A));
    func_8001C5B4_main(*obj->model, *obj->motion);
    Hu3DMotionTimeSet(*obj->model, 0.0f);
    func_8001C814_main(*obj->model, 2, 2);
    switch (index) {
        case 0:
        case 1:
            obj->trans.x = D_80111298_messy_memory[index][1];
            obj->trans.y = -180.0f;
            obj->trans.z = -1000.0f;
            break;
        case 2:
        case 3:
            obj->trans.x = D_80111298_messy_memory[index][1];
            obj->trans.y = -435.0f;
            obj->trans.z = -610.0f;
            break;
    }
    obj->rot.x = 0.0f;
    obj->rot.y = 0.0f;
    obj->rot.z = 0.0f;
    Hu3DModelRotSet(*obj->model, obj->rot.x, obj->rot.y, obj->rot.z);
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    Hu3DModelScaleSet(*obj->model, obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelPosSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    func_8001C258_main(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM0);
    obj->func = func_8010B5C8_messy_memory;
}

void func_8010C37C_messy_memory(void) {
    s32 unused[2]; // Unreferenced, but present in the stack frame.
    MessyMemoryWork *work;
    omObjData *obj;
    s32 playerNo;
    s16 i;

    for (i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                playerNo = 0;
                break;
            case 1:
                playerNo = 1;
                break;
            case 2:
                playerNo = 2;
                break;
            case 3:
                playerNo = 3;
                break;
            default:
                playerNo = 0;
                break;
        }
        work = &D_80113B18_messy_memory[i];
        obj = omAddObj(0x352, 9, 0x3C, -1, func_8010C03C_messy_memory);
        obj->work[0] = playerNo;
        work->obj = obj;
    }
}

void func_8010C478_messy_memory(omObjData *obj) {
    MessyMemoryWork *work = &D_80111700_messy_memory[obj->work[0] + 8 + obj->work[1] * 10];
    MessyMemoryWork *marker;
    MessyMemoryWork *cursor;
    u8 found;
    u8 slot;
    u8 i;
    u8 j;

    switch (D_80115D8C_messy_memory) {
        case 2:
            D_80111674_messy_memory = 7;
            break;
        case 3:
            if (obj->work[1] == 4 && D_80115D90_messy_memory[obj->work[0]] == 10 &&
                D_80111638_messy_memory < D_80111674_messy_memory) {
                slot = rand8() % 10;
                if (slot != D_80115D90_messy_memory[0] && slot != D_80115D90_messy_memory[1] &&
                    slot != D_80115D90_messy_memory[2] && slot != D_80115D90_messy_memory[3] &&
                    slot != D_80115D90_messy_memory[4] && slot != D_80115D90_messy_memory[5] &&
                    slot != D_80115D90_messy_memory[6] && slot != D_80115D90_messy_memory[7] &&
                    slot != D_80115D90_messy_memory[8] && slot != D_80115D90_messy_memory[9]) {
                    D_80115D90_messy_memory[obj->work[0]] = slot;
                    D_80111638_messy_memory++;
                    for (i = 0; i < 10; i++) {
                        if (slot == i) {
                            work->unk44.x = D_80110FF4_messy_memory[slot + 10][0];
                            work->unk44.y = D_80110FF4_messy_memory[slot + 10][1];
                        }
                    }
                }
            }
            if (D_80111638_messy_memory >= D_80111674_messy_memory) {
                if (obj->work[1] == 4) {
                    espPriSet(work->unk42, 0x1111);
                    espPosSet(work->unk42, work->unk44.x, work->unk44.y);
                }
                for (i = 0; i < 10; i++) {
                    work = &D_80111700_messy_memory[i + 48];
                    obj = work->obj;
                    for (j = 0; j < 20; j++) {
                        if (work->unk44.x == D_80110FF4_messy_memory[j][0] &&
                            work->unk44.y == D_80110FF4_messy_memory[j][1]) {
                            D_801116E0_messy_memory[j] = obj->work[0];
                        }
                    }
                }
            }
            break;
        case 4:
            if (obj->work[1] == 4) {
                espAttrReset(work->unk42, 0x4000);
            }
            if (obj->work[1] < 4) {
                for (i = 0; i < 20; i++) {
                    if (D_801116E0_messy_memory[i] == obj->work[0]) {
                        work->unk44.x = D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[obj->work[1]][0];
                        work->unk44.y = D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[obj->work[1]][1];
                        espPosSet(work->unk42, work->unk44.x, work->unk44.y);
                        espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
                        if (i < 15) {
                            espPriSet(work->unk42, 0xDDDD);
                        } else {
                            espPriSet(work->unk42, 0xBBBB);
                        }
                    }
                }
                if (obj->work[1] * 10 + obj->work[0] == 39) {
                    D_80115D9A_messy_memory = 4;
                }
            }
            break;
        case 5:
            if (obj->work[1] == 4) {
                u32 index = obj->work[0] + 48;

                work = &D_80111700_messy_memory[index];
                for (i = 0; i < 20; i++) {
                    if (work->unk44.x == D_80110FF4_messy_memory[i][0] && work->unk44.y == D_80110FF4_messy_memory[i][1]) {
                        D_80115D20_messy_memory[obj->work[0]][0] = D_801110A4_messy_memory[i][0] * 2.0f;
                        D_80115D20_messy_memory[obj->work[0]][1] = D_801110A4_messy_memory[i][1] * 2.0f;
                    }
                }
                work->unk44.x += D_80115D20_messy_memory[obj->work[0]][0];
                work->unk44.y += D_80115D20_messy_memory[obj->work[0]][1];
                espPosSet(work->unk42, work->unk44.x, work->unk44.y);
                work->unk5C.x = work->unk5C.y = D_8011165C_messy_memory;
                espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
                if (work->unk5C.x <= 0.01 || work->unk5C.y <= 0.01) {
                    espDispOff(work->unk42);
                    for (i = 0; i < 10; i++) {
                        if (obj->work[0] == D_801116A4_messy_memory[i]) {
                            work->unk44.x = D_80110FF4_messy_memory[i][0];
                            work->unk44.y = D_80110FF4_messy_memory[i][1];
                        }
                    }
                    for (i = 0; i < 20; i++) {
                        if (work->unk44.x == D_80110FF4_messy_memory[i][0] &&
                            work->unk44.y == D_80110FF4_messy_memory[i][1]) {
                            D_80115D20_messy_memory[obj->work[0]][0] = -D_801110A4_messy_memory[i][0];
                            D_80115D20_messy_memory[obj->work[0]][1] = -D_801110A4_messy_memory[i][1];
                            work->unk44.x = 160.0f;
                            work->unk44.y = 120.0f;
                        }
                    }
                }
            }
            break;
        case 6:
        case 7:
        case 8:
            break;
        case 9:
            if (obj->work[1] < 4) {
                switch (D_801116B0_messy_memory[obj->work[1] * 10 + obj->work[0]]) {
                    case 0:
                        espPriSet(work->unk42, 0xDDDD);
                        for (i = 15; i < 21; i++) {
                            if (work->unk44.x ==
                                    D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[obj->work[1]][0] &&
                                work->unk44.y ==
                                    D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[obj->work[1]][1]) {
                                espPriSet(work->unk42, 0xBBBB);
                            }
                        }
                        break;
                    case 1:
                        cursor = &D_80111700_messy_memory[obj->work[1]];
                        work->unk44.x = cursor->unk44.x;
                        work->unk44.y = cursor->unk44.y;
                        espPriSet(work->unk42, 0xAAAA);
                        break;
                }
                espPosSet(work->unk42, work->unk44.x, work->unk44.y);
                espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
            }
            break;
        case 10:
            if (obj->work[1] < 4) {
                if (D_801116B0_messy_memory[obj->work[1] * 10 + obj->work[0]] == 1) {
                    marker = &D_80111700_messy_memory[obj->work[0] + 0x56 + obj->work[1] * 10];
                    if (D_80110FE0_messy_memory[obj->work[1]][1] + 93.0f <= work->unk44.y) {
                        for (i = 1; i < 4; i++) {
                            if (abs(D_80110FE0_messy_memory[obj->work[1]][0] + D_80111094_messy_memory[work->unk06][0] -
                                    work->unk44.x) >
                                abs(D_80110FE0_messy_memory[obj->work[1]][0] + D_80111094_messy_memory[i][0] -
                                    work->unk44.x)) {
                                work->unk06 = i;
                            }
                        }
                        work->unk44.x =
                            D_80110FE0_messy_memory[obj->work[1]][0] + D_80111094_messy_memory[work->unk06][0];
                        work->unk44.y =
                            D_80110FE0_messy_memory[obj->work[1]][1] + D_80111094_messy_memory[work->unk06][1];
                        espPriSet(marker->unk42, 0xABBB);
                    }
                    if (D_80110FE0_messy_memory[obj->work[1]][1] + 93.0f > work->unk44.y) {
                        if (D_80110FE0_messy_memory[obj->work[1]][0] + 80.0f >= work->unk44.x && work->unk08 == 0) {
                            work->unk18 = 2.0f;
                            work->unk08 = 1;
                        }
                        if (D_80110FE0_messy_memory[obj->work[1]][0] + 80.0f < work->unk44.x && work->unk08 == 0) {
                            work->unk18 = -2.0f;
                            work->unk08 = 1;
                        }
                        work->unk1C += 0.5f;
                        work->unk44.x += work->unk18;
                        work->unk44.y += work->unk1C;
                        espPriSet(work->unk42, 0xCDDD);
                        espPriSet(marker->unk42, 0xCDEE);
                    }
                    if (D_80110FE0_messy_memory[obj->work[1]][1] + 93.0f <= work->unk44.y) {
                        D_801116B0_messy_memory[obj->work[1] * 10 + obj->work[0]] = 0;
                        espDispOn(marker->unk42);
                        espPosSet(marker->unk42, work->unk44.x, work->unk44.y + 1.0f);
                    }
                }
                found = FALSE;
                for (i = 0; i < 40; i++) {
                    if (D_801116B0_messy_memory[i] == 1) {
                        found = TRUE;
                    }
                }
                if (!found) {
                    D_80115D9A_messy_memory = 10;
                }
                espPosSet(work->unk42, work->unk44.x, work->unk44.y);
            }
            break;
        case 11:
            if (obj->work[1] == 4) {
                work->unk44.x = 160.0f;
                work->unk44.y = 120.0f;
            }
            break;
        case 12:
            if (obj->work[1] == 4) {
                u32 index = obj->work[0] + 48;

                work = &D_80111700_messy_memory[index];
                work->unk44.x += D_80115D20_messy_memory[obj->work[0]][0];
                work->unk44.y += D_80115D20_messy_memory[obj->work[0]][1];
                espPosSet(work->unk42, work->unk44.x, work->unk44.y);
                work->unk5C.x = work->unk5C.y = D_8011165C_messy_memory;
                espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
                espDispOn(work->unk42);
            }
            break;
        case 13:
            if (obj->work[1] < 4) {
                if (D_80110FE0_messy_memory[obj->work[1]][1] + 80.0f > work->unk44.y) {
                    espPriSet(work->unk42, 0xDDDD);
                    if (D_801116A4_messy_memory[D_8011163A_messy_memory] == obj->work[0]) {
                        for (i = 0; i < 10; i++) {
                            if (work->unk44.x ==
                                    D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[obj->work[1]][0] &&
                                work->unk44.y ==
                                    D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[obj->work[1]][1]) {
                                D_801116E0_messy_memory[i] = obj->work[0];
                                if (D_801116A4_messy_memory[i] == D_801116E0_messy_memory[i]) {
                                    espPriSet(work->unk42, 0x1111);
                                    if (work->unk04 == 0) {
                                        D_80115D76_messy_memory[obj->work[1]]++;
                                        work->unk04 = 1;
                                    }
                                    work->unk5C.x = work->unk5C.y = D_801116A0_messy_memory;
                                    espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
                                }
                            }
                        }
                    }
                }
            }
            if (obj->work[1] == 4) {
                espPriSet(work->unk42, 0x3333);
                if (D_801116A4_messy_memory[D_8011163A_messy_memory] == obj->work[0]) {
                    espPriSet(work->unk42, 0x1111);
                    work->unk5C.x = work->unk5C.y = D_8011165C_messy_memory;
                    espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
                }
            }
            break;
    }
}

void func_8010D55C_messy_memory(omObjData *obj) {
    MessyMemoryWork *work = &D_80111700_messy_memory[obj->work[0] + 8 + obj->work[1] * 10];
    s16 i;
    u8 slot;

    if (obj->work[1] == 0) {
        for (i = 0; i < 10; i++) {
            if (obj->work[0] == i) {
                D_80111608_messy_memory[i] = func_8000B838_main((&D_80111148_messy_memory[i])->fileId);
            }
        }
    }
    if (obj->work[1] < 4) {
        for (i = 0; i < 11; i++) {
            if (i == obj->work[0]) {
                work->unk42 = espEntry(D_80111608_messy_memory[i], 0, 0);
            }
        }
    } else {
        for (i = 0; i < 10; i++) {
            if (obj->work[0] == i) {
                work->unk40 = func_8000B838_main((&D_80111198_messy_memory[i])->fileId);
                work->unk42 = espEntry(work->unk40, 0, 0);
            }
        }
    }
    if (obj->work[1] == 4) {
        slot = rand8() % 10;
        while (TRUE) {
            if (slot != D_80115D90_messy_memory[0] && slot != D_80115D90_messy_memory[1] &&
                slot != D_80115D90_messy_memory[2] && slot != D_80115D90_messy_memory[3] &&
                slot != D_80115D90_messy_memory[4] && slot != D_80115D90_messy_memory[5] &&
                slot != D_80115D90_messy_memory[6] && slot != D_80115D90_messy_memory[7] &&
                slot != D_80115D90_messy_memory[8]) {
                D_80115D90_messy_memory[obj->work[0]] = slot;
                break;
            }
            slot++;
            if (slot >= 10) {
                slot = 0;
            }
        }
        for (i = 0; i < 10; i++) {
            if (slot == i) {
                work->unk44.x = D_80110FF4_messy_memory[slot][0];
                work->unk44.y = D_80110FF4_messy_memory[slot][1];
                D_801116A4_messy_memory[slot] = obj->work[0];
            }
        }
    }
    work->unk5C.x = 1.0f;
    work->unk5C.y = 1.0f;
    espAttrSet(work->unk42, 0x5008);
    espPosSet(work->unk42, work->unk44.x, work->unk44.y);
    espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
    espPriSet(work->unk42, 0xDDDD);
    if (obj->work[1] == 4) {
        espPriSet(work->unk42, 0x3333);
    }
    obj->func = func_8010C478_messy_memory;
}

void func_8010D910_messy_memory(void) {
    MessyMemoryWork *work;
    omObjData *obj;
    s16 i;
    s16 j;
    s16 k;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            work = &D_80111700_messy_memory[j + 8 + i * 10];
            obj = omAddObj(0x12C, 0, 0, -1, func_8010D55C_messy_memory);
            for (k = 0; k < 10; k++) {
                if (j % 10 == k) {
                    obj->work[0] = j;
                }
            }
            work->obj = obj;
            obj->work[1] = i;
        }
    }
}

void func_8010DA64_messy_memory(omObjData *obj) {
    MessyMemoryWork *work = &D_80111700_messy_memory[obj->work[0] + 0x56 + obj->work[1] * 10];
    MessyMemoryWork *tile = &D_80111700_messy_memory[obj->work[0] + 8 + obj->work[1] * 10];
    s16 i;

    switch (D_80115D8C_messy_memory) {
        case 3:
            if (obj->work[1] == 4) {
                for (i = 0; i < 21; i++) {
                    if (tile->unk44.x == D_80110FF4_messy_memory[i][0] + D_80110FE0_messy_memory[obj->work[1]][0] &&
                        tile->unk44.y == D_80110FF4_messy_memory[i][1] + D_80110FE0_messy_memory[obj->work[1]][1]) {
                        work->unk44.x = tile->unk44.x;
                        work->unk44.y = tile->unk44.y;
                        espDispOn(work->unk42);
                        espPosSet(work->unk42, work->unk44.x, work->unk44.y + 2.0f);
                        if (i < 15) {
                            espPriSet(work->unk42, 0x4444);
                        } else {
                            espPriSet(work->unk42, 0x2222);
                        }
                    }
                }
            }
            break;
        case 4:
            if (obj->work[1] == 4) {
                espAttrReset(work->unk42, 0x4000);
            }
            break;
        case 5:
            if (obj->work[1] == 4) {
                for (i = 0; i < 20; i++) {
                    if (tile->unk44.x == D_80110FF4_messy_memory[i][0] && tile->unk44.y == D_80110FF4_messy_memory[i][1]) {
                        D_80115D20_messy_memory[obj->work[0]][0] = D_801110A4_messy_memory[i][0] * 2.0f;
                        D_80115D20_messy_memory[obj->work[0]][1] = D_801110A4_messy_memory[i][1] * 2.0f;
                    }
                }
                work->unk44.x += D_80115D20_messy_memory[obj->work[0]][0];
                work->unk44.y += D_80115D20_messy_memory[obj->work[0]][1];
                espPosSet(work->unk42, work->unk44.x, work->unk44.y + 2.0f);
                work->unk5C.x = work->unk5C.y = D_8011165C_messy_memory;
                espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
                if (work->unk5C.x <= 0.01 || work->unk5C.y <= 0.01) {
                    espDispOff(work->unk42);
                }
            }
            if (obj->work[1] < 4) {
                for (i = 0; i < 21; i++) {
                    if (tile->unk44.x == D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[obj->work[1]][0] &&
                        tile->unk44.y == D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[obj->work[1]][1]) {
                        work->unk44.x = tile->unk44.x;
                        work->unk44.y = tile->unk44.y;
                        espDispOn(work->unk42);
                        espPosSet(work->unk42, work->unk44.x, work->unk44.y + 1.0f);
                        espDispOn(work->unk42);
                        if (i < 15) {
                            espPriSet(work->unk42, 0xEEEE);
                        } else {
                            espPriSet(work->unk42, 0xCCCC);
                        }
                    }
                }
            }
            break;
        case 8:
            if (obj->work[1] < 4) {
                for (i = 0; i < 21; i++) {
                    if (tile->unk44.x == D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[obj->work[1]][0] &&
                        tile->unk44.y == D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[obj->work[1]][1]) {
                        work->unk44.x = tile->unk44.x;
                        work->unk44.y = tile->unk44.y;
                        espDispOn(work->unk42);
                        espPosSet(work->unk42, work->unk44.x, work->unk44.y + 1.0f);
                        espDispOn(work->unk42);
                        if (i < 15) {
                            espPriSet(work->unk42, 0xEEEE);
                        } else {
                            espPriSet(work->unk42, 0xCCCC);
                        }
                    }
                }
            }
            break;
        case 9:
        case 10:
        case 11:
            if (obj->work[1] < 4) {
                for (i = 0; i < 21; i++) {
                    if (tile->unk44.x == D_80111044_messy_memory[i][0] + D_80110FE0_messy_memory[obj->work[1]][0] &&
                        tile->unk44.y == D_80111044_messy_memory[i][1] + D_80110FE0_messy_memory[obj->work[1]][1]) {
                        work->unk44.x = tile->unk44.x;
                        work->unk44.y = tile->unk44.y;
                        espDispOn(work->unk42);
                        espPosSet(work->unk42, work->unk44.x, work->unk44.y + 1.0f);
                        if (i < 15) {
                            espPriSet(work->unk42, 0xEEEE);
                        } else {
                            espPriSet(work->unk42, 0xCCCC);
                        }
                    }
                }
                if (D_801116B0_messy_memory[obj->work[1] * 10 + obj->work[0]] == 1) {
                    espDispOff(work->unk42);
                }
            }
            break;
        case 12:
            if (obj->work[1] < 4) {
                espPriSet(work->unk42, 0xEEEE);
            }
            break;
    }
}

void func_8010E29C_messy_memory(omObjData *obj) {
    MessyMemoryWork *work = &D_80111700_messy_memory[obj->work[0] + 0x56 + obj->work[1] * 10];
    MessyMemoryWork *tile = &D_80111700_messy_memory[obj->work[0] + 8 + obj->work[1] * 10];
    s16 i;

    if (obj->work[0] == 0 && obj->work[1] == 0) {
        D_80111634_messy_memory = func_8000B838_main(0x3E0003);
    }
    work->unk42 = espEntry(D_80111634_messy_memory, 0, 0);
    if (obj->work[1] == 4) {
        work->unk5C.x = 1.0f;
        work->unk5C.y = 1.0f;
    } else {
        work->unk5C.x = 0.5f;
        work->unk5C.y = 0.5f;
    }
    espDispOff(work->unk42);
    espPriSet(work->unk42, 0xEEEE);
    if (obj->work[1] == 4) {
        for (i = 0; i < 21; i++) {
            if (tile->unk44.x == D_80110FF4_messy_memory[i][0] + D_80110FE0_messy_memory[obj->work[1]][0] &&
                tile->unk44.y == D_80110FF4_messy_memory[i][1] + D_80110FE0_messy_memory[obj->work[1]][1]) {
                work->unk44.x = tile->unk44.x;
                work->unk44.y = tile->unk44.y;
                espPriSet(work->unk42, 0x4444);
                espDispOn(work->unk42);
                espPosSet(work->unk42, work->unk44.x, work->unk44.y + 2.0f);
            }
        }
    }
    espAttrSet(work->unk42, 0x5000);
    espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
    obj->func = func_8010DA64_messy_memory;
}

void func_8010E500_messy_memory(void) {
    MessyMemoryWork *work;
    omObjData *obj;
    s16 i;
    s16 j;
    s16 k;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            work = &D_80111700_messy_memory[j + 0x56 + i * 10];
            obj = omAddObj(0x190, 0, 0, -1, func_8010E29C_messy_memory);
            for (k = 0; k < 10; k++) {
                if (j % 10 == k) {
                    obj->work[0] = j;
                }
            }
            work->obj = obj;
            obj->work[1] = i;
        }
    }
}

void func_8010E654_messy_memory(omObjData *obj) {
    MessyMemoryWork *work = &D_801134E8_messy_memory[obj->work[0]];
    omObjData *mainObj = D_801134E8_messy_memory[0].obj;

    switch (D_80115D8C_messy_memory) {
        case 1:
            if (obj->work[0] == 0) {
                if (work->unk06 == 48) {
                    HuAudFXPlay(0x3F0);
                    HuAudFXVolSet(HuAudFXPlay(0x298), 0x73);
                    HuAudSeqPlay(0x4F);
                }
                if (work->unk06 < 50) {
                    work->unk06++;
                }
            }
            break;
        case 2:
        case 3:
            switch (obj->work[1]) {
                case 0:
                    obj->trans.z += D_80111228_messy_memory[obj->work[0]][0];
                    obj->trans.x += D_80111228_messy_memory[obj->work[0]][1];
                    if (obj->trans.z <= D_80111228_messy_memory[obj->work[0]][2]) {
                        obj->work[1] = 1;
                        D_80111650_messy_memory = 1;
                        if (obj->work[0] == 4 || obj->work[0] == 6) {
                            func_8001C5B4_main(*obj->model, mainObj->motion[3]);
                        } else {
                            func_8001C5B4_main(*obj->model, mainObj->motion[4]);
                            if (Hu3DData[*obj->model].motTime == 0.0f) {
                                HuAudFXVolSet(HuAudFXPlay(0x3EE), 0x73);
                            }
                        }
                        func_8001C814_main(*obj->model, 2, 2);
                        Hu3DMotionTimeSet(*obj->model, 0.0f);
                    }
                    break;
                case 1:
                    if (obj->work[0] != 4 && obj->work[0] != 6) {
                        if (Hu3DData[*obj->model].motTime == 0.0f) {
                            HuAudFXVolSet(HuAudFXPlay(0x3EE), 0x73);
                        }
                    }
                    work->unk04++;
                    if (D_80115D8C_messy_memory == 2 && obj->work[0] == 2 && work->unk04 == 5) {
                        D_80111675_messy_memory = 1;
                    }
                    if (D_80115D8C_messy_memory == 2 && obj->work[0] == 6 && work->unk04 == 10) {
                        D_80115D9A_messy_memory = 2;
                    }
                    if (obj->work[0] < 4) {
                        if (work->unk04 >= 70) {
                            work->unk04 = 0;
                            obj->work[1] = 2;
                        }
                    }
                    if (obj->work[0] >= 4) {
                        if (work->unk04 >= 20) {
                            work->unk04 = 0;
                            obj->work[1] = 2;
                            if (obj->work[0] == 4) {
                                HuAudFXPlay(0x3F2);
                            }
                        }
                    }
                    break;
                case 2:
                    obj->rot.y = func_801059BC_messy_memory(obj->rot.y, 180.0f);
                    func_8001C5B4_main(*obj->model, mainObj->motion[2]);
                    func_8001C814_main(*obj->model, 2, 2);
                    Hu3DMotionTimeSet(*obj->model, 0.0f);
                    if (obj->work[0] == 2) {
                        D_80111675_messy_memory = 2;
                        HuAudFXVolSet(HuAudFXPlay(0x298), 0x73);
                    }
                    obj->work[1] = 3;
                    break;
                case 3:
                    obj->trans.z -= D_80111228_messy_memory[obj->work[0]][0];
                    obj->trans.x -= D_80111228_messy_memory[obj->work[0]][1];
                    if (obj->trans.z >= 170.0f) {
                        obj->work[1] = 4;
                        if (obj->work[0] == 3) {
                            D_80115D9A_messy_memory = 3;
                        }
                    }
                    if (obj->work[0] == 3 && obj->trans.z == -50.0f) {
                        HuAudFXVolSet(HuAudFXPlay(0x29B), 0x73);
                    }
                    break;
                case 4:
                    func_8001C258_main(*obj->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    break;
            }
            Hu3DModelPosSet(*obj->model, obj->trans.x, obj->trans.y, obj->trans.z);
            break;
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z + 0.0f);
}

void func_8010EBB0_messy_memory(omObjData *obj) {
    u32 index = obj->work[0];
    omObjData *mainObj = D_801134E8_messy_memory[0].obj;
    u8 i;

    if (index == 0) {
        *obj->model = func_8000B108_main(0xA0000, 0xB9);
        D_8011163C_messy_memory = *obj->model;
        func_8000B460_main(obj, 0, 0xA0001);
        func_8000B460_main(obj, 1, 0xA0002);
        func_8000B460_main(obj, 2, 0xA0006);
        func_8000B460_main(obj, 3, 0xA0007);
        func_8000B460_main(obj, 4, 0xA0009);
    } else {
        *obj->model = Hu3DModelLink(D_8011163C_messy_memory);
    }
    obj->model[1] = func_8000B0A0_main(0, 0xA9);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80088800_main(Hu3DData[obj->model[1]].mtx, 0.0f, 15.0f, 0.0f);
    func_8001C5B4_main(*obj->model, mainObj->motion[2]);
    func_8001C814_main(*obj->model, 2, 2);
    Hu3DMotionTimeSet(*obj->model, 0.0f);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    for (i = 0; i < 7; i++) {
        if (i == obj->work[0]) {
            obj->trans.z = i * 80 + 120.0f;
        }
    }
    obj->rot.x = 0.0f;
    obj->rot.y = D_80111228_messy_memory[obj->work[0]][3];
    obj->rot.z = 0.0f;
    obj->scale.x = 0.8f;
    obj->scale.y = 0.8f;
    obj->scale.z = 0.8f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM1);
    obj->func = func_8010E654_messy_memory;
}

void func_8010EE6C_messy_memory(void) {
    MessyMemoryWork *work;
    omObjData *obj;
    s16 i;

    for (i = 0; i < 7; i++) {
        work = &D_801134E8_messy_memory[i];
        obj = omAddObj(0x1F4, 1, 0xA, -1, func_8010EBB0_messy_memory);
        obj->work[0] = i;
        work->obj = obj;
    }
}

void func_8010EF10_messy_memory(omObjData *obj) {
    MessyMemoryWork *work = &D_80113A94_messy_memory[obj->work[0]];

    switch (D_80115D8C_messy_memory) {
        case 2:
        case 3:
            if (D_80111675_messy_memory == 1) {
                if (D_80115D70_messy_memory == 0) {
                    HuAudFXPlay(0x3E9);
                    D_80115D70_messy_memory = 1;
                    HuAudFXPlay(0x127);
                }
                func_8001C258_main(*obj->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                func_8001F9E4_main(*obj->model, work->unk06);
                work->unk06 += 20;
                if (work->unk06 >= 255) {
                    work->unk06 = 255;
                }
            }
            if (D_80111675_messy_memory == 2) {
                func_8001F9E4_main(*obj->model, work->unk06);
                work->unk06 -= 10;
                if (work->unk06 <= 0) {
                    work->unk06 = 0;
                    func_8001C258_main(*obj->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    D_80111650_messy_memory = 0;
                }
            }
            break;
    }
}

void func_8010F04C_messy_memory(omObjData *obj) {
    *obj->model = func_8000B108_main(0x3E001C, 0xA9);
    func_8001C814_main(*obj->model, 2, 2);
    func_8001C258_main(*obj->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001FA68_main(*obj->model);
    func_8001F9E4_main(*obj->model, 100);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    obj->rot.x = 0.0f;
    obj->rot.y = 0.0f;
    obj->rot.z = 0.0f;
    obj->scale.x = 1.0f;
    obj->scale.y = 1.0f;
    obj->scale.z = 1.0f;
    Hu3DModelPosSet(*obj->model, obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(*obj->model, obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelScaleSet(*obj->model, obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelCameraSet(*obj->model, HU3D_CAM1);
    obj->func = func_8010EF10_messy_memory;
}

void func_8010F15C_messy_memory(void) {
    omObjData *obj = omAddObj(0xFA, 1, 0xA, -1, func_8010F04C_messy_memory);
    obj->work[0] = 0;
    D_80113A94_messy_memory[0].obj = obj;
}

void func_8010F19C_messy_memory(omObjData *obj) {
    MessyMemoryWork *work = &D_80113884_messy_memory[obj->work[0]];

    switch (D_80115D8C_messy_memory) {
        case 9:
            switch (D_80115D80_messy_memory[obj->work[0]]) {
                case 2:
                    if (Hu3DData[*obj->model].motTime == D_80111600_messy_memory) {
                        func_8001C814_main(*obj->model, 4, 4);
                    }
                    if (Hu3DData[*obj->model].motTime == 0.0f) {
                        D_80115D80_messy_memory[obj->work[0]] = 0;
                    }
                    break;
                case 1:
                    if (Hu3DData[*obj->model].motTime == 0.0f) {
                        func_8001C5B4_main(*obj->model, *obj->motion);
                        func_8001C814_main(*obj->model, 2, 0);
                    }
                    break;
            }
            break;
        case 11:
            if (D_80115D80_messy_memory[obj->work[0]] == 1 ||
                Hu3DData[*obj->model].motTime == D_80111600_messy_memory) {
                func_8001C814_main(*obj->model, 4, 4);
                D_80115D80_messy_memory[obj->work[0]] = 0;
            }
            if (obj->work[0] == 3) {
                work->unk04++;
                if (work->unk04 > 50) {
                    D_80115D9A_messy_memory = 11;
                    work->unk04 = 0;
                }
            }
            break;
    }
}

void func_8010F3DC_messy_memory(omObjData *obj) {
    *obj->model = func_8000B108_main(0x3E001A, 0xB9);
    func_8000B460_main(obj, 0, 0x3E001B);
    func_8001C5B4_main(*obj->model, *obj->motion);
    D_80111600_messy_memory = D_800CCF58_main[Hu3DData[*obj->model].motId].unk02;
    func_8001C814_main(*obj->model, 2, 1);
    switch (obj->work[0]) {
        case 0:
            obj->trans.x = -106.0f;
            obj->trans.y = 265.0f;
            obj->trans.z = -87.5f;
            obj->scale.y = 1.05f;
            break;
        case 1:
            obj->trans.x = 106.0f;
            obj->trans.y = 265.0f;
            obj->trans.z = -87.5f;
            obj->scale.y = 1.05f;
            break;
        case 2:
            obj->trans.x = -106.0f;
            obj->trans.y = 115.0f;
            obj->trans.z = -30.0f;
            obj->scale.y = 1.0f;
            break;
        case 3:
            obj->trans.x = 106.0f;
            obj->trans.y = 115.0f;
            obj->trans.z = -30.0f;
            obj->scale.y = 1.0f;
            break;
    }
    obj->rot.x = 0.0f;
    obj->rot.y = 0.0f;
    obj->rot.z = 0.0f;
    obj->scale.x = 1.0f;
    obj->scale.z = 1.0f;
    Hu3DModelPosSet(*obj->model, obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(*obj->model, obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelScaleSet(*obj->model, obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelCameraSet(*obj->model, HU3D_CAM1);
    obj->func = func_8010F19C_messy_memory;
}

void func_8010F644_messy_memory(void) {
    MessyMemoryWork *work;
    omObjData *obj;
    s16 i;

    for (i = 0; i < 4; i++) {
        work = &D_80113884_messy_memory[i];
        obj = omAddObj(0x1D6, 1, 3, -1, func_8010F3DC_messy_memory);
        obj->work[0] = i;
        work->obj = obj;
    }
}

void func_8010F6E8_messy_memory(omObjData *obj) {
    MessyMemoryWork *work = &D_80111700_messy_memory[obj->work[0] + 0x4A + obj->work[1] * 3];
    u8 i;

    switch (D_80115D8C_messy_memory) {
        case 13:
            if (obj->work[0] == 0 && obj->work[1] == 0 && work->unk06 == 0) {
                HuAudFXPlay(0x3EC);
                work->unk06 = 1;
            }
            break;
        case 14:
            work->unk5C.x = work->unk5C.y = D_80115D7C_messy_memory;
            if (obj->work[0] == 1) {
                espDispOn(work->unk42);
                work->unk04++;
                if (work->unk04 >= 10) {
                    work->unk04 = 0;
                }
                func_8000BD50_main(work->unk42, work->unk04);
            }
            if (obj->work[0] == 2) {
                espDispOn(work->unk42);
            }
            break;
        case 15:
            if (obj->work[0] == 0 && obj->work[1] == 0 && work->unk06 == 1) {
                HuAudFXPlay(0x3ED);
                work->unk06 = 2;
            }
            for (i = 0; i < 10; i++) {
                if (D_80115D76_messy_memory[obj->work[1]] == i) {
                    work = &D_80111700_messy_memory[obj->work[1] * 3 + 0x4B];
                    func_8000BD50_main(work->unk42, i);
                }
            }
            if (D_80115D76_messy_memory[obj->work[1]] == 10) {
                work = &D_80111700_messy_memory[obj->work[1] * 3 + 0x4A];
                espDispOn(work->unk42);
                func_8000BD50_main(work->unk42, 1);
                work = &D_80111700_messy_memory[obj->work[1] * 3 + 0x4B];
                func_8000BD50_main(work->unk42, 0);
            }
            work = &D_80111700_messy_memory[obj->work[0] + 0x4A + obj->work[1] * 3];
            work->unk5C.x = work->unk5C.y = D_80115D7C_messy_memory;
            if (work->unk5C.x < 0.01f || work->unk5C.y < 0.01f) {
                work->unk5C.x = work->unk5C.y = 0.01f;
                espDispOff(work->unk42);
                D_80115D9A_messy_memory = 15;
            }
            break;
    }
    espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
    espPosSet(work->unk42, work->unk44.x, work->unk44.y);
}

void func_8010FA38_messy_memory(omObjData *obj) {
    MessyMemoryWork *work = &D_80111700_messy_memory[obj->work[0] + 0x4A + obj->work[1] * 3];
    u8 i;

    switch (obj->work[0]) {
        case 0:
        case 1:
            work->unk40 = func_8000B838_main(0x2E);
            work->unk42 = espEntry(work->unk40, 0, 0);
            espAttrSet(work->unk42, 0x1000);
            espPriSet(work->unk42, 0);
            break;
        case 2:
            work->unk40 = func_8000B838_main(0x3E0019);
            work->unk42 = espEntry(work->unk40, 0, 0);
            espAttrSet(work->unk42, 0x1000);
            espPriSet(work->unk42, 0x500);
            break;
    }
    for (i = 0; i < 3; i++) {
        if (obj->work[0] == i) {
            work->unk44.x = D_801112B8_messy_memory[obj->work[1]][i * 2];
            work->unk44.y = D_801112B8_messy_memory[obj->work[1]][i * 2 + 1];
        }
    }
    espDispOff(work->unk42);
    obj->func = func_8010F6E8_messy_memory;
}

void func_8010FBB0_messy_memory(void) {
    MessyMemoryWork *work;
    omObjData *obj;
    u8 i;
    u8 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            work = &D_80111700_messy_memory[0x4A + i * 3 + j];
            obj = omAddObj(0x384, 1, 0xA, -1, func_8010FA38_messy_memory);
            obj->work[0] = j;
            obj->work[1] = i;
            work->obj = obj;
        }
    }
}

void func_8010FC90_messy_memory(void) {
    u32 i;

    for (i = 0; i < 2; i++) {
        CZoomM[i] = 495.05002f;
        CRotM[i].x = 335.14f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 204.0f;
        CenterM[i].z = -47.0f;
    }
}

void func_8010FD3C_messy_memory(omObjData *obj) {
    osViBlack(FALSE);
    omOvlReturnEx(1);
}

void func_8010FD60_messy_memory(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_8010FD3C_messy_memory;
    }
}

void func_8010FD98_messy_memory(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_8010FD60_messy_memory;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

void func_8010FDF0_messy_memory(omObjData *obj) {
    u8 winners[4];
    u8 i;
    u8 j;

    switch (D_80115D8C_messy_memory) {
        case 0:
            if (D_80115D8E_messy_memory > 0) {
                D_80115D8E_messy_memory--;
            }
            if (D_80115D8E_messy_memory < 91) {
                GMesCreate(GMES_MES_TIMER, D_80115D8E_messy_memory / 30, 160, 28);
                D_80115D8E_messy_memory = 91;
                func_80105B7C_messy_memory(1);
            }
            break;
        case 1:
            if (D_80115D8E_messy_memory > 0) {
                D_80115D8E_messy_memory--;
                if (D_80115D8E_messy_memory == 88) {
                    HuAudFXPlay(8);
                }
                func_8003F578_main((D_80115D8E_messy_memory + 29) / 30);
            } else {
                func_8003F5C0_main();
                D_80115D8E_messy_memory = 0;
                func_80105B7C_messy_memory(2);
            }
            break;
        case 2:
            if (D_80115D9A_messy_memory == 2) {
                for (i = 0; i < 10; i++) {
                    D_80115D90_messy_memory[i] = 10;
                }
                func_80105B7C_messy_memory(3);
            }
            break;
        case 3:
            if (D_80115D9A_messy_memory == 3) {
                func_80105B7C_messy_memory(4);
            }
            break;
        case 4:
            if (D_80115D9A_messy_memory == 4) {
                func_80105B7C_messy_memory(5);
            }
            break;
        case 5:
            D_8011165C_messy_memory -= 0.02f;
            if (D_80115D9A_messy_memory == 5) {
                func_80105B7C_messy_memory(6);
            }
            break;
        case 6:
            if (D_80115D9A_messy_memory == 6) {
                func_80105B7C_messy_memory(8);
                D_80115D8E_messy_memory = 0;
            }
            break;
        case 7:
            D_80115D8E_messy_memory--;
            if (D_80115D8E_messy_memory <= 0) {
                func_80105B7C_messy_memory(8);
                D_80115D8E_messy_memory = 0;
            }
            break;
        case 8:
            if (D_80115D8E_messy_memory == 0) {
                GMesCreate(GMES_MES_3);
                D_80115D8E_messy_memory++;
            } else if (D_80115D8E_messy_memory >= 43) {
                HuAudSeqPlay(0x31);
            } else {
                D_80115D8E_messy_memory++;
            }
            if (GMesStatGet() == 0) {
                func_80105B7C_messy_memory(9);
                GMesCreate(GMES_MES_TIMER, 30, 160, 28);
                D_80115D8E_messy_memory = 901;
            }
            break;
        case 9:
            if (D_80115D8E_messy_memory > 0) {
                D_80115D8E_messy_memory--;
                func_8003F578_main((D_80115D8E_messy_memory + 29) / 30);
            } else {
                func_8003F5C0_main();
                func_80105B7C_messy_memory(10);
                D_8011165C_messy_memory = 0.01f;
                GMesCreate(GMES_MES_14);
                HuAudSeqFadeOut(120);
            }
            break;
        case 10:
            if (D_80115D9A_messy_memory == 10 && GMesStatGet() == 0) {
                func_80105B7C_messy_memory(11);
            }
            break;
        case 11:
            if (D_80115D9A_messy_memory == 11) {
                func_80105B7C_messy_memory(12);
            }
            break;
        case 12:
            D_8011165C_messy_memory += 0.01f;
            if (D_80115D9A_messy_memory == 12) {
                func_80105B7C_messy_memory(13);
            }
            break;
        case 13:
            if (D_80111639_messy_memory == 0) {
                if (D_801116A0_messy_memory == 1.0f) {
                    HuAudFXPlay(0x3EF);
                }
                D_8011165C_messy_memory += 0.1f;
                D_801116A0_messy_memory += 0.05f;
                if (D_801116A0_messy_memory >= 1.5f) {
                    D_80111639_messy_memory = 1;
                }
            }
            if (D_80111639_messy_memory == 1) {
                D_8011165C_messy_memory -= 0.1f;
                D_801116A0_messy_memory -= 0.05f;
                if (D_801116A0_messy_memory <= 1.0f) {
                    D_801116A0_messy_memory = 1.0f;
                    D_8011163A_messy_memory++;
                    D_80111639_messy_memory = 0;
                    if (D_8011163A_messy_memory >= 10) {
                        for (i = 0; i < 4; i++) {
                            D_80111630_messy_memory[i] = i;
                        }
                        for (i = 0; i < 4; i++) {
                            for (j = 0; j < 3; j++) {
                                if (D_80115D76_messy_memory[D_80111630_messy_memory[j]] <
                                    D_80115D76_messy_memory[D_80111630_messy_memory[j + 1]]) {
                                    D_80111630_messy_memory[j] = D_80111630_messy_memory[j] ^ D_80111630_messy_memory[j + 1];
                                    D_80111630_messy_memory[j + 1] = D_80111630_messy_memory[j] ^ D_80111630_messy_memory[j + 1];
                                    D_80111630_messy_memory[j] = D_80111630_messy_memory[j + 1] ^ D_80111630_messy_memory[j];
                                }
                            }
                        }
                        for (i = 0; i < 3; i++) {
                            if (D_80115D76_messy_memory[D_80111630_messy_memory[0]] ==
                                D_80115D76_messy_memory[D_80111630_messy_memory[i + 1]]) {
                                D_8011163B_messy_memory++;
                            }
                        }
                        if (D_80115D76_messy_memory[D_80111630_messy_memory[0]] < 4) {
                            D_8011163B_messy_memory = 4;
                        }
                        D_80115D8E_messy_memory = 30;
                        func_80105B7C_messy_memory(14);
                    }
                }
            }
            break;
        case 14:
            D_80115D7C_messy_memory += 0.05f;
            if (D_80115D7C_messy_memory >= 1.0f) {
                D_80115D7C_messy_memory = 1.0f;
            }
            if (D_80115D9A_messy_memory == 14) {
                func_80105B7C_messy_memory(15);
            }
            break;
        case 15:
            D_80115D8E_messy_memory--;
            if (D_80115D8E_messy_memory < 0) {
                D_80115D7C_messy_memory -= 0.045f;
            }
            if (D_80115D9A_messy_memory == 15) {
                func_80105B7C_messy_memory(16);
                D_80115D8E_messy_memory = -15;
            }
            break;
        case 16:
            if (GMesStatGet() == 0 && D_80115D8E_messy_memory == 0) {
                D_80115D8E_messy_memory = 1;
                switch (D_8011163B_messy_memory) {
                    case 0:
                        winners[0] = GwPlayer[D_80111630_messy_memory[0]].chr;
                        GwPlayer[D_80111630_messy_memory[0]].bonusCoin = 10;
                        GMesCreate(GMES_MES_MG_WINNER, winners[0]);
                        HuAudSeqPlay(0x65);
                        break;
                    case 1:
                        for (i = 0; i < 2; i++) {
                            winners[i] = GwPlayer[D_80111630_messy_memory[i]].chr;
                            GwPlayer[D_80111630_messy_memory[i]].bonusCoin = 10;
                        }
                        GMesCreate(GMES_MES_MG_WINNERS_2, winners[0], winners[1]);
                        HuAudSeqPlay(0x66);
                        break;
                    case 2:
                        for (i = 0; i < 3; i++) {
                            winners[i] = GwPlayer[D_80111630_messy_memory[i]].chr;
                            GwPlayer[D_80111630_messy_memory[i]].bonusCoin = 10;
                        }
                        GMesCreate(GMES_MES_MG_WINNERS_3, winners[0], winners[1], winners[2]);
                        HuAudSeqPlay(0x66);
                        break;
                    case 3:
                        for (i = 0; i < 4; i++) {
                            winners[i] = GwPlayer[D_80111630_messy_memory[i]].chr;
                            GwPlayer[D_80111630_messy_memory[i]].bonusCoin = 10;
                        }
                        GMesCreate(GMES_MES_MG_WINNERS_4, winners[0], winners[1], winners[2], winners[3]);
                        HuAudSeqPlay(0x66);
                        break;
                    case 4:
                        GMesCreate(GMES_MES_MG_DRAW);
                        HuAudSeqPlay(0x6C);
                        break;
                }
            }
            if (D_80115D8E_messy_memory > 0) {
                if (GMesStatGet() == 0) {
                    func_80105B7C_messy_memory(17);
                    D_80115D8E_messy_memory = 15;
                }
            } else if (D_80115D8E_messy_memory < 0) {
                D_80115D8E_messy_memory++;
            }
            break;
        case 17:
            if (D_80115D8E_messy_memory > 0) {
                D_80115D8E_messy_memory--;
            } else {
                WipeCreateOut(0, 20);
                obj->func = func_8010FD60_messy_memory;
            }
            break;
    }
    if (D_80111650_messy_memory > 0) {
        if (D_80111650_messy_memory % 5 == 1) {
            for (i = 0; i < 4; i++) {
                if (!(GwPlayer[i].stat & 1)) {
                    omVibrate(i, 2, 3, 10);
                }
            }
        }
        D_80111650_messy_memory++;
    }
    if (D_80111650_messy_memory > 30000) {
        D_80111650_messy_memory = 1;
    }
}

void func_801109BC_messy_memory(omObjData *obj) {
    u8 i;
    u8 j;

    D_80115D8E_messy_memory = 0x67;
    D_80115D8C_messy_memory = 0;
    D_80115D9A_messy_memory = 50;
    D_80111638_messy_memory = 0;
    D_8011165C_messy_memory = 1.0f;
    D_801116A0_messy_memory = 1.0f;
    D_80111639_messy_memory = 0;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 2; j++) {
            D_80115D20_messy_memory[i][j] = 0.0f;
        }
    }
    for (i = 0; i < 10; i++) {
        D_801116A4_messy_memory[i] = 10;
    }
    for (i = 0; i < 20; i++) {
        D_801116E0_messy_memory[i] = 10;
    }
    for (i = 0; i < 4; i++) {
        D_80115D76_messy_memory[i] = 0;
    }
    for (i = 0; i < 10; i++) {
        D_80115D90_messy_memory[i] = 10;
    }
    for (i = 0; i < 4; i++) {
        D_80111670_messy_memory[i] = 0;
    }
    for (i = 0; i < 40; i++) {
        D_801116B0_messy_memory[i] = 0;
    }
    D_8011163A_messy_memory = 0;
    for (i = 0; i < 4; i++) {
        D_80115D80_messy_memory[i] = 0;
    }
    D_80111600_messy_memory = 0.0f;
    for (i = 0; i < 4; i++) {
        D_80111630_messy_memory[i] = 0;
    }
    D_8011163B_messy_memory = 0;
    D_80111675_messy_memory = 0;
    D_80111674_messy_memory = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            D_80111678_messy_memory[i][j] = 0;
        }
    }
    D_80115D7C_messy_memory = 0.1f;
    for (i = 0; i < 10; i++) {
        D_80111608_messy_memory[i] = 0;
    }
    D_80111634_messy_memory = 0;
    D_8011163C_messy_memory = 0;
    for (i = 0; i < 4; i++) {
        D_80115D84_messy_memory[i] = -1;
    }
    D_80115D70_messy_memory = 0;
    D_80111650_messy_memory = 0;
    func_8010FC90_messy_memory();
    func_80106588_messy_memory();
    func_801061AC_messy_memory();
    func_8010B4CC_messy_memory();
    func_8010D910_messy_memory();
    func_8010EE6C_messy_memory();
    func_8010F644_messy_memory();
    func_8010F15C_messy_memory();
    func_8010C37C_messy_memory();
    func_8010FBB0_messy_memory();
    func_8010E500_messy_memory();
    WipeCreateIn(0xFF, 16);
    obj->func = func_8010FDF0_messy_memory;
}

void func_80110D48_messy_memory(void) {
}

void func_80110D50_messy_memory(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 2;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    for (i = 0; i < 2; i++) {
        ScissorSet(i, D_80111340_messy_memory[i].scissorX, D_80111340_messy_memory[i].scissorY,
                   D_80111340_messy_memory[i].scissorWidth, D_80111340_messy_memory[i].scissorHeight);
        ViewportSet(i, D_80111340_messy_memory[i].viewportScale.x, D_80111340_messy_memory[i].viewportScale.y,
                    D_80111340_messy_memory[i].viewportScale.z, D_80111340_messy_memory[i].viewportTranslate.x,
                    D_80111340_messy_memory[i].viewportTranslate.y, D_80111340_messy_memory[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, D_80111340_messy_memory[i].fov, 80.0f, 8000.0f);
    }
}

void func_80110EC4_messy_memory(void) {
    func_8001FE20_main(50);
    func_800142A0_main(32);
    omInitObjMan(150, 0);
    func_8004A208_main();
    Hu3DGLightColorSet(0, 64, 64, 96);
    Hu3DGLightColorSet(1, 64, 64, 64);
    Hu3DGLightDirSet(1, 0.0f, 85.0f, 100.0f);
    func_80110D50_messy_memory();
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_801115F4_messy_memory, 0);
    func_80045010_main(D_801115F4_messy_memory, 1);
    omAddObj(1000, 0, 0, -1, func_801109BC_messy_memory);
    omAddObj(1000, 0, 0, -1, func_8010FD98_messy_memory);
    func_80105A3C_messy_memory();
}

const s16 D_801115F4_messy_memory[] = { 0x8260, 0x8261, 0x8262, 0 };
