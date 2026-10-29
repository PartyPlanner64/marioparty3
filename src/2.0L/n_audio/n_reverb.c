#include "common.h"

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_reverb", n_alFxPull);

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_reverb", n_alFxParamHdl);

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_reverb", _n_loadOutputBuffer);

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_reverb", _n_loadBuffer);

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_reverb", __n_saveBuffer);

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_reverb", __n_filterBuffer);
