#include "staff.h"

u16 staff_exitCnt = 0;
f32 staff_cameraFov = 58.0f;
s8 staff_cameraLookF = 0;
u32 staff_randSeed = 0;

void staff_ObjectSetup(void) {
    Hu3DCamInit(1);
    MapCollInit(1);
    Hu3DSprModelInit(25);
    omInitObjMan(51, 25);
    HuWinInit();
    omGameSysInit();
    Hu3DScreenClearF = 0;
    staff_cameraNear = 80.0f;
    staff_cameraFar = 6000.0f;
    staff_cameraFov = 58.0f;
    Hu3DCameraPerspectiveSet(0, staff_cameraFov, staff_cameraNear, staff_cameraFar);
    staff_cameraRot.x = 0;
    staff_cameraRot.y = 0;
    staff_cameraRot.z = 0;
    CRot.x = 0;
    CRot.y = 0;
    CRot.z = 0;
    staff_CameraUpdate();
    omAddObj(10000, 0, 0, -1, staff_ExitCheckObjMain);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(2, 0, 0, 0);
    Hu3DGLightDirSet(2, 0.0f, 0.0f, 100.0f);
    Hu3DGLightColorSet(3, 240, 240, 240);
    Hu3DGLightDirSet(3, 0.0f, 100.0f, 0.0f);
    Hu3DGLightColorSet(1, 255, 255, 255);
    Hu3DBGColorSet(0, 0, 0);
    omPrcSetStatBit(omAddPrcObj(staff_CameraProc, 0x1100, 0x400, 0), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    staff_exitMode = 0;
    staff_PlayerConfigInit();
    staff_chrNo = 0;
    staff_storyF = 0;
    if (omovlevtno >= 0 && omovlevtno < 6) {
        staff_chrNo = omovlevtno;
    } else if (omovlevtno >= 6) {
        staff_chrNo = GwStory.unk1;
        staff_storyF = 1;
    }
    omAddPrcObj(staff_MainProc, 0x3F00, 0x1000, 0);
    WipeColorSet(0, 0, 0);
    staff_wipeType = 11;
    staff_wipeTime = 20;
}

void staff_ExitCheckObjMain(omObjData *object) {
    if (staff_storyF == 0 && (HuPadBtnDown[staff_padNo] & START_BUTTON)) {
        staff_exitMode = 0;
        staff_exitCnt = 1;
    }
    if (staff_exitCnt == 0) {
        if (omSysExitReq != 0) {
            goto createWipe;
        }
    } else if (staff_exitCnt == 1) {
        goto createWipe;
    } else {
        staff_exitCnt--;
    }
    return;

createWipe:
    if (staff_wipeType >= 0) {
        WipeCreateOut(staff_wipeType, staff_wipeTime);
    }
    HuAudSeqFadeOut(15);
    object->func = staff_ExitObjMain;
}

void staff_ExitObjMain(omObjData *object) {
    u16 flags;

    if (WipeStatGet() == 0) {
        HuWinAllKill();
        flags = 0x14;
        switch (staff_exitMode) {
            case 0:
            default:
                if (staff_storyF != 0) {
                    omovlhisidx = -1;
                    omOvlCallEx(0x58, 0, 0x84);
                } else {
                    omOvlReturnEx(1);
                }
                break;
            case 2:
                omOvlCallEx(staff_exitOvlNo, staff_exitEvtNo, flags);
                break;
            case 1:
                omOvlGotoEx(staff_exitOvlNo, staff_exitEvtNo, flags);
                break;
            case 3:
                omOvlGotoEx(staff_exitOvlNo, staff_exitEvtNo, 0x4090);
                break;
            case 4:
                omOvlGotoEx(staff_exitOvlNo, staff_exitEvtNo, 0x92);
                break;
        }
    }
}

void staff_ModelEntryPosSet(MsetupModelEntry *entry, s16 model) {
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

void staff_ModelEntryReadAll(MsetupModelEntry *entry, MsetupModelHandle *handle, s32 count) {
    s16 i;
    s16 model;
    s32 motion;

    if (entry == NULL || handle == NULL) {
        return;
    }
    for (i = 0; i < count; entry++, i++, handle++) {
        model = handle->model = Hu3DModelRead(entry->dataId, entry->flags);
        staff_ModelEntryPosSet(entry, model);
        motion = handle->motion = Hu3DData[model].motId;
        if (motion >= 0) {
            Hu3DMotionAttrSet(model, -1, entry->motion);
        }
    }
}

u32 staff_RandSeedCalc(u32 seed) {
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

u32 staff_Rand(void) {
    return staff_randSeed = staff_RandSeedCalc(staff_randSeed);
}

s32 staff_RandMod(u32 limit) {
    u32 random;

    random = staff_randSeed = staff_RandSeedCalc(staff_randSeed);
    return (random & 0x7FFFFFFF) % limit;
}

void staff_CameraPresetSet(ModeCameraPreset *preset) {
    CRot = preset->rot;
    staff_cameraRot = CRot;
    Center = preset->center;
    CZoom = preset->zoom;
    if (preset->fov != staff_cameraFov) {
        staff_cameraFov = preset->fov;
        Hu3DCameraPerspectiveSet(0, staff_cameraFov, staff_cameraNear, staff_cameraFar);
    }
}

void staff_CameraUpdate(void) {
    Vec pos, at, up;
    f32 rotX, rotY, rotZ;
    f32 upX, upY, upZ;
    f32 dx, dy, dz;
    f32 length;

    if (staff_cameraLookF == 0) {
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
        pos = staff_cameraPos;
        at = staff_cameraTarget;
        up.x = 0.0f;
        up.y = 1.0f;
        up.z = 0.0f;
    }
    CFanParam[0] = pos.x;
    CFanParam[1] = pos.z;
    CFanParam[-1] = CRot.y;
    CFanParam[2] = gCameraList->fov;
    CFanParam[3] = CFanLen;
    CFanParam[4] = CFanOfs;
    Hu3DCameraPosSetV(0, &pos, &at, &up);
    Hu3DCamUpdateMtx(0);
}

void staff_CameraProc(void) {
    while (1) {
        staff_CameraUpdate();
        HuPrcVSleep();
    }
}

void staff_CameraKeyframeExec(MsetupCameraKeyframe *keys, f32 speed, void (*callback)(s16, s16, s16)) {
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
        staff_cameraRot.x = CRot.x = interpolated.values.preset.rot.x;
        staff_cameraRot.y = CRot.y = interpolated.values.preset.rot.y;
        staff_cameraRot.z = CRot.z = interpolated.values.preset.rot.z;
        CZoom = interpolated.values.preset.zoom;
        gCameraList->fov = staff_cameraFov = interpolated.values.preset.fov;
        if (callback != NULL) {
            onFrame((s16)duration, segment, i);
        }
        HuPrcVSleep();
    }
    segment++;
    staff_cameraRot.x = CRot.x = keys[segment].values.preset.rot.x;
    staff_cameraRot.y = CRot.y = keys[segment].values.preset.rot.y;
    staff_cameraRot.z = CRot.z = keys[segment].values.preset.rot.z;
    CZoom = keys[segment].values.preset.zoom;
    Center.x = keys[segment].values.preset.center.x;
    Center.y = keys[segment].values.preset.center.y;
    Center.z = keys[segment].values.preset.center.z;
    gCameraList->fov = staff_cameraFov = keys[segment].values.preset.fov;
    winPauseF = 0;
}

void staff_PlayerConfigInit(void) {
    s16 i;
    s16 connectedCount;
    s16 port;
    s16 j;

    for (i = 0; i < 4; i++) {
        staff_playerConfig.controllerPorts[i] = 0xFF;
        staff_playerConfig.characters[i] = i;
        staff_playerConfig.cpuDifficulty[i] = 0xFF;
        staff_playerConfig.stars[i] = 0;
    }
    for (i = 0, connectedCount = 0; i < 4; i++) {
        if (CheckControllerRead(i)) {
            staff_playerConfig.controllerPorts[connectedCount] = i;
            connectedCount++;
        }
    }
    for (i = 0; i < 4; i++) {
        if (staff_playerConfig.controllerPorts[i] == 0xFF) {
            for (port = 0; port < 4; port++) {
                for (j = 0; j < 4; j++) {
                    if (staff_playerConfig.controllerPorts[j] == port) {
                        break;
                    }
                }
                if (j == 4) {
                    break;
                }
            }
            staff_playerConfig.controllerPorts[i] = port;
        }
    }
    staff_playerConfig.totalTurns = 0;
    staff_playerConfig.unk16 = 0;
    staff_playerConfig.unk13 = 0;
    staff_playerConfig.connectedCount = connectedCount;
    staff_playerConfig.humanCount = 0;
    staff_playerConfig.cpuCount = 4;
    staff_playerConfig.boardIndex = 0;
    staff_padNo = staff_playerConfig.controllerPorts[0];
}
