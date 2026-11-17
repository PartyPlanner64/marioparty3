#include "common_duel.h"
#include "ovl_81.h"

extern NameSpriteIds mbdStatusAnim;
extern s16 mbdVsSprGrp;
extern s16 mbdVsSprAnim;
extern f32 mbdVsSprScale;
extern Vec2f mbdVsSprPos;
extern Vec2f mbdVsSprVel;
extern Vec2f mbdVsSprAccel;
extern s16 mbdVsSprMoveTime;
extern NamePlayerData mbdStatusPlayerTbl[];
extern Process *mbdStatusProc;
extern omObjData *mbdCoinTakeObjTbl[];

s32 mbdStatusCoinUpdateF = 1;
s32 mbdStatusCostUpdateF = 1;
s16 mbdStatusPosTbl[][2] = {
    { 24, 36 },
    { 200, 155 },
    { -192, 36 },
    { 416, 155 },
    { 48, 96 },
    { 176, 96 },
    { 112, 110 },
    { 416, 155 },
    { -192, 16 },
    { 416, 155 },
    { 512, 24 },
    { 512, 174 },
    { 200, 24 },
    { 200, 174 }
};
s16 mbdStatusGrpPosBTbl[][2] = { { 30, 138 }, { 194, 138 } };
s16 mbdStatusGrpPosATbl[][2] = { { 30, 138 }, { 194, 138 } };
s16 mbdStatusSprOfsTbl[][2] = {
    { 0, 0 },
    { 0, 0 },
    { -30, 0 },
    { 20, 0 },
    { 30, 0 },
    { 40, 0 },
    { 0, 13 },
    { 0, -31 },
    { 0, -31 },
    { -32, -25 },
    { -32, -37 },
    { 20, -31 },
    { -20, -25 },
    { -20, -37 },
    { 30, -31 },
    { 40, -31 },
    { 40, -31 },
    { 0, -31 },
    { 0, 31 },
    { 0, 31 },
    { -32, 37 },
    { -32, 25 },
    { 20, 31 },
    { -20, 37 },
    { -20, 25 },
    { 30, 31 },
    { 40, 31 },
    { 40, 31 },
    { 0, 31 }
};
s16 mbdStatusCostPosTbl[3][2] = { { 20, 31 }, { 30, 31 }, { 40, 31 } };
s16 mbdStatusCostPosAltTbl[3][2] = { { 30, 31 }, { 40, 31 }, { 40, 31 } };
s16 (*mbdStatusSprOfsPtrTbl[])[2] = { mbdStatusSprOfsTbl, mbdStatusSprOfsTbl };
u8 mbdStatusDispMovePosIdxTbl[] = {
    0, 2, 0, 0, 4, 0, 6, 8, 10, 12, 0, 0, 0, 0,
    16, 16, 16, 16, 14, 14, 14, 14, 0, 0, 0, 2, 0, 0
};
s32 mbdStatusCharSprTbl[] = {
    0x1300D8, 0x1300D9, 0x1300DB, 0x1300DC, 0x1300DD, 0x1300DE, 0x1300DF, 0x1300E1,
    0x1300D8, 0x1300DA, 0x1300DB, 0x1300DC, 0x1300DD, 0x1300DE, 0x1300E0, 0x1300E1
};
s32 mbdStatusPartnerSprTbl[] = {
    0x1300E2, 0x1300E3, 0x1300E4, 0x1300E5, 0x1300E6, 0x1300E7,
    0x1300E8, 0x1300E9, 0x1300EA, 0x1300EB, 0x1300EC, 0x1300ED
};
s16 (*mbdStatusGrpPosTbl[])[2] = { mbdStatusGrpPosATbl, mbdStatusGrpPosATbl, mbdStatusGrpPosATbl, mbdStatusGrpPosBTbl };
// -1 terminated sprite member lists; the second list continues into the third row.
s8 mbdStatusMemberTbl[][3] = { { 13, 24, -1 }, { 14, 15, 25 }, { 26, -1 } };

void MBDStatusNumUpdate(s32 playerIndex);
void MBDStatusMain(void);
void MBDStatusBackSprCreate(s32 playerIndex);
void MBDStatusPartnerSprCreate(s32 playerIndex, s32 partnerID, s16 *anims, s32 baseMember);
void MBDStatusPosSet(s32 playerIndex, s16 x, s16 y);
void MBDCoinTakeObjMain(omObjData *obj);
void MBDStatusScaleSet(s32 playerIndex, f32 scaleX, f32 scaleY);
void MBDStatusAnimCreate(void);
void MBDStatusPlayerCreate(s32 playerIndex);
void MBDStatusPlayerKill(s32 playerIndex);
void MBDCoinTakeCreateSound(s32 playerIndex, s32 coins, s32 arg2);

void MBDStatusNumUpdate(s32 playerIndex) {
    u8 coinDigits[3];
    GW_PLAYER *gwPlayer;
    NamePlayerData *player;
    s32 numDigits;
    s32 i;

    gwPlayer = MBDPlayerGet(playerIndex);
    player = &mbdStatusPlayerTbl[playerIndex];
    if (mbdStatusCoinUpdateF != 0) {
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
                HuSprAnimModeSet(player->spriteGroup, i + 3, HUSPR_ANIM_MODE_BANK);
            }

            player->unk_02 = GwPlayer[playerIndex].coin;
        }

        if (player->unk_01 != GwPlayer[playerIndex].star) {
            if (GwPlayer[playerIndex].star >= 5) {
                HuSprBankSet(player->spriteGroup, 2, 5, 0);
            } else {
                HuSprBankSet(player->spriteGroup, 2, GwPlayer[playerIndex].star, 0);
            }
            HuSprAnimModeSet(player->spriteGroup, 2, HUSPR_ANIM_MODE_BANK);
            player->unk_01 = GwPlayer[playerIndex].star;
        }

        if (gwPlayer->stats.partners.frontID != PARTNER_NONE) {
            HuSprBankSet(player->spriteGroup, 0xC, gwPlayer->stats.partners.frontHp, 0);
            HuSprBankSet(player->spriteGroup, 0xD, gwPlayer->stats.partners.frontPower, 0);
            HuSprBankSet(player->spriteGroup, 0xE, 0xC, 0);
            if (gwPlayer->stats.partners.frontCost >= 10) {
                HuSprBankSet(player->spriteGroup, 0xF, gwPlayer->stats.partners.frontCost / 10, 0);
                HuSprBankSet(player->spriteGroup, 0x10, gwPlayer->stats.partners.frontCost % 10, 0);
                if (player->unk_6A != gwPlayer->stats.partners.frontCost && mbdStatusCostUpdateF != 0) {
                    for (i = 0; i < 3; i++) {
                        HuSprPosSet(player->spriteGroup, i + 0xE, mbdStatusCostPosTbl[i][0], -mbdStatusCostPosTbl[i][1]);
                    }
                }
            } else {
                HuSprBankSet(player->spriteGroup, 0xF, gwPlayer->stats.partners.frontCost, 0);
                HuSprDispOff(player->spriteGroup, 0x10);
                if (player->unk_6A != gwPlayer->stats.partners.frontCost && mbdStatusCostUpdateF != 0) {
                    for (i = 0; i < 3; i++) {
                        HuSprPosSet(player->spriteGroup, i + 0xE, mbdStatusCostPosAltTbl[i][0], -mbdStatusCostPosAltTbl[i][1]);
                    }
                }
            }
            player->unk_6A = gwPlayer->stats.partners.frontCost;
            for (i = 5; i < 10; i++) {
                HuSprAnimModeSet(player->spriteGroup, i + 7, HUSPR_ANIM_MODE_BANK);
            }
        }

        if (gwPlayer->stats.partners.backID != PARTNER_NONE) {
            HuSprBankSet(player->spriteGroup, 0x17, gwPlayer->stats.partners.backHp, 0);
            HuSprBankSet(player->spriteGroup, 0x18, gwPlayer->stats.partners.backPower, 0);
            HuSprBankSet(player->spriteGroup, 0x19, 0xC, 0);
            if (gwPlayer->stats.partners.backCost >= 10) {
                HuSprBankSet(player->spriteGroup, 0x1A, gwPlayer->stats.partners.backCost / 10, 0);
                HuSprBankSet(player->spriteGroup, 0x1B, gwPlayer->stats.partners.backCost % 10, 0);
                if (player->unk_6B != gwPlayer->stats.partners.backCost && mbdStatusCostUpdateF != 0) {
                    for (i = 0; i < 3; i++) {
                        HuSprPosSet(player->spriteGroup, i + 0x19, mbdStatusCostPosTbl[i][0], mbdStatusCostPosTbl[i][1]);
                    }
                }
            } else {
                HuSprBankSet(player->spriteGroup, 0x1A, gwPlayer->stats.partners.backCost, 0);
                HuSprDispOff(player->spriteGroup, 0x1B);
                if (player->unk_6B != gwPlayer->stats.partners.backCost && mbdStatusCostUpdateF != 0) {
                    for (i = 0; i < 3; i++) {
                        HuSprPosSet(player->spriteGroup, i + 0x19, mbdStatusCostPosAltTbl[i][0], mbdStatusCostPosAltTbl[i][1]);
                    }
                }
            }
            player->unk_6B = gwPlayer->stats.partners.backCost;
            for (i = 5; i < 10; i++) {
                HuSprAnimModeSet(player->spriteGroup, i + 0x12, HUSPR_ANIM_MODE_BANK);
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

void MBDStatusSprDispOffAll(void) {
    NamePlayerData *player;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        player = &mbdStatusPlayerTbl[i];

        for (j = 0; j < 0x1D; j++) {
            HuSprDispOff(player->spriteGroup, j);
        }
    }
}

void MBDStatusMain(void) {
    NamePlayerData *player;
    s32 i;
    s32 j;

    while (1) {
        if (Hu3DPauseF == 0) {
            for (i = 0; i < 2; i++) {
                player = &mbdStatusPlayerTbl[i];

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
                MBDStatusNumUpdate(i);

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

            if (mbdVsSprGrp != -1) {
                mbdVsSprScale -= 1.0f;
                if (mbdVsSprScale < 1.0f) {
                    mbdVsSprScale = 1.0f;
                }
                HuSprScaleSet(mbdVsSprGrp, 0, mbdVsSprScale, mbdVsSprScale);
                if (mbdVsSprMoveTime > 0) {
                    mbdVsSprMoveTime--;
                    mbdVsSprPos.x += mbdVsSprVel.x;
                    mbdVsSprPos.y += mbdVsSprVel.y;
                    mbdVsSprVel.x += mbdVsSprAccel.x;
                    mbdVsSprVel.y += mbdVsSprAccel.y;
                    HuSprPosSet(mbdVsSprGrp, 0, mbdVsSprPos.x, mbdVsSprPos.y);
                }
            }
        }
        HuPrcVSleep();
    }
}

void MBDStatusCharSprCreate(s32 playerIndex) {
    s16 group = mbdStatusPlayerTbl[playerIndex].spriteGroup;

    HuSprGrpMemberSet(group, 1, mbdStatusAnim.unk_02[playerIndex], 0);
    HuSprAnimModeSet(group, 1, HUSPR_ANIM_MODE_STOP);
    HuSprPriSet(group, 1, playerIndex * 5 + 0x4790);
    HuSprAttrSet(group, 1, 0);
    HuSprPosSet(group, 1, mbdStatusSprOfsPtrTbl[playerIndex][1][0], mbdStatusSprOfsPtrTbl[playerIndex][1][1]);
    if (playerIndex != 0 && GwPlayer[playerIndex].chr != CHAR_LUIGI && GwPlayer[playerIndex].chr != CHAR_WALUIGI) {
        HuSprAttrSet(group, 1, 1);
    }
}

void MBDStatusIconSprCreate(s32 playerIndex) {
    s16 group = mbdStatusPlayerTbl[playerIndex].spriteGroup;

    HuSprGrpMemberSet(group, 2, mbdStatusAnim.unk_06, 0);
    HuSprPriSet(group, 2, playerIndex * 5 + 0x4790);
    HuSprAttrSet(group, 2, 0);
    HuSprZRotSet(group, 2, 0.0f);
    HuSprPosSet(group, 2, mbdStatusSprOfsPtrTbl[playerIndex][2][0], mbdStatusSprOfsPtrTbl[playerIndex][2][1]);
    HuSprSpeedSet(group, 2, 0.0f);
    HuSprTPLvlSet(group, 2, 0x100);
}

void MBDStatusNumSprCreate(s32 playerIndex) {
    NamePlayerData *player = &mbdStatusPlayerTbl[playerIndex];
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
        HuSprAnimModeSet(group, i + 3, HUSPR_ANIM_MODE_BANK);
        HuSprBankSet(group, i + 3, 0xA, 0);
        HuSprPriSet(group, i + 3, playerIndex * 5 + 0x4790);
        HuSprAttrSet(group, i + 3, 0);
        HuSprPosSet(group, i + 3, mbdStatusSprOfsPtrTbl[playerIndex][i + 3][0], mbdStatusSprOfsPtrTbl[playerIndex][i + 3][1]);
    }
    DataClose(data);
}

void MBDStatusBackSprCreate(s32 playerIndex) {
    NamePlayerData *player = &mbdStatusPlayerTbl[playerIndex];
    s16 group;

    group = player->spriteGroup = HuSprGrpCreate(0x1D, 2);
    HuSprGrpMemberSet(group, 0, mbdStatusAnim.unk_00, 0);
    HuSprPriSet(group, 0, playerIndex * 5 + 0x4790);
    HuSprAttrSet(group, 0, 0);
    HuSprPosSet(group, 0, 0, 0);
}

void MBDStatusComSprCreate(s32 playerIndex) {
    s16 group = mbdStatusPlayerTbl[playerIndex].spriteGroup;

    HuSprGrpMemberSet(group, 6, mbdStatusAnim.unk_0A, 0);
    HuSprAnimModeSet(group, 6, HUSPR_ANIM_MODE_STOP);
    HuSprPriSet(group, 6, playerIndex * 5 + 0x478E);
    HuSprAttrSet(group, 6, 0);
    HuSprPosSet(group, 6, mbdStatusSprOfsPtrTbl[playerIndex][6][0], mbdStatusSprOfsPtrTbl[playerIndex][6][1]);
    if (!(GwPlayer[playerIndex].stat & 1)) {
        HuSprDispOff(group, 6);
    }
}

void MBDStatusFrontDispOff(s32 playerIndex) {
    NamePlayerData *player;
    s32 i;

    if (MBDPlayerGet(playerIndex)->stats.partners.frontID == PARTNER_NONE) {
        player = &mbdStatusPlayerTbl[playerIndex];

        for (i = 0; i < 11; i++) {
            HuSprDispOff(player->spriteGroup, i + 7);
        }
    }
}

void MBDStatusPartnerSprCreate(s32 playerIndex, s32 partnerID, s16 *anims, s32 baseMember) {
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
    s16 group = mbdStatusPlayerTbl[playerIndex].spriteGroup;
    void *data;
    s32 i;

    for (i = 0; i < 11; i++) {
        if (i == 1) {
            if (playerIndex != 0) {
                HuSprAttrSet(group, baseMember + 1, 1);
            } else {
                HuSprAttrReset(group, baseMember + i, 1);
            }
            data = DataRead(mbdStatusPartnerSprTbl[partnerID]);
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
        HuSprAnimModeSet(group, baseMember + i, HUSPR_ANIM_MODE_BANK);
        if (i == 0) {
            HuSprPriSet(group, baseMember, playerIndex * 5 + 0x4793);
        } else {
            HuSprPriSet(group, baseMember + i, playerIndex * 5 + 0x4792);
        }
        HuSprDispOn(group, baseMember + i);
        HuSprPosSet(group, baseMember + i, mbdStatusSprOfsPtrTbl[playerIndex][baseMember + i][0],
                    mbdStatusSprOfsPtrTbl[playerIndex][baseMember + i][1]);

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

void MBDStatusFrontUpdate(s32 playerIndex) {
    GW_PLAYER *gwPlayer = MBDPlayerGet(playerIndex);
    s16 group;
    s32 i;

    MBDStatusFrontDispOff(playerIndex);
    if (gwPlayer->stats.partners.frontID != PARTNER_NONE) {
        mbdStatusPlayerTbl[playerIndex].unk_6A = -1;
        MBDStatusPartnerSprCreate(playerIndex, gwPlayer->stats.partners.frontID, mbdStatusPlayerTbl[playerIndex].unk_3A, 7);
        group = mbdStatusPlayerTbl[playerIndex].spriteGroup;
        HuSprBankSet(group, 0xC, gwPlayer->stats.partners.frontHp, 0);
        HuSprBankSet(group, 0xD, gwPlayer->stats.partners.frontPower, 0);
        HuSprBankSet(group, 0xE, 0xC, 0);
        if (gwPlayer->stats.partners.frontCost >= 10) {
            HuSprBankSet(group, 0xF, gwPlayer->stats.partners.frontCost / 10, 0);
            HuSprBankSet(group, 0x10, gwPlayer->stats.partners.frontCost % 10, 0);
            for (i = 0; i < 3; i++) {
                HuSprPosSet(group, i + 0xE, mbdStatusCostPosTbl[i][0], -mbdStatusCostPosTbl[i][1]);
            }
        } else {
            HuSprBankSet(group, 0xF, gwPlayer->stats.partners.frontCost, 0);
            HuSprDispOff(group, 0x10);
            for (i = 0; i < 3; i++) {
                HuSprPosSet(group, i + 0xE, mbdStatusCostPosAltTbl[i][0], -mbdStatusCostPosAltTbl[i][1]);
            }
        }
    }
}

void MBDStatusBackDispOff(s32 playerIndex) {
    NamePlayerData *player;
    s32 i;

    if (MBDPlayerGet(playerIndex)->stats.partners.backID == PARTNER_NONE) {
        player = &mbdStatusPlayerTbl[playerIndex];

        for (i = 0; i < 11; i++) {
            HuSprDispOff(player->spriteGroup, i + 0x12);
        }
    }
}

void MBDStatusBackUpdate(s32 playerIndex) {
    GW_PLAYER *gwPlayer = MBDPlayerGet(playerIndex);
    s16 group;
    s32 i;

    MBDStatusBackDispOff(playerIndex);
    if (gwPlayer->stats.partners.backID != PARTNER_NONE) {
        mbdStatusPlayerTbl[playerIndex].unk_6B = -1;
        MBDStatusPartnerSprCreate(playerIndex, gwPlayer->stats.partners.backID, mbdStatusPlayerTbl[playerIndex].unk_50, 0x12);
        group = mbdStatusPlayerTbl[playerIndex].spriteGroup;
        HuSprBankSet(group, 0x17, gwPlayer->stats.partners.backHp, 0);
        HuSprBankSet(group, 0x18, gwPlayer->stats.partners.backPower, 0);
        HuSprBankSet(group, 0x19, 0xC, 0);
        if (gwPlayer->stats.partners.backCost >= 10) {
            HuSprBankSet(group, 0x1A, gwPlayer->stats.partners.backCost / 10, 0);
            HuSprBankSet(group, 0x1B, gwPlayer->stats.partners.backCost % 10, 0);
            for (i = 0; i < 3; i++) {
                HuSprPosSet(group, i + 0x19, mbdStatusCostPosTbl[i][0], mbdStatusCostPosTbl[i][1]);
            }
        } else {
            HuSprBankSet(group, 0x1A, gwPlayer->stats.partners.backCost, 0);
            HuSprDispOff(group, 0x1B);
            for (i = 0; i < 3; i++) {
                HuSprPosSet(group, i + 0x19, mbdStatusCostPosAltTbl[i][0], mbdStatusCostPosAltTbl[i][1]);
            }
        }
    }
}

void MBDStatusAnimCreate(void) {
    NameSpriteIds *ids = &mbdStatusAnim;
    void *data;
    s32 i;

    data = DataRead(0x1300D6);
    ids->unk_00 = HuSprAnimRead(data);
    DataClose(data);

    for (i = 0; i < 2; i++) {
        data = DataRead(mbdStatusCharSprTbl[i * 8 + GwPlayer[i].chr]);
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

void MBDStatusAnimKill(void) {
    NameSpriteIds *ids = &mbdStatusAnim;
    s32 i;

    HuSprAnimKill(ids->unk_00);

    for (i = 0; i < 2; i++) {
        HuSprAnimKill(ids->unk_02[i]);
    }

    HuSprAnimKill(ids->unk_06);
    HuSprAnimKill(ids->unk_0A);
}

void MBDStatusPlayerCreate(s32 playerIndex) {
    NamePlayerData *player = &mbdStatusPlayerTbl[playerIndex];
    s32 i;

    player->unk_00 = 0;
    player->unk_02 = -1;
    player->unk_01 = -1;
    MBDStatusBackSprCreate(playerIndex);
    MBDStatusPosSet(playerIndex, mbdStatusPosTbl[playerIndex][0], mbdStatusPosTbl[playerIndex][1]);
    MBDStatusCharSprCreate(playerIndex);
    MBDStatusIconSprCreate(playerIndex);
    MBDStatusNumSprCreate(playerIndex);
    MBDStatusComSprCreate(playerIndex);

    for (i = 0; i < 11; i++) {
        player->unk_3A[i] = -1;
        player->unk_50[i] = -1;
    }

    player->unk_6A = -1;
    player->unk_6B = -1;
    MBDStatusFrontUpdate(playerIndex);
    MBDStatusBackUpdate(playerIndex);
    MBDStatusNumUpdate(playerIndex);
    mbdCoinTakeObjTbl[playerIndex] = NULL;
    player->unk_2C = NULL;
}

void MBDStatusCreate(void) {
    s32 i;

    MBDStatusAnimCreate();
    for (i = 0; i < 2; i++) {
        MBDStatusPlayerCreate(i);
    }
    mbdStatusProc = omAddPrcObj(MBDStatusMain, 0, 0x2000, 0);
    omPrcSetStatBit(mbdStatusProc, OM_STAT_NOALLPAUSE);
    mbdVsSprGrp = mbdVsSprAnim = -1;
}

void MBDStatusPlayerKill(s32 playerIndex) {
    NamePlayerData *player = &mbdStatusPlayerTbl[playerIndex];
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

    if (mbdCoinTakeObjTbl[playerIndex] != NULL) {
        omDelObj(mbdCoinTakeObjTbl[playerIndex]);
        mbdCoinTakeObjTbl[playerIndex] = NULL;
    }
}

void MBDStatusKill(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        MBDStatusPlayerKill(i);
    }
    MBDStatusAnimKill();
    HuPrcKill(mbdStatusProc);
    MBDVsSprKill();
}

void MBDStatusPosSet(s32 playerIndex, s16 x, s16 y) {
    NamePlayerData *player = &mbdStatusPlayerTbl[playerIndex];

    player->xPos = player->unk_14 = x;
    player->yPos = player->unk_18 = y;
    player->unk_1C = player->unk_20 = 0.0f;
    player->unk_08 = -2;
    HuSprPosSet(player->spriteGroup, 0, x + 0x30, y + 0x18);
}

void MBDStatusPosGet(s32 playerIndex, s16 *outX, s16 *outY) {
    NamePlayerData *player = &mbdStatusPlayerTbl[playerIndex];

    *outX = player->xPos;
    *outY = player->yPos;
}

void MBDStatusDispSideSet(s32 playerIndex, s32 mode) {
    MBDStatusPosSet(playerIndex, mbdStatusPosTbl[mode * 2 + playerIndex][0],
                          mbdStatusPosTbl[mode * 2 + playerIndex][1]);
}

void MBDStatusSideSet(s32 playerIndex, s32 posIndex) {
    MBDStatusPosSet(playerIndex, mbdStatusPosTbl[posIndex][0], mbdStatusPosTbl[posIndex][1]);
}

s32 MBDStatusDispMoveSet(s32 mode) {
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
        player = &mbdStatusPlayerTbl[i];

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
                MBDStatusPosSet(i, mbdStatusPosTbl[i + 2][0], mbdStatusPosTbl[i + 2][1]);
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
                player->unk_14 = mbdStatusPosTbl[mbdStatusDispMovePosIdxTbl[mode] + i][0];
                player->unk_18 = mbdStatusPosTbl[mbdStatusDispMovePosIdxTbl[mode] + i][1];
                break;
            case 2:
                player->unk_14 = mbdStatusGrpPosTbl[group1Count][slot[i]][0];
                player->unk_18 = mbdStatusGrpPosTbl[group1Count][slot[i]][1];
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
                player->unk_14 = mbdStatusPosTbl[mbdStatusDispMovePosIdxTbl[mode] + i][0];
                player->unk_18 = player->yPos;
                break;
        }

        player->unk_1C = player->unk_24 = (2.0f * (player->unk_14 - player->xPos)) / (f32)((player->unk_08 + 1) * (player->unk_08 + 1));
        player->unk_20 = player->unk_28 = (2.0f * (player->unk_18 - player->yPos)) / (f32)((player->unk_08 + 1) * (player->unk_08 + 1));

        if (mode == 5) {
            mbdVsSprVel.x = mbdVsSprAccel.x = 0.0f;
            mbdVsSprVel.y = mbdVsSprAccel.y = 2.0f;
            mbdVsSprMoveTime = player->unk_08;
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

s32 MBDStatusMoveCheck(void) {
    s32 result = 0;
    s32 i;

    for (i = 0; i < 2; i++) {
        if (mbdStatusPlayerTbl[i].unk_08 != -2) {
            result = 1;
        }
    }

    return result;
}

void MBDVsSprCreate(void) {
    void *data;

    if (mbdVsSprGrp == -1) {
        mbdVsSprGrp = HuSprGrpCreate(1, 0);
        data = DataRead(0x130115);
        mbdVsSprPos.y = 158.0f;
        mbdVsSprAnim = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(mbdVsSprGrp, 0, mbdVsSprAnim, 0);
        HuSprPriSet(mbdVsSprGrp, 0, 0x4780);
        HuSprAttrSet(mbdVsSprGrp, 0, 0x1000);
        HuSprPosSet(mbdVsSprGrp, 0, 0xA0, mbdVsSprPos.y);
        HuSprScaleSet(mbdVsSprGrp, 0, 0.0f, 0.0f);
        mbdVsSprScale = 10.0f;
        mbdVsSprPos.x = 160.0f;
        mbdVsSprVel.x = mbdVsSprVel.y = 0.0f;
        mbdVsSprMoveTime = 0;
    }
}

void MBDVsSprCreateY(f32 x, f32 y) {
    void *data;

    if (mbdVsSprGrp == -1) {
        mbdVsSprGrp = HuSprGrpCreate(1, 5);
        data = DataRead(0x130261);
        mbdVsSprPos.y = y;
        mbdVsSprAnim = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(mbdVsSprGrp, 0, mbdVsSprAnim, 0);
        HuSprPriSet(mbdVsSprGrp, 0, 0x4780);
        HuSprAttrSet(mbdVsSprGrp, 0, 0x1000);
        HuSprPosSet(mbdVsSprGrp, 0, 0xA0, mbdVsSprPos.y);
        HuSprScaleSet(mbdVsSprGrp, 0, 0.0f, 0.0f);
        mbdVsSprScale = 0.0f;
        mbdVsSprPos.x = x;
        mbdVsSprVel.x = mbdVsSprVel.y = 0.0f;
        mbdVsSprMoveTime = 0;
    }
}

void MBDVsSprKill(void) {
    if (mbdVsSprGrp != -1) {
        HuSprGrpKill(mbdVsSprGrp);
        mbdVsSprGrp = -1;
    }

    if (mbdVsSprAnim != -1) {
        HuSprAnimKill(mbdVsSprAnim);
        mbdVsSprAnim = -1;
    }
}

void MBDCoinTakeObjMain(omObjData *obj) {
    s32 soundPlayed = 0;

    while (obj->scale.y <= 0.0f) {
        if (obj->trans.x > 0.0f) {
            MBDPlayerCoinAdd(obj->work[0], 1);
            if (((obj->work[3] != 0) & (soundPlayed == 0)) && (obj->scale.z >= 3.0f)) {
                HuAudFXPlay(0x106);
                soundPlayed = 1;
                obj->scale.z -= 3.0f;
            }
            obj->trans.x -= 1.0f;
        } else {
            MBDPlayerCoinAdd(obj->work[0], -1);
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
            mbdCoinTakeObjTbl[obj->work[0]] = NULL;
            omDelObj(obj);
            return;
        }
        obj->scale.y += obj->scale.x;
    }

    obj->scale.y -= 1.0f;
    obj->scale.z += 2.0f;
}

void MBDCoinTakeCreateSound(s32 playerIndex, s32 coins, s32 arg2) {
    if (coins != 0) {
        if (mbdCoinTakeObjTbl[playerIndex] != NULL) {
            MBDPlayerCoinAdd(playerIndex, coins);
            return;
        }

        if (GwPlayer[playerIndex].coin == 0 && coins < 0) {
            return;
        }

        mbdCoinTakeObjTbl[playerIndex] = omAddObj(-0x8000, 0, 0, -1, MBDCoinTakeObjMain);
        mbdCoinTakeObjTbl[playerIndex]->work[0] = playerIndex;
        mbdCoinTakeObjTbl[playerIndex]->trans.x = coins;
        mbdCoinTakeObjTbl[playerIndex]->scale.x = coins > 0.0f ? (30.0f / coins) : (30.0f / (0.0f - coins));
        mbdCoinTakeObjTbl[playerIndex]->scale.y = 0.0f;
        mbdCoinTakeObjTbl[playerIndex]->scale.z = 3.0f;
        mbdCoinTakeObjTbl[playerIndex]->work[3] = arg2;
    }
}

void MBDCoinTakeCreate(s32 playerIndex, s32 coins) {
    MBDCoinTakeCreateSound(playerIndex, coins, 1);
}

s32 MBDCoinTakeCheck(s32 playerIndex) {
    return mbdCoinTakeObjTbl[playerIndex] != NULL;
}

s32 MBDStatusHideCheck(void) {
    if (mbdStatusPlayerTbl[0].unk_00 & 1) {
        return FALSE;
    }
    return TRUE;
}

void MBDStatusHideAll(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        mbdStatusPlayerTbl[i].unk_00 |= 1;
    }
}

void MBDStatusShowAll(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        mbdStatusPlayerTbl[i].unk_00 &= 0xFE;
    }
}

void MBDStatusScaleSet(s32 playerIndex, f32 scaleX, f32 scaleY) {
    NamePlayerData *player = &mbdStatusPlayerTbl[playerIndex];
    s32 i;

    for (i = 0; i < 0x1D; i++) {
        HuSprScaleSet(player->spriteGroup, i, scaleX, scaleY);
    }
}

void MBDStatusShrink(s32 playerIndex) {
    f32 angle;
    s32 i;

    for (angle = 0.0f; angle <= 90.0f; angle += 15.0f) {
        for (i = 0; i < 2; i++) {
            if (playerIndex == CUR_PLAYER || playerIndex == i) {
                MBDStatusScaleSet(i, cosdf(angle), 1.0f);
            }
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 2; i++) {
        if (playerIndex == CUR_PLAYER || playerIndex == i) {
            MBDStatusScaleSet(i, 0.0f, 0.0f);
        }
    }
    HuPrcVSleep();
}

void MBDStatusGrow(s32 playerIndex) {
    f32 angle;
    s32 i;

    for (angle = 90.0f; angle >= 0.0f; angle -= 15.0f) {
        for (i = 0; i < 2; i++) {
            if (playerIndex == CUR_PLAYER || playerIndex == i) {
                MBDStatusScaleSet(i, cosdf(angle), 1.0f);
            }
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 2; i++) {
        if (playerIndex == CUR_PLAYER || playerIndex == i) {
            MBDStatusScaleSet(i, 1.0f, 1.0f);
        }
    }
    HuPrcVSleep();
}

void MBDStatusPartnerPosSet(s32 playerIndex, s16 x, s16 y, s32 isBack) {
    GW_PLAYER *gwPlayer = MBDPlayerGet(playerIndex);
    s32 base;
    s16 group;
    s32 i;

    if (!isBack) {
        base = 7;
    } else {
        base = 0x12;
    }

    group = mbdStatusPlayerTbl[playerIndex].spriteGroup;
    for (i = base; i < base + 11; i++) {
        HuSprPosSet(group, i, x + mbdStatusSprOfsPtrTbl[playerIndex][i][0], y + mbdStatusSprOfsPtrTbl[playerIndex][i][1]);
    }

    if (!isBack) {
        if (gwPlayer->stats.partners.frontCost >= 10) {
            for (i = 0; i < 3; i++) {
                HuSprPosSet(group, base + 7 + i, x + mbdStatusCostPosTbl[i][0], y - mbdStatusCostPosTbl[i][1]);
            }
        } else {
            for (i = 0; i < 3; i++) {
                HuSprPosSet(group, base + 7 + i, x + mbdStatusCostPosAltTbl[i][0], y - mbdStatusCostPosAltTbl[i][1]);
            }
        }
    } else {
        if (gwPlayer->stats.partners.backCost >= 10) {
            for (i = 0; i < 3; i++) {
                HuSprPosSet(group, base + 7 + i, x + mbdStatusCostPosTbl[i][0], y + mbdStatusCostPosTbl[i][1]);
            }
        } else {
            for (i = 0; i < 3; i++) {
                HuSprPosSet(group, base + 7 + i, x + mbdStatusCostPosAltTbl[i][0], y + mbdStatusCostPosAltTbl[i][1]);
            }
        }
    }
}

void MBDStatusCoinUpdateSet(s32 value) {
    mbdStatusCoinUpdateF = value;
}

void MBDStatusCostUpdateSet(s32 value) {
    mbdStatusCostUpdateF = value;
}

void MBDStatusBounceExec(s32 playerIndex) {
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
            MBDStatusScaleSet(i, 0.0f, 0.0f);
        }
    }
    HuPrcVSleep();

    amplitude = 1.0f;
    for (angle = 0.0f; angle < 720.0f; angle += 60.0f) {
        for (i = 0; i < 2; i++) {
            if (mask & (1 << i)) {
                MBDStatusScaleSet(i, 1.0f - cosdf(angle) * amplitude, 1.0f - cosdf(angle) * amplitude);
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
            MBDStatusScaleSet(i, 1.0f, 1.0f);
        }
    }
    HuPrcVSleep();
}

void MBDStatusMemberGrow(s32 playerIndex, s32 listIndex) {
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
                player = &mbdStatusPlayerTbl[i];
                members = mbdStatusMemberTbl[listIndex];
                for (j = 0; j < 0x1D; j++) {
                    if (j == *members) {
                        members++;
                        scale = step / 10.0f;
                        HuSprScaleSet(player->spriteGroup, j, scale, scale);
                        HuSprPosSet(player->spriteGroup, j, mbdStatusSprOfsPtrTbl[playerIndex][j][0] / scale,
                                    mbdStatusSprOfsPtrTbl[playerIndex][j][1] / scale);
                        HuSprPriSet(player->spriteGroup, j, 1);
                    }
                }
            }
        }
        HuPrcVSleep();
    }
}

void MBDStatusMemberShrink(s32 playerIndex, s32 listIndex) {
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
                player = &mbdStatusPlayerTbl[i];
                members = mbdStatusMemberTbl[listIndex];
                for (j = 0; j < 0x1D; j++) {
                    if (j == *members) {
                        members++;
                        scale = step / 10.0f;
                        HuSprScaleSet(player->spriteGroup, j, scale, scale);
                        HuSprPosSet(player->spriteGroup, j, mbdStatusSprOfsPtrTbl[playerIndex][j][0] / scale,
                                    mbdStatusSprOfsPtrTbl[playerIndex][j][1] / scale);
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
