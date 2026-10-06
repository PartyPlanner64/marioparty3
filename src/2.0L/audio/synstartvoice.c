#include "common.h"

/* Filter message ids used to queue a control param onto a voice. */
enum {
    AL_FILTER_ADD_UPDATE = 3,
    AL_FILTER_START_VOICE = 14
};

/* Filter header at the front of every filter of this synth version. */
typedef struct ALFilter_s {
    struct ALFilter_s *source;
    Acmd *(*handler)(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *cmdList);
    s32 (*setParam)(void *filter, s32 paramID, void *param);
} ALFilter;

/* The physical voice of this synth version. Only the channel knob and the
 * sample offset are needed to queue a param onto a voice. */
typedef struct PVoice_s {
    /* 0x00 */ char pad00[0x0C];
    /* 0x0C */ ALFilter *channelKnob;
    /* 0x10 */ char pad10[0xC8];
    /* 0xD8 */ s32 offset;
} PVoice;

/* The control param that starts a voice playing from a wave table. */
typedef struct ALStartParam {
    struct ALParam_s *next;
    s32 delta;
    s16 type;
    s16 unity;
    ALWaveTable *wave;
} ALStartParam;

ALParam *func_8007825C_main(void);

void func_80078780_main(ALSynth *drvr, ALVoice *voice, ALWaveTable *wave) {
    ALFilter *knob;
    ALStartParam *param;

    if (voice->pvoice != NULL) {
        param = (ALStartParam *)func_8007825C_main();

        if (param != NULL) {
            param->delta = drvr->paramSamples + voice->pvoice->offset;
            param->type = AL_FILTER_START_VOICE;
            param->wave = wave;
            param->next = NULL;
            param->unity = voice->unityPitch;

            knob = voice->pvoice->channelKnob;
            knob->setParam(knob, AL_FILTER_ADD_UPDATE, param);
        }
    }
}
