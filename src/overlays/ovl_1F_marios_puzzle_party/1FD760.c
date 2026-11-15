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
extern u8 D_800D6A90_main;

Gfx D_80110230_marios_puzzle_party[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_TEX_EDGE, G_RM_NOOP2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsDPSetPrimColor(0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

MarioPuzzlePartySpriteBlock *D_801168B0_marios_puzzle_party BSS;
s16 D_801168B4_marios_puzzle_party BSS;     // number of sprite blocks in use
s16 D_801168B6_marios_puzzle_party BSS;     // model drawing the sprite display list
Gfx *D_801168B8_marios_puzzle_party[3] BSS; // one display list buffer per frame buffer
omObjData *D_801168C4_marios_puzzle_party BSS;
s32 D_801168C8_marios_puzzle_party[4] BSS; // per-board y offset

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

void func_8010F810_marios_puzzle_party(omObjData *object) {
    Gfx *gfx;
    MarioPuzzlePartySpriteBlock *block;
    MarioPuzzlePartySprite *sprite;
    HuSprAnimData *anim;
    void *image;
    s16 width;
    s16 height;
    s16 yOffset;
    s16 i;
    s16 j;

    gfx = (Gfx *)(Hu3DData[D_801168B6_marios_puzzle_party].hmf->unk3C =
                      (HmfModelData_Unk64_Unk3C_Struct *)D_801168B8_marios_puzzle_party[D_800D2008_main]);
    if (D_801168B4_marios_puzzle_party == 0) {
        gSPEndDisplayList(gfx++);
        return;
    }
    block = D_801168B0_marios_puzzle_party;
    gSPDisplayList(gfx++, osVirtualToPhysical(D_80110230_marios_puzzle_party));
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    if (omPauseChk() + D_800D6A90_main == 0) {
        for (i = 0; i < D_801168B4_marios_puzzle_party; i++, block++) {
            sprite = block->sprites;
            anim = HuSprGet(block->groupHandle, 0)->data;
            image = anim->pat->data;
            width = anim->sizeX;
            height = anim->sizeY;
            gDPLoadTextureTile(gfx++, image, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, 0, 0, 0, width, height, 0,
                               G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
            for (j = 0; j < block->count; j++, sprite++) {
                if (sprite->flags & 1) {
                    yOffset = 0;
                    if (i < 28) {
                        yOffset = D_801168C8_marios_puzzle_party[i / 7];
                    }
                    gSPScisTextureRectangle(gfx++, sprite->x * 4.0f,
                                            (yOffset + sprite->y - height * sprite->height) * 4.0f,
                                            (width * sprite->width + sprite->x) * 4.0f, (yOffset + sprite->y) * 4.0f,
                                            G_TX_RENDERTILE, 0, 0, 1024.0f / sprite->width, 1024.0f / sprite->height);
                }
            }
        }
    }
    gSPEndDisplayList(gfx++);
}

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
