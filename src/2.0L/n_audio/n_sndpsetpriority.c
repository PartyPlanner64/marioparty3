#include "common.h"
#include "PR/n_synthInternals.h"

void n_alSndpSetPriority(ALSndId id, u8 priority) {
    N_ALSndPlayer *sndp = (N_ALSndPlayer *)n_syn->n_sndp;
    N_ALSoundState *sState = sndp->sndState;

    sState[id].priority = priority;
}
