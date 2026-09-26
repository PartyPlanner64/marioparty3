#include "common.h"

/* Filter message id that appends a bus to this bus's chain. alSynNew uses it to
 * attach the synth's aux bus array to the main bus. */
enum {
    AL_FILTER_ADD_OUTBUS = 2
};

/* Filter header installed at the front of every filter by func_80075B00_main. */
typedef struct ALFilter_s {
    struct ALFilter_s *source;
    Acmd *(*handler)(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *cmdList);
    s32 (*setParam)(void *filter, s32 paramID, void *param);
    /* 0x0C */ s16 inp;
    /* 0x0E */ s16 outp;
    /* 0x10 */ s32 type;
} ALFilter;

/* The main bus, set up past its filter header by func_80073B6C_main. Its pull
 * handler walks outBus for the first inBus entries. */
typedef struct N_ALMainBus_s {
    /* 0x00 */ ALFilter filter;
    /* 0x14 */ s32 inBus; /* number of busses in outBus */
    /* 0x18 */ s32 maxAuxBusses;
    /* 0x1C */ struct ALFilter_s **outBus;
} N_ALMainBus;

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/mainbus", func_80075B20_main);

s32 func_80075C60_main(N_ALMainBus *mainBus, s32 paramID, struct ALFilter_s *param) {
    struct ALFilter_s **outBus = mainBus->outBus;

    if (paramID == AL_FILTER_ADD_OUTBUS) {
        s32 inBus = mainBus->inBus;

        mainBus->inBus = inBus + 1;
        outBus[inBus] = param;
    }

    return 0;
}
