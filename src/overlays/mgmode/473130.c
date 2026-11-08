#include "common.h"
#include "overlays/mgmode.h"

extern MgmodeEsprite *D_8011B450_mgmode;
extern s16 D_8011B454_mgmode;
extern s16 D_8011B458_mgmode[8];
extern u8 D_8011B430_mgmode[4];
extern u8 D_8011B434_mgmode;
extern s16 D_800CC438_main;
extern s16 D_800CE29C_main;
extern s16 D_800D03FE_main[4];
extern u8 D_80119430_mgmode[];
extern s16 D_800D4194_main;
extern s16 D_8011B6A8_mgmode;
extern MgmodeSpaceCoord D_80119424_mgmode[];

void func_8010CBFC_mgmode(void);
void func_801169C8_mgmode(MgmodeEsprite *arg0, s16 index);
void func_80116A48_mgmode(MgmodeEsprite *arg0, s16 index, f32 x, f32 y);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010BEC0_mgmode);

void func_8010CB20_mgmode(void) {
    HuWinMesSet(D_8011B6A8_mgmode, 0x5607, -1, -1);
    while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
        HuPrcVSleep();
    }
    func_80116ED4_mgmode(2, 10, 1, (void (*)(s16 *))-1);
    func_8010CBFC_mgmode();
    func_80116ED4_mgmode(5, 10, 1, (void (*)(s16 *))-1);
    func_8011822C_mgmode(D_80119424_mgmode);
    func_801181F4_mgmode(0);
    func_801182B4_mgmode(1);
    HuWinMesSet(D_8011B6A8_mgmode, 0x5600, -1, -1);
    while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
        HuPrcVSleep();
    }
}

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

u8 func_80110420_mgmode(s16 mgIndex) {
    s16 i;

    D_8011B434_mgmode = 0;
    if (D_800A6D40_main[mgIndex].minigameType != MINIGAME_ITEM) {
        for (i = 0; i < 4; i++) {
            if (GwPlayer[i].bonusCoin + GwPlayer[i].gameCoin >= 10) {
                D_8011B430_mgmode[D_8011B434_mgmode] = i;
                D_8011B434_mgmode++;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (GwPlayer[i].bonusCoin == 0) {
                D_8011B430_mgmode[D_8011B434_mgmode] = i;
                D_8011B434_mgmode++;
            }
        }
    }
    return D_8011B434_mgmode;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80110554_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80111380_mgmode);

s32 func_80111B08_mgmode(void) {
    s16 i;

    func_80110420_mgmode(D_800CE29C_main);
    for (i = 0; i < D_8011B434_mgmode; i++) {
        if (D_800D03FE_main[D_8011B430_mgmode[i]] + 1 >= D_80119430_mgmode[D_800CC438_main]) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80111BB0_mgmode);

void func_80111ED8_mgmode(void) {
    s16 i;

    for (i = 0; i < 6; i++) {
        func_80116A48_mgmode(D_8011B450_mgmode, D_800D4194_main + 4, 0.7f, (1.0f - i / 5.0f) * 0.7f);
        HuPrcVSleep();
    }
}

void func_80111F9C_mgmode(void) {
    s16 i;

    for (i = 0; i < 6; i++) {
        func_80116A48_mgmode(D_8011B450_mgmode, D_800CC438_main + 1, 0.7f, (1.0f - i / 5.0f) * 0.7f);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80112060_mgmode);
