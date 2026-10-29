#include "common.h"
#include "PR/n_synthInternals.h"

Acmd *n_alMainBusPull(s32 sampleOffset, Acmd *p) {
    Acmd *ptr = p;

    aClearBuffer(ptr++, N_AL_MAIN_L_OUT, N_AL_DIVIDED << 1);

    ptr = (n_syn->mainBus->filter.handler)(sampleOffset, ptr);

    aMix(ptr++, 0, 0x7fff, N_AL_AUX_L_OUT, N_AL_MAIN_L_OUT);
    aMix(ptr++, 0, 0x7fff, N_AL_AUX_R_OUT, N_AL_MAIN_R_OUT);

    return ptr;
}
