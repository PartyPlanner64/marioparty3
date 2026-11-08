#include "common.h"
#include "overlays/mgmode.h"

extern MgmodeEsprite *D_8011B450_mgmode;
extern s16 D_8011B454_mgmode;
extern s16 D_8011B458_mgmode[8];

void func_801169C8_mgmode(MgmodeEsprite *arg0, s16 index);
void func_80116A48_mgmode(MgmodeEsprite *arg0, s16 index, f32 x, f32 y);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010BEC0_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010CB20_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010CBFC_mgmode);

void func_8010D308_mgmode(void) {
    s16 i;
    f32 scale;

    HuAudFXPlay(0x244);
    for (i = 0; i < 11; i++) {
        scale = cosdf(i / 10.0f * 90.0f);
        func_80116A48_mgmode(D_8011B450_mgmode, 0, scale, scale);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010D3B0_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010D98C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010DAB8_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010E1F0_mgmode);

void func_8010E40C_mgmode(void) {
    s16 i;

    for (i = 0; i < D_8011B454_mgmode; i++) {
        func_801169C8_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[i] + 4);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010E494_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010E6F0_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010EE84_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010F348_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010F648_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80110420_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80110554_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80111380_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80111B08_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80111BB0_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80111ED8_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80111F9C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80112060_mgmode);
