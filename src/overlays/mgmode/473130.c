#include "common.h"
#include "overlays/mgmode.h"

extern MgmodeEsprite *D_8011B450_mgmode;
extern s16 D_8011B454_mgmode;
extern s16 D_8011B458_mgmode[8];
extern u8 D_8011B430_mgmode[4];
extern u8 D_8011B434_mgmode;
extern s16 D_800CC438_main;
extern s16 D_800CE29C_main;
extern s16 D_800D03FE_main[4];
extern u8 D_80119430_mgmode[];
extern s16 D_800D4194_main;
extern s16 D_800D0418_main[8];
extern u8 D_8011B6B0_mgmode[][25];
extern s16 D_8011B928_mgmode[];
extern s16 D_8011B940_mgmode[];
extern s16 D_8011B6A8_mgmode;
extern MgmodeSpaceCoord D_80119424_mgmode[];
extern u8 D_800D1F20_main[4];
extern s16 D_8011B8B6_mgmode[];
extern s16 D_8011B8E8_mgmode[];
extern s16 D_8011B8A8_mgmode[];
extern s16 D_8011B796_mgmode[];
extern s16 D_8011B78C_mgmode;
extern s16 D_8011B788_mgmode;
extern s16 D_80119340_mgmode;
extern s16 D_800D1F2C_main;
extern MgmodeEsprite *D_8011B480_mgmode;
extern s16 D_8011B484_mgmode;
extern u16 D_8011B488_mgmode[28];
extern s16 D_8011B808_mgmode;
extern MgmodeSpaceCoord D_8011943C_mgmode[];
extern s16 D_8011944C_mgmode[];

void func_8010CBFC_mgmode(void);
void func_801168E0_mgmode(MgmodeEsprite *arg0);
void func_801169C8_mgmode(MgmodeEsprite *arg0, s16 index);
void func_80116A78_mgmode(MgmodeEsprite *arg0, s16 index, s16 tpLvl);
void func_80116A48_mgmode(MgmodeEsprite *arg0, s16 index, f32 x, f32 y);
void func_80118888_mgmode(s16 index);
void func_801188A4_mgmode(s16 index);
s16 func_80116B20_mgmode(void);
void func_80116C18_mgmode(s16 arg0);
void func_80118624_mgmode(s16 dstModel, s16 srcModel);
void func_80116968_mgmode(MgmodeEsprite *arg0, s16 index, s16 arg2, s16 arg3);
void func_801169A0_mgmode(MgmodeEsprite *arg0, s16 index);
void func_8011829C_mgmode(s16 arg0);
void func_801182A8_mgmode(s16 arg0);
s16 func_801182DC_mgmode(s16 stickX, s16 stickY);
void func_80118D0C_mgmode(void);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010BEC0_mgmode);

void func_8010CB20_mgmode(void) {
    HuWinMesSet(D_8011B6A8_mgmode, 0x5607, -1, -1);
    while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
        HuPrcVSleep();
    }
    func_80116ED4_mgmode(2, 10, 1, (void (*)(s16 *))-1);
    func_8010CBFC_mgmode();
    func_80116ED4_mgmode(5, 10, 1, (void (*)(s16 *))-1);
    func_8011822C_mgmode(D_80119424_mgmode);
    func_801181F4_mgmode(0);
    func_801182B4_mgmode(1);
    HuWinMesSet(D_8011B6A8_mgmode, 0x5600, -1, -1);
    while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010CBFC_mgmode);

void func_8010D308_mgmode(void) {
    s16 i;
    f32 scale;

    HuAudFXPlay(0x244);
    for (i = 0; i < 11; i++) {
        scale = cosdf(i / 10.0f * 90.0f);
        func_80116A48_mgmode(D_8011B450_mgmode, 0, scale, scale);
        HuPrcVSleep();
    }
}

s16 func_8010D3B0_mgmode(s32 arg0) {
    s16 i;
    s16 j;
    s16 frame;
    s16 next;
    s16 sel;
    f32 dist;

    if (arg0 != 0) {
        for (i = 1; i < 6; i++) {
            func_80116A48_mgmode(D_8011B450_mgmode, D_800CC438_main + 1, 1.0f, cosdf(i / 5.0f * 90.0f));
            HuPrcVSleep();
        }
        func_801169C8_mgmode(D_8011B450_mgmode, D_800CC438_main + 1);
    }
    HuWinMesSet(D_8011B6A8_mgmode, 0x5608, -1, -1);
    while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
        HuPrcVSleep();
    }
    func_80116968_mgmode(D_8011B450_mgmode, 1, 180, 91);
    func_80116968_mgmode(D_8011B450_mgmode, 2, 180, 121);
    func_80116968_mgmode(D_8011B450_mgmode, 3, 180, 151);
    for (i = 1; i < 15; i++) {
        for (j = 0; j < 3; j++) {
            frame = i - j * 3;
            if (frame < 0) {
                func_801169C8_mgmode(D_8011B450_mgmode, j + 1);
            } else if (frame < 9) {
                func_801169A0_mgmode(D_8011B450_mgmode, j + 1);
                func_80116A48_mgmode(D_8011B450_mgmode, j + 1, 1.0f, sindf(frame / 8.0f * 90.0f));
            }
        }
        HuPrcVSleep();
    }
    sel = 0;
    func_8011822C_mgmode(D_8011943C_mgmode);
    func_801181F4_mgmode(0);
    func_8011829C_mgmode(5);
    func_801182B4_mgmode(1);
    while (TRUE) {
        HuPrcVSleep();
        func_80118D0C_mgmode();
        if (ABS(D_800CBB6E_main[D_8011B808_mgmode]) >= 31 || ABS(D_800D20A1_main[D_8011B808_mgmode]) >= 31) {
            next = func_801182DC_mgmode(-D_800CBB6E_main[D_8011B808_mgmode], D_800D20A1_main[D_8011B808_mgmode]);
            if (next == -1) {
                continue;
            }
            HuAudFXPlay(1);
            func_801182A8_mgmode(next);
            HuPrcSleep(5);
            sel = next;
        } else if (D_800D5558_main[D_8011B808_mgmode] & A_BUTTON) {
            HuAudFXPlay(2);
            dist = 47 - D_8011944C_mgmode[sel];
            for (i = 1; i < 6; i++) {
                for (j = 0; j < 3; j++) {
                    if (j == sel) {
                        func_80116968_mgmode(D_8011B450_mgmode, sel + 1, 180,
                                             D_8011944C_mgmode[j] + dist * sindf(i / 5.0f * 90.0f));
                    } else {
                        func_80116A48_mgmode(D_8011B450_mgmode, j + 1, 1.0f, cosdf(i / 5.0f * 90.0f));
                    }
                }
                HuPrcVSleep();
            }
            func_801169C8_mgmode(D_8011B450_mgmode, 1);
            func_801169C8_mgmode(D_8011B450_mgmode, 2);
            func_801169C8_mgmode(D_8011B450_mgmode, 3);
            func_801169A0_mgmode(D_8011B450_mgmode, sel + 1);
            break;
        } else if (D_800D5558_main[D_8011B808_mgmode] & B_BUTTON) {
            HuAudFXPlay(4);
            sel = -1;
            break;
        }
    }
    func_801182B4_mgmode(0);
    HuPrcSleep(5);
    return sel;
}

void func_8010D98C_mgmode(void) {
    s16 i;
    s16 j;
    s16 frame;

    for (i = 1; i < 15; i++) {
        for (j = 0; j < 3; j++) {
            frame = i - (2 - j) * 3;
            if (frame < 0) {
                continue;
            }
            if (frame >= 9) {
                func_801169C8_mgmode(D_8011B450_mgmode, j + 1);
            } else {
                func_80116A48_mgmode(D_8011B450_mgmode, j + 1, 1.0f, cosdf(frame / 8.0f * 90.0f));
            }
        }
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010DAB8_mgmode);

void func_8010E1F0_mgmode(void) {
    s16 list[20];
    s16 count;
    s16 i;
    s16 j;
    s16 r;
    s16 tmp;
    s16 category;

    category = D_800D4194_main;
    count = 0;
    for (i = 0; i < D_8011B940_mgmode[category]; i++) {
        if (D_8011B6B0_mgmode[category][i] != 0xFF) {
            list[count++] = D_8011B6B0_mgmode[category][i];
        }
    }
    for (i = 0; i < count * 2; i++) {
        j = i % count;
        r = (rand8() * count) >> 8;
        tmp = list[j];
        list[j] = list[r];
        list[r] = tmp;
    }
    for (i = 0; i < D_8011B928_mgmode[category]; i++) {
        D_800D0418_main[i] = list[i];
    }
}

void func_8010E40C_mgmode(void) {
    s16 i;

    for (i = 0; i < D_8011B454_mgmode; i++) {
        func_801169C8_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[i] + 4);
    }
}

#ifdef NON_MATCHING
// Matches except for one register copy: target emits `move t3,a2` for rank = 0,
// but GCC propagates the constant (`move t3,zero`) whenever `slot = 0` and
// `rank = 0` share a basic block, regardless of how the initializer is written.
// Partial workaround: putting an empty `if (count) {}` between `slot = 0;` and
// `rank = slot;` keeps the copy and gets within 2 instructions, but it's an
// artificial construct. A real fix likely needs a different loop structure.
void func_8010E494_mgmode(s16 arg0) {
    Vec pos[4];
    s16 order[4];
    s16 count;
    s16 i;
    s16 slot;
    s16 rank;

    count = (arg0 != 4) ? 4 : 2;
    for (i = 0; i < count; i++) {
        order[i] = D_800D1F20_main[i];
    }
    for (slot = 0, rank = 0; rank < count || slot < count; rank++) {
        for (i = 0; i < count; i++) {
            if (rank == order[i]) {
                pos[i].x = slot * 80 - 122;
                pos[i].y = 26.0f;
                pos[i].z = -312.0f;
                order[i] = -1;
                slot++;
            }
        }
    }
    for (i = 0; i < count; i++) {
        func_8001C258_main(D_8011B8B6_mgmode[i], 4, 0);
        Hu3DModelPosSet(D_8011B8B6_mgmode[i], pos[i].x, pos[i].y, pos[i].z);
        func_8001C258_main(D_8011B8E8_mgmode[i], 4, 0);
        Hu3DModelPosSet(D_8011B8E8_mgmode[i], pos[i].x, pos[i].y, pos[i].z);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010E494_mgmode);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010E6F0_mgmode);

void func_8010EE84_mgmode(s16 arg0) {
    Vec pos[4];
    Vec delta[4];
    f32 angle[4];
    s16 count;
    s16 i;
    s16 j;
    f32 t;

    count = (arg0 != 4) ? 4 : 2;
    for (i = 0; i < count; i++) {
        pos[i].x = HmfModelData[D_8011B8A8_mgmode[i + 7]].pos.x;
        pos[i].y = HmfModelData[D_8011B8A8_mgmode[i + 7]].pos.y;
        pos[i].z = HmfModelData[D_8011B8A8_mgmode[i + 7]].pos.z;
        delta[i].x = 400.0f - pos[i].x;
        delta[i].z = 900.0f - pos[i].z;
        func_8001C258_main(D_8011B8A8_mgmode[i + 7], 4, 0);
        Hu3DMotionShiftSet(D_8011B8A8_mgmode[i + 7], D_8011B796_mgmode[i], 0, 8, 2);
        angle[i] = atan2df(delta[i].x, delta[i].z);
    }
    for (j = 0; j < 9; j++) {
        t = j / 8.0f;
        for (i = 0; i < count; i++) {
            Hu3DModelRotSet(D_8011B8A8_mgmode[i + 7], 0.0f, t * angle[i], 0.0f);
        }
        HuPrcVSleep();
    }
    for (j = 0; j < 31; j++) {
        if (j == 10) {
            Hu3DMotionShiftSet(D_8011B8A8_mgmode[4], D_8011B78C_mgmode, 0, 8, 2);
        }
        t = 1.0f - sindf(j / 30.0f * 90.0f + 90.0f);
        for (i = 0; i < count; i++) {
            Hu3DModelPosSet(D_8011B8A8_mgmode[i + 7], pos[i].x + t * delta[i].x, pos[i].y, pos[i].z + t * delta[i].z);
            func_80118624_mgmode(D_8011B8A8_mgmode[i + 32], D_8011B8A8_mgmode[i + 7]);
            if (j < 25 && j % 5 == 0) {
                func_8004AC5C_main(GwPlayer[i].chr + 0x29, i);
            }
        }
        HuPrcVSleep();
    }
    for (i = 0; i < count; i++) {
        func_8001C258_main(D_8011B8A8_mgmode[i + 7], 4, 4);
        func_8001C258_main(D_8011B8A8_mgmode[i + 32], 4, 4);
    }
    Hu3DMotionShiftSet(D_8011B8A8_mgmode[4], D_8011B788_mgmode, 0, 8, 2);
}

#ifdef NON_MATCHING
// Matches except for one register: after `prev = idx;`, CSE substitutes `prev`
// for `idx` in the following `list[idx]` access (s0 instead of target s2).
// Reusing `category` for prev/result fixes that but changes register
// allocation priority so that `count` takes s0 and an extra s4 is saved.
s16 func_8010F348_mgmode(s16 category) {
    s16 list[32];
    s16 count;
    s16 i;
    s16 idx;
    s16 prev;

    if (D_80119340_mgmode == -1) {
        D_80119340_mgmode = func_80116B20_mgmode();
        espAttrSet(D_80119340_mgmode, 0x4008);
        espPosSet(D_80119340_mgmode, 180, 134);
        for (i = 0; i < 10; i++) {
            espTPLvlSet(D_80119340_mgmode, i / 10.0f * 255.0f);
            HuPrcVSleep();
        }
    }
    count = 0;
    for (i = 0; i < D_8011B940_mgmode[category]; i++) {
        if (D_8011B6B0_mgmode[category][i] != 0xFF) {
            list[count++] = D_8011B6B0_mgmode[category][i];
        }
    }
    prev = -1;
    idx = (rand8() * count) >> 8;
    func_80116C18_mgmode(D_800A6D40_main[list[idx]].flags & 0x7FF);
    for (i = 0; i < 30; i++) {
        HuPrcVSleep();
        while (idx == prev) {
            idx = (rand8() * count) >> 8;
        }
        prev = idx;
        func_80116C18_mgmode(D_800A6D40_main[list[idx]].flags & 0x7FF);
        HuAudFXPlay(0x104);
    }
    HuPrcVSleep();
    prev = D_800D0418_main[D_800D1F2C_main];
    func_80116C18_mgmode(D_800A6D40_main[prev].flags & 0x7FF);
    HuPrcVSleep();
    HuAudFXPlay(0x105);
    return prev;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010F348_mgmode);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010F648_mgmode);

u8 func_80110420_mgmode(s16 mgIndex) {
    s16 i;

    D_8011B434_mgmode = 0;
    if (D_800A6D40_main[mgIndex].minigameType != MINIGAME_ITEM) {
        for (i = 0; i < 4; i++) {
            if (GwPlayer[i].bonusCoin + GwPlayer[i].gameCoin >= 10) {
                D_8011B430_mgmode[D_8011B434_mgmode] = i;
                D_8011B434_mgmode++;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (GwPlayer[i].bonusCoin == 0) {
                D_8011B430_mgmode[D_8011B434_mgmode] = i;
                D_8011B434_mgmode++;
            }
        }
    }
    return D_8011B434_mgmode;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80110554_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80111380_mgmode);

s32 func_80111B08_mgmode(void) {
    s16 i;

    func_80110420_mgmode(D_800CE29C_main);
    for (i = 0; i < D_8011B434_mgmode; i++) {
        if (D_800D03FE_main[D_8011B430_mgmode[i]] + 1 >= D_80119430_mgmode[D_800CC438_main]) {
            return 1;
        }
    }
    return 0;
}

void func_80111BB0_mgmode(void) {
    s16 i;
    s16 j;

    for (i = 0; i < 28; i++) {
        espScaleSet(D_8011B488_mgmode[i], 0.0f, 0.0f);
    }
    for (i = 0; i < 4; i++) {
        func_80116A78_mgmode(D_8011B480_mgmode, i + 5, 0);
    }
    for (j = 0; j < 6; j++) {
        for (i = 0; i < 4; i++) {
            func_80116A78_mgmode(D_8011B480_mgmode, i + 5, (1.0 - j / 5.0) * 255.0);
        }
        for (i = 0; i < 28; i++) {
            espScaleSet(D_8011B488_mgmode[i], 1.0 - j / 5.0, 1.0 - j / 5.0);
        }
        HuPrcVSleep();
    }
    for (j = 0; j < 6; j++) {
        for (i = 0; i < 4; i++) {
            func_80116A78_mgmode(D_8011B480_mgmode, i + 1, (1.0 - j / 5.0) * 255.0);
        }
        func_80116A78_mgmode(D_8011B480_mgmode, 0, (1.0 - j / 5.0) * 192.0);
        HuPrcVSleep();
    }
    func_801168E0_mgmode(D_8011B480_mgmode);
    for (i = 0; i < 28; i++) {
        espKill(D_8011B488_mgmode[i]);
    }
    HuSprAnimKill(D_8011B484_mgmode);
}

void func_80111ED8_mgmode(void) {
    s16 i;

    for (i = 0; i < 6; i++) {
        func_80116A48_mgmode(D_8011B450_mgmode, D_800D4194_main + 4, 0.7f, (1.0f - i / 5.0f) * 0.7f);
        HuPrcVSleep();
    }
}

void func_80111F9C_mgmode(void) {
    s16 i;

    for (i = 0; i < 6; i++) {
        func_80116A48_mgmode(D_8011B450_mgmode, D_800CC438_main + 1, 0.7f, (1.0f - i / 5.0f) * 0.7f);
        HuPrcVSleep();
    }
}

void func_80112060_mgmode(s32 arg0) {
    s16 order[4];
    s16 i;
    s16 j;
    s16 k;
    s16 count;

    for (j = 0; j < 4; j++) {
        order[j] = D_800D1F20_main[j];
    }

    count = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == order[j]) {
                for (k = 0; k < D_8011B434_mgmode; k++) {
                    if (D_8011B430_mgmode[k] == j) {
                        break;
                    }
                }
                if (k != D_8011B434_mgmode) {
                    if (arg0) {
                        func_80118888_mgmode(count);
                    } else {
                        func_801188A4_mgmode(count);
                    }
                    order[j] = -1;
                }
                count++;
            }
        }
    }
}
