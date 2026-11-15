#include "common.h"
#include "mstory4.h"

// Misaligned u16 array after an s16 (see undefined_syms.txt for aliases).
typedef struct Mstory4Bss2348 {
    /* 0x00 */ s16 unk00;       // D_80112348_mstory4
    /* 0x02 */ u16 unk02[2][2]; // D_8011234A_mstory4
} Mstory4Bss2348;               // sizeof 0x0A

// Misaligned s16 array after an s16 (see undefined_syms.txt for aliases).
typedef struct Mstory4Bss23A4 {
    /* 0x00 */ s16 unk00;    // D_801123A4_mstory4
    /* 0x02 */ s16 unk02[2]; // D_801123A6_mstory4
} Mstory4Bss23A4;            // sizeof 0x06

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */

/* main.c */
s16 D_80112120_mstory4 BSS;
s16 D_80112122_mstory4 BSS;
s32 D_80112124_mstory4 BSS;
u16 D_80112128_mstory4 BSS;
u8 D_8011212C_mstory4[4] BSS; /* Unreferenced. */
s16 D_80112130_mstory4[8] BSS;
s16 D_80112140_mstory4[7][8] BSS;
s16 D_801121B0_mstory4 BSS;
s32 D_801121B4_mstory4 BSS;
u8 D_801121B8_mstory4[8] BSS; /* Unreferenced. */

/* scene0.c */
UnkStoryObj D_801121C0_mstory4[5] BSS;
s32 D_80112238_mstory4[4] BSS; // [i] low halves: D_8011223A/E_mstory4, D_80112242/6_mstory4
s16 D_80112248_mstory4 BSS;
u8 D_8011224C_mstory4[4] BSS; /* Unreferenced. */
Vec D_80112250_mstory4 BSS;
Vec D_8011225C_mstory4 BSS;
Vec D_80112268_mstory4 BSS;
Vec D_80112274_mstory4 BSS;
Vec D_80112280_mstory4 BSS;
s16 D_8011228C_mstory4 BSS;
s16 D_8011228E_mstory4 BSS;
s16 D_80112290_mstory4[4] BSS;
u8 D_80112298_mstory4[8] BSS; /* Unreferenced. */

/* scene1.c */
UnkStoryObj D_801122A0_mstory4[4] BSS;
Vec D_80112300_mstory4 BSS;
Vec D_8011230C_mstory4 BSS;
Vec D_80112318_mstory4 BSS;
s16 D_80112324_mstory4 BSS;
s16 D_80112326_mstory4 BSS;
s16 D_80112328_mstory4[5] BSS;
u8 D_80112334_mstory4[4] BSS;  /* Unreferenced. */
s32 D_80112338_mstory4[4] BSS; // [3] low half: D_80112346_mstory4
Mstory4Bss2348 mstory4Bss2348 BSS;
s16 D_80112352_mstory4 BSS;
u8 D_80112354_mstory4[4] BSS;  /* Unreferenced. */
s16 D_80112358_mstory4[8] BSS; // [7]: D_80112366_mstory4
s16 D_80112368_mstory4[8] BSS; // [7]: D_80112376_mstory4
s16 D_80112378_mstory4[22] BSS;
Mstory4Bss23A4 mstory4Bss23A4 BSS;
u8 D_801123AC_mstory4[4] BSS; /* Unreferenced. */

/* main.c */
s32 D_801123B0_mstory4[4] BSS;
