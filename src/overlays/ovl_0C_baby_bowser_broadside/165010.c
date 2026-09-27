#include "common.h"

typedef struct BabyBowserBroadsideEntry {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ char unk_02[0x2E];
} BabyBowserBroadsideEntry; // Size 0x30

typedef struct unk_80109EBC {
    /* 0x00 */ char unk_00[0xC];
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ char unk_0E[0x46];
    /* 0x54 */ BabyBowserBroadsideEntry *unk_54;
} unk_80109EBC;

void func_8010A158_baby_bowser_broadside();

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_801059A0_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_801059BC_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80105B94_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80105DE4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80105E2C_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80105E64_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80105E88_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80105F64_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80106288_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_801062C4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80106E40_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80106E70_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80106EC4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80107140_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80107600_baby_bowser_broadside);

void func_80107630_baby_bowser_broadside(void) {
    Center.x = 0.0f;
    Center.y = 215.0f;
    Center.z = -144.0f;
    CRot.x = 322.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2410.0f;
    func_8010A158_baby_bowser_broadside(0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_801076AC_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80107854_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80107A00_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80107A80_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80107C64_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80107FE0_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_801081A4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80108210_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80108350_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80108614_baby_bowser_broadside);

void func_801087CC_baby_bowser_broadside(s16 arg0) {
    HmfModelData[arg0].unk44 = 1.0f;
    HmfModelData[arg0].unk40 = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80108804_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80108860_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80109058_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_8010913C_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80109434_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_801096E8_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_801098F8_baby_bowser_broadside);

s16 func_80109970_baby_bowser_broadside(unk_80109EBC *arg0) {
    s16 i;

    for (i = 0; i < 3; i++) {
        if (arg0->unk_54[i].unk_00 == 0) {
            break;
        }
    }
    if (i == 3) {
        return -1;
    }
    return i;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_801099D4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80109BD8_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80109D2C_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80109D94_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80109EB0_baby_bowser_broadside);

void func_80109EBC_baby_bowser_broadside(unk_80109EBC *arg0, s16 arg1) {
    arg0->unk_0C = arg1;
}
