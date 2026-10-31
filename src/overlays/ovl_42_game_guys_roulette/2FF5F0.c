#include "common.h"

typedef struct GameGuysRouletteBanner { // 0x18 bytes
    /* 0x00 */ HuSprite *sprite;
    /* 0x04 */ void *unk_04[3];
    /* 0x10 */ s16 group;
    /* 0x12 */ s16 timer;
    /* 0x14 */ s16 unk_14;
} GameGuysRouletteBanner;

extern GameGuysRouletteBanner D_8010AC20_game_guys_roulette;
extern GameGuysRouletteBanner D_8010AC38_game_guys_roulette;

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_80108D20_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_80108FEC_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_80109078_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_80109B60_game_guys_roulette);

void func_80109D14_game_guys_roulette(void) {
    HuSprDispOff(D_8010AC38_game_guys_roulette.group, 0);
    HuSprDispOff(D_8010AC20_game_guys_roulette.group, 0);
    D_8010AC38_game_guys_roulette.sprite->unk_84->unk00->unk00 = D_8010AC38_game_guys_roulette.unk_04[0];
    D_8010AC20_game_guys_roulette.sprite->unk_84->unk00->unk00 = D_8010AC20_game_guys_roulette.unk_04[0];
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_80109D98_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_80109E6C_game_guys_roulette);

void func_80109FD0_game_guys_roulette(void) {
    s32 i, j;
    u8 *ptr;

    for (i = 0; i < 3; i++) {
        ptr = D_8010AC38_game_guys_roulette.unk_04[i];
        for (j = 0; j <= 0x95FF; j++) {
            *ptr++ = 0;
        }
    }
    for (i = 0; i < 3; i++) {
        ptr = D_8010AC20_game_guys_roulette.unk_04[i];
        for (j = 0; j <= 0x95FF; j++) {
            *ptr++ = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_8010A060_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_8010A1BC_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_8010A1FC_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_8010A3F4_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", D_8010A7E8_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", D_8010A7F0_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", D_8010A800_game_guys_roulette);
