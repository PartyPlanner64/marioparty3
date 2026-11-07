#include "common.h"

typedef struct {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ s16 unk_02[3];
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

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ Vec unk_08;
    /* 0x14 */ f32 unk_14;
} UnkDealerCoin; // Size 0x18

extern s8 D_80109910_mgresultdealer;
extern s8 D_80109911_mgresultdealer;
extern s32 D_80109914_mgresultdealer;
extern s32 D_80109918_mgresultdealer;
extern s32 D_8010991C_mgresultdealer;
extern s32 D_80109920_mgresultdealer;
extern s32 D_80109924_mgresultdealer;
extern s32 D_80109928_mgresultdealer;
extern s32 D_8010992C_mgresultdealer;
extern s8 D_80109930_mgresultdealer;
extern s8 D_80109931_mgresultdealer;
extern s32 D_80109934_mgresultdealer;
extern s8 D_80109938_mgresultdealer;
extern s16 D_8010993A_mgresultdealer;
extern s8 D_80109940_mgresultdealer;
extern s8 D_80109941_mgresultdealer;
extern s32 D_80109944_mgresultdealer;
extern s32 D_80109948_mgresultdealer;
extern s32 D_8010994C_mgresultdealer;
extern s32 D_80109950_mgresultdealer;
extern s16 D_8010A200_mgresultdealer;
extern s32 D_8010A204_mgresultdealer;
extern HuSprite *D_8010A208_mgresultdealer;
extern u8 *D_8010A20C_mgresultdealer;
extern UnkDealerSprites D_8010A210_mgresultdealer;
extern s32 D_8010A240_mgresultdealer;
extern s32 D_8010A244_mgresultdealer;
extern s16 D_8010A258_mgresultdealer;
extern omObjData *D_8010A25C_mgresultdealer;
extern omObjFunc D_8010A260_mgresultdealer;
extern s16 D_8010A264_mgresultdealer;
extern UnkDealerFadeProc D_8010A26C_mgresultdealer;
extern u16 D_80109A70_mgresultdealer;
extern u16 D_80109A72_mgresultdealer;
extern UnkDealerCoin D_80109A78_mgresultdealer[40];
extern UnkDealerCoin D_80109E38_mgresultdealer[40];
extern omObjFunc D_8010A278_mgresultdealer;
extern omObjData *D_8010A274_mgresultdealer;
extern s8 D_8010A266_mgresultdealer[4];

void func_80107888_mgresultdealer(omObjData *);
void func_80107E3C_mgresultdealer(void);
void func_80108194_mgresultdealer(omObjData *);
void func_80108258_mgresultdealer(void);
void func_801082A8_mgresultdealer(Gfx **, s32, s32);
void func_80108544_mgresultdealer(void);
void func_80108560_mgresultdealer(u8);
void func_80108AEC_mgresultdealer(omObjData *);
void func_80108BD4_mgresultdealer(omObjData *);
void func_80109044_mgresultdealer(omObjData *arg0);
void func_801090AC_mgresultdealer(void);
void func_80109100_mgresultdealer(void);
void func_80109484_mgresultdealer(omObjData *);
void func_80109710_mgresultdealer(omObjData *);

void func_801074A0_mgresultdealer(void) {
    omObjData *obj;
    void *data;
    s8 i;

    obj = omAddObj(0x14, 0x51, 0, -1, NULL);
    D_8010A274_mgresultdealer = obj;

    data = DataRead(0x210026);
    D_80109A70_mgresultdealer = HmfSprModelCreate(data, 0x2BD, 8);
    DataClose(data);
    func_8001C2FC_main(D_800CBB60_main[D_80109A70_mgresultdealer].modelId, 0x70000000, 0x70000000);
    for (i = 0; i < 40; i++) {
        D_80109A78_mgresultdealer[i].unk_00 = 0;
        D_80109A78_mgresultdealer[i].unk_02 = func_80014618_main(D_80109A70_mgresultdealer, 8);
        D_80109A78_mgresultdealer[i].unk_04 = 0;
        obj->model[i + 1] = D_800CBB60_main[D_80109A78_mgresultdealer[i].unk_02].modelId;
        Hu3DModelPosSet(obj->model[i + 1], 0.0f, 400.0f, 0.0f);
        Hu3DModelCameraSet(obj->model[i + 1], 1);
        Hu3DMotionSpeedSet(obj->model[i + 1], 2.0f);
        Hu3DModelScaleSet(D_800CBB60_main[i + 1].modelId, 1.5f, 1.5f, 1.5f);
    }

    data = DataRead(0xC);
    D_80109A72_mgresultdealer = HmfSprModelCreate(data, 0x2BD, 8);
    DataClose(data);
    func_8001C2FC_main(D_800CBB60_main[D_80109A72_mgresultdealer].modelId, 0x70000000, 0x70000000);
    Hu3DModelScaleSet(D_800CBB60_main[D_80109A72_mgresultdealer].modelId, 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 40; i++) {
        D_80109E38_mgresultdealer[i].unk_00 = 0;
        D_80109E38_mgresultdealer[i].unk_02 = func_80014618_main(D_80109A72_mgresultdealer, 8);
        D_80109E38_mgresultdealer[i].unk_04 = 0;
        obj->model[i + 41] = D_800CBB60_main[D_80109E38_mgresultdealer[i].unk_02].modelId;
        Hu3DModelPosSet(obj->model[i + 41], 0.0f, 400.0f, 0.0f);
        Hu3DModelCameraSet(obj->model[i + 41], 1);
        Hu3DMotionSpeedSet(obj->model[i + 41], 1.0f);
        Hu3DModelScaleSet(D_800CBB60_main[i + 41].modelId, 3.0f, 3.0f, 3.0f);
    }

    obj->model[0] = -1;
    D_80109910_mgresultdealer = 0;
    D_80109911_mgresultdealer = 0;
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    omPrcSetDestructor(0, func_80107E3C_mgresultdealer);
    D_8010A278_mgresultdealer = func_80107888_mgresultdealer;
    while (TRUE) {
        D_8010A278_mgresultdealer(obj);
        HuPrcVSleep();
    }
}

void func_80107888_mgresultdealer(omObjData *obj) {
    HmfModelEntry *entry;
    HmfAnimSet *animSet;
    HmfAnimRot *rot;
    s8 i;
    s8 count;
    s32 max;
    s16 landed;
    s8 spawning;
    f32 x;
    f32 y;
    f32 z;

    if (D_80109910_mgresultdealer) {
        if ((spawning = D_8010991C_mgresultdealer < D_80109920_mgresultdealer) == TRUE) {
            count = 0;
            for (i = 0; i < 40; i++) {
                if (D_80109A78_mgresultdealer[i].unk_00 != 0) {
                    continue;
                }
                if (D_80109914_mgresultdealer % D_80109924_mgresultdealer != 0) {
                    continue;
                }
                entry = &D_800CBB60_main[D_80109A78_mgresultdealer[i].unk_02];
                animSet = &D_800D408C_main[(u16)entry->unk_02];
                rot = &animSet->rot[entry->pointIdx];
                func_8001C258_main(obj->model[i + 1], HU3D_ATTR_DISPOFF, 0);
                if (D_80109918_mgresultdealer >= 20) {
                    max = (rand8() & 1) + 1;
                } else {
                    max = 1;
                }
                Hu3DModelPosSet(obj->model[i + 1], 0.0f, 400.0f, 0.0f);
                D_80109A78_mgresultdealer[i].unk_08.x = (u8)(rand8() % 60) - 30;
                D_80109A78_mgresultdealer[i].unk_08.y = 400.0f;
                D_80109A78_mgresultdealer[i].unk_08.z = (u8)(rand8() % 60) - 30;
                D_80109A78_mgresultdealer[i].unk_00 = 1;
                D_80109A78_mgresultdealer[i].unk_14 = 0.98f;
                entry->nodeIdx = rand8() % rot->frameCount;
                entry->unk_08 = 0;
                D_8010991C_mgresultdealer++;
                if (D_8010991C_mgresultdealer >= D_80109920_mgresultdealer) {
                    break;
                }
                count++;
                if (count >= max) {
                    break;
                }
            }
        }

        landed = 0;
        for (i = 0; i < 40; i++) {
            if (D_80109A78_mgresultdealer[i].unk_00 != 1) {
                continue;
            }
            x = D_80109A78_mgresultdealer[i].unk_08.x;
            y = D_80109A78_mgresultdealer[i].unk_08.y;
            z = D_80109A78_mgresultdealer[i].unk_08.z;
            Hu3DModelPosSet(obj->model[i + 1], x, y, z);
            D_80109A78_mgresultdealer[i].unk_08.y -= D_80109A78_mgresultdealer[i].unk_14;
            D_80109A78_mgresultdealer[i].unk_14 += 0.98f;
            D_80109A78_mgresultdealer[i].unk_04++;
            if (y <= 152.5f) {
                D_80109A78_mgresultdealer[i].unk_00 = 0;
                func_8001C258_main(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                func_8001C258_main(obj->model[i + 41], HU3D_ATTR_DISPOFF, 0);
                Hu3DModelPosSet(obj->model[i + 41], x, y, z);
                Hu3DMotionTimeSet(obj->model[i + 41], 0);
                func_80014714_main(D_80109E38_mgresultdealer[i].unk_02, 0);
                HuAudFXPlay(9);
                if (D_8010992C_mgresultdealer == 0) {
                    if (!(GwPlayer[D_8010A266_mgresultdealer[0]].stat & 1)) {
                        omVibrate(D_8010A266_mgresultdealer[0], 5, 0, 5);
                    }
                    D_8010992C_mgresultdealer = 1;
                }
            }
            landed++;
        }

        if (landed == 0 && spawning != TRUE) {
            if (D_80109928_mgresultdealer == 0) {
                HuAudFXPlay(0x517);
                D_80109928_mgresultdealer = 1;
            }
            D_80109911_mgresultdealer = 1;
        }
        D_80109914_mgresultdealer++;
    }
}

void func_80107E3C_mgresultdealer(void) {
}

void func_80107E44_mgresultdealer(s32 count) {
    omObjData *obj = D_8010A274_mgresultdealer;
    s8 i;

    if (count > 0) {
        count = (count >= 1000) ? 999 : count;
        D_80109918_mgresultdealer = count;
        D_8010991C_mgresultdealer = 0;
        D_80109914_mgresultdealer = 0;
        if (count <= 50) {
            D_80109920_mgresultdealer = count;
        } else {
            D_80109920_mgresultdealer = 50;
        }
        if (count > 40) {
            D_80109924_mgresultdealer = 100 / (D_80109920_mgresultdealer + 1);
        } else if (count > 20) {
            D_80109924_mgresultdealer = 80 / (D_80109920_mgresultdealer + 1);
        } else {
            D_80109924_mgresultdealer = 60 / (D_80109920_mgresultdealer + 1);
        }
        for (i = 0; i < 40; i++) {
            D_80109A78_mgresultdealer[i].unk_00 = 0;
            D_80109A78_mgresultdealer[i].unk_04 = 0;
            D_80109A78_mgresultdealer[i].unk_08.x = D_80109A78_mgresultdealer[i].unk_08.y = D_80109A78_mgresultdealer[i].unk_08.z = 0.0f;
            D_80109A78_mgresultdealer[i].unk_14 = 0.98f;
            func_8001C258_main(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelPosSet(obj->model[i + 1], 0.0f, 400.0f, 0.0f);
        }
        D_80109910_mgresultdealer = 1;
        D_80109911_mgresultdealer = 0;
    }
}

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

void func_80108570_mgresultdealer(void) {
    omObjData *obj;
    s16 multSprite;
    s16 sprite;
    s16 x;
    s8 i;

    obj = omAddObj(0x14, 0, 0, -1, NULL);
    D_8010A25C_mgresultdealer = obj;

    D_8010A210_mgresultdealer.groups[0].unk_02[0] = (s16)(D_8010A264_mgresultdealer / 100) % 10;
    D_8010A210_mgresultdealer.groups[0].unk_02[1] = (s16)(D_8010A264_mgresultdealer / 10) % 10;
    D_8010A210_mgresultdealer.groups[0].unk_02[2] = D_8010A264_mgresultdealer % 10;
    D_8010A210_mgresultdealer.groups[1].unk_02[0] = (s16)(D_8010A258_mgresultdealer / 100) % 10;
    D_8010A210_mgresultdealer.groups[1].unk_02[1] = (s16)(D_8010A258_mgresultdealer / 10) % 10;
    D_8010A210_mgresultdealer.groups[1].unk_02[2] = D_8010A258_mgresultdealer % 10;
    D_8010A210_mgresultdealer.groups[2].unk_02[0] = 0;
    D_8010A210_mgresultdealer.groups[2].unk_02[1] = 0;
    D_8010A210_mgresultdealer.groups[2].unk_02[2] = 0;

    sprite = func_8000B838_main(0x190005);
    D_8010A210_mgresultdealer.unk_2C = espEntry(sprite, 0, 1);
    espTPLvlSet(D_8010A210_mgresultdealer.unk_2C, 0x7F);
    espPosSet(D_8010A210_mgresultdealer.unk_2C, 0xA9, 0x60);
    espDispOff(D_8010A210_mgresultdealer.unk_2C);
    x = 0x5C;

    sprite = func_8000B838_main(0x190004);
    D_8010A210_mgresultdealer.unk_2A = espEntry(sprite, 0, 1);
    espPosSet(D_8010A210_mgresultdealer.unk_2A, 0xA3, 0x5A);
    espDispOff(D_8010A210_mgresultdealer.unk_2A);

    sprite = func_8000B838_main(0x190009);
    D_8010A210_mgresultdealer.groups[0].unk_00 = espEntry(sprite, 0, 1);
    espPosSet(D_8010A210_mgresultdealer.groups[0].unk_00, 0x4C, 0x5A);
    espBankSet(D_8010A210_mgresultdealer.groups[0].unk_00, 0, 0);
    espSpeedSet(D_8010A210_mgresultdealer.groups[0].unk_00, 2.0f);
    func_8000BDDC_main(D_8010A210_mgresultdealer.groups[0].unk_00, 0);
    espDispOff(D_8010A210_mgresultdealer.groups[0].unk_00);

    sprite = func_8000B838_main(0xC0086);
    for (i = 0; i < 3; i++) {
        D_8010A210_mgresultdealer.groups[0].unk_08[i] = espEntry(sprite, 0, 0);
        espPosSet(D_8010A210_mgresultdealer.groups[0].unk_08[i], x, 0x5A);
        espBankSet(D_8010A210_mgresultdealer.groups[0].unk_08[i], (u16)D_8010A210_mgresultdealer.groups[0].unk_02[i], 0);
        espDispOff(D_8010A210_mgresultdealer.groups[0].unk_08[i]);
        x += 16;
    }

    multSprite = func_8000B838_main(0xC008C);
    D_8010A210_mgresultdealer.groups[1].unk_00 = espEntry(multSprite, 0, 0);
    espPosSet(D_8010A210_mgresultdealer.groups[1].unk_00, x, 0x5A);
    espBankSet(D_8010A210_mgresultdealer.groups[1].unk_00, 0, 0);
    espDispOff(D_8010A210_mgresultdealer.groups[1].unk_00);
    x += 16;

    for (i = 0; i < 3; i++) {
        D_8010A210_mgresultdealer.groups[1].unk_08[i] = espEntry(sprite, 0, 0);
        espPosSet(D_8010A210_mgresultdealer.groups[1].unk_08[i], x, 0x5A);
        espBankSet(D_8010A210_mgresultdealer.groups[1].unk_08[i], (u16)D_8010A210_mgresultdealer.groups[1].unk_02[i], 0);
        espDispOff(D_8010A210_mgresultdealer.groups[1].unk_08[i]);
        x += 16;
    }

    D_8010A210_mgresultdealer.groups[2].unk_00 = espEntry(multSprite, 0, 0);
    espPosSet(D_8010A210_mgresultdealer.groups[2].unk_00, x, 0x5A);
    espBankSet(D_8010A210_mgresultdealer.groups[2].unk_00, 3, 0);
    espDispOff(D_8010A210_mgresultdealer.groups[2].unk_00);
    x += 16;

    for (i = 0; i < 3; i++) {
        D_8010A210_mgresultdealer.groups[2].unk_08[i] = espEntry(sprite, 0, 0);
        espPosSet(D_8010A210_mgresultdealer.groups[2].unk_08[i], x, 0x5A);
        espBankSet(D_8010A210_mgresultdealer.groups[2].unk_08[i], (u16)D_8010A210_mgresultdealer.groups[2].unk_02[i], 0);
        espDispOff(D_8010A210_mgresultdealer.groups[2].unk_08[i]);
        x += 16;
    }

    omPrcSetDestructor(0, func_801090AC_mgresultdealer);
    D_8010A260_mgresultdealer = func_80108AEC_mgresultdealer;
    while (TRUE) {
        D_8010A260_mgresultdealer(obj);
        HuPrcVSleep();
    }
}

void func_80108AEC_mgresultdealer(omObjData *arg0) {
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

void func_80108BD4_mgresultdealer(omObjData *arg0) {
    s32 total;
    s16 value;
    s8 i;

    if (D_80109940_mgresultdealer == 0) {
        return;
    }

    total = D_8010A264_mgresultdealer * D_8010A258_mgresultdealer;
    total = (total >= 1000) ? 999 : total;
    value = total / 28.0f * D_80109944_mgresultdealer;
    D_8010A210_mgresultdealer.groups[2].unk_02[0] = (s16)(value / 100) % 10;
    D_8010A210_mgresultdealer.groups[2].unk_02[1] = (s16)(value / 10) % 10;
    D_8010A210_mgresultdealer.groups[2].unk_02[2] = value % 10;
    for (i = 0; i < 3; i++) {
        func_8000BDDC_main(D_8010A210_mgresultdealer.groups[2].unk_08[i], 1);
        espBankSet(D_8010A210_mgresultdealer.groups[2].unk_08[i], (u16)D_8010A210_mgresultdealer.groups[2].unk_02[i], 0);
    }
    if (value < 10) {
        espDispOff(D_8010A210_mgresultdealer.groups[2].unk_08[0]);
        espDispOff(D_8010A210_mgresultdealer.groups[2].unk_08[1]);
    } else if (value < 100) {
        espDispOff(D_8010A210_mgresultdealer.groups[2].unk_08[0]);
        espDispOn(D_8010A210_mgresultdealer.groups[2].unk_08[1]);
    } else {
        espDispOn(D_8010A210_mgresultdealer.groups[2].unk_08[0]);
        espDispOn(D_8010A210_mgresultdealer.groups[2].unk_08[1]);
    }
    espDispOn(D_8010A210_mgresultdealer.groups[2].unk_08[2]);
    if (D_8010994C_mgresultdealer < value) {
        HuAudFXPlay(9);
        D_8010994C_mgresultdealer = value;
    }

    D_80109944_mgresultdealer++;
    if (D_80109944_mgresultdealer < 28) {
        return;
    }

    HuAudFXPlay(9);
    value = total;
    D_8010A210_mgresultdealer.groups[2].unk_02[0] = (s16)(value / 100) % 10;
    D_8010A210_mgresultdealer.groups[2].unk_02[1] = (s16)(value / 10) % 10;
    D_8010A210_mgresultdealer.groups[2].unk_02[2] = value % 10;
    for (i = 0; i < 3; i++) {
        func_8000BDDC_main(D_8010A210_mgresultdealer.groups[2].unk_08[i], 1);
        espBankSet(D_8010A210_mgresultdealer.groups[2].unk_08[i], (u16)D_8010A210_mgresultdealer.groups[2].unk_02[i], 0);
    }
    if (value < 10) {
        espDispOff(D_8010A210_mgresultdealer.groups[2].unk_08[0]);
        espDispOff(D_8010A210_mgresultdealer.groups[2].unk_08[1]);
    } else if (value < 100) {
        espDispOff(D_8010A210_mgresultdealer.groups[2].unk_08[0]);
        espDispOn(D_8010A210_mgresultdealer.groups[2].unk_08[1]);
    } else {
        espDispOn(D_8010A210_mgresultdealer.groups[2].unk_08[0]);
        espDispOn(D_8010A210_mgresultdealer.groups[2].unk_08[1]);
    }
    espDispOn(D_8010A210_mgresultdealer.groups[2].unk_08[2]);
    func_8000BDDC_main(D_8010A210_mgresultdealer.groups[0].unk_00, 0);
    D_8010994C_mgresultdealer = 0;
    D_8010A260_mgresultdealer = func_80109044_mgresultdealer;
}

void func_80109044_mgresultdealer(omObjData *arg0) {
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

void func_80109100_mgresultdealer(void) {
    s32 i;

    D_8010A240_mgresultdealer = 0;
    espDispOn(D_8010A210_mgresultdealer.unk_2A);
    espDispOn(D_8010A210_mgresultdealer.unk_2C);
    espDispOn(D_8010A210_mgresultdealer.groups[0].unk_00);
    espDispOn(D_8010A210_mgresultdealer.groups[1].unk_00);
    espDispOn(D_8010A210_mgresultdealer.groups[2].unk_00);
    if (D_8010A210_mgresultdealer.groups[0].unk_02[0] == 0) {
        espDispOff(D_8010A210_mgresultdealer.groups[0].unk_08[0]);
        if (D_8010A210_mgresultdealer.groups[0].unk_02[1] == 0) {
            espDispOff(D_8010A210_mgresultdealer.groups[0].unk_08[1]);
        } else {
            espDispOn(D_8010A210_mgresultdealer.groups[0].unk_08[1]);
        }
    } else {
        espDispOn(D_8010A210_mgresultdealer.groups[0].unk_08[0]);
        espDispOn(D_8010A210_mgresultdealer.groups[0].unk_08[1]);
    }
    espDispOn(D_8010A210_mgresultdealer.groups[0].unk_08[2]);
    if (D_8010A210_mgresultdealer.groups[1].unk_02[0] == 0) {
        espDispOff(D_8010A210_mgresultdealer.groups[1].unk_08[0]);
        if (D_8010A210_mgresultdealer.groups[1].unk_02[1] == 0) {
            espDispOff(D_8010A210_mgresultdealer.groups[1].unk_08[1]);
        } else {
            espDispOn(D_8010A210_mgresultdealer.groups[1].unk_08[1]);
        }
    } else {
        espDispOn(D_8010A210_mgresultdealer.groups[1].unk_08[0]);
        espDispOn(D_8010A210_mgresultdealer.groups[1].unk_08[1]);
    }
    espDispOn(D_8010A210_mgresultdealer.groups[1].unk_08[2]);
    if (D_8010A210_mgresultdealer.groups[2].unk_02[0] == 0) {
        espDispOff(D_8010A210_mgresultdealer.groups[2].unk_08[0]);
        if (D_8010A210_mgresultdealer.groups[2].unk_02[1] == 0) {
            espDispOff(D_8010A210_mgresultdealer.groups[2].unk_08[1]);
        } else {
            espDispOn(D_8010A210_mgresultdealer.groups[2].unk_08[1]);
        }
    } else {
        espDispOn(D_8010A210_mgresultdealer.groups[2].unk_08[0]);
        espDispOn(D_8010A210_mgresultdealer.groups[2].unk_08[1]);
    }
    espDispOn(D_8010A210_mgresultdealer.groups[2].unk_08[2]);
    espScaleSet(D_8010A210_mgresultdealer.unk_2A, 1.0f, 0.0f);
    espScaleSet(D_8010A210_mgresultdealer.unk_2C, 1.0f, 0.0f);
    espScaleSet(D_8010A210_mgresultdealer.groups[0].unk_00, 1.0f, 0.0f);
    espScaleSet(D_8010A210_mgresultdealer.groups[1].unk_00, 1.0f, 0.0f);
    espScaleSet(D_8010A210_mgresultdealer.groups[2].unk_00, 1.0f, 0.0f);
    for (i = 0; i < 3; i++) {
        espScaleSet(D_8010A210_mgresultdealer.groups[0].unk_08[i], 1.0f, 0.0f);
        espScaleSet(D_8010A210_mgresultdealer.groups[1].unk_08[i], 1.0f, 0.0f);
        espScaleSet(D_8010A210_mgresultdealer.groups[2].unk_08[i], 1.0f, 0.0f);
    }
    D_8010A260_mgresultdealer = func_80109484_mgresultdealer;
}

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

void func_80109484_mgresultdealer(omObjData *arg0) {
    f32 scale = 0.0f;
    s32 i;
    s32 j;

    for (i = 0; i < 10; i++) {
        espScaleSet(D_8010A210_mgresultdealer.unk_2A, 1.0f, scale);
        espScaleSet(D_8010A210_mgresultdealer.unk_2C, 1.0f, scale);
        espScaleSet(D_8010A210_mgresultdealer.groups[0].unk_00, 1.0f, scale);
        espScaleSet(D_8010A210_mgresultdealer.groups[1].unk_00, 1.0f, scale);
        espScaleSet(D_8010A210_mgresultdealer.groups[2].unk_00, 1.0f, scale);
        for (j = 0; j < 3; j++) {
            espScaleSet(D_8010A210_mgresultdealer.groups[0].unk_08[j], 1.0f, scale);
            espScaleSet(D_8010A210_mgresultdealer.groups[1].unk_08[j], 1.0f, scale);
            espScaleSet(D_8010A210_mgresultdealer.groups[2].unk_08[j], 1.0f, scale);
        }
        scale = sindf(i * 9.0f) * 1.1f;
        HuPrcVSleep();
    }
    espScaleSet(D_8010A210_mgresultdealer.unk_2A, 1.0f, 1.0f);
    espScaleSet(D_8010A210_mgresultdealer.unk_2C, 1.0f, 1.0f);
    espScaleSet(D_8010A210_mgresultdealer.groups[0].unk_00, 1.0f, 1.0f);
    espScaleSet(D_8010A210_mgresultdealer.groups[1].unk_00, 1.0f, 1.0f);
    espScaleSet(D_8010A210_mgresultdealer.groups[2].unk_00, 1.0f, 1.0f);
    for (j = 0; j < 3; j++) {
        espScaleSet(D_8010A210_mgresultdealer.groups[0].unk_08[j], 1.0f, 1.0f);
        espScaleSet(D_8010A210_mgresultdealer.groups[1].unk_08[j], 1.0f, 1.0f);
        espScaleSet(D_8010A210_mgresultdealer.groups[2].unk_08[j], 1.0f, 1.0f);
    }
    D_8010A240_mgresultdealer = 1;
    D_8010A260_mgresultdealer = func_80108AEC_mgresultdealer;
}

void func_80109710_mgresultdealer(omObjData *arg0) {
    f32 scale = 1.0f;
    s32 i;
    s32 j;

    for (i = 0; i < 5; i++) {
        espScaleSet(D_8010A210_mgresultdealer.unk_2A, 1.0f, scale);
        espScaleSet(D_8010A210_mgresultdealer.unk_2C, 1.0f, scale);
        espScaleSet(D_8010A210_mgresultdealer.groups[0].unk_00, 1.0f, scale);
        espScaleSet(D_8010A210_mgresultdealer.groups[1].unk_00, 1.0f, scale);
        espScaleSet(D_8010A210_mgresultdealer.groups[2].unk_00, 1.0f, scale);
        for (j = 0; j < 3; j++) {
            espScaleSet(D_8010A210_mgresultdealer.groups[0].unk_08[j], 1.0f, scale);
            espScaleSet(D_8010A210_mgresultdealer.groups[1].unk_08[j], 1.0f, scale);
            espScaleSet(D_8010A210_mgresultdealer.groups[2].unk_08[j], 1.0f, scale);
        }
        scale = cosdf(i * 18.0f);
        HuPrcVSleep();
    }
    func_801093A0_mgresultdealer();
    D_8010A244_mgresultdealer = 1;
    D_8010A260_mgresultdealer = func_80108AEC_mgresultdealer;
}
