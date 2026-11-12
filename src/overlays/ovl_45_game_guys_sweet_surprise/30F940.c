#include "common.h"
#include "game_guys_sweet_surprise.h"

typedef struct GameGuysSweetSurprisePadValues {
    /* 0x00 */ s16 v[4]; // one entry per controller port
} GameGuysSweetSurprisePadValues;

typedef struct GameGuysSweetSurpriseRewardTable {
    /* 0x00 */ s16 v[6];
} GameGuysSweetSurpriseRewardTable;

extern s16 D_8010CB76_game_guys_sweet_surprise;     // main state
extern s16 D_8010CB78_game_guys_sweet_surprise;     // main state timer
extern s16 D_8010CB7A_game_guys_sweet_surprise;     // message window
extern char *D_8010CB7C_game_guys_sweet_surprise[]; // character names
extern s16 D_8010CB9C_game_guys_sweet_surprise;     // state
extern s16 D_8010CB9E_game_guys_sweet_surprise;     // state
extern s16 D_8010CBA0_game_guys_sweet_surprise;     // input cooldown
extern s16 D_8010CBA2_game_guys_sweet_surprise;     // countdown seconds
extern s16 D_8010CBA4_game_guys_sweet_surprise;     // countdown tick timer
extern s16 D_8010CBA6_game_guys_sweet_surprise;     // state
extern s16 D_8010CBA8_game_guys_sweet_surprise;     // state
extern s16 D_8010CBAA_game_guys_sweet_surprise;     // timer
extern s16 D_8010CBAC_game_guys_sweet_surprise;     // sound counter
extern s16 D_8010CBAE_game_guys_sweet_surprise;     // timer
extern s16 D_8010CBB0_game_guys_sweet_surprise;     // state
extern s16 D_8010CBB2_game_guys_sweet_surprise;
extern GameGuysSweetSurprisePadValues D_8010CC70_game_guys_sweet_surprise; // player slots
extern GameGuysSweetSurpriseRewardTable D_8010CC78_game_guys_sweet_surprise;
extern GameGuysSweetSurpriseRewardTable D_8010CC84_game_guys_sweet_surprise;
extern s16 D_8010CF58_game_guys_sweet_surprise[7]; // player, pad, chr, is CPU, CPU difficulty, coins, coins
extern s16 D_8010CF66_game_guys_sweet_surprise;
extern s16 D_8010CF68_game_guys_sweet_surprise;
extern s16 D_8010CF6A_game_guys_sweet_surprise;
extern s16 D_8010CF6C_game_guys_sweet_surprise; // winning side
extern s16 D_8010CF6E_game_guys_sweet_surprise[2];
extern s16 D_8010CF72_game_guys_sweet_surprise[2];
extern char D_8010CE50_game_guys_sweet_surprise[];
extern Process *D_8010CF50_game_guys_sweet_surprise;
extern Process *D_8010CF54_game_guys_sweet_surprise;
extern omObjData *D_8010CFC0_game_guys_sweet_surprise;
extern omObjData *D_8010CFC4_game_guys_sweet_surprise;
extern omObjData *D_8010CFC8_game_guys_sweet_surprise;
extern omObjData *D_8010CFCC_game_guys_sweet_surprise;
extern omObjData *D_8010CFD0_game_guys_sweet_surprise;
extern omObjData *D_8010CFD4_game_guys_sweet_surprise;
extern omObjData *D_8010CFD8_game_guys_sweet_surprise;
extern s16 D_8010CFDC_game_guys_sweet_surprise; // process done flag
extern s16 D_8010CFDE_game_guys_sweet_surprise;
extern s16 D_8010CFE0_game_guys_sweet_surprise; // choice active
extern s16 D_8010CFE2_game_guys_sweet_surprise;
extern s16 D_8010CFE4_game_guys_sweet_surprise[2]; // per-side score
extern s16 D_8010CFE8_game_guys_sweet_surprise;
extern s16 D_8010CFEA_game_guys_sweet_surprise;
extern s16 D_8010CFEC_game_guys_sweet_surprise;
extern s16 D_8010CFEE_game_guys_sweet_surprise;
extern s16 D_8010CFF0_game_guys_sweet_surprise;
extern s16 D_8010CFF2_game_guys_sweet_surprise;
extern s16 D_8010CFF4_game_guys_sweet_surprise;
extern s16 D_8010CFF6_game_guys_sweet_surprise;
extern s16 D_8010CFF8_game_guys_sweet_surprise;
extern s16 D_8010CFFA_game_guys_sweet_surprise;
extern s16 D_8010CFFC_game_guys_sweet_surprise;
extern s16 D_8010CFFE_game_guys_sweet_surprise;
extern s16 D_8010D000_game_guys_sweet_surprise;
extern s16 D_8010D002_game_guys_sweet_surprise; // COM difficulty

void func_80105A28_game_guys_sweet_surprise(void);
void func_80105AB8_game_guys_sweet_surprise(void);
void func_80105C18_game_guys_sweet_surprise(void);
void func_80105C34_game_guys_sweet_surprise(void);
void func_80105DCC_game_guys_sweet_surprise(omObjData *object);
void func_80105F24_game_guys_sweet_surprise(void);
void func_8010612C_game_guys_sweet_surprise(omObjData *object);
void func_801063F0_game_guys_sweet_surprise(omObjData *object);
void func_80106594_game_guys_sweet_surprise(void);
void func_8010672C_game_guys_sweet_surprise(void);
void func_80106918_game_guys_sweet_surprise(omObjData *object);
void func_80106C0C_game_guys_sweet_surprise(void);
void func_80106CB4_game_guys_sweet_surprise(omObjData *object);
void func_80106D48_game_guys_sweet_surprise(omObjData *object);
void func_80106EE4_game_guys_sweet_surprise(omObjData *object);
void func_801071F8_game_guys_sweet_surprise(omObjData *object);
void func_801072B4_game_guys_sweet_surprise(omObjData *object);
void func_80107398_game_guys_sweet_surprise(omObjData *object);
void func_801073F0_game_guys_sweet_surprise(omObjData *object);
void func_80107418_game_guys_sweet_surprise(omObjData *object);
void func_8010878C_game_guys_sweet_surprise(omObjData *object);
void func_80108AC4_game_guys_sweet_surprise(omObjData *object);
void func_80108FE0_game_guys_sweet_surprise(omObjData *object);
void func_80109AA8_game_guys_sweet_surprise(omObjData *object);
void func_8010A604_game_guys_sweet_surprise(omObjData *object);
void func_8010AAD8_game_guys_sweet_surprise(omObjData *object);
void func_8010AB3C_game_guys_sweet_surprise(omObjData *object);
void func_8010ABD8_game_guys_sweet_surprise(omObjData *object);
s16 func_8010AE44_game_guys_sweet_surprise(s16 x, s16 y, s16 lines);
void func_8010AEB8_game_guys_sweet_surprise(s16 win, s16 player, s16 mode);
s16 func_8010B004_game_guys_sweet_surprise(s16 win, s16 player, s16 mode, s16 count);
void func_8010B1B4_game_guys_sweet_surprise(s16 win);

void func_801059A0_game_guys_sweet_surprise(void) {
    func_80105A28_game_guys_sweet_surprise();
}

s32 func_801059BC_game_guys_sweet_surprise(f32 arg0) {
    u8 randomByte1 = rand8();
    u8 randomByte2 = rand8();
    s32 shiftedByte1 = (randomByte1 << 8);
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;

    return scaledRandom;
}

void func_80105A28_game_guys_sweet_surprise(void) {
    func_8001FE20_main(32);
    func_800142A0_main(32);
    omInitObjMan(32, 32);
    func_8004A208_main();
    func_80105AB8_game_guys_sweet_surprise();
    func_80105C18_game_guys_sweet_surprise();
    func_80105C34_game_guys_sweet_surprise();
    omAddObj(1000, 0, 0, -1, func_80105DCC_game_guys_sweet_surprise);
    omAddObj(2000, 0, 0, -1, func_801073F0_game_guys_sweet_surprise);
}

void func_80105AB8_game_guys_sweet_surprise(void) {
    s32 camIndex;

    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(camIndex, 12.37f, 2000.0f, 8000.0f);
    CZoom = 3275.61f;
    CRot.x = -8.7f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 187.6f;
    Center.z = -16.89f;
}

void func_80105C18_game_guys_sweet_surprise(void) {
    HuWinInit();
}

void func_80105C34_game_guys_sweet_surprise(void) {
    s16 i = 0;
    GameGuysSweetSurprisePadValues players = D_8010CC70_game_guys_sweet_surprise;

    for (; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    if (i < 4) {
        D_8010CF58_game_guys_sweet_surprise[0] = players.v[i];
    } else {
        D_8010CF58_game_guys_sweet_surprise[0] = players.v[0];
    }
    D_8010CF58_game_guys_sweet_surprise[1] = GwPlayer[D_8010CF58_game_guys_sweet_surprise[0]].pad;
    D_8010CF58_game_guys_sweet_surprise[2] = GwPlayer[D_8010CF58_game_guys_sweet_surprise[0]].chr;
    if (GwPlayer[D_8010CF58_game_guys_sweet_surprise[0]].stat & 1) {
        D_8010CF58_game_guys_sweet_surprise[3] = 1;
        D_8010CF58_game_guys_sweet_surprise[4] = GwPlayer[D_8010CF58_game_guys_sweet_surprise[0]].cpu_difficulty;
        D_8010D002_game_guys_sweet_surprise = GwCommon.unkA0;
        if (D_8010D002_game_guys_sweet_surprise <= 0) {
            D_8010D002_game_guys_sweet_surprise = 0;
        } else if (D_8010D002_game_guys_sweet_surprise >= 2) {
            D_8010D002_game_guys_sweet_surprise = 2;
        }
    } else {
        D_8010CF58_game_guys_sweet_surprise[3] = 0;
        D_8010CF58_game_guys_sweet_surprise[4] = 0;
    }
    D_8010CF58_game_guys_sweet_surprise[5] = D_8010CF58_game_guys_sweet_surprise[6] = GwPlayer[D_8010CF58_game_guys_sweet_surprise[0]].gameCoin;
}

void func_80105DCC_game_guys_sweet_surprise(omObjData *object) {
    func_8010B250_game_guys_sweet_surprise(160, 180);
    func_80105F24_game_guys_sweet_surprise();
    D_8010CFC0_game_guys_sweet_surprise = omAddObj(10, 10, 10, -1, func_80107418_game_guys_sweet_surprise);
    D_8010CFC4_game_guys_sweet_surprise = omAddObj(20, 10, 10, -1, func_8010878C_game_guys_sweet_surprise);
    D_8010CFC8_game_guys_sweet_surprise = omAddObj(30, 10, 20, -1, func_80108AC4_game_guys_sweet_surprise);
    D_8010CFCC_game_guys_sweet_surprise = omAddObj(40, 10, 20, -1, func_80108FE0_game_guys_sweet_surprise);
    D_8010CFD0_game_guys_sweet_surprise = omAddObj(50, 10, 20, -1, func_80109AA8_game_guys_sweet_surprise);
    D_8010CFD4_game_guys_sweet_surprise = omAddObj(60, 10, 10, -1, func_8010A604_game_guys_sweet_surprise);
    D_8010CFD8_game_guys_sweet_surprise = omAddObj(70, 10, 10, -1, func_8010AAD8_game_guys_sweet_surprise);
    object->func = func_8010612C_game_guys_sweet_surprise;
}

void func_80105F24_game_guys_sweet_surprise(void) {
    GameGuysSweetSurpriseRewardTable table1 = D_8010CC78_game_guys_sweet_surprise;
    GameGuysSweetSurpriseRewardTable table2 = D_8010CC84_game_guys_sweet_surprise;
    s16 index;

    D_8010CF66_game_guys_sweet_surprise = 0;
    D_8010CF68_game_guys_sweet_surprise = 0;
    if (D_8010CF58_game_guys_sweet_surprise[3] == 1) {
        D_8010CF6A_game_guys_sweet_surprise = 0;
        if (D_8010CF58_game_guys_sweet_surprise[4] == 0) {
            D_8010CF6A_game_guys_sweet_surprise = func_801059BC_game_guys_sweet_surprise(2.0f);
        } else if (D_8010CF58_game_guys_sweet_surprise[4] == 1) {
            if (func_801059BC_game_guys_sweet_surprise(4.0f) == 0) {
                D_8010CF6A_game_guys_sweet_surprise = 1;
            }
        } else if (D_8010CF58_game_guys_sweet_surprise[4] == 2) {
            if (func_801059BC_game_guys_sweet_surprise(8.0f) == 0) {
                D_8010CF6A_game_guys_sweet_surprise = 1;
            }
        } else if (D_8010CF58_game_guys_sweet_surprise[4] == 3) {
            if (func_801059BC_game_guys_sweet_surprise(16.0f) == 0) {
                D_8010CF6A_game_guys_sweet_surprise = 1;
            }
        }
    }
    index = func_801059BC_game_guys_sweet_surprise(5.0f) + 1;
    D_8010CF6E_game_guys_sweet_surprise[0] = 2;
    D_8010CF6E_game_guys_sweet_surprise[1] = table1.v[index];
    while (D_8010CF72_game_guys_sweet_surprise[0] == D_8010CF72_game_guys_sweet_surprise[1]) {
        D_8010CF72_game_guys_sweet_surprise[0] = func_801059BC_game_guys_sweet_surprise(10.0f);
        D_8010CF72_game_guys_sweet_surprise[1] = func_801059BC_game_guys_sweet_surprise(10.0f);
    }
    D_8010CFFE_game_guys_sweet_surprise = 10;
    D_8010D000_game_guys_sweet_surprise = table2.v[index];
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CC90_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CC9C_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCAC_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCB4_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCC0_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCCC_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCD8_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCE4_game_guys_sweet_surprise);

void func_8010612C_game_guys_sweet_surprise(omObjData *object) {
    switch (D_8010CB76_game_guys_sweet_surprise) {
        case 0:
            WipeCreateIn(0xFF, 0x10);
            D_8010CB76_game_guys_sweet_surprise++;
            break;
        case 1:
            object->func = func_801063F0_game_guys_sweet_surprise;
            D_8010CB76_game_guys_sweet_surprise++;
            break;
        case 2:
            if (++D_8010CB78_game_guys_sweet_surprise == 1) {
                GMesCreate(9);
            } else if (D_8010CB78_game_guys_sweet_surprise == 70) {
                D_8010CFEE_game_guys_sweet_surprise = 3;
            } else if (D_8010CB78_game_guys_sweet_surprise == 80) {
                D_8010CFFA_game_guys_sweet_surprise = 1;
                HuAudFXPlay(0x538);
            } else if (GMesStatGet() == 0) {
                D_8010CFEE_game_guys_sweet_surprise = 2;
                D_8010CB76_game_guys_sweet_surprise++;
                D_8010CB78_game_guys_sweet_surprise = 0;
            }
            break;
        case 3:
            object->func = func_80106D48_game_guys_sweet_surprise;
            D_8010CB76_game_guys_sweet_surprise++;
            break;
        case 4:
            if (++D_8010CB78_game_guys_sweet_surprise == 1) {
                D_8010CFF8_game_guys_sweet_surprise = D_8010CFF4_game_guys_sweet_surprise = 3;
                GMesCreate(0x14);
                HuAudSeqFadeOut(120);
            } else if (GMesStatGet() == 0) {
                D_8010CB76_game_guys_sweet_surprise++;
                D_8010CB78_game_guys_sweet_surprise = 0;
            }
            break;
        case 5:
            object->func = func_801071F8_game_guys_sweet_surprise;
            D_8010CB76_game_guys_sweet_surprise++;
            break;
        case 6:
            if (++D_8010CB78_game_guys_sweet_surprise == 1) {
                switch (D_8010CF66_game_guys_sweet_surprise) {
                    case 1:
                        HuAudFXPlay(0x517);
                        HuAudSeqPlay(0x73);
                        D_8010CB7A_game_guys_sweet_surprise = GMesCreate(0x16, (u16)D_8010CF58_game_guys_sweet_surprise[2]);
                        func_800370D0_main(D_8010CB7A_game_guys_sweet_surprise, 0x78);
                        break;
                    case 0:
                        HuAudFXPlay(0x518);
                        HuAudSeqPlay(0x71);
                        sprintf(D_8010CE50_game_guys_sweet_surprise, "%s\x81\x40\x82\x6B\x82\x6E\x82\x72\x82\x73\x81\x49",
                                D_8010CB7C_game_guys_sweet_surprise[(u16)D_8010CF58_game_guys_sweet_surprise[2]]);
                        D_8010CB7A_game_guys_sweet_surprise = GMesCreate(0x19, D_8010CE50_game_guys_sweet_surprise, 0xA0, 0x78, 1.0, 1.0, 1);
                        func_800370D0_main(D_8010CB7A_game_guys_sweet_surprise, 0x78);
                        break;
                }
            } else if (D_8010CB78_game_guys_sweet_surprise >= 135) {
                D_8010CB76_game_guys_sweet_surprise++;
                D_8010CB78_game_guys_sweet_surprise = 0;
            }
            break;
        case 7:
            object->func = func_801072B4_game_guys_sweet_surprise;
            break;
    }
}

void func_801063F0_game_guys_sweet_surprise(omObjData *object) {
    switch (D_8010CB9C_game_guys_sweet_surprise) {
        case 0:
            if (WipeStatGet() != 1) {
                D_8010CB9C_game_guys_sweet_surprise++;
            }
            break;
        case 1:
            D_8010CB9C_game_guys_sweet_surprise += func_8010B5A8_game_guys_sweet_surprise();
            break;
        case 2:
            D_8010CFDC_game_guys_sweet_surprise = 0;
            D_8010CF50_game_guys_sweet_surprise = omAddPrcObj(func_80106594_game_guys_sweet_surprise, 0x3F00, 0x800, 0);
            D_8010CB9C_game_guys_sweet_surprise++;
            break;
        case 3:
            if (D_8010CFDC_game_guys_sweet_surprise == 1) {
                HuPrcKill(D_8010CF50_game_guys_sweet_surprise);
                D_8010CFDC_game_guys_sweet_surprise = 0;
                D_8010CB9C_game_guys_sweet_surprise++;
            }
            break;
        case 4:
            D_8010CF54_game_guys_sweet_surprise = omAddPrcObj(func_8010672C_game_guys_sweet_surprise, 0x3F00, 0x800, 0);
            D_8010CB9C_game_guys_sweet_surprise++;
            break;
        case 5:
            object->func = func_80106918_game_guys_sweet_surprise;
            D_8010CB9C_game_guys_sweet_surprise++;
            break;
        case 6:
            D_8010CFDC_game_guys_sweet_surprise = 0;
            D_8010CF50_game_guys_sweet_surprise = omAddPrcObj(func_80106C0C_game_guys_sweet_surprise, 0x3F00, 0x800, 0);
            D_8010CB9C_game_guys_sweet_surprise++;
            break;
        case 7:
            if (D_8010CFDC_game_guys_sweet_surprise == 1) {
                HuPrcKill(D_8010CF50_game_guys_sweet_surprise);
                D_8010CFDC_game_guys_sweet_surprise = 0;
                D_8010CB9C_game_guys_sweet_surprise++;
            }
            break;
        case 8:
            object->func = func_80106CB4_game_guys_sweet_surprise;
            D_8010CB9C_game_guys_sweet_surprise++;
            break;
        case 9:
            HuPrcKill(D_8010CF54_game_guys_sweet_surprise);
            object->func = func_8010612C_game_guys_sweet_surprise;
            break;
    }
}

void func_80106594_game_guys_sweet_surprise(void) {
    s16 win;
    s16 choice;
    s16 done = FALSE;

    D_8010CFDC_game_guys_sweet_surprise = 0;
    win = func_8010AE44_game_guys_sweet_surprise(130, 150, 12);
    HuAudFXPlay(0x11D);
    func_80060C14_main(win, 1);
    HuWinMesSet(win, 0x2E00, -1, -1);
    func_8010AEB8_game_guys_sweet_surprise(win, D_8010CF58_game_guys_sweet_surprise[1], D_8010CF58_game_guys_sweet_surprise[3]);
    HuWinMesSet(win, 0x2E01, -1, -1);
    while (done == FALSE) {
        choice = func_8010B004_game_guys_sweet_surprise(win, D_8010CF58_game_guys_sweet_surprise[1], D_8010CF58_game_guys_sweet_surprise[3], 1);
        switch (choice) {
            case 0:
                HuWinMesSet(win, 0x2E02, -1, -1);
                func_8010AEB8_game_guys_sweet_surprise(win, D_8010CF58_game_guys_sweet_surprise[1], D_8010CF58_game_guys_sweet_surprise[3]);
                /* fallthrough */
            case 1:
                done = TRUE;
                break;
        }
        HuPrcVSleep();
    }
    HuWinMesSet(win, 0x2E03, -1, -1);
    func_8010AEB8_game_guys_sweet_surprise(win, D_8010CF58_game_guys_sweet_surprise[1], D_8010CF58_game_guys_sweet_surprise[3]);
    func_8010B1B4_game_guys_sweet_surprise(win);
    D_8010CFDC_game_guys_sweet_surprise = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_8010672C_game_guys_sweet_surprise(void) {
    s16 done = FALSE;
    s16 leftWin;
    s16 rightWin;

    leftWin = HuWinCreate(37, 180, 106, 34, 0, 1);
    HuWinBGColSet(leftWin, 0, 0, 255);
    HuWinBGTPLvlSet(leftWin, 150);
    HuWinMesSet(leftWin, D_8010CF72_game_guys_sweet_surprise[0] + 0x2E07, -1, -1);
    rightWin = HuWinCreate(177, 180, 106, 34, 0, 1);
    HuWinBGColSet(rightWin, 255, 0, 0);
    HuWinBGTPLvlSet(rightWin, 150);
    HuWinMesSet(rightWin, D_8010CF72_game_guys_sweet_surprise[1] + 0x2E07, -1, -1);
    HuWinDispOff(leftWin);
    HuWinDispOff(rightWin);
    while (done == FALSE) {
        if (D_8010CFE0_game_guys_sweet_surprise == 1) {
            switch (D_8010CF68_game_guys_sweet_surprise) {
                case 0:
                    HuWinDispOn(leftWin);
                    HuWinDispOff(rightWin);
                    break;
                case 1:
                    HuWinDispOff(leftWin);
                    HuWinDispOn(rightWin);
                    break;
            }
        } else if (D_8010CFE0_game_guys_sweet_surprise == 0) {
            if (D_8010CFDE_game_guys_sweet_surprise == 1) {
                done = TRUE;
            }
        }
        HuPrcVSleep();
    }
    HuWinKill(leftWin);
    HuWinKill(rightWin);
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_80106918_game_guys_sweet_surprise(omObjData *object) {
    s16 input = 0;

    switch (D_8010CB9E_game_guys_sweet_surprise) {
        case 0:
            GMesCreate(0x1A, 10, 0x9C, 0x38);
            D_8010CBA2_game_guys_sweet_surprise = 10;
            D_8010CBA4_game_guys_sweet_surprise = 0;
            D_800D6A58_main = 0;
            D_8010CFE0_game_guys_sweet_surprise = 1;
            D_8010CB9E_game_guys_sweet_surprise++;
            break;
        case 1:
            if (D_8010CBA0_game_guys_sweet_surprise <= 0) {
                switch (D_8010CF58_game_guys_sweet_surprise[3]) {
                    case 0:
                        if (D_800D20A1_main[D_8010CF58_game_guys_sweet_surprise[1]] < -64 && D_8010CF68_game_guys_sweet_surprise != 1) {
                            input = 1;
                            D_8010CBA0_game_guys_sweet_surprise = 5;
                        }
                        if (D_800D20A1_main[D_8010CF58_game_guys_sweet_surprise[1]] > 64 && D_8010CF68_game_guys_sweet_surprise != 0) {
                            input = -1;
                            D_8010CBA0_game_guys_sweet_surprise = 5;
                        }
                        if (D_800D5558_main[D_8010CF58_game_guys_sweet_surprise[1]] & 0x8000) {
                            input = 10;
                        }
                        break;
                    case 1:
                        if (D_8010CF6A_game_guys_sweet_surprise == D_8010CF68_game_guys_sweet_surprise) {
                            input = 10;
                        } else {
                            input = 1;
                            D_8010CBA0_game_guys_sweet_surprise = 30;
                        }
                        break;
                }
            } else {
                D_8010CBA0_game_guys_sweet_surprise--;
            }
            if (D_8010CBA4_game_guys_sweet_surprise++ >= 30) {
                D_8010CBA2_game_guys_sweet_surprise--;
                D_8010CBA4_game_guys_sweet_surprise = 0;
                func_8003F578_main(D_8010CBA2_game_guys_sweet_surprise);
                if (D_8010CBA2_game_guys_sweet_surprise == 0) {
                    input = 10;
                } else if (D_8010CBA2_game_guys_sweet_surprise < 6) {
                    HuAudFXPlay(8);
                }
            }
            switch (input) {
                case 1:
                    HuAudFXPlay(1);
                    D_8010CF68_game_guys_sweet_surprise = 1;
                    break;
                case -1:
                    HuAudFXPlay(1);
                    D_8010CF68_game_guys_sweet_surprise = 0;
                    break;
                case 10:
                    HuAudFXPlay(3);
                    omVibrate(D_8010CF58_game_guys_sweet_surprise[0], 10, 0, 10);
                    D_8010CFEC_game_guys_sweet_surprise = 1;
                    D_8010CFE0_game_guys_sweet_surprise = 0;
                    D_8010CB9E_game_guys_sweet_surprise++;
                    break;
            }
            break;
        case 2:
            D_800D6A58_main = 1;
            func_8003F5C0_main();
            object->func = func_801063F0_game_guys_sweet_surprise;
            break;
    }
}

void func_80106C0C_game_guys_sweet_surprise(void) {
    s16 win;

    win = func_8010AE44_game_guys_sweet_surprise(130, 150, 12);
    func_80060C14_main(win, 1);
    HuWinMesSet(win, 0x2E04, -1, -1);
    HuWinInsertMesSet(win, D_8010CF68_game_guys_sweet_surprise + 0x2E05, 0);
    func_8010AEB8_game_guys_sweet_surprise(win, D_8010CF58_game_guys_sweet_surprise[1], D_8010CF58_game_guys_sweet_surprise[3]);
    func_8010B1B4_game_guys_sweet_surprise(win);
    D_8010CFDC_game_guys_sweet_surprise = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_80106CB4_game_guys_sweet_surprise(omObjData *object) {
    switch (D_8010CBA6_game_guys_sweet_surprise) {
        case 0:
            D_8010CFF0_game_guys_sweet_surprise = 1;
            D_8010CFFC_game_guys_sweet_surprise = 1;
            D_8010CBA6_game_guys_sweet_surprise++;
            break;
        case 1:
            if (D_8010CFF0_game_guys_sweet_surprise == 0) {
                D_8010CFE2_game_guys_sweet_surprise = 1;
                D_8010CBA6_game_guys_sweet_surprise++;
            }
            break;
        case 2:
            object->func = func_801063F0_game_guys_sweet_surprise;
            break;
    }
}

void func_80106D48_game_guys_sweet_surprise(omObjData *object) {
    switch (D_8010CBA8_game_guys_sweet_surprise) {
        case 0:
            object->func = func_80106EE4_game_guys_sweet_surprise;
            D_8010CBA8_game_guys_sweet_surprise++;
            break;
        case 1:
            if (D_8010CBAA_game_guys_sweet_surprise++ >= 8 && D_8010CBAA_game_guys_sweet_surprise % 5 == 0) {
                if (D_8010CBAC_game_guys_sweet_surprise == 0) {
                    HuAudFXPlay(0x539);
                }
                if (D_8010CBAC_game_guys_sweet_surprise++ < 4) {
                    D_8010CFFA_game_guys_sweet_surprise = 1;
                }
            }
            if (D_800CCF58_main[Hu3DData[D_8010CFC8_game_guys_sweet_surprise->model[0]].motId].unk02 <=
                Hu3DData[D_8010CFC8_game_guys_sweet_surprise->model[0]].motTime) {
                D_8010CBA8_game_guys_sweet_surprise++;
            }
            break;
        case 2:
            D_8010CFEE_game_guys_sweet_surprise = 0;
            object->func = func_8010612C_game_guys_sweet_surprise;
            break;
    }
}

void func_80106EE4_game_guys_sweet_surprise(omObjData *object) {
    s16 i;

    switch (D_8010CBB0_game_guys_sweet_surprise) {
        case 0:
            D_8010CFF6_game_guys_sweet_surprise = D_8010CFF2_game_guys_sweet_surprise = 2;
            D_8010CBB0_game_guys_sweet_surprise++;
            break;
        case 1:
            if (D_8010CBAE_game_guys_sweet_surprise++ >= 30) {
                if (func_801059BC_game_guys_sweet_surprise(D_8010CFFE_game_guys_sweet_surprise) < D_8010D000_game_guys_sweet_surprise) {
                    if (func_801059BC_game_guys_sweet_surprise(10.0f) < 6) {
                        D_8010CFE4_game_guys_sweet_surprise[0] += 1;
                    } else {
                        D_8010CFE4_game_guys_sweet_surprise[0] += 2;
                    }
                    if (D_8010CF68_game_guys_sweet_surprise == 0) {
                        omVibrate(D_8010CF58_game_guys_sweet_surprise[0], 10, 0, 10);
                    }
                    D_8010CFF2_game_guys_sweet_surprise = 3;
                    D_8010CFF6_game_guys_sweet_surprise = 2;
                } else {
                    if (func_801059BC_game_guys_sweet_surprise(10.0f) < 6) {
                        D_8010CFE4_game_guys_sweet_surprise[1] += 1;
                    } else {
                        D_8010CFE4_game_guys_sweet_surprise[1] += 2;
                    }
                    if (D_8010CF68_game_guys_sweet_surprise == 1) {
                        omVibrate(D_8010CF58_game_guys_sweet_surprise[0], 10, 0, 10);
                    }
                    D_8010CFE8_game_guys_sweet_surprise = 1;
                    D_8010CFF2_game_guys_sweet_surprise = 2;
                    D_8010CFF6_game_guys_sweet_surprise = 3;
                }
                D_8010CBAE_game_guys_sweet_surprise = 0;
            } else if (D_8010CBAE_game_guys_sweet_surprise % 7 == 0) {
                if (func_801059BC_game_guys_sweet_surprise(2.0f) == 0) {
                    D_8010CFEA_game_guys_sweet_surprise = 1;
                } else {
                    D_8010CFE8_game_guys_sweet_surprise = 1;
                }
            }
            break;
    }
    for (i = 0; i < 2; i++) {
        if (D_8010CFE4_game_guys_sweet_surprise[i] >= 6) {
            D_8010CFE4_game_guys_sweet_surprise[i] = 6;
        }
    }
    for (i = 0; i < 2; i++) {
        if (D_8010CFE4_game_guys_sweet_surprise[i] == 6) {
            D_8010CFF2_game_guys_sweet_surprise = 0;
            D_8010CFF6_game_guys_sweet_surprise = 0;
            D_8010CF6C_game_guys_sweet_surprise = i;
            D_8010CFEE_game_guys_sweet_surprise = 4;
            object->func = func_80106D48_game_guys_sweet_surprise;
        }
    }
}

void func_801071F8_game_guys_sweet_surprise(omObjData *object) {
    if (D_8010CBB2_game_guys_sweet_surprise == 0) {
        if (D_8010CF6C_game_guys_sweet_surprise == 0) {
            D_8010CFF6_game_guys_sweet_surprise = 1;
            D_8010CFF4_game_guys_sweet_surprise = 1;
            D_8010CFF8_game_guys_sweet_surprise = 2;
        } else {
            D_8010CFF2_game_guys_sweet_surprise = 1;
            D_8010CFF4_game_guys_sweet_surprise = 2;
            D_8010CFF8_game_guys_sweet_surprise = 1;
        }
        if (D_8010CF68_game_guys_sweet_surprise == D_8010CF6C_game_guys_sweet_surprise) {
            D_8010CF66_game_guys_sweet_surprise = 1;
        } else {
            D_8010CF66_game_guys_sweet_surprise = 0;
        }
        HuAudSeqFadeOut(30);
        object->func = func_8010612C_game_guys_sweet_surprise;
    }
}

void func_801072B4_game_guys_sweet_surprise(omObjData *object) {
    GwPlayer[D_8010CF58_game_guys_sweet_surprise[0]].gameCoin = D_8010CF58_game_guys_sweet_surprise[6];
    switch (D_8010CF66_game_guys_sweet_surprise) {
        case 1:
            GwPlayer[D_8010CF58_game_guys_sweet_surprise[0]].bonusCoin = D_8010CF6E_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise];
            break;
        case 0:
            GwPlayer[D_8010CF58_game_guys_sweet_surprise[0]].bonusCoin = 0;
            break;
    }
    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
    HuAudSeqFadeOut(30);
    func_8004AB0C_main(30);
    object->func = func_80107398_game_guys_sweet_surprise;
}

void func_80107398_game_guys_sweet_surprise(omObjData *object) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        func_8010C244_game_guys_sweet_surprise();
        GMesClose();
        HuWinAllKill();
        HuSprAnimAllKill();
        omOvlReturnEx(1);
    }
}

void func_801073F0_game_guys_sweet_surprise(omObjData *object) {
    if (D_800D530C_main == 1) {
        object->func = func_801072B4_game_guys_sweet_surprise;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107418_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107478_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107514_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107550_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107750_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_801077D4_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107894_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107A8C_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107B50_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107B8C_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107CAC_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107F74_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80108218_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80108538_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010878C_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80108878_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CD50_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CD70_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CD90_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CD9C_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80108AC4_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80108CB8_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80108FE0_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_801092F0_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80109AA8_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80109DE4_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010A604_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010A784_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010A820_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010AA94_game_guys_sweet_surprise);

void func_8010AAD8_game_guys_sweet_surprise(omObjData *object) {
    omAddObj(0xC8, 0xA, 0xA, -1, func_8010AB3C_game_guys_sweet_surprise);
    omAddObj(0x12C, 0xA, 0xA, -1, func_8010ABD8_game_guys_sweet_surprise);
    object->func = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010AB3C_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010ABD8_game_guys_sweet_surprise);

void func_8010AC74_game_guys_sweet_surprise(omObjData *object) {
    if (D_8010CFEA_game_guys_sweet_surprise == 1) {
        if (func_801059BC_game_guys_sweet_surprise(3.0f) == 0) {
            object->scale.x = object->scale.y = object->scale.z = 1.5f;
        } else {
            object->scale.x = object->scale.y = object->scale.z = 1.0f;
        }
        func_8001C5B4_main(object->model[0], object->motion[0]);
        D_8010CFEA_game_guys_sweet_surprise = 0;
    }
}

void func_8010AD04_game_guys_sweet_surprise(omObjData *object) {
    if (D_8010CFE8_game_guys_sweet_surprise == 1) {
        if (func_801059BC_game_guys_sweet_surprise(3.0f) == 0) {
            object->scale.x = object->scale.y = object->scale.z = 1.25f;
        } else {
            object->scale.x = object->scale.y = object->scale.z = 1.0f;
        }
        func_8001C5B4_main(object->model[0], object->motion[0]);
        D_8010CFE8_game_guys_sweet_surprise = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010AD94_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010AE44_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010AEB8_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010B004_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010B1B4_game_guys_sweet_surprise);

Vec2f *func_8010B1F4_game_guys_sweet_surprise(Vec2f *outPos, f32 x, f32 y, f32 z) {
    Vec pos;
    Vec2f screenPos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    Hu3D3Dto2D(0, &pos, &screenPos);
    *outPos = screenPos;
    return outPos;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CDEC_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CDF8_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CE08_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CE14_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CE24_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CE2C_game_guys_sweet_surprise);
