#include "common.h"

extern s16 D_8010D150_game_guys_lucky_7[][3]; // window x, y, lines
extern u16 D_8010D18E_game_guys_lucky_7;      // main state
extern u16 D_8010D190_game_guys_lucky_7;      // main state timer
extern char *D_8010D194_game_guys_lucky_7[];  // character names
extern s16 D_8010D1B4_game_guys_lucky_7;      // state
extern s16 D_8010D1B6_game_guys_lucky_7;      // timer
extern u16 D_8010D1B8_game_guys_lucky_7;      // state
extern u16 D_8010D1BA_game_guys_lucky_7;
extern f32 D_8010D1BC_game_guys_lucky_7;
extern u16 D_8010D1C0_game_guys_lucky_7;
extern u16 D_8010D1C2_game_guys_lucky_7; // state
extern u16 D_8010D1C4_game_guys_lucky_7;
extern u16 D_8010D1C6_game_guys_lucky_7; // state
extern u16 D_8010D1C8_game_guys_lucky_7; // timer
extern u16 D_8010D1CA_game_guys_lucky_7; // countdown tick timer
extern u16 D_8010D1CC_game_guys_lucky_7; // countdown seconds
extern u16 D_8010D1CE_game_guys_lucky_7;
extern u16 D_8010D1D0_game_guys_lucky_7;
extern char D_8010D5D0_game_guys_lucky_7[];
extern s16 D_8010D6D0_game_guys_lucky_7;
extern Process *D_8010D6D4_game_guys_lucky_7;
extern Process *D_8010D6D8_game_guys_lucky_7;
// [0] player index, [1] pad, [2] chr, [3] cpu flag, [4] cpu difficulty, [5] coins, [6] coins
extern u16 D_8010D6DC_game_guys_lucky_7[7];
extern s16 D_8010D726_game_guys_lucky_7;
extern u16 D_8010D728_game_guys_lucky_7;
extern f32 D_8010D72C_game_guys_lucky_7;
extern f32 D_8010D730_game_guys_lucky_7;
extern f32 D_8010D734_game_guys_lucky_7;
extern f32 D_8010D738_game_guys_lucky_7;
extern s16 D_8010D73C_game_guys_lucky_7;
extern u16 D_8010D73E_game_guys_lucky_7;
extern s16 D_8010D740_game_guys_lucky_7;
extern u16 D_8010D744_game_guys_lucky_7;
extern s16 D_8010D746_game_guys_lucky_7;
extern f32 D_8010D74C_game_guys_lucky_7;
extern f32 D_8010D754_game_guys_lucky_7;
extern s16 D_8010D758_game_guys_lucky_7;
extern f32 D_8010D75C_game_guys_lucky_7;
extern f32 D_8010D760_game_guys_lucky_7;
extern f32 D_8010D764_game_guys_lucky_7;
extern s16 D_8010D768_game_guys_lucky_7;
extern u16 D_8010D76A_game_guys_lucky_7;
extern u16 D_8010D76C_game_guys_lucky_7;
extern u16 D_8010D770_game_guys_lucky_7;
extern u16 D_8010D772_game_guys_lucky_7;
extern u16 D_8010D774_game_guys_lucky_7;
extern u16 D_8010D776_game_guys_lucky_7;
extern u16 D_8010D778_game_guys_lucky_7;
extern u16 D_8010D77A_game_guys_lucky_7;
extern u16 D_8010D77C_game_guys_lucky_7;
extern s16 D_8010D800_game_guys_lucky_7;
extern s16 D_8010D802_game_guys_lucky_7;

void func_80105A28_game_guys_lucky_7(void);
void func_80105AC0_game_guys_lucky_7(void);
void func_80105AC8_game_guys_lucky_7(void);
void func_80105C08_game_guys_lucky_7(void);
void func_80105C24_game_guys_lucky_7(void);
void func_80105E34_game_guys_lucky_7(omObjData *object);
void func_80105F70_game_guys_lucky_7(omObjData *object);
void func_80106248_game_guys_lucky_7(omObjData *object);
void func_80106370_game_guys_lucky_7(void);
void func_80106500_game_guys_lucky_7(omObjData *object);
void func_80106854_game_guys_lucky_7(omObjData *object);
void func_80106A0C_game_guys_lucky_7(omObjData *object);
void func_80106CF4_game_guys_lucky_7(omObjData *object);
void func_80107090_game_guys_lucky_7(void);
void func_80107270_game_guys_lucky_7(void);
void func_80107668_game_guys_lucky_7(omObjData *object);
void func_8010783C_game_guys_lucky_7(omObjData *object);
void func_80107AC4_game_guys_lucky_7(omObjData *object);
void func_80107DE4_game_guys_lucky_7(omObjData *object);
void func_80107EEC_game_guys_lucky_7(omObjData *object);
void func_80107F44_game_guys_lucky_7(omObjData *object);
void func_80107F6C_game_guys_lucky_7(void);
void func_80107F98_game_guys_lucky_7(omObjData *object);
void func_801087B4_game_guys_lucky_7(omObjData *object);
void func_801092B0_game_guys_lucky_7(omObjData *object);
void func_80109FA4_game_guys_lucky_7(omObjData *object);
void func_8010A0DC_game_guys_lucky_7(omObjData *object);
void func_8010A278_game_guys_lucky_7(omObjData *object);
void func_8010A3B8_game_guys_lucky_7(omObjData *object);
void func_8010A8A4_game_guys_lucky_7(omObjData *object);
s16 func_8010AD44_game_guys_lucky_7(s16 x, s16 y, s16 lines);
void func_8010ADB8_game_guys_lucky_7(s16 win);
void func_8010ADF8_game_guys_lucky_7(s16 win, s16 player, s16 mode);
s16 func_8010AF44_game_guys_lucky_7(s16 win, s16 player, s16 mode, s16 count);
s16 func_8010B13C_game_guys_lucky_7(s16 win, s16 player, s16 mode, s16 count);
void func_8010B830_game_guys_lucky_7(s16 x, s16 y);
s16 func_8010BB88_game_guys_lucky_7(void);
void func_8010C670_game_guys_lucky_7(s32 arg0);

void func_801059A0_game_guys_lucky_7(void) {
    func_80105A28_game_guys_lucky_7();
}

s32 func_801059BC_game_guys_lucky_7(f32 arg0) {
    u8 randomByte1 = rand8();
    u8 randomByte2 = rand8();
    s32 shiftedByte1 = (randomByte1 << 8);
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;

    return scaledRandom;
}

void func_80105A28_game_guys_lucky_7(void) {
    func_8001FE20_main(32);
    func_800142A0_main(32);
    omInitObjMan(32, 32);
    func_8004A208_main();
    func_80105AC0_game_guys_lucky_7();
    func_80105AC8_game_guys_lucky_7();
    func_80105C08_game_guys_lucky_7();
    func_80105C24_game_guys_lucky_7();
    omAddObj(1000, 0, 0, -1, func_80105E34_game_guys_lucky_7);
    omAddObj(2000, 0, 0, -1, func_80107F44_game_guys_lucky_7);
}

void func_80105AC0_game_guys_lucky_7(void) {
}

void func_80105AC8_game_guys_lucky_7(void) {
    s32 camIndex;

    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(camIndex, 6.57f, 2000.0f, 8500.0f);
    CZoom = 8075.0f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 350.0f;
    Center.z = 0.0f;
}

void func_80105C08_game_guys_lucky_7(void) {
    HuWinInit();
}

void func_80105C24_game_guys_lucky_7(void) {
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    switch (i) {
        case 0:
            D_8010D6DC_game_guys_lucky_7[0] = 0;
            break;
        case 1:
            D_8010D6DC_game_guys_lucky_7[0] = 1;
            break;
        case 2:
            D_8010D6DC_game_guys_lucky_7[0] = 2;
            break;
        case 3:
            D_8010D6DC_game_guys_lucky_7[0] = 3;
            break;
        default:
            D_8010D6DC_game_guys_lucky_7[0] = 0;
            break;
    }
    D_8010D6DC_game_guys_lucky_7[1] = GwPlayer[D_8010D6DC_game_guys_lucky_7[0]].pad;
    D_8010D6DC_game_guys_lucky_7[2] = GwPlayer[D_8010D6DC_game_guys_lucky_7[0]].chr;
    if (GwPlayer[D_8010D6DC_game_guys_lucky_7[0]].stat & 1) {
        D_8010D6DC_game_guys_lucky_7[3] = 1;
        D_8010D6DC_game_guys_lucky_7[4] = GwPlayer[D_8010D6DC_game_guys_lucky_7[0]].cpu_difficulty;
        D_8010D802_game_guys_lucky_7 = GwCommon.unkA0;
        if (D_8010D802_game_guys_lucky_7 <= 0) {
            D_8010D802_game_guys_lucky_7 = 0;
        } else if (D_8010D802_game_guys_lucky_7 >= 2) {
            D_8010D802_game_guys_lucky_7 = 2;
        }
    } else {
        D_8010D6DC_game_guys_lucky_7[3] = 0;
        D_8010D6DC_game_guys_lucky_7[4] = 0;
    }
    D_8010D6DC_game_guys_lucky_7[5] = D_8010D6DC_game_guys_lucky_7[6] =
        GwPlayer[D_8010D6DC_game_guys_lucky_7[0]].gameCoin;
    if (D_8010D6DC_game_guys_lucky_7[5] >= 999) {
        D_8010D6DC_game_guys_lucky_7[5] = 999;
        D_8010D6DC_game_guys_lucky_7[6] = 999;
    } else if (D_8010D6DC_game_guys_lucky_7[5] == 0) {
        D_8010D6DC_game_guys_lucky_7[5] = 0;
        D_8010D6DC_game_guys_lucky_7[6] = 0;
    }
}

void func_80105E34_game_guys_lucky_7(omObjData *object) {
    func_80107F6C_game_guys_lucky_7();
    func_8010B830_game_guys_lucky_7(160, 194);
    omAddObj(10, 10, 10, -1, func_80107F98_game_guys_lucky_7);
    omAddObj(20, 10, 20, -1, func_801087B4_game_guys_lucky_7);
    omAddObj(30, 10, 20, -1, func_801092B0_game_guys_lucky_7);
    omAddObj(40, 10, 10, -1, func_8010A3B8_game_guys_lucky_7);
    omAddObj(41, 10, 10, -1, func_80109FA4_game_guys_lucky_7);
    omAddObj(42, 10, 10, -1, func_8010A0DC_game_guys_lucky_7);
    omAddObj(42, 10, 10, -1, func_8010A278_game_guys_lucky_7);
    omAddObj(50, 10, 10, -1, func_8010A8A4_game_guys_lucky_7);
    object->func = func_80105F70_game_guys_lucky_7;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D310_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D31C_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D32C_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D334_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D340_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D34C_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D358_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D364_game_guys_lucky_7);

void func_80105F70_game_guys_lucky_7(omObjData *object) {
    switch (D_8010D18E_game_guys_lucky_7) {
        case 0:
            WipeCreateIn(0xFF, 0x10);
            D_8010D18E_game_guys_lucky_7++;
            break;
        case 1:
            object->func = func_80106248_game_guys_lucky_7;
            D_8010D18E_game_guys_lucky_7++;
            break;
        case 2:
            if (D_8010D190_game_guys_lucky_7++ == 0) {
                GMesCreate(9);
                D_8010D190_game_guys_lucky_7 = 1;
            } else if (GMesStatGet() == 0) {
                D_8010D190_game_guys_lucky_7 = 0;
                D_8010D18E_game_guys_lucky_7++;
            }
            break;
        case 3:
            object->func = func_80106854_game_guys_lucky_7;
            D_8010D18E_game_guys_lucky_7++;
            break;
        case 4:
            if (D_8010D190_game_guys_lucky_7++ == 0) {
                GMesCreate(0x14);
                HuAudSeqFadeOut(120);
            } else if (D_8010D190_game_guys_lucky_7 == 15) {
                if (D_8010D776_game_guys_lucky_7 >= 8) {
                    object->func = func_80107AC4_game_guys_lucky_7;
                }
            } else if (GMesStatGet() == 0) {
                D_8010D190_game_guys_lucky_7 = 0;
                D_8010D18E_game_guys_lucky_7++;
            }
            break;
        case 5:
            object->func = func_80107668_game_guys_lucky_7;
            D_8010D18E_game_guys_lucky_7++;
            break;
        case 6:
            if (D_8010D190_game_guys_lucky_7++ == 0) {
                switch (D_8010D77A_game_guys_lucky_7) {
                    case 1:
                        HuAudSeqPlay(0x73);
                        D_8010D6D0_game_guys_lucky_7 = GMesCreate(0x16, D_8010D6DC_game_guys_lucky_7[2]);
                        func_800370D0_main(D_8010D6D0_game_guys_lucky_7, 0x78);
                        break;
                    case 0:
                        HuAudSeqPlay(0x71);
                        sprintf(D_8010D5D0_game_guys_lucky_7,
                                "%s\x81\x40\x82\x6B\x82\x6E\x82\x72\x82\x73\x81\x49",
                                D_8010D194_game_guys_lucky_7[D_8010D6DC_game_guys_lucky_7[2]]);
                        D_8010D6D0_game_guys_lucky_7 =
                            GMesCreate(0x19, D_8010D5D0_game_guys_lucky_7, 0xA0, 0x78, 1.0, 1.0, 1);
                        func_800370D0_main(D_8010D6D0_game_guys_lucky_7, 0x78);
                        break;
                }
            } else if (D_8010D190_game_guys_lucky_7 >= 135) {
                D_8010D18E_game_guys_lucky_7++;
            }
            break;
        case 7:
            object->func = func_80107DE4_game_guys_lucky_7;
            break;
        case 999:
            break;
        case 1000:
            func_8010C670_game_guys_lucky_7(0x44);
            break;
    }
}

#ifdef NON_MATCHING
// The target dispatches these five dense cases with a compare tree; this emits a jump table.
void func_80106248_game_guys_lucky_7(omObjData *object) {
    switch (D_8010D1B4_game_guys_lucky_7) {
        case 0:
            D_8010D1B4_game_guys_lucky_7 = func_8010BB88_game_guys_lucky_7();
            if (D_8010D1B6_game_guys_lucky_7++ >= 115) {
                D_8010D1B4_game_guys_lucky_7++;
            }
            break;
        case 1:
            D_8010D77C_game_guys_lucky_7 = 0;
            D_8010D6D4_game_guys_lucky_7 = omAddPrcObj(func_80106370_game_guys_lucky_7, 0x3F00, 0x800, 0);
            D_8010D1B4_game_guys_lucky_7++;
            break;
        case 2:
            if (D_8010D77C_game_guys_lucky_7 != 0) {
                HuPrcKill(D_8010D6D4_game_guys_lucky_7);
                D_8010D77C_game_guys_lucky_7 = 0;
                D_8010D1B4_game_guys_lucky_7++;
            }
            break;
        case 3:
            object->func = func_80106500_game_guys_lucky_7;
            D_8010D1B4_game_guys_lucky_7++;
            break;
        case 4:
            object->func = func_80105F70_game_guys_lucky_7;
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80106248_game_guys_lucky_7);
#endif

void func_80106370_game_guys_lucky_7(void) {
    s16 win;
    s16 choice;
    s16 done = FALSE;

    win = func_8010AD44_game_guys_lucky_7(D_8010D150_game_guys_lucky_7[0][0], D_8010D150_game_guys_lucky_7[0][1],
                                          D_8010D150_game_guys_lucky_7[0][2]);
    HuAudFXPlay(0x11D);
    func_80060C14_main(win, 1);
    HuWinMesSet(win, 0x2B00, -1, -1);
    func_8010ADF8_game_guys_lucky_7(win, D_8010D6DC_game_guys_lucky_7[1], D_8010D6DC_game_guys_lucky_7[3]);
    HuWinMesSet(win, 0x2B01, -1, -1);
    while (done == FALSE) {
        choice = func_8010AF44_game_guys_lucky_7(win, D_8010D6DC_game_guys_lucky_7[1], D_8010D6DC_game_guys_lucky_7[3], 1);
        if (choice == 0) {
            HuWinMesSet(win, 0x2B02, -1, -1);
            func_8010ADF8_game_guys_lucky_7(win, D_8010D6DC_game_guys_lucky_7[1], D_8010D6DC_game_guys_lucky_7[3]);
            done = TRUE;
        } else if (choice == 1) {
            done = TRUE;
        }
        HuPrcVSleep();
    }
    HuWinMesSet(win, 0x2B03, -1, -1);
    func_8010ADF8_game_guys_lucky_7(win, D_8010D6DC_game_guys_lucky_7[1], D_8010D6DC_game_guys_lucky_7[3]);
    func_8010ADB8_game_guys_lucky_7(win);
    D_8010D77C_game_guys_lucky_7 = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_80106500_game_guys_lucky_7(omObjData *object) {
    f32 speedSq;

    if (D_8010D1BA_game_guys_lucky_7 == 0) {
        D_8010D1BA_game_guys_lucky_7 = func_8010BB88_game_guys_lucky_7();
    }
    switch (D_8010D1B8_game_guys_lucky_7) {
        case 0:
            D_8010D1BC_game_guys_lucky_7 = -1.7f;
            D_8010D73C_game_guys_lucky_7 = 7;
            D_8010D746_game_guys_lucky_7 = 1;
            D_8010D74C_game_guys_lucky_7 = 1000.0f;
            D_8010D754_game_guys_lucky_7 = 270.0f;
            D_8010D1B8_game_guys_lucky_7++;
            break;
        case 1:
            if (D_8010D74C_game_guys_lucky_7 > 350.0f) {
                D_8010D74C_game_guys_lucky_7 -= 10.0f;
            } else if (D_8010D754_game_guys_lucky_7 < 360.0f) {
                D_8010D754_game_guys_lucky_7 += 10.0f;
            } else {
                D_8010D746_game_guys_lucky_7 = 0;
                D_8010D754_game_guys_lucky_7 = 360.0f;
            }
            if (D_8010D740_game_guys_lucky_7 >= 25 && D_8010D73E_game_guys_lucky_7 != 0.0f) {
                D_8010D1BC_game_guys_lucky_7 += 0.11f;
                if (D_8010D1BC_game_guys_lucky_7 > 1.7f) {
                    D_8010D1BC_game_guys_lucky_7 = 1.7f;
                }
                speedSq = D_8010D1BC_game_guys_lucky_7 * D_8010D1BC_game_guys_lucky_7;
                if (D_8010D1BC_game_guys_lucky_7 >= 0.0f) {
                    D_8010D730_game_guys_lucky_7 += speedSq * -17.5f;
                } else {
                    D_8010D730_game_guys_lucky_7 += speedSq * 26.0f;
                }
            } else if (D_8010D73E_game_guys_lucky_7 == 0.0f) {
                if (D_8010D1C0_game_guys_lucky_7++ >= 30) {
                    D_8010D73E_game_guys_lucky_7 = 1;
                }
            }
            if (D_8010D740_game_guys_lucky_7 == 30) {
                D_8010D73E_game_guys_lucky_7 = 0;
                D_8010D1BC_game_guys_lucky_7 = 0.0f;
                D_8010D72C_game_guys_lucky_7 = 450.0f;
                D_8010D730_game_guys_lucky_7 = 800.0f;
                D_8010D734_game_guys_lucky_7 = -100.0f;
                D_8010D738_game_guys_lucky_7 = 360.0f;
            }
            if (D_8010D730_game_guys_lucky_7 <= 0.0f) {
                D_8010D754_game_guys_lucky_7 = 360.0f;
                D_8010D73C_game_guys_lucky_7 = 0;
                D_8010D730_game_guys_lucky_7 = 0.0f;
                D_8010D726_game_guys_lucky_7 = 2;
                D_8010D1B8_game_guys_lucky_7++;
            }
            break;
        case 2:
            object->func = func_80106248_game_guys_lucky_7;
            break;
    }
}

void func_80106854_game_guys_lucky_7(omObjData *object) {
    switch (D_8010D1C2_game_guys_lucky_7) {
        case 0:
            object->func = func_80106A0C_game_guys_lucky_7;
            D_8010D1C2_game_guys_lucky_7++;
            break;
        case 1:
            D_8010D77C_game_guys_lucky_7 = 0;
            D_8010D6D8_game_guys_lucky_7 = omAddPrcObj(func_80107090_game_guys_lucky_7, 0x3F00, 0x800, 0);
            D_8010D1C2_game_guys_lucky_7++;
            break;
        case 2:
            if (D_8010D77C_game_guys_lucky_7 != 0) {
                HuPrcKill(D_8010D6D8_game_guys_lucky_7);
                if (D_8010D77C_game_guys_lucky_7 == 2) {
                    D_8010D772_game_guys_lucky_7 = 0;
                    object->func = func_80106A0C_game_guys_lucky_7;
                }
                D_8010D1C2_game_guys_lucky_7++;
                D_8010D77C_game_guys_lucky_7 = 0;
            }
            break;
        case 3:
            D_8010D77C_game_guys_lucky_7 = 0;
            D_8010D772_game_guys_lucky_7 = 1;
            D_8010D6D8_game_guys_lucky_7 = omAddPrcObj(func_80107270_game_guys_lucky_7, 0x3F00, 0x800, 0);
            D_8010D1C2_game_guys_lucky_7++;
            break;
        case 4:
            if (D_8010D77C_game_guys_lucky_7 != 0 && D_8010D1C4_game_guys_lucky_7++ >= 15) {
                HuPrcKill(D_8010D6D8_game_guys_lucky_7);
                if (D_8010D77C_game_guys_lucky_7 == 1) {
                    if (D_8010D774_game_guys_lucky_7 >= 8) {
                        D_8010D73C_game_guys_lucky_7 = D_8010D800_game_guys_lucky_7 = 5;
                    }
                    object->func = func_80106A0C_game_guys_lucky_7;
                } else if (D_8010D77C_game_guys_lucky_7 == 2) {
                    object->func = func_80105F70_game_guys_lucky_7;
                }
            }
            break;
    }
}

void func_80106A0C_game_guys_lucky_7(omObjData *object) {
    switch (D_8010D1C6_game_guys_lucky_7) {
        case 0:
            D_8010D758_game_guys_lucky_7 = 1;
            if (D_8010D772_game_guys_lucky_7 == 1) {
                GMesCreate(0x1A, 10, 0x9C, 0x38);
            }
            D_8010D1C6_game_guys_lucky_7++;
            break;
        case 1:
            if (D_8010D1C8_game_guys_lucky_7++ >= 10) {
                D_8010D1C8_game_guys_lucky_7 = 0;
                D_8010D1C6_game_guys_lucky_7++;
            }
            break;
        case 2:
            if (D_8010D772_game_guys_lucky_7 == 0) {
                if (D_8010D1C8_game_guys_lucky_7++ >= 30) {
                    D_8010D73C_game_guys_lucky_7 = 2;
                    D_8010D1C8_game_guys_lucky_7 = 0;
                    D_8010D1C6_game_guys_lucky_7++;
                }
            } else if (D_8010D772_game_guys_lucky_7 == 1) {
                if (D_8010D1CA_game_guys_lucky_7++ >= 30) {
                    D_8010D1CC_game_guys_lucky_7--;
                    D_8010D1CA_game_guys_lucky_7 = 0;
                }
                func_8003F578_main(D_8010D1CC_game_guys_lucky_7);
                switch (D_8010D6DC_game_guys_lucky_7[3]) {
                    case 0:
                        if ((D_800D5558_main[D_8010D6DC_game_guys_lucky_7[1]] & 0x8000) ||
                            D_8010D1CC_game_guys_lucky_7 == 0) {
                            D_8010D746_game_guys_lucky_7 = 3;
                            D_8010D1C8_game_guys_lucky_7 = 0;
                            D_8010D1C6_game_guys_lucky_7++;
                        }
                        break;
                    case 1:
                        if (D_8010D1C8_game_guys_lucky_7++ >= 60) {
                            D_8010D746_game_guys_lucky_7 = 3;
                            D_8010D1C8_game_guys_lucky_7 = 0;
                            D_8010D1C6_game_guys_lucky_7++;
                        }
                        break;
                }
            }
            break;
        case 3:
            if (D_8010D1C8_game_guys_lucky_7++ >= 31) {
                D_8010D1C8_game_guys_lucky_7 = 0;
                D_8010D1C6_game_guys_lucky_7++;
            } else if (D_8010D1C8_game_guys_lucky_7 == 5) {
                D_8010D768_game_guys_lucky_7 = D_8010D770_game_guys_lucky_7 = D_8010D76C_game_guys_lucky_7 = 1;
                D_8010D758_game_guys_lucky_7 = 2;
                D_8010D76A_game_guys_lucky_7 = func_801059BC_game_guys_lucky_7(6.0f);
                if (D_8010D772_game_guys_lucky_7 == 1) {
                    func_8003F5C0_main();
                }
            }
            break;
        case 4:
            D_8010D1CA_game_guys_lucky_7 = 0;
            D_8010D1CC_game_guys_lucky_7 = 10;
            D_8010D1C6_game_guys_lucky_7 = 0;
            D_8010D1C8_game_guys_lucky_7 = 0;
            object->func = func_80106CF4_game_guys_lucky_7;
            break;
        case 999:
            if (D_800D5558_main[0] & 2) {
                D_8010D1C6_game_guys_lucky_7 = 0;
            }
            break;
    }
}

void func_80106CF4_game_guys_lucky_7(omObjData *object) {
    if (D_8010D772_game_guys_lucky_7 == 0) {
        if (D_8010D1CE_game_guys_lucky_7 != D_8010D76A_game_guys_lucky_7 + 1 && D_8010D728_game_guys_lucky_7 == 0 &&
            D_8010D774_game_guys_lucky_7 < 8) {
            D_8010D728_game_guys_lucky_7 = 1;
            D_8010D1CE_game_guys_lucky_7++;
        } else if ((D_8010D1CE_game_guys_lucky_7 == D_8010D76A_game_guys_lucky_7 + 1 ||
                    D_8010D774_game_guys_lucky_7 == 8) &&
                   D_8010D728_game_guys_lucky_7 == 0) {
            if (D_8010D774_game_guys_lucky_7 >= 8) {
                D_8010D1CE_game_guys_lucky_7 = 0;
                D_8010D772_game_guys_lucky_7 = 1;
                D_8010D1D0_game_guys_lucky_7 = 0;
                object->func = func_8010783C_game_guys_lucky_7;
            } else if (D_8010D1D0_game_guys_lucky_7++ >= 6) {
                if (D_8010D738_game_guys_lucky_7 <= 360.0f) {
                    D_8010D73C_game_guys_lucky_7 = 0;
                    D_8010D738_game_guys_lucky_7 += 10.0f;
                } else {
                    D_8010D1CE_game_guys_lucky_7 = 0;
                    D_8010D738_game_guys_lucky_7 = 360.0f;
                    D_8010D772_game_guys_lucky_7 = 1;
                    D_8010D1D0_game_guys_lucky_7 = 0;
                    if (D_8010D778_game_guys_lucky_7 == 0) {
                        object->func = func_80106A0C_game_guys_lucky_7;
                    } else if (D_8010D778_game_guys_lucky_7 == 1) {
                        object->func = func_80106854_game_guys_lucky_7;
                    }
                }
            }
        }
    } else if (D_8010D772_game_guys_lucky_7 == 1) {
        if (D_8010D1CE_game_guys_lucky_7 != D_8010D76A_game_guys_lucky_7 + 1 && D_8010D744_game_guys_lucky_7 == 0 &&
            D_8010D776_game_guys_lucky_7 < 8) {
            D_8010D744_game_guys_lucky_7 = 1;
            D_8010D1CE_game_guys_lucky_7++;
        } else if ((D_8010D1CE_game_guys_lucky_7 == D_8010D76A_game_guys_lucky_7 + 1 ||
                    D_8010D776_game_guys_lucky_7 == 8) &&
                   D_8010D744_game_guys_lucky_7 == 0) {
            if (D_8010D776_game_guys_lucky_7 >= 8) {
                CharFXPlay(0x286, D_8010D6DC_game_guys_lucky_7[2]);
                D_8010D746_game_guys_lucky_7 = 7;
                object->func = func_80105F70_game_guys_lucky_7;
            } else if (D_8010D1D0_game_guys_lucky_7++ >= 6) {
                if (D_8010D754_game_guys_lucky_7 <= 360.0f) {
                    D_8010D746_game_guys_lucky_7 = 1;
                    D_8010D754_game_guys_lucky_7 += 10.0f;
                } else {
                    if (D_8010D776_game_guys_lucky_7 == 7) {
                        omVibrate(D_8010D6DC_game_guys_lucky_7[0], 30, 0, 30);
                    }
                    D_8010D746_game_guys_lucky_7 = 0;
                    D_8010D1D0_game_guys_lucky_7 = 0;
                    D_8010D1CE_game_guys_lucky_7 = 0;
                    D_8010D754_game_guys_lucky_7 = 360.0f;
                    D_8010D772_game_guys_lucky_7 = 0;
                    if (D_8010D778_game_guys_lucky_7 == 0) {
                        D_8010D778_game_guys_lucky_7 = 1;
                        object->func = func_80106854_game_guys_lucky_7;
                    } else if (D_8010D778_game_guys_lucky_7 == 1) {
                        object->func = func_80105F70_game_guys_lucky_7;
                    }
                }
            }
        }
    }
}

void func_80107090_game_guys_lucky_7(void) {
    s16 win;
    s16 success = FALSE;

    if (D_8010D776_game_guys_lucky_7 >= D_8010D774_game_guys_lucky_7) {
        success = TRUE;
    } else {
        switch (D_8010D774_game_guys_lucky_7) {
            case 1:
                if (func_801059BC_game_guys_lucky_7(100.0f) < 100) {
                    success = TRUE;
                }
                break;
            case 2:
                if (func_801059BC_game_guys_lucky_7(100.0f) < 100) {
                    success = TRUE;
                }
                break;
            case 3:
                if (func_801059BC_game_guys_lucky_7(100.0f) < 100) {
                    success = TRUE;
                }
                break;
            case 4:
                if (func_801059BC_game_guys_lucky_7(100.0f) < 30) {
                    success = TRUE;
                }
                break;
            case 5:
                if (func_801059BC_game_guys_lucky_7(100.0f) < 10) {
                    success = TRUE;
                }
                break;
        }
    }
    win = func_8010AD44_game_guys_lucky_7(D_8010D150_game_guys_lucky_7[D_8010D774_game_guys_lucky_7][0],
                                          D_8010D150_game_guys_lucky_7[D_8010D774_game_guys_lucky_7][1],
                                          D_8010D150_game_guys_lucky_7[D_8010D774_game_guys_lucky_7][2]);
    HuAudFXPlay(0x11D);
    func_80060C14_main(win, 1);
    if (success == TRUE) {
        HuWinMesSet(win, 0x2B04, -1, -1);
    } else {
        HuWinMesSet(win, 0x2B05, -1, -1);
    }
    func_8010ADF8_game_guys_lucky_7(win, D_8010D6DC_game_guys_lucky_7[1], D_8010D6DC_game_guys_lucky_7[3]);
    func_8010ADB8_game_guys_lucky_7(win);
    if (success == FALSE) {
        D_8010D77C_game_guys_lucky_7 = 1;
    } else if (success == TRUE) {
        D_8010D77C_game_guys_lucky_7 = 2;
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_80107270_game_guys_lucky_7(void) {
    s16 cursor = TRUE;
    s16 cpuBonus[4] = { 30, 20, 10, 0 };
    s16 win;
    s16 choice;
    s16 mode = 0;

    if (D_8010D6DC_game_guys_lucky_7[3] == 1) {
        if (D_8010D776_game_guys_lucky_7 < D_8010D774_game_guys_lucky_7 && D_8010D774_game_guys_lucky_7 < 8) {
            cursor = FALSE;
        } else {
            switch (D_8010D776_game_guys_lucky_7) {
                case 1:
                    if (func_801059BC_game_guys_lucky_7(100.0f) < cpuBonus[D_8010D6DC_game_guys_lucky_7[4]] + 100) {
                        cursor = FALSE;
                    }
                    break;
                case 2:
                    if (func_801059BC_game_guys_lucky_7(100.0f) < cpuBonus[D_8010D6DC_game_guys_lucky_7[4]] + 100) {
                        cursor = FALSE;
                    }
                    break;
                case 3:
                    if (func_801059BC_game_guys_lucky_7(100.0f) < cpuBonus[D_8010D6DC_game_guys_lucky_7[4]] + 100) {
                        cursor = FALSE;
                    }
                    break;
                case 4:
                    if (func_801059BC_game_guys_lucky_7(100.0f) < cpuBonus[D_8010D6DC_game_guys_lucky_7[4]] + 30) {
                        cursor = FALSE;
                    }
                    break;
                case 5:
                    if (func_801059BC_game_guys_lucky_7(100.0f) < cpuBonus[D_8010D6DC_game_guys_lucky_7[4]] + 10) {
                        cursor = FALSE;
                    }
                    break;
                case 6:
                    if (func_801059BC_game_guys_lucky_7(100.0f) < cpuBonus[D_8010D6DC_game_guys_lucky_7[4]]) {
                        cursor = FALSE;
                    }
                    break;
            }
        }
    }
    win = func_8010AD44_game_guys_lucky_7(D_8010D150_game_guys_lucky_7[D_8010D774_game_guys_lucky_7][0],
                                          D_8010D150_game_guys_lucky_7[D_8010D774_game_guys_lucky_7][1],
                                          D_8010D150_game_guys_lucky_7[D_8010D774_game_guys_lucky_7][2]);
    HuAudFXPlay(0x11D);
    func_80060C14_main(win, 1);
    if (D_8010D774_game_guys_lucky_7 <= D_8010D776_game_guys_lucky_7 || D_8010D774_game_guys_lucky_7 >= 8) {
        if (D_8010D776_game_guys_lucky_7 == 1) {
            HuWinMesSet(win, 0x2B09, -1, -1);
            func_8010ADF8_game_guys_lucky_7(win, D_8010D6DC_game_guys_lucky_7[1], D_8010D6DC_game_guys_lucky_7[3]);
            HuWinMesSet(win, 0x2B0A, -1, -1);
        } else {
            HuWinMesSet(win, 0x2B07, -1, -1);
            HuWinInsertMesSet(win, D_8010D776_game_guys_lucky_7 + 0x2B09, 0);
            func_8010ADF8_game_guys_lucky_7(win, D_8010D6DC_game_guys_lucky_7[1], D_8010D6DC_game_guys_lucky_7[3]);
            HuWinMesSet(win, 0x2B08, -1, -1);
        }
        mode = 1;
        cursor = (cursor != TRUE);
    } else {
        HuWinMesSet(win, 0x2B06, -1, -1);
    }
    while (D_8010D77C_game_guys_lucky_7 == 0) {
        if (mode == 0) {
            choice = func_8010AF44_game_guys_lucky_7(win, D_8010D6DC_game_guys_lucky_7[1],
                                                     D_8010D6DC_game_guys_lucky_7[3], cursor);
        } else {
            choice = func_8010B13C_game_guys_lucky_7(win, D_8010D6DC_game_guys_lucky_7[1],
                                                     D_8010D6DC_game_guys_lucky_7[3], cursor);
        }
        switch (choice) {
            case 0:
                D_8010D77C_game_guys_lucky_7 = 1;
                func_8010ADB8_game_guys_lucky_7(win);
                break;
            case 1:
                D_8010D77C_game_guys_lucky_7 = 2;
                func_8010ADB8_game_guys_lucky_7(win);
                break;
        }
        HuPrcVSleep();
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80107668_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010783C_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80107AC4_game_guys_lucky_7);

void func_80107DE4_game_guys_lucky_7(omObjData *object) {
    GwPlayer[D_8010D6DC_game_guys_lucky_7[0]].gameCoin = D_8010D6DC_game_guys_lucky_7[6];
    if (D_8010D77A_game_guys_lucky_7 == 0) {
        GwPlayer[D_8010D6DC_game_guys_lucky_7[0]].bonusCoin = 0;
    } else if (D_8010D77A_game_guys_lucky_7 == 1) {
        if (D_8010D776_game_guys_lucky_7 == 7) {
            GwPlayer[D_8010D6DC_game_guys_lucky_7[0]].bonusCoin = 10;
        } else {
            GwPlayer[D_8010D6DC_game_guys_lucky_7[0]].bonusCoin = 2;
        }
    }
    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
    HuAudSeqFadeOut(30);
    func_8004AB0C_main(30);
    object->func = func_80107EEC_game_guys_lucky_7;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80107EEC_game_guys_lucky_7);

void func_80107F44_game_guys_lucky_7(omObjData *object) {
    if (D_800D530C_main == 1) {
        object->func = func_80107DE4_game_guys_lucky_7;
    }
}

void func_80107F6C_game_guys_lucky_7(void) {
    D_8010D772_game_guys_lucky_7 = 0;
    D_8010D774_game_guys_lucky_7 = 0;
    D_8010D776_game_guys_lucky_7 = 0;
    D_8010D778_game_guys_lucky_7 = 0;
    D_8010D77A_game_guys_lucky_7 = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80107F98_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80107FD8_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_801080E8_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010826C_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80108374_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_801083A0_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80108498_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_801085D4_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_801087B4_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D404_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D434_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D488_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80108B64_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_801092B0_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D508_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D518_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80109570_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_80109FA4_game_guys_lucky_7);

void func_8010A04C_game_guys_lucky_7(omObjData *object) {
    if (D_8010D76C_game_guys_lucky_7 == 1) {
        func_8001C5B4_main(object->model[0], object->motion[0]);
        D_8010D76C_game_guys_lucky_7 = 0;
    }
    omSetTra(object, D_8010D75C_game_guys_lucky_7, D_8010D760_game_guys_lucky_7 - 50.0f,
             D_8010D764_game_guys_lucky_7 + 120.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010A0DC_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010A19C_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010A278_game_guys_lucky_7);

void func_8010A328_game_guys_lucky_7(omObjData *object) {
    if (D_8010D770_game_guys_lucky_7 == 1) {
        func_8001C5B4_main(object->model[0], object->motion[0]);
        D_8010D770_game_guys_lucky_7 = 0;
    }
    omSetTra(object, D_8010D75C_game_guys_lucky_7, D_8010D760_game_guys_lucky_7 - 50.0f,
             D_8010D764_game_guys_lucky_7 + 120.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010A3B8_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010A458_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010A8A4_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010AA8C_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010AD44_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010ADB8_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010ADF8_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010AF44_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010B13C_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D580_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D598_game_guys_lucky_7);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", D_8010D5A0_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010B334_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010B498_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010B528_game_guys_lucky_7);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_43_game_guys_lucky_7/3010E0", func_8010B6E0_game_guys_lucky_7);
