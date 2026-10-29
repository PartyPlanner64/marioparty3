#include "common.h"
#include "PR/n_libaudio.h"

void n_alSndpDelete(void) {
    n_alSynRemovePlayer(n_syn->n_sndp);
}
