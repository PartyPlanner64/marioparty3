#include "common.h"

extern u8 D_80118EB1_mgmode;
extern u16 D_80118EB4_mgmode;
extern s16 D_8011B884_mgmode;
extern Gfx D_80119290_mgmode[];

void func_8010BD98_mgmode(omObjData *arg0);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_801059A0_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A400_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A404_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A40C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010606C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_80107298_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_80107610_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A430_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A434_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A43C_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A444_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A44C_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A454_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A45C_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A464_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A46C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_801076B0_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A484_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A490_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A49C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_80107D0C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_80108824_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_80108C88_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_80108CF4_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_80108DDC_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_801090C4_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_80109C10_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_80109DBC_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010A148_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010A5F0_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010A62C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010A824_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010A8E4_mgmode);

void func_8010AF78_mgmode(Gfx **arg0, s32 arg1, s32 arg2) {
    if (D_8011B884_mgmode != 0) {
        gDPSetDepthImage((*arg0)++, 0x3D0800);
        gDPSetColorImage((*arg0)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, 0x3D0800);
        gSPDisplayList((*arg0)++, D_80119290_mgmode);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010AFEC_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010B574_mgmode);

void func_8010BD28_mgmode(omObjData *arg0) {
    if ((D_80118EB1_mgmode != 0) || (D_800D530C_main != 0)) {
        if ((D_80118EB4_mgmode & 0x80) == 0) {
            WipeCreateOut(0xB, 8);
            HuAudSeqFadeOut(0x3C);
        }
        arg0->func = func_8010BD98_mgmode;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010BD98_mgmode);
