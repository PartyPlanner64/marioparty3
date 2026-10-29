#include "common.h"
#include "PR/synthInternals.h"

/*
 * WARNING: THE FOLLOWING CONSTANT MUST BE KEPT IN SYNC
 * WITH SCALING IN MICROCODE!!!
 */
#define SCALE 16384

#define RANGE 2.0

/*
 * the following constant is derived from:
 *
 *      ratio = 2^(cents/1200)
 *
 * and therefore for hundredths of a cent
 *                        x
 *      ln(ratio) = ---------------
 *                  (120,000)/ln(2)
 * where
 *      120,000/ln(2) = 173123.40...
 */
#define CONVERT 173123.404906676
#define LENGTH (d->output - d->input)

/* Default parameters for the built in effects. They live in the shared .data
 * block rather than in a .data section of this file. */
extern s32 D_800A2A90_main[]; /* SMALLROOM_PARAMS */
extern s32 D_800A2AF8_main[]; /* BIGROOM_PARAMS */
extern s32 D_800A2B80_main[]; /* ECHO_PARAMS */
extern s32 D_800A2BA8_main[]; /* CHORUS_PARAMS */
extern s32 D_800A2BD0_main[]; /* FLANGE_PARAMS */
extern s32 D_800A2BF8_main[]; /* NULL_PARAMS */

/* init_lpfilter */
void func_800733E0_main(ALLowPass *lp) {
    s32 i, temp;
    s16 fc;
    f64 ffc, fcoef;

    temp = lp->fc * SCALE;
    fc = temp >> 15;
    lp->fgain = SCALE - fc;

    lp->first = 1;
    for (i = 0; i < 8; i++) {
        lp->fcvec.fccoef[i] = 0;
    }

    lp->fcvec.fccoef[i++] = fc;
    fcoef = ffc = (f64)fc / SCALE;

    for (; i < 16; i++) {
        fcoef *= ffc;
        lp->fcvec.fccoef[i] = (s16)(fcoef * SCALE);
    }
}

/* alFxNew */
void func_80073484_main(ALFx *r, ALSynConfig *c, ALHeap *hp) {
    u16 i, j, k;
    s32 *param = 0;
    ALFilter *f = (ALFilter *)r;
    ALDelay *d;

    func_80075B00_main(f, 0, func_800762B4_main, AL_FX);
    f->handler = func_80075F40_main;
    r->paramHdl = func_800762C8_main;

    switch (c->fxType) {
        case AL_FX_SMALLROOM:
            param = D_800A2A90_main;
            break;
        case AL_FX_BIGROOM:
            param = D_800A2AF8_main;
            break;
        case AL_FX_ECHO:
            param = D_800A2B80_main;
            break;
        case AL_FX_CHORUS:
            param = D_800A2BA8_main;
            break;
        case AL_FX_FLANGE:
            param = D_800A2BD0_main;
            break;
        case AL_FX_CUSTOM:
            param = c->params;
            break;
        default:
            param = D_800A2BF8_main;
            break;
    }

    j = 0;

    r->section_count = param[j++];
    r->length = param[j++];

    r->delay = func_80077290_main(NULL, 0, hp, r->section_count, sizeof(ALDelay));
    r->base = func_80077290_main(NULL, 0, hp, r->length, sizeof(s16));
    r->input = r->base;

    for (k = 0; k < r->length; k++) {
        r->base[k] = 0;
    }

    for (i = 0; i < r->section_count; i++) {
        d = &r->delay[i];
        d->input = param[j++];
        d->output = param[j++];
        d->fbcoef = param[j++];
        d->ffcoef = param[j++];
        d->gain = param[j++];

        if (param[j]) {
            d->rsinc = ((((f32)param[j++]) / 1000) * RANGE) / c->outputRate;
            d->rsgain = (((f32)param[j++]) / CONVERT) * LENGTH;
            d->rsval = 1.0;
            d->rsdelta = 0.0;
            d->rs = func_80077290_main(NULL, 0, hp, 1, sizeof(ALResampler));
            d->rs->state = func_80077290_main(NULL, 0, hp, 1, sizeof(RESAMPLE_STATE));
            d->rs->delta = 0.0;
            d->rs->first = 1;
        } else {
            d->rs = 0;
            j++;
            j++;
        }

        if (param[j]) {
            d->lp = func_80077290_main(NULL, 0, hp, 1, sizeof(ALLowPass));
            d->lp->fstate = func_80077290_main(NULL, 0, hp, 1, sizeof(POLEF_STATE));
            d->lp->fc = param[j++];
            func_800733E0_main(d->lp);
        } else {
            d->lp = 0;
            j++;
        }
    }
}

/* alEnvmixerNew */
void func_8007391C_main(ALEnvMixer *e, ALHeap *hp) {
    func_80075B00_main((ALFilter *)e, func_80074B00_main, func_80075000_main, AL_ENVMIX);

    e->state = func_80077290_main(NULL, 0, hp, 1, sizeof(ENVMIX_STATE));

    e->first = 1;
    e->motion = AL_STOPPED;
    e->volume = 1;
    e->ltgt = 1;
    e->rtgt = 1;
    e->cvolL = 1;
    e->cvolR = 1;
    e->dryamt = 0;
    e->wetamt = 0;
    e->lratm = 1;
    e->lratl = 0;
    e->lratm = 1;
    e->lratl = 0;
    e->delta = 0;
    e->segEnd = 0;
    e->pan = 0;
    e->ctrlList = 0;
    e->ctrlTail = 0;
    e->sources = 0;
}

/* alLoadNew */
void func_800739D4_main(ALLoadFilter *f, ALDMANew dmaNew, ALHeap *hp) {
    func_80075B00_main((ALFilter *)f, func_80073C10_main, func_800743F0_main, AL_ADPCM);

    f->state = func_80077290_main(NULL, 0, hp, 1, sizeof(ADPCM_STATE));
    f->lstate = func_80077290_main(NULL, 0, hp, 1, sizeof(ADPCM_STATE));

    f->dma = dmaNew(&f->dmaState);

    f->lastsam = 0;
    f->first = 1;
    f->memin = 0;
}

/* alResampleNew */
void func_80073A84_main(ALResampler *r, ALHeap *hp) {
    func_80075B00_main((ALFilter *)r, func_80075C90_main, func_80075E7C_main, AL_RESAMPLE);

    r->state = func_80077290_main(NULL, 0, hp, 1, sizeof(RESAMPLE_STATE));
    r->delta = 0.0;
    r->first = 1;
    r->motion = AL_STOPPED;
    r->ratio = 1.0;
    r->upitch = 0;
    r->ctrlList = 0;
    r->ctrlTail = 0;
}

/* alAuxBusNew */
void func_80073B10_main(ALAuxBus *m, void *sources, s32 maxSources) {
    func_80075B00_main((ALFilter *)m, alAuxBusPull, alAuxBusParam, AL_AUXBUS);
    m->sourceCount = 0;
    m->maxSources = maxSources;
    m->sources = (ALFilter **)sources;
}

/* alMainBusNew */
void func_80073B6C_main(ALMainBus *m, void *sources, s32 maxSources) {
    func_80075B00_main((ALFilter *)m, func_80075B20_main, func_80075C60_main, AL_MAINBUS);
    m->sourceCount = 0;
    m->maxSources = maxSources;
    m->sources = (ALFilter **)sources;
}

/* alSaveNew */
void func_80073BC8_main(ALSave *f) {
    func_80075B00_main((ALFilter *)f, func_80076AE0_main, func_80076B88_main, AL_SAVE);

    f->dramout = 0;
    f->first = 1;
}
