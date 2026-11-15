#define NO_EXTERN_VARIABLES
#include "common.h"
#include "overlays/minigame.h"

/*
 * Some arrays in this overlay's BSS are only halfword aligned, which GCC won't
 * produce for standalone arrays. They are grouped into structs here, and the
 * field symbols used by the original code are aliased in undefined_syms.txt.
 */
typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s8 unk02[6];
} MinigameBssC1B8;

typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s8 unk02[4];
    /* 0x06 */ s8 unk06;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ s16 unk0A[1];
} MinigameBssC280;

Vec D_800EBDC0_minigame BSS;
u8 D_800EBDCC_minigame[4] BSS; /* Unreferenced. */
Vec D_800EBDD0_minigame BSS;
u8 D_800EBDDC_minigame[4] BSS; /* Unreferenced. */
MinigameFlow *D_800EBDE0_minigame BSS;
s16 D_800EBDE4_minigame BSS;
s16 D_800EBDE6_minigame BSS;
s16 D_800EBDE8_minigame[4] BSS;
s16 D_800EBDF0_minigame BSS;
D_800EBDF4_minigame_Entry *D_800EBDF4_minigame BSS;
s16 D_800EBDF8_minigame BSS;
s16 D_800EBDFA_minigame BSS;
u16 D_800EBDFC_minigame BSS;
s16 D_800EBE00_minigame[4] BSS;
u8 D_800EBE08_minigame[8] BSS; /* Unreferenced. */
s16 D_800EBE10_minigame[4] BSS;
s16 D_800EBE18_minigame[4] BSS;
u8 D_800EBE20_minigame[4] BSS;
s32 D_800EBE24_minigame BSS;
u16 D_800EBE28_minigame BSS;
f32 D_800EBE2C_minigame BSS;
HuMtx4F D_800EBE30_minigame BSS;
omObjData *D_800EBE70_minigame[16] BSS;
Hu3DQuadPool D_800EBEB0_minigame BSS;
D_800EBEB8_minigame_Entry D_800EBEB8_minigame[64] BSS;
MinigameBssC1B8 minigameBssC1B8 BSS;
omObjData *D_800EC1C0_minigame[32] BSS;
HuMtx4F D_800EC240_minigame BSS;
MinigameBssC280 minigameBssC280 BSS;
Vec D_800EC28C_minigame[1] BSS;
Vec D_800EC298_minigame[64] BSS;
omObjData *D_800EC598_minigame[16] BSS;
f32 D_800EC5D8_minigame BSS;
u8 D_800EC5DC_minigame[4] BSS;
