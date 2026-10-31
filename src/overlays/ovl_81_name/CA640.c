#include "common.h"
#include "ovl_81.h"

extern s16 D_80102CA4_name_81;
extern u8 D_80102CA6_name_81;
extern s16 D_80102CA8_name_81;
extern s16 D_80102CAA_name_81[];
extern char D_80102C30_name_81[0x20];
extern omObjData *D_80102CB0_name_81;
extern Object *D_80102CB4_name_81;
extern Vec D_80102CE0_name_81;
extern Vec D_80102CEC_name_81;
extern Vec D_80102CF8_name_81;
extern Vec D_80102D04_name_81;
extern Vec D_80102D10_name_81;

void func_800E38B0_name_81(void);
void func_800E4914_name_81(void);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102450_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102458_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102468_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102478_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102484_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102494_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_801024A0_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_801024D0_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102500_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102520_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102540_name_81);

void func_800E2870_name_81(void) {
    D_80102CA4_name_81 = -1;
    D_80102CA6_name_81 = 0;
    D_80102CA8_name_81 = -1;
    D_80102CAA_name_81[0] = D_80102CAA_name_81[1] = -1;
    D_80102CB0_name_81 = NULL;
    D_80102CB4_name_81 = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E28B0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E2978_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E2AD0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E2F84_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E2F94_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E31A0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E3400_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E35C4_name_81);

void func_800E35D4_name_81(void) {
    HuSprGrpKill(D_80102CA8_name_81);
    HuSprAnimKill(D_80102CAA_name_81[0]);
    HuSprAnimKill(D_80102CAA_name_81[1]);
    omDelObj(D_80102CB0_name_81);
    D_80102CB0_name_81 = NULL;
    D_80102CA6_name_81 &= 0xC3;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E363C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E3858_name_81);

void func_800E3868_name_81(void) {
    omDelObj(D_80102CB0_name_81);
    D_80102CB0_name_81 = NULL;
    func_8003B128_main(D_80102C30_name_81);
    D_80102CA6_name_81 &= 0xC3;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E38B0_name_81);

Process *func_800E39AC_name_81(s32 playerIndex) {
    Process *process = omAddPrcObj(func_800E38B0_name_81, 0, 0, 0x40);
    UnkOvl81_1 *work = HuMemMemoryAlloc(process->heap, sizeof(UnkOvl81_1));
    process->user_data = work;
    work->unk_00 = 0;
    work->unk_04 = playerIndex;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E3A0C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E3C6C_name_81);

Process *func_800E415C_name_81(void) {
    return omAddPrcObj(func_800E3C6C_name_81, 0, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E4188_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E47B8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E4914_name_81);

Process *func_800E4A74_name_81(s32 arg0) {
    Process *process = omAddPrcObj(func_800E4914_name_81, 0, 0, 0x40);
    UnkOvl81_1 *work = HuMemMemoryAlloc(process->heap, sizeof(UnkOvl81_1));
    process->user_data = work;
    work->unk_00 = arg0;
    return process;
}

void func_800E4AD0_name_81(void) {
    Hu3DCameraPerspectiveSet(1, 40.0f, 80.0f, 8000.0f);
    Hu3DCameraPosSetV(1, &D_80102CE0_name_81, &D_80102CEC_name_81, &D_80102CF8_name_81);
    Hu3DCamUpdateMtx(1);
    Hu3DCameraViewportSet(1, &D_80102D04_name_81, &D_80102D10_name_81);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E4B38_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E4B64_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E4E64_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E4EAC_name_81);
