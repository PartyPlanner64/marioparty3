#include "common.h"

extern s8 D_80109911_mgresultdealer;
extern s8 D_80109930_mgresultdealer;
extern s8 D_80109931_mgresultdealer;
extern s32 D_80109934_mgresultdealer;
extern s8 D_80109938_mgresultdealer;
extern s16 D_8010993A_mgresultdealer;
extern s8 D_80109940_mgresultdealer;
extern s8 D_80109941_mgresultdealer;
extern s32 D_80109944_mgresultdealer;
extern s32 D_80109950_mgresultdealer;
extern u8 *D_8010A20C_mgresultdealer;
extern s32 D_8010A240_mgresultdealer;
extern s32 D_8010A244_mgresultdealer;
extern omObjFunc D_8010A260_mgresultdealer;

void func_80108544_mgresultdealer(void);
void func_80108560_mgresultdealer(u8);
void func_80109100_mgresultdealer(void);
void func_80109710_mgresultdealer(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_801074A0_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80107888_mgresultdealer);

void func_80107E3C_mgresultdealer(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80107E44_mgresultdealer);

s8 func_80108034_mgresultdealer(void) {
    return D_80109911_mgresultdealer;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80108040_mgresultdealer);

void func_80108194_mgresultdealer(void) {
    f32 step;

    if (D_80109930_mgresultdealer) {
        step = 255.0f / 30;
        func_80108560_mgresultdealer(D_80109934_mgresultdealer * step);
        D_80109934_mgresultdealer++;
        if (D_80109934_mgresultdealer >= 30) {
            func_80108560_mgresultdealer(255);
            D_80109931_mgresultdealer = 1;
            D_80109930_mgresultdealer = 0;
        }
    }
}

void func_80108258_mgresultdealer(void) {
}

void func_80108260_mgresultdealer(void) {
    D_80109930_mgresultdealer = 1;
    D_80109931_mgresultdealer = 0;
    D_80109934_mgresultdealer = 0;
    func_80108544_mgresultdealer();
    func_80108560_mgresultdealer(0);
}

s8 func_8010829C_mgresultdealer(void) {
    return D_80109931_mgresultdealer;
}

void func_801082A8_mgresultdealer(Gfx **gfx, s32 arg1, s32 arg2) {
    Gfx *gdl;
    s32 alpha;
    s32 y;

    if (D_80109938_mgresultdealer) {
        alpha = D_8010993A_mgresultdealer;
        gdl = *gfx;
        gDPPipeSync(gdl++);
        gDPSetCycleType(gdl++, G_CYC_1CYCLE);
        gSPClearGeometryMode(gdl++, G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                        G_TEXTURE_GEN_LINEAR | G_LOD);
        gSPSetGeometryMode(gdl++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
        gDPSetTexturePersp(gdl++, G_TP_NONE);
        gDPSetPrimColor(gdl++, 0, 0, 0, 0, 0, alpha);
        gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(gdl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetTextureLUT(gdl++, G_TT_NONE);

        for (y = 0; y < 240; y += 10) {
            gDPLoadTextureTile_4b(gdl++, D_8010A20C_mgresultdealer, G_IM_FMT_I, 320, 240, 0, y, 319, y + 9, 0,
                                  G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                  G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTileSize(gdl++, G_TX_RENDERTILE, 0, 0, 320 << 2, 10 << 2);
            gSPTextureRectangle(gdl++, 0, y << 2, 320 << 2, (y + 10) << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
        }
        *gfx = gdl;
    }
}

void func_80108544_mgresultdealer(void) {
    D_80109938_mgresultdealer = 1;
}

void func_80108554_mgresultdealer(void) {
    D_80109938_mgresultdealer = 0;
}

void func_80108560_mgresultdealer(u8 arg0) {
    D_8010993A_mgresultdealer = arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80108570_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80108AEC_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80108BD4_mgresultdealer);

void func_80109044_mgresultdealer(void) {
    if (D_80109940_mgresultdealer == 0) {
        return;
    }

    D_80109950_mgresultdealer++;

    if (D_80109950_mgresultdealer < 0xF) {
        return;
    }

    D_80109940_mgresultdealer = 0;
    D_80109941_mgresultdealer = 1;
    D_80109950_mgresultdealer = 0;
    D_8010A244_mgresultdealer = 0;
    D_8010A260_mgresultdealer = func_80109710_mgresultdealer;
}

void func_801090AC_mgresultdealer(void) {
}

void func_801090B4_mgresultdealer(void) {
    D_80109940_mgresultdealer = 1;
    D_80109941_mgresultdealer = 0;
    D_80109944_mgresultdealer = 0;
    func_80109100_mgresultdealer();
}

s32 func_801090E8_mgresultdealer(void) {
    return D_8010A240_mgresultdealer;
}

s32 func_801090F4_mgresultdealer(void) {
    return D_8010A244_mgresultdealer;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80109100_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_801093A0_mgresultdealer);

s8 func_80109478_mgresultdealer(void) {
    return D_80109941_mgresultdealer;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80109484_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80109710_mgresultdealer);
