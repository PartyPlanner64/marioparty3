#include "common.h"

#define IFF_FILE_HDR 0x4D546864  /* 'MThd' */
#define IFF_TRACK_HDR 0x4D54726B /* 'MTrk' */

void func_80076C98_main(ALSeq *seq, ALEvent *event);
u8 func_800770B4_main(ALSeq *seq);
s16 func_800770C8_main(ALSeq *seq);
s32 func_800770F8_main(ALSeq *seq);
s32 func_80077148_main(ALSeq *seq);

/* alSeqNew */
void func_80076BB0_main(ALSeq *seq, u8 *ptr, s32 len) {
    /*
     * load the seqence pointed to by ptr
     */
    seq->base = ptr;
    seq->len = len;
    seq->lastStatus = 0;
    seq->lastTicks = 0;
    seq->curPtr = ptr;

    if (func_800770F8_main(seq) != IFF_FILE_HDR) {
        return;
    }

    func_800770F8_main(seq); /* skip the length field */

    if (func_800770C8_main(seq) != 0) {
        return;
    }

    if (func_800770C8_main(seq) != 1) {
        return;
    }

    seq->division = func_800770C8_main(seq);
    if (seq->division & 0x8000) {
        return;
    }

    seq->qnpt = 1.0 / (f32)seq->division;

    if (func_800770F8_main(seq) != IFF_TRACK_HDR) {
        return;
    }

    func_800770F8_main(seq); /* skip the length field */

    seq->trackStart = seq->curPtr;
}

/* alSeqNextEvent */
void func_80076C98_main(ALSeq *seq, ALEvent *event) {
    u8 status;
    s32 deltaTicks;

    deltaTicks = func_80077148_main(seq); /* read the delta time */
    seq->lastTicks += deltaTicks;
    status = func_800770B4_main(seq);

    if (status == AL_MIDI_Meta) {
        u8 type = func_800770B4_main(seq);

        if (type == AL_MIDI_META_TEMPO) {
            event->type = AL_TEMPO_EVT;
            event->msg.tempo.ticks = deltaTicks;
            event->msg.tempo.status = status;
            event->msg.tempo.type = type;
            event->msg.tempo.len = func_800770B4_main(seq);
            event->msg.tempo.byte1 = func_800770B4_main(seq);
            event->msg.tempo.byte2 = func_800770B4_main(seq);
            event->msg.tempo.byte3 = func_800770B4_main(seq);
        } else if (type == AL_MIDI_META_EOT) {
            event->type = AL_SEQ_END_EVT;
            event->msg.end.ticks = deltaTicks;
            event->msg.end.status = status;
            event->msg.end.type = type;
            event->msg.end.len = func_800770B4_main(seq);
        }

        seq->lastStatus = 0;
    } else {
        event->type = AL_SEQ_MIDI_EVT;
        event->msg.midi.ticks = deltaTicks;
        if (status & 0x80) {
            event->msg.midi.status = status;
            event->msg.midi.byte1 = func_800770B4_main(seq);
            seq->lastStatus = status;
        } else {
            /* running status */
            event->msg.midi.status = seq->lastStatus;
            event->msg.midi.byte1 = status;
        }

        if (((event->msg.midi.status & 0xF0) != AL_MIDI_ProgramChange) &&
            ((event->msg.midi.status & 0xF0) != AL_MIDI_ChannelPressure)) {
            event->msg.midi.byte2 = func_800770B4_main(seq);
        } else {
            event->msg.midi.byte2 = 0;
        }
    }
}

/* __alSeqNextDelta */
s32 func_80076E00_main(ALSeq *seq, s32 *pDeltaTicks) {
    u8 *savedPtr;

    if (seq->curPtr >= seq->base + seq->len) {
        return 0;
    }

    savedPtr = seq->curPtr;
    *pDeltaTicks = func_80077148_main(seq);
    seq->curPtr = savedPtr;

    return 1;
}

/* alSeqTicksToSec */
f32 func_80076E68_main(ALSeq *seq, s32 ticks, u32 usecs) {
    return (f32)ticks * usecs / ((f32)seq->division * 1000000.0);
}

/* alSeqSecToTicks */
u32 func_80076ED0_main(ALSeq *seq, f32 secs, u32 ticks) {
    return (u32)(secs * 1000000.0 * seq->division / ticks);
}

/* alSeqNewMarker */
void func_80076F60_main(ALSeq *seq, ALSeqMarker *m, u32 ticks) {
    ALEvent evt;
    u8 *savePtr, *lastPtr;
    s32 saveTicks, lastTicks;
    s16 saveStatus, lastStatus;

    /* does not check that ticks is within bounds */

    if (ticks == 0) { /* common case */
        m->curPtr = seq->trackStart;
        m->lastStatus = 0;
        m->lastTicks = 0;
        m->curTicks = 0;
        return;
    } else {
        savePtr = seq->curPtr;
        saveStatus = seq->lastStatus;
        saveTicks = seq->lastTicks;

        seq->curPtr = seq->trackStart;
        seq->lastStatus = 0;
        seq->lastTicks = 0;

        do {
            lastPtr = seq->curPtr;
            lastStatus = seq->lastStatus;
            lastTicks = seq->lastTicks;

            func_80076C98_main(seq, &evt);

            if (evt.type == AL_SEQ_END_EVT) {
                lastPtr = seq->curPtr;
                lastStatus = seq->lastStatus;
                lastTicks = seq->lastTicks;
                break;
            }
        } while (seq->lastTicks < ticks);

        m->curPtr = lastPtr;
        m->lastStatus = lastStatus;
        m->lastTicks = lastTicks;
        m->curTicks = seq->lastTicks; /* Used by test loop condition. */

        seq->curPtr = savePtr;
        seq->lastStatus = saveStatus;
        seq->lastTicks = saveTicks;
    }
}

s32 alSeqGetTicks(ALSeq *seq) {
    return seq->lastTicks;
}

/* alSeqSetLoc */
void func_8007707C_main(ALSeq *seq, ALSeqMarker *m) {
    seq->curPtr = m->curPtr;
    seq->lastStatus = m->lastStatus;
    seq->lastTicks = m->lastTicks;
}

/* alSeqGetLoc */
void func_80077098_main(ALSeq *seq, ALSeqMarker *m) {
    m->curPtr = seq->curPtr;
    m->lastStatus = seq->lastStatus;
    m->lastTicks = seq->lastTicks;
}

/* read8 */
u8 func_800770B4_main(ALSeq *seq) {
    return *seq->curPtr++;
}

/* read16 */
s16 func_800770C8_main(ALSeq *seq) {
    s16 value = *(seq->curPtr++) << 8;

    value |= *(seq->curPtr++);

    return value;
}

/* read32 */
s32 func_800770F8_main(ALSeq *seq) {
    s32 value = *(seq->curPtr++) << 24;

    value |= *(seq->curPtr++) << 16;
    value |= *(seq->curPtr++) << 8;
    value |= *(seq->curPtr++);

    return value;
}

/* readVarLen */
s32 func_80077148_main(ALSeq *seq) {
    s32 value = *(seq->curPtr++);
    s32 nextByte;

    if (value & 0x80) {
        value &= 0x7F;

        do {
            nextByte = *(seq->curPtr++);
            value = (value << 7) + (nextByte & 0x7F);
        } while (nextByte & 0x80);
    }

    return value;
}
