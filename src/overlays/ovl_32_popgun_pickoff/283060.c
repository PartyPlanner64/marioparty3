#include "common.h"

typedef struct {
    void *unk_00;
    void *unk_04;
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    s32 unk_14;
    s8 unk_18;
    s8 unk_19;
    s8 unk_1A;
    s8 unk_1B;
    s8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
    u8 unk_1F;
    u16 unk_20;
    char unk_22[2];
    s16 unk_24;
    char unk_26[2];
    s32 unk_28;
    s32 unk_2C;
    f32 unk_30;
    f32 unk_34;
    f32 unk_38;
    f32 unk_3C;
    f32 unk_40;
    f32 unk_44;
    f32 unk_48;
    f32 unk_4C;
    f32 unk_50;
    f32 unk_54;
    f32 unk_58;
    f32 unk_5C;
    f32 unk_60;
    f32 unk_64;
} PopgunPickoffPlayer; // Size 0x68

extern PopgunPickoffPlayer *D_8010DDD8_popgun_pickoff;

extern HuSprite_Unk84_Struct *D_800C9530_main[];

extern u32 D_8010C5F4_popgun_pickoff;

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_801059A0_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80105AFC_popgun_pickoff);

void func_80105BF8_popgun_pickoff(HuMtx4F mtx, f32 x, f32 y, f32 z, f32 *dst) {
    dst[0] = ((x * mtx[0][0]) + (y * mtx[1][0])) + (z * mtx[2][0]);
    dst[1] = ((x * mtx[0][1]) + (y * mtx[1][1])) + (z * mtx[2][1]);
    dst[2] = ((x * mtx[0][2]) + (y * mtx[1][2])) + (z * mtx[2][2]);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80105C78_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80105E68_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80105F74_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80106068_popgun_pickoff);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", D_8010C8E0_popgun_pickoff);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", D_8010C928_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_801060E8_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_801068D0_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80106A44_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010704C_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80107A54_popgun_pickoff);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", D_8010CA78_popgun_pickoff);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", D_8010CAA8_popgun_pickoff);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", D_8010CAB0_popgun_pickoff);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", D_8010CB10_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80107B20_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_801080DC_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80108398_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010880C_popgun_pickoff);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", D_8010CB78_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80108A78_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80108CF0_popgun_pickoff);

s32 func_80108E1C_popgun_pickoff(void) {
    D_8010C5F4_popgun_pickoff = D_8010C5F4_popgun_pickoff * 0x41C64E6D + 0x3039;
    D_8010C5F4_popgun_pickoff += rand8();
    return D_8010C5F4_popgun_pickoff >> 16;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80108E74_popgun_pickoff);

f32 func_80108EF4_popgun_pickoff(Vec *arg0, Vec *arg1) {
    return sqrtf(((arg0->x - arg1->x) * (arg0->x - arg1->x)) +
                 ((arg0->y - arg1->y) * (arg0->y - arg1->y)) +
                 ((arg0->z - arg1->z) * (arg0->z - arg1->z)));
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80108F5C_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80108FE4_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80109108_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80109150_popgun_pickoff);

HuSprite_Unk84_Unk00_Struct *func_80109218_popgun_pickoff(s16 groupId, s16 member) {
    return &func_80055194_main(groupId)->unk00[member];
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80109260_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_801093A8_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80109718_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010A024_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010A62C_popgun_pickoff);

void func_8010ABB4_popgun_pickoff(s16 playerId, s16 spriteId) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_08 = D_800C9530_main[spriteId];
        player->unk_1F = 0xFF;
        player->unk_1E = 0xFF;
        player->unk_1D = 0xFF;
        player->unk_20 = 0xFF;
        player->unk_2C = 0;
        player->unk_24 = 0;
        player->unk_30 = 1.0f;
    }
}

void func_8010AC34_popgun_pickoff(s16 playerId, s16 value) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_24 = value;
        player->unk_2C = 0;
    }
}

void func_8010AC74_popgun_pickoff(s16 playerId, f32 value) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_30 = value;
    }
}

void func_8010ACB4_popgun_pickoff(s16 playerId, f32 x, f32 y, f32 z) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_28 |= 0x4000000;
        player->unk_34 = x;
        player->unk_38 = y;
        player->unk_3C = z;
    }
}

void func_8010AD14_popgun_pickoff(s16 playerId, f32 value) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_3C = value;
    }
}

void func_8010AD54_popgun_pickoff(s16 playerId, f32 x, f32 y, f32 z) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_40 = x;
        player->unk_44 = y;
        player->unk_48 = z;
    }
}

void func_8010ADA4_popgun_pickoff(s16 playerId, f32 x, f32 y, f32 z) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_40 += x;
        player->unk_44 += y;
        player->unk_48 += z;
    }
}

void func_8010AE0C_popgun_pickoff(s16 playerId, f32 x, f32 y, f32 z) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_4C = x;
        player->unk_50 = y;
        player->unk_54 = z;
    }
}

void func_8010AE5C_popgun_pickoff(s16 playerId, f32 x, f32 y, f32 z) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_58 = x;
        player->unk_5C = y;
        player->unk_60 = z;
    }
}

void func_8010AEAC_popgun_pickoff(s16 playerId, s32 value) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_28 |= value;
    }
}

void func_8010AEF0_popgun_pickoff(s16 playerId, s32 value) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_28 &= ~value;
    }
}

s32 func_8010AF38_popgun_pickoff(s16 playerId) {
    PopgunPickoffPlayer *player;
    s32 id = playerId;

    if (id != -1) {
        player = D_8010DDD8_popgun_pickoff + id;
        return player->unk_28;
    }
    return -1;
}

void func_8010AF78_popgun_pickoff(s16 playerId, s8 value) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_1A = value;
    }
}

PopgunPickoffPlayer *func_8010AFB4_popgun_pickoff(s16 playerId) {
    if (playerId == -1) {
        return NULL;
    }
    return D_8010DDD8_popgun_pickoff + playerId;
}

void *func_8010AFF4_popgun_pickoff(s16 playerId) {
    PopgunPickoffPlayer *player;
    s32 id = playerId;

    if (id == -1) {
        return NULL;
    }
    player = D_8010DDD8_popgun_pickoff + id;
    return player->unk_04;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B038_popgun_pickoff);

void func_8010B0D4_popgun_pickoff(s16 playerId, s8 value1, s8 value2, s8 value3, s16 value4) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_1D = value1;
        player->unk_1E = value2;
        player->unk_1F = value3;
        player->unk_20 = value4;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B120_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B200_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B300_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B3D0_popgun_pickoff);

void func_8010B508_popgun_pickoff(s16 playerId, s32 value) {
    PopgunPickoffPlayer *player;

    if (playerId != -1) {
        player = D_8010DDD8_popgun_pickoff + playerId;
        player->unk_14 = value;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B544_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B5B4_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B64C_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B7A0_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010BA44_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010BC6C_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010C32C_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010C4EC_popgun_pickoff);
