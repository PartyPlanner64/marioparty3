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

extern s8 D_800D2132_main;
void func_80107F50_option(s32 animFile, s16 x, s16 y);
omObjData *func_80107758_option(Vec *, Vec *, s32);
void func_80106508_option(Vec *, Vec *, Vec *);
void func_801059D0_option(void);
s32 func_80105FF8_option(Vec *, Vec *, Vec *);
omObjData *func_80106F88_option(Vec *, Vec *, s32);
void func_8010744C_option(omObjData *);
void func_80107B80_option(Vec *, Vec *, f32, Vec *);
void func_80107D64_option(Vec *, Vec *, f32, Vec *);
void func_80106C7C_option(omObjData *);
void func_80107058_option(omObjData *);
void func_801077BC_option(omObjData *);
void func_80105E40_option(void);
void func_80108A68_option(void);
void func_80108AAC_option(void);
void func_80108AF0_option(void);
omObjData *func_8010737C_option(Vec *, Vec *, s32);

OptCam D_801146F0_option BSS;
s32 D_80114764_option BSS;

void func_801059D0_option(void) {
    omInitObjMan(0x40, 0x20);
    func_800142A0_main(0x20);
    func_8004A208_main();
    func_8000B5F0_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    {
        Vec pos = { 0.0f, 0.0f, 100.0f };
        Vec at = { 0.0f, 0.0f, 0.0f };
        Vec up = { 0.0f, 1.0f, 0.0f };

        ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
        ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
        Hu3DCameraPerspectiveSet(0, 41.0f, 80.0f, 8000.0f);
        Hu3DCameraPosSetV(0, &pos, &at, &up);
    }
    func_80030030_main(1.0f);
    pfInit();
    HuWinInit();
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(0, 128, 128, 128);
    Hu3DGLightColorSet(1, 64, 64, 96);
    Hu3DGLightColorSet(2, 0, 0, 0);
    Hu3DGLightColorSet(3, 0, 0, 0);
    Hu3DGLightDirSet(1, 0.0f, 64.0f, 192.0f);
    D_800D2132_main = 0;
}

const char D_80113A04_option[] = "";

void func_80105C14_option(void) {
    func_801059D0_option();
    func_80108A68_option();
}

void func_80105C38_option(void) {
    func_801059D0_option();
    func_80108A68_option();
}

void func_80105C5C_option(void) {
    func_801059D0_option();
    func_80108A68_option();
}

void func_80105C80_option(void) {
    func_801059D0_option();
    func_80108A68_option();
}

void func_80105CA4_option(void) {
    func_801059D0_option();
    func_80108AAC_option();
}

void func_80105CC8_option(void) {
    func_801059D0_option();
    func_80108AAC_option();
}

void func_80105CEC_option(void) {
    func_801059D0_option();
    func_80108AF0_option();
}

void func_80105D10_option(void) {
    D_801146F0_option.prcObj = NULL;
    D_801146F0_option.obj = NULL;
    D_801146F0_option.camId = -1;
    D_801146F0_option.fov = 50.0f;
    D_801146F0_option.nearPlane = 80.0f;
    D_801146F0_option.farPlane = 4000.0f;
}

void func_80105D5C_option(f32 fov, f32 nearPlane, f32 farPlane) {
    D_801146F0_option.fov = fov;
    D_801146F0_option.nearPlane = nearPlane;
    D_801146F0_option.farPlane = farPlane;
}

void func_80105D74_option(void) {
    while (1) {
        func_80012E54_main(0);
        HuPrcVSleep();
    }
}

void func_80105DA0_option(s32 camId, f32 fov) {
    if (D_801146F0_option.prcObj != NULL) {
        func_80105E40_option();
    }
    func_80013320_main(camId, 0);
    D_801146F0_option.camId = camId;
    D_801146F0_option.fov = fov;
    Hu3DCameraPerspectiveSet(0, fov, D_801146F0_option.nearPlane, D_801146F0_option.farPlane);
    func_80012E54_main(0);
    D_801146F0_option.prcObj = omAddPrcObj(func_80105D74_option, 0x5000, 0x2000, 0);
}

void func_80105E40_option(void) {
    if (D_801146F0_option.prcObj != NULL) {
        omDelPrcObj(D_801146F0_option.prcObj);
    } else {
        while (1) {
            HuPrcVSleep();
        }
    }

    if (D_801146F0_option.camId != -1) {
        func_80013350_main(0);
        D_801146F0_option.camId = -1;
    }

    D_801146F0_option.prcObj = NULL;
}

void func_80105EB8_option(void) {
    while (1) {
        Hu3DCameraPosSetV(0, &D_801146F0_option.pos, &D_801146F0_option.at, &D_801146F0_option.up);
        Hu3DCamUpdateMtx(0);
        HuPrcVSleep();
    }
}

void func_80105F08_option(f32 fov) {
    Vec pos, at, up;

    D_801146F0_option.fov = fov;
    if (D_801146F0_option.camId != -1) {
        func_80105FF8_option(&pos, &at, &up);
        HuVecCopy3F(&D_801146F0_option.pos, &pos);
        HuVecCopy3F(&D_801146F0_option.at, &at);
        HuVecCopy3F(&D_801146F0_option.up, &up);
    }
    if (D_801146F0_option.prcObj != NULL) {
        func_80105E40_option();
    }
    Hu3DCameraPosSetV(0, &D_801146F0_option.pos, &D_801146F0_option.at, &D_801146F0_option.up);
    Hu3DCamUpdateMtx(0);
    Hu3DCameraPerspectiveSet(0, D_801146F0_option.fov, D_801146F0_option.nearPlane, D_801146F0_option.farPlane);
    D_801146F0_option.prcObj = omAddPrcObj(func_80105EB8_option, 0x5000, 0x2000, 0);
}

s32 func_80105FF8_option(Vec *pos, Vec *at, Vec *up) {
    HmfData *hmf;
    HmfData_UnkBC *cam;
    f32 angle;
    f32 dx, dy, dz;
    f32 upX, upY, upZ;
    f32 length;

    if (D_801146F0_option.camId == -1) {
        HuVecCopy3F(pos, &D_801146F0_option.pos);
        HuVecCopy3F(at, &D_801146F0_option.at);
        HuVecCopy3F(up, &D_801146F0_option.up);
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

void func_80106508_option(Vec *pos, Vec *at, Vec *up) {
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
    HuVecCopy3F(&D_801146F0_option.pos, pos);
    HuVecCopy3F(&D_801146F0_option.at, at);
    HuVecCopy3F(&D_801146F0_option.up, up);
}

void func_80106998_option(omObjData *obj) {
    Vec pos, at, up, start, end;
    f32 t, clamped;

    t = (f32)D_801146F0_option.frame / D_801146F0_option.duration;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        clamped = 1.0f;
    } else {
        clamped = t;
    }
    HuVecCopy3F(&start, &D_801146F0_option.startPos);
    HuVecCopy3F(&end, &D_801146F0_option.endPos);
    HuVecCopyXYZ(&pos, (end.x - start.x) * clamped + start.x, (end.y - start.y) * clamped + start.y,
                 (end.z - start.z) * clamped + start.z);
    HuVecCopy3F(&start, &D_801146F0_option.startAt);
    HuVecCopy3F(&end, &D_801146F0_option.endAt);
    HuVecCopyXYZ(&at, (end.x - start.x) * clamped + start.x, (end.y - start.y) * clamped + start.y,
                 (end.z - start.z) * clamped + start.z);
    if (D_801146F0_option.frame > D_801146F0_option.duration) {
        omDelObj(obj);
        func_80106508_option(&D_801146F0_option.endPos, &D_801146F0_option.endAt, &up);
        D_801146F0_option.obj = NULL;
    } else {
        D_801146F0_option.frame++;
        func_80106508_option(&pos, &at, &up);
    }
}

void func_80106B78_option(void) {
    if (D_801146F0_option.obj != NULL) {
        omDelObj(D_801146F0_option.obj);
    }
    D_801146F0_option.obj = NULL;
}

omObjData *func_80106BAC_option(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    func_80106B78_option();
    obj = omAddObj(6, 0, 0, -1, func_80106998_option);
    obj->work[0] = 0;
    obj->work[1] = 0;
    D_801146F0_option.obj = obj;
    D_801146F0_option.frame = 0;
    D_801146F0_option.duration = duration;
    HuVecCopy3F(&D_801146F0_option.startAt, &D_801146F0_option.at);
    HuVecCopy3F(&D_801146F0_option.startPos, &D_801146F0_option.pos);
    HuVecCopyXYZ(&D_801146F0_option.endAt, at->x, at->y, at->z);
    HuVecCopyXYZ(&D_801146F0_option.endPos, pos->x, pos->y, pos->z);
    return obj;
}

void func_80106C7C_option(omObjData *obj) {
    Vec pos, at, up, startPos, endPos, direction, startAt, endAt, startDir, endDir;
    f32 t, clamped, startLength, length;

    t = (f32)D_801146F0_option.frame / D_801146F0_option.duration;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        clamped = 1.0f;
    } else {
        clamped = t;
    }
    HuVecCopy3F(&startPos, &D_801146F0_option.startPos);
    HuVecCopy3F(&endPos, &D_801146F0_option.endPos);
    HuVecCopyXYZ(&pos, (endPos.x - startPos.x) * clamped + startPos.x,
                 (endPos.y - startPos.y) * clamped + startPos.y,
                 (endPos.z - startPos.z) * clamped + startPos.z);
    HuVecCopy3F(&startAt, &D_801146F0_option.startAt);
    HuVecCopy3F(&endAt, &D_801146F0_option.endAt);
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
    if (D_801146F0_option.frame > D_801146F0_option.duration) {
        omDelObj(obj);
        func_80106508_option(&D_801146F0_option.endPos, &D_801146F0_option.endAt, &up);
        D_801146F0_option.obj = NULL;
    } else {
        D_801146F0_option.frame++;
        func_80106508_option(&pos, &at, &up);
    }
}

omObjData *func_80106F88_option(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    func_80106B78_option();
    obj = omAddObj(6, 0, 0, -1, func_80106C7C_option);
    obj->work[0] = 0;
    obj->work[1] = 0;
    D_801146F0_option.obj = obj;
    D_801146F0_option.frame = 0;
    D_801146F0_option.duration = duration;
    HuVecCopy3F(&D_801146F0_option.startAt, &D_801146F0_option.at);
    HuVecCopy3F(&D_801146F0_option.startPos, &D_801146F0_option.pos);
    HuVecCopyXYZ(&D_801146F0_option.endAt, at->x, at->y, at->z);
    HuVecCopyXYZ(&D_801146F0_option.endPos, pos->x, pos->y, pos->z);
    return obj;
}

void func_80107058_option(omObjData *obj) {
    Vec pos, at, up, startPos, endPos, direction, startAt, endAt, startDir, endDir;
    f32 t, clamped, startLength, length;

    t = (f32)D_801146F0_option.frame / D_801146F0_option.duration;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        clamped = 1.0f;
    } else {
        clamped = t;
    }
    clamped = sindf(clamped * 90.0f);
    HuVecCopy3F(&startPos, &D_801146F0_option.startPos);
    HuVecCopy3F(&endPos, &D_801146F0_option.endPos);
    HuVecCopyXYZ(&pos, (endPos.x - startPos.x) * clamped + startPos.x,
                 (endPos.y - startPos.y) * clamped + startPos.y,
                 (endPos.z - startPos.z) * clamped + startPos.z);
    HuVecCopy3F(&startAt, &D_801146F0_option.startAt);
    HuVecCopy3F(&endAt, &D_801146F0_option.endAt);
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
    if (D_801146F0_option.frame > D_801146F0_option.duration) {
        omDelObj(obj);
        func_80106508_option(&D_801146F0_option.endPos, &D_801146F0_option.endAt, &up);
        D_801146F0_option.obj = NULL;
    } else {
        D_801146F0_option.frame++;
        func_80106508_option(&pos, &at, &up);
    }
}

omObjData *func_8010737C_option(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    func_80106B78_option();
    obj = omAddObj(6, 0, 0, -1, func_80107058_option);
    obj->work[0] = 0;
    obj->work[1] = 0;
    D_801146F0_option.obj = obj;
    D_801146F0_option.frame = 0;
    D_801146F0_option.duration = duration;
    HuVecCopy3F(&D_801146F0_option.startAt, &D_801146F0_option.at);
    HuVecCopy3F(&D_801146F0_option.startPos, &D_801146F0_option.pos);
    HuVecCopyXYZ(&D_801146F0_option.endAt, at->x, at->y, at->z);
    HuVecCopyXYZ(&D_801146F0_option.endPos, pos->x, pos->y, pos->z);
    return obj;
}

void func_8010744C_option(omObjData *obj) {
    Vec pos, at, up, startPos, endPos, direction, startAt, endAt, startDir, endDir;
    f32 t, clamped, startLength, angleT;

    t = (f32)D_801146F0_option.frame / D_801146F0_option.duration;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        clamped = 1.0f;
    } else {
        clamped = t;
    }
    HuVecCopy3F(&startPos, &D_801146F0_option.startPos);
    HuVecCopy3F(&endPos, &D_801146F0_option.endPos);
    HuVecCopyXYZ(&pos, (endPos.x - startPos.x) * clamped + startPos.x,
                 (endPos.y - startPos.y) * clamped + startPos.y,
                 (endPos.z - startPos.z) * clamped + startPos.z);
    HuVecCopy3F(&startAt, &D_801146F0_option.startAt);
    HuVecCopy3F(&endAt, &D_801146F0_option.endAt);
    HuVecCopyXYZ(&at, (endAt.x - startAt.x) * clamped + startAt.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 (endAt.z - startAt.z) * clamped + startAt.z);
    HuVecCopyXYZ(&startDir, startAt.x - startPos.x, 0.0f, startAt.z - startPos.z);
    HuVecCopyXYZ(&endDir, endAt.x - endPos.x, 0.0f, endAt.z - endPos.z);
    angleT = sindf(clamped * 90.0f);
    if (D_80114764_option != 0) {
        func_80107B80_option(&startDir, &endDir, angleT, &direction);
    } else {
        func_80107D64_option(&startDir, &endDir, angleT, &direction);
    }
    startLength = HuVecGetLength3F(&startDir);
    t = (HuVecGetLength3F(&endDir) - startLength) * clamped + startLength;
    HuVecCopyXYZ(&at, t * direction.x + pos.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 t * direction.z + pos.z);
    if (D_801146F0_option.frame > D_801146F0_option.duration) {
        omDelObj(obj);
        func_80106508_option(&D_801146F0_option.endPos, &D_801146F0_option.endAt, &up);
        D_801146F0_option.obj = NULL;
    } else {
        D_801146F0_option.frame++;
        func_80106508_option(&pos, &at, &up);
    }
}

omObjData *func_80107758_option(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    obj = func_80106F88_option(pos, at, duration);
    obj->func = func_8010744C_option;
    D_80114764_option = 1;
    return obj;
}

omObjData *func_8010778C_option(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    obj = func_80106F88_option(pos, at, duration);
    obj->func = func_8010744C_option;
    D_80114764_option = 0;
    return obj;
}

void func_801077BC_option(omObjData *obj) {
    Vec pos, at, up, startPos, endPos, direction, startAt, endAt, startDir, endDir;
    f32 t, clamped, startLength, angleT;

    t = (f32)D_801146F0_option.frame / D_801146F0_option.duration;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        clamped = 1.0f;
    } else {
        clamped = t;
    }
    HuVecCopy3F(&startPos, &D_801146F0_option.startPos);
    HuVecCopy3F(&endPos, &D_801146F0_option.endPos);
    HuVecCopyXYZ(&pos, (endPos.x - startPos.x) * clamped + startPos.x,
                 (endPos.y - startPos.y) * clamped + startPos.y,
                 (endPos.z - startPos.z) * clamped + startPos.z);
    HuVecCopy3F(&startAt, &D_801146F0_option.startAt);
    HuVecCopy3F(&endAt, &D_801146F0_option.endAt);
    HuVecCopyXYZ(&at, (endAt.x - startAt.x) * clamped + startAt.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 (endAt.z - startAt.z) * clamped + startAt.z);
    HuVecCopyXYZ(&startDir, startAt.x - startPos.x, 0.0f, startAt.z - startPos.z);
    HuVecCopyXYZ(&endDir, endAt.x - endPos.x, 0.0f, endAt.z - endPos.z);
    angleT = sindf(clamped * 90.0f);
    if (D_80114764_option != 0) {
        func_80107B80_option(&startDir, &endDir, angleT, &direction);
    } else {
        func_80107D64_option(&startDir, &endDir, angleT, &direction);
    }
    startLength = HuVecGetLength3F(&startDir);
    t = (HuVecGetLength3F(&endDir) - startLength) * angleT + startLength;
    HuVecCopyXYZ(&at, t * direction.x + pos.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 t * direction.z + pos.z);
    if (D_801146F0_option.frame > D_801146F0_option.duration) {
        omDelObj(obj);
        func_80106508_option(&D_801146F0_option.endPos, &D_801146F0_option.endAt, &up);
        D_801146F0_option.obj = NULL;
    } else {
        D_801146F0_option.frame++;
        func_80106508_option(&pos, &at, &up);
    }
}

omObjData *func_80107AD4_option(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    obj = func_80106F88_option(pos, at, duration);
    obj->func = func_801077BC_option;
    D_80114764_option = 1;
    return obj;
}

omObjData *func_80107B08_option(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    obj = func_80106F88_option(pos, at, duration);
    obj->func = func_801077BC_option;
    D_80114764_option = 0;
    return obj;
}

f32 func_80107B38_option(f32 x1, f32 y1, f32 x2, f32 y2) {
    return -(atan2df(y2 - y1, x2 - x1) - 90.0f);
}

void func_80107B80_option(Vec *start, Vec *end, f32 weight, Vec *out) {
    f32 startAngle;
    f32 endAngle;
    f32 angle;
    f32 backwardTarget;

    startAngle = func_80107B38_option(0.0f, 0.0f, start->x, start->z);
    if (startAngle < 0.0f) {
        startAngle += 360.0f;
    }
    endAngle = func_80107B38_option(0.0f, 0.0f, end->x, end->z);
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

void func_80107D64_option(Vec *start, Vec *end, f32 weight, Vec *out) {
    f32 startAngle;
    f32 endAngle;
    f32 angle;
    f32 difference;
    f32 target;

    startAngle = func_80107B38_option(0.0f, 0.0f, start->x, start->z);
    if (startAngle < 0.0f) {
        startAngle += 360.0f;
    }
    endAngle = func_80107B38_option(0.0f, 0.0f, end->x, end->z);
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
