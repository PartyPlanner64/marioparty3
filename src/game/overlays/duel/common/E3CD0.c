#include "common_duel.h"
#include "ovl_81.h"
#include "game/pause.h"

// this file is a duplicate of 10C230.c in ovl_80_shared_board
extern UnkE3CD0 *D_801054B0_name_81;
extern Vec *D_801054AC_name_81;
extern Vec D_801054A0_name_81;
extern s16 D_8010549E_name_81;
extern s16 D_800A12C8_main;
extern f32 D_800C9938_main;
extern s16 D_800CE1D0_main;
extern s16 D_800D124C_main;
extern s16 D_800D1380_main;
extern s16 D_800CE206;
extern s32 D_80105498_name_81;
extern s16 D_8010549C_name_81;
extern Vec D_801054B8_name_81[];
extern Vec D_801054D0_name_81[][2];
extern s32 D_80105490_name_81;

s16 D_80101A50_name_81 = 0;
s32 D_80101A54_name_81[] = { 91, 92, 93, 94, 95, 96, 97 };
s32 D_80101A70_name_81[] = { 100, 100, 100, 100, 100, 100, 101 };
void (*D_80101A8C_name_81)(void) = NULL;
process_func D_80101A90_name_81 = NULL;
s32 (*D_80101A94_name_81)(void) = NULL;
void (*D_80101A98_name_81)(void) = NULL;
u8 D_80101A9C_name_81[4] = { 67, 68, 69, 70 };
u8 D_80101AA0_name_81[4] = { 5, 30, 65, 100 };
f32 D_80101AA4_name_81[][2] = { { 0.0f, 0.0f }, { 200.0f, 250.0f }, { 110.0f, 250.0f }, { 70.0f, 290.0f }, { 0.0f, 360.0f } };
f32 D_80101ACC_name_81[][2] = { { 0.0f, 0.0f }, { 20.0f, 70.0f }, { -70.0f, 70.0f }, { 70.0f, 290.0f }, { 0.0f, 360.0f } };
u8 D_80101AF4_name_81[] = { 3, 5, 8, 10 };
DuelHelpWin *D_80101AF8_name_81 = NULL;
DuelHelpWin *D_80101AFC_name_81 = NULL;
DuelHelpWin *D_80101B00_name_81 = NULL;
DuelHelpWin *D_80101B04_name_81 = NULL;

void func_800FD6F4_name_81(void);
void func_800FFA28_name_81(Vec *arg0);
void *func_800FFC2C_name_81(s16, s16, s32);
void func_800FFCCC_name_81(void *);
void func_800EB164_name_81(s16 arg0, s32 arg1);
void func_800FAE18_name_81(Object *arg0, s16 arg1, s16 arg2);
void func_800F3880_name_81(s32 playerIndex, s16 arg1, u16 arg2);
void func_800F38DC_name_81(s32 playerIndex, s16 arg1, u16 arg2);

void func_800FBF00_name_81(s32 id, s16 event, u16 stat) {
    omOvlHisData *overlay = &mbovlhis[mbovlhisidx++];

    if (id != -2) {
        if (id == -1) {
            id = omovlhis[omovlhisidx].overlayID;
            overlay->overlayID = id;
        } else {
            overlay->overlayID = id;
        }
    } else {
        id = D_80101A54_name_81[GwSystem.current_board_index];
        overlay->overlayID = id;
    }

    overlay->event = event;
    overlay->stat = stat;

    if (mbovlhisidx >= ARRAY_COUNT(mbovlhis)) {
        mbovlhisidx = ARRAY_COUNT(mbovlhis) - 1;
    }
}

void func_800FBFA4_name_81(void) {
    D_800CD2A0_main.unk_02 = 1;
    mbovlhisidx = 0;

    if (GWBoardFlagCheck(1) == 0) {
        func_800FBF00_name_81(-2, 1, 0x4190);
        func_800FBF00_name_81(D_80101A70_name_81[GwSystem.current_board_index], 0, 0x4190);
    }
    func_800FC5D8_name_81();
    func_800EBAD4_name_81(GwSystem.message_speed);
    _ClearFlag(0xC);
    D_800D6A48_main = 0;
}

void func_800FC030_name_81(void) {
    omOvlHisData *overlay;

    D_800D4196_main = 1;
    if (mbovlhisidx != 0) {
        mbovlhisidx--;
        overlay = &mbovlhis[mbovlhisidx];
        omOvlCallEx(overlay->overlayID, overlay->event, overlay->stat);
        return;
    }
    if (D_800CD2A0_main.unk_02 != 0) {
        D_800D4196_main = 0;
        omOvlCallEx(D_80101A54_name_81[GwSystem.current_board_index], 2, 0x4190);
        return;
    }
    if (D_800D6A48_main != 0) {
        _SetFlag(0xC);
    } else {
        _ClearFlag(0xC);
    }
    omOvlReturnEx(1);
}

void func_800FC108_name_81(void) {
    D_800CD2A0_main.unk_02 = 0;
}

s16 func_800FC114_name_81(void) {
    return D_800D4196_main;
}

void func_800FC120_name_81(s16 arg0) {
    s16 temp_v0 = mbovlhisidx;

    mbovlhis[mbovlhisidx].event = arg0;
    mbovlhisidx = temp_v0 + 1;
    if (mbovlhisidx >= 5) {
        mbovlhisidx = 4;
    }
    func_800FBF00_name_81(-2, 3, 0x4190);
    omOvlReturnEx(1);
}

s32 func_800FC18C_name_81(void) {
    return mbGameMode;
}

void func_800FC198_name_81(omObjData *obj) {
    s32 *temp_s0 = HuPrcCurrentGet()->user_data;

    while (1) {
        if (
            (func_800F37B8_name_81(temp_s0[0]) == 0) &&
            (D_800A12D8_main == 0) &&
            ((GwSystem.current_player_index != temp_s0[0]) || (D_800A12D4_main == 0)) &&
            (D_800C9520_main[GwPlayer[temp_s0[0]].pad] & 0x20)) {
            PlayerFXPlay(0x2BD, temp_s0[0]);
        }
        HuPrcVSleep();
    }
}

void func_800FC260_name_81(s32 arg0, s16 arg1, s32 arg2) {
    Process *temp_v0_2;
    UnkOvl81_1 *temp_v0_3;
    s32 frontPartnerID;
    s32 backPartnerID;
    Object *playerObj;
    s32 i;

    func_800E8D10_name_81();
    func_800E4F50_name_81(hvq_data_ROM_START);

    if (arg0 >= 0) {
        MBDBackLoad(arg0);
    }

    func_800E94D0_name_81();

    if (arg1 >= 0) {
        func_800E9B10_name_81(0x13, arg1);
    }

    MBDModelInit();
    func_800F3F4C_name_81();
    func_800F3DFC_name_81(0);
    func_800F3DFC_name_81(1);

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        MBDModelTempAllocFree(MBDGetPlayerStruct(i)->player_obj);
        playerObj = MBDGetPlayerStruct(i)->player_obj;
        playerObj->flags |= 2;
        MBDModelDispOn(MBDGetPlayerStruct(i)->player_obj);
    }

    func_8001FDE8_main(MBDGetPlayerStruct(0)->player_obj->omObj1->model[0]);
    func_8001FDE8_main(MBDGetPlayerStruct(1)->player_obj->omObj1->model[0]);
    func_800F8C68_name_81(0);
    func_800F8C68_name_81(1);
    func_800F4300_name_81();
    func_800DF1B0_name_81();
    func_800E0CEC_name_81();
    func_800E2870_name_81();
    func_800F6390_name_81();

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        frontPartnerID = GwPlayer[i].stats.partners.frontID;
        backPartnerID = GwPlayer[i].stats.partners.backID;
        GwPlayer[i].stats.partners.frontID = PARTNER_KOOPA; //?
        GwPlayer[i].stats.partners.backID = PARTNER_KOOPA;  //?
        func_800F5BB4_name_81(i);
        func_800F5EB0_name_81(i);
        GwPlayer[i].stats.partners.frontID = frontPartnerID;
        GwPlayer[i].stats.partners.backID = backPartnerID;
        func_800F5BB4_name_81(i);
        func_800F5EB0_name_81(i);
    }

    func_800DAB1C_name_81();
    HuWinInit();
    func_800EB664_name_81();

    D_80105494_name_81 = -1;
    D_800D1380_main = 0;
    D_80105496_name_81 = 0;
    func_800F4080_name_81();
    D_80101A8C_name_81 = NULL;
    D_80101A90_name_81 = 0;
    D_80101A94_name_81 = NULL;
    D_80101A98_name_81 = NULL;
    for (i = 0; i < 2; i++) {
        temp_v0_2 = omAddPrcObj(func_800FC198_name_81, 0, 0, 0x40);
        temp_v0_3 = HuMemMemoryAlloc(temp_v0_2->heap, sizeof(UnkOvl81_1));
        temp_v0_2->user_data = temp_v0_3;
        temp_v0_3->unk_00 = i;
        omPrcSetStatBit(temp_v0_2, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    }
}

void func_800FC4E4_name_81(void) {
    func_800DBEB0_name_81();
    func_800F64FC_name_81();
    func_800E28B0_name_81();
    func_800E0E38_name_81();
    func_800DF210_name_81();
    func_800F4314_name_81();
    HuWinAllKill();
    func_800F4030_name_81();
    MBDModelClose();
    func_800E9D9C_name_81();
    func_800E9564_name_81();
    MBDBackKill();
    MBDBackClose();
    func_800E4FF4_name_81();
    func_800E90B4_name_81();

    if (D_80101A8C_name_81 != NULL) {
        D_80101A8C_name_81();
    }

    func_800FD55C_name_81();
}

// file split? many setters here
void func_800FC590_name_81(void (*arg0)(void)) {
    D_80101A98_name_81 = arg0;
}

void func_800FC59C_name_81(s32 (*arg0)(void)) {
    D_80101A94_name_81 = arg0;
}

void func_800FC5A8_name_81(process_func arg0) {
    D_80101A90_name_81 = arg0;
}

void func_800FC5B4_name_81(void (*arg0)(void)) {
    D_80101A8C_name_81 = arg0;
}

void func_800FC5C0_name_81(s32 arg0) {
    D_800CC0B8_main = arg0;
}

s16 func_800FC5CC_name_81(void) {
    return D_800CC0B8_main;
}

void func_800FC5D8_name_81(void) {
    GW_PLAYER *player;
    GW_SYSTEM *system = &GwSystem;
    GW_COMMON *common = &GwCommon;
    s32 i, j;

    mbGameMode = 0;
    mbWalkNum = 0;
    D_800CE1D0_main = 0;
    D_800D124C_main = 0;
    D_80101A50_name_81 = 0;
    D_800C9938_main = 1.4f;
    func_800DF154_name_81();
    func_800DAAB0_name_81();
    D_800A12C8_main = -1;
    D_800C9930_main = -1;
    D_800CE206 = 0;
    D_800A12D4_main = 1;
    D_800A12D8_main = 0;

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
            player = MBDGetPlayerStruct(i);
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

void func_800FC888_name_81(s32 arg0) {
    D_8010549E_name_81 = arg0;
}

s16 func_800FC894_name_81(void) {
    return D_8010549E_name_81;
}

void func_800FC8A0_name_81(Vec *arg0) {
    D_801054A0_name_81 = *arg0;
}

void func_800FC8C4_name_81(Vec *arg0) {
    D_801054AC_name_81 = arg0;
}

Vec *func_800FC8D0_name_81(void) {
    return D_801054AC_name_81;
}

void func_800FC8DC_name_81(UnkE3CD0 *arg0) {
    D_801054B0_name_81 = arg0;
}

void func_800FC8E8_name_81(void) {
    Vec2f sp10;
    Vec sp18;

    while (1) {
        switch (D_8010549E_name_81) {
            case 1:
                MBDCameraPos3DSet(&GwPlayer[GwSystem.current_player_index].player_obj->coords);
                break;
            case 2:
                MBDCameraPos3DSet(&D_801054A0_name_81);
                break;
            case 4:
                MBDCameraPos3DSet(D_801054AC_name_81);
                break;
            case 5:
                HuVecCopy3F(&sp18, &D_801054B0_name_81->unk_0C);
                sp18.y += D_801054B0_name_81->unk_30;
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

void func_800FC9FC_name_81(void) {
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

void func_800FCAB4_name_81(void) {
    do {
        HuPrcVSleep();
    } while (WipeStatGet() != 0);

    while (1) {
        HuPrcVSleep();
        if (D_800D530C_main == 0) {
            if (D_80105494_name_81 < 0) {
                continue;
            }
        }

        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }

        if (D_80105496_name_81 != 0) {
            HuAudSeqFadeOut(0x5A);
            D_800C9930_main = D_800C9930_main;
            if (D_800C9930_main != -1) {
                func_800039A4_main(D_800C9930_main, 0x5A);
                D_800C9930_main = -1;
                HuAudSeqStop();
            }
            if (D_800CE206 != 0) {
                HuAudSeqStop();
                D_800CE206 = 0;
            }
        }

        WipeCreateOut((s32)D_800D1380_main, 0x10);
        HuPrcSleep(0x11);
        func_800FC4E4_name_81();
        if (D_80105494_name_81 & 0x20) {
            D_800D6A48_main = 1;
            if (GwSystem.current_board_index == 5) {
                _CheckFlag(9);
            }
            func_800FBF00_name_81(0x62, 0, 0x4190);
            func_800FC108_name_81();
        }
        if (D_80105494_name_81 & 1) {
            func_800FC9FC_name_81();
        }
        if (D_80105494_name_81 & 2) {
            func_800FBF00_name_81(0x70, 0, 0x192);
        }
        if (D_80105494_name_81 & 8) {
            func_800FBF00_name_81(D_80105498_name_81, D_8010549C_name_81, 0x192);
        }
        omOvlReturnEx(1);
        omOvlKill();
        HuPrcVSleep();
    }
}

void func_800FCC84_name_81(s16 arg0) {
    arg0 -= 2;

    switch (arg0) {
        case 0:
        case 1:
        case 3:
        case 4:
        case 6:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            HuAudFXPlay(0x101);
            break;
    }
}

void func_800FCCCC_name_81(s16 arg0) {
    arg0 -= 2;

    switch (arg0) {
        case 3:
            if (GwSystem.current_board_index == 5) {
                HuAudFXPlay(0x1D4);
            } else {
                HuAudFXPlay(0x1D3);
            }
            break;
        case 8:
            HuAudFXPlay(0x1D2);
            break;
        case 1:
            HuAudFXPlay(0x12E);
            break;
        case 0:
        case 4:
        case 6:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            HuAudFXPlay(0x108);
    }
}

void func_800FCD44_name_81(s32 playerIndex, Vec *out) {
    Vec curPos;
    Vec nextPos;
    Vec prevPos;
    Vec dir;
    Vec prevDir;
    GW_PLAYER *player;
    f32 len;

    player = MBDGetPlayerStruct(playerIndex);
    func_800EB680_name_81(playerIndex, MBDMasuLinkMasuIdGet(player->clink, player->cidx), &curPos);
    func_800EB680_name_81(playerIndex, MBDMasuLinkMasuIdGet(player->nlink, player->nidx), &nextPos);
    func_800EB680_name_81(playerIndex, MBDMasuLinkMasuIdGet(player->blink, player->bidx), &prevPos);
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

void func_800FCF50_name_81(s32 playerIndex, s32 time) {
    Vec offset;
    Vec frontOfs;
    Vec backOfs;
    s32 playersShareSpace;
    GW_PLAYER *player;
    GW_PLAYER *curPlayer;
    SpaceData *space;
    Object *partner;
    GW_SYSTEM *system = &GwSystem;

    player = MBDGetPlayerStruct(playerIndex);
    space = MBDMasuGet(MBDMasuLinkMasuIdGet(player->clink, player->cidx));
    if (system->current_player_index == playerIndex) {
        HuVecCopy3F(&player->player_obj->coords, &space->coords);
        func_800ED214_name_81(playerIndex);
        return;
    }

    playersShareSpace = 0;
    curPlayer = MBDGetPlayerStruct(system->current_player_index);
    do { // reg alloc hack
        if (player->clink == curPlayer->clink) {
            playersShareSpace = player->cidx == curPlayer->cidx;
        }
    } while (0);

    HuVecCopy3F(&D_801054B8_name_81[playerIndex], &space->coords);
    if (playersShareSpace == 1) {
        func_800FCD44_name_81(playerIndex, &offset);
        HuVecAdd(&D_801054B8_name_81[playerIndex], &D_801054B8_name_81[playerIndex], &offset);
    }

    if (time < 2) {
        HuVecCopy3F(&player->player_obj->coords, &D_801054B8_name_81[playerIndex]);
    } else {
        func_800EBF2C_name_81(&player->player_obj->coords, &D_801054B8_name_81[playerIndex], &player->player_obj->coords, time);
    }

    func_800ECF1C_name_81(playerIndex, &frontOfs, &backOfs);

    if (player->stats.partners.frontID != -1) {
        partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_FRONT);
        HuVecCopyXYZ(&D_801054D0_name_81[playerIndex][PARTNER_FRONT],
                     D_801054B8_name_81[playerIndex].x + frontOfs.x,
                     D_801054B8_name_81[playerIndex].y + frontOfs.y,
                     D_801054B8_name_81[playerIndex].z + frontOfs.z);
        if (time < 2) {
            HuVecCopy3F(&partner->coords, &D_801054D0_name_81[playerIndex][PARTNER_FRONT]);
        } else {
            func_800EBF2C_name_81(&partner->coords, &D_801054D0_name_81[playerIndex][PARTNER_FRONT], &partner->coords, time);
        }
    }

    if (player->stats.partners.backID != -1) {
        partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_BACK);
        HuVecCopyXYZ(&D_801054D0_name_81[playerIndex][PARTNER_BACK],
                     D_801054B8_name_81[playerIndex].x + backOfs.x,
                     D_801054B8_name_81[playerIndex].y + backOfs.y,
                     D_801054B8_name_81[playerIndex].z + backOfs.z);
        if (time < 2) {
            HuVecCopy3F(&partner->coords, &D_801054D0_name_81[playerIndex][PARTNER_BACK]);
        } else {
            func_800EBF2C_name_81(&partner->coords, &D_801054D0_name_81[playerIndex][PARTNER_BACK], &partner->coords, time);
        }
    }
}

// if player should jump to next space
s32 func_800FD298_name_81(s32 playerIndex) {
    Vec sp10;
    GW_PLAYER *curPlayer;
    GW_PLAYER *player;
    f32 var_f4;
    SpaceData *space;
    s32 var_s2;
    s32 var_s4;
    s32 i;

    curPlayer = MBDGetPlayerStruct(playerIndex);
    var_s2 = 0;
    var_s4 = 0;

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if (i == playerIndex) {
            continue;
        }
        player = MBDGetPlayerStruct(i);
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
    if ((var_s4 == 0) || (!(D_80101AA4_name_81[var_s4][0] < var_f4)) || (!(var_f4 <= D_80101AA4_name_81[var_s4][1]))) {
        if (var_s2 != 0) {
            if (D_80101ACC_name_81[var_s2][0] < 0.0f) {
                var_f4 -= 360.0f;
            }
            if (!(D_80101ACC_name_81[var_s2][0] < var_f4) || (!(var_f4 <= D_80101ACC_name_81[var_s2][1]))) {
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

s32 func_800FD498_name_81(void) {
    s32 var_a0 = (GwSystem.current_turn - 1) / 5;

    if (var_a0 > 3) {
        var_a0 = 3;
    }
    return D_80101AF4_name_81[var_a0];
}

void func_800FD4DC_name_81(void) {
    if (D_80101AF8_name_81 == NULL) {
        D_80101AF8_name_81 = func_800E1824_name_81(2, 0xAE, 1);
    }
    if (D_80101B00_name_81 == NULL) {
        D_80101B00_name_81 = func_800E1824_name_81(3, 0xCA, 1);
    }
    if (D_80101B04_name_81 == NULL) {
        D_80101B04_name_81 = func_800E1824_name_81(0xD, 0xBC, 1);
    }
}

void func_800FD55C_name_81(void) {
    if (D_80101AF8_name_81 != NULL) {
        func_800E1854_name_81(D_80101AF8_name_81);
        D_80101AF8_name_81 = NULL;
    }
    if (D_80101AFC_name_81 != NULL) {
        func_800E1854_name_81(D_80101AFC_name_81);
        D_80101AFC_name_81 = NULL;
    }
    if (D_80101B00_name_81 != NULL) {
        func_800E1854_name_81(D_80101B00_name_81);
        D_80101B00_name_81 = NULL;
    }
    if (D_80101B04_name_81 != NULL) {
        func_800E1854_name_81(D_80101B04_name_81);
        D_80101B04_name_81 = NULL;
    }
}

void func_800FD5F0_name_81(void) {
    mbGameMode = 7;
    D_800D1380_main = 8;
    func_800FD55C_name_81();
}

void func_800FD620_name_81(void) {
    Process *temp_s1;
    GW_PLAYER *temp_s0;

    temp_s0 = MBDGetPlayerStruct(CUR_PLAYER);
    temp_s1 = HuPrcCurrentGet();
    mbItemBtnF = 0;
    func_8001FDE8_main(temp_s0->player_obj->omObj1->model[0]);
    func_800F8C68_name_81(GwSystem.current_player_index);
    D_800A12D4_main = 0;
    HuPrcChildLink(temp_s1, func_800E0888_name_81());
    HuPrcChildWatch();
    mbGameMode = 10;
    D_80105494_name_81 = 2;
    D_80105496_name_81 = 1;
    D_800D1380_main = 10;
    GwPlayer[0].group = 0;
    GwPlayer[1].group = 1;
    GwPlayer[2].group = 2;
    GwPlayer[3].group = 3;
}

void func_800FD6F4_name_81(void) {
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
                            func_8005035C_main(1);
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
            D_800A12D4_main = 0;
            D_80105490_name_81 = func_800EA4D4_name_81(-2, 7);
        }

        D_800A12D4_main = 1;

        for (i = 0; i < MBD_MAX_PLAYERS; i++) {
            MBDGetPlayerStruct(i);
            func_800FCF50_name_81(i, 1);
        }

        player = MBDGetPlayerStruct(system->current_player_index);
        func_80050E84_main();
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
            func_800EA4D4_name_81(-4, 7);
            func_8001FDE8_main(MBDGetPlayerStruct(0)->player_obj->omObj1->model[0]);
            func_8001FDE8_main(MBDGetPlayerStruct(1)->player_obj->omObj1->model[0]);
            func_800F8C68_name_81(0);
            func_800F8C68_name_81(1);
            func_800F38DC_name_81(-1, -1, 2);
            func_800FC888_name_81(1);

            if (D_800A12CC_main == 0) {
                D_800C9938_main = 1.4f;
                MBDCameraZoomSet(1.4f);
                HuPrcChildLink(curProc, func_800F429C_name_81());
            } else if (func_800F42C8_name_81() == 0) {
                D_800C9938_main = 1.4f;
                MBDCameraZoomSet(1.4f);
                HuPrcChildLink(curProc, func_800F429C_name_81());
            } else {
                D_800C9938_main = 1.4f;
                HuPrcChildLink(curProc, MBDCameraZoomMotStart(1.4f));
            }

            HuPrcChildWatch();
            default:
                HuPrcSleep(4);
                func_800FFAE0_name_81(-1, 3);
                HuPrcChildLink(curProc, func_800E39AC_name_81(system->current_player_index));
                HuPrcChildWatch();
                func_800EA4D4_name_81(-5, 7);
            case 7:
            diceRoll:
                func_800FD4DC_name_81();
                D_800C9938_main = 1.7f;
                HuPrcChildLink(curProc, MBDCameraZoomMotStart(1.7f));
                if (D_800D124C_main == 0) {
                    diceProc = func_800DC324_name_81(system->current_player_index);
                }
                HuPrcChildWatch();
                HuPrcSleep(1);

                mbCameraBtnF = 1;
                mbItemBtnF = 1;
                D_800D51F8_main = 1;

                if (D_800D124C_main != 0) {
                    GWBoardFlagClear(0x11);
                    func_800D9F90_name_81(system->current_player_index);
                }

                HuPrcChildLink(curProc, diceProc);
                HuPrcChildWatch();
                func_800FD55C_name_81();

                mbCameraBtnF = 0;
                D_800D51F8_main = 0;
                mbWalkNum = func_800DC0B4_name_81(system->current_player_index);
                func_800ECE38_name_81(system->current_player_index);
                if (!(player->rev & 2)) {
                    func_800F3A04_name_81(-1, 0, 0, 5, 2);
                } else {
                    func_800F3A04_name_81(-1, 0, 0, 5, 6);
                }

                while (mbWalkNum != 0) {
                    func_800EA4D4_name_81(masuId, 8);

                    if (D_80101A94_name_81 != NULL) {
                        GW_PLAYER *opponent = MBDGetPlayerStruct((s8)(system->current_player_index ^ 1));
                        s32 attackType = D_80101A94_name_81();

                        if (attackType != -1) {
                            func_800F38DC_name_81(-1, -1, 2);
                            func_800DB3E0_name_81(player->turn);
                            D_800A12D8_main = 1;
                            func_800F924C_name_81(attackType);
                            D_800A12D8_main = 0;

                            if (mbTurnOnF != 0) {
                                player->star = 5;
                                opponent->star = 5;
                            }

                            if (opponent->star <= 0 || player->star <= 0) {
                                HuPrcChildLink(curProc, MBDCameraZoomMotStart(1.7f));
                                HuPrcChildWatch();
                                goto gameEnd;
                            }

                            func_800DADA0_name_81(player->turn);
                            HuPrcChildLink(curProc, MBDCameraZoomMotStart(1.7f));
                            HuPrcChildWatch();
                            if (!(player->rev & 2)) {
                                func_800F3A04_name_81(-1, 0, 0, 5, 2);
                            } else {
                                func_800F3A04_name_81(-1, 0, 0, 5, 6);
                            }
                        }
                    }

                    {
                        s16 curLink = player->clink;
                        s16 curIdx = player->cidx;

                        player->clink = player->nlink;
                        player->cidx = player->nidx;
                        func_800FCF50_name_81((s8)(system->current_player_index ^ 1), (system->walk_speed * 7) + 8);
                        player->clink = curLink;
                        player->cidx = curIdx;
                    }

                    space = MBDMasuGet(MBDMasuLinkMasuIdGet(player->nlink, player->nidx));

                    if (player->player_obj->unk48 != 0) {
                        if (!(player->rev & 2)) {
                            func_800F3A04_name_81(-1, 0, 0, 5, 2);
                        } else {
                            func_800F3A04_name_81(-1, 0, 0, 5, 6);
                        }
                    }

                    if (system->current_board_index == 4 && space->unk_02 == 2) {
                        s32 seNo;

                        seNo = HuAudFXPlay(0x1EC);
                        func_800F38DC_name_81(-1, -1, 2);
                        func_800F3AF4_name_81(-1, 1.0f);
                        effect = func_800FFC2C_name_81(-1, 1, 5);
                        func_800ECC34_name_81(system->current_player_index, 0.73f);
                        func_800FFCCC_name_81(effect);
                        HuAudFXStop(seNo);
                        HuPrcSleep(10);
                    } else {
                        switch (system->walk_speed) {
                            case 0:
                                func_800F3AF4_name_81(-1, 1.5f);
                                func_800ECC34_name_81(system->current_player_index, 5.0f);
                                break;
                            case 1:
                                func_800F3AF4_name_81(-1, 1.0f);
                                func_800ECC34_name_81(system->current_player_index, 4.0f);
                                break;
                            case 2:
                                func_800F3AF4_name_81(-1, 0.75f);
                                func_800ECC34_name_81(system->current_player_index, 3.0f);
                                break;
                        }
                        func_800F3AF4_name_81(-1, 1.0f);
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
                    func_800EA698_name_81(masuId);

                    switch (space->space_type) {
                        case 2:
                        case 3:
                        case 5:
                        case 6:
                        case 8:
                        case 10:
                        case 11:
                        case 12:
                        case 13:
                        case 14:
                        case 15:
                        case 16:
                        case 17:
                        case 18:
                            func_800DB4DC_name_81(system->current_player_index);
                            mbWalkNum--;
                            func_800EA388_name_81(masuId);
                            break;
                    }

                    if (mbWalkNum != 0) {
                        func_800FCC84_name_81(space->space_type);
                    } else {
                        func_800FCCCC_name_81(space->space_type);
                    }

                    D_80105490_name_81 = func_800EA4D4_name_81(masuId, 1);

                    if (D_80105494_name_81 < 0) {
                        continue;
                    }

                    mbGameMode = 2;
                    HuPrcSleep(-1);
                    case 2:
                        if (D_80105490_name_81 & 1) {
                            masuId = func_800EA6A4_name_81();
                            D_80105490_name_81 = func_800EA4D4_name_81(masuId, 2);
                            if (D_80105494_name_81 >= 0) {
                                mbGameMode = 3;
                                HuPrcSleep(-1);
                            }
                        }
                    case 3:
                    walkEventEnd:
                        if (D_80105490_name_81 & 2) {
                            mbWalkNum = 0;
                            continue;
                        }
                        func_800DADA0_name_81(system->current_player_index);
                        HuPrcSleep(10);
                }

                if (D_80101A50_name_81 == -1) {
                    D_80101A50_name_81 = 0;
                } else if (player->stats.partners.frontID == 7 || player->stats.partners.backID == 7) {
                    if (D_800D124C_main == 0 && D_800CE1D0_main == 0) {
                        if (func_800EFE20_name_81(100.0f) < 50 || D_80101A50_name_81 != 0) {
                            Vec dir;
                            Vec prevRot;
                            Object *partner;
                            Process *proc;

                            D_80101A50_name_81 = 0;
                            func_800EB7BC_name_81(&forward);
                            func_800EBC60_name_81(&player->player_obj->rot, &forward, &player->player_obj->rot, 8);
                            func_800F38DC_name_81(-1, -1, 2);
                            func_800FAD04_name_81(7);
                            if (player->stats.partners.backID == 7) {
                                partner = MBDGetPlayerPartnerRef(system->current_player_index, 1);
                            } else {
                                partner = MBDGetPlayerPartnerRef(system->current_player_index, 0);
                            }
                            MBDVecDirGet(&partner->coords, &player->player_obj->coords, &dir);
                            HuVecCopy3F(&prevRot, &partner->rot);
                            func_800EBC60_name_81(&partner->rot, &dir, &partner->rot, 2);
                            func_800FAE18_name_81(partner, 2, 0);
                            HuPrcSleep(5);
                            proc = HuPrcCurrentGet();
                            HuPrcChildLink(proc, MBDCameraZoomMotStart(2.0f));
                            func_800DB624_name_81(system->current_player_index, 2);
                            diceProc = func_800DC324_name_81(system->current_player_index);
                            GWBoardFlagSet(0x11);
                            func_800EFABC_name_81(partner);
                            func_800FAE18_name_81(partner, 3, 2);
                            func_800EAD08_name_81(0x4F0D);
                            func_800EAF70_name_81(system->current_player_index);
                            func_800EAF94_name_81();
                            MBDMotionShiftSet(partner, -1, 0, 5, 2);
                            func_800EBC60_name_81(&partner->rot, &prevRot, &partner->rot, 6);
                            HuPrcSleep(6);
                            func_800FADB4_name_81();
                            func_800FC888_name_81(1);
                            D_800D124C_main = 1;
                            goto diceRoll;
                        }
                    }
                }

                D_800D124C_main = 0;

                if (D_800CE1D0_main != 0) {
                    u8 tempLink = player->nlink;
                    u8 tempIdx = player->nidx;

                    player->nlink = player->blink;
                    player->nidx = player->bidx;
                    player->blink = tempLink;
                    player->bidx = tempIdx;
                    player->rev = 0;
                    D_800CE1D0_main = 0;
                }

                func_800F38DC_name_81(-1, -1, 2);
                masuId = MBDMasuLinkMasuIdGet(player->clink, player->cidx);

                switch (MBDMasuGet(masuId)->space_type) {
                    case 2:
                        func_800FFAE0_name_81(-1, 2);
                        GwSystem.boardData.halfWordBytes[2 + player->turn]++;
                        break;
                    case 3:
                        func_800FFAE0_name_81(-1, 3);
                        GwSystem.boardData.halfWordBytes[4 + player->turn]++;
                        break;
                    case 5:
                        if (system->current_board_index != 5) {
                            func_800FFAE0_name_81(-1, 1);
                        } else {
                            func_800FFAE0_name_81(-1, 3);
                        }
                        GwSystem.boardData.halfWordBytes[6 + player->turn]++;
                        break;
                    case 8:
                        func_800FFAE0_name_81(-1, 0);
                        GwSystem.boardData.halfWordBytes[8 + player->turn]++;
                        break;
                    case 10:
                        func_800FFAE0_name_81(-1, 2);
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
                D_80105490_name_81 = func_800EA4D4_name_81(masuId, 3);

                if (D_80105494_name_81 < 0) {
                    goto landed;
                }
                HuPrcSleep(-1);
            case 4:
                if (D_80105490_name_81 & 1) {
                    D_80105490_name_81 = func_800EA4D4_name_81(func_800EA6A4_name_81(), 4);
                    if (D_80105494_name_81 >= 0) {
                        mbGameMode = 5;
                        HuPrcSleep(-1);
                    }
                }
            case 5:
                HuPrcSleep(30);
            landed:
                func_800EB7BC_name_81(&forward);
                func_800EBC60_name_81(&player->player_obj->rot, &forward, &player->player_obj->rot, 8);
                masuId = MBDMasuLinkMasuIdGet(player->clink, player->cidx);
                space = MBDMasuGet(masuId);

                // Cast to s32 since this switch has a case -1 (unreachable for a u8 space type).
                switch ((s32)space->space_type) {
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                        coins = func_800FD498_name_81();

                        if (space->space_type - 11 == GwPlayer[system->current_player_index].chr) {
                            func_800FFAE0_name_81(-1, 1);
                            func_800E14D8_name_81(system->current_player_index, coins);
                            func_800F7378_name_81(system->current_player_index, coins);
                            goto spaceEventEnd;
                        }

                        func_800FFAE0_name_81(-1, 2);

                        if (player->stats.partners.frontID == 2 || player->stats.partners.backID == 2) {
                            Object *partner;
                            Vec pos;

                            if (player->stats.partners.backID == 2) {
                                partner = MBDGetPlayerPartnerRef(system->current_player_index, 1);
                            } else {
                                partner = MBDGetPlayerPartnerRef(system->current_player_index, 0);
                            }

                            HuPrcChildLink(curProc, MBDCameraZoomMotStart(2.0f));
                            HuPrcChildWatch();
                            HuVecCopy3F(&pos, &player->player_obj->coords);
                            func_800FC888_name_81(4);
                            func_800FC8C4_name_81(&pos);
                            HuPrcChildLink(curProc, func_800EC1E4_name_81(&pos, &partner->coords, &pos, 2.0f));
                            HuPrcChildWatch();
                            func_800EB7BC_name_81(&forward);
                            func_800EBC60_name_81(&partner->rot, &forward, &partner->rot, 8);
                            HuPrcSleep(8);
                            func_800FAD04_name_81(2);
                            HuAudFXPlay(0x298);
                            func_800FAE18_name_81(partner, 1, 0);
                            func_800EFABC_name_81(partner);
                            MBDMotionSet(partner, -1, 2);
                            func_800FADB4_name_81();
                            func_800EAFC4_name_81(0x1F1C);
                            func_800FC888_name_81(3);
                            break;
                        }

                        if (GwPlayer[system->current_player_index].coin == 0) {
                            coins = 0;
                            func_800EAFC4_name_81(0x1F1B);
                        } else if (GwPlayer[system->current_player_index].coin < coins) {
                            coins = GwPlayer[system->current_player_index].coin;
                        }

                        if (coins == 0) {
                            break;
                        }

                        func_800E14D8_name_81(system->current_player_index, -coins);
                        func_800F7378_name_81(system->current_player_index, -coins);
                        HuPrcSleep(30);
                        func_800E14B0_name_81(func_800EA848_name_81(masuId), coins);
                        func_800F7378_name_81(func_800EA848_name_81(masuId), coins);
                        HuPrcSleep(30);
                        break;

                    case 6:
                        HuPrcSleep(8);
                        func_800EA788_name_81(masuId, system->current_player_index);
                        func_800EA7D4_name_81();
                        func_800EA97C_name_81();
                        HuAudFXPlay(0x201);
                        break;

                    case 2:
                        if (D_80101A90_name_81 == NULL) {
                            break;
                        }
                        HuPrcChildLink(curProc, omAddPrcObj(D_80101A90_name_81, 0x4800, 0, 0));
                        HuPrcChildWatch();
                        break;

                    case 3: {
                        Object *gameGuy;
                        Process *gameGuyProc;
                        s32 rand;
                        u32 idx;

                        HuPrcSleep(8);
                        gameGuy = func_800D8010_name_81(0x3D, NULL);
                        MBDModelTempAllocFree(gameGuy);
                        HuVecCopy3F(&gameGuy->coords, &player->player_obj->coords);
                        gameGuy->velocity.x = 100.0f;

                        while (gameGuy->velocity.x >= 30.0f) {
                            gameGuy->velocity.x -= 2.0f;
                            HuPrcVSleep();
                        }

                        gameGuyProc = func_800EDEC4_name_81(gameGuy, 5.0f, 2.0f);

                        if (GwPlayer[system->current_player_index].coin != 0) {
                            HuAudFXPlay(0x2A1);
                            func_800EB140_name_81(10, 0x2F00);
                            GwPlayer[system->current_player_index].gameCoin = GwPlayer[system->current_player_index].coin;
                            func_800E14D8_name_81(system->current_player_index, -GwPlayer[system->current_player_index].coin);
                            func_800F7378_name_81(system->current_player_index, -GwPlayer[system->current_player_index].coin);
                            HuPrcSleep(30);
                            func_800EB140_name_81(10, 0x2F02);
                            omDelPrcObj(gameGuyProc);

                            while (gameGuy->velocity.x >= 10.0f) {
                                gameGuy->velocity.x -= 2.0f;
                                HuPrcVSleep();
                            }

                            func_800EF7C8_name_81(gameGuy, 2.0f, 0.0001f);
                            func_800EF7C8_name_81(player->player_obj, 2.0f, 0.0001f);
                            HuPrcSleep(30);
                        } else {
                            HuAudFXPlay(0x2A1);
                            func_800EB140_name_81(10, 0x2F01);
                            omDelPrcObj(gameGuyProc);

                            while (gameGuy->velocity.x <= 100.0f) {
                                gameGuy->velocity.x += 4.0f;
                                HuPrcVSleep();
                            }

                            MBDModelKill(gameGuy);
                            goto turnEnd;
                        }

                        if (func_800F37B8_name_81(system->current_player_index) != 0 && system->show_com_minigames != 0) {
                            s32 chance = func_800EFE20_name_81(1000.0f);

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

                            WipeCreateOut(9, 16);
                            HuPrcSleep(17);
                            MBDModelKill(gameGuy);
                            func_800EF7C8_name_81(player->player_obj, 0.0f, 0.0f);
                            player->player_obj->velocity.x = 0.0f;
                            HuPrcSleep(5);
                            WipeCreateIn(9, 16);
                            HuPrcSleep(17);
                        } else {
                            mbGameMode = 8;
                            D_80105494_name_81 = 2;
                            D_80105496_name_81 = 1;
                            D_800D1380_main = 9;
                            GwPlayer[(s8)(system->current_player_index ^ 1)].group = 1;
                            GwPlayer[2].group = 1;
                            GwPlayer[3].group = 1;
                            player->group = 0;
                            rand = func_800EFE20_name_81(100.0f);

                            for (idx = 0; idx < ARRAY_COUNT(D_80101AA0_name_81); idx++) {
                                if (rand < D_80101AA0_name_81[idx]) {
                                    break;
                                }
                            }
                            if (idx == ARRAY_COUNT(D_80101AA0_name_81)) {
                                idx = ARRAY_COUNT(D_80101AA0_name_81) - 1;
                            }
                            system->minigame_index = D_80101A9C_name_81[idx];
                            HuPrcSleep(-1);
                        }
                    }
                    gameGuyResult:
                        if (func_800F37B8_name_81(system->current_player_index) != 0 && system->show_com_minigames != 0) {
                            char buf[8];
                            s32 total = GwPlayer[system->current_player_index].gameCoin * GwPlayer[system->current_player_index].bonusCoin;

                            if (total >= 999) {
                                total = 999;
                            }
                            sprintf(buf, "%d", total);
                            if (total != 0) {
                                func_800EADBC_name_81(0x2F03, buf, 0, 0, 0, 0);
                                func_800EAF70_name_81(system->current_player_index);
                                func_800EAF94_name_81();
                            } else {
                                func_800EAFC4_name_81(0x2F04);
                                func_800F3880_name_81(-1, 2, 0);
                                PlayerFXPlay(0x286, system->current_player_index);
                                func_800EFABC_name_81(player->player_obj);
                                HuPrcSleep(20);
                                func_800F397C_name_81(-1, -1, 0, 5, 2);
                            }
                        }

                        if (GwPlayer[system->current_player_index].gameCoin != 0 && GwPlayer[system->current_player_index].bonusCoin != 0) {
                            func_800E14D8_name_81(system->current_player_index, GwPlayer[system->current_player_index].gameCoin * GwPlayer[system->current_player_index].bonusCoin);
                            func_800F7378_name_81(system->current_player_index, GwPlayer[system->current_player_index].gameCoin * GwPlayer[system->current_player_index].bonusCoin);
                            if (func_800F37B8_name_81(system->current_player_index) != 0 && system->show_com_minigames != 0) {
                                HuPrcSleep(20);
                                func_800F3880_name_81(-1, 6, 0);
                                PlayerFXPlay(0x274, system->current_player_index);
                                func_800EFABC_name_81(player->player_obj);
                                func_800F397C_name_81(-1, -1, 0, 5, 2);
                            }
                        }

                        if (func_800F37B8_name_81(system->current_player_index) != 0 && system->show_com_minigames != 0) {
                            break;
                        }
                        goto spaceEventEnd;

                    case 8:
                        HuPrcSleep(8);
                        func_800F74E4_name_81(-1);
                        func_800EEC40_name_81(&player->player_obj->coords);
                        HuAudFXPlay(0x2A7);
                        func_800EB140_name_81(0x15, 0x1F2F);
                        func_800FD620_name_81();
                        mbGameMode = 9;
                        HuPrcSleep(-1);
                    spaceEventEnd:
                        HuPrcSleep(30);
                        break;

                    case 10: {
                        Object *partnerObj[2];

                        if (player->stats.partners.frontID == -1 && player->stats.partners.backID == -1) {
                            func_800EAFC4_name_81(0x1F1E);
                            break;
                        }
                        if ((player->stats.partners.frontID != -1 && player->stats.partners.frontPoweredUp == 2) ||
                            (player->stats.partners.backID != -1 && player->stats.partners.backPoweredUp == 2)) {
                            func_800EAFC4_name_81(0x1F1F);
                            break;
                        }

                        func_800EDD50_name_81(&player->player_obj->coords);
                        func_800EE0F4_name_81(1);
                        func_800EDF48_name_81();
                        HuAudFXPlay(0x159);
                        func_800EB140_name_81(0x16, 0x1F1D);
                        HuAudFXPlay(0x1F6);
                        effect = func_800FFC2C_name_81(-1, 0, 5);
                        func_800EE74C_name_81(0);
                        func_800FFCCC_name_81(effect);
                        func_800EDF78_name_81();
                        func_800EE468_name_81(2);
                        func_800EDDBC_name_81();

                        partnerObj[0] = NULL;
                        partnerObj[1] = NULL;

                        if (player->stats.partners.frontID != -1) {
                            partnerObj[0] = func_800D8010_name_81(0x38, NULL);
                            MBDModelTempAllocFree(partnerObj[0]);
                            HuVecCopy3F(&partnerObj[0]->coords, &MBDGetPlayerPartnerRef(system->current_player_index, 0)->coords);
                            func_8001C814_main(partnerObj[0]->omObj1->model[0], 2, 0);
                        }
                        if (player->stats.partners.backID != -1) {
                            partnerObj[1] = func_800D8010_name_81(0x38, NULL);
                            MBDModelTempAllocFree(partnerObj[1]);
                            HuVecCopy3F(&partnerObj[1]->coords, &MBDGetPlayerPartnerRef(system->current_player_index, 1)->coords);
                            func_8001C814_main(partnerObj[1]->omObj1->model[0], 2, 0);
                        }

                        HuAudFXPlay(0x1FA);

                        if (partnerObj[0] != NULL) {
                            func_800EFABC_name_81(partnerObj[0]);
                            MBDModelKill(partnerObj[0]);
                        }
                        if (partnerObj[1] != NULL) {
                            func_800EFABC_name_81(partnerObj[1]);
                            MBDModelKill(partnerObj[1]);
                        }

                        Duel_PowerUpPartners(system->current_player_index);
                        HuPrcChildLink(curProc, func_800E4A74_name_81(0));
                        HuPrcChildWatch();
                        break;
                    }

                    case 5:
                        if (system->current_board_index == 5) {
                            break;
                        }
                        func_800DB624_name_81(system->current_player_index, 1);
                        if (D_800CE1D0_main == 0) {
                            u8 tempLink = player->nlink;
                            u8 tempIdx = player->nidx;

                            player->nlink = player->blink;
                            player->nidx = player->bidx;
                            player->blink = tempLink;
                            player->bidx = tempIdx;
                        }
                        player->rev = 7;
                        D_800CE1D0_main = 1;
                        goto diceRoll;

                    case -1:
                    walkEventResume:
                        func_800F38DC_name_81(-1, -1, 2);
                        HuPrcSleep(30);
                        if (D_80101A98_name_81 != NULL) {
                            D_80101A98_name_81();
                        }
                        D_80105490_name_81 = 0;
                        goto walkEventEnd;

                    default:
                        break;
                }

                mbGameMode = 6;
                D_80105490_name_81 = func_800EA4D4_name_81(masuId, 5);
                if (D_80105494_name_81 < 0) {
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
                    func_800EEC40_name_81(&player->player_obj->coords);
                    HuAudFXPlay(0x2A6);
                    func_800EB164_name_81(0x15, 0x2000);
                    GwSystem.boardData.halfWordBytes[0] = func_800EA940_name_81(0);
                    GwSystem.boardData.halfWordBytes[1] = func_800EA940_name_81(1);
                    D_80105494_name_81 = 0x20;
                    D_80105496_name_81 = 1;
                    D_800D1380_main = 2;
                    HuPrcSleep(-1);
                }

                HuPrcSleep(4);
                HuPrcChildLink(curProc, func_800F41DC_name_81());
                HuPrcChildWatch();
                func_800FC9FC_name_81();

                for (i = 0; i < MBD_MAX_PLAYERS; i++) {
                    func_800EB7D8_name_81(i);
                    MBDMotionSet(MBDGetPlayerStruct(i)->player_obj, -1, 2);
                }

                HuPrcVSleep();
                func_800FFA28_name_81(NULL);
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

void func_800FF420_name_81(void) {
    HuPrcVSleep();
    func_80100CEC_name_81(GwPlayer[GwSystem.current_player_index].pad);
    func_800FC4E4_name_81();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

void func_800FF480_name_81(void) {
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
        curPlayerNo = MBDGetCurrentPlayerIndex();
        for (i = 0; i < 4; i++) {
            if (D_800C9520_main[i] & START_BUTTON) {
                func_800DC3AC_name_81(curPlayerNo);
                MBDCameraPos2DGet(&sp10);
                MBDCameraPos2DSet(&sp10);
                func_800F3500_name_81(i);
                func_800DC410_name_81(curPlayerNo);
                break;
            }
            if (i < MBD_MAX_PLAYERS && func_800F37B8_name_81(i) == 0) {
                playerPadNo = GwPlayer[i].pad;
                if (i == curPlayerNo) {
                    if (D_800D51F8_main != 0 && (D_800C9520_main[playerPadNo] & B_BUTTON)) {
                        func_800DC3AC_name_81(i);
                        D_800CB99C_main = 1;
                        omAllPause();
                        func_800FB524_name_81(i);
                        omAllUPause();
                        D_800CB99C_main = 0;
                        func_800DC410_name_81(i);
                        break;
                    }
                    if (mbCameraBtnF != 0 && (D_800C9520_main[playerPadNo] & R_TRIG)) {
                        func_800DC3AC_name_81(curPlayerNo);
                        func_80100CEC_name_81(playerPadNo);
                        func_800DC410_name_81(curPlayerNo);
                        break;
                    }
                }
            }
        }
    }
}

void func_800FF640_name_81(u32 arg0) {
    GW_PLAYER *player;
    s32 i;

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        s16 masuID;
        player = MBDGetPlayerStruct(i);
        masuID = MBDMasuLinkMasuIdGet(player->clink, player->cidx);
        func_800EB6C4_name_81(i, masuID);
        func_800ED214_name_81(i);
    }

    func_800E5954_name_81();
    func_800E856C_name_81(1.0f);
    MBDCameraSpeedSet(-1.0f);
    D_800CD280_main = 1;
    switch (arg0) {
        case 0:
            switch (mbGameMode) {
                case 0:
                case 1:
                    WipeCreateIn(WIPE_TYPE_NORMAL, 0);
                    func_800F40E4_name_81();
                    break;
                default:
                    if (D_800A12C8_main != -1) {
                        if (D_800A12C8_main == 0) {
                            WipeColorSet(255, 255, 255);
                        } else {
                            WipeColorSet(0, 0, 0);
                        }
                        WipeCreateIn(D_800A12C8_main, 0x10);
                        D_800A12C8_main = -1;
                        func_800FFAE0_name_81(0, 0);
                        func_800FFAE0_name_81(1, 0);
                    } else {
                        WipeCreateIn(WIPE_TYPE_PREV, 0x10);
                    }
                    MBDCameraZoomSet(D_800C9938_main);
                    func_800F4080_name_81();
                    break;
            }
            MBDCameraPos3DSet(&GwPlayer[GwSystem.current_player_index].player_obj->coords);
            omAddPrcObj(func_800FD6F4_name_81, 0xEFFF, 0x4000, 0);
            omAddPrcObj(func_800FCAB4_name_81, 0x1005, 0, 0);
            omPrcSetStatBit(omAddPrcObj(func_800FF480_name_81, 0x1001, 0, 0), OM_STAT_NOALLPAUSE);
            mbCameraBtnF = 0;
            mbItemBtnF = 0;
            D_800D51F8_main = 0;
            omAddPrcObj(func_800FC8E8_name_81, 0x1005, 0, 0);
            func_800FC888_name_81(1);
            if (func_800037C4_main(D_800CDBC8_main) < 0x7F) {
                func_800DC7CC_name_81();
                return;
            }
            return;
        case 1:
            MBDCameraPos3DSet(&GwPlayer[GwSystem.current_player_index].player_obj->coords);
            omAddPrcObj(func_800FCAB4_name_81, 0x1005, 0, 0);
            omPrcSetStatBit(omAddPrcObj(func_800FF420_name_81, 0x1005, 0, 0), OM_STAT_NOALLPAUSE);
            mbCameraBtnF = 1;
            return;
        case 2:
            func_800F73C0_name_81();
            func_800FC888_name_81(0);
            break;
    }
}

void func_800FF944_name_81(s16 arg0) {
    D_800CD2A0_main.unk_02 = 1;
    D_80105494_name_81 = 0x40;
    D_800D1380_main = arg0;
    D_80105496_name_81 = 0;
}

void func_800FF970_name_81(s32 arg0) {
    D_800A12C8_main = arg0;
}

void func_800FF97C_name_81(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    D_80105498_name_81 = arg0;
    D_8010549C_name_81 = arg1;
    D_80105494_name_81 = 8;
    D_800D1380_main = arg2;
    D_80105496_name_81 = arg3;
}

void func_800FF9AC_name_81(s32 arg0, s16 arg1, s16 arg2) {
    func_800FF97C_name_81(arg0, arg1, arg2, 0);
}

void func_800FF9D8_name_81(void) {
    D_800D530C_main = 1;
}

void func_800FF9E8_name_81(s16 arg0, s16 arg1) {
    D_80105494_name_81 = 0x10;
    D_800D1380_main = arg0;
    D_80105496_name_81 = arg1;
    func_800FC108_name_81();
}

s16 func_800FFA1C_name_81(void) {
    return D_80105494_name_81;
}

void func_800FFA28_name_81(Vec *arg0) {
    f32 temp_f20;
    f32 temp_f22;
    Vec *var_s0;

    var_s0 = arg0;
    func_800E5C20_name_81();
    func_800E5BE8_name_81();
    temp_f22 = MBDCameraSpeedGet();
    MBDCameraSpeedSet(-1.0f);
    temp_f20 = func_800E8578_name_81();
    func_800E856C_name_81(1.0f);
    func_800E5954_name_81();
    if (var_s0 == NULL) {
        var_s0 = &MBDGetPlayerStruct(CUR_PLAYER)->player_obj->coords;
    }
    MBDCameraPos3DSet(var_s0);
    HuPrcVSleep();
    func_800E856C_name_81(temp_f20);
    MBDCameraSpeedSet(temp_f22);
}
