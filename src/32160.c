#include "common.h"
#include "mallocblock.h"

typedef struct {
    char unk00[0x1C];
    u8 unk1C;
    u8 unk1D;
    s16 unk1E;
    s16 unk20;
    void *unk24;
    void *unk28;
} HmfPalData;

INCLUDE_ASM("asm/nonmatchings/32160", func_80031560_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80031630_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_8003186C_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80031A08_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80031A44_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80031A60_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80031B30_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80031DF4_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80032038_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80032104_main);

void func_80032194_main(HmfPalData *pal) {
    pal->unk20 = 0;
    pal->unk24 = NULL;
    func_80019C00_main(pal->unk28);
}

INCLUDE_ASM("asm/nonmatchings/32160", func_800321B8_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_800322AC_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_8003235C_main);

INCLUDE_ASM("asm/nonmatchings/32160", HmfAnimCreate);

INCLUDE_ASM("asm/nonmatchings/32160", func_80032694_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80032950_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_800329B4_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80032FC0_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80032FF8_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_8003302C_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_800330D4_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80033128_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_800332D4_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80033354_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_800333B0_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80033430_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80033450_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80033510_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_800335BC_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80033694_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80033910_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80033970_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_800339D0_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80033D0C_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80033F8C_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80033FEC_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80034048_main);

INCLUDE_RODATA("asm/nonmatchings/32160", D_800A6D44_main);

INCLUDE_RODATA("asm/nonmatchings/32160", D_800A6D4C_main);

INCLUDE_RODATA("asm/nonmatchings/32160", D_800A6D50_main);
