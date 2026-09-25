#include "common.h"
#include "ovl_81.h"

extern f32 D_801014D8_name_81;

void func_800F413C_name_81(void);

void func_800F4208_name_81(void);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DBE50", func_800F4080_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DBE50", func_800F40E4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DBE50", func_800F413C_name_81);

void func_800F41DC_name_81(void) {
    omAddPrcObj(func_800F413C_name_81, 0x1002, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DBE50", func_800F4208_name_81);

void func_800F429C_name_81(void) {
    omAddPrcObj(func_800F4208_name_81, 0x1002, 0, 0);
}

s32 func_800F42C8_name_81(void) {
    return D_801014D8_name_81 == 304.0f;
}
