#include "common.h"
#include "PR/n_synthInternals.h"

void n_alSynFreeVoice(N_ALVoice *voice) {
    ALFreeParam *update;

    if (voice->pvoice != NULL) {
        if (voice->pvoice->offset != 0) { /* if voice was stolen */
            update = (ALFreeParam *)__n_allocParam();
            if (update == NULL) {
                return;
            }

            update->delta = n_syn->paramSamples + voice->pvoice->offset;
            update->type = AL_FILTER_FREE_VOICE;
            update->pvoice = voice->pvoice;

            n_alEnvmixerParam(voice->pvoice, AL_FILTER_ADD_UPDATE, update);
        } else {
            _n_freePVoice(voice->pvoice);
        }

        voice->pvoice = NULL;
    }
}
