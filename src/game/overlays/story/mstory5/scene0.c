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

extern const Vec mstory5_scene0KoopaJrBStartPos;
extern const Vec mstory5_scene0PlayerDestRot0;
extern const Vec mstory5_scene0PlayerDestRot1;
extern const Vec mstory5_scene0PlayerDestRot2;
extern const Vec mstory5_scene0PlayerDestRot3;
extern const Vec mstory5_scene0PlayerDestRot4;
extern const Vec mstory5_scene0PlayerDestRot5;
extern const Vec mstory5_scene0TumbleDestPos2;
extern const Vec mstory5_scene0TumbleDestPos3;
extern const Vec mstory5_scene0TumbleDestPos4;
extern const Vec mstory5_scene0TumbleDestRot7;
extern const Vec mstory5_scene0StarDestRot9;
extern void (*const mstory5_sceneCreateTbl[])(void);
extern StoryObjWork mstory5_scene0WorkTbl[8];
extern StoryObjWork mstory5_scene0FireWork;
extern Vec mstory5_scene0KoopaPos;
extern Mstory5FireParticle mstory5_scene0FireParticleTbl[16];
extern const Vec mstory5_scene0KoopaStartPos;
extern Vec mstory5_scene0KoopaJrAPos;
extern const Vec mstory5_scene0KoopaJrAStartPos;
extern Vec mstory5_scene0KoopaJrBPos;
extern Vec mstory5_scene0RivalPos;
extern const Vec mstory5_scene0RivalStartPos;
extern s16 mstory5_scene0ShadowMdl;
extern s16 mstory5_scene0TumbleFaceAnim2;
extern s16 mstory5_scene0TumbleFaceSlot;
extern s32 mstory5_scene0TumbleFaceAnimTbl[3];
extern s16 mstory5_scene0TumbleFaceAnim0;
extern Vec mstory5_scene0TumblePos;
extern const Vec mstory5_scene0TumbleStartPos;
extern const Vec mstory5_scene0StarDestPos4;
extern const Vec mstory5_scene0StarDestPos5;
extern const Vec mstory5_scene0StarDestRot5;
extern const Vec mstory5_scene0StarDestRot6;
extern const Vec mstory5_scene0StarDestRot7;
extern const Vec mstory5_scene0StarDestRot8;
extern Vec mstory5_scene0StampPos;
extern const Vec mstory5_scene0StampStartPos;
extern s16 mstory5_scene0StampEff;
extern const s32 mstory5_scene0StampMdlTbl[];
extern Vec mstory5_scene0StarPos;
extern const Vec mstory5_scene0StarStartPos;
extern const Vec mstory5_scene0KoopaJrADestPos0;
extern const Vec mstory5_scene0KoopaJrBDestPos0;
extern const Vec mstory5_scene0KoopaDestPos0;
extern const Vec mstory5_scene0KoopaDestPos1;
extern const Vec mstory5_scene0KoopaDestPos2;
extern const Vec mstory5_scene0KoopaDestRot0;
extern const Vec mstory5_scene0KoopaDestRot1;
extern const Vec mstory5_scene0KoopaDestRot2;
extern const Vec mstory5_scene0TumbleDestPos5;
extern const Vec mstory5_scene0KoopaJrBDestPos1;
extern const Vec mstory5_scene0KoopaJrBDestRot0;
extern const Vec mstory5_scene0KoopaJrBDestRot1;
extern const Vec mstory5_scene0KoopaJrADestPos1;
extern const Vec mstory5_scene0KoopaJrADestRot0;
extern const Vec mstory5_scene0KoopaJrADestRot1;
extern const Vec mstory5_scene0TumbleDestRot0;
extern const Vec mstory5_scene0TumbleDestRot2;
extern const Vec mstory5_scene0TumbleDestRot3;
extern const Vec mstory5_scene0TumbleDestRot4;
extern const Vec mstory5_scene0TumbleDestRot5;
extern const Vec mstory5_scene0TumbleDestRot6;
extern const Vec mstory5_scene0TumbleDestPos0;
extern const Vec mstory5_scene0TumbleDestPos1;
extern const Vec mstory5_scene0StarDestRot3;
extern const Vec mstory5_scene0StarDestRot4;
extern s16 mstory5_scene0TumbleFaceAnim1;
extern s32 omCharModelNoTbl[][6];
extern Vec mstory5_scene0PlayerPos;
extern const Vec mstory5_scene0PlayerStartPos;
extern const s32 mstory5_scene0PlayerMot5Tbl[];
extern const s32 mstory5_scene0PlayerMot6Tbl[];
extern const s32 mstory5_scene0PlayerMot7Tbl[];
extern const s32 mstory5_scene0PlayerMot9Tbl[];
extern s16 mstory5_scene0PlayerFaceAnimTbl[4];

s32 mstory5_scene0FireEmitCnt = 3;
s32 mstory5_scene0StarFloatF = 0;
Vec mstory5_scene0StampPathA[4] = {
    { 0.0f, 200.0f, 100.0f },
    { -200.0f, 100.0f, -100.0f },
    { -100.0f, 300.0f, 300.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};
Vec mstory5_scene0StampPathB[6] = {
    { -100.0f, 300.0f, 300.0f },
    { -200.0f, 200.0f, 100.0f },
    { 0.0f, 300.0f, -100.0f },
    { 400.0f, 400.0f, 200.0f },
    { -50.0f, 120.0f, 450.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};

void mstory5_Scene0PathPosGet(MstoryPath *path, f32 time, Vec *result);
void mstory5_ObjPosMoveEx(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void mstory5_ObjRotMoveV(omObjData *obj, const Vec *pos, s32 frames);
void mstory5_ObjRotMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void mstory5_MotionEndWait(s16 model);
void mstory5_Scene0ObjIdle(omObjData *obj);
void mstory5_Scene0KoopaJrAExec(omObjData *obj);
void mstory5_Scene0KoopaJrBExec(omObjData *obj);
void mstory5_Scene0KoopaDestroy(void);
void mstory5_Scene0KoopaJrADestroy(void);
void mstory5_Scene0RivalDestroy(void);
void mstory5_Scene0RivalExec(omObjData *obj);
void mstory5_Scene0TumbleExec(omObjData *obj);
void mstory5_Scene0PlayerProc(void);
void mstory5_Scene0TumbleProc(void);
void mstory5_Scene0TumbleDestroy(void);
void mstory5_Scene0RivalProc(void);
void mstory5_Scene0KoopaProc(void);
void mstory5_Scene0KoopaJrAProc(void);
void mstory5_Scene0KoopaJrBProc(void);
void mstory5_Scene0PlayerStampExec(omObjData *obj);
void mstory5_Scene0TumbleExit(omObjData *obj);
void mstory5_Scene0TumbleHop(omObjData *obj);
void mstory5_Scene0KoopaExec(omObjData *obj);
void mstory5_Scene0StarExec(omObjData *obj);
void mstory5_Scene0ObjSeLoopStart(s32 index, s32 seNo);
void mstory5_Scene0ObjSeLoopStop(s32 index);
void mstory5_Scene0StarTurn(omObjData *obj);
void mstory5_Scene0StampFlyExec(omObjData *obj);
void mstory5_Scene0KoopaJrBDestroy(void);
void mstory5_Scene0StarProc(void);
void mstory5_Scene0StarFloatProc(void);
void mstory5_Scene0StampProc(void);
void mstory5_Scene0FireProc(void);
void mstory5_Scene0ObjSeLoopProc(void);
void mstory5_Scene0StarDestroy(void);
void mstory5_Scene0StampDestroy(void);
void mstory5_Scene0PlayerDestroy(void);
void mstory5_SceneEnd(void);
void mstory5_StampCardStart(s32 arg0);
s32 mstory5_StampCardDoneCheck(void);
void mstory5_HmfAnimSet(s16 model, s16 animSlot, s16 anim);
void mstory5_WinCreate(void);
void mstory5_WinOpen(void);
void mstory5_WinClose(void);
void mstory5_WinMesExec(s32 mess);
s32 mstory5_PlayerChrCheck(s32 character);
void mstory5_ObjPosMoveV(omObjData *obj, const Vec *pos, s32 frames);

MstoryPath *mstory5_Scene0PathCreate(Vec *points, s32 flags) {
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

void mstory5_Scene0PathPosGet(MstoryPath *path, f32 time, Vec *result) {
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

void mstory5_Scene0PathKill(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void mstory5_Scene0Create(void) {
    mstory5_WinCreate();
    mstory5_scene0ShadowMdl = Hu3DModelRead(9, 0x2B9);
    omAddPrcObj(mstory5_Scene0PlayerProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory5_Scene0TumbleProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory5_Scene0RivalProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory5_Scene0KoopaProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory5_Scene0KoopaJrAProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory5_Scene0KoopaJrBProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory5_Scene0StarProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory5_Scene0StarFloatProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory5_Scene0StampProc, 0x384, 0x800, 0);
    omAddPrcObj(mstory5_Scene0FireProc, 0x384, 0x800, 0);
    omAddPrcObj(mstory5_Scene0ObjSeLoopProc, 0x1001, 0x800, 0);
    HuPrcVSleep();
    Hu3DModelAttrSet(mstory5_scene0ShadowMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void mstory5_Scene0ObjIdle(omObjData *obj) {
}

void mstory5_Scene0PlayerProc(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 6, 16, -1, NULL);
    mstory5_scene0WorkTbl[0].obj = obj;
    mstory5_scene0WorkTbl[0].unk_08 = 0;
    mstory5_scene0WorkTbl[0].unk_0C = 0;
    chr = GwStory.unk1;
    obj->model[1] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory5_scene0ShadowMdl);
    if (GwStory.unk1 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    obj->model[3] = Hu3DModelRead(0x1D000A, 0x2B9);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->model[4] = Hu3DModelRead(0x83, 0x2B9);
    Hu3DModelAttrSet(obj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 0x9C));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 1));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chr, 0x21));
    omObjMotionRead(obj, 5, mstory5_scene0PlayerMot5Tbl[chr]);
    omObjMotionRead(obj, 6, mstory5_scene0PlayerMot6Tbl[chr]);
    omObjMotionRead(obj, 7, mstory5_scene0PlayerMot7Tbl[chr]);
    omObjMotionRead(obj, 8, CharMotionDataNumGet(chr, 0x33));
    omObjMotionRead(obj, 9, mstory5_scene0PlayerMot9Tbl[chr]);
    omObjMotionRead(obj, 10, CharMotionDataNumGet(chr, 0x9B));
    mstory5_scene0PlayerFaceAnimTbl[0] = CharAnimCreate(obj->model[1], 2, chr, CharMotionDataNumGet(chr, 0xA4));
    mstory5_scene0PlayerFaceAnimTbl[1] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xAA));
    mstory5_scene0PlayerFaceAnimTbl[2] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA5));
    mstory5_scene0PlayerFaceAnimTbl[3] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA9));
    Hu3DModelDynamicFree(obj->model[1]);
    CharAnimSet(obj->model[1], 2, GwStory.unk1, mstory5_scene0PlayerFaceAnimTbl[0]);
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    mstory5_scene0PlayerPos = mstory5_scene0PlayerStartPos;
    Hu3DModelPosSet(obj->model[1], mstory5_scene0PlayerPos.x, mstory5_scene0PlayerPos.y, mstory5_scene0PlayerPos.z);
    Hu3DModelPosSet(obj->model[2], mstory5_scene0PlayerPos.x, -5.0f, mstory5_scene0PlayerPos.z);
    Hu3DModelPosSet(obj->model[4], mstory5_scene0PlayerPos.x, mstory5_scene0PlayerPos.y, mstory5_scene0PlayerPos.z);
    omPrcSetDestructor(0, mstory5_Scene0PlayerDestroy);
    mstory5_scene0WorkTbl[0].func = mstory5_Scene0ObjIdle;
    while (TRUE) {
        mstory5_scene0WorkTbl[0].func(obj);
        HuPrcVSleep();
    }
}

void mstory5_Scene0PlayerDestroy(void) {
}

const Vec mstory5_scene0PlayerStartPos = { -120.0f, 0.0f, 480.0f };

const Vec mstory5_scene0TumbleStartPos = { 38.0f, 100.0f, 214.0f };

const Vec mstory5_scene0RivalStartPos = { 150.0f, 0.0f, 384.0f };

const Vec mstory5_scene0KoopaStartPos = { 800.0f, 0.0f, 380.0f };

const Vec mstory5_scene0KoopaJrAStartPos = { -700.0f, 0.0f, 300.0f };

const Vec mstory5_scene0KoopaJrBStartPos = { -800.0f, 0.0f, 500.0f };

const Vec mstory5_scene0StarStartPos = { 0.0f, 200.0f, 150.0f };

const Vec mstory5_scene0StampStartPos = { 0.0f, 200.0f, 100.0f };

const s32 mstory5_scene0PlayerMot5Tbl[8] = { 0x1D003E, 0x1D0048, 0x1D0052, 0x1D005B, 0x1D0065, 0x1D006E, 0x1D003E, 0x1D003E };

const s32 mstory5_scene0PlayerMot6Tbl[8] = { 0x1D0040, 0x1D004B, 0x1D0054, 0x1D005D, 0x1D0067, 0x1D0070, 0x1D0040, 0x1D0040 };

const s32 mstory5_scene0PlayerMot7Tbl[8] = { 0x1D0041, 0x1D004C, 0x1D0055, 0x1D005E, 0x1D0068, 0x1D0071, 0x1D0041, 0x1D0041 };

const s32 mstory5_scene0PlayerMot9Tbl[8] = { 0x1D0043, 0x1D004E, 0x1D0057, 0x1D0060, 0x1D006A, 0x1D0073, 0x1D0043, 0x1D0043 };

const Vec mstory5_scene0PlayerDestRot0 = { 0.0f, 0.0f, 0.0f };

const Vec mstory5_scene0PlayerDestRot1 = { 0.0f, 180.0f, 0.0f };

const Vec mstory5_scene0PlayerDestRot2 = { 0.0f, 90.0f, 0.0f };
const Vec mstory5_scene0UnusedRot0 = { 0.0f, -90.0f, 0.0f }; /* Unreferenced. */

const Vec mstory5_scene0PlayerDestRot3 = { 0.0f, 135.0f, 0.0f };

const Vec mstory5_scene0PlayerDestPos0 = { 230.0f, 0.0f, 480.0f };
const Vec mstory5_scene0PlayerDestPos1 = { 680.0f, 0.0f, 480.0f };
const Vec mstory5_scene0PlayerDestPos2 = { -70.0f, 0.0f, 480.0f };
const Vec mstory5_scene0StarDestPos0 = { -100.0f, 0.0f, 350.0f };
const Vec mstory5_scene0StarDestPos1 = { -100.0f, 0.0f, 150.0f };
const Vec mstory5_scene0StarDestRot0 = { 0.0f, 20.0f, 0.0f };
const Vec mstory5_scene0StarDestRot1 = { 0.0f, 0.0f, 0.0f };
const Vec mstory5_scene0StarDestRot2 = { 0.0f, -26.565f, 0.0f };

const char mstory5_scene0ItemHookName[] = "item_hook";

void mstory5_Scene0PlayerStampExec(omObjData *obj) {
    s16 model;
    HmfMotionNode *node;
    omObjData *obj6;
    s32 fx;
    s32 i;
    f32 scale;
    f32 time;

    HuPrcSleep(20);
    model = obj->model[1];
    HuPrcSleep(50);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory5_ObjRotMove(obj, 0.0f, 110.0f, 0.0f, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    HuPrcSleep(10);
    Hu3DModelAttrSet(obj->model[3], 0x4000, 0x4000);
    Hu3DModelHookSet(obj->model[3], model, mstory5_scene0ItemHookName);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    mstory5_MotionEndWait(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[5]].motId, 0, 10, 0);
    mstory5_MotionEndWait(model);
    while (!(mstory5_scene0WorkTbl[7].unk_08 & 1)) {
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(mstory5_scene0WorkTbl[7].obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mstory5_scene0StampEff, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DMotionNoMotSet(model, Hu3DData[model].motId, mstory5_scene0ItemHookName, 0x1B, 0x45);
    Hu3DMotionNoMotSet(model, Hu3DData[model].motId, mstory5_scene0ItemHookName, 0x1B, 0x46);
    Hu3DMotionNoMotSet(model, Hu3DData[model].motId, mstory5_scene0ItemHookName, 0x1B, 0x47);
    node = Hu3DModelObjPtrGet(model, mstory5_scene0ItemHookName);
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
    Hu3DMotionNoMotReset(model, Hu3DData[model].motId, mstory5_scene0ItemHookName, 0x1B, 0x47);
    Hu3DMotionNoMotReset(model, Hu3DData[model].motId, mstory5_scene0ItemHookName, 0x1B, 0x46);
    Hu3DMotionNoMotReset(model, Hu3DData[model].motId, mstory5_scene0ItemHookName, 0x1B, 0x45);
    mstory5_StampCardStart(3);
    while (mstory5_StampCardDoneCheck() == 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(2) == 0 ? 0x5A3E : 0x5B31);
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
    Hu3DModelAttrSet(obj->model[3], 0x4000, 0);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    HuAudSeqFadeOut(20);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0PlayerDestRot0, 10);
    HuAudSeqPlay(0x72);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
    CharAnimSet(obj->model[1], 2, GwStory.unk1, mstory5_scene0PlayerFaceAnimTbl[2]);
    mstory5_MotionEndWait(model);
    fx = CharFXPlay(0x262, GwStory.unk1);
    HuPrcSleep(30);
    obj6 = mstory5_scene0WorkTbl[6].obj;
    mstory5_ObjRotMoveV(obj6, &mstory5_scene0StarDestRot2, 3);
    mstory5_ObjPosMoveV(obj6, &mstory5_scene0StarDestPos0, 5);
    mstory5_ObjRotMoveV(obj6, &mstory5_scene0StarDestRot0, 3);
    mstory5_scene0WorkTbl[1].func = mstory5_Scene0TumbleHop;
    HuAudFXPlay(0x219);
    HuAudFXStop(fx);
    Hu3DModelAttrSet(obj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    CharAnimSet(obj->model[1], 2, GwStory.unk1, mstory5_scene0PlayerFaceAnimTbl[3]);
    mstory5_ObjRotMoveV(obj6, &mstory5_scene0StarDestRot1, 3);
    mstory5_ObjPosMoveEx(obj6, &mstory5_scene0StarDestPos1, 10, 0);
    mstory5_MotionEndWait(model);
    HuAudSeqPlay(0x26);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0PlayerDestRot1, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    CharAnimSet(obj->model[1], 2, GwStory.unk1, mstory5_scene0PlayerFaceAnimTbl[0]);
    HuAudFXPlay(0x159);
    Hu3DMotionShiftSet(mstory5_scene0WorkTbl[6].obj->model[1], Hu3DData[mstory5_scene0WorkTbl[6].obj->motion[1]].motId, 0, 10, 2);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(2) == 0 ? 0x5A3F : 0x5B32);
    mstory5_WinClose();
    Hu3DMotionShiftSet(mstory5_scene0WorkTbl[6].obj->model[1], Hu3DData[mstory5_scene0WorkTbl[6].obj->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[8]].motId, 0, 10, 0);
    mstory5_MotionEndWait(model);
    mstory5_scene0WorkTbl[3].func = mstory5_Scene0KoopaExec;
    mstory5_scene0WorkTbl[6].func = mstory5_Scene0StarExec;
    mstory5_scene0WorkTbl[1].func = mstory5_Scene0TumbleExit;
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 2);
    mstory5_Scene0ObjSeLoopStart(0, 0x1F);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0PlayerDestRot2, 20);
    mstory5_ObjPosMoveV(obj, &mstory5_scene0PlayerDestPos0, 20);
    mstory5_Scene0ObjSeLoopStop(0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    while (!(mstory5_scene0WorkTbl[3].unk_08 & 2)) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 2);
    mstory5_Scene0ObjSeLoopStart(0, 0x1F);
    mstory5_ObjPosMoveEx(obj, &mstory5_scene0PlayerDestPos2, 30, 0);
    mstory5_Scene0ObjSeLoopStop(0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    for (i = 0; i < 2; i++) {
        Hu3DMotionShiftSet(model, Hu3DData[obj->motion[9]].motId, 0, 5, 0);
        Hu3DMotionSpeedSet(model, 5.0f);
        mstory5_MotionEndWait(model);
        Hu3DMotionModelSet(model, obj->motion[9]);
        Hu3DMotionAttrSet(model, 4, 4);
        Hu3DMotionAttrSet(model, 2, 0);
        Hu3DMotionSpeedSet(model, 5.0f);
        Hu3DMotionTimeSet(model, Hu3DMotion[Hu3DData[model].motId].unk02);
        while (Hu3DData[model].motTime > 0.0f) {
            HuPrcVSleep();
        }
        Hu3DMotionAttrSet(model, 4, 0);
    }
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    Hu3DMotionSpeedSet(model, 1.0f);
    while (!(mstory5_scene0WorkTbl[3].unk_08 & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0PlayerDestRot3, 40);
    while (!(mstory5_scene0WorkTbl[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0PlayerDestRot2, 15);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 2);
    mstory5_Scene0ObjSeLoopStart(0, 0x1F);
    mstory5_ObjPosMoveV(obj, &mstory5_scene0PlayerDestPos1, 30);
    mstory5_Scene0ObjSeLoopStop(0);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    mstory5_scene0WorkTbl[0].func = mstory5_Scene0ObjIdle;
}

void mstory5_Scene0PlayerReactExec(omObjData *obj) {
    s16 model = obj->model[1];

    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[9]].motId, 0, 10, 0);
    mstory5_MotionEndWait(model);
    HuPrcSleep(80);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory5_scene0WorkTbl[0].func = mstory5_Scene0ObjIdle;
}

void mstory5_Scene0PlayerTurn1(omObjData *obj) {
    mstory5_ObjRotMoveV(obj, &mstory5_scene0PlayerDestRot4, 10);
    mstory5_scene0WorkTbl[0].func = mstory5_Scene0ObjIdle;
}

void mstory5_Scene0PlayerTurn2(omObjData *obj) {
    mstory5_ObjRotMoveV(obj, &mstory5_scene0PlayerDestRot5, 10);
    mstory5_scene0WorkTbl[0].func = mstory5_Scene0ObjIdle;
}

const Vec mstory5_scene0PlayerDestRot4 = { 0.0f, 150.0f, 0.0f };

const Vec mstory5_scene0PlayerDestRot5 = { 0.0f, 162.4f, 0.0f };

const char mstory5_scene0TumbleAnimName[] = "c204n_0_DEF";

void mstory5_Scene0TumbleProc(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(20, 4, 8, -1, NULL);
    mstory5_scene0WorkTbl[1].obj = obj;
    mstory5_scene0WorkTbl[1].unk_08 = 0;
    mstory5_scene0WorkTbl[1].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory5_scene0ShadowMdl);
    omObjMotionRead(obj, 0, 0xA0076);
    omObjMotionRead(obj, 1, 0x1D0029);
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    mstory5_scene0TumblePos = mstory5_scene0TumbleStartPos;
    Hu3DModelPosSet(obj->model[1], mstory5_scene0TumblePos.x, mstory5_scene0TumblePos.y, mstory5_scene0TumblePos.z);
    Hu3DModelPosSet(obj->model[2], mstory5_scene0TumblePos.x, -5.0f, mstory5_scene0TumblePos.z);
    data = DataRead(0xA007E);
    mstory5_scene0TumbleFaceAnimTbl[0] = (s16)Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, mstory5_scene0TumbleAnimName);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    Hu3DAnimAttrSet(mstory5_scene0TumbleFaceAnim0, 1, 0);
    Hu3DAnimBankSet(mstory5_scene0TumbleFaceAnim0, 0);
    mstory5_scene0TumbleFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory5_scene0TumbleFaceAnim0, 0, mstory5_scene0TumbleAnimName);
    mstory5_scene0TumbleFaceAnimTbl[0] = Hu3DAnimData[mstory5_scene0TumbleFaceAnimTbl[0]].animIdx;
    data = DataRead(0xA0080);
    mstory5_scene0TumbleFaceAnimTbl[1] = (s16)Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    mstory5_scene0TumbleFaceAnimTbl[2] = (s16)Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory5_HmfAnimSet(obj->model[1], mstory5_scene0TumbleFaceSlot, mstory5_scene0TumbleFaceAnim0);
    omPrcSetDestructor(0, mstory5_Scene0TumbleDestroy);
    mstory5_scene0WorkTbl[1].func = mstory5_Scene0ObjIdle;
    while (TRUE) {
        mstory5_scene0WorkTbl[1].func(obj);
        HuPrcVSleep();
    }
}

void mstory5_Scene0TumbleDestroy(void) {
}

const Vec mstory5_scene0TumbleDestRot0 = { -5.0f, 300.0f, 0.0f };

const Vec mstory5_scene0TumbleDestRot1 = { 10.0f, 378.9f, 0.0f };

void mstory5_Scene0TumbleExec(omObjData *obj) {
    HuPrcSleep(40);
    HuPrcSleep(20);
    mstory5_scene0WorkTbl[0].func = mstory5_Scene0PlayerReactExec;
    mstory5_scene0WorkTbl[6].func = mstory5_Scene0StarTurn;
    mstory5_ObjRotMoveV(obj, &mstory5_scene0TumbleDestRot1, 30);
    mstory5_ObjPosMoveV(obj, &mstory5_scene0TumbleDestPos1, 20);
    HuPrcSleep(30);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0TumbleDestRot4, 10);
    mstory5_ObjPosMoveV(obj, &mstory5_scene0TumbleDestPos0, 15);
    mstory5_scene0WorkTbl[0].func = mstory5_Scene0PlayerTurn1;
    mstory5_ObjRotMoveV(obj, &mstory5_scene0TumbleDestRot2, 10);
    mstory5_HmfAnimSet(obj->model[1], mstory5_scene0TumbleFaceSlot, mstory5_scene0TumbleFaceAnim1);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(2) == 0 ? 0x5A3C : 0x5B2F);
    mstory5_WinClose();
    mstory5_HmfAnimSet(obj->model[1], mstory5_scene0TumbleFaceSlot, mstory5_scene0TumbleFaceAnim0);
    mstory5_ObjRotMove(mstory5_scene0WorkTbl[0].obj, 0.0f, 162.4744f, 0.0f, 10);
    mstory5_ObjRotMoveV(mstory5_scene0WorkTbl[6].obj, &mstory5_scene0StarDestRot3, 10);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0TumbleDestRot3, 20);
    Hu3DMotionShiftSet(mstory5_scene0WorkTbl[6].obj->model[1], Hu3DData[mstory5_scene0WorkTbl[6].obj->motion[1]].motId, 0, 10, 2);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(2) == 0 ? 0x5A3D : 0x5B30);
    mstory5_WinClose();
    Hu3DMotionShiftSet(mstory5_scene0WorkTbl[6].obj->model[1], Hu3DData[mstory5_scene0WorkTbl[6].obj->motion[0]].motId, 0, 10, 2);
    mstory5_ObjRotMoveV(mstory5_scene0WorkTbl[6].obj, &mstory5_scene0StarDestRot4, 10);
    mstory5_scene0WorkTbl[7].func = mstory5_Scene0StampFlyExec;
    mstory5_ObjRotMoveV(obj, &mstory5_scene0TumbleDestRot0, 20);
    Hu3DMotionShiftSet(mstory5_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory5_scene0WorkTbl[0].obj->motion[10]].motId, 0, 10, 2);
    while (!(mstory5_scene0WorkTbl[7].unk_08 & 2)) {
        HuPrcVSleep();
    }
    mstory5_scene0WorkTbl[0].func = mstory5_Scene0PlayerStampExec;
    HuPrcSleep(40);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0TumbleDestRot6, 50);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0TumbleDestRot5, 40);
    mstory5_scene0WorkTbl[1].func = mstory5_Scene0ObjIdle;
}

void mstory5_Scene0TumbleExit(omObjData *obj) {
    mstory5_ObjRotMoveV(obj, &mstory5_scene0TumbleDestRot7, 20);
    mstory5_ObjPosMoveV(obj, &mstory5_scene0TumbleDestPos2, 20);
    while (!(mstory5_scene0WorkTbl[3].unk_08 & 2)) {
        HuPrcVSleep();
    }
    mstory5_ObjPosMoveEx(obj, &mstory5_scene0TumbleDestPos4, 30, 0);
    while (!(mstory5_scene0WorkTbl[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    mstory5_ObjPosMoveV(obj, &mstory5_scene0TumbleDestPos3, 30);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    mstory5_scene0WorkTbl[1].func = mstory5_Scene0ObjIdle;
}

void mstory5_Scene0TumbleHop(omObjData *obj) {
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
    mstory5_HmfAnimSet(obj->model[1], mstory5_scene0TumbleFaceSlot, mstory5_scene0TumbleFaceAnim2);
    mstory5_scene0WorkTbl[1].func = mstory5_Scene0ObjIdle;
}

void mstory5_Scene0RivalProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    mstory5_scene0WorkTbl[2].obj = obj;
    mstory5_scene0WorkTbl[2].unk_08 = 0;
    mstory5_scene0WorkTbl[2].unk_0C = 0;
    if (mstory5_PlayerChrCheck(2) == 0) {
        obj->model[1] = Hu3DModelRead(0x700A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(mstory5_scene0ShadowMdl);
        omObjMotionRead(obj, 0, 0x70000);
        omObjMotionRead(obj, 1, 0x1D0050);
        omObjMotionRead(obj, 2, 0x1D0051);
    } else {
        obj->model[1] = Hu3DModelRead(0x300A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(mstory5_scene0ShadowMdl);
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
    mstory5_scene0RivalPos = mstory5_scene0RivalStartPos;
    Hu3DModelPosSet(obj->model[1], mstory5_scene0RivalPos.x, mstory5_scene0RivalPos.y, mstory5_scene0RivalPos.z);
    Hu3DModelPosSet(obj->model[2], mstory5_scene0RivalPos.x, -5.0f, mstory5_scene0RivalPos.z);
    omPrcSetDestructor(0, mstory5_Scene0RivalDestroy);
    mstory5_scene0WorkTbl[2].func = mstory5_Scene0RivalExec;
    while (1) {
        mstory5_scene0WorkTbl[2].func(obj);
        HuPrcVSleep();
    }
}

void mstory5_Scene0RivalDestroy(void) {
}

const Vec mstory5_scene0TumbleDestRot2 = { 20.0f, 320.0f, 0.0f };
const Vec mstory5_scene0UnusedRot1 = { 0.0f, 450.0f, 0.0f }; /* Unreferenced. */

const Vec mstory5_scene0TumbleDestRot3 = { 0.0f, 225.0f, 0.0f };

const Vec mstory5_scene0TumbleDestRot4 = { 0.0f, 134.2f, 0.0f };

const Vec mstory5_scene0TumbleDestRot5 = { 0.0f, 320.0f, 0.0f };

const Vec mstory5_scene0TumbleDestRot6 = { -30.0f, 260.0f, 0.0f };

const Vec mstory5_scene0TumbleDestPos0 = { 238.0f, 100.0f, 214.0f };

const Vec mstory5_scene0TumbleDestPos1 = { 88.0f, 100.0f, 360.0f };
const Vec mstory5_scene0UnusedRot2 = { 0.0f, 0.0f, 0.0f }; /* Unreferenced. */

const Vec mstory5_scene0StarDestRot3 = { 30.0f, -20.0f, 0.0f };

const Vec mstory5_scene0StarDestRot4 = { 0.0f, 0.0f, 0.0f };

const Vec mstory5_scene0TumbleDestPos2 = { 388.0f, 100.0f, 214.0f };

const Vec mstory5_scene0TumbleDestPos3 = { 818.0f, 100.0f, 214.0f };

const Vec mstory5_scene0TumbleDestPos4 = { -12.0f, 100.0f, 214.0f };

const Vec mstory5_scene0TumbleDestRot7 = { 0.0f, 90.0f, 0.0f };
const Vec mstory5_scene0UnusedRot3 = { 0.0f, 270.0f, 0.0f }; /* Unreferenced. */

const Vec mstory5_scene0RivalDestPos0 = { 200.0f, 0.0f, 1200.0f };

void mstory5_Scene0RivalExec(omObjData *obj) {
    HuPrcSleep(10);
    if (mstory5_PlayerChrCheck(2) == 0) {
        CharFXPlay(0x26B, 2);
    } else {
        CharFXPlay(0x26B, 1);
    }
    HuPrcSleep(20);
    mstory5_scene0WorkTbl[1].func = mstory5_Scene0TumbleExec;
    HuPrcSleep(70);
    if (mstory5_PlayerChrCheck(2) == 0) {
        CharFXPlay(0x286, 2);
    } else {
        CharFXPlay(0x286, 1);
    }
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    mstory5_ObjPosMoveV(obj, &mstory5_scene0RivalDestPos0, 40);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    mstory5_scene0WorkTbl[2].func = mstory5_Scene0ObjIdle;
}

void mstory5_Scene0FireProc(void) {
    omObjData *obj;
    void *data;
    s16 first;
    s16 spr;
    s16 model;
    f32 scale;
    s32 i;

    obj = omAddObj(20, 20, 1, -1, NULL);
    mstory5_scene0FireWork.obj = obj;
    for (i = 0; i < 16; i++) {
        if (i == 0) {
            data = DataRead(0x1D0036);
            first = spr = Hu3DSprModelCreate(data, 0xA89, 8);
            DataClose(data);
        } else {
            spr = Hu3DSprModelLink(first, 8);
        }
        Hu3DSprModelColorSet(spr, 0xF0, 0x40, 8);
        Hu3DSprModelTPLvlSet(spr, 0x80);
        model = Hu3DSprModelData[spr].modelId;
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelObjAttrSet(model, 0x70000000, 0x70000000);
        Hu3DMotionAttrSet(model, 2, 2);
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        obj->model[i + 1] = model;
        mstory5_scene0FireParticleTbl[i].time = -10.0f;
        mstory5_scene0FireParticleTbl[i].pos.x = 0.0f;
        mstory5_scene0FireParticleTbl[i].pos.y = 0.0f;
        mstory5_scene0FireParticleTbl[i].pos.z = 0.0f;
        mstory5_scene0FireParticleTbl[i].vel.x = 0.0f;
        mstory5_scene0FireParticleTbl[i].vel.y = 0.0f;
        mstory5_scene0FireParticleTbl[i].vel.z = 0.0f;
    }
    mstory5_scene0FireWork.func = mstory5_Scene0ObjIdle;
    while (TRUE) {
        mstory5_scene0FireWork.func(obj);
        for (i = 0; i < 16; i++) {
            if (mstory5_scene0FireParticleTbl[i].time < 0.0f) {
                continue;
            }
            Hu3DModelAttrSet(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            scale = mstory5_scene0FireParticleTbl[i].time / 40.0f * 3.0f + 1.0f;
            Hu3DModelScaleSet(obj->model[i + 1], scale, scale, scale);
            Hu3DModelPosSet(obj->model[i + 1], mstory5_scene0FireParticleTbl[i].pos.x, mstory5_scene0FireParticleTbl[i].pos.y, mstory5_scene0FireParticleTbl[i].pos.z);
            mstory5_scene0FireParticleTbl[i].pos.x += mstory5_scene0FireParticleTbl[i].vel.x;
            mstory5_scene0FireParticleTbl[i].pos.y += mstory5_scene0FireParticleTbl[i].vel.y;
            mstory5_scene0FireParticleTbl[i].pos.z += mstory5_scene0FireParticleTbl[i].vel.z;
            mstory5_scene0FireParticleTbl[i].time++;
            if (mstory5_scene0FireParticleTbl[i].time >= 40.0f) {
                Hu3DModelAttrSet(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                mstory5_scene0FireParticleTbl[i].time = -10.0f;
            }
        }
        HuPrcVSleep();
    }
}

void mstory5_Scene0FireEmit(omObjData *obj) {
    Vec pos;
    Vec rot;
    Vec ofs;
    omObjData *boat;
    s16 model;
    s32 i;

    if (mstory5_scene0FireEmitCnt >= 3) {
        mstory5_scene0FireEmitCnt = 0;
        boat = mstory5_scene0WorkTbl[3].obj;
        model = boat->model[1];
        pos.x = Hu3DData[model].pos.x;
        pos.y = Hu3DData[model].pos.y;
        pos.z = Hu3DData[model].pos.z;
        rot.x = Hu3DData[model].rot.x;
        rot.y = Hu3DData[model].rot.y;
        rot.z = Hu3DData[model].rot.z;
        for (i = 0; i < 16; i++) {
            if (mstory5_scene0FireParticleTbl[i].time < 0.0f) {
                ofs.x = 0.0f;
                ofs.y = 150.0f;
                ofs.z = 300.0f;
                mstory5_scene0FireParticleTbl[i].pos.x = cosdf(rot.y) * ofs.x + pos.x - sindf(rot.y) * ofs.z;
                mstory5_scene0FireParticleTbl[i].pos.y = pos.y + ofs.y;
                mstory5_scene0FireParticleTbl[i].pos.z = sindf(rot.y) * ofs.x + pos.z + cosdf(rot.y) * ofs.z;
                mstory5_scene0FireParticleTbl[i].vel.x = sindf(rot.y) * 5.0f;
                mstory5_scene0FireParticleTbl[i].vel.y = cosdf(120.0f) * 5.0f;
                mstory5_scene0FireParticleTbl[i].vel.z = cosdf(rot.y) * 5.0f;
                mstory5_scene0FireParticleTbl[i].time = 0.0f;
                Hu3DModelAttrSet(boat->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                break;
            }
        }
    }
    mstory5_scene0FireEmitCnt++;
}

void mstory5_Scene0KoopaProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 16, 8, -1, NULL);
    mstory5_scene0WorkTbl[3].obj = obj;
    mstory5_scene0WorkTbl[3].unk_08 = 0;
    mstory5_scene0WorkTbl[3].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0xA002F, 0x2B9);
    obj->model[2] = Hu3DModelLink(mstory5_scene0ShadowMdl);
    Hu3DModelScaleSet(obj->model[2], 3.0f, 1.0f, 3.0f);
    omObjMotionRead(obj, 0, 0xA0030);
    omObjMotionRead(obj, 1, 0xA0035);
    omObjMotionRead(obj, 2, 0xA0032);
    omObjMotionRead(obj, 3, 0xA003A);
    omObjMotionRead(obj, 4, 0xA003B);
    omObjMotionRead(obj, 5, 0x1D0031);
    Hu3DMotionModelSet(obj->model[1], obj->motion[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    mstory5_scene0KoopaPos = mstory5_scene0KoopaStartPos;
    Hu3DModelPosSet(obj->model[1], mstory5_scene0KoopaPos.x, mstory5_scene0KoopaPos.y, mstory5_scene0KoopaPos.z);
    Hu3DModelPosSet(obj->model[2], mstory5_scene0KoopaPos.x, -5.0f, mstory5_scene0KoopaPos.z);
    omPrcSetDestructor(0, mstory5_Scene0KoopaDestroy);
    mstory5_scene0WorkTbl[3].func = mstory5_Scene0ObjIdle;
    while (1) {
        mstory5_scene0WorkTbl[3].func(obj);
        HuPrcVSleep();
    }
}

void mstory5_Scene0KoopaDestroy(void) {
}

void mstory5_Scene0KoopaExec(omObjData *obj) {
    s16 model = obj->model[1];

    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    HuAudSeqPlay(0x21);
    HuAudFXPlay(0x29D);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(2) == 0 ? 0x5A40 : 0x5B33);
    mstory5_WinClose();
    mstory5_scene0WorkTbl[4].func = mstory5_Scene0KoopaJrAExec;
    mstory5_scene0WorkTbl[5].func = mstory5_Scene0KoopaJrBExec;
    mstory5_scene0WorkTbl[3].unk_08 |= 2;
    mstory5_ObjPosMoveV(obj, &mstory5_scene0KoopaDestPos0, 40);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    HuAudFXPlay(0x29C);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(2) == 0 ? 0x5A41 : 0x5B34);
    mstory5_WinClose();
    mstory5_scene0WorkTbl[3].unk_08 |= 8;
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
    mstory5_MotionEndWait(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory5_ObjPosMoveV(mstory5_scene0WorkTbl[1].obj, &mstory5_scene0TumbleDestPos5, 10);
    HuAudFXPlay(0x2A8);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(2) == 0 ? 0x5A42 : 0x5B35);
    mstory5_WinClose();
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[5]].motId, 0, 10, 0);
    mstory5_MotionEndWait(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory5_scene0WorkTbl[3].unk_08 |= 0x10;
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0KoopaDestRot0, 10);
    mstory5_ObjPosMoveEx(obj, &mstory5_scene0KoopaDestPos1, 40, 0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory5_scene0WorkTbl[3].unk_08 |= 1;
    mstory5_ObjRotMoveV(obj, &mstory5_scene0KoopaDestRot2, 90);
    HuPrcSleep(60);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0KoopaDestRot1, 20);
    mstory5_scene0WorkTbl[3].unk_08 |= 4;
    HuPrcSleep(20);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory5_ObjPosMoveV(obj, &mstory5_scene0KoopaDestPos2, 30);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0KoopaDestRot0, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    HuPrcSleep(30);
    HuAudFXPlay(0x21B);
    mstory5_scene0FireWork.func = mstory5_Scene0FireEmit;
    mstory5_MotionEndWait(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    HuPrcSleep(20);
    mstory5_scene0FireWork.func = mstory5_Scene0ObjIdle;
    mstory5_MotionEndWait(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(40);
    HuAudFXPlay(0x29E);
    mstory5_WinOpen();
    mstory5_WinMesExec(mstory5_PlayerChrCheck(2) == 0 ? 0x5A44 : 0x5B37);
    mstory5_WinClose();
    mstory5_scene0WorkTbl[3].unk_08 |= 0x20;
    HuPrcSleep(50);
    mstory5_SceneEnd();
    mstory5_scene0WorkTbl[3].func = mstory5_Scene0ObjIdle;
}

void mstory5_Scene0KoopaJrAProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    mstory5_scene0WorkTbl[4].obj = obj;
    mstory5_scene0WorkTbl[4].unk_08 = 0;
    mstory5_scene0WorkTbl[4].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(mstory5_scene0ShadowMdl);
    omObjMotionRead(obj, 0, 0xA00EF);
    omObjMotionRead(obj, 1, 0xA00F1);
    omObjMotionRead(obj, 2, 0xA00F0);
    omObjMotionRead(obj, 3, 0x1D0037);
    Hu3DMotionModelSet(obj->model[1], obj->motion[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    mstory5_scene0KoopaJrAPos = mstory5_scene0KoopaJrAStartPos;
    Hu3DModelPosSet(obj->model[1], mstory5_scene0KoopaJrAPos.x, mstory5_scene0KoopaJrAPos.y, mstory5_scene0KoopaJrAPos.z);
    Hu3DModelPosSet(obj->model[2], mstory5_scene0KoopaJrAPos.x, -5.0f, mstory5_scene0KoopaJrAPos.z);
    omPrcSetDestructor(0, mstory5_Scene0KoopaJrADestroy);
    mstory5_scene0WorkTbl[4].func = mstory5_Scene0ObjIdle;
    while (1) {
        mstory5_scene0WorkTbl[4].func(obj);
        HuPrcVSleep();
    }
}

void mstory5_Scene0KoopaJrADestroy(void) {
}

void mstory5_Scene0KoopaJrAExec(omObjData *obj) {
    s16 model = obj->model[1];

    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    mstory5_ObjPosMoveV(obj, &mstory5_scene0KoopaJrADestPos0, 40);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    while (!(mstory5_scene0WorkTbl[3].unk_08 & 8)) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    mstory5_MotionEndWait(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    while (!(mstory5_scene0WorkTbl[3].unk_08 & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0KoopaJrADestRot1, 40);
    while (!(mstory5_scene0WorkTbl[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(50);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0KoopaJrADestRot0, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    mstory5_ObjPosMoveV(obj, &mstory5_scene0KoopaJrADestPos1, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(40);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0KoopaJrADestRot1, 10);
    while (!(mstory5_scene0WorkTbl[3].unk_08 & 4)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0KoopaJrADestRot0, 30);
    while (!(mstory5_scene0WorkTbl[3].unk_08 & 0x20)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
        mstory5_MotionEndWait(model);
    }
}

void mstory5_Scene0KoopaJrBProc(void) {
    omObjData *obj;
    omObjData *src;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    mstory5_scene0WorkTbl[5].obj = obj;
    mstory5_scene0WorkTbl[5].unk_08 = 0;
    mstory5_scene0WorkTbl[5].unk_0C = 0;
    src = mstory5_scene0WorkTbl[4].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    obj->model[2] = Hu3DModelLink(mstory5_scene0ShadowMdl);
    Hu3DMotionModelSet(obj->model[1], src->motion[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    mstory5_scene0KoopaJrBPos = mstory5_scene0KoopaJrBStartPos;
    Hu3DModelPosSet(obj->model[1], mstory5_scene0KoopaJrBPos.x, mstory5_scene0KoopaJrBPos.y, mstory5_scene0KoopaJrBPos.z);
    Hu3DModelPosSet(obj->model[2], mstory5_scene0KoopaJrBPos.x, -5.0f, mstory5_scene0KoopaJrBPos.z);
    omPrcSetDestructor(0, mstory5_Scene0KoopaJrBDestroy);
    mstory5_scene0WorkTbl[5].func = mstory5_Scene0ObjIdle;
    while (1) {
        mstory5_scene0WorkTbl[5].func(obj);
        HuPrcVSleep();
    }
}

void mstory5_Scene0KoopaJrBExec(omObjData *obj) {
    omObjData *src = mstory5_scene0WorkTbl[4].obj;
    s16 model = obj->model[1];

    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    mstory5_ObjPosMoveV(obj, &mstory5_scene0KoopaJrBDestPos0, 40);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[0]].motId, 0, 10, 2);
    while (!(mstory5_scene0WorkTbl[3].unk_08 & 8)) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[3]].motId, 0, 10, 0);
    mstory5_MotionEndWait(model);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[0]].motId, 0, 10, 2);
    while (!(mstory5_scene0WorkTbl[3].unk_08 & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0KoopaJrBDestRot1, 40);
    while (!(mstory5_scene0WorkTbl[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(50);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0KoopaJrBDestRot0, 10);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[1]].motId, 0, 10, 2);
    mstory5_ObjPosMoveV(obj, &mstory5_scene0KoopaJrBDestPos1, 10);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(40);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0KoopaJrBDestRot1, 10);
    while (!(mstory5_scene0WorkTbl[3].unk_08 & 4)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0KoopaJrBDestRot0, 30);
    while (!(mstory5_scene0WorkTbl[3].unk_08 & 0x20)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        Hu3DMotionShiftSet(model, Hu3DData[src->motion[2]].motId, 0, 10, 0);
        mstory5_MotionEndWait(model);
    }
}

void mstory5_Scene0KoopaJrBDestroy(void) {
}

void mstory5_Scene0StarProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    mstory5_scene0WorkTbl[6].obj = obj;
    mstory5_scene0WorkTbl[6].unk_08 = 0;
    mstory5_scene0WorkTbl[6].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    AuraCreate(obj->model[1]);
    omObjMotionRead(obj, 0, 0xA0123);
    omObjMotionRead(obj, 1, 0xA0125);
    omObjMotionRead(obj, 2, 0xA0127);
    obj->model[2] = Hu3DModelLink(mstory5_scene0ShadowMdl);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    mstory5_scene0StarPos = mstory5_scene0StarStartPos;
    Hu3DModelPosSet(obj->model[1], mstory5_scene0StarPos.x, mstory5_scene0StarPos.y, mstory5_scene0StarPos.z);
    Hu3DModelPosSet(obj->model[2], mstory5_scene0StarPos.x, -5.0f, mstory5_scene0StarPos.z);
    omPrcSetDestructor(0, mstory5_Scene0StarDestroy);
    mstory5_scene0WorkTbl[6].func = mstory5_Scene0ObjIdle;
    mstory5_scene0StarFloatF = 1;
    while (1) {
        mstory5_scene0WorkTbl[6].func(obj);
        HuPrcVSleep();
    }
}

void mstory5_Scene0StarDestroy(void) {
}

const Vec mstory5_scene0KoopaDestPos0 = { 350.0f, 0.0f, 380.0f };
const Vec mstory5_scene0UnusedPos0 = { 1350.0f, 0.0f, 380.0f }; /* Unreferenced. */

const Vec mstory5_scene0KoopaDestPos1 = { 350.0f, 0.0f, 0.0f };

const Vec mstory5_scene0KoopaDestPos2 = { 150.0f, 0.0f, 400.0f };

const Vec mstory5_scene0KoopaDestRot0 = { 0.0f, 0.0f, 0.0f };
const Vec mstory5_scene0UnusedRot4 = { 0.0f, 90.0f, 0.0f };  /* Unreferenced. */
const Vec mstory5_scene0UnusedRot5 = { 0.0f, -90.0f, 0.0f }; /* Unreferenced. */

const Vec mstory5_scene0KoopaDestRot1 = { 0.0f, -26.565f, 0.0f };

const Vec mstory5_scene0KoopaDestRot2 = { 0.0f, 20.0f, 0.0f };

const Vec mstory5_scene0TumbleDestPos5 = { 68.0f, 100.0f, 214.0f };

const Vec mstory5_scene0KoopaJrADestPos0 = { -280.0f, 0.0f, 300.0f };
const Vec mstory5_scene0UnusedPos1 = { 820.0f, 0.0f, 300.0f }; /* Unreferenced. */

const Vec mstory5_scene0KoopaJrADestPos1 = { -180.0f, 0.0f, 300.0f };
const Vec mstory5_scene0UnusedRot6 = { 0.0f, 0.0f, 0.0f }; /* Unreferenced. */

const Vec mstory5_scene0KoopaJrADestRot0 = { 0.0f, 90.0f, 0.0f };

const Vec mstory5_scene0KoopaJrADestRot1 = { 0.0f, 135.0f, 0.0f };

const Vec mstory5_scene0KoopaJrBDestPos0 = { -300.0f, 0.0f, 500.0f };
const Vec mstory5_scene0UnusedPos2 = { 800.0f, 0.0f, 500.0f }; /* Unreferenced. */

const Vec mstory5_scene0KoopaJrBDestPos1 = { -200.0f, 0.0f, 500.0f };
const Vec mstory5_scene0UnusedRot7 = { 0.0f, 0.0f, 0.0f }; /* Unreferenced. */

const Vec mstory5_scene0KoopaJrBDestRot0 = { 0.0f, 90.0f, 0.0f };

const Vec mstory5_scene0KoopaJrBDestRot1 = { 0.0f, 125.0f, 0.0f };

const Vec mstory5_scene0StarDestPos2 = { 250.0f, 0.0f, 150.0f };
const Vec mstory5_scene0StarDestPos3 = { 800.0f, 0.0f, 350.0f };

void mstory5_Scene0StarExec(omObjData *obj) {
    mstory5_ObjRotMoveV(obj, &mstory5_scene0StarDestRot5, 20);
    mstory5_ObjPosMoveV(obj, &mstory5_scene0StarDestPos2, 20);
    while (!(mstory5_scene0WorkTbl[3].unk_08 & 2)) {
        HuPrcVSleep();
    }
    mstory5_ObjPosMoveEx(obj, &mstory5_scene0StarDestPos4, 30, 0);
    while (!(mstory5_scene0WorkTbl[3].unk_08 & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0StarDestRot8, 40);
    while (!(mstory5_scene0WorkTbl[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0StarDestRot5, 15);
    mstory5_ObjPosMoveEx(obj, &mstory5_scene0StarDestPos5, 5, 0);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0StarDestRot6, 10);
    mstory5_ObjRotMoveV(obj, &mstory5_scene0StarDestRot7, 10);
    mstory5_ObjPosMoveEx(obj, &mstory5_scene0StarDestPos3, 20, 0);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    mstory5_scene0WorkTbl[6].func = mstory5_Scene0ObjIdle;
}

void mstory5_Scene0StarTurn(omObjData *obj) {
    mstory5_ObjRotMoveV(obj, &mstory5_scene0StarDestRot9, 20);
    mstory5_scene0WorkTbl[6].func = mstory5_Scene0ObjIdle;
}

void mstory5_Scene0StarFloatProc(void) {
    f32 angle = 0.0f;
    Vec pos;
    f32 ofs;
    s16 model;

    if (mstory5_scene0StarFloatF != 0) {
        model = mstory5_scene0WorkTbl[6].obj->model[1];
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

void mstory5_Scene0StampProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 8, 0, -1, NULL);
    mstory5_scene0WorkTbl[7].obj = obj;
    mstory5_scene0WorkTbl[7].unk_08 = 0;
    mstory5_scene0WorkTbl[7].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(mstory5_scene0StampMdlTbl[0], 0x20299);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    mstory5_scene0StampPos = mstory5_scene0StampStartPos;
    Hu3DModelPosSet(obj->model[1], mstory5_scene0StampPos.x, mstory5_scene0StampPos.y, mstory5_scene0StampPos.z);
    mstory5_scene0StampEff = EffectCreate(0xB0004, 0x6A9);
    EffectParamSet(mstory5_scene0StampEff, 4.0f, 20.0f, 4.0f);
    EffectRangeSet(mstory5_scene0StampEff, 60.0f);
    Hu3DParticleAttrSet(mstory5_scene0StampEff, 1, 0);
    Hu3DModelAttrSet(mstory5_scene0StampEff, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    omPrcSetDestructor(0, mstory5_Scene0StampDestroy);
    mstory5_scene0WorkTbl[7].func = mstory5_Scene0ObjIdle;
    while (1) {
        mstory5_scene0WorkTbl[7].func(obj);
        HuPrcVSleep();
    }
}

void mstory5_Scene0StampDestroy(void) {
}

void mstory5_Scene0StampFlyExec(omObjData *obj) {
    Vec pos;
    MstoryPath *paths[2];
    omObjData *target;
    f32 rotY;
    s32 i;

    paths[0] = mstory5_Scene0PathCreate(mstory5_scene0StampPathA, 0);
    paths[1] = mstory5_Scene0PathCreate(mstory5_scene0StampPathB, 0);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(mstory5_scene0StampEff, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DParticleAttrSet(mstory5_scene0StampEff, 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 50; i++) {
        mstory5_Scene0PathPosGet(paths[0], (i * 0.02f) * (i * 0.02f), &pos);
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        EffectPosSet(mstory5_scene0StampEff, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    target = mstory5_scene0WorkTbl[6].obj;
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[2]].motId, 0, 10, 0);
    HuPrcSleep(20);
    mstory5_scene0WorkTbl[7].unk_08 |= 2;
    HuAudFXPlay(0x218);
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[0]].motId, 0, 10, 2);
    rotY = 0.0f;
    for (i = 0; i < 120; i++) {
        mstory5_Scene0PathPosGet(paths[1], (i * 0.008333334f) * (i * 0.008333334f), &pos);
        rotY -= 24.0f;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        Hu3DModelRotSet(obj->model[1], 0.0f, rotY, 0.0f);
        EffectPosSet(mstory5_scene0StampEff, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mstory5_scene0StampEff, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    HuAudFXPlay(0x21A);
    mstory5_Scene0PathKill(paths[0]);
    mstory5_Scene0PathKill(paths[1]);
    mstory5_scene0WorkTbl[7].unk_08 = 1;
    mstory5_scene0WorkTbl[7].func = mstory5_Scene0ObjIdle;
}

void mstory5_Scene0ObjTargetFace(omObjData *obj, omObjData *target) {
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

const Vec mstory5_scene0StarDestPos4 = { -150.0f, 0.0f, 150.0f };

const Vec mstory5_scene0StarDestPos5 = { 50.0f, 0.0f, 350.0f };

const Vec mstory5_scene0StarDestRot5 = { 0.0f, 90.0f, 0.0f };
const Vec mstory5_scene0UnusedRot8 = { 0.0f, -90.0f, 0.0f }; /* Unreferenced. */

const Vec mstory5_scene0StarDestRot6 = { 0.0f, 0.0f, 0.0f };

const Vec mstory5_scene0StarDestRot7 = { 0.0f, 0.0f, -20.0f };

const Vec mstory5_scene0StarDestRot8 = { 0.0f, 135.0f, 0.0f };

const Vec mstory5_scene0StarDestRot9 = { 0.0f, 10.0f, 0.0f };
const s32 mstory5_scene0UnusedStampMdlTbl[3] = { 0x1D0003, 0x1D0004, 0x1D0005 }; /* Unreferenced. */

const s32 mstory5_scene0StampMdlTbl[4] = { 0x1D0006, 0x1D0007, 0x1D0008, 0x1D0009 };

void mstory5_Scene0ObjSeLoopStart(s32 index, s32 seNo) {
    if (mstory5_scene0WorkTbl[index].unk_0C == 0) {
        mstory5_scene0WorkTbl[index].unk_0C = 1;
        mstory5_scene0WorkTbl[index].unk_10 = seNo;
        switch (index) {
            case 0:
                mstory5_scene0WorkTbl[index].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                break;
            case 2:
                if (mstory5_PlayerChrCheck(2) == 0) {
                    mstory5_scene0WorkTbl[index].unk_14 = CharFXPlay(seNo, 2);
                } else {
                    mstory5_scene0WorkTbl[index].unk_14 = CharFXPlay(seNo, 1);
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

void mstory5_Scene0ObjSeLoopStop(s32 index) {
    if (mstory5_scene0WorkTbl[index].unk_0C == 1) {
        mstory5_scene0WorkTbl[index].unk_0C = 0;
        switch (index) {
            case 0:
            case 2:
                HuAudFXStop((s16)mstory5_scene0WorkTbl[index].unk_14);
            case 1:
            case 3:
            case 4:
            case 5:
                break;
        }
    }
}

void mstory5_Scene0ObjSeLoopProc(void) {
    s32 i;
    s32 seNo;

    while (TRUE) {
        for (i = 0; i < 8; i++) {
            if (mstory5_scene0WorkTbl[i].unk_0C == 1 && Hu3DData[mstory5_scene0WorkTbl[i].obj->model[1]].motTime == 0.0f) {
                seNo = mstory5_scene0WorkTbl[i].unk_10;
                switch (i) {
                    case 0:
                        mstory5_scene0WorkTbl[i].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                        break;
                    case 2:
                        if (mstory5_PlayerChrCheck(2) == 0) {
                            mstory5_scene0WorkTbl[i].unk_14 = CharFXPlay(seNo, 2);
                        } else {
                            mstory5_scene0WorkTbl[i].unk_14 = CharFXPlay(seNo, 1);
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
