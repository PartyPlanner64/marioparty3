#include "common.h"

typedef struct D_80070030_main_Struct {
    char unk_00[0x18];
    ALSeq *unk_18;
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
} D_80070030_main_Struct;

INCLUDE_ASM("asm/nonmatchings/70C30", func_80070030_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_800701AC_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_80070660_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_8007071C_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_80070F20_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_80070F8C_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_80070FF0_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_8007110C_main);

void func_800711BC_main(D_80070030_main_Struct *arg0, f32 arg1) {
    if (arg0->unk_18 != NULL) {
        arg0->unk_24 = (s32)(arg1 * arg0->unk_18->qnpt);
    } else {
        arg0->unk_24 = 0x1E8;
    }
}

INCLUDE_ASM("asm/nonmatchings/70C30", func_800711F0_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_80071240_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_80071294_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_80071368_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_800713D8_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_800713F4_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_80071438_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_800714E4_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_80071548_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_800715C8_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_8007161C_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_8007170C_main);
