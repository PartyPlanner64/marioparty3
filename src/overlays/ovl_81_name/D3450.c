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

extern s32 D_801011E0_name_81[];

void func_800EED30_name_81(s32);

void func_800EB680_name_81(s16 playerIdx, s16 spaceIdx, Vec *outCoords) {
    SpaceData *space = MBDMasuGet(spaceIdx);

    outCoords->x = space->coords.x;
    outCoords->y = space->coords.y;
    outCoords->z = space->coords.z;
}

void func_800EB6C4_name_81(s16 playerIdx, s16 spaceIdx) {
    func_800EB680_name_81(playerIdx, spaceIdx, &GwPlayer[playerIdx].player_obj->coords);
}

void MBDVecDirGet(Vec *arg0, Vec *arg1, Vec *arg2) {
    HuVecSubtract(arg2, arg1, arg0);
    MBDVecNormalize(arg2);
}

void func_800EB740_name_81(s16 playerIdx, Vec *arg1) {
    Object *playerObj;

    playerObj = MBDGetPlayerStruct(playerIdx)->player_obj;
    MBDVecDirGet(&playerObj->coords, arg1, &playerObj->rot);
}

void func_800EB780_name_81(Object *arg0, s16 arg1) {
    MBDVecDirGet(&arg0->coords, &MBDMasuGet(arg1)->coords, &arg0->rot);
}

void func_800EB7BC_name_81(Vec *out) {
    out->x = 0.0f;
    out->y = 0.0f;
    out->z = 1.0f;
}

void func_800EB7D8_name_81(s16 playerIdx) {
    func_800EB7BC_name_81(&MBDGetPlayerStruct(playerIdx)->player_obj->rot);
}

void func_800EB804_name_81(Object *obj) {
    Vec sp10;
    Vec sp20;

    HuVecSubtract(&sp10, &gCameraList->pos, &obj->coords);
    HuVecCopyXYZ(&sp20, sp10.x, 0.0f, sp10.z);
    obj->omObj1->rot.x = -func_800D7CEC_name_81(&sp10, &sp20);
    MBDVecDirGet(&obj->coords, &gCameraList->pos, &sp10);
    obj->omObj1->rot.y = MBDVecAngleGet(&sp10);
    obj->omObj1->rot.z = 0;
}

void func_800EB8B0_name_81(s16 playerNoOne, s16 playerNoTwo) {
    GW_PLAYER *playerOne = MBDGetPlayerStruct(playerNoOne);
    GW_PLAYER *playerTwo = MBDGetPlayerStruct(playerNoTwo);
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

s16 func_800EB984_name_81(void) {
    s32 i;
    s32 totalStars = 0;

    for (i = 0; i < 2; i++) {
        totalStars += MBDGetPlayerStruct(i)->star;
    }
    return totalStars;
}

s16 func_800EB9D4_name_81(s8 percent) {
    return percent > ((rand8() & 0xFF) * 99 >> 8);
}

s16 func_800EBA1C_name_81(void) {
    GW_SYSTEM *system = &GwSystem;

    return system->total_turns - system->current_turn + 1;
}

s32 func_800EBA50_name_81(s16 arg0, f32 arg1) {
    Vec sp10;
    s32 var_v0;

    sp10.x = D_800CBB6E_main[arg0];
    sp10.y = 0.0f;
    sp10.z = D_800D20A1_main[arg0];

    if (!(arg1 <= HuVecGetLength3F(&sp10))) {
        var_v0 = 0;
    } else {
        var_v0 = 1;
    }
    return var_v0;
}

void func_800EBAD4_name_81(s16 arg0) {
    func_800EED30_name_81(D_801011E0_name_81[arg0]);
}

void func_800EBB00_name_81(void) {
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

Process *func_800EBC60_name_81(Vec *from, Vec *to, Vec *out, s32 time) {
    Process *prc = omAddPrcObj(func_800EBB00_name_81, 0x4002, 0, 0x80);
    UnkD3450RotData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450RotData));

    prc->user_data = data;
    HuVecCopyXYZ(&data->from, from->x, 0.0f, from->z);
    HuVecCopyXYZ(&data->to, to->x, 0.0f, to->z);
    data->out = out;
    data->time = time;
    data->spin = 0;
    return prc;
}

Process *func_800EBD1C_name_81(Vec *from, Vec *to, Vec *out, s32 time) {
    Process *prc = omAddPrcObj(func_800EBB00_name_81, 0x4002, 0, 0x80);
    UnkD3450RotData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450RotData));

    prc->user_data = data;
    HuVecCopyXYZ(&data->from, from->x, 0.0f, from->z);
    HuVecCopyXYZ(&data->to, to->x, 0.0f, to->z);
    data->out = out;
    data->time = time;
    data->spin = 1;
    return prc;
}

Process *func_800EBDDC_name_81(s16 playerIndex, s32 time, s16 spaceIndex) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);
    Vec dir;

    HuVecSubtract(&dir, &MBDMasuGet(spaceIndex)->coords, &player->player_obj->coords);
    MBDVecNormalize(&dir);
    return func_800EBC60_name_81(&player->player_obj->rot, &dir, &player->player_obj->rot, time);
}

void func_800EBE60_name_81(void) {
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

Process *func_800EBF2C_name_81(Vec *from, Vec *to, Vec *out, s32 time) {
    Process *prc = omAddPrcObj(func_800EBE60_name_81, 0x4002, 0, 0x50);
    UnkD3450MoveData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450MoveData));

    prc->user_data = data;
    data->from = *from;
    data->to = *to;
    data->out = out;
    data->time = time;
    return prc;
}

void func_800EBFE0_name_81(s16 playerIndex, s32 time) {
    Vec from;
    Vec to;
    Vec dir;
    Process *prc;
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);

    func_800EB680_name_81(playerIndex, MBDMasuLinkMasuIdGet(player->clink, player->cidx), &from);
    func_800EB680_name_81(playerIndex, MBDMasuLinkMasuIdGet(player->nlink, player->nidx), &to);
    if (!(player->rev & 4)) {
        MBDVecDirGet(&from, &to, &dir);
    } else {
        MBDVecDirGet(&to, &from, &dir);
    }
    func_800EBC60_name_81(&player->player_obj->rot, &dir, &player->player_obj->rot, time);
    prc = func_800EBF2C_name_81(&from, &to, &player->player_obj->coords, time);
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWatch();
}

void func_800EC114_name_81(void) {
}

void func_800EC11C_name_81(void) {
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

Process *func_800EC1E4_name_81(Vec *from, Vec *to, Vec *out, f32 speed) {
    Process *prc = omAddPrcObj(func_800EC11C_name_81, 0x4002, 0, 0x50);
    UnkD3450StepData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450StepData));

    prc->user_data = data;
    data->from = *from;
    data->to = *to;
    data->out = out;
    data->speed = speed;
    return prc;
}

void func_800EC298_name_81(void) {
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

Process *func_800EC36C_name_81(Vec *from, Vec *to, Vec *out, f32 speed) {
    Process *prc = omAddPrcObj(func_800EC298_name_81, 0x4002, 0, 0x50);
    UnkD3450StepData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450StepData));

    prc->user_data = data;
    data->from = *from;
    data->to = *to;
    data->out = out;
    data->speed = speed;
    return prc;
}

void func_800EC420_name_81(s16 playerIndex, f32 speed) {
    Vec from;
    Vec to;
    Process *prc;
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);

    func_800EB680_name_81(playerIndex, MBDMasuLinkMasuIdGet(player->clink, player->cidx), &from);
    func_800EB680_name_81(playerIndex, MBDMasuLinkMasuIdGet(player->nlink, player->nidx), &to);
    if (!(player->rev & 4)) {
        MBDVecDirGet(&from, &to, &player->player_obj->rot);
    } else {
        MBDVecDirGet(&to, &from, &player->player_obj->rot);
    }
    prc = func_800EC1E4_name_81(&from, &to, &player->player_obj->coords, speed);
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWatch();
}

void func_800EC548_name_81(s16 playerIndex, Vec *cur, Vec *next, Vec *after, Vec *dir) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);
    s16 spaceIndex;

    func_800EB680_name_81(playerIndex, MBDMasuLinkMasuIdGet(player->clink, player->cidx), cur);
    func_800EB680_name_81(playerIndex, MBDMasuLinkMasuIdGet(player->nlink, player->nidx), next);
    if (player->nnlink >= 0 && player->nnidx >= 0) {
        func_800EB680_name_81(playerIndex, MBDMasuLinkMasuIdGet(player->nnlink, player->nnidx), after);
    } else {
        if (!(player->rev & FLAG_REV)) {
            spaceIndex = MBDMasuLinkMasuIdGet(player->nlink, player->nidx + 1);
        } else {
            spaceIndex = MBDMasuLinkMasuIdGet(player->nlink, player->nidx - 1);
        }
        func_800EB680_name_81(playerIndex, spaceIndex, after);
    }
    if (!(player->rev & 4)) {
        MBDVecDirGet(cur, next, dir);
    } else {
        MBDVecDirGet(next, cur, dir);
    }
}

void func_800EC6F4_name_81(void) {
    UnkD3450PrcDataF *data = HuPrcCurrentGet()->user_data;
    s16 playerIndex = data->unk_00;
    f32 speed = data->unk_04;
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);
    Vec cur;
    Vec next;
    Vec after;
    Vec from;
    Vec to;
    Vec dir;
    Process *prc;
    Object *partner;
    f32 angle;

    func_800EC548_name_81(playerIndex, &cur, &next, &after, &dir);
    prc = HuPrcCurrentGet();
    partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_FRONT);
    if (!(player->rev & 4)) {
        HuVecCopy3F(&from, &partner->coords);
        HuVecCopy3F(&to, &next);
        HuVecCopy3F(&partner->rot, &dir);
    } else {
        MBDVecDirGet(&player->player_obj->coords, &partner->coords, &partner->rot);
        HuVecCopy3F(&from, &partner->coords);
        HuVecCopy3F(&to, &cur);
    }
    HuPrcChildLink(prc, func_800EC36C_name_81(&from, &to, &partner->coords, speed));
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
    HuPrcChildLink(prc, func_800EC1E4_name_81(&from, &to, &partner->coords, speed));
    HuPrcChildWatch();
    omDelPrcObj(NULL);
}

Process *func_800EC91C_name_81(s16 playerIdx, f32 arg1) {
    Process *prc = omAddPrcObj(func_800EC6F4_name_81, 0x4003, 0, 0x40);
    UnkD3450PrcDataF *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450PrcDataF));

    prc->user_data = data;
    data->unk_00 = playerIdx;
    data->unk_04 = arg1;
    return prc;
}

void func_800EC99C_name_81(void) {
    UnkD3450PrcDataF *data = HuPrcCurrentGet()->user_data;
    s16 playerIndex = data->unk_00;
    f32 speed = data->unk_04;
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);
    Vec cur;
    Vec next;
    Vec after;
    Vec from;
    Vec to;
    Vec dir;
    Process *prc;
    Object *partner;
    f32 angle;

    func_800EC548_name_81(playerIndex, &cur, &next, &after, &dir);
    prc = HuPrcCurrentGet();
    partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_BACK);
    if (!(player->rev & 4)) {
        MBDVecDirGet(&partner->coords, &player->player_obj->coords, &partner->rot);
        HuVecCopy3F(&from, &partner->coords);
        HuVecCopy3F(&to, &cur);
    } else {
        HuVecCopy3F(&partner->rot, &dir);
        HuVecCopy3F(&from, &partner->coords);
        HuVecCopy3F(&to, &next);
    }
    HuPrcChildLink(prc, func_800EC36C_name_81(&from, &to, &partner->coords, speed));
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
    HuPrcChildLink(prc, func_800EC1E4_name_81(&from, &to, &partner->coords, speed));
    HuPrcChildWatch();
    omDelPrcObj(NULL);
}

Process *func_800ECBB4_name_81(s16 playerIdx, f32 arg1) {
    Process *prc = omAddPrcObj(func_800EC99C_name_81, 0x4003, 0, 0x40);
    UnkD3450PrcDataF *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450PrcDataF));

    prc->user_data = data;
    data->unk_00 = playerIdx;
    data->unk_04 = arg1;
    return prc;
}

void func_800ECC34_name_81(s16 playerIndex, f32 speed) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);
    Process *prc = HuPrcCurrentGet();

    if (player->stats.partners.frontID != PARTNER_NONE) {
        HuPrcChildLink(prc, func_800EC91C_name_81(playerIndex, speed));
    }
    if (player->stats.partners.backID != PARTNER_NONE) {
        HuPrcChildLink(prc, func_800ECBB4_name_81(playerIndex, speed));
    }
    func_800EC420_name_81(playerIndex, speed);
    player->nnlink = -1;
    player->nnidx = -1;
}

void func_800ECD0C_name_81(s16 playerIdx, s16 nlink, s16 nidx) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerIdx);

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

void func_800ECD88_name_81(s16 playerIdx, s16 nlink, s16 nidx) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerIdx);

    if (nlink >= 0) {
        player->nlink = nlink;
    }
    if (nidx >= 0) {
        player->nidx = nidx;
    }
}

void func_800ECDE8_name_81(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    player->rev |= FLAG_REV;
}

void func_800ECE10_name_81(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    player->rev &= ~FLAG_REV;
}

void func_800ECE38_name_81(s32 playerIndex) {
    Vec from;
    Vec to;
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);
    s32 space;

    space = MBDMasuLinkMasuIdGet(player->clink, player->cidx);
    func_800EB680_name_81(playerIndex, space, &from);
    space = MBDMasuLinkMasuIdGet(player->nlink, player->nidx);
    func_800EB680_name_81(playerIndex, space, &to);
    if (!(player->rev & 4)) {
        MBDVecDirGet(&from, &to, &player->player_obj->rot);
    } else {
        MBDVecDirGet(&to, &from, &player->player_obj->rot);
    }
}

void func_800ECF1C_name_81(s32 playerIndex, Vec *frontOffset, Vec *backOffset) {
    Vec cur;
    Vec next;
    Vec back;
    Vec dir;
    f32 angle;
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);

    func_800EC548_name_81(playerIndex, &cur, &next, &back, &dir);
    func_800EB680_name_81(playerIndex, MBDMasuLinkMasuIdGet(player->blink, player->bidx), &back);
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

void func_800ED118_name_81(s32 playerIndex, Vec *frontDir, Vec *backDir) {
    Vec cur;
    Vec next;
    Vec back;
    Vec dir;
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);

    func_800EC548_name_81(playerIndex, &cur, &next, &back, &dir);
    func_800EB680_name_81(playerIndex, MBDMasuLinkMasuIdGet(player->blink, player->bidx), &back);
    if (!(player->rev & 4)) {
        MBDVecDirGet(&cur, &next, frontDir);
        MBDVecDirGet(&back, &cur, backDir);
    } else {
        MBDVecDirGet(&cur, &back, frontDir);
        MBDVecDirGet(&next, &cur, backDir);
    }
}

void func_800ED214_name_81(s32 playerIndex) {
    Vec sp10;
    Vec sp20;
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);
    Object *partner;

    func_800ECF1C_name_81(playerIndex, &sp10, &sp20);

    if (player->stats.partners.frontID != PARTNER_NONE) {
        partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_FRONT);
        HuVecCopy3F(&partner->coords, &player->player_obj->coords);
        HuVecAdd(&partner->coords, &partner->coords, &sp10);
        MBDVecNormalize(&sp10);
        HuVecCopy3F(&partner->rot, &sp10);
    }

    if (player->stats.partners.backID != PARTNER_NONE) {
        partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_BACK);
        HuVecCopy3F(&partner->coords, &player->player_obj->coords);
        HuVecAdd(&partner->coords, &partner->coords, &sp20);
        MBDVecNormalize(&sp20);
        MBDVecRotateY(&sp20, 180.0f);
        HuVecCopy3F(&partner->rot, &sp20);
    }
}

void func_800ED31C_name_81(void) {
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

    func_800EC548_name_81(playerIndex, &cur, &next, &after, &dir);
    prc = HuPrcCurrentGet();
    partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_FRONT);
    MBDVecDirGet(&cur, &next, &dir);
    angle = MBDVecAngleGet(&dir) + 0.0f;
    to.x = sindf(angle) * 12.0f + cur.x;
    to.z = cosdf(angle) * 12.0f + cur.z;
    to.y = cur.y;
    HuVecCopy3F(&from, &partner->coords);
    HuVecCopy3F(&partner->rot, &dir);
    HuPrcChildLink(prc, func_800EBF2C_name_81(&from, &to, &partner->coords, time));
    func_800EF7C8_name_81(partner, 5.0f, -5.0f / (time / 2));
    HuPrcChildWatch();
    omDelPrcObj(NULL);
}

Process *func_800ED4AC_name_81(s16 playerIdx, s32 arg) {
    Process *prc = omAddPrcObj(func_800ED31C_name_81, 0x4003, 0, 0x40);
    UnkD3450PrcData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450PrcData));

    prc->user_data = data;
    data->unk_00 = playerIdx;
    data->unk_04 = arg;
    return prc;
}

void func_800ED520_name_81(void) {
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

    func_800EC548_name_81(playerIndex, &cur, &next, &after, &dir);
    prc = HuPrcCurrentGet();
    partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_FRONT);
    MBDVecDirGet(&cur, &next, &dir);
    angle = MBDVecAngleGet(&dir) + 0.0f;
    to.x = sindf(angle) * 12.0f + cur.x;
    to.z = cosdf(angle) * 12.0f + cur.z;
    to.y = cur.y;
    HuVecCopy3F(&from, &partner->coords);
    HuVecCopy3F(&partner->rot, &dir);
    HuPrcChildLink(prc, func_800EC1E4_name_81(&from, &to, &partner->coords, speed));
    HuPrcChildWatch();
    omDelPrcObj(NULL);
}

Process *func_800ED68C_name_81(s16 playerIdx, f32 arg1) {
    Process *prc = omAddPrcObj(func_800ED520_name_81, 0x4003, 0, 0x40);
    UnkD3450PrcDataF *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450PrcDataF));

    prc->user_data = data;
    data->unk_00 = playerIdx;
    data->unk_04 = arg1;
    return prc;
}

Process *func_800ED70C_name_81(s32 playerIdx, s32 arg) {
    Process *prc = NULL;

    if (MBDGetPlayerStruct(playerIdx)->stats.prize.gamblePrize != -1) {
        if (arg != 0) {
            prc = func_800ED4AC_name_81(playerIdx, 0xF);
        } else {
            prc = func_800ED68C_name_81(playerIdx, 3.0f);
        }
    }
    return prc;
}

void func_800ED788_name_81(s32 playerIndex) {
    Process *prc;

    if (GwSystem.current_board_index == 3) {
        prc = func_800ED70C_name_81(playerIndex, 1);
    } else {
        prc = func_800ED70C_name_81(playerIndex, 0);
    }

    if (prc != NULL) {
        HuPrcChildLink(HuPrcCurrentGet(), prc);
        HuPrcChildWatch();
    }
}

void func_800ED7EC_name_81(void) {
    UnkD3450PrcData *data = HuPrcCurrentGet()->user_data;
    s32 time = data->unk_04;
    s16 playerIndex = data->unk_00;
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);
    Vec cur;
    Vec next;
    Vec back;
    Vec from;
    Vec to;
    Vec dir;
    Process *prc;
    Object *partner;
    f32 angle;

    func_800EC548_name_81(playerIndex, &cur, &next, &back, &dir);
    func_800EB680_name_81(playerIndex, MBDMasuLinkMasuIdGet(player->blink, player->bidx), &back);
    prc = HuPrcCurrentGet();
    partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_BACK);
    MBDVecDirGet(&back, &cur, &dir);
    angle = MBDVecAngleGet(&dir) + 180.0f;
    to.x = sindf(angle) * 12.0f + cur.x;
    to.z = cosdf(angle) * 12.0f + cur.z;
    to.y = cur.y;
    HuVecCopy3F(&from, &partner->coords);
    HuVecCopy3F(&partner->rot, &dir);
    HuPrcChildLink(prc, func_800EBF2C_name_81(&from, &to, &partner->coords, time));
    func_800EF7C8_name_81(partner, 5.0f, -5.0f / (time / 2));
    HuPrcChildWatch();
    omDelPrcObj(NULL);
}

Process *func_800ED9C4_name_81(s16 playerIdx, s32 arg) {
    Process *prc = omAddPrcObj(func_800ED7EC_name_81, 0x4003, 0, 0x40);
    UnkD3450PrcData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450PrcData));

    prc->user_data = data;
    data->unk_00 = playerIdx;
    data->unk_04 = arg;
    return prc;
}

void func_800EDA38_name_81(void) {
    UnkD3450PrcDataF *data = HuPrcCurrentGet()->user_data;
    s16 playerIndex = data->unk_00;
    f32 speed = data->unk_04;
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);
    Vec cur;
    Vec next;
    Vec back;
    Vec from;
    Vec to;
    Vec dir;
    Process *prc;
    Object *partner;
    f32 angle;

    func_800EC548_name_81(playerIndex, &cur, &next, &back, &dir);
    func_800EB680_name_81(playerIndex, MBDMasuLinkMasuIdGet(player->blink, player->bidx), &back);
    prc = HuPrcCurrentGet();
    partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_BACK);
    MBDVecDirGet(&back, &cur, &dir);
    angle = MBDVecAngleGet(&dir) + 180.0f;
    to.x = sindf(angle) * 12.0f + cur.x;
    to.z = cosdf(angle) * 12.0f + cur.z;
    to.y = cur.y;
    HuVecCopy3F(&from, &partner->coords);
    HuVecCopy3F(&partner->rot, &dir);
    HuPrcChildLink(prc, func_800EC1E4_name_81(&from, &to, &partner->coords, speed));
    HuPrcChildWatch();
    omDelPrcObj(NULL);
}

Process *func_800EDBEC_name_81(s16 playerIdx, f32 arg1) {
    Process *prc = omAddPrcObj(func_800EDA38_name_81, 0x4003, 0, 0x40);
    UnkD3450PrcDataF *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450PrcDataF));

    prc->user_data = data;
    data->unk_00 = playerIdx;
    data->unk_04 = arg1;
    return prc;
}

Process *func_800EDC6C_name_81(s32 playerIdx, s32 arg) {
    Process *prc = NULL;

    if (MBDGetPlayerStruct(playerIdx)->stats.prize.duelNo != -1) {
        if (arg != 0) {
            prc = func_800ED9C4_name_81(playerIdx, 0xF);
        } else {
            prc = func_800EDBEC_name_81(playerIdx, 3.0f);
        }
    }
    return prc;
}

void func_800EDCE8_name_81(s32 playerIndex) {
    Process *prc;

    if (GwSystem.current_board_index == 3) {
        prc = func_800EDC6C_name_81(playerIndex, 1);
    } else {
        prc = func_800EDC6C_name_81(playerIndex, 0);
    }
    if (prc != NULL) {
        HuPrcChildLink(HuPrcCurrentGet(), prc);
        HuPrcChildWatch();
    }
}
