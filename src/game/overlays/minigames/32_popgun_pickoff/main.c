#include "common.h"
#include "game/overlays/minigame.h"
#include "game/hmfmath.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"
#include "game/texload.h"

#define PLAYER_WORK(obj) ((PopgunPickoffPlayerWork *)((MgPlayerWork *)(obj)->data)->unk158)

#define POPGUN_CC_PRIM_DECALA 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0
#define POPGUN_CC_PRIM_MODULATEA 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0
#define POPGUN_CC_BLEND_DECALA 1, PRIMITIVE, TEXEL0, PRIMITIVE, 0, 0, 0, TEXEL0
#define POPGUN_CC_BLEND_MODULATEA 1, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0
#define POPGUN_CC_MODULATEI_PRIMA TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0
#define POPGUN_CC_MODULATEI_PASSA2 COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED

typedef struct PopgunPickoffBillboard {
    /* 0x00 */ Gfx *displayList;
    /* 0x04 */ Vtx_t *vtx;
    /* 0x08 */ HuSprAnimData *sprite;
    /* 0x0C */ struct PopgunPickoffBillboard *prev;
    /* 0x10 */ struct PopgunPickoffBillboard *next;
    /* 0x14 */ void (*callback)(struct PopgunPickoffBillboard *);
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
} PopgunPickoffBillboard; // Size 0x68

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

// Per-player work allocated in m250_PlayerCreate, stored at ObjData->unk158
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
} PopgunPickoffPhaseWork; // Size 0x6

extern HuSprAnimData *HuSprAnimTbl[];
extern s32 omCharModelNoTbl[][6];

s32 m250_waitTimer = 0;
u16 m250_timer = 0;
s32 m250_winner = -1;
s32 m250_finishPanTimer = 25;
s16 m250_musicTimer = 0;
s16 m250_spawnTimer = 1;
s16 m250_spawnCnt = 0;
s16 m250_unusedNoTbl[4] = { 0, 1, 2, 3 }; /* Unreferenced. */
u8 m250_playerInitNo = 0;
s32 m250_unusedNum = 0; /* Unreferenced. */
s16 m250_playerPosTbl[4][3] = {
    { -140, 20, 0 },
    { 140, 20, 0 },
    { 85, -75, -200 },
    { 85, 75, -200 }
};
f32 m250_playerRotTbl[4] = { 180.0f, 180.0f, -45.0f, -135.0f };
s16 m250_aimRotXTbl[3] = { -20, -10, 0 };
s16 m250_aimRotYTbl[2][3] = {
    { 0, -20, -30 },
    { 30, 20, 0 }
};
u32 m250_randSeed = 0x41C64E6D;
s32 m250_sizShiftTbl[] = { 4, 3, 2, 1 };
s16 m250_tmemRowAltTbl[] = {
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
s16 m250_tmemRowTbl[] = {
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
s16 m250_colorDitherTbl[] = { G_CD_DISABLE, G_CD_NOISE, G_CD_BAYER, G_CD_MAGICSQ };
s16 m250_texFilterTbl[] = { G_TF_POINT, G_TF_POINT, G_TF_BILERP, G_TF_AVERAGE };
s16 m250_alphaCompareTbl[] = { G_AC_THRESHOLD, G_AC_NONE, G_AC_DITHER, G_AC_NONE };
s32 m250_billboardBufNo = 0;

s16 m250_sprAnimTbl[16] BSS;
s16 m250_sprGrpTbl[8] BSS;
s16 m250_effSprUsedTbl[16] BSS;
PopgunPickoffPhaseWork m250_phaseWork BSS;
PopgunPickoffTarget m250_targetTbl[9] BSS;
u8 m250_targetTblPad[8] BSS; /* Unreferenced. */
PopgunPickoffShot m250_shotTbl[128] BSS;
f32 m250_viewMtx[4][4] BSS;
f32 m250_viewInvMtx[4][4] BSS;
f32 m250_fovTan BSS;
u8 m250_shotCnt BSS;
PopgunPickoffBillboard *m250_billboardTbl BSS;
void *m250_billboardBufTbl[3] BSS;
void *m250_billboardBufCur BSS;
s32 m250_billboardBufSize BSS;
s32 m250_billboardNum BSS;
u8 m250_billboardNumPad[0xC] BSS;             /* Unreferenced. */
PopgunPickoffBillboard m250_billboardOpaHead BSS; // List head of opaque entries
PopgunPickoffBillboard m250_billboardXluHead BSS; // List head of translucent entries
u8 m250_billboardXluHeadPad[0x10] BSS;            /* Unreferenced. */

/* Fields of m250_phaseWork, aliased in undefined_syms.txt. */
extern s16 m250_phase;
extern s16 m250_scoreTbl[2];

void m250_CameraViewInit(omObjData *object);
s32 m250_Rand16Get(void);
f32 m250_AngleCalc(f32 y, f32 x);
f32 m250_DistCalc(Vec *arg0, Vec *arg1);
u8 m250_PenaltyCreate(s16 x, s16 y);
void m250_BillboardAttrSet(s16 playerId, s32 value);
void m250_BillboardAttrReset(s16 playerId, s32 value);
void m250_BillboardKill(s16 playerId);
void m250_MtxVecMul(HuMtx4F mtx, f32 x, f32 y, f32 z, f32 *dst);
void m250_MtxInvert(HuMtx4F src, HuMtx4F dst);
void m250_StageObjCreate(void);
void m250_StageObjInit(omObjData *object);
void m250_StageObjMain(omObjData *object);
void m250_ShotTargetUpdate(omObjData *object);
void m250_PlayerObjCreateAll(void);
void m250_PlayerObjInit(omObjData *object);
void m250_PlayerCreate(omObjData *object, s32 arg1, s32 arg2, u16 player, u16 tag);
void m250_PlayerObjMain(omObjData *object);
u16 m250_PlayerComInput(omObjData *object);
u8 m250_ShotCreate(omObjData *object, s32 targetIndex);
void m250_HookPosGet(s16 model, char *hook, s16 time, Vec *pos);
s16 m250_AnimDataRead(s32 dataNum);
s16 m250_SprGrpCreate(s16 spriteId, s16 count);
HuSprAnimPat *m250_SprAnimPatGet(s16 groupId, s16 member);
s16 m250_BillboardGfxBuild(PopgunPickoffBillboard *player);
void m250_DirRotCalc(Vec *dir, f32 *rot);
void m250_BillboardBufAlloc(void);
void m250_BillboardSort(HuCamera *camera, HuMtx4F lookAt);
Gfx *m250_BillboardEntryDraw(Gfx *gfx, PopgunPickoffBillboard *player, HuMtx4F lookAt, Vec *rot);
void m250_BillboardAnimUpdate(void);
s16 m250_BillboardCreate(s16 spriteId, s32 flags);
void m250_BillboardCenterSet(s16 playerId, f32 x, f32 y, f32 z);
void m250_BillboardPosSet(s16 playerId, f32 x, f32 y, f32 z);
void m250_BillboardPatSet(s16 playerId, s16 value);
void m250_BillboardScaleSet(s16 playerId, f32 x, f32 y, f32 z);
void m250_BillboardRotSet(s16 playerId, f32 x, f32 y, f32 z);
void m250_BillboardModeSet(s16 playerId, s8 value);
void m250_BillboardColorSet(s16 playerId, s8 value1, s8 value2, s8 value3, s16 value4);
void m250_BillboardDraw(Gfx **gfxP, s32 arg1, s32 arg2);
void m250_BillboardClose(void);
void m250_BillboardInit(u16 count);

void m250_ObjectSetup(void) {
    omObjData *obj;
    u8 camIndex;

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
    m250_CameraViewInit(obj);
    m250_StageObjCreate();
    m250_BillboardInit(0x80);
    m250_PlayerObjCreateAll();
    Hu3DBGColorSet(180, 180, 180);
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
}

void m250_CameraViewInit(omObjData *object) {
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
    m250_fovTan = sinFov / cosFov;
    guMtxL2F(m250_viewMtx, &camera->mtxs[0].lookAtMtx);
    guMtxL2F(m250_viewInvMtx, &camera->mtxs[0].lookAtMtx);
    m250_MtxInvert(m250_viewInvMtx, m250_viewInvMtx);
}

void m250_MtxVecMul(HuMtx4F mtx, f32 x, f32 y, f32 z, f32 *dst) {
    dst[0] = ((x * mtx[0][0]) + (y * mtx[1][0])) + (z * mtx[2][0]);
    dst[1] = ((x * mtx[0][1]) + (y * mtx[1][1])) + (z * mtx[2][1]);
    dst[2] = ((x * mtx[0][2]) + (y * mtx[1][2])) + (z * mtx[2][2]);
}

void m250_MtxInvert(HuMtx4F src, HuMtx4F dst) {
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

        m250_MtxVecMul(dst, -mtx[3][0], -mtx[3][1], -mtx[3][2], dstRow3);
    }
}

void m250_ScreenPosCalc(f32 *pos, f32 *dst) {
    f32 mtx[4][4];
    f32 depth;
    f32 scale;

    guTranslateF(mtx, pos[0], pos[1], pos[2]);
    guMtxCatF(mtx, m250_viewMtx, mtx);
    depth = mtx[3][2] * m250_fovTan;
    scale = fabsf(depth);
    if (scale != 0.0) {
        dst[0] = mtx[3][0] * 160.0f / scale / 1.3333333333333333;
        dst[1] = -mtx[3][1] * 120.0f / scale;
    }
    dst[0] += 160.0;
    dst[1] += 120.0;
    dst[2] = scale;
}

void m250_WorldPosCalc(f32 x, f32 y, f32 z, f32 *dst) {
    f32 depth = z + m250_viewMtx[3][2];
    f32 scale = fabsf(depth * m250_fovTan);
    f32 mtx[4][4];

    x -= 160.0;
    y -= 120.0;
    guTranslateF(mtx, (x + x) * scale * 1.3333333333333333 / 320.0, -((y + y) * scale / 240.0f), depth);
    guMtxCatF(mtx, m250_viewInvMtx, mtx);
    dst[0] = mtx[3][0];
    dst[1] = mtx[3][1];
    dst[2] = mtx[3][2];
}

void m250_StageObjCreate(void) {
    mgMapObjNum = 0;
    MgMapBaseSet(0);
    mgMapObjTbl[mgMapObjNum++] = omAddObj(5, 10, 0, -1, m250_StageObjInit);
    m250_phase = 0;
    m250_scoreTbl[0] = m250_scoreTbl[1] = 0;
}

void m250_StageObjInit(omObjData *object) {
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

    m250_sprAnimTbl[0] = m250_AnimDataRead(0x530000);
    m250_sprGrpTbl[0] = m250_SprGrpCreate(m250_sprAnimTbl[0], 1);
    HuSprPosSet(m250_sprGrpTbl[0], 0, 160, 120);
    HuSprAttrSet(m250_sprGrpTbl[0], 0, 0x4000);
    m250_sprAnimTbl[1] = m250_AnimDataRead(0x530001);
    spr = m250_SprAnimPatGet(m250_sprAnimTbl[1], 0);
    m250_sprGrpTbl[1] = m250_BillboardCreate(m250_sprAnimTbl[1], 0x1808);
    m250_BillboardPosSet(m250_sprGrpTbl[1], 0.0f, -70.0f, -400.0f);
    m250_BillboardScaleSet(m250_sprGrpTbl[1], 3.0f, 3.0f, 1.0f);
    m250_BillboardCenterSet(m250_sprGrpTbl[1], spr->sizeX * 0.5, spr->sizeY, 0.0f);
    m250_BillboardModeSet(m250_sprGrpTbl[1], 0);
    m250_sprAnimTbl[4] = m250_AnimDataRead(0x530004);
    m250_sprAnimTbl[5] = m250_AnimDataRead(0x530005);
    for (i = 0; i < 9; i++) {
        target = &m250_targetTbl[i];
        pos[0] = target->pos.x = (positions[i][0] - spr->sizeX * 0.5) * 3.0;
        pos[1] = target->pos.y = (spr->sizeY - positions[i][1]) * 3.0 + -70.0;
        pos[2] = target->pos.z = -400.0f;
        m250_ScreenPosCalc(pos, screen);
        target->screenX = screen[0];
        target->screenY = screen[1];
        target->unk0C = -90.0f;
        target->unk14 = -1;
        target->unk16 = 0;
        target->unk1B = 0;
        target->playerId = m250_BillboardCreate(m250_sprAnimTbl[4], 0x12009808);
        m250_BillboardCenterSet(target->playerId, 16.0f, 32.0f, 0.0f);
        m250_BillboardPosSet(target->playerId, target->pos.x, target->pos.y - 42.0, target->pos.z - 10.0);
        m250_BillboardScaleSet(target->playerId, 3.0f, 3.0f, 1.0f);
        m250_BillboardRotSet(target->playerId, 90.0f, 0.0f, 0.0f);
        m250_BillboardModeSet(target->playerId, 0);
        m250_BillboardColorSet(target->playerId, 0, 0, 0, 0x100);
    }
    for (i = 0; i < 0x80; i++) {
        shot = &m250_shotTbl[i];
        shot->active = 0;
    }
    attr = 0x2D9;
    for (i = 0; i < 9; i++) {
        if (i == 0) {
            object->model[i] = Hu3DModelRead(0x530009, attr);
            object->trans.x = m250_targetTbl[i].pos.x;
            object->trans.y = m250_targetTbl[i].pos.y;
            object->trans.z = m250_targetTbl[i].pos.z + 10.0;
            object->scale.x = object->scale.z = 0.66f;
            object->scale.y = 0.63f;
        } else {
            object->model[i] = Hu3DModelLink(object->model[0]);
            Hu3DModelPosSet(object->model[i], m250_targetTbl[i].pos.x, m250_targetTbl[i].pos.y,
                            m250_targetTbl[i].pos.z + 10.0);
        }
        Hu3DModelScaleSet(object->model[i], object->scale.x, object->scale.y, object->scale.z);
        Hu3DMotionSpeedSet(object->model[i], 0.0f);
    }
    m250_sprAnimTbl[6] = m250_AnimDataRead(0x530007);
    m250_sprGrpTbl[2] = m250_SprGrpCreate(m250_sprAnimTbl[6], 2);
    HuSprAttrSet(m250_sprGrpTbl[2], 0, 0x1000);
    HuSprAttrSet(m250_sprGrpTbl[2], 1, 0x1000);
    HuSprColorTPLvlSet(m250_sprGrpTbl[2], 0, 0, 0, 0, 0xC2);
    HuSprColorTPLvlSet(m250_sprGrpTbl[2], 1, 0, 0, 0, 0xC2);
    HuSprPosSet(m250_sprGrpTbl[2], 0, 60, 48);
    HuSprPosSet(m250_sprGrpTbl[2], 1, 260, 48);
    m250_sprAnimTbl[11] =
        m250_AnimDataRead(characterSprites[PLAYER_WORK(mgPlayerObjTbl[0])->unk29] | 0x210000);
    m250_sprAnimTbl[12] =
        m250_AnimDataRead(characterSprites[PLAYER_WORK(mgPlayerObjTbl[1])->unk29] | 0x210000);
    m250_sprGrpTbl[6] = m250_SprGrpCreate(m250_sprAnimTbl[11], 2);
    HuSprGrpMemberSet(m250_sprGrpTbl[6], 1, m250_sprAnimTbl[12], 0);
    HuSprAttrSet(m250_sprGrpTbl[6], 0, 0x1000);
    HuSprAttrSet(m250_sprGrpTbl[6], 1, 0x1000);
    HuSprPosSet(m250_sprGrpTbl[6], 0, 36, 48);
    HuSprPosSet(m250_sprGrpTbl[6], 1, 236, 48);
    m250_sprAnimTbl[8] = m250_AnimDataRead(0x2D);
    m250_sprAnimTbl[9] = m250_AnimDataRead(0x2F);
    m250_sprGrpTbl[4] = m250_SprGrpCreate(m250_sprAnimTbl[8], 6);
    HuSprAttrSet(m250_sprGrpTbl[4], 0, 0x1000);
    HuSprAttrSet(m250_sprGrpTbl[4], 1, 0x1000);
    HuSprAttrSet(m250_sprGrpTbl[4], 2, 0x1000);
    HuSprAttrSet(m250_sprGrpTbl[4], 3, 0x1000);
    HuSprAttrSet(m250_sprGrpTbl[4], 4, 0x1000);
    HuSprAttrSet(m250_sprGrpTbl[4], 5, 0x1000);
    HuSprPosSet(m250_sprGrpTbl[4], 0, 80, 48);
    HuSprPosSet(m250_sprGrpTbl[4], 1, 67, 48);
    HuSprPosSet(m250_sprGrpTbl[4], 2, 53, 48);
    HuSprPosSet(m250_sprGrpTbl[4], 3, 280, 48);
    HuSprPosSet(m250_sprGrpTbl[4], 4, 267, 48);
    HuSprPosSet(m250_sprGrpTbl[4], 5, 253, 48);
    object->func = m250_StageObjMain;
}

u8 m250_PenaltyCreate(s16 x, s16 y) {
    u8 group = HuSprGrpCreate(3, 2);

    HuSprGrpMemberSet(group, 0, m250_sprAnimTbl[8], 0);
    HuSprGrpMemberSet(group, 1, m250_sprAnimTbl[8], 0);
    HuSprGrpMemberSet(group, 2, m250_sprAnimTbl[9], 0);
    HuSprAttrSet(group, 0, 0x1000);
    HuSprAttrSet(group, 1, 0x1000);
    HuSprAttrSet(group, 2, 0x1000);
    HuSprAnimModeSet(group, 0, HUSPR_ANIM_MODE_STOP);
    HuSprAnimModeSet(group, 1, HUSPR_ANIM_MODE_STOP);
    HuSprAnimModeSet(group, 2, HUSPR_ANIM_MODE_STOP);
    HuSprPosSet(group, 0, x, y);
    HuSprPosSet(group, 1, 12, 0);
    HuSprPosSet(group, 2, -12, 0);
    HuSprPatNoSet(group, 0, 1);
    HuSprPatNoSet(group, 1, 0);
    HuSprPatNoSet(group, 2, 4);
    return group;
}

void m250_StageObjMain(omObjData *object) {
    s32 i;

    switch (m250_phase) {
        case 0:
            Hu3DHookFuncCreate(0xC0, m250_BillboardDraw, 2);
            GMesCreate(GMES_MES_MG_START);
            m250_timer = 900;
            m250_phase++;
        case 1:
            if (WipeStatGet() == 0 && ++m250_musicTimer == 1) {
                HuAudSeqPlay(0x36);
            }
            if (GMesStatGet() == 0) {
                m250_phase++;
                GMesCreate(GMES_MES_TIMER, (m250_timer + 29) / 30, 0xA0, 0x20);
                HuAudFXPlay(0xE);
            }
            break;
        case 2:
            m250_timer--;
            GMesTimerValueSet((m250_timer + 29) / 30);
            if (m250_timer == 0) {
                m250_phase = 3;
                GMesTimerEnd();
                GMesCreate(GMES_MES_MG_FINISH);
                HuAudSeqFadeOut(0x78);
            }
            break;
        case 3:
            if (m250_finishPanTimer != 0) {
                m250_finishPanTimer--;
                Center.y -= 2.9;
                HuSprPosSet(m250_sprGrpTbl[0], 0, 160, m250_finishPanTimer + 95);
                break;
            }
            if (m250_shotCnt != 0) {
                break;
            }
            if (m250_scoreTbl[0] > m250_scoreTbl[1]) {
                m250_winner = 0;
                PLAYER_WORK(mgPlayerObjTbl[0])->unk2C = 1;
                PLAYER_WORK(mgPlayerObjTbl[1])->unk2C = 0;
            } else if (m250_scoreTbl[0] < m250_scoreTbl[1]) {
                m250_winner = 1;
                PLAYER_WORK(mgPlayerObjTbl[0])->unk2C = 0;
                PLAYER_WORK(mgPlayerObjTbl[1])->unk2C = 1;
            } else {
                m250_winner = -1;
                PLAYER_WORK(mgPlayerObjTbl[0])->unk2C = PLAYER_WORK(mgPlayerObjTbl[1])->unk2C = 0;
            }
            m250_waitTimer = 15;
            m250_phase++;
            break;
        case 4:
            if (GMesStatGet() != 0) {
                break;
            }
            if (--m250_waitTimer == 0) {
                if (m250_winner == -1) {
                    GMesCreate(GMES_MES_MG_DRAW);
                    HuAudSeqPlay(0x6C);
                } else {
                    GMesCreate(GMES_MES_MG_WINNER, PLAYER_WORK(mgPlayerObjTbl[m250_winner])->unk29);
                    HuAudSeqPlay(0x67);
                }
                m250_waitTimer = 15;
                m250_phase++;
            }
            break;
        case 5:
            if (GMesStatGet() != 0) {
                break;
            }
            if (--m250_waitTimer == 0) {
                m250_phase++;
            }
            break;
        case 6:
            if (m250_waitTimer != 0) {
                if (--m250_waitTimer == 0) {
                    m250_phase++;
                }
            } else {
                m250_waitTimer = 16;
                WipeCreateOut(WIPE_TYPE_NORMAL, m250_waitTimer);
                HuAudSeqFadeOut(m250_waitTimer);
                HuAudFXAllFadeOut((s16)m250_waitTimer);
            }
            break;
        case 7:
            HuAudSeqStop();
            omOvlReturnEx(1);
            m250_BillboardClose();
            break;
    }
    m250_ShotTargetUpdate(object);
    for (i = 0; i < 2; i++) {
        HuSprDispOn(m250_sprGrpTbl[4], i * 3 + 1);
        HuSprDispOn(m250_sprGrpTbl[4], i * 3 + 2);
        HuSprPatNoSet(m250_sprGrpTbl[4], i * 3, m250_scoreTbl[i] % 10);
        HuSprPatNoSet(m250_sprGrpTbl[4], i * 3 + 1, m250_scoreTbl[i] / 10 % 10);
        HuSprPatNoSet(m250_sprGrpTbl[4], i * 3 + 2, m250_scoreTbl[i] / 100);
    }
    if (omSysExitReq == 1 && WipeStatGet() == 0) {
        m250_phase = 6;
    }
}

void m250_ShotTargetUpdate(omObjData *object) {
    PopgunPickoffShot *shot;
    PopgunPickoffTarget *target;
    s16 effect;
    f32 scale;
    s32 count;
    s32 index;
    s32 i;

    m250_shotCnt = 0;
    for (i = 0; i < 0x80; i++) {
        shot = &m250_shotTbl[i];
        switch (shot->active) {
            case 0:
                continue;
            case 1:
                target = &m250_targetTbl[shot->target];
                if (m250_DistCalc(&target->pos, &shot->pos) <= 48.0) {
                    shot->pos.x = target->pos.x;
                    shot->pos.y = target->pos.y;
                    shot->pos.z = target->pos.z + 40.0;
                    shot->vel.x = shot->vel.x * 0.2 +
                                  (f32)(m250_Rand16Get() - 0x8000) * 3.0517578125e-05 * (shot->vel.x * 0.2);
                    shot->vel.y = (f32)m250_Rand16Get() * 1.52587890625e-05 * 6.0 + 15.0;
                    shot->vel.z = -shot->vel.z * 0.1 -
                                  (f32)m250_Rand16Get() * 1.52587890625e-05 * (shot->vel.z * 0.05);
                    shot->unk1B = 120;
                    shot->active++;
                    if (target->unk1B == 2) {
                        target->unk0C = -50.0f;
                        m250_BillboardPatSet(target->playerId, target->unk1A * 2 + 1);
                        if (target->unk1A == 0) {
                            m250_BillboardColorSet(target->playerId, -1, -1, -1, 0x100);
                            if (target->unk16 != 0) {
                                target->unk16--;
                            }
                            m250_scoreTbl[shot->unk1A]++;
                            effect = m250_BillboardCreate(m250_sprAnimTbl[10], 0x60001808);
                            m250_BillboardPosSet(effect, target->pos.x, target->pos.y, target->pos.z + 20.0f);
                            m250_BillboardColorSet(target->playerId, -1, -1, -1, 0xC6);
                            m250_BillboardScaleSet(effect, 2.0f, 2.0f, 1.0f);
                            HuAudFXPlay(0x497);
                        } else {
                            if (m250_scoreTbl[shot->unk1A] > 10) {
                                m250_scoreTbl[shot->unk1A] -= 10;
                            } else {
                                m250_scoreTbl[shot->unk1A] = 0;
                            }
                            target->unk14 = m250_PenaltyCreate(target->screenX, target->screenY);
                            m250_BillboardColorSet(target->playerId, -1, 0, 0, 0x100);
                            HuAudFXPlay(0x498);
                            omVibrate(PLAYER_WORK(mgPlayerObjTbl[shot->unk1A])->unk28, 10, 0, 10);
                            target->unk16 = 0;
                            target->unk1B++;
                        }
                    }
                }
                m250_shotCnt++;
                break;
            case 2:
                if (--shot->unk1B == 0) {
                    shot->active++;
                }
                break;
            case 3:
                shot->active = 0;
                m250_BillboardKill(shot->playerId);
                shot->playerId = 0xFF;
                continue;
        }
        shot->vel.y += -2.0f;
        shot->pos.x += shot->vel.x;
        shot->pos.y += shot->vel.y;
        shot->pos.z += shot->vel.z;
        m250_BillboardPosSet(shot->playerId, shot->pos.x, shot->pos.y, shot->pos.z);
        scale = 1.5 - shot->pos.z / -400.0f;
        m250_BillboardScaleSet(shot->playerId, scale, scale, 1.0f);
    }
    for (i = 0; i < 9; i++) {
        target = &m250_targetTbl[i];
        switch (target->unk1B) {
            case 0:
                break;
            case 1:
                m250_BillboardAttrReset(target->playerId, 0x8000);
                target->unk1B++;
                break;
            case 2:
                target->unk0C += 15.0;
                if (target->unk0C > 0.0) {
                    target->unk0C = 0.0f;
                    m250_BillboardPatSet(target->playerId, target->unk1A * 2);
                } else if (target->unk0C > -30.0) {
                    m250_BillboardColorSet(target->playerId, 0, 0, 0, 0x100);
                }
                if ((--target->unk1C == 0) | (target->unk16 == 0)) {
                    target->unk1B++;
                }
                break;
            case 3:
                m250_BillboardColorSet(target->playerId, 0, 0, 0, 0x100);
                if (target->unk0C <= -90.0) {
                    m250_BillboardAttrSet(target->playerId, 0x8000);
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
                    m250_BillboardAttrSet(target->playerId, 0x8000);
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
        m250_BillboardRotSet(target->playerId, target->unk0C, 0.0f, 0.0f);
    }
    if (m250_phase == 2 && --m250_spawnTimer == 0) {
        m250_spawnTimer = 120;
        count = ++m250_spawnCnt / 2 + 2;
        if (count >= 9) {
            count = 9;
        }
        for (i = 0; i < count;) {
            index = (f32)m250_Rand16Get() * 1.52587890625e-05 * 8.0;
            target = &m250_targetTbl[index];
            if (target->unk1B == 0) {
                target->unk1C = (s32)((f32)m250_Rand16Get() * 1.52587890625e-05 * 20.0) + 60;
                target->unk16 = 10;
                target->unk1B = 1;
                target->unk0C = -90.0f;
                target->unk14 = -1;
                if (i != 0) {
                    target->unk1A = m250_Rand16Get() & 1;
                } else {
                    target->unk1A = 0;
                }
                m250_BillboardPatSet(target->playerId, target->unk1A * 2);
                Hu3DMotionSpeedSet(object->model[index], 1.0f);
                i++;
                HuAudFXPlay(0x499);
            }
        }
    }
}

void m250_PlayerObjCreateAll(void) {
    s32 i;

    MgPlayerParamReset();
    m250_sprAnimTbl[2] = m250_AnimDataRead(0x530002);
    m250_sprAnimTbl[3] = m250_AnimDataRead(0x530003);
    m250_sprAnimTbl[10] = m250_AnimDataRead(0x530006);
    mgPlayerObjNum = 0;
    for (i = 0; i < 2; i++) {
        mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(2, 0xB, 0x32, -1, m250_PlayerObjInit);
    }
}

const PopgunPickoffCharColors m250_chrColorTbl = { {
    { 0xFF, 0x00, 0x00 },
    { 0x00, 0x40, 0xFF },
    { 0xFF, 0x80, 0xFF },
    { 0x00, 0xFF, 0x00 },
    { 0x80, 0x00, 0xFF },
    { 0xFF, 0x80, 0x80 },
    { 0x80, 0x80, 0x80 },
    { 0xFF, 0xFF, 0x00 },
} };

const PopgunPickoffCharMotions m250_chrAnimNoTbl = { { 0, 1, 2, 3, 4, 5, 6, 7 } };

void m250_PlayerObjInit(omObjData *object) {
    PopgunPickoffCharColors colors = m250_chrColorTbl;
    PopgunPickoffCharMotions motions = m250_chrAnimNoTbl;
    s32 anims[3][8] = {
        { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C },
        { 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0x1D },
        { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B },
    };
    MgPlayerWork *data;
    PopgunPickoffPlayerWork *work;
    s32 i;
    u8 player;
    s8 character;
    s32 model;
    s32 linkModel;

    for (i = 0; i < 4; i++) {
        if (m250_playerInitNo == GwPlayer[i].group) {
            break;
        }
    }
    player = i;
    character = GwPlayer[player].chr;
    model = omCharModelNoTbl[character][0];
    linkModel = omCharModelNoTbl[character][2];
    MgShadowAltSet(1);
    m250_PlayerCreate(object, model, linkModel, player, 0x2C9);
    data = object->data;
    object->trans.x = m250_playerPosTbl[m250_playerInitNo][0];
    object->trans.y = m250_playerPosTbl[m250_playerInitNo][1];
    object->trans.z = m250_playerPosTbl[m250_playerInitNo][2];
    object->rot.y = m250_playerRotTbl[m250_playerInitNo];
    data->unk3C = object->rot.y + 180.0;
    object->scale.x = object->scale.y = object->scale.z = data->unkAC;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y - 5.0, object->trans.z);
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);
    work = data->unk158;
    work->unk28 = i;
    work->unk29 = character;
    work->unk2A = m250_playerInitNo;
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
    work->unk2F = m250_SprGrpCreate(m250_sprAnimTbl[2], 1);
    HuSprAttrSet(work->unk2F, 0, 0x9008);
    HuSprColorTPLvlSet(work->unk2F, 0, colors.rgb[character][0], colors.rgb[character][1],
                       colors.rgb[character][2], 0x100);
    work->unk33 = CharAnimCreate(object->model[0], 2, motions.values[character], model | anims[2][character]);
    work->unk31 = Hu3DAnimDataRead(model | anims[0][character]);
    work->unk32 = Hu3DAnimDataRead(model | anims[1][character]);
    Hu3DModelDynamicFree(object->model[0]);
    if (m250_playerInitNo == 0) {
        object->model[2] = Hu3DModelRead(0x530008, 0x2C9);
    } else {
        object->model[2] = Hu3DModelRead(0x530008, 0x2C9);
        HuSprZRotSet(work->unk2F, 0, 45.0f);
    }
    Hu3DModelHookSet(object->model[2], object->model[0], "item_hook");
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_HOOK, HU3D_ATTR_HOOK);
    object->func = m250_PlayerObjMain;
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(character, 0x4B), 1, 0);
    MgPlayerMotLoad(object, 0x26, CharMotionDataNumGet(character, 0x4C), 2, 0);
    MgPlayerMotLoad(object, 0x27, CharMotionDataNumGet(character, 0x4D), 0, 0);
    MgPlayerMotLoad(object, 0xD, CharMotionDataNumGet(character, 0x2F), 2, 0x78);
    MgPlayerMotLoad(object, 0xE, CharMotionDataNumGet(character, 0x36), 2, 0x78);
    MgPlayerMotSet(object, 0);
    m250_playerInitNo++;
}

void m250_PlayerCreate(omObjData *object, s32 arg1, s32 arg2, u16 player, u16 tag) {
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
    data->unk158 = HuMemAllocTag(sizeof(PopgunPickoffPlayerWork), TAG_OVERLAY);
    memset(data->unk158, 0, sizeof(PopgunPickoffPlayerWork));

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

void m250_PlayerObjMain(omObjData *object) {
    PopgunPickoffCharMotions motions = m250_chrAnimNoTbl;
    s32 unused[4]; // Unreferenced, but present in the stack frame.
    MgPlayerWork *data;
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
    MgPlayerMotStatGet(object);
    switch (m250_phase) {
        case 0:
            MgPlayerMotSet(object, 0x26);
            break;
        case 1:
            work->unk30 = 0xFF;
            break;
        case 2:
            if (!work->unk2D) {
                stickX = HuPadStkX[(s8)pad];
                stickY = HuPadStkY[(s8)pad];
                input = HuPadBtnDown[(s8)pad];
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
                input = m250_PlayerComInput(object);
                target = work->unk34;
            }
            HuSprDispOn(work->unk2F, 0);
            HuSprPosSet(work->unk2F, 0, m250_targetTbl[target].screenX,
                        m250_targetTbl[target].screenY);
            rotX = m250_aimRotXTbl[target / 3];
            rot = m250_aimRotYTbl[work->unk2A][target % 3];
            break;
        case 3:
            HuSprDispOff(work->unk2F, 0);
            MgPlayerMotSet(object, 0);
        case 4:
            MgPlayerMotSet(object, 0);
            Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
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
                MgPlayerMotSet(object, 0xD);
                HuAudCharVoicePlayPlayer(work->unk24, -1, work->unk2A);
                CharAnimSet(object->model[0], 2, motions.values[work->unk29], work->unk31);
            } else {
                MgPlayerMotSet(object, 0xE);
                CharAnimSet(object->model[0], 2, motions.values[work->unk29], work->unk32);
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
    if (input & A_BUTTON) {
        if (m250_ShotCreate(object, target) != 0) {
            _HuAudPlayerFXPlay(0x496, data->unk59);
            Hu3DMotionTimeSet(object->model[0], 0.0f);
            MgPlayerMotForceSet(object, 0x27);
        }
    }
    data->unk3C = rot;
    object->rot.y = rot + 180.0;
    object->rot.x = rotX;
    MgPlayerMotUpdate(object);
}

u16 m250_PlayerComInput(omObjData *object) {
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
                target = &m250_targetTbl[i];
                if (target->unk1B != 0) {
                    candidates[count] = i;
                    count++;
                }
            }
            if (count != 0) {
                work->unk34 = candidates[m250_Rand16Get() % count];
                work->unk2E++;
            }
            break;
        case 1:
            target = &m250_targetTbl[work->unk34];
            if (target->unk1A != 0 && m250_Rand16Get() % (work->unk2B + 2) != 0) {
                work->unk2E = 0;
                break;
            }
            if (m250_Rand16Get() % (8 - work->unk2B) == 0) {
                input = A_BUTTON;
            }
            if (target->unk1B != 2 && m250_Rand16Get() % (work->unk2B + 2) != 0) {
                work->unk2E = 0;
            }
            break;
    }
    return input;
}

u8 m250_ShotCreate(omObjData *object, s32 targetIndex) {
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
    target = &m250_targetTbl[targetIndex];
    for (i = 0; i < 0x80; i++) {
        if (m250_shotTbl[i].active == 0) {
            break;
        }
    }
    if (i == 0x80) {
        return 0;
    }
    shot = &m250_shotTbl[i];
    m250_HookPosGet(object->model[0], "item_hook", Hu3DData[object->model[0]].motTime, &pos);
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
    shot->playerId = m250_BillboardCreate(m250_sprAnimTbl[3], 0x10001808);
    m250_BillboardPatSet(shot->playerId, work->unk29);
    m250_BillboardScaleSet(shot->playerId, 1.8f, 1.8f, 1.0f);
    return 1;
}

s16 m250_EffSprCreate(s16 spriteId, s16 x, s16 y, f32 rot) {
    s16 group; // Never assigned; the original passes an uninitialized value.
    s32 i;

    if (spriteId == -1) {
        return -1;
    }
    for (i = 0; i < 16; i++) {
        if (m250_effSprUsedTbl[i] == 0) {
            break;
        }
    }
    if (i >= 16) {
        return -1;
    }
    m250_effSprUsedTbl[i] = 1;
    HuSprGrpMemberSet(group, i, spriteId, 0);
    HuSprAnimModeSet(group, i, HUSPR_ANIM_MODE_PAT_LOOP);
    HuSprPosSet(group, i, x, y);
    HuSprZRotSet(group, i, rot);
    HuSprDispOn(group, i);
    return i;
}

s32 m250_Rand16Get(void) {
    m250_randSeed = m250_randSeed * 0x41C64E6D + 0x3039;
    m250_randSeed += rand8();
    return m250_randSeed >> 16;
}

f32 m250_AngleCalc(f32 y, f32 x) {
    f32 fullCircle = 360.0f;
    f32 angle = atan2df(x, y) * 57.29577951308232;

    if (angle < 0.0f) {
        angle += fullCircle;
    } else if (angle >= fullCircle) {
        angle -= fullCircle;
    }
    return angle;
}

f32 m250_DistCalc(Vec *arg0, Vec *arg1) {
    return sqrtf(((arg0->x - arg1->x) * (arg0->x - arg1->x)) +
                 ((arg0->y - arg1->y) * (arg0->y - arg1->y)) +
                 ((arg0->z - arg1->z) * (arg0->z - arg1->z)));
}

void m250_DirRotCalc(Vec *dir, f32 *rot) {
    *rot++ = m250_AngleCalc(sqrtf(dir->x * dir->x + dir->z * dir->z), -dir->y);
    *rot++ = m250_AngleCalc(dir->z, dir->x);
    *rot = 0.0f;
}

void m250_HookPosGet(s16 model, char *hook, s16 time, Vec *pos) {
    HuMtx4F transform;
    HuMtx4F result;
    HuMtx4F hookTransform;
    HmfModel *modelData;

    Hu3DModelObjMtxFrameGet(model, time, hook, &hookTransform);
    modelData = &Hu3DData[model];
    HuTranslateF(transform, modelData->pos.x, modelData->pos.y, modelData->pos.z);
    mtxRotCat(transform, modelData->rot.x, modelData->rot.y, modelData->rot.z);
    mtxScaleCat(transform, modelData->scale.x, modelData->scale.y, modelData->scale.z);
    mtxCat(hookTransform, transform, result);
    pos->x = result[0][0] + result[1][0] + result[2][0] + result[3][0];
    pos->y = result[0][1] + result[1][1] + result[2][1] + result[3][1];
    pos->z = result[0][2] + result[1][2] + result[2][2] + result[3][2];
}

s16 m250_AnimDataRead(s32 dataNum) {
    void *data;
    s16 spriteId;

    data = DataRead(dataNum);
    spriteId = HuSprAnimRead(data);
    DataClose(data);
    return spriteId;
}

s16 m250_SprGrpCreate(s16 spriteId, s16 count) {
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

HuSprAnimPat *m250_SprAnimPatGet(s16 groupId, s16 member) {
    return &HuSprAnimDataGet(groupId)->pat[member];
}

void m250_BillboardInit(u16 count) {
    PopgunPickoffBillboard *player;
    s16 i;

    m250_billboardNum = count;
    m250_billboardTbl = HuMemAlloc(count * sizeof(PopgunPickoffBillboard));
    for (i = 0; i < 3; i++) {
        m250_billboardBufTbl[i] = NULL;
    }
    for (i = 0; i < m250_billboardNum; i++) {
        player = &m250_billboardTbl[i];
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

void m250_BillboardTileLoad(Gfx **gfx, HuSprAnimPat *cel, u8 fmt, u8 siz, u16 height, u16 uls,
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

s16 m250_BillboardGfxBuild(PopgunPickoffBillboard *player) {
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
            if (m250_tmemRowAltTbl[cel->sizeX >> m250_sizShiftTbl[siz]] >= rows ||
                rows == m250_tmemRowTbl[cel->sizeX >> m250_sizShiftTbl[siz]]) {
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
        m250_BillboardTileLoad(&gfx, &segCel, fmt, siz, rows, 0, 0, cel->sizeX - 1, cel->sizeY - 1, cms, cmt, masks,
                                     maskt, mode);
        gSPVertex(gfx++, (Vtx *)0x0E000000, 5, 0);
        gSP2Triangles(gfx++, 0, 2, 4, 0, 2, 3, 4, 0);
        gSP2Triangles(gfx++, 0, 4, 1, 0, 4, 3, 1, 0);
    } else {
        for (i = 0; i < count; i++) {
            m250_BillboardTileLoad(&gfx, &segCel, fmt, siz, rows, 0, i * rows, cel->sizeX - 1, (i + 1) * rows - 1,
                                         cms, cmt, masks, maskt, mode);
            gSPVertex(gfx++, (Vtx *)0x0E000000 + i * 2, 4, 0);
            gSP2Triangles(gfx++, 0, 2, 3, 0, 0, 3, 1, 0);
        }
        if (remainder != 0) {
            m250_BillboardTileLoad(&gfx, &segCel, fmt, siz, remainder, 0, i * rows, cel->sizeX - 1,
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

s16 m250_BillboardCreate(s16 spriteId, s32 flags) {
    PopgunPickoffBillboard *player;
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

    for (index = 0; index < m250_billboardNum; index++) {
        if (m250_billboardTbl[index].sprite == NULL) {
            break;
        }
    }
    if (index == m250_billboardNum) {
        return -1;
    }
    player = &m250_billboardTbl[index];
    player->sprite = HuSprAnimTbl[spriteId];
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
    if (!m250_BillboardGfxBuild(player)) {
        HuMemFree(player->vtx);
        index = -1;
    }
    return index;
}

void m250_BillboardSprSet(s16 index, s16 spriteId) {
    PopgunPickoffBillboard *player;
    HuSprAnimPat *cel;
    s32 siz;
    s32 fmt;
    s32 alignedWidth;
    u32 rows;
    u32 count;
    s32 remainder;
    u32 i;
    s32 j;

    player = &m250_billboardTbl[index];
    player->sprite = HuSprAnimTbl[spriteId];
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
    m250_BillboardGfxBuild(player);
}

void m250_BillboardSprReplace(s16 playerId, s16 spriteId) {
    PopgunPickoffBillboard *player;

    if (playerId != -1) {
        player = m250_billboardTbl + playerId;
        player->sprite = HuSprAnimTbl[spriteId];
        player->unk_1F = 0xFF;
        player->unk_1E = 0xFF;
        player->unk_1D = 0xFF;
        player->unk_20 = 0xFF;
        player->unk_2C = 0;
        player->unk_24 = 0;
        player->unk_30.x = 1.0f;
    }
}

void m250_BillboardPatSet(s16 playerId, s16 value) {
    PopgunPickoffBillboard *player;

    if (playerId != -1) {
        player = m250_billboardTbl + playerId;
        player->unk_24 = value;
        player->unk_2C = 0;
    }
}

void m250_BillboardAnimSpeedSet(s16 playerId, f32 value) {
    PopgunPickoffBillboard *player;

    if (playerId != -1) {
        player = m250_billboardTbl + playerId;
        player->unk_30.x = value;
    }
}

void m250_BillboardCenterSet(s16 playerId, f32 x, f32 y, f32 z) {
    PopgunPickoffBillboard *player;

    if (playerId != -1) {
        player = m250_billboardTbl + playerId;
        player->unk_28 |= 0x4000000;
        player->unk_30.y = x;
        player->unk_30.z = y;
        player->unk_3C = z;
    }
}

void m250_BillboardCenterZSet(s16 playerId, f32 value) {
    PopgunPickoffBillboard *player;

    if (playerId != -1) {
        player = m250_billboardTbl + playerId;
        player->unk_3C = value;
    }
}

void m250_BillboardPosSet(s16 playerId, f32 x, f32 y, f32 z) {
    PopgunPickoffBillboard *player;

    if (playerId != -1) {
        player = m250_billboardTbl + playerId;
        player->unk_40.x = x;
        player->unk_40.y = y;
        player->unk_40.z = z;
    }
}

void m250_BillboardPosAdd(s16 playerId, f32 x, f32 y, f32 z) {
    PopgunPickoffBillboard *player;

    if (playerId != -1) {
        player = m250_billboardTbl + playerId;
        player->unk_40.x += x;
        player->unk_40.y += y;
        player->unk_40.z += z;
    }
}

void m250_BillboardScaleSet(s16 playerId, f32 x, f32 y, f32 z) {
    PopgunPickoffBillboard *player;

    if (playerId != -1) {
        player = m250_billboardTbl + playerId;
        player->unk_4C.x = x;
        player->unk_4C.y = y;
        player->unk_4C.z = z;
    }
}

void m250_BillboardRotSet(s16 playerId, f32 x, f32 y, f32 z) {
    PopgunPickoffBillboard *player;

    if (playerId != -1) {
        player = m250_billboardTbl + playerId;
        player->unk_58.x = x;
        player->unk_58.y = y;
        player->unk_58.z = z;
    }
}

void m250_BillboardAttrSet(s16 playerId, s32 value) {
    PopgunPickoffBillboard *player;

    if (playerId != -1) {
        player = m250_billboardTbl + playerId;
        player->unk_28 |= value;
    }
}

void m250_BillboardAttrReset(s16 playerId, s32 value) {
    PopgunPickoffBillboard *player;

    if (playerId != -1) {
        player = m250_billboardTbl + playerId;
        player->unk_28 &= ~value;
    }
}

s32 m250_BillboardAttrGet(s16 playerId) {
    PopgunPickoffBillboard *player;
    s32 id = playerId;

    if (id != -1) {
        player = m250_billboardTbl + id;
        return player->unk_28;
    }
    return -1;
}

void m250_BillboardModeSet(s16 playerId, s8 value) {
    PopgunPickoffBillboard *player;

    if (playerId != -1) {
        player = m250_billboardTbl + playerId;
        player->unk_1A = value;
    }
}

PopgunPickoffBillboard *m250_BillboardGet(s16 playerId) {
    if (playerId == -1) {
        return NULL;
    }
    return m250_billboardTbl + playerId;
}

Vtx_t *m250_BillboardVtxGet(s16 playerId) {
    PopgunPickoffBillboard *player;
    s32 id = playerId;

    if (id == -1) {
        return NULL;
    }
    player = m250_billboardTbl + id;
    return player->vtx;
}

s32 m250_BillboardCenterVtxSet(s16 playerId, s16 x, s16 y) {
    PopgunPickoffBillboard *player;
    Vtx_t *vtx;

    if (playerId == -1) {
        return 0;
    }
    player = m250_billboardTbl + playerId;
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

void m250_BillboardColorSet(s16 playerId, s8 value1, s8 value2, s8 value3, s16 value4) {
    PopgunPickoffBillboard *player;

    if (playerId != -1) {
        player = m250_billboardTbl + playerId;
        player->unk_1D = value1;
        player->unk_1E = value2;
        player->unk_1F = value3;
        player->unk_20 = value4;
    }
}

void m250_BillboardKill(s16 index) {
    PopgunPickoffBillboard *player;

    if (index != -1) {
        player = &m250_billboardTbl[index];
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

void m250_BillboardDarkSet(s32 playerId, s32 flag) {
    PopgunPickoffBillboard *player = m250_billboardTbl + playerId;
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

void m250_BillboardFlipXSet(s32 index, s32 flip) {
    PopgunPickoffBillboard *player = &m250_billboardTbl[index];
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

void m250_BillboardFlipYSet(s32 index, s32 flip) {
    PopgunPickoffBillboard *player = &m250_billboardTbl[index];
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

void m250_BillboardHookSet(s16 playerId, void (*callback)(PopgunPickoffBillboard *)) {
    PopgunPickoffBillboard *player;

    if (playerId != -1) {
        player = m250_billboardTbl + playerId;
        player->callback = callback;
    }
}

void m250_BillboardTileSet(s16 index, s8 arg1, s8 arg2, s32 flags) {
    PopgunPickoffBillboard *player;

    if (index != -1) {
        player = &m250_billboardTbl[index];
        player->unk_1B = arg1;
        player->unk_1C = arg2;
        player->unk_28 |= flags;
        HuMemFree(player->displayList);
        m250_BillboardGfxBuild(player);
    }
}

void m250_BillboardTintSet(s16 index, s32 flag) {
    PopgunPickoffBillboard *player;
    s8 color;
    s8 blue;
    s32 i;

    if (index != -1) {
        player = &m250_billboardTbl[index];
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

void m250_BillboardBufAlloc(void) {
    PopgunPickoffBillboard *player;
    s32 i;

    if (++m250_billboardBufNo >= 3) {
        m250_billboardBufNo = 0;
    }
    m250_billboardBufSize = 0;
    for (i = 0; i < m250_billboardNum; i++) {
        player = &m250_billboardTbl[i];
        if (player->sprite != NULL) {
            m250_billboardBufSize += 0x40 + (player->unk_22 * sizeof(Gfx) + player->unk_18 * 2 * sizeof(Vtx));
        }
    }
    if (m250_billboardBufTbl[m250_billboardBufNo] != NULL) {
        HuMemFree(m250_billboardBufTbl[m250_billboardBufNo]);
    }
    if (m250_billboardBufSize != 0) {
        m250_billboardBufTbl[m250_billboardBufNo] = HuMemAlloc(m250_billboardBufSize);
    } else {
        m250_billboardBufTbl[m250_billboardBufNo] = NULL;
    }
    m250_billboardBufCur = m250_billboardBufTbl[m250_billboardBufNo];
}

void m250_BillboardSort(HuCamera *camera, HuMtx4F lookAt) {
    PopgunPickoffBillboard tailOpaque;
    PopgunPickoffBillboard tailTranslucent;
    HuMtx4F unused[16]; // Unreferenced, but present in the stack frame.
    HuMtx4F mtx;
    PopgunPickoffBillboard *player;
    PopgunPickoffBillboard *node;
    f32 minX;
    f32 maxX;
    f32 minZ;
    f32 maxZ;
    s32 i;

    minX = camera->at.x - 640.0;
    maxX = camera->at.x + 640.0;
    minZ = camera->at.z - 640.0;
    maxZ = camera->at.z + 640.0;
    m250_billboardOpaHead.unk_64 = 0.0f;
    m250_billboardXluHead.unk_64 = 99999.9f;
    tailOpaque.unk_64 = -99999.9f;
    tailTranslucent.unk_64 = 0.0f;
    m250_billboardXluHead.prev = NULL;
    m250_billboardOpaHead.prev = NULL;
    m250_billboardOpaHead.next = &tailOpaque;
    m250_billboardXluHead.next = &tailTranslucent;
    tailOpaque.prev = &m250_billboardOpaHead;
    tailTranslucent.prev = &m250_billboardXluHead;
    tailTranslucent.next = NULL;
    tailOpaque.next = NULL;
    for (i = 0; i < m250_billboardNum; i++) {
        player = &m250_billboardTbl[i];
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
            node = &m250_billboardXluHead;
        } else {
            node = &m250_billboardOpaHead;
        }
        for (node = node->next; node->unk_64 > player->unk_64; node = node->next) {}
        node->prev->next = player;
        player->prev = node->prev;
        player->next = node;
        node->prev = player;
    }
    tailOpaque.prev->next = tailTranslucent.prev->next = NULL;
}

void m250_BillboardDraw(Gfx **gfxP, s32 arg1, s32 arg2) {
    HuCamera *camera = (HuCamera *)arg2;
    Gfx *gfx = *gfxP;
    HuMtx4F unused1[2]; // Unreferenced, but present in the stack frame.
    HuMtx4F lookAt;
    HuMtx4F unused2[4]; // Unreferenced, but present in the stack frame.
    Vec rot;
    Vec dir;
    HuMtx4F unused3[32]; // Unreferenced, but present in the stack frame.
    PopgunPickoffBillboard *player;

    guLookAtF(lookAt, camera->pos.x, camera->pos.y, camera->pos.z, camera->at.x, camera->at.y, camera->at.z,
              camera->up.x, camera->up.y, camera->up.z);
    dir.x = camera->pos.x - camera->at.x;
    dir.y = camera->pos.y - camera->at.y;
    dir.z = camera->pos.z - camera->at.z;
    m250_DirRotCalc(&dir, (f32 *)&rot);
    m250_BillboardBufAlloc();
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_2CYCLE);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING | G_TEXTURE_GEN);
    gSPSetGeometryMode(gfx++, G_SHADE | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    m250_BillboardSort(camera, lookAt);
    for (player = m250_billboardOpaHead.next; player != NULL; player = player->next) {
        gfx = m250_BillboardEntryDraw(gfx, player, lookAt, &rot);
    }
    for (player = m250_billboardXluHead.next; player != NULL; player = player->next) {
        gfx = m250_BillboardEntryDraw(gfx, player, lookAt, &rot);
    }
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    *gfxP = gfx;
    if (!Hu3DPauseF) {
        m250_BillboardAnimUpdate();
    }
}

Gfx *m250_BillboardEntryDraw(Gfx *gfx, PopgunPickoffBillboard *player, HuMtx4F lookAt, Vec *rot) {
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
    gDPSetTextureFilter(gfx++, m250_texFilterTbl[(player->unk_28 >> 2) & 3]);
    gDPSetColorDither(gfx++, m250_colorDitherTbl[(player->unk_28 >> 4) & 3]);
    gDPSetAlphaCompare(gfx++, m250_alphaCompareTbl[(player->unk_28 >> 22) & 3]);
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
    vtx = m250_billboardBufCur;
    mtxL = (Mtx *)&vtx[player->unk_18 * 2];
    dl = (Gfx *)&mtxL[1];
    m250_billboardBufCur = &dl[player->unk_22];
    guMtxIdentF(billboard);
    if (player->unk_28 & 0x4000000) {
        billboard[3][0] = -player->unk_30.y;
        billboard[3][1] = player->unk_30.z;
    } else {
        billboard[3][0] = -(u16)cel->centerX;
        billboard[3][1] = (u16)cel->centerY;
    }
    billboard[3][2] = player->unk_3C;
    mtxCopy(mtx, lookAt);
    mtxTransCat(mtx, player->unk_40.x, player->unk_40.y, player->unk_40.z);
    mtxRotCat(mtx, player->unk_58.x, player->unk_58.y, player->unk_58.z);
    mtxScaleCat(mtx, player->unk_4C.x, player->unk_4C.y, player->unk_4C.z);
    switch (player->unk_1A) {
        case 1:
            HuMtxRotXF(mtx, rot->x);
            break;
        case 2:
            HuMtxRotYF(mtx, rot->y);
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
            HmfInverseMtxF3X3Cat(mtx, inverse);
            mtxCat(scale, inverse, mtx);
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

void m250_BillboardAnimUpdate(void) {
    PopgunPickoffBillboard *player;
    s32 frameCount;
    s32 i;

    for (i = 0; i < m250_billboardNum; i++) {
        player = &m250_billboardTbl[i];
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
                        m250_BillboardKill(i);
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

void m250_BillboardClose(void) {
    s32 i;

    for (i = 0; i < m250_billboardNum; i++) {
        m250_BillboardKill(i);
    }
    for (i = 0; i < 3; i++) {
        if (m250_billboardBufTbl[i] != NULL) {
            HuMemFree(m250_billboardBufTbl[i]);
        }
    }
    HuMemFree(m250_billboardTbl);
}
