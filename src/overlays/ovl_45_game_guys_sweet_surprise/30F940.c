#include "common.h"
#include "game_guys_sweet_surprise.h"

typedef struct GameGuysSweetSurprisePadValues {
    /* 0x00 */ s16 v[4]; // one entry per controller port
} GameGuysSweetSurprisePadValues;

typedef struct GameGuysSweetSurprisePos {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
} GameGuysSweetSurprisePos;

typedef struct GameGuysSweetSurpriseRewardTable {
    /* 0x00 */ s16 v[6];
} GameGuysSweetSurpriseRewardTable;

extern s16 D_8010CB70_game_guys_sweet_surprise[];   // COM key wait frames, indexed by CPU difficulty
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
extern s16 D_8010CBB4_game_guys_sweet_surprise; // state
extern s16 D_8010CBB6_game_guys_sweet_surprise; // timer
extern f32 D_8010CBB8_game_guys_sweet_surprise; // scale
extern s16 D_8010CBBC_game_guys_sweet_surprise; // state
extern s16 D_8010CBBE_game_guys_sweet_surprise;
extern s16 D_8010CBC0_game_guys_sweet_surprise; // previous choice
extern f32 D_8010CBC4_game_guys_sweet_surprise; // scale
extern s16 D_8010CBC8_game_guys_sweet_surprise; // state
extern GameGuysSweetSurprisePos D_8010CBCC_game_guys_sweet_surprise[2];
extern s16 D_8010CBDC_game_guys_sweet_surprise; // state
extern f32 D_8010CBE0_game_guys_sweet_surprise; // time
extern f32 D_8010CBE4_game_guys_sweet_surprise; // y position
extern s16 D_8010CBE8_game_guys_sweet_surprise; // state
extern f32 D_8010CBEC_game_guys_sweet_surprise; // velocity
extern Vec D_8010CBF0_game_guys_sweet_surprise[2];
extern s16 D_8010CC08_game_guys_sweet_surprise;                            // previous motion
extern s16 D_8010CC0A_game_guys_sweet_surprise;                            // state
extern s16 D_8010CC0C_game_guys_sweet_surprise;                            // timer
extern f32 D_8010CC10_game_guys_sweet_surprise;                            // velocity
extern f32 D_8010CC14_game_guys_sweet_surprise;                            // shadow scale
extern s16 D_8010CC18_game_guys_sweet_surprise;                            // bob direction
extern s16 D_8010CC1A_game_guys_sweet_surprise;                            // bob offset
extern s16 D_8010CC1C_game_guys_sweet_surprise;                            // previous motion
extern f32 D_8010CC20_game_guys_sweet_surprise;                            // shadow scale
extern s16 D_8010CC24_game_guys_sweet_surprise;                            // state
extern s16 D_8010CC26_game_guys_sweet_surprise;                            // timer
extern f32 D_8010CC28_game_guys_sweet_surprise;                            // sway speed
extern f32 D_8010CC2C_game_guys_sweet_surprise;                            // sway angle
extern f32 D_8010CC30_game_guys_sweet_surprise;                            // start x
extern s16 D_8010CC34_game_guys_sweet_surprise;                            // bob direction
extern s16 D_8010CC36_game_guys_sweet_surprise;                            // bob offset
extern f32 D_8010CC38_game_guys_sweet_surprise;                            // segment spacing
extern f32 D_8010CC3C_game_guys_sweet_surprise;                            // bob amplitude
extern s16 D_8010CC40_game_guys_sweet_surprise;                            // previous motion
extern f32 D_8010CC44_game_guys_sweet_surprise;                            // shadow scale
extern s16 D_8010CC48_game_guys_sweet_surprise;                            // state
extern s16 D_8010CC4A_game_guys_sweet_surprise;                            // timer
extern f32 D_8010CC4C_game_guys_sweet_surprise;                            // sway speed
extern f32 D_8010CC50_game_guys_sweet_surprise;                            // sway angle
extern f32 D_8010CC54_game_guys_sweet_surprise;                            // start x
extern s16 D_8010CC58_game_guys_sweet_surprise;                            // state
extern s16 D_8010CC5A_game_guys_sweet_surprise;                            // timer
extern f32 D_8010CC5C_game_guys_sweet_surprise;                            // scale
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
extern s16 D_8010CF78_game_guys_sweet_surprise[]; // sprite IDs
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
extern s16 D_8010D004_game_guys_sweet_surprise; // linked model source

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
void func_80107478_game_guys_sweet_surprise(void);
void func_80107514_game_guys_sweet_surprise(void);
void func_80107550_game_guys_sweet_surprise(void);
void func_80107750_game_guys_sweet_surprise(void);
void func_801077D4_game_guys_sweet_surprise(void);
void func_80107894_game_guys_sweet_surprise(void);
void func_80107A8C_game_guys_sweet_surprise(void);
void func_80107B50_game_guys_sweet_surprise(omObjData *object);
void func_80107B8C_game_guys_sweet_surprise(void);
void func_80107CAC_game_guys_sweet_surprise(void);
void func_80107F74_game_guys_sweet_surprise(void);
void func_80108218_game_guys_sweet_surprise(void);
void func_80108538_game_guys_sweet_surprise(void);
void func_8010878C_game_guys_sweet_surprise(omObjData *object);
void func_80108878_game_guys_sweet_surprise(omObjData *object);
void func_80108AC4_game_guys_sweet_surprise(omObjData *object);
void func_80108CB8_game_guys_sweet_surprise(omObjData *object);
void func_80108FE0_game_guys_sweet_surprise(omObjData *object);
void func_801092F0_game_guys_sweet_surprise(omObjData *object);
void func_80109AA8_game_guys_sweet_surprise(omObjData *object);
void func_80109DE4_game_guys_sweet_surprise(omObjData *object);
void func_8010A604_game_guys_sweet_surprise(omObjData *object);
void func_8010A784_game_guys_sweet_surprise(omObjData *object);
void func_8010A820_game_guys_sweet_surprise(omObjData *object);
void func_8010AA94_game_guys_sweet_surprise(omObjData *object);
void func_8010AAD8_game_guys_sweet_surprise(omObjData *object);
void func_8010AB3C_game_guys_sweet_surprise(omObjData *object);
void func_8010ABD8_game_guys_sweet_surprise(omObjData *object);
void func_8010AC74_game_guys_sweet_surprise(omObjData *object);
void func_8010AD04_game_guys_sweet_surprise(omObjData *object);
s16 func_8010AD94_game_guys_sweet_surprise(s32 dataNum, u16 attr, u16 priority, s16 x, s16 y);
s16 func_8010AE44_game_guys_sweet_surprise(s16 x, s16 y, s16 lines);
void func_8010AEB8_game_guys_sweet_surprise(s16 win, s16 player, s16 mode);
s16 func_8010B004_game_guys_sweet_surprise(s16 win, s16 player, s16 mode, s16 count);
void func_8010B1B4_game_guys_sweet_surprise(s16 win);
Vec2f func_8010B1F4_game_guys_sweet_surprise(f32 x, f32 y, f32 z);

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

void func_80107418_game_guys_sweet_surprise(omObjData *object) {
    func_80107478_game_guys_sweet_surprise();
    func_80107514_game_guys_sweet_surprise();
    func_80107550_game_guys_sweet_surprise();
    func_80107750_game_guys_sweet_surprise();
    func_801077D4_game_guys_sweet_surprise();
    func_80107894_game_guys_sweet_surprise();
    func_80107A8C_game_guys_sweet_surprise();
    object->func = func_80107B50_game_guys_sweet_surprise;
}

void func_80107478_game_guys_sweet_surprise(void) {
    D_8010CF78_game_guys_sweet_surprise[0] = func_8010AD94_game_guys_sweet_surprise(0x660000, 0x4000, 1000, 160, 120);
    D_8010CF78_game_guys_sweet_surprise[1] = func_8010AD94_game_guys_sweet_surprise(0x660001, 0x4000, 1000, 160, 120);
    D_8010CF78_game_guys_sweet_surprise[2] = func_8010AD94_game_guys_sweet_surprise(0x660002, 0x4000, 1000, 160, 120);
    espDispOff(D_8010CF78_game_guys_sweet_surprise[1]);
    espDispOff(D_8010CF78_game_guys_sweet_surprise[2]);
}

void func_80107514_game_guys_sweet_surprise(void) {
    D_8010CF78_game_guys_sweet_surprise[5] = func_8010AD94_game_guys_sweet_surprise(0x660003, 0, 900, 269, 44);
}

void func_80107550_game_guys_sweet_surprise(void) {
    s16 i = 0;
    s16 y = 33;
    s16 x = 280;
    s16 base = 10;

    for (; i < 2; i++) {
        switch (D_8010CF6E_game_guys_sweet_surprise[i]) {
            case 4:
                D_8010CF78_game_guys_sweet_surprise[base + i] = func_8010AD94_game_guys_sweet_surprise(0x66000A, 0, 800, x, y + i * 22);
                break;
            case 8:
                D_8010CF78_game_guys_sweet_surprise[base + i] = func_8010AD94_game_guys_sweet_surprise(0x660006, 0, 800, x, y + i * 22);
                break;
            case 16:
                D_8010CF78_game_guys_sweet_surprise[base + i] = func_8010AD94_game_guys_sweet_surprise(0x660007, 0, 800, x, y + i * 22);
                break;
            case 32:
                D_8010CF78_game_guys_sweet_surprise[base + i] = func_8010AD94_game_guys_sweet_surprise(0x660008, 0, 800, x, y + i * 22);
                break;
            case 64:
                D_8010CF78_game_guys_sweet_surprise[base + i] = func_8010AD94_game_guys_sweet_surprise(0x660009, 0, 800, x, y + i * 22);
                break;
        }
    }
}

void func_80107750_game_guys_sweet_surprise(void) {
    s16 i = 15;

    D_8010CF78_game_guys_sweet_surprise[i] = func_8010AD94_game_guys_sweet_surprise(0x660004, 0, 800, 257, 33);
    D_8010CF78_game_guys_sweet_surprise[i + 1] = func_8010AD94_game_guys_sweet_surprise(0x660005, 0, 800, 257, 55);
    espDispOff(D_8010CF78_game_guys_sweet_surprise[i]);
    espDispOff(D_8010CF78_game_guys_sweet_surprise[i + 1]);
    D_8010CFDE_game_guys_sweet_surprise = 0;
}

void func_801077D4_game_guys_sweet_surprise(void) {
    s32 chr = GwPlayer[D_8010CF58_game_guys_sweet_surprise[0]].chr;
    s32 files[8] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 };
    s16 i = 20;

    D_8010CF78_game_guys_sweet_surprise[i] = func_8010AD94_game_guys_sweet_surprise(files[chr] | 0x210000, 0, 700, 0, 0);
    espDispOff(D_8010CF78_game_guys_sweet_surprise[i]);
    D_8010CFE0_game_guys_sweet_surprise = 0;
}

void func_80107894_game_guys_sweet_surprise(void) {
    Vec2f pos;
    void *data;
    s16 anim;
    s16 i;
    s16 base = 25;

    for (i = 0; i < 2; i++) {
        data = DataRead(0x66000B);
        anim = HuSprAnimRead(data);
        DataClose(data);
        D_8010CF78_game_guys_sweet_surprise[base + i] = HuSprGrpCreate(1, 0);
        HuSprGrpMemberSet(D_8010CF78_game_guys_sweet_surprise[base + i], 0, anim, 0);
        HuSprPriSet(D_8010CF78_game_guys_sweet_surprise[base + i], 0, 100);
        if (i == 0) {
            HuSprAttrReset(D_8010CF78_game_guys_sweet_surprise[base + i], 0, 0xFFFF);
            HuSprAttrSet(D_8010CF78_game_guys_sweet_surprise[base + i], 0, 0);
            pos = func_8010B1F4_game_guys_sweet_surprise(-80.0f, 600.0f, -400.0f);
            HuSprPosSet(D_8010CF78_game_guys_sweet_surprise[base + i], 0, pos.x, pos.y);
        } else if (i == 1) {
            HuSprAttrReset(D_8010CF78_game_guys_sweet_surprise[base + i], 0, 0xFFFF);
            HuSprAttrSet(D_8010CF78_game_guys_sweet_surprise[base + i], 0, 1);
            pos = func_8010B1F4_game_guys_sweet_surprise(80.0f, 600.0f, -400.0f);
            HuSprPosSet(D_8010CF78_game_guys_sweet_surprise[base + i], 0, pos.x, pos.y);
        }
        D_8010CFE4_game_guys_sweet_surprise[i] = 0;
    }
}

void func_80107A8C_game_guys_sweet_surprise(void) {
    s16 i = 30;

    D_8010CF78_game_guys_sweet_surprise[i] = func_8010AD94_game_guys_sweet_surprise(0x21001A, 0, 600, 30, 22);
    D_8010CF78_game_guys_sweet_surprise[i + 1] = func_8010AD94_game_guys_sweet_surprise(0x21001B, 0, 600, 42, 22);
    D_8010CF78_game_guys_sweet_surprise[i + 2] = func_8010AD94_game_guys_sweet_surprise(0x31, 0, 600, 54, 22);
    D_8010CF78_game_guys_sweet_surprise[i + 3] = func_8010AD94_game_guys_sweet_surprise(0x31, 0, 600, 66, 22);
    D_8010CF78_game_guys_sweet_surprise[i + 4] = func_8010AD94_game_guys_sweet_surprise(0x31, 0, 600, 78, 22);
}

void func_80107B50_game_guys_sweet_surprise(omObjData *object) {
    func_80107B8C_game_guys_sweet_surprise();
    func_80107CAC_game_guys_sweet_surprise();
    func_80107F74_game_guys_sweet_surprise();
    func_80108218_game_guys_sweet_surprise();
    func_80108538_game_guys_sweet_surprise();
}

void func_80107B8C_game_guys_sweet_surprise(void) {
    s16 i = 0;

    if (D_8010CBB6_game_guys_sweet_surprise++ >= 5) {
        D_8010CBB6_game_guys_sweet_surprise = 0;
        switch (D_8010CBB4_game_guys_sweet_surprise) {
            case 0:
                espDispOn(D_8010CF78_game_guys_sweet_surprise[i + 1]);
                espDispOff(D_8010CF78_game_guys_sweet_surprise[i + 2]);
                D_8010CBB4_game_guys_sweet_surprise++;
                break;
            case 1:
                espDispOff(D_8010CF78_game_guys_sweet_surprise[i + 1]);
                espDispOn(D_8010CF78_game_guys_sweet_surprise[i + 2]);
                D_8010CBB4_game_guys_sweet_surprise++;
                break;
            case 2:
                espDispOff(D_8010CF78_game_guys_sweet_surprise[i + 1]);
                espDispOff(D_8010CF78_game_guys_sweet_surprise[i + 2]);
                D_8010CBB4_game_guys_sweet_surprise = 0;
                break;
        }
    }
}

void func_80107CAC_game_guys_sweet_surprise(void) {
    s16 i = 15;

    if (D_8010CFDE_game_guys_sweet_surprise == 1) {
        switch (D_8010CBBC_game_guys_sweet_surprise) {
            case 0:
                D_8010CBB8_game_guys_sweet_surprise = 1.0f;
                D_8010CBBE_game_guys_sweet_surprise = 0;
                D_8010CBBC_game_guys_sweet_surprise++;
                break;
            case 1:
                espScaleSet(D_8010CF78_game_guys_sweet_surprise[i + D_8010CF68_game_guys_sweet_surprise],
                            D_8010CBB8_game_guys_sweet_surprise, D_8010CBB8_game_guys_sweet_surprise);
                if (D_8010CBB8_game_guys_sweet_surprise < 1.5f) {
                    D_8010CBB8_game_guys_sweet_surprise += 0.1f;
                } else {
                    D_8010CBBC_game_guys_sweet_surprise++;
                }
                break;
            case 2:
                espScaleSet(D_8010CF78_game_guys_sweet_surprise[i + D_8010CF68_game_guys_sweet_surprise],
                            D_8010CBB8_game_guys_sweet_surprise, D_8010CBB8_game_guys_sweet_surprise);
                if (D_8010CBB8_game_guys_sweet_surprise > 1.1f) {
                    D_8010CBB8_game_guys_sweet_surprise -= 0.1f;
                } else {
                    D_8010CBBC_game_guys_sweet_surprise--;
                }
                break;
        }
        if (D_8010CFE0_game_guys_sweet_surprise == 0) {
            D_8010CBB8_game_guys_sweet_surprise = 1.5f;
            D_8010CBBC_game_guys_sweet_surprise += 2;
            espScaleSet(D_8010CF78_game_guys_sweet_surprise[i + D_8010CF68_game_guys_sweet_surprise],
                        D_8010CBB8_game_guys_sweet_surprise, D_8010CBB8_game_guys_sweet_surprise);
        }
        if (D_8010CBC0_game_guys_sweet_surprise != D_8010CF68_game_guys_sweet_surprise) {
            switch (D_8010CF68_game_guys_sweet_surprise) {
                case 0:
                    espDispOn(D_8010CF78_game_guys_sweet_surprise[i]);
                    espDispOff(D_8010CF78_game_guys_sweet_surprise[i + 1]);
                    D_8010CBBC_game_guys_sweet_surprise = 0;
                    break;
                case 1:
                    espDispOff(D_8010CF78_game_guys_sweet_surprise[i]);
                    espDispOn(D_8010CF78_game_guys_sweet_surprise[i + 1]);
                    D_8010CBBC_game_guys_sweet_surprise = 0;
                    break;
            }
            espScaleSet(D_8010CF78_game_guys_sweet_surprise[i], 1.0f, 1.0f);
            espScaleSet(D_8010CF78_game_guys_sweet_surprise[i + 1], 1.0f, 1.0f);
            D_8010CBC0_game_guys_sweet_surprise = D_8010CF68_game_guys_sweet_surprise;
        }
    }
}

void func_80107F74_game_guys_sweet_surprise(void) {
    s16 i = 20;

    if (D_8010CFE0_game_guys_sweet_surprise == 1) {
        switch (D_8010CBC8_game_guys_sweet_surprise) {
            case 0:
                espPosSet(D_8010CF78_game_guys_sweet_surprise[i],
                          D_8010CBCC_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].x,
                          D_8010CBCC_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].y);
                espScaleSet(D_8010CF78_game_guys_sweet_surprise[i], 0.0f, 0.0f);
                espDispOn(D_8010CF78_game_guys_sweet_surprise[i]);
                D_8010CFDE_game_guys_sweet_surprise = 1;
                D_8010CBC8_game_guys_sweet_surprise++;
                break;
            case 1:
                D_8010CBC4_game_guys_sweet_surprise += 0.25f;
                espScaleSet(D_8010CF78_game_guys_sweet_surprise[i], D_8010CBC4_game_guys_sweet_surprise,
                            D_8010CBC4_game_guys_sweet_surprise);
                if (D_8010CBC4_game_guys_sweet_surprise >= 1.0f) {
                    D_8010CBC4_game_guys_sweet_surprise = 1.0f;
                    D_8010CBC8_game_guys_sweet_surprise++;
                }
                break;
            case 2:
                espPosSet(D_8010CF78_game_guys_sweet_surprise[i],
                          D_8010CBCC_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].x,
                          D_8010CBCC_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].y);
                break;
        }
    } else if (D_8010CFE0_game_guys_sweet_surprise == 0) {
        switch (D_8010CBC8_game_guys_sweet_surprise) {
            case 2:
                espPosSet(D_8010CF78_game_guys_sweet_surprise[i],
                          D_8010CBCC_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].x,
                          D_8010CBCC_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].y);
                espScaleSet(D_8010CF78_game_guys_sweet_surprise[i], 1.0f, 1.0f);
                D_8010CBC8_game_guys_sweet_surprise++;
                break;
            case 3:
                D_8010CBC4_game_guys_sweet_surprise -= 0.25f;
                espScaleSet(D_8010CF78_game_guys_sweet_surprise[i], D_8010CBC4_game_guys_sweet_surprise,
                            D_8010CBC4_game_guys_sweet_surprise);
                if (D_8010CBC4_game_guys_sweet_surprise <= 0.0f) {
                    D_8010CBC4_game_guys_sweet_surprise = 0.0f;
                    D_8010CBC8_game_guys_sweet_surprise++;
                }
                break;
            case 4:
                espDispOff(D_8010CF78_game_guys_sweet_surprise[i]);
                D_8010CBC8_game_guys_sweet_surprise++;
                break;
        }
    }
}

void func_80108218_game_guys_sweet_surprise(void) {
    Vec2f pos;
    s16 i = 0;
    s16 base = 25;

    for (; i < 2; i++) {
        if (D_8010CFE4_game_guys_sweet_surprise[i] == 6) {
            HuSprAttrReset(D_8010CF78_game_guys_sweet_surprise[base + i], 0, 0xFFFF);
            HuSprAttrSet(D_8010CF78_game_guys_sweet_surprise[base + i], 0, 0x8000);
        } else {
            HuSprAttrReset(D_8010CF78_game_guys_sweet_surprise[base + i], 0, 0x8000);
            HuSprBankSet(D_8010CF78_game_guys_sweet_surprise[base + i], 0, D_8010CFE4_game_guys_sweet_surprise[i], 0);
            func_800550F4_main(D_8010CF78_game_guys_sweet_surprise[base + i], 0, 1);
        }
    }
    if (D_8010CFE2_game_guys_sweet_surprise == 1) {
        switch (D_8010CBDC_game_guys_sweet_surprise) {
            case 0:
                D_8010CBE4_game_guys_sweet_surprise = 600.0f;
                D_8010CBE0_game_guys_sweet_surprise = 0.0f;
                HuAudFXPlay(0x53C);
                D_8010CBDC_game_guys_sweet_surprise++;
                break;
            case 1:
                D_8010CBE4_game_guys_sweet_surprise += D_8010CBE0_game_guys_sweet_surprise * D_8010CBE0_game_guys_sweet_surprise * -17.5f;
                if (D_8010CBE0_game_guys_sweet_surprise >= 1.47f) {
                    D_8010CBE0_game_guys_sweet_surprise = 1.47f;
                } else {
                    D_8010CBE0_game_guys_sweet_surprise += 0.22f;
                }
                if (D_8010CBE4_game_guys_sweet_surprise <= 0.0f) {
                    D_8010CBDC_game_guys_sweet_surprise++;
                    D_8010CBE4_game_guys_sweet_surprise = 0.0f;
                }
                break;
            case 2:
                D_8010CFE2_game_guys_sweet_surprise = 0;
                break;
        }
        pos = func_8010B1F4_game_guys_sweet_surprise(-80.0f, D_8010CBE4_game_guys_sweet_surprise, -400.0f);
        HuSprPosSet(D_8010CF78_game_guys_sweet_surprise[base], 0, pos.x, pos.y);
        pos = func_8010B1F4_game_guys_sweet_surprise(80.0f, D_8010CBE4_game_guys_sweet_surprise, -400.0f);
        HuSprPosSet(D_8010CF78_game_guys_sweet_surprise[base + 1], 0, pos.x, pos.y);
    }
}

void func_80108538_game_guys_sweet_surprise(void) {
    s16 i = 30;
    s16 x = 54;
    s16 y = 22;
    s16 *coins = &D_8010CF58_game_guys_sweet_surprise[5];
    s16 hundreds;
    s16 tens;

    if (*coins >= 999) {
        *coins = 999;
    } else if (*coins <= 0) {
        *coins = 0;
    }

    if ((hundreds = D_8010CF58_game_guys_sweet_surprise[5] / 100) == 0) {
        espDispOff(D_8010CF78_game_guys_sweet_surprise[i + 2]);
    } else {
        func_8000BD50_main(D_8010CF78_game_guys_sweet_surprise[i + 2], hundreds);
        espPosSet(D_8010CF78_game_guys_sweet_surprise[i + 2], x, y);
        espDispOn(D_8010CF78_game_guys_sweet_surprise[i + 2]);
        x += 12;
    }

    if ((tens = (s16)(D_8010CF58_game_guys_sweet_surprise[5] % 100) / 10) == 0 &&
        (s16)(D_8010CF58_game_guys_sweet_surprise[5] / 100) == 0) {
        espDispOff(D_8010CF78_game_guys_sweet_surprise[i + 3]);
    } else {
        func_8000BD50_main(D_8010CF78_game_guys_sweet_surprise[i + 3], tens);
        espPosSet(D_8010CF78_game_guys_sweet_surprise[i + 3], x, y);
        espDispOn(D_8010CF78_game_guys_sweet_surprise[i + 3]);
        x += 12;
    }

    func_8000BD50_main(D_8010CF78_game_guys_sweet_surprise[i + 4], D_8010CF58_game_guys_sweet_surprise[5] % 10);
    espPosSet(D_8010CF78_game_guys_sweet_surprise[i + 4], x, y);
    espDispOn(D_8010CF78_game_guys_sweet_surprise[i + 4]);
}

void func_8010878C_game_guys_sweet_surprise(omObjData *object) {
    s32 files[8] = { 0x21001C, 0x21001D, 0x21001E, 0x21001F, 0x210020, 0x210021, 0x210022, 0x210023 };

    object->model[0] = func_8000B108_main(files[(u16)D_8010CF58_game_guys_sweet_surprise[2]], 0x2A9);
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 90.0f, 0.0f, 0.0f);
    omSetSca(object, 2.0f, 2.0f, 2.0f);
    Hu3DModelCameraSet(object->model[0], 0);
    D_8010CFEC_game_guys_sweet_surprise = 0;
    object->func = func_80108878_game_guys_sweet_surprise;
}

void func_80108878_game_guys_sweet_surprise(omObjData *object) {
    if (D_8010CFEC_game_guys_sweet_surprise == 1) {
        switch (D_8010CBE8_game_guys_sweet_surprise) {
            case 0:
                Hu3DModelCameraSet(object->model[0], 1);
                object->trans.x = D_8010CBF0_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].x;
                object->trans.y = 600.0f;
                object->trans.z = D_8010CBF0_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].z;
                object->rot.y = 0.0f;
                D_8010CBEC_game_guys_sweet_surprise = 0.0f;
                D_8010CBE8_game_guys_sweet_surprise++;
                break;
            case 1:
            case 2:
            case 3:
                if (D_8010CBE8_game_guys_sweet_surprise == 1 || D_8010CBE8_game_guys_sweet_surprise == 2) {
                    object->trans.y += D_8010CBEC_game_guys_sweet_surprise * D_8010CBEC_game_guys_sweet_surprise *
                                       (D_8010CBEC_game_guys_sweet_surprise >= 0.0f ? -17.5f : 17.5f);
                } else {
                    object->trans.y += D_8010CBEC_game_guys_sweet_surprise * D_8010CBEC_game_guys_sweet_surprise *
                                       (D_8010CBEC_game_guys_sweet_surprise >= 0.0f ? -8.75f : 8.75f);
                }
                if (D_8010CBEC_game_guys_sweet_surprise < 1.7f) {
                    D_8010CBEC_game_guys_sweet_surprise += 0.11f;
                } else {
                    D_8010CBEC_game_guys_sweet_surprise = 1.7f;
                }
                if (object->trans.y < D_8010CBF0_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].y &&
                    D_8010CBEC_game_guys_sweet_surprise >= 0.0f) {
                    object->trans.y = D_8010CBF0_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].y;
                    if (D_8010CBE8_game_guys_sweet_surprise != 3) {
                        D_8010CBEC_game_guys_sweet_surprise = -1.47f;
                    } else {
                        D_8010CBEC_game_guys_sweet_surprise = 0.0f;
                    }
                    D_8010CBE8_game_guys_sweet_surprise++;
                }
                break;
        }
        object->rot.y += 10.0f;
    }
}

void func_80108AC4_game_guys_sweet_surprise(omObjData *object) {
    s16 i = 0; // initialized early to match register allocation
    s32 attr = 0x2A9;
    s32 files[3] = { 0xA0063, 0xA0064, 9 };
    s32 motions[5] = { 0xA0065, 0xA006E, 0xA006C, 0xA006F, 0xA0071 };

    for (i = 0; i < 3; i++) {
        object->model[i] = func_8000B108_main(files[i], attr);
    }
    omSetTra(object, 0.0f, 0.0f, 200.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    Hu3DModelPosSet(object->model[2], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelRotSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[2], 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 5; i++) {
        func_8000B460_main(object, i, motions[i]);
    }
    D_8010CFEE_game_guys_sweet_surprise = 0;
    Hu3DModelCameraSet(object->model[1], 0);
    func_80017358_main(object->model[1], "c203n30-r_hand", object->model[0], "c203_000_new-r_hand");
    D_8010CFF0_game_guys_sweet_surprise = 0;
    object->func = func_80108CB8_game_guys_sweet_surprise;
}

void func_80108CB8_game_guys_sweet_surprise(omObjData *object) {
    if (D_8010CC08_game_guys_sweet_surprise != D_8010CFEE_game_guys_sweet_surprise) {
        switch (D_8010CFEE_game_guys_sweet_surprise) {
            case 0:
            case 2:
                Hu3DMotionShiftSet(object->model[0],
                                   Hu3DData[object->motion[D_8010CFEE_game_guys_sweet_surprise]].motId, 0, 30, 2);
                break;
            case 1:
            case 3:
            case 4:
                func_8001C5B4_main(object->model[0], object->motion[D_8010CFEE_game_guys_sweet_surprise]);
                break;
        }
        D_8010CC08_game_guys_sweet_surprise = D_8010CFEE_game_guys_sweet_surprise;
    }
    if (D_8010CFF0_game_guys_sweet_surprise == 1) {
        switch (D_8010CC0A_game_guys_sweet_surprise) {
            case 0:
                D_8010CFEE_game_guys_sweet_surprise = 1;
                D_8010CC10_game_guys_sweet_surprise = -1.47f;
                D_8010CC0C_game_guys_sweet_surprise = 0;
                object->trans.y = 0.0f;
                object->trans.z = 200.0f;
                D_8010CC0A_game_guys_sweet_surprise++;
                break;
            case 1:
                if (D_8010CC0C_game_guys_sweet_surprise++ >= 25) {
                    D_8010CC0A_game_guys_sweet_surprise++;
                }
                break;
            case 2:
                object->trans.y += D_8010CC10_game_guys_sweet_surprise * D_8010CC10_game_guys_sweet_surprise *
                                   (D_8010CC10_game_guys_sweet_surprise >= 0.0f ? -35.0f : 35.0f);
                if (object->trans.y <= 0.0f && D_8010CC10_game_guys_sweet_surprise >= 0.0f) {
                    D_8010CC0A_game_guys_sweet_surprise++;
                    object->trans.y = 0.0f;
                }
                if (D_8010CC10_game_guys_sweet_surprise >= 1.47f) {
                    D_8010CC10_game_guys_sweet_surprise = 1.47f;
                } else {
                    D_8010CC10_game_guys_sweet_surprise += 0.11f;
                }
                object->trans.z -= 22.5f;
                break;
            case 3:
                D_8010CFEE_game_guys_sweet_surprise = 0;
                D_8010CFF0_game_guys_sweet_surprise = 0;
                break;
        }
    }
    D_8010CC14_game_guys_sweet_surprise = 1.0f - object->trans.y * 0.001f;
    Hu3DModelPosSet(object->model[2], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[2], D_8010CC14_game_guys_sweet_surprise, D_8010CC14_game_guys_sweet_surprise,
                      D_8010CC14_game_guys_sweet_surprise);
}

void func_80108FE0_game_guys_sweet_surprise(omObjData *object) {
    s16 i = 0; // initialized early to match register allocation
    s32 attr = 0x2A9;
    s32 files[3] = { 0xA00D9, 9, 0xA00E4 };
    s32 motions[4] = { 0xA00DA, 0xA00DE, 0xA00E1, 0xA00E2 };
    void *data;
    s16 anim;

    D_8010D004_game_guys_sweet_surprise = object->model[0] = func_8000B108_main(files[0], 0x2A9);
    object->model[1] = func_8000B108_main(files[1], 0x2A9);
    omSetTra(object, -210.0f, 0.0f, -50.0f);
    omSetRot(object, 0.0f, 90.0f, 0.0f);
    omSetSca(object, 0.6f, 0.6f, 0.6f);
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 2.0f, 1.0f, 2.0f);
    for (i = 0; i < 4; i++) {
        func_8000B460_main(object, i, motions[i]);
    }
    D_8010CFF2_game_guys_sweet_surprise = 0;
    data = DataRead(0xA00E5);
    anim = Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, data, 0, "c165n_4_DEF");
    DataClose(data);
    Hu3DModelRemakeStatic(object->model[0]);
    Hu3DAnimBankSet(anim, 0);
    func_80032FC0_main(anim, 1, 0);
    for (i = 0; i < 4; i++) {
        object->model[i + 2] = func_8000B108_main(files[2], attr);
        Hu3DModelRotSet(object->model[i + 2], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(object->model[i + 2], 0.5f, 0.5f, 0.5f);
    }
    Hu3DModelPosSet(object->model[2], -350.0f, 0.0f, -150.0f);
    Hu3DModelPosSet(object->model[3], -320.0f, 0.0f, -149.0f);
    Hu3DModelPosSet(object->model[4], -290.0f, 0.0f, -148.0f);
    Hu3DModelPosSet(object->model[5], -290.0f, 0.0f, -147.0f);
    object->func = func_801092F0_game_guys_sweet_surprise;
}

void func_801092F0_game_guys_sweet_surprise(omObjData *object) {
    f32 delta;
    f32 angle;
    f32 amplitude;

    if (D_8010CC1C_game_guys_sweet_surprise != D_8010CFF2_game_guys_sweet_surprise) {
        switch (D_8010CFF2_game_guys_sweet_surprise) {
            case 0:
            case 1:
            case 2:
            case 3:
                Hu3DMotionShiftSet(object->model[0],
                                   Hu3DData[object->motion[D_8010CFF2_game_guys_sweet_surprise]].motId, 0, 30, 2);
                break;
        }
        D_8010CC1C_game_guys_sweet_surprise = D_8010CFF2_game_guys_sweet_surprise;
    }
    if (D_8010CFF4_game_guys_sweet_surprise == 0) {
        if (D_8010CFF2_game_guys_sweet_surprise == 2 || D_8010CFF2_game_guys_sweet_surprise == 3) {
            if (object->trans.x < -190.0f) {
                object->trans.x += 5.0f;
            } else {
                D_8010CC2C_game_guys_sweet_surprise += D_8010CC28_game_guys_sweet_surprise;
                if (D_8010CC2C_game_guys_sweet_surprise <= -20.0f || D_8010CC2C_game_guys_sweet_surprise >= 20.0f) {
                    D_8010CC28_game_guys_sweet_surprise = -D_8010CC28_game_guys_sweet_surprise;
                }
                object->rot.y = D_8010CC2C_game_guys_sweet_surprise + 90.0f;
                if (D_8010CC2C_game_guys_sweet_surprise > 0.0f) {
                    object->trans.x = D_8010CC2C_game_guys_sweet_surprise / 2.0f + -190.0f;
                } else {
                    object->trans.x = -190.0f - D_8010CC2C_game_guys_sweet_surprise / 2.0f;
                }
            }
        }
        if (D_8010CFF2_game_guys_sweet_surprise == 2) {
            if (Hu3DData[object->model[0]].motTime == 4.0f) {
                HuAudFXPlay(0x53A);
            }
        } else if (D_8010CFF2_game_guys_sweet_surprise == 3) {
            if (Hu3DData[object->model[0]].motTime == 8.0f) {
                HuAudFXPlay(0x53A);
            }
        }
    }
    D_8010CC20_game_guys_sweet_surprise = 2.0f - object->trans.y * 0.002f;
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[1], D_8010CC20_game_guys_sweet_surprise, D_8010CC20_game_guys_sweet_surprise,
                      D_8010CC20_game_guys_sweet_surprise);
    delta = (object->trans.x - 90.0f - Hu3DData[object->model[2]].pos.x) / 3.0f;
    Hu3DData[object->model[3]].pos.x = delta + Hu3DData[object->model[2]].pos.x;
    Hu3DData[object->model[4]].pos.x = delta + Hu3DData[object->model[3]].pos.x;
    Hu3DData[object->model[5]].pos.x = delta + Hu3DData[object->model[4]].pos.x;
    if (D_8010CC1A_game_guys_sweet_surprise >= 4) {
        D_8010CC18_game_guys_sweet_surprise = -1;
    } else if (D_8010CC1A_game_guys_sweet_surprise < -3) {
        D_8010CC18_game_guys_sweet_surprise = 1;
    }
    D_8010CC1A_game_guys_sweet_surprise += D_8010CC18_game_guys_sweet_surprise;
    amplitude = 10.0f;
    angle = delta * 3.0f * 0.45f;
    Hu3DData[object->model[3]].pos.y = sindf(sindf(angle) * 30.0f) * amplitude + D_8010CC1A_game_guys_sweet_surprise;
    Hu3DData[object->model[4]].pos.y = sindf(sindf(angle) * 60.0f) * 20.0f - D_8010CC1A_game_guys_sweet_surprise;
    Hu3DData[object->model[5]].pos.y = sindf(sindf(angle) * 90.0f) * 30.0f + D_8010CC1A_game_guys_sweet_surprise;
    if (D_8010CFF4_game_guys_sweet_surprise == 1) {
        switch (D_8010CC24_game_guys_sweet_surprise) {
            case 0:
                D_8010CC26_game_guys_sweet_surprise = 0;
                D_8010CC30_game_guys_sweet_surprise = object->trans.x;
                D_8010CC24_game_guys_sweet_surprise++;
                break;
            case 1:
                object->trans.x = sindf(D_8010CC26_game_guys_sweet_surprise++ * 4.5f) * 100.0f +
                                  D_8010CC30_game_guys_sweet_surprise;
                if (D_8010CC26_game_guys_sweet_surprise >= 21) {
                    D_8010CC26_game_guys_sweet_surprise = 0;
                    D_8010CC24_game_guys_sweet_surprise++;
                }
                break;
            case 2:
                object->rot.y = 90.0f - sindf(D_8010CC26_game_guys_sweet_surprise++ * 9.0f) * 90.0f;
                if (object->rot.y <= 0.0f || D_8010CC26_game_guys_sweet_surprise >= 11) {
                    D_8010CC24_game_guys_sweet_surprise++;
                }
                break;
            case 3:
                HuAudFXPlay(0x53E);
                D_8010CFF2_game_guys_sweet_surprise = 2;
                D_8010CC24_game_guys_sweet_surprise++;
                break;
        }
    }
    if (D_8010CFF4_game_guys_sweet_surprise == 3) {
        if (object->rot.y == 90.0f) {
            D_8010CFF4_game_guys_sweet_surprise = 0;
        } else if (object->rot.y > 90.0f) {
            object->rot.y -= 1.0f;
            if (object->rot.y <= 90.0f) {
                object->rot.y = 90.0f;
                D_8010CFF4_game_guys_sweet_surprise = 0;
            }
        } else if (object->rot.y < 90.0f) {
            object->rot.y += 1.0f;
            if (object->rot.y >= 90.0f) {
                object->rot.y = 90.0f;
                D_8010CFF4_game_guys_sweet_surprise = 0;
            }
        }
    }
}

void func_80109AA8_game_guys_sweet_surprise(omObjData *object) {
    s16 i = 0; // initialized early to match register allocation
    s32 attr = 0x2A9;
    s32 files[4] = { 0xA00D9, 9, 0xA00E4, 0 };
    s32 motions[4] = { 0xA00DA, 0xA00DE, 0xA00E1, 0xA00E2 };
    void *data;
    s16 anim;

    object->model[0] = Hu3DModelLink(D_8010D004_game_guys_sweet_surprise);
    object->model[1] = func_8000B108_main(files[1], 0x2A9);
    omSetTra(object, 195.0f, 0.0f, -100.0f);
    omSetRot(object, 0.0f, 270.0f, 0.0f);
    omSetSca(object, 0.3f, 0.3f, 0.3f);
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 4; i++) {
        func_8000B460_main(object, i, motions[i]);
    }
    D_8010CFF6_game_guys_sweet_surprise = 0;
    data = DataRead(0xA00E5);
    anim = Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, data, 0, "c165n_4_DEF");
    DataClose(data);
    Hu3DModelRemakeStatic(object->model[0]);
    Hu3DAnimBankSet(anim, 0);
    func_80032FC0_main(anim, 1, 0);
    for (i = 0; i < 4; i++) {
        object->model[i + 2] = func_8000B108_main(files[2], attr);
    }
    for (i = 0; i < 4; i++) {
        Hu3DModelRotSet(object->model[i + 2], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(object->model[i + 2], 0.3f, 0.3f, 0.3f);
    }
    Hu3DModelPosSet(object->model[2], 350.0f, 0.0f, -150.0f);
    Hu3DModelPosSet(object->model[3], 320.0f, 0.0f, -150.0f);
    Hu3DModelPosSet(object->model[4], 290.0f, 0.0f, -150.0f);
    Hu3DModelPosSet(object->model[5], 280.0f, 70.0f, -150.0f);
    object->func = func_80109DE4_game_guys_sweet_surprise;
}

void func_80109DE4_game_guys_sweet_surprise(omObjData *object) {
    if (D_8010CC40_game_guys_sweet_surprise != D_8010CFF6_game_guys_sweet_surprise) {
        switch (D_8010CFF6_game_guys_sweet_surprise) {
            case 0:
            case 1:
            case 2:
            case 3:
                Hu3DMotionShiftSet(object->model[0],
                                   Hu3DData[object->motion[D_8010CFF6_game_guys_sweet_surprise]].motId, 0, 30, 2);
                break;
        }
        D_8010CC40_game_guys_sweet_surprise = D_8010CFF6_game_guys_sweet_surprise;
    }
    if (D_8010CFF8_game_guys_sweet_surprise == 0) {
        if (D_8010CFF6_game_guys_sweet_surprise == 2 || D_8010CFF6_game_guys_sweet_surprise == 3) {
            if (object->trans.x > 175.0f) {
                object->trans.x -= 5.0f;
            } else {
                D_8010CC50_game_guys_sweet_surprise += D_8010CC4C_game_guys_sweet_surprise;
                if (D_8010CC50_game_guys_sweet_surprise <= -20.0f || D_8010CC50_game_guys_sweet_surprise >= 20.0f) {
                    D_8010CC4C_game_guys_sweet_surprise = -D_8010CC4C_game_guys_sweet_surprise;
                }
                object->rot.y = D_8010CC50_game_guys_sweet_surprise + 270.0f;
                if (D_8010CC50_game_guys_sweet_surprise > 0.0f) {
                    object->trans.x = 175.0f - D_8010CC50_game_guys_sweet_surprise / 2.0f;
                } else {
                    object->trans.x = D_8010CC50_game_guys_sweet_surprise / 2.0f + 175.0f;
                }
            }
        }
        if (D_8010CFF6_game_guys_sweet_surprise == 2) {
            if (Hu3DData[object->model[0]].motTime == 4.0f) {
                HuAudFXPlay(0x53B);
            }
        } else if (D_8010CFF6_game_guys_sweet_surprise == 3) {
            if (Hu3DData[object->model[0]].motTime == 8.0f) {
                HuAudFXPlay(0x53B);
            }
        }
    }
    D_8010CC44_game_guys_sweet_surprise = 1.0f - object->trans.y * 0.001f;
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[1], D_8010CC44_game_guys_sweet_surprise, D_8010CC44_game_guys_sweet_surprise,
                      D_8010CC44_game_guys_sweet_surprise);
    D_8010CC38_game_guys_sweet_surprise = (object->trans.x + 60.0f - Hu3DData[object->model[2]].pos.x) / 3.0f;
    Hu3DData[object->model[3]].pos.x = Hu3DData[object->model[2]].pos.x + D_8010CC38_game_guys_sweet_surprise;
    Hu3DData[object->model[4]].pos.x = Hu3DData[object->model[3]].pos.x + D_8010CC38_game_guys_sweet_surprise;
    Hu3DData[object->model[5]].pos.x = Hu3DData[object->model[4]].pos.x + D_8010CC38_game_guys_sweet_surprise;
    if (D_8010CC36_game_guys_sweet_surprise >= 2) {
        D_8010CC34_game_guys_sweet_surprise = -1;
    } else if (D_8010CC36_game_guys_sweet_surprise < -1) {
        D_8010CC34_game_guys_sweet_surprise = 1;
    }
    D_8010CC36_game_guys_sweet_surprise += D_8010CC34_game_guys_sweet_surprise;
    D_8010CC3C_game_guys_sweet_surprise = 20.0f / 3.0f;
    Hu3DData[object->model[3]].pos.y =
        sindf(sindf(D_8010CC38_game_guys_sweet_surprise * 3.0f * -0.225f) * 30.0f) * D_8010CC3C_game_guys_sweet_surprise +
        D_8010CC36_game_guys_sweet_surprise;
    Hu3DData[object->model[4]].pos.y =
        D_8010CC3C_game_guys_sweet_surprise * 2.0f *
            sindf(sindf(D_8010CC38_game_guys_sweet_surprise * 3.0f * -0.225f) * 60.0f) -
        D_8010CC36_game_guys_sweet_surprise;
    Hu3DData[object->model[5]].pos.y =
        D_8010CC3C_game_guys_sweet_surprise * 3.0f *
            sindf(sindf(D_8010CC38_game_guys_sweet_surprise * 3.0f * -0.225f) * 90.0f) +
        D_8010CC36_game_guys_sweet_surprise;
    if (D_8010CFF8_game_guys_sweet_surprise == 1) {
        switch (D_8010CC48_game_guys_sweet_surprise) {
            case 0:
                D_8010CC4A_game_guys_sweet_surprise = 0;
                D_8010CC54_game_guys_sweet_surprise = object->trans.x;
                D_8010CC48_game_guys_sweet_surprise++;
                break;
            case 1:
                object->trans.x = D_8010CC54_game_guys_sweet_surprise -
                                  sindf(D_8010CC4A_game_guys_sweet_surprise++ * 4.5f) * 100.0f;
                if (D_8010CC4A_game_guys_sweet_surprise >= 21) {
                    D_8010CC4A_game_guys_sweet_surprise = 0;
                    D_8010CC48_game_guys_sweet_surprise++;
                }
                break;
            case 2:
                object->rot.y = sindf(D_8010CC4A_game_guys_sweet_surprise++ * 9.0f) * 90.0f + 270.0f;
                if (object->rot.y >= 360.0f || D_8010CC4A_game_guys_sweet_surprise >= 11) {
                    D_8010CC48_game_guys_sweet_surprise++;
                }
                break;
            case 3:
                HuAudFXPlay(0x53F);
                D_8010CFF6_game_guys_sweet_surprise = 2;
                D_8010CC48_game_guys_sweet_surprise++;
                break;
        }
    }
    if (D_8010CFF8_game_guys_sweet_surprise == 3) {
        if (object->rot.y == 270.0f) {
            D_8010CFF8_game_guys_sweet_surprise = 0;
        } else if (object->rot.y > 270.0f) {
            object->rot.y -= 1.0f;
            if (object->rot.y <= 270.0f) {
                object->rot.y = 270.0f;
                D_8010CFF8_game_guys_sweet_surprise = 0;
            }
        } else if (object->rot.y < 270.0f) {
            object->rot.y += 1.0f;
            if (object->rot.y >= 270.0f) {
                object->rot.y = 270.0f;
                D_8010CFF8_game_guys_sweet_surprise = 0;
            }
        }
    }
}

void func_8010A604_game_guys_sweet_surprise(omObjData *object) {
    s16 i = 0; // initialized early to match register allocation
    s32 attr = 0x2A9;
    s32 files[2] = { 0x66000D, 9 };

    for (i = 0; i < 2; i++) {
        object->model[i] = func_8000B108_main(files[i], attr);
    }
    omSetTra(object, 125.0f, 200.0f, -430.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 1.0f, 1.0f, 1.0f);
    omAddObj(0x64, 0xA, 0xA, -1, func_8010A784_game_guys_sweet_surprise);
    Hu3DModelCameraSet(object->model[0], 0);
    Hu3DModelCameraSet(object->model[1], 0);
    D_8010CFFA_game_guys_sweet_surprise = 0;
    object->func = func_8010A820_game_guys_sweet_surprise;
}

void func_8010A784_game_guys_sweet_surprise(omObjData *object) {
    object->model[0] = func_8000B108_main(0xB0006, 0x2A9);
    omSetTra(object, 125.0f, 125.0f, -400.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 2.0f, 2.0f, 2.0f);
    func_8000B460_main(object, 0, 0xB0006);
    object->func = func_8010AA94_game_guys_sweet_surprise;
    D_8010CFFC_game_guys_sweet_surprise = 0;
}

void func_8010A820_game_guys_sweet_surprise(omObjData *object) {
    f32 shadowScale;

    if (D_8010CFFA_game_guys_sweet_surprise == 1) {
        D_8010CC5C_game_guys_sweet_surprise = 1.5f;
        object->scale.x = object->scale.y = object->scale.z = D_8010CC5C_game_guys_sweet_surprise;
        D_8010CC5A_game_guys_sweet_surprise = 0;
        D_8010CFFA_game_guys_sweet_surprise = 0;
    }
    if (D_8010CFF0_game_guys_sweet_surprise == 1) {
        switch (D_8010CC58_game_guys_sweet_surprise) {
            case 0:
                HuAudFXPlay(0x53D);
                object->scale.x = object->scale.y = object->scale.z = 0.0f;
                Hu3DModelCameraSet(object->model[0], 1);
                Hu3DModelCameraSet(object->model[1], 1);
                D_8010CC58_game_guys_sweet_surprise++;
                break;
            case 1:
                if (object->scale.x < 2.0f) {
                    object->scale.x = object->scale.y = object->scale.z = object->scale.z + 1.0f;
                } else {
                    D_8010CC58_game_guys_sweet_surprise++;
                }
                break;
            case 2:
                if (object->scale.x > 1.0f) {
                    object->scale.x = object->scale.y = object->scale.z = object->scale.z - 0.5f;
                } else {
                    object->scale.x = object->scale.y = object->scale.z = 1.0f;
                    D_8010CC58_game_guys_sweet_surprise++;
                }
                break;
        }
    } else if (D_8010CC5C_game_guys_sweet_surprise > 1.0f) {
        if ((D_8010CC5A_game_guys_sweet_surprise++ & 1) == 0) {
            object->scale.x = object->scale.y = object->scale.z = 1.0f;
        } else {
            D_8010CC5C_game_guys_sweet_surprise -= 0.05f;
            object->scale.x = object->scale.y = object->scale.z = D_8010CC5C_game_guys_sweet_surprise;
        }
    } else {
        D_8010CC5C_game_guys_sweet_surprise = 1.0f;
        object->scale.x = object->scale.y = object->scale.z = D_8010CC5C_game_guys_sweet_surprise;
    }
    shadowScale = 1.0f - object->trans.y * 0.001f;
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[1], shadowScale, shadowScale, shadowScale);
}

void func_8010AA94_game_guys_sweet_surprise(omObjData *object) {
    if (D_8010CFFC_game_guys_sweet_surprise == 1) {
        func_8001C5B4_main(object->model[0], object->motion[0]);
        D_8010CFFC_game_guys_sweet_surprise = 0;
    }
}

void func_8010AAD8_game_guys_sweet_surprise(omObjData *object) {
    omAddObj(0xC8, 0xA, 0xA, -1, func_8010AB3C_game_guys_sweet_surprise);
    omAddObj(0x12C, 0xA, 0xA, -1, func_8010ABD8_game_guys_sweet_surprise);
    object->func = NULL;
}

void func_8010AB3C_game_guys_sweet_surprise(omObjData *object) {
    object->model[0] = func_8000B108_main(0x66000E, 0x2A9);
    omSetTra(object, -80.0f, 0.0f, -400.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 2.0f, 2.0f, 2.0f);
    func_8000B460_main(object, 0, 0x66000E);
    object->func = func_8010AC74_game_guys_sweet_surprise;
    D_8010CFEA_game_guys_sweet_surprise = 0;
}

void func_8010ABD8_game_guys_sweet_surprise(omObjData *object) {
    object->model[0] = func_8000B108_main(0x66000E, 0x2A9);
    omSetTra(object, 80.0f, 0.0f, -400.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 2.0f, 2.0f, 2.0f);
    func_8000B460_main(object, 0, 0x66000E);
    object->func = func_8010AD04_game_guys_sweet_surprise;
    D_8010CFE8_game_guys_sweet_surprise = 0;
}

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

s16 func_8010AD94_game_guys_sweet_surprise(s32 dataNum, u16 attr, u16 priority, s16 x, s16 y) {
    s16 sprite = espEntry(func_8000B838_main(dataNum), 0, 0);

    espAttrSet(sprite, attr | 8);
    espPriSet(sprite, priority);
    espPosSet(sprite, x, y);
    return sprite;
}

s16 func_8010AE44_game_guys_sweet_surprise(s16 x, s16 y, s16 lines) {
    s16 win;

    win = func_80060880_main(x, y, lines);
    func_8005B63C_main(win, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
    func_80061100_main(win, 1);
    HuWinMesSpeedSet(win, 0);
    HuWinHomeClear(win);
    return win;
}

void func_8010AEB8_game_guys_sweet_surprise(s16 win, s16 player, s16 mode) {
    s16 i;

    HuWinComKeyReset();
    while (HuWinStatGet(win) != 0) {
        switch (mode) {
            case 0:
                if (D_800D5558_main[player] & 0x8000) {
                    HuWinComKeySet(-0x8000, -0x8000, -0x8000, -0x8000);
                }
                break;
            case 1:
                for (i = 0; i < 10; i++) {
                    HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000,
                                    D_8010CB70_game_guys_sweet_surprise[D_8010D002_game_guys_sweet_surprise]);
                }
                while (HuWinStatGet(win) != 0) {
                    HuPrcVSleep();
                }
                break;
        }
        HuPrcVSleep();
    }
    HuWinComKeyReset();
}

s16 func_8010B004_game_guys_sweet_surprise(s16 win, s16 player, s16 mode, s16 count) {
    s16 keys[4] = { 0, 0, 0, 0 };
    s16 players[4] = { 1, 2, 4, 8 };
    s16 i;

    switch (mode) {
        case 0:
            keys[player] = -1;
            func_8005B63C_main(win, HUWIN_ATTR_COMKEY, HUWIN_ATTR_NONE);
            HuWinActivePlayerSet(win, players[player]);
            HuWinComKeySet(keys[0], keys[1], keys[2], keys[3]);
            break;
        case 1:
            for (i = 0; i < count; i++) {
                HuWinComKeyWait(0x400, 0x400, 0x400, 0x400,
                                D_8010CB70_game_guys_sweet_surprise[D_8010D002_game_guys_sweet_surprise]);
            }
            HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000,
                            D_8010CB70_game_guys_sweet_surprise[D_8010D002_game_guys_sweet_surprise]);
            break;
    }
    return HuWinChoiceGet(win, 0, 1);
}

void func_8010B1B4_game_guys_sweet_surprise(s16 win) {
    HuWinHomeClear(win);
    func_80060EA8_main(win, 1);
    HuWinExCleanup(win);
}

Vec2f func_8010B1F4_game_guys_sweet_surprise(f32 x, f32 y, f32 z) {
    Vec pos;
    Vec2f screenPos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    Hu3D3Dto2D(0, &pos, &screenPos);
    return screenPos;
}
