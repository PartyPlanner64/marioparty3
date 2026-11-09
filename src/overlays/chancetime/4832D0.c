#include "common.h"
#include "chancetime.h"

extern s32 D_8010FB00_chancetime;
extern s32 D_8010FB04_chancetime;
extern s32 D_8010FB08_chancetime;
extern Vec D_8010FB0C_chancetime;
extern Vec D_8010FB18_chancetime[4];
extern Vec D_8010FB48_chancetime;
extern Vec D_8010FB54_chancetime;
extern s32 D_8010FB60_chancetime;
extern f32 D_8010FB64_chancetime;
extern s32 D_8010FB68_chancetime;
extern f32 D_8010FB6C_chancetime;
extern f32 D_8010FB70_chancetime;
extern f32 D_8010FB74_chancetime;
extern f32 D_8010FB78_chancetime;
extern f32 D_8010FB7C_chancetime;
extern char D_8010FC80_chancetime[];
extern char D_8010FC8C_chancetime[];
extern s16 D_8010FE80_chancetime[];
extern s16 D_8010FE8A_chancetime;
extern s16 D_8010FE8E_chancetime;
extern ChanceTimeObjState D_80110088_chancetime[];
extern ChanceTimeObjState D_801100B0_chancetime;
extern ChanceTimeObjState D_801100B8_chancetime;
extern ChanceTimeObjState D_801100D4_chancetime;

void func_80107B18_chancetime(omObjData *object);
void func_80107C84_chancetime(omObjData *object);
void func_80107D60_chancetime(omObjData *object);
void func_80108738_chancetime(omObjData *object);
void func_80107E40_chancetime(omObjData *object);
void func_80107F58_chancetime(omObjData *object);
void func_801080EC_chancetime(omObjData *object);
void func_8010827C_chancetime(omObjData *object);
void func_80108414_chancetime(omObjData *object);
void func_80108C08_chancetime(s16 model, s16 slot, s16 animIdx);
s32 func_8010B6F4_chancetime(s16 arg0);
void func_8010B7A0_chancetime(s16 arg0);
void func_8010B818_chancetime(omObjData *object, Vec *pos, s32 arg2);
void func_8010B834_chancetime(omObjData *object, Vec *pos, s32 time, s32 faceDir);
void func_8010BA68_chancetime(omObjData *object, Vec *rot, s32 time);
void func_8010BC10_chancetime(omObjData *object, f32 x, f32 y, f32 z, s32 arg4);
void func_8010BC88_chancetime(omObjData *object, f32 x, f32 y, f32 z, s32 arg4);
void func_8010AA90_chancetime(omObjData *object);
void func_80108EDC_chancetime(omObjData *object);
void func_8010963C_chancetime(omObjData *object);
void func_80109B70_chancetime(omObjData *object);
void func_8010A0A4_chancetime(omObjData *object);
void func_8010A5D8_chancetime(omObjData *object);
void func_8010B124_chancetime(omObjData *object);
void func_8010BD40_chancetime(void);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80107300_chancetime);

void func_80107A80_chancetime(omObjData *object) {
}

void func_80107A88_chancetime(omObjData *object) {
}

void func_80107A90_chancetime(void) {
}

void func_80107A98_chancetime(omObjData *object) {
    func_8001C5B4_main(object->model[1], object->motion[2]);
    func_8001C814_main(object->model[1], 2, 0);
    func_8001C5B4_main(object->model[3], object->motion[2]);
    func_8001C814_main(object->model[3], 2, 0);
    D_801100D4_chancetime.func = func_80107B18_chancetime;
}

void func_80107B18_chancetime(omObjData *object) {
    D_8010FB64_chancetime += 8.0f;
    Hu3DModelRotSet(object->model[1], 0.0f, D_8010FB64_chancetime, 0.0f);
    Hu3DModelRotSet(object->model[3], 0.0f, -D_8010FB64_chancetime, 0.0f);
    if (D_8010FB64_chancetime >= 45.0f) {
        D_8010FB64_chancetime = 45.0f;
        Hu3DModelRotSet(object->model[1], 0.0f, D_8010FB64_chancetime, 0.0f);
        Hu3DModelRotSet(object->model[3], 0.0f, -D_8010FB64_chancetime, 0.0f);
        if (D_800CCF58_main[HmfModelData[object->model[1]].motId].unk02 <= HmfModelData[object->model[1]].motTime) {
            D_801100D4_chancetime.func = func_80107C84_chancetime;
            D_8010FB64_chancetime = 0.0f;
        }
    }
}

void func_80107C84_chancetime(omObjData *object) {
    Hu3DMotionShiftSet(object->model[1], HmfModelData[object->motion[3]].motId, 0, 30, 2);
    func_8001C814_main(object->model[5], 1, 0);
    Hu3DMotionShiftSet(object->model[3], HmfModelData[object->motion[3]].motId, 0, 30, 2);
    func_8001C814_main(object->model[6], 1, 0);
    D_801100D4_chancetime.func = func_80107D60_chancetime;
}

void func_80107D60_chancetime(omObjData *object) {
    if (Hu3DMotionShiftTimeGet(object->model[1]) >= 5.0f) {
        Hu3DModelHookSet(object->model[5], object->model[1], D_8010FC8C_chancetime);
        func_8001C258_main(object->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        func_8001C814_main(object->model[5], 1, 0);
        Hu3DModelHookSet(object->model[6], object->model[3], D_8010FC8C_chancetime);
        func_8001C258_main(object->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        func_8001C814_main(object->model[6], 1, 0);
        func_80108738_chancetime(object);
        D_801100D4_chancetime.func = func_80107A80_chancetime;
    }
}

void func_80107E40_chancetime(omObjData *object) {
    func_8001C814_main(object->model[5], 1, 1);
    func_8001C814_main(object->model[6], 1, 1);
    Hu3DMotionTimeSet(object->model[5], 0.0f);
    Hu3DMotionTimeSet(object->model[6], 0.0f);
    func_8001C814_main(object->model[5], 2, 0);
    func_8001C814_main(object->model[6], 2, 0);
    Hu3DMotionShiftSet(object->model[1], HmfModelData[object->motion[2]].motId, 0, 30, 0);
    Hu3DMotionShiftSet(object->model[3], HmfModelData[object->motion[2]].motId, 0, 30, 0);
    D_801100D4_chancetime.func = func_80107F58_chancetime;
}

void func_80107F58_chancetime(omObjData *object) {
    f32 time = Hu3DMotionShiftTimeGet(object->model[1]);

    if (D_8010FB68_chancetime == 0) {
        if (time >= 20.0f) {
            func_8001C258_main(object->model[5], 0x4000, 0);
            func_8001C258_main(object->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            func_8001C258_main(object->model[6], 0x4000, 0);
            func_8001C258_main(object->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            func_80108738_chancetime(object);
            D_8010FB68_chancetime = 1;
        }
    }
    if (time < 0.0f) {
        Hu3DMotionShiftSet(object->model[1], HmfModelData[object->motion[0]].motId, 0, 30, 2);
        Hu3DMotionShiftSet(object->model[3], HmfModelData[object->motion[1]].motId, 0, 30, 2);
        D_8010FB68_chancetime = 0;
        func_80108C08_chancetime(object->model[1], D_8010FE8E_chancetime, D_8010FE8A_chancetime);
        D_801100D4_chancetime.func = func_801080EC_chancetime;
    }
}

void func_801080EC_chancetime(omObjData *object) {
    s8 count = 0;

    D_8010FB6C_chancetime += 8.0f;
    if (D_8010FB6C_chancetime >= 45.0f) {
        D_8010FB6C_chancetime = 45.0f;
        count++;
    }
    Hu3DModelRotSet(object->model[1], 0.0f, 45.0f - D_8010FB6C_chancetime, 0.0f);
    D_8010FB70_chancetime += 8.0f;
    if (D_8010FB70_chancetime >= 135.0f) {
        D_8010FB70_chancetime = 135.0f;
        count++;
    }
    Hu3DModelRotSet(object->model[3], 0.0f, D_8010FB70_chancetime + -45.0f, 0.0f);
    if (count >= 2) {
        Hu3DMotionShiftSet(object->model[3], HmfModelData[object->motion[1]].motId, 0, 30, 2);
        D_8010FB6C_chancetime = D_8010FB70_chancetime = 0.0f;
        D_801100D4_chancetime.func = func_8010827C_chancetime;
    }
}

void func_8010827C_chancetime(omObjData *object) {
    s8 count = 0;

    D_8010FB74_chancetime += 30.0f;
    if (D_8010FB74_chancetime >= 250.0f) {
        D_8010FB74_chancetime = 250.0f;
        count++;
    }
    Hu3DModelPosSet(object->model[3], D_8010FB74_chancetime + 200.0f, 0.0f, -50.0f);
    Hu3DModelPosSet(object->model[4], D_8010FB74_chancetime + 200.0f, -5.0f, -50.0f);
    if (count == 1) {
        D_8010FB74_chancetime = 0.0f;
        func_8001C258_main(object->model[3], 4, 4);
        func_8001C258_main(object->model[4], 4, 4);
        func_80106B18_chancetime();
        Hu3DMotionShiftSet(object->model[1], HmfModelData[object->motion[5]].motId, 0, 30, 2);
        Hu3DMotionShiftSet(object->model[3], HmfModelData[object->motion[5]].motId, 0, 30, 2);
        D_801100D4_chancetime.func = func_80107A88_chancetime;
    }
}

void func_80108414_chancetime(omObjData *object) {
    Hu3DModelPosSet(object->model[1], -200.0f, sindf(D_8010FB78_chancetime * 18.0f) * 50.0f, -50.0f);
    Hu3DModelPosSet(object->model[3], 200.0f, sindf(D_8010FB78_chancetime * 18.0f) * 50.0f, -50.0f);
    D_8010FB78_chancetime += 1.0f;
    if (D_8010FB78_chancetime >= 10.0f) {
        D_8010FB78_chancetime = 0.0f;
        Hu3DModelPosSet(object->model[1], -200.0f, 0.0f, -50.0f);
        Hu3DModelPosSet(object->model[3], 200.0f, 0.0f, -50.0f);
        Hu3DModelPosSet(object->model[2], -200.0f, 0.0f, -50.0f);
        Hu3DModelPosSet(object->model[4], 200.0f, 0.0f, -50.0f);
        D_8010FB00_chancetime = 0;
        D_8010FB04_chancetime = 1;
        D_801100D4_chancetime.func = func_80107A80_chancetime;
    }
}

void func_80108578_chancetime(omObjData *object) {
    Hu3DModelPosSet(object->model[1], -200.0f, sindf(D_8010FB7C_chancetime * 36.0f) * 20.0f, -50.0f);
    Hu3DModelPosSet(object->model[3], 200.0f, sindf(D_8010FB7C_chancetime * 36.0f) * 20.0f, -50.0f);
    D_8010FB7C_chancetime += 1.0f;
    if (D_8010FB7C_chancetime >= 5.0f) {
        D_8010FB7C_chancetime = 0.0f;
        Hu3DModelPosSet(object->model[1], -200.0f, 0.0f, -50.0f);
        Hu3DModelPosSet(object->model[3], 200.0f, 0.0f, -50.0f);
        Hu3DModelPosSet(object->model[2], -200.0f, 0.0f, -50.0f);
        Hu3DModelPosSet(object->model[4], 200.0f, 0.0f, -50.0f);
        D_8010FB00_chancetime = 0;
        D_8010FB04_chancetime = 1;
        D_801100D4_chancetime.func = func_80107A80_chancetime;
    }
}

void func_801086DC_chancetime(void) {
    D_801100D4_chancetime.func = func_80107A98_chancetime;
}

void func_801086F0_chancetime(void) {
    D_801100D4_chancetime.func = func_80107E40_chancetime;
}

void func_80108704_chancetime(void) {
    D_8010FB00_chancetime = 1;
    D_8010FB04_chancetime = 0;
    D_801100D4_chancetime.func = func_80108414_chancetime;
}

s32 func_8010872C_chancetime(void) {
    return D_8010FB04_chancetime;
}

void func_80108738_chancetime(omObjData *object) {
    HuMtx4F mtx;
    Vec pos;
    f32 time;
    f32 rot;

    time = HmfModelData[object->model[1]].motTime;
    func_80016B00_main(object->model[1], time, D_8010FC8C_chancetime, &mtx);
    rot = -HmfModelData[object->model[1]].rot.y;
    pos.x = cosdf(rot) * mtx[3][0] - sindf(rot) * mtx[3][2];
    pos.y = mtx[3][1];
    pos.z = sindf(rot) * mtx[3][0] + cosdf(rot) * mtx[3][2];
    Hu3DModelPosSet(object->model[7], HmfModelData[object->model[1]].pos.x + pos.x,
                    HmfModelData[object->model[1]].pos.y + pos.y - 100.0f,
                    HmfModelData[object->model[1]].pos.z + pos.z + 80.0f);
    func_8001C258_main(object->model[7], 4, 0);
    func_8001C814_main(object->model[7], 2, 0);
    func_8001C814_main(object->model[7], 1, 0);
    func_80014714_main(D_8010FE80_chancetime[0], 0);

    time = HmfModelData[object->model[3]].motTime;
    func_80016B00_main(object->model[3], time, D_8010FC8C_chancetime, &mtx);
    rot = -HmfModelData[object->model[3]].rot.y;
    pos.x = cosdf(rot) * mtx[3][0] - sindf(rot) * mtx[3][2];
    pos.y = mtx[3][1];
    pos.z = sindf(rot) * mtx[3][0] + cosdf(rot) * mtx[3][2];
    Hu3DModelPosSet(object->model[8], HmfModelData[object->model[3]].pos.x + pos.x,
                    HmfModelData[object->model[3]].pos.y + pos.y - 100.0f,
                    HmfModelData[object->model[3]].pos.z + pos.z + 80.0f);
    func_8001C258_main(object->model[8], 4, 0);
    func_8001C814_main(object->model[8], 2, 0);
    func_8001C814_main(object->model[8], 1, 0);
    func_80014714_main(D_8010FE80_chancetime[1], 0);
}

void func_80108A88_chancetime(void) {
    omObjData *object = D_801100D4_chancetime.obj;

    Hu3DMotionShiftSet(object->model[1], HmfModelData[object->motion[5]].motId, 0, 30, 2);
    Hu3DMotionShiftSet(object->model[3], HmfModelData[object->motion[5]].motId, 0, 30, 2);
    D_8010FB08_chancetime = 0;
    D_801100D4_chancetime.func = func_80107A88_chancetime;
}

void func_80108B50_chancetime(void) {
    omObjData *object = D_801100D4_chancetime.obj;

    D_801100D4_chancetime.func = func_80107A80_chancetime;
    Hu3DMotionShiftSet(object->model[1], HmfModelData[object->motion[4]].motId, 0, 30, 2);
    Hu3DMotionShiftSet(object->model[3], HmfModelData[object->motion[4]].motId, 0, 30, 2);
}

void func_80108C08_chancetime(s16 model, s16 slot, s16 animIdx) {
    if (slot >= 0) {
        if (animIdx == -1) {
            func_80033910_main(HmfModelData[model].hmf);
        } else {
            HmfAnim *anim;

            func_80033970_main(HmfModelData[model].hmf);
            anim = &D_800D1714_main[slot];
            anim->animIdx = animIdx;
            anim->rot = 0;
            anim->flags = 0;
            anim->interp = 0;
            anim->frame = 0;
        }
    }
}

void func_80108CDC_chancetime(void) {
    omObjData *object;
    omObjData *motObj;
    void *data;
    s32 anim;

    object = omAddObj(20, 4, 0, -1, NULL);
    D_80110088_chancetime[0].obj = object;
    motObj = D_801100D4_chancetime.obj;
    object->model[1] = func_8000B108_main(0xA0000, 0x2A9);
    Hu3DModelPosSet(object->model[1], D_8010FB0C_chancetime.x, D_8010FB0C_chancetime.y, D_8010FB0C_chancetime.z);
    Hu3DModelCameraSet(object->model[1], 2);
    data = DataRead(0xA002A);
    anim = (s16)HmfAnimCreate(HmfModelData[object->model[1]].hmf, data, 0, D_8010FC80_chancetime);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(object->model[1]);
    func_8001C514_main(object->model[1]);
    func_80032FC0_main(anim, 1, 0);
    func_80032FF8_main(anim, 0);
    object->model[2] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(object->model[2], D_8010FB0C_chancetime.x, D_8010FB0C_chancetime.y, D_8010FB0C_chancetime.z);
    Hu3DModelCameraSet(object->model[2], 2);
    Hu3DMotionShiftSet(object->model[1], HmfModelData[motObj->motion[0]].motId, 0, 30, 2);
    func_8001C258_main(object->model[2], 4, 4);
    D_80110088_chancetime[0].func = func_80108EDC_chancetime;
    while (TRUE) {
        D_80110088_chancetime[0].func(object);
        HuPrcVSleep();
    }
}

void func_80108EDC_chancetime(omObjData *object) {
    s16 model = object->model[1];
    omObjData *motObj = D_801100D4_chancetime.obj;
    Vec unusedPos;
    f32 y;
    f32 speed;
    s32 i;
    s32 j;

    HuPrcSleep(5);
    HuPrcSleep(2);
    y = HmfModelData[model].pos.y;
    for (i = 0; i < 3; i++) {
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[12]].motId, 0, 10, 0);
        for (j = 0; j < 9; j++) {
            HmfModelData[model].pos.y = y + sindf(j * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    HmfModelData[model].pos.y = y;
    Hu3DMotionShiftSet(object->model[1], HmfModelData[motObj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(3);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[5]].motId, 0, 10, 0);
            Hu3DMotionSpeedSet(model, 1.5f);
            func_8010B7A0_chancetime(model);
        }
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[6]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        func_8010B7A0_chancetime(model);
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[7]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        func_8010B7A0_chancetime(model);
    }
    HuPrcSleep(1);
    Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[8]].motId, 0, 10, 0);
    HuPrcSleep(20);
    omAddPrcObj(func_8010BD40_chancetime, 0x1001, 0x2000, 0);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(object->model[1], HmfModelData[motObj->motion[12]].motId, 0, 10, 0);
    // Copied but never read in the original.
    unusedPos.x = HmfModelData[model].pos.x;
    unusedPos.y = HmfModelData[model].pos.y;
    unusedPos.z = HmfModelData[model].pos.z;
    (void)unusedPos;
    speed = 20.0f;
    while (TRUE) {
        HmfModelData[model].pos.y += speed;
        HmfModelData[model].pos.z += 20.0f;
        if (HmfModelData[model].pos.z >= -250.0f) {
            HmfModelData[object->model[2]].pos.x = HmfModelData[model].pos.x;
            HmfModelData[object->model[2]].pos.y = 0.0f;
            HmfModelData[object->model[2]].pos.z = HmfModelData[model].pos.z;
            func_8001C258_main(object->model[2], HU3D_ATTR_DISPOFF, 0);
        }
        if (HmfModelData[model].pos.y <= 0.0f) {
            break;
        }
        speed -= 3.0f;
        HuPrcVSleep();
    }
    HmfModelData[model].pos.y = 0.0f;
    HmfModelData[object->model[2]].pos.x = HmfModelData[model].pos.x;
    HmfModelData[object->model[2]].pos.y = 0.0f;
    HmfModelData[object->model[2]].pos.z = HmfModelData[model].pos.z;
    Hu3DMotionShiftSet(object->model[1], HmfModelData[motObj->motion[1]].motId, 0, 10, 2);
    func_8010BC88_chancetime(object, 0.0f, 0.0f, 500.0f, 5);
    func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_80110088_chancetime[0].func = func_80107A80_chancetime;
}

void func_801094CC_chancetime(void) {
    omObjData *obj;
    omObjData *motObj;
    omObjData *srcObj;

    obj = omAddObj(20, 4, 0, -1, NULL);
    D_80110088_chancetime[1].obj = obj;
    motObj = D_801100D4_chancetime.obj;
    srcObj = D_80110088_chancetime[0].obj;
    obj->model[1] = Hu3DModelLink(srcObj->model[1]);
    Hu3DModelPosSet(obj->model[1], D_8010FB18_chancetime[0].x, D_8010FB18_chancetime[0].y, D_8010FB18_chancetime[0].z);
    Hu3DModelCameraSet(obj->model[1], 2);
    obj->model[2] = Hu3DModelLink(srcObj->model[2]);
    Hu3DModelPosSet(obj->model[2], D_8010FB18_chancetime[0].x, D_8010FB18_chancetime[0].y, D_8010FB18_chancetime[0].z);
    Hu3DModelCameraSet(obj->model[2], 2);
    Hu3DMotionShiftSet(obj->model[1], HmfModelData[motObj->motion[0]].motId, 0, 10, 2);
    func_8001C258_main(obj->model[2], 4, 0);
    D_80110088_chancetime[1].func = func_8010963C_chancetime;
    while (TRUE) {
        D_80110088_chancetime[1].func(obj);
        HuPrcVSleep();
    }
}

void func_8010963C_chancetime(omObjData *object) {
    s16 model = object->model[1];
    omObjData *motObj = D_801100D4_chancetime.obj;
    f32 y;
    s32 i;
    s32 j;

    HuPrcSleep(5);
    HuPrcSleep(4);
    y = HmfModelData[model].pos.y;
    for (i = 0; i < 3; i++) {
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[12]].motId, 0, 10, 0);
        for (j = 0; j < 9; j++) {
            HmfModelData[model].pos.y = y + sindf(j * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    HmfModelData[model].pos.y = y;
    Hu3DMotionShiftSet(object->model[1], HmfModelData[motObj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(1);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[5]].motId, 0, 10, 0);
            Hu3DMotionSpeedSet(model, 1.5f);
            func_8010B7A0_chancetime(model);
        }
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[6]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        func_8010B7A0_chancetime(model);
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[7]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        func_8010B7A0_chancetime(model);
    }
    HuPrcSleep(1);
    Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[9]].motId, 0, 10, 0);
    HuPrcSleep(50);
    Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[1]].motId, 0, 10, 2);
    func_8010BC88_chancetime(object, -400.0f, 0.0f, 300.0f, 10);
    func_8001C258_main(object->model[1], 4, 4);
    func_8001C258_main(object->model[2], 4, 4);
    D_80110088_chancetime[1].func = func_80107A80_chancetime;
}

void func_80109A00_chancetime(void) {
    omObjData *obj;
    omObjData *motObj;
    omObjData *srcObj;

    obj = omAddObj(20, 4, 0, -1, NULL);
    D_80110088_chancetime[2].obj = obj;
    motObj = D_801100D4_chancetime.obj;
    srcObj = D_80110088_chancetime[0].obj;
    obj->model[1] = Hu3DModelLink(srcObj->model[1]);
    Hu3DModelPosSet(obj->model[1], D_8010FB18_chancetime[1].x, D_8010FB18_chancetime[1].y, D_8010FB18_chancetime[1].z);
    Hu3DModelCameraSet(obj->model[1], 2);
    obj->model[2] = Hu3DModelLink(srcObj->model[2]);
    Hu3DModelPosSet(obj->model[2], D_8010FB18_chancetime[1].x, D_8010FB18_chancetime[1].y, D_8010FB18_chancetime[1].z);
    Hu3DModelCameraSet(obj->model[2], 2);
    Hu3DMotionShiftSet(obj->model[1], HmfModelData[motObj->motion[0]].motId, 0, 10, 2);
    func_8001C258_main(obj->model[2], 4, 0);
    D_80110088_chancetime[2].func = func_80109B70_chancetime;
    while (TRUE) {
        D_80110088_chancetime[2].func(obj);
        HuPrcVSleep();
    }
}

void func_80109B70_chancetime(omObjData *object) {
    s16 model = object->model[1];
    omObjData *motObj = D_801100D4_chancetime.obj;
    f32 y;
    s32 i;
    s32 j;

    HuPrcSleep(5);
    HuPrcSleep(1);
    y = HmfModelData[model].pos.y;
    for (i = 0; i < 3; i++) {
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[12]].motId, 0, 10, 0);
        for (j = 0; j < 9; j++) {
            HmfModelData[model].pos.y = y + sindf(j * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    HmfModelData[model].pos.y = y;
    Hu3DMotionShiftSet(object->model[1], HmfModelData[motObj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(4);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[5]].motId, 0, 10, 0);
            Hu3DMotionSpeedSet(model, 1.5f);
            func_8010B7A0_chancetime(model);
        }
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[6]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        func_8010B7A0_chancetime(model);
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[7]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        func_8010B7A0_chancetime(model);
    }
    HuPrcSleep(1);
    Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[9]].motId, 0, 10, 0);
    HuPrcSleep(50);
    Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[1]].motId, 0, 10, 2);
    func_8010BC88_chancetime(object, -200.0f, 0.0f, 300.0f, 10);
    func_8001C258_main(object->model[1], 4, 4);
    func_8001C258_main(object->model[2], 4, 4);
    D_80110088_chancetime[2].func = func_80107A80_chancetime;
}

void func_80109F34_chancetime(void) {
    omObjData *obj;
    omObjData *motObj;
    omObjData *srcObj;

    obj = omAddObj(20, 4, 0, -1, NULL);
    D_80110088_chancetime[3].obj = obj;
    motObj = D_801100D4_chancetime.obj;
    srcObj = D_80110088_chancetime[0].obj;
    obj->model[1] = Hu3DModelLink(srcObj->model[1]);
    Hu3DModelPosSet(obj->model[1], D_8010FB18_chancetime[2].x, D_8010FB18_chancetime[2].y, D_8010FB18_chancetime[2].z);
    Hu3DModelCameraSet(obj->model[1], 2);
    obj->model[2] = Hu3DModelLink(srcObj->model[2]);
    Hu3DModelPosSet(obj->model[2], D_8010FB18_chancetime[2].x, D_8010FB18_chancetime[2].y, D_8010FB18_chancetime[2].z);
    Hu3DModelCameraSet(obj->model[2], 2);
    Hu3DMotionShiftSet(obj->model[1], HmfModelData[motObj->motion[0]].motId, 0, 10, 2);
    func_8001C258_main(obj->model[2], 4, 0);
    D_80110088_chancetime[3].func = func_8010A0A4_chancetime;
    while (TRUE) {
        D_80110088_chancetime[3].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A0A4_chancetime(omObjData *object) {
    s16 model = object->model[1];
    omObjData *motObj = D_801100D4_chancetime.obj;
    f32 y;
    s32 i;
    s32 j;

    HuPrcSleep(5);
    HuPrcSleep(3);
    y = HmfModelData[model].pos.y;
    for (i = 0; i < 3; i++) {
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[12]].motId, 0, 10, 0);
        for (j = 0; j < 9; j++) {
            HmfModelData[model].pos.y = y + sindf(j * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    HmfModelData[model].pos.y = y;
    Hu3DMotionShiftSet(object->model[1], HmfModelData[motObj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(2);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[5]].motId, 0, 10, 0);
            Hu3DMotionSpeedSet(model, 1.5f);
            func_8010B7A0_chancetime(model);
        }
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[6]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        func_8010B7A0_chancetime(model);
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[7]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        func_8010B7A0_chancetime(model);
    }
    HuPrcSleep(1);
    Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[10]].motId, 0, 10, 0);
    HuPrcSleep(50);
    Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[1]].motId, 0, 10, 2);
    func_8010BC88_chancetime(object, 200.0f, 0.0f, 300.0f, 10);
    func_8001C258_main(object->model[1], 4, 4);
    func_8001C258_main(object->model[2], 4, 4);
    D_80110088_chancetime[3].func = func_80107A80_chancetime;
}

void func_8010A468_chancetime(void) {
    omObjData *obj;
    omObjData *motObj;
    omObjData *srcObj;

    obj = omAddObj(20, 4, 0, -1, NULL);
    D_80110088_chancetime[4].obj = obj;
    motObj = D_801100D4_chancetime.obj;
    srcObj = D_80110088_chancetime[0].obj;
    obj->model[1] = Hu3DModelLink(srcObj->model[1]);
    Hu3DModelPosSet(obj->model[1], D_8010FB18_chancetime[3].x, D_8010FB18_chancetime[3].y, D_8010FB18_chancetime[3].z);
    Hu3DModelCameraSet(obj->model[1], 2);
    obj->model[2] = Hu3DModelLink(srcObj->model[2]);
    Hu3DModelPosSet(obj->model[2], D_8010FB18_chancetime[3].x, D_8010FB18_chancetime[3].y, D_8010FB18_chancetime[3].z);
    Hu3DModelCameraSet(obj->model[2], 2);
    Hu3DMotionShiftSet(obj->model[1], HmfModelData[motObj->motion[0]].motId, 0, 10, 2);
    func_8001C258_main(obj->model[2], 4, 0);
    D_80110088_chancetime[4].func = func_8010A5D8_chancetime;
    while (TRUE) {
        D_80110088_chancetime[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A5D8_chancetime(omObjData *object) {
    s16 model = object->model[1];
    omObjData *motObj = D_801100D4_chancetime.obj;
    f32 y;
    s32 i;
    s32 j;

    HuPrcSleep(5);
    HuPrcSleep(4);
    y = HmfModelData[model].pos.y;
    for (i = 0; i < 3; i++) {
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[12]].motId, 0, 10, 0);
        for (j = 0; j < 9; j++) {
            HmfModelData[model].pos.y = y + sindf(j * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    HmfModelData[model].pos.y = y;
    Hu3DMotionShiftSet(object->model[1], HmfModelData[motObj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(1);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[5]].motId, 0, 10, 0);
            Hu3DMotionSpeedSet(model, 1.5f);
            func_8010B7A0_chancetime(model);
        }
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[6]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        func_8010B7A0_chancetime(model);
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[7]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        func_8010B7A0_chancetime(model);
    }
    HuPrcSleep(1);
    Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[10]].motId, 0, 10, 0);
    HuPrcSleep(50);
    Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[1]].motId, 0, 10, 2);
    func_8010BC88_chancetime(object, 400.0f, 0.0f, 300.0f, 10);
    func_8001C258_main(object->model[1], 4, 4);
    func_8001C258_main(object->model[2], 4, 4);
    D_80110088_chancetime[4].func = func_80107A80_chancetime;
}

void func_8010A99C_chancetime(void) {
    omObjData *parent = D_801100D4_chancetime.obj;
    omObjData *object = omAddObj(20, 4, 0, -1, NULL);

    D_801100B0_chancetime.obj = object;
    object->model[1] = parent->model[1];
    object->model[2] = parent->model[2];
    Hu3DModelPosSet(object->model[1], D_8010FB48_chancetime.x, D_8010FB48_chancetime.y, D_8010FB48_chancetime.z);
    Hu3DModelPosSet(object->model[2], D_8010FB48_chancetime.x, D_8010FB48_chancetime.y, D_8010FB48_chancetime.z);
    func_8001C258_main(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801100B0_chancetime.func = func_8010AA90_chancetime;
    while (TRUE) {
        D_801100B0_chancetime.func(object);
        HuPrcVSleep();
    }
}

void func_8010AA90_chancetime(omObjData *object) {
    s16 model = D_801100D4_chancetime.obj->model[1];
    omObjData *motObj = D_801100D4_chancetime.obj;
    Vec unusedPos;
    f32 y;
    f32 speed;
    s32 i;
    s32 j;

    HuPrcSleep(5);
    HuPrcSleep(3);
    y = HmfModelData[model].pos.y;
    for (i = 0; i < 3; i++) {
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[12]].motId, 0, 10, 0);
        for (j = 0; j < 9; j++) {
            HmfModelData[model].pos.y = y + sindf(j * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    HmfModelData[model].pos.y = y;
    Hu3DMotionShiftSet(object->model[1], HmfModelData[motObj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(2);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[5]].motId, 0, 10, 0);
            Hu3DMotionSpeedSet(model, 1.5f);
            func_8010B7A0_chancetime(model);
        }
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[6]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        func_8010B7A0_chancetime(model);
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[7]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        func_8010B7A0_chancetime(model);
    }
    HuPrcSleep(1);
    Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[9]].motId, 0, 10, 0);
    HuPrcSleep(42);
    Hu3DMotionShiftSet(object->model[1], HmfModelData[motObj->motion[12]].motId, 0, 10, 0);
    // Copied but never read in the original.
    unusedPos.x = HmfModelData[model].pos.x;
    unusedPos.y = HmfModelData[model].pos.y;
    unusedPos.z = HmfModelData[model].pos.z;
    (void)unusedPos;
    speed = 20.0f;
    while (TRUE) {
        HmfModelData[model].pos.y += speed;
        HmfModelData[model].pos.z += 10.0f;
        if (HmfModelData[model].pos.z >= -250.0f) {
            HmfModelData[object->model[2]].pos.x = HmfModelData[model].pos.x;
            HmfModelData[object->model[2]].pos.y = 0.0f;
            HmfModelData[object->model[2]].pos.z = HmfModelData[model].pos.z;
            func_8001C258_main(object->model[2], HU3D_ATTR_DISPOFF, 0);
        }
        if (HmfModelData[model].pos.y <= 0.0f) {
            break;
        }
        speed -= 2.0f;
        HuPrcVSleep();
    }
    HmfModelData[model].pos.y = 0.0f;
    HmfModelData[object->model[2]].pos.x = HmfModelData[model].pos.x;
    HmfModelData[object->model[2]].pos.y = 0.0f;
    HmfModelData[object->model[2]].pos.z = HmfModelData[model].pos.z;
    Hu3DMotionShiftSet(object->model[1], HmfModelData[motObj->motion[5]].motId, 0, 10, 2);
    D_8010FB60_chancetime = 1;
    D_801100B0_chancetime.func = func_80107A80_chancetime;
}

void func_8010B030_chancetime(void) {
    omObjData *parent = D_801100D4_chancetime.obj;
    omObjData *object = omAddObj(20, 4, 0, -1, NULL);

    D_801100B8_chancetime.obj = object;
    object->model[1] = parent->model[3];
    object->model[2] = parent->model[4];
    Hu3DModelPosSet(object->model[1], D_8010FB54_chancetime.x, D_8010FB54_chancetime.y, D_8010FB54_chancetime.z);
    Hu3DModelPosSet(object->model[2], D_8010FB54_chancetime.x, D_8010FB54_chancetime.y, D_8010FB54_chancetime.z);
    func_8001C258_main(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801100B8_chancetime.func = func_8010B124_chancetime;
    while (TRUE) {
        D_801100B8_chancetime.func(object);
        HuPrcVSleep();
    }
}

void func_8010B124_chancetime(omObjData *object) {
    s16 model = D_801100D4_chancetime.obj->model[3];
    omObjData *motObj = D_801100D4_chancetime.obj;
    Vec unusedPos;
    f32 y;
    f32 speed;
    s32 i;
    s32 j;

    HuPrcSleep(5);
    HuPrcSleep(4);
    y = HmfModelData[model].pos.y;
    for (i = 0; i < 3; i++) {
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[12]].motId, 0, 10, 0);
        for (j = 0; j < 9; j++) {
            HmfModelData[model].pos.y = y + sindf(j * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    HmfModelData[model].pos.y = y;
    Hu3DMotionShiftSet(object->model[1], HmfModelData[motObj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(1);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[5]].motId, 0, 10, 0);
            Hu3DMotionSpeedSet(model, 1.5f);
            func_8010B7A0_chancetime(model);
        }
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[6]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        func_8010B7A0_chancetime(model);
        Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[7]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        func_8010B7A0_chancetime(model);
    }
    HuPrcSleep(1);
    Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[10]].motId, 0, 10, 0);
    HuPrcSleep(42);
    Hu3DMotionShiftSet(object->model[1], HmfModelData[motObj->motion[12]].motId, 0, 10, 0);
    // Copied but never read in the original.
    unusedPos.x = HmfModelData[model].pos.x;
    unusedPos.y = HmfModelData[model].pos.y;
    unusedPos.z = HmfModelData[model].pos.z;
    (void)unusedPos;
    speed = 20.0f;
    while (TRUE) {
        HmfModelData[model].pos.y += speed;
        HmfModelData[model].pos.z += 10.0f;
        if (HmfModelData[model].pos.z >= -250.0f) {
            HmfModelData[object->model[2]].pos.x = HmfModelData[model].pos.x;
            HmfModelData[object->model[2]].pos.y = 0.0f;
            HmfModelData[object->model[2]].pos.z = HmfModelData[model].pos.z;
            func_8001C258_main(object->model[2], HU3D_ATTR_DISPOFF, 0);
        }
        if (HmfModelData[model].pos.y <= 0.0f) {
            break;
        }
        speed -= 3.0f;
        HuPrcVSleep();
    }
    HmfModelData[model].pos.y = 0.0f;
    HmfModelData[object->model[2]].pos.x = HmfModelData[model].pos.x;
    HmfModelData[object->model[2]].pos.y = 0.0f;
    HmfModelData[object->model[2]].pos.z = HmfModelData[model].pos.z;
    Hu3DMotionShiftSet(model, HmfModelData[motObj->motion[1]].motId, 0, 10, 2);
    func_8010BC88_chancetime(object, 400.0f, 0.0f, 300.0f, 10);
    func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801100B8_chancetime.func = func_80107A80_chancetime;
}

s32 func_8010B6F4_chancetime(s16 model) {
    f32 time = Hu3DMotionShiftTimeGet(model);
    s32 ret = 0;

    if (time == -1.0f && D_800CCF58_main[HmfModelData[model].motId].unk02 <= HmfModelData[model].motTime) {
        ret = -1;
    }
    return ret;
}

void func_8010B7A0_chancetime(s16 arg0) {
    HuPrcSleep(15);
    while (!func_8010B6F4_chancetime(arg0)) {
        HuPrcVSleep();
    }
}

void func_8010B7EC_chancetime(omObjData *object, f32 x, f32 y, f32 z, s32 arg4) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_8010B818_chancetime(object, &pos, arg4);
}

void func_8010B818_chancetime(omObjData *object, Vec *pos, s32 arg2) {
    func_8010B834_chancetime(object, pos, arg2, 1);
}

void func_8010B834_chancetime(omObjData *object, Vec *pos, s32 time, s32 faceDir) {
    Vec start;
    Vec diff;
    Vec step;
    Vec cur;
    s16 model = object->model[1];
    f32 i;

    start.x = HmfModelData[model].pos.x;
    start.y = HmfModelData[model].pos.y;
    start.z = HmfModelData[model].pos.z;
    diff.x = pos->x - start.x;
    diff.y = pos->y - start.y;
    diff.z = pos->z - start.z;
    if (faceDir != 0) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(diff.z, diff.x) - 90.0f), 0.0f);
    }
    i = time;
    step.x = diff.x / i;
    step.y = diff.y / i;
    step.z = diff.z / i;
    for (i = 0.0f; i < (f32)time; i += 1.0f) {
        cur.x = i * step.x + start.x;
        cur.y = i * step.y + start.y;
        cur.z = i * step.z + start.z;
        Hu3DModelPosSet(model, cur.x, cur.y, cur.z);
        if (object->model[2] >= 0) {
            Hu3DModelPosSet(object->model[2], cur.x, 0.0f, cur.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    if (object->model[2] >= 0) {
        Hu3DModelPosSet(object->model[2], pos->x, 0.0f, pos->z);
    }
    HuPrcVSleep();
}

void func_8010BA68_chancetime(omObjData *object, Vec *rot, s32 time) {
    Vec start;
    Vec diff;
    Vec cur;
    s16 model = object->model[1];
    f32 i;
    f32 t;

    start.x = HmfModelData[model].rot.x;
    start.y = HmfModelData[model].rot.y;
    start.z = HmfModelData[model].rot.z;
    diff.x = rot->x - start.x;
    diff.y = rot->y - start.y;
    diff.z = rot->z - start.z;
    for (i = 0.0f; i < (f32)time; i += 1.0f) {
        t = 90.0f / time * i;
        cur.x = sindf(t) * diff.x + start.x;
        cur.y = sindf(t) * diff.y + start.y;
        cur.z = sindf(t) * diff.z + start.z;
        Hu3DModelRotSet(model, cur.x, cur.y, cur.z);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, rot->x, rot->y, rot->z);
    HuPrcVSleep();
}

void func_8010BC10_chancetime(omObjData *object, f32 x, f32 y, f32 z, s32 arg4) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_8010BA68_chancetime(object, &pos, arg4);
}

f32 func_8010BC3C_chancetime(Vec *from, Vec *to) {
    Vec diff;

    diff.x = to->x - from->x;
    diff.z = to->z - from->z;
    return -(atan2df(diff.z, diff.x) - 90.0f);
}

void func_8010BC88_chancetime(omObjData *object, f32 x, f32 y, f32 z, s32 arg4) {
    Vec from;
    Vec to;
    s16 modelId = object->model[1];

    from.x = HmfModelData[modelId].pos.x;
    from.y = HmfModelData[modelId].pos.y;
    from.z = HmfModelData[modelId].pos.z;
    to.x = x;
    to.y = y;
    to.z = z;
    func_8010BC10_chancetime(object, 0.0f, func_8010BC3C_chancetime(&from, &to), 0.0f, 10);
    func_8010B818_chancetime(object, &to, arg4);
}

void func_8010BD40_chancetime(void) {
    s16 anim;
    s16 sprite;
    f32 scale;
    s32 i;

    scale = 0.0f;
    anim = func_8000B838_main(0x1C0006);
    sprite = espEntry(anim, 0, 0);
    espPosSet(sprite, 160, 120);
    espDispOff(sprite);
    espScaleSet(sprite, scale, scale);
    espDispOn(sprite);
    for (i = 0; i < 5; i++) {
        scale = sindf(i * 18.0f) * 1.2f;
        espScaleSet(sprite, scale, scale);
        HuPrcVSleep();
    }
    HuAudFXPlay(0x261);
    scale = 1.0f;
    espScaleSet(sprite, scale, scale);
    HuPrcSleep(30);
    for (i = 0; i < 20; i++) {
        espScaleSet(sprite, scale, scale);
        scale = sindf(i * 4.5f);
        espTPLvlSet(sprite, 256.0f - scale * 256.0f);
        scale += 1.0f;
        HuPrcVSleep();
    }
    espDispOn(sprite);
    espKill(sprite);
    HuSprAnimKill(anim);
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 func_8010BF3C_chancetime(void) {
    return D_8010FB60_chancetime;
}

void func_8010BF48_chancetime(void) {
    omObjData *object = D_801100D4_chancetime.obj;

    func_8010BC10_chancetime(object, 0.0f, 45.0f, 0.0f, 10);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/4832D0", D_8010FC80_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/4832D0", D_8010FC8C_chancetime);
