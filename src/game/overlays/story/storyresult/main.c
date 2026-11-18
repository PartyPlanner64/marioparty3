#include "common.h"
#include "game/hmfmath.h"
#include "game/pause.h"
#include "game/overlays/minigame.h"
#include "game/overlays/duel/common/ovl_81.h"
#define NO_EXTERN_VARIABLES
#include "storyresult.h"
#include "game/hmfcoll.h"

void storyresult_ExitCheckObjMain(omObjData *object);
void storyresult_ExitObjMain(omObjData *object);
void storyresult_ModelEntryPosSet(MsetupModelEntry *entry, s16 model);
u32 storyresult_RandSeedCalc(u32 seed);
void storyresult_CameraUpdate(void);
void storyresult_CameraProc(void);
void storyresult_PlayerConfigInit(void);
extern f32 CFanLen;
extern f32 CFanOfs;
extern s16 kakusiMasuItemHis[10];

u16 storyresult_exitCnt = 0;
s16 storyresult_backF = 0;
s16 storyresult_musFadeNo = 1;
f32 storyresult_cameraFov = 58.0f;
s8 storyresult_cameraLookF = 0;
u32 storyresult_randSeed = 0;
u8 storyresult_pageTbl[14] = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 2, 2 };

s16 storyresult_padNo BSS;
s16 storyresult_exitMode BSS;
u8 storyresult_exitModePad[4] BSS; /* Unreferenced. */
MsetupPlayerConfig storyresult_playerConfig BSS;
Vec storyresult_cameraTarget BSS;
Vec storyresult_cameraRot BSS;
Vec storyresult_cameraPos BSS;
f32 storyresult_cameraNear BSS;
s16 storyresult_wipeTime BSS;
s16 storyresult_wipeType BSS;
f32 storyresult_cameraFar BSS;
s16 storyresult_exitEvtNo BSS;
s16 storyresult_exitOvlNo BSS;

void storyresult_ObjectSetup(void) {
    omInitObjMan(51, 25);
    switch (omovlevtno) {
        case 0:
            if (storyresult_StageClearCheck() == 0) {
                return;
            }
            break;
        case 2:
            MgStoryStageGoto();
            return;
    }
    Hu3DCamInit(1);
    MapCollInit(1);
    Hu3DSprModelInit(25);
    HuWinInit();
    Hu3DScreenClearF = 0;
    storyresult_cameraNear = 80.0f;
    storyresult_cameraFar = 6000.0f;
    storyresult_cameraFov = 58.0f;
    Hu3DCameraPerspectiveSet(0, storyresult_cameraFov, storyresult_cameraNear, storyresult_cameraFar);
    storyresult_cameraRot.x = 0;
    storyresult_cameraRot.y = 0;
    storyresult_cameraRot.z = 0;
    CRot.x = 0;
    CRot.y = 0;
    CRot.z = 0;
    storyresult_CameraUpdate();
    omAddObj(10000, 0, 0, -1, storyresult_ExitCheckObjMain);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(2, 0, 0, 0);
    Hu3DGLightDirSet(2, 0.0f, 0.0f, 100.0f);
    Hu3DGLightColorSet(3, 240, 240, 240);
    Hu3DGLightDirSet(3, 0.0f, 100.0f, 0.0f);
    Hu3DGLightColorSet(1, 255, 255, 255);
    Hu3DBGColorSet(16, 16, 240);
    omPrcSetStatBit(omAddPrcObj(storyresult_CameraProc, 0x1100, 0x400, 0), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    storyresult_exitMode = 0;
    storyresult_PlayerConfigInit();
    switch (omovlevtno) {
        case 0:
            if (omovlstat & OM_OVL_STAT_DUEL) {
                omAddPrcObj(storyresult_StageResultProc, 0x3F00, 0x1000, 0);
            }
            break;
        case 1:
            omAddPrcObj(storyresult_FinalResultProc, 0x3F00, 0x1000, 0);
            break;
        case 2:
            break;
        case 3:
            omAddPrcObj(storyresult_DebugStatProc, 0x3F00, 0x1000, 0);
            break;
    }
    WipeColorSet(0, 0, 0);
    storyresult_wipeType = WIPE_STARS;
    storyresult_wipeTime = 20;
}

void storyresult_ExitCheckObjMain(omObjData *object) {
    if (storyresult_exitCnt == 0) {
        if (omSysExitReq != 0) {
            goto createWipe;
        }
    } else if (storyresult_exitCnt == 1) {
        goto createWipe;
    } else {
        storyresult_exitCnt--;
    }
    return;

createWipe:
    if (storyresult_wipeType >= 0) {
        WipeCreateOut(storyresult_wipeType, storyresult_wipeTime);
    }
    switch (storyresult_musFadeNo) {
        case 1:
            HuAudSeqFadeOut(30);
            break;
        case 2:
            HuAudSeqFadeOut(81);
            break;
    }
    object->func = storyresult_ExitObjMain;
}

void storyresult_ExitObjMain(omObjData *object) {
    u16 flags;

    if (WipeStatGet() == 0) {
        if (storyresult_backF != 0) {
            MBDBackKill();
            MBDBackClose();
        }
        HuWinAllKill();
        flags = OM_OVL_STAT_MG | OM_OVL_STAT_SYSKEY;
        switch (storyresult_exitMode) {
            case 0:
            default:
                omOvlReturnEx(1);
                break;
            case 2:
                omOvlCallEx(storyresult_exitOvlNo, storyresult_exitEvtNo, flags);
                break;
            case 1:
                omOvlGotoEx(storyresult_exitOvlNo, storyresult_exitEvtNo, flags);
                break;
            case 3:
                omOvlGotoEx(storyresult_exitOvlNo, storyresult_exitEvtNo, OM_OVL_STAT_DUEL | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
                break;
            case 4:
                omOvlGotoEx(storyresult_exitOvlNo, storyresult_exitEvtNo, OM_OVL_STAT_BOARD | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
                break;
        }
    }
}

void storyresult_ModelEntryPosSet(MsetupModelEntry *entry, s16 model) {
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

void storyresult_ModelEntryReadAll(MsetupModelEntry *entry, MsetupModelHandle *handle, s32 count) {
    s16 i;
    s16 model;
    s32 motion;

    if (entry == NULL || handle == NULL) {
        return;
    }
    for (i = 0; i < count; entry++, i++, handle++) {
        model = handle->model = Hu3DModelRead(entry->dataId, entry->flags);
        storyresult_ModelEntryPosSet(entry, model);
        motion = handle->motion = Hu3DData[model].motId;
        if (motion >= 0) {
            Hu3DMotionAttrSet(model, -1, entry->motion);
        }
    }
}

u32 storyresult_RandSeedCalc(u32 seed) {
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

u32 storyresult_Rand(void) {
    return storyresult_randSeed = storyresult_RandSeedCalc(storyresult_randSeed);
}

u32 storyresult_RandMod(u32 limit) {
    u32 random;

    random = storyresult_randSeed = storyresult_RandSeedCalc(storyresult_randSeed);
    return (random & 0x7FFFFFFF) % limit;
}

void storyresult_CameraPresetSet(ModeCameraPreset *preset) {
    CRot = preset->rot;
    storyresult_cameraRot = CRot;
    Center = preset->center;
    CZoom = preset->zoom;
    if (preset->fov != storyresult_cameraFov) {
        storyresult_cameraFov = preset->fov;
        Hu3DCameraPerspectiveSet(0, storyresult_cameraFov, storyresult_cameraNear, storyresult_cameraFar);
    }
}

void storyresult_CameraUpdate(void) {
    Vec pos, at, up;
    f32 rotX, rotY, rotZ;
    f32 upX, upY, upZ;
    f32 dx, dy, dz;
    f32 length;

    if (storyresult_cameraLookF == 0) {
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
        pos = storyresult_cameraPos;
        at = storyresult_cameraTarget;
        up.x = 0.0f;
        up.y = 1.0f;
        up.z = 0.0f;
    }
    CFan.x = pos.x;
    CFan.z = pos.z;
    CFan.angle = CRot.y;
    CFan.shape.spread = gCameraList->fov;
    CFan.shape.length = CFanLen;
    CFan.shape.offset = CFanOfs;
    Hu3DCameraPosSetV(0, &pos, &at, &up);
    Hu3DCamUpdateMtx(0);
}

void storyresult_CameraProc(void) {
    while (1) {
        storyresult_CameraUpdate();
        HuPrcVSleep();
    }
}

void storyresult_CameraKeyframeExec(MsetupCameraKeyframe *keys, f32 speed, void (*callback)(s16, s16, s16)) {
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
        storyresult_cameraRot.x = CRot.x = interpolated.values.preset.rot.x;
        storyresult_cameraRot.y = CRot.y = interpolated.values.preset.rot.y;
        storyresult_cameraRot.z = CRot.z = interpolated.values.preset.rot.z;
        CZoom = interpolated.values.preset.zoom;
        gCameraList->fov = storyresult_cameraFov = interpolated.values.preset.fov;
        if (callback != NULL) {
            onFrame((s16)duration, segment, i);
        }
        HuPrcVSleep();
    }
    segment++;
    storyresult_cameraRot.x = CRot.x = keys[segment].values.preset.rot.x;
    storyresult_cameraRot.y = CRot.y = keys[segment].values.preset.rot.y;
    storyresult_cameraRot.z = CRot.z = keys[segment].values.preset.rot.z;
    CZoom = keys[segment].values.preset.zoom;
    Center.x = keys[segment].values.preset.center.x;
    Center.y = keys[segment].values.preset.center.y;
    Center.z = keys[segment].values.preset.center.z;
    gCameraList->fov = storyresult_cameraFov = keys[segment].values.preset.fov;
    winPauseF = 0;
}

void storyresult_PlayerConfigInit(void) {
    s16 i;
    s16 connectedCount;
    s16 port;
    s16 j;

    for (i = 0; i < 4; i++) {
        storyresult_playerConfig.controllerPorts[i] = 0xFF;
        storyresult_playerConfig.characters[i] = i;
        storyresult_playerConfig.cpuDifficulty[i] = 0xFF;
        storyresult_playerConfig.stars[i] = 0;
    }
    for (i = 0, connectedCount = 0; i < 4; i++) {
        if (CheckControllerRead(i)) {
            storyresult_playerConfig.controllerPorts[connectedCount] = i;
            connectedCount++;
        }
    }
    for (i = 0; i < 4; i++) {
        if (storyresult_playerConfig.controllerPorts[i] == 0xFF) {
            for (port = 0; port < 4; port++) {
                for (j = 0; j < 4; j++) {
                    if (storyresult_playerConfig.controllerPorts[j] == port) {
                        break;
                    }
                }
                if (j == 4) {
                    break;
                }
            }
            storyresult_playerConfig.controllerPorts[i] = port;
        }
    }
    storyresult_playerConfig.totalTurns = 0;
    storyresult_playerConfig.unk16 = 0;
    storyresult_playerConfig.unk13 = 0;
    storyresult_playerConfig.connectedCount = connectedCount;
    storyresult_playerConfig.humanCount = 0;
    storyresult_playerConfig.cpuCount = 4;
    storyresult_playerConfig.boardIndex = 0;
    storyresult_padNo = storyresult_playerConfig.controllerPorts[0];
}

s16 storyresult_StageClearCheck(void) {
    s16 result = 0;
    s16 winner;
    s16 i;

    switch (storyresult_pageTbl[GwStory.unk0]) {
        case 0:
            winner = kakusiMasuItemHis[0];
            if (winner >= 0 && winner < 6 && GwStory.unk1 == GwPlayer[winner].chr) {
                result++;
            }
            break;
        case 1:
            if (kakusiMasuItemHis[2] == 0) {
                winner = kakusiMasuItemHis[0];
                if (winner >= 0 && winner < 6 && GwStory.unk1 == GwPlayer[winner].chr) {
                    result++;
                }
            }
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                if (GwPlayer[i].chr == GwStory.unk1) {
                    break;
                }
            }
            if (i < 2 && GwPlayer[i].bonusCoin >= 0) {
                result++;
            }
            break;
        default:
            result++;
            break;
    }
    if (result == 0) {
        storyresult_exitMode = 1;
        storyresult_exitOvlNo = 0x75;
        storyresult_exitEvtNo = 0;
        storySceneNo = 15;
        omOvlGotoEx(storycall, 0, OM_OVL_STAT_MG | OM_OVL_STAT_SYSKEY);
    }
    return result;
}
