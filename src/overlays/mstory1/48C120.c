#include "common.h"

typedef struct UnkSeEntry {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 stopSeNo;
    char unk_0C[0xC];
} UnkSeEntry; // sizeof 0x18

extern f32 D_800CB890_main;
extern f32 D_800D5210_main;

extern Vec D_80114A8C_mstory1;
extern Vec D_80114A98_mstory1;
extern Vec D_80114AA4_mstory1;

extern s32 D_80114AB0_mstory1;
extern s16 D_801158B2_mstory1;
extern u16 D_801158B8_mstory1;
extern s32 D_801158E4_mstory1;
extern UnkSeEntry D_801158FC_mstory1[];

void func_80105FF4_mstory1(void);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114C50_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80105C90_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80105D80_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80105E00_mstory1);

void func_80105EC0_mstory1(void) {
    func_8001C258_main(D_801158B2_mstory1, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    espDispOff(D_801158B8_mstory1);
}

void func_80105EF4_mstory1(void) {
    func_8001C258_main(D_801158B2_mstory1, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    espDispOn(D_801158B8_mstory1);
}

void func_80105F28_mstory1(void) {
    D_800CE17C_main[0] = D_80114A8C_mstory1.x;
    D_800CE17C_main[1] = D_80114A8C_mstory1.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = 35.0f;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCameraPosSetV(0, &D_80114A8C_mstory1, &D_80114A98_mstory1, &D_80114AA4_mstory1);
    Hu3DCamUpdateMtx(0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80105FA8_mstory1);

void func_80105FB8_mstory1(s32 arg0) {
    D_801158E4_mstory1 = arg0;
    D_80114AB0_mstory1 = 0;
    omAddPrcObj(func_80105FF4_mstory1, 0x1000, 0x800, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80105FF4_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106894_mstory1);

void func_801068A0_mstory1(void) {
}

void func_801068A8_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801068B0_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106984_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801069EC_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106A1C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106A40_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106A94_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106AC0_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106AFC_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106B14_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106B30_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106D64_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106D80_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106F94_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106FC0_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106FF0_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010701C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010704C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801071F4_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80107220_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010726C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80107318_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801074C0_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801077C4_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010806C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010809C_mstory1);

void func_801081D8_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801081E0_mstory1);

void func_801085F0_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114C6C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114C88_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CB0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CBC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CC8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CD4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CE0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CEC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CF8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D04_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D10_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D30_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D50_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D70_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D90_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D9C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114DA8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114DCC_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801085F8_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109014_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801090D8_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010910C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114DFC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E08_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E14_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E20_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E30_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E38_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E40_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E4C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109140_mstory1);

void func_80109470_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E64_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109478_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010980C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109888_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801099F8_mstory1);

void func_80109C20_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E7C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E94_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EA0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EAC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EB8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EC4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114ED0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EDC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EE8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F00_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F0C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109C28_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109DC0_mstory1);

void func_80109FD0_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F30_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109FD8_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010A424_mstory1);

void func_8010A608_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010A610_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010AA98_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010AC40_mstory1);

void func_8010B108_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010B110_mstory1);

void func_8010B300_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F48_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F54_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F6C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F78_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F84_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F90_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F9C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FA8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FB4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FC0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FCC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FD8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FE4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FF0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FFC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80115008_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010B308_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010B384_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010B3B8_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010B4E4_mstory1);

void func_8010B69C_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010B6A4_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010B9C0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80115038_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80115050_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_8011505C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010BB08_mstory1);

void func_8010BBEC_mstory1(s32 index) {
    if (D_801158FC_mstory1[index].unk_00 == 1) {
        D_801158FC_mstory1[index].unk_00 = 0;
        switch (index) {
            case 0:
            case 2:
                HuAudFXStop(D_801158FC_mstory1[index].stopSeNo);
                break;
            case 1:
            case 3:
            case 4:
            case 5:
                break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010BC68_mstory1);
