#include "common.h"
#include "overlays/minigame.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/sprite.h"

extern s16 D_800EB91A_minigame;
extern s32 D_800EB91C_minigame;
extern s32 D_800EB920_minigame;
extern s32 D_800EB924_minigame;
extern u16 D_800EB926_minigame;
extern s16 D_800EBDE4_minigame;
extern s16 D_800EBDE6_minigame;
extern s16 D_800EBDE8_minigame;

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B8A20", func_800E5EA0_minigame);

void func_800E6248_minigame(s32 arg0, s32 arg1) {
    D_800EB91C_minigame = arg0;
    D_800EB920_minigame = arg1;
}

void func_800E625C_minigame(s32 arg0) {
    D_800EB924_minigame = arg0;
}

void func_800E6268_minigame(void) {
    void *data;

    data = DataRead(0x31);
    D_800EBDE4_minigame = HuSprAnimRead(data);
    DataClose(data);
}

void func_800E62A8_minigame(void) {
    void *data;

    data = DataRead(0x31);
    D_800EBDE6_minigame = HuSprAnimRead(data);
    DataClose(data);
    func_8000B880_main(D_800EBDE6_minigame, 0.0f, 1.0f, 0.0f);
}

s16 func_800E6300_minigame(s16 x, s16 y) {
    s16 group;
    s16 member;
    s16 memberX;

    group = D_800EBDE8_minigame = HuSprGrpCreate(7, 5);
    HuSprGrpMemberSet(group, 0, D_800EBDE4_minigame, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprDispOff(group, 0);
    HuSprPosSet(group, 0, x - 16, y);
    HuSprPriSet(group, 0, D_800EB926_minigame);

    memberX = 4;
    for (member = 1; member < 7; member++) {
        HuSprPriSet(group, member, D_800EB926_minigame);
        HuSprGrpMemberSet(group, member, D_800EBDE4_minigame, 0);
        HuSprPosSet(group, member, memberX, 0);
        HuSprAttrReset(group, member, 0xFFFF);
        HuSprDispOff(group, member);
        if (member == 3) {
            memberX += 8;
        } else {
            memberX += 12;
        }
        func_800554C4_main(group, member, 0);
    }

    HuSprDispOn(group, 2);
    return group;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B8A20", func_800E64B8_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B8A20", func_800E6670_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B8A20", func_800E6968_minigame);

void func_800E6E4C_minigame(s16 arg0) {
    D_800EBDE0_minigame->unk1C = arg0;
}

void func_800E6E5C_minigame(s16 arg0) {
    D_800EBDE0_minigame->unk1E = arg0;
}

void func_800E6E6C_minigame(s16 arg0) {
    D_800EBDE0_minigame->unk24 = arg0;
}

void func_800E6E7C_minigame(s8 arg0) {
    D_800EBDE0_minigame->unk01 = arg0;
}

u8 func_800E6E8C_minigame(void) {
    return D_800EBDE0_minigame->unk00;
}

u16 func_800E6E9C_minigame(void) {
    s32 value;

    switch (D_800EBDE0_minigame->unk00) {
        case 0:
            value = D_800EB910_minigame;
            break;
        case 1:
            value = D_800EB912_minigame;
            break;
        case 2:
            value = D_800EB914_minigame;
            break;
        case 3:
            value = D_800EB916_minigame;
            break;
        case 4:
        default:
            value = D_800EB918_minigame;
            break;
    }

    return value;
}

void func_800E6F0C_minigame(u8 arg0) {
    D_800EBDE0_minigame->unk00 = arg0;
}

void func_800E6F1C_minigame(void) {
    D_800EBDE0_minigame->unk00++;
}

void func_800E6F34_minigame(s32 arg0) {
    D_800EB91A_minigame = arg0;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/minigame/B8A20", D_800EBCF4_minigame);

INCLUDE_RODATA("asm/nonmatchings/overlays/minigame/B8A20", D_800EBCFC_minigame);

INCLUDE_RODATA("asm/nonmatchings/overlays/minigame/B8A20", D_800EBD04_minigame);

INCLUDE_RODATA("asm/nonmatchings/overlays/minigame/B8A20", D_800EBD10_minigame);

INCLUDE_RODATA("asm/nonmatchings/overlays/minigame/B8A20", D_800EBD18_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B8A20", func_800E6F40_minigame);
