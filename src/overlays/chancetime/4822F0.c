#include "common.h"

typedef struct ChanceTimeObjState {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
} ChanceTimeObjState;

extern s32 D_8010FAF0_chancetime;
extern s32 D_8010FE70_chancetime;
extern s32 D_8010FE74_chancetime;
extern s8 D_8010FE78_chancetime;
extern ChanceTimeObjState D_801100C0_chancetime;

void func_80106770_chancetime(omObjData *object);
void func_80106BEC_chancetime(omObjData *object);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_80106320_chancetime);

void func_80106760_chancetime(void) {
}

void func_80106768_chancetime(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_80106770_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_8010684C_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_80106A2C_chancetime);

void func_80106B18_chancetime(void) {
    omObjData *obj = D_801100C0_chancetime.obj;

    D_8010FE70_chancetime = 1;
    D_8010FE74_chancetime = 0;
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    D_801100C0_chancetime.func = func_80106770_chancetime;
}

s32 func_80106BB8_chancetime(void) {
    return D_8010FE74_chancetime;
}

void func_80106BC4_chancetime(s8 arg0) {
    D_8010FE78_chancetime = arg0;
    D_801100C0_chancetime.func = func_80106BEC_chancetime;
}

s32 func_80106BE0_chancetime(void) {
    return D_8010FAF0_chancetime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_80106BEC_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_80106F10_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_8010705C_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_801071A8_chancetime);
