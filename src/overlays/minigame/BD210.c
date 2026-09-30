#include "common.h"

// Per-object state allocated in func_800EA6C4_minigame, stored in the `data`
// pointer (0x5C) of the omObjData it belongs to.
typedef struct func_800EA6C4_minigame_ObjData {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ omObjFunc unk04;
    /* 0x08 */ omObjFunc unk08;
    /* 0x0C */ omObjFunc unk0C;
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

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BD210", func_800EA7F0_minigame);

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
