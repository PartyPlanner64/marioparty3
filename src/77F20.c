#include "common.h"

INCLUDE_ASM("asm/nonmatchings/77F20", func_80077320_main);

INCLUDE_ASM("asm/nonmatchings/77F20", func_8007742C_main);

s32 func_80077520_main(ALCSeq *seq, s32 *pDeltaTicks) {
    s32 minTicks;
    u32 i;
    u32 lastDeltaTicks;

    lastDeltaTicks = seq->lastDeltaTicks;

    if (seq->validTracks == 0) {
        return 0;
    }

    minTicks = -1;

    for (i = 0; i < AL_MAX_CHANNELS; i++) {
        if ((seq->validTracks >> i) & 1) {
            if (seq->deltaFlag) {
                seq->evtDeltaTicks[i] -= lastDeltaTicks;
            }
            if (minTicks > seq->evtDeltaTicks[i]) {
                minTicks = seq->evtDeltaTicks[i];
            }
        }
    }

    seq->deltaFlag = 0;
    *pDeltaTicks = minTicks;

    return 1;
}

INCLUDE_ASM("asm/nonmatchings/77F20", func_800775A0_main);

f32 func_80077810_main(ALCSeq *seq, s32 ticks, u32 tempo) {
    return (f32)ticks * tempo / ((f32)seq->base->division * 1000000.0);
}

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

void func_80077C40_main(ALCSeq *seq, ALCSeqMarker *marker) {
    s32 i;

    marker->validTracks = seq->validTracks;
    marker->lastTicks = seq->lastTicks;
    marker->lastDeltaTicks = seq->lastDeltaTicks;

    for (i = 0; i < AL_MAX_CHANNELS; i++) {
        marker->curLoc[i] = seq->curLoc[i];
        marker->curBUPtr[i] = seq->curBUPtr[i];
        marker->curBULen[i] = seq->curBULen[i];
        marker->lastStatus[i] = seq->lastStatus[i];
        marker->evtDeltaTicks[i] = seq->evtDeltaTicks[i];
    }
}

INCLUDE_ASM("asm/nonmatchings/77F20", func_80077CB4_main);

INCLUDE_ASM("asm/nonmatchings/77F20", func_80077D6C_main);
