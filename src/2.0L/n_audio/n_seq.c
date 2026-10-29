#include "common.h"
#include "PR/n_libaudio.h"

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_seq", n_alSeqNextEvent);

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_seq", n_alSeqNewMarker);

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_seq", func_80071A5C_main);

u32 func_80071A70_main(ALSeq *seq) {
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
