#include "common.h"

extern omObjData *D_8010D260_three_door_monty;
extern omObjData *D_8010D680_three_door_monty;
extern omObjData *D_8010D890_three_door_monty;

void func_801071FC_three_door_monty(omObjData *);
void func_8010742C_three_door_monty(omObjData *);
void func_80109594_three_door_monty(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_801059A0_three_door_monty);

f32 func_801059BC_three_door_monty(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 func_80105A3C_three_door_monty(s32 arg0) {
    u32 ret = (rand8() & 0xFF) * arg0;
    return ret >> 8;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80105A74_three_door_monty);

void func_80105B3C_three_door_monty(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80105BB4_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80105CBC_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_801062E8_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_801062F4_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80106390_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010642C_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010658C_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_801066F4_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_801067C4_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_801067E0_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80106868_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80106B98_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80106EDC_three_door_monty);

void func_801071F4_three_door_monty(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_801071FC_three_door_monty);

void func_80107344_three_door_monty(void) {
    omObjData *obj = omAddObj(0x32, 5, 0xA, -1, func_801071FC_three_door_monty);
    obj->work[0] = 0;
    D_8010D260_three_door_monty = obj;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", D_8010CEFC_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80107384_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010742C_three_door_monty);

void func_801074B4_three_door_monty(void) {
    omObjData *obj = omAddObj(0x10E, 1, 0, -1, func_8010742C_three_door_monty);
    obj->work[0] = 0;
    D_8010D890_three_door_monty = obj;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80107500_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80108034_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80108C28_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_801090C8_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010916C_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80109594_three_door_monty);

void func_801096FC_three_door_monty(void) {
    omObjData *obj = omAddObj(0xC8, 5, 0xA, -1, func_80109594_three_door_monty);
    obj->work[0] = 0;
    D_8010D680_three_door_monty = obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010973C_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80109890_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_801099EC_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80109A90_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80109C84_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80109F0C_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010A27C_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010A678_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010B138_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010B5A8_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010B7B8_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010BC08_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010BD88_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010BE64_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010C1B4_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010C2DC_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010C358_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010C390_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010C3E8_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010C8C0_three_door_monty);

void func_8010CA40_three_door_monty(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010CA48_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010CBBC_three_door_monty);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", D_8010D228_three_door_monty);
