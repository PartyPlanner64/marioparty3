#include "common.h"

// Per-object work block, reached via ObjData->data
typedef struct ChipShotChallengeWork {
    /* 0x00 */ char pad_00[0x38];
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ char pad_3C[0x20];
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ f32 unk_60;
    /* 0x64 */ f32 unk_64;
} ChipShotChallengeWork; // Size 0x68

extern s32 D_8010AAA0_chip_shot_challenge;
extern f32 D_8010A834_chip_shot_challenge;

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801059A0_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80105DE0_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80105E8C_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80105EB8_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_8010646C_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80106B84_chip_shot_challenge);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", D_8010A9D8_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80107048_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801071A8_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80107238_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801073D4_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80107520_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80107960_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80107BB0_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80107E94_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_8010802C_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80108108_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80108274_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801085C0_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80108638_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801086B4_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80108730_chip_shot_challenge);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", D_8010AA00_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801087AC_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801091E8_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801094D8_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80109AD0_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80109B24_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80109DE0_chip_shot_challenge);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", D_8010AA2C_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80109EF0_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_8010A04C_chip_shot_challenge);

void func_8010A3DC_chip_shot_challenge(omObjData *object, Vec *arg1) {
    ChipShotChallengeWork *work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);

    if (D_8010AAA0_chip_shot_challenge == 1 && work->unk_38 == 1000.0f) {
        work->unk_5C = arg1->x * D_8010A834_chip_shot_challenge;
        work->unk_60 = arg1->y;
        work->unk_64 = arg1->z * D_8010A834_chip_shot_challenge;
    } else {
        work->unk_5C = 0.0f;
        work->unk_60 = 0.0f;
        work->unk_64 = 0.0f;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_8010A454_chip_shot_challenge);
