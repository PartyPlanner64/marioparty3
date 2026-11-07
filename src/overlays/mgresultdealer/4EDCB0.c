#include "common.h"

typedef struct {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02[3];
    /* 0x08 */ u16 unk_08[3];
} UnkDealerSprGroup; // Size 0xE

typedef struct {
    /* 0x00 */ UnkDealerSprGroup groups[3];
    /* 0x2A */ u16 unk_2A;
    /* 0x2C */ u16 unk_2C;
} UnkDealerSprites;

typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ omObjFunc objFunc;
} UnkDealerFadeProc;

extern s8 D_80109911_mgresultdealer;
extern s8 D_80109930_mgresultdealer;
extern s8 D_80109931_mgresultdealer;
extern s32 D_80109934_mgresultdealer;
extern s8 D_80109938_mgresultdealer;
extern s16 D_8010993A_mgresultdealer;
extern s8 D_80109940_mgresultdealer;
extern s8 D_80109941_mgresultdealer;
extern s32 D_80109944_mgresultdealer;
extern s32 D_80109948_mgresultdealer;
extern s32 D_80109950_mgresultdealer;
extern s16 D_8010A200_mgresultdealer;
extern s32 D_8010A204_mgresultdealer;
extern HuSprite *D_8010A208_mgresultdealer;
extern u8 *D_8010A20C_mgresultdealer;
extern UnkDealerSprites D_8010A210_mgresultdealer;
extern s32 D_8010A240_mgresultdealer;
extern s32 D_8010A244_mgresultdealer;
extern s16 D_8010A258_mgresultdealer;
extern omObjFunc D_8010A260_mgresultdealer;
extern s16 D_8010A264_mgresultdealer;
extern UnkDealerFadeProc D_8010A26C_mgresultdealer;

void func_80108194_mgresultdealer(omObjData *);
void func_80108258_mgresultdealer(void);
void func_801082A8_mgresultdealer(Gfx **, s32, s32);
void func_80108544_mgresultdealer(void);
void func_80108560_mgresultdealer(u8);
void func_80108BD4_mgresultdealer(omObjData *);
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

void func_80108040_mgresultdealer(void) {
    omObjData *obj;
    s16 sprite;
    s16 group;

    obj = omAddObj(0x14, 1, 0, -1, NULL);
    D_8010A26C_mgresultdealer.obj = obj;
    sprite = func_8000B838_main(0x190001);
    D_8010A204_mgresultdealer = sprite;
    group = HuSprGrpCreate(1, 0);
    HuSprAttrSet(group, 0, 0x8000);
    HuSprGrpMemberSet(group, 0, sprite, 0);
    D_8010A208_mgresultdealer = HuSprGet(group, 0);
    D_8010A20C_mgresultdealer = D_8010A208_mgresultdealer->unk_84->unk00->unk00;
    D_8010A200_mgresultdealer = Hu3DHookFuncCreate(0, func_801082A8_mgresultdealer, 2);
    Hu3DModelCameraSet(D_8010A200_mgresultdealer, 1);
    D_80109930_mgresultdealer = 0;
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    omPrcSetDestructor(0, func_80108258_mgresultdealer);
    D_8010A26C_mgresultdealer.objFunc = func_80108194_mgresultdealer;
    while (TRUE) {
        D_8010A26C_mgresultdealer.objFunc(obj);
        HuPrcVSleep();
    }
}

void func_80108194_mgresultdealer(omObjData *obj) {
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

void func_80108AEC_mgresultdealer(void) {
    if (D_80109940_mgresultdealer == 0) {
        return;
    }

    D_80109948_mgresultdealer++;

    if (D_80109948_mgresultdealer < 0xF) {
        return;
    }

    D_80109948_mgresultdealer = 0;

    if (D_8010A264_mgresultdealer * D_8010A258_mgresultdealer == 0) {
        D_80109940_mgresultdealer = 0;
        D_80109941_mgresultdealer = 1;
        D_80109948_mgresultdealer = 0;
        D_8010A244_mgresultdealer = 0;
        D_8010A260_mgresultdealer = func_80109710_mgresultdealer;
    } else {
        espBankSet(D_8010A210_mgresultdealer.groups[0].unk_00, 0, 0);
        func_8000BDDC_main(D_8010A210_mgresultdealer.groups[0].unk_00, 1);
        espDispOn(D_8010A210_mgresultdealer.groups[0].unk_00);
        D_8010A260_mgresultdealer = func_80108BD4_mgresultdealer;
    }
}

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

void func_801093A0_mgresultdealer(void) {
    s8 i;

    espDispOff(D_8010A210_mgresultdealer.unk_2A);
    espDispOff(D_8010A210_mgresultdealer.unk_2C);
    espDispOff(D_8010A210_mgresultdealer.groups[0].unk_00);
    espDispOff(D_8010A210_mgresultdealer.groups[1].unk_00);
    espDispOff(D_8010A210_mgresultdealer.groups[2].unk_00);
    for (i = 0; i < 3; i++) {
        espDispOff(D_8010A210_mgresultdealer.groups[0].unk_08[i]);
        espDispOff(D_8010A210_mgresultdealer.groups[1].unk_08[i]);
        espDispOff(D_8010A210_mgresultdealer.groups[2].unk_08[i]);
    }
}

s8 func_80109478_mgresultdealer(void) {
    return D_80109941_mgresultdealer;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80109484_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80109710_mgresultdealer);
