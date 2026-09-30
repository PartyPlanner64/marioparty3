#include "common.h"

INCLUDE_ASM("asm/nonmatchings/527E0", func_80051BE0_main);

INCLUDE_ASM("asm/nonmatchings/527E0", func_80051D20_main);

INCLUDE_ASM("asm/nonmatchings/527E0", func_80051DB4_main);

INCLUDE_ASM("asm/nonmatchings/527E0", func_8005222C_main);

s32 func_800522D4_main(s32 value, f32 divisor) {
    f64 ratio = value / divisor;
    return ratio > 2147483647.0 ? 0x7FFFFFFF : (s32)ratio;
}
