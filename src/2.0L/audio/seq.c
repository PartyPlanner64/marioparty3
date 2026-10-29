#include "common.h"

#define IFF_FILE_HDR 0x4D546864  /* 'MThd' */
#define IFF_TRACK_HDR 0x4D54726B /* 'MTrk' */

static u8 read8(ALSeq *seq);
static s16 read16(ALSeq *seq);
static s32 read32(ALSeq *seq);
static s32 readVarLen(ALSeq *seq);

void alSeqNew(ALSeq *seq, u8 *ptr, s32 len) {
    /*
     * load the seqence pointed to by ptr
     */
    seq->base = ptr;
    seq->len = len;
    seq->lastStatus = 0;
    seq->lastTicks = 0;
    seq->curPtr = ptr;

    if (read32(seq) != IFF_FILE_HDR) {
        return;
    }

    read32(seq); /* skip the length field */

    if (read16(seq) != 0) {
        return;
    }

    if (read16(seq) != 1) {
        return;
    }

    seq->division = read16(seq);
    if (seq->division & 0x8000) {
        return;
    }

    seq->qnpt = 1.0 / (f32)seq->division;

    if (read32(seq) != IFF_TRACK_HDR) {
        return;
    }

    read32(seq); /* skip the length field */

    seq->trackStart = seq->curPtr;
}

void alSeqNextEvent(ALSeq *seq, ALEvent *event) {
    u8 status;
    s32 deltaTicks;

    deltaTicks = readVarLen(seq); /* read the delta time */
    seq->lastTicks += deltaTicks;
    status = read8(seq);

    if (status == AL_MIDI_Meta) {
        u8 type = read8(seq);

        if (type == AL_MIDI_META_TEMPO) {
            event->type = AL_TEMPO_EVT;
            event->msg.tempo.ticks = deltaTicks;
            event->msg.tempo.status = status;
            event->msg.tempo.type = type;
            event->msg.tempo.len = read8(seq);
            event->msg.tempo.byte1 = read8(seq);
            event->msg.tempo.byte2 = read8(seq);
            event->msg.tempo.byte3 = read8(seq);
        } else if (type == AL_MIDI_META_EOT) {
            event->type = AL_SEQ_END_EVT;
            event->msg.end.ticks = deltaTicks;
            event->msg.end.status = status;
            event->msg.end.type = type;
            event->msg.end.len = read8(seq);
        }

        seq->lastStatus = 0;
    } else {
        event->type = AL_SEQ_MIDI_EVT;
        event->msg.midi.ticks = deltaTicks;
        if (status & 0x80) {
            event->msg.midi.status = status;
            event->msg.midi.byte1 = read8(seq);
            seq->lastStatus = status;
        } else {
            /* running status */
            event->msg.midi.status = seq->lastStatus;
            event->msg.midi.byte1 = status;
        }

        if (((event->msg.midi.status & 0xF0) != AL_MIDI_ProgramChange) &&
            ((event->msg.midi.status & 0xF0) != AL_MIDI_ChannelPressure)) {
            event->msg.midi.byte2 = read8(seq);
        } else {
            event->msg.midi.byte2 = 0;
        }
    }
}

char __alSeqNextDelta(ALSeq *seq, s32 *pDeltaTicks) {
    u8 *savedPtr;

    if (seq->curPtr >= seq->base + seq->len) {
        return 0;
    }

    savedPtr = seq->curPtr;
    *pDeltaTicks = readVarLen(seq);
    seq->curPtr = savedPtr;

    return 1;
}

f32 alSeqTicksToSec(ALSeq *seq, s32 ticks, u32 usecs) {
    return (f32)ticks * usecs / ((f32)seq->division * 1000000.0);
}

u32 alSeqSecToTicks(ALSeq *seq, f32 secs, u32 ticks) {
    return (u32)(secs * 1000000.0 * seq->division / ticks);
}

void alSeqNewMarker(ALSeq *seq, ALSeqMarker *m, u32 ticks) {
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

            alSeqNextEvent(seq, &evt);

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

void alSeqSetLoc(ALSeq *seq, ALSeqMarker *m) {
    seq->curPtr = m->curPtr;
    seq->lastStatus = m->lastStatus;
    seq->lastTicks = m->lastTicks;
}

void alSeqGetLoc(ALSeq *seq, ALSeqMarker *m) {
    m->curPtr = seq->curPtr;
    m->lastStatus = seq->lastStatus;
    m->lastTicks = seq->lastTicks;
}

static u8 read8(ALSeq *seq) {
    return *seq->curPtr++;
}

static s16 read16(ALSeq *seq) {
    s16 value = *(seq->curPtr++) << 8;

    value |= *(seq->curPtr++);

    return value;
}

static s32 read32(ALSeq *seq) {
    s32 value = *(seq->curPtr++) << 24;

    value |= *(seq->curPtr++) << 16;
    value |= *(seq->curPtr++) << 8;
    value |= *(seq->curPtr++);

    return value;
}

static s32 readVarLen(ALSeq *seq) {
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
