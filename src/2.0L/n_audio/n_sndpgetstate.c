#include "common.h"
#include "PR/n_synthInternals.h"

s32 n_alSndpGetState(void) {
    N_ALSndPlayer *sndp = (N_ALSndPlayer *)n_syn->n_sndp;
    s32 id = sndp->target;
    N_ALSoundState *sState = sndp->sndState;

    return sState[id].state;
}
