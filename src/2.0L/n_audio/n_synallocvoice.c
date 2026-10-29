#include "common.h"
#include "PR/n_synthInternals.h"

s32 _n_allocatePVoice(N_PVoice **pvoice, s16 priority);

s32 n_alSynAllocVoice(N_ALVoice *voice, ALVoiceConfig *vc) {
    N_PVoice *pvoice = NULL;
    ALParam *update;
    s32 stolen;

    voice->priority = vc->priority;
    voice->unityPitch = vc->unityPitch;
    voice->table = NULL;
    voice->fxBus = vc->fxBus;
    voice->state = AL_STOPPED;
    voice->pvoice = NULL;

    stolen = _n_allocatePVoice(&pvoice, vc->priority);

    if (pvoice != NULL) { /* if we were able to allocate a voice */
        if (stolen) {
            pvoice->offset = 552;
            pvoice->vvoice->pvoice = NULL; /* zero stolen voice */
            pvoice->vvoice = voice;
            voice->pvoice = pvoice;

            /*
             * ramp down stolen voice
             */
            update = __n_allocParam();
            update->delta = n_syn->paramSamples;
            update->type = AL_FILTER_SET_VOLUME;
            update->data.i = 0;
            update->moredata.i = 368; /* ramp over two frames (offset - 184) */
            n_alEnvmixerParam(voice->pvoice, AL_FILTER_ADD_UPDATE, update);

            /*
             * stop stolen voice
             */
            update = __n_allocParam();
            if (update != NULL) {
                update->delta = n_syn->paramSamples + pvoice->offset;
                update->type = AL_FILTER_STOP_VOICE;
                update->next = NULL;
                n_alEnvmixerParam(voice->pvoice, AL_FILTER_ADD_UPDATE, update);
            }
        } else {
            pvoice->offset = 0;
            pvoice->vvoice = voice; /* assign new voice */
            voice->pvoice = pvoice;
        }
    }

    return pvoice != NULL;
}

s32 _n_allocatePVoice(N_PVoice **pvoice, s16 priority) {
    ALLink *dl;
    N_PVoice *pv;
    s32 stolen = 0;

    if ((dl = n_syn->pLameList.next) != NULL) { /* check the lame list first */
        *pvoice = (N_PVoice *)dl;
        alUnlink(dl);
        alLink(dl, &n_syn->pAllocList);
    } else if ((dl = n_syn->pFreeList.next) != NULL) { /* from the free list */
        *pvoice = (N_PVoice *)dl;
        alUnlink(dl);
        alLink(dl, &n_syn->pAllocList);
    } else { /* steal one */
        for (dl = n_syn->pAllocList.next; dl != NULL; dl = dl->next) {
            pv = (N_PVoice *)dl;

            /*
             * if it is lower priority and not already stolen, keep it
             * as a candidate for stealing
             */
            if ((pv->vvoice->priority <= priority) && (pv->offset == 0)) {
                *pvoice = pv;
                priority = pv->vvoice->priority;
                stolen = 1;
            }
        }
    }

    return stolen;
}
