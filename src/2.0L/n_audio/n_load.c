#include "common.h"
#include "PR/n_synthInternals.h"

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#define ADPCMFBYTES 9
#define LFSAMPLES 4

Acmd *_n_decodeChunk(Acmd *ptr, N_PVoice *f, s32 tsam, s32 nbytes, s16 outp, s16 inp, u32 flags);

Acmd *n_alAdpcmPull(N_PVoice *filter, s16 *outp, s32 outCount, Acmd *p) {
    Acmd *ptr = p;
    s16 inp;
    s32 tsam;
    s32 nframes;
    s32 nbytes;
    s32 overFlow;
    s32 startZero;
    s32 nOver;
    s32 nSam;
    s32 op;
    s32 nLeft;
    s32 bEnd;
    s32 decoded = 0;
    s32 looped = 0;
    N_PVoice *f = filter;

    if (outCount == 0) {
        return ptr;
    }

    inp = N_AL_DECODER_IN;
    aLoadADPCM(ptr++, f->dc_bookSize, K0_TO_PHYS(f->dc_table->waveInfo.adpcmWave.book->book));

    looped = (outCount + f->dc_sample > f->dc_loop.end) && (f->dc_loop.count != 0);
    if (looped) {
        nSam = f->dc_loop.end - f->dc_sample;
    } else {
        nSam = outCount;
    }

    if (f->dc_lastsam) {
        nLeft = ADPCMFSIZE - f->dc_lastsam;
    } else {
        nLeft = 0;
    }
    tsam = nSam - nLeft;
    if (tsam < 0) {
        tsam = 0;
    }

    nframes = (tsam + ADPCMFSIZE - 1) >> LFSAMPLES;
    nbytes = nframes * ADPCMFBYTES;

    if (looped) {
        ptr = _n_decodeChunk(ptr, f, tsam, nbytes, *outp, inp, f->dc_first);

        /*
         * Fix up output pointer, which will be used as the input pointer
         * by the following module.
         */
        if (f->dc_lastsam) {
            *outp += (f->dc_lastsam << 1);
        } else {
            *outp += (ADPCMFSIZE << 1);
        }

        /*
         * Now fix up state info to reflect the loop start point
         */
        f->dc_lastsam = f->dc_loop.start & 0xF;
        f->dc_memin = (s32)f->dc_table->base + ADPCMFBYTES * ((s32)(f->dc_loop.start >> LFSAMPLES) + 1);
        f->dc_sample = f->dc_loop.start;

        bEnd = *outp;
        while (outCount > nSam) {
            outCount -= nSam;

            /*
             * Put next one after the end of the last lot - on the
             * frame boundary (32 byte) after the end.
             */
            op = (bEnd + ((nframes + 1) << (LFSAMPLES + 1)) + 0x10) & ~0x1F;

            /*
             * The actual end of data
             */
            bEnd += (nSam << 1);

            /*
             * -1 is loop forever - the loop count is not exact now
             * for small loops!
             */
            if ((f->dc_loop.count != -1) && (f->dc_loop.count != 0)) {
                f->dc_loop.count--;
            }

            /*
             * What's left to compute.
             */
            nSam = MIN(outCount, f->dc_loop.end - f->dc_loop.start);
            tsam = nSam - ADPCMFSIZE + f->dc_lastsam;
            if (tsam < 0) {
                tsam = 0;
            }
            nframes = (tsam + ADPCMFSIZE - 1) >> LFSAMPLES;
            nbytes = nframes * ADPCMFBYTES;
            ptr = _n_decodeChunk(ptr, f, tsam, nbytes, op, inp, f->dc_first | A_LOOP);

            /*
             * Merge the two sections in DMEM.
             */
            aDMEMMove(ptr++, op + (f->dc_lastsam << 1), bEnd, nSam << 1);
        }

        f->dc_lastsam = (outCount + f->dc_lastsam) & 0xF;
        f->dc_sample += outCount;
        f->dc_memin += ADPCMFBYTES * nframes;
        return ptr;
    }

    /*
     * The unlooped case, which is executed most of the time
     */
    nSam = nframes << LFSAMPLES;

    /*
     * overFlow is the number of bytes past the end
     * of the bitstream I try to generate
     */
    overFlow = f->dc_memin + nbytes - ((s32)f->dc_table->base + f->dc_table->len);
    if (overFlow < 0) {
        overFlow = 0;
    }
    nOver = (overFlow / ADPCMFBYTES) << LFSAMPLES;
    if (nOver > nSam + nLeft) {
        nOver = nSam + nLeft;
    }

    nbytes -= overFlow;

    if ((nOver - (nOver & 0xF)) < outCount) {
        decoded = 1;
        ptr = _n_decodeChunk(ptr, f, nSam - nOver, nbytes, *outp, inp, f->dc_first);

        if (f->dc_lastsam) {
            *outp += (f->dc_lastsam << 1);
        } else {
            *outp += (ADPCMFSIZE << 1);
        }

        f->dc_lastsam = (outCount + f->dc_lastsam) & 0xF;
        f->dc_sample += outCount;
        f->dc_memin += ADPCMFBYTES * nframes;
    } else {
        f->dc_lastsam = 0;
        f->dc_memin += ADPCMFBYTES * nframes;
    }

    /*
     * Put zeros in if necessary
     */
    if (nOver) {
        f->dc_lastsam = 0;
        if (decoded) {
            startZero = (nLeft + nSam - nOver) << 1;
        } else {
            startZero = 0;
        }
        aClearBuffer(ptr++, startZero + *outp, nOver << 1);
    }

    return ptr;
}

void n_alLoadParam(N_PVoice *v, s32 paramID, void *param) {
    switch (paramID) {
        case AL_FILTER_SET_WAVETABLE:
            v->dc_table = (ALWaveTable *)param;
            v->dc_memin = (s32)v->dc_table->base;
            v->dc_sample = 0;
            switch (v->dc_table->type) {
                case AL_ADPCM_WAVE:
                    /*
                     * Make sure the table length is an integer number of
                     * frames
                     */
                    v->dc_table->len = ADPCMFBYTES * (v->dc_table->len / ADPCMFBYTES);

                    v->dc_bookSize = 2 * v->dc_table->waveInfo.adpcmWave.book->order *
                                     v->dc_table->waveInfo.adpcmWave.book->npredictors * ADPCMVSIZE;
                    if (v->dc_table->waveInfo.adpcmWave.loop) {
                        v->dc_loop.start = v->dc_table->waveInfo.adpcmWave.loop->start;
                        v->dc_loop.end = v->dc_table->waveInfo.adpcmWave.loop->end;
                        v->dc_loop.count = v->dc_table->waveInfo.adpcmWave.loop->count;
                        bcopy(v->dc_table->waveInfo.adpcmWave.loop->state, v->dc_lstate, sizeof(ADPCM_STATE));
                    } else {
                        v->dc_loop.start = v->dc_loop.end = v->dc_loop.count = 0;
                    }
                    break;

                case AL_RAW16_WAVE:
                    if (v->dc_table->waveInfo.rawWave.loop) {
                        v->dc_loop.start = v->dc_table->waveInfo.rawWave.loop->start;
                        v->dc_loop.end = v->dc_table->waveInfo.rawWave.loop->end;
                        v->dc_loop.count = v->dc_table->waveInfo.rawWave.loop->count;
                    } else {
                        v->dc_loop.start = v->dc_loop.end = v->dc_loop.count = 0;
                    }
                    break;

                default:
                    break;
            }
            break;

        case AL_FILTER_RESET:
            v->dc_lastsam = 0;
            v->dc_first = 1;
            v->dc_sample = 0;

            /* sct 2/14/96 - Check table since it is initialized to null and */
            /* Get loop info according to table type. */
            if (v->dc_table) {
                v->dc_memin = (s32)v->dc_table->base;
                if (v->dc_table->type == AL_ADPCM_WAVE) {
                    if (v->dc_table->waveInfo.adpcmWave.loop) {
                        v->dc_loop.count = v->dc_table->waveInfo.adpcmWave.loop->count;
                    }
                } else if (v->dc_table->type == AL_RAW16_WAVE) {
                    if (v->dc_table->waveInfo.rawWave.loop) {
                        v->dc_loop.count = v->dc_table->waveInfo.rawWave.loop->count;
                    }
                }
            }
            break;

        default:
            break;
    }
}

Acmd *_n_decodeChunk(Acmd *ptr, N_PVoice *f, s32 tsam, s32 nbytes, s16 outp, s16 inp, u32 flags) {
    s32 dramAlign;
    s32 dramLoc;

    if (nbytes > 0) {
        dramLoc = (f->dc_dma)(f->dc_memin, nbytes, f->dc_dmaState);
        /*
         * Make sure enough is loaded into DMEM to take care
         * of 8 byte alignment
         */
        dramAlign = dramLoc & 0x7;
        nbytes += dramAlign;
        n_aLoadBuffer(ptr++, nbytes + 8 - (nbytes & 0x7), inp, dramLoc - dramAlign);
    } else {
        dramAlign = 0;
    }

    if (flags & A_LOOP) {
        aSetLoop(ptr++, K0_TO_PHYS(f->dc_lstate));
    }

    n_aADPCMdec(ptr++, K0_TO_PHYS(f->dc_state), flags, tsam << 1, dramAlign, outp);
    f->dc_first = 0;

    return ptr;
}
