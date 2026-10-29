#include "common.h"
#include "PR/synthInternals.h"

void alSynSetFXMix(ALSynth *drvr, ALVoice *voice, u8 fxmix) {
    ALParam *param;
    ALFilter *knob;

    if (voice->pvoice != NULL) {
        param = __allocParam();

        if (param != NULL) {
            param->delta = drvr->paramSamples + voice->pvoice->offset;
            param->type = AL_FILTER_SET_FXAMT;
            if (fxmix > 0x7F) {
                fxmix = 0x7F;
            }
            param->data.i = fxmix;
            param->next = NULL;

            knob = voice->pvoice->channelKnob;
            knob->setParam(knob, AL_FILTER_ADD_UPDATE, param);
        }
    }
}
