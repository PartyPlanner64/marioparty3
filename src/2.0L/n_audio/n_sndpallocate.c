#include "common.h"
#include "PR/n_synthInternals.h"

ALSndId n_alSndpAllocate(ALSound *sound) {
    N_ALSndPlayer *sndp = (N_ALSndPlayer *)n_syn->n_sndp;
    N_ALSoundState *sState = sndp->sndState;
    ALSndId i;

    for (i = 0; i < sndp->maxSounds; i++) {
        if (sState[i].sound == NULL) {
            sState[i].sound = sound;
            sState[i].priority = AL_DEFAULT_PRIORITY;
            sState[i].state = AL_STOPPED;
            sState[i].pitch = 1.0f;
            sState[i].pan = AL_PAN_CENTER;
            sState[i].fxMix = AL_DEFAULT_FXMIX;
            sState[i].vol = 32767 * sound->sampleVolume / AL_VOL_FULL;
            return i;
        }
    }

    return -1;
}
