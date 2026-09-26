#include "common.h"

typedef struct D_800CBB60_main_Struct {
    /* 0x00 */ s16 modelId;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 nodeIdx;
    /* 0x06 */ s16 pointIdx;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ u16 flags;
    /* 0x12 */ u8 unk_12;
    /* 0x13 */ u8 colorR;
    /* 0x14 */ u8 colorG;
    /* 0x15 */ u8 colorB;
    /* 0x16 */ u8 colorStart[4];
    /* 0x1A */ u8 colorEnd[4];
    /* 0x1E */ char unk_1E[2];
    /* 0x20 */ u8 *unk_20;
} D_800CBB60_main_Struct;

extern D_800CBB60_main_Struct *D_800CBB60_main;

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800142A0_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800143F0_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", HmfSprModelCreate);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80014618_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800146DC_main);

void func_80014714_main(s16 arg0, s16 arg1) {
    D_800CBB60_main[arg0].nodeIdx = arg1;
}

void func_8001473C_main(s16 arg0, s16 arg1) {
    D_800CBB60_main[arg0].pointIdx = arg1;
    D_800CBB60_main[arg0].nodeIdx = 0;
    D_800CBB60_main[arg0].unk_08 = 0;
}

u16 func_8001476C_main(s16 arg0) {
    return D_800CBB60_main[arg0].nodeIdx;
}

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80014794_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800147FC_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80014850_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800148A8_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800149D0_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80014A3C_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80016638_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800166D0_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80016784_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800168A8_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800169E0_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80016B00_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80016C2C_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80016FB4_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017128_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017320_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017358_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_8001766C_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017790_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017954_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017A84_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017AD8_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017B20_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017B6C_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017BB8_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017C10_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017CD0_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017D24_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018044_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800183A0_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018544_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800185A4_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_8001866C_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018978_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018ACC_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018D68_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018DD8_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018E50_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018E74_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018F18_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6A98_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AA4_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AB0_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6ABC_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AC8_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AD4_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AE0_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AEC_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AF8_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B04_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B10_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B1C_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B28_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B34_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B40_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B4C_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B58_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B64_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B70_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B7C_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B88_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B94_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6BA0_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6BAC_main);
