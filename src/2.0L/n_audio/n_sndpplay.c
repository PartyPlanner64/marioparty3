#include "common.h"
#include "PR/n_synthInternals.h"

void n_alSndpPlay(void) {
    N_ALSndPlayer *sndp = (N_ALSndPlayer *)n_syn->n_sndp;
    N_ALSndpEvent evt;
    N_ALSoundState *sState = sndp->sndState;

    if (sState[sndp->target].state == AL_STOPPED) {
        evt.common.type = AL_SNDP_PLAY_EVT;
        evt.common.state = &sState[sndp->target];
        n_alEvtqPostEvent(&sndp->evtq, (N_ALEvent *)&evt, 0);
    }
}
