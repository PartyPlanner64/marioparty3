#include "common.h"

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/cseq", alCSeqNew);

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/cseq", alCSeqNextEvent);

s32 __alCSeqNextDelta(ALCSeq *seq, s32 *pDeltaTicks) {
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

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/cseq", __alCSeqGetTrackEvent);

f32 alCSeqTicksToSec(ALCSeq *seq, s32 ticks, u32 tempo) {
    return (f32)ticks * tempo / ((f32)seq->base->division * 1000000.0);
}

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/cseq", alCSeqSecToTicks);

s32 alCSeqGetTicks(ALCSeq *seq) {
    return seq->lastTicks;
}

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/cseq", alCSeqNewMarker);

void alCSeqSetLoc(ALCSeq *seq, ALCSeqMarker *marker) {
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

void alCSeqGetLoc(ALCSeq *seq, ALCSeqMarker *marker) {
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

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/cseq", __getTrackByte);

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/cseq", __readVarLen);
