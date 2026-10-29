#include "common.h"
#include "PR/n_synthInternals.h"

void n_alSynSetFXMix(N_ALVoice *v, u8 fxmix) {
    if (v->pvoice != NULL) {
        ALParam *update = __n_allocParam();

        if (update != NULL) {
            update->delta = n_syn->paramSamples + v->pvoice->offset;
            update->type = AL_FILTER_SET_FXAMT;
            if (fxmix > 127) {
                fxmix = 127;
            }
            update->data.i = fxmix;
            update->next = NULL;

            n_alEnvmixerParam(v->pvoice, AL_FILTER_ADD_UPDATE, update);
        }
    }
}
