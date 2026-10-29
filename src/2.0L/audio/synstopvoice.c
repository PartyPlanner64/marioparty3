#include "common.h"
#include "PR/synthInternals.h"

void alSynStopVoice(ALSynth *drvr, ALVoice *voice) {
    ALParam *param;
    ALFilter *knob;

    if (voice->pvoice != NULL) {
        param = __allocParam();

        if (param != NULL) {
            param->delta = drvr->paramSamples + voice->pvoice->offset;
            param->type = AL_FILTER_STOP_VOICE;
            param->next = NULL;

            knob = voice->pvoice->channelKnob;
            knob->setParam(knob, AL_FILTER_ADD_UPDATE, param);
        }
    }
}
