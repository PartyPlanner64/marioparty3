#include "common.h"

extern f32 D_8010AF8C_treadmill_grill[4];
extern f32 D_8010AF9C_treadmill_grill[4];
extern f32 D_8010B1B4_treadmill_grill[4];
extern f32 D_8010B1C4_treadmill_grill[4];

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801059A0_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80106008_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80106034_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801061E8_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801062DC_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801065DC_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801067A8_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80106DA0_treadmill_grill);

s32 func_80107230_treadmill_grill(void) {
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80107238_treadmill_grill);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", D_8010B288_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80107454_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80107798_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801084B4_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801085D8_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80108730_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80108888_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801089E0_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80108C64_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80108DE0_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80108FCC_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80109108_treadmill_grill);

void func_801093E0_treadmill_grill(s32 arg0, s32 arg1) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801093E8_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010980C_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80109FA8_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010A548_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010A6A4_treadmill_grill);

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
        hmf = HmfModelData[arg0->model[i]].hmf;
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
