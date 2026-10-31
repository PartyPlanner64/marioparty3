#include "common.h"

extern omObjData *D_8010B4B0_curtain_call;
extern omObjData *D_8010BA5C_curtain_call;
extern omObjData *D_8010BB64_curtain_call;
extern Process *D_8010CF34_curtain_call;
extern s8 D_8010CEC1_curtain_call;

void func_801062EC_curtain_call(void);
void func_80106500_curtain_call(omObjData *);
void func_80108F28_curtain_call(omObjData *);
void func_801092F0_curtain_call(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_801059A0_curtain_call);

f32 func_801059BC_curtain_call(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80105A3C_curtain_call);

void func_80105B04_curtain_call(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

s32 func_80105B7C_curtain_call(s32 arg0) {
    return rand8() % arg0;
}

void func_80105BD0_curtain_call(omObjData *arg0, u16 arg1, s16 arg2) {
    if (arg1 < 0xA) {
        func_8001C5B4_main(arg0->model[0], arg0->motion[arg1]);
        func_8001C814_main(arg0->model[0], arg2, arg2);
    }
}

void func_80105C3C_curtain_call(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s32 arg4) {
    if (arg1 < 0xA) {
        Hu3DMotionShiftSet(arg0->model[0], HmfModelData[arg0->motion[arg1]].unk02, arg2, arg3, arg4);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80105CB8_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80105D14_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_801062EC_curtain_call);

void func_80106408_curtain_call(void) {
    D_800D6A58_main = 1;
    HuWinInit();
    D_8010CF34_curtain_call = omAddPrcObj(func_801062EC_curtain_call, 0x3F00, 0x800, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010644C_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80106494_curtain_call);

void func_801064A0_curtain_call(omObjData *arg0) {
    switch (D_8010CEC1_curtain_call) {
        case 3:
            func_8001C258_main(arg0->model[2], 4, 4);
            break;
        case 5:
            func_8001C258_main(arg0->model[2], 4, 0);
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80106500_curtain_call);

void func_80106688_curtain_call(void) {
    D_8010B4B0_curtain_call = omAddObj(0x1F4, 4, 2, -1, func_80106500_curtain_call);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_801066C4_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B32C_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B338_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B344_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B350_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B35C_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B368_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B374_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B380_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_801067A8_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80106988_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80106AB4_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80106B78_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80106C18_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80107560_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80107680_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80107D20_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_801084A0_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80108670_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_801089FC_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80108E64_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80108EF8_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80108F28_curtain_call);

void func_801090FC_curtain_call(void) {
    D_8010BA5C_curtain_call = omAddObj(0x258, 3, 2, -1, func_80108F28_curtain_call);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80109138_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_801092F0_curtain_call);

void func_801093C4_curtain_call(void) {
    D_8010BB64_curtain_call = omAddObj(0x384, 1, 1, -1, func_801092F0_curtain_call);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80109400_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010954C_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010982C_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80109920_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80109AD0_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010A734_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010A7D8_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010A7FC_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010A8E8_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010A948_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010AD68_curtain_call);

void func_8010AE00_curtain_call(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010AE08_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010AF78_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B4A0_curtain_call);
