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

extern u8 D_800D2008_main;
extern MarioPuzzlePartySpriteBlock *D_801168B0_marios_puzzle_party;
extern s16 D_801168B4_marios_puzzle_party;     // number of sprite blocks in use
extern s16 D_801168B6_marios_puzzle_party;     // model drawing the sprite display list
extern Gfx *D_801168B8_marios_puzzle_party[3]; // one display list buffer per frame buffer
extern omObjData *D_801168C4_marios_puzzle_party;
extern s32 D_801168C8_marios_puzzle_party[4]; // per-board y offset

void func_8010F810_marios_puzzle_party(omObjData *object);

void func_8010F570_marios_puzzle_party(s16 blockCount) {
    s16 i;

    D_801168B0_marios_puzzle_party = HuMemAllocTag(blockCount * sizeof(MarioPuzzlePartySpriteBlock), 0x7918);
    D_801168B4_marios_puzzle_party = 0;
    for (i = 0; i < 3; i++) {
        D_801168B8_marios_puzzle_party[i] = HuMemAllocTag(0x3E80, 0x7918);
        gSPEndDisplayList(D_801168B8_marios_puzzle_party[i]);
    }
    D_801168C4_marios_puzzle_party = omAddObj(0x7D0, 0, 0, -1, func_8010F810_marios_puzzle_party);
    omSetStatBit(D_801168C4_marios_puzzle_party, 0xA0);
    D_801168B6_marios_puzzle_party = func_8001A894_main(0, D_801168B8_marios_puzzle_party[D_800D2008_main], 2);
}

void func_8010F678_marios_puzzle_party(s32 spriteData, s16 count) {
    MarioPuzzlePartySprite *sprite;
    s16 groupId;
    s16 groupHandle;
    s16 i;

    D_801168B0_marios_puzzle_party[D_801168B4_marios_puzzle_party].sprites = sprite =
        HuMemAllocTag(count * sizeof(MarioPuzzlePartySprite), 0x7918);
    groupId = func_8000B838_main(spriteData);
    D_801168B0_marios_puzzle_party[D_801168B4_marios_puzzle_party].groupId = groupId;
    groupHandle = HuSprGrpCreate(1, 0);
    D_801168B0_marios_puzzle_party[D_801168B4_marios_puzzle_party].groupHandle = groupHandle;
    HuSprGrpMemberSet(groupHandle, 0, groupId, 0);
    HuSprAttrReset(groupHandle, 0, 0xFFFF);
    HuSprAttrSet(groupHandle, 0, 0x8000);
    D_801168B0_marios_puzzle_party[D_801168B4_marios_puzzle_party].count = count;
    for (i = 0; i < count; i++, sprite++) {
        sprite->flags = 0;
    }
    D_801168B4_marios_puzzle_party++;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1FD760", func_8010F810_marios_puzzle_party);

s16 func_8010FEDC_marios_puzzle_party(s16 group, f32 x, f32 y) {
    MarioPuzzlePartySpriteBlock *block = &D_801168B0_marios_puzzle_party[group];
    MarioPuzzlePartySprite *sprite = block->sprites;
    s16 i;

    for (i = 0; i < block->count; i++, sprite++) {
        if (sprite->flags == 0) {
            sprite->flags = 1;
            sprite->x = x;
            sprite->y = y;
            sprite->height = 1.0f;
            sprite->width = 1.0f;
            break;
        }
    }
    return i + (group << 10);
}

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

void func_80110040_marios_puzzle_party(void) {
    Hu3DModelKill(D_801168B6_marios_puzzle_party);
    omDelObj(D_801168C4_marios_puzzle_party);
}

void func_8011006C_marios_puzzle_party(s32 board, s32 offset) {
    D_801168C8_marios_puzzle_party[board] = offset;
}
