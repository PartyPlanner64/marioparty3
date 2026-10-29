#include "common.h"
#include "PR/n_libaudio.h"

u8 n_alCSPGetChlVol(N_ALCSPlayer *seqp, u8 chan) {
    return seqp->chanState[chan].vol;
}
