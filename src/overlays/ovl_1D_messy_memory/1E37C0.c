#include "common.h"

// One tile tracked by the object made in func_8010F15C_messy_memory. The
// object's work[0] is the index of its entry here. Layout derived from the
// accesses in func_8010EF10_messy_memory.
typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ char unk04[2];
    /* 0x06 */ u16 unk06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ char unk08[0x7C];
} MessyMemoryTile; // sizeof 0x84

extern HuSprite_Unk84_Struct *D_80111654_messy_memory;
extern HuSprite_Unk84_Struct *D_801116D8_messy_memory;
extern omObjData *D_80111A9C_messy_memory;
extern MessyMemoryTile D_80113A94_messy_memory[1];
extern u8 D_80115D8C_messy_memory;

void func_80105B88_messy_memory(Gfx **, s32, s32);
void func_8010F04C_messy_memory(omObjData *object);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_801059A0_messy_memory);

f32 func_801059BC_messy_memory(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80105A3C_messy_memory);

void func_80105B04_messy_memory(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80105B7C_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80105B88_messy_memory);

void func_801060E0_messy_memory(omObjData *obj) {
    switch (D_80115D8C_messy_memory) {
        case 8:
            func_8001C258_main(*obj->model, 4, 0);
            break;
        case 0xC:
            func_8001C258_main(*obj->model, 4, 4);
            break;
    }
}

void func_80106140_messy_memory(omObjData *obj) {
    *obj->model = Hu3DHookFuncCreate(0, func_80105B88_messy_memory, 2);
    Hu3DModelCameraSet(*obj->model, 2);
    func_8001C258_main(*obj->model, 4, 4);
    obj->func = func_801060E0_messy_memory;
}

void func_801061AC_messy_memory(void) {
    omObjData *obj;
    D_80111654_messy_memory = func_80055194_main(func_8000B838_main(0x3E0002));
    D_801116D8_messy_memory = func_80055194_main(func_8000B838_main(0x3E0004));
    obj = omAddObj(0xC8, 1, 0, -1, func_80106140_messy_memory);
    obj->work[0] = 0;
    D_80111A9C_messy_memory = obj;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_801113F0_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_801113FC_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_8011140C_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_8011141C_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_80111428_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_80111434_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_80111440_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_8011144C_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010622C_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_801063FC_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80106588_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80106620_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80106704_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_801067D0_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80106800_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80106C60_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80107C88_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010ACE4_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010AD40_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010B32C_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010B4CC_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010B5C8_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010C03C_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010C37C_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010C478_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010D55C_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010D910_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010DA64_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010E29C_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010E500_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010E654_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010EBB0_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010EE6C_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010EF10_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010F04C_messy_memory);

void func_8010F15C_messy_memory(void) {
    omObjData *obj = omAddObj(0xFA, 1, 0xA, -1, func_8010F04C_messy_memory);
    obj->work[0] = 0;
    D_80113A94_messy_memory[0].obj = obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010F19C_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010F3DC_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010F644_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010F6E8_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010FA38_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010FBB0_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010FC90_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010FD3C_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010FD60_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010FD98_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010FDF0_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_801109BC_messy_memory);

void func_80110D48_messy_memory(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80110D50_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80110EC4_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_801115F4_messy_memory);
