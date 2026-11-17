#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/sprite.h"
#include "game/texload.h"
#include "game/hmfspr.h"
#include "game/hmfmath.h"
#include "game/mallocblock.h"

#define SPRPUT_CC_PRIM_DECALA 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0
#define SPRPUT_CC_PRIM_MODULATEA 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0
#define SPRPUT_CC_BLEND_DECALA 1, PRIMITIVE, TEXEL0, PRIMITIVE, 0, 0, 0, TEXEL0
#define SPRPUT_CC_BLEND_MODULATEA 1, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0
#define SPRPUT_CC_TEX_MODULATEA 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0

static f32 sprCullCorner[4][2];
static s32 sprTexFmt;
static s32 sprTexSiz;
static s32 sprTlutMode;
static s32 sprTexScale;
static s32 sprStripNum;
static s32 sprStripHeight;
static s32 sprStripRest;
static s32 sprStripCnt;
static s32 sprBilerpF;

static s32 sprTmemLineMax = 256;
static s32 sprOtherModeShiftTbl[] = { G_MDSFT_TEXTFILT, G_MDSFT_RGBDITHER, G_MDSFT_CYCLETYPE, G_MDSFT_ALPHACOMPARE };
static s32 sprAlphaCmpTbl[] = { G_AC_THRESHOLD, G_AC_NONE, G_AC_DITHER };
static s32 sprSizShiftTbl[] = { 4, 3, 2, 1 };
static s16 sprStripMaxTbl[] = {
    0, 512, 256, 170, 128, 102, 85, 73, 64, 56, 51, 20, 42, 26, 14, 19,
    32, 13, 28, 26, 8, 9, 4, 4, 5, 20, 13, 18, 3, 6, 3, 2,
    16, 2, 2, 3, 14, 2, 13, 2, 1, 12, 4, 2, 2, 2, 2, 2,
    2, 4, 10, 0, 1, 2, 9, 0, 1, 8, 0, 2, 0, 1, 0, 1,
    8, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 0, 6, 0, 0, 4,
    0, 0, 6, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 4, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0,
    0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0,
};
static s16 sprStripExactTbl[] = {
    0, 512, 256, 170, 128, 102, 85, 73, 64, 56, 51, 46, 42, 39, 36, 34,
    32, 30, 28, 26, 25, 24, 23, 22, 21, 20, 19, 19, 18, 18, 17, 17,
    16, 16, 15, 15, 14, 14, 13, 13, 13, 12, 12, 12, 11, 11, 11, 10,
    10, 10, 10, 10, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8,
    8, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
};

extern u8 Hu3DBufNo;
extern Gfx *HuSprTileBuf;
extern Vtx *HuSprVtxPos;


s32 HuSprCullCheck(HuSprite *sprite) {
    HuSprAnimPat *cel;
    f32 sin;
    f32 cos;
    f32 left;
    f32 top;
    f32 right;
    f32 bottom;

    cel = &sprite->data->pat[sprite->patNo];
    sin = sindf(sprite->unk_20);
    cos = cosdf(sprite->unk_20);
    if (!(sprite->dispAttr & HUSPR_ATTR_RECT)) {
        left = -(u16)cel->centerX * sprite->unk_18;
        top = -(u16)cel->centerY * sprite->unk_1C;
        right = (cel->sizeX - (u16)cel->centerX) * sprite->unk_18;
        bottom = (cel->sizeY - (u16)cel->centerY) * sprite->unk_1C;
    } else {
        left = (s16)sprite->unk_3C;
        top = (s16)sprite->unk_3E;
        right = (s16)sprite->unk_40;
        bottom = (s16)sprite->unk_42;
    }
    sprCullCorner[0][0] = cos * left + sin * top + sprite->unk_04;
    sprCullCorner[0][1] = -sin * left + cos * top + sprite->unk_08;
    sprCullCorner[1][0] = cos * right + sin * top + sprite->unk_04;
    sprCullCorner[1][1] = -sin * right + cos * top + sprite->unk_08;
    sprCullCorner[2][0] = cos * right + sin * bottom + sprite->unk_04;
    sprCullCorner[2][1] = -sin * right + cos * bottom + sprite->unk_08;
    sprCullCorner[3][0] = cos * left + sin * bottom + sprite->unk_04;
    sprCullCorner[3][1] = -sin * left + cos * bottom + sprite->unk_08;
    return HuSprQuadClip(sprCullCorner);
}

// Test the transformed sprite quad against the 320 by 240 viewport.
s32 HuSprQuadClip(f32 vertices[][2]) {
    s32 i;
    s32 next;
    f32 dx;
    f32 dy;
    f32 t;
    f32 intersection;
    f32 x;
    f32 y;

    for (i = 0; i < 4; i++) {
        if (vertices[i][0] >= 0.0f && vertices[i][0] < 320.0f &&
            vertices[i][1] >= 0.0f && vertices[i][1] < 240.0f) {
            return 1;
        }
    }

    for (i = 0; i < 4; i++) {
        next = i + 1;
        if (next >= 4) {
            next = 0;
        }
        dx = vertices[next][0] - vertices[i][0];
        dy = vertices[next][1] - vertices[i][1];
        if (dy != 0.0f) {
            t = (0.0f - vertices[i][1]) / dy;
            if ((t >= 0.0f) & (t < 1.0f)) {
                intersection = vertices[i][0] + t * dx;
                if ((intersection >= 0.0f) & (intersection < 320.0f)) {
                    return 1;
                }
            }
            t = (240.0f - vertices[i][1]) / dy;
            if ((t >= 0.0f) & (t < 1.0f)) {
                intersection = vertices[i][0] + t * dx;
                if ((intersection >= 0.0f) & (intersection < 320.0f)) {
                    return 1;
                }
            }
        }
        if (dx != 0.0f) {
            t = (0.0f - vertices[i][0]) / dx;
            if ((t >= 0.0f) & (t < 1.0f)) {
                intersection = vertices[i][1] + t * dy;
                if ((intersection >= 0.0f) & (intersection < 240.0f)) {
                    return 1;
                }
            }
            t = (320.0f - vertices[i][0]) / dx;
            if ((t >= 0.0f) & (t < 1.0f)) {
                intersection = vertices[i][1] + t * dy;
                if ((intersection >= 0.0f) & (intersection < 240.0f)) {
                    return 1;
                }
            }
        }
    }

    for (i = 0; i < 4; i++) {
        next = i + 1;
        if (next >= 4) {
            next = 0;
        }
        dx = vertices[next][0] - vertices[i][0];
        dy = vertices[next][1] - vertices[i][1];
        x = 160.0f - vertices[next][0];
        y = 120.0f - vertices[next][1];
        if (dx * y - dy * x < 0.0f) {
            return 0;
        }
    }
    return 1;
}

void HuSprDisp(Gfx **gfx, HuSprite *sprite, s32 arg2) {
    Gfx *gdl;
    HuSprAnimPat *cel;
    s32 alignedWidth;
    s32 intensity;
    s32 renderMode;
    s32 size;
    Vtx *vertices;
    f32 scaleX;
    f32 scaleY;
    f32 originX;
    f32 originY;
    HuMtx4F transform;
    Gfx *cached;

    gdl = *gfx;
    scaleX = sprite->unk_18;
    scaleY = sprite->unk_1C;
    if (sprite->data == NULL) {
        return;
    }
    cel = &sprite->data->pat[sprite->patNo];
    if ((scaleX <= 0.0f) | (scaleY <= 0.0f)) {
        return;
    }
    if (!HuSprCullCheck(sprite)) {
        return;
    }
    gDPSetScissor(gdl++, G_SC_NON_INTERLACE, sprite->scissorX, sprite->scissorY, sprite->scissorX2, sprite->scissorY2);
    switch (sprite->data->pixelBits) {
        case 4:
            sprTexSiz = G_IM_SIZ_4b;
            if (sprite->data->palNum == 1) {
                sprTexFmt = G_IM_FMT_IA;
                gDPSetTextureLUT(gdl++, G_TT_NONE);
            } else {
                sprTexFmt = G_IM_FMT_CI;
                if (sprite->unk_98.unk00 != NULL) {
                    gDPLoadTLUT_pal16(gdl++, 0, sprite->unk_98.unk6C);
                } else {
                    gDPLoadTLUT_pal16(gdl++, 0, sprite->data->pal);
                }
                gDPSetTextureLUT(gdl++, G_TT_RGBA16);
                sprTmemLineMax = 128;
            }
            sprTlutMode = 0;
            break;
        case 8:
            sprTexSiz = G_IM_SIZ_8b;
            if (sprite->data->palNum == 1) {
                sprTexFmt = G_IM_FMT_IA;
                gDPSetTextureLUT(gdl++, G_TT_NONE);
                sprTlutMode = 2;
            } else {
                sprTexFmt = G_IM_FMT_CI;
                if (sprite->unk_98.unk00 != NULL) {
                    gDPLoadTLUT_pal256(gdl++, sprite->unk_98.unk6C);
                } else {
                    gDPLoadTLUT_pal256(gdl++, sprite->data->pal);
                }
                gDPSetTextureLUT(gdl++, G_TT_RGBA16);
                sprTmemLineMax = 128;
                sprTlutMode = 2;
            }
            break;
        case 16:
            sprTexSiz = G_IM_SIZ_16b;
            if (sprite->data->palNum == 1) {
                sprTexFmt = G_IM_FMT_IA;
            } else {
                sprTexFmt = G_IM_FMT_RGBA;
            }
            gDPSetTextureLUT(gdl++, G_TT_NONE);
            sprTmemLineMax = 256;
            sprTlutMode = 2;
            break;
        case 32:
            sprTexSiz = G_IM_SIZ_32b;
            sprTexFmt = G_IM_FMT_RGBA;
            gDPSetTextureLUT(gdl++, G_TT_NONE);
            sprTmemLineMax = 256;
            sprTlutMode = 2;
            break;
        case 0x8004:
            sprTexSiz = G_IM_SIZ_4b;
            sprTexFmt = G_IM_FMT_I;
            gDPSetTextureLUT(gdl++, G_TT_NONE);
            sprTmemLineMax = 256;
            sprTlutMode = 0;
            break;
        case 0x8008:
            sprTexSiz = G_IM_SIZ_8b;
            sprTexFmt = G_IM_FMT_I;
            gDPSetTextureLUT(gdl++, G_TT_NONE);
            sprTmemLineMax = 256;
            sprTlutMode = 2;
            break;
    }
    // Round the row width up to the texture load alignment before sizing strips.
    alignedWidth = (((cel->sizeX << sprTexSiz) >> 4) << 4) >> sprTexSiz;
    if (alignedWidth < cel->sizeX) {
        alignedWidth += 16 >> sprTexSiz;
    }
    switch (sprTexFmt) {
        case G_IM_FMT_CI:
            if ((4096 >> sprTexSiz) >= cel->sizeY * alignedWidth) {
                sprStripHeight = cel->sizeY;
            } else {
                sprStripHeight = (4096 >> sprTexSiz) / alignedWidth;
            }
            break;
        case G_IM_FMT_I:
            if (4096 >= cel->sizeY * alignedWidth) {
                sprStripHeight = cel->sizeY;
            } else {
                sprStripHeight = 4096 / alignedWidth;
            }
            break;
        default:
            if ((8192 >> sprTexSiz) >= cel->sizeY * alignedWidth) {
                sprStripHeight = cel->sizeY;
            } else {
                sprStripHeight = (8192 >> sprTexSiz) / alignedWidth;
            }
            break;
    }
    sprStripNum = cel->sizeY / sprStripHeight;
    sprStripRest = cel->sizeY - sprStripNum * sprStripHeight;
    // Aligned strips can use the block loader when its DXT rounding is exact.
    if (cel->sizeX % (16 >> sprTexSiz) == 0) {
        if (((cel->sizeX * sprStripHeight) << sprTexSiz) <= 4096) {
            if (sprStripMaxTbl[cel->sizeX >> sprSizShiftTbl[sprTexSiz]] >= sprStripHeight ||
                sprStripHeight == sprStripExactTbl[cel->sizeX >> sprSizShiftTbl[sprTexSiz]]) {
                sprTlutMode++;
            }
        }
    }
    gDPPipeSync(gdl++);
    gSPSetOtherMode(gdl++, G_SETOTHERMODE_H, sprOtherModeShiftTbl[0], 2,
                    (((u32)sprite->dispAttr >> HUSPR_ATTR_FILTER_SHIFT) & 3) << sprOtherModeShiftTbl[0]);
    gSPSetOtherMode(gdl++, G_SETOTHERMODE_H, sprOtherModeShiftTbl[1], 2,
                    ((((u32)sprite->dispAttr >> HUSPR_ATTR_DITHER_SHIFT) ^ 3) & 3) << sprOtherModeShiftTbl[1]);
    gSPSetOtherMode(gdl++, G_SETOTHERMODE_H, sprOtherModeShiftTbl[2], 2,
                    (((u32)sprite->dispAttr >> HUSPR_ATTR_CYCLE_SHIFT) & 3) << sprOtherModeShiftTbl[2]);
    gSPSetOtherMode(gdl++, G_SETOTHERMODE_L, sprOtherModeShiftTbl[3], 2,
                    sprAlphaCmpTbl[((u32)sprite->dispAttr >> HUSPR_ATTR_ALPHACMP_SHIFT) & 3]);
    if (((u32)sprite->dispAttr >> HUSPR_ATTR_CYCLE_SHIFT) & 2) {
        gDPSetRenderMode(gdl++, G_RM_NOOP, G_RM_NOOP2);
        gDPSetCombineMode(gdl++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        sprTexScale = 4;
    } else {
        intensity = sprite->data->pixelBits >> 15;
        renderMode = (sprite->dispAttr & HUSPR_ATTR_ZBUF) ? Z_CMP | Z_UPD : 0;
        switch (((u32)sprite->dispAttr >> HUSPR_ATTR_AA_SHIFT) & 3) {
            case 0:
                if (sprite->dispAttr & HUSPR_ATTR_XLU) {
                    if ((sprite->tpLvl == 256) & (intensity == 0)) {
                        renderMode |= G_RM_TEX_EDGE;
                    } else {
                        renderMode |= G_RM_XLU_SURF;
                    }
                } else {
                    renderMode |= G_RM_OPA_SURF;
                }
                break;
            case 1:
                if (sprite->dispAttr & HUSPR_ATTR_XLU) {
                    if ((sprite->tpLvl == 256) & (intensity == 0)) {
                        renderMode |= G_RM_AA_TEX_EDGE;
                    } else {
                        renderMode |= G_RM_AA_XLU_SURF;
                    }
                } else {
                    renderMode |= G_RM_RA_OPA_SURF;
                }
                break;
            case 2:
                if (sprite->dispAttr & HUSPR_ATTR_XLU) {
                    if ((sprite->tpLvl == 256) & (intensity == 0)) {
                        renderMode |= G_RM_AA_TEX_EDGE;
                    } else {
                        renderMode |= G_RM_AA_XLU_SURF;
                    }
                } else {
                    renderMode |= G_RM_AA_OPA_SURF;
                }
                break;
        }
        gDPSetRenderMode(gdl++, renderMode, 0);
        if (intensity) {
            if (sprite->tpLvl == 256) {
                gDPSetCombineMode(gdl++, SPRPUT_CC_PRIM_DECALA, SPRPUT_CC_PRIM_DECALA);
            } else {
                gDPSetCombineMode(gdl++, SPRPUT_CC_PRIM_MODULATEA, SPRPUT_CC_PRIM_MODULATEA);
            }
        } else {
            if (sprite->tpLvl == 256) {
                if (sprite->dispAttr & HUSPR_ATTR_ADDCOL) {
                    gDPSetCombineMode(gdl++, SPRPUT_CC_BLEND_DECALA, SPRPUT_CC_BLEND_DECALA);
                } else {
                    gDPSetCombineMode(gdl++, G_CC_DECALRGBA, G_CC_DECALRGBA);
                }
            } else {
                if (sprite->dispAttr & HUSPR_ATTR_ADDCOL) {
                    gDPSetCombineMode(gdl++, SPRPUT_CC_BLEND_MODULATEA, SPRPUT_CC_BLEND_MODULATEA);
                } else {
                    gDPSetCombineMode(gdl++, SPRPUT_CC_TEX_MODULATEA, SPRPUT_CC_TEX_MODULATEA);
                }
            }
        }
        gDPSetPrimColor(gdl++, 0, 0, sprite->color[0], sprite->color[1], sprite->color[2], (u8)sprite->tpLvl);
        sprTexScale = 1;
    }
    sprBilerpF = ((u32)sprite->dispAttr >> 30) & 1;
    gSPSegment(gdl++, 2, osVirtualToPhysical(cel->data));
    if (sprBilerpF) {
        if (sprite->dispAttr & HUSPR_ATTR_RECT) {
            originX = ((s16)sprite->unk_3C - (s16)sprite->unk_40) * (u16)cel->centerX / cel->sizeX;
            originY = ((s16)sprite->unk_42 - (s16)sprite->unk_3E) * (u16)cel->centerY / cel->sizeY;
            sprite->unk_04 = (s16)sprite->unk_3C + ((s16)sprite->unk_40 - (s16)sprite->unk_3C) * (u16)cel->centerX / cel->sizeX;
            sprite->unk_08 = (s16)sprite->unk_3E + ((s16)sprite->unk_42 - (s16)sprite->unk_3E) * (u16)cel->centerY / cel->sizeY;
        } else {
            originX = -(u16)cel->centerX;
            originY = (u16)cel->centerY;
        }
        transform[0][2] = transform[0][3] = transform[1][2] = transform[1][3] = transform[2][0] =
            transform[2][1] = transform[2][3] = transform[3][2] = 0.0f;
        transform[2][2] = transform[3][3] = 1.0f;
        HuMtx2DRotTrans(transform, sprite->unk_04 - 160.0f, 120.0f - sprite->unk_08, sprite->unk_20);
        mtxScaleCat(transform, scaleX, scaleY, 1.0f);
        mtxTransCat(transform, originX, originY, 0.0f);
        HuMtxF2L(transform, &sprite->unk_140[Hu3DBufNo]);
        gSPMatrix(gdl++, osVirtualToPhysical(&sprite->unk_140[Hu3DBufNo]), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    }
    if (sprite->dispAttr & HUSPR_ATTR_DLCACHE) {
        if (sprite->dispAttr & HUSPR_ATTR_DLDIRTY) {
            if (sprBilerpF) {
                cached = HuSprDispTile(HuSprTileBuf, sprite, sprite->unk_134[sprite->unk_120],
                                            &sprite->unk_140[Hu3DBufNo], arg2);
            } else {
                cached = HuSprDispTile(HuSprTileBuf, sprite, NULL, NULL, arg2);
            }
            gSPEndDisplayList(cached++);
            size = (u8 *)cached - (u8 *)HuSprTileBuf;
            sprite->unk_128[sprite->unk_120] = HuMemAlloc(size);
            bcopy(HuSprTileBuf, sprite->unk_128[sprite->unk_120], size);
            sprite->unk_124 = sprite->unk_128[sprite->unk_120];
            sprite->unk_120++;
            if (sprite->unk_120 >= 3) {
                sprite->unk_120 = 0;
            }
            sprite->dispAttr &= ~HUSPR_ATTR_DLDIRTY;
        }
        gSPDisplayList(gdl++, sprite->unk_124);
    } else {
        if (sprBilerpF) {
            vertices = HuSprVtxPos;
            gdl = HuSprDispTile(gdl, sprite, vertices, &sprite->unk_140[Hu3DBufNo], arg2);
            if (!(sprite->dispAttr & HUSPR_ATTR_MULTITEX)) {
                HuSprVtxPos = vertices + (sprStripNum + 2) * 2;
            } else {
                HuSprVtxPos = vertices + (sprStripNum + 2) * 4;
            }
        } else {
            gdl = HuSprDispTile(gdl, sprite, NULL, NULL, arg2);
        }
    }
    *gfx = gdl;
}

Gfx *HuSprDispTile(Gfx *gfx, HuSprite *sprite, Vtx *vertices, Mtx *matrix, s32 arg4) {
    HuSprAnimPat *cel;
    f32 texT = 0.0f;
    f32 texS = 0.0f;
    f32 texStep = 0.0f;
    f32 drawStep;
    f32 scaleY;
    f32 drawY;
    f32 scaleX;
    f32 left;
    f32 right;
    f32 top;
    f32 stripHeight;
    s32 flipX;
    s32 flipY;
    s32 remaining;
    s32 height;
    s32 strip;
    s32 i;
    s32 cms;
    s32 cmt;
    s32 masks;
    s32 maskt;
    Vtx *vertexBase;

    cel = &sprite->data->pat[sprite->patNo];
    scaleX = sprite->unk_18;
    scaleY = sprite->unk_1C;
    drawY = 0.0f;
    drawStep = drawY;
    vertexBase = NULL;
    if (sprite->dispAttr & HUSPR_ATTR_MULTITEX) {
        gDPSetCycleType(gfx++, G_CYC_2CYCLE);
        gDPPipeSync(gfx++);
        gDPSetCombineLERP(gfx++, TEXEL1, TEXEL0, PRIMITIVE_ALPHA, TEXEL0, TEXEL1, TEXEL0, PRIMITIVE, TEXEL0,
                          0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
        gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_AA_XLU_SURF2);
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, (u8)sprite->tpLvl);
        sprStripNum <<= 1;
        sprStripHeight >>= 1;
    }
    if ((sprite->dispAttr & (HUSPR_ATTR_RECT | HUSPR_ATTR_RECT_TILE)) == (HUSPR_ATTR_RECT | HUSPR_ATTR_RECT_TILE)) {
        sprite->unk_30.f = ((s16)sprite->unk_40 - (s16)sprite->unk_3C) / (cel->sizeX * scaleX);
        sprite->unk_34.f = ((s16)sprite->unk_42 - (s16)sprite->unk_3E) / (cel->sizeY * scaleY);
    }
    if (sprite->dispAttr & HUSPR_ATTR_ZBUF) {
        gDPSetDepthSource(gfx++, G_ZS_PRIM);
        gDPSetPrimDepth(gfx++, (u16)sprite->unk_44, 0);
    }
    if (sprStripRest != 0) {
        sprStripCnt = sprStripNum + 1;
    } else {
        sprStripCnt = sprStripNum;
    }
    if (sprBilerpF) {
        vertexBase = vertices;
        flipX = 0;
        if (sprite->dispAttr & HUSPR_ATTR_FLIPX) {
            left = cel->sizeX * 63.999;
            right = 0.0f;
        } else {
            left = 0.0f;
            right = cel->sizeX * 63.999;
            flipX = 1;
        }
        if (sprite->dispAttr & HUSPR_ATTR_FLIPY) {
            if (sprite->dispAttr & HUSPR_ATTR_RECT) {
                top = ((s16)sprite->unk_3E - (s16)sprite->unk_42) / sprite->unk_34.f;
            } else {
                top = -cel->sizeY;
            }
            flipY = -1;
        } else {
            top = 0.0f;
            flipY = 1;
        }
        texT = 0.0f;
        remaining = cel->sizeY;
        for (strip = 0; strip < sprStripNum + 2; strip++) {
            if (remaining < sprStripHeight) {
                height = remaining;
            } else {
                height = sprStripHeight;
            }
            remaining -= sprStripHeight;
            if (sprite->dispAttr & HUSPR_ATTR_RECT) {
                vertices[0].v.ob[0] = 0;
                vertices[1].v.ob[0] = ((s16)sprite->unk_40 - (s16)sprite->unk_3C) / sprite->unk_30.f;
            } else {
                vertices[0].v.ob[0] = -cel->sizeX * (sprite->unk_30.f - 1.0f) * (flipX ^ 1);
                vertices[1].v.ob[0] = cel->sizeX;
            }
            vertices[0].v.ob[1] = vertices[1].v.ob[1] = top;
            vertices[0].v.tc[0] = left;
            vertices[1].v.tc[0] = right;
            vertices[0].v.tc[1] = vertices[1].v.tc[1] = texT * 128.0f;
            for (i = 0; i < 2; i++) {
                vertices[i].v.ob[2] = -1;
                vertices[i].v.cn[0] = 0;
                vertices[i].v.cn[1] = 0;
                vertices[i].v.cn[2] = 0;
                vertices[i].v.cn[3] = 255;
            }
            if ((sprite->dispAttr & HUSPR_ATTR_WRAPS_MASK) && sprite->unk_38) {
                vertices[1].v.ob[0] *= sprite->unk_30.f;
                vertices[0].v.tc[0] *= sprite->unk_30.f;
                vertices[1].v.tc[0] *= sprite->unk_30.f;
            }
            if ((sprite->dispAttr & HUSPR_ATTR_WRAPT_MASK) && sprite->unk_3A) {
                vertices[0].v.ob[1] *= sprite->unk_34.f;
                vertices[1].v.ob[1] *= sprite->unk_34.f;
                vertices[0].v.tc[1] *= sprite->unk_34.f;
                vertices[1].v.tc[1] *= sprite->unk_34.f;
            }
            if (sprite->dispAttr & HUSPR_ATTR_RECT) {
                if (flipY < 0) {
                    top += (f32)(((s16)sprite->unk_42 - (s16)sprite->unk_3E) * height / sprStripHeight) / sprite->unk_34.f;
                } else {
                    top += (f32)(((s16)sprite->unk_3E - (s16)sprite->unk_42) * height / sprStripHeight) / sprite->unk_34.f;
                }
            } else {
                top += -flipY * height;
            }
            vertices += 2;
            texT += height;
        }
    } else {
        if (sprite->dispAttr & HUSPR_ATTR_RECT) {
            left = (s16)sprite->unk_3C;
            right = (s16)sprite->unk_40;
            top = (s16)sprite->unk_3E;
            scaleX = (f32)((s16)sprite->unk_40 - (s16)sprite->unk_3C) / cel->sizeX;
            scaleY = (f32)((s16)sprite->unk_42 - (s16)sprite->unk_3E) / cel->sizeY;
            stripHeight = (f32)(((s16)sprite->unk_42 - (s16)sprite->unk_3E) / sprStripNum);
        } else {
            left = sprite->unk_04 - (u16)cel->centerX * scaleX;
            right = left + cel->sizeX * scaleX;
            top = sprite->unk_08 - (u16)cel->centerY * scaleY;
            stripHeight = sprStripHeight * scaleY;
        }
        if (sprite->dispAttr & HUSPR_ATTR_FLIPX) {
            texS = cel->sizeX - 1;
            flipX = -1;
        } else {
            texS = 0;
            flipX = 1;
        }
        if (sprite->dispAttr & HUSPR_ATTR_FLIPY) {
            flipY = -1;
            drawY = top + stripHeight * (sprStripNum - 1);
            drawY += sprStripRest * scaleY;
            drawStep = -stripHeight;
            texT = stripHeight / scaleY - 1.0f;
        } else {
            drawY = top;
            drawStep = stripHeight;
            flipY = 1;
            texT = 0.0f;
        }
        texStep = stripHeight / scaleY;
    }
    if (sprite->dispAttr & HUSPR_ATTR_WRAPS_MASK) {
        masks = sprite->unk_38;
        cms = (u32)sprite->dispAttr >> HUSPR_ATTR_WRAPS_SHIFT;
        cms--;
    } else {
        masks = 0;
        cms = 0;
    }
    if (sprite->dispAttr & HUSPR_ATTR_WRAPT_MASK) {
        maskt = sprite->unk_3A;
        cmt = (u32)sprite->dispAttr >> HUSPR_ATTR_WRAPT_SHIFT;
        cmt--;
    } else {
        maskt = 0;
        cmt = 0;
    }
    remaining = cel->sizeY;
    for (strip = 0; strip < sprStripCnt; strip++) {
        if (remaining < sprStripHeight) {
            height = remaining;
        } else {
            height = sprStripHeight;
        }
        remaining -= sprStripHeight;
        HuSprTileLoad(&gfx, sprite, height, 0, strip * sprStripHeight,
                           cel->sizeX - 1, strip * sprStripHeight + height - 1, cms, cmt, masks, maskt);
        if (sprBilerpF) {
            gSPVertex(gfx++, &vertexBase[strip * 2], 4, 0);
            gSP2Triangles(gfx++, 0, 2, 3, 0, 0, 3, 1, 0);
        } else {
            gSPScisTextureRectangle(gfx++, (s32)left << 2, (s16)drawY << 2,
                                    (s32)right << 2, (s32)(drawY + height * scaleY) << 2, 0,
                                    (s16)texS << 5, (s16)texT << 5,
                                    (s16)((sprTexScale / scaleX) * 1024.0f * flipX),
                                    (s16)((1.0f / scaleY) * 1024.0f * flipY));
            if (flipY < 0 && remaining < sprStripHeight) {
                drawStep = -(f32)remaining * scaleY;
                texStep = remaining / scaleY;
            }
            texT += texStep;
            drawY += drawStep;
        }
    }
    gDPPipeSync(gfx++);
    return gfx;
}

void HuSprTileLoad(Gfx **gfx, HuSprite *sprite, u16 height, u16 uls, u16 ult,
                        u16 lrs, u16 lrt, u16 cms, u16 cmt, u16 masks, u16 maskt) {
    HuSprAnimPat *cel;
    Gfx *gdl;

    cel = &sprite->data->pat[sprite->patNo];
    gdl = *gfx;
    switch (sprTlutMode) {
        case 0:
            gDPLoadTextureTile_4b(gdl++, (void *)0x02000000,
                                  sprTexFmt, cel->sizeX, height, uls, ult, lrs, lrt,
                                  0, cms, cmt, masks, maskt, 0, 0);
            break;
        case 1:
            HuLoadTextureBlock_4b(&gdl, (void *)0x02000000, sprTexFmt, cel->sizeX,
                               height, uls, ult, lrs, lrt, 0, cms, cmt, masks, maskt, 0, 0);
            break;
        case 2:
            HuLoadTextureTile(&gdl, (u16 *)0x02000000, sprTexFmt, sprTexSiz,
                               cel->sizeX, cel->sizeY, uls, ult, lrs, lrt, 0, cms, cmt, masks, maskt, 0, 0);
            break;
        case 3:
            HuLoadTextureBlock(&gdl, (void *)0x02000000, sprTexFmt, sprTexSiz,
                               cel->sizeX, height, uls, ult, lrs, lrt, 0, cms, cmt, masks, maskt, 0, 0);
            break;
    }
    if (sprite->dispAttr & HUSPR_ATTR_MULTITEX) {
        HuSprTileLoad_4b(&gdl, sprite, height, uls, ult, lrs, lrt, cms, cmt, masks, maskt);
    }
    *gfx = gdl;
}

void HuSprTileLoad_4b(Gfx **gfx, HuSprite *sprite, u16 height, u16 uls, u16 ult,
                        u16 lrs, u16 lrt, u16 cms, u16 cmt, u16 masks, u16 maskt) {
    HuSprAnimPat *cel;
    Gfx *gdl;

    cel = &sprite->data->pat[sprite->patNo];
    gdl = *gfx;
    switch (sprTlutMode) {
        case 0:
            gDPLoadMultiTile_4b(gdl++, (void *)0x02000000, sprTmemLineMax, 1,
                                sprTexFmt, cel->sizeX, height, uls, ult, lrs, lrt,
                                0, cms, cmt, masks, maskt, 0, 0);
            break;
        case 1:
            HuLoadMultiBlock_4b(&gdl, (void *)0x02000000, sprTexFmt, cel->sizeX,
                               height, uls, ult, lrs, lrt, 0, cms, cmt, masks, maskt, 0, 0, 1, sprTmemLineMax);
            break;
        case 2:
            HuLoadMultiTile(&gdl, (void *)0x02000000, sprTexFmt, sprTexSiz,
                               cel->sizeX, cel->sizeY, uls, ult, lrs, lrt, 0, cms, cmt, masks, maskt, 0, 0, 1, sprTmemLineMax);
            break;
        case 3:
            HuLoadMultiBlock(&gdl, (void *)0x02000000, sprTexFmt, sprTexSiz,
                               cel->sizeX, height, uls, ult, lrs, lrt, 0, cms, cmt, masks, maskt, 0, 0, 1, sprTmemLineMax);
            break;
    }
    *gfx = gdl;
}
