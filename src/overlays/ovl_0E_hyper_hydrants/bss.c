#include "common.h"
#include "overlays/minigame.h"
#include "hyper_hydrants.h"

/*
 * Several arrays in this overlay's BSS are only halfword or byte aligned, which
 * GCC won't produce for standalone arrays. They are grouped into structs here,
 * and the field symbols used by the original code are aliased in undefined_syms.txt.
 */
typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x02 */ s16 unk02[2];
    /* 0x06 */ s8 unk06;
} HyperHydrantsBssBF40;

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02[2];
} HyperHydrantsBssBF88;

typedef struct {
    /* 0x00 */ s8 unk00[2];
    /* 0x02 */ s8 unk02[2];
} HyperHydrantsBssBFAC;

typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x02 */ s16 unk02[2];
    /* 0x06 */ s16 unk06[2];
    /* 0x0A */ s16 unk0A[2][2];
    /* 0x12 */ s16 unk12[2];
} HyperHydrantsBssC010;

HyperHydrantsBssBF40 hyperHydrantsBssBF40 BSS;
s32 D_8010BF48_hyper_hydrants BSS;
s32 D_8010BF4C_hyper_hydrants BSS;
s8 D_8010BF50_hyper_hydrants BSS;
s16 D_8010BF52_hyper_hydrants BSS;
s16 D_8010BF54_hyper_hydrants BSS;
s16 D_8010BF56_hyper_hydrants BSS;
s16 D_8010BF58_hyper_hydrants BSS;
u8 D_8010BF5C_hyper_hydrants[4] BSS; /* Unreferenced. */
D_80111B50_vine_with_me_Struct D_8010BF60_hyper_hydrants BSS;
HyperHydrantsBssBF88 hyperHydrantsBssBF88 BSS;
s16 D_8010BF8E_hyper_hydrants BSS;
s16 D_8010BF90_hyper_hydrants BSS;
u8 *D_8010BF94_hyper_hydrants[2] BSS;
s32 D_8010BF9C_hyper_hydrants BSS;
s32 D_8010BFA0_hyper_hydrants BSS;
s32 D_8010BFA4_hyper_hydrants BSS;
s8 D_8010BFA8_hyper_hydrants BSS;
s8 D_8010BFA9_hyper_hydrants BSS;
s8 D_8010BFAA_hyper_hydrants BSS;
s8 D_8010BFAB_hyper_hydrants BSS;
HyperHydrantsBssBFAC hyperHydrantsBssBFAC BSS;
HyperHydrantsChainPoint *D_8010BFB0_hyper_hydrants[2][6] BSS;
omObjData *D_8010BFE0_hyper_hydrants[2] BSS;
omObjData *D_8010BFE8_hyper_hydrants[2][5] BSS;
HyperHydrantsBssC010 hyperHydrantsBssC010 BSS;
Vec D_8010C028_hyper_hydrants[2] BSS;
