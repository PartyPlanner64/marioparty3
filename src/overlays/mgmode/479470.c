#include "common.h"
#include "overlays/mgmode.h"

extern s16 D_8011B818_mgmode[28];
extern s16 D_8011B830_mgmode[16];
extern s16 D_8011B850_mgmode[16];
extern u8 *D_8011B610_mgmode[3];
extern MgmodeEsprite *D_801194C0_mgmode;

void func_801169C8_mgmode(MgmodeEsprite *arg0, s16 index);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80112200_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80112CF4_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80112F98_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80113204_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801134C0_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801136EC_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80114048_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801141EC_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80114344_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80114404_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80114614_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801146D8_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80114804_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801149F4_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80114C80_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80114EBC_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80114FA0_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801152C0_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115590_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115848_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115A9C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115BB8_mgmode);

void func_80115BE8_mgmode(void) {
    s16 i;

    func_801169C8_mgmode(D_801194C0_mgmode, 0xF);
    func_801169C8_mgmode(D_801194C0_mgmode, 0x10);

    for (i = 0; i < 4; i++) {
        func_801169C8_mgmode(D_801194C0_mgmode, i + 0x11);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115C5C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115CAC_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/479470", D_8011A688_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115CDC_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115E20_mgmode);

void func_80115E4C_mgmode(void) {
    s16 i;

    for (i = 0; i < 16; i++) {
        D_8011B850_mgmode[i] = D_8011B830_mgmode[i] = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115E9C_mgmode);

void func_80116024_mgmode(void) {
    s16 i;

    if (D_8011B830_mgmode[0] != GMES_ID_NONE) {
        GMesSprKill((GAMEMES *)((u8 *)D_8011B830_mgmode - offsetof(GAMEMES, strGId)));
        for (i = 0; i < 16; i++) {
            D_8011B850_mgmode[i] = D_8011B830_mgmode[i] = GMES_ID_NONE;
        }
    }
}

void func_801160A0_mgmode(s16 arg0) {
    int i;

    i = 0;
    if (D_8011B818_mgmode[0] > 0) {
        do {
            i++;
            HuSprTPLvlSet(D_8011B818_mgmode[12], (s16)i, arg0);
        } while ((s16)i < D_8011B818_mgmode[0]);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_8011611C_mgmode);

void func_80116260_mgmode(void) {
    memset(D_8011B610_mgmode[0], 0xFF, 0x4B00);
    memset(D_8011B610_mgmode[1], 0xFF, 0x4B00);
    memset(D_8011B610_mgmode[2], 0xFF, 0x4B00);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801162B4_mgmode);
