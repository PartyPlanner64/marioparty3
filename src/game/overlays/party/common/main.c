#include "common_board.h"
#include "game/object.h"
#include "game/board.h"
#include "window.h"
#include "player.h"
#include "back.h"
#include "move.h"
#include "mapfull.h"
#include "model.h"
#include "ksuit.h"
#include "sprgrp.h"
#include "mgcall.h"
#include "coinchange.h"
#include "item.h"
#include "status.h"
#include "sai.h"
#include "scissor.h"
#include "main.h"
#include "vec.h"
#include "pause.h"
#include "vibrate.h"
#include "scroll.h"
#include "helpwin.h"
#include "itemmasu.h"
#include "com.h"

enum DIFFICULTIES {
    EASY = 0,
    NORMAL = 1,
    HARD = 2,
    VERY_HARD = 3
};

extern s16 mbWipeType;
extern s32 mbCameraZoomInstantF;
extern s16 mbMgHis;
extern s16 kakusiMasuCoinForceF;
extern s32 mbBoardStartResult;
extern s16 kakusiMasuStarHisIdx;
extern s16 kakusiMasuCoinHisIdx;
extern s16 kakusiMasuItemForceF;
extern s16 kakusiMasuItemHisIdx;
extern u8 mgPlayerTeam[];
extern s16 mbSeqPlayF;
extern s32 mbExitOvlNo;
extern s16 mbExitOvlEvent;
extern s16 HuAudSubMusNo;
extern s16 mbCameraFocusMode;
extern Vec mbCameraFocusStaticPos;
extern Vec *mbCameraFocusVec;
extern Vec mbPlayerFixPosTbl[];
extern Object *mbBattleKuriboMdl;
extern Object *mbBattleKuriboUpperMdl;
extern omObjData *mbBattleKuriboObj;
extern s16 mbWipeTypeNext;
extern f32 mbCameraZoom;
extern s16 mbSeqPlayF;
extern s16 kakusiMasuItemForceF;
extern s16 kakusiMasuStarForceF;
extern s16 kakusiMasuItemHisIdx;
extern s16 kakusiMasuStarHisIdx;
extern s16 kakusiMasuCoinHisIdx;
extern u16 kakusiMasuCoinCnt;
extern u16 kakusiMasuStarCnt;
extern u16 kakusiMasuItemCnt;
extern s16 kakusiMasuItemHis[10];
extern s16 kakusiMasuCoinHis[10];
extern s16 kakusiMasuStarHis[10];
extern u16 mbBattleCoinMaxTbl[];
extern u16 mbBattleCoinTbl[];
extern s16 mgBattleCoinPot;
extern s16 mbExitFlag;
extern s16 mbExitMusFadeF;

static void MBSaveInit(void);

s32 mbBoardOvlTbl[] = {
    ChillyWaters,
    w02,
    w03,
    w04,
    w05,
    w06,
    w10,
    ChillyWaters,
    selmenu2
};

void (*mbExitHook)(void) = NULL;
void (*mbKinokoEffKillHook)(void) = NULL;
void (*mbHatenaFunc)(void) = NULL;

f32 mbPlayerFix4PosTbl[][2] = {
    { -7.0f, -7.0f },
    { 7.0f, -7.0f },
    { 7.0f, 7.0f },
    { -7.0f, 7.0f }
};

f32 mbPlayerFix3PosTbl[][2] = {
    { -7.0f, 4.0f },
    { 0.0f, -8.0f },
    { 7.0f, 4.0f },
};

f32 mbPlayerFix2PosTbl[][2] = {
    { -5.0f, 0.0f },
    { 5.0f, 0.0f },
};

f32 mbPlayerFixCur4PosTbl[][2] = {
    { -10.0f, -10.0f },
    { 10.0f, -10.0f },
    { 10.0f, 10.0f },
    { -10.0f, 10.0f },
};

f32 mbPlayerFixCur3PosTbl[][2] = {
    { -10.0f, 0.0f },
    { 0.0f, -10.0f },
    { 10.0f, 0.0f },
};

f32 mbPlayerFixCur2PosTbl[][2] = {
    { -7.0f, -7.0f },
    { 7.0f, -7.0f }
};

u8 mbGambleMgTbl[] = {
    MINIGAME_ID(game_guys_roulette),
    MINIGAME_ID(game_guys_lucky_7),
    MINIGAME_ID(game_guys_magic_boxes),
    MINIGAME_ID(game_guys_sweet_surprise)
};

u8 mbGambleMgRateTbl[] = {
    5,  // 5% game_guys_roulette
    30, // 25% game_guys_lucky_7
    65, // 35% game_guys_magic_boxes
    100 // 35% game_guys_sweet_surprise
};

// there's probably a better way to do this
#define GAME_GUY_RANDOM_MAX 1000

typedef struct CPU_GAMEGUY_STATS {
    u16 multiplier;
    u16 weight;
} CPU_GAMEGUY_STATS;

CPU_GAMEGUY_STATS mbGambleComRateTbl[] = {
    { 0, 500 },  // 0x multiplier - rolls 1-500 (50.0%)
    { 2, 870 },  // 2x multiplier - rolls 501-870 (37.0%)
    { 4, 950 },  // 4x multiplier - rolls 871-950 (8.0%)
    { 8, 985 },  // 8x multiplier - rolls 951-985 (3.5%)
    { 16, 995 }, // 16x multiplier - rolls 986-995 (1.0%)
    { 32, 999 }, // 32x multiplier - rolls 996-999 (0.4%)
    { 64, 1000 } // 64x multiplier - roll 1000 (0.1%)
};

// CPU enter shop probabilites per difficulty
u16 mbShopComEnterRateTbl[] = {
    [EASY] 75,
    [NORMAL] 85,
    [HARD] 90,
    [VERY_HARD] 95
};

u16 mbShopItemTbl[][8] = {
    [SHOP_TOAD] {
        ITEM_MUSHROOM,
            ITEM_SKELETON_KEY,
            ITEM_CELLULAR_SHOPPER,
            ITEM_WARP_BLOCK,
            ITEM_DUEL_GLOVE,
            ITEM_GOLDEN_MUSHROOM,
            ITEM_BOO_REPELLENT,
            ITEM_MAGIC_LAMP
    },

    [SHOP_BABY_BOWSER] {
        ITEM_SKELETON_KEY,
            ITEM_POISON_MUSHROOM,
            ITEM_REVERSE_MUSHROOM,
            ITEM_PLUNDER_CHEST,
            ITEM_BOWSER_PHONE,
            ITEM_LUCKY_LAMP,
            ITEM_BOWSER_SUIT,
            ITEM_BOO_BELL
    },
};

// shop messages
s32 mbShopMesTbl[][8] = {
    [SHOP_TOAD] {
        0x00003C23,
            0x00003C24,
            0x00003C27,
            0x00003C28,
            0x00003C2B,
            0x00003C2D,
            0x00003C2F,
            0x00003C31
    },
    [SHOP_BABY_BOWSER] {
        0x00003C24,
            0x00003C25,
            0x00003C26,
            0x00003C29,
            0x00003C2A,
            0x00003C2C,
            0x00003C2E,
            0x00003C30
    },
};

u16 mbShopComItemRateTbl[][5][8] = {
    {
        { 30, 50, 60, 70, 70, 90, 90, 100 },
        { 15, 30, 40, 50, 50, 85, 100, 100 },
        { 15, 30, 45, 60, 60, 100, 100, 100 },
        { 10, 22, 32, 32, 47, 67, 85, 100 },
        { 10, 20, 20, 20, 37, 57, 70, 100 },
    },
    {
        { 30, 50, 60, 70, 70, 70, 90, 100 },
        { 15, 30, 40, 50, 50, 80, 100, 100 },
        { 15, 30, 50, 60, 80, 90, 100, 100 },
        { 10, 10, 30, 40, 55, 75, 85, 100 },
        { 10, 10, 25, 40, 50, 70, 70, 100 },
    },
};

u16 mbShopComRankTbl[][4][3] = {
    {
        { 0x0000, 0x0001, 0x0002 },
        { 0x0000, 0x0000, 0x0003 },
        { 0x0000, 0x0000, 0x0004 },
        { 0x0000, 0x0000, 0x0004 },
    },
    {
        { 0x0000, 0x0001, 0x0002 },
        { 0x0000, 0x0000, 0x0003 },
        { 0x0000, 0x0000, 0x0004 },
        { 0x0000, 0x0000, 0x0004 },
    },
};

f32 mbJumpAngleTbl[][2] = {
    { 0.0f, 0.0f },
    { 200.0f, 250.0f },
    { 110.0f, 250.0f },
    { 70.0f, 290.0f },
    { 0.0f, 360.0f },
};

f32 mbJumpNextAngleTbl[][2] = {
    { 0.0f, 0.0f },
    { 20.0f, 70.0f },
    { -70.0f, 70.0f },
    { 70.0f, 290.0f },
    { 0.0f, 360.0f },
};

s8 mbKettouComWagerTbl[][4][2] = {
    {
        { -1, 1 },
        { 3, 2 },
        { 3, 3 },
        { 3, 3 },
    },
    {
        { 0, 1 },
        { -1, 1 },
        { 1, 2 },
        { 1, 2 },
    },
    {
        { 0, 1 },
        { 0, 1 },
        { -1, 1 },
        { 1, 2 },
    },
    {
        { 0, 0 },
        { 0, 1 },
        { 0, 1 },
        { -1, -1 },
    },
};

s16 mbKettouComRateTbl[][3] = {
    { 45, 90, 100 },
    { 70, 95, 100 },
    { 85, 95, 100 }
};

u16 mbBattleCoinMaxTbl[] = { 20, 30, 50 };

u8 mbTurnTierTbl[9][3] = {
    { 4, 7, 11 },   // 10 turns
    { 6, 11, 16 },  // 15 turns
    { 6, 16, 21 },  // 20 turns
    { 9, 17, 26 },  // 25 turns
    { 11, 21, 31 }, // 30 turns
    { 11, 21, 36 }, // 35 turns
    { 14, 27, 41 }, // 40 turns
    { 16, 31, 46 }, // 45 turns
    { 16, 36, 51 }, // 50 turns
};

// outcomes for how many coins are wagered for battle minigames
// If it's early game, a 30% chance is rolled. If successful, the battle minigame will be for 0 coins. Otherwise, run the table below
// order is probability of: 0 coins, 10 coins, 20 coins, 30 coins, 50 coins
// 1st place
u8 mbBattleCoinRank1Tbl[3][5] = {
    { 10, 95, 100, 0, 0 }, // early game
    { 10, 85, 100, 0, 0 }, // mid game
    { 10, 75, 100, 0, 0 }, // late game
};

// 2nd place
u8 mbBattleCoinRank2Tbl[3][5] = {
    { 5, 75, 95, 100, 0 }, // early game
    { 5, 65, 90, 100, 0 }, // mid game
    { 5, 55, 85, 100, 0 }, // late game
};

// 3rd place
u8 mbBattleCoinRank3Tbl[3][5] = {
    { 5, 65, 85, 95, 100 }, // early game
    { 5, 50, 80, 95, 100 }, // mid game
    { 5, 40, 70, 90, 100 }, // late game
};

// 4th place
u8 mbBattleCoinRank4Tbl[3][5] = {
    { 5, 50, 80, 95, 100 }, // early game
    { 5, 35, 70, 90, 100 }, // mid game
    { 5, 25, 60, 85, 100 }, // late game
};

// battle coin amounts (map index -> coin amount)
u16 mbBattleCoinTbl[] = {
    0, 10, 20, 30, 50
};

u8 (*mbBattleCoinRateTbl[])[3][5] = {
    &mbBattleCoinRank1Tbl,
    &mbBattleCoinRank2Tbl,
    &mbBattleCoinRank3Tbl,
    &mbBattleCoinRank4Tbl
};

Unk3 *mbTurnHelpWin0 = NULL;
Unk3 *mbTurnHelpWin1 = NULL;
Unk3 *mbTurnHelpWin2 = NULL;
Unk3 *mbTurnHelpWin3 = NULL;

u8 mbKakusiItemRateTbl[][2] = {
    { ITEM_SKELETON_KEY, 72 },
    { ITEM_MAGIC_LAMP, 80 },
    { ITEM_KOOPA_KARD, 85 },
    { ITEM_WACKY_WATCH, 90 },
    { ITEM_LUCKY_CHARM, 95 },
    { ITEM_BARTER_BOX, 100 },
};

// unused? padding?
u8 mbMainPad[2] = { 0, 0 };

u8 mbVibrateWaitTbl[] = {
    5, 10, 10, 20, 20, 30
};

void MBOvlCall(s32 id, s16 event, u16 stat) {
    omOvlHisData *overlay = &mbovlhis[mbovlhisidx++];

    if (id != -2) {
        if (id == -1) {
            id = omovlhis[omovlhisidx].overlayID;
            overlay->overlayID = id;
        } else {
            overlay->overlayID = id;
        }
    } else {
        id = mbBoardOvlTbl[GwSystem.current_board_index];
        overlay->overlayID = id;
    }

    overlay->event = event;
    overlay->stat = stat;

    if (mbovlhisidx >= ARRAY_COUNT(mbovlhis)) {
        mbovlhisidx = ARRAY_COUNT(mbovlhis) - 1;
    }
}

void MBOvlCallInit(void) {
    ditherBak.unk_02 = 1;
    mbovlhisidx = 0;

    if (GWBoardFlagCheck(1) == 0) {
        if ((GwSystem.current_board_index != 6) && (MBOvlCall(-2, 4, OM_OVL_STAT_BOARD | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1), (GwSystem.current_board_index != 6))) {
            MBOvlCall(0x53, 0, OM_OVL_STAT_BOARD | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1);
        } else {
            MBOvlCall(0x54, 0, OM_OVL_STAT_BOARD | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1);
        }

        MBOvlCall(-2, 1, OM_OVL_STAT_BOARD | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1);
    }

    MBSaveInit();
    MBMesSpeedSet(GwSystem.message_speed);
    _ClearFlag(0xC);
    mbEndingF = 0;
}

void MBOvlCallExec(void) {
    omOvlHisData *overlay;

    mbOvlCallF = 1;
    if (mbovlhisidx != 0) {
        mbovlhisidx--;
        overlay = &mbovlhis[mbovlhisidx];
        omOvlCallEx(overlay->overlayID, overlay->event, overlay->stat);
        return;
    }
    if (ditherBak.unk_02 != 0) {
        mbOvlCallF = 0;
        omOvlCallEx(mbBoardOvlTbl[GwSystem.current_board_index], 2, OM_OVL_STAT_BOARD | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1);
        return;
    }
    if (mbEndingF != 0) {
        _SetFlag(0xC);
    } else {
        _ClearFlag(0xC);
    }
    omOvlReturnEx(1);
}

void MBBoardReturnOff(void) {
    ditherBak.unk_02 = 0;
}

s16 MBOvlCallCheck(void) {
    return mbOvlCallF;
}

static void MBOvlCallEventReturn(s16 arg0) {
    s16 temp_v0 = mbovlhisidx;

    mbovlhis[mbovlhisidx].event = arg0;
    mbovlhisidx = temp_v0 + 1;
    if (mbovlhisidx >= ARRAY_COUNT(mbovlhis)) {
        mbovlhisidx = ARRAY_COUNT(mbovlhis) - 1;
    }
    MBOvlCall(-2, 3, OM_OVL_STAT_BOARD | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1);
    omOvlReturnEx(1);
}

void MBSaiCurseFlagSet(void) {
    if (GWBoardFlagCheck(0x17)) {
        GWBoardFlagSet(0x10);
    }
}

s32 MBGameModeGet(void) {
    return mbGameMode;
}

void MBPlayerTauntProc(void) {
    s32 *temp_s0 = HuPrcCurrentGet()->user_data;

    while (1) {
        if (
            (MBPlayerComCheck(temp_s0[0]) == 0) &&
            (mbTauntOffF == 0) &&
            ((GwSystem.current_player_index != temp_s0[0]) || (mbTurnUnkF == 0)) &&
            (ContBtnDown[GwPlayer[temp_s0[0]].pad] & L_TRIG)) {
            PlayerFXPlay(0x2BD, temp_s0[0]);
        }
        HuPrcVSleep();
    }
}

void MBObjectSetup(s32 arg0, s16 arg1, s32 arg2, s32 unused) {
    Process *temp_v0_2;
    UnkOvl81_1 *temp_v0_3;
    u8 playerIndex;
    Object *temp_v0;
    s32 i;
    GW_SYSTEM *system;

    MBBackSprInit();
    MBBackArcInit((u32)hvq_data_ROM_START);

    if (arg0 >= 0) {
        MBBackLoad(arg0);
    }

    MBMasuInit();
    if (arg1 >= 0) {
        MBMasuCreate(0x13, (s32)arg1);
    }

    MBMapFullInit(arg2);
    MBModelInit();
    MBPlayerMotInit();
    MBKSuitInit();
    MBPlayerModelCreateDef(0);
    MBPlayerModelCreateDef(1);
    MBPlayerModelCreateDef(2);
    MBPlayerModelCreateDef(3);

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        MBModelTempAllocFree(MBPlayerGet(i)->player_obj);
        temp_v0 = MBPlayerGet(i)->player_obj;
        temp_v0->flags |= 2;
        MBModelDispOn(MBPlayerGet(i)->player_obj);
    }

    system = &GwSystem;
    playerIndex = system->current_player_index;
    if ((playerIndex < 4) && (GwPlayer[system->current_player_index].itemTurn != 0)) {
        MBKSuitCreate();
        MBModelDispOff(GwPlayer[system->current_player_index].player_obj);
    }

    Hu3DMotionReset(MBPlayerGet(0)->player_obj->omObj1->model[0]);
    Hu3DMotionReset(MBPlayerGet(1)->player_obj->omObj1->model[0]);
    Hu3DMotionReset(MBPlayerGet(2)->player_obj->omObj1->model[0]);
    Hu3DMotionReset(MBPlayerGet(3)->player_obj->omObj1->model[0]);
    MBSprGrpInit();
    MBMgCallInit();
    MBCoinChangeInit();
    MBTelopInit();
    MBStatusCreate();
    MBSaiInit();
    HuWinInit();
    MBDlgWinParamReset();
    mbExitFlag = -1;
    mbWipeType = WIPE_TYPE_NORMAL;
    mbExitMusFadeF = 0;
    MBScissorFullSet();
    mbExitHook = NULL;
    mbKinokoEffKillHook = NULL;
    mbHatenaFunc = NULL;
    HuAudFadeObjCreate();

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        temp_v0_2 = omAddPrcObj(MBPlayerTauntProc, 0, 0, 0x40);
        temp_v0_3 = HuMemMemoryAlloc(temp_v0_2->heap, sizeof(UnkOvl81_1));
        temp_v0_2->user_data = temp_v0_3;
        temp_v0_3->unk_00 = i;
        omPrcSetStatBit(temp_v0_2, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    }
}

void MBExit(void) {
    MBSaiClose();
    MBStatusKill();
    MBTelopClose();
    MBCoinChangeClose();
    MBMgCallClose();
    MBSprGrpClose();
    HuWinAllKill();
    MBKSuitClose();
    MBPlayerClose();
    MBModelClose();
    MBMapFullClose();
    MBMasuKill();
    MBMasuClose();
    MBBackKill();
    MBBackClose();
    MBBackReset();
    MBBackSprKillAll();
    if (mbExitHook != NULL) {
        mbExitHook();
    }
    if (mbKinokoEffKillHook != NULL) {
        mbKinokoEffKillHook();
    }
    MBTurnHelpKill();
}

void MBHatenaFuncSet(void (*arg0)(void)) {
    mbHatenaFunc = arg0;
}

void MBExitHookSet(void (*arg0)(void)) {
    mbExitHook = arg0;
}

void MBKinokoEffKillHookSet(void (*arg0)()) {
    mbKinokoEffKillHook = arg0;
}

void MBBoardParamSet(s32 arg0) {
    mbUnkParam = arg0;
}

s16 MBBoardParamGet(void) {
    return mbUnkParam;
}

static void MBSaveInit(void) {
    GW_PLAYER *player;
    s32 i, j;
    GW_SYSTEM *system = &GwSystem;
    GW_COMMON *common = &GwCommon;

    mbGameMode = 0;
    mbWalkNum = 0;
    kakusiMasuItemCnt = 0;
    kakusiMasuStarCnt = 0;
    kakusiMasuCoinCnt = 0;
    kakusiMasuItem = -1;
    kakusiMasuStar = -1;
    kakusiMasuCoin = -1;
    kakusiMasuItemForceF = 0;
    kakusiMasuStarForceF = 0;
    kakusiMasuCoinForceF = 0;

    for (i = 0; i < 10; i++) {
        kakusiMasuCoinHis[i] =
            kakusiMasuStarHis[i] =
                kakusiMasuItemHis[i] = -1;
    }

    kakusiMasuItemHisIdx = 0;
    kakusiMasuStarHisIdx = 0;
    kakusiMasuCoinHisIdx = 0;
    mbCameraZoom = 1.0f;

    MBMgCallHisInit();
    MBSaiValueClear(); // clear lucky 7 flag for buffing golden mushrooms

    mbWipeTypeNext = -1;
    mbSubMusNo = -1;
    mbSeqPlayF = 0;
    mbTurnUnkF = 1;
    mbTauntOffF = 0;

    MBPlayerInit(0);
    MBPlayerInit(1);
    MBPlayerInit(2);
    MBPlayerInit(3);

    if (((common->unk9E == 3) | (common->unk9E == 1)) != 0) {
        common->unk9E = 2;
    }
    if (common->unk9F == 3) {
        common->unk9F = 0;
    }
    if (common->unkA0 == 3) {
        common->unkA0 = 1;
    }
    if (common->unkA1 == 3) {
        common->unkA1 = 1;
    }
    if (common->unkA2 == 3) {
        common->unkA2 = 0;
    }

    system->save_mode = common->unk9E;
    system->show_minigame_explanations = common->unk9F;
    system->message_speed = common->unkA0;
    system->walk_speed = common->unkA1;
    system->show_com_minigames = common->unkA2;

    if (GWBoardFlagCheck(1) == 0) {
        system->current_star_spawn = 0;
        system->current_turn = 1;
        system->current_player_index = 0;
        system->minigame_index = 0;

        for (i = 0; i < ARRAY_COUNT(GwPlayer); i++) { // clear all 5 "players" (bowser bomb remnants)
            player = MBPlayerGet(i);
            player->coin = 0;
            player->gamePrize = 0;
            player->coinPrize = 0;
            player->stats.prize.hatenaPrize = 0;
            player->stats.prize.redPrize = 0;
            player->stats.prize.bluePrize = 0;
            player->stats.prize.eventPrize = 0;
            player->stats.prize.gamblePrize = 0;
            player->stats.prize.kupaPrize = 0;
            player->stats.prize.battlePrize = 0;
            player->stats.prize.itemPrize = 0;
            player->stats.prize.bankPrize = 0;
            player->rev = 0;
            for (j = 0; j < ARRAY_COUNT(player->itemNo); j++) {
                player->itemNo[j] = -1;
            }
            player->itemTurn = 0;
        }

        // TODO: 16?
        for (i = 0; i < 16; i++) {
            GwSystem.boardData.halfWordBytes[i] = 0;
        }

        GWBoardFlagClear(6);
        GWBoardFlagClear(7);
        GWBoardFlagClear(8);
        GWBoardFlagClear(9);
        GWBoardFlagClear(10);
        GWBoardFlagClear(11);
        GWBoardFlagClear(12);
        GWBoardFlagClear(13);
        GWBoardFlagClear(18);
        GWBoardFlagClear(19);
        GWBoardFlagClear(20);
        GWBoardFlagClear(21);
        GWBoardFlagClear(22);
        GWBoardFlagClear(23);
        GWBoardFlagClear(2);
        GWBoardFlagClear(3);
        GWBoardFlagClear(4);
        GWBoardFlagClear(14);
        GWBoardFlagClear(1);
        GWBoardFlagClear(17);
        GWBoardFlagClear(16);

        if (_CheckFlag(0x1B) != 0) {
            GWBoardFlagSet(0xF);
        } else {
            GWBoardFlagClear(0xF);
        }

        if (GwSystem.playMode & 4) {
            if (_CheckFlag(0x28) != 0) {
                GWBoardFlagSet(0);
                return;
            }
            GWBoardFlagClear(0);
            return;
        }

        if (_CheckFlag(0x16) != 0) {
            GWBoardFlagSet(0);
            return;
        }

        GWBoardFlagClear(0);
    }
}

void MBCameraFocusModeSet(s16 arg0) {
    mbCameraFocusMode = arg0;
}

s16 MBCameraFocusModeGet(void) {
    return mbCameraFocusMode;
}

void MBCameraFocusStaticPosSet(Vec *arg0) {
    mbCameraFocusStaticPos = *arg0;
}

void MBCameraFocusVecSet(Vec *arg0) {
    mbCameraFocusVec = arg0;
}

static void MBCameraFocusProc(void) {
    Vec2f sp10;

    while (1) {
        switch (mbCameraFocusMode) {
            case 1:
                MBCameraPos3DSet(&GwPlayer[GwSystem.current_player_index].player_obj->coords);
                break;
            case 2:
                MBCameraPos3DSet(&mbCameraFocusStaticPos);
                break;
            case 4:
                MBCameraPos3DSet(mbCameraFocusVec);
                break;
            case 3:
                MBCameraPos2DGet(&sp10);
                MBCameraPos2DSet(&sp10);
                break;
        }
        HuPrcVSleep();
    }
}

static void MBNextPlayerTurn(void) {
    GW_SYSTEM *system = &GwSystem;

    system->current_player_index++;

    if (system->current_player_index >= MB_MAX_PLAYERS) {
        system->current_player_index = 0;
        if (mbTurnOnF == 0) {
            if (GwSystem.wackyWatchUsedState != WATCH_USED) {
                system->current_turn++;
            } else {
                GwSystem.wackyWatchUsedState = WATCH_SPENT;
                system->current_turn = system->total_turns - 4;
            }
            if (system->current_turn >= 99) {
                system->current_turn = 99;
            }
        }
    }
}

static s32 MBLast5Check(void) {
    GW_SYSTEM *system = &GwSystem;

    // TODO: is there another way to write this?
    if ((system->current_player_index == MB_MAX_PLAYERS - 1) || (system->current_player_index < 0) || (system->current_player_index >= MB_MAX_PLAYERS)) {
        if (system->total_turns >= 0) {
            if (system->current_turn == (system->total_turns - 5)) {
                return 1;
            }
        }

        if (GwSystem.wackyWatchUsedState == WATCH_USED) {
            return 1;
        }
    }

    return 0;
}

static void MBExitProc(void) {
    s32 i;

    do {
        HuPrcVSleep();
    } while (WipeStatGet() != 0);

    while (1) {
        HuPrcVSleep();
        if (omSysExitReq == 0 && mbExitFlag < 0) {
            continue;
        }

        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }

        if (mbExitMusFadeF != 0) {
            HuAudSeqFadeOut(0x5A);
            if (mbSubMusNo != -1) {
                msmMusFadeOut(mbSubMusNo, 0x5A);
                mbSubMusNo = -1;
                HuAudSeqStop();
            }
            if (mbSeqPlayF != 0) {
                HuAudSeqStop();
                mbSeqPlayF = 0;
            }
        }

        WipeCreateOut(mbWipeType, 0x10);
        HuPrcSleep(0x11);
        MBExit();

        if (mbExitFlag & 0x20) {
            mbEndingF = 1;
            if (GwSystem.current_board_index == WALUIGIS_ISLAND) {
                _CheckFlag(9);
            }
            MBOvlCall(0x4F, 0, OM_OVL_STAT_DUEL | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1);
            MBBoardReturnOff();
        }

        if (mbExitFlag & 1) {
            if (MBLast5Check() != 0) {
                MBOvlCall(0x51, 0, OM_OVL_STAT_BOARD | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1);
            }
            MBNextPlayerTurn();
        }

        if (mbExitFlag & 2) {
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                if (mbStatusData[i].spaceType == SPACE_BLUE) {
                    mgPlayerTeam[i] = 0;
                } else {
                    mgPlayerTeam[i] = 1;
                }
            }
            MBOvlCall(0x70, 0, OM_OVL_STAT_BOARD | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1);
        }

        if (mbExitFlag & 8) {
            MBOvlCall(mbExitOvlNo, mbExitOvlEvent, OM_OVL_STAT_BOARD | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1);
        }

        GWBoardFlagClear(5);
        omOvlReturnEx(1);
        omOvlKill();
        HuPrcVSleep();
    }
}

static void MBMasuPassSePlay(s16 arg0) {
    switch (--arg0) {
        case 13:
            if (GwSystem.current_player_index != MB_MAX_PLAYERS) {
                HuAudFXPlay(0x123);
                return;
            }
        case 0:
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
        case 8:
        case 11:
        case 14:
            HuAudFXPlay(0x101);
            break;
    }
}

static void MBMasuLandSePlay(s16 arg0) {
    switch (--arg0) {
        case 3:
        case 5:
            HuAudFXPlay(0x108);
            break;
        case 0:
            HuAudFXPlay(0x121);
            break;
        case 1:
            HuAudFXPlay(0x122);
            break;
        case 11:
            HuAudFXPlay(0x124);
            break;
        case 4:
            HuAudFXPlay(0x12F);
            break;
        case 8:
        case 14:
            HuAudFXPlay(0x12E);
            break;
        case 6:
            HuAudFXPlay(0x130);
            break;
        case 13:
            HuAudFXPlay(0x123);
            break;
    }
}

void MBPlayerPosFixSet(s32 playerNo, s32 arg1) {
    GW_PLAYER *player;
    GW_PLAYER *playerCur;
    SpaceData *space;
    s32 var_s1;
    s32 var_s4;
    s32 playersShareSpace;
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    player = MBPlayerGet(playerNo);
    space = MBMasuGet(MBMasuLinkMasuIdGet(player->clink, player->cidx));
    if (system->current_player_index == playerNo) {
        HuVecCopy3F(&player->player_obj->coords, &space->coords);
        return;
    }

    playersShareSpace = 0;
    playerCur = MBPlayerGet(system->current_player_index);
    var_s4 = 0;

    if (player->clink == playerCur->clink) {
        playersShareSpace = player->cidx == playerCur->cidx;
    }

    var_s1 = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if ((playerNo != i) && (i != system->current_player_index)) {
            GW_PLAYER *curPlayer = MBPlayerGet(i);
            if ((player->clink == curPlayer->clink) && (player->cidx == curPlayer->cidx)) {
                var_s1 += 1;
                var_s4 += i < playerNo;
            }
        }
    }

    if (playersShareSpace == 1) {
        if (var_s1 == 2) {
            HuVecCopyXYZ(&mbPlayerFixPosTbl[playerNo], space->coords.x + mbPlayerFixCur3PosTbl[var_s4][0], space->coords.y, space->coords.z + mbPlayerFixCur3PosTbl[var_s4][1]);
        } else if (var_s1 == 3) {
            HuVecCopyXYZ(&mbPlayerFixPosTbl[playerNo], space->coords.x + mbPlayerFixCur4PosTbl[var_s4][0], space->coords.y, space->coords.z + mbPlayerFixCur4PosTbl[var_s4][1]);
        } else {
            HuVecCopyXYZ(&mbPlayerFixPosTbl[playerNo], space->coords.x + mbPlayerFixCur2PosTbl[var_s4][0], space->coords.y, space->coords.z + mbPlayerFixCur2PosTbl[var_s4][1]);
        }
    } else {
        if (var_s1 == 0) {
            HuVecCopy3F(&mbPlayerFixPosTbl[playerNo], &space->coords);
        } else if (var_s1 == 2) {
            HuVecCopyXYZ(&mbPlayerFixPosTbl[playerNo], space->coords.x + mbPlayerFix3PosTbl[var_s4][0], space->coords.y, space->coords.z + mbPlayerFix3PosTbl[var_s4][1]);
        } else if (var_s1 == 3) {
            HuVecCopyXYZ(&mbPlayerFixPosTbl[playerNo], space->coords.x + mbPlayerFix4PosTbl[var_s4][0], space->coords.y, space->coords.z + mbPlayerFix4PosTbl[var_s4][1]);
        } else {
            HuVecCopyXYZ(&mbPlayerFixPosTbl[playerNo], space->coords.x + mbPlayerFix2PosTbl[var_s4][0], space->coords.y, space->coords.z + mbPlayerFix2PosTbl[var_s4][1]);
        }
    }

    if (arg1 < 2) {
        HuVecCopy3F(&player->player_obj->coords, &mbPlayerFixPosTbl[playerNo]);
        return;
    }
    MBPlayerPosMoveCreate(&player->player_obj->coords, &mbPlayerFixPosTbl[playerNo], &player->player_obj->coords, arg1);
}

// if player should jump to next space
s32 MBPlayerJumpCheck(s32 arg0) {
    Vec sp10;
    GW_PLAYER *curPlayer;
    GW_PLAYER *player;
    f32 var_f4;
    SpaceData *space;
    SpaceData *nextSpace;
    s32 var_s2;
    s32 var_s4;
    s32 i;
    Vec *temp;

    curPlayer = MBPlayerGet(arg0);
    var_s2 = 0;
    var_s4 = 0;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == arg0) {
            continue;
        }
        player = MBPlayerGet(i);
        if (curPlayer->clink == player->clink) {
            var_s4 += curPlayer->cidx == player->cidx;
        }
        if (curPlayer->nlink == player->clink) {
            var_s2 += curPlayer->nidx == player->cidx;
        }
    }

    space = MBMasuGet(MBMasuLinkMasuIdGet(curPlayer->clink, curPlayer->cidx));
    HuVecSubtract(&sp10, &MBMasuGet(MBMasuLinkMasuIdGet(curPlayer->nlink, curPlayer->nidx))->coords, &space->coords);
    var_f4 = MBVecAngleGet(&sp10);
    if ((var_s4 == 0) || (!(mbJumpAngleTbl[var_s4][0] < var_f4)) || (!(var_f4 <= mbJumpAngleTbl[var_s4][1]))) {
        if (var_s2 != 0) {
            if (mbJumpNextAngleTbl[var_s2][0] < 0.0f) {
                var_f4 -= 360.0f;
            }
            if (!(mbJumpNextAngleTbl[var_s2][0] < var_f4) || (!(var_f4 <= mbJumpNextAngleTbl[var_s2][1]))) {
                return 0;
            } else {
                return 1;
            }
        } else {
            return 0;
        }
    } else {
        return 1;
    }
}

static void MBSubMusStopProc(void) {
    HuPrcSleep(30);
    msmMusStop(HuAudSubMusNo);
    mbSeqPlayF = 0;
    omDelPrcObj(NULL);
}

static void MBBattleKuriboObjMain(omObjData *arg0) {
    mbBattleKuriboMdl->coords.y = sindf(arg0->rot.x) * 3.0f;
    mbBattleKuriboUpperMdl->coords.y = sindf(arg0->rot.x) * 3.0f;
    arg0->rot.x += 10.0f;
}

// related to how CPUs decide who to duel?
static s32 MBKettouComTargetGet(void) {
    s32 i;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 sp10[MB_MAX_PLAYERS];
    GW_SYSTEM *system = &GwSystem;

    for (i = 0, var_s2 = 99; i < MB_MAX_PLAYERS; i++) {
        if ((i != system->current_player_index) && ((GwSystem.unk_58 >> i) & 1) && (MBPlayerRankCalc(i) < var_s2) && GwPlayer[i].coin != 0) {
            var_s2 = MBPlayerRankCalc(i);
        }
    }

    var_s1 = 0;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if ((i != system->current_player_index) && ((GwSystem.unk_58 >> i) & 1) && (MBPlayerRankCalc(i) == var_s2)) {
            sp10[var_s1] = i;
            var_s1 += 1;
        }
    }

    if (MBPlayerGet(CUR_PLAYER)->coin >= 20) {
        if (MBPlayerGet(sp10[0])->coin < 20) {
            for (i = 0, var_s2 = 99, var_s3 = 0; i < MB_MAX_PLAYERS; i++) {
                if ((i != system->current_player_index) && (MBPlayerGet(i)->coin >= 20)) {
                    var_s3 = 1;
                    if (MBPlayerRankCalc(i) < var_s2) {
                        var_s2 = MBPlayerRankCalc(i);
                    }
                }
            }

            if (var_s3 != 0) {
                for (i = 0, var_s1 = 0; i < MB_MAX_PLAYERS; i++) {
                    if ((i != system->current_player_index) && ((GwSystem.unk_58 >> i) & 1) && (MBPlayerRankCalc(i) == var_s2) && GwPlayer[i].coin != 0) {
                        sp10[var_s1] = i;
                        var_s1++;
                    }
                }
            }
        }
    }
    i = sp10[MBRand(var_s1)];
    if (GwPlayer[i].coin == 0) {
        i = 4;
    }
    return i;
}

static s32 MBKettouComWagerGet(s32 playerNo) {
    s32 randRange;
    s32 minCoinAmount;
    s32 starDifference;
    s32 rank;
    GW_SYSTEM *system = &GwSystem;

    starDifference = GwPlayer[system->current_player_index].star - GwPlayer[playerNo].star;

    if ((GwPlayer[system->current_player_index].star - GwPlayer[playerNo].star) < 0) {
        starDifference = GwPlayer[playerNo].star - GwPlayer[system->current_player_index].star;
    }

    //@bug this should've been  if (starDifference >= 1) {
    if (starDifference <= 1) {
        starDifference = 1;
    }

    rank = MBPlayerRankCalc(system->current_player_index);
    switch (mbKettouComWagerTbl[rank][playerNo][starDifference]) {
        case 0:
            randRange = 10;
            minCoinAmount = 90;
            break;
        case 1:
            randRange = 20;
            minCoinAmount = 60;
            break;
        case 2:
            randRange = 20;
            minCoinAmount = 20;
            break;
        default:
            randRange = 9;
            minCoinAmount = 1;
            break;
    }
    randRange = (minCoinAmount + MBRand(randRange)) + 1;
    return GwPlayer[system->current_player_index].coin * (randRange / 100.0f);
}

static s32 MBKettouTargetChoiceGet(u8 *arg0) {
    s32 var_s2 = 0;
    s16 sp18[4];
    u8 sp20[4] = { 1, 2, 4, 8 };
    s32 j;
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == system->current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = 1; // why does this change codegen
                var_s2 = MBKettouComTargetGet() + 1;
                sp18[GwPlayer[i].pad] = D_JPAD;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = HUWIN_COMKEY_PAD;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        HuWinAttrSet(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; var_s2 != 0; j++) {
            var_s2--;
            if (var_s2 == 0) {
                sp18[GwPlayer[system->current_player_index].pad] = A_BUTTON;
            }
            if (j == 0) {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], MBMesWaitGet());
            } else {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], 5);
            }
        }
    } else {
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (arg0[i] == 0) {
            HuWinChoiceDisable(mbDlgWinId, i);
        }
    }

    i = 0;
    do {
        i = HuWinChoiceGet(mbDlgWinId, i, 1);
    } while (arg0[i] == 0);
    return i;
}

static void MBBattleKuriboEnd(void) {
    omDelObj(mbBattleKuriboObj);

    while (mbBattleKuriboMdl->velocity.x <= 120.0f) {
        HuPrcVSleep();
        mbBattleKuriboMdl->velocity.x += 3.0f;
        mbBattleKuriboUpperMdl->velocity.x += 3.0f;
    }

    MBModelKill(mbBattleKuriboMdl);
    MBModelKill(mbBattleKuriboUpperMdl);
}

void MBKettouResultExec(void) {
    char sp20[4];
    s32 temp_s1;
    s32 var_s0;
    GW_SYSTEM *system = &GwSystem;

    if ((GwPlayer[system->current_player_index].bonusCoin == 0) && (GwPlayer[GwSystem.unk_58].bonusCoin == 0)) {
        MBDlgWinExecY(6, 0x4006, 0x88);
        MBCoinChangeStatusCreate(system->current_player_index, GwSystem.playerIndexVisitingBowser);
        MBCoinTakeCreateSound(system->current_player_index, GwSystem.playerIndexVisitingBowser, 0);
        MBCoinChangeStatusCreate(GwSystem.unk_58, GwSystem.playerIndexVisitingBowser);
        MBCoinTakeCreateSound(GwSystem.unk_58, GwSystem.playerIndexVisitingBowser, 1);
    } else {
        var_s0 = (GwPlayer[system->current_player_index].bonusCoin != 0) ? system->current_player_index : GwSystem.unk_58;
        temp_s1 = GwSystem.playerIndexVisitingBowser * 2;
        sprintf(sp20, "%d", temp_s1);
        MBDlgWinInsertCreateY(6, 0x4005, mbCharNameMesTbl[GwPlayer[var_s0].chr], (u32)sp20, 0, 0, 0, 0x88);
        MBDlgWinClose();
        MBDlgWinKill();
        if (GwPlayer[system->current_player_index].bonusCoin != 0) {
            MBCoinChangeStatusCreate(system->current_player_index, temp_s1);
            MBCoinTakeCreateSound(system->current_player_index, temp_s1, 1);
        }
        if (GwPlayer[GwSystem.unk_58].bonusCoin != 0) {
            MBCoinChangeStatusCreate(GwSystem.unk_58, temp_s1);
            MBCoinTakeCreateSound(GwSystem.unk_58, temp_s1, 1);
        }
    }

    MBBattleKuriboEnd();
}

void MBBattleKuriboStart(GW_PLAYER *arg0, s32 arg1) {
    mbBattleKuriboMdl = MBModelCreate(0xC, NULL);
    Hu3DModelScaleSet(mbBattleKuriboMdl->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    Hu3DMotionReset(mbBattleKuriboMdl->omObj1->model[0]);

    mbBattleKuriboMdl->flags |= 1;
    mbBattleKuriboUpperMdl = MBModelCreate(0x1F, NULL);

    Hu3DModelScaleSet(mbBattleKuriboUpperMdl->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&mbBattleKuriboMdl->coords, &arg0->player_obj->coords);
    HuVecCopy3F(&mbBattleKuriboUpperMdl->coords, &arg0->player_obj->coords);

    mbBattleKuriboMdl->velocity.x = 120.0f;
    mbBattleKuriboUpperMdl->velocity.x = 122.0f;

    while (mbBattleKuriboMdl->velocity.x > 30.0f) {
        if (arg1 == 0) {
            HuPrcVSleep();
        }
        mbBattleKuriboMdl->velocity.x -= 1.0f;
        mbBattleKuriboUpperMdl->velocity.x -= 1.0f;
    }
    mbBattleKuriboObj = omAddObj(0x1F4, 0, 0, -1, MBBattleKuriboObjMain);
    mbBattleKuriboObj->rot.x = 180.0f;
}

s32 MBKettouPlayerBitGet(s32 arg0) {
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *player;
    s16 temp_s3;
    s16 var_s2;
    s32 i;

    var_s2 = 0;
    if ((system->total_turns - system->current_turn) >= 5) {
        return 0;
    }

    temp_s3 = MBMasuLinkMasuIdGet(MBPlayerGet(CUR_PLAYER)->clink, MBPlayerGet(CUR_PLAYER)->cidx);

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i != MBPlayerGet(CUR_PLAYER)->turn) {
            if (temp_s3 == MBMasuLinkMasuIdGet(MBPlayerGet(i)->clink, MBPlayerGet(i)->cidx)) {
                var_s2 |= 1 << i;
                if (arg0 != 0) {
                    MBPlayerVibrate(i, 3);
                }
            }
        }
    }
    return var_s2;
}

void MBKettouComResultSet(void) {
    s32 var_s0;
    s32 temp_a0_2;
    s32 var_a0;
    s32 var_a1;
    s32 temp_a3;
    s32 i;
    GW_SYSTEM *system = &GwSystem;
    s32 var_s1;

    WipeCreateOut(WIPE_GOOMBA, 0x10);
    HuPrcSleep(17);
    HuPrcSleep(5);
    var_s1 = GwSystem.unk_58;
    var_s0 = GwPlayer[system->current_player_index].cpu_difficulty - GwPlayer[var_s1].cpu_difficulty;

    if ((GwPlayer[system->current_player_index].cpu_difficulty - GwPlayer[var_s1].cpu_difficulty) < 0) {
        var_s0 = GwPlayer[GwSystem.unk_58].cpu_difficulty - GwPlayer[system->current_player_index].cpu_difficulty;
    }

    // if cpu difficulty difference was greater than 2, clamp to 2
    if (var_s0 > 2) {
        var_s0 = 2;
    }

    temp_a0_2 = MBRand(100.0f);

    for (i = 0; i < 3; i++) {
        if (!(mbKettouComRateTbl[var_s0][i] < temp_a0_2)) {
            break;
        }
    }

    var_a0 = system->current_player_index;
    var_a1 = var_s1;
    temp_a3 = var_a0;

    if (GwPlayer[var_a0].cpu_difficulty < GwPlayer[var_a1].cpu_difficulty) {
        var_a0 = var_a1;
        var_a1 = temp_a3;
    }

    GwPlayer[var_a0].bonusCoin = 0;
    GwPlayer[var_a1].bonusCoin = 0;

    switch (i) {
        case 0:
            GwPlayer[var_a0].bonusCoin = 10;
            break;
        case 1:
            GwPlayer[var_a1].bonusCoin = 10;
            break;
    }

    mbItemBtnF = 0;
    HuAudSubSeqVolFadeOut(0x1E);
    HuPrcSleep(0xF);
    HuAudSeqVolFadeIn(0x1E);
    mbItemBtnF = 1;
    mbSubMusNo = -1;
    mbSeqPlayF = 0;
    omPrcSetStatBit(omAddPrcObj(MBSubMusStopProc, 0, 0, 0), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    WipeCreateIn(WIPE_GOOMBA, 0x10);
    HuPrcSleep(17);
}

s32 MBKettouExec(GW_PLAYER *arg0, s32 arg1) {
    char sp20[MB_MAX_PLAYERS][16];
    u8 sp60[MB_MAX_PLAYERS + 2]; //+2?
    s16 sp68[2];
    s32 sp84;

    Process *temp_s0_2;
    s32 temp_v1;
    s32 var_s1_3;
    s32 var_s2;
    s32 var_s5;
    s32 var_a1;
    s32 var_s0_3;
    s32 var_s1;
    s32 var_s3;
    s32 var_s4;
    s32 var_s6;
    s32 var_s7;
    s32 i;
    s8 *showComMinigames = &GwSystem.show_com_minigames;

    var_s7 = 0;
    var_s4 = 0;
    mbItemBtnF = 0;
    HuAudSeqVolFadeOut(0xF);
    HuPrcSleep(0x10);
    mbSubMusNo = HuAudSubSeqPlay(0x3E);
    mbItemBtnF = 1;
    mbBattleKuriboMdl = MBModelCreate(0xC, NULL);
    Hu3DModelScaleSet(mbBattleKuriboMdl->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    Hu3DMotionReset(mbBattleKuriboMdl->omObj1->model[0]);
    mbBattleKuriboMdl->flags |= 1;
    mbBattleKuriboUpperMdl = MBModelCreate(0x1F, NULL);
    Hu3DModelScaleSet(mbBattleKuriboUpperMdl->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&mbBattleKuriboMdl->coords, &arg0->player_obj->coords);
    HuVecCopy3F(&mbBattleKuriboUpperMdl->coords, &arg0->player_obj->coords);
    mbBattleKuriboMdl->velocity.x = 120.0f;
    mbBattleKuriboUpperMdl->velocity.x = 122.0f;

    while (mbBattleKuriboMdl->velocity.x > 30.0f) {
        HuPrcVSleep();
        mbBattleKuriboMdl->velocity.x -= 1.0f;
        mbBattleKuriboUpperMdl->velocity.x -= 1.0f;
    }

    mbBattleKuriboObj = omAddObj(0x1F4, 0, 0, -1, MBBattleKuriboObjMain);
    mbBattleKuriboObj->rot.x = 180.0f;
    HuAudFXPlay(0x25B);
    var_s1 = 0;

    if (GwPlayer[arg0->turn].coin != 0) {
        var_s6 = 0;

        do { // reg alloc hack
            // Count valid duel targets
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                if ((GwSystem.unk_58 >> i) & 1 && GwPlayer[i].coin != 0) {
                    var_s7++; // valid duel target
                    var_s4 = i;
                    var_s1++;
                    sp20[var_s4][0] = 8;
                    sp60[var_s4] = 1;
                    var_s6 |= 1 << var_s4;
                } else {
                    sp20[i][0] = 1; // invalid duel target (disable prompt?)
                    sp60[i] = 0;
                }

                MBCharNameMesConv(i, &sp20[i][1]);
            }
        } while (0);

        if (var_s1 == 0) {
            MBDlgWinExecY(6, 0x4002, 0x88);
            MBBattleKuriboEnd();
            mbItemBtnF = 0;
            HuAudSubSeqVolFadeOut(0x1E);
            HuPrcSleep(0xF);
            HuAudSeqVolFadeIn(0x1E);
            mbItemBtnF = 1;
            mbSubMusNo = -1;
            mbSeqPlayF = 0;
            omPrcSetStatBit(omAddPrcObj(MBSubMusStopProc, 0, 0, 0), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
            HuPrcSleep(0x1F);
            return 0;
        } else {
            MBDlgWinExecY(6, 0x4000, 0x88);
        }
    } else {
        MBDlgWinExecY(6, 0x4001, 0x88);
        MBBattleKuriboEnd();
        mbItemBtnF = 0;
        HuAudSubSeqVolFadeOut(0x1E);
        HuPrcSleep(0xF);
        HuAudSeqVolFadeIn(0x1E);
        mbItemBtnF = 1;
        mbSubMusNo = -1;
        mbSeqPlayF = 0;
        omPrcSetStatBit(omAddPrcObj(MBSubMusStopProc, 0, 0, 0), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
        HuPrcSleep(0x1F);
        return 0;
    }

    // Target selection loop
    while (1) {
        if (var_s7 >= 2 || (GwSystem.playerIndexVisitingBowser & 0x8000)) {
        tempLabel:
            //?
            sp60[4] = 1;
            sp60[5] = 1;
            MBDlgWinInsertCreate(6, 0x5C02, (u32)sp20[0], (u32)sp20[1], (u32)sp20[2], (u32)sp20[3], 0);
            var_s4 = MBKettouTargetChoiceGet(sp60);
            MBDlgWinClose();
            MBDlgWinKill();

            switch (var_s4) {
                case 4:
                    i = 0;
                    var_s1 = var_s7;
                    for (i = 0; i < MB_MAX_PLAYERS; i++) {
                        if (var_s6 & (1 << i)) {
                            if (var_s1-- != 0) {
                                break;
                            }
                        }
                    }
                    var_s4 = i;
                    break;
                case 5:
                    mbCameraBtnF = 1;
                    mbItemBtnF = 0;
                    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
                    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
                    omPrcResetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
                    mbCameraBtnF = 0;
                    mbItemBtnF = 1;
                    MBTurnHelpKill();
                    goto tempLabel; // Go back to selection menu
            }
        }

        var_s3 = 0;
        break; // Exit selection loop
    }

    // Coin wager selection
    sprintf(sp20[0], "%d", 999);
    HuWinInsertMesSizeGet((u32)sp20[0], 0);
    HuWinMesMaxSizeGet(1, sp68, 0x4003);
    sp84 = MBWinCreate(6, sp68, 0x64);

    var_s1_3 = 1;

    var_s5 = 1;

    if (GwPlayer[GwSystem.current_player_index].coin <= GwPlayer[var_s4].coin) {
        var_s2 = GwPlayer[GwSystem.current_player_index].coin;
    } else {
        var_s2 = GwPlayer[var_s4].coin;
    }

    sprintf(sp20[0], "%d", var_s1_3);
    HuWinInsertMesSet(sp84, (u32)&sp20, 0);
    HuWinMesSet(sp84, 0x4003, -1, -1);
    HuWinExAnimIn(sp84);

    if (MBPlayerComCheck(-1) != 0) {
        var_s3 = MBKettouComWagerGet(var_s4);
        do { // reg alloc hack
            if (var_s2 < var_s3) {
                var_s3 = var_s2;
            }
            if (var_s3 <= 0) {
                var_s3 = 1;
            }
        } while (0);
    }

    var_s0_3 = 5;

    // Coin amount input loop
    while (1) {
        if (MBPlayerComCheck(-1) == 0) {
            // Player controlled input
            if (ContBtnDown[GwPlayer[GwSystem.current_player_index].pad] & A_BUTTON) { //?
                break;                                                                    // Player confirmed selection
            }

            if (ContBtnRep[GwPlayer[GwSystem.current_player_index].pad] & U_JPAD) {
                var_s1_3++;
            }
            if (ContBtnRep[GwPlayer[GwSystem.current_player_index].pad] & D_JPAD) {
                var_s1_3--;
            }
            if (ContBtnRep[GwPlayer[GwSystem.current_player_index].pad] & L_JPAD) {
                var_s1_3 -= 0xA;
            }
            if (ContBtnRep[GwPlayer[GwSystem.current_player_index].pad] & R_JPAD) {
                var_s1_3 += 0xA;
            }
        } else {
            var_s0_3--;
            // AI controlled input
            if (var_s0_3 == -1) {
                if (var_s3 != var_s1_3) {
                    if ((var_s3 % 10) != (var_s1_3 % 10)) {
                        var_s1_3 += 1;
                        var_s0_3 = 5;
                    } else if ((var_s3 / 10) != (var_s1_3 / 10)) {
                        var_s1_3 += 0xA;
                        var_s0_3 = 5;
                    }
                } else {
                    break; // AI finished selecting amount
                }
            }
        }

        // Clamp value to valid range
        if (var_s5 == 1 && var_s1_3 < 1) {
            var_s1_3 = var_s2;
        }
        if (var_s5 == var_s2 && var_s2 < var_s1_3) {
            var_s1_3 = 1;
        }
        if (var_s1_3 <= 0) {
            var_s1_3 = 1;
        }
        if (var_s2 < var_s1_3) {
            var_s1_3 = var_s2;
        }

        if (var_s5 != var_s1_3) {
            HuAudFXPlay(0x246);
        }

        var_s5 = var_s1_3;

        sprintf(sp20[0], "%d", var_s1_3);
        HuWinInsertMesSet(sp84, (u32)&sp20, 0);
        HuWinMesSet(sp84, 0x4003, -1, -1);

        HuPrcVSleep();
    }

    HuAudFXPlay(0x247);
    HuWinExAnimOut(sp84, 0);
    HuWinKill(sp84);
    HuPrcSleep(0xA);
    MBCoinChangeStatusCreate(GwSystem.current_player_index, -var_s1_3);
    MBCoinTakeCreateSound(GwSystem.current_player_index, -var_s1_3, 0);
    MBCoinChangeStatusCreate(var_s4, -var_s1_3);
    MBCoinTakeCreateSound(var_s4, -var_s1_3, 1);
    HuPrcSleep(0x1E);
    MBDlgWinExecY(6, 0x4004, 0x88);

    if (MBPlayerComCheck(-1) != 0) {
        if ((MBPlayerComCheck(var_s4) != 0)) {
            if (*showComMinigames != 0) {
                GwSystem.unk_58 = var_s4;
                GwSystem.playerIndexVisitingBowser = var_s1_3;
                return 2;
            }
        }
    }

    mbItemBtnF = 0;
    MBStatusItemDispOff();
    temp_s0_2 = MBMgCallKettouCreate(GwSystem.current_player_index, var_s4);
    HuPrcChildLink(HuPrcCurrentGet(), temp_s0_2);
    HuPrcChildWatch();

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        GwPlayer[i].group = 2;
    }

    arg0->group = 0;
    GwPlayer[var_s4].group = 1;
    GwSystem.unk_58 = var_s4;
    GwSystem.playerIndexVisitingBowser = var_s1_3;

    mbGameMode = (arg1 == 0) ? 8 : 9;

    mbExitFlag = 2;
    mbExitMusFadeF = 1;
    mbWipeType = WIPE_GOOMBA;
    return 1;
}

/**
 * @brief Gets the current game phase based on the given turn number.
 *
 * This function determines which phase of the game the given turn falls into:
 * early game (0), mid game (1), or late game (2). The thresholds for these
 * phases depend on the total number of turns set for the game and are defined
 * in a lookup table.
 *
 * If the special value `CUR_TURN` is passed, the current turn from GwSystem
 * is used.
 *
 * @param turn The turn number to check. Pass `CUR_TURN` to use the current game turn.
 * @return An integer representing the game phase:
 *         - 0: Early game
 *         - 1: Mid game
 *         - 2: Late game
 */
s32 MBTurnTierGet(s32 turn) {
    u32 turnTierIndex;
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    if (turn == CUR_TURN) {
        turn = system->current_turn;
    }

    turnTierIndex = (system->total_turns / 5) - 2;

    if (system->total_turns < turn) {
        turn = system->total_turns;
    }

    if (turnTierIndex >= 9) {
        turnTierIndex = 0;
    }

    for (i = 0; i < 3; i++) {
        if (mbTurnTierTbl[turnTierIndex][i] > turn) {
            break;
        }
    }

    return i;
}

static s32 MBBattleExec(GW_PLAYER* arg0) {
    char sp20[16];
    omObjData* sp34;
    omObjData* kuriboObj;
    s32 sp3C;
    s32 sp44;
    s32 sp4C;
    Object* temp_v0;
    Object* temp_v0_2;
    f32 var_f20;
    f32 var_f22;
    omObjData* temp_v0_3;
    s32 var_a0;
    s32 var_a1;
    s32 turnTier; // s3
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    void* temp_v0_4;
    s32 i; // s0
    s32 j;
    u8 *table;
    
    mbItemBtnF = 0;
    HuAudSeqVolFadeOut(0xF);
    HuPrcSleep(0x10);
    mbSubMusNo = HuAudSubSeqPlay(0x3E);
    mbItemBtnF = 1;
    
    mbBattleKuriboMdl = MBModelCreate(0xCU, 0);
    Hu3DModelScaleSet(mbBattleKuriboMdl->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    Hu3DMotionReset(mbBattleKuriboMdl->omObj1->model[0]);
    
    mbBattleKuriboMdl->flags |= 1;
    mbBattleKuriboUpperMdl = MBModelCreate(0x1F, 0);
    
    Hu3DModelScaleSet(mbBattleKuriboUpperMdl->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&mbBattleKuriboMdl->coords, &arg0->player_obj->coords);
    HuVecCopy3F(&mbBattleKuriboUpperMdl->coords, &arg0->player_obj->coords);
    
    mbBattleKuriboMdl->velocity.x = 120.0f;
    mbBattleKuriboUpperMdl->velocity.x = 122.0f;
    
    while (mbBattleKuriboMdl->velocity.x > 30.0f) {
        HuPrcVSleep();
        mbBattleKuriboMdl->velocity.x -= 1.0f;
        mbBattleKuriboUpperMdl->velocity.x -= 1.0f;
    }
    
    kuriboObj = omAddObj(0x1F4, 0, 0, -1, MBBattleKuriboObjMain);
    kuriboObj->rot.x = 180.0f;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (GwPlayer[i].coin >= 10) {
            break;
        }
    }
    
    HuAudFXPlay(0x25B);
    var_s6 = 0;
    if (i == MB_MAX_PLAYERS) {
        MBDlgWinExecYAllKey(6, 0x1301, 0x88);
    } else {
        turnTier = MBTurnTierGet(-1);
        for (i = 0, var_s4 = 0; i < MB_MAX_PLAYERS; i++) {
            if (var_s4 < GwPlayer[i].coin) {
                var_s4 = GwPlayer[i].coin;
            }
        }
        
        for (j = 0; j < 3; j++) {
            if (var_s4 < mbBattleCoinMaxTbl[j]) {
                break;
            }
        }

        
        var_s2 = MBRand(100.0f);
        
        for (i = 0, table = mbBattleCoinRateTbl[j][0][0]; i < 5; i++) {
            if (var_s2 < table[(turnTier * 5) + i]) {
                break;
            }
        }

        var_s4 = mbBattleCoinTbl[i];
        var_s6 = i;
        sp3C = MBRandCheck100(10);
        if ((turnTier == 0) && ((MBRandCheck100(30)) != 0)) {
            var_s6 = 0;
            var_s4 = mbBattleCoinTbl[0];
        }
        MBDlgWinInsertCreateYAllKey(6, 0x1300, NULL, 0, 0, 0, 0, 0x88);
        MBDlgWinMesWaitAllKey();
        MBDlgWinClose();
        MBDlgWinKill();
        var_s5 = HuSprGrpCreate(2U, 2U);
        temp_v0_4 = DataRead(0x130113);
        sp44 = HuSprAnimRead(temp_v0_4);
        DataClose(temp_v0_4);
        HuSprGrpMemberSet(var_s5, 0, sp44, 0);
        HuSprPriSet(var_s5, 0, 0x14U);
        HuSprAnimModeSet(var_s5, 0, HUSPR_ANIM_MODE_STOP);
        HuSprAttrSet(var_s5, 0, HUSPR_ATTR_XLU);
        HuSprPosSet(var_s5, 0, 0xA0, 0x78);
        HuSprParentSet(var_s5, 0, -1);
        temp_v0_4 = DataRead(0x130114);
        sp4C = HuSprAnimRead(temp_v0_4);
        DataClose(temp_v0_4);
        HuSprGrpMemberSet(var_s5, 1, sp4C, 0);
        HuSprPriSet(var_s5, 1, 0xAU);
        HuSprAnimModeSet(var_s5, 1, HUSPR_ANIM_MODE_BANK);
        HuSprAttrSet(var_s5, 1, HUSPR_ATTR_XLU);
        HuSprPosSet(var_s5, 1, -0x28, 0x10);
        HuSprParentSet(var_s5, 1, 0);
        
        for (var_f20 = 0.0f; var_f20 < 1.0f; var_f20 += 0.1f) {
            HuSprScaleSet(var_s5, 0, var_f20, var_f20);
            HuSprScaleSet(var_s5, 1, var_f20, var_f20);
            HuPrcVSleep();            
        }
        
        HuSprScaleSet(var_s5, 0, 1.0f, 1.0f);
        HuSprScaleSet(var_s5, 1, 1.0f, 1.0f);
        i = 0;  /* current index */
        var_s3 = 0;    /* tick counter */
        var_s1 = 1;  /* spin speed */
        var_s2 = 0;    /* slowdown counter */
    
        for (;; HuPrcVSleep()) {
            /* Update sprite to current index */
            HuSprGrpMemberSet(var_s5, 1, sp4C, i);
    
            /* Count frames before next tick */
            var_s3++;
            if (var_s3 > var_s1) {
                var_s3 = 0;
                HuAudFXPlay(0x116);
    
                i++;
                if (i >= 5) {
                    i = 0;
                }
            }
    
            /* Slow down the spinner gradually */
            var_s2++;
            if (var_s2 < 9) {
                continue;
            }
            var_s2 = 0;
            var_s1++;
            if (var_s1 <= 6) {
                continue;
            }
            var_s1 = 6;
            
            /* Check stop conditions */
            if (sp3C != 0) {
                /* Overshoot case (10% RNG) */
                if (var_s6 != 4) {
                    if (i == (var_s6 + 1)) {
                        break;
                    }
                } else {
                    if (i == 0) {
                        break;
                    }
                }
            } else {
                /* Normal stop */
                if (i == var_s6) {
                    break;
                }
            }
        }
        HuSprGrpMemberSet(var_s5, 1, sp4C, i);
        HuPrcSleep(0x14);
        if (sp3C != 0) {
            HuAudFXPlay(0x116);
            HuSprGrpMemberSet(var_s5, 1, sp4C, var_s6);
            HuPrcSleep(0xA);
        }

        if (var_s6 != 0) {
            HuAudFXPlay(0x117);
        } else {
            HuAudFXPlay(0x118);
        }
        
        MBSprGrpFlagSet(var_s5, 0);
        HuSprPosSet(var_s5, 1, 0x78, 0x88);
        if (var_s6 == 4) {
            for (var_f22 = 0.0f; var_f22 <= 1080.0f; var_f22 += 50.0f) {
                var_f20 = (sindf(var_f22) * 0.5f) + 1.0f;
                HuSprScaleSet(var_s5, 1, var_f20, var_f20);
                HuPrcVSleep();                
            }

            for (; var_f22 <= 1440.0f; var_f22 += 40.0f) {
                var_f20 = (sindf(var_f22) * 0.5f) + 1.0f;
                HuSprScaleSet(var_s5, 1, var_f20, var_f20);
                HuPrcVSleep();               
            }
        } else {
            for (var_f22 = 0.0f; var_f22 <= 720.0f; var_f22 += 40.0f) {
                var_f20 = (sindf(var_f22) * 0.5f) + 1.0f;
                HuSprScaleSet(var_s5, 1, var_f20, var_f20);
                HuPrcVSleep();                
            }

            for (; var_f22 <= 1080.0f; var_f22 += 30.0f) {
                var_f20 = (sindf(var_f22) * 0.5f) + 1.0f;
                HuSprScaleSet(var_s5, 1, var_f20, var_f20);
                HuPrcVSleep();               
            }
        }
        HuSprScaleSet(var_s5, 1, 1.0f, 1.0f);
        MBSprGrpFlagSet(var_s5, 2U);
        HuSprPosSet(var_s5, 1, -0x28, 0x10);
        HuPrcSleep(0x1E);
        
        for (var_f20 = 1.0f; var_f20 > 0.0f; var_f20 -= 0.1f) {
            HuSprScaleSet(var_s5, 0, var_f20, var_f20);
            HuSprScaleSet(var_s5, 1, var_f20, var_f20);
            HuPrcVSleep();            
        }

        HuSprScaleSet(var_s5, 0, 0.0f, 0.0f);
        HuSprScaleSet(var_s5, 1, 0.0f, 0.0f);
        HuSprGrpKill(var_s5);
        HuSprAnimKill(sp44);
        HuSprAnimKill(sp4C);
        HuPrcSleep(3);

        if (var_s4 == 0) {
            var_s3 = -1;
            var_s6 = 0;
            MBDlgWinInsertCreateYAllKey(6, 0x1304, NULL, 0, 0, 0, 0, 0x88);
            MBDlgWinMesWaitAllKey();
            MBDlgWinClose();
            MBDlgWinKill();
        } else {
            var_s6 = 1;
            var_s3 = -1;
            var_a0 = 0;
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                if (GwPlayer[i].coin >= var_s4) {
                    var_s3 = i;
                    break;
                } else {
                    if (var_a0 < GwPlayer[i].coin) {
                        var_s3 = i;
                        var_a0 = GwPlayer[i].coin;
                    }
                }
            }
            
            var_s2 = 0; //coin total
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                if (GwPlayer[i].coin < var_s4) {
                    GwPlayer[i].checkCoin = GwPlayer[i].coin;
                    var_s2 += GwPlayer[i].coin;
                    MBCoinChangeStatusCreate(i, -GwPlayer[i].coin);
                    if (i == var_s3) {
                        MBCoinTakeCreateSound(i, -GwPlayer[i].coin, 1);
                    } else {
                        MBCoinTakeCreateSound(i, -GwPlayer[i].coin, 0);
                    }
                } else {
                    GwPlayer[i].checkCoin = var_s4;
                    var_s2 += var_s4;
                    MBCoinChangeStatusCreate(i, -var_s4);
                    if (i == var_s3) {
                        MBCoinTakeCreateSound(i, -var_s4, 1);
                    } else {
                        MBCoinTakeCreateSound(i, -var_s4, 0);
                    }
                }
            }

            HuPrcSleep(0x1E);
            sprintf(sp20, "%d", var_s2);
            if (var_s2 < (var_s4 * 4)) {
                MBDlgWinInsertCreateYAllKey(6, 0x1303, (u32)sp20, 0, 0, 0, 0, 0x88);
                MBDlgWinMesWaitAllKey();
            } else {
                MBDlgWinInsertCreateYAllKey(6, 0x1302, (u32)sp20, 0, 0, 0, 0, 0x88);
            }
            MBDlgWinMesWaitAllKey();
            MBDlgWinClose();
            MBDlgWinKill();
            mgBattleCoinPot = var_s2;
        }
    }
    
    if (var_s6 == 0) {
        omDelObj(kuriboObj);
        while (mbBattleKuriboMdl->velocity.x <= 120.0f) {
            HuPrcVSleep();
            mbBattleKuriboMdl->velocity.x += 3.0f;
            mbBattleKuriboUpperMdl->velocity.x += 3.0f;
        }
        MBModelKill(mbBattleKuriboMdl);
        MBModelKill(mbBattleKuriboUpperMdl);
        mbItemBtnF = 0;
        HuAudSubSeqVolFadeOut(0x1E);
        HuPrcSleep(0xF);
        HuAudSeqVolFadeIn(0x1E);
        mbItemBtnF = 1;
        mbSubMusNo = -1;
        mbSeqPlayF = 0;
        omPrcSetStatBit(omAddPrcObj(MBSubMusStopProc, 0U, 0, 0), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
        HuPrcSleep(2);
        return 0;
    } else {
        return 1;
    }
}

static void MBBattleResultExec(void) {
    s32 var_a0;
    s32 var_s1;
    s32 i, j;

    MBDlgWinExecY(6, 0x1305, 0x88);
    var_s1 = 0;
    var_a0 = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (var_a0 < GwPlayer[i].checkCoin) {
            var_a0 = GwPlayer[i].checkCoin;
            var_s1 = i;
        }
    }

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (GwPlayer[i].checkCoin != 0) {
            MBCoinChangeStatusCreate(i, GwPlayer[i].checkCoin);
        }
        if (i == var_s1) {
            MBCoinTakeCreateSound(i, GwPlayer[i].checkCoin, 1);
        } else {
            if (GwPlayer[i].checkCoin != 0) {
                MBCoinTakeCreateSound(i, GwPlayer[i].checkCoin, 0);
            }
        }
    }

    MBBattleKuriboEnd();
}

static void MBGambleResultExec(void) {
    if (GwPlayer[GwSystem.playerIndexVisitingBowser].gameCoin != 0) {
        if (GwPlayer[GwSystem.playerIndexVisitingBowser].bonusCoin != 0) {
            MBCoinChangeStatusCreate(GwSystem.playerIndexVisitingBowser, GwPlayer[GwSystem.playerIndexVisitingBowser].gameCoin * GwPlayer[GwSystem.playerIndexVisitingBowser].bonusCoin);
            MBCoinTakeCreateSound(GwSystem.playerIndexVisitingBowser, GwPlayer[GwSystem.playerIndexVisitingBowser].gameCoin * GwPlayer[GwSystem.playerIndexVisitingBowser].bonusCoin, 1);
        }
    }
    HuPrcSleep(30);
}

static void MBBlockMasuUpdate(void) {
    s32 i;

    if (GWBoardFlagCheck(0xF)) {
        while (kakusiMasuCoin == -1 || kakusiMasuCoin == kakusiMasuStar || kakusiMasuCoin == kakusiMasuItem) {
            kakusiMasuCoin = MBMasuKakusiBlockGet(kakusiMasuCoinCnt);
            kakusiMasuCoinCnt++;
            for (i = 0; i < ARRAY_COUNT(kakusiMasuCoinHis); i++) {
                if (kakusiMasuCoin == kakusiMasuCoinHis[i]) {
                    break;
                }
            }
            if (i != ARRAY_COUNT(kakusiMasuCoinHis)) {
                kakusiMasuCoin = -1;
            }
        }
        while (kakusiMasuStar == -1 || kakusiMasuCoin == kakusiMasuStar || kakusiMasuItem == kakusiMasuStar) {
            kakusiMasuStar = MBMasuKakusiBlockGet(kakusiMasuStarCnt);
            kakusiMasuStarCnt++;
            for (i = 0; i < ARRAY_COUNT(kakusiMasuStarHis); i++) {
                if (kakusiMasuStar == kakusiMasuStarHis[i]) {
                    break;
                }
            }
            if (i != ARRAY_COUNT(kakusiMasuStarHis)) {
                kakusiMasuStar = -1;
            }
        }

        while (kakusiMasuItem == -1 || kakusiMasuCoin == kakusiMasuItem || kakusiMasuStar == kakusiMasuItem) {
            kakusiMasuItem = MBMasuKakusiBlockGet(kakusiMasuItemCnt);
            kakusiMasuItemCnt++;
            for (i = 0; i < ARRAY_COUNT(kakusiMasuItemHis); i++) {
                if (kakusiMasuItem == kakusiMasuItemHis[i]) {
                    break;
                }
            }
            if (i != ARRAY_COUNT(kakusiMasuItemHis)) {
                kakusiMasuItem = -1;
            }
        }
    }
}

void MBTurnHelpCreate(void) {
    s32 var_s0 = 0xA0;

    if (mbTurnHelpWin0 == NULL) {
        mbTurnHelpWin0 = MBHelpWinCreate(2, var_s0, 1);
    }
    if ((mbTurnHelpWin1 == NULL) && !(GwSystem.cur_player_used_item & 1)) {
        var_s0 += 14;
        mbTurnHelpWin1 = MBHelpWinCreate(0xD, var_s0, 1);
    }
    if (mbTurnHelpWin2 == NULL) {
        var_s0 += 14;
        mbTurnHelpWin2 = MBHelpWinCreate(3, var_s0, 1);
    }
    if (mbTurnHelpWin3 == NULL) {
        var_s0 += 14;
        mbTurnHelpWin3 = MBHelpWinCreate(0xB, var_s0, 1);
    }
}

void MBTurnHelpKill(void) {
    if (mbTurnHelpWin0 != NULL) {
        MBHelpWinKill(mbTurnHelpWin0);
        mbTurnHelpWin0 = NULL;
    }
    if (mbTurnHelpWin1 != NULL) {
        MBHelpWinKill(mbTurnHelpWin1);
        mbTurnHelpWin1 = NULL;
    }
    if (mbTurnHelpWin2 != NULL) {
        MBHelpWinKill(mbTurnHelpWin2);
        mbTurnHelpWin2 = NULL;
    }
    if (mbTurnHelpWin3 != NULL) {
        MBHelpWinKill(mbTurnHelpWin3);
        mbTurnHelpWin3 = NULL;
    }
}

void MBGameModeWarpSet(void) {
    mbGameMode = 0xA;
    mbWipeType = WIPE_GOOMBA;
    MBTurnHelpKill();
}

void MBGameModeKettouSet(void) {
    mbGameMode = 0xC;
    mbWipeType = WIPE_GOOMBA;
    MBTurnHelpKill();
}

void MBGameModeMgSet(void) {
    mbGameMode = 0xD;
    mbExitFlag = 2;
    mbExitMusFadeF = 1;
    mbWipeType = WIPE_GAME_GUY;
    MBTurnHelpKill();
}

void MBGameModeMajinLampSet(void) {
    mbGameMode = 0xB;
    MBTurnHelpKill();
    MBExitOvlCall(0x52, 0, 0xB);
}

void MBGameModeReloadSet(void) {
    mbGameMode = 0xF;
    mbWipeType = WIPE_FADE;
    mbExitMusFadeF = 0;
    MBTurnHelpKill();
}

void MBGameModeKoopaSet(void) {
    mbGameMode = 0xE;
    mbWipeType = WIPE_BOWSER;
    MBTurnHelpKill();
}

static void MBMain(void) {
    Process *telopProc;
    s32 i;
    s16 temp_v0_2;
    s32 temp_v0_3;
    GW_PLAYER *temp_v0_4;
    s16 var_s5;
    SpaceData *space;
    Vec sp20;
    Process *temp_s1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    Process *temp_s1_2;
    s16 temp_v0_9;
    s32 temp_v0_16;
    s32 var_v1;
    s32 var_s0;
    s16 temp_v0_18;
    GW_PLAYER *temp_s0_2;
    s32 temp_v0_20;
    s32 temp_s2;
    s32 temp_s0_3;
    s32 temp_s0_4;
    s32 temp_a0;
    s32 temp_s2_2;
    void *temp_v0_21;
    s32 temp_s3_3;
    Object *temp_v0_22;
    Process *temp_s1_5;
    s32 temp_a0_4;
    u32 var_v1_3;
    s32 temp_v1_8;
    s32 temp_a0_3;
    s32 var_s1_12;
    s32 var_s0_2;
    GW_SYSTEM *system = &GwSystem;
    s16 sp30[2];
    s16 sp38[2];
    s16 sp40[2];
    char sp48[16]; // unknown buffer size
    s32 flag;
    s32 state;
    s32 eight;

    telopProc = HuPrcCurrentGet();

    while (1) { // Main game loop
        if ((mbGameMode == 0 || mbGameMode == 1) && system->current_player_index == 0) {
            // Initialize all player colors
            for (i = 0; i < 4; i++) {
                MBPlayerGet(i)->color = 0;
                MBStatusItemDispOn();
            }

            // Check if we're in the last 5 turns
            if (system->total_turns >= 0) {
                short temp_v0 = (system->total_turns - system->current_turn) + 1;
                if (temp_v0 < 6) {
                    if (temp_v0 > 0) {
                        GWBoardFlagSet(2); // Last 5 turns flag
                    }
                }
            }

            if (!GWBoardFlagCheck(1) && system->current_turn >= 2) {
                switch (system->save_mode) {
                    case 1:
                        system->save_mode = 2;
                    case 0:
                        _SetFlag(0);
                        GWBoardFlagSet(0);

                        HuWinMesMaxSizeGet(1, sp30, 0x5900);
                        temp_v0_2 = HuWinCreate(0, 0, sp30[0], sp30[1], 0, 2);
                        HuWinBGTPLvlSet(temp_v0_2, 0);
                        HuWinMesSet(temp_v0_2, 0x5900, -1, -1);
                        HuWinMesSpeedSet(temp_v0_2, 0);

                        while (HuWinStatGet(temp_v0_2) != 0) {
                            HuPrcVSleep();
                        }

                        if (system->playMode & 4) {
                            _SetFlag(0x18);
                            _SetFlag(0x28);
                            SLSaveStory(1);
                        } else {
                            _SetFlag(0x16);
                            SLSaveBoard(1);
                        }

                        HuWinKill(temp_v0_2);
                        HuWinMesMaxSizeGet(1, sp30, 0x5901);
                        temp_v0_3 = HuWinCreate(0, 0, sp30[0], sp30[1], 0, 2);
                        HuWinBGTPLvlSet(temp_v0_3, 0);
                        HuWinMesSet(temp_v0_3, 0x5901, -1, -1);
                        HuWinMesSpeedSet(temp_v0_3, 0);
                        HuPrcSleep(0xF);
                        HuWinKill(temp_v0_3);
                        break;
                }
            }

            GWBoardFlagClear(1);
            mbTurnUnkF = 0;
            mbBoardStartResult = MBMasuEventCall(-2, 7);
        }

        mbTurnUnkF = 1;

        i = 0;
        eight = 8; // definitely a hack
        for (; i < 4; i++) {
            MBStatusColorSet(i, MBPlayerGet(i)->color);
            MBPlayerPosFixSet(i, 1);

            state = mbGameMode;

            if (state == eight) {
                // skip
            } else if (state < 8) {
                flag = 1;
                GwSystem.cur_player_used_item &= ~flag;
            } else if (state >= 0x10) {
                flag = 1;
                GwSystem.cur_player_used_item &= ~flag;
            } else if (state < 0xA) {
                flag = 1;
                GwSystem.cur_player_used_item &= ~flag;
            }
        }

        MBBlockMasuUpdate();
        temp_v0_4 = MBPlayerGet(system->current_player_index);
        var_s5 = MBMasuLinkMasuIdGet(temp_v0_4->clink, temp_v0_4->cidx);
        space = MBMasuGet(var_s5);
        MBMasuCurSet(var_s5);

        state = mbGameMode;

        if (state == 0 || state == 1) {
            goto temp;
        }

        switch (state) {
            case 8:
            case 9:
            case 0xC:
                MBBattleKuriboStart(temp_v0_4, 1);
                break;

            case 0x12:
                i = 0;
                for (; i < 4; i++) {
                    if (GwPlayer[i].bonusCoin != 3)
                        break;
                }
                if (i >= 4) {
                    MBBattleKuriboStart(temp_v0_4, 1);
                }
                break;

            default:
                break;
        }

        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }

        mbItemBtnF = 1;

        switch (mbGameMode) {
            case 12:
                MBKettouResultExec();
                MBSaiCurseFlagSet();
                goto label654;

            case 13: // Bank space
                MBGambleResultExec();

            case 15: // Some event
                MBSaiCurseFlagSet();
                goto label654;
            case 14:
                MBItemKoopaNKinokoExec();
                MBItemKoopaRKinokoExec();
                MBSaiCurseFlagSet();
                goto label654;

            case 11:
                mbGameMode = 0xA;
                MBItemMajinLampStarExec();
                MBVecForwardSet(&sp20);
                MBVecRotLerpCreate(&temp_v0_4->player_obj->rot, &sp20,
                                                  &temp_v0_4->player_obj->rot, 8);
                HuPrcSleep(8);
                goto label654;

            temp:
                MBMasuEventCall(-4, 7);
                // Hide all player models
                Hu3DMotionReset(MBPlayerGet(0)->player_obj->omObj1->model[0]);
                Hu3DMotionReset(MBPlayerGet(1)->player_obj->omObj1->model[0]);
                Hu3DMotionReset(MBPlayerGet(2)->player_obj->omObj1->model[0]);
                Hu3DMotionReset(MBPlayerGet(3)->player_obj->omObj1->model[0]);

                MBPlayerMotionSet(-1, -1, 2);
                MBCameraFocusModeSet(1);

                if (system->current_player_index == 4) {
                    MBKoopaPlayerPosSet();
                }

                // Camera setup
                if (mbCameraZoomInstantF == 0) {
                    mbCameraZoom = 1.0f;
                    MBCameraZoomSet(1.0f);
                    HuPrcChildLink(telopProc, MBScissorWipeInStart());
                } else if (system->current_player_index == 4 || system->current_player_index == 0) {
                    mbCameraZoom = 1.0f;
                    MBCameraZoomSet(1.0f);
                    HuPrcChildLink(telopProc, MBScissorWipeInStart());
                } else {
                    mbCameraZoom = 1.0f;
                    HuPrcChildLink(telopProc, MBCameraZoomMotStart(1.0f));
                }

                HuPrcChildWatch();
            default:
                HuPrcSleep(4);
                MBPlayerVibrate(-1, 3);
                HuPrcChildLink(telopProc, MBTelopCreate(system->current_player_index));
                HuPrcChildWatch();
                MBMasuEventCall(-5, 7);
                goto label654;
            case 6:
            case 16:
                HuPrcSleep(0x1E);
                goto label2444;

            case 9:
                MBKettouResultExec();
                goto label2444;

            case 10:
            label654:
                // STATE 10: Dice roll and movement
                MBTurnHelpCreate();
                mbCameraZoom = 1.3f;
                HuPrcChildLink(telopProc, MBCameraZoomMotStart(1.3f));
                temp_s1 = MBSaiPlayerCreate(system->current_player_index);
                HuPrcChildWatch();
                HuPrcSleep(1);

                if (system->current_player_index != 4) {
                    mbCameraBtnF = 1;
                    mbItemBtnF = 1;
                    mbSaiBtnF = 1;
                    mbMgHis = 1;
                }

                HuPrcChildLink(telopProc, temp_s1);
                HuPrcChildWatch();
                MBTurnHelpKill();

                mbCameraBtnF = 0;
                mbSaiBtnF = 0;
                mbWalkNum = MBSaiValueGet(system->current_player_index);

                if (mbBoardStartResult == 0 && (temp_v0_4->rev & 0x80)) {
                    temp_v0_4->nlink = temp_v0_4->blink;
                    temp_v0_4->nidx = temp_v0_4->bidx;
                    temp_v0_4->rev ^= 1;
                }

                var_s5 = MBMasuCurGet();
                mbBoardStartResult = MBMasuEventCall(var_s5, 9);
                MBPlayerMotionSet(-1, 0, 2);

                while (mbWalkNum != 0) {
                    short temp_s3;
                    short temp_s0;
                    MBMasuEventCall(var_s5, 8);

                    // Save current position
                    temp_s3 = temp_v0_4->clink;
                    temp_s0 = temp_v0_4->cidx;

                    // Update to next position
                    temp_v0_4->clink = temp_v0_4->nlink;
                    temp_v0_4->cidx = temp_v0_4->nidx;

                    // Update walk speed animations
                    for (i = 0; i < 4; i++) {
                        MBPlayerPosFixSet(i, (system->walk_speed * 5) + 5);
                    }

                    // Restore position temporarily
                    temp_v0_4->clink = temp_s3;
                    temp_v0_4->cidx = temp_s0;

                    // Check if next space requires jumping
                    space = MBMasuGet(MBMasuLinkMasuIdGet(temp_v0_4->nlink, temp_v0_4->nidx));

                    if ((space->unk_02 & 0x8000) || MBPlayerJumpCheck(system->current_player_index)) {
                        // Jump animation
                        PlayerFXPlay(0x3A, system->current_player_index);
                        MBPlayerMotionSet(-1, 2, 0);

                        switch (system->walk_speed) {
                            case 0:
                                temp_v0_4->player_obj->velocity.y = 8.0f;
                                temp_v0_4->player_obj->velocity.z = -2.0f;
                                MBPlayerPosMoveSet(system->current_player_index, 7);
                                break;
                            case 1:
                                temp_v0_4->player_obj->velocity.y = 4.0f;
                                temp_v0_4->player_obj->velocity.z = -0.5f;
                                MBPlayerPosMoveSet(system->current_player_index, 0xF);
                                break;
                            case 2:
                                temp_v0_4->player_obj->velocity.y = 2.0f;
                                temp_v0_4->player_obj->velocity.z = -0.125f;
                                MBPlayerPosMoveSet(system->current_player_index, 0x1E);
                                break;
                        }
                    } else {
                        // Normal walk animation
                        if (temp_v0_4->player_obj->unk46 != 0) {
                            MBPlayerMotionSet(-1, 0, 2);
                        }

                        switch (system->walk_speed) {
                            case 0:
                                Hu3DMotionSpeedSet(temp_v0_4->player_obj->omObj1->model[0], 2.0f);
                                MBPlayerPosMoveSet(system->current_player_index, 5);
                                break;
                            case 1:
                                Hu3DMotionSpeedSet(temp_v0_4->player_obj->omObj1->model[0], 1.0f);
                                MBPlayerPosMoveSet(system->current_player_index, 0xA);
                                break;
                            case 2:
                                Hu3DMotionSpeedSet(temp_v0_4->player_obj->omObj1->model[0], 0.75f);
                                MBPlayerPosMoveSet(system->current_player_index, 0xF);
                                break;
                        }
                        Hu3DMotionSpeedSet(temp_v0_4->player_obj->omObj1->model[0], 1.0f);
                    }

                    // Update position
                    temp_v0_4->blink = temp_v0_4->clink;
                    temp_v0_4->bidx = temp_v0_4->cidx;
                    temp_v0_4->clink = temp_v0_4->nlink;
                    temp_v0_4->cidx = temp_v0_4->nidx;

                    // Calculate next index based on direction
                    if (temp_v0_4->rev & 1) {
                        temp_v0_4->nidx = temp_v0_4->nidx - 1;
                    } else {
                        temp_v0_4->nidx = temp_v0_4->nidx + 1;
                    }

                    var_s5 = MBMasuLinkMasuIdGet(temp_v0_4->clink, temp_v0_4->cidx);
                    space = MBMasuGet(var_s5);
                    MBMasuCurSet(var_s5);

                    // Handle passing over certain space types
                    switch (space->space_type) {
                        case SPACE_BLUE:
                        case SPACE_RED:
                        case SPACE_HAPPENING:
                        case SPACE_CHANCE_TIME:
                        case SPACE_ITEM:
                        case SPACE_BANK:
                        case SPACE_BATTLE:
                        case SPACE_BOWSER:
                        case SPACE_GAME_GUY:
                            MBSaiNumCountDown(system->current_player_index);
                            mbWalkNum--;
                            MBMasuBounceCreate(var_s5);
                            break;
                    }

                    // Play appropriate sound effect
                    if (mbWalkNum != 0) {
                        MBMasuPassSePlay(space->space_type);
                    } else {
                        MBMasuLandSePlay(space->space_type);
                    }

                    MBItemKSuitWalkExec();
                    mbBoardStartResult = MBMasuEventCall(var_s5, 1);

                    if (mbExitFlag < 0) {
                        continue;
                    }

                    mbGameMode = 2;
                    HuPrcSleep(-1);
                    case 2:
                        if (mbBoardStartResult & 1) {
                            var_s5 = MBMasuCurGet();
                            mbBoardStartResult = MBMasuEventCall(var_s5, 2);
                            if (mbExitFlag >= 0) {
                                mbGameMode = 3;
                                HuPrcSleep(-1);
                            }
                        }
                        /* fallthrough */
                    case 3:
                        if (mbBoardStartResult & 2) {
                            mbWalkNum = 0;
                            continue;
                        }
                        MBSaiNumShow(system->current_player_index);
                        HuPrcSleep(0xA);
                }

                if (system->current_board_index == 3) {
                    GwSystem.boardData.halfWordBytes[4] = 0;
                }

                // Handle reverse direction cleanup
                if (temp_v0_4->rev & 0x80) {
                    if (temp_v0_4->rev & 1) {
                        // Swap blink/nlink and bidx/nidx
                        temp_v1_2 = temp_v0_4->blink;
                        temp_v0_4->blink = temp_v0_4->nlink;
                        temp_v0_4->nlink = temp_v1_2;

                        temp_v1_3 = temp_v0_4->bidx;
                        temp_v0_4->bidx = temp_v0_4->nidx;
                        temp_v0_4->nidx = temp_v1_3;
                    }
                    temp_v0_4->rev &= ~(0x80 | 0x1);
                }

                MBPlayerMotionSet(-1, -1, 2);
                var_s5 = MBMasuLinkMasuIdGet(temp_v0_4->clink, temp_v0_4->cidx);

                switch (MBMasuGet(var_s5)->space_type) {
                    case SPACE_HAPPENING:
                        MBPlayerVibrate(-1, 3);
                        temp_v0_4->stats.prize.hatenaPrize++;
                        break;
                    case SPACE_RED:
                        MBPlayerVibrate(-1, 1);
                        temp_v0_4->stats.prize.redPrize++;
                        break;
                    case SPACE_BLUE:
                        temp_v0_4->stats.prize.bluePrize++;
                        break;
                    case SPACE_CHANCE_TIME:
                        MBPlayerVibrate(-1, 4);
                        temp_v0_4->stats.prize.eventPrize++;
                        break;
                    case SPACE_GAME_GUY:
                        MBPlayerVibrate(-1, 4);
                        temp_v0_4->stats.prize.gamblePrize++;
                        break;
                    case SPACE_BOWSER:
                        MBPlayerVibrate(-1, 2);
                        temp_v0_4->stats.prize.kupaPrize++;
                        break;
                    case SPACE_BATTLE:
                        MBPlayerVibrate(0, 2);
                        MBPlayerVibrate(1, 2);
                        MBPlayerVibrate(2, 2);
                        MBPlayerVibrate(3, 2);
                        temp_v0_4->stats.prize.battlePrize++;
                        break;
                    case SPACE_ITEM:
                        MBPlayerVibrate(-1, 2);
                        temp_v0_4->stats.prize.itemPrize++;
                        break;
                    case SPACE_BANK:
                        MBPlayerVibrate(-1, 3);
                        temp_v0_4->stats.prize.bankPrize++;
                        break;
                }

                mbGameMode = 4;
                mbBoardStartResult = MBMasuEventCall(var_s5, 3);

                if (mbExitFlag < 0) {
                    goto labelE5C;
                }
                HuPrcSleep(-1);
                /* fallthrough */
            case 4:
                // STATE 4 & 5: Additional space handling
                if (mbBoardStartResult & 1) {
                    mbBoardStartResult = MBMasuEventCall(MBMasuCurGet(), 4);

                    if (mbExitFlag >= 0) {
                        mbGameMode = 5;
                        HuPrcSleep(-1);
                    }
                }
                /* fallthrough */
            case 5:
                HuPrcSleep(30);
            labelE5C:

                // Return player to space position
                MBVecForwardSet(&sp20);
                MBVecRotLerpSpinCreate(&temp_v0_4->player_obj->rot, &sp20,
                                                  &temp_v0_4->player_obj->rot, 8);

                var_s5 = MBMasuLinkMasuIdGet(temp_v0_4->clink, temp_v0_4->cidx);
                space = MBMasuGet(var_s5);

                if (kakusiMasuStar == var_s5 || kakusiMasuStarForceF != 0) {
                    MBPlayerVibrate(-1, 5);
                    HuPrcChildLink(telopProc, MBCameraZoomMotStart(1.6f));
                    temp_s1 = MBKakusiStarBlockCreate(system->current_player_index);
                    MBKakusiWaitOn();

                    // Display message window
                    HuWinMesMaxSizeGet(1, sp30, 0x3F00);
                    temp_v0_9 = HuWinExCreate(-1, 0xA0 - (sp30[0] / 2), 0x96, sp30[0], sp30[1], 0);
                    HuWinMesSet(temp_v0_9, 0x3F00, -1, -1);
                    HuWinExAnimIn(temp_v0_9);
                    HuWinKeyLockSet(temp_v0_9, 1);
                    HuPrcChildWatch();

                    HuWinKeyLockSet(temp_v0_9, 0);
                    MBWinComKeyWait(temp_v0_9, temp_v0_4->turn);
                    HuWinExAnimOut(temp_v0_9, 0);
                    HuWinKill(temp_v0_9);
                    MBKakusiWaitOff();

                    // Wait for player input
                    while (!(MBKakusiWaitCheck())) {
                        HuPrcVSleep();
                    }

                    // Display follow-up message
                    HuWinMesMaxSizeGet(1, sp30, 0x3F01);
                    temp_v0_9 = HuWinExCreate(-1, 0xA0 - (sp30[0] / 2), 0x96, sp30[0], sp30[1], 0);
                    HuWinMesSet(temp_v0_9, 0x3F01, -1, -1);
                    HuWinExAnimIn(temp_v0_9);
                    MBWinComKeyWait(temp_v0_9, temp_v0_4->turn);
                    HuWinExAnimOut(temp_v0_9, 0);
                    HuWinKill(temp_v0_9);
                    MBKakusiWaitOff();

                    HuPrcChildLink(telopProc, temp_s1);
                    HuPrcChildWatch();
                    HuPrcChildLink(telopProc, MBCameraZoomMotStart(1.3f));
                    HuPrcChildWatch();
                    HuPrcSleep(1);

                    // Update star block history
                    kakusiMasuStarHis[kakusiMasuStarHisIdx++] = kakusiMasuStar;
                    kakusiMasuStarHisIdx = kakusiMasuStarHisIdx % 10;
                    kakusiMasuStar = -1;
                    MBBlockMasuUpdate();
                }

                // COIN BLOCK HANDLING (similar structure to star block)
                if (kakusiMasuCoin == var_s5 || kakusiMasuCoinForceF != 0) {
                    MBPlayerVibrate(-1, 5);
                    HuPrcChildLink(telopProc, MBCameraZoomMotStart(1.6f));
                    temp_s1 = MBKakusiCoinBlockCreate(system->current_player_index);
                    MBKakusiWaitOn();
                    HuWinMesMaxSizeGet(1, sp38, 0x3F00);
                    temp_v0_9 = HuWinExCreate(-1, 0xA0 - (sp38[0] / 2), 0x96, sp38[0], sp38[1], 0);
                    HuWinMesSet(temp_v0_9, 0x3F00, -1, -1);
                    HuWinExAnimIn(temp_v0_9);
                    HuWinKeyLockSet(temp_v0_9, 1);
                    HuPrcChildWatch();
                    HuWinKeyLockSet(temp_v0_9, 0);
                    MBWinComKeyWait(temp_v0_9, temp_v0_4->turn);
                    HuWinExAnimOut(temp_v0_9, 0);
                    HuWinKill(temp_v0_9);
                    MBKakusiWaitOff();

                    while (!MBKakusiWaitCheck()) {
                        HuPrcVSleep();
                    }

                    HuPrcChildLink(telopProc, temp_s1);
                    HuPrcChildWatch();
                    HuWinMesMaxSizeGet(1, sp38, 0x3F02);
                    temp_v0_9 = HuWinExCreate(-1, 0xA0 - (sp38[0] / 2), 0x96, sp38[0], sp38[1], 0);
                    HuWinMesSet(temp_v0_9, 0x3F02, -1, -1);
                    HuWinExAnimIn(temp_v0_9);
                    MBWinComKeyWait(temp_v0_9, temp_v0_4->turn);
                    HuWinExAnimOut(temp_v0_9, 0);
                    HuWinKill(temp_v0_9);
                    HuPrcChildLink(telopProc, MBCameraZoomMotStart(1.3f));
                    HuPrcChildWatch();
                    HuPrcSleep(1);
                    kakusiMasuCoinHis[kakusiMasuCoinHisIdx++] = kakusiMasuCoin;
                    kakusiMasuCoinHisIdx = kakusiMasuCoinHisIdx % 10;
                    kakusiMasuCoin = -1;
                    MBBlockMasuUpdate();
                }

                // ITEM BLOCK HANDLING
                if (kakusiMasuItem == var_s5 || kakusiMasuItemForceF != 0) {
                    short var_s1;
                    short temp_v1_6;
                    MBPlayerVibrate(-1, 5);

                    // Random item selection with weighted probabilities
                    do {
                        var_s1 = 0;
                        temp_v1_6 = MBRand(100.0f) + 1;

                        while (1) {
                            if (temp_v1_6 <= mbKakusiItemRateTbl[var_s1][1])
                                break;
                            var_s1++;
                        }

                    } while (GwSystem.wackyWatchUsedState != WATCH_AVAILABLE && mbKakusiItemRateTbl[var_s1][0] == ITEM_WACKY_WATCH);

                    HuPrcChildLink(telopProc, MBCameraZoomMotStart(1.6f));
                    MBKakusiItemBlockCreate(system->current_player_index,
                                                     mbKakusiItemRateTbl[var_s1][0]);
                    MBKakusiWaitOn();

                    // Display item message window
                    HuWinMesMaxSizeGet(1, sp40, 0x3F00);
                    temp_v0_9 = HuWinExCreate(-1, 0xA0 - (sp40[0] / 2), 0x96, sp40[0], sp40[1], 0);
                    HuWinMesSet(temp_v0_9, 0x3F00, -1, -1);
                    HuWinExAnimIn(temp_v0_9);
                    HuWinKeyLockSet(temp_v0_9, 1);
                    HuPrcChildWatch();

                    HuWinKeyLockSet(temp_v0_9, 0);
                    MBWinComKeyWait(temp_v0_9, temp_v0_4->turn);
                    HuWinExAnimOut(temp_v0_9, 0);
                    HuWinKill(temp_v0_9);
                    MBKakusiWaitOff();

                    // Wait for input
                    while (!(MBKakusiWaitCheck() & 0xFF)) {
                        HuPrcVSleep();
                    }

                    MBKakusiWaitOff();
                    HuWinInsertMesSizeGet(var_s1 + 0x3F04, 0);

                    // Display item received message
                    HuWinMesMaxSizeGet(1, sp40, 0x3F03);
                    temp_v0_9 = HuWinExCreate(-1, 0xA0 - (sp40[0] / 2), 0x96, sp40[0], sp40[1], 0);
                    HuWinInsertMesSet(temp_v0_9, var_s1 + 0x3F04, 0);
                    HuWinMesSet(temp_v0_9, 0x3F03, -1, -1);
                    HuWinExAnimIn(temp_v0_9);
                    MBWinComKeyWait(temp_v0_9, temp_v0_4->turn);
                    HuWinExAnimOut(temp_v0_9, 0);
                    HuWinKill(temp_v0_9);

                    // Check if player has empty item slot
                    if (MBItemFindEmpty(system->current_player_index) == -1) {
                        MBDlgResultWinExec(0x3F0A); // Inventory full message
                    }

                    MBKakusiWaitOn();
                    HuPrcSleep(5);

                    // Wait for input
                    while (!(MBKakusiWaitCheck() & 0xFF)) {
                        HuPrcVSleep();
                    }

                    HuPrcSleep(0xA);
                    HuPrcChildLink(telopProc, MBCameraZoomMotStart(1.3f));
                    HuPrcChildWatch();
                    HuPrcSleep(1);

                    // Update item block history
                    kakusiMasuItemHis[kakusiMasuItemHisIdx++] = kakusiMasuItem;
                    kakusiMasuItemHisIdx = kakusiMasuItemHisIdx % 10;
                    kakusiMasuItem = -1;
                    MBBlockMasuUpdate();
                }

                // HAPPENING SPACE: Check for duel minigame
                if (space->space_type == SPACE_HAPPENING) {
                    goto label;
                } else {
                    short temp_v0_15;
                    temp_v0_15 = MBKettouPlayerBitGet(1);

                    if (temp_v0_15 == 0) {
                        goto label;
                    } else {
                        GwSystem.unk_58 = temp_v0_15;
                        GwSystem.playerIndexVisitingBowser = (1 << temp_v0_4->turn); //?
                        MBPlayerVibrate(temp_v0_4->turn, 3);

                        temp_v0_16 = MBKettouExec(temp_v0_4, 0);

                        if (temp_v0_16 == 0) {
                            goto label; //?
                            MBKettouResultExec();
                        } else if (temp_v0_16 == 1) {
                            HuPrcSleep(-1);
                        }
                        MBKettouComResultSet();
                    }
                }
                /* fallthrough */
            case 8:
                MBKettouResultExec();
            label:
                MBPlayerMasuColorSet(-1, space->space_type);
                MBStatusColorSet(system->current_player_index, temp_v0_4->color);

                switch (space->space_type) {
                    case SPACE_BLUE:
                        var_v1 = (GWBoardFlagCheck(2) != 0) ? 2 : 1; // Last 5 turns doubles coins
                        var_s0 = var_v1 * 2;
                        var_s0 += var_v1;

                    label181C:
                        MBCoinChangeCreate(system->current_player_index, var_s0);
                        MBCoinTakeCreate(system->current_player_index, var_s0);
                        HuPrcSleep(0x1E);
                        goto label2444;

                    case SPACE_RED:
                        var_v1 = (GWBoardFlagCheck(2) != 0) ? 2 : 1;
                        var_s0 = var_v1 * 2;
                        var_s0 += var_v1;
                        var_s0 = -var_s0;
                        goto label181C;

                    case SPACE_HAPPENING:
                        if (mbHatenaFunc == NULL) {
                            goto label2444;
                        }

                        // Execute board-specific happening event
                        HuPrcChildLink(telopProc, omAddPrcObj(mbHatenaFunc, 0x4800, 0, 0));
                        HuPrcChildWatch();

                        // Special handling for board 3
                        if (system->current_board_index == 3 && GwSystem.boardData.halfWordBytes[3] != 0) {
                            GwSystem.boardData.halfWordBytes[3] = 0;
                            goto label654; // Jump back to state 10 (dice roll)
                        }

                        // Check for another duel minigame
                        temp_v0_18 = MBKettouPlayerBitGet(1);

                        if (temp_v0_18 == 0) {
                            goto label2444;
                        }
                        GwSystem.unk_58 = temp_v0_18;
                        GwSystem.playerIndexVisitingBowser = (1 << MBPlayerGet(CUR_PLAYER)->turn); //?
                        MBPlayerVibrate(MBPlayerGet(CUR_PLAYER)->turn, 3);

                        temp_v0_16 = MBKettouExec(temp_v0_4, 1);

                        if (temp_v0_16 == 0) {
                            goto label2444;
                        } else if (temp_v0_16 == 1) {
                            HuPrcSleep(-1);
                        }
                        MBKettouComResultSet();
                        MBKettouResultExec();
                        goto label2444;

                    case SPACE_CHANCE_TIME:
                        mbGameMode = 0x10;

                        // Set up team groups
                        for (i = 0; i < 4; i++) {
                            temp_s0_2 = MBPlayerGet(i);
                            temp_s0_2->group = (i != MBPlayerTurnGet());
                        }

                        // Trigger event minigame
                        MBExitOvlCallEx(0x6A, 0, 5, 1);
                        HuPrcSleep(-1);
                        HuPrcSleep(0x1E);
                        goto label2444;

                    case SPACE_ITEM:
                        mbItemBtnF = 0;
                        HuPrcSleep(8);

                        // Check if last turn
                        if (system->current_turn == system->total_turns) {
                            MBDlgResultWinExec(0x3C01); // Last turn message
                            goto label2444;
                        }

                        // Check if inventory full
                        if (MBItemFindEmpty(system->current_player_index) == -1) {
                            MBDlgResultWinExec(0x3C00); // Inventory full
                            goto label2444;
                        }

                        // Item shop - random outcome
                        temp_v0_20 = MBRand(5.0f);

                        switch (temp_v0_20) {
                            case 0:
                                MBItemMasuKinopioExec(); // Shop outcome 1
                                goto label2444;
                            case 1:
                                MBItemMasuKoopaJrExec(); // Shop outcome 2
                                goto label2444;
                            default:
                                // Item minigame option
                                if (MBPlayerComCheck(-1) == 0 || system->show_com_minigames == 0) {
                                    goto label1d70;
                                }
                                // COM item minigame logic
                                WipeCreateOut(WIPE_TOAD, 0x10);
                                HuPrcSleep(0x11);
                                HuPrcSleep(5);
                                WipeCreateIn(WIPE_TOAD, 0x10);
                                HuPrcSleep(0x11);

                                temp_s2 = MBRandCheck100(66) ? 0 : 1;

                                // AI decision logic
                                if (!(MBRand(100.0f) >= mbShopComEnterRateTbl[GwPlayer[system->current_player_index].cpu_difficulty])) {
                                    // AI accepts - determine item
                                    i = 0;
                                    temp_s0_3 = MBPlayerRankCalc(system->current_player_index);
                                    temp_s0_4 = mbShopComRankTbl[temp_s2][temp_s0_3][MBTurnTierGet(-1)];
                                    temp_a0 = MBRand(100.0f);

                                    // Find item based on weighted table
                                    for (i = 0; i < 8; i++) {
                                        if (mbShopComItemRateTbl[temp_s2][temp_s0_4][i] > temp_a0) {
                                            break;
                                        }
                                    }

                                    // Display message
                                    MBDlgWinInsertCreate(-1, 0x3C22, mbShopMesTbl[temp_s2][i], 0, 0, 0, 0);
                                    MBDlgWinClose();
                                    MBDlgWinKill();

                                    // Store item
                                    GwPlayer[system->current_player_index].bonusCoin = mbShopItemTbl[temp_s2][i];

                                    // Display item sprite with animation
                                    temp_s2_2 = HuSprGrpCreate(1, 5);
                                    temp_v0_21 = DataRead(mbItemIconSprTbl[mbShopItemTbl[temp_s2][i]]);
                                    temp_s3_3 = HuSprAnimRead(temp_v0_21);
                                    DataClose(temp_v0_21);

                                    HuSprGrpMemberSet(temp_s2_2, 0, temp_s3_3, 0);
                                    HuSprPriSet(temp_s2_2, 0, 0xA);
                                    HuSprAnimModeSet(temp_s2_2, 0, HUSPR_ANIM_MODE_STOP);
                                    HuSprAttrSet(temp_s2_2, 0, HUSPR_ATTR_XLU | HUSPR_ATTR_AA | HUSPR_ATTR_FILTER_AVERAGE);
                                    HuSprPosSet(temp_s2_2, 0, 0xA0, 0x5A);
                                    HuSprTPLvlSet(temp_s2_2, 0, 0);
                                    HuAudFXPlay(0x10);

                                    // Animate sprite appearing
                                    for (i = 0; i < 0xA; i++) {
                                        HuSprTPLvlSet(temp_s2_2, 0, (i * 25));
                                        HuPrcVSleep();
                                    }

                                    HuSprTPLvlSet(temp_s2_2, 0, 0x100);
                                    HuPrcSleep(5);
                                    MBPlayerMotionSet(-1, 5, 0);
                                    HuPrcSleep(5);
                                    PlayerFXPlay(0x2BD, system->current_player_index);
                                    HuPrcSleep(0x14);
                                    MBPlayerMotionShiftSet(-1, -1, 0, 5, 2);
                                    HuPrcSleep(0xA);

                                    // Clean up sprite
                                    HuSprGrpKill(temp_s2_2);
                                    HuSprAnimKill(temp_s3_3);
                                    goto tempCase17;
                                }

                                MBDlgResultWinExec(0x3C32);
                                goto label2444;

                            label1d70:
                                MBStatusItemDispOff();

                                for (i = 0; i < 4; i++) {
                                    GwPlayer[i].group = 1;
                                }

                                temp_v0_4->group = 0;
                                HuPrcChildLink(telopProc, MBMgCallGambleCreate());
                                HuPrcChildWatch();

                                mbGameMode = 0x11;
                                mbExitFlag = 2;
                                mbExitMusFadeF = 1;
                                mbWipeType = WIPE_TOAD;
                                HuPrcSleep(-1);
                                goto label2444;
                        }

                    tempCase17:

                        GwPlayer[system->current_player_index].itemNo[MBItemFindEmpty(system->current_player_index)] =
                            GwPlayer[system->current_player_index].bonusCoin;
                        HuPrcSleep(0x1E);
                        goto label2444;
                    case SPACE_BATTLE:
                        if (!(MBBattleExec(temp_v0_4))) {
                            goto label2444;
                        } else {
                            mbItemBtnF = 0;
                            MBStatusItemDispOff();
                            HuPrcChildLink(telopProc, MBMgCallBattleCreate());
                            HuPrcChildWatch();
                            mbGameMode = 0x12;
                            mbExitFlag = 2;
                            mbExitMusFadeF = 1;
                            mbWipeType = WIPE_GOOMBA;
                            HuPrcSleep(-1);
                        }

                    test:
                        for (i = 0; i < 4; i++) {
                            if (GwPlayer[i].bonusCoin != 3) {
                                break;
                            }
                        }

                        if (i >= 4) {
                            // All players done with battle
                            MBBattleResultExec();
                        }

                        goto label2444;
                    case SPACE_BOWSER:
                        mbGameMode = 6;
                        GwSystem.playerIndexVisitingBowser = system->current_player_index;
                        MBExitOvlCallEx(0x50, 0, 3, 1);
                        HuPrcSleep(-1);
                        HuPrcSleep(0x1E);
                        goto label2444;

                    case SPACE_GAME_GUY:
                        HuPrcSleep(8);

                        // Create game guy object
                        temp_v0_22 = MBModelCreate(0x3E, NULL);
                        MBModelTempAllocFree(temp_v0_22);
                        HuVecCopy3F(&temp_v0_22->coords, &temp_v0_4->player_obj->coords);
                        temp_v0_22->velocity.x = 100.0f;

                        // Animate game guy appearing on screen
                        while (temp_v0_22->velocity.x >= 30.0f) {
                            temp_v0_22->velocity.x -= 2.0f;
                            HuPrcVSleep();
                        }

                        temp_s1 = MBModelHoverCreate(temp_v0_22, 5.0f, 2.0f);
                        HuAudFXPlay(0x2A1);

                        if (GwPlayer[system->current_player_index].coin != 0) {
                            // Take all coins
                            MBDlgWinExec(0xA, 0x2F00);
                            GwPlayer[system->current_player_index].gameCoin =
                                GwPlayer[system->current_player_index].coin;

                            MBCoinChangeCreate(system->current_player_index,
                                               -GwPlayer[system->current_player_index].coin);
                            MBCoinTakeCreate(system->current_player_index,
                                                              -GwPlayer[system->current_player_index].coin);
                            HuPrcSleep(0x1E);
                            MBDlgWinExec(0xA, 0x2F02);
                            omDelPrcObj(temp_s1);

                            // Animate game guy leaving with player
                            while (temp_v0_22->velocity.x >= 10.0f) {
                                temp_v0_22->velocity.x -= 2.0f;
                                HuPrcVSleep();
                            }

                            MBModelJumpSet(temp_v0_22, 2.0f, 0.0001f);
                            MBModelJumpSet(temp_v0_4->player_obj, 2.0f, 0.0001f);
                            HuPrcSleep(0x1E);
                        } else {
                            MBDlgWinExec(0xA, 0x2F01);
                            omDelPrcObj(temp_s1);
                            // Animate game guy leaving with player
                            while (temp_v0_22->velocity.x <= 100.0f) {
                                temp_v0_22->velocity.x += 4.0f;
                                HuPrcVSleep();
                            }
                            MBModelKill(temp_v0_22);
                            goto label2488;
                        }

                        if (MBPlayerComCheck(-1) != 0 && system->show_com_minigames != 0) {
                            // COM game guy - immediate result
                            WipeCreateOut(WIPE_GAME_GUY, 0x10);
                            HuPrcSleep(0x11);
                            MBModelKill(temp_v0_22);
                            MBModelJumpSet(temp_v0_4->player_obj, 0, 0);
                            temp_v0_4->player_obj->velocity.x = 0.0f;
                            HuPrcSleep(5);
                            WipeCreateIn(WIPE_GAME_GUY, 0x10);
                            HuPrcSleep(0x11);

                            // Weighted random multiplier
                            temp_v1_8 = MBRand(GAME_GUY_RANDOM_MAX) + 1;

                            for (i = 0; i < ARRAY_COUNT(mbGambleComRateTbl); i++) {
                                if (mbGambleComRateTbl[i].weight >= temp_v1_8) {
                                    break;
                                }
                            }

                            temp_a0_3 = mbGambleComRateTbl[i].multiplier;

                            if (temp_a0_3 != 0) {
                                // Won multiplier
                                var_s1_12 = GwPlayer[system->current_player_index].gameCoin * temp_a0_3;

                                if (var_s1_12 > 999) {
                                    var_s1_12 = 999;
                                }

                                sprintf(sp48, "%d", var_s1_12);
                                MBDlgWinInsertCreate(-1, 0x2F03, (s32)sp48, 0, 0, 0, 0);
                                MBDlgWinClose();
                                MBDlgWinKill();

                                MBCoinChangeCreate(system->current_player_index, var_s1_12);
                                MBCoinTakeCreate(system->current_player_index, var_s1_12);
                                HuPrcSleep(0x14);
                                MBPlayerMotionSet(-1, 5, 0);
                                PlayerFXPlay(0x274, system->current_player_index);
                                MBPlayerMotionWait(-1);
                            } else {
                                // Lost everything
                                MBDlgWinExec(-1, 0x2F04);
                                MBPlayerMotionSet(-1, 3, 0);
                                PlayerFXPlay(0x286, system->current_player_index);
                                MBPlayerMotionWait(-1);
                                HuPrcSleep(0x14);
                            }

                            MBPlayerMotionShiftSet(-1, -1, 0, 5, 2);
                            HuPrcSleep(0xA);
                            goto label2488;
                        } else {
                            // Setup for game guy minigame
                            mbGameMode = 0x13;
                            mbExitFlag = 2;
                            mbExitMusFadeF = 1;
                            mbWipeType = WIPE_GAME_GUY;

                            for (i = 0; i < 4; i++) {
                                GwPlayer[i].group = 1;
                            }
                            temp_v0_4->group = 0;

                            // Select minigame based on weighted random
                            temp_a0_4 = MBRand(100.0f);
                            var_v1_3 = 0;

                            for (var_v1_3 = 0; var_v1_3 < ARRAY_COUNT(mbGambleMgRateTbl); var_v1_3++) {
                                if (mbGambleMgRateTbl[var_v1_3] > temp_a0_4) {
                                    break;
                                }
                            }

                            if (var_v1_3 == ARRAY_COUNT(mbGambleMgRateTbl)) {
                                var_v1_3 = ARRAY_COUNT(mbGambleMgRateTbl) - 1;
                            }

                            system->minigame_index = mbGambleMgTbl[var_v1_3];
                            GwSystem.playerIndexVisitingBowser = system->current_player_index;
                        }

                        HuPrcSleep(-1);
                        goto label2438;

                    case SPACE_UNK:
                    case SPACE_BANK:
                    case SPACE_START:
                    case SPACE_UNK2: // Mushroom space? (from mp1)
                    case SPACE_UNK3:
                    case SPACE_ARROW:
                    case SPACE_STAR:
                    default:
                        goto label2444;
                }
            case 17:
                goto tempCase17;
            case 18:
                goto test;
            case 19:
            label2438:
                MBGambleResultExec();
            label2444:
                mbGameMode = 7;
                mbBoardStartResult = MBMasuEventCall(var_s5, 5);
                if (mbExitFlag < 0) {
                    goto label2488;
                }
                HuPrcSleep(-1);
            case 7:
                HuPrcSleep(0x1E);
            label2488:
                mbItemBtnF = 0;

                // END OF TURN: Check for end of round minigames
                if (system->current_player_index >= 3) {
                    MBMasuEventCall(-3, 7);
                    Hu3DMotionReset(MBPlayerGet(3)->player_obj->omObj1->model[0]);
                    mbTurnUnkF = 0;
                    MBStatusItemDispOff();

                    HuPrcChildLink(telopProc, MBMgCallCreate());
                    HuPrcChildWatch();

                    if (system->minigame_index >= 0) {
                        mbGameMode = 0;

                        // Determine minigame type
                        if (system->total_turns >= 0 && system->current_turn >= system->total_turns) {
                            if (GwSystem.wackyWatchUsedState == WATCH_USED) {
                                mbExitFlag = 3;
                            } else {
                                mbExitFlag = 0x23;
                            }
                        } else {
                            mbExitFlag = 3;
                        }
                        mbExitMusFadeF = 1;
                        mbWipeType = WIPE_TUMBLE;

                        for (var_s0_2 = 0; var_s0_2 < 4; var_s0_2++) {
                            MBStatusColorGet(var_s0_2);
                        }

                        HuPrcSleep(-1);
                    }
                }

                // Check for game end condition
                if (MBLast5Check() != 0) {
                    mbGameMode = 0;
                    mbExitFlag = 1;
                    HuPrcSleep(-1);
                }

                HuPrcSleep(4);

                HuPrcChildLink(telopProc, MBScissorWipeOutStart());
                HuPrcChildWatch();

                MBNextPlayerTurn();

                // Hide all players
                for (i = 0; i < 4; i++) {
                    MBPlayerForwardSet(i);
                    MBMotionSet(MBPlayerGet(i)->player_obj, -1, 2);
                }

                HuPrcVSleep();

                if (GwSystem.current_board_index == CHILLY_WATERS && GWBoardFlagCheck(0x12) != 0) {
                    MBMasuDispOn();
                    GWBoardFlagClear(0x12);
                }

                MBCameraRefresh(NULL);
                mbGameMode = 1;
        }
    }
}

static void MBMapScrollModeProc(void) {
    HuPrcVSleep();
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    MBExit();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

static void MBBtnProc(void) {
    Vec2f sp10;
    s32 curPlayerNo;
    s32 i;
    s32 comDecision;
    s32 playerPadNo;

    while (1) {
        HuPrcVSleep();
        if (WipeStatGet() != 0) {
            continue;
        }
        if (mbItemBtnF == 0) {
            continue;
        }
        if (wipeMode == WIPE_MODE_BLANK) {
            continue;
        }
        curPlayerNo = MBPlayerTurnGet();
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            if ((ContBtnDown[i] & START_BUTTON) && GwPlayer[GwSystem.current_player_index].itemTurn == 0) {
                MBSaiSeStop(curPlayerNo);
                MBCameraPos2DGet(&sp10);
                MBCameraPos2DSet(&sp10);
                MBPauseCreate(i);
                MBSaiSeResume(curPlayerNo);
                break;
            }
            if (MBPlayerComCheck(i) == 0) {
                playerPadNo = GwPlayer[i].pad;
                if (i == curPlayerNo) {
                    if (mbSaiBtnF != 0 && (ContBtnDown[playerPadNo] & B_BUTTON)) {
                        if (!(GwSystem.cur_player_used_item & 1)) {
                            MBTurnHelpKill();
                            MBSaiSeStop(i);
                            MBItemSelExec(i, -1);
                            MBSaiSeResume(i);
                        }
                        break;
                    }
                    if (duelCancelEnableF != 0 && (ContBtnDown[playerPadNo] & B_BUTTON)) {
                        MBSaiSeStop(curPlayerNo);
                        MBItemViewExec(curPlayerNo);
                        MBSaiSeResume(curPlayerNo);
                        break;
                    }
                    if (mbCameraBtnF != 0 && (ContBtnDown[playerPadNo] & R_TRIG)) {
                        MBSaiSeStop(curPlayerNo);
                        MBMapScrollExec(playerPadNo);
                        MBSaiSeResume(curPlayerNo);
                        break;
                    }
                    if (mbCameraBtnF != 0 && (ContBtnDown[playerPadNo] & Z_TRIG)) {
                        MBSaiSeStop(curPlayerNo);
                        MBMapFullExec(playerPadNo);
                        MBSaiSeResume(curPlayerNo);
                        break;
                    }
                }
            } else if (mbSaiBtnF != 0 && mbMgHis != 0) {
                if (i == curPlayerNo) {
                    comDecision = MBComItemDecide();
                    if (comDecision == -1) {
                        mbMgHis = 0;
                    } else {
                        MBTurnHelpKill();
                        MBSaiSeStop(curPlayerNo);
                        MBItemSelExec(curPlayerNo, comDecision);
                        MBSaiSeResume(curPlayerNo);
                    }
                }
            }
        }
    }
}

void MBStart(u32 arg0) {
    GW_PLAYER *player;
    s32 i;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        s16 masuID;
        player = MBPlayerGet(i);
        masuID = MBMasuLinkMasuIdGet(player->clink, player->cidx);
        MBPlayerPosMasuSet(i, masuID);
    }

    MBBackThreadPriHighSet();
    MBCameraSpeedDivSet(1.0f);
    MBCameraSpeedSet(-1.0f);
    Hu3DScreenClearF = 1;
    switch (arg0) {
        case 0:
            switch (mbGameMode) {
                case 0:
                case 1:
                    WipeCreateIn(WIPE_TYPE_NORMAL, 0);
                    MBScissorEmptySet();
                    break;
                default:
                    if (mbWipeTypeNext != -1) {
                        if (mbWipeTypeNext == WIPE_TYPE_NORMAL) {
                            WipeColorSet(255, 255, 255);
                        } else {
                            WipeColorSet(0, 0, 0);
                        }
                        WipeCreateIn(mbWipeTypeNext, 0x10);
                        mbWipeTypeNext = -1;
                        MBPlayerVibrate(0, 0);
                        MBPlayerVibrate(1, 0);
                        MBPlayerVibrate(2, 0);
                        MBPlayerVibrate(3, 0);
                    } else {
                        WipeCreateIn(WIPE_TYPE_PREV, 0x10);
                    }
                    MBCameraZoomSet(mbCameraZoom);
                    MBScissorFullSet();
                    break;
            }
            MBCameraPos3DSet(&GwPlayer[GwSystem.current_player_index].player_obj->coords);
            omAddPrcObj(MBMain, 0xEFFF, 0x3000, 0);
            omAddPrcObj(MBExitProc, 0x1005, 0, 0);
            omPrcSetStatBit(omAddPrcObj(MBBtnProc, 0x1001, 0, 0), OM_STAT_NOALLPAUSE);
            mbCameraBtnF = 0;
            mbItemBtnF = 0;
            mbSaiBtnF = 0;
            duelCancelEnableF = 0;
            omAddPrcObj(MBCameraFocusProc, 0x1005, 0, 0);
            MBCameraFocusModeSet(1);
            if (msmMusGetVolume(HuAudMusNo) < 0x7F) {
                MBSeqVolUpStart();
                return;
            }
            return;
        case 1:
            MBCameraPos3DSet(&GwPlayer[GwSystem.current_player_index].player_obj->coords);
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                MBStatusColorSet(i, MBPlayerGet(i)->color);
            }
            omAddPrcObj(MBExitProc, 0x1005, 0, 0);
            omPrcSetStatBit(omAddPrcObj(MBMapScrollModeProc, 0x1005, 0, 0), OM_STAT_NOALLPAUSE);
            mbCameraBtnF = 1;
            return;
        case 2:
            MBStatusHideAll();
            MBCameraFocusModeSet(0);
            break;
    }
}

void MBExitReturnSet(s16 arg0) {
    ditherBak.unk_02 = 1;
    mbExitFlag = 0x40;
    mbWipeType = arg0;
    mbExitMusFadeF = 0;
}

void MBWipeTypeNextSet(s32 arg0) {
    mbWipeTypeNext = arg0;
}

void MBExitOvlCallEx(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    mbExitOvlNo = arg0;
    mbExitOvlEvent = arg1;
    mbExitFlag = 8;
    mbWipeType = arg2;
    mbExitMusFadeF = arg3;
}

void MBExitOvlCall(s32 arg0, s16 arg1, s16 arg2) {
    MBExitOvlCallEx(arg0, arg1, arg2, 0);
}

void MBExitReq(s32 arg0) {
    omSysExitReq = 1;
}

void MBExitBoardSet(s16 arg0, s16 arg1) {
    mbExitFlag = 0x10;
    mbWipeType = arg0;
    mbExitMusFadeF = arg1;
    MBBoardReturnOff();
}

s16 MBExitFlagGet(void) {
    return mbExitFlag;
}

void MBCameraRefresh(Vec *arg0) {
    f32 temp_f20;
    f32 temp_f22;

    MBBackStreamStop();
    MBBackStreamStart();
    temp_f22 = MBCameraSpeedGet();
    MBCameraSpeedSet(-1.0f);
    temp_f20 = MBCameraSpeedDivGet();
    MBCameraSpeedDivSet(1.0f);
    MBBackThreadPriHighSet();

    if (arg0 == NULL) {
        arg0 = &MBPlayerGet(CUR_PLAYER)->player_obj->coords;
    }

    MBCameraPos3DSet(arg0);
    HuPrcVSleep();
    MBCameraSpeedDivSet(temp_f20);
    MBCameraSpeedSet(temp_f22);
}
