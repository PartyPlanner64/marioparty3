#include "common_duel.h"
#include "ovl_81.h"

typedef struct UnkD3450PrcData {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} UnkD3450PrcData; // sizeof 0x10

typedef struct UnkD3450PrcDataF {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} UnkD3450PrcDataF; // sizeof 0x10

typedef struct UnkD3450RotData {
    /* 0x00 */ Vec from;
    /* 0x0C */ Vec to;
    /* 0x18 */ Vec *out;
    /* 0x1C */ s32 time;
    /* 0x20 */ s32 spin;
} UnkD3450RotData; // sizeof 0x24

typedef struct UnkD3450MoveData {
    /* 0x00 */ Vec from;
    /* 0x0C */ Vec to;
    /* 0x18 */ Vec *out;
    /* 0x1C */ s32 time;
} UnkD3450MoveData; // sizeof 0x20

typedef struct UnkD3450StepData {
    /* 0x00 */ Vec from;
    /* 0x0C */ Vec to;
    /* 0x18 */ Vec *out;
    /* 0x1C */ f32 speed;
} UnkD3450StepData; // sizeof 0x20

s32 mbdMesSpeedTbl[] = { 5, 25, 60 };

void MBDMesWaitSet(s32);

void MBDMasuPosGet(s16 playerIdx, s16 spaceIdx, Vec *outCoords) {
    SpaceData *space = MBDMasuGet(spaceIdx);

    outCoords->x = space->coords.x;
    outCoords->y = space->coords.y;
    outCoords->z = space->coords.z;
}

void MBDPlayerPosMasuSet(s16 playerIdx, s16 spaceIdx) {
    MBDMasuPosGet(playerIdx, spaceIdx, &GwPlayer[playerIdx].player_obj->coords);
}

void MBDVecDirGet(Vec *arg0, Vec *arg1, Vec *arg2) {
    HuVecSubtract(arg2, arg1, arg0);
    MBDVecNormalize(arg2);
}

void MBDPlayerDirPosSet(s16 playerIdx, Vec *arg1) {
    Object *playerObj;

    playerObj = MBDPlayerGet(playerIdx)->player_obj;
    MBDVecDirGet(&playerObj->coords, arg1, &playerObj->rot);
}

void MBDModelDirMasuSet(Object *arg0, s16 arg1) {
    MBDVecDirGet(&arg0->coords, &MBDMasuGet(arg1)->coords, &arg0->rot);
}

void MBDVecForwardSet(Vec *out) {
    out->x = 0.0f;
    out->y = 0.0f;
    out->z = 1.0f;
}

void MBDPlayerForwardSet(s16 playerIdx) {
    MBDVecForwardSet(&MBDPlayerGet(playerIdx)->player_obj->rot);
}

void MBDModelBillboardSet(Object *obj) {
    Vec sp10;
    Vec sp20;

    HuVecSubtract(&sp10, &gCameraList->pos, &obj->coords);
    HuVecCopyXYZ(&sp20, sp10.x, 0.0f, sp10.z);
    obj->omObj1->rot.x = -MBDVecBetweenAngleGet(&sp10, &sp20);
    MBDVecDirGet(&obj->coords, &gCameraList->pos, &sp10);
    obj->omObj1->rot.y = MBDVecAngleGet(&sp10);
    obj->omObj1->rot.z = 0;
}

void MBDPlayerMasuSwap(s16 playerNoOne, s16 playerNoTwo) {
    GW_PLAYER *playerOne = MBDPlayerGet(playerNoOne);
    GW_PLAYER *playerTwo = MBDPlayerGet(playerNoTwo);
    u8 temp;
    u8 prevRev;

    temp = playerOne->clink;
    playerOne->clink = playerTwo->clink;
    playerTwo->clink = temp;
    temp = playerOne->cidx;
    playerOne->cidx = playerTwo->cidx;
    playerTwo->cidx = temp;
    temp = playerOne->nlink;
    playerOne->nlink = playerTwo->nlink;
    playerTwo->nlink = temp;
    temp = playerOne->nidx;
    playerOne->nidx = playerTwo->nidx;
    playerTwo->nidx = temp;
    temp = playerOne->blink;
    playerOne->blink = playerTwo->blink;
    playerTwo->blink = temp;
    temp = playerOne->bidx;
    playerOne->bidx = playerTwo->bidx;
    playerTwo->bidx = temp;
    temp = playerOne->nnlink;
    playerOne->nnlink = playerTwo->nnlink;
    playerTwo->nnlink = temp;
    temp = playerOne->nnidx;
    playerOne->nnidx = playerTwo->nnidx;
    playerTwo->nnidx = temp;
    prevRev = playerOne->rev;
    temp = playerTwo->rev;
    playerOne->rev = temp;
    playerTwo->rev = prevRev;
}

s16 MBDTotalStarGet(void) {
    s32 i;
    s32 totalStars = 0;

    for (i = 0; i < 2; i++) {
        totalStars += MBDPlayerGet(i)->star;
    }
    return totalStars;
}

s16 MBDRandCheck100(s8 percent) {
    return percent > ((rand8() & 0xFF) * 99 >> 8);
}

s16 MBDTurnRemain(void) {
    GW_SYSTEM *system = &GwSystem;

    return system->total_turns - system->current_turn + 1;
}

s32 MBDPadStkCheck(s16 arg0, f32 arg1) {
    Vec sp10;
    s32 var_v0;

    sp10.x = HuPadStkX[arg0];
    sp10.y = 0.0f;
    sp10.z = HuPadStkY[arg0];

    if (!(arg1 <= HuVecGetLength3F(&sp10))) {
        var_v0 = 0;
    } else {
        var_v0 = 1;
    }
    return var_v0;
}

void MBDMesSpeedSet(s16 arg0) {
    MBDMesWaitSet(mbdMesSpeedTbl[arg0]);
}

void MBDVecRotLerpProc(void) {
    UnkD3450RotData *data = HuPrcCurrentGet()->user_data;
    s32 time = data->time;
    f32 angle = MBDVecAngleGet(&data->from);
    f32 step = MBDVecAngleGet(&data->to) - angle;
    f32 timeF;

    if (step < -180.0f) {
        step += 360.0f;
    }
    if (step > 180.0f) {
        step -= 360.0f;
    }

    timeF = (f32)time;
    step = step / timeF;

    if (data->spin != 0) {
        if (step >= 0.0f) {
            step += 720.0f / timeF;
        } else {
            step -= 720.0f / timeF;
        }
    }

    for (angle = 0.0f; data->time != 0;) {
        HuVecCopy3F(data->out, &data->from);
        angle += step;
        MBDVecRotateY(data->out, angle);
        data->time--;
        HuPrcVSleep();
    }

    omDelPrcObj(NULL);
}

Process *MBDVecRotLerpCreate(Vec *from, Vec *to, Vec *out, s32 time) {
    Process *prc = omAddPrcObj(MBDVecRotLerpProc, 0x4002, 0, 0x80);
    UnkD3450RotData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450RotData));

    prc->user_data = data;
    HuVecCopyXYZ(&data->from, from->x, 0.0f, from->z);
    HuVecCopyXYZ(&data->to, to->x, 0.0f, to->z);
    data->out = out;
    data->time = time;
    data->spin = 0;
    return prc;
}

Process *MBDVecRotLerpSpinCreate(Vec *from, Vec *to, Vec *out, s32 time) {
    Process *prc = omAddPrcObj(MBDVecRotLerpProc, 0x4002, 0, 0x80);
    UnkD3450RotData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450RotData));

    prc->user_data = data;
    HuVecCopyXYZ(&data->from, from->x, 0.0f, from->z);
    HuVecCopyXYZ(&data->to, to->x, 0.0f, to->z);
    data->out = out;
    data->time = time;
    data->spin = 1;
    return prc;
}

Process *MBDPlayerRotMasuStart(s16 playerIndex, s32 time, s16 spaceIndex) {
    GW_PLAYER *player = MBDPlayerGet(playerIndex);
    Vec dir;

    HuVecSubtract(&dir, &MBDMasuGet(spaceIndex)->coords, &player->player_obj->coords);
    MBDVecNormalize(&dir);
    return MBDVecRotLerpCreate(&player->player_obj->rot, &dir, &player->player_obj->rot, time);
}

void MBDPlayerPosMoveProc(void) {
    UnkD3450MoveData *data = HuPrcCurrentGet()->user_data;
    s32 time = data->time;

    while (data->time) {
        HuVecSubtract(data->out, &data->to, &data->from);
        HuVecMulScalar(data->out, 1.0f - ((1.0f / (f32)time) * (f32)(data->time - 1)), data->out);
        HuVecAdd(data->out, data->out, &data->from);
        data->time--;
        HuPrcVSleep();
    }

    omDelPrcObj(NULL);
}

Process *MBDPlayerPosMoveCreate(Vec *from, Vec *to, Vec *out, s32 time) {
    Process *prc = omAddPrcObj(MBDPlayerPosMoveProc, 0x4002, 0, 0x50);
    UnkD3450MoveData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450MoveData));

    prc->user_data = data;
    data->from = *from;
    data->to = *to;
    data->out = out;
    data->time = time;
    return prc;
}

void MBDPlayerPosMoveSet(s16 playerIndex, s32 time) {
    Vec from;
    Vec to;
    Vec dir;
    Process *prc;
    GW_PLAYER *player = MBDPlayerGet(playerIndex);

    MBDMasuPosGet(playerIndex, MBDMasuLinkMasuIdGet(player->clink, player->cidx), &from);
    MBDMasuPosGet(playerIndex, MBDMasuLinkMasuIdGet(player->nlink, player->nidx), &to);
    if (!(player->rev & 4)) {
        MBDVecDirGet(&from, &to, &dir);
    } else {
        MBDVecDirGet(&to, &from, &dir);
    }
    MBDVecRotLerpCreate(&player->player_obj->rot, &dir, &player->player_obj->rot, time);
    prc = MBDPlayerPosMoveCreate(&from, &to, &player->player_obj->coords, time);
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWatch();
}

void MBDPlayerMoveStub(void) {
}

void MBDVecSpeedMoveProc(void) {
    UnkD3450StepData *data = HuPrcCurrentGet()->user_data;
    f32 speed = data->speed;
    Vec *to = &data->to;

    while (!(HuVecDistance(&data->from, to) < speed)) {
        HuVecSubtract(data->out, to, &data->from);
        MBDVecNormalize(data->out);
        HuVecMulScalar(data->out, speed, data->out);
        HuVecAdd(data->out, data->out, &data->from);
        HuVecCopy3F(&data->from, data->out);
        HuPrcVSleep();
    }

    HuVecCopy3F(data->out, &data->to);
    omDelPrcObj(NULL);
}

Process *MBDVecSpeedMoveCreate(Vec *from, Vec *to, Vec *out, f32 speed) {
    Process *prc = omAddPrcObj(MBDVecSpeedMoveProc, 0x4002, 0, 0x50);
    UnkD3450StepData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450StepData));

    prc->user_data = data;
    data->from = *from;
    data->to = *to;
    data->out = out;
    data->speed = speed;
    return prc;
}

void MBDVecSpeedMove2Proc(void) {
    UnkD3450StepData *data = HuPrcCurrentGet()->user_data;
    f32 speed = data->speed;
    s32 done = FALSE;

    while (TRUE) {
        HuVecSubtract(data->out, &data->to, &data->from);
        MBDVecNormalize(data->out);
        HuVecMulScalar(data->out, speed, data->out);
        HuVecAdd(data->out, data->out, &data->from);
        HuVecCopy3F(&data->from, data->out);
        if (HuVecDistance(&data->from, &data->to) < speed) {
            done = TRUE;
        }
        if (done) {
            break;
        }
        HuPrcVSleep();
    }

    omDelPrcObj(NULL);
}

Process *MBDVecSpeedMove2Create(Vec *from, Vec *to, Vec *out, f32 speed) {
    Process *prc = omAddPrcObj(MBDVecSpeedMove2Proc, 0x4002, 0, 0x50);
    UnkD3450StepData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450StepData));

    prc->user_data = data;
    data->from = *from;
    data->to = *to;
    data->out = out;
    data->speed = speed;
    return prc;
}

void MBDPlayerPosMoveSpeedSet(s16 playerIndex, f32 speed) {
    Vec from;
    Vec to;
    Process *prc;
    GW_PLAYER *player = MBDPlayerGet(playerIndex);

    MBDMasuPosGet(playerIndex, MBDMasuLinkMasuIdGet(player->clink, player->cidx), &from);
    MBDMasuPosGet(playerIndex, MBDMasuLinkMasuIdGet(player->nlink, player->nidx), &to);
    if (!(player->rev & 4)) {
        MBDVecDirGet(&from, &to, &player->player_obj->rot);
    } else {
        MBDVecDirGet(&to, &from, &player->player_obj->rot);
    }
    prc = MBDVecSpeedMoveCreate(&from, &to, &player->player_obj->coords, speed);
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWatch();
}

void MBDPlayerMoveVecGet(s16 playerIndex, Vec *cur, Vec *next, Vec *after, Vec *dir) {
    GW_PLAYER *player = MBDPlayerGet(playerIndex);
    s16 spaceIndex;

    MBDMasuPosGet(playerIndex, MBDMasuLinkMasuIdGet(player->clink, player->cidx), cur);
    MBDMasuPosGet(playerIndex, MBDMasuLinkMasuIdGet(player->nlink, player->nidx), next);
    if (player->nnlink >= 0 && player->nnidx >= 0) {
        MBDMasuPosGet(playerIndex, MBDMasuLinkMasuIdGet(player->nnlink, player->nnidx), after);
    } else {
        if (!(player->rev & FLAG_REV)) {
            spaceIndex = MBDMasuLinkMasuIdGet(player->nlink, player->nidx + 1);
        } else {
            spaceIndex = MBDMasuLinkMasuIdGet(player->nlink, player->nidx - 1);
        }
        MBDMasuPosGet(playerIndex, spaceIndex, after);
    }
    if (!(player->rev & 4)) {
        MBDVecDirGet(cur, next, dir);
    } else {
        MBDVecDirGet(next, cur, dir);
    }
}

void MBDPartnerFrontMoveProc(void) {
    UnkD3450PrcDataF *data = HuPrcCurrentGet()->user_data;
    s16 playerIndex = data->unk_00;
    f32 speed = data->unk_04;
    GW_PLAYER *player = MBDPlayerGet(playerIndex);
    Vec cur;
    Vec next;
    Vec after;
    Vec from;
    Vec to;
    Vec dir;
    Process *prc;
    Object *partner;
    f32 angle;

    MBDPlayerMoveVecGet(playerIndex, &cur, &next, &after, &dir);
    prc = HuPrcCurrentGet();
    partner = MBDPartnerObjGet(playerIndex, PARTNER_FRONT);
    if (!(player->rev & 4)) {
        HuVecCopy3F(&from, &partner->coords);
        HuVecCopy3F(&to, &next);
        HuVecCopy3F(&partner->rot, &dir);
    } else {
        MBDVecDirGet(&player->player_obj->coords, &partner->coords, &partner->rot);
        HuVecCopy3F(&from, &partner->coords);
        HuVecCopy3F(&to, &cur);
    }
    HuPrcChildLink(prc, MBDVecSpeedMove2Create(&from, &to, &partner->coords, speed));
    HuPrcChildWatch();

    if (player->rev & 4) {
        angle = MBDVecAngleGet(&dir);
    } else {
        MBDVecDirGet(&next, &after, &dir);
        angle = MBDVecAngleGet(&dir);
    }
    to.x = sindf(angle + 0.0f) * 12.0f + next.x;
    to.z = cosdf(angle + 0.0f) * 12.0f + next.z;
    to.y = next.y;
    HuVecCopy3F(&from, &partner->coords);
    HuVecCopy3F(&partner->rot, &dir);
    HuPrcChildLink(prc, MBDVecSpeedMoveCreate(&from, &to, &partner->coords, speed));
    HuPrcChildWatch();
    omDelPrcObj(NULL);
}

Process *MBDPartnerFrontMoveCreate(s16 playerIdx, f32 arg1) {
    Process *prc = omAddPrcObj(MBDPartnerFrontMoveProc, 0x4003, 0, 0x40);
    UnkD3450PrcDataF *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450PrcDataF));

    prc->user_data = data;
    data->unk_00 = playerIdx;
    data->unk_04 = arg1;
    return prc;
}

void MBDPartnerBackMoveProc(void) {
    UnkD3450PrcDataF *data = HuPrcCurrentGet()->user_data;
    s16 playerIndex = data->unk_00;
    f32 speed = data->unk_04;
    GW_PLAYER *player = MBDPlayerGet(playerIndex);
    Vec cur;
    Vec next;
    Vec after;
    Vec from;
    Vec to;
    Vec dir;
    Process *prc;
    Object *partner;
    f32 angle;

    MBDPlayerMoveVecGet(playerIndex, &cur, &next, &after, &dir);
    prc = HuPrcCurrentGet();
    partner = MBDPartnerObjGet(playerIndex, PARTNER_BACK);
    if (!(player->rev & 4)) {
        MBDVecDirGet(&partner->coords, &player->player_obj->coords, &partner->rot);
        HuVecCopy3F(&from, &partner->coords);
        HuVecCopy3F(&to, &cur);
    } else {
        HuVecCopy3F(&partner->rot, &dir);
        HuVecCopy3F(&from, &partner->coords);
        HuVecCopy3F(&to, &next);
    }
    HuPrcChildLink(prc, MBDVecSpeedMove2Create(&from, &to, &partner->coords, speed));
    HuPrcChildWatch();

    if (!(player->rev & 4)) {
        angle = MBDVecAngleGet(&dir);
    } else {
        MBDVecDirGet(&after, &next, &dir);
        angle = MBDVecAngleGet(&dir);
    }
    to.x = sindf(angle + 180.0f) * 12.0f + next.x;
    to.z = cosdf(angle + 180.0f) * 12.0f + next.z;
    to.y = next.y;
    HuVecCopy3F(&from, &partner->coords);
    HuVecCopy3F(&partner->rot, &dir);
    HuPrcChildLink(prc, MBDVecSpeedMoveCreate(&from, &to, &partner->coords, speed));
    HuPrcChildWatch();
    omDelPrcObj(NULL);
}

Process *MBDPartnerBackMoveCreate(s16 playerIdx, f32 arg1) {
    Process *prc = omAddPrcObj(MBDPartnerBackMoveProc, 0x4003, 0, 0x40);
    UnkD3450PrcDataF *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450PrcDataF));

    prc->user_data = data;
    data->unk_00 = playerIdx;
    data->unk_04 = arg1;
    return prc;
}

void MBDPlayerPartnerMoveExec(s16 playerIndex, f32 speed) {
    GW_PLAYER *player = MBDPlayerGet(playerIndex);
    Process *prc = HuPrcCurrentGet();

    if (player->stats.partners.frontID != PARTNER_NONE) {
        HuPrcChildLink(prc, MBDPartnerFrontMoveCreate(playerIndex, speed));
    }
    if (player->stats.partners.backID != PARTNER_NONE) {
        HuPrcChildLink(prc, MBDPartnerBackMoveCreate(playerIndex, speed));
    }
    MBDPlayerPosMoveSpeedSet(playerIndex, speed);
    player->nnlink = -1;
    player->nnidx = -1;
}

void MBDMoveMasuSet(s16 playerIdx, s16 nlink, s16 nidx) {
    GW_PLAYER *player = MBDPlayerGet(playerIdx);

    if (nlink >= 0) {
        player->clink = nlink;
        player->nlink = nlink;
        player->blink = nlink;
    }
    if (nidx >= 0) {
        player->cidx = nidx;
        player->nidx = nidx + 1;
        player->bidx = nidx - 1;
    }
}

void MBDMoveNextMasuSet(s16 playerIdx, s16 nlink, s16 nidx) {
    GW_PLAYER *player = MBDPlayerGet(playerIdx);

    if (nlink >= 0) {
        player->nlink = nlink;
    }
    if (nidx >= 0) {
        player->nidx = nidx;
    }
}

void MBDPlayerRevOn(void) {
    GW_PLAYER *player = MBDPlayerGet(CUR_PLAYER);

    player->rev |= FLAG_REV;
}

void MBDPlayerRevOff(void) {
    GW_PLAYER *player = MBDPlayerGet(CUR_PLAYER);

    player->rev &= ~FLAG_REV;
}

void MBDPlayerDirNextSet(s32 playerIndex) {
    Vec from;
    Vec to;
    GW_PLAYER *player = MBDPlayerGet(playerIndex);
    s32 space;

    space = MBDMasuLinkMasuIdGet(player->clink, player->cidx);
    MBDMasuPosGet(playerIndex, space, &from);
    space = MBDMasuLinkMasuIdGet(player->nlink, player->nidx);
    MBDMasuPosGet(playerIndex, space, &to);
    if (!(player->rev & 4)) {
        MBDVecDirGet(&from, &to, &player->player_obj->rot);
    } else {
        MBDVecDirGet(&to, &from, &player->player_obj->rot);
    }
}

void MBDPartnerOfsGet(s32 playerIndex, Vec *frontOffset, Vec *backOffset) {
    Vec cur;
    Vec next;
    Vec back;
    Vec dir;
    f32 angle;
    GW_PLAYER *player = MBDPlayerGet(playerIndex);

    MBDPlayerMoveVecGet(playerIndex, &cur, &next, &back, &dir);
    MBDMasuPosGet(playerIndex, MBDMasuLinkMasuIdGet(player->blink, player->bidx), &back);
    if (!(player->rev & 4)) {
        MBDVecDirGet(&cur, &next, &dir);
        angle = MBDVecAngleGet(&dir);
        frontOffset->x = sindf(angle + 0.0f) * 12.0f;
        frontOffset->z = cosdf(angle + 0.0f) * 12.0f;
        frontOffset->y = 0.0f;
        MBDVecDirGet(&back, &cur, &dir);
        angle = MBDVecAngleGet(&dir);
        backOffset->x = sindf(angle + 180.0f) * 12.0f;
        backOffset->z = cosdf(angle + 180.0f) * 12.0f;
        backOffset->y = 0.0f;
    } else {
        MBDVecDirGet(&cur, &back, &dir);
        angle = MBDVecAngleGet(&dir);
        frontOffset->x = sindf(angle + 0.0f) * 12.0f;
        frontOffset->z = cosdf(angle + 0.0f) * 12.0f;
        frontOffset->y = 0.0f;
        MBDVecDirGet(&next, &cur, &dir);
        angle = MBDVecAngleGet(&dir);
        backOffset->x = sindf(angle + 180.0f) * 12.0f;
        backOffset->z = cosdf(angle + 180.0f) * 12.0f;
        backOffset->y = 0.0f;
    }
}

void MBDPartnerDirGet(s32 playerIndex, Vec *frontDir, Vec *backDir) {
    Vec cur;
    Vec next;
    Vec back;
    Vec dir;
    GW_PLAYER *player = MBDPlayerGet(playerIndex);

    MBDPlayerMoveVecGet(playerIndex, &cur, &next, &back, &dir);
    MBDMasuPosGet(playerIndex, MBDMasuLinkMasuIdGet(player->blink, player->bidx), &back);
    if (!(player->rev & 4)) {
        MBDVecDirGet(&cur, &next, frontDir);
        MBDVecDirGet(&back, &cur, backDir);
    } else {
        MBDVecDirGet(&cur, &back, frontDir);
        MBDVecDirGet(&next, &cur, backDir);
    }
}

void MBDPartnerPosFix(s32 playerIndex) {
    Vec sp10;
    Vec sp20;
    GW_PLAYER *player = MBDPlayerGet(playerIndex);
    Object *partner;

    MBDPartnerOfsGet(playerIndex, &sp10, &sp20);

    if (player->stats.partners.frontID != PARTNER_NONE) {
        partner = MBDPartnerObjGet(playerIndex, PARTNER_FRONT);
        HuVecCopy3F(&partner->coords, &player->player_obj->coords);
        HuVecAdd(&partner->coords, &partner->coords, &sp10);
        MBDVecNormalize(&sp10);
        HuVecCopy3F(&partner->rot, &sp10);
    }

    if (player->stats.partners.backID != PARTNER_NONE) {
        partner = MBDPartnerObjGet(playerIndex, PARTNER_BACK);
        HuVecCopy3F(&partner->coords, &player->player_obj->coords);
        HuVecAdd(&partner->coords, &partner->coords, &sp20);
        MBDVecNormalize(&sp20);
        MBDVecRotateY(&sp20, 180.0f);
        HuVecCopy3F(&partner->rot, &sp20);
    }
}

void MBDPartnerFrontJumpProc(void) {
    UnkD3450PrcData *data = HuPrcCurrentGet()->user_data;
    s32 time = data->unk_04;
    s16 playerIndex = data->unk_00;
    Vec cur;
    Vec next;
    Vec after;
    Vec from;
    Vec to;
    Vec dir;
    Process *prc;
    Object *partner;
    f32 angle;

    MBDPlayerMoveVecGet(playerIndex, &cur, &next, &after, &dir);
    prc = HuPrcCurrentGet();
    partner = MBDPartnerObjGet(playerIndex, PARTNER_FRONT);
    MBDVecDirGet(&cur, &next, &dir);
    angle = MBDVecAngleGet(&dir) + 0.0f;
    to.x = sindf(angle) * 12.0f + cur.x;
    to.z = cosdf(angle) * 12.0f + cur.z;
    to.y = cur.y;
    HuVecCopy3F(&from, &partner->coords);
    HuVecCopy3F(&partner->rot, &dir);
    HuPrcChildLink(prc, MBDPlayerPosMoveCreate(&from, &to, &partner->coords, time));
    MBDModelJumpSet(partner, 5.0f, -5.0f / (time / 2));
    HuPrcChildWatch();
    omDelPrcObj(NULL);
}

Process *MBDPartnerFrontJumpCreate(s16 playerIdx, s32 arg) {
    Process *prc = omAddPrcObj(MBDPartnerFrontJumpProc, 0x4003, 0, 0x40);
    UnkD3450PrcData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450PrcData));

    prc->user_data = data;
    data->unk_00 = playerIdx;
    data->unk_04 = arg;
    return prc;
}

void MBDPartnerFrontWalkProc(void) {
    UnkD3450PrcDataF *data = HuPrcCurrentGet()->user_data;
    s16 playerIndex = data->unk_00;
    f32 speed = data->unk_04;
    Vec cur;
    Vec next;
    Vec after;
    Vec from;
    Vec to;
    Vec dir;
    Process *prc;
    Object *partner;
    f32 angle;

    MBDPlayerMoveVecGet(playerIndex, &cur, &next, &after, &dir);
    prc = HuPrcCurrentGet();
    partner = MBDPartnerObjGet(playerIndex, PARTNER_FRONT);
    MBDVecDirGet(&cur, &next, &dir);
    angle = MBDVecAngleGet(&dir) + 0.0f;
    to.x = sindf(angle) * 12.0f + cur.x;
    to.z = cosdf(angle) * 12.0f + cur.z;
    to.y = cur.y;
    HuVecCopy3F(&from, &partner->coords);
    HuVecCopy3F(&partner->rot, &dir);
    HuPrcChildLink(prc, MBDVecSpeedMoveCreate(&from, &to, &partner->coords, speed));
    HuPrcChildWatch();
    omDelPrcObj(NULL);
}

Process *MBDPartnerFrontWalkCreate(s16 playerIdx, f32 arg1) {
    Process *prc = omAddPrcObj(MBDPartnerFrontWalkProc, 0x4003, 0, 0x40);
    UnkD3450PrcDataF *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450PrcDataF));

    prc->user_data = data;
    data->unk_00 = playerIdx;
    data->unk_04 = arg1;
    return prc;
}

Process *MBDPartnerFrontFollowCreate(s32 playerIdx, s32 arg) {
    Process *prc = NULL;

    if (MBDPlayerGet(playerIdx)->stats.prize.gamblePrize != -1) {
        if (arg != 0) {
            prc = MBDPartnerFrontJumpCreate(playerIdx, 0xF);
        } else {
            prc = MBDPartnerFrontWalkCreate(playerIdx, 3.0f);
        }
    }
    return prc;
}

void MBDPartnerFrontFollowExec(s32 playerIndex) {
    Process *prc;

    if (GwSystem.current_board_index == DUEL_BOARD_BLOWHARD) {
        prc = MBDPartnerFrontFollowCreate(playerIndex, 1);
    } else {
        prc = MBDPartnerFrontFollowCreate(playerIndex, 0);
    }

    if (prc != NULL) {
        HuPrcChildLink(HuPrcCurrentGet(), prc);
        HuPrcChildWatch();
    }
}

void MBDPartnerBackJumpProc(void) {
    UnkD3450PrcData *data = HuPrcCurrentGet()->user_data;
    s32 time = data->unk_04;
    s16 playerIndex = data->unk_00;
    GW_PLAYER *player = MBDPlayerGet(playerIndex);
    Vec cur;
    Vec next;
    Vec back;
    Vec from;
    Vec to;
    Vec dir;
    Process *prc;
    Object *partner;
    f32 angle;

    MBDPlayerMoveVecGet(playerIndex, &cur, &next, &back, &dir);
    MBDMasuPosGet(playerIndex, MBDMasuLinkMasuIdGet(player->blink, player->bidx), &back);
    prc = HuPrcCurrentGet();
    partner = MBDPartnerObjGet(playerIndex, PARTNER_BACK);
    MBDVecDirGet(&back, &cur, &dir);
    angle = MBDVecAngleGet(&dir) + 180.0f;
    to.x = sindf(angle) * 12.0f + cur.x;
    to.z = cosdf(angle) * 12.0f + cur.z;
    to.y = cur.y;
    HuVecCopy3F(&from, &partner->coords);
    HuVecCopy3F(&partner->rot, &dir);
    HuPrcChildLink(prc, MBDPlayerPosMoveCreate(&from, &to, &partner->coords, time));
    MBDModelJumpSet(partner, 5.0f, -5.0f / (time / 2));
    HuPrcChildWatch();
    omDelPrcObj(NULL);
}

Process *MBDPartnerBackJumpCreate(s16 playerIdx, s32 arg) {
    Process *prc = omAddPrcObj(MBDPartnerBackJumpProc, 0x4003, 0, 0x40);
    UnkD3450PrcData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450PrcData));

    prc->user_data = data;
    data->unk_00 = playerIdx;
    data->unk_04 = arg;
    return prc;
}

void MBDPartnerBackWalkProc(void) {
    UnkD3450PrcDataF *data = HuPrcCurrentGet()->user_data;
    s16 playerIndex = data->unk_00;
    f32 speed = data->unk_04;
    GW_PLAYER *player = MBDPlayerGet(playerIndex);
    Vec cur;
    Vec next;
    Vec back;
    Vec from;
    Vec to;
    Vec dir;
    Process *prc;
    Object *partner;
    f32 angle;

    MBDPlayerMoveVecGet(playerIndex, &cur, &next, &back, &dir);
    MBDMasuPosGet(playerIndex, MBDMasuLinkMasuIdGet(player->blink, player->bidx), &back);
    prc = HuPrcCurrentGet();
    partner = MBDPartnerObjGet(playerIndex, PARTNER_BACK);
    MBDVecDirGet(&back, &cur, &dir);
    angle = MBDVecAngleGet(&dir) + 180.0f;
    to.x = sindf(angle) * 12.0f + cur.x;
    to.z = cosdf(angle) * 12.0f + cur.z;
    to.y = cur.y;
    HuVecCopy3F(&from, &partner->coords);
    HuVecCopy3F(&partner->rot, &dir);
    HuPrcChildLink(prc, MBDVecSpeedMoveCreate(&from, &to, &partner->coords, speed));
    HuPrcChildWatch();
    omDelPrcObj(NULL);
}

Process *MBDPartnerBackWalkCreate(s16 playerIdx, f32 arg1) {
    Process *prc = omAddPrcObj(MBDPartnerBackWalkProc, 0x4003, 0, 0x40);
    UnkD3450PrcDataF *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450PrcDataF));

    prc->user_data = data;
    data->unk_00 = playerIdx;
    data->unk_04 = arg1;
    return prc;
}

Process *MBDPartnerBackFollowCreate(s32 playerIdx, s32 arg) {
    Process *prc = NULL;

    if (MBDPlayerGet(playerIdx)->stats.prize.duelNo != -1) {
        if (arg != 0) {
            prc = MBDPartnerBackJumpCreate(playerIdx, 0xF);
        } else {
            prc = MBDPartnerBackWalkCreate(playerIdx, 3.0f);
        }
    }
    return prc;
}

void MBDPartnerBackFollowExec(s32 playerIndex) {
    Process *prc;

    if (GwSystem.current_board_index == DUEL_BOARD_BLOWHARD) {
        prc = MBDPartnerBackFollowCreate(playerIndex, 1);
    } else {
        prc = MBDPartnerBackFollowCreate(playerIndex, 0);
    }
    if (prc != NULL) {
        HuPrcChildLink(HuPrcCurrentGet(), prc);
        HuPrcChildWatch();
    }
}
