#include "common_board.h"
#include "game/aura.h"
#include "game/hu3d.h"
#include "game/input.h"
#include "game/pause.h"
#include "game/malloc.h"
#include "game/wipe.h"
#include "game/overlays/party/common/move.h"
#include "game/overlays/party/common/scissor.h"
#include "game/overlays/party/common/brancharrow.h"
#include "game/overlays/party/common/branch.h"
#include "game/overlays/party/common/vec.h"
#include "game/overlays/party/common/model.h"
#include "game/overlays/party/common/sai.h"
#include "game/overlays/party/common/pause.h"
#include "game/overlays/party/common/main.h"
#include "game/overlays/party/common/back.h"
#include "game/overlays/party/common/player.h"
#include "game/overlays/party/common/sprgrp.h"
#include "game/overlays/party/common/status.h"
#include "game/overlays/party/common/coinchange.h"
#include "game/overlays/party/common/helpwin.h"
#include "game/overlays/party/common/item.h"
#include "game/overlays/party/common/mgcall.h"

// Sets the shared process state and sleeps until another process changes it.
#define SET_STATE_AND_WAIT(state, value) \
    do {                                 \
        s32 _value = (value);            \
        *(state) = _value;               \
        while (*(state) == _value) {     \
            HuPrcVSleep();               \
        }                                \
    } while (0)

typedef struct {
    /* 0x00 */ s16 spriteGroup;
    /* 0x02 */ s16 sprites[3];
} W10SprGroup; // sizeof 0x08

typedef struct {
    /* 0x00 */ s32 player;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 slot;
    /* 0x0C */ s32 unkC;
} W10RunnerData; // sizeof 0x10

void MB10Ev_Branch1(void);

s16 mb10_playerChrTbl[] = { 4, 0, 1, 2 };

s32 mb10ev_guideFaceTbl[] = { 0xA007E, 0xA007F, 0xA0080, 0xA0081, 0xA0082, 0xA0083 };

s32 mb10ev_guideFaceEndTbl[] = { 0xA0084, 0xA0085 };

Vec mb10_bankCoinOfsTbl[] = {
    { -3.0f, 0.0f, -2.0f },
    { 0.0f, 2.0f, 2.0f },
    { 1.0f, 5.5f, -3.0f },
    { 3.5f, 8.0f, 4.0f },
    { -1.0f, 12.0f, 11.0f }
};

Vec mb10_bankCoinRotTbl[] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { -15.0f, 0.0f, 0.0f },
    { 20.0f, 0.0f, -30.0f },
    { 45.0f, 0.0f, 45.0f }
};

s16 mb10ev_branch1Masu[] = { 31, 24, -1, 0 };

s16 mb10ev_branch1ComArrowTbl[] = { 1, 0, 0, 0 };

event_list_entry mb10_branch1EventTbl[] = {
    { 1, 2, MB10Ev_Branch1 },
    { 0, 0, NULL }
};

event_table_entry mb10_specialEventTbl[] = {
    { 39, mb10_branch1EventTbl },
    { -1, NULL }
};

s32 mb10ev_captionSprTbl[] = {
    0x13000A, 0x13000B, 0x13000C, 0x13000D, 0x13000E, 0x13000F, 0x130010, 0x130011,
    0x130012, 0x130013
};

s32 mb10ev_iconSprTbl[] = { 0x130115, 0x130012, 0x130011 };

u32 mb10ev_unusedMot[] = { 1, 0xA005E }; /* Unreferenced. */

s16 mb10ev_guideMotNo = -1;

u32 mb10ev_shopKinopioMot[] = { 1, 0xA0017 };

u32 mb10ev_shopKoopaJrMot[] = { 1, 0xA00F0 };

u32 mb10ev_bankCoinPileMot[] = { 1, 0xA009D };

s32 mb10ev_shopKoopaJrF = 0;

f32 mb10ev_cartJumpOfsTbl[][2] = {
    { 0.0f, 0.0f },
    { -10.0f, 0.0f },
    { 10.0f, 0.0f },
    { 0.0f, -10.0f }
};

s32 mb10_pauseOffF BSS;
Object *mb10_starGuideMdl BSS;
Process *mb10_starGuideHoverProc BSS;
Object *mb10_teresaGuideMdl BSS;
Object *mb10_bankCoinBaseMdl BSS;
u8 mb10_bankCoinBaseMdlPad[4] BSS; /* Unreferenced. */
Object *mb10_bankCoinMdl[5] BSS;
s16 mb10ev_iconGrp BSS;
s16 mb10ev_iconSpr BSS;
s16 mb10ev_iconFrameGrp BSS;
s16 mb10ev_iconFrameSpr BSS;
s16 mb10_cameraMasu BSS;
Vec mb10_cameraPos BSS;
UnkMBGuideData *mb10ev_guide BSS;
Object *mb10ev_itemMasuNpcMdl BSS;
Object *mb10ev_itemMasuCloudMdl BSS;
Object *mb10ev_battleKuriboMdl BSS;
Object *mb10ev_battleKuriboUpperMdl BSS;
Process *mb10ev_actionTimeSprProc BSS;
u8 mb10ev_actionTimeSprProcPad[4] BSS; /* Unreferenced. */
s32 mb10ev_cartJumpStateTbl[4] BSS;
Object *mb10_cartMdl BSS;
s32 mb10_cartMoveF BSS;

void MB10Ev_TutorialProc(void);
void MB10Ev_KakusiExec(UnkMBGuideData *guide);

void MB10_BoardInit(void) {
    GwSystem.current_board_index = 6;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(boardcall, 0, 0x192);
}

void MB10_SaveInit(void) {
    s32 i;

    omInitObjMan(0xA, 0);
    MBMoveMasuSet(0, 0, 0);
    MBMoveMasuSet(1, 0, 0);
    MBMoveMasuSet(2, 0, 0);
    MBMoveMasuSet(3, 0, 0);
    for (i = 0; i < 4; i++) {
        MBPlayerGet(i)->chr = mb10_playerChrTbl[i];
    }
    omOvlReturnEx(1);
}

void MB10_StarGuideCreate(void) {
    Object *obj;

    if (mb10_starGuideMdl != NULL) {
        return;
    }
    obj = MBModelCreate(0x3A, NULL);
    AuraCreate(obj->omObj1->model[0]);
    MBModelTempAllocFree(obj);
    mb10_starGuideMdl = obj;
    obj->flags |= 2;
    HuVecCopyXYZ(&obj->scale, 0.6f, 0.6f, 0.6f);
    obj->velocity.x = 10.0f;
    mb10_starGuideHoverProc = MBModelHoverCreate(obj, 6.0f, 2.0f);
    HuVecCopy3F(&obj->coords, &MBMasuGet(0x25)->coords);
}

void MB10_StarGuideCreateAll(void) {
    mb10_starGuideMdl = NULL;
    MB10_StarGuideCreate();
}

void MB10_TeresaGuideCreate(void) {
    Object *obj;

    if (mb10_teresaGuideMdl != NULL) {
        return;
    }
    obj = MBModelCreate(0xA, NULL);
    Hu3DModelTPLvlInit(obj->omObj1->model[0]);
    Hu3DModelTPLvlInit(obj->omObj2->model[0]);
    mb10_teresaGuideMdl = obj;
    obj->flags |= 2;
    obj->velocity.x = 15.0f;
    HuVecCopy3F(&obj->coords, &MBMasuGet(0x24)->coords);
    MBModelDispOff(obj);
}

void MB10_TeresaGuideCreateAll(void) {
    mb10_teresaGuideMdl = NULL;
    MB10_TeresaGuideCreate();
}

void MB10_BankCoinCreate(s16 arg0) {
    Object *obj;

    if (mb10_bankCoinMdl[arg0] != NULL) {
        return;
    }
    if (mb10_bankCoinBaseMdl == NULL) {
        obj = MBModelCreate(0x1E, NULL);
        MBModelTempAllocFree(obj);
        mb10_bankCoinBaseMdl = obj;
    } else {
        obj = MBModelLinkCreate(mb10_bankCoinBaseMdl);
    }
    mb10_bankCoinMdl[arg0] = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBMasuGet(0x2F)->coords);
    HuVecAdd(&obj->coords, &mb10_bankCoinOfsTbl[arg0], &obj->coords);
    obj->omObj1->rot.x = mb10_bankCoinRotTbl[arg0].x;
    obj->omObj1->rot.z = mb10_bankCoinRotTbl[arg0].z;
}

void MB10_BankCoinCreateAll(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        mb10_bankCoinMdl[i] = NULL;
        MB10_BankCoinCreate(i);
    }
}

void MB10_BranchHelpStart(void) {
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    HuPrcSleep(3);
}

void MB10_BranchHelpEnd(void) {
}

void MB10Ev_Branch1(void) {
    UnkEA790Struct *win;
    s32 count;
    s32 sel;
    s32 i;

    MBPlayerMotionSet(-1, -1, 2);
    MB10_BranchHelpStart();
    win = MBBranchArrowLinkCreate(-1, mb10ev_branch1Masu);
    MBBranchSelStart(win, -1, 0);
    if (MBPlayerComCheck(-1)) {
        count = mb10ev_branch1ComArrowTbl[GwSystem.boardData.halfWordBytes[0]++];
        for (i = 0; i < count; i++) {
            MBBranchSelMesSend(win, -2);
        }
        MBBranchSelMesSend(win, -4);
    }
    sel = MBBranchSelWait(win);
    MBBranchArrowGrpKill(win);
    MB10_BranchHelpEnd();
    if (sel == 0) {
        MBMoveNextMasuSet(-1, 1, 0);
    } else {
        MBMoveNextMasuSet(-1, 2, 0);
    }
    omDelPrcObj(NULL);
}

void MB10Ev_ComSetAll(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        MBPlayerGet(i)->stat |= PLAYER_IS_CPU;
    }
}

void MB10Ev_ScissorWipeOut(void) {
    HuPrcChildLink(HuPrcCurrentGet(), MBScissorWipeOutStart());
    HuPrcChildWatch();
}

void MB10Ev_ScissorWipeIn(void) {
    HuPrcChildLink(HuPrcCurrentGet(), MBScissorWipeInStart());
    HuPrcChildWatch();
}

W10SprGroup *MB10Ev_CaptionCreate(s16 arg0, s16 x, s16 y) {
    W10SprGroup *group;
    void *data;

    group = HuMemMemoryAllocTemp(sizeof(W10SprGroup));
    group->spriteGroup = HuSprGrpCreate(3, 0);

    data = DataRead(0x130000);
    group->sprites[0] = HuSprAnimRead(data);
    HuSprGrpMemberSet(group->spriteGroup, 0, group->sprites[0], 0);
    HuSprPriSet(group->spriteGroup, 0, 0xB);
    HuSprAttrSet(group->spriteGroup, 0, HUSPR_ATTR_XLU);
    HuSprPosSet(group->spriteGroup, 0, x + 5, y);
    DataClose(data);

    data = DataRead(0x130001);
    group->sprites[1] = HuSprAnimRead(data);
    HuSprGrpMemberSet(group->spriteGroup, 1, group->sprites[1], 0);
    HuSprPriSet(group->spriteGroup, 1, 0xC);
    HuSprAttrSet(group->spriteGroup, 1, HUSPR_ATTR_XLU);
    HuSprPosSet(group->spriteGroup, 1, x + 5, y);
    HuSprTPLvlSet(group->spriteGroup, 1, 0xFF);
    HuSprColorSet(group->spriteGroup, 1, 0x1F, 0xB0, 0x3F);
    DataClose(data);

    data = DataRead(mb10ev_captionSprTbl[arg0]);
    group->sprites[2] = HuSprAnimRead(data);
    HuSprGrpMemberSet(group->spriteGroup, 2, group->sprites[2], 0);
    HuSprPriSet(group->spriteGroup, 2, 0xA);
    HuSprAttrSet(group->spriteGroup, 2, HUSPR_ATTR_XLU);
    HuSprPosSet(group->spriteGroup, 2, x, y);
    DataClose(data);

    return group;
}

void MB10Ev_CaptionKill(W10SprGroup *arg0) {
    HuSprAnimKill(arg0->sprites[0]);
    HuSprAnimKill(arg0->sprites[1]);
    HuSprAnimKill(arg0->sprites[2]);
    HuSprGrpKill(arg0->spriteGroup);
    HuMemMemoryFreeTemp(arg0);
}

void MB10Ev_IconCreate(s16 arg0, s16 x, s16 y) {
    void *data;

    mb10ev_iconGrp = HuSprGrpCreate(1, 0);
    data = DataRead(mb10ev_iconSprTbl[arg0]);
    mb10ev_iconSpr = HuSprAnimRead(data);
    HuSprGrpMemberSet(mb10ev_iconGrp, 0, mb10ev_iconSpr, 0);
    HuSprPriSet(mb10ev_iconGrp, 0, 0xB);
    HuSprAttrSet(mb10ev_iconGrp, 0, HUSPR_ATTR_XLU);
    HuSprPosSet(mb10ev_iconGrp, 0, x, y);
    DataClose(data);
}

void MB10Ev_IconFrameCreate(s16 x, s16 y) {
    void *data;
    f32 scale;

    mb10ev_iconFrameGrp = HuSprGrpCreate(1, 0);
    data = DataRead(0x130015);
    mb10ev_iconFrameSpr = HuSprAnimRead(data);
    HuSprGrpMemberSet(mb10ev_iconFrameGrp, 0, mb10ev_iconFrameSpr, 0);
    HuSprPriSet(mb10ev_iconFrameGrp, 0, 0xC);
    HuSprAttrSet(mb10ev_iconFrameGrp, 0, HUSPR_ATTR_XLU);
    HuSprColorSet(mb10ev_iconFrameGrp, 0, 0, 0xFF, 0);
    HuSprPosSet(mb10ev_iconFrameGrp, 0, x, y);
    HuSprScaleSet(mb10ev_iconFrameGrp, 0, 1.0f, 0.0f);
    DataClose(data);
    for (scale = 0.0f; scale < 1.0f; scale += 1.0f / 6.0f) {
        HuSprScaleSet(mb10ev_iconFrameGrp, 0, 1.0f, scale);
        HuPrcVSleep();
    }
    HuSprScaleSet(mb10ev_iconFrameGrp, 0, 1.0f, 1.0f);
}

void MB10Ev_IconKill(void) {
    HuSprAnimKill(mb10ev_iconSpr);
    HuSprGrpKill(mb10ev_iconGrp);
}

void MB10Ev_IconFrameKill(void) {
    f32 scale;

    for (scale = 1.0f; scale > 0.0f; scale -= 1.0f / 6.0f) {
        HuSprScaleSet(mb10ev_iconFrameGrp, 0, 1.0f, scale);
        HuPrcVSleep();
    }
    HuSprScaleSet(mb10ev_iconFrameGrp, 0, 1.0f, 0.0f);
    HuSprAnimKill(mb10ev_iconFrameSpr);
    HuSprGrpKill(mb10ev_iconFrameGrp);
}

void MB10_CameraProc(void) {
    mb10_cameraMasu = -1;
    MBPlayerPosFixSet(0, 1);
    MBPlayerPosFixSet(1, 1);
    MBPlayerPosFixSet(2, 1);
    MBPlayerPosFixSet(3, 1);
    WipeCreateIn(WIPE_STARS, 0x10);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    MBBackThreadPriLowSet();
    while (TRUE) {
        if (mb10_cameraMasu < 0) {
            if (mb10_cameraMasu == -2) {
                MBCameraPos3DSet(&mb10_cameraPos);
            } else {
                MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
            }
        } else {
            MBCameraPos3DSet(&MBMasuGet(mb10_cameraMasu)->coords);
        }
        HuPrcVSleep();
    }
}

void MB10_CameraMasuSet(s16 arg0) {
    mb10_cameraMasu = arg0;
    MBCameraSpeedSet(4.0f);
}

void MB10_CameraStopWait(void) {
    HuPrcSleep(3);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    MBCameraSpeedSet(-1.0f);
}

void MB10Ev_PlayerColorReset(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        GW_PLAYER *player = MBPlayerGet(i);
        player->color = 0;
        player->stat &= ~2;
    }
}

void MB10Ev_StatusColorUpdate(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        MBStatusColorSet(i, MBPlayerGet(i)->color);
    }
}

void MB10Ev_TurnNext(void) {
    GW_PLAYER *player;
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    if (++system->current_player_index >= 4) {
        system->current_player_index = 0;
    }
    for (i = 0; i < 4; i++) {
        player = MBPlayerGet(i);
        MBPlayerForwardSet(i);
        MBMotionSet(player->player_obj, -1, 2);
        MBPlayerPosFixSet(i, 1);
    }
    MBCameraZoomSet(1.0f);
}

void MB10Ev_CameraRefresh(Vec *arg0) {
    MBCameraRefresh(arg0);
}

void MB10Ev_TelopExec(void) {
    HuPrcChildLink(HuPrcCurrentGet(), MBTelopCreate(GwSystem.current_player_index));
    HuPrcChildWatch();
}

void MB10Ev_SaiExec(s16 arg0) {
    Process *process;
    Process *child;
    GW_SYSTEM *system = &GwSystem;

    MBSaiValueForceSet(system->current_player_index, arg0);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process, MBCameraZoomMotStart(1.3f));
    child = MBSaiPlayerCreate(system->current_player_index);
    HuPrcChildWatch();
    HuPrcChildLink(process, child);
    HuPrcChildWatch();
}

void MB10Ev_PlayerWalkExec(void) {
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);
    SpaceData *space;
    Vec dir;
    s16 walkNum;
    s16 masuId = 0;
    s16 clink;
    s16 cidx;
    s32 i;

    walkNum = MBSaiValueGet(system->current_player_index);
    MBPlayerMotionSet(-1, 0, 2);
    while (walkNum != 0) {
        clink = player->clink;
        cidx = player->cidx;
        player->clink = player->nlink;
        player->cidx = player->nidx;
        for (i = 0; i < 4; i++) {
            MBPlayerPosFixSet(i, 10);
        }
        player->clink = clink;
        player->cidx = cidx;

        space = GET_SPACE_FROM_LINK(player->nlink, player->nidx);
        if ((space->unk_02 & 0x8000) || MBPlayerJumpCheck(system->current_player_index)) {
            PlayerFXPlay(0x3A, system->current_player_index);
            MBPlayerMotionSet(-1, 2, 0);
            player->player_obj->velocity.y = 4.0f;
            player->player_obj->velocity.z = -0.5f;
            switch (system->walk_speed) {
                case 0:
                    player->player_obj->velocity.y = 8.0f;
                    player->player_obj->velocity.z = -2.0f;
                    MBPlayerPosMoveSet(system->current_player_index, 7);
                    break;
                case 1:
                    player->player_obj->velocity.y = 4.0f;
                    player->player_obj->velocity.z = -0.5f;
                    MBPlayerPosMoveSet(system->current_player_index, 15);
                    break;
                case 2:
                    player->player_obj->velocity.y = 2.0f;
                    player->player_obj->velocity.z = -0.125f;
                    MBPlayerPosMoveSet(system->current_player_index, 30);
                    break;
            }
        } else {
            if (player->player_obj->unk46 != 0) {
                MBPlayerMotionSet(-1, 0, 2);
            }
            switch (system->walk_speed) {
                case 0:
                    Hu3DMotionSpeedSet(player->player_obj->omObj1->model[0], 2.0f);
                    MBPlayerPosMoveSet(system->current_player_index, 5);
                    break;
                case 1:
                    Hu3DMotionSpeedSet(player->player_obj->omObj1->model[0], 1.0f);
                    MBPlayerPosMoveSet(system->current_player_index, 10);
                    break;
                case 2:
                    Hu3DMotionSpeedSet(player->player_obj->omObj1->model[0], 0.75f);
                    MBPlayerPosMoveSet(system->current_player_index, 15);
                    break;
            }
            Hu3DMotionSpeedSet(player->player_obj->omObj1->model[0], 1.0f);
        }

        player->clink = player->nlink;
        player->cidx = player->nidx;
        player->nidx++;
        masuId = MBMasuLinkMasuIdGet(player->clink, player->cidx);
        space = MBMasuGet(masuId);
        MBMasuCurSet(masuId);

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
                walkNum--;
                MBMasuBounceCreate(masuId);
                break;
        }

        if (walkNum != 0) {
            switch (space->space_type) {
                case SPACE_STAR:
                    HuAudFXPlay(0x123);
                    break;
                case SPACE_BLUE:
                case SPACE_RED:
                case SPACE_HAPPENING:
                case SPACE_CHANCE_TIME:
                case SPACE_ITEM:
                case SPACE_BANK:
                case SPACE_BATTLE:
                case SPACE_BOWSER:
                case SPACE_GAME_GUY:
                    HuAudFXPlay(0x101);
                    break;
            }
        } else {
            switch (space->space_type) {
                case SPACE_HAPPENING:
                case SPACE_ITEM:
                    HuAudFXPlay(0x108);
                    break;
                case SPACE_BLUE:
                    HuAudFXPlay(0x121);
                    break;
                case SPACE_RED:
                    HuAudFXPlay(0x122);
                    break;
                case SPACE_BOWSER:
                    HuAudFXPlay(0x124);
                    break;
                case SPACE_CHANCE_TIME:
                    HuAudFXPlay(0x12F);
                    break;
                case SPACE_BATTLE:
                case SPACE_GAME_GUY:
                    HuAudFXPlay(0x12E);
                    break;
                case SPACE_BANK:
                    HuAudFXPlay(0x130);
                    break;
                case SPACE_STAR:
                    HuAudFXPlay(0x123);
                    break;
            }
        }
        MBMasuEventCall(masuId, 1);
    }
    MBPlayerMotionSet(-1, -1, 2);
    MBMasuEventCall(masuId, 3);
    MBVecForwardSet(&dir);
    MBVecRotLerpSpinCreate(&player->player_obj->rot, &dir, &player->player_obj->rot, 8);
    MBStatusPulseStop(system->current_player_index);
}

void MB10Ev_MasuCoinExec(void) {
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);
    SpaceData *space = GET_SPACE_FROM_LINK(player->clink, player->cidx);

    MBPlayerMasuColorSet(-1, space->space_type);
    MBStatusColorSet(system->current_player_index, player->color);
    switch (space->space_type) {
        case SPACE_BLUE:
            MBCoinChangeCreate(system->current_player_index, 3);
            MBCoinTakeCreate(system->current_player_index, 3);
            HuPrcSleep(30);
            break;
        case SPACE_RED:
            MBCoinChangeCreate(system->current_player_index, -3);
            MBCoinTakeCreate(system->current_player_index, -3);
            HuPrcSleep(30);
            break;
    }
}

void MB10Ev_GuideWinExec(UnkMBGuideData *guide, u32 mess) {
    HuWinMesSet(guide->amount, mess, -1, -1);
    HuWinExOpen(guide->amount, 1);
    MBWinComKeyAnyWait(guide->amount);
    HuWinExClose(guide->amount, 1);
    HuWinHomeClear(guide->amount);
    HuPrcVSleep();
}

void MB10Ev_GuideWinOpen(UnkMBGuideData *guide, u32 mess) {
    HuWinMesSet(guide->amount, mess, -1, -1);
    HuWinExOpen(guide->amount, 1);
}

void MB10Ev_GuideWinOpenWait(UnkMBGuideData *guide, u32 mess) {
    HuWinMesSet(guide->amount, mess, -1, -1);
    HuWinExOpen(guide->amount, 1);
    while (HuWinStatGet(guide->amount) != 0) {
        HuPrcVSleep();
    }
}

void MB10Ev_GuideWinClose(UnkMBGuideData *guide) {
    MBWinComKeyAnyWait(guide->amount);
    HuWinExClose(guide->amount, 1);
    HuWinHomeClear(guide->amount);
    HuPrcVSleep();
}

void MB10Ev_GuideWinAutoExec(UnkMBGuideData *guide, u32 mess) {
    HuWinActivePlayerSet(guide->amount, 15);
    HuWinComKeySet(HUWIN_COMKEY_PAD, HUWIN_COMKEY_PAD, HUWIN_COMKEY_PAD, HUWIN_COMKEY_PAD);
    HuWinMesSet(guide->amount, mess, -1, -1);
    while (HuWinStatGet(guide->amount) != 0) {
        HuPrcVSleep();
    }
    HuWinComKeyReset();
}

void MB10Ev_GuideJump(UnkMBGuideData *guide) {
    Object *obj = guide->obj;

    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.6f;
    MBMotionSet(guide->obj, 0, 0);
    HuPrcSleep(3);
    while (MBMotionCheck(guide->obj) == 0) {
        HuPrcVSleep();
    }
    MBMotionSet(guide->obj, -1, 2);
}

void MB10Ev_GuideMove(UnkMBGuideData *guide, s16 pos) {
    s32 i;
    s16 step;
    s16 curPos = guide->spriteGroup;
    Object *obj = guide->obj;

    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.5f;
    step = (pos - curPos) / 14;
    for (i = 0; i < 14; i++) {
        curPos = guide->spriteGroup;
        MBGuidePosSet(guide, curPos + step, 0);
        HuPrcVSleep();
    }
    MBGuidePosSet(guide, pos, 0);
}

void MB10Ev_GuideMotProc(void) {
    UnkMBGuideData *guide = HuPrcCurrentGet()->user_data;
    s16 motion;

    while (TRUE) {
        HuPrcVSleep();
        if (mb10ev_guideMotNo == -1) {
            continue;
        }
        if (mb10ev_guideMotNo == -2) {
            mb10ev_guideMotNo = -1;
            MBMotionShiftSet(guide->obj, -1, 0, 10, 0);
        } else {
            MBMotionShiftSet(guide->obj, mb10ev_guideMotNo, 0, 10, 0);
        }
        motion = mb10ev_guideMotNo;
        mb10ev_guideMotNo = -1;
        while (MBMotionCheck(guide->obj) == 0 && mb10ev_guideMotNo == -1) {
            HuPrcVSleep();
        }
        switch (motion) {
            case 1:
                MBMotionSet(guide->obj, 3, 2);
                break;
            case 2:
                MBMotionSet(guide->obj, 4, 2);
                break;
            default:
                MBMotionSet(guide->obj, -1, 2);
                break;
        }
    }
}

void MB10Ev_GuideMotSet(s16 arg0) {
    mb10ev_guideMotNo = arg0;
}

void MB10Ev_ItemMasuFloatObjMain(omObjData *obj) {
    mb10ev_itemMasuNpcMdl->coords.y = -sindf(obj->rot.x) * 3.0f;
    mb10ev_itemMasuCloudMdl->coords.y = -sindf(obj->rot.x) * 3.0f;
    obj->rot.x += 3.0f;
}

void MB10Ev_BattleKuriboObjMain(omObjData *obj) {
    mb10ev_battleKuriboMdl->coords.y = sindf(obj->rot.x) * 3.0f;
    mb10ev_battleKuriboUpperMdl->coords.y = sindf(obj->rot.x) * 3.0f;
    obj->rot.x += 10.0f;
}

void MB10Ev_ItemMasuKinopioProc(void) {
    s32 *state = HuPrcCurrentGet()->user_data;
    GW_PLAYER *player = MBPlayerGet(-1);
    omObjData *bobObj;
    s32 effect;

    mb10ev_itemMasuNpcMdl = MBModelCreate(9, NULL);
    mb10ev_itemMasuCloudMdl = MBModelFileCreate(0x1301C8, -1, 1.0f, 0.0f, NULL);
    effect = EffectCreate(0xB0004, 0xAA9);
    HuAudFXPlay(0x119);
    Hu3DModelCameraSet(effect, HU3D_CAM0);
    EffectParamSet(effect, 1.0f, 20.0f, 1.0f);
    EffectRangeSet(effect, 15.0f);
    MBModelTempAllocFree(mb10ev_itemMasuNpcMdl);
    mb10ev_itemMasuNpcMdl->flags |= 1;
    MBModelTempAllocFree(mb10ev_itemMasuCloudMdl);
    HuVecCopy3F(&mb10ev_itemMasuNpcMdl->coords, &player->player_obj->coords);
    HuVecCopy3F(&mb10ev_itemMasuCloudMdl->coords, &player->player_obj->coords);
    mb10ev_itemMasuNpcMdl->velocity.x = 120.0f;
    mb10ev_itemMasuCloudMdl->velocity.x = 120.0f;
    while (mb10ev_itemMasuNpcMdl->velocity.x > 50.0f) {
        EffectPosSet(effect, mb10ev_itemMasuNpcMdl->coords.x, mb10ev_itemMasuNpcMdl->velocity.x - 10.0f,
                           mb10ev_itemMasuNpcMdl->coords.z);
        HuPrcVSleep();
        mb10ev_itemMasuNpcMdl->velocity.x -= 4.0f;
        mb10ev_itemMasuCloudMdl->velocity.x -= 4.0f;
    }
    bobObj = omAddObj(500, 0, 0, -1, MB10Ev_ItemMasuFloatObjMain);
    bobObj->rot.x = 180.0f;
    SET_STATE_AND_WAIT(state, 1);
    while (mb10ev_itemMasuNpcMdl->velocity.x < 120.0f) {
        EffectPosSet(effect, mb10ev_itemMasuNpcMdl->coords.x, mb10ev_itemMasuNpcMdl->velocity.x - 10.0f,
                           mb10ev_itemMasuNpcMdl->coords.z);
        HuPrcVSleep();
        mb10ev_itemMasuNpcMdl->velocity.x += 4.0f;
        mb10ev_itemMasuCloudMdl->velocity.x += 4.0f;
    }
    *state = 3;
    EffectStop(effect);
    MBModelKill(mb10ev_itemMasuNpcMdl);
    MBModelKill(mb10ev_itemMasuCloudMdl);
    omDelObj(bobObj);
    omDelPrcObj(NULL);
}

void MB10Ev_ItemMasuKoopaJrProc(void) {
    s32 *state = HuPrcCurrentGet()->user_data;
    GW_PLAYER *player = MBPlayerGet(-1);
    omObjData *bobObj;
    s32 effect;

    mb10ev_itemMasuNpcMdl = MBModelCreate(0x39, NULL);
    mb10ev_itemMasuCloudMdl = MBModelFileCreate(0x130203, -1, 1.0f, 0.0f, NULL);
    effect = EffectCreate(0xB0005, 0xAA9);
    HuAudFXPlay(0x11A);
    Hu3DModelCameraSet(effect, HU3D_CAM0);
    EffectParamSet(effect, 1.0f, 20.0f, 1.0f);
    EffectRangeSet(effect, 15.0f);
    MBModelTempAllocFree(mb10ev_itemMasuNpcMdl);
    mb10ev_itemMasuNpcMdl->flags |= 1;
    MBModelTempAllocFree(mb10ev_itemMasuCloudMdl);
    HuVecCopy3F(&mb10ev_itemMasuNpcMdl->coords, &player->player_obj->coords);
    HuVecCopy3F(&mb10ev_itemMasuCloudMdl->coords, &player->player_obj->coords);
    mb10ev_itemMasuNpcMdl->velocity.x = 120.0f;
    mb10ev_itemMasuCloudMdl->velocity.x = 120.0f;
    while (mb10ev_itemMasuNpcMdl->velocity.x > 50.0f) {
        EffectPosSet(effect, mb10ev_itemMasuNpcMdl->coords.x, mb10ev_itemMasuNpcMdl->velocity.x - 10.0f,
                           mb10ev_itemMasuNpcMdl->coords.z);
        HuPrcVSleep();
        mb10ev_itemMasuNpcMdl->velocity.x -= 4.0f;
        mb10ev_itemMasuCloudMdl->velocity.x -= 4.0f;
    }
    bobObj = omAddObj(500, 0, 0, -1, MB10Ev_ItemMasuFloatObjMain);
    bobObj->rot.x = 180.0f;
    SET_STATE_AND_WAIT(state, 1);
    while (mb10ev_itemMasuNpcMdl->velocity.x < 120.0f) {
        EffectPosSet(effect, mb10ev_itemMasuNpcMdl->coords.x, mb10ev_itemMasuNpcMdl->velocity.x - 10.0f,
                           mb10ev_itemMasuNpcMdl->coords.z);
        HuPrcVSleep();
        mb10ev_itemMasuNpcMdl->velocity.x += 4.0f;
        mb10ev_itemMasuCloudMdl->velocity.x += 4.0f;
    }
    *state = 3;
    EffectStop(effect);
    MBModelKill(mb10ev_itemMasuNpcMdl);
    MBModelKill(mb10ev_itemMasuCloudMdl);
    omDelObj(bobObj);
    omDelPrcObj(NULL);
}

void MB10Ev_BattleKuriboProc(void) {
    s32 *state = HuPrcCurrentGet()->user_data;
    GW_PLAYER *player = MBPlayerGet(-1);
    omObjData *bobObj;

    mb10ev_battleKuriboMdl = MBModelCreate(0xC, NULL);
    Hu3DModelScaleSet(mb10ev_battleKuriboMdl->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    Hu3DMotionReset(mb10ev_battleKuriboMdl->omObj1->model[0]);
    mb10ev_battleKuriboMdl->flags |= 1;
    mb10ev_battleKuriboUpperMdl = MBModelCreate(0x1F, NULL);
    Hu3DModelScaleSet(mb10ev_battleKuriboUpperMdl->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&mb10ev_battleKuriboMdl->coords, &player->player_obj->coords);
    HuVecCopy3F(&mb10ev_battleKuriboUpperMdl->coords, &player->player_obj->coords);
    mb10ev_battleKuriboMdl->velocity.x = 120.0f;
    mb10ev_battleKuriboUpperMdl->velocity.x = 122.0f;
    while (mb10ev_battleKuriboMdl->velocity.x > 30.0f) {
        HuPrcVSleep();
        mb10ev_battleKuriboMdl->velocity.x -= 2.0f;
        mb10ev_battleKuriboUpperMdl->velocity.x -= 2.0f;
    }
    bobObj = omAddObj(500, 0, 0, -1, MB10Ev_BattleKuriboObjMain);
    bobObj->rot.x = 180.0f;
    SET_STATE_AND_WAIT(state, 1);
    while (mb10ev_battleKuriboMdl->velocity.x < 120.0f) {
        HuPrcVSleep();
        mb10ev_battleKuriboMdl->velocity.x += 2.0f;
        mb10ev_battleKuriboUpperMdl->velocity.x += 2.0f;
    }
    *state = 3;
    MBModelKill(mb10ev_battleKuriboMdl);
    MBModelKill(mb10ev_battleKuriboUpperMdl);
    omDelObj(bobObj);
    omDelPrcObj(NULL);
}

void MB10Ev_GambleProc(void) {
    s32 *state = HuPrcCurrentGet()->user_data;
    GW_PLAYER *player = MBPlayerGet(-1);
    Process *process;

    mb10ev_itemMasuNpcMdl = MBModelCreate(0x3E, NULL);
    MBModelTempAllocFree(mb10ev_itemMasuNpcMdl);
    HuVecCopy3F(&mb10ev_itemMasuNpcMdl->coords, &player->player_obj->coords);
    mb10ev_itemMasuNpcMdl->velocity.x = 100.0f;
    do {
        mb10ev_itemMasuNpcMdl->velocity.x -= 2.0f;
        HuPrcVSleep();
    } while (mb10ev_itemMasuNpcMdl->velocity.x >= 30.0f);
    process = MBModelHoverCreate(mb10ev_itemMasuNpcMdl, 5.0f, 2.0f);
    SET_STATE_AND_WAIT(state, 1);
    omDelPrcObj(process);

    while (mb10ev_itemMasuNpcMdl->velocity.x < 100.0f) {
        mb10ev_itemMasuNpcMdl->velocity.x += 2.0f;
        HuPrcVSleep();
    }
    *state = 3;
    MBModelKill(mb10ev_itemMasuNpcMdl);
    omDelPrcObj(NULL);
}

void MB10Ev_ShopProc(void) {
    s32 *state = HuPrcCurrentGet()->user_data;
    s16 chestModel = mb10ev_shopKoopaJrF != 0 ? 0x31 : 0x30;
    Object *chest;
    Object *contents;
    s16 model;
    f32 angle;
    f32 scale;

    HuAudFXPlay(0x114);
    chest = MBModelCreate(chestModel, NULL);
    MBModelTempAllocFree(chest);
    HuVecCopyXYZ(&chest->rot, 0.0f, 0.0f, 1.0f);
    chest->scale.y = 0.0f;
    MBMotionSet(chest, -1, 1);
    MBModelDispFlagSet(chest);
    HuVecCopy3F(&chest->coords, &MBMasuGet(0x2B)->coords);
    if (mb10ev_shopKoopaJrF != 0) {
        contents = MBModelCreate(0x39, mb10ev_shopKoopaJrMot);
    } else {
        contents = MBModelCreate(0x1B, mb10ev_shopKinopioMot);
    }
    MBModelTempAllocFree(contents);
    HuVecCopy3F(&contents->rot, &chest->rot);
    HuVecCopy3F(&contents->coords, &chest->coords);
    contents->scale.y = contents->scale.x = contents->scale.z = 1.2f;
    MBModelDispOff(contents);

    scale = 1.0f / sindf(50.0f);
    for (angle = 0.0f; angle < 90.0f; angle += 11.25f) {
        chest->scale.y = sindf(angle) * scale;
        chest->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
        chest->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
        HuPrcVSleep();
    }
    for (; angle > 50.0f; angle -= 11.25f) {
        chest->scale.y = sindf(angle) * scale;
        chest->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
        chest->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
        HuPrcVSleep();
    }
    chest->scale.y = chest->scale.x = chest->scale.z = 1.0f;

    MBModelDispFlagSet(contents);
    MBMotionSet(chest, -1, 0);
    Hu3DMotionSpeedSet(chest->omObj1->model[0], 1.2f);
    while (MBMotionCheck(chest) == 0) {
        HuPrcVSleep();
    }
    MBMotionSet(contents, 0, 0);
    HuAudFXPlay(mb10ev_shopKoopaJrF != 0 ? 0x2A0 : 0x298);
    while (MBMotionCheck(contents) == 0) {
        HuPrcVSleep();
    }
    MBMotionSet(contents, -1, 2);
    SET_STATE_AND_WAIT(state, 1);

    HuAudFXPlay(0x115);
    MBMotionSet(chest, -1, 4);
    Hu3DMotionSpeedSet(chest->omObj1->model[0], 1.2f);
    model = chest->omObj1->model[0];
    Hu3DMotionTimeSet(model, Hu3DMotion[Hu3DData[model].motId].unk02);
    while (MBMotionStartCheck(chest) == 0) {
        HuPrcVSleep();
    }
    MBModelDispOff(contents);

    scale = 1.0f / sindf(50.0f);
    for (angle = 50.0f; angle < 90.0f; angle += 11.25f) {
        chest->scale.y = sindf(angle) * scale;
        chest->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
        chest->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
        HuPrcVSleep();
    }
    for (angle = 90.0f; angle > 0.0f; angle -= 11.25f) {
        chest->scale.y = sindf(angle) * scale;
        chest->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
        chest->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
        HuPrcVSleep();
    }
    chest->scale.y = 0.0f;
    chest->scale.x = 0.0f;
    chest->scale.z = 0.0f;
    MBModelKill(chest);
    MBModelKill(contents);
    *state = 3;
    omDelPrcObj(NULL);
}

void MB10Ev_ActionTimeSpr(void) {
    s32 sprites[3][4]; // [0] = rank anims, [1] = character anims, [2] = sprite groups
    s32 titleAnim;
    s32 boxAnim;
    s32 group;
    Process *process;
    s32 box;
    Unk3 *help;
    void *data;
    s32 i;
    s32 j;
    s32 count;
    s32 flag;
    s32 fading;
    s32 alpha;
    f32 angle;
    f32 step;

    process = HuPrcCurrentGet();
    data = DataRead(0x1300F7);
    titleAnim = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300F8);
    sprites[0][0] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300FB);
    sprites[0][1] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300F9);
    sprites[0][2] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300FA);
    sprites[0][3] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300FC);
    boxAnim = HuSprAnimRead(data);
    DataClose(data);
    for (i = 0; i < 4; i++) {
        data = DataRead((GwPlayer[i].chr + 8) | 0x210000);
        sprites[1][i] = HuSprAnimRead(data);
        DataClose(data);
    }

    group = HuSprGrpCreate(1, 5);
    HuSprGrpMemberSet(group, 0, titleAnim, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, HUSPR_ATTR_XLU | HUSPR_ATTR_FILTER_BILERP);
    HuSprPriSet(group, 0, 0x1000);
    HuSprPosSet(group, 0, 0xA0, 0x5A);
    angle = 0.0f;
    step = 30.0f;
    count = 0;
    flag = 0;
    for (;; angle += step) {
        if (angle >= 90.0f && !flag) {
            flag = 1;
            count++;
        }
        if (angle >= 360.0f) {
            flag = 0;
            angle -= 360.0f;
        }
        if (angle >= 180.0f && angle <= 360.0f) {
            HuSprAttrSet(group, 0, HUSPR_ATTR_FLIPY);
        } else {
            HuSprAttrReset(group, 0, HUSPR_ATTR_FLIPY);
        }
        HuSprScaleSet(group, 0, 1.0f, sindf(angle >= 180.0f ? angle - 180.0f : angle));
        if (count >= 2) {
            break;
        }
        HuPrcVSleep();
    }
    HuSprAttrReset(group, 0, HUSPR_ATTR_FLIPY);
    HuSprScaleSet(group, 0, 1.0f, 1.0f);
    help = MBHelpWinCreate(0x14, 0xA0, 1);

    for (i = 0; i < 4; i++) {
        box = sprites[2][i] = HuSprGrpCreate(6, 5);
        HuSprGrpMemberSet(box, 0, boxAnim, 0);
        HuSprAnimModeSet(box, 0, HUSPR_ANIM_MODE_STOP);
        HuSprAttrReset(box, 0, 0xFFFF);
        if (mb10ev_cartJumpStateTbl[i] != 0) {
            HuSprAttrSet(box, 0, HUSPR_ATTR_FILTER_BILERP);
        } else {
            HuSprDispOff(box, 0);
        }
        HuSprPriSet(box, 0, 0x1000);
        HuSprParentSet(box, 0, -1);
        HuSprGrpMemberSet(box, 1, sprites[1][i], 0);
        HuSprAnimModeSet(box, 1, HUSPR_ANIM_MODE_STOP);
        HuSprAttrReset(box, 1, 0xFFFF);
        if (mb10ev_cartJumpStateTbl[i] != 0) {
            HuSprAttrSet(box, 1, HUSPR_ATTR_FILTER_BILERP);
        } else {
            HuSprDispOff(box, 1);
        }
        HuSprPriSet(box, 1, 0x1000);
        HuSprPosSet(box, 1, 0, -9);
        HuSprParentSet(box, 1, 0);
        for (j = 0; j < 4; j++) {
            HuSprGrpMemberSet(box, j + 2, sprites[0][j], 0);
            HuSprAnimModeSet(box, j + 2, HUSPR_ANIM_MODE_BANK);
            HuSprAttrReset(box, j + 2, 0xFFFF);
            if (mb10ev_cartJumpStateTbl[i] == j + 1) {
                HuSprAttrSet(box, j + 2, HUSPR_ATTR_FILTER_BILERP);
            } else {
                HuSprDispOff(box, j + 2);
            }
            HuSprPriSet(box, j + 2, 0x1000);
            HuSprPosSet(box, j + 2, 0, 9);
            HuSprParentSet(box, j + 2, 0);
        }
        HuSprPosSet(box, 0, i * 70 + 55, 200);
    }
    HuPrcSleep(20);

    angle = 90.0f;
    count = 0;
    fading = 0;
    flag = 0;
    alpha = 0xFF;
    for (;; angle += step) {
        if (angle >= 360.0f && !flag) {
            flag = 1;
            count++;
        }
        if (angle >= 360.0f) {
            flag = 0;
            angle -= 360.0f;
        }
        if (!fading && count != 0 && angle >= 90.0f && angle < 180.0f) {
            fading = 1;
        }
        if (fading) {
            alpha -= 21;
            if (alpha <= 0) {
                alpha = 0;
            }
        }
        HuSprTPLvlSet(group, 0, alpha);
        if (count >= 2) {
            break;
        }
        HuPrcVSleep();
    }
    HuSprScaleSet(group, 0, 1.0f, 0.0f);
    HuSprGrpKill(group);
    HuSprAnimKill(titleAnim);
    process->user_data = (void *)1;

    while (TRUE) {
        for (i = 0; i < 4; i++) {
            switch (mb10ev_cartJumpStateTbl[i]) {
                case 0:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOff(sprites[2][i], j);
                    }
                    break;
                case 1:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOn(sprites[2][i], j);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprDispOff(sprites[2][i], j + 2);
                    }
                    HuSprDispOn(sprites[2][i], 2);
                    break;
                case 2:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOn(sprites[2][i], j);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprDispOff(sprites[2][i], j + 2);
                    }
                    HuSprDispOn(sprites[2][i], 3);
                    break;
                case 3:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOn(sprites[2][i], j);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprDispOff(sprites[2][i], j + 2);
                    }
                    HuSprDispOn(sprites[2][i], 4);
                    break;
                case 4:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOn(sprites[2][i], j);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprDispOff(sprites[2][i], j + 2);
                    }
                    HuSprDispOn(sprites[2][i], 5);
                    break;
                default:
                    goto end;
            }
        }
        HuPrcVSleep();
    }
end:
    MBHelpWinKill(help);
    HuSprAnimKill(boxAnim);
    for (i = 0; i < 4; i++) {
        HuSprAnimKill(sprites[0][i]);
        HuSprAnimKill(sprites[1][i]);
        HuSprGrpKill(sprites[2][i]);
    }
    omDelPrcObj(NULL);
}

void MB10_CartProc(void) {
    Object *obj;

    mb10_cartMoveF = 0;
    obj = MBModelCreate(0x4E, NULL);
    mb10_cartMdl = obj;
    MBModelTempAllocFree(obj);
    HuVecCopy3F(&obj->coords, &MBMasuGet(0x2E)->coords);
    HuVecCopyXYZ(&obj->rot, 0.0f, 0.0f, -1.0f);
    obj->velocity.x = 15.0f;
    while (mb10_cartMoveF == 0) {
        HuPrcVSleep();
    }
    while (mb10_cartMoveF != 0) {
        obj->omObj1->rot.z -= 15.0f;
        if (obj->omObj1->rot.z < 0.0f) {
            obj->omObj1->rot.z += 360.0f;
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void MB10Ev_CartJumpProc(void) {
    W10RunnerData *data = HuPrcCurrentGet()->user_data;
    Object *target = mb10_cartMdl;
    GW_PLAYER *player = MBPlayerGet(data->player);
    Object *playerObj = player->player_obj;
    s32 slot = data->slot;
    Process *process = HuPrcCurrentGet();
    SpaceData *start;
    SpaceData *end;
    Vec pos;

    MBPlayerRotMasuStart(data->player, 8, 0x2E);
    while (HuVecDistance(&playerObj->coords, &target->coords) > slot * 20.0f + 30.0f + 20.0f) {
        HuPrcVSleep();
    }
    mb10ev_cartJumpStateTbl[data->player] = 2;
    while (HuVecDistance(&playerObj->coords, &target->coords) > slot * 20.0f + 30.0f) {
        HuPrcVSleep();
    }
    if (data->player == 1) {
        mb10ev_cartJumpStateTbl[1] = 3;
        PlayerFXPlay(0x274, data->player);
        PlayerFXPlay(0x3A, data->player);
        if (data->player == GwSystem.current_player_index) {
            MBPlayerMotionSet(-1, 2, 0);
        } else {
            MBMotionSet(playerObj, 2, 0);
        }
        MBModelJumpSet(playerObj, 7.0f, -0.45f);
        MBModelJumpWait(playerObj);
        PlayerFXPlay(0x31, data->player);
        MBPlayerMotionShiftSet(data->player, -1, 0, 5, 2);
        if (data->player == GwSystem.current_player_index) {
            MBPlayerMotionSet(-1, -1, 2);
        } else {
            MBMotionSet(playerObj, -1, 2);
        }
    } else {
        mb10ev_cartJumpStateTbl[data->player] = 4;
        PlayerFXPlay(0x286, data->player);
        if (data->player == GwSystem.current_player_index) {
            MBPlayerMotionSet(-1, 1, 2);
        } else {
            MBMotionSet(playerObj, 1, 2);
        }
        start = MBMasuGet(0x26);
        end = MBMasuGet(0x10);
        HuVecCopy3F(&pos, &start->coords);
        MBVecDirGet(&playerObj->coords, &pos, &playerObj->rot);
        HuPrcChildLink(process, MBVecSpeedMove2Create(&playerObj->coords, &pos, &playerObj->coords, 2.0f));
        HuPrcChildWatch();
        HuVecCopy3F(&pos, &end->coords);
        pos.x += mb10ev_cartJumpOfsTbl[slot][0];
        pos.z += mb10ev_cartJumpOfsTbl[slot][1];
        MBVecDirGet(&playerObj->coords, &pos, &playerObj->rot);
        HuPrcChildLink(process, MBVecSpeedMoveCreate(&playerObj->coords, &pos, &playerObj->coords, 2.0f));
        HuPrcChildWatch();
        if (data->player == GwSystem.current_player_index) {
            MBPlayerMotionSet(-1, -1, 2);
        } else {
            MBMotionSet(playerObj, -1, 2);
        }
        HuVecCopyXYZ(&pos, 0.0f, 0.0f, 1.0f);
        MBVecRotLerpCreate(&player->player_obj->rot, &pos, &player->player_obj->rot, 5);
        HuPrcSleep(5);
    }
    omDelPrcObj(NULL);
}

void MB10Ev_TutorialProc(void) {
    s32 state;
    Process *process;
    W10SprGroup *spr;
    SpaceData *from;
    SpaceData *to;
    Object *chest;
    Object *contents;
    Object *box;
    Process *runner;
    W10RunnerData *data;
    s16 model;
    s16 sfx;
    s32 i;
    s32 alpha;
    f32 angle;
    f32 scale;

    process = HuPrcCurrentGet();
    GwSystem.boardData.halfWordBytes[0] = 0;
    MB10Ev_ComSetAll();
    mb10ev_guide = MBGuideCreate(NULL, 0);
    HuWinMesPalSet(mb10ev_guide->amount, 4, 0, 0xB0, 0xC0);
    HuVecCopyXYZ(&mb10ev_guide->obj->scale, 1.1f, 1.1f, 1.1f);
    mb10ev_guide->obj->coords.x -= 1.0f;
    mb10ev_guide->obj->coords.y -= 2.0f;
    MBGuideFaceCreate(mb10ev_guide->obj, 2, 0xF, mb10ev_guideFaceTbl[0]);
    MBGuidePosSet(mb10ev_guide, 0x42, 0);
    HuWinAttrSet(mb10ev_guide->amount, 0x40, 0x40);
    MB10Ev_PlayerColorReset();
    MB10Ev_StatusColorUpdate();
    HuPrcSleep(3);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(3);

    MB10Ev_GuideWinExec(mb10ev_guide, 0x1608);
    MB10Ev_TelopExec();
    MB10Ev_GuideWinExec(mb10ev_guide, 0x1609);
    MB10Ev_SaiExec(1);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x160A);
    MB10Ev_PlayerWalkExec();
    HuPrcVSleep();
    MB10Ev_GuideWinExec(mb10ev_guide, 0x160B);
    spr = MB10Ev_CaptionCreate(0, 100, 90);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x160C);
    MB10Ev_CaptionKill(spr);
    MB10Ev_MasuCoinExec();

    MB10Ev_ScissorWipeOut();
    MB10Ev_TurnNext();
    MB10Ev_CameraRefresh(NULL);
    MB10Ev_ScissorWipeIn();
    MB10Ev_StatusColorUpdate();
    MB10Ev_TelopExec();
    MB10Ev_SaiExec(2);
    MB10Ev_PlayerWalkExec();
    HuPrcVSleep();
    spr = MB10Ev_CaptionCreate(1, 100, 90);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x160D);
    MB10Ev_GuideMotSet(-2);
    MB10Ev_CaptionKill(spr);
    MB10Ev_MasuCoinExec();

    MB10Ev_ScissorWipeOut();
    MB10Ev_TurnNext();
    MB10Ev_CameraRefresh(NULL);
    MB10Ev_ScissorWipeIn();
    MB10Ev_StatusColorUpdate();
    MB10Ev_TelopExec();
    MB10Ev_SaiExec(3);
    MB10Ev_PlayerWalkExec();
    HuPrcVSleep();
    spr = MB10Ev_CaptionCreate(2, 100, 90);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x160E);
    MB10Ev_CaptionKill(spr);
    MB10Ev_MasuCoinExec();

    MB10Ev_ScissorWipeOut();
    MB10Ev_TurnNext();
    MB10Ev_CameraRefresh(NULL);
    MB10Ev_ScissorWipeIn();
    MB10Ev_StatusColorUpdate();
    MB10Ev_TelopExec();
    MB10Ev_SaiExec(5);
    MB10Ev_PlayerWalkExec();
    HuPrcVSleep();
    spr = MB10Ev_CaptionCreate(3, 100, 90);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x160F);
    MB10Ev_CaptionKill(spr);
    MB10Ev_MasuCoinExec();
    HuPrcSleep(10);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x1610);

    MB10Ev_ScissorWipeOut();
    MB10Ev_TurnNext();
    MB10Ev_CameraRefresh(NULL);
    MB10Ev_ScissorWipeIn();
    MB10Ev_PlayerColorReset();
    MB10Ev_StatusColorUpdate();
    MB10Ev_TelopExec();
    MB10Ev_SaiExec(4);
    MB10Ev_PlayerWalkExec();
    HuPrcVSleep();
    spr = MB10Ev_CaptionCreate(4, 100, 90);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x1611);
    MB10Ev_CaptionKill(spr);
    MB10Ev_MasuCoinExec();

    MB10Ev_ScissorWipeOut();
    MB10Ev_TurnNext();
    MB10Ev_CameraRefresh(NULL);
    MB10Ev_ScissorWipeIn();
    MB10Ev_StatusColorUpdate();
    MB10Ev_TelopExec();
    MB10Ev_SaiExec(5);
    MB10Ev_PlayerWalkExec();
    HuPrcVSleep();
    spr = MB10Ev_CaptionCreate(5, 100, 90);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x1612);
    state = 0;
    omAddPrcObj(MB10Ev_ItemMasuKinopioProc, 0x4800, 0, 0)->user_data = &state;
    do {
        HuPrcVSleep();
    } while (state == 0);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x1613);
    state = 2;
    while (state == 2) {
        HuPrcVSleep();
    }
    HuPrcSleep(4);
    state = 0;
    omAddPrcObj(MB10Ev_ItemMasuKoopaJrProc, 0x4800, 0, 0)->user_data = &state;
    do {
        HuPrcVSleep();
    } while (state == 0);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x1614);
    state = 2;
    while (state == 2) {
        HuPrcVSleep();
    }
    MB10Ev_CaptionKill(spr);
    MB10Ev_MasuCoinExec();

    MB10Ev_ScissorWipeOut();
    MB10Ev_TurnNext();
    MB10Ev_CameraRefresh(NULL);
    MB10Ev_ScissorWipeIn();
    MB10Ev_StatusColorUpdate();
    MB10Ev_TelopExec();
    MB10Ev_SaiExec(1);
    MB10Ev_PlayerWalkExec();
    HuPrcVSleep();
    spr = MB10Ev_CaptionCreate(9, 100, 90);
    state = 0;
    omAddPrcObj(MB10Ev_BattleKuriboProc, 0x4800, 0, 0)->user_data = &state;
    while (state == 0) {
        HuPrcVSleep();
    }
    MB10Ev_GuideWinExec(mb10ev_guide, 0x1615);
    state = 2;
    while (state == 2) {
        HuPrcVSleep();
    }
    MB10Ev_CaptionKill(spr);
    MB10Ev_MasuCoinExec();

    MB10Ev_ScissorWipeOut();
    MB10Ev_TurnNext();
    MB10Ev_CameraRefresh(NULL);
    MB10Ev_ScissorWipeIn();
    MB10Ev_StatusColorUpdate();
    MB10Ev_TelopExec();
    MB10Ev_SaiExec(1);
    MB10Ev_PlayerWalkExec();
    HuPrcVSleep();
    spr = MB10Ev_CaptionCreate(6, 100, 90);
    state = 0;
    omAddPrcObj(MB10Ev_GambleProc, 0x4800, 0, 0)->user_data = &state;
    while (state == 0) {
        HuPrcVSleep();
    }
    MB10Ev_GuideWinExec(mb10ev_guide, 0x1616);
    state = 2;
    while (state == 2) {
        HuPrcVSleep();
    }
    MB10Ev_CaptionKill(spr);
    MB10Ev_MasuCoinExec();

    MB10Ev_ScissorWipeOut();
    MB10Ev_TurnNext();
    MB10Ev_CameraRefresh(NULL);
    MB10Ev_ScissorWipeIn();
    MB10Ev_StatusColorUpdate();
    MB10Ev_TelopExec();
    MB10Ev_SaiExec(1);
    MB10Ev_PlayerWalkExec();
    MB10Ev_KakusiExec(mb10ev_guide);
    MB10Ev_MasuCoinExec();
    MBStatusItemDispOff();
    MB10Ev_GuideWinExec(mb10ev_guide, 0x161A);

    MBStatusDispMoveSet(4);
    MB10Ev_GuideMove(mb10ev_guide, -30);
    while (MBStatusMoveCheck()) {
        HuPrcVSleep();
    }
    MB10Ev_GuideWinExec(mb10ev_guide, 0x161B);
    HuPrcChildLink(process, MBMgCallTutorialCreate());
    HuPrcChildWatch();
    MBStatusColorSet(0, 1);
    MBStatusColorSet(1, 1);
    MBStatusColorSet(2, 1);
    MBStatusColorSet(3, 1);
    HuPrcSleep(30);
    MBStatusDispMoveSet(2);
    MBVsSprCreate();
    while (MBStatusMoveCheck()) {
        HuPrcVSleep();
    }
    MB10Ev_GuideWinExec(mb10ev_guide, 0x161C);
    MBVsSprKill();
    MBStatusColorSet(0, 2);
    MBStatusColorSet(1, 1);
    MBStatusColorSet(2, 2);
    MBStatusColorSet(3, 1);
    MBStatusDispMoveSet(2);
    MBVsSprCreate();
    while (MBStatusMoveCheck()) {
        HuPrcVSleep();
    }
    MB10Ev_GuideWinExec(mb10ev_guide, 0x161D);
    MBVsSprKill();
    MBStatusColorSet(0, 1);
    MBStatusColorSet(1, 2);
    MBStatusColorSet(2, 2);
    MBStatusColorSet(3, 2);
    MBStatusDispMoveSet(2);
    MBVsSprCreate();
    while (MBStatusMoveCheck()) {
        HuPrcVSleep();
    }
    MB10Ev_GuideWinExec(mb10ev_guide, 0x161E);
    MBStatusColorSet(0, 2);
    MBStatusColorSet(1, 1);
    MBStatusColorSet(2, 1);
    MBStatusColorSet(3, 1);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x161F);
    HuPrcSleep(15);
    HuPrcSleep(1);
    GwSystem.minigame_index = -1;
    MBMgCallListCreate(-1);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x1620);
    MBMgCallListClose();
    MBStatusDispMoveSet(5);
    while (GwSystem.minigame_index == -1) {
        HuPrcVSleep();
    }
    MBVsSprKill();
    MBMgCallClose();
    MB10Ev_GuideWinExec(mb10ev_guide, 0x1621);
    MBStatusHideAll();
    MBBackThreadPriLowSet();
    Hu3DMotionReset(MBPlayerGet(0)->player_obj->omObj1->model[0]);
    Hu3DMotionReset(MBPlayerGet(1)->player_obj->omObj1->model[0]);
    Hu3DMotionReset(MBPlayerGet(2)->player_obj->omObj1->model[0]);
    Hu3DMotionReset(MBPlayerGet(3)->player_obj->omObj1->model[0]);
    MB10Ev_GuideMove(mb10ev_guide, 0x69);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x1622);

    {
        Vec dir;

        MB10_CameraMasuSet(0x2D);
        MB10_CameraStopWait();
        from = MBMasuGet(0x2D);
        to = MBMasuGet(0x15);
        HuAudFXPlay(0x114);
        chest = MBModelCreate(0x32, NULL);
        MBModelTempAllocFree(chest);
        HuVecSubtract(&dir, &to->coords, &from->coords);
        MBVecNormalize(&dir);
        HuVecCopy3F(&chest->rot, &dir);
        chest->scale.y = 0.0f;
        HuVecCopy3F(&chest->coords, &from->coords);
        MBMotionSet(chest, -1, 1);
        MBModelDispFlagSet(chest);
        contents = MBModelCreate(0x35, mb10ev_bankCoinPileMot);
        MBModelTempAllocFree(contents);
        HuVecCopy3F(&contents->rot, &dir);
        HuVecCopy3F(&contents->coords, &from->coords);
        contents->scale.y = contents->scale.x = contents->scale.z = 1.2f;
        MBModelDispOff(contents);

        scale = 1.0f / sindf(50.0f);
        for (angle = 0.0f; angle < 90.0f; angle += 11.25f) {
            chest->scale.y = sindf(angle) * scale;
            chest->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            chest->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            HuPrcVSleep();
        }
        for (; angle > 50.0f; angle -= 11.25f) {
            chest->scale.y = sindf(angle) * scale;
            chest->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            chest->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            HuPrcVSleep();
        }
        chest->scale.z = chest->scale.x = chest->scale.y = 1.0f;

        MBModelDispFlagSet(contents);
        MBMotionSet(chest, -1, 0);
        Hu3DMotionSpeedSet(chest->omObj1->model[0], 1.2f);
        while (MBMotionCheck(chest) == 0) {
            HuPrcVSleep();
        }
        HuAudFXPlay(0x259);
        MBMotionSet(contents, 0, 0);
        while (MBMotionCheck(contents) == 0) {
            HuPrcVSleep();
        }
        MBMotionSet(contents, -1, 2);
        MB10Ev_GuideWinExec(mb10ev_guide, 0x1623);
        HuPrcSleep(10);

        HuAudFXPlay(0x115);
        MBMotionSet(chest, -1, 4);
        Hu3DMotionSpeedSet(chest->omObj1->model[0], 1.2f);
        model = chest->omObj1->model[0];
        Hu3DMotionTimeSet(model, Hu3DMotion[Hu3DData[model].motId].unk02);
        while (MBMotionStartCheck(chest) == 0) {
            HuPrcVSleep();
        }
        MBModelDispOff(contents);

        scale = 1.0f / sindf(50.0f);
        for (angle = 50.0f; angle < 90.0f; angle += 11.25f) {
            chest->scale.y = sindf(angle) * scale;
            chest->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            chest->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            HuPrcVSleep();
        }
        for (angle = 90.0f; angle > 0.0f; angle -= 11.25f) {
            chest->scale.y = sindf(angle) * scale;
            chest->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            chest->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            HuPrcVSleep();
        }
        chest->scale.y = 0.0f;
        chest->scale.x = 0.0f;
        chest->scale.z = 0.0f;
        MBModelKill(chest);
        MBModelKill(contents);
    }

    MB10_CameraMasuSet(0x2A);
    MB10_CameraStopWait();
    MB10Ev_GuideWinExec(mb10ev_guide, 0x1624);
    HuPrcSleep(10);
    state = 0;
    mb10ev_shopKoopaJrF = 0;
    omAddPrcObj(MB10Ev_ShopProc, 0x4800, 0, 0)->user_data = &state;
    while (state == 0) {
        HuPrcVSleep();
    }
    MB10Ev_GuideWinOpenWait(mb10ev_guide, 0x1625);
    state = 2;
    while (state != 3) {
        HuPrcVSleep();
    }
    state = 0;
    mb10ev_shopKoopaJrF = 1;
    omAddPrcObj(MB10Ev_ShopProc, 0x4800, 0, 0)->user_data = &state;
    while (state == 0) {
        HuPrcVSleep();
    }
    MB10Ev_GuideWinAutoExec(mb10ev_guide, 0x1626);
    state = 2;
    while (state != 3) {
        HuPrcVSleep();
    }
    MB10Ev_GuideWinExec(mb10ev_guide, 0x1627);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x1628);

    MB10_CameraMasuSet(0x25);
    MB10_CameraStopWait();
    HuAudFXPlay(0x159);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x1629);
    HuPrcSleep(10);
    MB10_CameraMasuSet(0x24);
    MB10_CameraStopWait();
    HuAudFXPlay(0x125);
    box = MBModelCreate(0x33, NULL);
    Hu3DModelRemakeStatic(box->omObj1->model[0]);
    MBModelTempAllocFree(box);
    HuVecCopyXYZ(&box->rot, 1.0f, 0.0f, 0.0f);
    box->scale.y = 0.0f;
    HuVecCopy3F(&box->coords, &MBMasuGet(0x24)->coords);
    MBMotionSet(box, -1, 1);
    MBModelDispOn(box);

    scale = 1.0f / sindf(50.0f);
    for (angle = 0.0f; angle < 90.0f; angle += 11.25f) {
        box->scale.y = sindf(angle) * scale;
        box->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
        box->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
        HuPrcVSleep();
    }
    for (; angle > 50.0f; angle -= 11.25f) {
        box->scale.y = sindf(angle) * scale;
        box->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
        box->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
        HuPrcVSleep();
    }
    box->scale.z = box->scale.x = box->scale.y = 1.0f;
    MBMotionSet(box, -1, 0);
    Hu3DMotionSpeedSet(box->omObj1->model[0], 1.2f);
    while (MBMotionCheck(box) == 0) {
        HuPrcVSleep();
    }

    HuAudFXPlay(0x257);
    MBModelDispOn(mb10_teresaGuideMdl);
    for (alpha = 0; alpha < 256; alpha += 12) {
        Hu3DModelTPLvlSet(mb10_teresaGuideMdl->omObj1->model[0], alpha);
        Hu3DModelTPLvlSet(mb10_teresaGuideMdl->omObj2->model[0], alpha);
        HuPrcVSleep();
    }
    Hu3DModelTPLvlSet(mb10_teresaGuideMdl->omObj1->model[0], 0xFF);
    Hu3DModelTPLvlSet(mb10_teresaGuideMdl->omObj2->model[0], 0xFF);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x162A);
    for (alpha = 255; alpha >= 0; alpha -= 12) {
        Hu3DModelTPLvlSet(mb10_teresaGuideMdl->omObj1->model[0], alpha);
        Hu3DModelTPLvlSet(mb10_teresaGuideMdl->omObj2->model[0], alpha);
        HuPrcVSleep();
    }
    Hu3DModelTPLvlSet(mb10_teresaGuideMdl->omObj1->model[0], 0);
    Hu3DModelTPLvlSet(mb10_teresaGuideMdl->omObj2->model[0], 0);
    MBModelDispOff(mb10_teresaGuideMdl);

    HuAudFXPlay(0x126);
    MBMotionSet(box, -1, 4);
    Hu3DMotionSpeedSet(box->omObj1->model[0], 1.2f);
    model = box->omObj1->model[0];
    Hu3DMotionTimeSet(model, Hu3DMotion[Hu3DData[model].motId].unk02);
    while (MBMotionStartCheck(box) == 0) {
        HuPrcVSleep();
    }
    scale = 1.0f / sindf(50.0f);
    for (angle = 50.0f; angle < 90.0f; angle += 11.25f) {
        box->scale.y = sindf(angle) * scale;
        box->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
        box->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
        HuPrcVSleep();
    }
    for (angle = 90.0f; angle > 0.0f; angle -= 11.25f) {
        box->scale.y = sindf(angle) * scale;
        box->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
        box->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
        HuPrcVSleep();
    }
    box->scale.y = 0.0f;
    box->scale.x = 0.0f;
    box->scale.z = 0.0f;
    MBModelKill(box);

    MB10Ev_GuideMove(mb10ev_guide, -30);
    MB10_CameraMasuSet(0x22);
    MB10_CameraStopWait();
    mb10_pauseOffF = 1;
    for (i = 0; i < 4; i++) {
        mb10ev_cartJumpStateTbl[i] = 0;
    }
    mb10ev_actionTimeSprProc = omAddPrcObj(MB10Ev_ActionTimeSpr, 0x4800, 0, 0);
    while (mb10ev_actionTimeSprProc->user_data == NULL) {
        HuPrcVSleep();
    }
    MB10Ev_GuideWinExec(mb10ev_guide, 0x162B);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x162C);
    mb10ev_cartJumpStateTbl[0] = 1;
    mb10ev_cartJumpStateTbl[1] = 1;
    mb10ev_cartJumpStateTbl[2] = 1;

    runner = omAddPrcObj(MB10Ev_CartJumpProc, 0x4800, 0, 0x40);
    runner->user_data = data = HuMemMemoryAlloc(runner->heap, 0x20);
    data->player = 0;
    data->unk4 = 0;
    data->slot = 0;
    data->unkC = 0;
    runner = omAddPrcObj(MB10Ev_CartJumpProc, 0x4800, 0, 0x40);
    runner->user_data = data = HuMemMemoryAlloc(runner->heap, 0x20);
    data->player = 1;
    data->unk4 = 0;
    data->slot = 0;
    data->unkC = 0;
    runner = omAddPrcObj(MB10Ev_CartJumpProc, 0x4800, 0, 0x40);
    runner->user_data = data = HuMemMemoryAlloc(runner->heap, 0x20);
    data->player = 2;
    data->unk4 = 0;
    data->slot = 1;
    data->unkC = 0;

    {
        Vec pos;
        Object *target;

        sfx = HuAudFXPlay(0x185);
        mb10_cartMoveF = 1;
        from = MBMasuGet(0x26);
        HuVecCopy3F(&pos, &from->coords);
        pos.x += 100.0f;
        target = mb10_cartMdl;
        HuPrcChildLink(HuPrcCurrentGet(), MBVecSpeedMoveCreate(&target->coords, &pos, &target->coords, 2.0f));
        MB10_CameraMasuSet(-2);
        HuVecCopy3F(&mb10_cameraPos, &MBMasuGet(0x22)->coords);
        MBCameraFocusVecSet(&mb10_cameraPos);
        HuPrcChildLink(HuPrcCurrentGet(), MBVecSpeedMoveCreate(&mb10_cameraPos, &from->coords,
                                                                     &mb10_cameraPos, 2.0f));
        HuPrcChildWatch();
        HuAudFXFadeOut(sfx, 30);
    }
    mb10ev_cartJumpStateTbl[0] = -1;
    mb10_pauseOffF = 0;

    MB10Ev_GuideMove(mb10ev_guide, 0x69);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x162D);
    MB10Ev_IconFrameCreate(0xA0, 0x4C);
    HuPrcSleep(10);
    MB10Ev_IconCreate(0, 0xA0, 0x4C);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x162E);
    MB10Ev_IconKill();
    MB10Ev_IconCreate(1, 0xA0, 0x4C);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x162F);
    MB10Ev_IconKill();
    MB10Ev_IconCreate(2, 0xA0, 0x4C);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x1630);
    MB10Ev_IconKill();
    HuPrcSleep(10);
    MB10Ev_IconFrameKill();
    HuPrcSleep(10);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x1631);
    MB10Ev_GuideWinExec(mb10ev_guide, 0x1632);
    MBGuideFaceSet(mb10ev_guide->obj, mb10ev_guideFaceEndTbl[0]);
    HuPrcSleep(30);
    HuAudSeqFadeOut(60);
    WipeCreateOut(WIPE_STARS, 16);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    HuPrcSleep(16);
    MBGuideKill(mb10ev_guide);
    MBExit();
    MBBoardReturnOff();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

void MB10Ev_KakusiExec(UnkMBGuideData *guide) {
    GW_SYSTEM *system = &GwSystem;
    Process *process;
    Process *proc;

    process = HuPrcCurrentGet();
    HuPrcChildLink(process, MBCameraZoomMotStart(1.6f));
    proc = MBKakusiStarBlockCreate(system->current_player_index);
    MBKakusiWaitOn();
    HuPrcChildWatch();
    MB10Ev_GuideWinOpen(guide, 0x1617);
    MBKakusiWaitOff();
    while (!MBKakusiWaitCheck()) {
        HuPrcVSleep();
    }
    MB10Ev_GuideWinClose(guide);
    MBKakusiWaitOff();
    HuPrcChildLink(process, proc);
    HuPrcChildWatch();

    proc = MBKakusiCoinBlockCreate(system->current_player_index);
    MBKakusiWaitOn();
    MBKakusiWaitOff();
    while (!MBKakusiWaitCheck()) {
        HuPrcVSleep();
    }
    HuPrcChildLink(process, proc);
    HuPrcChildWatch();
    MB10Ev_GuideWinExec(guide, 0x1618);

    proc = MBKakusiItemBlockCreate(system->current_player_index, 0);
    MBKakusiWaitOn();
    MBKakusiWaitOff();
    while (!MBKakusiWaitCheck()) {
        HuPrcVSleep();
    }
    HuPrcChildLink(process, proc);
    HuPrcChildWatch();
    MB10Ev_GuideWinExec(guide, 0x1619);

    HuPrcChildLink(process, MBCameraZoomMotStart(1.3f));
    HuPrcChildWatch();
    HuPrcSleep(1);
}

s16 MB10_PauseQuitCheck(s32 player) {
    UnkBoard8 *dimmer;
    UnkBoard8 *icon;
    void *data;
    s16 size[2];
    s16 win;
    s16 choice;

    HuAudSeqVolSet(0x60);
    dimmer = MBSprGrpCreate(1, 0);
    data = DataRead(0x13025D);
    dimmer->model[0] = HuSprAnimRead(data);
    HuSprGrpMemberSet(dimmer->spriteGroup, 0, dimmer->model[0], 0);
    HuSprPriSet(dimmer->spriteGroup, 0, 9);
    HuSprAttrSet(dimmer->spriteGroup, 0, HUSPR_ATTR_XLU);
    HuSprPosSet(dimmer->spriteGroup, 0, 0xA0, 0x78);
    HuSprScaleSet(dimmer->spriteGroup, 0, 40.0f, 30.0f);
    HuSprColorTPLvlSet(dimmer->spriteGroup, 0, 0, 0, 0, 0xC0);
    DataClose(data);

    icon = MBSprGrpCreate(2, 0);
    data = DataRead(0x130009);
    icon->model[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(icon->spriteGroup, 0, icon->model[0], 0);
    HuSprPriSet(icon->spriteGroup, 0, 8);
    HuSprAttrSet(icon->spriteGroup, 0, HUSPR_ATTR_XLU);
    HuSprPosSet(icon->spriteGroup, 0, 0x9E, 0x78);
    HuSprColorSet(icon->spriteGroup, 0, 0x89, 0xCA, 0xB2);

    HuWinMesMaxSizeGet(1, size, 0x1633);
    win = HuWinCreate(0x49, 0x4B, size[0], size[1], 0, 2);
    HuWinPriSet(win, 5);
    HuWinBGTPLvlSet(win, 0);
    HuWinDummy(win);
    HuWinMesPalSet(win, 7, 0, 0, 0xE0);
    HuWinMesPalSet(win, 0, 0x89, 0xCA, 0xB2);
    HuWinMesPalSet(win, 4, 0, 0x80, 0);
    HuWinBGColSet(win, 0x89, 0xCA, 0xB2);
    HuWinMesSet(win, 0x1633, -1, -1);
    HuWinMesSpeedSet(win, 0);
    while (HuWinStatGet(win) != 0) {
        HuPrcVSleep();
    }
    HuWinActivePlayerSet(win, 1 << player);
    choice = HuWinChoiceGet(win, 0, 0);
    HuWinKill(win);
    HuAudSeqVolSet(0x7F);
    MBSprGrpKill(dimmer);
    MBSprGrpKill(icon);
    return choice == 1;
}

void MB10_PauseProc(void) {
    Vec2f pos;
    s32 player;
    s32 i;

    mb10_pauseOffF = 0;
    while (TRUE) {
        HuPrcVSleep();
        if (WipeStatGet() != 0 || wipeMode == 3) {
            continue;
        }
        player = MBPlayerTurnGet();
        for (i = 0; i < 4; i++) {
            if (!(ContBtnDown[i] & START_BUTTON) || mb10_pauseOffF != 0) {
                continue;
            }
            MBSaiSeStop(player);
            MBCameraPos2DGet(&pos);
            MBCameraPos2DSet(&pos);
            winPauseF = 1;
            omAllPause();
            Hu3DPauseF = 1;
            if (MB10_PauseQuitCheck(i)) {
                HuAudSeqFadeOut(0x5A);
                WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
                HuPrcSleep(0x11);
                omDelPrcObj(mb10_starGuideHoverProc);
                MBExit();
                MBBoardReturnOff();
                omOvlReturnEx(1);
                omOvlKill();
                HuPrcVSleep();
            }
            Hu3DPauseF = 0;
            omAllUPause();
            winPauseF = 0;
            MBSaiSeResume(player);
            break;
        }
    }
}

void MB10_Create(void) {
    Vec dir;
    SpaceData *space;
    GW_PLAYER *player;
    s16 spaceIdx;
    s32 i;

    Hu3DCamInit(2);
    omInitObjMan(0x50, 0x28);
    omGameSysInit();
    Hu3DGLightMaxSet(1);
    Hu3DGLightColorSet(0, 0x78, 0x78, 0x78);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -100.0f, 100.0f, 300.0f);
    MBObjectSetup(0x15, 0x240, 0, 0);
    space = MBMasuGet(0x2A);
    MBVecDirGet(&space->coords, &MBMasuGet(0x2B)->coords, &dir);
    MBMasuArrowAngleAdd(MBVecAngleGet(&dir) + 180.0f);
    for (i = 0; i < 4; i++) {
        MBPlayerGet(i)->coin = 10;
    }
    MB10_StarGuideCreateAll();
    MB10_TeresaGuideCreateAll();
    MB10_BankCoinCreateAll();
    MBMasuEventTblAdd(mb10_specialEventTbl);
    for (i = 0; i < 4; i++) {
        player = MBPlayerGet(i);
        spaceIdx = MBMasuLinkMasuIdGet(player->clink, player->cidx);
        MBPlayerPosMasuSet(i, spaceIdx);
        MBPlayerForwardSet(i);
    }
    MBMasuTypeListCreate();
    MBBackThreadPriHighSet();
    MBCameraSpeedDivSet(1.0f);
    MBCameraSpeedSet(-1.0f);
    MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
    omAddPrcObj(MB10Ev_TutorialProc, 0xEFFF, 0, 0);
    omAddPrcObj(MB10_CameraProc, 0x1005, 0, 0);
    omPrcSetStatBit(omAddPrcObj(MB10_PauseProc, 0x1005, 0, 0), OM_STAT_NOALLPAUSE);
    omAddPrcObj(MB10_CartProc, 0x4800, 0, 0);
}
