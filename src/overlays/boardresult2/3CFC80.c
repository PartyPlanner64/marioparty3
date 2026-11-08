#include "common.h"
#include "../ovl_81_name/ovl_81.h"

extern UnkBoard4 *D_801099A4_boardresult2;
extern UnkBoard4 *D_801099A8_boardresult2;
extern UnkBoard4 *D_801099B0_boardresult2[4];
extern UnkBoard4 *D_801099C0_boardresult2;
extern UnkBoard4 *D_801099C4_boardresult2;
extern s32 D_801099F8_boardresult2[16];

void func_80108E1C_boardresult2(void);
void func_801096AC_boardresult2(omObjData *);
void func_801096F0_boardresult2(omObjData *);
void func_80109714_boardresult2(void);
void func_8010976C_boardresult2(void);
void func_80109740_boardresult2(void);
void func_8010979C_boardresult2(void);

void func_801059A0_boardresult2(void) {
    u32 i;

    omInitObjMan(0x50, 0x50);
    func_8010976C_boardresult2();
    func_80109714_boardresult2();
    HuWinInit();
    omAddPrcObj(func_80108E1C_boardresult2, 0x300, 0x4000, 0);
    omAddObj(0x1000, 0, 0, -1, func_801096F0_boardresult2);

    for (i = 0; i < 16; i++) {
        do {
            D_801099F8_boardresult2[i] = func_800EFE20_name_81(7.0f);
        } while (i != 0 && D_801099F8_boardresult2[i - 1] == D_801099F8_boardresult2[i]);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80105A8C_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80105B98_boardresult2);

s16 func_80105C68_boardresult2(s32 dataNum) {
    void *data = DataRead(dataNum);
    s16 anim = func_800329B4_main(data);

    DataClose(data);
    return anim;
}

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80105CB0_boardresult2);

void func_80106924_boardresult2(void) {
    s32 i;

    func_800F4584_name_81(D_801099A4_boardresult2);
    func_800F4584_name_81(D_801099A8_boardresult2);

    for (i = 0; i < 4; i++) {
        func_800F4584_name_81(D_801099B0_boardresult2[i]);
    }

    func_800F4584_name_81(D_801099C0_boardresult2);
    func_800F4584_name_81(D_801099C4_boardresult2);
}

void func_801069A4_boardresult2(void) {
    s32 i;
    s32 j;

    for (j = 0; j < 4; j++) {
        HuSprDispOff(D_801099A4_boardresult2->unk_0A, j);
    }
    HuSprDispOff(D_801099A8_boardresult2->unk_0A, 0);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            HuSprDispOff(D_801099B0_boardresult2[i]->unk_0A, j);
        }
    }

    HuSprDispOff(D_801099C0_boardresult2->unk_0A, 0);
    HuSprDispOff(D_801099C4_boardresult2->unk_0A, 0);
}

void func_80106A9C_boardresult2(void) {
    s32 i;
    s32 j;

    for (j = 0; j < 4; j++) {
        HuSprDispOn(D_801099A4_boardresult2->unk_0A, j);
    }
    HuSprDispOn(D_801099A8_boardresult2->unk_0A, 0);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            HuSprDispOn(D_801099B0_boardresult2[i]->unk_0A, j);
        }
    }

    HuSprDispOn(D_801099C0_boardresult2->unk_0A, 0);
    HuSprDispOn(D_801099C4_boardresult2->unk_0A, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80106B94_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_80109864_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_801074B4_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_80109880_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_801098B4_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_801098C4_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_801098DC_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_801098FC_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_8010991C_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_8010992C_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80107964_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80108548_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_801085F8_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_8010879C_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80108958_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80108A48_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80108C70_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80108E1C_boardresult2);

void func_801096AC_boardresult2(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_8010979C_boardresult2();
        func_80109740_boardresult2();
        HuWinAllKill();
        omOvlReturnEx(1);
    }
}

void func_801096F0_boardresult2(omObjData *arg0) {
    if (D_800D530C_main != 0) {
        arg0->func = func_801096AC_boardresult2;
    }
}

void func_80109714_boardresult2(void) {
    func_800D7EB8_name_81();
    func_800F3F4C_name_81();
    func_800F4300_name_81();
}

void func_80109740_boardresult2(void) {
    func_800F4030_name_81();
    func_800D7F0C_name_81();
    func_800F4314_name_81();
}

void func_8010976C_boardresult2(void) {
    Hu3DCamInit(2);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
}

void func_8010979C_boardresult2(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_8010996C_boardresult2);
