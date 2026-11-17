#include "common_duel.h"
#include "ovl_81.h"

typedef struct UnkNameVecEntry {
    /* 0x00 */ Object *obj;
    /* 0x04 */ u16 count; // number of points
    /* 0x06 */ u16 index; // current point index
    /* 0x08 */ f32 speed;
    /* 0x0C */ Vec *points; // array of count Vecs
} UnkNameVecEntry;          // sizeof 0x10

extern UnkD6B00 mbdMotShiftTbl[16];
s32 mbdWinComKeyAllNum = 2;
extern s32 GwMessSpeed;
extern s32 GwMessWait;

static void MBDMesSpeedCurSet(s32 arg0);
static void MBDWinComKeyExec(s32 arg0, s32 arg1, s32 arg2);
static void MBDWinComKey2Exec(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
static void MBDWinComKeyAllExec(s32 arg0, s32 arg1);
static s32 MBDModelTargetMoveExec(Object *obj, Vec *target, f32 speed, Vec *dir);

void MBDMesWaitSet(s32 arg0) {
    GwMessWait = arg0;
    MBDMesSpeedCurSet(arg0);
}

s32 MBDMesWaitGet(void) {
    return GwMessWait;
}

static void MBDMesSpeedCurSet(s32 arg0) {
    GwMessSpeed = arg0;
}

void MBDWinComKeyWait(s32 arg0, s32 arg1) {
    MBDWinComKeyExec(arg0, arg1, 0);
}

void MBDWinComKeyWaitKeep(s32 arg0, s32 arg1) {
    MBDWinComKeyExec(arg0, arg1, 1);
}

static void MBDWinComKeyExec(s32 arg0, s32 arg1, s32 arg2) {
    s16 sp18[MB_MAX_PLAYERS];
    s32 hasCom = 0;
    u8 sp20[MB_MAX_PLAYERS] = { 1, 2, 4, 8 };
    s32 sp2C;
    s32 i;

    hasCom = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == arg1) {
            if (GwPlayer[i].stat & 1) {
                hasCom = 1;
                sp18[GwPlayer[i].pad] = A_BUTTON;
            } else {
                HuWinActivePlayerSet(arg0, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (hasCom != 0) {
        HuWinAttrSet(arg0, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        GwMessSpeed = GwMessWait;
    } else {
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    if (arg2 == 0) {
        while (HuWinStatGet(arg0) != 0) {
            HuPrcVSleep();
        }
    } else {
        while ((HuWinStatGet(arg0) != 0) && !(HuWinAttrGet(arg0) & 0x200)) {
            HuPrcVSleep();
        }
        winData[arg0].stat = 7;
    }
    HuWinComKeyReset();
}

void MBDWinComKey2Wait(s32 arg0, s32 arg1, s32 arg2) {
    MBDWinComKey2Exec(arg0, arg1, arg2, 0);
}

void MBDWinComKey2WaitKeep(s32 arg0, s32 arg1, s32 arg2) {
    MBDWinComKey2Exec(arg0, arg1, arg2, 1);
}

static void MBDWinComKey2Exec(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS] = { 1, 2, 4, 8 };
    u8 mask;
    s32 i;

    mask = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if ((i == arg1) || (i == arg2)) {
            if (GwPlayer[i].stat & 1) {
                sp18[GwPlayer[i].pad] = A_BUTTON;
            } else {
                mask |= sp20[GwPlayer[i].pad];
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (mask) {
        HuWinActivePlayerSet(arg0, mask);
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    } else {
        HuWinAttrSet(arg0, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], GwMessSpeed);
        GwMessSpeed = GwMessWait;
    }

    if (arg3 == 0) {
        while (HuWinStatGet(arg0) != 0) {
            HuPrcVSleep();
        }
    } else {
        while ((HuWinStatGet(arg0) != 0) && !(HuWinAttrGet(arg0) & 0x200)) {
            HuPrcVSleep();
        }
        winData[arg0].stat = 7;
    }
    HuWinComKeyReset();
}

void MBDWinComKeyAllWait(s32 arg0) {
    MBDWinComKeyAllExec(arg0, 0);
}

void MBDWinComKeyAllWaitKeep(s32 arg0) {
    MBDWinComKeyAllExec(arg0, 1);
}

void MBDWinComKeyAllNumSet(s32 arg0) {
    mbdWinComKeyAllNum = arg0;
}

static void MBDWinComKeyAllExec(s32 arg0, s32 arg1) {
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS] = { 1, 2, 4, 8 };
    u8 mask;
    s32 i;

    mask = 0;
    for (i = 0; i < mbdWinComKeyAllNum; i++) {
        if (!(GwPlayer[i].stat & 1)) {
            break;
        }
    }

    if (i == mbdWinComKeyAllNum) {
        HuWinAttrSet(arg0, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(A_BUTTON, A_BUTTON, A_BUTTON, A_BUTTON, GwMessSpeed);
        HuWinComKeyWait(A_BUTTON, A_BUTTON, A_BUTTON, A_BUTTON, GwMessSpeed);
        HuWinComKeyWait(A_BUTTON, A_BUTTON, A_BUTTON, A_BUTTON, GwMessSpeed);
        HuWinComKeyWait(A_BUTTON, A_BUTTON, A_BUTTON, A_BUTTON, GwMessSpeed);
        HuWinComKeyWait(A_BUTTON, A_BUTTON, A_BUTTON, A_BUTTON, GwMessSpeed);
        HuWinComKeyWait(A_BUTTON, A_BUTTON, A_BUTTON, A_BUTTON, GwMessSpeed);
        HuWinComKeyWait(A_BUTTON, A_BUTTON, A_BUTTON, A_BUTTON, GwMessSpeed);
        GwMessSpeed = GwMessWait;
        if (arg1 == 0) {
            while (HuWinStatGet(arg0) != 0) {
                HuPrcVSleep();
            }
        } else {
            while ((HuWinStatGet(arg0) != 0) && !(HuWinAttrGet(arg0) & 0x200)) {
                HuPrcVSleep();
            }
            winData[arg0].stat = 7;
        }
    } else {
        for (i = 0; i < mbdWinComKeyAllNum; i++) {
            if (GwPlayer[i].stat & 1) {
                sp18[GwPlayer[i].pad] = 0;
            } else {
                mask |= sp20[GwPlayer[i].pad];
                sp18[GwPlayer[i].pad] = -1;
            }
        }
        HuWinActivePlayerSet(arg0, mask);
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
        if (arg1 == 0) {
            while (HuWinStatGet(arg0) != 0) {
                HuPrcVSleep();
            }
        } else {
            while ((HuWinStatGet(arg0) != 0) && !(HuWinAttrGet(arg0) & 0x200)) {
                HuPrcVSleep();
            }
            winData[arg0].stat = 7;
        }
    }
    HuWinComKeyReset();
}

void MBDWinComKeyAnyWait(s32 arg0) {
    HuWinActivePlayerSet(arg0, HUWIN_PLAYER_ALL);
    HuWinComKeySet(-1, -1, -1, -1);
    while (HuWinStatGet(arg0) != 0) {
        HuPrcVSleep();
    }
    HuWinComKeyReset();
}

void MBDModelJumpSet(Object *arg0, f32 arg1, f32 arg2) {
    arg0->velocity.y = arg1;
    arg0->velocity.z = arg2;
}

s32 MBDModelJumpCheck(Object *arg0) {
    s32 ret = 0;
    if (arg0->velocity.z != 0.0f) {
        ret = 1;
    }
    return ret;
}

void MBDModelJumpWait(Object *arg0) {
    while (MBDModelJumpCheck(arg0)) {
        HuPrcVSleep();
    }
}

void MBDMotShiftInit(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        mbdMotShiftTbl[i].unk_04 = NULL;
        mbdMotShiftTbl[i].unk_08 = NULL;
    }
}

void MBDMotShiftClose(void) {
    s32 i;
    UnkD6B00 *entry;

    for (i = 0, entry = mbdMotShiftTbl; i < 16; i++) {
        if (entry[i].unk_08 != NULL) {
            omDelObj(entry[i].unk_08);
            entry[i].unk_08 = NULL;
        }
    }
}

static void MBDMotShiftObjMain(omObjData *obj) {
    UnkD6B00 *entry = &mbdMotShiftTbl[obj->work[0]];

    if (Hu3DData[entry->unk_04->omObj1->model[0]].motTime ==
        Hu3DMotion[Hu3DData[entry->unk_04->omObj1->model[0]].motId].unk02) {
        MBDMotionShiftSet(entry->unk_04, entry->unk_00, 0, 0xA, entry->unk_02);
        entry->unk_04 = NULL;
        entry->unk_08 = NULL;
        omDelObj(obj);
    }
}

s32 MBDMotionEndShiftSet(Object *arg0, s16 arg1, s16 arg2) {
    omObjData *obj;
    UnkD6B00 *entry;
    s32 i;
    s32 ret;

    for (i = 0; i < ARRAY_COUNT(mbdMotShiftTbl); i++) {
        entry = &mbdMotShiftTbl[i];
        if (entry->unk_08 == NULL) {
            break;
        }
    }

    if (i != ARRAY_COUNT(mbdMotShiftTbl)) {
        obj = omAddObj(0x2000, 0, 0, -1, MBDMotShiftObjMain);
        entry->unk_08 = obj;
        obj->work[0] = i;
        entry->unk_04 = arg0;
        entry->unk_00 = arg1;
        entry->unk_02 = arg2;
        ret = i;
    } else {
        ret = -1;
    }
    return ret;
}

void MBDMotionShiftSetDef(Object *arg0, s16 arg1, s32 arg2) {
    MBDMotionShiftSet(arg0, arg1, 0, 0xA, arg2);
}

void MBDModelMotionWait(Object *arg0) {
    while (!(MBDMotionCheck(arg0) & 1)) {
        HuPrcVSleep();
    }
}

void MBDModelMotionStartWait(Object *arg0) {
    do {
        HuPrcVSleep();
    } while (!(MBDMotionStartCheck(arg0) & 1));
}

s32 MBDPlayerRankCalc(s32 playerIndex) {
    s32 rank;
    s32 i;
    s32 score[MBD_MAX_PLAYERS];

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        score[i] = GwPlayer[i].star * 1000 + GwPlayer[i].coin;
    }

    for (i = 0, rank = 0; i < MBD_MAX_PLAYERS; i++) {
        if ((i != playerIndex) && (score[playerIndex] < score[i])) {
            rank++;
        }
    }
    return rank;
}

s32 MBDPlayerScoreGet(s32 playerIndex) {
    return GwPlayer[playerIndex].star * 1000 + GwPlayer[playerIndex].coin;
}

void MBDPlayerKeyWait(void) {
    s32 i;

    HuPrcSleep(2);
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if (!(GwPlayer[i].stat & 1)) {
            break;
        }
    }

    if (i == MBD_MAX_PLAYERS) {
        HuPrcSleep(30);
        return;
    }

    while (1) {
        for (i = 0; i < MBD_MAX_PLAYERS; i++) {
            if (!(GwPlayer[i].stat & 1) && (HuPadBtnDown[GwPlayer[i].pad] & (A_BUTTON | B_BUTTON))) {
                break;
            }
        }

        if (i == MBD_MAX_PLAYERS) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
}

void MBDPlayerKeyWaitAll(void) {
    s32 i;

    HuPrcSleep(2);
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (!(GwPlayer[i].stat & 1)) {
            break;
        }
    }

    if (i == MB_MAX_PLAYERS) {
        HuPrcSleep(30);
        return;
    }

    while (1) {
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            if (!(GwPlayer[i].stat & 1) && (HuPadBtnDown[GwPlayer[i].pad] & (A_BUTTON | B_BUTTON))) {
                break;
            }
        }

        if (i == MB_MAX_PLAYERS) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
}

s32 MBDRand(f32 arg0) { // 800EEF80 in party mode
    // rand8 returns an unsigned byte
    u8 randomByte1 = rand8();
    u8 randomByte2 = rand8();
    s32 shiftedByte1 = (randomByte1 << 8);

    // Normalize the 16-bit number to the range [0, 1), then multiply by arg0
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;

    return scaledRandom;
}

s32 MBDModelTargetMoveRot(Object *obj, Vec *target, f32 speed) {
    return MBDModelTargetMoveExec(obj, target, speed, &obj->rot);
}

s32 MBDModelTargetMove(Object *obj, Vec *target, f32 speed) {
    Vec dir;

    return MBDModelTargetMoveExec(obj, target, speed, &dir);
}

static s32 MBDModelTargetMoveExec(Object *obj, Vec *target, f32 speed, Vec *dir) {
    f32 dist = HuVecDistance(&obj->coords, target);

    if (dist == 0.0f) {
        return 1;
    }
    MBDVecDirGet(&obj->coords, target, dir);
    if (speed <= dist) {
        obj->coords.x += speed * dir->x;
        obj->coords.y += speed * dir->y;
        obj->coords.z += speed * dir->z;
        return 0;
    }
    HuVecCopy3F(&obj->coords, target);
    return 1;
}

UnkNameVecEntry *MBDModelPathCreate(Object *obj, f32 speed, s16 count, Vec *points) {
    UnkNameVecEntry *entry = HuMemMemoryAllocPerm(sizeof(UnkNameVecEntry));

    entry->obj = obj;
    entry->count = count;
    entry->index = 0;
    entry->speed = speed;
    entry->points = points;
    return entry;
}

s32 MBDModelPathMove(UnkNameVecEntry *entry) {
    if (MBDModelTargetMoveRot(entry->obj, &entry->points[entry->index], entry->speed) == 0) {
        return 0;
    }
    if (++entry->index >= entry->count) {
        entry->index--;
    }
    return 1;
}

s32 MBDModelTargetTurn(Object *obj, Vec *target, f32 speed) {
    Vec dir;
    f32 maxTurn = speed * 1.2f;
    f32 targetAngle;
    f32 angle;
    f32 diff;

    MBDVecDirGet(&obj->coords, target, &dir);
    targetAngle = MBDVecAngleGet(&dir);
    angle = MBDVecAngleGet(&obj->rot);
    diff = targetAngle - angle;
    if (fabs(diff) > maxTurn) {
        if (diff < 0.0f) {
            diff += 360.0f;
        }
        if (diff < 180.0f) {
            if (maxTurn < diff) {
                angle += maxTurn;
            } else {
                angle += diff;
            }
        } else if (maxTurn < 360.0f - diff) {
            angle -= maxTurn;
        } else {
            angle -= 360.0f - diff;
        }
    } else {
        angle = targetAngle;
    }
    dir.x = sindf(angle);
    dir.z = cosdf(angle);
    obj->rot = dir;
    return angle == targetAngle;
}

void MBDCameraZoomLerpExec(Vec *pos, f32 zoom, f32 targetZoom, u32 frames) {
    f32 step;

    frames = frames * 1.2f;
    step = (targetZoom - zoom) / frames;
    while (1) {
        zoom += step;
        if (step >= 0.0f) {
            if (zoom >= targetZoom) {
                zoom = targetZoom;
            }
        } else if (zoom <= targetZoom) {
            zoom = targetZoom;
        }
        MBDCameraZoomSet(zoom);
        MBDCameraPos3DSet(pos);
        if (step >= 0.0f ? zoom >= targetZoom : zoom <= targetZoom) {
            break;
        }
        HuPrcVSleep();
    }
}

void MBDModelHookSet(Object *obj, char *hookName, s16 model) {
    Hu3DModelHookSet(model, obj->omObj1->model[0], hookName);
    Hu3DModelAttrSet(model, HU3D_ATTR_HOOK, HU3D_ATTR_HOOK);
}

void MBDModelHookReset(s16 arg0) {
    Hu3DModelAttrSet(arg0, HU3D_ATTR_HOOK, HU3D_ATTR_NONE);
}

s32 MBDWinDummyCreate(s16 x, s16 y, s16 w, s16 h) {
    s32 win = HuWinCreate(x, y, w, h, 0, 0);

    HuWinBGTPLvlSet(win, 200);
    HuWinDummy(win);
    HuWinAttrSet(win, HUWIN_ATTR_PAUSE, HUWIN_ATTR_PAUSE);
    HuWinMesSpeedSet(win, 0);
    return win;
}
