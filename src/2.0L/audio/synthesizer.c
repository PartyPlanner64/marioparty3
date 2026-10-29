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

s32 func_800783C8_main(ALSynth *drvr, ALPlayer **client); /* __nextSampleTime */

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

    save = func_80077290_main(NULL, 0, hp, 1, sizeof(ALSave));
    func_80073BC8_main(save);
    drvr->outputFilter = (ALFilter *)save;

    /*
     * allocate and initialize the auxilliary effects bus. at present
     * we only support 1 effects bus.
     */
    drvr->auxBus = func_80077290_main(NULL, 0, hp, 1, sizeof(ALAuxBus));
    drvr->maxAuxBusses = 1;
    sources = func_80077290_main(NULL, 0, hp, c->maxPVoices, sizeof(ALFilter *));
    func_80073B10_main(drvr->auxBus, sources, c->maxPVoices);

    /*
     * allocate and initialize the main bus.
     */
    drvr->mainBus = func_80077290_main(NULL, 0, hp, 1, sizeof(ALMainBus));
    sources = func_80077290_main(NULL, 0, hp, c->maxPVoices, sizeof(ALFilter *));
    func_80073B6C_main(drvr->mainBus, sources, c->maxPVoices);

    if (c->fxType != AL_FX_NONE) {
        /*
         * Allocate an effect and set parameters
         */
        func_80078AA0_main(drvr, 0, c, hp);
    } else {
        /*
         * Connect the aux bus to the main bus
         */
        func_80075C60_main(drvr->mainBus, AL_FILTER_ADD_SOURCE, &drvr->auxBus[0]);
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

    pvoices = func_80077290_main(NULL, 0, hp, c->maxPVoices, sizeof(PVoice));
    for (i = 0; i < c->maxPVoices; i++) {
        pv = &pvoices[i];
        alLink((ALLink *)pv, &drvr->pFreeList);
        pv->vvoice = 0;

        func_800739D4_main(&pv->decoder, drvr->dma, hp);
        func_800743F0_main(&pv->decoder, AL_FILTER_SET_SOURCE, 0);

        func_80073A84_main(&pv->resampler, hp);
        func_80075E7C_main(&pv->resampler, AL_FILTER_SET_SOURCE, &pv->decoder);

        func_8007391C_main(&pv->envmixer, hp);
        func_80075000_main(&pv->envmixer, AL_FILTER_SET_SOURCE, &pv->resampler);

        alAuxBusParam(drvr->auxBus, AL_FILTER_ADD_SOURCE, &pv->envmixer);

        pv->channelKnob = (ALFilter *)&pv->envmixer;
    }

    func_80076B88_main(save, AL_FILTER_SET_SOURCE, drvr->mainBus);

    /*
     * build the parameter update list
     */
    params = func_80077290_main(NULL, 0, hp, c->maxUpdates, sizeof(ALParam));
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
Acmd *func_800780AC_main(Acmd *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen) {
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
    for (drvr->paramSamples = func_800783C8_main(drvr, &client); drvr->paramSamples - drvr->curSamples < outLen;
         drvr->paramSamples = func_800783C8_main(drvr, &client)) {
        drvr->paramSamples &= ~0xF;
        client->samplesLeft += func_80078334_main(drvr, (*client->handler)(client));
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

    func_800782A0_main(drvr); /* collect free physical voices */

    return cmdlEnd;
}

ALParam *func_8007825C_main(void) {
    ALParam *param = NULL;

    if (alGlobals->drvr.paramList != NULL) {
        param = alGlobals->drvr.paramList;
        alGlobals->drvr.paramList = param->next;
        param->next = NULL;
    }

    return param;
}

void func_80078288_main(ALParam *param) {
    ALSynth *drvr = &alGlobals->drvr;

    param->next = drvr->paramList;
    drvr->paramList = param;
}

/* Returns every voice queued up on the lame list back to the free list. The
 * next pointer is re-read from the list head after every voice, because both
 * calls below move the node to a different list. */
void func_800782A0_main(ALSynth *drvr) {
    ALLink *link;

    for (link = drvr->pLameList.next; link != NULL; link = drvr->pLameList.next) {
        alUnlink(link);
        alLink(link, &drvr->pFreeList);
    }
}

void func_800782F4_main(ALSynth *drvr, PVoice *pvoice) {
    /*
     * move the voice from the allocated list to the lame list
     */
    alUnlink((ALLink *)pvoice);
    alLink((ALLink *)pvoice, &drvr->pLameList);
}

s32 func_80078334_main(ALSynth *drvr, s32 micros) {
    /* The 0.5 compensates for the average effect of the truncation error made
     * when the float result is cast to an int. */
    f32 samples = (f32)micros * drvr->outputRate / TIME_SCALE + TIME_ROUNDING;

    return samples;
}

static const f64 TIME_SCALE = 1000000.0;
static const f64 TIME_ROUNDING = 0.5;

/* Like the conversion above, but the frames are always played back in groups of
 * 16, so the frame count is rounded down to a multiple of 16. */
s32 func_8007837C_main(ALSynth *drvr, s32 micros) {
    f32 frames = (f32)micros * drvr->outputRate / FRAMES_TIME_SCALE + FRAMES_TIME_ROUNDING;

    return (s32)frames & ~0xF;
}

static const f64 FRAMES_TIME_SCALE = 1000000.0;
static const f64 FRAMES_TIME_ROUNDING = 0.5;

/* Finds the client whose frame is due soonest, relative to the current sample
 * position, and returns the sample count that client is now scheduled for. */
s32 func_800783C8_main(ALSynth *drvr, ALPlayer **client) {
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
