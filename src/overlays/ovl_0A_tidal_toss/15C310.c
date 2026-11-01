#include "common.h"
#include "overlays/minigame.h"
#include "mallocblock.h"

typedef struct {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    u8 unk10;
} TidalTossStruct;

typedef struct {
    u8 unk00[3];
    u8 unk03;
    u8 unk04;
    u8 unk05[0xAF];
} TidalTossSetupWork;

typedef struct {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    s32 unk24;
    u16 unk28;
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    u8 unk2F;
    u8 unk30;
    u8 unk31;
    u16 unk32;
    u16 unk34;
    u16 unk36;
    u16 unk38;
    u8 unk3A[0xA];
    f32 unk44;
} TidalTossWork;

typedef struct {
    s16 unk00;
    s16 unk02;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
} TidalTossSpriteWork;

extern u32 D_8010AAFC_tidal_toss;
extern u8 D_8010AA70_tidal_toss;
extern u8 D_8010AAB1_tidal_toss[];
extern u8 D_8010AAB8_tidal_toss;
extern u8 D_8010AAB9_tidal_toss;
extern f32 D_8010AABC_tidal_toss[4][3];
extern f32 D_8010AAEC_tidal_toss[4];
extern s32 D_800A178C_main[][6];
extern s32 D_800A1790_main[][6];
extern f32 D_8010B090_tidal_toss;
extern f32 D_8010B058_tidal_toss[4][4];
extern f32 D_8010B098_tidal_toss[4][4];
extern f32 D_8010B0D8_tidal_toss;
extern s16 D_8010AA74_tidal_toss[3][2];
extern f32 D_8010AA80_tidal_toss[3];

extern TidalTossStruct D_8010AF48_tidal_toss[8];
extern s16 D_8010AF40_tidal_toss;
extern s16 D_8010AED8_tidal_toss;
extern s16 D_8010AEDA_tidal_toss;
extern s16 D_8010AEE8_tidal_toss;
extern s16 D_8010AEEC_tidal_toss;
extern s16 D_8010AF38_tidal_toss;
extern s16 D_8010AF3A_tidal_toss;
extern TidalTossSpriteWork D_8010AFE8_tidal_toss[3];
extern Hu3DQuadPool D_800EBEB0_minigame;
extern D_80111B50_vine_with_me_Struct D_8010AEB0_tidal_toss;

void func_80108638_tidal_toss(omObjData *);
void func_8002367C_main(HuMtx4F dst, HuMtx4F src);
void func_80021BE0_main(Hu3DQuadPool *pool, u16 numQuads);
void func_800E1804_minigame(void);
void func_800E4C88_minigame(omObjData *, u8, f32, f32, f32, f32, f32);
void func_800E1490_minigame(s32);
s32 func_8000B638_main(void);
void func_80105B04_tidal_toss(omObjData *object);
void func_8010600C_tidal_toss(void);
void func_801085A4_tidal_toss(void);
void func_80106104_tidal_toss(omObjData *);
void func_80106480_tidal_toss(omObjData *);
void func_80106514_tidal_toss(omObjData *);
void func_801065AC_tidal_toss(omObjData *);
void func_80106D24_tidal_toss(Gfx **, s32, s32);
f32 atan2df(f32, f32);
void func_800E12EC_minigame(omObjData *, f32);
void func_800E1328_minigame(omObjData *, f32);
void func_800E1334_minigame(omObjData *, f32);
void func_800E1340_minigame(omObjData *, f32);
void func_800E1304_minigame(omObjData *, f32);
void func_800E1310_minigame(omObjData *, f32);
void func_800E131C_minigame(omObjData *, f32);
void func_800E1404_minigame(omObjData *, f32, f32);
u32 func_800E4A90_minigame(omObjData *);
s32 func_8010A7F8_tidal_toss(void);
u16 func_8010A11C_tidal_toss(omObjData *);
omObjData *func_80045ED0_main(s32 arg0);
void func_800DDD94_minigame(omObjData *);
void func_8010A7E4_tidal_toss(omObjData *, func_800E1BA8_minigame_ObjData **, TidalTossWork **);
void func_80105C80_tidal_toss(HuMtx4F, HuMtx4F);
s16 func_8010A90C_tidal_toss(s32);
s16 func_8010A954_tidal_toss(s16, s16);
void func_800E149C_minigame(omObjData *, s32, s32);
void func_800E5978_minigame(omObjData *, u16, s32, u16, u16);
void func_8010961C_tidal_toss(omObjData *);
void func_80109180_tidal_toss(omObjData *);

void func_801059A0_tidal_toss(void) {
    omObjData *obj;
    u8 camIndex;

    Hu3DAnimInit(3);
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
    func_80105B04_tidal_toss(obj);
    func_8010600C_tidal_toss();
    memset(&D_8010AEB0_tidal_toss, 0, 0x28);
    D_8010AEB0_tidal_toss.unk01 = 4;
    func_800E5EA0_minigame(&D_8010AEB0_tidal_toss);
    func_801085A4_tidal_toss();
}

void func_80105B04_tidal_toss(omObjData *object) {
    HuCamera *camera;
    f32 sinFov;
    f32 cosFov;

    CZoom = 1600.0f;
    CRot.x = -30.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 110.0f;
    Center.z = 0.0f;
    omOutView(object);

    camera = gCameraList;
    sinFov = sindf(camera->fov / 2.0);
    cosFov = cosdf(camera->fov / 2.0);
    D_8010B0D8_tidal_toss = sinFov / cosFov;
    guMtxL2F(D_8010B058_tidal_toss, &camera->mtxs[0].lookAtMtx);
    guMtxL2F(D_8010B098_tidal_toss, &camera->mtxs[0].lookAtMtx);
    func_80105C80_tidal_toss(D_8010B098_tidal_toss, D_8010B098_tidal_toss);
}

void func_80105C00_tidal_toss(HuMtx4F mtx, f32 x, f32 y, f32 z, f32 *dst) {
    dst[0] = ((x * mtx[0][0]) + (y * mtx[1][0])) + (z * mtx[2][0]);
    dst[1] = ((x * mtx[0][1]) + (y * mtx[1][1])) + (z * mtx[2][1]);
    dst[2] = ((x * mtx[0][2]) + (y * mtx[1][2])) + (z * mtx[2][2]);
}

void func_80105C80_tidal_toss(HuMtx4F src, HuMtx4F dst) {
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

        func_80105C00_tidal_toss(dst, -mtx[3][0], -mtx[3][1], -mtx[3][2], dstRow3);
    }
}

void func_80105E70_tidal_toss(f32 *arg0, f32 *dst) {
    f32 mtx[4][4];
    f32 depth;
    f32 scale;

    guTranslateF(mtx, arg0[0], arg0[1], arg0[2]);
    guMtxCatF(mtx, D_8010B058_tidal_toss, mtx);
    depth = mtx[3][2] * D_8010B0D8_tidal_toss;
    scale = __builtin_fabsf(depth);
    if (scale == 0.0) {
        return;
    }
    dst[0] = mtx[3][0] * 160.0f / scale / 1.3333334f;
    dst[1] = -mtx[3][1] * 120.0f / scale;
}

void func_80105F40_tidal_toss(f32 x, f32 y, f32 z, f32 *dst) {
    f32 depth = z + D_8010B090_tidal_toss;
    f32 scale = __builtin_fabsf(depth * D_8010B0D8_tidal_toss);
    f32 mtx[4][4];

    guTranslateF(mtx, ((x + x) * scale * 1.3333334f) / 320.0f, -((y + y) * scale / 240.0f), depth);
    guMtxCatF(mtx, D_8010B098_tidal_toss, mtx);
    dst[0] = mtx[3][0];
    dst[1] = mtx[3][1];
    dst[2] = mtx[3][2];
}

void func_8010600C_tidal_toss(void) {
    D_800EBE28_minigame = 0;
    func_800E1490_minigame(0);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(5, 1, 0, -1, func_80106104_tidal_toss);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(5, 1, 0, -1, func_80106480_tidal_toss);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(5, 1, 0, -1, func_80106514_tidal_toss);
    D_8010AF40_tidal_toss = 0;
}

void func_80106104_tidal_toss(omObjData *object) {
    TidalTossSetupWork *work;
    TidalTossStruct *entry;
    TidalTossSpriteWork *spriteWork;
    s16 *spriteGroup;
    s16 *setupSpriteGroup;
    s16 setupSpriteId;
    s16 model;
    f32 zero;
    f32 scale;
    s32 i;

    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 0;
    func_800E131C_minigame(object, 20.0f);
    func_800E1304_minigame(object, 0.5f);
    func_800E1310_minigame(object, 10.0f);
    func_800E1404_minigame(object, 0.0f, 730.0f);

    D_8010AED8_tidal_toss = func_8010A90C_tidal_toss(0x2B0000);
    setupSpriteId = func_8010A954_tidal_toss(D_8010AED8_tidal_toss, 1);
    setupSpriteGroup = &D_8010AEE8_tidal_toss;
    *setupSpriteGroup = setupSpriteId;
    HuSprPosSet(*setupSpriteGroup, 0, 160, 120);
    HuSprAttrSet(*setupSpriteGroup, 0, 0x4000);

    model = func_8000B108_main(0x2B0003, 0x4002CD);
    object->model[0] = model;
    D_8010AF38_tidal_toss = model;
    func_8001C954_main(object->model[0]);
    object->model[1] = func_8000B108_main(0x2B0004, 0x2D9);
    object->model[2] = Hu3DHookFuncCreate(0x80, func_80106D24_tidal_toss, 2);
    D_8010AF3A_tidal_toss = func_8010A90C_tidal_toss(0x2B0001);

    entry = D_8010AF48_tidal_toss;
    zero = 0.0f;
    for (i = 0; i < 8; i++) {
        entry->unk10 = 0;
        entry->unk0C = zero;
        entry->unk08 = zero;
        entry->unk04 = zero;
        entry->unk00 = zero;
        entry++;
    }

    D_8010AEDA_tidal_toss = func_8010A90C_tidal_toss(0x2B0002);
    D_8010AEEC_tidal_toss = func_8010A954_tidal_toss(D_8010AEDA_tidal_toss, 3);
    spriteWork = D_8010AFE8_tidal_toss;
    for (i = 0; i < 3; i++) {
        spriteWork->unk04 = (f32)D_8010AA74_tidal_toss[i][0];
        spriteWork->unk00 = spriteWork->unk04;
        spriteWork->unk08 = (f32)D_8010AA74_tidal_toss[i][1];
        spriteWork->unk02 = spriteWork->unk08;
        scale = D_8010AA80_tidal_toss[i];
        spriteWork->unk10 = scale;
        spriteWork->unk0C = scale;
        spriteWork->unk14 = (f32)((f64)(f32)func_8010A7F8_tidal_toss() * 1.52587890625e-05 * 360.0);
        spriteWork->unk18 = (f32)((f64)(f32)func_8010A7F8_tidal_toss() * 1.52587890625e-05 * 360.0);
        spriteWork->unk1C = (f32)((f64)(f32)func_8010A7F8_tidal_toss() * 1.52587890625e-05 * 2.0 + 2.0);
        spriteWork->unk20 = (f32)((f64)(f32)func_8010A7F8_tidal_toss() * 1.52587890625e-05 * 1.5 + 1.0);
        spriteGroup = &D_8010AEEC_tidal_toss;
        HuSprAttrSet(*spriteGroup, (s16)i, 0x20005808);
        HuSprPosSet(*spriteGroup, (s16)i, spriteWork->unk00, spriteWork->unk02);
        spriteWork++;
    }

    object->func = func_801065AC_tidal_toss;
}

void func_80106480_tidal_toss(omObjData *object) {
    TidalTossSetupWork *work;

    work = HuMemAllocTag(sizeof(TidalTossSetupWork), TAG_OVERLAY);
    object->data = work;
    memset(work, 0, sizeof(TidalTossSetupWork));
    work->unk03 = 1;
    work->unk04 = 0;
    func_800E131C_minigame(object, 20.0f);
    func_800E1304_minigame(object, 5.0f);
    func_800E1310_minigame(object, 10.0f);
    func_800E1404_minigame(object, 20.0f, 345.0f);
    object->func = NULL;
}

void func_80106514_tidal_toss(omObjData *object) {
    TidalTossSetupWork *work;

    work = HuMemAllocTag(sizeof(TidalTossSetupWork), TAG_OVERLAY);
    object->data = work;
    memset(work, 0, sizeof(TidalTossSetupWork));
    work->unk03 = 1;
    work->unk04 = 0;
    func_800E131C_minigame(object, 20.0f);
    func_800E1304_minigame(object, 0.05f);
    func_800E1310_minigame(object, 20.0f);
    func_800E1404_minigame(object, -800.0f, 1380.0f);
    object->func = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_801065AC_tidal_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_80106D24_tidal_toss);

void func_80108460_tidal_toss(f32 arg0) {
    TidalTossStruct *entry;
    s32 i;

    entry = D_8010AF48_tidal_toss;
    for (i = 0; i < 8; i++) {
        if (entry->unk10 == 0) {
            entry->unk00 = 0.0f;
            if (arg0 <= 150.0) {
                HuAudFXPlay(0x343);
                entry->unk10 = 1;
                entry->unk08 = 20.0f;
                entry->unk04 = 60.0f;
                entry->unk0C = 16.0f;
            } else if (arg0 <= 250.0) {
                HuAudFXPlay(0x346);
                entry->unk10 = 2;
                entry->unk08 = 20.0f;
                entry->unk04 = 120.0f;
                entry->unk0C = 20.0f;
            } else {
                HuAudFXPlay(0x345);
                entry->unk10 = 3;
                entry->unk08 = 26.0f;
                entry->unk04 = 240.0f;
                entry->unk0C = 30.0f;
            }
            return;
        }
        entry++;
    }
}

void func_801085A4_tidal_toss(void) {
    s32 i;

    func_800E18D8_minigame();
    D_800EC280_minigame = 0;
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 0xF, 0x32, -1, func_80108638_tidal_toss);
    }
}

void func_80108638_tidal_toss(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    TidalTossWork *work;
    u8 playerIndex;
    u8 playerSlot;
    s8 character;
    u32 model;
    u16 modelTag;
    s32 motion;
    s32 i;
    f32 scale;

    playerSlot = D_8010AAB8_tidal_toss;
    playerIndex = D_8010AAB1_tidal_toss[playerSlot * 2];
    character = (s8)GwPlayer[playerIndex].chr;
    model = D_800A178C_main[character][0];
    motion = D_800A1790_main[character][0];
    modelTag = 0x2D9;
    func_800E1BA8_minigame(object, model, motion, playerIndex, modelTag, modelTag);

    data = object->data;
    data->unk50 &= 0xFFFE;
    data->unkEC = 0;
    playerSlot = D_8010AAB8_tidal_toss;
    object->trans.x = D_8010AABC_tidal_toss[playerSlot][0];
    object->trans.y = D_8010AABC_tidal_toss[playerSlot][1];
    object->trans.z = D_8010AABC_tidal_toss[playerSlot][2];
    data->unk3C = D_8010AAEC_tidal_toss[playerSlot];
    scale = data->unkAC;
    object->scale.z = scale;
    object->scale.y = scale;
    object->scale.x = scale;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);

    data->unk158 = HuMemAllocTag(0x64, TAG_OVERLAY);
    memset(data->unk158, 0, 0x64);
    work = data->unk158;
    work->unk2B = playerIndex;
    playerSlot = D_8010AAB8_tidal_toss;
    work->unk2D = GwPlayer[playerSlot].group;
    work->unk2C = character;
    work->unk30 = GwPlayer[playerIndex].stat & 1;
    work->unk2E = GwPlayer[playerIndex].cpu_difficulty;
    work->unk2F = 0;
    work->unk1C = 11.0f;
    work->unk00 = object->trans.x;
    work->unk04 = object->trans.y;
    work->unk08 = object->trans.z;

    if (work->unk2D != 0) {
        playerSlot = D_8010AAB9_tidal_toss;
        object->trans.x = D_8010AABC_tidal_toss[playerSlot + 1][0];
        object->trans.y = D_8010AABC_tidal_toss[playerSlot + 1][1];
        object->trans.z = D_8010AABC_tidal_toss[playerSlot + 1][2];
        data->unk3C = D_8010AAEC_tidal_toss[playerSlot + 1];
        func_800E149C_minigame(object, 0, 2);
        func_800E149C_minigame(object, 1, 1);
        func_800E149C_minigame(object, 2, 1);
        data->unk50 |= 0x8000;
        object->func = func_8010961C_tidal_toss;
        D_8010AAB9_tidal_toss++;
    } else {
        object->trans.x = D_8010AABC_tidal_toss[0][0];
        object->trans.y = D_8010AABC_tidal_toss[0][1];
        object->trans.z = D_8010AABC_tidal_toss[0][2];
        data->unk3C = D_8010AAEC_tidal_toss[0];
        func_800E149C_minigame(object, 0, 1);
        func_800E149C_minigame(object, 1, 2);
        func_800E149C_minigame(object, 2, 1);
        object->model[9] = func_8000B108_main(0x2B0005, modelTag);
        Hu3DModelPosSet(object->model[9], object->trans.x, object->trans.y,
                        object->trans.z + 20.0);
        D_8010AA70_tidal_toss = data->unk59;
        object->func = func_80109180_tidal_toss;
    }

    modelTag = 0x2DD;
    if (work->unk2D != 0) {
        for (i = 9; i < 12; i++) {
            object->model[i] = func_8000B108_main(0x320003, modelTag);
            Hu3DMotionSpeedSet(object->model[i], 0.5f);
            Hu3DModelScaleSet(object->model[i], 1.0f, 1.0f, 1.0f);
        }
    }

    func_800E5A00_minigame(object, 0, func_80017BB8_main(character, 0), 1, 0);
    func_800E5A00_minigame(object, 6, func_80017BB8_main(character, 4), 1, 0x13);
    func_800E5A00_minigame(object, 0x15, func_80017BB8_main(character, 0x1F), 0, 0x13);

    if (work->unk2D != 0) {
        func_800E5A00_minigame(object, 1, func_80017BB8_main(character, 1), 1, 0);
        func_800E5A00_minigame(object, 2, func_80017BB8_main(character, 1), 1, 0);
        func_800E5A00_minigame(object, 0x11, func_80017BB8_main(character, 0xE), 0, 0);
        func_800E5A00_minigame(object, 0x20, func_80017BB8_main(character, 0x22), 0, 0);
        func_800E5A00_minigame(object, 9, func_80017BB8_main(character, 7), 1, 0x27);
        func_800E5A00_minigame(object, 0xA, func_80017BB8_main(character, 0x11), 1, 0x27);
        func_800E5978_minigame(object, 0x21, func_80017BB8_main(character, 0x23), 2, 0);
        func_800E5A00_minigame(object, 0x22, func_80017BB8_main(character, 0x24), 2, 0);
        work->unk24 = model | 0x2F;
        func_800E5A00_minigame(object, 0xD, func_80017BB8_main(character, 0x2F), 1, 0x78);
        func_800E5A00_minigame(object, 0xE, func_80017BB8_main(character, 0x36), 1, 0x78);
    } else {
        func_800E5A00_minigame(object, 8, func_80017BB8_main(character, 6), 1, 0x1D);
        func_800E5A00_minigame(object, 0x12, func_80017BB8_main(character, 0xF), 2, 0);
        switch (model >> 16) {
            case 2:
                work->unk24 = model | 0x30;
                func_800E5A00_minigame(object, 0xD, func_80017BB8_main(character, 0x30), 1, 0x78);
                func_800E5A00_minigame(object, 0xE, func_80017BB8_main(character, 0x38), 1, 0x64);
                break;
            case 3:
                work->unk24 = model | 0x30;
                func_800E5A00_minigame(object, 0xD, func_80017BB8_main(character, 0x30), 1, 0x78);
                func_800E5A00_minigame(object, 0xE, func_80017BB8_main(character, 0x38), 1, 0x64);
                break;
            case 7:
                work->unk24 = model | 0x30;
                func_800E5A00_minigame(object, 0xD, func_80017BB8_main(character, 0x30), 1, 0x78);
                func_800E5A00_minigame(object, 0xE, func_80017BB8_main(character, 0x36), 1, 0x78);
                break;
            case 5:
                work->unk24 = model | 0x2F;
                func_800E5A00_minigame(object, 0xD, func_80017BB8_main(character, 0x2F), 1, 0x78);
                func_800E5A00_minigame(object, 0xE, func_80017BB8_main(character, 0x38), 1, 0x64);
                break;
            case 6:
                work->unk24 = model | 0x2F;
                func_800E5A00_minigame(object, 0xD, func_80017BB8_main(character, 0x2F), 1, 0x78);
                func_800E5A00_minigame(object, 0xE, func_80017BB8_main(character, 0x38), 1, 0x64);
                break;
            case 9:
                work->unk24 = model | 0x2F;
                func_800E5A00_minigame(object, 0xD, func_80017BB8_main(character, 0x2F), 1, 0x78);
                func_800E5A00_minigame(object, 0xE, func_80017BB8_main(character, 0x38), 1, 0x64);
                break;
            case 4:
            case 8:
            default:
                work->unk24 = model | 0x2F;
                func_800E5A00_minigame(object, 0xD, func_80017BB8_main(character, 0x2F), 1, 0x78);
                func_800E5A00_minigame(object, 0xE, func_80017BB8_main(character, 0x36), 1, 0x78);
                break;
        }
    }

    func_800E5690_minigame(object, 0);

    D_8010AAB8_tidal_toss++;
}

void func_80108F08_tidal_toss(omObjData *object, s32 arg1, s32 arg2, u16 player, u16 tag) {
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

void func_80109180_tidal_toss(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    TidalTossWork *work;
    u8 player;
    u16 status;
    s32 random;
    f32 y;
    f32 zero;

    data = object->data;
    work = data->unk158;
    player = data->unk57;

    switch (D_8010AF40_tidal_toss) {
        case 0:
            work->unk44 = 0.0f;
            random = func_8010A7F8_tidal_toss();
            work->unk36 = (s32)((f64)(f32)random * 1.52587890625e-05 * 12.0);
            work->unk38 = 0;
            break;
        case 1:
            break;
        case 2:
            if (work->unk30 != 0) {
                D_800D20A1_main[player] = 0;
                D_800CBB6E_main[player] = 0;
                D_800D5558_main[player] = 0;
                D_800CDA7C_main[player] = 0;
                func_8010A11C_tidal_toss(object);
            }
            break;
        case 3:
        case 4:
            D_800CBB6E_main[player] = 0;
            D_800D20A1_main[player] = -64;
            D_800D5558_main[player] = 0;
            D_800CDA7C_main[player] = 0;
            break;
        case 5:
            if (work->unk2F == 1) {
                func_800E5690_minigame(object, 0xD);
                func_80045ED0_main(work->unk24);
                GwPlayer[data->unk59].bonusCoin += 10;
                work->unk2F++;
            } else if (work->unk2F == 0) {
                func_800E5690_minigame(object, 0xE);
                work->unk2F--;
            }
            break;
        case 6:
            if (data != NULL) {
                HuMemFree(data->unk158);
                object->data = NULL;
                object->func = NULL;
            }
            return;
        case 7:
            return;
    }

    status = func_800E4A90_minigame(object);
    work->unk0C = object->trans.x;
    work->unk10 = object->trans.y;
    work->unk14 = object->trans.z;
    if (status & 0x20) {
        D_800D20A1_main[player] = 0;
        D_800CBB6E_main[player] = 0;
    }

    func_800DDD94_minigame(object);
    func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);

    if (status & 0x200) {
        if ((data->unk50 & 0x80) && (work->unk2A == 0)) {
            func_80108460_tidal_toss(work->unk20);
            work->unk2A++;
        }
        if (!(work->unk28 & 0x200)) {
            work->unk20 = object->trans.y - 20.0;
            work->unk2A = 0;
        }
    } else if ((work->unk28 & 0x20) && !(status & 0x20)) {
        func_80108460_tidal_toss(100.0f);
        work->unk20 = 100.0f;
    }

    work->unk44 += 4.0;
    if (work->unk44 >= 360.0) {
        work->unk44 -= 360.0;
    }

    if ((work->unk20 > 20.0) && (work->unk2A != 0)) {
        y = 20.0 - work->unk20 * 0.075;
        work->unk20 *= 0.8;
    } else {
        y = 20.0 - sindf(work->unk44) * 5.0;
    }

    Hu3DModelPosSet(object->model[9], 0.0f, y, 0.0f);
    if (!(status & 0x220)) {
        object->trans.y = y;
    }
    zero = 0.0f;
    object->trans.z = zero;
    object->trans.x = zero;
    work->unk28 = status;
}

void func_80109584_tidal_toss(omObjData *arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 i;

    for (i = 9; i < 12; i++) {
        if (HmfModelData[arg0->model[i]].attr & 4) {
            func_800E4C88_minigame(arg0, i, arg1, arg2, arg3, 0.0f, 0.0f);
            return;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_8010961C_tidal_toss);

u16 func_8010A11C_tidal_toss(omObjData *object) {
    TidalTossWork *work;
    func_800E1BA8_minigame_ObjData *data;
    s16 player;
    s32 status;
    s32 random;
    u16 result;

    func_8010A7E4_tidal_toss(object, &data, &work);
    player = data->unk57;
    status = func_800E4A90_minigame(object);

    switch (work->unk32) {
        case 1:
            if (work->unk2E == 0) {
                D_800CDA7C_main[player] |= 0x8000;
            }
            if (status & 0x20) {
                work->unk32++;
            } else {
                D_800D5558_main[player] |= 0x8000;
            }
            break;
        case 2:
            if (work->unk2E == 0) {
                D_800CDA7C_main[player] |= 0x8000;
            }
            if (!(status & 0x20)) {
                work->unk32 = 0;
            }
            break;
        case 3:
            if (status & 2) {
                D_800D5558_main[player] |= 0x8000;
                work->unk32++;
            }
            break;
        case 4:
            D_800CDA7C_main[player] |= 0x8000;
            if ((f64)(f32)work->unk34 <= object->trans.y - 20.0) {
                D_800D5558_main[player] |= 0x2000;
                work->unk32++;
            }
            break;
        case 5:
            if (status & 2) {
                work->unk32 = 0;
            }
            break;
    }

    if (work->unk32 == 0) {
        random = func_8010A7F8_tidal_toss();
        if (random % (6 - work->unk2E) == 0) {
            work->unk38 = 5;
            random = func_8010A7F8_tidal_toss();
            if (random % (work->unk2E + 3) == 0 || work->unk36 == 0) {
                work->unk32 = 3;
                random = func_8010A7F8_tidal_toss();
                work->unk34 = (s32)((f64)(f32)random * 1.52587890625e-05 * 10.0) * 10 + 170;
                random = func_8010A7F8_tidal_toss();
                work->unk36 = (s32)((f64)(f32)random * 1.52587890625e-05 * 8.0) + 8;
            } else {
                work->unk32 = 1;
                work->unk34 = 400;
                work->unk36--;
            }
        }
    }

    return result;
}

u16 func_8010A490_tidal_toss(omObjData *arg0, f32 arg1) {
    TidalTossWork *work;
    func_800E1BA8_minigame_ObjData *data;
    TidalTossStruct *entry;
    f32 distance;
    f64 distanceD;
    f32 absDistance;
    f32 radius;
    u32 status;
    s16 player;
    s32 i;
    s32 random;
    u16 result; // The original function returns this uninitialized value; its caller ignores it.

    func_8010A7E4_tidal_toss(arg0, &data, &work);
    {
        f32 unused[2]; // Unused stack space retained from the original function.
    }
    player = data->unk57;
    status = func_800E4A90_minigame(arg0);
    entry = D_8010AF48_tidal_toss;

    for (i = 0; i < 8; i++) {
        if (entry->unk10 != 0) {
            distance = entry->unk00 - arg1;
            distanceD = distance;
            absDistance = __builtin_fabsf(distance);
            radius = entry->unk08 + (7.25 - (f32)entry->unk10 + (f32)work->unk2E * 0.25) * 20.0;
            if (absDistance <= radius) {
                if (distanceD <= 0.0) {
                    random = (s32)((f32)func_8010A7F8_tidal_toss() * 1.52587890625e-05 * 100.0);
                    if (random < work->unk2E * 10 + 45) {
                        D_800D5558_main[player] |= 0x8000;
                        switch (work->unk2E) {
                            case 0:
                            case 1:
                                work->unk32 = 10;
                                break;
                            case 2:
                                if (entry->unk10 != 1) {
                                    work->unk32 = 10;
                                } else {
                                    work->unk32 = 0;
                                }
                                break;
                            case 3:
                                if (entry->unk10 == 3) {
                                    work->unk32 = 10;
                                } else {
                                    work->unk32 = 0;
                                }
                                break;
                        }
                        break;
                    }
                }
            }
        }
        entry++;
    }

    if (work->unk32 != 0) {
        work->unk32--;
        D_800CDA7C_main[player] |= 0x8000;
    }

    if (240.0 < arg1 && !(status & 0x20)) {
        D_800CBB6E_main[player] = (work->unk2E * 4.0 + 53.0) * -arg0->trans.x / arg1;
        D_800D20A1_main[player] = (work->unk2E * 4.0 + 53.0) * arg0->trans.z / arg1;
    }

    return result;
}

void func_8010A7E4_tidal_toss(omObjData *arg0, func_800E1BA8_minigame_ObjData **arg1, TidalTossWork **arg2) {
    *arg1 = arg0->data;
    *arg2 = (*arg1)->unk158;
}

s32 func_8010A7F8_tidal_toss(void) {
    D_8010AAFC_tidal_toss = D_8010AAFC_tidal_toss * 0x41C64E6D + 0x3039;
    D_8010AAFC_tidal_toss += rand8();
    return D_8010AAFC_tidal_toss >> 16;
}

f32 func_8010A850_tidal_toss(Vec *arg0, Vec *arg1) {
    return sqrtf(((arg0->x - arg1->x) * (arg0->x - arg1->x)) +
                 ((arg0->z - arg1->z) * (arg0->z - arg1->z)));
}

f32 func_8010A8A4_tidal_toss(f32 arg0, f32 arg1) {
    f32 angle;
    f32 fullRot = 360.0f;

    angle = atan2df(arg0, arg1);
    if (angle < 0.0f) {
        angle += fullRot;
    } else if (fullRot <= angle) {
        angle -= fullRot;
    }
    return angle;
}

s16 func_8010A90C_tidal_toss(s32 arg0) {
    void *temp_v0;
    s16 temp_s0;

    temp_v0 = DataRead(arg0);
    temp_s0 = HuSprAnimRead(temp_v0);
    DataClose(temp_v0);
    return temp_s0;
}

s16 func_8010A954_tidal_toss(s16 arg0, s16 arg1) {
    s16 spriteId;
    s32 i;

    if (arg0 == -1) {
        return -1;
    }
    spriteId = HuSprGrpCreate(arg1, 0);
    if (spriteId == -1) {
        return -1;
    }
    for (i = 0; i < arg1; i++) {
        HuSprGrpMemberSet(spriteId, i, arg0, 0);
    }
    return spriteId;
}

HuSprite_Unk84_Unk00_Struct *func_8010AA1C_tidal_toss(s16 arg0, s16 arg1) {
    return &func_80055194_main(arg0)->unk00[arg1];
}
