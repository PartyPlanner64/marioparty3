#include "common.h"

extern u16 D_80106DB0_mchar2;
extern Vec D_80107048_mchar2;

void func_80106D80_mchar2(omObjData *arg0);

INCLUDE_ASM("asm/nonmatchings/overlays/mchar2/3D5C30", func_801059A0_mchar2);

INCLUDE_ASM("asm/nonmatchings/overlays/mchar2/3D5C30", func_80105B7C_mchar2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar2/3D5C30", D_80106E10_mchar2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar2/3D5C30", D_80106E1C_mchar2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar2/3D5C30", D_80106E28_mchar2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar2/3D5C30", D_80106E34_mchar2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar2/3D5C30", D_80106E40_mchar2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar2/3D5C30", D_80106E4C_mchar2);

INCLUDE_ASM("asm/nonmatchings/overlays/mchar2/3D5C30", func_80105C90_mchar2);

INCLUDE_ASM("asm/nonmatchings/overlays/mchar2/3D5C30", func_80106428_mchar2);

INCLUDE_ASM("asm/nonmatchings/overlays/mchar2/3D5C30", func_80106630_mchar2);

INCLUDE_ASM("asm/nonmatchings/overlays/mchar2/3D5C30", func_801067C4_mchar2);

void func_80106CA8_mchar2(void) {
    D_80107048_mchar2.x = D_80107048_mchar2.y = D_80107048_mchar2.z = 0.0f;
    CRot.x = CRot.y = CRot.z = 0.0f;
    CZoom = 400.0f;
    Center.x = Center.z = 0.0f;
    Center.y = 64.0f;
    gCameraList->fov[0] = 45.0f;
}

void func_80106D24_mchar2(omObjData *arg0) {
    if ((D_80106DB0_mchar2 != 0) || (D_800D530C_main != 0)) {
        WipeCreateOut(0, 8);
        arg0->func = func_80106D80_mchar2;
        HuAudSeqFadeOut(0x3C);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mchar2/3D5C30", func_80106D80_mchar2);
