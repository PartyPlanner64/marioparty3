#include "common.h"
#include "game_guys_lucky_7.h"

typedef struct GameGuysLucky7SpriteDef {
    /* 0x00 */ s32 dataNum;
    /* 0x04 */ s32 priority;
    /* 0x08 */ s32 x;
    /* 0x0C */ s32 y;
} GameGuysLucky7SpriteDef;

typedef struct GameGuysLucky7SpritePos {
    /* 0x00 */ s32 dataNum;
    /* 0x04 */ s32 x;
    /* 0x08 */ s32 y;
} GameGuysLucky7SpritePos;

typedef struct GameGuysLucky7PadValues {
    /* 0x00 */ s16 v[4]; // one entry per controller port
} GameGuysLucky7PadValues;

typedef struct GameGuysLucky7BssD6DC { // 0x14 bytes
    /* 0x00 */ u16 playerInfo[7];
    /* 0x0E */ u16 sprites[3];
} GameGuysLucky7BssD6DC;

s16 D_8010D150_game_guys_lucky_7[9][3] = {
    { 190, 150, 13 },
    { 220, 165, 15 },
    { 195, 150, 15 },
    { 170, 140, 15 },
    { 190, 115, 13 },
    { 155, 115, 14 },
    { 130, 105, 14 },
    { 100, 100, 14 },
    { 50, 190, 14 },
}; // window x, y, lines
s16 D_8010D188_game_guys_lucky_7[3] = { 5, 25, 60 }; // COM key wait frames, indexed by CPU difficulty
u16 D_8010D18E_game_guys_lucky_7 = 0;                // main state
u16 D_8010D190_game_guys_lucky_7 = 0;                // main state timer

char D_8010D5D0_game_guys_lucky_7[0x100] BSS;
s16 D_8010D6D0_game_guys_lucky_7 BSS;
Process *D_8010D6D4_game_guys_lucky_7 BSS;
Process *D_8010D6D8_game_guys_lucky_7 BSS;
// [0] player index, [1] pad, [2] chr, [3] cpu flag, [4] cpu difficulty, [5] coins, [6] coins
GameGuysLucky7BssD6DC gameGuysLucky7BssD6DC BSS;
extern u16 D_8010D6DC_game_guys_lucky_7[7]; // gameGuysLucky7BssD6DC.playerInfo
extern u16 D_8010D6EA_game_guys_lucky_7[3]; // gameGuysLucky7BssD6DC.sprites
u16 D_8010D6F0_game_guys_lucky_7[7] BSS;
f32 D_8010D700_game_guys_lucky_7[7] BSS;
u16 D_8010D71C_game_guys_lucky_7[5] BSS;
u16 D_8010D726_game_guys_lucky_7 BSS;
u16 D_8010D728_game_guys_lucky_7 BSS;
f32 D_8010D72C_game_guys_lucky_7 BSS;
f32 D_8010D730_game_guys_lucky_7 BSS;
f32 D_8010D734_game_guys_lucky_7 BSS;
f32 D_8010D738_game_guys_lucky_7 BSS;
u16 D_8010D73C_game_guys_lucky_7 BSS;
u16 D_8010D73E_game_guys_lucky_7 BSS;
s16 D_8010D740_game_guys_lucky_7 BSS;
u16 D_8010D742_game_guys_lucky_7 BSS;
u16 D_8010D744_game_guys_lucky_7 BSS;
u16 D_8010D746_game_guys_lucky_7 BSS; // player motion
f32 D_8010D748_game_guys_lucky_7 BSS;
f32 D_8010D74C_game_guys_lucky_7 BSS;
f32 D_8010D750_game_guys_lucky_7 BSS;
f32 D_8010D754_game_guys_lucky_7 BSS;
u16 D_8010D758_game_guys_lucky_7 BSS;
f32 D_8010D75C_game_guys_lucky_7 BSS;
f32 D_8010D760_game_guys_lucky_7 BSS;
f32 D_8010D764_game_guys_lucky_7 BSS;
u16 D_8010D768_game_guys_lucky_7 BSS;
u16 D_8010D76A_game_guys_lucky_7 BSS;
u16 D_8010D76C_game_guys_lucky_7 BSS;
u16 D_8010D76E_game_guys_lucky_7 BSS;
u16 D_8010D770_game_guys_lucky_7 BSS;
u16 D_8010D772_game_guys_lucky_7 BSS;
u16 D_8010D774_game_guys_lucky_7 BSS;
u16 D_8010D776_game_guys_lucky_7 BSS;
u16 D_8010D778_game_guys_lucky_7 BSS;
u16 D_8010D77A_game_guys_lucky_7 BSS;
u16 D_8010D77C_game_guys_lucky_7 BSS;
u8 D_8010D780_game_guys_lucky_7[0x18] BSS; /* Unreferenced. */
s16 D_8010D798_game_guys_lucky_7[52] BSS;  // spark models
s16 D_8010D800_game_guys_lucky_7 BSS;
s16 D_8010D802_game_guys_lucky_7 BSS;
s16 D_8010D804_game_guys_lucky_7 BSS;
extern const GameGuysLucky7PadValues D_8010D598_game_guys_lucky_7; // COM keys
extern const GameGuysLucky7PadValues D_8010D5A0_game_guys_lucky_7; // active players
extern s32 omCharModelNoTbl[][6];

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
void func_80107FD8_game_guys_lucky_7(void);
void func_801080E8_game_guys_lucky_7(void);
void func_8010826C_game_guys_lucky_7(void);
void func_80108374_game_guys_lucky_7(omObjData *object);
void func_801083A0_game_guys_lucky_7(void);
void func_80108498_game_guys_lucky_7(void);
void func_801085D4_game_guys_lucky_7(void);
void func_801087B4_game_guys_lucky_7(omObjData *object);
void func_80108B64_game_guys_lucky_7(omObjData *object);
void func_801092B0_game_guys_lucky_7(omObjData *object);
void func_80109570_game_guys_lucky_7(omObjData *object);
void func_80109FA4_game_guys_lucky_7(omObjData *object);
void func_8010A04C_game_guys_lucky_7(omObjData *object);
void func_8010A0DC_game_guys_lucky_7(omObjData *object);
void func_8010A19C_game_guys_lucky_7(omObjData *object);
void func_8010A278_game_guys_lucky_7(omObjData *object);
void func_8010A328_game_guys_lucky_7(omObjData *object);
void func_8010A3B8_game_guys_lucky_7(omObjData *object);
void func_8010A458_game_guys_lucky_7(omObjData *object);
void func_8010A8A4_game_guys_lucky_7(omObjData *object);
void func_8010AA8C_game_guys_lucky_7(omObjData *object);
void func_8010B334_game_guys_lucky_7(void);
void func_8010B498_game_guys_lucky_7(omObjData *object);
void func_8010B528_game_guys_lucky_7(s16 model);
void func_8010B6E0_game_guys_lucky_7(s16 model);
s16 func_8010AD44_game_guys_lucky_7(s16 x, s16 y, s16 lines);
void func_8010ADB8_game_guys_lucky_7(s16 win);
void func_8010ADF8_game_guys_lucky_7(s16 win, s16 player, s16 mode);
s16 func_8010AF44_game_guys_lucky_7(s16 win, s16 player, s16 mode, s16 count);
s16 func_8010B13C_game_guys_lucky_7(s16 win, s16 player, s16 mode, s16 count);

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
    MapCollInit(32);
    Hu3DSprModelInit(32);
    omInitObjMan(32, 32);
    omGameSysInit();
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
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
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

char *D_8010D194_game_guys_lucky_7[] = {
    "\x82\x6C\x82\x60\x82\x71\x82\x68\x82\x6E",                 // ＭＡＲＩＯ
    "\x82\x6B\x82\x74\x82\x68\x82\x66\x82\x68",                 // ＬＵＩＧＩ
    "\x82\x6F\x82\x64\x82\x60\x82\x62\x82\x67",                 // ＰＥＡＣＨ
    "\x82\x78\x82\x6E\x82\x72\x82\x67\x82\x68",                 // ＹＯＳＨＩ
    "\x82\x76\x82\x60\x82\x71\x82\x68\x82\x6E",                 // ＷＡＲＩＯ
    "\x82\x63\x82\x6A",                                         // ＤＫ
    "\x82\x76\x82\x60\x82\x6B\x82\x74\x82\x68\x82\x66\x82\x68", // ＷＡＬＵＩＧＩ
    "\x82\x63\x82\x60\x82\x68\x82\x72\x82\x78",                 // ＤＡＩＳＹ
}; // character names

s16 D_8010D1B4_game_guys_lucky_7 = 0; // state
s16 D_8010D1B6_game_guys_lucky_7 = 0; // timer
u16 D_8010D1B8_game_guys_lucky_7 = 0; // state
u16 D_8010D1BA_game_guys_lucky_7 = 0;
f32 D_8010D1BC_game_guys_lucky_7 = 0.0f;
u16 D_8010D1C0_game_guys_lucky_7 = 0;
u16 D_8010D1C2_game_guys_lucky_7 = 0; // state
u16 D_8010D1C4_game_guys_lucky_7 = 0;
u16 D_8010D1C6_game_guys_lucky_7 = 0;  // state
u16 D_8010D1C8_game_guys_lucky_7 = 0;  // timer
u16 D_8010D1CA_game_guys_lucky_7 = 0;  // countdown tick timer
u16 D_8010D1CC_game_guys_lucky_7 = 10; // countdown seconds
u16 D_8010D1CE_game_guys_lucky_7 = 0;
u16 D_8010D1D0_game_guys_lucky_7 = 0;
u16 D_8010D1D2_game_guys_lucky_7 = 0; // state
u16 D_8010D1D4_game_guys_lucky_7 = 0; // state
f32 D_8010D1D8_game_guys_lucky_7 = 0.0f;
u16 D_8010D1DC_game_guys_lucky_7 = 1; // state
f32 D_8010D1E0_game_guys_lucky_7 = 0.0f;
u16 D_8010D1E4_game_guys_lucky_7 = 0;
u16 D_8010D1E6_game_guys_lucky_7 = 0;   // timer
u16 D_8010D1E8_game_guys_lucky_7 = 0;   // state
u16 D_8010D1EA_game_guys_lucky_7 = 999; // previous player motion
u16 D_8010D1EC_game_guys_lucky_7 = 0;   // state
u16 D_8010D1EE_game_guys_lucky_7 = 0;   // timer
f32 D_8010D1F0_game_guys_lucky_7 = 0.0f;
u16 D_8010D1F4_game_guys_lucky_7 = 0;
f32 D_8010D1F8_game_guys_lucky_7 = 250.0f; /* Unreferenced. */
Vec D_8010D1FC_game_guys_lucky_7[7] = {
    { 75.0f, 0.0f, 150.0f },
    { 125.0f, 0.0f, 50.0f },
    { 175.0f, 0.0f, -50.0f },
    { 225.0f, 0.0f, -150.0f },
    { 275.0f, 0.0f, -250.0f },
    { 325.0f, 0.0f, -350.0f },
    { 375.0f, 0.0f, -450.0f },
};
f32 D_8010D250_game_guys_lucky_7[2] = { 425.0f, 0.0f }; // read as D_8010D1FC[7].x
u16 D_8010D258_game_guys_lucky_7 = 999;                 // previous motion
u16 D_8010D25A_game_guys_lucky_7 = 0;                   // state
u16 D_8010D25C_game_guys_lucky_7 = 0;                   // timer
f32 D_8010D260_game_guys_lucky_7 = 0.0f;
u16 D_8010D264_game_guys_lucky_7 = 0;
f32 D_8010D268_game_guys_lucky_7 = 300.0f; /* Unreferenced. */
Vec D_8010D26C_game_guys_lucky_7[7] = {
    { 100.0f, -100.0f, 200.0f },
    { 150.0f, -100.0f, 100.0f },
    { 200.0f, -100.0f, 0.0f },
    { 250.0f, -100.0f, -100.0f },
    { 300.0f, -100.0f, -200.0f },
    { 350.0f, -100.0f, -300.0f },
    { 375.0f, -100.0f, -450.0f },
};
f32 D_8010D2C0_game_guys_lucky_7[2] = { 425.0f, -100.0f }; // read as D_8010D26C[7].x
u16 D_8010D2C8_game_guys_lucky_7 = 0;
f32 D_8010D2CC_game_guys_lucky_7 = 0.0f;
f32 D_8010D2D0_game_guys_lucky_7 = 0.0f;
f32 D_8010D2D4_game_guys_lucky_7 = 0.0f;
f32 D_8010D2D8_game_guys_lucky_7 = 0.0f;
f32 D_8010D2DC_game_guys_lucky_7 = 0.0f;
u16 D_8010D2E0_game_guys_lucky_7 = 0;
f32 D_8010D2E4_game_guys_lucky_7 = 0.0f;
f32 D_8010D2E8_game_guys_lucky_7 = 0.0f;
u16 D_8010D2EC_game_guys_lucky_7 = 0;
s32 D_8010D2F0_game_guys_lucky_7[] = { 0xB002B, 0xB002C, 0xB002D, 0xB002E }; // spark model files

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
                        GMesTimeMaxSet(D_8010D6D0_game_guys_lucky_7, 0x78);
                        break;
                    case 0:
                        HuAudSeqPlay(0x71);
                        sprintf(D_8010D5D0_game_guys_lucky_7,
                                "%s\x81\x40\x82\x6B\x82\x6E\x82\x72\x82\x73\x81\x49",
                                D_8010D194_game_guys_lucky_7[D_8010D6DC_game_guys_lucky_7[2]]);
                        D_8010D6D0_game_guys_lucky_7 =
                            GMesCreate(0x19, D_8010D5D0_game_guys_lucky_7, 0xA0, 0x78, 1.0, 1.0, 1);
                        GMesTimeMaxSet(D_8010D6D0_game_guys_lucky_7, 0x78);
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
        case 999:
            break;
    }
}

void func_80106370_game_guys_lucky_7(void) {
    s16 win;
    s16 choice;
    s16 done = FALSE;

    win = func_8010AD44_game_guys_lucky_7(D_8010D150_game_guys_lucky_7[0][0], D_8010D150_game_guys_lucky_7[0][1],
                                          D_8010D150_game_guys_lucky_7[0][2]);
    HuAudFXPlay(0x11D);
    HuWinExOpen(win, 1);
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
                GMesTimerValueSet(D_8010D1CC_game_guys_lucky_7);
                switch (D_8010D6DC_game_guys_lucky_7[3]) {
                    case 0:
                        if ((HuPadBtnDown[D_8010D6DC_game_guys_lucky_7[1]] & 0x8000) ||
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
                    GMesTimerEnd();
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
            if (HuPadBtnDown[0] & 2) {
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
    HuWinExOpen(win, 1);
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
    HuWinExOpen(win, 1);
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

void func_80107668_game_guys_lucky_7(omObjData *object) {
    switch (D_8010D1D2_game_guys_lucky_7) {
        case 0:
            if (D_8010D776_game_guys_lucky_7 < 8) {
                if (D_8010D776_game_guys_lucky_7 >= D_8010D774_game_guys_lucky_7) {
                    D_8010D77A_game_guys_lucky_7 = 1;
                }
                if (D_8010D774_game_guys_lucky_7 >= 8) {
                    D_8010D77A_game_guys_lucky_7 = 1;
                }
            } else {
                D_8010D77A_game_guys_lucky_7 = 0;
            }
            D_8010D1D2_game_guys_lucky_7++;
            break;
        case 1:
            if (D_8010D77A_game_guys_lucky_7 == 1) {
                if (D_8010D776_game_guys_lucky_7 == 7) {
                    HuAudFXPlay(0x522);
                } else {
                    HuAudFXPlay(0x535);
                }
            } else {
                HuAudFXPlay(0x518);
            }
            D_8010D1D2_game_guys_lucky_7++;
            break;
        case 2:
            if (D_8010D776_game_guys_lucky_7 == 7) {
                func_8010BAFC_game_guys_lucky_7();
                D_8010D1D2_game_guys_lucky_7++;
            } else {
                D_8010D1D2_game_guys_lucky_7 += 2;
            }
        case 3:
            D_8010D1D2_game_guys_lucky_7 += func_8010C670_game_guys_lucky_7(0x44);
            break;
        case 4:
            if (D_8010D77A_game_guys_lucky_7 == 1) {
                if (D_8010D776_game_guys_lucky_7 == 7) {
                    func_8010B334_game_guys_lucky_7();
                }
                D_8010D746_game_guys_lucky_7 = 5;
                D_8010D73C_game_guys_lucky_7 = 4;
            } else if (D_8010D77A_game_guys_lucky_7 == 0) {
                D_8010D73C_game_guys_lucky_7 = 3;
                if (D_8010D776_game_guys_lucky_7 < 8) {
                    D_8010D746_game_guys_lucky_7 = 6;
                }
            }
            D_8010D1D2_game_guys_lucky_7++;
            break;
        case 5:
            object->func = func_80105F70_game_guys_lucky_7;
            break;
    }
}

void func_8010783C_game_guys_lucky_7(omObjData *object) {
    f32 speedSq;

    switch (D_8010D1D4_game_guys_lucky_7) {
        case 0:
            D_8010D1D8_game_guys_lucky_7 = 0.0f;
            HuAudFXPlay(0x51D);
            D_8010D1D4_game_guys_lucky_7 = 2;
            break;
        case 1:
            break;
        case 2:
            D_8010D1D8_game_guys_lucky_7 += 0.11f;
            if (D_8010D1D8_game_guys_lucky_7 >= 1.7f) {
                D_8010D1D8_game_guys_lucky_7 = 1.7f;
            }
            D_8010D730_game_guys_lucky_7 += D_8010D1D8_game_guys_lucky_7 * D_8010D1D8_game_guys_lucky_7 * -17.75f;
            if (D_8010D730_game_guys_lucky_7 <= 0.0f) {
                HuAudFXPlay(0x520);
                D_8010D726_game_guys_lucky_7 = 1;
                D_8010D1D4_game_guys_lucky_7++;
                D_8010D1D8_game_guys_lucky_7 = -1.47f;
            }
            break;
        case 3:
            D_8010D1D8_game_guys_lucky_7 += 0.22f;
            if (D_8010D1D8_game_guys_lucky_7 >= 1.7f) {
                D_8010D1D8_game_guys_lucky_7 = 1.7f;
            }
            speedSq = D_8010D1D8_game_guys_lucky_7 * D_8010D1D8_game_guys_lucky_7;
            if (D_8010D1D8_game_guys_lucky_7 >= 0.0f) {
                D_8010D730_game_guys_lucky_7 += speedSq * -17.5f;
            } else {
                D_8010D730_game_guys_lucky_7 += speedSq * 17.5f;
            }
            if (D_8010D738_game_guys_lucky_7 < 360.0f) {
                D_8010D738_game_guys_lucky_7 += 10.0f;
            } else {
                D_8010D738_game_guys_lucky_7 = 360.0f;
            }
            if (D_8010D730_game_guys_lucky_7 <= 0.0f && D_8010D1D8_game_guys_lucky_7 >= 0.0f) {
                D_8010D800_game_guys_lucky_7 = 4;
                D_8010D730_game_guys_lucky_7 = 0.0f;
                D_8010D1D4_game_guys_lucky_7++;
            }
            break;
        case 4:
            if (D_8010D73C_game_guys_lucky_7 == 0) {
                object->func = func_80106854_game_guys_lucky_7;
            }
            break;
    }
}

void func_80107AC4_game_guys_lucky_7(omObjData *object) {
    f32 speedSq;

    switch (D_8010D1DC_game_guys_lucky_7) {
        case 0:
            D_8010D746_game_guys_lucky_7 = 7;
            HuAudFXPlay(0x51D);
            D_8010D1E0_game_guys_lucky_7 = 0.0f;
            D_8010D1DC_game_guys_lucky_7++;
            break;
        case 1:
            D_8010D748_game_guys_lucky_7 = 1.0f;
            D_8010D746_game_guys_lucky_7 = 8;
            D_8010D1DC_game_guys_lucky_7++;
            break;
        case 2:
            D_8010D1E0_game_guys_lucky_7 += 0.11f;
            if (D_8010D1E0_game_guys_lucky_7 >= 1.7f) {
                D_8010D1E0_game_guys_lucky_7 = 1.7f;
            }
            D_8010D750_game_guys_lucky_7 += D_8010D1E0_game_guys_lucky_7 * D_8010D1E0_game_guys_lucky_7 * -17.5f;
            if (D_8010D750_game_guys_lucky_7 < 0.0f) {
                HuAudFXPlay(0x520);
                D_8010D750_game_guys_lucky_7 = 0.0f;
                D_8010D742_game_guys_lucky_7 = 1;
                D_8010D1DC_game_guys_lucky_7++;
                D_8010D1E0_game_guys_lucky_7 = -1.47f;
                omVibrate(D_8010D6DC_game_guys_lucky_7[0], 2, 2, 20);
            }
            break;
        case 3:
            D_8010D1E0_game_guys_lucky_7 += 0.15f;
            if (D_8010D1E0_game_guys_lucky_7 >= 1.7f) {
                D_8010D1E0_game_guys_lucky_7 = 1.7f;
            }
            speedSq = D_8010D1E0_game_guys_lucky_7 * D_8010D1E0_game_guys_lucky_7;
            if (D_8010D1E0_game_guys_lucky_7 >= 0.0f) {
                D_8010D750_game_guys_lucky_7 += speedSq * -17.5f;
            } else {
                D_8010D750_game_guys_lucky_7 += speedSq * 17.5f;
            }
            if (D_8010D754_game_guys_lucky_7 < 360.0f) {
                D_8010D754_game_guys_lucky_7 += 10.0f;
            } else {
                D_8010D754_game_guys_lucky_7 = 360.0f;
            }
            if (D_8010D750_game_guys_lucky_7 <= 0.0f && D_8010D1E0_game_guys_lucky_7 >= 0.0f) {
                HuAudFXPlay(0x51E);
                CharFXPlay(0x31, D_8010D6DC_game_guys_lucky_7[2]);
                D_8010D76E_game_guys_lucky_7 = 1;
                D_8010D750_game_guys_lucky_7 = 0.0f;
                D_8010D748_game_guys_lucky_7 = 0.0f;
                D_8010D746_game_guys_lucky_7 = 9;
                object->func = func_80105F70_game_guys_lucky_7;
                D_8010D1E4_game_guys_lucky_7 = 0;
                D_8010D1DC_game_guys_lucky_7 = 0;
            }
            break;
    }
}

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
    HuAudFXAllFadeOut(30);
    object->func = func_80107EEC_game_guys_lucky_7;
}

void func_80107EEC_game_guys_lucky_7(omObjData *object) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        func_8010C824_game_guys_lucky_7();
        GMesClose();
        HuWinAllKill();
        HuSprAnimAllKill();
        omOvlReturnEx(1);
    }
}

void func_80107F44_game_guys_lucky_7(omObjData *object) {
    if (omSysExitReq == 1) {
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

void func_80107F98_game_guys_lucky_7(omObjData *object) {
    func_80107FD8_game_guys_lucky_7();
    func_801080E8_game_guys_lucky_7();
    func_8010826C_game_guys_lucky_7();
    object->func = func_80108374_game_guys_lucky_7;
}

void func_80107FD8_game_guys_lucky_7(void) {
    GameGuysLucky7SpriteDef defs[3] = {
        { 0x640000, 1000, 160, 120 },
        { 0x640001, 900, 160, 57 },
        { 0x640002, 900, 160, 57 },
    };
    u16 i;

    for (i = 0; i < 3; i++) {
        D_8010D6EA_game_guys_lucky_7[i] = espEntry(HuSprAnimDataRead(defs[i].dataNum), 0, 0);
        espAttrSet(D_8010D6EA_game_guys_lucky_7[i], 0x4000);
        espPriSet(D_8010D6EA_game_guys_lucky_7[i], (u16)defs[i].priority);
        espPosSet(D_8010D6EA_game_guys_lucky_7[i], defs[i].x, defs[i].y);
    }
    espDispOff(D_8010D6EA_game_guys_lucky_7[1]);
    espDispOff(D_8010D6EA_game_guys_lucky_7[2]);
}

void func_801080E8_game_guys_lucky_7(void) {
    GameGuysLucky7SpritePos defs[7] = {
        { 0x640003, 225, 202 },
        { 0x640004, 199, 202 },
        { 0x640005, 173, 202 },
        { 0x640006, 147, 202 },
        { 0x640007, 121, 202 },
        { 0x640008, 95, 202 },
        { 0x640009, 68, 200 },
    };
    u16 i;

    for (i = 0; i < 7; i++) {
        D_8010D6F0_game_guys_lucky_7[i] = espEntry(HuSprAnimDataRead(defs[i].dataNum), 0, 0);
        if (i != 0) {
            espAttrSet(D_8010D6F0_game_guys_lucky_7[i], 0x4000);
        }
        espPriSet(D_8010D6F0_game_guys_lucky_7[i], 700);
        espPosSet(D_8010D6F0_game_guys_lucky_7[i], defs[i].x, defs[i].y);
        espScaleSet(D_8010D6F0_game_guys_lucky_7[i], 0.5f, 0.5f);
    }
    for (i = 0; i < 7; i++) {
        D_8010D700_game_guys_lucky_7[i] = 0.5f;
    }
}

void func_8010826C_game_guys_lucky_7(void) {
    GameGuysLucky7SpritePos defs[5] = {
        { 0x21001A, 30, 22 },
        { 0x21001B, 42, 22 },
        { 0x31, 54, 22 },
        { 0x31, 66, 22 },
        { 0x31, 78, 22 },
    };
    u16 i;

    for (i = 0; i < 5; i++) {
        D_8010D71C_game_guys_lucky_7[i] = espEntry(HuSprAnimDataRead(defs[i].dataNum), 0, 0);
        espPriSet(D_8010D71C_game_guys_lucky_7[i], 700);
        espPosSet(D_8010D71C_game_guys_lucky_7[i], defs[i].x, defs[i].y);
    }
}

void func_80108374_game_guys_lucky_7(omObjData *object) {
    func_801083A0_game_guys_lucky_7();
    func_80108498_game_guys_lucky_7();
    func_801085D4_game_guys_lucky_7();
}

void func_801083A0_game_guys_lucky_7(void) {
    if (D_8010D1E6_game_guys_lucky_7 >= 10) {
        switch (D_8010D1E8_game_guys_lucky_7) {
            case 0:
                espDispOn(D_8010D6EA_game_guys_lucky_7[1]);
                espDispOff(D_8010D6EA_game_guys_lucky_7[2]);
                D_8010D1E8_game_guys_lucky_7++;
                break;
            case 1:
                espDispOff(D_8010D6EA_game_guys_lucky_7[1]);
                espDispOn(D_8010D6EA_game_guys_lucky_7[2]);
                D_8010D1E8_game_guys_lucky_7++;
                break;
            case 2:
                espDispOff(D_8010D6EA_game_guys_lucky_7[1]);
                espDispOff(D_8010D6EA_game_guys_lucky_7[2]);
                D_8010D1E8_game_guys_lucky_7 = 0;
                break;
        }
        D_8010D1E6_game_guys_lucky_7 = 0;
    } else {
        D_8010D1E6_game_guys_lucky_7++;
    }
}

void func_80108498_game_guys_lucky_7(void) {
    u16 i;

    for (i = 0; i < 7; i++) {
        if (i == D_8010D776_game_guys_lucky_7 - 1) {
            if (D_8010D700_game_guys_lucky_7[D_8010D776_game_guys_lucky_7 - 1] < 1.0f) {
                D_8010D700_game_guys_lucky_7[D_8010D776_game_guys_lucky_7 - 1] += 0.125f;
            } else {
                D_8010D700_game_guys_lucky_7[D_8010D776_game_guys_lucky_7 - 1] = 1.0f;
            }
        } else if (D_8010D700_game_guys_lucky_7[i] > 0.5f) {
            D_8010D700_game_guys_lucky_7[i] -= 0.1f;
        } else {
            D_8010D700_game_guys_lucky_7[i] = 0.5f;
        }
    }
    for (i = 0; i < 7; i++) {
        espScaleSet(D_8010D6F0_game_guys_lucky_7[i], D_8010D700_game_guys_lucky_7[i], D_8010D700_game_guys_lucky_7[i]);
    }
}

void func_801085D4_game_guys_lucky_7(void) {
    s16 x;
    u16 hundreds;
    u16 tens;
    u16 *coins;

    x = 0;
    coins = &D_8010D6DC_game_guys_lucky_7[5];
    if (*coins >= 999) {
        *coins = 999;
    } else if (*coins == 0) {
        *coins = 0;
    }

    if ((hundreds = D_8010D6DC_game_guys_lucky_7[5] / 100) == 0) {
        espDispOff(D_8010D71C_game_guys_lucky_7[2]);
    } else {
        espPatNoSet(D_8010D71C_game_guys_lucky_7[2], hundreds);
        espPosSet(D_8010D71C_game_guys_lucky_7[2], 54, 22);
        espDispOn(D_8010D71C_game_guys_lucky_7[2]);
        x += 12;
    }

    if ((tens = (u16)(D_8010D6DC_game_guys_lucky_7[5] % 100) / 10) == 0 &&
        (u16)(D_8010D6DC_game_guys_lucky_7[5] / 100) == 0) {
        espDispOff(D_8010D71C_game_guys_lucky_7[3]);
    } else {
        espPatNoSet(D_8010D71C_game_guys_lucky_7[3], tens);
        espPosSet(D_8010D71C_game_guys_lucky_7[3], x + 54, 22);
        espDispOn(D_8010D71C_game_guys_lucky_7[3]);
        x += 12;
    }

    espPatNoSet(D_8010D71C_game_guys_lucky_7[4], D_8010D6DC_game_guys_lucky_7[5] % 10);
    espPosSet(D_8010D71C_game_guys_lucky_7[4], x + 54, 22);
    espDispOn(D_8010D71C_game_guys_lucky_7[4]);
}

void func_801087B4_game_guys_lucky_7(omObjData *object) {
    s32 attr = 0x2A9;
    s32 chr = D_8010D6DC_game_guys_lucky_7[2];
    s32 bodyFile = omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][1];
    s32 files[4] = { bodyFile, 9, 0x82, 0x83 };
    s32 motions[10] = {
        CharMotionDataNumGet(chr, 0x00),
        CharMotionDataNumGet(chr, 0x01),
        CharMotionDataNumGet(chr, 0x04),
        CharMotionDataNumGet(chr, 0x2B),
        CharMotionDataNumGet(chr, 0x1F),
        CharMotionDataNumGet(chr, 0x2F),
        CharMotionDataNumGet(chr, 0x36),
        CharMotionDataNumGet(chr, 0x29),
        CharMotionDataNumGet(chr, 0x0F),
        CharMotionDataNumGet(chr, 0x15),
    };
    u16 i;

    object->model[0] = Hu3DModelRead(files[0], attr);
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 10; i++) {
        omObjMotionRead(object, i, motions[i]);
    }
    Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[0]].motId, 0, 4, 2);
    for (i = 1; i < 4; i++) {
        object->model[i] = Hu3DModelRead(files[i], attr);
    }
    Hu3DModelPosSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(object->model[1], 15.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[2], 1.0f, 1.0f, 1.0f);
    Hu3DModelPosSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(object->model[2], 15.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[2], 1.0f, 1.0f, 1.0f);
    D_8010D742_game_guys_lucky_7 = 0;
    D_8010D744_game_guys_lucky_7 = 0;
    D_8010D746_game_guys_lucky_7 = 0;
    D_8010D74C_game_guys_lucky_7 = 1340.0f;
    D_8010D750_game_guys_lucky_7 = 0.0f;
    D_8010D754_game_guys_lucky_7 = 270.0f;
    object->func = func_80108B64_game_guys_lucky_7;
}

void func_80108B64_game_guys_lucky_7(omObjData *object) {
    f32 speedSq;
    f32 scale;
    u16 i;

    if (D_8010D1EA_game_guys_lucky_7 != D_8010D746_game_guys_lucky_7) {
        switch (D_8010D746_game_guys_lucky_7) {
            case 4:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[D_8010D746_game_guys_lucky_7]].motId, 0,
                                   10, 0);
                break;
            case 0:
            case 1:
            case 9:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[D_8010D746_game_guys_lucky_7]].motId, 0,
                                   4, 2);
                break;
            case 2:
            case 3:
                Hu3DMotionModelSet(object->model[0], object->motion[D_8010D746_game_guys_lucky_7]);
                break;
            case 5:
                Hu3DMotionModelSet(object->model[0], object->motion[5]);
                HuAudCharVoicePlay(omCharModelNoTbl[D_8010D6DC_game_guys_lucky_7[2]][0] | 0x2F);
                break;
            case 6:
                Hu3DMotionModelSet(object->model[0], object->motion[6]);
                HuAudCharVoicePlay(omCharModelNoTbl[D_8010D6DC_game_guys_lucky_7[2]][0] | 0x36);
                break;
            case 7:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[D_8010D746_game_guys_lucky_7]].motId, 0,
                                   10, 2);
                break;
            case 8:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[D_8010D746_game_guys_lucky_7]].motId, 0,
                                   30, 1);
                break;
        }
        D_8010D1EA_game_guys_lucky_7 = D_8010D746_game_guys_lucky_7;
    }
    if (D_8010D744_game_guys_lucky_7 == 1) {
        switch (D_8010D1EC_game_guys_lucky_7) {
            case 0:
                D_8010D1F0_game_guys_lucky_7 = -1.47f;
                if (D_8010D754_game_guys_lucky_7 != 270.0f) {
                    D_8010D746_game_guys_lucky_7 = 1;
                    D_8010D1EC_game_guys_lucky_7++;
                } else {
                    D_8010D1EC_game_guys_lucky_7 += 2;
                }
                break;
            case 1:
                D_8010D754_game_guys_lucky_7 -= 10.0f;
                if (D_8010D754_game_guys_lucky_7 <= 270.0f) {
                    D_8010D754_game_guys_lucky_7 = 270.0f;
                    D_8010D1EC_game_guys_lucky_7++;
                }
                break;
            case 2:
                if (D_8010D1EE_game_guys_lucky_7++ == 0) {
                    D_8010D746_game_guys_lucky_7 = 2;
                    CharFXPlay(0x3A, D_8010D6DC_game_guys_lucky_7[2]);
                } else if (D_8010D1EE_game_guys_lucky_7 >= 5) {
                    D_8010D1EE_game_guys_lucky_7 = 0;
                    D_8010D1EC_game_guys_lucky_7++;
                }
                break;
            case 3:
                if (D_8010D1F0_game_guys_lucky_7 >= 1.7f) {
                    D_8010D1F0_game_guys_lucky_7 = 1.7f;
                }
                if (D_8010D1F4_game_guys_lucky_7 == 7 && D_8010D1F0_game_guys_lucky_7 >= 0.5f) {
                    D_8010D746_game_guys_lucky_7 = 7;
                }
                D_8010D74C_game_guys_lucky_7 -= 7.14f;
                speedSq = D_8010D1F0_game_guys_lucky_7 * D_8010D1F0_game_guys_lucky_7;
                D_8010D750_game_guys_lucky_7 +=
                    (D_8010D1F0_game_guys_lucky_7 >= 0.0f) ? speedSq * -35.0f : speedSq * 35.0f;
                if (D_8010D750_game_guys_lucky_7 < D_8010D1FC_game_guys_lucky_7[D_8010D1F4_game_guys_lucky_7].x &&
                    D_8010D1F0_game_guys_lucky_7 >= 0.0f) {
                    D_8010D750_game_guys_lucky_7 = D_8010D1FC_game_guys_lucky_7[D_8010D1F4_game_guys_lucky_7].x;
                    D_8010D776_game_guys_lucky_7++;
                    if (D_8010D1F4_game_guys_lucky_7 != 7) {
                        D_8010D746_game_guys_lucky_7 = 4;
                        HuAudFXPlay(D_8010D776_game_guys_lucky_7 + 0x523);
                    }
                    D_8010D1EC_game_guys_lucky_7 += 2;
                }
                D_8010D1F0_game_guys_lucky_7 += 0.22f;
                break;
            case 4:
                if (D_8010D1EE_game_guys_lucky_7++ != 0) {
                    D_8010D1EE_game_guys_lucky_7 = 0;
                    D_8010D1EC_game_guys_lucky_7++;
                }
                break;
            case 5:
                D_8010D1F0_game_guys_lucky_7 = 0.0f;
                D_8010D1EC_game_guys_lucky_7 = 0;
                D_8010D1EE_game_guys_lucky_7 = 0;
                D_8010D1F4_game_guys_lucky_7++;
                D_8010D744_game_guys_lucky_7 = 0;
                break;
        }
    }
    omSetTra(object, D_8010D74C_game_guys_lucky_7, D_8010D750_game_guys_lucky_7, 0.0f);
    omSetRot(object, 0.0f, D_8010D754_game_guys_lucky_7, 0.0f);
    if (D_8010D742_game_guys_lucky_7 == 1) {
        for (i = 2; i < 4; i++) {
            Hu3DMotionTimeSet(object->model[i], 0.0f);
        }
        D_8010D742_game_guys_lucky_7 = 0;
    }
    scale = (1340.0f - D_8010D750_game_guys_lucky_7) * 0.00074626866f;
    if (D_8010D74C_game_guys_lucky_7 >= 300.0f || D_8010D74C_game_guys_lucky_7 <= -400.0f) {
        for (i = 1; i < 4; i++) {
            Hu3DModelPosSet(object->model[i], D_8010D74C_game_guys_lucky_7, 0.0f, 10.0f);
        }
        Hu3DModelScaleSet(object->model[1], scale, scale, scale);
    } else {
        Hu3DModelPosSet(object->model[1], D_8010D74C_game_guys_lucky_7, 5000.0f, 0.0f);
    }
}

void func_801092B0_game_guys_lucky_7(omObjData *object) {
    s32 attr = 0x2A9;
    s32 files[4] = { 0xA0063, 9, 0x82, 0x83 };
    s32 motions[10] = {
        0xA0065,
        0xA006A,
        0xA0069,
        0xA0067,
        0xA006B,
        0xA0073,
        0xA0074,
        0xA006E,
        0xA006D,
        0xA0070,
    };
    u16 i;

    object->model[0] = Hu3DModelRead(files[0], attr);
    omSetTra(object, 0.0f, 190.0f, 5100.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 10; i++) {
        omObjMotionRead(object, i, motions[i]);
    }
    for (i = 1; i < 4; i++) {
        object->model[i] = Hu3DModelRead(files[i], attr);
    }
    Hu3DModelPosSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(object->model[1], 15.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[2], 1.0f, 1.0f, 1.0f);
    Hu3DModelPosSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(object->model[2], 15.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[2], 1.0f, 1.0f, 1.0f);
    D_8010D726_game_guys_lucky_7 = 0;
    D_8010D728_game_guys_lucky_7 = 0;
    D_8010D72C_game_guys_lucky_7 = 0.0f;
    D_8010D730_game_guys_lucky_7 = 190.0f;
    D_8010D734_game_guys_lucky_7 = 5100.0f;
    D_8010D738_game_guys_lucky_7 = 0.0f;
    D_8010D73C_game_guys_lucky_7 = 0;
    D_8010D73E_game_guys_lucky_7 = 1;
    object->func = func_80109570_game_guys_lucky_7;
}

void func_80109570_game_guys_lucky_7(omObjData *object) {
    f32 speedSq;
    f32 scale;
    u16 i;

    if (D_8010D258_game_guys_lucky_7 != D_8010D73C_game_guys_lucky_7) {
        switch (D_8010D73C_game_guys_lucky_7) {
            case 9:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[D_8010D73C_game_guys_lucky_7]].motId, 0,
                                   10, 0);
                break;
            case 0:
            case 3:
            case 5:
            case 8:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[D_8010D73C_game_guys_lucky_7]].motId, 0,
                                   4, 2);
                break;
            case 1:
            case 2:
            case 4:
            case 7:
                Hu3DMotionModelSet(object->model[0], object->motion[D_8010D73C_game_guys_lucky_7]);
                break;
            case 6:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[D_8010D73C_game_guys_lucky_7]].motId, 0,
                                   15, 0);
                break;
        }
        D_8010D258_game_guys_lucky_7 = D_8010D73C_game_guys_lucky_7;
    }
    if (D_8010D800_game_guys_lucky_7 == 3) {
        if (D_8010D73C_game_guys_lucky_7 == 6 && Hu3DData[object->model[0]].motTime >= 30.0f) {
            Hu3DMotionTimeSet(object->model[0], 15.0f);
            D_8010D73E_game_guys_lucky_7 = 0;
            Hu3DMotionSpeedSet(object->model[0], 0.0f);
            D_8010D800_game_guys_lucky_7 = 0;
        }
    }
    if (D_8010D800_game_guys_lucky_7 == 4) {
        D_8010D73E_game_guys_lucky_7 = 1;
        Hu3DMotionSpeedSet(object->model[0], 1.0f);
        if (Hu3DData[object->model[0]].motTime == Hu3DMotion[Hu3DData[object->model[0]].motId].unk02) {
            D_8010D73C_game_guys_lucky_7 = 0;
            D_8010D800_game_guys_lucky_7 = 0;
        }
    }
    if (D_8010D728_game_guys_lucky_7 == 1) {
        switch (D_8010D25A_game_guys_lucky_7) {
            case 0:
                D_8010D260_game_guys_lucky_7 = -1.47f;
                if (D_8010D738_game_guys_lucky_7 != 270.0f) {
                    D_8010D73C_game_guys_lucky_7 = 0;
                    D_8010D25A_game_guys_lucky_7++;
                } else {
                    D_8010D25A_game_guys_lucky_7 += 2;
                }
                break;
            case 1:
                D_8010D738_game_guys_lucky_7 -= 10.0f;
                if (D_8010D738_game_guys_lucky_7 <= 270.0f) {
                    D_8010D738_game_guys_lucky_7 = 270.0f;
                    D_8010D73C_game_guys_lucky_7 = 0;
                    D_8010D25A_game_guys_lucky_7++;
                }
                break;
            case 2:
                if (D_8010D25C_game_guys_lucky_7 >= 4) {
                    D_8010D25C_game_guys_lucky_7 = 0;
                    D_8010D25A_game_guys_lucky_7++;
                    HuAudFXPlay(0x519);
                    D_8010D73C_game_guys_lucky_7 = 3;
                } else {
                    D_8010D25C_game_guys_lucky_7++;
                }
                break;
            case 3:
                if (D_8010D260_game_guys_lucky_7 >= 1.7f) {
                    D_8010D260_game_guys_lucky_7 = 1.7f;
                }
                if (D_8010D264_game_guys_lucky_7 == 7 && D_8010D260_game_guys_lucky_7 >= 0.8f) {
                    D_8010D774_game_guys_lucky_7++;
                    D_8010D25A_game_guys_lucky_7 += 2;
                    D_8010D800_game_guys_lucky_7 = 3;
                    D_8010D73C_game_guys_lucky_7 = 6;
                    break;
                }
                if (D_8010D264_game_guys_lucky_7 == 0) {
                    D_8010D72C_game_guys_lucky_7 -= 11.5f;
                } else if (D_8010D264_game_guys_lucky_7 == 7) {
                    D_8010D72C_game_guys_lucky_7 -= 17.0f;
                    D_8010D738_game_guys_lucky_7 += 5.0f;
                } else {
                    D_8010D72C_game_guys_lucky_7 -= 7.14f;
                }
                speedSq = D_8010D260_game_guys_lucky_7 * D_8010D260_game_guys_lucky_7;
                D_8010D730_game_guys_lucky_7 +=
                    (D_8010D260_game_guys_lucky_7 >= 0.0f) ? speedSq * -35.0f : speedSq * 35.0f;
                if (D_8010D730_game_guys_lucky_7 < D_8010D26C_game_guys_lucky_7[D_8010D264_game_guys_lucky_7].x &&
                    D_8010D260_game_guys_lucky_7 >= 0.0f) {
                    D_8010D730_game_guys_lucky_7 = D_8010D26C_game_guys_lucky_7[D_8010D264_game_guys_lucky_7].x;
                    HuAudFXPlay(0x51A);
                    if (D_8010D774_game_guys_lucky_7 != 7) {
                        D_8010D73C_game_guys_lucky_7 = 9;
                    }
                    D_8010D774_game_guys_lucky_7++;
                    D_8010D25A_game_guys_lucky_7 += 2;
                }
                D_8010D260_game_guys_lucky_7 += 0.22f;
                break;
            case 4:
                if (D_8010D25C_game_guys_lucky_7 >= 3) {
                    D_8010D25C_game_guys_lucky_7 = 0;
                    D_8010D25A_game_guys_lucky_7++;
                    D_8010D73C_game_guys_lucky_7 = 0;
                } else {
                    D_8010D25C_game_guys_lucky_7++;
                }
                break;
            case 5:
                D_8010D260_game_guys_lucky_7 = 0.0f;
                D_8010D25A_game_guys_lucky_7 = 0;
                D_8010D25C_game_guys_lucky_7 = 0;
                D_8010D264_game_guys_lucky_7++;
                D_8010D728_game_guys_lucky_7 = 0;
                break;
        }
    }
    omSetTra(object, D_8010D72C_game_guys_lucky_7, D_8010D730_game_guys_lucky_7, D_8010D734_game_guys_lucky_7);
    omSetRot(object, 0.0f, D_8010D738_game_guys_lucky_7, 0.0f);
    Hu3DMotionSpeedSet(object->model[0], D_8010D73E_game_guys_lucky_7);
    if (D_8010D726_game_guys_lucky_7 == 1) {
        for (i = 2; i < 4; i++) {
            Hu3DMotionTimeSet(object->model[i], 0.0f);
        }
        D_8010D726_game_guys_lucky_7 = 0;
    }
    if (D_8010D726_game_guys_lucky_7 == 2) {
        Hu3DMotionTimeSet(object->model[2], 0.0f);
        D_8010D726_game_guys_lucky_7 = 0;
        Hu3DModelPosSet(object->model[2], D_8010D72C_game_guys_lucky_7, D_8010D730_game_guys_lucky_7, -100.0f);
    }
    scale = (1340.0f - D_8010D730_game_guys_lucky_7) * 0.00074626866f;
    if (D_8010D72C_game_guys_lucky_7 >= 350.0f || D_8010D72C_game_guys_lucky_7 <= -400.0f) {
        for (i = 1; i < 4; i++) {
            Hu3DModelPosSet(object->model[i], D_8010D72C_game_guys_lucky_7, 0.0f, -100.0f);
        }
        Hu3DModelScaleSet(object->model[1], scale, scale, scale);
    } else {
        Hu3DModelPosSet(object->model[1], D_8010D72C_game_guys_lucky_7, 5000.0f, -100.0f);
    }
    D_8010D740_game_guys_lucky_7 = (s16)Hu3DData[object->model[0]].motTime / 2;
    if (D_8010D800_game_guys_lucky_7 == 5) {
        if (object->trans.z < 900.0f) {
            D_8010D734_game_guys_lucky_7 = object->trans.z += 100.0f;
        } else if (object->trans.x < 0.0f) {
            D_8010D738_game_guys_lucky_7 = object->rot.y = 90.0f;
            D_8010D72C_game_guys_lucky_7 = object->trans.x += 15.0f;
        } else if (object->rot.y > 0.0f) {
            D_8010D738_game_guys_lucky_7 = object->rot.y -= 10.0f;
            if (object->rot.y <= 0.0f) {
                D_8010D738_game_guys_lucky_7 = object->rot.y = 0.0f;
                D_8010D800_game_guys_lucky_7 = 0;
                D_8010D73C_game_guys_lucky_7 = 0;
            }
        }
    }
}

void func_80109FA4_game_guys_lucky_7(omObjData *object) {
    object->model[0] = Hu3DModelRead(0x83, 0x2A9);
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    omObjMotionRead(object, 0, 0x83);
    Hu3DMotionModelSet(object->model[0], object->motion[0]);
    D_8010D76C_game_guys_lucky_7 = 0;
    object->func = func_8010A04C_game_guys_lucky_7;
}

void func_8010A04C_game_guys_lucky_7(omObjData *object) {
    if (D_8010D76C_game_guys_lucky_7 == 1) {
        Hu3DMotionModelSet(object->model[0], object->motion[0]);
        D_8010D76C_game_guys_lucky_7 = 0;
    }
    omSetTra(object, D_8010D75C_game_guys_lucky_7, D_8010D760_game_guys_lucky_7 - 50.0f,
             D_8010D764_game_guys_lucky_7 + 120.0f);
}

void func_8010A0DC_game_guys_lucky_7(omObjData *object) {
    object->model[0] = Hu3DModelRead(0xB002F, 0x2A9);
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    omObjMotionRead(object, 0, 0xB002F);
    Hu3DMotionModelSet(object->model[0], object->motion[0]);
    Hu3DModelCameraSet(object->model[0], 0);
    D_8010D76E_game_guys_lucky_7 = 0;
    object->func = func_8010A19C_game_guys_lucky_7;
}

void func_8010A19C_game_guys_lucky_7(omObjData *object) {
    if (D_8010D76E_game_guys_lucky_7 == 1) {
        Hu3DModelCameraSet(object->model[0], 1);
        Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[0]].motId, 0, 10, 2);
        D_8010D76E_game_guys_lucky_7 = 0;
        if (D_8010D776_game_guys_lucky_7 >= 8) {
            omSetTra(object, D_8010D74C_game_guys_lucky_7, 125.0f, 0.0f);
        } else if (D_8010D774_game_guys_lucky_7 >= 8) {
            omSetTra(object, D_8010D72C_game_guys_lucky_7, 125.0f, -100.0f);
        }
    }
}

void func_8010A278_game_guys_lucky_7(omObjData *object) {
    object->model[0] = Hu3DModelRead(0xB0006, 0x2A9);
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 2.0f, 2.0f, 2.0f);
    omObjMotionRead(object, 0, 0xB0006);
    Hu3DMotionModelSet(object->model[0], object->motion[0]);
    D_8010D770_game_guys_lucky_7 = 0;
    object->func = func_8010A328_game_guys_lucky_7;
}

void func_8010A328_game_guys_lucky_7(omObjData *object) {
    if (D_8010D770_game_guys_lucky_7 == 1) {
        Hu3DMotionModelSet(object->model[0], object->motion[0]);
        D_8010D770_game_guys_lucky_7 = 0;
    }
    omSetTra(object, D_8010D75C_game_guys_lucky_7, D_8010D760_game_guys_lucky_7 - 50.0f,
             D_8010D764_game_guys_lucky_7 + 120.0f);
}

void func_8010A3B8_game_guys_lucky_7(omObjData *object) {
    object->model[0] = Hu3DModelRead(0x64000B, 0x2A9);
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    D_8010D758_game_guys_lucky_7 = 0;
    D_8010D75C_game_guys_lucky_7 = 0.0f;
    D_8010D760_game_guys_lucky_7 = 0.0f;
    D_8010D764_game_guys_lucky_7 = 0.0f;
    object->func = func_8010A458_game_guys_lucky_7;
}

void func_8010A458_game_guys_lucky_7(omObjData *object) {
    if (D_8010D758_game_guys_lucky_7 == 1) {
        switch (D_8010D2C8_game_guys_lucky_7) {
            case 0:
                D_8010D2CC_game_guys_lucky_7 = func_801059BC_game_guys_lucky_7(4.0f) * 90;
                D_8010D2D0_game_guys_lucky_7 = func_801059BC_game_guys_lucky_7(4.0f) * 90;
                D_8010D2D4_game_guys_lucky_7 = 0.0f;
                D_8010D2D8_game_guys_lucky_7 = 0.0f;
                if (D_8010D772_game_guys_lucky_7 == 0) {
                    D_8010D75C_game_guys_lucky_7 = D_8010D72C_game_guys_lucky_7;
                    D_8010D760_game_guys_lucky_7 = D_8010D730_game_guys_lucky_7 + 250.0f;
                    D_8010D764_game_guys_lucky_7 = -100.0f;
                } else if (D_8010D772_game_guys_lucky_7 == 1) {
                    D_8010D75C_game_guys_lucky_7 = D_8010D74C_game_guys_lucky_7;
                    D_8010D760_game_guys_lucky_7 = D_8010D750_game_guys_lucky_7 + 250.0f;
                    D_8010D764_game_guys_lucky_7 = 0.0f;
                }
                D_8010D2C8_game_guys_lucky_7++;
                break;
            case 1:
                D_8010D2D4_game_guys_lucky_7 =
                    (D_8010D2D4_game_guys_lucky_7 < 0.99f) ? D_8010D2D4_game_guys_lucky_7 + 0.4f : 1.0f;
                D_8010D2D8_game_guys_lucky_7 =
                    (D_8010D2D8_game_guys_lucky_7 < 0.99f) ? D_8010D2D8_game_guys_lucky_7 + 0.8f : 1.0f;
                if (D_8010D2DC_game_guys_lucky_7++ >= 10.0f) {
                    D_8010D2DC_game_guys_lucky_7 = 0.0f;
                    D_8010D2CC_game_guys_lucky_7 = 0.0f;
                    D_8010D2D0_game_guys_lucky_7 = 0.0f;
                    HuAudFXPlay(0x51B);
                    D_8010D2C8_game_guys_lucky_7++;
                }
                break;
            case 2:
                D_8010D2CC_game_guys_lucky_7 += 36.0f;
                if (D_8010D2CC_game_guys_lucky_7 >= 360.0f) {
                    D_8010D2CC_game_guys_lucky_7 -= 360.0f;
                } else if (D_8010D2CC_game_guys_lucky_7 < 0.0f) {
                    D_8010D2CC_game_guys_lucky_7 += 360.0f;
                }
                break;
        }
    } else if (D_8010D758_game_guys_lucky_7 == 2) {
        HuAudFXPlay(0x51C);
        D_8010D758_game_guys_lucky_7 = 0;
    } else if (D_8010D758_game_guys_lucky_7 == 0) {
        if (D_8010D2D4_game_guys_lucky_7 > 0.0f) {
            D_8010D2D4_game_guys_lucky_7 -= 0.2f;
        } else {
            D_8010D2D4_game_guys_lucky_7 = 0.0f;
        }
        if (D_8010D2D8_game_guys_lucky_7 > 0.0f) {
            D_8010D2D8_game_guys_lucky_7 -= 0.2f;
        } else {
            D_8010D2D8_game_guys_lucky_7 = 0.0f;
        }
        D_8010D2C8_game_guys_lucky_7 = 0;
    }
    omSetTra(object, D_8010D75C_game_guys_lucky_7, D_8010D760_game_guys_lucky_7, D_8010D764_game_guys_lucky_7);
    omSetRot(object, D_8010D2CC_game_guys_lucky_7, D_8010D2D0_game_guys_lucky_7, 0.0f);
    omSetSca(object, D_8010D2D4_game_guys_lucky_7, D_8010D2D8_game_guys_lucky_7, D_8010D2D8_game_guys_lucky_7);
}

void func_8010A8A4_game_guys_lucky_7(omObjData *object) {
    u16 i = 0; // initialized early to match register allocation
    s32 attr = 0x2A9;
    s32 files[6] = { 0x64000C, 0x64000D, 0x64000E, 0x64000F, 0x640010, 0x640011 };

    for (i = 0; i < 6; i++) {
        object->model[i] = Hu3DModelRead(files[i], attr);
    }
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    for (i = 1; i < 6; i++) {
        Hu3DModelPosSet(object->model[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(object->model[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(object->model[i], 1.0f, 1.0f, 1.0f);
    }
    for (i = 0; i < 6; i++) {
        Hu3DModelCameraSet(object->model[i], 0);
    }
    D_8010D768_game_guys_lucky_7 = 0;
    D_8010D76A_game_guys_lucky_7 = 0;
    object->func = func_8010AA8C_game_guys_lucky_7;
}

void func_8010AA8C_game_guys_lucky_7(omObjData *object) {
    if (D_8010D768_game_guys_lucky_7 == 1) {
        switch (D_8010D2E0_game_guys_lucky_7) {
            case 0:
                D_8010D2E4_game_guys_lucky_7 = D_8010D760_game_guys_lucky_7;
                D_8010D2E8_game_guys_lucky_7 = 0.0f;
                D_8010D2EC_game_guys_lucky_7 = 0;
                Hu3DModelCameraSet(object->model[D_8010D76A_game_guys_lucky_7], 1);
                D_8010D2E0_game_guys_lucky_7++;
                break;
            case 1:
                if (D_8010D2E8_game_guys_lucky_7 < 1.0f) {
                    D_8010D2E8_game_guys_lucky_7 += 0.1f;
                } else {
                    D_8010D2E8_game_guys_lucky_7 = 1.0f;
                    D_8010D2E0_game_guys_lucky_7++;
                }
                D_8010D2E4_game_guys_lucky_7 += 0.0f;
                break;
            case 2:
                if (D_8010D2EC_game_guys_lucky_7 >= 15) {
                    D_8010D2EC_game_guys_lucky_7 = 0;
                    D_8010D2E0_game_guys_lucky_7++;
                } else {
                    D_8010D2EC_game_guys_lucky_7++;
                }
                break;
            case 3:
                D_8010D2E0_game_guys_lucky_7 = 0;
                D_8010D768_game_guys_lucky_7 = 0;
                break;
        }
    } else if (D_8010D768_game_guys_lucky_7 == 0) {
        if (D_8010D2E8_game_guys_lucky_7 > 0.0f) {
            D_8010D2E8_game_guys_lucky_7 -= 0.1f;
        } else {
            D_8010D2E8_game_guys_lucky_7 = 0.0f;
            Hu3DModelCameraSet(object->model[D_8010D76A_game_guys_lucky_7], 0);
        }
    }
    if (D_8010D76A_game_guys_lucky_7 == 0) {
        omSetTra(object, D_8010D75C_game_guys_lucky_7, D_8010D2E4_game_guys_lucky_7, D_8010D764_game_guys_lucky_7);
        omSetSca(object, D_8010D2E8_game_guys_lucky_7, D_8010D2E8_game_guys_lucky_7, D_8010D2E8_game_guys_lucky_7);
    } else {
        Hu3DModelPosSet(object->model[D_8010D76A_game_guys_lucky_7], D_8010D75C_game_guys_lucky_7,
                        D_8010D2E4_game_guys_lucky_7, D_8010D764_game_guys_lucky_7);
        Hu3DModelScaleSet(object->model[D_8010D76A_game_guys_lucky_7], D_8010D2E8_game_guys_lucky_7,
                          D_8010D2E8_game_guys_lucky_7, D_8010D2E8_game_guys_lucky_7);
    }
}

s16 func_8010AD44_game_guys_lucky_7(s16 x, s16 y, s16 lines) {
    s16 win;

    win = HuWinExCreateStyled(x, y, lines);
    HuWinAttrSet(win, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
    HuWinExPriSet(win, 1);
    HuWinMesSpeedSet(win, 0);
    HuWinHomeClear(win);
    return win;
}

void func_8010ADB8_game_guys_lucky_7(s16 win) {
    HuWinHomeClear(win);
    HuWinExClose(win, 1);
    HuWinExCleanup(win);
}

void func_8010ADF8_game_guys_lucky_7(s16 win, s16 player, s16 mode) {
    s16 i;

    HuWinComKeyReset();
    while (HuWinStatGet(win) != 0) {
        switch (mode) {
            case 0:
                if (HuPadBtnDown[player] & 0x8000) {
                    HuWinComKeySet(-0x8000, -0x8000, -0x8000, -0x8000);
                }
                break;
            case 1:
                for (i = 0; i < 10; i++) {
                    HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000,
                                    D_8010D188_game_guys_lucky_7[D_8010D802_game_guys_lucky_7]);
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

s16 func_8010AF44_game_guys_lucky_7(s16 win, s16 player, s16 mode, s16 count) {
    GameGuysLucky7PadValues keys;
    GameGuysLucky7PadValues players;
    s16 i;

    keys = D_8010D598_game_guys_lucky_7;
    players = D_8010D5A0_game_guys_lucky_7;
    switch (mode) {
        case 0:
            keys.v[player] = -1;
            HuWinAttrSet(win, HUWIN_ATTR_COMKEY, HUWIN_ATTR_NONE);
            HuWinActivePlayerSet(win, players.v[player]);
            HuWinComKeySet(keys.v[0], keys.v[1], keys.v[2], keys.v[3]);
            break;
        case 1:
            for (i = 0; i < count; i++) {
                keys.v[player] = 0x400;
                HuWinComKeyWait(keys.v[0], keys.v[1], keys.v[2], keys.v[3],
                                D_8010D188_game_guys_lucky_7[D_8010D802_game_guys_lucky_7]);
            }
            keys.v[player] = -0x8000;
            HuWinComKeyWait(keys.v[0], keys.v[1], keys.v[2], keys.v[3],
                            D_8010D188_game_guys_lucky_7[D_8010D802_game_guys_lucky_7]);
            break;
    }
    return HuWinChoiceGet(win, 0, 1);
}

s16 func_8010B13C_game_guys_lucky_7(s16 win, s16 player, s16 mode, s16 count) {
    GameGuysLucky7PadValues keys;
    GameGuysLucky7PadValues players;
    s16 i;

    keys = D_8010D598_game_guys_lucky_7;
    players = D_8010D5A0_game_guys_lucky_7;
    switch (mode) {
        case 0:
            keys.v[player] = -1;
            HuWinAttrSet(win, HUWIN_ATTR_COMKEY, HUWIN_ATTR_NONE);
            HuWinActivePlayerSet(win, players.v[player]);
            HuWinComKeySet(keys.v[0], keys.v[1], keys.v[2], keys.v[3]);
            break;
        case 1:
            for (i = 0; i < count; i++) {
                keys.v[player] = 0x400;
                HuWinComKeyWait(keys.v[0], keys.v[1], keys.v[2], keys.v[3],
                                D_8010D188_game_guys_lucky_7[D_8010D802_game_guys_lucky_7]);
            }
            keys.v[player] = -0x8000;
            HuWinComKeyWait(keys.v[0], keys.v[1], keys.v[2], keys.v[3],
                            D_8010D188_game_guys_lucky_7[D_8010D802_game_guys_lucky_7]);
            break;
    }
    return HuWinChoiceGet(win, 1, 1);
}

const GameGuysLucky7PadValues D_8010D598_game_guys_lucky_7 = { { 0, 0, 0, 0 } }; // COM keys

const GameGuysLucky7PadValues D_8010D5A0_game_guys_lucky_7 = { { 1, 2, 4, 8 } }; // active players

void func_8010B334_game_guys_lucky_7(void) {
    s16 i;
    s16 model;

    for (i = 0; i < 4; i++) {
        model = Hu3DModelRead(D_8010D2F0_game_guys_lucky_7[i], 0x2A9);
        D_8010D798_game_guys_lucky_7[i] = model;
        Hu3DAnmNoSet(Hu3DAnimRead(Hu3DData[model].hmf, 0xB0048, "e268p01_I8"), i * 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelObjAttrSet(model, 0x20000, 0x20000);
        Hu3DModelRemakeStatic(model);
        Hu3DModelVtxBufMake(model);
        Hu3DModelDynamicFree(model);
        Hu3DParticleCreate(model, -1, NULL, func_8010B6E0_game_guys_lucky_7);
    }
    omAddObj(10, 10, 10, -1, func_8010B498_game_guys_lucky_7);
}

void func_8010B498_game_guys_lucky_7(omObjData *object) {
    s16 i;

    for (i = 0; i < 4; i++) {
        if (((D_8010D804_game_guys_lucky_7 + i) & 7) == 0) {
            func_8010B528_game_guys_lucky_7(D_8010D798_game_guys_lucky_7[i]);
        }
    }
    D_8010D804_game_guys_lucky_7++;
}

void func_8010B528_game_guys_lucky_7(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = effect->unk58;
    s16 i;
    s16 count = hmf->unk1A;
    f32 temp;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk10 <= 0.0f) {
            temp = rand8() % 200 + -450.0f;
            particle->unk0C = temp;
            particle->unk10 = 1000.0f;
            temp = (rand8() * 1000 >> 8) - 500;
            particle->unk14 = temp;
            temp = ((rand8() * 10 >> 8) - 5) / 2.0f;
            particle->unk18 = temp;
            particle->unk1C = 0.0f;
            temp = ((rand8() * 10 >> 8) - 5) / 2.0f;
            particle->unk20 = temp;
            particle->unk08 = 5.0f;
            break;
        }
    }
}

void func_8010B6E0_game_guys_lucky_7(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 i;
    s16 count = hmf->unk1A;

    if (effect->unk02 == 0) {
        effect->unk04 &= ~4;
        particle = effect->unk58;
        for (i = 0; i < count; i++, particle++) {
            particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
            particle->unk24 = particle->unk28 = particle->unk2C = 0.0f;
            particle->unk08 = 0.0f;
            particle->unk04 = 1.0f;
        }
        effect->unk02++;
    }
    particle = effect->unk58;
    for (i = 0; i < count; i++, particle++) {
        if (particle->unk10 > 0.0f) {
            particle->unk0C += particle->unk18;
            particle->unk10 += particle->unk1C - 10.0f;
            particle->unk14 += particle->unk20;
        } else {
            particle->unk08 = 0.0f;
        }
    }
}
