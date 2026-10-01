#include "common.h"
#include "mallocblock.h"
#include "../ovl_81_name/ovl_81.h"

typedef struct UnkStaff {
    char unk_00[0x18];
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} UnkStaff;

typedef struct UnkStaff_1 {
    /* 0x00 */ char unk_00[0x18];
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ char unk_20[8];
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ char unk_2A[2];
} UnkStaff_1;

typedef struct UnkStaff_2 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} UnkStaff_2;

typedef struct UnkStaff_3 { // sizeof 0x3C
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ char unk_0C[0x10];
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ char unk_1E[0x1C];
    /* 0x3A */ s16 unk_3A;
} UnkStaff_3;

typedef struct UnkStaff_4 {
    /* 0x00 */ UnkStaff_3 *unk_00;
    /* 0x08 */ s16 unk_08;
} UnkStaff_4;

typedef struct UnkStaff_5 { // sizeof 0x4C
    /* 0x00 */ char unk_00[0x18];
    /* 0x18 */ Vec unk_18;
    /* 0x24 */ char unk_24[0xC];
    /* 0x30 */ Vec unk_30;
    /* 0x3C */ char unk_3C[0x10];
} UnkStaff_5;

typedef struct UnkStaff_6 { // sizeof 0x8
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ char unk_02[4];
    /* 0x06 */ s16 unk_06;
} UnkStaff_6;

typedef struct UnkStaff_7 { // sizeof 0x14
    /* 0x00 */ void *unk_00;
    /* 0x04 */ f32 *unk_04;
    /* 0x08 */ f32 *unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 count;
} UnkStaff_7;

void func_80105E6C_staff(void *, s16 *, s32);
void func_8010C680_staff(s16 *, s32 *, f32 *, void *);
void func_8010C8F4_staff(UnkStaff_1 *);
void func_8010CD74_staff(UnkStaff_1 *);
void func_8010CFD4_staff(UnkStaff *);
void func_8010FB88_staff(void);
extern f32 D_80110534_staff;
extern s8 D_80110538_staff;
extern char D_80110FF4_staff[]; // unk type
extern Vec D_80111534_staff;
extern Vec D_80111540_staff;
extern f32 D_80111560_staff;
extern f32 D_80111564_staff;
extern UnkStaff_6 *D_801114C8_staff;
extern UnkStaff_6 *D_80111508_staff;

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801059A0_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80105BD4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80105CB4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80105DB8_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80105E6C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80105F48_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010601C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80106044_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010609C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010615C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80106720_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010674C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80106C50_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80106E20_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801073EC_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107508_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107740_staff);

void func_80107A9C_staff(UnkStaff_7 *arg0) {
    s32 i;
    UnkStaff_7 *ptr;

    for (i = 0, ptr = arg0; i < 4; i++, ptr++) {
        HuSprGrpKill(ptr->unk_0C);
        HuSprKill(ptr->unk_0E);
        HuMemFree(ptr->unk_00);
        HuMemFree(ptr->unk_04);
        HuMemFree(ptr->unk_08);
    }
    HuMemFree(arg0);
}

void func_80107B1C_staff(UnkStaff_7 *arg0, f32 arg1) {
    s16 i;
    s16 j;
    s16 count;
    f32 *dest;
    f32 *src;
    UnkStaff_7 *ptr;

    for (i = 0, ptr = arg0; i < 4; i++, ptr++) {
        dest = ptr->unk_04;
        src = ptr->unk_08;
        count = ptr->count;
        for (j = 0; j < count; j++, dest++, src++) {
            *dest = arg1 * *src;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107BA0_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107DBC_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107EB8_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801085F0_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801088F4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010919C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801091CC_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80109264_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801095E4_staff);

void func_8010992C_staff(Process *prc, s16 modelId) {
    UnkStaff_4 *staff = prc->user_data;
    UnkStaff_3 *ptr = staff->unk_00;
    s32 i;

    for (i = 0; i < 3; i++, ptr++) {
        if (ptr->unk_3A != 3) {
            continue;
        }
        if (ptr->unk_1C == modelId) {
            break;
        }
    }
    if (i < 3) {
        ptr->unk_3A |= 4;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010998C_staff);

void func_80109D08_staff(Process *prc, s16 modelId, Vec *pos) {
    UnkStaff_4 *staff = prc->user_data;
    UnkStaff_3 *ptr = staff->unk_00;
    s32 i;

    for (i = 0; i < 3; i++, ptr++) {
        if (ptr->unk_3A != 3) {
            continue;
        }
        if (ptr->unk_1C == modelId) {
            break;
        }
    }
    if (i < 3) {
        ptr->unk_00 = *pos;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80109D74_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80109F34_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010A848_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B1E0_staff);

void func_8010B430_staff(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    HuSprGrp *grp = HuSprGrpData[arg0];
    HuSprite *sprite = grp->members[arg1];

    if ((u32)arg2 || (u32)arg3) {
        grp->unk_0C = 1;
        sprite->unk_48 += arg2;
        sprite->unk_4C += arg3;
    }
}

void func_8010B4B4_staff(s16 arg0, s16 arg1, s16 arg2) {
    f32 value = arg2;
    HuSprGrp *grp = HuSprGrpData[arg0];
    HuSprite *sprite = grp->members[arg1];

    if (sprite->unk_4C == value) {
        return;
    }
    grp->unk_0C = 1;
    sprite->unk_4C = value;
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B514_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B794_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B8C0_staff);

void func_8010B9BC_staff(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    UnkStaff_6 *rec;

    switch (arg0) {
        case 0:
        default:
            rec = &D_801114C8_staff[arg1];
            break;
        case 1:
            rec = &D_80111508_staff[arg1];
            break;
    }

    if (rec->unk_06 != 0) {
        func_80054904_main(rec->unk_00, 0, arg2, arg3);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010BA30_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010BE20_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011133C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111348_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111354_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111360_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011136C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111378_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111384_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111390_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011139C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113A8_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113B4_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113C0_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113CC_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113D8_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113E4_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113F0_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010BF84_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010C680_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010C8F4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010CD74_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010CFD4_staff);

void func_8010D1E8_staff(void) {
    s16 sp10[3][2];
    UnkStaff sp20[8];
    UnkStaff_1 sp120[3];
    s16 sp1A8;
    s32 sp1AC;
    f32 sp1B0;
    s16 var_v0;
    s16 *temp_s2;
    s16 var_s0;
    s32 i;
    UnkStaff_1 *temp;
    UnkStaff *temp2;
    s16 *temp3;

    temp_s2 = HuPrcCurrentGet()->user_data;
    HmfLightDirSet(1, 0.0f, 0.0f, 100.0f);
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(0x20);
    func_800E8180_name_81(1000.0f, 10000.0f);
    func_800E8110_name_81();
    D_80110538_staff = 1;
    D_80111540_staff.x = 350.0f;
    D_80111540_staff.y = 190.0f;
    D_80111540_staff.z = 3770.0f;
    D_80111534_staff.x = -1000.0f;
    D_80111534_staff.y = 130.0f;
    D_80111534_staff.z = 450.0f;
    D_80110534_staff = 40.0f;
    Hu3DCamSetPerspective(0, 40.0f, D_80111564_staff, D_80111560_staff);
    func_80105E6C_staff(D_80110FF4_staff, &sp10[0][0], 3);
    func_8010CFD4_staff(sp20);
    func_8010CD74_staff(sp120);
    *temp_s2 = 0;
    sp1A8 = 0;
    sp1B0 = 90.0f;
    sp1AC = 0;
    for (var_s0 = 0; var_s0 >= 0;) {
        if (var_s0 != *temp_s2) {
            if (*temp_s2 == -1) {
                var_s0 = -1;
            } else {
                var_s0 = *temp_s2;
                func_8010C8F4_staff(sp120);
                func_8010C680_staff(&sp1A8, &sp1AC, &sp1B0, &sp20[3]);
                HuPrcVSleep();
            }
        } else {
            func_8010C8F4_staff(sp120);
            func_8010C680_staff(&sp1A8, &sp1AC, &sp1B0, &sp20[3]);
            HuPrcVSleep();
        }
    }

    // TODO: fix typing of temp3 or sp10
    for (temp3 = sp10[0], i = 0; i < 3; i++, temp3 += 2) {
        func_8001ACDC_main(*temp3); //?
    }
    for (temp2 = sp20, i = 0; i < 8; i++, temp2++) {
        func_8001ACDC_main(temp2->unk_18);
        func_8001ACDC_main(temp2->unk_1A);
        func_80033354_main(temp2->unk_1C);
        if (temp2->unk_1E >= 0) {
            func_8001ACDC_main(temp2->unk_1E);
        }
    }

    for (temp = sp120, i = 0; i < 3; i++, temp++) {
        func_8001ACDC_main(temp->unk_28);
    }

    MBDBackKill();
    MBDBackClose();
    *temp_s2 = 0;
    while (1) {
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010D450_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010D580_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010D998_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DE50_staff);

void func_8010DEDC_staff(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DEE4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DEF4_staff);

void func_8010DF04_staff(UnkStaff_2 *arg0, s16 arg1) {
    arg0->unk_0A = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DF0C_staff);

s16 func_8010DF24_staff(UnkStaff_2 *arg0) {
    return arg0->unk_04;
}

void func_8010DF2C_staff(UnkStaff_2 *arg0, s16 arg1) {
    arg0->unk_06 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DF34_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F04C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F3E4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F4C4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F9D4_staff);

void func_8010FB28_staff(void) {
    Process *prc = omAddPrcObj(func_8010FB88_staff, 0x3F00, 0x2000, 0);
    UnkStaff_5 *data = HuMemAllocTag(sizeof(UnkStaff_5), 0x7918);

    prc->user_data = data;
    data->unk_18.x = 0.0f;
    data->unk_18.y = 100.0f;
    data->unk_18.z = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010FB88_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111430_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011143C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111448_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111454_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111460_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011146C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111478_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111484_staff);
