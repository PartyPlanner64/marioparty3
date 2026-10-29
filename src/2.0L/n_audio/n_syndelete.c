#include "common.h"
#include "PR/n_libaudio.h"

void n_alSynDelete(void) {
    n_syn->head = NULL;
    n_syn->n_seqp1 = NULL;
    n_syn->n_seqp2 = NULL;
    n_syn->n_sndp = NULL;
}
