#include "common.h"

INCLUDE_ASM("asm/nonmatchings/6C9F0", func_8006BDF0_main);

INCLUDE_ASM("asm/nonmatchings/6C9F0", func_8006BF60_main);

INCLUDE_ASM("asm/nonmatchings/6C9F0", func_8006C408_main);

INCLUDE_ASM("asm/nonmatchings/6C9F0", func_8006C4C8_main);

INCLUDE_ASM("asm/nonmatchings/6C9F0", func_8006CD00_main);

INCLUDE_ASM("asm/nonmatchings/6C9F0", func_8006CE90_main);

void func_8006CF20_main(ALCSPlayer *seqp, f32 scale) {
    if (seqp->target != NULL) {
        seqp->uspt = (s32)(scale * seqp->target->qnpt);
    } else {
        seqp->uspt = 0x1E8;
    }
}

INCLUDE_ASM("asm/nonmatchings/6C9F0", func_8006CF54_main);
