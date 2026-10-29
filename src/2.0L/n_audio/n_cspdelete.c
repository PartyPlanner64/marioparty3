#include "common.h"
#include "PR/n_libaudio.h"

void n_alCSPDelete(N_ALCSPlayer *seqp) {
    n_alSynRemovePlayer(&seqp->node);
}
