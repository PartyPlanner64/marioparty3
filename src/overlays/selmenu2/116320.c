#include "common.h"

typedef struct UnkSelmenu2Space {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u32 unk_04;
    f32 unk_08;
    char *unk_0C;
} UnkSelmenu2Space; // sizeof 0x10

typedef struct UnkSelmenu2SpaceGroups {
    u8 group[4];
    u8 unk_04[4];
    s16 unk_08[4];
} UnkSelmenu2SpaceGroups; // sizeof 0x10

extern s32 fontcolor;

extern s16 D_80109B00_selmenu2;
extern s16 D_80109B02_selmenu2;
extern UnkSelmenu2Space D_80108BE0_selmenu2[];
extern UnkSelmenu2SpaceGroups D_801090D0_selmenu2[];
extern GW_PLAYER D_80109B20_selmenu2[];

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_801059A0_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80105F74_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_8010600C_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_801067B4_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80106A54_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80106D94_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_801078CC_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80107D94_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80107DA4_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80108718_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80108764_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_801087E0_selmenu2);

void func_80108910_selmenu2(u16 arg0, u16 arg1, char *arg2, u16 arg3, u16 arg4) {
    fontcolor = arg4;
    print8((arg0 + 1), (arg1 + 1), arg2);
    fontcolor = arg3;
    print8(arg0, arg1, arg2);
}

void func_80108990_selmenu2(void) {
    s16 x = D_80109B00_selmenu2;
    s16 y = D_80109B02_selmenu2;
    UnkSelmenu2SpaceGroups *groups = &D_801090D0_selmenu2[D_80108BE0_selmenu2[x * 10 + y].unk_01];
    GW_PLAYER *player = D_80109B20_selmenu2;

    player->group = groups->group[0];
    player++;
    player->group = groups->group[1];
    player++;
    player->group = groups->group[2];
    player++;
    player->group = groups->group[3];
}

void func_80108A04_selmenu2(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        GW_PLAYER *src = &D_80109B20_selmenu2[i];
        GW_PLAYER *dst = &GwPlayer[i];

        dst->stat = src->stat;
        dst->group = src->group;
        dst->pad = src->pad;
        dst->cpu_difficulty = src->cpu_difficulty;
        dst->coin = src->coin;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80108A6C_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80108B38_selmenu2);
