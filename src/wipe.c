#include "game/wipe.h"
#include "include_asm.h"
#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/gamemes.h"
#include "game/texload.h"
#include "game/malloc.h"
#include "game/mallocblock.h"
#include "game/hu3d.h"
#include "game/data.h"

typedef struct {
    s16 width;
    s16 height;
    u8 *pixels;
} WipeTexture;

typedef struct {
    u8 unk00[2];
    u8 offset[2];
    u8 width[2];
    u8 height[2];
} WipeTextureHeader;

extern WipeTexture D_800D1F5C_main;
extern u16 *D_800A26D4_main;
extern u16 *D_800BDA70_main;
extern u16 *D_800BDA74_main;
extern u8 D_800BDA78_main;
extern Gfx *D_800BDA7C_main;
extern s16 D_800BDA80_main;
extern s16 D_800BDA82_main;
extern u8 D_800CDA74_main;
extern u8 D_800D0598_main;
extern u8 *D_800D1F80_main[8];
extern u8 D_800D5304_main;
extern u8 D_800D212E_main;
extern u16 *D_800D5550_main;
extern Gfx D_800A26D8_main[];
extern Gfx D_800A2728_main[];
extern Gfx D_800A2738_main[];
extern u16 *currFrameBuffer;
extern u8 *D_800D1F60_main;


void WipeInit(void) {
    s16 i;

    wipeStat = 0;
    wipeMode = WIPE_MODE_DUMMY;
    D_800D212E_main = 0;
    D_800D0598_main = 0;
    D_800CDA74_main = 0;
    D_800D5304_main = 0;
    for (i = 0; i < 8; i++) {
        D_800D1F80_main[i] = NULL;
    }
    GMesInit();
}

void WipeExecAlways(Gfx **gfx) {
    s16 i;

    if (wipeMode == WIPE_MODE_BLANK) {
        switch (wipeType) {
            case WIPE_TYPE_CROSS:
                WipeFrameStill(gfx);
                break;
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                func_800651F0_main(gfx, 1.0f);
                break;
            default:
                WipeColorFill(gfx, 255, D_800A2728_main);
                break;
        }
        return;
    }
    GMesExec(gfx);
    if (wipeMode == WIPE_MODE_DUMMY) {
        return;
    }
    switch (wipeMode) {
        case WIPE_MODE_IN:
            switch (wipeType) {
                case 11:
                    wipeStat = WipeFadeIn(gfx);
                    break;
                case WIPE_TYPE_CROSS:
                    wipeStat = WipeCrossFadeIn(gfx);
                    break;
                case 1:
                    wipeStat = func_80063454_main(gfx);
                    break;
                case 2:
                    wipeStat = func_800640EC_main(gfx);
                    break;
                case 12:
                    wipeStat = func_80065D80_main(gfx);
                    break;
                case WIPE_TYPE_NORMAL:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                    wipeStat = func_8006515C_main(gfx);
                    break;
            }
            wipeTime += 1.0f;
            if (wipeStat == 0) {
                WipeColorSet(0, 0, 0);
                if (D_800A26D4_main != NULL) {
                    if (D_800D5304_main == 0) {
                        HuMemMemoryFreePerm(D_800A26D4_main);
                    }
                    D_800A26D4_main = NULL;
                }
                for (i = 0; i < 8; i++) {
                    if (D_800D1F80_main[i] != NULL) {
                        HuMemMemoryFreePerm(D_800D1F80_main[i]);
                    }
                    D_800D1F80_main[i] = NULL;
                }
                D_800D1F60_main = NULL;
                func_80019C68_main(TAG_WIPE);
            }
            break;
        case WIPE_MODE_OUT:
            switch (wipeType) {
                case WIPE_TYPE_NORMAL:
                    wipeStat = WipeImageOut(gfx, 0);
                    break;
                case 11:
                    wipeStat = WipeFadeOut(gfx);
                    break;
                case WIPE_TYPE_CROSS:
                    wipeStat = WipeCrossFadeOut(gfx);
                    break;
                case 1:
                    wipeStat = func_80063510_main(gfx);
                    break;
                case 2:
                    wipeStat = func_80065094_main(gfx);
                    break;
                case 12:
                    wipeStat = func_80065E88_main(gfx);
                    break;
                case 3:
                    wipeStat = WipeImageOut(gfx, 18);
                    break;
                case 4:
                    wipeStat = WipeImageOut(gfx, 19);
                    break;
                case 5:
                    wipeStat = WipeImageOut(gfx, 20);
                    break;
                case 6:
                    wipeStat = WipeImageOut(gfx, 21);
                    break;
                case 7:
                    wipeStat = WipeImageOut(gfx, 22);
                    break;
                case 8:
                    wipeStat = WipeImageOut(gfx, 17);
                    break;
                case 9:
                    wipeStat = WipeImageOut(gfx, 16);
                    break;
                case 10:
                    wipeStat = WipeImageOut(gfx, 15);
                    break;
            }
            wipeTime += 1.0f;
            break;
    }
    if (wipeStat == 0) {
        if (wipeMode == WIPE_MODE_OUT) {
            wipeMode = WIPE_MODE_BLANK;
        } else {
            wipeMode = WIPE_MODE_DUMMY;
        }
        wipeTime = 0.0f;
    }
}

void WipeCreateIn(s16 arg0, s16 arg1) {
    if (wipeStat == 0) {
        wipeMode = WIPE_MODE_IN;
        wipeStat = 1;
        if (arg0 != WIPE_TYPE_PREV) {
            wipeType = arg0;
        }
        wipeDuration = arg1;
        wipeTime = 0.0f;
    }
}

void WipeCreateOut(s16 arg0, s16 arg1) {
    if (wipeStat == 0) {
        wipeMode = WIPE_MODE_OUT;
        wipeStat = 1;
        if (arg0 != WIPE_TYPE_PREV) {
            wipeType = arg0;
        }
        wipeDuration = arg1;
        wipeTime = 0.0f;
    }
}

s32 WipeStatGet(void) {
    return wipeStat;
}

void WipeColorSet(u8 red, u8 green, u8 blue) {
    D_800CDA74_main = red;
    D_800D0598_main = green;
    D_800D212E_main = blue;
}

u8 *WipeMalloc(u32 size) {
    s16 i;

    for (i = 0; i < 8; i++) {
        if (D_800D1F80_main[i] == NULL) {
            break;
        }
    }
    if (i == 8) {
        return NULL;
    }
    D_800D1F80_main[i] = HuMemMemoryAllocPerm(size);
    return D_800D1F80_main[i];
}

s32 WipeFadeIn(Gfx **gfx) {
    if (wipeDuration == 0.0f) {
        return 0;
    }
    WipeColorFill(gfx, 255.0f - (wipeTime / wipeDuration) * 255.0f, D_800A2728_main);
    if (wipeTime >= wipeDuration) {
        return 0;
    }
    return 1;
}

s32 WipeFadeOut(Gfx **gfx) {
    if (wipeDuration == 0.0f) {
        return 0;
    }
    WipeColorFill(gfx, (wipeTime / wipeDuration) * 255.0f, D_800A2728_main);
    if (wipeTime >= wipeDuration) {
        return 0;
    }
    return 1;
}

void WipeColorFill(Gfx **gfx, u8 alpha, Gfx *displayList) {
    gSPDisplayList((*gfx)++, D_800A26D8_main);
    gDPSetRenderMode((*gfx)++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetCombineMode((*gfx)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor((*gfx)++, 0, 0, D_800CDA74_main, D_800D0598_main, D_800D212E_main, alpha);
    gDPFillRectangle((*gfx)++, 0, 0, 320, 240);
}

s32 WipeCrossFadeIn(Gfx **gfx) {
    u8 alpha;

    if (D_800A26D4_main == NULL) {
        return 0;
    }
    if (wipeDuration == 0.0f) {
        goto cleanup;
    }
    alpha = 255.0f - (wipeTime / wipeDuration) * 255.0f;
    gSPDisplayList((*gfx)++, D_800A26D8_main);
    gDPSetCombineMode((*gfx)++, G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM);
    gDPSetRenderMode((*gfx)++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetPrimColor((*gfx)++, 0, 0, 255, 255, 255, alpha);
    func_80062884_main(gfx, D_800D5550_main);
    if (wipeTime >= wipeDuration) {
    cleanup:
        if (D_800D5304_main == 0) {
            HuMemMemoryFreePerm(D_800A26D4_main);
        }
        D_800A26D4_main = NULL;
        return 0;
    }
    return 1;
}

s32 WipeCrossFadeOut(Gfx **gfx) {
    gSPDisplayList((*gfx)++, D_800A26D8_main);
    if (wipeTime == 0.0f) {
        D_800A26D4_main = HuMemMemoryAllocPerm(320 * 240 * sizeof(u16) + 64);
        D_800D5550_main = (u16 *)(((u32)D_800A26D4_main + 63) & ~63);
        func_8006265C_main(gfx, D_800D5550_main);
        return 1;
    }
    func_80062884_main(gfx, D_800D5550_main);
    if (wipeTime > 1.0f) {
        return 0;
    }
    return 1;
}

void func_8006265C_main(Gfx **gfx, u16 *image) {
    s16 y;
    s16 x;

    gDPSetColorImage((*gfx)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, image);
    for (y = 0; y < 240; y += 16) {
        for (x = 0; x < 320; x += 64) {
            func_800341D0_main(gfx, &((u16 *)0x02000000)[x + y * 320], G_IM_FMT_RGBA, G_IM_SIZ_16b,
                               320, 240, 0, 0, 64, 16, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            gSPTextureRectangle((*gfx)++, x * 4, y * 4, (x + 64) * 4, (y + 16) * 4,
                                G_TX_RENDERTILE, 0, 0, 1024, 1024);
        }
    }
    gDPSetColorImage((*gfx)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, (u16 *)0x02000000);
}

void WipeFrameStill(Gfx **gfx) {
    gSPDisplayList((*gfx)++, D_800A26D8_main);
    func_80062884_main(gfx, D_800D5550_main);
}

void func_80062884_main(Gfx **gfx, u16 *image) {
    s16 y;
    s16 x;

    for (y = 0; y < 240; y += 16) {
        for (x = 0; x < 320; x += 64) {
            func_800341D0_main(gfx, &image[x + y * 320], G_IM_FMT_RGBA, G_IM_SIZ_16b,
                               320, 240, 0, 0, 64, 16, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            gSPTextureRectangle((*gfx)++, x * 4, y * 4, (x + 64) * 4, (y + 16) * 4,
                                G_TX_RENDERTILE, 0, 0, 1024, 1024);
        }
    }
}

s32 func_80062A30_main(Gfx **gfx) {
    s16 y;
    s16 x;
    f32 scale;
    f32 inverseScale;
    u16 *image;

    if (wipeTime >= wipeDuration - 1.0f) {
        WipeColorFill(gfx, 255, D_800A2728_main);
        return 0;
    }
    scale = 1.0f - wipeTime / wipeDuration;
    inverseScale = 1.0f / scale;
    gSPDisplayList((*gfx)++, D_800A26D8_main);
    gDPSetAlphaCompare((*gfx)++, G_AC_THRESHOLD);
    gDPSetBlendColor((*gfx)++, 0, 0, 0, 0);
    gDPSetTextureFilter((*gfx)++, G_TF_BILERP);
    gDPSetScissor((*gfx)++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    image = currFrameBuffer;
    gDPSetColorImage((*gfx)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, (u16 *)0x003D0800);
    gSPDisplayList((*gfx)++, D_800A2738_main);
    gDPSetCombineMode((*gfx)++, G_CC_DECALRGB, G_CC_DECALRGB);
    gDPSetRenderMode((*gfx)++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    for (y = 0; y < 240; y += 16) {
        for (x = 0; x < 320; x += 64) {
            func_800341D0_main(gfx, &image[x + y * 320], G_IM_FMT_RGBA, G_IM_SIZ_16b,
                               320, 240, 0, 0, 64, 16, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            gSPTextureRectangle((*gfx)++, x * scale * 4, y * scale * 4,
                                (x * scale + scale * 64) * 4, (y * scale + scale * 16) * 4,
                                G_TX_RENDERTILE, 0, 0, inverseScale * 1024, inverseScale * 1024);
        }
    }
    gDPSetColorImage((*gfx)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, (u16 *)0x02000000);
    image = (u16 *)0x803D0800;
    for (y = 0; y < scale * 240 + 15; y += 16) {
        for (x = 0; x < scale * 320 + 31; x += 32) {
            func_800341D0_main(gfx, &image[x + y * 320], G_IM_FMT_RGBA, G_IM_SIZ_16b,
                               320, 240, 0, 0, 32, 16, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            gSPTextureRectangle((*gfx)++, x * inverseScale * 4, y * inverseScale * 4,
                                (x + 32) * inverseScale * 4, (y + 16) * inverseScale * 4,
                                G_TX_RENDERTILE, 0, 0, scale * 1024, scale * 1024);
        }
    }
    gDPPipeSync((*gfx)++);
    gDPSetCombineMode((*gfx)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetRenderMode((*gfx)++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor((*gfx)++, 0, 0, 0, 0, 0, 8);
    gDPFillRectangle((*gfx)++, 0, 0, 320, 240);
    return 1;
}

s32 func_80063454_main(Gfx **gfx) {
    if (wipeDuration == 0.0f) {
        return 0;
    }
    if (wipeTime == 0.0f) {
        func_800635F4_main(13);
    }
    func_800636D8_main(gfx, wipeTime / wipeDuration, 1.0f);
    if (wipeTime >= wipeDuration) {
        return 0;
    }
    return 1;
}

s32 func_80063510_main(Gfx **gfx) {
    f32 scale;

    if (wipeDuration == 0.0f) {
        return 0;
    }
    if (wipeTime == 0.0f) {
        func_800635F4_main(13);
    }
    scale = wipeTime / wipeDuration;
    scale = 1.0f - scale;
    scale *= 1.1f;
    func_800636D8_main(gfx, scale, 1.0f);
    if (wipeTime >= wipeDuration) {
        return 0;
    }
    return 1;
}

u8 *func_800635F4_main(s32 file) {
    u8 *data;
    WipeTextureHeader *header;

    data = DataRead(file);
    header = (WipeTextureHeader *)(data + (data[2] << 8) + data[3]);
    D_800D1F5C_main.width = (header->width[0] << 8) + header->width[1];
    D_800D1F5C_main.height = (header->height[0] << 8) + header->height[1];
    header = (WipeTextureHeader *)(data + (header->offset[0] << 8) + header->offset[1]);
    D_800D1F5C_main.pixels = WipeMalloc(D_800D1F5C_main.width * D_800D1F5C_main.height);
    bcopy(header, D_800D1F5C_main.pixels, D_800D1F5C_main.width * D_800D1F5C_main.height);
    DataClose(data);
    return data;
}

void func_800636D8_main(Gfx **gfx, f32 scale, f32 alpha) {
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
    f32 radius;

    if (scale == 0.0f) {
        WipeColorFill(gfx, 255, D_800A2728_main);
        return;
    }
    gSPDisplayList((*gfx)++, D_800A26D8_main);
    gDPSetAlphaCompare((*gfx)++, G_AC_THRESHOLD);
    gDPSetBlendColor((*gfx)++, 0, 0, 0, 1);
    gDPSetScissor((*gfx)++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gDPSetTextureFilter((*gfx)++, G_TF_BILERP);
    gDPSetRenderMode((*gfx)++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetCombineLERP((*gfx)++, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0,
                      0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0);
    gDPLoadTextureBlock((*gfx)++, D_800D1F5C_main.pixels, G_IM_FMT_I, G_IM_SIZ_8b,
                        D_800D1F5C_main.width, D_800D1F5C_main.height,
                        0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
    gDPSetPrimColor((*gfx)++, 0, 0, D_800CDA74_main, D_800D0598_main, D_800D212E_main, alpha * 255.0f);
    radius = scale * 160.0f;
    left = 160.0f - radius;
    top = 120.0f - radius;
    right = radius + 160.0f;
    bottom = radius + 120.0f;
    scale = ((f32)right - (f32)left) / D_800D1F5C_main.width;
    gSPScisTextureRectangle((*gfx)++, left * 4, top * 4, right * 4, bottom * 4,
                            G_TX_RENDERTILE, 0, 0, (1.0f / scale) * 1024,
                            (1.0f / scale) * 1024);
    gDPSetRenderMode((*gfx)++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetCombineMode((*gfx)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor((*gfx)++, 0, 0, D_800CDA74_main, D_800D0598_main, D_800D212E_main, alpha * 255.0f);
    if (top > 0) {
        gDPScisFillRectangle((*gfx)++, 0, 0, 320, top);
    } else {
        top = 0;
    }
    if (bottom < 240) {
        gDPScisFillRectangle((*gfx)++, 0, bottom, 320, 240);
    } else {
        bottom = 240;
    }
    if (left > 0) {
        gDPScisFillRectangle((*gfx)++, 0, top, left, bottom);
    }
    if (right < 320) {
        gDPScisFillRectangle((*gfx)++, right, top, 320, bottom);
    }
}

s32 func_800640EC_main(Gfx **gfx) {
    if (wipeDuration == 0.0f) {
        return 0;
    }
    if (wipeTime == 0.0f && D_800D1F60_main == NULL) {
        func_800635F4_main(23);
    }
    func_800641C8_main(gfx, 1.0f - (1.0f / wipeDuration) * wipeTime);
    if (wipeTime >= wipeDuration) {
        return 0;
    }
    return 1;
}

void func_800641C8_main(Gfx **gfx, f32 progress) {
    s16 i;
    f32 alpha;
    f32 tileAlpha;

    gSPDisplayList((*gfx)++, D_800A26D8_main);
    gDPSetAlphaCompare((*gfx)++, G_AC_THRESHOLD);
    gDPSetBlendColor((*gfx)++, 0, 0, 0, 1);
    gDPLoadTextureTile_4b((*gfx)++, D_800D1F5C_main.pixels, G_IM_FMT_I,
                          D_800D1F5C_main.width, D_800D1F5C_main.height,
                          0, 0, D_800D1F5C_main.width, D_800D1F5C_main.height,
                          0, G_TX_WRAP, G_TX_WRAP,
                          HMF_TEXTURE_MASK(D_800D1F5C_main.width), HMF_TEXTURE_MASK(D_800D1F5C_main.height), 0, 0);
    gDPSetRenderMode((*gfx)++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetCombineLERP((*gfx)++, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0,
                      0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0);
    alpha = progress * 1.2f * 255.0f - 51.0f;
    if (alpha > 255.0f) {
        alpha = 255.0f;
    }
    for (i = 0; i < 6; i++) {
        tileAlpha = alpha;
        if (tileAlpha < 0.0f) {
            tileAlpha = 0.0f;
        }
        gDPSetPrimColor((*gfx)++, 0, 0, D_800CDA74_main, D_800D0598_main, D_800D212E_main, tileAlpha);
        alpha += 8.0f;
        if (alpha > 255.0f) {
            alpha = 255.0f;
        }
        if (alpha <= 0.0f) {
            continue;
        }
        if (i == 0) {
            gSPScisTextureRectangle((*gfx)++, 144 * 4, 104 * 4, 176 * 4, 136 * 4,
                                    G_TX_RENDERTILE, 0, 0, 1024, 1024);
        } else {
            if (i < 5) {
                gSPScisTextureRectangle((*gfx)++, (144 - i * 32) * 4, (104 - i * 32) * 4,
                                        (176 + i * 32) * 4, (136 - i * 32) * 4,
                                        G_TX_RENDERTILE, 0, 0, 1024, 1024);
                gSPScisTextureRectangle((*gfx)++, (144 - i * 32) * 4, (104 + i * 32) * 4,
                                        (176 + i * 32) * 4, (136 + i * 32) * 4,
                                        G_TX_RENDERTILE, 0, 0, 1024, 1024);
            }
            gSPScisTextureRectangle((*gfx)++, (144 - i * 32) * 4, (136 - i * 32) * 4,
                                    (176 - i * 32) * 4, (104 + i * 32) * 4,
                                    G_TX_RENDERTILE, 0, 0, 1024, 1024);
            gSPScisTextureRectangle((*gfx)++, (144 + i * 32) * 4, (136 - i * 32) * 4,
                                    (176 + i * 32) * 4, (104 + i * 32) * 4,
                                    G_TX_RENDERTILE, 0, 0, 1024, 1024);
        }
    }
    gDPPipeSync((*gfx)++);
    gDPSetCombineMode((*gfx)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    alpha = progress * 1.4f * 255.0f - 102.0f;
    if (alpha > 255.0f) {
        alpha = 255.0f;
    }
    for (i = 0; i < 6; i++) {
        tileAlpha = alpha;
        if (tileAlpha < 0.0f) {
            tileAlpha = 0.0f;
        }
        gDPSetPrimColor((*gfx)++, 0, 0, D_800CDA74_main, D_800D0598_main, D_800D212E_main, tileAlpha);
        alpha += 16.0f;
        if (alpha > 255.0f) {
            alpha = 255.0f;
        }
        if (alpha <= 0.0f) {
            continue;
        }
        if (i == 0) {
            gDPScisFillRectangle((*gfx)++, 144, 104, 176, 136);
        } else {
            if (i < 5) {
                gDPScisFillRectangle((*gfx)++, 144 - i * 32, 104 - i * 32, 176 + i * 32, 136 - i * 32);
                gDPScisFillRectangle((*gfx)++, 144 - i * 32, 104 + i * 32, 176 + i * 32, 136 + i * 32);
            }
            gDPScisFillRectangle((*gfx)++, 144 - i * 32, 136 - i * 32, 176 - i * 32, 104 + i * 32);
            gDPScisFillRectangle((*gfx)++, 144 + i * 32, 136 - i * 32, 176 + i * 32, 104 + i * 32);
        }
    }
}

s32 func_80065094_main(Gfx **gfx) {
    if (wipeDuration == 0.0f) {
        return 0;
    }
    if (wipeTime == 0.0f) {
        func_800635F4_main(23);
    }
    func_800641C8_main(gfx, (1.0f / wipeDuration) * wipeTime);
    if (wipeTime >= wipeDuration) {
        return 0;
    }
    return 1;
}

s32 func_8006515C_main(Gfx **gfx) {
    if (wipeDuration == 0.0f) {
        return 0;
    }
    func_800651F0_main(gfx, 1.0f - (1.0f / wipeDuration) * wipeTime);
    if (wipeTime >= wipeDuration) {
        return 0;
    }
    return 1;
}

void func_800651F0_main(Gfx **gfx, f32 progress) {
    s16 i;
    s16 center;
    s16 row;
    f32 alpha;
    f32 halfHeight;
    f32 stripeHeight;
    s32 textureTop;

    if (progress == 0.0f) {
        return;
    }
    gSPDisplayList((*gfx)++, D_800A26D8_main);
    gDPSetAlphaCompare((*gfx)++, G_AC_THRESHOLD);
    gDPSetBlendColor((*gfx)++, 0, 0, 0, 1);
    alpha = (progress + 0.2f) * 255.0f;
    if (alpha > 255.0f) {
        alpha = 255.0f;
    }
    for (i = 0; i < 10; i++) {
        stripeHeight = 24.0f;
        halfHeight = progress * stripeHeight / 2.0f;
        center = i * stripeHeight + 12.0f;
        gDPPipeSync((*gfx)++);
        if (alpha == 255.0f) {
            gDPSetRenderMode((*gfx)++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
        } else {
            gDPSetRenderMode((*gfx)++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
        }
        gDPSetCombineMode((*gfx)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetPrimColor((*gfx)++, 0, 0, 0, 0, 0, alpha);
        gDPFillRectangle((*gfx)++, 0, center - halfHeight, 320, center + halfHeight);
        if (D_800D1F5C_main.pixels != NULL) {
            textureTop = (240 - D_800D1F5C_main.height) / 2;
            if (textureTop > i * stripeHeight || i * stripeHeight >= D_800D1F5C_main.height + textureTop) {
                continue;
            }
            row = i * stripeHeight - textureTop;
            gDPPipeSync((*gfx)++);
            gDPSetRenderMode((*gfx)++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
            gDPSetCombineLERP((*gfx)++, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0,
                              0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0);
            gDPSetPrimColor((*gfx)++, 0, 0, 255, 255, 255, alpha);
            gDPLoadTextureTile_4b((*gfx)++, &D_800D1F5C_main.pixels[(u32)(row * D_800D1F5C_main.width) / 2],
                                  G_IM_FMT_I, D_800D1F5C_main.width, D_800D1F5C_main.height,
                                  0, 0, D_800D1F5C_main.width, 24, 0, G_TX_CLAMP, G_TX_CLAMP,
                                  HMF_TEXTURE_MASK(D_800D1F5C_main.width), HMF_TEXTURE_MASK(D_800D1F5C_main.height), 0, 0);
            gSPScisTextureRectangle((*gfx)++, (160 - D_800D1F5C_main.width / 2) * 4,
                                    (center - halfHeight) * 4.0f, (D_800D1F5C_main.width / 2 + 160) * 4,
                                    (center + halfHeight) * 4.0f, G_TX_RENDERTILE, 0, 0,
                                    1024, (1.0f / progress) * 1024.0f);
        }
    }
}

s32 WipeImageOut(Gfx **gfx, s32 file) {
    if (wipeDuration == 0.0f) {
        return 0;
    }
    if (wipeTime == 0.0f) {
        if (file != 0) {
            func_800635F4_main(file);
        } else {
            D_800D1F60_main = NULL;
        }
    }
    func_800651F0_main(gfx, (1.0f / wipeDuration) * wipeTime);
    if (wipeTime >= wipeDuration) {
        return 0;
    }
    return 1;
}

s32 func_80065D80_main(Gfx **gfx) {
    f32 scale;
    f32 alpha;

    if (wipeDuration == 0.0f) {
        return 0;
    }
    if (wipeTime == 0.0f) {
        func_800635F4_main(24);
    }
    scale = (wipeTime / wipeDuration) * 2.0f;
    if (wipeTime > wipeDuration * 0.5f) {
        alpha = 1.0f - (wipeTime - wipeDuration * 0.5f) / (wipeDuration * 0.5f);
    } else {
        alpha = 1.0f;
    }
    func_800636D8_main(gfx, scale, alpha);
    if (wipeTime >= wipeDuration) {
        return 0;
    }
    return 1;
}

s32 func_80065E88_main(Gfx **gfx) {
    f32 scale;
    f32 alpha;

    if (wipeDuration == 0.0f) {
        return 0;
    }
    if (wipeTime == 0.0f) {
        func_800635F4_main(24);
    }
    scale = (1.0f - wipeTime / wipeDuration) * 2.0f;
    if (wipeTime < wipeDuration * 0.5f) {
        alpha = wipeTime / (wipeDuration * 0.5f);
    } else {
        alpha = 1.0f;
    }
    func_800636D8_main(gfx, scale, alpha);
    if (wipeTime >= wipeDuration) {
        return 0;
    }
    return 1;
}

void func_80065F8C_main(void) {
    Gfx *gfx;

    D_800BDA70_main = HuMemAlloc(320 * 240 * sizeof(u16) + 64);
    D_800BDA7C_main = HuMemAlloc(0x1900);
    gfx = D_800BDA7C_main;
    D_800BDA74_main = (u16 *)(((u32)D_800BDA70_main + 63) & ~63);
    D_800BDA80_main = Hu3DHookFuncCreate(0, func_8006619C_main, 6);
    gSPDisplayList(gfx++, D_800A26D8_main);
    func_8006265C_main(&gfx, D_800BDA74_main);
    gSPEndDisplayList(gfx);
    D_800BDA78_main = 0;
}

s32 func_80066048_main(void) {
    if (D_800BDA78_main < 3) {
        return 0;
    }
    func_80019C00_main(D_800BDA7C_main);
    Hu3DModelKill(D_800BDA80_main);
    return 1;
}

void func_8006608C_main(void) {
    Gfx *gfx;

    D_800BDA7C_main = HuMemAlloc(0x1900);
    gfx = D_800BDA7C_main;
    D_800BDA82_main = Hu3DHookFuncCreate(0, func_800661D4_main, 0);
    gSPDisplayList(gfx++, D_800A26D8_main);
    gDPSetCombineMode(gfx++, G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM);
    gDPSetRenderMode(gfx++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 128);
    func_80062884_main(&gfx, D_800BDA74_main);
    gSPEndDisplayList(gfx);
}

void func_80066164_main(void) {
    func_80019C00_main(D_800BDA7C_main);
    func_80019C00_main(D_800BDA70_main);
    Hu3DModelKill(D_800BDA82_main);
}

void func_8006619C_main(Gfx **arg0, s32 arg1, s32 arg2) {
    gSPDisplayList((*arg0)++, D_800BDA7C_main);
    D_800BDA78_main++;
}

void func_800661D4_main(Gfx **arg0, s32 arg1, s32 arg2) {
    gSPDisplayList((*arg0)++, D_800BDA7C_main);
}

void func_800661F8_main(void) {
    D_800BDA70_main = D_800A26D4_main;
    D_800BDA74_main = D_800D5550_main;
    D_800D5304_main = 1;
}

void func_80066228_main(void) {
    func_80019C00_main(D_800BDA7C_main);
    HuMemMemoryFreePerm(D_800BDA70_main);
    Hu3DModelKill(D_800BDA82_main);
    D_800D5304_main = 0;
}
