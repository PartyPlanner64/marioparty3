#include "common.h"
#include "PR/n_synthInternals.h"

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

s32 __n_nextSampleTime(ALPlayer **client);

void n_alSynNew(ALSynConfig *c) {
    s32 i;
    N_PVoice *pv;
    N_PVoice *pvoices;
    ALHeap *hp = c->heap;
    ALParam *params;
    ALParam *paramPtr;

    n_syn->head = NULL;
    n_syn->n_seqp1 = NULL;
    n_syn->n_seqp2 = NULL;
    n_syn->n_sndp = NULL;
    n_syn->numPVoices = c->maxPVoices;
    n_syn->curSamples = 0;
    n_syn->paramSamples = 0;
    n_syn->outputRate = c->outputRate;
    n_syn->maxOutSamples = N_AL_MAX_RSP_SAMPLES;
    n_syn->dma = (ALDMANew)c->dmaproc;

    n_syn->sv_dramout = 0;
    n_syn->sv_first = 1;

    /*
     * allocate and initialize the auxilliary effects bus. at present
     * we only support 1 effects bus.
     */
    n_syn->auxBus = alHeapAlloc(hp, 1, sizeof(N_ALAuxBus));
    n_syn->auxBus->sourceCount = 0;
    n_syn->auxBus->maxSources = c->maxPVoices;
    n_syn->auxBus->sources = alHeapAlloc(hp, c->maxPVoices, sizeof(N_PVoice *));

    /*
     * allocate and initialize the main bus.
     */
    n_syn->mainBus = alHeapAlloc(hp, 1, sizeof(N_ALMainBus));

    if (c->fxType != AL_FX_NONE) {
        /*
         * Allocate an effect and set parameters
         */
        n_syn->auxBus->fx = n_alSynAllocFX(0, c, hp);
        n_syn->mainBus->filter.handler = n_alFxPull;
    } else {
        /*
         * Connect the aux bus to the main bus
         */
        n_syn->mainBus->filter.handler = n_alAuxBusPull;
    }

    /*
     * Build the physical voice lists
     */
    n_syn->pFreeList.next = NULL;
    n_syn->pFreeList.prev = NULL;
    n_syn->pLameList.next = NULL;
    n_syn->pLameList.prev = NULL;
    n_syn->pAllocList.next = NULL;
    n_syn->pAllocList.prev = NULL;

    pvoices = alHeapAlloc(hp, c->maxPVoices, sizeof(N_PVoice));
    for (i = 0; i < c->maxPVoices; i++) {
        pv = &pvoices[i];
        alLink((ALLink *)pv, &n_syn->pFreeList);
        pv->vvoice = NULL;
        alN_PVoiceNew(pv, n_syn->dma, hp);
        n_syn->auxBus->sources[n_syn->auxBus->sourceCount++] = pv;
    }

    /*
     * build the parameter update list
     */
    params = alHeapAlloc(hp, c->maxUpdates, sizeof(ALParam));
    n_syn->paramList = NULL;
    for (i = 0; i < c->maxUpdates; i++) {
        paramPtr = &params[i];
        paramPtr->next = n_syn->paramList;
        n_syn->paramList = paramPtr;
    }

    n_syn->heap = hp;
}

/*
 * n_alAudioFrame() is called every video frame, and is based on the video
 * frame interrupt. It is assumed to be an accurate time source for the
 * clients.
 */
Acmd *n_alAudioFrame(Acmd *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen) {
    ALPlayer *client;
    Acmd *cmdlEnd = cmdList;
    s32 nOut;
    s16 *lOutBuf = outBuf;

    if (n_syn->head == NULL) {
        *cmdLen = 0;
        return cmdList; /* nothing to do */
    }

    /*
     * paramSamples = time of next parameter change.
     * curSamples = current sample time.
     * so paramSamples - curSamples is the time until the next parameter change.
     * if the next parameter change occurs within this frame time (outLen),
     * then call back the client that contains the parameter change.
     * Note, paramSamples must be rounded down to 16 sample boundary for use
     * during the client handler.
     */
    for (n_syn->paramSamples = __n_nextSampleTime(&client); n_syn->paramSamples - n_syn->curSamples < outLen;
         n_syn->paramSamples = __n_nextSampleTime(&client)) {
        n_syn->paramSamples &= ~0xF;
        client->samplesLeft += _n_timeToSamplesNoRound((*client->handler)(client));
    }

    /* for safety's sake, always store paramSamples aligned to 16 sample boundary.
     * this way, if an voice handler routine gets called outside the ALVoiceHandler
     * routine (alSynAllocVoice) it will get timestamped with an aligned value and
     * will be processed immediately next audio frame.
     */
    n_syn->paramSamples &= ~0xF;

    /*
     * Now build the command list in small chunks
     */
    while (outLen > 0) {
        nOut = MIN(n_syn->maxOutSamples, outLen);

        /*
         * construct the command list for each physical voice by calling
         * the head of the filter chain.
         */
        n_syn->sv_dramout = (s32)lOutBuf;
        cmdlEnd = n_alSavePull(n_syn->curSamples, cmdlEnd);
        outLen -= nOut;
        lOutBuf += nOut << 1; /* For Stereo */
        n_syn->curSamples += nOut;
    }
    *cmdLen = (s32)(cmdlEnd - cmdList);

    _n_collectPVoices(); /* collect free physical voices */

    return cmdlEnd;
}

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

void __n_freeParam(ALParam *param) {
    param->next = n_syn->paramList;
    n_syn->paramList = param;
}

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

s32 __n_nextSampleTime(ALPlayer **client) {
    ALMicroTime idelta;
    ALMicroTime delta = 0x7FFFFFFF; /* max delta for s32 */
    ALPlayer *cl;

    *client = NULL;

    cl = n_syn->n_sndp;
    if (cl != NULL) {
        idelta = cl->samplesLeft - n_syn->curSamples;
        if (idelta < delta) {
            *client = cl;
            delta = idelta;
        }
    }

    cl = n_syn->n_seqp1;
    if (cl != NULL) {
        idelta = cl->samplesLeft - n_syn->curSamples;
        if (idelta < delta) {
            *client = cl;
            delta = idelta;
        }
    }

    cl = n_syn->n_seqp2;
    if (cl != NULL) {
        if (cl->samplesLeft - n_syn->curSamples < delta) {
            *client = cl;
            delta = idelta;
        }
    }

    return (*client)->samplesLeft;
}
