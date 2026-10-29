#include "common.h"
#include "PR/n_synthInternals.h"

Acmd *n_alAuxBusPull(s32 sampleOffset, Acmd *p) {
    Acmd *ptr = p;
    N_ALAuxBus *m = n_syn->auxBus;
    N_PVoice **sources = m->sources;
    s32 i;

    aClearBuffer(ptr++, N_AL_AUX_L_OUT, N_AL_DIVIDED << 1);

    for (i = 0; i < m->sourceCount; i++) {
        ptr = n_alEnvmixerPull(sources[i], sampleOffset, ptr);
    }
    return ptr;
}
