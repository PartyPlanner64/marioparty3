#include "common.h"

extern s16 D_800D1FE0_main;
extern u16 D_80109AA4_mgenter;
extern s16 D_80109AA6_mgenter;
extern s16 D_80109B20_mgenter;
extern s16 D_80109B22_mgenter;
extern s16 D_80109B24_mgenter;
extern s16 D_80109B2A_mgenter;
extern s16 D_80109B2E_mgenter;
extern s16 D_80109B34_mgenter;
extern s16 D_80109B36_mgenter;
extern s16 D_80109B38_mgenter;
extern s16 D_80109B3A_mgenter;
extern s16 D_80109B76_mgenter;
extern s16 D_80109B7C_mgenter;
extern s16 D_80109B98_mgenter;

void func_80106710_mgenter(u8 *str);
void func_801089A0_mgenter(omObjData *);
void func_80109820_mgenter(void);

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_801059D0_mgenter);

void func_80105C60_mgenter(void) {
    Hu3DCamInit(1);
    Hu3DAnimInit(1);
    func_800142A0_main(0x19);
    omInitObjMan(0x33, 0x19);
    omOvlHisChg(0, 0x68, 0, 4);
    omOvlCallEx(0x70, 0, 2);
    _SetFlag(0xD);
    D_800D1FE0_main++;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_80105CD8_mgenter);

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_80106294_mgenter);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_8010677C_mgenter);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgenter/468AC0", D_80109AC0_mgenter);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgenter/468AC0", D_80109AC4_mgenter);

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_80106BD0_mgenter);

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_801079B4_mgenter);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_80107F0C_mgenter);

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
