#include "common.h"
#include "option.h"
#include "game/overlays/minigame.h"
#include "game/vibrator.h"
#include "game/mallocblock.h"
#include "game/pad.h"
#include "game/saveload.h"

typedef struct {
    /* 0x00 */ Process *prcObj;
    /* 0x04 */ Vec pos;
    /* 0x10 */ Vec at;
    /* 0x1C */ Vec up;
    /* 0x28 */ f32 fov;
    /* 0x2C */ f32 nearPlane;
    /* 0x30 */ f32 farPlane;
    /* 0x34 */ s16 camId;
    /* 0x38 */ omObjData *obj;
    /* 0x3C */ Vec startPos;
    /* 0x48 */ Vec startAt;
    /* 0x54 */ Vec endPos;
    /* 0x60 */ Vec endAt;
    /* 0x6C */ s32 frame;
    /* 0x70 */ s32 duration;
} OptCam; // sizeof 0x74

extern s8 omSysPauseReadyF;
void option_MgRecordExec(s32 animFile, s16 x, s16 y);
omObjData *option_CameraTurnMove(Vec *, Vec *, s32);
void option_CameraPosSet(Vec *, Vec *, Vec *);
void option_ObjectInit(void);
s32 option_CameraPosGet(Vec *, Vec *, Vec *);
omObjData *option_CameraMove(Vec *, Vec *, s32);
void option_CameraTurnObjMain(omObjData *);
void option_CameraDirLerp(Vec *, Vec *, f32, Vec *);
void option_CameraDirLerpRev(Vec *, Vec *, f32, Vec *);
void option_CameraMoveObjMain(omObjData *);
void option_CameraEaseObjMain(omObjData *);
void option_CameraTurnEaseObjMain(omObjData *);
void option_CameraProcKill(void);
void option_RoomCreate(void);
void option_SoundRoomCreate(void);
void option_RecordRoomCreate(void);
omObjData *option_CameraEaseMove(Vec *, Vec *, s32);

OptCam option_cameraWork BSS;
s32 option_cameraTurnDir BSS;

void option_ObjectInit(void) {
    omInitObjMan(0x40, 0x20);
    Hu3DSprModelInit(0x20);
    omGameSysInit();
    CamSetupInit(1);
    ScissorSet(0, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    {
        Vec pos = { 0.0f, 0.0f, 100.0f };
        Vec at = { 0.0f, 0.0f, 0.0f };
        Vec up = { 0.0f, 1.0f, 0.0f };

        ScissorSet(0, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
        ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
        Hu3DCameraPerspectiveSet(0, 41.0f, 80.0f, 8000.0f);
        Hu3DCameraPosSetV(0, &pos, &at, &up);
    }
    Hu3DMotionGlobalSpeedSet(1.0f);
    pfInit();
    HuWinInit();
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(0, 128, 128, 128);
    Hu3DGLightColorSet(1, 64, 64, 96);
    Hu3DGLightColorSet(2, 0, 0, 0);
    Hu3DGLightColorSet(3, 0, 0, 0);
    Hu3DGLightDirSet(1, 0.0f, 64.0f, 192.0f);
    omSysPauseReadyF = 0;
}

const char option_emptyStr[] = "";

void option_RoomObjectSetup(void) {
    option_ObjectInit();
    option_RoomCreate();
}

void option_RoomFromLObjectSetup(void) {
    option_ObjectInit();
    option_RoomCreate();
}

void option_RoomFromRObjectSetup(void) {
    option_ObjectInit();
    option_RoomCreate();
}

void option_RoomFromRecordObjectSetup(void) {
    option_ObjectInit();
    option_RoomCreate();
}

void option_SoundRoomLObjectSetup(void) {
    option_ObjectInit();
    option_SoundRoomCreate();
}

void option_SoundRoomRObjectSetup(void) {
    option_ObjectInit();
    option_SoundRoomCreate();
}

void option_RecordRoomObjectSetup(void) {
    option_ObjectInit();
    option_RecordRoomCreate();
}

void option_CameraInit(void) {
    option_cameraWork.prcObj = NULL;
    option_cameraWork.obj = NULL;
    option_cameraWork.camId = -1;
    option_cameraWork.fov = 50.0f;
    option_cameraWork.nearPlane = 80.0f;
    option_cameraWork.farPlane = 4000.0f;
}

void option_CameraPerspectiveSet(f32 fov, f32 nearPlane, f32 farPlane) {
    option_cameraWork.fov = fov;
    option_cameraWork.nearPlane = nearPlane;
    option_cameraWork.farPlane = farPlane;
}

void option_CameraMotionProc(void) {
    while (1) {
        Hu3DCameraMotionExec(0);
        HuPrcVSleep();
    }
}

void option_CameraMotionStart(s32 camId, f32 fov) {
    if (option_cameraWork.prcObj != NULL) {
        option_CameraProcKill();
    }
    Hu3DCameraMotionSet(camId, 0);
    option_cameraWork.camId = camId;
    option_cameraWork.fov = fov;
    Hu3DCameraPerspectiveSet(0, fov, option_cameraWork.nearPlane, option_cameraWork.farPlane);
    Hu3DCameraMotionExec(0);
    option_cameraWork.prcObj = omAddPrcObj(option_CameraMotionProc, 0x5000, 0x2000, 0);
}

void option_CameraProcKill(void) {
    if (option_cameraWork.prcObj != NULL) {
        omDelPrcObj(option_cameraWork.prcObj);
    } else {
        while (1) {
            HuPrcVSleep();
        }
    }

    if (option_cameraWork.camId != -1) {
        Hu3DCameraMotionOff(0);
        option_cameraWork.camId = -1;
    }

    option_cameraWork.prcObj = NULL;
}

void option_CameraProc(void) {
    while (1) {
        Hu3DCameraPosSetV(0, &option_cameraWork.pos, &option_cameraWork.at, &option_cameraWork.up);
        Hu3DCamUpdateMtx(0);
        HuPrcVSleep();
    }
}

void option_CameraManualStart(f32 fov) {
    Vec pos, at, up;

    option_cameraWork.fov = fov;
    if (option_cameraWork.camId != -1) {
        option_CameraPosGet(&pos, &at, &up);
        HuVecCopy3F(&option_cameraWork.pos, &pos);
        HuVecCopy3F(&option_cameraWork.at, &at);
        HuVecCopy3F(&option_cameraWork.up, &up);
    }
    if (option_cameraWork.prcObj != NULL) {
        option_CameraProcKill();
    }
    Hu3DCameraPosSetV(0, &option_cameraWork.pos, &option_cameraWork.at, &option_cameraWork.up);
    Hu3DCamUpdateMtx(0);
    Hu3DCameraPerspectiveSet(0, option_cameraWork.fov, option_cameraWork.nearPlane, option_cameraWork.farPlane);
    option_cameraWork.prcObj = omAddPrcObj(option_CameraProc, 0x5000, 0x2000, 0);
}

s32 option_CameraPosGet(Vec *pos, Vec *at, Vec *up) {
    HmfData *hmf;
    HmfData_UnkBC *cam;
    f32 angle;
    f32 dx, dy, dz;
    f32 upX, upY, upZ;
    f32 length;

    if (option_cameraWork.camId == -1) {
        HuVecCopy3F(pos, &option_cameraWork.pos);
        HuVecCopy3F(at, &option_cameraWork.at);
        HuVecCopy3F(up, &option_cameraWork.up);
        return 0;
    }
    hmf = Hu3DData[gCameraList->unk4].hmf;
    if (hmf == NULL || hmf->unkBC == NULL) {
        while (1) {
            HuPrcVSleep();
        }
    }
    cam = hmf->unkBC;
    pos->x = cam->unk08;
    pos->y = cam->unk0C;
    pos->z = cam->unk10;
    at->x = cam->unk14;
    at->y = cam->unk18;
    at->z = cam->unk1C;
    angle = -90.0f;
    dx = at->x - pos->x;
    dy = at->y - pos->y;
    dz = at->z - pos->z;
    length = dx * dx + dy * dy + dz * dz;
    length = HuSqrtf(length);
    dx /= length;
    dy /= length;
    dz /= length;
    upX = dy * dz - dz * (dy + 1.0f);
    upY = dz * dx - dz * dx;
    upZ = dx * (dy + 1.0f) - dy * dx;
    up->x = upX * (dx * dx + (1.0f - dx * dx) * cosdf(angle)) +
            upY * (dx * dy * (1.0f - cosdf(angle)) - dz * sindf(angle)) +
            upZ * (dx * dz * (1.0f - cosdf(angle)) + dy * sindf(angle));
    up->y = upX * (dx * dy * (1.0f - cosdf(angle)) + dz * sindf(angle)) +
            upY * (dy * dy + (1.0f - dy * dy) * cosdf(angle)) +
            upZ * (dy * dz * (1.0f - cosdf(angle)) - dx * sindf(angle));
    up->z = upX * (dx * dz * (1.0f - cosdf(angle)) - dy * sindf(angle)) +
            upY * (dy * dz * (1.0f - cosdf(angle)) + dx * sindf(angle)) +
            upZ * (dz * dz + (1.0f - dz * dz) * cosdf(angle));
    return 1;
}

void option_CameraPosSet(Vec *pos, Vec *at, Vec *up) {
    f32 angle;
    f32 dx, dy, dz;
    f32 upX, upY, upZ;
    f32 length;

    angle = -90.0f;
    dx = at->x - pos->x;
    dy = at->y - pos->y;
    dz = at->z - pos->z;
    length = dx * dx + dy * dy + dz * dz;
    length = HuSqrtf(length);
    dx /= length;
    dy /= length;
    dz /= length;
    upX = dy * dz - dz * (dy + 1.0f);
    upY = dz * dx - dz * dx;
    upZ = dx * (dy + 1.0f) - dy * dx;
    up->x = upX * (dx * dx + (1.0f - dx * dx) * cosdf(angle)) +
            upY * (dx * dy * (1.0f - cosdf(angle)) - dz * sindf(angle)) +
            upZ * (dx * dz * (1.0f - cosdf(angle)) + dy * sindf(angle));
    up->y = upX * (dx * dy * (1.0f - cosdf(angle)) + dz * sindf(angle)) +
            upY * (dy * dy + (1.0f - dy * dy) * cosdf(angle)) +
            upZ * (dy * dz * (1.0f - cosdf(angle)) - dx * sindf(angle));
    up->z = upX * (dx * dz * (1.0f - cosdf(angle)) - dy * sindf(angle)) +
            upY * (dy * dz * (1.0f - cosdf(angle)) + dx * sindf(angle)) +
            upZ * (dz * dz + (1.0f - dz * dz) * cosdf(angle));
    HuVecCopy3F(&option_cameraWork.pos, pos);
    HuVecCopy3F(&option_cameraWork.at, at);
    HuVecCopy3F(&option_cameraWork.up, up);
}

void option_CameraLinearObjMain(omObjData *obj) {
    Vec pos, at, up, start, end;
    f32 t, clamped;

    t = (f32)option_cameraWork.frame / option_cameraWork.duration;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        clamped = 1.0f;
    } else {
        clamped = t;
    }
    HuVecCopy3F(&start, &option_cameraWork.startPos);
    HuVecCopy3F(&end, &option_cameraWork.endPos);
    HuVecCopyXYZ(&pos, (end.x - start.x) * clamped + start.x, (end.y - start.y) * clamped + start.y,
                 (end.z - start.z) * clamped + start.z);
    HuVecCopy3F(&start, &option_cameraWork.startAt);
    HuVecCopy3F(&end, &option_cameraWork.endAt);
    HuVecCopyXYZ(&at, (end.x - start.x) * clamped + start.x, (end.y - start.y) * clamped + start.y,
                 (end.z - start.z) * clamped + start.z);
    if (option_cameraWork.frame > option_cameraWork.duration) {
        omDelObj(obj);
        option_CameraPosSet(&option_cameraWork.endPos, &option_cameraWork.endAt, &up);
        option_cameraWork.obj = NULL;
    } else {
        option_cameraWork.frame++;
        option_CameraPosSet(&pos, &at, &up);
    }
}

void option_CameraMoveKill(void) {
    if (option_cameraWork.obj != NULL) {
        omDelObj(option_cameraWork.obj);
    }
    option_cameraWork.obj = NULL;
}

omObjData *option_CameraLinearMove(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    option_CameraMoveKill();
    obj = omAddObj(6, 0, 0, -1, option_CameraLinearObjMain);
    obj->work[0] = 0;
    obj->work[1] = 0;
    option_cameraWork.obj = obj;
    option_cameraWork.frame = 0;
    option_cameraWork.duration = duration;
    HuVecCopy3F(&option_cameraWork.startAt, &option_cameraWork.at);
    HuVecCopy3F(&option_cameraWork.startPos, &option_cameraWork.pos);
    HuVecCopyXYZ(&option_cameraWork.endAt, at->x, at->y, at->z);
    HuVecCopyXYZ(&option_cameraWork.endPos, pos->x, pos->y, pos->z);
    return obj;
}

void option_CameraMoveObjMain(omObjData *obj) {
    Vec pos, at, up, startPos, endPos, direction, startAt, endAt, startDir, endDir;
    f32 t, clamped, startLength, length;

    t = (f32)option_cameraWork.frame / option_cameraWork.duration;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        clamped = 1.0f;
    } else {
        clamped = t;
    }
    HuVecCopy3F(&startPos, &option_cameraWork.startPos);
    HuVecCopy3F(&endPos, &option_cameraWork.endPos);
    HuVecCopyXYZ(&pos, (endPos.x - startPos.x) * clamped + startPos.x,
                 (endPos.y - startPos.y) * clamped + startPos.y,
                 (endPos.z - startPos.z) * clamped + startPos.z);
    HuVecCopy3F(&startAt, &option_cameraWork.startAt);
    HuVecCopy3F(&endAt, &option_cameraWork.endAt);
    HuVecCopyXYZ(&at, (endAt.x - startAt.x) * clamped + startAt.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 (endAt.z - startAt.z) * clamped + startAt.z);
    HuVecCopyXYZ(&startDir, startAt.x - startPos.x, 0.0f, startAt.z - startPos.z);
    HuVecCopyXYZ(&endDir, endAt.x - endPos.x, 0.0f, endAt.z - endPos.z);
    startLength = HuVecGetLength3F(&startDir);
    t = HuVecGetLength3F(&endDir);
    HuVecCopyXYZ(&direction, at.x - pos.x, 0.0f, at.z - pos.z);
    length = HuVecGetLength3F(&direction);
    t = ((t - startLength) * clamped + startLength) / length;
    HuVecCopyXYZ(&at, t * direction.x + pos.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 t * direction.z + pos.z);
    if (option_cameraWork.frame > option_cameraWork.duration) {
        omDelObj(obj);
        option_CameraPosSet(&option_cameraWork.endPos, &option_cameraWork.endAt, &up);
        option_cameraWork.obj = NULL;
    } else {
        option_cameraWork.frame++;
        option_CameraPosSet(&pos, &at, &up);
    }
}

omObjData *option_CameraMove(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    option_CameraMoveKill();
    obj = omAddObj(6, 0, 0, -1, option_CameraMoveObjMain);
    obj->work[0] = 0;
    obj->work[1] = 0;
    option_cameraWork.obj = obj;
    option_cameraWork.frame = 0;
    option_cameraWork.duration = duration;
    HuVecCopy3F(&option_cameraWork.startAt, &option_cameraWork.at);
    HuVecCopy3F(&option_cameraWork.startPos, &option_cameraWork.pos);
    HuVecCopyXYZ(&option_cameraWork.endAt, at->x, at->y, at->z);
    HuVecCopyXYZ(&option_cameraWork.endPos, pos->x, pos->y, pos->z);
    return obj;
}

void option_CameraEaseObjMain(omObjData *obj) {
    Vec pos, at, up, startPos, endPos, direction, startAt, endAt, startDir, endDir;
    f32 t, clamped, startLength, length;

    t = (f32)option_cameraWork.frame / option_cameraWork.duration;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        clamped = 1.0f;
    } else {
        clamped = t;
    }
    clamped = sindf(clamped * 90.0f);
    HuVecCopy3F(&startPos, &option_cameraWork.startPos);
    HuVecCopy3F(&endPos, &option_cameraWork.endPos);
    HuVecCopyXYZ(&pos, (endPos.x - startPos.x) * clamped + startPos.x,
                 (endPos.y - startPos.y) * clamped + startPos.y,
                 (endPos.z - startPos.z) * clamped + startPos.z);
    HuVecCopy3F(&startAt, &option_cameraWork.startAt);
    HuVecCopy3F(&endAt, &option_cameraWork.endAt);
    HuVecCopyXYZ(&at, (endAt.x - startAt.x) * clamped + startAt.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 (endAt.z - startAt.z) * clamped + startAt.z);
    HuVecCopyXYZ(&startDir, startAt.x - startPos.x, 0.0f, startAt.z - startPos.z);
    HuVecCopyXYZ(&endDir, endAt.x - endPos.x, 0.0f, endAt.z - endPos.z);
    startLength = HuVecGetLength3F(&startDir);
    t = HuVecGetLength3F(&endDir);
    HuVecCopyXYZ(&direction, at.x - pos.x, 0.0f, at.z - pos.z);
    length = HuVecGetLength3F(&direction);
    t = ((t - startLength) * clamped + startLength) / length;
    HuVecCopyXYZ(&at, t * direction.x + pos.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 t * direction.z + pos.z);
    if (option_cameraWork.frame > option_cameraWork.duration) {
        omDelObj(obj);
        option_CameraPosSet(&option_cameraWork.endPos, &option_cameraWork.endAt, &up);
        option_cameraWork.obj = NULL;
    } else {
        option_cameraWork.frame++;
        option_CameraPosSet(&pos, &at, &up);
    }
}

omObjData *option_CameraEaseMove(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    option_CameraMoveKill();
    obj = omAddObj(6, 0, 0, -1, option_CameraEaseObjMain);
    obj->work[0] = 0;
    obj->work[1] = 0;
    option_cameraWork.obj = obj;
    option_cameraWork.frame = 0;
    option_cameraWork.duration = duration;
    HuVecCopy3F(&option_cameraWork.startAt, &option_cameraWork.at);
    HuVecCopy3F(&option_cameraWork.startPos, &option_cameraWork.pos);
    HuVecCopyXYZ(&option_cameraWork.endAt, at->x, at->y, at->z);
    HuVecCopyXYZ(&option_cameraWork.endPos, pos->x, pos->y, pos->z);
    return obj;
}

void option_CameraTurnObjMain(omObjData *obj) {
    Vec pos, at, up, startPos, endPos, direction, startAt, endAt, startDir, endDir;
    f32 t, clamped, startLength, angleT;

    t = (f32)option_cameraWork.frame / option_cameraWork.duration;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        clamped = 1.0f;
    } else {
        clamped = t;
    }
    HuVecCopy3F(&startPos, &option_cameraWork.startPos);
    HuVecCopy3F(&endPos, &option_cameraWork.endPos);
    HuVecCopyXYZ(&pos, (endPos.x - startPos.x) * clamped + startPos.x,
                 (endPos.y - startPos.y) * clamped + startPos.y,
                 (endPos.z - startPos.z) * clamped + startPos.z);
    HuVecCopy3F(&startAt, &option_cameraWork.startAt);
    HuVecCopy3F(&endAt, &option_cameraWork.endAt);
    HuVecCopyXYZ(&at, (endAt.x - startAt.x) * clamped + startAt.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 (endAt.z - startAt.z) * clamped + startAt.z);
    HuVecCopyXYZ(&startDir, startAt.x - startPos.x, 0.0f, startAt.z - startPos.z);
    HuVecCopyXYZ(&endDir, endAt.x - endPos.x, 0.0f, endAt.z - endPos.z);
    angleT = sindf(clamped * 90.0f);
    if (option_cameraTurnDir != 0) {
        option_CameraDirLerp(&startDir, &endDir, angleT, &direction);
    } else {
        option_CameraDirLerpRev(&startDir, &endDir, angleT, &direction);
    }
    startLength = HuVecGetLength3F(&startDir);
    t = (HuVecGetLength3F(&endDir) - startLength) * clamped + startLength;
    HuVecCopyXYZ(&at, t * direction.x + pos.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 t * direction.z + pos.z);
    if (option_cameraWork.frame > option_cameraWork.duration) {
        omDelObj(obj);
        option_CameraPosSet(&option_cameraWork.endPos, &option_cameraWork.endAt, &up);
        option_cameraWork.obj = NULL;
    } else {
        option_cameraWork.frame++;
        option_CameraPosSet(&pos, &at, &up);
    }
}

omObjData *option_CameraTurnMove(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    obj = option_CameraMove(pos, at, duration);
    obj->func = option_CameraTurnObjMain;
    option_cameraTurnDir = 1;
    return obj;
}

omObjData *option_CameraTurnMoveRev(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    obj = option_CameraMove(pos, at, duration);
    obj->func = option_CameraTurnObjMain;
    option_cameraTurnDir = 0;
    return obj;
}

void option_CameraTurnEaseObjMain(omObjData *obj) {
    Vec pos, at, up, startPos, endPos, direction, startAt, endAt, startDir, endDir;
    f32 t, clamped, startLength, angleT;

    t = (f32)option_cameraWork.frame / option_cameraWork.duration;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        clamped = 1.0f;
    } else {
        clamped = t;
    }
    HuVecCopy3F(&startPos, &option_cameraWork.startPos);
    HuVecCopy3F(&endPos, &option_cameraWork.endPos);
    HuVecCopyXYZ(&pos, (endPos.x - startPos.x) * clamped + startPos.x,
                 (endPos.y - startPos.y) * clamped + startPos.y,
                 (endPos.z - startPos.z) * clamped + startPos.z);
    HuVecCopy3F(&startAt, &option_cameraWork.startAt);
    HuVecCopy3F(&endAt, &option_cameraWork.endAt);
    HuVecCopyXYZ(&at, (endAt.x - startAt.x) * clamped + startAt.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 (endAt.z - startAt.z) * clamped + startAt.z);
    HuVecCopyXYZ(&startDir, startAt.x - startPos.x, 0.0f, startAt.z - startPos.z);
    HuVecCopyXYZ(&endDir, endAt.x - endPos.x, 0.0f, endAt.z - endPos.z);
    angleT = sindf(clamped * 90.0f);
    if (option_cameraTurnDir != 0) {
        option_CameraDirLerp(&startDir, &endDir, angleT, &direction);
    } else {
        option_CameraDirLerpRev(&startDir, &endDir, angleT, &direction);
    }
    startLength = HuVecGetLength3F(&startDir);
    t = (HuVecGetLength3F(&endDir) - startLength) * angleT + startLength;
    HuVecCopyXYZ(&at, t * direction.x + pos.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 t * direction.z + pos.z);
    if (option_cameraWork.frame > option_cameraWork.duration) {
        omDelObj(obj);
        option_CameraPosSet(&option_cameraWork.endPos, &option_cameraWork.endAt, &up);
        option_cameraWork.obj = NULL;
    } else {
        option_cameraWork.frame++;
        option_CameraPosSet(&pos, &at, &up);
    }
}

omObjData *option_CameraTurnEaseMove(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    obj = option_CameraMove(pos, at, duration);
    obj->func = option_CameraTurnEaseObjMain;
    option_cameraTurnDir = 1;
    return obj;
}

omObjData *option_CameraTurnEaseMoveRev(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    obj = option_CameraMove(pos, at, duration);
    obj->func = option_CameraTurnEaseObjMain;
    option_cameraTurnDir = 0;
    return obj;
}

f32 option_CameraAngleCalc(f32 x1, f32 y1, f32 x2, f32 y2) {
    return -(atan2df(y2 - y1, x2 - x1) - 90.0f);
}

void option_CameraDirLerp(Vec *start, Vec *end, f32 weight, Vec *out) {
    f32 startAngle;
    f32 endAngle;
    f32 angle;
    f32 backwardTarget;

    startAngle = option_CameraAngleCalc(0.0f, 0.0f, start->x, start->z);
    if (startAngle < 0.0f) {
        startAngle += 360.0f;
    }
    endAngle = option_CameraAngleCalc(0.0f, 0.0f, end->x, end->z);
    if (endAngle < 0.0f) {
        endAngle += 360.0f;
    }
    if (-start->z * end->x + start->x * end->z > 0.0f) {
        backwardTarget = endAngle - startAngle < 0.0f ? endAngle : endAngle - 360.0f;
        angle = (backwardTarget - startAngle) * weight + startAngle;
        if (angle < 0.0f) {
            angle += 360.0f;
        }
    } else {
        f32 difference = endAngle - startAngle;
        // Keep this initialization for the original register allocation.
        f32 forwardTarget = endAngle;

        if (difference > 0.0f) {
            forwardTarget = endAngle;
        } else {
            forwardTarget = endAngle + 360.0f;
        }
        angle = (forwardTarget - startAngle) * weight + startAngle;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
    }
    out->x = sindf(angle);
    out->y = 0;
    out->z = cosdf(angle);
}

void option_CameraDirLerpRev(Vec *start, Vec *end, f32 weight, Vec *out) {
    f32 startAngle;
    f32 endAngle;
    f32 angle;
    f32 difference;
    f32 target;

    startAngle = option_CameraAngleCalc(0.0f, 0.0f, start->x, start->z);
    if (startAngle < 0.0f) {
        startAngle += 360.0f;
    }
    endAngle = option_CameraAngleCalc(0.0f, 0.0f, end->x, end->z);
    if (endAngle < 0.0f) {
        endAngle += 360.0f;
    }
    if (-start->z * end->x + start->x * end->z > 0.0f) {
        if (endAngle - startAngle > 0.0f) {
            target = endAngle;
        } else {
            target = endAngle + 360.0f;
        }
        angle = (target - startAngle) * weight + startAngle;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
    } else {
        difference = endAngle - startAngle;
        target = endAngle;
        if (difference < 0.0f) {
            target = endAngle;
        } else {
            target = endAngle - 360.0f;
        }
        angle = (target - startAngle) * weight + startAngle;
        if (angle < 0.0f) {
            angle += 360.0f;
        }
    }
    out->x = sindf(angle);
    out->y = 0;
    out->z = cosdf(angle);
}
