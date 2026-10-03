#include "common.h"
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F4710_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F4E90_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F4F20_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F52B8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F53C4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F54A4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F55FC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F56C0_name_81);

void func_800F57B0_name_81(s32 playerIndex) {
    NamePlayerData *player;
    s32 i;

    if (MBDGetPlayerStruct(playerIndex)->stats.partners.frontID == PARTNER_NONE) {
        player = &D_80105630_name_81[playerIndex];

        for (i = 0; i < 11; i++) {
            HuSprAttrSet(player->spriteGroup, i + 7, 0x8000);
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
            HuSprAttrSet(player->spriteGroup, i + 0x12, 0x8000);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F5EB0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F6110_name_81);

void func_800F6220_name_81(void) {
    NameSpriteIds *ids = &D_80105414_name_81;
    s32 i;

    HuSprKill(ids->unk_00);

    for (i = 0; i < 2; i++) {
        HuSprKill(ids->unk_02[i]);
    }

    HuSprKill(ids->unk_06);
    HuSprKill(ids->unk_0A);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F628C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F6390_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F6408_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F64FC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F6550_name_81);

void func_800F6600_name_81(s32 playerIndex, s16 *outX, s16 *outY) {
    NamePlayerData *player = &D_80105630_name_81[playerIndex];

    *outX = player->xPos;
    *outY = player->yPos;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F664C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F6688_name_81);

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
        HuSprKill(D_80105422_name_81);
        D_80105422_name_81 = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F6FE8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F7228_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F7378_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F7394_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F73AC_name_81);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F7458_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F74E4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F75EC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F76F8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F79D0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F79DC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F79E8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F7BB4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F7D94_name_81);
