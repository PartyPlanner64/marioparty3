#include "common.h"
#include "math.h"
#include "game/overlays/minigame.h"
#include "fridged_bridges.h"

// Result of the ice-floor probe performed by m236_FloorCheck.
typedef struct FridgedBridgesProbe {
    /* 0x00 */ f32 height[9];
    /* 0x24 */ u16 bridgeIds[9];
    /* 0x38 */ Vec pos;
} FridgedBridgesProbe; // sizeof 0x44

// Data for the objects created by m236_FoeCreateAll (one per player area).
// It jumps back and forth between the two points of m236_foeJumpPosTbl.
typedef struct FridgedBridgesFoe {
    /* 0x00 */ u16 state; // 0 waiting, 1 jumping, 2 turning around
    /* 0x02 */ u16 index;
    /* 0x04 */ s16 dir;  // index of the point it is heading to
    /* 0x06 */ u16 wait; // frames left before the next jump
    /* 0x08 */ f32 jumpDist;
    /* 0x0C */ f32 arcScale;
    /* 0x10 */ f32 jumpPos;
    /* 0x14 */ f32 speed;
    /* 0x18 */ f32 unk_18;
} FridgedBridgesFoe; // sizeof 0x1C

// Work area of the dropped-item objects created by m236_PieceDrop.
typedef struct FridgedBridgesPieceWork {
    /* 0x00 */ omObjData *playerObj;
    /* 0x04 */ u32 phase;
    /* 0x08 */ f32 fallSpeed;
} FridgedBridgesPieceWork;

// Data for the rescue objects created by m236_RescueCreate, which fly in to pick up
// a player that fell off the bridges.
typedef struct FridgedBridgesRescue {
    /* 0x00 */ u16 state;
    /* 0x02 */ u16 timer;
    /* 0x04 */ omObjData *playerObj;
    /* 0x08 */ u16 released;
    /* 0x0A */ s16 sfxId;
} FridgedBridgesRescue; // sizeof 0xC

extern omObjData *m236_introObj;
extern omObjData *m236_winObj;
extern s16 m236_winner;
extern s16 m236_goalF;
extern omObjData **m236_playerObjTbl;
extern omObjData *m236_pieceObj;
extern omObjData *m236_stageObj;
extern FridgedBridgesCamCollWork m236_camCollWorkTbl[4];
extern u16 m236_introPhase;
extern u16 m236_winPhase;
extern u16 m236_seaTexSizeTbl[4][2];
extern Vec2f m236_seaScrollTbl[4];
extern u8 omAllPauseF;
extern s32 omCharModelNoTbl[][6];
extern Vec2f m236_comPathPosTbl[4][3][12];
extern Vec2f m236_cameraPathPosTbl[4][12];
extern f32 CFanLenM[];
extern f32 CFanOfsM[];
extern omObjData *m236_foeObjTbl[4];
extern f32 m236_winZoomStep;
extern Vec m236_winRotStep;
extern u16 m236_winCameraTimer;
extern Vec2f m236_bridgeSlotPosTbl[4][3];
extern Vec2f m236_pieceStockPosTbl[4];
extern u16 m236_cameraPathNo;

MinigameFlow m236_mgFlow = {
    MG_STATE_OPENING, MINIGAME_4P, MG_TIMER_COUNT_DOWN, MG_TIME_DISP_NONE, FALSE, MG_GAUGE_NONE, MG_RESULT_WIN_1, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    -1, -1, 5400, 75, 135
};
s16 m236_cameraBitTbl[4] = { 1, 2, 4, 8 };
u16 m236_exitF = 0;
s32 m236_stageMdlFileTbl[4] = { 0x00450004, 0x00450005, 0x00450006, 0x00450007 };
s32 m236_seaMdlFileTbl[4] = { 0x00450008, 0x00450009, 0x0045000A, 0x0045000B };
/* Unreferenced. */
Vec2f m236_areaCenterTbl[4] = {
    { -550.0f, -200.0f },
    { 550.0f, -200.0f },
    { -550.0f, 200.0f },
    { 550.0f, 200.0f },
};

void m236_MainObjMain(omObjData *arg0);
void m236_PieceStockObjMain(omObjData *arg0);
void m236_MainObjInit(omObjData *arg0);
void m236_StageObjInit(omObjData *arg0);
void m236_Player0ObjInit(omObjData *arg0);
void m236_Player1ObjInit(omObjData *arg0);
void m236_Player2ObjInit(omObjData *arg0);
void m236_Player3ObjInit(omObjData *arg0);
void m236_PieceObjInit(omObjData *arg0);
void m236_PieceDropObjMain(omObjData *arg0);
s32 m236_FaceInsideHook(s32 count, s16 *vtx, Hu3DPoint *points, Vec *pos);
s32 m236_FaceInsideXZCheck(Vec *pos, s16 *face, Hu3DPoint *points);
void m236_PlayerHoldObjMain(omObjData *arg0);
void m236_PlayerFrontTurnObjMain(omObjData *arg0);
void m236_PlayerEndObjMain(omObjData *arg0);
void m236_CameraPathInit(void);
u16 m236_CameraPathPan(f32 arg0);
void m236_PieceGrowObjMain(omObjData *arg0);
void m236_BridgeSinkObjMain(omObjData *arg0);
void m236_PieceSinkWaitObjMain(omObjData *arg0);
void m236_PathInit(void);
void m236_EffInit(void);
void m236_CameraOutView(omObjData *arg0);
void m236_IntroObjMain(omObjData *arg0);
void m236_WinObjMain(omObjData *arg0);
void m236_OvlReturn(void);
u16 m236_FallDoneCheck(void);
void m236_StageObjMain(omObjData *arg0);
void m236_FoeCreateAll(void);
void m236_FoeObjMain(omObjData *arg0);
void m236_PlayerInit(omObjData *arg0, s16 playerIndex);
void m236_PlayerObjMain(omObjData *arg0);
s16 m236_ComLaneGet(omObjData *arg0);
void m236_CameraTargetCreate(omObjData *arg0);
void m236_PlayerFallObjMain(omObjData *arg0);
void m236_PlayerComInputGet(omObjData *arg0, s8 *stickX, s8 *stickY);
void m236_PieceGrab(omObjData *arg0);
void m236_PieceDrop(omObjData *arg0);
s32 m236_FloorCheck(omObjData *arg0, FridgedBridgesProbe *probe);
u16 m236_PieceStockCheck(omObjData *arg0, f32 x, f32 y, f32 z);
void m236_FoeHitPush(omObjData *arg0);
void m236_PlayerFreezeObjMain(omObjData *arg0);
void m236_PlayerFloatObjMain(omObjData *arg0);
void m236_PlayerEdgePush(omObjData *arg0);
void m236_RescueCreate(omObjData *arg0);
void m236_RescueObjMain(omObjData *arg0);
void m236_ReturnPosCalc(omObjData *arg0);
void m236_PathNearGet(FridgedBridgesPlayer *player, Vec2f *a, Vec2f *b);
omObjData *m236_EffCreate(u16 type, u16 playerId, f32 x, f32 y, f32 z);
void m236_PlayerMotRestore(omObjData *arg0);

void m236_ObjectSetup(void) {
    omObjData *obj;
    s32 i;

    omInitObjMan(60, 0);
    omGameSysInit();
    MapCollInit(16);
    Hu3DQuadPoolInit(&mgQuadPool, 64);
    HuAudCharVoiceInit();
    CamSetupInitMulti(4);
    CamSetupMapCullAddMulti(4);
    for (i = 0; i < 4; i++) {
        CZoomM[i] = 1340.0f;
        CRotM[i].x = -60.0f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = -320.0f;
        CenterM[i].y = 100.0f;
        CenterM[i].z = -420.0f;
        CFanLenM[i] = 5000.0f;
        CFanOfsM[i] = 1000.0f;
        Hu3DCameraModelHookSet(i, (void (*)(void *, struct HmfModel *))MapCullFan, &m236_camCollWorkTbl[i]);
    }
    obj = omAddObj(0x7FDA, 0, 0, -1, m236_CameraOutView);
    obj->work[0] = 4;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    ScissorSet(0, 1.0f, 1.0f, 159.0f, 119.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 240.0f, 511.0f);
    ScissorSet(1, 161.0f, 1.0f, 319.0f, 119.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 240.0f, 511.0f);
    ScissorSet(2, 1.0f, 121.0f, 159.0f, 239.0f);
    ViewportSet(2, 640.0f, 480.0f, 511.0f, 320.0f, 720.0f, 511.0f);
    ScissorSet(3, 161.0f, 121.0f, 319.0f, 239.0f);
    ViewportSet(3, 640.0f, 480.0f, 511.0f, 960.0f, 720.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 45.0f, 80.0f, 3000.0f);
    Hu3DCameraPerspectiveSet(1, 45.0f, 80.0f, 3000.0f);
    Hu3DCameraPerspectiveSet(2, 45.0f, 80.0f, 3000.0f);
    Hu3DCameraPerspectiveSet(3, 45.0f, 80.0f, 3000.0f);
    Hu3DBGColorSet(0, 0, 0);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(1, 0x40, 0x40, 0x60);
    Hu3DGLightDirSet(1, 3.0f, 89.0f, 80.0f);
    Hu3DGLightStatSet(1, 1, 1);
    Hu3DGLightColorSet(3, 0, 0, 0);
    Hu3DGLightDirSet(3, -115.0f, 6.0f, -33.0f);
    Hu3DGLightStatSet(2, 1, 1);
    omAddObj(0, 0, 0, -1, m236_MainObjInit);
    m236_stageObj = omAddObj(10, 8, 0, -1, m236_StageObjInit);
    omSetStatBit(m236_stageObj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    MgFlowInit(&m236_mgFlow);
    mgFlowSeqNo = 46;
    mgFlowSeqTime = 30;
    omMakeGroup(0, 4);
    m236_playerObjTbl = omGetGroupMemberList(0);
    omAddObj(20, 6, 9, 0, m236_Player0ObjInit);
    omAddObj(20, 6, 9, 0, m236_Player1ObjInit);
    omAddObj(20, 6, 9, 0, m236_Player2ObjInit);
    omAddObj(20, 6, 9, 0, m236_Player3ObjInit);
    m236_pieceObj = omAddObj(30, 20, 0, -1, m236_PieceObjInit);
    omSetStat(m236_pieceObj, 0x100);
    m236_PathInit();
    m236_EffInit();
}

void m236_MainObjInit(omObjData *arg0) {
    m236_winObj = NULL;
    m236_introObj = NULL;
    m236_goalF = 0;
    m236_winner = -1;
    arg0->func = m236_MainObjMain;
}

void m236_MainObjMain(omObjData *arg0) {
    u16 candidates[4];
    u16 count;
    s32 i;

    if (m236_exitF == 0) {
        switch (MgFlowMain()) {
            case 0:
                if (m236_introObj == NULL) {
                    m236_introPhase = 0;
                    m236_introObj = omAddObj(4, 0, 0, -1, m236_IntroObjMain);
                }
                break;
            case 1:
                break;
            case 2:
                if (m236_goalF == 1) {
                    if (m236_winner == -1) {
                        count = 0;
                        for (i = 0; i < 4; i++) {
                            if (OM_GET_DATA_PTR(m236_playerObjTbl[i], FridgedBridgesPlayer)->unk_06 == 1) {
                                candidates[count++] = i;
                            }
                        }
                        if (count == 1) {
                            m236_winner = candidates[0];
                        } else {
                            m236_winner = candidates[rand8() % count];
                        }
                        m236_mgFlow.winners[0] = m236_winner;
                    } else if (m236_FallDoneCheck() == 1) {
                        MgFlowStatSet(MG_STATE_FINISH);
                    }
                } else if (MgFlowStatTimeGet() == 5400) {
                    m236_goalF = 1;
                    m236_mgFlow.resultType = MG_RESULT_DRAW;
                    MgFlowStatSet(MG_STATE_FINISH);
                }
                break;
            case 3:
                if (m236_winObj == NULL) {
                    m236_winObj = omAddObj(4, 0, 0, -1, m236_WinObjMain);
                    if (m236_winner != -1) {
                        m236_winPhase = 0;
                    } else {
                        m236_winPhase = 6;
                    }
                }
                break;
            case 4:
                break;
            case 5:
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                HuAudSeqFadeOut(30);
                HuAudFXAllFadeOut(30);
                m236_exitF = 1;
                break;
        }
    } else if (WipeStatGet() == 0) {
        m236_OvlReturn();
    }
}

char *m236_seaObjNameTbl[4] = { "m236_004b-cube50", "m236_004b-cube52", "m236_004b-cube42", "m236_004b-cube51" };
Vec m236_startPosTbl[4] = {
    { -1300.0f, 0.0f, -780.0f },
    { 1300.0f, 0.0f, -780.0f },
    { -1300.0f, 0.0f, 780.0f },
    { 1300.0f, 0.0f, 780.0f },
};
f32 m236_chrScaleTbl[8] = { 1.1f, 1.1f, 1.1f, 1.1f, 1.1f, 1.0f, 1.1f, 1.1f };
u16 m236_bridgeAttrTbl[4] = { 0x200, 0x300, 0x400, 0 };
Vec2f m236_comPathTbl[3][12] = {
    {
        { -1300.0f, -900.0f },
        { -1250.0f, -565.0f },
        { -1200.9f, -326.8f },
        { -1080.0f, -302.5f },
        { -981.5f, -389.5f },
        { -875.8f, -591.5f },
        { -791.0f, -798.3f },
        { -636.5f, -860.4f },
        { -464.6f, -839.5f },
        { -345.8f, -799.0f },
        { -298.7f, -600.0f },
        { -267.7f, -220.0f },
    },
    {
        { -1300.0f, -900.0f },
        { -1305.0f, -565.0f },
        { -1240.9f, -351.8f },
        { -1135.0f, -244.5f },
        { -960.5f, -325.5f },
        { -836.8f, -594.5f },
        { -757.0f, -782.3f },
        { -636.5f, -831.4f },
        { -464.6f, -832.5f },
        { -357.8f, -734.0f },
        { -267.7f, -600.0f },
        { -267.7f, -220.0f },
    },
    {
        { -1300.0f, -900.0f },
        { -1250.0f, -565.0f },
        { -1170.9f, -338.0f },
        { -1090.0f, -309.0f },
        { -1005.0f, -379.0f },
        { -910.8f, -593.0f },
        { -830.0f, -816.3f },
        { -636.5f, -910.4f },
        { -410.6f, -890.5f },
        { -300.0f, -786.8f },
        { -267.7f, -600.0f },
        { -267.7f, -220.0f },
    },
};
Vec2f m236_cameraPathTbl[12] = {
    { -1300.0f, -780.0f },
    { -1250.0f, -565.0f },
    { -1156.9f, -331.8f },
    { -1080.0f, -302.5f },
    { -981.5f, -389.5f },
    { -875.8f, -591.5f },
    { -791.0f, -798.3f },
    { -636.5f, -860.4f },
    { -464.6f, -839.5f },
    { -345.8f, -799.0f },
    { -320.0f, -420.0f },
    { -267.7f, -220.0f },
};
Vec2f m236_bridgePosTbl[3] = { { -272.0f, -498.0f }, { -272.0f, -431.0f }, { -272.0f, -364.0f } };
Vec2f m236_pieceStockPos = { -1300.0f, -900.0f };
s16 m236_sinkSeF = 0;
s32 m236_introInitF = 0;
Vec m236_winPosTbl[4] = {
    { -150.0f, 0.0f, 100.0f },
    { 150.0f, 0.0f, 100.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
};
Vec2f m236_viewOfsTbl[4] = {
    { 0.0f, 0.0f },
    { 160.0f, 0.0f },
    { 0.0f, 120.0f },
    { 160.0f, 120.0f },
};
u16 m236_cameraPanDoneTbl[4] = { 0, 0, 0, 0 };
Vec2f m236_foeJumpPosTbl[4][2] = {
    { { -593.0f, -1088.0f }, { -588.0f, -708.0f } },
    { { 593.0f, -1088.0f }, { 588.0f, -708.0f } },
    { { -593.0f, 1088.0f }, { -588.0f, 708.0f } },
    { { 593.0f, 1088.0f }, { 588.0f, 708.0f } },
};

void m236_StageObjInit(omObjData *arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        arg0->model[i] = Hu3DModelRead(m236_stageMdlFileTbl[i], 0x699);
        arg0->model[i + 4] = Hu3DModelRead(m236_seaMdlFileTbl[i], 0x689);
        Hu3DModelCameraSet(arg0->model[i], m236_cameraBitTbl[i]);
        Hu3DModelCameraSet(arg0->model[i + 4], m236_cameraBitTbl[i]);
        m236_seaScrollTbl[i].x = 0.0f;
        m236_seaScrollTbl[i].y = 0.0f;
        Hu3DTexSizeGet("sea_01_DEF", m236_seaTexSizeTbl[i]);
        Hu3DModelVtxBufMake(arg0->model[i + 4]);
    }
    m236_FoeCreateAll();
    arg0->func = m236_StageObjMain;
}

void m236_StageObjMain(omObjData *arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (omPauseChk() + omAllPauseF == 0) {
            m236_seaScrollTbl[i].x += 0.1f;
            m236_seaScrollTbl[i].y += 0.1f;
        }
        Hu3DModelObjTexScroll(arg0->model[i + 4], m236_seaScrollTbl[i].x, m236_seaScrollTbl[i].y,
                           m236_seaTexSizeTbl[i][0], m236_seaTexSizeTbl[i][1],
                           m236_seaObjNameTbl[i], 0);
    }
}

void m236_Player0ObjInit(omObjData *arg0) {
    m236_PlayerInit(arg0, 0);
}

void m236_Player1ObjInit(omObjData *arg0) {
    m236_PlayerInit(arg0, 1);
}

void m236_Player2ObjInit(omObjData *arg0) {
    m236_PlayerInit(arg0, 2);
}

void m236_Player3ObjInit(omObjData *arg0) {
    m236_PlayerInit(arg0, 3);
}

void m236_PlayerInit(omObjData *arg0, s16 playerIndex) {
    FridgedBridgesPlayer *player;
    s8 chr;
    s32 modelFile;

    player = arg0->data = HuMemAllocTag(sizeof(FridgedBridgesPlayer), TAG_OVERLAY);
    player->playerId = playerIndex;
    player->motionState = 0;
    player->unk_08 = player->unk_0C = 0.0f;
    player->slideDist = player->slideDistTarget = 0.0f;
    player->unk_1E = m236_ComLaneGet(arg0);
    player->unk_20 = 1;
    player->unk_22 = 1;
    player->unk_24 = 0;
    player->unk_26 = 0;
    player->state = 1;
    player->unk_28 = 0;
    player->bridgeObj = NULL;
    player->unk_06 = 0;
    player->unk_48 = 0;
    player->unk_4A = 0;
    player->unk_56 = 0;
    player->unk_58 = 0;
    player->unk_6A = 0;
    chr = GwPlayer[playerIndex].chr;
    modelFile = omCharModelNoTbl[chr][0];
    arg0->model[0] = Hu3DModelRead(modelFile | omCharModelNoTbl[chr][1], 0x20699);
    omSetTra(arg0, m236_startPosTbl[playerIndex].x, m236_startPosTbl[playerIndex].y,
             m236_startPosTbl[playerIndex].z);
    arg0->model[1] = Hu3DModelRead3(9, 0xA89);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, 0.0f, arg0->trans.z);
    arg0->model[2] = Hu3DModelRead(0x450011, 0xA9D);
    arg0->model[3] = Hu3DModelRead(0x450012, 0x69D);
    arg0->model[4] = Hu3DModelRead(modelFile | omCharModelNoTbl[chr][2], 0x2068D);
    CharAnimCreate(arg0->model[4], 2, chr, CharMotionDataNumGetTbl(chr, 2, 0));
    Hu3DModelDynamicFree(arg0->model[4]);
    arg0->model[5] = Hu3DAnimDataRead(CharMotionDataNumGetTbl(chr, 2, 1));
    Hu3DModelCameraSet(arg0->model[0], m236_cameraBitTbl[playerIndex]);
    Hu3DModelCameraSet(arg0->model[1], m236_cameraBitTbl[playerIndex]);
    Hu3DModelCameraSet(arg0->model[2], m236_cameraBitTbl[playerIndex]);
    Hu3DModelCameraSet(arg0->model[3], m236_cameraBitTbl[playerIndex]);
    Hu3DModelCameraSet(arg0->model[4], m236_cameraBitTbl[playerIndex]);
    if (playerIndex < 2) {
        omSetRot(arg0, 0.0f, 0.0f, 0.0f);
    } else {
        omSetRot(arg0, 0.0f, 180.0f, 0.0f);
    }
    omObjMotionRead(arg0, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(arg0, 1, CharMotionDataNumGet(chr, 1));
    omObjMotionRead(arg0, 2, CharMotionDataNumGet(chr, 2));
    if (chr == 5) {
        omObjMotionRead(arg0, 3, 0x45000D);
        omObjMotionRead(arg0, 7, 0x45000E);
        omObjMotionRead(arg0, 8, 0x45000F);
    } else {
        omObjMotionRead(arg0, 3, CharMotionDataNumGet(chr, 0x12));
    }
    omObjMotionRead(arg0, 4, CharMotionDataNumGet(chr, 0xD));
    omObjMotionRead(arg0, 5, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(arg0, 6, CharMotionDataNumGet(chr, 0x36));
    Hu3DMotionModelSet(arg0->model[0], arg0->motion[0]);
    Hu3DMotionAttrSet(arg0->model[0], 3, 2);
    omSetSca(arg0, m236_chrScaleTbl[chr], m236_chrScaleTbl[chr], m236_chrScaleTbl[chr]);
    m236_CameraTargetCreate(arg0);
    player->pos.x = arg0->trans.x;
    player->pos.y = arg0->trans.y;
    player->pos.z = arg0->trans.z;
    player->unk_68 = 0x100;
    arg0->func = m236_PlayerObjMain;
}

void m236_PlayerObjMain(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;
    u16 port = GwPlayer[player->playerId].pad;
    FridgedBridgesProbe probe;
    s8 stickX;
    s8 stickY;
    f32 speed;
    f32 angle;
    u16 count;

    if (MgFlowStatGet() == MG_STATE_PLAY) {
        if (!(GwPlayer[player->playerId].stat & 1)) {
            stickX = HuPadStkX[port];
            stickY = HuPadStkY[port];
        } else {
            m236_PlayerComInputGet(arg0, &stickX, &stickY);
        }
    } else {
        stickX = stickY = 0;
    }
    if (player->unk_58 != 0) {
        if (--player->unk_58 == 0) {
            player->unk_56 = 0;
        }
    }
    if (player->state == 0) {
        stickX = stickY = 0;
    }
    speed = HuSqrtf(stickX * stickX + stickY * stickY) * 0.08f;
    angle = atan2df(stickX, -stickY);
    if (stickX != 0 || stickY != 0) {
        player->slideDist = sindf(angle) * speed;
        player->slideDistTarget = cosdf(angle) * speed;
        omSetRot(arg0, 0.0f, angle, 0.0f);
        if (speed > 2.5f) {
            if (player->motionState != 2) {
                if (GwPlayer[player->playerId].chr == CHAR_DK && player->unk_28 == 1) {
                    Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[8]].motId, 0, 6, 2);
                } else {
                    Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[2]].motId, 0, 6, 2);
                }
                player->motionState = 2;
                player->unk_48 = 0;
            }
            if (player->unk_48 == 0) {
                PlayerFXPlay(0x28, player->playerId);
                player->unk_48 = 12;
            } else {
                player->unk_48--;
            }
        } else {
            if (player->motionState != 1) {
                if (GwPlayer[player->playerId].chr == CHAR_DK && player->unk_28 == 1) {
                    Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[3]].motId, 0, 6, 2);
                } else {
                    Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[1]].motId, 0, 6, 2);
                }
                player->motionState = 1;
                player->unk_48 = 0;
            }
            if (player->unk_48 == 0) {
                PlayerFXPlay(0x1F, player->playerId);
                player->unk_48 = 22;
            } else {
                player->unk_48--;
            }
        }
        player->unk_4A = 0;
    } else {
        player->slideDist = player->slideDistTarget = 0.0f;
        if (player->motionState != 0) {
            if (GwPlayer[player->playerId].chr == CHAR_DK && player->unk_28 == 1) {
                Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[7]].motId, 0, 6, 2);
            } else {
                Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[0]].motId, 0, 6, 2);
            }
            player->motionState = 0;
        }
        if (player->unk_08 != 0.0f || player->unk_0C != 0.0f) {
            if (player->unk_4A == 0) {
                PlayerFXPlay(0xD3, player->playerId);
                player->unk_4A = 11;
            } else {
                player->unk_4A--;
            }
        }
    }
    if (fabs(player->unk_08) < 0.1f) {
        player->unk_08 = 0.0f;
    }
    if (fabs(player->unk_0C) < 0.1f) {
        player->unk_0C = 0.0f;
    }
    if (player->unk_28 != 0) {
        player->slideDist *= 0.85f;
        player->slideDistTarget *= 0.85f;
    }
    player->unk_08 += player->slideDist;
    player->unk_0C += player->slideDistTarget;
    speed = HuSqrtf(player->unk_08 * player->unk_08 + player->unk_0C * player->unk_0C);
    if (speed != 0.0f) {
        player->unk_08 /= speed;
        player->unk_0C /= speed;
        if (speed > 16.0f) {
            speed = 16.0f;
        }
    }
    player->unk_08 = speed * player->unk_08;
    player->unk_0C = speed * player->unk_0C;
    if (player->state == 0 || m236_winner != -1) {
        player->unk_08 = player->unk_0C = 0.0f;
    }
    if (m236_PieceStockCheck(arg0, arg0->trans.x + player->unk_08, arg0->trans.y,
                                      arg0->trans.z + player->unk_0C) == 1) {
        if (player->unk_28 == 0) {
            m236_PieceGrab(arg0);
            HuAudPlayerFXPlay(0x42D, player->playerId);
            player->unk_1E = m236_ComLaneGet(arg0);
            player->unk_20 = 1;
            player->unk_22 = 1;
        }
        player->unk_08 = player->unk_0C = 0.0f;
    }
    m236_FoeHitPush(arg0);
    omSetTra(arg0, arg0->trans.x + player->unk_08, arg0->trans.y, arg0->trans.z + player->unk_0C);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, 0.0f, arg0->trans.z);
    player->unk_08 *= 0.8f;
    player->unk_0C *= 0.8f;
    probe.pos.x = arg0->trans.x;
    probe.pos.y = arg0->trans.y;
    probe.pos.z = arg0->trans.z;
    count = m236_FloorCheck(arg0, &probe);
    if (probe.height[8] != -10000.0f) {
        count = 0;
    }
    if (count >= 6) {
        player->state = 2;
        player->unk_34.x = sindf(angle) * 10.0f;
        player->unk_34.z = cosdf(angle) * 10.0f;
        player->unk_34.y = -1.2f;
        player->motionState = 0;
        player->unk_48 = 0;
        arg0->func = m236_PlayerFallObjMain;
        player->unk_2C->work[0] = 0;
        Hu3DMotionAttrSet(arg0->model[0], 1, 1);
    }
    if (player->unk_1C == m236_bridgeAttrTbl[player->unk_24] && player->unk_28 == 1) {
        m236_PieceDrop(arg0);
        if (player->unk_24 != 2) {
            player->unk_22 = -1;
            player->unk_20--;
        }
    } else if (player->unk_1C == 0x600) {
        m236_goalF = 1;
        player->unk_06 = 1;
    }
    if (player->state != 2) {
        player->unk_68 = player->unk_1C;
        player->pos.x = arg0->trans.x;
        player->pos.y = arg0->trans.y;
        player->pos.z = arg0->trans.z;
    }
}

void m236_PlayerFallObjMain(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;

    arg0->trans.x += player->unk_08;
    arg0->trans.y += player->unk_34.y;
    arg0->trans.z += player->unk_0C;
    m236_FoeHitPush(arg0);
    m236_PlayerEdgePush(arg0);
    player->unk_08 *= 0.91f;
    player->unk_0C *= 0.91f;
    player->unk_34.y *= 1.3f;
    if (arg0->trans.y <= -150.0f) {
        arg0->trans.y = -150.0f;
        omVibrate(player->playerId, 2, 2, 20);
        PlayerFXPlay(0x70, player->playerId);
        m236_EffCreate(0, player->playerId, arg0->trans.x, -150.0f, arg0->trans.z);
        Hu3DModelAttrSet(arg0->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        player->unk_54 = 29;
        player->scale = 0.1f;
        player->state = 3;
        Hu3DModelPosSet(arg0->model[3], arg0->trans.x, arg0->trans.y, arg0->trans.z);
        Hu3DModelScaleSet(arg0->model[3], player->scale, player->scale, player->scale);
        HuAudPlayerFXPlay(0x42F, player->playerId);
        arg0->func = m236_PlayerFreezeObjMain;
        player->unk_56 = 0;
        player->unk_58 = 0;
        if (m236_goalF == 0) {
            m236_RescueCreate(arg0);
            m236_ReturnPosCalc(arg0);
        }
    }
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, -100.0f, arg0->trans.z);
}

void m236_PlayerFreezeObjMain(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;

    if (--player->unk_54 != 0) {
        if (player->unk_54 & 1) {
            Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg0->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            if (player->unk_28 == 1) {
                Hu3DModelAttrSet(m236_pieceObj->model[player->playerId * 5], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
        } else {
            Hu3DModelAttrSet(arg0->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            if (player->unk_28 == 1) {
                Hu3DModelAttrSet(m236_pieceObj->model[player->playerId * 5], HU3D_ATTR_DISPOFF,
                                   HU3D_ATTR_DISPOFF);
            }
        }
        player->scale += 0.03f;
        Hu3DModelScaleSet(arg0->model[3], player->scale, player->scale, player->scale);
    } else {
        Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(m236_pieceObj->model[player->playerId * 5], HU3D_ATTR_DISPOFF,
                           HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(arg0->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        player->unk_40 = 0.0f;
        Hu3DModelScaleSet(arg0->model[3], 1.0f, 1.0f, 1.0f);
        arg0->func = m236_PlayerFloatObjMain;
    }
}

void m236_PlayerFloatObjMain(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;

    arg0->trans.y += sindf(player->unk_40);
    Hu3DModelPosSet(arg0->model[3], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    player->unk_40 += 5.0f;
    if (player->unk_40 >= 360.0f) {
        player->unk_40 -= 360.0f;
    }
}

void m236_PlayerHoldObjMain(omObjData *arg0) {
}

void m236_PlayerFrontTurnObjMain(omObjData *arg0) {
    f32 diff = -arg0->rot.y;

    if (diff < 0.0f) {
        diff += 360.0f;
    }
    if (diff < 180.0f) {
        if (diff > 5.0f) {
            arg0->rot.y += 5.0f;
        } else {
            arg0->rot.y += diff;
        }
    } else {
        if (360.0f - diff > 5.0f) {
            arg0->rot.y -= 5.0f;
        } else {
            arg0->rot.y -= 360.0f - diff;
        }
    }
    if (arg0->rot.y >= 360.0f) {
        arg0->rot.y -= 360.0f;
    }
    if (arg0->rot.y < 0.0f) {
        arg0->rot.y += 360.0f;
    }
    if (arg0->rot.y < 0.0001f) {
        arg0->work[0] = 1;
        Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[0]].motId, 0, 6, 2);
        arg0->func = NULL;
    }
}

void m236_PlayerEndObjMain(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;
    HmfMotionNode *hook;

    if (player->unk_28 == 1) {
        hook = Hu3DModelObjPtrGet(arg0->model[0], "item_hook");
        player->unk_44 -= 0.1f;
        hook->scale.x = player->unk_44;
        hook->scale.y = player->unk_44;
        hook->scale.z = player->unk_44;
        if (!(player->unk_44 <= 0.0f)) {
            return;
        }
        Hu3DModelAttrSet(m236_pieceObj->model[player->playerId * 5], HU3D_ATTR_HOOK | HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        m236_PlayerMotRestore(arg0);
    }
    Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[6]].motId, 0, 6, 0);
    arg0->func = NULL;
}

void m236_PathInit(void) {
    f32 sign[2][4];
    s32 i;
    s32 j;
    s32 k;

    sign[0][0] = 1.0f;
    sign[0][1] = -1.0f;
    sign[0][2] = 1.0f;
    sign[0][3] = -1.0f;
    sign[1][0] = 1.0f;
    sign[1][1] = 1.0f;
    sign[1][2] = -1.0f;
    sign[1][3] = -1.0f;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 12; k++) {
                m236_comPathPosTbl[i][j][k].x = m236_comPathTbl[j][k].x * sign[0][i];
                m236_comPathPosTbl[i][j][k].y = m236_comPathTbl[j][k].y * sign[1][i];
            }
        }
        for (k = 0; k < 12; k++) {
            m236_cameraPathPosTbl[i][k].x = m236_cameraPathTbl[k].x * sign[0][i];
            m236_cameraPathPosTbl[i][k].y = m236_cameraPathTbl[k].y * sign[1][i];
        }
    }
}

// CPU input: walks the player along its path points, adjusting speed to avoid the foe.
void m236_PlayerComInputGet(omObjData *arg0, s8 *stickX, s8 *stickY) {
    FridgedBridgesPlayer *player;
    FridgedBridgesFoe *foe;
    u16 playerId;
    u16 lane;
    u16 point;
    f32 speed;
    f32 angle;
    f32 foeAngle;
    f32 dist;

    *stickY = 0;
    *stickX = 0;
    player = arg0->data;
    playerId = player->playerId;
    lane = player->unk_1E;
    point = player->unk_20;
    if (player->unk_6A != 0) {
        if (--player->unk_6A == 0) {
            player->unk_22 = -player->unk_22;
            player->unk_20 += player->unk_22;
        }
    }
    if (HuSqrtf((arg0->trans.x - m236_comPathPosTbl[playerId][lane][point].x) *
                    (arg0->trans.x - m236_comPathPosTbl[playerId][lane][point].x) +
                (arg0->trans.z - m236_comPathPosTbl[playerId][lane][point].y) *
                    (arg0->trans.z - m236_comPathPosTbl[playerId][lane][point].y)) < 80.0f) {
        player->unk_1E = m236_ComLaneGet(arg0);
        player->unk_20 += player->unk_22;
        if (player->unk_20 == 11 && player->unk_22 == 1) {
            player->unk_22 = -1;
        }
        if (player->unk_20 == 0 && player->unk_22 == -1) {
            player->unk_22 = 1;
        }
        point = player->unk_20;
    }
    switch (GwPlayer[player->playerId].cpu_difficulty) {
        case 0:
            speed = 35.0f;
            break;
        case 1:
            speed = 42.0f;
            break;
        case 2:
            speed = 55.0f;
            break;
        case 3:
            speed = 65.0f;
            break;
    }
    speed *= player->unk_4C;
    if (player->unk_1E != 0) {
        speed *= 0.5f;
    }
    angle = atan2df(-(arg0->trans.x - m236_comPathPosTbl[playerId][lane][point].x),
                    arg0->trans.z - m236_comPathPosTbl[playerId][lane][point].y);
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    foeAngle = atan2df(-(arg0->trans.x - m236_foeObjTbl[player->playerId]->trans.x),
                       arg0->trans.z - m236_foeObjTbl[player->playerId]->trans.z) -
               360.0f - angle;
    if (foeAngle < 0.0f) {
        foeAngle += 360.0f;
    }
    if (foeAngle > 180.0f) {
        foeAngle -= 360.0f;
    }
    dist = HuSqrtf((arg0->trans.x - m236_foeObjTbl[player->playerId]->trans.x) *
                       (arg0->trans.x - m236_foeObjTbl[player->playerId]->trans.x) +
                   (arg0->trans.z - m236_foeObjTbl[player->playerId]->trans.z) *
                       (arg0->trans.z - m236_foeObjTbl[player->playerId]->trans.z));
    foe = m236_foeObjTbl[player->playerId]->data;
    if (foe->state == 1) {
        if (dist < 170.0f) {
            if (fabs(foeAngle) > 80.0) {
                speed = 65.0f;
            } else {
                if (player->unk_22 == 1 && player->unk_20 >= 7 && player->unk_20 <= 8) {
                    speed = 65.0f;
                    angle = atan2df(-(arg0->trans.x - m236_comPathPosTbl[playerId][lane][point - 1].x),
                                    arg0->trans.z - m236_comPathPosTbl[playerId][lane][point - 1].y);
                }
                if (player->unk_22 == -1 && player->unk_20 >= 6 && player->unk_20 <= 8) {
                    speed = 65.0f;
                    angle = atan2df(-(arg0->trans.x - m236_comPathPosTbl[playerId][lane][point + 1].x),
                                    arg0->trans.z - m236_comPathPosTbl[playerId][lane][point + 1].y);
                }
            }
        } else if (dist < 300.0f) {
            if (player->unk_22 == 1 && player->unk_20 >= 7 && player->unk_20 <= 8) {
                speed = 15.0f;
            }
            if (player->unk_22 == -1 && player->unk_20 >= 6 && player->unk_20 <= 8) {
                speed = 15.0f;
            }
        }
    } else if (foe->state == 0) {
        if (dist < 150.0f && foe->wait < 5) {
            if (player->unk_22 == 1 && player->unk_20 >= 7 && player->unk_20 <= 8) {
                speed = 65.0f;
            }
            if (player->unk_22 == -1 && player->unk_20 >= 6 && player->unk_20 <= 8) {
                speed = 65.0f;
            }
        } else if (dist < 400.0f && foe->wait < 5) {
            if (player->unk_22 == 1 && player->unk_20 >= 7 && player->unk_20 <= 8) {
                speed = 15.0f;
            }
            if (player->unk_22 == -1 && player->unk_20 >= 6 && player->unk_20 <= 8) {
                speed = 15.0f;
            }
        }
    }
    *stickX = sindf(angle) * speed;
    *stickY = cosdf(angle) * speed;
}

// Picks a CPU player's lane and speed multiplier based on its difficulty.
s16 m236_ComLaneGet(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;
    s16 lane;

    player->unk_4C = 1.0f;
    switch (GwPlayer[player->playerId].cpu_difficulty) {
        case 0:
            if ((u8)(rand8() % 10) < 6) {
                lane = 0;
            } else {
                lane = (u8)(rand8() % 3);
            }
            if ((u8)(rand8() % 10) < 4) {
                player->unk_4C = 0.8f;
            }
            break;
        case 1:
            if ((u8)(rand8() % 10) < 7) {
                lane = 0;
            } else {
                lane = (u8)(rand8() % 3);
            }
            if ((u8)(rand8() % 10) < 4) {
                player->unk_4C = 0.8f;
            }
            break;
        case 2:
            lane = 0;
            if ((u8)(rand8() % 10) < 5) {
                player->unk_4C = 0.8f;
            }
            break;
        case 3:
            lane = 0;
            if ((u8)(rand8() % 10) < 6) {
                player->unk_4C = 0.8f;
            }
            break;
    }
    return lane;
}

void m236_PieceGrab(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;
    s16 playerId = player->playerId;
    u16 motion;

    player->unk_28 = 1;
    player->unk_26++;
    m236_pieceObj->work[2] &= ~(1 << player->playerId);
    Hu3DModelAttrSet(m236_pieceObj->model[player->playerId * 5 + 4], HU3D_ATTR_DISPOFF,
                       HU3D_ATTR_DISPOFF);
    Hu3DModelScaleSet(m236_pieceObj->model[playerId * 5], 1.0f, 1.0f, 1.0f);
    Hu3DModelHookSet(m236_pieceObj->model[playerId * 5], arg0->model[0], "item_hook");
    Hu3DModelAttrSet(m236_pieceObj->model[playerId * 5], HU3D_ATTR_HOOK | HU3D_ATTR_DISPOFF, HU3D_ATTR_HOOK);
    if (GwPlayer[player->playerId].chr == CHAR_DK) {
        switch (player->motionState) {
            case 0:
                motion = arg0->motion[7];
                break;
            case 1:
                motion = arg0->motion[3];
                break;
            case 2:
                motion = arg0->motion[8];
                break;
        }
        Hu3DMotionModelSet(arg0->model[0], motion);
        Hu3DMotionAttrSet(arg0->model[0], 2, 2);
    } else {
        Hu3DMotionShapeSet(arg0->model[0], Hu3DData[arg0->motion[3]].motId, 2);
    }
}

void m236_PieceDrop(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;
    s16 playerId = player->playerId;
    omObjData *obj;
    FridgedBridgesPieceWork *work;

    player->unk_28 = 0;
    Hu3DModelAttrSet(m236_pieceObj->model[playerId * 5], HU3D_ATTR_HOOK, HU3D_ATTR_NONE);
    m236_PlayerMotRestore(arg0);
    player->state = 0;
    obj = omAddObj(10, 0, 0, -1, m236_PieceDropObjMain);
    work = OM_GET_WORK_PTR(obj, FridgedBridgesPieceWork);
    work->playerObj = arg0;
    work->phase = 0;
    work->fallSpeed = 3.0f;
    obj->trans.x = sindf(arg0->rot.y) * 80.0f + arg0->trans.x;
    obj->trans.z = cosdf(arg0->rot.y) * 80.0f + arg0->trans.z;
    obj->trans.y = arg0->trans.y + 80.0f;
    obj->rot.y = arg0->rot.y;
    obj->rot.x = obj->rot.z = 0.0f;
    Hu3DModelPosSet(m236_pieceObj->model[playerId * 5], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelRotSet(m236_pieceObj->model[playerId * 5], arg0->rot.x, arg0->rot.y, arg0->rot.z);
}

void m236_PlayerMotRestore(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;
    u16 motion;

    if (GwPlayer[player->playerId].chr == CHAR_DK) {
        switch (player->motionState) {
            case 0:
                motion = arg0->motion[0];
                break;
            case 1:
                motion = arg0->motion[1];
                break;
            case 2:
                motion = arg0->motion[2];
                break;
        }
        Hu3DMotionModelSet(arg0->model[0], motion);
    } else {
        Hu3DData[arg0->model[0]].motIdShape = 0xFF;
    }
}

void m236_PieceObjInit(omObjData *arg0) {
    f32 sign[2][4];
    omObjData *obj;
    s32 i;
    s32 j;

    sign[0][0] = 1.0f;
    sign[0][1] = -1.0f;
    sign[0][2] = 1.0f;
    sign[0][3] = -1.0f;
    sign[1][0] = 1.0f;
    sign[1][1] = 1.0f;
    sign[1][2] = -1.0f;
    sign[1][3] = -1.0f;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            m236_bridgeSlotPosTbl[i][j].x = m236_bridgePosTbl[j].x * sign[0][i];
            m236_bridgeSlotPosTbl[i][j].y = m236_bridgePosTbl[j].y * sign[1][i];
        }
        m236_pieceStockPosTbl[i].x = m236_pieceStockPos.x * sign[0][i];
        m236_pieceStockPosTbl[i].y = m236_pieceStockPos.y * sign[1][i];
    }
    for (i = 0; i < 4; i++) {
        arg0->model[i * 5] = Hu3DModelRead(0x450000, 0x20699);
        arg0->model[i * 5 + 1] = Hu3DModelRead(0x450001, 0x699);
        arg0->model[i * 5 + 2] = Hu3DModelRead(0x450002, 0x699);
        arg0->model[i * 5 + 3] = Hu3DModelRead(0x450003, 0x699);
        arg0->model[i * 5 + 4] = Hu3DModelRead(0x450000, 0x20699);
        Hu3DModelAttrSet(arg0->model[i * 5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(arg0->model[i * 5 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(arg0->model[i * 5 + 2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(arg0->model[i * 5 + 3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(arg0->model[i * 5 + 4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(arg0->model[i * 5], m236_cameraBitTbl[i]);
        Hu3DModelCameraSet(arg0->model[i * 5 + 1], m236_cameraBitTbl[i]);
        Hu3DModelCameraSet(arg0->model[i * 5 + 2], m236_cameraBitTbl[i]);
        Hu3DModelCameraSet(arg0->model[i * 5 + 3], m236_cameraBitTbl[i]);
        Hu3DModelCameraSet(arg0->model[i * 5 + 4], m236_cameraBitTbl[i]);
    }
    arg0->work[2] = 0;
    omMakeGroup(1, 12);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            Hu3DModelAttrSet(arg0->model[i * 5 + 1 + j], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            obj = omAddObj(10, 1, 0, 1, m236_BridgeSinkObjMain);
            obj->model[0] = arg0->model[i * 5 + 1 + j];
            omSetTra(obj, m236_bridgeSlotPosTbl[i][j].x, 0.0f, m236_bridgeSlotPosTbl[i][j].y);
            obj->work[0] = j * 5 + 15;
            obj->work[1] = 0;
            obj->work[2] = i;
        }
    }
    arg0->work[0] = 0;
    arg0->func = m236_PieceSinkWaitObjMain;
}

void m236_BridgeSinkObjMain(omObjData *arg0) {
    if (arg0->work[0] == 0) {
        if (arg0->work[1] == 0) {
            m236_EffCreate(0, arg0->work[2], arg0->trans.x, -100.0f, arg0->trans.z);
            arg0->work[1] = 1;
            if (m236_sinkSeF == 0) {
                HuAudFXPlay(0x42C);
                m236_sinkSeF = 1;
            }
        }
        if (arg0->trans.y < -120.0f) {
            Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            omDelObj(arg0);
        } else {
            arg0->trans.y -= 8.0f;
        }
    } else {
        arg0->work[0]--;
    }
}

void m236_PieceSinkWaitObjMain(omObjData *arg0) {
    omObjData **bridgeObjs = omGetGroupMemberList(1);
    s32 deletedCount = 0;
    s32 i;

    for (i = 0; i < 12; i++) {
        deletedCount += bridgeObjs[i] == NULL;
    }

    if (deletedCount == 12) {
        arg0->work[0] = 1;
        arg0->func = m236_PieceStockObjMain;
    }
}

void m236_PieceDropObjMain(omObjData *arg0) {
    FridgedBridgesPieceWork *work = OM_GET_WORK_PTR(arg0, FridgedBridgesPieceWork);
    FridgedBridgesPlayer *player = work->playerObj->data;
    u16 modelId;

    if (work->phase == 0) {
        modelId = m236_pieceObj->model[player->playerId * 5];
        arg0->trans.y -= work->fallSpeed;
        work->fallSpeed *= 1.4f;
        if (arg0->trans.y < -100.0f) {
            work->phase = 1;
            m236_EffCreate(0, player->playerId, arg0->trans.x, -160.0f, arg0->trans.z);
            Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            modelId = m236_pieceObj->model[player->playerId * 5 + 1 + player->unk_24];
            Hu3DModelAttrSet(m236_pieceObj->model[player->playerId * 5 + 1 + player->unk_24],
                               HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            HuAudPlayerFXPlay(0x42B, player->playerId);
        }
        Hu3DModelPosSet(modelId, arg0->trans.x, arg0->trans.y, arg0->trans.z);
        Hu3DModelRotSet(modelId, arg0->rot.x, arg0->rot.y, arg0->rot.z);
    } else {
        modelId = m236_pieceObj->model[player->playerId * 5 + 1 + player->unk_24];
        arg0->trans.y += 8.0f;
        if (arg0->trans.y >= 0.0f) {
            arg0->trans.y = 0.0f;
        }
        Hu3DModelPosSet(modelId, m236_bridgeSlotPosTbl[player->playerId][player->unk_24].x, arg0->trans.y,
                        m236_bridgeSlotPosTbl[player->playerId][player->unk_24].y);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        if (arg0->trans.y == 0.0f) {
            player->state = 1;
            player->unk_24++;
            omDelObj(arg0);
        }
    }
}

// Shrinking phase of a player's bridge-sink object (created with m236_PieceDropObjMain).
// Sinks the player model 10 units per frame while scaling it away; when the
// scale runs out, stops the animation and deletes the object.
void m236_PieceShrinkObjMain(omObjData *arg0) {
    FridgedBridgesPlayer *player = OM_GET_DATA_PTR((omObjData *)arg0->work[0], FridgedBridgesPlayer);
    s16 playerId = player->playerId;
    u16 modelId = m236_pieceObj->model[playerId * 5];
    f32 *scale;

    arg0->trans.y -= 10.0f;
    Hu3DModelPosSet(modelId, arg0->trans.x, arg0->trans.y, arg0->trans.z);
    scale = (f32 *)&arg0->work[2];
    *scale -= 0.04f;
    if (*scale <= 0.0f) {
        Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        omDelObj(arg0);
    } else {
        Hu3DModelScaleSet(modelId, *scale, *scale, *scale);
    }
}

void m236_PieceStockObjMain(omObjData *arg0) {
    FridgedBridgesPlayer *player;
    omObjData *obj;
    u32 bit;
    s32 i;

    for (i = 0; i < 4; i++) {
        player = m236_playerObjTbl[i]->data;
        bit = 1 << i;
        if (!(bit & arg0->work[2]) && player->unk_26 != 3) {
            obj = omAddObj(30, 1, 0, -1, m236_PieceGrowObjMain);
            obj->model[0] = arg0->model[i * 5 + 4];
            omSetTra(obj, m236_pieceStockPosTbl[i].x, 25.0f, m236_pieceStockPosTbl[i].y);
            omSetSca(obj, 1.0f, 0.0f, 1.0f);
            omSetRot(obj, 0.0f, 0.0f, 0.0f);
            Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
            Hu3DModelScaleSet(obj->model[0], 1.0f, 0.0f, 1.0f);
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            arg0->work[2] |= bit;
        }
    }
}

void m236_PieceGrowObjMain(omObjData *arg0) {
    f32 *scale = OM_GET_WORK_PTR(arg0, f32);

    *scale += 0.05f;
    if (*scale >= 1.0f) {
        *scale = 1.0f;
    }
    omSetSca(arg0, 1.0f, *scale, 1.0f);
    if (*scale == 1.0f) {
        omDelObj(arg0);
    }
}

void m236_IntroObjMain(omObjData *arg0) {
    FridgedBridgesPlayer *player;
    omObjData *obj;
    s32 i;

    switch (m236_introPhase) {
        case 0:
            if (m236_introInitF == 0) {
                for (i = 0; i < 4; i++) {
                    obj = m236_playerObjTbl[i];
                    player = obj->data;
                    if (player->unk_28 == 0) {
                        m236_PieceGrab(obj);
                    }
                }
                m236_introInitF = 1;
                m236_CameraPathInit();
            }
            WipeCreateIn(WIPE_TYPE_PREV, 16);
            m236_introPhase = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                m236_introPhase = 2;
                HuAudFXPlay(0x42E);
            }
            break;
        case 2:
            if (m236_pieceObj->work[0] == 1) {
                m236_introPhase = 3;
            }
            break;
        case 3:
            if (m236_CameraPathPan(40.0f) == 1) {
                for (i = 0; i < 4; i++) {
                    player = m236_playerObjTbl[i]->data;
                    player->unk_2C->work[0] = 1;
                }
                omDelObj(arg0);
                m236_introObj = NULL;
                MgFlowStatSet(MG_STATE_START);
            }
            break;
    }
}

// Winner sequence: the winner walks to the goal and the camera zooms in.
void m236_WinObjMain(omObjData *arg0) {
    FridgedBridgesPlayer *player;
    omObjData *obj;
    s16 model;
    s32 i;

    switch (m236_winPhase) {
        case 0:
            obj = m236_playerObjTbl[m236_winner];
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(obj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            model = obj->model[0];
            obj->model[0] = obj->model[4];
            obj->model[4] = model;
            Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[1]].motId, 0, 6, 2);
            obj->rot.y = atan2df(m236_winPosTbl[m236_winner].x - obj->trans.x,
                                 m236_winPosTbl[m236_winner].z - obj->trans.z);
            m236_winPhase = 1;
            break;
        case 1:
            obj = m236_playerObjTbl[m236_winner];
            if (HuSqrtf((m236_winPosTbl[m236_winner].x - obj->trans.x) *
                            (m236_winPosTbl[m236_winner].x - obj->trans.x) +
                        (m236_winPosTbl[m236_winner].z - obj->trans.z) *
                            (m236_winPosTbl[m236_winner].z - obj->trans.z)) < 80.0f) {
                m236_winPhase = 2;
            } else {
                obj->trans.x += sindf(obj->rot.y) * 10.0f;
                obj->trans.z += cosdf(obj->rot.y) * 10.0f;
                Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
            }
            break;
        case 2:
            m236_winZoomStep = -650.0f / 30.0f;
            m236_winRotStep.x = 20.0f / 30.0f;
            m236_winRotStep.y = 0.0f;
            m236_winRotStep.z = 0.0f;
            m236_winCameraTimer = 30;
            m236_winPhase = 3;
            m236_playerObjTbl[m236_winner]->func = m236_PlayerFrontTurnObjMain;
            m236_playerObjTbl[m236_winner]->work[0] = 0;
            break;
        case 3:
            if (--m236_winCameraTimer != 0) {
                CZoomM[m236_winner] += m236_winZoomStep;
                CRotM[m236_winner].x += m236_winRotStep.x;
                CRotM[m236_winner].y += m236_winRotStep.y;
                CRotM[m236_winner].z += m236_winRotStep.z;
            } else {
                CZoomM[m236_winner] = 1065.0f;
                CRotM[m236_winner].x = -40.0f;
                CRotM[m236_winner].y = 0.0f;
                CRotM[m236_winner].z = 0.0f;
                m236_winPhase = 4;
            }
            break;
        case 4:
            if (m236_playerObjTbl[m236_winner]->work[0] == 1 &&
                MgFlowStatGet() == MG_STATE_RESULT) {
                player = m236_playerObjTbl[m236_winner]->data;
                CharAnimSet(m236_playerObjTbl[m236_winner]->model[0], 2,
                                   GwPlayer[player->playerId].chr,
                                   m236_playerObjTbl[m236_winner]->model[5]);
                Hu3DMotionShiftSet(
                    m236_playerObjTbl[m236_winner]->model[0],
                    Hu3DData[m236_playerObjTbl[m236_winner]->motion[5]].motId, 0, 6, 0);
                HuAudCharVoicePlay(omCharModelNoTbl[GwPlayer[m236_winner].chr][0] | 0x2F);
                m236_winPhase = 5;
                for (i = 0; i < 4; i++) {
                    obj = m236_playerObjTbl[i];
                    player = obj->data;
                    if (player->state != 3 && player->playerId != m236_winner) {
                        obj->func = m236_PlayerEndObjMain;
                    }
                    player->unk_44 = 1.0f;
                    if (player->playerId == m236_winner) {
                        GwPlayer[player->playerId].bonusCoin = 10;
                    }
                }
            }
            break;
        case 6:
            if (MgFlowStatGet() == MG_STATE_RESULT) {
                for (i = 0; i < 4; i++) {
                    obj = m236_playerObjTbl[i];
                    player = obj->data;
                    if (player->state != 3) {
                        obj->func = m236_PlayerEndObjMain;
                    }
                    player->unk_44 = 1.0f;
                }
                m236_winPhase = 5;
            }
            break;
        case 5:
            break;
    }
}

// Probes the floor height at 8 points around probe->pos plus the center, against
// both the ice floor and the player's bridges. Returns the number of probe points
// that found no floor at all.
s32 m236_FloorCheck(omObjData *arg0, FridgedBridgesProbe *probe) {
    FridgedBridgesPlayer *player = arg0->data;
    Vec pos;
    s32 missCount = 0;
    Hu3DPoint *points;
    Hu3DQuad *quad;
    f32 angle;
    f32 height;
    f32 best;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    s32 j;

    player->unk_1C = -1;
    for (i = 0; i < 9; i++) {
        if (i != 8) {
            angle = i * 45.0f;
            x = pos.x = sindf(angle) * 55.0f + probe->pos.x;
            y = pos.y = probe->pos.y;
            z = pos.z = cosdf(angle) * 55.0f + probe->pos.z;
        } else {
            x = pos.x = probe->pos.x;
            y = pos.y = probe->pos.y;
            z = pos.z = probe->pos.z;
        }
        best = probe->height[i] = -10000.0f;
        probe->bridgeIds[i] = 0xFFFF;
        points = (Hu3DPoint *)Hu3DData[m236_stageObj->model[player->playerId]].hmf->unk50;
        Hu3DQuadPoolCollect(m236_stageObj->model[player->playerId], &mgQuadPool,
                           m236_FaceInsideHook, &pos);
        for (quad = Hu3DQuadPoolNext(&mgQuadPool); quad != NULL;
             quad = Hu3DQuadPoolNext(&mgQuadPool)) {
            height = MapCalcPoint(x, y, z, points, quad);
            if (height > best) {
                probe->height[i] = best = height;
                probe->bridgeIds[i] = quad->vtx[0] & 0x3F00;
                if (i == 8) {
                    player->unk_1C = probe->bridgeIds[8];
                }
            }
        }
        for (j = 0; j < player->unk_24; j++) {
            pos.x = x - m236_bridgeSlotPosTbl[player->playerId][j].x;
            pos.z = z - m236_bridgeSlotPosTbl[player->playerId][j].y;
            points = (Hu3DPoint *)Hu3DData[m236_pieceObj->model[player->playerId * 5 + 1 + j]]
                         .hmf->unk50;
            Hu3DQuadPoolCollect(m236_pieceObj->model[player->playerId * 5 + 1 + j],
                               &mgQuadPool, m236_FaceInsideHook, &pos);
            for (quad = Hu3DQuadPoolNext(&mgQuadPool); quad != NULL;
                 quad = Hu3DQuadPoolNext(&mgQuadPool)) {
                height = MapCalcPoint(x, y, z, points, quad);
                if (height > best) {
                    probe->height[i] = best = height;
                    probe->bridgeIds[i] = player->unk_1C = quad->vtx[0] & 0x3F00;
                    if (i == 8) {
                        player->unk_1C = probe->bridgeIds[8];
                    }
                }
            }
        }
        if (best == -10000.0f) {
            missCount++;
        }
    }
    return missCount;
}

s32 m236_FaceInsideHook(s32 count, s16 *vtx, Hu3DPoint *points, Vec *pos) {
    return m236_FaceInsideXZCheck(pos, vtx - 1, points);
}

// Same as MgFaceInsideXZCheck, without the face type check.
s32 m236_FaceInsideXZCheck(Vec *pos, s16 *face, Hu3DPoint *points) {
    f32 x;
    f32 z;
    s32 count;
    s32 i;
    s32 next;

    x = pos->x;
    z = pos->z;
    count = ((u16)face[0] >> 14) + 2;
    face++;
    if (MapXZCross(x, z, &points[face[0]], &points[face[1]]) > 0.0f) {
        for (i = 1; i < count; i++) {
            next = (i + 1) % count;
            if (MapXZCross(x, z, &points[face[i]], &points[face[next]]) < 0.0f) {
                return FALSE;
            }
        }
    } else {
        for (i = 1; i < count; i++) {
            next = (i + 1) % count;
            if (MapXZCross(x, z, &points[face[i]], &points[face[next]]) > 0.0f) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

// Pushes a falling player away from the floor edges it is still touching.
void m236_PlayerEdgePush(omObjData *arg0) {
    FridgedBridgesProbe probe;
    f32 angle;
    f32 dx;
    f32 dz;
    u16 attempt;
    u16 missCount;
    u16 dir;
    u16 i;

    attempt = 0;
    do {
        probe.pos.x = arg0->trans.x;
        probe.pos.y = arg0->trans.y;
        probe.pos.z = arg0->trans.z;
        m236_FloorCheck(arg0, &probe);
        missCount = 0;
        for (i = 0; i < 8; i++) {
            if (probe.height[i] == -10000.0f) {
                missCount++;
            } else {
                dir = i + 4;
                if (dir >= 9) {
                    dir = i - 4;
                }
                angle = dir * 45.0f;
                dx = sindf(angle) * 5.0f;
                dz = cosdf(angle) * 5.0f;
                arg0->trans.x += dx;
                arg0->trans.z += dz;
            }
        }
    } while (missCount != 8 && ++attempt < 4);
}

// Returns 1 if the position is within reach of the player's dropped item.
u16 m236_PieceStockCheck(omObjData *arg0, f32 x, f32 y, f32 z) {
    FridgedBridgesPlayer *player = arg0->data;
    u16 playerId = player->playerId;
    f32 dist;

    if (!(m236_pieceObj->work[2] & (1 << playerId))) {
        return 0;
    }
    dist = HuSqrtf((x - m236_pieceStockPosTbl[playerId].x) * (x - m236_pieceStockPosTbl[playerId].x) +
                   (z - m236_pieceStockPosTbl[playerId].y) * (z - m236_pieceStockPosTbl[playerId].y));
    if (dist > HuSqrtf(6400.0f)) {
        return 0;
    }
    return 1;
}

void m236_RescueCreate(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;
    FridgedBridgesRescue *rescue;
    omObjData *obj;
    f32 angle;
    f32 x;

    obj = player->bridgeObj = omAddObj(40, 1, 0, -1, m236_RescueObjMain);
    rescue = obj->data = HuMemAllocTag(sizeof(FridgedBridgesRescue), TAG_OVERLAY);
    rescue->playerObj = arg0;
    obj->model[0] = arg0->model[2];
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    angle = (rand8() * rand8()) % 3600 / 10.0f;
    x = sindf(angle) * 600.0f + arg0->trans.x;
    omSetTra(obj, x, 500.0f, cosdf(angle) * 600.0f + arg0->trans.z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    rescue->state = 0;
    rescue->released = 0;
    rescue->sfxId = -1;
    obj->func = m236_RescueObjMain;
}

// Rescue sequence for a player that fell off the bridges: fly in, pick the player
// up, carry them back to the start of the course and drop them off.
void m236_RescueObjMain(omObjData *arg0) {
    FridgedBridgesRescue *rescue = arg0->data;
    FridgedBridgesPlayer *player = rescue->playerObj->data;
    u16 playerId = player->playerId;
    Vec pos;
    Vec2f screen;
    f32 dist;

    switch (rescue->state) {
        case 0:
            if (m236_goalF == 1) {
                rescue->state = 6;
                break;
            }
            dist = HuSqrtf((arg0->trans.x - rescue->playerObj->trans.x) * (arg0->trans.x - rescue->playerObj->trans.x) +
                           (arg0->trans.z - (rescue->playerObj->trans.z - 30.0f)) *
                               (arg0->trans.z - (rescue->playerObj->trans.z - 30.0f)));
            pos.x = arg0->trans.x;
            pos.y = arg0->trans.y;
            pos.z = arg0->trans.z;
            Hu3DCam3Dto2D(player->playerId, &pos, &screen);
            screen.x -= m236_viewOfsTbl[player->playerId].x;
            screen.y -= m236_viewOfsTbl[player->playerId].y;
            if (screen.x >= 0.0f && screen.x < 160.0 && screen.y >= 0.0f && screen.y < 120.0f &&
                rescue->sfxId == -1) {
                rescue->sfxId = HuAudPlayerFXPlay(0x431, player->playerId);
            }
            if (dist > 18.0f) {
                arg0->trans.x += (rescue->playerObj->trans.x - arg0->trans.x) / dist * 18.0f;
                arg0->trans.z += (rescue->playerObj->trans.z - 30.0f - arg0->trans.z) / dist * 18.0f;
            } else {
                arg0->trans.x = rescue->playerObj->trans.x;
                arg0->trans.z = rescue->playerObj->trans.z - 30.0f;
                rescue->state = 1;
            }
            break;
        case 1:
            if (m236_goalF == 1) {
                rescue->state = 6;
                break;
            }
            arg0->trans.y -= 30.0f;
            if (arg0->trans.y <= 10.0f) {
                arg0->trans.y = 10.0f;
                rescue->playerObj->func = m236_PlayerHoldObjMain;
                rescue->state = 2;
                Hu3DMotionAttrSet(rescue->playerObj->model[0], 1, 1);
            }
            break;
        case 2:
            if (m236_goalF == 1) {
                rescue->state = 7;
                break;
            }
            arg0->trans.y += 34.0f;
            omSetTra(rescue->playerObj, rescue->playerObj->trans.x, arg0->trans.y - 160.0f,
                     rescue->playerObj->trans.z);
            Hu3DModelPosSet(rescue->playerObj->model[3], rescue->playerObj->trans.x, arg0->trans.y - 160.0f,
                            rescue->playerObj->trans.z);
            if (arg0->trans.y > 900.0f) {
                rescue->state = 3;
                Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(rescue->playerObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            break;
        case 3:
            if (m236_goalF == 1) {
                rescue->state = 6;
                break;
            }
            dist = HuSqrtf((CenterM[playerId].x - player->pos.x) * (CenterM[playerId].x - player->pos.x) +
                           (CenterM[playerId].z - player->pos.z) * (CenterM[playerId].z - player->pos.z));
            if (dist > 18.0f) {
                CenterM[playerId].x += (player->pos.x - CenterM[playerId].x) / dist * 18.0f;
                CenterM[playerId].z += (player->pos.z - CenterM[playerId].z) / dist * 18.0f;
            } else {
                CenterM[playerId].x = player->pos.x;
                CenterM[playerId].z = player->pos.z;
                rescue->state = 4;
                omSetTra(arg0, player->pos.x, 900.0f, player->pos.z - 30.0f);
                omSetTra(rescue->playerObj, player->pos.x, 740.0f, player->pos.z);
                Hu3DModelPosSet(rescue->playerObj->model[0], rescue->playerObj->trans.x, rescue->playerObj->trans.y,
                                rescue->playerObj->trans.z);
                Hu3DModelPosSet(rescue->playerObj->model[3], rescue->playerObj->trans.x, rescue->playerObj->trans.y,
                                rescue->playerObj->trans.z);
                Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelAttrSet(rescue->playerObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            break;
        case 4:
            if (m236_goalF == 1) {
                rescue->state = 7;
                break;
            }
            arg0->trans.y -= 24.0f;
            omSetTra(rescue->playerObj, player->pos.x, arg0->trans.y - 160.0f, player->pos.z);
            Hu3DModelPosSet(rescue->playerObj->model[3], player->pos.x, arg0->trans.y - 160.0f, player->pos.z);
            if (arg0->trans.y < 160.0f) {
                arg0->trans.y = 160.0f;
                rescue->state = 5;
                Hu3DMotionModelSet(rescue->playerObj->model[0], rescue->playerObj->motion[0]);
                Hu3DMotionAttrSet(rescue->playerObj->model[0], 2, 2);
                Hu3DModelPosSet(rescue->playerObj->model[1], rescue->playerObj->trans.x, 0.0f,
                                rescue->playerObj->trans.z);
                Hu3DModelAttrSet(rescue->playerObj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                rescue->timer = 0;
                player->scale = 1.0f;
                HuAudPlayerFXPlay(0x430, player->playerId);
            }
            break;
        case 5:
            if (m236_goalF == 1 && rescue->released == 1) {
                rescue->state = 6;
                Hu3DModelAttrSet(rescue->playerObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                player->state = 1;
                break;
            }
            arg0->trans.y += 40.0f;
            if (arg0->trans.y > 1500.0f) {
                Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                if (rescue->sfxId != -1) {
                    HuAudFXStop(rescue->sfxId);
                }
                omDelObj(arg0);
                break;
            }
            rescue->timer++;
            if (rescue->timer >= 30) {
                if (rescue->released == 0) {
                    rescue->released = 1;
                    Hu3DModelAttrSet(rescue->playerObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    if (player->unk_28 == 1) {
                        Hu3DModelAttrSet(m236_pieceObj->model[player->playerId * 5], HU3D_ATTR_DISPOFF,
                                           0);
                    }
                    Hu3DModelAttrSet(rescue->playerObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    player->state = 1;
                    player->unk_08 = player->unk_0C = 0.0f;
                    player->unk_2C->work[0] = 1;
                    rescue->playerObj->func = m236_PlayerObjMain;
                    if (player->unk_24 == 3) {
                        player->unk_1E = 0;
                        player->unk_22 = 1;
                    } else {
                        player->unk_1E = 0;
                        if (player->unk_28 == 0) {
                            player->unk_22 = -1;
                        } else {
                            player->unk_22 = 1;
                        }
                    }
                }
            } else {
                if (rescue->timer & 1) {
                    Hu3DModelAttrSet(rescue->playerObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    if (player->unk_28 == 1) {
                        Hu3DModelAttrSet(m236_pieceObj->model[player->playerId * 5], HU3D_ATTR_DISPOFF,
                                           HU3D_ATTR_DISPOFF);
                    }
                    Hu3DModelAttrSet(rescue->playerObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                } else {
                    Hu3DModelAttrSet(rescue->playerObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    if (player->unk_28 == 1) {
                        Hu3DModelAttrSet(m236_pieceObj->model[player->playerId * 5], HU3D_ATTR_DISPOFF,
                                           0);
                    }
                    Hu3DModelAttrSet(rescue->playerObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
                player->scale -= 0.03f;
                Hu3DModelScaleSet(rescue->playerObj->model[3], player->scale, player->scale, player->scale);
            }
            break;
        case 6:
            arg0->trans.y += 40.0f;
            if (arg0->trans.y > 1500.0f) {
                Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                if (rescue->sfxId != -1) {
                    HuAudFXStop(rescue->sfxId);
                }
                omDelObj(arg0);
            }
            break;
        case 7:
            arg0->trans.y += 40.0f;
            omSetTra(rescue->playerObj, arg0->trans.x, arg0->trans.y - 160.0f, arg0->trans.z + 30.0f);
            Hu3DModelPosSet(rescue->playerObj->model[3], rescue->playerObj->trans.x, arg0->trans.y - 160.0f,
                            rescue->playerObj->trans.z);
            if (arg0->trans.y > 1500.0f) {
                Hu3DModelAttrSet(rescue->playerObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                if (rescue->sfxId != -1) {
                    HuAudFXStop(rescue->sfxId);
                }
                omDelObj(arg0);
            }
            break;
    }
}

// True once every player has left the frozen (state 2) pose.
u16 m236_FallDoneCheck(void) {
    s32 notFrozenCount = 0;
    s32 i = 0;
    omObjData **playerObjs = m236_playerObjTbl;

    for (; i < 4; i++) {
        notFrozenCount += OM_GET_DATA_PTR(playerObjs[i], FridgedBridgesPlayer)->state != 2;
    }
    return notFrozenCount == 4;
}

void m236_CameraPathInit(void) {
    s32 i;

    m236_cameraPathNo = 10;
    for (i = 0; i < 4; i++) {
        CenterM[i].x = m236_cameraPathPosTbl[i][m236_cameraPathNo].x;
        CenterM[i].y = 100.0f;
        CenterM[i].z = m236_cameraPathPosTbl[i][m236_cameraPathNo].y;
    }
}

// Pans each camera back along its path and zooms out. Returns 1 when every
// camera has reached the start of its path and is fully zoomed out.
u16 m236_CameraPathPan(f32 speed) {
    f32 targetX;
    f32 targetZ;
    f32 centerX;
    f32 centerZ;
    f32 angle;
    f32 dx;
    f32 dz;
    f32 zoomStep = 12.5f;
    s32 doneCount = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (m236_cameraPanDoneTbl[i] == 0) {
            targetX = m236_cameraPathPosTbl[i][m236_cameraPathNo].x;
            targetZ = m236_cameraPathPosTbl[i][m236_cameraPathNo].y;
            centerX = CenterM[i].x;
            centerZ = CenterM[i].z;
            if (HuSqrtf((centerX - targetX) * (centerX - targetX) + (centerZ - targetZ) * (centerZ - targetZ)) <=
                speed) {
                if (m236_cameraPathNo == 0) {
                    CenterM[i].x = m236_cameraPathPosTbl[i][0].x;
                    CenterM[i].z = m236_cameraPathPosTbl[i][0].y;
                    m236_cameraPanDoneTbl[i]++;
                } else {
                    m236_cameraPathNo--;
                    targetX = m236_cameraPathPosTbl[i][m236_cameraPathNo].x;
                    targetZ = m236_cameraPathPosTbl[i][m236_cameraPathNo].y;
                }
            }
            if (m236_cameraPanDoneTbl[i] == 0) {
                angle = atan2df(-(centerX - targetX), centerZ - targetZ);
                dx = sindf(angle) * speed;
                dz = -cosdf(angle) * speed;
                CenterM[i].x += dx;
                CenterM[i].z += dz;
            }
        } else {
            doneCount++;
        }
        if (CZoomM[i] < 1715.0f) {
            CZoomM[i] += zoomStep;
        }
        if (CZoomM[i] >= 1715.0f) {
            CZoomM[i] = 1715.0f;
            doneCount++;
        }
    }
    return doneCount == 8;
}

void m236_FoeCreateAll(void) {
    FridgedBridgesFoe *foe;
    omObjData *obj;
    f32 angle;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = m236_foeObjTbl[i] = omAddObj(30, 1, 0, -1, m236_FoeObjMain);
        if (i == 0) {
            obj->model[0] = Hu3DModelRead(0x450010, 0x20699);
        } else {
            obj->model[0] = Hu3DModelLink(m236_foeObjTbl[0]->model[0]);
        }
        foe = obj->data = HuMemAllocTag(sizeof(FridgedBridgesFoe), TAG_OVERLAY);
        foe->state = 0;
        foe->dir = 0;
        foe->wait = 0;
        foe->index = i;
        omSetTra(obj, m236_foeJumpPosTbl[i][0].x, -150.0f, m236_foeJumpPosTbl[i][0].y);
        omSetSca(obj, 0.5f, 0.5f, 0.5f);
        Hu3DModelCameraSet(obj->model[0], m236_cameraBitTbl[i]);
        angle = atan2df(-(obj->trans.x - m236_foeJumpPosTbl[i][1].x),
                        -(obj->trans.z - m236_foeJumpPosTbl[i][1].y));
        if (angle < 0.0f) {
            angle += 360.0f;
        }
        omSetRot(obj, 0.0f, angle, 0.0f);
        Hu3DMotionAttrSet(obj->model[0], 2, 2);
        foe->jumpDist = HuSqrtf((m236_foeJumpPosTbl[i][0].x - m236_foeJumpPosTbl[i][1].x) *
                                    (m236_foeJumpPosTbl[i][0].x - m236_foeJumpPosTbl[i][1].x) +
                                (m236_foeJumpPosTbl[i][0].y - m236_foeJumpPosTbl[i][1].y) *
                                    (m236_foeJumpPosTbl[i][0].y - m236_foeJumpPosTbl[i][1].y));
        foe->arcScale = 200.0f / ((foe->jumpDist / 2.0f) * (foe->jumpDist / 2.0f));
        foe->speed = 16.0f;
        foe->jumpPos = 0.0f;
        foe->unk_18 = -obj->rot.y;
        if (foe->unk_18 < 0.0f) {
            foe->unk_18 += 360.0f;
        }
    }
}

void m236_FoeObjMain(omObjData *arg0) {
    FridgedBridgesFoe *foe = arg0->data;
    FridgedBridgesPlayer *player = m236_playerObjTbl[foe->index]->data;
    f32 step;
    f32 t;
    f32 temp; // previous Y while jumping, angle difference while turning
    f32 angle;

    switch (foe->state) {
        case 0:
            if (player->state != 2 && player->state != 3 && MgFlowStatGet() == MG_STATE_PLAY) {
                if (foe->wait == 0) {
                    foe->state = 1;
                    foe->jumpPos = 0.0f;
                } else {
                    foe->wait--;
                }
            }
            break;
        case 1:
            if (foe->jumpPos > foe->jumpDist) {
                step = foe->jumpPos - foe->jumpDist;
                foe->state = 2;
            } else {
                step = foe->speed;
            }
            foe->jumpPos += step;
            t = foe->jumpPos - foe->jumpDist / 2.0f;
            temp = arg0->trans.y;
            arg0->trans.y = -foe->arcScale * t * t + 60.0f;
            arg0->rot.x = atan2df(temp - arg0->trans.y, step);
            arg0->trans.x += sindf(arg0->rot.y) * step;
            arg0->trans.z += cosdf(arg0->rot.y) * step;
            if (foe->state == 2) {
                m236_EffCreate(0, foe->index, arg0->trans.x, -100.0f, arg0->trans.z);
            }
            break;
        case 2:
            angle = atan2df(-(arg0->trans.x - m236_foeJumpPosTbl[foe->index][foe->dir].x),
                            -(arg0->trans.z - m236_foeJumpPosTbl[foe->index][foe->dir].y));
            arg0->rot.x = 0.0f;
            if (angle < arg0->rot.x) {
                angle += 360.0f;
            }
            if (angle != arg0->rot.y) {
                temp = angle - arg0->rot.y;
                if (temp < 0.0f) {
                    temp += 360.0f;
                }
                if (temp < 180.0f) {
                    if (temp > 13.5f) {
                        arg0->rot.y += 13.5f;
                    } else {
                        arg0->rot.y = angle;
                    }
                } else if (360.0f - temp > 13.5f) {
                    arg0->rot.y -= 13.5f;
                } else {
                    arg0->rot.y = angle;
                }
                if (arg0->rot.y < 0.0f) {
                    arg0->rot.y += 360.0f;
                }
                if (arg0->rot.y >= 360.0f) {
                    arg0->rot.y -= 360.0f;
                }
            } else if (player->state != 2 && player->state != 3 && MgFlowStatGet() == MG_STATE_PLAY) {
                foe->state = 0;
                foe->wait = (u8)(rand8() % 10) * 2 + 20;
                foe->dir ^= 1;
            }
            break;
    }
}

// Pushes the player out of the foe's reach, stunning the player on first contact.
void m236_FoeHitPush(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;
    omObjData *foeObj = m236_foeObjTbl[player->playerId];
    f32 dist;
    f32 reach;

    dist = HuSqrtf((arg0->trans.x - foeObj->trans.x) * (arg0->trans.x - foeObj->trans.x) +
                   (arg0->trans.z - foeObj->trans.z) * (arg0->trans.z - foeObj->trans.z));
    reach = HuSqrtf(12100.0f);
    if (dist > reach) {
        return;
    }
    dist = reach - dist;
    arg0->trans.x += sindf(foeObj->rot.y) * dist;
    arg0->trans.z += cosdf(foeObj->rot.y) * dist;
    if (player->unk_56 == 0) {
        player->unk_56 = 1;
        player->unk_58 = 20;
        omVibrate(player->playerId, 20, 0, 20);
    }
}

// Snaps the player back onto the line between its two nearest path points.
void m236_ReturnPosCalc(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;
    Vec2f a;
    Vec2f b;
    Vec2f unused; // unreferenced, pads the stack frame
    f32 slope;
    f32 offset;
    f32 t;

    if ((player->unk_68 == 0x1200) | (player->unk_68 == 0x100)) {
        player->pos.x = m236_startPosTbl[player->playerId].x;
        player->pos.y = m236_startPosTbl[player->playerId].y;
        player->pos.z = m236_startPosTbl[player->playerId].z;
    } else if (player->unk_68 == 0x300) {
        player->pos.x = m236_bridgeSlotPosTbl[player->playerId][0].x;
        player->pos.z = m236_bridgeSlotPosTbl[player->playerId][0].y;
    } else if (player->unk_68 == 0x400) {
        player->pos.x = m236_bridgeSlotPosTbl[player->playerId][1].x;
        player->pos.z = m236_bridgeSlotPosTbl[player->playerId][1].y;
    } else if (player->unk_68 == 0x500) {
        player->pos.x = m236_bridgeSlotPosTbl[player->playerId][2].x;
        player->pos.z = m236_bridgeSlotPosTbl[player->playerId][2].y;
    }
    m236_PathNearGet(player, &a, &b);
    if (a.x != b.x) {
        slope = (a.y - b.y) / (a.x - b.x);
        if (slope != 0.0f) {
            offset = slope * a.x - a.y;
            slope = -slope;
            t = -((slope * player->pos.x + player->pos.z + offset) / (slope * slope + 1.0f));
            player->pos.x = slope * t + player->pos.x;
            player->pos.z = t + player->pos.z;
        } else {
            player->pos.z = a.y;
        }
    } else {
        player->pos.x = a.x;
    }
}

// Finds the CPU path point nearest to the player (a) and the closer of its two
// neighbors (b).
void m236_PathNearGet(FridgedBridgesPlayer *player, Vec2f *a, Vec2f *b) {
    Vec2f pos;
    Vec2f point;
    f32 dist;
    f32 best;
    s32 bestIndex;
    s32 prev;
    s32 next;
    s32 i;

    pos.x = player->pos.x;
    pos.y = player->pos.z;
    best = 100000.0f;
    bestIndex = 0;
    for (i = 0; i < 12; i++) {
        point.x = m236_comPathPosTbl[player->playerId][0][i].x;
        point.y = m236_comPathPosTbl[player->playerId][0][i].y;
        dist = HuSqrtf((point.x - pos.x) * (point.x - pos.x) + (point.y - pos.y) * (point.y - pos.y));
        if (dist < best) {
            best = dist;
            bestIndex = i;
        }
    }
    a->x = m236_comPathPosTbl[player->playerId][0][bestIndex].x;
    a->y = m236_comPathPosTbl[player->playerId][0][bestIndex].y;
    prev = bestIndex - 1;
    next = bestIndex + 1;
    if (prev < 0) {
        b->x = m236_comPathPosTbl[player->playerId][0][next].x;
        b->y = m236_comPathPosTbl[player->playerId][0][next].y;
    } else if (next == 12) {
        b->x = m236_comPathPosTbl[player->playerId][0][prev].x;
        b->y = m236_comPathPosTbl[player->playerId][0][prev].y;
    } else {
        dist = HuSqrtf((m236_comPathPosTbl[player->playerId][0][prev].x - pos.x) *
                           (m236_comPathPosTbl[player->playerId][0][prev].x - pos.x) +
                       (m236_comPathPosTbl[player->playerId][0][prev].y - pos.y) *
                           (m236_comPathPosTbl[player->playerId][0][prev].y - pos.y));
        if (dist < HuSqrtf((m236_comPathPosTbl[player->playerId][0][next].x - pos.x) *
                               (m236_comPathPosTbl[player->playerId][0][next].x - pos.x) +
                           (m236_comPathPosTbl[player->playerId][0][next].y - pos.y) *
                               (m236_comPathPosTbl[player->playerId][0][next].y - pos.y))) {
            b->x = m236_comPathPosTbl[player->playerId][0][prev].x;
            b->y = m236_comPathPosTbl[player->playerId][0][prev].y;
        } else {
            b->x = m236_comPathPosTbl[player->playerId][0][next].x;
            b->y = m236_comPathPosTbl[player->playerId][0][next].y;
        }
    }
}
