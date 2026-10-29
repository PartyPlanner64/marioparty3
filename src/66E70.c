#include "common.h"
#include "PR/n_synthInternals.h"

extern u8 D_800CB8AC_main;

// MP3's version of n_alSynStartVoiceParams, which can force centered panning.
void func_80066270_main(N_ALVoice *v, ALWaveTable *w, f32 pitch, s16 vol, ALPan pan, u8 fxmix, ALMicroTime t) {
    ALStartParamAlt *update;

    if (v->pvoice) {
        update = (ALStartParamAlt *)__n_allocParam();
        if (update == NULL) {
            return;
        }

        if ((s8)fxmix < 0) {
            fxmix = -fxmix;
        }

        update->delta = n_syn->paramSamples + v->pvoice->offset;
        update->next = 0;
        update->type = AL_FILTER_START_VOICE_ALT;
        update->unity = v->unityPitch;
        if (D_800CB8AC_main & 1) {
            update->pan = 64;
        } else {
            update->pan = pan;
        }
        update->volume = vol;
        update->fxMix = fxmix;
        update->pitch = pitch;
        update->samples = _n_timeToSamples(t);
        update->wave = w;
        n_alEnvmixerParam(v->pvoice, AL_FILTER_ADD_UPDATE, update);
    }
}
