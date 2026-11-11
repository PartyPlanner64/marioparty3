#include "common_duel.h"
#include "ovl_81.h"

typedef struct NameSpriteIds {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02[2];
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} NameSpriteIds; // sizeof 0xC

typedef struct NamePlayerData {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ s8 unk_01;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 spriteGroup;
    /* 0x06 */ char unk_06[0x2];
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ char unk_0A[0x2];
    /* 0x0C */ f32 xPos;
    /* 0x10 */ f32 yPos;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ Object *unk_2C;
    /* 0x30 */ char unk_30[0xA];
    /* 0x3A */ s16 unk_3A[11];
    /* 0x50 */ s16 unk_50[11];
    /* 0x66 */ char unk_66[0x4];
    /* 0x6A */ s8 unk_6A;
    /* 0x6B */ s8 unk_6B;
} NamePlayerData; // sizeof 0x6C

extern NameSpriteIds D_80105414_name_81;
extern s16 D_80105420_name_81;
extern s16 D_80105422_name_81;
extern NamePlayerData D_80105630_name_81[];
extern s32 D_801014E0_name_81;
extern s32 D_801014E4_name_81;
extern s16 D_801014E8_name_81[][2];
extern Process *D_80105410_name_81;
extern omObjData *D_80105444_name_81[];

void func_800F4F20_name_81(void);
void func_800F6110_name_81(void);
void func_800F628C_name_81(s32 playerIndex);
void func_800F6408_name_81(s32 playerIndex);
void func_800F6F84_name_81(void);
void func_800F7228_name_81(s32 playerIndex, s32 coins, s32 arg2);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F4710_name_81);

void func_800F4E90_name_81(void) {
    NamePlayerData *player;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        player = &D_80105630_name_81[i];

        for (j = 0; j < 0x1D; j++) {
            HuSprDispOff(player->spriteGroup, j);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F4F20_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F52B8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F53C4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F54A4_name_81);

void func_800F55FC_name_81(s32 playerIndex) {
    NamePlayerData *player = &D_80105630_name_81[playerIndex];
    s16 group;

    group = player->spriteGroup = HuSprGrpCreate(0x1D, 2);
    HuSprGrpMemberSet(group, 0, D_80105414_name_81.unk_00, 0);
    HuSprPriSet(group, 0, playerIndex * 5 + 0x4790);
    HuSprAttrSet(group, 0, 0);
    HuSprPosSet(group, 0, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F56C0_name_81);

void func_800F57B0_name_81(s32 playerIndex) {
    NamePlayerData *player;
    s32 i;

    if (MBDGetPlayerStruct(playerIndex)->stats.partners.frontID == PARTNER_NONE) {
        player = &D_80105630_name_81[playerIndex];

        for (i = 0; i < 11; i++) {
            HuSprDispOff(player->spriteGroup, i + 7);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F5834_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F5BB4_name_81);

void func_800F5E2C_name_81(s32 playerIndex) {
    NamePlayerData *player;
    s32 i;

    if (MBDGetPlayerStruct(playerIndex)->stats.partners.backID == PARTNER_NONE) {
        player = &D_80105630_name_81[playerIndex];

        for (i = 0; i < 11; i++) {
            HuSprDispOff(player->spriteGroup, i + 0x12);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F5EB0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F6110_name_81);

void func_800F6220_name_81(void) {
    NameSpriteIds *ids = &D_80105414_name_81;
    s32 i;

    HuSprAnimKill(ids->unk_00);

    for (i = 0; i < 2; i++) {
        HuSprAnimKill(ids->unk_02[i]);
    }

    HuSprAnimKill(ids->unk_06);
    HuSprAnimKill(ids->unk_0A);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F628C_name_81);

void func_800F6390_name_81(void) {
    s32 i;

    func_800F6110_name_81();
    for (i = 0; i < 2; i++) {
        func_800F628C_name_81(i);
    }
    D_80105410_name_81 = omAddPrcObj(func_800F4F20_name_81, 0, 0x2000, 0);
    omPrcSetStatBit(D_80105410_name_81, OM_STAT_NOALLPAUSE);
    D_80105420_name_81 = D_80105422_name_81 = -1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F6408_name_81);

void func_800F64FC_name_81(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_800F6408_name_81(i);
    }
    func_800F6220_name_81();
    HuPrcKill(D_80105410_name_81);
    func_800F6F84_name_81();
}

void func_800F6550_name_81(s32 playerIndex, s16 x, s16 y) {
    NamePlayerData *player = &D_80105630_name_81[playerIndex];

    player->xPos = player->unk_14 = x;
    player->yPos = player->unk_18 = y;
    player->unk_1C = player->unk_20 = 0.0f;
    player->unk_08 = -2;
    HuSprPosSet(player->spriteGroup, 0, x + 0x30, y + 0x18);
}

void func_800F6600_name_81(s32 playerIndex, s16 *outX, s16 *outY) {
    NamePlayerData *player = &D_80105630_name_81[playerIndex];

    *outX = player->xPos;
    *outY = player->yPos;
}

void func_800F664C_name_81(s32 playerIndex, s32 mode) {
    func_800F6550_name_81(playerIndex, D_801014E8_name_81[mode * 2 + playerIndex][0],
                          D_801014E8_name_81[mode * 2 + playerIndex][1]);
}

void func_800F6688_name_81(s32 playerIndex, s32 posIndex) {
    func_800F6550_name_81(playerIndex, D_801014E8_name_81[posIndex][0], D_801014E8_name_81[posIndex][1]);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F66BC_name_81);

s32 func_800F6CA0_name_81(void) {
    s32 result = 0;
    s32 i;

    for (i = 0; i < 2; i++) {
        if (D_80105630_name_81[i].unk_08 != -2) {
            result = 1;
        }
    }

    return result;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F6CEC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F6E3C_name_81);

void func_800F6F84_name_81(void) {
    if (D_80105420_name_81 != -1) {
        HuSprGrpKill(D_80105420_name_81);
        D_80105420_name_81 = -1;
    }

    if (D_80105422_name_81 != -1) {
        HuSprAnimKill(D_80105422_name_81);
        D_80105422_name_81 = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F6FE8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F7228_name_81);

void func_800F7378_name_81(s32 playerIndex, s32 coins) {
    func_800F7228_name_81(playerIndex, coins, 1);
}

s32 func_800F7394_name_81(s32 playerIndex) {
    return D_80105444_name_81[playerIndex] != NULL;
}

s32 func_800F73AC_name_81(void) {
    if (D_80105630_name_81[0].unk_00 & 1) {
        return FALSE;
    }
    return TRUE;
}

void func_800F73C0_name_81(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        D_80105630_name_81[i].unk_00 |= 1;
    }
}

void func_800F740C_name_81(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        D_80105630_name_81[i].unk_00 &= 0xFE;
    }
}

void func_800F7458_name_81(s32 playerIndex, f32 scaleX, f32 scaleY) {
    NamePlayerData *player = &D_80105630_name_81[playerIndex];
    s32 i;

    for (i = 0; i < 0x1D; i++) {
        HuSprScaleSet(player->spriteGroup, i, scaleX, scaleY);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F74E4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F75EC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F76F8_name_81);

void func_800F79D0_name_81(s32 value) {
    D_801014E0_name_81 = value;
}

void func_800F79DC_name_81(s32 value) {
    D_801014E4_name_81 = value;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F79E8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F7BB4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F7D94_name_81);
