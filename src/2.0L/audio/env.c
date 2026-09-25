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

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/env", func_8007572C_main);
