#include "common.h"
#include "PR/n_synthInternals.h"

void n_alSndpSetPitch(f32 pitch) {
    N_ALSndPlayer *sndp = (N_ALSndPlayer *)n_syn->n_sndp;
    N_ALSndpEvent evt;
    N_ALSoundState *sState = sndp->sndState;

    evt.pitch.type = AL_SNDP_PITCH_EVT;
    evt.pitch.state = &sState[sndp->target];
    evt.pitch.pitch = pitch;
    n_alEvtqPostEvent(&sndp->evtq, (N_ALEvent *)&evt, 0);
}
