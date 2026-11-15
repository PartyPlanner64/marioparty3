#include "common.h"
#include "mstory5.h"

// Misaligned s16 arrays after an s16 (see undefined_syms.txt for aliases).
typedef struct Mstory5Bss5380 {
    /* 0x00 */ s16 unk00;    // D_80115380_mstory5
    /* 0x02 */ s16 unk02[4]; // D_80115382_mstory5 ([1]: D_80115384_mstory5)
    /* 0x0A */ s16 unk0A[4]; // D_8011538A_mstory5
} Mstory5Bss5380;            // sizeof 0x14

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */

/* main.c */
s16 D_801151B0_mstory5 BSS;
s16 D_801151B2_mstory5 BSS;
s32 D_801151B4_mstory5 BSS;
u16 D_801151B8_mstory5 BSS;
u8 D_801151BC_mstory5[4] BSS; /* Unreferenced. */
s16 D_801151C0_mstory5[8] BSS;
s16 D_801151D0_mstory5[8] BSS;
s16 D_801151E0_mstory5 BSS;
s32 D_801151E4_mstory5 BSS;
u8 D_801151E8_mstory5[8] BSS; /* Unreferenced. */

/* scene1.c */
UnkStoryObj D_801151F0_mstory5[9] BSS;
UnkStoryObj D_801152C8_mstory5 BSS;
UnkStoryObj D_801152E0_mstory5 BSS;
Vec D_801152F8_mstory5 BSS;
Vec D_80115304_mstory5 BSS;
Vec D_80115310_mstory5 BSS;
Vec D_8011531C_mstory5 BSS;
Vec D_80115328_mstory5 BSS;
Vec D_80115334_mstory5 BSS;
Vec D_80115340_mstory5 BSS;
Vec D_8011534C_mstory5 BSS;
Vec D_80115358_mstory5 BSS;
s16 D_80115364_mstory5 BSS;
s16 D_80115366_mstory5 BSS;
s16 D_80115368_mstory5 BSS;
u8 D_8011536C_mstory5[4] BSS;  /* Unreferenced. */
s32 D_80115370_mstory5[4] BSS; // [i] low halves: D_80115372/6/A/E_mstory5
Mstory5Bss5380 mstory5Bss5380 BSS;
u8 D_80115394_mstory5[12] BSS; /* Unreferenced. */

/* scene0.c */
UnkStoryObj D_801153A0_mstory5[8] BSS;
UnkStoryObj D_80115460_mstory5 BSS;
Vec D_80115478_mstory5 BSS;
Vec D_80115484_mstory5 BSS;
Vec D_80115490_mstory5 BSS;
Vec D_8011549C_mstory5 BSS;
Vec D_801154A8_mstory5 BSS;
Vec D_801154B4_mstory5 BSS;
Vec D_801154C0_mstory5 BSS;
Vec D_801154CC_mstory5 BSS;
s16 D_801154D8_mstory5 BSS;
s16 D_801154DA_mstory5 BSS;
s16 D_801154DC_mstory5[4] BSS;
s32 D_801154E4_mstory5[3] BSS; // [i] low halves: D_801154E6/A/E_mstory5
s16 D_801154F0_mstory5 BSS;
u8 D_801154F4_mstory5[4] BSS; /* Unreferenced. */
UnkMstory5Particle D_801154F8_mstory5[16] BSS;
u8 D_801156B8_mstory5[0x18] BSS; /* Unreferenced. */
