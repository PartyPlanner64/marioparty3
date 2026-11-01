#include "common.h"

extern s8 D_8010D408_inst;
extern s8 D_8010D40A_inst;
extern s32 D_8010DC40_inst;
extern s16 D_8010DC42_inst;
extern omObjData *D_8010DDD0_inst;
extern s32 D_8010D540_inst;
extern s32 D_8010D544_inst;
extern void (*D_8010DDD4_inst)(omObjData *);

void func_80109E94_inst(omObjData *);
void func_80109F50_inst(omObjData *);
void func_8010A000_inst(omObjData *);
void func_8010A0E8_inst(omObjData *);
void func_8010A1BC_inst(omObjData *object);
void func_8010C848_inst(void);
void func_8010C8D0_inst(void);

void func_80109A90_inst(void) {
    omObjData *object;
    void *data;

    object = omAddObj(25, 5, 8, -1, NULL);
    D_8010DDD0_inst = object;
    object->model[0] = func_8000B108_main(0xA00A5, 0x16A9);
    func_8000B460_main(object, 0, 0xA00B4);
    func_8000B460_main(object, 1, 0xA00B5);
    if (D_8010D40A_inst == 3) {
        object->model[1] = func_8000B108_main(0x170047, 0x16B9);
        func_8001C258_main(object->model[1], 0x4000, 0x4000);
        func_8001C814_main(object->model[1], 2, 2);
        func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelHookSet(object->model[1], object->model[0], "item_hook");
    }
    func_8001C5B4_main(object->model[0], object->motion[0]);
    func_8001C814_main(object->model[0], 2, 2);
    data = DataRead(0xA00B8);
    D_8010DC40_inst = (s16)HmfAnimCreate(HmfModelData[object->model[0]].hmf, data, 0, "c164m_0_DEF");
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(object->model[0]);
    func_8001C514_main(object->model[0]);
    func_80032FC0_main(D_8010DC42_inst, 1, 0);
    func_80032FF8_main(D_8010DC42_inst, 0);
    object->trans.x = D_8010D40A_inst == 3 ? -86.0f : -91.0f;
    object->trans.y = D_8010D40A_inst == 3 ? -150.0f : -164.0f;
    object->trans.z = 210.0f;
    object->rot.x = -20.0f;
    object->rot.y = 15.0f;
    object->scale.x = object->scale.y = object->scale.z = 0.5f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    object->scale.x = object->scale.y = object->scale.z = 0.4f;
    Hu3DModelScaleSet(object->model[0], 0.4f, 0.4f, 0.4f);
    func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    if (D_8010D408_inst == 1) {
        func_8001C5B4_main(object->model[0], object->motion[0]);
        func_8001C814_main(object->model[0], 2, 2);
        func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        object->trans.x = D_8010D40A_inst == 3 ? -86.0f : -91.0f;
        object->trans.y = D_8010D40A_inst == 3 ? 50.0f : 36.0f;
        object->trans.z = 210.0f;
        object->rot.x = -20.0f;
        object->rot.y = 15.0f;
        D_8010DDD4_inst = func_8010A0E8_inst;
    } else {
        D_8010DDD4_inst = func_80109E94_inst;
    }
    while (1) {
        D_8010DDD4_inst(object);
        HuPrcVSleep();
    }
}

void func_80109E94_inst(omObjData *object) {
    object->trans.x = D_8010D40A_inst == 3 ? -86.0f : -91.0f;
    object->trans.y = D_8010D40A_inst == 3 ? -150.0f : -164.0f;
    object->trans.z = 210.0f;
    object->rot.x = -20.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    D_8010DDD4_inst = func_80109F50_inst;
}

void func_80109F50_inst(omObjData *object) {
    D_8010D540_inst++;
    if (D_8010D540_inst >= 110) {
        func_8001C5B4_main(object->model[0], object->motion[1]);
        func_8001C814_main(object->model[0], 2, 0);
        func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        HuAudFXPlay(0x25B);
        D_8010DDD4_inst = func_8010A000_inst;
        D_8010D540_inst = 0;
        func_8010C8D0_inst();
    }
}

void func_8010A000_inst(omObjData *object) {
    f32 height;
    f32 finalHeight;

    D_8010D544_inst++;
    height = sindf(D_8010D544_inst * 5) * 200.0f;
    if (D_8010D40A_inst == 3) {
        object->trans.y = height + -150.0f;
    } else {
        object->trans.y = height + -164.0f;
    }
    if (D_8010D544_inst >= 17) {
        if (D_8010D40A_inst == 3) {
            finalHeight = 50.0f;
        } else {
            finalHeight = 36.0f;
        }
        object->trans.y = finalHeight;
        D_8010D544_inst = 0;
        D_8010DDD4_inst = func_8010A0E8_inst;
    }
}

void func_8010A0E8_inst(omObjData *object) {
    s16 model = object->model[0];

    if (D_800CCF58_main[HmfModelData[model].motId].unk02 <= HmfModelData[model].motTime + 15.0f) {
        Hu3DMotionShiftSet(model, HmfModelData[object->motion[0]].motId, 0, 30, 2);
        func_8010C848_inst();
        D_8010DDD4_inst = func_8010A1BC_inst;
    }
}

void func_8010A1BC_inst(omObjData *object) {
}
