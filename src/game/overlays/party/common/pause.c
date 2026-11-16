#include "common_board.h"
#include "item.h"
#include "player.h"
#include "status.h"
#include "mgcall.h"
#include "model.h"
#include "pause.h"
#include "sprgrp.h"
#include "helpwin.h"
#include "move.h"
#include "back.h"
#include "main.h"

typedef struct UnkPauseMesWork {
    /* 0x00 */ s32 *mes;
    /* 0x04 */ u16 unk_04;
} UnkPauseMesWork;

u8 mbPlayerRankRandTbl[MB_MAX_PLAYERS] = { 34, 62, 84, 100 };
// The zero gap here suggests pause.c is two files split at MBPauseMesNumGet (cf. duel/common comkey.c/pause.c).
u8 mbPauseUnusedTbl[12] = { 0 }; /* Unreferenced. */
s32 mbPauseBoardSprTbl[] = { 0x13007D, 0x13007E, 0x13007F, 0x130080, 0x130081, 0x130082 };
s16 mbPauseOptionSel = 0;
s16 mbPauseMesUpdateF = 0;
s32 mbPauseHelpF = 0;
s32 mbPauseColorNo = 0;
u8 mbPauseColorTbl[][3] = {
    { 254, 255, 164 },
    { 176, 255, 164 },
    { 255, 164, 172 },
    { 164, 231, 255 },
    { 204, 255, 131 }
};
s32 mbPauseGameLenSprTbl[] = { 0x130084, 0x130085, 0x130086, 0x130087 };
s32 mbPauseHelpMesTbl[] = { 0x3001, 0x300A, 0x3004 };
s32 mbPauseOptionMesTbl[] = { 0x5101, 0x5105, 0x5127, 0x512C, 0x5121, 0x5108, 0x510C, 0x5110 };
s32 mbPauseOptionSprTbl[] = { 0x13008C, 0x13008D, 0x13008F, 0x130092, 0x130095, 0x130099, 0x13009B, 0x13009A };
s32 mbPauseMgExplainSprTbl[] = { 0x13008D, 0x13008E };
s32 mbPauseComMgSprTbl[] = { 0x13008F, 0x130090 };
s32 mbPauseMesSpeedSprTbl[] = { 0x130091, 0x130092, 0x130093 };
s32 mbPauseWalkSpeedSprTbl[] = { 0x130094, 0x130095, 0x130096 };
s32 mbPauseSaveModeSprTbl[] = { 0x130097, 0x130098, 0x130099 };
s32 mbPauseOptFlagOffSpr = 0x1300B1;
s32 mbPauseOptFlagOnSpr = 0x1300B2;
s32 mbPausePadCfgOffSpr = 0x13009D;
s32 mbPauseQuitMesTbl[] = { 0x511F, 0x5120 };
s32 mbPauseCharSprTbl[] = { 0x130107, 0x130108, 0x130109, 0x13010A, 0x13010B, 0x13010C, 0x13010D, 0x13010E };
s32 mbPausePadIconSprTbl[] = { 0x13009E, 0x13009F, 0x1300A0, 0x1300A1, 0x1300A2, 0x1300A6, 0x1300A5, 0x1300A4, 0x1300A3 };
s8 mbPausePadIconTbl[8] = { 0, -1, 1, -1, 2, -1, 3, -1 };
s8 mbPauseComIconTbl[8] = { 4, 8, 4, 7, 4, 6, 4, 5 };
s16 mbPausePanelXTbl[4] = { 100, 236, 100, 236 };
s16 mbPausePanelYTbl[4] = { 50, 50, 122, 122 };
s16 mbPausePanelMoveTbl[4][4] = {
    { 0, 2, 0, 1 },
    { 0, 2, -1, 0 },
    { -2, 0, 0, 1 },
    { -2, 0, -1, 0 }
};

extern s16 mbPauseCursorBlinkF;
extern s16 mbPauseHelpWinSize[];
extern s32 GwMessSpeed;
extern s32 GwMessWait;
extern UnkMBGuideData* mbPauseGuide;
extern s32 mbPauseHelpWinL;
extern s32 mbPauseHelpWinR;
extern s16 mbPauseQuitF;
extern s8 omOvlSeKeepF;
extern s16 mbPauseStat;
extern UnkBoard mbMotShiftTbl[16];

static void MBMesSpeedCurSet(s32 arg0);
static void MBWinComKeyExec(s32, s32, s32);
static void MBWinComKey2Exec(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
static void MBWinComKeyAllExec(s32 arg0, s32 arg1);

void MBMesWaitSet(s32 arg0) {
    GwMessWait = arg0;
    MBMesSpeedCurSet(arg0);
}

s32 MBMesWaitGet(void) {
    return GwMessWait;
}

static void MBMesSpeedCurSet(s32 arg0) {
    GwMessSpeed = arg0;
}

void MBWinComKeyWait(s32 arg0, s32 arg1) {
    MBWinComKeyExec(arg0, arg1, 0);
}

void MBWinComKeyWaitKeep(s32 arg0, s32 arg1) {
    MBWinComKeyExec(arg0, arg1, 1);
}

static void MBWinComKeyExec(s32 arg0, s32 arg1, s32 arg2) {
    s16 sp18[MB_MAX_PLAYERS];
    s32 hasCom = 0;
    u8 sp20[MB_MAX_PLAYERS] = {1, 2, 4, 8};
    s32 sp2C;
    s32 i;

    hasCom = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == arg1) {
            if (GwPlayer[i].stat & 1) {
                hasCom = 1;
                sp18[GwPlayer[i].pad] = -0x8000;
            } else {
                HuWinActivePlayerSet(arg0, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (hasCom != 0) {
        HuWinAttrSet(arg0, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        GwMessSpeed = GwMessWait;
    } else {
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    if (arg2 == 0) {
        while (HuWinStatGet(arg0) != 0) {
            HuPrcVSleep();
        }
    } else {
        while ((HuWinStatGet(arg0) != 0) && !(HuWinAttrGet(arg0) & 0x200)) {
            HuPrcVSleep();
        }
        winData[arg0].stat = 7;
    }
    HuWinComKeyReset();
}

void MBWinComKey2Wait(s32 arg0, s32 arg1, s32 arg2) {
    MBWinComKey2Exec(arg0, arg1, arg2, 0);
}

void MBWinComKey2WaitKeep(s32 arg0, s32 arg1, s32 arg2) {
    MBWinComKey2Exec(arg0, arg1, arg2, 1);
}

static void MBWinComKey2Exec(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS] = {1, 2, 4, 8};
    u8 mask;
    s32 i;

    mask = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if ((i == arg1) || (i == arg2)) {
            if (GwPlayer[i].stat & 1) {
                sp18[GwPlayer[i].pad] = -0x8000;
            } else {
                mask |= sp20[GwPlayer[i].pad];
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (mask) {
        HuWinActivePlayerSet(arg0, mask);
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    } else {
        HuWinAttrSet(arg0, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        GwMessSpeed = GwMessWait;
    }

    if (arg3 == 0) {
        while (HuWinStatGet(arg0) != 0) {
            HuPrcVSleep();
        }
    } else {
        while ((HuWinStatGet(arg0) != 0) && !(HuWinAttrGet(arg0) & 0x200)) {
            HuPrcVSleep();
        }
        winData[arg0].stat = 7;
    }
    HuWinComKeyReset();
}

void MBWinComKeyAllWait(s32 arg0) {
    MBWinComKeyAllExec(arg0, 0);
}

void MBWinComKeyAllWaitKeep(s32 arg0) {
    MBWinComKeyAllExec(arg0, 1);
}

static void MBWinComKeyAllExec(s32 arg0, s32 arg1) {
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS] = {1, 2, 4, 8};
    u8 mask;
    s32 i;

    mask = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (!(GwPlayer[i].stat & 1)) {
            break;
        }
    }

    if (i == 4) {
        HuWinAttrSet(arg0, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(A_BUTTON, A_BUTTON, A_BUTTON, A_BUTTON, GwMessSpeed);
        HuWinComKeyWait(A_BUTTON, A_BUTTON, A_BUTTON, A_BUTTON, GwMessSpeed);
        HuWinComKeyWait(A_BUTTON, A_BUTTON, A_BUTTON, A_BUTTON, GwMessSpeed);
        HuWinComKeyWait(A_BUTTON, A_BUTTON, A_BUTTON, A_BUTTON, GwMessSpeed);
        HuWinComKeyWait(A_BUTTON, A_BUTTON, A_BUTTON, A_BUTTON, GwMessSpeed);
        HuWinComKeyWait(A_BUTTON, A_BUTTON, A_BUTTON, A_BUTTON, GwMessSpeed);
        HuWinComKeyWait(A_BUTTON, A_BUTTON, A_BUTTON, A_BUTTON, GwMessSpeed);
        GwMessSpeed = GwMessWait;
        if (arg1 == 0) {
            while (HuWinStatGet(arg0) != 0) {
                HuPrcVSleep();
            }
        } else {
            while ((HuWinStatGet(arg0) != 0) && !(HuWinAttrGet(arg0) & 0x200)) {
                HuPrcVSleep();
            }
            winData[arg0].stat = 7;
        }
    } else {
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            if (GwPlayer[i].stat & 1) {
                sp18[GwPlayer[i].pad] = 0;
            } else {
                mask |= sp20[GwPlayer[i].pad];
                sp18[GwPlayer[i].pad] = -1;
            }
        }
        HuWinActivePlayerSet(arg0, mask);
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
        if (arg1 == 0) {
            while (HuWinStatGet(arg0) != 0) {
                HuPrcVSleep();
            }
        } else {
            while ((HuWinStatGet(arg0) != 0) && !(HuWinAttrGet(arg0) & 0x200)) {
                HuPrcVSleep();
            }
            winData[arg0].stat = 7;
        }
    }
    HuWinComKeyReset();
}

const u8 pad[4] = {0, 0, 0, 0};

void MBWinComKeyAnyWait(s32 arg0) {
    HuWinActivePlayerSet(arg0, HUWIN_PLAYER_ALL);
    HuWinComKeySet(-1, -1, -1, -1);
    while ((HuWinStatGet(arg0)) != 0) {
        HuPrcVSleep();
    }
    HuWinComKeyReset();
}

void MBModelJumpSet(Object* arg0, f32 arg1, f32 arg2) {
    arg0->velocity.y = arg1;
    arg0->velocity.z = arg2;
}

s32 MBModelJumpCheck(Object* arg0) {
    if (arg0->velocity.z == 0.0f) {
        return 0;
    } else {
        return 1;
    }
}

void MBModelJumpWait(Object* arg0) {
    while (MBModelJumpCheck(arg0) != 0) {
        HuPrcVSleep();
    }
}

void MBMotShiftInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbMotShiftTbl); i++) {
        mbMotShiftTbl[i].unk_04 = NULL;
        mbMotShiftTbl[i].unk_08 = NULL;
    }
}

void MBMotShiftClose(void) {
    UnkBoard* temp_s1;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbMotShiftTbl); i++) {
        temp_s1 = &mbMotShiftTbl[i];
        if (temp_s1->unk_08 != NULL) {
            omDelObj(temp_s1->unk_08);
            temp_s1->unk_08 = NULL;
        }
    }
}

static void MBMotShiftObjMain(omObjData *func) {
    UnkBoard *temp_s0;

    temp_s0 = &mbMotShiftTbl[func->work[0]];
    if (Hu3DData[temp_s0->unk_04->omObj1->model[0]].motTime ==
        Hu3DMotion[Hu3DData[temp_s0->unk_04->omObj1->model[0]].motId].unk02) {
        MBMotionShiftSet(temp_s0->unk_04, temp_s0->unk_00, 0, 0xA, temp_s0->unk_02);
        temp_s0->unk_04 = NULL;
        temp_s0->unk_08 = NULL;
        omDelObj(func);
    }
}

u32 MBMotionEndShiftSet(Object *arg0, s16 arg1, s16 arg2) {
    omObjData *obj;
    UnkBoard *temp_s1;
    s32 i;
    s32 ret;

    for (i = 0; i < ARRAY_COUNT(mbMotShiftTbl); i++) {
        temp_s1 = &mbMotShiftTbl[i];
        if (temp_s1->unk_08 == NULL) {
            break;
        }
    }

    if (i != ARRAY_COUNT(mbMotShiftTbl)) {
        obj = omAddObj(0x2000, 0, 0, -1, MBMotShiftObjMain);
        temp_s1->unk_08 = obj;
        obj->work[0] = i;
        temp_s1->unk_04 = arg0;
        temp_s1->unk_00 = arg1;
        temp_s1->unk_02 = arg2;
        ret = i;
    } else {
        ret = -1;
    }
    return ret;
}

//unused
void MBMotionShiftSetDef(Object *arg0, s16 arg1, s32 arg2) {
    MBMotionShiftSet(arg0, arg1, 0, 0xA, arg2);
}

void MBModelMotionWait(Object *arg0) {
    while (!(MBMotionCheck(arg0) & 1)) {
        HuPrcVSleep();
    }
}

s32 MBPlayerRankCalc(s32 player) {
    s32 rank;
    s32 i;
    s32 score[4];

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        score[i] = MBPlayerScoreGet(i);
    }

    for (rank = 0, i = 0; i < MB_MAX_PLAYERS; i++) {
        if ((i != player) && (score[player] < score[i])) {
            rank++;
        }
    }
    return rank;
}

s32 MBPlayerStealRankGet(s32 arg0) {
    s32 var_a0_2;
    s32 var_a0;
    s32 i;
    s32 score[MB_MAX_PLAYERS];

    if (GWBoardFlagCheck(0xF) == 0) {
        return MBPlayerRankCalc(arg0);
    }

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        score[i] = MBPlayerScoreGet(i);
    }

    // calc what the highest mg coin total is
    for (i = 0, var_a0_2 = -100000; i < MB_MAX_PLAYERS; i++) {
        if (var_a0_2 < GwPlayer[i].gamePrize) {
            var_a0_2 = GwPlayer[i].gamePrize;
        }
    }

    // award players 1000 points (a star) for having the highest mg coin total
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (GwPlayer[i].gamePrize == var_a0_2) {
            score[i] += 1000;
        }
    }

    // calc what the highest amount of coins collected was
    for (i = 0, var_a0_2 = -100000; i < MB_MAX_PLAYERS; i++) {
        if (var_a0_2 < GwPlayer[i].coinPrize) {
            var_a0_2 = GwPlayer[i].coinPrize;
        }
    }

    // award players 1000 points (a star) for having the highest amount of coins
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (GwPlayer[i].coinPrize == var_a0_2) {
            score[i] += 1000;
        }
    }

    // calc what the highest amount of happening spaces landed on was
    for (i = 0, var_a0_2 = -100000; i < MB_MAX_PLAYERS; i++) {
        if (var_a0_2 < GwPlayer[i].stats.prize.hatenaPrize) {
            var_a0_2 = GwPlayer[i].stats.prize.hatenaPrize;
        }
    }

    // award players 1000 points (a star) for landing on the most happening spaces
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (GwPlayer[i].stats.prize.hatenaPrize == var_a0_2) {
            score[i] += 1000;
        }
    }

    for (i = 0, var_a0 = 0; i < MB_MAX_PLAYERS; i++) {
        if (i != arg0) {
            var_a0 += score[arg0] < score[i];
        }
    }

    return var_a0;
}

s32 MBPlayerScoreGet(s32 arg0) {
    return GwPlayer[arg0].star * 1000 + GwPlayer[arg0].coin;
}

//unused
s32 MBPlayerBonusScoreGet(s32 arg0) {
    s32 var_a0_2;
    s32 i;
    s32 playerBaseScore;

    playerBaseScore = (GwPlayer[arg0].star * 1000) + GwPlayer[arg0].coin;

    if (GWBoardFlagCheck(0xF) != 0) {
        // calc what the highest mg coin total is
        for (i = 0, var_a0_2 = -100000; i < MB_MAX_PLAYERS; i++) {
            if (var_a0_2 < GwPlayer[i].gamePrize) {
                var_a0_2 = GwPlayer[i].gamePrize;
            }
        }

        if (GwPlayer[arg0].gamePrize == var_a0_2) {
            playerBaseScore += 1000;
        }

        // calc what the highest amount of coins collected was
        for (i = 0, var_a0_2 = -100000; i < MB_MAX_PLAYERS; i++) {
            if (var_a0_2 < GwPlayer[i].coinPrize) {
                var_a0_2 = GwPlayer[i].coinPrize;
            }
        }

        if (GwPlayer[arg0].coinPrize == var_a0_2) {
            playerBaseScore += 1000;
        }

        for (i = 0, var_a0_2 = -100000; i < MB_MAX_PLAYERS; i++) {
            if (var_a0_2 < GwPlayer[i].stats.prize.hatenaPrize) {
                var_a0_2 = GwPlayer[i].stats.prize.hatenaPrize;
            }
        }

        if (GwPlayer[arg0].stats.prize.hatenaPrize == var_a0_2) {
            playerBaseScore += 1000;
        }
    }
    return playerBaseScore;
}

//unused
void MBPlayerKeyWait(void) {
    s32 i;

    HuPrcSleep(2);
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (!(GwPlayer[i].stat & 1)) {
            break;
        }
    }

    if (i == MB_MAX_PLAYERS) {
        HuPrcSleep(30);
        return;
    }

    while (1) {
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            if (!(GwPlayer[i].stat & 1) &&
                (HuPadBtnDown[GwPlayer[i].pad] & (A_BUTTON | B_BUTTON))) {
                break;
            }
        }

        if (i == MB_MAX_PLAYERS) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
}

s32 MBRand(f32 arg0) { // 800EFE20 in duel mode,
    // rand8 returns an unsigned byte
    u8 randomByte1 = rand8();
    u8 randomByte2 = rand8();
    s32 shiftedByte1 = (randomByte1 << 8);

    // Normalize the 16-bit number to the range [0, 1), then multiply by arg0
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;

    return scaledRandom;
}

// is there some kind of macro at play here? the cast to u8 is weird because `work` used to be u8[] in mp1/mp2
void MBGuideFaceCreate(Object *arg0, s16 arg1, s16 arg2, s32 arg3) {
    arg0->omObj1->work[0] = (u8)CharAnimCreate(arg0->omObj1->model[0], arg1, arg2, arg3);
    arg0->omObj1->work[1] = (u8)arg1;
    arg0->omObj1->work[2] = (u8)arg2;
}

void MBGuideFaceKill(void) {
}

void MBGuideFaceSet(Object* arg0, s32 arg1) {
    Hu3DAnimDataKill(arg0->omObj1->work[0]);
    arg0->omObj1->work[0] = (u8)Hu3DAnimDataRead(arg1);
    CharAnimSet(arg0->omObj1->model[0], arg0->omObj1->work[1], arg0->omObj1->work[2], arg0->omObj1->work[0]);
}

s32 MBPlayerRankRandGet(s32 arg0) {
    s32 randVal;
    s32 scoreIndex;
    s32 score[MB_MAX_PLAYERS];
    s32 curPlayerScore;
    s32 i, j;

    for (i = 0, scoreIndex = 0; i < MB_MAX_PLAYERS; i++) {
        for (j = 0; j < MB_MAX_PLAYERS; j++) {
            if (MBPlayerRankCalc(j) == i) {
                score[scoreIndex++] = j;
            }
        }
    }

    while (1) {
        randVal = MBRand(100.0f);
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            if (mbPlayerRankRandTbl[i] < randVal) {
                continue;
            } else {
                break;
            }
        }

        if (arg0 != 0 && score[i] == GwSystem.current_player_index) {
            continue;
        } else {
            break;
        }
    }

    // for some reason this requires reassigning i
    i = score[i];
    if (i >= MB_MAX_PLAYERS) {
        i = GwSystem.current_player_index + 1;
        i = (i < MB_MAX_PLAYERS) ? i : 0;
    }

    return i;
}

s32 MBPauseMesNumGet(s32 arg0) {
    return arg0;
}

static void MBPauseTurnNumSet(UnkBoard8* arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4) {
    u8 temp_s0;
    void* temp_s5;
    s32 i;

    temp_s5 = DataRead(0x13008A);
    sprintf(omDBGStrBuf, "%2d", arg2);
    
    for (i = 0; i < 2; i++) {
        temp_s0 = omDBGStrBuf[i];
        arg0->model[arg1] = HuSprAnimRead(temp_s5);
        if (temp_s0 != 0x20) {
            HuSprGrpMemberSet(arg0->spriteGroup, arg1, arg0->model[arg1], temp_s0 - 0x30);
        } else {
            HuSprGrpMemberSet(arg0->spriteGroup, arg1, arg0->model[arg1], 0xA);
        }
        
        HuSprPriSet(arg0->spriteGroup, arg1, 7);
        HuSprAttrSet(arg0->spriteGroup, arg1, 0x01001000);
        HuSprPosSet(arg0->spriteGroup, arg1, arg3, arg4);
        HuSprColorSet(arg0->spriteGroup, arg1, mbPauseColorTbl[mbPauseColorNo][0], mbPauseColorTbl[mbPauseColorNo][1], mbPauseColorTbl[mbPauseColorNo][2]);
        arg1 += 1;
        arg3 += 0xE;        
    }
    DataClose(temp_s5);
}

static UnkBoard8* MBPauseTurnNumCreate(void) {
    UnkBoard8* temp_s2;
    void* temp_v0_2;
    void* temp_v0_4;
    void* var_s0;

    temp_s2 = MBSprGrpCreate(0x10, 0);
    mbPauseColorNo = GwSystem.current_game_length;
    if (GwSystem.playMode & 4) {
        var_s0 = DataRead(0x13008B);
        mbPauseColorNo = 4;
    } else {
        var_s0 = DataRead(mbPauseGameLenSprTbl[GwSystem.current_game_length]);
    }
    temp_s2->model[0] = HuSprAnimRead(var_s0);
    HuSprGrpMemberSet(temp_s2->spriteGroup, 0, temp_s2->model[0], 0);
    HuSprPriSet(temp_s2->spriteGroup, 0, 7);
    HuSprAttrSet(temp_s2->spriteGroup, 0, 0x1000);
    HuSprPosSet(temp_s2->spriteGroup, 0, 0xA0, 0x73);
    HuSprColorSet(temp_s2->spriteGroup, 0, mbPauseColorTbl[mbPauseColorNo][0], mbPauseColorTbl[mbPauseColorNo][1], mbPauseColorTbl[mbPauseColorNo][2]);
    DataClose(var_s0);
    temp_v0_2 = DataRead(0x130088);
    temp_s2->model[1] = HuSprAnimRead(temp_v0_2);
    HuSprGrpMemberSet(temp_s2->spriteGroup, 1, temp_s2->model[1], 0);
    HuSprPriSet(temp_s2->spriteGroup, 1, 7);
    HuSprAttrSet(temp_s2->spriteGroup, 1, 0x1000);
    HuSprPosSet(temp_s2->spriteGroup, 1, 0xA0, 0x90);
    HuSprColorSet(temp_s2->spriteGroup, 1, mbPauseColorTbl[mbPauseColorNo][0], mbPauseColorTbl[mbPauseColorNo][1], mbPauseColorTbl[mbPauseColorNo][2]);
    DataClose(temp_v0_2);
    MBPauseTurnNumSet(temp_s2, 2, GwSystem.total_turns, 0xCB, 0x90);
    MBPauseTurnNumSet(temp_s2, 4, GwSystem.current_turn, 0xA1, 0x90);
    temp_v0_4 = DataRead(mbPauseBoardSprTbl[GwSystem.current_board_index]);
    temp_s2->model[6] = HuSprAnimRead(temp_v0_4);
    HuSprGrpMemberSet(temp_s2->spriteGroup, 6, temp_s2->model[6], 0);
    HuSprPriSet(temp_s2->spriteGroup, 6, 7);
    HuSprAttrSet(temp_s2->spriteGroup, 6, 0x1000);
    HuSprPosSet(temp_s2->spriteGroup, 6, 0xA0, 0x3C);
    DataClose(temp_v0_4);
    return temp_s2;
}

static void MBPauseTurnNumKill(UnkBoard8* arg0) {
    MBSprGrpKill(arg0);
}

static s16 MBPauseMainScrExec(s32 arg0) {
    Unk3* temp_s2;
    Unk3* temp_s3;
    s16 var_s0;
    UnkBoard8* temp_s1;

    temp_s3 = MBHelpWinCreate(0xA, 0xAE, 0);
    temp_s2 = MBHelpWinCreate(5, 0xBC, 0);
    temp_s1 = MBPauseTurnNumCreate();
    HuPrcVSleep();

    while (1) {
        HuPrcVSleep();
        if (HuPadBtnDown[arg0] & A_BUTTON) {
            var_s0 = 4;
            break;
        } else if (HuPadBtnDown[arg0] & START_BUTTON) {
            var_s0 = 0;
            break;
        }       
    }

    MBPauseTurnNumKill(temp_s1);
    MBHelpWinKill(temp_s3);
    MBHelpWinKill(temp_s2);
    return var_s0;
}

static void MBPauseGuideMove(UnkMBGuideData* arg0, s16 arg1) {
    s32 i;
    Object* obj;
    s16 temp_s2;
    s16 temp = arg0->spriteGroup;
    
    obj = arg0->obj;
    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.5f;
    temp_s2 = (arg1 - temp) / 14;

    for (i = 0; i < 14; i++) {
        temp = arg0->spriteGroup;
        MBGuidePosSet(arg0, (temp + temp_s2), 8);
        HuPrcVSleep();        
    }
    MBGuidePosSet(arg0, arg1, 8);
}

static void MBPauseDlgMesSet(s16 arg0, s32 arg1) {
    HuWinHomeClear(arg0);
    HuWinMesSet(arg0, MBPauseMesNumGet(arg1), -1, -1);
}

static void MBPauseHelpMesSet(s32 arg0, s16 arg1) {
    HuWinHomeClear(arg0);
    HuWinMesSet(arg0, mbPauseHelpMesTbl[arg1], HUWIN_POS_CENTER, HUWIN_POS_CENTER);
}

static s32 MBPauseHelpMesCreate(s16 arg0, s16 arg1, s16 arg2) {
    s16 sp18[2];
    s16 sp20[2];
    s32 win;

    HuWinMesMaxSizeGet(1, sp18, mbPauseHelpMesTbl[0]);
    HuWinMesMaxSizeGet(1, sp20, mbPauseHelpMesTbl[1]);

    if (sp20[0] > sp18[0]) {
        mbPauseHelpWinSize[0] = sp20[0];
    } else {
        mbPauseHelpWinSize[0] = sp18[0];
    }
    mbPauseHelpWinSize[1] = sp18[1];
    arg1 += 0xA0;
    win = HuWinCreate(arg1 - (mbPauseHelpWinSize[0] / 2), arg2,
                              mbPauseHelpWinSize[0], mbPauseHelpWinSize[1], 0, 4);
    HuWinPriSet(win, 9);
    HuWinBGTPLvlSet(win, 0);
    HuWinMesSpeedSet(win, 0);
    HuWinAttrSet(win, HUWIN_ATTR_NONE, HUWIN_ATTR_OUTLINE);
    MBPauseHelpMesSet(win, arg0);
    return win;
}

static void MBPauseMesMain(void) {
    UnkPauseMesWork *work;
    s32 *mes;
    s16 sel;
    s16 sel2;
    s16 prev;
    s32 help;
    s32 i;
    GW_SYSTEM* system;

    work = HuPrcCurrentGet()->user_data;
    
    mes = work->mes;
    sel = work->unk_04;
    system = &GwSystem;
    prev = -1;

    if (mbPauseHelpF != 0) {
        mbPauseHelpWinL = MBPauseHelpMesCreate(0, 0, 0x92);
        mbPauseHelpWinR = MBPauseHelpMesCreate(2, 0x64, 0x92);
    }

    while (1) {
        if (mbPauseHelpF != 0) {
            sel2 = mbPauseOptionSel;
        } else {
            sel2 = HuWinChoiceNowGet(sel);
        }

        if (((sel2 != prev) && (sel2 != -1)) || (mbPauseMesUpdateF != 0)) {
            if ((mbPauseMesUpdateF == 0) && (mbPauseHelpF != 0)) {
                switch (sel2) {
                case 0:
                case 7:
                    MBPauseHelpMesSet(mbPauseHelpWinL, 0);
                    break;
                default:
                    MBPauseHelpMesSet(mbPauseHelpWinL, 1);
                }
            }

            prev = sel2;
            mbPauseMesUpdateF = 0;

            switch (mes[prev]) {
            case 0x5101:
                for (i = 0; i < 4; i++) {
                    if (GwPlayer[i].stat & 1) {
                        HuWinInsertMesSet(mbPauseGuide->amount, MBPauseMesNumGet(0x5104), i);
                    } else {
                        HuWinInsertMesSet(mbPauseGuide->amount, MBPauseMesNumGet(0x5103), i);
                    }
                }
                break;

            case 0x5105:
                if (system->show_minigame_explanations == 0) {
                    HuWinInsertMesSet(mbPauseGuide->amount, MBPauseMesNumGet(0x5106), 0);
                } else {
                    HuWinInsertMesSet(mbPauseGuide->amount, MBPauseMesNumGet(0x5107), 0);
                }
                break;

            case 0x5108:
                switch (system->message_speed) {
                case 0:
                    HuWinInsertMesSet(mbPauseGuide->amount, MBPauseMesNumGet(0x5109), 0);
                    break;
                case 1:
                    HuWinInsertMesSet(mbPauseGuide->amount, MBPauseMesNumGet(0x510A), 0);
                    break;
                case 2:
                    HuWinInsertMesSet(mbPauseGuide->amount, MBPauseMesNumGet(0x510B), 0);
                    break;
                }
                break;

            case 0x510C:
                switch (system->save_mode) {
                case 0:
                    HuWinInsertMesSet(mbPauseGuide->amount, MBPauseMesNumGet(0x510D), 0);
                    break;
                case 1:
                    HuWinInsertMesSet(mbPauseGuide->amount, MBPauseMesNumGet(0x510E), 0);
                    break;
                case 2:
                    HuWinInsertMesSet(mbPauseGuide->amount, MBPauseMesNumGet(0x510F), 0);
                    break;
                }
                break;

            case 0x5121:
                switch (system->walk_speed) {
                case 0:
                    HuWinInsertMesSet(mbPauseGuide->amount, MBPauseMesNumGet(0x5122), 0);
                    break;
                case 1:
                    HuWinInsertMesSet(mbPauseGuide->amount, MBPauseMesNumGet(0x5123), 0);
                    break;
                case 2:
                    HuWinInsertMesSet(mbPauseGuide->amount, MBPauseMesNumGet(0x5124), 0);
                    break;
                }
                break;

            case 0x5127:
                switch (system->show_com_minigames) {
                case 0:
                    HuWinInsertMesSet(mbPauseGuide->amount, MBPauseMesNumGet(0x5128), 0);
                    break;
                case 1:
                    HuWinInsertMesSet(mbPauseGuide->amount, MBPauseMesNumGet(0x5129), 0);
                    break;
                }
                break;

            case 0x512C:
                if (_CheckFlag(0x20) != 0) {
                    HuWinInsertMesSet(mbPauseGuide->amount, MBPauseMesNumGet(0x512B), 0);
                } else {
                    HuWinInsertMesSet(mbPauseGuide->amount, MBPauseMesNumGet(0x512A), 0);
                }
                break;
            }

            MBPauseDlgMesSet(mbPauseGuide->amount, mes[prev]);
        }
        HuPrcVSleep();
    }
}

// draws a message?
static Process* MBPauseMesCreate(s32* arg0, s32 arg1, s16 arg2) {
    Process* proc;
    UnkPauseMesWork* temp_v0_2;

    proc = omAddPrcObj(MBPauseMesMain, 0x1005, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(proc->heap, sizeof(UnkPauseMesWork));
    proc->user_data = temp_v0_2;
    temp_v0_2->mes = arg0;
    temp_v0_2->unk_04 = arg2;
    mbPauseHelpF = arg1;
    return proc;
}

static void MBPauseMesKill(Process* arg0) {
    if (mbPauseHelpF != 0) {
        HuWinKill(mbPauseHelpWinL);
        HuWinKill(mbPauseHelpWinR);
    }
    omDelPrcObj(arg0);
}

static s16 MBPauseQuitMesCreate(s32 arg0, s16 arg1) {
    s16 sp18[2];
    s16 temp_v0;

    HuWinMesMaxSizeGet(1, sp18, arg0);
    temp_v0 = HuWinCreate(0xA0 - sp18[0] / 2, arg1, sp18[0], sp18[1], 0, 0);
    HuWinMesSet(temp_v0, arg0, -1, -1);
    return temp_v0;
}

static s16 MBPauseWinActiveCheck(void) {
    s16 var_t0;
    s16 var_a1;

    var_t0 = 0;
    var_a1 = winData->unk64;
    while (winData[var_a1].unk64 != -1) {
        if (winData[var_a1].attr & HUWIN_ATTR_PAUSE) {
            var_t0 |= (u8)winData[var_a1].stat; //TODO: why required cast?
        }
        var_a1 = winData[var_a1].unk64;
    }

    if (GwSystem.playMode & 4) {
        var_t0 = 1;
    }
    return var_t0;
}

static void MBPauseOptionIconSet(UnkBoard8 *arg0, s32 arg1) {
    void *data;
    s32 dataNum;
    GW_SYSTEM* system = &GwSystem;

    switch (arg1) {
    case 1:
        dataNum = mbPauseMgExplainSprTbl[system->show_minigame_explanations];
        break;
    case 2:
        dataNum = mbPauseComMgSprTbl[system->show_com_minigames];
        break;
    case 5:
        dataNum = mbPauseMesSpeedSprTbl[system->message_speed];
        break;
    case 4:
        dataNum = mbPauseWalkSpeedSprTbl[system->walk_speed];
        break;
    case 6:
        dataNum = mbPauseSaveModeSprTbl[system->save_mode];
        break;
    case 3:
        if (_CheckFlag(0x20) != 0) {
            dataNum = mbPauseOptFlagOnSpr;
        } else {
            dataNum = mbPauseOptFlagOffSpr;
        }
        break;
    default:
        return;
    }

    data = DataRead(dataNum);
    HuSprAnimKill(arg0->model[arg1]);
    arg0->model[arg1] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(arg0->spriteGroup, arg1, arg0->model[arg1], 0);
    HuSprPriSet(arg0->spriteGroup, arg1, 8);
    HuSprAttrSet(arg0->spriteGroup, arg1, 0x1000);
    HuSprPosSet(arg0->spriteGroup, arg1,
                        ((arg1 % 4) << 6) + 0x46,
                        ((arg1 / 4) * 0x3C) + 0x3C);
    mbPauseMesUpdateF = 1;
}


static s32 MBPauseOptionExec(s32 arg0) {
    void *data;
    Process *mesProc;
    UnkBoard8 *icons;
    UnkBoard8 *cursor;
    s32 dataNum;
    s8 ret;
    s16 sel;
    s16 prevSel;
    s32 i;
    u8 sleepFlag;
    GW_SYSTEM* system;
    GW_COMMON* common = &GwCommon;
    s8 temp;

    ret = 4;
    sel = 0;
    prevSel = 0;
    mesProc =  NULL;
    icons = NULL; // s4
    cursor = NULL;
    sleepFlag = 0;
    system = &GwSystem;
    
    if (!mbPauseQuitF) {
        sel = mbPauseOptionSel;
        prevSel = sel;
        icons = MBSprGrpCreate(8, 0);
        
        for (i = 0; i < 8; i++) {
            switch (i) {
            case 0:
                if ((MBPauseWinActiveCheck()) != 0) {
                    dataNum = mbPausePadCfgOffSpr;
                } else {
                    dataNum = mbPauseOptionSprTbl[0];
                }
                break;
            case 1:
                dataNum = mbPauseMgExplainSprTbl[system->show_minigame_explanations];
                break;
            case 2:
                dataNum = mbPauseComMgSprTbl[system->show_com_minigames];
                break;
            case 5:
                dataNum = mbPauseMesSpeedSprTbl[system->message_speed];
                break;
            case 4:
                dataNum = mbPauseWalkSpeedSprTbl[system->walk_speed];
                break;
            case 6:
                dataNum = mbPauseSaveModeSprTbl[system->save_mode];
                break;
            case 3:
                if (_CheckFlag(0x20) != 0) {
                    dataNum = mbPauseOptFlagOnSpr;
                } else {
                    dataNum = mbPauseOptFlagOffSpr;
                }
                break;
            default:
                dataNum = mbPauseOptionSprTbl[i];
                break;
            }
    
            data = DataRead(dataNum);
            icons->model[i] = HuSprAnimRead(data);
            DataClose(data);
            HuSprGrpMemberSet(icons->spriteGroup, i, icons->model[i], 0);
            HuSprPriSet(icons->spriteGroup, i, 8);
            HuSprAttrSet(icons->spriteGroup, i, 0x1000);
            HuSprPosSet(icons->spriteGroup, i,
                                ((i % 4) << 6) + 0x46,
                                ((i / 4) * 0x3C) + 0x3C);
        }
    
        if (mbPauseGuide == NULL) {
            HuPrcVSleep();
            mbPauseGuide = MBGuideCreate(0, 8);
            HuWinTabWidthSet(mbPauseGuide->amount, 0x2D);
            MBModelTempAllocFree(mbPauseGuide->obj);
            Hu3DModelAttrSet(mbPauseGuide->obj->omObj1->model[0], HU3D_ATTR_NOPAUSE, HU3D_ATTR_NOPAUSE);
            mbPauseGuide->obj->flags |= 0x10;
            MBGuidePosSet(mbPauseGuide, 0x104, 8);
            MBPauseGuideMove(mbPauseGuide, 0x69);
            HuWinExPriSet(mbPauseGuide->amount, 5);
            HuWinExOpen(mbPauseGuide->amount, 1);
        }
    
        cursor = MBSprGrpCreate(1, 0);
        data = DataRead(0x13009C);
        cursor->model[0] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(cursor->spriteGroup, 0, cursor->model[0], 0);
        HuSprPriSet(cursor->spriteGroup, 0, 7);
        HuSprAttrSet(cursor->spriteGroup, 0, 0x1000);
        HuSprPosSet(cursor->spriteGroup, 0,
                            ((mbPauseOptionSel % 4) * 64) + 0x2A,
                            ((mbPauseOptionSel / 4) * 60) + 0x20);
    
        mesProc = MBPauseMesCreate(mbPauseOptionMesTbl, 1, -1);
    
    restart:
        while (1) {
            HuPrcVSleep();
    
            if (ContBtnRep[arg0] & L_JPAD) {
                sel--;
                if ((sel == 3) || (sel == -1)) {
                    sel += 4;
                }
            }
            if (ContBtnRep[arg0] & R_JPAD) {
                sel++;
                if ((sel == 4) || (sel == 8)) {
                    sel -= 4;
                }
            }
            if (ContBtnRep[arg0] & U_JPAD) {
                sel -= 4;
                if (sel < 0) {
                    sel += 8;
                }
            }
            if (ContBtnRep[arg0] & D_JPAD) {
                sel += 4;
                if (sel >= 8) {
                    sel -= 8;
                }
            }
    
            if (ContBtnDown[arg0] & A_BUTTON) {
                HuAudFXPlay(2);
                break;
            }
            if (ContBtnDown[arg0] & B_BUTTON) {
                HuAudFXPlay(4);
                sel = -1;
                break;
            }
    
            if (sel != -1) {
                mbPauseOptionSel = sel;
            }
            if (prevSel != sel) {
                prevSel = sel;
                HuAudFXPlay(1);
            }
            HuSprPosSet(cursor->spriteGroup, 0,
                                ((mbPauseOptionSel % 4) * 64) + 0x2A,
                                ((mbPauseOptionSel / 4) * 0x3C) + 0x20);
        }
    
        switch (sel) {
        case 0:
            if ((MBPauseWinActiveCheck()) == 0) {
                ret = 2;
            }
            break;
        case 1:
            system->show_minigame_explanations ^= 1;
            MBPauseOptionIconSet(icons, 1);
            break;
        case 2:
            system->show_com_minigames ^= 1;
            MBPauseOptionIconSet(icons, 2);
            break;
        case 5:
            temp = (system->message_speed + 1);
            system->message_speed = temp % 3;
            MBPauseOptionIconSet(icons, 5);
            break;
        case 4:
            temp = (system->walk_speed + 1);
            system->walk_speed = temp % 3;
            MBPauseOptionIconSet(icons, 4);
            break;
        case 6:
            temp = (system->save_mode + 1);
            system->save_mode = temp % 3;
            MBPauseOptionIconSet(icons, 6);
            break;
        case 3:
            if (_CheckFlag(0x20) != 0) {
                _ClearFlag(0x20);
            } else {
                _SetFlag(0x20);
            }
            MBPauseOptionIconSet(icons, 3);
            break;
        case 7:
            ret = 9;
            break;
        case -1:
            ret = 1;
            break;
        }
    
        common->unk9E = system->save_mode;
        common->unk9F = system->show_minigame_explanations;
        common->unkA0 = system->message_speed;
        common->unkA1 = system->walk_speed;
        common->unkA2 = system->show_com_minigames;
        MBMesSpeedSet(common->unkA0);
        if ((ret == 2) || (ret == 9)) {
            MBSprGrpKill(icons);
            MBSprGrpKill(cursor);
            icons = NULL;
            cursor = NULL;
        }
    } else {
        ret = 0;
    }

    switch (ret) {
    case 0:
    case 1:
        if (mbPauseGuide != NULL) {
            HuWinExClose(mbPauseGuide->amount, 1);
            MBPauseGuideMove(mbPauseGuide, 0x104);
            MBGuideKill(mbPauseGuide);
            mbPauseGuide = NULL;
            if (icons != NULL) {
                MBSprGrpKill(icons);
                MBSprGrpKill(cursor);
            }
            sleepFlag = 1;
        }
        break;
    case 4:
        goto restart;
    }

    if (mesProc != NULL) {
        MBPauseMesKill(mesProc);
    }
    if (sleepFlag != 0) {
        HuPrcSleep(5);
    }
    return ret;
}

static s32 MBPauseQuitWinExec(s32 arg0) {
    Process* temp_s3;
    s16 temp_v0;
    s16 temp;

    temp_v0 = MBPauseQuitMesCreate(MBPauseMesNumGet(0x511E), 0x36);
    HuWinPriSet(temp_v0, 5);
    HuWinBGTPLvlSet(temp_v0, 0xFF);
    HuWinMesSet(temp_v0, MBPauseMesNumGet(0x511E), -1, -1);
    HuWinMesSpeedSet(temp_v0, 0);
    
    while ((HuWinStatGet(temp_v0)) != 0) {
        HuPrcVSleep();
    }
    
    temp_s3 = MBPauseMesCreate(mbPauseQuitMesTbl, 0, temp_v0);
    HuWinActivePlayerSet(temp_v0, 1 << arg0);
    temp = HuWinChoiceGet(temp_v0, 0, 0);
    if (temp == 1) {
        mbPauseQuitF = 1;
    }
    omDelPrcObj(temp_s3);
    HuWinKill(temp_v0);
    return 4;
}

static s32 MBPausePadUsedCheck(s16 arg0) {
    GW_PLAYER* player;
    s32 i;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        player = MBPlayerGet(i);
        if (!(player->stat & 1)) {
            if (player->pad == arg0) {
                return 1;
            }
        }
    }
    return 0;
}

static void MBPausePadSet(GW_PLAYER* arg0, s16 arg1) {
    GW_PLAYER* player;
    s32 i;
    u8 pad;

    pad = arg0->pad;
    if (arg1 < 4) {
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            player = MBPlayerGet(i);
            if (player->pad != arg1) {
                continue;
            }
            player->pad = pad;
            arg0->pad = arg1;
            arg0->stat &= ~1;
            return;
        }        
    } else {
        arg0->stat |= 1;
    }
}

static s32 MBPausePadNextGet(GW_PLAYER *arg0, s16 arg1) {
    s32 count;
    s32 port;
    u32 i;

    if (MBPlayerComCheck(arg0->turn) != 0) {
        count = 4;
        if (arg1 > 0) {
            port = 0;
        } else {
            port = 3;
        }
        for (; count != 0; count--) {
            if ((MBPausePadUsedCheck(port) == 0) &&
                (CheckControllerRead(port) != 0)) {
                return port;
            }
            port += arg1;
        }
        return 4;
    }

    //TODO: reg alloc hack
    port = (arg1 - 1) >= 0;
    if (port) {
        i = arg0->pad + 1;
    } else {
        i = arg0->pad - 1;
    }
    
    for (; i < 4; i += arg1) {
        if ((MBPausePadUsedCheck(i) == 0)) {
            if (CheckControllerRead(i) != 0) {
                return i;
            }
            
        }
    }
    return 4;
}

static void MBPauseCursorBlinkSet(s16 arg0) {
    mbPauseCursorBlinkF = arg0;
}

static void MBPauseCursorPosSet(UnkBoard8* arg0, s16 arg1) {
    HuSprPosSet(arg0->spriteGroup, 0, (mbPausePanelXTbl[arg1] - 55), (mbPausePanelYTbl[arg1] - 8));
    HuSprPosSet(arg0->spriteGroup, 1, (mbPausePanelXTbl[arg1] + 50), mbPausePanelYTbl[arg1]);
    HuSprPosSet(arg0->spriteGroup, 2, (mbPausePanelXTbl[arg1] - 50), mbPausePanelYTbl[arg1]);
}

static void MBPauseCursorProc(void) {
    f32 var_f20;
    s32 var_v0;
    UnkBoard8* temp_s1;

    temp_s1 = HuPrcCurrentGet()->user_data;
    var_f20 = 0.0f;
    while (1) {
        HuPrcVSleep();
        if (mbPauseCursorBlinkF != 0) {
            var_v0 = (s16) (sindf(var_f20) * 255.0f); //TODO: s16 cast
            if (var_v0 < 0) {
                var_v0 = -var_v0;
            }
            var_f20 += 6.0f;
            if (var_f20 > 360.0f) {
                var_f20 -= 360.0f;
            }
            HuSprColorSet(temp_s1->spriteGroup, 1, 0xFFU, var_v0, 0U);
            HuSprColorSet(temp_s1->spriteGroup, 2, 0xFFU, var_v0, 0U);
            HuSprDispOn(temp_s1->spriteGroup, 1);
            HuSprDispOn(temp_s1->spriteGroup, 2);
        } else {
            var_f20 = 0.0f;
            HuSprDispOff(temp_s1->spriteGroup, 1);
            HuSprDispOff(temp_s1->spriteGroup, 2);
        }
    }
}

static s32 MBPausePadCfgExec(s32 arg0) {
    s16 sel;
    UnkBoard8* panel;
    UnkBoard8* chr;
    UnkBoard8* icon;
    UnkBoard8* cursor;
    UnkBoard8* bg;
    Process* proc;
    GW_PLAYER* player;
    void* data;
    u16* trg;
    u16* dwn;
    s32 mess;
    s32 setting;
    s16 dir;
    s32 i;
    s32 diff;

    mess = 0;
    sel = 0;
    for (i = 0; i < 4; i++) {
        if ((MBPlayerComCheck(i) == 0) && (GwPlayer[i].pad == arg0)) {
            sel = i;
            break;
        }
    }

    bg = MBSprGrpCreate(1, 0);
    data = DataRead(0x1300AA);
    bg->model[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(bg->spriteGroup, 0, bg->model[0], 0);
    HuSprPriSet(bg->spriteGroup, 0, 8);
    HuSprAttrSet(bg->spriteGroup, 0, 0x1000);
    HuSprPosSet(bg->spriteGroup, 0, 0xAA, 0x58);

    panel = MBSprGrpCreate(4, 0);
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            data = DataRead(0x13010F);
            panel->model[0] = HuSprAnimRead(data);
            DataClose(data);
        }
        HuSprGrpMemberSet(panel->spriteGroup, i, panel->model[0], 0);
        HuSprPriSet(panel->spriteGroup, i, 8);
        HuSprAttrSet(panel->spriteGroup, i, 0x1000);
        HuSprPosSet(panel->spriteGroup, i,
                            mbPausePanelXTbl[i],
                            mbPausePanelYTbl[i]);
        HuSprColorSet(panel->spriteGroup, i, 0, 0, 0xFF);
    }

    chr = MBSprGrpCreate(4, 0);
    for (i = 0; i < 4; i++) {
        data = DataRead(mbPauseCharSprTbl[MBPlayerGet(i)->chr]);
        chr->model[i] = HuSprAnimRead(data);
        HuSprGrpMemberSet(chr->spriteGroup, i, chr->model[i], 0);
        HuSprPriSet(chr->spriteGroup, i, 7);
        HuSprAttrSet(chr->spriteGroup, i, 0x1000);
        HuSprPosSet(chr->spriteGroup, i,
                            mbPausePanelXTbl[i],
                            mbPausePanelYTbl[i]);
        DataClose(data);
    }

    icon = MBSprGrpCreate(9, 0);
    for (i = 0; i < 9; i++) {
        data = DataRead(mbPausePadIconSprTbl[i]);
        icon->model[i] = HuSprAnimRead(data);
        DataClose(data);
    }
    for (i = 0; i < 4; i++) {
        if (MBPlayerComCheck(i) != 0) {
            HuSprGrpMemberSet(icon->spriteGroup, i,
                icon->model[mbPauseComIconTbl[GwPlayer[i].cpu_difficulty * 2 + 0]], 0);
            HuSprGrpMemberSet(icon->spriteGroup, i + 4,
                icon->model[mbPauseComIconTbl[GwPlayer[i].cpu_difficulty * 2 + 1]], 0);
            HuSprPosSet(icon->spriteGroup, i,
                mbPausePanelXTbl[i] + 0x12,
                mbPausePanelYTbl[i] - 0xA);
        } else {
            HuSprGrpMemberSet(icon->spriteGroup, i,
                icon->model[mbPausePadIconTbl[GwPlayer[i].pad * 2]], 0);
            HuSprGrpMemberSet(icon->spriteGroup, i + 4,
                icon->model[mbPausePadIconTbl[GwPlayer[i].pad * 2]], 0);
            HuSprPosSet(icon->spriteGroup, i,
                mbPausePanelXTbl[i] + 0x12,
                mbPausePanelYTbl[i]);
            HuSprDispOff(icon->spriteGroup, i + 4);
        }
        HuSprPriSet(icon->spriteGroup, i, 7);
        HuSprAttrSet(icon->spriteGroup, i, 0x01001000);
        HuSprPriSet(icon->spriteGroup, i + 4, 7);
        HuSprAttrSet(icon->spriteGroup, i + 4, 0x01001000);
        HuSprPosSet(icon->spriteGroup, i + 4,
            mbPausePanelXTbl[i] + 0x12,
            mbPausePanelYTbl[i] + 6);
    }

    cursor = MBSprGrpCreate(3, 0);
    data = DataRead(0x13009C);
    cursor->model[0] = HuSprAnimRead(data);
    HuSprGrpMemberSet(cursor->spriteGroup, 0, cursor->model[0], 0);
    HuSprAttrSet(cursor->spriteGroup, 0, 0x1808);
    HuSprPriSet(cursor->spriteGroup, 0, 6);
    DataClose(data);

    data = DataRead(0x1300A9);
    cursor->model[1] = HuSprAnimRead(data);
    HuSprGrpMemberSet(cursor->spriteGroup, 1, cursor->model[1], 0);
    HuSprAttrSet(cursor->spriteGroup, 1, 0x9808);
    HuSprPriSet(cursor->spriteGroup, 1, 6);
    HuSprColorSet(cursor->spriteGroup, 1, 0xFF, 0, 0);
    HuSprAttrSet(cursor->spriteGroup, 1, 1);
    DataClose(data);

    data = DataRead(0x1300A9);
    cursor->model[2] = HuSprAnimRead(data);
    HuSprGrpMemberSet(cursor->spriteGroup, 2, cursor->model[2], 0);
    HuSprAttrSet(cursor->spriteGroup, 2, 0x9808);
    HuSprPriSet(cursor->spriteGroup, 2, 6);
    HuSprColorSet(cursor->spriteGroup, 2, 0xFF, 0, 0);
    DataClose(data);

    MBPauseCursorPosSet(cursor, sel);
    MBPauseCursorBlinkSet(0);
    proc = omAddPrcObj(MBPauseCursorProc, 0x1005, 0, 0);
    proc->user_data = cursor;

    do {
        if (mess != 0x5112) {
            mess = 0x5112;
            MBPauseDlgMesSet(mbPauseGuide->amount, 0x5112);
        }
        HuPrcVSleep();

        dir = -1;
        if (ContBtnDown[arg0] & U_JPAD) dir = 0;
        if (ContBtnDown[arg0] & D_JPAD) dir = 1;
        if (ContBtnDown[arg0] & L_JPAD) dir = 2;
        if (ContBtnDown[arg0] & R_JPAD) dir = 3;

        if (dir != -1) {
            sel += mbPausePanelMoveTbl[sel][dir];
            MBPauseCursorPosSet(cursor, sel);
            HuAudFXPlay(1);
        } else if (HuPadBtnDown[arg0] & A_BUTTON) {
            HuAudFXPlay(2);
            player = MBPlayerGet(sel);
            MBPauseCursorBlinkSet(1);
            diff = player->cpu_difficulty;
            i = (MBPlayerComCheck(sel) != 0) ? 4 : -1;

            while (1) {
                HuPrcVSleep();
                if (mess != 0x5113) {
                    mess = 0x5113;
                    MBPauseDlgMesSet(mbPauseGuide->amount, 0x5113);
                }

                if (ContBtnDown[arg0] & L_JPAD) {
                    if ((i != 4) || (diff == 0)) {
                        i = MBPausePadNextGet(player, -1);
                        if (i == 4) {
                            diff = _CheckFlag(0x2D) ? 3 : 2;
                        }
                    } else {
                        diff--;
                    }
                    MBPlayerComLevelSet(sel, diff);
                    HuAudFXPlay(1);
                } else if (ContBtnDown[arg0] & R_JPAD) {
                    if (_CheckFlag(0x2D) != 0) {
                        if ((i != 4) || (diff == 3)) {
                            i = MBPausePadNextGet(player, 1);
                            diff = -(i != 4) & diff;
                        } else {
                            diff++;
                        }
                        
                    } else if ((i != 4) || (diff == 2)) {
                        i = MBPausePadNextGet(player, 1);
                        diff = -(i != 4) & diff;
                    } else {
                        diff++;
                    }
                    MBPlayerComLevelSet(sel, diff);
                    HuAudFXPlay(1);
                }

                if (i >= 0) {
                    MBPausePadSet(player, i);
                    if (MBPlayerComCheck(sel) != 0) {
                        HuSprGrpMemberSet(icon->spriteGroup, sel,
                            icon->model[mbPauseComIconTbl[GwPlayer[sel].cpu_difficulty * 2 + 0]], 0);
                        HuSprGrpMemberSet(icon->spriteGroup, sel + 4,
                            icon->model[mbPauseComIconTbl[GwPlayer[sel].cpu_difficulty * 2 + 1]], 0);
                        HuSprPosSet(icon->spriteGroup, sel,
                            mbPausePanelXTbl[sel] + 0x12,
                            mbPausePanelYTbl[sel] - 0xA);
                        HuSprDispOn(icon->spriteGroup, sel + 4);
                    } else {
                        HuSprGrpMemberSet(icon->spriteGroup, sel,
                            icon->model[mbPausePadIconTbl[GwPlayer[sel].pad * 2]], 0);
                        HuSprPosSet(icon->spriteGroup, sel,
                            mbPausePanelXTbl[sel] + 0x12,
                            mbPausePanelYTbl[sel]);
                        HuSprDispOff(icon->spriteGroup, sel + 4);
                    }
                }

                if (ContBtnDown[arg0] & A_BUTTON) {
                    HuAudFXPlay(2);
                    MBPlayerComLevelSet(sel, diff);
                    break;
                }
                if (ContBtnDown[arg0] & B_BUTTON) {
                    HuAudFXPlay(4);
                    break;
                }
            }

            MBPauseCursorBlinkSet(0);
            HuPrcVSleep();
        }
    } while (!(HuPadBtnDown[arg0] & B_BUTTON));

    HuAudFXPlay(4);
    omDelPrcObj(proc);
    MBSprGrpKill(cursor);
    MBSprGrpKill(icon);
    MBSprGrpKill(chr);
    MBSprGrpKill(panel);
    MBSprGrpKill(bg);
    return 4;
}

static s16 MBPauseModeExec(s16 arg0, s32 arg1) {
    switch (arg0) {
    case 1:
        return MBPauseMainScrExec(arg1);
    case 2:
        return MBPausePadCfgExec(arg1);
    case 4:
        return MBPauseOptionExec(arg1);
    case 9:
        return MBPauseQuitWinExec(arg1);
    default:
        return 0;
    }
}

static void MBPauseMain(void) {
    UnkBoard8* temp_s1;
    s16 var_s2;
    s16 temp_v0;
    s32 temp_s3;
    void* temp_v0_2;

    temp_s3 = (s32)HuPrcCurrentGet()->user_data;
    var_s2 = 1;
    temp_v0 = MBStatusHideCheck();
    
    if (temp_v0 != 0) {
        MBStatusHideAll();
    }
    
    HuPrcVSleep();
    Hu3DPauseF = 1;
    temp_s1 = MBSprGrpCreate(1, 0);
    temp_v0_2 = DataRead(0x13025D);
    temp_s1->model[0] = HuSprAnimRead(temp_v0_2);
    HuSprGrpMemberSet(temp_s1->spriteGroup, 0, temp_s1->model[0], 0U);
    HuSprPriSet(temp_s1->spriteGroup, 0, 9U);
    HuSprAttrSet(temp_s1->spriteGroup, 0, 0x1000);
    HuSprPosSet(temp_s1->spriteGroup, 0, 0xA0, 0x78);
    HuSprScaleSet(temp_s1->spriteGroup, 0, 40.0f, 30.0f);
    HuSprColorTPLvlSet(temp_s1->spriteGroup, 0, 0, 0, 0, 0xC0);
    DataClose(temp_v0_2);
    
    do {
        HuPrcVSleep();
        var_s2 = MBPauseModeExec(var_s2, temp_s3);
    } while (var_s2 != 0);
    
    if (mbPauseQuitF == 0) {
        Hu3DPauseF = 0;
    }
    
    MBSprGrpKill(temp_s1);
    
    if (temp_v0 != 0) {
        MBStatusShowAll();
    }
    
    omDelPrcObj(NULL);
}

void MBPauseCreate(s32 arg0) {
    Process* temp_s1_2;
    Process* temp_v0;
    s16 var_a0;
    s32 temp_s1;
    s32 temp_s2;
    s32 var_v0;
    s32 i;

    MBBackSprDispOff();
    winPauseF = 1;
    omAllPause();
    temp_s2 = _CheckFlag(0x20) != 0;
    
    for (i = 0; i < 4; i++) {
        if (CheckControllerRead(i) != 0) {
            ResetVibrator(i);
        }        
    }

    if (mbSubMusNo != -1) {
        msmMusSetVolume(mbSubMusNo, 0x60);
    } else {
        HuAudSeqVolSet(0x60);
    }
    
    Hu3DModelModeSet(HuSprBGHookMdl, 2);
    Hu3DModelCameraSet(HuSprBGHookMdl, HU3D_CAM0);
    mbPauseGuide = 0;
    mbPauseStat = 0;
    mbPauseQuitF = 0;
    temp_s1_2 = HuPrcCurrentGet();
    temp_v0 = omAddPrcObj(MBPauseMain, 0xEFFFU, 0x1000, 0);
    temp_v0->user_data = (void*)arg0;
    omPrcSetStatBit(temp_v0, OM_STAT_NOALLPAUSE);
    HuPrcChildLink(temp_s1_2, temp_v0);
    HuPrcChildWatch();
    Hu3DModelModeSet(HuSprBGHookMdl, 6);
    if (mbSubMusNo != -1) {
        msmMusSetVolume(mbSubMusNo, 0x7F);
    } else {
        HuAudSeqVolSet(0x7F);
    }
    if (((_CheckFlag(0x20) != 0) && (temp_s2 == 0)) || ((_CheckFlag(0x20) == 0) && (temp_s2 != 0))) {
        MBMgCallHisInit();
    }
    if (mbPauseQuitF != 0) {
        omOvlSeKeepF = 0;
        HuAudSeqFadeOut(0x5A);
        if (mbSubMusNo != -1) {
            msmMusFadeOut(mbSubMusNo, 0x5A);
            mbSubMusNo = -1;
            HuAudSeqStop();
        }
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x11);
        MBExit();
        MBBoardReturnOff();
        if (GwSystem.playMode & 4) {
            omOvlReturnEx(3);
        } else {
            omOvlReturnEx(1);
        }
        
        omOvlKill();
        HuPrcVSleep();
    }
    omAllUPause();
    winPauseF = 0;
    MBBackSprDispOn();
}
