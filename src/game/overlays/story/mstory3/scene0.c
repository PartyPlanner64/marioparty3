#include "common.h"
#include "game/hmfmath.h"
#include "mstory3.h"

typedef struct MstoryPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ u16 flags;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec *points;
    /* 0x0C */ f32 (*intervals)[2];
} MstoryPath; // sizeof 0x10

extern const Vec mstory3_scene0PlayerDestRot3;
extern const Vec mstory3_scene0PlayerDestRot4;
extern const Vec mstory3_scene0PlayerDestRot5;
extern const Vec mstory3_scene0PlayerDestRot6;
extern const Vec mstory3_scene0WaluigiDestRot1;
extern const Vec mstory3_scene0WaluigiDestPos1;
extern const Vec mstory3_scene0PlayerDestRot7;
extern const Vec mstory3_scene0PlayerDestRot8;
extern const Vec mstory3_scene0PlayerDestRot9;
extern const Vec mstory3_scene0PlayerDestRot10;
extern const Vec mstory3_scene0PlayerDestRot11;
extern const Vec mstory3_scene0TumbleDestRot5;
extern const Vec mstory3_scene0TumbleDestRot6;
extern const Vec mstory3_scene0TumbleDestPos1;
extern const Vec mstory3_scene0TumbleDestPos2;
extern const Vec mstory3_scene0TumbleDestRot7;
extern const Vec mstory3_scene0TumbleDestRot8;
extern const Vec mstory3_scene0TumbleDestRot9;
extern const Vec mstory3_scene0TumbleDestRot10;
extern const Vec mstory3_scene0TumbleDestRot11;
extern const Vec mstory3_scene0TumbleDestRot12;
extern const Vec mstory3_scene0StarDestRot3;
extern const Vec mstory3_scene0StarDestRot4;
extern const Vec mstory3_scene0StarDestRot5;
extern const Vec mstory3_scene0StarDestRot6;
extern const Vec mstory3_scene0StarDestRot7;
extern const Vec mstory3_scene0StarDestRot8;
extern const Vec mstory3_scene0StarDestRot9;
extern const Vec mstory3_scene0StarDestRot10;
extern const Vec mstory3_scene0KoopaDestRot1;
extern const Vec mstory3_scene0KoopaDestRot2;
extern const Vec mstory3_scene0KoopaDestPos1;
extern const Vec mstory3_scene0KoopaDestPos2;
extern const Vec mstory3_scene0KoopaJrADestPos0;
extern Vec mstory3_scene0StampBPathA[];
extern Vec mstory3_scene0StampPathA[];
extern Vec mstory3_scene0StampPathB[];
extern Vec mstory3_scene0StampBPathB[];
extern s16 mstory3_scene1PlayerChr[];
extern s16 mstory3_scene0CloudStarTimeTbl[];
extern Mstory3ObjWork mstory3_scene0WorkTbl[11];
extern s16 mstory3_scene0ShadowMdl;
extern s16 mstory3_scene0WaluigiFaceAnimTbl[5];
extern s16 mstory3_scene0WaluigiFaceSlot;
extern s16 mstory3_scene0PlayerFaceSlot;
extern s16 mstory3_scene0TumbleFaceSlot;
extern s16 mstory3_scene0TumbleFaceAnimTbl[3];
extern s16 mstory3_scene0StampBSpinF;
extern s16 mstory3_scene0PlayerChr;
extern s16 mstory3_scene0PlayerFaceAnimTbl[5];
extern char *mstory3_scene0PlayerAnimNameTbl[];
extern s32 omCharModelNoTbl[][6];

MstoryPath *mstory3_Scene0PathCreate(Vec *points, s32 flags);
void mstory3_Scene0PathPosGet(MstoryPath *path, f32 time, Vec *result);
void mstory3_Scene0PathKill(MstoryPath *path);
void mstory3_Scene0ObjIdle(omObjData *obj);
void mstory3_Scene0WaluigiDestroy(void);
void mstory3_Scene0CloudVanish(omObjData *obj);
void mstory3_Scene0PlayerWaluigiFace2(omObjData *obj);
void mstory3_Scene0CloudStarUpdate(omObjData *obj);
void mstory3_Scene0StarDestroy(void);
void mstory3_Scene0CloudDestroy(void);
void mstory3_WinCreate(void);
void mstory3_Scene0ObjSeLoopProc(void);
void mstory3_Scene0EventProc(void);
void mstory3_Scene0PlayerProc(void);
void mstory3_Scene0DaisyProc(void);
void mstory3_Scene0WaluigiProc(void);
void mstory3_Scene0TumbleProc(void);
void mstory3_Scene0StarProc(void);
void mstory3_Scene0StarFloatProc(void);
void mstory3_Scene0KoopaProc(void);
void mstory3_Scene0KoopaJrAProc(void);
void mstory3_Scene0KoopaJrBProc(void);
void mstory3_Scene0StampProc(void);
void mstory3_Scene0StampBSpinProc(void);
void mstory3_Scene0CloudProc(void);
void mstory3_BackMotionStart(void);
void mstory3_BackMotionReverse(void);
void mstory3_ObjPosMoveV(omObjData *obj, const Vec *pos, s32 frames);
void mstory3_HmfAnimSet(s16 model, s16 arg1, s16 arg2);
void mstory3_ObjPosMoveEx(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void mstory3_ObjRotMoveV(omObjData *obj, const Vec *pos, s32 frames);
void mstory3_ObjForwardMove(omObjData *obj, f32 speed, s16 frames);
void mstory3_ObjBackwardMove(omObjData *obj, f32 speed, s16 frames);
void mstory3_MotionEndWait(s16 model);
void mstory3_ObjTargetFace(omObjData *obj, omObjData *target);
void mstory3_ObjRotMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void mstory3_StampCardStart(s32 arg0);
s32 mstory3_StampCardDoneCheck(void);
void mstory3_WinOpen(void);
void mstory3_WinMesExec(s32 mess);
void mstory3_WinClose(void);
void mstory3_Scene0EventIntroExec(omObjData *obj);
void mstory3_Scene0EventExec(omObjData *obj);
void mstory3_Scene0PlayerStampExec(omObjData *obj);
void mstory3_Scene0DaisyExit(omObjData *obj);
void mstory3_Scene0TumbleEnter(omObjData *obj);
void mstory3_Scene0TumbleHop1(omObjData *obj);
void mstory3_Scene0StampFlyExec(omObjData *obj);
void mstory3_Scene0StampBAppear(omObjData *obj);
void mstory3_Scene0PlayerWaluigiFace(omObjData *obj);
void mstory3_Scene0PlayerLookAround(omObjData *obj);
void mstory3_Scene0TumbleWaluigiFace(omObjData *obj);
void mstory3_Scene0TumbleWaluigiFace2(omObjData *obj);
void mstory3_Scene0StarTurn1(omObjData *obj);
void mstory3_Scene0StarWaluigiFace2(omObjData *obj);
void mstory3_Scene0StarWaluigiFace(omObjData *obj);
void mstory3_Scene0StarTurn3(omObjData *obj);
void mstory3_Scene0KoopaTurn1(omObjData *obj);
void mstory3_Scene0KoopaWaluigiFace(omObjData *obj);
void mstory3_Scene0KoopaAttack(omObjData *obj);
void mstory3_Scene0KoopaJrACarryExit(omObjData *obj);
void mstory3_Scene0StampBExit(omObjData *obj);
void mstory3_Scene0WaluigiStruggleEnd(omObjData *obj);
void mstory3_Scene0PlayerTurn2(omObjData *obj);
void mstory3_Scene0TumbleTurn1(omObjData *obj);
void mstory3_Scene0StarTurn2(omObjData *obj);
void mstory3_Scene0KoopaFaceAll(omObjData *obj);
void mstory3_Scene0KoopaEnter(omObjData *obj);
void mstory3_Scene0StampBFlyExec(omObjData *obj);
void mstory3_Scene0TumbleShake(omObjData *obj);
void mstory3_Scene0StarShake(omObjData *obj);
void mstory3_Scene0PlayerTurn4(omObjData *obj);
void mstory3_Scene0TumbleTurn2(omObjData *obj);
void mstory3_Scene0StarTurn4(omObjData *obj);
void mstory3_Scene0KoopaTurn2(omObjData *obj);
void mstory3_Scene0StampBApproach(omObjData *obj);
void mstory3_Scene0TumbleWalk(omObjData *obj);
void mstory3_Scene0KoopaStep(omObjData *obj);
void mstory3_Scene0StarLookAround(omObjData *obj);
void mstory3_Scene0TumbleLookAround(omObjData *obj);
void mstory3_Scene0PlayerStepBack2(omObjData *obj);
void mstory3_Scene0WaluigiTurn(omObjData *obj);
void mstory3_Scene0EventEndExec(omObjData *obj);
void mstory3_BackRotExec(void);
void mstory3_ObjPosMoveAccel(omObjData *obj, const Vec *target, s32 frames, s32 faceDir);
void mstory3_Scene0KoopaApproach(omObjData *obj);
void mstory3_Scene0CloudAppear(omObjData *obj);
void mstory3_Scene0WaluigiStruggle(omObjData *obj);
void mstory3_Scene0PlayerReactTurn(omObjData *obj);
void mstory3_Scene0StarReactTurn(omObjData *obj);
void mstory3_Scene0TumbleReactTurn(omObjData *obj);
void mstory3_Scene0KoopaPose(omObjData *obj);
void mstory3_Scene0WaluigiExit(omObjData *obj);
void mstory3_Scene0PlayerDash(omObjData *obj);
void mstory3_Scene0TumbleDash(omObjData *obj);
void mstory3_Scene0StarDash(omObjData *obj);
void mstory3_Scene0KoopaJrAEnter(omObjData *obj);
void mstory3_Scene0KoopaJrBEnter(omObjData *obj);
void mstory3_Scene0KoopaJrALift(omObjData *obj);
void mstory3_Scene0KoopaJrBCarry(omObjData *obj);
void mstory3_Scene0KoopaJrACarry(omObjData *obj);
void mstory3_WinMesChrNameExec(s32 mess);
void mstory3_SceneEnd(void);

Vec mstory3_scene0EventRot0 = { 0.0f, 90.0f, 0.0f };
Vec mstory3_scene0EventRot1 = { 0.0f, 0.0f, 0.0f };
Vec mstory3_scene0EventRot2 = { 0.0f, 0.0f, 0.0f };
Vec mstory3_scene0EventRot3 = { 0.0f, -157.81f, 0.0f };

MstoryPath *mstory3_Scene0PathCreate(Vec *points, s32 flags) {
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

void mstory3_Scene0PathPosGet(MstoryPath *path, f32 time, Vec *result) {
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

void mstory3_Scene0PathKill(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void mstory3_Scene0Create(void) {
    mstory3_scene0PlayerChr = GwStory.unk1;
    mstory3_WinCreate();
    mstory3_scene0ShadowMdl = Hu3DModelRead(9, 0x2B9);
    omAddPrcObj(mstory3_Scene0PlayerProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory3_Scene0DaisyProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory3_Scene0WaluigiProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory3_Scene0TumbleProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory3_Scene0StarProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory3_Scene0KoopaProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory3_Scene0KoopaJrAProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory3_Scene0KoopaJrBProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory3_Scene0StampProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory3_Scene0CloudProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory3_Scene0EventProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory3_Scene0StarFloatProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory3_Scene0StampBSpinProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory3_Scene0ObjSeLoopProc, 0x1001, 0x800, 0);
    HuPrcVSleep();
    Hu3DModelAttrSet(mstory3_scene0ShadowMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void mstory3_Scene0ObjIdle(omObjData *obj) {
}

void mstory3_Scene0ObjSeLoopProc(void) {
    s16 seNo;
    s8 vol;
    f32 z;

    while (TRUE) {
        if (mstory3_scene0WorkTbl[0].unk_0C == 1 && Hu3DData[mstory3_scene0WorkTbl[0].obj->model[1]].motTime == 0.0f) {
            CharFXPlay((s16)mstory3_scene0WorkTbl[0].unk_10, mstory3_scene0PlayerChr);
        }
        if (mstory3_scene0WorkTbl[2].unk_0C == 1 && Hu3DData[mstory3_scene0WorkTbl[2].obj->model[1]].motTime == 0.0f) {
            seNo = CharFXPlay((s16)mstory3_scene0WorkTbl[2].unk_10, 6);
            z = Hu3DData[mstory3_scene0WorkTbl[2].obj->model[1]].pos.z;
            if (z <= 0.0f) {
                vol = z / 15.0f + 127.0f;
            } else {
                vol = 127;
            }
            HuAudFXVolSet(seNo, vol);
        }
        if (mstory3_scene0WorkTbl[1].unk_0C == 1 && Hu3DData[mstory3_scene0WorkTbl[1].obj->model[1]].motTime == 0.0f) {
            CharFXPlay((s16)mstory3_scene0WorkTbl[1].unk_10, 7);
        }
        HuPrcVSleep();
    }
}

void mstory3_Scene0EventDestroy(void) {
}

void mstory3_Scene0EventProc(void) {
    omObjData *obj;

    obj = omAddObj(0xA, 0, 0, -1, NULL);
    mstory3_scene0WorkTbl[10].obj = obj;
    mstory3_scene0WorkTbl[10].unk_08 = 0;
    mstory3_scene0WorkTbl[10].func = mstory3_Scene0EventIntroExec;
    omPrcSetDestructor(0, mstory3_Scene0EventDestroy);
    while (1) {
        mstory3_scene0WorkTbl[10].func(obj);
        HuPrcVSleep();
    }
}

const Vec mstory3_scene0StarDestPos0 = { -100.0f, 0.0f, 350.0f };

const Vec mstory3_scene0StarDestPos1 = { -100.0f, 0.0f, 150.0f };

const Vec mstory3_scene0PlayerDestRot0 = { 0.0f, 162.4f, 0.0f };

const Vec mstory3_scene0StarDestRot0 = { 30.0f, -20.0f, 0.0f };

const Vec mstory3_scene0TumbleDestRot0 = { 0.0f, 225.0f, 0.0f };

const Vec mstory3_scene0FrontRot = { 0.0f, 0.0f, 0.0f };

const Vec mstory3_scene0TumbleDestRot1 = { -5.0f, 300.0f, 0.0f };

const Vec mstory3_scene0TumbleDestRot2 = { -30.0f, 260.0f, 0.0f };

const Vec mstory3_scene0TumbleDestRot3 = { 0.0f, 320.0f, 0.0f };

const Vec mstory3_scene0PlayerDestRot1 = { 0.0f, 0.0f, 0.0f };

const Vec mstory3_scene0StarDestRot1 = { 0.0f, -26.5f, 0.0f };

const Vec mstory3_scene0StarDestRot2 = { 0.0f, 0.0f, 0.0f };

const Vec mstory3_scene0PlayerDestRot2 = { 0.0f, 180.0f, 0.0f };

void mstory3_Scene0EventIntroExec(omObjData *obj) {
    s16 seNo;

    HuPrcSleep(30);
    CharFXPlay(0x26B, 7);
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0TumbleEnter;
    HuPrcSleep(70);
    mstory3_scene0WorkTbl[1].func = mstory3_Scene0DaisyExit;
    while (TRUE) {
        if (mstory3_scene0WorkTbl[3].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    mstory3_scene0WorkTbl[3].unk_08 = 0;
    mstory3_HmfAnimSet(mstory3_scene0WorkTbl[3].obj->model[1], mstory3_scene0TumbleFaceSlot, mstory3_scene0TumbleFaceAnimTbl[1]);
    mstory3_WinOpen();
    mstory3_WinMesExec(0x5A5A);
    mstory3_WinClose();
    mstory3_HmfAnimSet(mstory3_scene0WorkTbl[3].obj->model[1], mstory3_scene0TumbleFaceSlot, mstory3_scene0TumbleFaceAnimTbl[0]);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[0].obj, &mstory3_scene0PlayerDestRot0, 10);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[0]].motId, 0, 10, 0);
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[4].obj, &mstory3_scene0StarDestRot0, 10);
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[3].obj, &mstory3_scene0TumbleDestRot0, 10);
    HuAudFXPlay(0x159);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[4].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[4].obj->motion[1]].motId, 0, 10, 2);
    mstory3_WinOpen();
    mstory3_WinMesExec(0x5A5B);
    mstory3_WinClose();
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[4].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[4].obj->motion[0]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[4].obj, &mstory3_scene0FrontRot, 10);
    mstory3_scene0WorkTbl[8].func = mstory3_Scene0StampFlyExec;
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[3].obj, &mstory3_scene0TumbleDestRot1, 10);
    while (TRUE) {
        if (mstory3_scene0WorkTbl[8].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0PlayerStampExec;
    HuPrcSleep(40);
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[3].obj, &mstory3_scene0TumbleDestRot2, 50);
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[3].obj, &mstory3_scene0TumbleDestRot3, 40);
    while (TRUE) {
        if (mstory3_scene0WorkTbl[0].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    mstory3_scene0WorkTbl[0].unk_08 = 0;
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0ObjIdle;
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[0].obj, &mstory3_scene0PlayerDestRot1, 10);
    HuAudSeqPlay(0x72);
    mstory3_HmfAnimSet(mstory3_scene0WorkTbl[0].obj->model[1], mstory3_scene0PlayerFaceSlot, mstory3_scene0PlayerFaceAnimTbl[3]);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[7]].motId, 0, 10, 0);
    mstory3_MotionEndWait(mstory3_scene0WorkTbl[0].obj->model[1]);
    seNo = CharFXPlay(0x262, mstory3_scene0PlayerChr);
    HuPrcSleep(30);
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[4].obj, &mstory3_scene0StarDestRot1, 3);
    mstory3_ObjPosMoveV(mstory3_scene0WorkTbl[4].obj, &mstory3_scene0StarDestPos0, 5);
    HuAudFXPlay(0x219);
    HuAudFXStop(seNo);
    mstory3_HmfAnimSet(mstory3_scene0WorkTbl[0].obj->model[1], mstory3_scene0PlayerFaceSlot, mstory3_scene0PlayerFaceAnimTbl[1]);
    Hu3DModelAttrSet(mstory3_scene0WorkTbl[0].obj->model[4], HU3D_ATTR_DISPOFF, 0);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[8]].motId, 0, 10, 0);
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[4].obj, &mstory3_scene0StarDestRot2, 3);
    mstory3_scene0WorkTbl[4].unk_08 = 0;
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0TumbleHop1;
    mstory3_ObjPosMoveEx(mstory3_scene0WorkTbl[4].obj, &mstory3_scene0StarDestPos1, 10, 0);
    mstory3_MotionEndWait(mstory3_scene0WorkTbl[0].obj->model[1]);
    HuAudSeqPlay(0x26);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[0].obj, &mstory3_scene0PlayerDestRot2, 10);
    mstory3_HmfAnimSet(mstory3_scene0WorkTbl[0].obj->model[1], mstory3_scene0PlayerFaceSlot, mstory3_scene0PlayerFaceAnimTbl[0]);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[0]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[8].func = mstory3_Scene0StampBAppear;
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[4].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[4].obj->motion[1]].motId, 0, 10, 2);
    mstory3_WinOpen();
    mstory3_WinMesExec(0x5A5D);
    mstory3_WinClose();
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[4].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[4].obj->motion[0]].motId, 0, 10, 2);
    while (TRUE) {
        if (mstory3_scene0WorkTbl[8].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    mstory3_scene0WorkTbl[8].unk_08 = 0;
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[0].obj, &mstory3_scene0FrontRot, 10);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[7]].motId, 0, 10, 0);
    mstory3_MotionEndWait(mstory3_scene0WorkTbl[0].obj->model[1]);
    mstory3_scene0WorkTbl[10].func = mstory3_Scene0EventExec;
}

const Vec mstory3_scene0WaluigiDestPos0 = { 180.0f, 0.0f, 780.0f };

const Vec mstory3_scene0WaluigiDestRot0 = { 0.0f, -161.66f, 0.0f };

const Vec mstory3_scene0KoopaDestRot0 = { 0.0f, 60.0f, 0.0f };

void mstory3_Scene0EventExec(omObjData *obj) {
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0PlayerTurn2;
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0TumbleTurn1;
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0StarTurn2;
    HuAudFXPlay(0x29C);
    mstory3_WinOpen();
    mstory3_WinMesExec(0x5A5E);
    mstory3_WinClose();
    mstory3_scene0WorkTbl[8].func = mstory3_Scene0KoopaFaceAll;
    mstory3_scene0WorkTbl[5].func = mstory3_Scene0KoopaEnter;
    while (TRUE) {
        if (mstory3_scene0WorkTbl[5].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    mstory3_scene0WorkTbl[5].unk_08 = 0;
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[4].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[4].obj->motion[3]].motId, 0, 10, 2);
    mstory3_WinOpen();
    mstory3_WinMesExec(0x5A5F);
    mstory3_WinClose();
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[4].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[4].obj->motion[0]].motId, 0, 10, 2);
    HuAudFXPlay(0x29D);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[5].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[5].obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(5);
    mstory3_scene0WorkTbl[8].func = mstory3_Scene0StampBFlyExec;
    mstory3_WinOpen();
    mstory3_WinMesExec(0x5A60);
    mstory3_WinClose();
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[9]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[5].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[5].obj->motion[3]].motId, 0, 10, 2);
    HuPrcSleep(30);
    mstory3_scene0WorkTbl[3].unk_08 = 0;
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0TumbleShake;
    while (TRUE) {
        if (mstory3_scene0WorkTbl[3].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    mstory3_scene0WorkTbl[3].unk_08 = 0;
    HuAudFXPlay(0x2AA);
    mstory3_WinOpen();
    mstory3_WinMesExec(0x5A61);
    mstory3_WinClose();
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[4].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[4].obj->motion[3]].motId, 0, 10, 2);
    mstory3_WinOpen();
    HuAudSeqFadeOut(30);
    mstory3_WinMesExec(0x5A62);
    mstory3_WinClose();
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[4].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[4].obj->motion[0]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[3].unk_08 = 1;
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0TumbleShake;
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0StarShake;
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[10]].motId, 0, 10, 0);
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[5].obj, &mstory3_scene0KoopaDestRot0, 10);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[5].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[5].obj->motion[6]].motId, 0, 10, 0);
    mstory3_MotionEndWait(mstory3_scene0WorkTbl[5].obj->model[1]);
    HuAudFXVolSet(CharFXPlay(0x2BD, 6), 80);
    mstory3_WinOpen();
    mstory3_WinMesExec(0x5A63);
    HuAudSeqPlay(0x28);
    mstory3_WinClose();
    HuPrcSleep(10);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[5].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[5].obj->motion[0]].motId, 0, 10, 2);
    Hu3DModelAttrSet(mstory3_scene0WorkTbl[2].obj->model[1], HU3D_ATTR_DISPOFF, 0);
    Hu3DModelAttrSet(mstory3_scene0WorkTbl[2].obj->model[2], HU3D_ATTR_DISPOFF, 0);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[3]].motId, 0, 10, 0);
    HuPrcSleep(5);
    HuAudFXPlay(0x228);
    mstory3_BackRotExec();
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0PlayerTurn4;
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0TumbleTurn2;
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0StarTurn4;
    mstory3_scene0WorkTbl[5].func = mstory3_Scene0KoopaTurn2;
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(10);
    mstory3_scene0WorkTbl[8].func = mstory3_Scene0StampBApproach;
    HuPrcSleep(50);
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0TumbleHop1;
    mstory3_WinOpen();
    mstory3_WinMesExec(0x5A64);
    mstory3_WinClose();
    HuPrcSleep(10);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[4].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[4].obj->motion[1]].motId, 0, 10, 2);
    mstory3_WinOpen();
    mstory3_WinMesExec(0x5A65);
    mstory3_WinClose();
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[4].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[4].obj->motion[0]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0TumbleWaluigiFace;
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[2]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[1].func = mstory3_Scene0TumbleWalk;
    Hu3DMotionSpeedSet(mstory3_scene0WorkTbl[0].obj->model[1], 0.25f);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[13]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[2].unk_0C = 1;
    mstory3_scene0WorkTbl[2].unk_10 = 40;
    mstory3_ObjPosMoveAccel(mstory3_scene0WorkTbl[2].obj, &mstory3_scene0WaluigiDestPos0, 180, 1);
    mstory3_scene0WorkTbl[2].unk_0C = 0;
    Hu3DMotionSpeedSet(mstory3_scene0WorkTbl[0].obj->model[1], 1.0f);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[0]].motId, 0, 10, 2);
    mstory3_HmfAnimSet(mstory3_scene0WorkTbl[2].obj->model[1], mstory3_scene0WaluigiFaceSlot, mstory3_scene0WaluigiFaceAnimTbl[3]);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[4]].motId, 0, 10, 0);
    mstory3_MotionEndWait(mstory3_scene0WorkTbl[2].obj->model[1]);
    mstory3_HmfAnimSet(mstory3_scene0WorkTbl[2].obj->model[1], mstory3_scene0WaluigiFaceSlot, mstory3_scene0WaluigiFaceAnimTbl[0]);
    HuPrcSleep(30);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[2].obj, &mstory3_scene0WaluigiDestRot0, 10);
    mstory3_scene0WorkTbl[2].unk_0C = 1;
    mstory3_scene0WorkTbl[2].unk_10 = 31;
    mstory3_ObjForwardMove(mstory3_scene0WorkTbl[2].obj, 17.0f, 10);
    mstory3_scene0WorkTbl[2].unk_0C = 0;
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[7]].motId, 0, 10, 0);
    mstory3_HmfAnimSet(mstory3_scene0WorkTbl[0].obj->model[1], mstory3_scene0PlayerFaceSlot, mstory3_scene0PlayerFaceAnimTbl[2]);
    mstory3_WinOpen();
    mstory3_WinMesExec(0x5A66);
    mstory3_WinClose();
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0ObjIdle;
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0ObjIdle;
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0ObjIdle;
    mstory3_scene0WorkTbl[5].func = mstory3_Scene0KoopaStep;
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0StarLookAround;
    mstory3_scene0WorkTbl[3].unk_08 = 0;
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0TumbleLookAround;
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0PlayerStepBack2;
    mstory3_scene0WorkTbl[2].func = mstory3_Scene0WaluigiTurn;
    mstory3_WinOpen();
    mstory3_WinMesExec(0x5A67);
    mstory3_WinClose();
    while (TRUE) {
        if (mstory3_scene0WorkTbl[5].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    mstory3_scene0WorkTbl[5].unk_08 = 0;
    mstory3_scene0WorkTbl[10].func = mstory3_Scene0EventEndExec;
}

void mstory3_Scene0EventEndExec(omObjData *obj) {
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0StarLookAround;
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0TumbleLookAround;
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0PlayerLookAround;
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[7]].motId, 0, 10, 0);
    mstory3_HmfAnimSet(mstory3_scene0WorkTbl[2].obj->model[1], mstory3_scene0WaluigiFaceSlot, mstory3_scene0WaluigiFaceAnimTbl[3]);
    mstory3_WinOpen();
    mstory3_WinMesExec(0x5A69);
    mstory3_WinClose();
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[0]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0StarLookAround;
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0TumbleLookAround;
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0PlayerLookAround;
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[5].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[5].obj->motion[7]].motId, 0, 10, 0);
    mstory3_WinOpen();
    mstory3_WinMesExec(0x5A6A);
    mstory3_WinClose();
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[5].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[5].obj->motion[7]].motId, 0, 10, 0);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[7]].motId, 0, 10, 0);
    HuPrcSleep(10);
    mstory3_scene0WorkTbl[5].func = mstory3_Scene0KoopaApproach;
    mstory3_scene0WorkTbl[9].func = mstory3_Scene0CloudAppear;
    mstory3_scene0WorkTbl[2].func = mstory3_Scene0WaluigiStruggle;
    HuPrcSleep(120);
    mstory3_scene0WorkTbl[2].unk_08 = 1;
    HuPrcSleep(10);
    while (TRUE) {
        if (mstory3_scene0WorkTbl[9].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    mstory3_scene0WorkTbl[9].unk_08 = 0;
    HuPrcSleep(20);
    mstory3_scene0WorkTbl[2].func = mstory3_Scene0ObjIdle;
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[2].obj, &mstory3_scene0EventRot1, 5);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[0]].motId, 0, 10, 2);
    Hu3DData[mstory3_scene0WorkTbl[2].obj->model[1]].rot.y = 0.0f;
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[6]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[0].unk_08 = 1;
    mstory3_scene0WorkTbl[4].unk_08 = 1;
    mstory3_scene0WorkTbl[3].unk_08 = 1;
    HuAudFXPlay(0x2C4);
    mstory3_WinOpen();
    mstory3_WinMesExec(0x5A6C);
    mstory3_WinClose();
    HuPrcSleep(5);
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0PlayerReactTurn;
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0StarReactTurn;
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0TumbleReactTurn;
    HuAudFXPlay(0x29E);
    mstory3_scene0WorkTbl[5].func = mstory3_Scene0KoopaPose;
    mstory3_WinOpen();
    mstory3_WinMesChrNameExec(0x5A6D);
    mstory3_WinClose();
    HuPrcSleep(5);
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0PlayerReactTurn;
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0StarReactTurn;
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0TumbleReactTurn;
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[2].obj, &mstory3_scene0EventRot3, 10);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[0]].motId, 0, 10, 2);
    mstory3_WinOpen();
    mstory3_WinMesChrNameExec(0x5A6F);
    mstory3_WinClose();
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[2].obj, &mstory3_scene0EventRot1, 10);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[7]].motId, 0, 10, 0);
    mstory3_MotionEndWait(mstory3_scene0WorkTbl[2].obj->model[1]);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[2].obj, &mstory3_scene0EventRot0, 10);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[0]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[2].func = mstory3_Scene0WaluigiExit;
    while (TRUE) {
        if (mstory3_scene0WorkTbl[2].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    mstory3_scene0WorkTbl[2].unk_08 = 0;
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0PlayerDash;
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0TumbleDash;
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0StarDash;
    HuPrcSleep(30);
    mstory3_scene0EventRot0.y = Hu3DData[mstory3_scene0WorkTbl[0].obj->model[1]].rot.y;
    mstory3_scene0EventRot2.y = -62.78f;
    mstory3_HmfAnimSet(mstory3_scene0WorkTbl[0].obj->model[1], mstory3_scene0PlayerFaceSlot, mstory3_scene0PlayerFaceAnimTbl[0]);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[0].obj, &mstory3_scene0EventRot2, 10);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(40);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[0].obj, &mstory3_scene0EventRot1, 10);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(15);
    mstory3_HmfAnimSet(mstory3_scene0WorkTbl[0].obj->model[1], mstory3_scene0PlayerFaceSlot, mstory3_scene0PlayerFaceAnimTbl[2]);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[11]].motId, 0, 10, 0);
    mstory3_MotionEndWait(mstory3_scene0WorkTbl[0].obj->model[1]);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[2]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(mstory3_scene0WorkTbl[0].obj, &mstory3_scene0EventRot0, 3);
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0PlayerDash;
    HuPrcSleep(60);
    mstory3_scene0WorkTbl[6].func = mstory3_Scene0KoopaJrAEnter;
    mstory3_scene0WorkTbl[7].func = mstory3_Scene0KoopaJrBEnter;
    HuPrcSleep(15);
    HuAudFXPlay(0x2A0);
    mstory3_WinOpen();
    mstory3_WinMesChrNameExec(0x5A6E);
    mstory3_WinClose();
    while (TRUE) {
        if (mstory3_scene0WorkTbl[7].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    mstory3_scene0WorkTbl[7].unk_08 = 0;
    mstory3_scene0WorkTbl[6].func = mstory3_Scene0KoopaJrALift;
    mstory3_scene0WorkTbl[7].func = mstory3_Scene0KoopaJrBCarry;
    while (TRUE) {
        if (mstory3_scene0WorkTbl[6].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    mstory3_scene0WorkTbl[6].unk_08 = 0;
    mstory3_scene0WorkTbl[6].func = mstory3_Scene0KoopaJrACarry;
    HuPrcSleep(60);
    mstory3_SceneEnd();
    mstory3_scene0WorkTbl[10].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0PlayerDestroy(void) {
}

void mstory3_Scene0PlayerProc(void) {
    s32 motIds[8][4] = {
        { 0x3E, 0x40, 0x41, 0x43 },
        { 0x48, 0x4B, 0x4C, 0x4E },
        { 0x52, 0x54, 0x55, 0x57 },
        { 0x5B, 0x5D, 0x5E, 0x60 },
        { 0x65, 0x67, 0x68, 0x6A },
        { 0x6E, 0x70, 0x71, 0x73 },
        { 0x48, 0x4B, 0x4C, 0x4E },
        { 0x52, 0x54, 0x55, 0x57 },
    };
    omObjData *obj;
    s32 chr;
    void *data;

    obj = omAddObj(20, 20, 20, -1, NULL);
    mstory3_scene0WorkTbl[0].obj = obj;
    mstory3_scene0WorkTbl[0].unk_08 = 0;
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0ObjIdle;
    mstory3_scene0WorkTbl[0].unk_0C = 0;
    mstory3_scene0WorkTbl[0].unk_10 = 31;
    chr = mstory3_scene0PlayerChr;
    obj->model[1] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory3_scene0ShadowMdl);
    obj->model[3] = Hu3DModelRead(0x1D000A, 0x2B9);
    obj->model[4] = Hu3DModelRead(0x83, 0x2B9);
    Hu3DModelAttrSet(obj->model[3], 4, 4);
    Hu3DModelAttrSet(obj->model[4], 4, 4);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 1));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 2));
    omObjMotionRead(obj, 3, motIds[chr][1] | 0x1D0000);
    omObjMotionRead(obj, 4, motIds[chr][0] | 0x1D0000);
    omObjMotionRead(obj, 5, motIds[chr][2] | 0x1D0000);
    omObjMotionRead(obj, 6, motIds[chr][3] | 0x1D0000);
    omObjMotionRead(obj, 7, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(obj, 8, CharMotionDataNumGet(chr, 0x21));
    omObjMotionRead(obj, 9, CharMotionDataNumGet(chr, 0x72));
    omObjMotionRead(obj, 10, CharMotionDataNumGet(chr, 0x6C));
    omObjMotionRead(obj, 11, CharMotionDataNumGet(chr, 0x33));
    omObjMotionRead(obj, 12, CharMotionDataNumGet(chr, 0x9B));
    omObjMotionRead(obj, 13, CharMotionDataNumGet(chr, 0x9C));
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    if (mstory3_scene0PlayerChr == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    Hu3DModelPosSet(obj->model[1], -120.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], -120.0f, -5.0f, 480.0f);
    Hu3DModelPosSet(obj->model[4], -120.0f, 0.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    data = DataRead(CharMotionDataNumGet(chr, 0xA4));
    mstory3_scene0PlayerFaceAnimTbl[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, mstory3_scene0PlayerAnimNameTbl[chr]);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    Hu3DAnimAttrSet(mstory3_scene0PlayerFaceAnimTbl[0], 1, 0);
    Hu3DAnimBankSet(mstory3_scene0PlayerFaceAnimTbl[0], 0);
    mstory3_scene0PlayerFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory3_scene0PlayerFaceAnimTbl[0], 0, mstory3_scene0PlayerAnimNameTbl[chr]);
    data = DataRead(CharMotionDataNumGet(chr, 0xA9));
    mstory3_scene0PlayerFaceAnimTbl[1] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory3_scene0PlayerFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory3_scene0PlayerFaceAnimTbl[0], 0, mstory3_scene0PlayerAnimNameTbl[chr]);
    data = DataRead(CharMotionDataNumGet(chr, 0xAA));
    mstory3_scene0PlayerFaceAnimTbl[2] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory3_scene0PlayerFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory3_scene0PlayerFaceAnimTbl[0], 0, mstory3_scene0PlayerAnimNameTbl[chr]);
    data = DataRead(CharMotionDataNumGet(chr, 0xA5));
    mstory3_scene0PlayerFaceAnimTbl[3] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory3_scene0PlayerFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory3_scene0PlayerFaceAnimTbl[0], 0, mstory3_scene0PlayerAnimNameTbl[chr]);
    data = DataRead(CharMotionDataNumGet(chr, 0xA6));
    mstory3_scene0PlayerFaceAnimTbl[4] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory3_HmfAnimSet(obj->model[1], mstory3_scene0PlayerFaceSlot, mstory3_scene0PlayerFaceAnimTbl[0]);
    omPrcSetDestructor(0, mstory3_Scene0PlayerDestroy);
    while (TRUE) {
        mstory3_scene0WorkTbl[0].func(obj);
        HuPrcVSleep();
    }
}

void mstory3_Scene0PlayerPose(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    mstory3_MotionEndWait(obj->model[1]);
    HuPrcSleep(80);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0PlayerTurn1(omObjData *obj) {
    HuPrcSleep(10);
    mstory3_ObjRotMoveV(obj, &mstory3_scene0PlayerDestRot3, 10);
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0ObjIdle;
}

char *mstory3_scene0PlayerAnimNameTbl[] = { "c000l_0_DEF", "c001l_0_DEF", "c002l_0_DEF", "c003l_0_DEF", "c004l_0_DEF", "c005l_0_DEF", "c300l_0_DEF", "c301l_0_DEF" };
Vec mstory3_scene0StampPathA[4] = {
    { 0.0f, 200.0f, 100.0f },
    { -200.0f, 100.0f, -100.0f },
    { -100.0f, 300.0f, 300.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};
Vec mstory3_scene0StampPathB[6] = {
    { -100.0f, 300.0f, 300.0f },
    { -200.0f, 200.0f, 100.0f },
    { 0.0f, 300.0f, -100.0f },
    { 400.0f, 400.0f, 200.0f },
    { -50.0f, 120.0f, 450.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};
Vec mstory3_scene0StampBPathA[4] = {
    { 0.0f, 200.0f, 100.0f },
    { -200.0f, 100.0f, -100.0f },
    { -100.0f, 300.0f, 300.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};
Vec mstory3_scene0StampBPathB[6] = {
    { -70.0f, 300.0f, 300.0f },
    { 122.0f, 450.0f, -122.0f },
    { 314.0f, 500.0f, -544.0f },
    { 506.0f, 450.0f, -966.0f },
    { 700.0f, 150.0f, -1390.3f },
    { 9999.0f, 9999.0f, 9999.0f },
};

const Vec mstory3_scene0PlayerDestRot3 = { 0.0f, 150.0f, 0.0f };

void mstory3_Scene0PlayerStampExec(omObjData *obj) {
    HmfMotionNode *node;
    s32 i;
    f32 scale;
    f32 time;

    HuPrcSleep(70);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[13]].motId, 0, 10, 2);
    mstory3_ObjRotMove(obj, 0.0f, 110.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    HuPrcSleep(10);
    Hu3DModelAttrSet(obj->model[3], 0x4000, 0x4000);
    Hu3DModelHookSet(obj->model[3], obj->model[1], "item_hook");
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, 0);
    mstory3_MotionEndWait(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    mstory3_MotionEndWait(obj->model[1]);
    while (TRUE) {
        if (mstory3_scene0WorkTbl[8].unk_08 == 2) {
            break;
        }
        HuPrcVSleep();
    }
    mstory3_scene0WorkTbl[8].unk_08 = 0;
    Hu3DModelAttrSet(mstory3_scene0WorkTbl[8].obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mstory3_scene0WorkTbl[8].obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DMotionNoMotSet(obj->model[1], Hu3DData[obj->model[1]].motId, "item_hook", 27, 69);
    Hu3DMotionNoMotSet(obj->model[1], Hu3DData[obj->model[1]].motId, "item_hook", 27, 70);
    Hu3DMotionNoMotSet(obj->model[1], Hu3DData[obj->model[1]].motId, "item_hook", 27, 71);
    node = Hu3DModelObjPtrGet(obj->model[1], "item_hook");
    for (i = 0; i < 10; i++) {
        scale = sindf(i * 18.0f) * 0.8 + 1.0;
        node->baseScale.x = scale;
        node->baseScale.y = scale;
        node->baseScale.z = scale;
        node->scale.x = scale;
        node->scale.y = scale;
        node->scale.z = scale;
        HuPrcVSleep();
    }
    Hu3DMotionNoMotReset(obj->model[1], Hu3DData[obj->model[1]].motId, "item_hook", 27, 71);
    Hu3DMotionNoMotReset(obj->model[1], Hu3DData[obj->model[1]].motId, "item_hook", 27, 70);
    Hu3DMotionNoMotReset(obj->model[1], Hu3DData[obj->model[1]].motId, "item_hook", 27, 69);
    mstory3_StampCardStart(5);
    while (mstory3_StampCardDoneCheck() != 1) {
        HuPrcVSleep();
    }
    mstory3_WinOpen();
    mstory3_WinMesExec(0x5A5C);
    mstory3_WinClose();
    Hu3DMotionModelSet(obj->model[1], obj->motion[4]);
    Hu3DMotionAttrSet(obj->model[1], 4, 4);
    Hu3DMotionSpeedSet(obj->model[1], 2.0f);
    Hu3DMotionTimeSet(obj->model[1], Hu3DMotion[Hu3DData[obj->model[1]].motId].unk02);
    do {
        time = Hu3DData[obj->model[1]].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    Hu3DMotionModelSet(obj->model[1], obj->motion[3]);
    Hu3DMotionAttrSet(obj->model[1], 4, 4);
    Hu3DMotionTimeSet(obj->model[1], Hu3DMotion[Hu3DData[obj->model[1]].motId].unk02);
    do {
        time = Hu3DData[obj->model[1]].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    Hu3DMotionSpeedSet(obj->model[1], 1.0f);
    Hu3DModelAttrSet(obj->model[3], 0x4000, 0);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    HuAudSeqFadeOut(20);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[0].unk_08 = 1;
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0PlayerTurn2(omObjData *obj) {
    HuPrcSleep(10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(obj, &mstory3_scene0PlayerDestRot4, 5);
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0PlayerStepBack1(omObjData *obj) {
    mstory3_scene0WorkTbl[0].unk_0C = 1;
    mstory3_scene0WorkTbl[0].unk_10 = 31;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjBackwardMove(obj, 1.5f, 60);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[0].unk_0C = 0;
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0PlayerTurn3(omObjData *obj) {
    HuPrcSleep(10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(obj, &mstory3_scene0PlayerDestRot5, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0PlayerTurn4(omObjData *obj) {
    mstory3_ObjRotMoveV(obj, &mstory3_scene0PlayerDestRot6, 5);
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0PlayerWaluigiFace;
}

void mstory3_Scene0PlayerWaluigiFace(omObjData *obj) {
    mstory3_ObjTargetFace(obj, mstory3_scene0WorkTbl[2].obj);
}

void mstory3_Scene0PlayerStepBack2(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(obj, &mstory3_scene0PlayerDestRot7, 10);
    mstory3_scene0WorkTbl[0].unk_0C = 1;
    mstory3_scene0WorkTbl[0].unk_10 = 31;
    mstory3_ObjBackwardMove(obj, 6.0f, 30);
    mstory3_scene0WorkTbl[0].unk_0C = 0;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0PlayerLookAround;
}

void mstory3_Scene0PlayerReactTurn(omObjData *obj) {
    if (mstory3_scene0WorkTbl[0].unk_08 == 1) {
        mstory3_HmfAnimSet(obj->model[1], mstory3_scene0PlayerFaceSlot, mstory3_scene0PlayerFaceAnimTbl[4]);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
        mstory3_ObjRotMoveV(obj, &mstory3_scene0PlayerDestRot9, 10);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
        mstory3_scene0WorkTbl[0].unk_08 = 2;
        mstory3_scene0WorkTbl[0].func = mstory3_Scene0ObjIdle;
    } else if (mstory3_scene0WorkTbl[0].unk_08 == 2) {
        mstory3_HmfAnimSet(obj->model[1], mstory3_scene0PlayerFaceSlot, mstory3_scene0PlayerFaceAnimTbl[2]);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
        mstory3_ObjRotMoveV(obj, &mstory3_scene0PlayerDestRot8, 10);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
        mstory3_scene0WorkTbl[0].unk_08 = 3;
        mstory3_scene0WorkTbl[0].func = mstory3_Scene0PlayerWaluigiFace2;
    } else if (mstory3_scene0WorkTbl[0].unk_08 == 3) {
        mstory3_ObjRotMoveV(obj, &mstory3_scene0PlayerDestRot9, 10);
        mstory3_scene0WorkTbl[0].func = mstory3_Scene0PlayerWaluigiFace2;
    }
}

void mstory3_Scene0PlayerWaluigiFace2(omObjData *obj) {
    mstory3_ObjTargetFace(obj, mstory3_scene0WorkTbl[2].obj);
}

void mstory3_Scene0PlayerDash(omObjData *obj) {
    HuPrcSleep(5);
    mstory3_scene0WorkTbl[0].unk_0C = 1;
    mstory3_scene0WorkTbl[0].unk_10 = 40;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    mstory3_ObjForwardMove(obj, 20.0f, 15);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[0].unk_0C = 0;
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0PlayerLookAround(omObjData *obj) {
    if (mstory3_scene0WorkTbl[0].unk_08 == 0) {
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
        mstory3_ObjRotMoveV(obj, &mstory3_scene0PlayerDestRot10, 10);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
        mstory3_scene0WorkTbl[0].unk_08 = 1;
        mstory3_scene0WorkTbl[0].func = mstory3_Scene0ObjIdle;
    } else if (mstory3_scene0WorkTbl[0].unk_08 == 1) {
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
        mstory3_ObjRotMoveV(obj, &mstory3_scene0PlayerDestRot11, 10);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
        mstory3_scene0WorkTbl[0].unk_08 = 2;
        mstory3_scene0WorkTbl[0].func = mstory3_Scene0ObjIdle;
    } else if (mstory3_scene0WorkTbl[0].unk_08 == 2) {
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
        mstory3_ObjRotMoveV(obj, &mstory3_scene0PlayerDestRot10, 10);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
        mstory3_scene0WorkTbl[0].unk_08 = 0;
        mstory3_scene0WorkTbl[0].func = mstory3_Scene0ObjIdle;
    }
}

void mstory3_Scene0DaisyDestroy(void) {
}

void mstory3_Scene0DaisyProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    mstory3_scene0WorkTbl[1].obj = obj;
    mstory3_scene0WorkTbl[1].unk_08 = 0;
    mstory3_scene0WorkTbl[1].func = mstory3_Scene0ObjIdle;
    mstory3_scene0WorkTbl[1].unk_0C = 0;
    mstory3_scene0WorkTbl[1].unk_10 = 31;
    obj->model[1] = Hu3DModelRead(0x90000, 0x2B9);
    obj->model[2] = Hu3DModelLink(mstory3_scene0ShadowMdl);
    omObjMotionRead(obj, 0, 0x90004);
    omObjMotionRead(obj, 1, 0x1D007A);
    omObjMotionRead(obj, 2, 0x1D0051);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 30, 2);
    Hu3DModelPosSet(obj->model[1], 150.0f, 0.0f, 384.0f);
    Hu3DModelPosSet(obj->model[2], 150.0f, -5.0f, 384.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 340.0f, 0.0f);
    omPrcSetDestructor(0, mstory3_Scene0DaisyDestroy);
    while (1) {
        mstory3_scene0WorkTbl[1].func(obj);
        HuPrcVSleep();
    }
}

const Vec mstory3_scene0PlayerDestRot4 = { 0.0f, -99.79999f, 0.0f };

const Vec mstory3_scene0PlayerDestRot5 = { 0.0f, -221.9f, 0.0f };

const Vec mstory3_scene0PlayerDestRot6 = { 0.0f, -198.1f, 0.0f };

const Vec mstory3_scene0PlayerDestRot7 = { 0.0f, 0.0f, 0.0f };

const Vec mstory3_scene0PlayerDestRot8 = { 0.0f, 22.11f, 0.0f };

const Vec mstory3_scene0PlayerDestRot9 = { 0.0f, -23.36f, 0.0f };

const Vec mstory3_scene0PlayerDestRot10 = { 0.0f, -23.36f, 0.0f };

const Vec mstory3_scene0PlayerDestRot11 = { 0.0f, 22.11f, 0.0f };
const Vec mstory3_scene0UnusedRot0 = { 0.0f, 0.0f, 0.0f }; /* Unreferenced. */

const Vec mstory3_scene0DaisyDestPos0 = { 200.0f, 0.0f, 1200.0f };

void mstory3_Scene0DaisyExit(omObjData *obj) {
    HuAudFXPlay(0x28E);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[1].unk_0C = 1;
    mstory3_scene0WorkTbl[1].unk_10 = 40;
    mstory3_ObjPosMoveV(obj, &mstory3_scene0DaisyDestPos0, 40);
    mstory3_scene0WorkTbl[1].unk_0C = 0;
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    mstory3_scene0WorkTbl[1].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0StampBDrift(omObjData *obj) {
    Vec pos;

    pos.x = Hu3DData[mstory3_scene0WorkTbl[8].obj->model[2]].pos.x;
    pos.y = Hu3DData[mstory3_scene0WorkTbl[8].obj->model[2]].pos.y;
    pos.z = Hu3DData[mstory3_scene0WorkTbl[8].obj->model[2]].pos.z;
    pos.x += 0.5f;
    Hu3DModelPosSet(mstory3_scene0WorkTbl[8].obj->model[2], pos.x, pos.y, pos.z);
    EffectPosSet(mstory3_scene0WorkTbl[8].obj->model[5], pos.x, pos.y - 40.0f, pos.z);
}

void mstory3_Scene0WaluigiAppear(omObjData *obj) {
    omObjData *target = mstory3_scene0WorkTbl[2].obj;

    Hu3DModelAttrSet(target->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(target->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    mstory3_BackMotionStart();
    HuPrcSleep(3);
    mstory3_BackMotionReverse();
    mstory3_scene0WorkTbl[1].func = mstory3_Scene0ObjIdle;
}

const Vec mstory3_scene0TumbleDestPos0 = { 138.0f, 100.0f, 214.0f };

void mstory3_Scene0TumbleWalk(omObjData *obj) {
    mstory3_ObjPosMoveEx(mstory3_scene0WorkTbl[3].obj, &mstory3_scene0TumbleDestPos0, 180, 0);
    mstory3_scene0WorkTbl[1].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0WaluigiDestroy(void) {
}

void mstory3_Scene0WaluigiProc(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(20, 20, 20, -1, NULL);
    mstory3_scene0WorkTbl[2].obj = obj;
    mstory3_scene0WorkTbl[2].unk_08 = 0;
    mstory3_scene0WorkTbl[2].func = mstory3_Scene0ObjIdle;
    mstory3_scene0WorkTbl[2].unk_0C = 0;
    mstory3_scene0WorkTbl[2].unk_10 = 31;
    obj->model[1] = Hu3DModelRead(0x800A0, 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory3_scene0ShadowMdl);
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DModelAttrSet(obj->model[2], 4, 4);
    omObjMotionRead(obj, 0, 0x80000);
    omObjMotionRead(obj, 1, 0x80001);
    omObjMotionRead(obj, 2, 0x80002);
    omObjMotionRead(obj, 3, 0x80005);
    omObjMotionRead(obj, 4, 0x8002F);
    omObjMotionRead(obj, 5, 0x80072);
    omObjMotionRead(obj, 6, 0x1D0075);
    omObjMotionRead(obj, 7, 0x80033);
    omObjMotionRead(obj, 8, 0x80003);
    omObjMotionRead(obj, 9, 0x80005);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], 608.1f, -85.8f, -1390.3f);
    Hu3DModelPosSet(obj->model[2], 608.1f, -85.8f, -1390.3f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    data = DataRead(CharMotionDataNumGet(6, 0xA4));
    mstory3_scene0WaluigiFaceAnimTbl[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, "c300l_0_DEF");
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    Hu3DAnimAttrSet(mstory3_scene0WaluigiFaceAnimTbl[0], 1, 0);
    Hu3DAnimBankSet(mstory3_scene0WaluigiFaceAnimTbl[0], 0);
    mstory3_scene0WaluigiFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory3_scene0WaluigiFaceAnimTbl[0], 0, "c300l_0_DEF");
    data = DataRead(CharMotionDataNumGet(6, 0xA9));
    mstory3_scene0WaluigiFaceAnimTbl[1] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory3_scene0WaluigiFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory3_scene0WaluigiFaceAnimTbl[0], 0, "c300l_0_DEF");
    data = DataRead(CharMotionDataNumGet(6, 0xAA));
    mstory3_scene0WaluigiFaceAnimTbl[2] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory3_scene0WaluigiFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory3_scene0WaluigiFaceAnimTbl[0], 0, "c300l_0_DEF");
    data = DataRead(CharMotionDataNumGet(6, 0xA5));
    mstory3_scene0WaluigiFaceAnimTbl[3] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory3_HmfAnimSet(obj->model[1], mstory3_scene0WaluigiFaceSlot, mstory3_scene0WaluigiFaceAnimTbl[0]);
    omPrcSetDestructor(0, mstory3_Scene0WaluigiDestroy);
    while (TRUE) {
        mstory3_scene0WorkTbl[2].func(obj);
        HuPrcVSleep();
    }
}

void mstory3_Scene0WaluigiTurn(omObjData *obj) {
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[1]].motId, 0, 10,
                       2);
    mstory3_ObjRotMoveV(obj, &mstory3_scene0WaluigiDestRot1, 10);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[0]].motId, 0, 10,
                       2);
    mstory3_scene0WorkTbl[2].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0WaluigiExit(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(10);
    mstory3_scene0WorkTbl[8].func = mstory3_Scene0StampBExit;
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[13]].motId, 0, 10, 2);
    Hu3DMotionSpeedSet(mstory3_scene0WorkTbl[0].obj->model[1], 0.5f);
    mstory3_scene0WorkTbl[2].unk_0C = 1;
    mstory3_scene0WorkTbl[2].unk_10 = 40;
    mstory3_ObjPosMoveV(obj, &mstory3_scene0WaluigiDestPos1, 60);
    mstory3_scene0WorkTbl[2].unk_0C = 0;
    Hu3DMotionSpeedSet(mstory3_scene0WorkTbl[0].obj->model[1], 1.0f);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[0]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[2].unk_08 = 1;
    mstory3_scene0WorkTbl[2].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0TumbleDestroy(void) {
}

const Vec mstory3_scene0WaluigiDestRot1 = { 0.0f, -90.0f, 0.0f };

const Vec mstory3_scene0WaluigiDestPos1 = { 600.0f, 0.0f, 480.0f };

const char mstory3_scene0TumbleAnimName[] = "c204n_0_DEF";

void mstory3_Scene0TumbleProc(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 20, 20, -1, NULL);
    mstory3_scene0WorkTbl[3].obj = obj;
    mstory3_scene0WorkTbl[3].unk_08 = 0;
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0ObjIdle;
    obj->model[1] = Hu3DModelRead(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory3_scene0ShadowMdl);
    omObjMotionRead(obj, 0, 0xA0076);
    omObjMotionRead(obj, 1, 0x1D0029);
    omObjMotionRead(obj, 2, 0x1D002A);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], 38.0f, 100.0f, 214.0f);
    Hu3DModelPosSet(obj->model[2], 38.0f, -5.0f, 214.0f);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    data = DataRead(0xA007E);
    mstory3_scene0TumbleFaceAnimTbl[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, mstory3_scene0TumbleAnimName);
    HuMemMemoryFreePerm(data);
    mstory3_scene0TumbleFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory3_scene0TumbleFaceAnimTbl[0], 0, mstory3_scene0TumbleAnimName);
    data = DataRead(0xA0080);
    mstory3_scene0TumbleFaceAnimTbl[1] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory3_scene0TumbleFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory3_scene0TumbleFaceAnimTbl[0], 0, mstory3_scene0TumbleAnimName);
    data = DataRead(0xA0083);
    mstory3_scene0TumbleFaceAnimTbl[2] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    Hu3DAnimAttrSet(mstory3_scene0TumbleFaceAnimTbl[0], 1, 0);
    Hu3DAnimBankSet(mstory3_scene0TumbleFaceAnimTbl[0], 0);
    mstory3_HmfAnimSet(obj->model[1], mstory3_scene0TumbleFaceSlot, mstory3_scene0TumbleFaceAnimTbl[0]);
    omPrcSetDestructor(0, mstory3_Scene0TumbleDestroy);
    while (TRUE) {
        mstory3_scene0WorkTbl[3].func(obj);
        HuPrcVSleep();
    }
}

const Vec mstory3_scene0TumbleDestRot4 = { 10.0f, 378.9f, 0.0f };

void mstory3_Scene0TumbleEnter(omObjData *obj) {
    HuPrcSleep(60);
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0PlayerPose;
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0StarTurn1;
    mstory3_ObjRotMoveV(obj, &mstory3_scene0TumbleDestRot4, 30);
    mstory3_ObjPosMoveV(obj, &mstory3_scene0TumbleDestPos1, 20);
    HuPrcSleep(30);
    mstory3_ObjRotMoveV(obj, &mstory3_scene0TumbleDestRot5, 10);
    mstory3_ObjPosMoveV(obj, &mstory3_scene0TumbleDestPos2, 15);
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0PlayerTurn1;
    mstory3_ObjRotMoveV(obj, &mstory3_scene0TumbleDestRot6, 10);
    mstory3_scene0WorkTbl[3].unk_08 = 1;
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0ObjIdle;
}

const Vec mstory3_scene0TumbleDestRot5 = { 0.0f, 134.2f, 0.0f };

const Vec mstory3_scene0TumbleDestRot6 = { 20.0f, 320.0f, 0.0f };

const Vec mstory3_scene0TumbleDestPos1 = { 88.0f, 100.0f, 360.0f };

const Vec mstory3_scene0TumbleDestPos2 = { 238.0f, 100.0f, 214.0f };

void mstory3_Scene0TumbleHop1(omObjData *obj) {
    f32 baseY = Hu3DData[obj->model[1]].pos.y;
    f32 ofs;
    s16 i;

    for (i = 0; i < 12; i++) {
        ofs = sindf(i * 15.0) * 80.0f;
        Hu3DData[obj->model[1]].pos.y = baseY + ofs;
        HuPrcVSleep();
    }
    mstory3_HmfAnimSet(obj->model[1], mstory3_scene0TumbleFaceSlot, mstory3_scene0TumbleFaceAnimTbl[2]);
    mstory3_scene0WorkTbl[3].unk_08 = 1;
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0TumbleTurn1(omObjData *obj) {
    HuPrcSleep(10);
    mstory3_HmfAnimSet(obj->model[1], mstory3_scene0TumbleFaceSlot, mstory3_scene0TumbleFaceAnimTbl[0]);
    mstory3_ObjRotMoveV(obj, &mstory3_scene0TumbleDestRot7, 5);
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0ObjIdle;
}

const Vec mstory3_scene0TumbleDestRot7 = { 0.0f, 285.8f, 0.0f };

void mstory3_Scene0TumbleHop2(omObjData *obj) {
    f32 baseY = Hu3DData[obj->model[1]].pos.y;
    f32 ofs;
    s16 i;

    for (i = 0; i < 10; i++) {
        ofs = sindf(i * 15.0) * 100.0f;
        Hu3DData[obj->model[1]].pos.y = baseY + ofs;
        HuPrcVSleep();
    }
    mstory3_HmfAnimSet(obj->model[1], mstory3_scene0TumbleFaceSlot, mstory3_scene0TumbleFaceAnimTbl[2]);
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0PlayerTurn3;
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0StarTurn3;
    mstory3_scene0WorkTbl[5].func = mstory3_Scene0KoopaTurn1;
    mstory3_scene0WorkTbl[3].unk_08 = 1;
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0TumbleTurn2(omObjData *obj) {
    mstory3_ObjRotMoveV(obj, &mstory3_scene0TumbleDestRot8, 5);
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0TumbleWaluigiFace;
}

void mstory3_Scene0TumbleWaluigiFace(omObjData *obj) {
    mstory3_ObjTargetFace(obj, mstory3_scene0WorkTbl[2].obj);
}

void mstory3_Scene0TumbleReactTurn(omObjData *obj) {
    if (mstory3_scene0WorkTbl[3].unk_08 == 1) {
        mstory3_HmfAnimSet(obj->model[1], mstory3_scene0TumbleFaceSlot, mstory3_scene0TumbleFaceAnimTbl[0]);
        mstory3_ObjRotMoveV(obj, &mstory3_scene0TumbleDestRot9, 10);
        mstory3_scene0WorkTbl[3].unk_08 = 2;
        mstory3_scene0WorkTbl[3].func = mstory3_Scene0ObjIdle;
    } else if (mstory3_scene0WorkTbl[3].unk_08 == 2) {
        mstory3_HmfAnimSet(obj->model[1], mstory3_scene0TumbleFaceSlot, mstory3_scene0TumbleFaceAnimTbl[1]);
        mstory3_ObjRotMoveV(obj, &mstory3_scene0TumbleDestRot10, 10);
        mstory3_scene0WorkTbl[3].unk_08 = 3;
        mstory3_scene0WorkTbl[3].func = mstory3_Scene0TumbleWaluigiFace2;
    } else if (mstory3_scene0WorkTbl[3].unk_08 == 3) {
        mstory3_ObjRotMoveV(obj, &mstory3_scene0TumbleDestRot9, 10);
        mstory3_scene0WorkTbl[3].func = mstory3_Scene0TumbleWaluigiFace2;
    }
}

void mstory3_Scene0TumbleWaluigiFace2(omObjData *obj) {
    mstory3_ObjTargetFace(obj, mstory3_scene0WorkTbl[2].obj);
}

void mstory3_Scene0TumbleDash(omObjData *obj) {
    HuPrcSleep(10);
    mstory3_ObjForwardMove(obj, 20.0f, 60);
    mstory3_scene0WorkTbl[3].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0TumbleLookAround(omObjData *obj) {
    if (mstory3_scene0WorkTbl[3].unk_08 == 0) {
        mstory3_ObjRotMoveV(obj, &mstory3_scene0TumbleDestRot11, 10);
        mstory3_scene0WorkTbl[3].unk_08 = 1;
        mstory3_scene0WorkTbl[3].func = mstory3_Scene0ObjIdle;
    } else if (mstory3_scene0WorkTbl[3].unk_08 == 1) {
        mstory3_ObjRotMoveV(obj, &mstory3_scene0TumbleDestRot12, 10);
        mstory3_scene0WorkTbl[3].unk_08 = 2;
        mstory3_scene0WorkTbl[3].func = mstory3_Scene0ObjIdle;
    } else if (mstory3_scene0WorkTbl[3].unk_08 == 2) {
        mstory3_ObjRotMoveV(obj, &mstory3_scene0TumbleDestRot11, 10);
        mstory3_scene0WorkTbl[3].unk_08 = 0;
        mstory3_scene0WorkTbl[3].func = mstory3_Scene0ObjIdle;
    }
}

void mstory3_Scene0TumbleShake(omObjData *obj) {
    f32 rotY;
    f32 ofs;
    s16 i;

    if (mstory3_scene0WorkTbl[3].unk_08 == 0) {
        HuPrcSleep(30);
    }
    rotY = Hu3DData[obj->model[1]].rot.y;
    for (i = 0; i < 10; i++) {
        ofs = sindf(i * 9.0f) * 120.0f;
        Hu3DData[obj->model[1]].rot.y = rotY + ofs;
        HuPrcVSleep();
    }
    rotY = Hu3DData[obj->model[1]].rot.y;
    for (i = 0; i < 15; i++) {
        ofs = sindf(i * 4.5f) * 240.0f;
        Hu3DData[obj->model[1]].rot.y = rotY - ofs;
        HuPrcVSleep();
    }
    rotY = Hu3DData[obj->model[1]].rot.y;
    for (i = 0; i < 10; i++) {
        ofs = sindf(i * 9.0f) * 120.0f;
        Hu3DData[obj->model[1]].rot.y = rotY + ofs;
        HuPrcVSleep();
    }
    if (mstory3_scene0WorkTbl[3].unk_08 == 0) {
        mstory3_scene0WorkTbl[3].unk_08 = 0;
        mstory3_scene0WorkTbl[3].func = mstory3_Scene0TumbleHop2;
    } else {
        mstory3_scene0WorkTbl[3].unk_08 = 0;
        mstory3_scene0WorkTbl[3].func = mstory3_Scene0ObjIdle;
    }
}

void mstory3_Scene0StarDestroy(void) {
}

void mstory3_Scene0StarProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    mstory3_scene0WorkTbl[4].obj = obj;
    mstory3_scene0WorkTbl[4].unk_08 = 0;
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0ObjIdle;
    obj->model[1] = Hu3DModelRead(0xA0122, 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory3_scene0ShadowMdl);
    omObjMotionRead(obj, 0, 0xA0123);
    omObjMotionRead(obj, 1, 0xA0125);
    omObjMotionRead(obj, 2, 0xA0127);
    omObjMotionRead(obj, 3, 0xA0129);
    omObjMotionRead(obj, 4, 0xA012A);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], 0.0f, 200.0f, 150.0f);
    Hu3DModelPosSet(obj->model[2], 0.0f, -5.0f, 150.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    AuraCreate(obj->model[1]);
    omPrcSetDestructor(0, mstory3_Scene0StarDestroy);
    while (1) {
        mstory3_scene0WorkTbl[4].func(obj);
        HuPrcVSleep();
    }
}

void mstory3_Scene0StarFloatProc(void) {
    f32 angle = 0.0f;
    omObjData *obj = mstory3_scene0WorkTbl[4].obj;
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
        Hu3DModelPosSet(obj->model[1], pos.x, ofs + pos.y, pos.z);
        HuPrcVSleep();
    }
}

void mstory3_Scene0StarTurn1(omObjData *obj) {
    mstory3_ObjRotMoveV(obj, &mstory3_scene0StarDestRot3, 20);
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0StarTurn2(omObjData *obj) {
    HuPrcSleep(10);
    mstory3_ObjRotMoveV(obj, &mstory3_scene0StarDestRot4, 5);
    mstory3_scene0WorkTbl[8].unk_08 = 2;
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0StarStepBack(omObjData *obj) {
    mstory3_ObjBackwardMove(obj, 2.0f, 60);
    mstory3_scene0WorkTbl[4].unk_08 = 1;
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0StarTurn3(omObjData *obj) {
    HuPrcSleep(10);
    mstory3_ObjRotMoveV(obj, &mstory3_scene0StarDestRot5, 10);
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0StarTurn4(omObjData *obj) {
    mstory3_ObjRotMoveV(obj, &mstory3_scene0StarDestRot6, 5);
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0StarWaluigiFace;
}

void mstory3_Scene0StarWaluigiFace(omObjData *obj) {
    mstory3_ObjTargetFace(obj, mstory3_scene0WorkTbl[2].obj);
}

void mstory3_Scene0StarReactTurn(omObjData *obj) {
    if (mstory3_scene0WorkTbl[4].unk_08 == 1) {
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
        mstory3_ObjRotMoveV(obj, &mstory3_scene0StarDestRot7, 10);
        mstory3_scene0WorkTbl[4].unk_08 = 2;
        mstory3_scene0WorkTbl[4].func = mstory3_Scene0ObjIdle;
    } else if (mstory3_scene0WorkTbl[4].unk_08 == 2) {
        mstory3_ObjRotMoveV(obj, &mstory3_scene0StarDestRot8, 10);
        mstory3_scene0WorkTbl[4].unk_08 = 3;
        mstory3_scene0WorkTbl[4].func = mstory3_Scene0StarWaluigiFace2;
    } else if (mstory3_scene0WorkTbl[4].unk_08 == 3) {
        mstory3_ObjRotMoveV(obj, &mstory3_scene0StarDestRot7, 10);
        mstory3_scene0WorkTbl[4].func = mstory3_Scene0StarWaluigiFace2;
    }
}

void mstory3_Scene0StarWaluigiFace2(omObjData *obj) {
    mstory3_ObjTargetFace(obj, mstory3_scene0WorkTbl[2].obj);
}

void mstory3_Scene0StarDash(omObjData *obj) {
    HuPrcSleep(10);
    mstory3_ObjForwardMove(obj, 20.0f, 60);
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0StarLookAround(omObjData *obj) {
    if (mstory3_scene0WorkTbl[4].unk_08 == 0) {
        mstory3_ObjRotMoveV(obj, &mstory3_scene0StarDestRot9, 10);
        mstory3_scene0WorkTbl[4].unk_08 = 1;
        mstory3_scene0WorkTbl[4].func = mstory3_Scene0ObjIdle;
    } else if (mstory3_scene0WorkTbl[4].unk_08 == 1) {
        mstory3_ObjRotMoveV(obj, &mstory3_scene0StarDestRot10, 10);
        mstory3_scene0WorkTbl[4].unk_08 = 2;
        mstory3_scene0WorkTbl[4].func = mstory3_Scene0ObjIdle;
    } else if (mstory3_scene0WorkTbl[4].unk_08 == 2) {
        mstory3_ObjRotMoveV(obj, &mstory3_scene0StarDestRot9, 10);
        mstory3_scene0WorkTbl[4].unk_08 = 0;
        mstory3_scene0WorkTbl[4].func = mstory3_Scene0ObjIdle;
    }
}

void mstory3_Scene0StarShake(omObjData *obj) {
    f32 rotY;
    f32 ofs;
    s16 i;

    rotY = Hu3DData[obj->model[1]].rot.y;
    for (i = 0; i < 15; i++) {
        ofs = sindf(i * 6.0f) * 30.0f;
        Hu3DData[obj->model[1]].rot.y = rotY + ofs;
        HuPrcVSleep();
    }
    rotY = Hu3DData[obj->model[1]].rot.y;
    for (i = 0; i < 30; i++) {
        ofs = sindf(i * 3.0f) * 60.0f;
        Hu3DData[obj->model[1]].rot.y = rotY - ofs;
        HuPrcVSleep();
    }
    rotY = Hu3DData[obj->model[1]].rot.y;
    for (i = 0; i < 15; i++) {
        ofs = sindf(i * 6.0f) * 30.0f;
        Hu3DData[obj->model[1]].rot.y = rotY + ofs;
        HuPrcVSleep();
    }
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0KoopaDestroy(void) {
}

void mstory3_Scene0KoopaProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 20, 20, -1, NULL);
    mstory3_scene0WorkTbl[5].obj = obj;
    mstory3_scene0WorkTbl[5].unk_08 = 0;
    mstory3_scene0WorkTbl[5].func = mstory3_Scene0ObjIdle;
    obj->model[1] = Hu3DModelRead(0xA002F, 0x2B9);
    obj->model[2] = Hu3DModelLink(mstory3_scene0ShadowMdl);
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DModelAttrSet(obj->model[2], 4, 4);
    omObjMotionRead(obj, 0, 0xA0030);
    omObjMotionRead(obj, 1, 0xA0035);
    omObjMotionRead(obj, 2, 0xA0032);
    omObjMotionRead(obj, 3, 0x1D0032);
    omObjMotionRead(obj, 4, 0x1D0034);
    omObjMotionRead(obj, 5, 0x1D0033);
    omObjMotionRead(obj, 6, 0x1D0035);
    omObjMotionRead(obj, 7, 0xA0038);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], -700.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], -700.0f, -5.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 270.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[2], 3.0f, 1.0f, 3.0f);
    omPrcSetDestructor(0, mstory3_Scene0KoopaDestroy);
    while (1) {
        mstory3_scene0WorkTbl[5].func(obj);
        HuPrcVSleep();
    }
}

const Vec mstory3_scene0TumbleDestRot8 = { 0.0f, -193.0f, 0.0f };

const Vec mstory3_scene0TumbleDestRot9 = { 0.0f, -31.8f, 0.0f };

const Vec mstory3_scene0TumbleDestRot10 = { 0.0f, -2.58f, 0.0f };

const Vec mstory3_scene0TumbleDestRot11 = { 0.0f, -31.8f, 0.0f };

const Vec mstory3_scene0TumbleDestRot12 = { 0.0f, -2.58f, 0.0f };

const Vec mstory3_scene0StarDestRot3 = { 0.0f, 10.0f, 0.0f };

const Vec mstory3_scene0StarDestRot4 = { 0.0f, -61.1f, 0.0f };

const Vec mstory3_scene0StarDestRot5 = { 0.0f, 62.38f, 0.0f };

const Vec mstory3_scene0StarDestRot6 = { 0.0f, 157.87f, 0.0f };

const Vec mstory3_scene0StarDestRot7 = { 0.0f, -16.15f, 0.0f };

const Vec mstory3_scene0StarDestRot8 = { 0.0f, 17.12f, 0.0f };

const Vec mstory3_scene0StarDestRot9 = { 0.0f, -16.15f, 0.0f };

const Vec mstory3_scene0StarDestRot10 = { 0.0f, 17.12f, 0.0f };

const Vec mstory3_scene0KoopaDestPos0 = { -350.0f, 0.0f, 480.0f };
// Unreferenced zero-filled rodata.
const Vec mstory3_scene0UnusedPosTbl[9] = { 0 };

void mstory3_Scene0KoopaEnter(omObjData *obj) {
    Hu3DModelAttrSet(obj->model[1], 4, 0);
    Hu3DModelAttrSet(obj->model[2], 4, 0);
    mstory3_scene0WorkTbl[0].func = mstory3_Scene0PlayerStepBack1;
    mstory3_scene0WorkTbl[4].func = mstory3_Scene0StarStepBack;
    mstory3_scene0WorkTbl[1].func = mstory3_Scene0StampBDrift;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjPosMoveV(obj, &mstory3_scene0KoopaDestPos0, 60);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    while (TRUE) {
        if (mstory3_scene0WorkTbl[4].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    mstory3_scene0WorkTbl[4].unk_08 = 0;
    mstory3_scene0WorkTbl[1].func = mstory3_Scene0ObjIdle;
    mstory3_scene0WorkTbl[5].unk_08 = 1;
    mstory3_scene0WorkTbl[5].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0KoopaTurn1(omObjData *obj) {
    HuPrcSleep(10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(obj, &mstory3_scene0KoopaDestRot1, 10);
    mstory3_scene0WorkTbl[5].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0KoopaTurn2(omObjData *obj) {
    mstory3_ObjRotMoveV(obj, &mstory3_scene0KoopaDestRot2, 5);
    mstory3_scene0WorkTbl[5].func = mstory3_Scene0KoopaWaluigiFace;
}

void mstory3_Scene0KoopaWaluigiFace(omObjData *obj) {
    mstory3_ObjTargetFace(obj, mstory3_scene0WorkTbl[2].obj);
}

void mstory3_Scene0KoopaStep(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjPosMoveV(obj, &mstory3_scene0KoopaDestPos1, 60);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[5].unk_08 = 1;
    mstory3_scene0WorkTbl[5].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0KoopaPose(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    mstory3_MotionEndWait(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[5]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[5].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0KoopaApproach(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjPosMoveV(obj, &mstory3_scene0KoopaDestPos2, 30);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[5].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[5].obj->motion[2]].motId, 0, 10,
                       2);
    mstory3_scene0WorkTbl[5].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0KoopaAttack(omObjData *obj) {
    f32 t;
    s16 i;

    mstory3_scene0WorkTbl[9].func = mstory3_Scene0ObjIdle;
    Hu3DData[mstory3_scene0WorkTbl[5].obj->model[2]].pos.x = Hu3DData[mstory3_scene0WorkTbl[5].obj->model[1]].pos.x = -380.0f;
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[5].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[5].obj->motion[5]].motId, 0, 10, 2);
    Hu3DData[mstory3_scene0WorkTbl[2].obj->model[1]].pos.x = Hu3DData[mstory3_scene0WorkTbl[2].obj->model[2]].pos.x = 100.0f;
    Hu3DMotionModelSet(mstory3_scene0WorkTbl[2].obj->model[1], mstory3_scene0WorkTbl[2].obj->motion[3]);
    Hu3DMotionSpeedSet(mstory3_scene0WorkTbl[2].obj->model[1], 0.0f);
    Hu3DMotionTimeSet(mstory3_scene0WorkTbl[2].obj->model[1], 19.0f);
    HuAudFXPlay(0x29D);
    for (i = 0; i < 30; i++) {
        t = i * 3.0f;
        Hu3DData[mstory3_scene0WorkTbl[5].obj->model[1]].pos.x = sindf(t) * -300.0f + -80.0f;
        Hu3DData[mstory3_scene0WorkTbl[5].obj->model[2]].pos.x = sindf(t) * -175.0f + -80.0f;
        Hu3DData[mstory3_scene0WorkTbl[5].obj->model[2]].scale.x = Hu3DData[mstory3_scene0WorkTbl[5].obj->model[2]].scale.z = 5.0f;
        HuPrcVSleep();
    }
    mstory3_scene0WorkTbl[9].func = mstory3_Scene0CloudVanish;
    mstory3_scene0WorkTbl[5].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0KoopaJrADestroy(void) {
}

void mstory3_Scene0KoopaJrAProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    mstory3_scene0WorkTbl[6].obj = obj;
    mstory3_scene0WorkTbl[6].unk_08 = 0;
    mstory3_scene0WorkTbl[6].func = mstory3_Scene0ObjIdle;
    obj->model[1] = Hu3DModelRead(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(mstory3_scene0ShadowMdl);
    omObjMotionRead(obj, 0, 0xA00EF);
    omObjMotionRead(obj, 1, 0xA00F1);
    omObjMotionRead(obj, 2, 0x1D0039);
    omObjMotionRead(obj, 3, 0x1D003A);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], 500.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], 500.0f, -5.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 270.0f, 0.0f);
    omPrcSetDestructor(0, mstory3_Scene0KoopaJrADestroy);
    while (1) {
        mstory3_scene0WorkTbl[6].func(obj);
        HuPrcVSleep();
    }
}

void mstory3_Scene0KoopaJrAEnter(omObjData *obj) {
    mstory3_ObjPosMoveV(obj, &mstory3_scene0KoopaJrADestPos0, 60);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[6].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0KoopaJrALift(omObjData *obj) {
    s16 i;
    f32 y;

    Hu3DMotionShiftSet(obj->model[1], Hu3DData[mstory3_scene0WorkTbl[6].obj->motion[2]].motId, 0, 10, 0);
    HuPrcSleep(10);
    for (i = 0; i < 10; i++) {
        y = sindf(i * 9.0f) * 100.0f;
        Hu3DData[mstory3_scene0WorkTbl[5].obj->model[1]].pos.y = y;
        HuPrcVSleep();
    }
    mstory3_scene0WorkTbl[6].unk_08 = 1;
    mstory3_scene0WorkTbl[6].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0KoopaJrACarry(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], Hu3DData[mstory3_scene0WorkTbl[6].obj->motion[3]].motId, 0, 0xA, 2);
    HuPrcSleep(0xA);
    mstory3_scene0WorkTbl[6].func = mstory3_Scene0KoopaJrACarryExit;
}

void mstory3_Scene0KoopaJrACarryExit(omObjData *obj) {
    omObjData *obj6 = mstory3_scene0WorkTbl[6].obj;
    omObjData *obj7 = mstory3_scene0WorkTbl[7].obj;
    omObjData *obj5 = mstory3_scene0WorkTbl[5].obj;

    Hu3DData[obj6->model[2]].pos.x = Hu3DData[obj6->model[1]].pos.x += 10.0f;
    Hu3DData[obj7->model[2]].pos.x = Hu3DData[obj7->model[1]].pos.x += 10.0f;
    Hu3DData[obj5->model[1]].pos.x += 10.0f;
    Hu3DData[obj5->model[2]].pos.x += 10.0f;
}

void mstory3_Scene0KoopaJrBDestroy(void) {
}

void mstory3_Scene0KoopaJrBProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    mstory3_scene0WorkTbl[7].obj = obj;
    mstory3_scene0WorkTbl[7].unk_08 = 0;
    mstory3_scene0WorkTbl[7].func = mstory3_Scene0ObjIdle;
    obj->model[1] = Hu3DModelRead(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(mstory3_scene0ShadowMdl);
    Hu3DModelPosSet(obj->model[1], 500.0f, 0.0f, 700.0f);
    Hu3DModelPosSet(obj->model[2], 500.0f, -5.0f, 700.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 270.0f, 0.0f);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[mstory3_scene0WorkTbl[6].obj->motion[1]].motId, 0, 10, 2);
    omPrcSetDestructor(0, mstory3_Scene0KoopaJrBDestroy);
    while (1) {
        mstory3_scene0WorkTbl[7].func(obj);
        HuPrcVSleep();
    }
}

const Vec mstory3_scene0KoopaDestRot1 = { 0.0f, 105.7f, 0.0f };

const Vec mstory3_scene0KoopaDestRot2 = { 0.0f, 151.5f, 0.0f };

const Vec mstory3_scene0KoopaDestPos1 = { -200.0f, 0.0f, 480.0f };

const Vec mstory3_scene0KoopaDestPos2 = { -80.0f, 0.0f, 480.0f };

const Vec mstory3_scene0KoopaJrADestPos0 = { 0.0f, 0.0f, 480.0f };

const Vec mstory3_scene0KoopaJrBDestPos0 = { -400.0f, 0.0f, 700.0f };

void mstory3_Scene0KoopaJrBEnter(omObjData *obj) {
    mstory3_ObjPosMoveV(obj, &mstory3_scene0KoopaJrBDestPos0, 60);
    Hu3DModelPosSet(obj->model[1], -500.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], -500.0f, 0.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    mstory3_scene0WorkTbl[7].unk_08 = 1;
    mstory3_scene0WorkTbl[7].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0KoopaJrBCarry(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], Hu3DData[mstory3_scene0WorkTbl[6].obj->motion[3]].motId, 0, 0xA, 2);
    mstory3_scene0WorkTbl[7].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0StampDestroy(void) {
}

void mstory3_Scene0StampProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 20, 20, -1, NULL);
    mstory3_scene0WorkTbl[8].obj = obj;
    mstory3_scene0WorkTbl[8].unk_08 = 0;
    mstory3_scene0WorkTbl[8].func = mstory3_Scene0ObjIdle;
    obj->model[1] = Hu3DModelRead(0x1D0008, 0x20299);
    obj->model[2] = Hu3DModelRead(0x1D0009, 0x20299);
    obj->model[4] = Hu3DModelRead(0x1D0013, 0x2B9);
    obj->model[6] = Hu3DModelRead(0x83, 0x2B9);
    obj->model[7] = Hu3DModelLink(mstory3_scene0ShadowMdl);
    Hu3DModelAttrSet(obj->model[6], 4, 4);
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DModelAttrSet(obj->model[2], 4, 4);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DMotionAttrSet(obj->model[2], 2, 2);
    Hu3DModelPosSet(obj->model[1], 0.0f, 200.0f, 100.0f);
    Hu3DModelPosSet(obj->model[2], 0.0f, 200.0f, 100.0f);
    Hu3DModelPosSet(obj->model[4], 750.0f, 100.0f, -1500.3f);
    Hu3DModelPosSet(obj->model[6], -150.0f, 270.0f, 300.0f);
    Hu3DModelPosSet(obj->model[7], 750.0f, 0.0f, -1500.3f);
    obj->model[3] = EffectCreate(0xB0004, 0x6A9);
    EffectParamSet(obj->model[3], 4.0f, 20.0f, 4.0f);
    EffectRangeSet(obj->model[3], 60.0f);
    Hu3DParticleAttrSet(obj->model[3], 1, 0);
    Hu3DModelAttrSet(obj->model[3], 4, 4);
    obj->model[5] = EffectCreate(0xB0004, 0x6A9);
    EffectParamSet(obj->model[5], 4.0f, 20.0f, 4.0f);
    EffectRangeSet(obj->model[5], 60.0f);
    Hu3DParticleAttrSet(obj->model[5], 1, 0);
    Hu3DModelAttrSet(obj->model[5], 4, 4);
    omPrcSetDestructor(0, mstory3_Scene0StampDestroy);
    while (TRUE) {
        mstory3_scene0WorkTbl[8].func(obj);
        HuPrcVSleep();
    }
}

void mstory3_Scene0StampFlyExec(omObjData *obj) {
    Vec pos;
    MstoryPath *path[2];
    s16 i;

    path[0] = mstory3_Scene0PathCreate(mstory3_scene0StampPathA, 0);
    path[1] = mstory3_Scene0PathCreate(mstory3_scene0StampPathB, 0);
    Hu3DModelAttrSet(obj->model[1], 4, 0);
    Hu3DModelAttrSet(obj->model[3], 4, 0);
    Hu3DParticleAttrSet(obj->model[3], 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 50; i++) {
        if (i == 20) {
            Hu3DMotionShiftSet(mstory3_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[0].obj->motion[12]].motId, 0, 10, 2);
        }
        mstory3_Scene0PathPosGet(path[0], (i * (1.0f / 50.0f)) * (i * (1.0f / 50.0f)), &pos);
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        EffectPosSet(mstory3_scene0WorkTbl[8].obj->model[3], pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[4].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[4].obj->motion[2]].motId, 0, 10, 0);
    HuPrcSleep(20);
    mstory3_scene0WorkTbl[8].unk_08 = 1;
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[4].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[4].obj->motion[0]].motId, 0, 10, 0);
    HuAudFXPlay(0x218);
    for (i = 0; i < 120; i++) {
        mstory3_Scene0PathPosGet(path[1], (i * (1.0f / 120.0f)) * (i * (1.0f / 120.0f)), &pos);
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        EffectPosSet(mstory3_scene0WorkTbl[8].obj->model[3], pos.x, pos.y - 40.0f, pos.z);
        Hu3DData[obj->model[1]].rot.y += 24.0f;
        if (Hu3DData[obj->model[1]].rot.y >= 360.0f) {
            Hu3DData[obj->model[1]].rot.y -= 360.0f;
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(0x21A);
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DModelAttrSet(obj->model[3], 4, 4);
    Hu3DParticleAttrSet(obj->model[3], 1, 0);
    mstory3_Scene0PathKill(path[0]);
    mstory3_Scene0PathKill(path[1]);
    mstory3_scene0WorkTbl[8].unk_08 = 2;
    mstory3_scene0WorkTbl[8].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0KoopaFaceAll(omObjData *obj) {
    mstory3_ObjTargetFace(mstory3_scene0WorkTbl[5].obj, mstory3_scene0WorkTbl[0].obj);
    mstory3_ObjTargetFace(mstory3_scene0WorkTbl[0].obj, mstory3_scene0WorkTbl[5].obj);
    mstory3_ObjTargetFace(mstory3_scene0WorkTbl[4].obj, mstory3_scene0WorkTbl[5].obj);
    mstory3_ObjTargetFace(mstory3_scene0WorkTbl[3].obj, mstory3_scene0WorkTbl[5].obj);
}

void mstory3_Scene0StampBAppear(omObjData *obj) {
    MstoryPath *path;
    Vec pos;
    s16 i;

    path = mstory3_Scene0PathCreate(mstory3_scene0StampBPathA, 0);
    Hu3DModelPosSet(obj->model[2], -100.0f, 200.0f, 100.0f);
    EffectPosSet(obj->model[5], -100.0f, 200.0f, 100.0f);
    Hu3DModelAttrSet(obj->model[2], 4, 0);
    Hu3DModelAttrSet(obj->model[5], 4, 0);
    Hu3DParticleAttrSet(obj->model[5], 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 30; i++) {
        mstory3_Scene0PathPosGet(path, (i * (1.0f / 30.0f)) * (i * (1.0f / 30.0f)), &pos);
        pos.x -= 100.0f;
        Hu3DModelPosSet(obj->model[2], pos.x, pos.y, pos.z);
        EffectPosSet(mstory3_scene0WorkTbl[8].obj->model[5], pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    mstory3_Scene0PathKill(path);
    mstory3_scene0WorkTbl[8].unk_08 = 1;
    mstory3_scene0WorkTbl[8].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0StampBFlyExec(omObjData *obj) {
    omObjData *other = mstory3_scene0WorkTbl[2].obj;
    MstoryPath *path;
    Vec pos;
    s16 i;

    path = mstory3_Scene0PathCreate(mstory3_scene0StampBPathB, 0);
    Hu3DModelAttrSet(obj->model[6], 4, 0);
    Hu3DModelAttrSet(obj->model[2], 4, 0);
    Hu3DModelAttrSet(obj->model[5], 4, 0);
    Hu3DParticleAttrSet(obj->model[5], 1, 1);
    HuAudFXPlay(0x21F);
    for (i = 0; i < 30; i++) {
        mstory3_Scene0PathPosGet(path, i * (1.0f / 30.0f), &pos);
        pos.x -= 100.0f;
        Hu3DModelPosSet(obj->model[2], pos.x, pos.y, pos.z);
        EffectPosSet(mstory3_scene0WorkTbl[8].obj->model[5], pos.x, pos.y - 40.0f, pos.z);
        if (i == 25) {
            mstory3_scene0WorkTbl[1].func = mstory3_Scene0WaluigiAppear;
        }
        HuPrcVSleep();
    }
    mstory3_Scene0PathKill(path);
    Hu3DModelAttrSet(obj->model[5], 4, 4);
    Hu3DParticleAttrSet(obj->model[3], 1, 0);
    Hu3DData[obj->model[2]].pos.x = Hu3DData[obj->model[4]].pos.x;
    Hu3DData[obj->model[2]].pos.y = Hu3DData[obj->model[4]].pos.y;
    Hu3DData[obj->model[2]].pos.z = Hu3DData[obj->model[4]].pos.z;
    Hu3DData[obj->model[2]].rot.y = 0.0f;
    mstory3_scene0StampBSpinF = 1;
    Hu3DModelAttrSet(other->model[1], 4, 4);
    Hu3DModelAttrSet(other->model[2], 4, 4);
    mstory3_scene0WorkTbl[8].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0StampBApproach(omObjData *obj) {
    Vec pos;
    s16 i;

    pos.x = Hu3DData[obj->model[4]].pos.x;
    pos.y = Hu3DData[obj->model[4]].pos.y;
    pos.z = Hu3DData[obj->model[4]].pos.z;
    for (i = 0; i < 50; i++) {
        pos.x -= 3.5;
        pos.y += 1.75;
        pos.z += 19.25;
        Hu3DData[obj->model[2]].pos.z = Hu3DData[obj->model[4]].pos.z = pos.z;
        Hu3DData[obj->model[2]].pos.y = Hu3DData[obj->model[4]].pos.y = pos.y;
        Hu3DData[obj->model[2]].pos.x = Hu3DData[obj->model[4]].pos.x = pos.x;
        HuPrcVSleep();
    }
    mstory3_scene0WorkTbl[8].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0StampBExit(omObjData *obj) {
    s16 i;

    for (i = 0; i < 60; i++) {
        Hu3DData[obj->model[2]].pos.x = Hu3DData[obj->model[4]].pos.x += 15.0f;
        HuPrcVSleep();
    }
    mstory3_scene0WorkTbl[8].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0StampBSpinProc(void) {
    while (TRUE) {
        if (mstory3_scene0StampBSpinF == 1) {
            Hu3DData[mstory3_scene0WorkTbl[8].obj->model[2]].rot.y += 12.0f;
            Hu3DData[mstory3_scene0WorkTbl[8].obj->model[7]].pos.x = Hu3DData[mstory3_scene0WorkTbl[8].obj->model[4]].pos.x;
            Hu3DData[mstory3_scene0WorkTbl[8].obj->model[7]].pos.y = -85.8f;
            Hu3DData[mstory3_scene0WorkTbl[8].obj->model[7]].pos.z = Hu3DData[mstory3_scene0WorkTbl[8].obj->model[4]].pos.z;
        }
        HuPrcVSleep();
    }
}

void mstory3_Scene0CloudDestroy(void) {
}

void mstory3_Scene0CloudProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    mstory3_scene0WorkTbl[9].obj = obj;
    mstory3_scene0WorkTbl[9].unk_08 = 0;
    mstory3_scene0WorkTbl[9].func = mstory3_Scene0ObjIdle;
    obj->model[1] = Hu3DModelRead(0x1D0030, 0x2A8);
    obj->model[2] = Hu3DModelRead(0x83, 0x2B9);
    obj->model[3] = Hu3DModelRead(0x83, 0x2B9);
    obj->model[4] = Hu3DModelRead(0x83, 0x2B9);
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DModelAttrSet(obj->model[2], 4, 4);
    Hu3DModelAttrSet(obj->model[3], 4, 4);
    Hu3DModelAttrSet(obj->model[4], 4, 4);
    Hu3DModelTPLvlInit(obj->model[1]);
    Hu3DModelTPLvlSet(obj->model[1], 255);
    Hu3DModelPosSet(obj->model[1], 0.0f, -25.0f, 800.0f);
    Hu3DModelScaleSet(obj->model[1], 0.0f, 0.0f, 1.0f);
    omObjMotionRead(obj, 0, 0x1D0030);
    omObjMotionRead(obj, 1, 0x83);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    omPrcSetDestructor(0, mstory3_Scene0CloudDestroy);
    while (1) {
        mstory3_scene0WorkTbl[9].func(obj);
        HuPrcVSleep();
    }
}

void mstory3_Scene0CloudAppear(omObjData *obj) {
    s16 i;
    f32 scale;

    HuPrcSleep(10);
    Hu3DModelAttrSet(obj->model[1], 4, 0);
    Hu3DModelAttrSet(obj->model[2], 4, 0);
    Hu3DModelAttrSet(obj->model[3], 4, 0);
    Hu3DModelAttrSet(obj->model[4], 4, 0);
    HuAudFXPlay(0x220);
    for (i = 0; i < 10; i++) {
        scale = sindf(i * 9.0f) * 2.0f;
        Hu3DModelScaleSet(obj->model[1], scale, scale, 1.0f);
        HuPrcVSleep();
    }
    Hu3DData[mstory3_scene0WorkTbl[2].obj->model[1]].pos.x = Hu3DData[mstory3_scene0WorkTbl[2].obj->model[2]].pos.x = 100.0f;
    Hu3DData[mstory3_scene0WorkTbl[3].obj->model[1]].rot.y = 0.0f;
    Hu3DData[mstory3_scene0WorkTbl[4].obj->model[1]].rot.y = 0.0f;
    Hu3DData[mstory3_scene0WorkTbl[0].obj->model[1]].rot.y = 0.0f;
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[4].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[4].obj->motion[4]].motId, 0, 10, 2);
    mstory3_HmfAnimSet(obj->model[1], mstory3_scene0TumbleFaceSlot, mstory3_scene0TumbleFaceAnimTbl[2]);
    mstory3_scene0WorkTbl[9].func = mstory3_Scene0CloudStarUpdate;
}

void mstory3_Scene0CloudVanish(omObjData *obj) {
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    HuPrcSleep(30);
    Hu3DMotionSpeedSet(mstory3_scene0WorkTbl[2].obj->model[1], 1.0f);
    Hu3DMotionShiftSet(mstory3_scene0WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene0WorkTbl[2].obj->motion[0]].motId, 0, 10, 2);
    mstory3_scene0WorkTbl[9].unk_08 = 1;
    mstory3_scene0WorkTbl[9].func = mstory3_Scene0ObjIdle;
}

void mstory3_Scene0CloudStarUpdate(omObjData *obj) {
    f32 angle;
    s16 i;

    for (i = 2; i < 5; i++) {
        if (mstory3_scene1PlayerChr[i] == 0) {
            if ((u8)(rand8() % 7) == 0) {
                angle = (u8)(rand8() % 200) - 10.0f;
                Hu3DModelPosSet(obj->model[i], cosdf(angle) * 175.0f, sindf(angle) * 175.0f, 500.0f);
                Hu3DMotionModelSet(obj->model[i], obj->motion[1]);
                mstory3_scene1PlayerChr[i] = 1;
                mstory3_scene0CloudStarTimeTbl[i] = 10;
            }
        } else if (--mstory3_scene0CloudStarTimeTbl[i] <= 0) {
            mstory3_scene1PlayerChr[i] = 0;
        }
    }
}

void mstory3_Scene0WaluigiStruggle(omObjData *obj) {
    do {
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[8 + (rand8() & 1)]].motId, 0, 10, 0);
        mstory3_MotionEndWait(obj->model[1]);
        HuPrcVSleep();
    } while (mstory3_scene0WorkTbl[2].unk_08 != 1);
    mstory3_scene0WorkTbl[2].func = mstory3_Scene0WaluigiStruggleEnd;
}

void mstory3_Scene0WaluigiStruggleEnd(omObjData *obj) {
    mstory3_scene0WorkTbl[5].func = mstory3_Scene0KoopaAttack;
    mstory3_scene0WorkTbl[2].func = mstory3_Scene0ObjIdle;
    mstory3_scene0WorkTbl[2].unk_08 = 0;
}
