#include "common.h"
#include "math.h"
#include "game/overlays/minigame.h"

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
// m229_objWorkTbl; several sub-ranges of the pool have their own
// symbols (e.g. m229_dustWork is entry 69).
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
    /* 0x00 */ s16 unk00;   // m229_dustSeF
    /* 0x02 */ u8 unk02[4]; // m229_handAlphaTbl
    /* 0x06 */ u8 unk06[4]; // m229_scoreTbl
} MessyMemoryPlayerStat;       // sizeof 0xA

// Fields of m229_playerStat (aliased in undefined_syms.txt).
extern s16 m229_dustSeF;
extern u8 m229_handAlphaTbl[4];
extern u8 m229_scoreTbl[4];

// Sub-ranges of the m229_objWorkTbl work pool (aliased in undefined_syms.txt).
extern MessyMemoryWork m229_coverWorkTbl[2];
extern MessyMemoryWork m229_dividerWork[1];
extern MessyMemoryWork m229_moverWorkTbl[7];
extern MessyMemoryWork m229_shutterWorkTbl[4];
extern MessyMemoryWork m229_dustWork[1];
extern MessyMemoryWork m229_playerWorkTbl[4];

extern const s16 m229_fontMesTbl[];

void m229_DividerDraw(Gfx **gfxPos, s32 arg1, s32 arg2);
void m229_CoverObjMain(omObjData *obj);
void m229_CoverObjInit(omObjData *obj);
Gfx **m229_GfxRectTexInit(Gfx **gfx);
Gfx **m229_GfxRectXluInit(Gfx **gfx);
Gfx **m229_GfxPrimAlphaSet(Gfx **gfx, u8 alpha);
void m229_HandDraw(Gfx **gfxPos, s32 arg1, s32 arg2);
void m229_HandPadInput(omObjData *obj);
void m229_HandComInputCalc(omObjData *obj);
void m229_HandComInput(omObjData *obj);
void m229_HandObjMain(omObjData *obj);
void m229_HandObjInit(omObjData *obj);
void m229_PlayerObjMain(omObjData *obj);
void m229_PlayerObjInit(omObjData *obj);
void m229_ItemObjMain(omObjData *obj);
void m229_ItemObjInit(omObjData *obj);
void m229_ItemMarkObjMain(omObjData *obj);
void m229_ItemMarkObjInit(omObjData *obj);
void m229_MoverObjMain(omObjData *obj);
void m229_MoverObjInit(omObjData *obj);
void m229_DustObjInit(omObjData *obj);
void m229_ShutterObjMain(omObjData *obj);
void m229_ShutterObjInit(omObjData *obj);
void m229_ScoreObjMain(omObjData *obj);
void m229_ScoreObjInit(omObjData *obj);
void m229_MainObjMain(omObjData *obj);
void m229_MainObjInit(omObjData *obj);
void m229_CameraInit(void);
void m229_ObjectSetup(void);

s32 m229_voiceChrTbl[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };

s16 m229_viewOfsTbl[5][2] = {
    { 0, 0 },
    { 144, 0 },
    { 0, 112 },
    { 144, 112 },
    { 0, 0 },
};

s16 m229_roomSpotPosTbl[20][2] = {
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

s16 m229_viewSpotPosTbl[20][2] = {
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

s16 m229_trayPosTbl[4][2] = {
    { 46, 107 },
    { 70, 107 },
    { 95, 107 },
    { 121, 107 },
};

f32 m229_itemScatterVelTbl[20][2] = {
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

s32 m229_itemScatterVelTblPad = 0; /* Unreferenced. */

MessyMemorySpriteEntry m229_itemViewSprTbl[10] = {
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

MessyMemorySpriteEntry m229_itemRoomSprTbl[10] = {
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

MessyMemorySpriteEntry m229_handSprTbl[8] = {
    { 0, 0x6A },
    { 0, 0x6B },
    { 0, 0x6C },
    { 0, 0x6D },
    { 0, 0x6E },
    { 0, 0x6F },
    { 0, 0x70 },
    { 0, 0x71 },
};

f32 m229_moverPathTbl[7][4] = {
    { -5.0f, -3.0f, -170.0f, 240.0f },
    { -5.0f, 2.5f, -170.0f, 120.0f },
    { -5.0f, -0.5f, -200.0f, 200.0f },
    { -5.0f, 0.5f, -200.0f, 160.0f },
    { -5.0f, -1.5f, -70.0f, 240.0f },
    { -5.0f, 0.0f, -130.0f, 180.0f },
    { -5.0f, 1.5f, -70.0f, 140.0f },
};

f32 m229_playerWalkTbl[4][2] = {
    { 10.0f, -300.0f },
    { -10.0f, 300.0f },
    { 10.0f, -250.0f },
    { -10.0f, 250.0f },
};

// x/y pairs
f32 m229_scorePosTbl[4][6] = {
    { 65.0f, 40.0f, 85.0f, 40.0f, 115.0f, 45.0f },
    { 210.0f, 40.0f, 230.0f, 40.0f, 260.0f, 45.0f },
    { 65.0f, 150.0f, 85.0f, 150.0f, 115.0f, 155.0f },
    { 210.0f, 150.0f, 230.0f, 150.0f, 260.0f, 155.0f },
};

char *m229_chrNameTbl[8] = {
    "\x82\x6C\x82\x60\x82\x71\x82\x68\x82\x6E",                 // ＭＡＲＩＯ
    "\x82\x6B\x82\x74\x82\x68\x82\x66\x82\x68",                 // ＬＵＩＧＩ
    "\x82\x6F\x82\x64\x82\x60\x82\x62\x82\x67",                 // ＰＥＡＣＨ
    "\x82\x78\x82\x6E\x82\x72\x82\x67\x82\x68",                 // ＹＯＳＨＩ
    "\x82\x76\x82\x60\x82\x71\x82\x68\x82\x6E",                 // ＷＡＲＩＯ
    "\x82\x63\x82\x6E\x82\x6D\x82\x6A\x82\x64\x82\x78",         // ＤＯＮＫＥＹ
    "\x82\x76\x82\x60\x82\x6B\x82\x74\x82\x68\x82\x66\x82\x68", // ＷＡＬＵＩＧＩ
    "\x82\x63\x82\x60\x82\x68\x82\x72\x82\x78",                 // ＤＡＩＳＹ
}; /* Unreferenced. */

s16 m229_grabSe = 999;
s16 m229_dropSe = 1000;
s16 m229_walkSe = 40;

// Only the first two cameras are used.
MessyMemoryCamera m229_cameraViewTbl[4] = {
    { 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 34.71f },
    { 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 34.71f },
    { 0.0f, 120.0f, 160.0f, SCREEN_HEIGHT, { 320.0f, 240.0f, 511.0f }, { 320.0f, 720.0f, 511.0f }, 45.0f },
    { 160.0f, 120.0f, SCREEN_WIDTH, SCREEN_HEIGHT, { 320.0f, 240.0f, 511.0f }, { 960.0f, 720.0f, 511.0f }, 45.0f },
};

f32 m229_shutterMotEnd BSS;
u8 m229_shutterMotEndPad[4] BSS; /* Unreferenced. */
s32 m229_itemViewAnimTbl[10] BSS;
u8 m229_rankTbl[4] BSS;
s32 m229_itemMarkAnim BSS;
u8 m229_itemPlaceCnt BSS;
u8 m229_checkPulseF BSS;
u8 m229_checkNo BSS;
u8 m229_tieCnt BSS;
s32 m229_moverMdl BSS;
s32 m229_handPatTbl[4] BSS;
s16 m229_messVibTimer BSS;
HuSprAnimData *m229_dividerHAnim BSS;
u8 m229_handDispTbl[4] BSS;
f32 m229_zoomScale BSS;
HuSprAnimData *m229_handAnimTbl[4] BSS;
u8 m229_handGrabTbl[4] BSS;
u8 m229_itemPlaceNum BSS;
u8 m229_dustState BSS;
u8 m229_comKnownTbl[4][10] BSS;
f32 m229_checkScale BSS;
u8 m229_roomItemTbl[10] BSS;
u8 m229_itemHeldTbl[40] BSS;
HuSprAnimData *m229_dividerVAnim BSS;
u8 m229_dividerVAnimPad[4] BSS; /* Unreferenced. */
u8 m229_roomSpotItemTbl[20] BSS;
u8 m229_roomSpotItemTblPad[12] BSS; /* Unreferenced. */
MessyMemoryWork m229_objWorkTbl[0x88] BSS;
f32 m229_itemScatterTbl[10][2] BSS;
MessyMemoryPlayerStat m229_playerStat BSS;
f32 m229_scoreScale BSS;
u8 m229_shutterStateTbl[4] BSS;
s16 m229_walkSeTbl[4] BSS;
u8 m229_phase BSS;
s16 m229_timer BSS;
u8 m229_roomSlotTbl[10] BSS;
u8 m229_phaseDoneNo BSS;

void m229_Executor(void) {
    m229_ObjectSetup();
}

f32 m229_AngleAdd(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

void m229_ObjWorkInit(void) {
    MessyMemoryWork *work;
    u32 i;

    for (i = 0, work = m229_objWorkTbl; i < 0x88; i++, work++) {
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

void m229_PadClear(s32 playerIndex) {
    HuPadBtn[GwPlayer[playerIndex].pad] = 0;
    HuPadBtnDown[GwPlayer[playerIndex].pad] = 0;
    HuPadStkX[GwPlayer[playerIndex].pad] = 0;
    HuPadStkY[GwPlayer[playerIndex].pad] = 0;
}

void m229_PhaseSet(u8 arg0) {
    m229_phase = arg0;
}

void m229_DividerDraw(Gfx **gfxPos, s32 arg1, s32 arg2) {
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
    gDPLoadTLUT_pal16(gfx++, 0, m229_dividerHAnim->pal);
    for (i = 0, x = 0, y = 108; i < 24; i += 6) {
        gDPLoadTextureTile_4b(gfx++, m229_dividerHAnim->data, G_IM_FMT_CI, 320, 24, 0, i, 320, i + 6, 0,
                              G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                              G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 320 << G_TEXTURE_IMAGE_FRAC, 6 << G_TEXTURE_IMAGE_FRAC);
        gSPTextureRectangle(gfx++, x << 2, (y + i) << 2, (x + 320) << 2, (y + i + 6) << 2, G_TX_RENDERTILE, 0, 0,
                            1 << 10, 1 << 10);
    }

    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(gfx++, 0, m229_dividerVAnim->pal);
    for (i = 0, x = 148, y = 0; i < 240; i += 16) {
        gDPLoadTextureTile_4b(gfx++, m229_dividerVAnim->data, G_IM_FMT_CI, 24, 240, 0, i, 24, i + 16, 0,
                              G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                              G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 24 << G_TEXTURE_IMAGE_FRAC, 16 << G_TEXTURE_IMAGE_FRAC);
        gSPTextureRectangle(gfx++, x << 2, (y + i) << 2, (x + 24) << 2, (y + i + 16) << 2, G_TX_RENDERTILE, 0, 0,
                            1 << 10, 1 << 10);
    }
    *gfxPos = gfx;
}

void m229_DividerObjMain(omObjData *obj) {
    switch (m229_phase) {
        case 8:
            Hu3DModelAttrSet(*obj->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            break;
        case 0xC:
            Hu3DModelAttrSet(*obj->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            break;
    }
}

void m229_DividerObjInit(omObjData *obj) {
    *obj->model = Hu3DHookFuncCreate(0, m229_DividerDraw, 2);
    Hu3DModelCameraSet(*obj->model, HU3D_CAM1);
    Hu3DModelAttrSet(*obj->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->func = m229_DividerObjMain;
}

void m229_DividerCreate(void) {
    omObjData *obj;
    m229_dividerHAnim = HuSprAnimDataGet(HuSprAnimDataRead(0x3E0002));
    m229_dividerVAnim = HuSprAnimDataGet(HuSprAnimDataRead(0x3E0004));
    obj = omAddObj(0xC8, 1, 0, -1, m229_DividerObjInit);
    obj->work[0] = 0;
    m229_dividerWork[0].obj = obj;
}

void m229_CoverObjMain(omObjData *obj) {
    MessyMemoryWork *work;

    switch (m229_phase) {
        case 4:
            if (obj->work[0] == 0) {
                espAttrReset(m229_coverWorkTbl[0].unk42, HUSPR_ATTR_BG);
            }
            break;
        case 5:
            if (obj->work[0] == 0) {
                work = &m229_coverWorkTbl[obj->work[0]];
                if (work->unk04 == 0) {
                    HuAudFXPlay(0x3F1);
                    work->unk04 = 1;
                }
                work->unk5C.x = work->unk5C.y = m229_zoomScale;
                espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
                if (work->unk5C.x <= 0.01 || work->unk5C.y <= 0.01) {
                    m229_phaseDoneNo = 5;
                    espDispOff(work->unk42);
                }
            }
            break;
        case 12:
            if (obj->work[0] == 0) {
                work = &m229_coverWorkTbl[obj->work[0]];
                work->unk5C.x = work->unk5C.y = m229_zoomScale;
                espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
                espDispOn(work->unk42);
                espAttrSet(work->unk42, HUSPR_ATTR_BG);
                if (work->unk5C.x >= 0.23f || work->unk5C.y >= 0.23f) {
                    m229_phaseDoneNo = 12;
                }
            }
            break;
    }
}

void m229_CoverObjInit(omObjData *obj) {
    MessyMemoryWork *work = &m229_coverWorkTbl[obj->work[0]];

    if (obj->work[0] == 0) {
        work->unk44.x = 160.0f;
        work->unk44.y = 120.0f;
        work->unk40 = HuSprAnimDataRead(0x3E0000);
        work->unk42 = espEntry(work->unk40, 0, 0);
        espAttrSet(work->unk42, HUSPR_ATTR_BG);
        espPosSet(work->unk42, work->unk44.x, work->unk44.y);
        espPriSet(work->unk42, 0x5555);
    }
    if (obj->work[0] == 1) {
        work->unk44.x = 160.0f;
        work->unk44.y = 120.0f;
        work->unk40 = HuSprAnimDataRead(0x3E0001);
        work->unk42 = espEntry(work->unk40, 0, 0);
        espAttrSet(work->unk42, HUSPR_ATTR_BG);
        espPosSet(work->unk42, work->unk44.x, work->unk44.y);
        espPriSet(work->unk42, 0xFFFF);
    }
    obj->func = m229_CoverObjMain;
}

void m229_CoverObjCreateAll(void) {
    MessyMemoryWork *work;
    omObjData *obj;
    u8 i;

    for (i = 0; i < 2; i++) {
        work = &m229_coverWorkTbl[i];
        obj = omAddObj(0x3B6, 0, 0, -1, m229_CoverObjInit);
        obj->work[0] = i;
        work->obj = obj;
    }
}

Gfx **m229_GfxRectTexInit(Gfx **gfx) {
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

Gfx **m229_GfxRectXluInit(Gfx **gfx) {
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

Gfx **m229_GfxPrimAlphaSet(Gfx **gfx, u8 alpha) {
    Gfx *gdl = *gfx;

    gDPSetPrimColor(gdl++, 0, 0, 255, 255, 255, alpha);
    *gfx = gdl;
    return gfx;
}

void m229_HandDraw(Gfx **gfxPos, s32 arg1, s32 arg2) {
    MessyMemoryWork *work;
    omObjData *obj;
    HuSprAnimPat *frame;
    Gfx *gfx;
    s32 height;
    s32 i;

    for (i = 0; i < 4; i++) {
        work = &m229_objWorkTbl[i];
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
        if (m229_handDispTbl[obj->work[0]] == 0) {
            continue;
        }
        if (m229_handAlphaTbl[obj->work[0]] < 255) {
            gfxPos = m229_GfxPrimAlphaSet(m229_GfxRectXluInit(gfxPos),
                                                m229_handAlphaTbl[obj->work[0]]);
        } else {
            gfxPos = m229_GfxRectTexInit(gfxPos);
        }
        gfx = *gfxPos;
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
        gDPLoadTLUT_pal16(gfx++, 0, m229_handAnimTbl[obj->work[0]]->pal);
        frame = &m229_handAnimTbl[obj->work[0]]->pat[m229_handPatTbl[obj->work[0]]];
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

void m229_HandPadInput(omObjData *obj) {
    u16 playerNo = obj->work[0];
    MessyMemoryWork *work = &m229_objWorkTbl[playerNo];
    MessyMemoryWork *item;
    MessyMemoryWork *other;
    omObjData *itemObj;
    u8 outside;
    u8 blocked;
    u8 i;
    u8 j;
    u8 k;

    if (HuPadBtnDown[GwPlayer[playerNo].pad] & Z_TRIG) {
        switch (m229_shutterStateTbl[playerNo]) {
            case 0:
                m229_shutterStateTbl[playerNo] = 1;
                break;
            case 1:
                m229_shutterStateTbl[playerNo] = 2;
                break;
        }
    }
    if (m229_shutterStateTbl[playerNo] != 0) {
        return;
    }
    outside = TRUE;
    blocked = FALSE;
    m229_handAlphaTbl[obj->work[0]] = 0xFF;
    for (i = 0; i < 10; i++) {
        if (m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[playerNo][0] - 7.0f <= work->unk44.x &&
            m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[playerNo][0] + 7.0f >= work->unk44.x &&
            m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[playerNo][1] - 15.0f <= work->unk44.y &&
            m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[playerNo][1] + 6.0f >= work->unk44.y) {
            outside = FALSE;
        }
    }
    for (i = 10; i < 20; i++) {
        if (m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[playerNo][0] - 7.0f <= work->unk44.x &&
            m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[playerNo][0] + 7.0f >= work->unk44.x &&
            m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[playerNo][1] - 7.0f <= work->unk44.y &&
            m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[playerNo][1] + 6.0f >= work->unk44.y) {
            outside = FALSE;
        }
    }
    if (m229_handGrabTbl[playerNo] == 1) {
        for (k = 0; k < 10; k++) {
            s32 base = playerNo * 10 + 8;

            item = &m229_objWorkTbl[k + base];
            itemObj = item->obj;
            if (work->unk44.x == item->unk44.x && work->unk44.y == item->unk44.y) {
                for (i = 0; i < 10; i++) {
                    other = &m229_objWorkTbl[i + base];
                    if (itemObj->work[1] * 10 + itemObj->work[0] == other->obj->work[1] * 10 + other->obj->work[0]) {
                        continue;
                    }
                    for (j = 0; j < 20; j++) {
                        if (m229_viewSpotPosTbl[j][0] + m229_viewOfsTbl[playerNo][0] <= other->unk44.x &&
                            m229_viewSpotPosTbl[j][0] + m229_viewOfsTbl[playerNo][0] >= other->unk44.x) {
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
        m229_handAlphaTbl[obj->work[0]] = 150;
    }
    if (HuPadBtnDown[GwPlayer[playerNo].pad] & A_BUTTON) {
        switch (m229_handGrabTbl[playerNo]) {
            case 0:
                for (k = 0; k < 10; k++) {
                    for (i = 0; i < 4; i++) {
                        s32 base = i * 10 + 8;

                        item = &m229_objWorkTbl[k + base];
                        for (j = 0; j < 20; j++) {
                            if (m229_viewSpotPosTbl[j][0] + m229_viewOfsTbl[playerNo][0] <= item->unk44.x &&
                                m229_viewSpotPosTbl[j][0] + m229_viewOfsTbl[playerNo][0] >= item->unk44.x) {
                                if (j < 10) {
                                    if (item->unk44.x - 7.0f <= work->unk44.x && item->unk44.x + 7.0f >= work->unk44.x &&
                                        item->unk44.y - 15.0f <= work->unk44.y && item->unk44.y + 6.0f >= work->unk44.y) {
                                        m229_itemHeldTbl[i * 10 + k] = 1;
                                        m229_handPatTbl[obj->work[0]] = 1;
                                        HuAudPlayerFXPlay(m229_grabSe, obj->work[0]);
                                        m229_handGrabTbl[playerNo] = 1;
                                        omVibrate(playerNo, 5, 0, 5);
                                    }
                                } else {
                                    if (item->unk44.x - 7.0f <= work->unk44.x && item->unk44.x + 7.0f >= work->unk44.x &&
                                        item->unk44.y - 7.0f <= work->unk44.y && item->unk44.y + 6.0f >= work->unk44.y) {
                                        m229_itemHeldTbl[i * 10 + k] = 1;
                                        m229_handPatTbl[obj->work[0]] = 1;
                                        HuAudPlayerFXPlay(m229_grabSe, obj->work[0]);
                                        m229_handGrabTbl[playerNo] = 1;
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

                    item = &m229_objWorkTbl[k + base];
                    itemObj = item->obj;
                    if (work->unk44.x == item->unk44.x && work->unk44.y == item->unk44.y) {
                        for (i = 0; i < 10; i++) {
                            other = &m229_objWorkTbl[i + base];
                            if (itemObj->work[1] * 10 + itemObj->work[0] == other->obj->work[1] * 10 + other->obj->work[0]) {
                                continue;
                            }
                            for (j = 0; j < 20; j++) {
                                if (m229_viewSpotPosTbl[j][0] + m229_viewOfsTbl[playerNo][0] <= other->unk44.x &&
                                    m229_viewSpotPosTbl[j][0] + m229_viewOfsTbl[playerNo][0] >= other->unk44.x) {
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
                                if (m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[playerNo][0] - 7.0f <= work->unk44.x &&
                                    m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[playerNo][0] + 7.0f >= work->unk44.x &&
                                    m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[playerNo][1] - 15.0f <= work->unk44.y &&
                                    m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[playerNo][1] + 6.0f >= work->unk44.y) {
                                    m229_itemHeldTbl[obj->work[0] * 10 + k] = 0;
                                    item->unk44.x = m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[playerNo][0];
                                    item->unk44.y = m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[playerNo][1];
                                    m229_handPatTbl[obj->work[0]] = 0;
                                    HuAudPlayerFXPlay(m229_dropSe, obj->work[0]);
                                    m229_handGrabTbl[playerNo] = 0;
                                    omVibrate(playerNo, 2, 3, 10);
                                }
                            }
                            for (i = 10; i < 20; i++) {
                                if (m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[playerNo][0] - 7.0f <= work->unk44.x &&
                                    m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[playerNo][0] + 7.0f >= work->unk44.x &&
                                    m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[playerNo][1] - 7.0f <= work->unk44.y &&
                                    m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[playerNo][1] + 6.0f >= work->unk44.y) {
                                    m229_itemHeldTbl[obj->work[0] * 10 + k] = 0;
                                    item->unk44.x = m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[playerNo][0];
                                    item->unk44.y = m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[playerNo][1];
                                    m229_handPatTbl[obj->work[0]] = 0;
                                    HuAudPlayerFXPlay(m229_dropSe, obj->work[0]);
                                    m229_handGrabTbl[playerNo] = 0;
                                    omVibrate(playerNo, 2, 3, 10);
                                }
                            }
                        }
                    }
                }
                break;
        }
    }
    if (HuPadStkX[GwPlayer[playerNo].pad] < -29) {
        work->unk44.x -= 2.0f;
        if (work->unk44.x < m229_viewOfsTbl[playerNo][0] + 30.0f) {
            work->unk44.x = m229_viewOfsTbl[playerNo][0] + 30.0f;
        }
    }
    if (HuPadStkX[GwPlayer[playerNo].pad] >= 30) {
        work->unk44.x += 2.0f;
        if (work->unk44.x > m229_viewOfsTbl[playerNo][0] + 140.0f) {
            work->unk44.x = m229_viewOfsTbl[playerNo][0] + 140.0f;
        }
    }
    if (HuPadStkY[GwPlayer[playerNo].pad] >= 30) {
        work->unk44.y -= 2.0f;
        if (work->unk44.y < m229_viewOfsTbl[playerNo][1] + 20.0f) {
            work->unk44.y = m229_viewOfsTbl[playerNo][1] + 20.0f;
        }
    }
    if (HuPadStkY[GwPlayer[playerNo].pad] < -29) {
        work->unk44.y += 2.0f;
        if (work->unk44.y > m229_viewOfsTbl[playerNo][1] + 108.0f) {
            work->unk44.y = m229_viewOfsTbl[playerNo][1] + 108.0f;
        }
    }
}

void m229_HandComInputCalc(omObjData *obj) {
    u16 playerNo = obj->work[0];
    MessyMemoryWork *work = &m229_objWorkTbl[playerNo];
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
            if (m229_timer == 300 || m229_timer == 210) {
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
        switch (m229_shutterStateTbl[playerNo]) {
            case 0:
                m229_shutterStateTbl[playerNo] = 1;
                work->unk12++;
                work->unk06 = 0;
                break;
            case 1:
                m229_shutterStateTbl[playerNo] = 2;
                work->unk12++;
                work->unk06 = 0;
                break;
        }
    }
    if (m229_shutterStateTbl[playerNo] != 0) {
        return;
    }
    outside = TRUE;
    blocked = FALSE;
    m229_handAlphaTbl[obj->work[0]] = 0xFF;
    for (i = 0; i < 10; i++) {
        if (m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[playerNo][0] - 7.0f <= work->unk44.x &&
            m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[playerNo][0] + 7.0f >= work->unk44.x &&
            m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[playerNo][1] - 15.0f <= work->unk44.y &&
            m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[playerNo][1] + 6.0f >= work->unk44.y) {
            outside = FALSE;
        }
    }
    for (i = 10; i < 20; i++) {
        if (m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[playerNo][0] - 7.0f <= work->unk44.x &&
            m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[playerNo][0] + 7.0f >= work->unk44.x &&
            m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[playerNo][1] - 7.0f <= work->unk44.y &&
            m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[playerNo][1] + 6.0f >= work->unk44.y) {
            outside = FALSE;
        }
    }
    if (m229_handGrabTbl[playerNo] == 1) {
        for (k = 0; k < 10; k++) {
            s32 base = playerNo * 10 + 8;

            item = &m229_objWorkTbl[k + base];
            itemObj = item->obj;
            if (work->unk44.x == item->unk44.x && work->unk44.y == item->unk44.y) {
                for (i = 0; i < 10; i++) {
                    other = &m229_objWorkTbl[i + base];
                    if (itemObj->work[1] * 10 + itemObj->work[0] == other->obj->work[1] * 10 + other->obj->work[0]) {
                        continue;
                    }
                    for (j = 0; j < 20; j++) {
                        if (m229_viewSpotPosTbl[j][0] + m229_viewOfsTbl[playerNo][0] <= other->unk44.x &&
                            m229_viewSpotPosTbl[j][0] + m229_viewOfsTbl[playerNo][0] >= other->unk44.x) {
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
        m229_handAlphaTbl[obj->work[0]] = 150;
    }

    if (work->unk12 == 0) {
        switch (work->unk06) {
            case 0:
                slot = rand8() % 10;
                item = &m229_objWorkTbl[slot + 8 + playerNo * 10];
                if (m229_viewOfsTbl[playerNo][1] + 80.0f < item->unk44.y) {
                    work->unk08 = slot;
                    work->unk1C = item->unk44.x;
                    work->unk20 = item->unk44.y;
                    work->unk06 = 1;
                }
                if (work->unk06 != 1 && m229_comKnownTbl[playerNo][slot] == 0 &&
                    m229_timer > 450) {
                    work->unk08 = slot;
                    work->unk1C = item->unk44.x;
                    work->unk20 = item->unk44.y;
                    work->unk06 = 10;
                }
                break;
            case 10:
                MM_CPU_STEER(work);
                item = &m229_objWorkTbl[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, item->unk44.x, item->unk44.y)) {
                    work->unk06 = 0;
                }
                break;
            case 9:
                for (k = 0; k < 10; k++) {
                    if (k != work->unk08) {
                        item = &m229_objWorkTbl[k + 8 + playerNo * 10];
                        if (m229_viewOfsTbl[playerNo][1] + 80.0f < item->unk44.y) {
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
                item = &m229_objWorkTbl[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, item->unk44.x, item->unk44.y)) {
                    m229_itemHeldTbl[playerNo * 10 + work->unk08] = 1;
                    m229_handPatTbl[obj->work[0]] = 1;
                    HuAudPlayerFXPlay(m229_grabSe, obj->work[0]);
                    m229_handGrabTbl[playerNo] = 1;
                    if (m229_comKnownTbl[playerNo][work->unk08] == 1) {
                        work->unk06 = 2;
                    } else {
                        work->unk06 = 3;
                    }
                }
                break;
            case 2:
                itemObj = m229_objWorkTbl[work->unk08 + 8 + playerNo * 10].obj;
                for (k = 0; k < 10; k++) {
                    if (m229_roomItemTbl[k] == itemObj->work[0]) {
                        work->unk1C = m229_viewSpotPosTbl[k][0] + m229_viewOfsTbl[playerNo][0];
                        work->unk20 = m229_viewSpotPosTbl[k][1] + m229_viewOfsTbl[playerNo][1];
                        work->unk0A = k;
                        work->unk06 = 4;
                    }
                }
                break;
            case 3:
                item = &m229_objWorkTbl[work->unk08 + 8 + playerNo * 10];
                itemObj = item->obj;
                slot = rand8() % 10;
                found = FALSE;
                for (k = 0; k < 10; k++) {
                    other = &m229_objWorkTbl[k + 8 + playerNo * 10];
                    if (m229_viewSpotPosTbl[slot][0] + m229_viewOfsTbl[playerNo][0] == other->unk44.x &&
                        m229_viewSpotPosTbl[slot][1] + m229_viewOfsTbl[playerNo][1] == other->unk44.y) {
                        found = TRUE;
                    }
                }
                for (k = 0; k < 10; k++) {
                    if (m229_comKnownTbl[playerNo][k] == 1 && m229_roomItemTbl[slot] == k) {
                        found = TRUE;
                    }
                }
                if (!found && m229_roomItemTbl[slot] != itemObj->work[0]) {
                    work->unk1C = m229_viewSpotPosTbl[slot][0] + m229_viewOfsTbl[playerNo][0];
                    work->unk20 = m229_viewSpotPosTbl[slot][1] + m229_viewOfsTbl[playerNo][1];
                    work->unk0A = slot;
                    work->unk06 = 4;
                    work->unk0E = 0;
                }
                if (!found && m229_roomItemTbl[slot] == itemObj->work[0] && work->unk14 >= 6) {
                    work->unk1C = m229_viewSpotPosTbl[10][0] + m229_viewOfsTbl[playerNo][0];
                    work->unk20 = m229_viewSpotPosTbl[10][1] + m229_viewOfsTbl[playerNo][1];
                    work->unk0A = slot;
                    work->unk0C = 10;
                    work->unk06 = 5;
                    work->unk0E = 0;
                }
                if (++work->unk0E >= 50) {
                    work->unk0E = 0;
                    work->unk06 = 9;
                    for (i = 0; i < 20; i++) {
                        if (m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[playerNo][0] - 7.0f <= work->unk44.x &&
                            m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[playerNo][0] + 7.0f >= work->unk44.x &&
                            m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[playerNo][1] - 7.0f <= work->unk44.y &&
                            m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[playerNo][1] + 6.0f >= work->unk44.y) {
                            m229_itemHeldTbl[playerNo * 10 + work->unk08] = 0;
                            item->unk44.x = m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[playerNo][0];
                            item->unk44.y = m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[playerNo][1];
                            m229_handPatTbl[obj->work[0]] = 0;
                            HuAudPlayerFXPlay(m229_dropSe, obj->work[0]);
                            m229_handGrabTbl[playerNo] = 0;
                        }
                    }
                }
                break;
            case 4:
                MM_CPU_STEER(work);
                if (m229_timer > 150) {
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
                item = &m229_objWorkTbl[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, work->unk1C, work->unk20)) {
                    m229_itemHeldTbl[playerNo * 10 + work->unk08] = 0;
                    m229_handPatTbl[obj->work[0]] = 0;
                    HuAudPlayerFXPlay(m229_dropSe, obj->work[0]);
                    m229_handGrabTbl[playerNo] = 0;
                    item->unk44.x = m229_viewSpotPosTbl[work->unk0A][0] + m229_viewOfsTbl[playerNo][0];
                    item->unk44.y = m229_viewSpotPosTbl[work->unk0A][1] + m229_viewOfsTbl[playerNo][1];
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
                item = &m229_objWorkTbl[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, work->unk1C, work->unk20)) {
                    m229_itemHeldTbl[playerNo * 10 + work->unk08] = 0;
                    m229_handPatTbl[obj->work[0]] = 0;
                    HuAudPlayerFXPlay(m229_dropSe, obj->work[0]);
                    m229_handGrabTbl[playerNo] = 0;
                    item->unk44.x = m229_viewSpotPosTbl[work->unk0C][0] + m229_viewOfsTbl[playerNo][0];
                    item->unk44.y = m229_viewSpotPosTbl[work->unk0C][1] + m229_viewOfsTbl[playerNo][1];
                    work->unk06 = 6;
                }
                break;
            case 6:
                slot = rand8() % 10;
                item = &m229_objWorkTbl[slot + 8 + playerNo * 10];
                if (item->unk44.y < m229_viewOfsTbl[playerNo][1] + 80.0f &&
                    m229_comKnownTbl[playerNo][slot] != 1) {
                    work->unk08 = slot;
                    work->unk1C = item->unk44.x;
                    work->unk20 = item->unk44.y;
                    work->unk06 = 7;
                }
                break;
            case 7:
                MM_CPU_STEER(work);
                item = &m229_objWorkTbl[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, item->unk44.x, item->unk44.y)) {
                    m229_itemHeldTbl[playerNo * 10 + work->unk08] = 1;
                    m229_handPatTbl[obj->work[0]] = 1;
                    HuAudPlayerFXPlay(m229_grabSe, obj->work[0]);
                    m229_handGrabTbl[playerNo] = 1;
                    work->unk1C = m229_viewSpotPosTbl[work->unk0A][0] + m229_viewOfsTbl[playerNo][0];
                    work->unk20 = m229_viewSpotPosTbl[work->unk0A][1] + m229_viewOfsTbl[playerNo][1];
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
                item = &m229_objWorkTbl[slot + 8 + playerNo * 10];
                if (item->unk44.y < m229_viewOfsTbl[playerNo][1] + 80.0f) {
                    work->unk08 = slot;
                    work->unk38 = work->unk1C = item->unk44.x;
                    work->unk3C = work->unk20 = item->unk44.y;
                    work->unk06 = 1;
                }
                break;
            case 1:
                MM_CPU_STEER(work);
                item = &m229_objWorkTbl[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, item->unk44.x, item->unk44.y)) {
                    m229_itemHeldTbl[playerNo * 10 + work->unk08] = 1;
                    m229_handPatTbl[obj->work[0]] = 1;
                    HuAudPlayerFXPlay(m229_grabSe, obj->work[0]);
                    m229_handGrabTbl[playerNo] = 1;
                    work->unk14--;
                    work->unk06 = 2;
                }
                break;
            case 2:
                slot = rand8() % 10;
                work->unk1C = m229_viewSpotPosTbl[slot + 10][0] + m229_viewOfsTbl[playerNo][0];
                work->unk20 = m229_viewSpotPosTbl[slot + 10][1] + m229_viewOfsTbl[playerNo][1];
                work->unk0A = slot + 10;
                work->unk06 = 3;
                break;
            case 3:
                MM_CPU_STEER(work);
                item = &m229_objWorkTbl[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, work->unk1C, work->unk20)) {
                    m229_itemHeldTbl[playerNo * 10 + work->unk08] = 0;
                    m229_handPatTbl[obj->work[0]] = 0;
                    HuAudPlayerFXPlay(m229_dropSe, obj->work[0]);
                    m229_handGrabTbl[playerNo] = 0;
                    item->unk44.x = m229_viewSpotPosTbl[work->unk0A][0] + m229_viewOfsTbl[playerNo][0];
                    item->unk44.y = m229_viewSpotPosTbl[work->unk0A][1] + m229_viewOfsTbl[playerNo][1];
                    work->unk06 = 4;
                }
                break;
            case 4:
                slot = rand8() % 10;
                item = &m229_objWorkTbl[slot + 8 + playerNo * 10];
                if (item->unk44.y < m229_viewOfsTbl[playerNo][1] + 80.0f) {
                    work->unk08 = slot;
                    work->unk1C = item->unk44.x;
                    work->unk20 = item->unk44.y;
                    work->unk06 = 5;
                }
                break;
            case 5:
                MM_CPU_STEER(work);
                item = &m229_objWorkTbl[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, item->unk44.x, item->unk44.y)) {
                    m229_itemHeldTbl[playerNo * 10 + work->unk08] = 1;
                    m229_handPatTbl[obj->work[0]] = 1;
                    HuAudPlayerFXPlay(m229_grabSe, obj->work[0]);
                    m229_handGrabTbl[playerNo] = 1;
                    work->unk14--;
                    work->unk06 = 6;
                }
                break;
            case 6:
                for (k = 0; k < 10; k++) {
                    if (work->unk38 == m229_viewSpotPosTbl[k][0] + m229_viewOfsTbl[playerNo][0] &&
                        work->unk3C == m229_viewSpotPosTbl[k][1] + m229_viewOfsTbl[playerNo][1]) {
                        work->unk1C = m229_viewSpotPosTbl[k][0] + m229_viewOfsTbl[playerNo][0];
                        work->unk20 = m229_viewSpotPosTbl[k][1] + m229_viewOfsTbl[playerNo][1];
                        work->unk0A = k;
                        work->unk06 = 7;
                    }
                }
                break;
            case 7:
                MM_CPU_STEER(work);
                item = &m229_objWorkTbl[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, work->unk1C, work->unk20)) {
                    m229_itemHeldTbl[playerNo * 10 + work->unk08] = 0;
                    m229_handPatTbl[obj->work[0]] = 0;
                    HuAudPlayerFXPlay(m229_dropSe, obj->work[0]);
                    m229_handGrabTbl[playerNo] = 0;
                    item->unk44.x = m229_viewSpotPosTbl[work->unk0A][0] + m229_viewOfsTbl[playerNo][0];
                    item->unk44.y = m229_viewSpotPosTbl[work->unk0A][1] + m229_viewOfsTbl[playerNo][1];
                    work->unk06 = 8;
                    work->unk14++;
                }
                break;
            case 8:
                for (k = 0; k < 10; k++) {
                    item = &m229_objWorkTbl[k + 8 + playerNo * 10];
                    if (m229_viewOfsTbl[playerNo][1] + 80.0f < item->unk44.y) {
                        work->unk08 = k;
                        work->unk1C = item->unk44.x;
                        work->unk20 = item->unk44.y;
                        work->unk06 = 9;
                    }
                }
                break;
            case 9:
                MM_CPU_STEER(work);
                item = &m229_objWorkTbl[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, item->unk44.x, item->unk44.y)) {
                    m229_itemHeldTbl[playerNo * 10 + work->unk08] = 1;
                    m229_handPatTbl[obj->work[0]] = 1;
                    HuAudPlayerFXPlay(m229_grabSe, obj->work[0]);
                    m229_handGrabTbl[playerNo] = 1;
                    work->unk06 = 10;
                }
                break;
            case 10:
                for (k = 0; k < 10; k++) {
                    found = FALSE;
                    for (i = 0; i < 10; i++) {
                        other = &m229_objWorkTbl[i + 8 + playerNo * 10];
                        if (m229_viewSpotPosTbl[k][0] + m229_viewOfsTbl[playerNo][0] == other->unk44.x &&
                            m229_viewSpotPosTbl[k][1] + m229_viewOfsTbl[playerNo][1] == other->unk44.y) {
                            found = TRUE;
                        }
                    }
                    if (!found) {
                        work->unk1C = m229_viewSpotPosTbl[k][0] + m229_viewOfsTbl[playerNo][0];
                        work->unk20 = m229_viewSpotPosTbl[k][1] + m229_viewOfsTbl[playerNo][1];
                        work->unk0A = k;
                        work->unk06 = 11;
                    }
                }
                break;
            case 11:
                MM_CPU_STEER(work);
                item = &m229_objWorkTbl[work->unk08 + 8 + playerNo * 10];
                if (MM_CPU_NEAR(work, work->unk1C, work->unk20)) {
                    m229_itemHeldTbl[playerNo * 10 + work->unk08] = 0;
                    m229_handPatTbl[obj->work[0]] = 0;
                    HuAudPlayerFXPlay(m229_dropSe, obj->work[0]);
                    m229_handGrabTbl[playerNo] = 0;
                    item->unk44.x = m229_viewSpotPosTbl[work->unk0A][0] + m229_viewOfsTbl[playerNo][0];
                    item->unk44.y = m229_viewSpotPosTbl[work->unk0A][1] + m229_viewOfsTbl[playerNo][1];
                    work->unk06 = 12;
                    work->unk14++;
                    work->unk12 = 5;
                }
                break;
        }
    }

    if (work->unk24 == 1.0f) {
        work->unk44.x -= 2.0f;
        if (work->unk44.x < m229_viewOfsTbl[playerNo][0] + 30.0f) {
            work->unk44.x = m229_viewOfsTbl[playerNo][0] + 30.0f;
        }
    }
    if (work->unk24 == 2.0f) {
        work->unk44.x += 2.0f;
        if (work->unk44.x > m229_viewOfsTbl[playerNo][0] + 140.0f) {
            work->unk44.x = m229_viewOfsTbl[playerNo][0] + 140.0f;
        }
    }
    if (work->unk28 == 1.0f) {
        work->unk44.y -= 2.0f;
        if (work->unk44.y < m229_viewOfsTbl[playerNo][1] + 20.0f) {
            work->unk44.y = m229_viewOfsTbl[playerNo][1] + 20.0f;
        }
    }
    if (work->unk28 == 2.0f) {
        work->unk44.y += 2.0f;
        if (work->unk44.y > m229_viewOfsTbl[playerNo][1] + 108.0f) {
            work->unk44.y = m229_viewOfsTbl[playerNo][1] + 108.0f;
        }
    }
}

void m229_HandComInput(omObjData *obj) {
    s32 playerIndex = (u16)obj->work[0];

    if (m229_phase == 9) {
        switch (GwPlayer[playerIndex].cpu_difficulty) {
            case 0:
            case 1:
            case 2:
            case 3:
                m229_HandComInputCalc(obj);
                break;
        }
    }
}

void m229_HandObjMain(omObjData *obj) {
    u16 playerNo = obj->work[0];
    MessyMemoryWork *work = &m229_objWorkTbl[playerNo];
    s8 found;
    s8 count;
    s8 i;
    s8 j;
    s8 chance;

    switch (m229_phase) {
        case 8:
            m229_handDispTbl[obj->work[0]] = 1;
            work->unk18 += 0.05;
            if (work->unk18 > 1.0f) {
                work->unk18 = 1.0f;
            }
            if ((GwPlayer[playerNo].stat & PLAYER_IS_CPU) && work->unk16 == 0) {
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
                        if (m229_roomSpotItemTbl[j] == i) {
                            m229_comKnownTbl[playerNo][i] = 1;
                        }
                    }
                }
                for (i = 9; i >= 0; i--) {
                    found = FALSE;
                    if (count >= work->unk04) {
                        break;
                    }
                    for (j = 0; j < 10; j++) {
                        if (m229_roomSpotItemTbl[j] == i) {
                            found = TRUE;
                        }
                    }
                    if (!found && m229_comKnownTbl[playerNo][i] != 1) {
                        m229_comKnownTbl[playerNo][i] = 1;
                        count++;
                    }
                }
            }
            break;
        case 9:
            if (m229_timer > 0) {
                if (GwPlayer[playerNo].stat & PLAYER_IS_CPU) {
                    m229_HandComInput(obj);
                } else {
                    m229_HandPadInput(obj);
                }
            }
            break;
        case 11:
            work->unk18 -= 0.03;
            if (work->unk18 <= 0.05f) {
                work->unk18 = 0.05f;
                m229_handDispTbl[obj->work[0]] = 0;
            }
            break;
    }
}

void m229_HandObjInit(omObjData *obj) {
    s32 chr = GwPlayer[obj->work[0]].chr;
    MessyMemoryWork *work = &m229_objWorkTbl[obj->work[0]];
    s16 i;

    work->unk40 = HuSprAnimDataRead(m229_handSprTbl[chr].fileId);
    m229_handAnimTbl[obj->work[0]] = HuSprAnimDataGet(work->unk40);
    for (i = 0; i < 4; i++) {
        if (obj->work[0] == i) {
            work->unk44.x = m229_viewOfsTbl[obj->work[0]][0] + 88.0f;
            work->unk44.y = m229_viewOfsTbl[obj->work[0]][1] + 63.0f;
        }
    }
    work->unk5C.x = work->unk5C.y = work->unk18 = 0.1f;
    m229_handAlphaTbl[obj->work[0]] = 0xFF;
    m229_handDispTbl[obj->work[0]] = 0;
    if (obj->work[0] == 3) {
        Hu3DModelCameraSet(Hu3DHookFuncCreate(0, m229_HandDraw, 2), HU3D_CAM0);
    }
    obj->func = m229_HandObjMain;
}

void m229_HandObjCreateAll(void) {
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
        work = &m229_objWorkTbl[i];
        obj = omAddObj(0x96, 4, 1, -1, m229_HandObjInit);
        obj->work[0] = playerNo;
        work->obj = obj;
    }
}

void m229_PlayerObjMain(omObjData *obj) {
    u16 index = obj->work[0];
    MessyMemoryWork *work = &m229_playerWorkTbl[obj->work[0]];
    s16 near;
    s16 i;

    switch (m229_phase) {
        case 5:
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            break;
        case 6:
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            switch (work->unk04) {
                case 0:
                    Hu3DMotionModelSet(*obj->model, obj->motion[2]);
                    work->unk04 = 1;
                    break;
                case 1:
                    if (index == 0 || index == 2) {
                        obj->rot.y = m229_AngleAdd(obj->rot.y, 20.0f);
                    } else {
                        obj->rot.y = m229_AngleAdd(obj->rot.y, -20.0f);
                    }
                    if ((s16)obj->rot.y == 180) {
                        work->unk04 = 2;
                        obj->rot.y = 180.0f;
                        Hu3DMotionModelSet(*obj->model, obj->motion[0]);
                    }
                    break;
                case 2:
                    work->unk08++;
                    if (work->unk08 >= 5) {
                        work->unk04 = 3;
                        Hu3DMotionModelSet(*obj->model, obj->motion[5]);
                        PlayerFXPlay(0x286, obj->work[0]);
                    }
                    break;
                case 3:
                    if (Hu3DData[*obj->model].motTime >= Hu3DMotion[Hu3DData[*obj->model].motId].unk02) {
                        work->unk04 = 4;
                        Hu3DMotionModelSet(*obj->model, obj->motion[2]);
                        Hu3DMotionAttrSet(*obj->model, 2, 2);
                    }
                    break;
                case 4:
                    if (index == 0 || index == 2) {
                        obj->rot.y = m229_AngleAdd(obj->rot.y, 15.0f);
                    } else {
                        obj->rot.y = m229_AngleAdd(obj->rot.y, -15.0f);
                    }
                    if ((s16)obj->rot.y == 90 || (s16)obj->rot.y == 270) {
                        work->unk04 = 5;
                    }
                    break;
                case 5:
                    obj->trans.x -= m229_playerWalkTbl[index][0];
                    if (obj->work[0] == 3) {
                        near = FALSE;
                        for (i = 0; i < 4; i++) {
                            if (abs((&m229_playerWorkTbl[i])->obj->trans.x) < 651) {
                                near = TRUE;
                            }
                        }
                        if (!near) {
                            m229_phaseDoneNo = 6;
                            for (i = 0; i < 4; i++) {
                                Hu3DModelAttrSet(*(&m229_playerWorkTbl[i])->obj->model, HU3D_ATTR_DISPOFF,
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
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            switch (work->unk04) {
                case 0:
                    obj->trans.x += m229_playerWalkTbl[index][0];
                    if (work->unk06 >= 8) {
                        if (m229_walkSeTbl[obj->work[0]] != -1) {
                            HuAudFXStop(m229_walkSeTbl[obj->work[0]]);
                        }
                        m229_walkSeTbl[obj->work[0]] = PlayerFXPlay(m229_walkSe, obj->work[0]);
                        work->unk06 = 0;
                    } else {
                        work->unk06++;
                    }
                    if (abs(obj->trans.x) <= abs(m229_playerWalkTbl[index][1])) {
                        obj->trans.x = m229_playerWalkTbl[index][1];
                        work->unk04 = 1;
                        Hu3DMotionModelSet(*obj->model, obj->motion[1]);
                    }
                    break;
                case 1:
                    if (obj->rot.y >= 270.0f) {
                        obj->rot.y = m229_AngleAdd(obj->rot.y, 15.0f);
                    } else if (obj->rot.y <= 90.0f) {
                        obj->rot.y = m229_AngleAdd(obj->rot.y, -15.0f);
                    }
                    if ((s16)obj->rot.y == 0) {
                        work->unk04 = 2;
                        Hu3DMotionModelSet(*obj->model, obj->motion[0]);
                        if (index == 3) {
                            m229_phaseDoneNo = 14;
                        }
                    }
                    break;
            }
            break;
        case 16:
            if (m229_timer >= 0 && work->unk04 == 2) {
                if (m229_tieCnt == 0) {
                    if (index == m229_rankTbl[0]) {
                        Hu3DMotionModelSet(*obj->model, obj->motion[3]);
                        HuAudCharVoicePlay((m229_voiceChrTbl[GwPlayer[obj->work[0]].chr] << 16) | 0x2F);
                    } else {
                        Hu3DMotionModelSet(*obj->model, obj->motion[4]);
                    }
                }
                if (m229_tieCnt == 1) {
                    if (index == m229_rankTbl[0] || index == m229_rankTbl[1]) {
                        Hu3DMotionModelSet(*obj->model, obj->motion[3]);
                        HuAudCharVoicePlay((m229_voiceChrTbl[GwPlayer[obj->work[0]].chr] << 16) | 0x2F);
                    } else {
                        Hu3DMotionModelSet(*obj->model, obj->motion[4]);
                    }
                }
                if (m229_tieCnt == 2) {
                    if (index == m229_rankTbl[0] || index == m229_rankTbl[1] ||
                        index == m229_rankTbl[2]) {
                        Hu3DMotionModelSet(*obj->model, obj->motion[3]);
                        HuAudCharVoicePlay((m229_voiceChrTbl[GwPlayer[obj->work[0]].chr] << 16) | 0x2F);
                    } else {
                        Hu3DMotionModelSet(*obj->model, obj->motion[4]);
                    }
                }
                if (m229_tieCnt == 3) {
                    Hu3DMotionModelSet(*obj->model, obj->motion[3]);
                    HuAudCharVoicePlay((m229_voiceChrTbl[GwPlayer[obj->work[0]].chr] << 16) | 0x2F);
                }
                if (m229_tieCnt == 4) {
                    Hu3DMotionModelSet(*obj->model, obj->motion[4]);
                }
                work->unk04 = 3;
            }
            break;
    }
    if (GwPlayer[obj->work[0]].chr != CHAR_DK) {
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y - 5.0f, obj->trans.z);
    } else {
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y - 10.0f, obj->trans.z + 30.0f);
    }
}

void m229_PlayerObjInit(omObjData *obj) {
    u32 playerNo = obj->work[0];
    u16 index = obj->work[0];
    s8 chr = GwPlayer[playerNo].chr;

    *obj->model = Hu3DModelRead(omCharModelTbl[chr].model | omCharModelTbl[chr].motion[0], 0x2A9);
    Hu3DModelRemakeStatic(*obj->model);
    Hu3DModelDynamicFree(*obj->model);
    obj->model[1] = Hu3DModelRead2(0, 0x14C9);
    Hu3DModelObjAttrSet(obj->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    HuTranslateF(Hu3DData[obj->model[1]].mtx, 0.0f, 15.0f, 0.0f);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 1));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 2));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chr, 0x36));
    omObjMotionRead(obj, 5, CharMotionDataNumGet(chr, 0x7A));
    Hu3DMotionModelSet(*obj->model, *obj->motion);
    Hu3DMotionTimeSet(*obj->model, 0.0f);
    Hu3DMotionAttrSet(*obj->model, 2, 2);
    switch (index) {
        case 0:
        case 1:
            obj->trans.x = m229_playerWalkTbl[index][1];
            obj->trans.y = -180.0f;
            obj->trans.z = -1000.0f;
            break;
        case 2:
        case 3:
            obj->trans.x = m229_playerWalkTbl[index][1];
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
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM0);
    obj->func = m229_PlayerObjMain;
}

void m229_PlayerObjCreateAll(void) {
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
        work = &m229_playerWorkTbl[i];
        obj = omAddObj(0x352, 9, 0x3C, -1, m229_PlayerObjInit);
        obj->work[0] = playerNo;
        work->obj = obj;
    }
}

void m229_ItemObjMain(omObjData *obj) {
    MessyMemoryWork *work = &m229_objWorkTbl[obj->work[0] + 8 + obj->work[1] * 10];
    MessyMemoryWork *marker;
    MessyMemoryWork *cursor;
    u8 found;
    u8 slot;
    u8 i;
    u8 j;

    switch (m229_phase) {
        case 2:
            m229_itemPlaceNum = 7;
            break;
        case 3:
            if (obj->work[1] == 4 && m229_roomSlotTbl[obj->work[0]] == 10 &&
                m229_itemPlaceCnt < m229_itemPlaceNum) {
                slot = rand8() % 10;
                if (slot != m229_roomSlotTbl[0] && slot != m229_roomSlotTbl[1] &&
                    slot != m229_roomSlotTbl[2] && slot != m229_roomSlotTbl[3] &&
                    slot != m229_roomSlotTbl[4] && slot != m229_roomSlotTbl[5] &&
                    slot != m229_roomSlotTbl[6] && slot != m229_roomSlotTbl[7] &&
                    slot != m229_roomSlotTbl[8] && slot != m229_roomSlotTbl[9]) {
                    m229_roomSlotTbl[obj->work[0]] = slot;
                    m229_itemPlaceCnt++;
                    for (i = 0; i < 10; i++) {
                        if (slot == i) {
                            work->unk44.x = m229_roomSpotPosTbl[slot + 10][0];
                            work->unk44.y = m229_roomSpotPosTbl[slot + 10][1];
                        }
                    }
                }
            }
            if (m229_itemPlaceCnt >= m229_itemPlaceNum) {
                if (obj->work[1] == 4) {
                    espPriSet(work->unk42, 0x1111);
                    espPosSet(work->unk42, work->unk44.x, work->unk44.y);
                }
                for (i = 0; i < 10; i++) {
                    work = &m229_objWorkTbl[i + 48];
                    obj = work->obj;
                    for (j = 0; j < 20; j++) {
                        if (work->unk44.x == m229_roomSpotPosTbl[j][0] &&
                            work->unk44.y == m229_roomSpotPosTbl[j][1]) {
                            m229_roomSpotItemTbl[j] = obj->work[0];
                        }
                    }
                }
            }
            break;
        case 4:
            if (obj->work[1] == 4) {
                espAttrReset(work->unk42, HUSPR_ATTR_BG);
            }
            if (obj->work[1] < 4) {
                for (i = 0; i < 20; i++) {
                    if (m229_roomSpotItemTbl[i] == obj->work[0]) {
                        work->unk44.x = m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[obj->work[1]][0];
                        work->unk44.y = m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[obj->work[1]][1];
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
                    m229_phaseDoneNo = 4;
                }
            }
            break;
        case 5:
            if (obj->work[1] == 4) {
                u32 index = obj->work[0] + 48;

                work = &m229_objWorkTbl[index];
                for (i = 0; i < 20; i++) {
                    if (work->unk44.x == m229_roomSpotPosTbl[i][0] && work->unk44.y == m229_roomSpotPosTbl[i][1]) {
                        m229_itemScatterTbl[obj->work[0]][0] = m229_itemScatterVelTbl[i][0] * 2.0f;
                        m229_itemScatterTbl[obj->work[0]][1] = m229_itemScatterVelTbl[i][1] * 2.0f;
                    }
                }
                work->unk44.x += m229_itemScatterTbl[obj->work[0]][0];
                work->unk44.y += m229_itemScatterTbl[obj->work[0]][1];
                espPosSet(work->unk42, work->unk44.x, work->unk44.y);
                work->unk5C.x = work->unk5C.y = m229_zoomScale;
                espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
                if (work->unk5C.x <= 0.01 || work->unk5C.y <= 0.01) {
                    espDispOff(work->unk42);
                    for (i = 0; i < 10; i++) {
                        if (obj->work[0] == m229_roomItemTbl[i]) {
                            work->unk44.x = m229_roomSpotPosTbl[i][0];
                            work->unk44.y = m229_roomSpotPosTbl[i][1];
                        }
                    }
                    for (i = 0; i < 20; i++) {
                        if (work->unk44.x == m229_roomSpotPosTbl[i][0] &&
                            work->unk44.y == m229_roomSpotPosTbl[i][1]) {
                            m229_itemScatterTbl[obj->work[0]][0] = -m229_itemScatterVelTbl[i][0];
                            m229_itemScatterTbl[obj->work[0]][1] = -m229_itemScatterVelTbl[i][1];
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
                switch (m229_itemHeldTbl[obj->work[1] * 10 + obj->work[0]]) {
                    case 0:
                        espPriSet(work->unk42, 0xDDDD);
                        for (i = 15; i < 21; i++) {
                            if (work->unk44.x ==
                                    m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[obj->work[1]][0] &&
                                work->unk44.y ==
                                    m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[obj->work[1]][1]) {
                                espPriSet(work->unk42, 0xBBBB);
                            }
                        }
                        break;
                    case 1:
                        cursor = &m229_objWorkTbl[obj->work[1]];
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
                if (m229_itemHeldTbl[obj->work[1] * 10 + obj->work[0]] == 1) {
                    marker = &m229_objWorkTbl[obj->work[0] + 0x56 + obj->work[1] * 10];
                    if (m229_viewOfsTbl[obj->work[1]][1] + 93.0f <= work->unk44.y) {
                        for (i = 1; i < 4; i++) {
                            if (abs(m229_viewOfsTbl[obj->work[1]][0] + m229_trayPosTbl[work->unk06][0] -
                                    work->unk44.x) >
                                abs(m229_viewOfsTbl[obj->work[1]][0] + m229_trayPosTbl[i][0] -
                                    work->unk44.x)) {
                                work->unk06 = i;
                            }
                        }
                        work->unk44.x =
                            m229_viewOfsTbl[obj->work[1]][0] + m229_trayPosTbl[work->unk06][0];
                        work->unk44.y =
                            m229_viewOfsTbl[obj->work[1]][1] + m229_trayPosTbl[work->unk06][1];
                        espPriSet(marker->unk42, 0xABBB);
                    }
                    if (m229_viewOfsTbl[obj->work[1]][1] + 93.0f > work->unk44.y) {
                        if (m229_viewOfsTbl[obj->work[1]][0] + 80.0f >= work->unk44.x && work->unk08 == 0) {
                            work->unk18 = 2.0f;
                            work->unk08 = 1;
                        }
                        if (m229_viewOfsTbl[obj->work[1]][0] + 80.0f < work->unk44.x && work->unk08 == 0) {
                            work->unk18 = -2.0f;
                            work->unk08 = 1;
                        }
                        work->unk1C += 0.5f;
                        work->unk44.x += work->unk18;
                        work->unk44.y += work->unk1C;
                        espPriSet(work->unk42, 0xCDDD);
                        espPriSet(marker->unk42, 0xCDEE);
                    }
                    if (m229_viewOfsTbl[obj->work[1]][1] + 93.0f <= work->unk44.y) {
                        m229_itemHeldTbl[obj->work[1] * 10 + obj->work[0]] = 0;
                        espDispOn(marker->unk42);
                        espPosSet(marker->unk42, work->unk44.x, work->unk44.y + 1.0f);
                    }
                }
                found = FALSE;
                for (i = 0; i < 40; i++) {
                    if (m229_itemHeldTbl[i] == 1) {
                        found = TRUE;
                    }
                }
                if (!found) {
                    m229_phaseDoneNo = 10;
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

                work = &m229_objWorkTbl[index];
                work->unk44.x += m229_itemScatterTbl[obj->work[0]][0];
                work->unk44.y += m229_itemScatterTbl[obj->work[0]][1];
                espPosSet(work->unk42, work->unk44.x, work->unk44.y);
                work->unk5C.x = work->unk5C.y = m229_zoomScale;
                espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
                espDispOn(work->unk42);
            }
            break;
        case 13:
            if (obj->work[1] < 4) {
                if (m229_viewOfsTbl[obj->work[1]][1] + 80.0f > work->unk44.y) {
                    espPriSet(work->unk42, 0xDDDD);
                    if (m229_roomItemTbl[m229_checkNo] == obj->work[0]) {
                        for (i = 0; i < 10; i++) {
                            if (work->unk44.x ==
                                    m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[obj->work[1]][0] &&
                                work->unk44.y ==
                                    m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[obj->work[1]][1]) {
                                m229_roomSpotItemTbl[i] = obj->work[0];
                                if (m229_roomItemTbl[i] == m229_roomSpotItemTbl[i]) {
                                    espPriSet(work->unk42, 0x1111);
                                    if (work->unk04 == 0) {
                                        m229_scoreTbl[obj->work[1]]++;
                                        work->unk04 = 1;
                                    }
                                    work->unk5C.x = work->unk5C.y = m229_checkScale;
                                    espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
                                }
                            }
                        }
                    }
                }
            }
            if (obj->work[1] == 4) {
                espPriSet(work->unk42, 0x3333);
                if (m229_roomItemTbl[m229_checkNo] == obj->work[0]) {
                    espPriSet(work->unk42, 0x1111);
                    work->unk5C.x = work->unk5C.y = m229_zoomScale;
                    espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
                }
            }
            break;
    }
}

void m229_ItemObjInit(omObjData *obj) {
    MessyMemoryWork *work = &m229_objWorkTbl[obj->work[0] + 8 + obj->work[1] * 10];
    s16 i;
    u8 slot;

    if (obj->work[1] == 0) {
        for (i = 0; i < 10; i++) {
            if (obj->work[0] == i) {
                m229_itemViewAnimTbl[i] = HuSprAnimDataRead((&m229_itemViewSprTbl[i])->fileId);
            }
        }
    }
    if (obj->work[1] < 4) {
        for (i = 0; i < 11; i++) {
            if (i == obj->work[0]) {
                work->unk42 = espEntry(m229_itemViewAnimTbl[i], 0, 0);
            }
        }
    } else {
        for (i = 0; i < 10; i++) {
            if (obj->work[0] == i) {
                work->unk40 = HuSprAnimDataRead((&m229_itemRoomSprTbl[i])->fileId);
                work->unk42 = espEntry(work->unk40, 0, 0);
            }
        }
    }
    if (obj->work[1] == 4) {
        slot = rand8() % 10;
        while (TRUE) {
            if (slot != m229_roomSlotTbl[0] && slot != m229_roomSlotTbl[1] &&
                slot != m229_roomSlotTbl[2] && slot != m229_roomSlotTbl[3] &&
                slot != m229_roomSlotTbl[4] && slot != m229_roomSlotTbl[5] &&
                slot != m229_roomSlotTbl[6] && slot != m229_roomSlotTbl[7] &&
                slot != m229_roomSlotTbl[8]) {
                m229_roomSlotTbl[obj->work[0]] = slot;
                break;
            }
            slot++;
            if (slot >= 10) {
                slot = 0;
            }
        }
        for (i = 0; i < 10; i++) {
            if (slot == i) {
                work->unk44.x = m229_roomSpotPosTbl[slot][0];
                work->unk44.y = m229_roomSpotPosTbl[slot][1];
                m229_roomItemTbl[slot] = obj->work[0];
            }
        }
    }
    work->unk5C.x = 1.0f;
    work->unk5C.y = 1.0f;
    espAttrSet(work->unk42, HUSPR_ATTR_BG | HUSPR_ATTR_XLU | HUSPR_ATTR_FILTER_BILERP);
    espPosSet(work->unk42, work->unk44.x, work->unk44.y);
    espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
    espPriSet(work->unk42, 0xDDDD);
    if (obj->work[1] == 4) {
        espPriSet(work->unk42, 0x3333);
    }
    obj->func = m229_ItemObjMain;
}

void m229_ItemObjCreateAll(void) {
    MessyMemoryWork *work;
    omObjData *obj;
    s16 i;
    s16 j;
    s16 k;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            work = &m229_objWorkTbl[j + 8 + i * 10];
            obj = omAddObj(0x12C, 0, 0, -1, m229_ItemObjInit);
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

void m229_ItemMarkObjMain(omObjData *obj) {
    MessyMemoryWork *work = &m229_objWorkTbl[obj->work[0] + 0x56 + obj->work[1] * 10];
    MessyMemoryWork *tile = &m229_objWorkTbl[obj->work[0] + 8 + obj->work[1] * 10];
    s16 i;

    switch (m229_phase) {
        case 3:
            if (obj->work[1] == 4) {
                for (i = 0; i < 21; i++) {
                    if (tile->unk44.x == m229_roomSpotPosTbl[i][0] + m229_viewOfsTbl[obj->work[1]][0] &&
                        tile->unk44.y == m229_roomSpotPosTbl[i][1] + m229_viewOfsTbl[obj->work[1]][1]) {
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
                espAttrReset(work->unk42, HUSPR_ATTR_BG);
            }
            break;
        case 5:
            if (obj->work[1] == 4) {
                for (i = 0; i < 20; i++) {
                    if (tile->unk44.x == m229_roomSpotPosTbl[i][0] && tile->unk44.y == m229_roomSpotPosTbl[i][1]) {
                        m229_itemScatterTbl[obj->work[0]][0] = m229_itemScatterVelTbl[i][0] * 2.0f;
                        m229_itemScatterTbl[obj->work[0]][1] = m229_itemScatterVelTbl[i][1] * 2.0f;
                    }
                }
                work->unk44.x += m229_itemScatterTbl[obj->work[0]][0];
                work->unk44.y += m229_itemScatterTbl[obj->work[0]][1];
                espPosSet(work->unk42, work->unk44.x, work->unk44.y + 2.0f);
                work->unk5C.x = work->unk5C.y = m229_zoomScale;
                espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
                if (work->unk5C.x <= 0.01 || work->unk5C.y <= 0.01) {
                    espDispOff(work->unk42);
                }
            }
            if (obj->work[1] < 4) {
                for (i = 0; i < 21; i++) {
                    if (tile->unk44.x == m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[obj->work[1]][0] &&
                        tile->unk44.y == m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[obj->work[1]][1]) {
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
                    if (tile->unk44.x == m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[obj->work[1]][0] &&
                        tile->unk44.y == m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[obj->work[1]][1]) {
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
                    if (tile->unk44.x == m229_viewSpotPosTbl[i][0] + m229_viewOfsTbl[obj->work[1]][0] &&
                        tile->unk44.y == m229_viewSpotPosTbl[i][1] + m229_viewOfsTbl[obj->work[1]][1]) {
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
                if (m229_itemHeldTbl[obj->work[1] * 10 + obj->work[0]] == 1) {
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

void m229_ItemMarkObjInit(omObjData *obj) {
    MessyMemoryWork *work = &m229_objWorkTbl[obj->work[0] + 0x56 + obj->work[1] * 10];
    MessyMemoryWork *tile = &m229_objWorkTbl[obj->work[0] + 8 + obj->work[1] * 10];
    s16 i;

    if (obj->work[0] == 0 && obj->work[1] == 0) {
        m229_itemMarkAnim = HuSprAnimDataRead(0x3E0003);
    }
    work->unk42 = espEntry(m229_itemMarkAnim, 0, 0);
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
            if (tile->unk44.x == m229_roomSpotPosTbl[i][0] + m229_viewOfsTbl[obj->work[1]][0] &&
                tile->unk44.y == m229_roomSpotPosTbl[i][1] + m229_viewOfsTbl[obj->work[1]][1]) {
                work->unk44.x = tile->unk44.x;
                work->unk44.y = tile->unk44.y;
                espPriSet(work->unk42, 0x4444);
                espDispOn(work->unk42);
                espPosSet(work->unk42, work->unk44.x, work->unk44.y + 2.0f);
            }
        }
    }
    espAttrSet(work->unk42, HUSPR_ATTR_BG | HUSPR_ATTR_XLU);
    espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
    obj->func = m229_ItemMarkObjMain;
}

void m229_ItemMarkObjCreateAll(void) {
    MessyMemoryWork *work;
    omObjData *obj;
    s16 i;
    s16 j;
    s16 k;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            work = &m229_objWorkTbl[j + 0x56 + i * 10];
            obj = omAddObj(0x190, 0, 0, -1, m229_ItemMarkObjInit);
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

void m229_MoverObjMain(omObjData *obj) {
    MessyMemoryWork *work = &m229_moverWorkTbl[obj->work[0]];
    omObjData *mainObj = m229_moverWorkTbl[0].obj;

    switch (m229_phase) {
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
                    obj->trans.z += m229_moverPathTbl[obj->work[0]][0];
                    obj->trans.x += m229_moverPathTbl[obj->work[0]][1];
                    if (obj->trans.z <= m229_moverPathTbl[obj->work[0]][2]) {
                        obj->work[1] = 1;
                        m229_messVibTimer = 1;
                        if (obj->work[0] == 4 || obj->work[0] == 6) {
                            Hu3DMotionModelSet(*obj->model, mainObj->motion[3]);
                        } else {
                            Hu3DMotionModelSet(*obj->model, mainObj->motion[4]);
                            if (Hu3DData[*obj->model].motTime == 0.0f) {
                                HuAudFXVolSet(HuAudFXPlay(0x3EE), 0x73);
                            }
                        }
                        Hu3DMotionAttrSet(*obj->model, 2, 2);
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
                    if (m229_phase == 2 && obj->work[0] == 2 && work->unk04 == 5) {
                        m229_dustState = 1;
                    }
                    if (m229_phase == 2 && obj->work[0] == 6 && work->unk04 == 10) {
                        m229_phaseDoneNo = 2;
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
                    obj->rot.y = m229_AngleAdd(obj->rot.y, 180.0f);
                    Hu3DMotionModelSet(*obj->model, mainObj->motion[2]);
                    Hu3DMotionAttrSet(*obj->model, 2, 2);
                    Hu3DMotionTimeSet(*obj->model, 0.0f);
                    if (obj->work[0] == 2) {
                        m229_dustState = 2;
                        HuAudFXVolSet(HuAudFXPlay(0x298), 0x73);
                    }
                    obj->work[1] = 3;
                    break;
                case 3:
                    obj->trans.z -= m229_moverPathTbl[obj->work[0]][0];
                    obj->trans.x -= m229_moverPathTbl[obj->work[0]][1];
                    if (obj->trans.z >= 170.0f) {
                        obj->work[1] = 4;
                        if (obj->work[0] == 3) {
                            m229_phaseDoneNo = 3;
                        }
                    }
                    if (obj->work[0] == 3 && obj->trans.z == -50.0f) {
                        HuAudFXVolSet(HuAudFXPlay(0x29B), 0x73);
                    }
                    break;
                case 4:
                    Hu3DModelAttrSet(*obj->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    break;
            }
            Hu3DModelPosSet(*obj->model, obj->trans.x, obj->trans.y, obj->trans.z);
            break;
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z + 0.0f);
}

void m229_MoverObjInit(omObjData *obj) {
    u32 index = obj->work[0];
    omObjData *mainObj = m229_moverWorkTbl[0].obj;
    u8 i;

    if (index == 0) {
        *obj->model = Hu3DModelRead(0xA0000, 0xB9);
        m229_moverMdl = *obj->model;
        omObjMotionRead(obj, 0, 0xA0001);
        omObjMotionRead(obj, 1, 0xA0002);
        omObjMotionRead(obj, 2, 0xA0006);
        omObjMotionRead(obj, 3, 0xA0007);
        omObjMotionRead(obj, 4, 0xA0009);
    } else {
        *obj->model = Hu3DModelLink(m229_moverMdl);
    }
    obj->model[1] = Hu3DModelRead2(0, 0xA9);
    Hu3DModelObjAttrSet(obj->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    HuTranslateF(Hu3DData[obj->model[1]].mtx, 0.0f, 15.0f, 0.0f);
    Hu3DMotionModelSet(*obj->model, mainObj->motion[2]);
    Hu3DMotionAttrSet(*obj->model, 2, 2);
    Hu3DMotionTimeSet(*obj->model, 0.0f);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    for (i = 0; i < 7; i++) {
        if (i == obj->work[0]) {
            obj->trans.z = i * 80 + 120.0f;
        }
    }
    obj->rot.x = 0.0f;
    obj->rot.y = m229_moverPathTbl[obj->work[0]][3];
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
    obj->func = m229_MoverObjMain;
}

void m229_MoverObjCreateAll(void) {
    MessyMemoryWork *work;
    omObjData *obj;
    s16 i;

    for (i = 0; i < 7; i++) {
        work = &m229_moverWorkTbl[i];
        obj = omAddObj(0x1F4, 1, 0xA, -1, m229_MoverObjInit);
        obj->work[0] = i;
        work->obj = obj;
    }
}

void m229_DustObjMain(omObjData *obj) {
    MessyMemoryWork *work = &m229_dustWork[obj->work[0]];

    switch (m229_phase) {
        case 2:
        case 3:
            if (m229_dustState == 1) {
                if (m229_dustSeF == 0) {
                    HuAudFXPlay(0x3E9);
                    m229_dustSeF = 1;
                    HuAudFXPlay(0x127);
                }
                Hu3DModelAttrSet(*obj->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelTPLvlSet(*obj->model, work->unk06);
                work->unk06 += 20;
                if (work->unk06 >= 255) {
                    work->unk06 = 255;
                }
            }
            if (m229_dustState == 2) {
                Hu3DModelTPLvlSet(*obj->model, work->unk06);
                work->unk06 -= 10;
                if (work->unk06 <= 0) {
                    work->unk06 = 0;
                    Hu3DModelAttrSet(*obj->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    m229_messVibTimer = 0;
                }
            }
            break;
    }
}

void m229_DustObjInit(omObjData *obj) {
    *obj->model = Hu3DModelRead(0x3E001C, 0xA9);
    Hu3DMotionAttrSet(*obj->model, 2, 2);
    Hu3DModelAttrSet(*obj->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelTPLvlInit(*obj->model);
    Hu3DModelTPLvlSet(*obj->model, 100);
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
    obj->func = m229_DustObjMain;
}

void m229_DustObjCreate(void) {
    omObjData *obj = omAddObj(0xFA, 1, 0xA, -1, m229_DustObjInit);
    obj->work[0] = 0;
    m229_dustWork[0].obj = obj;
}

void m229_ShutterObjMain(omObjData *obj) {
    MessyMemoryWork *work = &m229_shutterWorkTbl[obj->work[0]];

    switch (m229_phase) {
        case 9:
            switch (m229_shutterStateTbl[obj->work[0]]) {
                case 2:
                    if (Hu3DData[*obj->model].motTime == m229_shutterMotEnd) {
                        Hu3DMotionAttrSet(*obj->model, 4, 4);
                    }
                    if (Hu3DData[*obj->model].motTime == 0.0f) {
                        m229_shutterStateTbl[obj->work[0]] = 0;
                    }
                    break;
                case 1:
                    if (Hu3DData[*obj->model].motTime == 0.0f) {
                        Hu3DMotionModelSet(*obj->model, *obj->motion);
                        Hu3DMotionAttrSet(*obj->model, 2, 0);
                    }
                    break;
            }
            break;
        case 11:
            if (m229_shutterStateTbl[obj->work[0]] == 1 ||
                Hu3DData[*obj->model].motTime == m229_shutterMotEnd) {
                Hu3DMotionAttrSet(*obj->model, 4, 4);
                m229_shutterStateTbl[obj->work[0]] = 0;
            }
            if (obj->work[0] == 3) {
                work->unk04++;
                if (work->unk04 > 50) {
                    m229_phaseDoneNo = 11;
                    work->unk04 = 0;
                }
            }
            break;
    }
}

void m229_ShutterObjInit(omObjData *obj) {
    *obj->model = Hu3DModelRead(0x3E001A, 0xB9);
    omObjMotionRead(obj, 0, 0x3E001B);
    Hu3DMotionModelSet(*obj->model, *obj->motion);
    m229_shutterMotEnd = Hu3DMotion[Hu3DData[*obj->model].motId].unk02;
    Hu3DMotionAttrSet(*obj->model, 2, 1);
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
    obj->func = m229_ShutterObjMain;
}

void m229_ShutterObjCreateAll(void) {
    MessyMemoryWork *work;
    omObjData *obj;
    s16 i;

    for (i = 0; i < 4; i++) {
        work = &m229_shutterWorkTbl[i];
        obj = omAddObj(0x1D6, 1, 3, -1, m229_ShutterObjInit);
        obj->work[0] = i;
        work->obj = obj;
    }
}

void m229_ScoreObjMain(omObjData *obj) {
    MessyMemoryWork *work = &m229_objWorkTbl[obj->work[0] + 0x4A + obj->work[1] * 3];
    u8 i;

    switch (m229_phase) {
        case 13:
            if (obj->work[0] == 0 && obj->work[1] == 0 && work->unk06 == 0) {
                HuAudFXPlay(0x3EC);
                work->unk06 = 1;
            }
            break;
        case 14:
            work->unk5C.x = work->unk5C.y = m229_scoreScale;
            if (obj->work[0] == 1) {
                espDispOn(work->unk42);
                work->unk04++;
                if (work->unk04 >= 10) {
                    work->unk04 = 0;
                }
                espPatNoSet(work->unk42, work->unk04);
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
                if (m229_scoreTbl[obj->work[1]] == i) {
                    work = &m229_objWorkTbl[obj->work[1] * 3 + 0x4B];
                    espPatNoSet(work->unk42, i);
                }
            }
            if (m229_scoreTbl[obj->work[1]] == 10) {
                work = &m229_objWorkTbl[obj->work[1] * 3 + 0x4A];
                espDispOn(work->unk42);
                espPatNoSet(work->unk42, 1);
                work = &m229_objWorkTbl[obj->work[1] * 3 + 0x4B];
                espPatNoSet(work->unk42, 0);
            }
            work = &m229_objWorkTbl[obj->work[0] + 0x4A + obj->work[1] * 3];
            work->unk5C.x = work->unk5C.y = m229_scoreScale;
            if (work->unk5C.x < 0.01f || work->unk5C.y < 0.01f) {
                work->unk5C.x = work->unk5C.y = 0.01f;
                espDispOff(work->unk42);
                m229_phaseDoneNo = 15;
            }
            break;
    }
    espScaleSet(work->unk42, work->unk5C.x, work->unk5C.y);
    espPosSet(work->unk42, work->unk44.x, work->unk44.y);
}

void m229_ScoreObjInit(omObjData *obj) {
    MessyMemoryWork *work = &m229_objWorkTbl[obj->work[0] + 0x4A + obj->work[1] * 3];
    u8 i;

    switch (obj->work[0]) {
        case 0:
        case 1:
            work->unk40 = HuSprAnimDataRead(0x2E);
            work->unk42 = espEntry(work->unk40, 0, 0);
            espAttrSet(work->unk42, HUSPR_ATTR_XLU);
            espPriSet(work->unk42, 0);
            break;
        case 2:
            work->unk40 = HuSprAnimDataRead(0x3E0019);
            work->unk42 = espEntry(work->unk40, 0, 0);
            espAttrSet(work->unk42, HUSPR_ATTR_XLU);
            espPriSet(work->unk42, 0x500);
            break;
    }
    for (i = 0; i < 3; i++) {
        if (obj->work[0] == i) {
            work->unk44.x = m229_scorePosTbl[obj->work[1]][i * 2];
            work->unk44.y = m229_scorePosTbl[obj->work[1]][i * 2 + 1];
        }
    }
    espDispOff(work->unk42);
    obj->func = m229_ScoreObjMain;
}

void m229_ScoreObjCreateAll(void) {
    MessyMemoryWork *work;
    omObjData *obj;
    u8 i;
    u8 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            work = &m229_objWorkTbl[0x4A + i * 3 + j];
            obj = omAddObj(0x384, 1, 0xA, -1, m229_ScoreObjInit);
            obj->work[0] = j;
            obj->work[1] = i;
            work->obj = obj;
        }
    }
}

void m229_CameraViewInit(void) {
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

void m229_ExitObjMain(omObjData *obj) {
    osViBlack(FALSE);
    omOvlReturnEx(1);
}

void m229_ExitWaitObjMain(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = m229_ExitObjMain;
    }
}

void m229_ExitCheckObjMain(omObjData *obj) {
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        obj->func = m229_ExitWaitObjMain;
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
    }
}

void m229_MainObjMain(omObjData *obj) {
    u8 winners[4];
    u8 i;
    u8 j;

    switch (m229_phase) {
        case 0:
            if (m229_timer > 0) {
                m229_timer--;
            }
            if (m229_timer < 91) {
                GMesCreate(GMES_MES_TIMER, m229_timer / 30, 160, 28);
                m229_timer = 91;
                m229_PhaseSet(1);
            }
            break;
        case 1:
            if (m229_timer > 0) {
                m229_timer--;
                if (m229_timer == 88) {
                    HuAudFXPlay(8);
                }
                GMesTimerValueSet((m229_timer + 29) / 30);
            } else {
                GMesTimerEnd();
                m229_timer = 0;
                m229_PhaseSet(2);
            }
            break;
        case 2:
            if (m229_phaseDoneNo == 2) {
                for (i = 0; i < 10; i++) {
                    m229_roomSlotTbl[i] = 10;
                }
                m229_PhaseSet(3);
            }
            break;
        case 3:
            if (m229_phaseDoneNo == 3) {
                m229_PhaseSet(4);
            }
            break;
        case 4:
            if (m229_phaseDoneNo == 4) {
                m229_PhaseSet(5);
            }
            break;
        case 5:
            m229_zoomScale -= 0.02f;
            if (m229_phaseDoneNo == 5) {
                m229_PhaseSet(6);
            }
            break;
        case 6:
            if (m229_phaseDoneNo == 6) {
                m229_PhaseSet(8);
                m229_timer = 0;
            }
            break;
        case 7:
            m229_timer--;
            if (m229_timer <= 0) {
                m229_PhaseSet(8);
                m229_timer = 0;
            }
            break;
        case 8:
            if (m229_timer == 0) {
                GMesCreate(GMES_MES_3);
                m229_timer++;
            } else if (m229_timer >= 43) {
                HuAudSeqPlay(0x31);
            } else {
                m229_timer++;
            }
            if (GMesStatGet() == 0) {
                m229_PhaseSet(9);
                GMesCreate(GMES_MES_TIMER, 30, 160, 28);
                m229_timer = 901;
            }
            break;
        case 9:
            if (m229_timer > 0) {
                m229_timer--;
                GMesTimerValueSet((m229_timer + 29) / 30);
            } else {
                GMesTimerEnd();
                m229_PhaseSet(10);
                m229_zoomScale = 0.01f;
                GMesCreate(GMES_MES_14);
                HuAudSeqFadeOut(120);
            }
            break;
        case 10:
            if (m229_phaseDoneNo == 10 && GMesStatGet() == 0) {
                m229_PhaseSet(11);
            }
            break;
        case 11:
            if (m229_phaseDoneNo == 11) {
                m229_PhaseSet(12);
            }
            break;
        case 12:
            m229_zoomScale += 0.01f;
            if (m229_phaseDoneNo == 12) {
                m229_PhaseSet(13);
            }
            break;
        case 13:
            if (m229_checkPulseF == 0) {
                if (m229_checkScale == 1.0f) {
                    HuAudFXPlay(0x3EF);
                }
                m229_zoomScale += 0.1f;
                m229_checkScale += 0.05f;
                if (m229_checkScale >= 1.5f) {
                    m229_checkPulseF = 1;
                }
            }
            if (m229_checkPulseF == 1) {
                m229_zoomScale -= 0.1f;
                m229_checkScale -= 0.05f;
                if (m229_checkScale <= 1.0f) {
                    m229_checkScale = 1.0f;
                    m229_checkNo++;
                    m229_checkPulseF = 0;
                    if (m229_checkNo >= 10) {
                        for (i = 0; i < 4; i++) {
                            m229_rankTbl[i] = i;
                        }
                        for (i = 0; i < 4; i++) {
                            for (j = 0; j < 3; j++) {
                                if (m229_scoreTbl[m229_rankTbl[j]] <
                                    m229_scoreTbl[m229_rankTbl[j + 1]]) {
                                    m229_rankTbl[j] = m229_rankTbl[j] ^ m229_rankTbl[j + 1];
                                    m229_rankTbl[j + 1] = m229_rankTbl[j] ^ m229_rankTbl[j + 1];
                                    m229_rankTbl[j] = m229_rankTbl[j + 1] ^ m229_rankTbl[j];
                                }
                            }
                        }
                        for (i = 0; i < 3; i++) {
                            if (m229_scoreTbl[m229_rankTbl[0]] ==
                                m229_scoreTbl[m229_rankTbl[i + 1]]) {
                                m229_tieCnt++;
                            }
                        }
                        if (m229_scoreTbl[m229_rankTbl[0]] < 4) {
                            m229_tieCnt = 4;
                        }
                        m229_timer = 30;
                        m229_PhaseSet(14);
                    }
                }
            }
            break;
        case 14:
            m229_scoreScale += 0.05f;
            if (m229_scoreScale >= 1.0f) {
                m229_scoreScale = 1.0f;
            }
            if (m229_phaseDoneNo == 14) {
                m229_PhaseSet(15);
            }
            break;
        case 15:
            m229_timer--;
            if (m229_timer < 0) {
                m229_scoreScale -= 0.045f;
            }
            if (m229_phaseDoneNo == 15) {
                m229_PhaseSet(16);
                m229_timer = -15;
            }
            break;
        case 16:
            if (GMesStatGet() == 0 && m229_timer == 0) {
                m229_timer = 1;
                switch (m229_tieCnt) {
                    case 0:
                        winners[0] = GwPlayer[m229_rankTbl[0]].chr;
                        GwPlayer[m229_rankTbl[0]].bonusCoin = 10;
                        GMesCreate(GMES_MES_MG_WINNER, winners[0]);
                        HuAudSeqPlay(0x65);
                        break;
                    case 1:
                        for (i = 0; i < 2; i++) {
                            winners[i] = GwPlayer[m229_rankTbl[i]].chr;
                            GwPlayer[m229_rankTbl[i]].bonusCoin = 10;
                        }
                        GMesCreate(GMES_MES_MG_WINNERS_2, winners[0], winners[1]);
                        HuAudSeqPlay(0x66);
                        break;
                    case 2:
                        for (i = 0; i < 3; i++) {
                            winners[i] = GwPlayer[m229_rankTbl[i]].chr;
                            GwPlayer[m229_rankTbl[i]].bonusCoin = 10;
                        }
                        GMesCreate(GMES_MES_MG_WINNERS_3, winners[0], winners[1], winners[2]);
                        HuAudSeqPlay(0x66);
                        break;
                    case 3:
                        for (i = 0; i < 4; i++) {
                            winners[i] = GwPlayer[m229_rankTbl[i]].chr;
                            GwPlayer[m229_rankTbl[i]].bonusCoin = 10;
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
            if (m229_timer > 0) {
                if (GMesStatGet() == 0) {
                    m229_PhaseSet(17);
                    m229_timer = 15;
                }
            } else if (m229_timer < 0) {
                m229_timer++;
            }
            break;
        case 17:
            if (m229_timer > 0) {
                m229_timer--;
            } else {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                obj->func = m229_ExitWaitObjMain;
            }
            break;
    }
    if (m229_messVibTimer > 0) {
        if (m229_messVibTimer % 5 == 1) {
            for (i = 0; i < 4; i++) {
                if (!(GwPlayer[i].stat & PLAYER_IS_CPU)) {
                    omVibrate(i, 2, 3, 10);
                }
            }
        }
        m229_messVibTimer++;
    }
    if (m229_messVibTimer > 30000) {
        m229_messVibTimer = 1;
    }
}

void m229_MainObjInit(omObjData *obj) {
    u8 i;
    u8 j;

    m229_timer = 0x67;
    m229_phase = 0;
    m229_phaseDoneNo = 50;
    m229_itemPlaceCnt = 0;
    m229_zoomScale = 1.0f;
    m229_checkScale = 1.0f;
    m229_checkPulseF = 0;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 2; j++) {
            m229_itemScatterTbl[i][j] = 0.0f;
        }
    }
    for (i = 0; i < 10; i++) {
        m229_roomItemTbl[i] = 10;
    }
    for (i = 0; i < 20; i++) {
        m229_roomSpotItemTbl[i] = 10;
    }
    for (i = 0; i < 4; i++) {
        m229_scoreTbl[i] = 0;
    }
    for (i = 0; i < 10; i++) {
        m229_roomSlotTbl[i] = 10;
    }
    for (i = 0; i < 4; i++) {
        m229_handGrabTbl[i] = 0;
    }
    for (i = 0; i < 40; i++) {
        m229_itemHeldTbl[i] = 0;
    }
    m229_checkNo = 0;
    for (i = 0; i < 4; i++) {
        m229_shutterStateTbl[i] = 0;
    }
    m229_shutterMotEnd = 0.0f;
    for (i = 0; i < 4; i++) {
        m229_rankTbl[i] = 0;
    }
    m229_tieCnt = 0;
    m229_dustState = 0;
    m229_itemPlaceNum = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            m229_comKnownTbl[i][j] = 0;
        }
    }
    m229_scoreScale = 0.1f;
    for (i = 0; i < 10; i++) {
        m229_itemViewAnimTbl[i] = 0;
    }
    m229_itemMarkAnim = 0;
    m229_moverMdl = 0;
    for (i = 0; i < 4; i++) {
        m229_walkSeTbl[i] = -1;
    }
    m229_dustSeF = 0;
    m229_messVibTimer = 0;
    m229_CameraViewInit();
    m229_CoverObjCreateAll();
    m229_DividerCreate();
    m229_HandObjCreateAll();
    m229_ItemObjCreateAll();
    m229_MoverObjCreateAll();
    m229_ShutterObjCreateAll();
    m229_DustObjCreate();
    m229_PlayerObjCreateAll();
    m229_ScoreObjCreateAll();
    m229_ItemMarkObjCreateAll();
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    obj->func = m229_MainObjMain;
}

void m229_Dummy(void) {
}

void m229_CameraInit(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 2;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(2);
    CamSetupMapCullAddMulti(2);
    for (i = 0; i < 2; i++) {
        ScissorSet(i, m229_cameraViewTbl[i].scissorX, m229_cameraViewTbl[i].scissorY,
                   m229_cameraViewTbl[i].scissorWidth, m229_cameraViewTbl[i].scissorHeight);
        ViewportSet(i, m229_cameraViewTbl[i].viewportScale.x, m229_cameraViewTbl[i].viewportScale.y,
                    m229_cameraViewTbl[i].viewportScale.z, m229_cameraViewTbl[i].viewportTranslate.x,
                    m229_cameraViewTbl[i].viewportTranslate.y, m229_cameraViewTbl[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, m229_cameraViewTbl[i].fov, 80.0f, 8000.0f);
    }
}

void m229_ObjectSetup(void) {
    MapCollInit(50);
    Hu3DSprModelInit(32);
    omInitObjMan(150, 0);
    omGameSysInit();
    Hu3DGLightColorSet(0, 64, 64, 96);
    Hu3DGLightColorSet(1, 64, 64, 64);
    Hu3DGLightDirSet(1, 0.0f, 85.0f, 100.0f);
    m229_CameraInit();
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    GMesFontMesCreate(m229_fontMesTbl, 0);
    GMesFontMesCreate(m229_fontMesTbl, 1);
    omAddObj(1000, 0, 0, -1, m229_MainObjInit);
    omAddObj(1000, 0, 0, -1, m229_ExitCheckObjMain);
    m229_ObjWorkInit();
}

const s16 m229_fontMesTbl[] = { 0x8260, 0x8261, 0x8262, 0 };
