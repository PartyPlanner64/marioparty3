#ifndef _N_SYNTHINTERNALS_H_
#define _N_SYNTHINTERNALS_H_

#include <PR/n_libaudio.h>
#include <PR/abi.h>

/*
 * Internal definitions for the libultra n_audio library (libn_audio).
 */

/* Filter message ids handled by the n_audio voice filters. */
enum {
    AL_FILTER_FREE_VOICE = 0,
    AL_FILTER_ADD_UPDATE = 3,
    AL_FILTER_RESET = 4,
    AL_FILTER_SET_WAVETABLE = 5,
    AL_FILTER_SET_PITCH = 7,
    AL_FILTER_SET_UNITY_PITCH = 8,
    AL_FILTER_START = 9,
    AL_FILTER_SET_VOLUME = 11,
    AL_FILTER_SET_PAN = 12,
    AL_FILTER_START_VOICE_ALT = 13,
    AL_FILTER_START_VOICE = 14,
    AL_FILTER_STOP_VOICE = 15,
    AL_FILTER_SET_FXAMT = 16
};

typedef struct {
    struct ALParam_s *next;
    s32 delta;
    s16 type;
    s16 unity; /* disable resampler */
    f32 pitch;
    s16 volume;
    ALPan pan;
    u8 fxMix;
    s32 samples;
    struct ALWaveTable_s *wave;
} ALStartParamAlt;

typedef struct {
    struct ALParam_s *next;
    s32 delta;
    s16 type;
    s16 unity; /* disable resampler */
    struct ALWaveTable_s *wave;
} ALStartParam;

typedef struct {
    struct ALParam_s *next;
    s32 delta;
    s16 type;
    struct N_PVoice_s *pvoice;
} ALFreeParam;

/*
 * A physical voice. Unlike the standard library, the sample loader,
 * resampler and envelope mixer state are all kept in this single object.
 */
typedef struct N_PVoice_s {
    /* 0x00 */ ALLink node;
    /* 0x08 */ struct N_ALVoice_s *vvoice;
    /** ALLoadFilter *********************************/
    /* 0x0C */ ADPCM_STATE *dc_state;
    /* 0x10 */ ADPCM_STATE *dc_lstate;
    /* 0x14 */ ALRawLoop dc_loop;
    /* 0x20 */ struct ALWaveTable_s *dc_table;
    /* 0x24 */ s32 dc_bookSize;
    /* 0x28 */ ALDMAproc dc_dma;
    /* 0x2C */ void *dc_dmaState;
    /* 0x30 */ s32 dc_sample;
    /* 0x34 */ s32 dc_lastsam;
    /* 0x38 */ s32 dc_first;
    /* 0x3C */ s32 dc_memin;
    /** ALResampler *********************************/
    /* 0x40 */ RESAMPLE_STATE *rs_state;
    /* 0x44 */ f32 rs_ratio;
    /* 0x48 */ s32 rs_upitch;
    /* 0x4C */ f32 rs_delta;
    /* 0x50 */ s32 rs_first;
    /** ALEnvMixer *********************************/
    /* 0x54 */ ENVMIX_STATE *em_state;
    /* 0x58 */ s16 em_pan;
    /* 0x5A */ s16 em_volume;
    /* 0x5C */ s16 em_cvolL;
    /* 0x5E */ s16 em_cvolR;
    /* 0x60 */ s16 em_dryamt;
    /* 0x62 */ s16 em_wetamt;
    /* 0x64 */ u16 em_lratl;
    /* 0x66 */ s16 em_lratm;
    /* 0x68 */ s16 em_ltgt;
    /* 0x6A */ u16 em_rratl;
    /* 0x6C */ s16 em_rratm;
    /* 0x6E */ s16 em_rtgt;
    /* 0x70 */ s32 em_delta;
    /* 0x74 */ s32 em_segEnd;
    /* 0x78 */ s32 em_first;
    /* 0x7C */ ALParam *em_ctrlList;
    /* 0x80 */ ALParam *em_ctrlTail;
    /* 0x84 */ s32 em_motion;
    /* 0x88 */ s32 offset;
} N_PVoice;

/* Per-sound state kept by the n_audio sound player. */
typedef struct N_ALSoundState_s {
    /* 0x00 */ N_ALVoice voice;
    /* 0x1C */ ALSound *sound;
    /* 0x20 */ s16 priority;
    /* 0x24 */ f32 pitch;
    /* 0x28 */ s32 state;
    /* 0x2C */ s16 vol;
    /* 0x2E */ ALPan pan;
    /* 0x2F */ u8 fxMix;
} N_ALSoundState; // size 0x30

/*
 * prototypes for private driver functions
 */
ALParam *__n_allocParam(void);
void __n_freeParam(ALParam *param);
void _n_freePVoice(N_PVoice *pvoice);
void _n_collectPVoices(void);
s32 _n_timeToSamplesNoRound(s32 micros);
s32 _n_timeToSamples(s32 micros);

s32 n_alLoadParam(N_PVoice *filter, s32 paramID, void *param);
Acmd *n_alResamplePull(N_PVoice *filter, s16 *outp, Acmd *p);
Acmd *n_alEnvmixerPull(N_PVoice *filter, s32 sampleOffset, Acmd *p);
s32 n_alEnvmixerParam(N_PVoice *filter, s32 paramID, void *param);

#endif
