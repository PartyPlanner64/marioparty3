#include "common.h"
#include "game/hmfmath.h"
#include "overlays/minigame.h"

typedef struct UnkMstory2Obj {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} UnkMstory2Obj; // sizeof 0x14

extern void (*const D_8011BDE0_mstory2[])(void);
extern UnkMstory2Obj D_8011CA10_mstory2[3];
extern s16 D_8011CA74_mstory2[3];
extern Vec D_8011CA50_mstory2;
extern const Vec D_8011C60C_mstory2;
extern s16 D_8011CA7A_mstory2;
extern s16 D_8011CA4C_mstory2;
extern f32 D_8011BDD0_mstory2;
extern Vec D_8011CA5C_mstory2;
extern const Vec D_8011C618_mstory2;
extern f32 D_8011BDD4_mstory2;
extern f32 D_8011BDD8_mstory2;
extern f32 D_8011CA04_mstory2;

void func_80105FBC_mstory2(void);
void func_80106D58_mstory2(s16 model, s16 arg1, s16 arg2);
void func_8011AB84_mstory2(void);
void func_8011AC08_mstory2(void);
void func_8011AC10_mstory2(omObjData *);
void func_8011AD8C_mstory2(omObjData *);
void func_8011B080_mstory2(omObjData *);
void func_8011B198_mstory2(void);
void func_8011AB7C_mstory2(omObjData *obj);
void func_8011B45C_mstory2(void);
void func_8011B464_mstory2(omObjData *obj);
void func_8011B64C_mstory2(void);
void func_8011B818_mstory2(void);
void func_8011B820_mstory2(omObjData *obj);
void func_80105EA4_mstory2(void);
void func_80105EB4_mstory2(void);
void func_801060A4_mstory2(void);
void func_801060D4_mstory2(void);
void func_801060F8_mstory2(s32 mess);
s16 func_801061BC_mstory2(void);

void func_8011AAE0_mstory2(void) {
    func_80105FBC_mstory2();
    D_8011CA4C_mstory2 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_8011B198_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8011B64C_mstory2, 0x1001, 0x1000, 0);
    HuPrcVSleep();
    omAddPrcObj(func_8011AB84_mstory2, 0x1001, 0x1000, 0);
    HuPrcVSleep();
    func_8001C258_main(D_8011CA4C_mstory2, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_8011AB7C_mstory2(omObjData *obj) {
}

void func_8011AB84_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0, 0, -1, NULL);
    D_8011CA10_mstory2[2].obj = obj;
    D_8011CA10_mstory2[2].unk_08 = 0;
    D_8011CA10_mstory2[2].func = func_8011AC10_mstory2;
    omPrcSetDestructor(0, func_8011AC08_mstory2);
    while (1) {
        D_8011CA10_mstory2[2].func(obj);
        HuPrcVSleep();
    }
}

void func_8011AC08_mstory2(void) {
}

void func_8011AC10_mstory2(omObjData *obj) {
    s16 choice;

    HuPrcSleep(40);
    HuAudFXPlay(0x159);
    func_801060A4_mstory2();
    func_801060F8_mstory2(0x5A7F);
    func_801060D4_mstory2();
    Hu3DMotionShiftSet(D_8011CA10_mstory2[1].obj->model[1], Hu3DData[D_8011CA10_mstory2[1].obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(20);
    Hu3DMotionShiftSet(D_8011CA10_mstory2[1].obj->model[1], Hu3DData[D_8011CA10_mstory2[1].obj->motion[1]].motId, 0, 10, 2);
    func_801060A4_mstory2();
    func_801060F8_mstory2(0x5A80);
    choice = func_801061BC_mstory2();
    func_801060D4_mstory2();
    Hu3DMotionShiftSet(D_8011CA10_mstory2[1].obj->model[1], Hu3DData[D_8011CA10_mstory2[1].obj->motion[0]].motId, 0, 10, 2);
    switch (choice) {
        case 0:
            D_8011CA10_mstory2[2].func = func_8011AD8C_mstory2;
            break;
        case 1:
            D_8011CA10_mstory2[2].func = func_8011B080_mstory2;
            break;
    }
}

void func_8011AD8C_mstory2(omObjData *obj) {
    Hu3DMotionShiftSet(D_8011CA10_mstory2[1].obj->model[1], Hu3DData[D_8011CA10_mstory2[1].obj->motion[3]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(D_8011CA10_mstory2[0].obj->model[1], Hu3DData[D_8011CA10_mstory2[0].obj->motion[0]].motId, 0, 10, 0);
    func_80106D58_mstory2(D_8011CA10_mstory2[0].obj->model[1], D_8011CA7A_mstory2, D_8011CA74_mstory2[1]);
    D_8011CA10_mstory2[0].func = func_8011B464_mstory2;
    D_8011CA10_mstory2[0].unk_08 = 1;
    func_801060A4_mstory2();
    func_801060F8_mstory2(0x5A81);
    func_801060D4_mstory2();
    Hu3DMotionShiftSet(D_8011CA10_mstory2[1].obj->model[1], Hu3DData[D_8011CA10_mstory2[1].obj->motion[0]].motId, 0, 10, 2);
    D_8011CA10_mstory2[1].unk_08 = 1;
    D_8011CA10_mstory2[0].unk_08 = 2;
    HuPrcSleep(20);
    while (TRUE) {
        if (D_8011CA10_mstory2[0].unk_08 == 3) {
            break;
        }
        HuPrcVSleep();
    }
    while (TRUE) {
        Hu3DData[D_8011CA10_mstory2[0].obj->model[1]].pos.y += 30.0f;
        Hu3DData[D_8011CA10_mstory2[1].obj->model[1]].pos.y += 60.0f;
        Hu3DData[D_8011CA10_mstory2[0].obj->model[2]].scale.x = Hu3DData[D_8011CA10_mstory2[0].obj->model[2]].scale.z -= 0.075f;
        Hu3DData[D_8011CA10_mstory2[1].obj->model[2]].scale.x = Hu3DData[D_8011CA10_mstory2[1].obj->model[2]].scale.z -= 0.075f;
        if (Hu3DData[D_8011CA10_mstory2[0].obj->model[1]].pos.y >= 500.0f) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcVSleep();
    func_80105EB4_mstory2();
    D_8011CA10_mstory2[1].func = func_8011AB7C_mstory2;
    D_8011CA10_mstory2[0].func = func_8011AB7C_mstory2;
    D_8011CA10_mstory2[2].func = func_8011AB7C_mstory2;
}

void func_8011B080_mstory2(omObjData *obj) {
    func_80106D58_mstory2(D_8011CA10_mstory2[0].obj->model[1], D_8011CA7A_mstory2, D_8011CA74_mstory2[2]);
    HuPrcSleep(20);
    Hu3DMotionShiftSet(D_8011CA10_mstory2[1].obj->model[1], Hu3DData[D_8011CA10_mstory2[1].obj->motion[2]].motId, 0, 10, 2);
    func_801060A4_mstory2();
    func_801060F8_mstory2(0x5A82);
    func_801060D4_mstory2();
    Hu3DMotionShiftSet(D_8011CA10_mstory2[1].obj->model[1], Hu3DData[D_8011CA10_mstory2[1].obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(30);
    func_80105EA4_mstory2();
    D_8011CA10_mstory2[1].func = func_8011AB7C_mstory2;
    D_8011CA10_mstory2[0].func = func_8011AB7C_mstory2;
    D_8011CA10_mstory2[2].func = func_8011AB7C_mstory2;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/4B0E80", D_8011C60C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/4B0E80", D_8011C618_mstory2);

const char D_8011C630_mstory2[] = "c204n_0_DEF";

void func_8011B198_mstory2(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 20, 20, -1, NULL);
    D_8011CA10_mstory2[0].obj = obj;
    D_8011CA10_mstory2[0].unk_08 = 0;
    D_8011CA10_mstory2[0].func = func_8011AB7C_mstory2;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011CA4C_mstory2);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011CA50_mstory2 = D_8011C60C_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011CA50_mstory2.x, D_8011CA50_mstory2.y, D_8011CA50_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011CA50_mstory2.x, -5.0f, D_8011CA50_mstory2.z);
    data = DataRead(0xA0082);
    D_8011CA74_mstory2[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_8011C630_mstory2);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8011CA74_mstory2[0], 1, 0);
    Hu3DAnimBankSet(D_8011CA74_mstory2[0], 0);
    D_8011CA7A_mstory2 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011CA74_mstory2[0], 0, D_8011C630_mstory2);
    data = DataRead(0xA0084);
    D_8011CA74_mstory2[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_8011CA7A_mstory2 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011CA74_mstory2[0], 0, D_8011C630_mstory2);
    data = DataRead(0xA0080);
    D_8011CA74_mstory2[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106D58_mstory2(obj->model[1], D_8011CA7A_mstory2, D_8011CA74_mstory2[0]);
    omPrcSetDestructor(0, func_8011B45C_mstory2);
    while (TRUE) {
        D_8011CA10_mstory2[0].func(obj);
        HuPrcVSleep();
    }
}

void func_8011B45C_mstory2(void) {
}

void func_8011B464_mstory2(omObjData *obj) {
    if (D_8011CA10_mstory2[0].unk_08 == 1) {
        Hu3DData[obj->model[1]].pos.y += D_8011BDD0_mstory2 * D_8011BDD0_mstory2 * (D_8011BDD0_mstory2 >= 0.0f ? -8.75f : 8.75f);
        if (D_8011BDD0_mstory2 > 1.5f) {
            D_8011BDD0_mstory2 = -1.5f;
        } else {
            D_8011BDD0_mstory2 += 0.2f;
        }
    } else if (D_8011CA10_mstory2[0].unk_08 == 2) {
        Hu3DData[obj->model[1]].pos.y += D_8011BDD0_mstory2 * D_8011BDD0_mstory2 * (D_8011BDD0_mstory2 >= 0.0f ? -8.75f : 8.75f);
        if (D_8011BDD0_mstory2 > 1.5f) {
            D_8011BDD0_mstory2 = 0.0f;
            Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
            D_8011CA10_mstory2[0].func = func_8011AB7C_mstory2;
            D_8011CA10_mstory2[0].unk_08 = 3;
        } else {
            D_8011BDD0_mstory2 += 0.2f;
        }
    }
}

void func_8011B64C_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_8011CA10_mstory2[1].obj = obj;
    D_8011CA10_mstory2[1].unk_08 = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011CA4C_mstory2);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0129);
    func_8000B460_main(obj, 2, 0xA0125);
    func_8000B460_main(obj, 3, 0xA0128);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011CA5C_mstory2 = D_8011C618_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011CA5C_mstory2.x, D_8011CA5C_mstory2.y, D_8011CA5C_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011CA5C_mstory2.x, -5.0f, D_8011CA5C_mstory2.z);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    omPrcSetDestructor(0, func_8011B818_mstory2);
    D_8011CA10_mstory2[1].func = func_8011B820_mstory2;
    while (1) {
        D_8011CA10_mstory2[1].func(obj);
        HuPrcVSleep();
    }
}

void func_8011B818_mstory2(void) {
}

void func_8011B820_mstory2(omObjData *obj) {
    D_8011CA04_mstory2 = Hu3DData[obj->model[1]].pos.y;
    D_8011BDD8_mstory2 = sindf(D_8011BDD4_mstory2) * 15.0f + 15.0f;
    D_8011BDD4_mstory2 += 2.0f;
    if (D_8011BDD4_mstory2 >= 360.0f) {
        D_8011BDD4_mstory2 -= 360.0f;
    }
    if (D_8011CA10_mstory2[1].unk_08 != 1) {
        Hu3DModelPosSet(obj->model[1], 0.0f, D_8011BDD8_mstory2 + 225.0f, 400.0f);
    }
}
