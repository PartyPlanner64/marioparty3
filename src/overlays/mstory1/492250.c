#include "common.h"

typedef struct UnkStoryObj {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} UnkStoryObj; // sizeof 0x18

typedef struct MstoryPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ u16 flags;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec *points;
    /* 0x0C */ f32 (*intervals)[2];
} MstoryPath; // sizeof 0x10

extern s32 D_80114B40_mstory1;
extern Vec D_80115250_mstory1;
extern Vec D_8011525C_mstory1;
extern Vec D_80115310_mstory1;
extern Vec D_8011531C_mstory1;
extern Vec D_80115448_mstory1;
extern Vec D_80115460_mstory1;
extern const Vec D_801150FC_mstory1;
extern UnkStoryObj D_80115A30_mstory1[8];
extern Vec D_80115B2C_mstory1;
extern s16 D_80115B50_mstory1;
extern s16 D_80115B66_mstory1;
extern s16 D_80115B68_mstory1;
extern Vec D_80115B44_mstory1;
extern const Vec D_80115114_mstory1;
extern s16 D_80115B52_mstory1;
extern const s32 D_80115470_mstory1[];
extern Vec D_80115B20_mstory1;
extern const Vec D_801150F0_mstory1;
extern Vec D_80115B38_mstory1;
extern const Vec D_80115108_mstory1;

void func_80106B14_mstory1(omObjData *obj, const Vec *pos, s32 frames);
s32 func_80106AFC_mstory1(s32 character);
void func_8010704C_mstory1(omObjData *obj, Vec *pos, s32 frames);
void func_801068B0_mstory1(s16 model, s16 animSlot, s16 anim);
void func_80107220_mstory1(s16 model);
void func_8010CAD8_mstory1(omObjData *obj);
void func_8010DD70_mstory1(omObjData *obj);
void func_80110248_mstory1(s32 index, s32 seNo);
void func_8011032C_mstory1(s32 index);
void func_80106984_mstory1(void);
void func_8010CAE0_mstory1(void);
void func_8010DA38_mstory1(void);
void func_8010E29C_mstory1(void);
void func_8010E5FC_mstory1(void);
void func_8010EC30_mstory1(void);
void func_8010F244_mstory1(void);
void func_8010F848_mstory1(void);
void func_8010F850_mstory1(void);
void func_8010FAF8_mstory1(void);
void func_8010FC24_mstory1(void);
void func_801103A8_mstory1(void);
void func_8010EE14_mstory1(void);
void func_8010FA40_mstory1(void);
void func_8010FDDC_mstory1(void);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010BDC0_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010C0C4_mstory1);

void func_8010C96C_mstory1(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_8010C99C_mstory1(void) {
    func_80106984_mstory1();
    D_80115B50_mstory1 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_8010CAE0_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010DA38_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010E29C_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010E5FC_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010EC30_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010F244_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010F850_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010FAF8_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010FC24_mstory1, 0x384, 0x800, 0);
    omAddPrcObj(func_801103A8_mstory1, 0x384, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_80115B50_mstory1, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

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

void func_8010D90C_mstory1(omObjData *obj) {
    s16 model = obj->model[1];

    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[9]].motId, 0, 10, 0);
    func_80107220_mstory1(model);
    HuPrcSleep(80);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_80115A30_mstory1[0].func = func_8010CAD8_mstory1;
}

void func_8010D9D0_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80115250_mstory1, 10);
    D_80115A30_mstory1[0].func = func_8010CAD8_mstory1;
}

void func_8010DA04_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_8011525C_mstory1, 10);
    D_80115A30_mstory1[0].func = func_8010CAD8_mstory1;
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
    D_80115A30_mstory1[1].func = func_8010CAD8_mstory1;
}

void func_8010E12C_mstory1(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec orig;
    f32 y;
    s32 i;

    orig.x = Hu3DData[model].pos.x;
    orig.y = Hu3DData[model].pos.y;
    orig.z = Hu3DData[model].pos.z;
    pos.y = Hu3DData[model].pos.y;
    for (i = 0; i < 12; i++) {
        pos.x = Hu3DData[model].pos.x;
        pos.z = Hu3DData[model].pos.z;
        y = sindf(i * 15.0f) * 80.0f;
        Hu3DModelPosSet(model, pos.x, y + pos.y, pos.z);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, orig.x, y + orig.y, orig.z);
    func_801068B0_mstory1(obj->model[1], D_80115B68_mstory1, D_80115B66_mstory1);
    D_80115A30_mstory1[1].func = func_8010CAD8_mstory1;
}

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

const Vec D_80115334_mstory1 = { 200.0f, 0.0f, 1200.0f };

void func_8010E4CC_mstory1(omObjData *obj) {
    HuPrcSleep(10);
    if (func_80106AFC_mstory1(3) == 0) {
        CharFXPlay(0x26B, 3);
    } else {
        CharFXPlay(0x26B, 1);
    }
    HuPrcSleep(20);
    D_80115A30_mstory1[1].func = func_8010DD70_mstory1;
    HuPrcSleep(70);
    if (func_80106AFC_mstory1(3) == 0) {
        CharFXPlay(0x286, 3);
    } else {
        CharFXPlay(0x286, 1);
    }
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    func_80110248_mstory1(2, 40);
    func_80106B14_mstory1(obj, &D_80115334_mstory1, 40);
    func_8011032C_mstory1(2);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_80115A30_mstory1[2].func = func_8010CAD8_mstory1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010E5FC_mstory1);

void func_8010E80C_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010E814_mstory1);

void func_8010EC30_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115A30_mstory1[4].obj = obj;
    D_80115A30_mstory1[4].unk_08 = 0;
    D_80115A30_mstory1[4].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115B50_mstory1);
    func_8000B460_main(obj, 0, 0xA00EF);
    func_8000B460_main(obj, 1, 0xA00F1);
    func_8000B460_main(obj, 2, 0xA00F0);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115B20_mstory1 = D_801150F0_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115B20_mstory1.x, D_80115B20_mstory1.y, D_80115B20_mstory1.z);
    Hu3DModelPosSet(obj->model[2], D_80115B20_mstory1.x, -5.0f, D_80115B20_mstory1.z);
    omPrcSetDestructor(0, func_8010EE14_mstory1);
    D_80115A30_mstory1[4].func = func_8010CAD8_mstory1;
    while (1) {
        D_80115A30_mstory1[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8010EE14_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010EE1C_mstory1);

void func_8010F244_mstory1(void) {
    omObjData *obj;
    omObjData *src;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115A30_mstory1[5].obj = obj;
    D_80115A30_mstory1[5].unk_08 = 0;
    D_80115A30_mstory1[5].unk_0C = 0;
    src = D_80115A30_mstory1[4].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    obj->model[2] = Hu3DModelLink(D_80115B50_mstory1);
    func_8001C5B4_main(obj->model[1], src->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115B2C_mstory1 = D_801150FC_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115B2C_mstory1.x, D_80115B2C_mstory1.y, D_80115B2C_mstory1.z);
    Hu3DModelPosSet(obj->model[2], D_80115B2C_mstory1.x, -5.0f, D_80115B2C_mstory1.z);
    omPrcSetDestructor(0, func_8010F848_mstory1);
    D_80115A30_mstory1[5].func = func_8010CAD8_mstory1;
    while (1) {
        D_80115A30_mstory1[5].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010F3EC_mstory1);

void func_8010F848_mstory1(void) {
}

void func_8010F850_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115A30_mstory1[6].obj = obj;
    D_80115A30_mstory1[6].unk_08 = 0;
    D_80115A30_mstory1[6].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA0127);
    obj->model[2] = Hu3DModelLink(D_80115B50_mstory1);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    D_80115B38_mstory1 = D_80115108_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115B38_mstory1.x, D_80115B38_mstory1.y, D_80115B38_mstory1.z);
    Hu3DModelPosSet(obj->model[2], D_80115B38_mstory1.x, -5.0f, D_80115B38_mstory1.z);
    omPrcSetDestructor(0, func_8010FA40_mstory1);
    D_80115A30_mstory1[6].func = func_8010CAD8_mstory1;
    D_80114B40_mstory1 = 1;
    while (1) {
        D_80115A30_mstory1[6].func(obj);
        HuPrcVSleep();
    }
}

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
    D_80115A30_mstory1[6].func = func_8010CAD8_mstory1;
}

void func_8010FAC4_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80115460_mstory1, 20);
    D_80115A30_mstory1[6].func = func_8010CAD8_mstory1;
}

void func_8010FAF8_mstory1(void) {
    f32 angle = 0.0f;
    Vec pos;
    f32 ofs;
    s16 model;

    if (D_80114B40_mstory1 != 0) {
        model = D_80115A30_mstory1[6].obj->model[1];
        pos.y = Hu3DData[model].pos.y;
        while (TRUE) {
            pos.x = Hu3DData[model].pos.x;
            pos.z = Hu3DData[model].pos.z;
            ofs = sindf(angle) * 25.0f + 25.0f;
            angle += 2.0f;
            angle = (angle >= 360.0f) ? angle - 360.0f : angle;
            Hu3DModelPosSet(model, pos.x, ofs + pos.y, pos.z);
            HuPrcVSleep();
        }
    }
}

void func_8010FC24_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 8, 0, -1, NULL);
    D_80115A30_mstory1[7].obj = obj;
    D_80115A30_mstory1[7].unk_08 = 0;
    D_80115A30_mstory1[7].unk_0C = 0;
    obj->model[1] = func_8000B108_main(D_80115470_mstory1[0], 0x20299);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_80115B44_mstory1 = D_80115114_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115B44_mstory1.x, D_80115B44_mstory1.y, D_80115B44_mstory1.z);
    D_80115B52_mstory1 = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_80115B52_mstory1, 4.0f, 20.0f, 4.0f);
    func_8000D018_main(D_80115B52_mstory1, 60.0f);
    func_800138EC_main(D_80115B52_mstory1, 1, 0);
    func_8001C258_main(D_80115B52_mstory1, 4, 4);
    omPrcSetDestructor(0, func_8010FDDC_mstory1);
    D_80115A30_mstory1[7].func = func_8010CAD8_mstory1;
    while (1) {
        D_80115A30_mstory1[7].func(obj);
        HuPrcVSleep();
    }
}

void func_8010FDDC_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010FDE4_mstory1);

void func_80110100_mstory1(omObjData *obj, omObjData *target) {
    s16 model[2];
    Vec pos[2];
    Vec rot;
    Vec diff;
    s32 i;

    model[0] = obj->model[1];
    model[1] = target->model[1];
    for (i = 0; i < 2; i++) {
        pos[i].x = Hu3DData[model[i]].pos.x;
        pos[i].y = Hu3DData[model[i]].pos.y;
        pos[i].z = Hu3DData[model[i]].pos.z;
    }
    rot.x = Hu3DData[model[0]].rot.x;
    rot.y = Hu3DData[model[0]].rot.y;
    rot.z = Hu3DData[model[0]].rot.z;
    diff.x = pos[1].x - pos[0].x;
    diff.y = pos[1].y - pos[0].y;
    diff.z = pos[1].z - pos[0].z;
    rot.y = -(atan2df(diff.z, diff.x) - 90.0f);
    Hu3DModelRotSet(model[0], rot.x, rot.y, rot.z);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115448_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115460_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/492250", D_80115470_mstory1);

void func_80110248_mstory1(s32 index, s32 seNo) {
    if (D_80115A30_mstory1[index].unk_0C == 0) {
        D_80115A30_mstory1[index].unk_0C = 1;
        D_80115A30_mstory1[index].unk_10 = seNo;
        switch (index) {
            case 0:
                D_80115A30_mstory1[index].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                break;
            case 2:
                if (func_80106AFC_mstory1(3) == 0) {
                    D_80115A30_mstory1[index].unk_14 = CharFXPlay(seNo, 3);
                } else {
                    D_80115A30_mstory1[index].unk_14 = CharFXPlay(seNo, 1);
                }
                break;
            case 1:
            case 3:
            case 4:
            case 5:
                break;
        }
    }
}

void func_8011032C_mstory1(s32 index) {
    if (D_80115A30_mstory1[index].unk_0C == 1) {
        D_80115A30_mstory1[index].unk_0C = 0;
        switch (index) {
            case 0:
            case 2:
                HuAudFXStop((s16)D_80115A30_mstory1[index].unk_14);
                break;
            case 1:
            case 3:
            case 4:
            case 5:
                break;
        }
    }
}

void func_801103A8_mstory1(void) {
    s32 i;
    s32 seNo;

    while (TRUE) {
        for (i = 0; i < 8; i++) {
            if (D_80115A30_mstory1[i].unk_0C == 1 && Hu3DData[D_80115A30_mstory1[i].obj->model[1]].motTime == 0.0f) {
                seNo = D_80115A30_mstory1[i].unk_10;
                switch (i) {
                    case 0:
                        D_80115A30_mstory1[i].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                        break;
                    case 2:
                        if (func_80106AFC_mstory1(3) == 0) {
                            D_80115A30_mstory1[i].unk_14 = CharFXPlay(seNo, 3);
                        } else {
                            D_80115A30_mstory1[i].unk_14 = CharFXPlay(seNo, 1);
                        }
                        break;
                    case 1:
                    case 3:
                    case 4:
                    case 5:
                        break;
                }
            }
        }
        HuPrcVSleep();
    }
}
