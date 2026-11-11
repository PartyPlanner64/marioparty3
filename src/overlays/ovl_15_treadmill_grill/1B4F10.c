#include "common.h"
#include "gcc/memory.h"
#include "overlays/minigame.h"

extern s32 D_800A178C_main[][6];
extern omObjData *D_800EBE70_minigame[];

extern f32 D_8010AF8C_treadmill_grill[4];
extern f32 D_8010AF9C_treadmill_grill[4];
extern f32 D_8010B1B4_treadmill_grill[4];
extern f32 D_8010B1C4_treadmill_grill[4];
extern Vec D_8010AFB0_treadmill_grill[4];
extern D_80111B50_vine_with_me_Struct D_8010B03C_treadmill_grill;
extern f32 D_8010B064_treadmill_grill[];
extern s32 D_8010B098_treadmill_grill[];
extern Vec D_8010B378_treadmill_grill[];
extern s32 D_8010AF80_treadmill_grill;
extern f32 D_8010AFAC_treadmill_grill;
extern s32 D_8010B178_treadmill_grill;
extern f32 D_8010B17C_treadmill_grill[4];
extern s32 D_8010B19C_treadmill_grill;
extern s32 D_8010B1D4_treadmill_grill;
extern s32 D_8010B1D8_treadmill_grill;
extern s32 D_8010B1DC_treadmill_grill;
extern s32 D_8010B258_treadmill_grill;
extern s16 D_8010B310_treadmill_grill[16];

void func_801062DC_treadmill_grill(omObjData *object);
void func_801065DC_treadmill_grill(omObjData *object);
void func_801067A8_treadmill_grill(omObjData *object);
void func_80106DA0_treadmill_grill(omObjData *object, s32 model, s32 motion, u16 player, f32 x, f32 y, f32 z);
void func_801084B4_treadmill_grill(omObjData *object);
void func_801085D8_treadmill_grill(omObjData *object);
void func_80108730_treadmill_grill(omObjData *object);
void func_80108888_treadmill_grill(omObjData *object);
void func_801089E0_treadmill_grill(void);
void func_80108DE0_treadmill_grill(omObjData *object);
void func_80108FCC_treadmill_grill(omObjData *object);
void func_80109108_treadmill_grill(omObjData *object);

void func_801059A0_treadmill_grill(void) {
    u8 camIndex;

    func_8001FE20_main(50);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    func_800142A0_main(32);
    omInitObjMan(30, 0);
    func_8004A208_main();
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 20.0f, 80.0f, 8000.0f);
    Hu3DGLightDirSet(1, -35.0f, -114.0f, -3.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    D_800EB77C_minigame = 0.0f;
    func_800E19F0_minigame(0);
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(1, 1, 0, -1, func_801065DC_treadmill_grill);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(1, 16, 0, -1, func_801067A8_treadmill_grill);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 16, 60, -1, func_801084B4_treadmill_grill);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 16, 60, -1, func_801085D8_treadmill_grill);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 16, 60, -1, func_80108730_treadmill_grill);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 16, 60, -1, func_80108888_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_800EB73C_minigame = 10.0f;
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    func_800E5EA0_minigame(&D_8010B03C_treadmill_grill);
    D_800EB930_minigame = 53;
    D_800EB932_minigame = 20;
    Hu3DGLightDirSet(1, 86.0f, 45.0f, 74.0f);
    func_801089E0_treadmill_grill();
}

void func_80106008_treadmill_grill(omObjData *object) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

void func_80106034_treadmill_grill(omObjData *object) {
    omObjData *other;
    f32 scale;
    s32 i;

    if (WipeStatGet() == 0) {
        func_80109108_treadmill_grill(object);
        for (i = 0; i < D_800EC1B8_minigame; i++) {
            other = D_800EBE70_minigame[i];
            other->trans.x = D_8010B378_treadmill_grill[i].x;
            other->trans.y = D_8010B378_treadmill_grill[i].y;
            other->trans.z = D_8010B378_treadmill_grill[i].z;
            other->rot.y = atan2df(-other->trans.x, -other->trans.z);
            scale = D_8010B064_treadmill_grill[i] += 0.125f;
            if (scale > 2.3f) {
                scale = 2.3f;
            }
            if (scale < 0.0f) {
                scale = 0.0f;
            }
            other->scale.x = other->scale.y = other->scale.z = scale;
            if (scale > 1.0f && D_8010B098_treadmill_grill[i] == 0) {
                HuAudFXPlay(0x39F);
                D_8010B098_treadmill_grill[i]++;
            }
        }
    }
}

void func_801061E8_treadmill_grill(omObjData *object) {
    f32 scale;
    s32 i;

    for (i = 0; i < 3; i++) {
        scale = Hu3DData[object->model[10 + i]].scale.x;
        scale -= 0.1f;
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        Hu3DModelScaleSet(object->model[10 + i], scale, scale, scale);
        Hu3DModelScaleSet(object->model[13 + i], scale, scale, scale);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801062DC_treadmill_grill);

void func_801065DC_treadmill_grill(omObjData *object) {
    D_800EC1C0_minigame_ObjData *work;

    object->model[0] = func_8000B0A0_main(0x360005, 0xA9);
    object->trans.x = 100.0f;
    object->trans.y = 0.0f;
    object->trans.z = -1200.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    object->func = func_801062DC_treadmill_grill;
    work->unk03 = 1;
    CZoom = 3736.0f;
    CRot.x = 319.0f;
    CRot.y = 0.0f;
    Center.x = 0.0f;
    Center.y = 50.0f;
    Center.z = -350.0f;
    func_800E147C_minigame(object);
    func_800E139C_minigame(object, 0.0f, -1500.0f, -1500.0f, 1500.0f, 1500.0f);
    func_800E1304_minigame(object, 0.2f);
    func_800E1310_minigame(object, D_800EB73C_minigame);
    func_800E131C_minigame(object, 25.0f);
    work->unk04 = 0;
    func_8001C2FC_main(object->model[0], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(object->model[0]);
    func_8001C954_main(object->model[0]);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801067A8_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80106DA0_treadmill_grill);

s32 func_80107230_treadmill_grill(void) {
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80107238_treadmill_grill);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", D_8010B288_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80107454_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80107798_treadmill_grill);

void func_801084B4_treadmill_grill(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    s32 motion;
    s32 model;
    s32 i;

    motion = D_800A178C_main[GwPlayer[0].chr][1];
    model = D_800A178C_main[GwPlayer[0].chr][0];
    func_80106DA0_treadmill_grill(object, model, motion, 0, 0.0f, 250.0f, -500.0f);
    data = object->data;
    i = rand8() & 3;
    object->trans.x = D_8010AFB0_treadmill_grill[i].x;
    object->trans.y = D_8010AFB0_treadmill_grill[i].y;
    object->trans.z = D_8010AFB0_treadmill_grill[i].z;
    D_8010AFB0_treadmill_grill[i].x = D_8010AFB0_treadmill_grill[i].y = D_8010AFB0_treadmill_grill[i].z = 0.0f;
    data->unk3C = i * 90.0f + 135.0f;
}

void func_801085D8_treadmill_grill(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    s32 motion;
    s32 model;
    s32 i;

    motion = D_800A178C_main[GwPlayer[1].chr][1];
    model = D_800A178C_main[GwPlayer[1].chr][0];
    func_80106DA0_treadmill_grill(object, model, motion, 1, 0.0f, 250.0f, -300.0f);
    data = object->data;
    do {
        i = rand8() & 3;
    } while (D_8010AFB0_treadmill_grill[i].x == 0.0f);
    object->trans.x = D_8010AFB0_treadmill_grill[i].x;
    object->trans.y = D_8010AFB0_treadmill_grill[i].y;
    object->trans.z = D_8010AFB0_treadmill_grill[i].z;
    D_8010AFB0_treadmill_grill[i].x = D_8010AFB0_treadmill_grill[i].y = D_8010AFB0_treadmill_grill[i].z = 0.0f;
    data->unk3C = i * 90.0f + 135.0f;
}

void func_80108730_treadmill_grill(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    s32 motion;
    s32 model;
    s32 i;

    motion = D_800A178C_main[GwPlayer[2].chr][1];
    model = D_800A178C_main[GwPlayer[2].chr][0];
    func_80106DA0_treadmill_grill(object, model, motion, 2, 0.0f, 250.0f, -300.0f);
    data = object->data;
    do {
        i = rand8() & 3;
    } while (D_8010AFB0_treadmill_grill[i].x == 0.0f);
    object->trans.x = D_8010AFB0_treadmill_grill[i].x;
    object->trans.y = D_8010AFB0_treadmill_grill[i].y;
    object->trans.z = D_8010AFB0_treadmill_grill[i].z;
    D_8010AFB0_treadmill_grill[i].x = D_8010AFB0_treadmill_grill[i].y = D_8010AFB0_treadmill_grill[i].z = 0.0f;
    data->unk3C = i * 90.0f + 135.0f;
}

void func_80108888_treadmill_grill(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    s32 motion;
    s32 model;
    s32 i;

    motion = D_800A178C_main[GwPlayer[3].chr][1];
    model = D_800A178C_main[GwPlayer[3].chr][0];
    func_80106DA0_treadmill_grill(object, model, motion, 3, 0.0f, 250.0f, -300.0f);
    data = object->data;
    do {
        i = rand8() & 3;
    } while (D_8010AFB0_treadmill_grill[i].x == 0.0f);
    object->trans.x = D_8010AFB0_treadmill_grill[i].x;
    object->trans.y = D_8010AFB0_treadmill_grill[i].y;
    object->trans.z = D_8010AFB0_treadmill_grill[i].z;
    D_8010AFB0_treadmill_grill[i].x = D_8010AFB0_treadmill_grill[i].y = D_8010AFB0_treadmill_grill[i].z = 0.0f;
    data->unk3C = i * 90.0f + 135.0f;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801089E0_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80108C64_treadmill_grill);

void func_80108DE0_treadmill_grill(omObjData *object) {
    A96F0_ObjData *data;
    s32 i;

    object->data = HuMemAllocTag(sizeof(A96F0_ObjData), TAG_OVERLAY);
    memset(object->data, 0, sizeof(A96F0_ObjData));
    data = object->data;
    object->model[1] = 0;
    object->model[0] = D_8010B310_treadmill_grill[D_8010AF80_treadmill_grill++];
    object->func = func_80108FCC_treadmill_grill;
    data->unk44 = 0.3f;
    data->unk48 = 60.0f;
    data->unk34 = 150.0f;
    data->unk3C = 0.0f;
    data->unk78 = 0;
    data->unk52 = 3;
    data->unk7C = 0;
    data->unk50 = 32;
    data->unk40 = 0.0f;
    data->unk74 = 0.8f;
    data->unk54 = 1;
    for (i = 0; i < 9; i++) {
        data->unk84[i] = NULL;
    }
    data->unk56 = D_8010B178_treadmill_grill;
    func_800E149C_minigame(object, 0, 2);
    func_800E149C_minigame(object, 1, 2);
    object->trans.x = sindf(D_8010B178_treadmill_grill * 36.0f) * 450.0f;
    object->trans.y = 500.0f;
    object->trans.z = cosdf(D_8010B178_treadmill_grill * 36.0f) * 450.0f + -512.0f;
    object->scale.x = object->scale.y = object->scale.z = 0.0f;
    D_8010B178_treadmill_grill++;
}

void func_80108FCC_treadmill_grill(omObjData *object) {
    omObjData *stage;
    A96F0_ObjData *data;

    stage = D_800EC1C0_minigame[1];
    data = object->data;
    if (func_800E6E8C_minigame() == 2) {
        object->trans.x = D_8010B378_treadmill_grill[data->unk56].x;
        object->trans.y = D_8010B378_treadmill_grill[data->unk56].y;
        object->trans.z = D_8010B378_treadmill_grill[data->unk56].z;
        object->rot.y = atan2df(stage->trans.x - object->trans.x, stage->trans.z - object->trans.z);
        object->scale.x = object->scale.y = object->scale.z =
            sindf(D_8010AFAC_treadmill_grill * 5.0f + data->unk56 * 30) * 0.3f + 2.2f;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80109108_treadmill_grill);

void func_801093E0_treadmill_grill(s32 arg0, s32 arg1) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801093E8_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010980C_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80109FA8_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010A548_treadmill_grill);

void func_8010A6A4_treadmill_grill(void) {
    s32 i;

    if (D_8010B258_treadmill_grill++ < 2) {
        D_8010B19C_treadmill_grill = 50;
        D_8010B1DC_treadmill_grill = 0;
        for (i = 0; i < 4; i++) {
            D_8010B17C_treadmill_grill[i] = -D_8010B1B4_treadmill_grill[i] / 20.0f;
            D_8010B1C4_treadmill_grill[i] = -D_8010B1B4_treadmill_grill[i] / 20.0f;
        }
        D_8010B1D8_treadmill_grill = 20;
        D_8010B1D4_treadmill_grill = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010A754_treadmill_grill);

void func_8010A9AC_treadmill_grill(s32 arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        func_801093E0_treadmill_grill(arg0, i);
        D_8010B1B4_treadmill_grill[i] += D_8010B1C4_treadmill_grill[i];
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010AA2C_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010AB9C_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010ACBC_treadmill_grill);

void func_8010AE6C_treadmill_grill(omObjData *arg0) {
    HmfData *hmf;
    HmfVertexGroup *group;
    Vtx *vtx;
    s32 i;
    s32 j;
    s32 k;
    f32 scale;

    for (i = 0; i < 4; i++) {
        hmf = Hu3DData[arg0->model[i]].hmf;
        scale = D_8010AF8C_treadmill_grill[i] / D_8010AF9C_treadmill_grill[i];
        for (j = 0; j < hmf->unk1A; j++) {
            group = &hmf->unkB0[j];
            for (k = 0; k < group->count; k++) {
                vtx = &hmf->unk40[group->indices[k]];
                vtx->v.tc[0] = (s16)(vtx->v.tc[0] * scale);
            }
        }
    }
}
