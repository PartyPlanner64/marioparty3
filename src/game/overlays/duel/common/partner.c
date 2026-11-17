#include "common_duel.h"
#include "ovl_81.h"

void MBDWinComKeyWait(s16, s32);
void MBDWinComKeyAllWait(s16);
void *MBDPlayerVibrateObjCreate(s16, s16, s32);
void MBDPlayerVibrateObjKill(void *);
void MBDAttackHpClear(void);
void MBDPartnerStub(void);

s32 mbdNokonokoMotTbl[] = { 4, 0xA0090, 0xA009A, 0xA009B, 0xA009C };
s32 mbdNokonokoAttackMotTbl[] = { 2, 0xA0094, 0xA0096 };
s32 mbdKuriboMotTbl[] = { 4, 0xA00A7, 0xA00AB, 0xA00AC, 0xA00AD };
s32 mbdKuriboAttackMotTbl[] = { 2, 0xA00AE, 0xA00AF };
s32 mbdKinopioMotTbl[] = { 4, 0xA0002, 0xA0012, 0xA0013, 0xA0014 };
s32 mbdKinopioAttackMotTbl[] = { 2, 0xA0015, 0xA0016 };
s32 mbdBomheiMotTbl[] = { 4, 0xA00BD, 0xA00BE, 0xA00BF, 0xA00C0 };
s32 mbdBomheiAttackMotTbl[] = { 1, 0xA00BC };
s32 mbdTeresaMotTbl[] = { 4, 0xA00C7, 0xA00C8, 0xA00C9, 0xA00CA };
s32 mbdWhompMotTbl[] = { 4, 0xA00D0, 0xA00D1, 0xA00D2, 0xA00D3 };
s32 mbdWhompAttackMotTbl[] = { 1, 0xA00D4 };
s32 mbdSnifitMotTbl[] = { 4, 0xA0138, 0xA0139, 0xA013A, 0xA013B };
s32 mbdSnifitAttackMotTbl[] = { 3, 0xA013C, 0xA013D, 0xA013E };
s32 mbdDossunMotTbl[] = { 4, 0xA00E9, 0xA00EA, 0xA00EB, 0xA00EC };
s32 mbdKoopaJrMotTbl[] = { 4, 0xA0103, 0xA0104, 0xA0105, 0xA0106 };
s32 mbdKoopaJrAttackMotTbl[] = { 2, 0xA0107, 0xA0108 };
s32 mbdWanwanMotTbl[] = { 4, 0xA00DD, 0xA00DE, 0xA00DF, 0xA00E0 };
s32 mbdWanwanAttackMotTbl[] = { 1, 0xA00E1 };
s32 mbdBlizzardMotTbl[] = { 4, 0xA0141, 0xA0142, 0xA0143, 0xA0144 };
s32 mbdBlizzardAttackMotTbl[] = { 1, 0xA0145 };
s32 mbdPakkunMotTbl[] = { 2, 0xA010F, 0xA0110 };
s32 mbdPakkunAttackMotTbl[] = { 4, 0xA0113, 0xA0114, 0xA0115, 0xA0116 };
s32 mbdPakkunExtMotTbl[] = { 3, 0xA0110, 0xA0111, 0xA0112 };

s32 *mbdPartnerMdlMotTbl[] = {
    mbdNokonokoMotTbl,
    mbdKuriboMotTbl,
    mbdKinopioMotTbl,
    mbdBomheiMotTbl,
    mbdTeresaMotTbl,
    mbdWhompMotTbl,
    mbdSnifitMotTbl,
    mbdPakkunMotTbl,
    mbdWanwanMotTbl,
    mbdDossunMotTbl,
    mbdBlizzardMotTbl,
    mbdKoopaJrMotTbl,
};
s32 *mbdPartnerAttackMotFileTbl[] = {
    mbdNokonokoAttackMotTbl,
    mbdKuriboAttackMotTbl,
    mbdKinopioAttackMotTbl,
    mbdBomheiAttackMotTbl,
    NULL,
    mbdWhompAttackMotTbl,
    mbdSnifitAttackMotTbl,
    mbdPakkunAttackMotTbl,
    mbdWanwanAttackMotTbl,
    NULL,
    mbdBlizzardAttackMotTbl,
    mbdKoopaJrAttackMotTbl,
};
s32 *mbdPartnerExtMotFileTbl[] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    mbdPakkunExtMotTbl,
    NULL,
    NULL,
    NULL,
    NULL,
};

PartnerBaseAttributes PartnersBaseStats[] = {
    { 37, 2, 1, 1, NULL, NULL, NULL, NULL },
    { 12, 1, 2, 2, NULL, NULL, NULL, NULL },
    { 9, 1, 1, 1, NULL, NULL, NULL, NULL },
    { 38, 1, 1, 3, NULL, NULL, MBDAttackHpClear, NULL },
    { 10, 1, 2, 3, NULL, NULL, NULL, MBDPartnerStub },
    { 11, 4, 0, 3, NULL, NULL, NULL, NULL },
    { 36, 2, 2, 5, NULL, NULL, NULL, NULL },
    { 44, 1, 3, 5, NULL, NULL, NULL, NULL },
    { 42, 2, 1, 6, NULL, NULL, NULL, NULL },
    { 13, 2, 0, 4, NULL, NULL, NULL, NULL },
    { 43, 3, 1, 2, NULL, NULL, NULL, NULL },
    { 41, 1, 1, 3, NULL, NULL, NULL, NULL },
};

Process *mbdPartnerProc = NULL;
u8 mbdCharPartnerTbl[] = { 0, 1, 2, 4, 3, 5, 7, 6 };
s8 *mbdAttackHp = NULL;
s8 *mbdAttackTargetHp = NULL;
s8 *mbdAttackOtherHp = NULL;
s8 *mbdAttackPartnerId = NULL;
s8 *mbdAttackTargetId = NULL;
s8 *mbdAttackOtherId = NULL;
s32 mbdCoinScatterNum = 0;
s32 mbdCoinScatterDoneNum = 0;
Object *mbdCoinScatterMdl = NULL;
void (*mbdCoinScatterHook)(void) = NULL;
s16 mbdPartnerAttackMotNum = 0;
s16 mbdPartnerExtMotNum = 0;
s16 mbdPartnerExtMotUseCnt = 0;
s32 mbdPartnerDescMesTbl[] = {
    0x4F00, 0x4F01, 0x4F02, 0x4F03, 0x4F04, 0x4F05,
    0x4F06, 0x4F07, 0x4F08, 0x4F09, 0x4F0A, 0x4F0B
};
s16 mbdPartnerDescFaceTbl[] = { 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22 };
s32 mbdPartnerComboTbl[][2] = { { 4, 10 }, { 3, 8 }, { 5, 9 }, { 0, 2 }, { 6, 10 } };
s32 mbdPartnerComboMesTbl[] = { 0x1F16, 0x1F17, 0x1F18, 0x1F19, 0x1F1A };
s32 mbdPartnerNameMesTbl[] = {
    0x1F0A, 0x1F0B, 0x1F0C, 0x1F0D, 0x1F0E, 0x1F0F,
    0x1F10, 0x1F11, 0x1F12, 0x1F13, 0x1F14, 0x1F15
};

void MBDPartnerObjClear(void) {
    s32 i, j;

    // TODO: unhardcode loop conditions
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            mbdPartnerObj[i][j] = NULL;
        }
    }
}

void MBDPartnerClose(void) {
    s32 i;

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        MBDPartnerModelKillAll(i);
    }

    if (mbdPartnerProc != NULL) {
        omDelPrcObj(mbdPartnerProc);
        mbdPartnerProc = NULL;
    }
}

// partnerNo arg goes unused?
Object *MBDPartnerPakkunModelCreate(s32 partnerNo) {
    return MBDPartnerModelCreate(7);
}

Object *MBDPartnerModelCreate(s32 partnerID) {
    Object *obj = MBDModelCreate(PartnersBaseStats[partnerID].unk_00, mbdPartnerMdlMotTbl[partnerID]);

    if (partnerID == PARTNER_BOO) {
        Hu3DModelTPLvlInit(obj->omObj1->model[0]);
        Hu3DModelTPLvlSet(obj->omObj1->model[0], 0xFF);
        Hu3DModelTPLvlInit(obj->omObj2->model[0]);
        Hu3DModelTPLvlSet(obj->omObj2->model[0], 0xFF);
    }

    MBDModelTempAllocFree(obj);
    return obj;
}

void MBDPartnerModelSetup(s32 playerIndex) {
    GW_PLAYER *player = MBDPlayerGet(playerIndex);

    if (mbdPartnerObj[playerIndex][PARTNER_FRONT] != NULL) {
        MBDModelKill(mbdPartnerObj[playerIndex][PARTNER_FRONT]);
        mbdPartnerObj[playerIndex][PARTNER_FRONT] = NULL;
    }

    if (player->stats.partners.frontID != PARTNER_NONE) {
        if (player->stats.partners.frontID == PARTNER_PIRANHA_PLANT) {
            mbdPartnerObj[playerIndex][PARTNER_FRONT] = MBDPartnerPakkunModelCreate(playerIndex);
        } else {
            mbdPartnerObj[playerIndex][PARTNER_FRONT] = MBDPartnerModelCreate(player->stats.partners.frontID);
        }
    }

    if (mbdPartnerObj[playerIndex][1] != NULL) {
        MBDModelKill(mbdPartnerObj[playerIndex][1]);
        mbdPartnerObj[playerIndex][1] = NULL;
    }

    if (player->stats.partners.backID != PARTNER_NONE) {
        if (player->stats.partners.backID == PARTNER_PIRANHA_PLANT) {
            mbdPartnerObj[playerIndex][PARTNER_BACK] = MBDPartnerPakkunModelCreate(playerIndex);
        } else {
            mbdPartnerObj[playerIndex][PARTNER_BACK] = MBDPartnerModelCreate(player->stats.partners.backID);
        }
    }
}

void MBDPartnerModelReset(s32 playerIndex, s32 partnerNo) {
    GW_PLAYER *player = MBDPlayerGet(playerIndex);
    Object *partnerObj = mbdPartnerObj[playerIndex][partnerNo];
    s32 partnerID;

    if (partnerObj != NULL) {
        MBDModelKill(partnerObj);
        mbdPartnerObj[playerIndex][partnerNo] = NULL;
    }

    if (partnerNo == PARTNER_KOOPA) {
        partnerID = player->stats.partners.frontID;
    } else {
        partnerID = player->stats.partners.backID;
    }

    if (partnerID != PARTNER_NONE) {
        if (partnerID == PARTNER_PIRANHA_PLANT) {
            mbdPartnerObj[playerIndex][partnerNo] = MBDPartnerPakkunModelCreate(playerIndex);
        } else {
            mbdPartnerObj[playerIndex][partnerNo] = MBDPartnerModelCreate(partnerID);
        }
    }
}

void MBDPartnerModelKillAll(s32 playerIndex) {
    s32 i;

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if (mbdPartnerObj[playerIndex][i] != NULL) {
            MBDModelKill(mbdPartnerObj[playerIndex][i]);
            mbdPartnerObj[playerIndex][i] = NULL;
        }
    }
}

void MBDPartnerModelUpdate(s32 playerIndex) {
    GW_PLAYER *player = MBDPlayerGet(playerIndex);

    if (player->stats.partners.frontID == PARTNER_NONE) {
        if (mbdPartnerObj[playerIndex][PARTNER_FRONT] != NULL) {
            MBDModelKill(mbdPartnerObj[playerIndex][PARTNER_FRONT]);
            mbdPartnerObj[playerIndex][PARTNER_FRONT] = NULL;
            MBDPartnerClear(playerIndex, PARTNER_FRONT);
        }
    }

    if (player->stats.partners.backID == PARTNER_NONE) {
        if (mbdPartnerObj[playerIndex][PARTNER_BACK] != NULL) {
            MBDModelKill(mbdPartnerObj[playerIndex][1]);
            mbdPartnerObj[playerIndex][PARTNER_BACK] = NULL;
            MBDPartnerClear(playerIndex, PARTNER_BACK);
        }
    }
}

void MBDPartnerSet(s32 playerIndex, s32 partnerID, s32 frontOrBackIndex) {
    GW_PLAYER *player = MBDPlayerGet(playerIndex);

    switch (frontOrBackIndex) {
        case PARTNER_FRONT:
            player->stats.partners.frontID = partnerID;
            player->stats.partners.frontPoweredUp = POWERUP_NONE;
            player->stats.partners.frontHp = PartnersBaseStats[partnerID].hp;
            player->stats.partners.frontCost = PartnersBaseStats[partnerID].cost;
            player->stats.partners.frontPower = PartnersBaseStats[partnerID].power;
            break;
        case PARTNER_BACK:
            player->stats.partners.backID = partnerID;
            player->stats.partners.backPoweredUp = POWERUP_NONE;
            player->stats.partners.backHp = PartnersBaseStats[partnerID].hp;
            player->stats.partners.backCost = PartnersBaseStats[partnerID].cost;
            player->stats.partners.backPower = PartnersBaseStats[partnerID].power;
            break;
    }

    if (player->stats.partners.frontID != PARTNER_NONE) {
        player->stats.partners.frontPower = PartnersBaseStats[player->stats.partners.frontID].power;
        player->stats.partners.frontCost = PartnersBaseStats[player->stats.partners.frontID].cost;
    }

    if (player->stats.partners.backID != PARTNER_NONE) {
        player->stats.partners.backPower = PartnersBaseStats[player->stats.partners.backID].power;
        player->stats.partners.backCost = PartnersBaseStats[player->stats.partners.backID].cost;
    }

    if (playerIndex == 0) {
        GWBoardFlagClear(0x12);
    } else {
        GWBoardFlagClear(0x13);
    }
}

void MBDPartnerClear(s32 playerIndex, s32 frontOrBackIndex) {
    GW_PLAYER *player = MBDPlayerGet(playerIndex);

    switch (frontOrBackIndex) {
        case PARTNER_FRONT:
            player->stats.partners.frontID = PARTNER_NONE;
            player->stats.partners.frontPoweredUp = 0;
            player->stats.partners.frontHp = 0;
            player->stats.partners.frontCost = 0;
            player->stats.partners.frontPower = 0;
            break;
        case PARTNER_BACK:
            player->stats.partners.backID = PARTNER_NONE;
            player->stats.partners.backPoweredUp = 0;
            player->stats.partners.backHp = 0;
            player->stats.partners.backCost = 0;
            player->stats.partners.backPower = 0;
            break;
    }

    if (player->stats.partners.frontID != PARTNER_NONE) {
        player->stats.partners.frontPower = PartnersBaseStats[player->stats.partners.frontID].power * player->stats.partners.frontPoweredUp;
        player->stats.partners.frontCost = PartnersBaseStats[player->stats.partners.frontID].cost * player->stats.partners.frontPoweredUp;
    }
    if (player->stats.partners.backID != PARTNER_NONE) {
        player->stats.partners.backPower = PartnersBaseStats[player->stats.partners.backID].power * player->stats.partners.backPoweredUp;
        player->stats.partners.backCost = PartnersBaseStats[player->stats.partners.backID].cost * player->stats.partners.backPoweredUp;
    }

    // TODO: what are these flags?
    if (playerIndex == 0) {
        GWBoardFlagClear(0x12);
    } else {
        GWBoardFlagClear(0x13);
    }
}

// swaps front and back partners for playerIndex player
void MBDPartnerPosSwap(s32 playerIndex) {
    GW_PLAYER *player = MBDPlayerGet(playerIndex);
    s32 frontID = player->stats.partners.frontID;
    s32 frontHP = player->stats.partners.frontHp;
    s32 frontPoweredUp = player->stats.partners.frontPoweredUp;
    s32 frontCost = player->stats.partners.frontCost;
    s32 frontPower = player->stats.partners.frontPower;
    Object *tempPartner;

    player->stats.partners.frontID = player->stats.partners.backID;
    player->stats.partners.frontHp = player->stats.partners.backHp;
    player->stats.partners.frontPoweredUp = player->stats.partners.backPoweredUp;
    player->stats.partners.frontCost = player->stats.partners.backCost;
    player->stats.partners.frontPower = player->stats.partners.backPower;

    player->stats.partners.backID = frontID;
    player->stats.partners.backHp = frontHP;
    player->stats.partners.backPoweredUp = frontPoweredUp;
    player->stats.partners.backCost = frontCost;
    player->stats.partners.backPower = frontPower;

    tempPartner = mbdPartnerObj[playerIndex][PARTNER_FRONT];
    mbdPartnerObj[playerIndex][PARTNER_FRONT] = mbdPartnerObj[playerIndex][PARTNER_BACK];
    mbdPartnerObj[playerIndex][PARTNER_BACK] = tempPartner;

    MBDPartnerPosFix(playerIndex);
    MBDStatusFrontUpdate(playerIndex);
    MBDStatusBackUpdate(playerIndex);
}

void MBDPartnerPowerUp(s32 playerIndex) {
    GW_PLAYER *player = MBDPlayerGet(playerIndex);

    if ((player->stats.partners.frontID != PARTNER_NONE) && (player->stats.partners.frontPoweredUp == POWERUP_NONE)) {
        player->stats.partners.frontPoweredUp = 2;
        player->stats.partners.frontHp *= 2;
        player->stats.partners.frontCost *= 2;
        player->stats.partners.frontPower *= 2;
    }
    if ((player->stats.partners.backID != PARTNER_NONE) &&
        (player->stats.partners.backPoweredUp == POWERUP_NONE)) {
        player->stats.partners.backPoweredUp = 2;
        player->stats.partners.backHp *= 2;
        player->stats.partners.backCost *= 2;
        player->stats.partners.backPower *= 2;
    }
}

void MBDPartnerPowerDown(s32 playerIndex) {
    GW_PLAYER *player = MBDPlayerGet(playerIndex);

    if ((player->stats.partners.frontID != PARTNER_NONE) && (player->stats.partners.frontPoweredUp == POWERUP_ACTIVE)) {
        player->stats.partners.frontPoweredUp = POWERUP_NONE;
        player->stats.partners.frontHp = (player->stats.partners.frontHp + 1) / 2;
        player->stats.partners.frontCost = player->stats.partners.frontCost / 2;
        player->stats.partners.frontPower = player->stats.partners.frontPower / 2;
    }
    if ((player->stats.partners.backID != PARTNER_NONE) && (player->stats.partners.backPoweredUp == POWERUP_ACTIVE)) {
        player->stats.partners.backPoweredUp = POWERUP_NONE;
        player->stats.partners.backHp = (player->stats.partners.backHp + 1) / 2;
        player->stats.partners.backCost = player->stats.partners.backCost / 2;
        player->stats.partners.backPower = player->stats.partners.backPower / 2;
    }
}

Object *MBDPartnerObjGet(s32 playerIndex, s32 frontOrBackIndex) {
    return mbdPartnerObj[playerIndex][frontOrBackIndex];
}

s32 MBDPartnerCostGet(s32 playerIndex) {
    GW_PLAYER *player = MBDPlayerGet(playerIndex);
    s32 totalPartnerCost = 0;

    if (player->stats.partners.frontID != PARTNER_NONE) {
        totalPartnerCost = player->stats.partners.frontCost;
    }
    if (player->stats.partners.backID != PARTNER_NONE) {
        totalPartnerCost += player->stats.partners.backCost;
    }
    return totalPartnerCost;
}

s32 MBDPartnerMotionSet(s32 playerIndex, s32 frontOrBackIndex, s16 arg2, u16 arg3) {
    s32 partnerCount = 0;
    GW_PLAYER *player = MBDPlayerGet(playerIndex);

    if (playerIndex == CUR_PLAYER) {
        playerIndex = MBDPlayerTurnGet();
    }

    if (frontOrBackIndex == PARTNER_FRONT) {
        if ((player->stats.partners.frontID != PARTNER_NONE) && (mbdPartnerMdlMotTbl[player->stats.partners.frontID] != NULL)) {
            MBDMotionSet(mbdPartnerObj[playerIndex][PARTNER_FRONT], arg2, arg3);
            partnerCount++;
        }
    }

    if (frontOrBackIndex == PARTNER_BACK) {
        if ((player->stats.partners.backID != PARTNER_NONE) && (mbdPartnerMdlMotTbl[player->stats.partners.backID] != NULL)) {
            MBDMotionSet(mbdPartnerObj[playerIndex][PARTNER_BACK], arg2, arg3);
            partnerCount++;
        }
    }
    return partnerCount;
}

s32 MBDPartnerMotionShiftSet(s32 playerIndex, s32 arg1, s16 arg2, s16 arg3, s16 arg4, u16 flags) {
    s32 partnerCount = 0;
    GW_PLAYER *player = MBDPlayerGet(playerIndex);
    u16 flagsCopy = flags;

    if (playerIndex == CUR_PLAYER) {
        playerIndex = MBDPlayerTurnGet();
    }

    if (arg1 == 0) {
        if ((player->stats.partners.frontID != PARTNER_NONE) && (mbdPartnerMdlMotTbl[player->stats.partners.frontID] != NULL)) {
            if (player->stats.partners.frontID == PARTNER_THWOMP) {
                flagsCopy &= ~4;
            }
            MBDMotionShiftSet(mbdPartnerObj[playerIndex][PARTNER_FRONT], arg2, arg3, arg4, flagsCopy);
            partnerCount++;
        }
    }

    if (arg1 == 1) {
        if ((player->stats.partners.backID != PARTNER_NONE) && (mbdPartnerMdlMotTbl[player->stats.partners.backID] != NULL)) {
            if (player->stats.partners.backID == PARTNER_THWOMP) {
                flags &= ~4;
            }
            MBDMotionShiftSet(mbdPartnerObj[playerIndex][PARTNER_BACK], arg2, arg3, arg4, flags);
            partnerCount++;
        }
    }

    return partnerCount;
}

void MBDPartnerMotionReset(s32 arg0) {
    Object *frontPartnerObj = mbdPartnerObj[arg0][PARTNER_FRONT];
    Object *backPartnerObj;

    if (frontPartnerObj != NULL) {
        Hu3DMotionReset(frontPartnerObj->omObj1->model[0]);
    }

    backPartnerObj = mbdPartnerObj[arg0][1];
    if (backPartnerObj != NULL) {
        Hu3DMotionReset(backPartnerObj->omObj1->model[0]);
    }
}

void MBDPartnerSpeedSet(s32 playerIndex, f32 arg1) {
    GW_PLAYER *player = MBDPlayerGet(playerIndex);

    if (playerIndex == PARTNER_NONE) {
        playerIndex = MBDPlayerTurnGet();
    }

    if (player->stats.partners.frontID != PARTNER_NONE) {
        Hu3DMotionSpeedSet(mbdPartnerObj[playerIndex][PARTNER_FRONT]->omObj1->model[0], arg1);
    }

    if (player->stats.partners.backID != PARTNER_NONE) {
        Hu3DMotionSpeedSet(mbdPartnerObj[playerIndex][PARTNER_BACK]->omObj1->model[0], arg1);
    }
}

void MBDPartnerAttackPairGet(s32 arg0, s32 *arg1, s32 *arg2) {
    GW_PLAYER *curPlayer = NULL;
    GW_PLAYER *opponent = NULL;
    s32 i;

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if (i == MBDPlayerTurnGet()) {
            curPlayer = MBDPlayerGet(i);
        } else {
            opponent = MBDPlayerGet(i);
        }
    }

    switch (arg0) {
        case 0:
            *arg1 = curPlayer->stats.partners.frontID;
            *arg2 = opponent->stats.partners.backID;
            return;
        case 1:
            *arg1 = curPlayer->stats.partners.backID;
            *arg2 = opponent->stats.partners.frontID;
            return;
        case 2:
            *arg1 = curPlayer->stats.partners.backID;
            *arg2 = opponent->stats.partners.backID;
            return;
        case 3:
            *arg1 = curPlayer->stats.partners.frontID;
            *arg2 = opponent->stats.partners.frontID;
            return;
    }
}

// what does this do? (arg4 is unused)
void MBDPartnerDamageCalc(u32 partnerID, s32 arg1, s32 *damageAmount, s32 *arg3, s32 arg4) {
    *arg3 = 0;

    switch (partnerID) {
        case PARTNER_KOOPA:
        case PARTNER_GOOMBA:
        case PARTNER_TOAD:
        case PARTNER_BOO:
        case PARTNER_WHOMP:
        case PARTNER_SNIFIT:
        case PARTNER_PIRANHA_PLANT:
        case PARTNER_MR_BLIZZARD:
            break;
        case PARTNER_BOB_OMB:
            *damageAmount = -*damageAmount;
            break;
        case PARTNER_THWOMP:
            if (arg1 != -1) {
                *damageAmount = 100;
            } else {
                *damageAmount = 0;
            }
            break;
        case PARTNER_BABY_BOWSER:
            if (MBDRand(100.0f) < 40) {
                *damageAmount *= 3;
            } else {
                *damageAmount = 0;
            }
            break;
        case PARTNER_CHOMP:
            if (*damageAmount == 4) {
                *damageAmount = 0xCA;
            } else if (*damageAmount == 2) {
                *damageAmount = 0xC9;
            } else {
                *damageAmount = 0xC8;
            }
            break;
    }

    if (*damageAmount > 0) {
        if ((*damageAmount < 0xC8) || (*damageAmount >= 0xCA)) {
            if (*damageAmount != 0xCA) {
                if (arg1 != -1) {
                    // related to miss chance potentially? gets a 10% chance of something...
                    if (MBDRand(10.0f) == 0) {
                        *damageAmount = 0x12C;
                    }
                }
            }
        }
    }

    switch (arg1) {
        case 4:
            if (*damageAmount == 0xC8) {
                *arg3 = 1;
            } else if (*damageAmount == 0xC9) {
                *arg3 = 2;
            } else if (*damageAmount == 0xCA) {
                *arg3 = 4;
            } else {
                if ((*damageAmount > 0) && (*damageAmount != 0x64)) {
                    if (*damageAmount != 0x12C) {
                        *arg3 = *damageAmount;
                    }
                }
            }
            break;

        case -1:
            if ((*damageAmount > 0) && ((*damageAmount < 0xC8) || (*damageAmount >= 0xCA)) && (*damageAmount != 0xCA)) {
                *damageAmount = -*damageAmount;
            }
            break;
    }

    if ((*arg3 > 0) && ((*arg3 < 0xC8) || (*arg3 >= 0xCA)) && (*arg3 != 0xCA) && (MBDRand(10.0f) == 0)) {
        *arg3 = 0x12C;
    }
}

void MBDPartnerMesWinExec(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 sp18[128];
    u8 sp98[32];
    u16 temp_v0;
    u8 spB8[32];
    s16 spD8[2];

    if (arg1 != 0) {
        HuWinMesConv(sp98, arg1);
        HuWinInsertMesSizeGet((u32)sp98, 0);
    }
    if (arg2 != 0) {
        HuWinMesConv(spB8, arg2);
        HuWinInsertMesSizeGet((u32)spB8, 1);
    }

    HuWinMesConv(sp18, arg0);
    HuWinMesMaxSizeGet(1, spD8, (u32)sp18);
    temp_v0 = HuWinExCreate(-1, 0xA0 - spD8[0] / 2, 0x78 - spD8[1] / 2, spD8[0], spD8[1], 0);

    if (arg1 != 0) {
        HuWinInsertMesSet(temp_v0, (u32)sp98, 0);
    }
    if (arg2 != 0) {
        HuWinInsertMesSet(temp_v0, (u32)spB8, 1);
    }

    HuWinMesSet(temp_v0, (u32)sp18, -1, -1);
    HuWinExAnimIn(temp_v0);

    if (arg3 == -1) {
        MBDWinComKeyAllWait(temp_v0);
    } else {
        MBDWinComKeyWait(temp_v0, arg3);
    }
    HuWinExAnimOut(temp_v0, 0);
    HuWinKill(temp_v0);
}

void MBDPartnerAttackExec(s32 attackType) {
    GW_PLAYER *player;
    GW_PLAYER *opposingPlayer;
    Process *process;
    Object *effect;
    Object *counterEffect;
    s32 curPlayerIndex;
    s32 opposingPlayerIndex;
    s32 partnerID;
    s32 targetID;
    s32 damage;
    s32 counterDamage;
    s32 poweredUp = 0;
    s32 frontOrBackIndex;
    Object *partner;
    Object *opposingPartner;
    s32 targetIndex;
    s32 flags;
    s32 counterFlags;
    s32 musHandle;
    s32 attackerID;
    s32 volume;
    s32 i;

    curPlayerIndex = MBDPlayerTurnGet();
    opposingPlayerIndex = curPlayerIndex ^ 1;
    player = MBDPlayerGet(curPlayerIndex);
    opposingPlayer = MBDPlayerGet(opposingPlayerIndex);
    process = HuPrcCurrentGet();
    MBDBackThreadPriLowSet();
    MBDPartnerExtMotInit();
    MBDPartnerAttackPairGet(attackType, &partnerID, &targetID);

    if (partnerID == PARTNER_MR_BLIZZARD) {
        switch (attackType) {
            case 0:
                attackType = 3;
                break;
            case 3:
                attackType = 0;
                break;
            case 2:
                attackType = 1;
                break;
            case 1:
                attackType = 2;
                break;
        }
    }

    mbdAttackType = attackType;
    MBDPartnerAttackPairGet(attackType, &partnerID, &targetID);

    if (partnerID == PARTNER_NONE) {
        HuPrcChildLink(process, MBDCameraZoomMotStart(1.0f));
        HuPrcChildWatch();
        MBDDlgResultWinExec(0x1E00);
        HuPrcChildLink(process, MBDCameraZoomMotStart(1.7f));
        HuPrcChildWatch();
    } else {
        damage = 0;
        targetIndex = 0;
        frontOrBackIndex = 0;
        counterFlags = 0;
        flags = 0;

        switch (attackType) {
            case 0:
                mbdAttackHp = &player->stats.partners.frontHp;
                mbdAttackTargetHp = &opposingPlayer->stats.partners.backHp;
                mbdAttackOtherHp = &opposingPlayer->stats.partners.frontHp;
                mbdAttackPartnerId = &player->stats.partners.frontID;
                mbdAttackTargetId = &opposingPlayer->stats.partners.backID;
                mbdAttackOtherId = &opposingPlayer->stats.partners.frontID;
                poweredUp = player->stats.partners.frontPoweredUp;
                damage = player->stats.partners.frontPower;
                frontOrBackIndex = 0;
                targetIndex = 1;
                break;
            case 2:
                mbdAttackHp = &player->stats.partners.backHp;
                mbdAttackTargetHp = &opposingPlayer->stats.partners.backHp;
                mbdAttackOtherHp = &opposingPlayer->stats.partners.frontHp;
                mbdAttackPartnerId = &player->stats.partners.backID;
                mbdAttackTargetId = &opposingPlayer->stats.partners.backID;
                mbdAttackOtherId = &opposingPlayer->stats.partners.frontID;
                poweredUp = player->stats.partners.backPoweredUp;
                damage = player->stats.partners.backPower;
                frontOrBackIndex = 1;
                targetIndex = 1;
                break;
            case 1:
                mbdAttackHp = &player->stats.partners.backHp;
                mbdAttackTargetHp = &opposingPlayer->stats.partners.frontHp;
                mbdAttackOtherHp = &opposingPlayer->stats.partners.backHp;
                mbdAttackPartnerId = &player->stats.partners.backID;
                mbdAttackTargetId = &opposingPlayer->stats.partners.frontID;
                mbdAttackOtherId = &opposingPlayer->stats.partners.backID;
                poweredUp = player->stats.partners.backPoweredUp;
                damage = player->stats.partners.backPower;
                frontOrBackIndex = 1;
                targetIndex = 0;
                break;
            case 3:
                mbdAttackHp = &player->stats.partners.frontHp;
                mbdAttackTargetHp = &opposingPlayer->stats.partners.frontHp;
                mbdAttackOtherHp = &opposingPlayer->stats.partners.backHp;
                mbdAttackPartnerId = &player->stats.partners.frontID;
                mbdAttackTargetId = &opposingPlayer->stats.partners.frontID;
                mbdAttackOtherId = &opposingPlayer->stats.partners.backID;
                poweredUp = player->stats.partners.frontPoweredUp;
                damage = player->stats.partners.frontPower;
                frontOrBackIndex = 0;
                targetIndex = 0;
                break;
        }

        partner = MBDPartnerObjGet(curPlayerIndex, frontOrBackIndex);
        opposingPartner = MBDPartnerObjGet(opposingPlayerIndex, targetIndex);
        mbItemBtnF = 0;
        volume = 127;
        HuPrcChildLink(process, MBDCameraZoomMotStart(1.0f));

        while (HuPrcChildGet(process) != NULL) {
            msmMusSetVolume(HuAudMusNo, volume);
            volume -= 5;
            if (volume < 0) {
                volume = 0;
            }
            HuPrcVSleep();
        }

        msmMusPause(HuAudMusNo);
        msmMusSetVolume(HuAudMusNo, 127);
        musHandle = HuAudSubSeqPlay(0x17);
        MBDPlayerVibrate(0, 2);
        MBDPlayerVibrate(1, 2);
        HuPrcChildLink(process, MBDTelopTitleCreate());
        HuPrcChildWatch();
        HuPrcChildLink(process, MBDCameraZoomMotStart(3.0f));
        HuPrcChildWatch();
        MBDStatusShrink(-1);
        HuVecCopy3F(&mbdAttackCameraPos, &player->player_obj->coords);
        MBDCameraFocusModeSet(4);
        MBDCameraFocusVecSet(&mbdAttackCameraPos);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&mbdAttackCameraPos, &partner->coords, &mbdAttackCameraPos, 4.0f));
        HuPrcChildWatch();
        MBDCameraFocusVecSet(&partner->coords);
        MBDPartnerDamageCalc(partnerID, targetID, &damage, &counterDamage, poweredUp);
        mbdAttackHpDamage = 0;
        mbdAttackStarDamage = 0;

    damageLoop:
        if (opposingPlayer->star == 0) {
            goto end;
        }
        if (damage == 300) {
            damage = 0;
            flags |= 8;
        } else if (damage == 200) {
            opposingPlayer->star -= 1;
            if (opposingPlayer->star < 0) {
                opposingPlayer->star = 0;
            }
            *mbdAttackTargetHp -= 1;
            *mbdAttackOtherHp -= 1;
            damage = 0;
            flags |= 4;
        } else if (damage == 201) {
            opposingPlayer->star -= 2;
            if (opposingPlayer->star < 0) {
                opposingPlayer->star = 0;
            }
            *mbdAttackTargetHp -= 2;
            if (*mbdAttackTargetHp < 0) {
                *mbdAttackTargetHp = 0;
            }
            *mbdAttackOtherHp -= 2;
            if (*mbdAttackOtherHp < 0) {
                *mbdAttackOtherHp = 0;
            }
            damage = 0;
            flags |= 0x10;
        } else if (damage == 202) {
            opposingPlayer->star -= 4;
            if (opposingPlayer->star < 0) {
                opposingPlayer->star = 0;
            }
            *mbdAttackTargetHp -= 4;
            if (*mbdAttackTargetHp < 0) {
                *mbdAttackTargetHp = 0;
            }
            *mbdAttackOtherHp -= 4;
            if (*mbdAttackOtherHp < 0) {
                *mbdAttackOtherHp = 0;
            }
            damage = 0;
            flags |= 0x20;
        } else if (damage < 0) {
            opposingPlayer->star += damage;
            if (opposingPlayer->star < 0) {
                opposingPlayer->star = 0;
            }
            mbdAttackStarDamage = -damage;
            damage = 0;
            flags |= 2;
        } else if (damage > 0) {
            *mbdAttackTargetHp -= damage;
            if (*mbdAttackTargetHp < 0) {
                mbdAttackHpDamage = *mbdAttackTargetHp + damage;
                if (damage != 100) {
                    damage = *mbdAttackTargetHp;
                } else {
                    damage = 0;
                }
                *mbdAttackTargetHp = 0;
            } else {
                mbdAttackHpDamage = damage;
                damage = 0;
            }
            flags |= 1;
            goto damageLoop;
        }

        mbdAttackResult = 0;
        if (opposingPlayer->star <= 0) {
            mbdAttackResult = 1;
        }
        if (*mbdAttackTargetHp <= 0) {
            if (counterDamage == 0) {
                mbdAttackResult |= 8;
                mbdAttackResult |= 2 << targetIndex;
            } else {
                mbdAttackResult |= 0x10;
            }
        }
        if (*mbdAttackOtherHp <= 0) {
            mbdAttackResult |= 2 << (targetIndex ^ 1);
        }

        for (i = 255; i > 64; i -= 16) {
            MBDBackTPLvlSet(i);
            HuPrcVSleep();
        }
        MBDBackTPLvlSet(64);

        HuPrcChildLink(process, MBDTelopAttackCreate(curPlayerIndex, *mbdAttackPartnerId, &player->player_obj->coords, &opposingPlayer->player_obj->coords, 1));
        effect = MBDModelCreate(0x36, 0);
        HuVecCopy3F(&effect->coords, &partner->coords);
        Hu3DMotionAttrSet(effect->omObj1->model[0], 2, 0);
        HuAudFXPlay(0x1CC);
        MBDModelMotionWait(effect);
        MBDModelKill(effect);
        HuPrcChildWatch();

        if (curPlayerIndex == 0) {
            if (GWBoardFlagCheck(0x12) != 0) {
                HuAudFXPlay(0x20E);
            }
        } else if (GWBoardFlagCheck(0x13) != 0) {
            HuAudFXPlay(0x20E);
        }

        MBDCoinScatterInit();

        if (PartnersBaseStats[*mbdAttackPartnerId].func1 != NULL) {
            mbdAttackTargetIdParam = (mbdAttackTargetId == NULL) ? -1 : *mbdAttackTargetId;
            mbdAttackOtherIdParam = (mbdAttackOtherId == NULL) ? -1 : *mbdAttackOtherId;
            PartnersBaseStats[*mbdAttackPartnerId].func1(curPlayerIndex, opposingPlayerIndex, partner, opposingPartner, flags, poweredUp);
        }
        MBDCoinScatterClose();
        mbdAttackHpDamage = 0;
        mbdAttackStarDamage = 0;

    counterLoop:
        if (player->star == 0) {
            goto end;
        }
        if (counterDamage == 300) {
            counterDamage = 0;
            counterFlags |= 8;
        } else if (counterDamage < 0) {
            player->star += counterDamage;
            if (player->star < 0) {
                player->star = 0;
            }
            mbdAttackStarDamage = -counterDamage;
            counterDamage = 0;
            counterFlags |= 2;
        } else if (counterDamage > 0) {
            *mbdAttackHp -= counterDamage;
            if (*mbdAttackHp < 0) {
                mbdAttackHpDamage = *mbdAttackHp + counterDamage;
                counterDamage = *mbdAttackHp;
                *mbdAttackHp = 0;
            } else {
                mbdAttackHpDamage = counterDamage;
                counterDamage = 0;
            }
            counterFlags |= 1;
            goto counterLoop;
        }

        mbdCounterResult = 0;
        if (player->star <= 0) {
            mbdCounterResult = 1;
        }
        if (*mbdAttackHp <= 0) {
            mbdCounterResult |= 8;
            mbdCounterResult |= 2 << frontOrBackIndex;
        }

        if (counterFlags != 0) {
            HuVecCopy3F(&mbdAttackCameraPos, MBDCameraFocusVecGet());
            MBDCameraFocusVecSet(&mbdAttackCameraPos);
            MBDCameraFocusModeSet(4);
            HuPrcChildLink(process, MBDVecSpeedMoveCreate(&mbdAttackCameraPos, &opposingPartner->coords, &mbdAttackCameraPos, 4.0f));
            HuPrcChildWatch();
            MBDCameraFocusVecSet(&opposingPartner->coords);

            HuPrcChildLink(process, MBDTelopAttackCreate(opposingPlayerIndex, *mbdAttackTargetId, &opposingPlayer->player_obj->coords, &player->player_obj->coords, 0));
            counterEffect = MBDModelCreate(0x36, 0);
            HuVecCopy3F(&counterEffect->coords, &opposingPartner->coords);
            Hu3DMotionAttrSet(counterEffect->omObj1->model[0], 2, 0);
            HuAudFXPlay(0x1CC);
            MBDModelMotionWait(counterEffect);
            MBDModelKill(counterEffect);
            HuPrcChildWatch();

            switch (attackType) {
                case 0:
                    attackType = 1;
                    break;
                case 3:
                    attackType = 3;
                    break;
                case 2:
                    attackType = 2;
                    break;
                case 1:
                    attackType = 0;
                    break;
            }
            mbdAttackType = attackType;
            MBDCoinScatterInit();

            if (*mbdAttackTargetId != -1 && PartnersBaseStats[*mbdAttackTargetId].func2 != NULL) {
                attackerID = *mbdAttackPartnerId;
                if (attackerID == 0) {
                    attackerID = -1;
                }
                mbdAttackTargetIdParam = attackerID;
                mbdAttackOtherIdParam = -1;
                PartnersBaseStats[*mbdAttackTargetId].func2(opposingPlayerIndex, curPlayerIndex, opposingPartner, partner, counterFlags, poweredUp + 0x10);
            }
            MBDCoinScatterClose();
        }

        if (*mbdAttackPartnerId != -1 && PartnersBaseStats[*mbdAttackPartnerId].func3 != NULL) {
            PartnersBaseStats[*mbdAttackPartnerId].func3();
        }
        if (*mbdAttackTargetId != -1 && PartnersBaseStats[*mbdAttackTargetId].func4 != NULL) {
            PartnersBaseStats[*mbdAttackTargetId].func4();
        }

        if (*mbdAttackHp <= 0) {
            *mbdAttackPartnerId = -1;
            *mbdAttackHp = 0;
            MBDPartnerModelUpdate(curPlayerIndex);
            MBDStatusFrontDispOff(curPlayerIndex);
            MBDStatusBackDispOff(curPlayerIndex);
        }
        if (*mbdAttackTargetHp <= 0) {
            *mbdAttackTargetId = -1;
            *mbdAttackTargetHp = 0;
            MBDPartnerModelUpdate(opposingPlayerIndex);
            MBDStatusFrontDispOff(opposingPlayerIndex);
            MBDStatusBackDispOff(opposingPlayerIndex);
        }
        if (*mbdAttackOtherHp <= 0) {
            *mbdAttackOtherId = -1;
            *mbdAttackOtherHp = 0;
            MBDPartnerModelUpdate(opposingPlayerIndex);
            MBDStatusFrontDispOff(opposingPlayerIndex);
            MBDStatusBackDispOff(opposingPlayerIndex);
        }

        for (i = 64; i < 255; i += 16) {
            MBDBackTPLvlSet(i);
            HuPrcVSleep();
        }
        MBDBackTPLvlSet(255);
        MBDStatusGrow(-1);
        HuVecCopy3F(&mbdAttackCameraPos, MBDCameraFocusVecGet());
        MBDCameraFocusVecSet(&mbdAttackCameraPos);
        MBDCameraFocusModeSet(4);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&mbdAttackCameraPos, &player->player_obj->coords, &mbdAttackCameraPos, 4.0f));
        HuPrcChildWatch();
        MBDCameraFocusModeSet(1);
        mbItemBtnF = 1;

    end:
        if (musHandle != -1) {
            msmMusFadeOut(musHandle, 30);
            msmMusResume(HuAudMusNo, 90);
        }
    }

    MBDPartnerExtMotKill();
    MBDBackThreadPriHighSet();
}

void MBDCoinScatterProc(void) {
    UnkBoard5 *data = HuPrcCurrentGet()->user_data;
    s32 order = data->unk_00;
    Object *obj = data->unk_04;
    s32 count = data->unk_08;
    s32 motion = data->unk_0C;
    s32 flags = data->unk_10;
    s32 seIdx = data->unk_14;
    Object *coinObjs[12];
    Vec coinTargets[12];
    f32 coinAngles[12] = { 45.0f, -45.0f, 135.0f, 225.0f, 90.0f, 270.0f, 180.0f, 0.0f, 60.0f, -30.0f, 150.0f, 240.0f };
    Vec2f screenPos;
    Process *process;
    UnkBoard4 *sprite;
    void *file;
    void *seNo;
    s32 i;
    f32 angle;
    f32 radius;

    radius = 10.0f;
    seNo = NULL;
    process = HuPrcCurrentGet();

    while (order != mbdCoinScatterDoneNum) {
        HuPrcVSleep();
    }

    if (mbdCoinScatterHook != NULL) {
        mbdCoinScatterHook();
    }

    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&mbdPartnerCameraPos, &obj->coords, &mbdPartnerCameraPos, 4.0f));
    HuPrcChildWatch();

    if (motion != -1 && count != -1) {
        MBDMotionSet(obj, motion, 0);
    }

    if (count != -1) {
        for (i = 0; i < count; i++) {
            coinObjs[i] = MBDModelLinkCreate(mbdCoinScatterMdl);
            HuVecCopy3F(&coinObjs[i]->coords, &obj->coords);
            sincosdf(-45.0f, &Hu3DData[coinObjs[i]->omObj1->model[0]].mtx[1][2], &Hu3DData[coinObjs[i]->omObj1->model[0]].mtx[1][1]);
            Hu3DData[coinObjs[i]->omObj1->model[0]].mtx[2][1] = -Hu3DData[coinObjs[i]->omObj1->model[0]].mtx[1][2];
            Hu3DData[coinObjs[i]->omObj1->model[0]].mtx[2][2] = Hu3DData[coinObjs[i]->omObj1->model[0]].mtx[1][1];
            Hu3DData[coinObjs[i]->omObj1->model[0]].mtx[0][1] = Hu3DData[coinObjs[i]->omObj1->model[0]].mtx[0][2] =
                Hu3DData[coinObjs[i]->omObj1->model[0]].mtx[0][3] = Hu3DData[coinObjs[i]->omObj1->model[0]].mtx[1][0] =
                    Hu3DData[coinObjs[i]->omObj1->model[0]].mtx[1][3] = Hu3DData[coinObjs[i]->omObj1->model[0]].mtx[2][0] =
                        Hu3DData[coinObjs[i]->omObj1->model[0]].mtx[2][3] = Hu3DData[coinObjs[i]->omObj1->model[0]].mtx[3][0] =
                            Hu3DData[coinObjs[i]->omObj1->model[0]].mtx[3][1] = Hu3DData[coinObjs[i]->omObj1->model[0]].mtx[3][2] = 0.0f;
            Hu3DData[coinObjs[i]->omObj1->model[0]].mtx[0][0] = Hu3DData[coinObjs[i]->omObj1->model[0]].mtx[3][3] = 1.0f;
        }
    }

    if (seIdx == -1) {
        if (obj == GwPlayer[0].player_obj) {
            PlayerFXPlay(0x286, 0);
            seNo = MBDPlayerVibrateObjCreate(0, 4, 6);
        } else if (obj == GwPlayer[1].player_obj) {
            PlayerFXPlay(0x286, 1);
            seNo = MBDPlayerVibrateObjCreate(1, 4, 6);
        }
    } else {
        s32 partnerSounds[12] = { 0x25A, 0x25B, 0x29A, 0x256, 0x257, 0x25D, 0x2A3, 0x2A4, 0x2A2, 0x258, 0x2A5, 0x2A0 };

        if (seIdx >= 0 && seIdx < 12) {
            s16 handle = HuAudFXPlay(partnerSounds[seIdx]);

            if (seIdx == 2) {
                msmSeSetVolume(handle, 0x77);
            }
        }
    }

    if (count != -1) {
        for (i = 0; i < count; i++) {
            MBDModelJumpSet(coinObjs[i], 5.0f, -1.0f);
            angle = MBDVecAngleGet(&coinObjs[i]->rot);
            HuVecCopyXYZ(&coinTargets[i],
                         coinObjs[i]->coords.x + sindf(angle + coinAngles[i]) * radius,
                         coinObjs[i]->coords.y,
                         coinObjs[i]->coords.z + cosdf(angle + coinAngles[i]) * radius);
            HuPrcChildLink(process, MBDPlayerPosMoveCreate(&coinObjs[i]->coords, &coinTargets[i], &coinObjs[i]->coords, 30));
        }
        MBDModelJumpWait(coinObjs[0]);

        for (i = 0; i < count; i++) {
            MBDModelJumpSet(coinObjs[i], 2.5f, -0.5f);
        }
        MBDModelJumpWait(coinObjs[0]);

        for (i = 0; i < count; i++) {
            MBDModelJumpSet(coinObjs[i], 1.0f, -0.2f);
        }
        MBDModelJumpWait(coinObjs[0]);

        HuPrcChildWatch();

        for (i = 0; i < count; i++) {
            MBDModelKill(coinObjs[i]);
        }
    }

    if (seNo != NULL) {
        MBDPlayerVibrateObjKill(seNo);
    }

    if (count != -1) {
        s32 countSounds[4] = { 0x208, 0x209, 0x20A, 0x20B };
        s32 soundIdx;

        soundIdx = (count - 1) / 3;
        if (soundIdx < 0) {
            soundIdx = 0;
        }
        if (soundIdx >= 4) {
            soundIdx = 3;
        }
        HuAudFXPlay(countSounds[soundIdx]);

        MBDCamera3Dto2D(&obj->coords, &screenPos);
        sprite = MBDSprGrpCreate(4, 2);

        for (i = 0; i < 4; i++) {
            if (i == 0) {
                file = DataRead(0x130132);
            } else {
                file = DataRead(0x1300CF);
            }
            sprite->unk_0C[i] = HuSprAnimRead(file);
            DataClose(file);

            switch (i) {
                case 0:
                    HuSprGrpMemberSet(sprite->unk_0A, i, sprite->unk_0C[i], 0);
                    break;
                case 1:
                    HuSprGrpMemberSet(sprite->unk_0A, i, sprite->unk_0C[i], 12);
                    break;
                case 2:
                    if (count >= 10) {
                        HuSprGrpMemberSet(sprite->unk_0A, i, sprite->unk_0C[i], count / 10);
                    } else {
                        HuSprGrpMemberSet(sprite->unk_0A, i, sprite->unk_0C[i], count);
                    }
                    break;
                case 3:
                    if (count >= 10) {
                        HuSprGrpMemberSet(sprite->unk_0A, i, sprite->unk_0C[i], count - (count / 10) * 10);
                    } else {
                        HuSprGrpMemberSet(sprite->unk_0A, i, sprite->unk_0C[i], 0);
                        HuSprDispOff(sprite->unk_0A, i);
                    }
                    break;
            }

            HuSprPriSet(sprite->unk_0A, i, 0x2010 - i);
            HuSprAttrSet(sprite->unk_0A, i, 0);

            if (i == 0) {
                HuSprPosSet(sprite->unk_0A, 0, screenPos.x, screenPos.y);
            } else if (count >= 10) {
                HuSprPosSet(sprite->unk_0A, i, (i - 1) * 10 - 10, 0);
            } else {
                HuSprPosSet(sprite->unk_0A, i, (i - 1) * 10 - 5, 0);
            }
        }

        for (i = 0; i < 30; i++) {
            HuSprPosSet(sprite->unk_0A, 0, screenPos.x, screenPos.y - i);
            HuPrcVSleep();
        }
        MBDSprGrpKill(sprite);
    }

    if (flags != 0 && !(flags & 1)) {
        MBDPartnerModelMotionSet(obj, 2, 0);
        MBDModelMotionWait(obj);
        {
            Vec effectOffsets[3] = { { 0.0f, 0.5f, 0.0f }, { -0.5f, 0.5f, 0.0f }, { 0.5f, 0.5f, 0.0f } };

            for (i = 0; i < 3; i++) {
                MBDEffMdlCreate(0x4E, &obj->coords, &effectOffsets[i], 2.0f);
            }
        }
        HuPrcVSleep();
        HuAudFXPlay(0x1CB);
        MBDModelDispOff(obj);
        Hu3DMotionReset(obj->omObj1->model[0]);
        HuPrcSleep(40);
    } else {
        MBDMotionSet(obj, -1, 2);
    }

    mbdCoinScatterNum--;
    mbdCoinScatterDoneNum++;
    omDelPrcObj(NULL);
}

void MBDCoinScatterInit(void) {
    Object *temp_v0;

    mbdCoinScatterNum = 0;
    mbdCoinScatterDoneNum = 0;
    temp_v0 = MBDModelCreate(0x3C, 0);
    mbdCoinScatterMdl = temp_v0;
    MBDModelTempAllocFree(temp_v0);
    MBDModelDispOff(mbdCoinScatterMdl);
}

Process *MBDCoinScatterCreate(Object *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Process *temp_v0;
    s32 temp_a0;
    UnkBoard5 *temp_v0_2;

    temp_v0 = omAddPrcObj(MBDCoinScatterProc, 0, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(temp_v0->heap, sizeof(UnkBoard5));
    temp_v0->user_data = temp_v0_2;
    temp_a0 = mbdCoinScatterNum;
    mbdCoinScatterNum++;
    temp_v0_2->unk_00 = temp_a0;
    temp_v0_2->unk_04 = arg0;
    temp_v0_2->unk_08 = arg1;
    temp_v0_2->unk_0C = arg2;
    temp_v0_2->unk_10 = arg3;
    temp_v0_2->unk_14 = arg4;
    return temp_v0;
}

void MBDPartnerCameraFocusSet(Vec *arg0) {
    HuVecCopy3F(&mbdPartnerCameraPos, arg0);
    MBDCameraFocusVecSet(&mbdPartnerCameraPos);
}

void MBDCoinScatterClose(void) {
    while (mbdCoinScatterNum != 0) {
        HuPrcVSleep();
    }
    MBDModelKill(mbdCoinScatterMdl);
}

void MBDPartnerAttackFuncSet(PartnerFunc *arg0, PartnerFunc *arg1) {
    s32 i;

    for (i = 0; i < 12; i++) {
        PartnersBaseStats[i].func1 = arg0[i];
    }

    for (i = 0; i < 12; i++) {
        PartnersBaseStats[i].func2 = arg1[i];
    }
}

void MBDPartnerAttackMotLoad(s32 arg0) {
    s32 *var_s1;
    s32 i;

    var_s1 = mbdPartnerAttackMotFileTbl[arg0];
    if (var_s1 == NULL) {
        mbdPartnerAttackMotNum = 0;
        return;
    }

    mbdPartnerAttackMotNum = *var_s1++;

    for (i = 0; i < mbdPartnerAttackMotNum; i++) {
        mbdPartnerAttackMotTbl[i] = Hu3DMotionCreate(DataRead(*var_s1++), 8);
    }
}

void MBDPartnerAttackMotKill(void) {
    s32 i;

    for (i = 0; i < mbdPartnerAttackMotNum; i++) {
        Hu3DMotionKill(mbdPartnerAttackMotTbl[i]);
    }
}

void MBDPartnerAttackMotSet(Object *arg0, s16 arg1, s16 arg2) {
    if (arg1 <= mbdPartnerAttackMotNum) {
        Hu3DMotionSet(arg0->omObj1->model[0], mbdPartnerAttackMotTbl[arg1]);
        Hu3DMotionAttrSet(arg0->omObj1->model[0], -1, arg2);
    }
}

void MBDPartnerAttackMotShiftSet(Object *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    Hu3DMotionShiftSet(arg0->omObj1->model[0], mbdPartnerAttackMotTbl[arg1], arg2, arg3, arg4);
}

void MBDPartnerExtMotInit(void) {
    mbdPartnerExtMotNum = 0;
    mbdPartnerExtMotUseCnt = 0;
}

void MBDPartnerExtMotLoad(s32 arg0) {
    s32 *var_s1;
    s32 i;

    var_s1 = mbdPartnerExtMotFileTbl[arg0];
    if (var_s1 == NULL) {
        mbdPartnerExtMotNum = 0;
        return;
    }

    mbdPartnerExtMotNum = *var_s1++;

    for (i = 0; i < mbdPartnerExtMotNum; i++) {
        mbdPartnerExtMotTbl[i] = Hu3DMotionCreate(DataRead(*var_s1++), 8);
    }
}

void MBDPartnerExtMotKill(void) {
    s32 i;

    while (mbdPartnerExtMotUseCnt != 0) {
        HuPrcVSleep();
    }

    for (i = 0; i < mbdPartnerExtMotNum; i++) {
        Hu3DMotionKill(mbdPartnerExtMotTbl[i]);
    }
}

void MBDPartnerExtMotSet(Object *arg0, s16 arg1, u16 arg2) {
    if (arg1 < mbdPartnerExtMotNum) {
        Hu3DMotionSet(arg0->omObj1->model[0], mbdPartnerExtMotTbl[arg1]);
        Hu3DMotionAttrSet(arg0->omObj1->model[0], -1, arg2);
    }
}

void MBDPartnerModelMotionSet(Object *arg0, s32 arg1, s32 arg2) {
    if (arg0->unk8 == 0x2C) {
        if (mbdPartnerExtMotNum == 0) {
            MBDPartnerExtMotLoad(7);
        }
        MBDPartnerExtMotSet(arg0, arg1 - 1, arg2);
        return;
    }
    MBDMotionSet(arg0, arg1, arg2);
}

void MBDAttackHpClear(void) {
    *mbdAttackHp = 0;
}

void MBDPartnerStub(void) {
}

void MBDPartnerDescProc(void) {
    s16 sp18[2];
    u16 sp36;
    DuelHelpWin *sp3C;
    UnkBoard4 *temp_s4;
    u16 *temp_s1;
    DuelHelpWin *temp_fp;
    DuelHelpWin *temp_s7;
    s32 var_s3;
    u8 playerPad;
    void *temp_v0_2;
    s32 playerIndex = (s32)HuPrcCurrentGet()->user_data;
    const s32 sp20[3] = { 0x001300D3, 0x001300D2, 0x001300D4 };
    s32 i;

    playerPad = GwPlayer[playerIndex].pad;
    var_s3 = 0;
    HuWinTabSizeSet(0x78);
    HuWinMesMaxSizeBetGet(sp18, 0x4F00, 0x4F0A);
    sp36 = HuWinExCreate(mbdPartnerDescFaceTbl[0], 0xA0 - sp18[0] / 2, 0x3C, sp18[0], sp18[1], 0);
    HuWinTabWidthSet(sp36, 0x78);
    HuWinBGColSet(sp36, 1, 0xB9, 0xE7);
    HuWinMesSet(sp36, mbdPartnerDescMesTbl[0], -1, -1);
    HuWinExAnimIn(sp36);
    temp_s4 = MBDSprGrpCreate(3, 2);

    for (i = 0; i < 3; i++) {
        temp_v0_2 = DataRead(sp20[i]);
        temp_s4->unk_0C[i] = HuSprAnimRead(temp_v0_2);
        DataClose(temp_v0_2);
        HuSprGrpMemberSet(temp_s4->unk_0A, i, temp_s4->unk_0C[i], 0);
        HuSprPriSet(temp_s4->unk_0A, i, 1U);
        HuSprAttrSet(temp_s4->unk_0A, i, 0U);
        if (i == 0) {
            HuSprPosSet(temp_s4->unk_0A, 0, 0xA0, 0x7E);
        } else {
            HuSprPosSet(temp_s4->unk_0A, i, 0, i * 0xE);
        }
    }

    sp3C = MBDHelpWinCreate(0x10, 0xA0, 0);
    temp_fp = MBDHelpWinCreate(0x11, 0xAE, 0);
    temp_s7 = MBDHelpWinCreate(4, 0xBC, 0);

    while (1) {
        if (ContBtnDown[playerPad] & B_BUTTON) {
            break;
        }
        if (ContBtnRep[playerPad] & R_CBUTTONS) {
            var_s3++;
            var_s3 %= 12;
            HuWinHomeClear(sp36);
            HuWinMesSet(sp36, mbdPartnerDescMesTbl[var_s3], -1, -1);
            HuWinExAnimPopIn(sp36, mbdPartnerDescFaceTbl[var_s3]);
        }
        if (ContBtnRep[playerPad] & L_CBUTTONS) {
            var_s3--;
            if (var_s3 < 0) {
                var_s3 = 0xB;
            }
            HuWinHomeClear(sp36);
            HuWinMesSet(sp36, mbdPartnerDescMesTbl[var_s3], -1, -1);
            HuWinExAnimPopIn(sp36, mbdPartnerDescFaceTbl[var_s3]);
        }
        HuPrcVSleep();
    }

    MBDSprGrpKill(temp_s4);
    MBDHelpWinKill(sp3C);
    MBDHelpWinKill(temp_fp);
    MBDHelpWinKill(temp_s7);
    HuWinExAnimOut(sp36, 0);
    HuWinKill(sp36);
    omDelPrcObj(0);
}

void MBDPartnerDescExec(s32 playerIndex) {
    Process *curProcess;
    Process *newProcess;

    curProcess = HuPrcCurrentGet();
    newProcess = omAddPrcObj(MBDPartnerDescProc, 0x1005, 0, 0);
    newProcess->user_data = (void *)playerIndex;
    omPrcSetStatBit(newProcess, OM_STAT_NOALLPAUSE);
    HuPrcChildLink(curProcess, newProcess);
    HuPrcChildWatch();
}

void MBDPartnerDamageExec(s32 playerIndex, s32 frontOrBackIndex, s32 targetIndex, s32 starDamage, s32 hpDamage, s32 selfStarDamage, s32 selfHpDamage) {
    GW_PLAYER *player;
    GW_PLAYER *opposingPlayer;
    Object *partner;
    Object *opposingPartner;
    s32 poweredUp;
    Process *process;
    Object *effect;
    Object *counterEffect;
    s32 opposingPlayerIndex;
    s32 flags;
    s32 counterFlags;
    s32 i;
    s32 partnerID;

    opposingPlayerIndex = playerIndex ^ 1;
    player = MBDPlayerGet(playerIndex);
    opposingPlayer = MBDPlayerGet(opposingPlayerIndex);
    counterFlags = 0;
    process = HuPrcCurrentGet();
    mbdAttackStarDamage = starDamage;
    mbdAttackHpDamage = hpDamage;
    flags = (starDamage != 0) << 1;
    if (hpDamage != 0) {
        flags |= 1;
    }
    if (flags == 0 && selfStarDamage != -1 && selfHpDamage != -1) {
        flags |= 8;
    }
    if (selfStarDamage > 0) {
        counterFlags |= 2;
    }
    if (selfHpDamage > 0) {
        counterFlags |= 1;
    }
    MBDPartnerExtMotInit();

    if (frontOrBackIndex == 0) {
        mbdAttackHp = &player->stats.partners.frontHp;
        mbdAttackPartnerId = &player->stats.partners.frontID;
        poweredUp = player->stats.partners.frontPoweredUp;
    } else {
        mbdAttackHp = &player->stats.partners.backHp;
        mbdAttackPartnerId = &player->stats.partners.backID;
        poweredUp = player->stats.partners.backPoweredUp;
    }

    if (targetIndex == 0) {
        mbdAttackTargetHp = &opposingPlayer->stats.partners.frontHp;
        mbdAttackTargetId = &opposingPlayer->stats.partners.frontID;
        mbdAttackOtherHp = &opposingPlayer->stats.partners.backHp;
        mbdAttackOtherId = &opposingPlayer->stats.partners.backID;
    } else if (targetIndex == 1) {
        mbdAttackTargetHp = &opposingPlayer->stats.partners.backHp;
        mbdAttackTargetId = &opposingPlayer->stats.partners.backID;
        mbdAttackOtherHp = &opposingPlayer->stats.partners.frontHp;
        mbdAttackOtherId = &opposingPlayer->stats.partners.frontID;
    } else {
        mbdAttackTargetHp = NULL;
        mbdAttackTargetId = NULL;
        mbdAttackOtherHp = NULL;
        mbdAttackOtherId = NULL;
    }

    partner = MBDPartnerObjGet(playerIndex, frontOrBackIndex);
    opposingPartner = MBDPartnerObjGet(opposingPlayerIndex, targetIndex);
    HuPrcChildLink(process, MBDCameraZoomMotStart(3.0f));
    HuPrcChildWatch();
    MBDStatusShrink(-1);
    HuVecCopy3F(&mbdAttackCameraPos, &player->player_obj->coords);
    MBDCameraFocusModeSet(4);
    MBDCameraFocusVecSet(&mbdAttackCameraPos);
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&mbdAttackCameraPos, &partner->coords, &mbdAttackCameraPos, 4.0f));
    HuPrcChildWatch();
    MBDCameraFocusVecSet(&partner->coords);

    if (hpDamage == 200) {
        *mbdAttackTargetHp -= 1;
        *mbdAttackOtherHp -= 1;
        opposingPlayer->star -= 1;
    } else {
        if (mbdAttackTargetHp != NULL) {
            *mbdAttackTargetHp -= hpDamage;
        }
        opposingPlayer->star -= starDamage;
    }
    if (selfHpDamage > 0) {
        // Adjusts the pointer rather than the HP value; likely an original bug.
        mbdAttackHp -= selfHpDamage;
    }
    if (selfStarDamage > 0) {
        player->star -= selfStarDamage;
    }

    for (i = 255; i > 64; i -= 16) {
        MBDBackTPLvlSet(i);
        HuPrcVSleep();
    }
    MBDBackTPLvlSet(64);

    HuPrcChildLink(process, MBDTelopAttackCreate(playerIndex, *mbdAttackPartnerId, &player->player_obj->coords, &opposingPlayer->player_obj->coords, 1));
    effect = MBDModelCreate(0x36, 0);
    HuVecCopy3F(&effect->coords, &partner->coords);
    Hu3DMotionAttrSet(effect->omObj1->model[0], 2, 0);
    HuAudFXPlay(0x1CC);
    MBDModelMotionWait(effect);
    MBDModelKill(effect);
    HuPrcChildWatch();
    MBDCoinScatterInit();

    if (PartnersBaseStats[*mbdAttackPartnerId].func1 != NULL) {
        mbdAttackTargetIdParam = (mbdAttackTargetId == NULL) ? -1 : *mbdAttackTargetId;
        mbdAttackOtherIdParam = (mbdAttackOtherId == NULL) ? -1 : *mbdAttackOtherId;
        PartnersBaseStats[*mbdAttackPartnerId].func1(playerIndex, opposingPlayerIndex, partner, opposingPartner, flags, poweredUp);
    }
    MBDCoinScatterClose();

    if (counterFlags != 0) {
        HuVecCopy3F(&mbdAttackCameraPos, MBDCameraFocusVecGet());
        MBDCameraFocusVecSet(&mbdAttackCameraPos);
        MBDCameraFocusModeSet(4);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&mbdAttackCameraPos, &opposingPartner->coords, &mbdAttackCameraPos, 4.0f));
        HuPrcChildWatch();
        MBDCameraFocusVecSet(&opposingPartner->coords);

        HuPrcChildLink(process, MBDTelopAttackCreate(opposingPlayerIndex, *mbdAttackTargetId, &opposingPlayer->player_obj->coords, &player->player_obj->coords, 0));
        counterEffect = MBDModelCreate(0x36, 0);
        HuVecCopy3F(&counterEffect->coords, &opposingPartner->coords);
        Hu3DMotionAttrSet(counterEffect->omObj1->model[0], 2, 0);
        HuAudFXPlay(0x1CC);
        MBDModelMotionWait(counterEffect);
        MBDModelKill(counterEffect);
        HuPrcChildWatch();
        MBDCoinScatterInit();

        if (*mbdAttackTargetId != -1 && PartnersBaseStats[*mbdAttackTargetId].func2 != NULL) {
            partnerID = *mbdAttackPartnerId;
            if (partnerID == 0) {
                partnerID = -1;
            }
            mbdAttackTargetIdParam = partnerID;
            mbdAttackOtherIdParam = -1;
            PartnersBaseStats[*mbdAttackTargetId].func2(opposingPlayerIndex, playerIndex, opposingPartner, partner, counterFlags, poweredUp + 0x10);
        }
        MBDCoinScatterClose();
    }

    if (*mbdAttackPartnerId != -1 && PartnersBaseStats[*mbdAttackPartnerId].func3 != NULL) {
        PartnersBaseStats[*mbdAttackPartnerId].func3();
    }
    if (mbdAttackTargetId != NULL && *mbdAttackTargetId != -1 && PartnersBaseStats[*mbdAttackTargetId].func4 != NULL) {
        PartnersBaseStats[*mbdAttackTargetId].func4();
    }

    if (*mbdAttackHp <= 0) {
        *mbdAttackPartnerId = -1;
        *mbdAttackHp = 0;
        MBDPartnerModelUpdate(playerIndex);
        MBDStatusFrontDispOff(playerIndex);
        MBDStatusBackDispOff(playerIndex);
    }
    if (mbdAttackTargetHp != NULL && *mbdAttackTargetHp <= 0) {
        *mbdAttackTargetId = -1;
        *mbdAttackTargetHp = 0;
        MBDPartnerModelUpdate(opposingPlayerIndex);
        MBDStatusFrontDispOff(opposingPlayerIndex);
        MBDStatusBackDispOff(opposingPlayerIndex);
    }
    if (mbdAttackOtherHp != NULL && *mbdAttackOtherHp <= 0) {
        *mbdAttackOtherId = -1;
        *mbdAttackOtherHp = 0;
        MBDPartnerModelUpdate(opposingPlayerIndex);
        MBDStatusFrontDispOff(opposingPlayerIndex);
        MBDStatusBackDispOff(opposingPlayerIndex);
    }

    for (i = 64; i < 255; i += 16) {
        MBDBackTPLvlSet(i);
        HuPrcVSleep();
    }
    MBDBackTPLvlSet(255);
    MBDStatusGrow(-1);
    HuVecCopy3F(&mbdAttackCameraPos, MBDCameraFocusVecGet());
    MBDCameraFocusVecSet(&mbdAttackCameraPos);
    MBDCameraFocusModeSet(4);
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&mbdAttackCameraPos, &player->player_obj->coords, &mbdAttackCameraPos, 4.0f));
    HuPrcChildWatch();
    MBDCameraFocusModeSet(1);
    MBDPartnerExtMotKill();
}

void MBDPartnerComboMesExec(void) {
    s32 sp20[1][2];
    GW_PLAYER *player;
    s32 i;
    // TODO: these vars seem rather fake
    s32 *new_var2;
    s32(*new_var3)[2];

    player = MBDPlayerGet(CUR_PLAYER);
    if ((player->stats.partners.frontID != PARTNER_NONE) && (player->stats.partners.backID != PARTNER_NONE)) {
        if (player->stats.partners.frontID < player->stats.partners.backID) {
            sp20[0][PARTNER_FRONT] = player->stats.partners.frontID;
            sp20[0][PARTNER_BACK] = player->stats.partners.backID;
        } else {
            sp20[0][PARTNER_FRONT] = player->stats.partners.backID;
            sp20[0][PARTNER_BACK] = player->stats.partners.frontID;
        }

        for (i = 0, new_var3 = mbdPartnerComboTbl; i < 5; i++) {
            if (sp20[0][PARTNER_FRONT] == new_var3[i][PARTNER_FRONT]) {
                new_var2 = &mbdPartnerComboTbl[i][PARTNER_BACK];
                if (sp20[0][PARTNER_BACK] == new_var2[PARTNER_FRONT]) {
                    MBDDlgWinInsertCreate(0x16, mbdPartnerComboMesTbl[i], mbdPartnerNameMesTbl[player->stats.partners.frontID], mbdPartnerNameMesTbl[player->stats.partners.backID], 0, 0, 0);
                    MBDDlgWinMesWait();
                    MBDDlgWinMesWait();
                    MBDDlgWinClose();
                    MBDDlgWinKill();
                    return;
                }
            }
        }
    }
}
