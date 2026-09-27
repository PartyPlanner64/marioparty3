#include "common.h"

extern omObjData *D_8010AAB0_slapdown;
extern omObjData *D_8010AB34_slapdown;

void func_80106608_slapdown(omObjData *);
void func_8010820C_slapdown(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801059A0_slapdown);

f32 func_801059BC_slapdown(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 func_80105A3C_slapdown(s32 arg0) {
    u32 ret = (rand8() & 0xFF) * arg0;
    return ret >> 8;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80105A74_slapdown);

void func_80105B3C_slapdown(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80105BB4_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80105CBC_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80106290_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_8010629C_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80106338_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801063D4_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80106534_slapdown);

void func_80106600_slapdown(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80106608_slapdown);

void func_801066A4_slapdown(void) {
    omObjData *obj = omAddObj(0x32, 1, 0, -1, func_80106608_slapdown);
    obj->work[0] = 0;
    D_8010AAB0_slapdown = obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801066E4_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80106780_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80106900_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80107858_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80107DCC_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80107FDC_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80108064_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801080D0_slapdown);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", D_8010A984_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801080FC_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_8010820C_slapdown);

void func_80108340_slapdown(void) {
    omObjData *obj = omAddObj(0x96, 1, 0, -1, func_8010820C_slapdown);
    obj->work[0] = 0;
    D_8010AB34_slapdown = obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80108380_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80108420_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801084BC_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80108BAC_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80108E44_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80108FE4_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_8010924C_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80109640_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801096E4_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801099C0_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80109D54_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80109E14_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80109E58_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80109E90_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80109EE8_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_8010A2B8_slapdown);

void func_8010A3D8_slapdown(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_8010A3E0_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_8010A550_slapdown);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", D_8010AA08_slapdown);
