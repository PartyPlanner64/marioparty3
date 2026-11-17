#include "common_board.h"
#include "mgcall.h"
#include "model.h"
#include "back.h"
#include "player.h"
#include "status.h"
#include "main.h"
#include "move.h"
#include "vibrate.h"
#include "window.h"
#include "sai.h"
#include "item.h"
#include "helpwin.h"
#include "scroll.h"
#include "mapfull.h"
#include "pause.h"
#include "ksuit.h"
#include "coinchange.h"
#include "game/mallocblock.h"
#include "game/malloc.h"

typedef struct TelopData {
    s32 unk_00;
    s32 playerNo;
    char unk_08[8];
} TelopData;

// void omAllPause(void);
// void MBBackRefresh(Vec *, s32);
// void MBPlayerPosMasuSet(s16, s16);
// void MBPlayerMasuSwap(s16, s16);
// void MBCameraFocusModeSet(s32);
// void MBPlayerPosFixSet(s32, s32);
// void omAllUPause(void);
// void MBKettouResultExec(void);
// void MBKettouComResultSet(void);
// s32 MBKettouExec(GW_PLAYER *);
// void MBGameModeKettouSet(void);
// void MBMasuCurSet(s16);
// void MBStatusItemIconSprReinit(s32);
// void GMesSprClose(char*);
// void HuWinMesConv(u8 *, s32);
// s32 HuWinExCreateStyled(s32 arg0, s32 arg1, s32 arg2);
// extern void sincosdf(f32, f32*, f32*);
// void HuWinExCleanup(s16);
// void MBGameModeWarpSet(void);
// f32 sindf(f32);
// void MBStatusItemScaleSet(s32, s32, f32, f32);
// void MBSaiDispOff(void);
// void MBSaiDispOn(s32 playerNo);
// void MBTurnHelpCreate(void);
// static void MBItemKSuitEnd(void);
// s16 GameMesStrInit(char* arg0, char* arg1, s32 arg2, s16 arg3, u16 arg4);
// s32 MBMgTypeCalc(void);

extern Vec mbCameraFocusPos;
extern u8 mbTelopFlag;
extern s16 mbItemWarpPlayerA;
extern s16 mbItemWarpPlayerB;
extern f32 mbCameraScrPos[2];
extern s16 mbTelopMgTypeStrNo;
extern s16 mbTelopPlayerGrp;
extern s16 mbTelopPlayerAnim[];
extern omObjData* mbTelopPlayerObj;
extern omObjData* mbTelopLast5Obj;
extern GAMEMES mbTelopMes;
extern s16 mbTelopLast5Grp[];
extern s16 mbTelopLast5Anim[];
extern s16 mbMasuBlockExtTbl[];
extern s16 mbMasuBlockExtNum;
extern s16 mbMasuBlockTbl[];
extern s16 mbMasuBlockNum;
extern Vec mbGuideCameraEye;
extern Vec mbGuideCameraAt;
extern Vec mbGuideCameraUp;
extern Vec mbGuideCameraViewSize;
extern Vec mbGuideCameraViewPos;
extern Object* mbTelopMgTypeMdl;
extern s32 mbTelopMgTypeY;
extern s32 mbItemScaleEffF;
extern s32 mbItemSelComNo;
extern s32 Hu3DSubMtxStackPrev[];

typedef struct SomeStruct {
    u8 unk_00[10];
} SomeStruct;

extern SomeStruct mbTelopLast5FrameTbl;
extern s32 mbTelopLast5Turn;

typedef struct SomeStruct2 {
    u16 unk_00[8];
} SomeStruct2;

extern SomeStruct2 mbTelopPlayerSprTbl;

s32 mbItemSelNo = -1;
u8 mbItemPriceTbl[] = { 5, 5, 5, 5, 5, 5, 10, 10, 10, 10, 10, 15, 10, 10, 20, 255, 255, 255, 255, 30 };
s32 mbItemComWeightTbl[] = { 3, 1, 2, 4, 3, 2, 4, 2, 3, 5, 5, 6, 3, 3, 7, 4, 6, 6, 6 };
s32 mbItemComShopWeightTbl[] = { 3, 1, 2, 4, 3, 2, 4, 2, 3, 5, 5, 8, 1, 3, 10, 1, 7, 6, 9 };
s32 mbItemCharSprTbl[] = { 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71 };
extern char *mbCharNameStrTbl[];
extern s32 (*MBItemFunctions[])(void);
extern s16 mbItemSelPosTbl[][2];
extern s32 mbItemDescMesTbl[];
extern s16 mbItemDescCharTbl[];
extern char *mbTelopMgTypeStrTbl[];
extern s8 mbTelopMgTypeLenTbl[];
extern s8 mbTelopMgTypeXTbl[];

extern const char mbMgType1vs1Str[];
extern const char mbMgTypeBattleStr[];
extern const char mbMgTypeItemStr[];
extern const char mbMgType2vs2Str[];
extern const char mbMgType1vs3Str[];
extern const char mbMgType4PStr[];

// TODO: fix (u8*)arg1 hack
void MBCharNameMesConv(s32 arg0, char *arg1) {
    if (arg0 == CUR_PLAYER) {
        arg0 = GwSystem.current_player_index;
    }
    HuWinMesConv((u8 *)arg1, (s32)mbCharNameStrTbl[GwPlayer[arg0].chr]);
}

void MBItemWarpBlockSwapInit(void) {
    mbItemWarpPlayerA = -1;
    mbItemWarpPlayerB = -1;
}

s16 MBPlayerOtherCheck(s32 arg0, s32 arg1) {
    return ((arg1 ^ arg0) << 0x10) != 0;
}

static void MBItemWarpPlayerSet(s16 arg0, s16 arg1) {
    if (arg1 == MBPlayerTurnGet()) {
        mbItemWarpPlayerA = arg1;
        mbItemWarpPlayerB = arg0;
        return;
    }
    mbItemWarpPlayerA = arg0;
    mbItemWarpPlayerB = arg1;
}

s32 MBItemWarpBlockSwapPlayerSet(s16 arg0) {
    MBItemWarpPlayerSet(MBPlayerGet(CUR_PLAYER)->turn, arg0);
    return 1;
}

static void MBItemWarpBlockSwap(void) {
    GW_PLAYER *temp_s4;
    GW_PLAYER *temp_s5;
    GW_PLAYER *playerCopy;
    Object *playerObj;
    Object *playerObjSecond;
    Object *model;
    Vec *temp_s0;
    f32 temp_f0;
    f32 temp_f2;
    s32 i;

    MBCameraFocusModeSet(0);
    temp_s4 = MBPlayerGet(mbItemWarpPlayerA);
    temp_s5 = MBPlayerGet(mbItemWarpPlayerB);
    temp_s4->stat |= 4;
    temp_s5->stat |= 4;
    playerObj = temp_s4->player_obj;
    playerObjSecond = temp_s5->player_obj;
    HuAudFXPlay(0x107);
    model = MBModelCreate(0x1C, NULL);
    MBMotionSet(model, -1, 0);
    HuVecCopy3F(&model->coords, &playerObj->coords);

    for (i = 0; i < 15; i++) {
        temp_f0 = (f32)i / 15.0f;
        temp_f2 = 1.0f - temp_f0;
        temp_f0 += 1.0f;
        playerObj->scale.x = temp_f2;
        playerObj->scale.y = temp_f0;
        playerObj->scale.z = temp_f2;
        playerObj->velocity.x += 6.0f;
        HuPrcVSleep();
    }

    playerObj->scale.x = 0.0f;
    playerObj->scale.y = 0.0f;
    playerObj->scale.z = 0.0f;

    HuPrcVSleep();
    playerObj->flags &= ~2;
    MBModelDispOff(playerObj);
    MBModelKill(model);
    HuAudFXPlay(0x107);
    model = MBModelCreate(0x1C, NULL);
    MBMotionSet(model, -1, 0);
    HuVecCopy3F(&model->coords, &playerObjSecond->coords);

    for (i = 0; i < 15; i++) {
        temp_f0 = (f32)i / 15.0f;
        temp_f2 = 1.0f - temp_f0;
        temp_f0 += 1.0f;
        playerObjSecond->scale.x = temp_f2;
        playerObjSecond->scale.y = temp_f0;
        playerObjSecond->scale.z = temp_f2;
        playerObjSecond->velocity.x += 6.0f;
        HuPrcVSleep();
    }

    playerCopy = temp_s4;
    MBModelKill(model);
    MBPlayerMasuSwap(mbItemWarpPlayerA, mbItemWarpPlayerB);
    MBPlayerPosMasuSet(mbItemWarpPlayerA, MBMasuLinkMasuIdGet(playerCopy->clink, temp_s4->cidx));
    MBPlayerPosMasuSet(mbItemWarpPlayerB, MBMasuLinkMasuIdGet(temp_s5->clink, temp_s5->cidx));
    HuAudFXPlay(0x107);
    model = MBModelCreate(0x1C, NULL);
    MBMotionSet(model, -1, 0);
    HuVecCopy3F(&model->coords, &playerObjSecond->coords);

    for (i = 14; i >= 0; i--) {
        temp_f0 = (f32)i / 15.0f;
        temp_f2 = 1.0f - temp_f0;
        temp_f0 += 1.0f;
        playerObjSecond->scale.x = temp_f2;
        playerObjSecond->scale.y = temp_f0;
        playerObjSecond->scale.z = temp_f2;
        playerObjSecond->velocity.x -= 6.0f;
        HuPrcVSleep();
    }

    MBModelKill(model);
    MBPlayerVibrate(mbItemWarpPlayerB, 3);
    WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
    HuPrcSleep(0x10);
    MBBackRefresh(&playerObj->coords, 0);
    MBPlayerPosFixSet(0, 1);
    MBPlayerPosFixSet(1, 1);
    MBPlayerPosFixSet(2, 1);
    MBPlayerPosFixSet(3, 1);
    WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
    HuPrcSleep(0x10);
    HuAudFXPlay(0x107);
    playerObj->flags |= 2;
    MBModelDispOn(playerObj);
    model = MBModelCreate(0x1C, NULL);
    MBMotionSet(model, -1, 0);
    HuVecCopy3F(&model->coords, &playerObj->coords);

    for (i = 14; i >= 0; i--) {
        temp_f0 = (f32)i / 15.0f;
        temp_f2 = 1.0f - temp_f0;
        temp_f0 += 1.0f;
        playerObj->scale.x = temp_f2;
        playerObj->scale.y = temp_f0;
        playerObj->scale.z = temp_f2;
        playerObj->velocity.x -= 6.0f;
        HuPrcVSleep();
    }

    MBModelKill(model);
    MBPlayerVibrate(mbItemWarpPlayerA, 3);
    playerCopy->stat &= ~4;
    temp_s5->stat &= ~4;

    if (mbItemWarpPlayerA != MBPlayerTurnGet()) {
        HuPrcSleep(15);
        WipeCreateOut(WIPE_TYPE_NORMAL, 16);
        HuPrcSleep(16);
        MBBackRefresh(&MBPlayerGet(CUR_PLAYER)->player_obj->coords, 0);
        WipeCreateIn(WIPE_TYPE_NORMAL, 16);
        HuPrcSleep(16);
    }

    HuPrcSleep(15);
    MBDlgWinInsertCreate(-1, 0x3A10, mbCharNameMesTbl[GwPlayer[mbItemWarpPlayerA].chr], mbCharNameMesTbl[GwPlayer[mbItemWarpPlayerB].chr], 0, 0, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    MBCameraFocusModeSet(1);
    MBItemWarpBlockSwapInit();
    omDelPrcObj(NULL);
}

void MBItemWarpBlockSwapCreate(void) {
    Process *proc;

    proc = HuPrcCurrentGet();
    HuPrcChildLink(proc, omAddPrcObj(MBItemWarpBlockSwap, 0x1003, 0, 0));
    HuPrcChildWatch();
}

s16 MBItemWarpPlayerGet(void) {
    return mbItemWarpPlayerA;
}

void MBItemHookSet(s32 idx, void (*func)()) {
    MBItemSubFunctions[idx] = func;
}

s32 MBItemNullExec(void) {
    MBDlgWinInsertCreate(-1, 0x3A00, mbCharNameMesTbl[GwPlayer[GwSystem.current_player_index].chr], 0, 0, 0, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    return 0;
}

s32 MBItemKinokoExec(void) {
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if ((MBSaiTypeGet(system->current_player_index) == (MB_MAX_PLAYERS - 1)) && player->rev & 0x80) {
        player->rev &= ~0x80;
        MBDlgWinExec(-1, 0x3A2B);
    } else {
        if (MBSaiTypeGet(system->current_player_index) == (MB_MAX_PLAYERS - 1)) {
            MBDlgWinExec(-1, 0x3A27);
        }
        if (player->rev & 0x80) {
            player->rev &= ~0x80;
            MBDlgWinExec(-1, 0x3A29);
        }
    }

    MBSaiKill(GwSystem.current_player_index);
    MBItemSubFunctions[IFUNC_MUSHROOM]();
    GwPlayer[GwSystem.current_player_index].itemNo[mbItemSelNo] = ITEM_NONE;
    MBItemRemoveEmpty(GwSystem.current_player_index);
    MBSaiNumSet(GwSystem.current_player_index, 2);
    MBPlayerVibrate(CUR_PLAYER, 2);
    MBSaiCreate(GwSystem.current_player_index);
    HuPrcSleep(15);
    return 1;
}

s32 MBItemKeymanExec(void) {
    MBItemSubFunctions[IFUNC_17]();
    return 1;
}

s32 MBItemNKinokoExec(void) {
    MBItemSubFunctions[IFUNC_8]();
    GwPlayer[GwSystem.current_player_index].itemNo[mbItemSelNo] = ITEM_NONE;
    MBItemRemoveEmpty(GwSystem.current_player_index);
    MBItemSubFunctions[IFUNC_10]();
    return 1;
}

s32 MBItemRKinokoExec(void) {
    void *temp_s0;

    MBItemSubFunctions[IFUNC_8]();
    GwPlayer[GwSystem.current_player_index].itemNo[mbItemSelNo] = ITEM_NONE;
    MBItemRemoveEmpty(GwSystem.current_player_index);
    MBItemSubFunctions[IFUNC_11]();
    return 1;
}

s32 MBItemShopPhoneExec(void) {
    MBItemSubFunctions[IFUNC_14]();
    return 1;
}

s32 MBItemKoopaPhoneExec(void) {
    MBItemSubFunctions[IFUNC_15]();
    return 1;
}

s32 MBItemStarYokeExec(void) {
    MBItemSubFunctions[IFUNC_16]();
    return 1;
}

s32 MBItemRobBoxExec(void) {
    MBItemSubFunctions[IFUNC_PLUNDER_CHEST]();
    return 1;
}

s32 MBItemKettouExec(void) {
    s32 temp_v0;

    MBItemSubFunctions[IFUNC_7]();
    GwPlayer[GwSystem.current_player_index].itemNo[mbItemSelNo] = ITEM_NONE;
    MBItemRemoveEmpty(GwSystem.current_player_index);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);

    if (MBSaiTypeGet(GwSystem.current_player_index) == (MB_MAX_PLAYERS - 1)) {
        GWBoardFlagSet(0x17);
    } else {
        GWBoardFlagClear(0x17);
    }

    GwSystem.unk_58 = ~(1 << MBPlayerTurnGet());
    GwSystem.playerIndexVisitingBowser = ((1 << MBPlayerTurnGet()) | 0x8000);
    temp_v0 = MBKettouExec(MBPlayerGet(CUR_PLAYER)); // The original call omits the second argument.

    if (temp_v0 != 0) {
        if (temp_v0 == 1) {
            MBGameModeKettouSet();
            MBTurnHelpKill();
            omAllUPause();
            HuPrcSleep(-1);
        }
        MBKettouComResultSet();
        MBKettouResultExec();
    }
    return 1;
}

s32 MBItemWarpBlockExec(void) {
    GW_PLAYER *temp_s0;
    GW_SYSTEM *system = &GwSystem;

    temp_s0 = MBPlayerGet(CUR_PLAYER);
    GwPlayer[system->current_player_index].itemNo[mbItemSelNo] = ITEM_NONE;
    MBItemRemoveEmpty(system->current_player_index);

    if (MBSaiTypeGet(system->current_player_index) == (MB_MAX_PLAYERS - 1) && (temp_s0->rev & 0x80)) {
        temp_s0->rev = temp_s0->rev & 0x7F;
        MBDlgWinExec(-1, 0x3A13);
    } else {
        if (MBSaiTypeGet(system->current_player_index) == (MB_MAX_PLAYERS - 1)) {
            MBDlgWinExec(-1, 0x3A11);
        }

        if (temp_s0->rev & 0x80) {
            temp_s0->rev = temp_s0->rev & 0x7F;
            MBDlgWinExec(-1, 0x3A12);
        }
    }

    MBGameModeWarpSet();
    MBItemSubFunctions[IFUNC_WARP_BLOCK]();
    return 1;
}

s32 MBItemSKinokoExec(void) {
    GW_PLAYER *temp_s0;
    GW_SYSTEM *system = &GwSystem;

    temp_s0 = MBPlayerGet(CUR_PLAYER);
    if (MBSaiTypeGet(system->current_player_index) == (MB_MAX_PLAYERS - 1) && (temp_s0->rev & 0x80)) {
        temp_s0->rev &= 0x7F;
        MBDlgWinExec(-1, 0x3A2C);
    } else {
        if (MBSaiTypeGet(system->current_player_index) == (MB_MAX_PLAYERS - 1)) {
            MBDlgWinExec(-1, 0x3A28);
        }

        if (temp_s0->rev & 0x80) {
            temp_s0->rev &= 0x7F;
            MBDlgWinExec(-1, 0x3A2A);
        }
    }

    MBSaiKill(GwSystem.current_player_index);
    MBItemSubFunctions[IFUNC_MUSHROOM]();
    GwPlayer[GwSystem.current_player_index].itemNo[mbItemSelNo] = ITEM_NONE;
    MBItemRemoveEmpty(GwSystem.current_player_index);
    MBSaiNumSet(GwSystem.current_player_index, 3);
    MBPlayerVibrate(-1, 3);
    MBSaiCreate(GwSystem.current_player_index);
    HuPrcSleep(0xF);
    return 1;
}

s32 MBItemTereBellExec(void) {
    GW_PLAYER *temp_s0;

    temp_s0 = MBPlayerGet(CUR_PLAYER);
    MBItemSubFunctions[IFUNC_7]();
    MBMasuCurSet(MBMasuLinkMasuIdGet(temp_s0->clink, temp_s0->cidx));
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
    MBItemSubFunctions[IFUNC_BOO]();
    GwPlayer[GwSystem.current_player_index].itemNo[mbItemSelNo] = ITEM_NONE;
    MBItemRemoveEmpty(GwSystem.current_player_index);
    MBStatusItemIconSprReinit(-1);
    return 1;
}

s32 MBItemTereYokeSprayExec(void) {
    MBItemSubFunctions[IFUNC_8]();
    GwPlayer[GwSystem.current_player_index].itemNo[mbItemSelNo] = ITEM_NONE;
    MBItemRemoveEmpty(GwSystem.current_player_index);
    MBDlgWinExec(-1, 0x3A1C);
    MBItemSubFunctions[IFUNC_KOOPA_KARD]();
    return 1;
}

s32 MBItemKSuitExec(void) {
    MBItemSubFunctions[IFUNC_MUSHROOM]();
    MBItemSubFunctions[IFUNC_BOWSER_SUIT_BEGIN]();
    GwPlayer[GwSystem.current_player_index].itemTurn = 1;
    GwPlayer[GwSystem.current_player_index].itemNo[mbItemSelNo] = ITEM_NONE;
    MBItemRemoveEmpty(GwSystem.current_player_index);
    return 1;
}

s32 MBItemMajinLampExec(void) {
    GW_PLAYER* temp_s0;
    GW_SYSTEM* system = &GwSystem;

    temp_s0 = MBPlayerGet(CUR_PLAYER);
    GwPlayer[system->current_player_index].itemNo[mbItemSelNo] = ITEM_NONE;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusItemIconSprReinit(-1);
    if (MBSaiTypeGet(system->current_player_index) == 3) {
        if (temp_s0->rev & 0x80) {
            temp_s0->rev &= ~0x80;
            MBDlgWinExec(-1, 0x3A1B);
            MBItemSubFunctions[IFUNC_MAGIC_LAMP]();
            return 1;
        }
    }
    
    if (MBSaiTypeGet(system->current_player_index) == 3) {
        MBDlgWinExec(-1, 0x3A19);
    }
    if (temp_s0->rev & 0x80) {
        temp_s0->rev &= ~0x80;
        MBDlgWinExec(-1, 0x3A1A);
    }        
    
    MBItemSubFunctions[IFUNC_MAGIC_LAMP]();
    return 1;
}


s32 MBItemKoopaCardExec(void) {
    MBItemSubFunctions[IFUNC_8]();
    GwPlayer[GwSystem.current_player_index].itemNo[mbItemSelNo] = ITEM_NONE;
    MBItemRemoveEmpty(GwSystem.current_player_index);
    MBDlgWinExec(-1, 0x3A22);
    MBItemSubFunctions[IFUNC_KOOPA_KARD]();
    return 1;
}

s32 MBItemExchangeBoxExec(void) {
    MBItemSubFunctions[IFUNC_EXHANGE_BOX]();
    return 1;
}

s32 MBItemGambleCoinExec(void) {
    MBItemSubFunctions[IFUNC_20]();
    return 1;
}

s32 MBItemAfter5Exec(void) {
    MBItemSubFunctions[IFUNC_21]();
    return 1;
}

void MBItemKoopaNKinokoExec(void) {
    MBItemSubFunctions[IFUNC_12]();
}

void MBItemKoopaRKinokoExec(void) {
    MBItemSubFunctions[IFUNC_13]();
}

//file split starting here? functions kind of change the general idea of what they accomplish at this point
extern Unk3* mbItemHelpWin1;
extern Unk3* mbItemHelpWin2;
extern Unk3* mbItemHelpWin3;
extern Unk3* mbItemHelpWin4;
extern Unk3* mbItemHelpWin5;
extern Unk3* mbItemHelpWin0;

static void MBItemHelpCreate(void) {
    mbItemHelpWin0 = MBHelpWinCreate(0, 0x84, 0);
    mbItemHelpWin1 = MBHelpWinCreate(0xE, 0x92, 0);
    mbItemHelpWin2 = MBHelpWinCreate(4, 0xA0, 0);
    mbItemHelpWin3 = MBHelpWinCreate(3, 0xAE, 0);
    mbItemHelpWin4 = MBHelpWinCreate(0xB, 0xBC, 0);
    mbItemHelpWin5 = MBHelpWinCreate(0xF, 0xCA, 0);
}

static void MBItemHelpKill(void) {
    if (mbItemHelpWin1 != NULL) {
        MBHelpWinKill(mbItemHelpWin0);
        MBHelpWinKill(mbItemHelpWin1);
        MBHelpWinKill(mbItemHelpWin2);
        MBHelpWinKill(mbItemHelpWin3);
        MBHelpWinKill(mbItemHelpWin4);
        MBHelpWinKill(mbItemHelpWin5);
        mbItemHelpWin1 = NULL;
    }
}

// does pulsing effect of item when hovering over it as an item to use
static void MBItemScaleEff(void) {
    f32 temp_f0;
    f32 var_f20;
    s32 *temp_s0;
    s32 prev;

    temp_s0 = HuPrcCurrentGet()->user_data;
    var_f20 = 0.0f;
    prev = *temp_s0;
    while (*temp_s0 != -1) {
        if (*temp_s0 != prev) {
            MBStatusItemScaleSet(GwSystem.current_player_index, prev, 1.0f, 1.0f);
            var_f20 = 0.0f;
            prev = *temp_s0;
        }
        if (var_f20 > 360.0f) {
            var_f20 -= 360.0f;
        }
        temp_f0 = (sindf(var_f20) * 0.2f) + 1.0f;
        MBStatusItemScaleSet(GwSystem.current_player_index, *temp_s0, temp_f0, temp_f0);
        HuPrcVSleep();
        var_f20 += 13.0f;
    }
    MBStatusItemScaleSet(GwSystem.current_player_index, prev, 1.0f, 1.0f);
    omDelPrcObj(0);
}

static void MBItemScaleEffCreate(void) {
    if (MBItemFindEmpty(-1) != 0) {
        HuSprDispOn(mbItemCursorGrpId, 0);
        omAddPrcObj(MBItemScaleEff, 0x1005U, 0, 0)->user_data = &mbItemScaleEffF;
    }
}

// function that runs immediately when pressing "B" to use an item
static void MBItemSel(void) {
    f32 sp10[2];
    s32 sp1C;
    s32 prevSelectedItemSlot;
    s32 playerNo;
    s32 var_s5;
    s32 playerPadNo;
    void *temp_v0;

    playerNo = (s32)HuPrcCurrentGet()->user_data;
    playerPadNo = GwPlayer[playerNo].pad;

    MBStatusShrink(-1);
    MBStatusItemDispSetAll(1);
    MBStatusGrow(-1);

    mbItemCursorGrpId = HuSprGrpCreate(1, 5);
    temp_v0 = DataRead(mbItemCharSprTbl[GwPlayer[GwSystem.current_player_index].chr]);
    sp1C = HuSprAnimRead(temp_v0);
    DataClose(temp_v0);

    HuSprGrpMemberSet(mbItemCursorGrpId, 0, sp1C, 0);
    HuSprPriSet(mbItemCursorGrpId, 0, 0xA);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);

    if (GwSystem.current_player_index & 1) {
        HuSprAttrSet(mbItemCursorGrpId, 0, HUSPR_ATTR_XLU | HUSPR_ATTR_FLIPX);
    } else {
        HuSprAttrSet(mbItemCursorGrpId, 0, HUSPR_ATTR_XLU);
    }

    var_s5 = 20;

    mbItemSelNo = 0;
    mbItemScaleEffF = 0;

    if (MBItemFindEmpty(-1) == 0) {
        HuSprDispOff(mbItemCursorGrpId, 0);
    } else {
        omAddPrcObj(MBItemScaleEff, 0x1005, 0, 0)->user_data = &mbItemScaleEffF;
    }

    MBStatusItemSprPosGet(GwSystem.current_player_index, mbItemScaleEffF, &sp10[0], &sp10[1]);
    MBStatusItemPriSet(GwSystem.current_player_index, mbItemScaleEffF, ((GwSystem.current_player_index * 5) + 0x478F));
    HuSprPosSet(mbItemCursorGrpId, 0,
                        mbItemSelPosTbl[GwSystem.current_player_index][0] + sp10[0],
                        mbItemSelPosTbl[GwSystem.current_player_index][1] + sp10[1]);

    MBItemHelpCreate();

    while (1) {
        prevSelectedItemSlot = mbItemSelNo;

        if (GwPlayer[GwSystem.current_player_index].itemNo[0] != -1) {
            if (ContBtnDown[playerPadNo] & L_JPAD) {
                do {
                    if (--mbItemSelNo < 0)
                        mbItemSelNo = ARRAY_COUNT(GwPlayer->itemNo) - 1;
                } while (GwPlayer[GwSystem.current_player_index].itemNo[mbItemSelNo] == -1);
            }

            if ((ContBtnDown[playerPadNo] & R_JPAD) || ((mbItemSelNo != mbItemSelComNo) && (var_s5-- == 0) && (MBPlayerComCheck(playerNo) != 0))) {
                var_s5 = 20;
                do {
                    if (++mbItemSelNo >= ARRAY_COUNT(GwPlayer->itemNo))
                        mbItemSelNo = 0;
                } while (GwPlayer[GwSystem.current_player_index].itemNo[mbItemSelNo] == -1);
            }

            if (prevSelectedItemSlot != mbItemSelNo) {
                HuAudFXPlay(1);
                mbItemScaleEffF = mbItemSelNo;
                MBStatusItemSprPosGet(GwSystem.current_player_index, mbItemSelNo, &sp10[0], &sp10[1]);
                HuSprPosSet(mbItemCursorGrpId, 0,
                                    mbItemSelPosTbl[GwSystem.current_player_index][0] + sp10[0],
                                    mbItemSelPosTbl[GwSystem.current_player_index][1] + sp10[1]);
                MBStatusItemPriSet(GwSystem.current_player_index, prevSelectedItemSlot, ((GwSystem.current_player_index * 5) + 0x4790));
                MBStatusItemPriSet(GwSystem.current_player_index, mbItemSelNo, ((GwSystem.current_player_index * 5) + 0x478F));
            }
        }

        if ((ContBtnDown[playerPadNo] & A_BUTTON) || ((MBPlayerComCheck(playerNo) != 0) && (mbItemSelComNo == mbItemSelNo))) {
            mbItemScaleEffF = -1;
            MBItemHelpKill();
            GwSystem.cur_player_used_item |= 1;

            if (MBItemFunctions[GwPlayer[playerNo].itemNo[mbItemSelNo] + 1]() == 0) {
                MBItemHelpCreate();
                GwSystem.cur_player_used_item &= ~1;
                MBStatusItemPriSet(GwSystem.current_player_index, mbItemScaleEffF, ((GwSystem.current_player_index * 5) + 0x478F));
                HuSprPosSet(mbItemCursorGrpId, 0,
                                    mbItemSelPosTbl[GwSystem.current_player_index][0] + sp10[0],
                                    mbItemSelPosTbl[GwSystem.current_player_index][1] + sp10[1]);
            } else {
                break;
            }
        }

        if (!(ContBtnDown[playerPadNo] & B_BUTTON)) {
            if (ContBtnDown[playerPadNo] & U_CBUTTONS) {
                mbItemScaleEffF = -1;
                HuPrcVSleep();
                HuSprDispOff(mbItemCursorGrpId, 0);
                MBItemHelpKill();
                MBItemDescExec(playerNo);
                MBItemHelpCreate();
                mbItemScaleEffF = mbItemSelNo;
                MBItemScaleEffCreate();
            }

            if (ContBtnDown[playerPadNo] & R_TRIG) {
                mbItemScaleEffF = -1;
                HuPrcVSleep();
                HuSprDispOff(mbItemCursorGrpId, 0);
                MBItemHelpKill();
                MBMapScrollExec(playerPadNo);
                MBItemHelpCreate();
                winPauseF = 1;
                omAllPause();
                mbItemScaleEffF = mbItemSelNo;
                MBItemScaleEffCreate();
            }

            if (ContBtnDown[playerPadNo] & Z_TRIG) {
                mbItemScaleEffF = -1;
                HuPrcVSleep();
                HuSprDispOff(mbItemCursorGrpId, 0);
                MBItemHelpKill();
                MBMapFullExec(playerPadNo);
                MBItemHelpCreate();
                winPauseF = 1;
                omAllPause();
                mbItemScaleEffF = mbItemSelNo;
                MBItemScaleEffCreate();
            }

            HuPrcVSleep();
            continue;
        }
        break;
    }

    MBItemHelpKill();
    mbItemScaleEffF = -1;
    HuSprGrpKill(mbItemCursorGrpId);
    HuSprAnimKill(sp1C);

    if (MBStatusItemDispGet(0) != 0) {
        MBStatusShrink(-1);
        MBStatusItemDispSetAll(0);
        MBStatusGrow(-1);
    }

    omDelPrcObj(NULL);
}

void MBItemSelExec(s32 playerNo, s32 arg1) {
    Process* temp_s2;
    Process* temp_v0;

    MBSaiDispOff(playerNo);
    
    winPauseF = 1;
    omAllPause();
    mbItemSelComNo = arg1;
    temp_s2 = HuPrcCurrentGet();
    temp_v0 = omAddPrcObj(MBItemSel, 0x1005, 0x1000, 0);
    temp_v0->user_data = (void*)playerNo;
    omPrcSetStatBit(temp_v0, OM_STAT_NOALLPAUSE);
    HuPrcChildLink(temp_s2, temp_v0);
    HuPrcChildWatch();
    omAllUPause();
    winPauseF = 0;
    MBSaiDispOn(playerNo);
    MBTurnHelpCreate();
}

static void MBItemView(void) {
    s32 playerIdx;
    s32 padNo;

    playerIdx = (s32)(HuPrcCurrentGet()->user_data);
    padNo = GwPlayer[playerIdx].pad;
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(1);
    MBStatusGrow(-1);
    mbItemSelNo = 0;
    mbItemHelpWin2 = MBHelpWinCreate(4, 0xA0, 0);
    mbItemHelpWin5 = MBHelpWinCreate(0xF, 0xAE, 0);
    while (1) {
        if ((ContBtnDown[padNo] & B_BUTTON)) {
            break;
        }
        if (ContBtnDown[padNo] & U_CBUTTONS) {
            MBHelpWinKill(mbItemHelpWin2);
            MBHelpWinKill(mbItemHelpWin5);
            MBItemDescExec(playerIdx);
            mbItemHelpWin2 = MBHelpWinCreate(4, 0xA0, 0);
            mbItemHelpWin5 = MBHelpWinCreate(0xF, 0xAE, 0);
        }
        HuPrcVSleep();      
    }

    MBHelpWinKill(mbItemHelpWin2);
    MBHelpWinKill(mbItemHelpWin5);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
    omDelPrcObj(NULL);
}

void MBItemViewExec(s32 playerNo) {
    Process* temp_s1;
    Process* temp_v0;

    winPauseF = 1;
    omAllPause();
    temp_s1 = HuPrcCurrentGet();
    temp_v0 = omAddPrcObj(MBItemView, 0x1005, 0, 0);
    temp_v0->user_data = (void*)playerNo;
    omPrcSetStatBit(temp_v0, OM_STAT_NOALLPAUSE);
    HuPrcChildLink(temp_s1, temp_v0);
    HuPrcChildWatch();
    omAllUPause();
    winPauseF = 0;
}

static void MBItemDesc(void) {
    s16 sp18[2];
    s16 temp_v0_2;
    s32 playerNo;
    s8 itemID;
    s32 savedItemID;
    s32 padNo;

    playerNo = (s32)(HuPrcCurrentGet()->user_data);
    padNo = GwPlayer[playerNo].pad;
    savedItemID = 0;
    
    if (mbItemSelNo != -1) {
        itemID = GwPlayer[playerNo].itemNo[mbItemSelNo];
        if (itemID != -1) {
            savedItemID = itemID;
        }
    }
    
    HuWinMesMaxSizeBetGet(sp18, 0x3E00, 0x3E0A);
    temp_v0_2 = HuWinExCreate(mbItemDescCharTbl[savedItemID], 0xA0 - (sp18[0] / 2), 0x3C, sp18[0], sp18[1], 0);
    HuWinBGColSet(temp_v0_2, 1, 0xBC, 0xE7);
    HuWinMesSet(temp_v0_2, mbItemDescMesTbl[savedItemID], -1, -1);
    HuWinExAnimIn(temp_v0_2);
    mbItemHelpWin2 = MBHelpWinCreate(0x10, 0xA0, 0);
    mbItemHelpWin3 = MBHelpWinCreate(0x11, 0xAE, 0);
    mbItemHelpWin4 = MBHelpWinCreate(4, 0xBC, 0);
    
    while (1) {
        if ((ContBtnDown[padNo] & B_BUTTON)) {
            break;
        }
        if (ContBtnRep[padNo] & R_CBUTTONS) {
            savedItemID++;
            savedItemID %= 20;
            HuWinHomeClear(temp_v0_2);
            HuWinMesSet(temp_v0_2, mbItemDescMesTbl[savedItemID], -1, -1);
            HuWinExAnimPopIn(temp_v0_2, mbItemDescCharTbl[savedItemID]);
        }
        if (ContBtnRep[padNo] & L_CBUTTONS) {
            savedItemID -= 1;
            if (savedItemID < 0) {
                savedItemID = 19;
            }
            HuWinHomeClear(temp_v0_2);
            HuWinMesSet(temp_v0_2, mbItemDescMesTbl[savedItemID], -1, -1);
            HuWinExAnimPopIn(temp_v0_2, mbItemDescCharTbl[savedItemID]);
        }
        HuPrcVSleep();
             
    }

    MBHelpWinKill(mbItemHelpWin2);
    MBHelpWinKill(mbItemHelpWin3);
    MBHelpWinKill(mbItemHelpWin4);
    HuWinExAnimOut(temp_v0_2, 0);
    HuWinKill(temp_v0_2);
    omDelPrcObj(NULL);
}


void MBItemDescExec(s32 arg0) {
    Process* temp_s2;
    Process* temp_v0;

    temp_s2 = HuPrcCurrentGet();
    temp_v0 = omAddPrcObj(MBItemDesc, 0x1005, 0, 0);
    temp_v0->user_data = (void*)arg0;
    omPrcSetStatBit(temp_v0, OM_STAT_NOALLPAUSE);
    HuPrcChildLink(temp_s2, temp_v0);
    HuPrcChildWatch();
}

char *mbCharNameStrTbl[] = {
    "\x82\x6C\x82\x60\x82\x71\x82\x68\x82\x6E",                 // ＭＡＲＩＯ
    "\x82\x6B\x82\x74\x82\x68\x82\x66\x82\x68",                 // ＬＵＩＧＩ
    "\x82\x6F\x82\x64\x82\x60\x82\x62\x82\x67",                 // ＰＥＡＣＨ
    "\x82\x78\x82\x6E\x82\x72\x82\x67\x82\x68",                 // ＹＯＳＨＩ
    "\x82\x76\x82\x60\x82\x71\x82\x68\x82\x6E",                 // ＷＡＲＩＯ
    "\x82\x63\x82\x6A",                                         // ＤＫ
    "\x82\x76\x82\x60\x82\x6B\x82\x74\x82\x68\x82\x66\x82\x68", // ＷＡＬＵＩＧＩ
    "\x82\x63\x82\x60\x82\x68\x82\x72\x82\x78",                 // ＤＡＩＳＹ
};

s32 (*MBItemFunctions[])(void) = {
    MBItemNullExec,
    MBItemKinokoExec,
    MBItemKeymanExec,
    MBItemNKinokoExec,
    MBItemRKinokoExec,
    MBItemShopPhoneExec,
    MBItemWarpBlockExec,
    MBItemRobBoxExec,
    MBItemKoopaPhoneExec,
    MBItemKettouExec,
    MBItemStarYokeExec,
    MBItemSKinokoExec,
    MBItemTereBellExec,
    MBItemTereYokeSprayExec,
    MBItemKSuitExec,
    MBItemMajinLampExec,
    MBItemKoopaCardExec,
    MBItemExchangeBoxExec,
    MBItemGambleCoinExec,
    MBItemAfter5Exec,
};

Unk3 *mbItemHelpWin1 = NULL;
Unk3 *mbItemHelpWin2 = NULL;
Unk3 *mbItemHelpWin3 = NULL;
Unk3 *mbItemHelpWin4 = NULL;
Unk3 *mbItemHelpWin5 = NULL;
Unk3 *mbItemHelpWin0 = NULL;
s16 mbItemSelPosTbl[][2] = {
    { 5, 5 },
    { -20, 10 },
    { 5, 5 },
    { -20, 10 }
};
s32 mbItemDescMesTbl[] = {
    0x3E00, 0x3E01, 0x3E02, 0x3E03, 0x3E04, 0x3E05, 0x3E06, 0x3E07, 0x3E08, 0x3E09,
    0x3E0A, 0x3E0D, 0x3E0C, 0x3E0B, 0x3E0E, 0x3E10, 0x3E11, 0x3E12, 0x3E13, 0x3E0F
};
s16 mbItemDescCharTbl[] = { 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 51, 52, 53, 54, 50 };

void MBItemKSuitWalkExec(void) {
    s8 sp20[4];
    Vec sp28;
    char sp38[16];
    s32 sp4C;
    GW_PLAYER *curPlayer;
    s16 absSpace;
    s32 temp_s0_2;
    s32 coinsToLose;
    s32 totalCoinsToLose;
    s32 playersPassed;
    s32 curPlayerIndex;
    s32 i;

    curPlayerIndex = GwSystem.current_player_index;
    curPlayer = MBPlayerGet(CUR_PLAYER);
    if (GwPlayer[curPlayerIndex].itemTurn != 0) {
        for (playersPassed = 0, i = 0; i < MB_MAX_PLAYERS; i++) {
            if (i == curPlayerIndex) {
                continue;
            }
            absSpace = MBMasuLinkMasuIdGet(GwPlayer[curPlayerIndex].clink, GwPlayer[curPlayerIndex].cidx);
            if (absSpace == MBMasuLinkMasuIdGet(GwPlayer[i].clink, GwPlayer[i].cidx)) {
                sp20[playersPassed++] = i;
            }
        }
        if (playersPassed != 0) {
            sp4C = MBSaiNumKill(curPlayerIndex);
            MBKSuitMotionSet(-1, 2);
            MBVecForwardSet(&sp28);
            MBVecRotLerpCreate(&curPlayer->player_obj->rot, &sp28, &curPlayer->player_obj->rot, 8);
            HuPrcSleep(8);
            totalCoinsToLose = 0;

            for (i = 0; i < playersPassed; i++) {
                if (GwPlayer[sp20[i]].coin != 0) {
                    if (GwPlayer[sp20[i]].coin < 20) {
                        coinsToLose = GwPlayer[sp20[i]].coin;
                    } else {
                        coinsToLose = 20;
                    }
                    sprintf(sp38, "%2d", coinsToLose);
                    MBDlgWinInsertCreate(-1, 0x3A15, mbCharNameMesTbl[GwPlayer[sp20[i]].chr], (s32)sp38, mbCharNameMesTbl[GwPlayer[curPlayerIndex].chr], 0, 0);
                    temp_s0_2 = -coinsToLose;
                    MBDlgWinClose();
                    totalCoinsToLose += coinsToLose;
                    MBDlgWinKill();
                    PlayerFXPlay(0, sp20[i]);
                    MBCoinChangeStatusCreate(sp20[i], temp_s0_2);
                    MBCoinTakeCreate(sp20[i], temp_s0_2);
                    HuPrcSleep(30);
                } else {
                    MBDlgWinInsertCreate(-1, 0x3A16, mbCharNameMesTbl[GwPlayer[sp20[i]].chr], NULL, 0, 0, 0);
                    MBDlgWinClose();
                    MBDlgWinKill();
                    do {
                    } while (0); // TODO: required to match
                }
            }

            if (totalCoinsToLose != 0) {
                MBCoinChangeCreate(curPlayerIndex, totalCoinsToLose);
                MBCoinTakeCreate(curPlayerIndex, totalCoinsToLose);
                HuPrcSleep(30);
            }
            if (sp4C != 0) {
                MBSaiNumShow(GwSystem.current_player_index);
            }
            MBKSuitMotionSet(0, 2);
        }
    }

    if (Hu3DSubMtxStackPrev[4] == 0) {
        MBItemKSuitEnd();
    }
}

void MBItemKSuitEnd(void) {
    s32 curPlayerIndex = GwSystem.current_player_index;
    if (GwPlayer[curPlayerIndex].itemTurn) {
        MBItemSubFunctions[IFUNC_BOWSER_SUIT_END]();
        GwPlayer[curPlayerIndex].itemTurn = 0;
    }
}

void MBItemMajinLampStarExec(void) {
    MBItemSubFunctions[IFUNC_9]();
}

s32 MBItemFind(s32 playerNo, s32 itemID) {
    s32 i;

    if (playerNo == CUR_PLAYER) {
        playerNo = GwSystem.current_player_index;
    }

    for (i = 0; i < ARRAY_COUNT(GwPlayer->itemNo); i++) {
        if (GwPlayer[playerNo].itemNo[i] == itemID) {
            break;
        }
    }

    if (i == ARRAY_COUNT(GwPlayer->itemNo)) {
        return ITEM_NONE;
    } else {
        return i;
    }
}

s32 MBItemFindEmpty(s32 arg0) {
    if (arg0 == CUR_PLAYER) {
        arg0 = GwSystem.current_player_index;
    }

    return MBItemFind(arg0, -1);
}

void MBItemRemoveEmpty(s32 arg0) {
    s8 *playerItems;
    s32 i;

    if (arg0 == CUR_PLAYER) {
        arg0 = GwSystem.current_player_index;
    }

    playerItems = GwPlayer[arg0].itemNo;

    for (i = 0; i < ARRAY_COUNT(GwPlayer->itemNo) - 1; i++) {
        if (playerItems[i] == ITEM_NONE) {
            playerItems[i] = playerItems[i + 1];
            playerItems[i + 1] = ITEM_NONE;
        }
    }
}

void MBItemSelNoClear(void) {
    mbItemSelNo = -1;
}

s32 MBItemSelNoGet(void) {
    return mbItemSelNo;
}

void MBItemSelNoSet(s32 arg0) {
    mbItemSelNo = arg0;
}

void MBPlayerRevAllSet(void) {
    GW_PLAYER* temp_v0;
    GW_PLAYER* temp_v0_2;
    s32 i;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        temp_v0 = MBPlayerGet(i);
        temp_v0->rev &= ~(0x40 | 0x04 | 0x02);
        temp_v0_2 = MBPlayerGet(i);
        temp_v0_2->rev |= (0x20 | 0x08);
        GwSystem.slow_dice_flags |= (1 << i);
    }
}

void MBPlayerRevAllReset(void) {
    GW_PLAYER* temp_v0;
    s32 i;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        temp_v0 = MBPlayerGet(i);
        temp_v0->rev &= ~(0x20 | 0x04 | 0x02);
        temp_v0->rev |= (0x80 | 0x40 | 0x10);
    }
}

void MBTelopInit(void) {
    mbTelopMgTypeStrNo = -1;
    mbTelopFlag = 0;
    mbTelopPlayerGrp = -1;
    mbTelopPlayerAnim[0] = mbTelopPlayerAnim[1] = -1;
    mbTelopPlayerObj = NULL;
    mbTelopLast5Obj = NULL;
}

void MBTelopClose(void) {
    if (mbTelopFlag & 0x20) {
        GMesSprClose(&mbTelopMes);
    }
    if (mbTelopFlag & 0x10) {
        HuSprGrpKill(mbTelopPlayerGrp);
        HuSprAnimKill(mbTelopPlayerAnim[0]);
        HuSprAnimKill(mbTelopPlayerAnim[1]);
    }
    if (mbTelopPlayerObj != NULL) {
        omDelObj(mbTelopPlayerObj);
        mbTelopPlayerObj = NULL;
    }
    if (mbTelopLast5Obj != NULL) {
        omDelObj(mbTelopLast5Obj);
        mbTelopLast5Obj = NULL;
    }
    mbTelopFlag &= ~(0x20 | 0x10);
}


static void MBTelopLast5Main(omObjData *obj) {
    s32 i;
    f32 scale;

    switch (obj->work[0]) {
    case 0:
        obj->rot.x += 30.0f;
        scale = sindf(obj->rot.x) * 0.5f + 1.0f;
        obj->scale.x = scale;
        HuSprScaleSet(mbTelopLast5Grp[0], 0, scale, scale);
        if (obj->rot.x >= 360.0f) {
            obj->rot.x -= 360.0f;
        }
        break;
    case 1:
        break;

    case 2:
        for (i = 0; i < 2; i++) {
            if (mbTelopLast5Anim[i] != -1) {
                HuSprAnimKill(mbTelopLast5Anim[i]);
            }
            if (mbTelopLast5Grp[i] != -1) {
                HuSprGrpKill(mbTelopLast5Grp[i]);
            }
        }
        mbTelopLast5Obj = 0;
        omDelObj(obj);
        break;
    }
}

static void MBTelopPlayerMain(omObjData* arg0) {
    GW_PLAYER* player;
    s32 i;

    if (arg0->rot.y > 0.0f) {
        arg0->rot.y = arg0->rot.y - 1.0f;
    }
    
    switch (arg0->work[0]) {
    case 0:
        arg0->scale.x += 0.2f;
        HuSprScaleSet(mbTelopPlayerGrp, 0, arg0->scale.x, arg0->scale.x);
        if (arg0->scale.x >= 1.0f) {
            arg0->work[0] = 1;
            arg0->work[1] = 0xC;
            return;
        }
        break;
        
    case 1:
        if (arg0->work[3] == 6) {
            return;
        }
        
        if (arg0->work[1] != 0) {
            arg0->work[1]--;
            return;
        }
        
        if (!(GwPlayer[arg0->work[3]].stat & 1)) {
            if (!(arg0->rot.y <= 0.0f)) {
                if (!(HuPadBtnDown[GwPlayer[arg0->work[3]].pad] & (A_BUTTON | B_BUTTON))) {
                    return;
                }
            }
        }
        arg0->work[0] = 2;
        return;

    case 2:
        arg0->scale.x += 0.2f;
        HuSprScaleSet(mbTelopPlayerGrp, 0, arg0->scale.x, arg0->scale.x);
        HuSprTPLvlSet(mbTelopPlayerGrp, 0, (2.0f - arg0->scale.x) * 256.0f);
        if (arg0->scale.x >= 2.0f) {
            arg0->work[0] = 3;
            return;
        }
        break;
    case 3:
        HuSprGrpKill(mbTelopPlayerGrp);
        HuSprAnimKill(mbTelopPlayerAnim[0]);
        mbTelopPlayerGrp = -1;
        mbTelopPlayerAnim[0] = -1;
        if (mbTelopLast5Obj != NULL) {
            for (i = 0; i < 2; i++) {
                if (mbTelopLast5Anim[i] != -1) {
                    HuSprAnimKill(mbTelopLast5Anim[i]);
                }
                if (mbTelopLast5Grp[i] != -1) {
                    HuSprGrpKill(mbTelopLast5Grp[i]);
                }
            }
            omDelObj(mbTelopLast5Obj);
            mbTelopLast5Obj = NULL;
        }
        mbTelopPlayerObj = 0;
        omDelObj(arg0);
        break;
    }
}

static void MBTelopMgTypeMain(omObjData *obj) {
    s32 i;

    if (obj->work[3] != 0) {
        obj->work[3]--;
        if (obj->work[3] < 2 && (obj->work[0] - 4) < 2) {
            HuAudFXPlay(0x206);
        }
    } else {
        HuVecCopyXYZ(&mbTelopMgTypeMdl->scale /* 0x24 */,
                     obj->trans.z, 1.0f, 1.0f);
        obj->trans.z += 0.12f;
        if (obj->trans.z > 1.0f) {
            obj->trans.z = 1.0f;
        }
    }

    if (obj->work[2] != 0) {
        obj->work[2]--;
        return;
    }

    obj->scale.x += 0.05f;
    if (obj->scale.x >= 1.0f) {
        obj->scale.x = 1.0f;
        obj->rot.z += 20.0f;
        if (obj->rot.z >= 360.0f) {
            obj->rot.z -= 360.0f;
        }
    }

    HuSprPosSet(mbTelopMes.strGId[mbTelopMgTypeStrNo],
        0,
        (obj->rot.x + 80.0f),
        (mbTelopMgTypeY + 2.0f * sindf(obj->rot.z)));

    for (i = 1; mbTelopMgTypeLenTbl[obj->work[0]] >= i; i++) {
        HuSprTPLvlSet(mbTelopMes.strGId[mbTelopMgTypeStrNo], i, (obj->scale.x * 256.0f));
    }
}

static void MBTelopLast5Create(void) {
    omObjData *obj;
    void *data;
    SomeStruct sp18 = mbTelopLast5FrameTbl;

    obj = omAddObj(-0x8000, 0, 0, -1, MBTelopLast5Main);
    mbTelopLast5Obj = obj;
    obj->rot.x = 0.0f;

    if (mbTelopLast5Turn == 0) {
        mbTelopLast5Grp[0] = HuSprGrpCreate(1, 0);
        data = DataRead(0x1301E0);
        mbTelopLast5Anim[0] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(mbTelopLast5Grp[0], 0,
                            mbTelopLast5Anim[0], 0);
        HuSprPriSet(mbTelopLast5Grp[0], 0, 0x10);
        HuSprAttrSet(mbTelopLast5Grp[0], 0, HUSPR_ATTR_XLU);
        HuSprPosSet(mbTelopLast5Grp[0], 0, 0xA0, 0x32);
        mbTelopLast5Anim[1] = -1;
        mbTelopLast5Grp[1] = -1;
        obj->work[0] = 1;
        return;
    }

    mbTelopLast5Grp[0] = HuSprGrpCreate(1, 0);
    data = DataRead(0x1301DF);
    mbTelopLast5Anim[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(mbTelopLast5Grp[0], 0,
                        mbTelopLast5Anim[0],
                        sp18.unk_00[mbTelopLast5Turn]);
    HuSprPriSet(mbTelopLast5Grp[0], 0, 0x10);
    HuSprAttrSet(mbTelopLast5Grp[0], 0, HUSPR_ATTR_XLU);
    HuSprPosSet(mbTelopLast5Grp[0], 0, 0xA0, 0x32);

    mbTelopLast5Grp[1] = HuSprGrpCreate(1, 0);
    data = DataRead(0x1301DE);
    mbTelopLast5Anim[1] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(mbTelopLast5Grp[1], 0,
                        mbTelopLast5Anim[1], 0);
    HuSprPriSet(mbTelopLast5Grp[1], 0, 0x11);
    HuSprAttrSet(mbTelopLast5Grp[1], 0, HUSPR_ATTR_XLU);
    HuSprPosSet(mbTelopLast5Grp[1], 0, 0xA0, 0x32);
    obj->work[0] = 0;
}

static void MBTelopPlayerCreate(s32 arg0) {
    omObjData* temp_v0_2;
    void* temp_v0;
    SomeStruct2 sp18 = mbTelopPlayerSprTbl;

    mbTelopPlayerGrp = HuSprGrpCreate(1U, 0);
    temp_v0 = DataRead(sp18.unk_00[GwPlayer[arg0].chr] | 0x130000);
    mbTelopPlayerAnim[0] = HuSprAnimRead(temp_v0);
    DataClose(temp_v0);
    HuSprGrpMemberSet(mbTelopPlayerGrp, 0, mbTelopPlayerAnim[0], 0);
    HuSprPriSet(mbTelopPlayerGrp, 0, 0x10);
    HuSprAttrSet(mbTelopPlayerGrp, 0, HUSPR_ATTR_XLU);
    HuSprPosSet(mbTelopPlayerGrp, 0, 0xA0, 0x78);
    temp_v0_2 = omAddObj(-0x8000, 0U, 0U, -1, MBTelopPlayerMain);
    mbTelopPlayerObj = temp_v0_2;
    
    temp_v0_2->scale.x = 0;
    temp_v0_2->rot.x = 180.0f;
    temp_v0_2->rot.y = 150.0f;
    temp_v0_2->work[2] = 30;
    temp_v0_2->work[0] = 0;
    temp_v0_2->work[1] = 12;
    
    if (mbTelopLast5Obj != 0) {
        temp_v0_2->work[1] = 24;
    }
    temp_v0_2->work[3] = arg0;
    if (arg0 >= 4) {
        temp_v0_2->work[3] = 4;
    }
}

s32 MBTelopPlayerCheck(void) {
    return mbTelopFlag & 4;
}

void MBTelopPlayerKill(void) {
    HuSprGrpKill(mbTelopPlayerGrp);
    HuSprAnimKill(mbTelopPlayerAnim[0]);
    HuSprAnimKill(mbTelopPlayerAnim[1]);
    omDelObj(mbTelopPlayerObj);
    mbTelopPlayerObj = 0;
    mbTelopFlag &= ~(0x20 | 0x10 | 0x08 | 0x04);
}

void MBTelopMgTypeCreate(s32 arg0, u32 arg1) {
    f32 sp18[2];
    Object* modelObj;
    omObjData* temp_v0_2;
    s32 i;
    s32 var_a0;
    s32 var_s1;

    if (!(mbTelopFlag & 4) && ((var_s1 = MBMgTypeCalc(), (((~var_s1 == 0) | (arg0 != 0)) == 0)) || (var_s1 = arg0 + 2, (arg0 != 0)))) {
        modelObj = MBModelFileCreate(0x130204, -1, 1.8f, 0, 0);
        mbTelopMgTypeMdl = modelObj;
        Hu3DModelAttrSet(modelObj->omObj1->model[0], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_OFF);
        Hu3DModelLayerSet(mbTelopMgTypeMdl->omObj1->model[0], 0x1800U);
        Hu3DModelRemakeStatic(mbTelopMgTypeMdl->omObj1->model[0]);
        MBModelTempAllocFree(mbTelopMgTypeMdl);
        HuVecCopy3F(&mbTelopMgTypeMdl->coords, &mbCameraFocusPos);
        HuVecCopyXYZ(&mbTelopMgTypeMdl->scale, 0.0f, 1.0f, 1.0f);
        mbTelopMgTypeMdl->coords.y += 56.0f;
        mbTelopMgTypeStrNo = GameMesStrInit(&mbTelopMes, mbTelopMgTypeStrTbl[var_s1], 0, 0, 0U);
        MBCamera3Dto2D(&mbTelopMgTypeMdl->coords, sp18);
        mbTelopMgTypeY = (sp18[1] - 14.0f);
        mbTelopMgTypeY = mbTelopMgTypeY + ((1.3f - MBCameraZoomGet()) * 50.0f);
        HuSprPosSet(mbTelopMes.strGId[mbTelopMgTypeStrNo], 0, (mbTelopMgTypeXTbl[var_s1] + 0x50), mbTelopMgTypeY);
        
        for (i = 1; mbTelopMgTypeLenTbl[var_s1] >= i; i++) {
            HuSprTPLvlSet(mbTelopMes.strGId[mbTelopMgTypeStrNo], i, 0);
        }
        
        temp_v0_2 = omAddObj(-0x8000, 0, 0, -1, MBTelopMgTypeMain);
        mbTelopPlayerObj = temp_v0_2;
        temp_v0_2->scale.x = 0.0f;
        temp_v0_2->trans.x = 400.0f;
        temp_v0_2->trans.z = 0.0f;
        temp_v0_2->rot.x = mbTelopMgTypeXTbl[var_s1];
        temp_v0_2->rot.y = 0.0f;
        temp_v0_2->rot.z = 0.0f;
        temp_v0_2->work[0] = var_s1;
        temp_v0_2->work[1] = mbTelopMgTypeStrNo;
        temp_v0_2->work[2] = arg1 + 8;
        temp_v0_2->work[3] = arg1;
        mbTelopFlag = 38;
        if (var_s1 >= 3) {
            MBMgCallListCreate(var_s1 - 3);
        } else {
            MBMgCallListCreate(-1);
        }
    }
}

s32 MBTelopMgTypeStatGet(void) {
    return mbTelopFlag & (8 | 4);
}

void MBTelopMgTypeKill(void) {
    MBModelKill(mbTelopMgTypeMdl);
    omDelObj(mbTelopPlayerObj);
    mbTelopPlayerObj = NULL;
    GMesSprClose(&mbTelopMes);
    mbTelopFlag &= ~(0x20 | 0x10 | 0x08 | 0x04);
}

static void MBTelopMain(void) {
    s32 temp_v0;
    s32 temp_v1;
    TelopData* temp_s0;

    temp_s0 = HuPrcCurrentGet()->user_data;
    while (1) {
        temp_v0 = temp_s0->unk_00;
        switch (temp_v0) {
        case 0:
            HuAudFXPlay(0x10C);
            if (temp_s0->playerNo == 0) {
                s32 turnsRemaining = GwSystem.total_turns - GwSystem.current_turn;
                mbTelopLast5Turn = turnsRemaining;
                if (turnsRemaining >= 0) {
                    if (turnsRemaining < 5) {
                        MBTelopLast5Create();
                    } else if (turnsRemaining == 9) {
                        MBTelopLast5Create();
                    }
                }
            }
            MBTelopPlayerCreate(temp_s0->playerNo);
            temp_s0->unk_00++;
            break;
        case 1:
            if (mbTelopPlayerGrp == -1) {
                omDelPrcObj(NULL);
            }
            break;
        }
        HuPrcVSleep();
    }
}

Process* MBTelopCreate(s32 playerNo) {
    Process* proc;
    TelopData* telopData;

    proc = omAddPrcObj(MBTelopMain, 0, 0, 0x40);
    telopData = HuMemMemoryAlloc(proc->heap, sizeof(TelopData));
    proc->user_data = telopData;
    telopData->unk_00 = 0;
    telopData->playerNo = playerNo;
    return proc;
}

static void MBGuideCameraCreate(void) {
    Hu3DCameraPerspectiveSet(1, 40.0f, 80.0f, 8000.0f);
    Hu3DCameraPosSetV(1, &mbGuideCameraEye, &mbGuideCameraAt, &mbGuideCameraUp);
    Hu3DCamUpdateMtx(1);
    Hu3DCameraViewportSet(1, &mbGuideCameraViewSize, &mbGuideCameraViewPos);
}

static void MBGuideMain(void) {
    while (1) {
        MBGuideCameraCreate();
        HuPrcVSleep();       
    }
}

UnkMBGuideData* MBGuideCreate(u32* arg0, s32 arg1) {
    s32 var_a0;
    s32 var_a2;
    s32 var_a1;
    f32 var_f0;
    f32 var_f1;
    HmfModel* temp_a2;
    HmfModel* temp_hmf;
    Object* temp_v0_2;
    Process* temp_v0_7;
    UnkMBGuideData* temp_v0;
    s32 temp;

    temp_v0 = HuMemMemoryAllocTemp(sizeof(UnkMBGuideData));
    if (temp_v0 != NULL) {
        temp_v0_2 = MBModelCreate(0x3B, arg0);
        temp_v0->obj = temp_v0_2;
        temp_v0_2->flags |= 1;

        Hu3DModelCameraSet(temp_v0->obj->omObj1->model[0], HU3D_CAM1);

        temp_a2 = &Hu3DData[temp_v0->obj->omObj1->model[0]];
        sincosdf(15.0f, &temp_a2->mtx[1][2], &temp_a2->mtx[1][1]);

        Hu3DData[temp_v0->obj->omObj1->model[0]].mtx[2][1] = -Hu3DData[temp_v0->obj->omObj1->model[0]].mtx[1][2];

        temp_hmf = &Hu3DData[temp_v0->obj->omObj1->model[0]];
        temp_hmf->mtx[2][2] = temp_hmf->mtx[1][1];

        temp_hmf = &Hu3DData[temp_v0->obj->omObj1->model[0]];
        var_f0 = 0.0f;
        temp_hmf->mtx[3][2] = var_f0;
        temp_hmf->mtx[3][1] = var_f0;
        temp_hmf->mtx[3][0] = var_f0;
        temp_hmf->mtx[2][3] = var_f0;
        temp_hmf->mtx[2][0] = var_f0;
        temp_hmf->mtx[1][3] = var_f0;
        temp_hmf->mtx[1][0] = var_f0;
        temp_hmf->mtx[0][3] = var_f0;
        temp_hmf->mtx[0][2] = var_f0;
        temp_hmf->mtx[0][1] = var_f0;

        temp_hmf = &Hu3DData[temp_v0->obj->omObj1->model[0]];
        var_f1 = 1.0f;
        temp_hmf->mtx[3][3] = var_f1;
        temp_hmf->mtx[0][0] = var_f1;

        temp_v0_7 = omAddPrcObj(MBGuideMain, 0x4000U, 0, 0);
        temp_v0->unk_04 = temp_v0_7;
        temp_v0_7->user_data = temp_v0;

        temp_v0->spriteGroup = 0x69;

        mbGuideCameraEye.x = var_f0;
        mbGuideCameraEye.y = var_f0;
        mbGuideCameraEye.z = 120.0f;

        mbGuideCameraAt.x = var_f0;
        mbGuideCameraAt.y = var_f0;
        mbGuideCameraAt.z = var_f0;

        mbGuideCameraUp.x = var_f0;
        mbGuideCameraUp.y = var_f1;
        mbGuideCameraUp.z = var_f0;

        mbGuideCameraViewSize.x = 1280.0f;
        mbGuideCameraViewSize.y = 960.0f;
        mbGuideCameraViewSize.z = 511.0f;

        mbGuideCameraViewPos.x = 240.0f;
        mbGuideCameraViewPos.y =
            (f32)temp_v0->spriteGroup * 4.0f + 480.0f;
        mbGuideCameraViewPos.z = 511.5f;

        MBGuideCameraCreate();

        if (arg1 != 0) {
            var_a1 = temp_v0->spriteGroup;
            var_a1 = var_a1 + 0x5a + arg1;        
            temp_v0->amount = HuWinExCreateStyled(0x5b, var_a1, 0x11);
            MBGuidePosSet(temp_v0, 0x69, arg1);
        } else {
            var_a1 = temp_v0->spriteGroup;
            var_a1 = var_a1 + 0x5a + arg1;  
            temp_v0->amount = HuWinExCreateStyled(0x4b, var_a1, 0x10);
            MBGuidePosSet(temp_v0, 0x69, arg1);
        }
    }
    return temp_v0;
}

void MBGuideKill(UnkMBGuideData* arg0) {
    if (arg0 != NULL) {
        MBModelKill(arg0->obj);
        omDelPrcObj(arg0->unk_04);
        HuWinExCleanup(arg0->amount);
        HuMemMemoryFreeTemp(arg0);
    }
}

void MBGuidePosSet(UnkMBGuideData* arg0, s16 arg1, s16 arg2) {
    s16 var1;
    s16 var2;

    arg0->spriteGroup = arg1;
    mbGuideCameraViewPos.y = (arg1 * 4.0f) + 480.0f;
    if ((arg2) != 0) {
        var1 = 0x5B;
        var2 = 0x50;
        HuWinPosSet(arg0->amount, var1, arg0->spriteGroup + (arg2 + var2));
    } else {
        var1 = 0x4B;
        var2 = 0x5A;
        HuWinPosSet(arg0->amount, var1, arg0->spriteGroup + (arg2 + var2));
    }
}

char *mbTelopMgTypeStrTbl[] = {
    (char *)mbMgType4PStr, // "4=PLAYER GAME"
    (char *)mbMgType1vs3Str, // " 1 VS 3 GAME"
    (char *)mbMgType2vs2Str, // " 2 VS 2 GAME"
    (char *)mbMgTypeItemStr, // " ITEM   GAME"
    (char *)mbMgTypeBattleStr, // " BATTLE GAME"
    (char *)mbMgType1vs1Str, // " 1 VS 1 GAME"
    "",
};
s8 mbTelopMgTypeLenTbl[] = { 13, 12, 12, 12, 12, 12, 0 };
s8 mbTelopMgTypeXTbl[] = { -6, 0, 0, 0, 0, 0, 0 };
