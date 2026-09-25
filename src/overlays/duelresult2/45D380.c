#include "common.h"
#include "../ovl_81_name/ovl_81.h"

extern UnkBoard4 *D_80108DB4_duelresult2[2];
extern UnkBoard4 *D_80108DBC_duelresult2;
extern UnkBoard4 *D_80108C30_duelresult2;

void func_80108B38_duelresult2(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_801059A0_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80105A8C_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80105B98_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80105C68_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80105CB0_duelresult2);

void func_80106848_duelresult2(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_800F4584_name_81(D_80108DB4_duelresult2[i]);
    }

    func_800F4584_name_81(D_80108DBC_duelresult2);

    if (D_80108C30_duelresult2 != NULL) {
        func_800F4584_name_81(D_80108C30_duelresult2);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_801068BC_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80106974_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80106A2C_duelresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult2/45D380", D_80108CC8_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80106F7C_duelresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult2/45D380", D_80108D08_duelresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult2/45D380", D_80108D28_duelresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult2/45D380", D_80108D48_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80107454_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80107FEC_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_8010809C_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80108240_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_801083FC_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_801084F4_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80108B38_duelresult2);

void func_80108B7C_duelresult2(omObjData *arg0) {
    if (D_800D530C_main != 0) {
        arg0->func = func_80108B38_duelresult2;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80108BA0_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80108BCC_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80108BF8_duelresult2);

void func_80108C28_duelresult2(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult2/45D380", D_80108D80_duelresult2);
