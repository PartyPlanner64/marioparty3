#include "common.h"

typedef struct GameGuysMagicBoxesBanner { // 0x18 bytes
    /* 0x00 */ HuSprite *sprite;
    /* 0x04 */ void *unk_04[3];
    /* 0x10 */ s16 group;
    /* 0x12 */ s16 timer;
    /* 0x14 */ s16 unk_14;
} GameGuysMagicBoxesBanner;

extern GameGuysMagicBoxesBanner D_8010CAE0_game_guys_magic_boxes;
extern GameGuysMagicBoxesBanner D_8010CAF8_game_guys_magic_boxes;

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/30DC30", func_8010A8C0_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/30DC30", func_8010AB8C_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/30DC30", func_8010AC18_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/30DC30", func_8010B700_game_guys_magic_boxes);

void func_8010B8B4_game_guys_magic_boxes(void) {
    HuSprDispOff(D_8010CAF8_game_guys_magic_boxes.group, 0);
    HuSprDispOff(D_8010CAE0_game_guys_magic_boxes.group, 0);
    D_8010CAF8_game_guys_magic_boxes.sprite->unk_84->unk00->unk00 = D_8010CAF8_game_guys_magic_boxes.unk_04[0];
    D_8010CAE0_game_guys_magic_boxes.sprite->unk_84->unk00->unk00 = D_8010CAE0_game_guys_magic_boxes.unk_04[0];
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/30DC30", func_8010B938_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/30DC30", func_8010BA0C_game_guys_magic_boxes);

void func_8010BB70_game_guys_magic_boxes(void) {
    s32 i, j;
    u8 *ptr;

    for (i = 0; i < 3; i++) {
        ptr = D_8010CAF8_game_guys_magic_boxes.unk_04[i];
        for (j = 0; j <= 0x95FF; j++) {
            *ptr++ = 0;
        }
    }
    for (i = 0; i < 3; i++) {
        ptr = D_8010CAE0_game_guys_magic_boxes.unk_04[i];
        for (j = 0; j <= 0x95FF; j++) {
            *ptr++ = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/30DC30", func_8010BC00_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/30DC30", func_8010BD5C_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/30DC30", func_8010BD9C_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/30DC30", func_8010BF94_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/30DC30", D_8010C5A0_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/30DC30", D_8010C5A8_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/30DC30", D_8010C5B0_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/30DC30", D_8010C5C0_game_guys_magic_boxes);
