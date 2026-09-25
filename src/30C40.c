#include "common.h"

extern s32 *D_800D59F8_main;

INCLUDE_ASM("asm/nonmatchings/30C40", func_80030040_main);

INCLUDE_ASM("asm/nonmatchings/30C40", func_800300A4_main);

void func_80030178_main(s32 arg0) {
    D_800D59F8_main[arg0 * 5 + 2] = 0;
}

INCLUDE_ASM("asm/nonmatchings/30C40", func_80030198_main);

INCLUDE_ASM("asm/nonmatchings/30C40", func_80030208_main);

INCLUDE_ASM("asm/nonmatchings/30C40", func_800303C8_main);

INCLUDE_ASM("asm/nonmatchings/30C40", func_80030414_main);

INCLUDE_ASM("asm/nonmatchings/30C40", func_800308C0_main);

INCLUDE_ASM("asm/nonmatchings/30C40", func_80031324_main);
