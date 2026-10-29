#include "common.h"
#include "PR/synthInternals.h"

void alSynSetPitch(ALSynth *drvr, ALVoice *voice, f32 ratio) {
    ALParam *param;
    ALFilter *knob;

    if (voice->pvoice != NULL) {
        param = __allocParam();

        if (param != NULL) {
            param->delta = drvr->paramSamples + voice->pvoice->offset;
            param->type = AL_FILTER_SET_PITCH;
            param->data.f = ratio;
            param->next = NULL;

            knob = voice->pvoice->channelKnob;
            knob->setParam(knob, AL_FILTER_ADD_UPDATE, param);
        }
    }
}
