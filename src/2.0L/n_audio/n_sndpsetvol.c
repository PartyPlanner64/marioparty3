#include "common.h"
#include "PR/n_synthInternals.h"

void n_alSndpSetVol(s16 vol) {
    N_ALSndPlayer *sndp = (N_ALSndPlayer *)n_syn->n_sndp;
    N_ALSndpEvent evt;
    N_ALSoundState *sState = sndp->sndState;

    evt.vol.type = AL_SNDP_VOL_EVT;
    evt.vol.state = &sState[sndp->target];
    evt.vol.vol = vol;
    n_alEvtqPostEvent(&sndp->evtq, (N_ALEvent *)&evt, 0);
}
