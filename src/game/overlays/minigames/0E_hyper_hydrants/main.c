#include "common.h"
#include "game/input.h"
#include "game/pause.h"
#include "gcc/memory.h"
#include "game/mallocblock.h"
#include "game/overlays/opening.h"
#include "game/overlays/minigame.h"
#include "hyper_hydrants.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

typedef struct {
    s8 unk00;
    s8 unk01;
    s8 unk02;
    s8 unk03;
    s8 unk04;
    s8 unk05;
    s8 unk06;
    s8 unk07;
    s16 unk08;
    s16 unk0A;
    f32 unk0C;
    f32 unk10;
    f32 unk14;
    s8 unk18;
    s8 unk19;
    s8 unk1A;
    s8 unk1B;
    s16 unk1C;
    s16 unk1E;
} HyperHydrantsFireWork;

typedef struct {
    s8 unk00[3];
    s8 unk03;
    s8 unk04;
    f32 unk08;
    u8 unk0C[0xA8];
} HyperHydrantsMaskData;

typedef struct {
    s16 spread;
    f32 angle;
    f32 speed;
} HyperHydrantsSprayData;

typedef struct {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    s8 unk10;
    u16 unk12;
    s32 unk14;
    union {
        s16 value;
        u8 bytes[2];
    } charge;
    s16 unk1A;
    s8 unk1C;
    s16 unk1E;
} HyperHydrantsCharacterData;

Vec m214_sprayer0Pos = { -900.0f, 0.0f, -30.0f };
Vec m214_pumper0Pos = { -720.0f, 0.0f, -30.0f };
Vec m214_sprayer1Pos = { 750.0f, 0.0f, -30.0f };
Vec m214_pumper1Pos = { 930.0f, 0.0f, -30.0f };
s8 m214_fireSpawnNoTbl[] = { 5, 5 };
s16 m214_scoreDigitPosTbl[2][2][2] = {
    { { 59, 32 }, { 71, 32 } },
    { { 276, 32 }, { 288, 32 } },
};
s8 m214_score0 = 0;
s8 m214_score1 = 0;
f32 m214_cameraPosZ = 570.285f;
f32 m214_cameraAtZ = -375.0f;
s32 m214_exitTimer = 0;
s8 m214_exitF = 0;
s8 m214_playerSlotNo = 0;
s8 m214_fireSizeTbl[][16] = {
    { 0, 1, 2, 1, 0, 2, 1, 0, 1, 2, 1, 0, 0, 2, 1, 2 },
    { 2, 0, 1, 2, 1, 1, 0, 1, 2, 0, 2, 1, 2, 0, 0, 1 },
    { 1, 2, 1, 0, 2, 0, 2, 2, 0, 1, 0, 2, 1, 1, 2, 0 },
};
s8 m214_fireSpawnFTbl[2] = { 0, 0 };
s8 m214_irisOpenF = 0;

extern MinigameFlow m214_mgFlow;
extern omObjData *m214_fireObjTbl[2][5];

extern s8 m214_pumpPowerTbl[2];
extern s8 m214_sprayWidthTbl[2];
extern s16 m214_pumpIdleTbl[2];
extern s16 m214_backAnim;
extern s16 m214_irisAnim;
extern s16 m214_frameAnim;
extern s16 m214_frameSprGrp;
extern s16 m214_backSprGrp;
extern s16 m214_irisSprGrpTbl[2];
extern s8 m214_hoseCnt;
extern u32 omCharModelNoTbl[][6];
extern s32 omCharMotTbl[][6];
extern s8 m214_introRandNo;
extern s16 m214_pumpSeNoTbl[2];
extern Vec m214_hydrantPosTbl[2];
extern HyperHydrantsHosePoint *m214_hoseTbl[2][6];

extern u8 omAllPauseF;
extern s32 m214_bigFireCnt;
extern s32 m214_fireCnt;
extern s8 m214_pumper0No;
extern s8 m214_pumper1No;
extern s8 m214_sprayer0No;
extern s8 m214_sprayer1No;
extern omObjData *m214_bigFireObjTbl[];
extern s8 m214_sprayCnt;
extern s16 m214_irisSizeX;
extern s16 m214_irisSizeY;
extern u8 *m214_irisTexTbl[2];
extern s32 m214_irisRadius;
extern s32 m214_irisX;
extern s32 m214_irisY;
extern s8 m214_firePatternNo;
extern s16 m214_scoreIconEspTbl[2];
extern s16 m214_scoreXEspTbl[2];
extern s16 m214_scoreDigitEspTbl[2][2];

void m214_FlowInit(MinigameFlow *flow);
void m214_CameraInit(void);
void m214_CameraObjMain(omObjData *object);
void m214_MainObjMain(omObjData *object);
void m214_BigFireObjInit(omObjData *object);
void m214_FireObjInit(omObjData *object);
void m214_FireObjMain(omObjData *object);
void m214_SprayObjInit(omObjData *object);
void m214_IrisObjInit(omObjData *object);
void m214_PlayerObjInit(omObjData *object);
void m214_HoseObjInit(omObjData *object);
void m214_ScoreObjInit(omObjData *object);
s16 m214_SePanPlay(s16 soundId, s16 side, s8 playerSound, s16 player);
void m214_CameraViewSet(s8 camera);
void m214_ScoreObjMain(omObjData *object);
void m214_IrisUpdate(void);
void m214_IrisObjMain(omObjData *object);
void m214_HoseObjMain(omObjData *object);
void m214_FireReset(omObjData *object);
void m214_SprayObjMain(omObjData *object);
void m214_PumperUpdate(omObjData *object);
void m214_PlayerObjMain(omObjData *object);
void m214_SprayParticleHook(s16 model);
void m214_SprayEmit(s16 model, Vec *position, HyperHydrantsSprayData *data, s8 count);
void m214_BigFireObjMain(omObjData *object);
void m214_FireIntroMove(omObjData *object);
void m214_FireMove(omObjData *object);
void m214_FireShrink(omObjData *object);
void m214_BigFireBounce(omObjData *object);

void m214_ObjectSetup(void) {
    omObjData *object;
    s32 i;
    s32 j;

    MapCollInit(0x20);
    Hu3DQuadPoolInit(&mgQuadPool, 0x40);
    Hu3DSprModelInit(0x40);
    omInitObjMan(0x20, 0);
    omGameSysInit();
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    MgFieldStatClear();
    m214_CameraInit();
    m214_FlowInit(&m214_mgFlow);
    MgFlowInit(&m214_mgFlow);
    Hu3DGLightColorSet(1, 0x40, 0x40, 0x40);
    Hu3DGLightDirSet(1, 0.0f, 0.0f, 100.0f);
    object = omAddObj(0x7FDA, 0, 0, -1, m214_CameraObjMain);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    m214_CameraObjMain(object);
    object = omAddObj(0, 0, 0, -1, m214_MainObjMain);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    for (i = 0; i < 2; i++) {
        m214_bigFireObjTbl[i] = omAddObj(0, 2, 0, -1, m214_BigFireObjInit);
    }
    m214_firePatternNo = (rand8() * 3) >> 8;
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 5; i++) {
            m214_fireObjTbl[j][i] = omAddObj(0, 3, 0, -1, m214_FireObjInit);
        }
    }
    for (i = 0; i < 2; i++) {
        omAddObj(1, 10, 0, -1, m214_SprayObjInit);
    }
    omAddObj(1, 0, 0, -1, m214_IrisObjInit);
    for (i = 0; i < 4; i++) {
        mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(2, 3, 5, -1, m214_PlayerObjInit);
    }
    for (i = 0; i < 2; i++) {
        omAddObj(3, 6, 0, -1, m214_HoseObjInit);
    }
    omAddObj(3, 0, 0, -1, m214_ScoreObjInit);
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
}

void m214_FlowInit(MinigameFlow *flow) {
    s32 i;

    mgFlowSeqTime = 10;
    flow->state = MG_STATE_OPENING;
    flow->type = MINIGAME_1V3;
    flow->timerMode = MG_TIMER_COUNT_DOWN;
    flow->timeDisp = MG_TIME_DISP_COUNTDOWN;
    flow->newRecord = FALSE;
    flow->gauge = MG_GAUGE_NONE;
    flow->resultType = MG_RESULT_NONE;
    flow->startDelay = 80;
    flow->timer = 900;
    flow->timeLimit = -1;
    flow->finishDelay = 75;
    flow->resultDelay = 150;
    for (i = 0; i < 4; i++) {
        flow->gaugeValue[i] = 0;
        flow->winners[i] = 0xFF;
    }
}

void m214_CameraObjMain(omObjData *object) {
    m214_CameraViewSet(0);
    m214_CameraViewSet(1);
}

void m214_CameraPanUpdate(s8 camera) {
    Vec pos;
    Vec at;
    Vec up;

    if (camera == 0) {
        pos.x = -850.0f;
    } else {
        pos.x = 850.0f;
    }
    pos.y = 1046.895f;
    pos.z = m214_cameraPosZ;
    if (camera == 0) {
        at.x = -850.0f;
    } else {
        at.x = 850.0f;
    }
    at.y = 0;
    m214_cameraAtZ += 2.0f;
    if (m214_cameraAtZ > at.y) {
        m214_cameraAtZ = at.y;
    }
    at.z = m214_cameraAtZ;
    up.x = 0;
    up.y = 1050.25f;
    up.z = 566.575f;
    Hu3DCameraPosSetV(camera, &pos, &at, &up);
    Hu3DCamUpdateMtx(camera);
}

void m214_CameraViewSet(s8 camera) {
    Vec pos;
    Vec at;
    Vec up;

    if (camera == 0) {
        pos.x = -850.0f;
    } else {
        pos.x = 850.0f;
    }
    pos.y = 1046.895f;
    pos.z = 570.285f;
    if (camera == 0) {
        at.x = -850.0f;
    } else {
        at.x = 850.0f;
    }
    at.y = 0;
    at.z = -375.0f;
    up.x = 0;
    up.y = 1050.25f;
    up.z = 566.575f;
    Hu3DCameraPosSetV(camera, &pos, &at, &up);
    Hu3DCamUpdateMtx(camera);
}

void m214_CameraInit(void) {
    CamSetupInit(2);
    CamSetupMapCullAddMulti(2);
    ScissorSet(0, 0.0f, 0.0f, 160.0f, SCREEN_HEIGHT);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 35.883f, 80.0f, 8000.0f);
    ScissorSet(1, 160.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(1, 35.883f, 80.0f, 8000.0f);
}

void m214_MainObjMain(omObjData *object) {
    if (omPauseChk() + omAllPauseF == 0) {
        if (m214_exitF == 0 && omSysExitReq == 1) {
            HuAudFXAllStop();
            if (!(HuAudStat & 4)) {
                HuAudSeqFadeOut(30);
            } else {
                HuAudSeqStop();
            }
            MgFlowStatSet(MG_STATE_EXIT);
            m214_exitF = 1;
        }
        MgFieldStatUpdate();
        switch (MgFlowMain()) {
            case 0:
                mgFlowSeqNo = 52;
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                if (m214_exitTimer == 0) {
                    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                } else if (WipeStatGet() == 0 && !(HuAudStat & 4)) {
                    omOvlReturnEx(1);
                }
                m214_exitTimer++;
                break;
        }
    }
}

void m214_PlayerObjInit(omObjData *object) {
    s32 character;
    u32 model;
    s32 motion;
    MgPlayerWork *playerData;
    HyperHydrantsCharacterData *data;

    character = (s8)GwPlayer[m214_playerSlotNo].chr;
    model = omCharModelNoTbl[character][0];
    motion = omCharMotTbl[character][0];
    MgShadowAltSet(1);
    MgPlayerCreate(object, model, motion, m214_playerSlotNo, 0xAC9, 0xAD9);
    playerData = object->data;
    object->rot.x = object->rot.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    playerData->unk158 = HuMemAllocTag(sizeof(HyperHydrantsCharacterData), TAG_OVERLAY);
    memset(object->data, 0, sizeof(HyperHydrantsCharacterData));
    data = playerData->unk158;
    data->charge.value = 0;
    data->unk1A = 0;
    data->unk10 = 0;
    data->unk12 = B_BUTTON;
    data->unk1E = 0;
    data->unk1C = 0;
    omObjMotionRead(object, 0, CharMotionDataNumGet(character, 0));
    omObjMotionRead(object, 1, CharMotionDataNumGet(character, 0x14));
    omObjMotionRead(object, 2, CharMotionDataNumGet(character, 0x7B));
    omObjMotionRead(object, 3, CharMotionDataNumGet(character, 0x2F));
    omObjMotionRead(object, 4, CharMotionDataNumGet(character, 0x36));
    if (m214_playerSlotNo == 0) {
        m214_introRandNo = (rand8() * 5U) >> 7;
    }
    switch (GwPlayer[playerData->unk59].group) {
        case 0:
            object->trans.x = m214_sprayer0Pos.x;
            object->trans.y = m214_sprayer0Pos.y;
            object->trans.z = m214_sprayer0Pos.z;
            m214_sprayer0No = playerData->unk59;
            object->rot.y = 180.0f;
            object->model[2] = Hu3DModelRead(0x2F0004, 0xA99);
            Hu3DModelRotSet(object->model[2], object->rot.x, object->rot.y, object->rot.z);
            Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[2]].motId, 0, 1, 2);
            Hu3DModelPosSet(object->model[2], object->trans.x, 0, object->trans.z);
            Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
            Hu3DModelCameraSet(object->model[1], HU3D_CAM0);
            Hu3DModelCameraSet(object->model[2], HU3D_CAM0);
            m214_pumpSeNoTbl[0] = m214_SePanPlay(0x369, 0, 1, playerData->unk59);
            HuAudFXVolSet(m214_pumpSeNoTbl[0], 0);
            break;
        case 1:
            object->trans.x = m214_pumper0Pos.x;
            object->trans.y = m214_pumper0Pos.y;
            object->trans.z = m214_pumper0Pos.z;
            m214_pumper0No = playerData->unk59;
            object->rot.y = 0;
            object->model[2] = Hu3DModelRead(0x2F0005, 0xA89);
            Hu3DModelAttrSet(object->model[2], HU3D_ATTR_PRIMCOLOR, HU3D_ATTR_PRIMCOLOR);
            Hu3DModelPrimColorSet(object->model[2], 0, 0, 0, 0);
            Hu3DModelEnvColorSet(object->model[2], 16, 16, 16, 0);
            Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[1]].motId, 0, 1, 2);
            if ((model >> 16) == 6) {
                object->trans.z -= 48.7f;
                Hu3DModelPosSet(object->model[2], object->trans.x, 0, object->trans.z + 48.7f);
            } else {
                Hu3DModelPosSet(object->model[2], object->trans.x, 0, object->trans.z);
            }
            Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
            Hu3DModelCameraSet(object->model[1], HU3D_CAM0);
            Hu3DModelCameraSet(object->model[2], HU3D_CAM0);
            break;
        case 2:
            object->trans.x = m214_sprayer1Pos.x;
            object->trans.y = m214_sprayer1Pos.y;
            object->trans.z = m214_sprayer1Pos.z;
            m214_sprayer1No = playerData->unk59;
            object->rot.y = 180.0f;
            object->model[2] = Hu3DModelRead(0x2F0006, 0xA99);
            Hu3DModelRotSet(object->model[2], object->rot.x, object->rot.y, object->rot.z);
            Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[2]].motId, 0, 1, 2);
            Hu3DModelPosSet(object->model[2], object->trans.x, 0, object->trans.z);
            Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
            Hu3DModelCameraSet(object->model[1], HU3D_CAM1);
            Hu3DModelCameraSet(object->model[2], HU3D_CAM1);
            m214_pumpSeNoTbl[1] = m214_SePanPlay(0x369, 1, 1, playerData->unk59);
            HuAudFXVolSet(m214_pumpSeNoTbl[1], 0);
            break;
        case 3:
            object->trans.x = m214_pumper1Pos.x;
            object->trans.y = m214_pumper1Pos.y;
            object->trans.z = m214_pumper1Pos.z;
            m214_pumper1No = playerData->unk59;
            object->rot.y = 0;
            object->model[2] = Hu3DModelRead(0x2F0007, 0xA89);
            Hu3DModelAttrSet(object->model[2], HU3D_ATTR_PRIMCOLOR, HU3D_ATTR_PRIMCOLOR);
            Hu3DModelPrimColorSet(object->model[2], 0, 0, 0, 0);
            Hu3DModelEnvColorSet(object->model[2], 16, 16, 16, 0);
            Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[1]].motId, 0, 1, 2);
            if ((model >> 16) == 6) {
                object->trans.z -= 48.7f;
                Hu3DModelPosSet(object->model[2], object->trans.x, 0, object->trans.z + 48.7f);
            } else {
                Hu3DModelPosSet(object->model[2], object->trans.x, 0, object->trans.z);
            }
            Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
            Hu3DModelCameraSet(object->model[1], HU3D_CAM1);
            Hu3DModelCameraSet(object->model[2], HU3D_CAM1);
            break;
    }
    data->unk00 = sindf(object->rot.y - 40.0f);
    data->unk04 = cosdf(object->rot.y - 40.0f);
    data->unk08 = sindf(object->rot.y - 140.0f);
    data->unk0C = cosdf(object->rot.y - 140.0f);
    Hu3DMotionAttrSet(object->model[0], 1, 1);
    Hu3DMotionTimeSet(object->model[2], 0);
    object->func = m214_PlayerObjMain;
    Hu3DModelPosSet(object->model[1], object->trans.x, 0, object->trans.z);
    Hu3DModelScaleSet(object->model[1], object->scale.x, object->scale.y, object->scale.z);
    m214_playerSlotNo++;
}

void m214_PlayerObjMain(omObjData *object) {
    MgPlayerWork *playerData;
    HyperHydrantsCharacterData *data;
    s8 side;
    s32 character;

    switch (MgFlowStatGet()) {
        case MG_STATE_OPENING:
        case MG_STATE_START:
            Hu3DMotionTimeSet(object->model[2], Hu3DData[object->model[0]].motTime);
            break;
        case MG_STATE_PLAY:
            playerData = object->data;
            data = playerData->unk158;
            if (playerData->unk59 == m214_pumper0No || playerData->unk59 == m214_pumper1No) {
                m214_PumperUpdate(object);
                break;
            }
            if (!(GwPlayer[playerData->unk59].stat & PLAYER_IS_CPU)) {
                if ((HuPadStkX[playerData->unk57] < 0 ? -HuPadStkX[playerData->unk57] : HuPadStkX[playerData->unk57]) > 0 && object->rot.y > 120.0f && object->rot.y < 240.0f) {
                    Hu3DMotionAttrSet(object->model[0], 1, 2);
                } else {
                    Hu3DMotionAttrSet(object->model[0], 1, 1);
                }
            }
            data->unk00 = sindf(object->rot.y - 40.0f);
            data->unk04 = cosdf(object->rot.y - 40.0f);
            data->unk08 = sindf(object->rot.y - 140.0f);
            data->unk0C = cosdf(object->rot.y - 140.0f);
            side = playerData->unk59 != m214_sprayer0No;
            switch (m214_pumpPowerTbl[side]) {
                case 0:
                    HuAudFXVolSet(m214_pumpSeNoTbl[side], 0);
                    break;
                case 1:
                    HuAudFXVolSet(m214_pumpSeNoTbl[side], 84);
                    HuAudFXPitchSet(m214_pumpSeNoTbl[side], -300);
                    break;
                case 2:
                    HuAudFXVolSet(m214_pumpSeNoTbl[side], 91);
                    HuAudFXPitchSet(m214_pumpSeNoTbl[side], -200);
                    break;
                case 3:
                    HuAudFXVolSet(m214_pumpSeNoTbl[side], 98);
                    HuAudFXPitchSet(m214_pumpSeNoTbl[side], -100);
                    break;
                case 4:
                    HuAudFXVolSet(m214_pumpSeNoTbl[side], 112);
                    HuAudFXPitchSet(m214_pumpSeNoTbl[side], 100);
                    break;
                case 5:
                    HuAudFXVolSet(m214_pumpSeNoTbl[side], 119);
                    HuAudFXPitchSet(m214_pumpSeNoTbl[side], 200);
                    break;
                default:
                    HuAudFXVolSet(m214_pumpSeNoTbl[side], 127);
                    HuAudFXPitchSet(m214_pumpSeNoTbl[side], 300);
                    break;
            }
            break;
        case MG_STATE_FINISH:
            playerData = object->data;
            if (MgFlowStatTimeGet() == 0) {
                HuAudFXStop(m214_pumpSeNoTbl[0]);
                HuAudFXStop(m214_pumpSeNoTbl[1]);
                HuAudFXPlay(0x36B);
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[0]].motId, 0, 30, 2);
                Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                switch (GwPlayer[playerData->unk59].group) {
                    case 0:
                    case 1:
                        if (m214_score0 > m214_score1) {
                            m214_mgFlow.resultType = MG_RESULT_WIN_2;
                            if (m214_mgFlow.winners[0] == 0xFF) {
                                m214_mgFlow.winners[0] = playerData->unk59;
                            } else {
                                m214_mgFlow.winners[1] = playerData->unk59;
                            }
                        } else if (m214_score0 == m214_score1) {
                            m214_mgFlow.resultType = MG_RESULT_DRAW;
                        }
                        break;
                    case 2:
                    case 3:
                        if (m214_score0 < m214_score1) {
                            m214_mgFlow.resultType = MG_RESULT_WIN_2;
                            if (m214_mgFlow.winners[0] == 0xFF) {
                                m214_mgFlow.winners[0] = playerData->unk59;
                            } else {
                                m214_mgFlow.winners[1] = playerData->unk59;
                            }
                        } else if (m214_score0 == m214_score1) {
                            m214_mgFlow.resultType = MG_RESULT_DRAW;
                        }
                        break;
                }
            }
            if ((object->rot.y > 0.0f ? object->rot.y : 0.0f - object->rot.y) > 20.0f) {
                object->rot.y -= 20.0f;
            } else {
                object->rot.y = 0.0f;
            }
            if ((omCharModelNoTbl[GwPlayer[playerData->unk59].chr][0] >> 16) == 6 &&
                (m214_pumper0No == playerData->unk59 || m214_pumper1No == playerData->unk59)) {
                object->trans.z += 5.0f;
                if (object->trans.z > 18.7f) {
                    object->trans.z = 18.7f;
                }
                Hu3DModelPosSet(object->model[1], object->trans.x, 0, object->trans.z);
            }
            break;
        case MG_STATE_RESULT:
            if (mgFlowResultF != 0) {
                playerData = object->data;
                if (playerData->unk59 == m214_mgFlow.winners[0] ||
                    playerData->unk59 == m214_mgFlow.winners[1]) {
                    Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[3]].motId, 0, 30, 2);
                    switch (GwPlayer[playerData->unk59].chr) {
                        case 0:
                        default:
                            character = 2;
                            break;
                        case 1:
                            character = 3;
                            break;
                        case 2:
                            character = 7;
                            break;
                        case 3:
                            character = 4;
                            break;
                        case 4:
                            character = 5;
                            break;
                        case 5:
                            character = 6;
                            break;
                        case 6:
                            character = 8;
                            break;
                        case 7:
                            character = 9;
                            break;
                    }
                    HuAudCharVoicePlay((character << 16) | 0x2F);
                    GwPlayer[playerData->unk59].bonusCoin += 10;
                } else {
                    Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[4]].motId, 0, 30, 2);
                }
            } else if (Hu3DData[object->model[0]].motTime >= 118.0f) {
                Hu3DMotionAttrSet(object->model[0], 1, 1);
            }
            break;
        case MG_STATE_EXIT:
            break;
    }
}

void m214_PumperUpdate(omObjData *object) {
    MgPlayerWork *playerData;
    HyperHydrantsCharacterData *data;
    u16 pressA = 0;
    u16 pressB = 0;
    s8 side;
    s16 press;
    s8 random;
    f32 time;
    f32 end;

    playerData = object->data;
    data = playerData->unk158;
    time = Hu3DData[object->model[0]].motTime;
    end = Hu3DMotion[Hu3DData[object->model[0]].motId].unk02;
    side = GwPlayer[playerData->unk59].group >= 2;
    if (GwPlayer[playerData->unk59].stat & PLAYER_IS_CPU) {
        if ((time == end) | (time == 0.0f)) {
            random = (rand8() * 100) >> 8;
            switch (GwPlayer[playerData->unk59].cpu_difficulty) {
                case 3:
                    press = 1;
                    break;
                case 2:
                    press = random < 90;
                    break;
                case 1:
                default:
                    press = random < 40;
                    break;
                case 0:
                    press = random < 30;
                    break;
            }
            if (m214_pumpPowerTbl[side] == 0) {
                m214_pumpPowerTbl[side] = 1;
                press = 1;
            }
        } else {
            press = 0;
        }
        if (press) {
            if (time == end) {
                pressB = 1;
            } else if (time == 0.0f) {
                pressA = 1;
            }
        }
    } else {
        pressA = (HuPadBtnDown[playerData->unk57] & A_BUTTON) != 0;
        pressB = (HuPadBtnDown[playerData->unk57] & (B_BUTTON | Z_TRIG)) != 0;
    }
    if ((pressA != 0) & (pressB != 0)) {
        if (data->unk12 == A_BUTTON) {
            pressA = 0;
        } else {
            pressB &= data->unk12 != B_BUTTON ? 0xFFFF : 0;
        }
    } else if (pressA) {
        pressA &= data->unk12 != A_BUTTON ? 0xFFFF : 0;
    } else if (pressB) {
        pressB &= data->unk12 != B_BUTTON ? 0xFFFF : 0;
    }
    if (pressA) {
        Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[1]].motId, (s16)time, 1, 2);
        data->unk10 = 1;
        m214_SePanPlay(0x368, side, 1, playerData->unk59);
        data->unk12 = A_BUTTON;
    } else if (pressB) {
        Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[1]].motId, (s16)time, 1, 4);
        data->unk10 = 2;
        m214_SePanPlay(0x367, side, 1, playerData->unk59);
        data->unk12 = B_BUTTON;
    }
    if (data->unk10 == 1) {
        if (data->charge.value < 9) {
            data->charge.value++;
        }
        if (time >= end - 2.0f) {
            Hu3DMotionAttrSet(object->model[0], 1, 1);
            Hu3DMotionAttrSet(object->model[2], 1, 1);
            time = end;
            data->unk10 = 0;
        }
        m214_pumpIdleTbl[side] = 0;
    } else if (data->unk10 == 2) {
        end = 0.0f;
        if (time == end) {
            Hu3DMotionAttrSet(object->model[0], 1, 1);
            Hu3DMotionAttrSet(object->model[2], 1, 1);
            time = end;
            data->unk10 = 0;
        } else {
            data->unk1C = 0;
        }
        m214_pumpIdleTbl[side] = 0;
    } else {
        if (data->charge.value == 0) {
            m214_pumpPowerTbl[side] = 0;
        } else if (data->charge.value < 2) {
            m214_pumpPowerTbl[side] = 1;
        } else if (data->charge.value < 3) {
            m214_pumpPowerTbl[side] = 2;
        } else if (data->charge.value < 4) {
            m214_pumpPowerTbl[side] = 3;
        } else if (data->charge.value < 6) {
            m214_pumpPowerTbl[side] = 4;
        } else if (data->charge.value < 8) {
            m214_pumpPowerTbl[side] = 5;
        } else {
            m214_pumpPowerTbl[side] = 6;
        }
        if (m214_pumpIdleTbl[side] >= 2) {
            if (data->charge.value > 0) {
                data->charge.value--;
            }
        }
        m214_pumpIdleTbl[side]++;
    }
    Hu3DMotionTimeSet(object->model[0], time);
    Hu3DMotionTimeSet(object->model[2], time);
    if (time == 0.0f) {
        data->unk1C ^= 1;
    } else {
        data->unk1C = 0;
    }
    if (data->unk1C) {
        Hu3DModelPrimColorSet(object->model[2], 64, 64, 64, 0);
        Hu3DModelEnvColorSet(object->model[2], 0, 0, 0, 0);
    } else {
        Hu3DModelPrimColorSet(object->model[2], 0, 0, 0, 0);
        Hu3DModelEnvColorSet(object->model[2], 16, 16, 16, 0);
    }
    if (data->unk1A >= 31) {
        m214_pumpPowerTbl[side] = data->charge.bytes[1];
        data->unk1A = 0;
        data->charge.value = 0;
    } else {
        data->unk1A++;
    }
}

void m214_SprayObjInit(omObjData *object) {
    HyperHydrantsSprayData *data;
    omObjData *player;

    object->work[0] = m214_sprayCnt;
    object->func = m214_SprayObjMain;
    object->model[0] = Hu3DModelRead(0x2F000B, 0x689);
    if (m214_sprayCnt == 0) {
        player = mgPlayerObjTbl[m214_sprayer0No];
        Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
    } else {
        player = mgPlayerObjTbl[m214_sprayer1No];
        Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    }
    object->trans.x = player->trans.x;
    object->trans.z = player->trans.z;
    object->trans.y = 40.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelObjAttrSet(object->model[0], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(object->model[0]);
    Hu3DModelVtxBufMake(object->model[0]);
    Hu3DModelDynamicFree(object->model[0]);
    Hu3DParticleCreate(object->model[0], -1, 0, m214_SprayParticleHook);
    data = HuMemAllocTag(sizeof(HyperHydrantsSprayData), TAG_OVERLAY);
    object->data = data;
    memset(data, 0, sizeof(HyperHydrantsSprayData));
    data->spread = 5;
    data->angle = 180.0f;
    data->speed = 50.0f;
    Hu3DData[object->model[0]].unkBC->unk08.f = m214_sprayCnt;
    m214_sprayCnt++;
}

void m214_SprayObjMain(omObjData *object) {
    HyperHydrantsSprayData *data;
    HyperHydrantsCharacterData *characterData;
    omObjData *player;
    MgPlayerWork *playerData;
    Vec position;
    f32 angle;
    f32 farthest;
    s16 side;
    s16 target;
    s16 count;
    s16 i;
    s8 playerIndex;
    s8 port;
    s8 particles;
    s16 maxSpread;

    if (MgFlowStatGet() != MG_STATE_PLAY) {
        return;
    }
    if (object->work[0] == 0) {
        if (m214_pumpPowerTbl[0] == 0) {
            return;
        }
        side = 0;
        playerIndex = m214_sprayer0No;
    } else {
        if (m214_pumpPowerTbl[1] == 0) {
            return;
        }
        side = 1;
        playerIndex = m214_sprayer1No;
    }
    player = mgPlayerObjTbl[playerIndex];
    playerData = player->data;
    characterData = playerData->unk158;
    port = playerData->unk57;
    data = object->data;
    count = 0;
    if (GwPlayer[playerIndex].stat & PLAYER_IS_CPU) {
        farthest = -1000.0f;
        target = 4;
        for (i = 0; i < 5; i++) {
            if (m214_fireObjTbl[side][i]->trans.z > farthest) {
                farthest = m214_fireObjTbl[side][i]->trans.z;
                target = i;
            }
            if (m214_fireObjTbl[side][i]->trans.z >= -250.0f) {
                count++;
            }
        }
        angle = atan2df(m214_fireObjTbl[side][target]->trans.x - mgPlayerObjTbl[playerIndex]->trans.x,
                        m214_fireObjTbl[side][target]->trans.z - mgPlayerObjTbl[playerIndex]->trans.z);
        while (angle >= 360.0f) {
            angle -= 360.0f;
        }
        while (angle < 0.0f) {
            angle += 360.0f;
        }
        if (ABS((s32)angle - data->angle) > 5.0f) {
            Hu3DMotionAttrSet(mgPlayerObjTbl[playerIndex]->model[0], 1, 2);
            switch (GwPlayer[playerIndex].cpu_difficulty) {
                case 3:
                    if ((s32)angle < data->angle) {
                        data->angle -= 4.0f;
                    } else {
                        data->angle += 4.0f;
                    }
                    break;
                case 2:
                    if (((rand8() * 2) >> 8) == 0) {
                        if ((s32)angle < data->angle) {
                            data->angle -= 4.0f;
                        } else {
                            data->angle += 4.0f;
                        }
                    }
                    break;
                case 1:
                default:
                    if (((rand8() * 3) >> 8) == 0) {
                        if ((s32)angle < data->angle) {
                            data->angle -= 2.0f;
                        } else {
                            data->angle += 2.0f;
                        }
                    }
                    break;
                case 0:
                    if (((rand8() * 5) >> 8) == 0) {
                        if ((s32)angle < data->angle) {
                            data->angle -= 1.0f;
                        } else {
                            data->angle += 1.0f;
                        }
                    }
                    break;
            }
        } else {
            Hu3DMotionAttrSet(mgPlayerObjTbl[playerIndex]->model[0], 1, 1);
        }
        if (data->angle > 240.0f) {
            data->angle = 240.0f;
        }
        if (data->angle < 120.0f) {
            data->angle = 120.0f;
        }
        if (count >= 2) {
            HuPadBtn[port] |= A_BUTTON;
        } else {
            HuPadBtn[port] &= ~A_BUTTON;
        }
    } else if (ABS(HuPadStkX[port]) > 40) {
        if (HuPadStkX[port] < 0) {
            data->angle += 5.0f;
            if (data->angle > 240.0f) {
                data->angle = 240.0f;
            }
        } else if (HuPadStkX[port] > 0) {
            data->angle -= 5.0f;
            if (data->angle < 120.0f) {
                data->angle = 120.0f;
            }
        }
    } else if (ABS(HuPadStkX[port]) > 20) {
        if (HuPadStkX[port] < 0) {
            data->angle += 2.0f;
            if (data->angle > 240.0f) {
                data->angle = 240.0f;
            }
        } else if (HuPadStkX[port] > 0) {
            data->angle -= 2.0f;
            if (data->angle < 120.0f) {
                data->angle = 120.0f;
            }
        }
    }
    player->rot.y = data->angle;
    Hu3DModelRotSet(player->model[2], player->rot.x, player->rot.y, player->rot.z);
    if ((u16)HuPadBtn[port] & A_BUTTON) {
        data->spread += 3;
        maxSpread = m214_pumpPowerTbl[side] * 15;
        if (data->spread > maxSpread) {
            data->spread = maxSpread;
        }
    } else {
        data->spread -= 3;
        if (data->spread < 5) {
            data->spread = 5;
        }
    }
    m214_sprayWidthTbl[side] = data->spread;
    if (data->spread > 50) {
        position.x = characterData->unk00 * 110.0f + player->trans.x;
        position.z = characterData->unk04 * 110.0f + player->trans.z;
    } else {
        position.x = characterData->unk00 * 55.0f + player->trans.x;
        position.z = characterData->unk04 * 55.0f + player->trans.z;
    }
    position.y = 40.0f;
    if (data->spread > 20) {
        particles = 28;
    } else {
        particles = 10;
    }
    m214_SprayEmit(object->model[0], &position, data, particles);
}

void m214_SprayEmit(s16 model, Vec *position, HyperHydrantsSprayData *data, s8 count) {
    HmfData *hmf;
    HmfModelData_UnkBC_Struct *modelData;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 particleCount;
    s16 halfSpread;
    s16 i;
    f32 angle;
    f32 speed;
    f32 offset;
    f32 random;
    Vec velocity;

    hmf = Hu3DData[model].hmf;
    modelData = Hu3DData[model].unkBC;
    particleCount = hmf->unk1A;
    halfSpread = data->spread / 2;
    angle = data->angle - halfSpread;
    speed = data->speed + ((rand8() * 10) >> 8) * 0.1f;
    random = (rand8() * data->spread) >> 8;
    velocity.x = sindf(angle + random) * speed;
    random = (rand8() * data->spread) >> 8;
    velocity.y = sindf(-halfSpread + random) * speed;
    random = (rand8() * data->spread) >> 8;
    velocity.z = cosdf(angle + random) * speed;
    particle = modelData->unk58;
    for (i = 0; i < particleCount; i++, particle++) {
        if (particle->unk10 <= 0.0f) {
            memcpy(&particle->unk24, &velocity, sizeof(velocity));
            offset = ((rand8() * 10) >> 8) * 0.1f;
            particle->unk0C = offset * velocity.x + position->x;
            particle->unk10 = offset * velocity.y + position->y;
            particle->unk14 = offset * velocity.z + position->z;
            if (data->spread >= 21) {
                particle->unk08 = (rand8() % 8) + 2;
            } else {
                particle->unk08 = (rand8() % 3) + 2;
            }
            if (--count == 0) {
                break;
            }
            speed = data->speed + ((rand8() * 10) >> 8) * 0.1f;
            random = (rand8() * data->spread) >> 8;
            velocity.x = sindf(angle + random) * speed;
            random = (rand8() * data->spread) >> 8;
            velocity.y = sindf(-halfSpread + random) * speed;
            random = (rand8() * data->spread) >> 8;
            velocity.z = cosdf(angle + random) * speed;
        }
    }
}

void m214_SprayParticleHook(s16 model) {
    HmfData *hmf;
    HmfModelData_UnkBC_Struct *modelData;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    MgPlayerWork *characterData;
    omObjData *target;
    HyperHydrantsFireWork *data;
    s16 particleCount;
    s16 j;
    s16 i;
    s32 side;
    s32 port;
    s32 hit;
    s32 hitEnd;
    f32 limit;
    f32 oldZ;
    f32 nextZ;
    f32 targetZ;
    f32 distance;
    s32 threshold;

    hmf = Hu3DData[model].hmf;
    modelData = Hu3DData[model].unkBC;
    particleCount = hmf->unk1A;
    side = modelData->unk08.f;
    if (modelData->unk02 == 0) {
        modelData->unk04 &= ~4;
        for (i = 0, particle = modelData->unk58; i < particleCount; particle++, i++) {
            particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
            particle->unk24 = particle->unk28 = particle->unk2C = 0.0f;
            particle->unk08 = 0.0f;
            particle->unk04 = 1.0f;
        }
        modelData->unk02++;
    }
    particle = modelData->unk58;
    if (side == 0) {
        characterData = mgPlayerObjTbl[m214_sprayer0No]->data;
    } else {
        characterData = mgPlayerObjTbl[m214_sprayer1No]->data;
    }
    port = characterData->unk57;
    limit = ((u16)HuPadBtn[port] & A_BUTTON) ? -250.0f : -500.0f;
    for (i = 0; i < particleCount; particle++, i++) {
        if (particle->unk10 > 0.0f) {
            if (particle->unk14 < limit) {
                particle->unk08 = 0.0f;
                particle->unk10 = 0.0f;
            } else {
                oldZ = particle->unk14;
                nextZ = oldZ + particle->unk2C;
                for (j = 0; j < 5; j++) {
                    target = m214_fireObjTbl[side][j];
                    data = target->data;
                    if (data->unk10 == 0.0f) {
                        continue;
                    }
                    targetZ = target->trans.z;
                    distance = target->trans.x - particle->unk0C > 0.0f ? target->trans.x - particle->unk0C : 0.0f - (target->trans.x - particle->unk0C);
                    if (nextZ < oldZ) {
                        hit = nextZ < targetZ;
                        hitEnd = targetZ < oldZ;
                    } else {
                        hit = oldZ < targetZ;
                        hitEnd = targetZ < nextZ;
                    }
                    if ((hit & hitEnd) && distance < data->unk10 * target->scale.x) {
                        if ((u16)HuPadBtn[port] & A_BUTTON) {
                            particle->unk10 = particle->unk08 = 0.0f;
                        }
                        // TODO: do-while(0) required to match (raises the hoisted 1's
                        // register-allocation priority above the loop counter i)
                        do {
                            data->unk19 = 1;
                        } while (0);
                        break;
                    }
                }
            }
            particle->unk0C += particle->unk24;
            particle->unk10 += particle->unk28 - 1.0f;
            particle->unk14 += particle->unk2C;
            switch (m214_pumpPowerTbl[side]) {
                case 0:
                    particle->unk10 = particle->unk08 = 0.0f;
                    particle->unk24 = particle->unk28 = particle->unk2C = 0.0f;
                    break;
                case 1:
                    particle->unk24 *= 0.6f;
                    particle->unk28 *= 0.6f;
                    particle->unk2C *= 0.6f;
                    if (m214_sprayWidthTbl[side] >= 6) {
                        particle->unk28 -= 75.0f;
                    } else {
                        particle->unk28 -= 2.5f;
                    }
                    break;
                case 2:
                    particle->unk24 *= 0.7f;
                    particle->unk28 *= 0.7f;
                    particle->unk2C *= 0.7f;
                    if (m214_sprayWidthTbl[side] >= 6) {
                        particle->unk28 -= 52.5f;
                    } else {
                        particle->unk28 -= 1.75f;
                    }
                    break;
                case 3:
                    particle->unk24 *= 0.8f;
                    particle->unk28 *= 0.8f;
                    particle->unk2C *= 0.8f;
                    if (m214_sprayWidthTbl[side] >= 6) {
                        particle->unk28 -= 45.0f;
                    } else {
                        particle->unk28 -= 1.5f;
                    }
                    break;
                case 4:
                    particle->unk24 *= 0.8f;
                    particle->unk28 *= 0.8f;
                    particle->unk2C *= 0.8f;
                    if (m214_sprayWidthTbl[side] >= 6) {
                        particle->unk28 -= 30.0f;
                    } else {
                        particle->unk28 -= 1.0f;
                    }
                    break;
                case 5:
                    particle->unk24 *= 0.9f;
                    particle->unk28 *= 0.9f;
                    particle->unk2C *= 0.9f;
                    if (m214_sprayWidthTbl[side] >= 6) {
                        particle->unk28 -= 15.0f;
                    } else {
                        particle->unk28 -= 0.5f;
                    }
                    break;
                default:
                    particle->unk24 *= 0.99f;
                    particle->unk28 *= 0.99f;
                    particle->unk2C *= 0.99f;
                    if (m214_sprayWidthTbl[side] >= 6) {
                        particle->unk28 -= 15.0f;
                    } else {
                        particle->unk28 -= 0.5f;
                    }
                    break;
            }
        } else {
            particle->unk08 = 0.0f;
        }
    }
    for (j = 0; j < 5; j++) {
        target = m214_fireObjTbl[side][j];
        data = target->data;
        if (data->unk19 == 1) {
            if (m214_pumpPowerTbl[side] > 0) {
                MgPlayerEffSet(target, 2, target->trans.x, 100.0f, target->trans.z + 50.0f, 0.0f, 0.0f);
                if (data->unk18 == 1) {
                    data->unk1A = 1;
                }
                data->unk18++;
            }
            threshold = 15;
            if ((u16)HuPadBtn[port] & A_BUTTON) {
                threshold = 30;
            }
            if (data->unk04 == 0 && data->unk18 >= threshold) {
                data->unk04 = 1;
                data->unk18 = 0;
            }
            data->unk19 = 0;
        } else {
            data->unk18 = 0;
        }
    }
}

void m214_BigFireObjInit(omObjData *object) {
    Vec position;
    Vec2f screen;
    s16 model;
    HyperHydrantsFireWork *data;

    object->func = m214_BigFireObjMain;
    object->data = HuMemAllocTag(sizeof(HyperHydrantsFireWork), TAG_OVERLAY);
    data = object->data;
    memset(data, 0, sizeof(HyperHydrantsFireWork));
    data->unk00 = m214_bigFireCnt;
    data->unk03 = 0;
    data->unk14 = 0;
    if (data->unk00 == 0) {
        object->trans.x = -800.0f;
    } else {
        object->trans.x = 800.0f;
    }
    object->trans.y = 800.0f;
    object->trans.z = -700.0f;
    object->scale.x = object->scale.y = object->scale.z = 3.0f;
    position.x = object->trans.x;
    position.y = object->trans.y + 200.0f;
    position.z = object->trans.z;
    if (data->unk00 == 0) {
        Hu3DCam3Dto2D(0, &position, &screen);
    } else {
        Hu3DCam3Dto2D(1, &position, &screen);
    }
    m214_irisX = screen.x;
    m214_irisY = screen.y;
    model = object->model[0] = Hu3DModelRead(0xA008A, 0x289);
    if (data->unk00 == 0) {
        Hu3DAnimRead(Hu3DData[model].hmf, 0xA008C, "c201n_00_DEF");
        Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
    } else {
        Hu3DAnimLink(Hu3DData[model].hmf, 0, 0, "c201n_00_DEF");
        Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    }
    Hu3DModelRemakeStatic(model);
    Hu3DModelDynamicFree(model);
    object->model[1] = Hu3DModelRead(0x2F0003, 0x99);
    Hu3DModelPosSet(object->model[1], object->trans.x, 0, object->trans.z);
    data->unk0C = 0.1f;
    Hu3DModelScaleSet(object->model[1], data->unk0C, data->unk0C, data->unk0C);
    m214_bigFireCnt++;
}

void m214_BigFireObjMain(omObjData *object) {
    Vec position;
    Vec2f screen;
    HyperHydrantsFireWork *data = object->data;
    HyperHydrantsFireWork *otherData;

    switch (MgFlowStatGet()) {
        case MG_STATE_OPENING:
            if (data->unk00 == 0) {
                position.x = object->trans.x + 50.0f;
                position.y = object->trans.y + 120.0f;
                position.z = object->trans.z;
                Hu3DCam3Dto2D(0, &position, &screen);
                m214_irisX = screen.x;
                m214_irisY = screen.y;
                if (data->unk03 == 0) {
                    object->trans.y -= 40.0f;
                    if (object->trans.y < 0.0f) {
                        m214_SePanPlay(0x366, 0, 1, 0);
                        data->unk03 = 1;
                        omVibrate(0, 10, 0, 10);
                        omVibrate(1, 10, 0, 10);
                        omVibrate(2, 10, 0, 10);
                        omVibrate(3, 10, 0, 10);
                    }
                } else if (data->unk03 == 1) {
                    m214_BigFireBounce(object);
                }
                data->unk0C += 0.5f;
                if (data->unk0C > object->scale.x / 2.0f) {
                    data->unk0C = object->scale.x / 2.0f;
                }
            } else {
                otherData = m214_bigFireObjTbl[0]->data;
                object->trans.y = m214_bigFireObjTbl[0]->trans.y;
                data->unk0C = otherData->unk0C;
                data->unk03 = otherData->unk03;
                if (data->unk03 == 0 && object->trans.y < 0.0f) {
                    m214_SePanPlay(0x366, 1, 1, 1);
                }
            }
            Hu3DModelScaleSet(object->model[1], data->unk0C, data->unk0C, data->unk0C);
            break;
        case MG_STATE_START:
            object->trans.y = 0;
            data->unk03 = 0;
            break;
        case MG_STATE_PLAY:
            m214_BigFireBounce(object);
            break;
        case MG_STATE_FINISH:
        case MG_STATE_RESULT:
        case MG_STATE_EXIT:
            object->scale.x -= 0.4f;
            if (object->scale.x < 0.0f) {
                object->scale.x = 0.0f;
            }
            object->scale.y = object->scale.z = object->scale.x;
            data->unk0C = object->scale.x / 2.0f;
            Hu3DModelScaleSet(object->model[1], data->unk0C, data->unk0C, data->unk0C);
            break;
    }
}

void m214_BigFireBounce(omObjData *object) {
    HyperHydrantsFireWork *data = object->data;

    if (data->unk03 == 1) {
        if (data->unk14 < 1080.0f) {
            object->trans.y = sindf(data->unk14) * 50.0f + 0.0f;
            data->unk14 += 45.0f;
            if ((s32)data->unk14 % 180 == 0) {
                data->unk14 += 180.0f;
            }
        } else {
            object->trans.y = 0.0f;
            data->unk14 = 0.0f;
            data->unk03 = 2;
        }
    }
}

void m214_FireObjInit(omObjData *object) {
    s16 model;
    HyperHydrantsFireWork *data;

    object->func = m214_FireObjMain;
    object->data = HuMemAllocTag(sizeof(HyperHydrantsFireWork), TAG_OVERLAY);
    data = object->data;
    memset(data, 0, sizeof(HyperHydrantsFireWork));
    if (m214_fireCnt < 5) {
        data->unk02 = 0;
    } else {
        data->unk02 = 1;
    }
    data->unk00 = m214_fireCnt % 5;
    data->unk10 = 50.0f;
    data->unk03 = rand8() >> 7;
    data->unk04 = 0;
    data->unk08 = (rand8() >> 5) * 15;
    data->unk18 = 0;
    data->unk19 = 0;
    data->unk14 = 0;
    data->unk05 = 0;
    data->unk06 = 2;
    data->unk0A = (rand8() >> 5) * 15;
    data->unk1A = 0;
    data->unk1E = 0;
    object->trans.x = m214_bigFireObjTbl[data->unk02]->trans.x;
    object->trans.z = m214_bigFireObjTbl[data->unk02]->trans.z;
    object->trans.y = 0;
    object->rot.x = object->rot.y = object->rot.z = object->trans.y;
    switch (m214_fireSizeTbl[m214_firePatternNo][data->unk00]) {
        case 0:
            object->scale.x = object->scale.y = object->scale.z = 1.0f;
            data->unk0C = 0.5f;
            data->unk01 = 1;
            break;
        case 1:
            object->scale.x = object->scale.y = object->scale.z = 1.25f;
            data->unk0C = 0.625f;
            data->unk01 = 2;
            break;
        case 2:
        default:
            object->scale.x = object->scale.y = object->scale.z = 1.5f;
            data->unk0C = 0.75f;
            data->unk01 = 3;
            break;
    }
    model = object->model[0] = Hu3DModelRead(0x2F0002, 9);
    if (m214_fireCnt == 0) {
        Hu3DAnimRead(Hu3DData[model].hmf, 0xA008C, "c201n_00_DEF");
    } else {
        Hu3DAnimLink(Hu3DData[model].hmf, 0, 0, "c201n_00_DEF");
    }
    Hu3DModelRemakeStatic(model);
    Hu3DModelDynamicFree(model);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    object->model[1] = Hu3DModelRead(0x2F0003, 0x99);
    Hu3DModelPosSet(object->model[1], object->trans.x, 0, object->trans.z);
    Hu3DModelScaleSet(object->model[1], data->unk0C, data->unk0C, data->unk0C);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    object->model[2] = Hu3DModelRead(0x2F000C, 0xA59);
    Hu3DModelScaleSet(object->model[2], 2.0f, 2.0f, 2.0f);
    if (data->unk02 == 0) {
        Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
        Hu3DModelCameraSet(object->model[1], HU3D_CAM0);
        Hu3DModelCameraSet(object->model[2], HU3D_CAM0);
    } else {
        Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
        Hu3DModelCameraSet(object->model[1], HU3D_CAM1);
        Hu3DModelCameraSet(object->model[2], HU3D_CAM1);
    }
    m214_fireCnt++;
}

void m214_FireObjMain(omObjData *object) {
    HyperHydrantsFireWork *data = object->data;

    switch (MgFlowStatGet()) {
        case MG_STATE_OPENING:
            m214_FireIntroMove(object);
            break;
        case MG_STATE_START:
            object->trans.y = 0;
            break;
        case MG_STATE_PLAY:
            m214_FireMove(object);
            if (data->unk04 == 1) {
                m214_FireShrink(object);
            }
            if (data->unk1A == 1) {
                if (data->unk1E >= 2) {
                    data->unk1E = 0;
                    data->unk1A = 0;
                } else {
                    if (data->unk1E == 0) {
                        data->unk1C = m214_SePanPlay(0x365, data->unk02, 0, 0);
                    }
                    data->unk1E++;
                }
            }
            break;
        case MG_STATE_FINISH:
            object->scale.x -= 0.1f;
            if (object->scale.x < 0.0f) {
                object->scale.x = 0.0f;
            }
            object->scale.y = object->scale.z = object->scale.x;
            data->unk0C = object->scale.x / 2.0f;
            break;
    }
    Hu3DModelPosSet(object->model[1], object->trans.x, 0, object->trans.z);
    Hu3DModelScaleSet(object->model[1], data->unk0C, data->unk0C, data->unk0C);
}

void m214_FireIntroMove(omObjData *object) {
    HyperHydrantsFireWork *data = object->data;
    s32 angle = 0;

    if (m214_bigFireObjTbl[data->unk02]->trans.y > 0.0f) {
        return;
    }
    if (data->unk14 == 0.0f) {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    } else if (data->unk14 < 720.0f) {
        angle = (s32)data->unk14 % 360;
        object->trans.y = sindf(data->unk14) * 200.0f;
    } else {
        object->trans.y = 0.0f;
    }
    switch (data->unk00) {
        case 0:
            object->trans.z += 6.0f;
            if (data->unk14 < 720.0f) {
                data->unk14 += 8.0f;
                if (angle >= 180) {
                    data->unk14 += 180.0f;
                }
            }
            break;
        case 1:
            object->trans.x -= 1.5f;
            object->trans.z += 8.0f;
            if (data->unk14 < 720.0f) {
                data->unk14 += 10.0f;
                if (angle >= 180) {
                    data->unk14 += 180.0f;
                }
            }
            break;
        case 2:
            object->trans.x += 1.5f;
            object->trans.z += 8.0f;
            if (data->unk14 < 720.0f) {
                data->unk14 += 10.0f;
                if (angle >= 180) {
                    data->unk14 += 180.0f;
                }
            }
            break;
        case 3:
            object->trans.x -= 1.5f;
            object->trans.z += 5.0f;
            if (data->unk14 < 720.0f) {
                data->unk14 += 6.0f;
                if (angle >= 180) {
                    data->unk14 += 180.0f;
                }
            }
            break;
        default:
            object->trans.x += 1.5f;
            object->trans.z += 5.0f;
            if (data->unk14 < 720.0f) {
                data->unk14 += 6.0f;
                if (angle >= 180) {
                    data->unk14 += 180.0f;
                }
            }
            break;
    }
}

void m214_FireMove(omObjData *object) {
    HyperHydrantsFireWork *data = object->data;
    Vec position;
    Vec2f screen;

    if (data->unk01 == 0) {
        if ((u16)(MgFlowStatTimeGet() % 60) == 0) {
            if (m214_fireSpawnFTbl[data->unk02] != 0) {
                return;
            }
            m214_FireReset(object);
            m214_SePanPlay(0x365, data->unk02, 0, 0);
            m214_fireSpawnFTbl[data->unk02] = 1;
            ((HyperHydrantsFireWork *)m214_bigFireObjTbl[data->unk02]->data)->unk03 = 1;
        } else {
            m214_fireSpawnFTbl[data->unk02] = 0;
            return;
        }
    } else if (data->unk05 == 1) {
        object->scale.x += 0.05f;
        switch (data->unk01) {
            case 1:
                if (object->scale.x > 1.0f) {
                    object->scale.x = 1.0f;
                    data->unk05 = 0;
                }
                break;
            case 2:
                if (object->scale.x > 1.25f) {
                    object->scale.x = 1.25f;
                    data->unk05 = 0;
                }
                break;
            case 3:
                if (object->scale.x > 1.5f) {
                    object->scale.x = 1.5f;
                    data->unk05 = 0;
                }
                break;
        }
        object->scale.y = object->scale.z = object->scale.x;
        data->unk0C = object->scale.x / 2.0f;
    }
    if (data->unk06 == 2) {
        object->trans.z += 2.0f;
        if (object->trans.z > -500.0f) {
            data->unk06 = 0;
        }
    } else if (data->unk0A == 0) {
        data->unk0A = (rand8() >> 5) * 15;
        if ((rand8() >> 7) == 0) {
            data->unk06 ^= 1;
        }
    } else {
        data->unk0A--;
        if (data->unk06 == 0) {
            if (object->trans.z > -200.0f) {
                data->unk06 ^= 1;
            }
        } else if (data->unk06 == 1) {
            if (object->trans.z < -500.0f) {
                data->unk06 ^= 1;
            }
        }
    }
    if (data->unk06 == 0) {
        object->trans.z += 3.0f;
    } else if (data->unk06 == 1) {
        object->trans.z -= 3.0f;
    }
    if (data->unk08 == 0) {
        data->unk03 ^= 1;
        data->unk08 = (rand8() >> 5) * 15;
    } else {
        data->unk08--;
        position.x = object->trans.x;
        position.y = object->trans.y;
        position.z = object->trans.z;
        if (data->unk02 == 0) {
            Hu3D3Dto2D(0, &position, &screen);
            if (data->unk03 == 0 && screen.x < 119.0f) {
                data->unk03 ^= 1;
            } else if (data->unk03 == 1 && screen.x > 225.0f) {
                data->unk03 ^= 1;
            }
        } else {
            Hu3D3Dto2D(1, &position, &screen);
            if (data->unk03 == 0 && screen.x < 95.0f) {
                data->unk03 ^= 1;
            } else if (data->unk03 == 1 && screen.x > 201.0f) {
                data->unk03 ^= 1;
            }
        }
    }
    if (data->unk03 != 0) {
        object->trans.x += 4.0f;
    } else {
        object->trans.x -= 4.0f;
    }
}

void m214_FireReset(omObjData *object) {
    HyperHydrantsFireWork *data = object->data;
    s8 index;
    s8 type;

    index = m214_fireSpawnNoTbl[data->unk02]++;
    if (index >= 16) {
        index %= 16;
    }
    type = m214_fireSizeTbl[m214_firePatternNo][index];
    data->unk10 = 50.0f;
    data->unk18 = 0;
    data->unk1A = 0;
    data->unk05 = 1;
    data->unk06 = 2;
    object->trans.x = m214_bigFireObjTbl[data->unk02]->trans.x;
    object->trans.z = m214_bigFireObjTbl[data->unk02]->trans.z;
    object->trans.y = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 0.1f;
    switch (type) {
        case 0:
            data->unk0C = object->scale.x / 2.0f;
            data->unk01 = 1;
            break;
        case 1:
            data->unk0C = object->scale.x / 2.0f;
            data->unk01 = 2;
            break;
        case 2:
        default:
            data->unk0C = object->scale.x / 2.0f;
            data->unk01 = 3;
            break;
    }
}

void m214_FireShrink(omObjData *object) {
    HyperHydrantsFireWork *data = object->data;

    switch (data->unk01) {
        case 3:
            if (object->scale.x <= 1.25f) {
                data->unk0C = 1.25f;
                object->scale.x = object->scale.y = object->scale.z = 1.25f;
                data->unk04 = 0;
                data->unk01--;
            } else {
                object->scale.x -= 0.05f;
                object->scale.y = object->scale.z = data->unk0C = object->scale.x;
            }
            break;
        case 2:
            if (object->scale.x <= 1.0f) {
                data->unk0C = 1.0f;
                object->scale.x = object->scale.y = object->scale.z = 1.0f;
                data->unk04 = 0;
                data->unk01--;
            } else {
                object->scale.x -= 0.05f;
                object->scale.y = object->scale.z = data->unk0C = object->scale.x;
            }
            break;
        case 1:
            if (object->scale.x <= 0.0f) {
                object->trans.z = m214_bigFireObjTbl[data->unk02]->trans.z;
                data->unk0C = data->unk10 = 0.0f;
                object->scale.x = object->scale.y = object->scale.z = 0.0f;
                data->unk04 = 0;
                data->unk01--;
                if (data->unk02 == 0) {
                    m214_score0++;
                    m214_SePanPlay(0x364, data->unk02, 1, m214_sprayer0No);
                } else {
                    m214_score1++;
                    m214_SePanPlay(0x364, data->unk02, 1, m214_sprayer1No);
                }
                if (data->unk02 == 0) {
                    omVibrate(m214_pumper0No, 2, 3, 10);
                    omVibrate(m214_sprayer0No, 2, 3, 10);
                } else {
                    omVibrate(m214_pumper1No, 2, 3, 10);
                    omVibrate(m214_sprayer1No, 2, 3, 10);
                }
            } else {
                object->scale.x -= 0.1f;
                object->scale.y = object->scale.z = data->unk0C = object->scale.x;
            }
            break;
    }
}

void m214_HoseObjInit(omObjData *object) {
    omObjData *player;
    MgPlayerWork *playerData;
    HyperHydrantsCharacterData *characterData;
    Vec step;
    f32 x;
    f32 z;
    s32 side;
    s32 i;
    s32 playerIndex;

    side = 1;
    object->func = m214_HoseObjMain;
    if (m214_hoseCnt == 0) {
        object->work[0] = 0;
        playerIndex = m214_pumper0No;
        side = 0;
    } else {
        object->work[0] = side;
        playerIndex = m214_pumper1No;
    }
    player = mgPlayerObjTbl[playerIndex];
    m214_hydrantPosTbl[side].x = player->trans.x - 25.0f - 18.75f;
    m214_hydrantPosTbl[side].y = 37.5f;
    playerData = player->data;
    if ((omCharModelNoTbl[GwPlayer[playerData->unk59].chr][0] >> 16) == 6) {
        m214_hydrantPosTbl[side].z = player->trans.z + 50.0f + 18.75f + 48.7f;
    } else {
        m214_hydrantPosTbl[side].z = player->trans.z + 50.0f + 18.75f;
    }
    object->scale.x = object->scale.y = object->scale.z = 1.6f;
    if (object->work[0] == 0) {
        player = mgPlayerObjTbl[m214_sprayer0No];
    } else {
        player = mgPlayerObjTbl[m214_sprayer1No];
    }
    playerData = player->data;
    characterData = playerData->unk158;
    x = player->trans.x + characterData->unk08 * 60.0f;
    z = player->trans.z + characterData->unk0C * 60.0f;
    step.x = ((m214_hydrantPosTbl[side].x - x > 0.0f) ? m214_hydrantPosTbl[side].x - x : 0.0f - (m214_hydrantPosTbl[side].x - x)) / 5.0f;
    step.y = -8.5f;
    step.z = ((m214_hydrantPosTbl[side].z - z > 0.0f) ? m214_hydrantPosTbl[side].z - z : 0.0f - (m214_hydrantPosTbl[side].z - z)) / 5.0f;
    for (i = 0; i < 6; i++) {
        object->model[i] = Hu3DModelRead(0x2F0008, 0x899);
        Hu3DModelScaleSet(object->model[i], object->scale.x, object->scale.y, object->scale.z);
        m214_hoseTbl[side][i] = HuMemAllocTag(sizeof(HyperHydrantsHosePoint), TAG_OVERLAY);
        if (side == 0) {
            Hu3DModelCameraSet(object->model[i], HU3D_CAM0);
        } else {
            Hu3DModelCameraSet(object->model[i], HU3D_CAM1);
        }
        m214_hoseTbl[side][i]->position.x = x + i * step.x;
        m214_hoseTbl[side][i]->position.y = i * step.y + 80.0f;
        m214_hoseTbl[side][i]->position.z = z + i * step.z;
        if (i == 0) {
            object->trans.x = m214_hoseTbl[side][i]->position.x;
            object->trans.y = m214_hoseTbl[side][i]->position.y;
            object->trans.z = m214_hoseTbl[side][i]->position.z;
        }
        Hu3DModelPosSet(object->model[i], m214_hoseTbl[side][i]->position.x, m214_hoseTbl[side][i]->position.y, m214_hoseTbl[side][i]->position.z);
    }
    m214_hoseCnt++;
}

void m214_HoseObjMain(omObjData *object) {
    omObjData *player;
    MgPlayerWork *playerData;
    HyperHydrantsCharacterData *characterData;
    Vec step;
    f32 x;
    f32 z;
    s32 side;
    s32 i;
    s32 playerIndex;

    switch (MgFlowStatGet()) {
        case MG_STATE_OPENING:
        case MG_STATE_START:
            break;
        case MG_STATE_PLAY:
            if (object->work[0] == 0) {
                playerIndex = m214_sprayer0No;
                side = 0;
            } else {
                playerIndex = m214_sprayer1No;
                side = 1;
            }
            player = mgPlayerObjTbl[playerIndex];
            playerData = player->data;
            characterData = playerData->unk158;
            x = player->trans.x + characterData->unk08 * 60.0f;
            z = player->trans.z + characterData->unk0C * 60.0f;
            step.x = ((m214_hydrantPosTbl[side].x - x > 0.0f) ? m214_hydrantPosTbl[side].x - x : 0.0f - (m214_hydrantPosTbl[side].x - x)) / 5.0f;
            step.y = -8.5f;
            step.z = ((m214_hydrantPosTbl[side].z - z > 0.0f) ? m214_hydrantPosTbl[side].z - z : 0.0f - (m214_hydrantPosTbl[side].z - z)) / 5.0f;
            for (i = 0; i < 6; i++) {
                m214_hoseTbl[side][i]->position.x = x + i * step.x;
                m214_hoseTbl[side][i]->position.y = i * step.y + 80.0f;
                m214_hoseTbl[side][i]->position.z = z + i * step.z;
                if (i == 0) {
                    object->trans.x = m214_hoseTbl[side][i]->position.x;
                    object->trans.y = m214_hoseTbl[side][i]->position.y;
                    object->trans.z = m214_hoseTbl[side][i]->position.z;
                }
                Hu3DModelPosSet(object->model[i], m214_hoseTbl[side][i]->position.x, m214_hoseTbl[side][i]->position.y, m214_hoseTbl[side][i]->position.z);
            }
            break;
        case MG_STATE_FINISH:
        case MG_STATE_RESULT:
        case MG_STATE_EXIT:
            for (i = 0; i < 6; i++) {
                Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            break;
    }
}

void m214_IrisObjInit(omObjData *object) {
    HuSprite *sprites[2];
    HyperHydrantsMaskData *data;
    s32 i;
    u8 *first;
    u8 *second;
    f32 x;
    f32 y;
    f32 dx;
    f32 dy;
    f32 distance;
    f32 step;

    object->func = m214_IrisObjMain;
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    m214_frameAnim = HuSprAnimDataRead(0x2F0009);
    m214_frameSprGrp = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(m214_frameSprGrp, 0, m214_frameAnim, 0);
    HuSprPriSet(m214_frameSprGrp, 0, 0x10);
    HuSprAttrReset(m214_frameSprGrp, 0, 0xFFFF);
    HuSprAttrSet(m214_frameSprGrp, 0, HUSPR_ATTR_XLU);
    HuSprPosSet(m214_frameSprGrp, 0, 160, 120);
    for (i = 0; i < 2; i++) {
        m214_backAnim = HuSprAnimDataRead(0x2F0000);
        m214_backSprGrp = HuSprGrpCreate(1, 0);
        HuSprGrpMemberSet(m214_backSprGrp, 0, m214_backAnim, 0);
        HuSprAttrReset(m214_backSprGrp, 0, 0xFFFF);
        if (i == 0) {
            HuSprAttrSet(m214_backSprGrp, 0, HUSPR_ATTR_BG | HUSPR_ATTR_XLU);
            HuSprPosSet(m214_backSprGrp, 0, 80, 120);
        } else {
            HuSprAttrSet(m214_backSprGrp, 0, HUSPR_ATTR_BG | HUSPR_ATTR_XLU | HUSPR_ATTR_FLIPX);
            HuSprPosSet(m214_backSprGrp, 0, 240, 120);
        }
    }
    data = object->data = HuMemAllocTag(sizeof(HyperHydrantsMaskData), TAG_OVERLAY);
    memset(data, 0, sizeof(HyperHydrantsMaskData));
    data->unk03 = 1;
    data->unk04 = 0;
    data->unk08 = 0.5f;
    MgMapAttrSet(object, 2, 0.0f);
    for (i = 0; i < 2; i++) {
        m214_irisAnim = HuSprAnimDataRead(0x2F0001);
        m214_irisSprGrpTbl[i] = HuSprGrpCreate(1, 0);
        HuSprGrpMemberSet(m214_irisSprGrpTbl[i], 0, m214_irisAnim, 0);
        HuSprPriSet(m214_frameSprGrp, 0, 0x20);
        HuSprAttrReset(m214_irisSprGrpTbl[i], 0, 0xFFFF);
        if (i == 0) {
            HuSprAttrSet(m214_irisSprGrpTbl[0], 0, HUSPR_ATTR_XLU);
            HuSprPosSet(m214_irisSprGrpTbl[0], 0, 80, 120);
        } else {
            HuSprAttrSet(m214_irisSprGrpTbl[i], 0, HUSPR_ATTR_XLU | HUSPR_ATTR_FLIPX);
            HuSprPosSet(m214_irisSprGrpTbl[i], 0, 240, 120);
        }
        sprites[i] = HuSprGet(m214_irisSprGrpTbl[i], 0);
        m214_irisTexTbl[i] = sprites[i]->data->pat->data;
    }
    m214_irisSizeX = sprites[0]->data->sizeX;
    m214_irisSizeY = sprites[0]->data->sizeY;
    m214_irisRadius = 35;
    step = 35.0f / 255.0f;
    first = m214_irisTexTbl[0];
    second = m214_irisTexTbl[1];
    for (y = 0.0f; y < m214_irisSizeY; y++) {
        for (x = 0.0f; x < m214_irisSizeX; x++, first++, second++) {
            dx = x - m214_irisX;
            dy = y - m214_irisY;
            distance = HuSqrtf(dx * dx + dy * dy);
            if (distance > m214_irisRadius) {
                *first = *second = 255;
            } else {
                *first = *second = (u32)(distance / step);
            }
        }
    }
    HuSprTPLvlSet(m214_irisSprGrpTbl[0], 0, 240);
    HuSprTPLvlSet(m214_irisSprGrpTbl[1], 0, 240);
}

void m214_IrisObjMain(omObjData *object) {
    if (MgFlowStatGet() == MG_STATE_OPENING) {
        if (m214_bigFireObjTbl[0]->trans.y > 0.0f) {
            m214_IrisUpdate();
        } else if (m214_irisRadius < 240) {
            m214_irisRadius += 3;
            m214_IrisUpdate();
        } else {
            m214_irisRadius = 240;
        }
    }
}

void m214_IrisUpdate(void) {
    HyperHydrantsFireWork *data;
    f32 innerRadius;
    f32 step;
    s32 endRow;
    u8 *first;
    u8 *second;
    s32 row;
    s32 column;
    f32 x;
    f32 y;
    f32 distance;
    u8 alpha;

    data = m214_bigFireObjTbl[0]->data;
    if (data->unk03 == 2) {
        m214_irisOpenF = 1;
    }
    innerRadius = m214_irisRadius * 0.8f;
    step = m214_irisRadius * 0.2f / 255.0f;
    endRow = m214_irisY + m214_irisRadius;
    first = m214_irisTexTbl[0];
    second = m214_irisTexTbl[1];
    for (row = 0; row < m214_irisSizeY; row++) {
        if (data->unk03 == 1) {
            if (row > m214_irisSizeY / 2) {
                break;
            }
        } else if (row > endRow) {
            break;
        }
        for (column = 0; column < m214_irisSizeX; column++, first++, second++) {
            if (m214_irisOpenF && *first == 0) {
                continue;
            }
            x = column - m214_irisX;
            y = row - m214_irisY;
            distance = HuSqrtf(x * x + y * y);
            if (distance <= innerRadius) {
                if (*first != 0) {
                    *second = 0;
                    *first = 0;
                }
            } else if (distance > m214_irisRadius) {
                if ((~*first & 0xFF) != 0) {
                    *second = 255;
                    *first = 255;
                }
            } else {
                alpha = (u32)((distance - innerRadius) / step);
                if (alpha != *first) {
                    *second = alpha;
                    *first = alpha;
                }
            }
        }
    }
}

void m214_ScoreObjInit(omObjData *object) {
    s16 positions[2][2] = { { 35, 32 }, { 252, 32 } };
    s16 sprite;
    s16 i;
    s16 j;

    sprite = HuSprAnimDataRead(0x2F000A);
    for (i = 0; i < 2; i++) {
        m214_scoreIconEspTbl[i] = espEntry(sprite, 0, 1);
        espPosSet(m214_scoreIconEspTbl[i], positions[i][0], positions[i][1]);
        espDispOff(m214_scoreIconEspTbl[i]);
    }
    sprite = HuSprAnimDataRead(0x21001B);
    for (i = 0; i < 2; i++) {
        m214_scoreXEspTbl[i] = espEntry(sprite, 0, 1);
        espPosSet(m214_scoreXEspTbl[i], positions[i][0] + 12, positions[i][1]);
        espDispOff(m214_scoreXEspTbl[i]);
    }
    sprite = HuSprAnimDataRead(0x31);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            m214_scoreDigitEspTbl[i][j] = espEntry(sprite, 0, 1);
            espPosSet(m214_scoreDigitEspTbl[i][j], m214_scoreDigitPosTbl[i][j][0], m214_scoreDigitPosTbl[i][j][1]);
            espDispOff(m214_scoreDigitEspTbl[i][j]);
        }
    }
    object->func = m214_ScoreObjMain;
}

void m214_ScoreObjMain(omObjData *object) {
    s32 i;
    s32 j;

    switch (MgFlowStatGet()) {
        case MG_STATE_PLAY:
        case MG_STATE_FINISH:
            if (m214_score0 < 10) {
                espDispOn(m214_scoreDigitEspTbl[0][0]);
                espPatNoSet(m214_scoreDigitEspTbl[0][0], (s8)(m214_score0 % 10));
                espPosSet(m214_scoreDigitEspTbl[0][0], m214_scoreDigitPosTbl[0][0][0], m214_scoreDigitPosTbl[0][0][1]);
                espDispOff(m214_scoreDigitEspTbl[0][1]);
            } else {
                espDispOn(m214_scoreDigitEspTbl[0][0]);
                espPatNoSet(m214_scoreDigitEspTbl[0][0], (s8)(m214_score0 / 10));
                espPosSet(m214_scoreDigitEspTbl[0][0], m214_scoreDigitPosTbl[0][0][0], m214_scoreDigitPosTbl[0][0][1]);
                espDispOn(m214_scoreDigitEspTbl[0][1]);
                espPatNoSet(m214_scoreDigitEspTbl[0][1], (s8)(m214_score0 % 10));
                espPosSet(m214_scoreDigitEspTbl[0][1], m214_scoreDigitPosTbl[0][1][0], m214_scoreDigitPosTbl[0][1][1]);
            }
            if (m214_score1 < 10) {
                espDispOn(m214_scoreDigitEspTbl[1][0]);
                espPatNoSet(m214_scoreDigitEspTbl[1][0], (s8)(m214_score1 % 10));
                espPosSet(m214_scoreDigitEspTbl[1][0], m214_scoreDigitPosTbl[1][0][0], m214_scoreDigitPosTbl[1][0][1]);
                espDispOff(m214_scoreDigitEspTbl[1][1]);
            } else {
                espDispOn(m214_scoreDigitEspTbl[1][0]);
                espPatNoSet(m214_scoreDigitEspTbl[1][0], (s8)(m214_score1 / 10));
                espPosSet(m214_scoreDigitEspTbl[1][0], m214_scoreDigitPosTbl[1][0][0], m214_scoreDigitPosTbl[1][0][1]);
                espDispOn(m214_scoreDigitEspTbl[1][1]);
                espPatNoSet(m214_scoreDigitEspTbl[1][1], (s8)(m214_score1 % 10));
                espPosSet(m214_scoreDigitEspTbl[1][1], m214_scoreDigitPosTbl[1][1][0], m214_scoreDigitPosTbl[1][1][1]);
            }
            for (i = 0; i < 2; i++) {
                espDispOn(m214_scoreIconEspTbl[i]);
                espDispOn(m214_scoreXEspTbl[i]);
            }
            break;
        default:
            for (i = 0; i < 2; i++) {
                espDispOff(m214_scoreIconEspTbl[i]);
                espDispOff(m214_scoreXEspTbl[i]);
                for (j = 0; j < 2; j++) {
                    espDispOff(m214_scoreDigitEspTbl[i][j]);
                }
            }
            break;
    }
}

s16 m214_SePanPlay(s16 soundId, s16 side, s8 playerSound, s16 player) {
    s16 sound;

    if (playerSound) {
        sound = HuAudPlayerFXPlay(soundId, player);
    } else {
        sound = HuAudFXPlay(soundId);
    }
    if (side == 0) {
        HuAudFXPanning(sound, 0x20);
    } else {
        HuAudFXPanning(sound, 0x60);
    }
    return sound;
}

void m214_DirCalc(Vec *arg0, Vec *arg1, Vec *arg2) {
    f32 length;

    arg0->x = arg2->x - arg1->x;
    arg0->y = arg2->y - arg1->y;
    arg0->z = arg2->z - arg1->z;
    length = arg0->x * arg0->x;
    length += arg0->y * arg0->y;
    length += arg0->z * arg0->z;
    length = HuSqrtf(length);
    if (length != 0.0f) {
        arg0->x /= length;
        arg0->y /= length;
        arg0->z /= length;
    } else {
        arg0->x = arg0->y = arg0->z = 0.0f;
    }
}
