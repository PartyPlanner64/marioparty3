#ifndef _COSMIC_COASTER_H
#define _COSMIC_COASTER_H

#include "common.h"

// Track objects have no motions, so the omObjData motion pointer slot instead
// holds the distance to the nearest light source as an f32.
#define COSMIC_COASTER_LIGHT_DIST(object) (*(f32 *)&(object)->motion)

// Track object placement entry. Lists are terminated by a 0xFFFF type, and
// each entry is spawned once a car comes within range of its z distance.
typedef struct CosmicCoasterSpawn { // 0x10 bytes
    u16 type;
    f32 x;
    f32 y;
    f32 z;
} CosmicCoasterSpawn;

// Object data of the two coaster cars, with per-rider state for both riders.
// targetX is the lane x position a rider steers toward; it holds the 100000.0f
// sentinel while no target is assigned. carried is the track object that the
// target was chosen for, and state is its live-assignment flag.
typedef struct CosmicCoasterCarData { // 0x54 bytes
    s16 group;                        // 0x00
    s16 player[2];                    // 0x02
    u16 finished;                     // 0x06
    f32 progress;                     // 0x08
    f32 prevProgress;                 // 0x0C progress of the previous frame
    f32 x[2];                         // 0x10
    f32 tilt[2];                      // 0x18 rider tilt after hitting an obstacle
    u16 stunTimer[2];                 // 0x20 frames before the tilt recovers
    u16 visible[2];                   // 0x24 toggled to blink a stunned rider
    u16 endPhase;                     // 0x28 victory sequence phase
    u8 pad2A[2];                      // 0x2A
    f32 rotY[2];                      // 0x2C
    f32 y[2];                         // 0x34
    f32 targetX[2];                   // 0x3C
    omObjData *carried[2];            // 0x44
    u16 state[2];                     // 0x4C
    u16 hasHuman;                     // 0x50
    s16 rollSfx;                      // 0x52 rolling sound, -1 when not playing
} CosmicCoasterCarData;

#ifndef NO_EXTERN_VARIABLES
extern omObjData *m216_carObjTbl[2];
extern s16 m216_winner;
extern omObjData *m216_stageObj; // track object manager
#endif

void m216_OvlReturn(void);
void m216_StageObjInit(omObjData *object);
u32 m216_StageHitCheck(omObjData **found, CosmicCoasterCarData *car, f32 ahead, f32 behind, u16 notify);
s32 m216_ComLaneMaskGet(omObjData *object, s32 slot, omObjData *target);

#endif
