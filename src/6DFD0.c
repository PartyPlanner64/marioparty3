#include "common.h"

INCLUDE_ASM("asm/nonmatchings/6DFD0", func_8006D3D0_main);

INCLUDE_ASM("asm/nonmatchings/6DFD0", func_8006D4E8_main);

INCLUDE_ASM("asm/nonmatchings/6DFD0", func_8006D578_main);

INCLUDE_ASM("asm/nonmatchings/6DFD0", func_8006D9B0_main);

s32 func_8006DA58_main(s32 value, f32 divisor) {
    f64 ratio = value / divisor;
    return ratio > 2147483647.0 ? 0x7FFFFFFF : (s32)ratio;
}
