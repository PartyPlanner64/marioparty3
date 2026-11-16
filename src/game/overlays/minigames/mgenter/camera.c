#include "common.h"
#include "game/camera.h"
#include "game/hvq.h"
#include "game/malloc.h"
#include "game/mallocblock.h"

typedef struct CameraViewState {
    f32 rotY;
    f32 posX;
    f32 posZ;
    f32 fov;
    f32 far;
    f32 near;
} CameraViewState;

extern f32 CFanOfs;
extern CameraViewState CFan;
extern f32 CFanLen;

f32 mgenter_cameraFov = 58.0f;
s8 mgenter_cameraLookF = 0;

extern s16 mgenter_mgPicAnim;
extern s16 mgenter_mgPicSpr;
extern s16 mgenter_mgPicBufNo;
extern u8 *mgenter_mgPicBufTbl[3];
extern u8 *mgenter_mgPicOrigData;
extern f32 mgenter_cameraNear;
extern s16 mgenter_padNo;
extern f32 mgenter_cameraFar;
extern Vec mgenter_cameraTarget;
extern Vec mgenter_cameraPos;

void mgenter_CameraDebugExec(void) {
    f32 dz;
    f32 zoom;
    f32 speed;
    f32 x, y;
    f32 length;
    s8 stick;

    if (HuPadBtnDown[1] & R_TRIG) {
        osSyncPrintf("\t{\n\t{%4.1f,%4.1f,%4.1f},\n", CRot.x, CRot.y, CRot.z);
        osSyncPrintf("\t{%4.1f,%4.1f,%4.1f},\n", Center.x, Center.y, Center.z);
        osSyncPrintf("\t%4.1f,%4.1f\n\t},\n", CZoom, mgenter_cameraFov);
    }
    if (HuPadBtn[1] & U_CBUTTONS) {
        if (HuPadBtn[1] & Z_TRIG) {
            zoom = CZoom;
            zoom += 30.0f;
            CZoom = zoom;
        } else {
            zoom = CZoom;
            zoom += 10.0f;
            CZoom = zoom;
        }
    }
    if ((HuPadBtn[1] & D_CBUTTONS) && (CZoom - 10.0f != 0.0f)) {
        if (HuPadBtn[1] & Z_TRIG) {
            CZoom -= 30.0f;
        } else {
            zoom = CZoom;
            CZoom = zoom - 10.0f;
        }
    }
    if (HuPadBtn[1] & L_CBUTTONS) {
        mgenter_cameraFov += 1.0f;
    }
    if (HuPadBtn[1] & R_CBUTTONS) {
        mgenter_cameraFov -= 1.0f;
    }
    Hu3DCameraPerspectiveSet(0, mgenter_cameraFov, mgenter_cameraNear, mgenter_cameraFar);
    x = CRot.x;
    y = CRot.y;
    if (HuPadBtn[1] & Z_TRIG) {
        speed = 5.0f;
    } else {
        speed = 2.0f;
    }
    y += (-HuPadStkX[1] / 30) * speed;
    if (y >= 360.0f) {
        y -= 360.0f;
    } else if (y < 0.0f) {
        y += 360.0f;
    }
    CRot.y = y;
    stick = HuPadStkY[1];
    stick /= 30;
    x += stick * speed;
    if (x >= 360.0f) {
        x -= 360.0f;
    } else if (x < 0.0f) {
        x += 360.0f;
    }
    CRot.x = x;
    if (HuPadBtn[1] & Z_TRIG) {
        speed = 10.0f;
    } else {
        speed = 2.0f;
    }
    if (HuPadBtn[1] & U_JPAD) {
        Center.x += sindf(y) * sindf(x) * -speed;
        Center.y += cosdf(x) * -speed;
        Center.z += cosdf(y) * sindf(x) * -speed;
    } else if (HuPadBtn[1] & D_JPAD) {
        Center.x += sindf(y) * sindf(x) * speed;
        Center.y += cosdf(x) * speed;
        Center.z += cosdf(y) * sindf(x) * speed;
    } else if (HuPadBtn[1] & L_JPAD) {
        x = gCameraList->pos.z - Center.z;
        dz = -(gCameraList->pos.x - Center.x);
        length = 1.0f / HuSqrtf(x * x + dz * dz);
        Center.x += x * length * speed;
        Center.y += 0.0f;
        Center.z += dz * length * speed;
    } else if (HuPadBtn[1] & R_JPAD) {
        x = -(gCameraList->pos.z - Center.z);
        dz = gCameraList->pos.x - Center.x;
        length = 1.0f / HuSqrtf(x * x + dz * dz);
        Center.x += x * length * speed;
        Center.y += 0.0f;
        Center.z += dz * length * speed;
    }
}

void mgenter_CameraProc(void) {
    Vec pos, at, up;
    f32 rotX, rotY, rotZ;
    f32 upX, upY, upZ;
    f32 dx, dy, dz;
    f32 length;

    while (1) {
        if (mgenter_cameraLookF == 0) {
            rotX = CRot.x;
            rotY = CRot.y;
            rotZ = CRot.z;
            pos.x = sindf(rotY) * cosdf(rotX) * CZoom + Center.x;
            pos.y = -sindf(rotX) * CZoom + Center.y;
            pos.z = cosdf(rotY) * cosdf(rotX) * CZoom + Center.z;
            at.x = Center.x;
            at.y = Center.y;
            at.z = Center.z;
            upX = sindf(rotY) * sindf(rotX);
            upY = cosdf(rotX);
            upZ = cosdf(rotY) * sindf(rotX);
            dx = at.x - pos.x;
            dy = at.y - pos.y;
            dz = at.z - pos.z;
            length = HuSqrtf(dx * dx + dy * dy + dz * dz);
            dx /= length;
            dy /= length;
            dz /= length;
            up.x = upX * (dx * dx + (1.0f - dx * dx) * cosdf(rotZ)) +
                   upY * (dx * dy * (1.0f - cosdf(rotZ)) - dz * sindf(rotZ)) +
                   upZ * (dx * dz * (1.0f - cosdf(rotZ)) + dy * sindf(rotZ));
            up.y = upX * (dx * dy * (1.0f - cosdf(rotZ)) + dz * sindf(rotZ)) +
                   upY * (dy * dy + (1.0f - dy * dy) * cosdf(rotZ)) +
                   upZ * (dy * dz * (1.0f - cosdf(rotZ)) - dx * sindf(rotZ));
            up.z = upX * (dx * dz * (1.0f - cosdf(rotZ)) - dy * sindf(rotZ)) +
                   upY * (dy * dz * (1.0f - cosdf(rotZ)) + dx * sindf(rotZ)) +
                   upZ * (dz * dz + (1.0f - dz * dz) * cosdf(rotZ));
        } else {
            pos = mgenter_cameraPos;
            at = mgenter_cameraTarget;
            up.x = 0.0f;
            up.y = 1.0f;
            up.z = 0.0f;
        }
        CFan.posX = pos.x;
        CFan.posZ = pos.z;
        CFan.rotY = CRot.y;
        CFan.fov = gCameraList->fov;
        CFan.far = CFanLen;
        CFan.near = CFanOfs;
        Hu3DCameraPosSetV(0, &pos, &at, &up);
        Hu3DCamUpdateMtx(0);
        HuPrcVSleep();
    }
}

s16 mgenter_MgPicCreate(void) {
    s16 sprGrp;
    s16 i;

    mgenter_mgPicAnim = HuSprAnimDataRead(0x12000E);
    sprGrp = espEntry(mgenter_mgPicAnim, 0, 1);
    mgenter_mgPicSpr = sprGrp;
    for (i = 0; i < ARRAY_COUNT(mgenter_mgPicBufTbl); i++) {
        mgenter_mgPicBufTbl[i] = HuMemAllocTag(0x6000, TAG_OVERLAY);
    }
    mgenter_mgPicOrigData = HuSprGet(esprite[sprGrp].unk04, 0)->data->pat->data;
    mgenter_mgPicBufNo = 0;
    espDispOff(sprGrp);
    return sprGrp;
}

void mgenter_MgPicLoad(s16 arg0) {
    u8 **sprData;
    u8 *palData;
    void *buf;

    sprData = DataRead(arg0 | 0x170000);
    palData = DataRead((arg0 + 1) | 0x170000);
    hvqMpsInit1(0xFF);
    hvqMpsDecodeStart1(palData);
    buf = HuMemMemoryAllocPerm(0xC00);
    hvqMpsDecode1(sprData, (u16 *)mgenter_mgPicBufTbl[mgenter_mgPicBufNo], 0x80, buf);
    HuMemMemoryFreePerm(buf);
    DataClose(sprData);
    DataClose(palData);
    HuSprGet(esprite[mgenter_mgPicSpr].unk04, 0)->data->pat->data =
        mgenter_mgPicBufTbl[mgenter_mgPicBufNo];
    mgenter_mgPicBufNo++;
    if (mgenter_mgPicBufNo >= ARRAY_COUNT(mgenter_mgPicBufTbl)) {
        mgenter_mgPicBufNo = 0;
    }
    espDispOn(mgenter_mgPicSpr);
}

void mgenter_MgPicKill(void) {
    s16 i;

    HuSprGet(esprite[mgenter_mgPicSpr].unk04, 0)->data->pat->data = mgenter_mgPicOrigData;
    espKill(mgenter_mgPicSpr);
    HuSprAnimKill(mgenter_mgPicAnim);
    for (i = 0; i < ARRAY_COUNT(mgenter_mgPicBufTbl); i++) {
        HuMemFree(mgenter_mgPicBufTbl[i]);
    }
}

void mgenter_DpadStickSet(void) {
    f32 y = 0.0f;
    f32 x = 0.0f;
    f32 length;

    if (HuPadBtn[mgenter_padNo] & L_JPAD) {
        x = -1.0f;
    }
    if (HuPadBtn[mgenter_padNo] & R_JPAD) {
        x += 1.0f;
    }
    if (HuPadBtn[mgenter_padNo] & U_JPAD) {
        y += 1.0f;
    }
    if (HuPadBtn[mgenter_padNo] & D_JPAD) {
        y += -1.0f;
    }
    if ((x == 0.0f) & (y == 0.0f)) {
        return;
    }
    length = HuSqrtf(x * x + y * y);
    HuPadStkX[mgenter_padNo] = x / length * 50.0f;
    HuPadStkY[mgenter_padNo] = y / length * 50.0f;
}
