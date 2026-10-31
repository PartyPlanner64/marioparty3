#include "common.h"
#include "mallocblock.h"

#define SPRPUT_CC_PRIM_DECALA 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0
#define SPRPUT_CC_PRIM_MODULATEA 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0
#define SPRPUT_CC_BLEND_DECALA 1, PRIMITIVE, TEXEL0, PRIMITIVE, 0, 0, 0, TEXEL0
#define SPRPUT_CC_BLEND_MODULATEA 1, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0
#define SPRPUT_CC_TEX_MODULATEA 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0

extern f32 D_800BD810_main[4][2];

extern s32 D_800BD830_main;
extern s32 D_800BD834_main;
extern s32 D_800BD838_main;
extern s32 D_800A1EB0_main;
extern s32 D_800BD83C_main;
extern s32 D_800BD840_main;
extern s32 D_800BD844_main;
extern s32 D_800BD848_main;
extern s32 D_800BD84C_main;
extern s32 D_800BD850_main;
extern s32 D_800A1EB4_main[];
extern s32 D_800A1EC4_main[];
extern s32 D_800A1ED0_main[];
extern s16 D_800A1EE0_main[];
extern s16 D_800A2018_main[];
extern u8 D_800D2008_main;
extern Gfx *D_800CCF30_main;
extern Vtx *D_800D59F4_main;

void func_80034F70_main(Gfx **gfx, void *image, s32 fmt, s32 width, s32 height,
                        s32 uls, s32 ult, s32 lrs, s32 lrt, s32 pal, s32 cms, s32 cmt,
                        s32 masks, s32 maskt, s32 shifts, s32 shiftt, s32 tile, s32 tmem);
void func_800343FC_main(Gfx **gfx, void *image, s32 fmt, s32 siz, s32 width, s32 height,
                        s32 uls, s32 ult, s32 lrs, s32 lrt, s32 pal, s32 cms, s32 cmt,
                        s32 masks, s32 maskt, s32 shifts, s32 shiftt, s32 tile, s32 tmem);
void func_80034C08_main(Gfx **gfx, void *image, s32 fmt, s32 siz, s32 width, s32 height,
                        s32 uls, s32 ult, s32 lrs, s32 lrt, s32 pal, s32 cms, s32 cmt,
                        s32 masks, s32 maskt, s32 shifts, s32 shiftt, s32 tile, s32 tmem);

void func_80034998_main(Gfx **gfx, void *image, s32 fmt, s32 width, s32 height,
                        s32 uls, s32 ult, s32 lrs, s32 lrt, s32 pal, s32 cms, s32 cmt,
                        s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void func_800341D0_main(Gfx **gfx, u16 *image, s32 fmt, s32 siz, s32 width, s32 height,
                        s32 uls, s32 ult, s32 lrs, s32 lrt, s32 pal, s32 cms, s32 cmt,
                        s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void func_80059CDC_main(Gfx **gfx, HuSprite *sprite, u16 height, u16 uls, u16 ult,
                        u16 lrs, u16 lrt, u16 cms, u16 cmt, u16 masks, u16 maskt);

void func_8005988C_main(Gfx **gfx, HuSprite *sprite, u16 height, u16 uls, u16 ult,
                        u16 lrs, u16 lrt, u16 cms, u16 cmt, u16 masks, u16 maskt);

Gfx *func_800589F4_main(Gfx *gfx, HuSprite *sprite, Vtx *vertices, Mtx *matrix, s32 arg4);
void func_8003521C_main(HuMtx4F transform, f64 x, f64 y, f64 angle);
void func_80017CD0_main(HuMtx4F transform, f32 x, f32 y, f32 z);

s32 func_800575D8_main(f32 vertices[][2]);

s32 func_80057400_main(HuSprite *sprite) {
    HuSprite_Unk84_Unk00_Struct *cel;
    f32 sin;
    f32 cos;
    f32 left;
    f32 top;
    f32 right;
    f32 bottom;

    cel = &sprite->unk_84->unk00[sprite->unk_90];
    sin = sindf(sprite->unk_20);
    cos = cosdf(sprite->unk_20);
    if (!(sprite->unk_24 & 0x10000)) {
        left = -(u16)cel->unk08 * sprite->unk_18;
        top = -(u16)cel->unk0A * sprite->unk_1C;
        right = (cel->unk04 - (u16)cel->unk08) * sprite->unk_18;
        bottom = (cel->unk06 - (u16)cel->unk0A) * sprite->unk_1C;
    } else {
        left = (s16)sprite->unk_3C;
        top = (s16)sprite->unk_3E;
        right = (s16)sprite->unk_40;
        bottom = (s16)sprite->unk_42;
    }
    D_800BD810_main[0][0] = cos * left + sin * top + sprite->unk_04;
    D_800BD810_main[0][1] = -sin * left + cos * top + sprite->unk_08;
    D_800BD810_main[1][0] = cos * right + sin * top + sprite->unk_04;
    D_800BD810_main[1][1] = -sin * right + cos * top + sprite->unk_08;
    D_800BD810_main[2][0] = cos * right + sin * bottom + sprite->unk_04;
    D_800BD810_main[2][1] = -sin * right + cos * bottom + sprite->unk_08;
    D_800BD810_main[3][0] = cos * left + sin * bottom + sprite->unk_04;
    D_800BD810_main[3][1] = -sin * left + cos * bottom + sprite->unk_08;
    return func_800575D8_main(D_800BD810_main);
}

// Test the transformed sprite quad against the 320 by 240 viewport.
s32 func_800575D8_main(f32 vertices[][2]) {
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

void func_800579E4_main(Gfx **gfx, HuSprite *sprite, s32 arg2) {
    Gfx *gdl;
    HuSprite_Unk84_Unk00_Struct *cel;
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
    if (sprite->unk_84 == NULL) {
        return;
    }
    cel = &sprite->unk_84->unk00[sprite->unk_90];
    if ((scaleX <= 0.0f) | (scaleY <= 0.0f)) {
        return;
    }
    if (!func_80057400_main(sprite)) {
        return;
    }
    gDPSetScissor(gdl++, G_SC_NON_INTERLACE, sprite->unk_204, sprite->unk_206, sprite->unk_208, sprite->unk_20A);
    switch (sprite->unk_84->unk18) {
        case 4:
            D_800BD834_main = G_IM_SIZ_4b;
            if (sprite->unk_84->unk1A == 1) {
                D_800BD830_main = G_IM_FMT_IA;
                gDPSetTextureLUT(gdl++, G_TT_NONE);
            } else {
                D_800BD830_main = G_IM_FMT_CI;
                if (sprite->unk_98.unk00 != NULL) {
                    gDPLoadTLUT_pal16(gdl++, 0, sprite->unk_98.unk6C);
                } else {
                    gDPLoadTLUT_pal16(gdl++, 0, sprite->unk_84->unk0C);
                }
                gDPSetTextureLUT(gdl++, G_TT_RGBA16);
                D_800A1EB0_main = 128;
            }
            D_800BD838_main = 0;
            break;
        case 8:
            D_800BD834_main = G_IM_SIZ_8b;
            if (sprite->unk_84->unk1A == 1) {
                D_800BD830_main = G_IM_FMT_IA;
                gDPSetTextureLUT(gdl++, G_TT_NONE);
                D_800BD838_main = 2;
            } else {
                D_800BD830_main = G_IM_FMT_CI;
                if (sprite->unk_98.unk00 != NULL) {
                    gDPLoadTLUT_pal256(gdl++, sprite->unk_98.unk6C);
                } else {
                    gDPLoadTLUT_pal256(gdl++, sprite->unk_84->unk0C);
                }
                gDPSetTextureLUT(gdl++, G_TT_RGBA16);
                D_800A1EB0_main = 128;
                D_800BD838_main = 2;
            }
            break;
        case 16:
            D_800BD834_main = G_IM_SIZ_16b;
            if (sprite->unk_84->unk1A == 1) {
                D_800BD830_main = G_IM_FMT_IA;
            } else {
                D_800BD830_main = G_IM_FMT_RGBA;
            }
            gDPSetTextureLUT(gdl++, G_TT_NONE);
            D_800A1EB0_main = 256;
            D_800BD838_main = 2;
            break;
        case 32:
            D_800BD834_main = G_IM_SIZ_32b;
            D_800BD830_main = G_IM_FMT_RGBA;
            gDPSetTextureLUT(gdl++, G_TT_NONE);
            D_800A1EB0_main = 256;
            D_800BD838_main = 2;
            break;
        case 0x8004:
            D_800BD834_main = G_IM_SIZ_4b;
            D_800BD830_main = G_IM_FMT_I;
            gDPSetTextureLUT(gdl++, G_TT_NONE);
            D_800A1EB0_main = 256;
            D_800BD838_main = 0;
            break;
        case 0x8008:
            D_800BD834_main = G_IM_SIZ_8b;
            D_800BD830_main = G_IM_FMT_I;
            gDPSetTextureLUT(gdl++, G_TT_NONE);
            D_800A1EB0_main = 256;
            D_800BD838_main = 2;
            break;
    }
    // Round the row width up to the texture load alignment before sizing strips.
    alignedWidth = (((cel->unk04 << D_800BD834_main) >> 4) << 4) >> D_800BD834_main;
    if (alignedWidth < cel->unk04) {
        alignedWidth += 16 >> D_800BD834_main;
    }
    switch (D_800BD830_main) {
        case G_IM_FMT_CI:
            if ((4096 >> D_800BD834_main) >= cel->unk06 * alignedWidth) {
                D_800BD844_main = cel->unk06;
            } else {
                D_800BD844_main = (4096 >> D_800BD834_main) / alignedWidth;
            }
            break;
        case G_IM_FMT_I:
            if (4096 >= cel->unk06 * alignedWidth) {
                D_800BD844_main = cel->unk06;
            } else {
                D_800BD844_main = 4096 / alignedWidth;
            }
            break;
        default:
            if ((8192 >> D_800BD834_main) >= cel->unk06 * alignedWidth) {
                D_800BD844_main = cel->unk06;
            } else {
                D_800BD844_main = (8192 >> D_800BD834_main) / alignedWidth;
            }
            break;
    }
    D_800BD840_main = cel->unk06 / D_800BD844_main;
    D_800BD848_main = cel->unk06 - D_800BD840_main * D_800BD844_main;
    // Aligned strips can use the block loader when its DXT rounding is exact.
    if (cel->unk04 % (16 >> D_800BD834_main) == 0) {
        if (((cel->unk04 * D_800BD844_main) << D_800BD834_main) <= 4096) {
            if (D_800A1EE0_main[cel->unk04 >> D_800A1ED0_main[D_800BD834_main]] >= D_800BD844_main ||
                D_800BD844_main == D_800A2018_main[cel->unk04 >> D_800A1ED0_main[D_800BD834_main]]) {
                D_800BD838_main++;
            }
        }
    }
    gDPPipeSync(gdl++);
    gSPSetOtherMode(gdl++, G_SETOTHERMODE_H, D_800A1EB4_main[0], 2,
                    (((u32)sprite->unk_24 >> 2) & 3) << D_800A1EB4_main[0]);
    gSPSetOtherMode(gdl++, G_SETOTHERMODE_H, D_800A1EB4_main[1], 2,
                    ((((u32)sprite->unk_24 >> 4) ^ 3) & 3) << D_800A1EB4_main[1]);
    gSPSetOtherMode(gdl++, G_SETOTHERMODE_H, D_800A1EB4_main[2], 2,
                    (((u32)sprite->unk_24 >> 6) & 3) << D_800A1EB4_main[2]);
    gSPSetOtherMode(gdl++, G_SETOTHERMODE_L, D_800A1EB4_main[3], 2,
                    D_800A1EC4_main[((u32)sprite->unk_24 >> 22) & 3]);
    if (((u32)sprite->unk_24 >> 6) & 2) {
        gDPSetRenderMode(gdl++, G_RM_NOOP, G_RM_NOOP2);
        gDPSetCombineMode(gdl++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        D_800BD83C_main = 4;
    } else {
        intensity = sprite->unk_84->unk18 >> 15;
        renderMode = (sprite->unk_24 & 0x4000000) ? Z_CMP | Z_UPD : 0;
        switch (((u32)sprite->unk_24 >> 10) & 3) {
            case 0:
                if (sprite->unk_24 & 0x1000) {
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
                if (sprite->unk_24 & 0x1000) {
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
                if (sprite->unk_24 & 0x1000) {
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
                if (sprite->unk_24 & 0x2000000) {
                    gDPSetCombineMode(gdl++, SPRPUT_CC_BLEND_DECALA, SPRPUT_CC_BLEND_DECALA);
                } else {
                    gDPSetCombineMode(gdl++, G_CC_DECALRGBA, G_CC_DECALRGBA);
                }
            } else {
                if (sprite->unk_24 & 0x2000000) {
                    gDPSetCombineMode(gdl++, SPRPUT_CC_BLEND_MODULATEA, SPRPUT_CC_BLEND_MODULATEA);
                } else {
                    gDPSetCombineMode(gdl++, SPRPUT_CC_TEX_MODULATEA, SPRPUT_CC_TEX_MODULATEA);
                }
            }
        }
        gDPSetPrimColor(gdl++, 0, 0, sprite->color[0], sprite->color[1], sprite->color[2], (u8)sprite->tpLvl);
        D_800BD83C_main = 1;
    }
    D_800BD850_main = ((u32)sprite->unk_24 >> 30) & 1;
    gSPSegment(gdl++, 2, osVirtualToPhysical(cel->unk00));
    if (D_800BD850_main) {
        if (sprite->unk_24 & 0x10000) {
            originX = ((s16)sprite->unk_3C - (s16)sprite->unk_40) * (u16)cel->unk08 / cel->unk04;
            originY = ((s16)sprite->unk_42 - (s16)sprite->unk_3E) * (u16)cel->unk0A / cel->unk06;
            sprite->unk_04 = (s16)sprite->unk_3C + ((s16)sprite->unk_40 - (s16)sprite->unk_3C) * (u16)cel->unk08 / cel->unk04;
            sprite->unk_08 = (s16)sprite->unk_3E + ((s16)sprite->unk_42 - (s16)sprite->unk_3E) * (u16)cel->unk0A / cel->unk06;
        } else {
            originX = -(u16)cel->unk08;
            originY = (u16)cel->unk0A;
        }
        transform[0][2] = transform[0][3] = transform[1][2] = transform[1][3] = transform[2][0] =
            transform[2][1] = transform[2][3] = transform[3][2] = 0.0f;
        transform[2][2] = transform[3][3] = 1.0f;
        func_8003521C_main(transform, sprite->unk_04 - 160.0f, 120.0f - sprite->unk_08, sprite->unk_20);
        func_80017CD0_main(transform, scaleX, scaleY, 1.0f);
        func_80017C10_main(transform, originX, originY, 0.0f);
        func_800898F0_main(transform, &sprite->unk_140[D_800D2008_main]);
        gSPMatrix(gdl++, osVirtualToPhysical(&sprite->unk_140[D_800D2008_main]), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    }
    if (sprite->unk_24 & 0x8000000) {
        if (sprite->unk_24 & 0x10000000) {
            if (D_800BD850_main) {
                cached = func_800589F4_main(D_800CCF30_main, sprite, sprite->unk_134[sprite->unk_120],
                                            &sprite->unk_140[D_800D2008_main], arg2);
            } else {
                cached = func_800589F4_main(D_800CCF30_main, sprite, NULL, NULL, arg2);
            }
            gSPEndDisplayList(cached++);
            size = (u8 *)cached - (u8 *)D_800CCF30_main;
            sprite->unk_128[sprite->unk_120] = HuMemAlloc(size);
            bcopy(D_800CCF30_main, sprite->unk_128[sprite->unk_120], size);
            sprite->unk_124 = sprite->unk_128[sprite->unk_120];
            sprite->unk_120++;
            if (sprite->unk_120 >= 3) {
                sprite->unk_120 = 0;
            }
            sprite->unk_24 &= ~0x10000000;
        }
        gSPDisplayList(gdl++, sprite->unk_124);
    } else {
        if (D_800BD850_main) {
            vertices = D_800D59F4_main;
            gdl = func_800589F4_main(gdl, sprite, vertices, &sprite->unk_140[D_800D2008_main], arg2);
            if (!(sprite->unk_24 & 0x2000)) {
                D_800D59F4_main = vertices + (D_800BD840_main + 2) * 2;
            } else {
                D_800D59F4_main = vertices + (D_800BD840_main + 2) * 4;
            }
        } else {
            gdl = func_800589F4_main(gdl, sprite, NULL, NULL, arg2);
        }
    }
    *gfx = gdl;
}

Gfx *func_800589F4_main(Gfx *gfx, HuSprite *sprite, Vtx *vertices, Mtx *matrix, s32 arg4) {
    HuSprite_Unk84_Unk00_Struct *cel;
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

    cel = &sprite->unk_84->unk00[sprite->unk_90];
    scaleX = sprite->unk_18;
    scaleY = sprite->unk_1C;
    drawY = 0.0f;
    drawStep = drawY;
    vertexBase = NULL;
    if (sprite->unk_24 & 0x2000) {
        gDPSetCycleType(gfx++, G_CYC_2CYCLE);
        gDPPipeSync(gfx++);
        gDPSetCombineLERP(gfx++, TEXEL1, TEXEL0, PRIMITIVE_ALPHA, TEXEL0, TEXEL1, TEXEL0, PRIMITIVE, TEXEL0,
                          0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
        gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_AA_XLU_SURF2);
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, (u8)sprite->tpLvl);
        D_800BD840_main <<= 1;
        D_800BD844_main >>= 1;
    }
    if ((sprite->unk_24 & 0x30000) == 0x30000) {
        sprite->unk_30.f = ((s16)sprite->unk_40 - (s16)sprite->unk_3C) / (cel->unk04 * scaleX);
        sprite->unk_34.f = ((s16)sprite->unk_42 - (s16)sprite->unk_3E) / (cel->unk06 * scaleY);
    }
    if (sprite->unk_24 & 0x4000000) {
        gDPSetDepthSource(gfx++, G_ZS_PRIM);
        gDPSetPrimDepth(gfx++, (u16)sprite->unk_44, 0);
    }
    if (D_800BD848_main != 0) {
        D_800BD84C_main = D_800BD840_main + 1;
    } else {
        D_800BD84C_main = D_800BD840_main;
    }
    if (D_800BD850_main) {
        vertexBase = vertices;
        flipX = 0;
        if (sprite->unk_24 & 1) {
            left = cel->unk04 * 63.999;
            right = 0.0f;
        } else {
            left = 0.0f;
            right = cel->unk04 * 63.999;
            flipX = 1;
        }
        if (sprite->unk_24 & 2) {
            if (sprite->unk_24 & 0x10000) {
                top = ((s16)sprite->unk_3E - (s16)sprite->unk_42) / sprite->unk_34.f;
            } else {
                top = -cel->unk06;
            }
            flipY = -1;
        } else {
            top = 0.0f;
            flipY = 1;
        }
        texT = 0.0f;
        remaining = cel->unk06;
        for (strip = 0; strip < D_800BD840_main + 2; strip++) {
            if (remaining < D_800BD844_main) {
                height = remaining;
            } else {
                height = D_800BD844_main;
            }
            remaining -= D_800BD844_main;
            if (sprite->unk_24 & 0x10000) {
                vertices[0].v.ob[0] = 0;
                vertices[1].v.ob[0] = ((s16)sprite->unk_40 - (s16)sprite->unk_3C) / sprite->unk_30.f;
            } else {
                vertices[0].v.ob[0] = -cel->unk04 * (sprite->unk_30.f - 1.0f) * (flipX ^ 1);
                vertices[1].v.ob[0] = cel->unk04;
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
            if ((sprite->unk_24 & 0xC0000) && sprite->unk_38) {
                vertices[1].v.ob[0] *= sprite->unk_30.f;
                vertices[0].v.tc[0] *= sprite->unk_30.f;
                vertices[1].v.tc[0] *= sprite->unk_30.f;
            }
            if ((sprite->unk_24 & 0x300000) && sprite->unk_3A) {
                vertices[0].v.ob[1] *= sprite->unk_34.f;
                vertices[1].v.ob[1] *= sprite->unk_34.f;
                vertices[0].v.tc[1] *= sprite->unk_34.f;
                vertices[1].v.tc[1] *= sprite->unk_34.f;
            }
            if (sprite->unk_24 & 0x10000) {
                if (flipY < 0) {
                    top += (f32)(((s16)sprite->unk_42 - (s16)sprite->unk_3E) * height / D_800BD844_main) / sprite->unk_34.f;
                } else {
                    top += (f32)(((s16)sprite->unk_3E - (s16)sprite->unk_42) * height / D_800BD844_main) / sprite->unk_34.f;
                }
            } else {
                top += -flipY * height;
            }
            vertices += 2;
            texT += height;
        }
    } else {
        if (sprite->unk_24 & 0x10000) {
            left = (s16)sprite->unk_3C;
            right = (s16)sprite->unk_40;
            top = (s16)sprite->unk_3E;
            scaleX = (f32)((s16)sprite->unk_40 - (s16)sprite->unk_3C) / cel->unk04;
            scaleY = (f32)((s16)sprite->unk_42 - (s16)sprite->unk_3E) / cel->unk06;
            stripHeight = (f32)(((s16)sprite->unk_42 - (s16)sprite->unk_3E) / D_800BD840_main);
        } else {
            left = sprite->unk_04 - (u16)cel->unk08 * scaleX;
            right = left + cel->unk04 * scaleX;
            top = sprite->unk_08 - (u16)cel->unk0A * scaleY;
            stripHeight = D_800BD844_main * scaleY;
        }
        if (sprite->unk_24 & 1) {
            texS = cel->unk04 - 1;
            flipX = -1;
        } else {
            texS = 0;
            flipX = 1;
        }
        if (sprite->unk_24 & 2) {
            flipY = -1;
            drawY = top + stripHeight * (D_800BD840_main - 1);
            drawY += D_800BD848_main * scaleY;
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
    if (sprite->unk_24 & 0xC0000) {
        masks = sprite->unk_38;
        cms = (u32)sprite->unk_24 >> 18;
        cms--;
    } else {
        masks = 0;
        cms = 0;
    }
    if (sprite->unk_24 & 0x300000) {
        maskt = sprite->unk_3A;
        cmt = (u32)sprite->unk_24 >> 20;
        cmt--;
    } else {
        maskt = 0;
        cmt = 0;
    }
    remaining = cel->unk06;
    for (strip = 0; strip < D_800BD84C_main; strip++) {
        if (remaining < D_800BD844_main) {
            height = remaining;
        } else {
            height = D_800BD844_main;
        }
        remaining -= D_800BD844_main;
        func_8005988C_main(&gfx, sprite, height, 0, strip * D_800BD844_main,
                           cel->unk04 - 1, strip * D_800BD844_main + height - 1, cms, cmt, masks, maskt);
        if (D_800BD850_main) {
            gSPVertex(gfx++, &vertexBase[strip * 2], 4, 0);
            gSP2Triangles(gfx++, 0, 2, 3, 0, 0, 3, 1, 0);
        } else {
            gSPScisTextureRectangle(gfx++, (s32)left << 2, (s16)drawY << 2,
                                    (s32)right << 2, (s32)(drawY + height * scaleY) << 2, 0,
                                    (s16)texS << 5, (s16)texT << 5,
                                    (s16)((D_800BD83C_main / scaleX) * 1024.0f * flipX),
                                    (s16)((1.0f / scaleY) * 1024.0f * flipY));
            if (flipY < 0 && remaining < D_800BD844_main) {
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

void func_8005988C_main(Gfx **gfx, HuSprite *sprite, u16 height, u16 uls, u16 ult,
                        u16 lrs, u16 lrt, u16 cms, u16 cmt, u16 masks, u16 maskt) {
    HuSprite_Unk84_Unk00_Struct *cel;
    Gfx *gdl;

    cel = &sprite->unk_84->unk00[sprite->unk_90];
    gdl = *gfx;
    switch (D_800BD838_main) {
        case 0:
            gDPLoadTextureTile_4b(gdl++, (void *)0x02000000,
                                  D_800BD830_main, cel->unk04, height, uls, ult, lrs, lrt,
                                  0, cms, cmt, masks, maskt, 0, 0);
            break;
        case 1:
            func_80034998_main(&gdl, (void *)0x02000000, D_800BD830_main, cel->unk04,
                               height, uls, ult, lrs, lrt, 0, cms, cmt, masks, maskt, 0, 0);
            break;
        case 2:
            func_800341D0_main(&gdl, (u16 *)0x02000000, D_800BD830_main, D_800BD834_main,
                               cel->unk04, cel->unk06, uls, ult, lrs, lrt, 0, cms, cmt, masks, maskt, 0, 0);
            break;
        case 3:
            func_8003465C_main(&gdl, (void *)0x02000000, D_800BD830_main, D_800BD834_main,
                               cel->unk04, height, uls, ult, lrs, lrt, 0, cms, cmt, masks, maskt, 0, 0);
            break;
    }
    if (sprite->unk_24 & 0x2000) {
        func_80059CDC_main(&gdl, sprite, height, uls, ult, lrs, lrt, cms, cmt, masks, maskt);
    }
    *gfx = gdl;
}

void func_80059CDC_main(Gfx **gfx, HuSprite *sprite, u16 height, u16 uls, u16 ult,
                        u16 lrs, u16 lrt, u16 cms, u16 cmt, u16 masks, u16 maskt) {
    HuSprite_Unk84_Unk00_Struct *cel;
    Gfx *gdl;

    cel = &sprite->unk_84->unk00[sprite->unk_90];
    gdl = *gfx;
    switch (D_800BD838_main) {
        case 0:
            gDPLoadMultiTile_4b(gdl++, (void *)0x02000000, D_800A1EB0_main, 1,
                                D_800BD830_main, cel->unk04, height, uls, ult, lrs, lrt,
                                0, cms, cmt, masks, maskt, 0, 0);
            break;
        case 1:
            func_80034F70_main(&gdl, (void *)0x02000000, D_800BD830_main, cel->unk04,
                               height, uls, ult, lrs, lrt, 0, cms, cmt, masks, maskt, 0, 0, 1, D_800A1EB0_main);
            break;
        case 2:
            func_800343FC_main(&gdl, (void *)0x02000000, D_800BD830_main, D_800BD834_main,
                               cel->unk04, cel->unk06, uls, ult, lrs, lrt, 0, cms, cmt, masks, maskt, 0, 0, 1, D_800A1EB0_main);
            break;
        case 3:
            func_80034C08_main(&gdl, (void *)0x02000000, D_800BD830_main, D_800BD834_main,
                               cel->unk04, height, uls, ult, lrs, lrt, 0, cms, cmt, masks, maskt, 0, 0, 1, D_800A1EB0_main);
            break;
    }
    *gfx = gdl;
}
