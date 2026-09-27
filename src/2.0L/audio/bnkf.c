#include "common.h"

void alSeqFileNew(ALSeqFile *f, u8 *base) {
    int i;

    for (i = 0; i < f->seqCount; i++) {
        f->seqArray[i].offset = (u8 *)((u32)f->seqArray[i].offset + (u32)base);
    }
}

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/bnkf", alBnkfNew);

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/bnkf", _bnkfPatchBank);

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/bnkf", _bnkfPatchInst);

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/bnkf", _bnkfPatchSound);

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/bnkf", _bnkfPatchWaveTable);
