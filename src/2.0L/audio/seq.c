#include "common.h"

s32 func_80077148_main(ALSeq *seq);

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/seq", func_80076BB0_main);

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/seq", func_80076C98_main);

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

f32 func_80076E68_main(ALSeq *seq, s32 ticks, u32 usecs) {
    return (f32)ticks * usecs / ((f32)seq->division * 1000000.0);
}

u32 func_80076ED0_main(ALSeq *seq, f32 secs, u32 ticks) {
    return (u32)(secs * 1000000.0 * seq->division / ticks);
}

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/seq", func_80076F60_main);

s32 alSeqGetTicks(ALSeq *seq) {
    return seq->lastTicks;
}

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/seq", func_8007707C_main);

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/seq", func_80077098_main);

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/seq", func_800770B4_main);

s16 func_800770C8_main(ALSeq *seq) {
    s16 value = *(seq->curPtr++) << 8;

    value |= *(seq->curPtr++);

    return value;
}

s32 func_800770F8_main(ALSeq *seq) {
    s32 value = *(seq->curPtr++) << 24;

    value |= *(seq->curPtr++) << 16;
    value |= *(seq->curPtr++) << 8;
    value |= *(seq->curPtr++);

    return value;
}

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
