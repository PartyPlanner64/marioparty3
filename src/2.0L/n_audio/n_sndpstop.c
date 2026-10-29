#include "common.h"
#include "PR/n_synthInternals.h"

void n_alSndpStop(void) {
    N_ALSndPlayer *sndp = (N_ALSndPlayer *)n_syn->n_sndp;
    N_ALSndpEvent evt;
    N_ALSoundState *sState = sndp->sndState;

    /*
     * Go immediately into the release phase
     */
    evt.common.type = AL_SNDP_STOP_EVT;
    evt.common.state = &sState[sndp->target];
    n_alEvtqPostEvent(&sndp->evtq, (N_ALEvent *)&evt, 0);
}
