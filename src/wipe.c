#include "game/wipe.h"
#include "include_asm.h"
#include "common.h"
#include "malloc.h"
#include "mallocblock.h"
#include "game/hmfman.h"

extern u8 D_800A26D0_main;
extern u16 *D_800A26D4_main;
extern u16 *D_800BDA70_main;
extern u16 *D_800BDA74_main;
extern u8 D_800BDA78_main;
extern Gfx *D_800BDA7C_main;
extern s16 D_800BDA80_main;
extern s16 D_800BDA82_main;
extern u8 D_800CC0BA_main;
extern u8 D_800CCF84_main;
extern u8 D_800CDA74_main;
extern f32 D_800D0A3C_main;
extern u8 D_800D0598_main;
extern u8 *D_800D1F80_main[8];
extern f32 D_800D51F4_main;
extern u8 D_800D5304_main;
extern u8 D_800D212E_main;
extern u16 *D_800D5550_main;
extern Gfx D_800A26D8_main[];
extern Gfx D_800A2728_main[];
extern u8 *D_800D1F60_main;

void func_8006231C_main(Gfx **gfx, u8 alpha, Gfx *displayList);
void func_8006265C_main(Gfx **gfx, u16 *image);
void func_800341D0_main(Gfx **gfx, u16 *image, s32 fmt, s32 siz, s32 width, s32 height,
                        s32 uls, s32 ult, s32 lrs, s32 lrt, s32 pal, s32 cms, s32 cmt,
                        s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void func_80062884_main(Gfx **gfx, u16 *image);
u8 *func_800635F4_main(s32 file);
void func_800636D8_main(Gfx **gfx, f32 scale, f32 alpha);
void func_800641C8_main(Gfx **gfx, f32 progress);
void func_800651F0_main(Gfx **gfx, f32 progress);
void func_8006619C_main(Gfx **gfx, s32 arg1, s32 arg2);
void func_800661D4_main(Gfx **gfx, s32 arg1, s32 arg2);

void WipeInit(void) {
    s16 i;

    D_800CCF84_main = 0;
    D_800CC0BA_main = 0;
    D_800D212E_main = 0;
    D_800D0598_main = 0;
    D_800CDA74_main = 0;
    D_800D5304_main = 0;
    for (i = 0; i < 8; i++) {
        D_800D1F80_main[i] = NULL;
    }
    func_8003661C_main();
}

INCLUDE_ASM("asm/nonmatchings/wipe", WipeExecAlways);

void WipeCreateIn(s16 arg0, s16 arg1) {
    if (D_800CCF84_main == 0) {
        D_800CC0BA_main = 1;
        D_800CCF84_main = 1;
        if (arg0 != 0xFF) {
            D_800A26D0_main = arg0;
        }
        D_800D0A3C_main = arg1;
        D_800D51F4_main = 0.0f;
    }
}

void WipeCreateOut(s16 arg0, s16 arg1) {
    if (D_800CCF84_main == 0) {
        D_800CC0BA_main = 2;
        D_800CCF84_main = 1;
        if (arg0 != 0xFF) {
            D_800A26D0_main = arg0;
        }
        D_800D0A3C_main = arg1;
        D_800D51F4_main = 0.0f;
    }
}

s32 WipeStatGet(void) {
    return D_800CCF84_main;
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

s32 func_80062168_main(Gfx **gfx) {
    if (D_800D0A3C_main == 0.0f) {
        return 0;
    }
    func_8006231C_main(gfx, 255.0f - (D_800D51F4_main / D_800D0A3C_main) * 255.0f, D_800A2728_main);
    if (D_800D51F4_main >= D_800D0A3C_main) {
        return 0;
    }
    return 1;
}

s32 func_80062244_main(Gfx **gfx) {
    if (D_800D0A3C_main == 0.0f) {
        return 0;
    }
    func_8006231C_main(gfx, (D_800D51F4_main / D_800D0A3C_main) * 255.0f, D_800A2728_main);
    if (D_800D51F4_main >= D_800D0A3C_main) {
        return 0;
    }
    return 1;
}

void func_8006231C_main(Gfx **gfx, u8 alpha, Gfx *displayList) {
    gSPDisplayList((*gfx)++, D_800A26D8_main);
    gDPSetRenderMode((*gfx)++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetCombineMode((*gfx)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor((*gfx)++, 0, 0, D_800CDA74_main, D_800D0598_main, D_800D212E_main, alpha);
    gDPFillRectangle((*gfx)++, 0, 0, 320, 240);
}

INCLUDE_ASM("asm/nonmatchings/wipe", func_800623F0_main);

s32 func_80062584_main(Gfx **gfx) {
    gSPDisplayList((*gfx)++, D_800A26D8_main);
    if (D_800D51F4_main == 0.0f) {
        D_800A26D4_main = HuMemMemoryAllocPerm(320 * 240 * sizeof(u16) + 64);
        D_800D5550_main = (u16 *)(((u32)D_800A26D4_main + 63) & ~63);
        func_8006265C_main(gfx, D_800D5550_main);
        return 1;
    }
    func_80062884_main(gfx, D_800D5550_main);
    if (D_800D51F4_main > 1.0f) {
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

void func_80062844_main(Gfx **gfx) {
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

INCLUDE_ASM("asm/nonmatchings/wipe", func_80062A30_main);

s32 func_80063454_main(Gfx **gfx) {
    if (D_800D0A3C_main == 0.0f) {
        return 0;
    }
    if (D_800D51F4_main == 0.0f) {
        func_800635F4_main(13);
    }
    func_800636D8_main(gfx, D_800D51F4_main / D_800D0A3C_main, 1.0f);
    if (D_800D51F4_main >= D_800D0A3C_main) {
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/wipe", func_80063510_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_800635F4_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_800636D8_main);

s32 func_800640EC_main(Gfx **gfx) {
    if (D_800D0A3C_main == 0.0f) {
        return 0;
    }
    if (D_800D51F4_main == 0.0f && D_800D1F60_main == NULL) {
        func_800635F4_main(23);
    }
    func_800641C8_main(gfx, 1.0f - (1.0f / D_800D0A3C_main) * D_800D51F4_main);
    if (D_800D51F4_main >= D_800D0A3C_main) {
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/wipe", func_800641C8_main);

s32 func_80065094_main(Gfx **gfx) {
    if (D_800D0A3C_main == 0.0f) {
        return 0;
    }
    if (D_800D51F4_main == 0.0f) {
        func_800635F4_main(23);
    }
    func_800641C8_main(gfx, (1.0f / D_800D0A3C_main) * D_800D51F4_main);
    if (D_800D51F4_main >= D_800D0A3C_main) {
        return 0;
    }
    return 1;
}

s32 func_8006515C_main(Gfx **gfx) {
    if (D_800D0A3C_main == 0.0f) {
        return 0;
    }
    func_800651F0_main(gfx, 1.0f - (1.0f / D_800D0A3C_main) * D_800D51F4_main);
    if (D_800D51F4_main >= D_800D0A3C_main) {
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/wipe", func_800651F0_main);

s32 func_80065C9C_main(Gfx **gfx, s32 file) {
    if (D_800D0A3C_main == 0.0f) {
        return 0;
    }
    if (D_800D51F4_main == 0.0f) {
        if (file != 0) {
            func_800635F4_main(file);
        } else {
            D_800D1F60_main = NULL;
        }
    }
    func_800651F0_main(gfx, (1.0f / D_800D0A3C_main) * D_800D51F4_main);
    if (D_800D51F4_main >= D_800D0A3C_main) {
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/wipe", func_80065D80_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_80065E88_main);

void func_80065F8C_main(void) {
    Gfx *gfx;

    D_800BDA70_main = HuMemAlloc(320 * 240 * sizeof(u16) + 64);
    D_800BDA7C_main = HuMemAlloc(0x1900);
    gfx = D_800BDA7C_main;
    D_800BDA74_main = (u16 *)(((u32)D_800BDA70_main + 63) & ~63);
    D_800BDA80_main = func_8001AC8C_main(0, func_8006619C_main, 6);
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
    func_8001ACDC_main(D_800BDA80_main);
    return 1;
}

void func_8006608C_main(void) {
    Gfx *gfx;

    D_800BDA7C_main = HuMemAlloc(0x1900);
    gfx = D_800BDA7C_main;
    D_800BDA82_main = func_8001AC8C_main(0, func_800661D4_main, 0);
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
    func_8001ACDC_main(D_800BDA82_main);
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
    func_8001ACDC_main(D_800BDA82_main);
    D_800D5304_main = 0;
}
