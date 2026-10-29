#include "common.h"
#include "PR/synthInternals.h"

/* alSynStopVoice */
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
