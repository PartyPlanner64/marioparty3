#include "common.h"

typedef struct Unk70C30_Tone {
    char unk_00[0xC];
    u8 unk_C;
} Unk70C30_Tone;

typedef struct Unk70C30_Channel {
    char unk_00[0x7];
    u8 unk_7;
    char unk_8[0x8];
} Unk70C30_Channel;

typedef struct D_80070030_main_Struct {
    char unk_00[0x18];
    ALSeq *unk_18;
    s32 unk_1C;
    Unk70C30_Tone *unk_20;
    s32 unk_24;
    char unk_28[0x9];
    u8 unk_31;
} D_80070030_main_Struct;

typedef struct D_800713F4_main_Struct {
    char unk_00[0x60];
    Unk70C30_Channel *unk_60;
} D_800713F4_main_Struct;

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

s32 func_800713F4_main(D_80070030_main_Struct *arg0, D_800713F4_main_Struct *arg1) {
    s32 value = arg1->unk_60[arg0->unk_31].unk_7;
    s32 offset = arg0->unk_20->unk_C - 0x40;
    value += offset;
    if (value < 0) {
        value = 0;
    }
    if (value >= 0x80) {
        value = 0x7F;
    }
    return value & 0xFF;
}

INCLUDE_ASM("asm/nonmatchings/70C30", func_80071438_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_800714E4_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_80071548_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_800715C8_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_8007161C_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_8007170C_main);
