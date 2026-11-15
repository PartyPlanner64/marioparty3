#define NO_EXTERN_VARIABLES
#include "common.h"
#include "chancetime.h"

// Misaligned s16 array after an s8 (see undefined_syms.txt for aliases).
typedef struct ChanceTimeBssFE78 {
    /* 0x00 */ s8 unk00;     // D_8010FE78_chancetime
    /* 0x02 */ s16 unk02[3]; // D_8010FE7A_chancetime
} ChanceTimeBssFE78;         // sizeof 0x08

// Misaligned s8 array after an s8 (see undefined_syms.txt for aliases).
typedef struct ChanceTimeBss00DC {
    /* 0x00 */ s8 unk00;    // D_801100DC_chancetime
    /* 0x01 */ s8 unk01[3]; // D_801100DD_chancetime, [2] = D_801100DF_chancetime
} ChanceTimeBss00DC;        // sizeof 0x04

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */
s32 D_8010FE60_chancetime BSS;
s8 D_8010FE64_chancetime[3] BSS;
u8 D_8010FE68_chancetime[8] BSS; /* Unreferenced. */
s32 D_8010FE70_chancetime BSS;
s32 D_8010FE74_chancetime BSS;
ChanceTimeBssFE78 chanceTimeBssFE78 BSS;
s16 D_8010FE80_chancetime[2] BSS;
s32 D_8010FE84_chancetime[2] BSS;
s32 D_8010FE8C_chancetime BSS;
s16 D_8010FE90_chancetime BSS;
s16 D_8010FE92_chancetime BSS;
s16 D_8010FE94_chancetime[3] BSS;
u16 D_8010FE9A_chancetime BSS;
HuSprite *D_8010FE9C_chancetime BSS;
void *D_8010FEA0_chancetime BSS;
void *D_8010FEA4_chancetime BSS;
s16 D_8010FEA8_chancetime[2] BSS;
u8 D_8010FEAC_chancetime[4] BSS; /* Unreferenced. */
s16 D_8010FEB0_chancetime[3][3] BSS;
s32 D_8010FEC4_chancetime BSS;
s8 D_8010FEC8_chancetime BSS;
s8 D_8010FEC9_chancetime BSS;
u8 D_8010FECC_chancetime[4] BSS; /* Unreferenced. */
ChanceTimeUnkFED0 D_8010FED0_chancetime[3] BSS;
s32 D_8010FF48_chancetime[3] BSS;
u8 D_8010FF54_chancetime[12] BSS; /* Unreferenced. */
ChanceTimeTransfer D_8010FF60_chancetime[20] BSS;
s8 D_80110000_chancetime BSS;
s32 D_80110004_chancetime BSS;
s32 D_80110008_chancetime BSS;
u8 D_8011000C_chancetime[4] BSS; /* Unreferenced. */
s16 D_80110010_chancetime[10] BSS;
u8 D_80110024_chancetime[4] BSS; /* Unreferenced. */
s16 D_80110028_chancetime[20] BSS;
u8 D_80110050_chancetime[0x30] BSS; /* Unreferenced. */
omObjData *D_80110080_chancetime BSS;
void (*D_80110084_chancetime)() BSS;
ChanceTimeObjState D_80110088_chancetime[5] BSS;
ChanceTimeObjState D_801100B0_chancetime BSS;
ChanceTimeObjState D_801100B8_chancetime BSS;
ChanceTimeObjState D_801100C0_chancetime BSS;
omObjData *D_801100C8_chancetime BSS;
void (*D_801100CC_chancetime)(omObjData *) BSS;
s8 D_801100D0_chancetime[4] BSS;
ChanceTimeObjState D_801100D4_chancetime BSS;
ChanceTimeBss00DC chanceTimeBss00DC BSS;
