#include "common.h"

typedef struct SelMenuConfig {
    u8 available;
    u8 player_groups;
    u8 unk_02;
    u8 unk_03;
    u32 unk_04;
    s16 unk_08;
    s16 unk_0A;
    char *name;
} SelMenuConfig; // sizeof 0x10

typedef struct SelMenuPlayerGroups {
    u8 group[4];
    u8 unk_04[0xC];
} SelMenuPlayerGroups; // sizeof 0x10

extern s32 fontcolor;

extern s16 D_8010A070_selmenu;
extern s16 D_8010A072_selmenu;
extern SelMenuConfig D_80108C90_selmenu[];
extern SelMenuPlayerGroups D_801092C0_selmenu[];
extern GW_PLAYER D_8010A098_selmenu[];

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_801059A0_selmenu);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80105F30_selmenu);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80105FC8_selmenu);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80106770_selmenu);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80106A10_selmenu);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80106DEC_selmenu);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80107924_selmenu);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80107DEC_selmenu);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80107DFC_selmenu);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_801087C8_selmenu);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80108814_selmenu);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80108890_selmenu);

void func_801089C0_selmenu(u16 arg0, u16 arg1, char *arg2, u16 arg3, u16 arg4) {
    fontcolor = arg4;
    print8((arg0 + 1), (arg1 + 1), arg2);
    fontcolor = arg3;
    print8(arg0, arg1, arg2);
}

void func_80108A40_selmenu(void) {
    SelMenuPlayerGroups *groups = &D_801092C0_selmenu[D_80108C90_selmenu[D_8010A070_selmenu * 10 + D_8010A072_selmenu].player_groups];
    GW_PLAYER *player = D_8010A098_selmenu;

    player->group = groups->group[0];
    player++;
    player->group = groups->group[1];
    player++;
    player->group = groups->group[2];
    player++;
    player->group = groups->group[3];
}

void func_80108AB4_selmenu(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        GW_PLAYER *src = &D_8010A098_selmenu[i];
        GW_PLAYER *dst = &GwPlayer[i];

        dst->stat = src->stat;
        dst->group = src->group;
        dst->pad = src->pad;
        dst->cpu_difficulty = src->cpu_difficulty;
        dst->coin = src->coin;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80108B1C_selmenu);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80108BE8_selmenu);
