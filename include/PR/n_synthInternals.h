#ifndef _N_SYNTHINTERNALS_H_
#define _N_SYNTHINTERNALS_H_

#include <PR/n_libaudio.h>
#include <PR/abi.h>
#include <PR/n_abi.h>

/*
 * Internal definitions for the libultra n_audio library (libn_audio).
 */

#define SAMPLES 184
#define SAMPLE184(delta) ((((delta) + (SAMPLES / 2)) / SAMPLES) * SAMPLES)
#define FIXED_SAMPLE SAMPLES

/* DMEM buffer locations used by the n_audio microcode. */
#define N_AL_DECODER_IN 0
#define N_AL_RESAMPLER_OUT 0
#define N_AL_TEMP_0 0
#define N_AL_DECODER_OUT 368
#define N_AL_TEMP_1 368
#define N_AL_TEMP_2 736
#define N_AL_MAIN_L_OUT 1248
#define N_AL_MAIN_R_OUT 1616
#define N_AL_AUX_L_OUT 1984
#define N_AL_AUX_R_OUT 2352

#define N_AL_DIVIDED 368

#define N_AL_MAX_RSP_SAMPLES 184

#define AL_MAX_AUX_BUS_SOURCES 8

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

typedef Acmd *(*N_ALCmdHandler)(s32, Acmd *);

typedef struct N_ALFilter_s {
    /* 0x00 */ struct N_ALFilter_s *source;
    /* 0x04 */ N_ALCmdHandler handler;
    /* 0x08 */ s32 (*setParam)(void *, s32, void *);
    /* 0x0C */ s16 inp;
    /* 0x0E */ s16 outp;
    /* 0x10 */ s32 type;
} N_ALFilter; // size 0x14

typedef struct N_ALMainBus_s {
    /* 0x00 */ N_ALFilter filter;
} N_ALMainBus;

typedef struct N_ALResampler_s {
    /* 0x00 */ N_ALFilter filter;
    /* 0x14 */ RESAMPLE_STATE *state;
    /* 0x18 */ f32 ratio;
    /* 0x1C */ s32 upitch;
    /* 0x20 */ f32 delta;
    /* 0x24 */ s32 first;
    /* 0x28 */ ALParam *ctrlList;
    /* 0x2C */ ALParam *ctrlTail;
    /* 0x30 */ s32 motion;
} N_ALResampler; // size 0x34

typedef struct {
    /* 0x00 */ s16 fc;
    /* 0x02 */ s16 fgain;
    /* 0x08 */ union {
        s16 fccoef[16];
        s64 force_aligned;
    } fcvec;
    /* 0x28 */ POLEF_STATE *fstate;
    /* 0x2C */ s32 first;
} N_ALLowPass; // size 0x30

typedef struct {
    /* 0x00 */ u32 input;
    /* 0x04 */ u32 output;
    /* 0x08 */ s16 ffcoef;
    /* 0x0A */ s16 fbcoef;
    /* 0x0C */ s16 gain;
    /* 0x10 */ f32 rsinc;
    /* 0x14 */ f32 rsval;
    /* 0x18 */ s32 rsdelta;
    /* 0x1C */ f32 rsgain;
    /* 0x20 */ N_ALLowPass *lp;
    /* 0x24 */ N_ALResampler *rs;
} N_ALDelay; // size 0x28

/* Effect (reverb) state. */
typedef struct N_ALFx_s {
    /* 0x00 */ N_ALFilter filter;
    /* 0x14 */ s16 *base;
    /* 0x18 */ s16 *input;
    /* 0x1C */ u32 length;
    /* 0x20 */ N_ALDelay *delay;
    /* 0x24 */ u8 section_count;
    /* 0x28 */ s32 (*paramHdl)(void *, s32, void *);
} N_ALFx; // size 0x2C

typedef struct N_ALAuxBus_s {
    /* 0x00 */ N_ALFilter filter;
    /* 0x14 */ s32 sourceCount;
    /* 0x18 */ s32 maxSources;
    /* 0x1C */ N_PVoice **sources;
    /* 0x20 */ N_ALFx *fx;
    /* 0x24 */ N_ALFx *fx_array[AL_MAX_AUX_BUS_SOURCES];
} N_ALAuxBus;

/* Sound player event types. */
typedef enum {
    AL_SNDP_PLAY_EVT,
    AL_SNDP_STOP_EVT,
    AL_SNDP_PAN_EVT,
    AL_SNDP_VOL_EVT,
    AL_SNDP_PITCH_EVT,
    AL_SNDP_API_EVT,
    AL_SNDP_DECAY_EVT,
    AL_SNDP_END_EVT,
    AL_SNDP_FX_EVT
} ALSndpMsgType;

typedef union {
    N_ALEvent msg;

    struct {
        s16 type;
        N_ALSoundState *state;
    } common;

    struct {
        s16 type;
        N_ALSoundState *state;
        s16 vol;
    } vol;

    struct {
        s16 type;
        N_ALSoundState *state;
        f32 pitch;
    } pitch;

    struct {
        s16 type;
        N_ALSoundState *state;
        ALPan pan;
    } pan;

    struct {
        s16 type;
        N_ALSoundState *state;
        u8 mix;
    } fx;
} N_ALSndpEvent;

/*
 * prototypes for private driver functions
 */
ALParam *__n_allocParam(void);
void __n_freeParam(ALParam *param);
void _n_freePVoice(N_PVoice *pvoice);
void _n_collectPVoices(void);
s32 _n_timeToSamplesNoRound(s32 micros);
s32 _n_timeToSamples(s32 micros);

/*
 * MP3 links its own versions of n_alSynStartVoiceParams (src/n_synstartvoiceparam.c) and
 * n_alSynSetPan (src/n_synsetpan.c) outside of the library.
 */
void func_80066270_main(N_ALVoice *v, ALWaveTable *w, f32 pitch, s16 vol, ALPan pan, u8 fxmix, ALMicroTime t);
void func_80066400_main(N_ALVoice *v, u8 pan);

void n_alLoadParam(N_PVoice *filter, s32 paramID, void *param);
Acmd *n_alResamplePull(N_PVoice *filter, s16 *outp, Acmd *p);
Acmd *n_alEnvmixerPull(N_PVoice *filter, s32 sampleOffset, Acmd *p);
s32 n_alEnvmixerParam(N_PVoice *filter, s32 paramID, void *param);
s32 n_alResampleParam(N_PVoice *filter, s32 paramID, void *param);
Acmd *n_alAdpcmPull(N_PVoice *filter, s16 *outp, s32 byteCount, Acmd *p);

Acmd *n_alSavePull(s32 sampleOffset, Acmd *p);
Acmd *n_alMainBusPull(s32 sampleOffset, Acmd *p);
Acmd *n_alAuxBusPull(s32 sampleOffset, Acmd *p);
Acmd *n_alFxPull(s32 sampleOffset, Acmd *p);
void n_alFxNew(N_ALFx **fx_ar, ALSynConfig *c, ALHeap *hp);
void alN_PVoiceNew(N_PVoice *mv, ALDMANew dmaNew, ALHeap *hp);

/* Shared with the standard library (src/2.0L/audio/drvrnew.c). */
void init_lpfilter(N_ALLowPass *lp);

#endif
