#include "common.h"

// Per-chomp state at D_8010C420_merry_go_chomp, indexed by omObjData::work[0]
typedef struct D_8010C420_merry_go_chomp_Entry {
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ s8 unk_18[4];
    /* 0x1C */ s8 unk_1C[4];
    /* 0x20 */ s8 unk_20[4];
} D_8010C420_merry_go_chomp_Entry; // Size 0x24

typedef struct D_8010C794_merry_go_chomp_Entry {
    /* 0x00 */ omObjData *unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ char unk_10[4];
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ char unk_16[2];
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ char unk_28[0x5C];
} D_8010C794_merry_go_chomp_Entry; // Size 0x84

extern D_8010C420_merry_go_chomp_Entry D_8010C420_merry_go_chomp[];
extern D_8010C794_merry_go_chomp_Entry D_8010C794_merry_go_chomp[];

extern omObjData *D_8010C500_merry_go_chomp;
extern omObjData *D_8010CA28_merry_go_chomp;
extern omObjData *D_8010CCBC_merry_go_chomp;
extern omObjData *D_8010D1E4_merry_go_chomp;
extern omObjData *D_8010D478_merry_go_chomp;

void func_80106384_merry_go_chomp(omObjData *);
void func_801064E8_merry_go_chomp(omObjData *);
void func_80106920_merry_go_chomp(omObjData *);
void func_8010A9D0_merry_go_chomp(omObjData *);
void func_8010AE2C_merry_go_chomp(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_801059A0_merry_go_chomp);

f32 func_801059BC_merry_go_chomp(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 func_80105A3C_merry_go_chomp(u32 arg0) {
    return (rand8() * arg0) >> 8;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80105A74_merry_go_chomp);

void func_80105B3C_merry_go_chomp(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80105BB4_merry_go_chomp);

s32 func_80105CE4_merry_go_chomp(s32 arg0) {
    return rand8() % arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80105D38_merry_go_chomp);

void func_80105DA0_merry_go_chomp(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    Hu3DMotionShiftSet(arg0->model[0], HmfModelData[arg0->motion[arg1]].unk02, arg2, arg3, arg4);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80105E0C_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80105F40_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80106054_merry_go_chomp);

void func_8010637C_merry_go_chomp(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80106384_merry_go_chomp);

void func_801064A0_merry_go_chomp(void) {
    omObjData *obj = omAddObj(0x1F4, 1, 1, -1, func_80106384_merry_go_chomp);
    obj->work[0] = 0;
    D_8010C500_merry_go_chomp = obj;
}

void func_801064E0_merry_go_chomp(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_801064E8_merry_go_chomp);

void func_8010662C_merry_go_chomp(void) {
    D_8010CCBC_merry_go_chomp = omAddObj(0x2BC, 4, 1, -1, func_801064E8_merry_go_chomp);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80106668_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80106920_merry_go_chomp);

void func_80106AB8_merry_go_chomp(void) {
    D_8010D1E4_merry_go_chomp = omAddObj(0x258, 5, 1, -1, func_80106920_merry_go_chomp);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80106AF4_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80106B9C_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80106CC4_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80107664_merry_go_chomp);

void func_801077D0_merry_go_chomp(omObjData *obj) {
    D_8010C420_merry_go_chomp_Entry *entry = &D_8010C420_merry_go_chomp[obj->work[0]];

    obj->trans.x += entry->unk_00.x;
    obj->trans.z += entry->unk_00.y;
    obj->rot.y = entry->unk_00.z;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80107818_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80107980_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80107E34_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_801084C8_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80108A88_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_801090B0_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80109420_merry_go_chomp);

void func_80109604_merry_go_chomp(void) {
    D_8010C794_merry_go_chomp_Entry *entry;
    s8 i;

    for (i = 0; i < 4; i++) {
        entry = &D_8010C794_merry_go_chomp[i];
        GwPlayer[entry->unk_00->work[0]].bonusCoin = entry->unk_0E;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80109670_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80109A04_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010A9D0_merry_go_chomp);

void func_8010ADE8_merry_go_chomp(void) {
    D_8010CA28_merry_go_chomp = omAddObj(0x384, 0xF, 4, -1, func_8010A9D0_merry_go_chomp);
}

void func_8010AE24_merry_go_chomp(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010AE2C_merry_go_chomp);

void func_8010AECC_merry_go_chomp(void) {
    D_8010D478_merry_go_chomp = omAddObj(0x3E8, 1, 1, -1, func_8010AE2C_merry_go_chomp);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010AF08_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010BAB8_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010BB7C_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010BBA0_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010BBD8_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010BC30_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010BDE8_merry_go_chomp);

void func_8010BEB4_merry_go_chomp(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010BEBC_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010C030_merry_go_chomp);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", D_8010C400_merry_go_chomp);
