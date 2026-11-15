#include "common_duel.h"
#include "ovl_81.h"

typedef struct EffectBurstWork {
    /* 0x00 */ s32 modelId;
    /* 0x04 */ s32 count;
    /* 0x08 */ Vec *pos;
    /* 0x0C */ f32 spread;
    /* 0x10 */ s32 interval;
    /* 0x14 */ s32 noLayer;
    /* 0x18 */ char unk_18[8];
} EffectBurstWork; // sizeof 0x20

typedef struct EffectMoveWork {
    /* 0x00 */ s32 modelId;
    /* 0x04 */ Vec *pos;
    /* 0x08 */ Vec *vel;
    /* 0x0C */ f32 scale;
    /* 0x10 */ Object *obj;
    /* 0x14 */ s32 delay;
    /* 0x18 */ char unk_18[8];
} EffectMoveWork; // sizeof 0x20

extern Object *D_80102AD0_name_81[];
s32 D_80100E40_name_81 = 1;
extern s16 D_80102B50_name_81;
extern omObjData *D_80102B54_name_81;
extern Vec D_80102B58_name_81;

void func_800DC800_name_81(void);
void func_800DCBA8_name_81(void);
void func_800DCE6C_name_81(s16 model);
void func_800DD518_name_81(omObjData *obj);
void func_800DD59C_name_81(s16 arg0, f32 arg1, f32 arg2);
void func_800DD5CC_name_81(s16 model);
void func_800DD75C_name_81(s16 model);

void func_800DC800_name_81(void) {
    EffectBurstWork *work = HuPrcCurrentGet()->user_data;
    s32 modelId = work->modelId;
    s32 count = work->count;
    Vec *basePos = work->pos;
    f32 spread = work->spread;
    s32 interval = work->interval;
    s32 noLayer = work->noLayer;
    Vec pos;
    Vec offsets[6] = {
        { 0.0f, 2.0f, 0.0f },
        { 8.0f, 4.0f, 8.0f },
        { -8.0f, -2.0f, -8.0f },
        { 8.0f, 6.0f, -8.0f },
        { -8.0f, 0.0f, 8.0f },
        { 0.0f, 10.0f, 0.0f },
    };
    Object *obj;
    s32 i;

    HuVecCopy3F(&pos, basePos);
    for (i = 0; i < count; i++) {
        obj = func_800D8010_name_81(modelId, NULL);
        D_80102AD0_name_81[i] = obj;
        if (!noLayer) {
            Hu3DModelLayerSet(obj->omObj1->model[0], 0x800);
            Hu3DModelAttrSet(D_80102AD0_name_81[i]->omObj1->model[0], 0x180, 0);
            Hu3DModelRemakeStatic(D_80102AD0_name_81[i]->omObj1->model[0]);
        }
        MBDModelTempAllocFree(D_80102AD0_name_81[i]);
        Hu3DMotionAttrSet(D_80102AD0_name_81[i]->omObj1->model[0], 2, 0);
        HuVecCopy3F(&D_80102AD0_name_81[i]->coords, &pos);
        D_80102AD0_name_81[i]->coords.x += spread * offsets[i % 6].x;
        D_80102AD0_name_81[i]->coords.y += spread * offsets[i % 6].y;
        D_80102AD0_name_81[i]->coords.z += spread * offsets[i % 6].z;
        HuPrcSleep(interval);
    }
    func_800EFABC_name_81(D_80102AD0_name_81[i - 1]);
    for (i = 0; i < count; i++) {
        MBDModelKill(D_80102AD0_name_81[i]);
    }
    omDelPrcObj(NULL);
}

Process *func_800DCA64_name_81(s32 modelId, s32 count, Vec *pos, f32 spread, s32 interval) {
    Process *process = omAddPrcObj(func_800DC800_name_81, 0, 0, 0x40);
    EffectBurstWork *work = HuMemMemoryAlloc(process->heap, sizeof(EffectBurstWork));

    process->user_data = work;
    work->modelId = modelId;
    work->count = count;
    work->pos = pos;
    work->spread = spread;
    work->interval = interval;
    work->noLayer = FALSE;
    return process;
}

Process *func_800DCB04_name_81(s32 modelId, s32 count, Vec *pos, f32 spread, s32 interval) {
    Process *process = omAddPrcObj(func_800DC800_name_81, 0, 0, 0x40);
    EffectBurstWork *work = HuMemMemoryAlloc(process->heap, sizeof(EffectBurstWork));

    process->user_data = work;
    work->modelId = modelId;
    work->count = count;
    work->pos = pos;
    work->spread = spread;
    work->interval = interval;
    work->noLayer = TRUE;
    return process;
}

void func_800DCBA8_name_81(void) {
    EffectMoveWork *work = HuPrcCurrentGet()->user_data;
    Vec *velIn = work->vel;
    Vec vel = { 0.0f, 0.0f, 0.0f };
    Object *obj = work->obj;
    s32 delay = work->delay;

    if (velIn != NULL) {
        HuVecCopy3F(&vel, velIn);
    }
    if (delay != 0) {
        HuPrcSleep(delay - 1);
        Hu3DMotionAttrSet(obj->omObj1->model[0], 1, 0);
        MBDModelDispOn(obj);
    }
    while (!(MBDMotionCheck(obj) & 1)) {
        HuPrcVSleep();
        HuVecAdd(&obj->coords, &obj->coords, &vel);
    }
    MBDModelKill(obj);
    omDelPrcObj(NULL);
}

Process *func_800DCC8C_name_81(s32 modelId, Vec *pos, Vec *vel, f32 scale, s32 delay, f32 speed) {
    Object *obj = func_800D8010_name_81(modelId, NULL);
    Process *process;
    EffectMoveWork *work;

    Hu3DModelLayerSet(obj->omObj1->model[0], 0x800);
    Hu3DModelAttrSet(obj->omObj1->model[0], 0x180, 0);
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    Hu3DMotionSpeedSet(obj->omObj1->model[0], speed);
    MBDModelTempAllocFree(obj);
    if (delay != 0) {
        Hu3DMotionAttrSet(obj->omObj1->model[0], 2, 1);
        MBDModelDispOff(obj);
    } else {
        Hu3DMotionAttrSet(obj->omObj1->model[0], 2, 0);
    }
    HuVecCopy3F(&obj->coords, pos);
    HuVecCopyXYZ(&obj->scale, scale, scale, scale);
    process = omAddPrcObj(func_800DCBA8_name_81, 0, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(EffectMoveWork));
    process->user_data = work;
    work->modelId = modelId;
    work->pos = pos;
    work->vel = vel;
    work->scale = scale;
    work->obj = obj;
    work->delay = delay;
    return process;
}

Process *func_800DCE10_name_81(s32 modelId, Vec *pos, Vec *vel, f32 scale, s32 delay) {
    return func_800DCC8C_name_81(modelId, pos, vel, scale, delay, 1.0f);
}

Process *func_800DCE40_name_81(s32 modelId, Vec *pos, Vec *vel, f32 scale) {
    return func_800DCC8C_name_81(modelId, pos, vel, scale, 0, 1.0f);
}

void func_800DCE6C_name_81(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 count;
    s16 side;
    s16 i;
    f32 theta;
    f32 phi;
    f32 sinTheta;

    if (effect->unk00 == -1) {
        count = hmf->unk1A;
    } else {
        count = hmf->unk60[effect->unk00].unk2E;
    }
    if (effect->unk02 == 0) {
        effect->unk04 &= ~4;
        side = HuSqrtf(hmf->unk1A);
        particle = effect->unk58;
        for (i = 0; i < count; i++, particle++) {
            particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
            theta = 360.0f / side * (i % side);
            sinTheta = sindf(theta);
            phi = 180.0f / side * (i / side);
            particle->unk24 = sinTheta * sindf(phi);
            particle->unk28 = cosdf(phi);
            particle->unk2C = cosdf(theta) * sindf(phi);
            particle->unk0C = particle->unk24 * 50.0f;
            particle->unk10 = particle->unk28 * 50.0f;
            particle->unk14 = particle->unk2C * 50.0f;
            particle->unk04 = (rand8() & 0xF) + 5;
            particle->unk08 = 3.0f;
        }
    }
    particle = effect->unk58;
    for (i = 0; i < count; i++, particle++) {
        particle->unk0C += particle->unk24 * particle->unk04;
        particle->unk10 += particle->unk28 * particle->unk04;
        particle->unk14 += particle->unk2C * particle->unk04;
        particle->unk04 *= 0.98f;
        particle->unk08 *= 0.9f;
    }
    effect->unk02++;
    if (effect->unk02 > 100) {
        effect->unk04 |= 4;
    }
}

s32 func_800DD1E0_name_81(s32 dataNum, char *objName) {
    s32 model = Hu3DModelRead(dataNum, 0xAA9);

    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelObjAttrSet(model, 0x20000, 0x20000);
    Hu3DModelAttrSet(model, 0x180, 0);
    Hu3DModelRemakeStatic(model);
    Hu3DModelVtxBufMake(model);
    Hu3DModelDynamicFree(model);
    Hu3DModelCameraSet(model, 1);
    Hu3DMotionSpeedSet(model, 0.5f);
    Hu3DModelScaleSet(model, 0.1f, 0.1f, 0.1f);
    Hu3DParticleCreate(model, -1, objName, func_800DCE6C_name_81);
    return model;
}

void func_800DD2BC_name_81(s32 model) {
    Hu3DModelKill(model);
}

void func_800DD2DC_name_81(s32 model, Vec *pos) {
    Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
}

void func_800DD30C_name_81(s32 model) {
    if (Hu3DMotion[Hu3DData[model].motId].unk02 <= Hu3DData[model].motTime) {
        Hu3DMotionTimeSet(model, 0.0f);
        Hu3DParticleAttrSet(model, 4, 0);
        Hu3DParticleCntSet(model, 0);
    }
}

s32 func_800DD3B4_name_81(s32 arg0) {
    return Hu3DMotion[Hu3DData[arg0].motId].unk02 <= Hu3DData[arg0].motTime;
}

void func_800DD41C_name_81(Vec *pos) {
    s16 model;

    model = D_80102B50_name_81 = Hu3DModelRead(0xB0032, 0xAA9);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelObjAttrSet(model, 0x20000, 0x20000);
    Hu3DModelCameraSet(model, 1);
    Hu3DModelRemakeStatic(model);
    Hu3DModelVtxBufMake(model);
    Hu3DModelDynamicFree(model);
    Hu3DParticleCreate(model, -1, NULL, func_800DD75C_name_81);
    func_800DD59C_name_81(model, 5.0f, 1.0f);
    D_80100E40_name_81 = 0;
    D_80102B54_name_81 = omAddObj(2000, 10, 10, -1, func_800DD518_name_81);
    HuVecCopy3F(&D_80102B58_name_81, pos);
}

void func_800DD518_name_81(omObjData *obj) {
    if (D_80100E40_name_81 != 0) {
        func_800DD5CC_name_81(D_80102B50_name_81);
        func_800DD5CC_name_81(D_80102B50_name_81);
    }
}

void func_800DD554_name_81(void) {
    D_80100E40_name_81 = 1;
}

void func_800DD564_name_81(void) {
    D_80100E40_name_81 = 0;
}

void func_800DD570_name_81(void) {
    Hu3DModelKill(D_80102B50_name_81);
    omDelObj(D_80102B54_name_81);
}

void func_800DD59C_name_81(s16 arg0, f32 arg1, f32 arg2) {
    HmfModelData_UnkBC_Struct *unkBC = Hu3DData[arg0].unkBC;
    unkBC->unk08.f = arg1;
    unkBC->unk0C.f = arg2;
}

void func_800DD5CC_name_81(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = effect->unk58;
    s16 count = hmf->unk1A;
    s16 i;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk08 <= 0.0f) {
            particle->unk18 = ((rand8() * 75) >> 6) + 100;
            particle->unk1C = effect->unk08.f;
            particle->unk20 = (rand8() * 45) >> 5;
            particle->unk0C = sindf(particle->unk20) * particle->unk18 / 20.0f + D_80102B58_name_81.x + 142.0f;
            particle->unk10 = D_80102B58_name_81.y;
            particle->unk14 = cosdf(particle->unk20) * particle->unk18 / 20.0f + D_80102B58_name_81.z;
            particle->unk08 = 0.3f;
            break;
        }
    }
}

void func_800DD75C_name_81(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 count = hmf->unk1A;
    s16 i;

    if (effect->unk02 == 0) {
        effect->unk04 &= ~4;
        particle = effect->unk58;
        for (i = 0; i < count; i++, particle++) {
            particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
            particle->unk24 = particle->unk28 = particle->unk2C = 0.0f;
            particle->unk08 = 0.0f;
            particle->unk04 = 1.0f;
        }
        effect->unk02++;
    }
    particle = effect->unk58;
    for (i = 0; i < count; i++, particle++) {
        if (particle->unk08 > 0.0f) {
            particle->unk0C = sindf(particle->unk20) * particle->unk18 / 20.0f + D_80102B58_name_81.x + 142.0f;
            particle->unk10 += particle->unk1C;
            particle->unk14 = cosdf(particle->unk20) * particle->unk18 / 20.0f + D_80102B58_name_81.z;
            particle->unk20 += (400.0f - particle->unk18) / 20.0f * effect->unk0C.f;
            if (particle->unk20 > 360.0f) {
                particle->unk20 -= 360.0f;
            }
            particle->unk08 -= 0.015f;
        } else {
            particle->unk08 = 0.0f;
        }
    }
}
