#include "common.h"

// 0x14 byte sprite draw entry, allocated in blocks of 0x3E80 bytes
typedef struct MarioPuzzlePartySprite {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 width;
    /* 0x0C */ f32 height;
    /* 0x10 */ s16 flags;
} MarioPuzzlePartySprite;

// 0x0C byte descriptor for one block of MarioPuzzlePartySprite
typedef struct MarioPuzzlePartySpriteBlock {
    /* 0x00 */ MarioPuzzlePartySprite *sprites;
    /* 0x04 */ s16 groupId;
    /* 0x06 */ s16 groupHandle;
    /* 0x08 */ s16 count;
} MarioPuzzlePartySpriteBlock;

extern MarioPuzzlePartySpriteBlock *D_801168B0_marios_puzzle_party;

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1FD760", func_8010F570_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1FD760", func_8010F678_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1FD760", func_8010F810_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1FD760", func_8010FEDC_marios_puzzle_party);

void func_8010FF78_marios_puzzle_party(s16 index, f32 x, f32 y) {
    MarioPuzzlePartySprite *sprites = D_801168B0_marios_puzzle_party[index >> 10].sprites;
    MarioPuzzlePartySprite *sprite = sprites + (index & 0x3FF);
    sprite->x = x;
    sprite->y = y;
}

void func_8010FFBC_marios_puzzle_party(s16 index, f32 width, f32 height) {
    MarioPuzzlePartySprite *sprites = D_801168B0_marios_puzzle_party[index >> 10].sprites;
    MarioPuzzlePartySprite *sprite = sprites + (index & 0x3FF);
    sprite->width = width;
    sprite->height = height;
}

void func_80110000_marios_puzzle_party(s16 index) {
    MarioPuzzlePartySprite *sprites = D_801168B0_marios_puzzle_party[index >> 10].sprites;
    MarioPuzzlePartySprite *sprite = sprites + (index & 0x3FF);
    sprite->flags = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1FD760", func_80110040_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1FD760", func_8011006C_marios_puzzle_party);
