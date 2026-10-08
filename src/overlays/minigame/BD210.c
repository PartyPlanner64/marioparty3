#include "common.h"

// Per-object state allocated in func_800EA6C4_minigame (0x290 bytes), stored
// in the `data` pointer (0x5C) of the omObjData it belongs to.
typedef struct func_800EA6C4_minigame_ObjData {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ omObjFunc unk04;
    /* 0x08 */ omObjFunc unk08;
    /* 0x0C */ omObjFunc unk0C;
    /* 0x10 */ char unk10[0x272];
    /* 0x282 */ s16 unk282;
    /* 0x284 */ s16 unk284;
    /* 0x286 */ s16 unk286;
    /* 0x288 */ s16 unk288;
    /* 0x28A */ s16 unk28A;
    /* 0x28C */ s16 unk28C;
    /* 0x28E */ s16 unk28E;
} func_800EA6C4_minigame_ObjData;

extern s16 D_800EBE00_minigame[4];

void func_800EA690_minigame(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_800EBE00_minigame[i] = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BD210", func_800EA6C4_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BD210", func_800EA7D0_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BD210", func_800EA7E0_minigame);

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

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BD210", func_800EA8F0_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BD210", func_800EA8FC_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BD210", func_800EA910_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BD210", func_800EA91C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BD210", func_800EA928_minigame);

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
