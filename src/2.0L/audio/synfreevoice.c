#include "common.h"
#include "PR/synthInternals.h"

/* alSynFreeVoice */
void func_80078480_main(ALSynth *drvr, ALVoice *voice) {
    ALFilter *f;
    ALFreeParam *update;

    if (voice->pvoice) {
        if (voice->pvoice->offset) { /* if voice was stolen */
            update = (ALFreeParam *)func_8007825C_main();
            ALFailIf(update == 0, ERR_ALSYN_NO_UPDATE);

            /*
             * set voice data
             */
            update->delta = drvr->paramSamples + voice->pvoice->offset;
            update->type = AL_FILTER_FREE_VOICE;
            update->pvoice = voice->pvoice;

            f = voice->pvoice->channelKnob;
            (*f->setParam)(f, AL_FILTER_ADD_UPDATE, update);
        } else {
            func_800782F4_main(drvr, voice->pvoice);
        }

        voice->pvoice = 0;
    }
}
