#include "common.h"

typedef struct UnkSeEntry {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 stopSeNo;
    char unk_0C[0xC];
} UnkSeEntry; // sizeof 0x18

typedef struct UnkMstory1Obj {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk_08;
} UnkMstory1Obj; // sizeof 0xC

typedef struct MstoryPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ u16 flags;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec *points;
    /* 0x0C */ f32 (*intervals)[2];
} MstoryPath; // sizeof 0x10

extern Vec D_80115250_mstory1;
extern Vec D_8011525C_mstory1;
extern Vec D_80115310_mstory1;
extern Vec D_8011531C_mstory1;
extern Vec D_80115448_mstory1;
extern Vec D_80115460_mstory1;
extern UnkMstory1Obj D_80115A30_mstory1;
extern UnkMstory1Obj D_80115AC0_mstory1;
extern UnkSeEntry D_80115A3C_mstory1[8];
extern UnkMstory1Obj D_80115A48_mstory1;

void func_80106B14_mstory1(omObjData *obj, const Vec *pos, s32 frames);
void func_8010704C_mstory1(omObjData *obj, Vec *pos, s32 frames);
void func_8010CAD8_mstory1(omObjData *obj);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010BDC0_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010C0C4_mstory1);

void func_8010C96C_mstory1(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010C99C_mstory1);

void func_8010CAD8_mstory1(omObjData *obj) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010CAE0_mstory1);

void func_8010CEF0_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801150C0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801150CC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801150D8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801150E4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801150F0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801150FC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115108_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115114_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115120_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115140_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115160_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115180_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801151A0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801151AC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801151B8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801151DC_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010CEF8_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010D90C_mstory1);

void func_8010D9D0_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80115250_mstory1, 10);
    D_80115A30_mstory1.func = func_8010CAD8_mstory1;
}

void func_8010DA04_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_8011525C_mstory1, 10);
    D_80115A30_mstory1.func = func_8010CAD8_mstory1;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_8011520C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115218_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115224_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115230_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115240_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115248_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115250_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_8011525C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010DA38_mstory1);

void func_8010DD68_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115274_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010DD70_mstory1);

void func_8010E0B0_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_8011531C_mstory1, 10);
    func_80106B14_mstory1(obj, &D_80115310_mstory1, 50);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_80115A48_mstory1.func = func_8010CAD8_mstory1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010E12C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010E29C_mstory1);

void func_8010E4C4_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_8011528C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801152A4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801152B0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801152BC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801152C8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801152D4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801152E0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801152EC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801152F8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115310_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_8011531C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010E4CC_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010E5FC_mstory1);

void func_8010E80C_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010E814_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010EC30_mstory1);

void func_8010EE14_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010EE1C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010F244_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010F3EC_mstory1);

void func_8010F848_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010F850_mstory1);

void func_8010FA40_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115340_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115358_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_8011537C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115388_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115394_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801153AC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801153B8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801153C4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801153D0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801153DC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_801153F4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115400_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_8011540C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115418_mstory1);

const Vec D_80115430_mstory1 = { 700.0f, 0.0f, 150.0f };
const Vec D_8011543C_mstory1 = { 216.66666f, 0.0f, 150.0f };

void func_8010FA48_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80115448_mstory1, 10);
    func_80106B14_mstory1(obj, &D_80115430_mstory1, 50);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_80115AC0_mstory1.func = func_8010CAD8_mstory1;
}

void func_8010FAC4_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80115460_mstory1, 20);
    D_80115AC0_mstory1.func = func_8010CAD8_mstory1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010FAF8_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010FC24_mstory1);

void func_8010FDDC_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010FDE4_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_80110100_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115448_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115460_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115470_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_80110248_mstory1);

void func_8011032C_mstory1(s32 index) {
    if (D_80115A3C_mstory1[index].unk_00 == 1) {
        D_80115A3C_mstory1[index].unk_00 = 0;
        switch (index) {
            case 0:
            case 2:
                HuAudFXStop(D_80115A3C_mstory1[index].stopSeNo);
                break;
            case 1:
            case 3:
            case 4:
            case 5:
                break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_801103A8_mstory1);
