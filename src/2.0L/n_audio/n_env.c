#include "common.h"
#include "PR/n_synthInternals.h"

/* Equal-power attenuation table for pan and dry/wet mixing. */
static s16 eqpower[128] = {
    32767, 32764, 32757, 32744, 32727, 32704,
    32677, 32644, 32607, 32564, 32517, 32464,
    32407, 32344, 32277, 32205, 32127, 32045,
    31958, 31866, 31770, 31668, 31561, 31450,
    31334, 31213, 31087, 30957, 30822, 30682,
    30537, 30388, 30234, 30075, 29912, 29744,
    29572, 29395, 29214, 29028, 28838, 28643,
    28444, 28241, 28033, 27821, 27605, 27385,
    27160, 26931, 26698, 26461, 26220, 25975,
    25726, 25473, 25216, 24956, 24691, 24423,
    24151, 23875, 23596, 23313, 23026, 22736,
    22442, 22145, 21845, 21541, 21234, 20924,
    20610, 20294, 19974, 19651, 19325, 18997,
    18665, 18331, 17993, 17653, 17310, 16965,
    16617, 16266, 15913, 15558, 15200, 14840,
    14477, 14113, 13746, 13377, 13006, 12633,
    12258, 11881, 11503, 11122, 10740, 10357,
    9971, 9584, 9196, 8806, 8415, 8023,
    7630, 7235, 6839, 6442, 6044, 5646,
    5246, 4845, 4444, 4042, 3640, 3237,
    2833, 2429, 2025, 1620, 1216, 810,
    405, 0
};

Acmd *__n_pullSubFrame(N_PVoice *filter, s16 *inp, s16 *outp, s32 outCount, Acmd *p);
s16 __n_getVol(s16 ivol, s32 samples, s16 ratem, u16 ratel);
s16 __n_getRate(f64 vol, f64 tgt, s32 count, u16 *ratel);

Acmd *n_alEnvmixerPull(N_PVoice *filter, s32 sampleOffset, Acmd *p) {
    Acmd *ptr = p;
    N_PVoice *e = filter;
    s16 inp;
    s32 lastOffset;
    s32 thisOffset = sampleOffset;
    s32 outCount = 184;
    s32 samples;
    s16 loutp = 0;
    s32 fVol;
    ALParam *thisParam;

    inp = 0;

    while (e->em_ctrlList != 0) {
        lastOffset = thisOffset;
        thisOffset = e->em_ctrlList->delta;
        /* Control updates are rounded to the nearest 184-sample frame. */
        samples = ((thisOffset - lastOffset + 92) / 184) * 184;
        if (samples == 0) {
            thisOffset = lastOffset;
        }
        if (samples > outCount) {
            break;
        }

        switch (e->em_ctrlList->type) {
            case AL_FILTER_START_VOICE_ALT: {
                ALStartParamAlt *param = (ALStartParamAlt *)e->em_ctrlList;

                s32 tmp;

                if (param->unity) {
                    e->rs_upitch = 1;
                }

                n_alLoadParam(e, AL_FILTER_SET_WAVETABLE, param->wave);
                e->em_motion = AL_PLAYING;

                e->em_first = 1;

                e->em_delta = 0;
                e->em_segEnd = ((param->samples + 92) / 184) * 184;

                tmp = ((s32)param->volume * (s32)param->volume) >> 15;
                e->em_volume = (s16)tmp;
                e->em_pan = param->pan;
                e->em_dryamt = eqpower[param->fxMix];
                e->em_wetamt = eqpower[128 - param->fxMix - 1];

                if (param->samples) {
                    e->em_cvolL = 1;
                    e->em_cvolR = 1;
                } else {
                    e->em_cvolL = (e->em_volume * eqpower[e->em_pan]) >> 15;
                    e->em_cvolR = (e->em_volume * eqpower[127 - e->em_pan]) >> 15;
                }

                e->rs_ratio = param->pitch;
            }

            break;

            case AL_FILTER_SET_FXAMT:
            case AL_FILTER_SET_PAN:
            case AL_FILTER_SET_VOLUME:
                ptr = __n_pullSubFrame(e, &inp, &loutp, samples, ptr);

                if (e->em_delta >= e->em_segEnd) {
                    e->em_ltgt = (e->em_volume * eqpower[e->em_pan]) >> 15;
                    e->em_rtgt = (e->em_volume * eqpower[127 - e->em_pan]) >> 15;
                    e->em_delta = e->em_segEnd;
                    e->em_cvolL = e->em_ltgt;
                    e->em_cvolR = e->em_rtgt;
                } else {
                    e->em_cvolL = __n_getVol(e->em_cvolL, e->em_delta, e->em_lratm, e->em_lratl);
                    e->em_cvolR = __n_getVol(e->em_cvolR, e->em_delta, e->em_rratm, e->em_rratl);
                }

                if (e->em_cvolL == 0)
                    e->em_cvolL = 1;
                if (e->em_cvolR == 0)
                    e->em_cvolR = 1;

                if (e->em_ctrlList->type == AL_FILTER_SET_PAN) {
                    e->em_pan = e->em_ctrlList->data.i;
                }

                if (e->em_ctrlList->type == AL_FILTER_SET_VOLUME) {
                    e->em_delta = 0;

                    fVol = (e->em_ctrlList->data.i);
                    fVol = (fVol * fVol) >> 15;
                    e->em_volume = (s16)fVol;

                    e->em_segEnd = ((e->em_ctrlList->moredata.i + 92) / 184) * 184;
                }

                if (e->em_ctrlList->type == AL_FILTER_SET_FXAMT) {
                    e->em_dryamt = eqpower[e->em_ctrlList->data.i];
                    e->em_wetamt = eqpower[128 - e->em_ctrlList->data.i - 1];
                }

                e->em_first = 1;
                break;

            case AL_FILTER_START_VOICE: {
                ALStartParam *p = (ALStartParam *)e->em_ctrlList;

                if (p->unity) {
                    e->rs_upitch = 1;
                }

                n_alLoadParam(e, AL_FILTER_SET_WAVETABLE, p->wave);
                e->em_motion = AL_PLAYING;
            } break;

            case AL_FILTER_STOP_VOICE: {
                ptr = __n_pullSubFrame(e, &inp, &loutp, samples, ptr);
                n_alEnvmixerParam(e, AL_FILTER_RESET, 0);
            } break;

            case AL_FILTER_FREE_VOICE: {
                ALFreeParam *param = (ALFreeParam *)e->em_ctrlList;
                param->pvoice->offset = 0;
                _n_freePVoice(param->pvoice);
            } break;

            case AL_FILTER_SET_PITCH:
                ptr = __n_pullSubFrame(e, &inp, &loutp, samples, ptr);
                e->rs_ratio = e->em_ctrlList->data.f;
                break;
            case AL_FILTER_SET_UNITY_PITCH:
                ptr = __n_pullSubFrame(e, &inp, &loutp, samples, ptr);
                e->rs_upitch = 1;
                break;
            case AL_FILTER_SET_WAVETABLE:
                ptr = __n_pullSubFrame(e, &inp, &loutp, samples, ptr);
                n_alLoadParam(e, AL_FILTER_SET_WAVETABLE, (void *)e->em_ctrlList->data.i);
                break;
            default:

                ptr = __n_pullSubFrame(e, &inp, &loutp, samples, ptr);
                n_alEnvmixerParam(e, e->em_ctrlList->type,
                                   (void *)e->em_ctrlList->data.i);
                break;
        }
        loutp += (samples << 1);
        outCount -= samples;

        thisParam = e->em_ctrlList;
        e->em_ctrlList = e->em_ctrlList->next;
        if (e->em_ctrlList == 0)
            e->em_ctrlTail = 0;

        __n_freeParam(thisParam);
    }

    ptr = __n_pullSubFrame(e, &inp, &loutp, outCount, ptr);

    if (e->em_delta > e->em_segEnd)
        e->em_delta = e->em_segEnd;

    return ptr;
}

s32 n_alEnvmixerParam(N_PVoice *e, s32 paramID, void *param) {
    switch (paramID) {
        case AL_FILTER_ADD_UPDATE:
            if (e->em_ctrlTail) {
                e->em_ctrlTail->next = param;
            } else {
                e->em_ctrlList = param;
            }
            e->em_ctrlTail = param;
            break;

        case AL_FILTER_RESET:
            e->em_first = 1;
            e->em_motion = AL_STOPPED;
            e->em_volume = 1;
            e->em_segEnd = 0;
            e->rs_delta = 0.0f;
            e->rs_first = 1;
            e->rs_upitch = 0;
            n_alLoadParam(e, AL_FILTER_RESET, param);
            break;

        case AL_FILTER_START:
            e->em_motion = AL_PLAYING;
            break;

        default:
            n_alLoadParam(e, paramID, param);
            break;
    }

    return 0;
}

Acmd *__n_pullSubFrame(N_PVoice *filter, s16 *inp, s16 *outp, s32 outCount, Acmd *p) {
    Acmd *ptr = p;
    N_PVoice *e = filter;

    if (e->em_motion != AL_PLAYING || !outCount) {
        return ptr;
    }

    ptr = n_alResamplePull(e, inp, p);
    if (e->em_first) {
        Acmd *cmd;

        e->em_first = 0;
        e->em_ltgt = (e->em_volume * eqpower[e->em_pan]) >> 15;
        e->em_lratm = __n_getRate(e->em_cvolL, e->em_ltgt, e->em_segEnd, &e->em_lratl);
        e->em_rtgt = (e->em_volume * eqpower[127 - e->em_pan]) >> 15;
        e->em_rratm = __n_getRate(e->em_cvolR, e->em_rtgt, e->em_segEnd, &e->em_rratl);

        /* This microcode packs the dry/wet amounts with the left volume,
         * and the initial right volume into the envelope command. */
        aSetVolume(ptr++, A_RATE, e->em_ltgt, e->em_lratm, e->em_lratl);
        aSetVolume(ptr++, A_LEFT | A_VOL, e->em_cvolL, e->em_dryamt, e->em_wetamt);
        aSetVolume(ptr++, A_VOL, e->em_rtgt, e->em_rratm, e->em_rratl);
        cmd = ptr++;
        cmd->words.w0 = _SHIFTL(A_ENVMIXER, 24, 8) | _SHIFTL(A_INIT, 16, 8) | _SHIFTL(e->em_cvolR, 0, 16);
        cmd->words.w1 = osVirtualToPhysical(e->em_state);
    } else {
        aEnvMixer(ptr++, A_CONTINUE, osVirtualToPhysical(e->em_state));
    }

    *inp += 184 * 2;
    e->em_delta += 184;
    return ptr;
}

s16 __n_getRate(f64 vol, f64 tgt, s32 count, u16 *ratel) {
    s16 s;
    s16 carry;
    f64 invn;
    f64 rate;

    if (count == 0) {
        if (tgt >= vol) {
            *ratel = 0xFFFF;
            return 0x7FFF;
        } else {
            *ratel = 0;
            return -0x8000;
        }
    }

    invn = 1.0 / count;
    if (tgt < 1.0) {
        tgt = 1.0;
    }
    if (vol <= 0.0) {
        vol = 1.0;
    }

    /* The envelope advances by this signed fixed-point rate every eight samples. */
    rate = (tgt - vol) * invn;
    rate *= 8.0;
    s = rate;
    rate -= s;
    rate += 1.0;
    carry = rate;
    rate -= carry;
    s -= 1;
    s += carry;
    *ratel = (u32)(rate * 65535.0);
    return s;
}

s16 __n_getVol(s16 ivol, s32 samples, s16 ratem, u16 ratel) {
    s32 inc;

    /* Rate values are actually rate^8 */
    samples >>= 3;
    if (samples == 0) {
        return ivol;
    }

    inc = (ratel * samples) >> 16;
    inc += ratem * samples;
    return ivol + inc;
}
