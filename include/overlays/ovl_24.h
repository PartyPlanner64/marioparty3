#ifndef _OVL_24_H
#define _OVL_24_H

#include "ultra64.h"

#include "game/object.h"

// Per-player state for this minigame. Lives in the `data` pointer (0x5C) of each
// of the four group 0 player objects.
typedef struct FridgedBridgesPlayer {
    /* 0x00 */ u16 state; // 0 when idle, 1 while sliding, 2 while frozen in place
    /* 0x02 */ u16 playerId;
    /* 0x04 */ s16 bridgeId; // index into the grid of ice bridges
    /* 0x06 */ u16 unk_06;   // counts down while frozen
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 slideDist;
    /* 0x14 */ f32 slideDistTarget;
    /* 0x18 */ char unk_18[0x6];
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ char unk_20[2];
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ u16 unk_26;
    /* 0x28 */ u16 unk_28;
    /* 0x2C */ void *unk_2C;
    /* 0x30 */ omObjData *bridgeObj;
    /* 0x34 */ char unk_34[0x1C];
    /* 0x50 */ f32 scale;
    /* 0x54 */ char unk_54[0x8];
    /* 0x5C */ Vec pos;
} FridgedBridgesPlayer; // sizeof 0x68

#endif
