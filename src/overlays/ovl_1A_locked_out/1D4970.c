#include "common.h"

extern u32 D_8010A1E8_locked_out;

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_801059A0_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80105B38_locked_out);

void func_80105C34_locked_out(HuMtx4F mtx, f32 x, f32 y, f32 z, f32 *dst) {
    dst[0] = ((x * mtx[0][0]) + (y * mtx[1][0])) + (z * mtx[2][0]);
    dst[1] = ((x * mtx[0][1]) + (y * mtx[1][1])) + (z * mtx[2][1]);
    dst[2] = ((x * mtx[0][2]) + (y * mtx[1][2])) + (z * mtx[2][2]);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80105CB4_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80105EA4_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80105F74_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80106040_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80106134_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80106424_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_801064E0_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80106FBC_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_8010713C_locked_out);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", D_8010A298_locked_out);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", D_8010A2A0_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_801071D8_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80107844_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80107ABC_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_801089F8_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80108A90_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_801090FC_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109110_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109264_locked_out);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", D_8010A468_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109444_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109858_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109CDC_locked_out);

s32 func_80109D70_locked_out(void) {
    D_8010A1E8_locked_out = (D_8010A1E8_locked_out + (rand8() & 0xFF)) * 0x41C64E6D + 0x3039;
    return D_8010A1E8_locked_out >> 16;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109DBC_locked_out);

f32 func_80109E34_locked_out(Vec *arg0, Vec *arg1) {
    return sqrtf(((arg0->x - arg1->x) * (arg0->x - arg1->x)) +
                 ((arg0->z - arg1->z) * (arg0->z - arg1->z)));
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109E88_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109FAC_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109FF4_locked_out);

HuSprite_Unk84_Unk00_Struct *func_8010A0BC_locked_out(s16 groupId, s16 member) {
    return &func_80055194_main(groupId)->unk00[member];
}
