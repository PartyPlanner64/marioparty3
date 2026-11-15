#include "common.h"
#include "option.h"
#include "overlays/minigame.h"
#include "game/vibrator.h"
#include "game/mallocblock.h"
#include "game/pad.h"
#include "game/saveload.h"

// One entry per on-screen cursor; the object is the 3D cursor for that slot.
typedef struct {
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ Vec unk_18;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ omObjData *obj;
} OptCursor; // sizeof 0x2C

// Object that keeps an attached 3d model sound playing for a fixed duration.
typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s32 seNo;
} OptSeObj; // sizeof 0x8

typedef struct {
    s32 message;
    s16 sound;
} OptSoundEntry;

typedef struct {
    s32 title;
    OptSoundEntry entries[9];
} OptSoundPage;

typedef struct {
    OptSoundPage pages[15];
} OptSoundMenu;

typedef struct {
    OptSoundPage pages[12];
} OptMusicMenu;

// Window rectangle for a line of the board record pages, relative to the top left of the page.
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 w;
    /* 0x0C */ f32 h;
} OptRecordWinRect; // sizeof 0x10

extern const OptSoundMenu D_80113DA8_option;
extern const OptMusicMenu D_8011421C_option;
extern OptSprSlot D_80114EF0_option[0x40];
extern OptSpr D_801147F0_option[0x40];
extern UnkOption D_80114F70_option[0x40];
extern s16 D_80115A70_option;
extern u16 D_80115A72_option;
extern OptWinEntry D_80115A78_option[0x20];
extern SaveCommonBuf D_800D09A8_main;
extern s32 D_801139D0_option;

s32 func_80113204_option(s32 arg0);
s32 func_8010FE00_option(void);
s32 func_80110018_option(void);
void func_8010FE10_option(void);
omObjData *func_8010FF0C_option(s32);

void func_8010C3E4_option(s32 animFile, s16 x, s16 y);
void func_8010D5B0_option(s32 animFile, s16 x, s16 y);
void func_80107F50_option(s32 animFile, s16 x, s16 y);
s32 func_8010BACC_option(s32, s32);
void func_801133BC_option(s32, u32);
void func_80113368_option(s32, s32 *, s32 *);
void func_8011323C_option(s32);
void func_80113258_option(s32);
void func_80113490_option(s32);
void func_80113424_option(s32);
s32 func_801130E8_option(s32);
s32 func_80109D04_option(s32, s32);
s32 func_80109EF4_option(s32, s32);
void func_8010A3E8_option(s32, s32);
void func_80109908_option(f32, f32, f32, s32 *, s32 *);
omObjData *func_80107758_option(Vec *, Vec *, s32);
void func_801133EC_option(s32);
void func_80109730_option(Vec *, Vec *, Vec *, f32, Vec *, f32 *, f32 *);
void func_80112F48_option(s32, s32, f32, f32, f32);
void func_8011331C_option(s32, s32, u16);
void func_801132AC_option(s32, s32);
void func_801132C8_option(s32, s32);
void func_801132E4_option(s32, u32);
void func_80112EB8_option(s32, s32, f32, f32, f32);
void func_80112FF4_option(s32, s32, f32, f32, f32);
void func_80112FD8_option(s32, s32, s32);
void func_80106508_option(Vec *, Vec *, Vec *);
void func_80113088_option(void);
s32 func_80105FF8_option(Vec *, Vec *, Vec *);
void func_80105F08_option(f32 fov);
void func_80106B78_option(void);
omObjData *func_80107AD4_option(Vec *pos, Vec *at, s32 duration);
void func_80113274_option(s32, f32 *, f32 *, f32 *);
void func_80113290_option(s32, f32, f32, f32);
omObjData *func_80106F88_option(Vec *, Vec *, s32);
void func_80108B34_option(void);
void func_80108B58_option(void);
s32 func_80109504_option(void);
void func_80112084_option(void);
void func_8010FB40_option(s32, s32);
void func_8010FA28_option(void);
void func_8011239C_option(void);
void func_8010A66C_option(void);
void func_8010C224_option(void);
void func_8010F94C_option(void);
void func_8010FDF4_option(void);
void func_80112060_option(void);
void func_80108A68_option(void);
void func_80108AAC_option(void);
void func_80108AF0_option(void);
void func_8011053C_option(s32, s32, s32);
void func_8011019C_option(void);
void func_80110754_option(void);
void func_801119CC_option(void);
void func_8011083C_option(s32, s32, s32);
void func_801110C0_option(s32, u32, s16, s16, u16, u16, s16);
void func_80111A10_option(s32);
void func_80111C50_option(s32, u32);
void func_80112028_option(s32, s32, s32);
void func_801130CC_option(void);
s32 func_80113218_option(s32);
omObjData *func_8010737C_option(Vec *, Vec *, s32);
void func_80113338_option(s32, s32, s16, s16, u16);
void func_80113384_option(s32);
void func_801133A0_option(s32);
void func_80113408_option(s32, u32);
void func_80113440_option(s32);
s32 func_8010AF54_option(s32, s32);
s32 func_8010A940_option(s32, s32);
void func_8010B654_option(s32, s32);
s32 func_8011345C_option(s32);
void func_801123D8_option(void);
void func_80113300_option(s32);
void func_80112A44_option(void);
void func_80112B08_option(void);
void func_80112E14_option(void);
void func_8010FFDC_option(void);
void func_8010E8E0_option(void);
void func_8010F138_option(void);

Vec D_801134F0_option[2] = {
    { 0.0f, 271.19f, 350.0f },
    { 0.0f, 228.72f, -550.0f },
}; /* Unreferenced. */
Vec D_80113508_option[2] = {
    { 0.0f, 250.0f, 350.0f },
    { 0.0f, 228.72f, 1275.0f },
};
Vec D_80113520_option[4][2] = {
    { { 0.0f, 271.19f, 350.0f }, { 0.0f, 228.72f, -550.0f } },
    { { 0.0f, 271.19f, 350.0f }, { -535.0f, 228.72f, -550.0f } },
    { { 0.0f, 271.19f, 350.0f }, { 535.0f, 228.72f, -550.0f } },
    { { 0.0f, 250.0f, -400.0f }, { 0.0f, 228.72f, 1275.0f } },
}; /* Unreferenced. */
Vec D_80113580_option[6][2] = {
    { { 0.0f, 264.9f, 364.27f }, { 0.0f, 184.59999f, 61.300003f } },
    { { 0.0f, 224.46501f, -293.5f }, { 0.0f, 123.75f, -61.300003f } },
    { { 0.0f, 224.46501f, 364.27f }, { -242.5f, 123.75f, -358.5f } },
    { { 0.0f, 224.46501f, 364.27f }, { 240.0f, 123.75f, -358.5f } },
    { { 0.0f, 224.46501f, -293.5f }, { -265.7f, 105.85f, 725.0f } },
    { { 0.0f, 224.46501f, -293.5f }, { 265.7f, 105.85f, 725.0f } },
};
Vec D_80113610_option[9] = {
    { 0.0f, 184.59999f, -61.300003f },
    { 0.0f, 184.59999f, -61.300003f },
    { 0.0f, 123.75f, -640.0f },
    { -242.5f, 201.0f, -358.5f },
    { 535.0f, 228.72f, -550.0f },
    { -265.7f, 105.85f, 725.0f },
    { 265.7f, 105.85f, 725.0f },
    { 0.0f, 225.0f, 0.0f },
    { 0.0f, 200.0f, -220.0f },
}; /* Unreferenced. */
Vec D_8011367C_option[2] = {
    { 0.0f, 225.0f, 0.0f },
    { -75.0f, 200.0f, -680.0f },
};
Vec D_80113694_option[2] = {
    { 0.0f, 225.0f, 0.0f },
    { 75.0f, 200.0f, -680.0f },
};
Vec D_801136AC_option[2] = {
    { 0.0f, 225.0f, 0.0f },
    { 0.0f, 225.0f, 475.0f },
};
Vec D_801136C4_option[4] = {
    { 0.0f, 170.0f, -7.64f },
    { -195.0f, -165.0f, -220.0f },
    { 195.0f, 165.0f, -220.0f },
    { -50.0f, 0.0f, 475.0f },
}; /* Unreferenced. */
Vec D_801136F4_option = { 0.0f, 410.0f, -450.0f };
Vec D_80113700_option = { 0.0f, 410.0f, -550.0f };
Vec D_8011370C_option = { -535.0f, 88.70001f, -450.0f };
Vec D_80113718_option = { -535.0f, 88.70001f, -550.0f };
Vec D_80113724_option = { 535.0f, 88.70001f, -450.0f };
Vec D_80113730_option = { 535.0f, 88.70001f, -550.0f };
Vec D_8011373C_option = { 0.0f, 128.70001f, 1175.0f };
Vec D_80113748_option = { 0.0f, 128.70001f, 1275.0f };
Vec D_80113754_option[2] = {
    { 0.0f, 93.70001f, -450.0f },
    { 0.0f, 93.70001f, -525.0f },
}; /* Unreferenced. */
Vec D_8011376C_option[4] = {
    { 0.0f, 430.0f, -550.0f },
    { -535.0f, 100.0f, -550.0f },
    { 535.0f, 100.0f, -550.0f },
    { 0.0f, 100.0f, 1275.0f },
};
Vec D_8011379C_option[2] = {
    { 0.0f, 271.19f, 350.0f },
    { 0.0f, 228.72f, -550.0f },
};
Vec D_801137B4_option[2] = {
    { 0.0f, 250.0f, 350.0f },
    { 0.0f, 228.72f, 1275.0f },
};
Vec D_801137CC_option[2] = {
    { 0.0f, 228.72f, 350.0f },
    { -535.0f, 228.72f, -550.0f },
};
Vec D_801137E4_option[2] = {
    { 0.0f, 228.72f, 350.0f },
    { 535.0f, 228.72f, -550.0f },
};
Vec D_801137FC_option = { -265.7f, 105.85f, 625.0f };
Vec D_80113808_option = { -265.7f, 105.85f, 725.0f };
Vec D_80113814_option = { 265.7f, 105.85f, 625.0f };
Vec D_80113820_option = { 265.7f, 105.85f, 725.0f };
Vec D_8011382C_option[2] = {
    { -228.75f, 123.75f, 41.500015f },
    { -323.75f, 98.75f, -358.5f },
};
Vec D_80113844_option[2] = {
    { 0.0f, 224.46501f, 364.27f },
    { -242.5f, 123.75f, -358.5f },
};
Vec D_8011385C_option[2] = {
    { 228.75f, 123.75f, 41.500015f },
    { 323.75f, 98.75f, -358.5f },
};
Vec D_80113874_option[2] = {
    { 0.0f, 224.46501f, 364.27f },
    { 242.5f, 123.75f, -358.5f },
};
Vec D_8011388C_option = { -195.0f, 165.0f, -695.0f };
Vec D_80113898_option = { 195.0f, 165.0f, -695.0f };
Vec D_801138A4_option = { -50.0f, 225.0f, 475.0f };
Vec D_801138B0_option = { 0.0f, 225.0f, 275.0f };
Vec D_801138BC_option = { 0.0f, 225.0f, 575.0f };
s32 D_801138C8_option[9] = { 0, 1, 2, 3, 4, 5, 7, 6, 8 };
OptRecordWinRect D_801138EC_option[6] = {
    { 0.0f, 0.0f, 213.0f, 20.0f },
    { 0.0f, 19.0f, 213.0f, 20.0f },
    { 0.0f, 34.0f, 213.0f, 20.0f },
    { 0.0f, 53.0f, 213.0f, 20.0f },
    { 0.0f, 105.0f, 213.0f, 20.0f },
    { 0.0f, 120.0f, 213.0f, 20.0f },
};
s32 D_8011394C_option[9] = { 0, 1, 2, 3, 4, 5, 7, 6, 8 };
OptRecordWinRect D_80113970_option[6] = {
    { 0.0f, 0.0f, 213.0f, 20.0f },
    { 0.0f, 19.0f, 213.0f, 20.0f },
    { 0.0f, 34.0f, 213.0f, 20.0f },
    { 0.0f, 53.0f, 213.0f, 20.0f },
    { 0.0f, 105.0f, 213.0f, 20.0f },
    { 0.0f, 120.0f, 213.0f, 20.0f },
};

Process *D_80114770_option BSS;
u8 D_80114774_option[4] BSS; /* Unreferenced. */
s32 D_80114778_option[4] BSS;
OptCursor D_80114788_option[2] BSS;
OptSeObj D_801147E0_option BSS;
s32 D_801147E8_option BSS;

void func_80107F50_option(s32 animFile, s16 x, s16 y) {
    s16 wins[10];
    u8 text0[32];
    u8 text1[32];
    u8 text2[32];
    u8 records[10] = { 0, 1, 2, 4, 3, 5, 6, 7, 9, 8 };
    s8 minigames[10] = { 13, 16, 35, 52, 44, 71, 71, 71, 0, -1 };
    s32 messages[10] = { 0x4501, 0x4502, 0x4503, 0x4504, 0x4505, 0x4506, 0x4507, 0x4508, 0x4509, 0x450A };
    s16 anim;
    u16 sprite;
    s16 win;
    s16 i;
    s16 j;
    s16 record;
    s32 offsetY;
    f32 scale;

    HuPrcSleep(3);
    anim = HuSprAnimDataRead(animFile);
    sprite = espEntry(anim, 0, 1);
    espPosSet(sprite, x, y);
    espPriSet(sprite, 0x8000);
    espScaleSet(sprite, 0.0f, 0.0f);
    for (i = 0; i < 10; i++) {
        offsetY = i * 14 - 71;
        wins[i] = HuWinExCreate(-1, x - 104, y + offsetY, 213, 20, 0);
        HuWinBGTPLvlSet(wins[i], 0);
    }
    win = HuWinExCreate(-1, 0, 0, 210, 14, 1);
    HuWinBGColSet(win, 255, 255, 255);
    HuAudFXPlay(0x2E7);
    for (i = 1; i <= 10; i++) {
        scale = cosdf(i * 36.0f) * 0.5f + 0.5f;
        espScaleSet(sprite, scale, sindf(i * 9.0f));
        HuPrcVSleep();
    }
    for (i = 0; i < 10; i++) {
        record = GWMgRecordGet(records[i]);
        if (record < 0) {
            record = 0;
        }
        switch (records[i]) {
            case 0:
                sprintf((char *)text0, "%3d", record);
                HuWinInsertMesSet(wins[i], (u32)text0, 0);
                break;
            case 1:
            case 2:
            case 5:
            case 6:
            case 7:
                sprintf((char *)text0, "%d", record / 3600);
                HuWinInsertMesSet(wins[i], (u32)text0, 0);
                record %= 3600;
                sprintf((char *)text1, "%2d", record / 60);
                if (text1[0] == ' ') {
                    text1[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)text1, 1);
                sprintf((char *)text2, "%2d", (s16)((record % 60) / 60.0f * 100.0f));
                if (text2[0] == ' ') {
                    text2[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)text2, 2);
                break;
            case 4:
                sprintf((char *)text0, "%3d", record / 100);
                record %= 100;
                HuWinInsertMesSet(wins[i], (u32)text0, 0);
                sprintf((char *)text1, "%2d", record);
                if (text1[0] == ' ') {
                    text1[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)text1, 1);
                break;
            case 3:
            case 9:
                sprintf((char *)text0, "%d", record / 1800);
                HuWinInsertMesSet(wins[i], (u32)text0, 0);
                record %= 1800;
                sprintf((char *)text1, "%2d", record / 30);
                if (text1[0] == ' ') {
                    text1[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)text1, 1);
                sprintf((char *)text2, "%2d", (s16)((record % 30) * (1.0f / 30.0f) * 99.0f));
                if (text2[0] == ' ') {
                    text2[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)text2, 2);
                break;
            case 8:
                sprintf((char *)text0, "%4d", record);
                HuWinInsertMesSet(wins[i], (u32)text0, 0);
                break;
        }
        HuWinDispOn(wins[i]);
        record = minigames[i];
        record--;
        if (record == 70 && _CheckFlag(0x2B)) {
            HuWinMesSet(wins[i], messages[i], -1, -1);
        } else if (record >= 0 && GWMgUnlockCheck(record)) {
            HuWinMesSet(wins[i], messages[i], -1, -1);
        } else if (record == -1 && _CheckFlag(0x1E)) {
            HuWinMesSet(wins[i], messages[i], -1, -1);
        } else if (record == -2 && _CheckFlag(0x1F)) {
            HuWinMesSet(wins[i], messages[i], -1, -1);
        } else {
            HuWinMesSet(wins[i], 0x4500, -1, -1);
        }
        HuWinPosSet(win, x, y + (s16)(i * 14 - 62));
        HuWinDispOn(win);
        HuAudFXPlay(0x2E8);
        for (j = 1; j < 4; j++) {
            HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
            HuPrcVSleep();
        }
    }
    HuWinKill(win);
    do {
        HuPrcVSleep();
    } while (!(D_800D5558_main[0] & (A_BUTTON | B_BUTTON)));
    for (i = 0; i < 10; i++) {
        HuWinDispOff(wins[i]);
    }
    HuAudFXPlay(0x2E9);
    for (i = 1; i <= 10; i++) {
        scale = 1.0f - sindf(i * 9.0f);
        espScaleSet(sprite, scale, scale);
        HuPrcVSleep();
    }
    for (i = 0; i < 10; i++) {
        HuWinKill(wins[i]);
    }
    espKill(sprite);
    HuSprAnimKill(anim);
}

void func_80108A68_option(void) {
    func_80108B34_option();
    func_80112060_option();
    D_80114770_option = omAddPrcObj(func_80108B58_option, 0x5000, 0x2000, 0);
}

void func_80108AAC_option(void) {
    func_80108B34_option();
    func_80112060_option();
    D_80114770_option = omAddPrcObj(func_8010A66C_option, 0x5000, 0x2000, 0);
}

void func_80108AF0_option(void) {
    func_80108B34_option();
    func_80112060_option();
    D_80114770_option = omAddPrcObj(func_8010C224_option, 0x5000, 0x2000, 0);
}

void func_80108B34_option(void) {
    func_8010F94C_option();
    func_8010FDF4_option();
}

const Vec D_80113A80_option = { 0.0f, 271.19f, 1191.11f };

const Vec D_80113A8C_option = { 0.0f, 228.72f, -550.0f };

const Vec D_80113A98_option = { 0.0f, 1.0f, 0.0f };

const Vec D_80113AA4_option = { 0.0f, 271.19f, 350.0f };

const Vec D_80113AB0_option = { -535.0f, 228.72f, -550.0f };

const Vec D_80113ABC_option = { 0.0f, 228.72f, 350.0f };

const Vec D_80113AC8_option = { -160.0f, 228.72f, 50.0f };

const Vec D_80113AD4_option = { 450.0f, 228.72f, 1191.11f };

const Vec D_80113AE0_option = { 535.0f, 228.72f, -550.0f };

const Vec D_80113AEC_option = { 160.0f, 228.72f, 50.0f };

const Vec D_80113AF8_option = { -450.0f, 228.72f, 1191.11f };

const Vec D_80113B04_option = { 0.0f, 410.0f, -550.0f };

const Vec D_80113B10_option = { 0.0f, 228.72f, 50.0f };

const Vec D_80113B1C_option = { 0.0f, 228.72f, 1191.11f };

void func_80108B58_option(void) {
    s32 selection;
    s32 active = 1;
    Vec pos, at;

    Hu3DBGColorSet(0, 0x40, 0x40);
    func_80112084_option();
    func_8010FB40_option(0, 9);
    func_8010FB40_option(1, 10);
    switch (omovlevtno) {
        case 0:
            func_8004A5C4_main(7);
            WipeCreateIn(11, 16);
            pos = D_80113A80_option;
            at = D_80113A8C_option;
            {
                Vec up = D_80113A98_option;
                func_80106508_option(&pos, &at, &up);
            }
            {
                Vec pos = D_80113AA4_option;
                Vec at = D_80113A8C_option;
                func_8010737C_option(&pos, &at, 45);
            }
            HuPrcSleep(45);
            break;
        case 1:
            func_8004A5C4_main(7);
            WipeColorSet(255, 255, 255);
            WipeCreateIn(11, 16);
            {
                Vec pos = D_80113AB0_option;
                Vec at = D_80113ABC_option;
                Vec up = D_80113A98_option;
                func_80106508_option(&pos, &at, &up);
            }
            {
                Vec pos = D_80113AC8_option;
                Vec at = D_80113AD4_option;
                func_80107AD4_option(&pos, &at, 46);
            }
            HuPrcSleep(46);
            {
                Vec pos = D_80113AA4_option;
                Vec at = D_80113A8C_option;
                func_80107758_option(&pos, &at, 45);
            }
            HuPrcSleep(45);
            break;
        case 2:
            func_8004A5C4_main(7);
            WipeColorSet(255, 255, 255);
            WipeCreateIn(11, 16);
            {
                Vec pos = D_80113AE0_option;
                Vec at = D_80113ABC_option;
                Vec up = D_80113A98_option;
                func_80106508_option(&pos, &at, &up);
            }
            {
                Vec pos = D_80113AEC_option;
                Vec at = D_80113AF8_option;
                func_80107AD4_option(&pos, &at, 46);
            }
            HuPrcSleep(46);
            {
                Vec pos = D_80113AA4_option;
                Vec at = D_80113A8C_option;
                func_80107758_option(&pos, &at, 45);
            }
            HuPrcSleep(45);
            break;
        case 3:
            WipeColorSet(255, 255, 255);
            WipeCreateIn(11, 16);
            {
                Vec pos = D_80113B04_option;
                Vec at = D_80113ABC_option;
                Vec up = D_80113A98_option;
                func_80106508_option(&pos, &at, &up);
            }
            {
                Vec pos = D_80113B10_option;
                Vec at = D_80113ABC_option;
                func_80106F88_option(&pos, &at, 50);
            }
            HuPrcSleep(50);
            {
                Vec pos = D_80113ABC_option;
                Vec at = D_80113B1C_option;
                func_8010737C_option(&pos, &at, 25);
            }
            HuPrcSleep(25);
            {
                Vec pos = D_80113ABC_option;
                Vec at = D_80113A8C_option;
                func_80107758_option(&pos, &at, 35);
            }
            HuPrcSleep(35);
            break;
        default:
            func_8004A5C4_main(7);
            WipeCreateIn(11, 16);
            {
                Vec pos = D_80113A80_option;
                Vec at = D_80113A8C_option;
                func_80107758_option(&pos, &at, 45);
            }
            HuPrcSleep(16);
            break;
    }
    selection = func_80109504_option();
    func_801133A0_option(0);
    switch (selection) {
        case 0:
            HuVecCopy3F(&pos, &D_801136F4_option);
            pos.y += 20.0f;
            HuVecCopy3F(&at, &D_80113700_option);
            at.y += 20.0f;
            HuAudFXPlay(0x2EB);
            func_801132AC_option(0, 0);
            func_801132E4_option(0, 0);
            func_80113300_option(0);
            func_80106F88_option(&pos, &at, 20);
            func_8010FFDC_option();
            WipeCreateOut(11, 20);
            HuPrcSleep(20);
            break;
        case 1:
            HuVecCopy3F(&pos, &D_8011370C_option);
            pos.z += 200.0f;
            HuVecCopy3F(&at, &D_80113718_option);
            func_80113338_option(9, 12, 0, 8, 0);
            HuAudFXPlay(0x2EB);
            func_8011331C_option(0, 6, 0);
            func_80113300_option(0);
            pos.z -= 200.0f;
            at.z -= 200.0f;
            func_80106F88_option(&pos, &at, 20);
            func_8010FFDC_option();
            WipeCreateOut(11, 20);
            HuAudSeqFadeOut(20);
            HuPrcSleep(20);
            break;
        case 2:
            HuVecCopy3F(&pos, &D_80113724_option);
            pos.z += 200.0f;
            HuVecCopy3F(&at, &D_80113730_option);
            func_80113338_option(10, 11, 0, 8, 0);
            HuAudFXPlay(0x2EB);
            func_8011331C_option(0, 7, 0);
            func_801132E4_option(0, 0);
            func_80113300_option(0);
            pos.z -= 200.0f;
            at.z -= 200.0f;
            func_80106F88_option(&pos, &at, 20);
            func_8010FFDC_option();
            WipeCreateOut(11, 20);
            HuAudSeqFadeOut(20);
            HuPrcSleep(20);
            break;
        case 3:
        case 4:
            HuVecCopy3F(&pos, &D_8011373C_option);
            HuVecCopy3F(&at, &D_80113748_option);
            func_80106F88_option(&pos, &at, 30);
            HuPrcSleep(20);
            func_80106B78_option();
            HuAudFXPlay(0x2E1);
            func_801132AC_option(1, 0);
            func_801132E4_option(1, 0);
            func_80113300_option(1);
            func_80106F88_option(&pos, &at, 20);
            func_8010FFDC_option();
            WipeColorSet(255, 255, 255);
            WipeCreateOut(11, 20);
            HuAudSeqFadeOut(20);
            HuPrcSleep(20);
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            selection = 9;
            break;
    }
    active = selection;
    func_8010FA28_option();
    func_8011239C_option();
    HuWinAllKill();
    omOvlKill();
    switch (active) {
        case 0:
            omOvlHisChg(0, 0x7B, 3, 0x91);
            omOvlCallEx(0x7B, 6, 0x91);
            break;
        case 1:
            omOvlGotoEx(0x7B, 4, 0x91);
            break;
        case 2:
            omOvlGotoEx(0x7B, 5, 0x91);
            break;
        case 3:
            omOvlReturnEx(1);
            omOvlHisChg(0, 0x77, 3, 0x91);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            omOvlReturnEx(1);
            break;
    }
    omDelPrcObj(D_80114770_option);
    while (1) {
        HuPrcVSleep();
    }
}

s32 func_80109504_option(void) {
    s32 selection = 0;
    s32 buttons;
    s32 result;
    Vec at;
    s32 x, y;

    if (func_800465E8_main()) {
        func_800465F4_main(1);
        func_801133BC_option(0, 0x4E00);
        func_80113490_option(0);
        func_80113408_option(0, 0x4E02);
    } else {
        func_801133BC_option(0, 0x4E02);
    }
    func_80113384_option(0);
    func_8010A3E8_option(selection, 0);
    while (1) {
        buttons = D_800D5558_main[0];
        buttons |= func_801130E8_option(0);
        if (buttons & 0x8000) {
            result = func_80109D04_option(selection, buttons);
            if (result != -1) {
                selection = result;
                break;
            }
        } else if (buttons & 0xF00) {
            selection = func_80109EF4_option(selection, buttons);
        } else if (buttons & 0x4000) {
            func_801133A0_option(0);
            func_80113440_option(0);
            switch (selection) {
                case 0:
                case 1:
                    HuVecCopy3F(&at, &D_80113508_option[1]);
                    func_80107758_option(&D_80113508_option[0], &at, 30);
                    HuPrcSleep(30);
                    break;
                case 2:
                    HuVecCopy3F(&at, &D_80113508_option[1]);
                    func_80107758_option(&D_80113508_option[0], &at, 30);
                    HuPrcSleep(30);
                    break;
                case 9:
                default:
                    break;
            }
            selection = 3;
            func_80109908_option(0.0f, 100.0f, 1275.0f, &x, &y);
            func_80112028_option(0, x, y);
            func_80113424_option(0);
            func_80113408_option(0, 0x4E03);
            func_80113384_option(0);
        }
        HuPrcVSleep();
    }
    func_801133EC_option(0);
    return selection;
}

void func_801096B8_option(s32 arg0, s32 arg1, s32 arg2) {
    D_80114778_option[0] = arg1;
    D_80114778_option[1] = arg2;
    func_80112028_option(arg0, 160, arg2);
}

void func_801096E4_option(s32 arg0) {
    if (++D_80114778_option[3] >= 21) {
        D_80114778_option[3] = 0;
    }
    D_80114778_option[2] = 0;
    func_80112028_option(arg0, D_80114778_option[0], D_80114778_option[1]);
}

void func_80109730_option(Vec *pos, Vec *at, Vec *up, f32 fov, Vec *point, f32 *screenX, f32 *screenY) {
    f32 mtx[4][4];
    f32 dx, dy, dz;
    f32 x, y, z;

    HuLookAtF(mtx, pos->x, pos->y, pos->z, at->x, at->y, at->z, up->x, up->y, up->z);
    dx = point->x;
    dy = point->y;
    dz = point->z;
    dx -= pos->x;
    dy -= pos->y;
    dz -= pos->z;
    x = dx * mtx[0][0] + dy * mtx[1][0] + dz * mtx[2][0];
    y = dx * mtx[0][1] + dy * mtx[1][1] + dz * mtx[2][1];
    z = dx * mtx[0][2] + dy * mtx[1][2] + dz * mtx[2][2];
    fov /= 2.0f;
    dx = sindf(fov) / cosdf(fov) * z * (4.0f / 3.0f);
    dy = sindf(fov) / cosdf(fov) * z;
    x = x * (160.0f / -dx) + 160.0f;
    *screenX = x;
    y = y * (120.0f / dy) + 120.0f;
    *screenY = y;
}

void func_80109908_option(f32 x, f32 y, f32 z, s32 *screenX, s32 *screenY) {
    Vec pos;
    f32 px, py;
    HuCamera *camera;

    camera = gCameraList;
    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80109730_option(&camera->pos, &camera->at, &camera->up, camera->fov, &pos, &px, &py);
    *screenX = px;
    *screenY = py;
}

void func_8010998C_option(Vec *camPos, Vec *camAt, Vec *camUp, f32 x, f32 y, f32 z, s32 *screenX, s32 *screenY) {
    Vec pos;
    f32 px, py;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80109730_option(camPos, camAt, camUp, gCameraList->fov, &pos, &px, &py);
    *screenX = px;
    *screenY = py;
}

void func_80109A0C_option(s32 slot, Vec *start, Vec *end, s32 duration) {
    f32 startPos[2], endPos[2];
    s32 x, y;
    s32 i;
    f32 t;

    for (i = 0; i <= duration; i++) {
        func_80109908_option(start->x, start->y, start->z, &x, &y);
        startPos[0] = x;
        startPos[1] = y;
        func_80109908_option(end->x, end->y, end->z, &x, &y);
        endPos[0] = x;
        endPos[1] = y;
        t = (1.0f / duration) * i;
        func_80112028_option(slot, t * (endPos[0] - startPos[0]) + startPos[0], t * (endPos[1] - startPos[1]) + startPos[1]);
        HuPrcVSleep();
    }
    func_80112028_option(slot, endPos[0], endPos[1]);
}

void func_80109B7C_option(s32 index, s32 startX, s32 startY, s32 endX, s32 endY, s32 duration) {
    s32 i;
    f32 t;

    for (i = 0; i <= duration; i++) {
        t = (1.0f / duration) * i;
        func_80112028_option(index, startX + t * (endX - startX), startY + t * (endY - startY));
        HuPrcVSleep();
    }
    func_80112028_option(index, endX, endY);
}

void func_80109CB0_option(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 val1 = 0xA0;
    s32 val2 = 0x78;

    switch (arg0) {
        case 0:
            val1 = 0xA0;
            val2 = 0x50;
            break;
        case 1:
        case 2:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 3:
        case 4:
            val1 = 0xA0;
            val2 = 0x6E;
            break;
        case 5:
        default:
            break;
    }

    *arg1 = val1;
    *arg2 = val2;
}

const Vec D_80113B90_option = { 0.0f, 430.0f, -150.0f };

const Vec D_80113B9C_option = { 0.0f, 430.0f, -550.0f };

const Vec D_80113BA8_option = { -535.0f, 128.72f, -150.0f };

const Vec D_80113BB4_option = { -535.0f, 78.72f, -550.0f };

const Vec D_80113BC0_option = { 535.0f, 128.72f, -150.0f };

const Vec D_80113BCC_option = { 535.0f, 78.72f, -550.0f };

s32 func_80109D04_option(s32 selection, s32 buttons) {
    switch (selection) {
        case 0: {
            Vec pos;
            Vec at;
            func_801133A0_option(0);
            func_80113440_option(0);
            pos = D_80113B90_option;
            at = D_80113B9C_option;
            func_8010737C_option(&pos, &at, 30);
            func_80113338_option(9, 11, 0, 8, 0);
            func_80113338_option(10, 12, 0, 8, 0);
            HuPrcSleep(30);
            break;
        }
        case 1: {
            Vec pos;
            Vec at;
            func_801133A0_option(0);
            func_80113440_option(0);
            pos = D_80113BA8_option;
            at = D_80113BB4_option;
            func_8010737C_option(&pos, &at, 20);
            HuPrcSleep(20);
            break;
        }
        case 2: {
            Vec pos;
            Vec at;
            func_801133A0_option(0);
            func_80113440_option(0);
            pos = D_80113BC0_option;
            at = D_80113BCC_option;
            func_8010737C_option(&pos, &at, 20);
            HuPrcSleep(20);
            break;
        }
        case 3:
            func_801133A0_option(0);
            func_80113408_option(0, 0x4E04);
            if (func_8011345C_option(0)) {
                func_80113408_option(0, 0x4E03);
                func_80113384_option(0);
                return -1;
            }
            selection = 3;
            break;
        case 9:
        default:
            break;
    }
    return selection;
}

s32 func_80109EF4_option(s32 selection, s32 buttons) {
    Vec up;
    s32 x, y, endX, endY;

    up = D_80113A98_option;

    switch (selection) {
        case 0:
            if (buttons & 0x200) {
                selection = 1;
                func_80107758_option(&D_801137CC_option[0], &D_801137CC_option[1], 7);
                func_80113368_option(0, &x, &y);
                func_8010998C_option(&D_801137CC_option[0], &D_801137CC_option[1], &up, D_8011376C_option[1].x, D_8011376C_option[1].y, D_8011376C_option[1].z, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 7);
                func_80113408_option(0, 0x4e01);
            } else if (buttons & 0x100) {
                selection = 2;
                func_80107758_option(&D_801137E4_option[0], &D_801137E4_option[1], 7);
                func_80113368_option(0, &x, &y);
                func_8010998C_option(&D_801137E4_option[0], &D_801137E4_option[1], &up, D_8011376C_option[2].x, D_8011376C_option[2].y, D_8011376C_option[2].z, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 7);
                func_80113408_option(0, 0x4e01);
            }
            break;
        case 1:
            if (buttons & 0x200) {
                selection = 3;
                func_80107758_option(&D_801137B4_option[0], &D_801137B4_option[1], 20);
                func_801133A0_option(0);
                func_80113440_option(0);
                HuPrcSleep(20);
                func_80109908_option(D_8011376C_option[3].x, D_8011376C_option[3].y, D_8011376C_option[3].z, &x, &y);
                func_80112028_option(0, x, y);
                func_80113258_option(0);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4e03);
            } else if (buttons & 0x100) {
                selection = 0;
                func_80107758_option(&D_8011379C_option[0], &D_8011379C_option[1], 7);
                func_80113368_option(0, &x, &y);
                func_8010998C_option(&D_8011379C_option[0], &D_8011379C_option[1], &up, D_8011376C_option[0].x, D_8011376C_option[0].y, D_8011376C_option[0].z, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 7);
                func_80113408_option(0, 0x4e02);
            }
            break;
        case 2:
            if (buttons & 0x200) {
                selection = 0;
                func_80107758_option(&D_8011379C_option[0], &D_8011379C_option[1], 7);
                func_80113368_option(0, &x, &y);
                func_8010998C_option(&D_8011379C_option[0], &D_8011379C_option[1], &up, D_8011376C_option[0].x, D_8011376C_option[0].y, D_8011376C_option[0].z, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 7);
                func_80113408_option(0, 0x4e02);
            } else if (buttons & 0x100) {
                selection = 3;
                func_80107758_option(&D_801137B4_option[0], &D_801137B4_option[1], 20);
                func_801133A0_option(0);
                func_80113440_option(0);
                HuPrcSleep(20);
                func_80109908_option(D_8011376C_option[3].x, D_8011376C_option[3].y, D_8011376C_option[3].z, &x, &y);
                func_80112028_option(0, x, y);
                func_80113258_option(0);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4e03);
            }
            break;
        case 3:
            if (buttons & 0x200) {
                selection = 2;
                func_80107758_option(&D_801137E4_option[0], &D_801137E4_option[1], 20);
                func_801133A0_option(0);
                func_80113440_option(0);
                func_8011323C_option(0);
                HuPrcSleep(20);
                func_80109908_option(D_8011376C_option[2].x, D_8011376C_option[2].y, D_8011376C_option[2].z, &x, &y);
                func_80112028_option(0, x, y);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4e01);
            } else if (buttons & 0x100) {
                selection = 1;
                func_80107758_option(&D_801137CC_option[0], &D_801137CC_option[1], 20);
                func_801133A0_option(0);
                func_80113440_option(0);
                func_8011323C_option(0);
                HuPrcSleep(20);
                func_80109908_option(D_8011376C_option[1].x, D_8011376C_option[1].y, D_8011376C_option[1].z, &x, &y);
                func_80112028_option(0, x, y);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4e01);
            }
            break;
        case 4:
        default:
            break;
    }
    return selection;
}

void func_8010A3E8_option(s32 selection, s32 arg1) {
    s32 index = 0;
    s32 x, y;

    switch (selection) {
        case 0:
            index = 0;
            break;
        case 1:
            index = 1;
            break;
        case 2:
            index = 2;
            break;
        case 3:
            index = 3;
            break;
    }
    func_80109908_option(D_8011376C_option[index].x, D_8011376C_option[index].y, D_8011376C_option[index].z, &x, &y);
    func_80112028_option(0, x, y);
}

s32 func_8010A498_option(void) {
    Vec pos, at;
    s32 selection = 0;
    s32 buttons;
    s32 result;

    func_80105F08_option(41.539f);
    func_801133BC_option(0, 0x4E05);
    func_80113490_option(0);
    func_80113408_option(0, 0x4E06);
    func_80113384_option(0);
    func_8010B654_option(0, 0);
    while (1) {
        buttons = D_800D5558_main[0];
        buttons |= func_801130E8_option(0);
        if (buttons & 0x8000) {
            result = func_8010AF54_option(selection, buttons);
            if (result != -1) {
                selection = result;
                break;
            }
        } else if (buttons & 0xF00) {
            selection = func_8010A940_option(selection, buttons);
        } else if (buttons & 0x4000) {
            func_801133A0_option(0);
            func_80113440_option(0);
            switch (selection) {
                case 0:
                case 1:
                case 2:
                    selection = 4;
                    HuVecCopy3F(&pos, &D_80113580_option[4][0]);
                    HuVecCopy3F(&at, &D_80113580_option[4][1]);
                    func_80107758_option(&pos, &at, 20);
                    HuPrcSleep(20);
                    break;
                case 3:
                    selection = 5;
                    HuVecCopy3F(&pos, &D_80113580_option[5][0]);
                    HuVecCopy3F(&at, &D_80113580_option[5][1]);
                    func_80107758_option(&pos, &at, 20);
                    HuPrcSleep(20);
                    break;
                case 4:
                case 5:
                default:
                    break;
            }
            func_80113424_option(0);
            func_80113408_option(0, 0x4E0B);
            func_80113384_option(0);
        }
        func_8010B654_option(selection, buttons);
        HuPrcVSleep();
    }
    func_801133EC_option(0);
    return selection;
}

void func_8010A66C_option(void) {
    Vec pos, at;
    s32 selection;
    s32 result;

    Hu3DBGColorSet(0, 64, 64);
    func_801123D8_option();
    HuAudSeqPlay(0x4A);
    WipeCreateIn(0xB, 16);
    HuPrcSleep(16);
    selection = func_8010A498_option();
    func_801133A0_option(0);
    switch (selection) {
        case 4:
            HuVecCopy3F(&pos, &D_801137FC_option);
            HuVecCopy3F(&at, &D_80113808_option);
            pos.z -= 200.0f;
            func_80106F88_option(&pos, &at, 20);
            HuPrcSleep(20);
            HuAudFXPlay(0x2EB);
            func_801132AC_option(1, 0);
            func_801132E4_option(1, 0);
            func_80113300_option(1);
            pos.z += 200.0f;
            func_80106F88_option(&pos, &at, 20);
            goto fadeOut;
        case 5:
            HuVecCopy3F(&pos, &D_80113814_option);
            HuVecCopy3F(&at, &D_80113820_option);
            pos.z -= 200.0f;
            func_80106F88_option(&pos, &at, 20);
            HuPrcSleep(20);
            HuAudFXPlay(0x2EB);
            func_801132AC_option(1, 0);
            func_8011331C_option(1, 12, 0);
            func_801132E4_option(1, 0);
            func_80113300_option(1);
            pos.z += 200.0f;
            func_80106F88_option(&pos, &at, 20);
        case 0:
        case 1:
        case 2:
        case 3:
        fadeOut:
            result = selection;
            func_8010FFDC_option();
            WipeColorSet(255, 255, 255);
            WipeCreateOut(0xB, 20);
            HuAudSeqFadeOut(20);
            HuPrcSleep(20);
            break;
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            selection = 9;
            break;
    }
    result = selection;
    func_80112A44_option();
    HuWinAllKill();
    omOvlKill();
    switch (result) {
        case 4:
            omOvlGotoEx(0x7B, 1, 0x91);
            break;
        case 5:
            omOvlGotoEx(0x7B, 2, 0x91);
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            omOvlReturnEx(1);
            break;
    }
    omDelPrcObj(D_80114770_option);
    while (1) {
        HuPrcVSleep();
    }
}

void func_8010A8DC_option(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 val1 = 0xA0;
    s32 val2 = 0x78;

    switch (arg0) {
        case 0:
            if (!(D_800D09A8_main.flags & 1)) {
                val1 = 0xE0;
                val2 = 0x38;
            } else {
                val1 = 0xB8;
                val2 = 0x38;
            }
            break;
        case 1:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 2:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 3:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 4:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 5:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 6:
        default:
            break;
    }

    *arg1 = val1;
    *arg2 = val2;
}

s32 func_8010A940_option(s32 selection, s32 buttons) {
    Vec pos, at;
    Vec(*camera)[2];
    s32 x, y, endX, endY;
    switch (selection) {
        case 0:
            if (buttons & 0x200) {
                selection = 2;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[2][0]);
                HuVecCopy3F(&at, &camera[2][1]);
                func_80107758_option(&pos, &at, 8);
                func_80113258_option(6);
                func_80113258_option(7);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(2, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 8);
                func_80113408_option(0, 0x4E0A);
            } else if (buttons & 0x100) {
                selection = 3;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[3][0]);
                HuVecCopy3F(&at, &camera[3][1]);
                func_80107758_option(&pos, &at, 8);
                func_80113258_option(6);
                func_80113258_option(7);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(3, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 8);
                func_80113408_option(0, 0x4E09);
            }
            break;
        case 2:
            if (buttons & 0x200) {
                selection = 4;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[4][0]);
                HuVecCopy3F(&at, &camera[4][1]);
                func_80107758_option(&pos, &at, 20);
                func_801133A0_option(0);
                func_80113440_option(0);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(4, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 20);
                HuPrcSleep(12);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4E0B);
            } else if (buttons & 0x100) {
                selection = 0;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[0][0]);
                HuVecCopy3F(&at, &camera[0][1]);
                func_80107758_option(&pos, &at, 8);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(0, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 8);
                func_80113408_option(0, 0x4E06);
                func_8011323C_option(6);
                func_8011323C_option(7);
            }
            break;
        case 3:
            if (buttons & 0x200) {
                selection = 0;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[0][0]);
                HuVecCopy3F(&at, &camera[0][1]);
                func_80107758_option(&pos, &at, 8);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(0, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 8);
                func_80113408_option(0, 0x4E06);
                func_8011323C_option(6);
                func_8011323C_option(7);
            } else if (buttons & 0x100) {
                selection = 5;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[5][0]);
                HuVecCopy3F(&at, &camera[5][1]);
                func_80107758_option(&pos, &at, 20);
                func_801133A0_option(0);
                func_80113440_option(0);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(5, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 20);
                HuPrcSleep(12);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4E0B);
            }
            break;
        case 4:
            if (buttons & 0x200) {
                selection = 5;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[5][0]);
                HuVecCopy3F(&at, &camera[5][1]);
                func_80107758_option(&pos, &at, 8);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(5, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 8);
                func_80113408_option(0, 0x4E0B);
            } else if (buttons & 0x100) {
                selection = 2;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[2][0]);
                HuVecCopy3F(&at, &camera[2][1]);
                func_80107758_option(&pos, &at, 20);
                func_801133A0_option(0);
                func_80113440_option(0);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(2, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 20);
                HuPrcSleep(12);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4E0A);
            }
            break;
        case 5:
            if (buttons & 0x200) {
                selection = 3;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[3][0]);
                HuVecCopy3F(&at, &camera[3][1]);
                func_80107758_option(&pos, &at, 20);
                func_801133A0_option(0);
                func_80113440_option(0);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(3, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 20);
                HuPrcSleep(12);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4E09);
            } else if (buttons & 0x100) {
                selection = 4;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[4][0]);
                HuVecCopy3F(&at, &camera[4][1]);
                func_80107758_option(&pos, &at, 8);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(4, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 8);
                func_80113408_option(0, 0x4E0B);
            }
            break;
        case 1:
        default:
            break;
    }
    return selection;
}

s32 func_8010AF54_option(s32 selection, s32 buttons) {
    s32 result = -1;
    s32 choice;
    s32 model;

    switch (selection) {
        case 0: {
            Vec camera[2] = { { 0.0f, 264.9f, 164.26999f }, { 0.0f, 184.59999f, -138.7f } };

            func_80113258_option(6);
            func_80113258_option(7);
            func_801133A0_option(0);
            func_80113440_option(0);
            func_80106F88_option(&camera[0], &camera[1], 8);
            HuPrcSleep(8);
            func_801133EC_option(0);
            do {
                if (!(D_800D09A8_main.flags & 1)) {
                    func_801133BC_option(0, 0x4E07);
                    func_80113408_option(0, 0x4E07);
                    choice = func_8011345C_option(0);
                    if (choice == 0) {
                        func_801133A0_option(0);
                        HuPrcVSleep();
                        D_800D09A8_main.flags |= 1;
                        func_80000F30_main(1);
                        RepeatVibrator(0, 5, 0, 5);
                        func_80050CFC_main();
                        func_80113440_option(0);
                        func_801133EC_option(0);
                        func_80113338_option(8, 11, 0, 8, 0);
                        func_801132C8_option(21, 1);
                        func_801132E4_option(21, 0);
                        func_80113300_option(8);
                        func_80113338_option(8, 10, 0, 8, 2);
                        func_801132C8_option(4, 7);
                        func_80113300_option(4);
                        func_8011331C_option(4, 17, 0);
                        func_801132E4_option(4, 40);
                        func_801132AC_option(4, 4);
                        HuAudFXPlay(0x2F5);
                        func_8011331C_option(5, 19, 0);
                        func_801132C8_option(5, 7);
                        func_801132E4_option(5, 0);
                        func_80113300_option(5);
                        func_8011331C_option(5, 20, 2);
                        func_801132AC_option(5, 2);
                    }
                } else {
                    func_801133BC_option(0, 0x4E08);
                    func_80113408_option(0, 0x4E08);
                    choice = func_8011345C_option(0);
                    if (choice == 0) {
                        func_801133A0_option(0);
                        HuPrcVSleep();
                        D_800D09A8_main.flags &= ~1;
                        func_80000F30_main(0);
                        RepeatVibrator(0, 5, 0, 5);
                        func_80050CFC_main();
                        func_801133EC_option(0);
                        func_80113338_option(8, 11, 0, 2, 0);
                        func_801132C8_option(21, 1);
                        func_801132E4_option(21, 0);
                        func_80113300_option(8);
                        func_80113338_option(8, 10, 0, 8, 2);
                        func_801132C8_option(5, 7);
                        func_80113300_option(5);
                        func_8011331C_option(5, 19, 0);
                        func_801132E4_option(5, 40);
                        func_801132AC_option(5, 4);
                        HuAudFXPlay(0x2F5);
                        func_8011331C_option(4, 17, 0);
                        func_801132C8_option(4, 7);
                        func_801132E4_option(4, 0);
                        func_80113300_option(4);
                        func_8011331C_option(4, 18, 2);
                        func_801132AC_option(4, 2);
                    }
                }
                func_8010B654_option(selection, 0);
            } while (choice == 0);
            func_80113408_option(0, 0x4E06);
            {
                Vec camera[2] = { { 0.0f, 264.9f, 364.27f }, { 0.0f, 184.59999f, 61.300003f } };

                func_80113440_option(0);
                func_80106F88_option(&camera[0], &camera[1], 8);
            }
            HuPrcSleep(8);
            func_80113384_option(0);
            func_80113424_option(0);
            func_8011323C_option(6);
            func_8011323C_option(7);
            return result;
        }
        case 1:
            return result;
        case 2:
            func_801133A0_option(0);
            func_80106F88_option(&D_8011382C_option[0], &D_8011382C_option[1], 8);
            HuAudFXPlay(0x2EA);
            func_801132E4_option(2, 0);
            func_801132C8_option(2, 7);
            func_801132AC_option(2, 0);
            func_80113300_option(2);
            func_80113440_option(0);
            func_8004A9DC_main(0x60);
            func_8010E8E0_option();
            func_8004A9DC_main(0x7F);
            func_80106F88_option(&D_80113844_option[0], &D_80113844_option[1], 8);
            func_801132E4_option(2, 40);
            func_801132C8_option(2, 7);
            func_801132AC_option(2, 4);
            model = func_80113218_option(2);
            while (Hu3DData[(s16)model].motTime != 0.0f) {
                HuPrcVSleep();
            }
            func_80113424_option(0);
            func_80113384_option(0);
            break;
        case 3:
            func_80113440_option(0);
            func_801133A0_option(0);
            func_80106F88_option(&D_8011385C_option[0], &D_8011385C_option[1], 8);
            HuAudFXPlay(0x2EA);
            func_801132E4_option(3, 0);
            func_801132C8_option(3, 7);
            func_801132AC_option(3, 0);
            func_80113300_option(3);
            func_8010F138_option();
            HuAudSeqPlay(0x4A);
            func_80106F88_option(&D_80113874_option[0], &D_80113874_option[1], 8);
            func_801132E4_option(3, 40);
            func_801132C8_option(3, 7);
            func_801132AC_option(3, 4);
            model = func_80113218_option(3);
            while (Hu3DData[(s16)model].motTime != 0.0f) {
                HuPrcVSleep();
            }
            func_80113424_option(0);
            func_80113384_option(0);
            break;
        case 4:
        case 5:
            func_801133A0_option(0);
            func_80113408_option(0, 0x4E0C);
            if (func_8011345C_option(0) != 0) {
                func_80113408_option(0, 0x4E0B);
                func_80113384_option(0);
                return -1;
            }
            result = selection;
            break;
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            result = selection;
            break;
    }
    return result;
}

void func_8010B654_option(s32 selection, s32 buttons) {
    s32 x, y;

    func_8010A8DC_option(selection, &x, &y);
    func_801096B8_option(0, x, y);
    func_801096E4_option(0);
}

s32 func_8010B68C_option(s32 selection, s32 buttons) {
    Vec pos, at, up;
    s32 x, y, endX, endY;

    up = D_80113A98_option;
    switch (selection) {
        case 0:
            if (buttons & 0x200) {
                selection = 1;
            } else if (buttons & 0x100) {
                selection = 2;
            }
            break;
        case 1:
            if (buttons & 0x200) {
                selection = 3;
                HuVecCopy3F(&pos, &D_80113694_option[0]);
                HuVecCopy3F(&at, &D_801136AC_option[1]);
                func_80107758_option(&pos, &at, 30);
                func_801133A0_option(0);
                func_80113440_option(0);
                HuPrcSleep(30);
                func_80109908_option(D_801138A4_option.x, D_801138A4_option.y, D_801138A4_option.z, &x, &y);
                func_80112028_option(0, x, y);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4e12);
            } else if (buttons & 0x100) {
                selection = 2;
                func_80107758_option(&D_80113694_option[0], &D_80113694_option[1], 7);
                func_80113368_option(0, &x, &y);
                func_8010998C_option(&D_80113694_option[0], &D_80113694_option[1], &up, D_80113898_option.x, D_80113898_option.y, D_80113898_option.z, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 7);
                func_80113408_option(0, 0x4e0e);
            }
            break;
        case 2:
            if (buttons & 0x200) {
                selection = 1;
                func_80107758_option(&D_8011367C_option[0], &D_8011367C_option[1], 7);
                func_80113368_option(0, &x, &y);
                func_8010998C_option(&D_8011367C_option[0], &D_8011367C_option[1], &up, D_8011388C_option.x, D_8011388C_option.y, D_8011388C_option.z, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 7);
                func_80113408_option(0, 0x4e10);
            } else if (buttons & 0x100) {
                selection = 3;
                HuVecCopy3F(&pos, &D_80113694_option[0]);
                HuVecCopy3F(&at, &D_801136AC_option[1]);
                func_80107758_option(&pos, &at, 30);
                func_801133A0_option(0);
                func_80113440_option(0);
                HuPrcSleep(30);
                func_80109908_option(D_801138A4_option.x, D_801138A4_option.y, D_801138A4_option.z, &x, &y);
                func_80112028_option(0, x, y);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4e12);
            }
            break;
        case 3:
            if (buttons & 0x200) {
                selection = 2;
                func_80107758_option(&D_80113694_option[0], &D_80113694_option[1], 30);
                func_801133A0_option(0);
                func_80113440_option(0);
                HuPrcSleep(30);
                func_80109908_option(D_80113898_option.x, D_80113898_option.y, D_80113898_option.z, &x, &y);
                func_80112028_option(0, x, y);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4e0e);
            } else if (buttons & 0x100) {
                selection = 1;
                func_80107758_option(&D_8011367C_option[0], &D_8011367C_option[1], 30);
                func_801133A0_option(0);
                func_80113440_option(0);
                HuPrcSleep(30);
                func_80109908_option(D_8011388C_option.x, D_8011388C_option.y, D_8011388C_option.z, &x, &y);
                func_80112028_option(0, x, y);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4e10);
            }
            break;
        case 4:
        default:
            break;
    }
    return selection;
}

s32 func_8010BACC_option(s32 selection, s32 arg1) {
    Vec pos, at;
    s32 result = -1;
    s32 choice;
    s32 model;

    switch (selection) {
        case 0:
            break;
        case 1:
            func_801133A0_option(0);
            HuAudFXPlay(0x2E6);
            func_80113338_option(8, 12, 0, 8, 2);
            func_801132E4_option(4, 0);
            func_801132C8_option(4, 7);
            func_80113300_option(4);
            func_80113408_option(0, 0x4E11);
            choice = func_8011345C_option(0);
            if (choice == 0) {
                HuVecCopyXYZ(&pos, -195.0f, 160.0f, -595.0f);
                HuVecCopyXYZ(&at, -195.0f, 160.0f, -680.0f);
                func_80106F88_option(&pos, &at, 20);
                func_80113440_option(0);
                HuPrcSleep(20);
                func_8010C3E4_option(0xE002E, 160, 120);
            } else if (choice == 1) {
                HuVecCopyXYZ(&pos, -195.0f, 160.0f, -595.0f);
                HuVecCopyXYZ(&at, -195.0f, 160.0f, -680.0f);
                func_80106F88_option(&pos, &at, 20);
                func_80113440_option(0);
                HuPrcSleep(20);
                func_8010D5B0_option(0xE002E, 160, 120);
            }
            func_80113408_option(0, 0x4E10);
            func_80106F88_option(&D_8011367C_option[0], &D_8011367C_option[1], 30);
            func_80113338_option(8, 10, 0, 8, 2);
            func_801132C8_option(4, 7);
            func_801132AC_option(4, 4);
            HuPrcSleep(30);
            model = func_80113218_option(4);
            while (Hu3DData[(s16)model].motTime != 0.0f) {
                HuPrcVSleep();
            }
            func_80113424_option(0);
            func_80113384_option(0);
            break;
        case 2:
            func_801133A0_option(0);
            HuAudFXPlay(0x2E6);
            func_80113338_option(9, 12, 0, 8, 2);
            func_801132E4_option(5, 0);
            func_801132C8_option(5, 7);
            func_80113300_option(5);
            func_80113408_option(0, 0x4E0F);
            if (func_8011345C_option(0) == 0) {
                HuVecCopyXYZ(&pos, 195.0f, 160.0f, -595.0f);
                HuVecCopyXYZ(&at, 195.0f, 160.0f, -665.0f);
                func_80106F88_option(&pos, &at, 20);
                func_80113440_option(0);
                HuPrcSleep(20);
                func_80107F50_option(0xE002D, 160, 120);
            }
            func_80113408_option(0, 0x4E0E);
            func_80106F88_option(&D_80113694_option[0], &D_80113694_option[1], 30);
            func_80113338_option(9, 11, 0, 8, 2);
            func_801132C8_option(5, 7);
            func_801132AC_option(5, 4);
            HuPrcSleep(30);
            model = func_80113218_option(5);
            while (Hu3DData[(s16)model].motTime != 0.0f) {
                HuPrcVSleep();
            }
            func_80113424_option(0);
            func_80113384_option(0);
            break;
        case 3:
            func_801133A0_option(0);
            func_80113408_option(0, 0x4E13);
            if (func_8011345C_option(0) == 0) {
                result = 3;
            } else {
                switch (selection) {
                    case 0:
                    default:
                        break;
                    case 1:
                        func_80113408_option(0, 0x4E10);
                        break;
                    case 2:
                        func_80113408_option(0, 0x4E0E);
                        break;
                    case 3:
                        func_80113408_option(0, 0x4E12);
                        break;
                }
                func_80113384_option(0);
                result = -1;
            }
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            result = 4;
            break;
    }
    return result;
}

void func_8010BFA4_option(s32 selection, s32 buttons) {
    s32 x = 160;
    s32 y = 120;

    switch (selection) {
        case 0:
            break;
        case 1:
            func_80109908_option(D_8011388C_option.x, D_8011388C_option.y, D_8011388C_option.z, &x, &y);
            break;
        case 2:
            func_80109908_option(D_80113898_option.x, D_80113898_option.y, D_80113898_option.z, &x, &y);
            break;
        case 3:
            func_80109908_option(D_801138A4_option.x, D_801138A4_option.y, D_801138A4_option.z, &x, &y);
            break;
    }
    func_801096B8_option(0, x, y);
    func_801096E4_option(0);
}

s32 func_8010C04C_option(void) {
    s32 x, y;
    s32 buttons;
    s32 selection;
    s32 next;

    func_801133BC_option(0, 0x4E0D);
    func_80113490_option(0);
    func_80113408_option(0, 0x4E10);
    selection = 1;
    func_80107758_option(&D_8011367C_option[0], &D_8011367C_option[1], 20);
    HuPrcSleep(20);
    func_80109908_option(D_8011388C_option.x, D_8011388C_option.y, D_8011388C_option.z, &x, &y);
    func_80112028_option(0, x, y);
    func_80113384_option(0);
    func_8010BFA4_option(1, 0);
    {
        Vec pos, at;
        while (1) {
            buttons = D_800D5558_main[0];
            buttons |= func_801130E8_option(0);
            if (buttons & 0x8000) {
                next = func_8010BACC_option(selection, buttons);
                if (next != -1) {
                    selection = next;
                    break;
                }
            } else if (buttons & 0xF00) {
                selection = func_8010B68C_option(selection, buttons);
            } else if (buttons & 0x4000) {
                func_801133A0_option(0);
                func_80113440_option(0);
                switch (selection) {
                    case 0:
                    case 1:
                    case 2:
                        selection = 3;
                        HuVecCopy3F(&pos, &D_801136AC_option[0]);
                        HuVecCopy3F(&at, &D_801136AC_option[1]);
                        func_80107758_option(&pos, &at, 20);
                        HuPrcSleep(20);
                        break;
                    case 3:
                    default:
                        selection = 3;
                        break;
                }
                func_80113424_option(0);
                func_80113408_option(0, 0x4E12);
                func_80113384_option(0);
            }
            func_8010BFA4_option(selection, buttons);
            HuPrcVSleep();
        }
    }
    func_801133EC_option(0);
    return selection;
}

void func_8010C224_option(void) {
    Vec pos, at;
    s32 selection;
    s32 result;

    Hu3DBGColorSet(0, 64, 64);
    func_80112B08_option();
    func_8004A9DC_main(0x60);
    WipeCreateIn(0xB, 16);
    HuPrcSleep(16);
    selection = func_8010C04C_option();
    func_801133A0_option(0);
    switch (selection) {
        case 3:
            HuVecCopy3F(&pos, &D_801138B0_option);
            pos.z -= 200.0f;
            pos.y -= 40.0f;
            HuVecCopy3F(&at, &D_801138BC_option);
            at.y -= 40.0f;
            HuAudFXPlay(0x2EB);
            func_801132E4_option(1, 0);
            func_801132C8_option(1, 7);
            func_80113300_option(1);
            pos.z += 200.0f;
            func_80106F88_option(&pos, &at, 20);
            result = selection;
            func_8010FFDC_option();
            WipeColorSet(255, 255, 255);
            WipeCreateOut(0xB, 20);
            func_8004A9DC_main(0x7F);
            HuPrcSleep(20);
            break;
        case 0:
        case 1:
        case 2:
        case 4:
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            selection = 9;
            break;
    }
    result = selection;
    func_80112E14_option();
    HuWinAllKill();
    omOvlKill();
    switch (result) {
        case 3:
            omOvlReturnEx(1);
            break;
        default:
            omOvlReturnEx(1);
            break;
    }
    omDelPrcObj(D_80114770_option);
    while (1) {
        HuPrcVSleep();
    }
}

void func_8010C3E4_option(s32 animFile, s16 x, s16 y) {
    s16 wins[10];
    s16 icons[8];
    s16 digits[16];
    s16 anim;
    u16 sprite;
    s16 win;
    s16 iconAnim;
    s16 digitAnim;
    s32 nextPage = 0;
    s32 messages[6] = { 0x5002, 0x5003, 0x5004, 0x5005, 0x5006, 0x5007 };
    char text[8];
    s16 i;
    s16 j;
    s32 page;
    s32 count;
    s32 buttons;
    s32 value;
    s32 ones;
    f32 scale;
    f32 baseX;
    f32 baseY;

    page = 0;
    HuPrcSleep(3);
    anim = HuSprAnimDataRead(animFile);
    sprite = espEntry(anim, 0, 1);
    espPosSet(sprite, x, y);
    espPriSet(sprite, 0x8000);
    espScaleSet(sprite, 0.0f, 0.0f);
    iconAnim = HuSprAnimDataRead(0x1F0004);
    for (i = 0; i < 8; i++) {
        icons[i] = espEntry(iconAnim, 0, 1);
        espPosSet(icons[i], x + i * 24 - 84, y + 12);
        espPriSet(icons[i], 0x8000);
        espScaleSet(icons[i], 1.0f, 1.0f);
        func_8000BDDC_main(icons[i], 1);
        espBankSet(icons[i], (u16)D_801138C8_option[i], 0);
        espDispOff(icons[i]);
    }
    digitAnim = HuSprAnimDataRead(0x1F0007);
    for (i = 0; i < 8; i++) {
        s32 offsetX;

        digits[i * 2] = espEntry(digitAnim, 0, 1);
        digits[i * 2 + 1] = espEntry(digitAnim, 0, 1);
        offsetX = i * 24 - 96;
        espPosSet(digits[i * 2], x + offsetX + 8, y + 26);
        espPosSet(digits[i * 2 + 1], x + offsetX + 16, y + 26);
        espPriSet(digits[i * 2], 0x8000);
        espPriSet(digits[i * 2 + 1], 0x8000);
        espScaleSet(digits[i * 2], 1.0f, 1.0f);
        espScaleSet(digits[i * 2 + 1], 1.0f, 1.0f);
        func_8000BDDC_main(digits[i * 2], 1);
        func_8000BDDC_main(digits[i * 2 + 1], 1);
        value = (u8)(GwCommon.boardRecord[0][page].chr[D_801138C8_option[i]] / 10);
        if (value >= 10) {
            value = 9;
        }
        ones = (u8)(GwCommon.boardRecord[0][page].chr[D_801138C8_option[i]] % 10);
        espBankSet(digits[i * 2], (u16)value, 0);
        espBankSet(digits[i * 2 + 1], (u16)ones, 0);
        espDispOff(digits[i * 2]);
        espDispOff(digits[i * 2 + 1]);
    }
    win = HuWinExCreate(-1, 0, 0, 210, 14, 1);
    HuWinBGColSet(win, 255, 255, 255);
    HuAudFXPlay(0x2E7);
    for (i = 1; i <= 10; i++) {
        scale = cosdf(i * 36.0f) * 0.5f + 0.5f;
        espScaleSet(sprite, scale, sindf(i * 9.0f));
        HuPrcVSleep();
    }
    baseX = x - 104;
    baseY = y - 71;
    while (1) {
        wins[0] = HuWinExCreate(-1, baseX + D_801138EC_option[0].x, baseY + D_801138EC_option[0].y,
                                D_801138EC_option[0].w, D_801138EC_option[0].h, 0);
        HuWinBGTPLvlSet(wins[0], 0);
        HuWinMesSet(wins[0], 0x5000, -1, -1);
        wins[1] = HuWinExCreate(-1, baseX + D_801138EC_option[1].x, baseY + D_801138EC_option[1].y,
                                D_801138EC_option[1].w, D_801138EC_option[1].h, 0);
        HuWinBGTPLvlSet(wins[1], 0);
        HuWinMesSet(wins[1], messages[page], -1, -1);
        count = 2;
        wins[count] = HuWinExCreate(-1, baseX + D_801138EC_option[count].x, baseY + D_801138EC_option[count].y,
                                    D_801138EC_option[count].w, D_801138EC_option[count].h, 0);
        HuWinBGTPLvlSet(wins[count], 0);
        value = GwCommon.boardRecord[0][page].playCount;
        if (value >= 100) {
            value = 99;
        }
        sprintf(text, "%2d", value);
        HuWinInsertMesSet(wins[count], (u32)text, 0);
        HuWinMesSet(wins[count], 0x500E, -1, -1);
        count++;
        wins[count] = HuWinExCreate(-1, baseX + D_801138EC_option[count].x, baseY + D_801138EC_option[count].y,
                                    D_801138EC_option[count].w, D_801138EC_option[count].h, 0);
        HuWinBGTPLvlSet(wins[count], 0);
        HuWinMesSet(wins[count], 0x500F, -1, -1);
        count++;
        wins[count] = HuWinExCreate(-1, baseX + D_801138EC_option[count].x, baseY + D_801138EC_option[count].y,
                                    D_801138EC_option[count].w, D_801138EC_option[count].h, 0);
        HuWinBGTPLvlSet(wins[count], 0);
        HuWinMesSet(wins[count], 0x5010, -1, -1);
        count++;
        wins[count] = HuWinExCreate(-1, baseX + D_801138EC_option[count].x, baseY + D_801138EC_option[count].y,
                                    D_801138EC_option[count].w, D_801138EC_option[count].h, 0);
        HuWinBGTPLvlSet(wins[count], 0);
        HuWinMesSet(wins[count], 0x5011, -1, -1);
        count++;
        for (i = 0; i < 4; i++) {
            HuWinDispOn(wins[i]);
            HuWinPosSet(win, baseX + 104.0f, baseY + D_801138EC_option[i].y + 9.0f);
            HuWinDispOn(win);
            HuAudFXPlay(0x2E8);
            for (j = 1; j < 4; j++) {
                HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
                HuPrcVSleep();
            }
        }
        for (i = 0; i < 8; i++) {
            espDispOn(icons[i]);
        }
        HuWinDispOn(win);
        HuAudFXPlay(0x2E8);
        for (j = 1; j < 4; j++) {
            HuWinPosSet(win, x, y + 10);
            HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
            HuPrcVSleep();
        }
        for (i = 0; i < 8; i++) {
            value = (u8)(GwCommon.boardRecord[0][page].chr[D_801138C8_option[i]] / 10);
            if (value >= 10) {
                value = 9;
            }
            ones = (u8)(GwCommon.boardRecord[0][page].chr[D_801138C8_option[i]] % 10);
            espBankSet(digits[i * 2], (u16)value, 0);
            espBankSet(digits[i * 2 + 1], (u16)ones, 0);
            func_8000BDDC_main(digits[i * 2], 1);
            func_8000BDDC_main(digits[i * 2 + 1], 1);
            if (value != 0) {
                espDispOn(digits[i * 2]);
            } else {
                espDispOff(digits[i * 2]);
            }
            espDispOn(digits[i * 2 + 1]);
        }
        HuWinDispOn(win);
        HuAudFXPlay(0x2E8);
        for (j = 1; j < 4; j++) {
            HuWinPosSet(win, x, y + 25);
            HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
            HuPrcVSleep();
        }
        HuWinDispOff(win);
        for (i = 4; i < count; i++) {
            HuWinDispOn(wins[i]);
            HuWinPosSet(win, baseX + 104.0f, baseY + D_801138EC_option[i].y + 9.0f);
            HuWinDispOn(win);
            HuAudFXPlay(0x2E8);
            for (j = 1; j < 4; j++) {
                HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
                HuPrcVSleep();
            }
        }
        do {
            HuPrcVSleep();
            buttons = D_800D5558_main[0];
            buttons |= func_801130E8_option(0);
        } while (!(buttons & (B_BUTTON | L_JPAD | R_JPAD)));
        if (buttons & B_BUTTON) {
            break;
        }
        if (buttons & L_JPAD) {
            nextPage = nextPage - 1 < 0 ? 5 : nextPage - 1;
            if (!_CheckFlag(0x31) && nextPage == 5) {
                nextPage = 4;
            }
        }
        if (buttons & R_JPAD) {
            nextPage = nextPage + 1 < 6 ? nextPage + 1 : 0;
            if (!_CheckFlag(0x31) && nextPage == 5) {
                nextPage = 0;
            }
        }
        page = nextPage;
        for (i = 0; i < 8; i++) {
            espDispOff(icons[i]);
            espDispOff(digits[i * 2]);
            espDispOff(digits[i * 2 + 1]);
        }
        for (i = 0; i < count; i++) {
            HuWinDispOff(wins[i]);
        }
        for (i = 0; i < count; i++) {
            HuWinKill(wins[i]);
        }
        HuPrcSleep(3);
    }
    HuAudFXPlay(0x2E9);
    HuWinKill(win);
    for (i = 0; i < 8; i++) {
        espDispOff(icons[i]);
        espDispOff(digits[i * 2]);
        espDispOff(digits[i * 2 + 1]);
    }
    for (i = 0; i < count; i++) {
        HuWinDispOff(wins[i]);
    }
    for (i = 0; i < count; i++) {
        HuWinKill(wins[i]);
    }
    HuPrcSleep(3);
    for (i = 1; i <= 10; i++) {
        scale = 1.0f - sindf(i * 9.0f);
        espScaleSet(sprite, scale, scale);
        HuPrcVSleep();
    }
    for (i = 0; i < 8; i++) {
        espKill(icons[i]);
        espKill(digits[i * 2]);
        espKill(digits[i * 2 + 1]);
    }
    HuSprAnimKill(iconAnim);
    HuSprAnimKill(digitAnim);
    espKill(sprite);
    HuSprAnimKill(anim);
}

void func_8010D5B0_option(s32 animFile, s16 x, s16 y) {
    s16 wins[10];
    s16 icons[8];
    s16 digits[16];
    s16 anim;
    u16 sprite;
    s16 win;
    s16 iconAnim;
    s16 digitAnim;
    s32 nextPage = 0;
    s32 messages[6] = { 0x5008, 0x5009, 0x500A, 0x500B, 0x500C, 0x500D };
    char text[8];
    s16 i;
    s16 j;
    s32 page;
    s32 count;
    s32 buttons;
    s32 value;
    s32 ones;
    f32 scale;
    f32 baseX;
    f32 baseY;

    page = 0;
    HuPrcSleep(3);
    anim = HuSprAnimDataRead(animFile);
    sprite = espEntry(anim, 0, 1);
    espPosSet(sprite, x, y);
    espPriSet(sprite, 0x8000);
    espScaleSet(sprite, 0.0f, 0.0f);
    iconAnim = HuSprAnimDataRead(0x1F0004);
    for (i = 0; i < 8; i++) {
        icons[i] = espEntry(iconAnim, 0, 1);
        espPosSet(icons[i], x + i * 24 - 84, y + 12);
        espPriSet(icons[i], 0x8000);
        espScaleSet(icons[i], 1.0f, 1.0f);
        func_8000BDDC_main(icons[i], 1);
        espBankSet(icons[i], (u16)D_8011394C_option[i], 0);
        espDispOff(icons[i]);
    }
    digitAnim = HuSprAnimDataRead(0x1F0007);
    for (i = 0; i < 8; i++) {
        s32 offsetX;

        digits[i * 2] = espEntry(digitAnim, 0, 1);
        digits[i * 2 + 1] = espEntry(digitAnim, 0, 1);
        offsetX = i * 24 - 96;
        espPosSet(digits[i * 2], x + offsetX + 8, y + 26);
        espPosSet(digits[i * 2 + 1], x + offsetX + 16, y + 26);
        espPriSet(digits[i * 2], 0x8000);
        espPriSet(digits[i * 2 + 1], 0x8000);
        espScaleSet(digits[i * 2], 1.0f, 1.0f);
        espScaleSet(digits[i * 2 + 1], 1.0f, 1.0f);
        func_8000BDDC_main(digits[i * 2], 1);
        func_8000BDDC_main(digits[i * 2 + 1], 1);
        value = (u8)(GwCommon.boardRecord[1][page].chr[D_8011394C_option[i]] / 10);
        if (value >= 10) {
            value = 9;
        }
        ones = (u8)(GwCommon.boardRecord[1][page].chr[D_8011394C_option[i]] % 10);
        espBankSet(digits[i * 2], (u16)value, 0);
        espBankSet(digits[i * 2 + 1], (u16)ones, 0);
        espDispOff(digits[i * 2]);
        espDispOff(digits[i * 2 + 1]);
    }
    win = HuWinExCreate(-1, 0, 0, 210, 14, 1);
    HuWinBGColSet(win, 255, 255, 255);
    HuAudFXPlay(0x2E7);
    for (i = 1; i <= 10; i++) {
        scale = cosdf(i * 36.0f) * 0.5f + 0.5f;
        espScaleSet(sprite, scale, sindf(i * 9.0f));
        HuPrcVSleep();
    }
    baseX = x - 104;
    baseY = y - 71;
    while (1) {
        wins[0] = HuWinExCreate(-1, baseX + D_80113970_option[0].x, baseY + D_80113970_option[0].y,
                                D_80113970_option[0].w, D_80113970_option[0].h, 0);
        HuWinBGTPLvlSet(wins[0], 0);
        HuWinMesSet(wins[0], 0x5001, -1, -1);
        wins[1] = HuWinExCreate(-1, baseX + D_80113970_option[1].x, baseY + D_80113970_option[1].y,
                                D_80113970_option[1].w, D_80113970_option[1].h, 0);
        HuWinBGTPLvlSet(wins[1], 0);
        HuWinMesSet(wins[1], messages[page], -1, -1);
        count = 2;
        wins[count] = HuWinExCreate(-1, baseX + D_80113970_option[count].x, baseY + D_80113970_option[count].y,
                                    D_80113970_option[count].w, D_80113970_option[count].h, 0);
        HuWinBGTPLvlSet(wins[count], 0);
        value = GwCommon.boardRecord[1][page].playCount;
        if (value >= 100) {
            value = 99;
        }
        sprintf(text, "%2d", value);
        HuWinInsertMesSet(wins[count], (u32)text, 0);
        HuWinMesSet(wins[count], 0x500E, -1, -1);
        count++;
        wins[count] = HuWinExCreate(-1, baseX + D_80113970_option[count].x, baseY + D_80113970_option[count].y,
                                    D_80113970_option[count].w, D_80113970_option[count].h, 0);
        HuWinBGTPLvlSet(wins[count], 0);
        HuWinMesSet(wins[count], 0x500F, -1, -1);
        count++;
        wins[count] = HuWinExCreate(-1, baseX + D_80113970_option[count].x, baseY + D_80113970_option[count].y,
                                    D_80113970_option[count].w, D_80113970_option[count].h, 0);
        HuWinBGTPLvlSet(wins[count], 0);
        HuWinMesSet(wins[count], 0x5010, -1, -1);
        count++;
        wins[count] = HuWinExCreate(-1, baseX + D_80113970_option[count].x, baseY + D_80113970_option[count].y,
                                    D_80113970_option[count].w, D_80113970_option[count].h, 0);
        HuWinBGTPLvlSet(wins[count], 0);
        HuWinMesSet(wins[count], 0x5011, -1, -1);
        count++;
        for (i = 0; i < 4; i++) {
            HuWinDispOn(wins[i]);
            HuWinPosSet(win, baseX + 104.0f, baseY + D_80113970_option[i].y + 9.0f);
            HuAudFXPlay(0x2E8);
            HuWinDispOn(win);
            for (j = 1; j < 4; j++) {
                HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
                HuPrcVSleep();
            }
        }
        for (i = 0; i < 8; i++) {
            espDispOn(icons[i]);
        }
        HuWinDispOn(win);
        HuAudFXPlay(0x2E8);
        for (j = 1; j < 4; j++) {
            HuWinPosSet(win, x, y + 10);
            HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
            HuPrcVSleep();
        }
        for (i = 0; i < 8; i++) {
            value = (u8)(GwCommon.boardRecord[1][page].chr[D_8011394C_option[i]] / 10);
            if (value >= 10) {
                value = 9;
            }
            ones = (u8)(GwCommon.boardRecord[1][page].chr[D_8011394C_option[i]] % 10);
            espBankSet(digits[i * 2], (u16)value, 0);
            espBankSet(digits[i * 2 + 1], (u16)ones, 0);
            func_8000BDDC_main(digits[i * 2], 1);
            func_8000BDDC_main(digits[i * 2 + 1], 1);
            if (value != 0) {
                espDispOn(digits[i * 2]);
            } else {
                espDispOff(digits[i * 2]);
            }
            espDispOn(digits[i * 2 + 1]);
        }
        HuAudFXPlay(0x2E8);
        HuWinDispOn(win);
        for (j = 1; j < 4; j++) {
            HuWinPosSet(win, x, y + 25);
            HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
            HuPrcVSleep();
        }
        HuWinDispOff(win);
        for (i = 4; i < count; i++) {
            HuWinDispOn(wins[i]);
            HuWinPosSet(win, baseX + 104.0f, baseY + D_80113970_option[i].y + 9.0f);
            HuWinDispOn(win);
            HuAudFXPlay(0x2E8);
            for (j = 1; j < 4; j++) {
                HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
                HuPrcVSleep();
            }
        }
        do {
            HuPrcVSleep();
            buttons = D_800D5558_main[0];
            buttons |= func_801130E8_option(0);
        } while (!(buttons & (B_BUTTON | L_JPAD | R_JPAD)));
        if (buttons & B_BUTTON) {
            break;
        }
        if (buttons & L_JPAD) {
            nextPage = nextPage - 1 < 0 ? 5 : nextPage - 1;
            if (!_CheckFlag(0x30) && nextPage == 5) {
                nextPage = 4;
            }
        }
        if (buttons & R_JPAD) {
            nextPage = nextPage + 1 < 6 ? nextPage + 1 : 0;
            if (!_CheckFlag(0x30) && nextPage == 5) {
                nextPage = 0;
            }
        }
        page = nextPage;
        for (i = 0; i < 8; i++) {
            espDispOff(icons[i]);
            espDispOff(digits[i * 2]);
            espDispOff(digits[i * 2 + 1]);
        }
        for (i = 0; i < count; i++) {
            HuWinDispOff(wins[i]);
        }
        for (i = 0; i < count; i++) {
            HuWinKill(wins[i]);
        }
        HuPrcSleep(3);
    }
    HuAudFXPlay(0x2E9);
    HuWinKill(win);
    for (i = 0; i < 8; i++) {
        espDispOff(icons[i]);
        espDispOff(digits[i * 2]);
        espDispOff(digits[i * 2 + 1]);
    }
    for (i = 0; i < count; i++) {
        HuWinDispOff(wins[i]);
    }
    for (i = 0; i < count; i++) {
        HuWinKill(wins[i]);
    }
    HuPrcSleep(3);
    for (i = 1; i <= 10; i++) {
        scale = 1.0f - sindf(i * 9.0f);
        espScaleSet(sprite, scale, scale);
        HuPrcVSleep();
    }
    for (i = 0; i < 8; i++) {
        espKill(icons[i]);
        espKill(digits[i * 2]);
        espKill(digits[i * 2 + 1]);
    }
    HuSprAnimKill(iconAnim);
    HuSprAnimKill(digitAnim);
    espKill(sprite);
    HuSprAnimKill(anim);
}

void func_8010E77C_option(s32 x, s32 y, s32 frame) {
    func_80112028_option(1, (s32)(x + sindf(frame * 18) * 4.0f) - 2, y);
}

void func_8010E7FC_option(s32 startX, s32 startY, s32 endX, s32 endY, s32 duration) {
    s32 i;
    s32 dx;
    s32 dy;
    f32 t;

    i = 0;
    dx = endX - startX;
    dy = endY - startY;
    for (;; i++) {
        HuPrcVSleep();
        t = (f32)i / duration;
        func_80112028_option(1, dx * t + startX, dy * t + startY);
        if (i == duration) {
            break;
        }
    }
}

void func_8010E8E0_option(void) {
    s16 windows[16];
    OptSoundMenu menu = D_80113DA8_option;
    s16 titleWindow;
    s32 i;
    s32 page;
    s32 selected;
    s32 frame;
    s32 buttons;
    s32 customSounds;
    s32 previous;
    s32 sound;
    s16 model;

    func_801132E4_option(2, 0);
    func_8011331C_option(2, 13, 0);
    func_801132C8_option(2, 7);
    selected = 0;
    page = 0;
    func_80112028_option(2, 90, 116);
    func_80113384_option(2);
    func_80112028_option(1, 30, 40);
    func_80113384_option(1);
    titleWindow = HuWinExCreate(-1, 24, 28, 120, 20, 0);
    HuWinBGTPLvlSet(titleWindow, 0);
    func_8005C154_main(titleWindow, 192, 192, 192);
    HuWinBGColSet(titleWindow, 255, 255, 255);
    HuWinMesPalSet(titleWindow, 0, 0, 0, 0);
    HuWinMesColSet(titleWindow, 0);
    HuWinMesSet(titleWindow, menu.pages[0].title, -1, -1);
    HuWinDispOn(titleWindow);
    customSounds = 0;
    if (func_800E905C_minigame(0) >= 0) {
        customSounds = 1;
        menu.pages[14].entries[1].message = 0x4C37;
        menu.pages[14].entries[1].sound = 0x2C7;
    }
    if (func_800E905C_minigame(1) >= 0) {
        customSounds = 1;
        menu.pages[14].entries[2].message = 0x4C38;
        menu.pages[14].entries[2].sound = 0x2C8;
    }
    if (func_800E905C_minigame(2) >= 0) {
        customSounds = 1;
        menu.pages[14].entries[3].message = 0x4C39;
        menu.pages[14].entries[3].sound = 0x2C9;
    }
    if (func_800E905C_minigame(3) >= 0) {
        customSounds = 1;
        menu.pages[14].entries[4].message = 0x4C3A;
        menu.pages[14].entries[4].sound = 0x2CA;
    }
    if (func_800E905C_minigame(4) >= 0) {
        customSounds = 1;
        menu.pages[14].entries[5].message = 0x4C3B;
        menu.pages[14].entries[5].sound = 0x2CB;
    }
    if (func_800E905C_minigame(5) >= 0) {
        customSounds = 1;
        menu.pages[14].entries[6].message = 0x4C3C;
        menu.pages[14].entries[6].sound = 0x2CC;
    }
    if (customSounds) {
        menu.pages[14].entries[0].message = 0x4C36;
        menu.pages[14].entries[0].sound = 0x240;
    }
    for (i = 0; i < 9; i++) {
        windows[i] = HuWinExCreate(-1, 36, (i + 1) * 14 + 28, 120, 20, 0);
        HuWinBGTPLvlSet(windows[i], 0);
        func_8005C154_main(windows[i], 192, 192, 192);
        HuWinBGColSet(windows[i], 255, 255, 255);
        HuWinMesPalSet(windows[i], 0, 0, 0, 0);
        HuWinMesColSet(windows[i], 0);
        if (menu.pages[page].entries[i].message != -1) {
            HuWinMesSet(windows[i], menu.pages[page].entries[i].message, -1, -1);
        } else {
            HuWinHomeClear(windows[i]);
        }
        HuWinDispOn(windows[i]);
    }
    windows[10] = HuWinExCreate(-1, 36, 176, 120, 44, 0);
    HuWinBGTPLvlSet(windows[10], 0);
    func_8005C154_main(windows[10], 192, 192, 192);
    HuWinBGColSet(windows[10], 255, 255, 255);
    HuWinMesPalSet(windows[10], 0, 0, 0, 0);
    HuWinMesColSet(windows[10], 0);
    HuWinMesSet(windows[10], 0x5D00, -1, -1);
    HuWinDispOn(windows[10]);
    frame = 0;
    while (1) {
        HuPrcVSleep();
        buttons = D_800D1244_main[0];
        buttons |= func_80113204_option(0);
        buttons = (buttons & ~(A_BUTTON | B_BUTTON)) | (D_800D5558_main[0] & (A_BUTTON | B_BUTTON));
        if (buttons & 0x4000) {
            model = func_80113218_option(2);
            func_80033910_main(Hu3DData[model].hmf);
            break;
        } else if (buttons & 0x8000) {
            if (menu.pages[page].entries[selected].sound != -1) {
                if (func_8010FE00_option()) {
                    func_8010FE10_option();
                }
                sound = HuAudFXPlay(menu.pages[page].entries[selected].sound);
                model = func_80113218_option(2);
                func_80033970_main(Hu3DData[model].hmf);
                func_8010FF0C_option(sound);
            } else {
                func_80113218_option(2);
            }
        } else if (buttons & 0x300) {
            if (buttons & 0x200) {
                page--;
            } else {
                page++;
            }
            page = page < 15 ? page : 0;
            if (page < 0) {
                page = 14;
            }
            if (page == 14) {
                if (!customSounds) {
                    page = buttons & 0x200 ? 13 : 0;
                }
            }
            HuWinMesSet(titleWindow, menu.pages[page].title, -1, -1);
            for (i = 0; i < 9; i++) {
                if (menu.pages[page].entries[i].message != -1) {
                    HuWinMesSet(windows[i], menu.pages[page].entries[i].message, -1, -1);
                } else {
                    HuWinHomeClear(windows[i]);
                }
            }
            for (;;) {
                if (menu.pages[page].entries[selected].sound != -1) {
                    goto update_cursor;
                }
                selected--;
                selected = selected < 9 ? selected : 0;
                if (selected < 0) {
                    selected = 8;
                }
            }
        } else if (buttons & 0xC00) {
            previous = selected;
            do {
                if (buttons & 0x800) {
                    selected--;
                } else {
                    selected++;
                }
                selected = selected < 9 ? selected : 0;
                if (selected < 0) {
                    selected = 8;
                }
            } while (menu.pages[page].entries[selected].sound == -1);
            func_8010E7FC_option(30, (previous + 1) * 14 + 40, 30, (selected + 1) * 14 + 40, 4);
        }
    update_cursor:
        frame = frame < 11 ? frame + 1 : 0;
        func_8010E77C_option(30, (selected + 1) * 14 + 40, frame);
    }
    HuWinDispOff(titleWindow);
    HuWinKill(titleWindow);
    for (i = 0; i < 9; i++) {
        HuWinDispOff(windows[i]);
    }
    for (i = 0; i < 9; i++) {
        HuWinKill(windows[i]);
    }
    HuWinDispOff(windows[10]);
    HuWinKill(windows[10]);
    HuAudFXPlay(0x2F9);
    func_8011331C_option(2, 15, 1);
    func_801132E4_option(2, 40);
    HuPrcSleep(3);
    func_801133A0_option(1);
    func_801133A0_option(2);
}

void func_8010F138_option(void) {
    s16 windows[16];
    OptMusicMenu menu = D_8011421C_option;
    s16 titleWindow;
    s32 i;
    s32 page;
    s32 selected;
    s32 frame;
    s32 buttons;
    s32 previous;
    s16 model;

    func_801132E4_option(3, 0);
    func_8011331C_option(3, 14, 0);
    func_801132C8_option(3, 7);
    selected = 0;
    page = 0;
    func_80112028_option(2, 230, 116);
    func_80113384_option(2);
    func_80112028_option(1, 170, 40);
    func_80113384_option(1);
    titleWindow = HuWinExCreate(-1, 164, 28, 120, 20, 0);
    HuWinBGTPLvlSet(titleWindow, 0);
    func_8005C154_main(titleWindow, 192, 192, 192);
    HuWinBGColSet(titleWindow, 255, 255, 255);
    HuWinMesPalSet(titleWindow, 0, 0, 0, 0);
    HuWinMesColSet(titleWindow, 0);
    HuWinMesSet(titleWindow, 0x5D01, -1, -1);
    HuWinDispOn(titleWindow);
    if (func_80110018_option()) {
        menu.pages[2].entries[1].message = 0x5D15;
        menu.pages[2].entries[1].sound = 0x4C;
    }
    if (_CheckFlag(0x1D)) {
        menu.pages[2].entries[2].message = 0x5D16;
        menu.pages[2].entries[2].sound = 0x4D;
    }
    if (_CheckFlag(0x31)) {
        menu.pages[3].entries[5].message = 0x5D1C;
        menu.pages[3].entries[5].sound = 0x1D;
    }
    if (_CheckFlag(0x30)) {
        menu.pages[4].entries[2].message = 0x5D1F;
        menu.pages[4].entries[2].sound = 0x20;
    }
    if (_CheckFlag(0x1E)) {
        menu.pages[8].entries[7].message = 0x5D3C;
        menu.pages[8].entries[7].sound = 0x41;
        menu.pages[10].entries[0].message = 0x5D44;
        menu.pages[10].entries[0].sound = 0x28;
        menu.pages[10].entries[1].message = 0x5D45;
        menu.pages[10].entries[1].sound = 0x29;
        menu.pages[10].entries[2].message = 0x5D46;
        menu.pages[10].entries[2].sound = 0x2A;
        menu.pages[10].entries[3].message = 0x5D47;
        menu.pages[10].entries[3].sound = 0x6;
    }
    for (i = 0; i < 9; i++) {
        windows[i] = HuWinExCreate(-1, 180, (i + 1) * 14 + 28, 118, 20, 0);
        HuWinBGTPLvlSet(windows[i], 0);
        func_8005C154_main(windows[i], 192, 192, 192);
        HuWinBGColSet(windows[i], 255, 255, 255);
        HuWinMesPalSet(windows[i], 0, 0, 0, 0);
        HuWinMesColSet(windows[i], 0);
        if (menu.pages[page].entries[i].message != -1) {
            HuWinMesSet(windows[i], menu.pages[page].entries[i].message, -1, -1);
        } else {
            HuWinHomeClear(windows[i]);
        }
        HuWinDispOn(windows[i]);
    }
    windows[10] = HuWinExCreate(-1, 176, 190, 120, 44, 0);
    HuWinBGTPLvlSet(windows[10], 0);
    func_8005C154_main(windows[10], 192, 192, 192);
    HuWinBGColSet(windows[10], 255, 255, 255);
    HuWinMesPalSet(windows[10], 0, 0, 0, 0);
    HuWinMesColSet(windows[10], 0);
    HuWinMesSet(windows[10], 0x5D00, -1, -1);
    HuWinDispOn(windows[10]);
    frame = 0;
    while (1) {
        HuPrcVSleep();
        buttons = D_800D1244_main[0];
        buttons |= func_80113204_option(0);
        buttons = (buttons & ~(A_BUTTON | B_BUTTON)) | (D_800D5558_main[0] & (A_BUTTON | B_BUTTON));
        if (buttons & 0x4000) {
            model = func_80113218_option(3);
            func_80033910_main(Hu3DData[model].hmf);
            break;
        } else if (buttons & 0x8000) {
            HuAudSeqStop();
            if (menu.pages[page].entries[selected].sound != -1) {
                HuAudSeqPlay(menu.pages[page].entries[selected].sound);
            }
            model = func_80113218_option(3);
            func_80033970_main(Hu3DData[model].hmf);
        } else if (buttons & 0x300) {
            if (buttons & 0x200) {
                page--;
            } else {
                page++;
            }
            page = page < 12 ? page : 0;
            if (page < 0) {
                page = 11;
            }
            if (page == 10) {
                if (!_CheckFlag(0x1E)) {
                    page = buttons & 0x200 ? 9 : 11;
                }
            }
            HuWinMesSet(titleWindow, menu.pages[page].title, -1, -1);
            for (i = 0; i < 9; i++) {
                if (menu.pages[page].entries[i].message != -1) {
                    HuWinMesSet(windows[i], menu.pages[page].entries[i].message, -1, -1);
                } else {
                    HuWinHomeClear(windows[i]);
                }
            }
            for (;;) {
                if (menu.pages[page].entries[selected].sound != -1) {
                    goto update_cursor;
                }
                selected--;
                selected = selected < 9 ? selected : 0;
                if (selected < 0) {
                    selected = 8;
                }
            }
        } else if (buttons & 0xC00) {
            previous = selected;
            do {
                if (buttons & 0x800) {
                    selected--;
                } else {
                    selected++;
                }
                selected = selected < 9 ? selected : 0;
                if (selected < 0) {
                    selected = 8;
                }
            } while (menu.pages[page].entries[selected].sound == -1);
            func_8010E7FC_option(170, (previous + 1) * 14 + 40, 170, (selected + 1) * 14 + 40, 4);
        }
    update_cursor:
        frame = frame < 11 ? frame + 1 : 0;
        func_8010E77C_option(170, (selected + 1) * 14 + 40, frame);
    }
    HuWinDispOff(titleWindow);
    HuWinKill(titleWindow);
    for (i = 0; i < 9; i++) {
        HuWinDispOff(windows[i]);
    }
    for (i = 0; i < 9; i++) {
        HuWinKill(windows[i]);
    }
    HuWinDispOff(windows[10]);
    HuWinKill(windows[10]);
    HuAudFXPlay(0x2F9);
    func_8011331C_option(3, 16, 1);
    func_801132E4_option(3, 40);
    HuPrcSleep(3);
    func_801133A0_option(1);
    func_801133A0_option(2);
}

f32 func_8010F914_option(f32 x, f32 y) {
    return -(atan2df(y, x) - 90.0f);
}

void func_8010F94C_option(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80114788_option); i++) {
        HuVecCopyXYZ(&D_80114788_option[i].unk_00, 0.0f, 0.0f, 0.0f);
        HuVecCopyXYZ(&D_80114788_option[i].unk_0C, 0.0f, 0.0f, 0.0f);
        HuVecCopyXYZ(&D_80114788_option[i].unk_18, 0.0f, 0.0f, 0.0f);
        D_80114788_option[i].obj = NULL;
    }
}

void func_8010FA28_option(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80114788_option); i++) {
        omDelObj(D_80114788_option[i].obj);
    }
}

void func_8010FA7C_option(omObjData *obj) {
    Vec pos;
    Vec at;
    Vec up;
    Vec modelPos;
    Vec direction;
    s32 model;

    model = D_80114788_option[obj->work[0]].unk_24;
    func_80105FF8_option(&pos, &at, &up);
    func_80113274_option(model, &modelPos.x, &modelPos.y, &modelPos.z);
    HuVecCopyXYZ(&direction, pos.x - modelPos.x, pos.y - modelPos.y, pos.z - modelPos.z);
    func_80113290_option(model, 0.0f, func_8010F914_option(direction.x, direction.z), 0.0f);
}

void func_8010FB40_option(s32 index, s32 model) {
    f32 x, y, z;

    if (D_80114788_option[index].obj != NULL) {
        omDelObj(D_80114788_option[index].obj);
    }
    func_80113274_option(model, &x, &y, &z);
    HuVecCopyXYZ(&D_80114788_option[index].unk_0C, 0.0f, 0.0f, 0.0f);
    HuVecCopyXYZ(&D_80114788_option[index].unk_18, x, y, z);
    D_80114788_option[index].unk_24 = model;
    D_80114788_option[index].obj = omAddObj(6, 0, 0, -1, func_8010FA7C_option);
    D_80114788_option[index].obj->work[0] = index;
}

const OptSoundMenu D_80113DA8_option = {
    {
        {
            0x4C01,
            {
                { 0x4C10, 0x2B5 },
                { 0x4C11, 0x263 },
                { 0x4C14, 0x275 },
                { 0x4C12, 0x290 },
                { 0x4C13, 0x27E },
                { 0x4C15, 0x26C },
                { 0x4C16, 0x287 },
                { 0x4C17, 0x2AC },
                { -1, -1 },
            },
        },
        {
            0x4C02,
            {
                { 0x4C10, 0x2B6 },
                { 0x4C11, 0x264 },
                { 0x4C14, 0x276 },
                { 0x4C12, 0x291 },
                { 0x4C13, 0x27F },
                { 0x4C15, 0x26D },
                { 0x4C16, 0x288 },
                { 0x4C17, 0x2AD },
                { -1, -1 },
            },
        },
        {
            0x4C03,
            {
                { 0x4C10, 0x2B7 },
                { 0x4C11, 0x265 },
                { 0x4C14, 0x277 },
                { 0x4C12, 0x292 },
                { 0x4C13, 0x280 },
                { 0x4C15, 0x26E },
                { 0x4C16, 0x289 },
                { 0x4C17, 0x2AE },
                { -1, -1 },
            },
        },
        {
            0x4C04,
            {
                { 0x4C10, 0x2B8 },
                { 0x4C11, 0x266 },
                { 0x4C14, 0x278 },
                { 0x4C12, 0x293 },
                { 0x4C13, 0x281 },
                { 0x4C15, 0x26F },
                { 0x4C16, 0x28A },
                { 0x4C17, 0x2AF },
                { -1, -1 },
            },
        },
        {
            0x4C05,
            {
                { 0x4C10, 0x2B9 },
                { 0x4C11, 0x267 },
                { 0x4C14, 0x279 },
                { 0x4C12, 0x294 },
                { 0x4C13, 0x282 },
                { 0x4C15, 0x270 },
                { 0x4C16, 0x28B },
                { 0x4C17, 0x2B0 },
                { -1, -1 },
            },
        },
        {
            0x4C06,
            {
                { 0x4C10, 0x2BA },
                { 0x4C11, 0x268 },
                { 0x4C14, 0x27A },
                { 0x4C12, 0x295 },
                { 0x4C13, 0x283 },
                { 0x4C15, 0x271 },
                { 0x4C16, 0x28C },
                { 0x4C17, 0x2B1 },
                { -1, -1 },
            },
        },
        {
            0x4C07,
            {
                { 0x4C10, 0x2BC },
                { 0x4C11, 0x26A },
                { 0x4C14, 0x27C },
                { 0x4C12, 0x297 },
                { 0x4C13, 0x285 },
                { 0x4C15, 0x273 },
                { 0x4C16, 0x28E },
                { 0x4C17, 0x2B3 },
                { -1, -1 },
            },
        },
        {
            0x4C08,
            {
                { 0x4C10, 0x2BB },
                { 0x4C11, 0x269 },
                { 0x4C14, 0x27B },
                { 0x4C12, 0x296 },
                { 0x4C13, 0x284 },
                { 0x4C15, 0x272 },
                { 0x4C16, 0x28D },
                { 0x4C17, 0x2B2 },
                { -1, -1 },
            },
        },
        {
            0x4C09,
            {
                { 0x4C18, 0x2A6 },
                { 0x4C19, 0x2A7 },
                { 0x4C1A, 0x2A8 },
                { 0x4C1B, 0x2A9 },
                { 0x4C1C, 0x2AA },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x4C0A,
            {
                { 0x4C1D, 0x29B },
                { 0x4C1E, 0x298 },
                { 0x4C1F, 0x299 },
                { 0x4C20, 0x29A },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x4C0B,
            {
                { 0x4C21, 0x29C },
                { 0x4C22, 0x29D },
                { 0x4C23, 0x29E },
                { 0x4C24, 0x29F },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x4C0C,
            {
                { 0x4C25, 0x259 },
                { 0x4C26, 0x25B },
                { 0x4C27, 0x256 },
                { 0x4C28, 0x257 },
                { 0x4C29, 0x25D },
                { 0x4C2A, 0x2A3 },
                { 0x4C2B, 0x2A4 },
                { 0x4C2C, 0x2A2 },
                { -1, -1 },
            },
        },
        {
            0x4C0D,
            {
                { 0x4C2D, 0x258 },
                { 0x4C2E, 0x2A5 },
                { 0x4C2F, 0x2A0 },
                { 0x4C30, 0x2A1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x4C0E,
            {
                { 0x4C31, 0x251 },
                { 0x4C32, 0x253 },
                { 0x4C33, 0x252 },
                { 0x4C34, 0x254 },
                { 0x4C35, 0x255 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x4C0F,
            {
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
    },
};

const OptMusicMenu D_8011421C_option = {
    {
        {
            0x5D01,
            {
                { 0x5D0F, 0x3 },
                { 0x5D10, 0x9 },
                { 0x5D11, 0xB },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D02,
            {
                { 0x5D12, 0x4 },
                { 0x5D13, 0x7 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D03,
            {
                { 0x5D14, 0x8 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D04,
            {
                { 0x5D17, 0x18 },
                { 0x5D18, 0x19 },
                { 0x5D19, 0x1A },
                { 0x5D1A, 0x1B },
                { 0x5D1B, 0x1C },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D05,
            {
                { 0x5D1D, 0x1E },
                { 0x5D1E, 0x1F },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D06,
            {
                { 0x5D20, 0xD },
                { 0x5D21, 0x12 },
                { 0x5D22, 0x17 },
                { 0x5D23, 0x24 },
                { 0x5D24, 0x13 },
                { 0x5D25, 0xF },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D07,
            {
                { 0x5D26, 0x10 },
                { 0x5D27, 0x3E },
                { 0x5D28, 0x14 },
                { 0x5D29, 0x15 },
                { 0x5D2A, 0x16 },
                { 0x5D2B, 0x46 },
                { 0x5D2C, 0x47 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D08,
            {
                { 0x5D2D, 0x2D },
                { 0x5D2E, 0x2E },
                { 0x5D2F, 0x2F },
                { 0x5D30, 0x30 },
                { 0x5D31, 0x31 },
                { 0x5D32, 0x32 },
                { 0x5D33, 0x33 },
                { 0x5D34, 0x34 },
                { -1, -1 },
            },
        },
        {
            0x5D09,
            {
                { 0x5D35, 0x35 },
                { 0x5D36, 0x36 },
                { 0x5D37, 0x37 },
                { 0x5D38, 0x38 },
                { 0x5D39, 0x44 },
                { 0x5D3A, 0x43 },
                { 0x5D3B, 0x42 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D0A,
            {
                { 0x5D3D, 0xA },
                { 0x5D3E, 0x39 },
                { 0x5D3F, 0x3A },
                { 0x5D40, 0x3B },
                { 0x5D41, 0x26 },
                { 0x5D42, 0x21 },
                { 0x5D43, 0x2C },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D0B,
            {
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D0C,
            {
                { 0x5D48, 0x3C },
                { 0x5D49, 0x3D },
                { 0x5D4A, 0x48 },
                { 0x5D4B, 0x45 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
    },
};

u16 func_8010FC40_option(s32 value) {
    char text[256];
    HmfData_UnkBC *cam;

    HuPrcSleep(3);
    while (1) {
        if (D_800D5558_main[0] & (A_BUTTON | B_BUTTON | START_BUTTON | R_TRIG)) {
            sprintf(text, "\n%d\n", value);
            break;
        }
        if (D_800D5558_main[0] & Z_TRIG) {
            cam = Hu3DData[gCameraList->unk4].hmf->unkBC;
            sprintf(text, "POS:%4.2f,%4.2f,%4.2f", cam->unk08, cam->unk0C, cam->unk10);
            print8(16, 180, text);
            sprintf(text, "A T:%4.2f,%4.2f,%4.2f", cam->unk14, cam->unk18, cam->unk1C);
            print8(16, 190, text);
            sprintf(text, "U P:%4.2f,%4.2f,%4.2f", cam->unk20, cam->unk24, cam->unk28);
            print8(16, 200, text);
        } else {
            sprintf(text, "%d", value);
            print8(16, 220, text);
        }
        HuPrcVSleep();
    }
    return D_800D5558_main[0];
}

void func_8010FDF4_option(void) {
    D_801147E0_option.obj = NULL;
}

s32 func_8010FE00_option(void) {
    return D_801147E0_option.obj != NULL;
}

void func_8010FE10_option(void) {
    s16 modelId;

    if (D_801147E0_option.obj != NULL) {
        modelId = func_80113218_option(2);
        func_80033910_main(Hu3DData[modelId].hmf);
        HuAudFXStop((s16)D_801147E0_option.seNo);
        omDelObj(D_801147E0_option.obj);
        D_801147E0_option.obj = NULL;
    }
}

void func_8010FE84_option(omObjData *obj) {
    s16 modelId;

    if (msmSeGetStatus(D_801147E0_option.seNo) == 0) {
        modelId = func_80113218_option(2);
        func_80033910_main(Hu3DData[modelId].hmf);
        HuAudFXStop((s16)D_801147E0_option.seNo);
        omDelObj(obj);
        D_801147E0_option.obj = NULL;
    }
}

omObjData *func_8010FF0C_option(s32 seNo) {
    if (D_801147E0_option.obj != NULL) {
        omDelObj(D_801147E0_option.obj);
    }
    D_801147E0_option.obj = omAddObj(6, 0, 0, -1, func_8010FE84_option);
    D_801147E0_option.seNo = seNo;
    msmSeGetStatus(seNo);
    return D_801147E0_option.obj;
}

void func_8010FF88_option(omObjData *obj) {
    s32 *counter;

    if (D_801147E8_option == 0) {
        RepeatVibrator(0, 5, 0, 5);
    }

    counter = &D_801147E8_option;
    *counter = (*counter < 11) ? *counter + 1 : 0;
}

void func_8010FFDC_option(void) {
    D_801147E8_option = 0;
    omAddObj(6, 0, 0, -1, func_8010FF88_option);
}

s32 func_80110018_option(void) {
    s32 type;
    s16 counts[9];
    s16 i;
    s16 minigameType;

    for (i = 0; i < 9; i++) {
        counts[i] = 0;
    }
    for (i = 0; i < 71; i++) {
        minigameType = D_800A6D40_main[i].minigameType;
        if ((D_800A6D40_main[i].overlay == 0x70) | (D_800A6D40_main[i].overlay == -1)) {
            continue;
        }
        if ((i == 27) | (i == 8)) {
            continue;
        }
        if (i == 16) {
            continue;
        }
        type = minigameType;
        if (type < 5 && GWMgUnlockCheck(i) != 0) {
            if (++counts[type] >= 3) {
                return 1;
            }
        }
    }
    return 0;
}
