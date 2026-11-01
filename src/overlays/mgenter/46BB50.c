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

extern f32 D_800CB890_main;
extern CameraViewState D_800CE178_main;
extern f32 D_800D5210_main;
extern f32 D_80109AB0_mgenter;
extern s8 D_80109AB4_mgenter;
extern s16 D_80109B40_mgenter;
extern s16 D_80109B42_mgenter;
extern s16 D_80109B44_mgenter;
extern u8 *D_80109B48_mgenter[3];
extern u8 *D_80109B54_mgenter;
extern f32 D_80109B64_mgenter;
extern s16 D_80109B74_mgenter;
extern f32 D_80109B78_mgenter;
extern Vec D_80109B88_mgenter;
extern Vec D_80109BA4_mgenter;

void func_80108A60_mgenter(void) {
    f32 dz;
    f32 zoom;
    f32 speed;
    f32 x, y;
    f32 length;
    s8 stick;

    if (D_800D5558_main[1] & R_TRIG) {
        osSyncPrintf("\t{\n\t{%4.1f,%4.1f,%4.1f},\n", CRot.x, CRot.y, CRot.z);
        osSyncPrintf("\t{%4.1f,%4.1f,%4.1f},\n", Center.x, Center.y, Center.z);
        osSyncPrintf("\t%4.1f,%4.1f\n\t},\n", CZoom, D_80109AB0_mgenter);
    }
    if (D_800CDA7C_main[1] & U_CBUTTONS) {
        if (D_800CDA7C_main[1] & Z_TRIG) {
            zoom = CZoom;
            zoom += 30.0f;
            CZoom = zoom;
        } else {
            zoom = CZoom;
            zoom += 10.0f;
            CZoom = zoom;
        }
    }
    if ((D_800CDA7C_main[1] & D_CBUTTONS) && (CZoom - 10.0f != 0.0f)) {
        if (D_800CDA7C_main[1] & Z_TRIG) {
            CZoom -= 30.0f;
        } else {
            zoom = CZoom;
            CZoom = zoom - 10.0f;
        }
    }
    if (D_800CDA7C_main[1] & L_CBUTTONS) {
        D_80109AB0_mgenter += 1.0f;
    }
    if (D_800CDA7C_main[1] & R_CBUTTONS) {
        D_80109AB0_mgenter -= 1.0f;
    }
    Hu3DCameraPerspectiveSet(0, D_80109AB0_mgenter, D_80109B64_mgenter, D_80109B78_mgenter);
    x = CRot.x;
    y = CRot.y;
    if (D_800CDA7C_main[1] & Z_TRIG) {
        speed = 5.0f;
    } else {
        speed = 2.0f;
    }
    y += (-D_800CBB6E_main[1] / 30) * speed;
    if (y >= 360.0f) {
        y -= 360.0f;
    } else if (y < 0.0f) {
        y += 360.0f;
    }
    CRot.y = y;
    stick = D_800D20A1_main[1];
    stick /= 30;
    x += stick * speed;
    if (x >= 360.0f) {
        x -= 360.0f;
    } else if (x < 0.0f) {
        x += 360.0f;
    }
    CRot.x = x;
    if (D_800CDA7C_main[1] & Z_TRIG) {
        speed = 10.0f;
    } else {
        speed = 2.0f;
    }
    if (D_800CDA7C_main[1] & U_JPAD) {
        Center.x += sindf(y) * sindf(x) * -speed;
        Center.y += cosdf(x) * -speed;
        Center.z += cosdf(y) * sindf(x) * -speed;
    } else if (D_800CDA7C_main[1] & D_JPAD) {
        Center.x += sindf(y) * sindf(x) * speed;
        Center.y += cosdf(x) * speed;
        Center.z += cosdf(y) * sindf(x) * speed;
    } else if (D_800CDA7C_main[1] & L_JPAD) {
        x = gCameraList->pos.z - Center.z;
        dz = -(gCameraList->pos.x - Center.x);
        length = 1.0f / HuSqrtf(x * x + dz * dz);
        Center.x += x * length * speed;
        Center.y += 0.0f;
        Center.z += dz * length * speed;
    } else if (D_800CDA7C_main[1] & R_JPAD) {
        x = -(gCameraList->pos.z - Center.z);
        dz = gCameraList->pos.x - Center.x;
        length = 1.0f / HuSqrtf(x * x + dz * dz);
        Center.x += x * length * speed;
        Center.y += 0.0f;
        Center.z += dz * length * speed;
    }
}

void func_80109020_mgenter(void) {
    Vec pos, at, up;
    f32 rotX, rotY, rotZ;
    f32 upX, upY, upZ;
    f32 dx, dy, dz;
    f32 length;

    while (1) {
        if (D_80109AB4_mgenter == 0) {
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
            pos = D_80109BA4_mgenter;
            at = D_80109B88_mgenter;
            up.x = 0.0f;
            up.y = 1.0f;
            up.z = 0.0f;
        }
        D_800CE178_main.posX = pos.x;
        D_800CE178_main.posZ = pos.z;
        D_800CE178_main.rotY = CRot.y;
        D_800CE178_main.fov = gCameraList->fov;
        D_800CE178_main.far = D_800D5210_main;
        D_800CE178_main.near = D_800CB890_main;
        Hu3DCameraPosSetV(0, &pos, &at, &up);
        Hu3DCamUpdateMtx(0);
        HuPrcVSleep();
    }
}

s16 func_801095F4_mgenter(void) {
    s16 sprGrp;
    s16 i;

    D_80109B40_mgenter = func_8000B838_main(0x12000E);
    sprGrp = espEntry(D_80109B40_mgenter, 0, 1);
    D_80109B42_mgenter = sprGrp;
    for (i = 0; i < ARRAY_COUNT(D_80109B48_mgenter); i++) {
        D_80109B48_mgenter[i] = HuMemAllocTag(0x6000, TAG_OVERLAY);
    }
    D_80109B54_mgenter = HuSprGet(D_800CD1DC_main[sprGrp].unk04, 0)->unk_84->unk00->unk00;
    D_80109B44_mgenter = 0;
    espDispOff(sprGrp);
    return sprGrp;
}

void func_801096EC_mgenter(s16 arg0) {
    u8 **sprData;
    u8 *palData;
    void *buf;

    sprData = DataRead(arg0 | 0x170000);
    palData = DataRead((arg0 + 1) | 0x170000);
    hvqMpsInit1(0xFF);
    hvqMpsDecodeStart1(palData);
    buf = HuMemMemoryAllocPerm(0xC00);
    hvqMpsDecode1(sprData, (u16 *)D_80109B48_mgenter[D_80109B44_mgenter], 0x80, buf);
    HuMemMemoryFreePerm(buf);
    DataClose(sprData);
    DataClose(palData);
    HuSprGet(D_800CD1DC_main[D_80109B42_mgenter].unk04, 0)->unk_84->unk00->unk00 =
        D_80109B48_mgenter[D_80109B44_mgenter];
    D_80109B44_mgenter++;
    if (D_80109B44_mgenter >= ARRAY_COUNT(D_80109B48_mgenter)) {
        D_80109B44_mgenter = 0;
    }
    espDispOn(D_80109B42_mgenter);
}

void func_80109820_mgenter(void) {
    s16 i;

    HuSprGet(D_800CD1DC_main[D_80109B42_mgenter].unk04, 0)->unk_84->unk00->unk00 = D_80109B54_mgenter;
    espKill(D_80109B42_mgenter);
    HuSprAnimKill(D_80109B40_mgenter);
    for (i = 0; i < ARRAY_COUNT(D_80109B48_mgenter); i++) {
        HuMemFree(D_80109B48_mgenter[i]);
    }
}

void func_801098D8_mgenter(void) {
    f32 y = 0.0f;
    f32 x = 0.0f;
    f32 length;

    if (D_800CDA7C_main[D_80109B74_mgenter] & L_JPAD) {
        x = -1.0f;
    }
    if (D_800CDA7C_main[D_80109B74_mgenter] & R_JPAD) {
        x += 1.0f;
    }
    if (D_800CDA7C_main[D_80109B74_mgenter] & U_JPAD) {
        y += 1.0f;
    }
    if (D_800CDA7C_main[D_80109B74_mgenter] & D_JPAD) {
        y += -1.0f;
    }
    if ((x == 0.0f) & (y == 0.0f)) {
        return;
    }
    length = HuSqrtf(x * x + y * y);
    D_800CBB6E_main[D_80109B74_mgenter] = x / length * 50.0f;
    D_800D20A1_main[D_80109B74_mgenter] = y / length * 50.0f;
}
