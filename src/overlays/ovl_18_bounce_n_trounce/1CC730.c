#include "common.h"

// Per-player work, allocated in func_801069F0_bounce_n_trounce
typedef struct BounceNTrounceWork {
    /* 0x00 */ s16 playerId;
    /* 0x02 */ s16 state;
    /* 0x04 */ char pad_04[0xA];
    /* 0x0E */ u16 unk_0E[4];
    /* 0x16 */ char pad_16[0x2E];
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;
} BounceNTrounceWork; // Size 0x4C

extern s16 D_8010AEBC_bounce_n_trounce;
extern omObjData *D_8010AEC0_bounce_n_trounce;
extern omObjData *D_8010AEC4_bounce_n_trounce;
extern s16 D_8010AECC_bounce_n_trounce;
extern omObjData **D_8010AEDC_bounce_n_trounce;

void func_80105CBC_bounce_n_trounce(omObjData *);
void func_80108CA8_bounce_n_trounce(omObjData *);
void func_80108D28_bounce_n_trounce(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_801059A0_bounce_n_trounce);

void func_80105C84_bounce_n_trounce(omObjData *arg0) {
    D_8010AEBC_bounce_n_trounce = 4;
    D_8010AEC4_bounce_n_trounce = 0;
    D_8010AEC0_bounce_n_trounce = 0;
    D_8010AECC_bounce_n_trounce = 1;
    arg0->func = func_80105CBC_bounce_n_trounce;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80105CBC_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80105E4C_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80106268_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80106434_bounce_n_trounce);

void func_8010675C_bounce_n_trounce(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80106764_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80106854_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_801068F4_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_801069F0_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80106F78_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_801070CC_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80107114_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80107EDC_bounce_n_trounce);

void func_80108350_bounce_n_trounce(omObjData *object) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);

    if (work->state != 2 && work->state != 3) {
        work->state = 0;
    }
    work->unk_44 = 0.0f;
    work->unk_48 = 0.0f;
    func_8001C258_main(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80108398_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80108454_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_8010846C_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_801085EC_bounce_n_trounce);

void func_80108940_bounce_n_trounce(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        BounceNTrounceWork *work = OM_GET_DATA_PTR(D_8010AEDC_bounce_n_trounce[i], BounceNTrounceWork);
        s32 j;

        for (j = 0; j < 4; j++) {
            work->unk_0E[j] = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80108994_bounce_n_trounce);

void func_80108C18_bounce_n_trounce(omObjData *object) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);

    work->state = 4;
    func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DMotionShiftSet(object->model[1], HmfModelData[object->motion[3]].motId, 0, 6, 0);
    object->work[0] = 8;
    object->func = func_80108CA8_bounce_n_trounce;
}

void func_80108CA8_bounce_n_trounce(omObjData *object) {
    if (object->work[0] != 0) {
        object->work[0]--;
    } else {
        Hu3DMotionShiftSet(object->model[1], HmfModelData[object->motion[1]].motId, 0, 6, 2);
        object->func = func_80108D28_bounce_n_trounce;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80108D28_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80108EFC_bounce_n_trounce);

void func_80108F98_bounce_n_trounce(omObjData *object) {
    func_8001C258_main(object->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelPosSet(object->model[6], object->trans.x, object->trans.y + 5.0f, object->trans.z);
    func_8001C814_main(object->model[6], 3, 0);
    Hu3DMotionTimeSet(object->model[6], 0.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80109018_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80109478_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80109804_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80109A00_bounce_n_trounce);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", D_8010AE14_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80109AF0_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80109F68_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_8010A664_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_8010A740_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_8010A8F0_bounce_n_trounce);

f32 func_8010AAE0_bounce_n_trounce(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    return HuSqrtf((arg0 - arg2) * (arg0 - arg2) + (arg1 - arg3) * (arg1 - arg3));
}

s32 func_8010AB1C_bounce_n_trounce(f32 arg0, f32 arg1) {
    s32 x;
    s32 y;
    s16 index;

    arg0 += 450.0f;
    arg1 += 450.0f;
    x = arg0 / 300.0f;
    y = arg1 / 300.0f;
    index = x + y * 3;
    return (index >= 0 && index < 9) ? index : -1;
}
