#include "common.h"
#include "PR/n_synthInternals.h"

void n_alSndpSetSound(ALSndId id) {
    N_ALSndPlayer *sndp = (N_ALSndPlayer *)n_syn->n_sndp;

    sndp->target = id;
}
