#include "common_duel.h"
#include "ovl_81.h"

void MBDItemWarpBlockSwapInit(void) {
    mbdItemWarpPlayerA = -1;
    mbdItemWarpPlayerB = -1;
}

s32 MBDPlayerOtherCheck(s16 arg0, s16 arg1) {
    return arg0 != arg1;
}

void MBDItemWarpPlayerSet(s16 arg0, s16 arg1) {
    s16 v0;
    s16 v1 = arg1;

    v0 = arg1;
    if (v0 == MBDGetCurrentPlayerIndex()) {
        mbdItemWarpPlayerA = v1;
        mbdItemWarpPlayerB = arg0;
    } else {
        mbdItemWarpPlayerA = arg0;
        mbdItemWarpPlayerB = v1;
    }
}

s32 MBDItemWarpBlockSwapPlayerSet(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);
    s16 indices[MBD_MAX_PLAYERS];
    s32 otherIndex;
    s32 i;

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        indices[i] = i;
    }
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        otherIndex = indices[i];
        if (player->turn != otherIndex && MBDPlayerOtherCheck(player->turn, otherIndex)) {
            break;
        }
    }
    if (i != MBD_MAX_PLAYERS) {
        MBDItemWarpPlayerSet(player->turn, otherIndex);
        return 1;
    }
    return 0;
}

void MBDItemWarpBlockSwap(void) {
    GW_PLAYER *player1;
    GW_PLAYER *player2;
    GW_PLAYER *playerCopy;
    Object *obj1;
    Object *obj2;
    Object *effect;
    f32 scaleY;
    f32 scaleXZ;
    s32 i;

    MBDCameraFocusModeSet(0);
    player1 = MBDGetPlayerStruct(mbdItemWarpPlayerA);
    player2 = MBDGetPlayerStruct(mbdItemWarpPlayerB);
    player1->stat |= 4;
    player2->stat |= 4;
    obj1 = player1->player_obj;
    obj2 = player2->player_obj;

    HuAudFXPlay(0x1F5);
    effect = MBDModelCreate(0x1F, NULL);
    MBDMotionSet(effect, -1, 0);
    HuVecCopy3F(&effect->coords, &obj1->coords);
    MBDPlayerVibrate(mbdItemWarpPlayerA, 1);
    for (i = 0; i < 15; i++) {
        scaleY = (f32)i / 15.0f;
        scaleXZ = 1.0f - scaleY;
        scaleY += 1.0f;
        obj1->scale.x = scaleXZ;
        obj1->scale.y = scaleY;
        obj1->scale.z = scaleXZ;
        MBDPlayerScaleSet(mbdItemWarpPlayerA, &obj1->scale);
        HuPrcVSleep();
    }
    obj1->scale.x = 0.0f;
    obj1->scale.y = 0.0f;
    obj1->scale.z = 0.0f;
    MBDPlayerScaleSet(mbdItemWarpPlayerA, &obj1->scale);
    HuPrcVSleep();
    obj1->flags &= ~2;
    MBDModelDispOff(obj1);
    MBDModelKill(effect);

    HuAudFXPlay(0x1F5);
    effect = MBDModelCreate(0x1F, NULL);
    MBDMotionSet(effect, -1, 0);
    HuVecCopy3F(&effect->coords, &obj2->coords);
    MBDPlayerVibrate(mbdItemWarpPlayerB, 1);
    for (i = 0; i < 15; i++) {
        scaleY = (f32)i / 15.0f;
        scaleXZ = 1.0f - scaleY;
        scaleY += 1.0f;
        obj2->scale.x = scaleXZ;
        obj2->scale.y = scaleY;
        obj2->scale.z = scaleXZ;
        MBDPlayerScaleSet(mbdItemWarpPlayerB, &obj2->scale);
        HuPrcVSleep();
    }
    playerCopy = player1;
    MBDModelKill(effect);

    duelUnkF0 = 0;
    MBDPlayerMasuSwap(mbdItemWarpPlayerA, mbdItemWarpPlayerB);
    MBDPlayerPosMasuSet(mbdItemWarpPlayerA, MBDMasuLinkMasuIdGet(playerCopy->clink, player1->cidx));
    MBDPlayerPosMasuSet(mbdItemWarpPlayerB, MBDMasuLinkMasuIdGet(player2->clink, player2->cidx));
    MBDPartnerPosFix(mbdItemWarpPlayerA);
    MBDPartnerPosFix(mbdItemWarpPlayerB);

    HuAudFXPlay(0x1F5);
    effect = MBDModelCreate(0x1F, NULL);
    MBDMotionSet(effect, -1, 0);
    HuVecCopy3F(&effect->coords, &obj2->coords);
    MBDPlayerVibrate(mbdItemWarpPlayerB, 1);
    for (i = 14; i >= 0; i--) {
        scaleY = (f32)i / 15.0f;
        scaleXZ = 1.0f - scaleY;
        scaleY += 1.0f;
        obj2->scale.x = scaleXZ;
        obj2->scale.y = scaleY;
        obj2->scale.z = scaleXZ;
        MBDPlayerScaleSet(mbdItemWarpPlayerB, &obj2->scale);
        HuPrcVSleep();
    }
    MBDModelKill(effect);

    WipeCreateOut(0, 16);
    HuPrcSleep(16);
    MBDBackRefresh(&obj1->coords, 1);
    MBDPlayerPosFixSet(0, 1);
    MBDPlayerPosFixSet(1, 1);
    WipeCreateIn(0, 16);
    HuPrcSleep(16);

    HuAudFXPlay(0x1F5);
    obj1->flags |= 2;
    MBDModelDispOn(obj1);
    effect = MBDModelCreate(0x1F, NULL);
    MBDMotionSet(effect, -1, 0);
    HuVecCopy3F(&effect->coords, &obj1->coords);
    MBDPlayerVibrate(mbdItemWarpPlayerA, 1);
    for (i = 14; i >= 0; i--) {
        scaleY = (f32)i / 15.0f;
        scaleXZ = 1.0f - scaleY;
        scaleY += 1.0f;
        obj1->scale.x = scaleXZ;
        obj1->scale.y = scaleY;
        obj1->scale.z = scaleXZ;
        MBDPlayerScaleSet(mbdItemWarpPlayerA, &obj1->scale);
        HuPrcVSleep();
    }
    MBDModelKill(effect);
    playerCopy->stat &= ~4;
    player2->stat &= ~4;

    if (mbdItemWarpPlayerA != MBDGetCurrentPlayerIndex()) {
        HuPrcSleep(15);
        WipeCreateOut(0, 16);
        HuPrcSleep(16);
        MBDBackRefresh(&MBDGetPlayerStruct(-1)->player_obj->coords, 1);
        WipeCreateIn(0, 16);
        HuPrcSleep(16);
    }
    HuPrcSleep(15);
    MBDDlgResultWinExec(0x1F2E);
    MBDCameraFocusModeSet(1);
    MBDItemWarpBlockSwapInit();
    omDelPrcObj(NULL);
}

void MBDItemWarpBlockSwapCreate(void) {
    Process *parent = HuPrcCurrentGet();

    HuPrcChildLink(parent, omAddPrcObj(MBDItemWarpBlockSwap, 0x1003, 0, 0));
    HuPrcChildWatch();
}

s16 MBDItemWarpPlayerGet(void) {
    return mbdItemWarpPlayerA;
}

void MBDWarpAuraSpinProc(void) {
    MBDAuraSpinExec(1);
    HuPrcSleep(-1);
}

void MBDWarpEffProc(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);
    s16 effect = EffectCreate(0x110012, 0x2A9);
    s32 i;

    Hu3DModelCameraSet(effect, 1);
    EffectParamSet(effect, 1.0f, 30.0f, 1.0f);
    EffectRangeSet(effect, 10.0f);
    for (i = 0; i < 30; i++) {
        EffectPosSet(effect, player->player_obj->coords.x, player->player_obj->coords.y + 30.0f,
                           player->player_obj->coords.z);
        HuPrcVSleep();
    }
    EffectStop(effect);
    omDelPrcObj(NULL);
}

void MBDWarpMasuProc(void) {
    GW_PLAYER *player;
    Object *obj;
    Object *effect;
    f32 scaleY;
    f32 scaleXZ;
    Process *process;
    s32 i;
    s32 tempLink;
    s32 tempIdx;

    MBDCameraFocusModeSet(0);
    player = MBDGetPlayerStruct(mbdItemWarpPlayerA);
    player->stat |= 4;
    obj = player->player_obj;
    MBDAuraCreate(&obj->coords);
    MBDAuraLandNoSe(1);
    MBDAuraHoverStart();
    process = omAddPrcObj(MBDWarpAuraSpinProc, 10, 0, 0);
    HuPrcSleep(10);

    HuAudFXPlay(0x1F7);
    effect = MBDModelCreate(0x1F, NULL);
    MBDMotionSet(effect, -1, 0);
    HuVecCopy3F(&effect->coords, &obj->coords);
    MBDPlayerVibrate(mbdItemWarpPlayerA, 1);
    for (i = 0; i < 15; i++) {
        scaleY = (f32)i / 15.0f;
        scaleXZ = 1.0f - scaleY;
        scaleY += 1.0f;
        obj->scale.x = scaleXZ;
        obj->scale.y = scaleY;
        obj->scale.z = scaleXZ;
        MBDPlayerScaleSet(mbdItemWarpPlayerA, &obj->scale);
        HuPrcVSleep();
    }
    obj->scale.x = 0.0f;
    obj->scale.y = 0.0f;
    obj->scale.z = 0.0f;
    MBDPlayerScaleSet(mbdItemWarpPlayerA, &obj->scale);
    HuPrcVSleep();
    obj->flags &= ~2;
    MBDModelDispOff(obj);
    MBDModelKill(effect);

    player->clink = player->nlink = player->blink = mbdWarpLink;
    player->cidx = mbdWarpIdx;
    player->nidx = mbdWarpIdx + 1;
    player->bidx = mbdWarpIdx - 1;
    player->nnidx = player->nnlink = -1;
    if (mbdWarpBackLink != -1) {
        player->blink = mbdWarpBackLink;
    }
    if (mbdWarpBackIdx != -1) {
        player->bidx = mbdWarpBackIdx;
    }
    player->rev = 0;
    duelUnkF0 = 0;
    MBDPlayerPosMasuSet(mbdItemWarpPlayerA, MBDMasuLinkMasuIdGet(player->clink, player->cidx));
    if (GwSystem.current_board_index == 5 && GwSystem.boardData.halfWordBytes[0] != 0) {
        player->rev = 1;
        tempLink = player->nlink;
        tempIdx = player->nidx;
        player->nlink = player->blink;
        player->nidx = player->bidx;
        player->blink = tempLink;
        player->bidx = tempIdx;
    }

    WipeCreateOut(0, 16);
    HuPrcSleep(16);
    omDelPrcObj(process);
    MBDAuraHoverStop();
    MBDAuraKill();
    MBDBackRefresh(&obj->coords, 1);
    MBDPlayerPosFixSet(0, 1);
    MBDPlayerPosFixSet(1, 1);
    WipeCreateIn(0, 16);
    HuPrcSleep(16);
    omAddPrcObj(MBDWarpEffProc, 10, 0, 0);
    HuPrcSleep(10);

    HuAudFXPlay(0x1F8);
    obj->flags |= 2;
    MBDModelDispOn(obj);
    effect = MBDModelCreate(0x1F, NULL);
    MBDMotionSet(effect, -1, 0);
    HuVecCopy3F(&effect->coords, &obj->coords);
    MBDPlayerVibrate(mbdItemWarpPlayerA, 1);
    for (i = 14; i >= 0; i--) {
        scaleY = (f32)i / 15.0f;
        scaleXZ = 1.0f - scaleY;
        scaleY += 1.0f;
        obj->scale.x = scaleXZ;
        obj->scale.y = scaleY;
        obj->scale.z = scaleXZ;
        MBDPlayerScaleSet(mbdItemWarpPlayerA, &obj->scale);
        HuPrcVSleep();
    }
    MBDModelKill(effect);
    player->stat &= ~4;
    HuPrcSleep(15);
    MBDCameraFocusModeSet(1);
    MBDItemWarpBlockSwapInit();
    omDelPrcObj(NULL);
}

void MBDWarpMasuExec(s32 link, s32 idx, s32 backLink, s32 backIdx) {
    Process *parent;

    mbdItemWarpPlayerA = MBDGetCurrentPlayerIndex();
    mbdWarpLink = link;
    mbdWarpIdx = idx;
    mbdWarpBackLink = backLink;
    mbdWarpBackIdx = backIdx;
    parent = HuPrcCurrentGet();
    HuPrcChildLink(parent, omAddPrcObj(MBDWarpMasuProc, 0x1003, 0, 0));
    HuPrcChildWatch();
}

void MBDWarpPosProc(void) {
    GW_PLAYER *player;
    Object *obj;
    Object *effect;
    f32 scaleY;
    f32 scaleXZ;
    Object *partner;
    s32 i;

    player = MBDGetPlayerStruct(mbdItemWarpPlayerA);
    player->stat |= 4;
    obj = player->player_obj;

    HuAudFXPlay(0x1F7);
    effect = MBDModelCreate(0x1F, NULL);
    MBDMotionSet(effect, -1, 0);
    obj->flags &= ~2;
    HuVecCopy3F(&effect->coords, &obj->coords);
    for (i = 0; i < 15; i++) {
        scaleY = (f32)i / 15.0f;
        scaleXZ = 1.0f - scaleY;
        scaleY += 1.0f;
        obj->scale.x = scaleXZ;
        obj->scale.y = scaleY;
        obj->scale.z = scaleXZ;
        MBDPlayerScaleSet(mbdItemWarpPlayerA, &obj->scale);
        HuPrcVSleep();
    }
    obj->scale.x = 0.0f;
    obj->scale.y = 0.0f;
    obj->scale.z = 0.0f;
    MBDPlayerScaleSet(mbdItemWarpPlayerA, &obj->scale);
    HuPrcVSleep();
    MBDModelDispOff(obj);
    MBDModelKill(effect);

    HuVecCopy3F(&obj->coords, &mbdWarpPosA);
    MBDVecForwardSet(&obj->rot);
    partner = MBDGetPlayerPartnerRef(mbdItemWarpPlayerA, PARTNER_FRONT);
    if (partner != NULL) {
        HuVecCopy3F(&partner->coords, &mbdWarpPosB);
        MBDVecForwardSet(&partner->rot);
    }
    partner = MBDGetPlayerPartnerRef(mbdItemWarpPlayerA, PARTNER_BACK);
    if (partner != NULL) {
        HuVecCopy3F(&partner->coords, &mbdWarpPosC);
        MBDVecForwardSet(&partner->rot);
    }
    HuPrcVSleep();

    HuAudFXPlay(0x1F8);
    obj->flags |= 2;
    MBDModelDispOn(obj);
    effect = MBDModelCreate(0x1F, NULL);
    MBDMotionSet(effect, -1, 0);
    HuVecCopy3F(&effect->coords, &obj->coords);
    for (i = 14; i >= 0; i--) {
        scaleY = (f32)i / 15.0f;
        scaleXZ = 1.0f - scaleY;
        scaleY += 1.0f;
        obj->scale.x = scaleXZ;
        obj->scale.y = scaleY;
        obj->scale.z = scaleXZ;
        MBDPlayerScaleSet(mbdItemWarpPlayerA, &obj->scale);
        HuPrcVSleep();
    }
    MBDModelKill(effect);
    player->stat &= ~4;
    HuPrcSleep(15);
    MBDItemWarpBlockSwapInit();
    omDelPrcObj(NULL);
}

void MBDWarpPosExec(s32 playerIndex, Vec *pos, Vec *pos1, Vec *pos2) {
    Process *parent;

    mbdItemWarpPlayerA = playerIndex;
    HuVecCopy3F(&mbdWarpPosA, pos);
    HuVecCopy3F(&mbdWarpPosB, pos1);
    HuVecCopy3F(&mbdWarpPosC, pos2);
    parent = HuPrcCurrentGet();
    HuPrcChildLink(parent, omAddPrcObj(MBDWarpPosProc, 0x1003, 0, 0));
    HuPrcChildWatch();
}
