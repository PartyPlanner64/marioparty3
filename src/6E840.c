#include "common.h"
#include "PR/sndp.h"

void func_8006DC40_main(ALSndId id, u8 priority) {
    ALSndPlayer *sndp = D_800A2884_main->sndp;
    ALSoundState *sState = sndp->sndState;

    sState[id].priority = priority;
}
