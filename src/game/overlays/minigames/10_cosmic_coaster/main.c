#include "common.h"
#include "game/mallocblock.h"
#include "game/overlays/minigame.h"
#include "math.h"
#include "humath.h"
#include "cosmic_coaster.h"

extern omObjData *D_8010C050_cosmic_coaster;
// Object data of the HUD/track object (D_8010C3C0), one half per coaster car.
typedef struct CosmicCoasterHudData { // 0x28 bytes
    s16 frame[2];                     // 0x00
    s16 label[2];                     // 0x04
    s16 meter[2];                     // 0x08
    s16 portrait[4];                  // 0x0C
    s16 banner;                       // 0x14
    s16 trackFrame[2];                // 0x16
    f32 trackOffset[2];               // 0x1C
    u16 trackCount[2];                // 0x24
} CosmicCoasterHudData;

// Object data of the sprite effect object created by func_801090C0.
typedef struct CosmicCoasterEffectData { // 0x28 bytes
    s16 sprite[6];                       // 0x00
    s16 sprite2[6];                      // 0x0C
    u16 timer[2];                        // 0x18
    u16 inUse[6];                        // 0x1C
} CosmicCoasterEffectData;

// A shooting star sprite pair spawned by func_80109290.
typedef struct CosmicCoasterStarData { // 0x1C bytes
    u16 side;                          // 0x00
    u16 *inUse;                        // 0x04
    u16 sprite;                        // 0x08
    u16 sprite2;                       // 0x0A
    f32 x;                             // 0x0C
    f32 y;                             // 0x10
    f32 vx;                            // 0x14
    f32 vy;                            // 0x18
} CosmicCoasterStarData;

// Camera keyframe for the intro camera sweep.
typedef struct CosmicCoasterCamKey { // 0x20 bytes
    u16 frames;
    f32 zoom;
    Vec rot;
    Vec center;
} CosmicCoasterCamKey;

MinigameFlow D_8010BB30_cosmic_coaster = {
    MG_STATE_OPENING, MINIGAME_1V3, MG_TIMER_COUNT_DOWN, MG_TIME_DISP_RECORD, FALSE, MG_GAUGE_TOP_2 | 5, MG_RESULT_WIN_2, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    -1, -1, 30000, -1, 135
};
s16 D_8010BB58_cosmic_coaster[2] = { 32, 96 }; // sound panning per car
u16 D_8010BB5C_cosmic_coaster = 0;
u16 D_8010BB5E_cosmic_coaster = 0;
s32 D_8010BB60_cosmic_coaster = 0; /* Unreferenced. */
s32 D_8010BB64_cosmic_coaster[8] = {
    0x00210008, 0x00210009, 0x0021000A, 0x0021000B,
    0x0021000C, 0x0021000D, 0x0021000E, 0x0021000F
};
f32 D_8010BB84_cosmic_coaster[2] = { -100.0f, 100.0f };
s32 D_8010BB8C_cosmic_coaster = 20;
CosmicCoasterCamKey D_8010BB90_cosmic_coaster[2] = {
    { 30, -700.0f, { 0.0f, 90.0f, 0.0f }, { 0.0f, 200.0f, -150.0f } },
    { 30, 970.0f, { -11.0f, 0.0f, 0.0f }, { 0.0f, 200.0f, -500.0f } },
};

extern s32 D_8010C054_cosmic_coaster;
extern s16 D_8010C058_cosmic_coaster;
extern omObjData *D_8010C3C0_cosmic_coaster;
extern f32 D_8010C02C_cosmic_coaster; // zoom at the start of the current key
// Per-frame camera steps toward the current key.
extern f32 D_8010C030_cosmic_coaster; // rotation x
extern f32 D_8010C034_cosmic_coaster; // rotation y
extern f32 D_8010C038_cosmic_coaster; // rotation z
extern f32 D_8010C03C_cosmic_coaster; // center x
extern f32 D_8010C040_cosmic_coaster; // center y
extern f32 D_8010C044_cosmic_coaster; // center z
extern s32 D_8010C048_cosmic_coaster; // frames left in the current key
extern s32 D_8010C04C_cosmic_coaster; // current key
extern omObjData *D_8010C3B8_cosmic_coaster;
extern f32 D_8010C010_cosmic_coaster[2];     // victory jump x velocity per rider
extern f32 D_8010C018_cosmic_coaster[2];     // victory jump y velocity per rider
extern s32 D_8010C020_cosmic_coaster;        // victory sequence countdown
extern omObjData *D_8010C024_cosmic_coaster; // victory camera helper object
extern omObjData *D_8010C028_cosmic_coaster; // losing car object
extern s32 D_800A178C_main[][6];
extern u16 D_8010C05A_cosmic_coaster;

void func_80105D80_cosmic_coaster(omObjData *arg0);
void func_80105DAC_cosmic_coaster(omObjData *arg0);
void func_80105FEC_cosmic_coaster(omObjData *arg0);
void func_801063CC_cosmic_coaster(omObjData *arg0);
void func_80106530_cosmic_coaster(s16 car);
void func_80106720_cosmic_coaster(omObjData *arg0);
void func_8010869C_cosmic_coaster(omObjData *arg0);
void func_8010673C_cosmic_coaster(omObjData *arg0);
void func_80106758_cosmic_coaster(omObjData *object, s16 group);
void func_80106D10_cosmic_coaster(omObjData *object);
void func_80107888_cosmic_coaster(omObjData *object);
void func_8010803C_cosmic_coaster(omObjData *object);
void func_80108124_cosmic_coaster(omObjData *object);
void func_8010812C_cosmic_coaster(omObjData *object);
void func_801083D0_cosmic_coaster(omObjData *object, s16 slot, s8 *stickX);
void func_80108C9C_cosmic_coaster(omObjData *object);
void func_801080C8_cosmic_coaster(omObjData *arg0);
void func_801090C0_cosmic_coaster(omObjData *arg0);
void func_80109290_cosmic_coaster(omObjData *object);
s16 func_8010923C_cosmic_coaster(CosmicCoasterEffectData *data);
void func_801096A8_cosmic_coaster(omObjData *object);

void func_801059A0_cosmic_coaster(void) {
    omObjData *object;
    s32 i;

    omInitObjMan(120, 0);
    omGameSysInit();
    HuAudCharVoiceInit();
    Hu3DFogSet(940, 1000, 0, 12, 55);
    D_8010C058_cosmic_coaster = EffectGroupStarCreate(0x2A9, 4);
    CamSetupInitMulti(2);
    CamSetupMapCullAddMulti(2);
    for (i = 0; i < 2; i++) {
        CZoomM[i] = 1400.0f;
        CRotM[i].x = -8.0f;
        CRotM[i].y = 180.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 200.0f;
        CenterM[i].z = 0.0f;
        Hu3DCameraPerspectiveSet(i, 60.0f, 80.0f, 20000.0f);
    }
    ScissorSet(0, 0.0f, 0.0f, 144.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
    ScissorSet(1, 176.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
    object = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    object->work[0] = 2;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(1, 0x40, 0x40, 0x60);
    Hu3DGLightDirSet(1, 3.0f, 89.0f, 80.0f);
    Hu3DGLightStatSet(1, 1, 1);
    Hu3DGLightColorSet(3, 0, 0, 0);
    Hu3DGLightDirSet(3, -115.0f, 6.0f, -33.0f);
    Hu3DGLightStatSet(2, 1, 1);
    omAddObj(0, 0, 0, -1, func_80105D80_cosmic_coaster);
    D_8010C3C0_cosmic_coaster = omAddObj(20, 8, 0, -1, func_80105FEC_cosmic_coaster);
    D_8010C3C4_cosmic_coaster = omAddObj(20, 55, 0, -1, func_8010991C_cosmic_coaster);
    D_8010C3B0_cosmic_coaster[0] = omAddObj(10, 9, 14, -1, func_80106720_cosmic_coaster);
    D_8010C3B0_cosmic_coaster[1] = omAddObj(10, 9, 14, -1, func_8010673C_cosmic_coaster);
    omSetStat(D_8010C3C4_cosmic_coaster, 0x100);
    omAddObj(40, 0, 0, -1, func_801090C0_cosmic_coaster);
    func_800E5EA0_minigame(&D_8010BB30_cosmic_coaster);
    func_800EA0FC_minigame(0, 0.0f, 130.0f);
    func_800EA0FC_minigame(1, 0.0f, 130.0f);
    CharAnimInit();
}

void func_80105D80_cosmic_coaster(omObjData *arg0) {
    D_8010C054_cosmic_coaster = 0;
    D_8010C050_cosmic_coaster = NULL;
    D_8010C3BC_cosmic_coaster = -1;
    arg0->func = func_80105DAC_cosmic_coaster;
}

void func_80105DAC_cosmic_coaster(omObjData *arg0) {
    CosmicCoasterCarData *car;
    CosmicCoasterCarData *car1;
    s32 finished;
    s32 i;

    if (D_8010BB5C_cosmic_coaster == 0) {
        switch (MgFlowMain()) {
            case 0:
                if (D_8010C050_cosmic_coaster == NULL) {
                    D_8010C05A_cosmic_coaster = 0;
                    D_8010C050_cosmic_coaster = omAddObj(4, 0, 0, -1, func_8010869C_cosmic_coaster);
                }
                break;
            case 1:
                break;
            case 2:
                finished = 0;
                for (i = 0; i < 2; i++) {
                    car = D_8010C3B0_cosmic_coaster[i]->data;
                    if (car->finished == 1) {
                        finished |= 1 << i;
                    }
                }
                if (finished == 1 || finished == 2) {
                    D_8010C3BC_cosmic_coaster = finished - 1;
                } else if (finished == 3) {
                    f32 progress0;
                    f32 progress1;

                    car = D_8010C3B0_cosmic_coaster[0]->data;
                    car1 = D_8010C3B0_cosmic_coaster[1]->data;
                    progress0 = car->progress;
                    progress1 = car1->progress;
                    if (progress0 > progress1) {
                        D_8010C3BC_cosmic_coaster = 0;
                    } else if (progress0 < progress1) {
                        D_8010C3BC_cosmic_coaster = 1;
                    } else {
                        D_8010C3BC_cosmic_coaster = rand8() & 1;
                    }
                } else {
                    break;
                }
                MgFlowStatSet(MG_STATE_FINISH);
                break;
            case 3:
                car = D_8010C3B0_cosmic_coaster[D_8010C3BC_cosmic_coaster]->data;
                D_8010BB30_cosmic_coaster.winners[0] = car->player[0];
                D_8010BB30_cosmic_coaster.winners[1] = car->player[1];
                if (D_8010BB5E_cosmic_coaster == 0) {
                    GwPlayer[car->player[0]].bonusCoin = 10;
                    GwPlayer[car->player[1]].bonusCoin = 10;
                    D_8010BB5E_cosmic_coaster = 1;
                }
                break;
            case 4:
                break;
            case 5:
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                D_8010BB5C_cosmic_coaster = 1;
                break;
        }
    } else if (WipeStatGet() == 0) {
        func_80109900_cosmic_coaster();
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
    }
}

void func_80105FEC_cosmic_coaster(omObjData *object) {
    CosmicCoasterHudData *hud;
    s16 portraits[4];
    s16 frameSprite;
    s16 labelSprite;
    s16 meterSprite;
    s16 bannerSprite;
    s16 cam;
    s16 x;
    s32 i;
    s32 j;

    omSetStat(object, 0x100);
    hud = object->data = HuMemAllocTag(sizeof(CosmicCoasterHudData), TAG_OVERLAY);
    frameSprite = HuSprAnimDataRead(0x31000E);
    labelSprite = HuSprAnimDataRead(0x31000F);
    meterSprite = HuSprAnimDataRead(0x310011);
    bannerSprite = HuSprAnimDataRead(0x310010);
    for (i = 0; i < 4; i++) {
        portraits[i] = HuSprAnimDataRead(D_8010BB64_cosmic_coaster[GwPlayer[((CosmicCoasterCarData *)D_8010C3B0_cosmic_coaster[i / 2]->data)->player[i % 2]].chr]);
    }
    hud->banner = espEntry(bannerSprite, 0, 0);
    espPosSet(hud->banner, 160, 40);
    espPriSet(hud->banner, 0x80C8);
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            cam = 1;
        } else {
            cam = 2;
        }
        hud->frame[i] = espEntry(frameSprite, 0, 0);
        espPosSet(hud->frame[i], i * 160 + 80, 120);
        espAttrSet(hud->frame[i], 0x4000);
        espPriSet(hud->frame[i], 0x8190);
        hud->label[i] = espEntry(labelSprite, 0, 0);
        espPosSet(hud->label[i], i * 15 + 153, 120);
        espPriSet(hud->label[i], 0x812C);
        hud->meter[i] = espEntry(meterSprite, 0, 0);
        espPosSet(hud->meter[i], i * 18 + 151, 204);
        espPriSet(hud->meter[i], 0x8064);
        for (j = 0; j < 2; j++) {
            hud->portrait[i * 2 + j] = espEntry(portraits[i * 2 + j], 0, 0);
            espPriSet(hud->portrait[i * 2 + j], 0x8032);
        }
        x = i * 18 + 151;
        espPosSet(hud->portrait[0], x, 196);
        espPosSet(hud->portrait[1], x, 196);
        for (j = 0; j < 4; j++) {
            if (i == 0 && j == 0) {
                object->model[0] = Hu3DModelRead(0x310000, 0x20699);
            } else {
                object->model[i * 4 + j] = Hu3DModelLink(object->model[0]);
            }
            Hu3DModelCameraSet(object->model[i * 4 + j], cam);
        }
        hud->trackOffset[i] = 3300.0f;
        hud->trackFrame[i] = 0;
        hud->trackCount[i] = 0;
    }
    func_80106530_cosmic_coaster(0);
    func_80106530_cosmic_coaster(1);
    object->func = func_801063CC_cosmic_coaster;
}

void func_801063CC_cosmic_coaster(omObjData *object) {
    CosmicCoasterHudData *hud = D_8010C3C0_cosmic_coaster->data;
    CosmicCoasterCarData *car;
    s16 x;
    s32 y;
    s32 i;

    for (i = 0; i < 2; i++) {
        car = D_8010C3B0_cosmic_coaster[i]->data;
        hud->trackOffset[i] += D_8010BB30_cosmic_coaster.gaugeValue[i] / 1.08f;
        func_80106530_cosmic_coaster(i);
        x = i * 18 + 151;
        y = 204.0f - car->progress / 63000.0f * 164.0f;
        espPosSet(hud->meter[i], x, y);
        espPosSet(hud->portrait[i * 2], x, y - 8);
        espPosSet(hud->portrait[i * 2 + 1], x, y + 8);
    }
}

// Positions the four repeating track segment models of one car's view and
// switches their texture animation once enough segments have scrolled past.
void func_80106530_cosmic_coaster(s16 car) {
    CosmicCoasterHudData *hud;
    s32 frame;
    s32 count;
    s32 i;
    s32 carIndex = car;

    hud = D_8010C3C0_cosmic_coaster->data;
    frame = hud->trackFrame[carIndex];
    count = hud->trackCount[carIndex];
    for (i = 0; i < 4; i++) {
        Hu3DModelPosSet(D_8010C3C0_cosmic_coaster->model[car * 4 + frame], 0.0f, 0.0f,
                        hud->trackOffset[car] - i * 3000.0f);
        if (++count >= 23) {
            Hu3DModelAttrSet(D_8010C3C0_cosmic_coaster->model[car * 4 + frame], 4, 4);
        } else {
            Hu3DModelAttrSet(D_8010C3C0_cosmic_coaster->model[car * 4 + frame], 4, 0);
        }
        if (++frame >= 4) {
            frame -= 4;
        }
    }
    if (hud->trackOffset[car] >= 6300.0f) {
        hud->trackOffset[car] -= 3000.0f;
        if (++hud->trackFrame[car] >= 4) {
            hud->trackFrame[car] -= 4;
        }
        hud->trackCount[car]++;
    }
}

void func_80106720_cosmic_coaster(omObjData *object) {
    func_80106758_cosmic_coaster(object, 0);
}

void func_8010673C_cosmic_coaster(omObjData *object) {
    func_80106758_cosmic_coaster(object, 1);
}

void func_80106758_cosmic_coaster(omObjData *object, s16 group) {
    CosmicCoasterCarData *car;
    s16 cam;
    s32 chr;
    s32 dir;
    s32 n;
    s32 i;

    if (group == 0) {
        cam = 1;
    } else {
        cam = 2;
    }
    car = object->data = HuMemAllocTag(sizeof(CosmicCoasterCarData), TAG_OVERLAY);
    car->group = group;
    car->progress = car->prevProgress = 0.0f;
    car->finished = 0;
    car->rollSfx = -1;
    n = 0;
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == group) {
            car->player[n] = i;
            n++;
        }
    }
    object->model[0] = Hu3DModelRead(0x310001, 0x206D9);
    Hu3DModelCameraSet(object->model[0], cam);
    object->model[1] = Hu3DModelRead(0x310002, 0x206D9);
    object->model[2] = Hu3DModelRead(0x310003, 0x206D9);
    Hu3DModelCameraSet(object->model[1], cam);
    Hu3DModelCameraSet(object->model[2], cam);
    Hu3DLLightCreate(object->model[0], 1);
    Hu3DLLightColorSet(object->model[0], 0, 0, 0);
    Hu3DLLightDirSet(object->model[0], 0.0f, -127.0f, 0.0f);
    car->hasHuman = 0;
    for (i = 0; i < 2; i++) {
        if (!(GwPlayer[i].stat & 1)) {
            car->hasHuman = 1;
        }
        chr = (s8)GwPlayer[car->player[i]].chr;
        dir = D_800A178C_main[chr][0];
        object->model[3 + i] = Hu3DModelRead(dir | D_800A178C_main[chr][1], 0x206D9);
        object->model[7 + i] = Hu3DModelRead(dir | D_800A178C_main[chr][2], 0x206CD);
        CharAnimCreate(object->model[7 + i], 2, chr, CharMotionDataNumGetTbl(chr, 2, 1));
        Hu3DModelDynamicFree(object->model[7 + i]);
        Hu3DModelCameraSet(object->model[3 + i], cam);
        Hu3DModelCameraSet(object->model[7 + i], cam);
        car->rotY[i] = 180.0f;
        Hu3DModelRotSet(object->model[3 + i], 0.0f, 180.0f, 0.0f);
        car->y[i] = 125.0f;
        object->model[5 + i] = Hu3DModelRead3(9, 0x68D);
        Hu3DModelCameraSet(object->model[5 + i], cam);
        omObjMotionRead(object, i, CharMotionDataNumGet(chr, 0));
        omObjMotionRead(object, i + 2, CharMotionDataNumGet(chr, 0x53));
        omObjMotionRead(object, i + 4, CharMotionDataNumGet(chr, 0x54));
        omObjMotionRead(object, i + 6, CharMotionDataNumGet(chr, 4));
        omObjMotionRead(object, i + 8, CharMotionDataNumGet(chr, 1));
        omObjMotionRead(object, i + 10, CharMotionDataNumGet(chr, 0x2F));
        omObjMotionRead(object, i + 12, CharMotionDataNumGet(chr, 0x36));
        Hu3DMotionModelSet(object->model[3 + i], object->motion[2 + i]);
        Hu3DMotionAttrSet(object->model[3 + i], 2, 2);
        car->x[i] = 0.0f;
        car->tilt[i] = 0.0f;
        car->stunTimer[i] = 0;
        car->visible[i] = 1;
        car->targetX[i] = 100000.0f;
        car->carried[i] = NULL;
        car->state[i] = 0;
        Hu3DLLightCreate(object->model[1 + i], 1);
        Hu3DLLightColorSet(object->model[1 + i], 0, 0, 0);
        Hu3DLLightDirSet(object->model[1 + i], 0.0f, -127.0f, 0.0f);
        Hu3DLLightCreate(object->model[3 + i], 1);
        Hu3DLLightColorSet(object->model[3 + i], 0, 0, 0);
        Hu3DLLightDirSet(object->model[3 + i], 0.0f, -127.0f, 0.0f);
        object->work[0] = 0;
    }
    Hu3DModelPosSet(object->model[1], car->x[0], 125.0f, D_8010BB84_cosmic_coaster[0]);
    Hu3DModelPosSet(object->model[2], car->x[1], 125.0f, D_8010BB84_cosmic_coaster[1]);
    Hu3DModelPosSet(object->model[3], car->x[0], car->y[0], D_8010BB84_cosmic_coaster[0]);
    Hu3DModelPosSet(object->model[4], car->x[1], car->y[1], D_8010BB84_cosmic_coaster[1]);
    object->func = func_80106D10_cosmic_coaster;
}

// Main update of a coaster car: steers the riders, accelerates or brakes the
// car, and handles riders colliding with track objects.
void func_80106D10_cosmic_coaster(omObjData *object) {
    omObjData *found[2];
    s8 stickX;
    CosmicCoasterCarData *car = object->data;
    f32 maxSpeed;
    u32 hits;
    s16 pad;
    s16 effect;
    s16 cam;
    s32 i;

    if (car->group == 0) {
        cam = 1;
    } else {
        cam = 2;
    }
    maxSpeed = 130.0f;
    func_8010812C_cosmic_coaster(object);
    for (i = 0; i < 2; i++) {
        pad = GwPlayer[car->player[i]].pad;
        if (GwPlayer[car->player[i]].stat & 1) {
            func_801083D0_cosmic_coaster(object, i, &stickX);
        } else {
            stickX = HuPadStkX[pad];
        }
        if (MgFlowStatGet() != MG_STATE_PLAY) {
            stickX = 0;
        }
        car->x[i] += stickX * 0.4f;
        if (car->x[i] < -160.0f) {
            car->x[i] = -160.0f;
        }
        if (car->x[i] > 160.0f) {
            car->x[i] = 160.0f;
        }
        Hu3DModelPosSet(object->model[1 + i], car->x[i], 125.0f, D_8010BB84_cosmic_coaster[i]);
        Hu3DModelPosSet(object->model[3 + i], car->x[i], 125.0f, D_8010BB84_cosmic_coaster[i]);
    }
    if (D_8010C3BC_cosmic_coaster == -1) {
        if (MgFlowStatGet() == MG_STATE_PLAY) {
            D_8010BB30_cosmic_coaster.gaugeValue[car->group] += 4.0f;
            if (D_8010BB30_cosmic_coaster.gaugeValue[car->group] > maxSpeed) {
                D_8010BB30_cosmic_coaster.gaugeValue[car->group] = maxSpeed;
            }
        }
    } else if (car->group == D_8010C3BC_cosmic_coaster) {
        if (car->progress < 63200.0f) {
            D_8010BB30_cosmic_coaster.gaugeValue[car->group] += 4.0f;
            if (D_8010BB30_cosmic_coaster.gaugeValue[car->group] > maxSpeed) {
                D_8010BB30_cosmic_coaster.gaugeValue[car->group] = maxSpeed;
            }
        } else {
            D_8010BB30_cosmic_coaster.gaugeValue[car->group] -= 12.0f;
            if (D_8010BB30_cosmic_coaster.gaugeValue[car->group] < 0.0f) {
                D_8010BB30_cosmic_coaster.gaugeValue[car->group] = 0.0f;
            }
            if (D_8010BB30_cosmic_coaster.gaugeValue[car->group] == 0.0f && car->tilt[0] >= 0.0f &&
                car->tilt[1] >= 0.0f) {
                HuAudFXStop(car->rollSfx);
                D_8010C3B0_cosmic_coaster[D_8010C3BC_cosmic_coaster]->func = func_80107888_cosmic_coaster;
                car->endPhase = 0;
            }
        }
        Hu3DLLightColorSet(object->model[0], 255, 255, 255);
        Hu3DLLightDirSet(object->model[0], 69.0f, 69.0f, 69.0f);
        Hu3DLLightColorSet(object->model[1], 255, 255, 255);
        Hu3DLLightDirSet(object->model[1], 69.0f, 69.0f, 69.0f);
        Hu3DLLightColorSet(object->model[2], 255, 255, 255);
        Hu3DLLightDirSet(object->model[2], 69.0f, 69.0f, 69.0f);
        Hu3DLLightColorSet(object->model[3], 255, 255, 255);
        Hu3DLLightDirSet(object->model[3], 69.0f, 69.0f, 69.0f);
        Hu3DLLightColorSet(object->model[4], 255, 255, 255);
        Hu3DLLightDirSet(object->model[4], 69.0f, 69.0f, 69.0f);
    } else {
        D_8010BB30_cosmic_coaster.gaugeValue[car->group] -= 9.6f;
        if (D_8010BB30_cosmic_coaster.gaugeValue[car->group] < 0.0f) {
            D_8010BB30_cosmic_coaster.gaugeValue[car->group] = 0.0f;
        }
        if (D_8010BB30_cosmic_coaster.gaugeValue[car->group] == 0.0f && car->tilt[0] >= 0.0f &&
            car->tilt[1] >= 0.0f) {
            HuAudFXStop(car->rollSfx);
            D_8010C3B0_cosmic_coaster[(s16)(D_8010C3BC_cosmic_coaster ^ 1)]->func = func_80108124_cosmic_coaster;
        }
    }
    car->prevProgress = car->progress;
    car->progress += D_8010BB30_cosmic_coaster.gaugeValue[car->group] / 1.08f;
    if (car->progress >= 63000.0f) {
        car->finished = 1;
    }
    for (i = 0; i < 2; i++) {
        if (car->tilt[i] < 0.0f) {
            car->visible[i] ^= 1;
            if (car->stunTimer[i] == 0) {
                car->tilt[i] += 10.0f;
            } else {
                car->stunTimer[i]--;
            }
        } else {
            car->visible[i] = 1;
            Hu3DMotionShiftSet(object->model[3 + i], Hu3DData[object->motion[2 + i]].motId, 0, 6, 0);
        }
        if (car->visible[i] != 0) {
            Hu3DModelAttrSet(object->model[1 + i], 4, 0);
            Hu3DModelAttrSet(object->model[3 + i], 4, 0);
        } else {
            Hu3DModelAttrSet(object->model[1 + i], 4, 4);
            Hu3DModelAttrSet(object->model[3 + i], 4, 4);
        }
    }
    hits = func_8010B644_cosmic_coaster(found, car, car->progress, car->prevProgress, 1);
    if ((hits & 0xFFFF) != 0xFFFF) {
        if ((hits & 0xFFFF) == 4) {
            HuAudFXPanning(HuAudFXPlay(9), D_8010BB58_cosmic_coaster[car->group]);
            GwPlayer[car->player[0]].gameCoin += 1;
            GwPlayer[car->player[1]].gameCoin += 1;
            effect = EffectGroupEmit(D_8010C058_cosmic_coaster, 0.0f, 0.0f, 0.0f);
            if (effect >= 0) {
                Hu3DModelCameraSet(effect, cam);
                Hu3DModelPosSet(effect, car->x[0], 270.0f, -100.0f);
                Hu3DModelScaleSet(effect, 2.0f, 2.0f, 2.0f);
            }
        } else {
            HuAudFXPanning(HuAudPlayerFXPlay(0x373, car->player[0]), D_8010BB58_cosmic_coaster[car->group]);
            D_8010BB30_cosmic_coaster.gaugeValue[car->group] *= 0.3f;
            car->tilt[0] = -50.0f;
            car->stunTimer[0] = 10;
            Hu3DMotionModelSet(object->model[3], object->motion[4]);
            omVibrate(car->player[0], 20, 0, 20);
        }
    }
    if ((hits >> 16) != 0xFFFF) {
        if ((hits >> 16) == 4) {
            HuAudFXPanning(HuAudFXPlay(9), D_8010BB58_cosmic_coaster[car->group]);
            GwPlayer[car->player[0]].gameCoin += 1;
            GwPlayer[car->player[1]].gameCoin += 1;
            effect = EffectGroupEmit(D_8010C058_cosmic_coaster, 0.0f, 0.0f, 0.0f);
            if (effect >= 0) {
                Hu3DModelCameraSet(effect, cam);
                Hu3DModelPosSet(effect, car->x[1], 270.0f, 100.0f);
                Hu3DModelScaleSet(effect, 2.0f, 2.0f, 2.0f);
            }
        } else {
            HuAudFXPanning(HuAudPlayerFXPlay(0x373, car->player[1]), D_8010BB58_cosmic_coaster[car->group]);
            D_8010BB30_cosmic_coaster.gaugeValue[car->group] *= 0.3f;
            car->tilt[1] = -50.0f;
            car->stunTimer[1] = 10;
            Hu3DMotionModelSet(object->model[4], object->motion[5]);
            omVibrate(car->player[1], 20, 0, 20);
        }
    }
    Hu3DModelRotSet(object->model[1], car->tilt[0], 180.0f, 0.0f);
    Hu3DModelRotSet(object->model[3], car->tilt[0], 180.0f, 0.0f);
    Hu3DModelRotSet(object->model[2], car->tilt[1], 180.0f, 0.0f);
    Hu3DModelRotSet(object->model[4], car->tilt[1], 180.0f, 0.0f);
    if (D_8010BB30_cosmic_coaster.gaugeValue[car->group] > 0.0f && car->rollSfx == -1) {
        car->rollSfx = HuAudFXPlay(0x372);
        HuAudFXPanning(car->rollSfx, D_8010BB58_cosmic_coaster[car->group]);
    }
    func_80108C9C_cosmic_coaster(object);
}

// Victory sequence of the winning car: the riders turn to face the camera,
// slide to the side, jump off the car, spin, and finally cheer.
void func_80107888_cosmic_coaster(omObjData *object) {
    f32 offsets[2];
    CosmicCoasterCarData *car;
    s16 tmp;
    s32 i;

    offsets[0] = -100.0f;
    offsets[1] = 100.0f;
    car = object->data;
    switch (car->endPhase) {
        case 0:
            car->endPhase = 1;
            D_8010C020_cosmic_coaster = 30;
            break;
        case 1:
            if (D_8010C020_cosmic_coaster != 0) {
                if (--D_8010C020_cosmic_coaster == 0) {
                    Hu3DMotionModelSet(object->model[3], object->motion[8]);
                    Hu3DMotionModelSet(object->model[4], object->motion[9]);
                    Hu3DMotionAttrSet(object->model[3], 3, 2);
                    Hu3DMotionAttrSet(object->model[4], 3, 2);
                }
            } else {
                for (i = 0; i < 2; i++) {
                    if (car->rotY[i] < 270.0f) {
                        car->rotY[i] += 8.0f;
                        if (car->rotY[i] > 270.0f) {
                            car->rotY[i] = 270.0f;
                        }
                    } else {
                        D_8010C024_cosmic_coaster = omAddObj(40, 0, 0, -1, func_8010803C_cosmic_coaster);
                        car->endPhase = 2;
                        Hu3DModelAttrSet(object->model[3 + i], 4, 4);
                        Hu3DModelAttrSet(object->model[7 + i], 4, 0);
                        tmp = object->model[3 + i];
                        object->model[3 + i] = object->model[7 + i];
                        object->model[7 + i] = tmp;
                        Hu3DModelPosSet(object->model[3 + i], car->x[i], car->y[i], offsets[i]);
                        Hu3DModelRotSet(object->model[3 + i], 0.0f, car->rotY[i], 0.0f);
                        Hu3DMotionModelSet(object->model[3], object->motion[0]);
                        Hu3DMotionModelSet(object->model[4], object->motion[1]);
                    }
                    Hu3DModelRotSet(object->model[3 + i], 0.0f, car->rotY[i], 0.0f);
                }
            }
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                car->x[i] -= 20.0f;
                if (car->x[i] < -160.0f) {
                    car->x[i] = -160.0f;
                }
                Hu3DModelPosSet(object->model[1 + i], car->x[i], car->y[i], offsets[i]);
                Hu3DModelPosSet(object->model[3 + i], car->x[i], car->y[i], offsets[i]);
            }
            if (car->x[0] == -160.0f && car->x[1] == -160.0f) {
                car->endPhase = 3;
                Hu3DMotionModelSet(object->model[3], object->motion[6]);
                Hu3DMotionModelSet(object->model[4], object->motion[7]);
                Hu3DMotionAttrSet(object->model[3], 2, 0);
                Hu3DMotionAttrSet(object->model[4], 2, 0);
                for (i = 0; i < 2; i++) {
                    D_8010C018_cosmic_coaster[i] = 70.0f;
                }
                D_8010C010_cosmic_coaster[0] = -17.0f;
                D_8010C010_cosmic_coaster[1] = -12.0f;
            }
            break;
        case 3:
            for (i = 0; i < 2; i++) {
                car->x[i] += D_8010C010_cosmic_coaster[i];
                car->y[i] += D_8010C018_cosmic_coaster[i];
                D_8010C018_cosmic_coaster[i] -= 10.0f;
                if (car->y[i] < 125.0f) {
                    car->y[i] = 125.0f;
                    car->endPhase = 4;
                    omDelObj(D_8010C024_cosmic_coaster);
                    D_8010C024_cosmic_coaster = omAddObj(40, 0, 0, -1, func_801080C8_cosmic_coaster);
                    Hu3DMotionModelSet(object->model[3], object->motion[8]);
                    Hu3DMotionModelSet(object->model[4], object->motion[9]);
                }
                Hu3DModelPosSet(object->model[3 + i], car->x[i], car->y[i], offsets[i]);
                Hu3DModelAttrSet(object->model[5 + i], 4, 0);
                Hu3DModelPosSet(object->model[5 + i], car->x[i], 125.0f, offsets[i]);
            }
            break;
        case 4:
            for (i = 0; i < 2; i++) {
                car->rotY[i] += 8.0f;
                if (car->rotY[i] >= 360.0f) {
                    car->rotY[0] = 0.0f;
                    car->endPhase = 5;
                }
                Hu3DModelRotSet(object->model[3 + i], 0.0f, car->rotY[i], 0.0f);
            }
            break;
        case 5:
            if (D_8010C024_cosmic_coaster->work[0] == 1) {
                car->endPhase = 6;
                omDelObj(D_8010C024_cosmic_coaster);
            }
            break;
        case 6:
            D_8010C028_cosmic_coaster = D_8010C3B0_cosmic_coaster[(s16)(D_8010C3BC_cosmic_coaster ^ 1)];
            for (i = 0; i < 2; i++) {
                Hu3DMotionShiftSet(object->model[3 + i], Hu3DData[object->motion[10 + i]].motId, 0, 6, 0);
                Hu3DMotionShiftSet(D_8010C028_cosmic_coaster->model[3 + i],
                                   Hu3DData[D_8010C028_cosmic_coaster->motion[12 + i]].motId, 0, 6, 0);
                HuAudCharVoicePlay(D_800A178C_main[GwPlayer[car->player[0]].chr][0] | 0x2F);
                HuAudCharVoicePlay(D_800A178C_main[GwPlayer[car->player[1]].chr][0] | 0x2F);
            }
            D_8010C028_cosmic_coaster->work[0] = 1;
            D_8010C028_cosmic_coaster->work[1] = 45;
            MgFlowStatSet(MG_STATE_RESULT);
            car->endPhase = 7;
            break;
    }
}

// Scrolls the winning car's camera toward the car's x position.
void func_8010803C_cosmic_coaster(omObjData *object) {
    CosmicCoasterCarData *car = D_8010C3B0_cosmic_coaster[D_8010C3BC_cosmic_coaster]->data;

    if (CenterM[D_8010C3BC_cosmic_coaster].x > car->x[0]) {
        CenterM[D_8010C3BC_cosmic_coaster].x -= 20.0f;
        if (CenterM[D_8010C3BC_cosmic_coaster].x < car->x[0]) {
            CenterM[D_8010C3BC_cosmic_coaster].x = car->x[0];
        }
    }
}

// Counts down a short zoom-out animation for the active camera. Once the
// countdown reaches zero the object flags itself with work[0] = 1 so its
// parent knows to delete it.
void func_801080C8_cosmic_coaster(omObjData *arg0) {
    if (D_8010BB8C_cosmic_coaster != 0) {
        CZoomM[D_8010C3BC_cosmic_coaster] -= 30.0f;
        D_8010BB8C_cosmic_coaster--;
    } else {
        arg0->work[0] = 1;
    }
}

void func_80108124_cosmic_coaster(omObjData *object) {
}

void func_8010812C_cosmic_coaster(omObjData *object) {
    u8 lanes[3];
    u8 freeLanes[3];
    f32 laneX[3] = { -160.0f, 0.0f, 160.0f };
    f32 offsets[2];
    omObjData *found[2];
    CosmicCoasterCarData *car;
    omObjData *target;
    f32 lookahead;
    u32 mask;
    u8 n;
    s32 i;
    s32 j;

    offsets[0] = -100.0f;
    offsets[1] = 100.0f;
    car = object->data;
    lookahead = D_8010BB30_cosmic_coaster.gaugeValue[car->group] / 1.08f * 15.0f;
    found[0] = found[1] = NULL;
    func_8010B644_cosmic_coaster(found, car, lookahead + car->progress, car->progress, 0);
    for (i = 0; i < 2; i++) {
        if (car->state[i] == 0) {
            target = found[i];
            if (target != NULL) {
                car->carried[i] = target;
                mask = func_8010B97C_cosmic_coaster(object, i, target);
                car->state[i] = 1;
                lanes[0] = (mask & 0x30) >> 4;
                lanes[1] = (mask & 0xC) >> 2;
                lanes[2] = mask & 3;
                n = 0;
                for (j = 0; j < 3; j++) {
                    if (lanes[j] < 2) {
                        freeLanes[n++] = j;
                    }
                }
                if (car->targetX[i] == 100000.0f) {
                    if (n == 1) {
                        car->targetX[i] = laneX[freeLanes[0]];
                    } else {
                        car->targetX[i] = laneX[freeLanes[rand8() % n]];
                    }
                }
            }
        } else {
            D_8010C3B8_cosmic_coaster = car->carried[i];
            if (car->progress - offsets[i] - 30.0f > car->carried[i]->trans.z) {
                car->carried[i] = NULL;
                car->targetX[i] = 100000.0f;
                car->state[i] = 0;
            }
        }
    }
}

// Computes the CPU stick input that steers a rider toward its target lane.
// The stick strength and the dead zone depend on the CPU difficulty.
void func_801083D0_cosmic_coaster(omObjData *object, s16 slot, s8 *stickX) {
    CosmicCoasterCarData *car = object->data;
    s8 speed;
    f32 deadZone;
    f32 diff;

    *stickX = 0;
    if (car->targetX[slot] == 100000.0f) {
        return;
    }
    if (car->hasHuman == 1) {
        speed = 70;
        deadZone = 4.0f;
    } else {
        switch (GwPlayer[car->player[slot]].cpu_difficulty) {
            case 0:
                speed = rand8() % 13 + 58;
                deadZone = 2.0f;
                break;
            case 1:
                speed = rand8() % 10 + 62;
                deadZone = 2.0f;
                break;
            case 2:
                speed = (rand8() & 7) + 66;
                deadZone = 3.0f;
                break;
            case 3:
                speed = 70;
                deadZone = 4.0f;
                break;
        }
    }
    if (speed > 70) {
        speed = 70;
    }
    if (car->x[slot] > car->targetX[slot]) {
        diff = car->x[slot] - car->targetX[slot];
        if (diff > 10.0f) {
            *stickX = -speed;
        } else if (diff < deadZone) {
            car->targetX[slot] = 100000.0f;
        } else {
            *stickX = -speed / 2;
        }
    } else if (car->x[slot] < car->targetX[slot]) {
        diff = car->x[slot] - car->targetX[slot];
        if (diff < -10.0f) {
            *stickX = speed;
        } else if (diff < -deadZone) {
            car->targetX[slot] = 100000.0f;
        } else {
            *stickX = speed / 2;
        }
    } else {
        car->targetX[slot] = 100000.0f;
    }
}

// Intro camera sweep through the D_8010BB90 keyframes for both cameras.
void func_8010869C_cosmic_coaster(omObjData *object) {
    s32 i;

    switch (D_8010C05A_cosmic_coaster) {
        case 0:
            WipeCreateIn(0xFF, 16);
            D_8010C05A_cosmic_coaster = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                D_8010C05A_cosmic_coaster = 2;
                D_8010C04C_cosmic_coaster = 0;
                D_8010C02C_cosmic_coaster = CZoomM[0];
                D_8010C030_cosmic_coaster = (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].rot.x - -8.0f) / 30.0f;
                D_8010C034_cosmic_coaster = (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].rot.y - 180.0f) / 30.0f;
                D_8010C038_cosmic_coaster = (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].rot.z - 0.0f) / 30.0f;
                D_8010C03C_cosmic_coaster = (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].center.x - 0.0f) / 30.0f;
                D_8010C040_cosmic_coaster = (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].center.y - 200.0f) / 30.0f;
                D_8010C044_cosmic_coaster = (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].center.z - 0.0f) / 30.0f;
                D_8010C048_cosmic_coaster = D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].frames;
            }
            break;
        case 2:
            if (--D_8010C048_cosmic_coaster != 0) {
                for (i = 0; i < 2; i++) {
                    CRotM[i].x += D_8010C030_cosmic_coaster;
                    CRotM[i].y += D_8010C034_cosmic_coaster;
                    CRotM[i].z += D_8010C038_cosmic_coaster;
                    CenterM[i].x += D_8010C03C_cosmic_coaster;
                    CenterM[i].y += D_8010C040_cosmic_coaster;
                    CenterM[i].z += D_8010C044_cosmic_coaster;
                    if (CRotM[i].y > 90.0f) {
                        CZoomM[i] = D_8010C02C_cosmic_coaster +
                                    fabs(sindf(CRotM[i].y)) * D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].zoom;
                    } else {
                        CZoomM[i] = D_8010C02C_cosmic_coaster +
                                    fabs(cosdf(CRotM[i].y)) * D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].zoom;
                    }
                }
            } else {
                for (i = 0; i < 2; i++) {
                    CRotM[i].x = D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].rot.x;
                    CRotM[i].y = D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].rot.y;
                    CRotM[i].z = D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].rot.z;
                    CenterM[i].x = D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].center.x;
                    CenterM[i].y = D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].center.y;
                    CenterM[i].z = D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].center.z;
                    if (CRotM[i].y >= 90.0f) {
                        CZoomM[i] = D_8010C02C_cosmic_coaster +
                                    fabs(sindf(CRotM[i].y)) * D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].zoom;
                    } else {
                        CZoomM[i] = D_8010C02C_cosmic_coaster +
                                    fabs(cosdf(CRotM[i].y)) * D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].zoom;
                    }
                }
                if (++D_8010C04C_cosmic_coaster == 2) {
                    D_8010C05A_cosmic_coaster = 3;
                    HuAudSeqPlay(0x37);
                } else {
                    D_8010C030_cosmic_coaster =
                        (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].rot.x - CRotM[0].x) / 30.0f;
                    D_8010C034_cosmic_coaster =
                        (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].rot.y - CRotM[0].y) / 30.0f;
                    D_8010C038_cosmic_coaster =
                        (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].rot.z - CRotM[0].z) / 30.0f;
                    D_8010C03C_cosmic_coaster =
                        (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].center.x - CenterM[0].x) / 30.0f;
                    D_8010C040_cosmic_coaster =
                        (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].center.y - CenterM[0].y) / 30.0f;
                    D_8010C044_cosmic_coaster =
                        (D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].center.z - CenterM[0].z) / 30.0f;
                    D_8010C02C_cosmic_coaster = CZoomM[0];
                    D_8010C048_cosmic_coaster = D_8010BB90_cosmic_coaster[D_8010C04C_cosmic_coaster].frames;
                }
            }
            break;
        case 3:
            omDelObj(object);
            D_8010C050_cosmic_coaster = NULL;
            MgFlowStatSet(MG_STATE_START);
            break;
    }
}

// Lights the car and its riders from the nearest track object of type 4
// (work[1]) within range, fading the light out with distance.
void func_80108C9C_cosmic_coaster(omObjData *object) {
    CosmicCoasterCarData *car = object->data;
    omObjData **list;
    omObjData *nearest;
    omObjData *obj;
    f32 minDist;
    f32 dist;
    f32 dirX;
    f32 dirY;
    f32 dirZ;
    u8 r;
    u8 g;
    u8 b;
    s32 i;

    list = omGetGroupMemberList(car->group);
    nearest = NULL;
    minDist = 500000.0f;
    for (i = 0; i < 55; i++) {
        obj = list[i];
        if (obj == NULL || obj->work[1] != 4) {
            continue;
        }
        dist = HuSqrtf((obj->trans.x - object->trans.x) * (obj->trans.x - object->trans.x) +
                       (obj->trans.y - object->trans.y) * (obj->trans.y - object->trans.y) +
                       (car->progress - obj->trans.z - object->trans.z) *
                           (car->progress - obj->trans.z - object->trans.z));
        if (dist < minDist) {
            minDist = dist;
            nearest = obj;
        }
    }
    if (nearest != NULL && minDist <= 1600.0f) {
        dirX = (nearest->trans.x - object->trans.x) / minDist * 127.0f;
        dirY = (nearest->trans.y - object->trans.y) / minDist * 127.0f;
        dirZ = (car->progress - nearest->trans.z - object->trans.z) / minDist * 127.0f;
        r = (1600.0f - minDist) * 0.159375f;
        g = (1600.0f - minDist) * 0.159375f;
        b = (1600.0f - minDist) * 0.159375f;
        Hu3DLLightColorSet(object->model[0], r, g, b);
        Hu3DLLightDirSet(object->model[0], dirX, dirY, dirZ);
        for (i = 0; i < 2; i++) {
            Hu3DLLightColorSet(object->model[1 + i], r, g, b);
            Hu3DLLightDirSet(object->model[1 + i], dirX, dirY, dirZ);
            Hu3DLLightColorSet(object->model[3 + i], r, g, b);
            Hu3DLLightDirSet(object->model[3 + i], dirX, dirY, dirZ);
        }
    } else {
        Hu3DLLightColorSet(object->model[0], 0, 0, 0);
        for (i = 0; i < 2; i++) {
            Hu3DLLightColorSet(object->model[1 + i], 0, 0, 0);
            Hu3DLLightColorSet(object->model[3 + i], 0, 0, 0);
        }
    }
}

void func_801090C0_cosmic_coaster(omObjData *object) {
    CosmicCoasterEffectData *data;
    s16 sprite;
    s16 sprite2;
    s32 i;

    data = object->data = HuMemAllocTag(sizeof(CosmicCoasterEffectData), TAG_OVERLAY);
    sprite = HuSprAnimDataRead(0x310012);
    sprite2 = HuSprAnimDataRead(0x310013);
    for (i = 0; i < 6; i++) {
        data->sprite[i] = espEntry(sprite, 0, 0);
        espPriSet(data->sprite[i], 0x815E);
        espAttrSet(data->sprite[i], 0x4000);
        espScaleSet(data->sprite[i], 0.5f, 0.5f);
        espDispOff(data->sprite[i]);
        data->sprite2[i] = espEntry(sprite2, 0, 0);
        espPriSet(data->sprite2[i], 0x815E);
        espAttrSet(data->sprite2[i], 0x4000);
        espScaleSet(data->sprite2[i], 0.5f, 0.5f);
        espDispOff(data->sprite2[i]);
        data->inUse[i] = 0;
    }
    for (i = 0; i < 2; i++) {
        data->timer[i] = rand8() + 120;
    }
    object->func = func_80109290_cosmic_coaster;
}

// Marks the first unused of the 6 star sprite slots as in use, returning its
// index, or -1 if all are in use.
s16 func_8010923C_cosmic_coaster(CosmicCoasterEffectData *data) {
    s16 i;

    for (i = 0; i < 6; i++) {
        if (data->inUse[i] == 0) {
            data->inUse[i] = 1;
            return i;
        }
    }

    return -1;
}

// Periodically launches a shooting star on each half of the screen.
void func_80109290_cosmic_coaster(omObjData *object) {
    CosmicCoasterEffectData *data = object->data;
    CosmicCoasterStarData *star;
    omObjData *starObj;
    f32 angle;
    f32 dir;
    f32 x;
    f32 y;
    s16 slot;
    s32 i;

    for (i = 0; i < 2; i++) {
        if (--data->timer[i] == 0) {
            data->timer[i] = (u8)(rand8() % 121) + 120;
            slot = func_8010923C_cosmic_coaster(data);
            if (slot != -1) {
                starObj = omAddObj(40, 0, 0, -1, func_801096A8_cosmic_coaster);
                star = starObj->data = HuMemAllocTag(sizeof(CosmicCoasterStarData), TAG_OVERLAY);
                star->side = i;
                angle = (rand8() * rand8()) % 1801;
                angle /= 10.0f;
                if (angle >= 60.0f && angle <= 120.0f) {
                    if (angle > 90.0f) {
                        angle = 120.0f;
                    } else {
                        angle = 60.0f;
                    }
                }
                x = cosdf(angle) * 160.0f;
                y = -(sindf(angle) * 160.0f + 80.0f);
                // The clamps must stay unbraced: each braced body emits an
                // extra block note, lengthening the constants' lifetimes enough
                // that the loop optimizer hoists 164.0f and 156.0f.
                // NOLINTBEGIN(readability-braces-around-statements)
                if (i == 0) {
                    if (x < -20.0f)
                        x = -20.0f;
                    if (x > 164.0f)
                        x = 164.0f;
                } else {
                    x += 160.0f;
                    if (x < 156.0f)
                        x = 156.0f;
                    if (x > 340.0f)
                        x = 180.0f;
                }
                if (y < -20.0f)
                    y = -20.0f;
                if (y > 80.0f)
                    y = 80.0f;
                // NOLINTEND(readability-braces-around-statements)
                star->x = x;
                star->y = y;
                dir = angle - 180.0f;
                star->vx = cosdf(dir) * 4.5f;
                star->vy = -sindf(dir) * 4.5f;
                star->inUse = &data->inUse[slot];
                star->sprite = data->sprite[slot];
                star->sprite2 = data->sprite2[slot];
                espPosSet(star->sprite, star->x, star->y);
                espDispOn(star->sprite);
                espPosSet(star->sprite2, star->x, star->y);
                espDispOn(star->sprite2);
            }
        }
    }
}

// Moves a shooting star and frees it once it leaves its half of the screen.
void func_801096A8_cosmic_coaster(omObjData *object) {
    CosmicCoasterStarData *star = object->data;

    star->x += star->vx;
    star->y += star->vy;
    star->vy *= 1.0f;
    espPosSet(star->sprite, star->x, star->y);
    espPosSet(star->sprite2, star->x, star->y);
    espZRotSet(star->sprite2, atan2df(-star->vy, star->vx) - 180.0f);
    switch (star->side) {
        case 0:
            if (star->y >= 260.0f || (star->vx < 0.0f && star->x < -20.0f) ||
                (star->vy >= 0.0f && star->x > 164.0f)) {
                espDispOff(star->sprite);
                espDispOff(star->sprite2);
                *star->inUse = 0;
                omDelObj(object);
            }
            break;
        case 1:
            if (star->y >= 260.0f || (star->vx < 0.0f && star->x < 156.0f) ||
                (star->vy >= 0.0f && star->x > 324.0f)) {
                espDispOff(star->sprite);
                espDispOff(star->sprite2);
                *star->inUse = 0;
                omDelObj(object);
            }
            break;
    }
}
