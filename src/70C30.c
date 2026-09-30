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

typedef struct Unk70C30_Node {
    struct Unk70C30_Node *unk_00;
    char unk_04[0x10];
    struct Unk70C30_Node *unk_14;
    char unk_18[0x19];
    u8 unk_31;
    u8 unk_32;
    u8 unk_33;
} Unk70C30_Node;

typedef struct D_80070030_main_Struct {
    char unk_00[0x18];
    ALSeq *unk_18;
    s32 unk_1C;
    Unk70C30_Tone *unk_20;
    s32 unk_24;
    char unk_28[0x9];
    u8 unk_31;
    char unk_32[0x32];
    Unk70C30_Node *unk_64;
    Unk70C30_Node *unk_68;
    Unk70C30_Node *unk_6C;
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

Unk70C30_Node *func_800711F0_main(D_80070030_main_Struct *arg0, u8 arg1, u8 arg2, u8 arg3) {
    Unk70C30_Node *node = arg0->unk_6C;
    if (node != NULL) {
        arg0->unk_6C = node->unk_00;
        node->unk_00 = NULL;
        if (arg0->unk_64 == NULL) {
            arg0->unk_64 = node;
        } else {
            arg0->unk_68->unk_00 = node;
        }
        arg0->unk_68 = node;
        node->unk_31 = arg3;
        node->unk_32 = arg1;
        node->unk_33 = arg2;
        node->unk_14 = node;
    }
    return node;
}

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
