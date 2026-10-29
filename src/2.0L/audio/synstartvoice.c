#include "common.h"
#include "PR/synthInternals.h"

/* alSynStartVoice */
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
