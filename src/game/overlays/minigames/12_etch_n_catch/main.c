#include "common.h"
#include "game/camera.h"
#include "game/camsetup.h"
#include "game/util.h"
#include "game/pause.h"
#include "game/wipe.h"
#include "variables.h"
#include "game/audio.h"
#include "game/esprite.h"
#include "game/input.h"
#include "game/mallocblock.h"
#include "game/sprite.h"
#include "gcc/memory.h"
#include "humath.h"
#include "math.h"
#include "game/overlays/minigame.h"

// Grid cell value marking a cell that was just filled.
#define ETCH_N_CATCH_CELL_FILLED 0x21
// Grid cell value marking a cell that ends a fill.
#define ETCH_N_CATCH_CELL_EDGE 0x22

#define ABS(x) ((x) > 0.0f ? (x) : 0.0f - (x))
#define FABS(x) ((x) < 0.0f ? -(x) : (x))
#define IABS(x) ((x) < 0 ? -(x) : (x))

// Per-player record. m218_lineNodeTbl points at one 0x100-entry array of
// these per player, and a record is free for reuse while unk_00 is zero.
// Records are chained through unk_04/unk_08/unk_0C.
typedef struct EtchNCatchNode {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ struct EtchNCatchNode *unk_04;
    /* 0x08 */ struct EtchNCatchNode *unk_08;
    /* 0x0C */ struct EtchNCatchNode *unk_0C;
    /* 0x10 */ struct EtchNCatchNode *unk_10;
    /* 0x14 */ u8 unk_14;
    /* 0x15 */ u8 unk_15;
    /* 0x16 */ s16 unk_16; // Countdown
    /* 0x18 */ s16 unk_18; // Grid x
    /* 0x1A */ s16 unk_1A; // Grid y
    /* 0x1C */ u8 unk_1C;  // Player index
    /* 0x1E */ s16 unk_1E; // Model, or -1
    /* 0x20 */ Vec unk_20;
    /* 0x2C */ s8 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ u8 unk_34; // Index into m218_lineMdlUseTbl[unk_1C]
} EtchNCatchNode;         // sizeof 0x38

// Heap-allocated (0x20 bytes) work block; unk_0C is the head of a linked list
// of nodes (m218_LineNodeAdd inserts, m218_LineNodeRemove removes, m218_LineLoopCheck walks).
typedef struct EtchNCatchWork {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01; // Team (3 or 12)
    /* 0x02 */ u8 unk_02;
    /* 0x04 */ s16 unk_04; // Grid x
    /* 0x06 */ s16 unk_06; // Grid y
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ struct EtchNCatchNode *unk_0C;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ u8 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ u8 unk_16;
    /* 0x17 */ u8 unk_17;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s16 unk_1C;
} EtchNCatchWork; // sizeof 0x20

// Positions of the four players and the offsets applied to them while
// m218_PlayerObjMain runs the shared player update.
typedef struct EtchNCatchPlayerOffsets {
    /* 0x00 */ f32 offsetX[4];
    /* 0x10 */ f32 offsetZ[4];
    /* 0x20 */ f32 x[4];
    /* 0x30 */ f32 z[4];
} EtchNCatchPlayerOffsets; // sizeof 0x40

// Per-object data of the Toad objects created by m218_KinopioObjInit.
typedef struct EtchNCatchKinopioData {
    /* 0x000 */ MgPlayerWork base;
    /* 0x15C */ s32 unk15C;
    /* 0x160 */ u8 unk160; // Index into m218_kinopioMarkSprTbl
    /* 0x161 */ u8 unk161;
    /* 0x164 */ f32 unk164;
    /* 0x168 */ f32 unk168;
    /* 0x16C */ f32 unk16C;
    /* 0x170 */ f32 unk170;
    /* 0x174 */ f32 unk174;
    /* 0x178 */ Vec unk178[5];
    /* 0x1B4 */ f32 unk1B4;
} EtchNCatchKinopioData; // sizeof 0x1B8

// Per-object data of the objects created by m218_CageObjInit.
typedef struct EtchNCatchCageWork {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
} EtchNCatchCageWork; // sizeof 0xC

extern f32 mgPlayerSpeedZero;
extern s32 omCharModelNoTbl[][6];
extern u8 omAllPauseF;

s8 m218_kinopioNum = 0;
s16 m218_scorePosTbl[2][2] = { { 64, 38 }, { 281, 38 } };
s8 m218_team0Score = 0;
s8 m218_team1Score = 0;
Vec m218_kinopioPosTbl[3] = { { -235.0f, 0.0f, -50.0f }, { -235.0f, 0.0f, 125.0f }, { -235.0f, 0.0f, -225.0f } };
s32 m218_exitTimer = 0;
s8 m218_exitF = 0;
s8 m218_playerNum = 0;
s8 m218_team0PlayerNum = 0; // Team 0 players placed so far
s8 m218_team1PlayerNum = 0; // Team 1 players placed so far
f32 m218_dropScale = 0.2f;
u8 m218_leftLoopF = 0;
u8 m218_rightLoopF = 0;
u8 m218_fillSideF = 0;
u8 m218_comStateTbl[4] = { 0 };
u8 m218_lineMdlUseTbl[4][3] = { 0 };
u8 m218_lineMdlNoTbl[4] = { 0 };
u8 m218_kinopioCatchStepTbl[2] = { 0 };

u8 m218_startPosSel BSS;
f32 m218_dropSpeed BSS;
EtchNCatchWork *m218_curPlayerWork BSS;
s16 m218_kinopioMdl BSS;
s16 m218_shadowMdl BSS;
u8 m218_cageNum BSS;
s16 m218_boardSprGrp BSS;
s16 m218_gridSprGrp BSS;
// Byte grid of player slots: m218_gridBuf is the base address and
// m218_gridW the row stride in bytes.
s16 m218_gridW BSS;
s16 m218_gridH BSS; // Grid height
u8 *m218_gridBuf BSS;
s16 m218_kinopioGridPosTbl[2][2] BSS;
omObjData *m218_kinopioObjTbl[2] BSS;
omObjData *m218_cageObjTbl[2] BSS;
EtchNCatchWork *m218_playerWorkTbl[4] BSS;
// Heap-allocated list of grid cells touched this frame, one pointer per entry.
u8 **m218_fillCellList BSS;
// Two heap-allocated queues of grid cells, swapped between fill passes.
u8 **m218_fillQueueTbl[2] BSS;
u8 m218_fillQueueTblPad[0xC] BSS; /* Unreferenced. */
// Per-player region bits of each grid cell pair, 160 cells per row.
u8 m218_regionTbl[120][160] BSS;
s16 m218_lineMdlTbl[4][3] BSS;
u16 m218_scoreSprTbl[2] BSS;
u8 m218_scoreSprTblPad[4] BSS; /* Unreferenced. */
MinigameFlow m218_mgFlow BSS;
EtchNCatchNode *m218_lineNodeTbl[4] BSS;
u16 m218_kinopioMarkSprTbl[4] BSS;

void m218_FlowInit(MinigameFlow *flow);
void m218_CameraInit(void);
void m218_WorkFree(void);
void m218_MainObjMain(omObjData *object);
void m218_PlayerObjInit(omObjData *object);
void m218_PlayerObjMain(omObjData *object);
void m218_LineInit(EtchNCatchWork *arg0);
void m218_PlayerComInput(omObjData *object);
void m218_StickTurnLimit(MgPlayerWork *data);
EtchNCatchNode *m218_LineNodeFreeGet(s8 playerId);
void m218_LineNodeAdd(EtchNCatchNode **head, EtchNCatchNode *node);
void m218_LineNodeRemove(EtchNCatchNode **head, EtchNCatchNode *node);
s32 m218_LineLoopCheck(EtchNCatchWork *work);
s32 m218_FillCheck(s16 x, s16 y);
u8 m218_GridValueGet(s16 x, s16 y);
void m218_GridValueSet(s16 x, s16 y, u8 value);
void m218_LineNodeErase(EtchNCatchNode *node, u8 value);
void m218_LineMdlSet(EtchNCatchNode *node);
s32 m218_GridHitCheck(s16 x, s16 y);
void m218_PlayerScaleSet(omObjData *object, f32 scale);
void m218_KinopioObjInit(omObjData *object);
void m218_KinopioObjMain(omObjData *object);
void m218_KinopioCatchEffUpdate(omObjData *object);
void m218_KinopioMarkSway(EtchNCatchKinopioData *data);
void m218_KinopioMarkPulse(EtchNCatchKinopioData *data);
void m218_KinopioMarkTurn(EtchNCatchKinopioData *data);
void m218_CageObjInit(omObjData *object);
void m218_CageObjMain(omObjData *object);
void m218_ScoreObjInit(omObjData *object);
void m218_ScoreObjMain(omObjData *object);
void m218_BoardObjInit(omObjData *object);
void m218_MapLeftObjInit(omObjData *object);
void m218_MapRightObjInit(omObjData *object);
f32 m218_AngleWrap(f32 arg0);
Vec2f m218_DirCalc(s32 x0, s32 y0, s32 x1, s32 y1);

void m218_ObjectSetup(void) {
    s32 i;

    MapCollInit(32);
    Hu3DQuadPoolInit(&mgQuadPool, 64);
    Hu3DSprModelInit(64);
    omInitObjMan(32, 0);
    omGameSysInit();
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    MgFieldStatClear();
    m218_FlowInit(&m218_mgFlow);
    MgFlowInit(&m218_mgFlow);
    Hu3DGLightColorSet(1, 64, 64, 64);
    Hu3DGLightDirSet(1, 0.0f, 0.0f, 100.0f);
    omSetStatBit(omAddObj(0, 0, 0, -1, m218_MainObjMain), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    m218_CameraInit();
    mgMapObjTbl[mgMapObjNum++] = omAddObj(2, 1, 0, -1, m218_MapLeftObjInit);
    mgMapObjTbl[mgMapObjNum++] = omAddObj(2, 1, 0, -1, m218_MapRightObjInit);
    MgMapBaseSet(mgMapObjNum);
    mgMapObjTbl[mgMapObjNum++] = omAddObj(1, 0, 0, -1, m218_BoardObjInit);
    MgPlayerParamReset();
    mgPlayerFriction = 0.5f;
    for (i = 0; i < 4; i++) {
        mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(3, 5, 60, -1, m218_PlayerObjInit);
        omSetStatBit(mgPlayerObjTbl[i], OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
        m218_lineNodeTbl[i] = HuMemAllocTag(0x100 * sizeof(EtchNCatchNode), TAG_OVERLAY);
        memset(m218_lineNodeTbl[i], 0, 0x100 * sizeof(EtchNCatchNode));
    }
    for (i = 0; i < 2; i++) {
        m218_cageObjTbl[i] = omAddObj(2, 3, 0, -1, m218_CageObjInit);
        m218_kinopioObjTbl[i] = omAddObj(2, 7, 2, -1, m218_KinopioObjInit);
    }
    omAddObj(3, 0, 0, -1, m218_ScoreObjInit);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
}

void m218_FlowInit(MinigameFlow *flow) {
    s32 i;

    mgFlowSeqTime = 60;
    flow->state = MG_STATE_OPENING;
    flow->type = MINIGAME_1V3;
    flow->timerMode = MG_TIMER_COUNT_DOWN;
    flow->timeDisp = MG_TIME_DISP_COUNTDOWN;
    flow->newRecord = FALSE;
    flow->gauge = MG_GAUGE_NONE;
    flow->resultType = MG_RESULT_WIN_1;
    flow->startDelay = 90;
    flow->timer = 900;
    flow->timeLimit = -1;
    flow->finishDelay = 75;
    flow->resultDelay = 150;
    for (i = 0; i < 4; i++) {
        flow->gaugeValue[i] = 0;
        flow->winners[i] = 0xFF;
    }
}

void m218_CameraInit(void) {
    s32 camIndex;
    HuCamera *camera;

    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(camIndex, 27.211f, 80.0f, 8000.0f);
    camera = &gCameraList[camIndex];
    camera->pos.x = -1.965f;
    camera->pos.y = 1392.72f;
    camera->pos.z = 1374.455f;
    camera->at.x = -1.965f;
    camera->at.y = 60.495f;
    camera->at.z = 20.66f;
    camera->up.x = 0.0f;
    camera->up.y = 0.5f;
    camera->up.z = -0.8660254f;
}

void m218_MainObjMain(omObjData *object) {
    s32 voice;
    s8 i;

    if (omPauseChk() + omAllPauseF == 0) {
        if (m218_exitF == 0 && omSysExitReq == 1) {
            HuAudFXAllStop();
            if (!(HuAudStat & 4)) {
                HuAudSeqFadeOut(30);
            } else {
                HuAudSeqStop();
            }
            MgFlowStatSet(MG_STATE_EXIT);
            m218_exitF = 1;
        }
        MgFieldStatUpdate();
        switch (MgFlowMain()) {
            case 0:
                mgFlowSeqNo = 56;
                break;
            case 1:
                break;
            case 2:
                if (m218_team0Score >= 5 || m218_team1Score >= 5) {
                    MgFlowStatSet(MG_STATE_FINISH);
                }
                break;
            case 3:
                if (MgFlowStatTimeGet() == 74.0) {
                    if (m218_team0Score == m218_team1Score) {
                        m218_mgFlow.resultType = MG_RESULT_DRAW;
                    } else {
                        m218_mgFlow.resultType = MG_RESULT_WIN_2;
                        for (i = 0; i < 4; i++) {
                            if (m218_team0Score > m218_team1Score && GwPlayer[i].group == 0) {
                                if (m218_mgFlow.winners[0] == 0xFF) {
                                    m218_mgFlow.winners[0] = i;
                                } else {
                                    m218_mgFlow.winners[1] = i;
                                }
                                GwPlayer[i].gameCoin += 10;
                            } else if (m218_team0Score < m218_team1Score && GwPlayer[i].group == 1) {
                                if (m218_mgFlow.winners[0] == 0xFF) {
                                    m218_mgFlow.winners[0] = i;
                                } else {
                                    m218_mgFlow.winners[1] = i;
                                }
                                GwPlayer[i].gameCoin += 10;
                            }
                        }
                    }
                }
                break;
            case 4:
                if (mgFlowResultF != 0) {
                    for (i = 0; i < 4; i++) {
                        if (m218_mgFlow.resultType == MG_RESULT_WIN_2) {
                            if (i == m218_mgFlow.winners[0] || i == m218_mgFlow.winners[1]) {
                                MgPlayerMotSet(mgPlayerObjTbl[i], 13);
                                switch (GwPlayer[i].chr) {
                                    case 0:
                                    default:
                                        voice = 2;
                                        break;
                                    case 1:
                                        voice = 3;
                                        break;
                                    case 2:
                                        voice = 7;
                                        break;
                                    case 3:
                                        voice = 4;
                                        break;
                                    case 4:
                                        voice = 5;
                                        break;
                                    case 5:
                                        voice = 6;
                                        break;
                                    case 6:
                                        voice = 8;
                                        break;
                                    case 7:
                                        voice = 9;
                                        break;
                                }
                                HuAudFXAllStop();
                                HuAudCharVoicePlay((voice << 16) | 0x2F);
                            } else {
                                MgPlayerMotSet(mgPlayerObjTbl[i], 14);
                            }
                        } else {
                            MgPlayerMotSet(mgPlayerObjTbl[i], 14);
                        }
                    }
                }
                break;
            case 5:
                if (m218_exitTimer == 0) {
                    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                    m218_WorkFree();
                } else if (WipeStatGet() == 0 && !(HuAudStat & 4)) {
                    omOvlReturnEx(1);
                }
                m218_exitTimer++;
                break;
        }
        Hu3DCameraPosSetV(0, &gCameraList[0].pos, &gCameraList[0].at, &gCameraList[0].up);
        Hu3DCamUpdateMtx(0);
    }
}

void m218_PlayerObjInit(omObjData *object) {
    Vec team0PosA[2] = { { -350.0f, 1000.0f, -200.0f }, { -150.0f, 1000.0f, 250.0f } };
    Vec team0PosB[2] = { { -150.0f, 1000.0f, 250.0f }, { -350.0f, 1000.0f, -200.0f } };
    Vec team1PosA[2] = { { 150.0f, 1000.0f, -200.0f }, { 350.0f, 1000.0f, 250.0f } };
    Vec team1PosB[2] = { { 350.0f, 1000.0f, 250.0f }, { 150.0f, 1000.0f, -200.0f } };
    MgPlayerWork *data;
    EtchNCatchWork *work;
    f32 offsetX;
    f32 offsetZ;
    s8 chr;
    s32 model;
    s32 motion;
    s32 i;

    chr = GwPlayer[m218_playerNum].chr;
    model = omCharModelNoTbl[chr][0];
    motion = omCharModelNoTbl[chr][1];
    MgShadowAltSet(1);
    MgPlayerCreate(object, model, motion, m218_playerNum, 0xAA9, 0xAB9);
    data = object->data;
    mgPlayerSeTbl[data->unk59][0] = -1;
    mgPlayerSeTbl[data->unk59][1] = -1;
    data->unk3C = 0.0f;
    m218_playerWorkTbl[m218_playerNum] = work = HuMemAllocTag(sizeof(EtchNCatchWork), TAG_OVERLAY);
    memset(work, 0, sizeof(EtchNCatchWork));
    m218_LineInit(work);
    object->rot.y = 0.0f;
    object->rot.x = object->rot.z = object->rot.y;
    object->scale.x = object->scale.y = object->scale.z = 0.75f;
    if (m218_playerNum == 0) {
        m218_startPosSel = (rand8() * 10) >> 8;
    }
    switch (GwPlayer[data->unk59].group) {
        case 0:
            if (!(m218_startPosSel & 1)) {
                object->trans.x = team0PosA[m218_team0PlayerNum].x;
                object->trans.y = team0PosA[m218_team0PlayerNum].y;
                object->trans.z = team0PosA[m218_team0PlayerNum].z;
            } else {
                object->trans.x = team0PosB[m218_team0PlayerNum].x;
                object->trans.y = team0PosB[m218_team0PlayerNum].y;
                object->trans.z = team0PosB[m218_team0PlayerNum].z;
            }
            work->unk_02 = 8;
            work->unk_01 = 3;
            if (m218_team0PlayerNum == 0) {
                work->unk_00 = 1;
            } else {
                work->unk_00 = 2;
            }
            MgPlayerMapAttrSet(object, 0, 2);
            MgPlayerMapAttrSet(object, 1, 1);
            m218_team0PlayerNum++;
            break;
        case 1:
            if (!(m218_startPosSel & 1)) {
                object->trans.x = team1PosA[m218_team1PlayerNum].x;
                object->trans.y = team1PosA[m218_team1PlayerNum].y;
                object->trans.z = team1PosA[m218_team1PlayerNum].z;
            } else {
                object->trans.x = team1PosB[m218_team1PlayerNum].x;
                object->trans.y = team1PosB[m218_team1PlayerNum].y;
                object->trans.z = team1PosB[m218_team1PlayerNum].z;
            }
            work->unk_02 = 1;
            work->unk_01 = 12;
            if (m218_team1PlayerNum == 0) {
                work->unk_00 = 4;
            } else {
                work->unk_00 = 8;
            }
            MgPlayerMapAttrSet(object, 0, 1);
            MgPlayerMapAttrSet(object, 1, 2);
            m218_team1PlayerNum++;
            break;
    }
    work->unk_0A = 0;
    work->unk_08 = 0;
    work->unk_14 = 0;
    work->unk_18 = 0;
    work->unk_17 = 0;
    work->unk_1C = 0;
    work->unk_12 = 0;
    work->unk_10 = 0;
    object->func = m218_PlayerObjMain;
    offsetX = sindf(data->unk3C) * 65.0f * 0.75f;
    offsetZ = cosdf(data->unk3C) * 65.0f * 0.75f;
    Hu3DModelPosSet(object->model[1], object->trans.x - offsetX, 0.0f, object->trans.z - offsetZ);
    Hu3DModelScaleSet(object->model[1], object->scale.x, object->scale.y, object->scale.z);
    if (work->unk_02 == 8) {
        object->model[2] = Hu3DModelRead(0x330000, 0xAB9);
    } else {
        object->model[2] = Hu3DModelRead(0x330001, 0xAB9);
    }
    Hu3DModelPosSet(object->model[2], object->trans.x, object->trans.y, object->trans.z);
    Hu3DMotionAttrSet(object->model[2], 2, 1);
    object->model[3] = Hu3DModelRead(3, 0x89D);
    object->model[4] = Hu3DModelRead(4, 0x89D);
    for (i = 0; i < 3; i++) {
        if (i == 0 && data->unk59 == 0) {
            m218_lineMdlTbl[0][0] = Hu3DModelRead3(0x330006, 0x28D);
        } else {
            m218_lineMdlTbl[data->unk59][i] = Hu3DModelLink(m218_lineMdlTbl[0][0]);
        }
        Hu3DMotionAttrSet(m218_lineMdlTbl[data->unk59][i], 2, 2);
        Hu3DModelTPLvlInit(m218_lineMdlTbl[data->unk59][i]);
    }
    MgPlayerRadiusSet(object, 46.875f);
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(chr, 0x47), 1, 0);
    MgPlayerMotLoad(object, 1, CharMotionDataNumGet(chr, 0x48), 1, 0);
    MgPlayerMotLoad(object, 13, CharMotionDataNumGet(chr, 0x2F), 1, 120);
    MgPlayerMotLoad(object, 14, CharMotionDataNumGet(chr, 0x36), 1, 120);
    MgPlayerMotLoad(object, 38, CharMotionDataNumGet(chr, 0), 1, 0);
    MgPlayerMotSet(object, 0);
    m218_playerNum++;
}

void m218_PlayerObjMain(omObjData *object) {
    EtchNCatchNode *nodes[32];
    Vec pos;
    Vec2f screenPos;
    Vec2f dir;
    EtchNCatchPlayerOffsets saved;
    MgPlayerWork *data;
    MgPlayerWork *otherData;
    EtchNCatchNode *newNode;
    EtchNCatchNode *node;
    f32 offsetX;
    f32 offsetZ;
    s32 buttons;
    s32 side;
    s32 found;
    s32 count;
    s32 i;
    s32 j;
    s16 gridX;
    s16 gridY;

    if (omPauseChk() + omAllPauseF != 0) {
        return;
    }
    if (MgFlowStatGet() == MG_STATE_EXIT) {
        return;
    }
    data = object->data;
    m218_curPlayerWork = m218_playerWorkTbl[data->unk59];
    if (MgFlowStatGet() == MG_STATE_OPENING) {
        if (m218_cageObjTbl[0]->work[0] != 3) {
            Hu3DModelScaleSet(object->model[1], 0.0f, 0.0f, 0.0f);
        } else {
            object->trans.y -= m218_dropSpeed + 5.0f;
            if (object->trans.y < 0.0f) {
                object->trans.y = 0.0f;
            } else if (data->unk59 == 0) {
                m218_dropSpeed += 5.0f;
                m218_dropScale += 0.05f;
                if (m218_dropScale > 0.75f) {
                    m218_dropScale = 0.75f;
                }
            }
            MgPlayerObjMain(object);
            Hu3DModelPosSet(object->model[2], object->trans.x, object->trans.y, object->trans.z);
            m218_PlayerScaleSet(object, 0.75f);
            offsetX = sindf(data->unk3C) * 65.0f * 0.75f;
            offsetZ = cosdf(data->unk3C) * 65.0f * 0.75f;
            Hu3DModelPosSet(object->model[1], object->trans.x - offsetX, 0.0f, object->trans.z - offsetZ);
            Hu3DModelScaleSet(object->model[1], m218_dropScale, object->scale.y, m218_dropScale);
        }
        return;
    }
    buttons = HuPadBtnDown[data->unk57];
    HuPadBtnDown[data->unk57] = 0;
    if (object->trans.x < 0.0f) {
        side = 0;
    } else {
        side = 1;
    }
    if (m218_kinopioObjTbl[side]->work[0] >= 6 || m218_cageObjTbl[side]->work[0] != 3) {
        HuPadStkX[data->unk57] = 0;
        HuPadStkY[data->unk57] = 0;
    }
    if (GwPlayer[data->unk59].stat & 1) {
        m218_PlayerComInput(object);
    }
    data->unk40 *= 0.9f;
    m218_StickTurnLimit(data);
    for (i = 0; i < 4; i++) {
        saved.x[i] = mgPlayerObjTbl[i]->trans.x;
        saved.z[i] = mgPlayerObjTbl[i]->trans.z;
        otherData = mgPlayerObjTbl[i]->data;
        saved.offsetX[i] = sindf(otherData->unk3C) * 46.875f;
        saved.offsetZ[i] = cosdf(otherData->unk3C) * 46.875f;
        mgPlayerObjTbl[i]->trans.x -= saved.offsetX[i];
        mgPlayerObjTbl[i]->trans.z -= saved.offsetZ[i];
    }
    MgPlayerObjMain(object);
    for (i = 0; i < 4; i++) {
        mgPlayerObjTbl[i]->trans.x += saved.offsetX[i];
        mgPlayerObjTbl[i]->trans.z += saved.offsetZ[i];
    }
    offsetX = sindf(data->unk3C) * 65.0f * 0.75f;
    offsetZ = cosdf(data->unk3C) * 65.0f * 0.75f;
    switch (MgFlowStatGet()) {
        case MG_STATE_FINISH:
            if (MgFlowStatTimeGet() == 0) {
                MgPlayerRadiusSet(object, 60.0f);
                object->trans.x -= offsetX;
                object->trans.z -= offsetZ;
            }
            if (data->unk3C == 0.0f) {
                Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
            } else {
                Hu3DModelPosSet(object->model[1], object->trans.x - offsetX, 0.0f, object->trans.z - offsetZ);
            }
            break;
        case MG_STATE_RESULT:
        case MG_STATE_EXIT:
            Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
            break;
        default:
            Hu3DModelPosSet(object->model[1], object->trans.x - offsetX, 0.0f, object->trans.z - offsetZ);
            break;
    }
    Hu3DModelPosSet(object->model[2], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelRotSet(object->model[2], object->rot.x, data->unk3C, object->rot.z);
    if (MgPlayerMotStatGet(object) == MGPLAYER_MOTSTAT_IDLE) {
        Hu3DMotionAttrSet(object->model[2], 2, 1);
    } else {
        Hu3DMotionAttrSet(object->model[2], 2, 2);
    }
    switch (MgFlowStatGet()) {
        case MG_STATE_OPENING:
        case MG_STATE_START:
        case MG_STATE_EXIT:
            m218_PlayerScaleSet(object, 0.75f);
            return;
        case MG_STATE_FINISH:
            if (MgFlowStatTimeGet() == 0) {
                Hu3DModelAttrSet(object->model[2], 4, 4);
                MgPlayerMotSet(object, 38);
            }
            data->unk3C = m218_AngleWrap(data->unk3C);
            if (data->unk3C < 0.0f) {
                data->unk3C += 360.0f;
            } else if (data->unk3C > 360.0f) {
                data->unk3C -= 360.0f;
            }
            if (data->unk3C > 10.0f && data->unk3C < 180.0f) {
                data->unk3C -= 10.0f;
            } else if (data->unk3C >= 180.0f && data->unk3C < 350.0f) {
                data->unk3C += 10.0f;
            } else {
                data->unk3C = 0.0f;
            }
            m218_PlayerScaleSet(object, 0.75f);
            break;
    }
    pos.x = object->trans.x;
    pos.y = object->trans.y;
    pos.z = object->trans.z;
    Hu3DCam3Dto2D(0, &pos, &screenPos);
    if (m218_curPlayerWork->unk_08 != m218_curPlayerWork->unk_04 ||
        m218_curPlayerWork->unk_0A != m218_curPlayerWork->unk_06) {
        m218_curPlayerWork->unk_08 = m218_curPlayerWork->unk_04;
        m218_curPlayerWork->unk_0A = m218_curPlayerWork->unk_06;
    }
    m218_curPlayerWork->unk_04 = screenPos.x;
    m218_curPlayerWork->unk_06 = screenPos.y;
    if (MgFlowStatGet() == MG_STATE_PLAY) {
        if (m218_curPlayerWork->unk_12 == 0 && (data->unk5C & 4) && Hu3DData[object->model[0]].motTime == 0.0f) {
            m218_curPlayerWork->unk_10 = PlayerFXPlay(0x37F, data->unk59);
            if (m218_curPlayerWork->unk_02 == 8) {
                HuAudFXPanning(m218_curPlayerWork->unk_10, 32);
            } else {
                HuAudFXPanning(m218_curPlayerWork->unk_10, 95);
            }
            m218_curPlayerWork->unk_12 = 1;
        } else if (m218_curPlayerWork->unk_12 == 1 && data->unk40 == mgPlayerSpeedZero) {
            HuAudFXStop(m218_curPlayerWork->unk_10);
            m218_curPlayerWork->unk_12 = 0;
        }
    } else if (MgFlowStatGet() == MG_STATE_FINISH) {
        HuAudFXStop(m218_curPlayerWork->unk_10);
        m218_curPlayerWork->unk_12 = 0;
    }
    if (MgFlowStatGet() == MG_STATE_PLAY && m218_curPlayerWork->unk_08 != 0 && m218_curPlayerWork->unk_0A != 0) {
        while (m218_curPlayerWork->unk_08 != m218_curPlayerWork->unk_04 ||
               m218_curPlayerWork->unk_0A != m218_curPlayerWork->unk_06) {
            newNode = m218_LineNodeFreeGet(data->unk59);
            memset(newNode, 0, sizeof(EtchNCatchNode));
            newNode->unk_00 = 1;
            newNode->unk_16 = 106;
            newNode->unk_18 = m218_curPlayerWork->unk_08;
            newNode->unk_1A = m218_curPlayerWork->unk_0A;
            newNode->unk_1C = data->unk59;
            newNode->unk_10 = NULL;
            newNode->unk_0C = NULL;
            newNode->unk_08 = NULL;
            newNode->unk_04 = NULL;
            m218_LineNodeAdd(&m218_curPlayerWork->unk_0C, newNode);
            newNode->unk_2C = 0;
            newNode->unk_30 = 1.0f;
            switch (rand8() >> 6) {
                case 0:
                    newNode->unk_20.x = object->trans.x + 10.0f;
                    newNode->unk_20.z = object->trans.z + 10.0f;
                    break;
                case 1:
                    newNode->unk_20.x = object->trans.x - 10.0f;
                    newNode->unk_20.z = object->trans.z - 10.0f;
                    break;
                case 2:
                    newNode->unk_20.x = object->trans.x + 10.0f;
                    newNode->unk_20.z = object->trans.z - 10.0f;
                    break;
                default:
                    newNode->unk_20.x = object->trans.x - 10.0f;
                    newNode->unk_20.z = object->trans.z + 10.0f;
                    break;
            }
            newNode->unk_20.y = object->trans.y;
            if (m218_GridValueGet(m218_curPlayerWork->unk_08, m218_curPlayerWork->unk_0A) ==
                m218_curPlayerWork->unk_02) {
                found = 0;
                for (i = 0; i < 4; i++) {
                    if (found == 1) {
                        break;
                    }
                    for (node = m218_playerWorkTbl[i]->unk_0C; node != NULL; node = node->unk_08) {
                        if (newNode != node && node->unk_18 == newNode->unk_18 && node->unk_1A == newNode->unk_1A) {
                            while (node->unk_0C != NULL) {
                                node = node->unk_0C;
                            }
                            found = 1;
                            node->unk_0C = newNode;
                            newNode->unk_10 = node;
                            break;
                        }
                    }
                }
            }
            newNode->unk_14 |= m218_curPlayerWork->unk_00;
            m218_GridValueSet(m218_curPlayerWork->unk_08, m218_curPlayerWork->unk_0A,
                                       m218_curPlayerWork->unk_02);
            newNode->unk_15 = m218_curPlayerWork->unk_02;
            m218_regionTbl[m218_curPlayerWork->unk_06 / 2][m218_curPlayerWork->unk_04 / 2] |=
                m218_curPlayerWork->unk_00;
            if ((HuPadStkX[data->unk57] != 0 || HuPadStkY[data->unk57] != 0) &&
                m218_LineLoopCheck(m218_curPlayerWork)) {
                if (object->trans.x < 0.0f) {
                    m218_leftLoopF = 1;
                } else {
                    m218_rightLoopF = 1;
                }
            }
            dir = m218_DirCalc(m218_curPlayerWork->unk_08, m218_curPlayerWork->unk_0A,
                                             m218_curPlayerWork->unk_04, m218_curPlayerWork->unk_06);
            if (dir.x <= -0.5f) {
                m218_curPlayerWork->unk_08--;
            } else if (dir.x >= 0.5f) {
                m218_curPlayerWork->unk_08++;
            }
            if (dir.y <= -0.5f) {
                m218_curPlayerWork->unk_0A--;
            } else if (dir.y >= 0.5f) {
                m218_curPlayerWork->unk_0A++;
            }
        }
    }
    if (data->unk59 == 3) {
        if (m218_fillSideF == 0 && m218_leftLoopF != 0 && m218_cageObjTbl[0]->work[0] == 3 &&
            m218_kinopioObjTbl[0]->work[0] < 5) {
            m218_kinopioObjTbl[0]->work[1] =
                m218_FillCheck(m218_kinopioGridPosTbl[0][0], m218_kinopioGridPosTbl[0][1]);
            if (m218_kinopioObjTbl[0]->work[1] != 0) {
                m218_kinopioObjTbl[0]->work[0] = 5;
                for (i = 0; i < 4; i++) {
                    if (m218_playerWorkTbl[i]->unk_01 == 3) {
                        otherData = mgPlayerObjTbl[i]->data;
                        omVibrate(otherData->unk59, 2, 3, 10);
                    }
                }
            }
            m218_leftLoopF = 0;
        } else if (m218_fillSideF != 0 && m218_rightLoopF != 0 &&
                   m218_cageObjTbl[1]->work[0] == 3 && m218_kinopioObjTbl[1]->work[0] < 5) {
            m218_kinopioObjTbl[1]->work[1] =
                m218_FillCheck(m218_kinopioGridPosTbl[1][0], m218_kinopioGridPosTbl[1][1]);
            if (m218_kinopioObjTbl[1]->work[1] != 0) {
                m218_kinopioObjTbl[1]->work[0] = 5;
                for (i = 0; i < 4; i++) {
                    if (m218_playerWorkTbl[i]->unk_01 == 12) {
                        otherData = mgPlayerObjTbl[i]->data;
                        omVibrate(otherData->unk59, 2, 3, 10);
                    }
                }
            }
            m218_rightLoopF = 0;
        }
        m218_fillSideF ^= 1;
    }
    m218_PlayerScaleSet(object, 0.75f);
    gridX = m218_kinopioGridPosTbl[side][0] * 2;
    gridY = m218_kinopioGridPosTbl[side][1] * 2;
    if (m218_GridHitCheck(gridX, gridY)) {
        for (i = 0; i < 32; i++) {
            nodes[i] = NULL;
        }
        count = 0;
        for (node = m218_curPlayerWork->unk_0C; node != NULL; node = node->unk_08) {
            if (IABS(gridX - node->unk_18) < 2 && IABS(gridY - node->unk_1A) < 2) {
                nodes[count++] = node;
            }
        }
        for (i = 0; i < count; i++) {
            for (node = nodes[i]; node != NULL; node = node->unk_04) {
                node->unk_16 = 17;
            }
        }
    }
    if (data->unk59 == 3) {
        for (j = 0; j < 4; j++) {
            m218_curPlayerWork = m218_playerWorkTbl[j];
            if (m218_curPlayerWork != NULL) {
                for (node = m218_curPlayerWork->unk_0C; node != NULL; node = node->unk_08) {
                    node->unk_16--;
                    if (node->unk_16 <= 16) {
                        if (node->unk_16 == 16) {
                            for (i = 0; i < 4; i++) {
                                if (node->unk_0C != NULL) {
                                    if (node->unk_0C->unk_15 != m218_playerWorkTbl[i]->unk_02) {
                                        m218_regionTbl[node->unk_1A / 2][node->unk_18 / 2] &=
                                            ~m218_playerWorkTbl[i]->unk_00;
                                    }
                                } else {
                                    m218_regionTbl[node->unk_1A / 2][node->unk_18 / 2] &=
                                        ~m218_playerWorkTbl[i]->unk_00;
                                }
                            }
                            m218_LineNodeErase(node, m218_curPlayerWork->unk_02);
                        } else if (node->unk_16 > 0) {
                            if (node->unk_1E != -1) {
                                m218_LineMdlSet(node);
                            }
                        } else {
                            Hu3DModelAttrSet(node->unk_1E, 4, 4);
                            m218_LineNodeRemove(&m218_curPlayerWork->unk_0C, node);
                        }
                    }
                }
            }
        }
        HuPadBtnDown[data->unk57] = buttons;
    }
}

s32 m218_AreaOutCheck(f32 x, f32 z, EtchNCatchWork *work) {
    s32 result;

    if (work->unk_01 == 3) {
        if (x < -80.0f && x > -450.0f && z < 300.0f && z > -400.0f) {
            result = FALSE;
        } else {
            result = TRUE;
        }
    } else {
        if (x > 80.0f && x < 450.0f && z < 300.0f && z > -400.0f) {
            result = FALSE;
        } else {
            result = TRUE;
        }
    }
    return result;
}

void m218_PlayerComInput(omObjData *object) {
    MgPlayerWork *data = object->data;
    EtchNCatchWork *work = m218_playerWorkTbl[data->unk59];
    omObjData *target;
    Vec2f dir;
    f32 radius;
    f32 dx;
    f32 dz;
    f32 x;
    f32 z;
    s8 speed;
    s32 side;

    if (MgFlowStatGet() != MG_STATE_PLAY) {
        return;
    }
    switch (GwPlayer[data->unk59].cpu_difficulty) {
        case 3:
            speed = 60;
            radius = 200.0f;
            break;
        case 2:
            speed = 60;
            radius = 250.0f;
            break;
        case 1:
        default:
            speed = 57;
            radius = 300.0f;
            break;
        case 0:
            speed = 54;
            radius = 350.0f;
            break;
    }
    side = (object->trans.x < 0.0f) ? 0 : 1;
    if (m218_kinopioObjTbl[side]->work[0] >= 6 || m218_cageObjTbl[side]->work[0] != 3) {
        HuPadStkX[data->unk57] = 0;
        HuPadStkY[data->unk57] = 0;
        return;
    }
    if (object->trans.x < 0.0f) {
        target = m218_kinopioObjTbl[0];
    } else {
        target = m218_kinopioObjTbl[1];
    }
    dx = ABS(target->trans.x - object->trans.x);
    dz = ABS(target->trans.z - object->trans.z);
    if (HuSqrtf(dx * dx + dz * dz) > 375.0f) {
        m218_comStateTbl[data->unk59] = 0;
    }
    switch (m218_comStateTbl[data->unk59]) {
        case 0:
            if (work->unk_00 == 1 || work->unk_00 == 4) {
                dir = m218_DirCalc(object->trans.x, object->trans.z, target->trans.x, target->trans.z - 75.0f);
            } else {
                dir = m218_DirCalc(object->trans.x, object->trans.z, target->trans.x, target->trans.z + 75.0f);
            }
            HuPadStkX[data->unk57] = speed * dir.x;
            HuPadStkY[data->unk57] = -(speed * dir.y);
            dx = ABS(target->trans.x - object->trans.x);
            if (work->unk_00 == 1 || work->unk_00 == 4) {
                dz = ABS(target->trans.z - 75.0f - object->trans.z);
            } else {
                dz = ABS(target->trans.z + 75.0f - object->trans.z);
            }
            if (HuSqrtf(dx * dx + dz * dz) < 50.0f) {
                m218_comStateTbl[data->unk59] = 1;
            }
            break;
        case 1:
            if (work->unk_00 == 1 || work->unk_00 == 4) {
                data->unk3C = m218_AngleWrap(data->unk3C);
                if (ABS(data->unk3C - 90.0f) < 5.0f) {
                    data->unk3C = 90.0f;
                    m218_comStateTbl[data->unk59] = 2;
                } else {
                    HuPadStkX[data->unk57] = speed / 2;
                    HuPadStkY[data->unk57] = 0;
                }
            }
            if (work->unk_00 == 2 || work->unk_00 == 8) {
                data->unk3C = m218_AngleWrap(data->unk3C);
                if (ABS(data->unk3C - 270.0f) < 5.0f) {
                    data->unk3C = 270.0f;
                    m218_comStateTbl[data->unk59] = 2;
                } else {
                    HuPadStkX[data->unk57] = -speed / 2;
                    HuPadStkY[data->unk57] = 0;
                }
            }
            break;
        case 2:
            data->unk3C += 5.0f;
            if (data->unk3C > 360.0f) {
                data->unk3C -= 360.0f;
            }
            x = sindf(data->unk3C) * (radius + 75.0f) + target->trans.x;
            z = cosdf(data->unk3C) * (radius + 75.0f) + target->trans.z;
            dir = m218_DirCalc(object->trans.x, object->trans.z, x, z);
            HuPadStkX[data->unk57] = speed * dir.x;
            HuPadStkY[data->unk57] = -(speed * dir.y);
            break;
    }
    x = sindf(data->unk3C) * 65.0f * 0.75f + object->trans.x;
    z = cosdf(data->unk3C) * 65.0f * 0.75f + object->trans.z;
    if (m218_AreaOutCheck(x, z, work)) {
        data->unk3C += 20.0f;
        if (data->unk3C > 360.0f) {
            data->unk3C -= 360.0f;
        }
        x = sindf(data->unk3C) * 10.0f + object->trans.x;
        z = cosdf(data->unk3C) * 10.0f + object->trans.z;
        dir = m218_DirCalc(object->trans.x, object->trans.z, x, z);
        HuPadStkX[data->unk57] = speed * dir.x;
        HuPadStkY[data->unk57] = -(speed * dir.y);
    }
}

void m218_StickTurnLimit(MgPlayerWork *data) {
    f32 stickX = HuPadStkX[data->unk57];
    f32 stickY = -HuPadStkY[data->unk57];
    f32 angle;
    f32 diff;
    f32 magnitude;

    if (FABS(stickX) < 8.0f && FABS(stickY) < 8.0f) {
        angle = data->unk3C;
    } else {
        angle = atan2df(stickX, stickY);
    }
    angle = m218_AngleWrap(angle);
    data->unk3C = m218_AngleWrap(data->unk3C);
    diff = angle - data->unk3C;
    if (ABS(diff) > 30.0f) {
        if ((diff > 0.0f && diff < 180.0f) || (diff < -180.0f && diff > -360.0f)) {
            angle = data->unk3C + 30.0f;
        } else {
            angle = data->unk3C - 30.0f;
        }
    } else {
        angle = diff + data->unk3C;
    }
    angle = m218_AngleWrap(angle);
    magnitude = HuSqrtf(stickX * stickX + stickY * stickY);
    HuPadStkX[data->unk57] = sindf(angle) * magnitude;
    HuPadStkY[data->unk57] = -cosdf(angle) * magnitude;
}

void m218_LineInit(EtchNCatchWork *arg0) {
    arg0->unk_0C = NULL;
}

EtchNCatchNode *m218_LineNodeFreeGet(s8 playerId) {
    EtchNCatchNode *node = m218_lineNodeTbl[playerId];
    s32 i;

    for (i = 0; i < 0x100; i++) {
        if (node->unk_00 == 0) {
            break;
        }
        node++;
    }
    return node;
}

void m218_LineNodeAdd(EtchNCatchNode **head, EtchNCatchNode *node) {
    EtchNCatchNode *prev = *head;

    if (prev != NULL) {
        while (prev->unk_08 != NULL) {
            prev = prev->unk_08;
        }
        node->unk_08 = prev->unk_08;
        node->unk_04 = prev;
        prev->unk_08 = node;
        if (node->unk_08 != NULL) {
            node->unk_08->unk_04 = node;
        }
        return;
    }

    node->unk_08 = *head;
    node->unk_04 = NULL;
    *head = node;
    if (prev != NULL) {
        prev->unk_04 = node;
    }
}

void m218_LineNodeRemove(EtchNCatchNode **head, EtchNCatchNode *node) {
    if (node->unk_08 != NULL) {
        node->unk_08->unk_04 = node->unk_04;
    }
    if (node->unk_04 != NULL) {
        node->unk_04->unk_08 = node->unk_08;
    } else {
        *head = node->unk_08;
    }
    node->unk_00 = 0;
}

s32 m218_LineLoopCheck(EtchNCatchWork *work) {
    EtchNCatchNode *node;
    s32 count = 0;
    s32 i;

    if (m218_playerWorkTbl[0]->unk_0C == NULL && m218_playerWorkTbl[1]->unk_0C == NULL &&
        m218_playerWorkTbl[2]->unk_0C == NULL && m218_playerWorkTbl[3]->unk_0C == NULL) {
        return FALSE;
    }
    for (i = 0; i < 4; i++) {
        for (node = m218_playerWorkTbl[i]->unk_0C; node != NULL; node = node->unk_08) {
            if (node->unk_18 == work->unk_04 - 1) {
                count += node->unk_1A == work->unk_06 - 1;
                count += node->unk_1A == work->unk_06;
                count += node->unk_1A == work->unk_06 + 1;
            }
            if (node->unk_18 == work->unk_04) {
                count += node->unk_1A == work->unk_06 - 1;
                count += node->unk_1A == work->unk_06 + 1;
            }
            if (node->unk_18 == work->unk_04 + 1) {
                count += node->unk_1A == work->unk_06 - 1;
                count += node->unk_1A == work->unk_06;
                count += node->unk_1A == work->unk_06 + 1;
            }
            if (count >= 3) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

// Undoes the "filled" mark on every grid cell appended to the touched-cell list
// up to (but not including) arg0. arg1-arg3 are unused.
void m218_FillUndo(u8 **arg0, u8 *arg1, u8 **arg2, s32 arg3) {
    u8 **cellPtr = m218_fillCellList;
    // arg0 points one past the last appended cell, so the difference is a byte offset.
    s32 count = ((s32)arg0 - (s32)cellPtr) >> 2;
    s32 i;

    for (i = 0; i < count; i++) {
        u8 *cell = *cellPtr++;
        if (cell[0] == ETCH_N_CATCH_CELL_FILLED) {
            cell[0] = 0;
        }
    }
}

s32 m218_FillCheck(s16 x, s16 y) {
    u8 **list;
    u8 **readBuf;
    u8 **writeBuf;
    u8 **read;
    u8 **write;
    u8 *cell;
    s32 count;
    s32 i;
    s32 offset;
    s32 row;
    s32 col;
    s32 flags = 0;

    cell = m218_gridBuf + x * 2 + y * (m218_gridW << 1);
    list = m218_fillCellList;
    *cell = ETCH_N_CATCH_CELL_FILLED;
    read = m218_fillQueueTbl[0];
    *read = *list++ = cell;
    count = 1;
    write = writeBuf = m218_fillQueueTbl[1];
    read = readBuf = m218_fillQueueTbl[0];
    while (count != 0) {
        for (i = 0; i < count; i++) {
            cell = *read++;
            *cell = ETCH_N_CATCH_CELL_FILLED;
            offset = cell - m218_gridBuf;
            row = offset / 320;
            col = offset % 320;
            col >>= 1;
            row >>= 1;
            cell++;
            if (*cell == 0) {
                *cell = ETCH_N_CATCH_CELL_FILLED;
                *write++ = *list++ = cell;
            } else if (*cell == ETCH_N_CATCH_CELL_EDGE) {
                m218_FillUndo(list, cell, readBuf, count);
                return FALSE;
            } else if ((*cell & 9) == 0) {
                *list++ = cell;
            } else {
                flags |= m218_regionTbl[row][col + 1];
            }
            cell -= 2;
            if (*cell == 0) {
                *cell = ETCH_N_CATCH_CELL_FILLED;
                *write++ = *list++ = cell;
            } else if (*cell == ETCH_N_CATCH_CELL_EDGE) {
                m218_FillUndo(list, cell, readBuf, count);
                return FALSE;
            } else if ((*cell & 9) == 0) {
                *list++ = cell;
            } else {
                flags |= m218_regionTbl[row][col - 1];
            }
            cell += m218_gridW + 1;
            if (*cell == 0) {
                *cell = ETCH_N_CATCH_CELL_FILLED;
                *write++ = *list++ = cell;
            } else if (*cell == ETCH_N_CATCH_CELL_EDGE) {
                m218_FillUndo(list, cell, readBuf, count);
                return FALSE;
            } else if ((*cell & 9) == 0) {
                *list++ = cell;
            } else {
                flags |= m218_regionTbl[row + 1][col];
            }
            cell -= m218_gridW * 2;
            if (*cell == 0) {
                *cell = ETCH_N_CATCH_CELL_FILLED;
                *write++ = *list++ = cell;
            } else if (*cell == ETCH_N_CATCH_CELL_EDGE) {
                m218_FillUndo(list, cell, readBuf, count);
                return FALSE;
            } else if ((*cell & 9) == 0) {
                *list++ = cell;
            } else {
                flags |= m218_regionTbl[row - 1][col];
            }
        }
        count = write - writeBuf;
        write = readBuf;
        readBuf = writeBuf;
        writeBuf = write;
        read = readBuf;
    }
    m218_FillUndo(list, cell, readBuf, count);
    return flags == 3 || flags == 12;
}

u8 *m218_GridCellGet(s16 x, s16 y) {
    return m218_gridBuf + m218_gridW * y + x;
}

u8 m218_GridValueGet(s16 x, s16 y) {
    u8 *p = m218_gridBuf + m218_gridW * y + x;
    return *p;
}

void m218_GridValueSet(s16 x, s16 y, u8 value) {
    u8 *cell;

    *m218_GridCellGet(x, y) = value;
    cell = m218_GridCellGet(x - 1, y);
    if (*cell != value) {
        *cell = value << 1;
    }
    cell = m218_GridCellGet(x + 1, y);
    if (*cell != value) {
        *cell = value << 1;
    }
    cell = m218_GridCellGet(x, y - 1);
    if (*cell != value) {
        *cell = value << 1;
    }
    cell = m218_GridCellGet(x, y + 1);
    if (*cell != value) {
        *cell = value << 1;
    }
    cell = m218_GridCellGet(x - 1, y - 1);
    if (*cell != value && *cell != (value << 1)) {
        *cell = value << 2;
    }
    cell = m218_GridCellGet(x - 1, y + 1);
    if (*cell != value && *cell != (value << 1)) {
        *cell = value << 2;
    }
    cell = m218_GridCellGet(x + 1, y + 1);
    if (*cell != value && *cell != (value << 1)) {
        *cell = value << 2;
    }
    cell = m218_GridCellGet(x + 1, y - 1);
    if (*cell != value && *cell != (value << 1)) {
        *cell = value << 2;
    }
}

void m218_LineNodeErase(EtchNCatchNode *node, u8 value) {
    u8 *cells[8];
    u8 *cell;
    s32 x;
    s32 y;
    s32 i;

    cell = m218_GridCellGet(node->unk_18, node->unk_1A);
    if (node->unk_0C == NULL && node->unk_10 == NULL) {
        *cell = 0;
    }
    if (node->unk_10 != NULL && node->unk_0C != NULL) {
        node->unk_10->unk_0C = node->unk_0C;
        node->unk_0C->unk_10 = node->unk_10;
    } else if (node->unk_10 != NULL && node->unk_0C == NULL) {
        node->unk_10->unk_0C = NULL;
    } else if (node->unk_10 == NULL && node->unk_0C != NULL) {
        node->unk_0C->unk_10 = NULL;
    }
    for (i = 0; i < 8; i++) {
        switch (i) {
            case 0:
                x = node->unk_18;
                y = node->unk_1A - 1;
                break;
            case 1:
                x = node->unk_18;
                y = node->unk_1A + 1;
                break;
            case 2:
                x = node->unk_18 - 1;
                y = node->unk_1A;
                break;
            case 3:
                x = node->unk_18 + 1;
                y = node->unk_1A;
                break;
            case 4:
                x = node->unk_18 - 1;
                y = node->unk_1A - 1;
                break;
            case 5:
                x = node->unk_18 + 1;
                y = node->unk_1A + 1;
                break;
            case 6:
                x = node->unk_18 - 1;
                y = node->unk_1A + 1;
                break;
            default:
                x = node->unk_18 + 1;
                y = node->unk_1A - 1;
                break;
        }
        cell = m218_GridCellGet(x, y);
        if (node->unk_10 != NULL || node->unk_0C != NULL) {
            if (i >= 0) {
                if (i < 4) {
                    if (*cell != value) {
                        *cell = value << 1;
                    }
                } else if (i < 8) {
                    if (*cell != value && *cell != (value << 1)) {
                        *cell = value << 2;
                    }
                }
            }
        }
        cells[0] = m218_GridCellGet(x, y + 1);
        cells[1] = m218_GridCellGet(x, y - 1);
        cells[2] = m218_GridCellGet(x - 1, y);
        cells[3] = m218_GridCellGet(x + 1, y);
        cells[4] = m218_GridCellGet(x - 1, y - 1);
        cells[5] = m218_GridCellGet(x + 1, y + 1);
        cells[6] = m218_GridCellGet(x - 1, y + 1);
        cells[7] = m218_GridCellGet(x + 1, y - 1);
        if (*cells[0] != value && *cells[1] != value && *cells[2] != value && *cells[3] != value &&
            *cells[4] != value && *cells[5] != value && *cells[6] != value && *cells[7] != value) {
            *cell = 0;
        } else if (*cells[0] == value || *cells[1] == value || *cells[2] == value || *cells[3] == value) {
            if (*cell != value) {
                *cell = value << 1;
            }
        } else if (*cells[4] == value || *cells[5] == value || *cells[6] == value || *cells[7] == value) {
            if (*cell != value && *cell != (value << 1)) {
                *cell = value << 2;
            }
        }
    }
}

void m218_LineMdlSet(EtchNCatchNode *node) {
    if (node->unk_2C == 0) {
        if (m218_lineMdlNoTbl[node->unk_1C] == 0) {
            if (m218_lineMdlUseTbl[node->unk_1C][0] == 0) {
                node->unk_1E = m218_lineMdlTbl[node->unk_1C][0];
                node->unk_34 = 0;
                m218_lineMdlUseTbl[node->unk_1C][0] = 1;
            } else if (m218_lineMdlUseTbl[node->unk_1C][1] == 0) {
                node->unk_1E = m218_lineMdlTbl[node->unk_1C][1];
                node->unk_34 = 1;
                m218_lineMdlUseTbl[node->unk_1C][1] = 1;
            } else if (m218_lineMdlUseTbl[node->unk_1C][2] == 0) {
                node->unk_1E = m218_lineMdlTbl[node->unk_1C][2];
                node->unk_34 = 2;
                m218_lineMdlUseTbl[node->unk_1C][2] = 1;
            } else {
                node->unk_1E = -1;
                node->unk_34 = 0xFF;
            }
        } else {
            node->unk_1E = -1;
            node->unk_34 = 0xFF;
        }
        m218_lineMdlNoTbl[node->unk_1C]++;
        if (m218_lineMdlNoTbl[node->unk_1C] > 8) {
            m218_lineMdlNoTbl[node->unk_1C] = 0;
        }
    }
    if (node->unk_1E != -1) {
        node->unk_2C++;
        node->unk_30 += 0.05f;
        if (node->unk_30 > 1.5f) {
            node->unk_30 = 1.5f;
        }
        Hu3DModelScaleSet(node->unk_1E, node->unk_30, node->unk_30, node->unk_30);
        Hu3DModelPosSet(node->unk_1E, node->unk_20.x, node->unk_20.y, node->unk_20.z);
        node->unk_20.y += 5.0f;
        if (node->unk_2C >= 15) {
            Hu3DModelAttrSet(node->unk_1E, 4, 4);
            m218_lineMdlUseTbl[node->unk_1C][node->unk_34] = 0;
        } else {
            Hu3DModelTPLvlSet(node->unk_1E, 255 - node->unk_2C * 16);
            Hu3DModelAttrSet(node->unk_1E, 4, 0);
        }
    }
}

void m218_KinopioObjInit(omObjData *object) {
    EtchNCatchKinopioData *data;
    s32 file = 0xA0000;
    s32 i;

    if (m218_kinopioNum == 0) {
        m218_kinopioMdl = object->model[0] = Hu3DModelRead(0xA0000, 0x8BD);
    } else {
        object->model[0] = Hu3DModelLink(m218_kinopioMdl);
    }
    Hu3DModelAttrSet(object->model[0], 4, 0);
    object->data = HuMemAllocTag(sizeof(EtchNCatchKinopioData), TAG_OVERLAY);
    memset(object->data, 0, sizeof(EtchNCatchKinopioData));
    data = object->data;
    data->base.unkE8 = HuMemAllocTag(object->mtncnt * sizeof(MgMotAttr), TAG_OVERLAY);
    data->base.unk5A = object->model[0];
    data->base.unk5B = 0;
    data->unk160 = m218_kinopioNum % 2;
    data->unk168 = 0.0f;
    omObjMotionRead(object, 2, file | 8);
    omObjMotionRead(object, 3, file);
    Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[2]].motId, 0, 1, 2);
    switch (data->unk160) {
        case 0:
            object->trans.x = m218_kinopioPosTbl[0].x;
            break;
        case 1:
            object->trans.x = -m218_kinopioPosTbl[0].x;
            break;
    }
    object->trans.y = m218_kinopioPosTbl[0].y;
    object->trans.z = m218_kinopioPosTbl[0].z;
    object->rot.x = object->rot.y = object->rot.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    object->work[0] = 10;
    object->work[1] = 0;
    data->unk15C = 0;
    data->unk164 = 0.5f;
    data->unk170 = data->unk174 = 0.0f;
    data->unk161 = 0;
    if (m218_kinopioNum == 0) {
        m218_shadowMdl = object->model[6] = Hu3DModelRead(9, 0x8BD);
    } else {
        object->model[6] = Hu3DModelLink(m218_shadowMdl);
    }
    Hu3DModelPosSet(object->model[6], object->trans.x, 0.0f, object->trans.z);
    for (i = 0; i < 5; i++) {
        if (i == 0) {
            object->model[1] = Hu3DModelRead(0x330006, 0x8AD);
        } else {
            object->model[i + 1] = Hu3DModelLink(object->model[1]);
        }
        Hu3DMotionAttrSet(object->model[i + 1], 2, 2);
        Hu3DModelTPLvlInit(object->model[i + 1]);
        data->unk1B4 = 0.0f;
        data->unk178[i].y = 1.0f;
    }
    data->unk178[0].x = 0.8660254f;
    data->unk178[0].z = -0.5f;
    data->unk178[1].x = 0.8660254f;
    data->unk178[1].z = 0.5f;
    data->unk178[2].x = 0.0f;
    data->unk178[2].z = 1.0f;
    data->unk178[3].x = -0.8660254f;
    data->unk178[3].z = 0.5f;
    data->unk178[4].x = -0.8660254f;
    data->unk178[4].z = -0.5f;
    m218_kinopioMarkSprTbl[data->unk160] = espEntry(HuSprAnimDataRead(0x330005), 0, 1);
    espAttrSet(m218_kinopioMarkSprTbl[data->unk160], 0x5000);
    espPosSet(m218_kinopioMarkSprTbl[data->unk160], 0, 0);
    espScaleSet(m218_kinopioMarkSprTbl[data->unk160], 0.5f, 0.5f);
    espTPLvlSet(m218_kinopioMarkSprTbl[data->unk160], 0xCC);
    espDispOff(m218_kinopioMarkSprTbl[data->unk160]);
    object->func = m218_KinopioObjMain;
    m218_kinopioNum++;
}

void m218_KinopioObjMain(omObjData *object) {
    Vec2f screen;
    Vec pos;
    f32 angles[8] = { 1.0f, 46.0f, 91.0f, 136.0f, 181.0f, 226.0f, 271.0f, 316.0f };
    EtchNCatchKinopioData *data = object->data;
    f32 x;
    f32 z;
    s32 i;

    pos.x = object->trans.x;
    pos.y = 0.0f;
    pos.z = object->trans.z;
    Hu3DCam3Dto2D(0, &pos, &screen);
    m218_kinopioGridPosTbl[data->unk160][0] = screen.x / 2.0f;
    m218_kinopioGridPosTbl[data->unk160][1] = screen.y / 2.0f;
    switch (object->work[0]) {
        case 0:
            object->trans.x = m218_cageObjTbl[data->unk160]->trans.x;
            object->trans.y = 0.0f;
            object->trans.z = m218_cageObjTbl[data->unk160]->trans.z;
            pos.x = object->trans.x;
            pos.y = 0.0f;
            pos.z = object->trans.z;
            Hu3DCam3Dto2D(0, &pos, &screen);
            espPosSet(m218_kinopioMarkSprTbl[data->unk160], screen.x, screen.y);
            data->unk164 = 0.5f;
            espScaleSet(m218_kinopioMarkSprTbl[data->unk160], data->unk164, data->unk164);
            data->unk170 = data->unk174 = 0.0f;
            espZRotSet(m218_kinopioMarkSprTbl[data->unk160], data->unk170);
            espDispOn(m218_kinopioMarkSprTbl[data->unk160]);
            Hu3DModelAttrSet(object->model[0], 4, 4);
            Hu3DModelAttrSet(object->model[6], 4, 4);
            for (i = 0; i < 5; i++) {
                Hu3DModelAttrSet(object->model[i + 1], 4, 4);
            }
            data->unk15C = 0;
            object->work[0] = 1;
            break;
        case 5:
            data->unk168 += 2.0f;
            object->trans.y += data->unk168 + 5.0f;
            Hu3DModelPosSet(object->model[0], object->trans.x, 0.0f, object->trans.z);
            Hu3DModelPosSet(object->model[6], object->trans.x, 0.0f, object->trans.z);
            if (m218_kinopioCatchStepTbl[data->unk160] == 0) {
                if (data->unk160 == 0) {
                    HuAudFXPanning(HuAudFXPlay(0x37D), 0x20);
                } else {
                    HuAudFXPanning(HuAudFXPlay(0x37E), 0x5F);
                }
                data->unk164 = 1.0f;
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[2]].motId, 0, 1, 2);
                Hu3DMotionTimeSet(object->model[0], 0.0f);
                data->unk15C = 0;
                data->unk1B4 = 0.0f;
                m218_kinopioCatchStepTbl[data->unk160] = 1;
            } else {
                espDispOff(m218_kinopioMarkSprTbl[data->unk160]);
                Hu3DModelAttrSet(object->model[0], 4, 0);
                Hu3DModelAttrSet(object->model[6], 4, 0);
                for (i = 0; i < 5; i++) {
                    Hu3DMotionTimeSet(object->model[i + 1], 0.0f);
                }
                m218_KinopioCatchEffUpdate(object);
                if (data->unk160 == 0) {
                    m218_team0Score++;
                } else {
                    m218_team1Score++;
                }
                m218_kinopioCatchStepTbl[data->unk160] = 0;
                data->unk15C = 0;
                object->work[0] = 6;
            }
            break;
        case 6:
            if (data->unk15C < 10) {
                m218_KinopioCatchEffUpdate(object);
            } else {
                for (i = 0; i < 5; i++) {
                    Hu3DModelAttrSet(object->model[i + 1], 4, 4);
                }
            }
            if (data->unk15C >= Hu3DMotion[Hu3DData[object->model[0]].motId].unk02 / 2.0f - 2.0f) {
                Hu3DMotionAttrSet(object->model[0], 2, 1);
                object->work[0] = 8;
                data->unk15C = 0;
            } else {
                data->unk168 += 2.0f;
                object->trans.y += data->unk168 + 5.0f;
                data->unk15C++;
            }
            break;
        case 8:
            data->unk168 += 2.0f;
            object->trans.y += data->unk168 + 5.0f;
            for (i = 0; i < 5; i++) {
                Hu3DModelAttrSet(object->model[i + 1], 4, 4);
            }
            object->work[0] = 9;
            m218_cageObjTbl[data->unk160]->work[0] = 0;
            break;
        case 9:
            for (i = 0; i < 5; i++) {
                Hu3DModelAttrSet(object->model[i + 1], 4, 4);
            }
            data->unk15C++;
            object->trans.y += data->unk168 + 5.0f;
            if (object->trans.y > 800.0f && data->unk164 == 0.0f) {
                data->unk168 = 0.0f;
                data->unk15C = 0;
                object->work[0] = 10;
            } else {
                data->unk168 += 2.0f;
                data->unk164 -= 0.05f;
                if (data->unk164 < 0.0f) {
                    data->unk164 = 0.0f;
                }
            }
            Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
            Hu3DModelScaleSet(object->model[6], data->unk164, data->unk164, data->unk164);
            break;
        case 10:
            Hu3DModelAttrSet(object->model[0], 4, 4);
            Hu3DModelAttrSet(object->model[6], 4, 4);
            data->unk164 = 1.0f;
            Hu3DModelScaleSet(object->model[6], data->unk164, data->unk164, data->unk164);
            break;
        default:
            if (MgFlowStatGet() != MG_STATE_OPENING) {
                switch (object->work[0]) {
                    case 1:
                        if (data->unk15C > 120) {
                            data->unk15C = 0;
                            object->work[0] = 2;
                        } else {
                            if (data->unk15C == 0) {
                                data->unk174 = data->unk170;
                            }
                            m218_KinopioMarkSway(data);
                            data->unk15C++;
                        }
                        break;
                    case 2:
                        if (data->unk15C > 16) {
                            data->unk15C = 0;
                            data->unk164 = 0.5f;
                            espScaleSet(m218_kinopioMarkSprTbl[data->unk160], data->unk164, data->unk164);
                            object->work[0] = 3;
                        } else {
                            data->unk15C++;
                            m218_KinopioMarkPulse(data);
                        }
                        break;
                    case 3:
                        if (data->unk15C == 0) {
                            while (TRUE) {
                                data->unk16C = angles[rand8() >> 5];
                                x = object->trans.x - sindf(data->unk16C) * 100.0f;
                                z = object->trans.z - cosdf(data->unk16C) * 100.0f;
                                if ((z > -300.0f) & (z < 200.0f)) {
                                    if (data->unk160 == 0) {
                                        if ((x < -180.0f) & (x > -350.0f)) {
                                            break;
                                        }
                                    } else {
                                        if ((x > 180.0f) & (x < 350.0f)) {
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        data->unk15C++;
                        if (data->unk16C == data->unk170) {
                            data->unk15C = 0;
                            object->work[0] = 4;
                        } else {
                            m218_KinopioMarkTurn(data);
                        }
                        break;
                    case 4:
                        object->trans.x -= sindf(data->unk170) * 3.0f;
                        object->trans.z -= cosdf(data->unk170) * 3.0f;
                        pos.x = object->trans.x;
                        pos.y = 0.0f;
                        pos.z = object->trans.z;
                        Hu3DCam3Dto2D(0, &pos, &screen);
                        espPosSet(m218_kinopioMarkSprTbl[data->unk160], screen.x, screen.y);
                        m218_kinopioGridPosTbl[data->unk160][0] = screen.x / 2.0f;
                        m218_kinopioGridPosTbl[data->unk160][1] = screen.y / 2.0f;
                        if (data->unk15C % 10 == 0) {
                            sindf(data->unk170);
                            cosdf(data->unk170);
                        }
                        if (object->trans.z < -300.0f || object->trans.z > 200.0f) {
                            data->unk15C = 0;
                            object->work[0] = 1;
                        } else if (data->unk160 == 0) {
                            if (object->trans.x > -180.0f || object->trans.x < -350.0f) {
                                data->unk15C = 0;
                                object->work[0] = 1;
                            }
                        } else {
                            if (object->trans.x < 180.0f || object->trans.x > 350.0f) {
                                data->unk15C = 0;
                                object->work[0] = 1;
                            }
                        }
                        if (data->unk15C > 60) {
                            data->unk15C = 0;
                            object->work[0] = 1;
                        } else {
                            if (data->unk15C == 0) {
                                data->unk174 = data->unk170;
                            }
                            m218_KinopioMarkSway(data);
                            data->unk15C++;
                        }
                        break;
                }
            }
            break;
    }
}

void m218_KinopioCatchEffUpdate(omObjData *object) {
    EtchNCatchKinopioData *data = object->data;
    s32 i;

    data->unk1B4 += 7.0f;
    for (i = 0; i < 5; i++) {
        Hu3DModelPosSet(object->model[i + 1], data->unk178[i].x * data->unk1B4 * 1.5f + object->trans.x,
                        data->unk178[i].y * data->unk1B4 + object->trans.y,
                        data->unk178[i].z * data->unk1B4 * 1.5f + object->trans.z);
        Hu3DModelTPLvlSet(object->model[i + 1], 255.0f - data->unk1B4 * 8.0f);
        Hu3DModelScaleSet(object->model[i + 1], 3.0f, 3.0f, 3.0f);
        Hu3DModelRotSet(object->model[i + 1], 0.0f, 90.0f, 0.0f);
        Hu3DModelAttrSet(object->model[i + 1], 4, 0);
    }
}

void m218_KinopioMarkSway(EtchNCatchKinopioData *data) {
    if (data->unk161 == 0) {
        data->unk170 += 2.0f;
        if (ABS(data->unk170 - data->unk174) >= 30.0f) {
            data->unk161 = 1;
        }
    } else {
        data->unk170 -= 2.0f;
        if (ABS(data->unk170 - data->unk174) >= 30.0f) {
            data->unk161 = 0;
        }
    }
    espZRotSet(m218_kinopioMarkSprTbl[data->unk160], data->unk170);
}

void m218_KinopioMarkPulse(EtchNCatchKinopioData *data) {
    if (data->unk15C < 16) {
        data->unk164 -= 0.01f;
    } else if (data->unk15C < 8) {
        data->unk164 += 0.01f;
    } else if (data->unk15C < 10) {
        data->unk164 -= 0.01;
    } else {
        data->unk164 += 0.01;
    }
    espScaleSet(m218_kinopioMarkSprTbl[data->unk160], data->unk164, data->unk164);
}

void m218_KinopioMarkTurn(EtchNCatchKinopioData *data) {
    f32 diff;

    data->unk170 = m218_AngleWrap(data->unk170);
    diff = data->unk16C - data->unk170;
    if (ABS(diff) > 5.0f) {
        if ((diff > 0.0f && diff < 180.0f) || (diff < -180.0f && diff > -360.0f)) {
            data->unk170 += 5.0f;
        } else {
            data->unk170 -= 5.0f;
        }
    } else {
        data->unk170 += diff;
    }
    data->unk170 = m218_AngleWrap(data->unk170);
    espZRotSet(m218_kinopioMarkSprTbl[data->unk160], data->unk170);
}

s32 m218_GridHitCheck(s16 x, s16 y) {
    s32 count = 0;
    s32 result;

    if (m218_GridValueGet(x, y) != 0) {
        result = TRUE;
    } else {
        count += m218_GridValueGet(x - 1, y) != 0;
        count += m218_GridValueGet(x + 1, y) != 0;
        count += m218_GridValueGet(x, y - 1) != 0;
        count += m218_GridValueGet(x, y + 1) != 0;
        result = count >= 3;
    }
    return result;
}

void m218_CageObjInit(omObjData *object) {
    EtchNCatchCageWork *work;

    object->data = HuMemAllocTag(sizeof(EtchNCatchCageWork), TAG_OVERLAY);
    memset(object->data, 0, sizeof(EtchNCatchCageWork));
    work = object->data;
    work->unk01 = 0;
    work->unk00 = m218_cageNum;
    work->unk04 = 0.0f;
    work->unk08 = 0.0f;
    work->unk02 = 0;
    object->work[0] = 0;
    switch (work->unk00) {
        case 0:
            object->trans.x = m218_kinopioPosTbl[0].x;
            break;
        case 1:
            object->trans.x = -m218_kinopioPosTbl[0].x;
            break;
    }
    object->trans.y = 800.0f;
    object->trans.z = m218_kinopioPosTbl[0].z;
    object->model[0] = Hu3DModelRead(0x330002, 0x8B9);
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    object->model[1] = Hu3DModelRead(0x330008, 0x89D);
    object->model[2] = Hu3DModelRead(9, 0x8B9);
    Hu3DModelPosSet(object->model[2], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[2], 0.0f, 0.0f, 0.0f);
    object->func = m218_CageObjMain;
    m218_cageNum++;
}

void m218_CageObjMain(omObjData *object) {
    omObjData *first = NULL;
    omObjData *second = NULL;
    EtchNCatchCageWork *work = object->data;
    s32 i;
    s16 fx;
    u8 index;

    switch (object->work[0]) {
        case 0:
            if (work->unk01 != 0 && work->unk08 == 0.0f) {
                for (i = 0; i < 4; i++) {
                    if (work->unk00 == 0 && m218_playerWorkTbl[i]->unk_01 == 3) {
                        if (first == NULL) {
                            first = mgPlayerObjTbl[i];
                        } else {
                            second = mgPlayerObjTbl[i];
                        }
                    } else if (work->unk00 == 1 && m218_playerWorkTbl[i]->unk_01 == 12) {
                        if (first == NULL) {
                            first = mgPlayerObjTbl[i];
                        } else {
                            second = mgPlayerObjTbl[i];
                        }
                    }
                }
                index = rand8() * 3 >> 8;
                switch (work->unk00) {
                    case 0:
                        object->trans.x = m218_kinopioPosTbl[index].x;
                        break;
                    case 1:
                        object->trans.x = -m218_kinopioPosTbl[index].x;
                        break;
                }
                object->trans.z = m218_kinopioPosTbl[index].z;
                if (ABS(first->trans.x - object->trans.x) < 75.0f && ABS(first->trans.z - object->trans.z) < 75.0f) {
                    break;
                }
                if (ABS(second->trans.x - object->trans.x) < 75.0f && ABS(second->trans.z - object->trans.z) < 75.0f) {
                    break;
                }
            } else if (work->unk01 == 0) {
                work->unk01 = 1;
            }
            object->trans.y -= work->unk08 + 5.0f;
            if (object->trans.y < 0.0f) {
                object->trans.y = 0.0f;
                work->unk08 = 0.0f;
                object->work[0] = 1;
            } else {
                work->unk08 += 5.0f;
                work->unk04 += 0.1f;
                if (work->unk04 > 1.5f) {
                    work->unk04 = 1.5f;
                }
                if (work->unk08 == 45.0f) {
                    Hu3DModelScaleSet(object->model[1], 3.6f, 3.6f, 3.6f);
                    MgPlayerEffSet(object, 1, object->trans.x, 0.0f, object->trans.z, 0.0f, 0.0f);
                } else if (work->unk08 == 50.0f) {
                    if (work->unk00 == 0) {
                        fx = HuAudFXPlay(0x37B);
                        HuAudFXPanning(fx, 32);
                        if (m218_team0Score == 0) {
                            HuAudFXVolSet(fx, 102);
                        } else {
                            HuAudFXVolSet(fx, 127);
                        }
                    } else {
                        fx = HuAudFXPlay(0x37C);
                        HuAudFXPanning(fx, 95);
                    }
                }
            }
            Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
            Hu3DModelPosSet(object->model[2], object->trans.x, 0.0f, object->trans.z);
            Hu3DModelScaleSet(object->model[2], work->unk04, work->unk04, work->unk04);
            Hu3DModelAttrSet(object->model[2], 4, 0);
            break;
        case 1:
            if (m218_kinopioObjTbl[work->unk00]->work[0] != 10) {
                break;
            }
            if (work->unk02 >= 5) {
                work->unk02 = 0;
                m218_kinopioObjTbl[work->unk00]->work[0] = 0;
                object->work[0] = 2;
                break;
            }
            if (work->unk02 == 0) {
                if (work->unk00 == 0) {
                    for (i = 0; i < 4; i++) {
                        if (m218_playerWorkTbl[i]->unk_01 == 3) {
                            omVibrate(((MgPlayerWork *)mgPlayerObjTbl[i]->data)->unk59, 10, 0, 10);
                        }
                    }
                } else {
                    for (i = 0; i < 4; i++) {
                        if (m218_playerWorkTbl[i]->unk_01 == 12) {
                            omVibrate(((MgPlayerWork *)mgPlayerObjTbl[i]->data)->unk59, 10, 0, 10);
                        }
                    }
                }
            }
            work->unk02++;
            break;
        case 2:
            object->trans.y += work->unk08 + 5.0f;
            if (object->trans.y > 800.0f && work->unk04 == 0.0f) {
                object->trans.y = 800.0f;
                work->unk08 = 0.0f;
                object->work[0] = 3;
            } else {
                work->unk08 += 5.0f;
                work->unk04 -= 0.1f;
                if (work->unk04 < 0.0f) {
                    work->unk04 = 0.0f;
                }
            }
            Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
            Hu3DModelScaleSet(object->model[2], work->unk04, work->unk04, work->unk04);
            break;
        case 3:
            work->unk04 = 1.0f;
            Hu3DModelAttrSet(object->model[2], 4, 4);
            break;
    }
}

void m218_ScoreObjInit(omObjData *object) {
    s16 pos[2][2] = { { 35, 38 }, { 252, 38 } };
    s16 sprite;
    s16 i;

    sprite = HuSprAnimDataRead(0x21002A);
    for (i = 0; i < 2; i++) {
        espPosSet(espEntry(sprite, 0, 1), pos[i][0], pos[i][1]);
    }
    sprite = HuSprAnimDataRead(0x21001B);
    for (i = 0; i < 2; i++) {
        espPosSet(espEntry(sprite, 0, 1), pos[i][0] + 16, pos[i][1]);
    }
    sprite = HuSprAnimDataRead(0x31);
    for (i = 0; i < 2; i++) {
        m218_scoreSprTbl[i] = espEntry(sprite, 0, 1);
        espPosSet(m218_scoreSprTbl[i], m218_scorePosTbl[i][0], m218_scorePosTbl[i][1]);
    }
    object->func = m218_ScoreObjMain;
}

void m218_ScoreObjMain(omObjData *object) {
    espPatNoSet(m218_scoreSprTbl[0], (s8)(m218_team0Score % 10));
    espPosSet(m218_scoreSprTbl[0], m218_scorePosTbl[0][0], m218_scorePosTbl[0][1]);
    espPatNoSet(m218_scoreSprTbl[1], (s8)(m218_team1Score % 10));
    espPosSet(m218_scoreSprTbl[1], m218_scorePosTbl[1][0], m218_scorePosTbl[1][1]);
}

void m218_BoardObjInit(omObjData *object) {
    MgMapWork *work;
    HuSprite *sprite;
    u16 *palette;
    u8 *grid;
    s16 spriteId1;
    s16 spriteId2;
    s32 i;

    spriteId1 = HuSprAnimDataRead(0x330003);
    m218_boardSprGrp = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(m218_boardSprGrp, 0, spriteId1, 0);
    HuSprAttrReset(m218_boardSprGrp, 0, 0xFFFF);
    HuSprAttrSet(m218_boardSprGrp, 0, 0x5000);
    HuSprPosSet(m218_boardSprGrp, 0, 160, 120);
    spriteId2 = HuSprAnimDataRead(0x330004);
    m218_gridSprGrp = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(m218_gridSprGrp, 0, spriteId2, 0);
    HuSprAttrReset(m218_gridSprGrp, 0, 0xFFFF);
    HuSprAttrSet(m218_gridSprGrp, 0, 0x5000);
    HuSprPosSet(m218_gridSprGrp, 0, 160, 120);
    m218_fillCellList = HuMemAlloc(0xE100);
    m218_fillQueueTbl[0] = HuMemAlloc(0xFA0);
    m218_fillQueueTbl[1] = HuMemAlloc(0xFA0);
    sprite = HuSprGet(m218_gridSprGrp, 0);
    m218_gridBuf = grid = sprite->data->pat->data;
    palette = sprite->data->pal;
    m218_gridW = sprite->data->sizeX;
    m218_gridH = sprite->data->sizeY;
    palette[0] = 0;
    palette[1] = 0xF801;
    palette[2] = 0xFC21;
    palette[4] = 0xFE31;
    palette[8] = 0x3F;
    palette[0x10] = 0x843F;
    palette[0x20] = 0xC63F;
    palette[ETCH_N_CATCH_CELL_FILLED] = 0x400;
    palette[ETCH_N_CATCH_CELL_EDGE] = 0xFFFE;
    for (i = 0; i < m218_gridW * m218_gridH; i++) {
        if (i > m218_gridW * 50 && i < m218_gridW * 51) {
            *grid++ = ETCH_N_CATCH_CELL_EDGE;
        } else if (i > m218_gridW * 200 && i < m218_gridW * 201) {
            *grid++ = ETCH_N_CATCH_CELL_EDGE;
        } else {
            *grid++ = 0;
        }
    }
    grid = m218_gridBuf;
    for (i = 30; i < m218_gridW * m218_gridH; i += m218_gridW) {
        grid[i] = ETCH_N_CATCH_CELL_EDGE;
    }
    for (i = 160; i < m218_gridW * m218_gridH; i += m218_gridW) {
        grid[i] = ETCH_N_CATCH_CELL_EDGE;
    }
    for (i = 290; i < m218_gridW * m218_gridH; i += m218_gridW) {
        grid[i] = ETCH_N_CATCH_CELL_EDGE;
    }
    object->func = NULL;
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk08 = 0.5f;
    MgMapAttrSet(object, 2, 0.0f);
}

void m218_WorkFree(void) {
    s32 i;

    HuMemFree(m218_fillCellList);
    HuMemFree(m218_fillQueueTbl[0]);
    HuMemFree(m218_fillQueueTbl[1]);
    for (i = 0; i < 4; i++) {
        EtchNCatchWork *work = m218_playerWorkTbl[i];

        HuMemFree(m218_lineNodeTbl[i]);
        HuMemFree(work);
    }
}

void m218_MapLeftObjInit(omObjData *object) {
    MgMapWork *work;

    object->model[0] = -1;
    object->func = NULL;
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 0;
    work->unk08 = 0.5f;
    MgMapBoxSet(object, 0.0f, -450.0f, -400.0f, -80.0f, 300.0f);
    MgMapNoBumpOn(object);
}

void m218_MapRightObjInit(omObjData *object) {
    MgMapWork *work;

    object->model[0] = -1;
    object->func = NULL;
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 1;
    work->unk08 = 0.5f;
    MgMapBoxSet(object, 0.0f, 80.0f, -400.0f, 450.0f, 300.0f);
    MgMapNoBumpOn(object);
}

f32 m218_AngleWrap(f32 arg0) {
    while (arg0 >= 360.0f) {
        arg0 -= 360.0f;
    }
    while (arg0 < 0.0f) {
        arg0 += 360.0f;
    }
    return arg0;
}

Vec2f m218_DirCalc(s32 x0, s32 y0, s32 x1, s32 y1) {
    Vec2f dir;
    f32 len;

    dir.x = x1 - x0;
    dir.y = y1 - y0;
    len = HuSqrtf(dir.x * dir.x + dir.y * dir.y);
    if (len == 0.0f) {
        dir.y = 0.0f;
        dir.x = 0.0f;
    } else {
        dir.x /= len;
        dir.y /= len;
    }
    return dir;
}

void m218_PlayerScaleSet(omObjData *object, f32 scale) {
    object->scale.z = scale;
    object->scale.y = scale;
    object->scale.x = scale;
    Hu3DModelScaleSet(object->model[0], scale, object->scale.y, object->scale.z);
    Hu3DModelScaleSet(object->model[1], object->scale.x, object->scale.y, object->scale.z);
    Hu3DModelScaleSet(object->model[2], object->scale.x, object->scale.y, object->scale.z);
}
