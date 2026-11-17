#include "common.h"
#include "math.h"
#include "game/overlays/minigame.h"

// Per-player state for this minigame. Lives in the `data` pointer (0x5C) of each
// of the group 0 player objects.
typedef struct EndOfTheLinePlayer {
    /* 0x00 */ u16 playerIdx;
    /* 0x02 */ u16 gwPlayerIdx;
    /* 0x04 */ omObjData *unk04;
    /* 0x08 */ omObjFunc unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u16 unk16;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u16 unk1C;
    /* 0x1E */ u16 unk1E;
    /* 0x20 */ omObjData *obj;
    /* 0x24 */ Vec pos;
    /* 0x30 */ Vec rot;
    /* 0x3C */ Vec pos2;
    /* 0x48 */ Vec rot2;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ u16 unk5C;
    /* 0x5E */ u16 esprites[2];
    /* 0x62 */ u16 esprites2[2];
    /* 0x66 */ char unk66[2];
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ u16 unk70;
    /* 0x72 */ char unk72[2];
    /* 0x74 */ f32 unk74;
    /* 0x78 */ s16 unk78;
    /* 0x7A */ s16 unk7A[3];
    /* 0x80 */ u16 unk80;
    /* 0x82 */ u16 unk82;
    /* 0x84 */ u16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ u16 unk8A;
    /* 0x8C */ s16 unk8C;
    /* 0x8E */ s16 unk8E;
    /* 0x90 */ s16 unk90;
    /* 0x92 */ s16 unk92;
} EndOfTheLinePlayer; // sizeof 0x94

// State for the whole minigame. Lives in the `data` pointer (0x5C) of the main
// object, m251_stageObj. The esprite handles a player uses are the
// slots at [playerIdx], [playerIdx + 2], [playerIdx + 4], ...
typedef struct EndOfTheLineStage {
    /* 0x00 */ u16 esprites[12];
    /* 0x18 */ f32 unk18[2][2];
} EndOfTheLineStage; // sizeof 0x28

// Work for the objects in m251_smokeObjTbl, which animate up to
// three models rising from a player.
typedef struct EndOfTheLineSmokeWork {
    /* 0x00 */ Vec pos[3];
    /* 0x24 */ f32 velY[3];
    /* 0x30 */ s16 timers[3];
    /* 0x36 */ s16 cooldown;
    /* 0x38 */ omObjData *target;
} EndOfTheLineSmokeWork; // sizeof 0x3C

// Data for the player's secondary object (EndOfTheLinePlayer.unk04).
typedef struct EndOfTheLineCameraWork {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ u16 unk10;
} EndOfTheLineCameraWork; // sizeof 0x14

// Grouped BSS variables; individual fields are aliased in undefined_syms.txt.
typedef struct EndOfTheLineResultWork {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02[2];
} EndOfTheLineResultWork; // sizeof 0x6

typedef struct EndOfTheLineSceneWork {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02[3];
} EndOfTheLineSceneWork; // sizeof 0x8

extern s32 omCharModelNoTbl[][6];

MinigameFlow m251_mgFlow = {
    MG_STATE_OPENING, MINIGAME_BATTLE, MG_TIMER_COUNT_DOWN, MG_TIME_DISP_NONE, FALSE, MG_GAUGE_NONE, MG_RESULT_WIN_1, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    -1, -1, 9000, -1, 150
};
s16 m251_cameraMaskTbl[2] = { 1, 2 };
f32 m251_splitX = 160.0f;
f32 m251_splitOfsXTbl[2] = { -80.0f, 80.0f };
s32 m251_flareMdlFileTbl[5] = { 0x0054000B, 0x0054000C, 0x0054000D, 0x0054000E, 0x0054000F };
s32 m251_flareMdlAttrTbl[5] = { 0x6DD, 0xADD, 0xADD, 0xADD, 0xADD };
// Per-camera scissor (x, y, width, height) and viewport (scale x/y, translate
// x/y) settings.
s16 m251_scissorTbl[2][4] = { { 0, 0, 159, 240 }, { 161, 0, 320, 240 } };
s16 m251_viewportTbl[2][4] = { { 640, 480, 320, 480 }, { 640, 480, 960, 480 } };
// Per-player sound effect IDs.
s32 m251_playerSeTbl[2][6] = {
    { 0x49A, 0x49B, 0x49C, 0x49D, 0x49E, 0x4A4 },
    { 0x49F, 0x4A0, 0x4A1, 0x4A2, 0x4A3, 0x4A5 }
};
u16 m251_exitF = 0;
s32 m251_unusedTbl[1] = { 0 }; /* Unreferenced. */
s32 m251_branchMdlFileTbl[3] = { 0x00540005, 0x00540006, 0x00540007 };
u16 m251_arrowXTbl[2] = { 110, 50 };
f32 m251_goalScale = 1.0f;
f32 m251_winZoom = 1.0f;
f32 m251_flareDistTbl[2][5] = { { 100.0f, 3300.0f, 3650.0f, 3800.0f, 3850.0f },
                                         { 200.0f, 4000.0f, 4100.0f, 4300.0f, 4500.0f } };
f32 m251_flareScaleTbl[2][5] = { { 3.2f, 0.6f, 1.2f, 1.0f, 1.0f }, { 5.0f, 0.8f, 2.0f, 3.0f, 1.5f } };
Vec m251_flareBlendTbl[2] = { { 1.0f, 0.99f, 0.9f }, { 0.4f, 0.8f, 0.7f } };

omObjData *m251_startObj BSS;
omObjData *m251_resultObj BSS;
omObjData *m251_stageObj BSS;
omObjData *m251_playerObjTbl[2] BSS;
omObjData *m251_smokeObjTbl[2] BSS;
omObjData *m251_goalEffObjTbl[2] BSS;
u16 m251_startPhase BSS;
u16 m251_resultPhase BSS;
u16 m251_goalF BSS;
u16 m251_timeUpF BSS;
EndOfTheLineResultWork m251_resultWork BSS;
s16 m251_comNum BSS;
s16 m251_comLuckyNo BSS;
u16 m251_goalViewF BSS;
u16 m251_branchRouteTbl[3] BSS;
s16 m251_frameSprAnim BSS;
s16 m251_branchFadeSprAnim BSS;
s16 m251_tunnelFadeSprAnim BSS;
s16 m251_goalSprAnim BSS;
s16 m251_drawSprAnim BSS;
s16 m251_arrowSprAnimTbl[2] BSS;
s16 m251_arrowDimSprAnimTbl[2] BSS;
EndOfTheLineSceneWork m251_sceneWork BSS;
Vec m251_cameraPosTbl[2] BSS;
Vec m251_cameraAtTbl[2] BSS;
Vec m251_cameraUpTbl[2] BSS;
s16 m251_winner BSS;

/* Fields of m251_resultWork and m251_sceneWork (aliased in undefined_syms.txt). */
extern u16 m251_noWinnerF;
extern u16 m251_goalTbl[2];
extern s16 m251_dividerSprAnim;
extern s16 m251_sceneReqTbl[3];

void m251_MainObjInit(omObjData *obj);
void m251_SceneSet(omObjData *arg0, omObjData *arg1, s32 arg2);
void m251_SmokeStart(u16 playerIdx);
void m251_SmokeObjMain(omObjData *obj);
void m251_PlayerIntroObjMain(omObjData *obj);
void m251_PlayerDropObjMain(omObjData *obj);
void m251_PlayerRideObjMain(omObjData *obj);
void m251_PlayerBranchObjMain(omObjData *obj);
void m251_PlayerFallObjMain(omObjData *obj);
void m251_PlayerGoalObjMain(omObjData *obj);
void m251_PlayerTurnObjMain(omObjData *obj);
void m251_TunnelFadeStart(omObjData *obj, s32 arg1);
void m251_TunnelFadeKill(EndOfTheLinePlayer *player);
void m251_BranchFadeStart(omObjData *obj, s32 arg1);
void m251_BranchFadeObjMain(omObjData *obj);
void m251_BranchFadeKill(EndOfTheLinePlayer *player);
s16 m251_PlayerComInput(omObjData *obj);
void m251_StartObjMain(omObjData *obj);
void m251_ResultObjMain(omObjData *obj);
void m251_CameraIntroObjMain(omObjData *obj);
void m251_CameraDropObjMain(omObjData *obj);
void m251_CameraZoomObjMain(omObjData *obj);
void m251_CameraRideObjMain(omObjData *obj);
void m251_CameraBranchObjMain(omObjData *obj);
void m251_CameraFallObjMain(omObjData *obj);
void m251_CameraGoalObjMain(omObjData *obj);
void m251_CameraWinObjMain(omObjData *obj);
void m251_CameraDrawObjMain(omObjData *obj);
void m251_FlareUpdate(u16 arg0, omObjData *obj, f32 arg2, f32 arg3, f32 arg4);
void m251_GoalEffStart(omObjData *obj);
void m251_GoalEffObjMain(omObjData *obj);
void m251_OvlReturn(void);
void m251_MainObjMain(omObjData *obj);
void m251_StageObjInit(omObjData *obj);
void m251_SmokeObjCreateAll(void);
void m251_PlayerObjInit(omObjData *obj);
void m251_TunnelFadeObjMain(omObjData *obj);
void m251_CameraViewObjMain(omObjData *obj);
void m251_GoalEffObjCreateAll(void);

void m251_ObjectSetup(void) {
    omObjData *obj;
    s32 i;

    omInitObjMan(30, 0);
    omGameSysInit();
    HuAudCharVoiceInit();
    CamSetupInitMulti(2);
    CamSetupMapCullAddMulti(2);
    for (i = 0; i < 2; i++) {
        m251_cameraAtTbl[i].x = 0.0f;
        m251_cameraAtTbl[i].y = 200.0f;
        m251_cameraAtTbl[i].z = 0.0f;
        m251_cameraPosTbl[i].x = 0.0f;
        m251_cameraPosTbl[i].y = 300.0f;
        m251_cameraPosTbl[i].z = 1000.0f;
        m251_cameraUpTbl[i].x = 0.0f;
        m251_cameraUpTbl[i].y = 0.1f;
        m251_cameraUpTbl[i].z = 0.0f;
        Hu3DCameraPerspectiveSet(i, 60.0f, 80.0f, 20000.0f);
        ScissorSet(i, m251_scissorTbl[i][0], m251_scissorTbl[i][1],
                   m251_scissorTbl[i][2], m251_scissorTbl[i][3]);
        ViewportSet(i, m251_viewportTbl[i][0], m251_viewportTbl[i][1], 511.0f,
                    m251_viewportTbl[i][2], m251_viewportTbl[i][3], 511.0f);
    }
    obj = omAddObj(0x7FDA, 0, 0, -1, m251_CameraViewObjMain);
    obj->work[0] = 2;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(1, 0x40, 0x40, 0x60);
    Hu3DGLightDirSet(1, 3.0f, 89.0f, 80.0f);
    Hu3DGLightStatSet(1, 1, 1);
    Hu3DGLightColorSet(3, 0, 0, 0);
    Hu3DGLightDirSet(3, -115.0f, 6.0f, -33.0f);
    Hu3DGLightStatSet(2, 1, 1);
    omAddObj(0, 0, 0, -1, m251_MainObjInit);
    m251_stageObj = omAddObj(10, 30, 0, -1, m251_StageObjInit);
    omSetStatBit(m251_stageObj, OM_STAT_MODELPAUSE);
    for (i = 0; i < 2; i++) {
        m251_playerObjTbl[i] = obj = omAddObj(20, 6, 12, -1, m251_PlayerObjInit);
        obj->work[0] = i;
    }
    m251_frameSprAnim = HuSprAnimDataRead(0x54001A);
    m251_branchFadeSprAnim = HuSprAnimDataRead(0x540018);
    m251_tunnelFadeSprAnim = HuSprAnimDataRead(0x540019);
    m251_goalSprAnim = HuSprAnimDataRead(0x540013);
    m251_drawSprAnim = HuSprAnimDataRead(0x54001B);
    m251_arrowSprAnimTbl[0] = HuSprAnimDataRead(0x540015);
    m251_arrowSprAnimTbl[1] = HuSprAnimDataRead(0x540014);
    m251_arrowDimSprAnimTbl[0] = HuSprAnimDataRead(0x540017);
    m251_arrowDimSprAnimTbl[1] = HuSprAnimDataRead(0x540016);
    m251_dividerSprAnim = HuSprAnimDataRead(0x38001F);
    m251_SmokeObjCreateAll();
    m251_GoalEffObjCreateAll();
    MgFlowInit(&m251_mgFlow);
}

void m251_MainObjInit(omObjData *obj) {
    m251_resultObj = 0;
    m251_startObj = 0;
    m251_winner = -1;
    m251_timeUpF = 0;
    m251_noWinnerF = 0;
    m251_goalF = 0;
    m251_goalViewF = 0;
    m251_goalTbl[0] = m251_goalTbl[1] = 0;
    m251_comNum = -1;
    m251_comLuckyNo = -1;
    m251_sceneReqTbl[0] = m251_sceneReqTbl[1] = -1;
    obj->func = m251_MainObjMain;
}

void m251_MainObjMain(omObjData *obj) {
    EndOfTheLinePlayer *player;
    EndOfTheLinePlayer *player2;
    s32 count;
    s32 i;

    if (m251_exitF == 0) {
        switch (MgFlowMain()) {
            case 0:
                if (m251_startObj == NULL) {
                    m251_startPhase = 0;
                    m251_startObj = omAddObj(4, 0, 0, -1, m251_StartObjMain);
                    m251_startObj->work[0] = 0;
                    m251_startObj->work[1] = 0;
                }
                break;
            case 2:
                if (m251_goalF == 1) {
                    count = 0;
                    for (i = 0; i < 2; i++) {
                        if (m251_goalTbl[i] == 1) {
                            m251_winner = i;
                            count++;
                        }
                    }
                    if (count == 2) {
                        m251_mgFlow.resultType = MG_RESULT_DRAW;
                        m251_noWinnerF = 1;
                    } else if (m251_timeUpF == 0) {
                        player = OM_GET_DATA_PTR(m251_playerObjTbl[m251_winner ^ 1],
                                                 EndOfTheLinePlayer);
                        if (player->unk18 == 2) {
                            player->unk0C = 0;
                        }
                        if (player->unk86 != -1) {
                            HuAudFXStop(player->unk86);
                            player->unk86 = -1;
                        }
                    }
                    MgFlowStatSet(MG_STATE_FINISH);
                } else if (MgFlowStatTimeGet() == 9000 || m251_timeUpF == 1) {
                    m251_timeUpF = 1;
                    m251_noWinnerF = 1;
                    GMesTimerValueSet(0);
                    player = OM_GET_DATA_PTR(m251_playerObjTbl[0], EndOfTheLinePlayer);
                    player2 = OM_GET_DATA_PTR(m251_playerObjTbl[1], EndOfTheLinePlayer);
                    if (player->unk18 == 1 && player2->unk18 == player->unk18) {
                        m251_mgFlow.resultType = MG_RESULT_DRAW;
                        MgFlowStatSet(MG_STATE_FINISH);
                        m251_mgFlow.finishDelay = 60;
                        m251_resultObj = omAddObj(4, 0, 0, -1, m251_ResultObjMain);
                        m251_resultPhase = 3;
                    }
                }
                break;
            case 1:
            case 3:
            case 4:
                break;
            case 5:
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                m251_exitF = 1;
                break;
        }
    } else if (WipeStatGet() == 0) {
        m251_OvlReturn();
    }

    for (i = 0; i < 2; i++) {
        if (m251_sceneReqTbl[i] < 0) {
            continue;
        }
        player = OM_GET_DATA_PTR(m251_playerObjTbl[i], EndOfTheLinePlayer);
        if ((m251_sceneReqTbl[i] & 0xF) == 4) {
            if (m251_noWinnerF == 0) {
                if (m251_sceneReqTbl[i] & 0x10) {
                    m251_TunnelFadeKill(player);
                }
                if (m251_sceneReqTbl[i] & 0x20) {
                    m251_BranchFadeKill(OM_GET_DATA_PTR(m251_playerObjTbl[i], EndOfTheLinePlayer));
                }
                m251_SceneSet(m251_stageObj, m251_playerObjTbl[i],
                                              m251_sceneReqTbl[i] & 0xF);
                player->unk5C = 7;
                m251_playerObjTbl[i]->func = m251_PlayerGoalObjMain;
                m251_SmokeStart(player->playerIdx);
                player->unk04->work[2] = 0;
                player->unk04->func = m251_CameraGoalObjMain;
            } else {
                if (m251_sceneReqTbl[i] & 0x10) {
                    m251_TunnelFadeKill(OM_GET_DATA_PTR(m251_playerObjTbl[i], EndOfTheLinePlayer));
                }
                if (m251_sceneReqTbl[i] & 0x20) {
                    m251_BranchFadeKill(OM_GET_DATA_PTR(m251_playerObjTbl[i], EndOfTheLinePlayer));
                }
                m251_SceneSet(m251_stageObj, m251_playerObjTbl[i], 6);
                player->unk5C = 7;
                m251_playerObjTbl[i]->func = m251_PlayerGoalObjMain;
                m251_SmokeStart(player->playerIdx);
                player->unk04->work[2] = 0;
                player->unk04->func = m251_CameraDrawObjMain;
            }
            if (m251_resultObj == NULL) {
                if (m251_noWinnerF == 0) {
                    m251_resultPhase = 0;
                } else {
                    m251_resultPhase = 1;
                }
                m251_resultObj = omAddObj(4, 0, 0, -1, m251_ResultObjMain);
            }
        } else {
            if (m251_sceneReqTbl[i] & 0x10) {
                m251_TunnelFadeKill(OM_GET_DATA_PTR(m251_playerObjTbl[i], EndOfTheLinePlayer));
            }
            if (m251_sceneReqTbl[i] & 0x20) {
                m251_BranchFadeKill(OM_GET_DATA_PTR(m251_playerObjTbl[i], EndOfTheLinePlayer));
            }
            m251_SceneSet(m251_stageObj, m251_playerObjTbl[i],
                                          m251_sceneReqTbl[i] & 0xF);
            if (m251_sceneReqTbl[i] & 0x40) {
                player->pos2.y = 200.0f;
            }
            if (m251_sceneReqTbl[i] & 0x80) {
                player->unk04->func = player->unk08;
            }
            if ((m251_sceneReqTbl[i] & 0xF) == 3) {
                omVibrate(player->gwPlayerIdx, 20, 0, 20);
            }
        }
        m251_sceneReqTbl[i] = -1;
    }
}

void m251_StageObjInit(omObjData *obj) {
    EndOfTheLineStage *data;
    s32 i;
    s32 j;

    data = obj->data = HuMemAllocTag(sizeof(EndOfTheLineStage), TAG_OVERLAY);
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            obj->model[0] = Hu3DModelRead(0x540002, 0x6DD);
            obj->model[4] = Hu3DModelRead(0x540003, 0x6DD);
            obj->model[12] = Hu3DModelRead(0x540004, 0x6DD);
            obj->model[14] = Hu3DModelRead(0x540008, 0x6DD);
            obj->model[16] = Hu3DModelRead(0x540009, 0x6DD);
            obj->model[18] = Hu3DModelRead(0x54000A, 0x6DD);
            for (j = 0; j < 5; j++) {
                obj->model[20 + j * 2] = Hu3DModelRead(m251_flareMdlFileTbl[j], m251_flareMdlAttrTbl[j]);
            }
        } else {
            obj->model[2] = Hu3DModelLink(obj->model[0]);
            obj->model[5] = Hu3DModelLink(obj->model[4]);
            obj->model[13] = Hu3DModelLink(obj->model[12]);
            obj->model[15] = Hu3DModelLink(obj->model[14]);
            obj->model[17] = Hu3DModelLink(obj->model[16]);
            obj->model[19] = Hu3DModelLink(obj->model[18]);
            for (j = 0; j < 5; j++) {
                obj->model[21 + j * 2] = Hu3DModelLink(obj->model[20 + j * 2]);
            }
        }
        Hu3DModelCameraSet(obj->model[i * 2], m251_cameraMaskTbl[i]);
        Hu3DModelCameraSet(obj->model[4 + i], m251_cameraMaskTbl[i]);
        Hu3DModelCameraSet(obj->model[12 + i], m251_cameraMaskTbl[i]);
        Hu3DModelCameraSet(obj->model[14 + i], m251_cameraMaskTbl[i]);
        Hu3DModelCameraSet(obj->model[16 + i], m251_cameraMaskTbl[i]);
        Hu3DModelCameraSet(obj->model[18 + i], m251_cameraMaskTbl[i]);
        Hu3DModelObjAttrSet(obj->model[18 + i], 0x70000000, 0x70000000);
        for (j = 0; j < 5; j++) {
            Hu3DModelObjAttrSet(obj->model[20 + j * 2 + i], 0x70000000, 0x70000000);
            Hu3DModelCameraSet(obj->model[20 + j * 2 + i], m251_cameraMaskTbl[i]);
        }
        for (j = 0; j < 1; j++) {
            obj->model[i * 2 + 1 + j] = Hu3DModelLink(obj->model[0]);
            Hu3DModelCameraSet(obj->model[i * 2 + 1 + j], m251_cameraMaskTbl[i]);
        }
        for (j = 0; j < 3; j++) {
            if (i == 0) {
                obj->model[6 + j] = Hu3DModelRead(m251_branchMdlFileTbl[j], 0x6DD);
            } else {
                obj->model[9 + j] = Hu3DModelLink(obj->model[6 + j]);
            }
            Hu3DModelCameraSet(obj->model[6 + i * 3 + j], m251_cameraMaskTbl[i]);
        }
        data->esprites[i] = espEntry(m251_frameSprAnim, 0, 0);
        data->esprites[i + 2] = espEntry(m251_tunnelFadeSprAnim, 0, 0);
        data->esprites[i + 4] = espEntry(m251_branchFadeSprAnim, 0, 0);
        data->esprites[i + 6] = espEntry(m251_goalSprAnim, 0, 0);
        data->esprites[i + 8] = espEntry(m251_drawSprAnim, 0, 0);
        espPosSet(data->esprites[i], i * 160 + 80, 120);
        espPosSet(data->esprites[i + 2], i * 160 + 80, 120);
        espPosSet(data->esprites[i + 4], i * 160 + 80, 120);
        espPosSet(data->esprites[i + 8], i * 160 + 80, 120);
        espDispOff(data->esprites[i]);
        espDispOff(data->esprites[i + 2]);
        espDispOff(data->esprites[i + 4]);
        espDispOff(data->esprites[i + 6]);
        espDispOff(data->esprites[i + 8]);
        espAttrSet(data->esprites[i], HUSPR_ATTR_BG);
        espAttrSet(data->esprites[i + 6], HUSPR_ATTR_BG | HUSPR_ATTR_FILTER_BILERP);
        espAttrSet(data->esprites[i + 8], HUSPR_ATTR_BG | HUSPR_ATTR_FILTER_BILERP);
        espPriSet(data->esprites[i + 2], 0x80C8);
        espPriSet(data->esprites[i + 4], 0x8190);
    }
    data->esprites[10] = espEntry(m251_dividerSprAnim, 0, 0);
    espPosSet(data->esprites[10], 160, 120);
    espPriSet(data->esprites[10], 0x8064);
    for (i = 0; i < 3; i++) {
        m251_branchRouteTbl[i] = rand8() < 0x80;
    }
    obj->work[0] = 0;
    obj->func = NULL;
}

void m251_StageGoalObjMain(omObjData *obj) {
    EndOfTheLineStage *data = OM_GET_DATA_PTR(obj, EndOfTheLineStage);
    EndOfTheLinePlayer *player;
    omObjData *playerObj;
    f32 offset;
    s32 front;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            data->unk18[i][j] += 37.037037f;
            Hu3DModelPosSet(obj->model[i * 2 + j], 0.0f, 0.0f, data->unk18[i][j]);
            if (data->unk18[i][j] >= 3300.0f) {
                data->unk18[i][j] -= 6600.0f;
            }
        }
        if (obj->work[0] == 1) {
            if (data->unk18[0][0] > data->unk18[0][1]) {
                front = 1;
            } else {
                front = 0;
            }
            m251_SceneSet(obj, m251_playerObjTbl[0], 1);
            m251_SceneSet(obj, m251_playerObjTbl[1], 1);
            offset = data->unk18[0][front];
            for (j = 0; j < 2; j++) {
                playerObj = m251_playerObjTbl[j];
                player = OM_GET_DATA_PTR(playerObj, EndOfTheLinePlayer);
                playerObj->trans.z -= offset;
                player->pos.z -= offset;
                Hu3DModelPosSet(playerObj->model[1], player->pos.x, player->pos.y, player->pos.z);
                Hu3DModelRotSet(playerObj->model[1], player->rot.x, player->rot.y, player->rot.z);
                Hu3DModelPosSet(playerObj->model[2], player->pos.x - sindf(player->rot.y) * 20.0f,
                                player->pos.y + 100.0f, player->pos.z - cosdf(player->rot.y) * 20.0f);
                Hu3DModelRotSet(playerObj->model[2], 0.0f, player->rot.y, 0.0f);
                Hu3DModelScaleSet(playerObj->model[4], 1.0f, 1.0f, 1.0f);
                Hu3DModelPosSet(playerObj->model[4], player->pos.x - sindf(player->rot.y) * 20.0f,
                                player->pos.y + 100.0f, player->pos.z - cosdf(player->rot.y) * 20.0f);
            }
            obj->func = NULL;
            return;
        }
    }
}

void m251_SceneSet(omObjData *arg0, omObjData *arg1, s32 arg2) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(arg1, EndOfTheLinePlayer);
    u16 idx = player->playerIdx;
    EndOfTheLineStage *data = OM_GET_DATA_PTR(arg0, EndOfTheLineStage);
    s32 i;

    Hu3DModelAttrSet(arg0->model[idx * 2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg0->model[idx * 2 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg0->model[4 + idx], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg0->model[12 + idx], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg0->model[14 + idx], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg0->model[16 + idx], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg0->model[18 + idx], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    for (i = 0; i < 5; i++) {
        Hu3DModelAttrSet(arg0->model[20 + i * 2 + idx], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    Hu3DModelAttrSet(arg0->model[6 + idx * 3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg0->model[6 + idx * 3 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg0->model[6 + idx * 3 + 2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg1->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg1->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg1->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg1->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg1->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg1->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    espDispOff(data->esprites[idx]);
    espDispOff(player->esprites[0]);
    espDispOff(player->esprites[1]);
    espDispOff(player->esprites2[0]);
    espDispOff(player->esprites2[1]);
    Hu3DGLightDirSet(1, 3.0f, 89.0f, 80.0f);
    player->unk18 = arg2;
    player->unk88 = 0x48;
    switch ((s16)arg2) {
        case 0:
            Hu3DGLightDirSet(1, 44.0f, 82.0f, -74.0f);
            Hu3DModelAttrSet(arg0->model[16 + idx], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg1->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg1->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg1->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            omSetTra(arg1, 0.0f, 0.0f, 2000.0f);
            omSetRot(arg1, 0.0f, 180.0f, 0.0f);
            player->pos.x = 0.0f;
            player->pos.y = 0.0f;
            player->pos.z = arg1->trans.z + 237.5f + 105.0f + 50.0f;
            player->rot.x = 0.0f;
            player->rot.y = 180.0f;
            player->rot.z = 0.0f;
            Hu3DModelPosSet(arg1->model[1], player->pos.x, player->pos.y, player->pos.z);
            Hu3DModelRotSet(arg1->model[1], player->rot.x, player->rot.y, player->rot.z);
            player->pos2.x = 0.0f;
            player->pos2.y = 0.0f;
            player->pos2.z = 0.0f;
            player->rot2.x = 0.0f;
            player->rot2.y = 180.0f;
            player->rot2.z = 0.0f;
            Hu3DModelPosSet(arg1->model[2], player->pos2.x, player->pos2.y, player->pos2.z);
            Hu3DModelRotSet(arg1->model[2], player->rot2.x, player->rot2.y, player->rot2.z);
            espDispOn(data->esprites[idx]);
            for (i = 0; i < 5; i++) {
                Hu3DModelAttrSet(arg0->model[20 + i * 2 + idx], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            Hu3DModelAttrSet(arg0->model[18 + idx], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelPosSet(arg0->model[18 + idx], -1000.0f, 4000.0f, 0.0f);
            Hu3DModelScaleSet(arg0->model[18 + idx], 4.5f, 4.5f, 4.5f);
            break;
        case 1:
            Hu3DModelAttrSet(arg0->model[idx * 2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg0->model[4 + idx], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg0->model[6 + idx * 3 + player->unk16], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelPosSet(arg0->model[idx * 2], 0.0f, 0.0f, 0.0f);
            Hu3DModelPosSet(arg0->model[4 + idx], 0.0f, 0.0f, -3300.0f);
            Hu3DModelPosSet(arg0->model[6 + idx * 3 + player->unk16], 0.0f, 0.0f, -3150.0f);
            Hu3DModelAttrSet(arg1->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg1->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg1->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            omSetTra(arg1, 0.0f, 0.0f, 0.0f);
            omSetRot(arg1, 0.0f, 180.0f, 0.0f);
            player->pos.x = 0.0f;
            player->pos.y = 0.0f;
            player->pos.z = 292.5f;
            player->rot.x = 0.0f;
            player->rot.y = 180.0f;
            player->rot.z = 0.0f;
            player->pos2.y = 0.0f;
            Hu3DModelPosSet(arg1->model[1], player->pos.x, player->pos.y, player->pos.z);
            Hu3DModelRotSet(arg1->model[1], player->rot.x, player->rot.y, player->rot.z);
            Hu3DModelPosSet(arg1->model[2], player->pos.x - sindf(player->rot.y) * 20.0f, player->pos2.y + 100.0f,
                            player->pos.z - cosdf(player->rot.y) * 20.0f);
            Hu3DModelRotSet(arg1->model[2], 0.0f, 180.0f, 0.0f);
            Hu3DModelPosSet(arg1->model[4], player->pos.x - sindf(player->rot.y) * 20.0f, player->pos2.y + 100.0f,
                            player->pos.z - cosdf(player->rot.y) * 20.0f);
            Hu3DModelAttrSet(arg1->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            espDispOn(data->esprites[idx]);
            espPosSet(data->esprites[player->playerIdx],
                      m251_splitOfsXTbl[player->playerIdx] + m251_splitX, 0x78);
            if (m251_timeUpF != 0) {
                player->unk0C = 0.0f;
                player->unk88 = 0;
            } else if (m251_goalF == 0) {
                player->unk0C = 40.0f;
                player->unk88 = 0x48;
            } else {
                player->unk0C = 0.0f;
                player->unk88 = 0;
            }
            player->unk68 = 0.0f;
            if (player->unk86 != -1) {
                msmSeSetFxMix(player->unk86, 22);
            }
            break;
        case 2:
            Hu3DModelAttrSet(arg0->model[14 + idx], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelPosSet(arg0->model[14 + idx], 0.0f, 0.0f, -1650.0f);
            omSetTra(arg1, 0.0f, 0.0f, 0.0f);
            omSetRot(arg1, 0.0f, 180.0f, 0.0f);
            Hu3DModelPosSet(arg1->model[2], arg1->trans.x, arg1->trans.y + 100.0f, arg1->trans.z + 20.0f);
            Hu3DModelRotSet(arg1->model[2], 0.0f, 180.0f, 0.0f);
            if (m251_goalF == 0) {
                player->unk0C = 40.0f;
                player->unk88 = 0x48;
            } else {
                player->unk0C = 0.0f;
                player->unk88 = 0;
            }
            break;
        case 3:
            player->unk88 = 0;
            player->unk54 = 345.0f;
            Hu3DModelAttrSet(arg1->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg1->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg1->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            for (i = 0; i < 5; i++) {
                Hu3DModelAttrSet(arg0->model[20 + i * 2 + idx], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            Hu3DModelAttrSet(arg0->model[12 + idx], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelPosSet(arg0->model[12 + idx], 0.0f, 0.0f, 0.0f);
            Hu3DModelAttrSet(arg0->model[18 + idx], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelPosSet(arg0->model[18 + idx], 1000.0f, 2500.0f, 900.0f);
            Hu3DModelScaleSet(arg0->model[18 + idx], 5.0f, 5.0f, 5.0f);
            omSetTra(arg1, -500.0f, -sindf(player->unk54) * 447.5f, -500.0f);
            omSetRot(arg1, player->unk54, 0.0f, 0.0f);
            player->pos.x = -500.0f;
            player->pos.y = -sindf(player->unk54) * 105.0f;
            player->pos.z = -792.5f;
            player->rot.x = player->unk54;
            player->rot.y = 0.0f;
            player->rot.z = 0.0f;
            Hu3DModelPosSet(arg1->model[1], player->pos.x, player->pos.y, player->pos.z);
            Hu3DModelRotSet(arg1->model[1], player->rot.x, player->rot.y, player->rot.z);
            Hu3DModelPosSet(arg1->model[2], player->pos.x - sindf(player->rot.y) * 20.0f,
                            -sindf(player->unk54) * 85.0f + 100.0f, player->pos.z - cosdf(player->rot.y) * 20.0f);
            Hu3DModelRotSet(arg1->model[2], 0.0f, 180.0f, 0.0f);
            espDispOn(data->esprites[idx]);
            espPosSet(data->esprites[player->playerIdx],
                      m251_splitOfsXTbl[player->playerIdx] + m251_splitX, 0x78);
            player->unk0C = 48.0f;
            break;
        case 4:
            Hu3DModelAttrSet(arg1->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg1->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg1->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            omSetTra(arg1, 0.0f, 0.0f, 950.0f);
            omSetRot(arg1, 0.0f, 180.0f, 0.0f);
            player->pos.x = 0.0f;
            player->pos.y = 0.0f;
            player->pos.z = 1242.5f;
            player->rot.x = 0.0f;
            player->rot.y = 180.0f;
            player->rot.z = 0.0f;
            Hu3DModelPosSet(arg1->model[1], player->pos.x, player->pos.y, player->pos.z);
            Hu3DModelRotSet(arg1->model[1], player->rot.x, player->rot.y, player->rot.z);
            Hu3DModelPosSet(arg1->model[2], player->pos.x - sindf(player->rot.y) * 20.0f, player->pos.y + 100.0f,
                            player->pos.z - cosdf(player->rot.y) * 20.0f);
            Hu3DModelRotSet(arg1->model[2], 0.0f, 180.0f, 0.0f);
            Hu3DModelPosSet(arg1->model[4], player->pos.x - sindf(player->rot.y) * 20.0f, player->pos.y + 100.0f,
                            player->pos.z - cosdf(player->rot.y) * 20.0f);
            Hu3DModelAttrSet(arg1->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            espDispOn(data->esprites[idx + 6]);
            if (idx == 0) {
                espPosSet(data->esprites[6], 0, 0x78);
            } else {
                espPosSet(data->esprites[idx + 6], 320, 0x78);
            }
            player->unk88 = 0x48;
            if (player->unk86 != -1) {
                msmSeSetFxMix(player->unk86, 22);
            }
            break;
        case 5:
            Hu3DModelAttrSet(arg0->model[idx * 2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg0->model[idx * 2 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            data->unk18[idx][0] = 1650.0f;
            data->unk18[idx][1] = -1650.0f;
            Hu3DModelPosSet(arg0->model[idx * 2], 0.0f, 0.0f, data->unk18[idx][0]);
            Hu3DModelPosSet(arg0->model[idx * 2 + 1], 0.0f, 0.0f, data->unk18[idx][1]);
            Hu3DModelAttrSet(arg1->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg1->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg1->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            omSetTra(arg1, 0.0f, 0.0f, 0.0f);
            omSetRot(arg1, 0.0f, 180.0f, 0.0f);
            player->pos.x = 0.0f;
            player->pos.y = 0.0f;
            player->pos.z = 292.5f;
            player->rot.x = 0.0f;
            player->rot.y = 180.0f;
            player->rot.z = 0.0f;
            Hu3DModelPosSet(arg1->model[1], player->pos.x, player->pos.y, player->pos.z);
            Hu3DModelRotSet(arg1->model[1], player->rot.x, player->rot.y, player->rot.z);
            player->pos2.x = player->pos.x - sindf(player->rot.y) * 20.0f;
            player->pos2.y = player->pos.y + 700.0f + 100.0f;
            player->pos2.z = player->pos.z - cosdf(player->rot.y) * 20.0f;
            player->rot2.x = 0.0f;
            player->rot2.y = 180.0f;
            player->rot2.z = 0.0f;
            Hu3DModelPosSet(arg1->model[2], player->pos2.x, player->pos2.y, player->pos2.z);
            Hu3DModelRotSet(arg1->model[2], player->rot2.x, player->rot2.y, player->rot2.z);
            Hu3DModelAttrSet(arg1->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelPosSet(arg1->model[4], player->pos2.x, 100.0f, player->pos2.z);
            player->unk6C = 0.1f;
            espDispOn(data->esprites[idx]);
            m251_stageObj->func = m251_StageGoalObjMain;
            break;
        case 6:
            Hu3DModelAttrSet(arg1->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg1->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg1->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            omSetTra(arg1, 0.0f, 0.0f, 950.0f);
            omSetRot(arg1, 0.0f, 180.0f, 0.0f);
            player->pos.x = 0.0f;
            player->pos.y = 0.0f;
            player->pos.z = 1242.5f;
            player->rot.x = 0.0f;
            player->rot.y = 180.0f;
            player->rot.z = 0.0f;
            Hu3DModelPosSet(arg1->model[1], player->pos.x, player->pos.y, player->pos.z);
            Hu3DModelRotSet(arg1->model[1], player->rot.x, player->rot.y, player->rot.z);
            Hu3DModelPosSet(arg1->model[2], player->pos.x - sindf(player->rot.y) * 20.0f, player->pos.y + 100.0f,
                            player->pos.z - cosdf(player->rot.y) * 20.0f);
            Hu3DModelRotSet(arg1->model[2], 0.0f, 180.0f, 0.0f);
            Hu3DModelPosSet(arg1->model[4], player->pos.x - sindf(player->rot.y) * 20.0f, player->pos.y + 100.0f,
                            player->pos.z - cosdf(player->rot.y) * 20.0f);
            Hu3DModelAttrSet(arg1->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            espDispOn(data->esprites[idx + 8]);
            if (idx == 0) {
                espPosSet(data->esprites[6], 0, 0x78);
            } else {
                espPosSet(data->esprites[idx + 6], 320, 0x78);
            }
            break;
    }
    if (player->unk86 != -1) {
        HuAudFXVolSet(player->unk86, player->unk88);
    }
}

void m251_SmokeObjCreateAll(void) {
    omObjData *obj;
    EndOfTheLineSmokeWork *work;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        m251_smokeObjTbl[i] = obj = omAddObj(0x28, 3, 0, -1, NULL);
        omSetStatBit(obj, OM_STAT_MODELPAUSE);
        work = obj->data = HuMemAllocTag(sizeof(EndOfTheLineSmokeWork), TAG_OVERLAY);
        for (j = 0; j < 3; j++) {
            work->timers[j] = 0;
            obj->model[j] = Hu3DModelRead(0x540010, 0xA8D);
        }
        work->cooldown = 0;
    }
}

void m251_SmokeStart(u16 playerIdx) {
    EndOfTheLineSmokeWork *work = OM_GET_DATA_PTR(m251_smokeObjTbl[playerIdx], EndOfTheLineSmokeWork);
    s32 i;

    for (i = 0; i < 3; i++) {
        Hu3DModelCameraSet(m251_smokeObjTbl[playerIdx]->model[i], m251_cameraMaskTbl[playerIdx]);
    }
    work->target = m251_playerObjTbl[playerIdx];
    m251_smokeObjTbl[playerIdx]->func = m251_SmokeObjMain;
}

void m251_SmokeObjMain(omObjData *obj) {
    EndOfTheLineSmokeWork *work = OM_GET_DATA_PTR(obj, EndOfTheLineSmokeWork);
    s32 i;

    if (work->cooldown == 0) {
        for (i = 0; i < 3; i++) {
            if (work->timers[i] == 0) {
                break;
            }
        }
        if (i != 3) {
            Hu3DModelAttrSet(obj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DMotionTimeSet(obj->model[i], 0.0f);
            Hu3DModelScaleSet(obj->model[i], 2.0f, 2.0f, 2.0f);
            work->pos[i].x = work->target->trans.x;
            work->pos[i].y = work->target->trans.y + 340.0f;
            work->pos[i].z = work->target->trans.z - 70.0f;
            work->timers[i] = 15;
            work->cooldown = 8;
            work->velY[i] = 13.0f;
        }
    } else {
        work->cooldown--;
    }
    for (i = 0; i < 3; i++) {
        if (work->timers[i] != 0) {
            Hu3DModelPosSet(obj->model[i], work->pos[i].x, work->pos[i].y, work->pos[i].z);
            work->pos[i].y += work->velY[i];
            work->velY[i] *= 0.97f;
            if (--work->timers[i] == 0) {
                Hu3DModelAttrSet(obj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
        }
    }
}

void m251_PlayerObjInit(omObjData *obj) {
    EndOfTheLinePlayer *player;
    s32 i;
    s8 chr;

    player = obj->data = HuMemAllocTag(sizeof(EndOfTheLinePlayer), TAG_OVERLAY);
    player->playerIdx = obj->work[0];
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == player->playerIdx) {
            player->gwPlayerIdx = i;
            if (GwPlayer[i].stat & 1) {
                m251_comNum++;
            }
            break;
        }
    }
    if (m251_comNum == 1) {
        m251_comLuckyNo = rand8() & 1;
    }
    obj->model[0] = Hu3DModelRead(0x540000, 0xAD9);
    obj->model[1] = Hu3DModelRead(0x540001, 0xAD9);
    obj->model[5] = Hu3DModelRead(0x540011, 0xADD);
    obj->model[3] = Hu3DModelRead(0x82, 0xA8D);
    obj->model[4] = Hu3DModelRead3(9, 0xA8D);
    Hu3DModelCameraSet(obj->model[0], m251_cameraMaskTbl[player->playerIdx]);
    Hu3DModelCameraSet(obj->model[1], m251_cameraMaskTbl[player->playerIdx]);
    Hu3DModelCameraSet(obj->model[3], m251_cameraMaskTbl[player->playerIdx]);
    Hu3DModelCameraSet(obj->model[4], m251_cameraMaskTbl[player->playerIdx]);
    Hu3DModelCameraSet(obj->model[5], m251_cameraMaskTbl[player->playerIdx]);
    Hu3DLLightCreate(obj->model[5], 1);
    Hu3DLLightColorSet(obj->model[5], 0xFF, 0xFF, 0xFF);
    Hu3DLLightDirSet(obj->model[5], 102.0f, 40.0f, 48.0f);
    chr = GwPlayer[player->gwPlayerIdx].chr;
    obj->model[2] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][1], 0x20AD9);
    Hu3DModelCameraSet(obj->model[2], m251_cameraMaskTbl[player->playerIdx]);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 1));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 0x36));
    omObjMotionRead(obj, 6, CharMotionDataNumGet(chr, 0x10));
    omObjMotionRead(obj, 5, CharMotionDataNumGet(chr, 0x11));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chr, 0x1A));
    omObjMotionRead(obj, 7, CharMotionDataNumGet(chr, 0x6C));
    omObjMotionRead(obj, 8, CharMotionDataNumGet(chr, 0x7A));
    omObjMotionRead(obj, 9, CharMotionDataNumGet(chr, 0x2C));
    omObjMotionRead(obj, 10, CharMotionDataNumGet(chr, 0x2E));
    omObjMotionRead(obj, 11, CharMotionDataNumGet(chr, 0x1F));
    Hu3DMotionModelSet(obj->model[2], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[2], 2, 2);
    Hu3DMotionAttrSet(obj->model[0], 2, 2);
    player->unk04 = omAddObj(0x32, 0, 0, -1, m251_CameraIntroObjMain);
    player->unk04->data = HuMemAllocTag(sizeof(EndOfTheLineCameraWork), TAG_OVERLAY);
    player->unk04->work[0] = (u32)obj;
    player->unk04->work[1] = 1;
    player->unk16 = 0;
    player->unk10 = 0;
    player->unk14 = 0;
    player->obj = NULL;
    player->unk0C = 40.0f;
    player->unk1A = 4;
    player->unk1C = 0;
    player->unk78 = 15;
    player->unk8A = 20;
    player->unk8C = 0;
    player->unk86 = -1;
    player->esprites[0] = espEntry(m251_arrowSprAnimTbl[0], 0, 0);
    player->esprites[1] = espEntry(m251_arrowSprAnimTbl[1], 0, 0);
    player->esprites2[0] = espEntry(m251_arrowDimSprAnimTbl[0], 0, 0);
    player->esprites2[1] = espEntry(m251_arrowDimSprAnimTbl[1], 0, 0);
    espTPLvlSet(player->esprites[0], 0xDC);
    espTPLvlSet(player->esprites[1], 0xDC);
    espTPLvlSet(player->esprites2[0], 0xDC);
    espTPLvlSet(player->esprites2[1], 0xDC);
    espDispOff(player->esprites[0]);
    espDispOff(player->esprites[1]);
    espDispOff(player->esprites2[0]);
    espDispOff(player->esprites2[1]);
    for (i = 0; i < 3; i++) {
        player->unk7A[i] = -1;
    }
    player->unk80 = 0;
    player->unk82 = 0;
    m251_SceneSet(m251_stageObj, obj, 0);
    player->unk70 = 0;
    player->unk8C = 3;
    obj->func = m251_PlayerIntroObjMain;
}

void m251_PlayerIntroObjMain(omObjData *obj) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);
    f32 dx;
    f32 dz;
    s32 i;

    if (player->pos2.y > 600.0f) {
        for (i = 0; i < 5; i++) {
            Hu3DModelAttrSet(m251_stageObj->model[20 + i * 2 + player->playerIdx], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
    } else {
        for (i = 0; i < 5; i++) {
            Hu3DModelAttrSet(m251_stageObj->model[20 + i * 2 + player->playerIdx], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
    }
    if (player->unk8A == 0) {
        HuAudFXPlay(m251_playerSeTbl[player->playerIdx][3]);
        player->unk8A = 30;
    } else {
        player->unk8A--;
    }
    if (player->unk78 != 0) {
        player->unk78--;
    } else if (player->rot2.y > 0.0f) {
        if (player->unk1A != 5 && player->unk70 == 0) {
            Hu3DMotionModelSet(obj->model[2], obj->motion[1]);
            Hu3DMotionAttrSet(obj->model[2], 2, 2);
            Hu3DMotionSpeedSet(obj->model[2], 2.0f);
            player->unk1A = 5;
        }
        player->rot2.y -= 20.0f;
        if (player->rot2.y < 0.0f) {
            player->rot2.y = 0.0f;
        }
    } else if (player->rot2.y == 0.0f) {
        if (player->unk1A != 3 && player->unk70 == 0) {
            Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[8]].motId, 0, 6, 2);
            Hu3DMotionSpeedSet(obj->model[2], 1.0f);
            player->unk1A = 3;
        }
    }
    if (obj->trans.z < 297.0f && player->unk70 == 0) {
        HuAudFXPlay(m251_playerSeTbl[player->playerIdx][4]);
        player->unk8E = PlayerFXPlay(0x286, player->gwPlayerIdx);
        player->unk70 = 1;
        player->unk74 = 80.0f;
        player->unk8A = 10000;
        Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[4]].motId, 0, 6, 2);
        Hu3DModelAttrSet(obj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelScaleSet(obj->model[5], 1.8f, 1.8f, 1.8f);
        player->unk1E = 7;
    }
    if (player->unk70 == 1) {
        if (player->unk8C == 0) {
            msmSeSetFxMix(player->unk8E, 0x40);
        } else {
            player->unk8C--;
        }
    }
    if (obj->trans.z > -100.0f) {
        dz = cosdf(obj->rot.y) * (player->unk0C / 1.08f);
        dx = sindf(obj->rot.y) * (player->unk0C / 1.08f);
        obj->trans.x += dx;
        obj->trans.z += dz;
        dz = cosdf(player->rot.y) * (player->unk0C / 1.08f);
        dx = sindf(player->rot.y) * (player->unk0C / 1.08f);
        player->pos.x += dx;
        player->pos.z += dz;
        Hu3DModelPosSet(obj->model[1], player->pos.x, player->pos.y, player->pos.z);
        Hu3DModelRotSet(obj->model[1], player->rot.x, player->rot.y, player->rot.z);
    }
    if (player->unk70 == 1) {
        m251_FlareUpdate(0, obj, -1000.0f, 4000.0f, 0.0f);
        player->pos2.y += player->unk74;
        player->unk74 *= 0.98f;
        if (player->unk74 < 60.0f) {
            player->unk74 = 60.0f;
        }
        if (player->pos2.y > 4000.0f) {
            m251_sceneReqTbl[player->playerIdx] = 0x85;
            player->unk74 = -6.0f;
            player->unk5C = 0;
            Hu3DMotionModelSet(obj->model[2], obj->motion[5]);
            obj->func = m251_PlayerDropObjMain;
            player->unk08 = m251_CameraDropObjMain;
        }
        if (player->unk1E != 0) {
            Hu3DModelRotSet(obj->model[5], 0.0f, 0.0f, (rand8() / 256.0f) * 360.0f);
            if (--player->unk1E == 0) {
                Hu3DModelAttrSet(obj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
        }
    }
    Hu3DModelPosSet(obj->model[5], player->pos2.x, player->pos2.y + 50.0f, player->pos2.z + 100.0f);
    Hu3DModelPosSet(obj->model[2], player->pos2.x, player->pos2.y, player->pos2.z);
    Hu3DModelRotSet(obj->model[2], player->rot2.x, player->rot2.y, player->rot2.z);
}

void m251_PlayerDropObjMain(omObjData *obj) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);
    EndOfTheLineCameraWork *sub;
    f32 scale;

    switch (player->unk5C) {
        case 0:
            player->pos2.y += player->unk74;
            player->unk74 *= 1.15f;
            scale = 1.0f - player->pos2.y / 1000.0f;
            if (scale < 0.0f) {
                scale = 0.0f;
            }
            if (scale > 1.0f) {
                scale = 1.0f;
            }
            player->unk6C = scale;
            if (player->pos2.y < 100.0f) {
                player->pos2.y = 100.0f;
                player->unk74 = 40.0f;
                player->unk5C = 1;
                player->unk6C = 1.0f;
                Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelPosSet(obj->model[3], player->pos2.x, player->pos2.y, player->pos2.z);
                Hu3DMotionTimeSet(obj->model[3], 0.0f);
                m251_startObj->work[0] = 1;
                if (player->playerIdx == 0) {
                    HuAudSeqPlay(0x34);
                }
            }
            Hu3DModelPosSet(obj->model[2], player->pos2.x, player->pos2.y, player->pos2.z);
            Hu3DModelScaleSet(obj->model[4], player->unk6C, player->unk6C, player->unk6C);
            Hu3DModelPosSet(obj->model[4], player->pos2.x, 100.0f, player->pos2.z);
            break;
        case 1:
            player->pos2.y += player->unk74;
            player->unk74 *= 0.5f;
            if (player->unk74 < 1.0f) {
                player->unk74 = -1.0f;
                player->unk5C = 2;
            }
            Hu3DModelPosSet(obj->model[2], player->pos2.x, player->pos2.y, player->pos2.z);
            break;
        case 2:
            player->pos2.y += player->unk74;
            player->unk74 += player->unk74;
            if (player->pos2.y < 100.0f) {
                player->pos2.y = 100.0f;
                Hu3DMotionModelSet(obj->model[2], obj->motion[6]);
                player->unk5C = 3;
                player->unk78 = 22;
            }
            Hu3DModelPosSet(obj->model[2], player->pos2.x, player->pos2.y, player->pos2.z);
            break;
        case 3:
            if (player->unk78 == 0) {
                player->unk78 = 30;
                Hu3DMotionSpeedSet(obj->model[2], 2.0f);
                Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[7]].motId, 0, 6, 0);
                player->unk5C = 4;
            } else {
                player->unk78--;
            }
            break;
        case 4:
            if (player->unk78 == 0) {
                player->unk78 = 20;
                Hu3DMotionSpeedSet(obj->model[2], 1.0f);
                Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[8]].motId, 0, 6, 0);
                player->unk5C = 5;
            } else {
                player->unk78--;
            }
            break;
        case 5:
            if (player->unk78 == 0) {
                Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[9]].motId, 0, 6, 2);
                player->unk1A = 0;
                sub = OM_GET_DATA_PTR(player->unk04, EndOfTheLineCameraWork);
                sub->unk10 = 20;
                sub->unk00 = 700.0f;
                sub->unk04 = 600.0f;
                sub->unk08 = -200.0f / sub->unk10;
                sub->unk0C = 400.0f / sub->unk10;
                player->unk04->func = m251_CameraZoomObjMain;
                player->unk5C = 6;
            } else {
                player->unk78--;
            }
            break;
    }
}

void m251_PlayerRideObjMain(omObjData *obj) {
    f32 limits[2];
    EndOfTheLinePlayer *player;
    s8 stick;
    f32 dx;
    f32 dz;
    f32 scale;
    f32 speed;
    f32 vol;
    f32 pitch;

    limits[0] = 157.0f;
    limits[1] = 203.0f;
    player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);
    if (m251_timeUpF == 1 && player->unk1A != 2) {
        player->unk0C *= 0.7f;
        if (player->unk0C < 2.0f) {
            player->unk0C = 0.0f;
            if (player->unk86 != -1) {
                HuAudFXStop(player->unk86);
                player->unk86 = -1;
            }
            obj->func = NULL;
        }
        if (player->unk86 != -1) {
            speed = player->unk0C;
            if (speed < 8.0f) {
                vol = (speed - 1.0f) * (36.0f / 7.0f) + 36.0f;
                pitch = (speed - 1.0f) * (300.0f / 7.0f) + 300.0f;
                HuAudFXVolSet(player->unk86, vol);
                HuAudFXPitchSet(player->unk86, (s16)pitch);
            }
        }
    } else if (m251_goalF == 1) {
        player->unk0C = 0.0f;
        if (player->unk86 != -1) {
            HuAudFXStop(player->unk86);
            player->unk86 = -1;
        }
    }
    if (GwPlayer[player->gwPlayerIdx].stat & 1) {
        stick = m251_PlayerComInput(obj);
    } else {
        stick = HuPadStkX[GwPlayer[player->gwPlayerIdx].pad];
    }
    dz = cosdf(obj->rot.y) * (player->unk0C / 1.08f);
    dx = sindf(obj->rot.y) * (player->unk0C / 1.08f);
    obj->trans.x += dx;
    obj->trans.z += dz;
    if (obj->trans.z < -3300.0f) {
        if (player->unk10 == 0) {
            if (obj->rot.y > limits[0]) {
                obj->rot.y -= 8.0f;
                if (obj->rot.y < limits[0]) {
                    obj->rot.y = limits[0];
                }
            }
        } else {
            if (obj->rot.y < limits[1]) {
                obj->rot.y += 8.0f;
                if (obj->rot.y > limits[1]) {
                    obj->rot.y = limits[1];
                }
            }
        }
        player->unk12 = player->unk10;
        espDispOff(player->esprites[0]);
        espDispOff(player->esprites[1]);
        espDispOff(player->esprites2[0]);
        espDispOff(player->esprites2[1]);
        if (player->unk1A == 0) {
            Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[10]].motId, 0, 6, 0);
            player->unk1A = 1;
            player->unk1C = 20;
        }
    } else {
        if (stick < 0) {
            player->unk10 = 1;
        } else if (stick > 0) {
            player->unk10 = 0;
        }
        if (m251_timeUpF == 0 && m251_goalF == 0 &&
            MgFlowStatGet() == MG_STATE_PLAY) {
            if (player->unk14 != player->unk10) {
                HuAudFXPlay(m251_playerSeTbl[player->playerIdx][0]);
            }
            espDispOn(player->esprites[player->unk10]);
            scale = sindf(player->unk68) * 0.15f + 0.85f;
            espScaleSet(player->esprites[player->unk10], scale, sindf(player->unk68) * 0.15f + 0.85f);
            espPosSet(player->esprites[player->unk10], m251_arrowXTbl[player->unk10] + player->playerIdx * 160,
                      0x50);
            espDispOff(player->esprites2[player->unk10]);
            espDispOff(player->esprites[player->unk10 ^ 1]);
            espDispOn(player->esprites2[player->unk10 ^ 1]);
            espPosSet(player->esprites2[player->unk10 ^ 1],
                      m251_arrowXTbl[player->unk10 ^ 1] + player->playerIdx * 160, 0x50);
            espScaleSet(player->esprites2[player->unk10 ^ 1], 0.7f, 0.7f);
            player->unk68 += 30.0f;
            if (player->unk68 >= 360.0f) {
                player->unk68 -= 360.0f;
            }
        } else {
            espDispOff(player->esprites[player->unk10]);
            espDispOff(player->esprites[player->unk10 ^ 1]);
            espDispOff(player->esprites2[player->unk10]);
            espDispOff(player->esprites2[player->unk10 ^ 1]);
        }
    }
    player->unk14 = player->unk10;
    if (obj->trans.z < -4100.0f && player->unk04->work[1] == 1) {
        if (m251_goalF == 0 && m251_timeUpF == 0) {
            HuAudFXPlay(m251_playerSeTbl[player->playerIdx][3]);
        }
        player->unk04->work[1] = 0;
    }
    if (obj->trans.z < -4600.0f) {
        m251_TunnelFadeStart(obj, 10);
        if (player->unk86 != -1) {
            msmSeSetFxMix(player->unk86, 0x3C);
        }
    }
    dz = cosdf(player->rot.y) * (player->unk0C / 1.08f);
    dx = sindf(player->rot.y) * (player->unk0C / 1.08f);
    player->pos.x += dx;
    player->pos.z += dz;
    if (player->pos.z < -3300.0f) {
        if (player->unk10 == 0) {
            if (player->rot.y > limits[0]) {
                player->rot.y -= 8.0f;
                if (player->rot.y < limits[0]) {
                    player->rot.y = limits[0];
                }
            }
        } else {
            if (player->rot.y < limits[1]) {
                player->rot.y += 8.0f;
                if (player->rot.y > limits[1]) {
                    player->rot.y = limits[1];
                }
            }
        }
    }
    Hu3DModelPosSet(obj->model[1], player->pos.x, player->pos.y, player->pos.z);
    Hu3DModelRotSet(obj->model[1], player->rot.x, player->rot.y, player->rot.z);
    player->pos2.x = player->pos.x - sindf(player->rot.y) * 20.0f;
    player->pos2.z = player->pos.z - cosdf(player->rot.y) * 20.0f;
    if (player->pos2.y > 0.0f) {
        player->pos2.y += player->unk74;
        player->unk74 *= 1.15f;
        if (player->pos2.y < 0.0f) {
            player->pos2.y = 0.0f;
            player->unk1C = 7;
            Hu3DMotionAttrSet(obj->model[2], 1, 0);
            Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DMotionTimeSet(obj->model[3], 0.0f);
        }
    } else if (player->unk1A == 2) {
        if (player->unk1C == 0) {
            Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[9]].motId, 0, 12, 2);
            player->unk1A = 0;
        } else {
            player->unk1C--;
        }
    }
    Hu3DModelPosSet(obj->model[3], player->pos2.x, player->pos2.y + 100.0f, player->pos2.z);
    Hu3DModelPosSet(obj->model[2], player->pos2.x, player->pos2.y + 100.0f, player->pos2.z);
    Hu3DModelRotSet(obj->model[2], 0.0f, player->rot.y, 0.0f);
    Hu3DModelPosSet(obj->model[4], player->pos2.x, player->pos.y + 100.0f + 0.0f, player->pos2.z);
    if (player->obj != NULL && player->obj->work[1] == 0 && m251_winner == -1) {
        player->unk82 = 0;
        player->unk80 = 0;
        m251_sceneReqTbl[player->playerIdx] = 0x12;
        player->unk04->work[1] = 1;
        obj->func = m251_PlayerBranchObjMain;
        player->unk04->func = m251_CameraBranchObjMain;
    }
    if (player->unk1A == 1) {
        if (player->unk1C == 0) {
            Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[0]].motId, 0, 15, 2);
            player->unk1A = 4;
        } else {
            player->unk1C--;
        }
    }
}

void m251_PlayerBranchObjMain(omObjData *obj) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);
    f32 dz;
    s16 fx;

    dz = cosdf(obj->rot.y) * (player->unk0C / 1.08f);
    obj->trans.x += sindf(obj->rot.y) * (player->unk0C / 1.08f);
    obj->trans.z += dz;
    if (obj->trans.z < -650.0f) {
        m251_BranchFadeStart(obj, 6);
        if (m251_goalViewF == 0 && player->unk92 == 0) {
            if (player->unk90 == 0) {
                HuAudFXPlay(m251_playerSeTbl[player->playerIdx][5]);
                player->unk92 = 1;
            } else {
                player->unk90--;
            }
        }
    }
    if (player->obj != NULL && player->obj->work[1] == 0) {
        player->unk10 = 0;
        player->unk14 = 0;
        if (player->unk12 == m251_branchRouteTbl[player->unk16] || m251_timeUpF == 1) {
            if (m251_timeUpF == 1) {
                player->unk16 = 0;
            } else {
                player->unk16++;
            }
            if (player->unk16 < 3) {
                m251_sceneReqTbl[player->playerIdx] = 0x21;
                Hu3DMotionModelSet(obj->model[2], obj->motion[9]);
                Hu3DMotionAttrSet(obj->model[2], 2, 2);
                player->unk1A = 0;
                obj->func = m251_PlayerRideObjMain;
                player->unk04->func = m251_CameraRideObjMain;
            } else {
                m251_goalF = 1;
                m251_goalTbl[player->playerIdx] = 1;
                m251_sceneReqTbl[player->playerIdx] = 0x24;
                Hu3DMotionModelSet(obj->model[2], obj->motion[0]);
                player->unk1A = 4;
                obj->func = NULL;
            }
        } else {
            m251_sceneReqTbl[player->playerIdx] = 0x23;
            obj->func = m251_PlayerFallObjMain;
            player->unk04->func = m251_CameraFallObjMain;
            Hu3DMotionModelSet(obj->model[2], obj->motion[8]);
            player->unk1A = 3;
            if (m251_goalViewF == 0) {
                fx = PlayerFXPlay(0x286, player->gwPlayerIdx);
                HuAudFXVolSet(fx, 0x5C);
                if (player->playerIdx == 0) {
                    HuAudFXPanning(fx, 0x20);
                } else {
                    HuAudFXPanning(fx, 0x60);
                }
            }
        }
    }
}

void m251_PlayerFallObjMain(omObjData *obj) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);
    f32 speed;
    f32 vy;
    f32 dx;
    f32 dz;

    m251_FlareUpdate(1, obj, 1000.0f, 2500.0f, 900.0f);
    vy = fabsf(sindf(player->unk54));
    speed = (1.0f - vy) * player->unk0C;
    vy = vy * player->unk0C;
    dz = cosdf(obj->rot.y) * (speed / 1.08f);
    dx = sindf(obj->rot.y) * (speed / 1.08f);
    obj->trans.x += dx;
    obj->trans.z += dz;
    obj->trans.y += vy;
    dz = cosdf(player->rot.y) * (speed / 1.08f);
    dx = sindf(player->rot.y) * (speed / 1.08f);
    player->pos.x += dx;
    player->pos.z += dz;
    player->pos.y += vy;
    Hu3DModelPosSet(obj->model[1], player->pos.x, player->pos.y, player->pos.z);
    Hu3DModelRotSet(obj->model[1], player->rot.x, player->rot.y, player->rot.z);
    Hu3DModelPosSet(obj->model[2], player->pos.x - sindf(player->rot.y) * 20.0f, player->pos.y + 100.0f,
                    player->pos.z - cosdf(player->rot.y) * 20.0f);
    Hu3DModelRotSet(obj->model[2], player->unk54, player->rot.y, 0.0f);
    player->unk0C *= 0.99f;
    if (obj->trans.z > 200.0f) {
        m251_BranchFadeStart(obj, 8);
    }
    if (player->obj != NULL && player->obj->work[1] == 0) {
        player->unk16 = 0;
        player->unk10 = 0;
        m251_sceneReqTbl[player->playerIdx] = 0x61;
        player->unk74 = -16.0f;
        player->unk04->work[1] = 1;
        Hu3DMotionModelSet(obj->model[2], obj->motion[11]);
        Hu3DMotionAttrSet(obj->model[2], 1, 1);
        player->unk1A = 2;
        obj->func = m251_PlayerRideObjMain;
        player->unk04->func = m251_CameraRideObjMain;
    }
}

void m251_PlayerGoalObjMain(omObjData *obj) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);
    f32 vol;
    f32 pitch;

    if (player->unk04->work[2] != 1) {
        return;
    }
    obj->trans.z -= player->unk0C;
    player->pos.z -= player->unk0C;
    Hu3DModelPosSet(obj->model[1], player->pos.x, player->pos.y, player->pos.z);
    Hu3DModelRotSet(obj->model[1], player->rot.x, player->rot.y, player->rot.z);
    Hu3DModelPosSet(obj->model[2], player->pos.x, player->pos.y + 100.0f, player->pos.z);
    Hu3DModelRotSet(obj->model[2], 0.0f, player->rot.y, 0.0f);
    Hu3DModelPosSet(obj->model[4], player->pos.x, player->pos.y + 100.0f, player->pos.z);
    player->unk0C *= 0.968f;
    if (player->unk86 != -1 && player->unk0C < 8.0f) {
        vol = (player->unk0C - 1.0f) * (36.0f / 7.0f) + 36.0f;
        pitch = (player->unk0C - 1.0f) * (1200.0f / 7.0f) + -600.0f;
        HuAudFXVolSet(player->unk86, vol);
        HuAudFXPitchSet(player->unk86, (s16)pitch);
    }
    if (player->unk0C < 1.0f) {
        player->unk0C = 0.0f;
        player->unk58 = 180.0f;
        if (m251_noWinnerF == 0) {
            HuAudFXPlay(m251_playerSeTbl[0][2]);
        } else if (player->playerIdx == 0) {
            HuAudFXPlay(m251_playerSeTbl[1][2]);
        }
        if (player->unk86 != -1) {
            HuAudFXStop(player->unk86);
            player->unk86 = -1;
        }
        m251_GoalEffStart(obj);
        if (m251_noWinnerF == 0) {
            Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[1]].motId, 0, 6, 2);
            player->unk5C = 8;
            obj->func = m251_PlayerTurnObjMain;
        } else {
            player->unk5C = 9;
        }
    }
}

void m251_PlayerTurnObjMain(omObjData *obj) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);

    player->unk58 -= 5.0f;
    if (player->unk58 < 65.0f) {
        player->unk58 = 65.0f;
        Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[0]].motId, 0, 6, 2);
        player->unk5C = 9;
        obj->func = NULL;
    }
    Hu3DModelRotSet(obj->model[2], 0.0f, player->unk58, 0.0f);
}

void m251_WinnerSet(void) {
    omObjData *obj = m251_playerObjTbl[m251_winner];
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);

    m251_mgFlow.winners[0] = player->gwPlayerIdx;
    GwPlayer[player->gwPlayerIdx].bonusCoin = 10;
    Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[2]].motId, 0, 6, 0);
    HuAudCharVoicePlayPlayer(omCharModelNoTbl[GwPlayer[player->gwPlayerIdx].chr][0] | 0x2F, -1, 0);
}

void m251_PlayerDrawMotSet(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[3]].motId, 0, 6, 0);
    obj->func = NULL;
    MgFlowStatSet(MG_STATE_RESULT);
}

void m251_TunnelFadeStart(omObjData *obj, s32 arg1) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);
    EndOfTheLineStage *data;

    if (player->obj != NULL) {
        return;
    }
    player->obj = omAddObj(0x28, 0, 0, -1, m251_TunnelFadeObjMain);
    player->obj->work[0] = player->playerIdx;
    player->obj->work[1] = 1;
    player->obj->work[2] = 0;
    player->obj->work[3] = arg1;
    data = OM_GET_DATA_PTR(m251_stageObj, EndOfTheLineStage);
    espDispOn(data->esprites[player->playerIdx + 2]);
    espTPLvlSet(data->esprites[player->playerIdx + 2], OM_GET_WORK_PTR(player->obj, s16)[5]);
    espPosSet(data->esprites[player->playerIdx + 2],
              m251_splitOfsXTbl[player->playerIdx] + m251_splitX, 0x78);
}

void m251_TunnelFadeObjMain(omObjData *obj) {
    EndOfTheLineStage *data = OM_GET_DATA_PTR(m251_stageObj, EndOfTheLineStage);

    obj->work[2] += obj->work[3];
    if (obj->work[2] >= 0x100) {
        obj->work[2] = 0xFF;
        obj->work[1] = 0;
    }
    espTPLvlSet(data->esprites[obj->work[0] + 2], OM_GET_WORK_PTR(obj, s16)[5]);
}

void m251_TunnelFadeKill(EndOfTheLinePlayer *player) {
    EndOfTheLineStage *data = OM_GET_DATA_PTR(m251_stageObj, EndOfTheLineStage);
    espDispOff(data->esprites[player->playerIdx + 2]);
    omDelObj(player->obj);
    player->obj = NULL;
}

void m251_BranchFadeStart(omObjData *obj, s32 arg1) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);
    EndOfTheLineStage *data;

    if (player->obj != NULL) {
        return;
    }
    player->obj = omAddObj(0x28, 0, 0, -1, m251_BranchFadeObjMain);
    player->obj->work[0] = player->playerIdx;
    player->obj->work[1] = 1;
    player->obj->work[2] = 0;
    player->obj->work[3] = arg1;
    player->unk90 = 0xF;
    player->unk92 = 0;
    data = OM_GET_DATA_PTR(m251_stageObj, EndOfTheLineStage);
    espDispOn(data->esprites[player->playerIdx + 4]);
    espTPLvlSet(data->esprites[player->playerIdx + 4], OM_GET_WORK_PTR(player->obj, s16)[5]);
    espPosSet(data->esprites[player->playerIdx + 4],
              m251_splitOfsXTbl[player->playerIdx] + m251_splitX, 0x78);
}

void m251_BranchFadeObjMain(omObjData *obj) {
    EndOfTheLineStage *data = OM_GET_DATA_PTR(m251_stageObj, EndOfTheLineStage);

    obj->work[2] += obj->work[3];
    if (obj->work[2] >= 0x100) {
        obj->work[2] = 0xFF;
        obj->work[1] = 0;
    }
    espTPLvlSet(data->esprites[obj->work[0] + 4], OM_GET_WORK_PTR(obj, s16)[5]);
}

void m251_BranchFadeKill(EndOfTheLinePlayer *player) {
    EndOfTheLineStage *data = OM_GET_DATA_PTR(m251_stageObj, EndOfTheLineStage);
    espDispOff(data->esprites[player->playerIdx + 4]);
    omDelObj(player->obj);
    player->obj = NULL;
}

s16 m251_PlayerComInput(omObjData *obj) {
    s16 dirs[2];
    EndOfTheLinePlayer *player;
    s32 difficulty;
    u16 dir;

    dirs[0] = 50;
    dirs[1] = -50;
    player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);
    if (player->unk16 == 3) {
        return 50;
    }
    difficulty = GwPlayer[player->gwPlayerIdx].cpu_difficulty;
    if (obj->trans.z < -3200.0f) {
        if (player->unk82 != 0) {
            return dirs[player->unk84];
        }
        player->unk82 = 1;
        switch (difficulty) {
            case 0:
                if (rand8() < 190) {
                    goto wrong;
                }
                goto right;
            case 1:
                if (rand8() < 128) {
                    goto random;
                }
                goto right;
            case 2:
                if (player->unk7A[player->unk16] == -1) {
                    goto random;
                }
                if (rand8() < 220) {
                    goto right;
                }
                goto wrong;
            case 3:
                if (player->unk7A[player->unk16] == -1) {
                    goto random;
                }
                if (rand8() < 220) {
                    goto right;
                }
                goto wrong;
            right:
                dir = m251_branchRouteTbl[player->unk16];
                break;
            wrong:
                dir = m251_branchRouteTbl[player->unk16] ^ 1;
                break;
            random:
                dir = (rand8() & 0x80) >> 7;
                break;
        }
        if (m251_comNum != 0) {
            if (m251_comLuckyNo == player->playerIdx) {
                dir = m251_branchRouteTbl[player->unk16];
            } else if (player->unk16 == 2) {
                dir = m251_branchRouteTbl[2] ^ 1;
            }
        }
        player->unk84 = dir;
        player->unk7A[player->unk16] = dir;
    }
    if (player->unk82 == 0) {
        if (player->unk80 != 0) {
            player->unk80--;
        } else {
            player->unk84 = (rand8() & 0x80) >> 7;
            player->unk80 = rand8() % 30 + 10;
        }
    }
    return dirs[player->unk84];
}

void m251_StartObjMain(omObjData *obj) {
    EndOfTheLinePlayer *player;
    s32 i;

    switch (m251_startPhase) {
        case 0:
            WipeCreateIn(WIPE_TYPE_PREV, 16);
            m251_startPhase = 1;
            break;
        case 1:
            if (WipeStatGet() != 0) {
                break;
            }
            obj->work[1] = 1;
            if (obj->work[0] == 1) {
                omDelObj(obj);
                m251_startObj = NULL;
                MgFlowStatSet(MG_STATE_START);
            }
            for (i = 0; i < 2; i++) {
                player = OM_GET_DATA_PTR(m251_playerObjTbl[i], EndOfTheLinePlayer);
                if (player->unk86 == -1) {
                    player->unk86 = HuAudFXPlay(m251_playerSeTbl[i][1]);
                    player->unk88 = 0x48;
                    HuAudFXVolSet(player->unk86, 0x48);
                    HuAudFXPitchSet(player->unk86, 600);
                    msmSeSetFxMix(player->unk86, 22);
                }
            }
            break;
    }
}

void m251_ResultObjMain(omObjData *obj) {
    EndOfTheLinePlayer *player =
        OM_GET_DATA_PTR(m251_playerObjTbl[m251_winner], EndOfTheLinePlayer);

    switch (m251_resultPhase) {
        case 0:
            if (player->unk5C == 8) {
                m251_resultPhase = 1;
                player->unk04->func = m251_CameraWinObjMain;
            }
            break;
        case 1:
            if (player->unk5C == 9) {
                if (m251_noWinnerF == 0) {
                    m251_WinnerSet();
                } else {
                    m251_PlayerDrawMotSet(m251_playerObjTbl[0]);
                    m251_PlayerDrawMotSet(m251_playerObjTbl[1]);
                }
                MgFlowStatSet(MG_STATE_RESULT);
                m251_resultPhase = 2;
            }
            break;
        case 2:
            break;
        case 3:
            if (mgFlowResultF == 1) {
                m251_PlayerDrawMotSet(m251_playerObjTbl[0]);
                m251_PlayerDrawMotSet(m251_playerObjTbl[1]);
            }
            break;
    }
}

void m251_CameraIntroObjMain(omObjData *obj) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR((omObjData *)obj->work[0], EndOfTheLinePlayer);
    s32 idx = player->playerIdx;

    m251_cameraAtTbl[idx].x = player->pos2.x;
    m251_cameraAtTbl[idx].y = player->pos2.y + 0.0f;
    m251_cameraAtTbl[idx].z = player->pos2.z;
    m251_cameraPosTbl[idx].x = player->pos2.x;
    m251_cameraPosTbl[idx].y = 200.0f;
    m251_cameraPosTbl[idx].z = m251_cameraAtTbl[idx].z - 1000.0f;
}

void m251_CameraDropObjMain(omObjData *obj) {
    omObjData *target = (omObjData *)obj->work[0];
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(target, EndOfTheLinePlayer);
    s32 idx = player->playerIdx;

    if (obj->work[1] == 1) {
        m251_cameraAtTbl[idx].x = target->trans.x;
        m251_cameraAtTbl[idx].y = target->trans.y + 200.0f;
        m251_cameraAtTbl[idx].z = target->trans.z;
        m251_cameraPosTbl[idx].x = target->trans.x;
        m251_cameraPosTbl[idx].y = m251_cameraAtTbl[idx].y + 700.0f;
        m251_cameraPosTbl[idx].z = m251_cameraAtTbl[idx].z + 600.0f;
    }
}

void m251_CameraZoomObjMain(omObjData *obj) {
    omObjData *target = (omObjData *)obj->work[0];
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(target, EndOfTheLinePlayer);
    EndOfTheLineCameraWork *sub = OM_GET_DATA_PTR(player->unk04, EndOfTheLineCameraWork);
    s32 idx = player->playerIdx;

    if (obj->work[1] == 1) {
        if (sub->unk10 != 0) {
            m251_stageObj->work[0] = obj->work[1];
            target->func = m251_PlayerRideObjMain;
            m251_cameraAtTbl[idx].x = target->trans.x;
            m251_cameraAtTbl[idx].y = target->trans.y + 200.0f;
            m251_cameraAtTbl[idx].z = target->trans.z;
            sub->unk00 += sub->unk08;
            sub->unk04 += sub->unk0C;
            m251_cameraPosTbl[idx].y = target->trans.y + 200.0f + sub->unk00;
            m251_cameraPosTbl[idx].z = target->trans.z + sub->unk04;
            sub->unk10--;
        } else {
            player->unk04->func = m251_CameraRideObjMain;
            m251_CameraRideObjMain(obj);
        }
    }
}

void m251_CameraRideObjMain(omObjData *obj) {
    omObjData *target = (omObjData *)obj->work[0];
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(target, EndOfTheLinePlayer);
    s32 idx = player->playerIdx;

    if (obj->work[1] == 1) {
        m251_cameraAtTbl[idx].x = target->trans.x;
        m251_cameraAtTbl[idx].y = target->trans.y + 200.0f;
        m251_cameraAtTbl[idx].z = target->trans.z;
        m251_cameraPosTbl[idx].x = target->trans.x;
        m251_cameraPosTbl[idx].y = m251_cameraAtTbl[idx].y + 500.0f;
        m251_cameraPosTbl[idx].z = m251_cameraAtTbl[idx].z + 1000.0f;
    }
}

void m251_CameraBranchObjMain(omObjData *obj) {
    omObjData *target = (omObjData *)obj->work[0];
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(target, EndOfTheLinePlayer);
    s32 idx = player->playerIdx;

    if (obj->work[1] == 1) {
        m251_cameraAtTbl[idx].x = target->trans.x;
        m251_cameraAtTbl[idx].y = 0.0f;
        m251_cameraAtTbl[idx].z = target->trans.z;
        m251_cameraPosTbl[idx].x = target->trans.x;
        m251_cameraPosTbl[idx].y = 0.0f;
        m251_cameraPosTbl[idx].z = m251_cameraAtTbl[idx].z + 10.0f;
    }
}

void m251_CameraFallObjMain(omObjData *obj) {
    omObjData *target = (omObjData *)obj->work[0];
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(target, EndOfTheLinePlayer);
    s32 idx = player->playerIdx;

    if (obj->work[1] == 1) {
        m251_cameraAtTbl[idx].x = target->trans.x;
        m251_cameraAtTbl[idx].y = target->trans.y + 100.0f;
        m251_cameraAtTbl[idx].z = target->trans.z;
    }
    m251_cameraPosTbl[idx].x = -2200.0f;
    m251_cameraPosTbl[idx].y = -1100.0f;
    m251_cameraPosTbl[idx].z = 700.0f;
}

void m251_CameraGoalObjMain(omObjData *obj) {
    s32 idx = OM_GET_DATA_PTR((omObjData *)obj->work[0], EndOfTheLinePlayer)->playerIdx;
    EndOfTheLineStage *data = OM_GET_DATA_PTR(m251_stageObj, EndOfTheLineStage);
    EndOfTheLinePlayer *other = OM_GET_DATA_PTR(m251_playerObjTbl[idx ^ 1], EndOfTheLinePlayer);
    s16 *viewport;
    s16 *scissor;
    s16 viewX;

    if (obj->work[2] == 0) {
        m251_goalViewF = 1;
        viewport = m251_viewportTbl[idx];
        scissor = m251_scissorTbl[idx];
        if (idx == 0) {
            m251_splitX += 4.0f;
            if (m251_splitX >= 320.0f) {
                m251_splitX = 320.0f;
                obj->work[2] = 1;
            }
            espPosSet(data->esprites[idx + 6], m251_splitX - 160.0f, 0x78);
            espPosSet(data->esprites[7], m251_splitX + 160.0f, 0x78);
            espPosSet(data->esprites[10], m251_splitX, 0x78);
            espPosSet(data->esprites[other->playerIdx + 4],
                      m251_splitOfsXTbl[other->playerIdx] + m251_splitX, 0x78);
            espPosSet(data->esprites[other->playerIdx + 2],
                      m251_splitOfsXTbl[other->playerIdx] + m251_splitX, 0x78);
            espPosSet(data->esprites[other->playerIdx],
                      m251_splitOfsXTbl[other->playerIdx] + m251_splitX, 0x78);
            scissor[2] += 4.0f;
            ScissorSet(idx, scissor[0], scissor[1], scissor[2], scissor[3]);
            ScissorSet(1, scissor[2] + 1, m251_scissorTbl[1][1], m251_scissorTbl[1][2],
                       m251_scissorTbl[1][3]);
            viewX = viewport[2] + (m251_splitX - 160.0f) * 320.0f / 159.0f;
            ViewportSet(idx, viewport[0], viewport[1], 511.0f, viewX, viewport[3], 511.0f);
        } else {
            m251_splitX -= 4.0f;
            if (m251_splitX <= 0.0f) {
                m251_splitX = 0.0f;
                obj->work[2] = 1;
            }
            espPosSet(data->esprites[idx + 6], m251_splitX + 160.0f, 0x78);
            espPosSet(data->esprites[6], m251_splitX - 160.0f, 0x78);
            espPosSet(data->esprites[10], m251_splitX, 0x78);
            espPosSet(data->esprites[other->playerIdx + 4],
                      m251_splitOfsXTbl[other->playerIdx] + m251_splitX, 0x78);
            espPosSet(data->esprites[other->playerIdx + 2],
                      m251_splitOfsXTbl[other->playerIdx] + m251_splitX, 0x78);
            espPosSet(data->esprites[other->playerIdx],
                      m251_splitOfsXTbl[other->playerIdx] + m251_splitX, 0x78);
            scissor[0] -= 4.0f;
            ScissorSet(idx, scissor[0], scissor[1], scissor[2], scissor[3]);
            ScissorSet(0, m251_scissorTbl[0][0], m251_scissorTbl[0][1],
                       m251_scissorTbl[1][0] - 1, m251_scissorTbl[0][3]);
            viewX = viewport[2] - (160.0f - m251_splitX) * 320.0f / 159.0f;
            ViewportSet(idx, viewport[0], viewport[1], 511.0f, viewX, viewport[3], 511.0f);
        }
    }
    m251_goalScale = 1.0f;
    m251_cameraAtTbl[idx].x = 400.0f;
    m251_cameraAtTbl[idx].y = 400.0f;
    m251_cameraAtTbl[idx].z = 0.0f;
    m251_cameraPosTbl[idx].x = 1660.0f;
    m251_cameraPosTbl[idx].y = 1030.0f;
    m251_cameraPosTbl[idx].z = 810.0f;
    espScaleSet(data->esprites[idx + 6], 1.0f, 1.0f);
    Hu3DCameraPerspectiveSet(idx, 33.0f, 80.0f, 20000.0f);
}

void m251_CameraWinObjMain(omObjData *obj) {
    s32 idx = OM_GET_DATA_PTR((omObjData *)obj->work[0], EndOfTheLinePlayer)->playerIdx;
    EndOfTheLineStage *data = OM_GET_DATA_PTR(m251_stageObj, EndOfTheLineStage);

    if (m251_winZoom > 0.9f) {
        m251_winZoom -= 0.01f;
    }
    m251_cameraAtTbl[idx].x = 400.0f;
    m251_cameraAtTbl[idx].y = 400.0f;
    m251_cameraAtTbl[idx].z = 0.0f;
    m251_cameraPosTbl[idx].x = m251_winZoom * 1660.0f;
    m251_cameraPosTbl[idx].y = m251_winZoom * 1030.0f;
    m251_cameraPosTbl[idx].z = m251_winZoom * 810.0f;
    espScaleSet(data->esprites[idx + 6], 1.0f - m251_winZoom + 1.0f,
                1.0f - m251_winZoom + 1.0f);
}

void m251_CameraDrawObjMain(omObjData *obj) {
    s32 idx = OM_GET_DATA_PTR((omObjData *)obj->work[0], EndOfTheLinePlayer)->playerIdx;
    EndOfTheLineStage *data = OM_GET_DATA_PTR(m251_stageObj, EndOfTheLineStage);

    m251_cameraAtTbl[idx].x = 400.0f;
    m251_cameraAtTbl[idx].y = 400.0f;
    m251_cameraAtTbl[idx].z = 0.0f;
    m251_cameraPosTbl[idx].x = 1660.0f;
    m251_cameraPosTbl[idx].y = 1030.0f;
    m251_cameraPosTbl[idx].z = 810.0f;
    espScaleSet(data->esprites[idx + 6], 1.0f, 1.0f);
    Hu3DCameraPerspectiveSet(idx, 33.0f, 80.0f, 20000.0f);
    obj->work[2] = 1;
}

void m251_CameraViewObjMain(omObjData *obj) {
    u32 i;

    for (i = 0; i < obj->work[0]; i++) {
        Hu3DCameraPosSetV(i, &m251_cameraPosTbl[i], &m251_cameraAtTbl[i],
                          &m251_cameraUpTbl[i]);
        Hu3DCamUpdateMtx(i);
    }
}

void m251_FlareUpdate(u16 arg0, omObjData *obj, f32 x, f32 y, f32 z) {
    Vec at;
    Vec eye;
    Vec pos;
    f32 len;
    s32 idx;
    s32 i;

    idx = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer)->playerIdx;

    eye.x = m251_cameraPosTbl[idx].x - x;
    eye.y = m251_cameraPosTbl[idx].y - y;
    eye.z = m251_cameraPosTbl[idx].z - z;
    len = HuSqrtf(eye.x * eye.x + eye.y * eye.y + eye.z * eye.z);
    eye.x /= len;
    eye.y /= len;
    eye.z /= len;

    at.x = m251_cameraAtTbl[idx].x - x;
    at.y = m251_cameraAtTbl[idx].y - y;
    at.z = m251_cameraAtTbl[idx].z - z;
    len = HuSqrtf(at.x * at.x + at.y * at.y + at.z * at.z);
    at.x /= len;
    at.y /= len;
    at.z /= len;

    at.x = eye.x * m251_flareBlendTbl[arg0].x + (1.0f - m251_flareBlendTbl[arg0].x) * at.x;
    at.y = eye.y * m251_flareBlendTbl[arg0].y + (1.0f - m251_flareBlendTbl[arg0].y) * at.y;
    at.z = eye.z * m251_flareBlendTbl[arg0].z + (1.0f - m251_flareBlendTbl[arg0].z) * at.z;

    for (i = 0; i < 5; i++) {
        pos.x = x + at.x * m251_flareDistTbl[arg0][i];
        pos.y = y + at.y * m251_flareDistTbl[arg0][i];
        pos.z = z + at.z * m251_flareDistTbl[arg0][i];
        Hu3DModelPosSet(m251_stageObj->model[20 + i * 2 + idx], pos.x, pos.y, pos.z);
        Hu3DModelScaleSet(m251_stageObj->model[20 + i * 2 + idx], m251_flareScaleTbl[arg0][i],
                          m251_flareScaleTbl[arg0][i], m251_flareScaleTbl[arg0][i]);
    }
}

void m251_GoalEffObjCreateAll(void) {
    omObjData *obj;
    s32 i;

    for (i = 0; i < 2; i++) {
        m251_goalEffObjTbl[i] = obj = omAddObj(0x28, 1, 0, -1, NULL);
        obj->model[0] = Hu3DModelRead(0x540012, 0xA8D);
    }
}

void m251_GoalEffStart(omObjData *obj) {
    s32 idx = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer)->playerIdx;

    omSetTra(m251_goalEffObjTbl[idx], obj->trans.x + 150.0f, obj->trans.y + 50.0f, obj->trans.z + 100.0f);
    omSetSca(m251_goalEffObjTbl[idx], 3.0f, 3.0f, 3.0f);
    Hu3DModelAttrSet(m251_goalEffObjTbl[idx]->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelCameraSet(m251_goalEffObjTbl[idx]->model[0], m251_cameraMaskTbl[idx]);
    Hu3DMotionAttrSet(m251_goalEffObjTbl[idx]->model[0], 2, 2);
    m251_goalEffObjTbl[idx]->func = m251_GoalEffObjMain;
}

void m251_GoalEffObjMain(omObjData *obj) {
}
