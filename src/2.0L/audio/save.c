#include "common.h"

/* Filter message ids understood by this filter's setParam handler. */
enum {
    AL_FILTER_SET_SOURCE = 1,
    AL_FILTER_SET_DRAM = 6
};

/* Byte offsets of the synth's main output pair in the RSP mixer input buffer. */
#define AL_MAIN_L_OUT 1088
#define AL_MAIN_R_OUT 1408

typedef struct ALFilter_s {
    struct ALFilter_s *source;
    Acmd *(*handler)(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *cmdList);
    s32 (*setParam)(void *filter, s32 paramID, void *param);
    /* 0x0C */ s16 inp;
    /* 0x0E */ s16 outp;
    /* 0x10 */ s32 type;
} ALFilter;

/* The synth's output filter. func_80076AE0_main is its pull handler, which emits
 * the filter's state as RSP commands, and func_80076B88_main is the setParam
 * handler that func_80073BC8_main installs alongside it. */
typedef struct ALSave_s {
    ALFilter filter;
    /* 0x14 */ s32 dramout;
    /* 0x18 */ s32 first;
} ALSave;

Acmd *func_80076AE0_main(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *cmdList) {
    Acmd *ptr = cmdList;
    ALSave *f = (ALSave *)filter;
    ALFilter *source = f->filter.source;

    ptr = source->handler(source, outp, outCount, sampleOffset, ptr);

    aSetBuffer(ptr++, 0, 0, 0, outCount << 1);
    aInterleave(ptr++, AL_MAIN_L_OUT, AL_MAIN_R_OUT);
    aSetBuffer(ptr++, 0, 0, 0, outCount << 2);
    aSaveBuffer(ptr++, f->dramout);
    return ptr;
}

s32 func_80076B88_main(void *filter, s32 paramID, void *param) {
    ALSave *save = (ALSave *)filter;
    ALFilter *f = (ALFilter *)filter;
    s32 pp = (s32)param;

    switch (paramID) {
        case AL_FILTER_SET_SOURCE:
            f->source = (ALFilter *)param;
            break;

        case AL_FILTER_SET_DRAM:
            save->dramout = pp;
            break;

        default:
            break;
    }
    return 0;
}
