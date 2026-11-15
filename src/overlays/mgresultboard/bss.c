#define NO_EXTERN_VARIABLES
#include "common.h"
#include "overlays/mgresultboard.h"

// Misaligned s16 array after an s8 (see undefined_syms.txt for aliases).
typedef struct MgResultBoardBssAD94 {
    /* 0x00 */ s8 unk00;     // D_8010AD94_mgresultboard
    /* 0x02 */ s16 unk02[3]; // D_8010AD96_mgresultboard
} MgResultBoardBssAD94;      // sizeof 0x08

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */
s32 D_8010AD90_mgresultboard BSS;
MgResultBoardBssAD94 mgResultBoardBssAD94 BSS;
u8 D_8010AD9C_mgresultboard[0x14] BSS; /* Unreferenced. */
s32 D_8010ADB0_mgresultboard[8] BSS;
s32 D_8010ADD0_mgresultboard[40] BSS;
s32 D_8010AE70_mgresultboard[2] BSS;
u8 D_8010AE78_mgresultboard[8] BSS; /* Unreferenced. */
s32 D_8010AE80_mgresultboard[8] BSS;
omObjData *D_8010AEA0_mgresultboard BSS;
void (*D_8010AEA4_mgresultboard)(omObjData *) BSS;
UnkTemp D_8010AEA8_mgresultboard[4][5] BSS;
omObjData *D_8010AF98_mgresultboard BSS;
void (*D_8010AF9C_mgresultboard)(omObjData *) BSS;
omObjData *D_8010AFA0_mgresultboard BSS;
void (*D_8010AFA4_mgresultboard)(omObjData *) BSS;
omObjData *D_8010AFA8_mgresultboard BSS;
void (*D_8010AFAC_mgresultboard)(omObjData *) BSS;
UnkTemp D_8010AFB0_mgresultboard[4] BSS;
omObjData *D_8010AFE0_mgresultboard BSS;
void (*D_8010AFE4_mgresultboard)(omObjData *) BSS;
UnkTemp D_8010AFE8_mgresultboard[4] BSS;
PlayerResult D_8010B018_mgresultboard[4] BSS;
PlayerResult D_8010B048_mgresultboard[4] BSS;
