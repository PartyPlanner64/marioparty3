#include "common.h"

typedef struct Unk70C30_Tone {
    char unk_00[0xC];
    u8 unk_C;
    u8 unk_D;
} Unk70C30_Tone;

typedef struct Unk70C30_Instrument {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    char unk_03[9];
    s16 unk_0C;
} Unk70C30_Instrument;

typedef struct Unk70C30_Channel {
    Unk70C30_Instrument *unk_00;
    s16 unk_04;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08;
    u8 unk_09;
    char unk_0A[2];
    f32 unk_0C;
} Unk70C30_Channel;

typedef struct Unk70C30_Node {
    struct Unk70C30_Node *unk_00;
    char unk_04[0x10];
    struct Unk70C30_Node *unk_14;
    char unk_18[0x8];
    Unk70C30_Tone *unk_20;
    char unk_24[0xC];
    u8 unk_30;
    u8 unk_31;
    u8 unk_32;
    u8 unk_33;
    u8 unk_34;
    u8 unk_35;
    u8 unk_36;
    u8 unk_37;
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
    char unk_00[0x32];
    s16 unk_32;
    char unk_34[0x2C];
    Unk70C30_Channel *unk_60;
} D_800713F4_main_Struct;

void func_800711BC_main(D_80070030_main_Struct *arg0, f32 arg1);

INCLUDE_ASM("asm/nonmatchings/70C30", func_80070030_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_800701AC_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_80070660_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_8007071C_main);

void func_80070F20_main(D_80070030_main_Struct *arg0, ALEvent *arg1) {
    ALEvent evt;

    if (arg1->msg.tempo.status == AL_MIDI_Meta) {
        if (arg1->msg.tempo.type == AL_MIDI_META_TEMPO) {
            func_800711BC_main(arg0,
                               (arg1->msg.tempo.byte1 << 16) | (arg1->msg.tempo.byte2 << 8) |
                                   arg1->msg.tempo.byte3);
        }
    }
}

void func_80070F8C_main(D_80070030_main_Struct *arg0, void *arg1) {
    Unk70C30_Node *node = arg0->unk_64;
    Unk70C30_Node *prev = NULL;

    if (node != NULL) {
        do {
            if (&node->unk_04 == arg1) {
                if (prev != NULL) {
                    prev->unk_00 = node->unk_00;
                } else {
                    arg0->unk_64 = node->unk_00;
                }
                if (node == arg0->unk_68) {
                    arg0->unk_68 = prev;
                }
                node->unk_00 = arg0->unk_6C;
                arg0->unk_6C = node;
                return;
            }
            prev = node;
            node = node->unk_00;
        } while (node != NULL);
    }
}

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

Unk70C30_Node *func_80071240_main(D_80070030_main_Struct *arg0, u8 arg1, u8 arg2) {
    Unk70C30_Node *node;

    for (node = arg0->unk_64; node != NULL; node = node->unk_00) {
        if (node->unk_32 == arg1 && node->unk_31 == arg2 && node->unk_35 != 3 && node->unk_35 != 4) {
            return node;
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/70C30", func_80071294_main);

s32 func_80071368_main(Unk70C30_Node *arg0, D_800713F4_main_Struct *arg1) {
    s32 vol = arg0->unk_36 * arg0->unk_33 * arg0->unk_30;
    s32 gain = arg0->unk_20->unk_D * arg1->unk_32 * arg1->unk_60[arg0->unk_31].unk_09;
    return ((vol >> 6) * (gain >> 14) * 2) >> 16;
}

INCLUDE_ASM("asm/nonmatchings/70C30", func_800713D8_main);

s32 func_800713F4_main(D_80070030_main_Struct *arg0, D_800713F4_main_Struct *arg1) {
    s32 value = arg1->unk_60[arg0->unk_31].unk_07;
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

void func_80071548_main(D_800713F4_main_Struct *arg0, s32 arg1) {
    arg0->unk_60[arg1].unk_06 = 0;
    arg0->unk_60[arg1].unk_0A[0] = 0;
    arg0->unk_60[arg1].unk_07 = 0x40;
    arg0->unk_60[arg1].unk_09 = 0x7F;
    arg0->unk_60[arg1].unk_08 = 5;
    arg0->unk_60[arg1].unk_0A[1] = 0;
    arg0->unk_60[arg1].unk_04 = 0xC8;
    arg0->unk_60[arg1].unk_0C = 1.0f;
}

void func_800715C8_main(D_800713F4_main_Struct *arg0, Unk70C30_Instrument *arg1, s32 arg2) {
    arg0->unk_60[arg2].unk_00 = arg1;
    arg0->unk_60[arg2].unk_07 = arg1->unk_01;
    arg0->unk_60[arg2].unk_09 = arg1->unk_00;
    arg0->unk_60[arg2].unk_08 = arg1->unk_02;
    arg0->unk_60[arg2].unk_04 = arg1->unk_0C;
}

INCLUDE_ASM("asm/nonmatchings/70C30", func_8007161C_main);

INCLUDE_ASM("asm/nonmatchings/70C30", func_8007170C_main);
