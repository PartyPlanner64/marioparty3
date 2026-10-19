#include "common.h"
#include "overlays/msetup.h"

void func_80013390_main(s16, s32, s32, void (*)(s16));
void func_8010CE8C_msetup(s16);
u32 func_80106208_msetup(u32);

s16 func_8010CAF0_msetup(s32 dataId, s32 flags) {
    s16 model;
    HmfData *hmf;
    HmfModelData_UnkBC_Struct *data;
    HmfModelData_UnkBC_Unk58_Struct *entry;
    f32 radius;
    f32 step;
    f32 angleStep;
    s16 i;

    model = func_8000B108_main(dataId, flags);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    func_8001C448_main(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    func_80013390_main(model, -1, 0, func_8010CE8C_msetup);
    hmf = HmfModelData[model].hmf;
    data = HmfModelData[model].unkBC;
    entry = data->unk58;
    data->unk08.f = 30.0f;
    data->unk0C.f = 720.0f;
    data->unk10.f = 80.0f;
    data->unk14 = 5.0f;
    radius = data->unk10.f / 10.0f;
    step = (data->unk10.f - radius) / data->unk08.f;
    angleStep = data->unk0C.f / data->unk08.f;
    for (i = 0; i < hmf->unk1A; i++, entry++) {
        entry->unk0C = entry->unk10 = entry->unk14 = 0.0f;
        entry->unk18 = 0.0f;
        entry->unk20 = radius;
        entry->unk1C = step;
        entry->unk24 = angleStep;
        entry->unk28 = 0.0f;
        entry->unk2C = 0.0f;
        entry->unk08 = 0.0f;
        entry->unk04 = 180.0f;
    }
    return model;
}

void func_8010CC70_msetup(s16 model, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *data = HmfModelData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *entry = data->unk58;
    s16 i;
    f32 value1;
    f32 value2;

    data->unk08.f = arg1;
    data->unk0C.f = arg2;
    data->unk10.f = arg3;
    data->unk14 = arg4;
    value1 = (arg3 - arg3 / 10.0f) / arg1;
    value2 = arg2 / arg1;
    for (i = 0; i < hmf->unk1A; i++, entry++) {
        entry->unk1C = value1;
        entry->unk24 = value2;
    }
}

s32 func_8010CD14_msetup(s16 model, f32 x, f32 y, f32 z) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *data = HmfModelData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *entry = data->unk58;
    s16 i;
    f32 angle;

    data->unk1C.f = x;
    data->unk20.f = y;
    data->unk24.f = z;
    for (i = 0; i < hmf->unk1A; i++, entry++) {
        if (entry->unk04 >= 180.0f) {
            entry->unk18 = func_80106208_msetup(360);
            entry->unk20 = data->unk10.f / 10.0f;
            angle = func_80106208_msetup(150);
            angle -= 75.0f;
            if (angle < 0.0f) {
                angle += 360.0f;
            }
            entry->unk28 = sindf(angle);
            entry->unk2C = cosdf(angle);
            entry->unk08 = 0.0f;
            entry->unk04 = 0.0f;
            return 1;
        }
    }
    return 0;
}

/* Preserve the trailing double after the compiler-generated conversion constant. */
const f64 D_8011A688_msetup = 0.0;

void func_8010CE8C_msetup(s16 model) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *data = HmfModelData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *entry = data->unk58;
    s16 i;
    s16 count = hmf->unk1A;
    f32 radius;

    for (i = 0; i < count; i++, entry++) {
        if (entry->unk04 < 180.0f) {
            entry->unk18 += entry->unk24;
            if (entry->unk18 < 0.0f) {
                entry->unk18 += 360.0f;
            } else if (entry->unk18 >= 360.0f) {
                entry->unk18 -= 360.0f;
            }
            entry->unk20 += entry->unk1C;
            radius = entry->unk20 * entry->unk2C;
            entry->unk0C = radius * sindf(entry->unk18) + data->unk1C.f;
            entry->unk14 = radius * cosdf(entry->unk18) + data->unk24.f;
            entry->unk10 = entry->unk20 * entry->unk28 + data->unk20.f;
            entry->unk04 += data->unk14;
            if (entry->unk04 > 180.0f) {
                entry->unk04 = 180.0f;
            }
            entry->unk08 = sindf(entry->unk04) * data->unk14;
        }
    }
    data->unk02++;
}
