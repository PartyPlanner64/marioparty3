#include "common.h"
#include "overlays/minigame.h"
#include "game/hmfmath.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"
#include "game/texload.h"

#define PLAYER_WORK(obj) ((FowlPlayerWork *)((func_800E1BA8_minigame_ObjData *)(obj)->data)->unk158)

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
} FowlSetupWork; // Size 0xB4

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
} FowlFoxWork; // Size 0x2B8

typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec prevPos;
    /* 0x18 */ u16 buttons;
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

typedef struct Fowl {
    /* 0x00 */ Gfx *displayList;
    /* 0x04 */ Vtx_t *vtx;
    /* 0x08 */ HuSprite_Unk84_Struct *sprite;
    /* 0x0C */ struct Fowl *prev;
    /* 0x10 */ struct Fowl *next;
    /* 0x14 */ void (*callback)(struct Fowl *);
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
} Fowl; // sizeof 0x68

extern HuSprite_Unk84_Struct *D_800C9530_main[];
extern s32 D_800A178C_main[][6];

extern s32 D_8010E7A4_fowl_play;
extern s32 D_8010E7AC_fowl_play;
extern s16 D_8010E7B2_fowl_play;
extern FowlWall D_8010E7B4_fowl_play[8];
extern u8 D_8010E87C_fowl_play;
extern Vec D_8010E884_fowl_play[];
extern f32 D_8010E8B4_fowl_play[];
extern s32 D_8010E8C4_fowl_play;
extern u32 D_8010E8C8_fowl_play;
extern s32 D_8010E8CC_fowl_play[];
extern s16 D_8010E8DC_fowl_play[];
extern s16 D_8010EA14_fowl_play[];
extern s16 D_8010EB4C_fowl_play[];
extern s16 D_8010EB54_fowl_play[];
extern s16 D_8010EB5C_fowl_play[];
extern s32 D_8010EB64_fowl_play;
extern s16 D_8010F200_fowl_play;
extern s16 D_8010F202_fowl_play;
extern D_80111B50_vine_with_me_Struct D_8010F208_fowl_play;
extern s16 D_8010F230_fowl_play[];
extern s16 D_8010F234_fowl_play;
extern s16 D_8010F238_fowl_play;
extern s16 D_8010F240_fowl_play[];
extern omObjData *D_8010F290_fowl_play[1];
extern omObjData *D_8010F294_fowl_play[2];
extern s16 D_8010F29C_fowl_play;
extern s16 D_8010F29E_fowl_play;
extern s16 D_8010F2A0_fowl_play;
extern f32 D_8010F2A8_fowl_play[4][4];
extern f32 D_8010F2E0_fowl_play;
extern f32 D_8010F2E8_fowl_play[4][4];
extern f32 D_8010F328_fowl_play;
extern Fowl *D_8010F32C_fowl_play;
extern void *D_8010F330_fowl_play[6];
extern void *D_8010F348_fowl_play;
extern s32 D_8010F34C_fowl_play;
extern s32 D_8010F350_fowl_play;
extern Fowl D_8010F360_fowl_play; // List head of opaque entries
extern Fowl D_8010F3C8_fowl_play; // List head of translucent entries

void func_80105BEC_fowl_play(omObjData *object);
void func_80105E4C_fowl_play(omObjData *object);
void func_80106528_fowl_play(HuMtx4F src, HuMtx4F dst);
void func_801068F0_fowl_play(void);
void func_80106960_fowl_play(omObjData *object);
void func_80106BD0_fowl_play(omObjData *object);
void func_801070FC_fowl_play(omObjData *object, f32 radius);
u8 func_8010724C_fowl_play(Vec *pos, Vec *prev, f32 radius);
void func_801079B0_fowl_play(void);
void func_80107A4C_fowl_play(omObjData *object);
void func_80108298_fowl_play(omObjData *object);
u16 func_80108B08_fowl_play(omObjData *object);
void func_80109410_fowl_play(omObjData *object, func_800E1BA8_minigame_ObjData **data, FowlPlayerWork **work);
void func_80109424_fowl_play(void);
void func_801094A4_fowl_play(omObjData *object);
void func_80109844_fowl_play(omObjData *object);
u8 func_8010A738_fowl_play(omObjData *object, u8 canCatch);
s32 func_8010A9A0_fowl_play(void);
f32 func_8010A9EC_fowl_play(f32 y, f32 x);
f32 func_8010AA64_fowl_play(Vec *arg0, Vec *arg1);
f32 func_801075B0_fowl_play(Vec *pos, f32 dist, f32 dir);
f32 func_8010AB40_fowl_play(Vec *vec);
f32 func_8010AC88_fowl_play(Vec *point, Vec *start, Vec *end, Vec *closest);
f32 func_8010AE10_fowl_play(Vec *pos1, Vec *dir1, Vec *pos2, Vec *dir2);
void func_8010B1A0_fowl_play(s16 model, char *hook, s16 time, Vec *pos);
s16 func_8010B2C4_fowl_play(s32 dataNum);
s16 func_8010B30C_fowl_play(s16 spriteId, s16 count);
void func_8010B41C_fowl_play(u16 count);
s16 func_8010B8D4_fowl_play(Fowl *fowl);
s16 func_8010C1F4_fowl_play(s16 spriteId, s32 flags);
void func_8010CE04_fowl_play(s16 arg0, s16 arg1);
void func_8010CE44_fowl_play(s16 arg0, f32 arg1);
void func_8010CF24_fowl_play(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_8010CFDC_fowl_play(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_8010D02C_fowl_play(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_8010D07C_fowl_play(s16 arg0, s32 arg1);
void func_8010D0C0_fowl_play(s16 arg0, s32 arg1);
s32 func_8010D108_fowl_play(s16 arg0);
void func_8010D148_fowl_play(s16 arg0, s8 arg1);
void func_8010D2A4_fowl_play(s16 arg0, s8 arg1, s8 arg2, s8 arg3, s16 arg4);
void func_8010D2F0_fowl_play(s16 index);
void func_8010DC24_fowl_play(Gfx **gfxP, s32 arg1, s32 arg2);
Gfx *func_8010DE4C_fowl_play(Gfx *gfx, Fowl *fowl, HuMtx4F lookAt, Vec *rot);
void func_8010E544_fowl_play(void);
void func_8010E704_fowl_play(void);

void func_801059A0_fowl_play(void) {
    omObjData *obj;

    func_8001FE20_main(1);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    omInitObjMan(0x14, 0);
    func_8004A208_main();
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -56.0f, 50.0f, 56.0f);
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    obj->work[0] = 2;
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    ScissorSet(0, 0.0f, 0.0f, 160.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 45.0f, 80.0f, 8000.0f);
    ScissorSet(1, 160.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(1, 45.0f, 80.0f, 8000.0f);
    func_800E1804_minigame();
    func_80105BEC_fowl_play(obj);
    func_8010B41C_fowl_play(0x80);
    func_801068F0_fowl_play();
    memset(&D_8010F208_fowl_play, 0, sizeof(D_8010F208_fowl_play));
    D_8010F208_fowl_play.unk01 = 4;
    func_800E5EA0_minigame(&D_8010F208_fowl_play);
    func_801079B0_fowl_play();
    D_8010F2A0_fowl_play = 0;
    func_80109424_fowl_play();
    Hu3DBGColorSet(0, 0, 0);
    WipeCreateIn(0xFF, 0x10);
}

void func_80105BEC_fowl_play(omObjData *object) {
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
    D_8010F328_fowl_play = sinFov / cosFov;
    guMtxL2F(D_8010F2A8_fowl_play, &camera->mtxs[0].lookAtMtx);
    guMtxL2F(D_8010F2E8_fowl_play, &camera->mtxs[0].lookAtMtx);
    func_80106528_fowl_play(D_8010F2E8_fowl_play, D_8010F2E8_fowl_play);
    for (i = 0; i < 2; i++) {
        obj = D_8010F294_fowl_play[i] = omAddObj(6, 1, 0, -1, func_80105E4C_fowl_play);
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

void func_80105E4C_fowl_play(omObjData *object) {
    FowlCameraWork *work;
    func_800E1BA8_minigame_ObjData *data;
    FowlPlayerWork *playerWork;
    HuMtx4F unusedMtx; // Unreferenced, but present in the stack frame.
    Vec unusedVec;     // Unreferenced, but present in the stack frame.
    HuCamera *camera;
    f32 playerRot;
    f32 diff;
    u8 index;

    if (D_8010F29C_fowl_play >= 8) {
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
    func_80109410_fowl_play(work->player, &data, &playerWork);
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
            func_8010A9EC_fowl_play(camera->pos.x - work->player->trans.x, camera->pos.z - work->player->trans.z);
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

void func_801064A8_fowl_play(HuMtx4F mtx, f32 x, f32 y, f32 z, f32 *dst) {
    dst[0] = ((x * mtx[0][0]) + (y * mtx[1][0])) + (z * mtx[2][0]);
    dst[1] = ((x * mtx[0][1]) + (y * mtx[1][1])) + (z * mtx[2][1]);
    dst[2] = ((x * mtx[0][2]) + (y * mtx[1][2])) + (z * mtx[2][2]);
}

void func_80106528_fowl_play(HuMtx4F src, HuMtx4F dst) {
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

        func_801064A8_fowl_play(dst, -mtx[3][0], -mtx[3][1], -mtx[3][2], dstRow3);
    }
}

void func_80106718_fowl_play(f32 *pos, f32 *dst) {
    f32 mtx[4][4];
    f32 depth;
    f32 scale;

    guTranslateF(mtx, pos[0], pos[1], pos[2]);
    guMtxCatF(mtx, D_8010F2A8_fowl_play, mtx);
    depth = mtx[3][2] * D_8010F328_fowl_play;
    scale = fabsf(depth);
    if (scale != 0.0) {
        dst[0] = mtx[3][0] * 160.0f / scale / 1.3333334f;
        dst[1] = -mtx[3][1] * 120.0f / scale;
    }
    dst[0] += 160.0;
    dst[1] += 120.0;
    dst[2] = scale;
}

void func_80106824_fowl_play(f32 x, f32 y, f32 z, f32 *dst) {
    f32 depth = z + D_8010F2E0_fowl_play;
    f32 scale = fabsf(depth * D_8010F328_fowl_play);
    f32 mtx[4][4];

    guTranslateF(mtx, (x + x) * scale * 1.3333334f / 320.0f, -((y + y) * scale / 240.0f), depth);
    guMtxCatF(mtx, D_8010F2E8_fowl_play, mtx);
    dst[0] = mtx[3][0];
    dst[1] = mtx[3][1];
    dst[2] = mtx[3][2];
}

void func_801068F0_fowl_play(void) {
    D_800EBE28_minigame = 0;
    func_800E1490_minigame(0);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(5, 1, 0, -1, func_80106960_fowl_play);
    D_8010F29C_fowl_play = 0;
}

void func_80106960_fowl_play(omObjData *object) {
    Vec unused[16] = { { -500.0f, 0.0f, -1550.0f }, { -1050.0f, 0.0f, -1450.0f }, { -300.0f, 0.0f, -2245.0f }, { -1400.0f, 0.0f, -600.0f }, { -1700.0f, 0.0f, 400.0f }, { -1550.0f, 0.0f, 800.0f }, { -400.0f, 0.0f, 2150.0f }, { -1300.0f, 0.0f, 1450.0f }, { 750.0f, 0.0f, 1650.0f }, { 1450.0f, 0.0f, 1600.0f }, { 450.0f, 0.0f, 2150.0f }, { 1550.0f, 0.0f, 800.0f }, { 2000.0f, 0.0f, 500.0f }, { 1550.0f, 0.0f, -800.0f }, { 400.0f, 0.0f, -2150.0f }, { 1150.0f, 0.0f, -1200.0f } };
    FowlSetupWork *work;

    work = HuMemAllocTag(sizeof(FowlSetupWork), TAG_OVERLAY);
    object->data = work;
    memset(work, 0, sizeof(FowlSetupWork));
    work->unk03 = 1;
    work->unk04 = 0;
    func_800E131C_minigame(object, 20.0f);
    func_800E1304_minigame(object, 0.5f);
    func_800E1310_minigame(object, 10.0f);
    func_800E1404_minigame(object, 0.0f, 1200.0f);
    D_8010F230_fowl_play[0] = func_8010B2C4_fowl_play(0x5B0000);
    D_8010F240_fowl_play[0] = func_8010B30C_fowl_play(D_8010F230_fowl_play[0], 2);
    HuSprPosSet(D_8010F240_fowl_play[0], 0, 0, 0);
    HuSprAttrSet(D_8010F240_fowl_play[0], 0, 0x44000);
    func_80055588_main(D_8010F240_fowl_play[0], 0, 2.0f, 1.0f);
    func_800555B8_main(D_8010F240_fowl_play[0], 0, 8, 7);
    HuSprScissorSet(D_8010F240_fowl_play[0], 0, 0, 0, 159, 240);
    HuSprPosSet(D_8010F240_fowl_play[0], 1, 160, 0);
    HuSprAttrSet(D_8010F240_fowl_play[0], 1, 0x44000);
    func_80055588_main(D_8010F240_fowl_play[0], 1, 2.0f, 1.0f);
    func_800555B8_main(D_8010F240_fowl_play[0], 1, 8, 7);
    HuSprScissorSet(D_8010F240_fowl_play[0], 1, 161, 0, 320, 240);
    D_8010F230_fowl_play[1] = func_8010B2C4_fowl_play(0x5B0004);
    D_8010F240_fowl_play[1] = func_8010B30C_fowl_play(D_8010F230_fowl_play[1], 1);
    HuSprPosSet(D_8010F240_fowl_play[1], 0, 160, 120);
    HuSprAttrSet(D_8010F240_fowl_play[1], 0, 0x1000);
    object->model[0] = func_8000B108_main(0x5B0005, 0x2D9);
    Hu3DModelCameraSet(object->model[0], 3);
    object->func = func_80106BD0_fowl_play;
}

void func_80106BD0_fowl_play(omObjData *object) {
    HuSprite *sprite;
    f32 x;
    s32 i;

    switch (D_8010F29C_fowl_play) {
        case 0:
            Hu3DModelCameraSet(Hu3DHookFuncCreate(0xC0, func_8010DC24_fowl_play, 2), 3);
            GMesCreate(6);
            D_8010F200_fowl_play = HuAudFXPlay(0x4BF);
            D_8010F29E_fowl_play = 1800;
            D_8010F29C_fowl_play++;
        case 1:
            if (WipeStatGet() == 0 && ++D_8010E7B2_fowl_play == 1) {
                HuAudSeqPlay(0x36);
            }
            if (GMesStatGet() == 0) {
                func_800E6F0C_minigame(2);
                D_8010F29C_fowl_play++;
                GMesCreate(0x1A, (D_8010F29E_fowl_play + 29) / 30, 0xA0, 0x20);
                HuAudFXPlay(0xE);
            }
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                if (PLAYER_WORK(D_800EC598_minigame[i])->unk24) {
                    D_8010E7AC_fowl_play = i;
                    D_8010F29C_fowl_play = 3;
                }
            }
            D_8010F29E_fowl_play--;
            func_8003F578_main((D_8010F29E_fowl_play + 29) / 30);
            if (D_8010F29E_fowl_play == 0) {
                D_8010F29C_fowl_play = 3;
            }
            break;
        case 3:
            func_8003F5C0_main();
            GMesCreate(0x11);
            HuAudSeqFadeOut(0x78);
            D_8010F29C_fowl_play = 6;
            D_8010E7A4_fowl_play = 15;
            D_8010F202_fowl_play = 15;
            break;
        case 6:
            if (--D_8010F202_fowl_play == 0) {
                func_8004AEF0_main(D_8010F200_fowl_play, 15);
            }
            if (GMesStatGet() != 0) {
                break;
            }
            if (--D_8010E7A4_fowl_play != 0) {
                break;
            }
            for (i = 0; i < 2; i++) {
                if (PLAYER_WORK(D_800EC598_minigame[i])->unk24) {
                    D_8010E7AC_fowl_play = i;
                }
            }
            if (D_8010E7AC_fowl_play != -1) {
                GMesCreate(0x16, PLAYER_WORK(D_800EC598_minigame[D_8010E7AC_fowl_play])->character);
                HuAudSeqPlay(0x67);
            } else {
                GMesCreate(0x20);
                HuAudSeqPlay(0x6C);
            }
            D_8010E7A4_fowl_play = 15;
            D_8010F29C_fowl_play++;
            func_800E6F0C_minigame(4);
            break;
        case 7:
            if (GMesStatGet() != 0) {
                break;
            }
            if (--D_8010E7A4_fowl_play == 0) {
                D_8010F29C_fowl_play++;
            }
            break;
        case 8:
            if (D_8010E7A4_fowl_play != 0) {
                if (--D_8010E7A4_fowl_play == 0) {
                    D_8010F29C_fowl_play++;
                }
            } else {
                func_800E6F0C_minigame(5);
                D_8010E7A4_fowl_play = 16;
                WipeCreateOut(WIPE_TYPE_NORMAL, D_8010E7A4_fowl_play);
                HuAudSeqFadeOut(D_8010E7A4_fowl_play);
                func_8004AB0C_main((s16)D_8010E7A4_fowl_play);
            }
            break;
        case 9:
            func_8010E704_fowl_play();
            HuAudSeqStop();
            omOvlReturnEx(1);
            break;
    }
    for (i = 0; i < 2; i++) {
        sprite = HuSprGet(D_8010F240_fowl_play[0], i);
        x = CRotM[i].y * 256.0 / 360.0 - 256.0 + i * 160;
        HuSprPosSet(D_8010F240_fowl_play[0], i, x, 0);
        sprite->pos.x = x;
    }
    if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010F29C_fowl_play = 8;
    }
}

void func_801070FC_fowl_play(omObjData *object, f32 radius) {
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
        if (func_8010AC88_fowl_play(&object->trans, &D_8010E7B4_fowl_play[i].start, &D_8010E7B4_fowl_play[i].end,
                                    &closest) >= radius) {
            continue;
        }
        dir.x = object->trans.x - closest.x;
        dir.y = 0.0f;
        dir.z = object->trans.z - closest.z;
        func_8010AB40_fowl_play(&dir);
        object->trans.x = radius * dir.x + closest.x;
        object->trans.z = radius * dir.z + closest.z;
    }
}

u8 func_8010724C_fowl_play(Vec *pos, Vec *prev, f32 radius) {
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
    func_8010A9EC_fowl_play(move.x, move.z);
    radius += 20.0;
    for (i = 0; i < 8; i++) {
        wall.x = D_8010E7B4_fowl_play[i].end.x - D_8010E7B4_fowl_play[i].start.x;
        wall.y = D_8010E7B4_fowl_play[i].end.y - D_8010E7B4_fowl_play[i].start.y;
        wall.z = D_8010E7B4_fowl_play[i].end.z - D_8010E7B4_fowl_play[i].start.z;
        c = wall.x * D_8010E7B4_fowl_play[i].start.z - wall.z * D_8010E7B4_fowl_play[i].start.x;
        nz = -wall.z;
        if ((nz * pos->x + wall.x * pos->z - c) * (nz * prev->x + wall.x * prev->z - c) > 0.0f) {
            continue;
        }
        t = func_8010AE10_fowl_play(&D_8010E7B4_fowl_play[i].start, &wall, pos, &move);
        if (t > 1.0) {
            continue;
        }
        if (t < 0.0) {
            continue;
        }
        hit.x = t * wall.x + D_8010E7B4_fowl_play[i].start.x;
        hit.y = 0.0f;
        hit.z = t * wall.z + D_8010E7B4_fowl_play[i].start.z;
        dist = func_8010AA64_fowl_play(pos, &hit);
        if (dist >= maxDist) {
            continue;
        }
        if (dist >= minDist) {
            continue;
        }
        minDist = dist;
        func_8010AC88_fowl_play(prev, &D_8010E7B4_fowl_play[i].start, &D_8010E7B4_fowl_play[i].end, &hit);
        wall.x = prev->x - hit.x;
        wall.y = 0.0f;
        wall.z = prev->z - hit.z;
        func_8010AB40_fowl_play(&wall);
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

f32 func_801075B0_fowl_play(Vec *pos, f32 dist, f32 dir) {
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
        wall.x = (D_8010E7B4_fowl_play[i].end.x - D_8010E7B4_fowl_play[i].start.x) * 1.2;
        wall.y = D_8010E7B4_fowl_play[i].end.y - D_8010E7B4_fowl_play[i].start.y;
        wall.z = (D_8010E7B4_fowl_play[i].end.z - D_8010E7B4_fowl_play[i].start.z) * 1.2;
        t = func_8010AE10_fowl_play(&D_8010E7B4_fowl_play[i].start, &wall, pos, &move);
        if (t > 1.0) {
            continue;
        }
        if (t < 0.0) {
            continue;
        }
        hit.x = t * wall.x + D_8010E7B4_fowl_play[i].start.x;
        hit.y = 0.0f;
        hit.z = t * wall.z + D_8010E7B4_fowl_play[i].start.z;
        d = func_8010AA64_fowl_play(pos, &hit);
        if (d > dist) {
            continue;
        }
        if (d > minDist) {
            continue;
        }
        minDist = d;
        angle = func_8010A9EC_fowl_play(wall.x, wall.z);
        diff = func_8010A9EC_fowl_play(pos->x - D_8010E7B4_fowl_play[i].start.x,
                                       pos->z - D_8010E7B4_fowl_play[i].start.z) -
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
        func_8010AC88_fowl_play(&newPos, &D_8010E7B4_fowl_play[i].start, &D_8010E7B4_fowl_play[i].end, &hit);
        wall.x = newPos.x - hit.x;
        wall.y = 0.0f;
        wall.z = newPos.z - hit.z;
        func_8010AB40_fowl_play(&wall);
        newPos.x = hit.x - wall.x * 40.0;
        newPos.z = hit.z - wall.z * 40.0;
    }
    pos->x = newPos.x;
    pos->z = newPos.z;
    return angle;
}

void func_801079B0_fowl_play(void) {
    s32 i;

    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    D_800EC280_minigame = 0;
    for (i = 0; i < 2; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 15, 50, -1, func_80107A4C_fowl_play);
    }
}

const FowlCharMotions D_8010ED88_fowl_play = { { 0, 1, 2, 3, 4, 5, 6, 7 } };

void func_80107A4C_fowl_play(omObjData *object) {
    FowlCharMotions motions = D_8010ED88_fowl_play; // Copied but never read.
    s32 anims[3][8] = {
        // Initialized but never read.
        { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C },
        { 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0x1D },
        { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B },
    };
    func_800E1BA8_minigame_ObjData *data;
    FowlPlayerWork *work;
    s32 i;
    u8 player;
    s8 character;
    u32 model;
    s32 motion;

    for (i = 0; i < 4; i++) {
        if (D_8010E87C_fowl_play == GwPlayer[i].group) {
            break;
        }
    }
    player = i;
    character = GwPlayer[player].chr;
    model = D_800A178C_main[character][0];
    motion = D_800A178C_main[character][1];
    func_800E1BA8_minigame(object, model, motion, player, 0x2D9, 0x2D9);
    data = object->data;
    data->unk50 &= ~1;
    data->unkEC = 0;
    object->trans.x = D_8010E884_fowl_play[D_8010E87C_fowl_play].x;
    object->trans.y = D_8010E884_fowl_play[D_8010E87C_fowl_play].y;
    object->trans.z = D_8010E884_fowl_play[D_8010E87C_fowl_play].z;
    data->unk3C = D_8010E8B4_fowl_play[D_8010E87C_fowl_play];
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
    object->trans.x = D_8010E884_fowl_play[D_8010E87C_fowl_play].x;
    object->trans.y = D_8010E884_fowl_play[D_8010E87C_fowl_play].y;
    object->trans.z = D_8010E884_fowl_play[D_8010E87C_fowl_play].z;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);

    data->unk158 = HuMemAllocTag(sizeof(FowlPlayerWork), TAG_OVERLAY);
    memset(data->unk158, 0, sizeof(FowlPlayerWork));
    work = data->unk158;
    work->player = player;
    work->index = D_8010E87C_fowl_play;
    work->character = character;
    work->unk25 = GwPlayer[player].stat & 1;
    work->unk23 = GwPlayer[player].cpu_difficulty;
    work->unk1C = model | 0x9A;
    work->unk24 = 0;
    work->pos.x = object->trans.x;
    work->pos.y = object->trans.y;
    work->pos.z = object->trans.z;
    work->unk26 = 0;
    ((FowlCameraWork *)D_8010F294_fowl_play[D_8010E87C_fowl_play]->data)->player = object;
    func_800E149C_minigame(object, 0, 2);
    data->unk50 |= 0x8200;
    object->func = func_80108298_fowl_play;
    Hu3DModelCameraSet(object->model[0], 3);
    Hu3DModelCameraSet(object->model[1], 3);
    func_800E5A00_minigame(object, 0, func_80017BB8_main(character, 0), 1, 0);
    func_800E5A00_minigame(object, 1, func_80017BB8_main(character, 1), 1, 0);
    func_800E5A00_minigame(object, 2, func_80017BB8_main(character, 2), 1, 0);
    func_800E5A00_minigame(object, 0x11, func_80017BB8_main(character, 0xE), 0, 0);
    func_800E5A00_minigame(object, 0x20, func_80017BB8_main(character, 0x22), 0, 0);
    func_800E5A00_minigame(object, 6, func_80017BB8_main(character, 4), 1, 0x13);
    func_800E5A00_minigame(object, 0x15, func_80017BB8_main(character, 0x1F), 0, 0x13);
    func_800E5A00_minigame(object, 5, func_80017BB8_main(character, 0x99), 0, 0);
    func_800E5A00_minigame(object, 0x27, func_80017BB8_main(character, 0x96), 1, 0);
    func_800E5A00_minigame(object, 0xD, func_80017BB8_main(character, 0x9A), 1, 0x3C);
    switch (model >> 16) {
        case 3:
        case 4:
        case 5:
            func_800E5A00_minigame(object, 0xE, func_80017BB8_main(character, 0x39), 1, 0x3C);
            break;
        case 2:
        case 6:
        case 7:
        case 8:
        case 9:
            func_800E5A00_minigame(object, 0xE, func_80017BB8_main(character, 0x3A), 1, 0x3C);
            break;
    }
    func_800E5690_minigame(object, 0);
    D_8010E87C_fowl_play++;
}

void func_80108020_fowl_play(omObjData *object, s32 arg1, s32 arg2, u16 player, u16 tag) {
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

    object->model[0] = func_8000B108_main(arg1 | arg2, tag);
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

void func_80108298_fowl_play(omObjData *object) {
    FowlCharMotions motions = D_8010ED88_fowl_play; // Copied but never read.
    Vec pos;
    func_800E1BA8_minigame_ObjData *data;
    func_800E1BA8_minigame_ObjData *otherData;
    FowlPlayerWork *work;
    FowlPlayerWork *otherWork;
    omObjData *other;
    u8 pad;
    u8 canCatch;
    u16 buttons;
    f32 angle;
    f32 mag;
    f32 range;
    f32 dist;
    s32 i;

    data = object->data;
    work = data->unk158;
    pad = data->unk57;
    canCatch = 0;
    if (D_8010F29C_fowl_play != 2) {
        D_800D20A1_main[pad] = 0;
        D_800CBB6E_main[pad] = 0;
        D_800D5558_main[pad] = 0;
        D_800CDA7C_main[pad] = 0;
    }
    switch (D_8010F29C_fowl_play) {
        case 0:
            work->unk2C = work->unk2E = work->unk30 = work->unk32 = work->unk34 = work->unk3C = work->unk3E = 0;
            work->unk36 = 450;
            work->unk26 = 0;
            work->unk27 = 0;
            break;
        case 2:
            if (!work->unk25) {
                angle = func_8010A9EC_fowl_play(D_800CBB6E_main[pad], -D_800D20A1_main[pad]) + CRotM[work->index].y;
                mag = sqrtf(D_800CBB6E_main[pad] * D_800CBB6E_main[pad] + D_800D20A1_main[pad] * D_800D20A1_main[pad]);
                D_800CBB6E_main[pad] = mag * sindf(angle);
                D_800D20A1_main[pad] = -mag * cosdf(angle);
            } else {
                D_800D20A1_main[pad] = 0;
                D_800CBB6E_main[pad] = 0;
                D_800D5558_main[pad] = 0;
                D_800CDA7C_main[pad] = 0;
                func_80108B08_fowl_play(object);
            }
            break;
        case 6:
            if (work->unk24) {
                angle = func_8010A9EC_fowl_play(-object->trans.x, -object->trans.z);
                D_800CBB6E_main[pad] = sindf(angle) * 18.0;
                D_800D20A1_main[pad] = -cosdf(angle) * 18.0;
                Hu3DMotionSpeedSet(object->model[0], 1.0f);
            }
            break;
        case 7:
            work->unk3C = 0;
            if (work->unk24 == 1) {
                GwPlayer[data->unk59].bonusCoin += 10;
                func_800E5690_minigame(object, 0xD);
                func_80045F1C_main(work->unk1C, -1, work->index);
                work->unk24++;
            } else if (work->unk24 == 0) {
                func_800E5690_minigame(object, 0xE);
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
    buttons = D_800D5558_main[pad]; // Overwritten immediately, but needed to match.
    buttons = func_800E4A90_minigame(object);
    work->prevPos.x = object->trans.x;
    work->prevPos.y = object->trans.y;
    work->prevPos.z = object->trans.z;
    if (work->unk3C != 0) {
        D_800D5558_main[pad] &= ~0x4000;
    } else {
        Hu3DData[object->model[0]].motIdShape = 0xFF;
    }
    func_800DDD94_minigame(object);
    if (buttons & 0x40) {
        if (Hu3DData[object->model[0]].motTime >= 16.0 && Hu3DData[object->model[0]].motTime <= 20.0) {
            canCatch = 1;
        }
    }
    if (func_8010A738_fowl_play(object, canCatch)) {
        work->unk3C = 1;
        work->unk24 = 1;
        func_8004AC5C_main(0x4C0, 2);
        func_8004AC5C_main(0x4C2, 3);
        omVibrate(data->unk59, 10, 0, 10);
        Hu3DMotionShapeSet(object->model[0], object->motion[0x27], 0);
    }
    for (i = 0; i < 2; i++) {
        other = D_800EC598_minigame[i];
        if (object == other) {
            continue;
        }
        otherData = other->data;
        otherWork = otherData->unk158;
        if (fabs(object->trans.y - other->trans.y) > 30.0) {
            continue;
        }
        dist = func_8010AA64_fowl_play(&object->trans, &other->trans);
        range = data->unk48 + otherData->unk48;
        if (dist > range) {
            continue;
        }
        if (data->unk40 <= otherData->unk40) {
            angle = func_8010A9EC_fowl_play(other->trans.x - object->trans.x, other->trans.z - object->trans.z);
            other->trans.x = range * sindf(angle) + object->trans.x;
            other->trans.z = range * cosdf(angle) + object->trans.z;
            if (other->trans.y < 30.0) {
                pos.x = otherWork->prevPos.x;
                pos.y = 0.0f;
                pos.z = otherWork->prevPos.z;
                if (func_8010724C_fowl_play(&pos, &other->trans, otherData->unk48)) {
                    other->trans.x = pos.x;
                    other->trans.z = pos.z;
                }
            }
        } else {
            angle = func_8010A9EC_fowl_play(object->trans.x - other->trans.x, object->trans.z - other->trans.z);
            object->trans.x = range * sindf(angle) + other->trans.x;
            object->trans.z = range * cosdf(angle) + other->trans.z;
            if (object->trans.y < 30.0) {
                pos.x = work->prevPos.x;
                pos.y = 0.0f;
                pos.z = work->prevPos.z;
                if (func_8010724C_fowl_play(&pos, &object->trans, data->unk48)) {
                    object->trans.x = pos.x;
                    object->trans.z = pos.z;
                }
            }
        }
    }
    dist = sqrtf(object->trans.x * object->trans.x + object->trans.z * object->trans.z);
    range = 1200.0 - data->unk48 - 10.0;
    if (dist > range) {
        angle = func_8010A9EC_fowl_play(object->trans.x, object->trans.z);
        object->trans.x = range * sindf(angle);
        object->trans.z = range * cosdf(angle);
    }
    func_801070FC_fowl_play(object, data->unk48);
    work->buttons = buttons;
}

void func_80108A70_fowl_play(omObjData *object, f32 x, f32 y, f32 z) {
    s32 i;

    for (i = 9; i < 12; i++) {
        if (Hu3DData[object->model[i]].attr & 4) {
            func_800E4C88_minigame(object, i, x, y, z, 0.0f, 0.0f);
            return;
        }
    }
}

u16 func_80108B08_fowl_play(omObjData *object) {
    Vec corners[4] = { { 1000.0f, 0.0f, 0.0f }, { -1000.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1000.0f }, { 0.0f, 0.0f, -1000.0f } };
    Vec target;
    func_800E1BA8_minigame_ObjData *data;
    FowlPlayerWork *work;
    omObjData *fox;
    FowlFoxWork *foxWork;
    f32 dist;
    f32 angle;
    f32 clear;
    f32 diff;
    u8 press = FALSE;
    s16 pad;
    u16 buttons;

    func_80109410_fowl_play(object, &data, &work);
    pad = data->unk57;
    func_800E4A90_minigame(object);
    fox = D_8010F290_fowl_play[0];
    foxWork = ((func_800E1BA8_minigame_ObjData *)fox->data)->unk158;
    if (D_8010F29E_fowl_play > 1500) {
        target.x = fox->trans.x + sindf(foxWork->unk14) * 60.0;
        target.z = fox->trans.z + cosdf(foxWork->unk14) * 60.0;
    } else {
        target.x = fox->trans.x + (work->unk23 * 0.5 + 1.0) * 20.0 * sindf(foxWork->unk14);
        target.z = fox->trans.z + (work->unk23 * 0.5 + 1.0) * 20.0 * cosdf(foxWork->unk14);
    }
    angle = func_8010A9EC_fowl_play(target.x - object->trans.x, target.z - object->trans.z);
    dist = func_8010AA64_fowl_play(&object->trans, &fox->trans);
    work->unk36--;
    switch (work->unk2C) {
        case 0:
            if (dist < (work->unk23 * 5.0 + 20.0) * 20.0) {
                work->unk2C = 1;
            }
            if (work->unk32 != 0) {
                f32 cornerDist = func_8010AA64_fowl_play(&object->trans, &corners[work->unk32 - 1]);

                angle = func_8010A9EC_fowl_play(corners[work->unk32 - 1].x - object->trans.x,
                                                corners[work->unk32 - 1].z - object->trans.z);
                if (cornerDist < 200.0) {
                    work->unk32 = 0;
                }
            } else {
                work->unk32 = (s32)((f32)func_8010A9A0_fowl_play() * 1.52587890625e-05 * 4.0) + 1;
            }
            if (work->unk36 == 0) {
                work->unk2C = 2;
                work->unk36 = work->unk23 * 20 + (s16)((s32)((f32)func_8010A9A0_fowl_play() * 1.52587890625e-05 * 40.0) + 30);
            }
            break;
        case 1:
            if (dist >= (work->unk23 * 5.0 + 25.0) * 20.0) {
                work->unk2C = 0;
            }
            if (work->unk2E == 0) {
                work->unk2E = (s32)((f32)func_8010A9A0_fowl_play() * 1.52587890625e-05 * 60.0) + 10;
                work->unk30 = (f32)(func_8010A9A0_fowl_play() - 0x8000) * 3.0517578125e-05 * (55 - work->unk23 * 5);
            }
            work->unk2E--;
            if (dist < data->unk48 + foxWork->unk0C + 26.0) {
                if (D_8010F29E_fowl_play > 1260) {
                    work->unk34 = 3;
                } else if ((s32)((f32)func_8010A9A0_fowl_play() * 1.52587890625e-05 * (6 - work->unk23)) == 0) {
                    press = TRUE;
                }
            } else if (work->unk34 != 0) {
                if (--work->unk34 == 0) {
                    press = TRUE;
                }
            }
            if (work->unk36 == 0) {
                work->unk2C = 2;
                work->unk36 = work->unk23 * 15 + (s16)((s32)((f32)func_8010A9A0_fowl_play() * 1.52587890625e-05 * 30.0) + 30);
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
                    135.0 - work->unk23 * 20 + (s32)((f32)func_8010A9A0_fowl_play() * 1.52587890625e-05 * 60.0);
            }
            break;
    }
    angle += work->unk30;
    D_800CBB6E_main[pad] = (work->unk23 * 2.0 + 56.0) * sindf(angle);
    D_800D20A1_main[pad] = (work->unk23 * 2.0 + 56.0) * -cosdf(angle);
    if (press) {
        D_800D5558_main[pad] |= B_BUTTON;
    }
    target.x = object->trans.x;
    target.y = 0.0f;
    target.z = object->trans.z;
    clear = func_801075B0_fowl_play(&target, 120.0f, angle);
    diff = angle - data->unk3C;
    while (diff < -180.0) {
        diff += 360.0;
    }
    while (diff > 180.0) {
        diff -= 360.0;
    }
    if (clear != angle) {
        if (fabs(diff) < 30.0) {
            D_800D5558_main[pad] |= A_BUTTON;
        }
    }
    return buttons;
}

void func_80109410_fowl_play(omObjData *object, func_800E1BA8_minigame_ObjData **data, FowlPlayerWork **work) {
    *data = object->data;
    *work = (*data)->unk158;
}

void func_80109424_fowl_play(void) {
    s32 i;

    D_8010F234_fowl_play = func_8010B2C4_fowl_play(0x5B0003);
    for (i = 0; i < 1; i++) {
        D_8010F290_fowl_play[i] = omAddObj(3, 5, 5, -1, func_801094A4_fowl_play);
    }
}

void func_801094A4_fowl_play(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    FowlFoxWork *work;
    s32 index;
    s32 i;

    data = HuMemAllocTag(sizeof(func_800E1BA8_minigame_ObjData), TAG_OVERLAY);
    object->data = data;
    memset(data, 0, sizeof(func_800E1BA8_minigame_ObjData));
    data->unkE8 = HuMemAllocTag(object->mtncnt * sizeof(func_800E1BA8_minigame_UnkE8_ObjData), TAG_OVERLAY);
    memset(data->unkE8, 0, object->mtncnt * sizeof(func_800E1BA8_minigame_UnkE8_ObjData));
    data->unk52 = 0;
    data->unkD0 = 0xFFFF;
    work = HuMemAllocTag(sizeof(FowlFoxWork), TAG_OVERLAY);
    data->unk158 = work;
    memset(work, 0, sizeof(FowlFoxWork));
    work->unk00 = 0;
    work->unk01 = 0;
    work->unk24.x = work->unk24.y = work->unk24.z = 0.0f;
    work->unk10 = work->unk14 = (f32)(func_8010A9A0_fowl_play() - 0x8000) * 3.0517578125e-05 * 180.0;
    work->unk0C = 20.0f;
    work->unk06 = 0;
    work->unk04 = 0;
    work->unk02 = 0;
    object->model[0] = func_8000B108_main(0x5B0006, 0x2D9);
    object->model[1] = func_8000B0D4_main(9, 0x2D9);
    D_8010F238_fowl_play = func_8010B2C4_fowl_play(0xB);
    for (i = 0; i < 8; i++) {
        work->unk34[i] = index = func_8010C1F4_fowl_play(D_8010F238_fowl_play, 0x20009000);
        func_8010D148_fowl_play(index, 2);
        func_8010D2A4_fowl_play(index, -1, -58, 105, 224);
        func_8010CFDC_fowl_play(index, 1.2f, 1.2f, 1.2f);
        func_8010CE44_fowl_play(index, 0.5f);
    }
    Hu3DModelScaleSet(object->model[1], 0.75f, 0.75f, 0.75f);
    func_800E5A00_minigame(object, 0, 0x5B0007, 1, 0);
    func_800E5A00_minigame(object, 1, 0x5B0008, 1, 0);
    func_800E5A00_minigame(object, 2, 0x5B0009, 1, 0);
    func_800E5690_minigame(object, 0);
    object->func = func_80109844_fowl_play;
    object->trans.x = (f32)(func_8010A9A0_fowl_play() - 0x8000) * 3.0517578125e-05 * 40.0;
    object->trans.z = (f32)(func_8010A9A0_fowl_play() - 0x8000) * 3.0517578125e-05 * 40.0;
    for (i = 0; i < 32; i++) {
        work->feathers[i].index = func_8010C1F4_fowl_play(D_8010F234_fowl_play, 0x10009000);
        func_8010D148_fowl_play(work->feathers[i].index, 0);
        func_8010CFDC_fowl_play(work->feathers[i].index, 2.0f, 2.0f, 2.0f);
        work->feathers[i].unk01 = 0;
        work->feathers[i].pos.x = work->feathers[i].pos.y = work->feathers[i].pos.z = 0.0f;
        work->feathers[i].unk10 = 0.0f;
    }
    D_8010F2A0_fowl_play++;
}

void func_80109844_fowl_play(omObjData *object) {
    Vec pos;
    Vec unusedVec; // Unreferenced, but present in the stack frame.
    f32 dists[2];
    f32 angles[2];
    HuMtx4F unusedMtx; // Unreferenced, but present in the stack frame.
    func_800E1BA8_minigame_ObjData *data = object->data;
    FowlFoxWork *work = data->unk158;
    omObjData *player;
    f32 dist;
    f32 angle;
    f32 diff;
    s16 seNo = 0;
    u8 index;
    s32 i;
    s16 pan;

    switch (D_8010F29C_fowl_play) {
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
    angle = func_8010A9EC_fowl_play(object->trans.x, object->trans.z);
    switch (work->unk00) {
        case 0:
            work->unk24.x = work->unk24.z = 0.0f;
            if (--work->unk02 == 0) {
                work->unk03 =
                    D_8010F29E_fowl_play * 0.2 + (s32)((f32)func_8010A9A0_fowl_play() * 1.52587890625e-05 * 30.0);
                work->unk00++;
            }
            break;
        case 1:
        case 2:
            for (i = 0; i < 2; i++) {
                player = D_800EC598_minigame[i];
                dists[i] = func_8010AA64_fowl_play(&object->trans, &player->trans);
                angles[i] =
                    func_8010A9EC_fowl_play(player->trans.x - object->trans.x, player->trans.z - object->trans.z);
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
                        D_8010E8C4_fowl_play = 1;
                    }
                    work->unk14 = angles[0] + 180.0;
                    work->unk00 = 1;
                } else if (dists[1] < 200.0) {
                    if (work->unk00 != 1) {
                        seNo = 0x4C1;
                        D_8010E8C4_fowl_play = 1;
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
                diff = func_801075B0_fowl_play(&pos, 200.0f, work->unk10);
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
                func_800E5690_minigame(object, 2);
                work->unk08 = 20.0f;
                work->unk04 -= 2;
                work->unk06--;
                if (work->unk03 == 0) {
                    work->unk03 =
                        D_8010F29E_fowl_play * 0.05 + (s32)((f32)func_8010A9A0_fowl_play() * 1.52587890625e-05 * 30.0);
                    work->unk00++;
                }
            } else {
                func_800E5690_minigame(object, 1);
                work->unk08 = 6.0f;
                work->unk04--;
                if (work->unk03 == 0) {
                    D_8010E8C4_fowl_play = 1;
                    seNo = 0x4C1;
                    work->unk03 =
                        D_8010F29E_fowl_play * 0.2 + (s32)((f32)func_8010A9A0_fowl_play() * 1.52587890625e-05 * 30.0);
                    work->unk00--;
                }
            }
            if (--D_8010E8C4_fowl_play == 0) {
                if (work->unk00 == 1) {
                    D_8010E8C4_fowl_play = 9;
                } else {
                    D_8010E8C4_fowl_play = 15;
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
                        seNo = (func_8010A9A0_fowl_play() & 3) + 0x4C3;
                    }
                    HuAudFXPanning(func_8004AC5C_main(seNo, 4), pan);
                }
            }
            break;
        case 3:
            if (--work->unk03 == 0) {
                func_800E5690_minigame(object, 0);
                Hu3DModelHookSet(object->model[0], work->target->model[0], "item_hook");
                func_8001C258_main(object->model[0], 0x4000, 0x4000);
            }
            func_8001C258_main(object->model[1], 4, 4);
            work->unk08 = 0.0f;
            if (D_8010F29C_fowl_play == 6) {
                func_8010B1A0_fowl_play(work->target->model[0], "item_hook", 0, &object->trans);
            } else if (D_8010F29C_fowl_play == 7) {
                work->unk10 = func_8010A9EC_fowl_play(-object->trans.x, -object->trans.z);
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
        if (func_8010724C_fowl_play(&pos, &object->trans, work->unk0C)) {
            object->trans.x = pos.x;
            object->trans.z = pos.z;
        } else {
            func_801070FC_fowl_play(object, work->unk0C);
        }
    } else {
        func_801070FC_fowl_play(object, work->unk0C);
    }
    work->unk01 = 0;
    if (dist > 1200.0 - work->unk0C) {
        object->trans.x = (1200.0 - work->unk0C) * (object->trans.x / dist);
        object->trans.z = (1200.0 - work->unk0C) * (object->trans.z / dist);
    }
    for (i = 0; i < 4; i++) {
        index = work->unk34[i];
        if ((func_8010D108_fowl_play(index) & 0x8000) && work->unk06 == 0) {
            func_8010CF24_fowl_play(index, object->trans.x, object->trans.y - 10.0, object->trans.z);
            func_8010D0C0_fowl_play(index, 0x8000);
            func_8010CE04_fowl_play(index, 0);
            work->unk06 = 8;
        }
    }
    for (i = 0; i < 32; i++) {
        if (work->feathers[i].unk01 == 0) {
            if (work->unk04 <= 0) {
                func_8010D0C0_fowl_play(work->feathers[i].index, 0x8000);
                work->feathers[i].pos.x = object->trans.x;
                work->feathers[i].pos.y = 1.0f;
                work->feathers[i].pos.z = object->trans.z;
                work->feathers[i].unk10 = work->unk10;
                work->feathers[i].unk01 = 0x80;
                func_8010CF24_fowl_play(work->feathers[i].index, work->feathers[i].pos.x, work->feathers[i].pos.y,
                                        work->feathers[i].pos.z);
                func_8010D02C_fowl_play(work->feathers[i].index, 90.0f, work->feathers[i].unk10, 0.0f);
                func_8010D2A4_fowl_play(work->feathers[i].index, 0, 0, 0, 0xFF);
                work->unk04 = 10;
            } else {
                func_8010D07C_fowl_play(work->feathers[i].index, 0x8000);
            }
        } else {
            work->feathers[i].unk01--;
            func_8010D2A4_fowl_play(work->feathers[i].index, 0, 0, 0, work->feathers[i].unk01 * 2);
        }
    }
    work->unk18.x = object->trans.x;
    work->unk18.y = object->trans.y;
    work->unk18.z = object->trans.z;
    object->rot.y = work->unk10;
    Hu3DModelPosSet(object->model[1], object->trans.x, 1.0f, object->trans.z);
    func_800E4E30_minigame(object);
}

u8 func_8010A738_fowl_play(omObjData *object, u8 canCatch) {
    Vec unused; // Unreferenced, but present in the stack frame.
    func_800E1BA8_minigame_ObjData *data;
    FowlFoxWork *work;
    omObjData *fox;
    f32 range;
    f32 dist;
    f32 angle;

    if (object->trans.y >= 20.0) {
        return 0;
    }
    fox = D_8010F290_fowl_play[0];
    work = ((func_800E1BA8_minigame_ObjData *)fox->data)->unk158;
    data = object->data;
    range = work->unk0C + data->unk48;
    dist = func_8010AA64_fowl_play(&object->trans, &fox->trans);
    if (dist > range + 20.0) {
        return 0;
    }
    angle = func_8010A9EC_fowl_play(object->trans.x - fox->trans.x, object->trans.z - fox->trans.z);
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

s32 func_8010A9A0_fowl_play(void) {
    D_8010E8C8_fowl_play = (D_8010E8C8_fowl_play + (rand8() & 0xFF)) * 0x41C64E6D + 0x3039;
    return D_8010E8C8_fowl_play >> 16;
}

f32 func_8010A9EC_fowl_play(f32 y, f32 x) {
    f32 fullCircle = 360.0f;
    f32 angle = atan2df(y, x);

    if (angle < -180.0f) {
        angle += fullCircle;
    } else if (angle >= 180.0) {
        angle -= fullCircle;
    }
    return angle;
}

f32 func_8010AA64_fowl_play(Vec *arg0, Vec *arg1) {
    return sqrtf(((arg0->x - arg1->x) * (arg0->x - arg1->x)) +
                 ((arg0->z - arg1->z) * (arg0->z - arg1->z)));
}

void func_8010AAB8_fowl_play(Vec *dir, f32 *rot) {
    *rot++ = func_8010A9EC_fowl_play(sqrtf(dir->x * dir->x + dir->z * dir->z), -dir->y);
    *rot++ = func_8010A9EC_fowl_play(dir->x, dir->z);
    *rot = 0.0f;
}

f32 func_8010AB40_fowl_play(Vec *vec) {
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

f32 func_8010AC04_fowl_play(Vec *arg0, Vec *arg1, Vec *arg2) {
    f32 dot = (arg2->x * (arg1->x - arg0->x)) + (arg2->y * (arg1->y - arg0->y)) +
              (arg2->z * (arg1->z - arg0->z));
    f32 len = -((arg2->x * arg2->x) + (arg2->y * arg2->y) + (arg2->z * arg2->z));

    if (len != 0.0f) {
        dot /= len;
    }
    return dot;
}

f32 func_8010AC88_fowl_play(Vec *point, Vec *start, Vec *end, Vec *closest) {
    Vec dir;
    f32 t;

    if (func_8010AA64_fowl_play(start, end) == 0.0f) {
        closest->x = start->x;
        closest->y = start->y;
        closest->z = start->z;
        return func_8010AA64_fowl_play(point, start);
    }
    dir.x = end->x - start->x;
    dir.y = end->y - start->y;
    dir.z = end->z - start->z;
    t = func_8010AC04_fowl_play(point, start, &dir);
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
    return func_8010AA64_fowl_play(point, closest);
}

f32 func_8010AE10_fowl_play(Vec *pos1, Vec *dir1, Vec *pos2, Vec *dir2) {
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

void func_8010B1A0_fowl_play(s16 model, char *hook, s16 time, Vec *pos) {
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

s16 func_8010B2C4_fowl_play(s32 dataNum) {
    void *data;
    s16 spriteId;

    data = DataRead(dataNum);
    spriteId = HuSprAnimRead(data);
    DataClose(data);
    return spriteId;
}

s16 func_8010B30C_fowl_play(s16 spriteId, s16 count) {
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

HuSprite_Unk84_Unk00_Struct *func_8010B3D4_fowl_play(s16 arg0, s16 arg1) {
    return &func_80055194_main(arg0)->unk00[arg1];
}

void func_8010B41C_fowl_play(u16 count) {
    Fowl *fowl;
    s16 i;

    D_8010F350_fowl_play = count;
    D_8010F32C_fowl_play = HuMemAlloc(count * sizeof(Fowl));
    for (i = 0; i < 6; i++) {
        D_8010F330_fowl_play[i] = NULL;
    }
    for (i = 0; i < D_8010F350_fowl_play; i++) {
        fowl = &D_8010F32C_fowl_play[i];
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

void func_8010B564_fowl_play(Gfx **gfx, HuSprite_Unk84_Unk00_Struct *cel, u8 fmt, u8 siz, u16 height, u16 uls,
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

s16 func_8010B8D4_fowl_play(Fowl *fowl) {
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

    cel = fowl->sprite->unk00;
    buf = HuMemAlloc(0x1000);
    gfx = buf;
    gSPSegment(gfx++, 0x0C, cel->unk00);
    gSPSegment(gfx++, 0x0E, fowl->vtx);
    start = gfx;
    gDPPipeSync(gfx++);
    switch (fowl->sprite->unk18) {
        case 4:
            siz = G_IM_SIZ_4b;
            if (fowl->sprite->unk1A == 1) {
                fmt = G_IM_FMT_IA;
                gDPSetTextureLUT(gfx++, G_TT_NONE);
            } else {
                fmt = G_IM_FMT_CI;
                gDPLoadTLUT_pal16(gfx++, 0, fowl->sprite->unk0C);
                gDPSetTextureLUT(gfx++, G_TT_RGBA16);
            }
            mode = 0;
            break;
        case 8:
            siz = G_IM_SIZ_8b;
            if (fowl->sprite->unk1A == 1) {
                fmt = G_IM_FMT_IA;
                gDPSetTextureLUT(gfx++, G_TT_NONE);
                mode = 2;
            } else {
                fmt = G_IM_FMT_CI;
                gDPLoadTLUT_pal256(gfx++, fowl->sprite->unk0C);
                gDPSetTextureLUT(gfx++, G_TT_RGBA16);
                mode = 2;
            }
            break;
        case 16:
            siz = G_IM_SIZ_16b;
            if (fowl->sprite->unk1A == 1) {
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
            if (D_8010E8DC_fowl_play[cel->unk04 >> D_8010E8CC_fowl_play[siz]] >= rows ||
                rows == D_8010EA14_fowl_play[cel->unk04 >> D_8010E8CC_fowl_play[siz]]) {
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
    segCel.unk00 = (void *)0x0C000000;
    if ((u32)fowl->unk_28 >= 0x80000000 && count == 1 && remainder == 0) {
        func_8010B564_fowl_play(&gfx, &segCel, fmt, siz, rows, 0, 0, cel->unk04 - 1, cel->unk06 - 1, cms, cmt, masks,
                                maskt, mode);
        gSPVertex(gfx++, (Vtx *)0x0E000000, 5, 0);
        gSP2Triangles(gfx++, 0, 2, 4, 0, 2, 3, 4, 0);
        gSP2Triangles(gfx++, 0, 4, 1, 0, 4, 3, 1, 0);
    } else {
        for (i = 0; i < count; i++) {
            func_8010B564_fowl_play(&gfx, &segCel, fmt, siz, rows, 0, i * rows, cel->unk04 - 1, (i + 1) * rows - 1,
                                    cms, cmt, masks, maskt, mode);
            gSPVertex(gfx++, (Vtx *)0x0E000000 + i * 2, 4, 0);
            gSP2Triangles(gfx++, 0, 2, 3, 0, 0, 3, 1, 0);
        }
        if (remainder != 0) {
            func_8010B564_fowl_play(&gfx, &segCel, fmt, siz, remainder, 0, i * rows, cel->unk04 - 1,
                                    cel->unk06 - 1, cms, cmt, masks, maskt, mode);
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

s16 func_8010C1F4_fowl_play(s16 spriteId, s32 flags) {
    Fowl *fowl;
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

    for (index = 0; index < D_8010F350_fowl_play; index++) {
        if (D_8010F32C_fowl_play[index].sprite == NULL) {
            break;
        }
    }
    if (index == D_8010F350_fowl_play) {
        return -1;
    }
    fowl = &D_8010F32C_fowl_play[index];
    fowl->sprite = D_800C9530_main[spriteId];
    fowl->unk_28 = flags;
    fowl->unk_1A = 7;
    cel = fowl->sprite->unk00;
    switch (fowl->sprite->unk18) {
        case 4:
            siz = G_IM_SIZ_4b;
            fmt = (fowl->sprite->unk1A == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 8:
            siz = G_IM_SIZ_8b;
            fmt = (fowl->sprite->unk1A == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 16:
            siz = G_IM_SIZ_16b;
            fmt = (fowl->sprite->unk1A == 1) ? G_IM_FMT_IA : G_IM_FMT_RGBA;
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
    fowl->unk_18 = count + 2;
    fowl->unk_19 = rows;
    fowl->vtx = HuMemAlloc((count + 2) * 2 * sizeof(Vtx));
    for (i = 0; i < count + 1; i++) {
        fowl->vtx[i * 2].ob[0] = 0;
        fowl->vtx[i * 2 + 1].ob[0] = cel->unk04;
        fowl->vtx[i * 2].ob[1] = fowl->vtx[i * 2 + 1].ob[1] = -i * rows;
        fowl->vtx[i * 2].tc[0] = 0;
        fowl->vtx[i * 2 + 1].tc[0] = cel->unk04 << 6;
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
        fowl->vtx[i * 2 + 1].ob[0] = cel->unk04;
        fowl->vtx[i * 2].ob[1] = fowl->vtx[i * 2 + 1].ob[1] = cel->unk06;
        fowl->vtx[i * 2].tc[0] = 0;
        fowl->vtx[i * 2 + 1].tc[0] = cel->unk04 << 6;
        fowl->vtx[i * 2].tc[1] = fowl->vtx[i * 2 + 1].tc[1] = cel->unk06 << 6;
        for (j = 0; j < 2; j++) {
            fowl->vtx[i * 2 + j].ob[2] = 0;
            fowl->vtx[i * 2 + j].cn[0] = 0xFF;
            fowl->vtx[i * 2 + j].cn[1] = 0xFF;
            fowl->vtx[i * 2 + j].cn[2] = 0xFF;
            fowl->vtx[i * 2 + j].cn[3] = 0xFF;
        }
    } else if (count == 1) {
        fowl->vtx[4].ob[0] = cel->unk04 * 0.5;
        fowl->vtx[4].ob[1] = -cel->unk06 * 0.5;
        fowl->vtx[4].ob[2] = 0;
        fowl->vtx[4].tc[0] = cel->unk04 * 0.5 * 64.0;
        fowl->vtx[4].tc[1] = cel->unk06 * 0.5 * 64.0;
        fowl->vtx[4].cn[0] = 0xFF;
        fowl->vtx[4].cn[1] = 0xFF;
        fowl->vtx[4].cn[2] = 0xFF;
        fowl->vtx[4].cn[3] = 0xFF;
    }
    if (!func_8010B8D4_fowl_play(fowl)) {
        HuMemFree(fowl->vtx);
        index = -1;
    }
    return index;
}

void func_8010C7FC_fowl_play(s16 index, s16 spriteId) {
    Fowl *fowl;
    HuSprite_Unk84_Unk00_Struct *cel;
    s32 siz;
    s32 fmt;
    s32 alignedWidth;
    u32 rows;
    u32 count;
    s32 remainder;
    u32 i;
    s32 j;

    fowl = &D_8010F32C_fowl_play[index];
    fowl->sprite = D_800C9530_main[spriteId];
    cel = fowl->sprite->unk00;
    HuMemFree(fowl->vtx);
    HuMemFree(fowl->displayList);
    switch (fowl->sprite->unk18) {
        case 4:
            siz = G_IM_SIZ_4b;
            fmt = (fowl->sprite->unk1A == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 8:
            siz = G_IM_SIZ_8b;
            fmt = (fowl->sprite->unk1A == 1) ? G_IM_FMT_IA : G_IM_FMT_CI;
            break;
        case 16:
            siz = G_IM_SIZ_16b;
            fmt = (fowl->sprite->unk1A == 1) ? G_IM_FMT_IA : G_IM_FMT_RGBA;
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
    fowl->unk_18 = count + 2;
    fowl->unk_19 = rows;
    fowl->vtx = HuMemAlloc((count + 2) * 2 * sizeof(Vtx));
    for (i = 0; i < count + 1; i++) {
        fowl->vtx[i * 2].ob[0] = 0;
        fowl->vtx[i * 2 + 1].ob[0] = cel->unk04;
        fowl->vtx[i * 2].ob[1] = fowl->vtx[i * 2 + 1].ob[1] = -i * rows;
        fowl->vtx[i * 2].tc[0] = 0;
        fowl->vtx[i * 2 + 1].tc[0] = cel->unk04 << 6;
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
        fowl->vtx[i * 2 + 1].ob[0] = cel->unk04;
        fowl->vtx[i * 2].ob[1] = fowl->vtx[i * 2 + 1].ob[1] = cel->unk06;
        fowl->vtx[i * 2].tc[0] = 0;
        fowl->vtx[i * 2 + 1].tc[0] = cel->unk04 << 6;
        fowl->vtx[i * 2].tc[1] = fowl->vtx[i * 2 + 1].tc[1] = cel->unk06 << 6;
        for (j = 0; j < 2; j++) {
            fowl->vtx[i * 2 + j].ob[2] = 0;
            fowl->vtx[i * 2 + j].cn[0] = 0xFF;
            fowl->vtx[i * 2 + j].cn[1] = 0xFF;
            fowl->vtx[i * 2 + j].cn[2] = 0xFF;
            fowl->vtx[i * 2 + j].cn[3] = 0xFF;
        }
    } else if (count == 1) {
        fowl->vtx[4].ob[0] = cel->unk04 * 0.5;
        fowl->vtx[4].ob[1] = -cel->unk06 * 0.5;
        fowl->vtx[4].ob[2] = 0;
        fowl->vtx[4].tc[0] = cel->unk04 * 0.5 * 64.0;
        fowl->vtx[4].tc[1] = cel->unk06 * 0.5 * 64.0;
        fowl->vtx[4].cn[0] = 0xFF;
        fowl->vtx[4].cn[1] = 0xFF;
        fowl->vtx[4].cn[2] = 0xFF;
        fowl->vtx[4].cn[3] = 0xFF;
    }
    func_8010B8D4_fowl_play(fowl);
}

void func_8010CD84_fowl_play(s16 index, s16 spriteId) {
    Fowl *fowl;

    if (index != -1) {
        fowl = D_8010F32C_fowl_play + index;
        fowl->sprite = D_800C9530_main[spriteId];
        fowl->unk_20 = 0x100;
        fowl->unk_1F = 0xFF;
        fowl->unk_1E = 0xFF;
        fowl->unk_1D = 0xFF;
        fowl->unk_2C = 0;
        fowl->unk_24 = 0;
        fowl->unk_30.x = 1.0f;
    }
}

void func_8010CE04_fowl_play(s16 arg0, s16 arg1) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_24 = arg1;
        fowl->unk_2C = 0;
    }
}

void func_8010CE44_fowl_play(s16 arg0, f32 arg1) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_30.x = arg1;
    }
}

void func_8010CE84_fowl_play(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_28 |= 0x4000000;
        fowl->unk_30.y = arg1;
        fowl->unk_30.z = arg2;
        fowl->unk_3C = arg3;
    }
}

void func_8010CEE4_fowl_play(s16 arg0, f32 arg1) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_3C = arg1;
    }
}

void func_8010CF24_fowl_play(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_40.x = arg1;
        fowl->unk_40.y = arg2;
        fowl->unk_40.z = arg3;
    }
}

void func_8010CF74_fowl_play(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_40.x += arg1;
        fowl->unk_40.y += arg2;
        fowl->unk_40.z += arg3;
    }
}

void func_8010CFDC_fowl_play(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_4C.x = arg1;
        fowl->unk_4C.y = arg2;
        fowl->unk_4C.z = arg3;
    }
}

void func_8010D02C_fowl_play(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_58.x = arg1;
        fowl->unk_58.y = arg2;
        fowl->unk_58.z = arg3;
    }
}

void func_8010D07C_fowl_play(s16 arg0, s32 arg1) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_28 |= arg1;
    }
}

void func_8010D0C0_fowl_play(s16 arg0, s32 arg1) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_28 &= ~arg1;
    }
}

s32 func_8010D108_fowl_play(s16 arg0) {
    Fowl *fowl;
    s32 i = arg0;

    if (i != -1) {
        fowl = D_8010F32C_fowl_play + i;
        return fowl->unk_28;
    }
    return -1;
}

void func_8010D148_fowl_play(s16 arg0, s8 arg1) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_1A = arg1;
    }
}

Fowl *func_8010D184_fowl_play(s16 arg0) {
    Fowl *fowl;
    s32 i = arg0;

    if (i == -1) {
        return NULL;
    }
    fowl = &D_8010F32C_fowl_play[i];
    return fowl;
}

Vtx_t *func_8010D1C4_fowl_play(s16 arg0) {
    Fowl *fowl;
    s32 i = arg0;

    if (i == -1) {
        return NULL;
    }
    fowl = D_8010F32C_fowl_play + i;
    return fowl->vtx;
}

s32 func_8010D208_fowl_play(s16 index, s16 x, s16 y) {
    Fowl *fowl;
    Vtx_t *vtx;

    if (index == -1) {
        return 0;
    }
    fowl = &D_8010F32C_fowl_play[index];
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

void func_8010D2A4_fowl_play(s16 arg0, s8 arg1, s8 arg2, s8 arg3, s16 arg4) {
    s32 i = arg0;

    if (i != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + i;
        fowl->unk_1D = arg1;
        fowl->unk_1E = arg2;
        fowl->unk_1F = arg3;
        fowl->unk_20 = arg4;
    }
}

void func_8010D2F0_fowl_play(s16 index) {
    Fowl *fowl;

    if (index != -1) {
        fowl = &D_8010F32C_fowl_play[index];
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

void func_8010D3D0_fowl_play(s32 index, s32 flag) {
    Fowl *fowl = D_8010F32C_fowl_play + index;
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

void func_8010D4D0_fowl_play(s32 index, s32 flip) {
    Fowl *fowl = &D_8010F32C_fowl_play[index];
    s32 i;

    if (flip) {
        for (i = 0; i < fowl->unk_18; i++) {
            fowl->vtx[i * 2].tc[0] = fowl->sprite->unk00->unk04 << 6;
            fowl->vtx[i * 2 + 1].tc[0] = 0;
        }
    } else {
        for (i = 0; i < fowl->unk_18; i++) {
            fowl->vtx[i * 2].tc[0] = 0;
            fowl->vtx[i * 2 + 1].tc[0] = fowl->sprite->unk00->unk04 << 6;
        }
    }
}

void func_8010D5A0_fowl_play(s32 index, s32 flip) {
    Fowl *fowl = &D_8010F32C_fowl_play[index];
    s32 remainder = fowl->sprite->unk00->unk06 - (fowl->unk_18 - 2) * fowl->unk_19;
    s32 i;

    if (flip) {
        for (i = 0; i < fowl->unk_18 - 1; i++) {
            fowl->vtx[i * 2].tc[1] = fowl->vtx[i * 2 + 1].tc[1] =
                fowl->sprite->unk00->unk06 - i * fowl->unk_19;
        }
        if (remainder != 0) {
            fowl->vtx[i * 2].tc[1] = fowl->vtx[i * 2 + 1].tc[1] = 0;
        }
    } else {
        for (i = 0; i < fowl->unk_18 - 1; i++) {
            fowl->vtx[i * 2].ob[1] = fowl->vtx[i * 2 + 1].ob[1] = i * fowl->unk_19;
        }
        if (remainder != 0) {
            fowl->vtx[i * 2].ob[1] = fowl->vtx[i * 2 + 1].ob[1] = fowl->sprite->unk00->unk06;
        }
    }
}

void func_8010D6D8_fowl_play(s16 arg0, void (*arg1)(struct Fowl *)) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->callback = arg1;
    }
}

void func_8010D714_fowl_play(s16 index, s8 arg1, s8 arg2, s32 flags) {
    Fowl *fowl;

    if (index != -1) {
        fowl = &D_8010F32C_fowl_play[index];
        fowl->unk_1B = arg1;
        fowl->unk_1C = arg2;
        fowl->unk_28 |= flags;
        HuMemFree(fowl->displayList);
        func_8010B8D4_fowl_play(fowl);
    }
}

void func_8010D784_fowl_play(s16 index, s32 flag) {
    Fowl *fowl;
    s8 color;
    s8 blue;
    s32 i;

    if (index != -1) {
        fowl = &D_8010F32C_fowl_play[index];
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

void func_8010D81C_fowl_play(void) {
    Fowl *fowl;
    s32 i;

    if (++D_8010EB64_fowl_play >= 6) {
        D_8010EB64_fowl_play = 0;
    }
    D_8010F34C_fowl_play = 0;
    for (i = 0; i < D_8010F350_fowl_play; i++) {
        fowl = &D_8010F32C_fowl_play[i];
        if (fowl->sprite != NULL) {
            D_8010F34C_fowl_play += 0x40 + (fowl->unk_22 * sizeof(Gfx) + fowl->unk_18 * 2 * sizeof(Vtx));
        }
    }
    if (D_8010F330_fowl_play[D_8010EB64_fowl_play] != NULL) {
        HuMemFree(D_8010F330_fowl_play[D_8010EB64_fowl_play]);
    }
    if (D_8010F34C_fowl_play != 0) {
        D_8010F330_fowl_play[D_8010EB64_fowl_play] = HuMemAlloc(D_8010F34C_fowl_play);
    } else {
        D_8010F330_fowl_play[D_8010EB64_fowl_play] = NULL;
    }
    D_8010F348_fowl_play = D_8010F330_fowl_play[D_8010EB64_fowl_play];
}

void func_8010D970_fowl_play(HuCamera *camera, HuMtx4F lookAt) {
    Fowl tailOpaque;
    Fowl tailTranslucent;
    HuMtx4F unused[16]; // Unreferenced, but present in the stack frame.
    HuMtx4F mtx;
    Fowl *fowl;
    Fowl *node;
    f32 minX;
    f32 maxX;
    f32 minZ;
    f32 maxZ;
    s32 i;

    minX = camera->at.x - 1920.0;
    maxX = camera->at.x + 1920.0;
    minZ = camera->at.z - 1920.0;
    maxZ = camera->at.z + 1920.0;
    D_8010F360_fowl_play.unk_64 = 0.0f;
    D_8010F3C8_fowl_play.unk_64 = 99999.9f;
    tailOpaque.unk_64 = -99999.9f;
    tailTranslucent.unk_64 = 0.0f;
    D_8010F3C8_fowl_play.prev = NULL;
    D_8010F360_fowl_play.prev = NULL;
    D_8010F360_fowl_play.next = &tailOpaque;
    D_8010F3C8_fowl_play.next = &tailTranslucent;
    tailOpaque.prev = &D_8010F360_fowl_play;
    tailTranslucent.prev = &D_8010F3C8_fowl_play;
    tailTranslucent.next = NULL;
    tailOpaque.next = NULL;
    for (i = 0; i < D_8010F350_fowl_play; i++) {
        fowl = &D_8010F32C_fowl_play[i];
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
            node = &D_8010F3C8_fowl_play;
        } else {
            node = &D_8010F360_fowl_play;
        }
        for (node = node->next; node->unk_64 > fowl->unk_64; node = node->next) {}
        node->prev->next = fowl;
        fowl->prev = node->prev;
        fowl->next = node;
        node->prev = fowl;
    }
    tailOpaque.prev->next = tailTranslucent.prev->next = NULL;
}

void func_8010DC24_fowl_play(Gfx **gfxP, s32 arg1, s32 arg2) {
    HuCamera *camera = (HuCamera *)arg2;
    Gfx *gfx = *gfxP;
    HuMtx4F unused1[2]; // Unreferenced, but present in the stack frame.
    HuMtx4F lookAt;
    HuMtx4F unused2[4]; // Unreferenced, but present in the stack frame.
    Vec rot;
    Vec dir;
    HuMtx4F unused3[33]; // Unreferenced, but present in the stack frame.
    Fowl *fowl;

    guLookAtF(lookAt, camera->pos.x, camera->pos.y, camera->pos.z, camera->at.x, camera->at.y, camera->at.z,
              camera->up.x, camera->up.y, camera->up.z);
    dir.x = camera->at.x - camera->pos.x;
    dir.y = camera->at.y - camera->pos.y;
    dir.z = camera->at.z - camera->pos.z;
    func_8010AAB8_fowl_play(&dir, (f32 *)&rot);
    func_8010D81C_fowl_play();
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_2CYCLE);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING | G_TEXTURE_GEN);
    gSPSetGeometryMode(gfx++, G_SHADE | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    func_8010D970_fowl_play(camera, lookAt);
    for (fowl = D_8010F360_fowl_play.next; fowl != NULL; fowl = fowl->next) {
        gfx = func_8010DE4C_fowl_play(gfx, fowl, lookAt, &rot);
    }
    for (fowl = D_8010F3C8_fowl_play.next; fowl != NULL; fowl = fowl->next) {
        gfx = func_8010DE4C_fowl_play(gfx, fowl, lookAt, &rot);
    }
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    *gfxP = gfx;
    if (!Hu3DPauseF) {
        func_8010E544_fowl_play();
    }
}

Gfx *func_8010DE4C_fowl_play(Gfx *gfx, Fowl *fowl, HuMtx4F lookAt, Vec *rot) {
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

    cel = &fowl->sprite->unk00[fowl->unk_24];
    gDPPipeSync(gfx++);
    gDPSetTextureFilter(gfx++, D_8010EB54_fowl_play[(fowl->unk_28 >> 2) & 3]);
    gDPSetColorDither(gfx++, D_8010EB4C_fowl_play[(fowl->unk_28 >> 4) & 3]);
    gDPSetAlphaCompare(gfx++, D_8010EB5C_fowl_play[(fowl->unk_28 >> 22) & 3]);
    if (fowl->unk_28 & 0x10000) {
        gSPSetGeometryMode(gfx++, G_LIGHTING);
    } else {
        gSPClearGeometryMode(gfx++, G_LIGHTING);
    }
    format = fowl->sprite->unk18;
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
    vtx = D_8010F348_fowl_play;
    mtxL = (Mtx *)&vtx[fowl->unk_18 * 2];
    dl = (Gfx *)&mtxL[1];
    D_8010F348_fowl_play = &dl[fowl->unk_22];
    guMtxIdentF(billboard);
    if (fowl->unk_28 & 0x4000000) {
        billboard[3][0] = -fowl->unk_30.y;
        billboard[3][1] = fowl->unk_30.z;
    } else {
        billboard[3][0] = -(u16)cel->unk08;
        billboard[3][1] = (u16)cel->unk0A;
    }
    billboard[3][2] = fowl->unk_3C;
    func_8002367C_main(mtx, lookAt);
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
    memcpy(vtx, fowl->vtx, fowl->unk_18 * 2 * sizeof(Vtx));
    memcpy(dl, fowl->displayList, fowl->unk_22 * sizeof(Gfx));
    if (!(fowl->unk_28 & 0x8000)) {
        gSPDisplayList(gfx++, dl);
    }
    return gfx;
}

void func_8010E544_fowl_play(void) {
    Fowl *fowl;
    s32 frameCount;
    s32 i;

    for (i = 0; i < D_8010F350_fowl_play; i++) {
        fowl = &D_8010F32C_fowl_play[i];
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
        frameCount = fowl->sprite->unk10;
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
                        func_8010D2F0_fowl_play(i);
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

void func_8010E704_fowl_play(void) {
    s32 i;

    for (i = 0; i < D_8010F350_fowl_play; i++) {
        func_8010D2F0_fowl_play(i);
    }
    for (i = 0; i < 6; i++) {
        if (D_8010F330_fowl_play[i] != NULL) {
            HuMemFree(D_8010F330_fowl_play[i]);
        }
    }
    HuMemFree(D_8010F32C_fowl_play);
}
