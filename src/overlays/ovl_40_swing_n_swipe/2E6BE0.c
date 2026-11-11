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

extern u16 D_800A11D0_main[];
extern s32 D_800A178C_main[][6];
extern u16 D_800A11DC_main[];
extern s16 D_8010BD40_swing_n_swipe; // state
extern s16 D_8010BD42_swing_n_swipe; // timer
extern s16 D_8010BD44_swing_n_swipe;
extern s16 D_8010BD46_swing_n_swipe;
extern s16 D_8010BD48_swing_n_swipe;
extern s16 D_8010BD4A_swing_n_swipe;
extern s16 D_8010BD4C_swing_n_swipe;
extern SwingNSwipeGroupOrder D_8010BEF0_swing_n_swipe;
extern SwingNSwipeCpuOffsets D_8010BEF8_swing_n_swipe;
extern SwingNSwipeCpuSpeeds D_8010BF00_swing_n_swipe;
extern s16 D_8010C13C_swing_n_swipe;
extern omObjData *D_8010C140_swing_n_swipe;
extern s16 D_8010C144_swing_n_swipe;
extern s16 D_8010C146_swing_n_swipe;
extern s16 D_8010C148_swing_n_swipe;
extern s16 D_8010C14A_swing_n_swipe[5];
extern s16 D_8010C154_swing_n_swipe;
extern s16 D_8010C156_swing_n_swipe;
extern s16 D_8010C15A_swing_n_swipe;
extern s16 D_8010C15E_swing_n_swipe;
extern s16 D_8010C166_swing_n_swipe;
extern s16 D_8010C168_swing_n_swipe;
extern s16 D_8010C160_swing_n_swipe;
extern s16 D_8010C162_swing_n_swipe;
extern s16 D_8010C164_swing_n_swipe;

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
void func_80108158_swing_n_swipe(void);
void func_8010A0E4_swing_n_swipe(omObjData *object);
void func_8010B100_swing_n_swipe(omObjData *object);
void func_8010897C_swing_n_swipe(void);
void func_801092B4_swing_n_swipe(void);
void func_801099E8_swing_n_swipe(void);
void func_8010A3FC_swing_n_swipe(void);
void func_8010A780_swing_n_swipe(void);
void func_8010A994_swing_n_swipe(void);
void func_8010AA3C_swing_n_swipe(void);
s16 func_8010B840_swing_n_swipe(s32 dataNum, u16 attr, u16 pri, s16 x, s16 y);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_80106AD0_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_801072D0_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_80107CEC_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_80107F00_swing_n_swipe);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", D_8010BF9C_swing_n_swipe);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", D_8010BFD8_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_80108158_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010897C_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_801092B4_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_801099E8_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010A0E4_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010A3FC_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010A780_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010A994_swing_n_swipe);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", D_8010C034_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010AA3C_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010B01C_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010B100_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010B23C_swing_n_swipe);

void func_8010897C_swing_n_swipe(void);
void func_801092B4_swing_n_swipe(void);
void func_801099E8_swing_n_swipe(void);
void func_8010A3FC_swing_n_swipe(void);
void func_8010A780_swing_n_swipe(void);
void func_8010A994_swing_n_swipe(void);
void func_8010AA3C_swing_n_swipe(void);
s16 func_8010B840_swing_n_swipe(s32 dataNum, u16 attr, u16 pri, s16 x, s16 y) {
    s16 sprite = espEntry(func_8000B838_main(dataNum), 0, 0);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010B920_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010BA40_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010BB88_swing_n_swipe);
