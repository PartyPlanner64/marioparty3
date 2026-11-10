#include "common.h"
#include "gcc/string.h"

extern s16 D_800A11E6_main;
extern s16 D_800D1F36_main;
extern s16 D_800D1FE0_main;
extern u8 D_800CE20A_main;
extern u16 D_80109AA4_mgenter;
extern s16 D_80109AA6_mgenter;
extern s16 D_80109B20_mgenter;
extern s16 D_80109B22_mgenter;
extern s16 D_80109B24_mgenter;
extern s16 D_80109B26_mgenter;
extern s16 D_80109B28_mgenter;
extern s16 D_80109B2A_mgenter;
extern s16 D_80109B2C_mgenter;
extern s16 D_80109B2E_mgenter;
extern s16 D_80109B30_mgenter;
extern s16 D_80109B32_mgenter;
extern s16 D_80109B34_mgenter;
extern s16 D_80109B36_mgenter;
extern s16 D_80109B38_mgenter;
extern s16 D_80109B3A_mgenter;
extern f32 D_80109AA0_mgenter;
extern f32 D_80109AB0_mgenter;
extern f32 D_80109B64_mgenter;
extern s16 D_80109B74_mgenter;
extern f32 D_80109B78_mgenter;
extern s16 D_80109B76_mgenter;
extern s16 D_80109B7C_mgenter;
extern s16 D_80109B98_mgenter;

void func_80105CD8_mgenter(void);
void func_80106294_mgenter(void);
void func_80106BD0_mgenter(void);
void func_80106568_mgenter(void);
void func_80106710_mgenter(u8 *str);
void func_8010677C_mgenter(void);
void func_801079B4_mgenter(void);
void func_80107E5C_mgenter(s16 winId, s16 value, u8 *buf);
void func_80107F0C_mgenter(void);
void func_80108560_mgenter(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void func_80108590_mgenter(void);
void func_801087C0_mgenter(void);
void func_80108934_mgenter(omObjData *obj);
void func_80109020_mgenter(void);
s16 func_801095F4_mgenter(void);
void func_801096EC_mgenter(s16 arg0);
void func_801089A0_mgenter(omObjData *);
void func_80109820_mgenter(void);
void func_801098D8_mgenter(void);

void func_801059D0_mgenter(void) {
    process_func func;
    s16 typeBits;

    Hu3DCamInit(1);
    func_8001FE20_main(1);
    func_800142A0_main(0x19);
    omInitObjMan(0x33, 0x19);
    HuWinInit();
    func_8004A208_main();
    omAddObj(0x2710, 0, 0, -1, func_80108934_mgenter);
    Hu3DGLightMaxSet(1);
    D_80109B78_mgenter = 8000.0f;
    D_80109AB0_mgenter = 45.0f;
    D_80109B64_mgenter = 80.0f;
    CRot.x = 354.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2240.0f;
    Center.x = 0.0f;
    Center.y = 260.0f;
    Center.z = 13.0f;
    Hu3DCameraPerspectiveSet(0, D_80109AB0_mgenter, D_80109B64_mgenter, D_80109B78_mgenter);
    omPrcSetStatBit(omAddPrcObj(func_80109020_mgenter, 0x1100, 0x800, 0), 0xA0);
    WipeCreateIn(0xFF, 0x10);
    D_800CD280_main = 1;
    Hu3DBGColorSet(0xFF, 0xFF, 0xFF);
    D_80109B74_mgenter = D_800D1F36_main;
    D_80109B7C_mgenter = 1;
    D_80109B76_mgenter = func_800341C0_main(GwSystem.minigame_index);
    D_80109B98_mgenter = 0;
    D_80109B2A_mgenter = GwSystem.minigame_index - 1;
    typeBits = (D_800A6D40_main[D_80109B2A_mgenter].flags & 0x3800) >> 11;
    D_80109B2E_mgenter = typeBits + 1;
    if (D_80109B2E_mgenter >= 2) {
        D_80109B2E_mgenter = typeBits;
    }
    if (D_80109B2A_mgenter == 70) {
        func = func_80105CD8_mgenter;
    } else if (D_80109B2A_mgenter == 30) {
        func = func_801079B4_mgenter;
    } else {
        func = func_80106294_mgenter;
    }
    omAddPrcObj(func, 0x3F00, 0x2000, 0);
    if (D_800D1FE0_main != 0) {
        GwSystem.show_minigame_explanations = 1;
    } else {
        D_800D1FE0_main++;
    }
    _SetFlag(0xD);
    HuAudSeqPlay(8);
}

void func_80105C60_mgenter(void) {
    Hu3DCamInit(1);
    func_8001FE20_main(1);
    func_800142A0_main(0x19);
    omInitObjMan(0x33, 0x19);
    omOvlHisChg(0, 0x68, 0, 4);
    omOvlCallEx(0x70, 0, 2);
    _SetFlag(0xD);
    D_800D1FE0_main++;
}

void func_80105CD8_mgenter(void) {
    s16 size[2];
    s16 winId;
    s16 confirmed;

    D_80109B2C_mgenter = D_800A11E6_main;
    if (D_80109B2C_mgenter < 0) {
        D_80109B2C_mgenter = 0;
    }
    D_80109B30_mgenter = 0;
    D_80109B28_mgenter = -1;
    omAddPrcObj(func_80108590_mgenter, 0x3F00, 0x800, 0);
    omAddPrcObj(func_80106568_mgenter, 0x3F00, 0x800, 0);
    omAddPrcObj(func_8010677C_mgenter, 0x3F00, 0x800, 0);
    omAddPrcObj(func_80107F0C_mgenter, 0x3F00, 0x800, 0);
    omAddPrcObj(func_80106BD0_mgenter, 0x3F00, 0x800, 0);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    D_80109B24_mgenter = 0;
    D_80109B26_mgenter = 0;
    HuPrcSleep(10);
    HuWinMesMaxSizeGet(3, size, 0x4600, 0x4601, 0x4603);
    winId = HuWinExCreate(-1, (320 - size[0]) / 2, 180, size[0], size[1], 0);
    HuWinMesSpeedSet(winId, 0);
    HuWinExAnimIn(winId);
    D_80109B32_mgenter = 0;
    while (TRUE) {
        HuWinMesSet(winId, 0x4600, -1, -1);
        while (HuWinStatGet(winId) != 0) {
            HuPrcVSleep();
        }
        func_80108560_mgenter(60, 110, 260, 110);
        D_80109B22_mgenter = 1;
        while (TRUE) {
            func_801098D8_mgenter();
            if (D_800CBB6E_main[D_80109B74_mgenter] >= 31 || (D_800D5558_main[D_80109B74_mgenter] & 1)) {
                HuAudFXPlay(1);
                D_80109B30_mgenter = 1;
                D_80109B22_mgenter = 0;
                HuPrcSleep(10);
                D_80109B22_mgenter = 1;
            } else if (D_800CBB6E_main[D_80109B74_mgenter] < -30 || (D_800D5558_main[D_80109B74_mgenter] & 2)) {
                HuAudFXPlay(1);
                D_80109B30_mgenter = -1;
                D_80109B22_mgenter = 0;
                HuPrcSleep(10);
                D_80109B22_mgenter = 1;
            }
            if (D_800D5558_main[D_80109B74_mgenter] & 0x8000) {
                HuAudFXPlay(2);
                D_800A11E6_main = D_80109B2C_mgenter;
                D_800CE20A_main = D_80109B2C_mgenter;
                break;
            }
            if (D_800D5558_main[D_80109B74_mgenter] & 0x4000) {
                HuAudFXPlay(4);
                D_800A11E6_main = -1;
                D_80109B7C_mgenter = 0;
                D_80109AA4_mgenter = 1;
                D_80109AA6_mgenter = 1;
                while (TRUE) {
                    HuPrcVSleep();
                }
            }
            HuPrcVSleep();
        }
        D_80109B22_mgenter = 0;
        D_80109B26_mgenter = 1;
        D_80109B28_mgenter = 0;
        HuPrcSleep(10);
        func_80108560_mgenter(80, 155, 240, 155);
        D_80109B22_mgenter = 1;
        HuWinMesSet(winId, 0x4603, -1, -1);
        while (HuWinStatGet(winId) != 0) {
            HuPrcVSleep();
        }
        while (TRUE) {
            func_801098D8_mgenter();
            if (D_800CBB6E_main[D_80109B74_mgenter] >= 31 || (D_800D5558_main[D_80109B74_mgenter] & 1)) {
                HuAudFXPlay(1);
                if (++D_80109B32_mgenter >= 3) {
                    D_80109B32_mgenter = 0;
                }
                D_80109B22_mgenter = 0;
                HuPrcSleep(10);
                D_80109B22_mgenter = 1;
            } else if (D_800CBB6E_main[D_80109B74_mgenter] < -30 || (D_800D5558_main[D_80109B74_mgenter] & 2)) {
                HuAudFXPlay(1);
                if (--D_80109B32_mgenter < 0) {
                    D_80109B32_mgenter = 2;
                }
                D_80109B22_mgenter = 0;
                HuPrcSleep(10);
                D_80109B22_mgenter = 1;
            }
            if (D_800D5558_main[D_80109B74_mgenter] & 0x8000) {
                HuAudFXPlay(2);
                confirmed = TRUE;
                break;
            }
            if (D_800D5558_main[D_80109B74_mgenter] & 0x4000) {
                HuAudFXPlay(4);
                confirmed = FALSE;
                break;
            }
            HuPrcVSleep();
        }
        if (confirmed) {
            break;
        }
        D_80109B22_mgenter = 0;
        D_80109B26_mgenter = 2;
        D_80109B28_mgenter = 1;
        HuPrcSleep(10);
    }
    GwPlayer[0].group = 0;
    D_800CB894_main = D_80109B32_mgenter;
    HuWinKill(winId);
    D_80109B7C_mgenter = 2;
    D_80109B76_mgenter = func_800341C0_main(GwSystem.minigame_index);
    D_80109B98_mgenter = 0;
    D_80109AA4_mgenter = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_80106294_mgenter(void) {
    s16 size[2];
    u16 sprite;
    s16 i;
    s16 winId;
    s16 btn;

    D_800A11E6_main = -1;
    omAddPrcObj(func_80106568_mgenter, 0x3F00, 0x800, 0);
    sprite = func_801095F4_mgenter();
    func_801096EC_mgenter(D_800A6D40_main[D_80109B2A_mgenter].flags & 0x7FF);
    espPosSet(sprite, 0, -100);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    D_80109B24_mgenter = 0;
    for (i = 0; i < 11; i++) {
        espPosSet(sprite, sindf(i * 9.0f) * 240.0f - 80.0f, 115);
        HuPrcVSleep();
    }
    HuWinMesMaxSizeGet(1, size, 0x4607);
    winId = HuWinExCreate(-1, (320 - size[0]) / 2, 180, size[0], size[1], 0);
    HuWinMesSpeedSet(winId, 0);
    HuWinExAnimIn(winId);
    HuWinMesSet(winId, 0x4607, -1, -1);
    while (HuWinStatGet(winId) != 0) {
        HuPrcVSleep();
    }
    while (TRUE) {
        btn = D_800D5558_main[D_80109B74_mgenter];
        if (btn & 0x8000) {
            HuAudFXPlay(2);
            break;
        }
        if (btn & 0x4000) {
            HuAudFXPlay(4);
            D_80109B7C_mgenter = 0;
            D_80109AA4_mgenter = 1;
            D_80109AA6_mgenter = 1;
            while (TRUE) {
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
    func_801087C0_mgenter();
    HuWinKill(winId);
    D_80109B7C_mgenter = 2;
    D_80109B76_mgenter = func_800341C0_main(GwSystem.minigame_index);
    D_80109B98_mgenter = 0;
    D_80109AA4_mgenter = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_80106568_mgenter(void) {
    GAMEMES gMes;
    u8 *text;
    s16 strId;
    s16 i;
    f32 y;

    text = func_800364DC_main((void *)(D_80109B2A_mgenter + 0x4700));
    func_80106710_mgenter(text);
    strId = func_8003A308_main(&gMes, (char *)text, 0, -1, -1);
    HuSprPosSet(gMes.strGId[strId], 0, 0, -100);
    func_800365E8_main(text);
    D_80109B24_mgenter = -1;
    if (D_80109B2E_mgenter != 1) {
        y = 28.0f;
    } else {
        y = 44.0f;
    }
    while (TRUE) {
        if (D_80109B24_mgenter == 0) {
            for (i = 0; i < 11; i++) {
                HuSprPosSet(gMes.strGId[strId], 0, sindf(i * 9.0f) * 160.0f, y);
                HuPrcVSleep();
            }
            D_80109B24_mgenter = -1;
        }
        HuPrcVSleep();
    }
}

void func_80106710_mgenter(u8 *str) {
    u8 *dst = str;
    u8 *src = str;
    u32 c;

    while (*src != '\0') {
        *dst = *src;
        c = *src;
        if (c >= 0x20 || c == 0x10) {
            dst++;
        } else if (c == 0x20 || c == 0x11) {
            dst++;
        } else {
            src++;
            continue;
        }
        src++;
    }
    *dst = '\0';
}

void func_8010677C_mgenter(void) {
    GAMEMES gMes[3];
    u8 buf[32];
    u8 *text;
    s16 len;
    s16 i;
    s16 j;
    s16 k;
    s16 strId;
    s16 cur;
    f32 x;

    cur = D_80109B2C_mgenter;
    for (i = 0; i < 3; i++) {
        text = func_800364DC_main((void *)(i + 0x4608));
        len = strlen((char *)text);
        k = 0;
        for (j = 0; j <= len; j++) {
            if (text[j] < 0x30 && text[j] != 0x20) {
                continue;
            }
            buf[k++] = text[j];
        }
        buf[k] = '\0';
        strId = func_8003A308_main(&gMes[i], (char *)buf, 0, -1, -1);
        HuSprPosSet(gMes[i].strGId[strId], 0, -340, 52);
        gMes[i].subMode = k;
        func_800365E8_main(text);
    }
    while (TRUE) {
        if (D_80109B24_mgenter == 0) {
            for (i = 0; i < 11; i++) {
                x = sindf(i * 9.0f) * 160.0f;
                HuSprPosSet(gMes[cur].strGId[strId], 0, x, 52);
                HuPrcVSleep();
            }
        }
        if (D_80109B30_mgenter != 0) {
            for (i = 1; i < 6; i++) {
                x = (1.0f - cosdf(i * 18.0f)) * 240.0f * D_80109B30_mgenter + 160.0f;
                HuSprPosSet(gMes[cur].strGId[strId], 0, x, 52);
                HuPrcVSleep();
            }
            cur += D_80109B30_mgenter;
            if (cur >= 3) {
                cur = 0;
            }
            if (cur < 0) {
                cur = 2;
            }
            for (i = 1; i < 6; i++) {
                x = -(1.0f - sindf(i * 18.0f)) * 240.0f * D_80109B30_mgenter + 160.0f;
                HuSprPosSet(gMes[cur].strGId[strId], 0, x, 52);
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
}

void func_80106BD0_mgenter(void) {
    s16 models[3];
    GAMEMES gMes[3];
    u8 buf[32];
    u8 mesIds[] = { 1, 0, 2 };
    u8 charIds[] = { 0, 2, 1 };
    HmfData *hmf;
    u8 *text;
    s16 model;
    s16 len;
    s16 strId;
    s16 i;
    s16 j;
    s16 k;
    s16 prevSel;
    f32 baseAngle;
    f32 rotAngle;
    f32 dir;
    f32 alpha;

    Hu3DFogSet(500, 550, 255, 255, 255);
    for (i = 0; i < 3; i++) {
        models[i] = func_8000B108_main(charIds[i] | 0x670000, 0x2BD);
        model = models[i];
        func_8001C258_main(model, 4, 4);
        func_8001C814_main(model, 1, 1);
        Hu3DMotionTimeSet(model, D_800CCF58_main[Hu3DData[model].motId].unk02 / 2);
        Hu3DModelPosSet(model, sindf(i * 120) * 500.0f, 0.0f, cosdf(i * 120) * 500.0f);
        hmf = Hu3DData[model].hmf;
        hmf->unk60[func_8002C834_main(hmf, "atama_2")].unk24 = 1;
        Hu3DData[model].rot.x = 20.0f;
    }
    for (i = 0; i < 3; i++) {
        text = func_800364DC_main((void *)(mesIds[i] + 0x4604));
        len = strlen((char *)text);
        j = 0;
        for (k = 0; k <= len; k++) {
            if (text[k] >= 0x30) {
                buf[j++] = text[k];
            }
        }
        buf[j] = '\0';
        strId = func_8003A308_main(&gMes[i], (char *)buf, 0, -1, -1);
        HuSprPosSet(gMes[i].strGId[strId], 0, 160, 130);
        len = j;
        gMes[i].subMode = j;
        for (j = 0; j < len; j++) {
            HuSprTPLvlSet(gMes[i].strGId[0], j + 1, 0);
        }
        func_800365E8_main(text);
    }
    baseAngle = 0.0f;
    prevSel = D_80109B32_mgenter;
    rotAngle = 0.0f;
    while (TRUE) {
        switch (D_80109B28_mgenter) {
            case 0:
                baseAngle = D_80109B32_mgenter * 120;
                prevSel = D_80109B32_mgenter;
                for (j = 0; j < 3; j++) {
                    Hu3DModelPosSet(models[j], sindf(j * 120 + baseAngle) * 500.0f, 0.0f,
                                    cosdf(j * 120 + baseAngle) * 500.0f);
                }
                for (i = 0; i < 3; i++) {
                    if (Hu3DData[models[i]].pos.z > 0.0f) {
                        func_8001C258_main(models[i], 4, 0);
                    } else {
                        func_8001C258_main(models[i], 4, 4);
                    }
                }
                for (i = 0; i < 6; i++) {
                    alpha = i * 51.0f;
                    for (j = 0; j < gMes[D_80109B32_mgenter].subMode; j++) {
                        HuSprTPLvlSet(gMes[D_80109B32_mgenter].strGId[0], j + 1, alpha);
                    }
                    HuPrcVSleep();
                }
                break;
            case 1:
                for (i = 0; i < 3; i++) {
                    func_8001C258_main(models[i], 4, 4);
                }
                func_8001C258_main(models[D_80109B32_mgenter], 4, 0);
                for (i = 0; i < 6; i++) {
                    alpha = i * 51.0f;
                    for (j = 0; j < gMes[D_80109B32_mgenter].subMode; j++) {
                        HuSprTPLvlSet(gMes[D_80109B32_mgenter].strGId[0], j + 1, 255.0f - alpha);
                    }
                    HuPrcVSleep();
                }
                HuPrcSleep(5);
                for (i = 0; i < 3; i++) {
                    func_8001C258_main(models[i], 4, 4);
                }
                break;
        }
        D_80109B28_mgenter = -1;
        if (prevSel != D_80109B32_mgenter) {
            dir = -func_80089750_main(prevSel - D_80109B32_mgenter);
            if ((D_80109B32_mgenter == 2 && prevSel == 0) || (D_80109B32_mgenter == 0 && prevSel == 2)) {
                dir = -dir;
            }
            for (i = 0; i < 3; i++) {
                func_8001C258_main(models[i], 4, 0);
            }
            for (i = 1; i < 11; i++) {
                for (j = 0; j < 3; j++) {
                    Hu3DModelPosSet(models[j], sindf(j * 120 + baseAngle + i * 12 * dir) * 500.0f, 0.0f,
                                    cosdf(j * 120 + baseAngle + i * 12 * dir) * 500.0f);
                    func_8008A2A0_main(Hu3DData[models[j]].mtx, rotAngle);
                }
                alpha = i * 25;
                for (j = 0; j < gMes[prevSel].subMode; j++) {
                    HuSprTPLvlSet(gMes[prevSel].strGId[0], j + 1, 255.0f - alpha);
                }
                for (j = 0; j < gMes[D_80109B32_mgenter].subMode; j++) {
                    HuSprTPLvlSet(gMes[D_80109B32_mgenter].strGId[0], j + 1, alpha);
                }
                rotAngle += 3.0f;
                HuPrcVSleep();
            }
            prevSel = D_80109B32_mgenter;
            for (i = 0; i < 3; i++) {
                if (Hu3DData[models[i]].pos.z > 0.0f) {
                    func_8001C258_main(models[i], 4, 0);
                } else {
                    func_8001C258_main(models[i], 4, 4);
                }
            }
            baseAngle = D_80109B32_mgenter * 120;
        }
        for (j = 0; j < 3; j++) {
            func_8008A2A0_main(Hu3DData[models[j]].mtx, rotAngle);
        }
        rotAngle += 3.0f;
        HuPrcVSleep();
    }
}

void func_801079B4_mgenter(void) {
    s16 size[2];
    u8 buf[16];
    u16 sprite;
    s16 i;
    s16 winId;
    s16 valueWinId;
    s16 value;
    s16 delta;
    s16 btn;

    D_800A11E6_main = -1;
    omAddPrcObj(func_80106568_mgenter, 0x3F00, 0x800, 0);
    sprite = func_801095F4_mgenter();
    func_801096EC_mgenter(D_800A6D40_main[D_80109B2A_mgenter].flags & 0x7FF);
    espPosSet(sprite, 0, -100);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    D_80109B24_mgenter = 0;
    for (i = 0; i < 11; i++) {
        espPosSet(sprite, sindf(i * 9.0f) * 240.0f - 80.0f, 100);
        HuPrcVSleep();
    }
    HuWinMesMaxSizeGet(1, size, 0x4601);
    winId = HuWinExCreate(-1, (320 - size[0]) / 2, 180, size[0], size[1], 0);
    for (i = 0; i < 4; i++) {
        buf[i] = 0xA0;
    }
    buf[i] = '\0';
    HuWinInsertMesSizeGet((u32)buf, 0);
    HuWinMesMaxSizeGet(1, size, 0x4602);
    valueWinId = HuWinExCreate(-1, (320 - size[0]) / 2, 155, size[0], size[1], 0);
    HuWinMesSpeedSet(winId, 0);
    HuWinExAnimIn(winId);
    HuWinMesSet(winId, 0x4601, -1, -1);
    value = 100;
    func_80107E5C_mgenter(valueWinId, value, buf);
    HuWinMesSet(valueWinId, 0x4602, -1, -1);
    while (HuWinStatGet(valueWinId) != 0) {
        HuPrcVSleep();
    }
    HuWinExAnimIn(valueWinId);
    while (TRUE) {
        btn = D_800D0590_main[D_80109B74_mgenter];
        if (btn & 0x800) {
            delta = 100;
        } else {
            delta = (btn & 0x400) ? -100 : 0;
        }
        if (value == 1000 && delta > 0) {
            value = 100;
        } else if (value + delta >= 1000) {
            value = 1000;
        } else if (value + delta < 100) {
            value = 1000;
        } else {
            value += delta;
        }
        if (delta != 0) {
            func_80107E5C_mgenter(valueWinId, value, buf);
            HuWinMesSet(valueWinId, 0x4602, -1, -1);
        }
        btn = D_800D5558_main[D_80109B74_mgenter];
        if (btn & 0x8000) {
            HuAudFXPlay(2);
            D_800CB894_main = value;
            break;
        }
        if (btn & 0x4000) {
            HuAudFXPlay(4);
            D_80109B7C_mgenter = 0;
            D_80109AA4_mgenter = 1;
            D_80109AA6_mgenter = 1;
            while (TRUE) {
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
    func_801087C0_mgenter();
    HuWinKill(winId);
    HuWinKill(valueWinId);
    D_80109B7C_mgenter = 2;
    D_80109B76_mgenter = func_800341C0_main(GwSystem.minigame_index);
    D_80109B98_mgenter = 0;
    D_80109AA4_mgenter = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_80107E5C_mgenter(s16 winId, s16 value, u8 *buf) {
    s16 i;

    sprintf((char *)buf, "%04d", value);
    if (buf[0] == '0') {
        buf[0] = 0x1A;
    }
    for (i = 0; i < 4; i++) {
        if (buf[i] >= '0' && buf[i] <= '9') {
            buf[i] += 0x70;
        }
    }
    HuWinInsertMesSet(winId, (u32)buf, 0);
}

void func_80107F0C_mgenter(void) {
    u16 sprite;
    s16 i;
    f32 t;
    f32 x;

    D_80109B24_mgenter = -1;
    sprite = func_801095F4_mgenter();
    func_801096EC_mgenter((D_800A6D40_main[D_80109B2A_mgenter].flags & 0x7FF) + D_80109B2C_mgenter * 2);
    espDispOff(sprite);
    D_80109B26_mgenter = -1;
    while (TRUE) {
        switch (D_80109B26_mgenter) {
            case 0:
                espDispOn(sprite);
                for (i = 0; i < 11; i++) {
                    x = sindf(i * 9.0f) * 240.0f - 80.0f;
                    espPosSet(sprite, x, D_80109AA0_mgenter);
                    HuPrcVSleep();
                }
                D_80109B26_mgenter = -1;
                break;
            case 1:
                for (i = 1; i < 11; i++) {
                    t = sindf(i * 9.0f);
                    D_80109AA0_mgenter = 115.0f - t * 35.0f;
                    espPosSet(sprite, 160, D_80109AA0_mgenter);
                    espScaleSet(sprite, 1.0f - t * 0.2f, 1.0f - t * 0.2f);
                    t = 1.0f - t;
                    Hu3DFogSet((s16)(970.0f - t * 100.0f), (s16)(975.0f - t * 100.0f), 255, 255, 255);
                    HuPrcVSleep();
                }
                D_80109B26_mgenter = -1;
                break;
            case 2:
                for (i = 1; i < 11; i++) {
                    t = 1.0f - sindf(i * 9.0f);
                    D_80109AA0_mgenter = 115.0f - t * 35.0f;
                    espPosSet(sprite, 160, D_80109AA0_mgenter);
                    espScaleSet(sprite, 1.0f - t * 0.2f, 1.0f - t * 0.2f);
                    t = 1.0f - t;
                    Hu3DFogSet((s16)(970.0f - t * 100.0f), (s16)(975.0f - t * 100.0f), 255, 255, 255);
                    HuPrcVSleep();
                }
                D_80109B26_mgenter = -1;
                break;
        }
        if (D_80109B30_mgenter != 0) {
            for (i = 1; i < 6; i++) {
                x = (1.0f - cosdf(i * 18.0f)) * 240.0f * D_80109B30_mgenter + 160.0f;
                espPosSet(sprite, x, D_80109AA0_mgenter);
                HuPrcVSleep();
            }
            D_80109B2C_mgenter += D_80109B30_mgenter;
            if (D_80109B2C_mgenter >= D_80109B2E_mgenter) {
                D_80109B2C_mgenter = 0;
            }
            if (D_80109B2C_mgenter < 0) {
                D_80109B2C_mgenter = D_80109B2E_mgenter - 1;
            }
            func_801096EC_mgenter((D_800A6D40_main[D_80109B2A_mgenter].flags & 0x7FF) + D_80109B2C_mgenter * 2);
            for (i = 1; i < 6; i++) {
                x = -(1.0f - sindf(i * 18.0f)) * 240.0f * D_80109B30_mgenter + 160.0f;
                espPosSet(sprite, x, D_80109AA0_mgenter);
                HuPrcVSleep();
            }
            D_80109B30_mgenter = 0;
        }
        HuPrcVSleep();
    }
}

void func_80108560_mgenter(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    D_80109B34_mgenter = arg0;
    D_80109B36_mgenter = arg2;
    D_80109B38_mgenter = arg1;
    D_80109B3A_mgenter = arg3;
    D_80109B20_mgenter = 1;
}

void func_80108590_mgenter(void) {
    s8 prevState = 0;
    s16 fading = 0;
    s16 data1;
    s16 data2;
    s16 sprite1;
    s16 sprite2;
    s16 alpha;
    s16 prevAlpha;
    s16 step;

    D_80109B22_mgenter = 0;
    D_80109B20_mgenter = 0;
    data1 = func_8000B838_main(0x140012);
    data2 = func_8000B838_main(0x140013);
    sprite1 = espEntry(data1, 0, 1);
    sprite2 = espEntry(data2, 0, 1);
    espPriSet(sprite1, 0x4800);
    espPriSet(sprite2, 0x4800);
    espPosSet(sprite1, 160, 120);
    espPosSet(sprite2, 160, 120);
    espDispOff(sprite1);
    espDispOff(sprite2);
    alpha = 0;
    step = 0;
    while (TRUE) {
        HuPrcVSleep();
        if (prevState != D_80109B22_mgenter) {
            prevState = D_80109B22_mgenter;
            fading = 1;
            if (D_80109B22_mgenter != 0) {
                step = 63;
            } else {
                step = -63;
            }
        }
        if (fading) {
            prevAlpha = alpha;
            alpha += step;
            if (alpha >= 255) {
                fading = 0;
                alpha = 255;
            } else if (alpha <= 0) {
                fading = 0;
                alpha = 0;
            }
            if (alpha != 0) {
                if (prevAlpha == 0) {
                    espDispOn(sprite1);
                    espDispOn(sprite2);
                }
                espTPLvlSet(sprite1, alpha);
                espTPLvlSet(sprite2, alpha);
            } else {
                espDispOff(sprite1);
                espDispOff(sprite2);
            }
        }
        if (D_80109B20_mgenter != 0) {
            espPosSet(sprite1, D_80109B34_mgenter, D_80109B38_mgenter);
            espPosSet(sprite2, D_80109B36_mgenter, D_80109B3A_mgenter);
            D_80109B20_mgenter = 0;
        }
    }
}

void func_801087C0_mgenter(void) {
    s16 minigameType = D_800A6D40_main[D_80109B2A_mgenter].minigameType;
    s16 i;

    if (minigameType == 1 || minigameType == 2) {
        for (i = 0; i < 4; i++) {
            if (GwPlayer[i].group >= 2) {
                break;
            }
        }
        if (i == 4) {
            return;
        }
        if (minigameType == 2) {
            for (i = 0; i < 4; i++) {
                if (GwPlayer[i].group != 0) {
                    GwPlayer[i].group = 1;
                }
            }
        } else {
            for (i = 0; i < 4; i++) {
                if (GwPlayer[i].group < 2) {
                    GwPlayer[i].group = 0;
                } else {
                    GwPlayer[i].group = 1;
                }
            }
        }
    }
}

void func_80108934_mgenter(omObjData *obj) {
    if ((D_80109AA4_mgenter != 0) || (D_800D530C_main != 0)) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 8);
        if (D_80109AA6_mgenter == 0) {
            HuAudSeqFadeOut(0x3C);
        }
        obj->func = func_801089A0_mgenter;
    }
}

void func_801089A0_mgenter(omObjData *obj) {
    if (WipeStatGet() != 0) {
        return;
    }
    func_80109820_mgenter();
    HuWinAllKill();
    switch (D_80109B7C_mgenter) {
        case 0:
            omOvlReturnEx(1);
            break;
        case 2:
            omOvlCallEx(D_80109B76_mgenter, D_80109B98_mgenter, 0x111);
            break;
        case 1:
            omOvlGotoEx(D_80109B76_mgenter, D_80109B98_mgenter, 0x111);
            break;
    }
}
