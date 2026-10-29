#include "common.h"
#include "PR/synthInternals.h"

/*
 * The factors used by the micros conversions below. They are loaded straight
 * out of .rodata, so each one is declared here and defined after the function
 * that uses it: gcc turns a constant whose value it knows into a `li.d`
 * immediate, which would move it into a constant pool of its own.
 */
static const f64 TIME_SCALE;
static const f64 TIME_ROUNDING;

/* The micros-to-frames conversion below works on its own copies of the factors. */
static const f64 FRAMES_TIME_SCALE;
static const f64 FRAMES_TIME_ROUNDING;

static s32 __nextSampleTime(ALSynth *drvr, ALPlayer **client);
static s32 _timeToSamplesNoRound(ALSynth *synth, s32 micros);

void alSynNew(ALSynth *drvr, ALSynConfig *c) {
    s32 i;
    PVoice *pv;
    PVoice *pvoices;
    ALHeap *hp = c->heap;
    ALSave *save;
    ALFilter *sources;
    ALParam *params;
    ALParam *paramPtr;

    drvr->head = NULL;
    drvr->numPVoices = c->maxPVoices;
    drvr->curSamples = 0;
    drvr->paramSamples = 0;
    drvr->outputRate = c->outputRate;
    drvr->maxOutSamples = AL_MAX_RSP_SAMPLES;
    drvr->dma = (ALDMANew)c->dmaproc;

    save = alHeapDBAlloc(NULL, 0, hp, 1, sizeof(ALSave));
    alSaveNew(save);
    drvr->outputFilter = (ALFilter *)save;

    /*
     * allocate and initialize the auxilliary effects bus. at present
     * we only support 1 effects bus.
     */
    drvr->auxBus = alHeapDBAlloc(NULL, 0, hp, 1, sizeof(ALAuxBus));
    drvr->maxAuxBusses = 1;
    sources = alHeapDBAlloc(NULL, 0, hp, c->maxPVoices, sizeof(ALFilter *));
    alAuxBusNew(drvr->auxBus, sources, c->maxPVoices);

    /*
     * allocate and initialize the main bus.
     */
    drvr->mainBus = alHeapDBAlloc(NULL, 0, hp, 1, sizeof(ALMainBus));
    sources = alHeapDBAlloc(NULL, 0, hp, c->maxPVoices, sizeof(ALFilter *));
    alMainBusNew(drvr->mainBus, sources, c->maxPVoices);

    if (c->fxType != AL_FX_NONE) {
        /*
         * Allocate an effect and set parameters
         */
        alSynAllocFX(drvr, 0, c, hp);
    } else {
        /*
         * Connect the aux bus to the main bus
         */
        alMainBusParam(drvr->mainBus, AL_FILTER_ADD_SOURCE, &drvr->auxBus[0]);
    }

    /*
     * Build the physical voice lists
     */
    drvr->pFreeList.next = 0;
    drvr->pFreeList.prev = 0;
    drvr->pLameList.next = 0;
    drvr->pLameList.prev = 0;
    drvr->pAllocList.next = 0;
    drvr->pAllocList.prev = 0;

    pvoices = alHeapDBAlloc(NULL, 0, hp, c->maxPVoices, sizeof(PVoice));
    for (i = 0; i < c->maxPVoices; i++) {
        pv = &pvoices[i];
        alLink((ALLink *)pv, &drvr->pFreeList);
        pv->vvoice = 0;

        alLoadNew(&pv->decoder, drvr->dma, hp);
        alLoadParam(&pv->decoder, AL_FILTER_SET_SOURCE, 0);

        alResampleNew(&pv->resampler, hp);
        alResampleParam(&pv->resampler, AL_FILTER_SET_SOURCE, &pv->decoder);

        alEnvmixerNew(&pv->envmixer, hp);
        alEnvmixerParam(&pv->envmixer, AL_FILTER_SET_SOURCE, &pv->resampler);

        alAuxBusParam(drvr->auxBus, AL_FILTER_ADD_SOURCE, &pv->envmixer);

        pv->channelKnob = (ALFilter *)&pv->envmixer;
    }

    alSaveParam(save, AL_FILTER_SET_SOURCE, drvr->mainBus);

    /*
     * build the parameter update list
     */
    params = alHeapDBAlloc(NULL, 0, hp, c->maxUpdates, sizeof(ALParam));
    drvr->paramList = 0;
    for (i = 0; i < c->maxUpdates; i++) {
        paramPtr = &params[i];
        paramPtr->next = drvr->paramList;
        drvr->paramList = paramPtr;
    }

    drvr->heap = hp;
}

/*
 * alAudioFrame() is called every video frame, and is based on the video
 * frame interrupt. It is assumed to be an accurate time source for the
 * clients.
 */
Acmd *alAudioFrame(Acmd *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen) {
    ALPlayer *client;
    ALFilter *output;
    ALSynth *drvr = &alGlobals->drvr;
    s16 tmp = 0; /* Starting buffer in DMEM */
    Acmd *cmdlEnd = cmdList;
    Acmd *cmdPtr;
    s32 nOut;
    s16 *lOutBuf = outBuf;

    if (drvr->head == NULL) {
        *cmdLen = 0;
        return cmdList; /* nothing to do */
    }

    /*
     * paramSamples = time of next parameter change.
     * curSamples = current sample time.
     * if the next parameter change occurs within this frame time (outLen),
     * then call back the client that contains the parameter change.
     */
    for (drvr->paramSamples = __nextSampleTime(drvr, &client); drvr->paramSamples - drvr->curSamples < outLen;
         drvr->paramSamples = __nextSampleTime(drvr, &client)) {
        drvr->paramSamples &= ~0xF;
        client->samplesLeft += _timeToSamplesNoRound(drvr, (*client->handler)(client));
    }

    drvr->paramSamples &= ~0xF;

    /*
     * Now build the command list in small chunks
     */
    while (outLen > 0) {
        nOut = MIN(drvr->maxOutSamples, outLen);

        cmdPtr = cmdlEnd;
        aSegment(cmdPtr++, 0, 0);
        output = drvr->outputFilter;
        (*output->setParam)(output, AL_FILTER_SET_DRAM, lOutBuf);
        cmdlEnd = (*output->handler)(output, &tmp, nOut, drvr->curSamples, cmdPtr);

        outLen -= nOut;
        lOutBuf += nOut << 1; /* For Stereo */
        drvr->curSamples += nOut;
    }
    *cmdLen = (s32)(cmdlEnd - cmdList);

    _collectPVoices(drvr); /* collect free physical voices */

    return cmdlEnd;
}

ALParam *__allocParam(void) {
    ALParam *param = NULL;

    if (alGlobals->drvr.paramList != NULL) {
        param = alGlobals->drvr.paramList;
        alGlobals->drvr.paramList = param->next;
        param->next = NULL;
    }

    return param;
}

void __freeParam(ALParam *param) {
    ALSynth *drvr = &alGlobals->drvr;

    param->next = drvr->paramList;
    drvr->paramList = param;
}

/* Returns every voice queued up on the lame list back to the free list. The
 * next pointer is re-read from the list head after every voice, because both
 * calls below move the node to a different list. */
void _collectPVoices(ALSynth *drvr) {
    ALLink *link;

    for (link = drvr->pLameList.next; link != NULL; link = drvr->pLameList.next) {
        alUnlink(link);
        alLink(link, &drvr->pFreeList);
    }
}

void _freePVoice(ALSynth *drvr, PVoice *pvoice) {
    /*
     * move the voice from the allocated list to the lame list
     */
    alUnlink((ALLink *)pvoice);
    alLink((ALLink *)pvoice, &drvr->pLameList);
}

static s32 _timeToSamplesNoRound(ALSynth *drvr, s32 micros) {
    /* The 0.5 compensates for the average effect of the truncation error made
     * when the float result is cast to an int. */
    f32 samples = (f32)micros * drvr->outputRate / TIME_SCALE + TIME_ROUNDING;

    return samples;
}

static const f64 TIME_SCALE = 1000000.0;
static const f64 TIME_ROUNDING = 0.5;

/* Like the conversion above, but the frames are always played back in groups of
 * 16, so the frame count is rounded down to a multiple of 16. */
s32 _timeToSamples(ALSynth *drvr, s32 micros) {
    f32 frames = (f32)micros * drvr->outputRate / FRAMES_TIME_SCALE + FRAMES_TIME_ROUNDING;

    return (s32)frames & ~0xF;
}

static const f64 FRAMES_TIME_SCALE = 1000000.0;
static const f64 FRAMES_TIME_ROUNDING = 0.5;

/* Finds the client whose frame is due soonest, relative to the current sample
 * position, and returns the sample count that client is now scheduled for. */
static s32 __nextSampleTime(ALSynth *drvr, ALPlayer **client) {
    ALPlayer *cur;
    s32 delta = 0x7FFFFFFF;

    *client = NULL;
    for (cur = drvr->head; cur != NULL; cur = cur->next) {
        if (cur->samplesLeft - drvr->curSamples < delta) {
            *client = cur;
            delta = cur->samplesLeft - drvr->curSamples;
        }
    }

    return (*client)->samplesLeft;
}
