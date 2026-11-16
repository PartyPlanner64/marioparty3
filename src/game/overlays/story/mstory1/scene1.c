#include "common.h"
#include "game/hmfmath.h"
#include "mstory1.h"

typedef struct MstoryPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ u16 flags;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec *points;
    /* 0x0C */ f32 (*intervals)[2];
} MstoryPath; // sizeof 0x10

extern const Vec mstory1_scene1PlayerDestRot3;
extern const Vec mstory1_scene1PlayerDestRot4;
extern const Vec mstory1_scene1TumbleDestPos2;
extern const Vec mstory1_scene1TumbleDestRot7;
extern const Vec mstory1_scene1StarDestRot5;
extern const Vec mstory1_scene1StarDestRot6;
extern const Vec mstory1_scene1KoopaJrBStartPos;
extern StoryObjWork mstory1_scene1WorkTbl[8];
extern const Vec mstory1_scene1PlayerDestRot0;
extern const Vec mstory1_scene1PlayerDestRot1;
extern const Vec mstory1_scene1PlayerDestRot2;
extern const Vec mstory1_scene1PlayerDestPos0;
extern Vec mstory1_scene1KoopaJrBPos;
extern s16 mstory1_scene1ShadowMdl;
extern s16 mstory1_scene1TumbleFaceAnim2;
extern s16 mstory1_scene1TumbleFaceSlot;
extern s32 mstory1_scene1TumbleFaceAnimTbl[3];
extern s16 mstory1_scene1TumbleFaceAnim0;
extern Vec mstory1_scene1TumblePos;
extern const Vec mstory1_scene1TumbleStartPos;
extern Vec mstory1_scene1StampPos;
extern const Vec mstory1_scene1StampStartPos;
extern s16 mstory1_scene1StampEff;
extern const s32 mstory1_scene1StampMdlTbl[7];
extern Vec mstory1_scene1KoopaJrAPos;
extern const Vec mstory1_scene1KoopaJrAStartPos;
extern Vec mstory1_scene1StarPos;
extern const Vec mstory1_scene1StarStartPos;
extern Vec mstory1_scene1RivalPos;
extern const Vec mstory1_scene1RivalStartPos;
extern Vec mstory1_scene1KoopaPos;
extern const Vec mstory1_scene1KoopaStartPos;
extern const Vec mstory1_scene1TumbleDestRot2;
extern const Vec mstory1_scene1TumbleDestRot3;
extern const Vec mstory1_scene1TumbleDestRot4;
extern const Vec mstory1_scene1TumbleDestRot5;
extern const Vec mstory1_scene1TumbleDestRot6;
extern const Vec mstory1_scene1TumbleDestPos0;
extern const Vec mstory1_scene1TumbleDestPos1;
extern const Vec mstory1_scene1StarDestRot3;
extern const Vec mstory1_scene1StarDestRot4;
extern s16 mstory1_scene1TumbleFaceAnim1;
extern const Vec mstory1_scene1TumbleDestRot0;
extern s32 omCharModelNoTbl[][6];
extern Vec mstory1_scene1PlayerPos;
extern const Vec mstory1_scene1PlayerStartPos;
extern const s32 mstory1_scene1PlayerMot5Tbl[];
extern const s32 mstory1_scene1PlayerMot6Tbl[];
extern const s32 mstory1_scene1PlayerMot7Tbl[];
extern const s32 mstory1_scene1PlayerMot9Tbl[];
extern s16 mstory1_scene1PlayerFaceAnimTbl[4];
extern const Vec mstory1_scene1KoopaDestPos0;
extern const Vec mstory1_scene1KoopaDestRot0;
extern const Vec mstory1_scene1KoopaDestRot1;
extern const Vec mstory1_scene1KoopaDestRot2;
extern const Vec mstory1_scene1KoopaJrADestPos0;
extern const Vec mstory1_scene1KoopaJrADestRot0;
extern const Vec mstory1_scene1KoopaJrADestRot1;
extern const Vec mstory1_scene1KoopaJrADestRot2;
extern const Vec mstory1_scene1KoopaJrADestRot3;
extern const Vec mstory1_scene1KoopaJrBDestPos0;
extern const Vec mstory1_scene1KoopaJrBDestRot0;
extern const Vec mstory1_scene1KoopaJrBDestRot1;
extern const Vec mstory1_scene1KoopaJrBDestRot2;
extern const Vec mstory1_scene1KoopaJrBDestRot3;

s32 mstory1_scene1StarFloatF = 0;
Vec mstory1_scene1StampPathA[4] = {
    { 0.0f, 200.0f, 100.0f },
    { -200.0f, 100.0f, -100.0f },
    { -100.0f, 300.0f, 300.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};
Vec mstory1_scene1StampPathB[6] = {
    { -100.0f, 300.0f, 300.0f },
    { -200.0f, 200.0f, 100.0f },
    { 0.0f, 300.0f, -100.0f },
    { 400.0f, 400.0f, 200.0f },
    { -50.0f, 120.0f, 450.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};

void mstory1_Scene1PathPosGet(MstoryPath *path, f32 time, Vec *result);
void mstory1_StampCardStart(s32 arg0);
s32 mstory1_StampCardDoneCheck(void);
void mstory1_ObjPosMoveEx(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void mstory1_ObjPosMoveV(omObjData *obj, const Vec *pos, s32 frames);
s32 mstory1_PlayerChrCheck(s32 character);
void mstory1_ObjRotMoveV(omObjData *obj, const Vec *pos, s32 frames);
void mstory1_HmfAnimSet(s16 model, s16 animSlot, s16 anim);
void mstory1_MotionEndWait(s16 model);
void mstory1_Scene1ObjIdle(omObjData *obj);
void mstory1_Scene1TumbleExec(omObjData *obj);
void mstory1_Scene1RivalDestroy(void);
void mstory1_Scene1RivalExec(omObjData *obj);
void mstory1_Scene1KoopaDestroy(void);
void mstory1_Scene1ObjSeLoopStart(s32 index, s32 seNo);
void mstory1_Scene1ObjSeLoopStop(s32 index);
void mstory1_Scene1StarExit(omObjData *obj);
void mstory1_Scene1KoopaExec(omObjData *obj);
void mstory1_Scene1TumbleExit(omObjData *obj);
void mstory1_Scene1TumbleHop(omObjData *obj);
void mstory1_SceneEnd(void);
void mstory1_WinCreate(void);
void mstory1_Scene1PlayerProc(void);
void mstory1_Scene1TumbleProc(void);
void mstory1_Scene1PlayerStampExec(omObjData *obj);
void mstory1_WinOpen(void);
void mstory1_WinClose(void);
void mstory1_WinMesExec(s32 mess);
void mstory1_ObjRotMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void mstory1_Scene1StarTurn(omObjData *obj);
void mstory1_Scene1StampFlyExec(omObjData *obj);
void mstory1_Scene1TumbleDestroy(void);
void mstory1_Scene1RivalProc(void);
void mstory1_Scene1KoopaProc(void);
void mstory1_Scene1KoopaJrAProc(void);
void mstory1_Scene1KoopaJrAExec(omObjData *obj);
void mstory1_Scene1KoopaJrBExec(omObjData *obj);
void mstory1_Scene1KoopaJrBProc(void);
void mstory1_Scene1KoopaJrBDestroy(void);
void mstory1_Scene1StarProc(void);
void mstory1_Scene1StarFloatProc(void);
void mstory1_Scene1StampProc(void);
void mstory1_Scene1ObjSeLoopProc(void);
void mstory1_Scene1KoopaJrADestroy(void);
void mstory1_Scene1StarDestroy(void);
void mstory1_Scene1StampDestroy(void);
void mstory1_Scene1PlayerDestroy(void);

MstoryPath *mstory1_Scene1PathCreate(Vec *points, s32 flags) {
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

void mstory1_Scene1PathPosGet(MstoryPath *path, f32 time, Vec *result) {
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

void mstory1_Scene1PathKill(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void mstory1_Scene1Create(void) {
    mstory1_WinCreate();
    mstory1_scene1ShadowMdl = Hu3DModelRead(9, 0x2B9);
    omAddPrcObj(mstory1_Scene1PlayerProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory1_Scene1TumbleProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory1_Scene1RivalProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory1_Scene1KoopaProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory1_Scene1KoopaJrAProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory1_Scene1KoopaJrBProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory1_Scene1StarProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory1_Scene1StarFloatProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory1_Scene1StampProc, 0x384, 0x800, 0);
    omAddPrcObj(mstory1_Scene1ObjSeLoopProc, 0x384, 0x800, 0);
    HuPrcVSleep();
    Hu3DModelAttrSet(mstory1_scene1ShadowMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void mstory1_Scene1ObjIdle(omObjData *obj) {
}

void mstory1_Scene1PlayerProc(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 6, 16, -1, NULL);
    mstory1_scene1WorkTbl[0].obj = obj;
    mstory1_scene1WorkTbl[0].unk_08 = 0;
    mstory1_scene1WorkTbl[0].unk_0C = 0;
    chr = GwStory.unk1;
    obj->model[1] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory1_scene1ShadowMdl);
    if (GwStory.unk1 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    obj->model[3] = Hu3DModelRead(0x1D000A, 0x2B9);
    Hu3DModelAttrSet(obj->model[3], 4, 4);
    obj->model[4] = Hu3DModelRead(0x83, 0x2B9);
    Hu3DModelAttrSet(obj->model[4], 4, 4);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 0x9C));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 1));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chr, 0x21));
    omObjMotionRead(obj, 5, mstory1_scene1PlayerMot5Tbl[chr]);
    omObjMotionRead(obj, 6, mstory1_scene1PlayerMot6Tbl[chr]);
    omObjMotionRead(obj, 7, mstory1_scene1PlayerMot7Tbl[chr]);
    omObjMotionRead(obj, 8, CharMotionDataNumGet(chr, 0x33));
    omObjMotionRead(obj, 9, mstory1_scene1PlayerMot9Tbl[chr]);
    omObjMotionRead(obj, 10, CharMotionDataNumGet(chr, 0x9B));
    mstory1_scene1PlayerFaceAnimTbl[0] = CharAnimCreate(obj->model[1], 2, chr, CharMotionDataNumGet(chr, 0xA4));
    mstory1_scene1PlayerFaceAnimTbl[1] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xAA));
    mstory1_scene1PlayerFaceAnimTbl[2] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA5));
    mstory1_scene1PlayerFaceAnimTbl[3] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA9));
    Hu3DModelDynamicFree(obj->model[1]);
    CharAnimSet(obj->model[1], 2, GwStory.unk1, mstory1_scene1PlayerFaceAnimTbl[0]);
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    mstory1_scene1PlayerPos = mstory1_scene1PlayerStartPos;
    Hu3DModelPosSet(obj->model[1], mstory1_scene1PlayerPos.x, mstory1_scene1PlayerPos.y, mstory1_scene1PlayerPos.z);
    Hu3DModelPosSet(obj->model[2], mstory1_scene1PlayerPos.x, -5.0f, mstory1_scene1PlayerPos.z);
    Hu3DModelPosSet(obj->model[4], mstory1_scene1PlayerPos.x, mstory1_scene1PlayerPos.y, mstory1_scene1PlayerPos.z);
    omPrcSetDestructor(0, mstory1_Scene1PlayerDestroy);
    mstory1_scene1WorkTbl[0].func = mstory1_Scene1ObjIdle;
    while (TRUE) {
        mstory1_scene1WorkTbl[0].func(obj);
        HuPrcVSleep();
    }
}

void mstory1_Scene1PlayerDestroy(void) {
}

const Vec mstory1_scene1PlayerStartPos = { -120.0f, 0.0f, 480.0f };

const Vec mstory1_scene1TumbleStartPos = { 38.0f, 100.0f, 214.0f };

const Vec mstory1_scene1RivalStartPos = { 150.0f, 0.0f, 384.0f };

const Vec mstory1_scene1KoopaStartPos = { -800.0f, 0.0f, 480.0f };

const Vec mstory1_scene1KoopaJrAStartPos = { -700.0f, 0.0f, 300.0f };

const Vec mstory1_scene1KoopaJrBStartPos = { -800.0f, 0.0f, 300.0f };

const Vec mstory1_scene1StarStartPos = { 0.0f, 200.0f, 150.0f };

const Vec mstory1_scene1StampStartPos = { 0.0f, 200.0f, 100.0f };

const s32 mstory1_scene1PlayerMot5Tbl[8] = { 0x1D003E, 0x1D0048, 0x1D0052, 0x1D005B, 0x1D0065, 0x1D006E, 0x1D003E, 0x1D003E };

const s32 mstory1_scene1PlayerMot6Tbl[8] = { 0x1D0040, 0x1D004B, 0x1D0054, 0x1D005D, 0x1D0067, 0x1D0070, 0x1D0040, 0x1D0040 };

const s32 mstory1_scene1PlayerMot7Tbl[8] = { 0x1D0041, 0x1D004C, 0x1D0055, 0x1D005E, 0x1D0068, 0x1D0071, 0x1D0041, 0x1D0041 };

const s32 mstory1_scene1PlayerMot9Tbl[8] = { 0x1D0043, 0x1D004E, 0x1D0057, 0x1D0060, 0x1D006A, 0x1D0073, 0x1D0043, 0x1D0043 };

const Vec mstory1_scene1PlayerDestRot0 = { 0.0f, 0.0f, 0.0f };

const Vec mstory1_scene1PlayerDestRot1 = { 0.0f, 180.0f, 0.0f };

const Vec mstory1_scene1PlayerDestRot2 = { 0.0f, 90.0f, 0.0f };
const Vec mstory1_scene1UnusedRot0 = { 0.0f, -90.0f, 0.0f };       /* Unreferenced. */
const Vec mstory1_scene1UnusedPos0 = { 146.66666f, 0.0f, 480.0f }; /* Unreferenced. */

const Vec mstory1_scene1PlayerDestPos0 = { 730.0f, 0.0f, 480.0f };
const Vec mstory1_scene1UnusedPos1 = { 196.66666f, 0.0f, 480.0f }; /* Unreferenced. */

const Vec mstory1_scene1StarDestPos0 = { -100.0f, 0.0f, 350.0f };

const Vec mstory1_scene1StarDestPos1 = { -100.0f, 0.0f, 150.0f };

const Vec mstory1_scene1StarDestRot0 = { 0.0f, 20.0f, 0.0f };

const Vec mstory1_scene1StarDestRot1 = { 0.0f, 0.0f, 0.0f };

const Vec mstory1_scene1StarDestRot2 = { 0.0f, -26.565f, 0.0f };

void mstory1_Scene1PlayerStampExec(omObjData *obj) {
    s16 model;
    HmfMotionNode *node;
    omObjData *other;
    s32 i;
    f32 scale;
    f32 time;
    s32 fx;

    HuPrcSleep(20);
    model = obj->model[1];
    HuPrcSleep(50);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory1_ObjRotMove(obj, 0.0f, 110.0f, 0.0f, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    HuPrcSleep(10);
    Hu3DModelAttrSet(obj->model[3], 0x4000, 0x4000);
    Hu3DModelHookSet(obj->model[3], model, "item_hook");
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, 0);
    mstory1_MotionEndWait(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[5]].motId, 0, 10, 0);
    mstory1_MotionEndWait(model);
    while (!(mstory1_scene1WorkTbl[7].unk_08 & 1)) {
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(mstory1_scene1WorkTbl[7].obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mstory1_scene1StampEff, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DMotionNoMotSet(model, Hu3DData[model].motId, "item_hook", 27, 69);
    Hu3DMotionNoMotSet(model, Hu3DData[model].motId, "item_hook", 27, 70);
    Hu3DMotionNoMotSet(model, Hu3DData[model].motId, "item_hook", 27, 71);
    node = Hu3DModelObjPtrGet(model, "item_hook");
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
    Hu3DMotionNoMotReset(model, Hu3DData[model].motId, "item_hook", 27, 71);
    Hu3DMotionNoMotReset(model, Hu3DData[model].motId, "item_hook", 27, 70);
    Hu3DMotionNoMotReset(model, Hu3DData[model].motId, "item_hook", 27, 69);
    mstory1_StampCardStart(1);
    while (TRUE) {
        if (mstory1_StampCardDoneCheck() != 0) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    mstory1_WinOpen();
    mstory1_WinMesExec(mstory1_PlayerChrCheck(3) == 0 ? 0x5A25 : 0x5B16);
    mstory1_WinClose();
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
    Hu3DModelAttrSet(obj->model[3], 0x4000, 0);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    HuAudSeqFadeOut(20);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    mstory1_ObjRotMoveV(obj, &mstory1_scene1PlayerDestRot0, 10);
    HuAudSeqPlay(0x72);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
    CharAnimSet(obj->model[1], 2, GwStory.unk1, mstory1_scene1PlayerFaceAnimTbl[2]);
    mstory1_MotionEndWait(model);
    fx = CharFXPlay(0x262, GwStory.unk1);
    HuPrcSleep(30);
    other = mstory1_scene1WorkTbl[6].obj;
    mstory1_ObjRotMoveV(other, &mstory1_scene1StarDestRot2, 3);
    mstory1_ObjPosMoveV(other, &mstory1_scene1StarDestPos0, 5);
    mstory1_ObjRotMoveV(other, &mstory1_scene1StarDestRot0, 3);
    mstory1_scene1WorkTbl[1].func = mstory1_Scene1TumbleHop;
    HuAudFXPlay(0x219);
    HuAudFXStop(fx);
    Hu3DModelAttrSet(obj->model[4], HU3D_ATTR_DISPOFF, 0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    CharAnimSet(obj->model[1], 2, GwStory.unk1, mstory1_scene1PlayerFaceAnimTbl[3]);
    mstory1_ObjRotMoveV(other, &mstory1_scene1StarDestRot1, 3);
    mstory1_ObjPosMoveEx(other, &mstory1_scene1StarDestPos1, 10, 0);
    mstory1_MotionEndWait(model);
    HuAudSeqPlay(0x26);
    mstory1_ObjRotMoveV(obj, &mstory1_scene1PlayerDestRot1, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    CharAnimSet(obj->model[1], 2, GwStory.unk1, mstory1_scene1PlayerFaceAnimTbl[0]);
    HuAudFXPlay(0x159);
    Hu3DMotionShiftSet(mstory1_scene1WorkTbl[6].obj->model[1], Hu3DData[mstory1_scene1WorkTbl[6].obj->motion[1]].motId, 0, 10, 2);
    mstory1_WinOpen();
    mstory1_WinMesExec(mstory1_PlayerChrCheck(3) == 0 ? 0x5A26 : 0x5B17);
    mstory1_WinClose();
    Hu3DMotionShiftSet(mstory1_scene1WorkTbl[6].obj->model[1], Hu3DData[mstory1_scene1WorkTbl[6].obj->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[8]].motId, 0, 10, 0);
    mstory1_MotionEndWait(model);
    mstory1_scene1WorkTbl[6].func = mstory1_Scene1StarExit;
    mstory1_scene1WorkTbl[1].func = mstory1_Scene1TumbleExit;
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 2);
    mstory1_scene1WorkTbl[3].func = mstory1_Scene1KoopaExec;
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 2);
    mstory1_Scene1ObjSeLoopStart(0, 31);
    mstory1_ObjRotMoveV(obj, &mstory1_scene1PlayerDestRot2, 10);
    mstory1_ObjPosMoveV(obj, &mstory1_scene1PlayerDestPos0, 50);
    mstory1_Scene1ObjSeLoopStop(0);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    mstory1_scene1WorkTbl[0].func = mstory1_Scene1ObjIdle;
}

void mstory1_Scene1PlayerReactExec(omObjData *obj) {
    s16 model = obj->model[1];

    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[9]].motId, 0, 10, 0);
    mstory1_MotionEndWait(model);
    HuPrcSleep(80);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory1_scene1WorkTbl[0].func = mstory1_Scene1ObjIdle;
}

void mstory1_Scene1PlayerTurn1(omObjData *obj) {
    mstory1_ObjRotMoveV(obj, &mstory1_scene1PlayerDestRot3, 10);
    mstory1_scene1WorkTbl[0].func = mstory1_Scene1ObjIdle;
}

void mstory1_Scene1PlayerTurn2(omObjData *obj) {
    mstory1_ObjRotMoveV(obj, &mstory1_scene1PlayerDestRot4, 10);
    mstory1_scene1WorkTbl[0].func = mstory1_Scene1ObjIdle;
}

const Vec mstory1_scene1PlayerDestRot3 = { 0.0f, 150.0f, 0.0f };

const Vec mstory1_scene1PlayerDestRot4 = { 0.0f, 162.4f, 0.0f };

const char mstory1_scene1TumbleAnimName[] = "c204n_0_DEF";

void mstory1_Scene1TumbleProc(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(20, 4, 8, -1, NULL);
    mstory1_scene1WorkTbl[1].obj = obj;
    mstory1_scene1WorkTbl[1].unk_08 = 0;
    mstory1_scene1WorkTbl[1].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory1_scene1ShadowMdl);
    omObjMotionRead(obj, 0, 0xA0076);
    omObjMotionRead(obj, 1, 0x1D0029);
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    mstory1_scene1TumblePos = mstory1_scene1TumbleStartPos;
    Hu3DModelPosSet(obj->model[1], mstory1_scene1TumblePos.x, mstory1_scene1TumblePos.y, mstory1_scene1TumblePos.z);
    Hu3DModelPosSet(obj->model[2], mstory1_scene1TumblePos.x, -5.0f, mstory1_scene1TumblePos.z);
    data = DataRead(0xA007E);
    mstory1_scene1TumbleFaceAnimTbl[0] = (s16)Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, mstory1_scene1TumbleAnimName);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    Hu3DAnimAttrSet(mstory1_scene1TumbleFaceAnim0, 1, 0);
    Hu3DAnimBankSet(mstory1_scene1TumbleFaceAnim0, 0);
    mstory1_scene1TumbleFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory1_scene1TumbleFaceAnim0, 0, mstory1_scene1TumbleAnimName);
    mstory1_scene1TumbleFaceAnimTbl[0] = Hu3DAnimData[mstory1_scene1TumbleFaceAnimTbl[0]].animIdx;
    data = DataRead(0xA0080);
    mstory1_scene1TumbleFaceAnimTbl[1] = (s16)Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    mstory1_scene1TumbleFaceAnimTbl[2] = (s16)Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory1_HmfAnimSet(obj->model[1], mstory1_scene1TumbleFaceSlot, mstory1_scene1TumbleFaceAnim0);
    omPrcSetDestructor(0, mstory1_Scene1TumbleDestroy);
    mstory1_scene1WorkTbl[1].func = mstory1_Scene1ObjIdle;
    while (TRUE) {
        mstory1_scene1WorkTbl[1].func(obj);
        HuPrcVSleep();
    }
}

void mstory1_Scene1TumbleDestroy(void) {
}

const Vec mstory1_scene1TumbleDestRot0 = { -5.0f, 300.0f, 0.0f };

const Vec mstory1_scene1TumbleDestRot1 = { 10.0f, 378.9f, 0.0f };

void mstory1_Scene1TumbleExec(omObjData *obj) {
    HuPrcSleep(40);
    HuPrcSleep(20);
    mstory1_scene1WorkTbl[0].func = mstory1_Scene1PlayerReactExec;
    mstory1_scene1WorkTbl[6].func = mstory1_Scene1StarTurn;
    mstory1_ObjRotMoveV(obj, &mstory1_scene1TumbleDestRot1, 30);
    mstory1_ObjPosMoveV(obj, &mstory1_scene1TumbleDestPos1, 20);
    HuPrcSleep(30);
    mstory1_ObjRotMoveV(obj, &mstory1_scene1TumbleDestRot4, 10);
    mstory1_ObjPosMoveV(obj, &mstory1_scene1TumbleDestPos0, 15);
    mstory1_scene1WorkTbl[0].func = mstory1_Scene1PlayerTurn1;
    mstory1_ObjRotMoveV(obj, &mstory1_scene1TumbleDestRot2, 10);
    mstory1_HmfAnimSet(obj->model[1], mstory1_scene1TumbleFaceSlot, mstory1_scene1TumbleFaceAnim1);
    mstory1_WinOpen();
    mstory1_WinMesExec(mstory1_PlayerChrCheck(3) == 0 ? 0x5A23 : 0x5B14);
    mstory1_WinClose();
    mstory1_HmfAnimSet(obj->model[1], mstory1_scene1TumbleFaceSlot, mstory1_scene1TumbleFaceAnim0);
    mstory1_ObjRotMove(mstory1_scene1WorkTbl[0].obj, 0.0f, 162.4744f, 0.0f, 10);
    mstory1_ObjRotMoveV(mstory1_scene1WorkTbl[6].obj, &mstory1_scene1StarDestRot3, 10);
    mstory1_ObjRotMoveV(obj, &mstory1_scene1TumbleDestRot3, 20);
    Hu3DMotionShiftSet(mstory1_scene1WorkTbl[6].obj->model[1], Hu3DData[mstory1_scene1WorkTbl[6].obj->motion[1]].motId, 0, 10, 2);
    mstory1_WinOpen();
    mstory1_WinMesExec(mstory1_PlayerChrCheck(3) == 0 ? 0x5A24 : 0x5B15);
    mstory1_WinClose();
    Hu3DMotionShiftSet(mstory1_scene1WorkTbl[6].obj->model[1], Hu3DData[mstory1_scene1WorkTbl[6].obj->motion[0]].motId, 0, 10, 2);
    mstory1_ObjRotMoveV(mstory1_scene1WorkTbl[6].obj, &mstory1_scene1StarDestRot4, 10);
    mstory1_scene1WorkTbl[7].func = mstory1_Scene1StampFlyExec;
    mstory1_ObjRotMoveV(obj, &mstory1_scene1TumbleDestRot0, 20);
    Hu3DMotionShiftSet(mstory1_scene1WorkTbl[0].obj->model[1], Hu3DData[mstory1_scene1WorkTbl[0].obj->motion[10]].motId, 0, 10, 2);
    while (!(mstory1_scene1WorkTbl[7].unk_08 & 2)) {
        HuPrcVSleep();
    }
    mstory1_scene1WorkTbl[0].func = mstory1_Scene1PlayerStampExec;
    HuPrcSleep(40);
    mstory1_ObjRotMoveV(obj, &mstory1_scene1TumbleDestRot6, 50);
    mstory1_ObjRotMoveV(obj, &mstory1_scene1TumbleDestRot5, 40);
    mstory1_scene1WorkTbl[1].func = mstory1_Scene1ObjIdle;
}

void mstory1_Scene1TumbleExit(omObjData *obj) {
    mstory1_ObjRotMoveV(obj, &mstory1_scene1TumbleDestRot7, 10);
    mstory1_ObjPosMoveV(obj, &mstory1_scene1TumbleDestPos2, 50);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    mstory1_scene1WorkTbl[1].func = mstory1_Scene1ObjIdle;
}

void mstory1_Scene1TumbleHop(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec orig;
    f32 y;
    s32 i;

    orig.x = Hu3DData[model].pos.x;
    orig.y = Hu3DData[model].pos.y;
    orig.z = Hu3DData[model].pos.z;
    pos.y = Hu3DData[model].pos.y;
    for (i = 0; i < 12; i++) {
        pos.x = Hu3DData[model].pos.x;
        pos.z = Hu3DData[model].pos.z;
        y = sindf(i * 15.0f) * 80.0f;
        Hu3DModelPosSet(model, pos.x, y + pos.y, pos.z);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, orig.x, y + orig.y, orig.z);
    mstory1_HmfAnimSet(obj->model[1], mstory1_scene1TumbleFaceSlot, mstory1_scene1TumbleFaceAnim2);
    mstory1_scene1WorkTbl[1].func = mstory1_Scene1ObjIdle;
}

void mstory1_Scene1RivalProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    mstory1_scene1WorkTbl[2].obj = obj;
    mstory1_scene1WorkTbl[2].unk_08 = 0;
    mstory1_scene1WorkTbl[2].unk_0C = 0;
    if (mstory1_PlayerChrCheck(3) == 0) {
        obj->model[1] = Hu3DModelRead(0x400A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(mstory1_scene1ShadowMdl);
        omObjMotionRead(obj, 0, 0x40000);
        omObjMotionRead(obj, 1, 0x1D0059);
        omObjMotionRead(obj, 2, 0x1D005A);
    } else {
        obj->model[1] = Hu3DModelRead(0x300A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(mstory1_scene1ShadowMdl);
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
    mstory1_scene1RivalPos = mstory1_scene1RivalStartPos;
    Hu3DModelPosSet(obj->model[1], mstory1_scene1RivalPos.x, mstory1_scene1RivalPos.y, mstory1_scene1RivalPos.z);
    Hu3DModelPosSet(obj->model[2], mstory1_scene1RivalPos.x, -5.0f, mstory1_scene1RivalPos.z);
    omPrcSetDestructor(0, mstory1_Scene1RivalDestroy);
    mstory1_scene1WorkTbl[2].func = mstory1_Scene1RivalExec;
    while (1) {
        mstory1_scene1WorkTbl[2].func(obj);
        HuPrcVSleep();
    }
}

void mstory1_Scene1RivalDestroy(void) {
}

const Vec mstory1_scene1TumbleDestRot2 = { 20.0f, 320.0f, 0.0f };
const Vec mstory1_scene1UnusedRot1 = { 0.0f, 450.0f, 0.0f }; /* Unreferenced. */

const Vec mstory1_scene1TumbleDestRot3 = { 0.0f, 225.0f, 0.0f };

const Vec mstory1_scene1TumbleDestRot4 = { 0.0f, 134.2f, 0.0f };

const Vec mstory1_scene1TumbleDestRot5 = { 0.0f, 320.0f, 0.0f };

const Vec mstory1_scene1TumbleDestRot6 = { -30.0f, 260.0f, 0.0f };

const Vec mstory1_scene1TumbleDestPos0 = { 238.0f, 100.0f, 214.0f };

const Vec mstory1_scene1TumbleDestPos1 = { 88.0f, 100.0f, 360.0f };

const Vec mstory1_scene1StarDestRot3 = { 30.0f, -20.0f, 0.0f };

const Vec mstory1_scene1StarDestRot4 = { 0.0f, 0.0f, 0.0f };
const Vec mstory1_scene1UnusedPos2 = { 384.66666f, 100.0f, 214.0f }; /* Unreferenced. */

const Vec mstory1_scene1TumbleDestPos2 = { 918.0f, 100.0f, 214.0f };

const Vec mstory1_scene1TumbleDestRot7 = { 0.0f, 90.0f, 0.0f };
const Vec mstory1_scene1UnusedRot2 = { 0.0f, 270.0f, 0.0f }; /* Unreferenced. */

const Vec mstory1_scene1RivalDestPos0 = { 200.0f, 0.0f, 1200.0f };

void mstory1_Scene1RivalExec(omObjData *obj) {
    HuPrcSleep(10);
    if (mstory1_PlayerChrCheck(3) == 0) {
        CharFXPlay(0x26B, 3);
    } else {
        CharFXPlay(0x26B, 1);
    }
    HuPrcSleep(20);
    mstory1_scene1WorkTbl[1].func = mstory1_Scene1TumbleExec;
    HuPrcSleep(70);
    if (mstory1_PlayerChrCheck(3) == 0) {
        CharFXPlay(0x286, 3);
    } else {
        CharFXPlay(0x286, 1);
    }
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    mstory1_Scene1ObjSeLoopStart(2, 40);
    mstory1_ObjPosMoveV(obj, &mstory1_scene1RivalDestPos0, 40);
    mstory1_Scene1ObjSeLoopStop(2);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    mstory1_scene1WorkTbl[2].func = mstory1_Scene1ObjIdle;
}

void mstory1_Scene1KoopaProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    mstory1_scene1WorkTbl[3].obj = obj;
    mstory1_scene1WorkTbl[3].unk_08 = 0;
    mstory1_scene1WorkTbl[3].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0xA002F, 0x2B9);
    obj->model[2] = Hu3DModelLink(mstory1_scene1ShadowMdl);
    Hu3DModelScaleSet(obj->model[2], 3.0f, 1.0f, 3.0f);
    omObjMotionRead(obj, 0, 0xA0030);
    omObjMotionRead(obj, 1, 0xA0035);
    omObjMotionRead(obj, 2, 0xA0032);
    omObjMotionRead(obj, 3, 0x1D0035);
    Hu3DMotionModelSet(obj->model[1], obj->motion[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DModelAttrSet(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    mstory1_scene1KoopaPos = mstory1_scene1KoopaStartPos;
    Hu3DModelPosSet(obj->model[1], mstory1_scene1KoopaPos.x, mstory1_scene1KoopaPos.y, mstory1_scene1KoopaPos.z);
    Hu3DModelPosSet(obj->model[2], mstory1_scene1KoopaPos.x, -5.0f, mstory1_scene1KoopaPos.z);
    omPrcSetDestructor(0, mstory1_Scene1KoopaDestroy);
    mstory1_scene1WorkTbl[3].func = mstory1_Scene1ObjIdle;
    while (1) {
        mstory1_scene1WorkTbl[3].func(obj);
        HuPrcVSleep();
    }
}

void mstory1_Scene1KoopaDestroy(void) {
}

void mstory1_Scene1KoopaExec(omObjData *obj) {
    s16 model;

    HuPrcSleep(60);
    model = obj->model[1];
    Hu3DModelAttrSet(model, 4, 0);
    Hu3DModelAttrSet(obj->model[2], 4, 0);
    HuAudSeqPlay(0x21);
    HuAudFXPlay(0x29D);
    mstory1_WinOpen();
    mstory1_WinMesExec(mstory1_PlayerChrCheck(3) == 0 ? 0x5A27 : 0x5B18);
    mstory1_WinClose();
    mstory1_scene1WorkTbl[4].func = mstory1_Scene1KoopaJrAExec;
    mstory1_scene1WorkTbl[5].func = mstory1_Scene1KoopaJrBExec;
    mstory1_ObjPosMoveV(obj, &mstory1_scene1KoopaDestPos0, 60);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory1_ObjRotMoveV(obj, &mstory1_scene1KoopaDestRot0, 20);
    HuAudFXPlay(0x29C);
    mstory1_WinOpen();
    mstory1_WinMesExec(mstory1_PlayerChrCheck(3) == 0 ? 0x5A28 : 0x5B19);
    mstory1_WinClose();
    mstory1_scene1WorkTbl[3].unk_08 |= 1;
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(30);
    while (!(mstory1_scene1WorkTbl[4].unk_08 & 1)) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory1_ObjRotMoveV(obj, &mstory1_scene1KoopaDestRot1, 10);
    mstory1_scene1WorkTbl[3].unk_08 |= 2;
    while (!(mstory1_scene1WorkTbl[5].unk_08 & 1)) {
        HuPrcVSleep();
    }
    mstory1_ObjRotMoveV(obj, &mstory1_scene1KoopaDestRot2, 10);
    HuPrcSleep(20);
    mstory1_ObjRotMoveV(obj, &mstory1_scene1KoopaDestRot0, 5);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    mstory1_MotionEndWait(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    HuAudFXPlay(0x29E);
    mstory1_WinOpen();
    mstory1_WinMesExec(mstory1_PlayerChrCheck(3) == 0 ? 0x5A2B : 0x5B1C);
    mstory1_WinClose();
    mstory1_scene1WorkTbl[3].unk_08 |= 4;
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(40);
    mstory1_scene1WorkTbl[3].unk_08 |= 8;
    HuPrcSleep(20);
    HuAudFXPlay(0x2A0);
    mstory1_WinOpen();
    mstory1_WinMesExec(mstory1_PlayerChrCheck(3) == 0 ? 0x5A2C : 0x5B1D);
    mstory1_WinClose();
    HuPrcSleep(40);
    mstory1_SceneEnd();
    mstory1_scene1WorkTbl[3].func = mstory1_Scene1ObjIdle;
}

void mstory1_Scene1KoopaJrAProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    mstory1_scene1WorkTbl[4].obj = obj;
    mstory1_scene1WorkTbl[4].unk_08 = 0;
    mstory1_scene1WorkTbl[4].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(mstory1_scene1ShadowMdl);
    omObjMotionRead(obj, 0, 0xA00EF);
    omObjMotionRead(obj, 1, 0xA00F1);
    omObjMotionRead(obj, 2, 0xA00F0);
    Hu3DMotionModelSet(obj->model[1], obj->motion[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DModelAttrSet(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    mstory1_scene1KoopaJrAPos = mstory1_scene1KoopaJrAStartPos;
    Hu3DModelPosSet(obj->model[1], mstory1_scene1KoopaJrAPos.x, mstory1_scene1KoopaJrAPos.y, mstory1_scene1KoopaJrAPos.z);
    Hu3DModelPosSet(obj->model[2], mstory1_scene1KoopaJrAPos.x, -5.0f, mstory1_scene1KoopaJrAPos.z);
    omPrcSetDestructor(0, mstory1_Scene1KoopaJrADestroy);
    mstory1_scene1WorkTbl[4].func = mstory1_Scene1ObjIdle;
    while (1) {
        mstory1_scene1WorkTbl[4].func(obj);
        HuPrcVSleep();
    }
}

void mstory1_Scene1KoopaJrADestroy(void) {
}

void mstory1_Scene1KoopaJrAExec(omObjData *obj) {
    s16 model = obj->model[1];

    Hu3DModelAttrSet(model, 4, 0);
    Hu3DModelAttrSet(obj->model[2], 4, 0);
    mstory1_ObjPosMoveV(obj, &mstory1_scene1KoopaJrADestPos0, 30);
    mstory1_ObjRotMoveV(obj, &mstory1_scene1KoopaJrADestRot0, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    while (!(mstory1_scene1WorkTbl[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
    mstory1_MotionEndWait(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
    mstory1_MotionEndWait(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory1_ObjRotMoveV(obj, &mstory1_scene1KoopaJrADestRot2, 5);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory1_ObjRotMoveV(obj, &mstory1_scene1KoopaJrADestRot1, 5);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory1_ObjRotMoveV(obj, &mstory1_scene1KoopaJrADestRot0, 5);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory1_ObjRotMoveV(obj, &mstory1_scene1KoopaJrADestRot3, 10);
    HuAudFXPlay(0x2A0);
    mstory1_WinOpen();
    mstory1_WinMesExec(mstory1_PlayerChrCheck(3) == 0 ? 0x5A29 : 0x5B1A);
    mstory1_WinClose();
    mstory1_scene1WorkTbl[4].unk_08 |= 1;
    while (!(mstory1_scene1WorkTbl[3].unk_08 & 8)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
        mstory1_MotionEndWait(model);
    }
}

void mstory1_Scene1KoopaJrBProc(void) {
    omObjData *obj;
    omObjData *src;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    mstory1_scene1WorkTbl[5].obj = obj;
    mstory1_scene1WorkTbl[5].unk_08 = 0;
    mstory1_scene1WorkTbl[5].unk_0C = 0;
    src = mstory1_scene1WorkTbl[4].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    obj->model[2] = Hu3DModelLink(mstory1_scene1ShadowMdl);
    Hu3DMotionModelSet(obj->model[1], src->motion[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DModelAttrSet(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    mstory1_scene1KoopaJrBPos = mstory1_scene1KoopaJrBStartPos;
    Hu3DModelPosSet(obj->model[1], mstory1_scene1KoopaJrBPos.x, mstory1_scene1KoopaJrBPos.y, mstory1_scene1KoopaJrBPos.z);
    Hu3DModelPosSet(obj->model[2], mstory1_scene1KoopaJrBPos.x, -5.0f, mstory1_scene1KoopaJrBPos.z);
    omPrcSetDestructor(0, mstory1_Scene1KoopaJrBDestroy);
    mstory1_scene1WorkTbl[5].func = mstory1_Scene1ObjIdle;
    while (1) {
        mstory1_scene1WorkTbl[5].func(obj);
        HuPrcVSleep();
    }
}

void mstory1_Scene1KoopaJrBExec(omObjData *obj) {
    omObjData *src = mstory1_scene1WorkTbl[4].obj;
    s16 model = obj->model[1];

    Hu3DModelAttrSet(model, 4, 0);
    Hu3DModelAttrSet(obj->model[2], 4, 0);
    mstory1_ObjPosMoveV(obj, &mstory1_scene1KoopaJrBDestPos0, 30);
    mstory1_ObjRotMoveV(obj, &mstory1_scene1KoopaJrBDestRot0, 10);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[0]].motId, 0, 10, 2);
    while (!(mstory1_scene1WorkTbl[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[2]].motId, 0, 10, 0);
    mstory1_MotionEndWait(model);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[2]].motId, 0, 10, 0);
    mstory1_MotionEndWait(model);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[1]].motId, 0, 10, 2);
    mstory1_ObjRotMoveV(obj, &mstory1_scene1KoopaJrBDestRot1, 5);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[1]].motId, 0, 10, 2);
    mstory1_ObjRotMoveV(obj, &mstory1_scene1KoopaJrBDestRot2, 5);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[1]].motId, 0, 10, 2);
    mstory1_ObjRotMoveV(obj, &mstory1_scene1KoopaJrBDestRot0, 5);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[0]].motId, 0, 10, 2);
    while (!(mstory1_scene1WorkTbl[3].unk_08 & 2)) {
        HuPrcVSleep();
    }
    mstory1_ObjRotMoveV(obj, &mstory1_scene1KoopaJrBDestRot3, 10);
    mstory1_WinOpen();
    mstory1_WinMesExec(mstory1_PlayerChrCheck(3) == 0 ? 0x5A2A : 0x5B1B);
    mstory1_WinClose();
    mstory1_scene1WorkTbl[5].unk_08 |= 1;
    while (!(mstory1_scene1WorkTbl[3].unk_08 & 8)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        Hu3DMotionShiftSet(model, Hu3DData[src->motion[2]].motId, 0, 10, 0);
        mstory1_MotionEndWait(model);
    }
}

void mstory1_Scene1KoopaJrBDestroy(void) {
}

void mstory1_Scene1StarProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    mstory1_scene1WorkTbl[6].obj = obj;
    mstory1_scene1WorkTbl[6].unk_08 = 0;
    mstory1_scene1WorkTbl[6].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    AuraCreate(obj->model[1]);
    omObjMotionRead(obj, 0, 0xA0123);
    omObjMotionRead(obj, 1, 0xA0125);
    omObjMotionRead(obj, 2, 0xA0127);
    obj->model[2] = Hu3DModelLink(mstory1_scene1ShadowMdl);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    mstory1_scene1StarPos = mstory1_scene1StarStartPos;
    Hu3DModelPosSet(obj->model[1], mstory1_scene1StarPos.x, mstory1_scene1StarPos.y, mstory1_scene1StarPos.z);
    Hu3DModelPosSet(obj->model[2], mstory1_scene1StarPos.x, -5.0f, mstory1_scene1StarPos.z);
    omPrcSetDestructor(0, mstory1_Scene1StarDestroy);
    mstory1_scene1WorkTbl[6].func = mstory1_Scene1ObjIdle;
    mstory1_scene1StarFloatF = 1;
    while (1) {
        mstory1_scene1WorkTbl[6].func(obj);
        HuPrcVSleep();
    }
}

void mstory1_Scene1StarDestroy(void) {
}

const Vec mstory1_scene1KoopaDestPos0 = { 0.0f, 0.0f, 480.0f };
const Vec mstory1_scene1UnusedPos3 = { 800.0f, 0.0f, 480.0f }; /* Unreferenced. */

const Vec mstory1_scene1KoopaDestRot0 = { 0.0f, 0.0f, 0.0f };
const Vec mstory1_scene1UnusedRot3 = { 0.0f, 90.0f, 0.0f };  /* Unreferenced. */
const Vec mstory1_scene1UnusedRot4 = { 0.0f, -90.0f, 0.0f }; /* Unreferenced. */

const Vec mstory1_scene1KoopaDestRot1 = { 0.0f, -40.0f, 0.0f };

const Vec mstory1_scene1KoopaDestRot2 = { 0.0f, 40.0f, 0.0f };

const Vec mstory1_scene1KoopaJrADestPos0 = { -300.0f, 0.0f, 350.0f };
const Vec mstory1_scene1UnusedPos4 = { 500.0f, 0.0f, 350.0f }; /* Unreferenced. */

const Vec mstory1_scene1KoopaJrADestRot0 = { 0.0f, 0.0f, 0.0f };

const Vec mstory1_scene1KoopaJrADestRot1 = { 0.0f, 90.0f, 0.0f };

const Vec mstory1_scene1KoopaJrADestRot2 = { 0.0f, -90.0f, 0.0f };

const Vec mstory1_scene1KoopaJrADestRot3 = { 0.0f, 30.0f, 0.0f };

const Vec mstory1_scene1KoopaJrBDestPos0 = { 300.0f, 0.0f, 350.0f };
const Vec mstory1_scene1UnusedPos5 = { 1100.0f, 0.0f, 350.0f }; /* Unreferenced. */

const Vec mstory1_scene1KoopaJrBDestRot0 = { 0.0f, 0.0f, 0.0f };

const Vec mstory1_scene1KoopaJrBDestRot1 = { 0.0f, 90.0f, 0.0f };

const Vec mstory1_scene1KoopaJrBDestRot2 = { 0.0f, -90.0f, 0.0f };

const Vec mstory1_scene1KoopaJrBDestRot3 = { 0.0f, -30.0f, 0.0f };
const Vec mstory1_scene1UnusedPos6 = { 166.66666f, 0.0f, 150.0f }; /* Unreferenced. */

const Vec mstory1_scene1StarDestPos2 = { 700.0f, 0.0f, 150.0f };
const Vec mstory1_scene1UnusedPos7 = { 216.66666f, 0.0f, 150.0f };

void mstory1_Scene1StarExit(omObjData *obj) {
    mstory1_ObjRotMoveV(obj, &mstory1_scene1StarDestRot5, 10);
    mstory1_ObjPosMoveV(obj, &mstory1_scene1StarDestPos2, 50);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    mstory1_scene1WorkTbl[6].func = mstory1_Scene1ObjIdle;
}

void mstory1_Scene1StarTurn(omObjData *obj) {
    mstory1_ObjRotMoveV(obj, &mstory1_scene1StarDestRot6, 20);
    mstory1_scene1WorkTbl[6].func = mstory1_Scene1ObjIdle;
}

void mstory1_Scene1StarFloatProc(void) {
    f32 angle = 0.0f;
    Vec pos;
    f32 ofs;
    s16 model;

    if (mstory1_scene1StarFloatF != 0) {
        model = mstory1_scene1WorkTbl[6].obj->model[1];
        pos.y = Hu3DData[model].pos.y;
        while (TRUE) {
            pos.x = Hu3DData[model].pos.x;
            pos.z = Hu3DData[model].pos.z;
            ofs = sindf(angle) * 25.0f + 25.0f;
            angle += 2.0f;
            angle = (angle >= 360.0f) ? angle - 360.0f : angle;
            Hu3DModelPosSet(model, pos.x, ofs + pos.y, pos.z);
            HuPrcVSleep();
        }
    }
}

void mstory1_Scene1StampProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 8, 0, -1, NULL);
    mstory1_scene1WorkTbl[7].obj = obj;
    mstory1_scene1WorkTbl[7].unk_08 = 0;
    mstory1_scene1WorkTbl[7].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(mstory1_scene1StampMdlTbl[1], 0x20299);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    mstory1_scene1StampPos = mstory1_scene1StampStartPos;
    Hu3DModelPosSet(obj->model[1], mstory1_scene1StampPos.x, mstory1_scene1StampPos.y, mstory1_scene1StampPos.z);
    mstory1_scene1StampEff = EffectCreate(0xB0004, 0x6A9);
    EffectParamSet(mstory1_scene1StampEff, 4.0f, 20.0f, 4.0f);
    EffectRangeSet(mstory1_scene1StampEff, 60.0f);
    Hu3DParticleAttrSet(mstory1_scene1StampEff, 1, 0);
    Hu3DModelAttrSet(mstory1_scene1StampEff, 4, 4);
    omPrcSetDestructor(0, mstory1_Scene1StampDestroy);
    mstory1_scene1WorkTbl[7].func = mstory1_Scene1ObjIdle;
    while (1) {
        mstory1_scene1WorkTbl[7].func(obj);
        HuPrcVSleep();
    }
}

void mstory1_Scene1StampDestroy(void) {
}

void mstory1_Scene1StampFlyExec(omObjData *obj) {
    Vec pos;
    MstoryPath *paths[2];
    omObjData *target;
    f32 rotY;
    s32 i;

    paths[0] = mstory1_Scene1PathCreate(mstory1_scene1StampPathA, 0);
    paths[1] = mstory1_Scene1PathCreate(mstory1_scene1StampPathB, 0);
    Hu3DModelAttrSet(obj->model[1], 4, 0);
    Hu3DModelAttrSet(mstory1_scene1StampEff, 4, 0);
    Hu3DParticleAttrSet(mstory1_scene1StampEff, 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 50; i++) {
        mstory1_Scene1PathPosGet(paths[0], (i * 0.02f) * (i * 0.02f), &pos);
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        EffectPosSet(mstory1_scene1StampEff, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    target = mstory1_scene1WorkTbl[6].obj;
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[2]].motId, 0, 10, 0);
    HuPrcSleep(20);
    mstory1_scene1WorkTbl[7].unk_08 |= 2;
    HuAudFXPlay(0x218);
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[0]].motId, 0, 10, 2);
    rotY = 0.0f;
    for (i = 0; i < 120; i++) {
        mstory1_Scene1PathPosGet(paths[1], (i * 0.008333334f) * (i * 0.008333334f), &pos);
        rotY -= 24.0f;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        Hu3DModelRotSet(obj->model[1], 0.0f, rotY, 0.0f);
        EffectPosSet(mstory1_scene1StampEff, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DModelAttrSet(mstory1_scene1StampEff, 4, 4);
    HuAudFXPlay(0x21A);
    mstory1_Scene1PathKill(paths[0]);
    mstory1_Scene1PathKill(paths[1]);
    mstory1_scene1WorkTbl[7].unk_08 = 1;
    mstory1_scene1WorkTbl[7].func = mstory1_Scene1ObjIdle;
}

void mstory1_Scene1ObjTargetFace(omObjData *obj, omObjData *target) {
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

const Vec mstory1_scene1StarDestRot5 = { 0.0f, 90.0f, 0.0f };
const Vec mstory1_scene1UnusedRot5 = { 0.0f, -90.0f, 0.0f }; /* Unreferenced. */

const Vec mstory1_scene1StarDestRot6 = { 0.0f, 10.0f, 0.0f };

const s32 mstory1_scene1StampMdlTbl[7] = { 0x1D0003, 0x1D0004, 0x1D0005, 0x1D0006, 0x1D0007, 0x1D0008, 0x1D0009 };

void mstory1_Scene1ObjSeLoopStart(s32 index, s32 seNo) {
    if (mstory1_scene1WorkTbl[index].unk_0C == 0) {
        mstory1_scene1WorkTbl[index].unk_0C = 1;
        mstory1_scene1WorkTbl[index].unk_10 = seNo;
        switch (index) {
            case 0:
                mstory1_scene1WorkTbl[index].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                break;
            case 2:
                if (mstory1_PlayerChrCheck(3) == 0) {
                    mstory1_scene1WorkTbl[index].unk_14 = CharFXPlay(seNo, 3);
                } else {
                    mstory1_scene1WorkTbl[index].unk_14 = CharFXPlay(seNo, 1);
                }
                break;
            case 1:
            case 3:
            case 4:
            case 5:
                break;
        }
    }
}

void mstory1_Scene1ObjSeLoopStop(s32 index) {
    if (mstory1_scene1WorkTbl[index].unk_0C == 1) {
        mstory1_scene1WorkTbl[index].unk_0C = 0;
        switch (index) {
            case 0:
            case 2:
                HuAudFXStop((s16)mstory1_scene1WorkTbl[index].unk_14);
                break;
            case 1:
            case 3:
            case 4:
            case 5:
                break;
        }
    }
}

void mstory1_Scene1ObjSeLoopProc(void) {
    s32 i;
    s32 seNo;

    while (TRUE) {
        for (i = 0; i < 8; i++) {
            if (mstory1_scene1WorkTbl[i].unk_0C == 1 && Hu3DData[mstory1_scene1WorkTbl[i].obj->model[1]].motTime == 0.0f) {
                seNo = mstory1_scene1WorkTbl[i].unk_10;
                switch (i) {
                    case 0:
                        mstory1_scene1WorkTbl[i].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                        break;
                    case 2:
                        if (mstory1_PlayerChrCheck(3) == 0) {
                            mstory1_scene1WorkTbl[i].unk_14 = CharFXPlay(seNo, 3);
                        } else {
                            mstory1_scene1WorkTbl[i].unk_14 = CharFXPlay(seNo, 1);
                        }
                        break;
                    case 1:
                    case 3:
                    case 4:
                    case 5:
                        break;
                }
            }
        }
        HuPrcVSleep();
    }
}
