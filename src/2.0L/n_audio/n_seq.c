#include "common.h"
#include "PR/n_libaudio.h"

static u8 read8(ALSeq *seq);
static s32 readVarLen(ALSeq *seq);

void n_alSeqNextEvent(ALSeq *seq, N_ALEvent *event) {
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

void n_alSeqNewMarker(ALSeq *seq, ALSeqMarker *m, u32 ticks) {
    N_ALEvent evt;
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

            n_alSeqNextEvent(seq, &evt);

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

/* non-aligned byte reading routines */
static u8 read8(ALSeq *seq) {
    return *seq->curPtr++;
}

static s32 readVarLen(ALSeq *seq) {
    u32 value = *seq->curPtr++;
    u8 byte;

    if (value & 0x80) {
        value &= 0x7F;
        do {
            byte = *seq->curPtr++;
            value = (value << 7) + (byte & 0x7F);
        } while (byte & 0x80);
    }
    return value;
}
