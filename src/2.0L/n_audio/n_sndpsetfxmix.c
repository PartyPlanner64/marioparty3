#include "common.h"
#include "PR/n_synthInternals.h"

void n_alSndpSetFXMix(u8 mix) {
    N_ALSndPlayer *sndp = (N_ALSndPlayer *)n_syn->n_sndp;
    N_ALSndpEvent evt;
    N_ALSoundState *sState = sndp->sndState;

    evt.fx.type = AL_SNDP_FX_EVT;
    evt.fx.state = &sState[sndp->target];
    evt.fx.mix = mix;
    n_alEvtqPostEvent(&sndp->evtq, (N_ALEvent *)&evt, 0);
}
