#include "common.h"
#include "mstory3.h"

// Misaligned s16 arrays between s16 scalars (see undefined_syms.txt for aliases).
typedef struct Mstory3BssC80 {
    /* 0x00 */ s16 unk00[3]; // D_80115C80_mstory3
    /* 0x06 */ s16 unk06;    // D_80115C86_mstory3
    /* 0x08 */ s16 unk08;    // D_80115C88_mstory3
    /* 0x0A */ s16 unk0A[3]; // D_80115C8A_mstory3
    /* 0x10 */ s16 unk10;    // D_80115C90_mstory3
    /* 0x12 */ s16 unk12[3]; // D_80115C92_mstory3
    /* 0x18 */ s16 unk18;    // D_80115C98_mstory3
    /* 0x1A */ s16 unk1A;    // D_80115C9A_mstory3
} Mstory3BssC80;             // sizeof 0x1C

// Two s16 arrays, the second one misaligned (see undefined_syms.txt for aliases).
typedef struct Mstory3BssC9C {
    /* 0x00 */ s16 unk00[3]; // D_80115C9C_mstory3 ([1]: D_80115C9E_mstory3)
    /* 0x06 */ s16 unk06[7]; // D_80115CA2_mstory3
} Mstory3BssC9C;             // sizeof 0x14

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */

/* 4B29E0 */
s16 D_80115B90_mstory3 BSS;
s16 D_80115B92_mstory3 BSS;
u16 D_80115B94_mstory3 BSS;
s16 D_80115B96_mstory3 BSS;
s16 D_80115B98_mstory3[8] BSS;
s16 D_80115BA8_mstory3[8] BSS;
s16 D_80115BB8_mstory3 BSS;
s32 D_80115BBC_mstory3 BSS;

/* 4B4DC0 */
UnkMstory3Obj D_80115BC0_mstory3[6] BSS;
u8 D_80115C38_mstory3[12] BSS; /* Unreferenced. */
Vec D_80115C44_mstory3 BSS;
Vec D_80115C50_mstory3 BSS;
Vec D_80115C5C_mstory3 BSS;
Vec D_80115C68_mstory3 BSS;
Vec D_80115C74_mstory3 BSS; /* Unreferenced. */
Mstory3BssC80 mstory3BssC80 BSS;
Mstory3BssC9C mstory3BssC9C BSS;

/* 4B9A30 */
UnkMstory3Obj D_80115CB0_mstory3[11] BSS;
s16 D_80115D8C_mstory3 BSS;
s16 D_80115D8E_mstory3 BSS;
s16 D_80115D90_mstory3[3] BSS;
s16 D_80115D96_mstory3 BSS;
s16 D_80115D98_mstory3[5] BSS;
s16 D_80115DA2_mstory3 BSS;
s16 D_80115DA4_mstory3[5] BSS;
s16 D_80115DAE_mstory3 BSS;
s16 D_80115DB0_mstory3 BSS;
u8 D_80115DB4_mstory3[12] BSS; /* Unreferenced. */

/* 4B29E0 */
s16 D_80115DC0_mstory3[4] BSS;
