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

extern u8 Hu3DBufNo;
extern u8 omAllPauseF;

Gfx m231_sprBatchGfx[] = {
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

MarioPuzzlePartySpriteBlock *m231_sprBatchTbl BSS;
s16 m231_sprBatchNum BSS;     // number of sprite blocks in use
s16 m231_sprBatchMdl BSS;     // model drawing the sprite display list
Gfx *m231_sprBatchGfxBuf[3] BSS; // one display list buffer per frame buffer
omObjData *m231_sprBatchObj BSS;
s32 m231_sprBatchOfsYTbl[4] BSS; // per-board y offset

void m231_SprBatchObjMain(omObjData *object);

void m231_SprBatchInit(s16 blockCount) {
    s16 i;

    m231_sprBatchTbl = HuMemAllocTag(blockCount * sizeof(MarioPuzzlePartySpriteBlock), 0x7918);
    m231_sprBatchNum = 0;
    for (i = 0; i < 3; i++) {
        m231_sprBatchGfxBuf[i] = HuMemAllocTag(0x3E80, 0x7918);
        gSPEndDisplayList(m231_sprBatchGfxBuf[i]);
    }
    m231_sprBatchObj = omAddObj(0x7D0, 0, 0, -1, m231_SprBatchObjMain);
    omSetStatBit(m231_sprBatchObj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    m231_sprBatchMdl = Hu3DModelDLCreate(0, m231_sprBatchGfxBuf[Hu3DBufNo], 2);
}

void m231_SprBatchAdd(s32 spriteData, s16 count) {
    MarioPuzzlePartySprite *sprite;
    s16 groupId;
    s16 groupHandle;
    s16 i;

    m231_sprBatchTbl[m231_sprBatchNum].sprites = sprite =
        HuMemAllocTag(count * sizeof(MarioPuzzlePartySprite), 0x7918);
    groupId = HuSprAnimDataRead(spriteData);
    m231_sprBatchTbl[m231_sprBatchNum].groupId = groupId;
    groupHandle = HuSprGrpCreate(1, 0);
    m231_sprBatchTbl[m231_sprBatchNum].groupHandle = groupHandle;
    HuSprGrpMemberSet(groupHandle, 0, groupId, 0);
    HuSprAttrReset(groupHandle, 0, 0xFFFF);
    HuSprDispOff(groupHandle, 0);
    m231_sprBatchTbl[m231_sprBatchNum].count = count;
    for (i = 0; i < count; i++, sprite++) {
        sprite->flags = 0;
    }
    m231_sprBatchNum++;
}

void m231_SprBatchObjMain(omObjData *object) {
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

    gfx = (Gfx *)(Hu3DData[m231_sprBatchMdl].hmf->unk3C =
                      (HmfModelData_Unk64_Unk3C_Struct *)m231_sprBatchGfxBuf[Hu3DBufNo]);
    if (m231_sprBatchNum == 0) {
        gSPEndDisplayList(gfx++);
        return;
    }
    block = m231_sprBatchTbl;
    gSPDisplayList(gfx++, osVirtualToPhysical(m231_sprBatchGfx));
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    if (omPauseChk() + omAllPauseF == 0) {
        for (i = 0; i < m231_sprBatchNum; i++, block++) {
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
                        yOffset = m231_sprBatchOfsYTbl[i / 7];
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

s16 m231_SprBatchEntryAdd(s16 group, f32 x, f32 y) {
    MarioPuzzlePartySpriteBlock *block = &m231_sprBatchTbl[group];
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

void m231_SprBatchPosSet(s16 index, f32 x, f32 y) {
    MarioPuzzlePartySprite *sprites = m231_sprBatchTbl[index >> 10].sprites;
    MarioPuzzlePartySprite *sprite = sprites + (index & 0x3FF);
    sprite->x = x;
    sprite->y = y;
}

void m231_SprBatchScaleSet(s16 index, f32 width, f32 height) {
    MarioPuzzlePartySprite *sprites = m231_sprBatchTbl[index >> 10].sprites;
    MarioPuzzlePartySprite *sprite = sprites + (index & 0x3FF);
    sprite->width = width;
    sprite->height = height;
}

void m231_SprBatchEntryKill(s16 index) {
    MarioPuzzlePartySprite *sprites = m231_sprBatchTbl[index >> 10].sprites;
    MarioPuzzlePartySprite *sprite = sprites + (index & 0x3FF);
    sprite->flags = 0;
}

void m231_SprBatchKill(void) {
    Hu3DModelKill(m231_sprBatchMdl);
    omDelObj(m231_sprBatchObj);
}

void m231_SprBatchOfsYSet(s32 board, s32 offset) {
    m231_sprBatchOfsYTbl[board] = offset;
}
