#ifndef _COSMIC_COASTER_H
#define _COSMIC_COASTER_H

#include "common.h"

// Object data of the two coaster cars, with per-rider state for both riders.
// targetX is the lane x position a rider steers toward; it holds the 100000.0f
// sentinel while no target is assigned. carried is the track object that the
// target was chosen for, and state is its live-assignment flag.
typedef struct CosmicCoasterCarData { // 0x54 bytes
    s16 group;                        // 0x00
    s16 player[2];                    // 0x02
    u16 finished;                     // 0x06
    f32 progress;                     // 0x08
    f32 unk0C;                        // 0x0C
    f32 x[2];                         // 0x10
    f32 unk18[2];                     // 0x18
    s16 unk20[2];                     // 0x20
    s16 unk24[2];                     // 0x24
    u8 pad28[4];                      // 0x28
    f32 rotY[2];                      // 0x2C
    f32 y[2];                         // 0x34
    f32 targetX[2];                   // 0x3C
    omObjData *carried[2];            // 0x44
    u16 state[2];                     // 0x4C
    u16 hasHuman;                     // 0x50
    s16 unk52;                        // 0x52
} CosmicCoasterCarData;

extern omObjData *D_8010C3B0_cosmic_coaster[2];
extern s16 D_8010C3BC_cosmic_coaster;
extern omObjData *D_8010C3C4_cosmic_coaster; // track object manager

void func_80109900_cosmic_coaster(void);
void func_8010991C_cosmic_coaster(omObjData *object);
void func_8010B644_cosmic_coaster(omObjData **found, CosmicCoasterCarData *car, f32 ahead, f32 behind, s16 arg4);
s32 func_8010B97C_cosmic_coaster(omObjData *object, s32 slot, omObjData *target);

#endif
