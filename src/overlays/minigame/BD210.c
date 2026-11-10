#include "common.h"
#include "overlays/minigame.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"

typedef struct func_800EA6C4_minigame_Entry {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
} func_800EA6C4_minigame_Entry; // Size 0x1C

// Per-object state allocated in func_800EA6C4_minigame (0x290 bytes), stored
// in the `data` pointer (0x5C) of the omObjData it belongs to.
typedef struct func_800EA6C4_minigame_ObjData {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ omObjFunc unk04;
    /* 0x08 */ omObjFunc unk08;
    /* 0x0C */ omObjFunc unk0C;
    /* 0x10 */ Vec unk10;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x024 */ func_800EA6C4_minigame_Entry unk24[10];
    /* 0x13C */ func_800EA6C4_minigame_Entry unk13C[10];
    /* 0x254 */ s16 sprites[23];
    /* 0x282 */ u16 unk282;
    /* 0x284 */ u16 unk284;
    /* 0x286 */ u16 unk286;
    /* 0x288 */ u16 unk288;
    /* 0x28A */ u16 unk28A;
    /* 0x28C */ u16 unk28C;
    /* 0x28E */ u16 unk28E;
} func_800EA6C4_minigame_ObjData;

extern s16 D_800EBE00_minigame[4];

void func_800EA690_minigame(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_800EBE00_minigame[i] = -1;
    }
}

omObjData *func_800EA6C4_minigame(s16 prio, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    omObjData *obj;
    func_800EA6C4_minigame_ObjData *data;
    s16 *model;
    s32 i;

    obj = omAddObj(prio, 23, 0, -1, func_800EAA58_minigame);
    model = obj->model;
    for (i = 0; i < 23; i++) {
        *model++ = -1;
    }
    data = obj->data = HuMemAllocTag(sizeof(func_800EA6C4_minigame_ObjData), TAG_OVERLAY);
    memset(data, 0, sizeof(func_800EA6C4_minigame_ObjData));
    data->unk282 = arg1;
    data->unk284 = arg2;
    data->unk286 = arg3;
    data->unk288 = arg4;
    data->unk28A = 24;
    data->unk28C = 120;
    data->unk28E = 1;
    data->unk20 = 0;
    data->unk04 = NULL;
    data->unk08 = func_800EB3CC_minigame;
    data->unk0C = func_800EB5E4_minigame;
    return obj;
}

void func_800EA7D0_minigame(omObjData *obj, f32 x, f32 y, f32 z) {
    obj->trans.x = x;
    obj->trans.y = y;
    obj->trans.z = z;
}

void func_800EA7E0_minigame(omObjData *obj, f32 x, f32 y, f32 z) {
    obj->rot.x = x;
    obj->rot.y = y;
    obj->rot.z = z;
}

void func_800EA7F0_minigame(omObjData *obj, f32 arg1, f32 arg2, f32 arg3) {
    func_800EA6C4_minigame_ObjData *data = obj->data;

    obj->scale.x = arg1;
    obj->scale.y = arg2;
    obj->scale.z = arg3;
    data->unk28C = (u32)(arg2 * 120.0f);
    data->unk28E = (u32)arg2;
    if (obj->model[2] >= 0) {
        Hu3DModelPosSet(obj->model[2], arg2 * 3.0f, arg2 * 3.0f, arg2 * 3.0f);
    }
}

void func_800EA8F0_minigame(omObjData *obj, f32 value) {
    func_800EA6C4_minigame_ObjData *data = obj->data;

    data->unk1C = value;
}

void func_800EA8FC_minigame(omObjData *obj, f32 x, f32 y, f32 z) {
    func_800EA6C4_minigame_ObjData *data = obj->data;

    data->unk10.x = x;
    data->unk10.y = y;
    data->unk10.z = z;
}

void func_800EA910_minigame(omObjData *obj, s32 value) {
    func_800EA6C4_minigame_ObjData *data = obj->data;

    data->unk20 = value;
}

s32 func_800EA91C_minigame(omObjData *obj) {
    func_800EA6C4_minigame_ObjData *data = obj->data;

    return data->unk20;
}

void func_800EA928_minigame(omObjData *obj, u16 arg1) {
    func_800EA6C4_minigame_Entry *entry;
    s16 model = obj->model[0];
    s16 i;

    if (model < 0) {
        return;
    }
    switch (arg1) {
        case 0:
            Hu3DMotionTimeSet(model, 0.0f);
            break;
        case 4:
            entry = ((func_800EA6C4_minigame_ObjData *)obj->data)->unk24;
            for (i = 10; i != 0; i--, entry++) {
                entry->unk18 = 0;
            }
            entry = ((func_800EA6C4_minigame_ObjData *)obj->data)->unk13C;
            for (i = 10; i != 0; i--, entry++) {
                entry->unk18 = 0;
            }
            break;
    }
    func_8001C258_main(model, 4, arg1);
    func_8001C258_main(obj->model[1], 4, arg1);
    for (i = 2; i < 23; i++) {
        func_8001C258_main(obj->model[i], 4, 4);
    }
}

void func_800EAA58_minigame(omObjData *obj) {
    func_800EA6C4_minigame_ObjData *data = obj->data;
    s16 sprite;
    s16 model;
    s16 j;
    s16 k;
    s32 i;

    if (D_800EBE00_minigame[0] < 0) {
        D_800EBE00_minigame[0] = model = func_8000B108_main(0x1C, data->unk282);
    } else {
        model = Hu3DModelLink(D_800EBE00_minigame[0]);
    }
    obj->model[0] = model;
    func_8001C814_main(model, 1, 1);

    if (D_800EBE00_minigame[1] < 0) {
        D_800EBE00_minigame[1] = model = func_8000B0D4_main(data->unk288 ? 9 : 1, data->unk284);
    } else {
        model = Hu3DModelLink(D_800EBE00_minigame[1]);
    }
    obj->model[1] = model;

    if (D_800EBE00_minigame[2] < 0) {
        D_800EBE00_minigame[2] = sprite = SprModelRead(12, data->unk286 | 4, 8);
    } else {
        sprite = func_80014618_main(D_800EBE00_minigame[2], 8);
    }
    data->sprites[2] = sprite;
    model = D_800CBB60_main[sprite].modelId;
    obj->model[2] = model;
    func_8001C258_main(model, 4, 4);
    func_80014794_main(sprite, 0xC0);
    func_800147FC_main(sprite, 0xFF, 0xFF, 0xBE);
    func_8001C2FC_main(model, 0x70000000, 0x70000000);
    func_800146DC_main(sprite, 4, 0);
    Hu3DModelScaleSet(model, data->unk28E * 3.0f, data->unk28E * 3.0f, data->unk28E * 3.0f);

    for (j = 3, k = 13, i = 0; i < 10; i++, j++, k++) {
        if (D_800EBE00_minigame[3] < 0) {
            D_800EBE00_minigame[3] = sprite = SprModelRead(10, data->unk286, 8);
        } else {
            sprite = func_80014618_main(D_800EBE00_minigame[3], 8);
        }
        data->sprites[j] = sprite;
        model = D_800CBB60_main[sprite].modelId;
        obj->model[j] = model;
        func_8001C2FC_main(model, 0x70000000, 0x70000000);
        Hu3DModelScaleSet(model, 2.0f, 2.0f, 2.0f);
        func_8001C258_main(model, 4, 4);

        sprite = func_80014618_main(D_800EBE00_minigame[3], 8);
        data->sprites[k] = sprite;
        model = D_800CBB60_main[sprite].modelId;
        obj->model[k] = model;
        func_8001C2FC_main(model, 0x70000000, 0x70000000);
        Hu3DModelScaleSet(model, 2.0f, 2.0f, 2.0f);
        func_8001C258_main(model, 4, 4);
        func_80014794_main(sprite, (u8)(i * 15 + 0x60));
    }
    obj->func = func_800EAE14_minigame;
}

void func_800EAE14_minigame(omObjData *arg0) {
    func_800EA6C4_minigame_ObjData *data = arg0->data;

    if (data->unk04 != NULL) {
        data->unk04(arg0);
    }
    if (data->unk08 != NULL) {
        data->unk08(arg0);
    }
    if (data->unk0C != NULL) {
        data->unk0C(arg0);
    }
}

s32 func_800EAE7C_minigame(omObjData *obj) {
    func_800EA6C4_minigame_ObjData *data = obj->data;
    func_800EA6C4_minigame_Entry *entry;
    s32 count = 0;
    f32 growStep;
    f32 shrinkStep;
    f32 maxScale;
    f32 angle;
    f32 sinAngle;
    f32 cosAngle;
    f32 step;
    f32 offsetX;
    f32 offsetZ;
    f32 x;
    f32 y;
    f32 z;
    s16 model;
    s32 i;

    growStep = 4.0f / data->unk28A;
    shrinkStep = -1.6f / data->unk28A;
    maxScale = data->unk28E * 2.0f;
    angle = CRot.y + 90.0f;
    entry = data->unk24;
    if (angle > 360.0f) {
        angle -= 360.0f;
    }
    sinAngle = sindf(angle);
    cosAngle = cosdf(angle);
    for (i = 3; i < 23; entry++, i++) {
        if (i == 13) {
            entry = data->unk13C;
        }
        if (entry->unk18 == 0) {
            continue;
        }
        model = obj->model[i];
        count++;
        switch (entry->unk18) {
            case 1:
                if (entry->unk1A != 0) {
                    entry->unk1A--;
                    break;
                }
                entry->unk18 = 2;
                entry->unk1A = data->unk28A;
                Hu3DModelScaleSet(model, entry->unk14, entry->unk14, entry->unk14);
                y = sindf(entry->unk10) * entry->unk0C;
                x = y * sinAngle;
                z = y * cosAngle;
                y = cosdf(entry->unk10) * entry->unk0C;
                x += entry->pos.x;
                y += entry->pos.y;
                z += entry->pos.z;
                Hu3DModelPosSet(model, x, y, z);
                func_8001C258_main(model, 4, 0);
                if (i == 3) {
                    func_8001C258_main(obj->model[2], 4, 0);
                    offsetX = sinAngle * 10.0f;
                    offsetZ = cosAngle * 10.0f;
                    Hu3DModelPosSet(obj->model[2], x + offsetX, y - 10.0f, z + offsetZ);
                    func_800146DC_main(data->sprites[2], 4, 4);
                }
                break;
            case 2:
                if (entry->unk1A != 0 && entry->unk14 < maxScale) {
                    step = growStep;
                    goto update;
                }
                entry->unk18 = 3;
                break;
            case 3:
                if (entry->unk1A != 0) {
                    step = shrinkStep;
                update:
                    entry->unk14 += step;
                    Hu3DModelScaleSet(model, entry->unk14, entry->unk14, entry->unk14);
                    x = data->unk10.x - entry->pos.x;
                    y = data->unk10.y - entry->pos.y;
                    z = data->unk10.z - entry->pos.z;
                    x /= entry->unk1A;
                    y /= entry->unk1A;
                    z /= entry->unk1A;
                    entry->pos.x += x;
                    entry->pos.y += y;
                    entry->pos.z += z;
                    y = sindf(entry->unk10) * entry->unk0C;
                    x = y * sinAngle;
                    z = y * cosAngle;
                    y = cosdf(entry->unk10) * entry->unk0C;
                    x += entry->pos.x;
                    y += entry->pos.y;
                    z += entry->pos.z;
                    Hu3DModelPosSet(model, x, y, z);
                    if (i == 3) {
                        offsetX = sinAngle * 10.0f;
                        offsetZ = cosAngle * 10.0f;
                        Hu3DModelPosSet(obj->model[2], x + offsetX, y - 10.0f, z + offsetZ);
                        func_80014714_main(data->sprites[2], entry->unk1A % 8);
                    }
                    entry->unk0C -= entry->unk0C / entry->unk1A;
                    entry->unk10 += 450.0f / data->unk28A;
                    if (entry->unk10 > 360.0f) {
                        entry->unk10 -= 360.0f;
                    } else if (entry->unk10 < 0.0f) {
                        entry->unk10 += 360.0f;
                    }
                    entry->unk1A--;
                } else {
                    entry->unk18 = 0;
                    func_8001C258_main(model, 4, 4);
                    if (i < 13) {
                        HuAudFXPlay(0);
                    }
                }
                break;
        }
    }
    return count;
}

void func_800EB3CC_minigame(omObjData *obj) {
    func_800EA6C4_minigame_ObjData *data = obj->data;
    func_800EA6C4_minigame_Entry *entry;
    s16 model;
    f32 time;
    s32 index;
    s32 i;

    if (data->unk20 > 0) {
        model = obj->model[0];
        switch (data->unk20) {
            case 1:
                func_8001C814_main(model, 1, 0);
                data->unk20 = 2;
                HuAudFXPlay(0);
                break;
            case 2:
                time = Hu3DData[model].motTime;
                if (D_800CCF58_main[Hu3DData[model].motId].unk02 <= time) {
                    data->unk20 = 3;
                    entry = data->unk24;
                    index = 0;
                    for (i = 0; i < 10; i++, entry++) {
                        entry->unk1A = index;
                        index += 2;
                        entry->unk0C = data->unk28C;
                        entry->unk10 = 180.0f;
                        entry->unk14 = data->unk28E;
                        entry->unk18 = 1;
                        entry->pos.x = obj->trans.x;
                        entry->pos.y = obj->trans.y + entry->unk0C;
                        entry->pos.z = obj->trans.z;
                    }
                    entry = data->unk13C;
                    index--;
                    for (i = 0; i < 10; i++, entry++) {
                        entry->unk1A = index;
                        index++;
                        entry->unk0C = data->unk28C;
                        entry->unk10 = 180.0f;
                        entry->unk14 = data->unk28E;
                        entry->unk18 = 1;
                        entry->pos.x = obj->trans.x;
                        entry->pos.y = obj->trans.y + entry->unk0C;
                        entry->pos.z = obj->trans.z;
                    }
                }
                break;
            case 3:
                if (func_800EAE7C_minigame(obj) == 0) {
                    data->unk20 = 0;
                }
                break;
        }
    }
}

void func_800EB5E4_minigame(omObjData *obj) {
    func_800EA6C4_minigame_ObjData *data = obj->data;
    s16 model = obj->model[1];
    f32 maxScale;
    f32 scale;

    Hu3DModelPosSet(model, obj->trans.x, data->unk1C, obj->trans.z);
    // Distance above the shadow plane; reused below as the shadow scale.
    scale = obj->trans.y - data->unk1C - obj->scale.y * 50.0f;
    if (data->unk288 == 0) {
        maxScale = obj->scale.y * 0.58f;
    } else {
        maxScale = obj->scale.y * 1.2f;
    }
    if (scale < 0.0f) {
        scale = maxScale;
    } else {
        scale = maxScale - scale * 0.002f;
        if (scale < 0.00001f) {
            scale = 0.00001f;
        }
    }
    Hu3DModelScaleSet(model, scale, scale, scale);
    Hu3DModelRotSet(model, obj->rot.x, obj->rot.y, obj->rot.z);
}
