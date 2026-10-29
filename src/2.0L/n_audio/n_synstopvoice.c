#include "common.h"
#include "PR/n_synthInternals.h"

void n_alSynStopVoice(N_ALVoice *v) {
    if (v->pvoice != NULL) {
        ALParam *update = __n_allocParam();

        if (update != NULL) {
            update->delta = n_syn->paramSamples + v->pvoice->offset;
            update->type = AL_FILTER_STOP_VOICE;
            update->next = NULL;
            n_alEnvmixerParam(v->pvoice, AL_FILTER_ADD_UPDATE, update);
        }
    }
}
