#include "common.h"
#include "PR/n_synthInternals.h"

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

/*
 * Default effect parameters (SMALLROOM, BIGROOM, ECHO, CHORUS, FLANGE, NULL).
 * They live in a data segment that has not been split out yet.
 */
extern s32 D_800A2890_main[];
extern s32 D_800A28F8_main[];
extern s32 D_800A2980_main[];
extern s32 D_800A29A8_main[];
extern s32 D_800A29D0_main[];
extern s32 D_800A29F8_main[];

void n_alFxNew(N_ALFx **fx_ar, ALSynConfig *c, ALHeap *hp) {
    u16 i, j, k;
    s32 *param = 0;
    N_ALDelay *d;
    N_ALFx *r;

    *fx_ar = r = alHeapDBAlloc(NULL, 0, hp, 1, sizeof(N_ALFx));

    switch (c->fxType) {
        case AL_FX_SMALLROOM:
            param = D_800A2890_main;
            break;
        case AL_FX_BIGROOM:
            param = D_800A28F8_main;
            break;
        case AL_FX_ECHO:
            param = D_800A2980_main;
            break;
        case AL_FX_CHORUS:
            param = D_800A29A8_main;
            break;
        case AL_FX_FLANGE:
            param = D_800A29D0_main;
            break;
        case AL_FX_CUSTOM:
            param = c->params;
            break;
        default:
            param = D_800A29F8_main;
            break;
    }

    j = 0;

    r->section_count = param[j++];
    r->length = param[j++];

    r->delay = alHeapDBAlloc(NULL, 0, hp, r->section_count, sizeof(N_ALDelay));
    r->base = alHeapDBAlloc(NULL, 0, hp, r->length, sizeof(s16));
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
            d->rs = alHeapDBAlloc(NULL, 0, hp, 1, sizeof(N_ALResampler));
            d->rs->state = alHeapDBAlloc(NULL, 0, hp, 1, sizeof(RESAMPLE_STATE));
            d->rs->delta = 0.0;
            d->rs->first = 1;
        } else {
            d->rs = 0;
            j++;
            j++;
        }

        if (param[j]) {
            d->lp = alHeapDBAlloc(NULL, 0, hp, 1, sizeof(N_ALLowPass));
            d->lp->fstate = alHeapDBAlloc(NULL, 0, hp, 1, sizeof(POLEF_STATE));
            d->lp->fc = param[j++];
            init_lpfilter(d->lp);
        } else {
            d->lp = 0;
            j++;
        }
    }
}

void alN_PVoiceNew(N_PVoice *mv, ALDMANew dmaNew, ALHeap *hp) {
    mv->dc_state = alHeapDBAlloc(NULL, 0, hp, 1, sizeof(ADPCM_STATE));
    mv->dc_lstate = alHeapDBAlloc(NULL, 0, hp, 1, sizeof(ADPCM_STATE));
    mv->dc_dma = dmaNew(&mv->dc_dmaState);
    mv->dc_lastsam = 0;
    mv->dc_first = 1;
    mv->dc_memin = 0;

    mv->rs_state = alHeapDBAlloc(NULL, 0, hp, 1, sizeof(RESAMPLE_STATE));
    mv->rs_delta = 0.0;
    mv->rs_first = 1;
    mv->rs_ratio = 1.0;
    mv->rs_upitch = 0;

    mv->em_state = alHeapDBAlloc(NULL, 0, hp, 1, sizeof(ENVMIX_STATE));
    mv->em_first = 1;
    mv->em_motion = AL_STOPPED;
    mv->em_volume = 1;
    mv->em_ltgt = 1;
    mv->em_rtgt = 1;
    mv->em_cvolL = 1;
    mv->em_cvolR = 1;
    mv->em_dryamt = 0;
    mv->em_wetamt = 0;
    mv->em_lratm = 1;
    mv->em_lratl = 0;
    mv->em_lratm = 1;
    mv->em_lratl = 0;
    mv->em_delta = 0;
    mv->em_segEnd = 0;
    mv->em_pan = 0;
    mv->em_ctrlList = 0;
    mv->em_ctrlTail = 0;
}
