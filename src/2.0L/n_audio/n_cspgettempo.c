#include "common.h"
#include "PR/n_libaudio.h"

s32 n_alCSPGetTempo(N_ALCSPlayer *seqp) {
    if (seqp->target == NULL) {
        return 0;
    }
    return seqp->uspt / seqp->target->qnpt;
}
