#include "common.h"
#include "PR/synthInternals.h"

/* alMainBusPull */
Acmd *func_80075B20_main(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p) {
    Acmd *ptr = p;
    ALMainBus *m = (ALMainBus *)filter;
    ALFilter **sources = m->sources;
    s32 i;

    /*
     * clear the output buffers here
     */
    aClearBuffer(ptr++, AL_MAIN_L_OUT, outCount << 1);
    aClearBuffer(ptr++, AL_MAIN_R_OUT, outCount << 1);

    for (i = 0; i < m->sourceCount; i++) {
        ptr = (sources[i]->handler)(sources[i], outp, outCount, sampleOffset, ptr);
        aSetBuffer(ptr++, 0, 0, 0, outCount << 1);
        aMix(ptr++, 0, 0x7FFF, AL_AUX_L_OUT, AL_MAIN_L_OUT);
        aMix(ptr++, 0, 0x7FFF, AL_AUX_R_OUT, AL_MAIN_R_OUT);
    }

    return ptr;
}

/* alMainBusParam */
s32 func_80075C60_main(void *filter, s32 paramID, void *param) {
    ALMainBus *m = (ALMainBus *)filter;
    ALFilter **sources = m->sources;

    switch (paramID) {
        case AL_FILTER_ADD_SOURCE:
            sources[m->sourceCount++] = (ALFilter *)param;
            break;

        default:
            break;
    }

    return 0;
}
