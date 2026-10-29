#include "common.h"
#include "PR/synthInternals.h"

void alSynSetPan(ALSynth *drvr, ALVoice *voice, ALPan pan) {
    ALParam *param;
    ALFilter *knob;

    if (voice->pvoice != NULL) {
        param = __allocParam();

        if (param != NULL) {
            param->delta = drvr->paramSamples + voice->pvoice->offset;
            param->type = AL_FILTER_SET_PAN;
            param->data.i = pan;
            param->next = NULL;

            knob = voice->pvoice->channelKnob;
            knob->setParam(knob, AL_FILTER_ADD_UPDATE, param);
        }
    }
}
