#include "common.h"

typedef struct FowlEntry {
    /* 0x00 */ char unk_00[0xC];
    /* 0x0C */ u8 unk_0C;
    /* 0x0D */ u8 unk_0D;
    /* 0x0E */ u8 unk_0E;
    /* 0x0F */ u8 unk_0F;
} FowlEntry; // Size 0x10

typedef struct Fowl {
    /* 0x00 */ void *unk_00;
    /* 0x04 */ FowlEntry *unk_04;
    /* 0x08 */ HuSprite_Unk84_Struct *sprite;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19;
    /* 0x1A */ u8 unk_1A;
    /* 0x1B */ s8 unk_1B;
    /* 0x1C */ s8 unk_1C;
    /* 0x1D */ u8 unk_1D;
    /* 0x1E */ u8 unk_1E;
    /* 0x1F */ u8 unk_1F;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ Vec unk_40;
    /* 0x4C */ Vec unk_4C;
    /* 0x58 */ Vec unk_58;
    /* 0x64 */ s32 unk_64;
} Fowl; // sizeof 0x68

extern Fowl *D_8010F32C_fowl_play;

extern HuSprite_Unk84_Struct *D_800C9530_main[];

extern u32 D_8010E8C8_fowl_play;

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_801059A0_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_80105BEC_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_80105E4C_fowl_play);

void func_801064A8_fowl_play(HuMtx4F mtx, f32 x, f32 y, f32 z, f32 *dst) {
    dst[0] = ((x * mtx[0][0]) + (y * mtx[1][0])) + (z * mtx[2][0]);
    dst[1] = ((x * mtx[0][1]) + (y * mtx[1][1])) + (z * mtx[2][1]);
    dst[2] = ((x * mtx[0][2]) + (y * mtx[1][2])) + (z * mtx[2][2]);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_80106528_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_80106718_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_80106824_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_801068F0_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_80106960_fowl_play);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", D_8010EC28_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_80106BD0_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_801070FC_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010724C_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_801075B0_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_801079B0_fowl_play);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", D_8010ED88_fowl_play);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", D_8010ED90_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_80107A4C_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_80108020_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_80108298_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_80108A70_fowl_play);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", D_8010EE68_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_80108B08_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_80109410_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_80109424_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_801094A4_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_80109844_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010A738_fowl_play);

s32 func_8010A9A0_fowl_play(void) {
    D_8010E8C8_fowl_play = (D_8010E8C8_fowl_play + (rand8() & 0xFF)) * 0x41C64E6D + 0x3039;
    return D_8010E8C8_fowl_play >> 16;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010A9EC_fowl_play);

f32 func_8010AA64_fowl_play(Vec *arg0, Vec *arg1) {
    return sqrtf(((arg0->x - arg1->x) * (arg0->x - arg1->x)) +
                 ((arg0->z - arg1->z) * (arg0->z - arg1->z)));
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010AAB8_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010AB40_fowl_play);

f32 func_8010AC04_fowl_play(Vec *arg0, Vec *arg1, Vec *arg2) {
    f32 dot = (arg2->x * (arg1->x - arg0->x)) + (arg2->y * (arg1->y - arg0->y)) +
              (arg2->z * (arg1->z - arg0->z));
    f32 len = -((arg2->x * arg2->x) + (arg2->y * arg2->y) + (arg2->z * arg2->z));

    if (len != 0.0f) {
        dot /= len;
    }
    return dot;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010AC88_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010AE10_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010B1A0_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010B2C4_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010B30C_fowl_play);

HuSprite_Unk84_Unk00_Struct *func_8010B3D4_fowl_play(s16 arg0, s16 arg1) {
    return &func_80055194_main(arg0)->unk00[arg1];
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010B41C_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010B564_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010B8D4_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010C1F4_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010C7FC_fowl_play);

void func_8010CD84_fowl_play(s16 index, s16 spriteId) {
    Fowl *fowl;

    if (index != -1) {
        fowl = D_8010F32C_fowl_play + index;
        fowl->sprite = D_800C9530_main[spriteId];
        fowl->unk_20 = 0x100;
        fowl->unk_1F = 0xFF;
        fowl->unk_1E = 0xFF;
        fowl->unk_1D = 0xFF;
        fowl->unk_2C = 0;
        fowl->unk_24 = 0;
        fowl->unk_30 = 1.0f;
    }
}

void func_8010CE04_fowl_play(s16 arg0, s16 arg1) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_24 = arg1;
        fowl->unk_2C = 0;
    }
}

void func_8010CE44_fowl_play(s16 arg0, f32 arg1) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_30 = arg1;
    }
}

void func_8010CE84_fowl_play(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_28 |= 0x4000000;
        fowl->unk_34 = arg1;
        fowl->unk_38 = arg2;
        fowl->unk_3C = arg3;
    }
}

void func_8010CEE4_fowl_play(s16 arg0, f32 arg1) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_3C = arg1;
    }
}

void func_8010CF24_fowl_play(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_40.x = arg1;
        fowl->unk_40.y = arg2;
        fowl->unk_40.z = arg3;
    }
}

void func_8010CF74_fowl_play(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_40.x += arg1;
        fowl->unk_40.y += arg2;
        fowl->unk_40.z += arg3;
    }
}

void func_8010CFDC_fowl_play(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_4C.x = arg1;
        fowl->unk_4C.y = arg2;
        fowl->unk_4C.z = arg3;
    }
}

void func_8010D02C_fowl_play(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_58.x = arg1;
        fowl->unk_58.y = arg2;
        fowl->unk_58.z = arg3;
    }
}

void func_8010D07C_fowl_play(s16 arg0, s32 arg1) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_28 |= arg1;
    }
}

void func_8010D0C0_fowl_play(s16 arg0, s32 arg1) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_28 &= ~arg1;
    }
}

s32 func_8010D108_fowl_play(s16 arg0) {
    Fowl *fowl;
    s32 i = arg0;

    if (i != -1) {
        fowl = D_8010F32C_fowl_play + i;
        return fowl->unk_28;
    }
    return -1;
}

void func_8010D148_fowl_play(s16 arg0, s8 arg1) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_1A = arg1;
    }
}

Fowl *func_8010D184_fowl_play(s16 arg0) {
    Fowl *fowl;
    s32 i = arg0;

    if (i == -1) {
        return NULL;
    }
    fowl = &D_8010F32C_fowl_play[i];
    return fowl;
}

void *func_8010D1C4_fowl_play(s16 arg0) {
    Fowl *fowl;
    s32 i = arg0;

    if (i == -1) {
        return NULL;
    }
    fowl = D_8010F32C_fowl_play + i;
    return fowl->unk_04;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010D208_fowl_play);

void func_8010D2A4_fowl_play(s16 arg0, s8 arg1, s8 arg2, s8 arg3, s16 arg4) {
    s32 i = arg0;

    if (i != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + i;
        fowl->unk_1D = arg1;
        fowl->unk_1E = arg2;
        fowl->unk_1F = arg3;
        fowl->unk_20 = arg4;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010D2F0_fowl_play);

void func_8010D3D0_fowl_play(s32 index, s32 flag) {
    Fowl *fowl = D_8010F32C_fowl_play + index;
    s32 i;

    if (flag != 0) {
        fowl->unk_28 |= 0x10000;
        for (i = 0; i < fowl->unk_18; i++) {
            fowl->unk_04[i].unk_0C = 0;
            fowl->unk_04[i].unk_0D = 0;
            fowl->unk_04[i].unk_0E = 0x80;
        }
        return;
    }
    fowl->unk_28 &= ~0x10000;
    for (i = 0; i < fowl->unk_18; i++) {
        fowl->unk_04[i].unk_0C = 0xFF;
        fowl->unk_04[i].unk_0D = 0xFF;
        fowl->unk_04[i].unk_0E = 0xFF;
        fowl->unk_04[i].unk_0F = 0xFF;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010D4D0_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010D5A0_fowl_play);

void func_8010D6D8_fowl_play(s16 arg0, s32 arg1) {
    if (arg0 != -1) {
        Fowl *fowl = D_8010F32C_fowl_play + arg0;
        fowl->unk_14 = arg1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010D714_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010D784_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010D81C_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010D970_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010DC24_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010DE4C_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010E544_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010E704_fowl_play);
