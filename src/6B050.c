#include "common.h"

INCLUDE_ASM("asm/nonmatchings/6B050", func_8006A450_main);

INCLUDE_ASM("asm/nonmatchings/6B050", func_8006A9C8_main);

INCLUDE_ASM("asm/nonmatchings/6B050", func_8006AA6C_main);

INCLUDE_ASM("asm/nonmatchings/6B050", func_8006AC8C_main);

s16 func_8006ADCC_main(s16 ivol, s32 samples, s16 ratem, u16 ratel) {
    s32 inc;

    /* Rate values are actually rate^8 */
    samples >>= 3;
    if (samples == 0) {
        return ivol;
    }

    inc = (ratel * samples) >> 16;
    inc += ratem * samples;
    return ivol + inc;
}
