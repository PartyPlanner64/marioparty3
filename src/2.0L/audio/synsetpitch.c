#include "common.h"
#include "PR/synthInternals.h"

/* alSynSetPitch */
void func_80078820_main(ALSynth *drvr, ALVoice *voice, f32 ratio) {
    ALParam *param;
    ALFilter *knob;

    if (voice->pvoice != NULL) {
        param = func_8007825C_main();

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
