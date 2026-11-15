#include "common_duel.h"
#include "ovl_81.h"

void func_800E18C0_name_81(void) {
    D_80102BF0_name_81 = -1;
    D_80102BF2_name_81 = -1;
}

s32 func_800E18D8_name_81(s16 arg0, s16 arg1) {
    return arg0 != arg1;
}

void func_800E18E8_name_81(s16 arg0, s16 arg1) {
    s16 v0;
    s16 v1 = arg1;

    v0 = arg1;
    if (v0 == MBDGetCurrentPlayerIndex()) {
        D_80102BF0_name_81 = v1;
        D_80102BF2_name_81 = arg0;
    } else {
        D_80102BF0_name_81 = arg0;
        D_80102BF2_name_81 = v1;
    }
}

s32 func_800E1960_name_81(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);
    s16 indices[MBD_MAX_PLAYERS];
    s32 otherIndex;
    s32 i;

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        indices[i] = i;
    }
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        otherIndex = indices[i];
        if (player->turn != otherIndex && func_800E18D8_name_81(player->turn, otherIndex)) {
            break;
        }
    }
    if (i != MBD_MAX_PLAYERS) {
        func_800E18E8_name_81(player->turn, otherIndex);
        return 1;
    }
    return 0;
}

void func_800E1A24_name_81(void) {
    GW_PLAYER *player1;
    GW_PLAYER *player2;
    GW_PLAYER *playerCopy;
    Object *obj1;
    Object *obj2;
    Object *effect;
    f32 scaleY;
    f32 scaleXZ;
    s32 i;

    func_800FC888_name_81(0);
    player1 = MBDGetPlayerStruct(D_80102BF0_name_81);
    player2 = MBDGetPlayerStruct(D_80102BF2_name_81);
    player1->stat |= 4;
    player2->stat |= 4;
    obj1 = player1->player_obj;
    obj2 = player2->player_obj;

    HuAudFXPlay(0x1F5);
    effect = func_800D8010_name_81(0x1F, NULL);
    MBDMotionSet(effect, -1, 0);
    HuVecCopy3F(&effect->coords, &obj1->coords);
    func_800FFAE0_name_81(D_80102BF0_name_81, 1);
    for (i = 0; i < 15; i++) {
        scaleY = (f32)i / 15.0f;
        scaleXZ = 1.0f - scaleY;
        scaleY += 1.0f;
        obj1->scale.x = scaleXZ;
        obj1->scale.y = scaleY;
        obj1->scale.z = scaleXZ;
        func_800F3B94_name_81(D_80102BF0_name_81, &obj1->scale);
        HuPrcVSleep();
    }
    obj1->scale.x = 0.0f;
    obj1->scale.y = 0.0f;
    obj1->scale.z = 0.0f;
    func_800F3B94_name_81(D_80102BF0_name_81, &obj1->scale);
    HuPrcVSleep();
    obj1->flags &= ~2;
    MBDModelDispOff(obj1);
    MBDModelKill(effect);

    HuAudFXPlay(0x1F5);
    effect = func_800D8010_name_81(0x1F, NULL);
    MBDMotionSet(effect, -1, 0);
    HuVecCopy3F(&effect->coords, &obj2->coords);
    func_800FFAE0_name_81(D_80102BF2_name_81, 1);
    for (i = 0; i < 15; i++) {
        scaleY = (f32)i / 15.0f;
        scaleXZ = 1.0f - scaleY;
        scaleY += 1.0f;
        obj2->scale.x = scaleXZ;
        obj2->scale.y = scaleY;
        obj2->scale.z = scaleXZ;
        func_800F3B94_name_81(D_80102BF2_name_81, &obj2->scale);
        HuPrcVSleep();
    }
    playerCopy = player1;
    MBDModelKill(effect);

    D_800CE1D0_main = 0;
    func_800EB8B0_name_81(D_80102BF0_name_81, D_80102BF2_name_81);
    func_800EB6C4_name_81(D_80102BF0_name_81, MBDMasuLinkMasuIdGet(playerCopy->clink, player1->cidx));
    func_800EB6C4_name_81(D_80102BF2_name_81, MBDMasuLinkMasuIdGet(player2->clink, player2->cidx));
    func_800ED214_name_81(D_80102BF0_name_81);
    func_800ED214_name_81(D_80102BF2_name_81);

    HuAudFXPlay(0x1F5);
    effect = func_800D8010_name_81(0x1F, NULL);
    MBDMotionSet(effect, -1, 0);
    HuVecCopy3F(&effect->coords, &obj2->coords);
    func_800FFAE0_name_81(D_80102BF2_name_81, 1);
    for (i = 14; i >= 0; i--) {
        scaleY = (f32)i / 15.0f;
        scaleXZ = 1.0f - scaleY;
        scaleY += 1.0f;
        obj2->scale.x = scaleXZ;
        obj2->scale.y = scaleY;
        obj2->scale.z = scaleXZ;
        func_800F3B94_name_81(D_80102BF2_name_81, &obj2->scale);
        HuPrcVSleep();
    }
    MBDModelKill(effect);

    WipeCreateOut(0, 16);
    HuPrcSleep(16);
    func_800E890C_name_81(&obj1->coords, 1);
    func_800FCF50_name_81(0, 1);
    func_800FCF50_name_81(1, 1);
    WipeCreateIn(0, 16);
    HuPrcSleep(16);

    HuAudFXPlay(0x1F5);
    obj1->flags |= 2;
    MBDModelDispOn(obj1);
    effect = func_800D8010_name_81(0x1F, NULL);
    MBDMotionSet(effect, -1, 0);
    HuVecCopy3F(&effect->coords, &obj1->coords);
    func_800FFAE0_name_81(D_80102BF0_name_81, 1);
    for (i = 14; i >= 0; i--) {
        scaleY = (f32)i / 15.0f;
        scaleXZ = 1.0f - scaleY;
        scaleY += 1.0f;
        obj1->scale.x = scaleXZ;
        obj1->scale.y = scaleY;
        obj1->scale.z = scaleXZ;
        func_800F3B94_name_81(D_80102BF0_name_81, &obj1->scale);
        HuPrcVSleep();
    }
    MBDModelKill(effect);
    playerCopy->stat &= ~4;
    player2->stat &= ~4;

    if (D_80102BF0_name_81 != MBDGetCurrentPlayerIndex()) {
        HuPrcSleep(15);
        WipeCreateOut(0, 16);
        HuPrcSleep(16);
        func_800E890C_name_81(&MBDGetPlayerStruct(-1)->player_obj->coords, 1);
        WipeCreateIn(0, 16);
        HuPrcSleep(16);
    }
    HuPrcSleep(15);
    func_800EAFC4_name_81(0x1F2E);
    func_800FC888_name_81(1);
    func_800E18C0_name_81();
    omDelPrcObj(NULL);
}

void func_800E1F38_name_81(void) {
    Process *parent = HuPrcCurrentGet();

    HuPrcChildLink(parent, omAddPrcObj(func_800E1A24_name_81, 0x1003, 0, 0));
    HuPrcChildWatch();
}

s16 func_800E1F88_name_81(void) {
    return D_80102BF0_name_81;
}

void func_800E1F94_name_81(void) {
    func_800EE74C_name_81(1);
    HuPrcSleep(-1);
}

void func_800E1FB8_name_81(void) {
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

void func_800E209C_name_81(void) {
    GW_PLAYER *player;
    Object *obj;
    Object *effect;
    f32 scaleY;
    f32 scaleXZ;
    Process *process;
    s32 i;
    s32 tempLink;
    s32 tempIdx;

    func_800FC888_name_81(0);
    player = MBDGetPlayerStruct(D_80102BF0_name_81);
    player->stat |= 4;
    obj = player->player_obj;
    func_800EDD50_name_81(&obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    process = omAddPrcObj(func_800E1F94_name_81, 10, 0, 0);
    HuPrcSleep(10);

    HuAudFXPlay(0x1F7);
    effect = func_800D8010_name_81(0x1F, NULL);
    MBDMotionSet(effect, -1, 0);
    HuVecCopy3F(&effect->coords, &obj->coords);
    func_800FFAE0_name_81(D_80102BF0_name_81, 1);
    for (i = 0; i < 15; i++) {
        scaleY = (f32)i / 15.0f;
        scaleXZ = 1.0f - scaleY;
        scaleY += 1.0f;
        obj->scale.x = scaleXZ;
        obj->scale.y = scaleY;
        obj->scale.z = scaleXZ;
        func_800F3B94_name_81(D_80102BF0_name_81, &obj->scale);
        HuPrcVSleep();
    }
    obj->scale.x = 0.0f;
    obj->scale.y = 0.0f;
    obj->scale.z = 0.0f;
    func_800F3B94_name_81(D_80102BF0_name_81, &obj->scale);
    HuPrcVSleep();
    obj->flags &= ~2;
    MBDModelDispOff(obj);
    MBDModelKill(effect);

    player->clink = player->nlink = player->blink = D_80102BF4_name_81;
    player->cidx = D_80102BF6_name_81;
    player->nidx = D_80102BF6_name_81 + 1;
    player->bidx = D_80102BF6_name_81 - 1;
    player->nnidx = player->nnlink = -1;
    if (D_80102BF8_name_81 != -1) {
        player->blink = D_80102BF8_name_81;
    }
    if (D_80102BFA_name_81 != -1) {
        player->bidx = D_80102BFA_name_81;
    }
    player->rev = 0;
    D_800CE1D0_main = 0;
    func_800EB6C4_name_81(D_80102BF0_name_81, MBDMasuLinkMasuIdGet(player->clink, player->cidx));
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
    func_800EDF78_name_81();
    func_800EDDBC_name_81();
    func_800E890C_name_81(&obj->coords, 1);
    func_800FCF50_name_81(0, 1);
    func_800FCF50_name_81(1, 1);
    WipeCreateIn(0, 16);
    HuPrcSleep(16);
    omAddPrcObj(func_800E1FB8_name_81, 10, 0, 0);
    HuPrcSleep(10);

    HuAudFXPlay(0x1F8);
    obj->flags |= 2;
    MBDModelDispOn(obj);
    effect = func_800D8010_name_81(0x1F, NULL);
    MBDMotionSet(effect, -1, 0);
    HuVecCopy3F(&effect->coords, &obj->coords);
    func_800FFAE0_name_81(D_80102BF0_name_81, 1);
    for (i = 14; i >= 0; i--) {
        scaleY = (f32)i / 15.0f;
        scaleXZ = 1.0f - scaleY;
        scaleY += 1.0f;
        obj->scale.x = scaleXZ;
        obj->scale.y = scaleY;
        obj->scale.z = scaleXZ;
        func_800F3B94_name_81(D_80102BF0_name_81, &obj->scale);
        HuPrcVSleep();
    }
    MBDModelKill(effect);
    player->stat &= ~4;
    HuPrcSleep(15);
    func_800FC888_name_81(1);
    func_800E18C0_name_81();
    omDelPrcObj(NULL);
}

void func_800E24AC_name_81(s32 link, s32 idx, s32 backLink, s32 backIdx) {
    Process *parent;

    D_80102BF0_name_81 = MBDGetCurrentPlayerIndex();
    D_80102BF4_name_81 = link;
    D_80102BF6_name_81 = idx;
    D_80102BF8_name_81 = backLink;
    D_80102BFA_name_81 = backIdx;
    parent = HuPrcCurrentGet();
    HuPrcChildLink(parent, omAddPrcObj(func_800E209C_name_81, 0x1003, 0, 0));
    HuPrcChildWatch();
}

void func_800E2550_name_81(void) {
    GW_PLAYER *player;
    Object *obj;
    Object *effect;
    f32 scaleY;
    f32 scaleXZ;
    Object *partner;
    s32 i;

    player = MBDGetPlayerStruct(D_80102BF0_name_81);
    player->stat |= 4;
    obj = player->player_obj;

    HuAudFXPlay(0x1F7);
    effect = func_800D8010_name_81(0x1F, NULL);
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
        func_800F3B94_name_81(D_80102BF0_name_81, &obj->scale);
        HuPrcVSleep();
    }
    obj->scale.x = 0.0f;
    obj->scale.y = 0.0f;
    obj->scale.z = 0.0f;
    func_800F3B94_name_81(D_80102BF0_name_81, &obj->scale);
    HuPrcVSleep();
    MBDModelDispOff(obj);
    MBDModelKill(effect);

    HuVecCopy3F(&obj->coords, &D_80102C00_name_81);
    func_800EB7BC_name_81(&obj->rot);
    partner = MBDGetPlayerPartnerRef(D_80102BF0_name_81, PARTNER_FRONT);
    if (partner != NULL) {
        HuVecCopy3F(&partner->coords, &D_80102C0C_name_81);
        func_800EB7BC_name_81(&partner->rot);
    }
    partner = MBDGetPlayerPartnerRef(D_80102BF0_name_81, PARTNER_BACK);
    if (partner != NULL) {
        HuVecCopy3F(&partner->coords, &D_80102C18_name_81);
        func_800EB7BC_name_81(&partner->rot);
    }
    HuPrcVSleep();

    HuAudFXPlay(0x1F8);
    obj->flags |= 2;
    MBDModelDispOn(obj);
    effect = func_800D8010_name_81(0x1F, NULL);
    MBDMotionSet(effect, -1, 0);
    HuVecCopy3F(&effect->coords, &obj->coords);
    for (i = 14; i >= 0; i--) {
        scaleY = (f32)i / 15.0f;
        scaleXZ = 1.0f - scaleY;
        scaleY += 1.0f;
        obj->scale.x = scaleXZ;
        obj->scale.y = scaleY;
        obj->scale.z = scaleXZ;
        func_800F3B94_name_81(D_80102BF0_name_81, &obj->scale);
        HuPrcVSleep();
    }
    MBDModelKill(effect);
    player->stat &= ~4;
    HuPrcSleep(15);
    func_800E18C0_name_81();
    omDelPrcObj(NULL);
}

void func_800E27D4_name_81(s32 playerIndex, Vec *pos, Vec *pos1, Vec *pos2) {
    Process *parent;

    D_80102BF0_name_81 = playerIndex;
    HuVecCopy3F(&D_80102C00_name_81, pos);
    HuVecCopy3F(&D_80102C0C_name_81, pos1);
    HuVecCopy3F(&D_80102C18_name_81, pos2);
    parent = HuPrcCurrentGet();
    HuPrcChildLink(parent, omAddPrcObj(func_800E2550_name_81, 0x1003, 0, 0));
    HuPrcChildWatch();
}
