#ifndef _AUDIO_SNDP_H_
#define _AUDIO_SNDP_H_

#include <PR/libaudio.h>

typedef struct ALSoundState_s {
    /* 0x00 */ ALVoice voice;
    /* 0x1C */ ALSound *sound;
    /* 0x20 */ s16 priority;
    /* 0x24 */ f32 pitch;
    /* 0x28 */ s32 state;
    /* 0x2C */ s16 vol;
    /* 0x2E */ ALPan pan;
    /* 0x2F */ u8 fxMix;
} ALSoundState; // size 0x30

/*
 * The game keeps its single ALSndPlayer inside a global audio manager
 * object; the sound player lives at offset 0x0C.
 */
typedef struct AudioManager_s {
    /* 0x00 */ char unk_00[0x0C];
    /* 0x0C */ ALSndPlayer *sndp;
    /* 0x10 */ ALLink pFreeList;
    /* 0x18 */ ALLink unk_18;
    /* 0x20 */ ALLink pLameList;
    /* 0x28 */ s32 curSamples;
    /* 0x2C */ s32 lastSamples;
    /* 0x30 */ char unk_30[0x08];
    /* 0x38 */ ALParam *freeParamList;
} AudioManager;

extern AudioManager *D_800A2884_main;

#endif
