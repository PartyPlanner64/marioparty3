#include "common.h"

// Partial definition of the 0x7918 byte work struct allocated for D_8010A498's object
typedef struct {
    /* 0x00 */ s32 flags;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08[0x11];
    /* 0x4C */ f32 unk_4C;
} WinnersWheelData;

extern omObjData *D_8010A498_winners_wheel;
extern omObjData *D_8010A4A8_winners_wheel;
extern omObjData *D_8010A4C0_winners_wheel;

extern u8 D_8010A464_winners_wheel;

extern s16 D_8010A488_winners_wheel;
extern s16 D_8010A48A_winners_wheel;

void func_8010677C_winners_wheel(void);
void func_80107820_winners_wheel(void);
void func_80108458_winners_wheel(void);
void func_801089F4_winners_wheel(void);
void func_8010907C_winners_wheel(void);
void func_80109130_winners_wheel(void);
void func_80109C1C_winners_wheel(void);
void func_80109FAC_winners_wheel(void);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_801059A0_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80105AB0_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80105BA8_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80105C5C_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80105E78_winners_wheel);

void func_80105F18_winners_wheel(void) {
    WinnersWheelData *wheel = (WinnersWheelData *)D_8010A498_winners_wheel->data;
    func_8001C814_main(*D_8010A498_winners_wheel->model, 4, 4);
    wheel->flags |= 2;
}

void func_80105F60_winners_wheel(void) {
    WinnersWheelData *work = (WinnersWheelData *)D_8010A498_winners_wheel->data;
    work->flags |= 4;
    HuAudFXPlay(0x4CA);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80105F94_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80105FB0_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80105FE4_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_801063B0_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80106514_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80106718_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80106734_winners_wheel);

void func_80106750_winners_wheel(void) {
    omAddPrcObj(func_8010677C_winners_wheel, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_8010677C_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80106910_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80106D2C_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80106EB0_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80106F54_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_8010701C_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_801070CC_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_801075D4_winners_wheel);

void func_801077F4_winners_wheel(void) {
    omAddPrcObj(func_80107820_winners_wheel, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80107820_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_801078D8_winners_wheel);

void func_80107B04_winners_wheel(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80107B0C_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80107BE0_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80107CB4_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80107D50_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80107F4C_winners_wheel);

void func_8010842C_winners_wheel(void) {
    omAddPrcObj(func_80108458_winners_wheel, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80108458_winners_wheel);

void func_801089C8_winners_wheel(void) {
    omAddPrcObj(func_801089F4_winners_wheel, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_801089F4_winners_wheel);

void func_80108E80_winners_wheel(void) {
    WinnersWheelData *wheel = (WinnersWheelData *)D_8010A4C0_winners_wheel->data;

    wheel->flags |= 3;
    wheel->unk_04 = 340.0f;
    wheel->unk_4C = 340.0f;
    func_8001C258_main(*D_8010A4C0_winners_wheel->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    omSetRot(D_8010A4C0_winners_wheel, 0, 0, wheel->unk_04);
    D_8010A48A_winners_wheel = HuAudFXPlay(0x4C7);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80108F04_winners_wheel);

void func_80109050_winners_wheel(void) {
    omAddPrcObj(func_8010907C_winners_wheel, 0x50, 0, 0);
}

void func_8010907C_winners_wheel(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        func_8001C258_main(*D_8010A4C0_winners_wheel->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        HuPrcSleep(10);
        func_8001C258_main(*D_8010A4C0_winners_wheel->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        HuPrcSleep(10);
    }
    D_8010A464_winners_wheel = 4;
    omDelPrcObj(NULL);
}

void func_80109104_winners_wheel(void) {
    omAddPrcObj(func_80109130_winners_wheel, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109130_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109388_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109454_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_801095E4_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_8010985C_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109A18_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109B90_winners_wheel);

void func_80109BAC_winners_wheel(void) {
    D_8010A488_winners_wheel = func_8000CED8_main(0xB0004, 0x6A9);
    ((WinnersWheelData *)D_8010A4A8_winners_wheel->data)->flags |= 2;
}

void func_80109BF0_winners_wheel(void) {
    omAddPrcObj(func_80109C1C_winners_wheel, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109C1C_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109D44_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109E90_winners_wheel);

void func_80109F80_winners_wheel(void) {
    omAddPrcObj(func_80109FAC_winners_wheel, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109FAC_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_8010A190_winners_wheel);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", D_8010A2E8_winners_wheel);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", D_8010A308_winners_wheel);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", D_8010A328_winners_wheel);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", D_8010A3A8_winners_wheel);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", D_8010A3C8_winners_wheel);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", D_8010A3E8_winners_wheel);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", D_8010A408_winners_wheel);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", D_8010A420_winners_wheel);
