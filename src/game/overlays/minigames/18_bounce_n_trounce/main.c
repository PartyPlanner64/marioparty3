#include "common.h"
#include "game/overlays/minigame.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

// Per-player work, allocated in m224_PlayerObjInit
typedef struct BounceNTrounceWork {
    /* 0x00 */ u16 playerId;
    /* 0x02 */ u16 state;
    /* 0x04 */ u16 motState;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ u16 unk_0C;
    /* 0x0E */ u16 unk_0E[4];
    /* 0x16 */ u16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1C */ omObjData *floorTile;
    /* 0x20 */ f32 motSpeed;
    /* 0x24 */ f32 motDir;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 jumpVel;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 jumpTime;
    /* 0x40 */ f32 jumpBaseY;
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;
    /* 0x4C */ Vec prevPos;
    /* 0x58 */ Vec unk_58;
    /* 0x64 */ f32 unk_64;
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ f32 floorRadius;
    /* 0x74 */ f32 radius;
    /* 0x78 */ omObjData *emitter;
    /* 0x7C */ s16 unk_7C;
    /* 0x7E */ u16 unk_7E;
    /* 0x80 */ Vec aiTargetPos;
    /* 0x8C */ Vec aiTilePos;
    /* 0x98 */ u16 aiTile;
    /* 0x9A */ char pad_9A[2];
    /* 0x9C */ omObjData *aiTarget;
    /* 0xA0 */ u16 aiState;
    /* 0xA2 */ u16 unk_A2;
    /* 0xA4 */ s16 unk_A4;
    /* 0xA6 */ u16 aiWait;
    /* 0xA8 */ u16 unk_A8;
    /* 0xAA */ char pad_AA[2];
} BounceNTrounceWork; // Size 0xAC

// Particle emitter work, allocated in m224_PlayerObjInit
typedef struct BounceNTrounceEmitterWork {
    /* 0x00 */ u16 interval;
    /* 0x04 */ f32 angle;
    /* 0x08 */ f32 angleStep;
} BounceNTrounceEmitterWork; // Size 0xC

// Floor tile work, allocated in m224_StageObjInit
typedef struct BounceNTrounceTileWork {
    /* 0x00 */ s16 index;
    /* 0x02 */ u16 state;
    /* 0x04 */ f32 velY;
    /* 0x08 */ u16 timer;
} BounceNTrounceTileWork; // Size 0xC

extern s32 omCharModelNoTbl[][6];
extern f32 Hu3DMotionGlobalSpeed;

MinigameFlow m224_mgFlow = {
    MG_STATE_OPENING, MINIGAME_4P, MG_TIMER_COUNT_DOWN, MG_TIME_DISP_COUNTDOWN, FALSE, MG_GAUGE_NONE, MG_RESULT_WIN_1, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    -1, 900, -1, -1, 135
};
s8 m224_introStickXTbl[4] = { 0, 0, 0, 0 };
s8 m224_introStickYTbl[4] = { 0, 0, 0, 0 };
u16 m224_introBtnTbl[4] = { 0, 0, 0, 0 };
u16 m224_exitF = 0;
Vec m224_tilePosTbl[9] = {
    { -300.0f, 0.0f, -300.0f },
    { 0.0f, 0.0f, -300.0f },
    { 300.0f, 0.0f, -300.0f },
    { -300.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 300.0f, 0.0f, 0.0f },
    { -300.0f, 0.0f, 300.0f },
    { 0.0f, 0.0f, 300.0f },
    { 300.0f, 0.0f, 300.0f }
};
Vec m224_decoPosTbl[7] = {
    { -750.0f, 100.0f, -900.0f },
    { 50.0f, 300.0f, -900.0f },
    { 1100.0f, -500.0f, -200.0f },
    { -1100.0f, -700.0f, -400.0f },
    { 700.0f, 100.0f, -900.0f },
    { 950.0f, 400.0f, -900.0f },
    { -1050.0f, -350.0f, -950.0f }
};
s32 m224_decoMdlTbl[7] = {
    0x0039000D, 0x0039000E, 0x0039000D, 0x0039000E, 0x0039000D, 0x0039000E, 0x0039000D
};
s32 m224_decoSpeedTbl[7] = { 160, 115, 140, 94, 120, 98, 150 };
s16 m224_tileFallTbl[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
u16 m224_tileFallDelay = 300;
u16 m224_tileFallTimer = 0;
Vec m224_playerStartPosTbl[4] = {
    { -90.0f, 0.0f, -90.0f },
    { 90.0f, 0.0f, -90.0f },
    { -90.0f, 0.0f, 90.0f },
    { 90.0f, 0.0f, 90.0f }
};
s32 m224_springMdlTbl[8] = {
    0x00390003, 0x00390004, 0x00390005, 0x00390006, 0x00390007, 0x00390008, 0x00390009, 0x0039000A
};
Vec m224_endPosTbl[4] = {
    { -150.0f, 0.0f, -150.0f },
    { 150.0f, 0.0f, -150.0f },
    { -150.0f, 0.0f, 150.0f },
    { 150.0f, 0.0f, 150.0f }
};
u16 m224_endPosUsedTbl[4] = { 0, 0, 0, 0 };
u16 m224_introJumpF = 0;
u16 m224_introJumpCnt = 0;
u16 m224_finishDecideF = 0;
u16 m224_winnerTurnF = 0;

u16 m224_finishTimer BSS;
u16 m224_finishNextPhase BSS;
f32 m224_cameraZoomSpeed BSS;
f32 m224_cameraZoomTarget BSS;
u16 m224_playerAliveCnt BSS;
u16 m224_winner BSS;
omObjData *m224_introObj BSS;
omObjData *m224_finishObj BSS;
u16 m224_introPhase BSS;
u16 m224_finishPhase BSS;
s16 m224_playF BSS;
omObjData *m224_stageObj BSS;
omObjData *m224_cameraObj BSS;
omObjData **m224_tileObjTbl BSS;
omObjData **m224_playerObjTbl BSS;
omObjData **m224_decoObjTbl BSS;
s16 m224_playerStartSlotTbl[4] BSS;

void omCameraViewSprDraw(struct CameraViewData *data);

void m224_MainObjInit(omObjData *arg0);
void m224_MainObjMain(omObjData *);
void m224_StageObjInit(omObjData *object);
void m224_PlayerObjInit(omObjData *object);
void m224_CameraZoomObjMain(omObjData *object);
void m224_StageObjMain(omObjData *object);
void m224_TileObjMain(omObjData *object);
void m224_DecoObjMain(omObjData *object);
void m224_PlayerObjMain(omObjData *object);
void m224_PlayerIntroObjMain(omObjData *object);
void m224_SpinEffHook(s16 model);
void m224_SpinEffObjMain(omObjData *object);
void m224_PlayerHitClear(void);
void m224_PlayerEndObjInit(omObjData *object);
void m224_IntroObjMain(omObjData *object);
void m224_FinishObjMain(omObjData *object);
f32 m224_Dist2DCalc(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
void m224_OvlReturn(void);
void m224_TileShakeObjMain(omObjData *object);
void m224_TileFallObjMain(omObjData *object);
void m224_PlayerUpdate(omObjData *object, s8 stickX, s8 stickY, u16 btn);
void m224_PlayerOutUpdate(omObjData *object);
void m224_PlayerSpinStop(omObjData *object);
void m224_PlayerKnockBack(omObjData *object, omObjData *other);
void m224_PlayerJumpSet(omObjData *object, f32 vel);
void m224_PlayerHitCheck(omObjData *object);
void m224_HitEffShow(omObjData *object, f32 x, f32 y, f32 z);
void m224_LandEffShow(omObjData *object);
void m224_PlayerComInputGet(omObjData *object, s8 *stickX, s8 *stickY, u16 *btn);
void m224_PlayerComStateDecide(omObjData *object);
f32 m224_PlayerFloorYGet(omObjData *object);
void m224_PlayerMotUpdate(omObjData *object);
s32 m224_PlayerComRouteSet(omObjData *object, s16 arg1);
s16 m224_PlayerComTileGet(omObjData *object);
s16 m224_TileNoGet(f32 x, f32 z);
void m224_PlayerEndWaitObjMain(omObjData *);
void m224_PlayerEndObjMain(omObjData *);

void m224_ObjectSetup(void) {
    s32 i;
    s16 slot;

    omInitObjMan(40, 0);
    omGameSysInit();
    HuAudCharVoiceInit();
    CamSetupInit(1);
    CamSetupMapCullAdd(1);
    Center.x = 0.0f;
    Center.y = 30.0f;
    Center.z = 0.0f;
    CRot.x = -30.0f;
    CRot.y = 45.0f;
    CRot.z = 0.0f;
    CZoom = 2100.0f;
    ScissorSet(0, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(1, 0x40, 0x40, 0x60);
    Hu3DGLightDirSet(1, 3.0f, 89.0f, 80.0f);
    Hu3DGLightStatSet(1, 1, 1);
    Hu3DGLightColorSet(3, 0, 0, 0);
    Hu3DGLightDirSet(3, -115.0f, 6.0f, -33.0f);
    Hu3DGLightStatSet(2, 1, 1);
    omAddObj(0, 0, 0, -1, m224_MainObjInit);
    m224_stageObj = omAddObj(10, 0, 0, -1, m224_StageObjInit);
    m224_cameraObj = omAddObj(50, 0, 0, -1, m224_CameraZoomObjMain);
    m224_cameraObj->work[0] = 0;
    omMakeGroup(0, 4);
    m224_playerObjTbl = omGetGroupMemberList(0);
    for (i = 0; i < 4; i++) {
        omAddObj(30, 7, 6, 0, m224_PlayerObjInit)->work[0] = i;
    }
    for (i = 0; i < 4; i++) {
        m224_playerStartSlotTbl[i] = -1;
    }
    for (i = 0; i < 4;) {
        slot = (u8)(rand8() & 3);
        if (m224_playerStartSlotTbl[slot] == -1) {
            m224_playerStartSlotTbl[slot] = i;
            i++;
        }
    }
    MgFlowInit(&m224_mgFlow);
}

void m224_MainObjInit(omObjData *arg0) {
    m224_playerAliveCnt = 4;
    m224_finishObj = 0;
    m224_introObj = 0;
    m224_playF = 1;
    arg0->func = m224_MainObjMain;
}

void m224_MainObjMain(omObjData *object) {
    if (m224_exitF == 0) {
        switch (MgFlowMain()) {
            case 0:
                if (m224_introObj == NULL) {
                    m224_introPhase = 0;
                    m224_introObj = omAddObj(4, 0, 0, -1, m224_IntroObjMain);
                    m224_cameraObj->work[0] = 1;
                }
                break;
            case 1:
                break;
            case 2:
                m224_PlayerHitClear();
                if (m224_playerAliveCnt == 0) {
                    m224_playF = 0;
                    m224_stageObj->work[0] = 0;
                    MgFlowStatSet(MG_STATE_FINISH);
                } else if (m224_playerAliveCnt == 1) {
                    m224_playF = 0;
                    m224_stageObj->work[0] = 0;
                    MgFlowStatSet(MG_STATE_FINISH);
                }
                break;
            case 3:
                m224_stageObj->work[0] = 0;
                m224_PlayerHitClear();
                if (m224_finishObj == NULL) {
                    m224_finishPhase = 0;
                    m224_finishObj = omAddObj(4, 0, 0, -1, m224_FinishObjMain);
                }
                break;
            case 4:
                m224_PlayerHitClear();
                break;
            case 5:
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                HuAudSeqFadeOut(30);
                HuAudFXAllFadeOut(30);
                m224_exitF = 1;
                break;
        }
    } else if (WipeStatGet() == 0) {
        m224_OvlReturn();
    }
}

void m224_StageObjInit(omObjData *object) {
    omObjData *obj;
    omObjData *deco;
    BounceNTrounceTileWork *tileWork;
    s32 i;
    s16 sprite;
    f32 x;
    f32 z;
    Vec pos;
    Vec target;

    omMakeGroup(2, 9);
    m224_tileObjTbl = omGetGroupMemberList(2);
    omMakeGroup(3, 7);
    m224_decoObjTbl = omGetGroupMemberList(3);
    for (i = 0; i < 9; i++) {
        obj = omAddObj(20, 1, 0, 2, m224_TileObjMain);
        obj->data = HuMemAllocTag(sizeof(BounceNTrounceTileWork), TAG_OVERLAY);
        tileWork = OM_GET_DATA_PTR(obj, BounceNTrounceTileWork);
        tileWork->index = i;
        if (i & 1) {
            if (i == 1) {
                obj->model[0] = Hu3DModelRead(0x390001, 0x6B9);
            } else {
                obj->model[0] = Hu3DModelLink(m224_tileObjTbl[1]->model[0]);
            }
        } else {
            if (i == 0) {
                obj->model[0] = Hu3DModelRead(0x390000, 0x6B9);
            } else {
                obj->model[0] = Hu3DModelLink(m224_tileObjTbl[0]->model[0]);
            }
        }
        omSetTra(obj, m224_tilePosTbl[i].x, m224_tilePosTbl[i].y,
                 m224_tilePosTbl[i].z);
        tileWork->state = 0;
    }
    for (i = 0; i < 7; i++) {
        deco = omAddObj(20, 1, 0, 3, m224_DecoObjMain);
        deco->model[0] = Hu3DModelRead(m224_decoMdlTbl[i], 0x6B9);
        HuSqrtf(m224_decoPosTbl[i].x * m224_decoPosTbl[i].x +
                m224_decoPosTbl[i].z * m224_decoPosTbl[i].z);
        x = cosdf(-45.0f) * m224_decoPosTbl[i].x - sindf(-45.0f) * m224_decoPosTbl[i].z;
        z = sindf(-45.0f) * m224_decoPosTbl[i].x + cosdf(-45.0f) * m224_decoPosTbl[i].z;
        omSetTra(deco, x, m224_decoPosTbl[i].y, z);
        omSetRot(deco, 0.0f, 45.0f, 0.0f);
        omSetSca(deco, 1.5f, 1.5f, 1.5f);
        deco->work[0] = 0;
        deco->work[1] = m224_decoSpeedTbl[i];
    }
    sprite = espEntry(HuSprAnimDataRead(0x390002), 0, 1);
    espDispOff(sprite);
    target.x = 0.0f;
    target.y = 120.0f;
    target.z = 0.0f;
    pos.x = sindf(45.0f) * 2800.0f;
    pos.y = 1400.0f;
    pos.z = cosdf(45.0f) * 2800.0f;
    omCameraViewCreate(0x7FDA, esprite[sprite].unk04, omCameraViewSprDraw, 45.0f, &pos, &target);
    Hu3DCameraPerspectiveSet(0, 45.0f, 500.0f, 4500.0f);
    CZoom = 2100.0f;
    object->work[0] = 1;
    m224_tileFallTbl[4] = 1;
    object->func = m224_StageObjMain;
}

void m224_StageObjMain(omObjData *object) {
    s16 candidates[9];
    s16 count;
    s32 i;
    s16 choice;
    BounceNTrounceTileWork *work;

    if (MgFlowStatGet() == MG_STATE_PLAY && object->work[0] != 0) {
        if (m224_tileFallDelay != 0) {
            m224_tileFallDelay--;
            return;
        }
        if (m224_tileFallTimer != 0) {
            m224_tileFallTimer--;
            return;
        }
        m224_tileFallTimer = 60;
        count = 0;
        for (i = 0; i < 9; i++) {
            if (m224_tileFallTbl[i] == 0) {
                candidates[count++] = i;
            }
        }
        if (count == 0) {
            return;
        }
        if (count == 1) {
            choice = candidates[0];
        } else {
            choice = candidates[rand8() % count];
        }
        m224_tileFallTbl[choice] = 1;
        work = OM_GET_DATA_PTR(m224_tileObjTbl[choice], BounceNTrounceTileWork);
        work->state = 1;
        work->velY = -15.0f;
        work->timer = 40;
        HuAudFXPlay(0x3D1);
        m224_tileObjTbl[choice]->func = m224_TileShakeObjMain;
    }
}

f32 m224_PlayerFloorYGet(omObjData *object) {
    BounceNTrounceWork *work;
    f32 radius;
    f32 maxY = -100000.0f;
    omObjData *tile;
    f32 x0;
    f32 x1;
    f32 z0;
    f32 z1;
    f32 dist;
    s32 i;
    s32 j;

    work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    radius = work->floorRadius;
    work->floorTile = NULL;
    for (i = 0; i < 9; i++) {
        tile = m224_tileObjTbl[i];
        if (OM_GET_DATA_PTR(tile, BounceNTrounceTileWork)->state == 3) {
            continue;
        }
        x0 = tile->trans.x - 150.0f;
        z0 = tile->trans.z - 150.0f;
        x1 = tile->trans.x + 150.0f;
        z1 = tile->trans.z + 150.0f;
        if (x0 <= object->trans.x && z0 <= object->trans.z && object->trans.x <= x1 && object->trans.z <= z1 &&
            maxY < tile->trans.y) {
            maxY = tile->trans.y;
            work->floorTile = tile;
            continue;
        }
        for (j = 0; j < 2; j++) {
            x0 = tile->trans.x - 150.0f;
            z0 = tile->trans.z - 150.0f + j * 150.0f * 2;
            x1 = tile->trans.x + 150.0f;
            if (x0 <= object->trans.x && object->trans.x <= x1) {
                dist = HuSqrtf((object->trans.z - z0) * (object->trans.z - z0));
            } else if (object->trans.x < x0) {
                dist = m224_Dist2DCalc(object->trans.x, object->trans.z, x0, z0);
            } else if (x1 < object->trans.x) {
                dist = m224_Dist2DCalc(object->trans.x, object->trans.z, x1, z0);
            }
            if (dist <= radius && maxY < tile->trans.y) {
                maxY = tile->trans.y;
                work->floorTile = tile;
            }
        }
        for (j = 0; j < 2; j++) {
            x0 = tile->trans.x - 150.0f + j * 150.0f * 2;
            z0 = tile->trans.z - 150.0f;
            z1 = tile->trans.z + 150.0f;
            if (z0 <= object->trans.z && object->trans.z <= z1) {
                dist = HuSqrtf((object->trans.x - x0) * (object->trans.x - x0));
            } else if (object->trans.z < z0) {
                dist = m224_Dist2DCalc(object->trans.x, object->trans.z, x0, z0);
            } else if (z1 < object->trans.z) {
                // Uses x1 from the previous loop rather than x0.
                dist = m224_Dist2DCalc(object->trans.x, object->trans.z, x1, z0);
            }
            if (dist <= radius && maxY < tile->trans.y) {
                maxY = tile->trans.y;
                work->floorTile = tile;
            }
        }
    }
    return maxY;
}

void m224_TileObjMain(omObjData *object) {
}

void m224_TileShakeObjMain(omObjData *object) {
    BounceNTrounceTileWork *work = OM_GET_DATA_PTR(object, BounceNTrounceTileWork);

    if (m224_stageObj->work[0] == 0) {
        omSetTra(object, object->trans.x, 0.0f, object->trans.z);
        object->func = NULL;
        return;
    }
    if (work->velY == 0.0f) {
        omSetTra(object, object->trans.x, 0.0f, object->trans.z);
        work->velY = -15.0f;
    } else {
        omSetTra(object, object->trans.x, work->velY, object->trans.z);
        work->velY = 0.0f;
    }
    if (--work->timer == 0) {
        work->velY = -4.4f;
        work->state = 2;
        object->func = m224_TileFallObjMain;
    }
}

void m224_TileFallObjMain(omObjData *object) {
    BounceNTrounceTileWork *work = OM_GET_DATA_PTR(object, BounceNTrounceTileWork);

    object->trans.y += work->velY;
    work->velY *= 1.22f;
    if (object->trans.y < -1500.0f) {
        object->trans.y = -1500.0f;
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        work->state = 3;
        object->func = NULL;
    }
}

void m224_DecoObjMain(omObjData *object) {
    f32 angle = object->work[0];

    angle /= 10.0f;
    object->work[0] += object->work[1];
    if (object->work[0] >= 3600) {
        object->work[0] -= 3600;
    }
    omSetSca(object, 1.5f - sindf(angle) * 0.5f, 1.5f - sindf(angle) * 0.5f, 1.5f - sindf(angle) * 0.5f);
}

void m224_PlayerObjInit(omObjData *object) {
    BounceNTrounceWork *work;
    omObjData *emitter;
    HmfData *hmf;
    HmfModelData_UnkBC_Struct *modelData;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    u16 playerId;
    s8 chr;
    s32 mdlId;
    s32 mdlAttr;
    f32 angle;
    s32 i;

    object->data = HuMemAllocTag(sizeof(BounceNTrounceWork), TAG_OVERLAY);
    work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    work->playerId = object->work[0];
    playerId = work->playerId;
    work->state = 0;
    work->motState = 2;
    work->motSpeed = 4.0f;
    work->motDir = 1.0f;
    work->unk_28 = 1.5f;
    work->unk_30 = work->unk_34 = work->unk_38 = 0.0f;
    work->unk_08 = 0;
    work->unk_0A = 0;
    work->unk_0C = 0;
    work->unk_18 = 0;
    work->unk_44 = 0.0f;
    work->unk_48 = 0.0f;
    work->unk_06 = 0;
    work->unk_16 = 0;
    work->floorRadius = 40.0f;
    work->radius = 55.0f;
    work->floorTile = NULL;
    work->unk_7C = 0;
    work->unk_7E = 0;
    work->aiState = 0;
    work->aiTarget = NULL;
    work->unk_A2 = 0;
    work->unk_64 = work->unk_68 = work->unk_6C = 0.0f;
    for (i = 0; i < 4; i++) {
        work->unk_0E[i] = 0;
    }
    chr = GwPlayer[playerId].chr;
    mdlId = omCharModelNoTbl[chr][0];
    mdlAttr = omCharModelNoTbl[chr][1];
    object->model[0] = Hu3DModelRead(m224_springMdlTbl[chr], 0x6D9);
    omSetTra(object, m224_playerStartPosTbl[m224_playerStartSlotTbl[playerId]].x,
             m224_playerStartPosTbl[m224_playerStartSlotTbl[playerId]].y,
             m224_playerStartPosTbl[m224_playerStartSlotTbl[playerId]].z);
    object->model[1] = Hu3DModelRead(mdlId | mdlAttr, 0x206B9);
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    object->model[2] = Hu3DModelRead3(0, 0xA89);
    Hu3DModelPosSet(object->model[2], object->trans.x, object->trans.y + 1.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[2], work->unk_28, 1.0f, work->unk_28);
    object->model[3] = Hu3DModelRead(0x39000B, 0x68D);
    object->model[4] = Hu3DModelRead(0x39000C, 0x68D);
    object->model[6] = Hu3DModelRead(0x82, 0xA8D);
    Hu3DModelScaleSet(object->model[3], 1.2f, 1.0f, 1.2f);
    omObjMotionRead(object, 0, CharMotionDataNumGet(chr, 0x73));
    omObjMotionRead(object, 1, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(object, 2, CharMotionDataNumGet(chr, 1));
    omObjMotionRead(object, 3, CharMotionDataNumGet(chr, 0x1F));
    omObjMotionRead(object, 4, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(object, 5, CharMotionDataNumGet(chr, 0x36));
    Hu3DMotionModelSet(object->model[1], object->motion[0]);
    Hu3DMotionAttrSet(object->model[1], 3, 1);
    Hu3DMotionAttrSet(object->model[0], 3, 1);
    angle = atan2df(-object->trans.x, -object->trans.z);
    omSetRot(object, 0.0f, angle, 0.0f);
    Hu3DModelRotSet(object->model[1], 0.0f, angle, 0.0f);
    object->model[5] = Hu3DModelRead(0x39000F, 0x6A9);
    Hu3DModelPosSet(object->model[5], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelObjAttrSet(object->model[5], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(object->model[5]);
    Hu3DModelVtxBufMake(object->model[5]);
    Hu3DModelDynamicFree(object->model[5]);
    Hu3DParticleCreate(object->model[5], -1, NULL, m224_SpinEffHook);
    hmf = Hu3DData[object->model[5]].hmf;
    modelData = Hu3DData[object->model[5]].unkBC;
    particle = modelData->unk58;
    modelData->unk1C.i = 0;
    modelData->unk20.i = 0;
    modelData->unk24.i = 0;
    Hu3DParticleAttrSet(object->model[5], 1, 1);
    for (i = 0; i < hmf->unk1A; i++, particle++) {
        particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
        particle->unk18 = particle->unk1C = particle->unk20 = 0.0f;
        particle->unk04 = particle->unk08 = 0.0f;
    }
    emitter = omAddObj(60, 0, 0, -1, m224_SpinEffObjMain);
    work->emitter = emitter;
    emitter->data = HuMemAllocTag(sizeof(BounceNTrounceEmitterWork), TAG_OVERLAY);
    emitter->work[0] = 0;
    emitter->work[1] = (u32)object;
    work->unk_A8 = 0;
    work->prevPos.x = object->trans.x;
    work->prevPos.y = object->trans.y;
    work->prevPos.z = object->trans.z;
    object->func = m224_PlayerIntroObjMain;
}

void m224_PlayerObjMain(omObjData *object) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    u16 port = GwPlayer[work->playerId].pad;
    s8 stickX;
    s8 stickY;
    u16 btn;

    if (work->state == 3) {
        return;
    }
    if (GwPlayer[work->playerId].stat & PLAYER_IS_CPU) {
        m224_PlayerComInputGet(object, &stickX, &stickY, &btn);
    } else {
        stickX = HuPadStkX[port];
        stickY = HuPadStkY[port];
        btn = HuPadBtnDown[port];
    }
    if (MgFlowStatGet() == MG_STATE_OPENING || MgFlowStatGet() == MG_STATE_START || MgFlowStatGet() == MG_STATE_FINISH) {
        stickY = 0;
        stickX = 0;
        btn = 0;
    }
    if (work->state == 2 || work->state == 3) {
        stickY = 0;
        stickX = 0;
        btn = 0;
        m224_PlayerOutUpdate(object);
    } else {
        m224_PlayerUpdate(object, stickX, stickY, btn);
    }
}

void m224_PlayerIntroObjMain(omObjData *object) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);

    m224_PlayerUpdate(object, m224_introStickXTbl[work->playerId],
                                   m224_introStickYTbl[work->playerId],
                                   m224_introBtnTbl[work->playerId]);
}

void m224_PlayerUpdate(omObjData *object, s8 stickX, s8 stickY, u16 btn) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    BounceNTrounceWork *otherWork;
    BounceNTrounceEmitterWork *emitterWork;
    omObjData *other;
    f32 angle = atan2df(stickX, -stickY) + CRot.y;
    f32 speed = HuSqrtf(stickX * stickX + stickY * stickY) * 0.1f;
    f32 rotY = object->rot.y;
    f32 floorY = m224_PlayerFloorYGet(object);
    f32 jumpVel;
    s16 fx;
    s32 i;

    if (work->floorTile != NULL) {
        if (OM_GET_DATA_PTR(work->floorTile, BounceNTrounceTileWork)->state == 1) {
            if (work->unk_A8 == 0) {
                omVibrate(work->playerId, 2, 3, 10);
                work->unk_A8 = 10;
            } else {
                work->unk_A8--;
            }
        } else if (work->unk_A8 >= 6) {
            work->unk_A8--;
        } else {
            work->unk_A8 = 0;
        }
    } else if (work->unk_A8 >= 6) {
        work->unk_A8--;
    } else {
        work->unk_A8 = 0;
    }
    switch (work->motState) {
        case 4:
            if (work->unk_0C == 1) {
                fx = PlayerFXPlay(0x3BE, work->playerId);
                if (MgFlowStatGet() != MG_STATE_PLAY) {
                    HuAudFXVolSet(fx, 0x75);
                }
                work->unk_0A++;
                if (work->unk_0A >= 4) {
                    work->unk_0A = 1;
                }
                jumpVel = (work->unk_0A - 1) * 50.0f * 0.24f + 70.0f;
                work->unk_0C = 0;
            } else {
                work->unk_0A = 0;
                jumpVel = 37.5f;
                fx = PlayerFXPlay(0x3B5, work->playerId);
                if (MgFlowStatGet() != MG_STATE_PLAY) {
                    HuAudFXVolSet(fx, 0x75);
                }
            }
            m224_PlayerJumpSet(object, jumpVel);
            work->unk_08 = 1;
            work->motState = 3;
            // fallthrough
        case 2:
            work->unk_34 = sindf(angle) * speed;
            work->unk_38 = cosdf(angle) * speed;
            if (stickX != 0 || stickY != 0) {
                rotY = angle;
            }
            if (btn & A_BUTTON) {
                work->unk_0C = 1;
            }
            break;
    }
    if (work->unk_08 == 1) {
        if (work->unk_44 == 0.0f && (btn & Z_TRIG) && work->unk_0A != 0 && work->state == 0) {
            fx = PlayerFXPlay(0x3C7, work->playerId);
            if (MgFlowStatGet() != MG_STATE_PLAY) {
                HuAudFXVolSet(fx, 0x75);
            }
            work->state = 1;
            work->unk_44 = object->trans.y / 1500.0f * 140.0f + 20.0f;
            if (work->unk_44 > 160.0f) {
                work->unk_44 = 160.0f;
            }
            work->jumpVel = 0.0f;
            work->jumpTime = 0.0f;
            work->jumpBaseY = object->trans.y;
            work->radius = 85.0f;
            Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DMotionAttrSet(object->model[3], 3, 2);
            Hu3DMotionTimeSet(object->model[3], 0.0f);
            work->unk_06 = 1;
            emitterWork = OM_GET_DATA_PTR(work->emitter, BounceNTrounceEmitterWork);
            emitterWork->interval = 3;
            emitterWork->angle = object->rot.y + 180.0f;
            if (emitterWork->angle >= 360.0f) {
                emitterWork->angle -= 360.0f;
            }
            emitterWork->angleStep = work->unk_44 / 0.6666667f;
            if (emitterWork->angleStep < 15.0f) {
                emitterWork->angleStep = 15.0f;
            }
            if (emitterWork->angleStep > 100.0f) {
                emitterWork->angleStep = 100.0f;
            }
            work->emitter->work[2] = 0;
            work->emitter->work[0] = 1;
        }
        if (work->unk_44 != 0.0f) {
            rotY += work->unk_44;
        }
        work->jumpTime += 1.0f;
        object->trans.y =
            work->jumpVel * work->jumpTime + work->jumpBaseY - work->jumpTime * 2.4f * work->jumpTime;
        if (work->unk_16 == 0) {
            work->unk_34 = sindf(angle) * speed;
            work->unk_38 = cosdf(angle) * speed;
            if ((stickX != 0 || stickY != 0) && work->unk_44 == 0.0f) {
                rotY = angle;
            }
        } else {
            object->trans.x += work->unk_64;
            object->trans.z += work->unk_68;
        }
        object->trans.x += work->unk_34;
        object->trans.z += work->unk_38;
        m224_PlayerHitCheck(object);
        for (i = 0; i < 4; i++) {
            if (i == work->playerId) {
                continue;
            }
            other = m224_playerObjTbl[i];
            otherWork = OM_GET_DATA_PTR(other, BounceNTrounceWork);
            if (work->state != 1) {
                if (work->unk_0E[i] & 1) {
                    if (otherWork->state == 1) {
                        work->unk_16 = 1;
                        atan2df(object->trans.x - other->trans.x, -(object->trans.z - other->trans.z));
                        m224_PlayerKnockBack(other, object);
                        m224_HitEffShow(object, object->trans.x, object->trans.y + 120.0f,
                                                       object->trans.z);
                    } else {
                        work->jumpVel = 0.0f;
                        work->jumpTime = 0.0f;
                        work->jumpBaseY = object->trans.y;
                    }
                } else if (work->unk_0E[i] & 2) {
                    if (otherWork->state == 1) {
                        work->unk_16 = 1;
                        atan2df(object->trans.x - other->trans.x, -(object->trans.z - other->trans.z));
                        m224_PlayerKnockBack(other, object);
                        m224_HitEffShow(object, object->trans.x, object->trans.y + 70.0f,
                                                       object->trans.z);
                    } else {
                        work->unk_38 = -work->unk_38;
                        work->unk_34 = -work->unk_34;
                        work->unk_16 = 1;
                    }
                } else if (work->unk_0E[i] & 4) {
                    if (otherWork->state == 1) {
                        work->unk_16 = 1;
                        atan2df(object->trans.x - other->trans.x, -(object->trans.z - other->trans.z));
                        m224_PlayerKnockBack(other, object);
                        m224_HitEffShow(object, object->trans.x, object->trans.y, object->trans.z);
                    } else {
                        work->jumpVel = 50.0f;
                        work->jumpTime = 0.0f;
                        work->jumpBaseY = object->trans.y;
                    }
                }
            } else {
                work->unk_A2 = 1;
                if (work->unk_0E[i] & 1) {
                    m224_HitEffShow(object, object->trans.x, object->trans.y + 120.0f, object->trans.z);
                    omVibrate(work->playerId, 2, 2, 20);
                    if (otherWork->state == 1) {
                        if (otherWork->unk_44 == work->unk_44) {
                            m224_PlayerSpinStop(object);
                            m224_PlayerSpinStop(other);
                        } else if (otherWork->unk_44 > work->unk_44) {
                            work->unk_16 = 1;
                            atan2df(object->trans.x - other->trans.x, -(object->trans.z - other->trans.z));
                            m224_PlayerKnockBack(other, object);
                            m224_PlayerSpinStop(object);
                        } else {
                            otherWork->unk_16 = 1;
                            atan2df(other->trans.x - object->trans.x, -(other->trans.z - object->trans.z));
                            m224_PlayerKnockBack(object, other);
                            m224_PlayerSpinStop(other);
                        }
                    } else {
                        otherWork->unk_16 = 1;
                        atan2df(other->trans.x - object->trans.x, -(other->trans.z - object->trans.z));
                        m224_PlayerKnockBack(object, other);
                    }
                } else if (work->unk_0E[i] & 2) {
                    m224_HitEffShow(object, object->trans.x, object->trans.y + 70.0f, object->trans.z);
                    omVibrate(work->playerId, 2, 2, 20);
                    if (otherWork->state == 1) {
                        if (otherWork->unk_44 == work->unk_44) {
                            m224_PlayerSpinStop(object);
                            m224_PlayerSpinStop(other);
                        } else if (otherWork->unk_44 > work->unk_44) {
                            work->unk_16 = 1;
                            atan2df(object->trans.x - other->trans.x, -(object->trans.z - other->trans.z));
                            m224_PlayerKnockBack(other, object);
                            m224_PlayerSpinStop(object);
                        } else {
                            otherWork->unk_16 = 1;
                            atan2df(other->trans.x - object->trans.x, -(other->trans.z - object->trans.z));
                            m224_PlayerKnockBack(object, other);
                            m224_PlayerSpinStop(other);
                        }
                    } else {
                        otherWork->unk_16 = 1;
                        atan2df(other->trans.x - object->trans.x, -(other->trans.z - object->trans.z));
                        m224_PlayerKnockBack(object, other);
                    }
                } else if (work->unk_0E[i] & 4) {
                    m224_HitEffShow(object, object->trans.x, object->trans.y, object->trans.z);
                    omVibrate(work->playerId, 2, 2, 20);
                    if (otherWork->state == 1) {
                        if (otherWork->unk_44 == work->unk_44) {
                            m224_PlayerSpinStop(object);
                            m224_PlayerSpinStop(other);
                        } else if (otherWork->unk_44 > work->unk_44) {
                            work->unk_16 = 1;
                            atan2df(object->trans.x - other->trans.x, -(object->trans.z - other->trans.z));
                            m224_PlayerKnockBack(other, object);
                            m224_PlayerSpinStop(object);
                        } else {
                            otherWork->unk_16 = 1;
                            atan2df(other->trans.x - object->trans.x, -(other->trans.z - object->trans.z));
                            m224_PlayerKnockBack(object, other);
                            m224_PlayerSpinStop(other);
                        }
                    } else {
                        otherWork->unk_16 = 1;
                        atan2df(other->trans.x - object->trans.x, -(other->trans.z - object->trans.z));
                        m224_PlayerKnockBack(object, other);
                    }
                }
            }
        }
        if (object->trans.y < floorY) {
            object->trans.y = floorY;
            work->motSpeed = 4.0f;
            work->motDir = 1.0f;
            work->motState = 2;
            work->unk_34 = work->unk_38 = 0.0f;
            work->unk_0C = 0;
            m224_PlayerSpinStop(object);
            work->emitter->work[0] = 0;
            work->unk_06 = 0;
            work->unk_08 = 0;
            work->unk_64 = work->unk_68 = 0.0f;
            work->radius = 55.0f;
            m224_LandEffShow(object);
        }
    }
    work->unk_64 *= work->unk_6C;
    work->unk_68 *= work->unk_6C;
    if (fabs(work->unk_64) < 0.01f) {
        work->unk_64 = 0.0f;
    }
    if (fabs(work->unk_68) < 0.01f) {
        work->unk_68 = 0.0f;
    }
    if (work->unk_64 == 0.0f && work->unk_68 == 0.0f) {
        work->unk_16 = 0;
    } else {
        object->trans.x += work->unk_64;
        object->trans.z += work->unk_68;
    }
    omSetRot(object, object->rot.x, rotY, object->rot.z);
    if (object->rot.y >= 360.0f) {
        object->rot.y -= 360.0f;
    }
    Hu3DModelRotSet(object->model[1], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    if (floorY == -100000.0f) {
        Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    } else {
        work->unk_28 = 1.5 - fabs(object->trans.y - floorY) / 900.0 * 1.2f;
        if (work->unk_28 < 0.3f) {
            work->unk_28 = 0.3f;
        }
        Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelPosSet(object->model[2], object->trans.x, floorY + 1.0f, object->trans.z);
        Hu3DModelScaleSet(object->model[2], work->unk_28, 1.0f, work->unk_28);
    }
    if (work->unk_06 == 1) {
        Hu3DModelPosSet(object->model[3], object->trans.x, object->trans.y + 60.0f, object->trans.z);
    }
    m224_PlayerMotUpdate(object);
    if (object->trans.y < -45.0f && work->unk_08 == 1 && work->state != 2) {
        HuAudPlayerFXPlay(0x3D0, work->playerId);
        work->state = 2;
        work->unk_34 = work->unk_38 = work->unk_64 = work->unk_68 = 0.0f;
        m224_playerAliveCnt--;
    }
    work->prevPos.x = object->trans.x;
    work->prevPos.y = object->trans.y;
    work->prevPos.z = object->trans.z;
}

void m224_PlayerOutUpdate(omObjData *object) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    f32 rotY = object->rot.y;
    f32 floorY = m224_PlayerFloorYGet(object);
    Vec pos;
    Vec2f screenPos;

    if (work->unk_08 == 1) {
        if (work->unk_44 != 0.0f) {
            rotY += work->unk_44;
        }
        work->jumpTime += 1.0f;
        object->trans.y =
            work->jumpVel * work->jumpTime + work->jumpBaseY - work->jumpTime * 2.4f * work->jumpTime;
        if (work->unk_16 == 1) {
            object->trans.x += work->unk_64;
            object->trans.z += work->unk_68;
        }
        object->trans.x += work->unk_34;
        object->trans.z += work->unk_38;
    }
    work->unk_64 *= work->unk_6C;
    work->unk_68 *= work->unk_6C;
    if (fabs(work->unk_64) < 0.01f) {
        work->unk_64 = 0.0f;
    }
    if (fabs(work->unk_68) < 0.01f) {
        work->unk_68 = 0.0f;
    }
    if (work->unk_64 == 0.0f && work->unk_68 == 0.0f) {
        work->unk_16 = 0;
    } else {
        object->trans.x += work->unk_64;
        object->trans.z += work->unk_68;
    }
    omSetRot(object, object->rot.x, rotY, object->rot.z);
    if (object->rot.y >= 360.0f) {
        object->rot.y -= 360.0f;
    }
    Hu3DModelRotSet(object->model[1], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    if (floorY == -100000.0f) {
        Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    } else {
        work->unk_28 = 1.5 - fabs(object->trans.y - floorY) / 900.0 * 1.2f;
        if (work->unk_28 < 0.3f) {
            work->unk_28 = 0.3f;
        }
        Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelPosSet(object->model[2], object->trans.x, floorY + 1.0f, object->trans.z);
        Hu3DModelScaleSet(object->model[2], work->unk_28, 1.0f, work->unk_28);
    }
    if (work->unk_06 == 1) {
        Hu3DModelPosSet(object->model[3], object->trans.x, object->trans.y + 60.0f, object->trans.z);
    }
    m224_PlayerMotUpdate(object);
    if (object->trans.y < -5000.0f) {
        work->state = 3;
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        work->unk_06 = 0;
        Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        object->func = NULL;
    }
    pos.x = object->trans.x;
    pos.y = object->trans.y;
    pos.z = object->trans.z;
    Hu3DCam3Dto2D(0, &pos, &screenPos);
    if (screenPos.y > 240.0f && work->unk_18 == 0) {
        work->unk_18 = 1;
        PlayerFXPlay(0x286, work->playerId);
    }
    work->prevPos.x = object->trans.x;
    work->prevPos.y = object->trans.y;
    work->prevPos.z = object->trans.z;
}

void m224_PlayerSpinStop(omObjData *object) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);

    if (work->state != 2 && work->state != 3) {
        work->state = 0;
    }
    work->unk_44 = 0.0f;
    work->unk_48 = 0.0f;
    Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void m224_PlayerKnockBack(omObjData *object, omObjData *other) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    BounceNTrounceWork *otherWork = OM_GET_DATA_PTR(other, BounceNTrounceWork);
    f32 speed;
    f32 angle;

    speed = work->unk_44 / 160.0f * 22.0f + 20.0f;
    angle = atan2df(other->trans.x - object->trans.x, other->trans.z - object->trans.z);
    otherWork->unk_64 = sindf(angle) * speed;
    otherWork->unk_68 = cosdf(angle) * speed;
    otherWork->unk_6C = 0.8f;
}

void m224_PlayerJumpSet(omObjData *object, f32 vel) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);

    work->jumpVel = vel;
    work->jumpTime = 0.0f;
    work->jumpBaseY = object->trans.y;
}

void m224_PlayerMotUpdate(omObjData *object) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    f32 dir = work->motDir;
    f32 rate = Hu3DMotionGlobalSpeed;
    f32 time = Hu3DData[object->model[0]].motTime;

    if (work->motState == 2) {
        time += dir * work->motSpeed * rate;
        if (time > Hu3DMotion[Hu3DData[object->model[0]].motId].unk02) {
            work->motDir = -1.0f;
            time = Hu3DMotion[Hu3DData[object->model[0]].motId].unk02;
            work->motState = 4;
        }
    } else if (work->motState == 3) {
        time += work->motDir * work->motSpeed * Hu3DMotionGlobalSpeed;
        if (time < 0.0f) {
            time = 0.0f;
            work->motState = 1;
        }
    }
    Hu3DMotionTimeSet(object->model[0], time);
    Hu3DMotionTimeSet(object->model[1], time);
}

void m224_PlayerHitCheck(omObjData *object) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    BounceNTrounceWork *otherWork;
    omObjData *other;
    f32 dist;
    f32 minDist;
    f32 angle;
    s32 i;

    for (i = 0; i < 4; i++) {
        other = m224_playerObjTbl[i];
        if (object == other) {
            continue;
        }
        otherWork = OM_GET_DATA_PTR(other, BounceNTrounceWork);
        dist = m224_Dist2DCalc(other->trans.x, other->trans.z, object->trans.x, object->trans.z);
        minDist = HuSqrtf((work->radius + otherWork->radius) * (work->radius + otherWork->radius));
        if (!(dist < minDist)) {
            continue;
        }
        if (other->trans.y + 180.0f < object->trans.y) {
            continue;
        }
        if (object->trans.y + 180.0f < other->trans.y) {
            continue;
        }
        if (other->trans.x == object->trans.x && other->trans.z == object->trans.z) {
            rand8();
            rand8();
        }
        angle = -atan2df(other->trans.x - object->trans.x, -(other->trans.z - object->trans.z));
        if (object->trans.y < other->trans.y + 180.0f && other->trans.y + 180.0f - 40.0f < object->trans.y) {
            work->unk_0E[otherWork->playerId] |= 4;
            otherWork->unk_0E[work->playerId] |= 1;
            minDist -= dist;
            object->trans.x += sindf(angle) * minDist;
            object->trans.z += cosdf(angle) * minDist;
            object->trans.y = other->trans.y + 180.0f + 1.0f;
        } else if (other->trans.y < object->trans.y + 180.0f && object->trans.y + 180.0f < other->trans.y + 40.0f) {
            work->unk_0E[otherWork->playerId] |= 1;
            otherWork->unk_0E[work->playerId] |= 4;
            minDist -= dist;
            object->trans.x += sindf(angle) * minDist;
            object->trans.z += cosdf(angle) * minDist;
            object->trans.y = other->trans.y - 180.0f - 1.0f;
        } else {
            work->unk_0E[otherWork->playerId] |= 2;
            otherWork->unk_0E[work->playerId] |= 2;
            minDist -= dist;
            object->trans.x += sindf(angle) * minDist;
            object->trans.z += cosdf(angle) * minDist;
        }
    }
}

void m224_PlayerHitClear(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        BounceNTrounceWork *work = OM_GET_DATA_PTR(m224_playerObjTbl[i], BounceNTrounceWork);
        s32 j;

        for (j = 0; j < 4; j++) {
            work->unk_0E[j] = 0;
        }
    }
}

u16 m224_PlayerEndCheck(void) {
    f32 dists[4];
    u16 order[4];
    s32 count = 0;
    s32 i;
    s32 j;
    s32 k;
    BounceNTrounceWork *work;
    f32 dist;
    u16 temp;

    for (i = 0; i < 4; i++) {
        work = OM_GET_DATA_PTR(m224_playerObjTbl[i], BounceNTrounceWork);
        count += (work->state == 3);
        if (work->motState == 2 || work->motState == 4) {
            if (work->state != 4) {
                m224_playerObjTbl[i]->func = m224_PlayerEndObjInit;
                for (j = 0; j < 4; j++) {
                    dists[j] = m224_Dist2DCalc(
                        m224_endPosTbl[j].x, m224_endPosTbl[j].z,
                        m224_playerObjTbl[i]->trans.x, m224_playerObjTbl[i]->trans.z);
                    order[j] = j;
                }
                for (j = 0; j < 3; j++) {
                    for (k = j + 1; k < 4; k++) {
                        if (dists[order[j]] > dists[order[k]]) {
                            dist = dists[order[j]];
                            temp = order[j];
                            dists[order[j]] = dists[order[k]];
                            order[j] = order[k];
                            dists[order[k]] = dist;
                            order[k] = temp;
                        }
                    }
                }
                for (j = 0; j < 4; j++) {
                    if (m224_endPosUsedTbl[order[j]] != 1) {
                        work->unk_58 = m224_endPosTbl[order[j]];
                        m224_endPosUsedTbl[order[j]] = 1;
                        break;
                    }
                }
            } else {
                count += (m224_playerObjTbl[i]->work[0] == 0);
            }
        }
    }
    return count == 4;
}

void m224_PlayerEndObjInit(omObjData *object) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);

    work->state = 4;
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[3]].motId, 0, 6, 0);
    object->work[0] = 8;
    object->func = m224_PlayerEndWaitObjMain;
}

void m224_PlayerEndWaitObjMain(omObjData *object) {
    if (object->work[0] != 0) {
        object->work[0]--;
    } else {
        Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[1]].motId, 0, 6, 2);
        object->func = m224_PlayerEndObjMain;
    }
}

void m224_PlayerEndObjMain(omObjData *object) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    BounceNTrounceWork *otherWork;
    f32 angle;
    f32 dist;
    f32 step;
    s32 i;

    for (i = 0; i < 4; i++) {
        otherWork = OM_GET_DATA_PTR(m224_playerObjTbl[i], BounceNTrounceWork);
        if (otherWork->state == 4) {
            continue;
        }
        if (work->unk_0E[i] & 1 || work->unk_0E[i] & 2) {
            angle = atan2df(-m224_playerObjTbl[i]->trans.x, -m224_playerObjTbl[i]->trans.z);
            otherWork->unk_64 = sindf(angle) * 6.0f;
            otherWork->unk_68 = cosdf(angle) * 6.0f;
            otherWork->unk_6C = 0.9f;
            dist = m224_Dist2DCalc(work->unk_58.x, work->unk_58.z, object->trans.x, object->trans.z);
            step = (dist < 50.0f) ? dist : 50.0f;
            angle = atan2df(work->unk_58.x - object->trans.x, work->unk_58.z - object->trans.z);
            object->trans.x += sindf(angle) * step;
            object->trans.z += cosdf(angle) * step;
            Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
            Hu3DModelPosSet(object->model[2], object->trans.x, 1.0f, object->trans.z);
        }
    }
}

void m224_HitEffShow(omObjData *object, f32 x, f32 y, f32 z) {
    Hu3DModelAttrSet(object->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelPosSet(object->model[4], object->trans.x, object->trans.y + 200.0f, object->trans.z);
    Hu3DModelRotSet(object->model[4], 0.0f, CRot.y, 0.0f);
    Hu3DMotionAttrSet(object->model[4], 3, 0);
    Hu3DMotionTimeSet(object->model[4], 0.0f);
}

void m224_LandEffShow(omObjData *object) {
    Hu3DModelAttrSet(object->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelPosSet(object->model[6], object->trans.x, object->trans.y + 5.0f, object->trans.z);
    Hu3DMotionAttrSet(object->model[6], 3, 0);
    Hu3DMotionTimeSet(object->model[6], 0.0f);
}

void m224_PlayerComInputGet(omObjData *object, s8 *stickX, s8 *stickY, u16 *btn) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    BounceNTrounceWork *targetWork;
    u16 tile;
    u16 chance;
    f32 dist;
    f32 angle;

    *stickY = 0;
    *stickX = 0;
    *btn = 0;
    if (work->floorTile != NULL) {
        u16 state = OM_GET_DATA_PTR(work->floorTile, BounceNTrounceTileWork)->state;

        if ((state == 1 || state == 2) && work->unk_7E == 0) {
            tile = m224_PlayerComTileGet(object);
            work->unk_7E = 1;
            work->aiState = 1;
            work->aiTargetPos.x = m224_tilePosTbl[tile].x;
            work->aiTargetPos.y = m224_tilePosTbl[tile].y;
            work->aiTargetPos.z = m224_tilePosTbl[tile].z;
        }
    }
    if (work->aiState == 0) {
        m224_PlayerComStateDecide(object);
    }
    switch (work->aiState) {
        case 1:
            if (m224_Dist2DCalc(object->trans.x, object->trans.z, work->aiTargetPos.x,
                                               work->aiTargetPos.z) < 60.0f) {
                work->aiState = 0;
                work->unk_7E = 0;
                return;
            }
            if (work->motState == 2) {
                *btn |= A_BUTTON;
            }
            angle = atan2df(work->aiTargetPos.z - object->trans.z, work->aiTargetPos.x - object->trans.x) + CRot.y;
            *stickX = cosdf(angle) * 80.0f;
            *stickY = -sindf(angle) * 80.0f;
            break;
        case 2:
            if (work->aiWait != 0) {
                work->aiState = 0;
            } else {
                work->aiWait--;
            }
            return;
        case 3:
            targetWork = OM_GET_DATA_PTR(work->aiTarget, BounceNTrounceWork);
            if (work->unk_A2 == 1) {
                switch (GwPlayer[work->playerId].cpu_difficulty) {
                    case 0:
                        chance = 100;
                        break;
                    case 1:
                        chance = 50;
                        break;
                    case 2:
                        chance = 30;
                        break;
                    case 3:
                        chance = 10;
                        break;
                }
                if (rand8() < chance) {
                    work->aiState = 0;
                    work->unk_A2 = 0;
                }
            }
            if (targetWork->floorTile == NULL || targetWork->state == 2 || targetWork->state == 3) {
                work->aiState = 0;
                return;
            }
            dist = m224_Dist2DCalc(work->aiTarget->trans.x, work->aiTarget->trans.z,
                                                  object->trans.x, object->trans.z);
            if (dist < 80.0f && work->state != 1) {
                work->aiState = 0;
            }
            if (dist < 150.0f && work->unk_0A != 0) {
                *btn |= Z_TRIG;
            }
            if (dist < 400.0f && work->motState == 2) {
                *btn |= A_BUTTON;
            }
            angle = atan2df(work->aiTarget->trans.z - object->trans.z, work->aiTarget->trans.x - object->trans.x) + CRot.y;
            *stickX = cosdf(angle) * 80.0f;
            *stickY = -sindf(angle) * 80.0f;
            break;
        case 5:
            if (m224_Dist2DCalc(object->trans.x, object->trans.z, work->aiTargetPos.x,
                                               work->aiTargetPos.z) < 100.0f) {
                work->aiState = work->unk_A4;
                return;
            }
            angle = atan2df(work->aiTargetPos.z - object->trans.z, work->aiTargetPos.x - object->trans.x) + CRot.y;
            *stickX = cosdf(angle) * 80.0f;
            *stickY = -sindf(angle) * 80.0f;
            break;
        case 4:
            if (OM_GET_DATA_PTR(m224_tileObjTbl[work->aiTile], BounceNTrounceTileWork)->state != 0) {
                work->aiState = 0;
                return;
            }
            if (m224_Dist2DCalc(object->trans.x, object->trans.z, work->aiTilePos.x,
                                               work->aiTilePos.z) < 100.0f) {
                work->aiState = 0;
                return;
            }
            angle = atan2df(work->aiTilePos.z - object->trans.z, work->aiTilePos.x - object->trans.x) + CRot.y;
            *stickX = cosdf(angle) * 80.0f;
            *stickY = -sindf(angle) * 80.0f;
            break;
    }
}

void m224_PlayerComStateDecide(omObjData *object) {
    omObjData *targets[4];
    s16 tiles[9];
    u16 aiStates[4][8] = {
        { 2, 2, 2, 3, 2, 4, 4, 3 },
        { 2, 3, 2, 3, 2, 3, 4, 3 },
        { 2, 3, 2, 3, 2, 3, 4, 3 },
        { 2, 3, 3, 3, 2, 3, 3, 3 },
    };
    BounceNTrounceWork *work;
    s32 count;
    s16 tileCount;
    s16 tile;
    s32 i;

    work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    work->aiState = aiStates[GwPlayer[work->playerId].cpu_difficulty][rand8() & 7];
    while (TRUE) {
        switch (work->aiState) {
            case 2:
                work->aiWait = rand8() % 30 + 20;
                return;
            case 3:
                count = 0;
                for (i = 0; i < 4; i++) {
                    if (i != work->playerId &&
                        OM_GET_DATA_PTR(m224_playerObjTbl[i], BounceNTrounceWork)->state < 2) {
                        targets[count++] = m224_playerObjTbl[i];
                    }
                }
                if (count == 0) {
                    work->aiState = 2;
                    break;
                }
                if (count == 1) {
                    work->aiTarget = targets[0];
                } else {
                    work->aiTarget = targets[rand8() % count];
                }
                m224_PlayerComRouteSet(object, 3);
                return;
            case 4:
                tileCount = 0;
                for (i = 0; i < 9; i++) {
                    if (OM_GET_DATA_PTR(m224_tileObjTbl[i], BounceNTrounceTileWork)->state == 0) {
                        tiles[tileCount++] = i;
                    }
                }
                if (tileCount == 1) {
                    tile = tiles[0];
                } else {
                    tile = tiles[rand8() % tileCount];
                }
                work->aiTarget = m224_tileObjTbl[tile];
                work->aiTilePos.x = m224_tilePosTbl[tile].x;
                work->aiTilePos.y = m224_tilePosTbl[tile].y;
                work->aiTilePos.z = m224_tilePosTbl[tile].z;
                work->aiTile = tile;
                return;
        }
    }
}

s32 m224_PlayerComRouteSet(omObjData *object, s16 arg1) {
    BounceNTrounceWork *objWork = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    BounceNTrounceWork *work;
    s16 tile;
    s16 targetTile;
    s16 nextTile;

    tile = m224_TileNoGet(object->trans.x, object->trans.z);
    targetTile = m224_TileNoGet(objWork->aiTarget->trans.x, objWork->aiTarget->trans.z);
    work = objWork; // Second pointer copy is needed for register allocation to match.
    if (abs(tile - targetTile) == 1 || abs(tile - targetTile) == 3) {
        return 0;
    }
    if (tile == 0 || tile == 2 || tile == 6 || tile == 8) {
        if (abs(tile - targetTile) != 2 && abs(tile - targetTile) != 6) {
            return 0;
        }
        if (tile - targetTile == -2) {
            nextTile = tile + 1;
        } else if (tile - targetTile == -6) {
            nextTile = tile + 3;
        } else if (tile - targetTile == 2) {
            nextTile = tile - 1;
        } else if (tile - targetTile == 6) {
            nextTile = tile - 3;
        } else {
            goto end;
        }
        if (OM_GET_DATA_PTR(m224_tileObjTbl[nextTile], BounceNTrounceTileWork)->state != 1) {
            work->aiState = 5;
            work->unk_A4 = arg1;
            work->aiTargetPos.x = m224_tilePosTbl[nextTile].x;
            work->aiTargetPos.y = m224_tilePosTbl[nextTile].y;
            work->aiTargetPos.z = m224_tilePosTbl[nextTile].z;
        }
    }
end:
    // The original has no return value here.
}

s16 m224_PlayerComTileGet(omObjData *object) {
    f32 dists[9]; // Unused stack space retained from the original function.
    f32 minDist = 1000000.0f;
    s32 result = 0;
    u16 i;

    for (i = 0; i < 9; i++) {
        if (OM_GET_DATA_PTR(m224_tileObjTbl[i], BounceNTrounceTileWork)->state == 0) {
            if (HuSqrtf((object->trans.x - m224_tilePosTbl[i].x) *
                            (object->trans.x - m224_tilePosTbl[i].x) +
                        (object->trans.z - m224_tilePosTbl[i].z) *
                            (object->trans.z - m224_tilePosTbl[i].z)) < minDist) {
                result = i;
            }
        }
    }
    return result;
}

void m224_IntroObjMain(omObjData *object) {
    omObjData *player;
    BounceNTrounceWork *work;
    f32 angle;
    s32 i;

    switch (m224_introPhase) {
        case 0:
            WipeCreateIn(WIPE_TYPE_PREV, 16);
            m224_introPhase = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                m224_introPhase = 2;
            }
            break;
        case 2:
            player = m224_playerObjTbl[0];
            work = OM_GET_DATA_PTR(player, BounceNTrounceWork);
            if (work->motState == 2) {
                if (++m224_introJumpCnt == 6) {
                    m224_introJumpF = 1;
                }
            }
            for (i = 0; i < 4; i++) {
                player = m224_playerObjTbl[i];
                work = OM_GET_DATA_PTR(player, BounceNTrounceWork);
                if (work->motState == 2 && m224_introJumpF == 1) {
                    m224_introBtnTbl[i] |= A_BUTTON;
                }
            }
            if (m224_introJumpF == 1) {
                m224_introPhase = 3;
            }
            break;
        case 3:
            if (m224_playerObjTbl[0]->trans.y > 500.0f) {
                for (i = 0; i < 4; i++) {
                    m224_introBtnTbl[i] |= Z_TRIG;
                }
                m224_introPhase = 4;
            }
            break;
        case 4:
            player = m224_playerObjTbl[0];
            work = OM_GET_DATA_PTR(player, BounceNTrounceWork);
            if (work->motState == 2) {
                for (i = 0; i < 4; i++) {
                    player = m224_playerObjTbl[i];
                    work = OM_GET_DATA_PTR(player, BounceNTrounceWork);
                    angle = atan2df(-player->trans.x, -player->trans.z);
                    player->rot.y = angle;
                    angle -= 180.0f;
                    work->unk_64 = sindf(angle) * 30.0f;
                    work->unk_68 = cosdf(angle) * 30.0f;
                    work->unk_6C = 0.925f;
                    work->unk_16 = 1;
                    work->unk_0A = 0;
                    player->func = NULL;
                    omVibrate(work->playerId, 2, 2, 20);
                }
                m224_introPhase = 5;
            }
            break;
        case 5:
            for (i = 0; i < 4; i++) {
                player = m224_playerObjTbl[i];
                work = OM_GET_DATA_PTR(player, BounceNTrounceWork);
                player->trans.x += work->unk_64;
                player->trans.z += work->unk_68;
                Hu3DModelPosSet(player->model[1], player->trans.x, player->trans.y, player->trans.z);
                Hu3DModelPosSet(player->model[2], player->trans.x, player->trans.y + 1.0f, player->trans.z);
                Hu3DModelRotSet(player->model[1], player->rot.x, player->rot.y, player->rot.z);
                work->unk_64 *= work->unk_6C;
                work->unk_68 *= work->unk_6C;
                if (fabs(work->unk_64) < 1.0) {
                    work->unk_64 = 0.0f;
                }
                if (fabs(work->unk_68) < 1.0) {
                    work->unk_68 = 0.0f;
                }
                if (work->unk_64 == 0.0f && work->unk_68 == 0.0f) {
                    m224_introPhase = 6;
                    HuAudSeqPlay(0x37);
                }
            }
            break;
        case 6:
            for (i = 0; i < 4; i++) {
                m224_playerObjTbl[i]->func = m224_PlayerObjMain;
            }
            omDelObj(object);
            m224_introObj = NULL;
            MgFlowStatSet(MG_STATE_START);
            break;
    }
}

void m224_FinishObjMain(omObjData *object) {
    omObjData *player;
    BounceNTrounceWork *work;
    f32 dist;
    f32 diff;
    s32 i;

    switch (m224_finishPhase) {
        case 0:
            m224_cameraObj->work[0] = 0;
            m224_finishTimer = 45;
            m224_finishPhase = 1;
            for (i = 0; i < 4; i++) {
                work = OM_GET_DATA_PTR(m224_playerObjTbl[i], BounceNTrounceWork);
                work->radius = 50.0f;
            }
            break;
        case 1:
            if (m224_finishTimer == 0) {
                if (m224_finishDecideF == 1) {
                    m224_finishPhase = m224_finishNextPhase;
                }
            } else {
                m224_finishTimer--;
            }
            if (m224_finishDecideF != 0) {
                break;
            }
            if (m224_playerAliveCnt != 0) {
                if (m224_PlayerEndCheck() != 1) {
                    break;
                }
                if (m224_playerAliveCnt == 1) {
                    for (i = 0; i < 4; i++) {
                        work = OM_GET_DATA_PTR(m224_playerObjTbl[i], BounceNTrounceWork);
                        if (work->state == 4) {
                            m224_winner = i;
                            m224_mgFlow.winners[0] = m224_winner;
                            m224_finishNextPhase = 3;
                            m224_finishDecideF = 1;
                        }
                    }
                    break;
                }
            }
            m224_mgFlow.resultType = MG_RESULT_DRAW;
            m224_finishNextPhase = 2;
            m224_finishDecideF = 1;
            break;
        case 2:
            MgFlowStatSet(MG_STATE_RESULT);
            for (i = 0; i < 4; i++) {
                work = OM_GET_DATA_PTR(m224_playerObjTbl[i], BounceNTrounceWork);
                if (work->state == 4) {
                    Hu3DMotionShiftSet(m224_playerObjTbl[i]->model[1],
                                       Hu3DData[m224_playerObjTbl[i]->motion[5]].motId, 0, 6, 0);
                }
            }
            m224_finishPhase = 6;
            break;
        case 3:
            player = m224_playerObjTbl[m224_winner];
            m224_cameraZoomTarget = 1350.0f;
            dist = HuSqrtf(player->trans.x * player->trans.x + player->trans.z * player->trans.z);
            if (dist > 560.0f && (player->trans.z > 0.0f || player->trans.x > 0.0f)) {
                m224_cameraZoomTarget += (dist - 560.0f) / 113.0f * 400.0f;
            }
            m224_cameraZoomSpeed = (m224_cameraZoomTarget - CZoom) / 30.0f;
            Hu3DMotionShiftSet(m224_playerObjTbl[m224_winner]->model[1],
                               Hu3DData[m224_playerObjTbl[m224_winner]->motion[2]].motId, 0,
                               6, 0);
            m224_finishPhase = 4;
            break;
        case 4:
            CZoom += m224_cameraZoomSpeed;
            if (CZoom < m224_cameraZoomTarget) {
                CZoom = m224_cameraZoomTarget;
                m224_finishPhase = 5;
            }
            if (m224_winnerTurnF != 0) {
                break;
            }
            player = m224_playerObjTbl[m224_winner];
            if (player->rot.y >= 360.0f) {
                player->rot.y -= 360.0f;
            }
            if (player->rot.y < 0.0f) {
                player->rot.y += 360.0f;
            }
            diff = CRot.y + 0.0f - player->rot.y;
            if (diff < 0.0f) {
                diff += 360.0f;
            }
            if (diff < 180.0f) {
                if (diff > 8.0f) {
                    player->rot.y += 8.0f;
                } else {
                    player->rot.y += diff;
                }
            } else if (360.0f - diff > 8.0f) {
                player->rot.y -= 8.0f;
            } else {
                player->rot.y -= 360.0f - diff;
            }
            Hu3DModelRotSet(player->model[1], player->rot.x, player->rot.y, player->rot.z);
            if (fabs(player->rot.y - (CRot.y + 0.0f)) < 0.1f) {
                Hu3DMotionShiftSet(player->model[1], Hu3DData[player->motion[1]].motId, 0, 6, 0);
                m224_winnerTurnF = 1;
            }
            break;
        case 5:
            Hu3DMotionShiftSet(m224_playerObjTbl[m224_winner]->model[1],
                               Hu3DData[m224_playerObjTbl[m224_winner]->motion[4]].motId, 0,
                               6, 0);
            MgFlowStatSet(MG_STATE_RESULT);
            HuAudCharVoicePlay(omCharModelNoTbl[GwPlayer[m224_winner].chr][0] | 0x2F);
            GwPlayer[m224_winner].bonusCoin = 10;
            m224_finishPhase = 6;
            break;
        case 6:
            omDelObj(object);
            m224_finishObj = NULL;
            break;
    }
}

void m224_CameraZoomObjMain(omObjData *object) {
    f32 maxY;
    s32 i;

    if (object->work[0] != 0) {
        maxY = 0.0f;
        for (i = 0; i < 4; i++) {
            if (maxY < m224_playerObjTbl[i]->trans.y) {
                maxY = m224_playerObjTbl[i]->trans.y;
            }
        }
        if (maxY > 300.0f) {
            maxY -= 300.0f;
            CZoom = maxY * 700.0f / 700.0f + 2100.0f;
            if (CZoom > 2800.0f) {
                CZoom = 2800.0f;
            }
        } else {
            CZoom = 2100.0f;
        }
    }
}

void m224_SpinEffHook(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *modelData = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = modelData->unk58;
    s16 i;
    s32 tile;
    f32 floorY;

    for (i = 0; i < hmf->unk1A; i++, particle++) {
        if (particle->unk08 > 0.0f) {
            particle->unk0C += particle->unk18;
            particle->unk10 += particle->unk1C;
            particle->unk14 += particle->unk20;
            particle->unk18 *= particle->unk24;
            particle->unk20 *= particle->unk2C;
            particle->unk1C *= particle->unk28;
            particle->unk08 += particle->unk04;
            if (particle->unk08 < 0.0f) {
                particle->unk08 = 0.0f;
            }
            tile = m224_TileNoGet(particle->unk0C, particle->unk14);
            if (tile >= 0 && tile < 9) {
                floorY = m224_tileObjTbl[tile]->trans.y;
                if (particle->unk10 < floorY && particle->unk10 > floorY - 300.0f) {
                    particle->unk08 = 0.0f;
                }
            }
        }
    }
    modelData->unk02++;
}

void m224_SpinEffObjMain(omObjData *object) {
    omObjData *player = (omObjData *)object->work[1];
    BounceNTrounceWork *playerWork = OM_GET_DATA_PTR(player, BounceNTrounceWork);
    BounceNTrounceEmitterWork *work;
    HmfModelData_UnkBC_Struct *modelData;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    HmfData *hmf;
    s32 i;
    f32 angle;
    f32 speed;

    if (object->work[0] == 0) {
        return;
    }
    if (object->work[2] != 0) {
        object->work[2]--;
        return;
    }
    work = OM_GET_DATA_PTR(object, BounceNTrounceEmitterWork);
    modelData = Hu3DData[player->model[5]].unkBC;
    hmf = Hu3DData[player->model[5]].hmf;
    particle = modelData->unk58;
    for (i = 0; i < hmf->unk1A; i++, particle++) {
        if (particle->unk08 <= 0.0f) {
            break;
        }
    }
    if (i == hmf->unk1A) {
        return;
    }
    object->work[2] = work->interval;
    angle = work->angle;
    work->angle += work->angleStep;
    if (work->angle >= 360.0f) {
        work->angle -= 360.0f;
    }
    particle->unk0C = player->trans.x;
    particle->unk10 = player->trans.y + 120.0f;
    particle->unk14 = player->trans.z;
    speed = playerWork->unk_44 / 7.0f;
    if (speed < 10.0f) {
        speed = 10.0f;
    }
    particle->unk18 = sindf(angle) * speed;
    particle->unk20 = cosdf(angle) * speed;
    particle->unk1C = -10.0f;
    particle->unk2C = particle->unk24 = 0.95f;
    particle->unk28 = 1.05f;
    particle->unk04 = -0.22f;
    particle->unk08 = 10.0f;
}

f32 m224_Dist2DCalc(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    return HuSqrtf((arg0 - arg2) * (arg0 - arg2) + (arg1 - arg3) * (arg1 - arg3));
}

s16 m224_TileNoGet(f32 arg0, f32 arg1) {
    s32 x;
    s32 y;
    s16 index;

    arg0 += 450.0f;
    arg1 += 450.0f;
    x = arg0 / 300.0f;
    y = arg1 / 300.0f;
    index = x + y * 3;
    return (index >= 0 && index < 9) ? index : -1;
}
