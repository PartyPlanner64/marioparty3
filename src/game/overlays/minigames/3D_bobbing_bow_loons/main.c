#include "common.h"
#include "game/mallocblock.h"
#include "game/overlays/minigame.h"

// Per-object work block for m261_balloonObj, allocated in
// m261_BalloonObjCreate. Holds five parallel per-item arrays.
typedef struct BobbingBowLoonsBalloon {
    /* 0x00 */ s32 state[5];
    /* 0x14 */ f32 pos_x[5];
    /* 0x28 */ f32 pos_y[5];
    /* 0x3C */ f32 pos_z[5];
    /* 0x50 */ f32 unk_50[5];
    /* 0x64 */ f32 unk_64[5];
    /* 0x78 */ f32 rise;
} BobbingBowLoonsBalloon; // Size 0x7C

// Per-balloon positions for the burst effect of the five balloons tied to the player,
// held in m261_burstObj. Each axis is a parallel array of five.
typedef struct BobbingBowLoonsBurst {
    /* 0x00 */ f32 x[5];
    /* 0x14 */ f32 y[5];
    /* 0x28 */ f32 z[5];
} BobbingBowLoonsBurst; // Size 0x3C

// Object data for the player object held in m261_playerObj,
// created in m261_PlayerObjCreate.
typedef struct BobbingBowLoonsPlayer {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ Vec pos;
    /* 0x10 */ f32 scale;
    /* 0x14 */ f32 unk_14;
} BobbingBowLoonsPlayer; // Size 0x18

// Object data for the stage object created in m261_StageObjCreate.
// Holds the positions of its eight models.
typedef struct BobbingBowLoonsStage {
    /* 0x00 */ f32 x[8];
    /* 0x20 */ f32 y[8];
    /* 0x40 */ f32 z[8];
} BobbingBowLoonsStage; // Size 0x60

// Object data for the dart object held in m261_dartObj,
// created in m261_DartObjCreate.
typedef struct BobbingBowLoonsDart {
    /* 0x00 */ s32 flags;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ f32 rotZ;
} BobbingBowLoonsDart; // Size 0x14

// Object data for the string object held in m261_stringObj,
// created in m261_StringObjCreate. Holds the positions of its seven models.
typedef struct BobbingBowLoonsString {
    /* 0x00 */ f32 x[7];
    /* 0x1C */ f32 y[7];
    /* 0x38 */ f32 z[7];
} BobbingBowLoonsString; // Size 0x54

// Object data for the balloon pop effect object held in m261_popObj,
// created in m261_PopObjCreate.
typedef struct BobbingBowLoonsPop {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ s32 flags;
    /* 0x10 */ f32 scale;
    /* 0x14 */ s32 timer;
    /* 0x18 */ s32 unk_18;
} BobbingBowLoonsPop; // Size 0x1C

// Object data for the Bowser object held in m261_koopaObj,
// created in m261_KoopaObjCreate.
typedef struct BobbingBowLoonsKoopa {
    /* 0x00 */ f32 y;
    /* 0x04 */ f32 headRot;
} BobbingBowLoonsKoopa; // Size 0x8

// Object data for the item object held in m261_itemObj,
// created in m261_ItemObjCreate. One item hangs from each balloon.
typedef struct BobbingBowLoonsItem {
    /* 0x00 */ f32 x[5];
    /* 0x14 */ f32 y[5];
    /* 0x28 */ f32 z[5];
    /* 0x3C */ s32 state[5];
    /* 0x50 */ f32 angle;
    /* 0x54 */ f32 heldX;
    /* 0x58 */ f32 heldY;
} BobbingBowLoonsItem; // Size 0x5C

extern u16 mgInstColumnTbl[];
extern u16 mgInstSlotTbl[];

MinigameFlow m261_mgFlow = {
    MG_STATE_OPENING, MINIGAME_ITEM, MG_TIMER_NONE, MG_TIME_DISP_NONE, FALSE, MG_GAUGE_NONE, MG_RESULT_GOT_ITEM, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    30, 300, -1, 90, 135
};
f32 m261_chrBalloonOfsTbl[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
s32 m261_chrDirTbl[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
char *m261_chrHandNameTbl[8] = {
    "migi-te3_2_1",
    "c001_000-migi-te2_3",
    "C002_000b-bmerge16",
    "c003_000-bmerge1_8",
    "Luigi1-migi-te1_1",
    "c005_000-bmerge6",
    "c001_000-migi-te2_3",
    "C002_000b-bmerge16",
};
s32 m261_chrAnimNoTbl[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

u8 m261_bssPad[4] BSS; /* Unreferenced. */
u8 m261_seqNo BSS;
s16 m261_unusedNo BSS;
s16 m261_itemEffNo BSS;
s16 m261_itemEffNoPad BSS; /* Unreferenced. */
s32 m261_playerNo BSS;
s32 m261_prizeItem BSS;
s32 m261_comTargetNo BSS;
s16 m261_cameraNo BSS;
s16 m261_cameraNoPad BSS; /* Unreferenced. */
omObjData *m261_playerObj BSS;
s16 m261_playerAnimTbl[2] BSS;
u8 m261_playerAnimTblPad[4] BSS; /* Unreferenced. */
omObjData *m261_stageObj BSS;
omObjData *m261_balloonObj BSS;
omObjData *m261_dartObj BSS;
omObjData *m261_stringObj BSS;
omObjData *m261_itemObj BSS;
u8 m261_itemObjPad[4] BSS; /* Unreferenced. */
s32 m261_balloonItemTbl[5] BSS;
s32 m261_hitBalloonNo BSS;
omObjData *m261_hitEffObj BSS;
omObjData *m261_popObj BSS;
omObjData *m261_burstObj BSS;
omObjData *m261_koopaObj BSS;

void omCameraViewSprDraw(struct CameraViewData *data);
void m261_CameraInit(void);
void m261_BackCreate(void);
void m261_PlayerObjCreate(void);
void m261_BalloonObjMain(omObjData *obj);
void m261_CameraZoomOutStart(void);
void m261_TimerStart(void);
void m261_DartThrow(void);
void m261_ThrowInputStart(void);
void m261_BalloonPopAll(void);
void m261_PlayerBurstStart(void);
void m261_StageObjMain(omObjData *obj);
void m261_PlayerObjMain(omObjData *obj);
void m261_StageObjCreate(void);
void m261_MainObjMain(omObjData *obj);
void m261_BalloonObjCreate(void);
void m261_ItemObjCreate(void);
void m261_StringObjCreate(void);
void m261_DartObjCreate(void);
void m261_BurstObjCreate(void);
void m261_KoopaObjCreate(void);
void m261_HitEffObjCreate(void);
void m261_CameraZoomOutProc(void);
void m261_CameraZoomInProc(void);
void m261_CameraLoseProc(void);
void m261_TimerProc(void);
void m261_DartMissProc(void);
void m261_ThrowInputProc(void);
void m261_KoopaLaughProc(void);
void m261_StringObjMain(omObjData *obj);
void m261_ItemObjMain(omObjData *obj);
void m261_ItemGetProc(void);
void m261_CameraZoomInStart(void);
void m261_PopStart(f32 x, f32 y);
void m261_PopObjMain(omObjData *obj);
void m261_BurstObjMain(omObjData *obj);
void m261_KoopaObjMain(omObjData *obj);
void m261_DartObjMain(omObjData *obj);
void m261_DartMissStart(void);
void m261_KoopaLaughStart(void);
void m261_HitEffDispOn(void);

void m261_ObjectSetup(void) {
    omInitObjMan(30, 10);
    MapCollInit(16);
    Hu3DQuadPoolInit(&mgQuadPool, 64);
    Hu3DSprModelInit(64);
    m261_CameraInit();
    omGameSysInit();
    Hu3DBGColorSet(0, 0, 0);
    MgFlowInit(&m261_mgFlow);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    m261_BackCreate();
    m261_PlayerObjCreate();
    m261_StageObjCreate();
    m261_BalloonObjCreate();
    m261_ItemObjCreate();
    m261_KoopaObjCreate();
    m261_unusedNo = 0;
    mgFieldStat = 0;
    m261_seqNo = 0;
    m261_prizeItem = -1;
    omAddObj(0x50, 0, 0, -1, m261_MainObjMain);
    m261_StringObjCreate();
    m261_DartObjCreate();
    m261_BurstObjCreate();
    m261_HitEffObjCreate();
    CZoom = 1000.0f;
    Center.x = 200.0f;
    Center.y = 80.0f;
    Center.z = 0.0f;
}

void m261_CameraInit(void) {
    s16 camIndex;

    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    m261_cameraNo = camIndex;
    Hu3DCameraPerspectiveSet(camIndex, 30.0f, 80.0f, 8000.0f);
    CZoom = 500.0f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = 0.0f;
}

void m261_BackCreate(void) {
    omObjData *obj;
    Vec pos;
    Vec target;
    s16 sprite;

    sprite = espEntry(HuSprAnimDataRead(0x5E0000), 0, 1);
    espDispOff(sprite);
    pos.x = 0.0f;
    pos.y = 1.0f;
    pos.z = 1500.0f;
    target.x = 0.0f;
    target.y = 0.0f;
    target.z = 0.0f;
    omCameraViewCreate(100, esprite[sprite].unk04, omCameraViewSprDraw, 30.0f, &pos, &target);
    obj = omAddObj(0x50, 3, 0, -1, NULL);
    obj->model[0] = Hu3DModelRead(0x5E0003, 0x6D9);
    obj->model[1] = Hu3DModelLink(obj->model[0]);
    obj->model[2] = Hu3DModelRead(0x5E0004, 0x6D9);
    omSetTra(obj, -550.0f, -400.0f, 10.0f);
    omSetSca(obj, 1.5f, 1.5f, 1.5f);
    Hu3DModelPosSet(obj->model[1], 400.0f, -400.0f, 4.0f);
    Hu3DModelPosSet(obj->model[2], 340.0f, -50.0f, -100.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 2.0f, 1.0f);
}

void m261_PlayerObjCreate(void) {
    // Copied onto the stack but never read.
    s32 unused[8] = { 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 3 };
    s32 modelFiles[8] = { 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0 };
    s32 motions[8][3] = {
        { 0x6E, 0x6F, 0x29 },
        { 0x6E, 0x6F, 0x29 },
        { 0x6E, 0x6F, 0x29 },
        { 0x6E, 0x6F, 0x29 },
        { 0x6E, 0x6F, 0x29 },
        { 0x6E, 0x6F, 0x29 },
        { 0x6E, 0x6F, 0x29 },
        { 0x6E, 0x6F, 0x29 },
    };
    s32 markerFiles[8] = { 8, 9, 10, 11, 12, 13, 14, 15 };
    s32 handFiles[8] = { 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C };
    s32 spriteFiles[8] = { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B };
    s32 spriteFiles2[8] = { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C };
    BobbingBowLoonsPlayer *player;
    omObjData *obj;
    s32 dir;
    s32 file;
    s16 chr;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            m261_playerNo = i;
            break;
        }
    }
    obj = omAddObj(0x50, 4, 10, -1, m261_PlayerObjMain);
    obj->data = HuMemAllocTag(sizeof(BobbingBowLoonsPlayer), 0x7918);
    m261_playerObj = obj;
    player = obj->data;
    player->unk_00 = 1;
    player->scale = 1.0f;
    player->unk_00 = 1;
    chr = GwPlayer[m261_playerNo].chr;
    dir = m261_chrDirTbl[chr] << 16;
    file = dir | modelFiles[chr];
    obj->model[0] = Hu3DModelRead(file, 0x6A9);
    obj->model[2] = Hu3DModelRead(handFiles[chr] | 0x5E0000, 0x6BD);
    obj->model[3] = Hu3DModelRead(file, 0x6BD);
    player->pos.x = 400.0f;
    player->pos.y = 0.0f;
    player->pos.z = 80.0f;
    player->unk_14 = 0.0f;
    omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
    omSetRot(obj, 0.0f, 270.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    Hu3DModelRotSet(obj->model[3], 0.0f, 270.0f, 0.0f);
    m261_playerAnimTbl[0] =
        CharAnimCreate(obj->model[0], 1, m261_chrAnimNoTbl[chr], dir | spriteFiles[chr]);
    m261_playerAnimTbl[1] = Hu3DAnimDataRead(dir | spriteFiles2[chr]);
    Hu3DModelDynamicFree(obj->model[0]);
    for (i = 0; i < 4; i++) {
        omObjMotionRead(obj, i, CharMotionDataNumGet(chr, motions[chr][i]));
    }
    Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
    Hu3DModelObjCopy(obj->model[2], m261_chrHandNameTbl[chr], obj->model[0],
                       m261_chrHandNameTbl[chr]);
    obj->model[1] = Hu3DModelRead(markerFiles[chr] | 0x5E0000, 0x6B9);
    Hu3DModelPosSet(obj->model[1],
                    player->pos.x + m261_chrBalloonOfsTbl[GwPlayer[m261_playerNo].chr],
                    player->pos.y + 150.0f, player->pos.z + 0.0f);
    Hu3DModelScaleSet(obj->model[1], 1.5f, 1.5f, 1.5f);
}

void m261_PlayerObjMain(omObjData *obj) {
    BobbingBowLoonsPlayer *player = obj->data;
    f32 scale;

    omSetSca(obj, player->scale, player->scale, player->scale);
    omSetTra(obj, player->pos.x, player->pos.y - 50.0f, player->pos.z);
    Hu3DModelPosSet(obj->model[1],
                    player->pos.x + m261_chrBalloonOfsTbl[GwPlayer[m261_playerNo].chr],
                    player->pos.y + 150.0f, player->pos.z + 0.0f);
    Hu3DModelPosSet(obj->model[3], player->pos.x, player->pos.y - 50.0f, player->pos.z + 2.0f);
    scale = player->scale * 1.5f;
    Hu3DModelScaleSet(obj->model[1], scale, scale, scale);
    if (player->unk_00 & 1) {
        player->pos.y = sindf(player->unk_14) * 10.0f;
        player->unk_14 += 10.0f;
        if (player->unk_14 >= 360.0f) {
            player->unk_14 -= 360.0f;
        }
    }
}

void m261_PlayerWinMotSet(void) {
    s16 chr = GwPlayer[m261_playerNo].chr;

    Hu3DMotionShiftSet(m261_playerObj->model[0], Hu3DData[m261_playerObj->motion[1]].motId,
                       0, 10, 0);
    CharAnimSet(m261_playerObj->model[0], 1, m261_chrAnimNoTbl[chr],
                       m261_playerAnimTbl[1]);
    HuAudCharVoicePlay((m261_chrDirTbl[chr] << 16) | 0x6F);
}

void m261_PlayerFallStart(void) {
    s16 chr = GwPlayer[m261_playerNo].chr;

    Hu3DModelAttrSet(m261_playerObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(m261_playerObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionShiftSet(m261_playerObj->model[3], Hu3DData[m261_playerObj->motion[2]].motId,
                       0, 10, 0);
    Hu3DMotionAttrSet(m261_playerObj->model[3], 2, 2);
    Hu3DModelObjCopy(m261_playerObj->model[3], m261_chrHandNameTbl[chr],
                       m261_playerObj->model[0], m261_chrHandNameTbl[chr]);
    m261_PlayerBurstStart();
}

void m261_StageObjCreate(void) {
    s32 attrs[2];
    s32 files[2] = { 0x13, 0x14 };
    s32 alphas[2] = { 0x40, 0xB3 };
    BobbingBowLoonsStage *stage;
    omObjData *obj;
    s32 i;
    s32 j;

    attrs[0] = 0xAC9;
    attrs[1] = 0x2C9;

    obj = omAddObj(0xFF, 8, 0, -1, m261_StageObjMain);
    m261_stageObj = obj;
    stage = obj->data = HuMemAllocTag(sizeof(BobbingBowLoonsStage), 0x7918);
    stage->x[0] = 0.0f;
    stage->x[1] = 1000.0f;
    stage->x[2] = 0.0f;
    stage->x[3] = 1000.0f;
    stage->x[4] = 50.0f;
    stage->x[5] = -950.0f;
    stage->x[6] = 50.0f;
    stage->x[7] = -950.0f;
    stage->y[0] = -400.0f;
    stage->y[1] = -400.0f;
    stage->y[2] = -400.0f;
    stage->y[3] = -400.0f;
    stage->y[4] = -400.0f;
    stage->y[5] = -400.0f;
    stage->y[6] = -400.0f;
    stage->y[7] = -400.0f;
    stage->z[0] = 16.0f;
    stage->z[1] = 16.0f;
    stage->z[2] = 2.0f;
    stage->z[3] = 2.0f;
    stage->z[4] = 18.0f;
    stage->z[5] = 18.0f;
    stage->z[6] = 0.0f;
    stage->z[7] = 0.0f;
    obj->model[0] = Hu3DModelRead(0x5E0001, 0x1699);
    obj->model[1] = Hu3DModelLink(obj->model[0]);
    obj->model[2] = Hu3DModelRead(0x5E0002, 0x699);
    obj->model[3] = Hu3DModelLink(obj->model[2]);
    for (j = 0, i = 4; i < 8; j++, i += 2) {
        obj->model[i] = Hu3DModelRead(files[j] | 0x5E0000, attrs[j]);
        Hu3DModelObjAttrSet(obj->model[i], 0x20000, 0x20000);
        Hu3DModelVtxBufMake(obj->model[i]);
        Hu3DModelTPLvlInit(obj->model[i]);
        Hu3DModelTPLvlSet(obj->model[i], alphas[j]);
        Hu3DModelRemakeStatic(obj->model[i]);
        Hu3DModelDynamicFree(obj->model[i]);
        obj->model[i + 1] = Hu3DModelLink(obj->model[i]);
    }
    omSetTra(obj, stage->x[0], stage->y[0], stage->z[0]);
    for (i = 1; i < 8; i++) {
        Hu3DModelPosSet(obj->model[i], stage->x[i], stage->y[i], stage->z[i]);
    }
}

void m261_StageObjMain(omObjData *obj) {
    BobbingBowLoonsStage *stage = obj->data;
    s32 i;

    for (i = 0; i < 8; i++) {
        if (i == 0) {
            omSetTra(obj, stage->x[0], stage->y[0], stage->z[0]);
        } else {
            Hu3DModelPosSet(obj->model[i], stage->x[i], stage->y[i], stage->z[i]);
        }
    }
    stage->x[0] += -3.0f;
    stage->x[1] += -3.0f;
    stage->x[2] += -1.0f;
    stage->x[3] += -1.0f;
    stage->x[4] += -3.0f;
    stage->x[5] += -3.0f;
    stage->x[6] += -1.0f;
    stage->x[7] += -1.0f;
    for (i = 0; i < 8; i++) {
        if (stage->x[i] <= -1000.0f) {
            stage->x[i] += 2000.0f;
        }
    }
}

void m261_ExitObjMain(omObjData *obj) {
    if (WipeStatGet() == 0) {
        HuWinAllKill();
        omOvlReturnEx(1);
    }
}

void m261_MainObjMain(omObjData *obj) {
    f32 cueFrames[8] = { 40.0f, 40.0f, 40.0f, 40.0f, 40.0f, 40.0f, 40.0f, 40.0f };

    if (omSysExitReq != 0) {
        HuAudFXAllStop();
        HuAudSeqFadeOut(30);
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
    }
    switch (MgFlowMain(obj)) {
        case 0:
            if (MgFlowStatTimeGet() == 1) {
                HuAudSeqPlay(0x44);
            }
            if (Hu3DData[m261_playerObj->model[0]].motTime ==
                cueFrames[GwPlayer[m261_playerNo].chr]) {
                HuAudFXPlay(0x4DA);
            }
            if (MgFlowStatTimeGet() == 15) {
                m261_CameraZoomOutStart();
                HuAudFXPlay(0x4E0);
            }
            break;
        case 1:
            break;
        case 2:
            if (MgFlowStatTimeGet() == 0) {
                m261_TimerStart();
                m261_ThrowInputStart();
            }
            if (m261_seqNo == 2 || m261_seqNo == 3) {
                if (m261_seqNo == 2) {
                    m261_BalloonPopAll();
                }
                m261_DartThrow();
                m261_seqNo = 4;
            }
            break;
        case 3:
            break;
        case 4:
            if (m261_prizeItem != -1) {
                m261_mgFlow.resultType = MG_RESULT_GOT_ITEM;
            } else {
                m261_mgFlow.resultType = MG_RESULT_GAME_OVER;
            }
            break;
        case 5:
            if (m261_prizeItem != -1) {
                GwPlayer[m261_playerNo].bonusCoin = m261_prizeItem;
            } else {
                GwPlayer[m261_playerNo].bonusCoin = -1;
            }
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            obj->func = m261_ExitObjMain;
            break;
    }
}

void m261_BalloonObjCreate(void) {
    s32 attr = 0x699;
    BobbingBowLoonsBalloon *work;
    BobbingBowLoonsPlayer *player;
    omObjData *obj;
    s32 i;

    obj = omAddObj(0xFF, 10, 0, -1, m261_BalloonObjMain);
    m261_balloonObj = obj;
    work = obj->data = HuMemAllocTag(sizeof(BobbingBowLoonsBalloon), 0x7918);
    player = m261_playerObj->data;
    for (i = 0; i < 5; i++) {
        work->state[i] = 1;
        work->pos_x[i] = i * 120.0f - 280.0f;
        work->pos_y[i] = 0.0f;
        work->pos_z[i] = player->pos.z;
        work->unk_50[i] = 0.0f;
        // The do-while(0) block ends a CSE block, needed to match register allocation.
        do {
            rand8();
            rand8();
        } while (0);
        work->unk_64[i] = (i + 1) * 1.3f;
        if (i == 0) {
            obj->model[0] = Hu3DModelRead(0x5E0007, attr);
            omSetTra(obj, work->pos_x[0], work->pos_y[0], work->pos_z[0]);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
            Hu3DModelPosSet(obj->model[i], work->pos_x[i % 5], work->pos_y[i % 5], work->pos_z[i % 5]);
        }
    }
    for (i = 0; i < 5; i++) {
        if (i == 0) {
            obj->model[5] = Hu3DModelRead(0x5E0010, attr);
            omSetTra(obj, work->pos_x[0], work->pos_y[0], work->pos_z[0]);
        } else {
            obj->model[i + 5] = Hu3DModelLink(obj->model[5]);
            Hu3DModelPosSet(obj->model[i], work->pos_x[i % 5], work->pos_y[i % 5], work->pos_z[i % 5]);
        }
    }
    work->rise = 0.0f;
}

void m261_BalloonObjMain(omObjData *obj) {
    BobbingBowLoonsBalloon *work = obj->data;
    s32 i;

    for (i = 0; i < 5; i++) {
        if (i == 0) {
            omSetTra(obj, work->pos_x[0], work->pos_y[0], work->pos_z[0]);
        } else {
            Hu3DModelPosSet(obj->model[i], work->pos_x[i], work->pos_y[i], work->pos_z[i]);
        }
        Hu3DModelPosSet(obj->model[i + 5], work->pos_x[i], work->pos_y[i], work->pos_z[i] - 4.0f);
        if (work->state[i] & 1) {
            work->pos_y[i] = sindf(work->unk_50[i]) * 200.0f;
            work->unk_50[i] += work->unk_64[i];
            if (work->unk_50[i] >= 360.0f) {
                work->unk_50[i] -= 360.0f;
            }
            if (work->unk_50[i] <= 0.0f) {
                work->unk_50[i] += 360.0f;
            }
        }
        if (work->state[i] & 2) {
            work->pos_y[i] += work->rise;
            work->rise += 0.1f;
            if (work->pos_y[i] >= 500.0f) {
                work->state[i] &= ~2;
            }
        }
    }
}

void m261_BalloonRiseStart(void) {
    BobbingBowLoonsBalloon *work = m261_balloonObj->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(work->state); i++) {
        work->state[i] = (work->state[i] | 2) & ~1;
    }
    work->rise = 0;
}

s32 m261_BalloonHitCheck(void) {
    s32 hit = -1;
    BobbingBowLoonsBalloon *work = m261_balloonObj->data;
    BobbingBowLoonsDart *dart = m261_dartObj->data;
    f32 x = dart->x - 25.0f;
    f32 y = dart->y - 100.0f;
    f32 loonX;
    f32 loonY;
    s16 fx;
    s32 i;

    for (i = 0; i < 5; i++) {
        loonX = work->pos_x[i];
        loonY = work->pos_y[i] - 50.0f;
        if (fabs(x - loonX) < 50.0 && fabs(y - loonY) < 50.0) {
            hit = i;
            fx = HuAudFXPlay(0x4DC);
            if (fx >= 0) {
                HuAudFXPanning(fx, hit * 10 + 44);
            }
            return hit;
        }
    }
    return hit;
}

void m261_StringObjCreate(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x50, 7, 0, -1, m261_StringObjMain);
    obj->data = HuMemAllocTag(sizeof(BobbingBowLoonsString), 0x7918);
    m261_stringObj = obj;
    obj->model[0] = Hu3DModelRead(0x5E0006, 0x4B9);
    for (i = 1; i < 7; i++) {
        obj->model[i] = Hu3DModelLink(obj->model[0]);
    }
    Hu3DData[obj->model[5]].scale.y = 1.2f;
}

void m261_StringObjMain(omObjData *obj) {
    BobbingBowLoonsString *strings = obj->data;
    BobbingBowLoonsBalloon *work = m261_balloonObj->data;
    BobbingBowLoonsPlayer *player = m261_playerObj->data;
    s32 i;

    for (i = 0; i < 5; i++) {
        strings->x[i] = work->pos_x[i];
        strings->y[i] = work->pos_y[i] - 100.0f;
        strings->z[i] = work->pos_z[i] - 2.0f;
    }
    strings->x[5] = player->pos.x + m261_chrBalloonOfsTbl[GwPlayer[m261_playerNo].chr];
    strings->y[5] = player->pos.y + 42.0f;
    strings->z[5] = player->pos.z - 2.0f;
    omSetTra(obj, strings->x[0], strings->y[0], strings->z[0]);
    for (i = 1; i < 7; i++) {
        Hu3DModelPosSet(obj->model[i], strings->x[i], strings->y[i], strings->z[i]);
    }
    Hu3DModelAttrSet(obj->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void m261_ItemObjCreate(void) {
    s32 counts[16];
    s32 itemFiles[16] = { 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60 };
    BobbingBowLoonsItem *items;
    BobbingBowLoonsBalloon *work;
    omObjData *obj;
    void *spriteData;
    s16 sprite;
    s32 total;
    s32 value; // Item index, then reused for the random roll
    s32 i;
    s32 j;

    obj = omAddObj(0xFE, 5, 0, -1, m261_ItemObjMain);
    obj->data = HuMemAllocTag(sizeof(BobbingBowLoonsItem), 0x7918);
    m261_itemObj = obj;
    items = obj->data;
    work = m261_balloonObj->data;
    for (i = 0; i < 16; i++) {
        counts[i] = 0;
    }
    for (i = 0; i < 5; i++) {
        value = mgInstColumnTbl[4 - i];
        counts[value]++;
        m261_balloonItemTbl[i] = value;
        spriteData = DataRead(itemFiles[value] | 0x210000);
        sprite = Hu3DSprModelCreate(spriteData, 0x699, 8);
        DataClose(spriteData);
        obj->model[i] = Hu3DSprModelData[sprite].modelId;
        items->x[i] = work->pos_x[i];
        items->y[i] = work->pos_y[i];
        items->z[i] = work->pos_z[i] - 2.0f;
        if (i == 0) {
            omSetTra(obj, items->x[0], items->y[0], items->z[0]);
            omSetSca(obj, 1.8f, 1.8f, 1.8f);
        } else {
            Hu3DModelPosSet(obj->model[i], items->x[i], items->y[i], items->z[i]);
            Hu3DModelScaleSet(obj->model[i], 1.8f, 1.8f, 1.8f);
        }
        items->state[i] = 1;
    }
    items->angle = 0.0f;
    items->heldX = 0.0f;
    items->heldY = 0.0f;
    if (GwPlayer[m261_playerNo].stat & 1) {
        value = (u8)(rand8() % 100);
        for (j = 0, total = 0; j < 5; j++) {
            if (value >= total && value < total + mgInstSlotTbl[j]) {
                break;
            }
            total += mgInstSlotTbl[j];
        }
        if (j == 5) {
            j = 4;
        }
        m261_comTargetNo = j;
    }
}

void m261_ItemObjMain(omObjData *obj) {
    BobbingBowLoonsItem *items = obj->data;
    BobbingBowLoonsBalloon *work = m261_balloonObj->data;
    BobbingBowLoonsPlayer *player = m261_playerObj->data;
    s32 i;

    for (i = 0; i < 5; i++) {
        if (items->state[i] & 1) {
            items->y[i] = work->pos_y[i] + 50.0f;
        }
        if (items->state[i] & 2) {
            items->x[i] = items->heldX;
            items->y[i] = sindf(items->angle) * 20.0f + items->heldY;
            items->z[i] = player->pos.z + 2.0f;
            items->angle += 10.0f;
            if (items->angle >= 360.0f) {
                items->angle -= 360.0f;
            }
            EffectPosSet(m261_itemEffNo, items->x[i], items->y[i], items->z[i]);
        }
        if (i == 0) {
            omSetTra(obj, items->x[0], items->y[0], items->z[0]);
        } else {
            Hu3DModelPosSet(obj->model[i], items->x[i], items->y[i], items->z[i]);
        }
    }
}

void m261_ItemGetStart(s32 idx) {
    BobbingBowLoonsItem *items = m261_itemObj->data;

    items->state[idx] |= 2;
    items->angle = 0.0f;
    items->heldX = 0.0f;
    items->heldY = 0.0f;
    m261_hitBalloonNo = idx;
    m261_prizeItem = m261_balloonItemTbl[idx];
    m261_itemEffNo = EffectCreate(0xB0004, 0x6A9);
    omAddPrcObj(m261_ItemGetProc, 0x50, 0, 0);
    HuAudFXPlay(0x4DD);
}

void m261_ItemGetProc(void) {
    BobbingBowLoonsBalloon *work = m261_balloonObj->data;
    BobbingBowLoonsItem *items = m261_itemObj->data;
    BobbingBowLoonsPlayer *player = m261_playerObj->data;
    f32 dx;
    f32 dy;
    s32 i;

    m261_BalloonRiseStart();
    Hu3DModelAttrSet(m261_balloonObj->model[m261_hitBalloonNo], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(m261_balloonObj->model[m261_hitBalloonNo + 5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(m261_stringObj->model[m261_hitBalloonNo], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(m261_dartObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    m261_PopStart(work->pos_x[m261_hitBalloonNo],
                                    work->pos_y[m261_hitBalloonNo] + 50.0f);
    items->heldX = items->x[m261_hitBalloonNo];
    items->heldY = items->y[m261_hitBalloonNo] + 50.0f;
    dx = (player->pos.x - items->x[m261_hitBalloonNo]) / 30.0f;
    dy = (player->pos.y + 150.0f - items->y[m261_hitBalloonNo]) / 30.0f;
    for (i = 0; i < 30; i++) {
        items->heldX += dx;
        items->heldY += dy;
        HuPrcVSleep();
    }
    m261_CameraZoomInStart();
    omDelPrcObj(NULL);
}

void m261_CameraZoomOutStart(void) {
    omAddPrcObj(m261_CameraZoomOutProc, 0x50, 0, 0);
}

void m261_CameraZoomOutProc(void) {
    s32 i;

    for (i = 0; i < 30; i++) {
        CZoom += (1500.0f - 1000.0f) / 30.0f;
        Center.x += (0.0f - 200.0f) / 30.0f;
        Center.y += (0.0f - 80.0f) / 30.0f;
        HuPrcVSleep();
    }
    CZoom = 1500.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    omDelPrcObj(NULL);
}

void m261_CameraZoomInStart(void) {
    omAddPrcObj(m261_CameraZoomInProc, 0x50, 0, 0);
}

void m261_CameraZoomInProc(void) {
    s32 i;

    for (i = 0; i < 30; i++) {
        CZoom -= (1500.0f - 1000.0f) / 30.0f;
        Center.x -= (0.0f - 200.0f) / 30.0f;
        Center.y -= (0.0f - 80.0f) / 30.0f;
        HuPrcVSleep();
    }
    CZoom = 1000.0f;
    Center.x = 200.0f;
    Center.y = 80.0f;
    m261_PlayerWinMotSet();
    omDelPrcObj(NULL);
}

void m261_CameraLoseStart(void) {
    omAddPrcObj(m261_CameraLoseProc, 0x50, 0, 0);
}

void m261_CameraLoseProc(void) {
    s32 i;

    for (i = 0; i < 20; i++) {
        CZoom -= (1500.0f - 1250.0f) / 20.0f;
        Center.x -= (0.0f - 100.0f) / 20.0f;
        Center.y -= (0.0f - 0.0f) / 20.0f;
        HuPrcVSleep();
    }
    CZoom = 1250.0f;
    Center.x = 100.0f;
    Center.y = 0.0f;
    omDelPrcObj(NULL);
}

void m261_TimerStart(void) {
    omAddPrcObj(m261_TimerProc, 0x50, 0, 0);
}

void m261_TimerProc(void) {
    s32 seconds = 10;
    s32 frames = 30;

    GMesPosSet(GMesCreate(GMES_MES_TIMER, 10, 160, 28), 160.0f, 28.0f);
    do {
        frames--;
        if (frames == 0) {
            frames = 30;
            seconds--;
        }
        GMesTimerValueSet(seconds);
        HuPrcVSleep();
        if (m261_seqNo == 4) {
            break;
        }
    } while (seconds > 0);
    if (m261_seqNo == 0) {
        m261_seqNo = 2;
    }
    GMesTimerEnd();
    omDelPrcObj(NULL);
}

void m261_DartObjCreate(void) {
    BobbingBowLoonsDart *dart;
    BobbingBowLoonsPlayer *player;
    omObjData *obj;

    obj = omAddObj(0xFF, 1, 0, -1, m261_DartObjMain);
    m261_dartObj = obj;
    dart = HuMemAllocTag(sizeof(BobbingBowLoonsDart), 0x7918);
    obj->data = dart;
    player = m261_playerObj->data;
    obj->model[0] = Hu3DModelRead(0x5E0005, 0x699);
    dart->flags = 0;
    dart->x = 0.0f;
    dart->y = 50.0f;
    dart->z = player->pos.z;
    dart->rotZ = 270.0f;
    omSetTra(obj, dart->x, dart->y, dart->z);
    omSetRot(obj, 0.0f, 0.0f, dart->rotZ);
    Hu3DModelHookSet(obj->model[0], m261_playerObj->model[0], "item_hook");
    Hu3DModelAttrSet(obj->model[0], 0x4000, 0x4000);
}

void m261_DartObjMain(omObjData *obj) {
    BobbingBowLoonsDart *dart = obj->data;
    s32 hit;

    omSetTra(obj, dart->x, dart->y, dart->z);
    omSetRot(obj, 0.0f, 0.0f, dart->rotZ);
    if (dart->flags & 1) {
        dart->x -= 23.0f;
        hit = m261_BalloonHitCheck();
        if (hit != -1) {
            MgFlowStatSet(MG_STATE_FINISH);
            m261_ItemGetStart(hit);
            dart->flags &= ~1;
            omVibrate(m261_playerNo, 2, 2, 20);
        } else if (dart->x <= -290.0f) {
            m261_seqNo = 0;
            MgFlowStatSet(MG_STATE_FINISH);
            m261_DartMissStart();
            dart->flags &= ~1;
            omVibrate(m261_playerNo, 20, 0, 20);
        }
    }
}

void m261_DartThrow(void) {
    BobbingBowLoonsDart *dart = m261_dartObj->data;

    dart->x = m261_playerObj->trans.x;
    dart->y = m261_playerObj->trans.y + 100.0f;
    dart->flags |= 1;
    Hu3DModelAttrSet(m261_dartObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(m261_dartObj->model[0], 0x4000, 0);
    HuAudFXPlay(0x4DB);
}

void m261_DartMissStart(void) {
    omAddPrcObj(m261_DartMissProc, 0x50, 0, 0);
}

void m261_DartMissProc(void) {
    f32 offsetX[8] = { -20.0f, 0.0f, -15.0f, 31.5f, 5.0f, 19.2f, -15.0f, 0.0f };
    f32 offsetY[8] = { 100.0f, -19.0f, 70.0f, -106.2f, -18.0f, -107.1f, 70.0f, -16.0f };
    f32 offsetZ[8] = { 15.0f, -2.5f, 0.0f, 20.5f, 0.0f, 36.2f, 0.0f, 3.0f };
    BobbingBowLoonsDart *dart = m261_dartObj->data;
    BobbingBowLoonsPlayer *player = m261_playerObj->data;
    BobbingBowLoonsBalloon *work = m261_balloonObj->data;
    f32 speed;
    s32 i;

    if (m261_seqNo != 2) {
        m261_BalloonPopAll();
    }
    for (i = 0; i < 5; i++) {
        work->state[i] &= ~1;
    }
    omSetTra(m261_hitEffObj, dart->x + 30.0f, dart->y - 30.0f, dart->z);
    m261_HitEffDispOn();
    HuAudFXPlay(0x4DE);
    dart->rotZ = 150.0f;
    while (dart->y < 400.0f) {
        dart->x += sindf(30.0f) * 23.0f;
        dart->y += cosdf(30.0f) * 23.0f;
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    dart->rotZ = 180.0f;
    dart->x = m261_playerObj->trans.x;
    while (m261_playerObj->trans.y + 300.0f <= dart->y) {
        dart->y -= 23.0f;
        HuPrcVSleep();
    }
    dart->y = m261_playerObj->trans.y - 200.0f;
    Hu3DModelAttrSet(m261_dartObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(m261_stringObj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(m261_playerObj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    m261_PopStart(
        player->pos.x + m261_chrBalloonOfsTbl[GwPlayer[m261_playerNo].chr],
        player->pos.y + 230.0f);
    HuAudFXPlay(0x4DF);
    HuAudFXPlay(GwPlayer[m261_playerNo].chr + 0x2AC);
    player->unk_00 &= ~1;
    player->pos.x -= offsetX[GwPlayer[m261_playerNo].chr];
    player->pos.y -= offsetY[GwPlayer[m261_playerNo].chr];
    player->pos.z -= offsetZ[GwPlayer[m261_playerNo].chr];
    m261_PlayerFallStart();
    HuPrcSleep(30);
    HuAudPlayerFXPlay(GwPlayer[m261_playerNo].chr + 0x287, m261_playerNo);
    Hu3DMotionAttrSet(m261_playerObj->model[3], 1, 1);
    speed = -20.0f;
    while (player->pos.y >= -500.0f) {
        player->pos.y = speed + player->pos.y;
        speed -= 5.0f;
        HuPrcVSleep();
    }
    m261_KoopaLaughStart();
    MgFlowStatSet(MG_STATE_FINISH);
    omDelPrcObj(NULL);
}

void m261_ThrowInputStart(void) {
    omAddPrcObj(m261_ThrowInputProc, 0x50, 0, 0);
}

void m261_ThrowInputProc(void) {
    f32 angles[5];
    f32 minAngles[5] = { 120.0f, 300.0f, 120.0f, 320.0f, 160.0f };
    f32 maxAngles[5] = { 140.0f, 320.0f, 140.0f, 340.0f, 180.0f };
    f32 targetAngles[5];
    BobbingBowLoonsBalloon *work;
    s32 done = FALSE;
    s32 range;
    s32 hit;
    s32 i;
    f32 y;

    work = m261_balloonObj->data;
    do {
        if (GwPlayer[m261_playerNo].stat & 1) {
            range = (4 - GwPlayer[m261_playerNo].cpu_difficulty) * 5;
            for (i = 0; i < 5; i++) {
                targetAngles[i] = (rand8() % (range * 2) - range) + minAngles[i];
            }
            angles[m261_comTargetNo] = work->unk_50[m261_comTargetNo];
            hit = 0;
            if (maxAngles[m261_comTargetNo] < 360.0f) {
                if (targetAngles[m261_comTargetNo] <= angles[m261_comTargetNo] &&
                    angles[m261_comTargetNo] < maxAngles[m261_comTargetNo]) {
                    hit++;
                }
            } else if ((angles[m261_comTargetNo] >= 0.0f &&
                        angles[m261_comTargetNo] < maxAngles[m261_comTargetNo] - 360.0f) ||
                       (angles[m261_comTargetNo] >= minAngles[m261_comTargetNo] &&
                        angles[m261_comTargetNo] < 360.0f)) {
                hit++;
            }
            if (hit != 0) {
                hit = 0;
                y = work->pos_y[m261_comTargetNo];
                for (i = m261_comTargetNo + 1; i < 5; i++) {
                    if (work->pos_y[i] >= y - 20.0f && work->pos_y[i] < y + 20.0f) {
                        hit++;
                        break;
                    }
                }
                if (hit == 0) {
                    m261_seqNo = 3;
                    break;
                }
            }
        } else if (HuPadBtnDown[GwPlayer[m261_playerNo].pad] & A_BUTTON) {
            m261_seqNo = 3;
            break;
        }
        HuPrcVSleep();
    } while (!done);
    omDelPrcObj(NULL);
}

void m261_PopObjCreate(s32 recolor) {
    BobbingBowLoonsPop *effect;
    omObjData *obj;

    obj = omAddObj(0xFF, 2, 0, -1, m261_PopObjMain);
    m261_popObj = obj;
    effect = obj->data = HuMemAllocTag(sizeof(BobbingBowLoonsPop), 0x7918);
    obj->model[0] = Hu3DModelRead(0x5E0011, 0x6CD);
    Hu3DModelObjAttrSet(obj->model[0], 0x20000, 0x20000);
    Hu3DModelVtxBufMake(obj->model[0]);
    obj->model[1] = Hu3DModelRead(0x5E0012, 0x6DD);
    if (recolor) {
        switch (GwPlayer[m261_playerNo].chr) {
            case 0:
                Hu3DModelTexAnimChange(obj->model[0], "c0_DEF", "c1_DEF");
                break;
            case 1:
                Hu3DModelTexAnimChange(obj->model[0], "c0_DEF", "c2_DEF");
                break;
            case 2:
                Hu3DModelTexAnimChange(obj->model[0], "c0_DEF", "c3_DEF");
                break;
            case 3:
                Hu3DModelTexAnimChange(obj->model[0], "c0_DEF", "c4_DEF");
                break;
            case 4:
                Hu3DModelTexAnimChange(obj->model[0], "c0_DEF", "c5_DEF");
                break;
            case 5:
                Hu3DModelTexAnimChange(obj->model[0], "c0_DEF", "c6_DEF");
                break;
            case 6:
                Hu3DModelTexAnimChange(obj->model[0], "c0_DEF", "c7_DEF");
                break;
            case 7:
                Hu3DModelTexAnimChange(obj->model[0], "c0_DEF", "c8_DEF");
                break;
        }
    }
    Hu3DModelTPLvlInit(obj->model[0]);
    Hu3DModelTPLvlSet(obj->model[0], 0xA0);
    Hu3DModelRemakeStatic(obj->model[0]);
    Hu3DModelDynamicFree(obj->model[0]);
    effect->x = 0.0f;
    effect->y = 0.0f;
    effect->z = 0.0f;
    effect->flags = 0;
    effect->timer = 0;
    effect->scale = 0.1f;
}

void m261_PopObjMain(omObjData *obj) {
    BobbingBowLoonsPop *effect = obj->data;

    omSetTra(obj, effect->x, effect->y, effect->z);
    if (effect->flags & 1) {
        effect->scale += 0.03f;
        Hu3DModelVtxWave(obj->model[0], effect->scale, effect->scale * 25.0f, 2);
        if (++effect->timer == 30) {
            Hu3DModelAttrSet(m261_popObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            effect->flags &= ~1;
        }
    }
}

void m261_PopStart(f32 x, f32 y) {
    BobbingBowLoonsPlayer *player = m261_playerObj->data;
    BobbingBowLoonsPop *effect;
    s32 recolor;
    f32 scale;

    if (x == player->pos.x + m261_chrBalloonOfsTbl[GwPlayer[m261_playerNo].chr]) {
        scale = 1.5f;
        recolor = TRUE;
    } else {
        recolor = FALSE;
        scale = 1.0f;
    }
    m261_PopObjCreate(recolor);
    effect = m261_popObj->data;
    effect->flags |= 1;
    Hu3DModelAttrSet(m261_popObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    effect->x = x;
    effect->y = y;
    effect->z = 16.0f;
    omSetSca(m261_popObj, scale, scale, scale);
}

void m261_BurstObjCreate(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0xFF, 2, 0, -1, m261_BurstObjMain);
    m261_burstObj = obj;
    obj->data = HuMemAllocTag(sizeof(BobbingBowLoonsBurst), 0x7918);
    obj->model[0] = Hu3DModelRead(0x5D0008, 0xA3D);
    for (i = 1; i < 5; i++) {
        obj->model[i] = Hu3DModelLink(obj->model[0]);
    }
}

void m261_BurstObjMain(omObjData *obj) {
    BobbingBowLoonsBurst *burst = obj->data;
    s32 i;

    omSetTra(obj, burst->x[0], burst->y[0], burst->z[0]);
    for (i = 1; i < 5; i++) {
        Hu3DModelPosSet(obj->model[i], burst->x[i], burst->y[i], burst->z[i]);
    }
    if (Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 <= Hu3DData[obj->model[0]].motTime) {
        for (i = 0; i < 5; i++) {
            Hu3DModelAttrSet(obj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
    }
}

void m261_BalloonPopAll(void) {
    BobbingBowLoonsBurst *burst = m261_burstObj->data;
    BobbingBowLoonsBalloon *work = m261_balloonObj->data;
    s32 i;

    for (i = 0; i < 5; i++) {
        Hu3DModelAttrSet(m261_balloonObj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(m261_stringObj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(m261_itemObj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        burst->x[i] = work->pos_x[i];
        burst->y[i] = work->pos_y[i] + 50.0f;
        burst->z[i] = work->pos_z[i] + 2.0f;
        work->state[i] &= ~1;
        work->pos_y[i] = -1000.0f;
        Hu3DModelAttrSet(m261_burstObj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
}

void m261_PlayerBurstStart(void) {
    BobbingBowLoonsBurst *burst = OM_GET_DATA_PTR(m261_burstObj, BobbingBowLoonsBurst);
    BobbingBowLoonsPlayer *player = OM_GET_DATA_PTR(m261_playerObj, BobbingBowLoonsPlayer);

    burst->x[0] = player->pos.x;
    burst->y[0] = player->pos.y + 50.0f;
    burst->z[0] = player->pos.z + 2.0f;
    Hu3DModelAttrSet(m261_burstObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionTimeSet(m261_burstObj->model[0], 0.0f);
}

void m261_KoopaObjCreate(void) {
    BobbingBowLoonsKoopa *koopa;
    omObjData *obj;

    obj = omAddObj(0xFF, 2, 0, -1, m261_KoopaObjMain);
    m261_koopaObj = obj;
    koopa = HuMemAllocTag(sizeof(BobbingBowLoonsKoopa), 0x7918);
    obj->data = koopa;
    obj->model[0] = Hu3DModelRead(0xA00EE, 0x6D9);
    omSetSca(obj, 0.7f, 0.7f, 0.7f);
    omSetRot(obj, 0.0f, 325.0f, 0.0f);
    Hu3DMotionAttrSet(obj->model[0], 2, 2);
    koopa->y = -130.0f;
    koopa->headRot = 0.0f;
}

void m261_KoopaObjMain(omObjData *obj) {
    BobbingBowLoonsKoopa *koopa = obj->data;
    HmfMotionNode *node;
    s16 model;

    omSetTra(obj, 370.0f, koopa->y, -70.0f);
    model = obj->model[0];
    Hu3DMotionNoMotSet(model, Hu3DData[model].motId, "c162_000-atama", 0x4C, 0x45);
    node = Hu3DModelObjPtrGet(model, "c162_000-atama");
    node->baseRot.x = koopa->headRot;
    node->rot.x = koopa->headRot;
    Hu3DMotionAttrSet(obj->model[0], 1, 1);
}

void m261_KoopaLaughStart(void) {
    omAddPrcObj(m261_KoopaLaughProc, 0x50, 0, 0);
}

void m261_KoopaLaughProc(void) {
    BobbingBowLoonsKoopa *koopa = m261_koopaObj->data;
    s32 i;
    s32 j;

    for (i = 0; i < 10; i++) {
        koopa->y += 10.0f;
        HuPrcVSleep();
    }
    m261_CameraLoseStart();
    HuPrcSleep(20);
    HuAudFXPlay(0x2A0);
    for (i = 0; i < 30; i++) {
        for (j = 0; j < 2; j++) {
            koopa->headRot += 8.0f;
            HuPrcVSleep();
        }
        for (j = 0; j < 2; j++) {
            koopa->headRot -= 8.0f;
            HuPrcVSleep();
        }
    }
    omDelPrcObj(NULL);
}

void m261_HitEffObjCreate(void) {
    omObjData *object = omAddObj(0xFF, 1, 0, -1, NULL);

    m261_hitEffObj = object;
    object->data = HuMemAllocTag(8, TAG_OVERLAY);
    object->model[0] = Hu3DModelRead(0xB0003, 0x6DD);
}

void m261_HitEffDispOn(void) {
    Hu3DModelAttrSet(m261_hitEffObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}
