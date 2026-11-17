#include "common.h"
#include "game/hmfmath.h"
#include "mstory4.h"

typedef struct MstoryPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ u16 flags;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec *points;
    /* 0x0C */ f32 (*intervals)[2];
} MstoryPath; // sizeof 0x10

typedef struct Mstory4FireworkWork {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Vec pos;
} Mstory4FireworkWork; // sizeof 0x10

typedef struct Mstory4SparkGroup {
    /* 0x00 */ s16 count;
    /* 0x04 */ s16 (*pos)[2];
} Mstory4SparkGroup; // sizeof 0x8

extern Vec mstory4_cameraPos;
extern Vec mstory4_cameraTarget;

extern s32 mstory4_mbdBackF;
extern const char mstory4_scene1StarBBodyName[];
extern s16 mstory4_scene1StarEff;
extern const Mstory4SparkGroup mstory4_scene1SparkGroupTbl[6];
extern const s32 mstory4_scene1PicFadeTimeTbl[];
extern s16 mstory4_scene1SparkSprTbl[];
extern s16 mstory4_scene1SparkAnim;
extern const Vec mstory4_scene1TumbleStartPos;
extern void (*const mstory4_sceneCreateTbl[])(void);
extern s32 omCharModelNoTbl[][6];
extern u16 mstory4_scene1VignetteSprTbl[2][2];
extern s16 mstory4_scene1VignetteAnim;
extern const s32 mstory4_scene1PicFileTbl[8];
extern const s32 mstory4_scene1TitleChrFileTbl[8];
extern const s16 mstory4_scene1TitleXTbl[8][2];
extern const s16 mstory4_scene1TitleWidthTbl[2];
extern s16 mstory4_scene1PicAnimTbl[];
extern s16 mstory4_scene1PicAnim7;
extern s16 mstory4_scene1PicSprTbl[];
extern u16 mstory4_scene1PicSpr7;
extern s16 mstory4_scene1TitleSprTbl[2];
extern StoryObjWork mstory4_scene1WorkTbl[4];
extern s16 mstory4_scene1ShadowMdl;
extern s16 mstory4_scene1PlayerFaceAnimTbl[5];
extern Vec mstory4_scene1PlayerPos;
extern Vec mstory4_scene1TumblePos;
extern s32 mstory4_scene1TumbleFaceAnimTbl[4];
extern s16 mstory4_scene1TumbleFaceSlot;
extern s16 mstory4_scene1TumbleFaceAnim3;
extern const Vec mstory4_scene1PlayerStartPos;
extern const s32 mstory4_scene1PlayerMot7Tbl[];
extern const s32 mstory4_scene1PlayerMot10Tbl[];
extern Vec mstory4_scene1StarPos;
extern const Vec mstory4_scene1StarStartPos;
extern const Vec mstory4_scene1StarVanishOfs;

s32 mstory4_scene1StarFloatF = 0;
s32 mstory4_scene1StarFloatStopF = 0;
s32 mstory4_scene1StarBFloatF = 0;
s32 mstory4_scene1StarBFloatStopF = 1;
f32 mstory4_scene1StarBSpinRot = 0.0f;

void mstory4_ObjRotMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void mstory4_Scene1StarBFlyUp(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg5);
void mstory4_Scene1ObjIdle(omObjData *obj);
void mstory4_Scene1PlayerDestroy(void);
void mstory4_Scene1TumbleDestroy(void);
void mstory4_Scene1StarDestroy(void);
void mstory4_Scene1PlayerProc(void);
void mstory4_Scene1TumbleProc(void);
void mstory4_Scene1StarProc(void);
void mstory4_Scene1StarBFloatProc(void);
void mstory4_Scene1StarFloatProc(void);
void mstory4_Scene1EventProc(void);
void mstory4_Scene1ObjSeLoopProc(void);
void mstory4_Scene1EventExec(omObjData *obj);
void mstory4_Scene1StarBPosMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 faceDir);
void mstory4_Scene1VignetteCreate(void);
void mstory4_Scene1VignetteKill(void);
void mstory4_Scene1PicCreate(void);
void mstory4_Scene1PlayerDispOff(void);
void mstory4_Scene1PlayerDispOn(void);
void mstory4_Scene1TumbleKill(void);
void mstory4_Scene1StarFlyUpExec(void);
void mstory4_Scene1StarSpinExec(void);
void mstory4_Scene1ConstellationExec(void);
void mstory4_Scene1SuperstarExec(void);
void mstory4_Scene1TumbleHopTurn(omObjData *obj);
void mstory4_Scene1TumbleLookUp(omObjData *obj);
s16 mstory4_EffectCreate(s32 file, s32 flags);
void mstory4_EffectRangeSet(s16 modelId, f32 value);
void mstory4_EffectParamSet(s16 modelId, f32 x, f32 y, f32 z);
void mstory4_EffectObjExec(omObjData *obj);
s32 mstory4_EffectEmit(s16 model, f32 x, f32 y, f32 z);
s16 mstory4_EffectModelCreate(s32 file, s32 flags);
void mstory4_EffectParticleHook(s16 model);
s16 mstory4_EffectModelRead(s32 dataNum, s32 attr);
void mstory4_Scene1FireworkProc(void);
void mstory4_Scene1FireworkBurst(s16 model, f32 x, f32 y, f32 z, s16 count, s32 randomAxis);
void mstory4_Scene1FireworkHook(s16 model);
void mstory4_Scene1ObjSeLoopStart(s32 index, s32 seNo);
void mstory4_Scene1ObjSeLoopStop(s32 index);
void mstory4_BackDispOff(void);
void mstory4_BackDispOn(void);
void mstory4_SceneEnd(void);
void mstory4_HmfAnimSet(s16 model, s16 animSlot, s16 anim);
void mstory4_WinCreate(void);
void mstory4_WinOpen(void);
void mstory4_WinClose(void);
void mstory4_WinMesExec(s32 mess);
void mstory4_ObjPosMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void mstory4_ObjPosMoveExXYZ(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3);
void mstory4_MotionEndWait(s16 model);

MstoryPath *mstory4_Scene1PathCreate(Vec *points, s32 flags) {
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

void mstory4_Scene1PathPosGet(MstoryPath *path, f32 time, Vec *result) {
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

void mstory4_Scene1PathKill(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void mstory4_Scene1Create(void) {
    mstory4_WinCreate();
    mstory4_scene1ShadowMdl = Hu3DModelRead(9, 0x2B9);
    omAddPrcObj(mstory4_Scene1PlayerProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory4_Scene1TumbleProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory4_Scene1StarProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory4_Scene1StarBFloatProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory4_Scene1StarFloatProc, 0x1001, 0x800, 0);
    omAddPrcObj(mstory4_Scene1EventProc, 0x1002, 0x800, 0);
    omAddPrcObj(mstory4_Scene1ObjSeLoopProc, 0x1002, 0x800, 0);
    HuPrcVSleep();
    Hu3DModelAttrSet(mstory4_scene1ShadowMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void mstory4_Scene1ObjIdle(omObjData *obj) {
}

void mstory4_Scene1PlayerProc(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 6, 16, -1, NULL);
    mstory4_scene1WorkTbl[0].obj = obj;
    mstory4_scene1WorkTbl[0].unk_08 = 0;
    mstory4_scene1WorkTbl[0].unk_0C = 0;
    chr = GwStory.unk1;
    obj->model[1] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory4_scene1ShadowMdl);
    if (GwStory.unk1 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    obj->model[3] = Hu3DModelRead(0x1D000A, 0x2B9);
    Hu3DModelAttrSet(obj->model[3], 4, 4);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 0x34));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 0x8F));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chr, 0x32));
    omObjMotionRead(obj, 5, CharMotionDataNumGet(chr, 0x36));
    omObjMotionRead(obj, 6, CharMotionDataNumGet(chr, 1));
    omObjMotionRead(obj, 7, mstory4_scene1PlayerMot7Tbl[chr]);
    omObjMotionRead(obj, 8, CharMotionDataNumGet(chr, 0x9B));
    omObjMotionRead(obj, 9, CharMotionDataNumGet(chr, 0x7A));
    omObjMotionRead(obj, 10, mstory4_scene1PlayerMot10Tbl[chr]);
    omObjMotionRead(obj, 11, CharMotionDataNumGet(chr, 2));
    omObjMotionRead(obj, 12, CharMotionDataNumGet(chr, 0x72));
    omObjMotionRead(obj, 13, CharMotionDataNumGet(chr, 0x6C));
    mstory4_scene1PlayerFaceAnimTbl[0] = CharAnimCreate(obj->model[1], 2, chr, CharMotionDataNumGet(chr, 0xA4));
    mstory4_scene1PlayerFaceAnimTbl[1] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xAA));
    mstory4_scene1PlayerFaceAnimTbl[2] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA5));
    mstory4_scene1PlayerFaceAnimTbl[3] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA9));
    mstory4_scene1PlayerFaceAnimTbl[4] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xAB));
    Hu3DModelDynamicFree(obj->model[1]);
    CharAnimSet(obj->model[1], 2, GwStory.unk1, mstory4_scene1PlayerFaceAnimTbl[0]);
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    mstory4_scene1PlayerPos = mstory4_scene1PlayerStartPos;
    Hu3DModelPosSet(obj->model[1], mstory4_scene1PlayerPos.x, mstory4_scene1PlayerPos.y, mstory4_scene1PlayerPos.z);
    Hu3DModelPosSet(obj->model[2], mstory4_scene1PlayerPos.x, -5.0f, mstory4_scene1PlayerPos.z);
    omPrcSetDestructor(0, mstory4_Scene1PlayerDestroy);
    mstory4_scene1WorkTbl[0].func = mstory4_Scene1ObjIdle;
    while (TRUE) {
        mstory4_scene1WorkTbl[0].func(obj);
        HuPrcVSleep();
    }
}

void mstory4_Scene1PlayerDestroy(void) {
}

void mstory4_Scene1PlayerStep(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    HuPrcSleep(30);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[6]].motId, 0, 10, 2);
    mstory4_Scene1ObjSeLoopStart(0, 0x1F);
    mstory4_ObjPosMoveExXYZ(obj, pos.x, pos.y, pos.z + 50.0f, 15, 0);
    mstory4_Scene1ObjSeLoopStop(0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    mstory4_scene1WorkTbl[0].func = mstory4_Scene1ObjIdle;
}

void mstory4_Scene1PlayerTurn(omObjData *obj) {
    mstory4_ObjRotMove(obj, 0.0f, 180.0f, 0.0f, 40);
    mstory4_scene1WorkTbl[0].func = mstory4_Scene1ObjIdle;
}

const Vec mstory4_scene1PlayerStartPos = { -120.0f, 0.0f, 480.0f };

const Vec mstory4_scene1TumbleStartPos = { 188.0f, 100.0f, 314.0f };

const Vec mstory4_scene1StarStartPos = { 0.0f, 200.0f, 150.0f };

const s32 mstory4_scene1PlayerMot7Tbl[8] = { 0x1D0042, 0x1D004D, 0x1D0056, 0x1D005F, 0x1D0069, 0x1D0072, 0x1D0042, 0x1D0042 };

const s32 mstory4_scene1PlayerMot10Tbl[8] = { 0x1D007D, 0x1D007E, 0x1D007F, 0x1D0080, 0x1D0081, 0x1D0082, 0x1D007D, 0x1D007D };

const char mstory4_scene1TumbleAnimName[] = "c204n_0_DEF";

void mstory4_Scene1TumbleProc(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(20, 8, 8, -1, NULL);
    mstory4_scene1WorkTbl[1].obj = obj;
    mstory4_scene1WorkTbl[1].unk_08 = 0;
    mstory4_scene1WorkTbl[1].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory4_scene1ShadowMdl);
    obj->model[3] = Hu3DModelRead(0x1D002B, 0x2B9);
    obj->model[4] = Hu3DModelRead(0x1D002C, 0x2B9);
    Hu3DModelAttrSet(obj->model[3], 4, 4);
    Hu3DModelAttrSet(obj->model[4], 4, 4);
    obj->model[5] = Hu3DModelRead(0x1D002D, 0x299);
    Hu3DModelAttrSet(obj->model[5], 4, 4);
    Hu3DModelScaleSet(obj->model[5], 2.0f, 2.0f, 2.0f);
    Hu3DMotionAttrSet(obj->model[5], 2, 2);
    Hu3DMotionSpeedSet(obj->model[5], 0.5f);
    obj->model[6] = Hu3DModelRead(0xA015F, 0x2A9);
    Hu3DModelAttrSet(obj->model[6], 4, 4);
    Hu3DMotionAttrSet(obj->model[6], 2, 2);
    mstory4_scene1StarBFloatF = 1;
    omObjMotionRead(obj, 0, 0xA0076);
    omObjMotionRead(obj, 1, 0x1D0029);
    omObjMotionRead(obj, 2, 0x1D0083);
    omObjMotionRead(obj, 3, 0x1D0084);
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 10.0f, 330.0f, 0.0f);
    mstory4_scene1TumblePos = mstory4_scene1TumbleStartPos;
    Hu3DModelPosSet(obj->model[1], mstory4_scene1TumblePos.x, mstory4_scene1TumblePos.y, mstory4_scene1TumblePos.z);
    Hu3DModelPosSet(obj->model[2], mstory4_scene1TumblePos.x, -5.0f, mstory4_scene1TumblePos.z);
    data = DataRead(0xA007E);
    mstory4_scene1TumbleFaceAnimTbl[0] = (s16)Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, mstory4_scene1TumbleAnimName);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    Hu3DAnimAttrSet(mstory4_scene1TumbleFaceAnimTbl[0], 1, 0);
    Hu3DAnimBankSet(mstory4_scene1TumbleFaceAnimTbl[0], 0);
    mstory4_scene1TumbleFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory4_scene1TumbleFaceAnimTbl[0], 0, mstory4_scene1TumbleAnimName);
    mstory4_scene1TumbleFaceAnimTbl[0] = Hu3DAnimData[mstory4_scene1TumbleFaceAnimTbl[0]].animIdx;
    data = DataRead(0xA0080);
    mstory4_scene1TumbleFaceAnimTbl[1] = (s16)Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    mstory4_scene1TumbleFaceAnimTbl[2] = (s16)Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0081);
    mstory4_scene1TumbleFaceAnimTbl[3] = (s16)Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory4_HmfAnimSet(obj->model[1], mstory4_scene1TumbleFaceSlot, mstory4_scene1TumbleFaceAnimTbl[0]);
    omPrcSetDestructor(0, mstory4_Scene1TumbleDestroy);
    mstory4_scene1WorkTbl[1].func = mstory4_Scene1ObjIdle;
    while (TRUE) {
        mstory4_scene1WorkTbl[1].func(obj);
        HuPrcVSleep();
    }
}

void mstory4_Scene1TumbleDestroy(void) {
}

void mstory4_Scene1TumbleTurn(omObjData *obj) {
    mstory4_ObjRotMove(obj, 0.0f, 230.0f, 0.0f, 30);
    mstory4_scene1WorkTbl[1].func = mstory4_Scene1ObjIdle;
}

void mstory4_Scene1TumbleSpin(omObjData *obj) {
    Vec pos;
    f32 scale;
    s32 i;

    mstory4_ObjRotMove(obj, 0.0f, 360.0f, 0.0f, 10);
    Hu3DData[obj->model[1]].rot.y = 0.0f;
    pos.x = Hu3DData[obj->model[1]].pos.x;
    pos.y = Hu3DData[obj->model[1]].pos.y;
    pos.z = Hu3DData[obj->model[1]].pos.z;
    mstory4_ObjPosMoveExXYZ(obj, pos.x, pos.y - 50.0f, pos.z, 20, 0);
    pos.x = Hu3DData[obj->model[1]].pos.x;
    pos.y = Hu3DData[obj->model[1]].pos.y + 80.0f;
    pos.z = Hu3DData[obj->model[1]].pos.z;
    Hu3DModelAttrSet(obj->model[5], 4, 0);
    Hu3DModelPosSet(obj->model[5], pos.x, pos.y, pos.z);
    Hu3DModelPosSet(obj->model[6], pos.x, pos.y, pos.z);
    HuAudFXPlay(0x222);
    for (i = 0; i < 10; i++) {
        Hu3DModelPosSet(obj->model[5], pos.x, pos.y, pos.z);
        Hu3DModelPosSet(obj->model[6], pos.x, pos.y, pos.z);
        scale = sindf(i * 9.0f) * 2.0f;
        Hu3DModelScaleSet(obj->model[5], scale, scale, 1.0f);
        HuPrcVSleep();
    }
    Hu3DModelScaleSet(obj->model[5], 2.0f, 2.0f, 2.0f);
    mstory4_scene1WorkTbl[1].func = mstory4_Scene1ObjIdle;
}

void mstory4_Scene1TumbleExit(omObjData *obj) {
    mstory4_ObjRotMove(obj, 10.0f, -30.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[3]].motId, 0, 10, 2);
    HuPrcSleep(30);
    mstory4_ObjPosMoveExXYZ(obj, mstory4_scene1TumbleStartPos.x + 300.0f, mstory4_scene1TumbleStartPos.y + 100.0f, mstory4_scene1TumbleStartPos.z, 20,
                          0);
    mstory4_scene1WorkTbl[1].func = mstory4_Scene1ObjIdle;
}

void mstory4_Scene1StarProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    mstory4_scene1WorkTbl[2].obj = obj;
    mstory4_scene1WorkTbl[2].unk_08 = 0;
    mstory4_scene1WorkTbl[2].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    AuraCreate(obj->model[1]);
    omObjMotionRead(obj, 0, 0xA0123);
    omObjMotionRead(obj, 1, 0xA0125);
    omObjMotionRead(obj, 2, 0xA0129);
    omObjMotionRead(obj, 3, 0xA0127);
    omObjMotionRead(obj, 4, 0xA012D);
    obj->model[2] = Hu3DModelLink(mstory4_scene1ShadowMdl);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    mstory4_scene1StarPos = mstory4_scene1StarStartPos;
    Hu3DModelPosSet(obj->model[1], mstory4_scene1StarPos.x, mstory4_scene1StarPos.y, mstory4_scene1StarPos.z);
    Hu3DModelPosSet(obj->model[2], mstory4_scene1StarPos.x, -5.0f, mstory4_scene1StarPos.z);
    omPrcSetDestructor(0, mstory4_Scene1StarDestroy);
    mstory4_scene1WorkTbl[2].func = mstory4_Scene1ObjIdle;
    mstory4_scene1StarFloatF = 1;
    while (1) {
        mstory4_scene1WorkTbl[2].func(obj);
        HuPrcVSleep();
    }
}

void mstory4_Scene1StarDestroy(void) {
}

const Vec mstory4_scene1StarVanishOfs = { -400.0f, 300.0f, -400.0f };

void mstory4_Scene1StarVanish(omObjData *obj) {
    s16 models[2];
    Vec pos;
    Vec ofs;
    f32 rot;
    f32 scale;
    f32 t;
    f32 s;
    f32 c;
    s32 i;

    models[0] = obj->model[1];
    models[1] = obj->model[2];
    pos.x = Hu3DData[models[0]].pos.x;
    pos.y = Hu3DData[models[0]].pos.y;
    pos.z = Hu3DData[models[0]].pos.z;
    ofs.x = 0.0f;
    ofs.y = 0.0f;
    ofs.z = 0.0f;
    rot = ofs.x;
    scale = rot;
    mstory4_scene1StarFloatStopF = 1;
    for (i = 0; i < 20; i++) {
        t = i * 4.5f;
        s = sindf(t);
        ofs.x = s * mstory4_scene1StarVanishOfs.x;
        ofs.y = s * mstory4_scene1StarVanishOfs.y;
        ofs.z = s * mstory4_scene1StarVanishOfs.z;
        Hu3DModelPosSet(models[0], pos.x + ofs.x, pos.y + ofs.y, pos.z + ofs.z);
        Hu3DModelPosSet(models[1], pos.x + ofs.x, 0.0f, pos.z + ofs.z);
        c = cosdf(t) * 2.0f;
        Hu3DModelScaleSet(models[0], c, c, c);
        scale -= 0.2;
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        Hu3DModelScaleSet(models[1], scale, scale, scale);
        rot += 0.5f;
        Hu3DModelRotSet(models[0], 0.0f, 0.0f, rot);
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DModelAttrSet(obj->model[2], 4, 4);
    mstory4_scene1WorkTbl[2].func = mstory4_Scene1ObjIdle;
}

void mstory4_Scene1StarFloatProc(void) {
    f32 angle = 0.0f;
    Vec pos;
    f32 ofs;
    s16 model;

    if (mstory4_scene1StarFloatF != 0) {
        model = mstory4_scene1WorkTbl[2].obj->model[1];
        pos.y = Hu3DData[model].pos.y;
        while (TRUE) {
            pos.x = Hu3DData[model].pos.x;
            pos.z = Hu3DData[model].pos.z;
            ofs = sindf(angle) * 25.0f + 25.0f;
            angle += 2.0f;
            angle = (angle >= 360.0f) ? angle - 360.0f : angle;
            Hu3DModelPosSet(model, pos.x, ofs + pos.y, pos.z);
            if (mstory4_scene1StarFloatStopF == 1) {
                break;
            }
            HuPrcVSleep();
        }
        while (TRUE) {
            HuPrcVSleep();
        }
    }
}

void mstory4_Scene1StarBFloatProc(void) {
    f32 angle = 0.0f;
    Vec pos;
    f32 ofs;
    s16 model;

    if (mstory4_scene1StarBFloatF != 0) {
        model = mstory4_scene1WorkTbl[1].obj->model[6];
        pos.y = Hu3DData[model].pos.y;
        while (TRUE) {
            if (mstory4_scene1StarBFloatStopF == 0) {
                pos.x = Hu3DData[model].pos.x;
                pos.z = Hu3DData[model].pos.z;
                ofs = sindf(angle) * 40.0f;
                angle += 2.0f;
                angle = (angle >= 360.0f) ? angle - 360.0f : angle;
                Hu3DModelPosSet(model, pos.x, ofs + pos.y, pos.z);
            } else {
                pos.y = Hu3DData[model].pos.y;
                angle = 0.0f;
            }
            HuPrcVSleep();
        }
    }
}

void mstory4_Scene1ObjTargetFace(omObjData *obj, omObjData *target) {
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

void mstory4_Scene1EventProc(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    mstory4_scene1WorkTbl[3].obj = obj;
    mstory4_scene1WorkTbl[3].unk_08 = 0;
    mstory4_scene1WorkTbl[3].unk_0C = 0;
    mstory4_scene1WorkTbl[3].func = mstory4_Scene1EventExec;

    for (;;) {
        mstory4_scene1WorkTbl[3].func(obj);
        HuPrcVSleep();
    }
}

const char *mstory4_scene1StarBAuraNameTbl[] = { "c221_000-aura_0", "c221_000-aura_1", "c221_000-aura_2", "c221_000-aura3" };
s16 mstory4_scene1Spark0PosTbl[][2] = {
    { 147, 99 },
    { 135, 111 },
    { 126, 141 },
    { 186, 39 },
};
s16 mstory4_scene1Spark1PosTbl[][2] = {
    { 175, 64 },
    { 174, 92 },
    { 161, 113 },
    { 154, 136 },
    { 139, 155 },
};
s16 mstory4_scene1Spark2PosTbl[][2] = {
    { 193, 78 },
    { 189, 105 },
    { 173, 127 },
    { 167, 158 },
};
s16 mstory4_scene1Spark3PosTbl[][2] = {
    { 215, 112 },
    { 206, 130 },
    { 188, 141 },
};
s16 mstory4_scene1Spark4PosTbl[][2] = {
    { 229, 122 },
    { 221, 146 },
    { 202, 169 },
};
s16 mstory4_scene1Spark5PosTbl[][2] = {
    { 246, 119 },
    { 236, 156 },
    { 225, 174 },
};
u8 mstory4_effectScaleWobble[] = { 0, 1, 2, 1 };
s16 mstory4_scene1FireworkSide = 1;
u8 mstory4_scene1FireworkColorTbl[] = {
    0xFF,
    0x20,
    0x40,
    0xFF,
    0xFF,
    0x40,
    0x40,
    0xC0,
    0xC0,
    0xFF,
    0xFF,
    0xFF,
};

// Remaining differences:
// - Only the `model` spill slot differs (0x3E in the target vs 0x7E here).
//   The target frame is 0x40 bytes larger than the locals need, but that space
//   lies after the reload-allocated `model` slot, i.e. it comes from 8 more
//   reload slots (8 bytes each) for pseudos with no remaining insns. `dist` is
//   one such pseudo: loop.c hoists `dist / time` next to the constant sets,
//   then combine folds the three insns with `time` as i1 (kept, it is still
//   used by the loop test) and `dist` as i2; because the result needs a new
//   i2 pattern, combine does not zero dist's reg_n_refs, so reload gives it a
//   slot. A variable only reproduces this when it is the later-set operand of
//   a hoisted constant expression whose other operand stays live. Named
//   locals for the 4.5f/0.5f rotation steps (e.g. `rotY / time`) add at most
//   one slot per distinct variable, and extra variables in the `dist` loop
//   would need separate registers. The `unused` array restores the frame
//   size, but since arrays are allocated before reload slots, it pushes
//   `model` past it.
// - The final wait loop needs `pad` reassigned in the for-loop increment: the
//   register then is not single-use inside the loop, so loop.c hoists the
//   address into s0 as in the target (plain `while (!HuPadBtnDown[0])`
//   forms get the address substituted back into the load).
#ifdef NON_MATCHING
void mstory4_Scene1EventExec(omObjData *obj) {
    omObjData *obj0;
    omObjData *obj1;
    omObjData *obj2;
    Vec pos;
    HmfMotionNode *nodes[4];
    s16 model;
    s32 i;
    f32 ofs;
    f32 time;
    f32 dist;
    f32 scale;
    u16 *pad;
    s32 unused[16]; // Retain the original stack frame.

    HuPrcVSleep();
    obj0 = mstory4_scene1WorkTbl[0].obj;
    obj1 = mstory4_scene1WorkTbl[1].obj;
    obj2 = mstory4_scene1WorkTbl[2].obj;
    model = obj0->model[1];
    HuPrcSleep(10);
    CharFXPlay(0x262, GwStory.unk1);
    CharAnimSet(obj0->model[1], 2, GwStory.unk1, mstory4_scene1PlayerFaceAnimTbl[2]);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[1]].motId, 0, 20, 0);
    mstory4_MotionEndWait(model);
    HuPrcSleep(30);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(20);
    CharAnimSet(obj0->model[1], 2, GwStory.unk1, mstory4_scene1PlayerFaceAnimTbl[0]);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[10]].motId, 0, 10, 2);
    mstory4_ObjRotMove(obj0, 0.0f, 180.0f, 0.0f, 20);
    HuPrcSleep(30);
    mstory4_ObjRotMove(obj1, 0.0f, 210.0f, 0.0f, 10);
    mstory4_WinOpen();
    mstory4_WinMesExec(0x5A79);
    mstory4_WinClose();
    HuPrcSleep(40);
    mstory4_ObjPosMoveExXYZ(obj2, 0.0f, 200.0f, -150.0f, 40, 0);
    HuPrcSleep(50);
    HuAudFXPlay(0x15C);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(mstory4_scene1WorkTbl[2].obj->model[1], Hu3DData[mstory4_scene1WorkTbl[2].obj->motion[2]].motId, 0, 10, 2);
    mstory4_scene1WorkTbl[0].func = mstory4_Scene1PlayerStep;
    mstory4_ObjRotMove(obj2, 0.0f, -10.0f, 0.0f, 10);
    mstory4_ObjPosMoveExXYZ(obj2, -120.0f, 200.0f, 400.0f, 20, 0);
    mstory4_ObjRotMove(obj2, 0.0f, 0.0f, 0.0f, 10);
    mstory4_WinOpen();
    mstory4_WinMesExec(0x5A7A);
    mstory4_WinClose();
    Hu3DMotionShiftSet(mstory4_scene1WorkTbl[2].obj->model[1], Hu3DData[mstory4_scene1WorkTbl[2].obj->motion[2]].motId, 0, 10, 0);
    HuPrcSleep(30);
    mstory4_ObjPosMoveExXYZ(obj2, 0.0f, 200.0f, -150.0f, 5, 0);
    mstory4_ObjRotMove(obj2, 0.0f, 0.0f, 0.0f, 5);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(mstory4_scene1WorkTbl[2].obj->model[1], Hu3DData[mstory4_scene1WorkTbl[2].obj->motion[4]].motId, 0, 10, 2);
    mstory4_WinOpen();
    mstory4_WinMesExec(0x5A7B);
    mstory4_WinClose();
    mstory4_scene1WorkTbl[2].func = mstory4_Scene1StarVanish;
    HuAudFXPlay(0x224);
    HuAudSeqFadeOut(120);
    HuPrcSleep(10);
    mstory4_scene1WorkTbl[1].func = mstory4_Scene1TumbleHopTurn;
    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[6]].motId, 0, 10, 2);
    mstory4_Scene1ObjSeLoopStart(0, 0x1F);
    mstory4_ObjPosMove(obj0, pos.x - 80.0f, pos.y, pos.z - 200.0f, 20);
    mstory4_Scene1ObjSeLoopStop(0);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(50);
    mstory4_ObjRotMove(obj0, 0.0f, 0.0f, 0.0f, 10);
    CharFXPlay(0x286, GwStory.unk1);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[5]].motId, 0, 10, 0);
    mstory4_MotionEndWait(model);
    HuPrcSleep(40);
    mstory4_scene1WorkTbl[1].func = mstory4_Scene1TumbleSpin;
    HuPrcSleep(40);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[0]].motId, 0, 30, 0);
    HuPrcSleep(20);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[9]].motId, 0, 10, 0);
    mstory4_ObjRotMove(obj0, 0.0f, 110.0f, 0.0f, 20);
    mstory4_MotionEndWait(model);
    HuPrcSleep(25);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[6]].motId, 0, 10, 2);
    Hu3DMotionSpeedSet(model, 1.0f);
    mstory4_Scene1ObjSeLoopStart(0, 0x1F);
    mstory4_ObjPosMove(obj0, -100.0f, 0.0f, 300.0f, 35);
    mstory4_Scene1ObjSeLoopStop(0);
    Hu3DMotionSpeedSet(model, 1.0f);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(20);
    mstory4_BackDispOff();
    mstory4_Scene1VignetteCreate();
    mstory4_cameraTarget.x = Hu3DData[obj1->model[1]].pos.x;
    mstory4_cameraTarget.y = Hu3DData[obj1->model[1]].pos.y + 90.0f;
    mstory4_cameraTarget.z = Hu3DData[obj1->model[1]].pos.z;
    mstory4_cameraPos.x = Hu3DData[obj1->model[1]].pos.x;
    mstory4_cameraPos.y = Hu3DData[obj1->model[1]].pos.y + 90.0f;
    mstory4_cameraPos.z = Hu3DData[obj1->model[1]].pos.z + 400.0f;
    mstory4_Scene1PlayerDispOff();
    pos.x = Hu3DData[obj1->model[1]].pos.x;
    pos.y = Hu3DData[obj1->model[1]].pos.y + 90.0f;
    pos.z = Hu3DData[obj1->model[1]].pos.z - 5.0f;
    Hu3DModelPosSet(obj1->model[6], pos.x, pos.y, pos.z);
    Hu3DModelPosSet(obj1->model[5], pos.x, pos.y, pos.z - 80.0f);
    Hu3DMotionModelSet(obj1->model[1], obj1->motion[2]);
    Hu3DMotionAttrSet(obj1->model[1], 2, 0);
    Hu3DMotionAttrSet(obj1->model[1], 1, 1);
    Hu3DModelObjCopy(obj1->model[3], "saikoro", obj1->model[1], "saikoro");
    Hu3DModelObjCopy(obj1->model[4], "c204nj1-futa", obj1->model[1], "futa");
    ofs = 0.0f;
    scale = 0.0f;
    for (i = 0; i < 4; i++) {
        Hu3DMotionNoMotSet(obj1->model[6], Hu3DData[obj1->model[6]].motId, mstory4_scene1StarBAuraNameTbl[i], 27, 69);
        Hu3DMotionNoMotSet(obj1->model[6], Hu3DData[obj1->model[6]].motId, mstory4_scene1StarBAuraNameTbl[i], 27, 70);
        Hu3DMotionNoMotSet(obj1->model[6], Hu3DData[obj1->model[6]].motId, mstory4_scene1StarBAuraNameTbl[i], 27, 71);
        nodes[i] = Hu3DModelObjPtrGet(obj1->model[6], mstory4_scene1StarBAuraNameTbl[i]);
        nodes[i]->baseScale.z = nodes[i]->baseScale.y = nodes[i]->baseScale.x = scale;
        nodes[i]->scale.z = nodes[i]->scale.y = nodes[i]->scale.x = scale;
    }
    HuPrcVSleep();
    HuPrcSleep(10);
    Hu3DMotionAttrSet(obj1->model[1], 1, 0);
    HuPrcSleep(30);
    Hu3DModelAttrSet(obj1->model[6], 4, 0);
    HuAudFXPlay(0x223);
    HuPrcSleep(60);
    time = 60.0f;
    dist = 250.0f;
    ofs = 0.0f;
    for (i = 0; i <= time; i++) {
        mstory4_cameraTarget.y += dist / time;
        mstory4_cameraPos.y += dist / time;
        ofs += dist / time;
        HuPrcVSleep();
        Hu3DModelPosSet(obj1->model[6], pos.x, ofs + pos.y, pos.z);
        Hu3DModelPosSet(obj1->model[5], pos.x, ofs + pos.y, pos.z - 80.0f);
    }
    HuPrcSleep(50);
    mstory4_cameraTarget.x = -25.0f;
    mstory4_cameraTarget.y = 0.0f;
    mstory4_cameraTarget.z = -650.0f;
    mstory4_cameraPos.x = 14.0f;
    mstory4_cameraPos.y = 193.0f;
    mstory4_cameraPos.z = 1400.0f;
    HuPrcVSleep();
    Hu3DModelPosSet(obj1->model[6], mstory4_scene1TumbleStartPos.x, mstory4_scene1TumbleStartPos.y + 150.0f, mstory4_scene1TumbleStartPos.z);
    Hu3DModelAttrSet(obj1->model[5], 4, 4);
    for (i = 0; i < 4; i++) {
        Hu3DMotionNoMotReset(obj1->model[6], Hu3DData[obj1->model[6]].motId, mstory4_scene1StarBAuraNameTbl[i], 27, 69);
        Hu3DMotionNoMotReset(obj1->model[6], Hu3DData[obj1->model[6]].motId, mstory4_scene1StarBAuraNameTbl[i], 27, 70);
        Hu3DMotionNoMotReset(obj1->model[6], Hu3DData[obj1->model[6]].motId, mstory4_scene1StarBAuraNameTbl[i], 27, 71);
    }
    mstory4_Scene1VignetteKill();
    mstory4_BackDispOn();
    mstory4_Scene1PlayerDispOn();
    Hu3DModelPosSet(obj0->model[1], 0.0f, 0.0f, 300.0f);
    Hu3DModelPosSet(obj0->model[2], 0.0f, 0.0f, 300.0f);
    HuPrcVSleep();
    mstory4_scene1StarBFloatStopF = 0;
    Hu3DMotionModelSet(obj1->model[1], obj1->motion[2]);
    Hu3DMotionAttrSet(obj1->model[1], 2, 0);
    Hu3DMotionAttrSet(obj1->model[1], 4, 4);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[9]].motId, 0, 10, 0);
    Hu3DMotionTimeSet(obj1->model[1], Hu3DMotion[Hu3DData[obj1->model[1]].motId].unk02);
    do {
        time = Hu3DData[obj1->model[1]].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    Hu3DMotionAttrSet(obj1->model[1], 4, 0);
    Hu3DMotionModelSet(obj1->model[1], obj1->motion[0]);
    Hu3DMotionAttrSet(obj1->model[1], 2, 2);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[8]].motId, 0, 30, 2);
    mstory4_scene1StarBFloatStopF = 1;
    mstory4_scene1WorkTbl[0].func = mstory4_Scene1PlayerTurn;
    mstory4_Scene1StarBPosMove(obj1, 0.0f, 300.0f, 300.0f, 40, 0);
    mstory4_scene1StarBFloatStopF = 0;
    pos.x = Hu3DData[obj1->model[1]].pos.x;
    pos.y = Hu3DData[obj1->model[1]].pos.y + 100.0f;
    pos.z = Hu3DData[obj1->model[1]].pos.z;
    mstory4_ObjPosMoveExXYZ(obj1, pos.x, pos.y, pos.z, 15, 0);
    HuPrcSleep(20);
    HuAudSeqPlay(0x2A);
    mstory4_WinOpen();
    mstory4_WinMesExec(0x5A7C);
    mstory4_WinClose();
    Hu3DMotionNoMotSet(obj1->model[6], Hu3DData[obj1->model[6]].motId, mstory4_scene1StarBBodyName, 76, 69);
    Hu3DMotionNoMotSet(obj1->model[6], Hu3DData[obj1->model[6]].motId, mstory4_scene1StarBBodyName, 76, 70);
    nodes[0] = Hu3DModelObjPtrGet(obj1->model[6], mstory4_scene1StarBBodyName);
    scale = 0.0f;
    nodes[0]->baseRot.y = scale;
    nodes[0]->rot.z = scale;
    for (i = 0; i < 10; i++) {
        nodes[0]->baseRot.y += 4.5f;
        nodes[0]->rot.z += 4.5f;
        nodes[0]->baseRot.x += 0.5f;
        nodes[0]->rot.x += 0.5f;
        HuPrcVSleep();
    }
    mstory4_ObjRotMove(obj1, 0.0f, -45.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj1->model[1], Hu3DData[obj1->motion[3]].motId, 0, 10, 2);
    mstory4_HmfAnimSet(obj1->model[1], mstory4_scene1TumbleFaceSlot, mstory4_scene1TumbleFaceAnim3);
    HuPrcSleep(40);
    Hu3DMotionShiftSet(obj1->model[1], Hu3DData[obj1->motion[0]].motId, 0, 10, 2);
    mstory4_ObjRotMove(obj1, 10.0f, -20.0f, 0.0f, 10);
    for (i = 0; i < 10; i++) {
        nodes[0]->baseRot.y -= 4.5f;
        nodes[0]->rot.z -= 4.5f;
        nodes[0]->baseRot.x -= 0.5f;
        nodes[0]->rot.x -= 0.5f;
        HuPrcVSleep();
    }
    Hu3DMotionNoMotReset(obj1->model[6], Hu3DData[obj1->model[6]].motId, mstory4_scene1StarBBodyName, 76, 69);
    Hu3DMotionNoMotReset(obj1->model[6], Hu3DData[obj1->model[6]].motId, mstory4_scene1StarBBodyName, 76, 70);
    HuPrcSleep(40);
    mstory4_WinOpen();
    mstory4_WinMesExec(0x5A7D);
    mstory4_WinClose();
    HuPrcSleep(30);
    mstory4_scene1StarBFloatStopF = 1;
    mstory4_scene1WorkTbl[1].func = mstory4_Scene1TumbleLookUp;
    mstory4_Scene1StarBPosMove(obj1, 0.0f, 230.0f, 300.0f, 30, 0);
    HuAudFXPlay(0x225);
    mstory4_Scene1StarBPosMove(obj1, 0.0f, 700.0f, 300.0f, 30, 0);
    HuPrcSleep(30);
    mstory4_Scene1PlayerDispOff();
    mstory4_Scene1TumbleKill();
    AuraKill(mstory4_scene1WorkTbl[2].obj->model[1]);
    Hu3DModelKill(mstory4_scene1WorkTbl[2].obj->model[1]);
    mstory4_BackDispOff();
    mstory4_Scene1PicCreate();
    mstory4_scene1StarBFloatStopF = 1;
    mstory4_Scene1StarFlyUpExec();
    mstory4_Scene1StarSpinExec();
    mstory4_Scene1ConstellationExec();
    mstory4_Scene1SuperstarExec();
    HuPrcSleep(150);
    for (pad = HuPadBtnDown; *pad == 0; pad = HuPadBtnDown) {
        HuPrcVSleep();
    }
    mstory4_SceneEnd();
    mstory4_scene1WorkTbl[3].func = mstory4_Scene1ObjIdle;
}
#else
INCLUDE_ASM("asm/nonmatchings/game/overlays/story/mstory4/scene1", mstory4_Scene1EventExec);
#endif

void mstory4_Scene1StarBPosMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 faceDir) {
    Vec start;
    Vec diff;
    Vec step;
    Vec cur;
    s16 model = obj->model[6];
    f32 i;

    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = x - start.x;
    diff.y = y - start.y;
    diff.z = z - start.z;
    if (faceDir != 0) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(diff.z, diff.x) - 90.0f), 0.0f);
    }
    i = frames;
    step.x = diff.x / i;
    step.y = diff.y / i;
    step.z = diff.z / i;
    for (i = 0.0f; i < (f32)frames; i += 1.0f) {
        cur.x = i * step.x + start.x;
        cur.y = i * step.y + start.y;
        cur.z = i * step.z + start.z;
        Hu3DModelPosSet(model, cur.x, cur.y, cur.z);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, x, y, z);
    HuPrcVSleep();
}

void mstory4_Scene1StarBFlyUp(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg5) {
    Vec start;
    Vec diff;
    Vec step;
    Vec cur;
    s16 model = obj->model[6];
    f32 i;
    f32 angle;
    f32 scale;

    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = x - start.x;
    diff.y = y - start.y;
    diff.z = z - start.z;
    if (arg5 != 0) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(diff.z, diff.x) - 90.0f), 0.0f);
    }
    i = frames;
    step.x = diff.x / i;
    step.y = diff.y / i;
    step.z = diff.z / i;
    scale = 1.0f;
    for (i = 0.0f; i < (f32)frames; i += 1.0f) {
        cur.x = i * step.x + start.x;
        angle = i / frames * 90.0f;
        cur.y = sindf(angle) * diff.y + start.y;
        cur.z = i * step.z + start.z;
        Hu3DModelPosSet(model, cur.x, cur.y, cur.z);
        Hu3DModelScaleSet(model, scale, scale, scale);
        scale = sindf(angle) * 5.0f;
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, x, y, z);
    HuPrcVSleep();
}

f32 mstory4_Scene1StarBSpinPosMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 faceDir) {
    Vec start;
    Vec diff;
    Vec step;
    Vec cur;
    s16 model = obj->model[6];
    f32 i;

    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = x - start.x;
    diff.y = y - start.y;
    diff.z = z - start.z;
    if (faceDir != 0) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(diff.z, diff.x) - 90.0f), 0.0f);
    }
    i = frames;
    step.x = diff.x / i;
    step.y = diff.y / i;
    step.z = diff.z / i;
    mstory4_scene1StarBSpinRot = 0.0f;
    for (i = 0.0f; i < (f32)frames; i += 1.0f) {
        cur.x = i * step.x + start.x;
        cur.y = i * step.y + start.y;
        cur.z = i * step.z + start.z;
        Hu3DModelPosSet(model, cur.x, cur.y, cur.z);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, x, y, z);
    return 20.0f;
}

void mstory4_Scene1VignetteCreate(void) {
    s32 i;
    s32 j;

    mstory4_scene1VignetteAnim = HuSprAnimDataRead(0x1D0028);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            mstory4_scene1VignetteSprTbl[i][j] = espEntry(mstory4_scene1VignetteAnim, 0, 0);
            espPosSet(mstory4_scene1VignetteSprTbl[i][j], j * 160 + 80, i * 120 + 60);
            espAttrSet(mstory4_scene1VignetteSprTbl[i][j], 0x4000);
        }
    }
    espAttrSet(mstory4_scene1VignetteSprTbl[0][1], 1);
    espAttrSet(mstory4_scene1VignetteSprTbl[1][0], 2);
    espAttrSet(mstory4_scene1VignetteSprTbl[1][1], 3);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            espDispOn(mstory4_scene1VignetteSprTbl[i][j]);
        }
    }
}

void mstory4_Scene1VignetteKill(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            espDispOff(mstory4_scene1VignetteSprTbl[i][j]);
            espKill(mstory4_scene1VignetteSprTbl[i][j]);
        }
    }
    HuSprAnimKill(mstory4_scene1VignetteAnim);
}

void mstory4_Scene1PicCreate(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        mstory4_scene1PicAnimTbl[i] = HuSprAnimDataRead(mstory4_scene1PicFileTbl[i]);
        mstory4_scene1PicSprTbl[i] = espEntry(mstory4_scene1PicAnimTbl[i], 0, 0);
        espPosSet(mstory4_scene1PicSprTbl[i], 160, 120);
        espAttrSet(mstory4_scene1PicSprTbl[i], 0x4000);
        espDispOff(mstory4_scene1PicSprTbl[i]);
    }
}

void mstory4_Scene1PicDispOn(s32 index) {
    espDispOn(mstory4_scene1PicSprTbl[index]);
}

void mstory4_Scene1PicDispOff(s32 index) {
    espDispOff(mstory4_scene1PicSprTbl[index]);
}

void mstory4_Scene1PicTPLvlSet(s32 index, s16 level) {
    espTPLvlSet(mstory4_scene1PicSprTbl[index], level);
}

void mstory4_Scene1PicKillAll(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        espDispOff(mstory4_scene1PicSprTbl[i]);
        espKill(mstory4_scene1PicSprTbl[i]);
        HuSprAnimKill(mstory4_scene1PicAnimTbl[i]);
    }
    HuPrcSleep(3);
}

void mstory4_Scene1PicSeqKill(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        espDispOff(mstory4_scene1PicSprTbl[i]);
        espKill(mstory4_scene1PicSprTbl[i]);
        HuSprAnimKill(mstory4_scene1PicAnimTbl[i]);
        HuPrcSleep(3);
    }
}

void mstory4_Scene1PicLastKill(void) {
    u16 *espriteSlot = &mstory4_scene1PicSpr7;
    s16 *sprite = &mstory4_scene1PicAnim7;

    espDispOff(*espriteSlot);
    espKill(*espriteSlot);
    HuSprAnimKill(*sprite);
}

void mstory4_Scene1PlayerDispOff(void) {
    omObjData *obj = mstory4_scene1WorkTbl[0].obj;

    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void mstory4_Scene1PlayerDispOn(void) {
    omObjData *obj = mstory4_scene1WorkTbl[0].obj;

    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void mstory4_Scene1TumbleKill(void) {
    omObjData *obj = mstory4_scene1WorkTbl[1].obj;

    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelKill(obj->model[1]);
    Hu3DModelKill(obj->model[3]);
    Hu3DModelKill(obj->model[4]);
    Hu3DModelKill(obj->model[5]);
}

const char mstory4_scene1StarBBodyName[] = "c221_000-body";

const s32 mstory4_scene1PicFileTbl[8] = { 0x1D0017, 0x1D0015, 0x1D0018, 0x1D0019, 0x1D001A, 0x1D001B, 0x1D001C, 0x1D0016 };

void mstory4_Scene1CameraDebugProc(void) {
    while (TRUE) {
        if (HuPadBtn[0] & Z_TRIG) {
            if (HuPadBtn[0] & R_JPAD) {
                mstory4_cameraPos.x -= 10.0f;
            }
            if (HuPadBtn[0] & L_JPAD) {
                mstory4_cameraPos.x += 10.0f;
            }
        } else {
            if (HuPadBtn[0] & U_JPAD) {
                mstory4_cameraPos.z -= 10.0f;
            }
            if (HuPadBtn[0] & D_JPAD) {
                mstory4_cameraPos.z += 10.0f;
            }
            if (HuPadBtn[0] & R_JPAD) {
                mstory4_cameraPos.y -= 10.0f;
            }
            if (HuPadBtn[0] & L_JPAD) {
                mstory4_cameraPos.y += 10.0f;
            }
        }
        if (HuPadBtn[0] & Z_TRIG) {
            if (HuPadBtn[0] & 1) {
                mstory4_cameraTarget.x -= 10.0f;
            }
            if (HuPadBtn[0] & 2) {
                mstory4_cameraTarget.x += 10.0f;
            }
        } else {
            if (HuPadBtn[0] & 8) {
                mstory4_cameraTarget.z -= 10.0f;
            }
            if (HuPadBtn[0] & 4) {
                mstory4_cameraTarget.z += 10.0f;
            }
            if (HuPadBtn[0] & 1) {
                mstory4_cameraTarget.y -= 10.0f;
            }
            if (HuPadBtn[0] & 2) {
                mstory4_cameraTarget.y += 10.0f;
            }
        }
        sprintf(omDBGStrBuf, "POSX   :[%f]", mstory4_cameraPos.x);
        print8(24, 128, omDBGStrBuf);
        sprintf(omDBGStrBuf, "POSY   :[%f]", mstory4_cameraPos.y);
        print8(24, 136, omDBGStrBuf);
        sprintf(omDBGStrBuf, "POSZ   :[%f]", mstory4_cameraPos.z);
        print8(24, 144, omDBGStrBuf);
        sprintf(omDBGStrBuf, "INTERX :[%f]", mstory4_cameraTarget.x);
        print8(24, 160, omDBGStrBuf);
        sprintf(omDBGStrBuf, "INTERY :[%f]", mstory4_cameraTarget.y);
        print8(24, 168, omDBGStrBuf);
        sprintf(omDBGStrBuf, "INTERZ :[%f]", mstory4_cameraTarget.z);
        print8(24, 176, omDBGStrBuf);
        HuPrcVSleep();
    }
}

void mstory4_Scene1StarFlyUpExec(void) {
    omObjData *obj = mstory4_scene1WorkTbl[1].obj;

    mstory4_Scene1PicDispOn(1);
    mstory4_cameraPos.x = 1720.0f;
    mstory4_cameraPos.y = 4000.0f;
    mstory4_cameraPos.z = 4000.0f;
    mstory4_cameraTarget.x = 140.0f;
    mstory4_cameraTarget.y = 1000.0f;
    mstory4_cameraTarget.z = 500.0f;
    HuPrcVSleep();
    Hu3DModelPosSet(obj->model[6], 0.0f, 0.0f, 0.0f);
    HuAudFXPlay(0x225);
    mstory4_Scene1StarBFlyUp(obj, 0.0f, 3000.0f, 0.0f, 100, 0);
}

void mstory4_Scene1StarSpinExec(void) {
    omObjData *obj = mstory4_scene1WorkTbl[1].obj;
    HmfMotionNode *node;
    f32 speed;
    s32 i;

    mstory4_scene1StarEff = mstory4_EffectCreate(0xB0004, 0x689);
    mstory4_EffectParamSet(mstory4_scene1StarEff, 7.0f, 50.0f, 12.0f);
    mstory4_EffectRangeSet(mstory4_scene1StarEff, 120.0f);
    Hu3DParticleAttrSet(mstory4_scene1StarEff, 1, 0);
    Hu3DModelAttrSet(mstory4_scene1StarEff, 4, 4);
    mstory4_Scene1PicDispOff(1);
    mstory4_Scene1PicDispOn(0);
    mstory4_cameraPos.x = 0.0f;
    mstory4_cameraPos.y = 0.0f;
    mstory4_cameraPos.z = 500.0f;
    mstory4_cameraTarget.x = 0.0f;
    mstory4_cameraTarget.y = 0.0f;
    mstory4_cameraTarget.z = 0.0f;
    HuPrcVSleep();
    Hu3DModelPosSet(obj->model[6], 0.0f, -100.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[6], 1.0f, 1.0f, 1.0f);
    Hu3DMotionNoMotSet(obj->model[6], Hu3DData[obj->model[6]].motId, mstory4_scene1StarBBodyName, 76, 70);
    mstory4_Scene1StarBSpinPosMove(obj, 0.0f, 50.0f, 0.0f, 40, 0);
    speed = 0.0f;
    HuPrcSleep(20);
    node = Hu3DModelObjPtrGet(obj->model[6], mstory4_scene1StarBBodyName);
    node->rot.z = node->baseRot.y = mstory4_scene1StarBSpinRot;
    HuAudFXPlay(0x226);
    for (i = 0; i < 80; i++) {
        if (i == 30) {
            Hu3DParticleAttrSet(mstory4_scene1StarEff, 1, 1);
            Hu3DModelAttrSet(mstory4_scene1StarEff, 4, 0);
        }
        mstory4_scene1StarBSpinRot += speed;
        speed += 1.0f;
        if (speed > 30.0f) {
            speed = 40.0f;
        }
        node->rot.z = node->baseRot.y = mstory4_scene1StarBSpinRot;
        HuPrcVSleep();
    }
    Hu3DMotionNoMotReset(obj->model[6], Hu3DData[obj->model[6]].motId, mstory4_scene1StarBBodyName, 76, 70);
    mstory4_scene1StarBSpinRot = 0.0f;
}

void mstory4_Scene1ConstellationExec(void) {
    omObjData *obj = mstory4_scene1WorkTbl[1].obj;
    void *data;
    s32 n;
    s32 i;
    s32 j;

    data = DataRead(0x1D001D);
    n = 0;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < mstory4_scene1SparkGroupTbl[i].count; j++) {
            mstory4_scene1SparkAnim = HuSprAnimRead(data);
            mstory4_scene1SparkSprTbl[n] = espEntry(mstory4_scene1SparkAnim, 0, 1);
            espPosSet(mstory4_scene1SparkSprTbl[n], mstory4_scene1SparkGroupTbl[i].pos[j][0], mstory4_scene1SparkGroupTbl[i].pos[j][1]);
            espAttrSet(mstory4_scene1SparkSprTbl[n], 0x1000);
            espColorSet(mstory4_scene1SparkSprTbl[n], 0xFF, 0xFF, 0xDC);
            espAttrSet(mstory4_scene1SparkSprTbl[n], 8);
            espTPLvlSet(mstory4_scene1SparkSprTbl[n], 0xFF);
            espDispOff(mstory4_scene1SparkSprTbl[n]);
            n++;
        }
    }
    HuMemMemoryFreePerm(data);
    Hu3DModelAttrSet(obj->model[6], 4, 4);
    mstory4_Scene1PicDispOff(0);
    mstory4_Scene1PicDispOn(1);
    mstory4_cameraPos.x = 0.0f;
    mstory4_cameraPos.y = 40.0f;
    mstory4_cameraPos.z = 310.0f;
    mstory4_cameraTarget.x = 0.0f;
    mstory4_cameraTarget.y = -270.0f;
    mstory4_cameraTarget.z = -180.0f;
    HuPrcVSleep();
    HuPrcSleep(90);
    Hu3DParticleAttrSet(mstory4_scene1StarEff, 1, 0);
    HuPrcSleep(10);
    HuAudFXPlay(0x24E);
    for (j = 1; j < 7; j++) {
        mstory4_Scene1PicDispOn(j + 1);
        mstory4_Scene1PicTPLvlSet(j + 1, 0);
        for (i = 0; i < mstory4_scene1PicFadeTimeTbl[j]; i++) {
            mstory4_Scene1PicTPLvlSet(j + 1, 256.0f / mstory4_scene1PicFadeTimeTbl[j] * i);
            HuPrcVSleep();
        }
        mstory4_Scene1PicDispOff(j);
        mstory4_Scene1PicTPLvlSet(j + 1, 0x100);
    }
    HuAudFXPlay(0x227);
    n = 0;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < mstory4_scene1SparkGroupTbl[i].count; j++) {
            espBankSet(mstory4_scene1SparkSprTbl[n], 0, 0);
            espAnimModeSet(mstory4_scene1SparkSprTbl[n], 1);
            espDispOn(mstory4_scene1SparkSprTbl[n]);
            n++;
            HuPrcSleep(1);
        }
    }
    mstory4_Scene1PicSeqKill();
    HuPrcSleep(129);
}

void MBDBackArcInit(u8 *);
void MBDBackCreate(s32, s32);                   /* extern */
void mstory4_Scene1PicDispOff(s32);                /* extern */
void mstory4_Scene1PicLastKill(void);               /* extern */
void mstory4_Scene1PlayerDispOn(void);               /* extern */
void mstory4_Scene1TitleCreate(void);               /* extern */
void mstory4_Scene1FireworkCreate(f32, f32, f32, s16); /* extern */

void mstory4_Scene1SuperstarExec(void) {
    omObjData *temp_s5;
    omObjData *temp_s7;
    s32 var_s3;
    u16 temp_fp;
    s32 i, j;

    temp_s5 = mstory4_scene1WorkTbl[0].obj;
    temp_s7 = mstory4_scene1WorkTbl[1].obj;
    temp_fp = temp_s5->model[1];
    Hu3DCameraPerspectiveSet(0, 40.0f, 80.0f, 8000.0f);

    mstory4_cameraPos.x = 0.0f;
    mstory4_cameraPos.y = 190.0f;
    mstory4_cameraPos.z = 3770.0f;

    mstory4_cameraTarget.x = 0.0f;
    mstory4_cameraTarget.y = 130.0f;
    mstory4_cameraTarget.z = 450.0f;

    mstory4_mbdBackF = 1;
    var_s3 = 0;
    MBDBackArcInit(hvq_data_ROM_START);
    MBDBackCreate(0x20, 0);
    mstory4_Scene1PicDispOff(7);
    for (i = 0; i < 6; i++) {
        for (j = 0; j < mstory4_scene1SparkGroupTbl[i].count; var_s3++, j++) {
            espBankSet(mstory4_scene1SparkSprTbl[var_s3], 0, 0);
            espAnimModeSet(mstory4_scene1SparkSprTbl[var_s3], 1);
            espDispOff(mstory4_scene1SparkSprTbl[var_s3]);
            espKill(mstory4_scene1SparkSprTbl[var_s3]);
        }
    }

    HuSprAnimKill(mstory4_scene1SparkAnim);
    mstory4_Scene1PlayerDispOn();
    Hu3DMotionModelSet(temp_s5->model[1], temp_s5->motion[13]);
    Hu3DMotionAttrSet(temp_s5->model[1], 2, 2);
    Hu3DModelPosSet(temp_s5->model[1], 0.0f, 0.0f, 2220.0f);
    Hu3DModelPosSet(temp_s5->model[2], 0.0f, -5.0f, 2220.0f);
    Hu3DModelRotSet(temp_s5->model[1], 0, 0, 0);
    Hu3DModelScaleSet(temp_s5->model[1], 1.5f, 1.5f, 1.5f);
    Hu3DModelScaleSet(temp_s5->model[2], 1.5f, 1.5f, 1.5f);
    HuPrcVSleep();
    mstory4_Scene1PicLastKill();
    HuPrcSleep(30);
    Hu3DModelAttrSet(temp_s7->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelPosSet(temp_s7->model[6], 0.0f, 1000.0f, 2120.0f);
    Hu3DModelRotSet(temp_s7->model[6], 0, 0, 0);
    Hu3DModelScaleSet(temp_s7->model[6], 1.5f, 1.5f, 1.5f);
    mstory4_Scene1StarBPosMove(temp_s7, 0.0f, 400.0f, 2120.0f, 0x3C, 0);
    mstory4_scene1StarBFloatStopF = 0;
    HuPrcSleep(20);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[0]].motId, 0, 0xA, 2);
    mstory4_ObjRotMove(temp_s5, 0.0f, 180.0f, 0.0f, 8);
    HuPrcSleep(20);
    mstory4_WinOpen();
    mstory4_WinMesExec(0x5A7E);
    mstory4_WinClose();
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[4]].motId, 0, 0xA, 0);
    mstory4_MotionEndWait(temp_fp);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[0]].motId, 0, 0xA, 2);
    mstory4_ObjRotMove(temp_s5, 0.0f, 0.0f, 0.0f, 0xA);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[11]].motId, 0, 0xA, 2);
    mstory4_Scene1ObjSeLoopStart(0, 0x1F);
    mstory4_ObjPosMoveExXYZ(temp_s5, 0.0f, 0.0f, 2930.0f, 0x28, 0);
    mstory4_Scene1ObjSeLoopStop(0);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[0]].motId, 0, 0xA, 2);
    HuPrcSleep(20);
    CharFXPlay(0x2C6, GwStory.unk1);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[2]].motId, 0, 0xA, 0);
    CharAnimSet(temp_fp, 2, GwStory.unk1, mstory4_scene1PlayerFaceAnimTbl[4]);
    mstory4_Scene1StarBPosMove(temp_s7, 0.0f, 400.0f, 2500.0f, 0x14, 0);
    mstory4_MotionEndWait(temp_fp);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[3]].motId, 0, 0xA, 2);
    mstory4_Scene1TitleCreate();
    HuPrcVSleep();
    for (i = 0; i < 4; i++) {
        mstory4_Scene1FireworkCreate(0.0f, 400.0f, 2500.0f, i << 3);
        HuPrcSleep(2);
    }
}

void mstory4_Scene1TitleCreate(void) {
    s8 chr = GwStory.unk1;
    s8 i;

    mstory4_scene1TitleSprTbl[0] = espEntry(HuSprAnimDataRead(mstory4_scene1TitleChrFileTbl[chr]), 0, 0);
    mstory4_scene1TitleSprTbl[1] = espEntry(HuSprAnimDataRead(0x1D001E), 0, 0);
    for (i = 0; i < 2; i++) {
        espPosSet(mstory4_scene1TitleSprTbl[i], mstory4_scene1TitleXTbl[chr][i] + mstory4_scene1TitleWidthTbl[i] / 2, 194);
    }
}

s16 mstory4_EffectCreate(s32 file, s32 flags) {
    omObjData *obj;
    HmfModelData_UnkBC_Struct *effect;
    s16 model;

    obj = omAddObj(1000, 0, 0, -1, mstory4_EffectObjExec);
    obj->work[0] = model = mstory4_EffectModelCreate(file, flags);
    effect = Hu3DData[model].unkBC;
    effect->unk1C.f = effect->unk20.f = effect->unk24.f = 0.0f;
    effect->unk04 |= 1;
    effect->unk10.f = 100.0f;
    effect->unk14 = -1.0f;
    return model;
}

void mstory4_EffectPosSet(s16 modelId, s32 x, s32 y, s32 z) {
    HmfModelData_UnkBC_Struct *model = Hu3DData[modelId].unkBC;
    model->unk1C.i = x;
    model->unk20.i = y;
    model->unk24.i = z;
}

void mstory4_EffectTimeSet(s16 modelId, s16 value) {
    Hu3DData[modelId].unkBC->unk14 = value;
}

void mstory4_EffectRangeSet(s16 modelId, f32 value) {
    Hu3DData[modelId].unkBC->unk10.f = value;
}

void mstory4_EffectStop(s16 model) {
    Hu3DParticleAttrSet(model, 5, 4);
}

void mstory4_EffectObjExec(omObjData *obj) {
    s16 model = obj->work[0];
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 i;
    f32 x;
    f32 z;

    if (bc->unk04 & 4) {
        particle = bc->unk58;
        for (i = 0; i < hmf->unk1A; i++, particle++) {
            if (particle->unk04 > 0.0f) {
                break;
            }
        }
        if (i == hmf->unk1A) {
            Hu3DModelKill(model);
            omDelObj(obj);
            return;
        }
        bc->unk04 &= ~1;
    }
    if (bc->unk14 >= 0.0f) {
        if ((bc->unk14 -= 1.0f) <= 0.0f) {
            bc->unk04 &= ~1;
        }
    }
    if (bc->unk04 & 1) {
        x = rand8() * bc->unk10.f / 256.0f - bc->unk10.f / 2.0f;
        z = rand8() * bc->unk10.f / 256.0f - bc->unk10.f / 2.0f;
        mstory4_EffectEmit(model, x + bc->unk1C.f, bc->unk20.f, z + bc->unk24.f);
    }
}

s32 mstory4_EffectEmit(s16 model, f32 x, f32 y, f32 z) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = bc->unk58;
    s16 i;

    for (i = 0; i < hmf->unk1A; i++, particle++) {
        if (particle->unk04 <= 0.0f) {
            particle->unk0C = x;
            particle->unk10 = y;
            particle->unk14 = z;
            particle->unk04 = particle->unk08 =
                bc->unk08.f * 0.7f + bc->unk08.f * 0.3f * ((rand8() % 10 + 1) * 0.1f);
            return 1;
        }
    }
    return 0;
}

void mstory4_EffectParamSet(s16 modelId, f32 x, f32 y, f32 z) {
    HmfData *hmf = Hu3DData[modelId].hmf;
    HmfModelData_UnkBC_Struct *unkBC = Hu3DData[modelId].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *entry = unkBC->unk58;
    s16 i;

    unkBC->unk08.f = x;
    unkBC->unk0C.f = y;
    for (i = 0; i < hmf->unk1A; i++) {
        entry->unk1C = -z;
        entry++;
    }
}

s16 mstory4_EffectModelCreate(s32 file, s32 flags) {
    s16 model = mstory4_EffectModelRead(file, flags);
    HmfData *hmf;
    HmfModelData_UnkBC_Struct *unkBC;
    HmfModelData_UnkBC_Unk58_Struct *entry;
    s16 i;

    Hu3DParticleCreate(model, -1, 0, mstory4_EffectParticleHook);
    hmf = Hu3DData[model].hmf;
    unkBC = Hu3DData[model].unkBC;
    entry = unkBC->unk58;
    unkBC->unk08.f = 5.0f;
    unkBC->unk0C.f = 20.0f;
    for (i = 0; i < hmf->unk1A; i++, entry++) {
        entry->unk0C = entry->unk10 = entry->unk14 = 0.0f;
        entry->unk18 = entry->unk20 = 0.0f;
        entry->unk1C = -10.0f;
        entry->unk04 = entry->unk08 = 0.0f;
    }
    return model;
}

void mstory4_EffectParticleHook(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = bc->unk58;
    s16 i;
    s16 count;

    for (i = 0, count = hmf->unk1A; i < count; i++, particle++) {
        if (particle->unk04 > 0.0f) {
            particle->unk0C = particle->unk0C * 0.04f + particle->unk18 + particle->unk0C;
            particle->unk10 += particle->unk1C;
            particle->unk14 = particle->unk14 * 0.04f + particle->unk20 + particle->unk14;
            particle->unk04 -= bc->unk08.f / bc->unk0C.f;
            if (particle->unk04 <= 0.0f) {
                particle->unk04 = 0.0f;
            }
            particle->unk08 = (mstory4_effectScaleWobble[(bc->unk02 + i) & 3] * 0.15f + 1.0f) * particle->unk04;
        }
    }
    bc->unk02++;
}

s16 mstory4_EffectModelRead(s32 dataNum, s32 attr) {
    s16 model = Hu3DModelRead(dataNum, attr);

    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelObjAttrSet(model, 0x20000, 0x20000);
    Hu3DModelRemakeStatic(model);
    Hu3DModelVtxBufMake(model);
    Hu3DModelDynamicFree(model);
    return model;
}

void mstory4_Scene1TumbleHopTurn(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec orig;
    Vec rot;
    f32 step;
    f32 y;
    s32 i;

    orig.x = Hu3DData[model].pos.x;
    orig.y = Hu3DData[model].pos.y;
    orig.z = Hu3DData[model].pos.z;
    pos.y = Hu3DData[model].pos.y;
    rot.x = Hu3DData[model].rot.x;
    rot.y = Hu3DData[model].rot.y;
    rot.z = Hu3DData[model].rot.z;
    step = (230.0f - rot.y) / 12.0f;
    for (i = 0; i < 12; i++) {
        pos.x = Hu3DData[model].pos.x;
        pos.z = Hu3DData[model].pos.z;
        y = sindf(i * 15.0f) * 80.0f;
        rot.y += step;
        Hu3DModelPosSet(model, pos.x, y + pos.y, pos.z);
        Hu3DModelRotSet(model, rot.x, y + rot.y, rot.z);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, orig.x, orig.y, orig.z);
    mstory4_scene1WorkTbl[1].func = mstory4_Scene1ObjIdle;
}

void mstory4_Scene1TumbleLookUp(omObjData *obj) {
    HuPrcSleep(30);
    mstory4_ObjRotMove(obj, -30.0f, -45.0f, 0.0f, 30);
    mstory4_scene1WorkTbl[1].func = mstory4_Scene1ObjIdle;
}

void mstory4_Scene1FireworkCreate(f32 x, f32 y, f32 z, s16 arg3) {
    Process *process = omAddPrcObj(mstory4_Scene1FireworkProc, 0x3F00, 0x2000, 0);
    Mstory4FireworkWork *work = HuMemAllocTag(sizeof(Mstory4FireworkWork), 0x7918);

    process->user_data = work;
    work->pos.x = x;
    work->pos.y = y;
    work->pos.z = z;
    work->unk_02 = arg3;
    work->unk_00 = 0;
}

void mstory4_Scene1FireworkProc(void) {
    Mstory4FireworkWork *work = HuPrcCurrentGet()->user_data;
    HmfData *hmf;
    HmfModelData_Unk64_Unk60_Unk54_Struct *face;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 model;
    s16 models[3];
    s16 total;
    s16 count;
    s16 i;
    s16 j;
    f32 rx;
    f32 ry;
    f32 rz;
    f32 x;
    f32 y;
    f32 z;

    models[0] = model = Hu3DModelRead(0xB0034, 0x28C);
    Hu3DModelObjAttrSet(model, 0x20000, 0x20000);
    hmf = Hu3DData[model].hmf;
    for (j = 0; j < hmf->unk10; j++) {
        count = hmf->unk60[j].unk22;
        face = hmf->unk60[j].unk54;
        for (i = 0; i < count; i++, face++) {
            face->unk00 |= 0x80;
        }
    }
    HuPrcVSleep();
    Hu3DModelRemakeStatic(model);
    Hu3DModelVtxBufMake(model);
    Hu3DModelDynamicFree(model);
    Hu3DParticleCreate(model, -1, NULL, mstory4_Scene1FireworkHook);
    Hu3DParticleAttrSet(model, 8, 8);
    Hu3DParticleCntSet(model, 0);
    particle = Hu3DData[model].unkBC->unk58;
    total = hmf->unk1A;
    for (i = 0; i < total; i++, particle++) {
        particle->unk08 = particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
    }
    HuPrcVSleep();
    models[1] = Hu3DModelRead(0xB004B, 0x29D);
    Hu3DMotionAttrSet(models[1], 2, 2);
    Hu3DModelScaleSet(models[1], 0.2f, 0.2f, 0.2f);
    models[2] = Hu3DModelRead(0xB004C, 0x29D);
    Hu3DModelScaleSet(models[2], 0.4f, 0.4f, 0.4f);
    HuPrcSleep(work->unk_02);
    Hu3DModelAttrSet(model, 4, 0);
    while (TRUE) {
        HuPrcVSleep();
        rx = (s32)(rand8() * 25U >> 7);
        rx = (rx + 100.0f) * mstory4_scene1FireworkSide;
        ry = (rand8() * 75 >> 7) + 50;
        // do-while(0) needed for rz to be register-allocated before rx.
        do {
            rz = rand8() * 75 >> 7;
        } while (0);
        rx *= 2.0f;
        ry *= 2.0f;
        rz *= 2.0f;
        mstory4_scene1FireworkSide *= -1;
        Hu3DModelAttrSet(models[1], 4, 0);
        for (i = 0; i <= 20; i++) {
            x = rx * sindf(i / 20.0f * 90.0f) + work->pos.x;
            y = ry * sindf(i / 20.0f * 135.0f + 45.0f) - ry * sindf(45.0f) + work->pos.y;
            z = rz * sindf(i / 20.0f * 90.0f) + work->pos.z;
            Hu3DModelPosSet(models[1], x, y, z);
            HuPrcVSleep();
        }
        Hu3DModelAttrSet(models[1], 4, 4);
        HuPrcSleep(5);
        if (rand8() & 3) {
            Hu3DModelAttrSet(models[2], 4, 0);
            Hu3DMotionTimeSet(models[2], 0.0f);
            Hu3DMotionSpeedSet(models[2], 3.0f);
            Hu3DModelPosSet(models[2], x, y, z);
            for (i = 0; i < 8; i++) {
                mstory4_Scene1FireworkBurst(model, x, y, z, total / 8, i & 3);
                HuPrcVSleep();
            }
            Hu3DModelAttrSet(models[2], 4, 4);
        } else {
            for (i = 0; i < 8; i++) {
                mstory4_Scene1FireworkBurst(model, x, y, z, total / 8, i & 3);
                HuPrcVSleep();
            }
        }
        HuPrcSleep(25);
    }
}

void mstory4_Scene1FireworkBurst(s16 model, f32 x, f32 y, f32 z, s16 count, s32 randomAxis) {
    f32 step = 360.0f / count;
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Unk58_Struct *particle = Hu3DData[model].unkBC->unk58;
    s16 total = hmf->unk1A;
    f32 ax;
    f32 ay;
    f32 az;
    f32 len;
    f32 angle;
    s16 type;
    s16 i;
    s16 j;

    if (randomAxis) {
        while (TRUE) {
            ax = rand8() - 128;
            ay = rand8() - 128;
            az = rand8() - 128;
            len = ax * ax + ay * ay + az * az;
            if (len != 0.0f) {
                break;
            }
        }
    } else {
        ax = 0.0f;
        ay = 0.0f;
        az = 1.0f;
        len = ax * ax + ay * ay + az * az;
    }
    len = HuSqrtf(len);
    ax /= len;
    ay /= len;
    az /= len;
    type = rand8() & 3;
    for (i = 0, j = 0; j < total; j++, particle++) {
        if (particle->unk08 <= 0.0f) {
            particle->unk0C = x;
            particle->unk10 = y;
            particle->unk14 = z;
            angle = step * i;
            particle->unk18 = ax * ay * (1.0f - cosdf(angle)) - az * sindf(angle);
            particle->unk1C = ay * ay + (1.0f - ay * ay) * cosdf(angle);
            particle->unk20 = ay * az * (1.0f - cosdf(angle)) + ax * sindf(angle);
            particle->unk24 = type;
            particle->unk28 = 0.0f;
            particle->unk08 = 1.0f;
            particle->unk04 = 20.0f;
            if (++i >= count) {
                break;
            }
        }
    }
}

void mstory4_Scene1FireworkHook(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 count;
    s16 i;
    s16 color;
    f32 dx;
    f32 dy;
    f32 dz;

    if (bc->unk00 == -1) {
        count = hmf->unk1A;
    } else {
        count = hmf->unk60[bc->unk00].unk2E;
    }
    particle = bc->unk58;
    if (bc->unk02 >= 50) {
        if (!(bc->unk04 & 1)) {
            return;
        }
        bc->unk02 = 0;
    }
    for (i = 0; i < count; i++, particle++) {
        if (particle->unk08 > 0.0f) {
            color = particle->unk24;
            particle->unk28 += 1.0f;
            particle->unk00[0] = mstory4_scene1FireworkColorTbl[color * 3 + 0];
            particle->unk00[1] = mstory4_scene1FireworkColorTbl[color * 3 + 1];
            particle->unk00[2] = mstory4_scene1FireworkColorTbl[color * 3 + 2];
            dx = particle->unk18 * particle->unk04;
            dy = particle->unk1C * particle->unk04;
            dz = particle->unk20 * particle->unk04;
            particle->unk0C += dx;
            particle->unk10 += dy;
            particle->unk14 += dz;
            particle->unk04 *= 0.9f;
            particle->unk08 -= 0.05f;
        }
    }
}

void mstory4_Scene1ObjSeLoopStart(s32 index, s32 seNo) {
    if (mstory4_scene1WorkTbl[index].unk_0C == 0) {
        mstory4_scene1WorkTbl[index].unk_0C = 1;
        mstory4_scene1WorkTbl[index].unk_10 = seNo;
        if (index == 0) {
            mstory4_scene1WorkTbl[index].unk_14 = CharFXPlay(seNo, GwStory.unk1);
        }
    }
}

void mstory4_Scene1ObjSeLoopStop(s32 index) {
    if (mstory4_scene1WorkTbl[index].unk_0C == 1) {
        mstory4_scene1WorkTbl[index].unk_0C = 0;
        if (index == 0) {
            HuAudFXStop((s16)mstory4_scene1WorkTbl[0].unk_14);
        }
    }
}

void mstory4_Scene1ObjSeLoopProc(void) {
    s32 i;
    s32 seNo;

    while (TRUE) {
        for (i = 0; i < 3; i++) {
            if (mstory4_scene1WorkTbl[i].unk_0C == 1 && Hu3DData[mstory4_scene1WorkTbl[i].obj->model[1]].motTime == 0.0f) {
                seNo = mstory4_scene1WorkTbl[i].unk_10;
                if (i == 0) {
                    mstory4_scene1WorkTbl[i].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                }
            }
        }
        HuPrcVSleep();
    }
}

const Mstory4SparkGroup mstory4_scene1SparkGroupTbl[6] = {
    { 4, mstory4_scene1Spark0PosTbl },
    { 5, mstory4_scene1Spark1PosTbl },
    { 4, mstory4_scene1Spark2PosTbl },
    { 3, mstory4_scene1Spark3PosTbl },
    { 3, mstory4_scene1Spark4PosTbl },
    { 3, mstory4_scene1Spark5PosTbl },
};

const s32 mstory4_scene1PicFadeTimeTbl[7] = { 8, 8, 8, 8, 8, 8, 24 };

const s32 mstory4_scene1TitleChrFileTbl[8] = { 0x1D001F, 0x1D0020, 0x1D0021, 0x1D0022, 0x1D0023, 0x1D0024, 0x1D001F, 0x1D001F };

const s16 mstory4_scene1TitleXTbl[8][2] = {
    { 25, 98 },
    { 25, 92 },
    { 25, 100 },
    { 25, 97 },
    { 25, 98 },
    { 25, 81 },
    { 25, 98 },
    { 25, 98 },
};

const s16 mstory4_scene1TitleWidthTbl[2] = { 78, 190 };
