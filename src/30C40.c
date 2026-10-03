#include "common.h"
#include "mallocblock.h"

extern s32 *D_800D59F8_main;

void func_80030040_main(void) {
    s16 i;
    D_800D59F8_main = HuMemAlloc(0x140);
    for (i = 0; i < 0x10; i++) {
        D_800D59F8_main[i * 5 + 2] = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/30C40", func_800300A4_main);

void func_80030178_main(s32 arg0) {
    D_800D59F8_main[arg0 * 5 + 2] = 0;
}

void func_80030198_main(void) {
    s16 i;

    for (i = 0; i < 0x10; i++) {
        if (D_800D59F8_main[i * 5 + 2] != 0) {
            func_80030178_main(i);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/30C40", func_80030208_main);

INCLUDE_ASM("asm/nonmatchings/30C40", func_800303C8_main);

INCLUDE_ASM("asm/nonmatchings/30C40", func_80030414_main);

INCLUDE_ASM("asm/nonmatchings/30C40", func_800308C0_main);

INCLUDE_ASM("asm/nonmatchings/30C40", func_80031324_main);
