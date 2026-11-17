#include "common_duel.h"
#include "ovl_81.h"
#include "game/pause.h"

// this file is a duplicate of main.c in party/common
extern UnkE3CD0 *mbdCameraFocusObj;
extern Vec *mbdCameraFocusVec;
extern Vec mbdCameraFocusStaticPos;
extern s16 mbdCameraFocusMode;
extern s16 mbWipeTypeNext;
extern f32 mbCameraZoom;
extern s16 duelUnkF0;
extern s16 duelUnkF1;
extern s16 mbWipeType;
extern s16 mbSeqPlayF;
extern s32 mbdExitOvlNo;
extern s16 mbdExitOvlEvent;
extern Vec mbdPlayerFixPosTbl[];
extern Vec mbdPartnerFixPosTbl[][2];
extern s32 mbdWalkEventResult;

s16 mbdPakkunForceF = 0;
s32 mbdBoardOvlTbl[] = { 91, 92, 93, 94, 95, 96, 97 };
s32 mbdBoardIntroOvlTbl[] = { 100, 100, 100, 100, 100, 100, 101 };
void (*mbdExitHook)(void) = NULL;
process_func mbdHatenaFunc = NULL;
s32 (*mbdWalkAttackHook)(void) = NULL;
void (*mbdWalkEndHook)(void) = NULL;
u8 mbdGambleMgTbl[4] = { 67, 68, 69, 70 };
u8 mbdGambleMgRateTbl[4] = { 5, 30, 65, 100 };
f32 mbdJumpAngleTbl[][2] = { { 0.0f, 0.0f }, { 200.0f, 250.0f }, { 110.0f, 250.0f }, { 70.0f, 290.0f }, { 0.0f, 360.0f } };
f32 mbdJumpNextAngleTbl[][2] = { { 0.0f, 0.0f }, { 20.0f, 70.0f }, { -70.0f, 70.0f }, { 70.0f, 290.0f }, { 0.0f, 360.0f } };
u8 mbdTurnCoinTbl[] = { 3, 5, 8, 10 };
DuelHelpWin *mbdTurnHelpWin0 = NULL;
DuelHelpWin *mbdTurnHelpWin1 = NULL;
DuelHelpWin *mbdTurnHelpWin2 = NULL;
DuelHelpWin *mbdTurnHelpWin3 = NULL;

void MBDMain(void);
void MBDCameraRefresh(Vec *arg0);
void *MBDPlayerVibrateObjCreate(s16, s16, s32);
void MBDPlayerVibrateObjKill(void *);
void MBDDlgWinExecAllKey(s16 arg0, s32 arg1);
void MBDPartnerAttackMotSet(Object *arg0, s16 arg1, s16 arg2);
void MBDPlayerMotionSet(s32 playerIndex, s16 arg1, u16 arg2);
void MBDPlayerPartyMotionSet(s32 playerIndex, s16 arg1, u16 arg2);

void MBDOvlCall(s32 id, s16 event, u16 stat) {
    omOvlHisData *overlay = &mbovlhis[mbovlhisidx++];

    if (id != -2) {
        if (id == -1) {
            id = omovlhis[omovlhisidx].overlayID;
            overlay->overlayID = id;
        } else {
            overlay->overlayID = id;
        }
    } else {
        id = mbdBoardOvlTbl[GwSystem.current_board_index];
        overlay->overlayID = id;
    }

    overlay->event = event;
    overlay->stat = stat;

    if (mbovlhisidx >= ARRAY_COUNT(mbovlhis)) {
        mbovlhisidx = ARRAY_COUNT(mbovlhis) - 1;
    }
}

void MBDOvlCallInit(void) {
    ditherBak.unk_02 = 1;
    mbovlhisidx = 0;

    if (GWBoardFlagCheck(1) == 0) {
        MBDOvlCall(-2, 1, 0x4190);
        MBDOvlCall(mbdBoardIntroOvlTbl[GwSystem.current_board_index], 0, 0x4190);
    }
    MBDSaveInit();
    MBDMesSpeedSet(GwSystem.message_speed);
    _ClearFlag(0xC);
    mbEndingF = 0;
}

void MBDOvlCallExec(void) {
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
        omOvlCallEx(mbdBoardOvlTbl[GwSystem.current_board_index], 2, 0x4190);
        return;
    }
    if (mbEndingF != 0) {
        _SetFlag(0xC);
    } else {
        _ClearFlag(0xC);
    }
    omOvlReturnEx(1);
}

void MBDBoardReturnOff(void) {
    ditherBak.unk_02 = 0;
}

s16 MBDOvlCallCheck(void) {
    return mbOvlCallF;
}

void MBDOvlCallEventReturn(s16 arg0) {
    s16 temp_v0 = mbovlhisidx;

    mbovlhis[mbovlhisidx].event = arg0;
    mbovlhisidx = temp_v0 + 1;
    if (mbovlhisidx >= 5) {
        mbovlhisidx = 4;
    }
    MBDOvlCall(-2, 3, 0x4190);
    omOvlReturnEx(1);
}

s32 MBDGameModeGet(void) {
    return mbGameMode;
}

void MBDPlayerTauntProc(omObjData *obj) {
    s32 *temp_s0 = HuPrcCurrentGet()->user_data;

    while (1) {
        if (
            (MBDPlayerComCheck(temp_s0[0]) == 0) &&
            (mbTauntOffF == 0) &&
            ((GwSystem.current_player_index != temp_s0[0]) || (mbTurnUnkF == 0)) &&
            (ContBtnDown[GwPlayer[temp_s0[0]].pad] & L_TRIG)) {
            PlayerFXPlay(0x2BD, temp_s0[0]);
        }
        HuPrcVSleep();
    }
}

void MBDObjectSetup(s32 arg0, s16 arg1, s32 arg2) {
    Process *temp_v0_2;
    UnkOvl81_1 *temp_v0_3;
    s32 frontPartnerID;
    s32 backPartnerID;
    Object *playerObj;
    s32 i;

    MBDBackSprInit();
    MBDBackArcInit(hvq_data_ROM_START);

    if (arg0 >= 0) {
        MBDBackLoad(arg0);
    }

    MBDMasuInit();

    if (arg1 >= 0) {
        MBDMasuCreate(0x13, arg1);
    }

    MBDModelInit();
    MBDPlayerMotInit();
    MBDPlayerModelSetup(0);
    MBDPlayerModelSetup(1);

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        MBDModelTempAllocFree(MBDPlayerGet(i)->player_obj);
        playerObj = MBDPlayerGet(i)->player_obj;
        playerObj->flags |= 2;
        MBDModelDispOn(MBDPlayerGet(i)->player_obj);
    }

    Hu3DMotionReset(MBDPlayerGet(0)->player_obj->omObj1->model[0]);
    Hu3DMotionReset(MBDPlayerGet(1)->player_obj->omObj1->model[0]);
    MBDPartnerMotionReset(0);
    MBDPartnerMotionReset(1);
    MBDSprGrpInit();
    MBDMgCallInit();
    MBDCoinChangeInit();
    MBDTelopInit();
    MBDStatusCreate();

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        frontPartnerID = GwPlayer[i].stats.partners.frontID;
        backPartnerID = GwPlayer[i].stats.partners.backID;
        GwPlayer[i].stats.partners.frontID = PARTNER_KOOPA; //?
        GwPlayer[i].stats.partners.backID = PARTNER_KOOPA;  //?
        MBDStatusFrontUpdate(i);
        MBDStatusBackUpdate(i);
        GwPlayer[i].stats.partners.frontID = frontPartnerID;
        GwPlayer[i].stats.partners.backID = backPartnerID;
        MBDStatusFrontUpdate(i);
        MBDStatusBackUpdate(i);
    }

    MBDSaiInit();
    HuWinInit();
    MBDDlgWinParamReset();

    mbdExitFlag = -1;
    mbWipeType = WIPE_TYPE_NORMAL;
    mbdExitMusFadeF = 0;
    MBDScissorFullSet();
    mbdExitHook = NULL;
    mbdHatenaFunc = 0;
    mbdWalkAttackHook = NULL;
    mbdWalkEndHook = NULL;
    for (i = 0; i < 2; i++) {
        temp_v0_2 = omAddPrcObj(MBDPlayerTauntProc, 0, 0, 0x40);
        temp_v0_3 = HuMemMemoryAlloc(temp_v0_2->heap, sizeof(UnkOvl81_1));
        temp_v0_2->user_data = temp_v0_3;
        temp_v0_3->unk_00 = i;
        omPrcSetStatBit(temp_v0_2, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    }
}

void MBDExit(void) {
    MBDSaiClose();
    MBDStatusKill();
    MBDTelopClose();
    MBDCoinChangeClose();
    MBDMgCallClose();
    MBDSprGrpClose();
    HuWinAllKill();
    MBDPlayerClose();
    MBDModelClose();
    MBDMasuKill();
    MBDMasuClose();
    MBDBackKill();
    MBDBackClose();
    MBDBackReset();
    MBDBackSprKillAll();

    if (mbdExitHook != NULL) {
        mbdExitHook();
    }

    MBDTurnHelpKill();
}

// file split? many setters here
void MBDWalkEndHookSet(void (*arg0)(void)) {
    mbdWalkEndHook = arg0;
}

void MBDWalkAttackHookSet(s32 (*arg0)(void)) {
    mbdWalkAttackHook = arg0;
}

void MBDHatenaFuncSet(process_func arg0) {
    mbdHatenaFunc = arg0;
}

void MBDExitHookSet(void (*arg0)(void)) {
    mbdExitHook = arg0;
}

void MBDBoardParamSet(s32 arg0) {
    mbUnkParam = arg0;
}

s16 MBDBoardParamGet(void) {
    return mbUnkParam;
}

void MBDSaveInit(void) {
    GW_PLAYER *player;
    GW_SYSTEM *system = &GwSystem;
    GW_COMMON *common = &GwCommon;
    s32 i, j;

    mbGameMode = 0;
    mbWalkNum = 0;
    duelUnkF0 = 0;
    duelUnkF1 = 0;
    mbdPakkunForceF = 0;
    mbCameraZoom = 1.4f;
    MBDMgCallHisInit();
    MBDSaiValueClear();
    mbWipeTypeNext = -1;
    mbSubMusNo = -1;
    mbSeqPlayF = 0;
    mbTurnUnkF = 1;
    mbTauntOffF = 0;

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
        system->current_turn = 1;
        system->current_player_index = 0;
        system->minigame_index = 0;

        if (system->total_turns == -1U) { //?
            system->total_turns = 50;
        } else {
            system->total_turns = 20;
        }

        for (i = 0; i < MBD_MAX_PLAYERS; i++) {
            player = MBDPlayerGet(i);
            player->coin = 0;
            player->gamePrize = 0;
            player->coinPrize = 0;
            player->stats.partners.frontID = -1;
            player->stats.partners.backID = -1;
            player->stats.partners.frontPoweredUp = 0;
            player->stats.partners.backPoweredUp = 0;
            player->stats.partners.frontHp = 0;
            player->stats.partners.backHp = 0;
            player->stats.partners.frontCost = 0;
            player->stats.partners.backCost = 0;
            player->stats.partners.frontPower = 0;
            player->stats.partners.backPower = 0;

            for (j = 0; j < ARRAY_COUNT(player->itemNo); j++) {
                player->itemNo[j] = -1;
            }

            player->itemTurn = 0;
            player->rev = 0;
        }

#ifdef BUG_FIX
        for (i = 0; i < ARRAY_COUNT(GwSystem.boardData.halfWordBytes); i++) {
            GwSystem.boardData.halfWordBytes[i] = 0;
        }
#else
        // potentially this used to be 16 in length, then was shortened?
        for (i = 0; i < 16; i++) {
            GwSystem.boardData.halfWordBytes[i] = 0;
        }
#endif

        GWBoardFlagClear(0x12);
        GWBoardFlagClear(0x13);
        GWBoardFlagClear(0x14);
        GWBoardFlagClear(0x15);
        GWBoardFlagClear(0x16);
        GWBoardFlagClear(0x17);
        GWBoardFlagClear(1);
        GWBoardFlagClear(0x11);

        if (GwSystem.playMode & 4) {
            if (_CheckFlag(0x28) != 0) {
                GWBoardFlagSet(0);
                return;
            }
            GWBoardFlagClear(0);
            return;
        }

        if (_CheckFlag(0x17) != 0) {
            GWBoardFlagSet(0);
            return;
        }

        GWBoardFlagClear(0);
    }
}

void MBDCameraFocusModeSet(s32 arg0) {
    mbdCameraFocusMode = arg0;
}

s16 MBDCameraFocusModeGet(void) {
    return mbdCameraFocusMode;
}

void MBDCameraFocusStaticPosSet(Vec *arg0) {
    mbdCameraFocusStaticPos = *arg0;
}

void MBDCameraFocusVecSet(Vec *arg0) {
    mbdCameraFocusVec = arg0;
}

Vec *MBDCameraFocusVecGet(void) {
    return mbdCameraFocusVec;
}

void MBDCameraFocusObjSet(UnkE3CD0 *arg0) {
    mbdCameraFocusObj = arg0;
}

void MBDCameraFocusProc(void) {
    Vec2f sp10;
    Vec sp18;

    while (1) {
        switch (mbdCameraFocusMode) {
            case 1:
                MBDCameraPos3DSet(&GwPlayer[GwSystem.current_player_index].player_obj->coords);
                break;
            case 2:
                MBDCameraPos3DSet(&mbdCameraFocusStaticPos);
                break;
            case 4:
                MBDCameraPos3DSet(mbdCameraFocusVec);
                break;
            case 5:
                HuVecCopy3F(&sp18, &mbdCameraFocusObj->unk_0C);
                sp18.y += mbdCameraFocusObj->unk_30;
                MBDCameraPos3DSet(&sp18);
                break;
            case 3:
                MBDCameraPos2DGet(&sp10);
                MBDCameraPos2DSet(&sp10);
                break;
        }
        HuPrcVSleep();
    }
}

void MBDNextPlayerTurn(void) {
    GW_SYSTEM *system = &GwSystem;

    system->current_player_index++;
    if ((system->current_player_index >= 2) && (system->current_player_index = 0, (mbTurnOnF == 0))) {
        system->current_turn++;
        if ((system->current_board_index == 4) && (system->total_turns == 50)) {
            if (system->current_turn > 20) {
                system->current_turn = 19;
            }
        } else if (system->current_turn >= 20) {
            system->current_turn = 20;
        }
    }
}

void MBDExitProc(void) {
    do {
        HuPrcVSleep();
    } while (WipeStatGet() != 0);

    while (1) {
        HuPrcVSleep();
        if (omSysExitReq == 0) {
            if (mbdExitFlag < 0) {
                continue;
            }
        }

        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }

        if (mbdExitMusFadeF != 0) {
            HuAudSeqFadeOut(0x5A);
            mbSubMusNo = mbSubMusNo;
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

        WipeCreateOut((s32)mbWipeType, 0x10);
        HuPrcSleep(0x11);
        MBDExit();
        if (mbdExitFlag & 0x20) {
            mbEndingF = 1;
            if (GwSystem.current_board_index == 5) {
                _CheckFlag(9);
            }
            MBDOvlCall(0x62, 0, 0x4190);
            MBDBoardReturnOff();
        }
        if (mbdExitFlag & 1) {
            MBDNextPlayerTurn();
        }
        if (mbdExitFlag & 2) {
            MBDOvlCall(0x70, 0, 0x192);
        }
        if (mbdExitFlag & 8) {
            MBDOvlCall(mbdExitOvlNo, mbdExitOvlEvent, 0x192);
        }
        omOvlReturnEx(1);
        omOvlKill();
        HuPrcVSleep();
    }
}

void MBDMasuPassSePlay(s16 spaceType) {
    switch (spaceType) {
        case MBD_MASU_TYPE_HAPPENING:
        case MBD_MASU_TYPE_GAMEGUY:
        case MBD_MASU_TYPE_REVERSE:
        case MBD_MASU_TYPE_BASIC:
        case MBD_MASU_TYPE_MINIGAME:
        case MBD_MASU_TYPE_POWERUP:
        case MBD_MASU_TYPE_CHR(CHAR_MARIO):
        case MBD_MASU_TYPE_CHR(CHAR_LUIGI):
        case MBD_MASU_TYPE_CHR(CHAR_PEACH):
        case MBD_MASU_TYPE_CHR(CHAR_YOSHI):
        case MBD_MASU_TYPE_CHR(CHAR_WARIO):
        case MBD_MASU_TYPE_CHR(CHAR_DK):
        case MBD_MASU_TYPE_CHR(CHAR_WALUIGI):
        case MBD_MASU_TYPE_CHR(CHAR_DAISY):
            HuAudFXPlay(0x101);
            break;
    }
}

void MBDMasuLandSePlay(s16 spaceType) {
    switch (spaceType) {
        case MBD_MASU_TYPE_REVERSE:
            if (GwSystem.current_board_index == 5) {
                HuAudFXPlay(0x1D4);
            } else {
                HuAudFXPlay(0x1D3);
            }
            break;
        case MBD_MASU_TYPE_POWERUP:
            HuAudFXPlay(0x1D2);
            break;
        case MBD_MASU_TYPE_GAMEGUY:
            HuAudFXPlay(0x12E);
            break;
        case MBD_MASU_TYPE_HAPPENING:
        case MBD_MASU_TYPE_BASIC:
        case MBD_MASU_TYPE_MINIGAME:
        case MBD_MASU_TYPE_CHR(CHAR_MARIO):
        case MBD_MASU_TYPE_CHR(CHAR_LUIGI):
        case MBD_MASU_TYPE_CHR(CHAR_PEACH):
        case MBD_MASU_TYPE_CHR(CHAR_YOSHI):
        case MBD_MASU_TYPE_CHR(CHAR_WARIO):
        case MBD_MASU_TYPE_CHR(CHAR_DK):
        case MBD_MASU_TYPE_CHR(CHAR_WALUIGI):
        case MBD_MASU_TYPE_CHR(CHAR_DAISY):
            HuAudFXPlay(0x108);
    }
}

void MBDPlayerFixOfsGet(s32 playerIndex, Vec *out) {
    Vec curPos;
    Vec nextPos;
    Vec prevPos;
    Vec dir;
    Vec prevDir;
    GW_PLAYER *player;
    f32 len;

    player = MBDPlayerGet(playerIndex);
    MBDMasuPosGet(playerIndex, MBDMasuLinkMasuIdGet(player->clink, player->cidx), &curPos);
    MBDMasuPosGet(playerIndex, MBDMasuLinkMasuIdGet(player->nlink, player->nidx), &nextPos);
    MBDMasuPosGet(playerIndex, MBDMasuLinkMasuIdGet(player->blink, player->bidx), &prevPos);
    MBDVecDirGet(&curPos, &nextPos, &dir);
    len = HuVecGetLength3F(&dir);
    MBDVecDirGet(&curPos, &prevPos, &prevDir);
    HuVecAdd(&dir, &dir, &prevDir);
    if (HuVecGetLength3F(&dir) <= len) {
        MBDVecDirGet(&curPos, &nextPos, &dir);
        MBDVecRotateY(&dir, 90.0f);
        MBDVecNormalize(&dir);
        if (GwSystem.current_board_index == 4 && player->clink == 6 && player->cidx == 0) {
            HuVecMulScalar(&dir, 24.0f, &dir);
        } else {
            HuVecMulScalar(&dir, 16.968f, &dir);
        }
    } else {
        MBDVecNormalize(&dir);
        HuVecMulScalar(&dir, 24.0f, &dir);
    }
    HuVecCopy3F(out, &dir);
}

void MBDPlayerPosFixSet(s32 playerIndex, s32 time) {
    Vec offset;
    Vec frontOfs;
    Vec backOfs;
    s32 playersShareSpace;
    GW_PLAYER *player;
    GW_PLAYER *curPlayer;
    SpaceData *space;
    Object *partner;
    GW_SYSTEM *system = &GwSystem;

    player = MBDPlayerGet(playerIndex);
    space = MBDMasuGet(MBDMasuLinkMasuIdGet(player->clink, player->cidx));
    if (system->current_player_index == playerIndex) {
        HuVecCopy3F(&player->player_obj->coords, &space->coords);
        MBDPartnerPosFix(playerIndex);
        return;
    }

    playersShareSpace = 0;
    curPlayer = MBDPlayerGet(system->current_player_index);
    do { // reg alloc hack
        if (player->clink == curPlayer->clink) {
            playersShareSpace = player->cidx == curPlayer->cidx;
        }
    } while (0);

    HuVecCopy3F(&mbdPlayerFixPosTbl[playerIndex], &space->coords);
    if (playersShareSpace == 1) {
        MBDPlayerFixOfsGet(playerIndex, &offset);
        HuVecAdd(&mbdPlayerFixPosTbl[playerIndex], &mbdPlayerFixPosTbl[playerIndex], &offset);
    }

    if (time < 2) {
        HuVecCopy3F(&player->player_obj->coords, &mbdPlayerFixPosTbl[playerIndex]);
    } else {
        MBDPlayerPosMoveCreate(&player->player_obj->coords, &mbdPlayerFixPosTbl[playerIndex], &player->player_obj->coords, time);
    }

    MBDPartnerOfsGet(playerIndex, &frontOfs, &backOfs);

    if (player->stats.partners.frontID != -1) {
        partner = MBDPartnerObjGet(playerIndex, PARTNER_FRONT);
        HuVecCopyXYZ(&mbdPartnerFixPosTbl[playerIndex][PARTNER_FRONT],
                     mbdPlayerFixPosTbl[playerIndex].x + frontOfs.x,
                     mbdPlayerFixPosTbl[playerIndex].y + frontOfs.y,
                     mbdPlayerFixPosTbl[playerIndex].z + frontOfs.z);
        if (time < 2) {
            HuVecCopy3F(&partner->coords, &mbdPartnerFixPosTbl[playerIndex][PARTNER_FRONT]);
        } else {
            MBDPlayerPosMoveCreate(&partner->coords, &mbdPartnerFixPosTbl[playerIndex][PARTNER_FRONT], &partner->coords, time);
        }
    }

    if (player->stats.partners.backID != -1) {
        partner = MBDPartnerObjGet(playerIndex, PARTNER_BACK);
        HuVecCopyXYZ(&mbdPartnerFixPosTbl[playerIndex][PARTNER_BACK],
                     mbdPlayerFixPosTbl[playerIndex].x + backOfs.x,
                     mbdPlayerFixPosTbl[playerIndex].y + backOfs.y,
                     mbdPlayerFixPosTbl[playerIndex].z + backOfs.z);
        if (time < 2) {
            HuVecCopy3F(&partner->coords, &mbdPartnerFixPosTbl[playerIndex][PARTNER_BACK]);
        } else {
            MBDPlayerPosMoveCreate(&partner->coords, &mbdPartnerFixPosTbl[playerIndex][PARTNER_BACK], &partner->coords, time);
        }
    }
}

// if player should jump to next space
s32 MBDPlayerJumpCheck(s32 playerIndex) {
    Vec sp10;
    GW_PLAYER *curPlayer;
    GW_PLAYER *player;
    f32 var_f4;
    SpaceData *space;
    s32 var_s2;
    s32 var_s4;
    s32 i;

    curPlayer = MBDPlayerGet(playerIndex);
    var_s2 = 0;
    var_s4 = 0;

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if (i == playerIndex) {
            continue;
        }
        player = MBDPlayerGet(i);
        if (curPlayer->clink == player->clink) {
            var_s4 += curPlayer->cidx == player->cidx;
        }
        if (curPlayer->nlink == player->clink) {
            var_s2 += curPlayer->nidx == player->cidx;
        }
    }

    space = MBDMasuGet(MBDMasuLinkMasuIdGet(curPlayer->clink, curPlayer->cidx));
    HuVecSubtract(&sp10, &MBDMasuGet(MBDMasuLinkMasuIdGet(curPlayer->nlink, curPlayer->nidx))->coords, &space->coords);
    var_f4 = MBDVecAngleGet(&sp10);
    if ((var_s4 == 0) || (!(mbdJumpAngleTbl[var_s4][0] < var_f4)) || (!(var_f4 <= mbdJumpAngleTbl[var_s4][1]))) {
        if (var_s2 != 0) {
            if (mbdJumpNextAngleTbl[var_s2][0] < 0.0f) {
                var_f4 -= 360.0f;
            }
            if (!(mbdJumpNextAngleTbl[var_s2][0] < var_f4) || (!(var_f4 <= mbdJumpNextAngleTbl[var_s2][1]))) {
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

s32 MBDTurnCoinGet(void) {
    s32 var_a0 = (GwSystem.current_turn - 1) / 5;

    if (var_a0 > 3) {
        var_a0 = 3;
    }
    return mbdTurnCoinTbl[var_a0];
}

void MBDTurnHelpCreate(void) {
    if (mbdTurnHelpWin0 == NULL) {
        mbdTurnHelpWin0 = MBDHelpWinCreate(2, 0xAE, 1);
    }
    if (mbdTurnHelpWin2 == NULL) {
        mbdTurnHelpWin2 = MBDHelpWinCreate(3, 0xCA, 1);
    }
    if (mbdTurnHelpWin3 == NULL) {
        mbdTurnHelpWin3 = MBDHelpWinCreate(0xD, 0xBC, 1);
    }
}

void MBDTurnHelpKill(void) {
    if (mbdTurnHelpWin0 != NULL) {
        MBDHelpWinKill(mbdTurnHelpWin0);
        mbdTurnHelpWin0 = NULL;
    }
    if (mbdTurnHelpWin1 != NULL) {
        MBDHelpWinKill(mbdTurnHelpWin1);
        mbdTurnHelpWin1 = NULL;
    }
    if (mbdTurnHelpWin2 != NULL) {
        MBDHelpWinKill(mbdTurnHelpWin2);
        mbdTurnHelpWin2 = NULL;
    }
    if (mbdTurnHelpWin3 != NULL) {
        MBDHelpWinKill(mbdTurnHelpWin3);
        mbdTurnHelpWin3 = NULL;
    }
}

void MBDGameModeWarpSet(void) {
    mbGameMode = 7;
    mbWipeType = WIPE_GOOMBA;
    MBDTurnHelpKill();
}

void MBDGameModeMgSet(void) {
    Process *temp_s1;
    GW_PLAYER *temp_s0;

    temp_s0 = MBDPlayerGet(CUR_PLAYER);
    temp_s1 = HuPrcCurrentGet();
    mbItemBtnF = 0;
    Hu3DMotionReset(temp_s0->player_obj->omObj1->model[0]);
    MBDPartnerMotionReset(GwSystem.current_player_index);
    mbTurnUnkF = 0;
    HuPrcChildLink(temp_s1, MBDMgCallCreate());
    HuPrcChildWatch();
    mbGameMode = 10;
    mbdExitFlag = 2;
    mbdExitMusFadeF = 1;
    mbWipeType = WIPE_TUMBLE;
    GwPlayer[0].group = 0;
    GwPlayer[1].group = 1;
    GwPlayer[2].group = 2;
    GwPlayer[3].group = 3;
}

void MBDMain(void) {
    GW_SYSTEM *system = &GwSystem;
    Process *curProc;
    Process *diceProc = NULL;
    GW_PLAYER *player;
    SpaceData *space;
    s16 masuId;
    s32 i;
    s32 coins;
    void *effect;
    Vec forward;

    curProc = HuPrcCurrentGet();

    while (1) {
        if ((mbGameMode == 0 || mbGameMode == 1) && system->current_player_index == 0) {
            if (!GWBoardFlagCheck(1) && system->current_turn >= 2) {
                switch (system->save_mode) {
                    case 1:
                        system->save_mode = 2;
                    case 0: {
                        s16 size[2];
                        s16 winId;

                        _SetFlag(0);
                        GWBoardFlagSet(0);

                        HuWinMesMaxSizeGet(1, size, 0x5900);
                        winId = HuWinCreate(0, 0, size[0], size[1], 0, 2);
                        HuWinBGTPLvlSet(winId, 0);
                        HuWinMesSet(winId, 0x5900, -1, -1);
                        HuWinMesSpeedSet(winId, 0);

                        while (HuWinStatGet(winId) != 0) {
                            HuPrcVSleep();
                        }

                        if (system->playMode & 4) {
                            _SetFlag(0x18);
                            _SetFlag(0x28);
                            SLSaveStory(1);
                        } else {
                            _SetFlag(0x17);
                            SLSaveBoardStory(1);
                        }

                        HuWinKill(winId);
                        HuWinMesMaxSizeGet(1, size, 0x5901);
                        winId = HuWinCreate(0, 0, size[0], size[1], 0, 2);
                        HuWinBGTPLvlSet(winId, 0);
                        HuWinMesSet(winId, 0x5901, -1, -1);
                        HuWinMesSpeedSet(winId, 0);
                        HuPrcSleep(15);
                        HuWinKill(winId);
                        break;
                    }
                }
            }

            GWBoardFlagClear(1);
            mbTurnUnkF = 0;
            mbdWalkEventResult = MBDMasuEventCall(-2, 7);
        }

        mbTurnUnkF = 1;

        for (i = 0; i < MBD_MAX_PLAYERS; i++) {
            MBDPlayerGet(i);
            MBDPlayerPosFixSet(i, 1);
        }

        player = MBDPlayerGet(system->current_player_index);
        SLPadAssign();
        GwPlayer[2].stat |= PLAYER_IS_CPU;
        GwPlayer[3].stat |= PLAYER_IS_CPU;
        masuId = MBDMasuLinkMasuIdGet(player->clink, player->cidx);
        space = MBDMasuGet(masuId);

        if (mbGameMode == 0 || mbGameMode == 1) {
            goto start;
        }

        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }

        mbItemBtnF = 1;

        switch (mbGameMode) {
        start:
            MBDMasuEventCall(-4, 7);
            Hu3DMotionReset(MBDPlayerGet(0)->player_obj->omObj1->model[0]);
            Hu3DMotionReset(MBDPlayerGet(1)->player_obj->omObj1->model[0]);
            MBDPartnerMotionReset(0);
            MBDPartnerMotionReset(1);
            MBDPlayerPartyMotionSet(-1, -1, 2);
            MBDCameraFocusModeSet(1);

            if (mbCameraZoomInstantF == 0) {
                mbCameraZoom = 1.4f;
                MBDCameraZoomSet(1.4f);
                HuPrcChildLink(curProc, MBDScissorWipeInStart());
            } else if (MBDScissorFullCheck() == 0) {
                mbCameraZoom = 1.4f;
                MBDCameraZoomSet(1.4f);
                HuPrcChildLink(curProc, MBDScissorWipeInStart());
            } else {
                mbCameraZoom = 1.4f;
                HuPrcChildLink(curProc, MBDCameraZoomMotStart(1.4f));
            }

            HuPrcChildWatch();
            default:
                HuPrcSleep(4);
                MBDPlayerVibrate(-1, 3);
                HuPrcChildLink(curProc, MBDTelopCreate(system->current_player_index));
                HuPrcChildWatch();
                MBDMasuEventCall(-5, 7);
            case 7:
            diceRoll:
                MBDTurnHelpCreate();
                mbCameraZoom = 1.7f;
                HuPrcChildLink(curProc, MBDCameraZoomMotStart(1.7f));
                if (duelUnkF1 == 0) {
                    diceProc = MBDSaiPlayerCreate(system->current_player_index);
                }
                HuPrcChildWatch();
                HuPrcSleep(1);

                mbCameraBtnF = 1;
                mbItemBtnF = 1;
                duelCancelEnableF = 1;

                if (duelUnkF1 != 0) {
                    GWBoardFlagClear(0x11);
                    MBDSaiSePlay(system->current_player_index);
                }

                HuPrcChildLink(curProc, diceProc);
                HuPrcChildWatch();
                MBDTurnHelpKill();

                mbCameraBtnF = 0;
                duelCancelEnableF = 0;
                mbWalkNum = MBDSaiValueGet(system->current_player_index);
                MBDPlayerDirNextSet(system->current_player_index);
                if (!(player->rev & 2)) {
                    MBDPlayerPartyMotionShiftSet(-1, 0, 0, 5, 2);
                } else {
                    MBDPlayerPartyMotionShiftSet(-1, 0, 0, 5, 6);
                }

                while (mbWalkNum != 0) {
                    MBDMasuEventCall(masuId, 8);

                    if (mbdWalkAttackHook != NULL) {
                        GW_PLAYER *opponent = MBDPlayerGet((s8)(system->current_player_index ^ 1));
                        s32 attackType = mbdWalkAttackHook();

                        if (attackType != -1) {
                            MBDPlayerPartyMotionSet(-1, -1, 2);
                            MBDSaiNumKill(player->turn);
                            mbTauntOffF = 1;
                            MBDPartnerAttackExec(attackType);
                            mbTauntOffF = 0;

                            if (mbTurnOnF != 0) {
                                player->star = 5;
                                opponent->star = 5;
                            }

                            if (opponent->star <= 0 || player->star <= 0) {
                                HuPrcChildLink(curProc, MBDCameraZoomMotStart(1.7f));
                                HuPrcChildWatch();
                                goto gameEnd;
                            }

                            MBDSaiNumShow(player->turn);
                            HuPrcChildLink(curProc, MBDCameraZoomMotStart(1.7f));
                            HuPrcChildWatch();
                            if (!(player->rev & 2)) {
                                MBDPlayerPartyMotionShiftSet(-1, 0, 0, 5, 2);
                            } else {
                                MBDPlayerPartyMotionShiftSet(-1, 0, 0, 5, 6);
                            }
                        }
                    }

                    {
                        s16 curLink = player->clink;
                        s16 curIdx = player->cidx;

                        player->clink = player->nlink;
                        player->cidx = player->nidx;
                        MBDPlayerPosFixSet((s8)(system->current_player_index ^ 1), (system->walk_speed * 7) + 8);
                        player->clink = curLink;
                        player->cidx = curIdx;
                    }

                    space = MBDMasuGet(MBDMasuLinkMasuIdGet(player->nlink, player->nidx));

                    if (player->player_obj->unk48 != 0) {
                        if (!(player->rev & 2)) {
                            MBDPlayerPartyMotionShiftSet(-1, 0, 0, 5, 2);
                        } else {
                            MBDPlayerPartyMotionShiftSet(-1, 0, 0, 5, 6);
                        }
                    }

                    if (system->current_board_index == 4 && space->unk_02 == 2) {
                        s32 seNo;

                        seNo = HuAudFXPlay(0x1EC);
                        MBDPlayerPartyMotionSet(-1, -1, 2);
                        MBDPlayerSpeedSet(-1, 1.0f);
                        effect = MBDPlayerVibrateObjCreate(-1, 1, 5);
                        MBDPlayerPartnerMoveExec(system->current_player_index, 0.73f);
                        MBDPlayerVibrateObjKill(effect);
                        HuAudFXStop(seNo);
                        HuPrcSleep(10);
                    } else {
                        switch (system->walk_speed) {
                            case 0:
                                MBDPlayerSpeedSet(-1, 1.5f);
                                MBDPlayerPartnerMoveExec(system->current_player_index, 5.0f);
                                break;
                            case 1:
                                MBDPlayerSpeedSet(-1, 1.0f);
                                MBDPlayerPartnerMoveExec(system->current_player_index, 4.0f);
                                break;
                            case 2:
                                MBDPlayerSpeedSet(-1, 0.75f);
                                MBDPlayerPartnerMoveExec(system->current_player_index, 3.0f);
                                break;
                        }
                        MBDPlayerSpeedSet(-1, 1.0f);
                    }

                    player->blink = player->clink;
                    player->bidx = player->cidx;
                    player->clink = player->nlink;
                    player->cidx = player->nidx;

                    if (!(player->rev & 1)) {
                        player->nidx++;
                    } else {
                        player->nidx--;
                    }

                    masuId = MBDMasuLinkMasuIdGet(player->clink, player->cidx);
                    space = MBDMasuGet(masuId);
                    MBDMasuCurSet(masuId);

                    switch (space->space_type) {
                        case MBD_MASU_TYPE_HAPPENING:
                        case MBD_MASU_TYPE_GAMEGUY:
                        case MBD_MASU_TYPE_REVERSE:
                        case MBD_MASU_TYPE_BASIC:
                        case MBD_MASU_TYPE_MINIGAME:
                        case MBD_MASU_TYPE_POWERUP:
                        case MBD_MASU_TYPE_CHR(CHAR_MARIO):
                        case MBD_MASU_TYPE_CHR(CHAR_LUIGI):
                        case MBD_MASU_TYPE_CHR(CHAR_PEACH):
                        case MBD_MASU_TYPE_CHR(CHAR_YOSHI):
                        case MBD_MASU_TYPE_CHR(CHAR_WARIO):
                        case MBD_MASU_TYPE_CHR(CHAR_DK):
                        case MBD_MASU_TYPE_CHR(CHAR_WALUIGI):
                        case MBD_MASU_TYPE_CHR(CHAR_DAISY):
                            MBDSaiNumCountDown(system->current_player_index);
                            mbWalkNum--;
                            MBDMasuBounceCreate(masuId);
                            break;
                    }

                    if (mbWalkNum != 0) {
                        MBDMasuPassSePlay(space->space_type);
                    } else {
                        MBDMasuLandSePlay(space->space_type);
                    }

                    mbdWalkEventResult = MBDMasuEventCall(masuId, 1);

                    if (mbdExitFlag < 0) {
                        continue;
                    }

                    mbGameMode = 2;
                    HuPrcSleep(-1);
                    case 2:
                        if (mbdWalkEventResult & 1) {
                            masuId = MBDMasuCurGet();
                            mbdWalkEventResult = MBDMasuEventCall(masuId, 2);
                            if (mbdExitFlag >= 0) {
                                mbGameMode = 3;
                                HuPrcSleep(-1);
                            }
                        }
                    case 3:
                    walkEventEnd:
                        if (mbdWalkEventResult & 2) {
                            mbWalkNum = 0;
                            continue;
                        }
                        MBDSaiNumShow(system->current_player_index);
                        HuPrcSleep(10);
                }

                if (mbdPakkunForceF == -1) {
                    mbdPakkunForceF = 0;
                } else if (player->stats.partners.frontID == 7 || player->stats.partners.backID == 7) {
                    if (duelUnkF1 == 0 && duelUnkF0 == 0) {
                        if (MBDRand(100.0f) < 50 || mbdPakkunForceF != 0) {
                            Vec dir;
                            Vec prevRot;
                            Object *partner;
                            Process *proc;

                            mbdPakkunForceF = 0;
                            MBDVecForwardSet(&forward);
                            MBDVecRotLerpCreate(&player->player_obj->rot, &forward, &player->player_obj->rot, 8);
                            MBDPlayerPartyMotionSet(-1, -1, 2);
                            MBDPartnerAttackMotLoad(7);
                            if (player->stats.partners.backID == 7) {
                                partner = MBDPartnerObjGet(system->current_player_index, 1);
                            } else {
                                partner = MBDPartnerObjGet(system->current_player_index, 0);
                            }
                            MBDVecDirGet(&partner->coords, &player->player_obj->coords, &dir);
                            HuVecCopy3F(&prevRot, &partner->rot);
                            MBDVecRotLerpCreate(&partner->rot, &dir, &partner->rot, 2);
                            MBDPartnerAttackMotSet(partner, 2, 0);
                            HuPrcSleep(5);
                            proc = HuPrcCurrentGet();
                            HuPrcChildLink(proc, MBDCameraZoomMotStart(2.0f));
                            MBDSaiTypeSet(system->current_player_index, 2);
                            diceProc = MBDSaiPlayerCreate(system->current_player_index);
                            GWBoardFlagSet(0x11);
                            MBDModelMotionWait(partner);
                            MBDPartnerAttackMotSet(partner, 3, 2);
                            MBDWinOpen(0x4F0D);
                            MBDWinKeyWaitKeep(system->current_player_index);
                            MBDWinClose();
                            MBDMotionShiftSet(partner, -1, 0, 5, 2);
                            MBDVecRotLerpCreate(&partner->rot, &prevRot, &partner->rot, 6);
                            HuPrcSleep(6);
                            MBDPartnerAttackMotKill();
                            MBDCameraFocusModeSet(1);
                            duelUnkF1 = 1;
                            goto diceRoll;
                        }
                    }
                }

                duelUnkF1 = 0;

                if (duelUnkF0 != 0) {
                    u8 tempLink = player->nlink;
                    u8 tempIdx = player->nidx;

                    player->nlink = player->blink;
                    player->nidx = player->bidx;
                    player->blink = tempLink;
                    player->bidx = tempIdx;
                    player->rev = 0;
                    duelUnkF0 = 0;
                }

                MBDPlayerPartyMotionSet(-1, -1, 2);
                masuId = MBDMasuLinkMasuIdGet(player->clink, player->cidx);

                switch (MBDMasuGet(masuId)->space_type) {
                    case MBD_MASU_TYPE_HAPPENING:
                        MBDPlayerVibrate(-1, 2);
                        GwSystem.boardData.halfWordBytes[2 + player->turn]++;
                        break;
                    case MBD_MASU_TYPE_GAMEGUY:
                        MBDPlayerVibrate(-1, 3);
                        GwSystem.boardData.halfWordBytes[4 + player->turn]++;
                        break;
                    case MBD_MASU_TYPE_REVERSE:
                        if (system->current_board_index != 5) {
                            MBDPlayerVibrate(-1, 1);
                        } else {
                            MBDPlayerVibrate(-1, 3);
                        }
                        GwSystem.boardData.halfWordBytes[6 + player->turn]++;
                        break;
                    case MBD_MASU_TYPE_MINIGAME:
                        MBDPlayerVibrate(-1, 0);
                        GwSystem.boardData.halfWordBytes[8 + player->turn]++;
                        break;
                    case MBD_MASU_TYPE_POWERUP:
                        MBDPlayerVibrate(-1, 2);
                        GwSystem.boardData.halfWordBytes[10 + player->turn]++;
                        break;
                    case 6:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                        GwSystem.boardData.halfWordBytes[12 + player->turn]++;
                        break;
                }

                mbGameMode = 4;
                mbdWalkEventResult = MBDMasuEventCall(masuId, 3);

                if (mbdExitFlag < 0) {
                    goto landed;
                }
                HuPrcSleep(-1);
            case 4:
                if (mbdWalkEventResult & 1) {
                    mbdWalkEventResult = MBDMasuEventCall(MBDMasuCurGet(), 4);
                    if (mbdExitFlag >= 0) {
                        mbGameMode = 5;
                        HuPrcSleep(-1);
                    }
                }
            case 5:
                HuPrcSleep(30);
            landed:
                MBDVecForwardSet(&forward);
                MBDVecRotLerpCreate(&player->player_obj->rot, &forward, &player->player_obj->rot, 8);
                masuId = MBDMasuLinkMasuIdGet(player->clink, player->cidx);
                space = MBDMasuGet(masuId);

                // Cast to s32 since this switch has a case -1 (unreachable for a u8 space type).
                switch ((s32)space->space_type) {
                    case MBD_MASU_TYPE_CHR(CHAR_MARIO):
                    case MBD_MASU_TYPE_CHR(CHAR_LUIGI):
                    case MBD_MASU_TYPE_CHR(CHAR_PEACH):
                    case MBD_MASU_TYPE_CHR(CHAR_YOSHI):
                    case MBD_MASU_TYPE_CHR(CHAR_WARIO):
                    case MBD_MASU_TYPE_CHR(CHAR_DK):
                    case MBD_MASU_TYPE_CHR(CHAR_WALUIGI):
                    case MBD_MASU_TYPE_CHR(CHAR_DAISY):
                        coins = MBDTurnCoinGet();

                        if (space->space_type - MBD_MASU_TYPE_CHR_BASE == GwPlayer[system->current_player_index].chr) {
                            MBDPlayerVibrate(-1, 1);
                            MBDCoinChangeCreate(system->current_player_index, coins);
                            MBDCoinTakeCreate(system->current_player_index, coins);
                            goto spaceEventEnd;
                        }

                        MBDPlayerVibrate(-1, 2);

                        if (player->stats.partners.frontID == 2 || player->stats.partners.backID == 2) {
                            Object *partner;
                            Vec pos;

                            if (player->stats.partners.backID == 2) {
                                partner = MBDPartnerObjGet(system->current_player_index, 1);
                            } else {
                                partner = MBDPartnerObjGet(system->current_player_index, 0);
                            }

                            HuPrcChildLink(curProc, MBDCameraZoomMotStart(2.0f));
                            HuPrcChildWatch();
                            HuVecCopy3F(&pos, &player->player_obj->coords);
                            MBDCameraFocusModeSet(4);
                            MBDCameraFocusVecSet(&pos);
                            HuPrcChildLink(curProc, MBDVecSpeedMoveCreate(&pos, &partner->coords, &pos, 2.0f));
                            HuPrcChildWatch();
                            MBDVecForwardSet(&forward);
                            MBDVecRotLerpCreate(&partner->rot, &forward, &partner->rot, 8);
                            HuPrcSleep(8);
                            MBDPartnerAttackMotLoad(2);
                            HuAudFXPlay(0x298);
                            MBDPartnerAttackMotSet(partner, 1, 0);
                            MBDModelMotionWait(partner);
                            MBDMotionSet(partner, -1, 2);
                            MBDPartnerAttackMotKill();
                            MBDDlgResultWinExec(0x1F1C);
                            MBDCameraFocusModeSet(3);
                            break;
                        }

                        if (GwPlayer[system->current_player_index].coin == 0) {
                            coins = 0;
                            MBDDlgResultWinExec(0x1F1B);
                        } else if (GwPlayer[system->current_player_index].coin < coins) {
                            coins = GwPlayer[system->current_player_index].coin;
                        }

                        if (coins == 0) {
                            break;
                        }

                        MBDCoinChangeCreate(system->current_player_index, -coins);
                        MBDCoinTakeCreate(system->current_player_index, -coins);
                        HuPrcSleep(30);
                        MBDCoinChangeStatusCreate(MBDMasuOwnerGet(masuId), coins);
                        MBDCoinTakeCreate(MBDMasuOwnerGet(masuId), coins);
                        HuPrcSleep(30);
                        break;

                    case MBD_MASU_TYPE_BASIC:
                        HuPrcSleep(8);
                        MBDMasuOwnerAdd(masuId, system->current_player_index);
                        MBDMasuOwnerTypeUpdate();
                        MBDMasuTypeListCreate();
                        HuAudFXPlay(0x201);
                        break;

                    case MBD_MASU_TYPE_HAPPENING:
                        if (mbdHatenaFunc == NULL) {
                            break;
                        }
                        HuPrcChildLink(curProc, omAddPrcObj(mbdHatenaFunc, 0x4800, 0, 0));
                        HuPrcChildWatch();
                        break;

                    case MBD_MASU_TYPE_GAMEGUY: {
                        Object *gameGuy;
                        Process *gameGuyProc;
                        s32 rand;
                        u32 idx;

                        HuPrcSleep(8);
                        gameGuy = MBDModelCreate(0x3D, NULL);
                        MBDModelTempAllocFree(gameGuy);
                        HuVecCopy3F(&gameGuy->coords, &player->player_obj->coords);
                        gameGuy->velocity.x = 100.0f;

                        while (gameGuy->velocity.x >= 30.0f) {
                            gameGuy->velocity.x -= 2.0f;
                            HuPrcVSleep();
                        }

                        gameGuyProc = MBDModelHoverCreate(gameGuy, 5.0f, 2.0f);

                        if (GwPlayer[system->current_player_index].coin != 0) {
                            HuAudFXPlay(0x2A1);
                            MBDDlgWinExec(10, 0x2F00);
                            GwPlayer[system->current_player_index].gameCoin = GwPlayer[system->current_player_index].coin;
                            MBDCoinChangeCreate(system->current_player_index, -GwPlayer[system->current_player_index].coin);
                            MBDCoinTakeCreate(system->current_player_index, -GwPlayer[system->current_player_index].coin);
                            HuPrcSleep(30);
                            MBDDlgWinExec(10, 0x2F02);
                            omDelPrcObj(gameGuyProc);

                            while (gameGuy->velocity.x >= 10.0f) {
                                gameGuy->velocity.x -= 2.0f;
                                HuPrcVSleep();
                            }

                            MBDModelJumpSet(gameGuy, 2.0f, 0.0001f);
                            MBDModelJumpSet(player->player_obj, 2.0f, 0.0001f);
                            HuPrcSleep(30);
                        } else {
                            HuAudFXPlay(0x2A1);
                            MBDDlgWinExec(10, 0x2F01);
                            omDelPrcObj(gameGuyProc);

                            while (gameGuy->velocity.x <= 100.0f) {
                                gameGuy->velocity.x += 4.0f;
                                HuPrcVSleep();
                            }

                            MBDModelKill(gameGuy);
                            goto turnEnd;
                        }

                        if (MBDPlayerComCheck(system->current_player_index) != 0 && system->show_com_minigames != 0) {
                            s32 chance = MBDRand(1000.0f);

                            if (chance < 500) {
                                GwPlayer[system->current_player_index].gameCoin = 0;
                                GwPlayer[system->current_player_index].bonusCoin = 0;
                            } else if (chance < 870) {
                                GwPlayer[system->current_player_index].bonusCoin = 2;
                            } else if (chance < 950) {
                                GwPlayer[system->current_player_index].bonusCoin = 4;
                            } else if (chance < 985) {
                                GwPlayer[system->current_player_index].bonusCoin = 8;
                            } else if (chance < 995) {
                                GwPlayer[system->current_player_index].bonusCoin = 16;
                            } else if (chance < 999) {
                                GwPlayer[system->current_player_index].bonusCoin = 32;
                            } else {
                                GwPlayer[system->current_player_index].bonusCoin = 64;
                            }

                            WipeCreateOut(WIPE_GAME_GUY, 16);
                            HuPrcSleep(17);
                            MBDModelKill(gameGuy);
                            MBDModelJumpSet(player->player_obj, 0.0f, 0.0f);
                            player->player_obj->velocity.x = 0.0f;
                            HuPrcSleep(5);
                            WipeCreateIn(WIPE_GAME_GUY, 16);
                            HuPrcSleep(17);
                        } else {
                            mbGameMode = 8;
                            mbdExitFlag = 2;
                            mbdExitMusFadeF = 1;
                            mbWipeType = WIPE_GAME_GUY;
                            GwPlayer[(s8)(system->current_player_index ^ 1)].group = 1;
                            GwPlayer[2].group = 1;
                            GwPlayer[3].group = 1;
                            player->group = 0;
                            rand = MBDRand(100.0f);

                            for (idx = 0; idx < ARRAY_COUNT(mbdGambleMgRateTbl); idx++) {
                                if (rand < mbdGambleMgRateTbl[idx]) {
                                    break;
                                }
                            }
                            if (idx == ARRAY_COUNT(mbdGambleMgRateTbl)) {
                                idx = ARRAY_COUNT(mbdGambleMgRateTbl) - 1;
                            }
                            system->minigame_index = mbdGambleMgTbl[idx];
                            HuPrcSleep(-1);
                        }
                    }
                    gameGuyResult:
                        if (MBDPlayerComCheck(system->current_player_index) != 0 && system->show_com_minigames != 0) {
                            char buf[8];
                            s32 total = GwPlayer[system->current_player_index].gameCoin * GwPlayer[system->current_player_index].bonusCoin;

                            if (total >= 999) {
                                total = 999;
                            }
                            sprintf(buf, "%d", total);
                            if (total != 0) {
                                MBDWinInsertOpen(0x2F03, buf, 0, 0, 0, 0);
                                MBDWinKeyWaitKeep(system->current_player_index);
                                MBDWinClose();
                            } else {
                                MBDDlgResultWinExec(0x2F04);
                                MBDPlayerMotionSet(-1, 2, 0);
                                PlayerFXPlay(0x286, system->current_player_index);
                                MBDModelMotionWait(player->player_obj);
                                HuPrcSleep(20);
                                MBDPlayerMotionShiftSet(-1, -1, 0, 5, 2);
                            }
                        }

                        if (GwPlayer[system->current_player_index].gameCoin != 0 && GwPlayer[system->current_player_index].bonusCoin != 0) {
                            MBDCoinChangeCreate(system->current_player_index, GwPlayer[system->current_player_index].gameCoin * GwPlayer[system->current_player_index].bonusCoin);
                            MBDCoinTakeCreate(system->current_player_index, GwPlayer[system->current_player_index].gameCoin * GwPlayer[system->current_player_index].bonusCoin);
                            if (MBDPlayerComCheck(system->current_player_index) != 0 && system->show_com_minigames != 0) {
                                HuPrcSleep(20);
                                MBDPlayerMotionSet(-1, 6, 0);
                                PlayerFXPlay(0x274, system->current_player_index);
                                MBDModelMotionWait(player->player_obj);
                                MBDPlayerMotionShiftSet(-1, -1, 0, 5, 2);
                            }
                        }

                        if (MBDPlayerComCheck(system->current_player_index) != 0 && system->show_com_minigames != 0) {
                            break;
                        }
                        goto spaceEventEnd;

                    case MBD_MASU_TYPE_MINIGAME:
                        HuPrcSleep(8);
                        MBDStatusShrink(-1);
                        MBDAuraAltCreate(&player->player_obj->coords);
                        HuAudFXPlay(0x2A7);
                        MBDDlgWinExec(0x15, 0x1F2F);
                        MBDGameModeMgSet();
                        mbGameMode = 9;
                        HuPrcSleep(-1);
                    spaceEventEnd:
                        HuPrcSleep(30);
                        break;

                    case MBD_MASU_TYPE_POWERUP: {
                        Object *partnerObj[2];

                        if (player->stats.partners.frontID == -1 && player->stats.partners.backID == -1) {
                            MBDDlgResultWinExec(0x1F1E);
                            break;
                        }
                        if ((player->stats.partners.frontID != -1 && player->stats.partners.frontPoweredUp == 2) ||
                            (player->stats.partners.backID != -1 && player->stats.partners.backPoweredUp == 2)) {
                            MBDDlgResultWinExec(0x1F1F);
                            break;
                        }

                        MBDAuraCreate(&player->player_obj->coords);
                        MBDAuraLandNoSe(1);
                        MBDAuraHoverStart();
                        HuAudFXPlay(0x159);
                        MBDDlgWinExec(0x16, 0x1F1D);
                        HuAudFXPlay(0x1F6);
                        effect = MBDPlayerVibrateObjCreate(-1, 0, 5);
                        MBDAuraSpinExec(0);
                        MBDPlayerVibrateObjKill(effect);
                        MBDAuraHoverStop();
                        MBDAuraRiseExec(2);
                        MBDAuraKill();

                        partnerObj[0] = NULL;
                        partnerObj[1] = NULL;

                        if (player->stats.partners.frontID != -1) {
                            partnerObj[0] = MBDModelCreate(0x38, NULL);
                            MBDModelTempAllocFree(partnerObj[0]);
                            HuVecCopy3F(&partnerObj[0]->coords, &MBDPartnerObjGet(system->current_player_index, 0)->coords);
                            Hu3DMotionAttrSet(partnerObj[0]->omObj1->model[0], 2, 0);
                        }
                        if (player->stats.partners.backID != -1) {
                            partnerObj[1] = MBDModelCreate(0x38, NULL);
                            MBDModelTempAllocFree(partnerObj[1]);
                            HuVecCopy3F(&partnerObj[1]->coords, &MBDPartnerObjGet(system->current_player_index, 1)->coords);
                            Hu3DMotionAttrSet(partnerObj[1]->omObj1->model[0], 2, 0);
                        }

                        HuAudFXPlay(0x1FA);

                        if (partnerObj[0] != NULL) {
                            MBDModelMotionWait(partnerObj[0]);
                            MBDModelKill(partnerObj[0]);
                        }
                        if (partnerObj[1] != NULL) {
                            MBDModelMotionWait(partnerObj[1]);
                            MBDModelKill(partnerObj[1]);
                        }

                        MBDPartnerPowerUp(system->current_player_index);
                        HuPrcChildLink(curProc, MBDTelopBannerCreate(0));
                        HuPrcChildWatch();
                        break;
                    }

                    case MBD_MASU_TYPE_REVERSE:
                        if (system->current_board_index == 5) {
                            break;
                        }
                        MBDSaiTypeSet(system->current_player_index, 1);
                        if (duelUnkF0 == 0) {
                            u8 tempLink = player->nlink;
                            u8 tempIdx = player->nidx;

                            player->nlink = player->blink;
                            player->nidx = player->bidx;
                            player->blink = tempLink;
                            player->bidx = tempIdx;
                        }
                        player->rev = 7;
                        duelUnkF0 = 1;
                        goto diceRoll;

                    case -1:
                    walkEventResume:
                        MBDPlayerPartyMotionSet(-1, -1, 2);
                        HuPrcSleep(30);
                        if (mbdWalkEndHook != NULL) {
                            mbdWalkEndHook();
                        }
                        mbdWalkEventResult = 0;
                        goto walkEventEnd;

                    default:
                        break;
                }

                mbGameMode = 6;
                mbdWalkEventResult = MBDMasuEventCall(masuId, 5);
                if (mbdExitFlag < 0) {
                    goto turnEnd;
                }
                HuPrcSleep(-1);
            case 6:
                HuPrcSleep(30);
            turnEnd:
                mbItemBtnF = 0;

                if (system->current_player_index > 0 && system->total_turns >= 0 &&
                    system->current_turn >= system->total_turns) {
                gameEnd:
                    HuAudFXPlay(0x20C);
                    MBDAuraAltCreate(&player->player_obj->coords);
                    HuAudFXPlay(0x2A6);
                    MBDDlgWinExecAllKey(0x15, 0x2000);
                    GwSystem.boardData.halfWordBytes[0] = MBDMasuOwnerNumGet(0);
                    GwSystem.boardData.halfWordBytes[1] = MBDMasuOwnerNumGet(1);
                    mbdExitFlag = 0x20;
                    mbdExitMusFadeF = 1;
                    mbWipeType = WIPE_STARS;
                    HuPrcSleep(-1);
                }

                HuPrcSleep(4);
                HuPrcChildLink(curProc, MBDScissorWipeOutStart());
                HuPrcChildWatch();
                MBDNextPlayerTurn();

                for (i = 0; i < MBD_MAX_PLAYERS; i++) {
                    MBDPlayerForwardSet(i);
                    MBDMotionSet(MBDPlayerGet(i)->player_obj, -1, 2);
                }

                HuPrcVSleep();
                MBDCameraRefresh(NULL);
                mbGameMode = 1;
                break;

            case 8:
                goto gameGuyResult;
            case 9:
                goto spaceEventEnd;
            case 10:
                goto walkEventResume;
        }
    }
}

void MBDMapScrollModeProc(void) {
    HuPrcVSleep();
    MBDMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    MBDExit();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

void MBDBtnProc(void) {
    Vec2f sp10;
    s32 curPlayerNo;
    s32 i;
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
        curPlayerNo = MBDPlayerTurnGet();
        for (i = 0; i < 4; i++) {
            if (ContBtnDown[i] & START_BUTTON) {
                MBDSaiSeStop(curPlayerNo);
                MBDCameraPos2DGet(&sp10);
                MBDCameraPos2DSet(&sp10);
                MBDPauseCreate(i);
                MBDSaiSeResume(curPlayerNo);
                break;
            }
            if (i < MBD_MAX_PLAYERS && MBDPlayerComCheck(i) == 0) {
                playerPadNo = GwPlayer[i].pad;
                if (i == curPlayerNo) {
                    if (duelCancelEnableF != 0 && (ContBtnDown[playerPadNo] & B_BUTTON)) {
                        MBDSaiSeStop(i);
                        winPauseF = 1;
                        omAllPause();
                        MBDPartnerDescExec(i);
                        omAllUPause();
                        winPauseF = 0;
                        MBDSaiSeResume(i);
                        break;
                    }
                    if (mbCameraBtnF != 0 && (ContBtnDown[playerPadNo] & R_TRIG)) {
                        MBDSaiSeStop(curPlayerNo);
                        MBDMapScrollExec(playerPadNo);
                        MBDSaiSeResume(curPlayerNo);
                        break;
                    }
                }
            }
        }
    }
}

void MBDStart(u32 arg0) {
    GW_PLAYER *player;
    s32 i;

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        s16 masuID;
        player = MBDPlayerGet(i);
        masuID = MBDMasuLinkMasuIdGet(player->clink, player->cidx);
        MBDPlayerPosMasuSet(i, masuID);
        MBDPartnerPosFix(i);
    }

    MBDBackThreadPriHighSet();
    MBDCameraSpeedDivSet(1.0f);
    MBDCameraSpeedSet(-1.0f);
    Hu3DScreenClearF = 1;
    switch (arg0) {
        case 0:
            switch (mbGameMode) {
                case 0:
                case 1:
                    WipeCreateIn(WIPE_TYPE_NORMAL, 0);
                    MBDScissorEmptySet();
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
                        MBDPlayerVibrate(0, 0);
                        MBDPlayerVibrate(1, 0);
                    } else {
                        WipeCreateIn(WIPE_TYPE_PREV, 0x10);
                    }
                    MBDCameraZoomSet(mbCameraZoom);
                    MBDScissorFullSet();
                    break;
            }
            MBDCameraPos3DSet(&GwPlayer[GwSystem.current_player_index].player_obj->coords);
            omAddPrcObj(MBDMain, 0xEFFF, 0x4000, 0);
            omAddPrcObj(MBDExitProc, 0x1005, 0, 0);
            omPrcSetStatBit(omAddPrcObj(MBDBtnProc, 0x1001, 0, 0), OM_STAT_NOALLPAUSE);
            mbCameraBtnF = 0;
            mbItemBtnF = 0;
            duelCancelEnableF = 0;
            omAddPrcObj(MBDCameraFocusProc, 0x1005, 0, 0);
            MBDCameraFocusModeSet(1);
            if (msmMusGetVolume(HuAudMusNo) < 0x7F) {
                MBDSeqVolUpStart();
                return;
            }
            return;
        case 1:
            MBDCameraPos3DSet(&GwPlayer[GwSystem.current_player_index].player_obj->coords);
            omAddPrcObj(MBDExitProc, 0x1005, 0, 0);
            omPrcSetStatBit(omAddPrcObj(MBDMapScrollModeProc, 0x1005, 0, 0), OM_STAT_NOALLPAUSE);
            mbCameraBtnF = 1;
            return;
        case 2:
            MBDStatusHideAll();
            MBDCameraFocusModeSet(0);
            break;
    }
}

void MBDExitReturnSet(s16 arg0) {
    ditherBak.unk_02 = 1;
    mbdExitFlag = 0x40;
    mbWipeType = arg0;
    mbdExitMusFadeF = 0;
}

void MBDWipeTypeNextSet(s32 arg0) {
    mbWipeTypeNext = arg0;
}

void MBDExitOvlCallEx(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    mbdExitOvlNo = arg0;
    mbdExitOvlEvent = arg1;
    mbdExitFlag = 8;
    mbWipeType = arg2;
    mbdExitMusFadeF = arg3;
}

void MBDExitOvlCall(s32 arg0, s16 arg1, s16 arg2) {
    MBDExitOvlCallEx(arg0, arg1, arg2, 0);
}

void MBDExitReq(void) {
    omSysExitReq = 1;
}

void MBDExitBoardSet(s16 arg0, s16 arg1) {
    mbdExitFlag = 0x10;
    mbWipeType = arg0;
    mbdExitMusFadeF = arg1;
    MBDBoardReturnOff();
}

s16 MBDExitFlagGet(void) {
    return mbdExitFlag;
}

void MBDCameraRefresh(Vec *arg0) {
    f32 temp_f20;
    f32 temp_f22;
    Vec *var_s0;

    var_s0 = arg0;
    MBDBackStreamStop();
    MBDBackStreamStart();
    temp_f22 = MBDCameraSpeedGet();
    MBDCameraSpeedSet(-1.0f);
    temp_f20 = MBDCameraSpeedDivGet();
    MBDCameraSpeedDivSet(1.0f);
    MBDBackThreadPriHighSet();
    if (var_s0 == NULL) {
        var_s0 = &MBDPlayerGet(CUR_PLAYER)->player_obj->coords;
    }
    MBDCameraPos3DSet(var_s0);
    HuPrcVSleep();
    MBDCameraSpeedDivSet(temp_f20);
    MBDCameraSpeedSet(temp_f22);
}
