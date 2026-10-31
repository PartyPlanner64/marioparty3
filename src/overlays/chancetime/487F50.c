#include "common.h"

extern s8 D_8010FB80_chancetime;
extern s8 D_8010FB81_chancetime;
extern s32 D_8010FC10_chancetime;
extern s32 D_8010FC14_chancetime;
extern s32 D_8010FC1C_chancetime;
extern s16 D_8010FE94_chancetime[3];
extern u16 D_8010FE9A_chancetime;
extern s32 D_8010FEC4_chancetime;
extern s8 D_8010FEC8_chancetime;
extern s8 D_8010FEC9_chancetime;
extern s32 D_80110008_chancetime;
extern void (*D_80110084_chancetime)();
extern omObjData *D_801100C8_chancetime;
extern void (*D_801100CC_chancetime)(void);

void func_8010C610_chancetime(void);
void func_8010DFA4_chancetime(void);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010BF80_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010C5F4_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010C610_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010C870_chancetime);

void func_8010C98C_chancetime(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010C994_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010CF78_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FC98_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCC0_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCC8_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCD0_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCD8_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCE8_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCF8_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010D320_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010D6A4_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010D92C_chancetime);

void func_8010DA24_chancetime(void) {
    s32 i;

    D_8010FB80_chancetime = 1;
    D_8010FB81_chancetime = 0;
    for (i = 0; i < 3; i++) {
        espDispOn(D_8010FE94_chancetime[i]);
    }
    espDispOn(D_8010FE9A_chancetime);
    D_801100CC_chancetime = func_8010C610_chancetime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010DAA4_chancetime);

void func_8010DAB0_chancetime(void) {
    omObjData *obj = D_801100C8_chancetime;
    s8 i;

    for (i = 0; i < 3; i++) {
        func_8001C258_main(obj->model[i + 1], 4, 4);
    }
}

void func_8010DB1C_chancetime(s8 arg0) {
    omObjData *obj = D_801100C8_chancetime;

    espDispOff(D_8010FE94_chancetime[arg0]);
    func_8001C258_main(obj->model[arg0 + 1], 4, 0);
}

void func_8010DB78_chancetime(void) {
    D_8010FEC4_chancetime = 0;
    D_8010FEC8_chancetime = 1;
    D_8010FEC9_chancetime = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010DB98_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010DBB0_chancetime);

void func_8010DF68_chancetime(void) {
}

void func_8010DF70_chancetime(void) {
}

void func_8010DF78_chancetime(s32 arg0) {
    D_8010FC14_chancetime = 0;
    D_80110008_chancetime = (s8)arg0;
    D_80110084_chancetime = func_8010DFA4_chancetime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010DFA4_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010E1E0_chancetime);

void func_8010E210_chancetime(void) {
    D_8010FC1C_chancetime++;
    if (D_8010FC1C_chancetime < 10) {
        return;
    }
    D_8010FC14_chancetime = 1;
    D_8010FC1C_chancetime = 0;
    D_80110084_chancetime = func_8010DF70_chancetime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010E258_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010E264_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010E280_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010E4C4_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010E4D0_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010F1DC_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010F1F8_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010F420_chancetime);

void func_8010F42C_chancetime(void) {
    D_8010FC10_chancetime = 1;
    D_80110084_chancetime = func_8010DF70_chancetime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010F44C_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010F984_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD0C_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD20_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD38_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD3C_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD40_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD5C_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD68_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD8C_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FDB0_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FDD4_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FDF8_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FE1C_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FE3C_chancetime);
