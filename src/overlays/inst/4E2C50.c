#include "common.h"

extern s32 D_8010D540_inst;
extern void (*D_8010DDD4_inst)(omObjData *);

void func_8010A000_inst(omObjData *);
void func_8010C8D0_inst(void);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_80109A90_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_80109E94_inst);

void func_80109F50_inst(omObjData *object) {
    D_8010D540_inst++;
    if (D_8010D540_inst >= 110) {
        func_8001C5B4_main(object->model[0], object->motion[1]);
        func_8001C814_main(object->model[0], 2, 0);
        func_8001C258_main(object->model[0], 4, 0);
        func_8001C258_main(object->model[1], 4, 0);
        HuAudFXPlay(0x25B);
        D_8010DDD4_inst = func_8010A000_inst;
        D_8010D540_inst = 0;
        func_8010C8D0_inst();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010A000_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010A0E8_inst);

void func_8010A1BC_inst(void) {
}
