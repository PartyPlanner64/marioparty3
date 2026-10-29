#include "common.h"
#include "PR/n_synthInternals.h"

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_synthesizer", n_alSynNew);

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_synthesizer", n_alAudioFrame);

ALParam *__n_allocParam(void) {
    N_ALSynth *drvr = n_syn;
    ALParam *update = NULL;

    if (drvr->paramList != NULL) {
        update = drvr->paramList;
        drvr->paramList = update->next;
        update->next = NULL;
    }

    return update;
}

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_synthesizer", __n_freeParam);

void _n_collectPVoices(void) {
    ALLink *dl = n_syn->pLameList.next;

    while (dl != NULL) {
        alUnlink(dl);
        alLink(dl, &n_syn->pFreeList);
        dl = n_syn->pLameList.next;
    }
}

void _n_freePVoice(N_PVoice *pvoice) {
    alUnlink((ALLink *)pvoice);
    alLink((ALLink *)pvoice, &n_syn->pLameList);
}

s32 _n_timeToSamplesNoRound(s32 micros) {
    f32 tmp = ((f32)micros * n_syn->outputRate) / 1000000.0 + 0.5;
    return (s32)tmp;
}

s32 _n_timeToSamples(s32 micros) {
    f32 tmp = ((f32)micros * n_syn->outputRate) / 1000000.0 + 0.5;
    return (s32)tmp & ~0xF;
}

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_synthesizer", __n_nextSampleTime);
