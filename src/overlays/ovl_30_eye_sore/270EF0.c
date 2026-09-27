#include "common.h"

extern omObjData *D_8010AF70_eye_sore;

void func_8010605C_eye_sore(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_801059A0_eye_sore);

f32 func_801059BC_eye_sore(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 func_80105A3C_eye_sore(s32 arg0) {
    u32 ret = (rand8() & 0xFF) * arg0;
    return ret >> 8;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80105A74_eye_sore);

void func_80105B3C_eye_sore(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80105BB4_eye_sore);

s32 func_80105CE4_eye_sore(s32 arg0) {
    return rand8() % arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80105D38_eye_sore);

void func_80105DA0_eye_sore(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    func_8001C624_main(arg0->model[0], HmfModelData[arg0->motion[arg1]].unk02, arg2, arg3, arg4);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80105E0C_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80105F40_eye_sore);

void func_80106054_eye_sore(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010605C_eye_sore);

void func_80106210_eye_sore(void) {
    omObjData *obj = omAddObj(0x1F4, 3, 3, -1, func_8010605C_eye_sore);
    obj->work[0] = 0;
    D_8010AF70_eye_sore = obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80106250_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80106328_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010ADC8_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010ADD4_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010ADE0_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010ADEC_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010ADF8_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010AE04_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010AE10_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010AE1C_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_801063E8_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80106510_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80106718_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010683C_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_801070CC_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010725C_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80107804_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80107CBC_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80108330_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80108AAC_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80108BBC_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80108D3C_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80108E8C_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80109478_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80109854_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_801098F8_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010A0CC_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010A3C0_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010A464_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010A528_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010A54C_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010A62C_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010A684_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010A8EC_eye_sore);

void func_8010A97C_eye_sore(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010A984_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010AAF8_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010AF0C_eye_sore);
