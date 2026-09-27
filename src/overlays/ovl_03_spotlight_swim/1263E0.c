#include "common.h"

extern s16 D_8010CCF4_spotlight_swim[4];
extern s32 D_8010D2F0_spotlight_swim;
extern u32 *D_8010D2F8_spotlight_swim[3];
extern s16 D_8010D3B0_spotlight_swim[8];
extern u32 D_8010D448_spotlight_swim;
extern u32 D_8010D47C_spotlight_swim;

extern omObjData *D_8010D480_spotlight_swim;
extern omObjData *D_8010D504_spotlight_swim;
extern omObjData *D_8010DAB0_spotlight_swim;
extern omObjData *D_8010DB34_spotlight_swim;
extern omObjData *D_8010DCC0_spotlight_swim;

void func_80106150_spotlight_swim(omObjData *);
void func_80106350_spotlight_swim(omObjData *);
void func_801065C4_spotlight_swim(omObjData *);
void func_8010B828_spotlight_swim(omObjData *);
void func_8010C25C_spotlight_swim(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801059A0_spotlight_swim);

f32 func_801059BC_spotlight_swim(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80105A3C_spotlight_swim);

void func_80105B04_spotlight_swim(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

void func_80105B7C_spotlight_swim(s16 arg0, s16 arg1) {
    s16 stopSeNo = D_8010D3B0_spotlight_swim[arg1];

    if (stopSeNo != -1) {
        HuAudFXStop(stopSeNo);
    }

    D_8010D3B0_spotlight_swim[arg1] = func_8004AC98_main(D_8010CCF4_spotlight_swim[arg0], arg1);
}

void func_80105C04_spotlight_swim(s16 arg0, s16 arg1) {
    s16 stopSeNo = D_8010D3B0_spotlight_swim[arg1];

    if (stopSeNo != -1) {
        HuAudFXStop(stopSeNo);
    }

    D_8010D3B0_spotlight_swim[arg1] = func_8004ACE0_main(D_8010CCF4_spotlight_swim[arg0], arg1);
}

s32 func_80105C8C_spotlight_swim(s32 arg0) {
    return rand8() % arg0;
}

void func_80105CE0_spotlight_swim(omObjData *arg0, u16 arg1, s16 arg2) {
    if (arg1 < 0xA) {
        func_8001C5B4_main(arg0->model[0], arg0->motion[arg1]);
        func_8001C814_main(arg0->model[0], arg2, arg2);
    }
}

void func_80105D4C_spotlight_swim(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    if (arg1 < 0xA) {
        func_8001C624_main(arg0->model[0], HmfModelData[arg0->motion[arg1]].unk02, arg2, arg3, arg4);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80105DC8_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80105E9C_spotlight_swim);

void func_80106148_spotlight_swim(omObjData *object) {
}

void func_80106150_spotlight_swim(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x240000, 0x299);
    func_8001C8A8_main(obj->model[0], 1);
    obj->func = func_80106148_spotlight_swim;
}

void func_801061A0_spotlight_swim(void) {
    D_8010D480_spotlight_swim = omAddObj(0x1F4, 1, 0, -1, func_80106150_spotlight_swim);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801061DC_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80106350_spotlight_swim);

void func_801063E4_spotlight_swim(void) {
    D_8010D504_spotlight_swim = omAddObj(0x258, 1, 0, -1, func_80106350_spotlight_swim);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80106420_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801065C4_spotlight_swim);

void func_80106754_spotlight_swim(void) {
    D_8010DCC0_spotlight_swim = omAddObj(0x4B0, 5, 3, -1, func_801065C4_spotlight_swim);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80106790_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80106808_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801069BC_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80106BC8_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80106EB0_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801072C4_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010755C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80107674_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80107710_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801077AC_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801079FC_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80107C10_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010846C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010881C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80108AD8_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109088_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109194_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010932C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109468_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109558_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109690_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801098A8_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109A94_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109C1C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109E08_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109F60_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010A328_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010A670_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010A7AC_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010AAB8_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010ADF8_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010AE9C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010B828_spotlight_swim);

void func_8010BA30_spotlight_swim(void) {
    D_8010DB34_spotlight_swim = omAddObj(0x514, 5, 5, -1, func_8010B828_spotlight_swim);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010BA6C_spotlight_swim);

void func_8010BD10_spotlight_swim(void) {
    u32 i;
    u32 *ptr = D_8010D2F8_spotlight_swim[D_8010D2F0_spotlight_swim];

    for (i = 0; i < 0x35C0; i++) {
        *ptr = D_8010D47C_spotlight_swim | D_8010D448_spotlight_swim;
        ptr++;
    }
}

s32 func_8010BD5C_spotlight_swim(void) {
    u32 i;
    u32 *ptr = D_8010D2F8_spotlight_swim[D_8010D2F0_spotlight_swim];

    for (i = 0; i < 0x4B00; i++) {
        *ptr = D_8010D47C_spotlight_swim | D_8010D448_spotlight_swim;
        ptr++;
    }

    if (D_8010D47C_spotlight_swim >= 8) {
        D_8010D47C_spotlight_swim -= 8;
        return 0;
    }

    D_8010D47C_spotlight_swim = 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010BDE0_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010BFD0_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C094_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C25C_spotlight_swim);

void func_8010C444_spotlight_swim(void) {
    omObjData *obj = omAddObj(0x44C, 1, 0, -1, func_8010C25C_spotlight_swim);
    obj->work[0] = 0;
    D_8010DAB0_spotlight_swim = obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C484_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C52C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C550_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C588_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C5E0_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C900_spotlight_swim);

void func_8010CA00_spotlight_swim(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010CA08_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010CB78_spotlight_swim);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", D_8010D2E0_spotlight_swim);
