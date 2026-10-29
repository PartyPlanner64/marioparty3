#include "common.h"
#include "PR/n_synthInternals.h"

void n_alSndpSetPan(ALPan pan) {
    N_ALSndPlayer *sndp = (N_ALSndPlayer *)n_syn->n_sndp;
    N_ALSndpEvent evt;
    N_ALSoundState *sState = sndp->sndState;

    evt.pan.type = AL_SNDP_PAN_EVT;
    evt.pan.pan = pan;
    evt.pan.state = &sState[sndp->target];
    n_alEvtqPostEvent(&sndp->evtq, (N_ALEvent *)&evt, 0);
}
