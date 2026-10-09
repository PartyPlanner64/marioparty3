#ifndef _OVL_BABY_BOWSER_BROADSIDE_H
#define _OVL_BABY_BOWSER_BROADSIDE_H

#include "common.h"

typedef struct BabyBowserBroadsideWork { // 0x24 bytes, 0x8 entries
    /* 0x00 */ s8 unk_00;
    /* 0x01 */ char unk_01[3];
    /* 0x04 */ s32 unk_04; // flags
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ u8 unk_0A;
    /* 0x0C */ s16 unk_0C; // hmf model index
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ char unk_12[2];
    /* 0x14 */ f32 *unk_14;
    /* 0x18 */ f32 *unk_18;
    /* 0x1C */ f32 *unk_1C;
    /* 0x20 */ u8 unk_20[4];
} BabyBowserBroadsideWork; // Size 0x24

typedef struct BabyBowserBroadsideSprite { // 0x8 bytes, 0xE entries
    /* 0x00 */ s8 unk_00;                  // state
    /* 0x01 */ u8 unk_01;                  // sprite group id
    /* 0x02 */ u8 unk_02;                  // sprite frame index
    /* 0x03 */ char unk_03;
    /* 0x04 */ s16 unk_04; // frame count
    /* 0x06 */ s16 unk_06;
} BabyBowserBroadsideSprite; // Size 0x8

// One entry of the array that func_8010A0B4_baby_bowser_broadside appends to
// for each live effect. The callback at 0x40 is invoked from
// func_8010A2C4_baby_bowser_broadside.
typedef struct BabyBowserBroadsideHandler { // 0x44 bytes
    /* 0x00 */ s8 unk_00;
    /* 0x01 */ char unk_01;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ char unk_06[2];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s8 unk_0C;
    /* 0x0D */ s8 unk_0D;
    /* 0x0E */ char unk_0E[2];
    /* 0x10 */ s8 unk_10;
    /* 0x11 */ char unk_11[0xB];
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ char unk_20[0xC];
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ char unk_34[8];
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ void (*unk_40)();
} BabyBowserBroadsideHandler; // Size 0x44

// 0xC entries allocated by func_8010DAE8_baby_bowser_broadside
typedef struct BabyBowserBroadsideBoat { // 0xE4 bytes
    /* 0x00 */ s32 unk_00;               // flags
    /* 0x04 */ s8 unk_04;
    /* 0x05 */ char unk_05[0xDF];
} BabyBowserBroadsideBoat; // Size 0xE4

// Allocated as a single 0xC block by func_80109F64_baby_bowser_broadside
typedef struct BabyBowserBroadsideSlot { // 0xC bytes
    /* 0x00 */ omObjData *unk_00;
    /* 0x04 */ u16 *unk_04;
    /* 0x08 */ s16 unk_08;
} BabyBowserBroadsideSlot; // Size 0xC

// 0x7 entries allocated by func_80109ED0_baby_bowser_broadside
typedef struct BabyBowserBroadsideGroup { // 0x14 bytes, 0x7 entries
    /* 0x00 */ BabyBowserBroadsideSlot *unk_00;
    /* 0x04 */ BabyBowserBroadsideHandler *unk_04; // array of unk_08 live handlers
    /* 0x08 */ s16 unk_08;                         // live handler count
    /* 0x0A */ char unk_0A[2];
    /* 0x0C */ s32 unk_0C; // byte size of the unk_04 allocation
    /* 0x10 */ s8 unk_10;  // active flag
    /* 0x11 */ char unk_11[3];
} BabyBowserBroadsideGroup; // Size 0x14

// Per-ship movement state, 0x34 bytes. Allocated in
// func_80107140_baby_bowser_broadside and set up by func_8010E018_baby_bowser_broadside.
typedef struct BabyBowserBroadsideShip { // 0x34 bytes
    /* 0x00 */ s32 unk_00;               // flags
    /* 0x04 */ s16 *unk_04;              // ship index per player slot
    /* 0x08 */ s16 unk_08;               // slot count
    /* 0x0A */ char unk_0A[2];
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec facing;
    /* 0x24 */ f32 unk_24; // speed
    /* 0x28 */ s16 unk_28; // hmf model index
    /* 0x2A */ s16 unk_2A;
    /* 0x2C */ s16 unk_2C;
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ s16 unk_30;
    /* 0x32 */ char unk_32[2];
} BabyBowserBroadsideShip; // Size 0x34

extern BabyBowserBroadsideWork *D_80110010_baby_bowser_broadside;
extern BabyBowserBroadsideGroup *D_80110014_baby_bowser_broadside;
extern BabyBowserBroadsideSprite *D_80110018_baby_bowser_broadside;
extern BabyBowserBroadsideBoat *D_80110020_baby_bowser_broadside;

#endif
