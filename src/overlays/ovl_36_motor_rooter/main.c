#include "overlays/ovl_36.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/hmfman.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "mallocblock.h"
#include "math.h"
#include "include_asm.h"
#include "input.h"
#include "variables.h"
#include "functions.us.h"

#define PLAYERS_TOTAL 2

// C1F0
void func_8000B5F0_main(u8 arg0);
s32 func_8000B710_main(s32 arg0);

// 14EA0
void func_800142A0_main(s32);
void func_80017D24_main(f32 *, f32, f32, f32);

// 20A20

// unknown
extern u16 D_800D530C_main;
extern s32 D_800A178C_main[][6];

enum {
    FGRP_CAMERA
};

typedef struct {
    s32 fileIds[2][2];
} CourseModels;

typedef struct {
    s32 fileIds[8];
} CharacterSprites;

typedef struct {
    s32 fileIds[7];
} ObstacleSprites;

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ s16 obstacleSprites[21];
    /* 0x2E */ s16 obstacleSlots[3];
    /* 0x34 */ s16 obstacleSafeDirections[3][3];
    /* 0x46 */ s16 obstacleFrames[3];
    /* 0x4C */ s16 obstaclePoints[10];
    /* 0x60 */ s16 obstacleDirections[10];
    /* 0x74 */ s16 obstacleTypes[10];
    /* 0x88 */ s16 nextObstacleSlot;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ omObjData *unk8C;
    /* 0x90 */ s16 itemSlots[15];
    /* 0xAE */ s16 nextItemSlot;
    /* 0xB0 */ s16 itemSprites[5];
    /* 0xBA */ s16 itemFrames[5];
    /* 0xC4 */ s8 itemDelays[4];
    /* 0xC8 */ s8 itemStates[4];
    /* 0xCC */ char unkCC[8];
    /* 0xD4 */ s16 itemTimer;
    /* 0xD6 */ char unkD6[0x1E];
} PlayerView; // Size 0xF4

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 pitch;
    /* 0x10 */ f32 yaw;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 segLen;
    /* 0x1C */ f32 invSegLen;
    /* 0x20 */ f32 cumDist;
} PathPoint; // Size 0x24

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ f32 pitch;
    /* 0x14 */ f32 yaw;
    /* 0x18 */ f32 roll;
} PathPosition; // Size 0x1C

typedef union {
    struct {
        /* 0x00 */ s8 viewCounters[6];
        /* 0x06 */ s8 itemViewCount;
        /* 0x07 */ char unk07[0x19];
    } initialization;
    struct {
        /* 0x00 */ s8 playerCounters[PLAYERS_TOTAL * 4];
        /* 0x08 */ char unk08[8];
        /* 0x10 */ s16 impactFrameCounters[PLAYERS_TOTAL];
        /* 0x14 */ char unk14[0xC];
    } gameplay;
} MinigameCounters; // Size 0x20

typedef struct {
    /* 0x00 */ MinigameCounters counters;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ char unk24[0xC];
} MinigameRuntime; // Size 0x30

typedef struct {
    /* 0x000 */ PlayerView *views;
    /* 0x004 */ f32 totalDistance;
    /* 0x008 */ f32 finishDistance;
    /* 0x00C */ s16 pathPointCount;
    /* 0x00E */ s16 unk0E;
    /* 0x010 */ f32 timer;
    /* 0x014 */ s16 itemPoints[100];
    /* 0x0DC */ s16 itemDirections[100];
    /* 0x1A4 */ MinigameRuntime runtime;
} MinigameData; // Size 0x1D4

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ s16 controllerPort;
    /* 0x06 */ s16 isCpu;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s8 unk14;
    /* 0x15 */ char unk15;
    /* 0x16 */ s16 direction;
    /* 0x18 */ f32 turnAngle;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 meterSprites[5];
    /* 0x28 */ s16 unk28[5];
    /* 0x32 */ s8 animChange;
    /* 0x34 */ s16 nextAnim;
    /* 0x36 */ char unk36[0x12];
    /* 0x48 */ s16 unk48;
    /* 0x4A */ s16 progressSprite;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ char unk4E[0xA];
    /* 0x58 */ Vec cameraStart;
    /* 0x64 */ f32 rotationStart;
    /* 0x68 */ Vec motion;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ u16 unk78;
    /* 0x7A */ char unk7A[2];
    /* 0x7C */ Vec motionCopy;
    /* 0x88 */ s16 obstacleSoundStarted;
    /* 0x8A */ s16 obstacleSound;
} D_801137C8_motor_rooter_Struct; // Size 0x8C

void m254_InitEnvironment(void);
void m254_CreateMinigame(void);
void m254_CheckExitRequest(omObjData *object);
void m254_WaitExitWipeOut(omObjData *object);
void m254_ExitOverlay(omObjData *object);
void func_80106044_motor_rooter(omObjData *object);
void func_80106298_motor_rooter(omObjData *object);
void func_801062BC_motor_rooter(omObjData *object);
void func_801064EC_motor_rooter(omObjData *object);
void func_80106508_motor_rooter(omObjData *object);
void func_80106998_motor_rooter(omObjData *object);
void func_80106B7C_motor_rooter(omObjData *object);
void func_8010A174_motor_rooter(FuncContext *ctx);
void func_80106BAC_motor_rooter(omObjData *object);
void func_80107210_motor_rooter(omObjData *object);
void func_801076AC_motor_rooter(omObjData *object);
void func_801079E8_motor_rooter(omObjData *object);
void func_80107D50_motor_rooter(omObjData *object);
void m254_InitCamera(FuncContext *ctx);
void func_801082E0_motor_rooter(FuncContext *ctx);
void func_80108514_motor_rooter(FuncContext *ctx);
void func_80108E6C_motor_rooter(FuncContext *ctx);
void func_80108BF0_motor_rooter(FuncContext *ctx);
void func_801087C0_motor_rooter(FuncContext *ctx);
void func_801089B8_motor_rooter(FuncContext *ctx);
void func_8010A440_motor_rooter(FuncContext *ctx);
void func_8010BDF0_motor_rooter(FuncContext *ctx);
void func_8010AF0C_motor_rooter(FuncContext *ctx);
void func_8010B394_motor_rooter(FuncContext *ctx);
void func_8010B970_motor_rooter(FuncContext *ctx);
void func_80109134_motor_rooter(FuncContext *ctx);
void func_80108FDC_motor_rooter(FuncContext *ctx);
void func_801107FC_motor_rooter(u16 modelId, HuSprite_Unk84_Struct *sprite, u16 frame);
void func_801108CC_motor_rooter(u16 modelId, HuSprite_Unk84_Struct *sprite, u16 frame, RGBA *color);
void func_8010CB2C_motor_rooter(omObjData *object, s16 item, s16 modelIndex);
void func_8010CD84_motor_rooter(Vec *, s16);
s16 func_8010D03C_motor_rooter(f32);
PathPosition func_8010D0AC_motor_rooter(s16, f32);
void func_8010D2E4_motor_rooter(s32);
void func_8010DC3C_motor_rooter(s16 point, s16 direction);
void func_801070CC_motor_rooter(omObjData *object);
void func_8010ABC4_motor_rooter(FuncContext *ctx);
void func_8010BCD0_motor_rooter(FuncContext *ctx);
void func_8010BB78_motor_rooter(FuncContext *ctx);
void func_8010BDE4_motor_rooter(D_801137C8_motor_rooter_Struct *player, s16 anim, s8 change);
void func_8010C084_motor_rooter(FuncContext *ctx);
void func_8010C44C_motor_rooter(FuncContext *ctx);
void func_8010C824_motor_rooter(FuncContext *ctx);
void func_80109C94_motor_rooter(PlayerView *view, s16 slot);
void func_80109EFC_motor_rooter(FuncContext *ctx);
void func_8010961C_motor_rooter(FuncContext *ctx);
void func_8010972C_motor_rooter(FuncContext *ctx);
void func_801091A0_motor_rooter(FuncContext *ctx);
void func_80106968_motor_rooter(omObjData *object);

// BSS
extern PathPoint *D_801137C0_motor_rooter;
extern MinigameData *m254_minigame; // D_801137C4_motor_rooter
extern D_801137C8_motor_rooter_Struct *D_801137C8_motor_rooter;
extern s16 D_801137CC_motor_rooter;
extern s16 D_801137CE_motor_rooter;
extern s16 D_801137D0_motor_rooter;
extern s16 D_801137D2_motor_rooter;
extern s16 m254_playerId[]; // D_801137D4_motor_rooter
extern s16 D_801137D8_motor_rooter;
extern s16 D_8011345A_motor_rooter[];
extern s16 D_8011349E_motor_rooter[];
extern s8 D_8011349C_motor_rooter[];
extern s8 D_80113468_motor_rooter[];
extern s8 D_8011346C_motor_rooter[];

extern Vec D_80111550_motor_rooter[];
extern Vec D_8011245C_motor_rooter[];

extern s16 D_801135E0_motor_rooter[];
extern s16 D_801135EC_motor_rooter[];
extern s16 D_801135FC_motor_rooter[];
extern s16 D_80113458_motor_rooter;
extern s16 D_80113498_motor_rooter;
extern s16 D_80113494_motor_rooter;
extern s16 D_80113496_motor_rooter;
extern CourseModels D_80113608_motor_rooter;
extern CharacterSprites D_80113634_motor_rooter;
extern ObstacleSprites D_80113618_motor_rooter;
extern RGBA D_80113470_motor_rooter;
extern s32 D_80113474_motor_rooter[];
extern const f64 D_80113658_motor_rooter;

void m254_OverlayMain(void) {
    m254_InitEnvironment();
}

void m254_InitEnvironment(void) {
    omObjData *temp_v0;

    Hu3DAnimInit(50);
    func_800142A0_main(0x30);
    omInitObjMan(50, 0);
    func_8004A208_main();
    temp_v0 = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    temp_v0->work[0] = 2;
    omSetStatBit(temp_v0, 0xA0);
    HmfLightColorSet(0, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, -56.0f, 50.0f, 56.0f);
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    ScissorSet(0, 0.0f, 0.0f, 152.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 60.0f, 40.0f, 4000.0f);
    ScissorSet(1, 168.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(1, 60.0f, 40.0f, 4000.0f);
    Hu3DBGColorSet(0xFF, 0xFF, 0xFF);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    m254_CreateSystem();
    m254_CreateMinigame();
    omAddObj(100, 0, 0, -1, func_80106044_motor_rooter);
    omAddObj(1000, 0, 0, -1, m254_CheckExitRequest);
    func_80045010_main(D_801135E0_motor_rooter, 1);
    func_80045010_main(D_801135EC_motor_rooter, 1);
    func_80045010_main(D_801135FC_motor_rooter, 1);
}

void m254_CreateMinigame(void) {
    s16 player1Set = FALSE;
    s16 player2Set = FALSE;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            if (!player1Set) {
                m254_playerId[0] = i;
                player1Set = TRUE;
            }
        } else if (GwPlayer[i].group == 1) {
            if (!player2Set) {
                m254_playerId[1] = i;
                player2Set = TRUE;
            }
        }
    }
    m254_minigame = HuMemAllocTag(sizeof(MinigameData), 31000);
    memset(m254_minigame, 0, sizeof(MinigameData));
    m254_minigame->views = HuMemAllocTag(PLAYERS_TOTAL * sizeof(PlayerView), 31000);
    memset(m254_minigame->views, 0, PLAYERS_TOTAL * sizeof(PlayerView));
    D_801137CE_motor_rooter = (rand16() % 201) / 100;
    switch (D_801137CE_motor_rooter) {
        case 0:
            D_801137CC_motor_rooter = 280;
            func_8010CD84_motor_rooter(D_80111550_motor_rooter, 321);
            break;
        case 1:
            D_801137CC_motor_rooter = 300;
            func_8010CD84_motor_rooter(D_8011245C_motor_rooter, 341);
            break;
        default:
            D_801137CC_motor_rooter = 280;
            func_8010CD84_motor_rooter(D_80111550_motor_rooter, 321);
            D_801137CE_motor_rooter = 0;
            break;
    }
    func_8010D2E4_motor_rooter(0);
    D_801137C8_motor_rooter = HuMemAllocTag(2 * sizeof(D_801137C8_motor_rooter_Struct), 31000); // PLAYERS_TOTAL?
    memset(D_801137C8_motor_rooter, 0, 2 * sizeof(D_801137C8_motor_rooter_Struct));
}

void m254_CheckExitRequest(omObjData *object) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        object->func = m254_WaitExitWipeOut;
    }
}

void m254_WaitExitWipeOut(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = m254_ExitOverlay;
    }
}

void m254_ExitOverlay(omObjData *object) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_80105F04_motor_rooter(void) {
    s16 i;

    for (i = 0; i < 2; i++) {
        if (CRotM[i].x > 360.0f) {
            CRotM[i].x -= 360.0f;
        } else if (CRotM[i].x < 0.0f) {
            CRotM[i].x += 360.0f;
        }
        if (CRotM[i].y > 360.0f) {
            CRotM[i].y -= 360.0f;
        } else if (CRotM[i].y < 0.0f) {
            CRotM[i].y += 360.0f;
        }
    }
    m254_UpdateFuncGroup(FGRP_CAMERA);
}

void func_80106044_motor_rooter(omObjData *object) {
    s16 i;

    func_8001EF24_main(0x3CA, 1000, 0xFF, 0xFF, 0xFF);
    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    for (i = 0; i < 2; i++) {
        D_800EC1C0_minigame[i] = omAddObj(10, 2, 0, -1, func_801062BC_motor_rooter);
        m254_minigame->views[i].unk00 = omAddObj(100, 21, 0, -1, func_80106508_motor_rooter);
        m254_minigame->views[i].unk8C = omAddObj(200, 15, 0, -1, func_80106998_motor_rooter);
        omAddObj(500, 1, 0, -1, func_80107210_motor_rooter);
        omAddObj(800, 5, 0, -1, func_801079E8_motor_rooter);
        D_800EC598_minigame[i] = D_801137C8_motor_rooter[i].unk00 = omAddObj(300, 11, 40, -1, func_80106BAC_motor_rooter);
    }
    memset(&m254_minigame->runtime, 0, sizeof(m254_minigame->runtime));
    m254_SetFunc(FGRP_CAMERA, 0, -1, NULL, m254_InitCamera, 0, FALSE);
    m254_SetFunc(1, 0, -1, NULL, func_80108BF0_motor_rooter, 0, FALSE);
    WipeCreateIn(0xFF, 0x10);
    object->func = func_80106298_motor_rooter;
}

void func_80106298_motor_rooter(omObjData *object) {
    m254_UpdateFuncGroup(1);
    func_80105F04_motor_rooter();
}

void func_801062BC_motor_rooter(omObjData *object) {
    s32 modelFlags = 0x99;
    CourseModels courseModels = D_80113608_motor_rooter;
    s16 modelCounts[2] = { 2, 2 };
    s16 i;
    s16 cameraMask;

    object->work[0] = m254_minigame->runtime.counters.initialization.viewCounters[0];
    for (i = 0; i < modelCounts[D_801137CE_motor_rooter]; i++) {
        if (object->work[0] == 0) {
            object->model[i] = func_8000B108_main(courseModels.fileIds[D_801137CE_motor_rooter][i] | 0x570000, modelFlags);
        } else {
            object->model[i] = Hu3DModelLink(D_800EC1C0_minigame[0]->model[i]);
        }
        Hu3DModelPosSet(object->model[i], 0.0f, 0.0f, 0.0f);
    }
    m254_SyncWithModel(object);
    cameraMask = object->work[0] == 0 ? 1 : 2;
    for (i = 0; i < modelCounts[D_801137CE_motor_rooter]; i++) {
        func_8001C8A8_main(object->model[i], cameraMask);
    }
    m254_minigame->runtime.counters.initialization.viewCounters[0]++;
    object->func = func_801064EC_motor_rooter;
}

void func_801064EC_motor_rooter(omObjData *object) {
    m254_SyncWithModel(object);
}

void func_80106508_motor_rooter(omObjData *object) {
    ObstacleSprites sprites = D_80113618_motor_rooter;
    s32 *fileIds;
    PlayerView *view;
    FuncContext *ctx;
    s16 i;
    s16 j;
    s16 cameraMask;
    s16 spriteId;
    s16 k;

    object->work[0] = m254_minigame->runtime.counters.initialization.viewCounters[1];
    view = &m254_minigame->views[object->work[0]];
    for (i = 0, fileIds = sprites.fileIds; i < 3; i++) {
        for (j = 0; j < 7; j++) {
            spriteId = func_8000B838_main(fileIds[j] | 0x570000);
            m254_minigame->views[object->work[0]].obstacleSprites[i * 7 + j] = spriteId;
            object->model[i * 7 + j] = func_8010EFF8_motor_rooter(func_80055194_main(spriteId), 1.0f);
            Hu3DModelScaleSet(object->model[i * 7 + j], 2.0f, 2.0f, 2.0f);
        }
        view->obstacleSlots[i] = view->nextObstacleSlot++;
        if (view->nextObstacleSlot > D_801137D2_motor_rooter) {
            for (j = i * 7; j < i * 7 + 7; j++) {
                func_8001C258_main(object->model[j], 4, 4);
            }
            view->obstacleSlots[i] = -1;
        } else {
            func_80109C94_motor_rooter(view, i);
        }
        view->obstacleFrames[i] = rand16() % 3;
    }
    cameraMask = object->work[0] == 0 ? 1 : 2;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 7; j++) {
            func_8001C8A8_main(object->model[i * 7 + j], cameraMask);
        }
    }
    m254_minigame->runtime.counters.initialization.viewCounters[1]++;
    m254_SetFunc(2, 6, -1, &m254_minigame->views[object->work[0]], func_8010961C_motor_rooter, object->work[0], FALSE);
    ctx = m254_SetFunc(2, 7, -1, &m254_minigame->views[object->work[0]], func_8010972C_motor_rooter, object->work[0], FALSE);
    for (k = 0; k < 3; k++) {
        ctx->work.s16[0] = k;
        func_801091A0_motor_rooter(ctx);
    }
    m254_SyncWithModel(object);
    object->func = func_80106968_motor_rooter;
}

void func_80106968_motor_rooter(omObjData *object) {
    m254_UpdateFuncGroup(2);
    m254_SyncWithModel(object);
}

void func_80106998_motor_rooter(omObjData *object) {
    PlayerView *view;
    s16 i;
    s16 cameraMask;
    s32 modelFlags = 0x99;

    object->work[0] = m254_minigame->runtime.counters.initialization.viewCounters[3];
    view = &m254_minigame->views[object->work[0]];
    for (i = 0; i < 15; i++) {
        if (object->work[0] == 0) {
            object->model[i] = func_8000B108_main(0x570002, modelFlags);
        } else {
            object->model[i] = Hu3DModelLink(m254_minigame->views[0].unk8C->model[i]);
        }
        view->itemSlots[i] = view->nextItemSlot++;
        Hu3DModelScaleSet(object->model[i], 0.7f, 0.7f, 0.7f);
    }
    m254_SyncWithModel(object);
    cameraMask = object->work[0] == 0 ? 1 : 2;
    for (i = 0; i < 15; i++) {
        func_8001C8A8_main(object->model[i], cameraMask);
    }
    m254_minigame->runtime.counters.initialization.viewCounters[3]++;
    m254_SetFunc(3, 5, -1, object, func_8010A174_motor_rooter, 0, FALSE);
    object->func = func_80106B7C_motor_rooter;
}

void func_80106B7C_motor_rooter(omObjData *object) {
    m254_UpdateFuncGroup(3);
    m254_SyncWithModel(object);
}

void func_80106BAC_motor_rooter(omObjData *object) {
    s32 modelFiles[2] = { 0, 1 };
    func_800E1BA8_minigame_ObjData *data;
    s16 character;
    s32 modelFlags = 0x289;
    s32 characterIndex;
    s32 characterModel;
    s32 characterMotion;
    s32 motion;
    s16 cameraMask;
    s16 i;

    object->work[0] = D_800EC280_minigame;
    object->work[1] = m254_playerId[object->work[0]];
    character = GwPlayer[object->work[1]].chr;
    characterIndex = GwPlayer[object->work[1]].chr;
    characterModel = D_800A178C_main[characterIndex][0];
    characterMotion = D_800A178C_main[characterIndex][2];
    func_800E1BA8_minigame(object, characterModel, characterMotion, object->work[1], modelFlags, 0x299);
    func_8001C258_main(object->model[1], 4, 4);
    Hu3DModelScaleSet(object->model[1], 0.2f, 0.2f, 0.2f);
    object->model[9] = func_8000B108_main(modelFiles[object->work[0]] | 0x570000, 0x299);
    func_8001C258_main(object->model[9], 4, 0);
    object->model[10] = func_8000B108_main(9, 0x99);
    Hu3DModelScaleSet(object->model[10], 0.4f, 0.4f, 0.4f);
    motion = func_80017BB8_main(character, 0);
    func_800E5A00_minigame(object, 0, motion, 1, 0);
    motion = func_80017BB8_main(character, 4);
    func_800E5A00_minigame(object, 6, motion, 1, 19);
    motion = func_80017BB8_main(character, 47);
    func_800E5A00_minigame(object, 13, motion, 1, 999);
    motion = func_80017BB8_main(character, 31);
    func_800E5A00_minigame(object, 21, motion, 1, 999);
    motion = func_80017BB8_main(character, 39);
    func_800E5A00_minigame(object, 38, motion, 1, 0);
    motion = func_80017BB8_main(character, 40);
    func_800E5A00_minigame(object, 39, motion, 1, 99);
    object->trans.x = 0.0f;
    object->trans.y = -56.0f;
    object->trans.z = 100.0f;
    object->rot.y = 180.0f;
    object->scale.x = object->scale.y = object->scale.z = 0.2f;
    Hu3DModelPosSet(object->model[9], 0.0f, 0.0f, 200.0f);
    Hu3DModelRotSet(object->model[9], 0.0f, 180.0f, 0.0f);
    func_8001C258_main(object->model[10], 4, 4);
    func_8010BDE4_motor_rooter(&D_801137C8_motor_rooter[object->work[0]], 38, 1);
    D_800EC280_minigame++;
    data = object->data;
    D_801137C8_motor_rooter[object->work[0]].unk08 = 1;
    D_801137C8_motor_rooter[object->work[0]].controllerPort = data->unk57;
    D_801137C8_motor_rooter[object->work[0]].direction = 0;
    D_801137C8_motor_rooter[object->work[0]].unk14 = 1;
    cameraMask = object->work[0] == 0 ? 1 : 2;
    for (i = 0; i < 11; i++) {
        func_8001C8A8_main(object->model[i], cameraMask);
    }
    m254_SetFunc((u8)object->work[0] + 4, 5, -1, &D_801137C8_motor_rooter[object->work[0]], func_8010ABC4_motor_rooter, 0, 0);
    m254_SetFunc((u8)object->work[0] + 4, 9, -1, &D_801137C8_motor_rooter[object->work[0]], func_8010BCD0_motor_rooter, 0, 0);
    m254_SetFunc((u8)object->work[0] + 4, 4, -1, &D_801137C8_motor_rooter[object->work[0]], func_8010BB78_motor_rooter, 0, 0);
    object->func = func_801070CC_motor_rooter;
}

void func_801070CC_motor_rooter(omObjData *object) {
    m254_UpdateFuncGroup((u8)object->work[0] + 4);
    func_800E4E30_minigame(object);
    if (object->rot.x >= 360.0f) {
        object->rot.x -= 360.0f;
    }
    if (object->rot.x < 0.0f) {
        object->rot.x += 360.0f;
    }
    if (object->rot.y >= 360.0f) {
        object->rot.y -= 360.0f;
    }
    if (object->rot.y < 0.0f) {
        object->rot.y += 360.0f;
    }
    if (object->rot.z >= 360.0f) {
        object->rot.z -= 360.0f;
    }
    if (object->rot.z < 0.0f) {
        object->rot.z += 360.0f;
    }
}

void func_80107210_motor_rooter(omObjData *object) {
    CharacterSprites characters = D_80113634_motor_rooter;
    s16 sprite;
    s16 i;
    f32 y;

    object->work[0] = m254_minigame->runtime.counters.initialization.viewCounters[2];
    object->work[1] = m254_playerId[object->work[0]];
    m254_SetSpriteDispOn(m254_SetSprite(0xFFFF, 0x57, 7, 0, 0), 160, 120);
    for (i = 0; i < 5; i++) {
        sprite = m254_SetSprite(0xFFFF, 0x21, 0x18, 0, 0);
        if (object->work[0] == 0) {
            m254_SetSpriteDispOn(sprite, (s16)(35 + i * 10), 25);
        } else {
            m254_SetSpriteDispOn(sprite, (s16)(285 - i * 10), 25);
        }
    }
    for (i = 0; i < 5; i++) {
        sprite = D_801137C8_motor_rooter[object->work[0]].meterSprites[i] = m254_SetSprite(0xFFF, 0x21, 0x19, 0, 0x1000);
        if (object->work[0] == 0) {
            m254_SetSpriteDispOn(sprite, (s16)(35 + i * 10), 25);
        } else {
            m254_SetSpriteDispOn(sprite, (s16)(285 - (4 - i) * 10), 25);
        }
        if (i == 0) {
            m254_sprites[sprite].unk06 = 255;
        } else {
            m254_sprites[sprite].unk06 = 0;
        }
        HuSprTPLvlSet(m254_sprites[sprite].groupId, 0, (u8)m254_sprites[sprite].unk06);
        D_801137C8_motor_rooter[object->work[0]].unk28[i] = 0;
    }
    D_801137C8_motor_rooter[object->work[0]].progressSprite = sprite = m254_SetSprite(0xFFF, 0x21, characters.fileIds[GwPlayer[m254_playerId[object->work[0]]].chr], 0, 0);
    m254_SetSpriteDispOn(sprite, (s16)(152 + object->work[0] * 16), 220);
    for (i = 0; i < D_801137D2_motor_rooter; i++) {
        y = 220 - (s16)(D_801137C0_motor_rooter[m254_minigame->views[object->work[0]].obstaclePoints[i]].cumDist / m254_minigame->finishDistance * 180.0f);
        sprite = m254_SetSprite(0xEFFF, 0x57, 0x11, 0, 0);
        m254_SetSpriteDispOn(sprite, (s16)(152 + object->work[0] * 16), (s16)y);
    }
    m254_minigame->runtime.counters.initialization.viewCounters[2]++;
    object->func = func_801076AC_motor_rooter;
}

void func_801076AC_motor_rooter(omObjData *object) {
    D_801137C8_motor_rooter_Struct *player = D_801137C8_motor_rooter;
    SpriteData *sprite;
    s16 fading;
    s16 i;
    s16 j;
    s16 y;
    s16 alpha;

    for (i = 0; i < PLAYERS_TOTAL; i++, player++) {
        fading = 0;
        for (j = 0; j < 5; j++) {
            if (player->unk28[j] != 0) {
                fading = 1;
            }
        }
        if (!fading && player->unk14 == 5) {
            if (D_80113468_motor_rooter[i] == 0) {
                for (j = 0; j < 5; j++) {
                    sprite = &m254_sprites[player->meterSprites[j]];
                    HuSprTPLvlSet(sprite->groupId, 0, 0);
                }
                if (++D_8011346C_motor_rooter[i] >= 3) {
                    D_8011346C_motor_rooter[i] = 0;
                    D_80113468_motor_rooter[i] = 1;
                }
            } else {
                for (j = 0; j < 5; j++) {
                    sprite = &m254_sprites[player->meterSprites[j]];
                    HuSprTPLvlSet(sprite->groupId, 0, 255);
                }
                if (++D_8011346C_motor_rooter[i] >= 3) {
                    D_8011346C_motor_rooter[i] = 0;
                    D_80113468_motor_rooter[i] = 0;
                }
            }
        } else {
            for (j = 0; j < 5; j++) {
                sprite = &m254_sprites[player->meterSprites[j]];
                if (player->unk28[j] == 0) {
                    HuSprTPLvlSet(sprite->groupId, 0, (u8)sprite->unk06);
                } else {
                    if (player->unk28[j] == 1) {
                        alpha = sprite->unk06 + 10;
                        sprite->unk06 = alpha;
                        if (alpha >= 255) {
                            alpha = 255;
                            sprite->unk06 = alpha;
                            player->unk28[j] = 0;
                        }
                    } else {
                        alpha = sprite->unk06 - 10;
                        sprite->unk06 = alpha;
                        if (alpha <= 0) {
                            sprite->unk06 = 0;
                            player->unk28[j] = 0;
                        }
                    }
                    HuSprTPLvlSet(sprite->groupId, 0, (u8)sprite->unk06);
                }
            }
        }
        if (!(player->unk08 & 0x40)) {
            y = 220 - (s32)(player->unk0C / m254_minigame->finishDistance * 180.0f);
            m254_SetSpriteDispOn(player->progressSprite, (s16)(152 + i * 16), y);
        }
    }
}

void func_801079E8_motor_rooter(omObjData *object) {
    s16 i;
    s16 cameraMask;
    s16 spriteId;
    HuSprite_Unk84_Struct *sprite;

    object->work[0] = m254_minigame->runtime.counters.initialization.itemViewCount;
    for (i = 0; i < 4; i++) {
        m254_minigame->views[object->work[0]].itemSprites[i] = spriteId = func_8000B838_main(0x570010);
        sprite = func_80055194_main(spriteId);
        object->model[i] = func_8010FC10_motor_rooter(sprite, &D_80113470_motor_rooter);
        Hu3DModelScaleSet(object->model[i], 2.0f, 2.0f, 1.0f);
        func_8001C258_main(object->model[i], 4, 4);
        m254_minigame->views[object->work[0]].itemFrames[i] = 0;
        m254_minigame->views[object->work[0]].itemDelays[i] = rand16() % 11;
        m254_minigame->views[object->work[0]].itemStates[i] = 0;
    }
    m254_minigame->views[object->work[0]].itemTimer = 0;
    m254_minigame->views[object->work[0]].itemSprites[i] = spriteId = func_8000B838_main(0x57000F);
    sprite = func_80055194_main(spriteId);
    object->model[i] = func_8010EFF8_motor_rooter(sprite, 1.0f);
    Hu3DModelScaleSet(object->model[i], 1.5f, 1.5f, 1.0f);
    func_8001C258_main(object->model[i], 4, 4);
    m254_minigame->views[object->work[0]].itemFrames[i] = 0;
    m254_SyncWithModel(object);
    cameraMask = object->work[0] == 0 ? 1 : 2;
    for (i = 0; i < 5; i++) {
        func_8001C8A8_main(object->model[i], cameraMask);
    }
    m254_minigame->runtime.counters.initialization.itemViewCount++;
    object->func = func_80107D50_motor_rooter;
}

void func_80107D50_motor_rooter(omObjData *object) {
    PlayerView *view;
    D_801137C8_motor_rooter_Struct *player;
    s16 camera;
    s16 i;
    s16 j;

    camera = object->work[0];
    view = &m254_minigame->views[camera];
    player = &D_801137C8_motor_rooter[camera];
    i = 0;
    if (player->unk10 == 0.0f) {
        for (i = 0; i < 5; i++) {
            func_8001C258_main(object->model[i], 4, 4);
        }
        return;
    }
    if (player->unk78 & 4) {
        for (i = 0; i < 4; i++) {
            if (view->itemDelays[i] != 99) {
                if (++m254_minigame->runtime.counters.gameplay.playerCounters[camera * 4 + i] > view->itemDelays[i]) {
                    func_8001C258_main(object->model[i], 4, 0);
                    func_8010CB2C_motor_rooter(object, 4, i);
                    func_801108CC_motor_rooter(object->model[i], func_80055194_main(view->itemSprites[i]),
                                               view->itemFrames[i], &D_80113470_motor_rooter);
                    if (++view->itemFrames[i] >= 15) {
                        if (view->itemStates[i] == 0) {
                            view->itemStates[i] = 1;
                            view->itemFrames[i] = 0;
                        } else {
                            func_8001C258_main(object->model[i], 4, 4);
                            m254_minigame->runtime.counters.gameplay.playerCounters[camera * 4 + i] = 0;
                            view->itemDelays[i] = 99;
                            view->itemFrames[i] = 0;
                            if (++view->itemTimer >= 4) {
                                for (j = 0; j < 4; j++) {
                                    view->itemStates[j] = 0;
                                    view->itemDelays[j] = rand16() % 11;
                                }
                                player->unk78 &= ~4;
                            }
                        }
                    }
                }
            }
        }
    } else if (player->unk78 & 1) {
        func_8001C258_main(object->model[0], 4, 0);
        func_8010CB2C_motor_rooter(object, 1, 0);
        func_801108CC_motor_rooter(object->model[0], func_80055194_main(view->itemSprites[0]),
                                   view->itemFrames[0], &D_80113470_motor_rooter);
        if (++view->itemFrames[0] >= 15) {
            func_8001C258_main(object->model[0], 4, 4);
            player->unk78 &= ~1;
            view->itemFrames[0] = 0;
        }
    }
    if (player->unk78 & 2) {
        func_8001C258_main(object->model[4], 4, 0);
        func_8010CB2C_motor_rooter(object, 2, 4);
        func_801107FC_motor_rooter(object->model[4], func_80055194_main(view->itemSprites[4]), view->itemFrames[4]);
        if (++m254_minigame->runtime.counters.gameplay.impactFrameCounters[object->work[0]] >= 2) {
            m254_minigame->runtime.counters.gameplay.impactFrameCounters[object->work[0]] = 0;
            if (++view->itemFrames[4] >= 5) {
                func_8001C258_main(object->model[4], 4, 4);
                player->unk78 &= ~2;
                view->itemFrames[4] = 0;
            }
        }
    }
    m254_SyncWithModel(object);
}

void m254_InitCamera(FuncContext *ctx) {
    s16 i;

    for (i = 0; i < 2; i++) {
        CZoomM[i] = 100.0f;
        CenterM[i].x = D_801137C0_motor_rooter[0].x;
        CenterM[i].y = D_801137C0_motor_rooter[0].y;
        CenterM[i].z = D_801137C0_motor_rooter[0].z;
        CRotM[i].x = D_801137C0_motor_rooter[0].pitch - 180.0f;
        CRotM[i].y = D_801137C0_motor_rooter[0].yaw;
        CRotM[i].z = D_801137C0_motor_rooter[0].unk14;
    }
    m254_ResetFunc(FGRP_CAMERA, ctx);
    m254_SetFunc(FGRP_CAMERA, 0, -1, NULL, func_801082E0_motor_rooter, 0, FALSE);
}

void func_801082E0_motor_rooter(FuncContext *ctx) {
    PlayerView *view;
    D_801137C8_motor_rooter_Struct *var_s1;
    PathPosition position;
    s16 temp_v0;
    s16 i;

    view = m254_minigame->views;
    var_s1 = D_801137C8_motor_rooter;
    for (i = 0; i < 2; i++, var_s1++, view++) {
        if (var_s1->unk08 & 0x80) {
            continue;
        }
        temp_v0 = func_8010D03C_motor_rooter(var_s1->unk0C);
        position = func_8010D0AC_motor_rooter(temp_v0, var_s1->unk0C);
        CenterM[i].x = position.x;
        CenterM[i].y = position.y;
        CenterM[i].z = position.z;
        CRotM[i].x = position.pitch - 180.0f;
        CRotM[i].y = position.yaw;
        CRotM[i].z = position.roll;
        if (CRotM[i].x > 360.0f) {
            CRotM[i].x -= 360.0f;
        } else if (CRotM[i].x < 0.0f) {
            CRotM[i].x += 360.0f;
        }
        if (CRotM[i].y > 360.0f) {
            CRotM[i].y -= 360.0f;
        } else if (CRotM[i].y < 0.0f) {
            CRotM[i].y += 360.0f;
        }
        var_s1->unk1C = temp_v0 + 1;
        view->unk8A = temp_v0;
    }
}

void func_80108514_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;
    s16 camera = object->work[0];
    PathPosition position;
    f32 t;
    s32 fileId;

    if (ctx->state == 0) {
        position = func_8010D0AC_motor_rooter(func_8010D03C_motor_rooter(player->unk0C + D_80113658_motor_rooter),
                                              player->unk0C + D_80113658_motor_rooter);
        ctx->work.f32[0] = position.x;
        ctx->work.f32[1] = position.y - 30.0;
        ctx->work.f32[2] = position.z;
        player->cameraStart.x = CenterM[camera].x;
        player->cameraStart.y = CenterM[camera].y;
        player->cameraStart.z = CenterM[camera].z;
        ctx->work.s8[0] = ctx->work.s8[1] = ctx->work.s8[2] = 0;
        ctx->state = 1;
    }
    t = ctx->work.s8[0] / 30.0f;
    t = sindf(t * 90.0f);
    t = t > 1.0f ? 1.0f : t;
    CenterM[camera].x = (ctx->work.f32[0] - player->cameraStart.x) * t + player->cameraStart.x;
    CenterM[camera].y = (ctx->work.f32[1] - player->cameraStart.y) * t + player->cameraStart.y;
    CenterM[camera].z = (ctx->work.f32[2] - player->cameraStart.z) * t + player->cameraStart.z;
    if (++ctx->work.s8[0] >= 31) {
        fileId = D_80113474_motor_rooter[GwPlayer[m254_playerId[object->work[0]]].chr];
        func_80017790_main(object->model[0], 2, GwPlayer[m254_playerId[object->work[0]]].chr, fileId);
        func_8010BDE4_motor_rooter(player, 0xD, 1);
        m254_ResetFunc(FGRP_CAMERA, ctx);
        m254_SetFunc(1, 0, -1, player, func_80108E6C_motor_rooter, 0, FALSE);
    }
}

void func_801087C0_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = D_801137C8_motor_rooter;
    s16 count = 0;
    s16 finishers[2];
    s16 i;
    s32 loser;
    D_801137C8_motor_rooter_Struct *winnerPlayer;
    D_801137C8_motor_rooter_Struct *loserPlayer;

    finishers[0] = -1;
    finishers[1] = -1;
    for (i = 0; i < PLAYERS_TOTAL; i++, player++) {
        if (!(player->unk08 & 0x40) && player->unk1C == D_801137CC_motor_rooter) {
            finishers[count] = i;
            count++;
        }
    }
    if (count != 0) {
        if (count == 2) {
            i = rand16() % 2;
        } else {
            i = finishers[0];
        }
        D_801137C8_motor_rooter[i].unk08 |= 0x50;
        loser = !i;
        D_801137C8_motor_rooter[loser].unk08 |= 0x41;
        HuAudSeqFadeOut(120);
        GMesCreate(0x11);
        func_8003F5C0_main();
        m254_minigame->runtime.unk20 = 99.0f;
        winnerPlayer = &D_801137C8_motor_rooter[i];
        m254_SetFunc((u8)winnerPlayer->unk00->work[0] + 4, 5, -1, winnerPlayer, func_8010C084_motor_rooter, 0, 0);
        loserPlayer = &D_801137C8_motor_rooter[loser];
        m254_SetFunc((u8)loserPlayer->unk00->work[0] + 4, 5, -1, loserPlayer, func_8010C824_motor_rooter, 0, 0);
        m254_ResetFunc(1, ctx);
    }
}

void func_801089B8_motor_rooter(FuncContext *ctx) {
    s16 i;
    f32 fps;

    switch (ctx->state) {
        case 0:
            m254_minigame->timer = 1800.0f;
            fps = 30.0f;
            GMesCreate(0x1A, 60.0, 160, 28);
            func_8003F578_main((m254_minigame->timer + 29.0f) / fps);
            ctx->state = 1;
            break;
        case 1:
            if (m254_minigame->runtime.unk20 == 99.0f) {
                break;
            }
            m254_minigame->timer -= 1.0f;
            func_8003F578_main((m254_minigame->timer + 29.0f) * (1.0f / 30.0f));
            if (m254_minigame->timer < 0.0f) {
                func_8003F5C0_main();
                m254_ResetFunc(1, ctx);
                m254_SetFunc(1, 0, -1, NULL, func_80108FDC_motor_rooter, 0, FALSE);
                for (i = 0; i < 2; i++) {
                    D_801137C8_motor_rooter[i].unk08 |= 0x41;
                    m254_SetFunc((u8)D_801137C8_motor_rooter[i].unk00->work[0] + 4, 5, -1,
                                 &D_801137C8_motor_rooter[i], func_8010C824_motor_rooter, 0, FALSE);
                }
            }
            break;
    }
}

void func_80108BF0_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player;
    s16 i;

    player = D_801137C8_motor_rooter;
    if (ctx->state == 0) {
        ctx->work.s16[0] = 0;
        ctx->state = 1;
    }
    switch (++ctx->work.s16[0]) {
        case 10:
            for (i = 0; i < 2; i++, player++) {
                m254_SetFunc(i + 4, 0, -1, player, func_8010BDF0_motor_rooter, 0, FALSE);
            }
            break;
        case 110:
            GMesCreate(6);
            HuAudFXPlay(14);
            HuAudSeqPlay(0x37);
            break;
        case 130:
            D_80113494_motor_rooter = 1;
            break;
        default:
            if (D_80113494_motor_rooter && GMesStatGet() == 2) {
                m254_SetFunc(1, 0, -1, NULL, func_801089B8_motor_rooter, 0, FALSE);
                for (i = 0; i < 2; i++, player++) {
                    player->unk08 = (player->unk08 & ~1) | 0x120;
                    player->unk10 = 1.0f;
                    player->unk4C = 0;
                    if (GwPlayer[m254_playerId[i]].stat & PLAYER_IS_CPU) {
                        player->isCpu = TRUE;
                        m254_SetFunc(i + 4, 0, -1, player, func_8010A440_motor_rooter, 0, FALSE);
                    } else {
                        player->isCpu = FALSE;
                    }
                }
                m254_ResetFunc(1, ctx);
                m254_SetFunc(1, 1, -1, NULL, func_801087C0_motor_rooter, 0, FALSE);
            }
            break;
    }
}

void func_80108E6C_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;
    s16 timer;

    if (D_80113496_motor_rooter >= 2) {
        if (GMesStatGet() == 0) {
            D_80113496_motor_rooter = 3;
        }
        if (D_80113496_motor_rooter == 3) {
            if (++ctx->work.s16[0] >= 15) {
                m254_ResetFunc(1, ctx);
                m254_SetFunc(1, 0, -1, NULL, func_80109134_motor_rooter, 0, TRUE);
            }
        }
    } else {
        timer = ctx->work.s16[0]++;
        if (timer == 0) {
            HuAudSeqPlay(0x67);
            GMesCreate(0x16, GwPlayer[m254_playerId[object->work[0]]].chr);
            GwPlayer[m254_playerId[object->work[0]]].bonusCoin += 10;
        }
        if (GMesStatGet() != 0) {
            ctx->work.s16[0] = 0;
            D_80113496_motor_rooter = 2;
        }
    }
}

void func_80108FDC_motor_rooter(FuncContext *ctx) {
    s16 timer;

    if (D_80113498_motor_rooter >= 2) {
        if (GMesStatGet() == 0) {
            D_80113498_motor_rooter = 3;
        }
        if (D_80113498_motor_rooter == 3) {
            if (++ctx->work.s16[0] >= 15) {
                m254_ResetFunc(1, ctx);
                m254_SetFunc(1, 0, -1, NULL, func_80109134_motor_rooter, 0, TRUE);
            }
        }
    } else if (D_80113498_motor_rooter == 1) {
        timer = ctx->work.s16[0]++;
        if (timer == 15) {
            GMesCreate(0x20);
            HuAudSeqPlay(0x6C);
        }
        if (GMesStatGet() != 0) {
            ctx->work.s16[0] = 0;
            D_80113498_motor_rooter = 2;
        }
    } else {
        timer = ctx->work.s16[0]++;
        if (timer == 0) {
            HuAudSeqFadeOut(120);
            GMesCreate(0x11);
        } else if (GMesStatGet() == 0) {
            ctx->work.s16[0] = 0;
            D_80113498_motor_rooter = 1;
        }
    }
}

void func_80109134_motor_rooter(FuncContext *ctx) {
    switch (ctx->state) {
        case 0:
            WipeCreateOut(0, 20);
            ctx->state = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                omOvlReturnEx(1);
            }
            break;
    }
}

void func_801091A0_motor_rooter(FuncContext *ctx) {
    PlayerView *view = ctx->data;
    omObjData *object = view->unk00;
    s16 direction = 0;
    f32 rotX[16];
    f32 rotY[16];
    f32 transform[16];
    Vec offset;
    f32 position[3];
    s16 directions0[] = { 0, 1, 2, 3, -1, -2, -3 };
    s16 directions2[] = { 0, 1, 99, 2, -1, -2, -3 };
    s16 directions3[] = { 0, 1, 2, 3, -1, 99, -2 };
    s16 directions1[] = { 0, 1, 99, 2, -1, 99, -2 };
    s16 i;
    s16 obstacle;
    HmfModel *model;
    PathPoint *point;
    f32 angle;
    f32 pitch;

    obstacle = view->obstacleSlots[ctx->work.s16[0]];
    for (i = 0; i < 7; i++) {
        model = &HmfModelData[object->model[ctx->work.s16[0] * 7 + i]];
        switch (view->obstacleTypes[obstacle]) {
            case 0:
                direction = view->obstacleDirections[obstacle] + directions0[i];
                break;
            case 1:
                direction = view->obstacleDirections[obstacle] + directions1[i];
                break;
            case 2:
                direction = view->obstacleDirections[obstacle] + directions2[i];
                break;
            case 3:
                direction = view->obstacleDirections[obstacle] + directions3[i];
                break;
        }
        if (direction >= 51) {
            Hu3DModelPosSet(object->model[ctx->work.s16[0] * 7 + i], 0.0f, 200.0f, 0.0f);
            func_8001C258_main(object->model[ctx->work.s16[0] * 7 + i], 4, 4);
            continue;
        }
        if (direction >= 8) {
            direction -= 8;
        }
        if (direction < 0) {
            direction += 8;
        }
        angle = direction * 45.0f;
        offset.x = sindf(angle) * 55.9999990463256836;
        offset.y = -cosdf(angle) * 55.9999990463256836;
        offset.z = 0.0f;
        point = &D_801137C0_motor_rooter[view->obstaclePoints[obstacle]];
        pitch = point->pitch - 180.0f;
        m254_MakeRotXMtx(rotX, pitch);
        m254_MakeRotYMtx(rotY, point->yaw);
        m254_MultiplyMtx(rotX, rotY, transform);
        func_801114B0_motor_rooter(transform, &offset, position);
        model->pos.x = point->x + position[0];
        model->pos.y = point->y + position[1];
        model->pos.z = point->z + position[2];
        model->rot.x = pitch;
        model->rot.y = point->yaw;
        m254_MakeIdentityMtx(model->mtx[0]);
        func_80017D24_main(model->mtx[0], 0.0f, 0.0f, angle);
    }
}

void func_8010961C_motor_rooter(FuncContext *ctx) {
    PlayerView *view;
    omObjData *object;
    s16 i;
    s16 j;

    view = ctx->data;
    object = view->unk00;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 7; j++) {
            func_801107FC_motor_rooter(object->model[i * 7 + j],
                                       func_80055194_main(view->obstacleSprites[i * 7 + j]),
                                       view->obstacleFrames[i]);
        }
        view->obstacleFrames[i] = view->obstacleFrames[i] + 1 < 5 ? view->obstacleFrames[i] + 1 : 0;
    }
}

void func_8010972C_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player;
    PlayerView *view;
    omObjData *object;
    s16 distance;
    s16 slot;
    s16 obstacle;
    s16 i;

    player = &D_801137C8_motor_rooter[ctx->tag];
    view = ctx->data;
    object = view->unk00;
    distance = 9999;
    for (slot = 0; slot < 3; slot++) {
        obstacle = view->obstacleSlots[slot];
        if (obstacle == -1) {
            continue;
        }
        if (view->obstaclePoints[obstacle] - player->unk1C < m254_minigame->unk0E) {
            for (i = slot * 7; i < slot * 7 + 7; i++) {
                func_8001C258_main(object->model[i], 4, 0);
            }
        } else {
            for (i = slot * 7; i < slot * 7 + 7; i++) {
                func_8001C258_main(object->model[i], 4, 4);
            }
        }
        if (distance > view->obstaclePoints[obstacle] - player->unk1C) {
            distance = view->obstaclePoints[obstacle] - player->unk1C;
        }
        ctx->work.s16[0] = slot;
        if (!(player->unk08 & 0x42) && player->unk1C == view->obstaclePoints[obstacle] &&
            player->direction != view->obstacleSafeDirections[slot][0] &&
            player->direction != view->obstacleSafeDirections[slot][1] &&
            player->direction != view->obstacleSafeDirections[slot][2]) {
            for (i = 0; i < 3; i++) {
                if (player->unk14 - 1 > 0) {
                    player->unk14--;
                    player->unk28[player->unk14] = 2;
                    player->unk10 -= 4.0f;
                }
            }
            func_8004AC98_main(0x4B0, player->unk00->work[0]);
            HuAudFXPitchSet(D_801137D8_motor_rooter, D_8011345A_motor_rooter[player->unk14]);
            player->unk08 |= 2;
            player->unk78 |= 2;
            func_8010BDE4_motor_rooter(player, 0x27, 1);
            if (!player->isCpu) {
                omVibrate(m254_playerId[ctx->tag], 2, 2, 20);
            }
        }
        if (view->unk8A > view->obstaclePoints[obstacle] + 2) {
            view->obstacleSlots[slot] = view->nextObstacleSlot++;
            if (view->nextObstacleSlot > D_801137D2_motor_rooter) {
                for (i = slot * 7; i < slot * 7 + 7; i++) {
                    func_8001C258_main(object->model[i], 4, 4);
                }
                view->obstacleSlots[slot] = -1;
            } else {
                for (i = slot * 7; i < slot * 7 + 7; i++) {
                    func_8001C258_main(object->model[i], 4, 4);
                }
                func_80109C94_motor_rooter(view, slot);
                func_801091A0_motor_rooter(ctx);
            }
        }
    }
    if (!player->obstacleSoundStarted) {
        player->obstacleSoundStarted = 1;
        player->obstacleSound = func_8004AC5C_main(0x4B2, ctx->tag);
        func_8004AAD0_main(player->obstacleSound, 0);
    }
    distance += 3;
    if (distance < 26) {
        distance = distance < 0 ? 0 : distance;
        func_8004AAD0_main(player->obstacleSound, 127 - distance * 3);
    } else {
        func_8004AAD0_main(player->obstacleSound, 0);
    }
}

void func_80109C94_motor_rooter(PlayerView *view, s16 slot) {
    s16 i;

    switch (view->obstacleTypes[view->obstacleSlots[slot]]) {
        case 0:
            view->obstacleSafeDirections[slot][0] = view->obstacleSafeDirections[slot][1] =
                view->obstacleSafeDirections[slot][2] = view->obstacleDirections[view->obstacleSlots[slot]] + 4;
            break;
        case 1:
            view->obstacleSafeDirections[slot][0] = view->obstacleDirections[view->obstacleSlots[slot]] + 4;
            view->obstacleSafeDirections[slot][1] = view->obstacleDirections[view->obstacleSlots[slot]] + 5;
            view->obstacleSafeDirections[slot][2] = view->obstacleDirections[view->obstacleSlots[slot]] + 3;
            break;
        case 2:
            view->obstacleSafeDirections[slot][0] = view->obstacleDirections[view->obstacleSlots[slot]] + 4;
            view->obstacleSafeDirections[slot][1] = view->obstacleDirections[view->obstacleSlots[slot]] + 4;
            view->obstacleSafeDirections[slot][2] = view->obstacleDirections[view->obstacleSlots[slot]] + 3;
            break;
        case 3:
            view->obstacleSafeDirections[slot][0] = view->obstacleDirections[view->obstacleSlots[slot]] + 4;
            view->obstacleSafeDirections[slot][1] = view->obstacleDirections[view->obstacleSlots[slot]] + 4;
            view->obstacleSafeDirections[slot][2] = view->obstacleDirections[view->obstacleSlots[slot]] + 5;
            break;
    }
    for (i = 0; i < 3; i++) {
        if (view->obstacleSafeDirections[slot][i] >= 8) {
            view->obstacleSafeDirections[slot][i] -= 8;
        }
        if (view->obstacleSafeDirections[slot][i] < 0) {
            view->obstacleSafeDirections[slot][i] += 8;
        }
    }
}

void func_80109EFC_motor_rooter(FuncContext *ctx) {
    omObjData *object = ctx->data;
    PlayerView *view = &m254_minigame->views[object->work[0]];
    f32 rotX[16];
    f32 rotY[16];
    f32 transform[16];
    Vec offset;
    f32 position[3];
    HmfModel *model;
    PathPoint *point;
    f32 angle;
    s16 slot = ctx->work.s16[0];
    f32 pitch;

    model = &HmfModelData[object->model[slot]];
    angle = m254_minigame->itemDirections[view->itemSlots[slot]] * 45.0f;
    offset.x = sindf(angle) * 64.0000009536743164;
    offset.y = -cosdf(angle) * 64.0000009536743164;
    offset.z = -30.0f;
    point = &D_801137C0_motor_rooter[m254_minigame->itemPoints[view->itemSlots[slot]]];
    pitch = point->pitch - 180.0f;
    m254_MakeRotXMtx(rotX, pitch);
    m254_MakeRotYMtx(rotY, point->yaw);
    m254_MultiplyMtx(rotX, rotY, transform);
    func_801114B0_motor_rooter(transform, &offset, position);
    model->pos.x = D_801137C0_motor_rooter[m254_minigame->itemPoints[view->itemSlots[slot]]].x + position[0];
    model->pos.y = D_801137C0_motor_rooter[m254_minigame->itemPoints[view->itemSlots[slot]]].y + position[1];
    model->pos.z = D_801137C0_motor_rooter[m254_minigame->itemPoints[view->itemSlots[slot]]].z + position[2];
    model->rot.x = pitch;
    model->rot.y = point->yaw;
    m254_MakeIdentityMtx(model->mtx[0]);
    func_80017D24_main(model->mtx[0], 0.0f, 0.0f, angle);
}

void func_8010A174_motor_rooter(FuncContext *ctx) {
    omObjData *object;
    PlayerView *view;
    D_801137C8_motor_rooter_Struct *player;
    s16 slot;

    object = ctx->data;
    view = &m254_minigame->views[object->work[0]];
    player = &D_801137C8_motor_rooter[object->work[0]];
    if (ctx->work.s16[1] != player->unk1C) {
        for (slot = 0; slot < 15; slot++) {

            if (view->itemSlots[slot] >= D_801137D0_motor_rooter) {
                func_8001C258_main(object->model[slot], 4, 4);
                continue;
            }
            ctx->work.s16[0] = slot;
            func_80109EFC_motor_rooter(ctx);
            if (player->unk1C == m254_minigame->itemPoints[view->itemSlots[slot]] &&
                player->direction == m254_minigame->itemDirections[view->itemSlots[slot]]) {
                if (player->unk14 + 1 < 6) {
                    if (player->unk48 > 90) {
                        player->unk48 = 180 - player->unk48;
                    }
                    player->unk4C = 0;
                    player->unk28[player->unk14++] = 1;
                    player->unk10 += 4.0f;
                    player->unk08 |= 0x20;
                    player->unk78 |= 1;
                    ctx->work.s16[1] = player->unk1C;
                    HuAudFXPitchSet(D_801137D8_motor_rooter, D_8011345A_motor_rooter[player->unk14]);
                    func_8004AC5C_main(0x4B1, player->unk00->work[0]);
                    if (!player->isCpu) {
                        omVibrate(m254_playerId[object->work[0]], 10, 0, 10);
                    }
                } else {
                    if (player->unk48 > 90) {
                        player->unk48 = 180 - player->unk48;
                    }
                    player->unk08 |= 0x20;
                    player->unk78 |= 1;
                    ctx->work.s16[1] = player->unk1C;
                    player->unk4C = 0;
                    func_8004AC5C_main(0x4B1, player->unk00->work[0]);
                    if (!player->isCpu) {
                        omVibrate(m254_playerId[object->work[0]], 10, 0, 10);
                    }
                }
            }
            if (view->unk8A > m254_minigame->itemPoints[view->itemSlots[slot]]) {
                view->itemSlots[slot] = view->nextItemSlot++;
            }
        }
    }
}

#ifdef NON_MATCHING
// The body matches, but GCC allocates a 0x60 stack frame instead of 0xC0.
void func_8010A440_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;
    PlayerView *view = &m254_minigame->views[object->work[0]];
    s16 selected = 0;
    s16 obstacleClosest;
    s16 itemClosest;
    s16 obstacleI;
    s16 itemI;
    s16 obstaclePoint;
    s16 itemPoint;
    s16 slot;
    s16 obstacleDirection;
    s16 itemDirection;
    s16 obstacleTargetDirection;
    s16 itemTargetDirection;
    s16 obstacleDifference;
    s16 itemDifference;

    if (!ctx->state) {
        switch (GwPlayer[m254_playerId[object->work[0]]].cpu_difficulty) {
            case 0:
                ctx->work.s8[2] = 8;
                ctx->work.s8[3] = 7;
                ctx->work.s8[4] = 5;
                ctx->work.s8[5] = 3;
                ctx->work.s8[6] = 1;
                ctx->work.s8[7] = 1;
                break;
            case 1:
                ctx->work.s8[2] = 6;
                ctx->work.s8[3] = 5;
                ctx->work.s8[4] = 4;
                ctx->work.s8[5] = 4;
                ctx->work.s8[6] = 3;
                ctx->work.s8[7] = 3;
                break;
            case 2:
                ctx->work.s8[2] = 4;
                ctx->work.s8[3] = 3;
                ctx->work.s8[4] = 3;
                ctx->work.s8[5] = 5;
                ctx->work.s8[6] = 6;
                ctx->work.s8[7] = 6;
                break;
            case 3:
                ctx->work.s8[2] = 2;
                ctx->work.s8[3] = 1;
                ctx->work.s8[4] = 2;
                ctx->work.s8[5] = 6;
                ctx->work.s8[6] = 8;
                ctx->work.s8[7] = 10;
                break;
        }
        ctx->work.s16[1] = 8;
        ctx->state = 1;
    }
    D_800CBB6E_main[player->controllerPort] = 0;
    D_800D20A1_main[player->controllerPort] = 0;
    D_800CDA7C_main[player->controllerPort] = 0;
    obstacleClosest = 999;
    for (obstacleI = 0; obstacleI < 3; obstacleI++) {
        if (view->obstacleSlots[obstacleI] != -1) {
            obstaclePoint = view->obstaclePoints[view->obstacleSlots[obstacleI]];
            if (player->unk1C <= obstaclePoint) {
                if (obstaclePoint < obstacleClosest) {
                    obstacleClosest = obstaclePoint;
                    selected = obstacleI;
                }
            }
        }
    }
    if (obstacleClosest != 999 && player->unk1C + ctx->work.s16[1] > view->obstaclePoints[view->obstacleSlots[selected]]) {
        obstacleDirection = player->direction;
        obstacleTargetDirection = view->obstacleSafeDirections[selected][0];
        if (obstacleDirection != obstacleTargetDirection) {
            obstacleDifference = obstacleTargetDirection - obstacleDirection;
            if (obstacleDifference < 0) {
                obstacleDifference += 7;
            }
            if (ctx->work.s8[0] > ctx->work.s8[2]) {
                ctx->work.s8[0] = 0;
                switch (D_80113458_motor_rooter) {
                    case 0:
                    case 1:
                        if (obstacleDifference < 3) {
                            D_800CBB6E_main[player->controllerPort] = 50;
                        } else {
                            if (obstacleDifference < 4) {
                                (void)rand16();
                            }
                            D_800CBB6E_main[player->controllerPort] = -50;
                        }
                        break;
                    case 2:
                        if (obstacleDifference < 3) {
                            ((u16 *)D_800CDA7C_main)[player->controllerPort] = 0x8000;
                        } else {
                            if (obstacleDifference < 4) {
                                (void)rand16();
                            }
                            ((u16 *)D_800CDA7C_main)[player->controllerPort] = 0x4000;
                        }
                        break;
                }
            } else {
                ctx->work.s8[0]++;
            }
        } else {
            ctx->work.s16[1] = 8 - rand16() % (ctx->work.s8[3] + 1);
        }
    } else {
        ctx->work.s8[0] = 0;
        if (rand16() % (ctx->work.s8[7] + 1)) {
            itemClosest = 999;
            for (itemI = 0; itemI < 15; itemI++) {
                slot = view->itemSlots[itemI];
                itemPoint = m254_minigame->itemPoints[slot];
                if (player->unk1C < itemPoint) {
                    if (itemPoint < itemClosest) {
                        itemClosest = itemPoint;
                        selected = slot;
                    }
                }
            }
            if (itemClosest != 999 && player->unk1C + ctx->work.s8[5] > m254_minigame->itemPoints[selected]) {
                itemDirection = player->direction;
                itemTargetDirection = m254_minigame->itemDirections[selected];
                if (itemDirection != itemTargetDirection) {
                    itemDifference = itemTargetDirection - itemDirection;
                    if (itemDifference < 0) {
                        itemDifference += 7;
                    }
                    if (ctx->work.s8[1] > ctx->work.s8[4]) {
                        ctx->work.s8[1] = 0;
                        switch (D_80113458_motor_rooter) {
                            case 0:
                            case 1:
                                if (itemDifference < 3) {
                                    D_800CBB6E_main[player->controllerPort] = 50;
                                } else {
                                    if (itemDifference < 4) {
                                        (void)rand16();
                                    }
                                    D_800CBB6E_main[player->controllerPort] = -50;
                                }
                                if (!(rand16() % (ctx->work.s8[6] + 1))) {
                                    D_800CBB6E_main[player->controllerPort] *= -1;
                                }
                                break;
                            case 2:
                                if (itemDifference < 3) {
                                    ((u16 *)D_800CDA7C_main)[player->controllerPort] = 0x8000;
                                } else {
                                    if (itemDifference < 4) {
                                        (void)rand16();
                                    }
                                    ((u16 *)D_800CDA7C_main)[player->controllerPort] = 0x4000;
                                }
                                if (!(rand16() % (ctx->work.s8[6] + 1))) {
                                    D_800CDA7C_main[player->controllerPort] = ~D_800CDA7C_main[player->controllerPort];
                                    D_800CDA7C_main[player->controllerPort] &= 0xC000;
                                }
                                break;
                        }
                    } else {
                        ctx->work.s8[1]++;
                    }
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010A440_motor_rooter);
#endif

void func_8010ABC4_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;

    if (player->unk08 & 0x13) {
        return;
    }
    switch (D_80113458_motor_rooter) {
        case 0:
        case 1:
            if (D_800CBB6E_main[player->controllerPort] > 10) {
                if (!ctx->work.s8[0]) {
                    if (D_80113458_motor_rooter == 0) {
                        ctx->work.s8[0] = 1;
                    }
                    ctx->work.s8[1] = 0;
                    if (!(player->unk08 & 0xC)) {
                        player->unk08 |= 4;
                        m254_SetFunc((u8)object->work[0] + 4, 4, -1, player, func_8010B970_motor_rooter, 0, 0);
                    } else {
                        ctx->work.s8[2] = 4;
                    }
                }
            } else if (D_800CBB6E_main[player->controllerPort] < -10) {
                if (!ctx->work.s8[1]) {
                    ctx->work.s8[0] = 0;
                    if (D_80113458_motor_rooter == 0) {
                        ctx->work.s8[1] = 1;
                    }
                    if (!(player->unk08 & 0xC)) {
                        player->unk08 |= 8;
                        m254_SetFunc((u8)object->work[0] + 4, 4, -1, player, func_8010B970_motor_rooter, 0, 1);
                    } else {
                        ctx->work.s8[2] = 8;
                    }
                }
            } else {
                ctx->work.s8[0] = ctx->work.s8[1] = 0;
            }
            break;
        case 2:
            if ((u16)D_800CDA7C_main[player->controllerPort] & 0x8000) {
                if (!ctx->work.s8[0]) {
                    ctx->work.s8[0] = 1;
                    ctx->work.s8[1] = 0;
                    if (!(player->unk08 & 0xC)) {
                        player->unk08 |= 4;
                        m254_SetFunc((u8)object->work[0] + 4, 4, -1, player, func_8010B970_motor_rooter, 0, 0);
                    } else {
                        ctx->work.s8[2] = 4;
                    }
                }
            } else if (D_800CDA7C_main[player->controllerPort] & 0x4000) {
                if (!ctx->work.s8[1]) {
                    ctx->work.s8[0] = 0;
                    ctx->work.s8[1] = 1;
                    if (!(player->unk08 & 0xC)) {
                        player->unk08 |= 8;
                        m254_SetFunc((u8)object->work[0] + 4, 4, -1, player, func_8010B970_motor_rooter, 0, 1);
                    } else {
                        ctx->work.s8[2] = 8;
                    }
                }
            } else {
                ctx->work.s8[0] = ctx->work.s8[1] = 0;
            }
            break;
    }
    if (D_80113458_motor_rooter != 1 && !(GwPlayer[m254_playerId[object->work[0]]].stat & PLAYER_IS_CPU) &&
        !(player->unk08 & 0xC)) {
        switch (ctx->work.s8[2]) {
            case 4:
                player->unk08 |= 4;
                m254_SetFunc((u8)object->work[0] + 4, 4, -1, player, func_8010B970_motor_rooter, 0, 0);
                break;
            case 8:
                player->unk08 |= 8;
                m254_SetFunc((u8)object->work[0] + 4, 4, -1, player, func_8010B970_motor_rooter, 0, 1);
                break;
        }
        ctx->work.s8[2] = 0;
    }
}

void func_8010AF0C_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;
    f32 bounce = 0.0f;
    s16 camera = object->work[0];
    f32 rotX[16];
    f32 rotY[16];
    f32 transform[16];
    Vec offset;
    f32 position[3];
    f32 angle;

    if (player->unk08 & 0x80) {
        m254_ResetFunc((u8)object->work[0] + 4, ctx);
        return;
    }
    if (player->unk08 == 0) {
        ctx->work.s16[1] = 1;
        ctx->state = 1;
    }
    player->unk0C += player->unk10;
    ctx->work.s16[0] = ctx->work.s16[0] + 2 < 361 ? ctx->work.s16[0] + 2 : 0;
    ctx->work.f32[0] = sindf(ctx->work.s16[0]) * 20.0 * 0.05;
    if (player->unk08 & 2) {
        f32 jitter = D_8011349C_motor_rooter[ctx->work.s8[0]];
        angle = jitter + player->turnAngle;
        ctx->work.s8[0]++;
        if (ctx->work.s8[0] >= 4) {
            func_8010BDE4_motor_rooter(player, 38, 0);
            ctx->work.s8[0] = 0;
            player->unk08 &= ~2;
        }
    } else {
        angle = player->turnAngle;
    }
    if (player->unk08 & 0x20) {
        bounce = sindf(player->unk48) * 30.0;
        player->unk48 += 10;
        if (player->unk48 >= 181) {
            player->unk48 = 0;
            player->unk08 &= ~0x20;
        }
    }
    player->motion.x = ctx->work.f32[0];
    player->motion.y = angle;
    player->motion.z = bounce;
    player->motionCopy.x = ctx->work.f32[0];
    player->motionCopy.y = angle;
    player->motionCopy.z = bounce;
    offset.x = sindf(angle) * (ctx->work.f32[0] + 55.9999990463256836);
    offset.y = -cosdf(angle) * (ctx->work.f32[0] + 55.9999990463256836);
    offset.z = -120.0 - bounce;
    m254_MakeRotXMtx(rotX, CRotM[camera].x);
    m254_MakeRotYMtx(rotY, CRotM[camera].y);
    m254_MultiplyMtx(rotX, rotY, transform);
    func_801114B0_motor_rooter(transform, &offset, position);
    object->trans.x = CenterM[camera].x + position[0];
    object->trans.y = CenterM[camera].y + position[1];
    object->trans.z = CenterM[camera].z + position[2];
    if (player->unk08 & 0x400) {
        object->rot.x = CRotM[camera].x;
        m254_MakeIdentityMtx(HmfModelData[object->model[0]].mtx[0]);
        func_80017D24_main(HmfModelData[object->model[0]].mtx[0], 0.0f, player->unk74, 0.0f);
        object->rot.y = 0.0f;
    } else {
        object->rot.x = 360.0f - CRotM[camera].x;
        if (!(player->unk08 & 1)) {
            object->rot.y = CRotM[camera].y + 180.0f;
        }
        m254_MakeIdentityMtx(HmfModelData[object->model[0]].mtx[0]);
        func_80017D24_main(HmfModelData[object->model[0]].mtx[0], 0.0f, 0.0f, 360.0f - angle);
    }
}

void func_8010B394_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;
    HmfModel *model = &HmfModelData[object->model[9]];
    s16 camera = object->work[0];
    f32 rotX[16];
    f32 rotY[16];
    f32 transform[16];
    Vec offset;
    f32 position[3];
    f32 angle;
    f32 bounce;

    if (player->unk08 & 0x80) {
        m254_ResetFunc((u8)object->work[0] + 4, ctx);
        return;
    }
    if (!(player->unk08 & 0x200)) {
        offset.x = sindf(player->motionCopy.y) * (player->motionCopy.x + 55.9999990463256836);
        offset.y = -cosdf(player->motionCopy.y) * (player->motionCopy.x + 55.9999990463256836);
        offset.z = -120.0 - player->motionCopy.z;
        m254_MakeRotXMtx(rotX, CRotM[camera].x);
        m254_MakeRotYMtx(rotY, CRotM[camera].y);
        m254_MultiplyMtx(rotX, rotY, transform);
        func_801114B0_motor_rooter(transform, &offset, position);
        HmfModelData[object->model[9]].pos.x = CenterM[camera].x + position[0];
        HmfModelData[object->model[9]].pos.y = CenterM[camera].y + position[1];
        HmfModelData[object->model[9]].pos.z = CenterM[camera].z + position[2];
    } else {
        Hu3DModelPosSet(object->model[9], object->trans.x, object->trans.y + 0.0, object->trans.z);
    }
    Hu3DModelRotSet(object->model[9], object->rot.x, object->rot.y, object->rot.z);
    if (player->unk08 & 0x400) {
        m254_MakeIdentityMtx(model->mtx[0]);
        func_80017D24_main(model->mtx[0], 0.0f, player->unk74, 0.0f);
        model->rot.y = model->rot.z = 0.0f;
    } else {
        m254_MakeIdentityMtx(model->mtx[0]);
        func_80017D24_main(model->mtx[0], 0.0f, 0.0f, 360.0f - player->turnAngle);
    }
    if (!(player->unk08 & 0x200)) {
        angle = player->motion.y;
        bounce = player->motion.z;
        offset.x = sindf(angle) * (player->motion.x + 65.9999990463256836);
        offset.y = -cosdf(angle) * (player->motion.x + 65.9999990463256836);
        offset.z = -120.0 - bounce;
        m254_MakeRotXMtx(rotX, CRotM[camera].x);
        m254_MakeRotYMtx(rotY, CRotM[camera].y);
        m254_MultiplyMtx(rotX, rotY, transform);
        func_801114B0_motor_rooter(transform, &offset, position);
        HmfModelData[object->model[10]].pos.x = CenterM[camera].x + position[0];
        HmfModelData[object->model[10]].pos.y = CenterM[camera].y + position[1];
        HmfModelData[object->model[10]].pos.z = CenterM[camera].z + position[2];
    } else {
        func_8001C258_main(object->model[10], 4, 0);
        Hu3DModelPosSet(object->model[10], object->trans.x, object->trans.y - 10.0 + 0.0, object->trans.z);
    }
    if (player->unk08 & 0x400) {
        Hu3DModelRotSet(object->model[10], object->rot.x, object->rot.y, 0.0f);
        m254_MakeIdentityMtx(HmfModelData[object->model[10]].mtx[0]);
        func_80017D24_main(HmfModelData[object->model[10]].mtx[0], 0.0f, player->unk74, 0.0f);
    } else {
        Hu3DModelRotSet(object->model[10], object->rot.x, object->rot.y, object->rot.z);
        m254_MakeIdentityMtx(HmfModelData[object->model[10]].mtx[0]);
        func_80017D24_main(HmfModelData[object->model[10]].mtx[0], 0.0f, 0.0f, 360.0f - player->turnAngle);
    }
}

void func_8010B970_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;

    if (player->unk08 & 2) {
        return;
    }
    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            if (player->unk08 & 4) {
                ctx->work.f32[0] = player->turnAngle;
                ctx->work.f32[1] = player->turnAngle + 45.0f;
                player->direction = player->direction + 1 < 8 ? player->direction + 1 : 0;
            } else {
                player->direction = player->direction - 1 >= 0 ? player->direction - 1 : 7;
                ctx->work.f32[0] = player->turnAngle;
                ctx->work.f32[1] = player->turnAngle - 45.0f;
            }
            ctx->state = 1;
            break;
        case 1:
            player->turnAngle = (ctx->work.f32[1] - ctx->work.f32[0]) * sindf(ctx->work.s8[0] / 4.0f * 90.0f) + ctx->work.f32[0];
            if (player->turnAngle > 360.0f) {
                player->turnAngle -= 360.0f;
            }
            if (player->turnAngle < 0.0f) {
                player->turnAngle += 360.0f;
            }
            if (++ctx->work.s8[0] > 4.0f) {
                player->unk08 &= ~0xC;
                m254_ResetFunc((u8)object->work[0] + 4, ctx);
            }
            break;
    }
}

void func_8010BB78_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;

    if (player->unk08 & 0x11) {
        return;
    }
    if (player->unk08 & 0x100) {
        if (player->unk10 < 20.0f) {
            player->unk10 *= 2.0f;
            if (player->unk10 > 20.0f) {
                player->unk10 = 20.0f;
            }
        } else {
            HuAudFXPitchSet(D_801137D8_motor_rooter, D_8011345A_motor_rooter[player->unk14]);
            player->unk08 &= ~0x100;
        }
    } else {
        player->unk4C++;
        if (player->unk4C > D_8011349E_motor_rooter[player->unk14]) {
            player->unk4C = 0;
            if (player->unk14 - 1 > 0) {
                player->unk14--;
                player->unk28[player->unk14] = 2;
                player->unk10 -= 4.0f;
            }
            func_8004AAD0_main(D_801137D8_motor_rooter, 64);
            HuAudFXPitchSet(D_801137D8_motor_rooter, D_8011345A_motor_rooter[player->unk14]);
        }
    }
}

void func_8010BCD0_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player;
    omObjData *object;
    HmfModel *model;

    player = ctx->data;
    object = player->unk00;
    model = &HmfModelData[object->model[0]];
    if (model->unk40 >= D_800CCF58_main[model->unk02].unk02 - 1) {
        player->animChange = 1;
    }
    if (player->animChange) {
        func_800E5690_minigame(object, player->nextAnim);
        player->animChange = 0;
        if (player->nextAnim == 13) {
            func_80045F1C_main(D_800A178C_main[GwPlayer[m254_playerId[object->work[0]]].chr][0] | 0x2F, -1, 0);
        }
    }
}

void func_8010BDE4_motor_rooter(D_801137C8_motor_rooter_Struct *player, s16 anim, s8 change) {
    player->animChange = change;
    player->nextAnim = anim;
}

void func_8010BDF0_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;
    f32 t;

    if (ctx->state == 0) {
        ctx->work.s8[0] = 0;
        ctx->work.s16[0] = 0;
        ctx->work.f32[0] = -120.0f;
        ctx->work.f32[1] = 40.0f;
        ctx->state = 1;
        player->unk08 |= 0x200;
        D_801137D8_motor_rooter = func_8004AC5C_main(0x4AF, player->unk00->work[0]);
        func_8004AAD0_main(D_801137D8_motor_rooter, 64);
        HuAudFXPitchSet(D_801137D8_motor_rooter, D_8011345A_motor_rooter[player->unk14]);
        m254_SetFunc((u8)object->work[0] + 4, 8, -1, &D_801137C8_motor_rooter[object->work[0]],
                     func_8010B394_motor_rooter, 0, 0);
    }
    t = ctx->work.s8[0];
    t = sindf(t / 80.0f) * 90.0f;
    t = t > 1.0f ? 1.0f : t;
    ctx->work.s16[0] = ctx->work.s16[0] + 2 < 361 ? ctx->work.s16[0] + 2 : 0;
    ctx->work.f32[2] = sindf(ctx->work.s16[0]) * 20.0 * 0.05;
    object->trans.z = (ctx->work.f32[0] - ctx->work.f32[1]) * t + ctx->work.f32[1];
    object->trans.y = ctx->work.f32[2] + -55.9999990463256836;
    if (++ctx->work.s8[0] > 80) {
        m254_ResetFunc((u8)object->work[0] + 4, ctx);
        m254_SetFunc((u8)object->work[0] + 4, 7, -1, player, func_8010AF0C_motor_rooter, 0, 0)->work.s16[0] = ctx->work.s16[0];
        player->unk08 &= ~0x200;
    }
}

void func_8010C084_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;
    s16 camera = object->work[0];
    s16 i;
    f32 t;

    if (player->unk08 & 0xC) {
        return;
    }
    switch (ctx->state) {
        case 0:
            ctx->work.s8[2] = 0;
            ctx->work.s16[0] = 1;
            ctx->work.f32[3] = object->rot.y;
            player->rotationStart = CRotM[camera].y + 90.0f;
            if (ctx->work.f32[3] > 360.0f) {
                ctx->work.f32[3] -= 360.0f;
            }
            if (ctx->work.f32[3] < 0.0f) {
                ctx->work.f32[3] += 360.0f;
            }
            if (player->rotationStart - ctx->work.f32[3] > 180.0f) {
                player->rotationStart -= 360.0f;
            }
            ctx->work.f32[2] = player->turnAngle;
            if (player->turnAngle > 180.0f) {
                ctx->work.f32[1] = 360.0f;
            } else {
                ctx->work.f32[1] = 0;
            }
            ctx->work.f32[0] = player->unk10 / 40.0f;
            ctx->state = 1;
            player->unk08 |= 1;
            break;
        case 1:
            t = ctx->work.s8[2] / 15.0f;
            player->turnAngle = (ctx->work.f32[1] - ctx->work.f32[2]) * t + ctx->work.f32[2];
            if (++ctx->work.s8[2] > 15) {
                func_8004AB0C_main(120);
                ctx->state = 2;
                player->unk78 |= 4;
                for (i = 0; i < 4; i++) {
                    m254_minigame->runtime.counters.gameplay.playerCounters[camera * 4 + i] = 0;
                }
            }
            break;
        case 2:
            object->rot.y = (player->rotationStart - ctx->work.f32[3]) * sindf(ctx->work.s16[0]) + ctx->work.f32[3];
            if ((ctx->work.s16[0] *= 2.0f) > 90) {
                ctx->work.s16[0] = 90;
            }
            player->unk10 -= ctx->work.f32[0];
            if (++ctx->work.s16[5] > 6) {
                ctx->work.s16[5] = 0;
                if (player->unk14 - 1 >= 0) {
                    player->unk14--;
                    player->unk28[player->unk14] = 2;
                }
            }
            if (player->unk10 < 0.0f) {
                player->unk10 = 0;
                player->unk08 |= 0x80;
                m254_SetFunc((u8)object->work[0] + 4, 5, -1, player, func_8010C44C_motor_rooter, 0, 0);
                m254_ResetFunc((u8)object->work[0] + 4, ctx);
            }
            break;
    }
}

void func_8010C44C_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;
    PathPosition position;
    f32 t;

    if (ctx->state == 0) {
        position = func_8010D0AC_motor_rooter(func_8010D03C_motor_rooter(player->unk0C + 60.0),
                                              player->unk0C + 60.0);
        ctx->work.f32[0] = position.x;
        ctx->work.f32[1] = position.y;
        ctx->work.f32[2] = position.z;
        ctx->work.f32[3] = CRotM[object->work[0]].y;
        if (ctx->work.f32[3] <= -360.0f) {
            ctx->work.f32[3] += 360.0f;
        }
        player->cameraStart.x = object->trans.x;
        player->cameraStart.y = object->trans.y;
        player->cameraStart.z = object->trans.z;
        player->rotationStart = object->rot.y;
        ctx->work.s8[0] = ctx->work.s8[1] = ctx->work.s8[2] = 0;
        func_8010BDE4_motor_rooter(player, 6, 1);
        CharFXPlay(0x3A, GwPlayer[m254_playerId[object->work[0]]].chr);
        func_8001C258_main(object->model[1], 4, 0);
        ctx->state = 1;
    }
    t = ctx->work.s8[0] / 30.0f;
    t = sindf(t) * 90.0f;
    t = t > 1.0f ? 1.0f : t;
    object->trans.x = (ctx->work.f32[0] - player->cameraStart.x) * t + player->cameraStart.x;
    object->trans.z = (ctx->work.f32[2] - player->cameraStart.z) * t + player->cameraStart.z;
    object->trans.y = m254_CalcQuadraticBezier(t, player->cameraStart.y,
                                               player->cameraStart.y + 60.0, player->cameraStart.y);
    Hu3DModelPosSet(object->model[1], object->trans.x, player->cameraStart.y, object->trans.z);
    t = ctx->work.s8[1] / 10.0f;
    t = sindf(t) * 90.0f;
    t = t > 1.0f ? 1.0f : t;
    object->rot.y = (ctx->work.f32[3] - player->rotationStart) * t + player->rotationStart;
    if (++ctx->work.s8[0] > 30) {
        m254_SetFunc(FGRP_CAMERA, 0, -1, player, func_80108514_motor_rooter, 0, 0);
        m254_ResetFunc((u8)object->work[0] + 4, ctx);
    }
    if (++ctx->work.s8[1] > 10) {
        ctx->work.s8[1] = 10;
    }
    if (ctx->work.s8[0] > 20) {
        if (ctx->work.s8[2] == 0) {
            ctx->work.s8[2] = 1;
            func_8010BDE4_motor_rooter(player, 21, 1);
            CharFXPlay(0x31, GwPlayer[m254_playerId[object->work[0]]].chr);
        } else if (ctx->work.s8[2] == 1) {
            ctx->work.s8[2] = 2;
            func_8010BDE4_motor_rooter(player, 0, 0);
        }
    }
}

void func_8010C824_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;
    s16 i;
    f32 t;

    if (player->unk08 & 0xC) {
        return;
    }
    switch (ctx->state) {
        case 0:
            ctx->work.s8[2] = 0;
            ctx->work.s16[0] = 1;
            ctx->work.f32[3] = object->rot.y;
            ctx->work.f32[2] = player->turnAngle;
            if (player->turnAngle > 180.0f) {
                ctx->work.f32[1] = 360.0f;
            } else {
                ctx->work.f32[1] = 0;
            }
            ctx->work.f32[0] = player->unk10 / 60.0f;
            ctx->state = 1;
            player->unk08 |= 1;
            break;
        case 1:
            t = ctx->work.s8[2] / 15.0f;
            player->turnAngle = (ctx->work.f32[1] - ctx->work.f32[2]) * t + ctx->work.f32[2];
            if (++ctx->work.s8[2] > 15) {
                player->unk74 = object->rot.y;
                player->unk08 |= 0x400;
                ctx->state = 2;
                player->unk78 |= 4;
                for (i = 0; i < 4; i++) {
                    m254_minigame->runtime.counters.gameplay.playerCounters[object->work[0] * 4 + i] = 0;
                }
            }
            break;
        case 2:
            player->unk74 = (ctx->work.f32[3] + 1080.0f - ctx->work.f32[3]) * sindf(ctx->work.s16[0]) + ctx->work.f32[3];
            if (player->unk74 > 360.0f) {
                player->unk74 -= 360.0f;
            }
            if ((ctx->work.s16[0] += 1.0f) > 90) {
                ctx->work.s16[0] = 90;
            }
            player->unk10 -= ctx->work.f32[0];
            if (++ctx->work.s16[5] > 10) {
                ctx->work.s16[5] = 0;
                if (player->unk14 - 1 >= 0) {
                    player->unk14--;
                    player->unk28[player->unk14] = 2;
                }
            }
            if (player->unk10 < 0.0f) {
                player->unk10 = 0;
                func_8010BDE4_motor_rooter(player, 0, 1);
                m254_ResetFunc((u8)object->work[0] + 4, ctx);
            }
            break;
    }
}

void func_8010CB2C_motor_rooter(omObjData *object, s16 item, s16 modelIndex) {
    D_801137C8_motor_rooter_Struct *player = &D_801137C8_motor_rooter[object->work[0]];
    f32 jitter = 0.0f;
    s16 camera = object->work[0];
    s16 modelId = object->model[modelIndex];
    f32 rotX[16];
    f32 rotY[16];
    f32 transform[16];
    Vec offset;
    f32 position[3];
    HmfModel *model;
    f32 angle;

    if (item == 4) {
        jitter = rand16() % 31 - 15;
    }
    model = &HmfModelData[modelId];
    angle = jitter + player->turnAngle;
    offset.x = sindf(angle) * 55.9999990463256836;
    offset.y = -cosdf(angle) * 55.9999990463256836;
    offset.z = -100.0f;
    m254_MakeRotXMtx(rotX, CRotM[camera].x);
    m254_MakeRotYMtx(rotY, CRotM[camera].y);
    m254_MultiplyMtx(rotX, rotY, transform);
    func_801114B0_motor_rooter(transform, &offset, position);
    model->pos.x = CenterM[camera].x + position[0];
    model->pos.y = CenterM[camera].y + position[1];
    model->pos.z = CenterM[camera].z + position[2];
    model->rot.x = CRotM[camera].x;
    model->rot.y = CRotM[camera].y;
    m254_MakeIdentityMtx(model->mtx[0]);
    func_80017D24_main(model->mtx[0], 0.0f, 0.0f, angle);
}

void func_8010CD84_motor_rooter(Vec *positions, s16 count) {
    PathPoint *point;
    f32 angles[3];
    f32 distance;
    f32 finishDistance;
    f32 dx, dy, dz;
    s16 i;

    D_801137C0_motor_rooter = HuMemAllocTag(count * sizeof(PathPoint), 31000);
    point = D_801137C0_motor_rooter;
    finishDistance = distance = 0.0f;
    for (i = 0; i < count - 1; i++, point++) {
        dx = positions[i + 1].x - positions[i].x;
        dy = positions[i + 1].y - positions[i].y;
        dz = positions[i + 1].z - positions[i].z;
        point->segLen = point->invSegLen = sqrtf(dx * dx + dy * dy + dz * dz);
        point->cumDist = distance;
        distance += point->segLen;
        if (i <= D_801137CC_motor_rooter) {
            finishDistance += point->segLen;
        }
        if (point->invSegLen != 0.0f) {
            point->invSegLen = 1.0f / point->invSegLen;
        } else {
            point->invSegLen = 0.0f;
        }
        point->x = positions[i].x;
        point->y = positions[i].y;
        point->z = positions[i].z;
        m254_CalcPitchAndYaw(positions[i], positions[i + 1], angles);
        point->pitch = angles[0] + 180.0f;
        point->yaw = angles[1] - 180.0f;
        point->unk14 = 0.0f;
        while (point->pitch >= 360.0f) {
            point->pitch -= 360.0f;
        }
    }
    point->segLen = -1.0f;
    point->cumDist = distance;
    point->x = positions[i].x;
    point->y = positions[i].y;
    point->z = positions[i].z;
    m254_minigame->totalDistance = distance;
    m254_minigame->finishDistance = finishDistance;
    m254_minigame->pathPointCount = count;
    m254_minigame->unk0E = 60;
}

s16 func_8010D03C_motor_rooter(f32 dist) {
    s16 i;
    PathPoint *point;

    point = &D_801137C0_motor_rooter[m254_minigame->pathPointCount - 1];
    for (i = m254_minigame->pathPointCount; i > 0; i--, point--) {
        if (point->cumDist <= dist) {
            break;
        }
    }
    return i - 1;
}

PathPosition func_8010D0AC_motor_rooter(s16 index, f32 dist) {
    PathPosition position;
    PathPoint *point;
    f32 fraction;
    f32 start;
    f32 end;

    point = &D_801137C0_motor_rooter[index];
    fraction = dist - point->cumDist;
    fraction *= point->invSegLen;
    end = point[1].x;
    start = point->x;
    position.x = (end - start) * fraction + start;
    end = point[1].y;
    start = point->y;
    position.y = (end - start) * fraction + start;
    end = point[1].z;
    start = point->z;
    position.z = (end - start) * fraction + start;
    end = point[1].pitch;
    start = point->pitch;
    position.pitch = (end - start) * fraction + start;
    end = point[1].yaw;
    start = point->yaw;
    position.yaw = (end - start) * fraction + start;
    position.roll = 0;
    return position;
}

void func_8010D1A8_motor_rooter(s16 point, s16 direction) {
    s16 index = D_801137D2_motor_rooter;

    if (point >= D_801137CC_motor_rooter) {
        return;
    }
    if (index >= 10) {
        return;
    }
    m254_minigame->views[0].obstaclePoints[index] = m254_minigame->views[1].obstaclePoints[index] = point;
    direction += 4;
    while (direction < 0) {
        direction += 8;
    }
    while (direction >= 8) {
        direction -= 8;
    }
    m254_minigame->views[0].obstacleDirections[index] = m254_minigame->views[1].obstacleDirections[index] = direction;
    m254_minigame->views[0].obstacleTypes[index] = m254_minigame->views[1].obstacleTypes[index] = (rand16() % 3) + 1;
    D_801137D2_motor_rooter++;
}

void func_8010D2E4_motor_rooter(s32 arg0) {
    s16 directions[8];
    s16 obstacleSections[10];
    s16 j, k;
    s16 point, direction, count, sectionLength, section, preferredDirection, step, chance;

    for (step = 0; step < 10; step++) {
        obstacleSections[step] = 0;
    }
    sectionLength = (D_801137CC_motor_rooter - 10) / 10;
    direction = 0;
    point = 5;
    while (1) {
        if (point >= D_801137CC_motor_rooter || D_801137D0_motor_rooter >= 100) {
            break;
        }
        preferredDirection = -1;
        switch ((s16)(rand16() % 14)) {
            case 0:
            case 1:
                direction = rand16() % 8;
                count = rand16() % 2 + 2;
                for (j = 0; j < count; j++, point += 2) {
                    func_8010DC3C_motor_rooter(point, direction);
                }
                preferredDirection = direction + 4;
                chance = 70;
                break;
            case 2:
            case 3:
            case 4:
                direction = rand16() % 8;
                count = rand16() % 2 + 3;
                for (j = 0; j < count; j++, point += 6) {
                    func_8010DC3C_motor_rooter(point, direction);
                    direction += rand16() % 2 ? -1 : 1;
                }
                chance = 25;
                break;
            case 5:
                count = rand16() % 2 + 2;
                for (j = 0; j < count; j++, point += 8) {
                    direction = rand16() % 8;
                    for (k = 0; k < 2; k++) {
                        func_8010DC3C_motor_rooter(point, direction + k * 4);
                    }
                }
                preferredDirection = direction;
                chance = 25;
                break;
            case 6:
            case 7:
                direction = rand16() % 8;
                step = rand16() % 2 ? -1 : 1;
                count = rand16() % 2 + 2;
                for (j = 0; j < count; j++, point += 7) {
                    for (k = 0; k < 2; k++) {
                        func_8010DC3C_motor_rooter(point, direction + k * 4);
                    }
                    direction += step;
                }
                preferredDirection = direction;
                chance = 25;
                break;
            case 8:
                count = rand16() % 2 + 1;
                for (j = 0; j < count; j++, point += 9) {
                    m254_MakeRandPermutation(directions, 8);
                    for (k = 0; k < 3; k++) {
                        func_8010DC3C_motor_rooter(point, directions[k]);
                    }
                }
                chance = 50;
                break;
            case 9:
                count = rand16() % 2 + 2;
                for (j = 0; j < count; j++, point += 7) {
                    direction = rand16() % 8;
                    for (k = 0; k < 3; k++, direction += 3) {
                        func_8010DC3C_motor_rooter(point, direction);
                    }
                }
                chance = 50;
                break;
            case 10:
                direction = rand16() % 8;
                count = rand16() % 2 + 1;
                func_8010DC3C_motor_rooter(point, direction);
                point += 2;
                for (j = 0; j < count; j++, point += 2) {
                    for (k = 0; k < 2; k++) {
                        func_8010DC3C_motor_rooter(point, direction + k * 4);
                    }
                }
                preferredDirection = direction + 4;
                chance = 100;
                break;
            default:
                count = rand16() % 2 + 2;
                for (j = 0; j < count; j++, point += 9) {
                    direction = rand16() % 8;
                    func_8010DC3C_motor_rooter(point, direction);
                }
                chance = 50;
                break;
        }
        obstacleSections[0] = 1;
        section = (point - 10) / sectionLength;
        if (rand16() % 101 < chance && obstacleSections[section] == 0) {
            if (preferredDirection == -1) {
                direction = rand16() % 8;
            } else {
                direction = preferredDirection;
            }
            obstacleSections[section]++;
            step = 0;
            if (D_801137D2_motor_rooter > 0 &&
                point - m254_minigame->views[0].obstaclePoints[D_801137D2_motor_rooter - 1] < 5) {
                func_8010D1A8_motor_rooter(point,
                                           m254_minigame->views[0].obstacleDirections[D_801137D2_motor_rooter - 1] + 2);
            } else {
                func_8010D1A8_motor_rooter(point - step, direction);
            }
            for (j = 0; j < section; j++) {
                if (obstacleSections[j] == 0) {
                    obstacleSections[section] = 0;
                    obstacleSections[j]++;
                }
            }
            point += 4 + rand16() % 5;
        }
    }
}

void func_8010DC3C_motor_rooter(s16 point, s16 direction) {
    if (point >= D_801137CC_motor_rooter || D_801137D0_motor_rooter >= 100) {
        return;
    }
    if (D_801137D0_motor_rooter >= 16 &&
        point - m254_minigame->itemPoints[D_801137D0_motor_rooter - 15] < m254_minigame->unk0E) {
        return;
    }
    while (direction < 0) {
        direction += 8;
    }
    while (direction >= 8) {
        direction -= 8;
    }
    m254_minigame->itemPoints[D_801137D0_motor_rooter] = point;
    m254_minigame->itemDirections[D_801137D0_motor_rooter++] = direction;
}

void func_8010DD10_motor_rooter(FuncContext *ctx) {
    ctx->work.s8[0]++;
    if (ctx->work.s8[0] >= 6) {
        ctx->work.s8[0] = 0;
        if (D_800CDA7C_main[0] & 0x2000) {
            D_80113458_motor_rooter = D_80113458_motor_rooter + 1 < 3 ? D_80113458_motor_rooter + 1 : 0;
        }
    }
    sprintf(D_800D5218_main, "CONT TYPE %d", D_80113458_motor_rooter);
    print8(16, 80, D_800D5218_main);
}
