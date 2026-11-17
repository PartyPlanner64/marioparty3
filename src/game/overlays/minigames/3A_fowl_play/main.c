#include "common.h"
#include "game/overlays/minigame.h"
#include "game/hmfmath.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"
#include "game/texload.h"

#define PLAYER_WORK(obj) ((FowlPlayerWork *)((MgPlayerWork *)(obj)->data)->unk158)

#define FOWL_CC_PRIM_DECALA 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0
#define FOWL_CC_PRIM_MODULATEA 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0
#define FOWL_CC_BLEND_DECALA 1, PRIMITIVE, TEXEL0, PRIMITIVE, 0, 0, 0, TEXEL0
#define FOWL_CC_BLEND_MODULATEA 1, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0
#define FOWL_CC_MODULATEI_PRIMA TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0
#define FOWL_CC_MODULATEI_PASSA2 COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED

typedef struct {
    /* 0x00 */ u8 unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05[0xAF];
} FowlPlayStageWork; // Size 0xB4

typedef struct {
    /* 0x00 */ Vec start;
    /* 0x0C */ Vec end;
} FowlWall; // Size 0x18

typedef struct {
    /* 0x00 */ s8 index;
    /* 0x01 */ u8 unk01;
    /* 0x04 */ Vec pos;
    /* 0x10 */ f32 unk10;
} FowlFeather; // Size 0x14

typedef struct {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ Vec unk18;
    /* 0x24 */ Vec unk24;
    /* 0x30 */ omObjData *target;
    /* 0x34 */ u8 unk34[4];
    /* 0x38 */ FowlFeather feathers[32];
} FowlPlayChickenWork; // Size 0x2B8

typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec prevPos;
    /* 0x18 */ u16 motStat;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8 player;
    /* 0x21 */ u8 index;
    /* 0x22 */ u8 character;
    /* 0x23 */ u8 unk23;
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 unk27;
    /* 0x28 */ char unk28[4];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ char unk38[4];
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ char unk40[0xC];
} FowlPlayerWork; // Size 0x4C

typedef struct {
    u8 values[8];
} FowlCharMotions;

typedef struct {
    /* 0x00 */ u8 index;
    /* 0x01 */ u8 unk01;
    /* 0x04 */ f32 zoom;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ Vec center;
    /* 0x18 */ Vec rot;
    /* 0x24 */ omObjData *player;
} FowlCameraWork; // Size 0x28

typedef struct FowlPlayBillboard {
    /* 0x00 */ Gfx *displayList;
    /* 0x04 */ Vtx_t *vtx;
    /* 0x08 */ HuSprAnimData *sprite;
    /* 0x0C */ struct FowlPlayBillboard *prev;
    /* 0x10 */ struct FowlPlayBillboard *next;
    /* 0x14 */ void (*callback)(struct FowlPlayBillboard *);
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
} FowlPlayBillboard; // sizeof 0x68

extern HuSprAnimData *HuSprAnimTbl[];
extern s32 omCharModelNoTbl[][6];

u8 m258_unusedF = 1; /* Unreferenced. */
s32 m258_phaseTimer = 0;
s32 m258_unusedNum = 0; /* Unreferenced. */
s32 m258_winner = -1;
s16 m258_unusedTime = 180; /* Unreferenced. */
s16 m258_musicTimer = 0;
FowlWall m258_wallTbl[8] = {
    { { -1250.0f, 0.0f, -200.0f }, { -800.0f, 0.0f, -200.0f } },
    { { -800.0f, 0.0f, -200.0f }, { -587.5f, 0.0f, 12.0f } },
    { { 200.0f, 0.0f, -1250.0f }, { 200.0f, 0.0f, -800.0f } },
    { { 200.0f, 0.0f, -800.0f }, { -12.0f, 0.0f, -587.5f } },
    { { 1250.0f, 0.0f, 200.0f }, { 800.0f, 0.0f, 200.0f } },
    { { 800.0f, 0.0f, 200.0f }, { 587.5f, 0.0f, -12.0f } },
    { { -200.0f, 0.0f, 1250.0f }, { -200.0f, 0.0f, 800.0f } },
    { { -200.0f, 0.0f, 800.0f }, { 12.0f, 0.0f, 587.5f } }
};
s16 m258_unusedNoTbl[4] = { 0, 1, 2, 3 }; /* Unreferenced. */
u8 m258_playerInitNo = 0;
s32 m258_playerInitNoPad = 0; /* Unreferenced. */
Vec m258_playerPosTbl[4] = {
    { 1000.0f, 0.0f, 0.0f },
    { -1000.0f, 0.0f, 0.0f },
    { 100.0f, 0.0f, 400.0f },
    { 300.0f, 0.0f, 400.0f }
};
f32 m258_playerRotTbl[4] = { -90.0f, 90.0f, 180.0f, 180.0f };
s32 m258_cluckTimer = 3;
u32 m258_randSeed = 0x41C64E6D;
s32 m258_sizShiftTbl[] = { 4, 3, 2, 1 };
s16 m258_tmemRowAltTbl[] = {
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
s16 m258_tmemRowTbl[] = {
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
s16 m258_colorDitherTbl[] = { G_CD_DISABLE, G_CD_NOISE, G_CD_BAYER, G_CD_MAGICSQ };
s16 m258_texFilterTbl[] = { G_TF_POINT, G_TF_POINT, G_TF_BILERP, G_TF_AVERAGE };
s16 m258_alphaCompareTbl[] = { G_AC_THRESHOLD, G_AC_NONE, G_AC_DITHER, G_AC_NONE };
s32 m258_billboardBufNo = 0;

s16 m258_bgSeNo BSS;
s16 m258_seFadeTimer BSS;
u8 m258_seFadeTimerPad[4] BSS; /* Unreferenced. */
MinigameFlow m258_mgFlow BSS;
s16 m258_sprAnimTbl[2] BSS;
s16 m258_featherSprAnim BSS;
s16 m258_featherSprAnimPad BSS; /* Unreferenced. */
s16 m258_dustSprAnim BSS;
u8 m258_dustSprAnimPad[4] BSS; /* Unreferenced. */
s16 m258_sprGrpTbl[40] BSS;
omObjData *m258_chickenObjTbl[1] BSS;
omObjData *m258_cameraObjTbl[2] BSS;
s16 m258_phase BSS;
s16 m258_timer BSS;
s16 m258_chickenNum BSS;
u8 m258_chickenNumPad[4] BSS; /* Unreferenced. */
f32 m258_viewMtx[4][4] BSS;
f32 m258_viewInvMtx[4][4] BSS;
f32 m258_fovTan BSS;
FowlPlayBillboard *m258_billboardTbl BSS;
void *m258_billboardBufTbl[6] BSS;
void *m258_billboardBufCur BSS;
s32 m258_billboardBufSize BSS;
s32 m258_billboardNum BSS;
u8 m258_billboardNumPad[0xC] BSS;  /* Unreferenced. */
FowlPlayBillboard m258_billboardOpaHead BSS;     // List head of opaque entries
FowlPlayBillboard m258_billboardXluHead BSS;     // List head of translucent entries
u8 m258_billboardXluHeadPad[0x10] BSS; /* Unreferenced. */

void m258_CameraViewInit(omObjData *object);
void m258_CameraObjMain(omObjData *object);
void m258_MtxInvert(HuMtx4F src, HuMtx4F dst);
void m258_StageObjCreate(void);
void m258_StageObjInit(omObjData *object);
void m258_StageObjMain(omObjData *object);
void m258_WallPush(omObjData *object, f32 radius);
u8 m258_WallCrossCheck(Vec *pos, Vec *prev, f32 radius);
void m258_PlayerObjCreateAll(void);
void m258_PlayerObjInit(omObjData *object);
void m258_PlayerObjMain(omObjData *object);
u16 m258_PlayerComInput(omObjData *object);
void m258_PlayerWorkGet(omObjData *object, MgPlayerWork **data, FowlPlayerWork **work);
void m258_ChickenObjCreate(void);
void m258_ChickenObjInit(omObjData *object);
void m258_ChickenObjMain(omObjData *object);
u8 m258_ChickenCatchCheck(omObjData *object, u8 canCatch);
s32 m258_Rand16Get(void);
f32 m258_AngleCalc(f32 y, f32 x);
f32 m258_DistXZCalc(Vec *arg0, Vec *arg1);
f32 m258_WallAvoidCalc(Vec *pos, f32 dist, f32 dir);
f32 m258_VecNormalize(Vec *vec);
f32 m258_SegmentDistCalc(Vec *point, Vec *start, Vec *end, Vec *closest);
f32 m258_LineCrossCalc(Vec *pos1, Vec *dir1, Vec *pos2, Vec *dir2);
void m258_HookPosGet(s16 model, char *hook, s16 time, Vec *pos);
s16 m258_AnimDataRead(s32 dataNum);
s16 m258_SprGrpCreate(s16 spriteId, s16 count);
void m258_BillboardInit(u16 count);
s16 m258_BillboardGfxBuild(FowlPlayBillboard *fowl);
s16 m258_BillboardCreate(s16 spriteId, s32 flags);
void m258_BillboardPatSet(s16 arg0, s16 arg1);
void m258_BillboardAnimSpeedSet(s16 arg0, f32 arg1);
void m258_BillboardPosSet(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void m258_BillboardScaleSet(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void m258_BillboardRotSet(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void m258_BillboardAttrSet(s16 arg0, s32 arg1);
void m258_BillboardAttrReset(s16 arg0, s32 arg1);
s32 m258_BillboardAttrGet(s16 arg0);
void m258_BillboardModeSet(s16 arg0, s8 arg1);
void m258_BillboardColorSet(s16 arg0, s8 arg1, s8 arg2, s8 arg3, s16 arg4);
void m258_BillboardKill(s16 index);
void m258_BillboardDraw(Gfx **gfxP, s32 arg1, s32 arg2);
Gfx *m258_BillboardEntryDraw(Gfx *gfx, FowlPlayBillboard *fowl, HuMtx4F lookAt, Vec *rot);
void m258_BillboardAnimUpdate(void);
void m258_BillboardClose(void);

void m258_ObjectSetup(void) {
    omObjData *obj;

    MapCollInit(1);
    Hu3DQuadPoolInit(&mgQuadPool, 0x40);
    omInitObjMan(0x14, 0);
    omGameSysInit();
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -56.0f, 50.0f, 56.0f);
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    obj->work[0] = 2;
    CamSetupInit(2);
    CamSetupMapCullAddMulti(2);
    ScissorSet(0, 0.0f, 0.0f, 160.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 45.0f, 80.0f, 8000.0f);
    ScissorSet(1, 160.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(1, 45.0f, 80.0f, 8000.0f);
    MgFieldStatClear();
    m258_CameraViewInit(obj);
    m258_BillboardInit(0x80);
    m258_StageObjCreate();
    memset(&m258_mgFlow, 0, sizeof(m258_mgFlow));
    m258_mgFlow.type = MINIGAME_BATTLE;
    MgFlowInit(&m258_mgFlow);
    m258_PlayerObjCreateAll();
    m258_chickenNum = 0;
    m258_ChickenObjCreate();
    Hu3DBGColorSet(0, 0, 0);
    WipeCreateIn(0xFF, 0x10);
}

void m258_CameraViewInit(omObjData *object) {
    HuCamera *camera;
    omObjData *obj;
    FowlCameraWork *work;
    f32 sinFov;
    f32 cosFov;
    s32 i;

    CZoom = 1000.0f;
    CRot.x = -15.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 160.0f;
    Center.z = 0.0f;
    omOutView(object);

    camera = gCameraList;
    sinFov = sindf(camera->fov / 2.0);
    cosFov = cosdf(camera->fov / 2.0);
    m258_fovTan = sinFov / cosFov;
    guMtxL2F(m258_viewMtx, &camera->mtxs[0].lookAtMtx);
    guMtxL2F(m258_viewInvMtx, &camera->mtxs[0].lookAtMtx);
    m258_MtxInvert(m258_viewInvMtx, m258_viewInvMtx);
    for (i = 0; i < 2; i++) {
        obj = m258_cameraObjTbl[i] = omAddObj(6, 1, 0, -1, m258_CameraObjMain);
        work = HuMemAllocTag(sizeof(FowlCameraWork), TAG_OVERLAY);
        obj->data = work;
        memset(work, 0, sizeof(FowlCameraWork));
        work->index = i;
        work->unk08 = 0.0f;
        work->unk01 = 2;
        work->center.x = CenterM[i].x = Center.x;
        work->center.y = CenterM[i].y = Center.y;
        work->center.z = CenterM[i].z = Center.z;
        work->rot.x = CRotM[i].x = CRot.x;
        work->rot.y = CRotM[i].y = 90.0 - i * 180.0;
        work->rot.z = CRotM[i].z = CRot.z;
        work->zoom = CZoomM[i] = CZoom;
    }
}

void m258_CameraObjMain(omObjData *object) {
    FowlCameraWork *work;
    MgPlayerWork *data;
    FowlPlayerWork *playerWork;
    HuMtx4F unusedMtx; // Unreferenced, but present in the stack frame.
    Vec unusedVec;     // Unreferenced, but present in the stack frame.
    HuCamera *camera;
    f32 playerRot;
    f32 diff;
    u8 index;

    if (m258_phase >= 8) {
        if (object->data != NULL) {
            HuMemFree(object->data);
            object->data = NULL;
        }
        return;
    }
    work = object->data;
    if (work->player == NULL) {
        return;
    }
    m258_PlayerWorkGet(work->player, &data, &playerWork);
    playerRot = data->unk3C;
    index = work->index;
    camera = &gCameraList[index];
    if (playerWork->unk24) {
        work->unk08 = 0.25f;
        work->rot.y = playerRot;
    } else if (data->unk40 >= 0.1) {
        if (work->unk08 < 20.0) {
            work->unk08 += 0.25;
        }
        work->rot.y =
            m258_AngleCalc(camera->pos.x - work->player->trans.x, camera->pos.z - work->player->trans.z);
        work->unk01 = 5;
    } else if (--work->unk01 == 0) {
        work->unk08 = 0.25f;
        work->rot.y = playerRot + 180.0;
    }
    while (work->rot.y < 0.0) {
        work->rot.y += 360.0;
    }
    while (work->rot.y > 360.0) {
        work->rot.y -= 360.0;
    }
    CZoomM[index] = work->zoom;
    CRotM[index].x = work->rot.x;
    diff = CRotM[index].y - work->rot.y;
    while (diff < -180.0) {
        diff += 360.0;
    }
    while (diff > 180.0) {
        diff -= 360.0;
    }
    if (playerWork->unk24) {
        if (fabs(diff) < 5.0) {
            work->unk08 = 0.5f;
        } else {
            work->unk08 = fabs(diff) * 0.1;
        }
    } else if (data->unk40 <= 0.1) {
        if (fabs(diff) < 5.0) {
            work->unk08 = 0.25f;
        } else {
            work->unk08 = fabs(diff) * 0.05;
        }
    }
    if (diff > work->unk08) {
        CRotM[index].y -= work->unk08;
    } else if (diff < -work->unk08) {
        CRotM[index].y += work->unk08;
    } else {
        CRotM[index].y = work->rot.y;
    }
    while (CRotM[index].y < 0.0) {
        CRotM[index].y += 360.0;
    }
    while (CRotM[index].y > 360.0) {
        CRotM[index].y -= 360.0;
    }
    work->center.x = work->player->trans.x - sindf(CRotM[index].y) * 200.0;
    work->center.z = work->player->trans.z - cosdf(CRotM[index].y) * 200.0;
    CenterM[index].x = work->center.x;
    CenterM[index].z = work->center.z;
}

void m258_MtxVecMul(HuMtx4F mtx, f32 x, f32 y, f32 z, f32 *dst) {
    dst[0] = ((x * mtx[0][0]) + (y * mtx[1][0])) + (z * mtx[2][0]);
    dst[1] = ((x * mtx[0][1]) + (y * mtx[1][1])) + (z * mtx[2][1]);
    dst[2] = ((x * mtx[0][2]) + (y * mtx[1][2])) + (z * mtx[2][2]);
}

void m258_MtxInvert(HuMtx4F src, HuMtx4F dst) {
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

        m258_MtxVecMul(dst, -mtx[3][0], -mtx[3][1], -mtx[3][2], dstRow3);
    }
}

void m258_ScreenPosCalc(f32 *pos, f32 *dst) {
    f32 mtx[4][4];
    f32 depth;
    f32 scale;

    guTranslateF(mtx, pos[0], pos[1], pos[2]);
    guMtxCatF(mtx, m258_viewMtx, mtx);
    depth = mtx[3][2] * m258_fovTan;
    scale = fabsf(depth);
    if (scale != 0.0) {
        dst[0] = mtx[3][0] * 160.0f / scale / 1.3333334f;
        dst[1] = -mtx[3][1] * 120.0f / scale;
    }
    dst[0] += 160.0;
    dst[1] += 120.0;
    dst[2] = scale;
}

void m258_WorldPosCalc(f32 x, f32 y, f32 z, f32 *dst) {
    f32 depth = z + m258_viewMtx[3][2];
    f32 scale = fabsf(depth * m258_fovTan);
    f32 mtx[4][4];

    guTranslateF(mtx, (x + x) * scale * 1.3333334f / 320.0f, -((y + y) * scale / 240.0f), depth);
    guMtxCatF(mtx, m258_viewInvMtx, mtx);
    dst[0] = mtx[3][0];
    dst[1] = mtx[3][1];
    dst[2] = mtx[3][2];
}

void m258_StageObjCreate(void) {
    mgMapObjNum = 0;
    MgMapBaseSet(0);
    mgMapObjTbl[mgMapObjNum++] = omAddObj(5, 1, 0, -1, m258_StageObjInit);
    m258_phase = 0;
}

void m258_StageObjInit(omObjData *object) {
    Vec unused[16] = { { -500.0f, 0.0f, -1550.0f }, { -1050.0f, 0.0f, -1450.0f }, { -300.0f, 0.0f, -2245.0f }, { -1400.0f, 0.0f, -600.0f }, { -1700.0f, 0.0f, 400.0f }, { -1550.0f, 0.0f, 800.0f }, { -400.0f, 0.0f, 2150.0f }, { -1300.0f, 0.0f, 1450.0f }, { 750.0f, 0.0f, 1650.0f }, { 1450.0f, 0.0f, 1600.0f }, { 450.0f, 0.0f, 2150.0f }, { 1550.0f, 0.0f, 800.0f }, { 2000.0f, 0.0f, 500.0f }, { 1550.0f, 0.0f, -800.0f }, { 400.0f, 0.0f, -2150.0f }, { 1150.0f, 0.0f, -1200.0f } };
    FowlPlayStageWork *work;

    work = HuMemAllocTag(sizeof(FowlPlayStageWork), TAG_OVERLAY);
    object->data = work;
    memset(work, 0, sizeof(FowlPlayStageWork));
    work->unk03 = 1;
    work->unk04 = 0;
    MgMapSlideSet(object, 20.0f);
    MgMapFrictionSet(object, 0.5f);
    MgMapAccelSet(object, 10.0f);
    MgMapCircleSet(object, 0.0f, 1200.0f);
    m258_sprAnimTbl[0] = m258_AnimDataRead(0x5B0000);
    m258_sprGrpTbl[0] = m258_SprGrpCreate(m258_sprAnimTbl[0], 2);
    HuSprPosSet(m258_sprGrpTbl[0], 0, 0, 0);
    HuSprAttrSet(m258_sprGrpTbl[0], 0, 0x44000);
    HuSprTexScaleSet(m258_sprGrpTbl[0], 0, 2.0f, 1.0f);
    HuSprTexMaskSet(m258_sprGrpTbl[0], 0, 8, 7);
    HuSprScissorSet(m258_sprGrpTbl[0], 0, 0, 0, 159, 240);
    HuSprPosSet(m258_sprGrpTbl[0], 1, 160, 0);
    HuSprAttrSet(m258_sprGrpTbl[0], 1, 0x44000);
    HuSprTexScaleSet(m258_sprGrpTbl[0], 1, 2.0f, 1.0f);
    HuSprTexMaskSet(m258_sprGrpTbl[0], 1, 8, 7);
    HuSprScissorSet(m258_sprGrpTbl[0], 1, 161, 0, 320, 240);
    m258_sprAnimTbl[1] = m258_AnimDataRead(0x5B0004);
    m258_sprGrpTbl[1] = m258_SprGrpCreate(m258_sprAnimTbl[1], 1);
    HuSprPosSet(m258_sprGrpTbl[1], 0, 160, 120);
    HuSprAttrSet(m258_sprGrpTbl[1], 0, 0x1000);
    object->model[0] = Hu3DModelRead(0x5B0005, 0x2D9);
    Hu3DModelCameraSet(object->model[0], 3);
    object->func = m258_StageObjMain;
}

void m258_StageObjMain(omObjData *object) {
    HuSprite *sprite;
    f32 x;
    s32 i;

    switch (m258_phase) {
        case 0:
            Hu3DModelCameraSet(Hu3DHookFuncCreate(0xC0, m258_BillboardDraw, 2), 3);
            GMesCreate(6);
            m258_bgSeNo = HuAudFXPlay(0x4BF);
            m258_timer = 1800;
            m258_phase++;
        case 1:
            if (WipeStatGet() == 0 && ++m258_musicTimer == 1) {
                HuAudSeqPlay(0x36);
            }
            if (GMesStatGet() == 0) {
                MgFlowStatSet(MG_STATE_PLAY);
                m258_phase++;
                GMesCreate(0x1A, (m258_timer + 29) / 30, 0xA0, 0x20);
                HuAudFXPlay(0xE);
            }
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                if (PLAYER_WORK(mgPlayerObjTbl[i])->unk24) {
                    m258_winner = i;
                    m258_phase = 3;
                }
            }
            m258_timer--;
            GMesTimerValueSet((m258_timer + 29) / 30);
            if (m258_timer == 0) {
                m258_phase = 3;
            }
            break;
        case 3:
            GMesTimerEnd();
            GMesCreate(0x11);
            HuAudSeqFadeOut(0x78);
            m258_phase = 6;
            m258_phaseTimer = 15;
            m258_seFadeTimer = 15;
            break;
        case 6:
            if (--m258_seFadeTimer == 0) {
                HuAudFXFadeOut(m258_bgSeNo, 15);
            }
            if (GMesStatGet() != 0) {
                break;
            }
            if (--m258_phaseTimer != 0) {
                break;
            }
            for (i = 0; i < 2; i++) {
                if (PLAYER_WORK(mgPlayerObjTbl[i])->unk24) {
                    m258_winner = i;
                }
            }
            if (m258_winner != -1) {
                GMesCreate(0x16, PLAYER_WORK(mgPlayerObjTbl[m258_winner])->character);
                HuAudSeqPlay(0x67);
            } else {
                GMesCreate(0x20);
                HuAudSeqPlay(0x6C);
            }
            m258_phaseTimer = 15;
            m258_phase++;
            MgFlowStatSet(MG_STATE_RESULT);
            break;
        case 7:
            if (GMesStatGet() != 0) {
                break;
            }
            if (--m258_phaseTimer == 0) {
                m258_phase++;
            }
            break;
        case 8:
            if (m258_phaseTimer != 0) {
                if (--m258_phaseTimer == 0) {
                    m258_phase++;
                }
            } else {
                MgFlowStatSet(MG_STATE_EXIT);
                m258_phaseTimer = 16;
                WipeCreateOut(WIPE_TYPE_NORMAL, m258_phaseTimer);
                HuAudSeqFadeOut(m258_phaseTimer);
                HuAudFXAllFadeOut((s16)m258_phaseTimer);
            }
            break;
        case 9:
            m258_BillboardClose();
            HuAudSeqStop();
            omOvlReturnEx(1);
            break;
    }
    for (i = 0; i < 2; i++) {
        sprite = HuSprGet(m258_sprGrpTbl[0], i);
        x = CRotM[i].y * 256.0 / 360.0 - 256.0 + i * 160;
        HuSprPosSet(m258_sprGrpTbl[0], i, x, 0);
        sprite->pos.x = x;
    }
    if (omSysExitReq == 1 && WipeStatGet() == 0) {
        m258_phase = 8;
    }
}

void m258_WallPush(omObjData *object, f32 radius) {
    Vec closest;
    Vec dir;
    s32 i;

    if (object->trans.y >= 30.0) {
        return;
    }
    radius += 20.0;
    if (object->trans.y > 20.0) {
        radius *= (30.0 - object->trans.y) / 10.0;
    }
    for (i = 0; i < 8; i++) {
        if (m258_SegmentDistCalc(&object->trans, &m258_wallTbl[i].start, &m258_wallTbl[i].end,
                                    &closest) >= radius) {
            continue;
        }
        dir.x = object->trans.x - closest.x;
        dir.y = 0.0f;
        dir.z = object->trans.z - closest.z;
        m258_VecNormalize(&dir);
        object->trans.x = radius * dir.x + closest.x;
        object->trans.z = radius * dir.z + closest.z;
    }
}

u8 m258_WallCrossCheck(Vec *pos, Vec *prev, f32 radius) {
    Vec hit;
    Vec unused; // Unreferenced, but present in the stack frame.
    Vec result;
    Vec wall;
    Vec move;
    f32 maxDist;
    f32 minDist;
    f32 dist;
    f32 t;
    f32 c;
    f32 nz;
    s32 i;
    u8 count;

    move.x = prev->x - pos->x;
    move.y = 0.0f;
    move.z = prev->z - pos->z;
    count = 0;
    minDist = sqrtf(move.x * move.x + move.z * move.z);
    maxDist = minDist;
    m258_AngleCalc(move.x, move.z);
    radius += 20.0;
    for (i = 0; i < 8; i++) {
        wall.x = m258_wallTbl[i].end.x - m258_wallTbl[i].start.x;
        wall.y = m258_wallTbl[i].end.y - m258_wallTbl[i].start.y;
        wall.z = m258_wallTbl[i].end.z - m258_wallTbl[i].start.z;
        c = wall.x * m258_wallTbl[i].start.z - wall.z * m258_wallTbl[i].start.x;
        nz = -wall.z;
        if ((nz * pos->x + wall.x * pos->z - c) * (nz * prev->x + wall.x * prev->z - c) > 0.0f) {
            continue;
        }
        t = m258_LineCrossCalc(&m258_wallTbl[i].start, &wall, pos, &move);
        if (t > 1.0) {
            continue;
        }
        if (t < 0.0) {
            continue;
        }
        hit.x = t * wall.x + m258_wallTbl[i].start.x;
        hit.y = 0.0f;
        hit.z = t * wall.z + m258_wallTbl[i].start.z;
        dist = m258_DistXZCalc(pos, &hit);
        if (dist >= maxDist) {
            continue;
        }
        if (dist >= minDist) {
            continue;
        }
        minDist = dist;
        m258_SegmentDistCalc(prev, &m258_wallTbl[i].start, &m258_wallTbl[i].end, &hit);
        wall.x = prev->x - hit.x;
        wall.y = 0.0f;
        wall.z = prev->z - hit.z;
        m258_VecNormalize(&wall);
        result.x = hit.x - radius * wall.x;
        result.z = hit.z - radius * wall.z;
        count++;
    }
    if (count) {
        pos->x = result.x;
        pos->z = result.z;
    }
    return count;
}

f32 m258_WallAvoidCalc(Vec *pos, f32 dist, f32 dir) {
    Vec hit;
    Vec newPos;
    Vec wall;
    Vec move;
    f32 minDist;
    f32 angle;
    f32 t;
    f32 d;
    f32 diff;
    s32 i;

    minDist = dist;
    angle = dir;
    move.x = dist * sindf(angle);
    move.y = 0.0f;
    move.z = dist * cosdf(angle);
    for (i = 0; i < 8; i++) {
        wall.x = (m258_wallTbl[i].end.x - m258_wallTbl[i].start.x) * 1.2;
        wall.y = m258_wallTbl[i].end.y - m258_wallTbl[i].start.y;
        wall.z = (m258_wallTbl[i].end.z - m258_wallTbl[i].start.z) * 1.2;
        t = m258_LineCrossCalc(&m258_wallTbl[i].start, &wall, pos, &move);
        if (t > 1.0) {
            continue;
        }
        if (t < 0.0) {
            continue;
        }
        hit.x = t * wall.x + m258_wallTbl[i].start.x;
        hit.y = 0.0f;
        hit.z = t * wall.z + m258_wallTbl[i].start.z;
        d = m258_DistXZCalc(pos, &hit);
        if (d > dist) {
            continue;
        }
        if (d > minDist) {
            continue;
        }
        minDist = d;
        angle = m258_AngleCalc(wall.x, wall.z);
        diff = m258_AngleCalc(pos->x - m258_wallTbl[i].start.x,
                                       pos->z - m258_wallTbl[i].start.z) -
               angle;
        while (diff < -180.0) {
            diff += 360.0;
        }
        while (diff > 180.0) {
            diff -= 360.0;
        }
        if (diff > 0.0) {
            angle += 60.0;
        } else {
            angle -= 60.0;
        }
        newPos.x = pos->x + move.x;
        newPos.y = 0.0f;
        newPos.z = pos->z + move.z;
        m258_SegmentDistCalc(&newPos, &m258_wallTbl[i].start, &m258_wallTbl[i].end, &hit);
        wall.x = newPos.x - hit.x;
        wall.y = 0.0f;
        wall.z = newPos.z - hit.z;
        m258_VecNormalize(&wall);
        newPos.x = hit.x - wall.x * 40.0;
        newPos.z = hit.z - wall.z * 40.0;
    }
    pos->x = newPos.x;
    pos->z = newPos.z;
    return angle;
}

void m258_PlayerObjCreateAll(void) {
    s32 i;

    MgPlayerParamReset();
    MgShadowAltSet(1);
    mgPlayerObjNum = 0;
    for (i = 0; i < 2; i++) {
        mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(2, 15, 50, -1, m258_PlayerObjInit);
    }
}

const FowlCharMotions m258_chrAnimNoTbl = { { 0, 1, 2, 3, 4, 5, 6, 7 } };

void m258_PlayerObjInit(omObjData *object) {
    FowlCharMotions motions = m258_chrAnimNoTbl; // Copied but never read.
    s32 anims[3][8] = {
        // Initialized but never read.
        { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C },
        { 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0x1D },
        { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B },
    };
    MgPlayerWork *data;
    FowlPlayerWork *work;
    s32 i;
    u8 player;
    s8 character;
    u32 model;
    s32 motion;

    for (i = 0; i < 4; i++) {
        if (m258_playerInitNo == GwPlayer[i].group) {
            break;
        }
    }
    player = i;
    character = GwPlayer[player].chr;
    model = omCharModelNoTbl[character][0];
    motion = omCharModelNoTbl[character][1];
    MgPlayerCreate(object, model, motion, player, 0x2D9, 0x2D9);
    data = object->data;
    data->unk50 &= ~1;
    data->unkEC = 0;
    object->trans.x = m258_playerPosTbl[m258_playerInitNo].x;
    object->trans.y = m258_playerPosTbl[m258_playerInitNo].y;
    object->trans.z = m258_playerPosTbl[m258_playerInitNo].z;
    data->unk3C = m258_playerRotTbl[m258_playerInitNo];
    switch (model >> 16) {
        case 6:
            data->unk48 *= 1.25f;
            break;
        case 4:
            data->unk48 *= 1.1f;
            break;
        case 5:
            data->unk48 *= 1.2f;
            break;
    }
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    object->trans.x = m258_playerPosTbl[m258_playerInitNo].x;
    object->trans.y = m258_playerPosTbl[m258_playerInitNo].y;
    object->trans.z = m258_playerPosTbl[m258_playerInitNo].z;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);

    data->unk158 = HuMemAllocTag(sizeof(FowlPlayerWork), TAG_OVERLAY);
    memset(data->unk158, 0, sizeof(FowlPlayerWork));
    work = data->unk158;
    work->player = player;
    work->index = m258_playerInitNo;
    work->character = character;
    work->unk25 = GwPlayer[player].stat & 1;
    work->unk23 = GwPlayer[player].cpu_difficulty;
    work->unk1C = model | 0x9A;
    work->unk24 = 0;
    work->pos.x = object->trans.x;
    work->pos.y = object->trans.y;
    work->pos.z = object->trans.z;
    work->unk26 = 0;
    ((FowlCameraWork *)m258_cameraObjTbl[m258_playerInitNo]->data)->player = object;
    MgPlayerMapAttrSet(object, 0, 2);
    data->unk50 |= 0x8200;
    object->func = m258_PlayerObjMain;
    Hu3DModelCameraSet(object->model[0], 3);
    Hu3DModelCameraSet(object->model[1], 3);
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(character, 0), 1, 0);
    MgPlayerMotLoad(object, 1, CharMotionDataNumGet(character, 1), 1, 0);
    MgPlayerMotLoad(object, 2, CharMotionDataNumGet(character, 2), 1, 0);
    MgPlayerMotLoad(object, 0x11, CharMotionDataNumGet(character, 0xE), 0, 0);
    MgPlayerMotLoad(object, 0x20, CharMotionDataNumGet(character, 0x22), 0, 0);
    MgPlayerMotLoad(object, 6, CharMotionDataNumGet(character, 4), 1, 0x13);
    MgPlayerMotLoad(object, 0x15, CharMotionDataNumGet(character, 0x1F), 0, 0x13);
    MgPlayerMotLoad(object, 5, CharMotionDataNumGet(character, 0x99), 0, 0);
    MgPlayerMotLoad(object, 0x27, CharMotionDataNumGet(character, 0x96), 1, 0);
    MgPlayerMotLoad(object, 0xD, CharMotionDataNumGet(character, 0x9A), 1, 0x3C);
    switch (model >> 16) {
        case 3:
        case 4:
        case 5:
            MgPlayerMotLoad(object, 0xE, CharMotionDataNumGet(character, 0x39), 1, 0x3C);
            break;
        case 2:
        case 6:
        case 7:
        case 8:
        case 9:
            MgPlayerMotLoad(object, 0xE, CharMotionDataNumGet(character, 0x3A), 1, 0x3C);
            break;
    }
    MgPlayerMotSet(object, 0);
    m258_playerInitNo++;
}

void m258_PlayerCreate(omObjData *object, s32 arg1, s32 arg2, u16 player, u16 tag) {
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

    object->model[0] = Hu3DModelRead(arg1 | arg2, tag);
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

void m258_PlayerObjMain(omObjData *object) {
    FowlCharMotions motions = m258_chrAnimNoTbl; // Copied but never read.
    Vec pos;
    MgPlayerWork *data;
    MgPlayerWork *otherData;
    FowlPlayerWork *work;
    FowlPlayerWork *otherWork;
    omObjData *other;
    u8 pad;
    u8 canCatch;
    u16 motStat;
    f32 angle;
    f32 mag;
    f32 range;
    f32 dist;
    s32 i;

    data = object->data;
    work = data->unk158;
    pad = data->unk57;
    canCatch = 0;
    if (m258_phase != 2) {
        HuPadStkY[pad] = 0;
        HuPadStkX[pad] = 0;
        HuPadBtnDown[pad] = 0;
        HuPadBtn[pad] = 0;
    }
    switch (m258_phase) {
        case 0:
            work->unk2C = work->unk2E = work->unk30 = work->unk32 = work->unk34 = work->unk3C = work->unk3E = 0;
            work->unk36 = 450;
            work->unk26 = 0;
            work->unk27 = 0;
            break;
        case 2:
            if (!work->unk25) {
                angle = m258_AngleCalc(HuPadStkX[pad], -HuPadStkY[pad]) + CRotM[work->index].y;
                mag = sqrtf(HuPadStkX[pad] * HuPadStkX[pad] + HuPadStkY[pad] * HuPadStkY[pad]);
                HuPadStkX[pad] = mag * sindf(angle);
                HuPadStkY[pad] = -mag * cosdf(angle);
            } else {
                HuPadStkY[pad] = 0;
                HuPadStkX[pad] = 0;
                HuPadBtnDown[pad] = 0;
                HuPadBtn[pad] = 0;
                m258_PlayerComInput(object);
            }
            break;
        case 6:
            if (work->unk24) {
                angle = m258_AngleCalc(-object->trans.x, -object->trans.z);
                HuPadStkX[pad] = sindf(angle) * 18.0;
                HuPadStkY[pad] = -cosdf(angle) * 18.0;
                Hu3DMotionSpeedSet(object->model[0], 1.0f);
            }
            break;
        case 7:
            work->unk3C = 0;
            if (work->unk24 == 1) {
                GwPlayer[data->unk59].bonusCoin += 10;
                MgPlayerMotSet(object, 0xD);
                HuAudCharVoicePlayPlayer(work->unk1C, -1, work->index);
                work->unk24++;
            } else if (work->unk24 == 0) {
                MgPlayerMotSet(object, 0xE);
                work->unk24--;
            }
            break;
        case 8:
            if (data != NULL) {
                HuMemFree(data->unk158);
                object->data = NULL;
                object->func = NULL;
            }
            return;
        case 9:
            return;
    }
    motStat = HuPadBtnDown[pad]; // Overwritten immediately, but needed to match.
    motStat = MgPlayerMotStatGet(object);
    work->prevPos.x = object->trans.x;
    work->prevPos.y = object->trans.y;
    work->prevPos.z = object->trans.z;
    if (work->unk3C != 0) {
        HuPadBtnDown[pad] &= ~B_BUTTON;
    } else {
        Hu3DData[object->model[0]].motIdShape = 0xFF;
    }
    MgPlayerObjMain(object);
    if (motStat & MGPLAYER_MOTSTAT_PUNCH) {
        if (Hu3DData[object->model[0]].motTime >= 16.0 && Hu3DData[object->model[0]].motTime <= 20.0) {
            canCatch = 1;
        }
    }
    if (m258_ChickenCatchCheck(object, canCatch)) {
        work->unk3C = 1;
        work->unk24 = 1;
        _HuAudPlayerFXPlay(0x4C0, 2);
        _HuAudPlayerFXPlay(0x4C2, 3);
        omVibrate(data->unk59, 10, 0, 10);
        Hu3DMotionShapeSet(object->model[0], object->motion[0x27], 0);
    }
    for (i = 0; i < 2; i++) {
        other = mgPlayerObjTbl[i];
        if (object == other) {
            continue;
        }
        otherData = other->data;
        otherWork = otherData->unk158;
        if (fabs(object->trans.y - other->trans.y) > 30.0) {
            continue;
        }
        dist = m258_DistXZCalc(&object->trans, &other->trans);
        range = data->unk48 + otherData->unk48;
        if (dist > range) {
            continue;
        }
        if (data->unk40 <= otherData->unk40) {
            angle = m258_AngleCalc(other->trans.x - object->trans.x, other->trans.z - object->trans.z);
            other->trans.x = range * sindf(angle) + object->trans.x;
            other->trans.z = range * cosdf(angle) + object->trans.z;
            if (other->trans.y < 30.0) {
                pos.x = otherWork->prevPos.x;
                pos.y = 0.0f;
                pos.z = otherWork->prevPos.z;
                if (m258_WallCrossCheck(&pos, &other->trans, otherData->unk48)) {
                    other->trans.x = pos.x;
                    other->trans.z = pos.z;
                }
            }
        } else {
            angle = m258_AngleCalc(object->trans.x - other->trans.x, object->trans.z - other->trans.z);
            object->trans.x = range * sindf(angle) + other->trans.x;
            object->trans.z = range * cosdf(angle) + other->trans.z;
            if (object->trans.y < 30.0) {
                pos.x = work->prevPos.x;
                pos.y = 0.0f;
                pos.z = work->prevPos.z;
                if (m258_WallCrossCheck(&pos, &object->trans, data->unk48)) {
                    object->trans.x = pos.x;
                    object->trans.z = pos.z;
                }
            }
        }
    }
    dist = sqrtf(object->trans.x * object->trans.x + object->trans.z * object->trans.z);
    range = 1200.0 - data->unk48 - 10.0;
    if (dist > range) {
        angle = m258_AngleCalc(object->trans.x, object->trans.z);
        object->trans.x = range * sindf(angle);
        object->trans.z = range * cosdf(angle);
    }
    m258_WallPush(object, data->unk48);
    work->motStat = motStat;
}

void m258_SplashEffSet(omObjData *object, f32 x, f32 y, f32 z) {
    s32 i;

    for (i = 9; i < 12; i++) {
        if (Hu3DData[object->model[i]].attr & 4) {
            MgPlayerEffSet(object, i, x, y, z, 0.0f, 0.0f);
            return;
        }
    }
}

u16 m258_PlayerComInput(omObjData *object) {
    Vec corners[4] = { { 1000.0f, 0.0f, 0.0f }, { -1000.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1000.0f }, { 0.0f, 0.0f, -1000.0f } };
    Vec target;
    MgPlayerWork *data;
    FowlPlayerWork *work;
    omObjData *fox;
    FowlPlayChickenWork *foxWork;
    f32 dist;
    f32 angle;
    f32 clear;
    f32 diff;
    u8 press = FALSE;
    s16 pad;
    u16 buttons;

    m258_PlayerWorkGet(object, &data, &work);
    pad = data->unk57;
    MgPlayerMotStatGet(object);
    fox = m258_chickenObjTbl[0];
    foxWork = ((MgPlayerWork *)fox->data)->unk158;
    if (m258_timer > 1500) {
        target.x = fox->trans.x + sindf(foxWork->unk14) * 60.0;
        target.z = fox->trans.z + cosdf(foxWork->unk14) * 60.0;
    } else {
        target.x = fox->trans.x + (work->unk23 * 0.5 + 1.0) * 20.0 * sindf(foxWork->unk14);
        target.z = fox->trans.z + (work->unk23 * 0.5 + 1.0) * 20.0 * cosdf(foxWork->unk14);
    }
    angle = m258_AngleCalc(target.x - object->trans.x, target.z - object->trans.z);
    dist = m258_DistXZCalc(&object->trans, &fox->trans);
    work->unk36--;
    switch (work->unk2C) {
        case 0:
            if (dist < (work->unk23 * 5.0 + 20.0) * 20.0) {
                work->unk2C = 1;
            }
            if (work->unk32 != 0) {
                f32 cornerDist = m258_DistXZCalc(&object->trans, &corners[work->unk32 - 1]);

                angle = m258_AngleCalc(corners[work->unk32 - 1].x - object->trans.x,
                                                corners[work->unk32 - 1].z - object->trans.z);
                if (cornerDist < 200.0) {
                    work->unk32 = 0;
                }
            } else {
                work->unk32 = (s32)((f32)m258_Rand16Get() * 1.52587890625e-05 * 4.0) + 1;
            }
            if (work->unk36 == 0) {
                work->unk2C = 2;
                work->unk36 = work->unk23 * 20 + (s16)((s32)((f32)m258_Rand16Get() * 1.52587890625e-05 * 40.0) + 30);
            }
            break;
        case 1:
            if (dist >= (work->unk23 * 5.0 + 25.0) * 20.0) {
                work->unk2C = 0;
            }
            if (work->unk2E == 0) {
                work->unk2E = (s32)((f32)m258_Rand16Get() * 1.52587890625e-05 * 60.0) + 10;
                work->unk30 = (f32)(m258_Rand16Get() - 0x8000) * 3.0517578125e-05 * (55 - work->unk23 * 5);
            }
            work->unk2E--;
            if (dist < data->unk48 + foxWork->unk0C + 26.0) {
                if (m258_timer > 1260) {
                    work->unk34 = 3;
                } else if ((s32)((f32)m258_Rand16Get() * 1.52587890625e-05 * (6 - work->unk23)) == 0) {
                    press = TRUE;
                }
            } else if (work->unk34 != 0) {
                if (--work->unk34 == 0) {
                    press = TRUE;
                }
            }
            if (work->unk36 == 0) {
                work->unk2C = 2;
                work->unk36 = work->unk23 * 15 + (s16)((s32)((f32)m258_Rand16Get() * 1.52587890625e-05 * 30.0) + 30);
            }
            break;
        case 2:
            work->unk30 = 0;
            if (dist < data->unk48 + foxWork->unk0C + 20.0) {
                press = TRUE;
            }
            if (work->unk36 == 0) {
                work->unk2C = 0;
                work->unk36 =
                    135.0 - work->unk23 * 20 + (s32)((f32)m258_Rand16Get() * 1.52587890625e-05 * 60.0);
            }
            break;
    }
    angle += work->unk30;
    HuPadStkX[pad] = (work->unk23 * 2.0 + 56.0) * sindf(angle);
    HuPadStkY[pad] = (work->unk23 * 2.0 + 56.0) * -cosdf(angle);
    if (press) {
        HuPadBtnDown[pad] |= B_BUTTON;
    }
    target.x = object->trans.x;
    target.y = 0.0f;
    target.z = object->trans.z;
    clear = m258_WallAvoidCalc(&target, 120.0f, angle);
    diff = angle - data->unk3C;
    while (diff < -180.0) {
        diff += 360.0;
    }
    while (diff > 180.0) {
        diff -= 360.0;
    }
    if (clear != angle) {
        if (fabs(diff) < 30.0) {
            HuPadBtnDown[pad] |= A_BUTTON;
        }
    }
    return buttons;
}

void m258_PlayerWorkGet(omObjData *object, MgPlayerWork **data, FowlPlayerWork **work) {
    *data = object->data;
    *work = (*data)->unk158;
}

void m258_ChickenObjCreate(void) {
    s32 i;

    m258_featherSprAnim = m258_AnimDataRead(0x5B0003);
    for (i = 0; i < 1; i++) {
        m258_chickenObjTbl[i] = omAddObj(3, 5, 5, -1, m258_ChickenObjInit);
    }
}

void m258_ChickenObjInit(omObjData *object) {
    MgPlayerWork *data;
    FowlPlayChickenWork *work;
    s32 index;
    s32 i;

    data = HuMemAllocTag(sizeof(MgPlayerWork), TAG_OVERLAY);
    object->data = data;
    memset(data, 0, sizeof(MgPlayerWork));
    data->unkE8 = HuMemAllocTag(object->mtncnt * sizeof(MgMotAttr), TAG_OVERLAY);
    memset(data->unkE8, 0, object->mtncnt * sizeof(MgMotAttr));
    data->unk52 = 0;
    data->unkD0 = 0xFFFF;
    work = HuMemAllocTag(sizeof(FowlPlayChickenWork), TAG_OVERLAY);
    data->unk158 = work;
    memset(work, 0, sizeof(FowlPlayChickenWork));
    work->unk00 = 0;
    work->unk01 = 0;
    work->unk24.x = work->unk24.y = work->unk24.z = 0.0f;
    work->unk10 = work->unk14 = (f32)(m258_Rand16Get() - 0x8000) * 3.0517578125e-05 * 180.0;
    work->unk0C = 20.0f;
    work->unk06 = 0;
    work->unk04 = 0;
    work->unk02 = 0;
    object->model[0] = Hu3DModelRead(0x5B0006, 0x2D9);
    object->model[1] = Hu3DModelRead3(9, 0x2D9);
    m258_dustSprAnim = m258_AnimDataRead(0xB);
    for (i = 0; i < 8; i++) {
        work->unk34[i] = index = m258_BillboardCreate(m258_dustSprAnim, 0x20009000);
        m258_BillboardModeSet(index, 2);
        m258_BillboardColorSet(index, -1, -58, 105, 224);
        m258_BillboardScaleSet(index, 1.2f, 1.2f, 1.2f);
        m258_BillboardAnimSpeedSet(index, 0.5f);
    }
    Hu3DModelScaleSet(object->model[1], 0.75f, 0.75f, 0.75f);
    MgPlayerMotLoad(object, 0, 0x5B0007, 1, 0);
    MgPlayerMotLoad(object, 1, 0x5B0008, 1, 0);
    MgPlayerMotLoad(object, 2, 0x5B0009, 1, 0);
    MgPlayerMotSet(object, 0);
    object->func = m258_ChickenObjMain;
    object->trans.x = (f32)(m258_Rand16Get() - 0x8000) * 3.0517578125e-05 * 40.0;
    object->trans.z = (f32)(m258_Rand16Get() - 0x8000) * 3.0517578125e-05 * 40.0;
    for (i = 0; i < 32; i++) {
        work->feathers[i].index = m258_BillboardCreate(m258_featherSprAnim, 0x10009000);
        m258_BillboardModeSet(work->feathers[i].index, 0);
        m258_BillboardScaleSet(work->feathers[i].index, 2.0f, 2.0f, 2.0f);
        work->feathers[i].unk01 = 0;
        work->feathers[i].pos.x = work->feathers[i].pos.y = work->feathers[i].pos.z = 0.0f;
        work->feathers[i].unk10 = 0.0f;
    }
    m258_chickenNum++;
}

void m258_ChickenObjMain(omObjData *object) {
    Vec pos;
    Vec unusedVec; // Unreferenced, but present in the stack frame.
    f32 dists[2];
    f32 angles[2];
    HuMtx4F unusedMtx; // Unreferenced, but present in the stack frame.
    MgPlayerWork *data = object->data;
    FowlPlayChickenWork *work = data->unk158;
    omObjData *player;
    f32 dist;
    f32 angle;
    f32 diff;
    s16 seNo = 0;
    u8 index;
    s32 i;
    s16 pan;

    switch (m258_phase) {
        case 0:
        case 1:
            work->unk04 = 2;
            work->unk02 = 2;
            work->unk06 = 20;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            break;
        case 8:
            if (data != NULL) {
                HuMemFree(data->unk158);
                object->data = NULL;
                object->func = NULL;
            }
            return;
        case 9:
            return;
    }
    dist = sqrtf(object->trans.x * object->trans.x + object->trans.z * object->trans.z);
    angle = m258_AngleCalc(object->trans.x, object->trans.z);
    switch (work->unk00) {
        case 0:
            work->unk24.x = work->unk24.z = 0.0f;
            if (--work->unk02 == 0) {
                work->unk03 =
                    m258_timer * 0.2 + (s32)((f32)m258_Rand16Get() * 1.52587890625e-05 * 30.0);
                work->unk00++;
            }
            break;
        case 1:
        case 2:
            for (i = 0; i < 2; i++) {
                player = mgPlayerObjTbl[i];
                dists[i] = m258_DistXZCalc(&object->trans, &player->trans);
                angles[i] =
                    m258_AngleCalc(player->trans.x - object->trans.x, player->trans.z - object->trans.z);
            }
            if (work->unk02 == 0) {
                if (dist >= 960.0) {
                    s32 nearest;

                    if (dists[0] < dists[1]) {
                        nearest = 0;
                    } else {
                        nearest = 1;
                    }
                    diff = angle - angles[nearest];
                    while (diff < -180.0) {
                        diff += 360.0;
                    }
                    while (diff > 180.0) {
                        diff -= 360.0;
                    }
                    if (diff < 0.0) {
                        work->unk14 = angle + 170.0;
                    } else {
                        work->unk14 = angle - 170.0;
                    }
                    work->unk02 = 10;
                } else if (dists[0] < 200.0) {
                    if (work->unk00 != 1) {
                        seNo = 0x4C1;
                        m258_cluckTimer = 1;
                    }
                    work->unk14 = angles[0] + 180.0;
                    work->unk00 = 1;
                } else if (dists[1] < 200.0) {
                    if (work->unk00 != 1) {
                        seNo = 0x4C1;
                        m258_cluckTimer = 1;
                    }
                    work->unk14 = angles[1] + 180.0;
                    work->unk00 = 1;
                } else {
                    work->unk14 =
                        (angles[0] + angles[1]) * 0.5 + ((fabs(angles[0] - angles[1]) < 180.0) ? 180.0 : 0.0);
                }
                pos.x = object->trans.x;
                pos.y = 0.0f;
                pos.z = object->trans.z;
                diff = m258_WallAvoidCalc(&pos, 200.0f, work->unk10);
                if (work->unk10 != diff) {
                    work->unk14 = diff;
                }
            } else {
                work->unk02--;
            }
            while (work->unk14 < -180.0) {
                work->unk14 += 360.0;
            }
            while (work->unk14 > 180.0) {
                work->unk14 -= 360.0;
            }
            diff = work->unk10 - work->unk14;
            while (diff < -180.0) {
                diff += 360.0;
            }
            while (diff > 180.0) {
                diff -= 360.0;
            }
            if (diff > 8.0) {
                work->unk10 = work->unk10 - 8.0;
            } else if (diff < -8.0) {
                work->unk10 = work->unk10 + 8.0;
            } else {
                work->unk10 = work->unk14;
            }
            while (work->unk10 < -180.0) {
                work->unk10 += 360.0;
            }
            while (work->unk10 > 180.0) {
                work->unk10 -= 360.0;
            }
            work->unk03--;
            if (work->unk00 == 1) {
                MgPlayerMotSet(object, 2);
                work->unk08 = 20.0f;
                work->unk04 -= 2;
                work->unk06--;
                if (work->unk03 == 0) {
                    work->unk03 =
                        m258_timer * 0.05 + (s32)((f32)m258_Rand16Get() * 1.52587890625e-05 * 30.0);
                    work->unk00++;
                }
            } else {
                MgPlayerMotSet(object, 1);
                work->unk08 = 6.0f;
                work->unk04--;
                if (work->unk03 == 0) {
                    m258_cluckTimer = 1;
                    seNo = 0x4C1;
                    work->unk03 =
                        m258_timer * 0.2 + (s32)((f32)m258_Rand16Get() * 1.52587890625e-05 * 30.0);
                    work->unk00--;
                }
            }
            if (--m258_cluckTimer == 0) {
                if (work->unk00 == 1) {
                    m258_cluckTimer = 9;
                } else {
                    m258_cluckTimer = 15;
                }
                if (dists[0] < 800.0 || dists[1] < 800.0) {
                    f32 total = dists[0] + dists[1];

                    pan = dists[0] * 128.0 / total;
                    if (pan < 32) {
                        pan = 32;
                    }
                    if (pan > 96) {
                        pan = 96;
                    }
                    if (seNo == 0) {
                        seNo = (m258_Rand16Get() & 3) + 0x4C3;
                    }
                    HuAudFXPanning(_HuAudPlayerFXPlay(seNo, 4), pan);
                }
            }
            break;
        case 3:
            if (--work->unk03 == 0) {
                MgPlayerMotSet(object, 0);
                Hu3DModelHookSet(object->model[0], work->target->model[0], "item_hook");
                Hu3DModelAttrSet(object->model[0], 0x4000, 0x4000);
            }
            Hu3DModelAttrSet(object->model[1], 4, 4);
            work->unk08 = 0.0f;
            if (m258_phase == 6) {
                m258_HookPosGet(work->target->model[0], "item_hook", 0, &object->trans);
            } else if (m258_phase == 7) {
                work->unk10 = m258_AngleCalc(-object->trans.x, -object->trans.z);
                work->unk08 = 16.0f;
                work->unk24.y = 15.0f;
                work->unk00++;
            }
            break;
        case 4:
            work->unk24.y -= 2.0;
            object->trans.y += work->unk24.y;
            if (object->trans.y < 0.0) {
                object->trans.y = 0.0f;
            }
            break;
    }
    work->unk24.x = sindf(work->unk10) * work->unk08;
    work->unk24.z = cosdf(work->unk10) * work->unk08;
    object->trans.x += work->unk24.x;
    object->trans.z += work->unk24.z;
    if (work->unk01 != 0) {
        pos.x = work->unk18.x;
        pos.y = 0.0f;
        pos.z = work->unk18.z;
        if (m258_WallCrossCheck(&pos, &object->trans, work->unk0C)) {
            object->trans.x = pos.x;
            object->trans.z = pos.z;
        } else {
            m258_WallPush(object, work->unk0C);
        }
    } else {
        m258_WallPush(object, work->unk0C);
    }
    work->unk01 = 0;
    if (dist > 1200.0 - work->unk0C) {
        object->trans.x = (1200.0 - work->unk0C) * (object->trans.x / dist);
        object->trans.z = (1200.0 - work->unk0C) * (object->trans.z / dist);
    }
    for (i = 0; i < 4; i++) {
        index = work->unk34[i];
        if ((m258_BillboardAttrGet(index) & 0x8000) && work->unk06 == 0) {
            m258_BillboardPosSet(index, object->trans.x, object->trans.y - 10.0, object->trans.z);
            m258_BillboardAttrReset(index, 0x8000);
            m258_BillboardPatSet(index, 0);
            work->unk06 = 8;
        }
    }
    for (i = 0; i < 32; i++) {
        if (work->feathers[i].unk01 == 0) {
            if (work->unk04 <= 0) {
                m258_BillboardAttrReset(work->feathers[i].index, 0x8000);
                work->feathers[i].pos.x = object->trans.x;
                work->feathers[i].pos.y = 1.0f;
                work->feathers[i].pos.z = object->trans.z;
                work->feathers[i].unk10 = work->unk10;
                work->feathers[i].unk01 = 0x80;
                m258_BillboardPosSet(work->feathers[i].index, work->feathers[i].pos.x, work->feathers[i].pos.y,
                                        work->feathers[i].pos.z);
                m258_BillboardRotSet(work->feathers[i].index, 90.0f, work->feathers[i].unk10, 0.0f);
                m258_BillboardColorSet(work->feathers[i].index, 0, 0, 0, 0xFF);
                work->unk04 = 10;
            } else {
                m258_BillboardAttrSet(work->feathers[i].index, 0x8000);
            }
        } else {
            work->feathers[i].unk01--;
            m258_BillboardColorSet(work->feathers[i].index, 0, 0, 0, work->feathers[i].unk01 * 2);
        }
    }
    work->unk18.x = object->trans.x;
    work->unk18.y = object->trans.y;
    work->unk18.z = object->trans.z;
    object->rot.y = work->unk10;
    Hu3DModelPosSet(object->model[1], object->trans.x, 1.0f, object->trans.z);
    MgPlayerMotUpdate(object);
}

u8 m258_ChickenCatchCheck(omObjData *object, u8 canCatch) {
    Vec unused; // Unreferenced, but present in the stack frame.
    MgPlayerWork *data;
    FowlPlayChickenWork *work;
    omObjData *fox;
    f32 range;
    f32 dist;
    f32 angle;

    if (object->trans.y >= 20.0) {
        return 0;
    }
    fox = m258_chickenObjTbl[0];
    work = ((MgPlayerWork *)fox->data)->unk158;
    data = object->data;
    range = work->unk0C + data->unk48;
    dist = m258_DistXZCalc(&object->trans, &fox->trans);
    if (dist > range + 20.0) {
        return 0;
    }
    angle = m258_AngleCalc(object->trans.x - fox->trans.x, object->trans.z - fox->trans.z);
    if (dist < range) {
        fox->trans.x = object->trans.x - (work->unk0C + data->unk48) * sindf(angle);
        fox->trans.z = object->trans.z - (work->unk0C + data->unk48) * cosdf(angle);
        work->unk01 = 1;
    }
    if (canCatch == 0) {
        return 0;
    }
    if (work->unk00 >= 3) {
        return 0;
    }
    angle = angle + 180.0 - data->unk3C;
    while (angle < -180.0) {
        angle += 360.0;
    }
    while (angle > 180.0) {
        angle -= 360.0;
    }
    if (fabs(angle) < 60.0) {
        work->target = object;
        work->unk00 = 3;
        work->unk03 = 1;
        return 1;
    }
    return 0;
}

s32 m258_Rand16Get(void) {
    m258_randSeed = (m258_randSeed + (rand8() & 0xFF)) * 0x41C64E6D + 0x3039;
    return m258_randSeed >> 16;
}

f32 m258_AngleCalc(f32 y, f32 x) {
    f32 fullCircle = 360.0f;
    f32 angle = atan2df(y, x);

    if (angle < -180.0f) {
        angle += fullCircle;
    } else if (angle >= 180.0) {
        angle -= fullCircle;
    }
    return angle;
}

f32 m258_DistXZCalc(Vec *arg0, Vec *arg1) {
    return sqrtf(((arg0->x - arg1->x) * (arg0->x - arg1->x)) +
                 ((arg0->z - arg1->z) * (arg0->z - arg1->z)));
}

void m258_DirRotCalc(Vec *dir, f32 *rot) {
    *rot++ = m258_AngleCalc(sqrtf(dir->x * dir->x + dir->z * dir->z), -dir->y);
    *rot++ = m258_AngleCalc(dir->x, dir->z);
    *rot = 0.0f;
}

f32 m258_VecNormalize(Vec *vec) {
    f32 len;
    f32 inv;

    len = vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
    len = sqrtf(len);
    if (len != 0.0f) {
        inv = 1.0f / len;
        vec->x = inv * vec->x;
        vec->y = inv * vec->y;
        vec->z = inv * vec->z;
    } else {
        vec->x = vec->y = vec->z = 0.0f;
    }
    return len;
}

f32 m258_LineParamCalc(Vec *arg0, Vec *arg1, Vec *arg2) {
    f32 dot = (arg2->x * (arg1->x - arg0->x)) + (arg2->y * (arg1->y - arg0->y)) +
              (arg2->z * (arg1->z - arg0->z));
    f32 len = -((arg2->x * arg2->x) + (arg2->y * arg2->y) + (arg2->z * arg2->z));

    if (len != 0.0f) {
        dot /= len;
    }
    return dot;
}

f32 m258_SegmentDistCalc(Vec *point, Vec *start, Vec *end, Vec *closest) {
    Vec dir;
    f32 t;

    if (m258_DistXZCalc(start, end) == 0.0f) {
        closest->x = start->x;
        closest->y = start->y;
        closest->z = start->z;
        return m258_DistXZCalc(point, start);
    }
    dir.x = end->x - start->x;
    dir.y = end->y - start->y;
    dir.z = end->z - start->z;
    t = m258_LineParamCalc(point, start, &dir);
    if (t <= 0.0) {
        closest->x = start->x;
        closest->y = start->y;
        closest->z = start->z;
    } else if (t >= 1.0) {
        closest->x = end->x;
        closest->y = end->y;
        closest->z = end->z;
    } else {
        closest->x = t * dir.x + start->x;
        closest->y = t * dir.y + start->y;
        closest->z = t * dir.z + start->z;
    }
    return m258_DistXZCalc(point, closest);
}

f32 m258_LineCrossCalc(Vec *pos1, Vec *dir1, Vec *pos2, Vec *dir2) {
    f32 invalid = -1.0f;
    f32 result;
    f32 det;
    f32 absX;
    f32 absY;
    f32 absZ;
    s32 axis;

    absX = dir2->x;
    if (absX < 0.0f) {
        absX = -absX;
    }
    absY = dir2->y;
    if (absY < 0.0f) {
        absY = -absY;
    }
    absZ = dir2->z;
    if (absZ < 0.0f) {
        absZ = -absZ;
    }
    if (absX >= absY) {
        if (absX >= absZ) {
            axis = 1;
        } else {
            axis = 0x100;
        }
    } else {
        if (absY >= absZ) {
            axis = 0x10;
        } else {
            axis = 0x100;
        }
    }
    if (axis & 3) {
        if (dir1->x != 0.0f || dir1->z != 0.0f) {
            det = dir2->x * dir1->z - dir2->z * dir1->x;
            if (det == 0.0f) {
                return invalid;
            }
            result = (dir2->z * (pos1->x - pos2->x) - dir2->x * (pos1->z - pos2->z)) / det;
        } else {
            det = dir2->y * dir1->x - dir2->x * dir1->y;
            if (det == 0.0f) {
                return invalid;
            }
            result = (dir2->x * (pos1->y - pos2->y) - dir2->y * (pos1->x - pos2->x)) / det;
        }
    } else if (axis & 0x30) {
        if (dir1->x != 0.0f || dir1->y != 0.0f) {
            det = dir2->y * dir1->x - dir2->x * dir1->y;
            if (det == 0.0f) {
                return invalid;
            }
            result = (dir2->x * (pos1->y - pos2->y) - dir2->y * (pos1->x - pos2->x)) / det;
        } else {
            det = dir2->z * dir1->y - dir2->y * dir1->z;
            if (det == 0.0f) {
                return invalid;
            }
            result = (dir2->y * (pos1->z - pos2->z) - dir2->z * (pos1->y - pos2->y)) / det;
        }
    } else {
        if (dir1->x != 0.0f || dir1->z != 0.0f) {
            det = dir2->x * dir1->z - dir2->z * dir1->x;
            if (det == 0.0f) {
                return invalid;
            }
            result = (dir2->z * (pos1->x - pos2->x) - dir2->x * (pos1->z - pos2->z)) / det;
        } else {
            det = dir2->z * dir1->y - dir2->y * dir1->z;
            if (det == 0.0f) {
                return invalid;
            }
            result = (dir2->y * (pos1->z - pos2->z) - dir2->z * (pos1->y - pos2->y)) / det;
        }
    }
    return result;
}

void m258_HookPosGet(s16 model, char *hook, s16 time, Vec *pos) {
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

s16 m258_AnimDataRead(s32 dataNum) {
    void *data;
    s16 spriteId;

    data = DataRead(dataNum);
    spriteId = HuSprAnimRead(data);
    DataClose(data);
    return spriteId;
}

s16 m258_SprGrpCreate(s16 spriteId, s16 count) {
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

HuSprAnimPat *m258_SprAnimPatGet(s16 arg0, s16 arg1) {
    return &HuSprAnimDataGet(arg0)->pat[arg1];
}

void m258_BillboardInit(u16 count) {
    FowlPlayBillboard *fowl;
    s16 i;

    m258_billboardNum = count;
    m258_billboardTbl = HuMemAlloc(count * sizeof(FowlPlayBillboard));
    for (i = 0; i < 6; i++) {
        m258_billboardBufTbl[i] = NULL;
    }
    for (i = 0; i < m258_billboardNum; i++) {
        fowl = &m258_billboardTbl[i];
        fowl->sprite = NULL;
        fowl->callback = NULL;
        fowl->unk_28 = 0;
        fowl->unk_20 = 0x100;
        fowl->unk_1F = 0xFF;
        fowl->unk_1E = 0xFF;
        fowl->unk_1D = 0xFF;
        fowl->unk_2C = 0;
        fowl->unk_24 = 0;
        fowl->unk_30.x = 1.0f;
        fowl->unk_1C = 0;
        fowl->unk_1B = 0;
        fowl->unk_30.y = fowl->unk_30.z = fowl->unk_3C = 0.0f;
        fowl->unk_40.x = fowl->unk_40.y = fowl->unk_40.z = 0.0f;
        fowl->unk_4C.x = fowl->unk_4C.y = fowl->unk_4C.z = 1.0f;
        fowl->unk_58.x = fowl->unk_58.y = fowl->unk_58.z = 0.0f;
    }
}

void m258_BillboardTileLoad(Gfx **gfx, HuSprAnimPat *cel, u8 fmt, u8 siz, u16 height, u16 uls,
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

s16 m258_BillboardGfxBuild(FowlPlayBillboard *fowl) {
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

    cel = fowl->sprite->pat;
    buf = HuMemAlloc(0x1000);
    gfx = buf;
    gSPSegment(gfx++, 0x0C, cel->data);
    gSPSegment(gfx++, 0x0E, fowl->vtx);
    start = gfx;
    gDPPipeSync(gfx++);
    switch (fowl->sprite->pixelBits) {
        case 4:
            siz = G_IM_SIZ_4b;
            if (fowl->sprite->palNum == 1) {
                fmt = G_IM_FMT_IA;
                gDPSetTextureLUT(gfx++, G_TT_NONE);
            } else {
                fmt = G_IM_FMT_CI;
                gDPLoadTLUT_pal16(gfx++, 0, fowl->sprite->pal);
                gDPSetTextureLUT(gfx++, G_TT_RGBA16);
            }
            mode = 0;
            break;
        case 8:
            siz = G_IM_SIZ_8b;
            if (fowl->sprite->palNum == 1) {
                fmt = G_IM_FMT_IA;
                gDPSetTextureLUT(gfx++, G_TT_NONE);
                mode = 2;
            } else {
                fmt = G_IM_FMT_CI;
                gDPLoadTLUT_pal256(gfx++, fowl->sprite->pal);
                gDPSetTextureLUT(gfx++, G_TT_RGBA16);
                mode = 2;
            }
            break;
        case 16:
            siz = G_IM_SIZ_16b;
            if (fowl->sprite->palNum == 1) {
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
            if (m258_tmemRowAltTbl[cel->sizeX >> m258_sizShiftTbl[siz]] >= rows ||
                rows == m258_tmemRowTbl[cel->sizeX >> m258_sizShiftTbl[siz]]) {
                mode++;
            }
        }
    }
    // The differing masks/maskt byte conversions are required to match register allocation.
    if (fowl->unk_28 & 0xC0000) {
        masks = fowl->unk_1B & 0xFF;
        cms = (fowl->unk_28 >> 18) - 1;
    } else {
        masks = 0;
        cms = 0;
    }
    if (fowl->unk_28 & 0x300000) {
        maskt = (u8)fowl->unk_1C;
        cmt = (fowl->unk_28 >> 20) - 1;
    } else {
        maskt = 0;
        cmt = 0;
    }
    gDPPipeSync(gfx++);
    segCel = *cel;
    segCel.data = (void *)0x0C000000;
    if ((u32)fowl->unk_28 >= 0x80000000 && count == 1 && remainder == 0) {
        m258_BillboardTileLoad(&gfx, &segCel, fmt, siz, rows, 0, 0, cel->sizeX - 1, cel->sizeY - 1, cms, cmt, masks,
                                maskt, mode);
        gSPVertex(gfx++, (Vtx *)0x0E000000, 5, 0);
        gSP2Triangles(gfx++, 0, 2, 4, 0, 2, 3, 4, 0);
        gSP2Triangles(gfx++, 0, 4, 1, 0, 4, 3, 1, 0);
    } else {
        for (i = 0; i < count; i++) {
            m258_BillboardTileLoad(&gfx, &segCel, fmt, siz, rows, 0, i * rows, cel->sizeX - 1, (i + 1) * rows - 1,
                                    cms, cmt, masks, maskt, mode);
            gSPVertex(gfx++, (Vtx *)0x0E000000 + i * 2, 4, 0);
            gSP2Triangles(gfx++, 0, 2, 3, 0, 0, 3, 1, 0);
        }
        if (remainder != 0) {
            m258_BillboardTileLoad(&gfx, &segCel, fmt, siz, remainder, 0, i * rows, cel->sizeX - 1,
                                    cel->sizeY - 1, cms, cmt, masks, maskt, mode);
            gSPVertex(gfx++, (Vtx *)0x0E000000 + i * 2, 4, 0);
            gSP2Triangles(gfx++, 0, 2, 3, 0, 0, 3, 1, 0);
        }
    }
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    fowl->unk_22 = gfx - start;
    fowl->displayList = HuMemAlloc(fowl->unk_22 * sizeof(Gfx));
    memcpy(fowl->displayList, start, fowl->unk_22 * sizeof(Gfx));
    HuMemFree(buf);
    return 1;
}

s16 m258_BillboardCreate(s16 spriteId, s32 flags) {
    FowlPlayBillboard *fowl;
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

    for (index = 0; index < m258_billboardNum; index++) {
        if (m258_billboardTbl[index].sprite == NULL) {
            break;
        }
    }
    if (index == m258_billboardNum) {
        return -1;
    }
    fowl = &m258_billboardTbl[index];
    fowl->sprite = HuSprAnimTbl[spriteId];
    fowl->unk_28 = flags;
    fowl->unk_1A = 7;
    cel = fowl->sprite->pat;
    switch (fowl->sprite->pixelBits) {
        case 4:
            siz = G_IM_SIZ_4b;
            fmt = (fowl->sprite->palNum == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 8:
            siz = G_IM_SIZ_8b;
            fmt = (fowl->sprite->palNum == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 16:
            siz = G_IM_SIZ_16b;
            fmt = (fowl->sprite->palNum == 1) ? G_IM_FMT_IA : G_IM_FMT_RGBA;
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
    fowl->unk_18 = count + 2;
    fowl->unk_19 = rows;
    fowl->vtx = HuMemAlloc((count + 2) * 2 * sizeof(Vtx));
    for (i = 0; i < count + 1; i++) {
        fowl->vtx[i * 2].ob[0] = 0;
        fowl->vtx[i * 2 + 1].ob[0] = cel->sizeX;
        fowl->vtx[i * 2].ob[1] = fowl->vtx[i * 2 + 1].ob[1] = -i * rows;
        fowl->vtx[i * 2].tc[0] = 0;
        fowl->vtx[i * 2 + 1].tc[0] = cel->sizeX << 6;
        fowl->vtx[i * 2].tc[1] = (i * rows) << 6;
        fowl->vtx[i * 2 + 1].tc[1] = (i * rows) << 6;
        for (j = 0; j < 2; j++) {
            fowl->vtx[i * 2 + j].ob[2] = 0;
            fowl->vtx[i * 2 + j].cn[0] = 0xFF;
            fowl->vtx[i * 2 + j].cn[1] = 0xFF;
            fowl->vtx[i * 2 + j].cn[2] = 0xFF;
            fowl->vtx[i * 2 + j].cn[3] = 0xFF;
        }
    }
    if (remainder != 0) {
        fowl->vtx[i * 2].ob[0] = 0;
        fowl->vtx[i * 2 + 1].ob[0] = cel->sizeX;
        fowl->vtx[i * 2].ob[1] = fowl->vtx[i * 2 + 1].ob[1] = cel->sizeY;
        fowl->vtx[i * 2].tc[0] = 0;
        fowl->vtx[i * 2 + 1].tc[0] = cel->sizeX << 6;
        fowl->vtx[i * 2].tc[1] = fowl->vtx[i * 2 + 1].tc[1] = cel->sizeY << 6;
        for (j = 0; j < 2; j++) {
            fowl->vtx[i * 2 + j].ob[2] = 0;
            fowl->vtx[i * 2 + j].cn[0] = 0xFF;
            fowl->vtx[i * 2 + j].cn[1] = 0xFF;
            fowl->vtx[i * 2 + j].cn[2] = 0xFF;
            fowl->vtx[i * 2 + j].cn[3] = 0xFF;
        }
    } else if (count == 1) {
        fowl->vtx[4].ob[0] = cel->sizeX * 0.5;
        fowl->vtx[4].ob[1] = -cel->sizeY * 0.5;
        fowl->vtx[4].ob[2] = 0;
        fowl->vtx[4].tc[0] = cel->sizeX * 0.5 * 64.0;
        fowl->vtx[4].tc[1] = cel->sizeY * 0.5 * 64.0;
        fowl->vtx[4].cn[0] = 0xFF;
        fowl->vtx[4].cn[1] = 0xFF;
        fowl->vtx[4].cn[2] = 0xFF;
        fowl->vtx[4].cn[3] = 0xFF;
    }
    if (!m258_BillboardGfxBuild(fowl)) {
        HuMemFree(fowl->vtx);
        index = -1;
    }
    return index;
}

void m258_BillboardSprSet(s16 index, s16 spriteId) {
    FowlPlayBillboard *fowl;
    HuSprAnimPat *cel;
    s32 siz;
    s32 fmt;
    s32 alignedWidth;
    u32 rows;
    u32 count;
    s32 remainder;
    u32 i;
    s32 j;

    fowl = &m258_billboardTbl[index];
    fowl->sprite = HuSprAnimTbl[spriteId];
    cel = fowl->sprite->pat;
    HuMemFree(fowl->vtx);
    HuMemFree(fowl->displayList);
    switch (fowl->sprite->pixelBits) {
        case 4:
            siz = G_IM_SIZ_4b;
            fmt = (fowl->sprite->palNum == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 8:
            siz = G_IM_SIZ_8b;
            fmt = (fowl->sprite->palNum == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 16:
            siz = G_IM_SIZ_16b;
            fmt = (fowl->sprite->palNum == 1) ? G_IM_FMT_IA : G_IM_FMT_RGBA;
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
    fowl->unk_18 = count + 2;
    fowl->unk_19 = rows;
    fowl->vtx = HuMemAlloc((count + 2) * 2 * sizeof(Vtx));
    for (i = 0; i < count + 1; i++) {
        fowl->vtx[i * 2].ob[0] = 0;
        fowl->vtx[i * 2 + 1].ob[0] = cel->sizeX;
        fowl->vtx[i * 2].ob[1] = fowl->vtx[i * 2 + 1].ob[1] = -i * rows;
        fowl->vtx[i * 2].tc[0] = 0;
        fowl->vtx[i * 2 + 1].tc[0] = cel->sizeX << 6;
        fowl->vtx[i * 2].tc[1] = (i * rows) << 6;
        fowl->vtx[i * 2 + 1].tc[1] = (i * rows) << 6;
        for (j = 0; j < 2; j++) {
            fowl->vtx[i * 2 + j].ob[2] = 0;
            fowl->vtx[i * 2 + j].cn[0] = 0xFF;
            fowl->vtx[i * 2 + j].cn[1] = 0xFF;
            fowl->vtx[i * 2 + j].cn[2] = 0xFF;
            fowl->vtx[i * 2 + j].cn[3] = 0xFF;
        }
    }
    if (remainder != 0) {
        fowl->vtx[i * 2].ob[0] = 0;
        fowl->vtx[i * 2 + 1].ob[0] = cel->sizeX;
        fowl->vtx[i * 2].ob[1] = fowl->vtx[i * 2 + 1].ob[1] = cel->sizeY;
        fowl->vtx[i * 2].tc[0] = 0;
        fowl->vtx[i * 2 + 1].tc[0] = cel->sizeX << 6;
        fowl->vtx[i * 2].tc[1] = fowl->vtx[i * 2 + 1].tc[1] = cel->sizeY << 6;
        for (j = 0; j < 2; j++) {
            fowl->vtx[i * 2 + j].ob[2] = 0;
            fowl->vtx[i * 2 + j].cn[0] = 0xFF;
            fowl->vtx[i * 2 + j].cn[1] = 0xFF;
            fowl->vtx[i * 2 + j].cn[2] = 0xFF;
            fowl->vtx[i * 2 + j].cn[3] = 0xFF;
        }
    } else if (count == 1) {
        fowl->vtx[4].ob[0] = cel->sizeX * 0.5;
        fowl->vtx[4].ob[1] = -cel->sizeY * 0.5;
        fowl->vtx[4].ob[2] = 0;
        fowl->vtx[4].tc[0] = cel->sizeX * 0.5 * 64.0;
        fowl->vtx[4].tc[1] = cel->sizeY * 0.5 * 64.0;
        fowl->vtx[4].cn[0] = 0xFF;
        fowl->vtx[4].cn[1] = 0xFF;
        fowl->vtx[4].cn[2] = 0xFF;
        fowl->vtx[4].cn[3] = 0xFF;
    }
    m258_BillboardGfxBuild(fowl);
}

void m258_BillboardSprReplace(s16 index, s16 spriteId) {
    FowlPlayBillboard *fowl;

    if (index != -1) {
        fowl = m258_billboardTbl + index;
        fowl->sprite = HuSprAnimTbl[spriteId];
        fowl->unk_20 = 0x100;
        fowl->unk_1F = 0xFF;
        fowl->unk_1E = 0xFF;
        fowl->unk_1D = 0xFF;
        fowl->unk_2C = 0;
        fowl->unk_24 = 0;
        fowl->unk_30.x = 1.0f;
    }
}

void m258_BillboardPatSet(s16 arg0, s16 arg1) {
    if (arg0 != -1) {
        FowlPlayBillboard *fowl = m258_billboardTbl + arg0;
        fowl->unk_24 = arg1;
        fowl->unk_2C = 0;
    }
}

void m258_BillboardAnimSpeedSet(s16 arg0, f32 arg1) {
    if (arg0 != -1) {
        FowlPlayBillboard *fowl = m258_billboardTbl + arg0;
        fowl->unk_30.x = arg1;
    }
}

void m258_BillboardCenterSet(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg0 != -1) {
        FowlPlayBillboard *fowl = m258_billboardTbl + arg0;
        fowl->unk_28 |= 0x4000000;
        fowl->unk_30.y = arg1;
        fowl->unk_30.z = arg2;
        fowl->unk_3C = arg3;
    }
}

void m258_BillboardCenterZSet(s16 arg0, f32 arg1) {
    if (arg0 != -1) {
        FowlPlayBillboard *fowl = m258_billboardTbl + arg0;
        fowl->unk_3C = arg1;
    }
}

void m258_BillboardPosSet(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg0 != -1) {
        FowlPlayBillboard *fowl = m258_billboardTbl + arg0;
        fowl->unk_40.x = arg1;
        fowl->unk_40.y = arg2;
        fowl->unk_40.z = arg3;
    }
}

void m258_BillboardPosAdd(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg0 != -1) {
        FowlPlayBillboard *fowl = m258_billboardTbl + arg0;
        fowl->unk_40.x += arg1;
        fowl->unk_40.y += arg2;
        fowl->unk_40.z += arg3;
    }
}

void m258_BillboardScaleSet(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg0 != -1) {
        FowlPlayBillboard *fowl = m258_billboardTbl + arg0;
        fowl->unk_4C.x = arg1;
        fowl->unk_4C.y = arg2;
        fowl->unk_4C.z = arg3;
    }
}

void m258_BillboardRotSet(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg0 != -1) {
        FowlPlayBillboard *fowl = m258_billboardTbl + arg0;
        fowl->unk_58.x = arg1;
        fowl->unk_58.y = arg2;
        fowl->unk_58.z = arg3;
    }
}

void m258_BillboardAttrSet(s16 arg0, s32 arg1) {
    if (arg0 != -1) {
        FowlPlayBillboard *fowl = m258_billboardTbl + arg0;
        fowl->unk_28 |= arg1;
    }
}

void m258_BillboardAttrReset(s16 arg0, s32 arg1) {
    if (arg0 != -1) {
        FowlPlayBillboard *fowl = m258_billboardTbl + arg0;
        fowl->unk_28 &= ~arg1;
    }
}

s32 m258_BillboardAttrGet(s16 arg0) {
    FowlPlayBillboard *fowl;
    s32 i = arg0;

    if (i != -1) {
        fowl = m258_billboardTbl + i;
        return fowl->unk_28;
    }
    return -1;
}

void m258_BillboardModeSet(s16 arg0, s8 arg1) {
    if (arg0 != -1) {
        FowlPlayBillboard *fowl = m258_billboardTbl + arg0;
        fowl->unk_1A = arg1;
    }
}

FowlPlayBillboard *m258_BillboardGet(s16 arg0) {
    FowlPlayBillboard *fowl;
    s32 i = arg0;

    if (i == -1) {
        return NULL;
    }
    fowl = &m258_billboardTbl[i];
    return fowl;
}

Vtx_t *m258_BillboardVtxGet(s16 arg0) {
    FowlPlayBillboard *fowl;
    s32 i = arg0;

    if (i == -1) {
        return NULL;
    }
    fowl = m258_billboardTbl + i;
    return fowl->vtx;
}

s32 m258_BillboardCenterVtxSet(s16 index, s16 x, s16 y) {
    FowlPlayBillboard *fowl;
    Vtx_t *vtx;

    if (index == -1) {
        return 0;
    }
    fowl = &m258_billboardTbl[index];
    if (fowl->unk_18 != 3) {
        return 0;
    }
    fowl->unk_28 |= 0x80000000;
    vtx = &fowl->vtx[4];
    vtx->ob[0] = x;
    vtx->ob[1] = -y;
    vtx->ob[2] = 0;
    vtx->tc[0] = x * 64;
    vtx->tc[1] = y * 64;
    return 1;
}

void m258_BillboardColorSet(s16 arg0, s8 arg1, s8 arg2, s8 arg3, s16 arg4) {
    s32 i = arg0;

    if (i != -1) {
        FowlPlayBillboard *fowl = m258_billboardTbl + i;
        fowl->unk_1D = arg1;
        fowl->unk_1E = arg2;
        fowl->unk_1F = arg3;
        fowl->unk_20 = arg4;
    }
}

void m258_BillboardKill(s16 index) {
    FowlPlayBillboard *fowl;

    if (index != -1) {
        fowl = &m258_billboardTbl[index];
        if (fowl->sprite != NULL) {
            HuMemFree(fowl->displayList);
            HuMemFree(fowl->vtx);
            fowl->sprite = NULL;
            fowl->unk_28 = 0;
            fowl->unk_20 = 0x100;
            fowl->unk_1F = 0xFF;
            fowl->unk_1E = 0xFF;
            fowl->unk_1D = 0xFF;
            fowl->unk_2C = 0;
            fowl->unk_24 = 0;
            fowl->unk_1C = 0;
            fowl->unk_1B = 0;
            fowl->unk_30.y = fowl->unk_30.z = fowl->unk_3C = 0.0f;
            fowl->unk_40.x = fowl->unk_40.y = fowl->unk_40.z = 0.0f;
            fowl->unk_4C.x = fowl->unk_4C.y = fowl->unk_4C.z = 1.0f;
            fowl->unk_58.x = fowl->unk_58.y = fowl->unk_58.z = 0.0f;
            fowl->unk_30.x = 1.0f;
        }
    }
}

void m258_BillboardDarkSet(s32 index, s32 flag) {
    FowlPlayBillboard *fowl = m258_billboardTbl + index;
    s32 i;

    if (flag != 0) {
        fowl->unk_28 |= 0x10000;
        for (i = 0; i < fowl->unk_18; i++) {
            fowl->vtx[i].cn[0] = 0;
            fowl->vtx[i].cn[1] = 0;
            fowl->vtx[i].cn[2] = 0x80;
        }
        return;
    }
    fowl->unk_28 &= ~0x10000;
    for (i = 0; i < fowl->unk_18; i++) {
        fowl->vtx[i].cn[0] = 0xFF;
        fowl->vtx[i].cn[1] = 0xFF;
        fowl->vtx[i].cn[2] = 0xFF;
        fowl->vtx[i].cn[3] = 0xFF;
    }
}

void m258_BillboardFlipXSet(s32 index, s32 flip) {
    FowlPlayBillboard *fowl = &m258_billboardTbl[index];
    s32 i;

    if (flip) {
        for (i = 0; i < fowl->unk_18; i++) {
            fowl->vtx[i * 2].tc[0] = fowl->sprite->pat->sizeX << 6;
            fowl->vtx[i * 2 + 1].tc[0] = 0;
        }
    } else {
        for (i = 0; i < fowl->unk_18; i++) {
            fowl->vtx[i * 2].tc[0] = 0;
            fowl->vtx[i * 2 + 1].tc[0] = fowl->sprite->pat->sizeX << 6;
        }
    }
}

void m258_BillboardFlipYSet(s32 index, s32 flip) {
    FowlPlayBillboard *fowl = &m258_billboardTbl[index];
    s32 remainder = fowl->sprite->pat->sizeY - (fowl->unk_18 - 2) * fowl->unk_19;
    s32 i;

    if (flip) {
        for (i = 0; i < fowl->unk_18 - 1; i++) {
            fowl->vtx[i * 2].tc[1] = fowl->vtx[i * 2 + 1].tc[1] =
                fowl->sprite->pat->sizeY - i * fowl->unk_19;
        }
        if (remainder != 0) {
            fowl->vtx[i * 2].tc[1] = fowl->vtx[i * 2 + 1].tc[1] = 0;
        }
    } else {
        for (i = 0; i < fowl->unk_18 - 1; i++) {
            fowl->vtx[i * 2].ob[1] = fowl->vtx[i * 2 + 1].ob[1] = i * fowl->unk_19;
        }
        if (remainder != 0) {
            fowl->vtx[i * 2].ob[1] = fowl->vtx[i * 2 + 1].ob[1] = fowl->sprite->pat->sizeY;
        }
    }
}

void m258_BillboardHookSet(s16 arg0, void (*arg1)(struct FowlPlayBillboard *)) {
    if (arg0 != -1) {
        FowlPlayBillboard *fowl = m258_billboardTbl + arg0;
        fowl->callback = arg1;
    }
}

void m258_BillboardTileSet(s16 index, s8 arg1, s8 arg2, s32 flags) {
    FowlPlayBillboard *fowl;

    if (index != -1) {
        fowl = &m258_billboardTbl[index];
        fowl->unk_1B = arg1;
        fowl->unk_1C = arg2;
        fowl->unk_28 |= flags;
        HuMemFree(fowl->displayList);
        m258_BillboardGfxBuild(fowl);
    }
}

void m258_BillboardTintSet(s16 index, s32 flag) {
    FowlPlayBillboard *fowl;
    s8 color;
    s8 blue;
    s32 i;

    if (index != -1) {
        fowl = &m258_billboardTbl[index];
        if (flag) {
            color = 0;
            blue = 0x70;
        } else {
            color = 0xFF;
            blue = 0xFF;
        }
        for (i = 0; i < fowl->unk_18; i++) {
            fowl->vtx[i].cn[0] = fowl->vtx[i].cn[1] = fowl->vtx[i].cn[3] = color;
            fowl->vtx[i].cn[2] = blue;
        }
    }
}

void m258_BillboardBufAlloc(void) {
    FowlPlayBillboard *fowl;
    s32 i;

    if (++m258_billboardBufNo >= 6) {
        m258_billboardBufNo = 0;
    }
    m258_billboardBufSize = 0;
    for (i = 0; i < m258_billboardNum; i++) {
        fowl = &m258_billboardTbl[i];
        if (fowl->sprite != NULL) {
            m258_billboardBufSize += 0x40 + (fowl->unk_22 * sizeof(Gfx) + fowl->unk_18 * 2 * sizeof(Vtx));
        }
    }
    if (m258_billboardBufTbl[m258_billboardBufNo] != NULL) {
        HuMemFree(m258_billboardBufTbl[m258_billboardBufNo]);
    }
    if (m258_billboardBufSize != 0) {
        m258_billboardBufTbl[m258_billboardBufNo] = HuMemAlloc(m258_billboardBufSize);
    } else {
        m258_billboardBufTbl[m258_billboardBufNo] = NULL;
    }
    m258_billboardBufCur = m258_billboardBufTbl[m258_billboardBufNo];
}

void m258_BillboardSort(HuCamera *camera, HuMtx4F lookAt) {
    FowlPlayBillboard tailOpaque;
    FowlPlayBillboard tailTranslucent;
    HuMtx4F unused[16]; // Unreferenced, but present in the stack frame.
    HuMtx4F mtx;
    FowlPlayBillboard *fowl;
    FowlPlayBillboard *node;
    f32 minX;
    f32 maxX;
    f32 minZ;
    f32 maxZ;
    s32 i;

    minX = camera->at.x - 1920.0;
    maxX = camera->at.x + 1920.0;
    minZ = camera->at.z - 1920.0;
    maxZ = camera->at.z + 1920.0;
    m258_billboardOpaHead.unk_64 = 0.0f;
    m258_billboardXluHead.unk_64 = 99999.9f;
    tailOpaque.unk_64 = -99999.9f;
    tailTranslucent.unk_64 = 0.0f;
    m258_billboardXluHead.prev = NULL;
    m258_billboardOpaHead.prev = NULL;
    m258_billboardOpaHead.next = &tailOpaque;
    m258_billboardXluHead.next = &tailTranslucent;
    tailOpaque.prev = &m258_billboardOpaHead;
    tailTranslucent.prev = &m258_billboardXluHead;
    tailTranslucent.next = NULL;
    tailOpaque.next = NULL;
    for (i = 0; i < m258_billboardNum; i++) {
        fowl = &m258_billboardTbl[i];
        if (fowl->sprite == NULL) {
            continue;
        }
        if (fowl->unk_28 & 0x8000) {
            continue;
        }
        if (fowl->unk_40.x < minX || maxX < fowl->unk_40.x) {
            continue;
        }
        if (fowl->unk_40.z < minZ || maxZ < fowl->unk_40.z) {
            continue;
        }
        guTranslateF(mtx, fowl->unk_40.x, fowl->unk_40.y, fowl->unk_40.z);
        guMtxCatF(mtx, lookAt, mtx);
        fowl->unk_64 = mtx[3][2];
        if (fowl->unk_64 > 0.0) {
            continue;
        }
        if ((fowl->unk_28 & 0x1000) && fowl->unk_20 < 0x100) {
            fowl->unk_64 *= -1.0;
            node = &m258_billboardXluHead;
        } else {
            node = &m258_billboardOpaHead;
        }
        for (node = node->next; node->unk_64 > fowl->unk_64; node = node->next) {}
        node->prev->next = fowl;
        fowl->prev = node->prev;
        fowl->next = node;
        node->prev = fowl;
    }
    tailOpaque.prev->next = tailTranslucent.prev->next = NULL;
}

void m258_BillboardDraw(Gfx **gfxP, s32 arg1, s32 arg2) {
    HuCamera *camera = (HuCamera *)arg2;
    Gfx *gfx = *gfxP;
    HuMtx4F unused1[2]; // Unreferenced, but present in the stack frame.
    HuMtx4F lookAt;
    HuMtx4F unused2[4]; // Unreferenced, but present in the stack frame.
    Vec rot;
    Vec dir;
    HuMtx4F unused3[33]; // Unreferenced, but present in the stack frame.
    FowlPlayBillboard *fowl;

    guLookAtF(lookAt, camera->pos.x, camera->pos.y, camera->pos.z, camera->at.x, camera->at.y, camera->at.z,
              camera->up.x, camera->up.y, camera->up.z);
    dir.x = camera->at.x - camera->pos.x;
    dir.y = camera->at.y - camera->pos.y;
    dir.z = camera->at.z - camera->pos.z;
    m258_DirRotCalc(&dir, (f32 *)&rot);
    m258_BillboardBufAlloc();
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_2CYCLE);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING | G_TEXTURE_GEN);
    gSPSetGeometryMode(gfx++, G_SHADE | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    m258_BillboardSort(camera, lookAt);
    for (fowl = m258_billboardOpaHead.next; fowl != NULL; fowl = fowl->next) {
        gfx = m258_BillboardEntryDraw(gfx, fowl, lookAt, &rot);
    }
    for (fowl = m258_billboardXluHead.next; fowl != NULL; fowl = fowl->next) {
        gfx = m258_BillboardEntryDraw(gfx, fowl, lookAt, &rot);
    }
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    *gfxP = gfx;
    if (!Hu3DPauseF) {
        m258_BillboardAnimUpdate();
    }
}

Gfx *m258_BillboardEntryDraw(Gfx *gfx, FowlPlayBillboard *fowl, HuMtx4F lookAt, Vec *rot) {
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

    cel = &fowl->sprite->pat[fowl->unk_24];
    gDPPipeSync(gfx++);
    gDPSetTextureFilter(gfx++, m258_texFilterTbl[(fowl->unk_28 >> 2) & 3]);
    gDPSetColorDither(gfx++, m258_colorDitherTbl[(fowl->unk_28 >> 4) & 3]);
    gDPSetAlphaCompare(gfx++, m258_alphaCompareTbl[(fowl->unk_28 >> 22) & 3]);
    if (fowl->unk_28 & 0x10000) {
        gSPSetGeometryMode(gfx++, G_LIGHTING);
    } else {
        gSPClearGeometryMode(gfx++, G_LIGHTING);
    }
    format = fowl->sprite->pixelBits;
    blend = 0x110000;
    if (fowl->unk_28 & 0x8000000) {
        blend = 0xC8004000;
    }
    if (fowl->unk_28 & 0x1000) {
        if (format & 0x8000) {
            mode = 0x4850;
            blend = 0x100000;
            if (fowl->unk_20 == 0x100) {
                gDPSetCombineMode(gfx++, FOWL_CC_PRIM_DECALA, FOWL_CC_MODULATEI_PASSA2);
            } else {
                gDPSetCombineMode(gfx++, FOWL_CC_PRIM_MODULATEA, G_CC_MODULATEIA2);
            }
        } else if (fowl->unk_20 == 0x100) {
            mode = 0x3038;
            if (fowl->unk_28 & 0x2000000) {
                gDPSetCombineMode(gfx++, FOWL_CC_BLEND_DECALA, FOWL_CC_MODULATEI_PASSA2);
            } else {
                gDPSetCombineMode(gfx++, G_CC_MODULATEIDECALA, FOWL_CC_MODULATEI_PASSA2);
            }
        } else {
            mode = 0x4850;
            blend = 0x100000;
            if (fowl->unk_28 & 0x2000000) {
                gDPSetCombineMode(gfx++, FOWL_CC_BLEND_MODULATEA, G_CC_MODULATEIA2);
            } else {
                gDPSetCombineMode(gfx++, FOWL_CC_MODULATEI_PRIMA, G_CC_MODULATEIA2);
            }
        }
    } else {
        mode = 0x2030;
        if (fowl->unk_28 & 0x2000000) {
            gDPSetCombineMode(gfx++, FOWL_CC_BLEND_MODULATEA, G_CC_PASS2);
        } else {
            gDPSetCombineMode(gfx++, FOWL_CC_MODULATEI_PRIMA, G_CC_PASS2);
        }
    }
    switch ((fowl->unk_28 >> 10) & 3) {
        case 0:
            mode |= 0x200;
            break;
        case 2:
            mode |= 0x40;
            if (fowl->unk_28 & 0x1000) {
                mode |= 0x180;
            }
        case 1:
            mode |= 0x8;
            break;
    }
    if (fowl->unk_28 & 0x2000) {
        mode |= 0xC00;
    }
    if (fowl->unk_28 & 0x8000000) {
        gSPSetGeometryMode(gfx++, G_FOG);
        gDPSetRenderMode(gfx++, G_RM_FOG_SHADE_A, mode | blend);
    } else {
        gSPClearGeometryMode(gfx++, G_FOG);
        gDPSetRenderMode(gfx++, G_RM_PASS, mode | blend);
    }
    gDPSetPrimColor(gfx++, 0, 0, fowl->unk_1D, fowl->unk_1E, fowl->unk_1F, fowl->unk_20);
    vtx = m258_billboardBufCur;
    mtxL = (Mtx *)&vtx[fowl->unk_18 * 2];
    dl = (Gfx *)&mtxL[1];
    m258_billboardBufCur = &dl[fowl->unk_22];
    guMtxIdentF(billboard);
    if (fowl->unk_28 & 0x4000000) {
        billboard[3][0] = -fowl->unk_30.y;
        billboard[3][1] = fowl->unk_30.z;
    } else {
        billboard[3][0] = -(u16)cel->centerX;
        billboard[3][1] = (u16)cel->centerY;
    }
    billboard[3][2] = fowl->unk_3C;
    mtxCopy(mtx, lookAt);
    mtxTransCat(mtx, fowl->unk_40.x, fowl->unk_40.y, fowl->unk_40.z);
    switch (fowl->unk_1A) {
        case 0:
            mtxRotCat(mtx, fowl->unk_58.x, fowl->unk_58.y, fowl->unk_58.z);
            mtxScaleCat(mtx, fowl->unk_4C.x, fowl->unk_4C.y, fowl->unk_4C.z);
            break;
        case 2:
            mtxRotCat(mtx, fowl->unk_58.x, fowl->unk_58.y + rot->y, fowl->unk_58.z);
            mtxScaleCat(mtx, fowl->unk_4C.x, fowl->unk_4C.y, fowl->unk_4C.z);
            break;
        case 1:
        case 4:
            break;
        case 7:
            mtxRotCat(mtx, fowl->unk_58.x, fowl->unk_58.y, fowl->unk_58.z);
            mtxScaleCat(mtx, fowl->unk_4C.x, fowl->unk_4C.y, fowl->unk_4C.z);
            scale[0][0] = fowl->unk_4C.x;
            scale[1][1] = fowl->unk_4C.y;
            scale[2][2] = fowl->unk_4C.z;
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
    memcpy(vtx, fowl->vtx, fowl->unk_18 * 2 * sizeof(Vtx));
    memcpy(dl, fowl->displayList, fowl->unk_22 * sizeof(Gfx));
    if (!(fowl->unk_28 & 0x8000)) {
        gSPDisplayList(gfx++, dl);
    }
    return gfx;
}

void m258_BillboardAnimUpdate(void) {
    FowlPlayBillboard *fowl;
    s32 frameCount;
    s32 i;

    for (i = 0; i < m258_billboardNum; i++) {
        fowl = &m258_billboardTbl[i];
        if (fowl->callback != NULL) {
            fowl->callback(fowl);
        }
        if (fowl->sprite == NULL) {
            continue;
        }
        if (fowl->unk_28 & 0x8000) {
            continue;
        }
        if (fowl->unk_28 & 0x10000000) {
            continue;
        }
        frameCount = fowl->sprite->patNum;
        fowl->unk_2C += fowl->unk_30.x;
        while (fowl->unk_2C >= 1.0) {
            fowl->unk_24++;
            fowl->unk_2C -= 1.0f;
            if (fowl->unk_24 >= frameCount) {
                if (fowl->unk_28 & 0x20000000) {
                    fowl->unk_28 |= 0x8000;
                    fowl->unk_24--;
                    fowl->unk_2C += 1.0f;
                    if (fowl->unk_28 & 0x40000000) {
                        m258_BillboardKill(i);
                    }
                    break;
                }
                if (fowl->unk_28 & 0x40000000) {
                    fowl->unk_24--;
                    break;
                }
                fowl->unk_24 = 0;
            }
        }
    }
}

void m258_BillboardClose(void) {
    s32 i;

    for (i = 0; i < m258_billboardNum; i++) {
        m258_BillboardKill(i);
    }
    for (i = 0; i < 6; i++) {
        if (m258_billboardBufTbl[i] != NULL) {
            HuMemFree(m258_billboardBufTbl[i]);
        }
    }
    HuMemFree(m258_billboardTbl);
}
