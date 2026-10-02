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

void _bnkfPatchWaveTable(ALWaveTable *table, u32 start, u32 end) {
    if (table->flags == 0) {
        table->flags = 1;
        table->base += end;

        if (table->type == AL_ADPCM_WAVE) {
            table->waveInfo.adpcmWave.book = (ALADPCMBook *)((u8 *)table->waveInfo.adpcmWave.book + start);
            if (table->waveInfo.adpcmWave.loop != NULL) {
                table->waveInfo.adpcmWave.loop = (ALADPCMloop *)((u8 *)table->waveInfo.adpcmWave.loop + start);
            }
        } else if (table->type == AL_RAW16_WAVE) {
            if (table->waveInfo.rawWave.loop != NULL) {
                table->waveInfo.rawWave.loop = (ALRawLoop *)((u8 *)table->waveInfo.rawWave.loop + start);
            }
        }
    }
}
