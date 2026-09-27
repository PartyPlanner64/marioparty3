#include "common.h"
#include "overlays/minigame.h"

typedef struct UnkCrowdCover {
    /* 0x00 */ Gfx *displayList;
    /* 0x04 */ s32 *entries;
    /* 0x08 */ HuSprite_Unk84_Struct *sprite;
    /* 0x0C */ struct UnkCrowdCover *prev;
    /* 0x10 */ struct UnkCrowdCover *next;
    /* 0x14 */ void (*callback)(struct UnkCrowdCover *);
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19;
    /* 0x1A */ s8 unk_1A;
    /* 0x1B */ s8 unk_1B;
    /* 0x1C */ s8 unk_1C;
    /* 0x1D */ u8 unk_1D;
    /* 0x1E */ u8 unk_1E;
    /* 0x1F */ u8 unk_1F;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ char pad_26[2];
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ Vec unk_30;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ Vec unk_40;
    /* 0x4C */ Vec unk_4C;
    /* 0x58 */ Vec unk_58;
    /* 0x64 */ f32 unk_64;
} UnkCrowdCover; // sizeof 0x68

typedef struct {
    /* 0x00 */ s16 unk00[9];
} UnkCrowdCoverVec; // sizeof 0x12

// Per-player work allocated in func_80107298_crowd_cover, stored at ObjData->unk158
typedef struct {
    /* 0x00 */ char unk00[0x20];
    /* 0x20 */ s16 unk20;
    /* 0x22 */ char unk22[2];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 unk29;
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ u8 unk2C;
    /* 0x2D */ u8 unk2D;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 unk2F;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ u16 unk34;
    /* 0x36 */ u16 unk36;
    /* 0x38 */ char unk38[0x1C];
} UnkCrowdCoverWork; // sizeof 0x54

extern UnkCrowdCover *D_8010D8EC_crowd_cover;

extern HuSprite_Unk84_Struct *D_800C9530_main[];

extern u32 D_8010C800_crowd_cover;

extern UnkCrowdCoverVec D_8010CC70_crowd_cover;

void func_80107E40_crowd_cover(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_801059A0_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80105B58_crowd_cover);

void func_80105C54_crowd_cover(HuMtx4F mtx, f32 x, f32 y, f32 z, f32 *dst) {
    dst[0] = ((x * mtx[0][0]) + (y * mtx[1][0])) + (z * mtx[2][0]);
    dst[1] = ((x * mtx[0][1]) + (y * mtx[1][1])) + (z * mtx[2][1]);
    dst[2] = ((x * mtx[0][2]) + (y * mtx[1][2])) + (z * mtx[2][2]);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80105CD4_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80105EC4_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80105FD0_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_801060C4_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CAF0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CAF8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CB00_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80106144_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CB48_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80106580_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80106CB8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CB70_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CB78_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CBD8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CBE0_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80106D4C_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80107298_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CBF8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CC00_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CC08_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80107554_crowd_cover);

u16 func_80107C5C_crowd_cover(omObjData *arg0) {
    UnkCrowdCoverVec vec = D_8010CC70_crowd_cover;
    UnkCrowdCoverWork *work;
    s16 remaining;
    u16 result = 0;

    work = OM_GET_DATA_PTR(arg0, func_800E1BA8_minigame_ObjData)->unk158;
    remaining = --work->unk34;
    if (remaining == 0) {
        result = work->unk36;
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80107CE0_crowd_cover);

void func_80107E0C_crowd_cover(void) {
    omAddObj(3, 0xB, 0x32, -1, func_80107E40_crowd_cover);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CC70_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CC84_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CDEC_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80107E40_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80108238_crowd_cover);

s32 func_80108F1C_crowd_cover(void) {
    D_8010C800_crowd_cover = D_8010C800_crowd_cover * 0x41C64E6D + 0x3039;
    D_8010C800_crowd_cover += rand8();
    return D_8010C800_crowd_cover >> 16;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80108F74_crowd_cover);

f32 func_80108FDC_crowd_cover(Vec *arg0, Vec *arg1) {
    return sqrtf(((arg0->x - arg1->x) * (arg0->x - arg1->x)) +
                 ((arg0->y - arg1->y) * (arg0->y - arg1->y)) +
                 ((arg0->z - arg1->z) * (arg0->z - arg1->z)));
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80109044_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_801090CC_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_801091FC_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80109244_crowd_cover);

HuSprite_Unk84_Unk00_Struct *func_8010930C_crowd_cover(s16 groupId, s16 member) {
    return &func_80055194_main(groupId)->unk00[member];
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80109354_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010949C_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010980C_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE38_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE3C_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", jtbl_8010CE40_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE60_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE68_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE70_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE78_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE80_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE88_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE90_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE98_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEA0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEA8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEB0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEB8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEC0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEC8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CED0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CED8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEE0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEE8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEF0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEF8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF00_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF08_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF10_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF18_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF20_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF28_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF30_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF38_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF40_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF48_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010A12C_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010A734_crowd_cover);

void func_8010ACBC_crowd_cover(s16 index, s16 spriteId) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->sprite = D_800C9530_main[spriteId];
        crowd->unk_20 = 0x100;
        crowd->unk_1F = 0xFF;
        crowd->unk_1E = 0xFF;
        crowd->unk_1D = 0xFF;
        crowd->unk_2C = 0;
        crowd->unk_24 = 0;
        crowd->unk_30.x = 1.0f;
    }
}

void func_8010AD3C_crowd_cover(s16 index, s16 value) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_24 = value;
        crowd->unk_2C = 0;
    }
}

void func_8010AD7C_crowd_cover(s16 index, f32 value) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_30.x = value;
    }
}

void func_8010ADBC_crowd_cover(s16 index, f32 y, f32 z, f32 unk_3C) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_28 |= 0x4000000;
        crowd->unk_30.y = y;
        crowd->unk_30.z = z;
        crowd->unk_3C = unk_3C;
    }
}

void func_8010AE1C_crowd_cover(s16 index, f32 value) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_3C = value;
    }
}

void func_8010AE5C_crowd_cover(s16 index, f32 x, f32 y, f32 z) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_40.x = x;
        crowd->unk_40.y = y;
        crowd->unk_40.z = z;
    }
}

void func_8010AEAC_crowd_cover(s16 index, f32 x, f32 y, f32 z) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_40.x += x;
        crowd->unk_40.y += y;
        crowd->unk_40.z += z;
    }
}

void func_8010AF14_crowd_cover(s16 index, f32 x, f32 y, f32 z) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_4C.x = x;
        crowd->unk_4C.y = y;
        crowd->unk_4C.z = z;
    }
}

void func_8010AF64_crowd_cover(s16 index, f32 x, f32 y, f32 z) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_58.x = x;
        crowd->unk_58.y = y;
        crowd->unk_58.z = z;
    }
}

void func_8010AFB4_crowd_cover(s16 index, s32 value) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_28 |= value;
    }
}

void func_8010AFF8_crowd_cover(s16 index, s32 value) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_28 &= ~value;
    }
}

s32 func_8010B040_crowd_cover(s16 index) {
    UnkCrowdCover *crowd;
    s32 i = index;

    if (i != -1) {
        crowd = &D_8010D8EC_crowd_cover[i];
        return crowd->unk_28;
    }
    return -1;
}

void func_8010B080_crowd_cover(s16 index, s8 value) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_1A = value;
    }
}

UnkCrowdCover *func_8010B0BC_crowd_cover(s16 index) {
    UnkCrowdCover *crowd;
    s32 i = index;

    if (i == -1) {
        return NULL;
    }
    crowd = &D_8010D8EC_crowd_cover[i];
    return crowd;
}

s32 *func_8010B0FC_crowd_cover(s16 index) {
    UnkCrowdCover *crowd;
    s32 i = index;

    if (i == -1) {
        return NULL;
    }
    crowd = &D_8010D8EC_crowd_cover[i];
    return crowd->entries;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B140_crowd_cover);

void func_8010B1DC_crowd_cover(s16 index, s8 value1, s8 value2, s8 value3, s16 value4) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->unk_1D = value1;
        crowd->unk_1E = value2;
        crowd->unk_1F = value3;
        crowd->unk_20 = value4;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B228_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B308_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B408_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B4D8_crowd_cover);

void func_8010B610_crowd_cover(s16 index, void (*callback)(struct UnkCrowdCover *)) {
    UnkCrowdCover *crowd;

    if (index != -1) {
        crowd = &D_8010D8EC_crowd_cover[index];
        crowd->callback = callback;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B64C_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B6BC_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B754_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B8A8_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010BB4C_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010BD74_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010C45C_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010C61C_crowd_cover);
