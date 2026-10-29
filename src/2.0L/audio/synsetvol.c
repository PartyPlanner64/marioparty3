#include "common.h"
#include "PR/synthInternals.h"

void alSynSetVol(ALSynth *drvr, ALVoice *voice, s16 vol, ALMicroTime delta) {
    ALParam *param;
    ALFilter *knob;

    if (voice->pvoice != NULL) {
        param = __allocParam();

        if (param != NULL) {
            param->delta = drvr->paramSamples + voice->pvoice->offset;
            param->type = AL_FILTER_SET_VOLUME;
            param->data.i = vol;
            param->moredata.i = _timeToSamples(drvr, delta);
            param->next = NULL;

            knob = voice->pvoice->channelKnob;
            knob->setParam(knob, AL_FILTER_ADD_UPDATE, param);
        }
    }
}
