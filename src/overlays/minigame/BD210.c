#include "common.h"
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
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x024 */ func_800EA6C4_minigame_Entry unk24[10];
    /* 0x13C */ func_800EA6C4_minigame_Entry unk13C[10];
    /* 0x254 */ char unk254[0x2E];
    /* 0x282 */ s16 unk282;
    /* 0x284 */ s16 unk284;
    /* 0x286 */ s16 unk286;
    /* 0x288 */ s16 unk288;
    /* 0x28A */ s16 unk28A;
    /* 0x28C */ s16 unk28C;
    /* 0x28E */ s16 unk28E;
} func_800EA6C4_minigame_ObjData;

extern s16 D_800EBE00_minigame[4];

void func_800EAA58_minigame(omObjData *obj);
void func_800EB3CC_minigame(omObjData *obj);
void func_800EB5E4_minigame(omObjData *obj);

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

void func_800EA8F0_minigame(omObjData *obj, s32 value) {
    func_800EA6C4_minigame_ObjData *data = obj->data;

    data->unk1C = value;
}

void func_800EA8FC_minigame(omObjData *obj, s32 arg1, s32 arg2, s32 arg3) {
    func_800EA6C4_minigame_ObjData *data = obj->data;

    data->unk10 = arg1;
    data->unk14 = arg2;
    data->unk18 = arg3;
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

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BD210", func_800EAA58_minigame);

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

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BD210", func_800EAE7C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BD210", func_800EB3CC_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BD210", func_800EB5E4_minigame);
