#include "common.h"
#include "PR/synthInternals.h"

/* alSynSetVol */
s32 func_8007837C_main(ALSynth *drvr, ALMicroTime micros);

void func_800788B0_main(ALSynth *drvr, ALVoice *voice, s16 vol, ALMicroTime delta) {
    ALParam *param;
    ALFilter *knob;

    if (voice->pvoice != NULL) {
        param = func_8007825C_main();

        if (param != NULL) {
            param->delta = drvr->paramSamples + voice->pvoice->offset;
            param->type = AL_FILTER_SET_VOLUME;
            param->data.i = vol;
            param->moredata.i = func_8007837C_main(drvr, delta);
            param->next = NULL;

            knob = voice->pvoice->channelKnob;
            knob->setParam(knob, AL_FILTER_ADD_UPDATE, param);
        }
    }
}
