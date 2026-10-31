#include "common.h"

typedef struct GameGuysSweetSurpriseBanner { // 0x18 bytes
    /* 0x00 */ HuSprite *sprite;
    /* 0x04 */ void *unk_04[3];
    /* 0x10 */ s16 group;
    /* 0x12 */ s16 timer;
    /* 0x14 */ s16 unk_14;
} GameGuysSweetSurpriseBanner;

extern GameGuysSweetSurpriseBanner D_8010D0D0_game_guys_sweet_surprise;
extern GameGuysSweetSurpriseBanner D_8010D0E8_game_guys_sweet_surprise;

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/3151F0", func_8010B250_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/3151F0", func_8010B51C_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/3151F0", func_8010B5A8_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/3151F0", func_8010C090_game_guys_sweet_surprise);

void func_8010C244_game_guys_sweet_surprise(void) {
    HuSprDispOff(D_8010D0E8_game_guys_sweet_surprise.group, 0);
    HuSprDispOff(D_8010D0D0_game_guys_sweet_surprise.group, 0);
    D_8010D0E8_game_guys_sweet_surprise.sprite->unk_84->unk00->unk00 =
        D_8010D0E8_game_guys_sweet_surprise.unk_04[0];
    D_8010D0D0_game_guys_sweet_surprise.sprite->unk_84->unk00->unk00 =
        D_8010D0D0_game_guys_sweet_surprise.unk_04[0];
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/3151F0", func_8010C2C8_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/3151F0", func_8010C39C_game_guys_sweet_surprise);

void func_8010C500_game_guys_sweet_surprise(void) {
    s32 i, j;
    u8 *ptr;

    for (i = 0; i < 3; i++) {
        ptr = D_8010D0E8_game_guys_sweet_surprise.unk_04[i];
        for (j = 0; j <= 0x95FF; j++) {
            *ptr++ = 0;
        }
    }
    for (i = 0; i < 3; i++) {
        ptr = D_8010D0D0_game_guys_sweet_surprise.unk_04[i];
        for (j = 0; j <= 0x95FF; j++) {
            *ptr++ = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/3151F0", func_8010C590_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/3151F0", func_8010C6EC_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/3151F0", func_8010C72C_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/3151F0", func_8010C924_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/3151F0", D_8010CE40_game_guys_sweet_surprise);
