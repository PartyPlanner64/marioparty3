#include "common.h"

typedef struct {
    /* 0x00 */ void *unk00;
    /* 0x04 */ s16 unk04;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ char unk0A[0x0E];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ char unk1C[0x68];
} CoconutConkData; // sizeof 0x84

extern omObjData *D_8010B1F0_coconut_conk;
extern omObjData *D_8010B274_coconut_conk;
extern omObjData *D_8010B37C_coconut_conk;
extern omObjData *D_8010B400_coconut_conk;
extern omObjData *D_8010B484_coconut_conk;
extern CoconutConkData D_8010BCC4_coconut_conk;

void func_80105C60_coconut_conk(omObjData *);
void func_801060C8_coconut_conk(omObjData *);
void func_801061F4_coconut_conk(omObjData *);
void func_80106394_coconut_conk(omObjData *);
void func_8010659C_coconut_conk(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801059A0_coconut_conk);

f32 func_801059BC_coconut_conk(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80105A3C_coconut_conk);

void func_80105B04_coconut_conk(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80105B7C_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80105B88_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80105BA4_coconut_conk);

void func_80105C58_coconut_conk(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80105C60_coconut_conk);

void func_80105D58_coconut_conk(void) {
    omObjData *obj = omAddObj(0x3E8, 1, 0xA, -1, func_80105C60_coconut_conk);
    obj->work[0] = 0;
    D_8010B1F0_coconut_conk = obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80105D98_coconut_conk);

void func_801060C0_coconut_conk(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801060C8_coconut_conk);

void func_801061AC_coconut_conk(void) {
    omObjData *obj = omAddObj(0x384, 1, 0xA, -1, func_801060C8_coconut_conk);
    obj->work[0] = 0;
    D_8010B274_coconut_conk = obj;
}

void func_801061EC_coconut_conk(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801061F4_coconut_conk);

void func_80106294_coconut_conk(void) {
    omObjData *obj = omAddObj(0x3B6, 1, 0xA, -1, func_801061F4_coconut_conk);
    obj->work[0] = 0;
    D_8010B37C_coconut_conk = obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801062D4_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80106394_coconut_conk);

void func_8010641C_coconut_conk(void) {
    omObjData *obj = omAddObj(0x35C, 1, 0, -1, func_80106394_coconut_conk);
    obj->work[0] = 0;
    D_8010B400_coconut_conk = obj;
    omSetStatBit(obj, 0xA0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80106468_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_8010659C_coconut_conk);

void func_801066A4_coconut_conk(void) {
    omObjData *obj = omAddObj(0x366, 5, 0xA, -1, func_8010659C_coconut_conk);
    obj->work[0] = 0;
    D_8010B484_coconut_conk = obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801066E4_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801067E0_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80106924_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801069BC_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80106D40_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80106D5C_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80106E80_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80106F18_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80107674_coconut_conk);

void func_80107690_coconut_conk(omObjData *arg0) {
    CoconutConkData *data = &D_8010BCC4_coconut_conk;

    data->unk04 = 0;
    if (D_800CBB6E_main[arg0->work[3]] <= -30) {
        data->unk04 = 1;
    }
    if (D_800CBB6E_main[arg0->work[3]] >= 30) {
        data->unk04 = 2;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801076EC_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801078BC_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80107B8C_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_8010815C_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801089DC_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80108FA0_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801090C4_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801095A4_coconut_conk);

void func_801095C0_coconut_conk(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801095C8_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80109940_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80109DEC_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_8010A344_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_8010A4AC_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_8010A55C_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_8010A5D8_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_8010A610_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_8010A668_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_8010AB4C_coconut_conk);

void func_8010AC88_coconut_conk(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_8010AC90_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_8010AE04_coconut_conk);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", D_8010B1B8_coconut_conk);
