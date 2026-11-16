#include "common.h"
#include "game/hmfmath.h"
#include "game/overlays/minigame.h"
#include "mstory2.h"

typedef struct MstoryPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ u16 flags;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec *points;
    /* 0x0C */ f32 (*intervals)[2];
} MstoryPath; // sizeof 0x10

extern s32 omCharModelNoTbl[][6];

extern char *mstory2_scene4PlayerAnimNameTbl[];
extern char *mstory2_scene4RivalAnimNameTbl[];

extern void (*const mstory2_sceneCreateTbl[])(void);
extern const Vec mstory2_scene4RivalStartPos;
extern const Vec mstory2_scene4TumbleDestRot2;
extern const Vec mstory2_scene4StarStartPos;
extern const Vec mstory2_scene4StampStartPos;
extern const Vec mstory2_scene4FrontRot;
extern const Vec mstory2_scene4TumbleDestRot4;
extern const Vec mstory2_scene4TumbleDestRot5;
extern Vec mstory2_scene4RivalPos;
extern Vec mstory2_scene4StarPos;
extern Mstory2ObjWork mstory2_scene4WorkTbl[6];
extern Vec mstory2_scene4StampPos;
extern s16 mstory2_scene4TumbleFaceAnimTbl[3];
extern Vec mstory2_scene4TumblePos;
extern const Vec mstory2_scene4TumbleStartPos;
extern s16 mstory2_scene4TumbleFaceSlot;
extern const Vec mstory2_scene4TumbleDestRot3;
extern s16 mstory2_scene4StarFloatStopF;
extern s16 mstory2_scene4ShadowMdl;
extern s16 mstory2_scene4PlayerChr;
extern s16 mstory2_scene4RivalChr;
extern s16 mstory2_scene4RivalFaceAnimTbl[3];
extern const Vec mstory2_scene4RivalDestRot2;
extern s16 mstory2_scene4PlayerFaceAnimTbl[3];
extern const Vec mstory2_scene4PlayerDestRot1;
extern s16 mstory2_scene4PlayerFaceSlot;
extern s16 mstory2_scene4RivalFaceSlot;

void mstory2_WinCreate(void);
void mstory2_HmfAnimSet(s16 model, s16 arg1, s16 arg2);
void mstory2_ObjPosMoveEx(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void mstory2_ObjRotMoveV(omObjData *obj, Vec *pos, s32 frames);
void mstory2_ObjForwardMove(omObjData *obj, f32 speed, s16 frames);
void mstory2_ObjTargetFace(omObjData *obj, omObjData *target);
void mstory2_Scene4PlayerDestroy(void);
void mstory2_Scene4RivalDestroy(void);
void mstory2_Scene4PlayerRivalFace(omObjData *obj);
void mstory2_Scene4TumbleTurn(omObjData *obj);
void mstory2_Scene4TumbleRivalFace(omObjData *obj);
void mstory2_Scene4PlayerStep(omObjData *);
void mstory2_Scene4ObjIdle(omObjData *);
void mstory2_Scene4EventExec(omObjData *);
void mstory2_ObjPosMoveAccel(omObjData *obj, Vec *target, s32 frames, s32 faceDir);
void mstory2_Scene4PlayerCardShow(omObjData *obj);
void mstory2_Scene4PlayerCardHide(omObjData *obj);
void mstory2_Scene4PlayerKnockBack(omObjData *obj);
void mstory2_Scene4PlayerExit(omObjData *obj);
void mstory2_Scene4RivalStep(omObjData *obj);
void mstory2_Scene4RivalKnockBack(omObjData *obj);
void mstory2_Scene4RivalExit(omObjData *obj);
void mstory2_Scene4RivalLuigiPose(omObjData *obj);
void mstory2_Scene4TumbleHop1(omObjData *obj);
void mstory2_Scene4TumbleLand(omObjData *obj);
void mstory2_Scene4TumbleHop2(omObjData *obj);
void mstory2_Scene4TumblePlayerFace(omObjData *obj);
void mstory2_Scene4StarRivalFace(omObjData *obj);
void mstory2_Scene4StarTurn(omObjData *obj);
void mstory2_Scene4StarTumbleTurn(omObjData *obj);
void mstory2_Scene4EventIntroExec(omObjData *);
void mstory2_Scene4StarDestroy(void);
void mstory2_Scene4StampDestroy(void);
void mstory2_Scene4PlayerProc(void);
void mstory2_Scene4RivalProc(void);
void mstory2_Scene4TumbleProc(void);
void mstory2_Scene4TumbleDestroy(void);
void mstory2_Scene4StarProc(void);
void mstory2_Scene4StampProc(void);
void mstory2_Scene4EventProc(void);
void mstory2_Scene4StarFloatProc(void);
void mstory2_Scene4ObjSeLoopProc(void);
void mstory2_SceneEnd(void);
void mstory2_WinOpen(void);
void mstory2_WinClose(void);
void mstory2_WinMesExec(s32 mess);
void mstory2_WinMesChrNameExec(s32 mess);
void mstory2_BackMotionStart(void);
void mstory2_ObjPosMoveV(omObjData *obj, Vec *pos, s32 frames);
void mstory2_MotionEndWait(s16 model);

Vec mstory2_scene4StampPathA[4] = {
    { 0.0f, 200.0f, 100.0f },
    { -200.0f, 100.0f, -100.0f },
    { -100.0f, 300.0f, 300.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};
Vec mstory2_scene4StampPathB[4] = {
    { -100.0f, 300.0f, 300.0f },
    { -200.0f, 400.0f, -100.0f },
    { 0.0f, 200.0f, 100.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};
Vec mstory2_scene4UnusedRot0 = { 0.0f, 158.73f, 0.0f }; /* Unreferenced. */
Vec mstory2_scene4UnusedRot1 = { 0.0f, 167.01f, 0.0f }; /* Unreferenced. */
Vec mstory2_scene4StarDestRot0 = { 0.0f, 158.46f, 0.0f };
Vec mstory2_scene4RivalDestRot0 = { 0.0f, -70.43f, 0.0f };
Vec mstory2_scene4TumbleDestRot0 = { 0.0f, -77.13f, 0.0f };
Vec mstory2_scene4TumbleDestRot1 = { 0.0f, -135.0f, 0.0f };
Vec mstory2_scene4UnusedRot2 = { 0.0f, 162.4f, 0.0f };   /* Unreferenced. */
Vec mstory2_scene4UnusedRot3 = { 0.0f, -147.34f, 0.0f }; /* Unreferenced. */
Vec mstory2_scene4UnusedRot4 = { 0.0f, 306.61f, 0.0f };  /* Unreferenced. */
Vec mstory2_scene4RivalDestRot1 = { 0.0f, 90.0f, 0.0f };
Vec mstory2_scene4StarDestRot1 = { 0.0f, 50.19f, 0.0f };
Vec mstory2_scene4PlayerDestRot0 = { 0.0f, 100.78f, 0.0f };

const Vec mstory2_scene4PlayerStartPos = { -120.0f, 0.0f, 480.0f };

MstoryPath *mstory2_Scene4PathCreate(Vec *points, s32 flags) {
    MstoryPath *path;
    Vec *current;
    Vec *next;
    f32(*interval)[2];
    f32 totalLength;
    f32 length;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 count;
    s16 i;

    path = HuMemAllocTag(sizeof(MstoryPath), TAG_OVERLAY);
    path->flags = flags;
    path->points = points;
    current = points;
    next = current + 1;
    totalLength = 0.0f;
    for (count = 0; next->x != 9999.0f || next->y != 9999.0f || next->z != 9999.0f; count++, next++, current++) {
        dx = next->x - current->x;
        dy = next->y - current->y;
        dz = next->z - current->z;
        totalLength += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    if (flags & 1) {
        dx = points->x - current->x;
        dy = points->y - current->y;
        dz = points->z - current->z;
        totalLength += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    count++;
    path->count = count;
    interval = HuMemAllocTag(count * sizeof(*interval), TAG_OVERLAY);
    path->intervals = interval;
    current = points;
    next = current + 1;
    length = 0.0f;
    for (i = 0; i < count; i++, current++, next++, interval++) {
        dx = next->x - current->x;
        dy = next->y - current->y;
        dz = next->z - current->z;
        if (flags & 1) {
            if (i == count - 1) {
                dx = points->x - current->x;
                dy = points->y - current->y;
                dz = points->z - current->z;
            }
        }
        dz = HuSqrtf(dx * dx + dy * dy + dz * dz);
        (*interval)[0] = length / totalLength;
        (*interval)[1] = (length + dz) / totalLength;
        if ((*interval)[1] > 1.0f) {
            (*interval)[1] = 1.0001f;
        }
        length += dz;
    }
    return path;
}

void mstory2_Scene4PathPosGet(MstoryPath *path, f32 time, Vec *result) {
    f32 values[4];
    f32 times[4];
    Vec *points;
    f32(*interval)[2];
    s16 i;

    if (time >= 1.0f) {
        result->x = path->points[path->count - 1].x;
        result->y = path->points[path->count - 1].y;
        result->z = path->points[path->count - 1].z;
        return;
    }
    interval = path->intervals;
    for (i = 0; i < path->count; i++, interval++) {
        if (time <= (*interval)[0]) {
            break;
        }
    }
    i--;
    if (i < 0) {
        i = 0;
    }
    if (i >= path->count - 1) {
        i--;
    }
    interval = path->intervals;
    if (path->flags & 1) {
        times[0] = i == 0 ? -(1.0f - interval[path->count - 1][0]) : interval[i - 1][0];
        times[1] = interval[i][0];
        times[2] = i >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 1][0];
        times[3] = i + 1 >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 2][0];
        points = path->points;
        if (i == 0) {
            values[0] = points[path->count - 1].x;
        } else {
            values[0] = points[i - 1].x;
        }
        values[1] = points[i].x;
        if (i >= path->count - 1) {
            values[2] = points[0].x;
        } else {
            values[2] = points[i + 1].x;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[0].x;
        } else {
            values[3] = points[i + 2].x;
        }
        result->x = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[path->count - 1].y;
        } else {
            values[0] = points[i - 1].y;
        }
        values[1] = points[i].y;
        if (i >= path->count - 1) {
            values[2] = points[0].y;
        } else {
            values[2] = points[i + 1].y;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[0].y;
        } else {
            values[3] = points[i + 2].y;
        }
        result->y = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[path->count - 1].z;
        } else {
            values[0] = points[i - 1].z;
        }
        values[1] = points[i].z;
        if (i >= path->count - 1) {
            values[2] = points[0].z;
        } else {
            values[2] = points[i + 1].z;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[0].z;
        } else {
            values[3] = points[i + 2].z;
        }
        result->z = InterpolateBMLine(values, times, time);
    } else {
        if (i == 0) {
            times[0] = -1.0f;
        } else {
            times[0] = interval[i - 1][0];
        }
        times[1] = interval[i][0];
        times[2] = i >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 1][0];
        times[3] = i + 1 >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 2][0];
        points = path->points;
        if (i == 0) {
            values[0] = points[0].x;
        } else {
            values[0] = points[i - 1].x;
        }
        values[1] = points[i].x;
        if (i >= path->count - 1) {
            values[2] = points[path->count - 1].x;
        } else {
            values[2] = points[i + 1].x;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[path->count - 1].x;
        } else {
            values[3] = points[i + 2].x;
        }
        result->x = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[0].y;
        } else {
            values[0] = points[i - 1].y;
        }
        values[1] = points[i].y;
        if (i >= path->count - 1) {
            values[2] = points[path->count - 1].y;
        } else {
            values[2] = points[i + 1].y;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[path->count - 1].y;
        } else {
            values[3] = points[i + 2].y;
        }
        result->y = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[0].z;
        } else {
            values[0] = points[i - 1].z;
        }
        values[1] = points[i].z;
        if (i >= path->count - 1) {
            values[2] = points[path->count - 1].z;
        } else {
            values[2] = points[i + 1].z;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[path->count - 1].z;
        } else {
            values[3] = points[i + 2].z;
        }
        result->z = InterpolateBMLine(values, times, time);
    }
}

void mstory2_Scene4PathKill(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void mstory2_Scene4Create(void) {
    mstory2_scene4PlayerChr = GwStory.unk1;
    if (mstory2_scene4PlayerChr == 2) {
        mstory2_scene4RivalChr = 1;
    } else {
        mstory2_scene4RivalChr = 2;
    }
    mstory2_WinCreate();
    mstory2_scene4ShadowMdl = Hu3DModelRead(9, 0x2B9);
    omAddPrcObj(mstory2_Scene4PlayerProc, 0x1001, 0x1000, 0);
    omAddPrcObj(mstory2_Scene4RivalProc, 0x1001, 0x1000, 0);
    omAddPrcObj(mstory2_Scene4TumbleProc, 0x1001, 0x1000, 0);
    omAddPrcObj(mstory2_Scene4StarProc, 0x1001, 0x1000, 0);
    omAddPrcObj(mstory2_Scene4StampProc, 0x1001, 0x1000, 0);
    HuPrcVSleep();
    omAddPrcObj(mstory2_Scene4EventProc, 0x1001, 0x1000, 0);
    omAddPrcObj(mstory2_Scene4StarFloatProc, 0x1001, 0x1000, 0);
    omAddPrcObj(mstory2_Scene4ObjSeLoopProc, 0x1001, 0x1000, 0);
    Hu3DModelAttrSet(mstory2_scene4ShadowMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void mstory2_Scene4ObjIdle(omObjData *obj) {
}

void mstory2_Scene4ObjSeLoopProc(void) {
    s16 seNo;
    s8 vol;
    f32 z;

    while (TRUE) {
        if (mstory2_scene4WorkTbl[0].unk_0C == 1 && Hu3DData[mstory2_scene4WorkTbl[0].obj->model[1]].motTime == 0.0f) {
            CharFXPlay((s16)mstory2_scene4WorkTbl[0].unk_10, mstory2_scene4PlayerChr);
        }
        if (mstory2_scene4WorkTbl[1].unk_0C == 1 && Hu3DData[mstory2_scene4WorkTbl[1].obj->model[1]].motTime == 0.0f) {
            seNo = CharFXPlay((s16)mstory2_scene4WorkTbl[1].unk_10, mstory2_scene4RivalChr);
            z = Hu3DData[mstory2_scene4WorkTbl[1].obj->model[1]].pos.z;
            if (z <= 0.0f) {
                vol = z / 15.0f + 127.0f;
            } else {
                vol = 127;
            }
            HuAudFXVolSet(seNo, vol);
        }
        HuPrcVSleep();
    }
}

void mstory2_Scene4EventProc(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    mstory2_scene4WorkTbl[5].obj = obj;
    mstory2_scene4WorkTbl[5].unk_08 = 0;
    mstory2_scene4WorkTbl[5].func = mstory2_Scene4EventIntroExec;

    for (;;) {
        mstory2_scene4WorkTbl[5].func(obj);
        HuPrcVSleep();
    }
}

const Vec mstory2_scene4RivalStartPos = { 608.1f, -85.8f, -1390.3f };

const Vec mstory2_scene4TumbleStartPos = { 238.0f, 100.0f, 214.0f };

const Vec mstory2_scene4StarStartPos = { 0.0f, 200.0f, 150.0f };

const Vec mstory2_scene4StampStartPos = { 0.0f, 200.0f, 100.0f };
const Vec mstory2_scene4UnusedPos0 = { 0.0f, 0.0f, 0.0f }; /* Unreferenced. */

void mstory2_Scene4EventIntroExec(omObjData *obj) {
    Vec pos[4] = {
        { 20.0f, -20.0f, 0.0f },
        { 0.0f, 225.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 300.0f, 0.0f },
    };

    HuPrcSleep(40);
    mstory2_ObjRotMoveV(mstory2_scene4WorkTbl[3].obj, &pos[0], 10);
    mstory2_ObjRotMoveV(mstory2_scene4WorkTbl[2].obj, &pos[1], 10);
    HuAudFXPlay(0x159);
    Hu3DMotionShiftSet(mstory2_scene4WorkTbl[3].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[3].obj->motion[1]].motId, 0, 10, 2);
    mstory2_WinOpen();
    if (mstory2_scene4PlayerChr != 2) {
        mstory2_WinMesChrNameExec(0x5A38);
    } else {
        mstory2_WinMesExec(0x5B2A);
    }
    mstory2_WinClose();
    Hu3DMotionShiftSet(mstory2_scene4WorkTbl[3].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[3].obj->motion[0]].motId, 0, 10, 2);
    mstory2_ObjRotMoveV(mstory2_scene4WorkTbl[3].obj, &pos[2], 10);
    mstory2_ObjRotMoveV(mstory2_scene4WorkTbl[2].obj, &pos[3], 10);
    mstory2_scene4WorkTbl[5].func = mstory2_Scene4EventExec;
}

void mstory2_Scene4EventExec(omObjData *obj) {
    Vec cur;
    MstoryPath *paths[2];
    s16 j = 0;
    Vec pos[6] = {
        { 150.0f, 0.0f, 384.0f },
        { 0.0f, 200.0f, 300.0f },
        { 0.0f, 200.0f, 150.0f },
        { 300.0f, 25.0f, 400.0f },
        { 300.0f, 125.0f, 400.0f },
        { 238.0f, 100.0f, 214.0f },
    };
    s16 i;
    f32 t;

    Hu3DModelAttrSet(mstory2_scene4WorkTbl[4].obj->model[1], 4, 0);
    Hu3DModelAttrSet(mstory2_scene4WorkTbl[4].obj->model[2], 4, 0);
    Hu3DParticleAttrSet(mstory2_scene4WorkTbl[4].obj->model[2], 1, 1);
    HuAudFXPlay(0x215);
    paths[0] = mstory2_Scene4PathCreate(mstory2_scene4StampPathA, 0);
    for (i = 0; i < 40.0f; i++) {
        if (i == 30) {
            Hu3DMotionShiftSet(mstory2_scene4WorkTbl[0].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[0].obj->motion[9]].motId, 0, 10, 2);
        }
        t = i * 0.025f;
        mstory2_Scene4PathPosGet(paths[0], t * t, &cur);
        Hu3DModelPosSet(mstory2_scene4WorkTbl[4].obj->model[1], cur.x, cur.y, cur.z);
        EffectPosSet(mstory2_scene4WorkTbl[4].obj->model[2], cur.x, cur.y - 40.0f, cur.z);
        HuPrcVSleep();
    }
    mstory2_Scene4PathKill(paths[0]);
    mstory2_scene4WorkTbl[0].func = mstory2_Scene4PlayerCardShow;
    while (TRUE) {
        if (mstory2_scene4WorkTbl[0].unk_08 == 1) {
            cur.x -= 0.19999999f;
            cur.y -= 2.0f;
            cur.z += 1.0f;
            Hu3DModelPosSet(mstory2_scene4WorkTbl[4].obj->model[1], cur.x, cur.y, cur.z);
            EffectPosSet(mstory2_scene4WorkTbl[4].obj->model[2], cur.x, cur.y - 40.0f, cur.z);
            if (j++ == 30.0f) {
                j = 0;
                break;
            }
        }
        HuPrcVSleep();
    }
    HuAudFXVolSet(CharFXPlay(0x2BD, mstory2_scene4RivalChr), 80);
    HuPrcSleep(30);
    Hu3DModelAttrSet(mstory2_scene4WorkTbl[1].obj->model[1], 4, 0);
    Hu3DModelAttrSet(mstory2_scene4WorkTbl[1].obj->model[2], 4, 0);
    mstory2_BackMotionStart();
    HuPrcSleep(10);
    mstory2_scene4WorkTbl[0].func = mstory2_Scene4PlayerCardHide;
    mstory2_scene4WorkTbl[2].func = mstory2_Scene4TumbleHop1;
    while (TRUE) {
        cur.x += 1.0f;
        cur.y += 10.0f;
        cur.z -= 5.0f;
        Hu3DModelPosSet(mstory2_scene4WorkTbl[4].obj->model[1], cur.x, cur.y, cur.z);
        EffectPosSet(mstory2_scene4WorkTbl[4].obj->model[2], cur.x, cur.y - 40.0f, cur.z);
        if (j++ == 6.0f) {
            break;
        }
        HuPrcVSleep();
    }
    mstory2_scene4StampPathB[0].x = cur.x;
    mstory2_scene4StampPathB[0].y = cur.y;
    mstory2_scene4StampPathB[0].z = cur.z;
    mstory2_ObjRotMoveV(mstory2_scene4WorkTbl[3].obj, &mstory2_scene4StarDestRot0, 5);
    mstory2_scene4WorkTbl[3].func = mstory2_Scene4StarRivalFace;
    while (TRUE) {
        if (mstory2_scene4WorkTbl[2].unk_08 == 5) {
            break;
        }
        HuPrcVSleep();
    }
    mstory2_MotionEndWait(mstory2_scene4WorkTbl[1].obj->model[1]);
    HuPrcSleep(30);
    mstory2_scene4WorkTbl[1].unk_0C = 1;
    mstory2_scene4WorkTbl[1].unk_10 = 40;
    Hu3DMotionSpeedSet(mstory2_scene4WorkTbl[0].obj->model[1], 0.25f);
    Hu3DMotionShiftSet(mstory2_scene4WorkTbl[0].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[0].obj->motion[10]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(mstory2_scene4WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[1].obj->motion[2]].motId, 0, 10, 2);
    mstory2_ObjPosMoveAccel(mstory2_scene4WorkTbl[1].obj, &pos[0], 180, 1);
    mstory2_scene4WorkTbl[1].unk_0C = 0;
    Hu3DMotionShiftSet(mstory2_scene4WorkTbl[0].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[0].obj->motion[0]].motId, 0, 10, 2);
    Hu3DMotionSpeedSet(mstory2_scene4WorkTbl[0].obj->model[1], 1.0f);
    mstory2_HmfAnimSet(mstory2_scene4WorkTbl[2].obj->model[1], mstory2_scene4TumbleFaceSlot, mstory2_scene4TumbleFaceAnimTbl[0]);
    Hu3DMotionShiftSet(mstory2_scene4WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[1].obj->motion[3]].motId, 0, 10, 2);
    HuPrcSleep(60);
    mstory2_HmfAnimSet(mstory2_scene4WorkTbl[2].obj->model[1], mstory2_scene4TumbleFaceSlot, mstory2_scene4TumbleFaceAnimTbl[0]);
    Hu3DMotionShiftSet(mstory2_scene4WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[1].obj->motion[0]].motId, 0, 10, 2);
    mstory2_ObjRotMoveV(mstory2_scene4WorkTbl[1].obj, &mstory2_scene4RivalDestRot0, 10);
    if (mstory2_scene4PlayerChr != 2) {
        mstory2_ObjPosMoveEx(mstory2_scene4WorkTbl[2].obj, &pos[3], 15, 0);
        Hu3DMotionShiftSet(mstory2_scene4WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[1].obj->motion[1]].motId, 0, 10, 2);
        mstory2_ObjRotMoveV(mstory2_scene4WorkTbl[1].obj, &mstory2_scene4RivalDestRot1, 10);
        Hu3DMotionShiftSet(mstory2_scene4WorkTbl[0].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[0].obj->motion[0]].motId, 0, 10, 2);
        Hu3DMotionShiftSet(mstory2_scene4WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[1].obj->motion[5]].motId, 0, 10, 0);
        HuPrcSleep(10);
        Hu3DMotionShiftSet(mstory2_scene4WorkTbl[2].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[2].obj->motion[2]].motId, 0, 10, 2);
        mstory2_MotionEndWait(mstory2_scene4WorkTbl[1].obj->model[1]);
        Hu3DMotionShiftSet(mstory2_scene4WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[1].obj->motion[5]].motId, 0, 10, 0);
        mstory2_MotionEndWait(mstory2_scene4WorkTbl[1].obj->model[1]);
        Hu3DMotionShiftSet(mstory2_scene4WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[1].obj->motion[0]].motId, 0, 10, 2);
        Hu3DMotionShiftSet(mstory2_scene4WorkTbl[2].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[2].obj->motion[0]].motId, 0, 10, 2);
        mstory2_scene4WorkTbl[2].func = mstory2_Scene4ObjIdle;
        mstory2_ObjPosMoveV(mstory2_scene4WorkTbl[2].obj, &pos[4], 8);
        mstory2_ObjRotMoveV(mstory2_scene4WorkTbl[2].obj, &mstory2_scene4TumbleDestRot0, 10);
        Hu3DMotionShiftSet(mstory2_scene4WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[1].obj->motion[1]].motId, 0, 10, 2);
        mstory2_ObjRotMoveV(mstory2_scene4WorkTbl[1].obj, &mstory2_scene4RivalDestRot0, 5);
        Hu3DMotionShiftSet(mstory2_scene4WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[1].obj->motion[0]].motId, 0, 10, 2);
        mstory2_scene4WorkTbl[3].func = mstory2_Scene4ObjIdle;
        mstory2_scene4WorkTbl[0].func = mstory2_Scene4ObjIdle;
        mstory2_ObjRotMoveV(mstory2_scene4WorkTbl[3].obj, &mstory2_scene4StarDestRot1, 5);
        mstory2_ObjRotMoveV(mstory2_scene4WorkTbl[0].obj, &mstory2_scene4PlayerDestRot0, 5);
        mstory2_WinOpen();
        mstory2_WinMesExec(0x5A39);
        mstory2_WinClose();
    } else {
        for (i = 0; i < 2; i++) {
            mstory2_ObjPosMoveEx(mstory2_scene4WorkTbl[2].obj, &pos[3], 15, 0);
            Hu3DMotionShiftSet(mstory2_scene4WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[1].obj->motion[1]].motId, 0, 10, 2);
            mstory2_ObjRotMoveV(mstory2_scene4WorkTbl[1].obj, &mstory2_scene4RivalDestRot1, 10);
            Hu3DMotionShiftSet(mstory2_scene4WorkTbl[0].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[0].obj->motion[0]].motId, 0, 10, 2);
            Hu3DMotionShiftSet(mstory2_scene4WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[1].obj->motion[5]].motId, 0, 10, 0);
            HuPrcSleep(10);
            Hu3DMotionShiftSet(mstory2_scene4WorkTbl[2].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[2].obj->motion[2]].motId, 0, 10, 2);
            mstory2_MotionEndWait(mstory2_scene4WorkTbl[1].obj->model[1]);
            if (i == 0) {
                Hu3DMotionShiftSet(mstory2_scene4WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[1].obj->motion[5]].motId, 0, 10, 0);
                mstory2_MotionEndWait(mstory2_scene4WorkTbl[1].obj->model[1]);
            }
            Hu3DMotionShiftSet(mstory2_scene4WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[1].obj->motion[0]].motId, 0, 10, 2);
            Hu3DMotionShiftSet(mstory2_scene4WorkTbl[2].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[2].obj->motion[0]].motId, 0, 10, 2);
            mstory2_scene4WorkTbl[2].func = mstory2_Scene4ObjIdle;
            mstory2_ObjPosMoveV(mstory2_scene4WorkTbl[2].obj, &pos[4], 8);
            mstory2_ObjRotMoveV(mstory2_scene4WorkTbl[2].obj, &mstory2_scene4TumbleDestRot0, 10);
            Hu3DMotionShiftSet(mstory2_scene4WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[1].obj->motion[1]].motId, 0, 10, 2);
            mstory2_ObjRotMoveV(mstory2_scene4WorkTbl[1].obj, &mstory2_scene4RivalDestRot0, 5);
            Hu3DMotionShiftSet(mstory2_scene4WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[1].obj->motion[0]].motId, 0, 10, 2);
            mstory2_scene4WorkTbl[3].func = mstory2_Scene4ObjIdle;
            mstory2_scene4WorkTbl[0].func = mstory2_Scene4ObjIdle;
            mstory2_ObjRotMoveV(mstory2_scene4WorkTbl[3].obj, &mstory2_scene4StarDestRot1, 5);
            mstory2_ObjRotMoveV(mstory2_scene4WorkTbl[0].obj, &mstory2_scene4PlayerDestRot0, 5);
            mstory2_WinOpen();
            mstory2_scene4WorkTbl[1].func = mstory2_Scene4RivalLuigiPose;
            mstory2_WinMesExec(i + 0x5B2B);
            mstory2_WinClose();
            Hu3DMotionShiftSet(mstory2_scene4WorkTbl[0].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[0].obj->motion[8]].motId, 0, 10, 0);
            mstory2_MotionEndWait(mstory2_scene4WorkTbl[0].obj->model[1]);
        }
        mstory2_MotionEndWait(mstory2_scene4WorkTbl[1].obj->model[1]);
    }
    Hu3DMotionShiftSet(mstory2_scene4WorkTbl[0].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[0].obj->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(mstory2_scene4WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[1].obj->motion[1]].motId, 0, 10, 2);
    mstory2_scene4WorkTbl[1].func = mstory2_Scene4RivalStep;
    mstory2_scene4WorkTbl[2].func = mstory2_Scene4TumbleLand;
    mstory2_scene4WorkTbl[3].func = mstory2_Scene4StarTurn;
    paths[1] = mstory2_Scene4PathCreate(mstory2_scene4StampPathB, 0);
    for (i = 0; i < 50.0f; i++) {
        t = i * 0.02f;
        mstory2_Scene4PathPosGet(paths[1], t * t, &cur);
        Hu3DModelPosSet(mstory2_scene4WorkTbl[4].obj->model[1], cur.x, cur.y, cur.z);
        EffectPosSet(mstory2_scene4WorkTbl[4].obj->model[2], cur.x, cur.y - 40.0f, cur.z);
        HuPrcVSleep();
    }
    mstory2_Scene4PathKill(paths[1]);
    Hu3DModelAttrSet(mstory2_scene4WorkTbl[4].obj->model[1], 4, 4);
    Hu3DModelAttrSet(mstory2_scene4WorkTbl[4].obj->model[2], 4, 4);
    Hu3DParticleAttrSet(mstory2_scene4WorkTbl[4].obj->model[2], 1, 0);
    HuPrcSleep(5);
    mstory2_HmfAnimSet(mstory2_scene4WorkTbl[2].obj->model[1], mstory2_scene4TumbleFaceSlot, mstory2_scene4TumbleFaceAnimTbl[2]);
    Hu3DMotionShiftSet(mstory2_scene4WorkTbl[2].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[2].obj->motion[1]].motId, 0, 10, 2);
    mstory2_scene4WorkTbl[2].func = mstory2_Scene4TumblePlayerFace;
    HuPrcSleep(10);
    mstory2_ObjPosMoveV(mstory2_scene4WorkTbl[2].obj, &pos[5], 60);
    HuPrcSleep(30);
    mstory2_scene4WorkTbl[2].func = mstory2_Scene4ObjIdle;
    mstory2_ObjRotMoveV(mstory2_scene4WorkTbl[2].obj, &mstory2_scene4TumbleDestRot1, 10);
    mstory2_WinOpen();
    mstory2_WinMesExec(mstory2_scene4PlayerChr == 2 ? 0x5A3A : 0x5B2D);
    mstory2_WinClose();
    HuPrcSleep(30);
    mstory2_scene4StarFloatStopF = 1;
    pos[2].y = pos[1].y = Hu3DData[mstory2_scene4WorkTbl[3].obj->model[1]].pos.y;
    mstory2_ObjPosMoveV(mstory2_scene4WorkTbl[3].obj, &pos[1], 3);
    HuAudFXPlay(0x217);
    mstory2_scene4WorkTbl[2].func = mstory2_Scene4TumbleHop2;
    mstory2_scene4WorkTbl[3].func = mstory2_Scene4StarTumbleTurn;
    mstory2_scene4WorkTbl[0].func = mstory2_Scene4PlayerKnockBack;
    mstory2_scene4WorkTbl[1].func = mstory2_Scene4RivalKnockBack;
    HuAudPlayerFXPlay(mstory2_scene4PlayerChr + 0x2AC, 0);
    HuAudPlayerFXPlay(mstory2_scene4RivalChr + 0x2AC, 1);
    mstory2_scene4StarFloatStopF = 0;
    mstory2_ObjPosMoveEx(mstory2_scene4WorkTbl[3].obj, &pos[2], 5, 0);
    while (TRUE) {
        if (mstory2_scene4WorkTbl[2].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    Hu3DMotionShiftSet(mstory2_scene4WorkTbl[3].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[3].obj->motion[1]].motId, 0, 10, 2);
    mstory2_WinOpen();
    mstory2_WinMesExec(mstory2_scene4PlayerChr != 2 ? 0x5A3B : 0x5B2E);
    mstory2_WinClose();
    Hu3DMotionShiftSet(mstory2_scene4WorkTbl[3].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[3].obj->motion[0]].motId, 0, 10, 2);
    mstory2_scene4WorkTbl[0].func = mstory2_Scene4PlayerExit;
    mstory2_scene4WorkTbl[1].func = mstory2_Scene4RivalExit;
    while (TRUE) {
        if (mstory2_scene4WorkTbl[0].unk_08 == 10 && mstory2_scene4WorkTbl[1].unk_08 == 10) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    mstory2_SceneEnd();
    mstory2_scene4WorkTbl[0].func = mstory2_Scene4ObjIdle;
    mstory2_scene4WorkTbl[3].func = mstory2_Scene4ObjIdle;
    mstory2_scene4WorkTbl[2].func = mstory2_Scene4ObjIdle;
    mstory2_scene4WorkTbl[4].func = mstory2_Scene4ObjIdle;
    mstory2_scene4WorkTbl[1].func = mstory2_Scene4ObjIdle;
    mstory2_scene4WorkTbl[5].func = mstory2_Scene4ObjIdle;
}

void mstory2_Scene4PlayerProc(void) {
    s32 motIds[8][3] = {
        { 0x40, 0x3E, 0x42 },
        { 0x4B, 0x48, 0x4D },
        { 0x54, 0x52, 0x56 },
        { 0x5D, 0x5B, 0x5F },
        { 0x67, 0x65, 0x69 },
        { 0x70, 0x6E, 0x72 },
        { 0x4B, 0x48, 0x4D },
        { 0x54, 0x52, 0x56 },
    };
    omObjData *obj;
    void *data;

    obj = omAddObj(10, 20, 20, -1, NULL);
    mstory2_scene4WorkTbl[0].obj = obj;
    mstory2_scene4WorkTbl[0].unk_08 = 0;
    mstory2_scene4WorkTbl[0].func = mstory2_Scene4ObjIdle;
    mstory2_scene4WorkTbl[0].unk_0C = 0;
    mstory2_scene4WorkTbl[0].unk_10 = 31;
    obj->model[1] = Hu3DModelRead(omCharModelNoTbl[mstory2_scene4PlayerChr][0] | omCharModelNoTbl[mstory2_scene4PlayerChr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory2_scene4ShadowMdl);
    obj->model[3] = Hu3DModelRead(0x1D000A, 0x2B9);
    obj->model[4] = Hu3DModelRead(0x83, 0x2B9);
    Hu3DModelAttrSet(obj->model[3], 4, 4);
    Hu3DModelAttrSet(obj->model[4], 4, 4);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(mstory2_scene4PlayerChr, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(mstory2_scene4PlayerChr, 1));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(mstory2_scene4PlayerChr, 2));
    omObjMotionRead(obj, 3, motIds[mstory2_scene4PlayerChr][0] | 0x1D0000);
    omObjMotionRead(obj, 4, motIds[mstory2_scene4PlayerChr][1] | 0x1D0000);
    omObjMotionRead(obj, 5, CharMotionDataNumGet(mstory2_scene4PlayerChr, 0x72));
    omObjMotionRead(obj, 6, CharMotionDataNumGet(mstory2_scene4PlayerChr, 0x21));
    omObjMotionRead(obj, 7, CharMotionDataNumGet(mstory2_scene4PlayerChr, 0x33));
    omObjMotionRead(obj, 8, motIds[mstory2_scene4PlayerChr][2] | 0x1D0000);
    omObjMotionRead(obj, 9, CharMotionDataNumGet(mstory2_scene4PlayerChr, 0x9B));
    omObjMotionRead(obj, 10, CharMotionDataNumGet(mstory2_scene4PlayerChr, 0x9C));
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], -120.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], -120.0f, -5.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 162.4f, 0.0f);
    if (mstory2_scene4PlayerChr == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    data = DataRead(CharMotionDataNumGet(mstory2_scene4PlayerChr, 0xA4));
    mstory2_scene4PlayerFaceAnimTbl[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, mstory2_scene4PlayerAnimNameTbl[mstory2_scene4PlayerChr]);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    Hu3DAnimAttrSet(mstory2_scene4PlayerFaceAnimTbl[0], 1, 0);
    Hu3DAnimBankSet(mstory2_scene4PlayerFaceAnimTbl[0], 0);
    mstory2_scene4PlayerFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory2_scene4PlayerFaceAnimTbl[0], 0, mstory2_scene4PlayerAnimNameTbl[mstory2_scene4PlayerChr]);
    data = DataRead(CharMotionDataNumGet(mstory2_scene4PlayerChr, 0xA9));
    mstory2_scene4PlayerFaceAnimTbl[1] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory2_scene4PlayerFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory2_scene4PlayerFaceAnimTbl[0], 0, mstory2_scene4PlayerAnimNameTbl[mstory2_scene4PlayerChr]);
    data = DataRead(CharMotionDataNumGet(mstory2_scene4PlayerChr, 0xAA));
    mstory2_scene4PlayerFaceAnimTbl[2] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory2_HmfAnimSet(obj->model[1], mstory2_scene4PlayerFaceSlot, mstory2_scene4PlayerFaceAnimTbl[0]);
    omPrcSetDestructor(0, mstory2_Scene4PlayerDestroy);
    while (TRUE) {
        mstory2_scene4WorkTbl[0].func(obj);
        HuPrcVSleep();
    }
}

void mstory2_Scene4PlayerDestroy(void) {
}

char *mstory2_scene4PlayerAnimNameTbl[] = { "c000l_0_DEF", "c001l_0_DEF", "c002l_0_DEF", "c003l_0_DEF", "c004l_0_DEF", "c005l_0_DEF", "c300l_0_DEF", "c301l_0_DEF" };
char *mstory2_scene4RivalAnimNameTbl[] = { "c002l_0_DEF", "c001l_0_DEF" };

const char mstory2_scene4ItemHookName[] = "item_hook";

void mstory2_Scene4PlayerCardShow(omObjData *obj) {
    s16 model = obj->model[1];

    HuPrcSleep(20);
    Hu3DModelAttrSet(obj->model[3], 0x4000, 0x4000);
    Hu3DModelHookSet(obj->model[3], obj->model[1], mstory2_scene4ItemHookName);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, 0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    mstory2_MotionEndWait(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    mstory2_MotionEndWait(model);
    mstory2_scene4WorkTbl[0].func = mstory2_Scene4ObjIdle;
    mstory2_scene4WorkTbl[0].unk_08 = 1;
}

void mstory2_Scene4PlayerCardHide(omObjData *obj) {
    s16 model = obj->model[1];
    f32 time;

    Hu3DMotionModelSet(model, obj->motion[4]);
    Hu3DMotionAttrSet(model, 4, 4);
    Hu3DMotionSpeedSet(model, 2.0f);
    Hu3DMotionTimeSet(model, Hu3DMotion[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    Hu3DMotionModelSet(model, obj->motion[3]);
    Hu3DMotionAttrSet(model, 4, 4);
    Hu3DMotionTimeSet(model, Hu3DMotion[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    Hu3DMotionSpeedSet(model, 1.0f);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    Hu3DModelAttrSet(obj->model[3], 0x4000, 0);
    Hu3DModelAttrSet(obj->model[3], 4, 4);
    mstory2_scene4WorkTbl[0].func = mstory2_Scene4PlayerRivalFace;
}

void mstory2_Scene4PlayerRivalFace(omObjData *obj) {
    mstory2_ObjTargetFace(obj, mstory2_scene4WorkTbl[1].obj);
}

void mstory2_Scene4PlayerStep(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory2_scene4WorkTbl[0].unk_0C = 1;
    mstory2_scene4WorkTbl[0].unk_10 = 31;
    mstory2_ObjForwardMove(obj, 3.5f, 15);
    mstory2_HmfAnimSet(obj->model[1], mstory2_scene4PlayerFaceSlot, mstory2_scene4PlayerFaceAnimTbl[2]);
    mstory2_HmfAnimSet(mstory2_scene4WorkTbl[1].obj->model[1], mstory2_scene4RivalFaceSlot, mstory2_scene4RivalFaceAnimTbl[2]);
    mstory2_scene4WorkTbl[0].unk_0C = 0;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[5]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(mstory2_scene4WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[1].obj->motion[4]].motId, 0, 10, 2);
    mstory2_scene4WorkTbl[0].func = mstory2_Scene4ObjIdle;
}

void mstory2_Scene4PlayerKnockBack(omObjData *obj) {
    Vec pos = mstory2_scene4PlayerDestRot1;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x - 5.0f;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    target = tmp;
    mstory2_HmfAnimSet(obj->model[1], mstory2_scene4PlayerFaceSlot, mstory2_scene4PlayerFaceAnimTbl[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[4], Hu3DData[obj->model[1]].pos.x, Hu3DData[obj->model[1]].pos.y, Hu3DData[obj->model[1]].pos.z);
    Hu3DModelAttrSet(obj->model[4], 4, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    mstory2_ObjPosMoveV(obj, &target, 10);
    mstory2_MotionEndWait(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory2_ObjRotMoveV(obj, &pos, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory2_HmfAnimSet(obj->model[1], mstory2_scene4PlayerFaceSlot, mstory2_scene4PlayerFaceAnimTbl[0]);
    mstory2_scene4WorkTbl[0].func = mstory2_Scene4ObjIdle;
}

void mstory2_Scene4PlayerExit(omObjData *obj) {
    Vec pos = mstory2_scene4FrontRot;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 1200.0f;
    target = tmp;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory2_ObjRotMoveV(obj, &pos, 10);
    mstory2_scene4WorkTbl[2].func = mstory2_Scene4TumbleTurn;
    HuAudPlayerFXPlay(mstory2_scene4PlayerChr + 0x275, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 0);
    mstory2_MotionEndWait(obj->model[1]);
    mstory2_scene4WorkTbl[0].unk_08 = 10;
    while (TRUE) {
        if (mstory2_scene4WorkTbl[1].unk_08 != 10) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
    mstory2_scene4WorkTbl[0].unk_0C = 1;
    mstory2_scene4WorkTbl[0].unk_10 = 40;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(10);
    mstory2_ObjPosMoveV(obj, &target, 60);
    mstory2_scene4WorkTbl[0].unk_0C = 0;
    mstory2_scene4WorkTbl[0].func = mstory2_Scene4ObjIdle;
}

void mstory2_Scene4RivalProc(void) {
    s16 chrs[2] = { 2, 1 };
    s32 motIds[2] = { 0x4F, 0x44 };
    omObjData *obj;
    s16 idx;
    void *data;

    idx = mstory2_scene4PlayerChr == 2;
    obj = omAddObj(10, 20, 20, -1, NULL);
    mstory2_scene4WorkTbl[1].obj = obj;
    mstory2_scene4WorkTbl[1].unk_08 = 0;
    mstory2_scene4WorkTbl[1].func = mstory2_Scene4ObjIdle;
    mstory2_scene4WorkTbl[1].unk_0C = 0;
    mstory2_scene4WorkTbl[1].unk_10 = 31;
    if (idx == 0) {
        obj->model[1] = Hu3DModelRead(0x700A0, 0x2A9);
    } else {
        obj->model[1] = Hu3DModelRead(0x300A0, 0x2A9);
    }
    obj->model[2] = Hu3DModelLink(mstory2_scene4ShadowMdl);
    obj->model[3] = Hu3DModelRead(0x83, 0x2B9);
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DModelAttrSet(obj->model[2], 4, 4);
    Hu3DModelAttrSet(obj->model[3], 4, 4);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chrs[idx], 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chrs[idx], 1));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chrs[idx], 2));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chrs[idx], 0x13));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chrs[idx], 0x72));
    omObjMotionRead(obj, 5, motIds[idx] | 0x1D0000);
    omObjMotionRead(obj, 6, CharMotionDataNumGet(chrs[idx], 0x21));
    omObjMotionRead(obj, 7, CharMotionDataNumGet(chrs[idx], 0x33));
    omObjMotionRead(obj, 8, CharMotionDataNumGet(chrs[idx], 0x2F));
    if (mstory2_scene4PlayerChr == 2) {
        omObjMotionRead(obj, 9, 0x1D0045);
    }
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    mstory2_scene4RivalPos = mstory2_scene4RivalStartPos;
    Hu3DModelPosSet(obj->model[1], mstory2_scene4RivalPos.x, mstory2_scene4RivalPos.y, mstory2_scene4RivalPos.z);
    Hu3DModelPosSet(obj->model[2], mstory2_scene4RivalPos.x, mstory2_scene4RivalPos.y - -5.0f, mstory2_scene4RivalPos.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, -14.48f, 0.0f);
    data = DataRead(CharMotionDataNumGet(chrs[idx], 0xA4));
    mstory2_scene4RivalFaceAnimTbl[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, mstory2_scene4RivalAnimNameTbl[idx]);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    Hu3DAnimAttrSet(mstory2_scene4RivalFaceAnimTbl[0], 1, 0);
    Hu3DAnimBankSet(mstory2_scene4RivalFaceAnimTbl[0], 0);
    mstory2_scene4RivalFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory2_scene4RivalFaceAnimTbl[0], 0, mstory2_scene4RivalAnimNameTbl[idx]);
    data = DataRead(CharMotionDataNumGet(chrs[idx], 0xA9));
    mstory2_scene4RivalFaceAnimTbl[1] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory2_scene4RivalFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory2_scene4RivalFaceAnimTbl[0], 0, mstory2_scene4RivalAnimNameTbl[idx]);
    data = DataRead(CharMotionDataNumGet(chrs[idx], 0xAA));
    mstory2_scene4RivalFaceAnimTbl[2] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory2_HmfAnimSet(obj->model[1], mstory2_scene4RivalFaceSlot, mstory2_scene4RivalFaceAnimTbl[0]);
    omPrcSetDestructor(0, mstory2_Scene4RivalDestroy);
    while (TRUE) {
        mstory2_scene4WorkTbl[1].func(obj);
        HuPrcVSleep();
    }
}

void mstory2_Scene4RivalDestroy(void) {
}

void mstory2_Scene4RivalStep(omObjData *obj) {
    mstory2_scene4WorkTbl[1].unk_0C = 1;
    mstory2_scene4WorkTbl[1].unk_10 = 31;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory2_ObjForwardMove(obj, 4.5f, 15);
    mstory2_scene4WorkTbl[1].unk_0C = 0;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory2_scene4WorkTbl[1].func = mstory2_Scene4ObjIdle;
    mstory2_scene4WorkTbl[0].func = mstory2_Scene4PlayerStep;
}

void mstory2_Scene4RivalKnockBack(omObjData *obj) {
    Vec pos = mstory2_scene4RivalDestRot2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x + 5.0f;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    target = tmp;
    mstory2_HmfAnimSet(obj->model[1], mstory2_scene4RivalFaceSlot, mstory2_scene4RivalFaceAnimTbl[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[3], Hu3DData[obj->model[1]].pos.x, Hu3DData[obj->model[1]].pos.y, Hu3DData[obj->model[1]].pos.z);
    Hu3DModelAttrSet(obj->model[3], 4, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    mstory2_ObjPosMoveV(obj, &target, 10);
    mstory2_MotionEndWait(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory2_ObjRotMoveV(obj, &pos, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory2_HmfAnimSet(obj->model[1], mstory2_scene4RivalFaceSlot, mstory2_scene4RivalFaceAnimTbl[0]);
    mstory2_scene4WorkTbl[1].func = mstory2_Scene4ObjIdle;
}

void mstory2_Scene4RivalExit(omObjData *obj) {
    Vec pos = mstory2_scene4FrontRot;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 1200.0f;
    target = tmp;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory2_ObjRotMoveV(obj, &pos, 10);
    HuAudPlayerFXPlay(mstory2_scene4RivalChr + 0x275, 1);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 0);
    mstory2_MotionEndWait(obj->model[1]);
    mstory2_scene4WorkTbl[1].unk_08 = 10;
    while (TRUE) {
        if (mstory2_scene4WorkTbl[0].unk_08 != 10) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
    mstory2_scene4WorkTbl[1].unk_0C = 1;
    mstory2_scene4WorkTbl[1].unk_10 = 40;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(10);
    mstory2_ObjPosMoveV(obj, &target, 60);
    mstory2_scene4WorkTbl[1].unk_0C = 0;
    mstory2_scene4WorkTbl[0].func = mstory2_Scene4ObjIdle;
}

void mstory2_Scene4RivalLuigiPose(omObjData *obj) {
    Hu3DMotionShiftSet(mstory2_scene4WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[1].obj->motion[9]].motId, 0, 10, 0);
    mstory2_MotionEndWait(obj->model[1]);
    mstory2_scene4WorkTbl[1].func = mstory2_Scene4ObjIdle;
}

const Vec mstory2_scene4PlayerDestRot1 = { 0.0f, 180.0f, 0.0f };

const Vec mstory2_scene4FrontRot = { 0.0f, 0.0f, 0.0f };

const Vec mstory2_scene4RivalDestRot2 = { 0.0f, -180.0f, 0.0f };

const char mstory2_scene4TumbleAnimName[] = "c204n_0_DEF";

void mstory2_Scene4TumbleProc(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(10, 20, 20, -1, NULL);
    mstory2_scene4WorkTbl[2].obj = obj;
    mstory2_scene4WorkTbl[2].unk_08 = 0;
    obj->model[1] = Hu3DModelRead(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory2_scene4ShadowMdl);
    omObjMotionRead(obj, 0, 0xA0076);
    omObjMotionRead(obj, 1, 0x1D0029);
    omObjMotionRead(obj, 2, 0x1D002A);
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    mstory2_scene4TumblePos = mstory2_scene4TumbleStartPos;
    Hu3DModelPosSet(obj->model[1], mstory2_scene4TumblePos.x, mstory2_scene4TumblePos.y, mstory2_scene4TumblePos.z);
    Hu3DModelPosSet(obj->model[2], mstory2_scene4TumblePos.x, -5.0f, mstory2_scene4TumblePos.z);
    Hu3DModelRotSet(obj->model[1], 20.0f, 320.0f, 0.0f);
    data = DataRead(0xA007E);
    mstory2_scene4TumbleFaceAnimTbl[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, mstory2_scene4TumbleAnimName);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    Hu3DAnimAttrSet(mstory2_scene4TumbleFaceAnimTbl[0], 1, 0);
    Hu3DAnimBankSet(mstory2_scene4TumbleFaceAnimTbl[0], 0);
    mstory2_scene4TumbleFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory2_scene4TumbleFaceAnimTbl[0], 0, mstory2_scene4TumbleAnimName);
    data = DataRead(0xA0083);
    mstory2_scene4TumbleFaceAnimTbl[1] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory2_scene4TumbleFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory2_scene4TumbleFaceAnimTbl[0], 0, mstory2_scene4TumbleAnimName);
    data = DataRead(0xA0080);
    mstory2_scene4TumbleFaceAnimTbl[2] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory2_HmfAnimSet(obj->model[1], mstory2_scene4TumbleFaceSlot, mstory2_scene4TumbleFaceAnimTbl[0]);
    omPrcSetDestructor(0, mstory2_Scene4TumbleDestroy);
    mstory2_scene4WorkTbl[2].func = mstory2_Scene4ObjIdle;
    while (TRUE) {
        mstory2_scene4WorkTbl[2].func(obj);
        HuPrcVSleep();
    }
}

void mstory2_Scene4TumbleDestroy(void) {
}

void mstory2_Scene4TumbleHop1(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec target = mstory2_scene4TumbleDestRot2;
    f32 y;
    s16 i;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    mstory2_HmfAnimSet(model, mstory2_scene4TumbleFaceSlot, mstory2_scene4TumbleFaceAnimTbl[1]);
    for (i = 0; i < 13; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        Hu3DData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    mstory2_ObjRotMoveV(obj, &target, 5);
    mstory2_HmfAnimSet(model, mstory2_scene4TumbleFaceSlot, mstory2_scene4TumbleFaceAnimTbl[0]);
    Hu3DMotionShiftSet(mstory2_scene4WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[1].obj->motion[8]].motId, 0, 10, 0);
    HuPrcSleep(mstory2_scene4PlayerChr != 2 ? 30 : 35);
    HuAudFXVolSet(CharFXPlay(0x28F, mstory2_scene4RivalChr), 0x60);
    mstory2_scene4WorkTbl[2].func = mstory2_Scene4TumbleRivalFace;
    mstory2_scene4WorkTbl[2].unk_08 = 5;
}

void mstory2_Scene4TumbleRivalFace(omObjData *obj) {
    mstory2_ObjTargetFace(obj, mstory2_scene4WorkTbl[1].obj);
}

void mstory2_Scene4TumbleLand(omObjData *obj) {
    while (TRUE) {
        if (Hu3DData[obj->model[1]].pos.y > 100.0f) {
            Hu3DData[obj->model[1]].pos.y -= 2.0f;
            HuPrcVSleep();
        } else {
            break;
        }
    }
    Hu3DData[obj->model[1]].pos.y = 100.0f;
    mstory2_scene4WorkTbl[2].func = mstory2_Scene4ObjIdle;
}

void mstory2_Scene4TumbleHop2(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec target = mstory2_scene4TumbleDestRot3;
    f32 y;
    s16 i;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    mstory2_HmfAnimSet(model, mstory2_scene4TumbleFaceSlot, mstory2_scene4TumbleFaceAnimTbl[1]);
    Hu3DMotionShiftSet(mstory2_scene4WorkTbl[2].obj->model[1], Hu3DData[mstory2_scene4WorkTbl[2].obj->motion[0]].motId, 0, 10, 2);
    for (i = 0; i < 15; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        Hu3DData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    mstory2_ObjRotMoveV(obj, &target, 10);
    mstory2_scene4WorkTbl[2].func = mstory2_Scene4ObjIdle;
    mstory2_scene4WorkTbl[2].unk_08 = 1;
}

void mstory2_Scene4TumbleTurn(omObjData *obj) {
    Vec pos = mstory2_scene4TumbleDestRot4;

    mstory2_HmfAnimSet(obj->model[1], mstory2_scene4TumbleFaceSlot, mstory2_scene4TumbleFaceAnimTbl[0]);
    mstory2_ObjRotMoveV(obj, &pos, 10);
    while (TRUE) {
        mstory2_ObjTargetFace(mstory2_scene4WorkTbl[2].obj, mstory2_scene4WorkTbl[0].obj);
        HuPrcVSleep();
    }
}

void mstory2_Scene4TumblePlayerFace(omObjData *obj) {
    mstory2_ObjTargetFace(obj, mstory2_scene4WorkTbl[0].obj);
}

void mstory2_Scene4StarProc(void) {
    omObjData *obj;

    obj = omAddObj(0xA, 20, 20, -1, NULL);
    mstory2_scene4WorkTbl[3].obj = obj;
    mstory2_scene4WorkTbl[3].unk_08 = 0;
    obj->model[1] = Hu3DModelRead(0xA0122, 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory2_scene4ShadowMdl);
    AuraCreate(obj->model[1]);
    omObjMotionRead(obj, 0, 0xA0123);
    omObjMotionRead(obj, 1, 0xA0125);
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    mstory2_scene4StarPos = mstory2_scene4StarStartPos;
    Hu3DModelPosSet(obj->model[1], mstory2_scene4StarPos.x, mstory2_scene4StarPos.y, mstory2_scene4StarPos.z);
    Hu3DModelPosSet(obj->model[2], mstory2_scene4StarPos.x, -5.0f, mstory2_scene4StarPos.z);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    omPrcSetDestructor(0, mstory2_Scene4StarDestroy);
    mstory2_scene4WorkTbl[3].func = mstory2_Scene4ObjIdle;
    while (1) {
        mstory2_scene4WorkTbl[3].func(obj);
        HuPrcVSleep();
    }
}

void mstory2_Scene4StarDestroy(void) {
}

void mstory2_Scene4StarFloatProc(void) {
    f32 angle = 0.0f;
    omObjData *obj = mstory2_scene4WorkTbl[3].obj;
    Vec pos;
    f32 ofs;

    pos.y = Hu3DData[obj->model[1]].pos.y;
    while (TRUE) {
        pos.x = Hu3DData[obj->model[1]].pos.x;
        pos.z = Hu3DData[obj->model[1]].pos.z;
        ofs = sindf(angle) * 25.0f + 25.0f;
        angle += 2.0f;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        if (mstory2_scene4StarFloatStopF != 1) {
            Hu3DModelPosSet(obj->model[1], pos.x, ofs + pos.y, pos.z);
        }
        HuPrcVSleep();
    }
}

void mstory2_Scene4StarRivalFace(omObjData *obj) {
    mstory2_ObjTargetFace(obj, mstory2_scene4WorkTbl[1].obj);
}

void mstory2_Scene4StarTurn(omObjData *obj) {
    Vec pos = mstory2_scene4FrontRot;

    mstory2_ObjRotMoveV(obj, &pos, 10);
    mstory2_scene4WorkTbl[3].func = mstory2_Scene4ObjIdle;
}

void mstory2_Scene4StarTumbleTurn(omObjData *obj) {
    Vec pos = mstory2_scene4TumbleDestRot5;

    mstory2_ObjRotMoveV(mstory2_scene4WorkTbl[2].obj, &pos, 10);
    mstory2_scene4WorkTbl[3].func = mstory2_Scene4ObjIdle;
}

void mstory2_Scene4StampProc(void) {
    omObjData *obj;

    obj = omAddObj(0xA, 20, 20, -1, NULL);
    mstory2_scene4WorkTbl[4].obj = obj;
    mstory2_scene4WorkTbl[4].unk_08 = 0;
    mstory2_scene4WorkTbl[4].func = mstory2_Scene4ObjIdle;
    obj->model[1] = Hu3DModelRead(0x1D0006, 0x20299);
    obj->model[2] = EffectCreate(0xB0004, 0x6A9);
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    mstory2_scene4StampPos = mstory2_scene4StampStartPos;
    Hu3DModelPosSet(obj->model[1], mstory2_scene4StampPos.x, mstory2_scene4StampPos.y, mstory2_scene4StampPos.z);
    EffectParamSet(obj->model[2], 4.0f, 20.0f, 4.0f);
    EffectRangeSet(obj->model[2], 60.0f);
    Hu3DParticleAttrSet(obj->model[2], 1, 0);
    Hu3DModelAttrSet(obj->model[2], 4, 4);
    omPrcSetDestructor(0, mstory2_Scene4StampDestroy);
    while (1) {
        mstory2_scene4WorkTbl[4].func(obj);
        HuPrcVSleep();
    }
}

void mstory2_Scene4StampDestroy(void) {
}

const Vec mstory2_scene4TumbleDestRot2 = { 0.0f, 167.0f, 0.0f };

const Vec mstory2_scene4TumbleDestRot3 = { 0.0f, -135.0f, 0.0f };

const Vec mstory2_scene4TumbleDestRot4 = { 0.0f, -53.39f, 0.0f };

const Vec mstory2_scene4TumbleDestRot5 = { 0.0f, -53.390015f, 0.0f };
