#include "common.h"

typedef struct ChanceTimeUnkFED0 {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ char unk01[0x27];
} ChanceTimeUnkFED0; // size = 0x28

typedef struct ChanceTimeUnkFE3C {
    /* 0x00 */ s16 coins;
    /* 0x02 */ s16 stars;
} ChanceTimeUnkFE3C; // size = 0x4

extern s8 D_8010FB80_chancetime;
extern s8 D_8010FB81_chancetime;
extern s16 D_8010FB84_chancetime[2];
extern f32 D_8010FB88_chancetime;
extern f32 D_8010FB8C_chancetime;
extern s32 D_8010FBF0_chancetime;
extern s32 D_8010FBF4_chancetime;
extern s32 D_8010FBF8_chancetime;
extern s32 D_8010FBFC_chancetime;
extern s32 D_8010FC10_chancetime;
extern s32 D_8010FC14_chancetime;
extern s32 D_8010FC18_chancetime;
extern s32 D_8010FC1C_chancetime;
extern s16 D_8010FE94_chancetime[3];
extern u16 D_8010FE9A_chancetime;
extern s32 D_8010FEC4_chancetime;
extern ChanceTimeUnkFE3C D_8010FE3C_chancetime[];
extern ChanceTimeUnkFED0 D_8010FED0_chancetime[3];
extern s32 D_8010FF48_chancetime[3];
extern s8 D_8010FEC8_chancetime;
extern s8 D_8010FEC9_chancetime;
extern s8 D_80110000_chancetime;
extern s32 D_80110008_chancetime;
extern void (*D_80110084_chancetime)();
extern omObjData *D_801100C8_chancetime;
extern s8 D_801100D0_chancetime[4];
extern s8 D_801100DD_chancetime[2];
extern s8 D_801100DF_chancetime;
extern void (*D_801100CC_chancetime)(void);

s32 func_8010872C_chancetime(void);
void func_8010C610_chancetime(void);
void func_8010F44C_chancetime(s32 arg0, s16 arg1, s16 arg2);
void func_8010D320_chancetime(void);
void func_8010D6A4_chancetime(s32 arg0);
void func_8010DFA4_chancetime(void);
void func_8010E210_chancetime(void);
void func_8010E280_chancetime(void);
void func_8010F1F8_chancetime(void);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010BF80_chancetime);

void func_8010C5F4_chancetime(void) {
    func_8010D320_chancetime();
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010C610_chancetime);

void func_8010C870_chancetime(void) {
    D_8010FB84_chancetime[0] = 74;
    D_8010FB84_chancetime[1] = 25;
    espPosSet(D_8010FE9A_chancetime, 161, 71);
    espPosSet(D_8010FE94_chancetime[0], D_8010FB84_chancetime[0] + 51, D_8010FB84_chancetime[1] + 46);
    espPosSet(D_8010FE94_chancetime[1], D_8010FB84_chancetime[0] + 124, D_8010FB84_chancetime[1] + 46);
    espPosSet(D_8010FE94_chancetime[2], D_8010FB84_chancetime[0] + 87, D_8010FB84_chancetime[1] + 116);
    if (func_8010872C_chancetime() == 1) {
        D_8010FB88_chancetime = 600.0f;
        D_8010FB8C_chancetime = 0.0f;
        D_8010FB80_chancetime = 0;
        D_8010FB81_chancetime = 1;
        D_801100CC_chancetime = func_8010C5F4_chancetime;
    }
}

void func_8010C98C_chancetime(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010C994_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010CF78_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FC98_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCC0_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCC8_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCD0_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCD8_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCE8_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCF8_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010D320_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010D6A4_chancetime);

void func_8010D92C_chancetime(s8 arg0) {
    switch (D_8010FBF0_chancetime) {
        case 1:
            if (D_8010FBF4_chancetime == 1) {
                HuAudFXStop((s16)D_8010FF48_chancetime[0]);
            }
            HuAudFXPlay(0x4FC);
            break;
        case 2:
            if (D_8010FBF8_chancetime == 1) {
                HuAudFXStop((s16)D_8010FF48_chancetime[1]);
            }
            HuAudFXPlay(0x4FD);
            break;
        case 3:
            if (D_8010FBFC_chancetime == 1) {
                HuAudFXStop((s16)D_8010FF48_chancetime[2]);
            }
            HuAudFXPlay(0x4FE);
            break;
    }
    D_8010FED0_chancetime[arg0].unk00 = 1;
}

void func_8010DA24_chancetime(void) {
    s32 i;

    D_8010FB80_chancetime = 1;
    D_8010FB81_chancetime = 0;
    for (i = 0; i < 3; i++) {
        espDispOn(D_8010FE94_chancetime[i]);
    }
    espDispOn(D_8010FE9A_chancetime);
    D_801100CC_chancetime = func_8010C610_chancetime;
}

s8 func_8010DAA4_chancetime(void) {
    return D_8010FB81_chancetime;
}

void func_8010DAB0_chancetime(void) {
    omObjData *obj = D_801100C8_chancetime;
    s8 i;

    for (i = 0; i < 3; i++) {
        func_8001C258_main(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
}

void func_8010DB1C_chancetime(s8 arg0) {
    omObjData *obj = D_801100C8_chancetime;

    espDispOff(D_8010FE94_chancetime[arg0]);
    func_8001C258_main(obj->model[arg0 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void func_8010DB78_chancetime(void) {
    D_8010FEC4_chancetime = 0;
    D_8010FEC8_chancetime = 1;
    D_8010FEC9_chancetime = 0;
}

void func_8010DB98_chancetime(void) {
    D_8010FEC8_chancetime = 0;
    D_8010FEC9_chancetime = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010DBB0_chancetime);

void func_8010DF68_chancetime(void) {
}

void func_8010DF70_chancetime(void) {
}

void func_8010DF78_chancetime(s32 arg0) {
    D_8010FC14_chancetime = 0;
    D_80110008_chancetime = (s8)arg0;
    D_80110084_chancetime = func_8010DFA4_chancetime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010DFA4_chancetime);

void func_8010E1E0_chancetime(void) {
    func_8010D6A4_chancetime(D_80110000_chancetime);
    D_80110084_chancetime = func_8010E210_chancetime;
}

void func_8010E210_chancetime(void) {
    D_8010FC1C_chancetime++;
    if (D_8010FC1C_chancetime < 10) {
        return;
    }
    D_8010FC14_chancetime = 1;
    D_8010FC1C_chancetime = 0;
    D_80110084_chancetime = func_8010DF70_chancetime;
}

s32 func_8010E258_chancetime(void) {
    return D_8010FC14_chancetime;
}

void func_8010E264_chancetime(void) {
    D_8010FC18_chancetime = 0;
    D_80110084_chancetime = func_8010E280_chancetime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010E280_chancetime);

s32 func_8010E4C4_chancetime(void) {
    return D_8010FC18_chancetime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010E4D0_chancetime);

void func_8010F1DC_chancetime(void) {
    D_8010FC10_chancetime = 0;
    D_80110084_chancetime = func_8010F1F8_chancetime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010F1F8_chancetime);

s32 func_8010F420_chancetime(void) {
    return D_8010FC10_chancetime;
}

void func_8010F42C_chancetime(void) {
    D_8010FC10_chancetime = 1;
    D_80110084_chancetime = func_8010DF70_chancetime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010F44C_chancetime);

void func_8010F984_chancetime(void) {
    s32 players[4];
    s32 i;
    s32 j;
    s32 coinAmount;
    s32 starAmount;
    s16 coins;
    s16 stars;
    u16 isStars;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (D_801100DD_chancetime[i] == GwPlayer[D_801100D0_chancetime[j]].chr) {
                players[i] = D_801100D0_chancetime[j];
                break;
            }
        }
    }

    coins = D_8010FE3C_chancetime[D_801100DF_chancetime].coins;
    coinAmount = D_8010FE3C_chancetime[D_801100DF_chancetime].coins;
    starAmount = D_8010FE3C_chancetime[D_801100DF_chancetime].stars;
    stars = starAmount;
    if (coinAmount > 0) {
        if (GwPlayer[players[0]].coin < coinAmount) {
            coins = GwPlayer[players[0]].coin;
        }
        isStars = FALSE;
    } else {
        if (stars > GwPlayer[players[0]].star) {
            stars = GwPlayer[players[0]].star;
        }
        isStars = TRUE;
    }

    if (!isStars) {
        func_8010F44C_chancetime(D_801100DF_chancetime, coinAmount, coins);
    } else {
        func_8010F44C_chancetime(D_801100DF_chancetime, starAmount, stars);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD0C_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD20_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD38_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD3C_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD40_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD5C_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD68_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD8C_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FDB0_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FDD4_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FDF8_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FE1C_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FE3C_chancetime);
