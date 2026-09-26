#include "common.h"

typedef struct GameGuysLucky7Banner { // 0x18 bytes
    /* 0x00 */ HuSprite *sprite;
    /* 0x04 */ void *unk_04[3];
    /* 0x10 */ s16 group;
    /* 0x12 */ s16 timer;
    /* 0x14 */ s16 unk_14;
} GameGuysLucky7Banner;

extern GameGuysLucky7Banner D_8010D8D0_game_guys_lucky_7;
extern GameGuysLucky7Banner D_8010D8E8_game_guys_lucky_7;

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/306F70", func_8010B830_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/306F70", func_8010BAFC_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/306F70", func_8010BB88_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/306F70", func_8010C670_game_guys_lucky_7);

void func_8010C824_game_guys_lucky_7(void) {
    HuSprAttrSet(D_8010D8E8_game_guys_lucky_7.group, 0, 0x8000);
    HuSprAttrSet(D_8010D8D0_game_guys_lucky_7.group, 0, 0x8000);
    D_8010D8E8_game_guys_lucky_7.sprite->unk_84->unk00->unk00 =
        D_8010D8E8_game_guys_lucky_7.unk_04[0];
    D_8010D8D0_game_guys_lucky_7.sprite->unk_84->unk00->unk00 =
        D_8010D8D0_game_guys_lucky_7.unk_04[0];
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/306F70", func_8010C8A8_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/306F70", func_8010C97C_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/306F70", func_8010CAE0_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/306F70", func_8010CB70_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/306F70", func_8010CCCC_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/306F70", func_8010CD0C_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/306F70", func_8010CF04_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/306F70", D_8010D5C0_game_guys_lucky_7);
