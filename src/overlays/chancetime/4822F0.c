#include "common.h"
#include "chancetime.h"

extern s32 D_8010FAF0_chancetime;
extern f32 D_8010FAF4_chancetime;
extern f32 D_8010FAFC_chancetime;
extern s32 D_8010FE70_chancetime;
extern s32 D_8010FE74_chancetime;
extern s8 D_8010FE78_chancetime;
extern s16 D_8010FE7C_chancetime;
extern s16 D_8010FE7E_chancetime;
extern ChanceTimeObjState D_801100C0_chancetime;
extern s8 D_801100D0_chancetime[];

void func_80106770_chancetime(omObjData *object);
void func_8010684C_chancetime(omObjData *object);
void func_80106BEC_chancetime(omObjData *object);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_80106320_chancetime);

void func_80106760_chancetime(omObjData *object) {
}

void func_80106768_chancetime(void) {
}

void func_80106770_chancetime(omObjData *object) {
    s16 done = FALSE;

    D_8010FAF4_chancetime -= 25.0f;
    if (D_8010FAF4_chancetime <= 180.0f) {
        D_8010FAF4_chancetime = 180.0f;
        done = TRUE;
    }
    Hu3DModelPosSet(object->model[1], D_8010FAF4_chancetime, 0.0f, -50.0f);
    Hu3DModelPosSet(object->model[2], D_8010FAF4_chancetime, -10.0f, -50.0f);
    if (done == TRUE) {
        D_8010FAF4_chancetime = 360.0f;
        D_801100C0_chancetime.func = func_8010684C_chancetime;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_8010684C_chancetime);

void func_80106A2C_chancetime(omObjData *object) {
    s32 done = FALSE;

    HuPrcSleep(2);
    HuAudFXPlay(0x501);
    do {
        D_8010FAFC_chancetime += 0.14f;
        if (D_8010FAFC_chancetime >= 0.7f) {
            D_8010FAFC_chancetime = 0.7f;
            done = TRUE;
        }
        Hu3DModelScaleSet(object->model[3], D_8010FAFC_chancetime, D_8010FAFC_chancetime, D_8010FAFC_chancetime);
        HuPrcVSleep();
    } while (done != TRUE);
    D_8010FAFC_chancetime = 0.0f;
    D_801100C0_chancetime.func = func_80106760_chancetime;
}

void func_80106B18_chancetime(void) {
    omObjData *obj = D_801100C0_chancetime.obj;

    D_8010FE70_chancetime = 1;
    D_8010FE74_chancetime = 0;
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    D_801100C0_chancetime.func = func_80106770_chancetime;
}

s32 func_80106BB8_chancetime(void) {
    return D_8010FE74_chancetime;
}

void func_80106BC4_chancetime(s8 arg0) {
    D_8010FE78_chancetime = arg0;
    D_801100C0_chancetime.func = func_80106BEC_chancetime;
}

s32 func_80106BE0_chancetime(void) {
    return D_8010FAF0_chancetime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_80106BEC_chancetime);

void func_80106F10_chancetime(void) {
    omObjData *object = D_801100C0_chancetime.obj;
    f32 time;
    f32 length;

    HuAudFXPlay(0x502);
    CharFXPlay(0x274, GwPlayer[D_801100D0_chancetime[0]].chr);
    func_80017954_main(object->model[1], 2, GwPlayer[D_801100D0_chancetime[0]].chr, D_8010FE7C_chancetime);
    Hu3DMotionShiftSet(object->model[1], HmfModelData[object->motion[2]].motId, 0, 30, 0);
    HuPrcSleep(30);
    do {
        time = HmfModelData[object->model[1]].motTime;
        length = D_800CCF58_main[HmfModelData[object->model[1]].motId].unk02;
        HuPrcVSleep();
    } while (time < length);
}

void func_8010705C_chancetime(void) {
    omObjData *object = D_801100C0_chancetime.obj;
    f32 time;
    f32 length;

    HuAudFXPlay(0x503);
    CharFXPlay(0x26B, GwPlayer[D_801100D0_chancetime[0]].chr);
    func_80017954_main(object->model[1], 2, GwPlayer[D_801100D0_chancetime[0]].chr, D_8010FE7E_chancetime);
    Hu3DMotionShiftSet(object->model[1], HmfModelData[object->motion[3]].motId, 0, 30, 0);
    HuPrcSleep(30);
    do {
        time = HmfModelData[object->model[1]].motTime;
        length = D_800CCF58_main[HmfModelData[object->model[1]].motId].unk02;
        HuPrcVSleep();
    } while (time < length);
}

void func_801071A8_chancetime(void) {
    omObjData *object = D_801100C0_chancetime.obj;
    f32 time;
    f32 length;

    HuAudFXPlay(0x503);
    CharFXPlay(0x26B, GwPlayer[D_801100D0_chancetime[0]].chr);
    func_80017954_main(object->model[1], 2, GwPlayer[D_801100D0_chancetime[0]].chr, D_8010FE7E_chancetime);
    Hu3DMotionShiftSet(object->model[1], HmfModelData[object->motion[4]].motId, 0, 30, 0);
    HuPrcSleep(30);
    do {
        time = HmfModelData[object->model[1]].motTime;
        length = D_800CCF58_main[HmfModelData[object->model[1]].motId].unk02;
        HuPrcVSleep();
    } while (time < length);
}
