#include "common.h"
#include "game_guys_roulette.h"

typedef struct GameGuysRoulettePlayerInfo { // 0x8 bytes
    /* 0x00 */ u8 player;
    /* 0x01 */ u8 pad;
    /* 0x02 */ u8 chr;
    /* 0x03 */ u8 cpu;
    /* 0x04 */ u8 difficulty;
    /* 0x06 */ u16 coins;
} GameGuysRoulettePlayerInfo;

typedef struct GameGuysRouletteSprite { // 0x20 bytes
    /* 0x00 */ u8 slot;
    /* 0x04 */ s32 priority;
    /* 0x08 */ s32 x;
    /* 0x0C */ s32 y;
    /* 0x10 */ u32 width;
    /* 0x14 */ u32 height;
    /* 0x18 */ f32 scaleX;
    /* 0x1C */ f32 scaleY;
} GameGuysRouletteSprite;

typedef struct GameGuysRoulettePrizeFiles { // 0x18 bytes
    /* 0x00 */ s32 ids[6];
} GameGuysRoulettePrizeFiles;

typedef struct GameGuysRouletteCharFiles { // 0x20 bytes
    /* 0x00 */ s32 ids[8];                 // per-character sprite index (low half)
} GameGuysRouletteCharFiles;

extern s16 D_8010A640_game_guys_roulette[]; // COM key wait frames, indexed by CPU difficulty
extern u8 D_8010A646_game_guys_roulette;
extern u8 D_8010A6A0_game_guys_roulette;   // banner blink timer
extern u8 D_8010A6A1_game_guys_roulette;   // banner blink frame
extern u8 D_8010A6A4_game_guys_roulette[]; // prize multipliers
extern s16 D_8010A65C_game_guys_roulette;
extern GameGuysRoulettePrizeFiles D_8010A6C0_game_guys_roulette;
extern GameGuysRouletteCharFiles D_8010A6D8_game_guys_roulette;
extern GameGuysRoulettePrizeFiles D_8010A6F8_game_guys_roulette;
extern GameGuysRouletteCharFiles D_8010A710_game_guys_roulette;
extern s16 D_8010A678_game_guys_roulette;
extern u8 D_8010A67A_game_guys_roulette;      // result timer
extern u8 D_8010A67B_game_guys_roulette;      // result state
extern s16 D_8010A67C_game_guys_roulette;     // result message
extern char *D_8010A680_game_guys_roulette[]; // character names
extern char D_8010A810_game_guys_roulette[];
extern omObjData *D_8010A910_game_guys_roulette;
extern omObjData *D_8010A914_game_guys_roulette;
extern omObjData *D_8010A918_game_guys_roulette;
extern omObjData *D_8010A91C_game_guys_roulette;
extern omObjData *D_8010A920_game_guys_roulette;
extern Process *D_8010A924_game_guys_roulette;
extern Process *D_8010A928_game_guys_roulette;
extern GameGuysRouletteSprite D_8010A930_game_guys_roulette; // background
extern GameGuysRouletteSprite D_8010A950_game_guys_roulette;
extern GameGuysRouletteSprite D_8010A970_game_guys_roulette;
extern GameGuysRouletteSprite D_8010A990_game_guys_roulette;    // prize panel
extern GameGuysRouletteSprite D_8010A9B0_game_guys_roulette[6]; // prize icons
extern GameGuysRouletteSprite D_8010AA70_game_guys_roulette;    // character portrait
extern GameGuysRouletteSprite D_8010AA90_game_guys_roulette;
extern GameGuysRouletteSprite D_8010AAB0_game_guys_roulette;
extern u16 D_8010AAD0_game_guys_roulette[3]; // coin digits
extern GameGuysRoulettePlayerInfo D_8010AAD6_game_guys_roulette;
extern u16 D_8010AADE_game_guys_roulette; // window
extern u16 D_8010AAE0_game_guys_roulette;
extern u16 D_8010AAE2_game_guys_roulette;
extern f32 D_8010AAE4_game_guys_roulette;
extern f32 D_8010AAE8_game_guys_roulette;
extern f32 D_8010AAEC_game_guys_roulette;
extern u16 D_8010AAF0_game_guys_roulette[21]; // wheel slot angles
extern f32 D_8010AB20_game_guys_roulette[6];
extern f32 D_8010AB38_game_guys_roulette[6];
extern u8 D_8010AB50_game_guys_roulette;
extern u8 D_8010AB51_game_guys_roulette;
extern s16 D_8010AB52_game_guys_roulette;
extern s16 D_8010AB54_game_guys_roulette; // message window
extern u8 D_8010AB56_game_guys_roulette;  // winning slot
extern u8 D_8010AB57_game_guys_roulette;  // winning prize
extern u8 D_8010AB58_game_guys_roulette;
extern s16 D_8010AB5A_game_guys_roulette; // CPU difficulty

void func_80105A28_game_guys_roulette(void);
void func_80105A78_game_guys_roulette(void);
void func_80105BD8_game_guys_roulette(void);
void func_80105C40_game_guys_roulette(void);
void func_80105CD0_game_guys_roulette(omObjData *object);
void func_80105E10_game_guys_roulette(GameGuysRoulettePlayerInfo *info);
void func_80105F70_game_guys_roulette(void);
void func_80106428_game_guys_roulette(omObjData *object);
void func_801070C4_game_guys_roulette(void);
void func_80107104_game_guys_roulette(void);
void func_8010726C_game_guys_roulette(s16 win);
void func_801073AC_game_guys_roulette(void);
void func_80107A00_game_guys_roulette(void);
void func_80107AA8_game_guys_roulette(void);
void func_80107B20_game_guys_roulette(void);
void func_80108414_game_guys_roulette(void);
void func_80108480_game_guys_roulette(void);
void func_801085A4_game_guys_roulette(omObjData *object);
void func_80108A14_game_guys_roulette(u8 *espriteSlot, s32 spriteIndex, u16 visibility);
void func_80108A6C_game_guys_roulette(GameGuysRouletteSprite *sprite, s32 priority, s32 x, s32 y, u32 width, u32 height,
                                      f32 scaleX, f32 scaleY);
void func_80108A9C_game_guys_roulette(GameGuysRouletteSprite *sprite, u8 visible);
void func_801068E8_game_guys_roulette(omObjData *object);
void func_801069DC_game_guys_roulette(omObjData *object);
void func_80106B74_game_guys_roulette(omObjData *object);
void func_80106C58_game_guys_roulette(omObjData *object);
void func_80106DD8_game_guys_roulette(omObjData *object);
void func_80106EA4_game_guys_roulette(omObjData *object);
void func_801088B0_game_guys_roulette(omObjData *object);
s16 func_80108B44_game_guys_roulette(s16 win, s16 player, s16 mode, s16 count);
void func_80108998_game_guys_roulette(omObjData *object);
void func_801089EC_game_guys_roulette(omObjData *object);

void func_801059A0_game_guys_roulette(void) {
    func_80105C40_game_guys_roulette();
}

s32 func_801059BC_game_guys_roulette(f32 arg0) {
    u8 randomByte1 = rand8();
    u8 randomByte2 = rand8();
    s32 shiftedByte1 = (randomByte1 << 8);
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;

    return scaledRandom;
}

void func_80105A28_game_guys_roulette(void) {
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, 0.0f, 0.0f, 95.0f);
}

void func_80105A78_game_guys_roulette(void) {
    s32 camIndex;

    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(camIndex, 19.03f, 80.0f, 8000.0f);
    CZoom = 1498.69f;
    CRot.x = 334.75f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 10.82f;
    Center.z = -505.55f;
}

void func_80105BD8_game_guys_roulette(void) {
    HuWinInit();
    D_8010AADE_game_guys_roulette = func_80060880_main(130, 110, 9);
    func_8005B63C_main(D_8010AADE_game_guys_roulette, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
    func_80061100_main(D_8010AADE_game_guys_roulette, 1);
    func_80060EA8_main(D_8010AADE_game_guys_roulette, 1);
}

void func_80105C40_game_guys_roulette(void) {
    func_8001FE20_main(32);
    func_800142A0_main(32);
    omInitObjMan(32, 32);
    func_8004A208_main();
    func_80105A28_game_guys_roulette();
    func_80105A78_game_guys_roulette();
    func_80105BD8_game_guys_roulette();
    omAddObj(1000, 0, 0, -1, func_80105CD0_game_guys_roulette);
    omAddObj(2000, 0, 0, -1, func_801089EC_game_guys_roulette);
}

void func_80105CD0_game_guys_roulette(omObjData *object) {
    func_80108D20_game_guys_roulette(160, 86);
    func_80105E10_game_guys_roulette(&D_8010AAD6_game_guys_roulette);
    func_80105F70_game_guys_roulette();
    D_8010A910_game_guys_roulette = omAddObj(0, 10, 10, -1, func_80106428_game_guys_roulette);
    D_8010A918_game_guys_roulette = omAddObj(1, 10, 10, -1, func_801068E8_game_guys_roulette);
    D_8010A914_game_guys_roulette = omAddObj(2, 10, 10, -1, func_801069DC_game_guys_roulette);
    D_8010A91C_game_guys_roulette = omAddObj(3, 10, 10, -1, func_80106B74_game_guys_roulette);
    D_8010A920_game_guys_roulette = omAddObj(4, 10, 10, -1, func_80106C58_game_guys_roulette);
    omAddObj(5, 10, 10, -1, func_80106DD8_game_guys_roulette);
    WipeCreateIn(255, 16);
    object->func = func_80106EA4_game_guys_roulette;
}

void func_80105E10_game_guys_roulette(GameGuysRoulettePlayerInfo *info) {
    u8 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    switch (i) {
        case 0:
            i = 0;
            break;
        case 1:
            i = 1;
            break;
        case 2:
            i = 2;
            break;
        case 3:
            i = 3;
            break;
        default:
            i = 0;
            break;
    }
    info->player = i;
    info->pad = GwPlayer[i].pad;
    info->chr = GwPlayer[i].chr;
    if (GwPlayer[i].stat & 1) {
        info->cpu = 1;
        info->difficulty = GwPlayer[i].cpu_difficulty;
        D_8010AB5A_game_guys_roulette = GwCommon.unkA0;
        if (D_8010AB5A_game_guys_roulette <= 0) {
            D_8010AB5A_game_guys_roulette = 0;
        } else if (D_8010AB5A_game_guys_roulette >= 2) {
            D_8010AB5A_game_guys_roulette = 2;
        }
    } else {
        info->cpu = 0;
        info->difficulty = 0;
    }
    info->coins = GwPlayer[i].gameCoin;
}

void func_80105F70_game_guys_roulette(void) {
    f32 slice = 17.142857f;
    f32 halfSlice = 8.571428f;
    u32 angle;
    u8 i;

    D_8010AB56_game_guys_roulette = func_801059BC_game_guys_roulette(21.0f);
    if (D_8010AB56_game_guys_roulette == 0) {
        D_8010AB57_game_guys_roulette = 5;
    } else if (D_8010AB56_game_guys_roulette < 5) {
        D_8010AB57_game_guys_roulette = 2;
    } else if (D_8010AB56_game_guys_roulette < 7) {
        D_8010AB57_game_guys_roulette = 4;
    } else if (D_8010AB56_game_guys_roulette < 13) {
        D_8010AB57_game_guys_roulette = 0;
    } else if (D_8010AB56_game_guys_roulette < 16) {
        D_8010AB57_game_guys_roulette = 3;
    } else if (D_8010AB56_game_guys_roulette < 21) {
        D_8010AB57_game_guys_roulette = 1;
    }
    if (D_8010AAD6_game_guys_roulette.cpu == 1) {
        D_8010AB52_game_guys_roulette = func_801059BC_game_guys_roulette(6.0f);
        if (D_8010AAD6_game_guys_roulette.difficulty != 0) {
            D_8010AB52_game_guys_roulette -= func_801059BC_game_guys_roulette(D_8010AAD6_game_guys_roulette.difficulty);
            if (D_8010AB52_game_guys_roulette <= 0) {
                D_8010AB52_game_guys_roulette = 0;
            }
        }
        if (D_8010AB57_game_guys_roulette == D_8010AB52_game_guys_roulette) {
            D_8010AB58_game_guys_roulette = 1;
        } else {
            D_8010AB58_game_guys_roulette = 0;
        }
    }
    D_8010AB51_game_guys_roulette = 0;
    for (i = 0; i < 21; i++) {
        angle = (slice * i + 270.0f) * 100.0f;
        if (angle % 100 >= 50) {
            D_8010AAF0_game_guys_roulette[i] = (angle / 100 + 1) % 360;
        } else {
            D_8010AAF0_game_guys_roulette[i] = (angle / 100) % 360;
        }
    }
    D_8010AAE4_game_guys_roulette = (D_8010AAF0_game_guys_roulette[D_8010AB56_game_guys_roulette] + 2520.0f) * 2 / 450.0f;
    D_8010AAE8_game_guys_roulette = D_8010AAE4_game_guys_roulette / 450.0f;
    D_8010AAEC_game_guys_roulette = (D_8010AAE4_game_guys_roulette + D_8010AAE8_game_guys_roulette) *
                                        (D_8010AAE4_game_guys_roulette / D_8010AAE8_game_guys_roulette) / 2.0f -
                                    (D_8010AAF0_game_guys_roulette[D_8010AB56_game_guys_roulette] + 2520.0f);
    D_8010AAE4_game_guys_roulette =
        (D_8010AAF0_game_guys_roulette[D_8010AB56_game_guys_roulette] + 2520.0f - D_8010AAEC_game_guys_roulette) * 2 / 450.0f;
    D_8010AAE8_game_guys_roulette = D_8010AAE4_game_guys_roulette / 450.0f;
    D_8010AB20_game_guys_roulette[0] = 270.0f - halfSlice;
    D_8010AB20_game_guys_roulette[1] = slice + D_8010AB20_game_guys_roulette[0];
    D_8010AB20_game_guys_roulette[2] = slice * 4 + D_8010AB20_game_guys_roulette[1];
    D_8010AB20_game_guys_roulette[3] = slice * 2 + D_8010AB20_game_guys_roulette[2] - 360.0f;
    D_8010AB20_game_guys_roulette[4] = slice * 6 + D_8010AB20_game_guys_roulette[3];
    D_8010AB20_game_guys_roulette[5] = slice * 3 + D_8010AB20_game_guys_roulette[4];
    D_8010AB38_game_guys_roulette[0] = D_8010AAF0_game_guys_roulette[9] + halfSlice;
    D_8010AB38_game_guys_roulette[1] = D_8010AAF0_game_guys_roulette[18];
    D_8010AB38_game_guys_roulette[2] = D_8010AAF0_game_guys_roulette[2] + halfSlice;
    D_8010AB38_game_guys_roulette[3] = D_8010AAF0_game_guys_roulette[14];
    D_8010AB38_game_guys_roulette[4] = D_8010AAF0_game_guys_roulette[5] + halfSlice;
    D_8010AB38_game_guys_roulette[5] = 270.0f;
    D_8010AB50_game_guys_roulette = 0;
}

void func_80106428_game_guys_roulette(omObjData *object) {
    GameGuysRoulettePrizeFiles prizeFiles = D_8010A6C0_game_guys_roulette;
    s32 chr = GwPlayer[D_8010AAD6_game_guys_roulette.player].chr;
    GameGuysRouletteCharFiles charFiles = D_8010A6D8_game_guys_roulette;
    s16 sprite;
    u8 i;

    func_80108A14_game_guys_roulette(&D_8010A930_game_guys_roulette.slot, 0x630000, 0x4008);
    func_80108A6C_game_guys_roulette(&D_8010A930_game_guys_roulette, 1000, 0, 0, 320, 240, 1.0f, 1.0f);
    func_80108A9C_game_guys_roulette(&D_8010A930_game_guys_roulette, 1);
    func_80108A14_game_guys_roulette(&D_8010A950_game_guys_roulette.slot, 0x630001, 0x4008);
    func_80108A6C_game_guys_roulette(&D_8010A950_game_guys_roulette, 900, 0, 0, 320, 128, 1.0f, 1.0f);
    func_80108A9C_game_guys_roulette(&D_8010A950_game_guys_roulette, 0);
    func_80108A14_game_guys_roulette(&D_8010A970_game_guys_roulette.slot, 0x630002, 0x4008);
    func_80108A6C_game_guys_roulette(&D_8010A970_game_guys_roulette, 900, 0, 0, 320, 128, 1.0f, 1.0f);
    func_80108A9C_game_guys_roulette(&D_8010A970_game_guys_roulette, 0);
    func_80108A14_game_guys_roulette(&D_8010A990_game_guys_roulette.slot, 0x630003, 8);
    func_80108A6C_game_guys_roulette(&D_8010A990_game_guys_roulette, 800, 242, 16, 54, 144, 1.0f, 1.0f);
    func_80108A9C_game_guys_roulette(&D_8010A990_game_guys_roulette, 1);
    for (i = 0; i < 6; i++) {
        func_80108A14_game_guys_roulette(&D_8010A9B0_game_guys_roulette[i].slot, prizeFiles.ids[i] | 0x630000, 8);
        func_80108A6C_game_guys_roulette(&D_8010A9B0_game_guys_roulette[i], 700, 246, i * 22 + 22, 22, 22, 1.0f, 1.0f);
        func_80108A9C_game_guys_roulette(&D_8010A9B0_game_guys_roulette[i], 0);
    }
    func_80108A14_game_guys_roulette(&D_8010AA70_game_guys_roulette.slot, charFiles.ids[chr] | 0x210000, 8);
    func_80108A6C_game_guys_roulette(&D_8010AA70_game_guys_roulette, 600, 206, 1, 46, 46, 1.0f, 1.0f);
    func_80108A9C_game_guys_roulette(&D_8010AA70_game_guys_roulette, 0);
    func_80108A14_game_guys_roulette(&D_8010AA90_game_guys_roulette.slot, 0x21001A, 8);
    func_80108A6C_game_guys_roulette(&D_8010AA90_game_guys_roulette, 500, 24, 16, 12, 12, 1.0f, 1.0f);
    func_80108A9C_game_guys_roulette(&D_8010AA90_game_guys_roulette, 1);
    func_80108A14_game_guys_roulette(&D_8010AAB0_game_guys_roulette.slot, 0x21001B, 8);
    func_80108A6C_game_guys_roulette(&D_8010AAB0_game_guys_roulette, 500, 36, 16, 12, 12, 1.0f, 1.0f);
    func_80108A9C_game_guys_roulette(&D_8010AAB0_game_guys_roulette, 1);
    sprite = func_8000B838_main(0x31);
    D_8010AAD0_game_guys_roulette[0] = espEntry(sprite, 0, 1);
    espPosSet(D_8010AAD0_game_guys_roulette[0], 54, 22);
    espPriSet(D_8010AAD0_game_guys_roulette[0], 500);
    D_8010AAD0_game_guys_roulette[1] = espEntry(sprite, 0, 1);
    espPosSet(D_8010AAD0_game_guys_roulette[1], 66, 22);
    espPriSet(D_8010AAD0_game_guys_roulette[1], 500);
    D_8010AAD0_game_guys_roulette[2] = espEntry(sprite, 0, 1);
    espPosSet(D_8010AAD0_game_guys_roulette[2], 78, 22);
    espPriSet(D_8010AAD0_game_guys_roulette[2], 500);
    object->func = func_801085A4_game_guys_roulette;
}

void func_801068E8_game_guys_roulette(omObjData *object) {
    object->model[0] = func_8000B108_main(0xA0063, 0x2B9);
    omSetTra(object, 0.0f, 193.0f, -117.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    func_8000B460_main(object, 0, 0xA0063);
    func_8000B460_main(object, 1, 0xA0066);
    func_8000B460_main(object, 2, 0xA0067);
    Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[0]].motId, 0, 30, 2);
    object->func = NULL;
}

void func_801069DC_game_guys_roulette(omObjData *object) {
    GameGuysRoulettePrizeFiles modelFiles = D_8010A6F8_game_guys_roulette;
    u8 i;

    object->model[0] = func_8000B108_main(0x63000D, 0x2B9);
    omSetTra(object, 0.0f, 100.0f, 0.0f);
    omSetRot(object, 15.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    for (i = 1; i < 7; i++) {
        object->model[i] = func_8000B108_main(modelFiles.ids[i - 1] | 0x630000, 0x2B9);
        Hu3DModelPosSet(object->model[i], 0.0f, 100.0f, 0.0f);
        Hu3DModelRotSet(object->model[i], 15.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(object->model[i], 1.0f, 1.0f, 1.0f);
    }
    object->func = NULL;
}

void func_80106B74_game_guys_roulette(omObjData *object) {
    GameGuysRouletteCharFiles charFiles = D_8010A710_game_guys_roulette;

    object->model[0] = func_8000B108_main(charFiles.ids[D_8010AAD6_game_guys_roulette.chr] | 0x210000, 0x2B9);
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 15.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    Hu3DModelCameraSet(object->model[0], 0);
    object->func = NULL;
}

void func_80106C58_game_guys_roulette(omObjData *object) {
    f32 x, y, z;

    object->model[0] = func_8000B108_main(0x63000B, 0x2B9);
    object->model[1] = func_8000B108_main(0x63000C, 0x2B9);
    x = cosdf(270.0f) * 85.0f;
    y = cosdf(15.0f) * 100.0f - sindf(270.0f) * 85.0f * sindf(15.0f);
    z = sindf(15.0f) * 100.0f + sindf(270.0f) * 85.0f * cosdf(15.0f);
    omSetTra(object, x, y + 100.0f, z);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    object->func = NULL;
}

void func_80106DD8_game_guys_roulette(omObjData *object) {
    object->model[0] = func_8000B108_main(0x630014, 0x2B9);
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    func_8000B460_main(object, 0, 0x630014);
    Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[0]].motId, 0, 30, 2);
    object->func = NULL;
}

void func_80106EA4_game_guys_roulette(omObjData *object) {
    switch (D_8010AB50_game_guys_roulette) {
        case 0:
            func_801070C4_game_guys_roulette();
            break;
        case 1:
            D_8010A924_game_guys_roulette = omAddPrcObj(func_80107104_game_guys_roulette, 0x3F00, 0x800, 0);
            D_8010AB50_game_guys_roulette = 2;
            break;
        case 2:
            if (D_8010AAE0_game_guys_roulette == 1) {
                D_8010AB50_game_guys_roulette = 5;
                D_8010AAE0_game_guys_roulette = 0;
                omDelPrcObj(D_8010A924_game_guys_roulette);
                D_800D6A58_main = 0;
                D_8010AB54_game_guys_roulette = GMesCreate(0x1A, 10, 156, 56);
            }
            break;
        case 5:
            func_801073AC_game_guys_roulette();
            break;
        case 6:
            D_8010A928_game_guys_roulette = omAddPrcObj(func_80107A00_game_guys_roulette, 0x3F00, 0x800, 0);
            D_8010AB50_game_guys_roulette = 7;
            break;
        case 7:
            if (D_8010AA70_game_guys_roulette.scaleX > 0.0f) {
                D_8010AA70_game_guys_roulette.scaleX = D_8010AA70_game_guys_roulette.scaleY -= 0.25f;
                func_80108A9C_game_guys_roulette(&D_8010AA70_game_guys_roulette, 1);
            } else {
                D_8010AA70_game_guys_roulette.scaleX = D_8010AA70_game_guys_roulette.scaleY = 0.0f;
                func_80108A9C_game_guys_roulette(&D_8010AA70_game_guys_roulette, 0);
            }
            if (D_8010AAE2_game_guys_roulette == 1 && D_8010AA70_game_guys_roulette.scaleX <= 0.0f) {
                D_8010AB50_game_guys_roulette = 8;
                D_8010AAE2_game_guys_roulette = 0;
                omDelPrcObj(D_8010A928_game_guys_roulette);
            }
            break;
        case 8:
            func_80107AA8_game_guys_roulette();
            break;
        case 9:
            func_80107B20_game_guys_roulette();
            break;
        case 10:
            func_80108414_game_guys_roulette();
            break;
        case 11:
            func_80108480_game_guys_roulette();
            break;
        case 12:
            object->func = func_801088B0_game_guys_roulette;
            break;
    }
}

void func_801070C4_game_guys_roulette(void) {
    D_8010A646_game_guys_roulette = func_80109078_game_guys_roulette();
    if (D_8010A646_game_guys_roulette == 1) {
        D_8010AB50_game_guys_roulette = 1;
    }
}

void func_80107104_game_guys_roulette(void) {
    s16 done = FALSE;
    s16 choice;

    HuWinHomeClear(D_8010AADE_game_guys_roulette);
    HuAudFXPlay(0x11D);
    func_80060C14_main(D_8010AADE_game_guys_roulette, 1);
    HuWinMesSet(D_8010AADE_game_guys_roulette, 0x2D00, -1, -1);
    func_8010726C_game_guys_roulette(D_8010AADE_game_guys_roulette);
    HuWinMesSet(D_8010AADE_game_guys_roulette, 0x2D01, -1, -1);
    while (done == FALSE) {
        choice = func_80108B44_game_guys_roulette(D_8010AADE_game_guys_roulette, D_8010AAD6_game_guys_roulette.pad,
                                                  D_8010AAD6_game_guys_roulette.cpu, 1);
        if (choice == 0) {
            HuWinMesSet(D_8010AADE_game_guys_roulette, 0x2D02, -1, -1);
            func_8010726C_game_guys_roulette(D_8010AADE_game_guys_roulette);
            done = TRUE;
        } else if (choice == 1) {
            done = TRUE;
        }
        HuPrcVSleep();
    }
    HuWinMesSet(D_8010AADE_game_guys_roulette, 0x2D03, -1, -1);
    func_8010726C_game_guys_roulette(D_8010AADE_game_guys_roulette);
    HuWinHomeClear(D_8010AADE_game_guys_roulette);
    func_80060EA8_main(D_8010AADE_game_guys_roulette, 1);
    D_8010AAE0_game_guys_roulette = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_8010726C_game_guys_roulette(s16 win) {
    s16 i;

    HuWinComKeyReset();
    while (HuWinStatGet(win) != 0) {
        switch (D_8010AAD6_game_guys_roulette.cpu) {
            case 0:
                if (D_800D5558_main[D_8010AAD6_game_guys_roulette.pad] & 0x8000) {
                    HuWinComKeySet(-0x8000, -0x8000, -0x8000, -0x8000);
                }
                break;
            case 1:
                for (i = 0; i < 10; i++) {
                    HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000,
                                    D_8010A640_game_guys_roulette[D_8010AB5A_game_guys_roulette]);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_801073AC_game_guys_roulette);

void func_80107A00_game_guys_roulette(void) {
    HuWinHomeClear(D_8010AADE_game_guys_roulette);
    func_80060C14_main(D_8010AADE_game_guys_roulette, 1);
    HuWinMesSet(D_8010AADE_game_guys_roulette, 0x2D04, -1, -1);
    HuWinInsertMesSet(D_8010AADE_game_guys_roulette, D_8010AB51_game_guys_roulette + 0x2D05, 0);
    func_8010726C_game_guys_roulette(D_8010AADE_game_guys_roulette);
    HuWinHomeClear(D_8010AADE_game_guys_roulette);
    func_80060EA8_main(D_8010AADE_game_guys_roulette, 1);
    D_8010AAE2_game_guys_roulette = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_80107AA8_game_guys_roulette(void) {
    if (++D_8010A65C_game_guys_roulette == 1) {
        GMesCreate(9);
    } else if (GMesStatGet() == GMES_STAT_NONE) {
        HuAudSeqFadeOut(0x1E);
        D_8010AB50_game_guys_roulette = 9;
        D_8010A65C_game_guys_roulette = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80107B20_game_guys_roulette);

void func_80108414_game_guys_roulette(void) {
    if (++D_8010A678_game_guys_roulette == 1) {
        GMesCreate(0x14);
        HuAudSeqFadeOut(0x78);
    } else if (GMesStatGet() == GMES_STAT_NONE) {
        D_8010AB50_game_guys_roulette = 0xB;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A770_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A77C_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A78C_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A794_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A7A0_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A7AC_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A7B8_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A7C4_game_guys_roulette);

void func_80108480_game_guys_roulette(void) {
    if (D_8010A67B_game_guys_roulette == 0) {
        func_8004AB0C_main(30);
        if (D_8010AB58_game_guys_roulette == 1) {
            HuAudSeqPlay(0x73);
            D_8010A67C_game_guys_roulette = GMesCreate(0x16, D_8010AAD6_game_guys_roulette.chr);
            func_800370D0_main(D_8010A67C_game_guys_roulette, 0x78);
        } else {
            HuAudSeqPlay(0x71);
            sprintf(D_8010A810_game_guys_roulette, "%s\x81\x40\x82\x6B\x82\x6E\x82\x72\x82\x73\x81\x49",
                    D_8010A680_game_guys_roulette[D_8010AAD6_game_guys_roulette.chr]);
            D_8010A67C_game_guys_roulette = GMesCreate(0x19, D_8010A810_game_guys_roulette, 0xA0, 0x78, 1.0, 1.0, 1);
            func_800370D0_main(D_8010A67C_game_guys_roulette, 0x78);
        }
        D_8010A67B_game_guys_roulette = 1;
    } else if (D_8010A67B_game_guys_roulette == 1) {
        if (D_8010A67A_game_guys_roulette++ >= 135) {
            D_8010AB50_game_guys_roulette = 12;
        }
    }
}

void func_801085A4_game_guys_roulette(omObjData *object) {
    u16 digit;
    s16 x = 0;

    if (D_8010A6A0_game_guys_roulette >= 5) {
        if (D_8010A6A1_game_guys_roulette == 0) {
            func_80108A9C_game_guys_roulette(&D_8010A950_game_guys_roulette, 0);
            func_80108A9C_game_guys_roulette(&D_8010A970_game_guys_roulette, 0);
        } else if (D_8010A6A1_game_guys_roulette == 1) {
            func_80108A9C_game_guys_roulette(&D_8010A950_game_guys_roulette, 1);
            func_80108A9C_game_guys_roulette(&D_8010A970_game_guys_roulette, 0);
        } else if (D_8010A6A1_game_guys_roulette == 2) {
            func_80108A9C_game_guys_roulette(&D_8010A950_game_guys_roulette, 0);
            func_80108A9C_game_guys_roulette(&D_8010A970_game_guys_roulette, 1);
        }
        D_8010A6A1_game_guys_roulette++;
        if (D_8010A6A1_game_guys_roulette >= 3) {
            D_8010A6A1_game_guys_roulette = 0;
        }
        D_8010A6A0_game_guys_roulette = 0;
    }
    D_8010A6A0_game_guys_roulette++;
    if (D_8010AAD6_game_guys_roulette.coins >= 999) {
        D_8010AAD6_game_guys_roulette.coins = 999;
    }
    if (D_8010AAD6_game_guys_roulette.coins == 0) {
        D_8010AAD6_game_guys_roulette.coins = 0;
    }

    espDispOn(D_8010AAD0_game_guys_roulette[2]);
    if ((digit = D_8010AAD6_game_guys_roulette.coins / 100) == 0) {
        espDispOff(D_8010AAD0_game_guys_roulette[2]);
    }
    func_8000BD50_main(D_8010AAD0_game_guys_roulette[2], digit);
    espPosSet(D_8010AAD0_game_guys_roulette[2], x + 54, 22);
    if (digit != 0) {
        x += 12;
    }

    espDispOn(D_8010AAD0_game_guys_roulette[1]);
    if ((digit = (u16)(D_8010AAD6_game_guys_roulette.coins % 100) / 10) == 0 &&
        (u16)(D_8010AAD6_game_guys_roulette.coins / 100) == 0) {
        espDispOff(D_8010AAD0_game_guys_roulette[1]);
    }
    func_8000BD50_main(D_8010AAD0_game_guys_roulette[1], digit);
    espPosSet(D_8010AAD0_game_guys_roulette[1], x + 54, 22);
    if (digit != 0 || (u16)(D_8010AAD6_game_guys_roulette.coins / 100) != 0) {
        x += 12;
    }

    func_8000BD50_main(D_8010AAD0_game_guys_roulette[0], D_8010AAD6_game_guys_roulette.coins % 10);
    espPosSet(D_8010AAD0_game_guys_roulette[0], x + 54, 22);
}

void func_801088B0_game_guys_roulette(omObjData *object) {
    GwPlayer[D_8010AAD6_game_guys_roulette.player].gameCoin = D_8010AAD6_game_guys_roulette.coins;
    if (D_8010AB58_game_guys_roulette == 1) {
        GwPlayer[D_8010AAD6_game_guys_roulette.player].bonusCoin = D_8010A6A4_game_guys_roulette[D_8010AB51_game_guys_roulette];
    } else if (D_8010AB58_game_guys_roulette == 0) {
        GwPlayer[D_8010AAD6_game_guys_roulette.player].bonusCoin = 0;
    }
    WipeCreateOut(0, 20);
    HuAudSeqFadeOut(30);
    func_8004AB0C_main(30);
    object->func = func_80108998_game_guys_roulette;
}

void func_80108998_game_guys_roulette(omObjData *object) {
    if (WipeStatGet() == 0) {
        osViBlack(0);
        func_80109D14_game_guys_roulette();
        GMesClose();
        HuWinAllKill();
        HuSprAnimAllKill();
        omOvlReturnEx(1);
    }
}

void func_801089EC_game_guys_roulette(omObjData *object) {
    if (D_800D530C_main == 1) {
        object->func = func_801088B0_game_guys_roulette;
    }
}

void func_80108A14_game_guys_roulette(u8 *espriteSlot, s32 spriteIndex, u16 visibility) {
    *espriteSlot = espEntry(func_8000B838_main(spriteIndex), 0, 1);
    espAttrSet(*espriteSlot, visibility);
}

void func_80108A6C_game_guys_roulette(GameGuysRouletteSprite *sprite, s32 priority, s32 x, s32 y, u32 width, u32 height,
                                      f32 scaleX, f32 scaleY) {
    sprite->priority = priority;
    sprite->x = x;
    sprite->y = y;
    sprite->width = width;
    sprite->height = height;
    sprite->scaleX = scaleX;
    sprite->scaleY = scaleY;
}

void func_80108A9C_game_guys_roulette(GameGuysRouletteSprite *sprite, u8 visible) {
    espPosSet(sprite->slot, sprite->x + sprite->width / 2, sprite->y + sprite->height / 2);
    espScaleSet(sprite->slot, sprite->scaleX, sprite->scaleY);
    espPriSet(sprite->slot, (u16)sprite->priority);
    if (visible == 1) {
        espDispOn(sprite->slot);
    } else {
        espDispOff(sprite->slot);
    }
}

s16 func_80108B44_game_guys_roulette(s16 win, s16 player, s16 mode, s16 count) {
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
                keys[player] = 0x400;
                HuWinComKeyWait(keys[0], keys[1], keys[2], keys[3], D_8010A640_game_guys_roulette[D_8010AB5A_game_guys_roulette]);
            }
            HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, D_8010A640_game_guys_roulette[D_8010AB5A_game_guys_roulette]);
            break;
    }
    return HuWinChoiceGet(win, 0, 1);
}
