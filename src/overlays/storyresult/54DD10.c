#include "common.h"
#include "game/hmfmath.h"
#include "game/pause.h"
#include "overlays/minigame.h"
#include "../ovl_81_name/ovl_81.h"
#include "storyresult.h"

void func_80105C30_storyresult(omObjData *object);
void func_80105CF8_storyresult(omObjData *object);
void func_80105DEC_storyresult(MsetupModelEntry *entry, s16 model);
u32 func_80105F7C_storyresult(u32 seed);
void func_80106190_storyresult(void);
void func_80106754_storyresult(void);
void func_80106C84_storyresult(void);
extern f32 D_8010A918_storyresult;
extern s8 D_8010A91C_storyresult;
extern u32 D_8010A920_storyresult;
extern MsetupPlayerConfig D_8010ABE8_storyresult;
extern Vec D_8010AC00_storyresult;
extern Vec D_8010AC0C_storyresult;
extern Vec D_8010AC18_storyresult;
extern f32 D_8010AC24_storyresult;
extern f32 D_8010AC2C_storyresult;
extern f32 D_800D5210_main;
extern f32 D_800CB890_main;
extern s16 kakusiMasuItemHis[10];

void func_801059A0_storyresult(void) {
    omInitObjMan(51, 25);
    switch (omovlevtno) {
        case 0:
            if (func_80106E48_storyresult() == 0) {
                return;
            }
            break;
        case 2:
            func_800E989C_minigame();
            return;
    }
    Hu3DCamInit(1);
    func_8001FE20_main(1);
    func_800142A0_main(25);
    HuWinInit();
    D_800CD280_main = 0;
    D_8010AC24_storyresult = 80.0f;
    D_8010AC2C_storyresult = 6000.0f;
    D_8010A918_storyresult = 58.0f;
    Hu3DCameraPerspectiveSet(0, D_8010A918_storyresult, D_8010AC24_storyresult, D_8010AC2C_storyresult);
    D_8010AC0C_storyresult.x = 0;
    D_8010AC0C_storyresult.y = 0;
    D_8010AC0C_storyresult.z = 0;
    CRot.x = 0;
    CRot.y = 0;
    CRot.z = 0;
    func_80106190_storyresult();
    omAddObj(10000, 0, 0, -1, func_80105C30_storyresult);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(2, 0, 0, 0);
    Hu3DGLightDirSet(2, 0.0f, 0.0f, 100.0f);
    Hu3DGLightColorSet(3, 240, 240, 240);
    Hu3DGLightDirSet(3, 0.0f, 100.0f, 0.0f);
    Hu3DGLightColorSet(1, 255, 255, 255);
    Hu3DBGColorSet(16, 16, 240);
    omPrcSetStatBit(omAddPrcObj(func_80106754_storyresult, 0x1100, 0x400, 0), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_8010ABE2_storyresult = 0;
    func_80106C84_storyresult();
    switch (omovlevtno) {
        case 0:
            if (omovlstat & 0x4000) {
                omAddPrcObj(func_80107204_storyresult, 0x3F00, 0x1000, 0);
            }
            break;
        case 1:
            omAddPrcObj(func_8010822C_storyresult, 0x3F00, 0x1000, 0);
            break;
        case 2:
            break;
        case 3:
            omAddPrcObj(func_801083A4_storyresult, 0x3F00, 0x1000, 0);
            break;
    }
    WipeColorSet(0, 0, 0);
    D_8010AC2A_storyresult = 2;
    D_8010AC28_storyresult = 20;
}

void func_80105C30_storyresult(omObjData *object) {
    if (D_8010A910_storyresult == 0) {
        if (D_800D530C_main != 0) {
            goto createWipe;
        }
    } else if (D_8010A910_storyresult == 1) {
        goto createWipe;
    } else {
        D_8010A910_storyresult--;
    }
    return;

createWipe:
    if (D_8010AC2A_storyresult >= 0) {
        WipeCreateOut(D_8010AC2A_storyresult, D_8010AC28_storyresult);
    }
    switch (D_8010A914_storyresult) {
        case 1:
            HuAudSeqFadeOut(30);
            break;
        case 2:
            HuAudSeqFadeOut(81);
            break;
    }
    object->func = func_80105CF8_storyresult;
}

void func_80105CF8_storyresult(omObjData *object) {
    u16 flags;

    if (WipeStatGet() == 0) {
        if (D_8010A912_storyresult != 0) {
            MBDBackKill();
            MBDBackClose();
        }
        HuWinAllKill();
        flags = 0x14;
        switch (D_8010ABE2_storyresult) {
            case 0:
            default:
                omOvlReturnEx(1);
                break;
            case 2:
                omOvlCallEx(D_8010AC32_storyresult, D_8010AC30_storyresult, flags);
                break;
            case 1:
                omOvlGotoEx(D_8010AC32_storyresult, D_8010AC30_storyresult, flags);
                break;
            case 3:
                omOvlGotoEx(D_8010AC32_storyresult, D_8010AC30_storyresult, 0x4090);
                break;
            case 4:
                omOvlGotoEx(D_8010AC32_storyresult, D_8010AC30_storyresult, 0x92);
                break;
        }
    }
}

void func_80105DEC_storyresult(MsetupModelEntry *entry, s16 model) {
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

void func_80105EA0_storyresult(MsetupModelEntry *entry, MsetupModelHandle *handle, s32 count) {
    s16 i;
    s16 model;
    s32 motion;

    if (entry == NULL || handle == NULL) {
        return;
    }
    for (i = 0; i < count; entry++, i++, handle++) {
        model = handle->model = func_8000B108_main(entry->dataId, entry->flags);
        func_80105DEC_storyresult(entry, model);
        motion = handle->motion = Hu3DData[model].motId;
        if (motion >= 0) {
            func_8001C814_main(model, -1, entry->motion);
        }
    }
}

u32 func_80105F7C_storyresult(u32 seed) {
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

u32 func_80106050_storyresult(void) {
    return D_8010A920_storyresult = func_80105F7C_storyresult(D_8010A920_storyresult);
}

u32 func_80106078_storyresult(u32 limit) {
    u32 random;

    random = D_8010A920_storyresult = func_80105F7C_storyresult(D_8010A920_storyresult);
    return (random & 0x7FFFFFFF) % limit;
}

void func_801060D0_storyresult(MsetupCameraPreset *preset) {
    CRot = preset->rot;
    D_8010AC0C_storyresult = CRot;
    Center = preset->center;
    CZoom = preset->zoom;
    if (preset->fov != D_8010A918_storyresult) {
        D_8010A918_storyresult = preset->fov;
        Hu3DCameraPerspectiveSet(0, D_8010A918_storyresult, D_8010AC24_storyresult, D_8010AC2C_storyresult);
    }
}

#ifdef NON_MATCHING
// Instruction scheduling differs around the Center address load.
void func_80106190_storyresult(void) {
    Vec pos, at, up;
    f32 rotX, rotY, rotZ;
    f32 upX, upY, upZ;
    f32 dx, dy, dz;
    f32 length;

    if (D_8010A91C_storyresult == 0) {
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
        pos = D_8010AC18_storyresult;
        at = D_8010AC00_storyresult;
        up.x = 0.0f;
        up.y = 1.0f;
        up.z = 0.0f;
    }
    D_800CE17C_main[0] = pos.x;
    D_800CE17C_main[1] = pos.z;
    D_800CE17C_main[-1] = CRot.y;
    D_800CE17C_main[2] = gCameraList->fov;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCameraPosSetV(0, &pos, &at, &up);
    Hu3DCamUpdateMtx(0);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54DD10", func_80106190_storyresult);
#endif

void func_80106754_storyresult(void) {
    while (1) {
        func_80106190_storyresult();
        HuPrcVSleep();
    }
}

void func_80106780_storyresult(MsetupCameraKeyframe *keys, f32 speed, void (*callback)(s16, s16, s16)) {
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
        D_8010AC0C_storyresult.x = CRot.x = interpolated.values.preset.rot.x;
        D_8010AC0C_storyresult.y = CRot.y = interpolated.values.preset.rot.y;
        D_8010AC0C_storyresult.z = CRot.z = interpolated.values.preset.rot.z;
        CZoom = interpolated.values.preset.zoom;
        gCameraList->fov = D_8010A918_storyresult = interpolated.values.preset.fov;
        if (callback != NULL) {
            onFrame((s16)duration, segment, i);
        }
        HuPrcVSleep();
    }
    segment++;
    D_8010AC0C_storyresult.x = CRot.x = keys[segment].values.preset.rot.x;
    D_8010AC0C_storyresult.y = CRot.y = keys[segment].values.preset.rot.y;
    D_8010AC0C_storyresult.z = CRot.z = keys[segment].values.preset.rot.z;
    CZoom = keys[segment].values.preset.zoom;
    Center.x = keys[segment].values.preset.center.x;
    Center.y = keys[segment].values.preset.center.y;
    Center.z = keys[segment].values.preset.center.z;
    gCameraList->fov = D_8010A918_storyresult = keys[segment].values.preset.fov;
    D_800CB99C_main = 0;
}

void func_80106C84_storyresult(void) {
    s16 i;
    s16 connectedCount;
    s16 port;
    s16 j;

    for (i = 0; i < 4; i++) {
        D_8010ABE8_storyresult.controllerPorts[i] = 0xFF;
        D_8010ABE8_storyresult.characters[i] = i;
        D_8010ABE8_storyresult.cpuDifficulty[i] = 0xFF;
        D_8010ABE8_storyresult.stars[i] = 0;
    }
    for (i = 0, connectedCount = 0; i < 4; i++) {
        if (CheckControllerRead(i)) {
            D_8010ABE8_storyresult.controllerPorts[connectedCount] = i;
            connectedCount++;
        }
    }
    for (i = 0; i < 4; i++) {
        if (D_8010ABE8_storyresult.controllerPorts[i] == 0xFF) {
            for (port = 0; port < 4; port++) {
                for (j = 0; j < 4; j++) {
                    if (D_8010ABE8_storyresult.controllerPorts[j] == port) {
                        break;
                    }
                }
                if (j == 4) {
                    break;
                }
            }
            D_8010ABE8_storyresult.controllerPorts[i] = port;
        }
    }
    D_8010ABE8_storyresult.totalTurns = 0;
    D_8010ABE8_storyresult.unk16 = 0;
    D_8010ABE8_storyresult.unk13 = 0;
    D_8010ABE8_storyresult.connectedCount = connectedCount;
    D_8010ABE8_storyresult.humanCount = 0;
    D_8010ABE8_storyresult.cpuCount = 4;
    D_8010ABE8_storyresult.boardIndex = 0;
    D_8010ABE0_storyresult = D_8010ABE8_storyresult.controllerPorts[0];
}

s16 func_80106E48_storyresult(void) {
    s16 result = 0;
    s16 winner;
    s16 i;

    switch (D_8010A924_storyresult[GwStory.unk0]) {
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
        D_8010ABE2_storyresult = 1;
        D_8010AC32_storyresult = 0x75;
        D_8010AC30_storyresult = 0;
        D_800CE20A_main = 15;
        omOvlGotoEx(0x75, 0, 0x14);
    }
    return result;
}
