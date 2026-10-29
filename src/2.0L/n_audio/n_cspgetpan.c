#include "common.h"
#include "PR/n_libaudio.h"

ALPan n_alCSPGetChlPan(N_ALCSPlayer *seqp, u8 chan) {
    return seqp->chanState[chan].pan;
}
