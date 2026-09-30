#include "common.h"

typedef struct Unk723E0_Stream {
    char unk_00[0x4];
    u8 *unk_04;
    u8 *unk_08;
    s32 unk_0C;
    char unk_10[0xA];
    u16 unk_1A;
} Unk723E0_Stream;

INCLUDE_ASM("asm/nonmatchings/723E0", func_800717E0_main);

INCLUDE_ASM("asm/nonmatchings/723E0", func_80071948_main);

INCLUDE_ASM("asm/nonmatchings/723E0", func_80071A5C_main);

u32 func_80071A70_main(Unk723E0_Stream *arg0) {
    u32 value = *arg0->unk_08++;
    u8 byte;

    if (value & 0x80) {
        value &= 0x7F;
        do {
            byte = *arg0->unk_08++;
            value = (value << 7) + (byte & 0x7F);
        } while (byte & 0x80);
    }
    return value;
}

INCLUDE_ASM("asm/nonmatchings/723E0", func_80071AC0_main);
