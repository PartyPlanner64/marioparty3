#ifndef _SYNTHINTERNALS_H_
#define _SYNTHINTERNALS_H_

#include <PR/libaudio.h>
#include <PR/abi.h>

/*
 * Internal definitions for the standard libultra audio library (libaudio),
 * src/2.0L/audio. The n_audio library has its own n_synthInternals.h.
 */

/*
 * filter message ids
 */
enum {
    AL_FILTER_FREE_VOICE,
    AL_FILTER_SET_SOURCE,
    AL_FILTER_ADD_SOURCE,
    AL_FILTER_ADD_UPDATE,
    AL_FILTER_RESET,
    AL_FILTER_SET_WAVETABLE,
    AL_FILTER_SET_DRAM,
    AL_FILTER_SET_PITCH,
    AL_FILTER_SET_UNITY_PITCH,
    AL_FILTER_START,
    AL_FILTER_SET_STATE,
    AL_FILTER_SET_VOLUME,
    AL_FILTER_SET_PAN,
    AL_FILTER_START_VOICE_ALT,
    AL_FILTER_START_VOICE,
    AL_FILTER_STOP_VOICE,
    AL_FILTER_SET_FXAMT
};

#define AL_MAX_RSP_SAMPLES 160

/*
 * buffer locations based on AL_MAX_RSP_SAMPLES
 */
#define AL_DECODER_IN 0
#define AL_RESAMPLER_OUT 0
#define AL_TEMP_0 0
#define AL_DECODER_OUT 320
#define AL_TEMP_1 320
#define AL_TEMP_2 640
#define AL_MAIN_L_OUT 1088
#define AL_MAIN_R_OUT 1408
#define AL_AUX_L_OUT 1728
#define AL_AUX_R_OUT 2048

/*
 * filter types
 */
enum {
    AL_ADPCM,
    AL_RESAMPLE,
    AL_BUFFER,
    AL_SAVE,
    AL_ENVMIX,
    AL_FX,
    AL_AUXBUS,
    AL_MAINBUS
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
    struct PVoice_s *pvoice;
} ALFreeParam;

typedef Acmd *(*ALCmdHandler)(void *, s16 *, s32, s32, Acmd *);
typedef s32 (*ALSetParam)(void *, s32, void *);

typedef struct ALFilter_s {
    /* 0x00 */ struct ALFilter_s *source;
    /* 0x04 */ ALCmdHandler handler;
    /* 0x08 */ ALSetParam setParam;
    /* 0x0C */ s16 inp;
    /* 0x0E */ s16 outp;
    /* 0x10 */ s32 type;
} ALFilter; // size 0x14

#define AL_MAX_ADPCM_STATES 3 /* Depends on number of subframes per frame and loop length */

typedef struct {
    /* 0x00 */ ALFilter filter;
    /* 0x14 */ ADPCM_STATE *state;
    /* 0x18 */ ADPCM_STATE *lstate;
    /* 0x1C */ ALRawLoop loop;
    /* 0x28 */ struct ALWaveTable_s *table;
    /* 0x2C */ s32 bookSize;
    /* 0x30 */ ALDMAproc dma;
    /* 0x34 */ void *dmaState;
    /* 0x38 */ s32 sample;
    /* 0x3C */ s32 lastsam;
    /* 0x40 */ s32 first;
    /* 0x44 */ s32 memin;
} ALLoadFilter; // size 0x48

typedef struct ALResampler_s {
    /* 0x00 */ ALFilter filter;
    /* 0x14 */ RESAMPLE_STATE *state;
    /* 0x18 */ f32 ratio;
    /* 0x1C */ s32 upitch;
    /* 0x20 */ f32 delta;
    /* 0x24 */ s32 first;
    /* 0x28 */ ALParam *ctrlList;
    /* 0x2C */ ALParam *ctrlTail;
    /* 0x30 */ s32 motion;
} ALResampler; // size 0x34

typedef struct {
    /* 0x00 */ s16 fc;
    /* 0x02 */ s16 fgain;
    /* 0x08 */ union {
        s16 fccoef[16];
        s64 force_aligned;
    } fcvec;
    /* 0x28 */ POLEF_STATE *fstate;
    /* 0x2C */ s32 first;
} ALLowPass; // size 0x30

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
    /* 0x20 */ ALLowPass *lp;
    /* 0x24 */ ALResampler *rs;
} ALDelay; // size 0x28

typedef s32 (*ALSetFXParam)(void *, s32, void *);
typedef struct {
    /* 0x00 */ struct ALFilter_s filter;
    /* 0x14 */ s16 *base;
    /* 0x18 */ s16 *input;
    /* 0x1C */ u32 length;
    /* 0x20 */ ALDelay *delay;
    /* 0x24 */ u8 section_count;
    /* 0x28 */ ALSetFXParam paramHdl;
} ALFx; // size 0x2C

#define AL_MAX_MAIN_BUS_SOURCES 1
typedef struct ALMainBus_s {
    /* 0x00 */ ALFilter filter;
    /* 0x14 */ s32 sourceCount;
    /* 0x18 */ s32 maxSources;
    /* 0x1C */ ALFilter **sources;
} ALMainBus; // size 0x20

#define AL_MAX_AUX_BUS_SOURCES 8
#define AL_MAX_AUX_BUS_FX 1
typedef struct ALAuxBus_s {
    /* 0x00 */ ALFilter filter;
    /* 0x14 */ s32 sourceCount;
    /* 0x18 */ s32 maxSources;
    /* 0x1C */ ALFilter **sources;
    /* 0x20 */ ALFx fx[AL_MAX_AUX_BUS_FX];
} ALAuxBus; // size 0x4C

typedef struct ALSave_s {
    /* 0x00 */ ALFilter filter;
    /* 0x14 */ s32 dramout;
    /* 0x18 */ s32 first;
} ALSave; // size 0x1C

typedef struct ALEnvMixer_s {
    /* 0x00 */ ALFilter filter;
    /* 0x14 */ ENVMIX_STATE *state;
    /* 0x18 */ s16 pan;
    /* 0x1A */ s16 volume;
    /* 0x1C */ s16 cvolL;
    /* 0x1E */ s16 cvolR;
    /* 0x20 */ s16 dryamt;
    /* 0x22 */ s16 wetamt;
    /* 0x24 */ u16 lratl;
    /* 0x26 */ s16 lratm;
    /* 0x28 */ s16 ltgt;
    /* 0x2A */ u16 rratl;
    /* 0x2C */ s16 rratm;
    /* 0x2E */ s16 rtgt;
    /* 0x30 */ s32 delta;
    /* 0x34 */ s32 segEnd;
    /* 0x38 */ s32 first;
    /* 0x3C */ ALParam *ctrlList;
    /* 0x40 */ ALParam *ctrlTail;
    /* 0x44 */ ALFilter **sources;
    /* 0x48 */ s32 motion;
} ALEnvMixer; // size 0x4C

#define AL_CACHE_ALIGN 15

/*
 * synth stuff
 */
typedef struct PVoice_s {
    /* 0x00 */ ALLink node;
    /* 0x08 */ struct ALVoice_s *vvoice;
    /* 0x0C */ ALFilter *channelKnob;
    /* 0x10 */ ALLoadFilter decoder;
    /* 0x58 */ ALResampler resampler;
    /* 0x8C */ ALEnvMixer envmixer;
    /* 0xD8 */ s32 offset;
} PVoice; // size 0xDC

/*
 * Prototypes for the library's internal functions. Most are still named by
 * address; the libultra name of each is given alongside.
 */

/* heapalloc.c */
void *func_80077290_main(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size); /* alHeapDBAlloc */

/* filter.c */
void func_80075B00_main(ALFilter *f, ALCmdHandler h, ALSetParam s, s32 type); /* alFilterNew */

/* drvrnew.c */
void func_800733E0_main(ALLowPass *lp);                               /* init_lpfilter */
void func_80073484_main(ALFx *r, ALSynConfig *c, ALHeap *hp);         /* alFxNew */
void func_8007391C_main(ALEnvMixer *e, ALHeap *hp);                   /* alEnvmixerNew */
void func_800739D4_main(ALLoadFilter *f, ALDMANew dma, ALHeap *hp);   /* alLoadNew */
void func_80073A84_main(ALResampler *r, ALHeap *hp);                  /* alResampleNew */
void func_80073B10_main(ALAuxBus *m, void *sources, s32 maxSources);  /* alAuxBusNew */
void func_80073B6C_main(ALMainBus *m, void *sources, s32 maxSources); /* alMainBusNew */
void func_80073BC8_main(ALSave *f);                                   /* alSaveNew */

/* load.c */
Acmd *func_80073C10_main(void *f, s16 *outp, s32 byteCount, s32 sampleOffset, Acmd *p); /* alAdpcmPull */
Acmd *func_80074054_main(void *f, s16 *outp, s32 byteCount, s32 sampleOffset, Acmd *p); /* alRaw16Pull */
s32 func_800743F0_main(void *filter, s32 paramID, void *param);                         /* alLoadParam */

/* auxbus.c */
Acmd *alAuxBusPull(void *f, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p);
s32 alAuxBusParam(void *filter, s32 paramID, void *param);

/* env.c */
Acmd *func_80074B00_main(void *f, s16 *outp, s32 out, s32 sampleOffset, Acmd *p); /* alEnvmixerPull */
s32 func_80075000_main(void *filter, s32 paramID, void *param);                   /* alEnvmixerParam */

/* mainbus.c */
Acmd *func_80075B20_main(void *f, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p); /* alMainBusPull */
s32 func_80075C60_main(void *filter, s32 paramID, void *param);                        /* alMainBusParam */

/* resample.c */
Acmd *func_80075C90_main(void *f, s16 *outp, s32 out, s32 sampleOffset, Acmd *p); /* alResamplePull */
s32 func_80075E7C_main(void *f, s32 paramID, void *param);                        /* alResampleParam */

/* reverb.c */
Acmd *func_80075F40_main(void *f, s16 *outp, s32 out, s32 sampleOffset, Acmd *p); /* alFxPull */
s32 func_800762B4_main(void *filter, s32 paramID, void *param);                   /* alFxParam */
s32 func_800762C8_main(void *filter, s32 paramID, void *param);                   /* alFxParamHdl */

/* save.c */
Acmd *func_80076AE0_main(void *f, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p); /* alSavePull */
s32 func_80076B88_main(void *f, s32 paramID, void *param);                             /* alSaveParam */

/* synthesizer.c */
ALParam *func_8007825C_main(void);                      /* __allocParam */
void func_80078288_main(ALParam *param);                /* __freeParam */
void func_800782A0_main(ALSynth *drvr);                 /* _collectPVoices */
void func_800782F4_main(ALSynth *drvr, PVoice *pvoice); /* _freePVoice */
s32 func_80078334_main(ALSynth *synth, s32 micros);     /* _timeToSamplesNoRound */
s32 func_8007837C_main(ALSynth *synth, s32 micros);     /* _timeToSamples */

/* synallocfx.c */
ALFxRef *func_80078AA0_main(ALSynth *s, s16 bus, ALSynConfig *c, ALHeap *hp); /* alSynAllocFX */

#endif
