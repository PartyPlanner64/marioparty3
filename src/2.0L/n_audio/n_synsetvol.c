#include "common.h"
#include "PR/n_synthInternals.h"

void n_alSynSetVol(N_ALVoice *v, s16 volume, ALMicroTime t) {
    if (v->pvoice != NULL) {
        ALParam *update = __n_allocParam();

        if (update != NULL) {
            update->delta = n_syn->paramSamples + v->pvoice->offset;
            update->type = AL_FILTER_SET_VOLUME;
            update->data.i = volume;
            update->moredata.i = _n_timeToSamples(t);
            update->next = NULL;

            n_alEnvmixerParam(v->pvoice, AL_FILTER_ADD_UPDATE, update);
        }
    }
}
