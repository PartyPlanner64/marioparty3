#include "common.h"
#include "inst.h"

typedef struct {
    s16 count;
    char *nodes[1];
} InstModelHooks;

extern u8 D_800CB8B1_main[];
extern s8 D_8010D400_inst[7];
extern s8 D_8010D40A_inst;
extern s8 D_8010D554_inst[4];
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

s32 func_80107E20_inst(void);
void func_801080FC_inst(void);
void func_8010AC04_inst(omObjData *object);
void func_8010B628_inst(omObjData *);
void func_80016B00_main(s16, s16, char *, HuMtx4F);
void func_8010A750_inst(omObjData *);
void func_8010AC30_inst(omObjData *); /* extern */
void func_8010AD78_inst(omObjData *);
void func_8010B038_inst(omObjData *object);
void func_8008A120_main(HuMtx4F, f32);
void func_8002367C_main(HuMtx4F, HuMtx4F);
void func_80018044_main(HuMtx4F, HuMtx4F, HuMtx4F);
void func_8010B2A4_inst(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010A1D0_inst);

void func_8010A750_inst(omObjData *object) {
    omObjData *source;
    HmfModel *model;
    f32 duration;
    f32 time;
    InstModelHooks *models;
    s8 i;

    source = D_8010DDD8_inst.object;
    duration = D_800CCF58_main[HmfModelData[source->model[0]].unk02].unk02;
    time = HmfModelData[source->model[0]].unk40;
    models = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < models->count; i++) {
        model = &HmfModelData[object->model[i + 1]];
        func_80016B00_main(source->model[0], time, models->nodes[i], model->mtx);
    }
    models = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < models->count; i++) {
        model = &HmfModelData[object->model[i + 10]];
        func_80016B00_main(source->model[0], time, models->nodes[i], model->mtx);
    }
    if (func_80107E20_inst() == 1) {
        models = D_8010D4C0_inst[D_8010D40A_inst][0];
        for (i = 0; i < models->count; i++) {
            func_8001C6A8_main(object->model[i + 1], 0);
            func_8001C814_main(object->model[i + 1], 1, 0);
            HmfModelData[object->model[i + 1]].rot.x = 0;
            func_80016B00_main(source->model[0], duration, models->nodes[i], D_8010DC50_inst);
            Hu3DModelPosSet(object->model[i + 5], D_8010DC50_inst[3][0] * 0.5f, D_8010DC50_inst[3][1] * 0.5f,
                            D_8010DC50_inst[3][2] * 0.5f);
        }
        models = D_8010D4C0_inst[D_8010D40A_inst][1];
        for (i = 0; i < models->count; i++) {
            func_8001C6A8_main(object->model[i + 10], 0);
            func_8001C814_main(object->model[i + 10], 1, 0);
            HmfModelData[object->model[i + 10]].rot.x = 0;
            func_80016B00_main(source->model[0], duration, models->nodes[i], D_8010DC50_inst);
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
        func_8001C258_main(object->model[i + 5], 4, 0);
        func_8001C6A8_main(object->model[i + 5], 0);
        func_8001C814_main(object->model[i + 5], 1, 0);
    }
    models = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < models->count; i++) {
        func_8001C258_main(object->model[i + 15], 4, 0);
        func_8001C6A8_main(object->model[i + 15], 0);
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

    duration = D_800CCF58_main[HmfModelData[object->model[5]].unk02].unk02 - 20.0f;
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

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010D9C8_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010D9E8_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA24_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA34_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA44_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA54_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA64_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA74_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA84_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA94_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DAA4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DAB0_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DABC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DAC8_inst);

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
        func_8001C258_main(object->model[i + 5], 4, 0);
    }
    models = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < models->count; i++) {
        func_8001C814_main(object->model[i + 15], 1, 0);
        func_8001C814_main(object->model[i + 15], 4, 4);
        func_8001C258_main(object->model[i + 15], 4, 0);
    }
    D_8010DC94_inst = func_8010B2A4_inst;
}

void func_8010B2A4_inst(omObjData *object) {
    HuMtx4F rotation;
    HuMtx4F matrix;
    f32 duration;
    InstModelHooks *models;
    s8 i;

    duration = D_800CCF58_main[HmfModelData[object->model[5]].unk02].unk02 - 20.0f;
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
            func_8001C258_main(object->model[i + 5], 4, 4);
        }
        models = D_8010D4C0_inst[D_8010D40A_inst][1];
        for (i = 0; i < models->count; i++) {
            func_8001C258_main(object->model[i + 15], 4, 4);
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

    duration = D_800CCF58_main[HmfModelData[object->model[5]].unk02].unk02;
    models = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < models->count; i++) {
        func_8001C258_main(object->model[i + 5], 4, 0);
        func_8001C6A8_main(object->model[i + 5], duration);
        func_8001C814_main(object->model[i + 5], 1, 0);
    }
    models = D_8010D4C0_inst[D_8010D40A_inst][1];
    duration = D_800CCF58_main[HmfModelData[object->model[15]].unk02].unk02;
    for (i = 0; i < models->count; i++) {
        func_8001C258_main(object->model[i + 15], 4, 0);
        func_8001C6A8_main(object->model[i + 15], duration);
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
