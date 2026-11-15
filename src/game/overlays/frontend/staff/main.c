#include "staff.h"

u16 D_80110530_staff = 0;
f32 D_80110534_staff = 58.0f;
s8 D_80110538_staff = 0;
u32 D_8011053C_staff = 0;

void func_801059A0_staff(void) {
    Hu3DCamInit(1);
    MapCollInit(1);
    Hu3DSprModelInit(25);
    omInitObjMan(51, 25);
    HuWinInit();
    omGameSysInit();
    Hu3DScreenClearF = 0;
    D_80111564_staff = 80.0f;
    D_80111560_staff = 6000.0f;
    D_80110534_staff = 58.0f;
    Hu3DCameraPerspectiveSet(0, D_80110534_staff, D_80111564_staff, D_80111560_staff);
    D_80111550_staff.x = 0;
    D_80111550_staff.y = 0;
    D_80111550_staff.z = 0;
    CRot.x = 0;
    CRot.y = 0;
    CRot.z = 0;
    func_8010615C_staff();
    omAddObj(10000, 0, 0, -1, func_80105BD4_staff);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(2, 0, 0, 0);
    Hu3DGLightDirSet(2, 0.0f, 0.0f, 100.0f);
    Hu3DGLightColorSet(3, 240, 240, 240);
    Hu3DGLightDirSet(3, 0.0f, 100.0f, 0.0f);
    Hu3DGLightColorSet(1, 255, 255, 255);
    Hu3DBGColorSet(0, 0, 0);
    omPrcSetStatBit(omAddPrcObj(func_80106720_staff, 0x1100, 0x400, 0), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_8011155C_staff = 0;
    func_80106C50_staff();
    D_80111514_staff = 0;
    D_80111512_staff = 0;
    if (omovlevtno >= 0 && omovlevtno < 6) {
        D_80111514_staff = omovlevtno;
    } else if (omovlevtno >= 6) {
        D_80111514_staff = GwStory.unk1;
        D_80111512_staff = 1;
    }
    omAddPrcObj(func_80106E20_staff, 0x3F00, 0x1000, 0);
    WipeColorSet(0, 0, 0);
    D_80111530_staff = 11;
    D_8011154C_staff = 20;
}

void func_80105BD4_staff(omObjData *object) {
    if (D_80111512_staff == 0 && (HuPadBtnDown[D_80111510_staff] & 0x1000)) {
        D_8011155C_staff = 0;
        D_80110530_staff = 1;
    }
    if (D_80110530_staff == 0) {
        if (omSysExitReq != 0) {
            goto createWipe;
        }
    } else if (D_80110530_staff == 1) {
        goto createWipe;
    } else {
        D_80110530_staff--;
    }
    return;

createWipe:
    if (D_80111530_staff >= 0) {
        WipeCreateOut(D_80111530_staff, D_8011154C_staff);
    }
    HuAudSeqFadeOut(15);
    object->func = func_80105CB4_staff;
}

void func_80105CB4_staff(omObjData *object) {
    u16 flags;

    if (WipeStatGet() == 0) {
        HuWinAllKill();
        flags = 0x14;
        switch (D_8011155C_staff) {
            case 0:
            default:
                if (D_80111512_staff != 0) {
                    omovlhisidx = -1;
                    omOvlCallEx(0x58, 0, 0x84);
                } else {
                    omOvlReturnEx(1);
                }
                break;
            case 2:
                omOvlCallEx(D_80111516_staff, D_80111532_staff, flags);
                break;
            case 1:
                omOvlGotoEx(D_80111516_staff, D_80111532_staff, flags);
                break;
            case 3:
                omOvlGotoEx(D_80111516_staff, D_80111532_staff, 0x4090);
                break;
            case 4:
                omOvlGotoEx(D_80111516_staff, D_80111532_staff, 0x92);
                break;
        }
    }
}

void func_80105DB8_staff(MsetupModelEntry *entry, s16 model) {
    switch (entry->positionMode) {
        case 0:
            break;
        case 1:
            Hu3DModelPosSet(model, entry->pos.x, entry->pos.y, entry->pos.z);
            Hu3DModelRotSet(model, entry->rot.x, entry->rot.y, entry->rot.z);
            break;
        case 2:
            Hu3DModelPosSet(model, entry->pos.x * 5.0f, entry->pos.y * 5.0f, entry->pos.z * 5.0f);
            Hu3DModelRotSet(model, entry->rot.x, entry->rot.y, entry->rot.z);
            break;
    }
}

void func_80105E6C_staff(MsetupModelEntry *entry, MsetupModelHandle *handle, s32 count) {
    s16 i;
    s16 model;
    s32 motion;

    if (entry == NULL || handle == NULL) {
        return;
    }
    for (i = 0; i < count; entry++, i++, handle++) {
        model = handle->model = Hu3DModelRead(entry->dataId, entry->flags);
        func_80105DB8_staff(entry, model);
        motion = handle->motion = Hu3DData[model].motId;
        if (motion >= 0) {
            Hu3DMotionAttrSet(model, -1, entry->motion);
        }
    }
}

u32 func_80105F48_staff(u32 seed) {
    u32 quotient;
    u32 remainder;

    if (seed == 0) {
        seed = rand8();
        seed ^= osGetCount();
        seed ^= 0xD826BC89;
    }
    quotient = seed / 127773;
    remainder = seed % 127773;
    seed = quotient * 2836;
    return seed - remainder * 16807;
}

u32 func_8010601C_staff(void) {
    return D_8011053C_staff = func_80105F48_staff(D_8011053C_staff);
}

s32 func_80106044_staff(u32 limit) {
    u32 random;

    random = D_8011053C_staff = func_80105F48_staff(D_8011053C_staff);
    return (random & 0x7FFFFFFF) % limit;
}

void func_8010609C_staff(ModeCameraPreset *preset) {
    CRot = preset->rot;
    D_80111550_staff = CRot;
    Center = preset->center;
    CZoom = preset->zoom;
    if (preset->fov != D_80110534_staff) {
        D_80110534_staff = preset->fov;
        Hu3DCameraPerspectiveSet(0, D_80110534_staff, D_80111564_staff, D_80111560_staff);
    }
}

void func_8010615C_staff(void) {
    Vec pos, at, up;
    f32 rotX, rotY, rotZ;
    f32 upX, upY, upZ;
    f32 dx, dy, dz;
    f32 length;

    if (D_80110538_staff == 0) {
        rotX = CRot.x;
        rotY = CRot.y;
        rotZ = CRot.z;
        pos.x = Center.x + sindf(rotY) * cosdf(rotX) * CZoom;
        pos.y = Center.y + -sindf(rotX) * CZoom;
        pos.z = Center.z + cosdf(rotY) * cosdf(rotX) * CZoom;
        at.x = Center.x;
        at.y = Center.y;
        at.z = Center.z;
        upX = sindf(rotY) * sindf(rotX);
        upY = cosdf(rotX);
        upZ = cosdf(rotY) * sindf(rotX);
        dx = at.x - pos.x;
        dy = at.y - pos.y;
        dz = at.z - pos.z;
        length = dx * dx + dy * dy + dz * dz;
        length = HuSqrtf(length);
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
        pos = D_80111540_staff;
        at = D_80111534_staff;
        up.x = 0.0f;
        up.y = 1.0f;
        up.z = 0.0f;
    }
    D_800CE17C_main[0] = pos.x;
    D_800CE17C_main[1] = pos.z;
    D_800CE17C_main[-1] = CRot.y;
    D_800CE17C_main[2] = gCameraList->fov;
    D_800CE17C_main[3] = CFanLen;
    D_800CE17C_main[4] = CFanOfs;
    Hu3DCameraPosSetV(0, &pos, &at, &up);
    Hu3DCamUpdateMtx(0);
}

void func_80106720_staff(void) {
    while (1) {
        func_8010615C_staff();
        HuPrcVSleep();
    }
}

void func_8010674C_staff(MsetupCameraKeyframe *keys, f32 speed, void (*callback)(s16, s16, s16)) {
    MsetupCameraKeyframe interpolated;
    f32 values[4];
    f32 times[4];
    MsetupCameraKeyframe *key;
    f32 *p0;
    f32 *p1;
    f32 *p2;
    f32 *p3;
    f32 *out;
    f32 oldX;
    f32 oldY;
    f32 oldZ;
    f32 x;
    f32 y;
    f32 z;
    f32 duration;
    f32 distance;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 i;
    s16 component;
    s16 segment;
    void (*onFrame)(s16, s16, s16) = callback;

    duration = oldX = oldY = oldZ = 0.0f;
    for (i = 0, key = keys; key->values.preset.zoom != 0.0f; i++, key = &keys[i]) {
        if (speed != 0.0f) {
            x = sindf(key->values.preset.rot.y) * cosdf(key->values.preset.rot.x) * key->values.preset.zoom + key->values.preset.center.x;
            y = -sindf(key->values.preset.rot.x) * key->values.preset.zoom + key->values.preset.center.y;
            z = cosdf(key->values.preset.rot.y) * cosdf(key->values.preset.rot.x) * key->values.preset.zoom + key->values.preset.center.z;
            if (i > 0) {
                dx = oldX - x;
                dy = oldY - y;
                dz = oldZ - z;
                dx = dx * dx + dy * dy;
                dz *= dz;
                distance = dx + dz;
                distance = HuSqrtf(distance);
                if (distance == 0.0f) {
                    distance = speed * 10.0f;
                }
                duration += distance / speed;
                key->time = duration;
            }
            oldX = x;
            oldY = y;
            oldZ = z;
        } else {
            duration = key->time;
        }
    }
    duration -= 10.0f;
    for (i = 10, segment = 1; i < duration; i++) {
        if (i > keys[segment + 1].time) {
            segment++;
        }
        times[0] = keys[segment - 1].time;
        times[1] = keys[segment].time;
        times[2] = keys[segment + 1].time;
        times[3] = keys[segment + 2].time;
        p0 = keys[segment - 1].values.components;
        p1 = keys[segment].values.components;
        p2 = keys[segment + 1].values.components;
        p3 = keys[segment + 2].values.components;
        out = interpolated.values.components;
        for (component = 0; component < 8; component++) {
            values[0] = *p0++;
            values[1] = *p1++;
            values[2] = *p2++;
            values[3] = *p3++;
            *out++ = InterpolateBMLine(values, times, i);
        }
        Center.x = interpolated.values.preset.center.x;
        Center.y = interpolated.values.preset.center.y;
        Center.z = interpolated.values.preset.center.z;
        D_80111550_staff.x = CRot.x = interpolated.values.preset.rot.x;
        D_80111550_staff.y = CRot.y = interpolated.values.preset.rot.y;
        D_80111550_staff.z = CRot.z = interpolated.values.preset.rot.z;
        CZoom = interpolated.values.preset.zoom;
        gCameraList->fov = D_80110534_staff = interpolated.values.preset.fov;
        if (callback != NULL) {
            onFrame((s16)duration, segment, i);
        }
        HuPrcVSleep();
    }
    segment++;
    D_80111550_staff.x = CRot.x = keys[segment].values.preset.rot.x;
    D_80111550_staff.y = CRot.y = keys[segment].values.preset.rot.y;
    D_80111550_staff.z = CRot.z = keys[segment].values.preset.rot.z;
    CZoom = keys[segment].values.preset.zoom;
    Center.x = keys[segment].values.preset.center.x;
    Center.y = keys[segment].values.preset.center.y;
    Center.z = keys[segment].values.preset.center.z;
    gCameraList->fov = D_80110534_staff = keys[segment].values.preset.fov;
    winPauseF = 0;
}

void func_80106C50_staff(void) {
    s16 i;
    s16 connectedCount;
    s16 port;
    s16 j;

    for (i = 0; i < 4; i++) {
        D_80111518_staff.controllerPorts[i] = 0xFF;
        D_80111518_staff.characters[i] = i;
        D_80111518_staff.cpuDifficulty[i] = 0xFF;
        D_80111518_staff.stars[i] = 0;
    }
    for (i = 0, connectedCount = 0; i < 4; i++) {
        if (CheckControllerRead(i)) {
            D_80111518_staff.controllerPorts[connectedCount] = i;
            connectedCount++;
        }
    }
    for (i = 0; i < 4; i++) {
        if (D_80111518_staff.controllerPorts[i] == 0xFF) {
            for (port = 0; port < 4; port++) {
                for (j = 0; j < 4; j++) {
                    if (D_80111518_staff.controllerPorts[j] == port) {
                        break;
                    }
                }
                if (j == 4) {
                    break;
                }
            }
            D_80111518_staff.controllerPorts[i] = port;
        }
    }
    D_80111518_staff.totalTurns = 0;
    D_80111518_staff.unk16 = 0;
    D_80111518_staff.unk13 = 0;
    D_80111518_staff.connectedCount = connectedCount;
    D_80111518_staff.humanCount = 0;
    D_80111518_staff.cpuCount = 4;
    D_80111518_staff.boardIndex = 0;
    D_80111510_staff = D_80111518_staff.controllerPorts[0];
}
