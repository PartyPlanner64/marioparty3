#include "common.h"
#include "PR/synthInternals.h"

#define RANGE 2.0

/*
 * macros
 */
#define SWAP(in, out) \
    {                 \
        s16 t = out;  \
        out = in;     \
        in = t;       \
    }

Acmd *func_800764B8_main(ALFx *r, ALDelay *d, s32 buff, s32 incount, Acmd *p);  /* _loadOutputBuffer */
Acmd *func_800766D0_main(ALFx *r, s16 *curr_ptr, s32 buff, s32 count, Acmd *p); /* _loadBuffer */
Acmd *func_80076840_main(ALFx *r, s16 *curr_ptr, s32 buff, s32 count, Acmd *p); /* _saveBuffer */
Acmd *func_800769B0_main(ALLowPass *lp, s32 buff, s32 count, Acmd *p);          /* _filterBuffer */
f32 func_80076A4C_main(ALDelay *d, s32 count);                                  /* _doModFunc */

/***********************************************************************
 * Reverb filter public interfaces
 ***********************************************************************/
/* alFxPull */
Acmd *func_80075F40_main(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p) {
    Acmd *ptr = p;
    ALFx *r = (ALFx *)filter;
    ALFilter *source = r->filter.source;
    s16 i, buff1, buff2, input, output;
    s16 *in_ptr, *out_ptr, *prev_out_ptr = 0;
    ALDelay *d;

    /*
     * pull channels going into this effect first
     */
    ptr = (*source->handler)(source, outp, outCount, sampleOffset, p);

    input = AL_AUX_L_OUT;
    output = AL_AUX_R_OUT;
    buff1 = AL_TEMP_0;
    buff2 = AL_TEMP_1;

    aSetBuffer(ptr++, 0, 0, 0, outCount << 1);   /* set the buffer size */
    aMix(ptr++, 0, 0xda83, AL_AUX_L_OUT, input); /* .707L = L - .293L */
    aMix(ptr++, 0, 0x5a82, AL_AUX_R_OUT, input); /* mix the AuxL and AuxR into the AuxL */
    /* and write the mixed value to the delay line at r->input */
    ptr = func_80076840_main(r, r->input, input, outCount, ptr);

    aClearBuffer(ptr++, output, outCount << 1); /* clear the AL_AUX_R_OUT */

    for (i = 0; i < r->section_count; i++) {
        d = &r->delay[i]; /* get the ALDelay structure */
        in_ptr = &r->input[-d->input];
        out_ptr = &r->input[-d->output];

        if (in_ptr == prev_out_ptr) {
            SWAP(buff1, buff2);
        } else { /* load data at in_ptr into buff1 */
            ptr = func_800766D0_main(r, in_ptr, buff1, outCount, ptr);
        }
        ptr = func_800764B8_main(r, d, buff2, outCount, ptr);

        if (d->ffcoef) {
            aMix(ptr++, 0, (u16)d->ffcoef, buff1, buff2);
            if (!d->rs && !d->lp) {
                ptr = func_80076840_main(r, out_ptr, buff2, outCount, ptr);
            }
        }

        if (d->fbcoef) {
            aMix(ptr++, 0, (u16)d->fbcoef, buff2, buff1);
            ptr = func_80076840_main(r, in_ptr, buff1, outCount, ptr);
        }

        if (d->lp) {
            ptr = func_800769B0_main(d->lp, buff2, outCount, ptr);
        }

        if (!d->rs) {
            ptr = func_80076840_main(r, out_ptr, buff2, outCount, ptr);
        }

        if (d->gain) {
            aMix(ptr++, 0, (u16)d->gain, buff2, output);
        }

        prev_out_ptr = &r->input[d->output];
    }

    /*
     * bump the master delay line input pointer
     * modulo the length
     */
    r->input += outCount;
    if (r->input > &r->base[r->length]) {
        r->input -= r->length;
    }

    /*
     * output already in AL_AUX_R_OUT
     *      just copy to AL_AUX_L_OUT
     */
    aDMEMMove(ptr++, output, AL_AUX_L_OUT, outCount << 1);

    return ptr;
}

/* alFxParam */
s32 func_800762B4_main(void *filter, s32 paramID, void *param) {
    if (paramID == AL_FILTER_SET_SOURCE) {
        ALFilter *f = (ALFilter *)filter;
        f->source = (ALFilter *)param;
    }
    return 0;
}

/*
 * This routine gets called by alSynSetFXParam. No checking takes place to
 * verify the validity of the paramID or the param value. input and output
 * values must be 8 byte aligned, so round down any param passed.
 */
/* alFxParamHdl */
s32 func_800762C8_main(void *filter, s32 paramID, void *param) {
    ALFx *f = (ALFx *)filter;
    s32 p = (paramID - 2) % 8;
    s32 s = (paramID - 2) / 8;
    s32 val = *(s32 *)param;

#define INPUT_PARAM 0
#define OUTPUT_PARAM 1
#define FBCOEF_PARAM 2
#define FFCOEF_PARAM 3
#define GAIN_PARAM 4
#define CHORUSRATE_PARAM 5
#define CHORUSDEPTH_PARAM 6
#define LPFILT_PARAM 7

    switch (p) {
        case INPUT_PARAM:
            f->delay[s].input = (u32)val & 0xFFFFFFF8;
            break;
        case OUTPUT_PARAM:
            f->delay[s].output = (u32)val & 0xFFFFFFF8;
            break;
        case FFCOEF_PARAM:
            f->delay[s].ffcoef = (s16)val;
            break;
        case FBCOEF_PARAM:
            f->delay[s].fbcoef = (s16)val;
            break;
        case GAIN_PARAM:
            f->delay[s].gain = (s16)val;
            break;
        case CHORUSRATE_PARAM:
            /* f->delay[s].rsinc = ((f32)val)/0xffffff; */
            f->delay[s].rsinc = ((((f32)val) / 1000) * RANGE) / alGlobals->drvr.outputRate;
            break;

/*
 * the following constant is derived from:
 *
 *      ratio = 2^(cents/1200)
 *
 * and therefore for hundredths of a cent
 *                     x
 *      ln(ratio) = ---------------
 *              (120,000)/ln(2)
 * where
 *      120,000/ln(2) = 173123.40...
 */
#define CONVERT 173123.404906676
#define LENGTH (f->delay[s].output - f->delay[s].input)

        case CHORUSDEPTH_PARAM:
            /*f->delay[s].rsgain = (((f32)val) / CONVERT) * LENGTH; */
            f->delay[s].rsgain = (((f32)val) / CONVERT) * LENGTH;
            break;
        case LPFILT_PARAM:
            if (f->delay[s].lp) {
                f->delay[s].lp->fc = (s16)val;
                func_800733E0_main(f->delay[s].lp);
            }
            break;
    }
    return 0;
}

/* _loadOutputBuffer */
Acmd *func_800764B8_main(ALFx *r, ALDelay *d, s32 buff, s32 incount, Acmd *p) {
    Acmd *ptr = p;
    s32 ratio, count, rbuff = AL_TEMP_2;
    s16 *out_ptr;
    f32 fincount, fratio, delta;
    s32 ramalign = 0, length;
    /*
     * The following section implements the chorus resampling. Modulate where you pull
     * the samples from, since you need varying amounts of samples.
     */
    if (d->rs) {
        length = d->output - d->input;
        delta = func_80076A4C_main(d, incount); /* get the number of samples to modulate by */
        /*
         * find ratio of delta to delay length and quantize
         *  to same resolution as resampler
         */
        delta /= length;                    /* convert delta from number of samples to a pitch ratio */
        delta = (s32)(delta * UNITY_PITCH); /* quantize to value microcode will use */
        delta = delta / UNITY_PITCH;
        fratio = 1.0 - delta; /* pitch ratio needs to be centered around 1, not zero */

        /* d->rs->delta is the difference between the fractional and integer value
         * of the samples needed. fratio * incount + rs->delta gives the number of samples
         * needed for this frame.
         */
        fincount = d->rs->delta + (fratio * (f32)incount);
        count = (s32)fincount;                /* quantize to s32 */
        d->rs->delta = fincount - (f32)count; /* calculate the round off and store */

        /*
         * d->rsdelta is amount the out_ptr has deviated from its starting position.
         * You calc the out_ptr by taking d->output - d->rsdelta, and then using the
         * negative of that as an index into the delay buffer. loadBuffer that uses this
         * value then bumps it up if it is below the  delay buffer.
         */
        out_ptr = &r->input[-(d->output - d->rsdelta)];
        ramalign = ((s32)out_ptr & 0x7) >> 1; /* calculate the number of samples needed
                                               to align the buffer*/
        /* load the rbuff with samples, note that there will be ramalign worth of
         *  samples at the begining which you don't care about. */
        ptr = func_800766D0_main(r, out_ptr - ramalign, rbuff, count + ramalign, ptr);

        /* convert fratio to 16 bit fraction for microcode use */
        ratio = (s32)(fratio * UNITY_PITCH);
        /* set the buffers, and do the resample */
        aSetBuffer(ptr++, 0, rbuff + (ramalign << 1), buff, incount << 1);
        aResample(ptr++, d->rs->first, ratio, osVirtualToPhysical(d->rs->state));

        d->rs->first = 0;              /* turn off first time flag */
        d->rsdelta += count - incount; /* add the number of samples to d->rsdelta */
    } else {
        out_ptr = &r->input[-d->output];
        ptr = func_800766D0_main(r, out_ptr, buff, incount, ptr);
    }

    return ptr;
}
/*
 * This routine is for loading data from the delay line buff. If the
 * address of curr_ptr < r->base, it will force it to be within r->base
 * space, If the load goes past the end of r->base it will wrap around.
 * Cause count bytes of data at curr_ptr (within the delay line) to be
 * loaded into buff. (Buff is a dmem buffer)
 */
/* _loadBuffer */
Acmd *func_800766D0_main(ALFx *r, s16 *curr_ptr, s32 buff, s32 count, Acmd *p) {
    Acmd *ptr = p;
    s32 after_end, before_end;
    s16 *updated_ptr, *delay_end;

    delay_end = &r->base[r->length];

    if (curr_ptr < r->base) {
        curr_ptr += r->length;
    }
    updated_ptr = curr_ptr + count;

    if (updated_ptr > delay_end) {
        after_end = updated_ptr - delay_end;
        before_end = delay_end - curr_ptr;

        aSetBuffer(ptr++, 0, buff, 0, before_end << 1);
        aLoadBuffer(ptr++, osVirtualToPhysical(curr_ptr));
        aSetBuffer(ptr++, 0, buff + (before_end << 1), 0, after_end << 1);
        aLoadBuffer(ptr++, osVirtualToPhysical(r->base));
    } else {
        aSetBuffer(ptr++, 0, buff, 0, count << 1);
        aLoadBuffer(ptr++, osVirtualToPhysical(curr_ptr));
    }

    aSetBuffer(ptr++, 0, 0, 0, count << 1);

    return ptr;
}

/*
 * This routine is for writing data to the delay line buff. If the
 * address of curr_ptr < r->base, it will force it to be within r->base
 * space. If the write goes past the end of r->base, it will wrap around
 * Cause count bytes of data at buff to be written to delay line, curr_ptr.
 */
/* _saveBuffer */
Acmd *func_80076840_main(ALFx *r, s16 *curr_ptr, s32 buff, s32 count, Acmd *p) {
    Acmd *ptr = p;
    s32 after_end, before_end;
    s16 *updated_ptr, *delay_end;

    delay_end = &r->base[r->length];
    if (curr_ptr < r->base) {  /* probably just security */
        curr_ptr += r->length; /* shouldn't occur */
    }
    updated_ptr = curr_ptr + count;

    if (updated_ptr > delay_end) { /* if the data wraps past end of r->base */
        after_end = updated_ptr - delay_end;
        before_end = delay_end - curr_ptr;

        aSetBuffer(ptr++, 0, 0, buff, before_end << 1);
        aSaveBuffer(ptr++, osVirtualToPhysical(curr_ptr));
        aSetBuffer(ptr++, 0, 0, buff + (before_end << 1), after_end << 1);
        aSaveBuffer(ptr++, osVirtualToPhysical(r->base));
        aSetBuffer(ptr++, 0, 0, 0, count << 1);
    } else {
        aSetBuffer(ptr++, 0, 0, buff, count << 1);
        aSaveBuffer(ptr++, osVirtualToPhysical(curr_ptr));
    }

    return ptr;
}

/* _filterBuffer */
Acmd *func_800769B0_main(ALLowPass *lp, s32 buff, s32 count, Acmd *p) {
    Acmd *ptr = p;

    aSetBuffer(ptr++, 0, buff, buff, count << 1);
    aLoadADPCM(ptr++, 32, osVirtualToPhysical(lp->fcvec.fccoef));
    aPoleFilter(ptr++, lp->first, lp->fgain, osVirtualToPhysical(lp->fstate));
    lp->first = 0;

    return ptr;
}

/*
 * Generate a triangle wave from -1 to 1, and find the current position
 * in the wave. (Rate of the wave is controlled by d->rsinc, which is chorus
 * rate) Multiply the current triangle wave value by d->rsgain, (chorus depth)
 * which is expressed in number of samples back from output pointer the chorus
 * should go at it's full chorus. In otherwords, this function returns a number
 * of samples the output pointer should modulate backwards.
 */
/* _doModFunc */
f32 func_80076A4C_main(ALDelay *d, s32 count) {
    f32 val;

    /*
     * generate bipolar sawtooth
     * from -RANGE to +RANGE
     */
    d->rsval += d->rsinc * count;
    d->rsval = (d->rsval > RANGE) ? d->rsval - (RANGE * 2) : d->rsval;

    /*
     * convert to monopolar triangle
     * from 0 to RANGE
     */
    val = d->rsval;
    val = (val < 0) ? -val : val;

    /*
     * convert to bipolar triangle
     * from -1 to 1
     */
    val -= RANGE / 2;

    return (d->rsgain * val);
}
