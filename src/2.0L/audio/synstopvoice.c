#include "common.h"

/* Filter message ids used to queue a control param onto a voice. */
enum {
    AL_FILTER_ADD_UPDATE = 3,
    AL_FILTER_STOP_VOICE = 15
};

/* Filter header at the front of every filter of this synth version. */
typedef struct ALFilter_s {
    struct ALFilter_s *source;
    Acmd *(*handler)(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *cmdList);
    s32 (*setParam)(void *filter, s32 paramID, void *param);
} ALFilter;

/* The physical voice of this synth version. alSynNew allocates these in blocks
 * of 0xDC and carves the load, resample and envelope mixer filters out of each
 * one, so only the members the synth itself touches are named here. */
typedef struct PVoice_s {
    /* 0x00 */ ALLink node;
    /* 0x08 */ ALVoice *vvoice;
    /* 0x0C */ ALFilter *channelKnob;
    /* 0x10 */ char decoder[0x48];
    /* 0x58 */ char resampler[0x34];
    /* 0x8C */ char envmixer[0x4C];
    /* 0xD8 */ s32 offset;
} PVoice; // size 0xDC

ALParam *func_8007825C_main(void);

void func_80078700_main(ALSynth *drvr, ALVoice *voice) {
    ALParam *param;
    ALFilter *knob;

    if (voice->pvoice != NULL) {
        param = func_8007825C_main();

        if (param != NULL) {
            param->delta = drvr->paramSamples + voice->pvoice->offset;
            param->type = AL_FILTER_STOP_VOICE;
            param->next = NULL;

            knob = voice->pvoice->channelKnob;
            knob->setParam(knob, AL_FILTER_ADD_UPDATE, param);
        }
    }
}
