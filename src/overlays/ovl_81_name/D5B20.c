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

Object *D_801011F0_name_81 = NULL;
Process *D_801011F4_name_81 = NULL;
s16 D_801011F8_name_81 = -1;
s32 D_801011FC_name_81 = 1;
s32 D_80101200_name_81[] = { 0x1C00, 0x1C01, 0x1C02, 0x1C03, 0x1C04, 0x1C05, 0x1C06, 0x1C07 }; /* Unreferenced. */

Object *func_800EDD50_name_81(Vec *pos) {
    D_801011F0_name_81 = func_800D8010_name_81(0x3B, NULL);
    HuVecCopy3F(&D_801011F0_name_81->coords, pos);
    D_801011F0_name_81->flags |= 1;
    func_800461B4_main(D_801011F0_name_81->omObj1->model[0]);
    return D_801011F0_name_81;
}

void func_800EDDBC_name_81(void) {
    func_80046558_main(D_801011F0_name_81->omObj1->model[0]);
    MBDModelKill(D_801011F0_name_81);
    if (D_801011F8_name_81 != -1) {
        func_8000D044_main(D_801011F8_name_81);
        D_801011F8_name_81 = -1;
    }
}

void func_800EDE1C_name_81(void) {
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

Process *func_800EDEC4_name_81(Object *obj, f32 arg1, f32 arg2) {
    Process *prc = omAddPrcObj(func_800EDE1C_name_81, 0xA, 0, 0x40);
    UnkNameWobbleData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkNameWobbleData));

    prc->user_data = data;
    data->obj = obj;
    data->unk_04 = arg1;
    data->unk_08 = arg2;
    data->unk_0C = obj->velocity.x;
    return prc;
}

void func_800EDF48_name_81(void) {
    D_801011F4_name_81 = func_800EDEC4_name_81(D_801011F0_name_81, 5.0f, 2.0f);
}

void func_800EDF78_name_81(void) {
    if (D_801011F4_name_81 != NULL) {
        omDelPrcObj(D_801011F4_name_81);
        D_801011F4_name_81 = NULL;
    }
}

void func_800EDFAC_name_81(s32 arg0) {
    if (D_801011FC_name_81 != 0) {
        HuAudFXPlay(0x1EA);
    }
    switch (arg0) {
        case 0:
            D_801011F0_name_81->velocity.x = 70.0f;
            do {
                D_801011F0_name_81->velocity.x -= 2.0f;
                HuPrcVSleep();
            } while (D_801011F0_name_81->velocity.x >= 30.0f);
            break;
        case 1:
            D_801011F0_name_81->velocity.x = 120.0f;
            do {
                D_801011F0_name_81->velocity.x -= 2.5f;
                HuPrcVSleep();
            } while (D_801011F0_name_81->velocity.x >= 30.0f);
            break;
    }
}

void func_800EE0D0_name_81(s32 arg0) {
    D_801011FC_name_81 = 1;
    func_800EDFAC_name_81(arg0);
}

void func_800EE0F4_name_81(s32 arg0) {
    D_801011FC_name_81 = 0;
    func_800EDFAC_name_81(arg0);
}

void func_800EE114_name_81(void) {
    UnkNameProcData *data = HuPrcCurrentGet()->user_data;
    HmfModel *model;
    f32 step;
    f32 angle;
    f32 zero;
    s32 i;

    switch (data->unk_00) {
        case 0:
            while (D_801011F0_name_81->velocity.x <= 70.0f) {
                D_801011F0_name_81->velocity.x += 2.0f;
                HuPrcVSleep();
            }
            break;
        case 1:
            while (D_801011F0_name_81->velocity.x <= 120.0f) {
                D_801011F0_name_81->velocity.x += 2.5f;
                D_801011F0_name_81->coords.x += 2.5f;
                HuPrcVSleep();
            }
            break;
        case 2:
            step = 3.0f;
            angle = 0.0f;
            for (i = 0; i < 35; i++) {
                D_801011F0_name_81->velocity.x += step;
                step -= 0.2f;
                D_801011F0_name_81->coords.x += 2.0f;
                if (i >= 11) {
                    sincosdf(angle, &Hu3DData[D_801011F0_name_81->omObj1->model[0]].mtx[0][1],
                             &Hu3DData[D_801011F0_name_81->omObj1->model[0]].mtx[0][0]);
                    Hu3DData[D_801011F0_name_81->omObj1->model[0]].mtx[1][0] =
                        -Hu3DData[D_801011F0_name_81->omObj1->model[0]].mtx[0][1];
                    model = &Hu3DData[D_801011F0_name_81->omObj1->model[0]];
                    model->mtx[1][1] = model->mtx[0][0];
                    model = &Hu3DData[D_801011F0_name_81->omObj1->model[0]];
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
                    model = &Hu3DData[D_801011F0_name_81->omObj1->model[0]];
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

Process *func_800EE40C_name_81(s32 arg0) {
    Process *prc = omAddPrcObj(func_800EE114_name_81, 0xA, 0, 0x40);
    UnkNameProcData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkNameProcData));

    prc->user_data = data;
    data->unk_00 = arg0;
    return prc;
}

void func_800EE468_name_81(s32 arg0) {
    HmfModel *model;
    f32 step;
    f32 angle;
    f32 zero;
    s32 i;

    switch (arg0) {
        case 0:
            while (D_801011F0_name_81->velocity.x <= 70.0f) {
                D_801011F0_name_81->velocity.x += 4.0f;
                HuPrcVSleep();
            }
            break;
        case 1:
            while (D_801011F0_name_81->velocity.x <= 120.0f) {
                D_801011F0_name_81->velocity.x += 2.5f;
                D_801011F0_name_81->coords.x += 2.5f;
                HuPrcVSleep();
            }
            break;
        case 2:
            step = 3.0f;
            angle = 0.0f;
            for (i = 0; i < 35; i++) {
                D_801011F0_name_81->velocity.x += step;
                step -= 0.2f;
                D_801011F0_name_81->coords.x += 2.0f;
                if (i >= 11) {
                    sincosdf(angle, &Hu3DData[D_801011F0_name_81->omObj1->model[0]].mtx[0][1],
                             &Hu3DData[D_801011F0_name_81->omObj1->model[0]].mtx[0][0]);
                    Hu3DData[D_801011F0_name_81->omObj1->model[0]].mtx[1][0] =
                        -Hu3DData[D_801011F0_name_81->omObj1->model[0]].mtx[0][1];
                    model = &Hu3DData[D_801011F0_name_81->omObj1->model[0]];
                    model->mtx[1][1] = model->mtx[0][0];
                    model = &Hu3DData[D_801011F0_name_81->omObj1->model[0]];
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
                    model = &Hu3DData[D_801011F0_name_81->omObj1->model[0]];
                    model->mtx[3][3] = 1.0f;
                    model->mtx[2][2] = 1.0f;
                    angle -= 3.0f;
                }
                HuPrcVSleep();
            }
            break;
    }
}

void func_800EE74C_name_81(s32 arg0) {
    Vec pos;
    f32 angle;
    s32 i;

    switch (arg0) {
        case 0:
            D_801011F8_name_81 = func_8000CED8_main(0xB0004, 0xAA9);
            Hu3DModelCameraSet(D_801011F8_name_81, 1);
            func_8000CD00_main(D_801011F8_name_81, 1.0f, 30.0f, 1.0f);
            func_8000D018_main(D_801011F8_name_81, 10.0f);
            HuVecCopy3F(&pos, &D_801011F0_name_81->coords);
            angle = MBDVecAngleGet(&D_801011F0_name_81->rot);
            for (i = 0; i <= 720; i += 15) {
                func_8000CFA4_main(D_801011F8_name_81, D_801011F0_name_81->coords.x, D_801011F0_name_81->velocity.x,
                                   D_801011F0_name_81->coords.z);
                HuVecCopyXYZ(&D_801011F0_name_81->coords, sindf(i) * 12.0f + pos.x, pos.y, cosdf(i) * 2.0f + pos.z);
                D_801011F0_name_81->rot.z = cosdf(i * 3 + angle);
                D_801011F0_name_81->rot.x = sindf(i * 3 + angle);
                HuPrcVSleep();
            }
            break;
        case 1:
            D_801011F8_name_81 = func_8000CED8_main(0xB0004, 0xAA9);
            Hu3DModelCameraSet(D_801011F8_name_81, 1);
            func_8000CD00_main(D_801011F8_name_81, 1.0f, 30.0f, 1.0f);
            func_8000D018_main(D_801011F8_name_81, 10.0f);
            angle = MBDVecAngleGet(&D_801011F0_name_81->rot);
            for (i = 0; i <= 720; i += 15) {
                func_8000CFA4_main(D_801011F8_name_81, D_801011F0_name_81->coords.x, D_801011F0_name_81->velocity.x,
                                   D_801011F0_name_81->coords.z);
                D_801011F0_name_81->rot.z = cosdf(i * 3 + angle);
                D_801011F0_name_81->rot.x = sindf(i * 3 + angle);
                HuPrcVSleep();
            }
            break;
        case 2:
            angle = MBDVecAngleGet(&D_801011F0_name_81->rot);
            for (i = 0; i <= 720; i += 15) {
                D_801011F0_name_81->rot.z = cosdf(i * 3 + angle);
                D_801011F0_name_81->rot.x = sindf(i * 3 + angle);
                HuPrcVSleep();
            }
            break;
        case 3:
            D_801011F8_name_81 = func_8000CED8_main(0xB000C, 0xAA9);
            Hu3DModelCameraSet(D_801011F8_name_81, 1);
            func_8000CD00_main(D_801011F8_name_81, 0.3f, 30.0f, 1.0f);
            func_8000D018_main(D_801011F8_name_81, 10.0f);
            angle = MBDVecAngleGet(&D_801011F0_name_81->rot);
            for (i = 0; i <= 720; i += 15) {
                func_8000CFA4_main(D_801011F8_name_81, D_801011F0_name_81->coords.x, D_801011F0_name_81->velocity.x,
                                   D_801011F0_name_81->coords.z);
                D_801011F0_name_81->rot.z = cosdf(i * 3 + angle);
                D_801011F0_name_81->rot.x = sindf(i * 3 + angle);
                HuPrcVSleep();
            }
            break;
        case 4:
            D_801011F8_name_81 = func_8000CED8_main(0xB0005, 0xAA9);
            Hu3DModelCameraSet(D_801011F8_name_81, 1);
            func_8000CD00_main(D_801011F8_name_81, 1.0f, 30.0f, 1.0f);
            func_8000D018_main(D_801011F8_name_81, 10.0f);
            angle = MBDVecAngleGet(&D_801011F0_name_81->rot);
            for (i = 0; i <= 720; i += 15) {
                func_8000CFA4_main(D_801011F8_name_81, D_801011F0_name_81->coords.x, D_801011F0_name_81->velocity.x,
                                   D_801011F0_name_81->coords.z);
                D_801011F0_name_81->rot.z = cosdf(i * 3 + angle);
                D_801011F0_name_81->rot.x = sindf(i * 3 + angle);
                HuPrcVSleep();
            }
            break;
    }
    if (D_801011F8_name_81 != -1) {
        func_8000D044_main(D_801011F8_name_81);
        D_801011F8_name_81 = -1;
    }
}

Object *func_800EEC40_name_81(Vec *pos) {
    D_801011F0_name_81 = func_800D8010_name_81(0x3E, NULL);
    MBDModelTempAllocFree(D_801011F0_name_81);
    HuVecCopy3F(&D_801011F0_name_81->coords, pos);
    D_801011F0_name_81->velocity.x = 120.0f;
    do {
        D_801011F0_name_81->velocity.x -= 2.5f;
        HuPrcVSleep();
    } while (D_801011F0_name_81->velocity.x >= 30.0f);
    D_801011F4_name_81 = func_800EDEC4_name_81(D_801011F0_name_81, 5.0f, 2.0f);
    return D_801011F0_name_81;
}

Object *func_800EED24_name_81(void) {
    return D_801011F0_name_81;
}
