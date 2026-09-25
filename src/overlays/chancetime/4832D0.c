#include "common.h"

extern s32 D_8010FB00_chancetime;
extern s32 D_8010FB04_chancetime;
extern void (*D_801100D8_chancetime)(omObjData *);

void func_80107B18_chancetime(omObjData *object);
void func_80108414_chancetime(omObjData *object);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80107300_chancetime);

void func_80107A80_chancetime(void) {
}

void func_80107A88_chancetime(void) {
}

void func_80107A90_chancetime(void) {
}

void func_80107A98_chancetime(omObjData *object) {
    func_8001C5B4_main(object->model[1], object->motion[2]);
    func_8001C814_main(object->model[1], 2, 0);
    func_8001C5B4_main(object->model[3], object->motion[2]);
    func_8001C814_main(object->model[3], 2, 0);
    D_801100D8_chancetime = func_80107B18_chancetime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80107B18_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80107C84_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80107D60_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80107E40_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80107F58_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_801080EC_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010827C_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80108414_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80108578_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_801086DC_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_801086F0_chancetime);

void func_80108704_chancetime(void) {
    D_8010FB00_chancetime = 1;
    D_8010FB04_chancetime = 0;
    D_801100D8_chancetime = func_80108414_chancetime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010872C_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80108738_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80108A88_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80108B50_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80108C08_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80108CDC_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80108EDC_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_801094CC_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010963C_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80109A00_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80109B70_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80109F34_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010A0A4_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010A468_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010A5D8_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010A99C_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010AA90_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010B030_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010B124_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010B6F4_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010B7A0_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010B7EC_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010B818_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010B834_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010BA68_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010BC10_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010BC3C_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010BC88_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010BD40_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010BF3C_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010BF48_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/4832D0", D_8010FC80_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/4832D0", D_8010FC8C_chancetime);
