#include "common.h"
#include "game/hmfmath.h"
#include "mstory5.h"

typedef struct MstoryPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ u16 flags;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec *points;
    /* 0x0C */ f32 (*intervals)[2];
} MstoryPath; // sizeof 0x10

extern const Vec mstory5_scene1KoopaJrBStartPos;
extern const Vec mstory5_scene1PlayerDestRot2;
extern const Vec mstory5_scene1StarDestRot6;
extern const Vec mstory5_scene1StarDestRot7;
extern const Vec mstory5_scene1TumbleDestRot8;
extern const Vec mstory5_scene1PlayerDestRot0;
extern const Vec mstory5_scene1PlayerDestRot1;
extern void (*const mstory5_sceneCreateTbl[])(void);
extern StoryObjWork mstory5_scene1WorkTbl[9];
extern StoryObjWork mstory5_scene1EventWork;
extern StoryObjWork mstory5_scene1SubEventWork;
extern Vec mstory5_scene1KoopaJrBPos;
extern s16 mstory5_scene1ShadowMdl;
extern Vec mstory5_scene1KoopaPos;
extern const Vec mstory5_scene1KoopaStartPos;
extern s16 mstory5_scene1ShockMdl;
extern s16 mstory5_scene1TumbleFaceAnim0;
extern s32 mstory5_scene1TumbleFaceAnimTbl[4];
extern Vec mstory5_scene1TumblePos;
extern const Vec mstory5_scene1TumbleStartPos;
extern s16 mstory5_scene1TumbleFaceAnim2;
extern s16 mstory5_scene1TumbleFaceSlot;
extern s16 mstory5_scene1PlayerFaceAnim1;
extern s16 mstory5_scene1DaisyFaceAnimTbl[4];
extern s16 mstory5_scene1PlayerFaceAnimTbl[4];
extern Vec mstory5_scene1DaisyPos;
extern const Vec mstory5_scene1DaisyStartPos;
extern const Vec mstory5_scene1PlayerDestRot4;
extern const Vec mstory5_scene1DaisyDestRot2;
extern Vec mstory5_scene1StampPos;
extern const Vec mstory5_scene1StampStartPos;
extern const s32 mstory5_scene1StampMdlTbl[];
extern s16 mstory5_scene1StampEff;
extern Vec mstory5_scene1RivalPos;
extern const Vec mstory5_scene1RivalStartPos;
extern Vec mstory5_scene1KoopaJrAPos;
extern const Vec mstory5_scene1KoopaJrAStartPos;
extern const Vec mstory5_scene1TumbleDestRot2;
extern const Vec mstory5_scene1TumbleDestRot3;
extern const Vec mstory5_scene1TumbleDestRot4;
extern const Vec mstory5_scene1TumbleDestRot5;
extern const Vec mstory5_scene1TumbleDestRot6;
extern const Vec mstory5_scene1TumbleDestPos0;
extern const Vec mstory5_scene1TumbleDestPos1;
extern const Vec mstory5_scene1StarDestRot3;
extern const Vec mstory5_scene1StarDestRot4;
extern s16 mstory5_scene1TumbleFaceAnim1;
extern const Vec mstory5_scene1TumbleDestRot0;
extern const Vec mstory5_scene1DaisyDestRot0;
extern const Vec mstory5_scene1TumbleDestRot7;
extern const Vec mstory5_scene1DaisyDestRot1;
extern const Vec mstory5_scene1StarDestRot5;
extern const Vec mstory5_scene1PlayerDestRot3;
extern const Vec mstory5_scene1StarDestPos2;
extern const Vec mstory5_scene1StarDestPos3;
extern const Vec mstory5_scene1TumbleDestPos2;
extern const Vec mstory5_scene1TumbleDestPos3;
extern s16 mstory5_scene1TumbleFaceAnim3;
extern s32 omCharModelNoTbl[][6];
extern Vec mstory5_scene1PlayerPos;
extern Vec mstory5_scene1StarPos;
extern const Vec mstory5_scene1StarStartPos;
extern const Vec mstory5_scene1PlayerStartPos;
extern const s32 mstory5_scene1PlayerMot5Tbl[];
extern const s32 mstory5_scene1PlayerMot6Tbl[];
extern const s32 mstory5_scene1PlayerMot7Tbl[];
extern const s32 mstory5_scene1PlayerMot9Tbl[];
extern const s32 mstory5_scene1PlayerMot10Tbl[];

s16 mstory5_scene1StarFloatStopF = 0;
s32 mstory5_scene1StarFloatF = 0;
Vec mstory5_scene1StampPathA[4] = {
    { 0.0f, 200.0f, 100.0f },
    { -200.0f, 100.0f, -100.0f },
    { -100.0f, 300.0f, 300.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};
Vec mstory5_scene1StampPathB[6] = {
    { -100.0f, 300.0f, 300.0f },
    { -200.0f, 200.0f, 100.0f },
    { 0.0f, 300.0f, -100.0f },
    { 400.0f, 400.0f, 200.0f },
    { -50.0f, 120.0f, 450.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};
Vec mstory5_scene1StampBPath[4] = {
    { 100.0f, 200.0f, 100.0f },
    { -100.0f, 100.0f, -100.0f },
    { 0.0f, 300.0f, 300.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};

void mstory5_ObjPosMoveEx(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void mstory5_ObjRotMoveV(omObjData *obj, const Vec *pos, s32 frames);
void mstory5_ObjRotMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void mstory5_MotionEndWait(s16 model);
void mstory5_Scene1ObjIdle(omObjData *obj);
void mstory5_Scene1PlayerDestroy(void);
void mstory5_Scene1StarDestroy(void);
void mstory5_Scene1TumbleExec(omObjData *obj);
void mstory5_Scene1StarEyesASwap(void);
void mstory5_Scene1StarEyesBSwap(void);
void mstory5_Scene1ObjTargetFace(omObjData *obj, omObjData *target);
void mstory5_ObjForwardMove(omObjData *obj, f32 speed, s16 frames);
void mstory5_Scene1PlayerStep(omObjData *obj);
void mstory5_Scene1ObjSeLoopStart(s32 index, s32 seNo);
void mstory5_Scene1ObjSeLoopStop(s32 index);
void mstory5_Scene1DaisySeFadeIn(omObjData *obj);
void mstory5_ObjPosMoveAccelXYZ(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 faceDir);
MstoryPath *mstory5_Scene1PathCreate(Vec *points, s32 flags);
void mstory5_Scene1PathPosGet(MstoryPath *path, f32 time, Vec *result);
void mstory5_Scene1StampDestroy(void);
void mstory5_Scene1RivalDestroy(void);
void mstory5_Scene1RivalExec(omObjData *obj);
void mstory5_Scene1PlayerProc(void);
void mstory5_Scene1TumbleProc(void);
void mstory5_Scene1DaisyDestroy(void);
void mstory5_Scene1PlayerStampExec(omObjData *obj);
void mstory5_Scene1PlayerDaisyFace(omObjData *obj);
void mstory5_Scene1TumbleExit(omObjData *obj);
void mstory5_Scene1TumbleHop1(omObjData *obj);
void mstory5_Scene1EventExec(omObjData *obj);
void mstory5_Scene1DaisyEnter(omObjData *obj);
void mstory5_Scene1DaisyExit(omObjData *obj);
void mstory5_Scene1KoopaExec(omObjData *obj);
void mstory5_Scene1KoopaJrAEnter(omObjData *obj);
void mstory5_Scene1KoopaJrBEnter(omObjData *obj);
void mstory5_Scene1TumbleDaisyFace(omObjData *obj);
void mstory5_Scene1TumbleHop2(omObjData *obj);
void mstory5_Scene1StarExit(omObjData *arg0);
void mstory5_Scene1StarTurn1(omObjData *obj);
void mstory5_Scene1StampFlyExec(omObjData *obj);
void mstory5_Scene1TumbleDestroy(void);
void mstory5_Scene1RivalProc(void);
void mstory5_Scene1DaisyProc(void);
void mstory5_Scene1KoopaProc(void);
void mstory5_Scene1KoopaDestroy(void);
void mstory5_Scene1KoopaJrAProc(void);
void mstory5_Scene1StarProc(void);
void mstory5_Scene1EventProc(void);
void mstory5_Scene1SubEventProc(void);
void mstory5_Scene1StampProc(void);
void mstory5_Scene1StarFloatProc(void);
void mstory5_Scene1ObjSeLoopProc(void);
void mstory5_Scene1KoopaJrBProc(void);
void mstory5_Scene1KoopaJrBDestroy(void);
void mstory5_Scene1StampBShowExec(omObjData *obj);
void mstory5_Scene1DaisyStep(omObjData *obj);
void mstory5_Scene1StarTurn2(omObjData *obj);
void mstory5_Scene1TumblePlayerFace(omObjData *obj);
void mstory5_Scene1PlayerKnockBack(omObjData *obj);
void mstory5_Scene1DaisyKnockBack(omObjData *obj);
void mstory5_Scene1PlayerPose(omObjData *obj);
void mstory5_Scene1DaisyPose(omObjData *obj);
void mstory5_Scene1StarEyesASet(void);
void mstory5_Scene1GroupStepBack(omObjData *obj);
void mstory5_Scene1EventMesExec(omObjData *obj);
void mstory5_Scene1DaisyMotionEndWait(omObjData *obj);
void mstory5_Scene1GroupTurn(omObjData *obj);
void mstory5_Scene1KoopaJrADestroy(void);
void mstory5_BackMotionStart(void);
void mstory5_SceneEnd(void);
void mstory5_StampCardStart(s32 arg0);
s32 mstory5_StampCardDoneCheck(void);
void mstory5_HmfAnimSet(s16 model, s16 animSlot, s16 anim);
void mstory5_WinCreate(void);
void mstory5_WinOpen(void);
void mstory5_WinClose(void);
void mstory5_WinMesExec(s32 mess);
void mstory5_WinMesSet(s32 mess);
void mstory5_WinMesWait(void);
s32 mstory5_PlayerChrCheck(s32 character);
void mstory5_ObjPosMoveV(omObjData *obj, const Vec *pos, s32 frames);
void mstory5_ObjPosMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void mstory5_ObjPosMoveExXYZ(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3);

MstoryPath *mstory5_Scene1PathCreate(Vec *points, s32 flags) {
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

void mstory5_Scene1PathPosGet(MstoryPath *path, f32 time, Vec *result) {
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

void mstory5_Scene1PathKill(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void mstory5_Scene1Create(void) {
    mstory5_WinCreate();
    mstory5_scene1ShadowMdl = Hu3DModelRead(9, 0x2B9);
    mstory5_scene1ShockMdl = Hu3DModelRead(0x83, 0x2B9);
    omAddPrcObj(mstory5_Scene1PlayerProc, 0x1002, 0x800, 0);
    omAddPrcObj(mstory5_Scene1TumbleProc, 0x1002, 0x800, 0);
    omAddPrcObj(mstory5_Scene1RivalProc, 0x1002, 0x800, 0);
    omAddPrcObj(mstory5_Scene1DaisyProc, 0x1002, 0x800, 0);
    omAddPrcObj(mstory5_Scene1KoopaProc, 0x1002, 0x800, 0);
    omAddPrcObj(mstory5_Scene1KoopaJrAProc, 0x1002, 0x800, 0);
    omAddPrcObj(mstory5_Scene1KoopaJrBProc, 0x1002, 0x800, 0);
    omAddPrcObj(mstory5_Scene1StarProc, 0x1002, 0x800, 0);
    omAddPrcObj(mstory5_Scene1EventProc, 0x1002, 0x800, 0);
    omAddPrcObj(mstory5_Scene1SubEventProc, 0x1002, 0x800, 0);
    omAddPrcObj(mstory5_Scene1StampProc, 0x384, 0x800, 0);
    omAddPrcObj(mstory5_Scene1StarFloatProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory5_Scene1ObjSeLoopProc, 0x1001, 0x800, 0);
    HuPrcVSleep();
    Hu3DModelAttrSet(mstory5_scene1ShadowMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mstory5_scene1ShockMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void mstory5_Scene1ObjIdle(omObjData *obj) {
}

void mstory5_Scene1PlayerProc(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 6, 16, -1, NULL);
    mstory5_scene1WorkTbl[0].obj = obj;
    mstory5_scene1WorkTbl[0].unk_08 = 0;
    mstory5_scene1WorkTbl[0].unk_0C = 0;
    chr = GwStory.unk1;
    obj->model[1] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory5_scene1ShadowMdl);
    if (GwStory.unk1 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    obj->model[3] = Hu3DModelRead(0x1D000A, 0x2B9);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->model[4] = Hu3DModelLink(mstory5_scene1ShockMdl);
    Hu3DModelAttrSet(obj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 0x9C));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 1));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chr, 0x21));
    omObjMotionRead(obj, 5, mstory5_scene1PlayerMot5Tbl[chr]);
    omObjMotionRead(obj, 6, mstory5_scene1PlayerMot6Tbl[chr]);
    omObjMotionRead(obj, 7, mstory5_scene1PlayerMot7Tbl[chr]);
    omObjMotionRead(obj, 8, CharMotionDataNumGet(chr, 0x33));
    omObjMotionRead(obj, 9, mstory5_scene1PlayerMot9Tbl[chr]);
    omObjMotionRead(obj, 10, mstory5_scene1PlayerMot10Tbl[chr]);
    omObjMotionRead(obj, 11, CharMotionDataNumGet(chr, 0x72));
    omObjMotionRead(obj, 12, CharMotionDataNumGet(chr, 0x9B));
    mstory5_scene1PlayerFaceAnimTbl[0] = CharAnimCreate(obj->model[1], 2, chr, CharMotionDataNumGet(chr, 0xA4));
    mstory5_scene1PlayerFaceAnimTbl[1] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xAA));
    mstory5_scene1PlayerFaceAnimTbl[2] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA5));
    mstory5_scene1PlayerFaceAnimTbl[3] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA9));
    Hu3DModelDynamicFree(obj->model[1]);
    CharAnimSet(obj->model[1], 2, GwStory.unk1, mstory5_scene1PlayerFaceAnimTbl[0]);
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    mstory5_scene1PlayerPos = mstory5_scene1PlayerStartPos;
    Hu3DModelPosSet(obj->model[1], mstory5_scene1PlayerPos.x, mstory5_scene1PlayerPos.y, mstory5_scene1PlayerPos.z);
    Hu3DModelPosSet(obj->model[2], mstory5_scene1PlayerPos.x, -5.0f, mstory5_scene1PlayerPos.z);
    Hu3DModelPosSet(obj->model[4], mstory5_scene1PlayerPos.x, mstory5_scene1PlayerPos.y, mstory5_scene1PlayerPos.z);
    omPrcSetDestructor(0, mstory5_Scene1PlayerDestroy);
    mstory5_scene1WorkTbl[0].func = mstory5_Scene1ObjIdle;
    while (TRUE) {
        mstory5_scene1WorkTbl[0].func(obj);
        HuPrcVSleep();
    }
}

void mstory5_Scene1PlayerDestroy(void) {
}

const Vec mstory5_scene1PlayerStartPos = { -120.0f, 0.0f, 480.0f };

const Vec mstory5_scene1TumbleStartPos = { 38.0f, 100.0f, 214.0f };

const Vec mstory5_scene1RivalStartPos = { 150.0f, 0.0f, 384.0f };

const Vec mstory5_scene1DaisyStartPos = { 608.1f, -85.8f, -1390.3f };

const Vec mstory5_scene1KoopaStartPos = { 800.0f, 0.0f, 380.0f };

const Vec mstory5_scene1KoopaJrAStartPos = { -700.0f, 0.0f, 300.0f };

const Vec mstory5_scene1KoopaJrBStartPos = { -900.0f, 0.0f, 300.0f };

const Vec mstory5_scene1StarStartPos = { 0.0f, 200.0f, 150.0f };

const Vec mstory5_scene1StampStartPos = { 0.0f, 200.0f, 100.0f };

const s32 mstory5_scene1PlayerMot5Tbl[8] = { 0x1D003E, 0x1D0048, 0x1D0052, 0x1D005B, 0x1D0065, 0x1D006E, 0x1D003E, 0x1D003E };

const s32 mstory5_scene1PlayerMot6Tbl[8] = { 0x1D0040, 0x1D004B, 0x1D0054, 0x1D005D, 0x1D0067, 0x1D0070, 0x1D0040, 0x1D0040 };

const s32 mstory5_scene1PlayerMot7Tbl[8] = { 0x1D0041, 0x1D004C, 0x1D0055, 0x1D005E, 0x1D0068, 0x1D0071, 0x1D0041, 0x1D0041 };

const s32 mstory5_scene1PlayerMot9Tbl[8] = { 0x1D0043, 0x1D004E, 0x1D0057, 0x1D0060, 0x1D006A, 0x1D0073, 0x1D0043, 0x1D0043 };

const s32 mstory5_scene1PlayerMot10Tbl[8] = { 0x1D003B, 0x1D0044, 0x1D004F, 0x1D0058, 0x1D0061, 0x1D006B, 0x1D003B, 0x1D003B };

const Vec mstory5_scene1PlayerDestRot0 = { 0.0f, 0.0f, 0.0f };

const Vec mstory5_scene1PlayerDestRot1 = { 0.0f, 180.0f, 0.0f };

const Vec mstory5_scene1StarDestPos0 = { -100.0f, 0.0f, 350.0f };
const Vec mstory5_scene1StarDestPos1 = { -100.0f, 0.0f, 150.0f };
const Vec mstory5_scene1StarDestRot0 = { 0.0f, 20.0f, 0.0f };
const Vec mstory5_scene1StarDestRot1 = { 0.0f, 0.0f, 0.0f };
const Vec mstory5_scene1StarDestRot2 = { 0.0f, -26.565f, 0.0f };
const Vec mstory5_scene1UnusedRot0 = { 0.0f, 45.0f, 0.0f };

const char mstory5_scene1ItemHookName[] = "item_hook";

void mstory5_Scene1PlayerStampExec(omObjData *obj) {
    omObjData *obj0;
    omObjData *obj7;
    omObjData *obj1;
    s16 model;
    HmfMotionNode *node;
    s32 fx;
    s32 i;
    f32 scale;
    f32 time;
    Vec pos;

    HuPrcSleep(20);
    // obj0 is unused, but reading it first makes mstory5_scene1WorkTbl itself
    // the shared base address for the following holder accesses.
    obj0 = mstory5_scene1WorkTbl[0].obj;
    obj7 = mstory5_scene1WorkTbl[7].obj;
    obj1 = mstory5_scene1WorkTbl[1].obj;
    (void)obj0;
    model = obj->model[1];
    HuPrcSleep(50);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory5_ObjRotMove(obj, 0.0f, 110.0f, 0.0f, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    HuPrcSleep(10);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_HOOK, HU3D_ATTR_HOOK);
    Hu3DModelHookSet(obj->model[3], model, mstory5_scene1ItemHookName);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    mstory5_MotionEndWait(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[5]].motId, 0, 10, 0);
    mstory5_MotionEndWait(model);
    while (!(mstory5_scene1WorkTbl[8].unk_08 & 1)) {
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(mstory5_scene1WorkTbl[8].obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DMotionNoMotSet(model, Hu3DData[model].motId, mstory5_scene1ItemHookName, 0x1B, 0x45);
    Hu3DMotionNoMotSet(model, Hu3DData[model].motId, mstory5_scene1ItemHookName, 0x1B, 0x46);
    Hu3DMotionNoMotSet(model, Hu3DData[model].motId, mstory5_scene1ItemHookName, 0x1B, 0x47);
    node = Hu3DModelObjPtrGet(model, mstory5_scene1ItemHookName);
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
    Hu3DMotionNoMotReset(model, Hu3DData[model].motId, mstory5_scene1ItemHookName, 0x1B, 0x47);
    Hu3DMotionNoMotReset(model, Hu3DData[model].motId, mstory5_scene1ItemHookName, 0x1B, 0x46);
    Hu3DMotionNoMotReset(model, Hu3DData[model].motId, mstory5_scene1ItemHookName, 0x1B, 0x45);
    mstory5_StampCardStart(4);
    while (mstory5_StampCardDoneCheck() == 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(0) == 0 ? 0x5A4B : 0x5B3F);
    mstory5_WinClose();
    Hu3DMotionModelSet(model, obj->motion[5]);
    Hu3DMotionAttrSet(model, 4, 4);
    Hu3DMotionSpeedSet(model, 2.0f);
    Hu3DMotionTimeSet(model, Hu3DMotion[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    Hu3DMotionModelSet(model, obj->motion[6]);
    Hu3DMotionAttrSet(model, 4, 4);
    Hu3DMotionTimeSet(model, Hu3DMotion[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    Hu3DMotionSpeedSet(model, 1.0f);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_HOOK, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    HuAudSeqFadeOut(20);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    mstory5_ObjRotMoveV(obj, &mstory5_scene1PlayerDestRot0, 10);
    HuAudSeqPlay(0x72);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
    CharAnimSet(model, 2, GwStory.unk1, mstory5_scene1PlayerFaceAnimTbl[2]);
    mstory5_MotionEndWait(model);
    fx = CharFXPlay(0x262, GwStory.unk1);
    HuPrcSleep(30);
    mstory5_ObjRotMoveV(obj7, &mstory5_scene1StarDestRot2, 3);
    mstory5_ObjPosMoveV(obj7, &mstory5_scene1StarDestPos0, 5);
    mstory5_ObjRotMoveV(obj7, &mstory5_scene1StarDestRot0, 3);
    mstory5_scene1WorkTbl[1].func = mstory5_Scene1TumbleHop1;
    HuAudFXPlay(0x219);
    HuAudFXStop(fx);
    Hu3DModelAttrSet(obj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    CharAnimSet(model, 2, GwStory.unk1, mstory5_scene1PlayerFaceAnimTbl[3]);
    mstory5_ObjRotMoveV(obj7, &mstory5_scene1StarDestRot1, 3);
    mstory5_ObjPosMoveEx(obj7, &mstory5_scene1StarDestPos1, 10, 0);
    mstory5_MotionEndWait(model);
    mstory5_ObjRotMoveV(obj, &mstory5_scene1PlayerDestRot1, 10);
    HuAudSeqPlay(0x26);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    CharAnimSet(model, 2, GwStory.unk1, mstory5_scene1PlayerFaceAnimTbl[0]);
    HuAudFXPlay(0x159);
    Hu3DMotionShiftSet(mstory5_scene1WorkTbl[7].obj->model[1], Hu3DData[mstory5_scene1WorkTbl[7].obj->motion[1]].motId, 0, 10, 2);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(0) == 0 ? 0x5A4C : 0x5B40);
    mstory5_WinClose();
    Hu3DMotionShiftSet(mstory5_scene1WorkTbl[7].obj->model[1], Hu3DData[mstory5_scene1WorkTbl[7].obj->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[8]].motId, 0, 10, 0);
    mstory5_MotionEndWait(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory5_scene1WorkTbl[3].func = mstory5_Scene1DaisyEnter;
    mstory5_ObjRotMove(mstory5_scene1WorkTbl[7].obj, 0.0f, 158.46f, 0.0f, 5);
    mstory5_scene1WorkTbl[1].func = mstory5_Scene1TumbleHop2;
    mstory5_scene1WorkTbl[7].func = mstory5_Scene1TumbleDaisyFace;
    mstory5_scene1SubEventWork.func = mstory5_Scene1PlayerDaisyFace;
    mstory5_ObjPosMoveExXYZ(obj1, 238.0f, 100.0f, 214.0f, 10, 0);
    while (!(mstory5_scene1WorkTbl[3].unk_08 & 8)) {
        HuPrcVSleep();
    }
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(0) == 0 ? 0x5A4D : 0x5B41);
    mstory5_WinClose();
    mstory5_scene1WorkTbl[3].unk_08 |= 1;
    while (!(mstory5_scene1WorkTbl[3].unk_08 & 4)) {
        HuPrcVSleep();
    }
    mstory5_scene1EventWork.func = mstory5_Scene1EventExec;
    while (!(mstory5_scene1WorkTbl[1].unk_08 & 1)) {
        HuPrcVSleep();
    }
    mstory5_scene1WorkTbl[4].func = mstory5_Scene1KoopaExec;
    while (!(mstory5_scene1WorkTbl[4].unk_08 & 2)) {
        HuPrcVSleep();
    }
    mstory5_scene1SubEventWork.func = mstory5_Scene1StarExit;
    mstory5_scene1WorkTbl[1].func = mstory5_Scene1TumbleExit;
    mstory5_scene1WorkTbl[3].func = mstory5_Scene1DaisyExit;
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 2);
    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    mstory5_Scene1ObjSeLoopStart(0, 0x1F);
    mstory5_ObjRotMove(obj, 0.0f, 90.0f, 0.0f, 20);
    mstory5_ObjPosMove(obj, pos.x + 1000.0f, pos.y, pos.z, 30);
    mstory5_Scene1ObjSeLoopStop(0);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    mstory5_scene1WorkTbl[5].func = mstory5_Scene1KoopaJrAEnter;
    mstory5_scene1WorkTbl[6].func = mstory5_Scene1KoopaJrBEnter;
    HuPrcSleep(30);
    HuPrcSleep(40);
    HuAudFXPlay(0x2A0);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(0) == 0 ? 0x5A57 : 0x5B4B);
    mstory5_WinClose();
    HuPrcSleep(30);
    mstory5_scene1WorkTbl[0].unk_08 |= 1;
    HuPrcSleep(50);
    mstory5_SceneEnd();
    mstory5_scene1WorkTbl[0].func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1PlayerReactExec(omObjData *obj) {
    s16 model = obj->model[1];

    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[9]].motId, 0, 10, 0);
    mstory5_MotionEndWait(model);
    HuPrcSleep(80);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory5_scene1WorkTbl[0].func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1PlayerTurn1(omObjData *obj) {
    mstory5_ObjRotMoveV(obj, &mstory5_scene1PlayerDestRot2, 10);
    mstory5_scene1WorkTbl[0].func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1PlayerDaisyFace(omObjData *obj) {
    mstory5_Scene1ObjTargetFace(mstory5_scene1WorkTbl[0].obj, mstory5_scene1WorkTbl[3].obj);
}

const Vec mstory5_scene1PlayerDestRot2 = { 0.0f, 150.0f, 0.0f };

const char mstory5_scene1TumbleAnimName[] = "c204n_0_DEF";

void mstory5_Scene1TumbleProc(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(20, 4, 8, -1, NULL);
    mstory5_scene1WorkTbl[1].obj = obj;
    mstory5_scene1WorkTbl[1].unk_08 = 0;
    mstory5_scene1WorkTbl[1].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory5_scene1ShadowMdl);
    omObjMotionRead(obj, 0, 0xA0076);
    omObjMotionRead(obj, 1, 0x1D0029);
    omObjMotionRead(obj, 2, 0x1D002A);
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    mstory5_scene1TumblePos = mstory5_scene1TumbleStartPos;
    Hu3DModelPosSet(obj->model[1], mstory5_scene1TumblePos.x, mstory5_scene1TumblePos.y, mstory5_scene1TumblePos.z);
    Hu3DModelPosSet(obj->model[2], mstory5_scene1TumblePos.x, -5.0f, mstory5_scene1TumblePos.z);
    data = DataRead(0xA007E);
    mstory5_scene1TumbleFaceAnimTbl[0] = (s16)Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, mstory5_scene1TumbleAnimName);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    Hu3DAnimAttrSet(mstory5_scene1TumbleFaceAnim0, 1, 0);
    Hu3DAnimBankSet(mstory5_scene1TumbleFaceAnim0, 0);
    mstory5_scene1TumbleFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory5_scene1TumbleFaceAnim0, 0, mstory5_scene1TumbleAnimName);
    mstory5_scene1TumbleFaceAnimTbl[0] = Hu3DAnimData[mstory5_scene1TumbleFaceAnimTbl[0]].animIdx;
    data = DataRead(0xA0080);
    mstory5_scene1TumbleFaceAnimTbl[1] = (s16)Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    mstory5_scene1TumbleFaceAnimTbl[2] = (s16)Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0085);
    mstory5_scene1TumbleFaceAnimTbl[3] = (s16)Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory5_HmfAnimSet(obj->model[1], mstory5_scene1TumbleFaceSlot, mstory5_scene1TumbleFaceAnim0);
    omPrcSetDestructor(0, mstory5_Scene1TumbleDestroy);
    mstory5_scene1WorkTbl[1].func = mstory5_Scene1ObjIdle;
    while (TRUE) {
        mstory5_scene1WorkTbl[1].func(obj);
        HuPrcVSleep();
    }
}

void mstory5_Scene1TumbleDestroy(void) {
}

const Vec mstory5_scene1TumbleDestRot0 = { -5.0f, 300.0f, 0.0f };

const Vec mstory5_scene1TumbleDestRot1 = { 10.0f, 378.9f, 0.0f };

void mstory5_Scene1TumbleExec(omObjData *obj) {
    HuPrcSleep(40);
    HuPrcSleep(20);
    mstory5_scene1WorkTbl[0].func = mstory5_Scene1PlayerReactExec;
    mstory5_scene1WorkTbl[7].func = mstory5_Scene1StarTurn1;
    mstory5_ObjRotMoveV(obj, &mstory5_scene1TumbleDestRot1, 30);
    mstory5_ObjPosMoveV(obj, &mstory5_scene1TumbleDestPos1, 20);
    HuPrcSleep(30);
    mstory5_ObjRotMoveV(obj, &mstory5_scene1TumbleDestRot4, 10);
    mstory5_ObjPosMoveV(obj, &mstory5_scene1TumbleDestPos0, 15);
    mstory5_scene1WorkTbl[0].func = mstory5_Scene1PlayerTurn1;
    mstory5_ObjRotMoveV(obj, &mstory5_scene1TumbleDestRot2, 10);
    mstory5_HmfAnimSet(obj->model[1], mstory5_scene1TumbleFaceSlot, mstory5_scene1TumbleFaceAnim1);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(0) == 0 ? 0x5A49 : 0x5B3D);
    mstory5_WinClose();
    mstory5_HmfAnimSet(obj->model[1], mstory5_scene1TumbleFaceSlot, mstory5_scene1TumbleFaceAnim0);
    mstory5_ObjRotMove(mstory5_scene1WorkTbl[0].obj, 0.0f, 162.4744f, 0.0f, 10);
    mstory5_ObjRotMoveV(mstory5_scene1WorkTbl[7].obj, &mstory5_scene1StarDestRot3, 10);
    mstory5_ObjRotMoveV(obj, &mstory5_scene1TumbleDestRot3, 20);
    Hu3DMotionShiftSet(mstory5_scene1WorkTbl[7].obj->model[1], Hu3DData[mstory5_scene1WorkTbl[7].obj->motion[1]].motId, 0, 10, 2);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(0) == 0 ? 0x5A4A : 0x5B3E);
    mstory5_WinClose();
    Hu3DMotionShiftSet(mstory5_scene1WorkTbl[7].obj->model[1], Hu3DData[mstory5_scene1WorkTbl[7].obj->motion[0]].motId, 0, 10, 2);
    mstory5_ObjRotMoveV(mstory5_scene1WorkTbl[7].obj, &mstory5_scene1StarDestRot4, 10);
    mstory5_scene1WorkTbl[8].func = mstory5_Scene1StampFlyExec;
    mstory5_ObjRotMoveV(obj, &mstory5_scene1TumbleDestRot0, 20);
    Hu3DMotionShiftSet(mstory5_scene1WorkTbl[0].obj->model[1], Hu3DData[mstory5_scene1WorkTbl[0].obj->motion[12]].motId, 0, 10, 2);
    while (!(mstory5_scene1WorkTbl[8].unk_08 & 2)) {
        HuPrcVSleep();
    }
    mstory5_scene1WorkTbl[0].func = mstory5_Scene1PlayerStampExec;
    HuPrcSleep(40);
    mstory5_ObjRotMoveV(obj, &mstory5_scene1TumbleDestRot6, 50);
    mstory5_ObjRotMoveV(obj, &mstory5_scene1TumbleDestRot5, 40);
    mstory5_scene1WorkTbl[1].func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1TumbleExit(omObjData *obj) {
    Vec pos;
    s16 model = obj->model[1];

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    mstory5_ObjRotMove(obj, 0.0f, 90.0f, 0.0f, 20);
    mstory5_ObjPosMove(obj, pos.x + 1000.0f, pos.y, pos.z, 30);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    mstory5_scene1WorkTbl[1].func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1TumbleHop1(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec orig;
    s32 i;

    orig.x = Hu3DData[model].pos.x;
    orig.y = Hu3DData[model].pos.y;
    orig.z = Hu3DData[model].pos.z;
    pos.y = Hu3DData[model].pos.y;
    for (i = 0; i < 12; i++) {
        pos.x = Hu3DData[model].pos.x;
        pos.z = Hu3DData[model].pos.z;
        Hu3DModelPosSet(model, pos.x, sindf(i * 15.0f) * 80.0f + pos.y, pos.z);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, orig.x, orig.y, orig.z);
    mstory5_HmfAnimSet(obj->model[1], mstory5_scene1TumbleFaceSlot, mstory5_scene1TumbleFaceAnim2);
    mstory5_scene1WorkTbl[1].func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1EventExec(omObjData *obj) {
    omObjData *obj1 = mstory5_scene1WorkTbl[1].obj;
    omObjData *obj3 = mstory5_scene1WorkTbl[3].obj;
    omObjData *obj7 = mstory5_scene1WorkTbl[7].obj;
    omObjData *obj0 = mstory5_scene1WorkTbl[0].obj;

    while (!(mstory5_scene1WorkTbl[3].unk_08 & 2)) {
        HuPrcVSleep();
    }
    mstory5_ObjPosMoveEx(mstory5_scene1WorkTbl[1].obj, &mstory5_scene1TumbleDestPos2, 15, 0);
    mstory5_scene1WorkTbl[3].func = mstory5_Scene1ObjIdle;
    mstory5_ObjRotMoveV(mstory5_scene1WorkTbl[3].obj, &mstory5_scene1DaisyDestRot1, 10);
    mstory5_ObjPosMoveExXYZ(obj7, 0.0f, 200.0f, 150.0f, 15, 0);
    Hu3DMotionShiftSet(mstory5_scene1WorkTbl[0].obj->model[1], Hu3DData[mstory5_scene1WorkTbl[0].obj->motion[0]].motId, 0, 30, 2);
    Hu3DMotionShiftSet(mstory5_scene1WorkTbl[3].obj->model[1], Hu3DData[mstory5_scene1WorkTbl[3].obj->motion[9]].motId, 0, 30, 0);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(mstory5_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory5_scene1WorkTbl[1].obj->motion[2]].motId, 0, 30, 2);
    mstory5_MotionEndWait(mstory5_scene1WorkTbl[3].obj->model[1]);
    Hu3DMotionShiftSet(mstory5_scene1WorkTbl[3].obj->model[1], Hu3DData[mstory5_scene1WorkTbl[3].obj->motion[9]].motId, 0, 30, 0);
    mstory5_MotionEndWait(mstory5_scene1WorkTbl[3].obj->model[1]);
    Hu3DMotionShiftSet(mstory5_scene1WorkTbl[3].obj->model[1], Hu3DData[mstory5_scene1WorkTbl[3].obj->motion[0]].motId, 0, 30, 2);
    Hu3DMotionShiftSet(mstory5_scene1WorkTbl[1].obj->model[1], Hu3DData[mstory5_scene1WorkTbl[1].obj->motion[0]].motId, 0, 30, 2);
    mstory5_scene1WorkTbl[1].func = mstory5_Scene1ObjIdle;
    mstory5_ObjPosMoveV(mstory5_scene1WorkTbl[1].obj, &mstory5_scene1TumbleDestPos3, 8);
    mstory5_ObjRotMoveV(mstory5_scene1WorkTbl[1].obj, &mstory5_scene1TumbleDestRot7, 10);
    mstory5_ObjRotMoveV(mstory5_scene1WorkTbl[3].obj, &mstory5_scene1DaisyDestRot0, 5);
    mstory5_scene1WorkTbl[7].func = mstory5_Scene1ObjIdle;
    mstory5_scene1WorkTbl[0].func = mstory5_Scene1ObjIdle;
    mstory5_ObjRotMoveV(mstory5_scene1WorkTbl[7].obj, &mstory5_scene1StarDestRot5, 5);
    mstory5_ObjRotMoveV(mstory5_scene1WorkTbl[0].obj, &mstory5_scene1PlayerDestRot3, 5);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(0) == 0 ? 0x5A4E : 0x5B42);
    mstory5_WinClose();
    mstory5_ObjPosMoveV(mstory5_scene1WorkTbl[1].obj, &mstory5_scene1TumbleDestPos2, 10);
    mstory5_ObjRotMove(mstory5_scene1WorkTbl[7].obj, 15.0f, 20.0f, 0.0f, 5);
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[1]].motId, 0, 10, 2);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(0) == 0 ? 0x5A4F : 0x5B43);
    mstory5_WinClose();
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[0]].motId, 0, 10, 2);
    HuAudFXPlay(0x27C);
    mstory5_ObjRotMove(obj3, 0.0f, -110.0f, 0.0f, 5);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[4]].motId, 0, 10, 0);
    mstory5_MotionEndWait(obj3->model[1]);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[5]].motId, 0, 10, 2);
    mstory5_HmfAnimSet(obj1->model[1], mstory5_scene1TumbleFaceSlot, mstory5_scene1TumbleFaceAnim3);
    mstory5_Scene1StarEyesASwap();
    HuAudFXPlay(0x21C);
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[4]].motId, 0, 10, 2);
    HuPrcSleep(20);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(0) == 0 ? 0x5A50 : 0x5B44);
    mstory5_WinClose();
    mstory5_ObjRotMove(obj7, 0.0f, 0.0f, 0.0f, 5);
    mstory5_scene1WorkTbl[8].func = mstory5_Scene1StampBShowExec;
    HuPrcSleep(50);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[12]].motId, 0, 10, 0);
    mstory5_MotionEndWait(obj3->model[1]);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[0]].motId, 0, 10, 2);
    mstory5_scene1SubEventWork.func = mstory5_Scene1ObjIdle;
    mstory5_ObjRotMove(obj0, 0.0f, 150.0f, 0.0f, 10);
    mstory5_HmfAnimSet(obj1->model[1], mstory5_scene1TumbleFaceSlot, mstory5_scene1TumbleFaceAnim0);
    Hu3DMotionShiftSet(obj0->model[1], Hu3DData[obj0->motion[10]].motId, 0, 10, 2);
    HuPrcSleep(100);
    mstory5_ObjPosMoveV(mstory5_scene1WorkTbl[1].obj, &mstory5_scene1TumbleDestPos3, 8);
    mstory5_ObjRotMoveV(mstory5_scene1WorkTbl[1].obj, &mstory5_scene1TumbleDestRot7, 10);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(0) == 0 ? 0x5A51 : 0x5B45);
    mstory5_WinClose();
    Hu3DMotionShiftSet(obj0->model[1], Hu3DData[obj0->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(mstory5_scene1WorkTbl[3].obj->model[1], Hu3DData[mstory5_scene1WorkTbl[3].obj->motion[1]].motId, 0, 30, 2);
    mstory5_scene1WorkTbl[3].func = mstory5_Scene1DaisyStep;
    mstory5_scene1WorkTbl[7].func = mstory5_Scene1StarTurn2;
    HuPrcSleep(70);
    mstory5_HmfAnimSet(obj1->model[1], mstory5_scene1TumbleFaceSlot, mstory5_scene1TumbleFaceAnim1);
    Hu3DMotionShiftSet(obj1->model[1], Hu3DData[obj1->motion[1]].motId, 0, 10, 2);
    mstory5_scene1WorkTbl[1].func = mstory5_Scene1TumblePlayerFace;
    mstory5_ObjPosMoveExXYZ(obj1, 238.0f, 100.0f, 214.0f, 60, 0);
    mstory5_scene1WorkTbl[1].func = mstory5_Scene1ObjIdle;
    mstory5_scene1WorkTbl[8].unk_08 |= 0x10;
    while (!(mstory5_scene1WorkTbl[8].unk_08 & 8)) {
        HuPrcVSleep();
    }
    mstory5_ObjRotMove(obj1, 0.0f, -140.0f, 0.0f, 10);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(0) == 0 ? 0x5A52 : 0x5B46);
    mstory5_WinClose();
    mstory5_ObjRotMoveV(mstory5_scene1WorkTbl[1].obj, &mstory5_scene1TumbleDestRot7, 10);
    HuPrcSleep(20);
    mstory5_Scene1StarEyesASet();
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[0]].motId, 0, 10, 2);
    mstory5_scene1StarFloatStopF = 1;
    mstory5_ObjPosMoveV(mstory5_scene1WorkTbl[7].obj, &mstory5_scene1StarDestPos2, 3);
    HuAudFXPlay(0x219);
    CharFXPlay(0x2AB, GwStory.unk1);
    _HuAudPlayerFXPlay(0x2B3, 1);
    mstory5_scene1SubEventWork.func = mstory5_Scene1PlayerKnockBack;
    mstory5_scene1WorkTbl[3].func = mstory5_Scene1DaisyKnockBack;
    mstory5_scene1StarFloatStopF = 0;
    mstory5_ObjPosMoveEx(mstory5_scene1WorkTbl[7].obj, &mstory5_scene1StarDestPos3, 5, 0);
    mstory5_scene1WorkTbl[1].func = mstory5_Scene1TumbleHop1;
    HuPrcSleep(12);
    mstory5_ObjRotMove(mstory5_scene1WorkTbl[1].obj, 0.0f, -135.0f, 0.0f, 10);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(0) == 0 ? 0x5A53 : 0x5B47);
    mstory5_ObjRotMoveV(mstory5_scene1WorkTbl[1].obj, &mstory5_scene1TumbleDestRot7, 10);
    mstory5_Scene1StarEyesASwap();
    HuAudFXPlay(0x21C);
    mstory5_ObjRotMove(obj7, 20.0f, 10.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[4]].motId, 0, 10, 2);
    mstory5_WinMesExec(mstory5_PlayerChrCheck(0) == 0 ? 0x5A54 : 0x5B48);
    mstory5_WinClose();
    CharFXPlay(0x274, GwStory.unk1);
    _HuAudPlayerFXPlay(0x27C, 1);
    mstory5_scene1SubEventWork.func = mstory5_Scene1PlayerPose;
    mstory5_scene1WorkTbl[3].func = mstory5_Scene1DaisyPose;
    HuPrcSleep(10);
    HuPrcSleep(40);
    mstory5_scene1WorkTbl[1].unk_08 |= 1;
    mstory5_scene1EventWork.func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1TumblePlayerFace(omObjData *obj) {
    mstory5_Scene1ObjTargetFace(obj, mstory5_scene1WorkTbl[0].obj);
}

void mstory5_Scene1RivalProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    mstory5_scene1WorkTbl[2].obj = obj;
    mstory5_scene1WorkTbl[2].unk_08 = 0;
    mstory5_scene1WorkTbl[2].unk_0C = 0;
    if (mstory5_PlayerChrCheck(0) == 0) {
        obj->model[1] = Hu3DModelRead(0x200A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(mstory5_scene1ShadowMdl);
        omObjMotionRead(obj, 0, 0x20000);
        omObjMotionRead(obj, 1, 0x1D003C);
        omObjMotionRead(obj, 2, 0x1D003D);
    } else {
        obj->model[1] = Hu3DModelRead(0x300A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(mstory5_scene1ShadowMdl);
        omObjMotionRead(obj, 0, 0x30000);
        omObjMotionRead(obj, 1, 0x1D0046);
        omObjMotionRead(obj, 2, 0x1D0047);
    }
    Hu3DMotionModelSet(obj->model[1], obj->motion[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 340.0f, 0.0f);
    mstory5_scene1RivalPos = mstory5_scene1RivalStartPos;
    Hu3DModelPosSet(obj->model[1], mstory5_scene1RivalPos.x, mstory5_scene1RivalPos.y, mstory5_scene1RivalPos.z);
    Hu3DModelPosSet(obj->model[2], mstory5_scene1RivalPos.x, -5.0f, mstory5_scene1RivalPos.z);
    omPrcSetDestructor(0, mstory5_Scene1RivalDestroy);
    mstory5_scene1WorkTbl[2].func = mstory5_Scene1RivalExec;
    while (1) {
        mstory5_scene1WorkTbl[2].func(obj);
        HuPrcVSleep();
    }
}

void mstory5_Scene1RivalDestroy(void) {
}

const Vec mstory5_scene1TumbleDestRot2 = { 20.0f, 320.0f, 0.0f };
const Vec mstory5_scene1UnusedRot1 = { 0.0f, 450.0f, 0.0f }; /* Unreferenced. */

const Vec mstory5_scene1TumbleDestRot3 = { 0.0f, 225.0f, 0.0f };

const Vec mstory5_scene1TumbleDestRot4 = { 0.0f, 134.2f, 0.0f };

const Vec mstory5_scene1TumbleDestRot5 = { 0.0f, 320.0f, 0.0f };

const Vec mstory5_scene1TumbleDestRot6 = { -30.0f, 260.0f, 0.0f };

const Vec mstory5_scene1TumbleDestPos0 = { 238.0f, 100.0f, 214.0f };

const Vec mstory5_scene1TumbleDestPos1 = { 88.0f, 100.0f, 360.0f };

const Vec mstory5_scene1StarDestRot3 = { 30.0f, -20.0f, 0.0f };

const Vec mstory5_scene1StarDestRot4 = { 0.0f, 0.0f, 0.0f };
const Vec mstory5_scene1UnusedRot2 = { 0.0f, 158.73f, 0.0f }; /* Unreferenced. */
const Vec mstory5_scene1UnusedRot3 = { 0.0f, 167.01f, 0.0f }; /* Unreferenced. */
const Vec mstory5_scene1UnusedRot4 = { 0.0f, 158.46f, 0.0f }; /* Unreferenced. */

const Vec mstory5_scene1DaisyDestRot0 = { 0.0f, -70.43f, 0.0f };

const Vec mstory5_scene1TumbleDestRot7 = { 0.0f, -77.13f, 0.0f };
const Vec mstory5_scene1UnusedRot5 = { 0.0f, -135.0f, 0.0f };  /* Unreferenced. */
const Vec mstory5_scene1UnusedRot6 = { 0.0f, 162.4f, 0.0f };   /* Unreferenced. */
const Vec mstory5_scene1UnusedRot7 = { 0.0f, -147.34f, 0.0f }; /* Unreferenced. */
const Vec mstory5_scene1UnusedRot8 = { 0.0f, 306.61f, 0.0f };  /* Unreferenced. */

const Vec mstory5_scene1DaisyDestRot1 = { 0.0f, 90.0f, 0.0f };

const Vec mstory5_scene1StarDestRot5 = { 0.0f, 50.19f, 0.0f };

const Vec mstory5_scene1PlayerDestRot3 = { 0.0f, 100.78f, 0.0f };
const Vec mstory5_scene1UnusedPos0 = { 150.0f, 0.0f, 384.0f }; /* Unreferenced. */

const Vec mstory5_scene1StarDestPos2 = { 0.0f, 200.0f, 300.0f };

const Vec mstory5_scene1StarDestPos3 = { 0.0f, 200.0f, 150.0f };

const Vec mstory5_scene1TumbleDestPos2 = { 300.0f, 25.0f, 400.0f };

const Vec mstory5_scene1TumbleDestPos3 = { 300.0f, 125.0f, 400.0f };
const Vec mstory5_scene1UnusedPos1 = { 238.0f, 100.0f, 214.0f }; /* Unreferenced. */

const Vec mstory5_scene1RivalDestPos0 = { 200.0f, 0.0f, 1200.0f };

void mstory5_Scene1RivalExec(omObjData *obj) {
    HuPrcSleep(10);
    if (mstory5_PlayerChrCheck(0) == 0) {
        CharFXPlay(0x26B, 0);
    } else {
        CharFXPlay(0x26B, 1);
    }
    HuPrcSleep(20);
    mstory5_scene1WorkTbl[1].func = mstory5_Scene1TumbleExec;
    HuPrcSleep(70);
    if (mstory5_PlayerChrCheck(0) == 0) {
        CharFXPlay(0x286, 0);
    } else {
        CharFXPlay(0x286, 1);
    }
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    mstory5_Scene1ObjSeLoopStart(2, 40);
    mstory5_ObjPosMoveV(obj, &mstory5_scene1RivalDestPos0, 40);
    mstory5_Scene1ObjSeLoopStop(2);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    mstory5_scene1WorkTbl[2].func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1DaisyProc(void) {
    omObjData *obj;

    obj = omAddObj(20, 4, 16, -1, NULL);
    mstory5_scene1WorkTbl[3].obj = obj;
    mstory5_scene1WorkTbl[3].unk_08 = 0;
    mstory5_scene1WorkTbl[3].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0x90000, 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory5_scene1ShadowMdl);
    obj->model[3] = Hu3DModelLink(mstory5_scene1ShockMdl);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    omObjMotionRead(obj, 0, 0x90004);
    omObjMotionRead(obj, 1, CharMotionDataNumGet(7, 1));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(7, 2));
    omObjMotionRead(obj, 3, 0x9000C);
    omObjMotionRead(obj, 4, 0x1D0079);
    omObjMotionRead(obj, 5, 0x1D007B);
    omObjMotionRead(obj, 6, 0x1D007C);
    omObjMotionRead(obj, 7, CharMotionDataNumGet(7, 0x7A));
    omObjMotionRead(obj, 8, 0x70003);
    omObjMotionRead(obj, 9, 0x1D0078);
    omObjMotionRead(obj, 10, CharMotionDataNumGet(7, 0x13));
    omObjMotionRead(obj, 11, CharMotionDataNumGet(7, 0x72));
    omObjMotionRead(obj, 12, CharMotionDataNumGet(7, 0x32));
    omObjMotionRead(obj, 13, CharMotionDataNumGet(7, 0x33));
    omObjMotionRead(obj, 14, CharMotionDataNumGet(7, 0x21));
    mstory5_scene1DaisyFaceAnimTbl[0] = CharAnimCreate(obj->model[1], 2, 7, CharMotionDataNumGet(7, 0xA4));
    mstory5_scene1DaisyFaceAnimTbl[1] = Hu3DAnimDataRead(CharMotionDataNumGet(7, 0xAA));
    mstory5_scene1DaisyFaceAnimTbl[2] = Hu3DAnimDataRead(CharMotionDataNumGet(7, 0xA5));
    mstory5_scene1DaisyFaceAnimTbl[3] = Hu3DAnimDataRead(CharMotionDataNumGet(7, 0xA6));
    Hu3DModelDynamicFree(obj->model[1]);
    CharAnimSet(obj->model[1], 2, 7, mstory5_scene1DaisyFaceAnimTbl[0]);
    Hu3DMotionModelSet(obj->model[1], obj->motion[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    mstory5_scene1DaisyPos = mstory5_scene1DaisyStartPos;
    Hu3DModelPosSet(obj->model[1], mstory5_scene1DaisyPos.x, mstory5_scene1DaisyPos.y, mstory5_scene1DaisyPos.z);
    Hu3DModelPosSet(obj->model[2], mstory5_scene1DaisyPos.x, -5.0f, mstory5_scene1DaisyPos.z);
    omPrcSetDestructor(0, mstory5_Scene1DaisyDestroy);
    mstory5_scene1WorkTbl[3].func = mstory5_Scene1ObjIdle;
    while (TRUE) {
        mstory5_scene1WorkTbl[3].func(obj);
        HuPrcVSleep();
    }
}

void mstory5_Scene1DaisyDestroy(void) {
}

void mstory5_Scene1DaisyEnter(omObjData *obj) {
    s16 model = obj->model[1];

    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    mstory5_BackMotionStart();
    HuPrcSleep(15);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    while (!(mstory5_scene1WorkTbl[1].unk_08 & 2)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    HuAudFXVolSet(HuAudFXPlay(0x297), 90);
    mstory5_MotionEndWait(model);
    mstory5_scene1WorkTbl[3].unk_08 |= 8;
    while (!(mstory5_scene1WorkTbl[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    mstory5_Scene1ObjSeLoopStart(3, 40);
    HuAudFXVolSet((s16)mstory5_scene1WorkTbl[3].unk_14, 64);
    mstory5_scene1SubEventWork.func = mstory5_Scene1DaisySeFadeIn;
    mstory5_ObjPosMoveAccelXYZ(obj, 150.0f, 0.0f, 384.0f, 180, 1);
    mstory5_Scene1ObjSeLoopStop(3);
    mstory5_HmfAnimSet(mstory5_scene1WorkTbl[1].obj->model[1], mstory5_scene1TumbleFaceSlot, mstory5_scene1TumbleFaceAnim0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[10]].motId, 0, 30, 2);
    mstory5_scene1WorkTbl[3].unk_08 |= 4;
    HuPrcSleep(60);
    mstory5_HmfAnimSet(mstory5_scene1WorkTbl[1].obj->model[1], mstory5_scene1TumbleFaceSlot, mstory5_scene1TumbleFaceAnim0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 30, 2);
    mstory5_scene1WorkTbl[3].unk_08 |= 2;
    mstory5_scene1WorkTbl[3].func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1DaisyExit(omObjData *obj) {
    Vec pos;
    s16 model = obj->model[1];

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory5_Scene1ObjSeLoopStart(3, 0x1F);
    mstory5_ObjRotMove(obj, 0.0f, 90.0f, 0.0f, 20);
    mstory5_ObjPosMove(obj, pos.x + 1000.0f, pos.y, pos.z, 30);
    mstory5_Scene1ObjSeLoopStop(3);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    mstory5_scene1WorkTbl[3].func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1DaisyMotionEndWait(omObjData *obj) {
    s16 model = obj->model[1];

    mstory5_MotionEndWait(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory5_scene1WorkTbl[3].func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1KoopaProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 16, 8, -1, NULL);
    mstory5_scene1WorkTbl[4].obj = obj;
    mstory5_scene1WorkTbl[4].unk_08 = 0;
    mstory5_scene1WorkTbl[4].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0xA002F, 0x2B9);
    obj->model[2] = Hu3DModelLink(mstory5_scene1ShadowMdl);
    Hu3DModelScaleSet(obj->model[2], 3.0f, 1.0f, 3.0f);
    obj->model[3] = Hu3DModelRead(0x1D0027, 0x2B9);
    omObjMotionRead(obj, 0, 0xA0030);
    omObjMotionRead(obj, 1, 0xA0035);
    omObjMotionRead(obj, 2, 0xA0032);
    omObjMotionRead(obj, 3, 0x1D0031);
    Hu3DMotionModelSet(obj->model[1], obj->motion[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DMotionAttrSet(obj->model[3], 2, 2);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    mstory5_scene1KoopaPos = mstory5_scene1KoopaStartPos;
    Hu3DModelPosSet(obj->model[1], mstory5_scene1KoopaPos.x, mstory5_scene1KoopaPos.y, mstory5_scene1KoopaPos.z);
    Hu3DModelPosSet(obj->model[2], mstory5_scene1KoopaPos.x, -5.0f, mstory5_scene1KoopaPos.z);
    omPrcSetDestructor(0, mstory5_Scene1KoopaDestroy);
    mstory5_scene1WorkTbl[4].func = mstory5_Scene1ObjIdle;
    while (1) {
        mstory5_scene1WorkTbl[4].func(obj);
        HuPrcVSleep();
    }
}

void mstory5_Scene1KoopaDestroy(void) {
}

void mstory5_Scene1KoopaExec(omObjData *obj) {
    s16 model = obj->model[1];
    omObjData *obj3 = mstory5_scene1WorkTbl[3].obj;
    omObjData *obj7 = mstory5_scene1WorkTbl[7].obj;
    omObjData *obj0 = mstory5_scene1WorkTbl[0].obj;
    omObjData *obj1 = mstory5_scene1WorkTbl[1].obj;
    Vec rot;
    Vec pos;
    Vec vel;
    f32 scale;
    f32 shadowScale;
    f32 t;

    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    mstory5_Scene1StarEyesASet();
    HuAudSeqPlay(0x21);
    HuAudFXPlay(0x29D);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(0) == 0 ? 0x5A55 : 0x5B49);
    mstory5_WinClose();
    mstory5_scene1WorkTbl[7].func = mstory5_Scene1GroupStepBack;
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(40);
    mstory5_ObjRotMove(obj3, 0.0f, -90.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[1]].motId, 0, 10, 2);
    mstory5_Scene1ObjSeLoopStart(3, 31);
    mstory5_ObjPosMove(obj3, Hu3DData[obj3->model[1]].pos.x - 50.0f, Hu3DData[obj3->model[1]].pos.y, Hu3DData[obj3->model[1]].pos.z, 10);
    mstory5_Scene1ObjSeLoopStop(3);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[0]].motId, 0, 10, 2);
    while (!(mstory5_scene1WorkTbl[7].unk_08 & 1)) {
        HuPrcVSleep();
    }
    mstory5_ObjPosMove(obj, 300.0f, 0.0f, 380.0f, 30);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
    mstory5_MotionEndWait(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory5_HmfAnimSet(obj->model[1], mstory5_scene1TumbleFaceSlot, mstory5_scene1TumbleFaceAnim2);
    mstory5_ObjRotMove(obj3, 0.0f, 90.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[7]].motId, 0, 10, 0);
    HuAudFXPlay(0x2B3);
    mstory5_MotionEndWait(obj3->model[1]);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[8]].motId, 0, 10, 0);
    HuPrcSleep(3);
    Hu3DMotionAttrSet(obj3->model[1], 1, 1);
    HuPrcSleep(10);
    Hu3DMotionAttrSet(obj3->model[1], 1, 0);
    HuPrcSleep(6);
    HuAudFXPlay(0x21D);
    mstory5_scene1EventWork.func = mstory5_Scene1EventMesExec;
    mstory5_scene1WorkTbl[3].func = mstory5_Scene1DaisyMotionEndWait;
    Hu3DMotionTimeSet(obj0->model[4], 0.0f);
    Hu3DModelPosSet(obj0->model[4], 180.0f, 0.0f, 480.0f);
    Hu3DModelAttrSet(obj0->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    mstory5_scene1WorkTbl[1].func = mstory5_Scene1TumbleHop1;
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[5]].motId, 0, 10, 2);
    mstory5_scene1WorkTbl[7].func = mstory5_Scene1GroupTurn;
    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    rot.x = Hu3DData[model].rot.x;
    rot.y = Hu3DData[model].rot.y;
    rot.z = Hu3DData[model].rot.z;
    scale = 1.0f;
    shadowScale = 3.0f;
    vel.x = -111.666664f;
    vel.y = 66.666664f;
    vel.z = -100.0f;
    t = 0.0f;
    while (TRUE) {
        pos.x += vel.x;
        pos.y += vel.y;
        pos.z += vel.z;
        vel.x *= 0.85f;
        vel.y *= 0.85f;
        vel.z *= 0.85f;
        Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        Hu3DModelPosSet(obj->model[2], pos.x, 0.0f, pos.z);
        rot.z += 2.25f;
        Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
        Hu3DModelScaleSet(model, scale, scale, scale);
        scale = vel.z / -100.0f;
        Hu3DModelScaleSet(obj->model[2], shadowScale, 1.0f, shadowScale);
        shadowScale -= 0.5f;
        if (shadowScale < 0.0f) {
            shadowScale = 0.0f;
        }
        if (t >= 20.0f) {
            break;
        }
        t += 1.0f;
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(obj->model[3], Hu3DData[model].pos.x, Hu3DData[model].pos.y, Hu3DData[model].pos.z);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    HuAudFXPlay(0x21E);
    while (!(mstory5_scene1WorkTbl[4].unk_08 & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(35);
    mstory5_scene1WorkTbl[7].unk_08 |= 2;
    HuPrcSleep(50);
    mstory5_ObjRotMove(obj3, 0.0f, 0.0f, 0.0f, 10);
    CharAnimSet(obj3->model[1], 2, 7, mstory5_scene1DaisyFaceAnimTbl[2]);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[4]].motId, 0, 10, 0);
    mstory5_MotionEndWait(obj3->model[1]);
    HuAudFXPlay(0x27C);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[5]].motId, 0, 10, 2);
    HuPrcSleep(20);
    mstory5_ObjRotMove(obj3, 0.0f, -90.0f, 0.0f, 20);
    HuPrcSleep(10);
    mstory5_ObjRotMove(obj1, 0.0f, -30.0f, 0.0f, 10);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(0) == 0 ? 0x5A58 : 0x5B4C);
    mstory5_WinClose();
    mstory5_ObjRotMove(obj1, 0.0f, 0.0f, 0.0f, 10);
    HuPrcSleep(60);
    mstory5_ObjRotMove(obj7, 0.0f, 20.0f, 0.0f, 10);
    Hu3DMotionShiftSet(mstory5_scene1WorkTbl[7].obj->model[1], Hu3DData[mstory5_scene1WorkTbl[7].obj->motion[2]].motId, 0, 10, 2);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(0) == 0 ? 0x5A59 : 0x5B4D);
    mstory5_WinClose();
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[5]].motId, 0, 10, 2);
    CharAnimSet(obj3->model[1], 2, 7, mstory5_scene1DaisyFaceAnimTbl[0]);
    mstory5_ObjRotMove(obj3, 0.0f, 0.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[13]].motId, 0, 10, 0);
    mstory5_MotionEndWait(obj3->model[1]);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[0]].motId, 0, 10, 2);
    mstory5_ObjRotMove(obj3, 0.0f, 90.0f, 0.0f, 10);
    mstory5_scene1WorkTbl[4].unk_08 |= 2;
    mstory5_scene1WorkTbl[4].func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1KoopaJrAProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    mstory5_scene1WorkTbl[5].obj = obj;
    mstory5_scene1WorkTbl[5].unk_08 = 0;
    mstory5_scene1WorkTbl[5].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(mstory5_scene1ShadowMdl);
    omObjMotionRead(obj, 0, 0xA00EF);
    omObjMotionRead(obj, 1, 0xA00F1);
    omObjMotionRead(obj, 2, 0xA00F0);
    Hu3DMotionModelSet(obj->model[1], obj->motion[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    mstory5_scene1KoopaJrAPos = mstory5_scene1KoopaJrAStartPos;
    Hu3DModelPosSet(obj->model[1], mstory5_scene1KoopaJrAPos.x, mstory5_scene1KoopaJrAPos.y, mstory5_scene1KoopaJrAPos.z);
    Hu3DModelPosSet(obj->model[2], mstory5_scene1KoopaJrAPos.x, -5.0f, mstory5_scene1KoopaJrAPos.z);
    omPrcSetDestructor(0, mstory5_Scene1KoopaJrADestroy);
    mstory5_scene1WorkTbl[5].func = mstory5_Scene1ObjIdle;
    while (1) {
        mstory5_scene1WorkTbl[5].func(obj);
        HuPrcVSleep();
    }
}

void mstory5_Scene1KoopaJrADestroy(void) {
}

void mstory5_Scene1KoopaJrAEnter(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory5_ObjPosMove(obj, 100.0f, pos.y, pos.z, 30);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory5_ObjRotMove(obj, 0.0f, 210.0f, 0.0f, 10);
    while (!(mstory5_scene1WorkTbl[0].unk_08 & 1)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 2);
        mstory5_MotionEndWait(model);
    }
}

void mstory5_Scene1KoopaJrBProc(void) {
    omObjData *obj;
    omObjData *src;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    mstory5_scene1WorkTbl[6].obj = obj;
    mstory5_scene1WorkTbl[6].unk_08 = 0;
    mstory5_scene1WorkTbl[6].unk_0C = 0;
    src = mstory5_scene1WorkTbl[5].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    obj->model[2] = Hu3DModelLink(mstory5_scene1ShadowMdl);
    Hu3DMotionModelSet(obj->model[1], src->motion[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    mstory5_scene1KoopaJrBPos = mstory5_scene1KoopaJrBStartPos;
    Hu3DModelPosSet(obj->model[1], mstory5_scene1KoopaJrBPos.x, mstory5_scene1KoopaJrBPos.y, mstory5_scene1KoopaJrBPos.z);
    Hu3DModelPosSet(obj->model[2], mstory5_scene1KoopaJrBPos.x, -5.0f, mstory5_scene1KoopaJrBPos.z);
    omPrcSetDestructor(0, mstory5_Scene1KoopaJrBDestroy);
    mstory5_scene1WorkTbl[6].func = mstory5_Scene1ObjIdle;
    while (1) {
        mstory5_scene1WorkTbl[6].func(obj);
        HuPrcVSleep();
    }
}

void mstory5_Scene1KoopaJrBEnter(omObjData *obj) {
    s16 model = obj->model[1];
    omObjData *src = mstory5_scene1WorkTbl[5].obj;
    Vec pos;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[1]].motId, 0, 10, 2);
    mstory5_ObjPosMove(obj, -100.0f, pos.y, pos.z, 30);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[0]].motId, 0, 10, 2);
    mstory5_ObjRotMove(obj, 0.0f, 200.0f, 0.0f, 10);
    while (!(mstory5_scene1WorkTbl[0].unk_08 & 1)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        Hu3DMotionShiftSet(model, Hu3DData[src->motion[2]].motId, 0, 10, 2);
        mstory5_MotionEndWait(model);
    }
}

void mstory5_Scene1KoopaJrBDestroy(void) {
}

const char mstory5_scene1StarEyesAObjName[] = "c208nk0-r_eye";
const char mstory5_scene1StarREyeName[] = "r_eye";
const char mstory5_scene1StarLEyeName[] = "l_eye";
const char mstory5_scene1StarEyesBObjName[] = "c208nk1-r_eye";

void mstory5_Scene1StarProc(void) {
    omObjData *obj;

    obj = omAddObj(20, 10, 8, -1, NULL);
    mstory5_scene1WorkTbl[7].obj = obj;
    mstory5_scene1WorkTbl[7].unk_08 = 0;
    mstory5_scene1WorkTbl[7].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    AuraCreate(obj->model[1]);
    omObjMotionRead(obj, 0, 0xA0123);
    omObjMotionRead(obj, 1, 0xA0125);
    omObjMotionRead(obj, 2, 0xA012E);
    omObjMotionRead(obj, 3, 0xA0127);
    omObjMotionRead(obj, 4, 0xA0126);
    omObjMotionRead(obj, 5, 0xA012A);
    obj->model[2] = Hu3DModelLink(mstory5_scene1ShadowMdl);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    obj->model[3] = Hu3DModelRead(0x1D002E, 0x6B9);
    obj->model[4] = Hu3DModelRead(0x1D002E, 0x6B9);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->model[5] = Hu3DModelRead(0xA0122, 0x2A9);
    Hu3DModelAttrSet(obj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelScaleSet(obj->model[5], 2.0f, 2.0f, 2.0f);
    AuraCreate(obj->model[5]);
    Hu3DModelObjCopy(obj->model[3], mstory5_scene1StarEyesAObjName, obj->model[5], mstory5_scene1StarREyeName);
    Hu3DModelObjCopy(obj->model[4], mstory5_scene1StarEyesAObjName, obj->model[5], mstory5_scene1StarLEyeName);
    obj->model[6] = Hu3DModelRead(0x1D002F, 0x6B9);
    obj->model[7] = Hu3DModelRead(0x1D002F, 0x6B9);
    Hu3DModelAttrSet(obj->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[7], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->model[8] = Hu3DModelRead(0xA0122, 0x2A9);
    Hu3DModelAttrSet(obj->model[8], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelScaleSet(obj->model[8], 2.0f, 2.0f, 2.0f);
    AuraCreate(obj->model[8]);
    Hu3DModelObjCopy(obj->model[6], mstory5_scene1StarEyesBObjName, obj->model[8], mstory5_scene1StarREyeName);
    Hu3DModelObjCopy(obj->model[7], mstory5_scene1StarEyesBObjName, obj->model[8], mstory5_scene1StarLEyeName);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    mstory5_scene1StarPos = mstory5_scene1StarStartPos;
    Hu3DModelPosSet(obj->model[1], mstory5_scene1StarPos.x, mstory5_scene1StarPos.y, mstory5_scene1StarPos.z);
    Hu3DModelPosSet(obj->model[2], mstory5_scene1StarPos.x, -5.0f, mstory5_scene1StarPos.z);
    omPrcSetDestructor(0, mstory5_Scene1StarDestroy);
    mstory5_scene1WorkTbl[7].func = mstory5_Scene1ObjIdle;
    mstory5_scene1StarFloatF = 1;
    while (TRUE) {
        mstory5_scene1WorkTbl[7].func(obj);
        HuPrcVSleep();
    }
}

void mstory5_Scene1StarEyesASwap(void) {
    omObjData *obj = mstory5_scene1WorkTbl[7].obj;
    s16 models[2];

    models[0] = obj->model[1];
    models[1] = obj->model[5];
    Hu3DModelAttrSet(models[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(models[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DData[models[1]].pos.x = Hu3DData[models[0]].pos.x;
    Hu3DData[models[1]].pos.y = Hu3DData[models[0]].pos.y;
    Hu3DData[models[1]].pos.z = Hu3DData[models[0]].pos.z;
    Hu3DData[models[1]].rot.x = Hu3DData[models[0]].rot.x;
    Hu3DData[models[1]].rot.y = Hu3DData[models[0]].rot.y;
    Hu3DData[models[1]].rot.z = Hu3DData[models[0]].rot.z;
    Hu3DData[models[1]].scale.x = Hu3DData[models[0]].scale.x;
    Hu3DData[models[1]].scale.y = Hu3DData[models[0]].scale.y;
    Hu3DData[models[1]].scale.z = Hu3DData[models[0]].scale.z;
    obj->model[1] = models[1];
    obj->model[5] = models[0];
}

void mstory5_Scene1StarEyesASet(void) {
    mstory5_Scene1StarEyesASwap();
}

void mstory5_Scene1StarEyesBSwap(void) {
    omObjData *obj = mstory5_scene1WorkTbl[7].obj;
    s16 models[2];

    models[0] = obj->model[1];
    models[1] = obj->model[8];
    Hu3DModelAttrSet(models[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(models[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DData[models[1]].pos.x = Hu3DData[models[0]].pos.x;
    Hu3DData[models[1]].pos.y = Hu3DData[models[0]].pos.y;
    Hu3DData[models[1]].pos.z = Hu3DData[models[0]].pos.z;
    Hu3DData[models[1]].rot.x = Hu3DData[models[0]].rot.x;
    Hu3DData[models[1]].rot.y = Hu3DData[models[0]].rot.y;
    Hu3DData[models[1]].rot.z = Hu3DData[models[0]].rot.z;
    Hu3DData[models[1]].scale.x = Hu3DData[models[0]].scale.x;
    Hu3DData[models[1]].scale.y = Hu3DData[models[0]].scale.y;
    Hu3DData[models[1]].scale.z = Hu3DData[models[0]].scale.z;
    obj->model[1] = models[1];
    obj->model[8] = models[0];
}

void mstory5_Scene1StarEyesBSet(void) {
    mstory5_Scene1StarEyesBSwap();
}

void mstory5_Scene1StarDestroy(void) {
}

void mstory5_Scene1StarExit(omObjData *arg0) {
    omObjData *obj = mstory5_scene1WorkTbl[7].obj;
    Vec pos;
    s16 model = obj->model[1];

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    mstory5_ObjRotMove(obj, 0.0f, 90.0f, 0.0f, 20);
    mstory5_ObjPosMove(obj, pos.x + 1000.0f, pos.y, pos.z, 30);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    mstory5_scene1SubEventWork.func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1StarTurn1(omObjData *obj) {
    mstory5_ObjRotMoveV(obj, &mstory5_scene1StarDestRot6, 20);
    mstory5_scene1WorkTbl[7].func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1GroupStepBack(omObjData *obj) {
    s32 frames = 20;
    omObjData *objs[4];
    Vec dist;
    f32 speed[3];
    s32 i;
    s32 j;

    dist.x = 150.0f;
    dist.y = 350.0f;
    dist.z = 400.0f;
    speed[0] = dist.x / frames;
    speed[1] = dist.y / frames;
    speed[2] = dist.z / frames;

    objs[0] = mstory5_scene1WorkTbl[0].obj;
    objs[1] = mstory5_scene1WorkTbl[1].obj;
    objs[2] = mstory5_scene1WorkTbl[7].obj;
    objs[3] = mstory5_scene1WorkTbl[3].obj;
    mstory5_ObjRotMove(objs[0], 0.0f, 90.0f, 0.0f, 10);
    mstory5_ObjRotMove(objs[1], 0.0f, 90.0f, 0.0f, 10);
    mstory5_ObjRotMove(objs[2], 0.0f, 90.0f, 0.0f, 10);
    Hu3DMotionShiftSet(objs[0]->model[1], Hu3DData[objs[0]->motion[3]].motId, 0, 10, 2);
    for (i = 0; i < frames; i++) {
        for (j = 0; j < 3; j++) {
            Hu3DData[objs[j]->model[1]].pos.x -= speed[j];
            Hu3DData[objs[j]->model[2]].pos.x -= speed[j];
        }
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(objs[0]->model[1], Hu3DData[objs[0]->motion[0]].motId, 0, 10, 2);
    mstory5_scene1WorkTbl[7].unk_08 |= 1;
    mstory5_scene1WorkTbl[7].func = mstory5_Scene1ObjIdle;
}

const Vec mstory5_scene1StarDestRot6 = { 0.0f, 10.0f, 0.0f };

void mstory5_Scene1GroupTurn(omObjData *obj) {
    omObjData *objs[3];
    f32 rotY[3] = { 90.0f, 135.0f, 135.0f };
    f32 rotX[3] = { 0.0f, 10.0f, 20.0f };
    s32 frames;
    s32 i;
    s32 j;

    frames = 20;
    objs[0] = mstory5_scene1WorkTbl[0].obj;
    objs[1] = mstory5_scene1WorkTbl[7].obj;
    objs[2] = mstory5_scene1WorkTbl[1].obj;
    Hu3DMotionShiftSet(objs[0]->model[1], Hu3DData[objs[0]->motion[3]].motId, 0, 10, 2);
    for (i = 0; i < frames; i++) {
        for (j = 0; j < 3; j++) {
            Hu3DData[objs[j]->model[1]].rot.y += 90.0f / frames;
        }
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(objs[0]->model[1], Hu3DData[objs[0]->motion[0]].motId, 0, 10, 2);
    while (!(mstory5_scene1WorkTbl[7].unk_08 & 2)) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(objs[0]->model[1], Hu3DData[objs[0]->motion[3]].motId, 0, 10, 2);
    frames = 20;
    for (i = 0; i < frames; i++) {
        for (j = 0; j < 3; j++) {
            Hu3DData[objs[j]->model[1]].rot.y -= rotY[j] / frames;
            Hu3DData[objs[j]->model[1]].rot.x += rotX[j] / frames;
        }
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(objs[0]->model[1], Hu3DData[objs[0]->motion[0]].motId, 0, 10, 2);
    mstory5_scene1WorkTbl[7].func = mstory5_Scene1ObjIdle;
}

const s32 mstory5_scene1UnusedStampMdlTbl[] = { 0x1D0003, 0x1D0004, 0x1D0005, 0x1D0006 };

void mstory5_Scene1StarTurn3(omObjData *obj) {
    HuPrcSleep(60);
    mstory5_ObjRotMove(obj, 0.0f, 30.0f, 0.0f, 50);
    mstory5_scene1WorkTbl[7].func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1StarFloatProc(void) {
    f32 angle = 0.0f;
    omObjData *obj;
    Vec pos;
    f32 ofs;
    s16 model;

    if (mstory5_scene1StarFloatF != 0) {
        obj = mstory5_scene1WorkTbl[7].obj;
        model = obj->model[1];
        pos.y = Hu3DData[model].pos.y;
        while (TRUE) {
            model = obj->model[1];
            pos.x = Hu3DData[model].pos.x;
            pos.z = Hu3DData[model].pos.z;
            ofs = sindf(angle) * 25.0f + 25.0f;
            angle += 2.0f;
            angle = (angle >= 360.0f) ? angle - 360.0f : angle;
            if (mstory5_scene1StarFloatStopF != 1) {
                Hu3DModelPosSet(model, pos.x, ofs + pos.y, pos.z);
            }
            HuPrcVSleep();
        }
    }
}

void mstory5_Scene1StampProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 8, 0, -1, NULL);
    mstory5_scene1WorkTbl[8].obj = obj;
    mstory5_scene1WorkTbl[8].unk_08 = 0;
    mstory5_scene1WorkTbl[8].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(mstory5_scene1StampMdlTbl[0], 0x20299);
    obj->model[2] = Hu3DModelRead(mstory5_scene1StampMdlTbl[1], 0x20299);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DMotionAttrSet(obj->model[2], 2, 2);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    mstory5_scene1StampPos = mstory5_scene1StampStartPos;
    Hu3DModelPosSet(obj->model[1], mstory5_scene1StampPos.x, mstory5_scene1StampPos.y, mstory5_scene1StampPos.z);
    mstory5_scene1StampEff = EffectCreate(0xB0004, 0x6A9);
    EffectParamSet(mstory5_scene1StampEff, 4.0f, 20.0f, 4.0f);
    EffectRangeSet(mstory5_scene1StampEff, 60.0f);
    Hu3DParticleAttrSet(mstory5_scene1StampEff, 1, 0);
    Hu3DModelAttrSet(mstory5_scene1StampEff, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    omPrcSetDestructor(0, mstory5_Scene1StampDestroy);
    mstory5_scene1WorkTbl[8].func = mstory5_Scene1ObjIdle;
    while (1) {
        mstory5_scene1WorkTbl[8].func(obj);
        HuPrcVSleep();
    }
}

void mstory5_Scene1StampDestroy(void) {
}

void mstory5_Scene1StampFlyExec(omObjData *obj) {
    Vec pos;
    MstoryPath *paths[2];
    omObjData *target;
    f32 rotY;
    s32 i;

    paths[0] = mstory5_Scene1PathCreate(mstory5_scene1StampPathA, 0);
    paths[1] = mstory5_Scene1PathCreate(mstory5_scene1StampPathB, 0);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(mstory5_scene1StampEff, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DParticleAttrSet(mstory5_scene1StampEff, 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 50; i++) {
        mstory5_Scene1PathPosGet(paths[0], (i * 0.02f) * (i * 0.02f), &pos);
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        EffectPosSet(mstory5_scene1StampEff, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    target = mstory5_scene1WorkTbl[7].obj;
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[3]].motId, 0, 10, 0);
    HuPrcSleep(20);
    mstory5_scene1WorkTbl[8].unk_08 |= 2;
    HuAudFXPlay(0x218);
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[0]].motId, 0, 10, 2);
    rotY = 0.0f;
    for (i = 0; i < 120; i++) {
        mstory5_Scene1PathPosGet(paths[1], (i * 0.008333334f) * (i * 0.008333334f), &pos);
        rotY -= 24.0f;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        Hu3DModelRotSet(obj->model[1], 0.0f, rotY, 0.0f);
        EffectPosSet(mstory5_scene1StampEff, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DParticleAttrSet(mstory5_scene1StampEff, 1, 0);
    HuAudFXPlay(0x21A);
    mstory5_Scene1PathKill(paths[0]);
    mstory5_Scene1PathKill(paths[1]);
    mstory5_scene1WorkTbl[8].unk_08 = 1;
    mstory5_scene1WorkTbl[8].func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1StampBShowExec(omObjData *obj) {
    Vec pos;
    MstoryPath *path;
    s32 i;

    path = mstory5_Scene1PathCreate(mstory5_scene1StampBPath, 0);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DParticleAttrSet(mstory5_scene1StampEff, 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 50; i++) {
        mstory5_Scene1PathPosGet(path, (i * 0.02f) * (i * 0.02f), &pos);
        pos.x += -100.0f;
        Hu3DModelPosSet(obj->model[2], pos.x, pos.y, pos.z);
        EffectPosSet(mstory5_scene1StampEff, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    while (!(mstory5_scene1WorkTbl[8].unk_08 & 0x10)) {
        HuPrcVSleep();
    }
    for (i = 0; i < 50; i++) {
        mstory5_Scene1PathPosGet(path, (1.0f - i * 0.02f) * (1.0f - i * 0.02f), &pos);
        pos.x += -100.0f;
        Hu3DModelPosSet(obj->model[2], pos.x, pos.y, pos.z);
        EffectPosSet(mstory5_scene1StampEff, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DParticleAttrSet(mstory5_scene1StampEff, 1, 0);
    mstory5_Scene1PathKill(path);
    mstory5_scene1WorkTbl[8].unk_08 = 8;
    mstory5_scene1WorkTbl[8].func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1ObjTargetFace(omObjData *obj, omObjData *target) {
    s16 model[2];
    Vec pos[2];
    Vec rot;
    Vec diff;
    s32 i;

    model[0] = obj->model[1];
    model[1] = target->model[1];
    for (i = 0; i < 2; i++) {
        pos[i].x = Hu3DData[model[i]].pos.x;
        pos[i].y = Hu3DData[model[i]].pos.y;
        pos[i].z = Hu3DData[model[i]].pos.z;
    }
    rot.x = Hu3DData[model[0]].rot.x;
    rot.y = Hu3DData[model[0]].rot.y;
    rot.z = Hu3DData[model[0]].rot.z;
    diff.x = pos[1].x - pos[0].x;
    diff.y = pos[1].y - pos[0].y;
    diff.z = pos[1].z - pos[0].z;
    rot.y = -(atan2df(diff.z, diff.x) - 90.0f);
    Hu3DModelRotSet(model[0], rot.x, rot.y, rot.z);
}

void mstory5_Scene1TumbleDaisyFace(omObjData *obj) {
    mstory5_Scene1ObjTargetFace(obj, mstory5_scene1WorkTbl[3].obj);
}

void mstory5_Scene1EventProc(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    mstory5_scene1EventWork.obj = obj;
    mstory5_scene1EventWork.unk_08 = 0;
    mstory5_scene1EventWork.unk_0C = 0;
    mstory5_scene1EventWork.func = mstory5_Scene1ObjIdle;

    for (;;) {
        mstory5_scene1EventWork.func(obj);
        HuPrcVSleep();
    }
}

void mstory5_Scene1SubEventProc(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    mstory5_scene1SubEventWork.obj = obj;
    mstory5_scene1SubEventWork.unk_08 = 0;
    mstory5_scene1SubEventWork.unk_0C = 0;
    mstory5_scene1SubEventWork.func = mstory5_Scene1ObjIdle;

    for (;;) {
        mstory5_scene1SubEventWork.func(obj);
        HuPrcVSleep();
    }
}

void mstory5_Scene1EventMesExec(omObjData *obj) {
    mstory5_WinOpen();
    mstory5_WinMesSet(mstory5_PlayerChrCheck(0) == 0 ? 0x5A56 : 0x5B4A);
    mstory5_WinMesWait();
    mstory5_WinClose();
    mstory5_scene1WorkTbl[4].unk_08 |= 0x10;
    mstory5_scene1EventWork.func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1DaisyStep(omObjData *obj) {
    mstory5_Scene1ObjTargetFace(obj, mstory5_scene1WorkTbl[0].obj);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 30, 2);
    mstory5_Scene1ObjSeLoopStart(3, 31);
    mstory5_ObjForwardMove(obj, 4.5f, 15);
    mstory5_Scene1ObjSeLoopStop(3);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 30, 2);
    mstory5_scene1WorkTbl[3].func = mstory5_Scene1ObjIdle;
    mstory5_scene1SubEventWork.func = mstory5_Scene1PlayerStep;
}

void mstory5_Scene1TumbleLand(omObjData *obj) {
    while (TRUE) {
        if (Hu3DData[obj->model[1]].pos.y > 100.0f) {
            Hu3DData[obj->model[1]].pos.y -= 2.0f;
            HuPrcVSleep();
        } else {
            break;
        }
    }
    Hu3DData[obj->model[1]].pos.y = 100.0f;
    mstory5_scene1WorkTbl[1].func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1StarTurn2(omObjData *obj) {
    Vec pos = mstory5_scene1StarDestRot7;

    mstory5_ObjRotMoveV(obj, &pos, 10);
    mstory5_scene1WorkTbl[7].func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1PlayerStep(omObjData *obj) {
    omObjData *player = mstory5_scene1WorkTbl[0].obj;

    mstory5_Scene1ObjTargetFace(player, mstory5_scene1WorkTbl[3].obj);
    Hu3DMotionShiftSet(player->model[1], Hu3DData[player->motion[3]].motId, 0, 30, 2);
    mstory5_Scene1ObjSeLoopStart(0, 31);
    mstory5_ObjForwardMove(player, 3.5f, 15);
    mstory5_Scene1ObjSeLoopStop(0);
    CharAnimSet(player->model[1], 2, GwStory.unk1, mstory5_scene1PlayerFaceAnim1);
    Hu3DMotionShiftSet(player->model[1], Hu3DData[player->motion[11]].motId, 0, 30, 2);
    CharAnimSet(mstory5_scene1WorkTbl[3].obj->model[1], 2, 7, mstory5_scene1DaisyFaceAnimTbl[0]);
    Hu3DMotionShiftSet(mstory5_scene1WorkTbl[3].obj->model[1], Hu3DData[mstory5_scene1WorkTbl[3].obj->motion[11]].motId, 0, 30, 2);
    mstory5_scene1SubEventWork.func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1TumbleHop2(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec target = mstory5_scene1TumbleDestRot8;
    f32 y;
    s16 i;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    mstory5_HmfAnimSet(model, mstory5_scene1TumbleFaceSlot, mstory5_scene1TumbleFaceAnim2);
    for (i = 0; i < 13; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        Hu3DData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    mstory5_ObjRotMoveV(obj, &target, 5);
    mstory5_HmfAnimSet(model, mstory5_scene1TumbleFaceSlot, mstory5_scene1TumbleFaceAnim0);
    mstory5_scene1WorkTbl[1].unk_08 |= 2;
    mstory5_scene1WorkTbl[1].func = mstory5_Scene1TumbleDaisyFace;
}

void mstory5_Scene1PlayerKnockBack(omObjData *obj) {
    Vec pos = mstory5_scene1PlayerDestRot4;
    Vec target;
    omObjData *player = mstory5_scene1WorkTbl[0].obj;

    target.x = Hu3DData[player->model[1]].pos.x - 5.0f;
    target.y = Hu3DData[player->model[1]].pos.y;
    target.z = 500.0f;
    Hu3DModelRotSet(player->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(player->model[4], Hu3DData[player->model[1]].pos.x, Hu3DData[player->model[1]].pos.y, Hu3DData[player->model[1]].pos.z);
    Hu3DMotionTimeSet(player->model[4], 0.0f);
    Hu3DModelAttrSet(player->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    CharAnimSet(player->model[1], 2, GwStory.unk1, mstory5_scene1PlayerFaceAnimTbl[3]);
    Hu3DMotionShiftSet(player->model[1], Hu3DData[player->motion[4]].motId, 0, 30, 0);
    mstory5_ObjPosMoveV(player, &target, 10);
    mstory5_MotionEndWait(player->model[1]);
    CharAnimSet(player->model[1], 2, GwStory.unk1, mstory5_scene1PlayerFaceAnimTbl[0]);
    Hu3DMotionShiftSet(player->model[1], Hu3DData[player->motion[0]].motId, 0, 30, 2);
    mstory5_ObjRotMoveV(player, &pos, 10);
    mstory5_scene1SubEventWork.func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1DaisyKnockBack(omObjData *obj) {
    Vec pos = mstory5_scene1DaisyDestRot2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x + 5.0f;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    target = tmp;
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[3], Hu3DData[obj->model[1]].pos.x, Hu3DData[obj->model[1]].pos.y, Hu3DData[obj->model[1]].pos.z);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    CharAnimSet(obj->model[1], 2, 7, mstory5_scene1DaisyFaceAnimTbl[3]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[14]].motId, 0, 30, 0);
    mstory5_ObjPosMoveV(obj, &target, 10);
    mstory5_MotionEndWait(obj->model[1]);
    CharAnimSet(obj->model[1], 2, 7, mstory5_scene1DaisyFaceAnimTbl[0]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 30, 2);
    mstory5_ObjRotMoveV(obj, &pos, 10);
    mstory5_scene1WorkTbl[3].func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1PlayerPose(omObjData *obj) {
    omObjData *target = mstory5_scene1WorkTbl[0].obj;

    mstory5_ObjRotMove(target, 0.0f, 0.0f, 0.0f, 10);
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[8]].motId, 0, 10, 0);
    mstory5_scene1SubEventWork.func = mstory5_Scene1ObjIdle;
}

void mstory5_Scene1DaisyPose(omObjData *obj) {
    omObjData *target = mstory5_scene1WorkTbl[3].obj;

    mstory5_ObjRotMove(target, 0.0f, 0.0f, 0.0f, 10);
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[13]].motId, 0, 10, 0);
    mstory5_scene1WorkTbl[3].func = mstory5_Scene1ObjIdle;
}

const s32 mstory5_scene1StampMdlTbl[3] = { 0x1D0007, 0x1D0008, 0x1D0009 };

const Vec mstory5_scene1StarDestRot7 = { 0.0f, 0.0f, 0.0f };

const Vec mstory5_scene1TumbleDestRot8 = { 0.0f, 167.0f, 0.0f };

const Vec mstory5_scene1PlayerDestRot4 = { 0.0f, 180.0f, 0.0f };

const Vec mstory5_scene1DaisyDestRot2 = { 0.0f, -180.0f, 0.0f };

void mstory5_Scene1ObjSeLoopStart(s32 index, s32 seNo) {
    if (mstory5_scene1WorkTbl[index].unk_0C == 0) {
        mstory5_scene1WorkTbl[index].unk_0C = 1;
        mstory5_scene1WorkTbl[index].unk_10 = seNo;
        switch (index) {
            case 0:
                mstory5_scene1WorkTbl[index].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                break;
            case 2:
                if (mstory5_PlayerChrCheck(0) == 0) {
                    mstory5_scene1WorkTbl[index].unk_14 = CharFXPlay(seNo, 0);
                } else {
                    mstory5_scene1WorkTbl[index].unk_14 = CharFXPlay(seNo, 1);
                }
                break;
            case 3:
                mstory5_scene1WorkTbl[index].unk_14 = CharFXPlay(seNo, 7);
                break;
            case 1:
            case 4:
            case 5:
            case 6:
                break;
        }
    }
}

void mstory5_Scene1ObjSeLoopStop(s32 index) {
    if (mstory5_scene1WorkTbl[index].unk_0C == 1) {
        mstory5_scene1WorkTbl[index].unk_0C = 0;
        switch (index) {
            case 0:
            case 2:
            case 3:
                HuAudFXStop((s16)mstory5_scene1WorkTbl[index].unk_14);
            case 1:
            case 4:
            case 5:
            case 6:
                break;
        }
    }
}

void mstory5_Scene1ObjSeLoopProc(void) {
    s32 i;
    s32 seNo;

    while (TRUE) {
        for (i = 0; i < 9; i++) {
            if (mstory5_scene1WorkTbl[i].unk_0C == 1 && Hu3DData[mstory5_scene1WorkTbl[i].obj->model[1]].motTime == 0.0f) {
                seNo = mstory5_scene1WorkTbl[i].unk_10;
                switch (i) {
                    case 0:
                        mstory5_scene1WorkTbl[i].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                        break;
                    case 2:
                        if (mstory5_PlayerChrCheck(0) == 0) {
                            mstory5_scene1WorkTbl[i].unk_14 = CharFXPlay(seNo, 0);
                        } else {
                            mstory5_scene1WorkTbl[i].unk_14 = CharFXPlay(seNo, 1);
                        }
                        break;
                    case 3:
                        mstory5_scene1WorkTbl[i].unk_14 = CharFXPlay(seNo, 7);
                        break;
                    case 1:
                    case 4:
                    case 5:
                    case 6:
                        break;
                }
            }
        }
        HuPrcVSleep();
    }
}

void mstory5_Scene1DaisySeFadeIn(omObjData *obj) {
    f32 step = 0.35f;
    f32 vol = 0.0f;
    s32 i;

    if (mstory5_scene1WorkTbl[3].unk_0C == 1) {
        for (i = 0; i < 180; i++) {
            HuAudFXVolSet((s16)mstory5_scene1WorkTbl[3].unk_14, (s32)vol + 64);
            vol += step;
            HuPrcVSleep();
        }
        HuAudFXVolSet((s16)mstory5_scene1WorkTbl[3].unk_14, 127);
    }
    mstory5_scene1SubEventWork.func = mstory5_Scene1ObjIdle;
}
