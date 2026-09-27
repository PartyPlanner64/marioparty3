#include "common.h"

// One entry of the 50 card stack. Layout derived from the table clear in
// func_80105A74_stacked_deck, which walks 50 entries of 0x84 bytes.
typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk_04[9];
    /* 0x18 */ s32 unk_18[10];
    /* 0x40 */ s16 unk_40[2];
    /* 0x44 */ f32 unk_44[16];
} StackedDeckCard; //sizeof 0x84

extern StackedDeckCard D_8010F730_stacked_deck[50];

void func_8010655C_stacked_deck(omObjData *object);
void func_8010669C_stacked_deck(omObjData *object);
void func_8010DAE4_stacked_deck(omObjData *object);
void func_8010DDAC_stacked_deck(omObjData *object);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_801059A0_stacked_deck);

f32 func_801059BC_stacked_deck(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 func_80105A3C_stacked_deck(s32 arg0) {
    u32 ret = (rand8() & 0xFF) * arg0;
    return ret >> 8;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80105A74_stacked_deck);

void func_80105B3C_stacked_deck(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80105BB4_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80105CBC_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80106290_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010629C_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80106338_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80106354_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_801063F4_stacked_deck);

void func_80106554_stacked_deck(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010655C_stacked_deck);

void func_80106654_stacked_deck(void) {
    omObjData *obj = omAddObj(0x3E6, 1, 1, -1, func_8010655C_stacked_deck);
    obj->work[0] = 0;
    D_8010F730_stacked_deck[0].obj = obj;
}

void func_80106694_stacked_deck(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010669C_stacked_deck);

void func_80106738_stacked_deck(void) {
    omObjData *obj = omAddObj(0x3E7, 1, 1, -1, func_8010669C_stacked_deck);
    obj->work[0] = 0;
    D_8010F730_stacked_deck[1].obj = obj;
}

void func_80106778_stacked_deck(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80106780_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_801069A0_stacked_deck);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", D_8010F42C_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80106BC8_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80108E48_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010969C_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_801097D4_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010C188_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010C524_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010C5C8_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010D58C_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010D8E8_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010D98C_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010DAE4_stacked_deck);

void func_8010DBF4_stacked_deck(void) {
    omObjData *obj = omAddObj(0x244, 1, 0, -1, func_8010DAE4_stacked_deck);
    obj->work[0] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010DC2C_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010DDAC_stacked_deck);

void func_8010DEBC_stacked_deck(void) {
    omObjData *obj = omAddObj(0x24E, 1, 0, -1, func_8010DDAC_stacked_deck);
    obj->work[0] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010DEF4_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010E368_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010E4EC_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010E590_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010E650_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010E6FC_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010E734_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010E78C_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010ED44_stacked_deck);

void func_8010EFBC_stacked_deck(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010EFC4_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010F134_stacked_deck);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", D_8010F6E8_stacked_deck);
