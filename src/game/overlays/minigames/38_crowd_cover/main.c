#include "common.h"
#include "macros.h"
#include "game/overlays/minigame.h"
#include "game/hmfmath.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"
#include "game/texload.h"

#define PLAYER_WORK(obj) ((CrowdCoverPlayerWork *)((MgPlayerWork *)(obj)->data)->unk158)

#define CROWD_CC_PRIM_DECALA 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0
#define CROWD_CC_PRIM_MODULATEA 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0
#define CROWD_CC_BLEND_DECALA 1, PRIMITIVE, TEXEL0, PRIMITIVE, 0, 0, 0, TEXEL0
#define CROWD_CC_BLEND_MODULATEA 1, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0
#define CROWD_CC_MODULATEI_PRIMA TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0
#define CROWD_CC_MODULATEI_PASSA2 COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED

typedef struct CrowdCoverBillboard {
    /* 0x00 */ Gfx *displayList;
    /* 0x04 */ Vtx_t *vtx;
    /* 0x08 */ HuSprAnimData *sprite;
    /* 0x0C */ struct CrowdCoverBillboard *prev;
    /* 0x10 */ struct CrowdCoverBillboard *next;
    /* 0x14 */ void (*callback)(struct CrowdCoverBillboard *);
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
} CrowdCoverBillboard; // sizeof 0x68

typedef struct {
    /* 0x00 */ s16 unk00[9];
} CrowdCoverComCandidates; // sizeof 0x12

// Per-player work allocated in m256_PlayerCreate, stored at ObjData->unk158
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
} CrowdCoverPlayerWork; // sizeof 0x54

typedef struct {
    u8 values[8];
} CrowdCoverCharMotions;

// Crowd member state, updated by m256_CrowdObjMain
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

extern s32 omCharModelNoTbl[][6];
extern HuSprAnimData *HuSprAnimTbl[];
extern u8 storySceneNo;

s16 m256_timer = 2700;
s16 m256_choicePosTbl[3][2] = {
    { 116, 202 },
    { 160, 202 },
    { 202, 202 }
};
s32 m256_phaseTimer = 0;
s32 m256_winner = -1;
s32 m256_missChoiceNo = 0;
s16 m256_unusedNoTbl[4] = { 0, 1, 2, 3 }; /* Unreferenced. */
u8 m256_playerInitNo = 0;
u8 m256_playerInitNoPad[4] = { 0 }; /* Unreferenced. */
s16 m256_playerPosTbl[4][3] = {
    { -160, 10, 60 },
    { 160, 10, 60 },
    { 85, -75, -200 },
    { 85, 75, -200 }
};
f32 m256_playerRotTbl[4] = { 180.0f, 180.0f, -45.0f, -135.0f };
s16 m256_crowdWalkPatTbl[9][13] = {
    { 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 5, 4, -1 },
    { 10, 9, 8, 7, 8, 9, 10, 11, 12, 13, 12, 11, -1 },
    { 17, 16, 15, 14, 15, 16, 17, 18, 19, 20, 19, 18, -1 },
    { 24, 23, 22, 21, 22, 23, 24, 25, 26, 27, 26, 25, -1 },
    { 31, 30, 29, 28, 29, 30, 31, 32, 33, 34, 33, 32, -1 },
    { 38, 37, 36, 35, 36, 37, 38, 39, 40, 41, 40, 39, -1 },
    { 45, 44, 43, 42, 43, 44, 45, 46, 47, 48, 47, 46, -1 },
    { 52, 51, 50, 49, 50, 51, 52, 53, 54, 55, 54, 53, -1 },
    { 56, 57, 58, 59, 60, 61, 62, 63, -1, -1, -1, -1, -1 }
};
u32 m256_randSeed = 0x41C64E6D;
s32 m256_sizShiftTbl[] = { 4, 3, 2, 1 };
s16 m256_tmemRowAltTbl[] = {
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
s16 m256_tmemRowTbl[] = {
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
s16 m256_colorDitherTbl[] = { G_CD_DISABLE, G_CD_NOISE, G_CD_BAYER, G_CD_MAGICSQ };
s16 m256_texFilterTbl[] = { G_TF_POINT, G_TF_POINT, G_TF_BILERP, G_TF_AVERAGE };
s16 m256_alphaCompareTbl[] = { G_AC_THRESHOLD, G_AC_NONE, G_AC_DITHER, G_AC_NONE };
s32 m256_billboardBufNo = 0;

s16 m256_pictureTPLvl BSS;
s16 m256_musicTimer BSS;
u8 m256_musicTimerPad[4] BSS; /* Unreferenced. */
s16 m256_sprAnimTbl[16] BSS;
s16 m256_sprGrpTbl[8] BSS;
s16 m256_effSprUsedTbl[16] BSS;
s16 m256_phase BSS;
u8 m256_phasePad[4] BSS; /* Unreferenced. */
CrowdCoverMember m256_crowdTbl[32] BSS;
s16 m256_stageNo BSS;
s16 m256_answerNo BSS;
s16 m256_crowdSprAnim BSS;
s16 m256_crowdNum BSS;
f32 m256_viewMtx[4][4] BSS;
f32 m256_viewInvMtx[4][4] BSS;
f32 m256_fovTan BSS;
CrowdCoverBillboard *m256_billboardTbl BSS;
void *m256_billboardBufTbl[3] BSS;
void *m256_billboardBufCur BSS;
s32 m256_billboardBufSize BSS;
s32 m256_billboardNum BSS;
u8 m256_billboardNumPad[0x10] BSS;      /* Unreferenced. */
CrowdCoverBillboard m256_billboardOpaHead BSS; // List head of opaque entries
CrowdCoverBillboard m256_billboardXluHead BSS; // List head of translucent entries

extern const CrowdCoverComCandidates m256_comCandidateTbl;

void m256_CameraViewInit(omObjData *object);
void m256_MtxInvert(HuMtx4F src, HuMtx4F dst);
void m256_StageObjCreate(void);
void m256_StageObjInit(omObjData *object);
void m256_StageObjMain(omObjData *object);
void m256_PlayerObjCreateAll(void);
void m256_PlayerObjInit(omObjData *object);
void m256_PlayerCreate(omObjData *object, s32 arg1, s32 arg2, u16 player, u16 tag);
void m256_PlayerObjMain(omObjData *object);
u16 m256_PlayerComInput(omObjData *arg0);
void m256_CrowdObjCreate(void);
void m256_CrowdObjInit(omObjData *);
void m256_CrowdObjMain(omObjData *object);
s32 m256_Rand16Get(void);
s16 m256_AnimDataRead(s32 dataNum);
s16 m256_SprGrpCreate(s16 spriteId, s16 count);
void m256_DirRotCalc(Vec *dir, f32 *rot);
void m256_HookPosGet(s16 model, char *hook, s16 time, Vec *pos);
void m256_BillboardInit(u16 count);
s16 m256_BillboardGfxBuild(CrowdCoverBillboard *crowd);
s16 m256_BillboardCreate(s16 spriteId, s32 flags);
void m256_BillboardCenterSet(s16 index, f32 y, f32 z, f32 unk_3C);
void m256_BillboardPosSet(s16 index, f32 x, f32 y, f32 z);
void m256_BillboardScaleSet(s16 index, f32 x, f32 y, f32 z);
void m256_BillboardPatSet(s16 index, s16 value);
void m256_BillboardAttrSet(s16 index, s32 value);
void m256_BillboardColorSet(s16 index, s8 value1, s8 value2, s8 value3, s16 value4);
f32 m256_AngleCalc(f32 y, f32 x);
f32 m256_DistCalc(Vec *arg0, Vec *arg1);
void m256_BillboardKill(s16 index);
void m256_BillboardBufAlloc(void);
void m256_BillboardSort(HuCamera *camera, HuMtx4F lookAt);
Gfx *m256_BillboardEntryDraw(Gfx *gfx, CrowdCoverBillboard *crowd, HuMtx4F lookAt, Vec *rot);
void m256_BillboardDraw(Gfx **gfxP, s32 arg1, s32 arg2);
void m256_BillboardAnimUpdate(void);
void m256_BillboardClose(void);

void m256_ObjectSetup(void) {
    omObjData *obj;
    u8 camIndex;
    s32 count;

    MapCollInit(1);
    Hu3DQuadPoolInit(&mgQuadPool, 0x40);
    omInitObjMan(0x10, 0);
    omGameSysInit();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 45.0f, 80.0f, 8000.0f);
    MgFieldStatClear();
    m256_CameraViewInit(obj);
    m256_StageObjCreate();
    m256_BillboardInit(0x80);
    m256_PlayerObjCreateAll();
    m256_CrowdObjCreate();
    count = (f32)m256_Rand16Get() * 1.52587890625e-05 * 16.0;
    while (--count != 0) {
        m256_Rand16Get();
    }
    Hu3DBGColorSet(180, 180, 180);
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
}

void m256_CameraViewInit(omObjData *object) {
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
    m256_fovTan = sinFov / cosFov;
    guMtxL2F(m256_viewMtx, &camera->mtxs[0].lookAtMtx);
    guMtxL2F(m256_viewInvMtx, &camera->mtxs[0].lookAtMtx);
    m256_MtxInvert(m256_viewInvMtx, m256_viewInvMtx);
}

void m256_MtxVecMul(HuMtx4F mtx, f32 x, f32 y, f32 z, f32 *dst) {
    dst[0] = ((x * mtx[0][0]) + (y * mtx[1][0])) + (z * mtx[2][0]);
    dst[1] = ((x * mtx[0][1]) + (y * mtx[1][1])) + (z * mtx[2][1]);
    dst[2] = ((x * mtx[0][2]) + (y * mtx[1][2])) + (z * mtx[2][2]);
}

void m256_MtxInvert(HuMtx4F src, HuMtx4F dst) {
    f32 mtx[4][4];
    f32 t0;
    f32 t1;
    f32 t2;
    f32 det;
    f32 *dstRow3;

    mtxCopy(mtx, src);

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

        m256_MtxVecMul(dst, -mtx[3][0], -mtx[3][1], -mtx[3][2], dstRow3);
    }
}

void m256_ScreenPosCalc(f32 *pos, f32 *dst) {
    f32 mtx[4][4];
    f32 depth;
    f32 scale;

    guTranslateF(mtx, pos[0], pos[1], pos[2]);
    guMtxCatF(mtx, m256_viewMtx, mtx);
    depth = mtx[3][2] * m256_fovTan;
    scale = fabsf(depth);
    if (scale != 0.0) {
        dst[0] = mtx[3][0] * 160.0f / scale / 1.3333333333333333;
        dst[1] = -mtx[3][1] * 120.0f / scale;
    }
    dst[0] += 160.0;
    dst[1] += 120.0;
    dst[2] = scale;
}

void m256_WorldPosCalc(f32 x, f32 y, f32 z, f32 *dst) {
    f32 depth = z + m256_viewMtx[3][2];
    f32 scale = fabsf(depth * m256_fovTan);
    f32 mtx[4][4];

    x -= 160.0;
    y -= 120.0;
    guTranslateF(mtx, (x + x) * scale * 1.3333333333333333 / 320.0, -((y + y) * scale / 240.0f), depth);
    guMtxCatF(mtx, m256_viewInvMtx, mtx);
    dst[0] = mtx[3][0];
    dst[1] = mtx[3][1];
    dst[2] = mtx[3][2];
}

void m256_StageObjCreate(void) {
    mgMapObjNum = 0;
    MgMapBaseSet(0);
    m256_stageNo = storySceneNo;
    mgMapObjTbl[mgMapObjNum++] = omAddObj(5, 1, 0, -1, m256_StageObjInit);
    m256_phase = 0;
}

void m256_StageObjInit(omObjData *object) {
    u16 sp10[3] = { 4, 5, 6 };
    u16 sp18[3] = { 7, 8, 9 };
    s16 orders[6][3] = { { 0, 1, 2 }, { 0, 2, 1 }, { 1, 0, 2 }, { 1, 2, 0 }, { 2, 1, 0 }, { 2, 0, 1 } };
    s16 unused[16]; // Unreferenced, but present in the stack frame.
    s16 order;
    s32 i;

    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    m256_sprAnimTbl[0] = m256_AnimDataRead(0x590000);
    m256_sprGrpTbl[0] = m256_SprGrpCreate(m256_sprAnimTbl[0], 1);
    HuSprPosSet(m256_sprGrpTbl[0], 0, 160, 120);
    HuSprAttrSet(m256_sprGrpTbl[0], 0, 0x4000);
    m256_sprAnimTbl[3] = m256_AnimDataRead(0x59000A);
    m256_sprGrpTbl[4] = m256_SprGrpCreate(m256_sprAnimTbl[3], 1);
    HuSprPosSet(m256_sprGrpTbl[4], 0, 160, 198);
    HuSprAttrSet(m256_sprGrpTbl[4], 0, 0x100C);
    m256_sprAnimTbl[2] = m256_AnimDataRead(sp18[m256_stageNo] | 0x590000);
    m256_sprGrpTbl[2] = m256_SprGrpCreate(m256_sprAnimTbl[2], 3);
    order = (f32)m256_Rand16Get() * 1.52587890625e-05 * 6.0;
    for (i = 0; i < 3; i++) {
        HuSprPosSet(m256_sprGrpTbl[2], i, m256_choicePosTbl[i][0], m256_choicePosTbl[i][1]);
        HuSprAttrSet(m256_sprGrpTbl[2], i, 0x1008);
        HuSprPatNoSet(m256_sprGrpTbl[2], i, orders[order][i]);
    }
    m256_sprAnimTbl[1] = m256_AnimDataRead(sp10[m256_stageNo] | 0x590000);
    m256_sprGrpTbl[1] = m256_SprGrpCreate(m256_sprAnimTbl[1], 1);
    HuSprPosSet(m256_sprGrpTbl[1], 0, 160, 110);
    m256_answerNo = (f32)m256_Rand16Get() * 1.52587890625e-05 * 3.0;
    HuSprPatNoSet(m256_sprGrpTbl[1], 0, orders[order][m256_answerNo]);
    HuSprAttrSet(m256_sprGrpTbl[1], 0, 0x405808);
    m256_sprAnimTbl[4] = m256_AnimDataRead(0x59000B);
    m256_sprGrpTbl[5] = m256_SprGrpCreate(m256_sprAnimTbl[4], 1);
    HuSprPosSet(m256_sprGrpTbl[5], 0, 160, 110);
    HuSprScaleSet(m256_sprGrpTbl[5], 0, 1.2f, 1.2f);
    HuSprAttrSet(m256_sprGrpTbl[5], 0, 0x940C);
    object->func = m256_StageObjMain;
}

void m256_StageObjMain(omObjData *object) {
    s16 sounds[3] = { 0x4B8, 0x4B9, 0x4BA };

    if (Hu3DPauseF) {
        HuSprAttrSet(m256_sprGrpTbl[1], 0, 0x8000);
        return;
    }
    HuSprAttrReset(m256_sprGrpTbl[1], 0, 0x8000);
    switch (m256_phase) {
        case 0:
            Hu3DHookFuncCreate(0xC0, m256_BillboardDraw, 2);
            m256_pictureTPLvl = 0;
            HuSprTPLvlSet(m256_sprGrpTbl[1], 0, 0);
            GMesCreate(6);
            m256_timer = 900;
            m256_phase++;
            HuAudFXPlay(sounds[m256_stageNo]);
            m256_musicTimer = 45;
        case 1:
            if (--m256_musicTimer == 0) {
                HuAudSeqPlay(0x31);
            }
            if (GMesStatGet() == 0) {
                m256_phase++;
                GMesCreate(0x1A, (m256_timer + 29) / 30, 0xA0, 0x20);
                HuAudFXPlay(0xE);
            }
            break;
        case 2:
            if (m256_pictureTPLvl < 0x100) {
                m256_pictureTPLvl += 8;
                HuSprTPLvlSet(m256_sprGrpTbl[1], 0, m256_pictureTPLvl);
            } else {
                HuSprTPLvlSet(m256_sprGrpTbl[1], 0, 0x100);
            }
            m256_timer--;
            GMesTimerValueSet((m256_timer + 29) / 30);
            if (m256_timer == 0) {
                m256_phase = 3;
            }
            if (PLAYER_WORK(mgPlayerObjTbl[0])->unk32 | PLAYER_WORK(mgPlayerObjTbl[1])->unk32) {
                m256_phase = 3;
                if (PLAYER_WORK(mgPlayerObjTbl[0])->unk32 != 0 &&
                    PLAYER_WORK(mgPlayerObjTbl[1])->unk32 != 0) {
                    PLAYER_WORK(mgPlayerObjTbl[m256_Rand16Get() & 1])->unk32 = 0;
                }
            }
            break;
        case 3:
            if (PLAYER_WORK(mgPlayerObjTbl[0])->unk32 != 0) {
                if (PLAYER_WORK(mgPlayerObjTbl[0])->unk32 == m256_answerNo + 1) {
                    m256_winner = 0;
                    PLAYER_WORK(mgPlayerObjTbl[0])->unk2C = 1;
                    PLAYER_WORK(mgPlayerObjTbl[1])->unk2C = 0;
                } else {
                    m256_winner = 1;
                    m256_missChoiceNo = PLAYER_WORK(mgPlayerObjTbl[0])->unk32;
                    PLAYER_WORK(mgPlayerObjTbl[0])->unk2C = 0;
                    PLAYER_WORK(mgPlayerObjTbl[1])->unk2C = 1;
                }
                m256_phaseTimer = 36;
            } else if (PLAYER_WORK(mgPlayerObjTbl[1])->unk32 != 0) {
                if (PLAYER_WORK(mgPlayerObjTbl[1])->unk32 == m256_answerNo + 1) {
                    m256_winner = 1;
                    PLAYER_WORK(mgPlayerObjTbl[0])->unk2C = 0;
                    PLAYER_WORK(mgPlayerObjTbl[1])->unk2C = 1;
                } else {
                    m256_winner = 0;
                    m256_missChoiceNo = PLAYER_WORK(mgPlayerObjTbl[1])->unk32;
                    PLAYER_WORK(mgPlayerObjTbl[0])->unk2C = 1;
                    PLAYER_WORK(mgPlayerObjTbl[1])->unk2C = 0;
                }
            } else {
                m256_winner = -1;
            }
            m256_phaseTimer = 15;
            GMesTimerEnd();
            GMesCreate(0x11);
            HuAudSeqFadeOut(0x78);
            m256_phase++;
            break;
        case 4:
            if (m256_pictureTPLvl < 0x100) {
                m256_pictureTPLvl += 8;
                HuSprTPLvlSet(m256_sprGrpTbl[1], 0, m256_pictureTPLvl);
            } else {
                HuSprTPLvlSet(m256_sprGrpTbl[1], 0, 0x100);
            }
            m256_timer -= 10;
            if (m256_timer > 0) {
                break;
            }
            m256_timer = 0;
            if (GMesStatGet() != 0) {
                break;
            }
            if (m256_phaseTimer == 15) {
                HuSprAttrReset(m256_sprGrpTbl[5], 0, 0x8000);
                if (m256_missChoiceNo == 0) {
                    HuAudFXPlay(m256_winner == -1 ? 0x4B6 : 0x4B5);
                    HuSprPosSet(m256_sprGrpTbl[5], 0, m256_choicePosTbl[m256_answerNo][0],
                                m256_choicePosTbl[m256_answerNo][1]);
                } else {
                    HuAudFXPlay(0x4B6);
                    HuSprPatNoSet(m256_sprGrpTbl[5], 0, 1);
                    HuSprPosSet(m256_sprGrpTbl[5], 0, m256_choicePosTbl[m256_missChoiceNo - 1][0],
                                m256_choicePosTbl[m256_missChoiceNo - 1][1]);
                }
            }
            if (--m256_phaseTimer == 0) {
                if (m256_winner == -1) {
                    GMesCreate(0x20);
                    HuAudSeqPlay(0x6C);
                } else {
                    GMesCreate(0x16, PLAYER_WORK(mgPlayerObjTbl[m256_winner])->unk29);
                    HuAudSeqPlay(0x67);
                }
                m256_phaseTimer = 15;
                m256_phase++;
            }
            break;
        case 5:
            if (GMesStatGet() != 0) {
                break;
            }
            if (--m256_phaseTimer == 0) {
                m256_phase++;
            }
            break;
        case 6:
            if (m256_phaseTimer != 0) {
                if (--m256_phaseTimer == 0) {
                    m256_phase++;
                }
            } else {
                m256_phaseTimer = 16;
                WipeCreateOut(WIPE_TYPE_NORMAL, m256_phaseTimer);
                HuAudSeqFadeOut(m256_phaseTimer);
                HuAudFXAllFadeOut((s16)m256_phaseTimer);
            }
            break;
        case 7:
            HuAudSeqStop();
            omOvlReturnEx(1);
            m256_BillboardClose();
            break;
    }
    if (omSysExitReq == 1 && WipeStatGet() == 0) {
        m256_phaseTimer = 0;
        m256_phase = 6;
    }
}

void m256_PlayerObjCreateAll(void) {
    s32 i;

    MgPlayerParamReset();
    mgPlayerObjNum = 0;
    for (i = 0; i < 2; i++) {
        mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(2, 0xB, 0x32, -1, m256_PlayerObjInit);
    }
}

const CrowdCoverCharMotions m256_chrAnimNoTbl = { { 0, 1, 2, 3, 4, 5, 6, 7 } };

void m256_PlayerObjInit(omObjData *object) {
    CrowdCoverCharMotions motions = m256_chrAnimNoTbl;
    s32 anims[3][8] = {
        { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C },
        { 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0x1D },
        { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B },
    };
    s16 itemModels[3] = { 14, 13, 12 };
    s32 unused[4]; // Unreferenced, but present in the stack frame.
    MgPlayerWork *data;
    CrowdCoverPlayerWork *work;
    s32 i;
    u8 player;
    s8 character;
    s32 model;
    s32 linkModel;
    u16 tag;
    s32 slot;

    for (i = 0; i < 4; i++) {
        if (m256_playerInitNo == GwPlayer[i].group) {
            break;
        }
    }
    player = i;
    character = GwPlayer[player].chr;
    model = omCharModelNoTbl[character][0];
    linkModel = omCharModelNoTbl[character][2];
    MgShadowAltSet(1);
    m256_PlayerCreate(object, model, linkModel, player, 0x2C9);
    data = object->data;
    object->trans.x = m256_playerPosTbl[m256_playerInitNo][0];
    object->trans.y = m256_playerPosTbl[m256_playerInitNo][1];
    object->trans.z = m256_playerPosTbl[m256_playerInitNo][2];
    data->unk3C = m256_playerRotTbl[m256_playerInitNo];
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
    work->unk2A = m256_playerInitNo;
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
    work->unk31 = CharAnimCreate(object->model[0], 2, motions.values[character], model | anims[2][character]);
    work->unk2F = Hu3DAnimDataRead(model | anims[0][character]);
    work->unk30 = Hu3DAnimDataRead(model | anims[1][character]);
    Hu3DModelDynamicFree(object->model[0]);
    tag = 0x2BD;
    for (i = 0; i < 3; i++) {
        slot = i + 2;
        object->model[slot] = Hu3DModelRead(itemModels[i] | 0x590000, tag);
        Hu3DModelHookSet(object->model[slot], object->model[0], "item_hook");
        Hu3DModelAttrSet(object->model[slot], 0x4000, 0x4000);
    }
    Hu3DModelAttrSet(object->model[2], 4, 0);
    object->model[9] = Hu3DModelRead2(7, 0x2DD);
    object->func = m256_PlayerObjMain;
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(character, 0), 1, 0);
    MgPlayerMotLoad(object, 0x26, CharMotionDataNumGet(character, 0x66), 1, 0);
    MgPlayerMotLoad(object, 0x27, CharMotionDataNumGet(character, 0x67), 1, 0x3C);
    MgPlayerMotLoad(object, 0xD, CharMotionDataNumGet(character, 0x2F), 2, 0x78);
    MgPlayerMotLoad(object, 0xE, CharMotionDataNumGet(character, 0x36), 2, 0x78);
    MgPlayerMotSet(object, 0x26);
    m256_playerInitNo++;
}

void m256_PlayerCreate(omObjData *object, s32 arg1, s32 arg2, u16 player, u16 tag) {
    MgPlayerWork *data;
    s32 i;
    u32 character;
    f32 zero;
    MgMotAttr *entry;

    for (i = 0; i < object->mdlcnt; i++) {
        object->model[i] = 0;
    }
    object->data = HuMemAllocTag(sizeof(MgPlayerWork), TAG_OVERLAY);
    memset(object->data, 0, sizeof(MgPlayerWork));
    data = object->data;
    data->unkE8 = HuMemAllocTag(object->mtncnt * 3 * sizeof(s32), TAG_OVERLAY);
    memset(data->unkE8, 0, object->mtncnt * 3 * sizeof(s32));
    data->unk158 = HuMemAllocTag(sizeof(CrowdCoverPlayerWork), TAG_OVERLAY);
    memset(data->unk158, 0, sizeof(CrowdCoverPlayerWork));

    object->model[0] = Hu3DModelRead(arg1 | arg2, tag);
    object->model[1] = Hu3DModelRead3(9, tag);
    MgShadowMdlInit(object->model[1]);
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
    MgPlayerRadiusSet(object, 60.0f);
    MgPlayerHeightSet(object, 150.0f);
    MgPlayerPunchRadiusSet(object, 20.0f);
    MgPlayerVelYSet(object, 1000.0f);

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

void m256_PlayerObjMain(omObjData *object) {
    CrowdCoverCharMotions motions = m256_chrAnimNoTbl;
    s16 cpuDelays[4] = { 450, 240, 150, 90 };
    s16 unusedDelays[4] = { 180, 150, 90, 60 }; // Initialized but never read.
    u16 buttons[3] = { 0x8000, 0x4000, 0x2000 };
    s32 unused[4]; // Unreferenced, but present in the stack frame.
    Vec pos;
    MgPlayerWork *data;
    CrowdCoverPlayerWork *work;
    u8 pad;
    f32 rot;
    u16 input;
    s32 model;
    HuMtx4F *mtx;

    data = object->data;
    work = data->unk158;
    pad = data->unk57;
    rot = data->unk3C;
    MgPlayerMotStatGet(object);
    switch (m256_phase) {
        case 0:
            if (!work->unk2D) {
                break;
            }
            work->unk34 = cpuDelays[work->unk2B] +
                          (s32)((f32)m256_Rand16Get() * 1.52587890625e-05 * cpuDelays[work->unk2B]);
            if ((s32)((f32)m256_Rand16Get() * 1.52587890625e-05 * 100.0) < (work->unk2B + 1) * 20) {
                work->unk36 = buttons[m256_answerNo];
            } else {
                work->unk36 = buttons[(s32)((f32)m256_Rand16Get() * 1.52587890625e-05 * 3.0)];
            }
            break;
        case 2:
            if (!work->unk2D) {
                input = HuPadBtnDown[(s8)pad];
            } else {
                input = m256_PlayerComInput(object);
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
                Hu3DModelAttrSet(object->model[2], 4, 4);
                Hu3DModelAttrSet(object->model[work->unk32 + 1], 4, 0);
            } else {
                MgPlayerMotSet(object, 0);
                model = object->model[9];
                m256_HookPosGet(object->model[0], "item_hook", Hu3DData[object->model[0]].motTime, &pos);
                Hu3DModelAttrSet(model, 4, 0);
                Hu3DModelPosSet(model, pos.x, pos.y, pos.z + 10.0);
                Hu3DModelScaleSet(model, 0.4f, 0.4f, 0.4f);
                Hu3DMotionTimeSet(model, 0.0f);
                Hu3DMotionSpeedSet(model, 2.0f);
                Hu3DMotionAttrSet(model, 1, 0);
                Hu3DModelAttrSet(object->model[2], 4, 4);
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
            MgPlayerMotSet(object, 0x27);
            if (Hu3DData[object->model[0]].motTime ==
                Hu3DMotion[Hu3DData[object->model[0]].motId].unk02 - 2.0) {
                omVibrate(data->unk59, 2, 3, 10);
            }
            break;
        case 5:
            if (work->unk20 != 0) {
                break;
            }
            if (work->unk32 != 0) {
                model = object->model[9];
                m256_HookPosGet(object->model[0], "item_hook", Hu3DData[object->model[0]].motTime, &pos);
                Hu3DModelAttrSet(model, 4, 0);
                Hu3DModelPosSet(model, pos.x, pos.y, pos.z + 10.0);
                Hu3DModelScaleSet(model, 0.4f, 0.4f, 0.4f);
                Hu3DMotionTimeSet(model, 0.0f);
                Hu3DMotionSpeedSet(model, 2.0f);
                Hu3DMotionAttrSet(model, 1, 0);
                Hu3DModelAttrSet(object->model[work->unk32 + 1], 4, 4);
            }
            if (work->unk2C) {
                GwPlayer[data->unk59].bonusCoin += 10;
                CharAnimSet(object->model[0], 2, motions.values[work->unk29], work->unk2F);
                MgPlayerMotSet(object, 0xD);
                HuAudCharVoicePlayPlayer(work->unk24, -1, work->unk2A);
            } else {
                CharAnimSet(object->model[0], 2, motions.values[work->unk29], work->unk30);
                MgPlayerMotSet(object, 0xE);
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
    HuMtxRotXF(*mtx, -50.0f);
    mtxRotCat(*mtx, 0.0f, rot, 0.0f);
    data->unk3C = rot;
    MgPlayerMotUpdate(object);
}

u16 m256_PlayerComInput(omObjData *arg0) {
    CrowdCoverComCandidates vec = m256_comCandidateTbl;
    CrowdCoverPlayerWork *work;
    s16 remaining;
    u16 result = 0;

    work = OM_GET_DATA_PTR(arg0, MgPlayerWork)->unk158;
    remaining = --work->unk34;
    if (remaining == 0) {
        result = work->unk36;
    }
    return result;
}

s16 m256_EffSprCreate(s16 spriteId, s16 x, s16 y, f32 rot) {
    s16 group; // Never assigned; the original passes an uninitialized value.
    s32 i;

    if (spriteId == -1) {
        return -1;
    }
    for (i = 0; i < 16; i++) {
        if (m256_effSprUsedTbl[i] == 0) {
            break;
        }
    }
    if (i >= 16) {
        return -1;
    }
    m256_effSprUsedTbl[i] = 1;
    HuSprGrpMemberSet(group, i, spriteId, 0);
    HuSprAnimModeSet(group, i, HUSPR_ANIM_MODE_PAT_LOOP);
    HuSprPosSet(group, i, x, y);
    HuSprZRotSet(group, i, rot);
    HuSprAttrReset(group, i, 0x8000);
    return i;
}

void m256_CrowdObjCreate(void) {
    omAddObj(3, 0xB, 0x32, -1, m256_CrowdObjInit);
}

const CrowdCoverComCandidates m256_comCandidateTbl = { { -1, -1, -1, -1, -1, -1, -1, -1, -1 } };

void m256_CrowdObjInit(omObjData *object) {
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

    m256_crowdSprAnim = m256_AnimDataRead(dataNums[m256_stageNo] | 0x590000);
    m256_crowdNum = 30;
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 0.8f;
    for (i = 0; i < m256_crowdNum; i++) {
        order[i] = i;
    }
    for (i = m256_crowdNum; i > 0; i--) {
        j = (f32)m256_Rand16Get() * 1.52587890625e-05 * i;
        temp = order[i - 1];
        order[i - 1] = order[j];
        order[j] = temp;
    }
    member = m256_crowdTbl;
    for (i = 0; i < m256_crowdNum; i++, member++) {
        member->crowdIndex = m256_BillboardCreate(m256_crowdSprAnim, 0x401808);
        member->model = Hu3DModelRead3(9, 0x2C9);
        Hu3DModelTPLvlInit(member->model);
        Hu3DModelTPLvlSet(member->model, 0xFF);
        member->pos.x = positions[order[i]].x;
        member->pos.y = positions[order[i]].y;
        member->pos.z = positions[order[i]].z;
        member->state = 1;
        member->unk04 = 0;
        member->timer = (s32)((f32)m256_Rand16Get() * 1.52587890625e-05 * 30.0) + 1;
        member->vel.x = member->vel.y = member->vel.z = 0.0f;
        member->unk06 = member->unk07 = 0;
        member->unk0C = 0.0f;
        member->unk34 = (f32)m256_Rand16Get() * 1.52587890625e-05 * 360.0;
        member->unk38 = member->unk3C = member->unk40 = 0.0f;
        if (m256_stageNo == 1) {
            member->unk34 = Hu3DModelRead2(0x10013, 0x2DD);
        } else if (m256_stageNo == 2) {
            member->unk3C = member->unk04 * 4;
        }
        m256_BillboardCenterSet(member->crowdIndex, 16.0f, 32.0f, 0.0f);
        m256_BillboardPosSet(member->crowdIndex, member->pos.x, member->pos.y, member->pos.z);
        m256_BillboardScaleSet(member->crowdIndex, 2.5f, 2.5f, 1.0f);
        Hu3DModelScaleSet(member->model, 0.45f, 0.45f, 0.45f);
    }
    object->func = m256_CrowdObjMain;
}

void m256_CrowdObjMain(omObjData *object) {
    CrowdCoverMember *member;
    CrowdCoverMember *other;
    s32 i;
    s32 j;
    s32 model;
    s32 frame;
    f32 scale;
    f32 angle;

    member = m256_crowdTbl;
    for (i = 0; i < m256_crowdNum; i++, member++) {
        member->timer--;
        switch (member->state) {
            case 0:
                member->timer = (s32)((f32)m256_Rand16Get() * 1.52587890625e-05 * 10.0) + 15;
                member->state = 1;
                member->vel.x = member->vel.z = 0.0f;
                if (m256_Rand16Get() & 1) {
                    break;
                }
                member->unk04 = (f32)m256_Rand16Get() * 1.52587890625e-05 * 8.0;
                if (m256_Rand16Get() & 1) {
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
                switch (m256_stageNo) {
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
                        m256_BillboardScaleSet(member->crowdIndex, scale, scale, 1.0f);
                        if (member->unk07 >= 8) {
                            m256_BillboardAttrSet(member->crowdIndex, 0x8000);
                            Hu3DModelAttrSet(member->model, 4, 4);
                            model = member->unk34;
                            HuAudFXPlay(0x4B7);
                            Hu3DModelAttrSet(model, 4, 0);
                            Hu3DModelPosSet(model, member->pos.x, member->pos.y + 40.0, member->pos.z);
                            Hu3DModelScaleSet(model, object->scale.x, object->scale.y, object->scale.z);
                            Hu3DMotionTimeSet(model, 0.0f);
                            Hu3DMotionSpeedSet(model, 1.5f);
                            Hu3DMotionAttrSet(model, 1, 0);
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
                        m256_BillboardColorSet(member->crowdIndex, 0, 0, 0, member->timer);
                        Hu3DModelTPLvlSet(member->model, member->timer);
                        if (member->timer == 0) {
                            member->state = 6;
                        }
                        break;
                }
                break;
            case 5:
                model = member->unk34;
                if (Hu3DData[model].motTime >= Hu3DMotion[Hu3DData[model].motId].unk02) {
                    Hu3DModelKill(model);
                    member->state = 6;
                }
                continue;
            case 6:
                m256_BillboardAttrSet(member->crowdIndex, 0x8000);
                Hu3DModelAttrSet(member->model, 4, 4);
                continue;
        }
        member->pos.x += member->vel.x;
        member->pos.z += member->vel.z;
        if (member->state < 4) {
            if (i >= (s16)(m256_timer / 30)) {
                member->vel.x = member->vel.z = 0.0f;
                member->state = 4;
                member->unk0C = 0.0f;
                member->unk38 = 0.0f;
                member->timer = 250;
            }
            for (j = 0; j < m256_crowdNum; j++) {
                if (i == j) {
                    continue;
                }
                other = &m256_crowdTbl[j];
                if (other->state >= 4) {
                    continue;
                }
                if (m256_DistCalc(&member->pos, &other->pos) >= 40.0) {
                    continue;
                }
                angle = m256_AngleCalc(other->pos.x - member->pos.x, other->pos.z - member->pos.z) + 180.0;
                member->state = 0;
                if (angle >= 360.0) {
                    angle -= 360.0;
                }
                member->pos.x = other->pos.x + sindf(angle) * 42.0;
                member->pos.z = other->pos.z + cosdf(angle) * 42.0;
            }
            if (member->pos.x > 200.0) {
                member->state = m256_Rand16Get() & 1;
                member->unk04 = (s32)((f32)m256_Rand16Get() * 1.52587890625e-05 * 3.0) + 5;
                member->pos.x = 200.0f;
            } else if (member->pos.x < -200.0) {
                member->state = m256_Rand16Get() & 1;
                member->unk04 = (s32)((f32)m256_Rand16Get() * 1.52587890625e-05 * 3.0) + 1;
                member->pos.x = -200.0f;
            }
            if (member->pos.z > -60.0) {
                member->state = m256_Rand16Get() & 1;
                member->unk04 = (s32)((f32)m256_Rand16Get() * 1.52587890625e-05 * 3.0) + 3;
                member->pos.z = -60.0f;
            } else if (member->pos.z < -500.0) {
                member->state = m256_Rand16Get() & 1;
                member->unk04 = ((s32)((f32)m256_Rand16Get() * 1.52587890625e-05 * 3.0) + 7) & 7;
                member->pos.z = -500.0f;
            }
        }
        member->unk06 = member->unk04;
        member->unk07 = member->unk0C;
        frame = m256_crowdWalkPatTbl[member->unk06][member->unk07];
        if (frame == -1) {
            member->unk07 = 0;
            member->unk0C = 0.0f;
            frame = m256_crowdWalkPatTbl[member->unk06][member->unk07];
        }
        if (m256_stageNo == 2) {
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
        m256_BillboardPosSet(member->crowdIndex, member->pos.x + member->offset.x,
                                  member->pos.y + member->offset.y, member->pos.z);
        m256_BillboardPatSet(member->crowdIndex, frame);
        Hu3DModelPosSet(member->model, member->pos.x, 0.0f, member->pos.z - 5.0);
    }
}

s32 m256_Rand16Get(void) {
    m256_randSeed = m256_randSeed * 0x41C64E6D + 0x3039;
    m256_randSeed += rand8();
    return m256_randSeed >> 16;
}

f32 m256_AngleCalc(f32 y, f32 x) {
    f32 fullCircle = 360.0f;
    f32 angle = atan2df(y, x);

    if (angle < 0.0f) {
        angle += fullCircle;
    } else if (angle >= fullCircle) {
        angle -= fullCircle;
    }
    return angle;
}

f32 m256_DistCalc(Vec *arg0, Vec *arg1) {
    return sqrtf(((arg0->x - arg1->x) * (arg0->x - arg1->x)) +
                 ((arg0->y - arg1->y) * (arg0->y - arg1->y)) +
                 ((arg0->z - arg1->z) * (arg0->z - arg1->z)));
}

void m256_DirRotCalc(Vec *dir, f32 *rot) {
    *rot++ = m256_AngleCalc(sqrtf(dir->x * dir->x + dir->z * dir->z), -dir->y);
    *rot++ = m256_AngleCalc(dir->z, dir->x);
    *rot = 0.0f;
}

void m256_HookPosGet(s16 model, char *hook, s16 time, Vec *pos) {
    HuMtx4F transform;
    HuMtx4F result;
    HuMtx4F hookTransform;
    HmfModel *modelData;

    Hu3DModelObjMtxFrameGet(model, time, hook, &hookTransform);
    modelData = &Hu3DData[model];
    mtxCopy(transform, modelData->mtx);
    mtxTransCat(transform, modelData->pos.x, modelData->pos.y, modelData->pos.z);
    mtxRotCat(transform, modelData->rot.x, modelData->rot.y, modelData->rot.z);
    mtxScaleCat(transform, modelData->scale.x, modelData->scale.y, modelData->scale.z);
    mtxCat(hookTransform, transform, result);
    pos->x = result[0][0] + result[1][0] + result[2][0] + result[3][0];
    pos->y = result[0][1] + result[1][1] + result[2][1] + result[3][1];
    pos->z = result[0][2] + result[1][2] + result[2][2] + result[3][2];
}

s16 m256_AnimDataRead(s32 dataNum) {
    void *data;
    s16 spriteId;

    data = DataRead(dataNum);
    spriteId = HuSprAnimRead(data);
    DataClose(data);
    return spriteId;
}

s16 m256_SprGrpCreate(s16 spriteId, s16 count) {
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

HuSprAnimPat *m256_SprAnimPatGet(s16 groupId, s16 member) {
    return &HuSprAnimDataGet(groupId)->pat[member];
}

void m256_BillboardInit(u16 count) {
    CrowdCoverBillboard *crowd;
    s16 i;

    m256_billboardNum = count;
    m256_billboardTbl = HuMemAlloc(count * sizeof(CrowdCoverBillboard));
    for (i = 0; i < 3; i++) {
        m256_billboardBufTbl[i] = NULL;
    }
    for (i = 0; i < m256_billboardNum; i++) {
        crowd = &m256_billboardTbl[i];
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

void m256_BillboardTileLoad(Gfx **gfx, HuSprAnimPat *cel, u8 fmt, u8 siz, u16 height, u16 uls,
                               u16 ult, u16 lrs, u16 lrt, u16 cms, u16 cmt, u16 masks, u16 maskt, s32 mode) {
    Gfx *gdl = *gfx;

    switch (mode) {
        case 0:
            gDPLoadTextureTile_4b(gdl++, (void *)0x0C000000, fmt, cel->sizeX, height, uls, ult, lrs, lrt, 0, cms,
                                  cmt, masks, maskt, 0, 0);
            break;
        case 1:
            HuLoadTextureBlock_4b(&gdl, (void *)0x0C000000, fmt, cel->sizeX, height, uls, ult, lrs, lrt, 0, cms, cmt,
                               masks, maskt, 0, 0);
            break;
        case 2:
            HuLoadTextureTile(&gdl, (u16 *)0x0C000000, fmt, siz, cel->sizeX, cel->sizeY, uls, ult, lrs, lrt, 0,
                               cms, cmt, masks, maskt, 0, 0);
            break;
        case 3:
            HuLoadTextureBlock(&gdl, (void *)0x0C000000, fmt, siz, cel->sizeX, height, uls, ult, lrs, lrt, 0, cms,
                               cmt, masks, maskt, 0, 0);
            break;
    }
    *gfx = gdl;
}

s16 m256_BillboardGfxBuild(CrowdCoverBillboard *crowd) {
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

    cel = crowd->sprite->pat;
    buf = HuMemAlloc(0x1000);
    gfx = buf;
    gSPSegment(gfx++, 0x0C, cel->data);
    gSPSegment(gfx++, 0x0E, crowd->vtx);
    start = gfx;
    gDPPipeSync(gfx++);
    switch (crowd->sprite->pixelBits) {
        case 4:
            siz = G_IM_SIZ_4b;
            if (crowd->sprite->palNum == 1) {
                fmt = G_IM_FMT_IA;
                gDPSetTextureLUT(gfx++, G_TT_NONE);
            } else {
                fmt = G_IM_FMT_CI;
                gDPLoadTLUT_pal16(gfx++, 0, crowd->sprite->pal);
                gDPSetTextureLUT(gfx++, G_TT_RGBA16);
            }
            mode = 0;
            break;
        case 8:
            siz = G_IM_SIZ_8b;
            if (crowd->sprite->palNum == 1) {
                fmt = G_IM_FMT_IA;
                gDPSetTextureLUT(gfx++, G_TT_NONE);
            } else {
                fmt = G_IM_FMT_CI;
                gDPLoadTLUT_pal256(gfx++, crowd->sprite->pal);
                gDPSetTextureLUT(gfx++, G_TT_RGBA16);
            }
            mode = 2;
            break;
        case 16:
            siz = G_IM_SIZ_16b;
            if (crowd->sprite->palNum == 1) {
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
            if (m256_tmemRowAltTbl[cel->sizeX >> m256_sizShiftTbl[siz]] >= rows ||
                rows == m256_tmemRowTbl[cel->sizeX >> m256_sizShiftTbl[siz]]) {
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
    segCel.data = (void *)0x0C000000;
    if ((u32)crowd->unk_28 >= 0x80000000 && count == 1 && remainder == 0) {
        m256_BillboardTileLoad(&gfx, &segCel, fmt, siz, rows, 0, 0, cel->sizeX - 1, cel->sizeY - 1, cms, cmt, masks,
                                  maskt, mode);
        gSPVertex(gfx++, (Vtx *)0x0E000000, 5, 0);
        gSP2Triangles(gfx++, 0, 2, 4, 0, 2, 3, 4, 0);
        gSP2Triangles(gfx++, 0, 4, 1, 0, 4, 3, 1, 0);
    } else {
        for (i = 0; i < count; i++) {
            m256_BillboardTileLoad(&gfx, &segCel, fmt, siz, rows, 0, i * rows, cel->sizeX - 1, (i + 1) * rows - 1,
                                      cms, cmt, masks, maskt, mode);
            gSPVertex(gfx++, (Vtx *)0x0E000000 + i * 2, 4, 0);
            gSP2Triangles(gfx++, 0, 2, 3, 0, 0, 3, 1, 0);
        }
        if (remainder != 0) {
            m256_BillboardTileLoad(&gfx, &segCel, fmt, siz, remainder, 0, i * rows, cel->sizeX - 1,
                                      cel->sizeY - 1, cms, cmt, masks, maskt, mode);
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

s16 m256_BillboardCreate(s16 spriteId, s32 flags) {
    CrowdCoverBillboard *crowd;
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

    for (index = 0; index < m256_billboardNum; index++) {
        if (m256_billboardTbl[index].sprite == NULL) {
            break;
        }
    }
    if (index == m256_billboardNum) {
        return -1;
    }
    crowd = &m256_billboardTbl[index];
    crowd->sprite = HuSprAnimTbl[spriteId];
    crowd->unk_28 = flags;
    crowd->unk_1A = 7;
    cel = crowd->sprite->pat;
    switch (crowd->sprite->pixelBits) {
        case 4:
            siz = G_IM_SIZ_4b;
            fmt = (crowd->sprite->palNum == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 8:
            siz = G_IM_SIZ_8b;
            fmt = (crowd->sprite->palNum == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 16:
            siz = G_IM_SIZ_16b;
            fmt = (crowd->sprite->palNum == 1) ? G_IM_FMT_IA : G_IM_FMT_RGBA;
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
    crowd->unk_18 = count + 2;
    crowd->unk_19 = rows;
    crowd->vtx = HuMemAlloc((count + 2) * 2 * sizeof(Vtx));
    for (i = 0; i < count + 1; i++) {
        crowd->vtx[i * 2].ob[0] = 0;
        crowd->vtx[i * 2 + 1].ob[0] = cel->sizeX;
        crowd->vtx[i * 2].ob[1] = crowd->vtx[i * 2 + 1].ob[1] = -i * rows;
        crowd->vtx[i * 2].tc[0] = 0;
        crowd->vtx[i * 2 + 1].tc[0] = cel->sizeX << 6;
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
        crowd->vtx[i * 2 + 1].ob[0] = cel->sizeX;
        crowd->vtx[i * 2].ob[1] = crowd->vtx[i * 2 + 1].ob[1] = cel->sizeY;
        crowd->vtx[i * 2].tc[0] = 0;
        crowd->vtx[i * 2 + 1].tc[0] = cel->sizeX << 6;
        crowd->vtx[i * 2].tc[1] = crowd->vtx[i * 2 + 1].tc[1] = cel->sizeY << 6;
        for (j = 0; j < 2; j++) {
            crowd->vtx[i * 2 + j].ob[2] = 0;
            crowd->vtx[i * 2 + j].cn[0] = 0xFF;
            crowd->vtx[i * 2 + j].cn[1] = 0xFF;
            crowd->vtx[i * 2 + j].cn[2] = 0xFF;
            crowd->vtx[i * 2 + j].cn[3] = 0xFF;
        }
    } else if (count == 1) {
        crowd->vtx[4].ob[0] = cel->sizeX * 0.5;
        crowd->vtx[4].ob[1] = -cel->sizeY * 0.5;
        crowd->vtx[4].ob[2] = 0;
        crowd->vtx[4].tc[0] = cel->sizeX * 0.5 * 64.0;
        crowd->vtx[4].tc[1] = cel->sizeY * 0.5 * 64.0;
        crowd->vtx[4].cn[0] = 0xFF;
        crowd->vtx[4].cn[1] = 0xFF;
        crowd->vtx[4].cn[2] = 0xFF;
        crowd->vtx[4].cn[3] = 0xFF;
    }
    if (!m256_BillboardGfxBuild(crowd)) {
        HuMemFree(crowd->vtx);
        index = -1;
    }
    return index;
}

void m256_BillboardSprSet(s16 index, s16 spriteId) {
    CrowdCoverBillboard *crowd;
    HuSprAnimPat *cel;
    s32 siz;
    s32 fmt;
    s32 alignedWidth;
    u32 rows;
    u32 count;
    s32 remainder;
    u32 i;
    s32 j;

    crowd = &m256_billboardTbl[index];
    crowd->sprite = HuSprAnimTbl[spriteId];
    cel = crowd->sprite->pat;
    HuMemFree(crowd->vtx);
    HuMemFree(crowd->displayList);
    switch (crowd->sprite->pixelBits) {
        case 4:
            siz = G_IM_SIZ_4b;
            fmt = (crowd->sprite->palNum == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 8:
            siz = G_IM_SIZ_8b;
            fmt = (crowd->sprite->palNum == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 16:
            siz = G_IM_SIZ_16b;
            fmt = (crowd->sprite->palNum == 1) ? G_IM_FMT_IA : G_IM_FMT_RGBA;
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
    crowd->unk_18 = count + 2;
    crowd->unk_19 = rows;
    crowd->vtx = HuMemAlloc((count + 2) * 2 * sizeof(Vtx));
    for (i = 0; i < count + 1; i++) {
        crowd->vtx[i * 2].ob[0] = 0;
        crowd->vtx[i * 2 + 1].ob[0] = cel->sizeX;
        crowd->vtx[i * 2].ob[1] = crowd->vtx[i * 2 + 1].ob[1] = -i * rows;
        crowd->vtx[i * 2].tc[0] = 0;
        crowd->vtx[i * 2 + 1].tc[0] = cel->sizeX << 6;
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
        crowd->vtx[i * 2 + 1].ob[0] = cel->sizeX;
        crowd->vtx[i * 2].ob[1] = crowd->vtx[i * 2 + 1].ob[1] = cel->sizeY;
        crowd->vtx[i * 2].tc[0] = 0;
        crowd->vtx[i * 2 + 1].tc[0] = cel->sizeX << 6;
        crowd->vtx[i * 2].tc[1] = crowd->vtx[i * 2 + 1].tc[1] = cel->sizeY << 6;
        for (j = 0; j < 2; j++) {
            crowd->vtx[i * 2 + j].ob[2] = 0;
            crowd->vtx[i * 2 + j].cn[0] = 0xFF;
            crowd->vtx[i * 2 + j].cn[1] = 0xFF;
            crowd->vtx[i * 2 + j].cn[2] = 0xFF;
            crowd->vtx[i * 2 + j].cn[3] = 0xFF;
        }
    } else if (count == 1) {
        crowd->vtx[4].ob[0] = cel->sizeX * 0.5;
        crowd->vtx[4].ob[1] = -cel->sizeY * 0.5;
        crowd->vtx[4].ob[2] = 0;
        crowd->vtx[4].tc[0] = cel->sizeX * 0.5 * 64.0;
        crowd->vtx[4].tc[1] = cel->sizeY * 0.5 * 64.0;
        crowd->vtx[4].cn[0] = 0xFF;
        crowd->vtx[4].cn[1] = 0xFF;
        crowd->vtx[4].cn[2] = 0xFF;
        crowd->vtx[4].cn[3] = 0xFF;
    }
    m256_BillboardGfxBuild(crowd);
}

void m256_BillboardSprReplace(s16 index, s16 spriteId) {
    CrowdCoverBillboard *crowd;

    if (index != -1) {
        crowd = &m256_billboardTbl[index];
        crowd->sprite = HuSprAnimTbl[spriteId];
        crowd->unk_20 = 0x100;
        crowd->unk_1F = 0xFF;
        crowd->unk_1E = 0xFF;
        crowd->unk_1D = 0xFF;
        crowd->unk_2C = 0;
        crowd->unk_24 = 0;
        crowd->unk_30.x = 1.0f;
    }
}

void m256_BillboardPatSet(s16 index, s16 value) {
    CrowdCoverBillboard *crowd;

    if (index != -1) {
        crowd = &m256_billboardTbl[index];
        crowd->unk_24 = value;
        crowd->unk_2C = 0;
    }
}

void m256_BillboardAnimSpeedSet(s16 index, f32 value) {
    CrowdCoverBillboard *crowd;

    if (index != -1) {
        crowd = &m256_billboardTbl[index];
        crowd->unk_30.x = value;
    }
}

void m256_BillboardCenterSet(s16 index, f32 y, f32 z, f32 unk_3C) {
    CrowdCoverBillboard *crowd;

    if (index != -1) {
        crowd = &m256_billboardTbl[index];
        crowd->unk_28 |= 0x4000000;
        crowd->unk_30.y = y;
        crowd->unk_30.z = z;
        crowd->unk_3C = unk_3C;
    }
}

void m256_BillboardCenterZSet(s16 index, f32 value) {
    CrowdCoverBillboard *crowd;

    if (index != -1) {
        crowd = &m256_billboardTbl[index];
        crowd->unk_3C = value;
    }
}

void m256_BillboardPosSet(s16 index, f32 x, f32 y, f32 z) {
    CrowdCoverBillboard *crowd;

    if (index != -1) {
        crowd = &m256_billboardTbl[index];
        crowd->unk_40.x = x;
        crowd->unk_40.y = y;
        crowd->unk_40.z = z;
    }
}

void m256_BillboardPosAdd(s16 index, f32 x, f32 y, f32 z) {
    CrowdCoverBillboard *crowd;

    if (index != -1) {
        crowd = &m256_billboardTbl[index];
        crowd->unk_40.x += x;
        crowd->unk_40.y += y;
        crowd->unk_40.z += z;
    }
}

void m256_BillboardScaleSet(s16 index, f32 x, f32 y, f32 z) {
    CrowdCoverBillboard *crowd;

    if (index != -1) {
        crowd = &m256_billboardTbl[index];
        crowd->unk_4C.x = x;
        crowd->unk_4C.y = y;
        crowd->unk_4C.z = z;
    }
}

void m256_BillboardRotSet(s16 index, f32 x, f32 y, f32 z) {
    CrowdCoverBillboard *crowd;

    if (index != -1) {
        crowd = &m256_billboardTbl[index];
        crowd->unk_58.x = x;
        crowd->unk_58.y = y;
        crowd->unk_58.z = z;
    }
}

void m256_BillboardAttrSet(s16 index, s32 value) {
    CrowdCoverBillboard *crowd;

    if (index != -1) {
        crowd = &m256_billboardTbl[index];
        crowd->unk_28 |= value;
    }
}

void m256_BillboardAttrReset(s16 index, s32 value) {
    CrowdCoverBillboard *crowd;

    if (index != -1) {
        crowd = &m256_billboardTbl[index];
        crowd->unk_28 &= ~value;
    }
}

s32 m256_BillboardAttrGet(s16 index) {
    CrowdCoverBillboard *crowd;
    s32 i = index;

    if (i != -1) {
        crowd = &m256_billboardTbl[i];
        return crowd->unk_28;
    }
    return -1;
}

void m256_BillboardModeSet(s16 index, s8 value) {
    CrowdCoverBillboard *crowd;

    if (index != -1) {
        crowd = &m256_billboardTbl[index];
        crowd->unk_1A = value;
    }
}

CrowdCoverBillboard *m256_BillboardGet(s16 index) {
    CrowdCoverBillboard *crowd;
    s32 i = index;

    if (i == -1) {
        return NULL;
    }
    crowd = &m256_billboardTbl[i];
    return crowd;
}

Vtx_t *m256_BillboardVtxGet(s16 index) {
    CrowdCoverBillboard *crowd;
    s32 i = index;

    if (i == -1) {
        return NULL;
    }
    crowd = &m256_billboardTbl[i];
    return crowd->vtx;
}

s32 m256_BillboardCenterVtxSet(s16 index, s16 x, s16 y) {
    CrowdCoverBillboard *crowd;
    Vtx_t *vtx;

    if (index == -1) {
        return 0;
    }
    crowd = &m256_billboardTbl[index];
    if (crowd->unk_18 != 3) {
        return 0;
    }
    crowd->unk_28 |= 0x80000000;
    vtx = &crowd->vtx[4];
    vtx->ob[0] = x;
    vtx->ob[1] = -y;
    vtx->ob[2] = 0;
    vtx->tc[0] = x * 64;
    vtx->tc[1] = y * 64;
    return 1;
}

void m256_BillboardColorSet(s16 index, s8 value1, s8 value2, s8 value3, s16 value4) {
    CrowdCoverBillboard *crowd;

    if (index != -1) {
        crowd = &m256_billboardTbl[index];
        crowd->unk_1D = value1;
        crowd->unk_1E = value2;
        crowd->unk_1F = value3;
        crowd->unk_20 = value4;
    }
}

void m256_BillboardKill(s16 index) {
    CrowdCoverBillboard *crowd;

    if (index != -1) {
        crowd = &m256_billboardTbl[index];
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

void m256_BillboardDarkSet(s32 index, s32 flag) {
    CrowdCoverBillboard *crowd = &m256_billboardTbl[index];
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

void m256_BillboardFlipXSet(s32 index, s32 flip) {
    CrowdCoverBillboard *crowd = &m256_billboardTbl[index];
    s32 i;

    if (flip) {
        for (i = 0; i < crowd->unk_18; i++) {
            crowd->vtx[i * 2].tc[0] = crowd->sprite->pat->sizeX << 6;
            crowd->vtx[i * 2 + 1].tc[0] = 0;
        }
    } else {
        for (i = 0; i < crowd->unk_18; i++) {
            crowd->vtx[i * 2].tc[0] = 0;
            crowd->vtx[i * 2 + 1].tc[0] = crowd->sprite->pat->sizeX << 6;
        }
    }
}

void m256_BillboardFlipYSet(s32 index, s32 flip) {
    CrowdCoverBillboard *crowd = &m256_billboardTbl[index];
    s32 remainder = crowd->sprite->pat->sizeY - (crowd->unk_18 - 2) * crowd->unk_19;
    s32 i;

    if (flip) {
        for (i = 0; i < crowd->unk_18 - 1; i++) {
            crowd->vtx[i * 2].tc[1] = crowd->vtx[i * 2 + 1].tc[1] =
                crowd->sprite->pat->sizeY - i * crowd->unk_19;
        }
        if (remainder != 0) {
            crowd->vtx[i * 2].tc[1] = crowd->vtx[i * 2 + 1].tc[1] = 0;
        }
    } else {
        for (i = 0; i < crowd->unk_18 - 1; i++) {
            crowd->vtx[i * 2].ob[1] = crowd->vtx[i * 2 + 1].ob[1] = i * crowd->unk_19;
        }
        if (remainder != 0) {
            crowd->vtx[i * 2].ob[1] = crowd->vtx[i * 2 + 1].ob[1] = crowd->sprite->pat->sizeY;
        }
    }
}

void m256_BillboardHookSet(s16 index, void (*callback)(struct CrowdCoverBillboard *)) {
    CrowdCoverBillboard *crowd;

    if (index != -1) {
        crowd = &m256_billboardTbl[index];
        crowd->callback = callback;
    }
}

void m256_BillboardTileSet(s16 index, s8 arg1, s8 arg2, s32 flags) {
    CrowdCoverBillboard *crowd;

    if (index != -1) {
        crowd = &m256_billboardTbl[index];
        crowd->unk_1B = arg1;
        crowd->unk_1C = arg2;
        crowd->unk_28 |= flags;
        HuMemFree(crowd->displayList);
        m256_BillboardGfxBuild(crowd);
    }
}

void m256_BillboardTintSet(s16 index, s32 flag) {
    CrowdCoverBillboard *crowd;
    s8 color;
    s8 blue;
    s32 i;

    if (index != -1) {
        crowd = &m256_billboardTbl[index];
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

void m256_BillboardBufAlloc(void) {
    CrowdCoverBillboard *crowd;
    s32 i;

    if (++m256_billboardBufNo >= 3) {
        m256_billboardBufNo = 0;
    }
    m256_billboardBufSize = 0;
    for (i = 0; i < m256_billboardNum; i++) {
        crowd = &m256_billboardTbl[i];
        if (crowd->sprite != NULL) {
            m256_billboardBufSize += 0x40 + (crowd->unk_22 * sizeof(Gfx) + crowd->unk_18 * 2 * sizeof(Vtx));
        }
    }
    if (m256_billboardBufTbl[m256_billboardBufNo] != NULL) {
        HuMemFree(m256_billboardBufTbl[m256_billboardBufNo]);
    }
    if (m256_billboardBufSize != 0) {
        m256_billboardBufTbl[m256_billboardBufNo] = HuMemAlloc(m256_billboardBufSize);
    } else {
        m256_billboardBufTbl[m256_billboardBufNo] = NULL;
    }
    m256_billboardBufCur = m256_billboardBufTbl[m256_billboardBufNo];
}

void m256_BillboardSort(HuCamera *camera, HuMtx4F lookAt) {
    CrowdCoverBillboard tailOpaque;
    CrowdCoverBillboard tailTranslucent;
    HuMtx4F unused[16]; // Unreferenced, but present in the stack frame.
    HuMtx4F mtx;
    CrowdCoverBillboard *crowd;
    CrowdCoverBillboard *node;
    f32 minX;
    f32 maxX;
    f32 minZ;
    f32 maxZ;
    s32 i;

    minX = camera->at.x - 640.0;
    maxX = camera->at.x + 640.0;
    minZ = camera->at.z - 640.0;
    maxZ = camera->at.z + 640.0;
    m256_billboardOpaHead.unk_64 = 0.0f;
    m256_billboardXluHead.unk_64 = 99999.9f;
    tailOpaque.unk_64 = -99999.9f;
    tailTranslucent.unk_64 = 0.0f;
    m256_billboardXluHead.prev = NULL;
    m256_billboardOpaHead.prev = NULL;
    m256_billboardOpaHead.next = &tailOpaque;
    m256_billboardXluHead.next = &tailTranslucent;
    tailOpaque.prev = &m256_billboardOpaHead;
    tailTranslucent.prev = &m256_billboardXluHead;
    tailTranslucent.next = NULL;
    tailOpaque.next = NULL;
    for (i = 0; i < m256_billboardNum; i++) {
        crowd = &m256_billboardTbl[i];
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
            node = &m256_billboardXluHead;
        } else {
            node = &m256_billboardOpaHead;
        }
        for (node = node->next; node->unk_64 > crowd->unk_64; node = node->next) {}
        node->prev->next = crowd;
        crowd->prev = node->prev;
        crowd->next = node;
        node->prev = crowd;
    }
    tailOpaque.prev->next = tailTranslucent.prev->next = NULL;
}

void m256_BillboardDraw(Gfx **gfxP, s32 arg1, s32 arg2) {
    HuCamera *camera = (HuCamera *)arg2;
    Gfx *gfx = *gfxP;
    HuMtx4F unused1[2]; // Unreferenced, but present in the stack frame.
    HuMtx4F lookAt;
    HuMtx4F unused2[4]; // Unreferenced, but present in the stack frame.
    Vec rot;
    Vec dir;
    HuMtx4F unused3[32]; // Unreferenced, but present in the stack frame.
    CrowdCoverBillboard *crowd;

    guLookAtF(lookAt, camera->pos.x, camera->pos.y, camera->pos.z, camera->at.x, camera->at.y, camera->at.z,
              camera->up.x, camera->up.y, camera->up.z);
    dir.x = camera->pos.x - camera->at.x;
    dir.y = camera->pos.y - camera->at.y;
    dir.z = camera->pos.z - camera->at.z;
    m256_DirRotCalc(&dir, (f32 *)&rot);
    m256_BillboardBufAlloc();
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_2CYCLE);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING | G_TEXTURE_GEN);
    gSPSetGeometryMode(gfx++, G_SHADE | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    m256_BillboardSort(camera, lookAt);
    for (crowd = m256_billboardOpaHead.next; crowd != NULL; crowd = crowd->next) {
        gfx = m256_BillboardEntryDraw(gfx, crowd, lookAt, &rot);
    }
    for (crowd = m256_billboardXluHead.next; crowd != NULL; crowd = crowd->next) {
        gfx = m256_BillboardEntryDraw(gfx, crowd, lookAt, &rot);
    }
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    *gfxP = gfx;
    if (!Hu3DPauseF) {
        m256_BillboardAnimUpdate();
    }
}

Gfx *m256_BillboardEntryDraw(Gfx *gfx, CrowdCoverBillboard *crowd, HuMtx4F lookAt, Vec *rot) {
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

    cel = &crowd->sprite->pat[crowd->unk_24];
    gDPPipeSync(gfx++);
    gDPSetTextureFilter(gfx++, m256_texFilterTbl[(crowd->unk_28 >> 2) & 3]);
    gDPSetColorDither(gfx++, m256_colorDitherTbl[(crowd->unk_28 >> 4) & 3]);
    gDPSetAlphaCompare(gfx++, m256_alphaCompareTbl[(crowd->unk_28 >> 22) & 3]);
    if (crowd->unk_28 & 0x10000) {
        gSPSetGeometryMode(gfx++, G_LIGHTING);
    } else {
        gSPClearGeometryMode(gfx++, G_LIGHTING);
    }
    format = crowd->sprite->pixelBits;
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
    vtx = m256_billboardBufCur;
    mtxL = (Mtx *)&vtx[crowd->unk_18 * 2];
    dl = (Gfx *)&mtxL[1];
    m256_billboardBufCur = &dl[crowd->unk_22];
    guMtxIdentF(billboard);
    if (crowd->unk_28 & 0x4000000) {
        billboard[3][0] = -crowd->unk_30.y;
        billboard[3][1] = crowd->unk_30.z;
    } else {
        billboard[3][0] = -(u16)cel->centerX;
        billboard[3][1] = (u16)cel->centerY;
    }
    billboard[3][2] = crowd->unk_3C;
    mtxCopy(mtx, lookAt);
    mtxTransCat(mtx, crowd->unk_40.x, crowd->unk_40.y, crowd->unk_40.z);
    mtxRotCat(mtx, crowd->unk_58.x, crowd->unk_58.y, crowd->unk_58.z);
    mtxScaleCat(mtx, crowd->unk_4C.x, crowd->unk_4C.y, crowd->unk_4C.z);
    switch (crowd->unk_1A) {
        case 1:
            HuMtxRotXF(mtx, rot->x);
            break;
        case 2:
            HuMtxRotYF(mtx, rot->y);
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
            HmfInverseMtxF3X3Cat(mtx, inverse);
            mtxCat(scale, inverse, mtx);
            break;
    }
    guMtxCatF(billboard, mtx, mtx);
    guMtxF2L(mtx, mtxL);
    gDPPipeSync(gfx++);
    gSPMatrix(gfx++, osVirtualToPhysical(mtxL), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPPipeSync(gfx++);
    gSPSegment(gfx++, 0x0C, cel->data);
    gSPSegment(gfx++, 0x0E, vtx);
    gDPPipeSync(gfx++);
    memcpy(vtx, crowd->vtx, crowd->unk_18 * 2 * sizeof(Vtx));
    memcpy(dl, crowd->displayList, crowd->unk_22 * sizeof(Gfx));
    if (!(crowd->unk_28 & 0x8000)) {
        gSPDisplayList(gfx++, dl);
    }
    return gfx;
}

void m256_BillboardAnimUpdate(void) {
    CrowdCoverBillboard *crowd;
    s32 frameCount;
    s32 i;

    for (i = 0; i < m256_billboardNum; i++) {
        crowd = &m256_billboardTbl[i];
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
        frameCount = crowd->sprite->patNum;
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
                        m256_BillboardKill(i);
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

void m256_BillboardClose(void) {
    s32 i;

    for (i = 0; i < m256_billboardNum; i++) {
        m256_BillboardKill(i);
    }
    for (i = 0; i < 3; i++) {
        if (m256_billboardBufTbl[i] != NULL) {
            HuMemFree(m256_billboardBufTbl[i]);
        }
    }
    HuMemFree(m256_billboardTbl);
}
