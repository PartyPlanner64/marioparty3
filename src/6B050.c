#include "common.h"

/* Filter message ids used by the envelope mixer */
enum {
    AL_FILTER_ADD_UPDATE = 3,
    AL_FILTER_RESET = 4,
    AL_FILTER_START = 9
};

typedef struct ALFilter_s {
    struct ALFilter_s *source;
    Acmd *(*handler)(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *cmdList);
    s32 (*setParam)(void *filter, s32 paramID, void *param);
} ALFilter;

/* Node of the envelope control list. Nodes are cast to the parameter structs
 * the individual messages need, the widest of which reaches offset 0x1C. */
typedef struct ALParam_s {
    /* 0x00 */ struct ALParam_s *next;
    /* 0x04 */ s32 delta;
    /* 0x08 */ s16 type;
    /* 0x0A */ char unk_0A[0x12];
} ALParam;

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

s32 func_8006B268_main(ALEnvMixer *e, s32 paramID, void *param);

INCLUDE_ASM("asm/nonmatchings/6B050", func_8006A450_main);

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

INCLUDE_ASM("asm/nonmatchings/6B050", func_8006AA6C_main);

INCLUDE_ASM("asm/nonmatchings/6B050", func_8006AC8C_main);

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
