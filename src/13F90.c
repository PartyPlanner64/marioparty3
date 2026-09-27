#include "common.h"

INCLUDE_ASM("asm/nonmatchings/13F90", func_80013390_main);

void func_800138EC_main(s16 arg0, s32 arg1, s32 arg2) {
    HmfModelData_UnkBC_Struct *lightFlags = HmfModelData[arg0].unkBC;

    lightFlags->unk04 = arg2 | (lightFlags->unk04 & ~arg1);
}

s16 func_80013928_main(s16 arg0) {
    return HmfModelData[arg0].unkBC->unk04;
}

void func_80013954_main(s16 arg0, s16 arg1) {
    HmfModelData[arg0].unkBC->unk02 = arg1;
}

s16 func_80013980_main(s16 arg0) {
    return HmfModelData[arg0].unkBC->unk02;
}

INCLUDE_ASM("asm/nonmatchings/13F90", func_800139AC_main);

void func_80013D44_main(void) {
}

INCLUDE_ASM("asm/nonmatchings/13F90", func_80013D4C_main);

INCLUDE_ASM("asm/nonmatchings/13F90", func_80013FB4_main);
