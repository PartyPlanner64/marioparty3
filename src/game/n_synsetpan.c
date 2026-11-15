#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/msm.h"
#include "PR/n_synthInternals.h"

// MP3's version of n_alSynSetPan, which can force centered panning.
void func_80066400_main(N_ALVoice *v, ALPan pan) {
    ALParam *update;

    if (v->pvoice) {
        update = __n_allocParam();
        if (update == NULL) {
            return;
        }

        update->delta = n_syn->paramSamples + v->pvoice->offset;
        update->type = AL_FILTER_SET_PAN;
        if (D_800CB8AC_main & 1) {
            update->data.i = 64;
        } else {
            update->data.i = pan;
        }
        update->next = 0;
        n_alEnvmixerParam(v->pvoice, AL_FILTER_ADD_UPDATE, update);
    }
}
