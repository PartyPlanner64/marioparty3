#include "common.h"


extern u16 D_800A1902_main;

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_801059A0_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_80105D40_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110E60_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_80105F48_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_80106610_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_801066A0_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_80106D28_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110EB8_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110F34_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110F40_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110F7C_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110F84_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110F8C_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_80106D4C_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110FA8_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110FC8_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_80108DE8_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_8010AE4C_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_8010AE80_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_8010AEAC_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_8010AED8_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111030_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111050_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111070_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_8010AF04_ridiculous_relay);

f32 func_8010B474_ridiculous_relay(f32 x) {
    Vec pos;
    Vec2f out;

    pos.x = x;
    pos.y = 0.0f;
    pos.z = 0.0f;
    func_80012B14_main(1, &pos, &out);
    return out.x;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_8011108C_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_801110D4_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_8011111C_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111164_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111178_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111184_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111194_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_801111A4_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_801111B4_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_8010B4A8_ridiculous_relay);

s16 func_80110BF4_ridiculous_relay(s16 arg0, s16 arg1) {
    if (D_800A1902_main == 0) {
        return 0;
    }
    if (arg0 == 0) {
        return 0;
    }
    return func_8004AC5C_main(arg0, 0);
}

s16 func_80110C3C_ridiculous_relay(s16 seId, s16 playerIdx) {
    if (D_800A1902_main == 0) {
        return 0;
    }
    if (seId == 0) {
        return 0;
    }
    return func_8004AC5C_main(seId + GwPlayer[playerIdx].chr + 1, 0);
}
