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

void func_8010CBFC_mgmode(void);
void func_801169C8_mgmode(MgmodeEsprite *arg0, s16 index);
void func_80116A48_mgmode(MgmodeEsprite *arg0, s16 index, f32 x, f32 y);
void func_80118888_mgmode(s16 index);
void func_801188A4_mgmode(s16 index);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010D3B0_mgmode);

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
// Matches except for one register copy: target emits `move t3,a2` for rank = 0.
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

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010EE84_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010F348_mgmode);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80111BB0_mgmode);

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
