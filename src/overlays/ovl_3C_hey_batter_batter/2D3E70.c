#include "common.h"

void func_80106C24_hey_batter_batter(omObjData *object);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_801059A0_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_801059BC_hey_batter_batter);

void func_80105A4C_hey_batter_batter(void) {
    HmfLightMaxSet(3);
    HmfLightDirSet(1, -10.0f, -10.0f, 150.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(2, -82.0f, 255.0f, -60.0f);
    HmfLightColorSet(2, 0xFF, 0xFF, 0xFF);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80105AB8_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80105C44_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80105CE8_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80105DE0_hey_batter_batter);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", D_80109DA0_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80106048_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_801062E0_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80106744_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80106928_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80106C24_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80106C6C_hey_batter_batter);

void func_80106CBC_hey_batter_batter(omObjData *object) {
    if (D_800D530C_main == 1) {
        object->func = func_80106C24_hey_batter_batter;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80106CE4_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80106FA8_hey_batter_batter);

void func_801070D8_hey_batter_batter(omObjData *object) {
    object->model[0] = func_8000B108_main(0x5D0001, 0x2A9);
    object->model[1] = func_8000B108_main(0x5D0002, 0x2A9);
    Hu3DModelPosSet(object->model[1], 0.0f, 0.0f, -1000.0f);
    object->func = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80107144_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80107464_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_801079D0_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80107C48_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80108B48_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80108D90_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_8010951C_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80109630_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_801098DC_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80109A78_hey_batter_batter);

s16 func_80109B24_hey_batter_batter(s32 arg0) {
    s16 temp = func_8000B13C_main(arg0);

    if (temp < 0) {
        temp = -1;
    }
    return temp;
}
