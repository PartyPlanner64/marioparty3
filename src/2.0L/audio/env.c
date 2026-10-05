#include "common.h"

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/env", func_80074B00_main);

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/env", func_80075000_main);

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/env", func_800750D4_main);

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/env", func_800753A8_main);

f64 func_80075488_main(f64 arg0, s32 arg1) {
    if (arg1 != 0) {
        arg0 *= (f64)(1 << arg1);
    }
    return arg0;
}

INCLUDE_RODATA("asm/nonmatchings/2.0L/audio/env", D_800A8360_main);

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/env", func_800754AC_main);

/* Scales `value` by the Q32 rate given as its signed high half and unsigned
 * low half, once for every eight samples. The factor is squared once per bit
 * of the sample count, so only the low bits of the count are applied. */
f32 func_8007572C_main(f32 value, s32 count, s16 rateHi, u16 rateLo) {
    f32 step;
    f32 ratio;
    s32 i;

    count >>= 3;
    if (count == 0) {
        return value;
    }

    step = ((f32)(rateHi << 16) + (f32)rateLo) / 65536.0f;
    ratio = 1.0f;

    for (i = 0; i < 0x20; i++) {
        if (count & 1) {
            ratio *= step;
        }
        count >>= 1;
        if (count == 0) {
            return value * ratio;
        }
        step *= step;
    }

    return value * ratio;
}
