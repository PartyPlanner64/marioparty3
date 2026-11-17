#include "common_duel.h"
#include "ovl_81.h"

typedef struct UnkNameProcData {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} UnkNameProcData; // sizeof 0x10

typedef struct UnkNameWobbleData {
    /* 0x00 */ Object *obj;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
} UnkNameWobbleData; // sizeof 0x10

Object *mbdAuraObj = NULL;
Process *mbdAuraHoverProc = NULL;
s16 mbdAuraEffNo = -1;
s32 mbdAuraSeF = 1;
s32 mbdAuraMesTbl[] = { 0x1C00, 0x1C01, 0x1C02, 0x1C03, 0x1C04, 0x1C05, 0x1C06, 0x1C07 }; /* Unreferenced. */

Object *MBDAuraCreate(Vec *pos) {
    mbdAuraObj = MBDModelCreate(0x3B, NULL);
    HuVecCopy3F(&mbdAuraObj->coords, pos);
    mbdAuraObj->flags |= 1;
    AuraCreate(mbdAuraObj->omObj1->model[0]);
    return mbdAuraObj;
}

void MBDAuraKill(void) {
    AuraKill(mbdAuraObj->omObj1->model[0]);
    MBDModelKill(mbdAuraObj);
    if (mbdAuraEffNo != -1) {
        EffectStop(mbdAuraEffNo);
        mbdAuraEffNo = -1;
    }
}

void MBDModelHoverProc(void) {
    UnkNameWobbleData *data = HuPrcCurrentGet()->user_data;
    Object *obj = data->obj;
    f32 speed = data->unk_04;
    f32 amplitude = data->unk_08;
    f32 base = data->unk_0C;
    f32 angle = 0.0f;

    while (1) {
        f32 value = base - (sindf(angle) * amplitude);
        angle += speed;
        obj->velocity.x = value;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        HuPrcVSleep();
    }
}

Process *MBDModelHoverCreate(Object *obj, f32 arg1, f32 arg2) {
    Process *prc = omAddPrcObj(MBDModelHoverProc, 0xA, 0, 0x40);
    UnkNameWobbleData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkNameWobbleData));

    prc->user_data = data;
    data->obj = obj;
    data->unk_04 = arg1;
    data->unk_08 = arg2;
    data->unk_0C = obj->velocity.x;
    return prc;
}

void MBDAuraHoverStart(void) {
    mbdAuraHoverProc = MBDModelHoverCreate(mbdAuraObj, 5.0f, 2.0f);
}

void MBDAuraHoverStop(void) {
    if (mbdAuraHoverProc != NULL) {
        omDelPrcObj(mbdAuraHoverProc);
        mbdAuraHoverProc = NULL;
    }
}

void MBDAuraLandExec(s32 arg0) {
    if (mbdAuraSeF != 0) {
        HuAudFXPlay(0x1EA);
    }
    switch (arg0) {
        case 0:
            mbdAuraObj->velocity.x = 70.0f;
            do {
                mbdAuraObj->velocity.x -= 2.0f;
                HuPrcVSleep();
            } while (mbdAuraObj->velocity.x >= 30.0f);
            break;
        case 1:
            mbdAuraObj->velocity.x = 120.0f;
            do {
                mbdAuraObj->velocity.x -= 2.5f;
                HuPrcVSleep();
            } while (mbdAuraObj->velocity.x >= 30.0f);
            break;
    }
}

void MBDAuraLand(s32 arg0) {
    mbdAuraSeF = 1;
    MBDAuraLandExec(arg0);
}

void MBDAuraLandNoSe(s32 arg0) {
    mbdAuraSeF = 0;
    MBDAuraLandExec(arg0);
}

void MBDAuraRiseProc(void) {
    UnkNameProcData *data = HuPrcCurrentGet()->user_data;
    HmfModel *model;
    f32 step;
    f32 angle;
    f32 zero;
    s32 i;

    switch (data->unk_00) {
        case 0:
            while (mbdAuraObj->velocity.x <= 70.0f) {
                mbdAuraObj->velocity.x += 2.0f;
                HuPrcVSleep();
            }
            break;
        case 1:
            while (mbdAuraObj->velocity.x <= 120.0f) {
                mbdAuraObj->velocity.x += 2.5f;
                mbdAuraObj->coords.x += 2.5f;
                HuPrcVSleep();
            }
            break;
        case 2:
            step = 3.0f;
            angle = 0.0f;
            for (i = 0; i < 35; i++) {
                mbdAuraObj->velocity.x += step;
                step -= 0.2f;
                mbdAuraObj->coords.x += 2.0f;
                if (i >= 11) {
                    sincosdf(angle, &Hu3DData[mbdAuraObj->omObj1->model[0]].mtx[0][1],
                             &Hu3DData[mbdAuraObj->omObj1->model[0]].mtx[0][0]);
                    Hu3DData[mbdAuraObj->omObj1->model[0]].mtx[1][0] =
                        -Hu3DData[mbdAuraObj->omObj1->model[0]].mtx[0][1];
                    model = &Hu3DData[mbdAuraObj->omObj1->model[0]];
                    model->mtx[1][1] = model->mtx[0][0];
                    model = &Hu3DData[mbdAuraObj->omObj1->model[0]];
                    zero = 0.0f;
                    model->mtx[3][2] = zero;
                    model->mtx[3][1] = zero;
                    model->mtx[3][0] = zero;
                    model->mtx[2][3] = zero;
                    model->mtx[2][1] = zero;
                    model->mtx[2][0] = zero;
                    model->mtx[1][2] = zero;
                    model->mtx[1][3] = zero;
                    model->mtx[0][3] = zero;
                    model->mtx[0][2] = zero;
                    model = &Hu3DData[mbdAuraObj->omObj1->model[0]];
                    model->mtx[3][3] = 1.0f;
                    model->mtx[2][2] = 1.0f;
                    angle -= 3.0f;
                }
                HuPrcVSleep();
            }
            break;
    }
    omDelPrcObj(NULL);
}

Process *MBDAuraRiseCreate(s32 arg0) {
    Process *prc = omAddPrcObj(MBDAuraRiseProc, 0xA, 0, 0x40);
    UnkNameProcData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkNameProcData));

    prc->user_data = data;
    data->unk_00 = arg0;
    return prc;
}

void MBDAuraRiseExec(s32 arg0) {
    HmfModel *model;
    f32 step;
    f32 angle;
    f32 zero;
    s32 i;

    switch (arg0) {
        case 0:
            while (mbdAuraObj->velocity.x <= 70.0f) {
                mbdAuraObj->velocity.x += 4.0f;
                HuPrcVSleep();
            }
            break;
        case 1:
            while (mbdAuraObj->velocity.x <= 120.0f) {
                mbdAuraObj->velocity.x += 2.5f;
                mbdAuraObj->coords.x += 2.5f;
                HuPrcVSleep();
            }
            break;
        case 2:
            step = 3.0f;
            angle = 0.0f;
            for (i = 0; i < 35; i++) {
                mbdAuraObj->velocity.x += step;
                step -= 0.2f;
                mbdAuraObj->coords.x += 2.0f;
                if (i >= 11) {
                    sincosdf(angle, &Hu3DData[mbdAuraObj->omObj1->model[0]].mtx[0][1],
                             &Hu3DData[mbdAuraObj->omObj1->model[0]].mtx[0][0]);
                    Hu3DData[mbdAuraObj->omObj1->model[0]].mtx[1][0] =
                        -Hu3DData[mbdAuraObj->omObj1->model[0]].mtx[0][1];
                    model = &Hu3DData[mbdAuraObj->omObj1->model[0]];
                    model->mtx[1][1] = model->mtx[0][0];
                    model = &Hu3DData[mbdAuraObj->omObj1->model[0]];
                    zero = 0.0f;
                    model->mtx[3][2] = zero;
                    model->mtx[3][1] = zero;
                    model->mtx[3][0] = zero;
                    model->mtx[2][3] = zero;
                    model->mtx[2][1] = zero;
                    model->mtx[2][0] = zero;
                    model->mtx[1][2] = zero;
                    model->mtx[1][3] = zero;
                    model->mtx[0][3] = zero;
                    model->mtx[0][2] = zero;
                    model = &Hu3DData[mbdAuraObj->omObj1->model[0]];
                    model->mtx[3][3] = 1.0f;
                    model->mtx[2][2] = 1.0f;
                    angle -= 3.0f;
                }
                HuPrcVSleep();
            }
            break;
    }
}

void MBDAuraSpinExec(s32 arg0) {
    Vec pos;
    f32 angle;
    s32 i;

    switch (arg0) {
        case 0:
            mbdAuraEffNo = EffectCreate(0xB0004, 0xAA9);
            Hu3DModelCameraSet(mbdAuraEffNo, HU3D_CAM0);
            EffectParamSet(mbdAuraEffNo, 1.0f, 30.0f, 1.0f);
            EffectRangeSet(mbdAuraEffNo, 10.0f);
            HuVecCopy3F(&pos, &mbdAuraObj->coords);
            angle = MBDVecAngleGet(&mbdAuraObj->rot);
            for (i = 0; i <= 720; i += 15) {
                EffectPosSet(mbdAuraEffNo, mbdAuraObj->coords.x, mbdAuraObj->velocity.x,
                                   mbdAuraObj->coords.z);
                HuVecCopyXYZ(&mbdAuraObj->coords, sindf(i) * 12.0f + pos.x, pos.y, cosdf(i) * 2.0f + pos.z);
                mbdAuraObj->rot.z = cosdf(i * 3 + angle);
                mbdAuraObj->rot.x = sindf(i * 3 + angle);
                HuPrcVSleep();
            }
            break;
        case 1:
            mbdAuraEffNo = EffectCreate(0xB0004, 0xAA9);
            Hu3DModelCameraSet(mbdAuraEffNo, HU3D_CAM0);
            EffectParamSet(mbdAuraEffNo, 1.0f, 30.0f, 1.0f);
            EffectRangeSet(mbdAuraEffNo, 10.0f);
            angle = MBDVecAngleGet(&mbdAuraObj->rot);
            for (i = 0; i <= 720; i += 15) {
                EffectPosSet(mbdAuraEffNo, mbdAuraObj->coords.x, mbdAuraObj->velocity.x,
                                   mbdAuraObj->coords.z);
                mbdAuraObj->rot.z = cosdf(i * 3 + angle);
                mbdAuraObj->rot.x = sindf(i * 3 + angle);
                HuPrcVSleep();
            }
            break;
        case 2:
            angle = MBDVecAngleGet(&mbdAuraObj->rot);
            for (i = 0; i <= 720; i += 15) {
                mbdAuraObj->rot.z = cosdf(i * 3 + angle);
                mbdAuraObj->rot.x = sindf(i * 3 + angle);
                HuPrcVSleep();
            }
            break;
        case 3:
            mbdAuraEffNo = EffectCreate(0xB000C, 0xAA9);
            Hu3DModelCameraSet(mbdAuraEffNo, HU3D_CAM0);
            EffectParamSet(mbdAuraEffNo, 0.3f, 30.0f, 1.0f);
            EffectRangeSet(mbdAuraEffNo, 10.0f);
            angle = MBDVecAngleGet(&mbdAuraObj->rot);
            for (i = 0; i <= 720; i += 15) {
                EffectPosSet(mbdAuraEffNo, mbdAuraObj->coords.x, mbdAuraObj->velocity.x,
                                   mbdAuraObj->coords.z);
                mbdAuraObj->rot.z = cosdf(i * 3 + angle);
                mbdAuraObj->rot.x = sindf(i * 3 + angle);
                HuPrcVSleep();
            }
            break;
        case 4:
            mbdAuraEffNo = EffectCreate(0xB0005, 0xAA9);
            Hu3DModelCameraSet(mbdAuraEffNo, HU3D_CAM0);
            EffectParamSet(mbdAuraEffNo, 1.0f, 30.0f, 1.0f);
            EffectRangeSet(mbdAuraEffNo, 10.0f);
            angle = MBDVecAngleGet(&mbdAuraObj->rot);
            for (i = 0; i <= 720; i += 15) {
                EffectPosSet(mbdAuraEffNo, mbdAuraObj->coords.x, mbdAuraObj->velocity.x,
                                   mbdAuraObj->coords.z);
                mbdAuraObj->rot.z = cosdf(i * 3 + angle);
                mbdAuraObj->rot.x = sindf(i * 3 + angle);
                HuPrcVSleep();
            }
            break;
    }
    if (mbdAuraEffNo != -1) {
        EffectStop(mbdAuraEffNo);
        mbdAuraEffNo = -1;
    }
}

Object *MBDAuraAltCreate(Vec *pos) {
    mbdAuraObj = MBDModelCreate(0x3E, NULL);
    MBDModelTempAllocFree(mbdAuraObj);
    HuVecCopy3F(&mbdAuraObj->coords, pos);
    mbdAuraObj->velocity.x = 120.0f;
    do {
        mbdAuraObj->velocity.x -= 2.5f;
        HuPrcVSleep();
    } while (mbdAuraObj->velocity.x >= 30.0f);
    mbdAuraHoverProc = MBDModelHoverCreate(mbdAuraObj, 5.0f, 2.0f);
    return mbdAuraObj;
}

Object *MBDAuraObjGet(void) {
    return mbdAuraObj;
}
