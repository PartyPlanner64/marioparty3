#include "common.h"

/* Filter message ids used by the envelope mixer */
enum {
    AL_FILTER_FREE_VOICE = 0,
    AL_FILTER_ADD_UPDATE = 3,
    AL_FILTER_RESET = 4,
    AL_FILTER_SET_WAVETABLE = 5,
    AL_FILTER_SET_PITCH = 7,
    AL_FILTER_SET_UNITY_PITCH = 8,
    AL_FILTER_START = 9,
    AL_FILTER_SET_VOLUME = 11,
    AL_FILTER_SET_PAN = 12,
    AL_FILTER_START_VOICE_ALT = 13,
    AL_FILTER_START_VOICE = 14,
    AL_FILTER_STOP_VOICE = 15,
    AL_FILTER_SET_FXAMT = 16
};

typedef struct ALFilter_s {
    struct ALFilter_s *source;
    Acmd *(*handler)(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *cmdList);
    s32 (*setParam)(void *filter, s32 paramID, void *param);
} ALFilter;

typedef struct ALParam_s {
    struct ALParam_s *next;
    s32 delta;
    s16 type;
    union {
        f32 f;
        s32 i;
    } data;
    union {
        f32 f;
        s32 i;
    } moredata;
    union {
        f32 f;
        s32 i;
    } stillmoredata;
    union {
        f32 f;
        s32 i;
    } yetstillmoredata;
} ALParam;

typedef struct {
    struct ALParam_s *next;
    s32 delta;
    s16 type;
    s16 unity; /* disable resampler */
    f32 pitch;
    s16 volume;
    ALPan pan;
    u8 fxMix;
    s32 samples;
    struct ALWaveTable_s *wave;
} ALStartParamAlt;

typedef struct {
    struct ALParam_s *next;
    s32 delta;
    s16 type;
    s16 unity; /* disable resampler */
    struct ALWaveTable_s *wave;
} ALStartParam;

typedef struct {
    struct ALParam_s *next;
    s32 delta;
    s16 type;
    struct PVoice_s *pvoice;
} ALFreeParam;

/* Per voice filter. Sample loading, resampling and the envelope generator are
 * all kept in this single object, so the layout is the libultra load filter,
 * resampler and envelope mixer layouts laid end to end. */
typedef struct {
    /* 0x00 */ ALFilter filter;
    /* 0x0C */ ADPCM_STATE *state;
    /* 0x10 */ ADPCM_STATE *lstate;
    /* 0x14 */ s32 loopStart;
    /* 0x18 */ s32 loopEnd;
    /* 0x1C */ s32 loopCount;
    /* 0x20 */ struct ALWaveTable_s *table;
    /* 0x24 */ s32 bookSize;
    /* 0x28 */ void *dmaState;
    /* 0x2C */ void *unk_2C;
    /* 0x30 */ s32 sample;
    /* 0x34 */ s32 lastsam;
    /* 0x38 */ s32 loadFirst;
    /* 0x3C */ s32 memin;
    /* 0x40 */ void *rsState;
    /* 0x44 */ f32 rsRatio;
    /* 0x48 */ s32 rsUpitch;
    /* 0x4C */ f32 rsDelta;
    /* 0x50 */ s32 rsFirst;
    /* 0x54 */ void *envState;
    /* 0x58 */ s16 pan;
    /* 0x5A */ s16 volume;
    /* 0x5C */ s16 cvolL;
    /* 0x5E */ s16 cvolR;
    /* 0x60 */ s16 dryamt;
    /* 0x62 */ s16 wetamt;
    /* 0x64 */ u16 lratl;
    /* 0x66 */ s16 lratm;
    /* 0x68 */ s16 ltgt;
    /* 0x6A */ u16 rratl;
    /* 0x6C */ s16 rratm;
    /* 0x6E */ s16 rtgt;
    /* 0x70 */ s32 delta;
    /* 0x74 */ s32 segEnd;
    /* 0x78 */ s32 first;
    /* 0x7C */ ALParam *ctrlList;
    /* 0x80 */ ALParam *ctrlTail;
    /* 0x84 */ s32 motion;
} ALEnvMixer;

typedef struct PVoice_s {
    ALEnvMixer envmixer;
    s32 offset;
} PVoice;

/* Equal-power attenuation table for pan and dry/wet mixing. */
s16 D_800A2780_main[128] = {
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

void func_8006BBE8_main(ALParam *param);
void func_8006BC60_main(PVoice *voice);
s32 func_8006A9C8_main(ALEnvMixer *e, s32 paramID, void *param);
Acmd *func_8006AA6C_main(ALEnvMixer *filter, s16 *inp, s16 *outp, s32 outCount, Acmd *p);
s16 func_8006ADCC_main(s16 ivol, s32 samples, s16 ratem, u16 ratel);
s16 func_8006AC8C_main(f64 vol, f64 tgt, s32 count, u16 *ratel);
s32 func_8006B268_main(ALEnvMixer *e, s32 paramID, void *param);
Acmd *func_8006B540_main(ALEnvMixer *e, s16 *inp, Acmd *p);

Acmd *func_8006A450_main(ALEnvMixer *filter, s32 sampleOffset, Acmd *p) {
    Acmd *ptr = p;
    ALEnvMixer *e = filter;
    s16 inp;
    s32 lastOffset;
    s32 thisOffset = sampleOffset;
    s32 outCount = 184;
    s32 samples;
    s16 loutp = 0;
    s32 fVol;
    ALParam *thisParam;

    inp = 0;

    while (e->ctrlList != 0) {
        lastOffset = thisOffset;
        thisOffset = e->ctrlList->delta;
        /* Control updates are rounded to the nearest 184-sample frame. */
        samples = ((thisOffset - lastOffset + 92) / 184) * 184;
        if (samples == 0) {
            thisOffset = lastOffset;
        }
        if (samples > outCount) {
            break;
        }

        switch (e->ctrlList->type) {
            case AL_FILTER_START_VOICE_ALT: {
                ALStartParamAlt *param = (ALStartParamAlt *)e->ctrlList;

                s32 tmp;

                if (param->unity) {
                    e->rsUpitch = 1;
                }

                func_8006B268_main(e, AL_FILTER_SET_WAVETABLE, param->wave);
                e->motion = AL_PLAYING;

                e->first = 1;

                e->delta = 0;
                e->segEnd = ((param->samples + 92) / 184) * 184;

                tmp = ((s32)param->volume * (s32)param->volume) >> 15;
                e->volume = (s16)tmp;
                e->pan = param->pan;
                e->dryamt = D_800A2780_main[param->fxMix];
                e->wetamt = D_800A2780_main[128 - param->fxMix - 1];

                if (param->samples) {
                    e->cvolL = 1;
                    e->cvolR = 1;
                } else {
                    e->cvolL = (e->volume * D_800A2780_main[e->pan]) >> 15;
                    e->cvolR = (e->volume * D_800A2780_main[127 - e->pan]) >> 15;
                }

                e->rsRatio = param->pitch;
            }

            break;

            case AL_FILTER_SET_FXAMT:
            case AL_FILTER_SET_PAN:
            case AL_FILTER_SET_VOLUME:
                ptr = func_8006AA6C_main(e, &inp, &loutp, samples, ptr);

                if (e->delta >= e->segEnd) {
                    e->ltgt = (e->volume * D_800A2780_main[e->pan]) >> 15;
                    e->rtgt = (e->volume * D_800A2780_main[127 - e->pan]) >> 15;
                    e->delta = e->segEnd;
                    e->cvolL = e->ltgt;
                    e->cvolR = e->rtgt;
                } else {
                    e->cvolL = func_8006ADCC_main(e->cvolL, e->delta, e->lratm, e->lratl);
                    e->cvolR = func_8006ADCC_main(e->cvolR, e->delta, e->rratm, e->rratl);
                }

                if (e->cvolL == 0)
                    e->cvolL = 1;
                if (e->cvolR == 0)
                    e->cvolR = 1;

                if (e->ctrlList->type == AL_FILTER_SET_PAN) {
                    e->pan = e->ctrlList->data.i;
                }

                if (e->ctrlList->type == AL_FILTER_SET_VOLUME) {
                    e->delta = 0;

                    fVol = (e->ctrlList->data.i);
                    fVol = (fVol * fVol) >> 15;
                    e->volume = (s16)fVol;

                    e->segEnd = ((e->ctrlList->moredata.i + 92) / 184) * 184;
                }

                if (e->ctrlList->type == AL_FILTER_SET_FXAMT) {
                    e->dryamt = D_800A2780_main[e->ctrlList->data.i];
                    e->wetamt = D_800A2780_main[128 - e->ctrlList->data.i - 1];
                }

                e->first = 1;
                break;

            case AL_FILTER_START_VOICE: {
                ALStartParam *p = (ALStartParam *)e->ctrlList;

                if (p->unity) {
                    e->rsUpitch = 1;
                }

                func_8006B268_main(e, AL_FILTER_SET_WAVETABLE, p->wave);
                e->motion = AL_PLAYING;
            } break;

            case AL_FILTER_STOP_VOICE: {
                ptr = func_8006AA6C_main(e, &inp, &loutp, samples, ptr);
                func_8006A9C8_main(e, AL_FILTER_RESET, 0);
            } break;

            case AL_FILTER_FREE_VOICE: {
                ALFreeParam *param = (ALFreeParam *)e->ctrlList;
                param->pvoice->offset = 0;
                func_8006BC60_main(param->pvoice);
            } break;

            case AL_FILTER_SET_PITCH:
                ptr = func_8006AA6C_main(e, &inp, &loutp, samples, ptr);
                e->rsRatio = e->ctrlList->data.f;
                break;
            case AL_FILTER_SET_UNITY_PITCH:
                ptr = func_8006AA6C_main(e, &inp, &loutp, samples, ptr);
                e->rsUpitch = 1;
                break;
            case AL_FILTER_SET_WAVETABLE:
                ptr = func_8006AA6C_main(e, &inp, &loutp, samples, ptr);
                func_8006B268_main(e, AL_FILTER_SET_WAVETABLE, (void *)e->ctrlList->data.i);
                break;
            default:

                ptr = func_8006AA6C_main(e, &inp, &loutp, samples, ptr);
                func_8006A9C8_main(e, e->ctrlList->type,
                                   (void *)e->ctrlList->data.i);
                break;
        }
        loutp += (samples << 1);
        outCount -= samples;

        thisParam = e->ctrlList;
        e->ctrlList = e->ctrlList->next;
        if (e->ctrlList == 0)
            e->ctrlTail = 0;

        func_8006BBE8_main(thisParam);
    }

    ptr = func_8006AA6C_main(e, &inp, &loutp, outCount, ptr);

    if (e->delta > e->segEnd)
        e->delta = e->segEnd;

    return ptr;
}

s32 func_8006A9C8_main(ALEnvMixer *e, s32 paramID, void *param) {
    switch (paramID) {
        case AL_FILTER_ADD_UPDATE:
            if (e->ctrlTail) {
                e->ctrlTail->next = param;
            } else {
                e->ctrlList = param;
            }
            e->ctrlTail = param;
            break;

        case AL_FILTER_RESET:
            e->first = 1;
            e->motion = AL_STOPPED;
            e->volume = 1;
            e->segEnd = 0;
            e->rsDelta = 0.0f;
            e->rsFirst = 1;
            e->rsUpitch = 0;
            func_8006B268_main(e, AL_FILTER_RESET, param);
            break;

        case AL_FILTER_START:
            e->motion = AL_PLAYING;
            break;

        default:
            func_8006B268_main(e, paramID, param);
            break;
    }

    return 0;
}

Acmd *func_8006AA6C_main(ALEnvMixer *filter, s16 *inp, s16 *outp, s32 outCount, Acmd *p) {
    Acmd *ptr = p;
    ALEnvMixer *e = filter;

    if (e->motion != AL_PLAYING || !outCount) {
        return ptr;
    }

    ptr = func_8006B540_main(e, inp, p);
    if (e->first) {
        Acmd *cmd;

        e->first = 0;
        e->ltgt = (e->volume * D_800A2780_main[e->pan]) >> 15;
        e->lratm = func_8006AC8C_main(e->cvolL, e->ltgt, e->segEnd, &e->lratl);
        e->rtgt = (e->volume * D_800A2780_main[127 - e->pan]) >> 15;
        e->rratm = func_8006AC8C_main(e->cvolR, e->rtgt, e->segEnd, &e->rratl);

        /* This microcode packs the dry/wet amounts with the left volume,
         * and the initial right volume into the envelope command. */
        aSetVolume(ptr++, A_RATE, e->ltgt, e->lratm, e->lratl);
        aSetVolume(ptr++, A_LEFT | A_VOL, e->cvolL, e->dryamt, e->wetamt);
        aSetVolume(ptr++, A_VOL, e->rtgt, e->rratm, e->rratl);
        cmd = ptr++;
        cmd->words.w0 = _SHIFTL(A_ENVMIXER, 24, 8) | _SHIFTL(A_INIT, 16, 8) | _SHIFTL(e->cvolR, 0, 16);
        cmd->words.w1 = osVirtualToPhysical(e->envState);
    } else {
        aEnvMixer(ptr++, A_CONTINUE, osVirtualToPhysical(e->envState));
    }

    *inp += 184 * 2;
    e->delta += 184;
    return ptr;
}

s16 func_8006AC8C_main(f64 vol, f64 tgt, s32 count, u16 *ratel) {
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

s16 func_8006ADCC_main(s16 ivol, s32 samples, s16 ratem, u16 ratel) {
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
