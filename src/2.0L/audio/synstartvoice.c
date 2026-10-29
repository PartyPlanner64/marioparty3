#include "common.h"
#include "PR/synthInternals.h"

void alSynStartVoice(ALSynth *drvr, ALVoice *voice, ALWaveTable *wave) {
    ALFilter *knob;
    ALStartParam *param;

    if (voice->pvoice != NULL) {
        param = (ALStartParam *)__allocParam();

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
