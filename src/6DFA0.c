#include "common.h"
#include "PR/sndp.h"

s32 func_8006D3A0_main(void) {
    ALSndPlayer *sndp = D_800A2884_main->sndp;
    s32 id = sndp->target;
    ALSoundState *sState = sndp->sndState;

    return sState[id].state;
}
