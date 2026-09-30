#include "common.h"

// Per-object state for this minigame. Lives in the `data` pointer (0x5C) of the
// omObjData for the players as well as for the boulder. func_800D6B70_minigame
// walks it every frame: it places the model using `size` scaled by sin/cos of
// `phase`, and dispatches the nine callback slots at 0x84.
typedef struct BoulderBallData {
    /* 0x00 */ char unk_00[0x3C];
    /* 0x3C */ f32 phase;
    /* 0x40 */ f32 size;
    /* 0x44 */ char unk_44[0x34];
    /* 0x78 */ s32 unk_78;
    /* 0x7C */ char unk_7C[0x30];
} BoulderBallData; // sizeof 0xAC

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_801059A0_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80105E74_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80105EA0_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_801060D0_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80106410_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80106B58_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80106C8C_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80106DAC_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_8010707C_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80107194_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80107298_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80107924_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80107A20_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80107B0C_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80107C08_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80108000_boulder_ball);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", D_80109818_boulder_ball);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", D_80109828_boulder_ball);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", D_80109838_boulder_ball);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", D_80109848_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_801083D8_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80108798_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80108A08_boulder_ball);

s32 func_80108CF4_boulder_ball(void) {
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80108CFC_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80108E5C_boulder_ball);

void func_801093B8_boulder_ball(omObjData *arg0) {
    BoulderBallData *data = OM_GET_DATA_PTR(arg0, BoulderBallData);

    data->size += 0.3f;
    data->unk_78++;
    if (35.0f < data->size) {
        data->size = 35.0f;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80109410_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_801095A0_boulder_ball);
