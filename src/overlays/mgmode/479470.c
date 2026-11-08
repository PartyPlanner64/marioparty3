#include "common.h"
#include "overlays/mgmode.h"
#include "gcc/memory.h"
#include "gcc/string.h"

extern u8 D_8011B510_mgmode[256];
extern GAMEMES D_8011B810_mgmode;
extern u8 *D_8011B610_mgmode[3];
extern s16 D_8011B61C_mgmode;
extern s16 D_8011B61E_mgmode;
extern u8 D_800D2008_main;
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
extern s16 D_8011B8B8_mgmode[];
extern s16 D_8011B792_mgmode;
extern s16 D_8011B790_mgmode;
extern s16 D_8011B79C_mgmode;
extern s16 D_8011B798_mgmode;
extern s16 D_8011B788_mgmode;
extern s16 D_8011B78C_mgmode;
extern s16 D_8011B78E_mgmode;
extern s16 D_8011B624_mgmode;
extern s32 D_801194C8_mgmode;
extern s16 D_800D0418_main[8];
extern s16 D_801195BC_mgmode[];
extern u8 D_801195C4_mgmode[4];
extern u8 D_801195C8_mgmode[8];
extern s16 D_800D1F2C_main;
extern s16 D_800CE29C_main;
extern u8 D_80118EB1_mgmode;
extern s16 D_80118EB4_mgmode;
extern s16 D_8011B950_mgmode;
extern s16 D_8011B95A_mgmode;

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
void func_80118624_mgmode(s16 dstModel, s16 srcModel);
void func_801134C0_mgmode(void);
void func_801141EC_mgmode(s32 animate);
s16 func_801149F4_mgmode(void);
s16 func_80114C80_mgmode(void);
void func_80115C5C_mgmode(s16 value);
s16 func_80116B20_mgmode(void);
void func_80116C18_mgmode(s16 arg0);
void func_80115E9C_mgmode(s32 mesId, s16 x, s16 y);
void func_801162B4_mgmode(f32 arg0, f32 arg1);
void func_80118888_mgmode(s16 index);
void func_801188A4_mgmode(s16 index);
void func_80112F98_mgmode(void);
void func_80113204_mgmode(void);
void func_80115590_mgmode(void);
void func_80115848_mgmode(void);
void func_80114344_mgmode(void);
void func_80115BE8_mgmode(void);
void func_80115E20_mgmode(void);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80112200_mgmode);

void func_80112CF4_mgmode(void) {
    f32 radius;
    f32 t;
    s16 i;

    HuWinExAnimOut(D_8011B6A8_mgmode, 0);
    func_8001C258_main(D_8011B8A8_mgmode[18], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelScaleSet(D_8011B8A8_mgmode[18], 1.0f, 0.0f, 1.0f);
    func_80116ED4_mgmode(6, 20, 1, (void (*)(s16 *))-1);
    radius = 144.0f;
    Hu3DModelPosSet(D_8011B8A8_mgmode[4], -352.0f, 637.5f, -332.0f);
    Hu3DMotionShiftSet(D_8011B8A8_mgmode[4], D_8011B78C_mgmode, 0, 10, 0);
    for (i = 0; i < 11; i++) {
        if (i < 6) {
            Hu3DModelScaleSet(D_8011B8A8_mgmode[18], 1.0f, sindf(i / 5.0f * 90.0f), 1.0f);
        }
        t = i / 10.0f * 90.0f;
        HmfModelData[D_8011B8A8_mgmode[4]].pos.x = sindf(t) * radius + -352.0;
        HmfModelData[D_8011B8A8_mgmode[4]].pos.y = cosdf(t) * 200.0f + 63.75f;
        HmfModelData[D_8011B8A8_mgmode[4]].rot.y = cosdf(t) * 75.0f + 15.0f;
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(D_8011B8A8_mgmode[4], D_8011B788_mgmode, 0, 8, 2);
    HuAudFXPlay(0x51A);
    func_80115590_mgmode();
    func_80112F98_mgmode();
    func_80115848_mgmode();
    func_80113204_mgmode();
}

void func_80112F98_mgmode(void) {
    s16 i;

    D_800D1FE0_main = 10;
    D_800D1F2C_main = 0;
    func_801134C0_mgmode();
    func_80115C5C_mgmode(D_800D1FE0_main);
    HuPrcVSleep();
    func_801141EC_mgmode(1);
    HuWinMesSet(D_8011B6A8_mgmode, 0x5808, -1, -1);
    HuWinExAnimIn(D_8011B6A8_mgmode);
    D_800CE29C_main = func_801149F4_mgmode();
    HuWinInsertMesSet(D_8011B6A8_mgmode, D_800CE29C_main + 0x4700, 0);
    HuWinMesSet(D_8011B6A8_mgmode, 0x580A, -1, -1);
    while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
        HuPrcVSleep();
    }
    HuWinMesSet(D_8011B6A8_mgmode, 0x580B, -1, -1);
    D_800CB894_main = -1;
    do {
        D_800CB894_main = func_80114C80_mgmode();
        if (D_800CB894_main < 0) {
            HuWinMesSet(D_8011B6A8_mgmode, 0x5813, -1, -1);
            while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
                HuPrcVSleep();
            }
            if ((s16)HuWinChoiceGet(D_8011B6A8_mgmode, 0, 0) == 0) {
                return;
            }
            HuWinMesSet(D_8011B6A8_mgmode, 0x580B, -1, -1);
        }
    } while (D_800CB894_main < 0);
    D_800D1FE0_main -= D_800CB894_main;
    GwPlayer[0].gameCoin = D_800CB894_main;
    GwPlayer[0].group = 0;
    for (i = 1; i < 4; i++) {
        GwPlayer[i].group = 1;
    }
    _SetFlag(0xD);
    GwSystem.minigame_index = (u8)D_800CE29C_main + 1;
    omOvlHisChg(0, 0x69, 5, 0x84);
    D_80118EB1_mgmode = 1;
    D_8011B95A_mgmode = 0x70;
    D_8011B950_mgmode = 0;
    D_80118EB4_mgmode = 2;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_80113204_mgmode(void) {
    f32 radius;
    f32 t;
    s16 i;

    HuWinExAnimOut(D_8011B6A8_mgmode, 0);
    func_80116024_mgmode();
    func_80115BE8_mgmode();
    func_80116D4C_mgmode();
    D_801194C4_mgmode = -1;
    func_80114344_mgmode();
    func_80115E20_mgmode();
    HuAudFXPlay(0x519);
    Hu3DMotionShiftSet(D_8011B8A8_mgmode[4], D_8011B78E_mgmode, 0, 8, 0);
    radius = 144.0f;
    for (i = 0; i < 9; i++) {
        if (i < 6) {
            Hu3DModelScaleSet(D_8011B8A8_mgmode[18], 1.0f, cosdf(i / 5.0f * 90.0f), 1.0f);
        }
        t = i / 8.0f * 90.0f;
        HmfModelData[D_8011B8A8_mgmode[4]].pos.x = cosdf(t) * radius + -352.0;
        HmfModelData[D_8011B8A8_mgmode[4]].pos.y = sindf(t) * 100.0f + 63.75f;
        HmfModelData[D_8011B8A8_mgmode[4]].rot.y = -sindf(t) * 100.0f + 15.0f;
        HuPrcVSleep();
    }
    Hu3DModelPosSet(D_8011B8A8_mgmode[4], -436.0f, 0.0f, 92.0f);
    HmfModelData[D_8011B8A8_mgmode[4]].rot.y = 100.0f;
    Hu3DMotionShiftSet(D_8011B8A8_mgmode[4], D_8011B788_mgmode, 0, 8, 0);
    func_80116ED4_mgmode(2, 20, 1, (void (*)(s16 *))-1);
    func_8001C258_main(D_8011B8A8_mgmode[18], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_801134C0_mgmode(void) {
    u8 counts[4] = { 0, 0, 0, 0 };
    s16 attempt;
    s16 i;
    s16 type;

    for (attempt = 0; attempt < 100; attempt++) {
        for (i = 0; i < 4; i++) {
            counts[i] = 0;
        }
        type = rand8() & 3;
        D_800D0418_main[0] = type;
        counts[type]++;
        for (i = 1; i < 8; i++) {
            do {
                type = rand8() & 3;
            } while (D_800D0418_main[i - 1] == type);
            counts[type]++;
            if (D_801195C4_mgmode[type] < counts[type]) {
                break;
            }
            D_800D0418_main[i] = type;
        }
        if (i == 8 && D_800D0418_main[0] != D_800D0418_main[7]) {
            break;
        }
    }
    if (attempt == 100) {
        for (i = 0; i < 8; i++) {
            D_800D0418_main[i] = D_801195C8_mgmode[i];
        }
    }
    for (i = 0; i < 8; i++) {
        D_800D0418_main[i] = D_801195BC_mgmode[D_800D0418_main[i]];
    }
}

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
        Hu3DMotionShiftSet(D_8011B8B8_mgmode[0], D_8011B796_mgmode, 0, 8, 0);
        func_8004AC5C_main(GwPlayer[0].chr + 0x287, 0);
    } else {
        Hu3DMotionShiftSet(D_8011B8B8_mgmode[0], D_8011B794_mgmode, 0, 8, 0);
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

s16 func_801149F4_mgmode(void) {
    s16 i;
    s16 prev;
    s16 type;
    s16 result;

    if (D_801194C4_mgmode == -1) {
        D_801194C4_mgmode = func_80116B20_mgmode();
        espPriSet(D_801194C4_mgmode, 15);
        espAttrSet(D_801194C4_mgmode, 0x5008);
        espPosSet(D_801194C4_mgmode, 184, 132);
        for (i = 0; i < 10; i++) {
            espTPLvlSet(D_801194C4_mgmode, i / 10.0f * 255.0f);
            HuPrcVSleep();
        }
    }
    prev = -1;
    type = rand8() & 3;
    func_80116C18_mgmode(D_800A6D40_main[D_801195BC_mgmode[type]].flags & 0x7FF);
    func_80115E9C_mgmode(D_801195BC_mgmode[type] + 0x4700, 184, 62);
    for (i = 0; i < 30; i++) {
        HuPrcVSleep();
        while (type == prev) {
            type = rand8() & 3;
        }
        prev = type;
        func_80116024_mgmode();
        func_80116C18_mgmode(D_800A6D40_main[D_801195BC_mgmode[type]].flags & 0x7FF);
        func_80115E9C_mgmode(D_801195BC_mgmode[type] + 0x4700, 184, 62);
        HuAudFXPlay(0x104);
    }
    HuPrcVSleep();
    result = D_800D0418_main[D_800D1F2C_main];
    func_80116024_mgmode();
    func_80116C18_mgmode(D_800A6D40_main[result].flags & 0x7FF);
    func_80115E9C_mgmode(result + 0x4700, 184, 62);
    HuPrcVSleep();
    HuAudFXPlay(0x105);
    return result;
}

s16 func_80114C80_mgmode(void) {
    s16 value = 0;
    s16 delta;

    func_80115A9C_mgmode(184, 126, 0);
    while (TRUE) {
        HuPrcVSleep();
        if ((D_800D5558_main[D_8011B808_mgmode] & A_BUTTON) && value != 0) {
            HuAudFXPlay(0x247);
            break;
        }
        if (D_800D5558_main[D_8011B808_mgmode] & B_BUTTON) {
            HuAudFXPlay(4);
            value = -1;
            break;
        }
        if (D_800D0590_main[D_8011B808_mgmode] & L_JPAD) {
            delta = 10;
        } else if (D_800D0590_main[D_8011B808_mgmode] & R_JPAD) {
            delta = -10;
        } else if (D_800D0590_main[D_8011B808_mgmode] & U_JPAD) {
            delta = 1;
        } else if (D_800D0590_main[D_8011B808_mgmode] & D_JPAD) {
            delta = -1;
        } else {
            delta = 0;
        }
        if (delta != 0) {
            HuAudFXPlay(0x246);
        }
        if ((value == D_800D1FE0_main || value == 100) && delta > 0) {
            value = 0;
        } else if (value + delta >= 100 || value + delta > D_800D1FE0_main) {
            value = D_800D1FE0_main;
            if (value > 100) {
                value = 100;
            }
        } else if (value + delta < 0) {
            value = D_800D1FE0_main;
            if (value > 100) {
                value = 100;
            }
        } else {
            value += delta;
        }
        func_80115BB8_mgmode(value);
        func_80115CAC_mgmode(D_800D1FE0_main - value);
    }
    return value;
}

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

void func_80114FA0_mgmode(void) {
    s16 model = D_8011B8B8_mgmode[7];
    s16 camera;
    f32 scale;
    f32 y;
    s16 i;

    camera = func_8000CED8_main(0xB0004, 0x2A9);
    Hu3DModelCameraSet(camera, 2);
    func_8000D018_main(camera, 50.0f);
    func_8000CD00_main(camera, 2.0f, 20.0f, 0.0f);
    Hu3DMotionShiftSet(D_8011B8B8_mgmode[0], D_8011B790_mgmode, 0, 8, 0);
    func_8001C258_main(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelPosSet(model, 2.0f, 500.0f, -382.0f);
    func_8000CFA4_main(camera, 2.0f, 500.0f, -332.0f);
    Hu3DModelRotSet(model, 30.0f, 80.0f, 3.0f);
    func_80088800_main(HmfModelData[model].mtx, 0.0f, 0.0f, 20.0f);
    scale = 1.0f;
    HuAudFXPlay(0x249);
    for (i = 0; i < 51; i++) {
        y = (1.0f - sindf(i / 50.0f * 90.0f)) * 400.0f + 100.0f;
        HmfModelData[model].pos.y = y;
        func_8000CFA4_main(camera, 2.0f, y + 30.0f, -332.0f);
        if (i == 10) {
            Hu3DMotionShiftSet(D_8011B8B8_mgmode[0], D_8011B79C_mgmode, 0, 8, 0);
        }
        if (i == 40) {
            Hu3DMotionShiftSet(D_8011B8B8_mgmode[0], D_8011B794_mgmode, 0, 8, 0);
            RepeatVibrator(D_8011B808_mgmode, 20, 0, 20);
        }
        if (i > 30) {
            scale -= 0.1f;
            if (scale < 0.0f) {
                scale = 0.0f;
            }
            Hu3DModelScaleSet(model, scale, scale, scale);
        }
        HuPrcVSleep();
    }
    func_8001C258_main(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8000D044_main(camera);
}

void func_801152C0_mgmode(void) {
    s16 i;

    D_801194C8_mgmode = 0;
    HuAudFXPlay(0x248);
    func_80116260_mgmode();
    HuSprDispOn(D_8011B61E_mgmode, 0);
    for (i = 0; i < 31; i++) {
        if (i == 15) {
            func_80118888_mgmode(D_8011B624_mgmode);
        }
        if (i == 25) {
            Hu3DMotionShiftSet(D_8011B8B8_mgmode[0], D_8011B798_mgmode, 0, 8, 0);
            func_8004AC5C_main(GwPlayer[0].chr + 0x263, 0);
        }
        HuSprTPLvlSet(D_8011B61E_mgmode, 0, i / 30.0f * 220.0f);
        func_801162B4_mgmode(186.0f, sindf(i / 30.0f * 90.0f) * 10.0f);
        HuPrcVSleep();
    }
    func_80114614_mgmode(8);
    D_801194C8_mgmode = 1;
    do {
        HuPrcVSleep();
    } while (D_801194C8_mgmode != 0);
    for (i = 0; i < 11; i++) {
        HuSprTPLvlSet(D_8011B61E_mgmode, 0, (1.0f - i / 30.0f) * 220.0f);
        HuPrcVSleep();
    }
    HuSprDispOff(D_8011B61E_mgmode, 0);
    func_801188A4_mgmode(D_8011B624_mgmode);
    omDelPrcObj(NULL);
}

void func_80115590_mgmode(void) {
    s16 model = D_8011B8B8_mgmode[0];
    s16 other = D_8011B8B8_mgmode[9];
    f32 dx = 198.0f;
    f32 dz = 210.0f;
    f32 angle;
    f32 t;
    f32 x;
    f32 z;
    s16 i;

    func_8001C258_main(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8001C258_main(other, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionSet(model, D_8011B792_mgmode);
    func_8001C814_main(model, 2, 2);
    angle = atan2df(dx, dz) + 180.0f;
    Hu3DModelPosSet(model, 200.0f, 0.0f, -122.0f);
    Hu3DModelRotSet(model, 0.0f, angle, 0.0f);
    for (i = 0; i < 16; i++) {
        t = 1.0f - i / 15.0f;
        x = dx * t + 2.0f;
        z = dz * t + -332.0f;
        Hu3DModelPosSet(model, x, 0.0f, z);
        func_80118624_mgmode(other, model);
        if (i < 12 && i % 5 == 0) {
            func_8004AC5C_main(GwPlayer[0].chr + 0x29, 0);
        }
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(model, D_8011B790_mgmode, 0, 8, 2);
    for (i = 0; i < 9; i++) {
        t = 1.0f - i / 8.0f;
        HmfModelData[model].rot.y = t * angle;
        HuPrcVSleep();
    }
}

void func_80115848_mgmode(void) {
    s16 model = D_8011B8B8_mgmode[0];
    s16 other = D_8011B8B8_mgmode[9];
    f32 dx = -198.0f;
    f32 dz = -210.0f;
    f32 angle;
    f32 t;
    f32 x;
    f32 z;
    s16 i;

    Hu3DMotionShiftSet(model, D_8011B792_mgmode, 0, 8, 2);
    angle = atan2df(dx, dz) + 180.0f;
    for (i = 0; i < 9; i++) {
        t = i / 8.0f;
        HmfModelData[model].rot.y = t * angle;
        HuPrcVSleep();
    }
    for (i = 0; i < 16; i++) {
        t = 1.0f - i / 15.0f;
        x = dx * t + 200.0f;
        z = dz * t + -122.0f;
        Hu3DModelPosSet(model, x, 0.0f, z);
        func_80118624_mgmode(other, model);
        if (i < 12 && i % 5 == 0) {
            func_8004AC5C_main(GwPlayer[0].chr + 0x29, 0);
        }
        HuPrcVSleep();
    }
    func_8001C258_main(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(other, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

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

void func_801162B4_mgmode(f32 centerX, f32 angle) {
    u8 *dst;
    f32 spread;
    s16 y;
    s16 x;
    s16 left;
    s16 right;
    u8 *p;
    u8 pixel;

    dst = D_8011B610_mgmode[D_800D2008_main];
    spread = sindf(angle);
    for (y = 0; y < 120; y++) {
        left = centerX - spread * (y + 100);
        right = centerX + spread * (y + 100);
        for (x = 0; x < 320; x++) {
            if (left < x && x < right) {
                pixel = *dst;
                *dst = (x & 1) ? pixel & 0xF0 : pixel & 0xF;
            } else {
                pixel = *dst;
                *dst = (x & 1) ? pixel | 0xF : pixel | 0xF0;
            }
            dst += x & 1;
        }

        p = &D_8011B610_mgmode[D_800D2008_main][(y * 320 + left - 1) / 2];
        *p &= ((left - 1) & 1) ? 0xF0 : 0xF;
        *p |= ((left - 1) & 1) ? 0xA : 0xA0;
        p = &D_8011B610_mgmode[D_800D2008_main][(y * 320 + right + 1) / 2];
        *p &= ((right + 1) & 1) ? 0xF0 : 0xF;
        *p |= ((right + 1) & 1) ? 0xA : 0xA0;
        p = &D_8011B610_mgmode[D_800D2008_main][(y * 320 + left) / 2];
        *p &= (left & 1) ? 0xF0 : 0xF;
        *p |= (left & 1) ? 0x4 : 0x40;
        p = &D_8011B610_mgmode[D_800D2008_main][(y * 320 + right) / 2];
        *p &= (right & 1) ? 0xF0 : 0xF;
        *p |= (right & 1) ? 0x4 : 0x40;
    }
    HuSprGet(D_8011B61E_mgmode, 0)->unk_84->unk00->unk00 = D_8011B610_mgmode[D_800D2008_main];
}
