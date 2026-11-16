#include "common.h"
#include "mgresultdealer.h"


s8 mgresultdealer_coinRainF = 0;
s8 mgresultdealer_coinDoneF = 0;
s32 mgresultdealer_coinTimer = 0;
s32 mgresultdealer_coinNum = 0;
s32 mgresultdealer_coinOutCnt = 0;
s32 mgresultdealer_coinMax = 0;
s32 mgresultdealer_coinInterval = 0;
s32 mgresultdealer_coinEndSeF = 0;
s32 mgresultdealer_coinVibF = 0;
s8 mgresultdealer_fadeF = 0;
s8 mgresultdealer_fadeDoneF = 0;
s32 mgresultdealer_fadeTimer = 0;
s8 mgresultdealer_fadeDispF = 0;
s16 mgresultdealer_fadeAlpha = 0;
u8 mgresultdealer_fadePad[4] = { 0 }; /* Unreferenced. */
s8 mgresultdealer_calcF = 0;
s8 mgresultdealer_calcDoneF = 0;
s32 mgresultdealer_calcCountCnt = 0;
s32 mgresultdealer_calcWaitCnt = 0;
s32 mgresultdealer_calcSeValue = 0;
s32 mgresultdealer_calcEndCnt = 0;

extern s16 mgresultdealer_fadeHookMdl;
extern s32 mgresultdealer_fadeSprData;
extern HuSprite *mgresultdealer_fadeSpr;
extern u8 *mgresultdealer_fadeTex;
extern UnkDealerSprites mgresultdealer_calcSpr;
extern s32 mgresultdealer_calcOpenF;
extern s32 mgresultdealer_calcCloseF;
extern s16 mgresultdealer_payoutRate;
extern omObjData *mgresultdealer_calcObj;
extern omObjFunc mgresultdealer_calcFunc;
extern s16 mgresultdealer_bet;
extern UnkDealerFadeProc mgresultdealer_fadeWork;
extern u16 mgresultdealer_coinSprMdl;
extern u16 mgresultdealer_coinEffSprMdl;
extern UnkDealerCoin mgresultdealer_coinTbl[40];
extern UnkDealerCoin mgresultdealer_coinEffTbl[40];
extern omObjFunc mgresultdealer_coinFunc;
extern omObjData *mgresultdealer_coinObj;
extern s8 mgresultdealer_playerOrderTbl[4];

void mgresultdealer_CoinRain(omObjData *);
void mgresultdealer_CoinDestroy(void);
void mgresultdealer_FadeUpdate(omObjData *);
void mgresultdealer_FadeDestroy(void);
void mgresultdealer_FadeDraw(Gfx **, s32, s32);
void mgresultdealer_FadeDispOn(void);
void mgresultdealer_FadeAlphaSet(u8);
void mgresultdealer_CalcWait(omObjData *);
void mgresultdealer_CalcCount(omObjData *);
void mgresultdealer_CalcEndWait(omObjData *arg0);
void mgresultdealer_CalcDestroy(void);
void mgresultdealer_CalcOpenStart(void);
void mgresultdealer_CalcOpen(omObjData *);
void mgresultdealer_CalcClose(omObjData *);

void mgresultdealer_CoinProc(void) {
    omObjData *obj;
    void *data;
    s8 i;

    obj = omAddObj(0x14, 0x51, 0, -1, NULL);
    mgresultdealer_coinObj = obj;

    data = DataRead(0x210026);
    mgresultdealer_coinSprMdl = Hu3DSprModelCreate(data, 0x2BD, 8);
    DataClose(data);
    Hu3DModelObjAttrSet(Hu3DSprModelData[mgresultdealer_coinSprMdl].modelId, 0x70000000, 0x70000000);
    for (i = 0; i < 40; i++) {
        mgresultdealer_coinTbl[i].unk_00 = 0;
        mgresultdealer_coinTbl[i].unk_02 = Hu3DSprModelLink(mgresultdealer_coinSprMdl, 8);
        mgresultdealer_coinTbl[i].unk_04 = 0;
        obj->model[i + 1] = Hu3DSprModelData[mgresultdealer_coinTbl[i].unk_02].modelId;
        Hu3DModelPosSet(obj->model[i + 1], 0.0f, 400.0f, 0.0f);
        Hu3DModelCameraSet(obj->model[i + 1], 1);
        Hu3DMotionSpeedSet(obj->model[i + 1], 2.0f);
        Hu3DModelScaleSet(Hu3DSprModelData[i + 1].modelId, 1.5f, 1.5f, 1.5f);
    }

    data = DataRead(0xC);
    mgresultdealer_coinEffSprMdl = Hu3DSprModelCreate(data, 0x2BD, 8);
    DataClose(data);
    Hu3DModelObjAttrSet(Hu3DSprModelData[mgresultdealer_coinEffSprMdl].modelId, 0x70000000, 0x70000000);
    Hu3DModelScaleSet(Hu3DSprModelData[mgresultdealer_coinEffSprMdl].modelId, 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 40; i++) {
        mgresultdealer_coinEffTbl[i].unk_00 = 0;
        mgresultdealer_coinEffTbl[i].unk_02 = Hu3DSprModelLink(mgresultdealer_coinEffSprMdl, 8);
        mgresultdealer_coinEffTbl[i].unk_04 = 0;
        obj->model[i + 41] = Hu3DSprModelData[mgresultdealer_coinEffTbl[i].unk_02].modelId;
        Hu3DModelPosSet(obj->model[i + 41], 0.0f, 400.0f, 0.0f);
        Hu3DModelCameraSet(obj->model[i + 41], 1);
        Hu3DMotionSpeedSet(obj->model[i + 41], 1.0f);
        Hu3DModelScaleSet(Hu3DSprModelData[i + 41].modelId, 3.0f, 3.0f, 3.0f);
    }

    obj->model[0] = -1;
    mgresultdealer_coinRainF = 0;
    mgresultdealer_coinDoneF = 0;
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    omPrcSetDestructor(0, mgresultdealer_CoinDestroy);
    mgresultdealer_coinFunc = mgresultdealer_CoinRain;
    while (TRUE) {
        mgresultdealer_coinFunc(obj);
        HuPrcVSleep();
    }
}

void mgresultdealer_CoinRain(omObjData *obj) {
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

    if (mgresultdealer_coinRainF) {
        if ((spawning = mgresultdealer_coinOutCnt < mgresultdealer_coinMax) == TRUE) {
            count = 0;
            for (i = 0; i < 40; i++) {
                if (mgresultdealer_coinTbl[i].unk_00 != 0) {
                    continue;
                }
                if (mgresultdealer_coinTimer % mgresultdealer_coinInterval != 0) {
                    continue;
                }
                entry = &Hu3DSprModelData[mgresultdealer_coinTbl[i].unk_02];
                animSet = &Hu3DAnimSetData[(u16)entry->unk_02];
                rot = &animSet->rot[entry->pointIdx];
                Hu3DModelAttrSet(obj->model[i + 1], HU3D_ATTR_DISPOFF, 0);
                if (mgresultdealer_coinNum >= 20) {
                    max = (rand8() & 1) + 1;
                } else {
                    max = 1;
                }
                Hu3DModelPosSet(obj->model[i + 1], 0.0f, 400.0f, 0.0f);
                mgresultdealer_coinTbl[i].unk_08.x = (u8)(rand8() % 60) - 30;
                mgresultdealer_coinTbl[i].unk_08.y = 400.0f;
                mgresultdealer_coinTbl[i].unk_08.z = (u8)(rand8() % 60) - 30;
                mgresultdealer_coinTbl[i].unk_00 = 1;
                mgresultdealer_coinTbl[i].unk_14 = 0.98f;
                entry->nodeIdx = rand8() % rot->frameCount;
                entry->unk_08 = 0;
                mgresultdealer_coinOutCnt++;
                if (mgresultdealer_coinOutCnt >= mgresultdealer_coinMax) {
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
            if (mgresultdealer_coinTbl[i].unk_00 != 1) {
                continue;
            }
            x = mgresultdealer_coinTbl[i].unk_08.x;
            y = mgresultdealer_coinTbl[i].unk_08.y;
            z = mgresultdealer_coinTbl[i].unk_08.z;
            Hu3DModelPosSet(obj->model[i + 1], x, y, z);
            mgresultdealer_coinTbl[i].unk_08.y -= mgresultdealer_coinTbl[i].unk_14;
            mgresultdealer_coinTbl[i].unk_14 += 0.98f;
            mgresultdealer_coinTbl[i].unk_04++;
            if (y <= 152.5f) {
                mgresultdealer_coinTbl[i].unk_00 = 0;
                Hu3DModelAttrSet(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(obj->model[i + 41], HU3D_ATTR_DISPOFF, 0);
                Hu3DModelPosSet(obj->model[i + 41], x, y, z);
                Hu3DMotionTimeSet(obj->model[i + 41], 0);
                Hu3DSprModelFrameSet(mgresultdealer_coinEffTbl[i].unk_02, 0);
                HuAudFXPlay(9);
                if (mgresultdealer_coinVibF == 0) {
                    if (!(GwPlayer[mgresultdealer_playerOrderTbl[0]].stat & 1)) {
                        omVibrate(mgresultdealer_playerOrderTbl[0], 5, 0, 5);
                    }
                    mgresultdealer_coinVibF = 1;
                }
            }
            landed++;
        }

        if (landed == 0 && spawning != TRUE) {
            if (mgresultdealer_coinEndSeF == 0) {
                HuAudFXPlay(0x517);
                mgresultdealer_coinEndSeF = 1;
            }
            mgresultdealer_coinDoneF = 1;
        }
        mgresultdealer_coinTimer++;
    }
}

void mgresultdealer_CoinDestroy(void) {
}

void mgresultdealer_CoinRainStart(s32 count) {
    omObjData *obj = mgresultdealer_coinObj;
    s8 i;

    if (count > 0) {
        count = (count >= 1000) ? 999 : count;
        mgresultdealer_coinNum = count;
        mgresultdealer_coinOutCnt = 0;
        mgresultdealer_coinTimer = 0;
        if (count <= 50) {
            mgresultdealer_coinMax = count;
        } else {
            mgresultdealer_coinMax = 50;
        }
        if (count > 40) {
            mgresultdealer_coinInterval = 100 / (mgresultdealer_coinMax + 1);
        } else if (count > 20) {
            mgresultdealer_coinInterval = 80 / (mgresultdealer_coinMax + 1);
        } else {
            mgresultdealer_coinInterval = 60 / (mgresultdealer_coinMax + 1);
        }
        for (i = 0; i < 40; i++) {
            mgresultdealer_coinTbl[i].unk_00 = 0;
            mgresultdealer_coinTbl[i].unk_04 = 0;
            mgresultdealer_coinTbl[i].unk_08.x = mgresultdealer_coinTbl[i].unk_08.y = mgresultdealer_coinTbl[i].unk_08.z = 0.0f;
            mgresultdealer_coinTbl[i].unk_14 = 0.98f;
            Hu3DModelAttrSet(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelPosSet(obj->model[i + 1], 0.0f, 400.0f, 0.0f);
        }
        mgresultdealer_coinRainF = 1;
        mgresultdealer_coinDoneF = 0;
    }
}

s8 mgresultdealer_CoinRainDoneCheck(void) {
    return mgresultdealer_coinDoneF;
}

void mgresultdealer_FadeProc(void) {
    omObjData *obj;
    s16 sprite;
    s16 group;

    obj = omAddObj(0x14, 1, 0, -1, NULL);
    mgresultdealer_fadeWork.obj = obj;
    sprite = HuSprAnimDataRead(0x190001);
    mgresultdealer_fadeSprData = sprite;
    group = HuSprGrpCreate(1, 0);
    HuSprAttrSet(group, 0, 0x8000);
    HuSprGrpMemberSet(group, 0, sprite, 0);
    mgresultdealer_fadeSpr = HuSprGet(group, 0);
    mgresultdealer_fadeTex = mgresultdealer_fadeSpr->data->pat->data;
    mgresultdealer_fadeHookMdl = Hu3DHookFuncCreate(0, mgresultdealer_FadeDraw, 2);
    Hu3DModelCameraSet(mgresultdealer_fadeHookMdl, 1);
    mgresultdealer_fadeF = 0;
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    omPrcSetDestructor(0, mgresultdealer_FadeDestroy);
    mgresultdealer_fadeWork.objFunc = mgresultdealer_FadeUpdate;
    while (TRUE) {
        mgresultdealer_fadeWork.objFunc(obj);
        HuPrcVSleep();
    }
}

void mgresultdealer_FadeUpdate(omObjData *obj) {
    f32 step;

    if (mgresultdealer_fadeF) {
        step = 255.0f / 30;
        mgresultdealer_FadeAlphaSet(mgresultdealer_fadeTimer * step);
        mgresultdealer_fadeTimer++;
        if (mgresultdealer_fadeTimer >= 30) {
            mgresultdealer_FadeAlphaSet(255);
            mgresultdealer_fadeDoneF = 1;
            mgresultdealer_fadeF = 0;
        }
    }
}

void mgresultdealer_FadeDestroy(void) {
}

void mgresultdealer_FadeStart(void) {
    mgresultdealer_fadeF = 1;
    mgresultdealer_fadeDoneF = 0;
    mgresultdealer_fadeTimer = 0;
    mgresultdealer_FadeDispOn();
    mgresultdealer_FadeAlphaSet(0);
}

s8 mgresultdealer_FadeDoneCheck(void) {
    return mgresultdealer_fadeDoneF;
}

void mgresultdealer_FadeDraw(Gfx **gfx, s32 arg1, s32 arg2) {
    Gfx *gdl;
    s32 alpha;
    s32 y;

    if (mgresultdealer_fadeDispF) {
        alpha = mgresultdealer_fadeAlpha;
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
            gDPLoadTextureTile_4b(gdl++, mgresultdealer_fadeTex, G_IM_FMT_I, 320, 240, 0, y, 319, y + 9, 0,
                                  G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                  G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTileSize(gdl++, G_TX_RENDERTILE, 0, 0, 320 << 2, 10 << 2);
            gSPTextureRectangle(gdl++, 0, y << 2, 320 << 2, (y + 10) << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
        }
        *gfx = gdl;
    }
}

void mgresultdealer_FadeDispOn(void) {
    mgresultdealer_fadeDispF = 1;
}

void mgresultdealer_FadeDispOff(void) {
    mgresultdealer_fadeDispF = 0;
}

void mgresultdealer_FadeAlphaSet(u8 arg0) {
    mgresultdealer_fadeAlpha = arg0;
}

void mgresultdealer_CalcProc(void) {
    omObjData *obj;
    s16 multSprite;
    s16 sprite;
    s16 x;
    s8 i;

    obj = omAddObj(0x14, 0, 0, -1, NULL);
    mgresultdealer_calcObj = obj;

    mgresultdealer_calcSpr.groups[0].unk_02[0] = (s16)(mgresultdealer_bet / 100) % 10;
    mgresultdealer_calcSpr.groups[0].unk_02[1] = (s16)(mgresultdealer_bet / 10) % 10;
    mgresultdealer_calcSpr.groups[0].unk_02[2] = mgresultdealer_bet % 10;
    mgresultdealer_calcSpr.groups[1].unk_02[0] = (s16)(mgresultdealer_payoutRate / 100) % 10;
    mgresultdealer_calcSpr.groups[1].unk_02[1] = (s16)(mgresultdealer_payoutRate / 10) % 10;
    mgresultdealer_calcSpr.groups[1].unk_02[2] = mgresultdealer_payoutRate % 10;
    mgresultdealer_calcSpr.groups[2].unk_02[0] = 0;
    mgresultdealer_calcSpr.groups[2].unk_02[1] = 0;
    mgresultdealer_calcSpr.groups[2].unk_02[2] = 0;

    sprite = HuSprAnimDataRead(0x190005);
    mgresultdealer_calcSpr.unk_2C = espEntry(sprite, 0, 1);
    espTPLvlSet(mgresultdealer_calcSpr.unk_2C, 0x7F);
    espPosSet(mgresultdealer_calcSpr.unk_2C, 0xA9, 0x60);
    espDispOff(mgresultdealer_calcSpr.unk_2C);
    x = 0x5C;

    sprite = HuSprAnimDataRead(0x190004);
    mgresultdealer_calcSpr.unk_2A = espEntry(sprite, 0, 1);
    espPosSet(mgresultdealer_calcSpr.unk_2A, 0xA3, 0x5A);
    espDispOff(mgresultdealer_calcSpr.unk_2A);

    sprite = HuSprAnimDataRead(0x190009);
    mgresultdealer_calcSpr.groups[0].unk_00 = espEntry(sprite, 0, 1);
    espPosSet(mgresultdealer_calcSpr.groups[0].unk_00, 0x4C, 0x5A);
    espBankSet(mgresultdealer_calcSpr.groups[0].unk_00, 0, 0);
    espSpeedSet(mgresultdealer_calcSpr.groups[0].unk_00, 2.0f);
    espAnimModeSet(mgresultdealer_calcSpr.groups[0].unk_00, 0);
    espDispOff(mgresultdealer_calcSpr.groups[0].unk_00);

    sprite = HuSprAnimDataRead(0xC0086);
    for (i = 0; i < 3; i++) {
        mgresultdealer_calcSpr.groups[0].unk_08[i] = espEntry(sprite, 0, 0);
        espPosSet(mgresultdealer_calcSpr.groups[0].unk_08[i], x, 0x5A);
        espBankSet(mgresultdealer_calcSpr.groups[0].unk_08[i], (u16)mgresultdealer_calcSpr.groups[0].unk_02[i], 0);
        espDispOff(mgresultdealer_calcSpr.groups[0].unk_08[i]);
        x += 16;
    }

    multSprite = HuSprAnimDataRead(0xC008C);
    mgresultdealer_calcSpr.groups[1].unk_00 = espEntry(multSprite, 0, 0);
    espPosSet(mgresultdealer_calcSpr.groups[1].unk_00, x, 0x5A);
    espBankSet(mgresultdealer_calcSpr.groups[1].unk_00, 0, 0);
    espDispOff(mgresultdealer_calcSpr.groups[1].unk_00);
    x += 16;

    for (i = 0; i < 3; i++) {
        mgresultdealer_calcSpr.groups[1].unk_08[i] = espEntry(sprite, 0, 0);
        espPosSet(mgresultdealer_calcSpr.groups[1].unk_08[i], x, 0x5A);
        espBankSet(mgresultdealer_calcSpr.groups[1].unk_08[i], (u16)mgresultdealer_calcSpr.groups[1].unk_02[i], 0);
        espDispOff(mgresultdealer_calcSpr.groups[1].unk_08[i]);
        x += 16;
    }

    mgresultdealer_calcSpr.groups[2].unk_00 = espEntry(multSprite, 0, 0);
    espPosSet(mgresultdealer_calcSpr.groups[2].unk_00, x, 0x5A);
    espBankSet(mgresultdealer_calcSpr.groups[2].unk_00, 3, 0);
    espDispOff(mgresultdealer_calcSpr.groups[2].unk_00);
    x += 16;

    for (i = 0; i < 3; i++) {
        mgresultdealer_calcSpr.groups[2].unk_08[i] = espEntry(sprite, 0, 0);
        espPosSet(mgresultdealer_calcSpr.groups[2].unk_08[i], x, 0x5A);
        espBankSet(mgresultdealer_calcSpr.groups[2].unk_08[i], (u16)mgresultdealer_calcSpr.groups[2].unk_02[i], 0);
        espDispOff(mgresultdealer_calcSpr.groups[2].unk_08[i]);
        x += 16;
    }

    omPrcSetDestructor(0, mgresultdealer_CalcDestroy);
    mgresultdealer_calcFunc = mgresultdealer_CalcWait;
    while (TRUE) {
        mgresultdealer_calcFunc(obj);
        HuPrcVSleep();
    }
}

void mgresultdealer_CalcWait(omObjData *arg0) {
    if (mgresultdealer_calcF == 0) {
        return;
    }

    mgresultdealer_calcWaitCnt++;

    if (mgresultdealer_calcWaitCnt < 0xF) {
        return;
    }

    mgresultdealer_calcWaitCnt = 0;

    if (mgresultdealer_bet * mgresultdealer_payoutRate == 0) {
        mgresultdealer_calcF = 0;
        mgresultdealer_calcDoneF = 1;
        mgresultdealer_calcWaitCnt = 0;
        mgresultdealer_calcCloseF = 0;
        mgresultdealer_calcFunc = mgresultdealer_CalcClose;
    } else {
        espBankSet(mgresultdealer_calcSpr.groups[0].unk_00, 0, 0);
        espAnimModeSet(mgresultdealer_calcSpr.groups[0].unk_00, 1);
        espDispOn(mgresultdealer_calcSpr.groups[0].unk_00);
        mgresultdealer_calcFunc = mgresultdealer_CalcCount;
    }
}

void mgresultdealer_CalcCount(omObjData *arg0) {
    s32 total;
    s16 value;
    s8 i;

    if (mgresultdealer_calcF == 0) {
        return;
    }

    total = mgresultdealer_bet * mgresultdealer_payoutRate;
    total = (total >= 1000) ? 999 : total;
    value = total / 28.0f * mgresultdealer_calcCountCnt;
    mgresultdealer_calcSpr.groups[2].unk_02[0] = (s16)(value / 100) % 10;
    mgresultdealer_calcSpr.groups[2].unk_02[1] = (s16)(value / 10) % 10;
    mgresultdealer_calcSpr.groups[2].unk_02[2] = value % 10;
    for (i = 0; i < 3; i++) {
        espAnimModeSet(mgresultdealer_calcSpr.groups[2].unk_08[i], 1);
        espBankSet(mgresultdealer_calcSpr.groups[2].unk_08[i], (u16)mgresultdealer_calcSpr.groups[2].unk_02[i], 0);
    }
    if (value < 10) {
        espDispOff(mgresultdealer_calcSpr.groups[2].unk_08[0]);
        espDispOff(mgresultdealer_calcSpr.groups[2].unk_08[1]);
    } else if (value < 100) {
        espDispOff(mgresultdealer_calcSpr.groups[2].unk_08[0]);
        espDispOn(mgresultdealer_calcSpr.groups[2].unk_08[1]);
    } else {
        espDispOn(mgresultdealer_calcSpr.groups[2].unk_08[0]);
        espDispOn(mgresultdealer_calcSpr.groups[2].unk_08[1]);
    }
    espDispOn(mgresultdealer_calcSpr.groups[2].unk_08[2]);
    if (mgresultdealer_calcSeValue < value) {
        HuAudFXPlay(9);
        mgresultdealer_calcSeValue = value;
    }

    mgresultdealer_calcCountCnt++;
    if (mgresultdealer_calcCountCnt < 28) {
        return;
    }

    HuAudFXPlay(9);
    value = total;
    mgresultdealer_calcSpr.groups[2].unk_02[0] = (s16)(value / 100) % 10;
    mgresultdealer_calcSpr.groups[2].unk_02[1] = (s16)(value / 10) % 10;
    mgresultdealer_calcSpr.groups[2].unk_02[2] = value % 10;
    for (i = 0; i < 3; i++) {
        espAnimModeSet(mgresultdealer_calcSpr.groups[2].unk_08[i], 1);
        espBankSet(mgresultdealer_calcSpr.groups[2].unk_08[i], (u16)mgresultdealer_calcSpr.groups[2].unk_02[i], 0);
    }
    if (value < 10) {
        espDispOff(mgresultdealer_calcSpr.groups[2].unk_08[0]);
        espDispOff(mgresultdealer_calcSpr.groups[2].unk_08[1]);
    } else if (value < 100) {
        espDispOff(mgresultdealer_calcSpr.groups[2].unk_08[0]);
        espDispOn(mgresultdealer_calcSpr.groups[2].unk_08[1]);
    } else {
        espDispOn(mgresultdealer_calcSpr.groups[2].unk_08[0]);
        espDispOn(mgresultdealer_calcSpr.groups[2].unk_08[1]);
    }
    espDispOn(mgresultdealer_calcSpr.groups[2].unk_08[2]);
    espAnimModeSet(mgresultdealer_calcSpr.groups[0].unk_00, 0);
    mgresultdealer_calcSeValue = 0;
    mgresultdealer_calcFunc = mgresultdealer_CalcEndWait;
}

void mgresultdealer_CalcEndWait(omObjData *arg0) {
    if (mgresultdealer_calcF == 0) {
        return;
    }

    mgresultdealer_calcEndCnt++;

    if (mgresultdealer_calcEndCnt < 0xF) {
        return;
    }

    mgresultdealer_calcF = 0;
    mgresultdealer_calcDoneF = 1;
    mgresultdealer_calcEndCnt = 0;
    mgresultdealer_calcCloseF = 0;
    mgresultdealer_calcFunc = mgresultdealer_CalcClose;
}

void mgresultdealer_CalcDestroy(void) {
}

void mgresultdealer_CalcStart(void) {
    mgresultdealer_calcF = 1;
    mgresultdealer_calcDoneF = 0;
    mgresultdealer_calcCountCnt = 0;
    mgresultdealer_CalcOpenStart();
}

s32 mgresultdealer_CalcOpenCheck(void) {
    return mgresultdealer_calcOpenF;
}

s32 mgresultdealer_CalcCloseCheck(void) {
    return mgresultdealer_calcCloseF;
}

void mgresultdealer_CalcOpenStart(void) {
    s32 i;

    mgresultdealer_calcOpenF = 0;
    espDispOn(mgresultdealer_calcSpr.unk_2A);
    espDispOn(mgresultdealer_calcSpr.unk_2C);
    espDispOn(mgresultdealer_calcSpr.groups[0].unk_00);
    espDispOn(mgresultdealer_calcSpr.groups[1].unk_00);
    espDispOn(mgresultdealer_calcSpr.groups[2].unk_00);
    if (mgresultdealer_calcSpr.groups[0].unk_02[0] == 0) {
        espDispOff(mgresultdealer_calcSpr.groups[0].unk_08[0]);
        if (mgresultdealer_calcSpr.groups[0].unk_02[1] == 0) {
            espDispOff(mgresultdealer_calcSpr.groups[0].unk_08[1]);
        } else {
            espDispOn(mgresultdealer_calcSpr.groups[0].unk_08[1]);
        }
    } else {
        espDispOn(mgresultdealer_calcSpr.groups[0].unk_08[0]);
        espDispOn(mgresultdealer_calcSpr.groups[0].unk_08[1]);
    }
    espDispOn(mgresultdealer_calcSpr.groups[0].unk_08[2]);
    if (mgresultdealer_calcSpr.groups[1].unk_02[0] == 0) {
        espDispOff(mgresultdealer_calcSpr.groups[1].unk_08[0]);
        if (mgresultdealer_calcSpr.groups[1].unk_02[1] == 0) {
            espDispOff(mgresultdealer_calcSpr.groups[1].unk_08[1]);
        } else {
            espDispOn(mgresultdealer_calcSpr.groups[1].unk_08[1]);
        }
    } else {
        espDispOn(mgresultdealer_calcSpr.groups[1].unk_08[0]);
        espDispOn(mgresultdealer_calcSpr.groups[1].unk_08[1]);
    }
    espDispOn(mgresultdealer_calcSpr.groups[1].unk_08[2]);
    if (mgresultdealer_calcSpr.groups[2].unk_02[0] == 0) {
        espDispOff(mgresultdealer_calcSpr.groups[2].unk_08[0]);
        if (mgresultdealer_calcSpr.groups[2].unk_02[1] == 0) {
            espDispOff(mgresultdealer_calcSpr.groups[2].unk_08[1]);
        } else {
            espDispOn(mgresultdealer_calcSpr.groups[2].unk_08[1]);
        }
    } else {
        espDispOn(mgresultdealer_calcSpr.groups[2].unk_08[0]);
        espDispOn(mgresultdealer_calcSpr.groups[2].unk_08[1]);
    }
    espDispOn(mgresultdealer_calcSpr.groups[2].unk_08[2]);
    espScaleSet(mgresultdealer_calcSpr.unk_2A, 1.0f, 0.0f);
    espScaleSet(mgresultdealer_calcSpr.unk_2C, 1.0f, 0.0f);
    espScaleSet(mgresultdealer_calcSpr.groups[0].unk_00, 1.0f, 0.0f);
    espScaleSet(mgresultdealer_calcSpr.groups[1].unk_00, 1.0f, 0.0f);
    espScaleSet(mgresultdealer_calcSpr.groups[2].unk_00, 1.0f, 0.0f);
    for (i = 0; i < 3; i++) {
        espScaleSet(mgresultdealer_calcSpr.groups[0].unk_08[i], 1.0f, 0.0f);
        espScaleSet(mgresultdealer_calcSpr.groups[1].unk_08[i], 1.0f, 0.0f);
        espScaleSet(mgresultdealer_calcSpr.groups[2].unk_08[i], 1.0f, 0.0f);
    }
    mgresultdealer_calcFunc = mgresultdealer_CalcOpen;
}

void mgresultdealer_CalcDispOff(void) {
    s8 i;

    espDispOff(mgresultdealer_calcSpr.unk_2A);
    espDispOff(mgresultdealer_calcSpr.unk_2C);
    espDispOff(mgresultdealer_calcSpr.groups[0].unk_00);
    espDispOff(mgresultdealer_calcSpr.groups[1].unk_00);
    espDispOff(mgresultdealer_calcSpr.groups[2].unk_00);
    for (i = 0; i < 3; i++) {
        espDispOff(mgresultdealer_calcSpr.groups[0].unk_08[i]);
        espDispOff(mgresultdealer_calcSpr.groups[1].unk_08[i]);
        espDispOff(mgresultdealer_calcSpr.groups[2].unk_08[i]);
    }
}

s8 mgresultdealer_CalcDoneCheck(void) {
    return mgresultdealer_calcDoneF;
}

void mgresultdealer_CalcOpen(omObjData *arg0) {
    f32 scale = 0.0f;
    s32 i;
    s32 j;

    for (i = 0; i < 10; i++) {
        espScaleSet(mgresultdealer_calcSpr.unk_2A, 1.0f, scale);
        espScaleSet(mgresultdealer_calcSpr.unk_2C, 1.0f, scale);
        espScaleSet(mgresultdealer_calcSpr.groups[0].unk_00, 1.0f, scale);
        espScaleSet(mgresultdealer_calcSpr.groups[1].unk_00, 1.0f, scale);
        espScaleSet(mgresultdealer_calcSpr.groups[2].unk_00, 1.0f, scale);
        for (j = 0; j < 3; j++) {
            espScaleSet(mgresultdealer_calcSpr.groups[0].unk_08[j], 1.0f, scale);
            espScaleSet(mgresultdealer_calcSpr.groups[1].unk_08[j], 1.0f, scale);
            espScaleSet(mgresultdealer_calcSpr.groups[2].unk_08[j], 1.0f, scale);
        }
        scale = sindf(i * 9.0f) * 1.1f;
        HuPrcVSleep();
    }
    espScaleSet(mgresultdealer_calcSpr.unk_2A, 1.0f, 1.0f);
    espScaleSet(mgresultdealer_calcSpr.unk_2C, 1.0f, 1.0f);
    espScaleSet(mgresultdealer_calcSpr.groups[0].unk_00, 1.0f, 1.0f);
    espScaleSet(mgresultdealer_calcSpr.groups[1].unk_00, 1.0f, 1.0f);
    espScaleSet(mgresultdealer_calcSpr.groups[2].unk_00, 1.0f, 1.0f);
    for (j = 0; j < 3; j++) {
        espScaleSet(mgresultdealer_calcSpr.groups[0].unk_08[j], 1.0f, 1.0f);
        espScaleSet(mgresultdealer_calcSpr.groups[1].unk_08[j], 1.0f, 1.0f);
        espScaleSet(mgresultdealer_calcSpr.groups[2].unk_08[j], 1.0f, 1.0f);
    }
    mgresultdealer_calcOpenF = 1;
    mgresultdealer_calcFunc = mgresultdealer_CalcWait;
}

void mgresultdealer_CalcClose(omObjData *arg0) {
    f32 scale = 1.0f;
    s32 i;
    s32 j;

    for (i = 0; i < 5; i++) {
        espScaleSet(mgresultdealer_calcSpr.unk_2A, 1.0f, scale);
        espScaleSet(mgresultdealer_calcSpr.unk_2C, 1.0f, scale);
        espScaleSet(mgresultdealer_calcSpr.groups[0].unk_00, 1.0f, scale);
        espScaleSet(mgresultdealer_calcSpr.groups[1].unk_00, 1.0f, scale);
        espScaleSet(mgresultdealer_calcSpr.groups[2].unk_00, 1.0f, scale);
        for (j = 0; j < 3; j++) {
            espScaleSet(mgresultdealer_calcSpr.groups[0].unk_08[j], 1.0f, scale);
            espScaleSet(mgresultdealer_calcSpr.groups[1].unk_08[j], 1.0f, scale);
            espScaleSet(mgresultdealer_calcSpr.groups[2].unk_08[j], 1.0f, scale);
        }
        scale = cosdf(i * 18.0f);
        HuPrcVSleep();
    }
    mgresultdealer_CalcDispOff();
    mgresultdealer_calcCloseF = 1;
    mgresultdealer_calcFunc = mgresultdealer_CalcWait;
}
