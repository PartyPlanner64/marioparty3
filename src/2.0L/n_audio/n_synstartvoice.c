#include "common.h"
#include "PR/n_synthInternals.h"

void n_alSynStartVoice(N_ALVoice *v, ALWaveTable *table) {
    if (v->pvoice != NULL) {
        ALStartParam *update = (ALStartParam *)__n_allocParam();

        if (update != NULL) {
            update->delta = n_syn->paramSamples + v->pvoice->offset;
            update->type = AL_FILTER_START_VOICE;
            update->wave = table;
            update->next = NULL;
            update->unity = v->unityPitch;

            n_alEnvmixerParam(v->pvoice, AL_FILTER_ADD_UPDATE, update);
        }
    }
}
