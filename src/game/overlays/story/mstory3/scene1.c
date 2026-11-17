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

extern s32 omCharModelNoTbl[][6];

extern char *mstory3_scene1PlayerAnimNameTbl[];
extern char *mstory3_scene1RivalAnimNameTbl[];

extern void (*const mstory3_sceneCreateTbl[])(void);
extern const Vec mstory3_scene1StarStartPos;
extern const Vec mstory3_scene1StampStartPos;
extern const Vec mstory3_scene1FrontRot;
extern const Vec mstory3_scene1PlayerDestRot1;
extern s16 mstory3_scene1PlayerFaceAnimTbl[3];
extern const Vec mstory3_scene1RivalDestRot2;
extern s16 mstory3_scene1RivalFaceAnimTbl[3];
extern const Vec mstory3_scene1TumbleDestRot4;
extern const Vec mstory3_scene1TumbleDestRot5;
extern Mstory3ObjWork mstory3_scene1WorkTbl[6];
extern Vec mstory3_scene1StarPos;
extern Vec mstory3_scene1StampPos;
extern s16 mstory3_scene1TumbleFaceAnimTbl[3];
extern Vec mstory3_scene1RivalPos;
extern Vec mstory3_scene1TumblePos;
extern const Vec mstory3_scene1RivalStartPos;
extern const Vec mstory3_scene1TumbleStartPos;
extern s16 mstory3_scene1TumbleFaceSlot;
extern const Vec mstory3_scene1TumbleDestRot2;
extern const Vec mstory3_scene1TumbleDestRot3;
extern s16 mstory3_scene1StarFloatStopF;
extern s16 mstory3_scene1PlayerFaceSlot;
extern s16 mstory3_scene1RivalFaceSlot;
extern s16 mstory3_scene1ShadowMdl;
extern s16 mstory3_scene1PlayerChr;
extern s16 mstory3_scene1RivalChr;

void mstory3_ObjPosMoveEx(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void mstory3_HmfAnimSet(s16 model, s16 arg1, s16 arg2);
void mstory3_ObjRotMoveV(omObjData *obj, const Vec *pos, s32 frames);
void mstory3_MotionEndWait(s16 model);
void mstory3_ObjForwardMove(omObjData *obj, f32 speed, s16 frames);
void mstory3_ObjTargetFace(omObjData *obj, omObjData *target);
void mstory3_Scene1ObjIdle(omObjData *);
void mstory3_Scene1PlayerDestroy(void);
void mstory3_Scene1RivalDestroy(void);
void mstory3_Scene1PlayerRivalFace(omObjData *obj);
void mstory3_Scene1TumbleTurn(omObjData *obj);
void mstory3_Scene1StarDestroy(void);
void mstory3_Scene1TumbleRivalFace(omObjData *obj);
void mstory3_Scene1EventIntroExec(omObjData *);
void mstory3_Scene1EventExec(omObjData *);
void mstory3_Scene1PlayerStep(omObjData *);
void mstory3_Scene1PlayerProc(void);
void mstory3_Scene1RivalProc(void);
void mstory3_Scene1TumbleProc(void);
void mstory3_Scene1TumbleDestroy(void);
void mstory3_Scene1StarProc(void);
void mstory3_Scene1StampProc(void);
void mstory3_Scene1StampDestroy(void);
void mstory3_Scene1StarFloatProc(void);
void mstory3_Scene1ObjSeLoopProc(void);
void mstory3_Scene1EventProc(void);
void mstory3_ObjPosMoveAccel(omObjData *obj, const Vec *target, s32 frames, s32 faceDir);
void mstory3_Scene1PlayerCardShow(omObjData *obj);
void mstory3_Scene1PlayerCardHide(omObjData *obj);
void mstory3_Scene1PlayerKnockBack(omObjData *obj);
void mstory3_Scene1PlayerExit(omObjData *obj);
void mstory3_Scene1RivalStep(omObjData *obj);
void mstory3_Scene1RivalKnockBack(omObjData *obj);
void mstory3_Scene1RivalExit(omObjData *obj);
void mstory3_Scene1RivalLuigiPose(omObjData *obj);
void mstory3_Scene1TumbleHop1(omObjData *obj);
void mstory3_Scene1TumbleLand(omObjData *obj);
void mstory3_Scene1TumbleHop2(omObjData *obj);
void mstory3_Scene1TumblePlayerFace(omObjData *obj);
void mstory3_Scene1StarRivalFace(omObjData *obj);
void mstory3_Scene1StarTurn(omObjData *obj);
void mstory3_Scene1StarTumbleTurn(omObjData *obj);
void mstory3_SceneEnd(void);
void mstory3_WinCreate(void);
void mstory3_WinOpen(void);
void mstory3_WinClose(void);
void mstory3_WinMesExec(s32 mess);
void mstory3_BackMotionStart(void);
void mstory3_ObjPosMoveV(omObjData *obj, const Vec *pos, s32 frames);

Vec mstory3_scene1StampPathA[4] = {
    { 0.0f, 200.0f, 100.0f },
    { -200.0f, 100.0f, -100.0f },
    { -100.0f, 300.0f, 300.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};
Vec mstory3_scene1StampPathB[4] = {
    { -100.0f, 300.0f, 300.0f },
    { -200.0f, 400.0f, -100.0f },
    { 0.0f, 200.0f, 100.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};
Vec mstory3_scene1UnusedRot0 = { 0.0f, 158.73f, 0.0f }; /* Unreferenced. */
Vec mstory3_scene1UnusedRot1 = { 0.0f, 167.01f, 0.0f }; /* Unreferenced. */
Vec mstory3_scene1StarDestRot0 = { 0.0f, 158.46f, 0.0f };
Vec mstory3_scene1RivalDestRot0 = { 0.0f, -70.43f, 0.0f };
Vec mstory3_scene1TumbleDestRot0 = { 0.0f, -77.13f, 0.0f };
Vec mstory3_scene1TumbleDestRot1 = { 0.0f, -135.0f, 0.0f };
Vec mstory3_scene1UnusedRot2 = { 0.0f, 162.4f, 0.0f };   /* Unreferenced. */
Vec mstory3_scene1UnusedRot3 = { 0.0f, -147.34f, 0.0f }; /* Unreferenced. */
Vec mstory3_scene1UnusedRot4 = { 0.0f, 306.61f, 0.0f };  /* Unreferenced. */
Vec mstory3_scene1RivalDestRot1 = { 0.0f, 90.0f, 0.0f };
Vec mstory3_scene1StarDestRot1 = { 0.0f, 50.19f, 0.0f };
Vec mstory3_scene1PlayerDestRot0 = { 0.0f, 100.78f, 0.0f };

const Vec mstory3_scene1PlayerStartPos = { -120.0f, 0.0f, 480.0f };

const Vec mstory3_scene1RivalStartPos = { 608.1f, -85.8f, -1390.3f };

const Vec mstory3_scene1TumbleStartPos = { 238.0f, 100.0f, 214.0f };

const Vec mstory3_scene1StarStartPos = { 0.0f, 200.0f, 150.0f };

const Vec mstory3_scene1StampStartPos = { 0.0f, 200.0f, 100.0f };
const Vec mstory3_scene1UnusedPos0 = { 0.0f, 0.0f, 0.0f }; /* Unreferenced. */

MstoryPath *mstory3_Scene1PathCreate(Vec *points, s32 flags) {
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

void mstory3_Scene1PathPosGet(MstoryPath *path, f32 time, Vec *result) {
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

void mstory3_Scene1PathKill(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void mstory3_Scene1Create(void) {
    mstory3_scene1PlayerChr = GwStory.unk1;
    if (mstory3_scene1PlayerChr == 0) {
        mstory3_scene1RivalChr = 1;
    } else {
        mstory3_scene1RivalChr = 0;
    }
    mstory3_WinCreate();
    mstory3_scene1ShadowMdl = Hu3DModelRead(9, 0x2B9);
    omAddPrcObj(mstory3_Scene1PlayerProc, 0x1001, 0x1000, 0);
    omAddPrcObj(mstory3_Scene1RivalProc, 0x1001, 0x1000, 0);
    omAddPrcObj(mstory3_Scene1TumbleProc, 0x1001, 0x1000, 0);
    omAddPrcObj(mstory3_Scene1StarProc, 0x1001, 0x1000, 0);
    omAddPrcObj(mstory3_Scene1StampProc, 0x1001, 0x1000, 0);
    HuPrcVSleep();
    omAddPrcObj(mstory3_Scene1EventProc, 0x1001, 0x1000, 0);
    omAddPrcObj(mstory3_Scene1StarFloatProc, 0x1001, 0x1000, 0);
    omAddPrcObj(mstory3_Scene1ObjSeLoopProc, 0x1001, 0x1000, 0);
    Hu3DModelAttrSet(mstory3_scene1ShadowMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void mstory3_Scene1ObjIdle(omObjData *obj) {
}

void mstory3_Scene1ObjSeLoopProc(void) {
    s16 seNo;
    s8 vol;
    f32 z;

    while (TRUE) {
        if (mstory3_scene1WorkTbl[0].unk_0C == 1 && Hu3DData[mstory3_scene1WorkTbl[0].obj->model[1]].motTime == 0.0f) {
            CharFXPlay((s16)mstory3_scene1WorkTbl[0].unk_10, mstory3_scene1PlayerChr);
        }
        if (mstory3_scene1WorkTbl[1].unk_0C == 1 && Hu3DData[mstory3_scene1WorkTbl[1].obj->model[1]].motTime == 0.0f) {
            seNo = CharFXPlay((s16)mstory3_scene1WorkTbl[1].unk_10, mstory3_scene1RivalChr);
            z = Hu3DData[mstory3_scene1WorkTbl[1].obj->model[1]].pos.z;
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

void mstory3_Scene1EventProc(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    mstory3_scene1WorkTbl[5].obj = obj;
    mstory3_scene1WorkTbl[5].unk_08 = 0;
    mstory3_scene1WorkTbl[5].func = mstory3_Scene1EventIntroExec;

    for (;;) {
        mstory3_scene1WorkTbl[5].func(obj);
        HuPrcVSleep();
    }
}

void mstory3_Scene1EventIntroExec(omObjData *obj) {
    Vec pos[4] = {
        { 20.0f, -20.0f, 0.0f },
        { 0.0f, 225.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 300.0f, 0.0f },
    };

    HuPrcSleep(40);
    mstory3_ObjRotMoveV(mstory3_scene1WorkTbl[3].obj, &pos[0], 10);
    mstory3_ObjRotMoveV(mstory3_scene1WorkTbl[2].obj, &pos[1], 10);
    HuAudFXPlay(0x159);
    Hu3DMotionShiftSet(mstory3_scene1WorkTbl[3].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[3].obj->motion[1]].motId, 0, 10, 2);
    mstory3_WinOpen();
    mstory3_WinMesExec(mstory3_scene1PlayerChr != 0 ? 0x5A45 : 0x5B38);
    mstory3_WinClose();
    Hu3DMotionShiftSet(mstory3_scene1WorkTbl[3].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[3].obj->motion[0]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(mstory3_scene1WorkTbl[3].obj, &pos[2], 10);
    mstory3_ObjRotMoveV(mstory3_scene1WorkTbl[2].obj, &pos[3], 10);
    mstory3_scene1WorkTbl[5].func = mstory3_Scene1EventExec;
}

void mstory3_Scene1EventExec(omObjData *obj) {
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

    Hu3DModelAttrSet(mstory3_scene1WorkTbl[4].obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(mstory3_scene1WorkTbl[4].obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DParticleAttrSet(mstory3_scene1WorkTbl[4].obj->model[2], 1, 1);
    HuAudFXPlay(0x215);
    paths[0] = mstory3_Scene1PathCreate(mstory3_scene1StampPathA, 0);
    for (i = 0; i < 40.0f; i++) {
        if (i == 30) {
            Hu3DMotionShiftSet(mstory3_scene1WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[0].obj->motion[9]].motId, 0, 10, 2);
        }
        t = i * 0.025f;
        mstory3_Scene1PathPosGet(paths[0], t * t, &cur);
        Hu3DModelPosSet(mstory3_scene1WorkTbl[4].obj->model[1], cur.x, cur.y, cur.z);
        EffectPosSet(mstory3_scene1WorkTbl[4].obj->model[2], cur.x, cur.y - 40.0f, cur.z);
        HuPrcVSleep();
    }
    mstory3_Scene1PathKill(paths[0]);
    mstory3_scene1WorkTbl[0].func = mstory3_Scene1PlayerCardShow;
    while (TRUE) {
        if (mstory3_scene1WorkTbl[0].unk_08 == 1) {
            cur.x -= 0.19999999f;
            cur.y -= 2.0f;
            cur.z += 1.0f;
            Hu3DModelPosSet(mstory3_scene1WorkTbl[4].obj->model[1], cur.x, cur.y, cur.z);
            EffectPosSet(mstory3_scene1WorkTbl[4].obj->model[2], cur.x, cur.y - 40.0f, cur.z);
            if (j++ == 30.0f) {
                j = 0;
                break;
            }
        }
        HuPrcVSleep();
    }
    HuAudFXVolSet(CharFXPlay(0x2BD, mstory3_scene1RivalChr), 80);
    HuPrcSleep(30);
    Hu3DModelAttrSet(mstory3_scene1WorkTbl[1].obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(mstory3_scene1WorkTbl[1].obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    mstory3_BackMotionStart();
    HuPrcSleep(10);
    mstory3_scene1WorkTbl[0].func = mstory3_Scene1PlayerCardHide;
    mstory3_scene1WorkTbl[2].func = mstory3_Scene1TumbleHop1;
    while (TRUE) {
        cur.x += 1.0f;
        cur.y += 10.0f;
        cur.z -= 5.0f;
        Hu3DModelPosSet(mstory3_scene1WorkTbl[4].obj->model[1], cur.x, cur.y, cur.z);
        EffectPosSet(mstory3_scene1WorkTbl[4].obj->model[2], cur.x, cur.y - 40.0f, cur.z);
        if (j++ == 6.0f) {
            break;
        }
        HuPrcVSleep();
    }
    mstory3_scene1StampPathB[0].x = cur.x;
    mstory3_scene1StampPathB[0].y = cur.y;
    mstory3_scene1StampPathB[0].z = cur.z;
    mstory3_ObjRotMoveV(mstory3_scene1WorkTbl[3].obj, &mstory3_scene1StarDestRot0, 5);
    mstory3_scene1WorkTbl[3].func = mstory3_Scene1StarRivalFace;
    while (TRUE) {
        if (mstory3_scene1WorkTbl[2].unk_08 == 5) {
            break;
        }
        HuPrcVSleep();
    }
    mstory3_MotionEndWait(mstory3_scene1WorkTbl[1].obj->model[1]);
    HuPrcSleep(30);
    mstory3_scene1WorkTbl[1].unk_0C = 1;
    mstory3_scene1WorkTbl[1].unk_10 = 40;
    Hu3DMotionSpeedSet(mstory3_scene1WorkTbl[0].obj->model[1], 0.25f);
    Hu3DMotionShiftSet(mstory3_scene1WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[0].obj->motion[10]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(mstory3_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[1].obj->motion[2]].motId, 0, 10, 2);
    mstory3_ObjPosMoveAccel(mstory3_scene1WorkTbl[1].obj, &pos[0], 180, 1);
    mstory3_scene1WorkTbl[1].unk_0C = 0;
    Hu3DMotionShiftSet(mstory3_scene1WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[0].obj->motion[0]].motId, 0, 10, 2);
    Hu3DMotionSpeedSet(mstory3_scene1WorkTbl[0].obj->model[1], 1.0f);
    mstory3_HmfAnimSet(mstory3_scene1WorkTbl[2].obj->model[1], mstory3_scene1TumbleFaceSlot, mstory3_scene1TumbleFaceAnimTbl[0]);
    Hu3DMotionShiftSet(mstory3_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[1].obj->motion[3]].motId, 0, 10, 2);
    HuPrcSleep(60);
    mstory3_HmfAnimSet(mstory3_scene1WorkTbl[2].obj->model[1], mstory3_scene1TumbleFaceSlot, mstory3_scene1TumbleFaceAnimTbl[0]);
    Hu3DMotionShiftSet(mstory3_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[1].obj->motion[0]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(mstory3_scene1WorkTbl[1].obj, &mstory3_scene1RivalDestRot0, 10);
    if (mstory3_scene1PlayerChr != 0) {
        mstory3_ObjPosMoveEx(mstory3_scene1WorkTbl[2].obj, &pos[3], 15, 0);
        Hu3DMotionShiftSet(mstory3_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[1].obj->motion[1]].motId, 0, 10, 2);
        mstory3_ObjRotMoveV(mstory3_scene1WorkTbl[1].obj, &mstory3_scene1RivalDestRot1, 10);
        Hu3DMotionShiftSet(mstory3_scene1WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[0].obj->motion[0]].motId, 0, 10, 2);
        Hu3DMotionShiftSet(mstory3_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[1].obj->motion[5]].motId, 0, 10, 0);
        HuPrcSleep(10);
        Hu3DMotionShiftSet(mstory3_scene1WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[2].obj->motion[2]].motId, 0, 10, 2);
        mstory3_MotionEndWait(mstory3_scene1WorkTbl[1].obj->model[1]);
        Hu3DMotionShiftSet(mstory3_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[1].obj->motion[5]].motId, 0, 10, 0);
        mstory3_MotionEndWait(mstory3_scene1WorkTbl[1].obj->model[1]);
        Hu3DMotionShiftSet(mstory3_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[1].obj->motion[0]].motId, 0, 10, 2);
        Hu3DMotionShiftSet(mstory3_scene1WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[2].obj->motion[0]].motId, 0, 10, 2);
        mstory3_scene1WorkTbl[2].func = mstory3_Scene1ObjIdle;
        mstory3_ObjPosMoveV(mstory3_scene1WorkTbl[2].obj, &pos[4], 8);
        mstory3_ObjRotMoveV(mstory3_scene1WorkTbl[2].obj, &mstory3_scene1TumbleDestRot0, 10);
        Hu3DMotionShiftSet(mstory3_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[1].obj->motion[1]].motId, 0, 10, 2);
        mstory3_ObjRotMoveV(mstory3_scene1WorkTbl[1].obj, &mstory3_scene1RivalDestRot0, 5);
        Hu3DMotionShiftSet(mstory3_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[1].obj->motion[0]].motId, 0, 10, 2);
        mstory3_scene1WorkTbl[3].func = mstory3_Scene1ObjIdle;
        mstory3_scene1WorkTbl[0].func = mstory3_Scene1ObjIdle;
        mstory3_ObjRotMoveV(mstory3_scene1WorkTbl[3].obj, &mstory3_scene1StarDestRot1, 5);
        mstory3_ObjRotMoveV(mstory3_scene1WorkTbl[0].obj, &mstory3_scene1PlayerDestRot0, 5);
        mstory3_WinOpen();
        mstory3_WinMesExec(0x5A46);
        mstory3_WinClose();
    } else {
        for (i = 0; i < 2; i++) {
            mstory3_ObjPosMoveEx(mstory3_scene1WorkTbl[2].obj, &pos[3], 15, 0);
            Hu3DMotionShiftSet(mstory3_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[1].obj->motion[1]].motId, 0, 10, 2);
            mstory3_ObjRotMoveV(mstory3_scene1WorkTbl[1].obj, &mstory3_scene1RivalDestRot1, 10);
            Hu3DMotionShiftSet(mstory3_scene1WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[0].obj->motion[0]].motId, 0, 10, 2);
            Hu3DMotionShiftSet(mstory3_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[1].obj->motion[5]].motId, 0, 10, 0);
            HuPrcSleep(10);
            Hu3DMotionShiftSet(mstory3_scene1WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[2].obj->motion[2]].motId, 0, 10, 2);
            mstory3_MotionEndWait(mstory3_scene1WorkTbl[1].obj->model[1]);
            if (i == 0) {
                Hu3DMotionShiftSet(mstory3_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[1].obj->motion[5]].motId, 0, 10, 0);
                mstory3_MotionEndWait(mstory3_scene1WorkTbl[1].obj->model[1]);
            }
            Hu3DMotionShiftSet(mstory3_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[1].obj->motion[0]].motId, 0, 10, 2);
            Hu3DMotionShiftSet(mstory3_scene1WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[2].obj->motion[0]].motId, 0, 10, 2);
            mstory3_scene1WorkTbl[2].func = mstory3_Scene1ObjIdle;
            mstory3_ObjPosMoveV(mstory3_scene1WorkTbl[2].obj, &pos[4], 8);
            mstory3_ObjRotMoveV(mstory3_scene1WorkTbl[2].obj, &mstory3_scene1TumbleDestRot0, 10);
            Hu3DMotionShiftSet(mstory3_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[1].obj->motion[1]].motId, 0, 10, 2);
            mstory3_ObjRotMoveV(mstory3_scene1WorkTbl[1].obj, &mstory3_scene1RivalDestRot0, 5);
            Hu3DMotionShiftSet(mstory3_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[1].obj->motion[0]].motId, 0, 10, 2);
            mstory3_scene1WorkTbl[3].func = mstory3_Scene1ObjIdle;
            mstory3_scene1WorkTbl[0].func = mstory3_Scene1ObjIdle;
            mstory3_ObjRotMoveV(mstory3_scene1WorkTbl[3].obj, &mstory3_scene1StarDestRot1, 5);
            mstory3_ObjRotMoveV(mstory3_scene1WorkTbl[0].obj, &mstory3_scene1PlayerDestRot0, 5);
            mstory3_WinOpen();
            mstory3_scene1WorkTbl[1].func = mstory3_Scene1RivalLuigiPose;
            mstory3_WinMesExec(i + 0x5B39);
            mstory3_WinClose();
            Hu3DMotionShiftSet(mstory3_scene1WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[0].obj->motion[8]].motId, 0, 10, 0);
            mstory3_MotionEndWait(mstory3_scene1WorkTbl[0].obj->model[1]);
        }
        mstory3_MotionEndWait(mstory3_scene1WorkTbl[1].obj->model[1]);
    }
    Hu3DMotionShiftSet(mstory3_scene1WorkTbl[0].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[0].obj->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(mstory3_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[1].obj->motion[1]].motId, 0, 10, 2);
    mstory3_scene1WorkTbl[1].func = mstory3_Scene1RivalStep;
    mstory3_scene1WorkTbl[2].func = mstory3_Scene1TumbleLand;
    mstory3_scene1WorkTbl[3].func = mstory3_Scene1StarTurn;
    paths[1] = mstory3_Scene1PathCreate(mstory3_scene1StampPathB, 0);
    for (i = 0; i < 50.0f; i++) {
        t = i * 0.02f;
        mstory3_Scene1PathPosGet(paths[1], t * t, &cur);
        Hu3DModelPosSet(mstory3_scene1WorkTbl[4].obj->model[1], cur.x, cur.y, cur.z);
        EffectPosSet(mstory3_scene1WorkTbl[4].obj->model[2], cur.x, cur.y - 40.0f, cur.z);
        HuPrcVSleep();
    }
    mstory3_Scene1PathKill(paths[1]);
    Hu3DModelAttrSet(mstory3_scene1WorkTbl[4].obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mstory3_scene1WorkTbl[4].obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DParticleAttrSet(mstory3_scene1WorkTbl[4].obj->model[2], 1, 0);
    HuPrcSleep(5);
    mstory3_HmfAnimSet(mstory3_scene1WorkTbl[2].obj->model[1], mstory3_scene1TumbleFaceSlot, mstory3_scene1TumbleFaceAnimTbl[2]);
    Hu3DMotionShiftSet(mstory3_scene1WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[2].obj->motion[1]].motId, 0, 10, 2);
    mstory3_scene1WorkTbl[2].func = mstory3_Scene1TumblePlayerFace;
    HuPrcSleep(10);
    mstory3_ObjPosMoveV(mstory3_scene1WorkTbl[2].obj, &pos[5], 60);
    HuPrcSleep(30);
    mstory3_scene1WorkTbl[2].func = mstory3_Scene1ObjIdle;
    mstory3_ObjRotMoveV(mstory3_scene1WorkTbl[2].obj, &mstory3_scene1TumbleDestRot1, 10);
    mstory3_WinOpen();
    mstory3_WinMesExec(mstory3_scene1PlayerChr == 0 ? 0x5A47 : 0x5B3B);
    mstory3_WinClose();
    HuPrcSleep(30);
    mstory3_scene1StarFloatStopF = 1;
    pos[2].y = pos[1].y = Hu3DData[mstory3_scene1WorkTbl[3].obj->model[1]].pos.y;
    mstory3_ObjPosMoveV(mstory3_scene1WorkTbl[3].obj, &pos[1], 3);
    HuAudFXPlay(0x217);
    mstory3_scene1WorkTbl[2].func = mstory3_Scene1TumbleHop2;
    mstory3_scene1WorkTbl[3].func = mstory3_Scene1StarTumbleTurn;
    mstory3_scene1WorkTbl[0].func = mstory3_Scene1PlayerKnockBack;
    mstory3_scene1WorkTbl[1].func = mstory3_Scene1RivalKnockBack;
    HuAudPlayerFXPlay(mstory3_scene1PlayerChr + 0x2AC, 0);
    HuAudPlayerFXPlay(mstory3_scene1RivalChr + 0x2AC, 1);
    mstory3_scene1StarFloatStopF = 0;
    mstory3_ObjPosMoveEx(mstory3_scene1WorkTbl[3].obj, &pos[2], 5, 0);
    while (TRUE) {
        if (mstory3_scene1WorkTbl[2].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    Hu3DMotionShiftSet(mstory3_scene1WorkTbl[3].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[3].obj->motion[1]].motId, 0, 10, 2);
    mstory3_WinOpen();
    mstory3_WinMesExec(mstory3_scene1PlayerChr != 0 ? 0x5A48 : 0x5B3C);
    mstory3_WinClose();
    Hu3DMotionShiftSet(mstory3_scene1WorkTbl[3].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[3].obj->motion[0]].motId, 0, 10, 2);
    mstory3_scene1WorkTbl[0].func = mstory3_Scene1PlayerExit;
    mstory3_scene1WorkTbl[1].func = mstory3_Scene1RivalExit;
    while (TRUE) {
        if (mstory3_scene1WorkTbl[0].unk_08 == 10 && mstory3_scene1WorkTbl[1].unk_08 == 10) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    mstory3_SceneEnd();
    mstory3_scene1WorkTbl[0].func = mstory3_Scene1ObjIdle;
    mstory3_scene1WorkTbl[3].func = mstory3_Scene1ObjIdle;
    mstory3_scene1WorkTbl[2].func = mstory3_Scene1ObjIdle;
    mstory3_scene1WorkTbl[4].func = mstory3_Scene1ObjIdle;
    mstory3_scene1WorkTbl[1].func = mstory3_Scene1ObjIdle;
    mstory3_scene1WorkTbl[5].func = mstory3_Scene1ObjIdle;
}

void mstory3_Scene1PlayerProc(void) {
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
    mstory3_scene1WorkTbl[0].obj = obj;
    mstory3_scene1WorkTbl[0].unk_08 = 0;
    mstory3_scene1WorkTbl[0].func = mstory3_Scene1ObjIdle;
    mstory3_scene1WorkTbl[0].unk_0C = 0;
    mstory3_scene1WorkTbl[0].unk_10 = 31;
    obj->model[1] = Hu3DModelRead(omCharModelNoTbl[mstory3_scene1PlayerChr][0] | omCharModelNoTbl[mstory3_scene1PlayerChr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory3_scene1ShadowMdl);
    obj->model[3] = Hu3DModelRead(0x1D000A, 0x2B9);
    obj->model[4] = Hu3DModelRead(0x83, 0x2B9);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(mstory3_scene1PlayerChr, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(mstory3_scene1PlayerChr, 1));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(mstory3_scene1PlayerChr, 2));
    omObjMotionRead(obj, 3, motIds[mstory3_scene1PlayerChr][0] | 0x1D0000);
    omObjMotionRead(obj, 4, motIds[mstory3_scene1PlayerChr][1] | 0x1D0000);
    omObjMotionRead(obj, 5, CharMotionDataNumGet(mstory3_scene1PlayerChr, 0x72));
    omObjMotionRead(obj, 6, CharMotionDataNumGet(mstory3_scene1PlayerChr, 0x21));
    omObjMotionRead(obj, 7, CharMotionDataNumGet(mstory3_scene1PlayerChr, 0x33));
    omObjMotionRead(obj, 8, motIds[mstory3_scene1PlayerChr][2] | 0x1D0000);
    omObjMotionRead(obj, 9, CharMotionDataNumGet(mstory3_scene1PlayerChr, 0x9B));
    omObjMotionRead(obj, 10, CharMotionDataNumGet(mstory3_scene1PlayerChr, 0x9C));
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], -120.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], -120.0f, -5.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 162.4f, 0.0f);
    if (mstory3_scene1PlayerChr == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    data = DataRead(CharMotionDataNumGet(mstory3_scene1PlayerChr, 0xA4));
    mstory3_scene1PlayerFaceAnimTbl[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, mstory3_scene1PlayerAnimNameTbl[mstory3_scene1PlayerChr]);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    Hu3DAnimAttrSet(mstory3_scene1PlayerFaceAnimTbl[0], 1, 0);
    Hu3DAnimBankSet(mstory3_scene1PlayerFaceAnimTbl[0], 0);
    mstory3_scene1PlayerFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory3_scene1PlayerFaceAnimTbl[0], 0, mstory3_scene1PlayerAnimNameTbl[mstory3_scene1PlayerChr]);
    data = DataRead(CharMotionDataNumGet(mstory3_scene1PlayerChr, 0xA9));
    mstory3_scene1PlayerFaceAnimTbl[1] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory3_scene1PlayerFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory3_scene1PlayerFaceAnimTbl[0], 0, mstory3_scene1PlayerAnimNameTbl[mstory3_scene1PlayerChr]);
    data = DataRead(CharMotionDataNumGet(mstory3_scene1PlayerChr, 0xAA));
    mstory3_scene1PlayerFaceAnimTbl[2] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory3_HmfAnimSet(obj->model[1], mstory3_scene1PlayerFaceSlot, mstory3_scene1PlayerFaceAnimTbl[0]);
    omPrcSetDestructor(0, mstory3_Scene1PlayerDestroy);
    while (TRUE) {
        mstory3_scene1WorkTbl[0].func(obj);
        HuPrcVSleep();
    }
}

char *mstory3_scene1PlayerAnimNameTbl[] = { "c000l_0_DEF", "c001l_0_DEF", "c002l_0_DEF", "c003l_0_DEF", "c004l_0_DEF", "c005l_0_DEF", "c300l_0_DEF", "c301l_0_DEF" };
char *mstory3_scene1RivalAnimNameTbl[] = { "c000l_0_DEF", "c001l_0_DEF" };

const char mstory3_scene1ItemHookName[] = "item_hook";

void mstory3_Scene1PlayerDestroy(void) {
}

void mstory3_Scene1PlayerCardShow(omObjData *obj) {
    s16 model = obj->model[1];

    HuPrcSleep(20);
    Hu3DModelAttrSet(obj->model[3], 0x4000, 0x4000);
    Hu3DModelHookSet(obj->model[3], obj->model[1], mstory3_scene1ItemHookName);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    mstory3_MotionEndWait(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    mstory3_MotionEndWait(model);
    mstory3_scene1WorkTbl[0].func = mstory3_Scene1ObjIdle;
    mstory3_scene1WorkTbl[0].unk_08 = 1;
}

void mstory3_Scene1PlayerCardHide(omObjData *obj) {
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
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    mstory3_scene1WorkTbl[0].func = mstory3_Scene1PlayerRivalFace;
}

void mstory3_Scene1PlayerRivalFace(omObjData *obj) {
    mstory3_ObjTargetFace(obj, mstory3_scene1WorkTbl[1].obj);
}

void mstory3_Scene1PlayerStep(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory3_scene1WorkTbl[0].unk_0C = 1;
    mstory3_scene1WorkTbl[0].unk_10 = 31;
    mstory3_ObjForwardMove(obj, 3.5f, 15);
    mstory3_HmfAnimSet(obj->model[1], mstory3_scene1PlayerFaceSlot, mstory3_scene1PlayerFaceAnimTbl[2]);
    mstory3_HmfAnimSet(mstory3_scene1WorkTbl[1].obj->model[1], mstory3_scene1RivalFaceSlot, mstory3_scene1RivalFaceAnimTbl[2]);
    mstory3_scene1WorkTbl[0].unk_0C = 0;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[5]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(mstory3_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[1].obj->motion[4]].motId, 0, 10, 2);
    mstory3_scene1WorkTbl[0].func = mstory3_Scene1ObjIdle;
}

void mstory3_Scene1PlayerKnockBack(omObjData *obj) {
    Vec pos = mstory3_scene1PlayerDestRot1;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x - 5.0f;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    target = tmp;
    mstory3_HmfAnimSet(obj->model[1], mstory3_scene1PlayerFaceSlot, mstory3_scene1PlayerFaceAnimTbl[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[4], Hu3DData[obj->model[1]].pos.x, Hu3DData[obj->model[1]].pos.y, Hu3DData[obj->model[1]].pos.z);
    Hu3DModelAttrSet(obj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    mstory3_ObjPosMoveV(obj, &target, 10);
    mstory3_MotionEndWait(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(obj, &pos, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory3_HmfAnimSet(obj->model[1], mstory3_scene1PlayerFaceSlot, mstory3_scene1PlayerFaceAnimTbl[0]);
    mstory3_scene1WorkTbl[0].func = mstory3_Scene1ObjIdle;
}

void mstory3_Scene1PlayerExit(omObjData *obj) {
    Vec pos = mstory3_scene1FrontRot;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 1200.0f;
    target = tmp;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(obj, &pos, 10);
    mstory3_scene1WorkTbl[2].func = mstory3_Scene1TumbleTurn;
    HuAudPlayerFXPlay(mstory3_scene1PlayerChr + 0x275, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 0);
    mstory3_MotionEndWait(obj->model[1]);
    mstory3_scene1WorkTbl[0].unk_08 = 10;
    while (TRUE) {
        if (mstory3_scene1WorkTbl[1].unk_08 != 10) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
    mstory3_scene1WorkTbl[0].unk_0C = 1;
    mstory3_scene1WorkTbl[0].unk_10 = 40;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(10);
    mstory3_ObjPosMoveV(obj, &target, 60);
    mstory3_scene1WorkTbl[0].unk_0C = 0;
    mstory3_scene1WorkTbl[0].func = mstory3_Scene1ObjIdle;
}

void mstory3_Scene1RivalProc(void) {
    s16 chrs[2] = { 0, 1 };
    s32 motIds[2] = { 0x3B, 0x44 };
    omObjData *obj;
    s16 idx;
    void *data;

    idx = mstory3_scene1PlayerChr == 0;
    obj = omAddObj(10, 20, 20, -1, NULL);
    mstory3_scene1WorkTbl[1].obj = obj;
    mstory3_scene1WorkTbl[1].unk_08 = 0;
    mstory3_scene1WorkTbl[1].func = mstory3_Scene1ObjIdle;
    mstory3_scene1WorkTbl[1].unk_0C = 0;
    mstory3_scene1WorkTbl[1].unk_10 = 31;
    if (idx == 0) {
        obj->model[1] = Hu3DModelRead(0x200A0, 0x2A9);
    } else {
        obj->model[1] = Hu3DModelRead(0x300A0, 0x2A9);
    }
    obj->model[2] = Hu3DModelLink(mstory3_scene1ShadowMdl);
    obj->model[3] = Hu3DModelRead(0x83, 0x2B9);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chrs[idx], 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chrs[idx], 1));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chrs[idx], 2));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chrs[idx], 0x13));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chrs[idx], 0x72));
    omObjMotionRead(obj, 5, motIds[idx] | 0x1D0000);
    omObjMotionRead(obj, 6, CharMotionDataNumGet(chrs[idx], 0x21));
    omObjMotionRead(obj, 7, CharMotionDataNumGet(chrs[idx], 0x33));
    omObjMotionRead(obj, 8, CharMotionDataNumGet(chrs[idx], 0x2F));
    if (mstory3_scene1PlayerChr == 0) {
        omObjMotionRead(obj, 9, 0x1D0045);
    }
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    mstory3_scene1RivalPos = mstory3_scene1RivalStartPos;
    Hu3DModelPosSet(obj->model[1], mstory3_scene1RivalPos.x, mstory3_scene1RivalPos.y, mstory3_scene1RivalPos.z);
    Hu3DModelPosSet(obj->model[2], mstory3_scene1RivalPos.x, mstory3_scene1RivalPos.y - -5.0f, mstory3_scene1RivalPos.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, -14.48f, 0.0f);
    data = DataRead(CharMotionDataNumGet(chrs[idx], 0xA4));
    mstory3_scene1RivalFaceAnimTbl[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, mstory3_scene1RivalAnimNameTbl[idx]);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    Hu3DAnimAttrSet(mstory3_scene1RivalFaceAnimTbl[0], 1, 0);
    Hu3DAnimBankSet(mstory3_scene1RivalFaceAnimTbl[0], 0);
    mstory3_scene1RivalFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory3_scene1RivalFaceAnimTbl[0], 0, mstory3_scene1RivalAnimNameTbl[idx]);
    data = DataRead(CharMotionDataNumGet(chrs[idx], 0xA9));
    mstory3_scene1RivalFaceAnimTbl[1] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory3_scene1RivalFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory3_scene1RivalFaceAnimTbl[0], 0, mstory3_scene1RivalAnimNameTbl[idx]);
    data = DataRead(CharMotionDataNumGet(chrs[idx], 0xAA));
    mstory3_scene1RivalFaceAnimTbl[2] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory3_HmfAnimSet(obj->model[1], mstory3_scene1RivalFaceSlot, mstory3_scene1RivalFaceAnimTbl[0]);
    omPrcSetDestructor(0, mstory3_Scene1RivalDestroy);
    while (TRUE) {
        mstory3_scene1WorkTbl[1].func(obj);
        HuPrcVSleep();
    }
}

void mstory3_Scene1RivalDestroy(void) {
}

void mstory3_Scene1RivalStep(omObjData *obj) {
    mstory3_scene1WorkTbl[1].unk_0C = 1;
    mstory3_scene1WorkTbl[1].unk_10 = 31;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjForwardMove(obj, 4.5f, 15);
    mstory3_scene1WorkTbl[1].unk_0C = 0;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory3_scene1WorkTbl[1].func = mstory3_Scene1ObjIdle;
    mstory3_scene1WorkTbl[0].func = mstory3_Scene1PlayerStep;
}

void mstory3_Scene1RivalKnockBack(omObjData *obj) {
    Vec pos = mstory3_scene1RivalDestRot2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x + 5.0f;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    target = tmp;
    mstory3_HmfAnimSet(obj->model[1], mstory3_scene1RivalFaceSlot, mstory3_scene1RivalFaceAnimTbl[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[3], Hu3DData[obj->model[1]].pos.x, Hu3DData[obj->model[1]].pos.y, Hu3DData[obj->model[1]].pos.z);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    mstory3_ObjPosMoveV(obj, &target, 10);
    mstory3_MotionEndWait(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(obj, &pos, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory3_HmfAnimSet(obj->model[1], mstory3_scene1RivalFaceSlot, mstory3_scene1RivalFaceAnimTbl[0]);
    mstory3_scene1WorkTbl[1].func = mstory3_Scene1ObjIdle;
}

void mstory3_Scene1RivalExit(omObjData *obj) {
    Vec pos = mstory3_scene1FrontRot;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 1200.0f;
    target = tmp;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory3_ObjRotMoveV(obj, &pos, 10);
    HuAudPlayerFXPlay(mstory3_scene1RivalChr + 0x275, 1);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 0);
    mstory3_MotionEndWait(obj->model[1]);
    mstory3_scene1WorkTbl[1].unk_08 = 10;
    while (TRUE) {
        if (mstory3_scene1WorkTbl[0].unk_08 != 10) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
    mstory3_scene1WorkTbl[1].unk_0C = 1;
    mstory3_scene1WorkTbl[1].unk_10 = 40;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(10);
    mstory3_ObjPosMoveV(obj, &target, 60);
    mstory3_scene1WorkTbl[1].unk_0C = 0;
    mstory3_scene1WorkTbl[0].func = mstory3_Scene1ObjIdle;
}

void mstory3_Scene1RivalLuigiPose(omObjData *obj) {
    Hu3DMotionShiftSet(mstory3_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[1].obj->motion[9]].motId, 0, 10, 0);
    mstory3_MotionEndWait(obj->model[1]);
    mstory3_scene1WorkTbl[1].func = mstory3_Scene1ObjIdle;
}

const Vec mstory3_scene1PlayerDestRot1 = { 0.0f, 180.0f, 0.0f };

const Vec mstory3_scene1FrontRot = { 0.0f, 0.0f, 0.0f };

const Vec mstory3_scene1RivalDestRot2 = { 0.0f, -180.0f, 0.0f };

const char mstory3_scene1TumbleAnimName[] = "c204n_0_DEF";

const Vec mstory3_scene1TumbleDestRot2 = { 0.0f, 167.0f, 0.0f };

const Vec mstory3_scene1TumbleDestRot3 = { 0.0f, -135.0f, 0.0f };

const Vec mstory3_scene1TumbleDestRot4 = { 0.0f, -53.39f, 0.0f };

const Vec mstory3_scene1TumbleDestRot5 = { 0.0f, -53.390015f, 0.0f };
const Vec mstory3_scene1UnusedRot5 = { 0.0f, 0.0f, 0.0f }; /* Unreferenced. */

void mstory3_Scene1TumbleProc(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(10, 20, 20, -1, NULL);
    mstory3_scene1WorkTbl[2].obj = obj;
    mstory3_scene1WorkTbl[2].unk_08 = 0;
    obj->model[1] = Hu3DModelRead(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory3_scene1ShadowMdl);
    omObjMotionRead(obj, 0, 0xA0076);
    omObjMotionRead(obj, 1, 0x1D0029);
    omObjMotionRead(obj, 2, 0x1D002A);
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    mstory3_scene1TumblePos = mstory3_scene1TumbleStartPos;
    Hu3DModelPosSet(obj->model[1], mstory3_scene1TumblePos.x, mstory3_scene1TumblePos.y, mstory3_scene1TumblePos.z);
    Hu3DModelPosSet(obj->model[2], mstory3_scene1TumblePos.x, -5.0f, mstory3_scene1TumblePos.z);
    Hu3DModelRotSet(obj->model[1], 20.0f, 320.0f, 0.0f);
    data = DataRead(0xA007E);
    mstory3_scene1TumbleFaceAnimTbl[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, mstory3_scene1TumbleAnimName);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    Hu3DAnimAttrSet(mstory3_scene1TumbleFaceAnimTbl[0], 1, 0);
    Hu3DAnimBankSet(mstory3_scene1TumbleFaceAnimTbl[0], 0);
    mstory3_scene1TumbleFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory3_scene1TumbleFaceAnimTbl[0], 0, mstory3_scene1TumbleAnimName);
    data = DataRead(0xA0083);
    mstory3_scene1TumbleFaceAnimTbl[1] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory3_scene1TumbleFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory3_scene1TumbleFaceAnimTbl[0], 0, mstory3_scene1TumbleAnimName);
    data = DataRead(0xA0080);
    mstory3_scene1TumbleFaceAnimTbl[2] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory3_HmfAnimSet(obj->model[1], mstory3_scene1TumbleFaceSlot, mstory3_scene1TumbleFaceAnimTbl[0]);
    omPrcSetDestructor(0, mstory3_Scene1TumbleDestroy);
    mstory3_scene1WorkTbl[2].func = mstory3_Scene1ObjIdle;
    while (TRUE) {
        mstory3_scene1WorkTbl[2].func(obj);
        HuPrcVSleep();
    }
}

void mstory3_Scene1TumbleDestroy(void) {
}

void mstory3_Scene1TumbleHop1(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec target = mstory3_scene1TumbleDestRot2;
    f32 y;
    s16 i;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    mstory3_HmfAnimSet(model, mstory3_scene1TumbleFaceSlot, mstory3_scene1TumbleFaceAnimTbl[1]);
    for (i = 0; i < 13; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        Hu3DData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    mstory3_ObjRotMoveV(obj, &target, 5);
    mstory3_HmfAnimSet(model, mstory3_scene1TumbleFaceSlot, mstory3_scene1TumbleFaceAnimTbl[0]);
    Hu3DMotionShiftSet(mstory3_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[1].obj->motion[8]].motId, 0, 10, 0);
    HuPrcSleep(mstory3_scene1PlayerChr != 0 ? 30 : 35);
    HuAudFXVolSet(CharFXPlay(0x28F, mstory3_scene1RivalChr), 0x60);
    mstory3_scene1WorkTbl[2].func = mstory3_Scene1TumbleRivalFace;
    mstory3_scene1WorkTbl[2].unk_08 = 5;
}

void mstory3_Scene1TumbleRivalFace(omObjData *obj) {
    mstory3_ObjTargetFace(obj, mstory3_scene1WorkTbl[1].obj);
}

void mstory3_Scene1TumbleLand(omObjData *obj) {
    while (TRUE) {
        if (Hu3DData[obj->model[1]].pos.y > 100.0f) {
            Hu3DData[obj->model[1]].pos.y -= 2.0f;
            HuPrcVSleep();
        } else {
            break;
        }
    }
    Hu3DData[obj->model[1]].pos.y = 100.0f;
    mstory3_scene1WorkTbl[2].func = mstory3_Scene1ObjIdle;
}

void mstory3_Scene1TumbleHop2(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec target = mstory3_scene1TumbleDestRot3;
    f32 y;
    s16 i;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    mstory3_HmfAnimSet(model, mstory3_scene1TumbleFaceSlot, mstory3_scene1TumbleFaceAnimTbl[1]);
    Hu3DMotionShiftSet(mstory3_scene1WorkTbl[2].obj->model[1], Hu3DData[mstory3_scene1WorkTbl[2].obj->motion[0]].motId, 0, 10, 2);
    for (i = 0; i < 15; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        Hu3DData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    mstory3_ObjRotMoveV(obj, &target, 10);
    mstory3_scene1WorkTbl[2].func = mstory3_Scene1ObjIdle;
    mstory3_scene1WorkTbl[2].unk_08 = 1;
}

void mstory3_Scene1TumbleTurn(omObjData *obj) {
    Vec pos = mstory3_scene1TumbleDestRot4;

    mstory3_HmfAnimSet(obj->model[1], mstory3_scene1TumbleFaceSlot, mstory3_scene1TumbleFaceAnimTbl[0]);
    mstory3_ObjRotMoveV(obj, &pos, 10);
    while (TRUE) {
        mstory3_ObjTargetFace(mstory3_scene1WorkTbl[2].obj, mstory3_scene1WorkTbl[0].obj);
        HuPrcVSleep();
    }
}

void mstory3_Scene1TumblePlayerFace(omObjData *obj) {
    mstory3_ObjTargetFace(obj, mstory3_scene1WorkTbl[0].obj);
}

void mstory3_Scene1StarProc(void) {
    omObjData *obj;

    obj = omAddObj(0xA, 20, 20, -1, NULL);
    mstory3_scene1WorkTbl[3].obj = obj;
    mstory3_scene1WorkTbl[3].unk_08 = 0;
    obj->model[1] = Hu3DModelRead(0xA0122, 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory3_scene1ShadowMdl);
    AuraCreate(obj->model[1]);
    omObjMotionRead(obj, 0, 0xA0123);
    omObjMotionRead(obj, 1, 0xA0125);
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    mstory3_scene1StarPos = mstory3_scene1StarStartPos;
    Hu3DModelPosSet(obj->model[1], mstory3_scene1StarPos.x, mstory3_scene1StarPos.y, mstory3_scene1StarPos.z);
    Hu3DModelPosSet(obj->model[2], mstory3_scene1StarPos.x, -5.0f, mstory3_scene1StarPos.z);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    omPrcSetDestructor(0, mstory3_Scene1StarDestroy);
    mstory3_scene1WorkTbl[3].func = mstory3_Scene1ObjIdle;
    while (1) {
        mstory3_scene1WorkTbl[3].func(obj);
        HuPrcVSleep();
    }
}

void mstory3_Scene1StarDestroy(void) {
}

void mstory3_Scene1StarFloatProc(void) {
    f32 angle = 0.0f;
    omObjData *obj = mstory3_scene1WorkTbl[3].obj;
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
        if (mstory3_scene1StarFloatStopF != 1) {
            Hu3DModelPosSet(obj->model[1], pos.x, ofs + pos.y, pos.z);
        }
        HuPrcVSleep();
    }
}

void mstory3_Scene1StarRivalFace(omObjData *obj) {
    mstory3_ObjTargetFace(obj, mstory3_scene1WorkTbl[1].obj);
}

void mstory3_Scene1StarTurn(omObjData *obj) {
    Vec pos = mstory3_scene1FrontRot;

    mstory3_ObjRotMoveV(obj, &pos, 10);
    mstory3_scene1WorkTbl[3].func = mstory3_Scene1ObjIdle;
}

void mstory3_Scene1StarTumbleTurn(omObjData *obj) {
    Vec pos = mstory3_scene1TumbleDestRot5;

    mstory3_ObjRotMoveV(mstory3_scene1WorkTbl[2].obj, &pos, 10);
    mstory3_scene1WorkTbl[3].func = mstory3_Scene1ObjIdle;
}

void mstory3_Scene1StampProc(void) {
    omObjData *obj;

    obj = omAddObj(0xA, 20, 20, -1, NULL);
    mstory3_scene1WorkTbl[4].obj = obj;
    mstory3_scene1WorkTbl[4].unk_08 = 0;
    mstory3_scene1WorkTbl[4].func = mstory3_Scene1ObjIdle;
    obj->model[1] = Hu3DModelRead(0x1D0007, 0x20299);
    obj->model[2] = EffectCreate(0xB0004, 0x6A9);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    mstory3_scene1StampPos = mstory3_scene1StampStartPos;
    Hu3DModelPosSet(obj->model[1], mstory3_scene1StampPos.x, mstory3_scene1StampPos.y, mstory3_scene1StampPos.z);
    EffectParamSet(obj->model[2], 4.0f, 20.0f, 4.0f);
    EffectRangeSet(obj->model[2], 60.0f);
    Hu3DParticleAttrSet(obj->model[2], 1, 0);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    omPrcSetDestructor(0, mstory3_Scene1StampDestroy);
    while (1) {
        mstory3_scene1WorkTbl[4].func(obj);
        HuPrcVSleep();
    }
}

void mstory3_Scene1StampDestroy(void) {
}
