#include "common.h"
#include "game/vibrator.h"
#include "game/camera.h"
#include "game/overlays/msetup.h"
#include "game/mallocblock.h"
#include "gcc/string.h"
#include "game/hmfmath.h"

typedef MsetupLinkedModel Array2D[2];

typedef struct MsetupSceneryState {
    f32 upperHeights[3];
    f32 lowerHeights[3];
    f32 rotation;
    Vec innerPositions[3];
    Vec outerPositions[6];
} MsetupSceneryState;

extern MsetupEntryAnim msetup_playerWorkTbl[];
extern s16 msetup_shadowMdl;
extern void (*msetup_setupProcTbl[])(void);
extern omObjData *msetup_backObj;
extern s16 (*msetup_partyStepTbl[])(s16);
extern s16 (*msetup_duelStepTbl[])(s16);
extern u8 msetup_storyBoardTbl[];
extern s16 (*msetup_mgModeStepTbl[])(s16);
extern s16 (*msetup_mgMode1PStepTbl[])(s16);
extern u8 msetup_storyStageKindTbl[];
extern u8 msetup_storyRivalTbl[];
extern s32 msetup_storyPartyBoardMesTbl[];
extern s32 msetup_storyDuelBoardMesTbl[];
extern s32 msetup_storyDuelRivalMesTbl[];
extern s32 msetup_storyDuelLuigiMesTbl[];
extern u16 msetup_exitCnt;
extern s16 msetup_exitRumbleF;
extern u8 msetup_exitRumbleCnt;
extern MsetupPlayerConfig msetup_playerConfig;
extern s16 msetup_wipeType;
extern s16 msetup_wipeTime;
extern s16 msetup_exitMode;
extern s16 msetup_exitEvtNo;
extern s16 msetup_exitOvlNo;
extern s16 msetup_backNarrowF;
extern f32 msetup_cameraFov;
extern u32 msetup_randSeed;
extern f32 msetup_cameraFar;
extern f32 msetup_cameraNear;
extern Vec msetup_cameraRot;
extern Process *msetup_summaryProc;
extern s32 msetup_boardPartySprTbl[];
extern s32 msetup_boardDuelSprTbl[];
extern s32 msetup_boardPartyMesTbl[];
extern s32 msetup_boardDuelMesTbl[];
extern s16 msetup_playerNum;
extern MsetupMenuState msetup_menu;
extern s16 msetup_winMode;
extern s16 msetup_setupMode;
extern s16 msetup_padNo;
extern u8 msetup_padNoLo;
extern s16 msetup_entryMdlTbl[];
extern s16 msetup_entryMotTbl[];
extern s32 msetup_stageMdlFileTbl[];
extern s32 msetup_tutorialPartyMesTbl[];
extern s32 msetup_tutorialDuelMesTbl[];
extern ModeCameraPreset msetup_cameraPreset;
extern MsetupCameraKeyframe msetup_cameraIntroKeyTbl[];
extern MsetupCameraKeyframe msetup_cameraStartKeyTbl[];
extern MsetupCameraKeyframe msetup_cameraCancelKeyTbl[];
extern s8 msetup_cameraLookF;
extern Vec msetup_cameraTarget;
extern Vec msetup_cameraPos;
extern f32 CFanLen;
extern f32 CFanOfs;

void msetup_WinMesSet(s32);
s32 msetup_WinMesWait(void);
void msetup_WinInsertMesSet(u32, s8);
void msetup_WinHomeClear(void);
s16 msetup_WinInputGet(void);
omObjData *msetup_EffObjCreate(void);
void msetup_PlayerProcCreate(s16);
void msetup_PlayerProcKill(s16);
void msetup_PlayerProcCreateEx(s16, s16);
void msetup_PlayerProcKillEx(s16, s16);
void msetup_WinAttrWait(s32, s32);
void msetup_ArrowObjKill(omObjData *object);
omObjData *msetup_ArrowObjCreate(s32, s32, s32);
void msetup_PanelCreate(Array2D *, s32, f32);
void msetup_PanelDynamicFree(MsetupLinkedModel *, s32);
void msetup_PanelSpinMove(Array2D *models, s16 count, s16 frames, f32 rotation, f32 height, f32 scale, f32 endScale, s16 animateBoard);
void msetup_SummaryEntrySet(Process *, s16, s16, s16);
s16 msetup_SummaryStateSet(Process *, s16);
s16 msetup_BoardSelect(MsetupMenuState *arg0);
void msetup_IntroCameraHook(s16, s16, s16);
void msetup_ModelEntryPosSet(MsetupModelEntry *, s16);
void msetup_ExitObjMain(omObjData *);
void msetup_TutorialSetupExec(s16);
void msetup_SysClose(void);
void msetup_MgModeSetupExec(s16 (**)(s16));
void msetup_ObjectSetup(void);
void msetup_ExitCheckObjMain(omObjData *);
void msetup_CameraProc(void);
void msetup_PlayerConfigInit(void);
void msetup_MenuProc(void);
void msetup_TumbleProc(void);
Process *msetup_SummaryCreate(void);
void msetup_CameraKeyframeExec(MsetupCameraKeyframe *, f32, void (*)(s16, s16, s16));

void msetup_ObjectSetup(void) {
    Hu3DCamInit(1);
    MapCollInit(1);
    Hu3DSprModelInit(25);
    omInitObjMan(51, 25);
    HuWinInit();
    omGameSysInit();
    Hu3DScreenClearF = 1;
    msetup_cameraNear = 80.0f;
    msetup_cameraFar = 6000.0f;
    msetup_cameraFov = 58.0f;
    Hu3DCameraPerspectiveSet(0, msetup_cameraFov, msetup_cameraNear, msetup_cameraFar);
    msetup_cameraRot.x = 0;
    msetup_cameraRot.y = 0;
    msetup_cameraRot.z = 0;
    CRot.x = 0;
    CRot.y = 0;
    CRot.z = 0;
    msetup_shadowMdl = -1;
    omAddObj(10000, 0, 0, -1, msetup_ExitCheckObjMain);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(2, 0, 0, 0);
    Hu3DGLightDirSet(2, 0.0f, 0.0f, 100.0f);
    Hu3DGLightColorSet(3, 240, 240, 240);
    Hu3DGLightDirSet(3, 0.0f, 100.0f, 0.0f);
    Hu3DGLightColorSet(1, 255, 255, 255);
    Hu3DBGColorSet(16, 16, 240);
    omPrcSetStatBit(omAddPrcObj(msetup_CameraProc, 0x1100, 0x400, 0), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    msetup_exitMode = 0;
    msetup_PlayerConfigInit();
    msetup_setupMode = -1;
    switch (omovlevtno) {
        case 0:
            msetup_setupMode = 0;
            break;
        case 1:
            msetup_setupMode = 1;
            break;
        case 2:
            msetup_setupMode = 2;
            break;
        case 3:
            msetup_setupMode = 3;
            break;
        case 4:
            msetup_setupMode = 4;
            break;
        case 5:
            msetup_setupMode = 5;
            break;
        case 6:
            msetup_setupMode = 6;
            break;
        case 7:
            msetup_setupMode = 7;
            break;
        case 8:
            msetup_setupMode = 8;
            break;
    }
    if (msetup_setupMode < 0) {
        msetup_exitCnt = 1;
    } else {
        omAddPrcObj(msetup_setupProcTbl[msetup_setupMode], 0x3F00, 0x1000, 0);
    }
    if (msetup_setupMode == 4) {
        WipeColorSet(255, 255, 255);
    } else {
        WipeColorSet(0, 0, 0);
    }
    msetup_wipeType = 11;
    msetup_wipeTime = 20;
}

void msetup_ExitCheckObjMain(omObjData *object) {
    s32 i;

    if (msetup_exitRumbleF != 0) {
        msetup_exitRumbleCnt--;
        if (msetup_exitRumbleCnt == 0) {
            for (i = 0; i < msetup_playerConfig.humanCount; i++) {
                RepeatVibrator(msetup_playerConfig.controllerPorts[i], 5, 0, 5);
            }
            msetup_exitRumbleCnt = 10;
        }
    }
    if (msetup_exitCnt == 0) {
        if (omSysExitReq != 0) {
            goto createWipe;
        }
    } else if (msetup_exitCnt == 1) {
        goto createWipe;
    } else {
        msetup_exitCnt--;
    }
    return;

createWipe:
    if (msetup_setupMode == 4) {
        WipeColorSet(255, 255, 255);
        msetup_wipeType = 11;
    } else {
        msetup_wipeType = 2;
    }
    if (msetup_wipeType >= 0) {
        WipeCreateOut(msetup_wipeType, msetup_wipeTime);
    }
    if (msetup_exitMode == 0) {
        HuAudSeqFadeOut(15);
    }
    object->func = msetup_ExitObjMain;
}

void msetup_ExitObjMain(omObjData *object) {
    u16 flags;

    if (WipeStatGet() == 0) {
        HuWinAllKill();
        msetup_SysClose();
        flags = 0x14;
        switch (msetup_exitMode) {
            case 0:
            default:
                omOvlReturnEx(1);
                break;
            case 2:
                omOvlCallEx(msetup_exitOvlNo, msetup_exitEvtNo, flags);
                break;
            case 1:
                omOvlGotoEx(msetup_exitOvlNo, msetup_exitEvtNo, flags);
                break;
            case 3:
                omOvlGotoEx(msetup_exitOvlNo, msetup_exitEvtNo, 0x4090);
                break;
            case 4:
                omOvlGotoEx(msetup_exitOvlNo, msetup_exitEvtNo, 0x92);
                break;
        }
    }
}

void msetup_ModelEntryReadList(MsetupModelEntry *entry) {
    s32 i;
    s16 model;
    s32 motion;

    for (i = 0; entry->dataId != -1; entry++, i++) {
        model = msetup_entryMdlTbl[(s16)i] = Hu3DModelRead(entry->dataId, entry->flags);
        msetup_ModelEntryPosSet(entry, model);
        motion = msetup_entryMotTbl[(s16)i] = Hu3DData[model].motId;
        if (motion != -1) {
            Hu3DMotionAttrSet(model, -1, entry->motion);
        }
    }
}

void msetup_ModelEntryPosSet(MsetupModelEntry *entry, s16 model) {
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

void msetup_ModelEntryReadAll(MsetupModelEntry *entry, MsetupModelHandle *handle, s32 count) {
    s16 i;
    s16 model;
    s32 motion;

    if (entry == NULL || handle == NULL) {
        return;
    }
    for (i = 0; i < count; entry++, i++, handle++) {
        model = handle->model = Hu3DModelRead(entry->dataId, entry->flags);
        msetup_ModelEntryPosSet(entry, model);
        motion = handle->motion = Hu3DData[model].motId;
        if (motion >= 0) {
            Hu3DMotionAttrSet(model, -1, entry->motion);
        }
    }
}

u32 msetup_RandSeedCalc(u32 seed) {
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

u32 msetup_Rand(void) {
    return msetup_randSeed = msetup_RandSeedCalc(msetup_randSeed);
}

u32 msetup_RandMod(u32 limit) {
    u32 random;

    random = msetup_randSeed = msetup_RandSeedCalc(msetup_randSeed);
    return (random & 0x7FFFFFFF) % limit;
}

void msetup_CameraPresetSet(ModeCameraPreset *preset) {
    CRot = preset->rot;
    msetup_cameraRot = CRot;
    Center = preset->center;
    CZoom = preset->zoom;
    if (preset->fov != msetup_cameraFov) {
        msetup_cameraFov = preset->fov;
        Hu3DCameraPerspectiveSet(0, msetup_cameraFov, msetup_cameraNear, msetup_cameraFar);
    }
}

void msetup_CameraProc(void) {
    Vec pos, at, up;
    f32 rotX, rotY, rotZ;
    f32 upX, upY, upZ;
    f32 dx, dy, dz;
    f32 length;

    while (1) {
        if (msetup_cameraLookF == 0) {
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
            pos = msetup_cameraPos;
            at = msetup_cameraTarget;
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
        HuPrcVSleep();
    }
}

void msetup_CameraKeyframeExec(MsetupCameraKeyframe *keys, f32 speed, void (*callback)(s16, s16, s16)) {
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
        msetup_cameraRot.x = CRot.x = interpolated.values.preset.rot.x;
        msetup_cameraRot.y = CRot.y = interpolated.values.preset.rot.y;
        msetup_cameraRot.z = CRot.z = interpolated.values.preset.rot.z;
        CZoom = interpolated.values.preset.zoom;
        gCameraList->fov = msetup_cameraFov = interpolated.values.preset.fov;
        if (callback != NULL) {
            onFrame((s16)duration, segment, i);
        }
        HuPrcVSleep();
    }
    segment++;
    msetup_cameraRot.x = CRot.x = keys[segment].values.preset.rot.x;
    msetup_cameraRot.y = CRot.y = keys[segment].values.preset.rot.y;
    msetup_cameraRot.z = CRot.z = keys[segment].values.preset.rot.z;
    CZoom = keys[segment].values.preset.zoom;
    Center.x = keys[segment].values.preset.center.x;
    Center.y = keys[segment].values.preset.center.y;
    Center.z = keys[segment].values.preset.center.z;
    gCameraList->fov = msetup_cameraFov = keys[segment].values.preset.fov;
    winPauseF = 0;
}

void msetup_PlayerConfigInit(void) {
    s16 i;
    s16 connectedCount;
    s16 port;
    s16 j;

    for (i = 0; i < 4; i++) {
        msetup_playerConfig.controllerPorts[i] = 0xFF;
        msetup_playerConfig.characters[i] = i;
        msetup_playerConfig.cpuDifficulty[i] = 0xFF;
        msetup_playerConfig.stars[i] = 0;
    }
    for (i = 0, connectedCount = 0; i < 4; i++) {
        if (CheckControllerRead(i)) {
            msetup_playerConfig.controllerPorts[connectedCount] = i;
            connectedCount++;
        }
    }
    for (i = 0; i < 4; i++) {
        if (msetup_playerConfig.controllerPorts[i] == 0xFF) {
            for (port = 0; port < 4; port++) {
                for (j = 0; j < 4; j++) {
                    if (msetup_playerConfig.controllerPorts[j] == port) {
                        break;
                    }
                }
                if (j == 4) {
                    break;
                }
            }
            msetup_playerConfig.controllerPorts[i] = port;
        }
    }
    msetup_playerConfig.totalTurns = 0;
    msetup_playerConfig.unk16 = 0;
    msetup_playerConfig.unk13 = 0;
    msetup_playerConfig.connectedCount = connectedCount;
    msetup_playerConfig.humanCount = 0;
    msetup_playerConfig.cpuCount = 4;
    msetup_playerConfig.boardIndex = 0;
    msetup_playerConfig.unk17 = 0;
    msetup_padNo = msetup_playerConfig.controllerPorts[0];
}

f32 msetup_BackPartPosRand(Vec *pos, u32 mask, f32 radius) {
    u32 random;
    f32 angle;

    random = msetup_Rand() & mask;
    pos->y -= (f32)random;
    random = msetup_Rand() & 0x7FFFFFFF;
    if (msetup_backNarrowF != 0) {
        random %= 120;
        random += 120;
    } else {
        random %= 360;
    }
    angle = random;
    pos->x = radius * sindf(angle);
    pos->z = radius * cosdf(angle);
    return angle;
}

void msetup_BackObjMain(omObjData *object) {
    MsetupSceneryState *state;
    Vec *pos;
    s32 i;
    u16 model;
    f32 height;

    state = object->data;
    for (i = 0; i < 3; i++) {
        model = object->model[i + 4];
        height = state->upperHeights[i];
        height += 100.0f;
        if (height >= 4000.0f) {
            height -= 12000.0f;
        }
        Hu3DModelPosSet(model, 0.0f, height, 0.0f);
        Hu3DModelRotSet(model, 0.0f, state->rotation, 0.0f);
        state->upperHeights[i] = height;
    }
    state->rotation += 2.0f;
    for (i = 0; i < 3; i++) {
        model = object->model[i + 1];
        height = state->lowerHeights[i];
        height += 60.0f;
        if (height >= 4000.0f) {
            height -= 12000.0f;
        }
        Hu3DModelPosSet(model, 0.0f, height, 0.0f);
        state->lowerHeights[i] = height;
    }
    for (i = 0; i < 3; i++) {
        model = object->model[i + 7];
        pos = &state->innerPositions[i];
        pos->y += 40.0f;
        if (pos->y > 1000.0f) {
            pos->y -= 12000.0f;
            msetup_BackPartPosRand(pos, 0xFFF, 900.00006103515625f);
        }
        Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    }
    for (i = 0; i < 6; i++) {
        model = object->model[i + 10];
        pos = &state->outerPositions[i];
        pos->y += 75.0f;
        if (pos->y > 1000.0f) {
            pos->y -= 12000.0f;
            height = msetup_BackPartPosRand(pos, 0xFFF, 906.00006103515625f);
            Hu3DModelRotSet(model, 0.0f, height - 180.0f, 0.0f);
        }
        Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    }
}

omObjData *msetup_BackObjCreate(void) {
    MsetupSceneryState *state;
    omObjData *object;
    Vec *pos;
    s32 i;
    s16 model;
    s16 source;
    f32 height;

    msetup_backNarrowF = 0;
    object = omAddObj(0x17D0, 16, 0, -1, msetup_BackObjMain);
    msetup_backObj = object;
    if (object == NULL) {
        return NULL;
    }
    object->model[0] = -1;
    state = HuMemAllocTag(sizeof(MsetupSceneryState), TAG_OVERLAY);
    memset(state, 0, sizeof(MsetupSceneryState));
    object->data = state;
    height = 0.0f;
    source = -1;
    for (i = 0; i < 3; i++) {
        if (source < 0) {
            model = Hu3DModelRead(0x140000, 0x2B9);
            source = model;
        } else {
            model = Hu3DModelLink(source);
        }
        object->model[i + 4] = model;
        Hu3DModelPosSet(model, 0.0f, height, 0.0f);
        Hu3DModelScaleSet(model, 1.2f, 2.0f, 1.2f);
        state->upperHeights[i] = height;
        height -= 4000.0f;
    }
    state->rotation = 0.0f;
    height = state->rotation;
    source = -1;
    for (i = 0; i < 3; i++) {
        if (source < 0) {
            model = Hu3DModelRead(0x140004, 0x299);
            source = model;
        } else {
            model = Hu3DModelLink(source);
        }
        object->model[i + 1] = model;
        Hu3DModelPosSet(model, 0.0f, height, 0.0f);
        Hu3DModelScaleSet(model, 1.2f, 2.0f, 1.2f);
        state->lowerHeights[i] = height;
        height -= 4000.0f;
    }
    source = -1;
    for (i = 0; i < 3; i++) {
        if (source < 0) {
            model = Hu3DModelRead(0x140002, 0x299);
            source = model;
        } else {
            model = Hu3DModelLink(source);
        }
        object->model[i + 7] = model;
        pos = &state->innerPositions[i];
        pos->y = 0.0f;
        msetup_BackPartPosRand(pos, 0x1FFF, 900.00006103515625f);
        Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    }
    source = -1;
    for (i = 0; i < 6; i++) {
        if (source < 0) {
            model = Hu3DModelRead(0x140005, 0x299);
            source = model;
        } else {
            model = Hu3DModelLink(source);
        }
        object->model[i + 10] = model;
        pos = &state->outerPositions[i];
        pos->y = 0.0f;
        height = msetup_BackPartPosRand(pos, 0x1FFF, 906.00006103515625f);
        Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
        Hu3DModelRotSet(model, 0.0f, height - 180.0f, 0.0f);
    }
    return object;
}

s16 msetup_PartyPlayerNumStep(s16 stateIndex) {
    msetup_menu.state = 1;
    do {
        HuPrcVSleep();
    } while (msetup_menu.state != 0);

    if (msetup_menu.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 msetup_PartyChrStep(s16 stateIndex) {
    s32 i;

    msetup_menu.state = 2;
    do {
        HuPrcVSleep();
    } while (msetup_menu.state != 0);

    if (msetup_menu.result != -1) {
        msetup_winMode = 0;
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
        msetup_PlayerProcCreate(msetup_playerNum);
        for (i = 4; i != 0; i--) {
            HuPrcVSleep();
        }
        HuAudFXPlay(0x2DB);
        for (i = 0; i < msetup_playerNum; i++) {
            msetup_playerWorkTbl[i].state = 1;
        }
        while (msetup_playerWorkTbl[3].state != 0) {
            HuPrcVSleep();
        }
    }
    if (msetup_menu.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 msetup_PartyComLevelStep(s16 stateIndex) {
    s32 i;

    if (msetup_playerConfig.cpuCount != 0) {
        for (i = 0; i < msetup_playerNum; i++) {
            msetup_playerWorkTbl[i].state = 7;
        }
        msetup_menu.state = 3;
        do {
            HuPrcVSleep();
        } while (msetup_menu.state != 0);
    } else {
        msetup_winMode = 1;
    }
    if (msetup_menu.result == -1) {
        HuAudFXPlay(0x2E4);
        msetup_PlayerProcKill(msetup_playerNum);
    }
    if (msetup_menu.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 msetup_PartyHandicapStep(s16 stateIndex) {
    s32 i;

    if (msetup_menu.result < 0) {
        for (i = 0; i < msetup_playerNum; i++) {
            msetup_playerWorkTbl[i].state = 10;
        }
    }
    msetup_menu.state = 6;
    do {
        HuPrcVSleep();
    } while (msetup_menu.state != 0);

    if (msetup_menu.result == 0) {
        msetup_menu.state = 4;
        do {
            HuPrcVSleep();
        } while (msetup_menu.state != 0);
        if (msetup_menu.result >= 0) {
            stateIndex++;
        }
    } else {
        for (i = 0; i < msetup_playerNum; i++) {
            msetup_playerConfig.stars[i] = 0;
        }
        if (msetup_menu.result < 0) {
            stateIndex--;
        } else {
            stateIndex++;
        }
    }
    return stateIndex;
}

s16 msetup_PartyBoardStep(s16 stateIndex) {
    s32 i;

    for (i = 0; i < msetup_playerNum; i++) {
        msetup_playerWorkTbl[i].state = 12;
    }
    msetup_winMode = 2;
    HuPrcVSleep();
    msetup_WinAttrWait(0x4000, 0x4000);
    msetup_menu.state = 8;
    do {
        HuPrcVSleep();
    } while (msetup_menu.state != 0);

    if (msetup_menu.result < 0) {
        msetup_SummaryStateSet(msetup_summaryProc, 0xFF);
    } else {
        msetup_SummaryStateSet(msetup_summaryProc, 1);
    }
    msetup_winMode = 1;
    HuPrcVSleep();
    msetup_WinAttrWait(0x4000, 0x4000);
    for (i = 0; i < msetup_playerNum; i++) {
        msetup_playerWorkTbl[i].state = 11;
    }
    HuPrcVSleep();
    if (msetup_menu.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 msetup_PartyTurnStep(s16 stateIndex) {
    msetup_menu.state = 5;
    do {
        HuPrcVSleep();
    } while (msetup_menu.state != 0);

    if (msetup_menu.result == -1) {
        msetup_SummaryStateSet(msetup_summaryProc, 3);
    } else {
        msetup_SummaryStateSet(msetup_summaryProc, 4);
    }

    if (msetup_menu.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 msetup_PartyMgPackStep(s16 stateIndex) {
    s32 i;

    msetup_menu.state = 13;
    do {
        HuPrcVSleep();
    } while (msetup_menu.state != 0);

    if (msetup_menu.result == 0) {
        msetup_playerConfig.unk17 = 0;
    } else {
        msetup_playerConfig.unk17 = 1;
    }

    if (msetup_menu.result == -1) {
        msetup_SummaryStateSet(msetup_summaryProc, 6);
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
    }

    if (msetup_menu.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 msetup_PartyBonusStep(s16 stateIndex) {
    msetup_menu.state = 7;
    do {
        HuPrcVSleep();
    } while (msetup_menu.state != 0);

    if (msetup_menu.result == 0) {
        msetup_playerConfig.unk13 = 1;
    } else {
        msetup_playerConfig.unk13 = 0;
    }

    if (msetup_menu.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 msetup_PartyConfirmStep(s16 stateIndex) {
    msetup_menu.result = 0;
    msetup_WinMesSet(0x152D);
    if (msetup_WinMesWait() == 0) {
        msetup_WinMesSet(0x152F);
        stateIndex = -2;
        msetup_WinMesWait();
        HuAudFXPlay(0x2A6);
    } else {
        msetup_WinMesSet(0x152E);
        if (msetup_WinMesWait() == 0) {
            msetup_SummaryStateSet(msetup_summaryProc, 9);
            HuAudFXPlay(0x2E4);
            stateIndex = 0;
            msetup_PlayerProcKill(msetup_playerNum);
        } else {
            msetup_menu.result = -1;
            stateIndex--;
        }
    }
    return stateIndex;
}

void msetup_IntroCameraHook(s16 countdown, s16 pointIndex, s16 frame) {
    if (frame == 0x31) {
        HuAudSeqPlay(9);
    }
}

void msetup_PartySetupProc(void) {
    s16 state[2];
    Process *process;
    s16 step;
    s32 i;

    msetup_playerNum = 4;
    _ClearFlag(0);
    Hu3DModelPosSet(Hu3DModelRead(msetup_stageMdlFileTbl[2], 0x2B9), 0.0f, -37.5f, 100.0f);
    msetup_BackObjCreate();
    process = omAddPrcObj(msetup_MenuProc, 0xBB8, 0x1000, 0);
    memset(&msetup_menu, 0, sizeof(msetup_menu));
    msetup_menu.result = -1;
    process->user_data = &msetup_menu;
    msetup_summaryProc = msetup_SummaryCreate();
    process = omAddPrcObj(msetup_TumbleProc, 0x3E8, 0x600, 0);
    memset(state, 0, sizeof(state));
    process->user_data = state;
    msetup_CameraPresetSet(&msetup_cameraPreset);
    HuPrcVSleep();
    WipeCreateIn(msetup_wipeType, 16);
    HuAudFXPlay(0x2D8);
    msetup_CameraKeyframeExec(msetup_cameraIntroKeyTbl, 22.0f, msetup_IntroCameraHook);
    msetup_backNarrowF = 1;
    state[0] = 1;
    do {
        HuPrcVSleep();
    } while (state[0] == 1);
    msetup_winMode = 1;
    msetup_WinAttrWait(0x4000, 0x4000);
    if (!_CheckFlag(0x1A)) {
        _SetFlag(0x1A);
        msetup_WinMesSet(0x1500);
        msetup_WinMesWait();
    }
    msetup_WinMesSet(0x1502);
    msetup_WinMesWait();
    step = 0;
    do {
        step = msetup_partyStepTbl[step](step);
    } while (step >= 0);
    msetup_SummaryStateSet(msetup_summaryProc, 8);
    msetup_winMode = 0;
    if (step < -1) {
        for (i = 0; i < msetup_playerNum; i++) {
            msetup_playerWorkTbl[i].state = 12;
        }
        HuPrcVSleep();
        for (i = 0; i < msetup_playerNum; i++) {
            msetup_playerWorkTbl[i].state = 16;
        }
        HuAudSeqFadeOut(390);
        msetup_exitRumbleF = 1;
        HuAudFXPlay(0x2DF);
        msetup_CameraKeyframeExec(msetup_cameraStartKeyTbl, 22.0f, NULL);
        GwSystem.current_board_index = msetup_playerConfig.boardIndex;
        GwSystem.total_turns = msetup_playerConfig.totalTurns;
        GwSystem.current_game_length = msetup_playerConfig.unk16;
        for (i = 0; i < msetup_playerNum; i++) {
            GwPlayer[i].chr = msetup_playerConfig.characters[i];
            GwPlayer[i].star = msetup_playerConfig.stars[i];
            GwPlayer[i].coin = 0;
            GwPlayer[i].pad = msetup_playerConfig.controllerPorts[i];
            if (msetup_playerConfig.cpuDifficulty[i] < 4) {
                GwPlayer[i].cpu_difficulty = msetup_playerConfig.cpuDifficulty[i];
                GwPlayer[i].stat = 1;
            } else {
                GwPlayer[i].cpu_difficulty = 1;
                GwPlayer[i].stat = 0;
            }
        }
        if (msetup_playerConfig.unk13 != 0) {
            _SetFlag(0x1B);
        } else {
            _ClearFlag(0x1B);
        }
        if (msetup_playerConfig.unk17 != 0) {
            _SetFlag(0x20);
        } else {
            _ClearFlag(0x20);
        }
        msetup_exitMode = 4;
        msetup_exitOvlNo = 71;
        msetup_exitEvtNo = 0;
    } else {
        msetup_exitCnt = 75;
        HuAudFXPlay(0x2EC);
        msetup_CameraKeyframeExec(msetup_cameraCancelKeyTbl, 25.0f, NULL);
    }
    msetup_SummaryStateSet(msetup_summaryProc, 0xFF);
    msetup_exitCnt = 1;
    while (1) {
        HuPrcVSleep();
    }
}

s16 msetup_DuelPlayerNumStep(s16 stateIndex) {
    msetup_menu.state = 9;
    do {
        HuPrcVSleep();
    } while (msetup_menu.state != 0);

    if (msetup_menu.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 msetup_DuelChrStep(s16 stateIndex) {
    s32 i;

    msetup_menu.state = 2;
    do {
        HuPrcVSleep();
    } while (msetup_menu.state != 0);

    if (msetup_menu.result != -1) {
        msetup_winMode = 0;
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
        msetup_PlayerProcCreate(msetup_playerNum);
        HuAudFXPlay(0x2DB);
        for (i = 0; i < msetup_playerNum; i++) {
            msetup_playerWorkTbl[i].state = 1;
        }
        while (msetup_playerWorkTbl[1].state != 0) {
            HuPrcVSleep();
        }
    }
    if (msetup_menu.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 msetup_DuelComLevelStep(s16 stateIndex) {
    s32 i;

    if (msetup_playerConfig.cpuCount != 0) {
        for (i = 0; i < msetup_playerNum; i++) {
            msetup_playerWorkTbl[i].state = 6;
        }
        msetup_menu.state = 3;
        do {
            HuPrcVSleep();
        } while (msetup_menu.state != 0);
    } else {
        msetup_winMode = 1;
    }
    if (msetup_menu.result == -1) {
        HuAudFXPlay(0x2E4);
        msetup_PlayerProcKill(msetup_playerNum);
    }
    if (msetup_menu.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 msetup_DuelHandicapStep(s16 stateIndex) {
    s32 i;

    for (i = 0; i < msetup_playerNum; i++) {
        msetup_playerWorkTbl[i].state = 14;
    }
    msetup_menu.state = 11;
    do {
        HuPrcVSleep();
    } while (msetup_menu.state != 0);

    if (msetup_menu.result == 0) {
        msetup_menu.state = 10;
        do {
            HuPrcVSleep();
        } while (msetup_menu.state != 0);
        if (msetup_menu.result >= 0) {
            stateIndex++;
        }
    } else {
        for (i = 0; i < msetup_playerNum; i++) {
            msetup_playerConfig.stars[i] = 5;
        }
        if (msetup_menu.result < 0) {
            stateIndex--;
        } else {
            stateIndex++;
        }
    }
    return stateIndex;
}

s16 msetup_DuelBoardStep(s16 stateIndex) {
    s32 i;

    msetup_menu.state = 8;
    do {
        HuPrcVSleep();
    } while (msetup_menu.state != 0);

    if (msetup_menu.result < 0) {
        msetup_SummaryStateSet(msetup_summaryProc, 0xFF);
    } else {
        msetup_SummaryStateSet(msetup_summaryProc, 1);
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
    }

    if (msetup_menu.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 msetup_DuelTurnStep(s16 stateIndex) {
    msetup_menu.state = 5;
    do {
        HuPrcVSleep();
    } while (msetup_menu.state != 0);

    if (msetup_menu.result == -1) {
        msetup_SummaryStateSet(msetup_summaryProc, 3);
    } else {
        msetup_SummaryStateSet(msetup_summaryProc, 4);
    }

    if (msetup_menu.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 msetup_DuelMgPackStep(s16 stateIndex) {
    s32 i;

    msetup_menu.state = 13;
    do {
        HuPrcVSleep();
    } while (msetup_menu.state != 0);

    if (msetup_menu.result == 0) {
        msetup_playerConfig.unk17 = 0;
    } else {
        msetup_playerConfig.unk17 = 1;
    }

    if (msetup_menu.result == -1) {
        msetup_SummaryStateSet(msetup_summaryProc, 6);
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
    }

    if (msetup_menu.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 msetup_DuelConfirmStep(s16 stateIndex) {
    msetup_menu.result = 0;
    msetup_WinMesSet(0x241B);
    if (msetup_WinMesWait() == 0) {
        msetup_WinMesSet(0x241D);
        stateIndex = -2;
        msetup_WinMesWait();
        HuAudFXPlay(0x2A6);
    } else {
        msetup_WinMesSet(0x241C);
        if (msetup_WinMesWait() == 0) {
            msetup_SummaryStateSet(msetup_summaryProc, 9);
            HuAudFXPlay(0x2E4);
            stateIndex = 0;
            msetup_PlayerProcKill(msetup_playerNum);
        } else {
            msetup_menu.result = -1;
            stateIndex--;
        }
    }
    return stateIndex;
}

void msetup_DuelSetupProc(void) {
    s16 state[2];
    Process *process;
    s16 step;
    s32 i;

    msetup_playerNum = 2;
    _ClearFlag(0);
    Hu3DModelPosSet(Hu3DModelRead(msetup_stageMdlFileTbl[1], 0x2B9), 0.0f, -37.5f, 100.0f);
    msetup_BackObjCreate();
    process = omAddPrcObj(msetup_MenuProc, 0xBB8, 0x1000, 0);
    memset(&msetup_menu, 0, sizeof(msetup_menu));
    msetup_menu.result = -1;
    process->user_data = &msetup_menu;
    msetup_summaryProc = msetup_SummaryCreate();
    process = omAddPrcObj(msetup_TumbleProc, 0x3E8, 0x600, 0);
    memset(state, 0, sizeof(state));
    process->user_data = state;
    msetup_CameraPresetSet(&msetup_cameraPreset);
    HuPrcVSleep();
    for (i = 0; i < msetup_playerNum; i++) {
        msetup_playerConfig.stars[i] = 5;
    }
    WipeCreateIn(msetup_wipeType, 16);
    HuAudFXPlay(0x2D8);
    msetup_CameraKeyframeExec(msetup_cameraIntroKeyTbl, 22.0f, msetup_IntroCameraHook);
    msetup_backNarrowF = 1;
    state[0] = 1;
    do {
        HuPrcVSleep();
    } while (state[0] == 1);
    msetup_winMode = 1;
    msetup_WinAttrWait(0x4000, 0x4000);
    if (!_CheckFlag(0x19)) {
        _SetFlag(0x19);
        msetup_WinMesSet(0x2400);
        msetup_WinMesWait();
    }
    msetup_WinMesSet(0x2402);
    msetup_WinMesWait();
    step = 0;
    do {
        step = msetup_duelStepTbl[step](step);
    } while (step >= 0);
    msetup_SummaryStateSet(msetup_summaryProc, 8);
    msetup_winMode = 0;
    if (step < -1) {
        for (i = 0; i < msetup_playerNum; i++) {
            msetup_playerWorkTbl[i].state = 12;
        }
        HuPrcVSleep();
        for (i = 0; i < msetup_playerNum; i++) {
            msetup_playerWorkTbl[i].state = 16;
        }
        HuAudSeqFadeOut(390);
        msetup_exitRumbleF = 1;
        HuAudFXPlay(0x2DF);
        msetup_CameraKeyframeExec(msetup_cameraStartKeyTbl, 22.0f, NULL);
        GwSystem.current_board_index = msetup_playerConfig.boardIndex;
        GwSystem.total_turns = msetup_playerConfig.totalTurns;
        for (i = 0; i < msetup_playerNum; i++) {
            GwPlayer[i].chr = msetup_playerConfig.characters[i];
            GwPlayer[i].star = msetup_playerConfig.stars[i];
            GwPlayer[i].coin = 0;
            GwPlayer[i].pad = msetup_playerConfig.controllerPorts[i];
            if (msetup_playerConfig.cpuDifficulty[i] < 4) {
                GwPlayer[i].cpu_difficulty = msetup_playerConfig.cpuDifficulty[i];
                GwPlayer[i].stat = 1;
            } else {
                GwPlayer[i].cpu_difficulty = 1;
                GwPlayer[i].stat = 0;
            }
        }
        if (msetup_playerConfig.unk17 != 0) {
            _SetFlag(0x20);
        } else {
            _ClearFlag(0x20);
        }
        msetup_exitMode = 3;
        msetup_exitOvlNo = 90;
        msetup_exitEvtNo = 0;
    } else {
        msetup_exitCnt = 75;
        HuAudFXPlay(0x2EC);
        msetup_CameraKeyframeExec(msetup_cameraCancelKeyTbl, 25.0f, NULL);
    }
    msetup_SummaryStateSet(msetup_summaryProc, 0xFF);
    msetup_exitCnt = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void msetup_StoryPlayerInit(void) {
    u8 characters[4];
    s32 i;
    s32 player;
    s16 mode;
    u8 opponent;
    u8 character;
    u8 stars;
    u32 random;
    u32 first;
    u32 second;

    GwSystem.current_board_index = msetup_storyBoardTbl[GwStory.unk0];
    GwSystem.current_game_length = 0;
    mode = msetup_storyStageKindTbl[GwStory.unk0];
    stars = 0;
    if (mode == 1) {
        GwSystem.total_turns = 20;
        stars = 5;
    } else {
        GwSystem.total_turns = 15;
    }
    GwPlayer[0].chr = GwStory.unk1;
    GwPlayer[0].star = stars;
    GwPlayer[0].pad = msetup_padNoLo;
    GwPlayer[0].cpu_difficulty = 1;
    GwPlayer[0].stat = 0;
    GwPlayer[0].coin = 0;
    opponent = msetup_storyRivalTbl[GwStory.unk0];
    if (opponent == GwStory.unk1) {
        opponent = 1;
    }
    i = 0;
    if (mode == 1) {
        GwPlayer[1].chr = opponent;
        GwPlayer[1].star = stars;
        GwPlayer[1].pad = msetup_playerConfig.controllerPorts[1];
        GwPlayer[1].cpu_difficulty = GwStory.unk2;
        GwPlayer[1].stat = 1;
        GwPlayer[1].coin = 0;
    } else {
        character = 0;
        do {
            if (character != GwStory.unk1) {
                if (character != opponent) {
                    characters[i++] = character;
                }
            }
            character++;
        } while (i < 4);
        for (i = 96; i != 0; i--) {
            random = msetup_Rand();
            first = random & 3;
            second = (random >> 2) & 3;
            character = characters[first];
            characters[first] = characters[second];
            characters[second] = character;
        }
        player = 1;
        if (GwStory.unk0 >= 11) {
            GwPlayer[player].chr = opponent;
            GwPlayer[player].star = stars;
            GwPlayer[player].pad = msetup_playerConfig.controllerPorts[1];
            GwPlayer[player].cpu_difficulty = GwStory.unk2;
            GwPlayer[player].stat = 1;
            GwPlayer[player].coin = 0;
            player = 2;
        }
        for (i = 0; player < 4; player++, i++) {
            GwPlayer[player].chr = characters[i];
            GwPlayer[player].star = stars;
            GwPlayer[player].pad = msetup_playerConfig.controllerPorts[player];
            GwPlayer[player].cpu_difficulty = GwStory.unk2;
            GwPlayer[player].stat = 1;
            GwPlayer[player].coin = 0;
        }
    }
}

void msetup_StoryPartySetupProc(void) {
    s16 state[2];
    Process *process;
    s32 i;

    msetup_playerNum = 4;
    msetup_StoryPlayerInit();
    msetup_playerConfig.boardIndex = GwSystem.current_board_index;
    msetup_playerConfig.totalTurns = GwSystem.total_turns;
    msetup_playerConfig.unk17 = _CheckFlag(0x29);
    for (i = 0; i < msetup_playerNum; i++) {
        msetup_playerConfig.characters[i] = GwPlayer[i].chr;
        msetup_playerConfig.stars[i] = GwPlayer[i].star;
        msetup_playerConfig.controllerPorts[i] = GwPlayer[i].pad;
        if (GwPlayer[i].stat & 1) {
            msetup_playerConfig.cpuDifficulty[i] = GwPlayer[i].cpu_difficulty;
        } else {
            msetup_playerConfig.cpuDifficulty[i] = 0xFF;
        }
    }
    msetup_playerConfig.humanCount = 1;
    msetup_playerConfig.cpuCount = 3;
    Hu3DModelPosSet(Hu3DModelRead(msetup_stageMdlFileTbl[2], 0x2B9), 0.0f, -37.5f, 100.0f);
    msetup_BackObjCreate();
    process = omAddPrcObj(msetup_MenuProc, 0xBB8, 0x1000, 0);
    memset(&msetup_menu, 0, sizeof(msetup_menu));
    msetup_menu.result = -1;
    process->user_data = &msetup_menu;
    process = omAddPrcObj(msetup_TumbleProc, 0x3E8, 0x600, 0);
    memset(state, 0, sizeof(state));
    process->user_data = state;
    msetup_CameraPresetSet(&msetup_cameraPreset);
    msetup_PlayerProcCreate(msetup_playerNum);
    HuPrcVSleep();
    WipeCreateIn(msetup_wipeType, 16);
    HuAudFXPlay(0x2D8);
    msetup_CameraKeyframeExec(msetup_cameraIntroKeyTbl, 22.0f, msetup_IntroCameraHook);
    msetup_backNarrowF = 1;
    state[0] = 1;
    HuAudFXPlay(0x2DB);
    msetup_playerWorkTbl[0].state = 1;
    while (state[0] == 1) {
        HuPrcVSleep();
    }
    msetup_winMode = 1;
    msetup_WinAttrWait(0x4000, 0x4000);
    msetup_WinHomeClear();
    msetup_WinInsertMesSet(msetup_playerConfig.characters[0] + 0x1C00, 0);
    msetup_WinMesSet(0x1A00);
    msetup_WinMesWait();
    msetup_WinMesSet(msetup_storyPartyBoardMesTbl[msetup_playerConfig.boardIndex]);
    msetup_WinMesWait();
    msetup_WinMesSet(0x1A07);
    msetup_WinMesWait();
    msetup_WinHomeClear();
    msetup_winMode = 2;
    msetup_menu.state = 12;
    do {
        HuPrcVSleep();
    } while (msetup_menu.state != 0);
    msetup_winMode = 1;
    HuPrcVSleep();
    msetup_WinAttrWait(0x4000, 0x4000);
    msetup_WinMesSet(0x1A08);
    msetup_WinMesWait();
    msetup_winMode = 0;
    HuAudFXPlay(0x2DB);
    for (i = 1; i < msetup_playerNum; i++) {
        msetup_playerWorkTbl[i].state = 1;
    }
    for (i = 7; i != 0; i--) {
        HuPrcVSleep();
    }
    msetup_playerWorkTbl[0].state = 17;
    while (msetup_playerWorkTbl[msetup_playerNum - 1].state != 0) {
        HuPrcVSleep();
    }
    msetup_winMode = 1;
    msetup_WinMesSet(0x1A09);
    msetup_WinMesWait();
    msetup_WinMesSet(0x1A0A);
    msetup_WinMesWait();
    msetup_WinMesSet(0x1A0B);
    msetup_WinMesWait();
    if (msetup_playerConfig.unk17 != 0) {
        msetup_WinMesSet(0x1A10);
    } else {
        msetup_WinMesSet(0x1A0F);
    }
    msetup_WinMesWait();
    msetup_WinMesSet(0x1A0C);
    msetup_WinMesWait();
    i = 1;
    do {
        msetup_WinMesSet(0x1A0D);
        if (msetup_WinMesWait() == 0) {
            msetup_WinMesSet(0x1A0E);
            msetup_WinMesWait();
            HuAudFXPlay(0x2A6);
            msetup_winMode = 0;
            for (i = 0; i < msetup_playerNum; i++) {
                msetup_playerWorkTbl[i].state = 16;
            }
            HuAudSeqFadeOut(390);
            msetup_exitRumbleF = 1;
            HuAudFXPlay(0x2DF);
            msetup_CameraKeyframeExec(msetup_cameraStartKeyTbl, 22.0f, NULL);
            _ClearFlag(0);
            _ClearFlag(0x28);
            _SetFlag(0x1B);
            if (msetup_playerConfig.unk17 != 0) {
                _SetFlag(0x20);
            } else {
                _ClearFlag(0x20);
            }
            GwSystem.playMode = 5;
            msetup_exitMode = 4;
            msetup_exitOvlNo = 71;
            msetup_exitEvtNo = 0;
            omOvlHisChg(0, 0x7D, 0, 0x4090);
            omovlhisidx++;
            i = 0;
        } else {
            msetup_WinMesSet(0x1501);
            if (msetup_WinMesWait() == 0) {
                i = 0;
                msetup_winMode = 0;
                msetup_exitCnt = 75;
                HuAudFXPlay(0x2EC);
                msetup_CameraKeyframeExec(msetup_cameraCancelKeyTbl, 25.0f, NULL);
            }
        }
    } while (i != 0);
    msetup_exitCnt = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void msetup_StoryDuelSetupProc(void) {
    s16 state[2];
    Process *process;
    s32 i;

    msetup_playerNum = 2;
    msetup_StoryPlayerInit();
    msetup_playerConfig.boardIndex = GwSystem.current_board_index;
    msetup_playerConfig.totalTurns = GwSystem.total_turns;
    msetup_playerConfig.unk17 = _CheckFlag(0x29);
    for (i = 0; i < msetup_playerNum; i++) {
        msetup_playerConfig.characters[i] = GwPlayer[i].chr;
        msetup_playerConfig.stars[i] = GwPlayer[i].star;
        msetup_playerConfig.controllerPorts[i] = GwPlayer[i].pad;
        if (GwPlayer[i].stat & 1) {
            msetup_playerConfig.cpuDifficulty[i] = GwPlayer[i].cpu_difficulty;
        } else {
            msetup_playerConfig.cpuDifficulty[i] = 0xFF;
        }
    }
    msetup_playerConfig.humanCount = 1;
    msetup_playerConfig.cpuCount = 1;
    Hu3DModelPosSet(Hu3DModelRead(msetup_stageMdlFileTbl[1], 0x2B9), 0.0f, -37.5f, 100.0f);
    msetup_BackObjCreate();
    process = omAddPrcObj(msetup_MenuProc, 0xBB8, 0x1000, 0);
    memset(&msetup_menu, 0, sizeof(msetup_menu));
    msetup_menu.result = -1;
    process->user_data = &msetup_menu;
    process = omAddPrcObj(msetup_TumbleProc, 0x3E8, 0x600, 0);
    memset(state, 0, sizeof(state));
    process->user_data = state;
    msetup_CameraPresetSet(&msetup_cameraPreset);
    msetup_PlayerProcCreate(msetup_playerNum);
    HuPrcVSleep();
    WipeCreateIn(msetup_wipeType, 16);
    HuAudFXPlay(0x2D8);
    msetup_CameraKeyframeExec(msetup_cameraIntroKeyTbl, 22.0f, msetup_IntroCameraHook);
    msetup_backNarrowF = 1;
    state[0] = 1;
    HuAudFXPlay(0x2DB);
    msetup_playerWorkTbl[0].state = 1;
    while (state[0] == 1) {
        HuPrcVSleep();
    }
    msetup_winMode = 1;
    msetup_WinAttrWait(0x4000, 0x4000);
    msetup_WinInsertMesSet(msetup_playerConfig.characters[0] + 0x1C00, 0);
    msetup_WinMesSet(0x2900);
    msetup_WinMesWait();
    msetup_WinMesSet(msetup_storyDuelBoardMesTbl[msetup_playerConfig.boardIndex]);
    msetup_WinMesWait();
    msetup_WinMesSet(0x2907);
    msetup_WinMesWait();
    msetup_menu.state = 12;
    do {
        HuPrcVSleep();
    } while (msetup_menu.state != 0);
    msetup_WinMesSet(0x2908);
    msetup_WinMesWait();
    HuAudFXPlay(0x2DB);
    for (i = 1; i < msetup_playerNum; i++) {
        msetup_playerWorkTbl[i].state = 1;
    }
    for (i = 7; i != 0; i--) {
        HuPrcVSleep();
    }
    msetup_playerWorkTbl[0].state = 17;
    while (msetup_playerWorkTbl[msetup_playerNum - 1].state != 0) {
        HuPrcVSleep();
    }
    if (msetup_playerConfig.characters[1] != 1) {
        msetup_WinMesSet(msetup_storyDuelRivalMesTbl[msetup_playerConfig.characters[1]]);
    } else {
        msetup_WinMesSet(msetup_storyDuelLuigiMesTbl[msetup_playerConfig.boardIndex]);
    }
    msetup_WinMesWait();
    msetup_WinMesSet(0x2914);
    msetup_WinMesWait();
    msetup_WinMesSet(0x2915);
    msetup_WinMesWait();
    msetup_WinMesSet(0x2916);
    msetup_WinMesWait();
    if (msetup_playerConfig.unk17 != 0) {
        msetup_WinMesSet(0x291A);
    } else {
        msetup_WinMesSet(0x2919);
    }
    msetup_WinMesWait();
    i = 1;
    do {
        msetup_WinMesSet(0x2917);
        if (msetup_WinMesWait() == 0) {
            msetup_WinMesSet(0x2918);
            msetup_WinMesWait();
            HuAudFXPlay(0x2A6);
            msetup_winMode = 0;
            for (i = 0; i < msetup_playerNum; i++) {
                msetup_playerWorkTbl[i].state = 16;
            }
            HuAudSeqFadeOut(390);
            msetup_exitRumbleF = 1;
            HuAudFXPlay(0x2DF);
            msetup_CameraKeyframeExec(msetup_cameraStartKeyTbl, 22.0f, NULL);
            _ClearFlag(0);
            _ClearFlag(0x28);
            if (msetup_playerConfig.unk17 != 0) {
                _SetFlag(0x20);
            } else {
                _ClearFlag(0x20);
            }
            GwSystem.playMode = 6;
            msetup_exitMode = 3;
            msetup_exitOvlNo = 90;
            msetup_exitEvtNo = 0;
            omOvlHisChg(0, 0x7D, 0, 0x4090);
            omovlhisidx++;
            i = 0;
        } else {
            msetup_WinMesSet(0x1501);
            if (msetup_WinMesWait() == 0) {
                i = 0;
                msetup_winMode = 0;
                msetup_exitCnt = 75;
                HuAudFXPlay(0x2EC);
                msetup_CameraKeyframeExec(msetup_cameraCancelKeyTbl, 25.0f, NULL);
            }
        }
    } while (i != 0);
    msetup_exitCnt = 1;
    while (1) {
        HuPrcVSleep();
    }
}

s16 msetup_MgModeIntroStep(s16 stateIndex) {
    s16 nextState;

    if (msetup_menu.result >= 0) {
        msetup_WinMesSet(0x4900);
        msetup_WinMesWait();
        msetup_WinMesSet(0x4902);
        msetup_WinMesWait();
        nextState = stateIndex + 1;
    } else {
        nextState = stateIndex - 1;
    }
    return nextState;
}

s16 msetup_MgMode1PIntroStep(s16 stateIndex) {
    s16 nextState;

    if (msetup_menu.result >= 0) {
        msetup_WinInsertMesSet(msetup_playerConfig.characters[0] + 0x1C00, 0);
        msetup_WinMesSet(0x4A00);
        msetup_WinMesWait();
        msetup_WinMesSet(0x4A02);
        msetup_WinMesWait();
        nextState = stateIndex + 1;
    } else {
        nextState = stateIndex - 1;
    }
    return nextState;
}

s16 msetup_MgMode1PChrStep(s16 step) {
    s32 i;

    msetup_menu.state = 2;
    do {
        HuPrcVSleep();
    } while (msetup_menu.state != 0);

    if (msetup_menu.result != -1) {
        msetup_winMode = 0;
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
        msetup_PlayerProcCreateEx(1, msetup_playerNum);
        for (i = 4; i != 0; i--) {
            HuPrcVSleep();
        }
        HuAudFXPlay(0x2DB);
        for (i = 1; i < msetup_playerNum; i++) {
            msetup_playerWorkTbl[i].state = 1;
        }
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
        msetup_playerWorkTbl[0].state = 17;
        while (msetup_playerWorkTbl[msetup_playerNum - 1].state != 0) {
            HuPrcVSleep();
        }
    }
    if (msetup_menu.result < 0) {
        step--;
    } else {
        step++;
    }
    return step;
}

s16 msetup_MgMode1PComLevelStep(s16 step) {
    s32 i;

    if (msetup_playerConfig.cpuCount != 0) {
        for (i = 0; i < msetup_playerNum; i++) {
            msetup_playerWorkTbl[i].state = 7;
        }
        msetup_menu.state = 3;
        do {
            HuPrcVSleep();
        } while (msetup_menu.state != 0);
    } else {
        msetup_winMode = 1;
    }
    if (msetup_menu.result == -1) {
        HuAudFXPlay(0x2E4);
        msetup_PlayerProcKillEx(1, msetup_playerNum);
    }
    if (msetup_menu.result < 0) {
        step--;
    } else {
        step++;
    }
    return step;
}

s16 msetup_MgModeConfirmStep(s16 step) {
    msetup_menu.result = 0;
    msetup_WinMesSet(0x4919);
    if (msetup_WinMesWait() == 0) {
        msetup_WinMesSet(0x491B);
        step = -2;
        msetup_WinMesWait();
        HuAudFXPlay(0x2A6);
    } else {
        msetup_WinMesSet(0x491A);
        if (msetup_WinMesWait() == 0) {
            HuAudFXPlay(0x2E4);
            step = 1;
            msetup_PlayerProcKill(msetup_playerNum);
        } else {
            msetup_menu.result = -1;
            step--;
        }
    }
    return step;
}

s16 msetup_MgMode1PConfirmStep(s16 step) {
    msetup_menu.result = 0;
    msetup_WinMesSet(0x4919);
    if (msetup_WinMesWait() == 0) {
        msetup_WinMesSet(0x491B);
        step = -2;
        msetup_WinMesWait();
        HuAudFXPlay(0x2A6);
    } else {
        msetup_WinMesSet(0x491A);
        if (msetup_WinMesWait() == 0) {
            HuAudFXPlay(0x2E4);
            msetup_PlayerProcKillEx(1, msetup_playerNum);
            step = 1;
        } else {
            msetup_menu.result = -1;
            step--;
        }
    }
    return step;
}

void msetup_MgModeSetupExec(s16 (**steps)(s16)) {
    s16 state[2];
    Process *process;
    s16 step;
    s32 i;

    msetup_playerNum = 4;
    Hu3DModelPosSet(Hu3DModelRead(msetup_stageMdlFileTbl[0], 0x2B9), 0.0f, -37.5f, 100.0f);
    msetup_BackObjCreate();
    process = omAddPrcObj(msetup_MenuProc, 0xBB8, 0x1000, 0);
    memset(&msetup_menu, 0, sizeof(msetup_menu));
    msetup_menu.result = -1;
    process->user_data = &msetup_menu;
    process = omAddPrcObj(msetup_TumbleProc, 0x3E8, 0x600, 0);
    memset(state, 0, sizeof(state));
    process->user_data = state;
    if (msetup_setupMode == 6) {
        msetup_PlayerProcCreateEx(0, 1);
    }
    msetup_CameraPresetSet(&msetup_cameraPreset);
    HuPrcVSleep();
    WipeCreateIn(msetup_wipeType, 16);
    msetup_menu.result = 0;
    HuAudFXPlay(0x2D8);
    msetup_CameraKeyframeExec(msetup_cameraIntroKeyTbl, 22.0f, msetup_IntroCameraHook);
    msetup_backNarrowF = 1;
    if (msetup_setupMode == 6) {
        HuAudFXPlay(0x2DB);
        msetup_playerWorkTbl[0].state = 1;
    }
    state[0] = 1;
    do {
        HuPrcVSleep();
    } while (state[0] == 1);
    msetup_winMode = 1;
    msetup_WinAttrWait(0x4000, 0x4000);
    step = 0;
    do {
        step = steps[step](step);
    } while (step >= 0);
    msetup_winMode = 0;
    if (step < -1) {
        for (i = 0; i < msetup_playerNum; i++) {
            msetup_playerWorkTbl[i].state = 12;
        }
        HuPrcVSleep();
        for (i = 0; i < msetup_playerNum; i++) {
            msetup_playerWorkTbl[i].state = 16;
        }
        HuAudSeqFadeOut(390);
        msetup_exitRumbleF = 1;
        HuAudFXPlay(0x2DF);
        msetup_CameraKeyframeExec(msetup_cameraStartKeyTbl, 22.0f, NULL);
        for (i = 0; i < msetup_playerNum; i++) {
            GwPlayer[i].chr = msetup_playerConfig.characters[i];
            GwPlayer[i].star = msetup_playerConfig.stars[i];
            GwPlayer[i].coin = 0;
            GwPlayer[i].pad = msetup_playerConfig.controllerPorts[i];
            if (msetup_playerConfig.cpuDifficulty[i] < 4) {
                GwPlayer[i].cpu_difficulty = msetup_playerConfig.cpuDifficulty[i];
                GwPlayer[i].stat = 1;
            } else {
                GwPlayer[i].cpu_difficulty = 1;
                GwPlayer[i].stat = 0;
            }
        }
        msetup_exitMode = 1;
        msetup_exitOvlNo = 105;
        msetup_exitEvtNo = 0;
    } else {
        msetup_exitCnt = 75;
        HuAudFXPlay(0x2EC);
        msetup_CameraKeyframeExec(msetup_cameraCancelKeyTbl, 25.0f, NULL);
    }
    msetup_exitCnt = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void msetup_MgModeSetupProc(void) {
    msetup_MgModeSetupExec(msetup_mgModeStepTbl);
}

void msetup_MgMode1PSetupProc(void) {
    msetup_playerConfig.humanCount = 1;
    msetup_playerConfig.cpuCount = 3;
    msetup_playerConfig.characters[0] = GwStory.unk1;
    msetup_playerConfig.cpuDifficulty[0] = 0xFF;
    msetup_MgModeSetupExec(msetup_mgMode1PStepTbl);
}

void msetup_TutorialSetupExec(s16 mode) {
    s16 state[2];
    Process *process;
    s32 *messages;
    s32 i;
    u8 *controllerPort;
    s32 stars;

    switch (mode) {
        default:
        case 0:
            msetup_playerNum = 4;
            msetup_playerConfig.humanCount = 1;
            msetup_playerConfig.cpuCount = 3;
            msetup_playerConfig.characters[0] = 3;
            msetup_playerConfig.characters[1] = 2;
            msetup_playerConfig.characters[2] = 0;
            msetup_playerConfig.characters[3] = 4;
            messages = msetup_tutorialPartyMesTbl;
            i = 2;
            break;
        case 1:
            msetup_playerNum = 2;
            msetup_playerConfig.humanCount = 1;
            msetup_playerConfig.cpuCount = 1;
            msetup_playerConfig.characters[0] = 0;
            msetup_playerConfig.characters[1] = 1;
            messages = msetup_tutorialDuelMesTbl;
            i = 1;
            break;
    }
    Hu3DModelPosSet(Hu3DModelRead(msetup_stageMdlFileTbl[i], 0x2B9), 0.0f, -37.5f, 100.0f);
    msetup_BackObjCreate();
    msetup_EffObjCreate();
    process = omAddPrcObj(msetup_TumbleProc, 0x3E8, 0x600, 0);
    memset(state, 0, sizeof(state));
    process->user_data = state;
    msetup_CameraPresetSet(&msetup_cameraPreset);
    msetup_PlayerProcCreate(msetup_playerNum);
    i = 0;
    HuPrcVSleep();
    WipeCreateIn(msetup_wipeType, 16);
    HuAudFXPlay(0x2D8);
    msetup_CameraKeyframeExec(msetup_cameraIntroKeyTbl, 22.0f, msetup_IntroCameraHook);
    msetup_backNarrowF = 1;
    state[0] = 1;
    HuAudFXPlay(0x2DB);
    for (; i < msetup_playerNum; i++) {
        msetup_playerWorkTbl[i].state = 1;
    }
    while (state[0] == 1) {
        HuPrcVSleep();
    }
    msetup_winMode = 1;
    msetup_WinAttrWait(0x4000, 0x4000);
    msetup_WinHomeClear();
    for (i = 0; i < 4; i++) {
        msetup_WinMesSet(messages[i]);
        msetup_WinMesWait();
        if (msetup_WinInputGet() & B_BUTTON) {
            msetup_WinMesSet(messages[4]);
            if (msetup_WinMesWait() == 0) {
                break;
            }
        }
    }
    if (i < 4) {
        msetup_winMode = 0;
        msetup_exitCnt = 75;
        HuAudFXPlay(0x2EC);
        msetup_CameraKeyframeExec(msetup_cameraCancelKeyTbl, 25.0f, NULL);
    } else {
        HuAudFXPlay(0x2A6);
        msetup_winMode = 0;
        for (i = 0; i < msetup_playerNum; i++) {
            msetup_playerWorkTbl[i].state = 16;
        }
        HuAudSeqFadeOut(390);
        msetup_exitRumbleF = 1;
        HuAudFXPlay(0x2DF);
        msetup_CameraKeyframeExec(msetup_cameraStartKeyTbl, 22.0f, NULL);
        _ClearFlag(0);
        GwSystem.current_board_index = 6;
        GwSystem.total_turns = 20;
        GwSystem.current_game_length = 0;
        switch (mode) {
            default:
            case 0:
                msetup_exitMode = 4;
                msetup_exitOvlNo = 71;
                msetup_exitEvtNo = 0;
                stars = 0;
                break;
            case 1:
                msetup_exitMode = 3;
                msetup_exitOvlNo = 90;
                msetup_exitEvtNo = 0;
                stars = 5;
                break;
        }
        for (i = 0; i < msetup_playerNum; i++) {
            controllerPort = &msetup_padNoLo;
            GwPlayer[i].chr = msetup_playerConfig.characters[i];
            GwPlayer[i].star = stars;
            GwPlayer[i].pad = *controllerPort;
            GwPlayer[i].cpu_difficulty = 1;
            GwPlayer[i].stat = 1;
            GwPlayer[i].coin = 0;
        }
    }
    msetup_exitCnt = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void msetup_TutorialPartySetupProc(void) {
    msetup_TutorialSetupExec(0);
}

void msetup_TutorialDuelSetupProc(void) {
    msetup_TutorialSetupExec(1);
}

void msetup_SysClose(void) {
}
