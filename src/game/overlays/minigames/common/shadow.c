#include "common.h"
#include "game/overlays/minigame.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"

typedef struct MgBoxSparkle {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
} MgBoxSparkle; // Size 0x1C

// Per-object state allocated in MgBoxObjCreate (0x290 bytes), stored
// in the `data` pointer (0x5C) of the omObjData it belongs to.
typedef struct MgBoxWork {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ omObjFunc unk04;
    /* 0x08 */ omObjFunc unk08;
    /* 0x0C */ omObjFunc unk0C;
    /* 0x10 */ Vec unk10;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x024 */ MgBoxSparkle unk24[10];
    /* 0x13C */ MgBoxSparkle unk13C[10];
    /* 0x254 */ s16 sprites[23];
    /* 0x282 */ u16 unk282;
    /* 0x284 */ u16 unk284;
    /* 0x286 */ u16 unk286;
    /* 0x288 */ u16 unk288;
    /* 0x28A */ u16 unk28A;
    /* 0x28C */ u16 unk28C;
    /* 0x28E */ u16 unk28E;
} MgBoxWork;

extern s16 mgBoxMdlTbl[4];

void MgBoxMdlReset(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        mgBoxMdlTbl[i] = -1;
    }
}

omObjData *MgBoxObjCreate(s16 prio, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    omObjData *obj;
    MgBoxWork *data;
    s16 *model;
    s32 i;

    obj = omAddObj(prio, 23, 0, -1, MgBoxObjInit);
    model = obj->model;
    for (i = 0; i < 23; i++) {
        *model++ = -1;
    }
    data = obj->data = HuMemAllocTag(sizeof(MgBoxWork), TAG_OVERLAY);
    memset(data, 0, sizeof(MgBoxWork));
    data->unk282 = arg1;
    data->unk284 = arg2;
    data->unk286 = arg3;
    data->unk288 = arg4;
    data->unk28A = 24;
    data->unk28C = 120;
    data->unk28E = 1;
    data->unk20 = 0;
    data->unk04 = NULL;
    data->unk08 = MgBoxOpenUpdate;
    data->unk0C = MgBoxShadowUpdate;
    return obj;
}

void MgBoxPosSet(omObjData *obj, f32 x, f32 y, f32 z) {
    obj->trans.x = x;
    obj->trans.y = y;
    obj->trans.z = z;
}

void MgBoxRotSet(omObjData *obj, f32 x, f32 y, f32 z) {
    obj->rot.x = x;
    obj->rot.y = y;
    obj->rot.z = z;
}

void MgBoxScaleSet(omObjData *obj, f32 arg1, f32 arg2, f32 arg3) {
    MgBoxWork *data = obj->data;

    obj->scale.x = arg1;
    obj->scale.y = arg2;
    obj->scale.z = arg3;
    data->unk28C = (u32)(arg2 * 120.0f);
    data->unk28E = (u32)arg2;
    if (obj->model[2] >= 0) {
        Hu3DModelPosSet(obj->model[2], arg2 * 3.0f, arg2 * 3.0f, arg2 * 3.0f);
    }
}

void MgBoxShadowYSet(omObjData *obj, f32 value) {
    MgBoxWork *data = obj->data;

    data->unk1C = value;
}

void MgBoxTargetSet(omObjData *obj, f32 x, f32 y, f32 z) {
    MgBoxWork *data = obj->data;

    data->unk10.x = x;
    data->unk10.y = y;
    data->unk10.z = z;
}

void MgBoxStatSet(omObjData *obj, s32 value) {
    MgBoxWork *data = obj->data;

    data->unk20 = value;
}

s32 MgBoxStatGet(omObjData *obj) {
    MgBoxWork *data = obj->data;

    return data->unk20;
}

void MgBoxDispSet(omObjData *obj, u16 arg1) {
    MgBoxSparkle *entry;
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
            entry = ((MgBoxWork *)obj->data)->unk24;
            for (i = 10; i != 0; i--, entry++) {
                entry->unk18 = 0;
            }
            entry = ((MgBoxWork *)obj->data)->unk13C;
            for (i = 10; i != 0; i--, entry++) {
                entry->unk18 = 0;
            }
            break;
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, arg1);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, arg1);
    for (i = 2; i < 23; i++) {
        Hu3DModelAttrSet(obj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
}

void MgBoxObjInit(omObjData *obj) {
    MgBoxWork *data = obj->data;
    s16 sprite;
    s16 model;
    s16 j;
    s16 k;
    s32 i;

    if (mgBoxMdlTbl[0] < 0) {
        mgBoxMdlTbl[0] = model = Hu3DModelRead(0x1C, data->unk282);
    } else {
        model = Hu3DModelLink(mgBoxMdlTbl[0]);
    }
    obj->model[0] = model;
    Hu3DMotionAttrSet(model, 1, 1);

    if (mgBoxMdlTbl[1] < 0) {
        mgBoxMdlTbl[1] = model = Hu3DModelRead3(data->unk288 ? 9 : 1, data->unk284);
    } else {
        model = Hu3DModelLink(mgBoxMdlTbl[1]);
    }
    obj->model[1] = model;

    if (mgBoxMdlTbl[2] < 0) {
        mgBoxMdlTbl[2] = sprite = SprModelRead(12, data->unk286 | 4, 8);
    } else {
        sprite = Hu3DSprModelLink(mgBoxMdlTbl[2], 8);
    }
    data->sprites[2] = sprite;
    model = Hu3DSprModelData[sprite].modelId;
    obj->model[2] = model;
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DSprModelTPLvlSet(sprite, 0xC0);
    Hu3DSprModelColorSet(sprite, 0xFF, 0xFF, 0xBE);
    Hu3DModelObjAttrSet(model, 0x70000000, 0x70000000);
    Hu3DSprModelAttrSet(sprite, 4, 0);
    Hu3DModelScaleSet(model, data->unk28E * 3.0f, data->unk28E * 3.0f, data->unk28E * 3.0f);

    for (j = 3, k = 13, i = 0; i < 10; i++, j++, k++) {
        if (mgBoxMdlTbl[3] < 0) {
            mgBoxMdlTbl[3] = sprite = SprModelRead(10, data->unk286, 8);
        } else {
            sprite = Hu3DSprModelLink(mgBoxMdlTbl[3], 8);
        }
        data->sprites[j] = sprite;
        model = Hu3DSprModelData[sprite].modelId;
        obj->model[j] = model;
        Hu3DModelObjAttrSet(model, 0x70000000, 0x70000000);
        Hu3DModelScaleSet(model, 2.0f, 2.0f, 2.0f);
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);

        sprite = Hu3DSprModelLink(mgBoxMdlTbl[3], 8);
        data->sprites[k] = sprite;
        model = Hu3DSprModelData[sprite].modelId;
        obj->model[k] = model;
        Hu3DModelObjAttrSet(model, 0x70000000, 0x70000000);
        Hu3DModelScaleSet(model, 2.0f, 2.0f, 2.0f);
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DSprModelTPLvlSet(sprite, (u8)(i * 15 + 0x60));
    }
    obj->func = MgBoxObjMain;
}

void MgBoxObjMain(omObjData *arg0) {
    MgBoxWork *data = arg0->data;

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

s32 MgBoxSparkleUpdate(omObjData *obj) {
    MgBoxWork *data = obj->data;
    MgBoxSparkle *entry;
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
                Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                if (i == 3) {
                    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    offsetX = sinAngle * 10.0f;
                    offsetZ = cosAngle * 10.0f;
                    Hu3DModelPosSet(obj->model[2], x + offsetX, y - 10.0f, z + offsetZ);
                    Hu3DSprModelAttrSet(data->sprites[2], 4, 4);
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
                        Hu3DSprModelFrameSet(data->sprites[2], entry->unk1A % 8);
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
                    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    if (i < 13) {
                        HuAudFXPlay(0);
                    }
                }
                break;
        }
    }
    return count;
}

void MgBoxOpenUpdate(omObjData *obj) {
    MgBoxWork *data = obj->data;
    MgBoxSparkle *entry;
    s16 model;
    f32 time;
    s32 index;
    s32 i;

    if (data->unk20 > 0) {
        model = obj->model[0];
        switch (data->unk20) {
            case 1:
                Hu3DMotionAttrSet(model, 1, 0);
                data->unk20 = 2;
                HuAudFXPlay(0);
                break;
            case 2:
                time = Hu3DData[model].motTime;
                if (Hu3DMotion[Hu3DData[model].motId].unk02 <= time) {
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
                if (MgBoxSparkleUpdate(obj) == 0) {
                    data->unk20 = 0;
                }
                break;
        }
    }
}

void MgBoxShadowUpdate(omObjData *obj) {
    MgBoxWork *data = obj->data;
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
