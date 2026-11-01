#include "common.h"
#include "inst.h"

extern u8 D_800CB8B1_main[];
extern s8 D_8010D400_inst[4];
extern s8 D_8010D40A_inst;
extern u8 D_8010D554_inst[4];
extern s8 D_8010D40C_inst[5];
extern const char *D_8010D55C_inst[8];
extern s32 D_8010D57C_inst[4];
extern const char *D_8010D58C_inst[4];
extern s16 D_8010DC98_inst[4];
extern s32 D_8010D558_inst;
extern s32 D_8010D59C_inst;
extern s32 D_8010D5A0_inst;
extern f32 D_8010D414_inst;
extern omObjData *D_8010DC90_inst;
extern InstModelHooks *D_8010D4C0_inst[][2];
extern InstObjectState D_8010DDD8_inst;
extern HuMtx4F D_8010DC50_inst;
extern s8 D_8010D408_inst;
extern s8 D_8010D550_inst;
extern s8 D_8010D551_inst;
extern void (*D_8010DC94_inst)(omObjData *);

static const s32 D_8010D9C8_inst[] = {
    0x17002E, 0x17002F, 0x170030, 0x170031, 0x170032, 0x170033, 0x170034, 0x170035,
};
static const s32 D_8010D9E8_inst[] = {
    0x170038, 0x170039, 0x17003A, 0x17003B, 0x17003C, 0x17003D, 0x17003E, 0x17003F,
    0x170040, 0x170041, 0x170042, 0x170045, 0x170044, 0x170043, 0x170046,
};

const char D_8010DA24_inst[] = "y002_13-grid1";
const char D_8010DA34_inst[] = "y002_12-grid1";
const char D_8010DA44_inst[] = "y002_11-grid1";
const char D_8010DA54_inst[] = "y002_10-grid1";
const char D_8010DA64_inst[] = "y002_09-grid1";
const char D_8010DA74_inst[] = "y002_08-grid1";
const char D_8010DA84_inst[] = "y002_07-grid1";
const char D_8010DA94_inst[] = "y002_06-grid1";
const char D_8010DAA4_inst[] = "hook_last";
const char D_8010DAB0_inst[] = "hook_midori";
const char D_8010DABC_inst[] = "hook_aka";
const char D_8010DAC8_inst[] = "hook_ao";

s32 func_80107E20_inst(void);
void func_8010B040_inst(void);
void func_80017358_main(s16, const char *, s16, const char *);
u16 func_8000B0D4_main(s32 arg0, s32 arg1);
void func_801080FC_inst(void);
void func_8010AC04_inst(omObjData *object);
void func_8010B628_inst(omObjData *);
void func_80016B00_main(s16 model, s16 frame, char *name, HuMtx4F *out);
void func_8010A750_inst(omObjData *);
void func_8010AC30_inst(omObjData *); /* extern */
void func_8010AD78_inst(omObjData *);
void func_8010B038_inst(omObjData *object);
void func_8002367C_main(HuMtx4F, HuMtx4F);
void func_80018044_main(HuMtx4F, HuMtx4F, HuMtx4F);
void func_8010B2A4_inst(omObjData *);

void func_8010A1D0_inst(void) {
    omObjData *object;
    InstModelHooks *models;
    s32 i;
    s32 player;

    object = omAddObj(21, 30, 1, -1, NULL);
    D_8010DC90_inst = object;
    func_8010B040_inst();
    models = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < models->count; i++) {
        object->model[i + 1] = func_8000B0D4_main(D_8010D57C_inst[D_8010D554_inst[i]], 0x1AB9);
    }
    object->model[5] = func_8000B0D4_main(0x170036, 0x16B9);
    for (i = 1; i < models->count; i++) {
        object->model[i + 5] = Hu3DModelLink(object->model[5]);
    }
    for (i = 0; i < models->count; i++) {
        player = D_8010D400_inst[i];
        D_8010DC98_inst[i] = func_8000B0D4_main(D_8010D9C8_inst[GwPlayer[player].chr], 0x1AB9);
        func_80017358_main(D_8010DC98_inst[i], D_8010D55C_inst[GwPlayer[player].chr],
                           object->model[i + 1], D_8010D58C_inst[D_8010D554_inst[i]]);
        func_8001C258_main(D_8010DC98_inst[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DMotionTimeSet(object->model[i + 1], 0);
        func_8001C814_main(object->model[i + 1], 2, 0);
    }
    object->trans.x = 0;
    object->trans.y = 0;
    object->trans.z = 0;
    for (i = 0; i < models->count; i++) {
        Hu3DModelPosSet(object->model[i + 1], 0, 0, 0);
        Hu3DModelScaleSet(object->model[i + 1], 0.5f, 0.5f, 0.5f);
        func_8001C258_main(object->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        func_8001C814_main(object->model[i + 1], 1, 1);
        Hu3DModelPosSet(object->model[i + 5], 0, 0, 0);
        Hu3DModelScaleSet(object->model[i + 5], 0.5f, 0.5f, 0.5f);
        func_8001C258_main(object->model[i + 5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        func_8001C814_main(object->model[i + 5], 1, 1);
    }
    models = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < models->count; i++) {
        object->model[i + 10] = func_8000B0D4_main(D_8010D9E8_inst[D_8010D40C_inst[i]], 0x1AB9);
    }
    if (models->count > 0) {
        object->model[15] = func_8000B0D4_main(0x170037, 0x16B9);
        for (i = 1; i < models->count; i++) {
            object->model[i + 15] = Hu3DModelLink(object->model[15]);
        }
    }
    for (i = 0; i < models->count; i++) {
        Hu3DModelPosSet(object->model[i + 10], 0, 0, 0);
        Hu3DModelScaleSet(object->model[i + 10], 0.5f, 0.5f, 0.5f);
        func_8001C258_main(object->model[i + 10], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        func_8001C814_main(object->model[i + 10], 1, 1);
        Hu3DModelPosSet(object->model[i + 15], 0, 0, 0);
        Hu3DModelScaleSet(object->model[i + 15], 0.5f, 0.5f, 0.5f);
        func_8001C258_main(object->model[i + 15], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        func_8001C814_main(object->model[i + 15], 1, 1);
    }
    D_8010DC94_inst = func_8010A750_inst;
    while (1) {
        D_8010DC94_inst(object);
        HuPrcVSleep();
    }
}

void func_8010A750_inst(omObjData *object) {
    omObjData *source;
    HmfModel *model;
    f32 duration;
    f32 time;
    InstModelHooks *models;
    s8 i;

    source = D_8010DDD8_inst.object;
    duration = D_800CCF58_main[HmfModelData[source->model[0]].motId].unk02;
    time = HmfModelData[source->model[0]].motTime;
    models = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < models->count; i++) {
        model = &HmfModelData[object->model[i + 1]];
        func_80016B00_main(source->model[0], time, models->nodes[i], &model->mtx);
    }
    models = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < models->count; i++) {
        model = &HmfModelData[object->model[i + 10]];
        func_80016B00_main(source->model[0], time, models->nodes[i], &model->mtx);
    }
    if (func_80107E20_inst() == 1) {
        models = D_8010D4C0_inst[D_8010D40A_inst][0];
        for (i = 0; i < models->count; i++) {
            Hu3DMotionTimeSet(object->model[i + 1], 0);
            func_8001C814_main(object->model[i + 1], 1, 0);
            HmfModelData[object->model[i + 1]].rot.x = 0;
            func_80016B00_main(source->model[0], duration, models->nodes[i], &D_8010DC50_inst);
            Hu3DModelPosSet(object->model[i + 5], D_8010DC50_inst[3][0] * 0.5f, D_8010DC50_inst[3][1] * 0.5f,
                            D_8010DC50_inst[3][2] * 0.5f);
        }
        models = D_8010D4C0_inst[D_8010D40A_inst][1];
        for (i = 0; i < models->count; i++) {
            Hu3DMotionTimeSet(object->model[i + 10], 0);
            func_8001C814_main(object->model[i + 10], 1, 0);
            HmfModelData[object->model[i + 10]].rot.x = 0;
            func_80016B00_main(source->model[0], duration, models->nodes[i], &D_8010DC50_inst);
            Hu3DModelPosSet(object->model[i + 15], D_8010DC50_inst[3][0] * 0.5f, D_8010DC50_inst[3][1] * 0.5f,
                            D_8010DC50_inst[3][2] * 0.5f);
        }
        if (D_8010D558_inst == 0) {
            if (D_8010D408_inst == 0) {
                D_8010DC94_inst = func_8010AC04_inst;
            } else {
                D_8010DC94_inst = func_8010B628_inst;
            }
        } else {
            D_8010DC94_inst = func_8010B038_inst;
        }
    }
}

void func_8010AC04_inst(omObjData *object) {
    if (D_8010D550_inst == 1) {
        D_8010DC94_inst = func_8010AC30_inst;
    }
}

void func_8010AC30_inst(omObjData *object) {
    s32 i;
    InstModelHooks *models;

    models = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < models->count; i++) {
        func_8001C258_main(object->model[i + 5], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionTimeSet(object->model[i + 5], 0);
        func_8001C814_main(object->model[i + 5], 1, 0);
    }
    models = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < models->count; i++) {
        func_8001C258_main(object->model[i + 15], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionTimeSet(object->model[i + 15], 0);
        func_8001C814_main(object->model[i + 15], 1, 0);
    }
    D_8010DC94_inst = func_8010AD78_inst;
}

void func_8010AD78_inst(omObjData *object) {
    HuMtx4F rotation;
    HuMtx4F matrix;
    f32 duration;
    InstModelHooks *models;
    s8 i;

    duration = D_800CCF58_main[HmfModelData[object->model[5]].motId].unk02 - 20.0f;
    models = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < models->count; i++) {
        func_8008A120_main(rotation, (1.0f / duration) * D_8010D414_inst);
        func_8002367C_main(matrix, HmfModelData[object->model[i + 1]].mtx);
        func_80018044_main(rotation, matrix, HmfModelData[object->model[i + 1]].mtx);
    }
    models = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < models->count; i++) {
        func_8008A120_main(rotation, (1.0f / duration) * D_8010D414_inst);
        func_8002367C_main(matrix, HmfModelData[object->model[i + 10]].mtx);
        func_80018044_main(rotation, matrix, HmfModelData[object->model[i + 10]].mtx);
    }
    D_8010D59C_inst++;
    if (D_8010D59C_inst >= duration) {
        D_8010DC94_inst = func_8010B038_inst;
        D_8010D551_inst = 1;
        D_8010D59C_inst = 0;
    }
}

void func_8010B038_inst(omObjData *object) {
}

void func_8010B040_inst(void) {
    s32 i;

    switch (D_8010D40A_inst) {
        case 0:
        case 1:
        case 2:
            for (i = 0; i < 4; i++) {
                if (D_800CB8B1_main[D_8010D400_inst[i]] == 0) {
                    D_8010D554_inst[i] = 0;
                } else {
                    D_8010D554_inst[i] = 1;
                }
            }
            break;
        case 3:
        case 4:
        case 5:
        case 7:
            D_8010D554_inst[0] = 2;
            D_8010D554_inst[1] = 2;
            D_8010D554_inst[2] = 2;
            D_8010D554_inst[3] = 2;
            break;
        case 8:
            D_8010D554_inst[0] = 3;
            D_8010D554_inst[1] = 3;
            D_8010D554_inst[2] = 3;
            D_8010D554_inst[3] = 3;
            break;
    }
}

void func_8010B0FC_inst(void) {
    D_8010D550_inst = 1;
}

s32 func_8010B10C_inst(void) {
    return D_8010D550_inst;
}

s32 func_8010B118_inst(void) {
    return D_8010D551_inst;
}

void func_8010B124_inst(void) {
    s8 i;
    omObjData *object = D_8010DC90_inst;
    InstModelHooks *models;

    D_8010D558_inst = 1;
    models = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < models->count; i++) {
        func_8001C814_main(object->model[i + 5], 1, 0);
        func_8001C814_main(object->model[i + 5], 4, 4);
        func_8001C258_main(object->model[i + 5], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
    models = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < models->count; i++) {
        func_8001C814_main(object->model[i + 15], 1, 0);
        func_8001C814_main(object->model[i + 15], 4, 4);
        func_8001C258_main(object->model[i + 15], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
    D_8010DC94_inst = func_8010B2A4_inst;
}

void func_8010B2A4_inst(omObjData *object) {
    HuMtx4F rotation;
    HuMtx4F matrix;
    f32 duration;
    InstModelHooks *models;
    s8 i;

    duration = D_800CCF58_main[HmfModelData[object->model[5]].motId].unk02 - 20.0f;
    models = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < models->count; i++) {
        func_8008A120_main(rotation, (1.0f / duration) * D_8010D414_inst);
        func_8002367C_main(matrix, HmfModelData[object->model[i + 1]].mtx);
        func_80018044_main(rotation, matrix, HmfModelData[object->model[i + 1]].mtx);
    }
    models = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < models->count; i++) {
        func_8008A120_main(rotation, (1.0f / duration) * D_8010D414_inst);
        func_8002367C_main(matrix, HmfModelData[object->model[i + 10]].mtx);
        func_80018044_main(rotation, matrix, HmfModelData[object->model[i + 10]].mtx);
    }
    D_8010D5A0_inst++;
    if (D_8010D5A0_inst == duration) {
        models = D_8010D4C0_inst[D_8010D40A_inst][0];
        for (i = 0; i < models->count; i++) {
            func_8001C258_main(object->model[i + 5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
        models = D_8010D4C0_inst[D_8010D40A_inst][1];
        for (i = 0; i < models->count; i++) {
            func_8001C258_main(object->model[i + 15], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
        func_801080FC_inst();
        D_8010DC94_inst = func_8010A750_inst;
        D_8010D5A0_inst = 0;
    }
}

void func_8010B628_inst(omObjData *object) {
    HuMtx4F rotation;
    HuMtx4F matrix;
    f32 duration;
    InstModelHooks *models;
    s32 i;

    duration = D_800CCF58_main[HmfModelData[object->model[5]].motId].unk02;
    models = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < models->count; i++) {
        func_8001C258_main(object->model[i + 5], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionTimeSet(object->model[i + 5], duration);
        func_8001C814_main(object->model[i + 5], 1, 0);
    }
    models = D_8010D4C0_inst[D_8010D40A_inst][1];
    duration = D_800CCF58_main[HmfModelData[object->model[15]].motId].unk02;
    for (i = 0; i < models->count; i++) {
        func_8001C258_main(object->model[i + 15], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionTimeSet(object->model[i + 15], duration);
        func_8001C814_main(object->model[i + 15], 1, 0);
    }
    models = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < models->count; i++) {
        func_8008A120_main(rotation, D_8010D414_inst);
        func_8002367C_main(matrix, HmfModelData[object->model[i + 1]].mtx);
        func_80018044_main(rotation, matrix, HmfModelData[object->model[i + 1]].mtx);
    }
    models = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < models->count; i++) {
        func_8008A120_main(rotation, D_8010D414_inst);
        func_8002367C_main(matrix, HmfModelData[object->model[i + 10]].mtx);
        func_80018044_main(rotation, matrix, HmfModelData[object->model[i + 10]].mtx);
    }
    D_8010DC94_inst = func_8010B038_inst;
}
