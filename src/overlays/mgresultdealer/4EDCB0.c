#include "common.h"

extern s8 D_80109911_mgresultdealer;
extern s8 D_80109930_mgresultdealer;
extern s8 D_80109931_mgresultdealer;
extern s32 D_80109934_mgresultdealer;
extern s8 D_80109938_mgresultdealer;
extern s16 D_8010993A_mgresultdealer;
extern s8 D_80109940_mgresultdealer;
extern s8 D_80109941_mgresultdealer;
extern s32 D_80109944_mgresultdealer;
extern s32 D_80109950_mgresultdealer;
extern s32 D_8010A240_mgresultdealer;
extern s32 D_8010A244_mgresultdealer;
extern omObjFunc D_8010A260_mgresultdealer;

void func_80108544_mgresultdealer(void);
void func_80108560_mgresultdealer(u8);
void func_80109100_mgresultdealer(void);
void func_80109710_mgresultdealer(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_801074A0_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80107888_mgresultdealer);

void func_80107E3C_mgresultdealer(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80107E44_mgresultdealer);

s8 func_80108034_mgresultdealer(void) {
    return D_80109911_mgresultdealer;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80108040_mgresultdealer);

void func_80108194_mgresultdealer(void) {
    f32 step;

    if (D_80109930_mgresultdealer) {
        step = 255.0f / 30;
        func_80108560_mgresultdealer(D_80109934_mgresultdealer * step);
        D_80109934_mgresultdealer++;
        if (D_80109934_mgresultdealer >= 30) {
            func_80108560_mgresultdealer(255);
            D_80109931_mgresultdealer = 1;
            D_80109930_mgresultdealer = 0;
        }
    }
}

void func_80108258_mgresultdealer(void) {
}

void func_80108260_mgresultdealer(void) {
    D_80109930_mgresultdealer = 1;
    D_80109931_mgresultdealer = 0;
    D_80109934_mgresultdealer = 0;
    func_80108544_mgresultdealer();
    func_80108560_mgresultdealer(0);
}

s8 func_8010829C_mgresultdealer(void) {
    return D_80109931_mgresultdealer;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_801082A8_mgresultdealer);

void func_80108544_mgresultdealer(void) {
    D_80109938_mgresultdealer = 1;
}

void func_80108554_mgresultdealer(void) {
    D_80109938_mgresultdealer = 0;
}

void func_80108560_mgresultdealer(u8 arg0) {
    D_8010993A_mgresultdealer = arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80108570_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80108AEC_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80108BD4_mgresultdealer);

void func_80109044_mgresultdealer(void) {
    if (D_80109940_mgresultdealer == 0) {
        return;
    }

    D_80109950_mgresultdealer++;

    if (D_80109950_mgresultdealer < 0xF) {
        return;
    }

    D_80109940_mgresultdealer = 0;
    D_80109941_mgresultdealer = 1;
    D_80109950_mgresultdealer = 0;
    D_8010A244_mgresultdealer = 0;
    D_8010A260_mgresultdealer = func_80109710_mgresultdealer;
}

void func_801090AC_mgresultdealer(void) {
}

void func_801090B4_mgresultdealer(void) {
    D_80109940_mgresultdealer = 1;
    D_80109941_mgresultdealer = 0;
    D_80109944_mgresultdealer = 0;
    func_80109100_mgresultdealer();
}

s32 func_801090E8_mgresultdealer(void) {
    return D_8010A240_mgresultdealer;
}

s32 func_801090F4_mgresultdealer(void) {
    return D_8010A244_mgresultdealer;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80109100_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_801093A0_mgresultdealer);

s8 func_80109478_mgresultdealer(void) {
    return D_80109941_mgresultdealer;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80109484_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EDCB0", func_80109710_mgresultdealer);
