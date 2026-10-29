#include "common.h"
#include "PR/n_libaudio.h"

void n_alSynAddPlayer(ALPlayer *client) {
    OSIntMask mask = osSetIntMask(OS_IM_NONE);
    N_ALSynth *drvr = n_syn;

    client->samplesLeft = drvr->curSamples;
    client->next = drvr->head;
    drvr->head = client;

    osSetIntMask(mask);
}

void n_alSynAddSndPlayer(ALPlayer *client) {
    OSIntMask mask = osSetIntMask(OS_IM_NONE);
    N_ALSynth *drvr = n_syn;

    client->samplesLeft = drvr->curSamples;
    client->next = drvr->head;
    drvr->head = client;

    if (drvr->n_sndp == NULL) {
        drvr->n_sndp = client;
    }

    osSetIntMask(mask);
}

void n_alSynAddSeqPlayer(ALPlayer *client) {
    OSIntMask mask = osSetIntMask(OS_IM_NONE);
    N_ALSynth *drvr = n_syn;

    client->samplesLeft = drvr->curSamples;
    client->next = drvr->head;
    drvr->head = client;

    if (drvr->n_seqp1 == NULL) {
        drvr->n_seqp1 = client;
    } else if (drvr->n_seqp2 == NULL) {
        drvr->n_seqp2 = client;
    }

    osSetIntMask(mask);
}
