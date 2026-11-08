#include "common.h"

extern s32 D_8010FAF0_chancetime;
extern s32 D_8010FE74_chancetime;
extern s8 D_8010FE78_chancetime;
extern void (*D_801100C4_chancetime)(omObjData *);

void func_80106BEC_chancetime(omObjData *object);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_80106320_chancetime);

void func_80106760_chancetime(void) {
}

void func_80106768_chancetime(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_80106770_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_8010684C_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_80106A2C_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_80106B18_chancetime);

s32 func_80106BB8_chancetime(void) {
    return D_8010FE74_chancetime;
}

void func_80106BC4_chancetime(s8 arg0) {
    D_8010FE78_chancetime = arg0;
    D_801100C4_chancetime = func_80106BEC_chancetime;
}

s32 func_80106BE0_chancetime(void) {
    return D_8010FAF0_chancetime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_80106BEC_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_80106F10_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_8010705C_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_801071A8_chancetime);
