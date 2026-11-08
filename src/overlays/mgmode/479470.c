#include "common.h"
#include "overlays/mgmode.h"
#include "gcc/memory.h"
#include "gcc/string.h"

extern u8 D_8011B510_mgmode[256];
extern GAMEMES D_8011B810_mgmode;
extern u8 *D_8011B610_mgmode[3];
extern s16 D_8011B61C_mgmode;
extern s16 D_8011B61E_mgmode;
extern MgmodeEsprite *D_801194C0_mgmode;
extern s16 D_801194C4_mgmode;
extern MgmodeEsprite *D_801195D0_mgmode;
extern MgmodeEspriteDef D_8011A270_mgmode[];
extern MgmodeEspriteDef D_8011A2C4_mgmode[];
extern s16 D_8011B8A8_mgmode[];
extern s16 D_8011B6A8_mgmode;
extern s16 D_8011B808_mgmode;
extern s16 D_800D1FE0_main;
extern s16 D_8011B794_mgmode;
extern s16 D_8011B796_mgmode;
extern s16 D_8011B8B8_mgmode;

void func_80115BB8_mgmode(s16 value);
void func_80115CAC_mgmode(s16 value);
void func_80115CDC_mgmode(MgmodeEsprite *sprites, s16 base, s16 value, s16 digits);
MgmodeEsprite *func_80116794_mgmode(MgmodeEspriteDef *defs);
void func_801168E0_mgmode(MgmodeEsprite *arg0);
void func_80116968_mgmode(MgmodeEsprite *arg0, s16 index, s16 arg2, s16 arg3);
void func_801169A0_mgmode(MgmodeEsprite *arg0, s16 index);
void func_801169C8_mgmode(MgmodeEsprite *arg0, s16 index);
void func_80116A48_mgmode(MgmodeEsprite *arg0, s16 index, f32 x, f32 y);
void func_80116AA8_mgmode(MgmodeEsprite *arg0, s16 index, s16 arg2);
void func_80116AEC_mgmode(MgmodeEsprite *arg0, s16 index, u16 arg2);
void func_80116024_mgmode(void);
void func_80116260_mgmode(void);
void func_801160A0_mgmode(s16 arg0);
void func_80116D4C_mgmode(void);
void func_80114614_mgmode(s16 index);
void func_80114804_mgmode(s16 arg0, s16 arg1, s16 arg2);
void func_80115A9C_mgmode(s16 x, s16 y, s16 value);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80112200_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80112CF4_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80112F98_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80113204_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801134C0_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801136EC_mgmode);

s32 func_80114048_mgmode(void) {
    s16 size[2];
    s32 result = FALSE;
    s16 winId;
    s16 choice;

    HuWinMesSet(D_8011B6A8_mgmode, 0x5813, -1, -1);
    while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
        HuPrcVSleep();
    }
    if ((s16)HuWinChoiceGet(D_8011B6A8_mgmode, 0, 0) == 0) {
        if (D_800D1FE0_main < 11) {
            result = TRUE;
        } else {
            HuWinExAnimOut(D_8011B6A8_mgmode, 0);
            HuWinMesMaxSizeGet(1, size, 0x5814);
            winId = HuWinExCreate(-1, (320 - size[0]) / 2, 224 - size[1], size[0], size[1], 0);
            HuWinActivePlayerSet(winId, 1 << D_8011B808_mgmode);
            HuWinExAnimIn(winId);
            HuWinMesSet(winId, 0x5814, -1, -1);
            while (HuWinStatGet(winId) != 0) {
                HuPrcVSleep();
            }
            choice = HuWinChoiceGet(winId, 0, 0);
            HuWinExAnimOut(winId, 0);
            HuWinKill(winId);
            if (choice == 0) {
                result = TRUE;
            }
        }
    }
    return result;
}

void func_801141EC_mgmode(s32 animate) {
    s16 i;
    f32 t;
    f32 scaleX;
    f32 scaleY;

    if (D_801194C0_mgmode == (MgmodeEsprite *)-1) {
        D_801194C0_mgmode = func_80116794_mgmode(D_8011A2C4_mgmode);
        if (animate) {
            HuAudFXPlay(0x243);
            func_80116A48_mgmode(D_801194C0_mgmode, 0, 0.0f, 0.0f);
            HuPrcSleep(5);
            for (i = 0; i < 11; i++) {
                t = i / 10.0f;
                scaleX = sindf(t * 90.0f);
                scaleY = cosdf(t * 270.0f + 90.0f);
                if (scaleY < 0.0f) {
                    scaleY = -scaleY;
                }
                func_80116A48_mgmode(D_801194C0_mgmode, 0, scaleX, scaleY);
                HuPrcVSleep();
            }
        }
        func_80116AEC_mgmode(D_801194C0_mgmode, 0, 20);
    }
}

void func_80114344_mgmode(void) {
    s16 i;
    f32 scale;

    HuAudFXPlay(0x244);
    for (i = 0; i < 11; i++) {
        scale = cosdf(i / 10.0f * 90.0f);
        func_80116A48_mgmode(D_801194C0_mgmode, 0, scale, scale);
        HuPrcVSleep();
    }
    func_801168E0_mgmode(D_801194C0_mgmode);
    D_801194C0_mgmode = (MgmodeEsprite *)-1;
}

void func_80114404_mgmode(void) {
    s16 rate = D_800CB894_main;
    s16 coins = GwPlayer[0].bonusCoin;
    s16 i;

    func_801169A0_mgmode(D_801194C0_mgmode, 1);
    func_80116968_mgmode(D_801194C0_mgmode, 1, 184, 46);
    func_801169A0_mgmode(D_801194C0_mgmode, 2);
    func_80116968_mgmode(D_801194C0_mgmode, 2, 184, 98);
    func_80115A9C_mgmode(184, 122, D_800D1FE0_main);
    func_80114804_mgmode(rate, 0, 0);
    func_80115BB8_mgmode(D_800D1FE0_main);
    func_80115CAC_mgmode(D_800D1FE0_main);
    HuPrcSleep(10);
    for (i = 0; i <= coins; i++) {
        func_80114804_mgmode(rate, i, rate * i);
        func_80115BB8_mgmode(D_800D1FE0_main + rate * i);
        func_80115CAC_mgmode(D_800D1FE0_main + rate * i);
        HuAudFXPlay(9);
        HuPrcSleep(2);
    }
    D_800D1FE0_main += coins * rate;
    if (coins == 0) {
        Hu3DMotionShiftSet(D_8011B8B8_mgmode, D_8011B796_mgmode, 0, 8, 0);
        func_8004AC5C_main(GwPlayer[0].chr + 0x287, 0);
    } else {
        Hu3DMotionShiftSet(D_8011B8B8_mgmode, D_8011B794_mgmode, 0, 8, 0);
        func_8004AC5C_main(GwPlayer[0].chr + 0x275, 0);
    }
    func_80114614_mgmode(8);
}

void func_80114614_mgmode(s16 index) {
    while (Hu3DMotionShiftTimeGet(D_8011B8A8_mgmode[index]) != -1.0f ||
           HmfModelData[D_8011B8A8_mgmode[index]].motTime <
               D_800CCF58_main[HmfModelData[D_8011B8A8_mgmode[index]].motId].unk02) {
        HuPrcVSleep();
    }
}

void func_801146D8_mgmode(void) {
    s16 i;
    s16 j;
    f32 scale;

    for (i = 0; i < 10; i++) {
        scale = 1.0f - i / 10.0f;
        for (j = 1; j < 21; j++) {
            func_80116A48_mgmode(D_801194C0_mgmode, j, scale, scale);
        }
        HuPrcVSleep();
    }
    for (j = 1; j < 21; j++) {
        func_801169C8_mgmode(D_801194C0_mgmode, j);
        func_80116A48_mgmode(D_801194C0_mgmode, j, 1.0f, 1.0f);
    }
}

void func_80114804_mgmode(s16 arg0, s16 arg1, s16 arg2) {
    s16 i;

    if (arg2 >= 10000) {
        arg2 = 9999;
    }
    func_80115CDC_mgmode(D_801194C0_mgmode, 3, arg0, 3);
    for (i = 0; i < 3; i++) {
        func_80116968_mgmode(D_801194C0_mgmode, i + 3, i * 16 + 104, 70);
    }
    func_80115CDC_mgmode(D_801194C0_mgmode, 8, arg1, 2);
    for (i = 0; i < 2; i++) {
        func_80116968_mgmode(D_801194C0_mgmode, i + 8, i * 16 + 168, 70);
    }
    func_80115CDC_mgmode(D_801194C0_mgmode, 11, arg2, 4);
    for (i = 0; i < 4; i++) {
        func_80116968_mgmode(D_801194C0_mgmode, i + 11, i * 16 + 216, 70);
    }
    func_801169A0_mgmode(D_801194C0_mgmode, 7);
    func_80116968_mgmode(D_801194C0_mgmode, 7, 152, 70);
    func_801169A0_mgmode(D_801194C0_mgmode, 10);
    func_80116AA8_mgmode(D_801194C0_mgmode, 10, 3);
    func_80116968_mgmode(D_801194C0_mgmode, 10, 200, 70);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801149F4_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80114C80_mgmode);

void func_80114EBC_mgmode(void) {
    s16 i;
    s16 tpLvl;

    for (i = 0; i < 10; i++) {
        tpLvl = (1.0f - i / 10.0f) * 255.0f;
        espTPLvlSet(D_801194C4_mgmode, tpLvl);
        func_801160A0_mgmode(tpLvl);
        HuPrcVSleep();
    }
    func_80116024_mgmode();
    func_80116D4C_mgmode();
    D_801194C4_mgmode = -1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80114FA0_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801152C0_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115590_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115848_mgmode);

void func_80115A9C_mgmode(s16 x, s16 y, s16 value) {
    s16 left;
    s16 i;

    left = x - 40;
    func_80116968_mgmode(D_801194C0_mgmode, 0xF, left, y);
    func_801169A0_mgmode(D_801194C0_mgmode, 0xF);
    func_80116968_mgmode(D_801194C0_mgmode, 0x10, x - 24, y);
    func_801169A0_mgmode(D_801194C0_mgmode, 0x10);
    for (i = 0; i < 4; i++) {
        func_80116968_mgmode(D_801194C0_mgmode, i + 0x11, left + (i + 2) * 16, y);
    }
    func_80115BB8_mgmode(value);
}

void func_80115BB8_mgmode(s16 value) {
    func_80115CDC_mgmode(D_801194C0_mgmode, 0x11, value, 4);
}

void func_80115BE8_mgmode(void) {
    s16 i;

    func_801169C8_mgmode(D_801194C0_mgmode, 0xF);
    func_801169C8_mgmode(D_801194C0_mgmode, 0x10);

    for (i = 0; i < 4; i++) {
        func_801169C8_mgmode(D_801194C0_mgmode, i + 0x11);
    }
}

void func_80115C5C_mgmode(s16 value) {
    if (D_801195D0_mgmode == (MgmodeEsprite *)-1) {
        D_801195D0_mgmode = func_80116794_mgmode(D_8011A270_mgmode);
        func_80115CAC_mgmode(value);
    }
}

void func_80115CAC_mgmode(s16 value) {
    func_80115CDC_mgmode(D_801195D0_mgmode, 2, value, 4);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/479470", D_8011A688_mgmode);

void func_80115CDC_mgmode(MgmodeEsprite *sprites, s16 base, s16 value, s16 digits) {
    u8 buf[8];
    s16 offset;
    s16 i;

    if (value >= 10000) {
        value = 9999;
    }
    sprintf((char *)buf, "%4d", value);
    offset = 4 - digits;
    for (i = 0; i < digits; i++) {
        if (buf[offset + i] < '0') {
            func_801169C8_mgmode(sprites, base + i);
        } else {
            func_801169A0_mgmode(sprites, base + i);
            func_80116AA8_mgmode(sprites, base + i, buf[offset + i] & 0xF);
        }
    }
}

void func_80115E20_mgmode(void) {
    func_801168E0_mgmode(D_801195D0_mgmode);
    D_801195D0_mgmode = (MgmodeEsprite *)-1;
}

void func_80115E4C_mgmode(void) {
    s16 i;

    for (i = 0; i < 16; i++) {
        D_8011B810_mgmode.strSprId[i] = D_8011B810_mgmode.strGId[i] = -1;
    }
}

void func_80115E9C_mgmode(s32 mesId, s16 x, s16 y) {
    u8 *str;
    s16 len;
    s16 count;
    s16 i;

    str = func_800364DC_main((void *)mesId);
    len = strlen((char *)str);
    count = 0;
    for (i = 0; i <= len; i++) {
        if (str[i] >= '0') {
            D_8011B510_mgmode[count++] = str[i];
        }
    }
    D_8011B510_mgmode[count] = 0;
    func_800365E8_main(str);
    D_8011B810_mgmode.subMode = count;
    GameMesStrCreate(&D_8011B810_mgmode, (char *)D_8011B510_mgmode, 0, -1, -1);
    for (i = 0; i < D_8011B810_mgmode.subMode; i++) {
        HuSprPriSet(D_8011B810_mgmode.strGId[0], i + 1, 10);
        HuSprScaleSet(D_8011B810_mgmode.strGId[0], i + 1, 0.7f, 1.0f);
    }
    HuSprPosSet(D_8011B810_mgmode.strGId[0], 0, x, y);
}

void func_80116024_mgmode(void) {
    s16 i;

    if (D_8011B810_mgmode.strGId[0] != GMES_ID_NONE) {
        GMesSprKill(&D_8011B810_mgmode);
        for (i = 0; i < 16; i++) {
            D_8011B810_mgmode.strSprId[i] = D_8011B810_mgmode.strGId[i] = GMES_ID_NONE;
        }
    }
}

void func_801160A0_mgmode(s16 arg0) {
    int i;

    i = 0;
    if (D_8011B810_mgmode.subMode > 0) {
        do {
            i++;
            HuSprTPLvlSet(D_8011B810_mgmode.strGId[0], (s16)i, arg0);
        } while ((s16)i < D_8011B810_mgmode.subMode);
    }
}

void func_8011611C_mgmode(void) {
    HuSprite *sprite;

    D_8011B61C_mgmode = func_8000B838_main(0x12003D);
    D_8011B61E_mgmode = HuSprGrpCreate(5, 0);
    HuSprGrpMemberSet(D_8011B61E_mgmode, 0, D_8011B61C_mgmode, 0);
    HuSprAttrReset(D_8011B61E_mgmode, 0, 0xFFFF);
    HuSprAttrSet(D_8011B61E_mgmode, 0, 0x9008);
    HuSprPosSet(D_8011B61E_mgmode, 0, 160, 120);
    HuSprPriSet(D_8011B61E_mgmode, 0, 15);
    HuSprScaleSet(D_8011B61E_mgmode, 0, 1.0f, 2.0f);
    sprite = HuSprGet(D_8011B61E_mgmode, 0);
    HuMemFree(sprite->unk_84->unk00->unk00);
    D_8011B610_mgmode[0] = HuMemAllocTag(0x4B00, 0x7918);
    D_8011B610_mgmode[1] = HuMemAllocTag(0x4B00, 0x7918);
    D_8011B610_mgmode[2] = HuMemAllocTag(0x4B00, 0x7918);
    sprite->unk_84->unk00->unk00 = D_8011B610_mgmode[0];
    func_80116260_mgmode();
}

void func_80116260_mgmode(void) {
    memset(D_8011B610_mgmode[0], 0xFF, 0x4B00);
    memset(D_8011B610_mgmode[1], 0xFF, 0x4B00);
    memset(D_8011B610_mgmode[2], 0xFF, 0x4B00);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801162B4_mgmode);
