#include "common.h"

extern s16 D_8010A65C_game_guys_roulette;
extern s16 D_8010A678_game_guys_roulette;
extern u8 D_8010AB50_game_guys_roulette;

void func_801088B0_game_guys_roulette(omObjData *object);
void espAttrSet(u16 arg0, u16 arg1);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_801059A0_game_guys_roulette);

s32 func_801059BC_game_guys_roulette(f32 arg0) {
    u8 randomByte1 = rand8();
    u8 randomByte2 = rand8();
    s32 shiftedByte1 = (randomByte1 << 8);
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;

    return scaledRandom;
}

void func_80105A28_game_guys_roulette(void) {
    HmfLightColorSet(0, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, 0.0f, 0.0f, 95.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80105A78_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80105BD8_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80105C40_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80105CD0_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80105E10_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80105F70_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80106428_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_801068E8_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_801069DC_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80106B74_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80106C58_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80106DD8_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80106EA4_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_801070C4_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80107104_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_8010726C_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_801073AC_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80107A00_game_guys_roulette);

void func_80107AA8_game_guys_roulette(void) {
    if (++D_8010A65C_game_guys_roulette == 1) {
        GMesCreate(9);
    } else if (GMesStatGet() == GMES_STAT_NONE) {
        HuAudSeqFadeOut(0x1E);
        D_8010AB50_game_guys_roulette = 9;
        D_8010A65C_game_guys_roulette = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80107B20_game_guys_roulette);

void func_80108414_game_guys_roulette(void) {
    if (++D_8010A678_game_guys_roulette == 1) {
        GMesCreate(0x14);
        HuAudSeqFadeOut(0x78);
    } else if (GMesStatGet() == GMES_STAT_NONE) {
        D_8010AB50_game_guys_roulette = 0xB;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A770_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A77C_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A78C_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A794_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A7A0_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A7AC_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A7B8_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A7C4_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A7D0_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80108480_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_801085A4_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_801088B0_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80108998_game_guys_roulette);

void func_801089EC_game_guys_roulette(omObjData *object) {
    if (D_800D530C_main == 1) {
        object->func = func_801088B0_game_guys_roulette;
    }
}

void func_80108A14_game_guys_roulette(u8 *espriteSlot, s32 spriteIndex, u16 visibility) {
    *espriteSlot = espEntry(func_8000B838_main(spriteIndex), 0, 1);
    espAttrSet(*espriteSlot, visibility);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80108A6C_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80108A9C_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80108B44_game_guys_roulette);
