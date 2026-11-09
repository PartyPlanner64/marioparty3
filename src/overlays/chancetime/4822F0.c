#include "common.h"
#include "chancetime.h"

extern s32 D_8010FAF0_chancetime;
extern f32 D_8010FAF4_chancetime;
extern f32 D_8010FAF8_chancetime;
extern f32 D_8010FAFC_chancetime;
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

void func_80106320_chancetime(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 6, 10, -1, NULL);
    D_801100C0_chancetime.obj = obj;
    chr = GwPlayer[D_801100D0_chancetime[0]].chr;

    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    func_8001C814_main(obj->model[1], 2, 2);
    Hu3DModelPosSet(obj->model[1], 360.0f, 0.0f, -50.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, -90.0f, 0.0f);
    func_8001C258_main(obj->model[1], 4, 4);
    Hu3DModelCameraSet(obj->model[1], 2);

    obj->model[2] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(obj->model[2], 360.0f, -10.0f, -50.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 1.0f, 1.0f);
    func_8001C258_main(obj->model[2], 4, 4);
    Hu3DModelCameraSet(obj->model[2], 2);

    obj->model[3] = func_8000B108_main(0x1C000B, 0x2B9);
    Hu3DModelPosSet(obj->model[3], 180.0f, 220.0f, 0.0f);
    func_8001C814_main(obj->model[3], 2, 0);
    Hu3DModelScaleSet(obj->model[3], 0.7f, 0.7f, 0.7f);
    func_8001C258_main(obj->model[3], 4, 4);
    Hu3DModelCameraSet(obj->model[3], 2);

    obj->model[4] = func_8000B108_main(0x5D0008, 0x2B9);
    Hu3DModelPosSet(obj->model[4], 180.0f, 220.0f, 0.0f);
    func_8001C258_main(obj->model[4], 4, 4);

    D_8010FE7A_chancetime[0] = func_80017790_main(obj->model[1], 2, chr, func_80017BB8_main(chr, 0xA4));
    D_8010FE7A_chancetime[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_8010FE7A_chancetime[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA6));
    func_8001C514_main(obj->model[1]);
    func_80017954_main(obj->model[1], 2, GwPlayer[D_801100D0_chancetime[0]].chr, D_8010FE7A_chancetime[0]);

    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x36));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x36));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x2B));
    func_8000B460_main(obj, 6, func_80017BB8_main(chr, 0x1F));
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);

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
        Hu3DMotionShiftSet(object->model[1], HmfModelData[object->motion[0]].motId, 0, 30, 2);
        Hu3DModelScaleSet(object->model[3], 0.2f, 0.2f, 0.2f);
        func_8001C814_main(object->model[3], 2, 0);
        func_8001C814_main(object->model[3], 1, 1);
        func_8001C258_main(object->model[3], 4, 0);
        Hu3DModelPosSet(object->model[4], HmfModelData[object->model[3]].pos.x, HmfModelData[object->model[3]].pos.y,
                        HmfModelData[object->model[3]].pos.z);
        func_8001C258_main(object->model[4], 4, 0);
        func_8001C814_main(object->model[4], 2, 0);
        func_8001C814_main(object->model[4], 1, 0);
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

#ifdef NON_MATCHING
// Loop/branch ordering differs: GCC moves the CPU-player branch of the first loop after the loop.
void func_80106BEC_chancetime(omObjData *object) {
    s8 player = D_801100D0_chancetime[0];
    f32 time;
    s16 done;

    D_8010FAF0_chancetime = 0;
    while (TRUE) {
        if (GwPlayer[player].stat & 1) {
            HuPrcSleep((u8)(rand8() % 15) + 15);
            break;
        }
        if (D_800D5558_main[GwPlayer[player].pad] & 0x8000) {
            break;
        }
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(object->model[1], HmfModelData[object->motion[5]].motId, 0, 20, 0);
    Hu3DMotionSpeedSet(object->model[1], 3.0f);
    done = FALSE;
    do {
        time = Hu3DMotionShiftTimeGet(object->model[1]);
        if (done == FALSE) {
            if (time >= 5.0f) {
                done = TRUE;
                func_8010D92C_chancetime(D_8010FE78_chancetime);
                func_8001C814_main(object->model[3], 2, 0);
                func_8001C814_main(object->model[3], 1, 0);
                Hu3DMotionTimeSet(object->model[3], 0.0f);
                Hu3DMotionSpeedSet(object->model[3], 1.2f);
                func_8001C258_main(object->model[3], 4, 0);
            }
        }
        HuPrcVSleep();
    } while (time >= 0.0f);
    Hu3DMotionShiftSet(object->model[1], HmfModelData[object->motion[6]].motId, 0, 20, 0);
    Hu3DMotionSpeedSet(object->model[1], 3.0f);
    do {
        time = Hu3DMotionShiftTimeGet(object->model[1]);
        HuPrcVSleep();
    } while (time >= 0.0f);
    time = 0.0f;
    Hu3DModelPosSet(object->model[1], 180.0f, time, -50.0f);
    Hu3DModelPosSet(object->model[3], 180.0f, 220.0f, time);
    Hu3DMotionShiftSet(object->model[1], HmfModelData[object->motion[0]].motId, 0, 20, 2);
    Hu3DMotionSpeedSet(object->model[1], 1.0f);
    D_8010FAF0_chancetime = 1;
    D_801100C0_chancetime.func = func_80106760_chancetime;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4822F0", func_80106BEC_chancetime);
#endif

void func_80106F10_chancetime(void) {
    omObjData *object = D_801100C0_chancetime.obj;
    f32 time;
    f32 length;

    HuAudFXPlay(0x502);
    CharFXPlay(0x274, GwPlayer[D_801100D0_chancetime[0]].chr);
    func_80017954_main(object->model[1], 2, GwPlayer[D_801100D0_chancetime[0]].chr, D_8010FE7A_chancetime[1]);
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
    func_80017954_main(object->model[1], 2, GwPlayer[D_801100D0_chancetime[0]].chr, D_8010FE7A_chancetime[2]);
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
    func_80017954_main(object->model[1], 2, GwPlayer[D_801100D0_chancetime[0]].chr, D_8010FE7A_chancetime[2]);
    Hu3DMotionShiftSet(object->model[1], HmfModelData[object->motion[4]].motId, 0, 30, 0);
    HuPrcSleep(30);
    do {
        time = HmfModelData[object->model[1]].motTime;
        length = D_800CCF58_main[HmfModelData[object->model[1]].motId].unk02;
        HuPrcVSleep();
    } while (time < length);
}
