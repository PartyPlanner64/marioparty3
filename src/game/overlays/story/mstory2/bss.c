#include "common.h"
#include "mstory2.h"

// Per-scene s16 variables, some arrays misaligned (see undefined_syms.txt for aliases).
typedef struct Mstory2SceneBss {
    /* 0x00 */ s16 unk00[3];
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A[3];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12[3];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
} Mstory2SceneBss; // sizeof 0x20

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */

/* main.c */
s16 D_8011C640_mstory2 BSS;
s16 D_8011C642_mstory2 BSS;
s16 D_8011C644_mstory2 BSS;
u16 D_8011C646_mstory2 BSS;
s16 D_8011C648_mstory2 BSS;
u8 D_8011C64C_mstory2[4] BSS; /* Unreferenced. */
s16 D_8011C650_mstory2[8] BSS;
s16 D_8011C660_mstory2[8] BSS;
s16 D_8011C670_mstory2 BSS;
s32 D_8011C674_mstory2 BSS;
u8 D_8011C678_mstory2[8] BSS; /* Unreferenced. */

/* scene1.c */
UnkMstory2Obj D_8011C680_mstory2[6] BSS;
u8 D_8011C6F8_mstory2[12] BSS; /* Unreferenced. */
Vec D_8011C704_mstory2 BSS;
Vec D_8011C710_mstory2 BSS;
Vec D_8011C71C_mstory2 BSS;
Vec D_8011C728_mstory2 BSS;
Vec D_8011C734_mstory2 BSS; /* Unreferenced. */
Mstory2SceneBss mstory2BssC740 BSS;

/* scene2.c */
UnkMstory2Obj D_8011C760_mstory2[6] BSS;
u8 D_8011C7D8_mstory2[12] BSS; /* Unreferenced. */
Vec D_8011C7E4_mstory2 BSS;
Vec D_8011C7F0_mstory2 BSS;
Vec D_8011C7FC_mstory2 BSS;
Vec D_8011C808_mstory2 BSS;
Vec D_8011C814_mstory2 BSS; /* Unreferenced. */
Mstory2SceneBss mstory2BssC820 BSS;

/* scene3.c */
UnkMstory2Obj D_8011C840_mstory2[6] BSS;
u8 D_8011C8B8_mstory2[12] BSS; /* Unreferenced. */
Vec D_8011C8C4_mstory2 BSS;
Vec D_8011C8D0_mstory2 BSS;
Vec D_8011C8DC_mstory2 BSS;
Vec D_8011C8E8_mstory2 BSS;
Vec D_8011C8F4_mstory2 BSS; /* Unreferenced. */
Mstory2SceneBss mstory2BssC900 BSS;

/* scene4.c */
UnkMstory2Obj D_8011C920_mstory2[6] BSS;
u8 D_8011C998_mstory2[12] BSS; /* Unreferenced. */
Vec D_8011C9A4_mstory2 BSS;
Vec D_8011C9B0_mstory2 BSS;
Vec D_8011C9BC_mstory2 BSS;
Vec D_8011C9C8_mstory2 BSS;
Vec D_8011C9D4_mstory2 BSS; /* Unreferenced. */
Mstory2SceneBss mstory2BssC9E0 BSS;

/* scene0.c */
u8 D_8011CA00_mstory2[4] BSS; /* Unreferenced. */
f32 D_8011CA04_mstory2 BSS;
u8 D_8011CA08_mstory2[8] BSS; /* Unreferenced. */
UnkMstory2Obj D_8011CA10_mstory2[3] BSS;
s16 D_8011CA4C_mstory2 BSS;
Vec D_8011CA50_mstory2 BSS;
Vec D_8011CA5C_mstory2 BSS;
Vec D_8011CA68_mstory2 BSS; /* Unreferenced. */
s16 D_8011CA74_mstory2[3] BSS;
s16 D_8011CA7A_mstory2 BSS;
u8 D_8011CA7C_mstory2[4] BSS; /* Unreferenced. */

/* main.c */
s16 D_8011CA80_mstory2[4] BSS;
