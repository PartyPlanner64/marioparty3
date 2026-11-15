#include "common.h"
#include "overlays/minigame.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "game/pause.h"
#include "game/wipe.h"

typedef struct SwingNSwipeGroupOrder {
    s16 order[4];
} SwingNSwipeGroupOrder;

typedef struct SwingNSwipeCpuOffsets {
    s16 offsets[4];
} SwingNSwipeCpuOffsets;

typedef struct SwingNSwipeCpuSpeeds {
    f32 speeds[4];
} SwingNSwipeCpuSpeeds;

typedef struct SwingNSwipeBssC148 {
    /* 0x00 */ s16 unk00; // D_8010C148
    /* 0x02 */ s16 unk02[5]; // D_8010C14A
} SwingNSwipeBssC148; // sizeof 0xC

extern u16 D_800A11D0_main[];
extern s32 D_800A178C_main[][6];
extern u16 D_800A11DC_main[];
extern s16 D_8010C148_swing_n_swipe; // swingNSwipeBssC148.unk00
extern s16 D_8010C14A_swing_n_swipe[5]; // swingNSwipeBssC148.unk02
f32 D_8010BD30_swing_n_swipe = -400.0f; // min x
f32 D_8010BD34_swing_n_swipe = -275.0f; // min z
f32 D_8010BD38_swing_n_swipe = 400.0f; // max x
f32 D_8010BD3C_swing_n_swipe = 600.0f; // max z
s16 D_8010BD40_swing_n_swipe = 0; // state
s16 D_8010BD42_swing_n_swipe = 0; // timer
s16 D_8010BD44_swing_n_swipe = 0;
s16 D_8010BD46_swing_n_swipe = 0;
s16 D_8010BD48_swing_n_swipe = 301;
s16 D_8010BD4A_swing_n_swipe = 0;
s16 D_8010BD4C_swing_n_swipe = 0;
s16 D_8010BD4E_swing_n_swipe = 0;
s16 D_8010BD50_swing_n_swipe = 0;
s16 D_8010BD52_swing_n_swipe = 0;
s16 D_8010BD54_swing_n_swipe = 0;
f32 D_8010BD58_swing_n_swipe = -1.47f;
s16 D_8010BD5C_swing_n_swipe = 0;
f32 D_8010BD60_swing_n_swipe = 99.0f;
s16 D_8010BD64_swing_n_swipe = 0;
Vec2f D_8010BD68_swing_n_swipe[10] = { 0 };
s16 D_8010BDB8_swing_n_swipe = 0;
s16 D_8010BDBA_swing_n_swipe = 0;
s16 D_8010BDBC_swing_n_swipe[5] = { 999, 999, 999, 999, 999 };
s16 D_8010BDC8_swing_n_swipe[5] = { 0 };
s16 D_8010BDD4_swing_n_swipe[5] = { 0 };
s16 D_8010BDE0_swing_n_swipe[5] = { 0 };
Vec2f D_8010BDEC_swing_n_swipe[5] = { 0 };
s16 D_8010BE14_swing_n_swipe[5] = { 0 };
s16 D_8010BE20_swing_n_swipe[5] = { 1, 1, 1, 1, 1 };
f32 D_8010BE2C_swing_n_swipe = 0.0f;
f32 D_8010BE30_swing_n_swipe = 0.0f;
s16 D_8010BE34_swing_n_swipe[5] = { 0 };
s16 D_8010BE40_swing_n_swipe[5] = { 1, 1, 1, 1, 1 };
s16 D_8010BE4C_swing_n_swipe[5] = { 0 };

Vec D_8010BE58_swing_n_swipe[5] = {
    { 0.0f, 0.0f, -150.0f },
    { -190.0f, 0.0f, 100.0f },
    { -370.0f, 0.0f, 325.0f },
    { 190.0f, 0.0f, 100.0f },
    { 370.0f, 0.0f, 325.0f },
};

s32 D_8010BE94_swing_n_swipe[] = {
    0x0021002D,
    0x0021002E,
    0x0021002F,
    0x00210030,
    0x00210031,
    0x00210032,
    0x00210033,
    0x00210034,
    0x00210035,
    0x00210036,
    0x00210037,
    0x00210038,
    0x00210039,
    0x0021003A,
    0x0021003B,
    0x0021003C,
    0x0021003D,
    0x0021003E,
    0x0021003F,
    0x00210040,
};

s16 D_8010BEE4_swing_n_swipe = 0;
s16 D_8010BEE6_swing_n_swipe = 0;
s16 D_8010BEE8_swing_n_swipe = 0;
s16 D_8010BEEA_swing_n_swipe = 0;
s32 D_8010BEEC_swing_n_swipe = 0; /* Unreferenced. */
SwingNSwipeGroupOrder D_8010BEF0_swing_n_swipe = { { 0, 1, 2, 3 } };
SwingNSwipeCpuOffsets D_8010BEF8_swing_n_swipe = { { 45, 30, 15, 5 } };
SwingNSwipeCpuSpeeds D_8010BF00_swing_n_swipe = { { 10.0f, 11.0f, 12.0f, 13.0f } };

f32 D_8010C090_swing_n_swipe BSS;
f32 D_8010C094_swing_n_swipe BSS;
Vec D_8010C098_swing_n_swipe BSS;
f32 D_8010C0A4_swing_n_swipe BSS;
f32 D_8010C0A8_swing_n_swipe BSS;
f32 D_8010C0AC_swing_n_swipe BSS;
f32 D_8010C0B0_swing_n_swipe BSS;
f32 D_8010C0B4_swing_n_swipe BSS;
f32 D_8010C0B8_swing_n_swipe BSS;
f32 D_8010C0BC_swing_n_swipe BSS;
Vec D_8010C0C0_swing_n_swipe[5] BSS;
u8 D_8010C0FC_swing_n_swipe[4] BSS; /* Unreferenced. */
Vec D_8010C100_swing_n_swipe[5] BSS;
s16 D_8010C13C_swing_n_swipe BSS;
omObjData *D_8010C140_swing_n_swipe BSS;
s16 D_8010C144_swing_n_swipe BSS;
s16 D_8010C146_swing_n_swipe BSS;
SwingNSwipeBssC148 swingNSwipeBssC148 BSS;
s16 D_8010C154_swing_n_swipe BSS;
s16 D_8010C156_swing_n_swipe BSS;
s16 D_8010C158_swing_n_swipe BSS;
s16 D_8010C15A_swing_n_swipe BSS;
s16 D_8010C15C_swing_n_swipe BSS;
s16 D_8010C15E_swing_n_swipe BSS;
s16 D_8010C160_swing_n_swipe BSS;
s16 D_8010C162_swing_n_swipe BSS;
s16 D_8010C164_swing_n_swipe BSS;
s16 D_8010C166_swing_n_swipe BSS;
s16 D_8010C168_swing_n_swipe BSS;
s16 D_8010C16A_swing_n_swipe BSS; /* Unreferenced. */
u8 D_8010C16C_swing_n_swipe[4] BSS; /* Unreferenced. */
s16 D_8010C170_swing_n_swipe[5][2] BSS;
s16 D_8010C184_swing_n_swipe[5] BSS;
s16 D_8010C190_swing_n_swipe[5][4] BSS;
s16 D_8010C1B8_swing_n_swipe[4] BSS;
s16 D_8010C1C0_swing_n_swipe[5] BSS;
s16 D_8010C1CC_swing_n_swipe[2] BSS;
s16 D_8010C1D0_swing_n_swipe[3] BSS;

void func_801059BC_swing_n_swipe(void);
void func_80105C08_swing_n_swipe(omObjData *object);
void func_80105CDC_swing_n_swipe(void);
void func_80105EE0_swing_n_swipe(omObjData *object);
void func_80106154_swing_n_swipe(omObjData *object);
void func_80106290_swing_n_swipe(omObjData *object);
void func_801064A4_swing_n_swipe(omObjData *object);
void func_80106764_swing_n_swipe(omObjData *object);
void func_801069CC_swing_n_swipe(omObjData *object);
void func_80106AD0_swing_n_swipe(void);
void func_801072D0_swing_n_swipe(void);
void func_80107CEC_swing_n_swipe(omObjData *object);
void func_80107F00_swing_n_swipe(omObjData *object);
void func_80108158_swing_n_swipe(void);
void func_8010A0E4_swing_n_swipe(omObjData *object);
void func_8010B01C_swing_n_swipe(omObjData *object);
void func_8010B100_swing_n_swipe(omObjData *object);
void func_8010B23C_swing_n_swipe(omObjData *object);
void func_8010897C_swing_n_swipe(void);
void func_801092B4_swing_n_swipe(void);
void func_801099E8_swing_n_swipe(void);
void func_8010A3FC_swing_n_swipe(void);
void func_8010A780_swing_n_swipe(void);
void func_8010A994_swing_n_swipe(void);
void func_8010AA3C_swing_n_swipe(void);
s16 func_8010B840_swing_n_swipe(s32 dataNum, u16 attr, u16 pri, s16 x, s16 y);
s16 func_8010B8EC_swing_n_swipe(s32 arg0);
s16 func_8010B920_swing_n_swipe(void);
s16 func_8010BA40_swing_n_swipe(s16 index);
s16 func_8010BB88_swing_n_swipe(s16 index);
void func_801066BC_swing_n_swipe(omObjData *object);
void func_80106704_swing_n_swipe(omObjData *object);
void func_8010673C_swing_n_swipe(omObjData *object);

void func_801059A0_swing_n_swipe(void) {
    func_801059BC_swing_n_swipe();
}

void func_801059BC_swing_n_swipe(void) {
    SwingNSwipeGroupOrder groupOrder = D_8010BEF0_swing_n_swipe;
    omObjData *obj;
    s32 camIndex;
    s16 i;

    func_8001FE20_main(0x40);
    func_800142A0_main(0x40);
    omInitObjMan(0x40, 0x40);
    func_8004A208_main();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(camIndex, 30.0f, 80.0f, 8000.0f);
    CZoom = 1800.0f;
    CRot.x = -15.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 174.5f;
    Center.z = 150.0f;
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    if (i < 4) {
        D_8010C144_swing_n_swipe = groupOrder.order[i];
    } else {
        D_8010C144_swing_n_swipe = groupOrder.order[0];
    }
    omAddObj(1000, 0, 0, -1, func_80105C08_swing_n_swipe);
    omAddObj(2000, 0, 0, -1, func_8010673C_swing_n_swipe);
}

void func_80105C08_swing_n_swipe(omObjData *object) {
    func_80105CDC_swing_n_swipe();
    func_8010B840_swing_n_swipe(0x610000, 0x4000, 10, 160, 120);
    D_8010C140_swing_n_swipe = omAddObj(10, 20, 20, -1, func_80106764_swing_n_swipe);
    omAddObj(20, 20, 20, -1, func_80107CEC_swing_n_swipe);
    omAddObj(30, 20, 20, -1, func_8010A0E4_swing_n_swipe);
    omAddObj(40, 20, 20, -1, func_8010B100_swing_n_swipe);
    object->func = func_80105EE0_swing_n_swipe;
}

void func_80105CDC_swing_n_swipe(void) {
    s16 thresholds[5];
    SwingNSwipeCpuOffsets offsets = D_8010BEF8_swing_n_swipe;
    SwingNSwipeCpuSpeeds speeds = D_8010BF00_swing_n_swipe;
    s16 i;
    s16 roll;

    D_8010C13C_swing_n_swipe = 1;
    GwPlayer[D_8010C144_swing_n_swipe].bonusCoin = -1;
    if (GwPlayer[D_8010C144_swing_n_swipe].stat & 1) {
        thresholds[0] = D_800A11DC_main[0];
        for (i = 1; i < 5; i++) {
            thresholds[i] = thresholds[i - 1] + D_800A11DC_main[i];
        }
        roll = (u8)(rand8() % 100);
        for (i = 0; i < 5; i++) {
            if (roll < thresholds[i]) {
                break;
            }
        }
        if (i <= 0) {
            i = 0;
        }
        if (i >= 4) {
            i = 4;
        }
        D_8010C160_swing_n_swipe = i;
        D_8010C162_swing_n_swipe = offsets.offsets[GwPlayer[D_8010C144_swing_n_swipe].cpu_difficulty];
        D_8010C164_swing_n_swipe = speeds.speeds[GwPlayer[D_8010C144_swing_n_swipe].cpu_difficulty];
    }
}

void func_80105EE0_swing_n_swipe(omObjData *object) {
    switch (D_8010BD40_swing_n_swipe) {
        case 0:
            WipeCreateIn(0xFF, 16);
            D_8010BD40_swing_n_swipe++;
            break;
        case 1:
            object->func = func_80106154_swing_n_swipe;
            D_8010BD40_swing_n_swipe++;
            break;
        case 2:
            if (++D_8010BD42_swing_n_swipe == 1) {
                GMesCreate(8);
            } else if (GMesStatGet() == 0) {
                D_8010BD42_swing_n_swipe = 0;
                D_8010BD40_swing_n_swipe++;
            }
            break;
        case 3:
            object->func = func_80106290_swing_n_swipe;
            D_8010BD40_swing_n_swipe++;
            break;
        case 4:
            if (++D_8010BD42_swing_n_swipe == 1) {
                GMesCreate(0x13);
                HuAudSeqFadeOut(120);
            } else if (GMesStatGet() == 0) {
                D_8010BD42_swing_n_swipe = 0;
                D_8010BD40_swing_n_swipe++;
            }
            break;
        case 5:
            object->func = func_801064A4_swing_n_swipe;
            D_8010BD40_swing_n_swipe++;
            break;
        case 6:
            if (++D_8010BD42_swing_n_swipe == 1) {
                switch (D_8010C13C_swing_n_swipe) {
                    case 0:
                        HuAudSeqPlay(0x68);
                        func_800370D0_main(GMesCreate(0x24), 120);
                        GwPlayer[D_8010C144_swing_n_swipe].bonusCoin = D_800A11D0_main[D_8010C15E_swing_n_swipe];
                        break;
                    case 1:
                        HuAudSeqPlay(0x6B);
                        func_800370D0_main(GMesCreate(0x1D), 120);
                        GwPlayer[D_8010C144_swing_n_swipe].bonusCoin = -1;
                        break;
                }
            } else if (D_8010BD42_swing_n_swipe >= 135) {
                D_8010BD42_swing_n_swipe = 0;
                D_8010BD40_swing_n_swipe++;
            }
            break;
        case 7:
            object->func = func_801066BC_swing_n_swipe;
            break;
    }
    func_801092B4_swing_n_swipe();
    func_801099E8_swing_n_swipe();
    func_8010A994_swing_n_swipe();
    func_8010AA3C_swing_n_swipe();
}

void func_80106154_swing_n_swipe(omObjData *object) {
    switch (D_8010BD44_swing_n_swipe) {
        case 0:
            if (WipeStatGet() == 1) {
                return;
            }
            HuAudSeqPlay(0x44);
            D_8010BD44_swing_n_swipe++;
            break;
        case 1:
            D_8010C154_swing_n_swipe = 1;
            if (D_8010BD46_swing_n_swipe++ >= 30) {
                D_8010BD46_swing_n_swipe = 0;
                D_8010BD44_swing_n_swipe++;
            }
            break;
        case 2:
            D_8010C148_swing_n_swipe = 1;
            D_8010BD44_swing_n_swipe++;
            break;
        case 3:
            if (D_8010BD46_swing_n_swipe++ >= 60) {
                D_8010BD46_swing_n_swipe = 0;
                D_8010BD44_swing_n_swipe++;
            }
            break;
        case 4:
            D_8010C146_swing_n_swipe = 1;
            D_8010BD44_swing_n_swipe++;
            break;
        case 5:
            if (D_8010C146_swing_n_swipe == 0) {
                object->func = func_80105EE0_swing_n_swipe;
            }
            break;
    }
    func_80106AD0_swing_n_swipe();
    func_80108158_swing_n_swipe();
    func_8010A3FC_swing_n_swipe();
}

void func_80106290_swing_n_swipe(omObjData *object) {
    s16 i;

    if (--D_8010BD48_swing_n_swipe == 300) {
        D_8010C148_swing_n_swipe = 2;
        GMesCreate(0x1A, 10, 160, 56);
    } else if (D_8010BD48_swing_n_swipe >= 0) {
        func_8003F578_main((D_8010BD48_swing_n_swipe + 29) / 30);
        func_801072D0_swing_n_swipe();
        func_8010897C_swing_n_swipe();
    } else {
        D_8010C13C_swing_n_swipe = 1;
        func_8003F5C0_main();
        D_8010C156_swing_n_swipe = 1;
        D_8010C15A_swing_n_swipe = 1;
        D_8010C146_swing_n_swipe = 0;
        D_8010C148_swing_n_swipe = 0;
        Hu3DData[D_8010C140_swing_n_swipe->model[0]].motIdShape = 0xFF;
        func_800E5690_minigame(D_8010C140_swing_n_swipe, 0);
        for (i = 0; i < 5; i++) {
            D_8010C14A_swing_n_swipe[i] = 0;
        }
        object->func = func_80105EE0_swing_n_swipe;
    }
    if (D_8010C13C_swing_n_swipe == 0) {
        D_8010C13C_swing_n_swipe = 0;
        func_8003F5C0_main();
        D_8010C156_swing_n_swipe = 1;
        D_8010C146_swing_n_swipe = 0;
        D_8010C148_swing_n_swipe = 4;
        for (i = 0; i < 5; i++) {
            D_8010C14A_swing_n_swipe[i] = 0;
        }
        object->func = func_80105EE0_swing_n_swipe;
    }
    func_801092B4_swing_n_swipe();
    func_801099E8_swing_n_swipe();
    func_8010A780_swing_n_swipe();
}

void func_801064A4_swing_n_swipe(omObjData *object) {
    s16 i;

    switch (D_8010BD4A_swing_n_swipe) {
        case 0:
            if (D_8010C13C_swing_n_swipe == 0) {
                D_8010C154_swing_n_swipe = 4;
            } else if (D_8010C13C_swing_n_swipe == 1) {
                D_8010C146_swing_n_swipe = 3;
                D_8010C148_swing_n_swipe = 3;
            }
            D_8010BD4A_swing_n_swipe++;
            break;
        case 1:
            if (D_8010BD4C_swing_n_swipe++ >= 90) {
                D_8010BD4A_swing_n_swipe++;
            }
            break;
        case 2:
            if (D_8010C13C_swing_n_swipe == 0) {
                func_800E5690_minigame(D_8010C140_swing_n_swipe, 6);
                func_80045ED0_main(D_800A178C_main[GwPlayer[D_8010C144_swing_n_swipe].chr][0] | 0x35);
            } else if (D_8010C13C_swing_n_swipe == 1) {
                HuAudFXPlay(0x4F6);
                func_800E5690_minigame(D_8010C140_swing_n_swipe, 7);
                func_80045ED0_main(D_800A178C_main[GwPlayer[D_8010C144_swing_n_swipe].chr][0] | 0x38);
                for (i = 0; i < 5; i++) {
                    D_8010C14A_swing_n_swipe[i] = 4;
                }
            }
            object->func = func_80105EE0_swing_n_swipe;
            break;
    }
    func_80106AD0_swing_n_swipe();
    func_801092B4_swing_n_swipe();
    func_801099E8_swing_n_swipe();
    func_8010AA3C_swing_n_swipe();
}

void func_801066BC_swing_n_swipe(omObjData *object) {
    WipeCreateOut(WIPE_TYPE_NORMAL, 16);
    HuAudSeqFadeOut(30);
    func_8004AB0C_main(30);
    object->func = func_80106704_swing_n_swipe;
}

void func_80106704_swing_n_swipe(omObjData *object) {
    if (WipeStatGet() != 1) {
        osViBlack(FALSE);
        omOvlReturnEx(1);
    }
}

void func_8010673C_swing_n_swipe(omObjData *object) {
    if (D_800D530C_main == 1) {
        object->func = func_801066BC_swing_n_swipe;
    }
}

void func_80106764_swing_n_swipe(omObjData *object) {
    s32 chr;
    s32 model;
    s32 motion;

    func_800E18D8_minigame();
    chr = GwPlayer[D_8010C144_swing_n_swipe].chr;
    model = D_800A178C_main[chr][0];
    motion = D_800A178C_main[chr][1];
    func_800E1BA8_minigame(object, model, motion, D_8010C144_swing_n_swipe, 0x2B9, 0x2B9);
    func_800E5A00_minigame(object, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(object, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(object, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(object, 4, func_80017BB8_main(chr, 0x18), 1, 0);
    func_800E5A00_minigame(object, 3, func_80017BB8_main(chr, 4), 0, 0);
    func_800E5A00_minigame(object, 5, func_80017BB8_main(chr, 0x91), 0, 0);
    func_800E5A00_minigame(object, 6, func_80017BB8_main(chr, 0x35), 0, 0);
    func_800E5A00_minigame(object, 7, func_80017BB8_main(chr, 0x38), 0, 0);
    func_800E5690_minigame(object, 4);
    omSetTra(object, 0.0f, 0.0f, 1500.0f);
    object->model[1] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelScaleSet(object->model[1], 1.5f, 1.0f, 1.5f);
    D_8010C166_swing_n_swipe = func_8000B108_main(0x610002, 0x2B9);
    func_8001C258_main(D_8010C166_swing_n_swipe, 0x4000, 0x4000);
    Hu3DModelHookSet(D_8010C166_swing_n_swipe, object->model[0], "item_hook");
    object->func = func_801069CC_swing_n_swipe;
}

void func_801069CC_swing_n_swipe(omObjData *object) {
    f32 scale = 1.5f - object->trans.y * 0.003f;

    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[1], scale, 1.0f, scale);
    if (D_8010C168_swing_n_swipe == 1 && Hu3DData[object->model[0]].motTime == 0.0f) {
        CharFXPlay(0x1F, GwPlayer[D_8010C144_swing_n_swipe].chr);
    }
    func_800E4E30_minigame(object);
}

void func_80106AD0_swing_n_swipe(void) {
    omObjData *obj = D_8010C140_swing_n_swipe;

    if (D_8010C146_swing_n_swipe == 0) {
        D_8010BD52_swing_n_swipe = 0;
        D_8010BD50_swing_n_swipe = 0;
        D_8010BD4E_swing_n_swipe = 0;
    }
    if (D_8010C146_swing_n_swipe == 1) {
        switch (D_8010BD4E_swing_n_swipe) {
            case 0:
                obj->trans.z = 1500.0f;
                obj->rot.y = 180.0f;
                Hu3DMotionShapeSet(obj->model[0], obj->motion[4], 0);
                func_800E5690_minigame(obj, 1);
                D_8010BD4E_swing_n_swipe++;
                break;
            case 1:
                D_8010C168_swing_n_swipe = 1;
                obj->trans.z -= 13.5f;
                if (obj->trans.z <= 550.0f) {
                    obj->trans.z = 550.0f;
                    D_8010BD4E_swing_n_swipe++;
                }
                break;
            case 2:
                obj->rot.y -= 13.5f;
                if (obj->rot.y <= 0.0f) {
                    obj->rot.y = 0.0f;
                    D_8010BD4E_swing_n_swipe++;
                }
                break;
            case 3:
                D_8010C168_swing_n_swipe = 0;
                Hu3DMotionShapeSet(obj->model[0], obj->motion[4], 0);
                func_800E5690_minigame(obj, 0);
                D_8010BD4E_swing_n_swipe++;
                break;
            case 4:
                if (D_8010BD50_swing_n_swipe++ >= 10) {
                    D_8010BD50_swing_n_swipe = 0;
                    D_8010BD4E_swing_n_swipe++;
                }
                break;
            case 5:
            case 8:
                HuAudFXPlay(0x4F8);
                Hu3DMotionShapeSet(obj->model[0], obj->motion[5], 0);
                func_800E5690_minigame(obj, 5);
                D_8010BD4E_swing_n_swipe++;
                break;
            case 6:
            case 9:
                if (D_8010BD50_swing_n_swipe++ >= 10) {
                    D_8010BD50_swing_n_swipe = 0;
                    D_8010BD4E_swing_n_swipe++;
                }
                break;
            case 7:
            case 10:
                if (D_800CCF58_main[Hu3DData[obj->model[0]].motId].unk02 == Hu3DData[obj->model[0]].motTime) {
                    D_8010BD4E_swing_n_swipe++;
                }
                break;
            case 11:
                Hu3DMotionShapeSet(obj->model[0], obj->motion[4], 0);
                func_800E5690_minigame(obj, 0);
                D_8010BD50_swing_n_swipe = 0;
                D_8010BD4E_swing_n_swipe = 0;
                D_8010C146_swing_n_swipe = 0;
                break;
        }
    }
    if (D_8010C146_swing_n_swipe == 3) {
        switch (D_8010BD4E_swing_n_swipe) {
            case 0:
                D_8010C098_swing_n_swipe.x = obj->trans.x;
                D_8010C098_swing_n_swipe.z = obj->trans.z;
                D_8010BD52_swing_n_swipe = 1;
                D_8010BD58_swing_n_swipe = -1.47f;
                Hu3DData[obj->model[0]].motIdShape = 0xFF;
                func_800E5690_minigame(obj, 1);
                D_8010BD4E_swing_n_swipe++;
                break;
            case 1:
                if (D_8010BD54_swing_n_swipe == 0) {
                    D_8010C168_swing_n_swipe = 1;
                    if (func_8010B920_swing_n_swipe() == 1) {
                        D_8010BD54_swing_n_swipe = 1;
                        func_800E5690_minigame(obj, 3);
                        CharFXPlay(0x3A, GwPlayer[D_8010C144_swing_n_swipe].chr);
                        D_8010C168_swing_n_swipe = 0;
                        break;
                    }
                }
                if (D_8010BD54_swing_n_swipe == 1) {
                    obj->trans.y += D_8010BD58_swing_n_swipe * D_8010BD58_swing_n_swipe *
                                    ((D_8010BD58_swing_n_swipe >= 0.0f) ? -17.0f : 17.0f);
                    if (D_8010BD58_swing_n_swipe >= 1.7f) {
                        D_8010BD58_swing_n_swipe = 1.7f;
                    } else {
                        D_8010BD58_swing_n_swipe += 0.11f;
                    }
                    if (D_8010BD58_swing_n_swipe >= 0.0f && obj->trans.y < 0.0f) {
                        obj->trans.y = 0.0f;
                        D_8010BD58_swing_n_swipe = -1.47f;
                        D_8010C168_swing_n_swipe = 1;
                        D_8010BD54_swing_n_swipe = 0;
                        CharFXPlay(0x31, GwPlayer[D_8010C144_swing_n_swipe].chr);
                        func_800E5690_minigame(obj, 1);
                    }
                }
                D_8010C090_swing_n_swipe = obj->trans.x;
                D_8010C094_swing_n_swipe = obj->trans.z;
                obj->trans.x = D_8010C098_swing_n_swipe.x - sindf(D_8010BD52_swing_n_swipe * 1.5f) * D_8010C098_swing_n_swipe.x;
                obj->trans.z = D_8010C098_swing_n_swipe.z - sindf(D_8010BD52_swing_n_swipe * 1.5f) * (D_8010C098_swing_n_swipe.z - 400.0f);
                obj->rot.y = -atan2df(D_8010C094_swing_n_swipe - obj->trans.z, D_8010C090_swing_n_swipe - obj->trans.x) + 270.0f;
                if (sindf(D_8010BD52_swing_n_swipe++ * 1.5f) == 1.0f || (obj->trans.x == 0.0f && obj->trans.z == 350.0f)) {
                    D_8010BD4E_swing_n_swipe++;
                }
                break;
            case 2:
                if (obj->rot.y >= 360.0f) {
                    obj->rot.y -= 360.0f;
                }
                if (obj->rot.y < 0.0f) {
                    obj->rot.y += 360.0f;
                }
                if (obj->rot.y >= 180.0f) {
                    obj->rot.y += 15.0f;
                    if (obj->rot.y >= 360.0f) {
                        obj->rot.y = 0;
                        D_8010BD4E_swing_n_swipe++;
                    }
                } else if (obj->rot.y > 0.0f) {
                    obj->rot.y -= 15.0f;
                    if (obj->rot.y <= 0.0f) {
                        obj->rot.y = 0.0f;
                        D_8010BD4E_swing_n_swipe++;
                    }
                } else if (obj->rot.y == 0.0f) {
                    D_8010BD4E_swing_n_swipe++;
                }
                break;
            case 3:
                D_8010C168_swing_n_swipe = 0;
                func_800E5690_minigame(obj, 0);
                D_8010BD4E_swing_n_swipe++;
                break;
        }
    }
}

void func_801072D0_swing_n_swipe(void) {
    omObjData *obj = D_8010C140_swing_n_swipe;
    s16 modelId;
    f32 moveZ = 0.0f;
    f32 moveX = moveZ;
    s16 i = 0;
    s16 pad;

    if (!(GwPlayer[D_8010C144_swing_n_swipe].stat & 1)) {
        pad = GwPlayer[D_8010C144_swing_n_swipe].pad;
        if ((D_800D5558_main[pad] & A_BUTTON) && D_8010BD5C_swing_n_swipe == 0) {
            D_8010BD5C_swing_n_swipe = 1;
            for (i = 0; i < 10; i++) {
                D_8010BD68_swing_n_swipe[i].x = D_8010BD68_swing_n_swipe[i].y = 0.0f;
            }
            Hu3DMotionShapeSet(obj->model[0], obj->motion[5], 0);
            func_800E5690_minigame(obj, 5);
        }
        if (D_8010BD5C_swing_n_swipe == 0) {
            D_8010BD68_swing_n_swipe[D_8010BDB8_swing_n_swipe].x = D_800CBB6E_main[pad];
            D_8010BD68_swing_n_swipe[D_8010BDB8_swing_n_swipe++].y = D_800D20A1_main[pad];
            for (i = 0; i < 10; i++) {
                moveX += D_8010BD68_swing_n_swipe[i].x;
                moveZ += D_8010BD68_swing_n_swipe[i].y;
            }
            moveX /= 100.0f;
            moveZ /= 100.0f;
        }
    } else {
        if (D_8010BD5C_swing_n_swipe == 0) {
            D_8010C0A4_swing_n_swipe = cosdf(obj->rot.y - 90.0f) * 100.0f + obj->trans.x;
            D_8010C0A8_swing_n_swipe = obj->trans.z - sindf(obj->rot.y - 90.0f) * 100.0f;
            modelId = D_8010C170_swing_n_swipe[D_8010C160_swing_n_swipe][0];
            D_8010C0AC_swing_n_swipe = D_8010C0A4_swing_n_swipe - Hu3DData[modelId].pos.x;
            D_8010C0B0_swing_n_swipe = D_8010C0A8_swing_n_swipe - Hu3DData[modelId].pos.z;
            if (HuSqrtf(D_8010C0AC_swing_n_swipe * D_8010C0AC_swing_n_swipe +
                        D_8010C0B0_swing_n_swipe * D_8010C0B0_swing_n_swipe) <= 100.0f) {
                D_8010BD5C_swing_n_swipe = 1;
                for (i = 0; i < 10; i++) {
                    D_8010BD68_swing_n_swipe[i].x = D_8010BD68_swing_n_swipe[i].y = 0.0f;
                }
                Hu3DMotionShapeSet(obj->model[0], obj->motion[5], 0);
                func_800E5690_minigame(obj, 5);
            }
        }
        if (D_8010C162_swing_n_swipe <= D_8010BD60_swing_n_swipe++ && D_8010BD5C_swing_n_swipe == 0) {
            D_8010BD60_swing_n_swipe = 0.0f;
            D_8010C0B4_swing_n_swipe =
                obj->trans.x - Hu3DData[D_8010C170_swing_n_swipe[D_8010C160_swing_n_swipe][0]].pos.x;
            D_8010C0B8_swing_n_swipe =
                obj->trans.z - Hu3DData[D_8010C170_swing_n_swipe[D_8010C160_swing_n_swipe][0]].pos.z;
            D_8010C0BC_swing_n_swipe = -atan2df(D_8010C0B4_swing_n_swipe, -D_8010C0B8_swing_n_swipe) + 270.0f;
        }
        D_8010BD68_swing_n_swipe[D_8010BDB8_swing_n_swipe].x =
            (D_8010C164_swing_n_swipe / 2) * cosdf(D_8010C0BC_swing_n_swipe);
        D_8010BD68_swing_n_swipe[D_8010BDB8_swing_n_swipe++].y =
            (D_8010C164_swing_n_swipe / 2) * sindf(D_8010C0BC_swing_n_swipe);
        for (i = 0; i < 10; i++) {
            moveX += D_8010BD68_swing_n_swipe[i].x;
            moveZ += D_8010BD68_swing_n_swipe[i].y;
        }
        moveX /= 10.0f;
        moveZ /= 10.0f;
    }
    if (D_8010BDB8_swing_n_swipe >= 10) {
        D_8010BDB8_swing_n_swipe = 0;
    }
    if (D_8010BD5C_swing_n_swipe == 1) {
        if (D_8010BDBA_swing_n_swipe == 0) {
            HuAudFXPlay(0x4F8);
            D_8010BDBA_swing_n_swipe = 1;
        }
        if (D_8010BD64_swing_n_swipe >= 7 && Hu3DData[obj->model[0]].motTime == 16.0f) {
            D_8010BD64_swing_n_swipe = 0;
            D_8010C0A4_swing_n_swipe = cosdf(obj->rot.y - 90.0f) * 100.0f + obj->trans.x;
            D_8010C0A8_swing_n_swipe = obj->trans.z - sindf(obj->rot.y - 90.0f) * 100.0f;
            for (i = 0; i < 5; i++) {
                modelId = D_8010C170_swing_n_swipe[i][0];
                D_8010C0AC_swing_n_swipe = D_8010C0A4_swing_n_swipe - Hu3DData[modelId].pos.x;
                D_8010C0B0_swing_n_swipe = D_8010C0A8_swing_n_swipe - Hu3DData[modelId].pos.z;
                if (HuSqrtf(D_8010C0AC_swing_n_swipe * D_8010C0AC_swing_n_swipe +
                            D_8010C0B0_swing_n_swipe * D_8010C0B0_swing_n_swipe) <= 125.0f) {
                    D_8010C15E_swing_n_swipe = i;
                    D_8010C148_swing_n_swipe = 5;
                    D_8010C154_swing_n_swipe = 3;
                    D_8010C15C_swing_n_swipe = 1;
                    D_8010C13C_swing_n_swipe = 0;
                    omVibrate(D_8010C144_swing_n_swipe, 2, 2, 20);
                    HuAudFXPlay(0x4F4);
                    HuAudFXPlay(0x4F5);
                    break;
                }
            }
        } else {
            D_8010BD64_swing_n_swipe++;
        }
        if (D_800CCF58_main[Hu3DData[obj->model[0]].motId].unk02 == Hu3DData[obj->model[0]].motTime &&
            D_8010BD64_swing_n_swipe >= 7) {
            D_8010BD5C_swing_n_swipe = 0;
            D_8010BD64_swing_n_swipe = 0;
            D_8010BDBA_swing_n_swipe = 0;
        }
    } else if (D_8010BD5C_swing_n_swipe == 0) {
        obj->trans.x += moveX;
        obj->trans.z -= moveZ;
        if (func_8010B920_swing_n_swipe() == 1) {
            obj->trans.x -= moveX;
            obj->trans.z += moveZ;
        }
        if (obj->trans.z > D_8010BD3C_swing_n_swipe) {
            obj->trans.z = D_8010BD3C_swing_n_swipe;
        } else if (obj->trans.z < D_8010BD34_swing_n_swipe) {
            obj->trans.z = D_8010BD34_swing_n_swipe;
        }
        if (obj->trans.x > D_8010BD38_swing_n_swipe) {
            obj->trans.x = D_8010BD38_swing_n_swipe;
        } else if (obj->trans.x < D_8010BD30_swing_n_swipe) {
            obj->trans.x = D_8010BD30_swing_n_swipe;
        }
    }
    if (moveX != 0.0f || moveZ != 0.0f) {
        if (D_8010BD5C_swing_n_swipe == 0) {
            if (Hu3DData[obj->model[0]].motTime == 0.0f) {
                CharFXPlay(0x1F, GwPlayer[D_8010C144_swing_n_swipe].chr);
            }
            Hu3DMotionShapeSet(obj->model[0], obj->motion[4], 0);
            func_800E5690_minigame(obj, 1);
            obj->rot.y = -atan2df(-moveX, -moveZ);
        }
    } else if (D_8010BD5C_swing_n_swipe == 0) {
        Hu3DMotionShapeSet(obj->model[0], obj->motion[4], 0);
        func_800E5690_minigame(obj, 0);
    }
}

void func_80107CEC_swing_n_swipe(omObjData *object) {
    s16 i;

    D_8010C170_swing_n_swipe[0][0] = func_8000B108_main(0xA0109, 0x2B9);
    D_8010C170_swing_n_swipe[0][1] = func_8000B108_main(9, 0x2B9);
    for (i = 1; i < 5; i++) {
        D_8010C170_swing_n_swipe[i][0] = Hu3DModelLink(D_8010C170_swing_n_swipe[0][0]);
        D_8010C170_swing_n_swipe[i][1] = Hu3DModelLink(D_8010C170_swing_n_swipe[0][1]);
    }
    for (i = 0; i < 5; i++) {
        Hu3DModelCameraSet(D_8010C170_swing_n_swipe[i][0], 0);
        Hu3DModelScaleSet(D_8010C170_swing_n_swipe[i][1], 1.5f, 1.0f, 1.5f);
        Hu3DModelCameraSet(D_8010C170_swing_n_swipe[i][1], 0);
    }
    D_8010C184_swing_n_swipe[0] = func_8010B8EC_swing_n_swipe(0xA0102);
    D_8010C184_swing_n_swipe[1] = func_8010B8EC_swing_n_swipe(0xA0103);
    D_8010C184_swing_n_swipe[2] = func_8010B8EC_swing_n_swipe(0xA010A);
    D_8010C184_swing_n_swipe[3] = func_8010B8EC_swing_n_swipe(0xA010B);
    D_8010C184_swing_n_swipe[4] = func_8010B8EC_swing_n_swipe(0xA010C);
    for (i = 0; i < 5; i++) {
        Hu3DMotionShiftSet(D_8010C170_swing_n_swipe[i][0], Hu3DData[D_8010C184_swing_n_swipe[0]].motId, 0, 30, 2);
    }
    D_8010C148_swing_n_swipe = 0;
    object->func = func_80107F00_swing_n_swipe;
}

void func_80107F00_swing_n_swipe(omObjData *object) {
    f32 scale;
    s16 i;

    for (i = 0; i < 5; i++) {
        if (D_8010BDBC_swing_n_swipe[i] != D_8010C14A_swing_n_swipe[i]) {
            D_8010BDBC_swing_n_swipe[i] = D_8010C14A_swing_n_swipe[i];
            switch (D_8010BDBC_swing_n_swipe[i]) {
                case 0:
                case 1:
                case 3:
                case 4:
                    Hu3DMotionShiftSet(D_8010C170_swing_n_swipe[i][0],
                                       Hu3DData[D_8010C184_swing_n_swipe[D_8010BDBC_swing_n_swipe[i]]].motId, 0, 30, 2);
                    break;
                case 2:
                    func_8001C5B4_main(D_8010C170_swing_n_swipe[i][0],
                                       D_8010C184_swing_n_swipe[D_8010BDBC_swing_n_swipe[i]]);
                    break;
            }
        }
    }
    for (i = 0; i < 5; i++) {
        scale = 1.5f - Hu3DData[D_8010C170_swing_n_swipe[i][0]].pos.y * 0.00375f;
        if (scale <= 0.0f) {
            scale = 0.0f;
        }
        Hu3DModelPosSet(D_8010C170_swing_n_swipe[i][1], Hu3DData[D_8010C170_swing_n_swipe[i][0]].pos.x, 0.0f,
                        Hu3DData[D_8010C170_swing_n_swipe[i][0]].pos.z);
        Hu3DModelScaleSet(D_8010C170_swing_n_swipe[i][1], scale, 1.0f, scale);
    }
}

void func_80108158_swing_n_swipe(void) {
    Vec startPos[5] = {
        { -575.0f, 0.0f, 600.0f },
        { -625.0f, 0.0f, 800.0f },
        { -675.0f, 0.0f, 1000.0f },
        { 625.0f, 0.0f, 800.0f },
        { 675.0f, 0.0f, 1000.0f },
    };
    Vec endPos[5] = {
        { 0.0f, 0.0f, -250.0f },
        { -190.0f, 0.0f, -50.0f },
        { -370.0f, 0.0f, 200.0f },
        { 190.0f, 0.0f, -50.0f },
        { 370.0f, 0.0f, 200.0f },
    };
    s16 model;
    s16 shadow;
    s16 other;
    f32 x;
    f32 z;
    s16 i;

    if (D_8010C148_swing_n_swipe != 1) {
        return;
    }
    for (i = 0; i < 5; i++) {
        model = D_8010C170_swing_n_swipe[i][0];
        shadow = D_8010C170_swing_n_swipe[i][1];
        other = D_8010C190_swing_n_swipe[i][0];
        switch (D_8010BDC8_swing_n_swipe[i]) {
            case 0:
                Hu3DModelPosSet(model, startPos[i].x, 0.0f, startPos[i].z);
                Hu3DModelPosSet(shadow, Hu3DData[model].pos.x, 0.0f, Hu3DData[model].pos.z);
                D_8010C14A_swing_n_swipe[i] = 1;
                Hu3DModelCameraSet(model, 1);
                Hu3DModelCameraSet(shadow, 1);
                D_8010BDC8_swing_n_swipe[i]++;
                break;
            case 1:
                x = Hu3DData[model].pos.x;
                z = Hu3DData[model].pos.z;
                if (i < 3) {
                    Hu3DData[model].pos.x += 2.5f;
                } else {
                    Hu3DData[model].pos.x -= 2.5f;
                }
                Hu3DData[model].pos.z -= 10.0f;
                Hu3DData[model].rot.y = -atan2df(z - Hu3DData[model].pos.z, x - Hu3DData[model].pos.x) + 270.0f;
                if (endPos[i].z >= Hu3DData[model].pos.z) {
                    Hu3DData[model].pos.z = endPos[i].z;
                    D_8010BDC8_swing_n_swipe[i]++;
                }
                break;
            case 2:
                if (i < 3) {
                    Hu3DData[model].rot.y -= 6.75f;
                    if (Hu3DData[model].rot.y <= 90.0f) {
                        Hu3DData[model].rot.y = 90.0f;
                        D_8010BDC8_swing_n_swipe[i]++;
                    }
                } else {
                    Hu3DData[model].rot.y += 6.75f;
                    if (Hu3DData[model].rot.y >= 270.0f) {
                        Hu3DData[model].rot.y = 270.0f;
                        D_8010BDC8_swing_n_swipe[i]++;
                    }
                }
                break;
            case 3:
                x = Hu3DData[model].pos.x;
                z = Hu3DData[model].pos.z;
                if (i < 3) {
                    Hu3DData[model].pos.x += 10.0f;
                } else {
                    Hu3DData[model].pos.x -= 10.0f;
                }
                Hu3DData[model].rot.y = -atan2df(z - Hu3DData[model].pos.z, x - Hu3DData[model].pos.x) + 270.0f;
                if (i < 3) {
                    if (endPos[i].x <= Hu3DData[model].pos.x) {
                        Hu3DData[model].pos.x = endPos[i].x;
                        D_8010BDC8_swing_n_swipe[i]++;
                    }
                } else if (endPos[i].x >= Hu3DData[model].pos.x) {
                    Hu3DData[model].pos.x = endPos[i].x;
                    D_8010BDC8_swing_n_swipe[i]++;
                }
                break;
            case 4:
                if (i < 3) {
                    Hu3DData[model].rot.y -= 6.75f;
                    if (Hu3DData[model].rot.y <= 0.0f) {
                        Hu3DData[model].rot.y = 0.0f;
                        D_8010C14A_swing_n_swipe[i] = 2;
                        D_8010BDC8_swing_n_swipe[i]++;
                    }
                } else {
                    Hu3DData[model].rot.y += 6.75f;
                    if (Hu3DData[model].rot.y >= 360.0f) {
                        Hu3DData[model].rot.y = 0;
                        D_8010C14A_swing_n_swipe[i] = 2;
                        D_8010BDC8_swing_n_swipe[i]++;
                    }
                }
                break;
            case 5:
                Hu3DData[other].pos.y = (1.0f - cosdf(D_8010BDD4_swing_n_swipe[i] * 4.5f)) * 140.0f;
                if (D_8010BDD4_swing_n_swipe[i] > 10.0f) {
                    Hu3DData[other].pos.z =
                        (endPos[i].z + 100.0f) - sindf((D_8010BDD4_swing_n_swipe[i] - 10.0f) * 9.0f) * 50.0f;
                }
                if (sindf(D_8010BDD4_swing_n_swipe[i]++ * 4.5f) == 1.0f) {
                    D_8010BDD4_swing_n_swipe[i] = 0;
                    D_8010BDC8_swing_n_swipe[i]++;
                }
                break;
            case 6:
                if (i == 0) {
                    D_8010C148_swing_n_swipe = 0;
                    D_8010C154_swing_n_swipe = 2;
                }
                break;
        }
    }
}

void func_8010897C_swing_n_swipe(void) {
    s16 work[5][5];
    f32 x;
    f32 z;
    f32 dx;
    f32 dz;
    s16 model;
    s16 i;

    if (D_8010C148_swing_n_swipe == 2) {
        for (i = 0; i < 5; i++) {
            model = D_8010C170_swing_n_swipe[i][0];
            switch (D_8010BDE0_swing_n_swipe[i]) {
                case 0:
                    D_8010C14A_swing_n_swipe[i] = 3;
                    work[i][0] = (s16)((u8)(rand8() % 180) + 90.0f) % 360;
                    work[i][1] = rand8() % 2;
                    D_8010BDE0_swing_n_swipe[i]++;
                    break;
                case 1:
                    if (work[i][1] == 0) {
                        Hu3DData[model].rot.y += 10.0f;
                        if ((u8)(rand8() % 10) == 0) {
                            if (Hu3DData[model].rot.y <= 360.0f) {
                                Hu3DData[model].rot.y -= 360.0f;
                            }
                            D_8010BDE0_swing_n_swipe[i]++;
                        }
                    } else {
                        Hu3DData[model].rot.y -= 10.0f;
                        if ((u8)(rand8() % 10) == 0) {
                            if (Hu3DData[model].rot.y < 0.0f) {
                                Hu3DData[model].rot.y += 360.0f;
                            }
                            D_8010BDE0_swing_n_swipe[i]++;
                        }
                    }
                    D_8010BDEC_swing_n_swipe[i].x = D_8010BDEC_swing_n_swipe[i].y = 0.0f;
                    break;
                case 2:
                    x = Hu3DData[model].pos.x;
                    z = Hu3DData[model].pos.z;
                    dx = cosdf(Hu3DData[model].rot.y + 270.0f) * 10.0f;
                    dz = sindf(Hu3DData[model].rot.y + 270.0f) * 10.0f;
                    Hu3DData[model].pos.x += dx;
                    Hu3DData[model].pos.z -= dz;
                    Hu3DData[model].rot.y = -atan2df(z - Hu3DData[model].pos.z, x - Hu3DData[model].pos.x) + 270.0f;
                    if (func_8010BA40_swing_n_swipe(i) == 1 || func_8010BB88_swing_n_swipe(i) == 1) {
                        Hu3DData[model].pos.x -= dx;
                        Hu3DData[model].pos.z += dz;
                        D_8010BDE0_swing_n_swipe[i]++;
                        work[i][0] = (u8)(rand8() % 180) + 90.0f;
                    } else if (Hu3DData[model].pos.x > D_8010BD38_swing_n_swipe) {
                        Hu3DData[model].pos.x = D_8010BD38_swing_n_swipe;
                        D_8010BDE0_swing_n_swipe[i]++;
                        work[i][0] = 270;
                    } else if (Hu3DData[model].pos.x < D_8010BD30_swing_n_swipe) {
                        Hu3DData[model].pos.x = D_8010BD30_swing_n_swipe;
                        D_8010BDE0_swing_n_swipe[i]++;
                        work[i][0] = 90;
                    } else if (Hu3DData[model].pos.z > D_8010BD3C_swing_n_swipe) {
                        Hu3DData[model].pos.z = D_8010BD3C_swing_n_swipe;
                        D_8010BDE0_swing_n_swipe[i]++;
                        work[i][0] = 0;
                    } else if (Hu3DData[model].pos.z < D_8010BD34_swing_n_swipe) {
                        Hu3DData[model].pos.z = D_8010BD34_swing_n_swipe;
                        D_8010BDE0_swing_n_swipe[i]++;
                        work[i][0] = 180;
                    }
                    break;
                case 3:
                    work[i][0] %= 360;
                    work[i][1] = rand8() % 2;
                    D_8010BDE0_swing_n_swipe[i] = 1;
                    break;
            }
        }
    }
    for (i = 0; i < 5; i++) {
        model = D_8010C170_swing_n_swipe[i][0];
        if (D_8010BDE0_swing_n_swipe[i] == 2) {
            if (D_8010BDEC_swing_n_swipe[i].y < 0.0f) {
                Hu3DData[model].rot.y += 3.0f;
                D_8010BDEC_swing_n_swipe[i].y += 1.0f;
            } else if (D_8010BDEC_swing_n_swipe[i].y > 0.0f) {
                Hu3DData[model].rot.y -= 3.0f;
                D_8010BDEC_swing_n_swipe[i].y -= 1.0f;
            } else {
                D_8010BDEC_swing_n_swipe[i].y = (u8)(rand8() % 80) - 40;
            }
        }
    }
}

void func_801092B4_swing_n_swipe(void) {
    omObjData *obj = D_8010C140_swing_n_swipe;
    f32 x;
    f32 z;
    s16 model;
    s16 shadow;
    s16 i;

    if (D_8010C148_swing_n_swipe == 4) {
        for (i = 0; i < 5; i++) {
            if (i == D_8010C15E_swing_n_swipe) {
                continue;
            }
            model = D_8010C170_swing_n_swipe[i][0];
            shadow = D_8010C170_swing_n_swipe[i][1];
            switch (D_8010BE14_swing_n_swipe[i]) {
                case 0:
                    D_8010C0C0_swing_n_swipe[i].x = Hu3DData[model].pos.x;
                    D_8010C0C0_swing_n_swipe[i].y = Hu3DData[model].pos.y;
                    D_8010C14A_swing_n_swipe[i] = 1;
                    Hu3DMotionSpeedSet(model, 2.0f);
                    D_8010BE20_swing_n_swipe[i] = 1;
                    D_8010BE14_swing_n_swipe[i]++;
                    break;
                case 1:
                    x = Hu3DData[model].pos.x;
                    z = Hu3DData[model].pos.z;
                    if (obj->trans.x <= x) {
                        Hu3DData[model].pos.x += 10.0f;
                    } else {
                        Hu3DData[model].pos.x -= 10.0f;
                    }
                    Hu3DData[model].pos.z += 27.0f;
                    Hu3DData[model].rot.y = -atan2df(z - Hu3DData[model].pos.z, x - Hu3DData[model].pos.x) + 270.0f;
                    if (Hu3DData[model].pos.x <= -1200.0f) {
                        D_8010BE14_swing_n_swipe[i]++;
                    }
                    break;
                case 2:
                    Hu3DModelCameraSet(model, 0);
                    Hu3DModelCameraSet(shadow, 0);
                    D_8010BE14_swing_n_swipe[i]++;
                    break;
            }
        }
    }
    if (D_8010C148_swing_n_swipe == 4 || D_8010C148_swing_n_swipe == 5) {
        for (i = 0; i < 5; i++) {
            if (i != D_8010C15E_swing_n_swipe) {
                continue;
            }
            model = D_8010C170_swing_n_swipe[i][0];
            shadow = D_8010C170_swing_n_swipe[i][1];
            switch (D_8010BE14_swing_n_swipe[i]) {
                case 0:
                    D_8010BE30_swing_n_swipe = D_8010C140_swing_n_swipe->rot.y + 270.0f;
                    D_8010BE2C_swing_n_swipe = -2.0f;
                    Hu3DData[model].rot.y = D_8010BE30_swing_n_swipe;
                    D_8010C14A_swing_n_swipe[i] = 3;
                    D_8010BE14_swing_n_swipe[i]++;
                    break;
                case 1:
                    Hu3DData[model].pos.x -= cosdf(D_8010BE30_swing_n_swipe + 270.0f) * 100.0f;
                    Hu3DData[model].pos.z += sindf(D_8010BE30_swing_n_swipe + 270.0f) * 100.0f;
                    Hu3DData[model].pos.y += D_8010BE2C_swing_n_swipe * D_8010BE2C_swing_n_swipe *
                                             ((D_8010BE2C_swing_n_swipe <= 0.0f) ? 17.5f : -17.5f);
                    if (Hu3DData[model].pos.z <= -4000.0f && Hu3DData[model].scale.x > 0.0f) {
                        Hu3DData[model].scale.x = Hu3DData[model].scale.y = Hu3DData[model].scale.z -= 0.025f;
                    }
                    if (D_8010BE2C_swing_n_swipe <= 0.0f) {
                        D_8010BE2C_swing_n_swipe += 0.11f;
                    } else {
                        D_8010BE2C_swing_n_swipe = 0.0f;
                    }
                    if (sindf(D_8010BE20_swing_n_swipe[i] * 3.0f) != 1.0f) {
                        Hu3DData[model].rot.x = 0.0f - sindf(D_8010BE20_swing_n_swipe[i]++ * 3.0f) * 90.0f;
                    } else {
                        Hu3DData[model].rot.x = -90.0f;
                    }
                    if (Hu3DData[model].pos.x >= 5000.0f || Hu3DData[model].pos.x <= -5000.0f ||
                        Hu3DData[model].pos.z >= 5000.0f || Hu3DData[model].pos.z <= -6000.0f) {
                        D_8010BE14_swing_n_swipe[i]++;
                    }
                    break;
                case 2:
                    Hu3DModelCameraSet(model, 0);
                    Hu3DModelCameraSet(shadow, 0);
                    D_8010BE14_swing_n_swipe[i]++;
                    break;
            }
            break;
        }
    }
}

void func_801099E8_swing_n_swipe(void) {
    Vec targetPos[5] = {
        { -370.0f, 0.0f, 325.0f },
        { -190.0f, 0.0f, 100.0f },
        { 0.0f, 0.0f, -150.0f },
        { 190.0f, 0.0f, 100.0f },
        { 370.0f, 0.0f, 325.0f },
    };
    f32 x;
    f32 z;
    s16 model;
    s16 rank;
    s16 i;
    s16 j;

    if (D_8010BE34_swing_n_swipe[0] == 0) {
        rank = 0;
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                if (i != j && Hu3DData[D_8010C170_swing_n_swipe[i][0]].pos.x >
                                  Hu3DData[D_8010C170_swing_n_swipe[j][0]].pos.x) {
                    rank++;
                }
            }
            D_8010BE4C_swing_n_swipe[i] = rank;
            rank = 0;
        }
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                if (i != j && D_8010BE4C_swing_n_swipe[i] == D_8010BE4C_swing_n_swipe[j]) {
                    D_8010BE4C_swing_n_swipe[j]++;
                    i = 0;
                    break;
                }
            }
        }
    }
    if (D_8010C148_swing_n_swipe == 3) {
        for (i = 0; i < 5; i++) {
            model = D_8010C170_swing_n_swipe[i][0];
            switch (D_8010BE34_swing_n_swipe[i]) {
                case 0:
                    D_8010C100_swing_n_swipe[i].x = Hu3DData[model].pos.x;
                    D_8010C100_swing_n_swipe[i].z = Hu3DData[model].pos.z;
                    D_8010C14A_swing_n_swipe[i] = 1;
                    D_8010BE34_swing_n_swipe[i]++;
                    break;
                case 1:
                    x = Hu3DData[model].pos.x;
                    z = Hu3DData[model].pos.z;
                    Hu3DData[model].pos.x =
                        D_8010C100_swing_n_swipe[i].x -
                        sindf(D_8010BE40_swing_n_swipe[i] * 1.5f) *
                            (D_8010C100_swing_n_swipe[i].x - targetPos[D_8010BE4C_swing_n_swipe[i]].x);
                    Hu3DData[model].pos.z =
                        D_8010C100_swing_n_swipe[i].z -
                        sindf(D_8010BE40_swing_n_swipe[i] * 1.5f) *
                            (D_8010C100_swing_n_swipe[i].z - targetPos[D_8010BE4C_swing_n_swipe[i]].z);
                    Hu3DData[model].rot.y = -atan2df(z - Hu3DData[model].pos.z, x - Hu3DData[model].pos.x) + 270.0f;
                    if (sindf(D_8010BE40_swing_n_swipe[i]++ * 1.5f) == 1.0f) {
                        Hu3DData[model].pos.x = targetPos[D_8010BE4C_swing_n_swipe[i]].x;
                        Hu3DData[model].pos.z = targetPos[D_8010BE4C_swing_n_swipe[i]].z;
                        D_8010BE40_swing_n_swipe[i] = 0;
                        D_8010BE34_swing_n_swipe[i]++;
                    }
                    break;
                case 2:
                    if (Hu3DData[model].rot.y >= 360.0f) {
                        Hu3DData[model].rot.y -= 360.0f;
                    }
                    if (Hu3DData[model].rot.y < 0.0f) {
                        Hu3DData[model].rot.y += 360.0f;
                    }
                    if (Hu3DData[model].rot.y >= 180.0f) {
                        Hu3DData[model].rot.y += 6.75f;
                        if (Hu3DData[model].rot.y >= 360.0f) {
                            Hu3DData[model].rot.y = 0;
                            D_8010BE34_swing_n_swipe[i]++;
                        }
                    } else if (Hu3DData[model].rot.y > 0.0f) {
                        Hu3DData[model].rot.y -= 6.75f;
                        if (Hu3DData[model].rot.y <= 0.0f) {
                            Hu3DData[model].rot.y = 0.0f;
                            D_8010BE34_swing_n_swipe[i]++;
                        }
                    } else if (Hu3DData[model].rot.y == 0.0f) {
                        Hu3DData[model].pos.y = 0.0f;
                        D_8010BE34_swing_n_swipe[i]++;
                    }
                    break;
                case 3:
                    D_8010C14A_swing_n_swipe[i] = 0;
                    D_8010BE34_swing_n_swipe[i]++;
                    break;
            }
        }
    }
}

void func_8010A0E4_swing_n_swipe(omObjData *object) {
    s16 i;

    D_8010C190_swing_n_swipe[0][0] = func_8000B108_main(0x610001, 0x2B9);
    D_8010C190_swing_n_swipe[0][2] = func_8000B108_main(9, 0x2B9);
    for (i = 1; i < 5; i++) {
        D_8010C190_swing_n_swipe[i][0] = Hu3DModelLink(D_8010C190_swing_n_swipe[0][0]);
        D_8010C190_swing_n_swipe[i][2] = Hu3DModelLink(D_8010C190_swing_n_swipe[0][2]);
    }
    for (i = 0; i < 5; i++) {
        Hu3DModelPosSet(D_8010C190_swing_n_swipe[i][0], D_8010BE58_swing_n_swipe[i].x, D_8010BE58_swing_n_swipe[i].y,
                        D_8010BE58_swing_n_swipe[i].z);
        Hu3DModelScaleSet(D_8010C190_swing_n_swipe[i][0], 1.5f, 1.5f, 1.5f);
        Hu3DMotionSpeedSet(D_8010C190_swing_n_swipe[i][0], 0.0f);
        D_8010C190_swing_n_swipe[i][1] =
            D_800CBB60_main[(s16)SprModelRead(D_8010BE94_swing_n_swipe[D_800A11D0_main[i]], 0xA0, 0x10)].modelId;
        Hu3DModelPosSet(D_8010C190_swing_n_swipe[i][1], Hu3DData[D_8010C190_swing_n_swipe[i][0]].pos.x, 1000.0f,
                        Hu3DData[D_8010C190_swing_n_swipe[i][0]].pos.z);
        Hu3DModelScaleSet(D_8010C190_swing_n_swipe[i][1], 3.0f, 3.0f, 3.0f);
        Hu3DModelCameraSet(D_8010C190_swing_n_swipe[i][1], 0);
        Hu3DModelPosSet(D_8010C190_swing_n_swipe[i][2], Hu3DData[D_8010C190_swing_n_swipe[i][0]].pos.x, 0.0f,
                        Hu3DData[D_8010C190_swing_n_swipe[i][0]].pos.z);
        Hu3DModelScaleSet(D_8010C190_swing_n_swipe[i][2], 1.5f, 1.0f, 1.5f);
    }
    D_8010C1B8_swing_n_swipe[0] = func_8000CED8_main(0xB0004, 0x2A9);
    func_800138EC_main(D_8010C1B8_swing_n_swipe[0], 1, 0);
    D_8010C1B8_swing_n_swipe[1] = func_8000B108_main(9, 0x2B9);
    Hu3DModelScaleSet(D_8010C1B8_swing_n_swipe[1], 1.0f, 1.0f, 1.0f);
    Hu3DModelCameraSet(D_8010C1B8_swing_n_swipe[1], 0);
    D_8010C154_swing_n_swipe = 0;
    object->func = func_8010B01C_swing_n_swipe;
}

void func_8010A3FC_swing_n_swipe(void) {
    s16 i;

    if (D_8010C154_swing_n_swipe == 1) {
        switch (D_8010BEE4_swing_n_swipe) {
            case 0:
                for (i = 0; i < 5; i++) {
                    Hu3DMotionSpeedSet(D_8010C190_swing_n_swipe[i][0], 1.0f);
                    Hu3DModelCameraSet(D_8010C190_swing_n_swipe[i][1], 1);
                }
                HuAudFXPlay(0x4F1);
                D_8010BEE4_swing_n_swipe++;
                break;
            case 1:
                for (i = 0; i < 5; i++) {
                    Hu3DData[D_8010C190_swing_n_swipe[i][1]].pos.y =
                        1000.0f - sindf(D_8010BEE6_swing_n_swipe * 0.75f) * 960.0f;
                    if (D_8010BEE6_swing_n_swipe >= 100 && Hu3DData[D_8010C190_swing_n_swipe[i][1]].scale.x > 2.0f) {
                        Hu3DData[D_8010C190_swing_n_swipe[i][1]].scale.x =
                            Hu3DData[D_8010C190_swing_n_swipe[i][1]].scale.y =
                                Hu3DData[D_8010C190_swing_n_swipe[i][1]].scale.z -= 0.1f;
                    }
                }
                if (sindf(D_8010BEE6_swing_n_swipe++ * 0.75f) == 1.0f) {
                    D_8010BEE4_swing_n_swipe++;
                    HuAudFXPlay(0x4F0);
                }
                break;
            case 2:
                for (i = 0; i < 5; i++) {
                    Hu3DMotionSpeedSet(D_8010C190_swing_n_swipe[i][0], -1.0f);
                }
                if (Hu3DData[D_8010C190_swing_n_swipe[0][0]].motTime <= 0.0f) {
                    for (i = 0; i < 5; i++) {
                        Hu3DMotionSpeedSet(D_8010C190_swing_n_swipe[i][0], 0.0f);
                        Hu3DMotionTimeSet(D_8010C190_swing_n_swipe[i][0], 0.0f);
                        Hu3DModelCameraSet(D_8010C190_swing_n_swipe[i][1], 0);
                    }
                    D_8010BEE4_swing_n_swipe++;
                }
                break;
            case 3:
                D_8010BEE6_swing_n_swipe = 0;
                D_8010BEE4_swing_n_swipe = 0;
                D_8010C154_swing_n_swipe = 0;
                break;
        }
    }
}

void func_8010A780_swing_n_swipe(void) {
    s16 i;

    if (D_8010C154_swing_n_swipe == 2) {
        for (i = 0; i < 5; i++) {
            Hu3DData[D_8010C190_swing_n_swipe[i][0]].pos.x =
                Hu3DData[D_8010C170_swing_n_swipe[i][0]].pos.x +
                cosdf(Hu3DData[D_8010C170_swing_n_swipe[i][0]].rot.y + 270.0f) * 50.0f;
            Hu3DData[D_8010C190_swing_n_swipe[i][0]].pos.y = Hu3DData[D_8010C170_swing_n_swipe[i][0]].pos.y + 140.0f;
            Hu3DData[D_8010C190_swing_n_swipe[i][0]].pos.z =
                Hu3DData[D_8010C170_swing_n_swipe[i][0]].pos.z -
                sindf(Hu3DData[D_8010C170_swing_n_swipe[i][0]].rot.y + 270.0f) * 50.0f;
            Hu3DData[D_8010C190_swing_n_swipe[i][0]].rot.y = Hu3DData[D_8010C170_swing_n_swipe[i][0]].rot.y;
        }
    }
}

void func_8010A994_swing_n_swipe(void) {
    s16 index = D_8010C15E_swing_n_swipe;

    if (D_8010C154_swing_n_swipe == 3) {
        Hu3DData[D_8010C190_swing_n_swipe[index][0]].pos.y -= 10.0f;
        if (Hu3DData[D_8010C190_swing_n_swipe[index][0]].pos.y <= 0.0f) {
            Hu3DData[D_8010C190_swing_n_swipe[index][0]].pos.y = 0.0f;
            D_8010C154_swing_n_swipe = 0;
        }
    }
}

void func_8010AA3C_swing_n_swipe(void) {
    s16 index;

    if (D_8010C154_swing_n_swipe == 4) {
        index = D_8010C15E_swing_n_swipe;
        switch (D_8010BEE8_swing_n_swipe) {
            case 0:
                Hu3DModelPosSet(D_8010C190_swing_n_swipe[index][1], Hu3DData[D_8010C190_swing_n_swipe[index][0]].pos.x,
                                40.0f, Hu3DData[D_8010C190_swing_n_swipe[index][0]].pos.z);
                Hu3DModelCameraSet(D_8010C190_swing_n_swipe[index][1], 1);
                Hu3DMotionSpeedSet(D_8010C190_swing_n_swipe[index][0], 1.0f);
                HuAudFXPlay(0x4F7);
                D_8010BEE8_swing_n_swipe++;
                break;
            case 1:
                if (D_800CCF58_main[Hu3DData[D_8010C190_swing_n_swipe[index][0]].motId].unk02 ==
                    Hu3DData[D_8010C190_swing_n_swipe[index][0]].motTime) {
                    HuAudFXPlay(0x4F3);
                    func_800138EC_main(D_8010C1B8_swing_n_swipe[0], 1, 1);
                    func_8000CD00_main(D_8010C1B8_swing_n_swipe[0], 5.0f, 20.0f, 10.0f);
                    func_8000D018_main(D_8010C1B8_swing_n_swipe[0], 100.0f);
                    func_8000CFA4_main(D_8010C1B8_swing_n_swipe[0], Hu3DData[D_8010C190_swing_n_swipe[index][1]].pos.x,
                                       Hu3DData[D_8010C190_swing_n_swipe[index][1]].pos.y,
                                       Hu3DData[D_8010C190_swing_n_swipe[index][1]].pos.z);
                    Hu3DModelCameraSet(D_8010C1B8_swing_n_swipe[1], 1);
                    Hu3DModelPosSet(D_8010C1B8_swing_n_swipe[1], Hu3DData[D_8010C190_swing_n_swipe[index][1]].pos.x,
                                    0.0f, Hu3DData[D_8010C190_swing_n_swipe[index][1]].pos.z);
                    D_8010C158_swing_n_swipe = 1;
                    D_8010BEE8_swing_n_swipe++;
                }
                break;
            case 2:
                Hu3DData[D_8010C190_swing_n_swipe[index][1]].pos.y =
                    40.0f - sindf(D_8010BEEA_swing_n_swipe * 3.0f) * -310.0f;
                if (D_8010BEEA_swing_n_swipe >= 10 && Hu3DData[D_8010C190_swing_n_swipe[index][1]].scale.x < 3.0f) {
                    Hu3DData[D_8010C190_swing_n_swipe[index][1]].scale.x =
                        Hu3DData[D_8010C190_swing_n_swipe[index][1]].scale.y =
                            Hu3DData[D_8010C190_swing_n_swipe[index][1]].scale.z += 0.1f;
                }
                if (sindf(D_8010BEEA_swing_n_swipe++ * 3.0f) == 1.0f) {
                    D_8010BEEA_swing_n_swipe = 0;
                    D_8010BEE8_swing_n_swipe++;
                }
                break;
            case 3:
                Hu3DData[D_8010C190_swing_n_swipe[index][1]].pos.x =
                    Hu3DData[D_8010C190_swing_n_swipe[index][0]].pos.x -
                    sindf(D_8010BEEA_swing_n_swipe * 3.0f) * Hu3DData[D_8010C190_swing_n_swipe[index][0]].pos.x;
                Hu3DData[D_8010C190_swing_n_swipe[index][1]].pos.z =
                    Hu3DData[D_8010C190_swing_n_swipe[index][0]].pos.z -
                    sindf(D_8010BEEA_swing_n_swipe * 3.0f) *
                        (Hu3DData[D_8010C190_swing_n_swipe[index][0]].pos.z - 400.0f);
                if (sindf(D_8010BEEA_swing_n_swipe++ * 3.0f) == 1.0f) {
                    D_8010BEEA_swing_n_swipe = 0;
                    D_8010BEE8_swing_n_swipe++;
                }
                break;
            case 4:
                Hu3DData[D_8010C190_swing_n_swipe[index][1]].pos.y =
                    sindf(D_8010BEEA_swing_n_swipe * 6.0f) * 10.0f + 350.0f;
                if (D_8010BEEA_swing_n_swipe++ >= 60) {
                    D_8010BEEA_swing_n_swipe = 0;
                }
                break;
        }
        func_8000CFA4_main(D_8010C1B8_swing_n_swipe[0], Hu3DData[D_8010C190_swing_n_swipe[index][1]].pos.x,
                           Hu3DData[D_8010C190_swing_n_swipe[index][1]].pos.y,
                           Hu3DData[D_8010C190_swing_n_swipe[index][1]].pos.z);
        Hu3DModelPosSet(D_8010C1B8_swing_n_swipe[1], Hu3DData[D_8010C190_swing_n_swipe[index][1]].pos.x, 0.0f,
                        Hu3DData[D_8010C190_swing_n_swipe[index][1]].pos.z);
    }
}

void func_8010B01C_swing_n_swipe(omObjData *object) {
    f32 scale;
    s16 i;

    for (i = 0; i < 5; i++) {
        scale = 1.5f - Hu3DData[D_8010C190_swing_n_swipe[i][0]].pos.y * 0.010714286f;
        Hu3DModelPosSet(D_8010C190_swing_n_swipe[i][2], Hu3DData[D_8010C190_swing_n_swipe[i][0]].pos.x, 0.0f,
                        Hu3DData[D_8010C190_swing_n_swipe[i][0]].pos.z);
        Hu3DModelScaleSet(D_8010C190_swing_n_swipe[i][2], scale, 1.0f, scale);
    }
}

void func_8010B100_swing_n_swipe(omObjData *object) {
    s16 i;

    for (i = 0; i < 5; i++) {
        D_8010C1C0_swing_n_swipe[i] = func_8000B108_main(0x610005, 0x2B9);
        Hu3DModelScaleSet(D_8010C1C0_swing_n_swipe[i], 1.5f, 1.5f, 1.0f);
        Hu3DModelCameraSet(D_8010C1C0_swing_n_swipe[i], 0);
    }
    D_8010C1D0_swing_n_swipe[0] = func_8010B8EC_swing_n_swipe(0x610005);
    D_8010C1CC_swing_n_swipe[0] = func_8000B108_main(0xB0006, 0x2B9);
    D_8010C1D0_swing_n_swipe[1] = func_8010B8EC_swing_n_swipe(0xB0006);
    Hu3DModelCameraSet(D_8010C1CC_swing_n_swipe[0], 0);
    D_8010C1CC_swing_n_swipe[1] = func_8000B108_main(0x610004, 0x2B9);
    D_8010C1D0_swing_n_swipe[2] = func_8010B8EC_swing_n_swipe(0x610004);
    Hu3DModelCameraSet(D_8010C1CC_swing_n_swipe[1], 0);
    object->func = func_8010B23C_swing_n_swipe;
}

void func_8010B23C_swing_n_swipe(omObjData *object) {
    s16 i;
    s16 skip;
    s16 index;
    s16 model;
    f32 x;
    f32 y;
    f32 z;

    if (D_8010C156_swing_n_swipe == 1) {
        skip = (D_8010C13C_swing_n_swipe == 0) ? D_8010C15E_swing_n_swipe : -1;
        for (i = 0; i < 5; i++) {
            if (i != skip) {
                x = Hu3DData[D_8010C170_swing_n_swipe[i][0]].pos.x;
                y = Hu3DData[D_8010C170_swing_n_swipe[i][0]].pos.y + 125.0f;
                z = Hu3DData[D_8010C170_swing_n_swipe[i][0]].pos.z + 50.0f;
                Hu3DModelPosSet(D_8010C1C0_swing_n_swipe[i], x, y, z);
                Hu3DModelCameraSet(D_8010C1C0_swing_n_swipe[i], 1);
                func_8001C5B4_main(D_8010C1C0_swing_n_swipe[i], D_8010C1D0_swing_n_swipe[0]);
                Hu3DModelCameraSet(D_8010C190_swing_n_swipe[i][0], 0);
                Hu3DModelCameraSet(D_8010C190_swing_n_swipe[i][1], 0);
                Hu3DModelCameraSet(D_8010C190_swing_n_swipe[i][2], 0);
            }
        }
        HuAudFXPlay(0x4F2);
        D_8010C156_swing_n_swipe = 2;
    }
    if (D_8010C156_swing_n_swipe == 2 &&
        D_800CCF58_main[Hu3DData[D_8010C1C0_swing_n_swipe[0]].motId].unk02 ==
            Hu3DData[D_8010C1C0_swing_n_swipe[0]].motTime) {
        do {
            for (i = 0; i < 5; i++) {
                if (i != D_8010C15E_swing_n_swipe) {
                    Hu3DModelCameraSet(D_8010C1C0_swing_n_swipe[i], 0);
                }
            }
        } while (0); // TODO: required to match (loop depth affects i register allocation)
    }
    if (D_8010C158_swing_n_swipe == 1) {
        index = D_8010C15E_swing_n_swipe;
        z = Hu3DData[D_8010C190_swing_n_swipe[index][0]].pos.z + 50.0f;
        Hu3DModelPosSet(D_8010C1C0_swing_n_swipe[index], Hu3DData[D_8010C190_swing_n_swipe[index][0]].pos.x, 10.0f, z);
        Hu3DModelCameraSet(D_8010C1C0_swing_n_swipe[index], 1);
        func_8001C5B4_main(D_8010C1C0_swing_n_swipe[index], D_8010C1D0_swing_n_swipe[0]);
        Hu3DModelCameraSet(D_8010C190_swing_n_swipe[index][0], 0);
        Hu3DModelCameraSet(D_8010C190_swing_n_swipe[index][2], 0);
        D_8010C146_swing_n_swipe = 3;
        D_8010C15A_swing_n_swipe = 1;
        D_8010C158_swing_n_swipe = 2;
    } else if (D_8010C158_swing_n_swipe == 2) {
        model = D_8010C1C0_swing_n_swipe[D_8010C15E_swing_n_swipe];
        if (D_800CCF58_main[Hu3DData[model].motId].unk02 == Hu3DData[model].motTime) {
            Hu3DModelCameraSet(model, 0);
        }
    }
    if (D_8010C15A_swing_n_swipe == 1) {
        Hu3DModelPosSet(D_8010C1CC_swing_n_swipe[0], D_8010C140_swing_n_swipe->trans.x, 100.0f,
                        D_8010C140_swing_n_swipe->trans.z + 150.0f);
        Hu3DModelCameraSet(D_8010C1CC_swing_n_swipe[0], 1);
        func_8001C5B4_main(D_8010C1CC_swing_n_swipe[0], D_8010C1D0_swing_n_swipe[1]);
        Hu3DModelCameraSet(D_8010C166_swing_n_swipe, 0);
        D_8010C15A_swing_n_swipe = 2;
    }
    if (D_8010C15A_swing_n_swipe == 2) {
        model = D_8010C1CC_swing_n_swipe[0];
        if (D_800CCF58_main[Hu3DData[model].motId].unk02 == Hu3DData[model].motTime) {
            Hu3DModelCameraSet(model, 0);
        }
    }
    if (D_8010C15C_swing_n_swipe == 1) {
        x = D_8010C140_swing_n_swipe->trans.x + cosdf(D_8010C140_swing_n_swipe->rot.y - 90.0f) * 100.0f;
        Hu3DModelPosSet(D_8010C1CC_swing_n_swipe[1], x, 50.0f,
                        D_8010C140_swing_n_swipe->trans.z + sindf(D_8010C140_swing_n_swipe->rot.y - 90.0f) * 100.0f);
        Hu3DModelCameraSet(D_8010C1CC_swing_n_swipe[1], 1);
        func_8001C5B4_main(D_8010C1CC_swing_n_swipe[1], D_8010C1D0_swing_n_swipe[2]);
        D_8010C15C_swing_n_swipe = 2;
    }
    if (D_8010C15C_swing_n_swipe == 2) {
        model = D_8010C1CC_swing_n_swipe[1];
        if (D_800CCF58_main[Hu3DData[model].motId].unk02 == Hu3DData[model].motTime) {
            Hu3DModelCameraSet(model, 0);
        }
    }
}

s16 func_8010B840_swing_n_swipe(s32 dataNum, u16 attr, u16 pri, s16 x, s16 y) {
    s16 sprite = espEntry(HuSprAnimDataRead(dataNum), 0, 0);

    espAttrSet(sprite, attr);
    espPriSet(sprite, pri);
    espPosSet(sprite, x, y);
    return sprite;
}

s16 func_8010B8EC_swing_n_swipe(s32 arg0) {
    s16 temp = func_8000B13C_main(arg0);

    if (temp < 0) {
        temp = -1;
    }
    return temp;
}

s16 func_8010B920_swing_n_swipe(void) {
    omObjData *obj = D_8010C140_swing_n_swipe;
    f32 x;
    f32 z;
    f32 dx;
    f32 dz;
    f32 px;
    f32 pz;
    s16 i;
    s16 j;

    x = obj->trans.x + cosdf(obj->rot.y - 90.0f) * 50.0f;
    pz = obj->trans.z - sindf(obj->rot.y - 90.0f) * 50.0f;
    z = pz;
    j = 3;
    for (i = 0; i < 5; i++) {
        // TODO: `j` is an otherwise unused variable that the original code
        // keeps live (dead `li s1, 3`); `i + j - j` is an unknown stand-in.
        px = Hu3DData[D_8010C170_swing_n_swipe[i + j - j][0]].pos.x;
        pz = Hu3DData[D_8010C170_swing_n_swipe[i + j - j][0]].pos.z;
        dx = x - px;
        dz = z - pz;
        // The do-while(0) raises the loop depth weighting of the 100.0f
        // constant use, needed to match float register allocation.
        do {
            if (HuSqrtf(dx * dx + dz * dz) < 100.0f) {
                return 1;
            }
        } while (0);
    }
    return 0;
}

s16 func_8010BA40_swing_n_swipe(s16 index) {
    omObjData *obj = D_8010C140_swing_n_swipe;
    f32 x;
    f32 z;
    f32 dx;
    f32 dz;

    x = Hu3DData[D_8010C170_swing_n_swipe[index][0]].pos.x +
        cosdf(Hu3DData[D_8010C170_swing_n_swipe[index][0]].rot.y - 90.0f) * 50.0f;
    z = Hu3DData[D_8010C170_swing_n_swipe[index][0]].pos.z -
        sindf(Hu3DData[D_8010C170_swing_n_swipe[index][0]].rot.y - 90.0f) * 50.0f;
    dx = obj->trans.x;
    dz = obj->trans.z;
    dx -= x;
    dz -= z;
    if (HuSqrtf(dx * dx + dz * dz) < 150.0f) {
        return 1;
    }
    return 0;
}

s16 func_8010BB88_swing_n_swipe(s16 index) {
    f32 x;
    f32 z;
    f32 dx;
    f32 dz;
    s16 i;

    x = Hu3DData[D_8010C170_swing_n_swipe[index][0]].pos.x +
        cosdf(Hu3DData[D_8010C170_swing_n_swipe[index][0]].rot.y - 90.0f) * 50.0f;
    z = Hu3DData[D_8010C170_swing_n_swipe[index][0]].pos.z -
        sindf(Hu3DData[D_8010C170_swing_n_swipe[index][0]].rot.y - 90.0f) * 50.0f;
    for (i = 0; i < 5; i++) {
        if (index == i) {
            continue;
        }
        dx = Hu3DData[D_8010C170_swing_n_swipe[i][0]].pos.x;
        dz = Hu3DData[D_8010C170_swing_n_swipe[i][0]].pos.z;
        dx -= x;
        dz -= z;
        if (HuSqrtf(dx * dx + dz * dz) < 150.0f) {
            return 1;
        }
    }
    return 0;
}
