#include "common.h"

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_sndplayer", n_alSndpNew);

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_sndplayer", _n_sndpVoiceHandler);

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_sndplayer", _n_handleEvent);

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_sndplayer", _n_removeEvents);

s32 _n_DivS32ByF32(s32 value, f32 divisor) {
    f64 ratio = value / divisor;
    return ratio > 2147483647.0 ? 0x7FFFFFFF : (s32)ratio;
}
