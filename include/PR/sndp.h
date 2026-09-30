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

typedef struct ALFilter_s {
    struct ALFilter_s *source;
    Acmd *(*handler)(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *cmdList);
    s32 (*setParam)(void *filter, s32 paramID, void *param);
} ALFilter;

/* Per voice filter. Sample loading, resampling and the envelope generator are
 * all kept in this single object, so the layout is the libultra load filter,
 * resampler and envelope mixer layouts laid end to end. */
typedef struct {
    /* 0x00 */ ALFilter filter;
    /* 0x0C */ ADPCM_STATE *state;
    /* 0x10 */ ADPCM_STATE *lstate;
    /* 0x14 */ s32 loopStart;
    /* 0x18 */ s32 loopEnd;
    /* 0x1C */ s32 loopCount;
    /* 0x20 */ struct ALWaveTable_s *table;
    /* 0x24 */ s32 bookSize;
    /* 0x28 */ void *dmaState;
    /* 0x2C */ void *unk_2C;
    /* 0x30 */ s32 sample;
    /* 0x34 */ s32 lastsam;
    /* 0x38 */ s32 loadFirst;
    /* 0x3C */ s32 memin;
    /* 0x40 */ void *rsState;
    /* 0x44 */ f32 rsRatio;
    /* 0x48 */ s32 rsUpitch;
    /* 0x4C */ f32 rsDelta;
    /* 0x50 */ s32 rsFirst;
    /* 0x54 */ void *envState;
    /* 0x58 */ s16 pan;
    /* 0x5A */ s16 volume;
    /* 0x5C */ s16 cvolL;
    /* 0x5E */ s16 cvolR;
    /* 0x60 */ s16 dryamt;
    /* 0x62 */ s16 wetamt;
    /* 0x64 */ u16 lratl;
    /* 0x66 */ s16 lratm;
    /* 0x68 */ s16 ltgt;
    /* 0x6A */ u16 rratl;
    /* 0x6C */ s16 rratm;
    /* 0x6E */ s16 rtgt;
    /* 0x70 */ s32 delta;
    /* 0x74 */ s32 segEnd;
    /* 0x78 */ s32 first;
    /* 0x7C */ ALParam *ctrlList;
    /* 0x80 */ ALParam *ctrlTail;
    /* 0x84 */ s32 motion;
} ALEnvMixer;

/* A physical voice is either linked into one of the audio manager lists or
 * owned by one of the voice filters, both of which start at offset 0. */
typedef struct PVoice_s {
    union {
        ALLink queue;
        ALEnvMixer envmixer;
    } p;
    s32 offset;
} PVoice;

/*
 * The game keeps its single ALSndPlayer inside a global audio manager
 * object; the sound player lives at offset 0x0C.
 */
typedef struct AudioManager_s {
    /* 0x00 */ ALPlayer *head;
    /* 0x04 */ char unk_04[0x08];
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
