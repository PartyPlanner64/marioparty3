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
    /* 0x2C */ omObjData *unk_2C;
    /* 0x30 */ char unk_30[0x4];
    /* 0x34 */ s16 unk_34;
    /* 0x36 */ char unk_36[0x4];
    /* 0x3A */ s16 unk_3A[11];
    /* 0x50 */ s16 unk_50[11];
    /* 0x66 */ char unk_66[0x4];
    /* 0x6A */ s8 unk_6A;
    /* 0x6B */ s8 unk_6B;
} NamePlayerData; // sizeof 0x6C

extern NameSpriteIds D_80105414_name_81;
extern s16 D_80105420_name_81;
extern s16 D_80105422_name_81;
extern f32 D_80105424_name_81;
extern Vec2f D_80105428_name_81;
extern Vec2f D_80105430_name_81;
extern Vec2f D_80105438_name_81;
extern s16 D_80105440_name_81;
extern NamePlayerData D_80105630_name_81[];
extern s32 D_801014E0_name_81;
extern s32 D_801014E4_name_81;
extern s16 D_801014E8_name_81[][2];
extern Process *D_80105410_name_81;
extern omObjData *D_80105444_name_81[];
extern s16 D_801015A4_name_81[3][2];
extern s16 D_801015B0_name_81[3][2];
extern s16 (*D_801015BC_name_81[])[2];
extern u8 D_801015C4_name_81[];
extern s32 D_80101620_name_81[];
extern s16 (*D_80101650_name_81[])[2];
extern s8 D_80101660_name_81[][3];
extern s32 D_801015E0_name_81[];

void func_800F4710_name_81(s32 playerIndex);
void func_800F4F20_name_81(void);
void func_800F55FC_name_81(s32 playerIndex);
void func_800F5834_name_81(s32 playerIndex, s32 partnerID, s16 *anims, s32 baseMember);
void func_800F6550_name_81(s32 playerIndex, s16 x, s16 y);
void func_800F6FE8_name_81(omObjData *obj);
void func_800F7458_name_81(s32 playerIndex, f32 scaleX, f32 scaleY);
void func_800F6110_name_81(void);
void func_800F628C_name_81(s32 playerIndex);
void func_800F6408_name_81(s32 playerIndex);
void func_800F6F84_name_81(void);
void func_800F7228_name_81(s32 playerIndex, s32 coins, s32 arg2);

void func_800F4710_name_81(s32 playerIndex) {
    u8 coinDigits[3];
    GW_PLAYER *gwPlayer;
    NamePlayerData *player;
    s32 numDigits;
    s32 i;

    gwPlayer = MBDGetPlayerStruct(playerIndex);
    player = &D_80105630_name_81[playerIndex];
    if (D_801014E0_name_81 != 0) {
        if (player->unk_02 != GwPlayer[playerIndex].coin) {
            coinDigits[0] = GwPlayer[playerIndex].coin / 100;
            coinDigits[1] = (s16)(GwPlayer[playerIndex].coin / 10) % 10;
            coinDigits[2] = GwPlayer[playerIndex].coin % 10;
            if (coinDigits[0] != 0) {
                numDigits = ((coinDigits[0] != 0) ? 3 : 2);
            } else if (coinDigits[1] != 0) {
                numDigits = ((coinDigits[0] != 0) ? 3 : 2);
            } else {
                numDigits = 1;
            }

            if (numDigits == 1) {
                HuSprDispOff(player->spriteGroup, 5);
                coinDigits[1] = coinDigits[2];
            } else {
                HuSprDispOn(player->spriteGroup, 5);
            }

            if (coinDigits[0] == 0) {
                coinDigits[0] = 10;
            }
            for (i = 0; i < ARRAY_COUNT(coinDigits); i++) {
                HuSprBankSet(player->spriteGroup, i + 3, coinDigits[i], 0);
                func_800550F4_main(player->spriteGroup, i + 3, 1);
            }

            player->unk_02 = GwPlayer[playerIndex].coin;
        }

        if (player->unk_01 != GwPlayer[playerIndex].star) {
            if (GwPlayer[playerIndex].star >= 5) {
                HuSprBankSet(player->spriteGroup, 2, 5, 0);
            } else {
                HuSprBankSet(player->spriteGroup, 2, GwPlayer[playerIndex].star, 0);
            }
            func_800550F4_main(player->spriteGroup, 2, 1);
            player->unk_01 = GwPlayer[playerIndex].star;
        }

        if (gwPlayer->stats.partners.frontID != PARTNER_NONE) {
            HuSprBankSet(player->spriteGroup, 0xC, gwPlayer->stats.partners.frontHp, 0);
            HuSprBankSet(player->spriteGroup, 0xD, gwPlayer->stats.partners.frontPower, 0);
            HuSprBankSet(player->spriteGroup, 0xE, 0xC, 0);
            if (gwPlayer->stats.partners.frontCost >= 10) {
                HuSprBankSet(player->spriteGroup, 0xF, gwPlayer->stats.partners.frontCost / 10, 0);
                HuSprBankSet(player->spriteGroup, 0x10, gwPlayer->stats.partners.frontCost % 10, 0);
                if (player->unk_6A != gwPlayer->stats.partners.frontCost && D_801014E4_name_81 != 0) {
                    for (i = 0; i < 3; i++) {
                        HuSprPosSet(player->spriteGroup, i + 0xE, D_801015A4_name_81[i][0], -D_801015A4_name_81[i][1]);
                    }
                }
            } else {
                HuSprBankSet(player->spriteGroup, 0xF, gwPlayer->stats.partners.frontCost, 0);
                HuSprDispOff(player->spriteGroup, 0x10);
                if (player->unk_6A != gwPlayer->stats.partners.frontCost && D_801014E4_name_81 != 0) {
                    for (i = 0; i < 3; i++) {
                        HuSprPosSet(player->spriteGroup, i + 0xE, D_801015B0_name_81[i][0], -D_801015B0_name_81[i][1]);
                    }
                }
            }
            player->unk_6A = gwPlayer->stats.partners.frontCost;
            for (i = 5; i < 10; i++) {
                func_800550F4_main(player->spriteGroup, i + 7, 1);
            }
        }

        if (gwPlayer->stats.partners.backID != PARTNER_NONE) {
            HuSprBankSet(player->spriteGroup, 0x17, gwPlayer->stats.partners.backHp, 0);
            HuSprBankSet(player->spriteGroup, 0x18, gwPlayer->stats.partners.backPower, 0);
            HuSprBankSet(player->spriteGroup, 0x19, 0xC, 0);
            if (gwPlayer->stats.partners.backCost >= 10) {
                HuSprBankSet(player->spriteGroup, 0x1A, gwPlayer->stats.partners.backCost / 10, 0);
                HuSprBankSet(player->spriteGroup, 0x1B, gwPlayer->stats.partners.backCost % 10, 0);
                if (player->unk_6B != gwPlayer->stats.partners.backCost && D_801014E4_name_81 != 0) {
                    for (i = 0; i < 3; i++) {
                        HuSprPosSet(player->spriteGroup, i + 0x19, D_801015A4_name_81[i][0], D_801015A4_name_81[i][1]);
                    }
                }
            } else {
                HuSprBankSet(player->spriteGroup, 0x1A, gwPlayer->stats.partners.backCost, 0);
                HuSprDispOff(player->spriteGroup, 0x1B);
                if (player->unk_6B != gwPlayer->stats.partners.backCost && D_801014E4_name_81 != 0) {
                    for (i = 0; i < 3; i++) {
                        HuSprPosSet(player->spriteGroup, i + 0x19, D_801015B0_name_81[i][0], D_801015B0_name_81[i][1]);
                    }
                }
            }
            player->unk_6B = gwPlayer->stats.partners.backCost;
            for (i = 5; i < 10; i++) {
                func_800550F4_main(player->spriteGroup, i + 0x12, 1);
            }
        }
    }

    if (gwPlayer->stats.partners.frontPoweredUp == 2) {
        HuSprDispOn(player->spriteGroup, 0x11);
    } else {
        HuSprDispOff(player->spriteGroup, 0x11);
    }

    if (gwPlayer->stats.partners.backPoweredUp == 2) {
        HuSprDispOn(player->spriteGroup, 0x1C);
    } else {
        HuSprDispOff(player->spriteGroup, 0x1C);
    }
}

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

void func_800F4F20_name_81(void) {
    NamePlayerData *player;
    s32 i;
    s32 j;

    while (1) {
        if (Hu3DPauseF == 0) {
            for (i = 0; i < 2; i++) {
                player = &D_80105630_name_81[i];

                if (player->unk_00 & 1) {
                    for (j = 0; j < 0x1D; j++) {
                        HuSprDispOff(player->spriteGroup, j);
                    }
                    continue;
                }

                for (j = 0; j < 0x1D; j++) {
                    if (j >= 7 && j <= 17) {
                        if (GwPlayer[i].stats.partners.frontID != PARTNER_NONE) {
                            goto show;
                        }
                        continue;
                    } else if (j >= 18 && j <= 28) {
                        if (GwPlayer[i].stats.partners.backID != PARTNER_NONE) {
                            goto show;
                        }
                        continue;
                    } else {
                        switch (j) {
                            case 6:
                                if (GwPlayer[i].stat & 1) {
                                    break;
                                }
                                continue;
                            case 5:
                                if (GwPlayer[i].coin < 10) {
                                    continue;
                                }
                                break;
                        }
                    }
                show:
                    HuSprDispOn(player->spriteGroup, j);
                }
                func_800F4710_name_81(i);

                if (player->unk_08 > 0) {
                    player->unk_08--;
                    player->xPos += player->unk_1C;
                    player->yPos += player->unk_20;
                    player->unk_1C += player->unk_24;
                    player->unk_20 += player->unk_28;
                } else if (player->unk_08 == -1) {
                    player->unk_08 = -2;
                } else if (player->unk_08 != -2) {
                    player->xPos = player->unk_14;
                    player->yPos = player->unk_18;
                    player->unk_08 = -1;
                }
                HuSprPosSet(player->spriteGroup, 0, (s16)((s32)(player->xPos + 0.5f) + 0x30),
                            (s16)((s32)(player->yPos + 0.5f) + 0x18));
            }

            if (D_80105420_name_81 != -1) {
                D_80105424_name_81 -= 1.0f;
                if (D_80105424_name_81 < 1.0f) {
                    D_80105424_name_81 = 1.0f;
                }
                HuSprScaleSet(D_80105420_name_81, 0, D_80105424_name_81, D_80105424_name_81);
                if (D_80105440_name_81 > 0) {
                    D_80105440_name_81--;
                    D_80105428_name_81.x += D_80105430_name_81.x;
                    D_80105428_name_81.y += D_80105430_name_81.y;
                    D_80105430_name_81.x += D_80105438_name_81.x;
                    D_80105430_name_81.y += D_80105438_name_81.y;
                    HuSprPosSet(D_80105420_name_81, 0, D_80105428_name_81.x, D_80105428_name_81.y);
                }
            }
        }
        HuPrcVSleep();
    }
}

void func_800F52B8_name_81(s32 playerIndex) {
    s16 group = D_80105630_name_81[playerIndex].spriteGroup;

    HuSprGrpMemberSet(group, 1, D_80105414_name_81.unk_02[playerIndex], 0);
    func_800550F4_main(group, 1, 0);
    HuSprPriSet(group, 1, playerIndex * 5 + 0x4790);
    HuSprAttrSet(group, 1, 0);
    HuSprPosSet(group, 1, D_801015BC_name_81[playerIndex][1][0], D_801015BC_name_81[playerIndex][1][1]);
    if (playerIndex != 0 && GwPlayer[playerIndex].chr != 1 && GwPlayer[playerIndex].chr != 6) {
        HuSprAttrSet(group, 1, 1);
    }
}

void func_800F53C4_name_81(s32 playerIndex) {
    s16 group = D_80105630_name_81[playerIndex].spriteGroup;

    HuSprGrpMemberSet(group, 2, D_80105414_name_81.unk_06, 0);
    HuSprPriSet(group, 2, playerIndex * 5 + 0x4790);
    HuSprAttrSet(group, 2, 0);
    HuSprZRotSet(group, 2, 0.0f);
    HuSprPosSet(group, 2, D_801015BC_name_81[playerIndex][2][0], D_801015BC_name_81[playerIndex][2][1]);
    HuSprSpeedSet(group, 2, 0.0f);
    HuSprTPLvlSet(group, 2, 0x100);
}

void func_800F54A4_name_81(s32 playerIndex) {
    NamePlayerData *player = &D_80105630_name_81[playerIndex];
    s16 group;
    void *data;
    s32 i;

    player->unk_02 = -1;
    player->unk_01 = -1;
    data = DataRead(0x1300CF);
    player->unk_34 = HuSprAnimRead(data);
    group = player->spriteGroup;
    for (i = 0; i < 3; i++) {
        HuSprGrpMemberSet(group, i + 3, player->unk_34, 0);
        func_800550F4_main(group, i + 3, 1);
        HuSprBankSet(group, i + 3, 0xA, 0);
        HuSprPriSet(group, i + 3, playerIndex * 5 + 0x4790);
        HuSprAttrSet(group, i + 3, 0);
        HuSprPosSet(group, i + 3, D_801015BC_name_81[playerIndex][i + 3][0], D_801015BC_name_81[playerIndex][i + 3][1]);
    }
    DataClose(data);
}

void func_800F55FC_name_81(s32 playerIndex) {
    NamePlayerData *player = &D_80105630_name_81[playerIndex];
    s16 group;

    group = player->spriteGroup = HuSprGrpCreate(0x1D, 2);
    HuSprGrpMemberSet(group, 0, D_80105414_name_81.unk_00, 0);
    HuSprPriSet(group, 0, playerIndex * 5 + 0x4790);
    HuSprAttrSet(group, 0, 0);
    HuSprPosSet(group, 0, 0, 0);
}

void func_800F56C0_name_81(s32 playerIndex) {
    s16 group = D_80105630_name_81[playerIndex].spriteGroup;

    HuSprGrpMemberSet(group, 6, D_80105414_name_81.unk_0A, 0);
    func_800550F4_main(group, 6, 0);
    HuSprPriSet(group, 6, playerIndex * 5 + 0x478E);
    HuSprAttrSet(group, 6, 0);
    HuSprPosSet(group, 6, D_801015BC_name_81[playerIndex][6][0], D_801015BC_name_81[playerIndex][6][1]);
    if (!(GwPlayer[playerIndex].stat & 1)) {
        HuSprDispOff(group, 6);
    }
}

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

void func_800F5834_name_81(s32 playerIndex, s32 partnerID, s16 *anims, s32 baseMember) {
    s32 files[11] = {
        0x1300D5,
        0,
        0x1300D2,
        0x1300D3,
        0x1300D4,
        0x1300CF,
        0x1300CF,
        0x1300D0,
        0x1300D0,
        0x1300D0,
        0x1300F6,
    };
    s16 group = D_80105630_name_81[playerIndex].spriteGroup;
    void *data;
    s32 i;

    for (i = 0; i < 11; i++) {
        if (i == 1) {
            if (playerIndex != 0) {
                HuSprAttrSet(group, baseMember + 1, 1);
            } else {
                HuSprAttrReset(group, baseMember + i, 1);
            }
            data = DataRead(D_80101620_name_81[partnerID]);
            if (anims[i] != -1) {
                HuSprAnimKill(anims[i]);
            }
            anims[i] = HuSprAnimRead(data);
            DataClose(data);
        } else if (anims[i] == -1) {
            data = DataRead(files[i]);
            anims[i] = HuSprAnimRead(data);
            DataClose(data);
        }

        HuSprGrpMemberSet(group, baseMember + i, anims[i], 0);
        func_800550F4_main(group, baseMember + i, 1);
        if (i == 0) {
            HuSprPriSet(group, baseMember, playerIndex * 5 + 0x4793);
        } else {
            HuSprPriSet(group, baseMember + i, playerIndex * 5 + 0x4792);
        }
        HuSprDispOn(group, baseMember + i);
        HuSprPosSet(group, baseMember + i, D_801015BC_name_81[playerIndex][baseMember + i][0],
                    D_801015BC_name_81[playerIndex][baseMember + i][1]);

        if (i == 0) {
            HuSprAttrSet(group, baseMember, 0x1000);
            HuSprTPLvlSet(group, baseMember, 0xA4);
        } else if (i == 10) {
            HuSprAttrSet(group, baseMember + 10, 0x1000);
        } else {
            HuSprAttrSet(group, baseMember + i, 0);
        }

        if (i == 10) {
            HuSprDispOff(group, baseMember + 10);
            HuSprColorSet(group, baseMember + 10, 0, 0xFF, 0);
            HuSprTPLvlSet(group, baseMember + 10, 0xC0);
        }
    }
}

void func_800F5BB4_name_81(s32 playerIndex) {
    GW_PLAYER *gwPlayer = MBDGetPlayerStruct(playerIndex);
    s16 group;
    s32 i;

    func_800F57B0_name_81(playerIndex);
    if (gwPlayer->stats.partners.frontID != PARTNER_NONE) {
        D_80105630_name_81[playerIndex].unk_6A = -1;
        func_800F5834_name_81(playerIndex, gwPlayer->stats.partners.frontID, D_80105630_name_81[playerIndex].unk_3A, 7);
        group = D_80105630_name_81[playerIndex].spriteGroup;
        HuSprBankSet(group, 0xC, gwPlayer->stats.partners.frontHp, 0);
        HuSprBankSet(group, 0xD, gwPlayer->stats.partners.frontPower, 0);
        HuSprBankSet(group, 0xE, 0xC, 0);
        if (gwPlayer->stats.partners.frontCost >= 10) {
            HuSprBankSet(group, 0xF, gwPlayer->stats.partners.frontCost / 10, 0);
            HuSprBankSet(group, 0x10, gwPlayer->stats.partners.frontCost % 10, 0);
            for (i = 0; i < 3; i++) {
                HuSprPosSet(group, i + 0xE, D_801015A4_name_81[i][0], -D_801015A4_name_81[i][1]);
            }
        } else {
            HuSprBankSet(group, 0xF, gwPlayer->stats.partners.frontCost, 0);
            HuSprDispOff(group, 0x10);
            for (i = 0; i < 3; i++) {
                HuSprPosSet(group, i + 0xE, D_801015B0_name_81[i][0], -D_801015B0_name_81[i][1]);
            }
        }
    }
}

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

void func_800F5EB0_name_81(s32 playerIndex) {
    GW_PLAYER *gwPlayer = MBDGetPlayerStruct(playerIndex);
    s16 group;
    s32 i;

    func_800F5E2C_name_81(playerIndex);
    if (gwPlayer->stats.partners.backID != PARTNER_NONE) {
        D_80105630_name_81[playerIndex].unk_6B = -1;
        func_800F5834_name_81(playerIndex, gwPlayer->stats.partners.backID, D_80105630_name_81[playerIndex].unk_50, 0x12);
        group = D_80105630_name_81[playerIndex].spriteGroup;
        HuSprBankSet(group, 0x17, gwPlayer->stats.partners.backHp, 0);
        HuSprBankSet(group, 0x18, gwPlayer->stats.partners.backPower, 0);
        HuSprBankSet(group, 0x19, 0xC, 0);
        if (gwPlayer->stats.partners.backCost >= 10) {
            HuSprBankSet(group, 0x1A, gwPlayer->stats.partners.backCost / 10, 0);
            HuSprBankSet(group, 0x1B, gwPlayer->stats.partners.backCost % 10, 0);
            for (i = 0; i < 3; i++) {
                HuSprPosSet(group, i + 0x19, D_801015A4_name_81[i][0], D_801015A4_name_81[i][1]);
            }
        } else {
            HuSprBankSet(group, 0x1A, gwPlayer->stats.partners.backCost, 0);
            HuSprDispOff(group, 0x1B);
            for (i = 0; i < 3; i++) {
                HuSprPosSet(group, i + 0x19, D_801015B0_name_81[i][0], D_801015B0_name_81[i][1]);
            }
        }
    }
}

void func_800F6110_name_81(void) {
    NameSpriteIds *ids = &D_80105414_name_81;
    void *data;
    s32 i;

    data = DataRead(0x1300D6);
    ids->unk_00 = HuSprAnimRead(data);
    DataClose(data);

    for (i = 0; i < 2; i++) {
        data = DataRead(D_801015E0_name_81[i * 8 + GwPlayer[i].chr]);
        ids->unk_02[i] = HuSprAnimRead(data);
        DataClose(data);
    }

    data = DataRead(0x1300D7);
    ids->unk_06 = HuSprAnimRead(data);
    DataClose(data);

    data = DataRead(0x1300D1);
    ids->unk_0A = HuSprAnimRead(data);
    DataClose(data);
}

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

void func_800F628C_name_81(s32 playerIndex) {
    NamePlayerData *player = &D_80105630_name_81[playerIndex];
    s32 i;

    player->unk_00 = 0;
    player->unk_02 = -1;
    player->unk_01 = -1;
    func_800F55FC_name_81(playerIndex);
    func_800F6550_name_81(playerIndex, D_801014E8_name_81[playerIndex][0], D_801014E8_name_81[playerIndex][1]);
    func_800F52B8_name_81(playerIndex);
    func_800F53C4_name_81(playerIndex);
    func_800F54A4_name_81(playerIndex);
    func_800F56C0_name_81(playerIndex);

    for (i = 0; i < 11; i++) {
        player->unk_3A[i] = -1;
        player->unk_50[i] = -1;
    }

    player->unk_6A = -1;
    player->unk_6B = -1;
    func_800F5BB4_name_81(playerIndex);
    func_800F5EB0_name_81(playerIndex);
    func_800F4710_name_81(playerIndex);
    D_80105444_name_81[playerIndex] = NULL;
    player->unk_2C = NULL;
}

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

void func_800F6408_name_81(s32 playerIndex) {
    NamePlayerData *player = &D_80105630_name_81[playerIndex];
    s32 i;

    HuSprAnimKill(player->unk_34);
    HuSprGrpKill(player->spriteGroup);

    for (i = 0; i < 11; i++) {
        if (player->unk_3A[i] != -1) {
            HuSprAnimKill(player->unk_3A[i]);
        }
        if (player->unk_50[i] != -1) {
            HuSprAnimKill(player->unk_50[i]);
        }
    }

    if (player->unk_2C != NULL) {
        omDelObj(player->unk_2C);
        player->unk_2C = NULL;
    }

    if (D_80105444_name_81[playerIndex] != NULL) {
        omDelObj(D_80105444_name_81[playerIndex]);
        D_80105444_name_81[playerIndex] = NULL;
    }
}

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

s32 func_800F66BC_name_81(s32 mode) {
    u8 slot[8];
    u8 group1[8];
    u8 group2[8];
    NamePlayerData *player;
    s32 i;
    u8 group1Count;
    u8 group2Count;
    u8 otherCount;

    group1Count = 0;
    group2Count = 0;

    if (mode == 2) {
        for (i = 0; i < 3; i++) {
            group1[i] = i;
        }
        group1Count = 3;
        group2Count = 0;
        otherCount = 0;
        for (i = 0; i < group1Count; i++) {
            slot[group1[i]] = otherCount++;
        }
    }

    for (i = 0; i < 2; i++) {
        player = &D_80105630_name_81[i];

        /* Modes 8-9, 10-11 and 12-13 target one specific player only. */
        if ((mode >= 8) && (mode <= 9) && (i != mode - 8)) {
            continue;
        }
        if ((mode >= 10) && (mode <= 11) && (i != mode - 10)) {
            continue;
        }
        if ((mode >= 12) && (mode <= 13) && (i != mode - 12)) {
            continue;
        }

        switch (mode) {
            case 0:
            case 8:
            case 9:
                func_800F6550_name_81(i, D_801014E8_name_81[i + 2][0], D_801014E8_name_81[i + 2][1]);
                break;
        }

        player->unk_08 = 19;
        switch (mode) {
            case 14:
            case 15:
                player->unk_08 = 5;
                goto setTarget;
            case 6:
            case 7:
                player->unk_08 = 15;
                goto setTarget;
            case 0:
            case 1:
            case 3:
            case 4:
            case 8:
            case 9:
            setTarget:
                player->unk_14 = D_801014E8_name_81[D_801015C4_name_81[mode] + i][0];
                player->unk_18 = D_801014E8_name_81[D_801015C4_name_81[mode] + i][1];
                break;
            case 2:
                player->unk_14 = D_80101650_name_81[group1Count][slot[i]][0];
                player->unk_18 = D_80101650_name_81[group1Count][slot[i]][1];
                player->unk_08 = 9;
                break;
            case 5:
                /* Slide off whichever side of the screen it is already on. */
                if (player->xPos >= 160.0f) {
                    player->unk_14 = player->xPos + 1920.0f;
                } else {
                    player->unk_14 = player->xPos - 1920.0f;
                }
                player->unk_18 = player->yPos;
                player->unk_08 = 19;
                break;
            case 10:
            case 11:
            case 12:
            case 13:
                player->unk_14 = D_801014E8_name_81[D_801015C4_name_81[mode] + i][0];
                player->unk_18 = player->yPos;
                break;
        }

        player->unk_1C = player->unk_24 = (2.0f * (player->unk_14 - player->xPos)) / (f32)((player->unk_08 + 1) * (player->unk_08 + 1));
        player->unk_20 = player->unk_28 = (2.0f * (player->unk_18 - player->yPos)) / (f32)((player->unk_08 + 1) * (player->unk_08 + 1));

        if (mode == 5) {
            D_80105430_name_81.x = D_80105438_name_81.x = 0.0f;
            D_80105430_name_81.y = D_80105438_name_81.y = 2.0f;
            D_80105440_name_81 = player->unk_08;
        }
    }

    if ((mode == 2) && (group1Count != 5)) {
        if ((group1Count == 4) || (group1Count == 0)) {
            /* Free-for-all: everyone in their own group. */
            for (i = 0; i < 2; i++) {
                GwPlayer[i].group = i;
            }
        } else if (group1Count == 3) {
            for (i = 0; i < group1Count; i++) {
                GwPlayer[group1[i]].group = 1;
            }
            for (i = 0; i < group2Count; i++) {
                GwPlayer[group2[i]].group = 0;
            }
        } else {
            for (i = 0; i < group1Count; i++) {
                GwPlayer[group1[i]].group = 0;
            }
            for (i = 0; i < group2Count; i++) {
                GwPlayer[group2[i]].group = 1;
            }
        }
    }

    if ((mode == 6) || (mode == 7)) {
        for (i = 0; i < 2; i++) {
            if (i == mode - 6) {
                GwPlayer[i].group = 0;
            } else {
                GwPlayer[i].group = 1;
            }
        }
    }

    return 0;
}

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

void func_800F6CEC_name_81(void) {
    void *data;

    if (D_80105420_name_81 == -1) {
        D_80105420_name_81 = HuSprGrpCreate(1, 0);
        data = DataRead(0x130115);
        D_80105428_name_81.y = 158.0f;
        D_80105422_name_81 = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_80105420_name_81, 0, D_80105422_name_81, 0);
        HuSprPriSet(D_80105420_name_81, 0, 0x4780);
        HuSprAttrSet(D_80105420_name_81, 0, 0x1000);
        HuSprPosSet(D_80105420_name_81, 0, 0xA0, D_80105428_name_81.y);
        HuSprScaleSet(D_80105420_name_81, 0, 0.0f, 0.0f);
        D_80105424_name_81 = 10.0f;
        D_80105428_name_81.x = 160.0f;
        D_80105430_name_81.x = D_80105430_name_81.y = 0.0f;
        D_80105440_name_81 = 0;
    }
}

void func_800F6E3C_name_81(f32 x, f32 y) {
    void *data;

    if (D_80105420_name_81 == -1) {
        D_80105420_name_81 = HuSprGrpCreate(1, 5);
        data = DataRead(0x130261);
        D_80105428_name_81.y = y;
        D_80105422_name_81 = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_80105420_name_81, 0, D_80105422_name_81, 0);
        HuSprPriSet(D_80105420_name_81, 0, 0x4780);
        HuSprAttrSet(D_80105420_name_81, 0, 0x1000);
        HuSprPosSet(D_80105420_name_81, 0, 0xA0, D_80105428_name_81.y);
        HuSprScaleSet(D_80105420_name_81, 0, 0.0f, 0.0f);
        D_80105424_name_81 = 0.0f;
        D_80105428_name_81.x = x;
        D_80105430_name_81.x = D_80105430_name_81.y = 0.0f;
        D_80105440_name_81 = 0;
    }
}

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

void func_800F6FE8_name_81(omObjData *obj) {
    s32 soundPlayed = 0;

    while (obj->scale.y <= 0.0f) {
        if (obj->trans.x > 0.0f) {
            func_800F37E0_name_81(obj->work[0], 1);
            if (((obj->work[3] != 0) & (soundPlayed == 0)) && (obj->scale.z >= 3.0f)) {
                HuAudFXPlay(0x106);
                soundPlayed = 1;
                obj->scale.z -= 3.0f;
            }
            obj->trans.x -= 1.0f;
        } else {
            func_800F37E0_name_81(obj->work[0], -1);
            obj->trans.x += 1.0f;
            if (obj->work[3] != 0) {
                if ((soundPlayed == 0) && (obj->scale.z >= 3.0f)) {
                    HuAudFXPlay(0x109);
                    soundPlayed = 1;
                    obj->scale.z -= 3.0f;
                }
                if ((obj->trans.x == 0.0f) || (GwPlayer[obj->work[0]].coin == 0)) {
                    HuAudFXPlay(0x10A);
                }
            }
        }

        if ((obj->trans.x == 0.0f) || (GwPlayer[obj->work[0]].coin == 0)) {
            D_80105444_name_81[obj->work[0]] = NULL;
            omDelObj(obj);
            return;
        }
        obj->scale.y += obj->scale.x;
    }

    obj->scale.y -= 1.0f;
    obj->scale.z += 2.0f;
}

void func_800F7228_name_81(s32 playerIndex, s32 coins, s32 arg2) {
    if (coins != 0) {
        if (D_80105444_name_81[playerIndex] != NULL) {
            func_800F37E0_name_81(playerIndex, coins);
            return;
        }

        if (GwPlayer[playerIndex].coin == 0 && coins < 0) {
            return;
        }

        D_80105444_name_81[playerIndex] = omAddObj(-0x8000, 0, 0, -1, func_800F6FE8_name_81);
        D_80105444_name_81[playerIndex]->work[0] = playerIndex;
        D_80105444_name_81[playerIndex]->trans.x = coins;
        D_80105444_name_81[playerIndex]->scale.x = coins > 0.0f ? (30.0f / coins) : (30.0f / (0.0f - coins));
        D_80105444_name_81[playerIndex]->scale.y = 0.0f;
        D_80105444_name_81[playerIndex]->scale.z = 3.0f;
        D_80105444_name_81[playerIndex]->work[3] = arg2;
    }
}

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

void func_800F74E4_name_81(s32 playerIndex) {
    f32 angle;
    s32 i;

    for (angle = 0.0f; angle <= 90.0f; angle += 15.0f) {
        for (i = 0; i < 2; i++) {
            if (playerIndex == CUR_PLAYER || playerIndex == i) {
                func_800F7458_name_81(i, cosdf(angle), 1.0f);
            }
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 2; i++) {
        if (playerIndex == CUR_PLAYER || playerIndex == i) {
            func_800F7458_name_81(i, 0.0f, 0.0f);
        }
    }
    HuPrcVSleep();
}

void func_800F75EC_name_81(s32 playerIndex) {
    f32 angle;
    s32 i;

    for (angle = 90.0f; angle >= 0.0f; angle -= 15.0f) {
        for (i = 0; i < 2; i++) {
            if (playerIndex == CUR_PLAYER || playerIndex == i) {
                func_800F7458_name_81(i, cosdf(angle), 1.0f);
            }
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 2; i++) {
        if (playerIndex == CUR_PLAYER || playerIndex == i) {
            func_800F7458_name_81(i, 1.0f, 1.0f);
        }
    }
    HuPrcVSleep();
}

void func_800F76F8_name_81(s32 playerIndex, s16 x, s16 y, s32 isBack) {
    GW_PLAYER *gwPlayer = MBDGetPlayerStruct(playerIndex);
    s32 base;
    s16 group;
    s32 i;

    if (!isBack) {
        base = 7;
    } else {
        base = 0x12;
    }

    group = D_80105630_name_81[playerIndex].spriteGroup;
    for (i = base; i < base + 11; i++) {
        HuSprPosSet(group, i, x + D_801015BC_name_81[playerIndex][i][0], y + D_801015BC_name_81[playerIndex][i][1]);
    }

    if (!isBack) {
        if (gwPlayer->stats.partners.frontCost >= 10) {
            for (i = 0; i < 3; i++) {
                HuSprPosSet(group, base + 7 + i, x + D_801015A4_name_81[i][0], y - D_801015A4_name_81[i][1]);
            }
        } else {
            for (i = 0; i < 3; i++) {
                HuSprPosSet(group, base + 7 + i, x + D_801015B0_name_81[i][0], y - D_801015B0_name_81[i][1]);
            }
        }
    } else {
        if (gwPlayer->stats.partners.backCost >= 10) {
            for (i = 0; i < 3; i++) {
                HuSprPosSet(group, base + 7 + i, x + D_801015A4_name_81[i][0], y + D_801015A4_name_81[i][1]);
            }
        } else {
            for (i = 0; i < 3; i++) {
                HuSprPosSet(group, base + 7 + i, x + D_801015B0_name_81[i][0], y + D_801015B0_name_81[i][1]);
            }
        }
    }
}

void func_800F79D0_name_81(s32 value) {
    D_801014E0_name_81 = value;
}

void func_800F79DC_name_81(s32 value) {
    D_801014E4_name_81 = value;
}

void func_800F79E8_name_81(s32 playerIndex) {
    s32 mask;
    f32 amplitude;
    f32 angle;
    s32 i;

    if (playerIndex == CUR_PLAYER) {
        mask = 3;
    } else {
        mask = 1 << playerIndex;
    }

    for (i = 0; i < 2; i++) {
        if (mask & (1 << i)) {
            func_800F7458_name_81(i, 0.0f, 0.0f);
        }
    }
    HuPrcVSleep();

    amplitude = 1.0f;
    for (angle = 0.0f; angle < 720.0f; angle += 60.0f) {
        for (i = 0; i < 2; i++) {
            if (mask & (1 << i)) {
                func_800F7458_name_81(i, 1.0f - cosdf(angle) * amplitude, 1.0f - cosdf(angle) * amplitude);
            }
        }
        amplitude -= 1.0f / 12.0f;
        if (amplitude < 0.0f) {
            amplitude = 0.0f;
        }
        HuPrcVSleep();
    }

    for (i = 0; i < 2; i++) {
        if (mask & (1 << i)) {
            func_800F7458_name_81(i, 1.0f, 1.0f);
        }
    }
    HuPrcVSleep();
}

void func_800F7BB4_name_81(s32 playerIndex, s32 listIndex) {
    NamePlayerData *player;
    s8 *members;
    s32 mask;
    s32 step;
    f32 scale;
    s32 i;
    s32 j;

    if (playerIndex == CUR_PLAYER) {
        mask = 3;
    } else {
        mask = 1 << playerIndex;
    }

    for (step = 10; step <= 30; step += 10) {
        for (i = 0; i < 2; i++) {
            if (mask & (1 << i)) {
                player = &D_80105630_name_81[i];
                members = D_80101660_name_81[listIndex];
                for (j = 0; j < 0x1D; j++) {
                    if (j == *members) {
                        members++;
                        scale = step / 10.0f;
                        HuSprScaleSet(player->spriteGroup, j, scale, scale);
                        HuSprPosSet(player->spriteGroup, j, D_801015BC_name_81[playerIndex][j][0] / scale,
                                    D_801015BC_name_81[playerIndex][j][1] / scale);
                        HuSprPriSet(player->spriteGroup, j, 1);
                    }
                }
            }
        }
        HuPrcVSleep();
    }
}

void func_800F7D94_name_81(s32 playerIndex, s32 listIndex) {
    NamePlayerData *player;
    s8 *members;
    s32 mask;
    s32 step;
    f32 scale;
    s32 i;
    s32 j;

    if (playerIndex == CUR_PLAYER) {
        mask = 3;
    } else {
        mask = 1 << playerIndex;
    }

    for (step = 30; step >= 10; step -= 2) {
        for (i = 0; i < 2; i++) {
            if (mask & (1 << i)) {
                player = &D_80105630_name_81[i];
                members = D_80101660_name_81[listIndex];
                for (j = 0; j < 0x1D; j++) {
                    if (j == *members) {
                        members++;
                        scale = step / 10.0f;
                        HuSprScaleSet(player->spriteGroup, j, scale, scale);
                        HuSprPosSet(player->spriteGroup, j, D_801015BC_name_81[playerIndex][j][0] / scale,
                                    D_801015BC_name_81[playerIndex][j][1] / scale);
                        if (step == 10) {
                            HuSprPriSet(player->spriteGroup, j, i * 5 + 0x4792);
                        }
                    }
                }
            }
        }
        HuPrcVSleep();
    }
}
