#ifndef _OVL_24_H
#define _OVL_24_H

#include "ultra64.h"

#include "game/object.h"

// Per-player state for this minigame. Lives in the `data` pointer (0x5C) of each
// of the four group 0 player objects.
typedef struct FridgedBridgesPlayer {
    /* 0x00 */ u16 state; // 0 when idle, 1 while sliding, 2 while frozen in place
    /* 0x02 */ s16 playerId;
    /* 0x04 */ u16 motionState; // 0 idle, 1 walking, 2 running
    /* 0x06 */ s16 unk_06;      // counts down while frozen
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 slideDist;
    /* 0x14 */ f32 slideDistTarget;
    /* 0x18 */ char unk_18[0x4];
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ u16 unk_26;
    /* 0x28 */ u16 unk_28;
    /* 0x2C */ omObjData *unk_2C; // camera target object, see func_8010BE0C
    /* 0x30 */ omObjData *bridgeObj;
    /* 0x34 */ Vec unk_34;
    /* 0x40 */ f32 unk_40; // bobbing angle while floating
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ u16 unk_48;
    /* 0x4A */ u16 unk_4A;
    /* 0x4C */ char unk_4C[0x4];
    /* 0x50 */ f32 scale;
    /* 0x54 */ u16 unk_54;
    /* 0x56 */ s16 unk_56;
    /* 0x58 */ u16 unk_58;
    /* 0x5A */ char unk_5A[0x2];
    /* 0x5C */ Vec pos;
    /* 0x68 */ s16 unk_68;
    /* 0x6A */ s16 unk_6A;
} FridgedBridgesPlayer; // sizeof 0x6C

#endif
