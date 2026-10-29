#include "common.h"
#include "PR/synthInternals.h"

/* alSynAllocFX */
ALFxRef *func_80078AA0_main(ALSynth *s, s16 bus, ALSynConfig *c, ALHeap *hp) {
    func_80073484_main(&s->auxBus[bus].fx[0], c, hp);
    func_800762B4_main(&s->auxBus[bus].fx[0], AL_FILTER_SET_SOURCE, &s->auxBus[bus]);
    func_80075C60_main(s->mainBus, AL_FILTER_ADD_SOURCE, &s->auxBus[bus].fx[0]);

    return (ALFxRef)(&s->auxBus[bus].fx[0]);
}
