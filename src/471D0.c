#include "common.h"

typedef union LightObjWork {
    u32 words[4];
    s16 halfwords[8];
} LightObjWork;

extern omObjData *D_800A1660_main;
extern s8 D_800B23B0_main;

extern void func_8004DEC8_main(s16);

s32 func_800465D0_main(void) {
    return D_800B23B0_main;
}

INCLUDE_ASM("asm/nonmatchings/471D0", func_800465DC_main);

INCLUDE_ASM("asm/nonmatchings/471D0", func_800465E8_main);

INCLUDE_ASM("asm/nonmatchings/471D0", func_800465F4_main);

INCLUDE_ASM("asm/nonmatchings/471D0", func_80046600_main);

void func_800466D8_main(void) {
    omObjData *lightObj = D_800A1660_main;
    LightObjWork *work;

    if (lightObj != NULL) {
        work = OM_GET_WORK_PTR(lightObj, LightObjWork);
        func_8004DEC8_main(work->halfwords[0]);
        func_8004DEC8_main(work->halfwords[4]);
        omDelObj(D_800A1660_main);
        D_800A1660_main = NULL;
    }
}

INCLUDE_ASM("asm/nonmatchings/471D0", func_80046728_main);
