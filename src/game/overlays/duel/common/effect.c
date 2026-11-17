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

extern Object *mbdEffBurstObjTbl[];
s32 mbdEffSwirlF = 1;
extern s16 mbdEffSwirlMdl;
extern omObjData *mbdEffSwirlObj;
extern Vec mbdEffSwirlPos;

void MBDEffBurstProc(void);
void MBDEffMdlProc(void);
void MBDEffExplodeHook(s16 model);
void MBDEffSwirlObjMain(omObjData *obj);
void MBDEffSwirlParamSet(s16 arg0, f32 arg1, f32 arg2);
void MBDEffSwirlEmit(s16 model);
void MBDEffSwirlHook(s16 model);

void MBDEffBurstProc(void) {
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
        obj = MBDModelCreate(modelId, NULL);
        mbdEffBurstObjTbl[i] = obj;
        if (!noLayer) {
            Hu3DModelLayerSet(obj->omObj1->model[0], 0x800);
            Hu3DModelAttrSet(mbdEffBurstObjTbl[i]->omObj1->model[0], 0x180, 0);
            Hu3DModelRemakeStatic(mbdEffBurstObjTbl[i]->omObj1->model[0]);
        }
        MBDModelTempAllocFree(mbdEffBurstObjTbl[i]);
        Hu3DMotionAttrSet(mbdEffBurstObjTbl[i]->omObj1->model[0], 2, 0);
        HuVecCopy3F(&mbdEffBurstObjTbl[i]->coords, &pos);
        mbdEffBurstObjTbl[i]->coords.x += spread * offsets[i % 6].x;
        mbdEffBurstObjTbl[i]->coords.y += spread * offsets[i % 6].y;
        mbdEffBurstObjTbl[i]->coords.z += spread * offsets[i % 6].z;
        HuPrcSleep(interval);
    }
    MBDModelMotionWait(mbdEffBurstObjTbl[i - 1]);
    for (i = 0; i < count; i++) {
        MBDModelKill(mbdEffBurstObjTbl[i]);
    }
    omDelPrcObj(NULL);
}

Process *MBDEffBurstCreate(s32 modelId, s32 count, Vec *pos, f32 spread, s32 interval) {
    Process *process = omAddPrcObj(MBDEffBurstProc, 0, 0, 0x40);
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

Process *MBDEffBurstNoLayerCreate(s32 modelId, s32 count, Vec *pos, f32 spread, s32 interval) {
    Process *process = omAddPrcObj(MBDEffBurstProc, 0, 0, 0x40);
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

void MBDEffMdlProc(void) {
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

Process *MBDEffMdlCreateEx(s32 modelId, Vec *pos, Vec *vel, f32 scale, s32 delay, f32 speed) {
    Object *obj = MBDModelCreate(modelId, NULL);
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
    process = omAddPrcObj(MBDEffMdlProc, 0, 0, 0x40);
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

Process *MBDEffMdlDelayCreate(s32 modelId, Vec *pos, Vec *vel, f32 scale, s32 delay) {
    return MBDEffMdlCreateEx(modelId, pos, vel, scale, delay, 1.0f);
}

Process *MBDEffMdlCreate(s32 modelId, Vec *pos, Vec *vel, f32 scale) {
    return MBDEffMdlCreateEx(modelId, pos, vel, scale, 0, 1.0f);
}

void MBDEffExplodeHook(s16 model) {
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

s32 MBDEffExplodeCreate(s32 dataNum, char *objName) {
    s32 model = Hu3DModelRead(dataNum, 0xAA9);

    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelObjAttrSet(model, 0x20000, 0x20000);
    Hu3DModelAttrSet(model, 0x180, 0);
    Hu3DModelRemakeStatic(model);
    Hu3DModelVtxBufMake(model);
    Hu3DModelDynamicFree(model);
    Hu3DModelCameraSet(model, HU3D_CAM0);
    Hu3DMotionSpeedSet(model, 0.5f);
    Hu3DModelScaleSet(model, 0.1f, 0.1f, 0.1f);
    Hu3DParticleCreate(model, -1, objName, MBDEffExplodeHook);
    return model;
}

void MBDEffExplodeKill(s32 model) {
    Hu3DModelKill(model);
}

void MBDEffExplodePosSet(s32 model, Vec *pos) {
    Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
}

void MBDEffExplodeLoop(s32 model) {
    if (Hu3DMotion[Hu3DData[model].motId].unk02 <= Hu3DData[model].motTime) {
        Hu3DMotionTimeSet(model, 0.0f);
        Hu3DParticleAttrSet(model, 4, 0);
        Hu3DParticleCntSet(model, 0);
    }
}

s32 MBDEffExplodeEndCheck(s32 arg0) {
    return Hu3DMotion[Hu3DData[arg0].motId].unk02 <= Hu3DData[arg0].motTime;
}

void MBDEffSwirlCreate(Vec *pos) {
    s16 model;

    model = mbdEffSwirlMdl = Hu3DModelRead(0xB0032, 0xAA9);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelObjAttrSet(model, 0x20000, 0x20000);
    Hu3DModelCameraSet(model, HU3D_CAM0);
    Hu3DModelRemakeStatic(model);
    Hu3DModelVtxBufMake(model);
    Hu3DModelDynamicFree(model);
    Hu3DParticleCreate(model, -1, NULL, MBDEffSwirlHook);
    MBDEffSwirlParamSet(model, 5.0f, 1.0f);
    mbdEffSwirlF = 0;
    mbdEffSwirlObj = omAddObj(2000, 10, 10, -1, MBDEffSwirlObjMain);
    HuVecCopy3F(&mbdEffSwirlPos, pos);
}

void MBDEffSwirlObjMain(omObjData *obj) {
    if (mbdEffSwirlF != 0) {
        MBDEffSwirlEmit(mbdEffSwirlMdl);
        MBDEffSwirlEmit(mbdEffSwirlMdl);
    }
}

void MBDEffSwirlOn(void) {
    mbdEffSwirlF = 1;
}

void MBDEffSwirlOff(void) {
    mbdEffSwirlF = 0;
}

void MBDEffSwirlKill(void) {
    Hu3DModelKill(mbdEffSwirlMdl);
    omDelObj(mbdEffSwirlObj);
}

void MBDEffSwirlParamSet(s16 arg0, f32 arg1, f32 arg2) {
    HmfModelData_UnkBC_Struct *unkBC = Hu3DData[arg0].unkBC;
    unkBC->unk08.f = arg1;
    unkBC->unk0C.f = arg2;
}

void MBDEffSwirlEmit(s16 model) {
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
            particle->unk0C = sindf(particle->unk20) * particle->unk18 / 20.0f + mbdEffSwirlPos.x + 142.0f;
            particle->unk10 = mbdEffSwirlPos.y;
            particle->unk14 = cosdf(particle->unk20) * particle->unk18 / 20.0f + mbdEffSwirlPos.z;
            particle->unk08 = 0.3f;
            break;
        }
    }
}

void MBDEffSwirlHook(s16 model) {
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
            particle->unk0C = sindf(particle->unk20) * particle->unk18 / 20.0f + mbdEffSwirlPos.x + 142.0f;
            particle->unk10 += particle->unk1C;
            particle->unk14 = cosdf(particle->unk20) * particle->unk18 / 20.0f + mbdEffSwirlPos.z;
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
