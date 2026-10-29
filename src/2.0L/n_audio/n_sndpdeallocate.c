#include "common.h"
#include "PR/n_synthInternals.h"

void n_alSndpDeallocate(ALSndId id) {
    N_ALSndPlayer *sndp = (N_ALSndPlayer *)n_syn->n_sndp;
    N_ALSoundState *sState = sndp->sndState;

    if (sState[id].state != AL_STOPPED) {
        return;
    }

    sState[id].sound = NULL;
    if (sndp->target == id) {
        sndp->target = -1;
    }
}
