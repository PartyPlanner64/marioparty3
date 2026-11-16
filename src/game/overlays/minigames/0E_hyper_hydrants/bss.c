#include "common.h"
#include "game/overlays/minigame.h"
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
} HyperHydrantsPumpState;

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02[2];
} HyperHydrantsBackSpr;

typedef struct {
    /* 0x00 */ s8 unk00[2];
    /* 0x02 */ s8 unk02[2];
} HyperHydrantsSprayPower;

typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x02 */ s16 unk02[2];
    /* 0x06 */ s16 unk06[2];
    /* 0x0A */ s16 unk0A[2][2];
    /* 0x12 */ s16 unk12[2];
} HyperHydrantsHud;

HyperHydrantsPumpState m214_pumpState BSS;
s32 m214_bigFireCnt BSS;
s32 m214_fireCnt BSS;
s8 m214_hoseCnt BSS;
s16 m214_backAnim BSS;
s16 m214_irisAnim BSS;
s16 m214_frameAnim BSS;
s16 m214_frameSprGrp BSS;
u8 m214_frameSprGrpPad[4] BSS; /* Unreferenced. */
MinigameFlow m214_mgFlow BSS;
HyperHydrantsBackSpr m214_backSpr BSS;
s16 m214_irisSizeX BSS;
s16 m214_irisSizeY BSS;
u8 *m214_irisTexTbl[2] BSS;
s32 m214_irisRadius BSS;
s32 m214_irisX BSS;
s32 m214_irisY BSS;
s8 m214_pumper0No BSS;
s8 m214_pumper1No BSS;
s8 m214_sprayer0No BSS;
s8 m214_sprayer1No BSS;
HyperHydrantsSprayPower m214_sprayPower BSS;
HyperHydrantsHosePoint *m214_hoseTbl[2][6] BSS;
omObjData *m214_bigFireObjTbl[2] BSS;
omObjData *m214_fireObjTbl[2][5] BSS;
HyperHydrantsHud m214_hud BSS;
Vec m214_hydrantPosTbl[2] BSS;
