#ifndef _FRIDGED_BRIDGES_H
#define _FRIDGED_BRIDGES_H

#include "ultra64.h"

#include "game/hmfcoll.h"
#include "game/object.h"

// Per-camera collision work buffer passed to Hu3DCameraModelHookSet. Starts with the
// CollisionFan used by MapCullFan; the remainder is used by the custom
// fan-culling draw in m236_MapCullFanBatch.
typedef struct FridgedBridgesCamCollWork {
    /* 0x000 */ CollisionFan fan;
    /* 0x018 */ u16 dlCount[3];
    /* 0x020 */ HmfData hmf[3]; // copies of the model's HMF with a custom display list
    /* 0x2B8 */ Gfx gfx[3][100];
} FridgedBridgesCamCollWork; // sizeof 0xC18

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
    /* 0x20 */ u16 unk_20; // CPU: index of the next path point
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ u16 unk_26;
    /* 0x28 */ u16 unk_28;
    /* 0x2C */ omObjData *unk_2C; // camera target object, see m236_CameraTargetCreate
    /* 0x30 */ omObjData *bridgeObj;
    /* 0x34 */ Vec unk_34;
    /* 0x40 */ f32 unk_40; // bobbing angle while floating
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ u16 unk_48;
    /* 0x4A */ u16 unk_4A;
    /* 0x4C */ f32 unk_4C; // CPU speed multiplier
    /* 0x50 */ f32 scale;
    /* 0x54 */ u16 unk_54;
    /* 0x56 */ u16 unk_56;
    /* 0x58 */ u16 unk_58;
    /* 0x5A */ char unk_5A[0x2];
    /* 0x5C */ Vec pos;
    /* 0x68 */ s16 unk_68;
    /* 0x6A */ u16 unk_6A;
} FridgedBridgesPlayer; // sizeof 0x6C

#endif
