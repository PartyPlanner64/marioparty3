#include "common.h"
#include "PR/n_libaudio.h"

s32 n_alCSPGetChlProgram(N_ALCSPlayer *seqp, u8 chan) {
    ALBank *bank = seqp->bank;
    ALChanState chanState = seqp->chanState[chan];
    s32 i;

    for (i = 0; i < bank->instCount; i++) {
        if (bank->instArray[i] == chanState.instrument) {
            return i;
        }
    }

    return -1;
}
