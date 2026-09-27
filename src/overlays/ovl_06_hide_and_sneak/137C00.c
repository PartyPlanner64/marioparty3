#include "common.h"

typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk_04;
} HideAndSneakWork;

typedef struct { // 0x84 bytes, four entries (one per player)
    omObjData *obj;
    s16 unk_04;
    s16 unk_08;
    char unk_0A[0xC];
    s16 unk_16;
    char unk_18[0x6C];
} HideAndSneakPlayerWork;

extern omObjData *D_8010C7A0_hide_and_sneak;
extern HideAndSneakPlayerWork D_8010CA34_hide_and_sneak[4];
extern HideAndSneakWork D_8010CE54_hide_and_sneak;
extern s8 D_8010E182_hide_and_sneak[4];
extern s8 D_8010E188_hide_and_sneak[4][4];

void func_80106738_hide_and_sneak(omObjData *);
void func_8010AFA0_hide_and_sneak(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_801059A0_hide_and_sneak);

f32 func_801059BC_hide_and_sneak(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 func_80105A3C_hide_and_sneak(s32 arg0) {
    u32 ret = (rand8() & 0xFF) * arg0;
    return ret >> 8;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80105A74_hide_and_sneak);

void func_80105B3C_hide_and_sneak(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80105BB4_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80105C98_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80105D64_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80105D94_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80105EC4_hide_and_sneak);

s32 func_801064F4_hide_and_sneak(s32 arg0) {
    return rand8() % arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80106548_hide_and_sneak);

void func_801065B0_hide_and_sneak(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    func_8001C624_main(arg0->model[0], HmfModelData[arg0->motion[arg1]].unk02, arg2, arg3, arg4);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010661C_hide_and_sneak);

void func_80106730_hide_and_sneak(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80106738_hide_and_sneak);

void func_80106960_hide_and_sneak(void) {
    D_8010C7A0_hide_and_sneak = omAddObj(0x1F4, 4, 2, -1, func_80106738_hide_and_sneak);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010699C_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80106ABC_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80106D10_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80107638_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_801078E4_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_801079E8_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80107B30_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80107BD8_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80107CF4_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80107D98_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80107EF0_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108040_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108130_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108278_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010841C_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108588_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108670_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_801087B4_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_801088A0_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108990_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108AF0_hide_and_sneak);

s32 func_80108BD8_hide_and_sneak(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108BE0_hide_and_sneak);

void func_80109578_hide_and_sneak(void) {
    s8 i;

    for (i = 0; i < 4; i++) {
        D_8010E188_hide_and_sneak[i][1] = -1;
        D_8010E188_hide_and_sneak[i][2] = -1;
        D_8010E188_hide_and_sneak[i][3] = -1;
        D_8010E188_hide_and_sneak[i][0] = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_801095DC_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80109688_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80109870_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80109BF4_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80109D88_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010A1CC_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010A48C_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010A6BC_hide_and_sneak);

s32 func_8010A7A4_hide_and_sneak(void) {
    s8 i = 0;
    s8 count1 = 0;
    s8 count2 = 0;
    HideAndSneakPlayerWork *players = D_8010CA34_hide_and_sneak;

    while (i < 4) {
        if (players[i].unk_04 == 0) {
            count1++;
        }
        if (D_8010E182_hide_and_sneak[i] != 0) {
            count2++;
        }
        i++;
    }

    return count1 == count2;
}

s32 func_8010A824_hide_and_sneak(void) {
    s8 i = 0;
    s8 count = 0;
    HideAndSneakPlayerWork *players = D_8010CA34_hide_and_sneak;

    while (i < 4) {
        if (players[i].unk_04 == -0x40) {
            count++;
        }
        i++;
    }
    return count == 4;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010A88C_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010AAC8_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010ABC8_hide_and_sneak);

void func_8010AC78_hide_and_sneak(void) {
    HideAndSneakWork *work = &D_8010CE54_hide_and_sneak;

    if (work->unk_04 < 0xFF) {
        work->unk_04 += 0x1A;
    } else {
        work->unk_04 = 0xFF;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010ACB8_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010ACC4_hide_and_sneak);

void func_8010AF98_hide_and_sneak(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010AFA0_hide_and_sneak);

void func_8010B0D0_hide_and_sneak(void) {
    D_8010CE54_hide_and_sneak.obj = omAddObj(0x3E8, 2, 1, -1, func_8010AFA0_hide_and_sneak);
    omSetStatBit(D_8010CE54_hide_and_sneak.obj, 0xA0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010B118_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010B33C_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C670_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C680_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C694_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6A4_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6B8_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6C8_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6DC_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6EC_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010B410_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010B55C_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010B600_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010BBBC_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010BC8C_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010BCB0_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010BCE8_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010BD40_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010BFE8_hide_and_sneak);

void func_8010C0A4_hide_and_sneak(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010C0AC_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010C220_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C754_hide_and_sneak);
