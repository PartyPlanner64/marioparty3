#include "common.h"

// One entry of the 50 entry object table at D_8010B4B0_curtain_call. Layout
// derived from the table clear in func_80105A3C_curtain_call, which walks 50
// entries of 0x84 bytes.
typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ s16 unk_40[2];
    /* 0x44 */ Vec unk_44;
    /* 0x50 */ Vec unk_50;
    /* 0x5C */ Vec unk_5C;
    /* 0x68 */ f32 unk_68[4];
    /* 0x78 */ Vec unk_78;
} CurtainCallEntry; // sizeof 0x84

extern CurtainCallEntry D_8010B4B0_curtain_call[50];
extern omObjData *D_8010BA5C_curtain_call;
extern omObjData *D_8010BB64_curtain_call;
extern Process *D_8010CF34_curtain_call;
extern s8 D_8010CEC1_curtain_call;

void func_801062EC_curtain_call(void);
void func_8010AF78_curtain_call(void);
void func_80106500_curtain_call(omObjData *);
void func_80108F28_curtain_call(omObjData *);
void func_801092F0_curtain_call(omObjData *);

void func_801059A0_curtain_call(void) {
    func_8010AF78_curtain_call();
}

f32 func_801059BC_curtain_call(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

void func_80105A3C_curtain_call(void) {
    CurtainCallEntry *entry;
    u32 i;

    for (i = 0, entry = D_8010B4B0_curtain_call; i < 50; i++, entry++) {
        entry->obj = NULL;
        entry->unk_04 = 0;
        entry->unk_06 = 0;
        entry->unk_08 = 0;
        entry->unk_0A = 0;
        entry->unk_0C = 0;
        entry->unk_0E = 0;
        entry->unk_10 = 0;
        entry->unk_12 = 0;
        entry->unk_14 = 0;
        entry->unk_16 = 0;
        entry->unk_18 = 0;
        entry->unk_1C = 0;
        entry->unk_20 = 0;
        entry->unk_24 = 0;
        entry->unk_28 = 0;
        entry->unk_2C = 0;
        entry->unk_30 = 0;
        entry->unk_34 = 0;
        entry->unk_38 = 0;
        entry->unk_3C = 0;
        entry->unk_40[0] = -1;
        entry->unk_40[1] = -1;
        entry->unk_44.x = entry->unk_44.y = entry->unk_44.z = 0.0f;
        entry->unk_50.x = entry->unk_50.y = entry->unk_50.z = 0.0f;
        entry->unk_5C.x = entry->unk_5C.y = entry->unk_5C.z = 0.0f;
        entry->unk_68[0] = 0.0f;
        entry->unk_68[1] = 0.0f;
        entry->unk_68[2] = 0.0f;
        entry->unk_68[3] = 0.0f;
        entry->unk_78.x = entry->unk_78.y = entry->unk_78.z = 0.0f;
    }
}

void func_80105B04_curtain_call(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

s32 func_80105B7C_curtain_call(s32 arg0) {
    return rand8() % arg0;
}

void func_80105BD0_curtain_call(omObjData *arg0, u16 arg1, s16 arg2) {
    if (arg1 < 0xA) {
        func_8001C5B4_main(arg0->model[0], arg0->motion[arg1]);
        func_8001C814_main(arg0->model[0], arg2, arg2);
    }
}

void func_80105C3C_curtain_call(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s32 arg4) {
    if (arg1 < 0xA) {
        Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[arg1]].motId, arg2, arg3, arg4);
    }
}

s32 func_80105CB8_curtain_call(omObjData *obj, f32 target) {
    if (obj->rot.y != target) {
        obj->rot.y = func_801059BC_curtain_call(obj->rot.y, 10.0f);
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80105D14_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_801062EC_curtain_call);

void func_80106408_curtain_call(void) {
    D_800D6A58_main = 1;
    HuWinInit();
    D_8010CF34_curtain_call = omAddPrcObj(func_801062EC_curtain_call, 0x3F00, 0x800, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010644C_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80106494_curtain_call);

void func_801064A0_curtain_call(omObjData *arg0) {
    switch (D_8010CEC1_curtain_call) {
        case 3:
            func_8001C258_main(arg0->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            break;
        case 5:
            func_8001C258_main(arg0->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80106500_curtain_call);

void func_80106688_curtain_call(void) {
    D_8010B4B0_curtain_call[0].obj = omAddObj(0x1F4, 4, 2, -1, func_80106500_curtain_call);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_801066C4_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B32C_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B338_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B344_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B350_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B35C_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B368_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B374_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B380_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_801067A8_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80106988_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80106AB4_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80106B78_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80106C18_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80107560_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80107680_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80107D20_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_801084A0_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80108670_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_801089FC_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80108E64_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80108EF8_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80108F28_curtain_call);

void func_801090FC_curtain_call(void) {
    D_8010BA5C_curtain_call = omAddObj(0x258, 3, 2, -1, func_80108F28_curtain_call);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80109138_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_801092F0_curtain_call);

void func_801093C4_curtain_call(void) {
    D_8010BB64_curtain_call = omAddObj(0x384, 1, 1, -1, func_801092F0_curtain_call);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80109400_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010954C_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010982C_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80109920_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_80109AD0_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010A734_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010A7D8_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010A7FC_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010A8E8_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010A948_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010AD68_curtain_call);

void func_8010AE00_curtain_call(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010AE08_curtain_call);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010AF78_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B4A0_curtain_call);
