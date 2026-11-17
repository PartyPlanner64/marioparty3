#include "common_board.h"
#include "pause.h"
#include "player.h"
#include "status.h"
#include "item.h"
#include "model.h"
#include "back.h"
#include "sprgrp.h"
#include "window.h"

extern Object *mbItemMasuNpcMdl;
extern Object *mbItemMasuCloudMdl;
extern Object* mbItemMasuBoxMdl;

extern s32 mbItemMasuGiveTbl[3];
extern s32 mbItemMasuGive1; //TODO: fake symbol
extern s32 mbItemMasuGive2; //TODO: fake symbol
extern f32 mbItemMasuBoxRot;
extern s32 mbItemMasuKinopioF;
extern s32 mbItemMasuEff;
extern s32 mbItemMasuRareItem;

static void MBItemMasuKinopioNoneExec(void);
static void MBItemMasuKinopioItemExec(void);
static void MBItemMasuKinopioKeyExec(void);
static void MBItemMasuKinopioRareExec(void);
static void MBItemMasuKinopioItem2Exec(void);
static void MBItemMasuKinopioKinokoExec(void);
static void MBItemMasuKoopaJrItemExec(void);
static void MBItemMasuKoopaJrItem2Exec(void);
static void MBItemMasuKoopaJrItem3Exec(void);
static void MBItemMasuKoopaJrKeyExec(void);
static void MBItemMasuKoopaJrWarpExec(void);
static void MBItemMasuKoopaJrNoneExec(void);


// item ids
s32 mbItemMasuItemTbl[] = {
    ITEM_MUSHROOM, ITEM_SKELETON_KEY, ITEM_BOO_REPELLENT,
    ITEM_DUEL_GLOVE, ITEM_WARP_BLOCK, ITEM_GOLDEN_MUSHROOM,
    ITEM_MAGIC_LAMP, ITEM_CELLULAR_SHOPPER
};

// rare item ids?
s32 mbItemMasuRareTbl[] = {
    ITEM_KOOPA_KARD, ITEM_BARTER_BOX, ITEM_LUCKY_CHARM,
    ITEM_WACKY_WATCH
};

s32 mbItemMasuKoopaJrTbl[] = {
    ITEM_SKELETON_KEY, ITEM_PLUNDER_CHEST, ITEM_BOWSER_PHONE,
    ITEM_WARP_BLOCK, ITEM_BOO_BELL, ITEM_BOWSER_SUIT,
    ITEM_POISON_MUSHROOM, ITEM_REVERSE_MUSHROOM, ITEM_LUCKY_LAMP
};

f32 mbItemMasuStatusPosTbl[][2] = {
    { 88.0f, 44.0f }, { 245.0f, 44.0f }, { 88.0f, 220.0f }, { 245.0f, 220.0f }
};

s32 mbItemMasuRareMesTbl[] = {
    [ITEM_MUSHROOM] 0,
    [ITEM_SKELETON_KEY] 0,
    [ITEM_POISON_MUSHROOM] 0,
    [ITEM_REVERSE_MUSHROOM] 0,
    [ITEM_CELLULAR_SHOPPER] 0,
    [ITEM_WARP_BLOCK] 0,
    [ITEM_PLUNDER_CHEST] 0,
    [ITEM_BOWSER_PHONE] 0,
    [ITEM_DUEL_GLOVE] 0,
    [ITEM_LUCKY_LAMP] 0,
    [ITEM_GOLDEN_MUSHROOM] 0,
    [ITEM_BOO_BELL] 0,
    [ITEM_BOO_REPELLENT] 0,
    [ITEM_BOWSER_SUIT] 0,
    [ITEM_MAGIC_LAMP] 0,
    [ITEM_KOOPA_KARD] 0x00003C0E,
    [ITEM_BARTER_BOX] 0x00003C10,
    [ITEM_LUCKY_CHARM] 0x00003C11,
    [ITEM_WACKY_WATCH] 0x00003C0F
};

void (*mbItemMasuKinopioFuncTbl[])(void) = {
    MBItemMasuKinopioNoneExec,
    MBItemMasuKinopioItemExec,
    MBItemMasuKinopioKeyExec,
    MBItemMasuKinopioRareExec,
    MBItemMasuKinopioItem2Exec,
    MBItemMasuKinopioKinokoExec
};

void (*mbItemMasuKoopaJrFuncTbl[])(void) = {
    MBItemMasuKoopaJrItemExec,
    MBItemMasuKoopaJrItem2Exec,
    MBItemMasuKoopaJrItem3Exec,
    MBItemMasuKoopaJrKeyExec,
    MBItemMasuKoopaJrWarpExec,
    MBItemMasuKoopaJrNoneExec
};

s32 mbItemMasuKinopioMesTbl[] = {
    0x00003C03, 0x00003C04, 0x00003C05, 0x00003C06, 0x00003C07
};

s32 mbItemMasuKoopaJrMesTbl[] = {
    0x00003C15, 0x00003C16, 0x00003C17,
    0x00003C18, 0x00003C19, 0x00003C1A
};

static void MBItemMasuFloatObjMain(omObjData *arg0) {
    mbItemMasuNpcMdl->coords.y = -sindf(arg0->rot.x) * 3.0f;
    mbItemMasuCloudMdl->coords.y = -sindf(arg0->rot.x) * 3.0f;
    arg0->rot.x += 3.0f;
}

static void MBItemMasuBoxObjMain(omObjData *obj) {
    mbItemMasuBoxRot += 20.0f;
    if (mbItemMasuBoxRot >= 360.0f) {
        mbItemMasuBoxRot -= 360.0f;
    }

    HuMtxRotZF(Hu3DData[mbItemMasuBoxMdl->omObj1->model[0]].mtx, mbItemMasuBoxRot);
}

static s32 MBItemMasuChoiceGet(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS] = { 1, 2, 4, 8 };
    s32 var_v0;
    s32 i;
    s32 j;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                sp18[GwPlayer[i].pad] = D_JPAD;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = HUWIN_COMKEY_PAD;
            }

        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (arg2 != 0) {
        HuWinAttrSet(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; arg2 != 0; j++) {
            if (--arg2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = A_BUTTON;
            }
            if (j == 0) {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], MBMesWaitGet());
            } else {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], 0x10);
            }
        }
    } else {
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    }
    for (i = 0; i < arg3; i++) {
        if ((arg0 != 0) && ((u8 *)arg0)[i] == 0) {
            HuWinChoiceDisable(mbDlgWinId, i);
        }
    }

    i = 0;

    while (1) {
        i = HuWinChoiceGet(mbDlgWinId, i, arg1);
        if (arg1 != 0) {
            if ((arg0 == 0) || ((((u8 *)arg0)[i] != 0))) {
                return i;
            }
        } else if (i == -1) {
            return -1;
        } else {
            if ((arg0 == 0) || ((((u8 *)arg0)[i] != 0))) {
                return i;
            }
        }
    }
}

// All items you can carry from item space
void MBItemMasuItemDecide(void) {
    s32 prev;
    s32 i;
    s32 *boardItemIds;

    prev = -1;
    for (i = 0; i < ARRAY_COUNT(GwPlayer->itemNo); i++) {
        boardItemIds = &mbItemMasuGiveTbl[i];
        while (1) {
            *boardItemIds = mbItemMasuItemTbl[MBRand(ARRAY_COUNT(mbItemMasuItemTbl))];
            if (*boardItemIds != prev) {
                prev = *boardItemIds;
                break;
            }
        }
    }
}

#ifdef NON_MATCHING
// more readable version of the function as the matching version is very jank
void MBItemMasuRareDecide(void) {
    s32 *temp2 = mbItemMasuRareTbl;
    s32 itemID;

    while (1) {
        itemID = temp2[MBRand(ARRAY_COUNT(mbItemMasuRareTbl))];
        mbItemMasuGiveTbl[0] = itemID;

        if (itemID == ITEM_WACKY_WATCH && GwSystem.unk_52 == WATCH_AVAILABLE) {
            GwSystem.unk_52 = 1;
            break;
        }

        if (itemID != ITEM_WACKY_WATCH) {
            break;
        }
    }

    mbItemMasuGive1 = -1;
    mbItemMasuRareItem = itemID;
}
#else
// TODO: cleanup this jank function
void MBItemMasuRareDecide(void) {
    s32 itemID;
    
    while (1) {
        itemID = mbItemMasuGiveTbl[0] = mbItemMasuRareTbl[MBRand(ARRAY_COUNT(mbItemMasuRareTbl))];
        if (itemID != ITEM_WACKY_WATCH) {
            break;
        }

        //is wacky watch to get here
        if (GwSystem.wackyWatchUsedState == WATCH_AVAILABLE) {
            if (itemID == ITEM_WACKY_WATCH) {
                GwSystem.wackyWatchUsedState = WATCH_ISSUED;
            }
            break;
        }
        if (itemID != ITEM_WACKY_WATCH) {
            GwSystem.wackyWatchUsedState = WATCH_ISSUED;
        }
    }

    mbItemMasuGive1 = -1;
    mbItemMasuRareItem = itemID;
}
#endif

// All items you can carry from item space
void MBItemMasuKoopaJrDecide(void) {
    s32 prev;
    s32 i;
    s32 *boardItemIds;

    prev = -1;
    for (i = 0; i < ARRAY_COUNT(GwPlayer->itemNo); i++) {
        boardItemIds = &mbItemMasuGiveTbl[i];
        while (1) {
            *boardItemIds = mbItemMasuKoopaJrTbl[MBRand(ARRAY_COUNT(mbItemMasuKoopaJrTbl))];
            if (*boardItemIds != prev) {
                prev = *boardItemIds;
                break;
            }
        }
    }
}

void MBItemMasuGiveExec(s32 arg0) {
    f32 sp20[2];
    GW_PLAYER *player;
    UnkBoard8 *temp_s2;
    f32 var_f20;
    f32 var_f28;
    omObjData *obj;
    s32 playerNo;
    s32 temp_s6;
    s32 var_s4;
    void *temp_v0;
    s32 i;

    player = MBPlayerGet(CUR_PLAYER);
    playerNo = MBPlayerTurnGet();
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(1);
    MBStatusGrow(-1);

    var_s4 = 0;
    if (arg0 == 0) {
        var_f28 = 5.0f;
    } else {
        var_f28 = 10.0f;
    }

    while ((MBItemFindEmpty(playerNo) != ITEM_NONE) && (mbItemMasuGiveTbl[var_s4] != -1)) {
        if (mbItemMasuKinopioF != 0) {
            mbItemMasuBoxMdl = MBModelCreate(0x22, NULL);
        } else {
            mbItemMasuBoxMdl = MBModelFileCreate(0xB0036, -1, 1.0f, 0, 0);
        }
        Hu3DModelAttrSet(mbItemMasuBoxMdl->omObj1->model[0], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_OFF);
        Hu3DModelLayerSet(mbItemMasuBoxMdl->omObj1->model[0], 0x1800);
        Hu3DModelRemakeStatic(mbItemMasuBoxMdl->omObj1->model[0]);
        HuVecCopy3F(&mbItemMasuBoxMdl->coords, &player->player_obj->coords);
        mbItemMasuBoxMdl->coords.y += 25.0f;
        MBCamera3Dto2D(&mbItemMasuBoxMdl->coords, sp20);
        HuAudFXPlay(0x143);
        mbItemMasuBoxRot = 0;

        obj = omAddObj(0x1F4, 0, 0, -1, MBItemMasuBoxObjMain);
        for (var_f20 = 1.0f; var_f20 < var_f28; var_f20 += 0.5) {
            HuVecCopyXYZ(&mbItemMasuBoxMdl->scale, var_f20, var_f20, var_f20);
            HuPrcVSleep();
        }

        var_f20 = var_f20 - 0.5f;

        HuAudFXPlay(0x11C);
        temp_s6 = mbItemMasuGiveTbl[var_s4++];
        temp_s2 = MBSprGrpCreate(1, 0);
        temp_v0 = DataRead(mbItemIconSprTbl[temp_s6]);
        temp_s2->model[0] = HuSprAnimRead(temp_v0);
        DataClose(temp_v0);
        HuSprGrpMemberSet(temp_s2->spriteGroup, 0, temp_s2->model[0], 0);
        HuSprAttrReset(temp_s2->spriteGroup, 0, 0xFFFF);
        HuSprAttrSet(temp_s2->spriteGroup, 0, HUSPR_ATTR_XLU);
        HuSprPriSet(temp_s2->spriteGroup, 0, 0x1000U);
        HuSprPosSet(temp_s2->spriteGroup, 0, sp20[0], sp20[1]);

        for (i = 0; i < 15; i++) {
            HuSprTPLvlSet(temp_s2->spriteGroup, 0, ((i * 16) + i));
            HuPrcVSleep();
        }

        HuSprTPLvlSet(temp_s2->spriteGroup, 0, 0xFF);

        if (arg0 == 1) {
            MBDlgWinInsertCreateY(-1, 0x3C0D, mbItemMasuRareMesTbl[mbItemMasuRareItem], 0, 0, 0, 0, 0x8C);
            MBDlgWinClose();
            MBDlgWinKill();
        }
        for (i = 0; i < 70; i += 5) {
            // this sure is a line of code
            HuSprPosSet(temp_s2->spriteGroup, 0, (((sindf(i) * (mbItemMasuStatusPosTbl[playerNo][0] - sp20[0])) + sp20[0])), ((sp20[1] - (sindf((i + 0x5A)) * (mbItemMasuStatusPosTbl[playerNo][1] - sp20[1]))) + (mbItemMasuStatusPosTbl[playerNo][1] - sp20[1])));
            HuSprTPLvlSet(temp_s2->spriteGroup, 0, (256.0 - (i * 1.5)));
            HuSprScaleSet(temp_s2->spriteGroup, 0, (1.0f - (i / 200.0f)), (1.0f - (i / 200.0f)));
            HuPrcVSleep();
        }

        MBSprGrpKill(temp_s2);
        GwPlayer[playerNo].itemNo[MBItemFindEmpty(playerNo)] = temp_s6;
        MBStatusItemSprKill(playerNo);

        for (; var_f20 >= 1.0f; var_f20 -= 0.5) {
            HuVecCopyXYZ(&mbItemMasuBoxMdl->scale, var_f20, var_f20, var_f20);
            HuPrcVSleep();
        }

        omDelObj(obj);
        MBModelKill(mbItemMasuBoxMdl);
    }

    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
}

// probably a file split here
static void MBItemMasuKinopioNoneExec(void) {
    MBDlgWinExec(CHAR_TOAD, 0x3C08);
}

static void MBItemMasuKinopioItemExec(void) {
    MBDlgWinExec(CHAR_TOAD, 0x3C09);
    MBItemMasuItemDecide();
    MBItemMasuGiveExec(0);
    MBDlgWinExec(CHAR_TOAD, 0x3C0A);
}

// Toad gives all skeleton keys
static void MBItemMasuKinopioKeyExec(void) {
    MBDlgWinExec(CHAR_TOAD, 0x3C0B);
    mbItemMasuGiveTbl[0] =
        mbItemMasuGiveTbl[1] =
            mbItemMasuGiveTbl[2] = ITEM_SKELETON_KEY;
    MBItemMasuGiveExec(0);
    MBDlgWinExec(CHAR_TOAD, 0x3C0A);
}

static void MBItemMasuKinopioRareExec(void) {
    MBDlgWinExec(CHAR_TOAD, 0x3C0C);
    MBItemMasuRareDecide();
    MBItemMasuGiveExec(1);
    MBDlgWinExec(CHAR_TOAD, 0x3C0A);
}

static void MBItemMasuKinopioItem2Exec(void) {
    MBDlgWinExec(CHAR_TOAD, 0x3C12);
    MBItemMasuItemDecide();
    mbItemMasuGive2 = -1;
    MBItemMasuGiveExec(0);
    MBDlgWinExec(CHAR_TOAD, 0x3C0A);
}

static void MBItemMasuKinopioKinokoExec(void) {
    MBDlgWinExec(CHAR_TOAD, 0x3C13);
    mbItemMasuGiveTbl[0] =
        mbItemMasuGiveTbl[1] =
            mbItemMasuGiveTbl[2] = ITEM_MUSHROOM;
    MBItemMasuGiveExec(0);
    MBDlgWinExec(CHAR_TOAD, 0x3C0A);
}

static void MBItemMasuKoopaJrItemExec(void) {
    MBDlgWinExec(CHAR_BABY_BOWSER, 0x3C1C);
    MBItemMasuKoopaJrDecide();
    mbItemMasuGive1 = -1;
    MBItemMasuGiveExec(0);
    MBDlgWinExec(CHAR_BABY_BOWSER, 0x3C1D);
}

static void MBItemMasuKoopaJrItem2Exec(void) {
    MBDlgWinExec(CHAR_BABY_BOWSER, 0x3C1E);
    MBItemMasuKoopaJrDecide();
    mbItemMasuGive2 = -1;
    MBItemMasuGiveExec(0);
    MBDlgWinExec(CHAR_BABY_BOWSER, 0x3C1D);
}

static void MBItemMasuKoopaJrItem3Exec(void) {
    MBDlgWinExec(CHAR_BABY_BOWSER, 0x3C1F);
    MBItemMasuKoopaJrDecide();
    MBItemMasuGiveExec(0);
    MBDlgWinExec(CHAR_BABY_BOWSER, 0x3C1D);
}

// Baby bowser gives all skeleton keys
static void MBItemMasuKoopaJrKeyExec(void) {
    MBDlgWinExec(CHAR_BABY_BOWSER, 0x3C20);
    mbItemMasuGiveTbl[0] =
        mbItemMasuGiveTbl[1] =
            mbItemMasuGiveTbl[2] = ITEM_SKELETON_KEY;
    MBItemMasuGiveExec(0);
    MBDlgWinExec(CHAR_BABY_BOWSER, 0x3C1D);
}

// Baby bowser gives warp blocks from item space
static void MBItemMasuKoopaJrWarpExec(void) {
    MBDlgWinExec(CHAR_BABY_BOWSER, 0x3C21);
    mbItemMasuGiveTbl[0] =
        mbItemMasuGiveTbl[1] =
            mbItemMasuGiveTbl[2] = ITEM_WARP_BLOCK;
    MBItemMasuGiveExec(0);
    MBDlgWinExec(CHAR_BABY_BOWSER, 0x3C1D);
}

static void MBItemMasuKoopaJrNoneExec(void) {
    MBDlgWinExec(CHAR_BABY_BOWSER, 0x3C1B);
}

static void MBItemMasuExec(void) {
    GW_PLAYER *temp_s1;
    Object *temp_a0;
    f32 var_f12;
    omObjData *temp_v0;
    s16 var_a0;
    s32 temp_s0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_a0_2;
    s32 var_s0;
    s32 var_v0_2;
    void (*dispatch_func)();

    temp_s1 = MBPlayerGet(CUR_PLAYER);

    if (mbItemMasuKinopioF != 0) {
        mbItemMasuNpcMdl = MBModelCreate(9, NULL);
        mbItemMasuCloudMdl = MBModelFileCreate(0x1301C8, -1, 1.0f, 0, 0);
        mbItemMasuEff = EffectCreate(0xB0004, 0xAA9);
        HuAudFXPlay(0x119);
    } else {
        mbItemMasuNpcMdl = MBModelCreate(0x39, NULL);
        mbItemMasuCloudMdl = MBModelFileCreate(0x130203, -1, 1.0f, 0, 0);
        mbItemMasuEff = EffectCreate(0xB0005, 0xAA9);
        HuAudFXPlay(0x11A);
    }

    Hu3DModelCameraSet(mbItemMasuEff, HU3D_CAM0);
    EffectParamSet(mbItemMasuEff, 1.0f, 20.0f, 1.0f);
    EffectRangeSet(mbItemMasuEff, 15.0f);
    MBModelTempAllocFree(mbItemMasuNpcMdl);
    mbItemMasuNpcMdl->flags |= 1;
    MBModelTempAllocFree(mbItemMasuCloudMdl);
    HuVecCopy3F(&mbItemMasuNpcMdl->coords, &temp_s1->player_obj->coords);
    HuVecCopy3F(&mbItemMasuCloudMdl->coords, &temp_s1->player_obj->coords);

    mbItemMasuNpcMdl->velocity.x = 120.0f;
    mbItemMasuCloudMdl->velocity.x = 120.0f;

    while (mbItemMasuNpcMdl->velocity.x > 50.0f) {
        EffectPosSet(mbItemMasuEff, mbItemMasuNpcMdl->coords.x, mbItemMasuNpcMdl->velocity.x - 10.0f, mbItemMasuNpcMdl->coords.z);
        HuPrcVSleep();
        mbItemMasuNpcMdl->velocity.x -= 2.0f;
        mbItemMasuCloudMdl->velocity.x -= 2.0f;
    }

    temp_v0 = omAddObj(0x1F4, 0, 0, -1, MBItemMasuFloatObjMain);
    temp_v0->rot.x = 180.0f;
    var_s0 = 0;

    if (mbItemMasuKinopioF != 0) {
        HuAudFXPlay(0x298);
        MBDlgWinExec(CHAR_TOAD, 0x3C02);
        MBDlgWinCreate(CHAR_TOAD, mbItemMasuKinopioMesTbl[MBRand(ARRAY_COUNT(mbItemMasuKinopioMesTbl))]);
        if (temp_s1->stat & PLAYER_IS_CPU) {
            var_f12 = 3.0f;
            var_s0 = MBRand(var_f12) + 1;
        }
    } else {
        HuAudFXPlay(0x2A0);
        MBDlgWinExec(CHAR_BABY_BOWSER, 0x3C14);
        MBDlgWinCreate(CHAR_BABY_BOWSER, mbItemMasuKoopaJrMesTbl[MBRand(ARRAY_COUNT(mbItemMasuKoopaJrMesTbl))]);
        if (temp_s1->stat & PLAYER_IS_CPU) {
            var_f12 = 2.0f;
            var_s0 = MBRand(var_f12) + 1;
        }
    }

    temp_s0 = MBItemMasuChoiceGet(0, 1, var_s0, -1);
    MBDlgWinClose();
    MBDlgWinKill();
    temp_v1 = MBRand(10.0f);
    if (mbItemMasuKinopioF != 0) {
        switch (temp_s0) {
            case 0:
                if (temp_v1 < 4) {
                    var_a0_2 = 0;
                } else if (temp_v1 < 8) {
                    var_a0_2 = 1;
                } else {
                    var_a0_2 = 2;
                }
                break;

            case 1:
                if (temp_v1 < 2) {
                    var_a0_2 = 3;
                } else if (temp_v1 >= 8) {
                    var_a0_2 = 1;
                } else {
                    if (MBItemFindEmpty(MBPlayerTurnGet()) == 2) {
                        var_a0_2 = 1;
                    } else {
                        var_a0_2 = 4;
                    }
                }
                break;

            case 2:
            default:
                if (temp_v1 < 3) {
                    var_a0_2 = 3;
                } else if (temp_v1 < 7) {
                    var_a0_2 = 1;
                } else if (temp_v1 < 9) {
                    var_a0_2 = 5;
                } else {
                    var_a0_2 = 2;
                }
                break;
        }

        dispatch_func = mbItemMasuKinopioFuncTbl[var_a0_2];
    } else {
        if (temp_s0 == 0) {
            if (temp_v1 < 2) {
                var_a0_2 = 0;
            } else if (temp_v1 < 6) {
                if (MBItemFindEmpty(MBPlayerTurnGet()) == 2) {
                    var_a0_2 = 2;
                } else {
                    var_a0_2 = 1;
                }
            } else if (temp_v1 < 8) {
                var_a0_2 = 2;
            } else if (temp_v1 < 9) {
                var_a0_2 = 3;
            } else {
                var_a0_2 = 4;
            }
        } else {
            if (temp_v1 < 2) {
                var_a0_2 = 5;
            } else if (temp_v1 < 6) {
                var_a0_2 = 2;
            } else if (temp_v1 < 8) {
                var_a0_2 = 3;
            } else {
                var_a0_2 = 4;
            }
        }

        dispatch_func = mbItemMasuKoopaJrFuncTbl[var_a0_2];
    }

    dispatch_func();
    omDelObj(temp_v0);

    while (mbItemMasuNpcMdl->velocity.x < 120.0f) {
        EffectPosSet(mbItemMasuEff, mbItemMasuNpcMdl->coords.x, mbItemMasuNpcMdl->velocity.x - 10.0f, mbItemMasuNpcMdl->coords.z);
        HuPrcVSleep();
        mbItemMasuNpcMdl->velocity.x += 4.0f;
        mbItemMasuCloudMdl->velocity.x += 4.0f;
    }

    EffectStop(mbItemMasuEff);
    MBModelKill(mbItemMasuNpcMdl);
    MBModelKill(mbItemMasuCloudMdl);
}

void MBItemMasuKinopioExec(void) {
    mbItemMasuKinopioF = 1;
    MBItemMasuExec();
}

void MBItemMasuKoopaJrExec(void) {
    mbItemMasuKinopioF = 0;
    MBItemMasuExec();
}
