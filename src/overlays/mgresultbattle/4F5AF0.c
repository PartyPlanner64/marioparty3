#include "common.h"
#include "game/hmfspr.h"
#include "mgresultbattle.h"

extern u16 D_80108F30_mgresultbattle[];
extern u16 D_80108F38_mgresultbattle[4][3];
extern omObjData *D_80108F7C_mgresultbattle;
extern omObjData *D_80108F84_mgresultbattle;
extern omObjFunc D_80108F88_mgresultbattle;
extern Vec D_801089D0_mgresultbattle[4];
extern s32 D_80108A00_mgresultbattle[4];
extern f32 D_80108A10_mgresultbattle[4];
extern omObjFunc D_80108F80_mgresultbattle;
extern s8 D_80108F8C_mgresultbattle[4];

void func_80107F94_mgresultbattle(void);
void func_80107F9C_mgresultbattle(omObjData *obj);
void func_8010829C_mgresultbattle(omObjData *obj);
void func_801082A4_mgresultbattle(void);
void func_801082C0_mgresultbattle(omObjData *obj);
void func_80106918_mgresultbattle(void);
void func_80108510_mgresultbattle(s16 group, s16 x, s16 y);

void func_80107D10_mgresultbattle(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x14, 8, 8, -1, NULL);
    D_80108F7C_mgresultbattle = obj;
    obj->model[0] = func_8000B108_main(0x1B0005, 0x2B9);

    for (i = 0; i < 4; i++) {
        obj->model[i + 1] = func_8000B108_main(
            D_80108A00_mgresultbattle[GwPlayer[D_80108F8C_mgresultbattle[i]].bonusCoin], 0x16B9);
        func_8001C814_main(obj->model[i + 1], 2, 0);
        func_8001C814_main(obj->model[i + 1], 1, 1);
        func_8001C258_main(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(obj->model[i + 1], D_801089D0_mgresultbattle[i].x, D_801089D0_mgresultbattle[i].y,
                        D_801089D0_mgresultbattle[i].z);
        Hu3DModelRotSet(obj->model[i + 1], 0.0f, D_80108A10_mgresultbattle[i], 0.0f);
        func_8001C258_main(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionTimeSet(obj->model[i + 1], D_800CCF58_main[HmfModelData[obj->model[i + 1]].motId].unk02);
        func_8001C814_main(obj->model[i + 1], 1, 1);
    }

    obj->trans.x = 0.0f;
    obj->trans.y = -5.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(NULL, func_80107F94_mgresultbattle);
    D_80108F80_mgresultbattle = func_80107F9C_mgresultbattle;
    HuPrcSleep(2);

    while (TRUE) {
        D_80108F80_mgresultbattle(obj);
        HuPrcVSleep();
    }
}

void func_80107F94_mgresultbattle(void) {
}

void func_80107F9C_mgresultbattle(omObjData *obj) {
    HuMtx4F mtx;
    s32 i;

    for (i = 0; i < 4; i++) {
        func_80016B00_main(obj->model[i + 1], HmfModelData[obj->model[i + 1]].motTime, "chara", &mtx);
        Hu3DModelPosSet(D_80108F50_mgresultbattle[i].obj->model[1], mtx[3][0] + D_801089D0_mgresultbattle[i].x,
                        mtx[3][1] + D_801089D0_mgresultbattle[i].y, mtx[3][2] + D_801089D0_mgresultbattle[i].z);
    }
}

void func_801080A0_mgresultbattle(void) {
    omObjData *obj = D_80108F7C_mgresultbattle;
    s32 i;

    for (i = 0; i < 4; i++) {
        func_8001C258_main(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        func_8001C814_main(obj->model[i + 1], 1, 0);
        Hu3DMotionTimeSet(obj->model[i + 1], 0.0f);
    }
}

void func_80108130_mgresultbattle(void) {
    omObjData *obj;
    s16 sprite;
    s32 i;
    s32 j;

    obj = omAddObj(0x14, 0, 0, -1, NULL);
    D_80108F84_mgresultbattle = obj;

    sprite = func_8000B838_main(0x1B0006);
    for (j = 0; j < 4; j++) {
        D_80108F30_mgresultbattle[j] = espEntry(sprite, 0, 0);
        espDispOff(D_80108F30_mgresultbattle[j]);
    }

    sprite = func_8000B838_main(0x1B0007);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            D_80108F38_mgresultbattle[i][j] = espEntry(sprite, 0, 0);
            espDispOff(D_80108F38_mgresultbattle[i][j]);
        }
    }

    omPrcSetDestructor(0, func_801082A4_mgresultbattle);
    D_80108F88_mgresultbattle = func_8010829C_mgresultbattle;

    while (TRUE) {
        D_80108F88_mgresultbattle(obj);
        HuPrcVSleep();
    }
}

void func_8010829C_mgresultbattle(omObjData *obj) {
}

void func_801082A4_mgresultbattle(void) {
}

void func_801082AC_mgresultbattle(void) {
    D_80108F88_mgresultbattle = func_801082C0_mgresultbattle;
}

void func_801082C0_mgresultbattle(omObjData *obj) {
    Vec pos;
    Vec2f screen;
    Vec2f screenPos[4];
    s32 i;

    for (i = 0; i < 4; i++) {
        pos.x = HmfModelData[D_80108F50_mgresultbattle[i].obj->model[1]].pos.x;
        pos.y = HmfModelData[D_80108F50_mgresultbattle[i].obj->model[1]].pos.y;
        pos.z = HmfModelData[D_80108F50_mgresultbattle[i].obj->model[1]].pos.z;
        Hu3D3Dto2D(0, &pos, &screen);
        espPosSet(D_80108F30_mgresultbattle[i], screen.x, (s32)screen.y - 48);
        espDispOn(D_80108F30_mgresultbattle[i]);
        espScaleSet(D_80108F30_mgresultbattle[i], 0.0f, 0.0f);
        screenPos[i] = screen;
    }

    for (i = 0; i < 20; i++) {
        sindf(i * 4.5f);
        HuPrcVSleep();
    }

    for (i = 0; i < 4; i++) {
        espScaleSet(D_80108F30_mgresultbattle[i], 1.0f, 1.0f);
        func_80108510_mgresultbattle(i, screenPos[i].x, (s32)screenPos[i].y - 48);
    }

    func_80106918_mgresultbattle();
    HuPrcSleep(50);
    D_80108F88_mgresultbattle = func_8010829C_mgresultbattle;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F5AF0", func_80108510_mgresultbattle);

void func_80108858_mgresultbattle(s16 group) {
    espDispOff(D_80108F30_mgresultbattle[group]);
    espDispOff(D_80108F38_mgresultbattle[group][0]);
    espDispOff(D_80108F38_mgresultbattle[group][1]);
    espDispOff(D_80108F38_mgresultbattle[group][2]);
}
