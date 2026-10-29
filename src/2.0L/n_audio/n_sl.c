#include "common.h"
#include "PR/n_libaudio.h"

void n_alInit(N_ALGlobals *g, ALSynConfig *c) {
    if (n_alGlobals == NULL) {
        n_alGlobals = g;
        if (n_syn == NULL) {
            n_syn = &g->drvr;
            n_alSynNew(c);
        }
    }
}

void n_alClose(N_ALGlobals *glob) {
    if (n_alGlobals != NULL) {
        n_alSynDelete();
        n_alGlobals = NULL;
        n_syn = NULL;
    }
}
