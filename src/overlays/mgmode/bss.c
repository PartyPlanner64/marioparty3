#include "common.h"
#include "game/gamemes.h"
#include "overlays/mgmode.h"

// Misaligned s8 array after an s16 (see undefined_syms.txt for aliases).
typedef struct MgmodeBssB3E4 {
    /* 0x00 */ s16 unk00;   // D_8011B3E4_mgmode
    /* 0x02 */ s8 unk02[4]; // D_8011B3E6_mgmode
} MgmodeBssB3E4;            // sizeof 0x06

// Misaligned s16 arrays after a u8 (see undefined_syms.txt for aliases).
typedef struct MgmodeBssB434 {
    /* 0x00 */ u8 unk00;     // D_8011B434_mgmode
    /* 0x02 */ s16 unk02[4]; // D_8011B436_mgmode
    /* 0x0A */ s16 unk0A[4]; // D_8011B43E_mgmode
    /* 0x12 */ s16 unk12[4]; // D_8011B446_mgmode
} MgmodeBssB434;             // sizeof 0x1A

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */
s16 D_8011A700_mgmode BSS;
u8 D_8011A704_mgmode[4] BSS; /* Unreferenced. */
char D_8011A708_mgmode[0x100] BSS;
HuMtx4F D_8011A808_mgmode BSS;
HuMtx4F D_8011A848_mgmode BSS;
HuMtx4F D_8011A888_mgmode BSS;
u8 D_8011A8C8_mgmode[8][20] BSS;
u8 D_8011A968_mgmode[8] BSS;
u8 D_8011A970_mgmode[8][20] BSS;
u8 D_8011AA10_mgmode[8] BSS;
MgmodeSpaceCoord D_8011AA18_mgmode[26] BSS;
Vec D_8011AA80_mgmode[8][25] BSS;
u16 *D_8011B3E0_mgmode BSS;
MgmodeBssB3E4 mgmodeBssB3E4 BSS;
MgmodeEsprite *D_8011B3EC_mgmode BSS;

HuMtx4F D_8011B3F0_mgmode BSS;
u8 D_8011B430_mgmode[4] BSS;
MgmodeBssB434 mgmodeBssB434 BSS;
MgmodeEsprite *D_8011B450_mgmode BSS;
s16 D_8011B454_mgmode BSS;
s16 D_8011B458_mgmode[8] BSS;
MgmodeSpaceCoord D_8011B468_mgmode[6] BSS;
MgmodeEsprite *D_8011B480_mgmode BSS;
s16 D_8011B484_mgmode BSS;
u16 D_8011B488_mgmode[28] BSS;
s16 D_8011B4C0_mgmode BSS;
u8 D_8011B4C4_mgmode[12] BSS; /* Unreferenced. */

HuMtx4F D_8011B4D0_mgmode BSS;
u8 D_8011B510_mgmode[256] BSS;
u8 *D_8011B610_mgmode[3] BSS;
s16 D_8011B61C_mgmode BSS;
s16 D_8011B61E_mgmode BSS;
s16 D_8011B620_mgmode BSS;
s16 D_8011B622_mgmode BSS;
s16 D_8011B624_mgmode BSS;
u8 D_8011B628_mgmode[8] BSS; /* Unreferenced. */

u8 D_8011B630_mgmode[0x20] BSS;
s16 D_8011B650_mgmode BSS;
s16 D_8011B652_mgmode BSS;
u16 *D_8011B654_mgmode[3] BSS;
void *D_8011B660_mgmode BSS;
s16 D_8011B664_mgmode BSS;
s16 D_8011B666_mgmode BSS;
s16 D_8011B668_mgmode BSS;
s16 D_8011B66A_mgmode BSS;
s16 D_8011B66C_mgmode BSS;
s16 D_8011B66E_mgmode BSS;
MgmodeSpaceCoord *D_8011B670_mgmode BSS;
u8 D_8011B674_mgmode[4] BSS; /* Unreferenced. */
s16 D_8011B678_mgmode[4][4] BSS;
s16 D_8011B698_mgmode[4] BSS;

s16 D_8011B6A0_mgmode BSS;
f32 D_8011B6A4_mgmode BSS;
s16 D_8011B6A8_mgmode BSS;
u8 D_8011B6AC_mgmode[4] BSS; /* Unreferenced. */
u8 D_8011B6B0_mgmode[8][25] BSS;
u8 D_8011B778_mgmode BSS;
s16 D_8011B77A_mgmode BSS;
u8 D_8011B77C_mgmode[4] BSS; /* Unreferenced. */
s16 D_8011B780_mgmode[64] BSS;
s16 D_8011B800_mgmode BSS;
f32 D_8011B804_mgmode BSS;
s16 D_8011B808_mgmode BSS;
s16 D_8011B80A_mgmode BSS;
u8 D_8011B80C_mgmode[4] BSS; /* Unreferenced. */
GAMEMES D_8011B810_mgmode BSS;
s16 D_8011B884_mgmode BSS;
f32 D_8011B888_mgmode BSS;
Vec D_8011B88C_mgmode BSS;
Vec D_8011B898_mgmode BSS;
u8 D_8011B8A4_mgmode BSS;
s16 D_8011B8A8_mgmode[64] BSS;
s16 D_8011B928_mgmode[8] BSS;
f32 D_8011B938_mgmode BSS;
u8 D_8011B93C_mgmode[4] BSS; /* Unreferenced. */
s16 D_8011B940_mgmode[8] BSS;
s16 D_8011B950_mgmode BSS;
ModeCameraPreset *D_8011B954_mgmode BSS;
u8 D_8011B958_mgmode BSS;
s16 D_8011B95A_mgmode BSS;
