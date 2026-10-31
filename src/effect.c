#include "common.h"
#include "mallocblock.h"

#define EFFECT_GROUP_MAX 8

typedef struct EffectGroupModel {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 model;
    /* 0x04 */ Vec unk04;
} EffectGroupModel; // Size 0x10

typedef struct EffectGroup {
    /* 0x00 */ s16 count;
    /* 0x04 */ EffectGroupModel *models;
} EffectGroup; // Size 0x08

extern u8 D_80097720_main[];
extern EffectGroup *D_800D6A00_main[EFFECT_GROUP_MAX];

void func_80013390_main(s16 model, s16 type, char *name, void (*func)(s16));
void func_800138EC_main(s16 model, s32 clear, s32 set);
s16 func_80013928_main(s16 model);
void func_80013954_main(s16 model, s16 value);
s16 func_8000CC98_main(s32 fileId, s32 attr);
void func_8000D06C_main(omObjData *obj);
void func_8000D268_main(s16 model);
s16 func_8000D3E0_main(s32 fileId, s32 attr, s16 count, void (*func)(s16));
void func_8000D694_main(s16 model);

s16 func_8000CBA0_main(s32 fileId, s32 attr) {
    s16 model;
    HmfData *hmf;
    HmfModelData_UnkBC_Struct *bc;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 i;

    model = func_8000CC98_main(fileId, attr & ~0x60);
    func_80013390_main(model, -1, NULL, func_8000D268_main);
    hmf = HmfModelData[model].hmf;
    bc = HmfModelData[model].unkBC;
    particle = bc->unk58;
    bc->unk08.f = 5.0f;
    bc->unk0C.f = 20.0f;
    for (i = 0; i < hmf->unk1A; i++, particle++) {
        particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
        particle->unk18 = particle->unk20 = 0.0f;
        particle->unk1C = -10.0f;
        particle->unk04 = particle->unk08 = 0.0f;
    }
    return model;
}

s16 func_8000CC98_main(s32 fileId, s32 attr) {
    s16 model = func_8000B108_main(fileId, attr);

    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    Hu3DModelRemakeStatic(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    return model;
}

void func_8000CD00_main(s16 model, f32 arg1, f32 arg2, f32 arg3) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = HmfModelData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = bc->unk58;
    s16 i;

    bc->unk08.f = arg1;
    bc->unk0C.f = arg2;
    for (i = 0; i < hmf->unk1A; i++, particle++) {
        particle->unk1C = -arg3;
    }
}

s32 func_8000CD74_main(s16 model, f32 x, f32 y, f32 z) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = HmfModelData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = bc->unk58;
    s16 i;

    for (i = 0; i < hmf->unk1A; i++, particle++) {
        if (particle->unk04 <= 0.0f) {
            particle->unk0C = x;
            particle->unk10 = y;
            particle->unk14 = z;
            particle->unk04 = particle->unk08 =
                bc->unk08.f * 0.7f + bc->unk08.f * 0.3f * ((rand8() % 10 + 1) * 0.1f);
            return 1;
        }
    }
    return 0;
}

s16 func_8000CED8_main(s32 fileId, s32 attr) {
    omObjData *obj;
    s16 model;
    HmfModelData_UnkBC_Struct *bc;

    obj = omAddObj(1000, 0, 0, -1, func_8000D06C_main);
    model = func_8000CBA0_main(fileId, attr);
    obj->work[0] = model;
    bc = HmfModelData[model].unkBC;
    bc->unk1C.f = bc->unk20.f = bc->unk24.f = 0.0f;
    bc->unk04 |= 1;
    bc->unk10.f = 100.0f;
    bc->unk14 = -1.0f;
    return model;
}

void func_8000CFA4_main(s16 model, f32 x, f32 y, f32 z) {
    HmfModelData_UnkBC_Struct *bc = HmfModelData[model].unkBC;

    bc->unk1C.f = x;
    bc->unk20.f = y;
    bc->unk24.f = z;
}

void func_8000CFD8_main(s16 model, s16 time) {
    HmfModelData[model].unkBC->unk14 = time;
}

void func_8000D018_main(s16 model, f32 range) {
    HmfModelData[model].unkBC->unk10.f = range;
}

void func_8000D044_main(s16 model) {
    func_800138EC_main(model, 5, 4);
}

void func_8000D06C_main(omObjData *obj) {
    s16 model = obj->work[0];
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = HmfModelData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 i;
    f32 x;
    f32 z;

    if (bc->unk04 & 4) {
        particle = bc->unk58;
        for (i = 0; i < hmf->unk1A; i++, particle++) {
            if (particle->unk04 > 0.0f) {
                break;
            }
        }
        if (i == hmf->unk1A) {
            Hu3DModelKill(model);
            omDelObj(obj);
            return;
        }
        bc->unk04 &= ~1;
    }
    if (bc->unk14 >= 0.0f) {
        if ((bc->unk14 -= 1.0f) <= 0.0f) {
            bc->unk04 &= ~1;
        }
    }
    if (bc->unk04 & 1) {
        x = rand8() * bc->unk10.f / 256.0f - bc->unk10.f / 2.0f;
        z = rand8() * bc->unk10.f / 256.0f - bc->unk10.f / 2.0f;
        func_8000CD74_main(model, x + bc->unk1C.f, bc->unk20.f, z + bc->unk24.f);
    }
}

void func_8000D268_main(s16 model) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = HmfModelData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = bc->unk58;
    s16 i;
    s16 count;

    for (i = 0, count = hmf->unk1A; i < count; i++, particle++) {
        if (particle->unk04 > 0.0f) {
            particle->unk0C += particle->unk18;
            particle->unk10 += particle->unk1C;
            particle->unk14 += particle->unk20;
            particle->unk04 -= bc->unk08.f / bc->unk0C.f;
            if (particle->unk04 <= 0.0f) {
                particle->unk04 = 0.0f;
            }
            particle->unk08 = (D_80097720_main[(bc->unk02 + i) & 3] * 0.15f + 1.0f) * particle->unk04;
        }
    }
    bc->unk02++;
}

void func_8000D3AC_main(void) {
    EffectGroup **slot = D_800D6A00_main;
    s16 i;

    for (i = 0; i < EFFECT_GROUP_MAX; i++, slot++) {
        *slot = NULL;
    }
}

s16 func_8000D3E0_main(s32 fileId, s32 attr, s16 count, void (*func)(s16)) {
    EffectGroup **slot;
    EffectGroup *group;
    EffectGroupModel *entry;
    s16 i;
    s16 j;
    s16 model;

    for (slot = D_800D6A00_main, i = 0; i < EFFECT_GROUP_MAX; i++, slot++) {
        if (*slot == NULL) {
            break;
        }
    }
    if (i == EFFECT_GROUP_MAX) {
        return -1;
    }
    group = HuMemAllocTag(sizeof(EffectGroup), TAG_OVERLAY);
    *slot = group;
    group->count = count;
    entry = HuMemAllocTag(count * sizeof(EffectGroupModel), TAG_OVERLAY);
    group->models = entry;
    for (j = 0; j < count; j++, entry++) {
        model = func_8000CC98_main(fileId, attr | 4);
        entry->model = model;
        func_80013390_main(model, -1, NULL, func);
        func_800138EC_main(model, 6, 6);
        entry->unk04.x = entry->unk04.y = entry->unk04.z = 0.0f;
        entry->unk00 = 0;
    }
    return i;
}

s16 func_8000D550_main(s16 index, f32 x, f32 y, f32 z) {
    EffectGroup *group = D_800D6A00_main[index];
    EffectGroupModel *entry = group->models;
    s16 i;
    s16 model;

    for (i = 0; i < group->count; i++, entry++) {
        if (func_80013928_main(entry->model) & 4) {
            break;
        }
    }
    if (i == group->count) {
        return -1;
    }
    model = entry->model;
    Hu3DModelPosSet(model, x, y, z);
    func_80013954_main(model, 0);
    func_800138EC_main(model, 6, 0);
    func_8001C258_main(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    return model;
}

s16 func_8000D658_main(s32 attr, s16 count) {
    return func_8000D3E0_main(0x85, attr, count, func_8000D694_main);
}

void func_8000D694_main(s16 model) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = HmfModelData[model].unkBC;
    s16 count = hmf->unk1A;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 i;
    f32 angle;
    f32 scale;

    if (bc->unk02 == 0) {
        bc->unk04 &= ~4;
        particle = bc->unk58;
        for (i = 0; i < count; i++, particle++) {
            particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
            angle = 360 / count * i;
            particle->unk18 = sindf(angle);
            particle->unk1C = 5 - (rand8() & 0xF);
            particle->unk20 = cosdf(angle);
            particle->unk04 = 15.0f;
        }
    }
    if (!(bc->unk04 & 4)) {
        particle = bc->unk58;
        scale = cosdf(bc->unk02 * 11.25f) * 5.0f;
        for (i = 0; i < count; i++, particle++) {
            particle->unk0C += particle->unk18 * particle->unk04;
            particle->unk10 += particle->unk1C;
            particle->unk14 += particle->unk20 * particle->unk04;
            particle->unk08 = scale;
            particle->unk1C -= 2.0f;
            particle->unk04 *= 0.7f;
        }
        if (++bc->unk02 >= 8) {
            bc->unk04 |= 4;
            func_8001C258_main(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
    }
}
