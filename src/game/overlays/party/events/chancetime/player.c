#include "common.h"
#include "chancetime.h"

extern s32 D_8010FE70_chancetime;
extern s32 D_8010FE74_chancetime;
extern s8 D_8010FE78_chancetime;
extern s16 D_8010FE7A_chancetime[3];
extern ChanceTimeObjState D_801100C0_chancetime;
extern s32 D_800A178C_main[][6];

void func_80106760_chancetime(omObjData *object);
void func_80106768_chancetime(void);
void func_80106770_chancetime(omObjData *object);
void func_8010684C_chancetime(omObjData *object);
void func_80106A2C_chancetime(omObjData *object);
void func_80106BEC_chancetime(omObjData *object);

s32 D_8010FAF0_chancetime = 0;
f32 D_8010FAF4_chancetime = 360.0f;
f32 D_8010FAF8_chancetime = 0.0f;
f32 D_8010FAFC_chancetime = 0.2f;

void func_80106320_chancetime(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 6, 10, -1, NULL);
    D_801100C0_chancetime.obj = obj;
    chr = GwPlayer[D_801100D0_chancetime[0]].chr;

    obj->model[1] = Hu3DModelRead(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelPosSet(obj->model[1], 360.0f, 0.0f, -50.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, -90.0f, 0.0f);
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DModelCameraSet(obj->model[1], 2);

    obj->model[2] = Hu3DModelRead(9, 0x2B9);
    Hu3DModelPosSet(obj->model[2], 360.0f, -10.0f, -50.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrSet(obj->model[2], 4, 4);
    Hu3DModelCameraSet(obj->model[2], 2);

    obj->model[3] = Hu3DModelRead(0x1C000B, 0x2B9);
    Hu3DModelPosSet(obj->model[3], 180.0f, 220.0f, 0.0f);
    Hu3DMotionAttrSet(obj->model[3], 2, 0);
    Hu3DModelScaleSet(obj->model[3], 0.7f, 0.7f, 0.7f);
    Hu3DModelAttrSet(obj->model[3], 4, 4);
    Hu3DModelCameraSet(obj->model[3], 2);

    obj->model[4] = Hu3DModelRead(0x5D0008, 0x2B9);
    Hu3DModelPosSet(obj->model[4], 180.0f, 220.0f, 0.0f);
    Hu3DModelAttrSet(obj->model[4], 4, 4);

    D_8010FE7A_chancetime[0] = CharAnimCreate(obj->model[1], 2, chr, CharMotionDataNumGet(chr, 0xA4));
    D_8010FE7A_chancetime[1] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA5));
    D_8010FE7A_chancetime[2] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA6));
    Hu3DModelDynamicFree(obj->model[1]);
    CharAnimSet(obj->model[1], 2, GwPlayer[D_801100D0_chancetime[0]].chr, D_8010FE7A_chancetime[0]);

    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 1));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 0x36));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chr, 0x36));
    omObjMotionRead(obj, 5, CharMotionDataNumGet(chr, 0x2B));
    omObjMotionRead(obj, 6, CharMotionDataNumGet(chr, 0x1F));
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);

    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(0, func_80106768_chancetime);
    D_801100C0_chancetime.func = func_80106760_chancetime;

    while (TRUE) {
        D_801100C0_chancetime.func(obj);
        HuPrcVSleep();
    }
}

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

void func_8010684C_chancetime(omObjData *object) {
    s16 done = FALSE;

    D_8010FAF8_chancetime += 8.0f;
    if (D_8010FAF8_chancetime >= 90.0f) {
        D_8010FAF8_chancetime = 90.0f;
        done = TRUE;
    }
    Hu3DModelRotSet(object->model[1], 0.0f, D_8010FAF8_chancetime + -90.0f, 0.0f);
    if (done == TRUE) {
        D_8010FAF8_chancetime = 0.0f;
        D_8010FE70_chancetime = 0;
        D_8010FE74_chancetime = done;
        Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[0]].motId, 0, 30, 2);
        Hu3DModelScaleSet(object->model[3], 0.2f, 0.2f, 0.2f);
        Hu3DMotionAttrSet(object->model[3], 2, 0);
        Hu3DMotionAttrSet(object->model[3], 1, 1);
        Hu3DModelAttrSet(object->model[3], 4, 0);
        Hu3DModelPosSet(object->model[4], Hu3DData[object->model[3]].pos.x, Hu3DData[object->model[3]].pos.y,
                        Hu3DData[object->model[3]].pos.z);
        Hu3DModelAttrSet(object->model[4], 4, 0);
        Hu3DMotionAttrSet(object->model[4], 2, 0);
        Hu3DMotionAttrSet(object->model[4], 1, 0);
        D_801100C0_chancetime.func = func_80106A2C_chancetime;
    }
}

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
    Hu3DMotionModelSet(obj->model[1], obj->motion[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelAttrSet(obj->model[1], 4, 0);
    Hu3DModelAttrSet(obj->model[2], 4, 0);
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

void func_80106BEC_chancetime(omObjData *object) {
    s16 player = D_801100D0_chancetime[0];
    f32 time;
    s16 done;
    s16 delay;
    u16 btn;

    D_8010FAF0_chancetime = 0;
    // The repeated done checks and the delay/btn temporaries are needed for the original block layout.
    while (TRUE) {
        done = FALSE;
        if (GwPlayer[player].stat & 1) {
            done = TRUE;
        }
        if (done) {
            delay = (u8)(rand8() % 15) + 15;
            HuPrcSleep(delay);
        }
        if (done) {
            break;
        }
        btn = HuPadBtnDown[GwPlayer[player].pad] & 0x8000;
        if (btn) {
            break;
        }
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[5]].motId, 0, 20, 0);
    Hu3DMotionSpeedSet(object->model[1], 3.0f);
    done = FALSE;
    do {
        time = Hu3DMotionShiftTimeGet(object->model[1]);
        if (done == FALSE) {
            if (time >= 5.0f) {
                done = TRUE;
                func_8010D92C_chancetime(D_8010FE78_chancetime);
                Hu3DMotionAttrSet(object->model[3], 2, 0);
                Hu3DMotionAttrSet(object->model[3], 1, 0);
                Hu3DMotionTimeSet(object->model[3], 0.0f);
                Hu3DMotionSpeedSet(object->model[3], 1.2f);
                Hu3DModelAttrSet(object->model[3], 4, 0);
            }
        }
        HuPrcVSleep();
    } while (time >= 0.0f);
    Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[6]].motId, 0, 20, 0);
    Hu3DMotionSpeedSet(object->model[1], 3.0f);
    do {
        time = Hu3DMotionShiftTimeGet(object->model[1]);
        HuPrcVSleep();
    } while (time >= 0.0f);
    time = 0.0f;
    Hu3DModelPosSet(object->model[1], 180.0f, time, -50.0f);
    Hu3DModelPosSet(object->model[3], 180.0f, 220.0f, time);
    Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[0]].motId, 0, 20, 2);
    Hu3DMotionSpeedSet(object->model[1], 1.0f);
    D_8010FAF0_chancetime = 1;
    D_801100C0_chancetime.func = func_80106760_chancetime;
}

void func_80106F10_chancetime(void) {
    omObjData *object = D_801100C0_chancetime.obj;
    f32 time;
    f32 length;

    HuAudFXPlay(0x502);
    CharFXPlay(0x274, GwPlayer[D_801100D0_chancetime[0]].chr);
    CharAnimSet(object->model[1], 2, GwPlayer[D_801100D0_chancetime[0]].chr, D_8010FE7A_chancetime[1]);
    Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[2]].motId, 0, 30, 0);
    HuPrcSleep(30);
    do {
        time = Hu3DData[object->model[1]].motTime;
        length = Hu3DMotion[Hu3DData[object->model[1]].motId].unk02;
        HuPrcVSleep();
    } while (time < length);
}

void func_8010705C_chancetime(void) {
    omObjData *object = D_801100C0_chancetime.obj;
    f32 time;
    f32 length;

    HuAudFXPlay(0x503);
    CharFXPlay(0x26B, GwPlayer[D_801100D0_chancetime[0]].chr);
    CharAnimSet(object->model[1], 2, GwPlayer[D_801100D0_chancetime[0]].chr, D_8010FE7A_chancetime[2]);
    Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[3]].motId, 0, 30, 0);
    HuPrcSleep(30);
    do {
        time = Hu3DData[object->model[1]].motTime;
        length = Hu3DMotion[Hu3DData[object->model[1]].motId].unk02;
        HuPrcVSleep();
    } while (time < length);
}

void func_801071A8_chancetime(void) {
    omObjData *object = D_801100C0_chancetime.obj;
    f32 time;
    f32 length;

    HuAudFXPlay(0x503);
    CharFXPlay(0x26B, GwPlayer[D_801100D0_chancetime[0]].chr);
    CharAnimSet(object->model[1], 2, GwPlayer[D_801100D0_chancetime[0]].chr, D_8010FE7A_chancetime[2]);
    Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[4]].motId, 0, 30, 0);
    HuPrcSleep(30);
    do {
        time = Hu3DData[object->model[1]].motTime;
        length = Hu3DMotion[Hu3DData[object->model[1]].motId].unk02;
        HuPrcVSleep();
    } while (time < length);
}
