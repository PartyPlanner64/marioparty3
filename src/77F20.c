#include "common.h"

INCLUDE_ASM("asm/nonmatchings/77F20", func_80077320_main);

INCLUDE_ASM("asm/nonmatchings/77F20", func_8007742C_main);

INCLUDE_ASM("asm/nonmatchings/77F20", func_80077520_main);

INCLUDE_ASM("asm/nonmatchings/77F20", func_800775A0_main);

INCLUDE_ASM("asm/nonmatchings/77F20", func_80077810_main);

INCLUDE_ASM("asm/nonmatchings/77F20", func_8007788C_main);

s32 alCSeqGetTicks(ALCSeq *seq) {
    return seq->lastTicks;
}

INCLUDE_ASM("asm/nonmatchings/77F20", func_80077934_main);

void func_80077BCC_main(ALCSeq *seq, ALCSeqMarker *marker) {
    s32 i;

    seq->validTracks = marker->validTracks;
    seq->lastTicks = marker->lastTicks;
    seq->lastDeltaTicks = marker->lastDeltaTicks;

    for (i = 0; i < AL_MAX_CHANNELS; i++) {
        seq->curLoc[i] = marker->curLoc[i];
        seq->curBUPtr[i] = marker->curBUPtr[i];
        seq->curBULen[i] = marker->curBULen[i];
        seq->lastStatus[i] = marker->lastStatus[i];
        seq->evtDeltaTicks[i] = marker->evtDeltaTicks[i];
    }
}

INCLUDE_ASM("asm/nonmatchings/77F20", func_80077C40_main);

INCLUDE_ASM("asm/nonmatchings/77F20", func_80077CB4_main);

INCLUDE_ASM("asm/nonmatchings/77F20", func_80077D6C_main);
