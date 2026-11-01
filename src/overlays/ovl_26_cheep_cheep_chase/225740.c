#include "common.h"
#include "gcc/memory.h"

typedef struct UnkCheepCheepChaseSprite {
    /* 0x00 */ s8 state;   // 0 while unused, 1 once hidden, 2 once shown
    /* 0x01 */ u8 groupId; // sprite group this sprite lives in
    /* 0x02 */ char unk_02[0x4];
} UnkCheepCheepChaseSprite; // sizeof 0x6

typedef struct UnkCheepCheepChaseGroup {
    /* 0x00 */ void *unk_00;
    /* 0x04 */ s8 unk_04;
    /* 0x05 */ u8 active;
    /* 0x06 */ char unk_06[0xA];
} UnkCheepCheepChaseGroup; // sizeof 0x10

typedef struct UnkCheepCheepChaseHandler {
    /* 0x00 */ char unk_00[0x0B];
    /* 0x0B */ u8 unk_0B;
    /* 0x0C */ char unk_0C[0x34];
} UnkCheepCheepChaseHandler; // sizeof 0x40

typedef struct UnkCheepCheepChaseActor {
    /* 0x00 */ f32 *unk_00;
    /* 0x04 */ u8 *unk_04;
    /* 0x08 */ u8 *unk_08;
    /* 0x0C */ u8 *unk_0C;
    /* 0x10 */ void *unk_10;
    /* 0x14 */ s16 zTick;
    /* 0x16 */ char unk_16[0x2];
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ s16 scaleIndex;
    /* 0x1E */ s16 xTick;
    /* 0x20 */ char unk_20[0x4];
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ char unk_26[0x2];
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s16 unk_2C;
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ s16 unk_30;
} UnkCheepCheepChaseActor; // sizeof 0x34

extern UnkCheepCheepChaseActor *D_8010E360_cheep_cheep_chase;
extern UnkCheepCheepChaseSprite *D_8010E390_cheep_cheep_chase;
extern UnkCheepCheepChaseGroup *D_8010E398_cheep_cheep_chase;

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801059A0_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801059BC_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80105BBC_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80105DD0_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80105E18_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80105E50_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80105E74_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80105F50_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010619C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801061C8_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010636C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80106388_cheep_cheep_chase);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E050_cheep_cheep_chase);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E05C_cheep_cheep_chase);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E06C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80106484_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010665C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801067B0_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80106978_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80106AA0_cheep_cheep_chase);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E0C0_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80106E80_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010732C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80107440_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80107698_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801076B4_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80107760_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80107BDC_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80107E3C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801080C8_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80108170_cheep_cheep_chase);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E170_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801085FC_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801088F8_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010896C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80108AF4_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80108C98_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80108F78_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801090E0_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801091FC_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801092B8_cheep_cheep_chase);

void func_801093CC_cheep_cheep_chase(s32 arg0) {
    Hu3DModelPosSet(arg0, 0.0f, 110.0f, -250.0 - (D_8010E360_cheep_cheep_chase->zTick * 500.0));
    D_8010E360_cheep_cheep_chase->zTick++;
}

void func_80109444_cheep_cheep_chase(s32 arg0) {
    Hu3DModelPosSet(arg0, -325.0f, 200.0f, 200.0 - (D_8010E360_cheep_cheep_chase->xTick * 1000.0));
    D_8010E360_cheep_cheep_chase->xTick++;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801094C0_cheep_cheep_chase);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E1B8_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80109750_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80109CAC_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010A08C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010A57C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010A938_cheep_cheep_chase);

void func_8010ACD8_cheep_cheep_chase(s32 arg0) {
    arg0 &= 0xFF;
    D_800CBB6E_main[arg0] = 0;
    D_800D20A1_main[arg0] = 0;
    D_800CDA7C_main[arg0] = 0;
    D_800D5558_main[arg0] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010AD14_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010AF70_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010B148_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010B33C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010B52C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010B63C_cheep_cheep_chase);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E258_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010B648_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010BB9C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010BEA4_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010C004_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010C440_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010C8EC_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010C988_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010CAD4_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010CBBC_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010D02C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010D198_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010D560_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010D62C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010D6F4_cheep_cheep_chase);

void func_8010D7F4_cheep_cheep_chase(s8 arg0, UnkCheepCheepChaseHandler *arg1) {
    u8 saved = arg1->unk_0B;

    memset(arg1, 0, sizeof(UnkCheepCheepChaseHandler));
    arg1->unk_0B = saved;
    D_8010E398_cheep_cheep_chase[arg0].active = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010D85C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010D8FC_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010D9E8_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010DA74_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010DA84_cheep_cheep_chase);

void func_8010DB24_cheep_cheep_chase(s16 arg0) {
    UnkCheepCheepChaseSprite *sprite = &D_8010E390_cheep_cheep_chase[arg0];

    if (sprite->state != 0) {
        HuSprDispOff(sprite->groupId, 0);
        sprite->state = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010DB80_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010DB8C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010DC7C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010DDF4_cheep_cheep_chase);

u8 func_8010DF48_cheep_cheep_chase(f32 *outPos, u8 *tickPtr, f32 posA, f32 posB, f32 numTicks) {
    u8 ticks;
    f32 frac = (f32)*tickPtr / numTicks;

    *outPos = posA + ((posB - posA) * frac);
    ticks = *tickPtr + 1;
    *tickPtr = ticks;
    if (numTicks < ticks) {
        *tickPtr = 0;
        *outPos = posB;
        return 1;
    }
    return 0;
}

f32 func_8010DFC0_cheep_cheep_chase(f32 t, f32 p0, f32 p1, f32 p2) {
    f32 u = 1.0f - t;
    f32 ret;

    ret = u * u * p0;
    ret += 2.0f * u * t * p1;
    ret += u * u * p2;
    return ret;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E350_cheep_cheep_chase);
