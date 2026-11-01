#ifndef _GAME_MSM_H
#define _GAME_MSM_H

#include "ultra64.h"

/* Optional parameters for starting a sound effect. */
typedef struct {
    /* 0x00 */ s32 flags; // which of the fields below are valid
    /* 0x04 */ s32 slot;
    /* 0x08 */ s32 variant;
    /* 0x0C */ s32 vol;
    /* 0x10 */ s32 pitch;
    /* 0x14 */ s32 pan;
    /* 0x18 */ s32 fxMix;
    /* 0x1C */ s32 angle;
    /* 0x20 */ f32 dist;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
} SePlayParam; // size: 0x2C

#endif
