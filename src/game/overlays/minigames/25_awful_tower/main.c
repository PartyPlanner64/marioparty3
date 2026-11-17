#include "common.h"
#include "macros.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/effect.h"
#include "game/esprite.h"
#include "game/hmfanim.h"
#include "game/hmfspr.h"
#include "game/malloc.h"
#include "game/mallocblock.h"
#include "game/object.h"
#include "game/pause.h"
#include "game/util.h"
#include "game/wipe.h"
#include "gcc/memory.h"
#include "game/overlays/minigame.h"

#define ABS(x) ((x) > 0 ? (x) : -(x))

// Per-player info, indexed by group through m237_groupPlayerTbl
typedef struct {
    /* 0x00 */ s8 chr;
    /* 0x01 */ s8 player;
    /* 0x02 */ s8 group;
    /* 0x03 */ s8 pad;
    /* 0x04 */ s8 cpuDifficulty; // -1 for human players
    /* 0x05 */ char unk05[3];
    /* 0x08 */ s32 unk08;
} AwfulTowerPlayer; // Size 0xC

extern s32 omCharModelNoTbl[][6];
extern EffectGroup *EffectGroupData[];
extern f32 mgPlayerSpeedMax;
extern Gfx *gMainGfxPos;
extern omObjData *mgItemObjTbl[];

s32 m237_cameraBitTbl[] = { 1, 2, 4, 8 };
MinigameFlow m237_mgFlow = { 0 };
s32 m237_coinSprMdlTbl[] = { -1, -1 };

Gfx m237_gfxBackInit[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 320, 240),
    gsSPEndDisplayList(),
};

u32 m237_frameCnt = 40;
f32 m237_groundXTbl[4] = { 32000.0f, 32000.0f, 32000.0f, 32000.0f };
s8 m237_platNoTbl[4] = { -1, -1, -1, -1 };
s8 m237_endPlatNoTbl[4] = { -1, -1, -1, -1 };
s8 m237_ridePlatTbl[4] = { 0 };
s8 m237_bonkTbl[4] = { 0 };
u8 m237_flyerStateTbl[4] = { 0 };
u8 m237_flyerPosNoTbl[4] = { 0 };
u8 m237_flyerThrowTbl[4] = { 0 };
f32 m237_shotYTbl[4] = { -1000.0f, -1000.0f, -1000.0f, -1000.0f };
u8 m237_squeezePlatTbl[4] = { 1, 1, 1, 1 };
f32 m237_topXTbl[4] = { 1000.0f, 1000.0f, 1000.0f, 1000.0f };
s8 m237_comTargetTbl[4] = { -1, -1, -1, -1 };
u8 m237_comJumpTimerTbl[4] = { 0 };
u8 m237_winCenterTimer = 0;
f32 m237_winStartX = 1000.0f;
u8 m237_flyerDelayTbl[4] = { 0 };
f32 m237_prevX2Tbl[4] = { 0 };
f32 m237_prevXTbl[4] = { 0 };
u8 m237_ridePushTbl[4] = { 0 };
s8 m237_wallDirTbl[4] = { 0 };
s8 m237_comJitterTbl[4] = { 0 };
s8 m237_comJumpTimeTbl[20] = { 0, 0, 0, 0, 3, 0, 0, 0, 0, 6, 0, 0, 0, 0, 2, 6, 60, 0, 0, 0 };
s8 m237_comHoldTbl[20] = { 0, 0, 0, 0, 3, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 };
u8 m237_comMissCntTbl[4] = { 0 };
f32 m237_shotVelXInitTbl[] = { -10.0f, -16.0f, -18.0f };
f32 m237_shotVelYInitTbl[] = { 22.0f, 24.0f, 60.0f };

f32 m237_platYTbl[16] BSS;
f32 m237_platMoveTbl[16] BSS;
f32 m237_flyerXTbl[4] BSS;
f32 m237_flyerYTbl[4] BSS;
f32 m237_flyerVelXTbl[4] BSS;
f32 m237_flyerVelYTbl[4] BSS;
f32 m237_shotXTbl[4] BSS;
f32 m237_shotVelXTbl[4] BSS;
f32 m237_shotVelYTbl[4] BSS;
f32 m237_shotRotTbl[4] BSS;
f32 m237_shotRotSpeedTbl[4] BSS;
f32 m237_shotActiveTbl[4] BSS;
f32 m237_waveTbl[55] BSS;
s16 m237_starEffTbl[4] BSS;
u8 m237_starEffPad[4] BSS; /* Unreferenced. */
AwfulTowerPlayer m237_playerTbl[4] BSS;
AwfulTowerPlayer *m237_groupPlayerTbl[4] BSS;
u8 m237_groupPlayerPad[8] BSS; /* Unreferenced. */
f32 m237_cameraYTbl[4] BSS;
u8 m237_coinStatTbl[4][5] BSS;
omObjData *m237_stageObj BSS;
u16 m237_flyerSprTbl[4][3] BSS;
omObjData *m237_platObjTbl[4][3] BSS;
omObjData *m237_coinObjTbl[5] BSS;
u8 m237_coinObjPad[4] BSS; /* Unreferenced. */
omObjData *m237_playerObjTbl[4] BSS;
s16 m237_backSprAnimTbl[4] BSS;
u8 m237_backSprAnimPad[0xC] BSS; /* Unreferenced. */
u8 m237_playerGroupTbl[4] BSS;
s16 m237_backSprTbl[4] BSS;
u16 m237_exitF BSS;
u32 m237_phaseTimer BSS;
u8 m237_phaseTimerPad[4] BSS; /* Unreferenced. */
s16 m237_phase BSS;
omObjData *m237_mdlObj BSS;
s16 m237_winAnimTbl[2] BSS;
u8 m237_winAnimPad[0xC] BSS; /* Unreferenced. */
s8 m237_winner BSS;
u8 m237_exitTimer BSS;
u8 m237_goalCnt BSS;

extern const s16 m237_fontMesTbl[];

void m237_MainObjInit(omObjData *object);
void m237_MainObjMain(omObjData *object);
void m237_StageObjInit(omObjData *object);
void m237_CoinObjInit(omObjData *object);
void m237_PlatObjInit(omObjData *object);
void m237_MdlObjInit(omObjData *object);
void m237_MdlObjMain(omObjData *object);
void m237_BackDraw(void);
void m237_PlayerInit(omObjData *object, s32 model, s32 motion, u16 group, f32 x, f32 y, f32 z);
void m237_Player0ObjInit(omObjData *object);
void m237_Player1ObjInit(omObjData *object);
void m237_Player2ObjInit(omObjData *object);
void m237_Player3ObjInit(omObjData *object);
void m237_PlayerObjMain(omObjData *object);

void m237_ObjectSetup(void) {
    omObjData *object;
    s32 i;
    s32 j;

    MapCollInit(50);
    Hu3DQuadPoolInit(&mgQuadPool, 0x40);
    Hu3DSprModelInit(0x20);
    omInitObjMan(100, 0);
    omGameSysInit();
    Hu3DScreenClearF = 1;
    CamSetupInit(4);
    CamSetupMapCullAddMulti(4);
    for (i = 0; i < 4; i++) {
        s32 lefts[4] = { 0, 93, 161, 229 };
        s32 rights[4] = { 92, 160, 228, 320 };

        ScissorSet(i, lefts[i], 0.0f, rights[i], 240.0f);
        ViewportSet(i, 640.0f, 480.0f, 511.0f, i * 272 + 236, 480.0f, 511.0f);
        Hu3DCameraPerspectiveSet(i, 7.152669f, 8000.0f, 16000.0f);
        CenterM[i].x = 0.0f;
        CenterM[i].y = 650.0f;
        CenterM[i].z = 0.0f;
        CRotM[i].x = 0.0f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CZoomM[i] = 12000.0f;
    }
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    MgPlayerParamReset();
    MgShadowAltSet(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightDirSet(0, 0.0f, 80.0f, 130.0f);
    Hu3DGLightColorSet(0, 0x80, 0x80, 0x90);
    Hu3DGLightDirSet(1, 20.0f, 80.0f, 110.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xF0);
    omAddObj(0, 0, 0, -1, m237_MainObjInit);
    m237_mdlObj = omAddObj(4, 21, 21, -1, m237_MdlObjInit);
    omSetStatBit(m237_mdlObj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    MgMapBaseSet(mgMapObjNum);
    mgMapObjTbl[mgMapObjNum++] = m237_stageObj = omAddObj(2, 21, 21, -1, m237_StageObjInit);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            mgMapObjTbl[mgMapObjNum++] = m237_platObjTbl[i][j] = omAddObj(2, 4, 4, -1, m237_PlatObjInit);
        }
    }
    for (i = 0; i < 5; i++) {
        mgItemObjTbl[mgItemObjNum++] = m237_coinObjTbl[i] = omAddObj(2, 4, 2, -1, m237_CoinObjInit);
    }
    mgPlayerObjTbl[mgPlayerObjNum++] = m237_playerObjTbl[0] = omAddObj(3, 12, 60, -1, m237_Player0ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = m237_playerObjTbl[1] = omAddObj(3, 12, 60, -1, m237_Player1ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = m237_playerObjTbl[2] = omAddObj(3, 12, 60, -1, m237_Player2ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = m237_playerObjTbl[3] = omAddObj(3, 12, 60, -1, m237_Player3ObjInit);
    object = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    object->work[0] = 4;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    WipeCreateIn(WIPE_TYPE_PREV, 30);
    GMesFontMesCreate(m237_fontMesTbl, 1);
    m237_mgFlow.type = MINIGAME_4P;
    m237_mgFlow.startDelay = 60;
    m237_mgFlow.timer = 1800;
    m237_mgFlow.timeDisp = MG_TIME_DISP_COUNTDOWN;
    m237_mgFlow.timerMode = MG_TIMER_COUNT_DOWN;
    m237_mgFlow.finishDelay = 75;
    m237_mgFlow.resultDelay = 165;
    m237_mgFlow.newRecord = FALSE;
    m237_mgFlow.gauge = MG_GAUGE_NONE;
    m237_mgFlow.timeLimit = -1;
    MgFlowInit(&m237_mgFlow);
    for (i = 0; i < 4; i++) {
        m237_starEffTbl[i] = EffectGroupStarCreate(0x6A9, 4);
    }
}

void m237_BackDrawHook(void) {
    m237_BackDraw();
}

void m237_MainObjInit(omObjData *object) {
    s32 i;
    s32 group;

    m237_exitF = 0;
    m237_phase = 0;
    m237_phaseTimer = 0;
    m237_winner = 5;
    m237_exitTimer = 0;
    m237_goalCnt = 0;
    m237_cameraYTbl[0] = 650.0f;
    m237_cameraYTbl[1] = 650.0f;
    m237_cameraYTbl[2] = 650.0f;
    m237_cameraYTbl[3] = 650.0f;
    for (i = 0; i < 4; i++) {
        m237_coinStatTbl[i][0] = m237_coinStatTbl[i][1] = m237_coinStatTbl[i][2] =
            m237_coinStatTbl[i][3] = m237_coinStatTbl[i][4] = 1;
        m237_groupPlayerTbl[i] = &m237_playerTbl[i];
        bzero(&m237_playerTbl[i], sizeof(AwfulTowerPlayer));
    }
    for (i = 0; i < 4; i++) {
        group = m237_playerGroupTbl[i] = GwPlayer[i].group;
        m237_groupPlayerTbl[group]->player = i;
        m237_groupPlayerTbl[group]->pad = GwPlayer[i].pad;
        m237_groupPlayerTbl[group]->chr = GwPlayer[i].chr;
        m237_groupPlayerTbl[group]->group = group;
        m237_groupPlayerTbl[group]->cpuDifficulty = (GwPlayer[i].stat & PLAYER_IS_CPU) ? GwPlayer[i].cpu_difficulty : -1;
    }
    object->func = m237_MainObjMain;
}

const s16 m237_fontMesTbl[] = {
    0x8260, 0x8261, 0x8262, 0x8263, 0x8264, 0x8265, 0x8266, 0x8267, 0x8268, 0x8269, 0x826A, 0x826B, 0x826C,
    0x826D, 0x826E, 0x826F, 0x8270, 0x8271, 0x8272, 0x8273, 0x8274, 0x8275, 0x8276, 0x8277, 0x8278, 0x8279,
    0x824F, 0x8250, 0x8251, 0x8252, 0x8253, 0x8254, 0x8255, 0x8256, 0x8257, 0x8258, 0x0000
};

void m237_MainObjMain(omObjData *object) {
    u8 motions[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    s32 chrDirs[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
    s32 winFiles[2][8] = {
        { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B },
        { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C },
    };
    s8 chr;
    s16 i;

    m237_phaseTimer++;
    switch (m237_phase) {
        case 0:
            if (m237_phaseTimer == 51 && m237_exitF == 0 && omSysExitReq == 0) {
                HuAudSeqPlay(0x33);
            }
            break;
        case 3:
            if (m237_goalCnt >= 20) {
                MgFlowStatNext();
            }
            break;
    }
    MgFlowMain();
    switch (m237_phase) {
        case 0:
            if (MgFlowStatGet() == MG_STATE_START) {
                m237_phase = 1;
                m237_phaseTimer = 0;
            }
            break;
        case 1:
            if (MgFlowStatGet() == MG_STATE_PLAY) {
                m237_phase = 2;
                m237_phaseTimer = 0;
            }
            break;
        case 2:
            if (m237_winner != 5 || MgFlowStatGet() == MG_STATE_FINISH) {
                if (m237_winner == 5) {
                    m237_phase = 6;
                    m237_winner = 4;
                } else {
                    m237_phase = 3;
                }
                m237_phaseTimer = 0;
            }
            if (m237_phase != 3) {
                break;
            }
        case 3:
            if (m237_phaseTimer == 0) {
                m237_mgFlow.finishDelay = 210;
                if (MgFlowStatGet() != MG_STATE_FINISH) {
                    MgFlowStatNext();
                }
                m237_mgFlow.resultType = MG_RESULT_WIN_1;
                m237_mgFlow.winners[0] = m237_groupPlayerTbl[m237_winner]->player;
                GwPlayer[m237_groupPlayerTbl[m237_winner]->player].bonusCoin = 10;
            }
            if (m237_phaseTimer == 2) {
                MgFlowResultWaitSet(30);
            }
            if (MgFlowStatGet() == MG_STATE_RESULT) {
                m237_phase = 4;
                m237_phaseTimer = 0;
            }
            break;
        case 6:
            if (m237_phaseTimer == 1) {
                m237_mgFlow.resultType = MG_RESULT_DRAW;
                m237_mgFlow.resultDelay = 0x90;
            }
            if (MgFlowStatGet() == MG_STATE_RESULT) {
                m237_phase = 5;
                m237_phaseTimer = 0;
            }
            break;
        case 4:
            if (m237_phaseTimer == 1) {
                chr = m237_groupPlayerTbl[m237_winner]->chr;
                m237_playerObjTbl[m237_winner]->model[9] =
                    Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][2], 0x4AD);
                m237_winAnimTbl[0] =
                    CharAnimCreate(m237_playerObjTbl[m237_winner]->model[9], 1, motions[chr],
                                       (chrDirs[chr] << 16) | winFiles[0][chr]);
                m237_winAnimTbl[1] = Hu3DAnimDataRead((chrDirs[chr] << 16) | winFiles[1][chr]);
                Hu3DModelDynamicFree(m237_playerObjTbl[m237_winner]->model[9]);
                Hu3DModelCameraSet(m237_playerObjTbl[m237_winner]->model[9],
                                   m237_cameraBitTbl[m237_winner]);
                Hu3DModelAttrSet(m237_playerObjTbl[m237_winner]->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(m237_playerObjTbl[m237_winner]->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DMotionTimeSet(m237_playerObjTbl[m237_winner]->model[9],
                                  Hu3DData[m237_playerObjTbl[m237_winner]->model[0]].motTime);
                Hu3DMotionAttrSet(m237_playerObjTbl[m237_winner]->model[9], 2, 2);
                Hu3DData[m237_playerObjTbl[m237_winner]->model[9]].pos.x =
                    m237_playerObjTbl[m237_winner]->trans.x;
                Hu3DData[m237_playerObjTbl[m237_winner]->model[9]].pos.y =
                    m237_playerObjTbl[m237_winner]->trans.y;
                Hu3DData[m237_playerObjTbl[m237_winner]->model[9]].pos.z =
                    m237_playerObjTbl[m237_winner]->trans.z;
            }
            if (m237_phaseTimer < 16) {
                Hu3DModelRotSet(m237_playerObjTbl[m237_winner]->model[9], 0.0f,
                                m237_phaseTimer / 15.0f * 90.0f + -90.0f, 0.0f);
            }
            if (m237_phaseTimer == 30) {
                Hu3DMotionModelSet(m237_playerObjTbl[m237_winner]->model[9],
                                   m237_playerObjTbl[m237_winner]->model[10]);
                Hu3DMotionAttrSet(m237_playerObjTbl[m237_winner]->model[9], 2, 0);
                CharAnimSet(m237_playerObjTbl[m237_winner]->model[9], 1,
                                   motions[m237_groupPlayerTbl[m237_winner]->chr],
                                   m237_winAnimTbl[1]);
                HuAudCharVoicePlay(m237_groupPlayerTbl[m237_winner]->unk08);
            }
        case 5:
            if (m237_phase == 5 && m237_phaseTimer == 1) {
                for (i = 0; i < 4; i++) {
                    MgPlayerMotSet(m237_playerObjTbl[i], 14);
                }
            }
            if (MgFlowStatGet() == MG_STATE_EXIT) {
                m237_phase = 7;
                m237_phaseTimer = 0;
            }
            break;
        case 7:
            if (m237_phaseTimer == 1) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            } else if (m237_phaseTimer >= 32) {
                m237_exitF = 1;
            }
            break;
    }
    if (m237_exitF != 0 || omSysExitReq != 0) {
        if (omSysExitReq != 0) {
            if (m237_exitTimer == 0) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                HuAudSeqFadeOut(20);
                HuAudFXAllFadeOut(20);
            }
            m237_exitTimer++;
            if (m237_exitTimer < 25) {
                return;
            }
        } else {
            HuAudSeqFadeOut(30);
        }
        omOvlReturnEx(1);
    }
}

void m237_StageObjInit(omObjData *object) {
    MgMapWork *work;

    object->model[0] = -1;
    object->model[0] = Hu3DModelRead2(0x460006, 0x499);
    Hu3DModelObjAttrSet(object->model[0], 0x600, 0);
    Hu3DLLightCreate(object->model[0], 1);
    Hu3DLLightColorSet(object->model[0], 0xFF, 0xFF, 0xFF);
    Hu3DLLightDirSet(object->model[0], 0.0f, 0.0f, 127.0f);
    object->trans.y = object->trans.z = 0.0f;
    object->trans.x = 1500.0f;
    object->trans.y = -60.0f;
    object->trans.z = 300.0f;
    omSetRot(object, 90.0f, 0.0f, 0.0f);
    omSetSca(object, 1000.0f, 1.0f, 1.0f);
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    MgMapBoxSet(object, 0.0f, -670.0f, -380.0f, 670.0f, 250.0f);
    MgMapFrictionSet(object, 1.0f);
    MgMapAccelSet(object, 6.0f);
    MgMapNoBumpOn(object);
    work->unk04 = 0;
    object->func = NULL;
}

s32 m237_CoinGetHook(omObjData *player, omObjData *object) {
    MgItemWork *data = object->data;

    GwPlayer[((MgPlayerWork *)player->data)->unk59].gameCoin++;
    HuAudFXPlay(9);
    data->unk54 = 0;
    data->unk78 = 0;
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    return 1;
}

void m237_CoinObjInit(omObjData *object) {
    MgItemWork *data;
    s16 i;
    s32 unused[2]; // Retain the original stack frame.

    object->data = HuMemAllocTag(sizeof(MgItemWork), TAG_OVERLAY);
    memset(object->data, 0, sizeof(MgItemWork));
    data = object->data;
    if (m237_coinSprMdlTbl[0] == -1) {
        MgObjSprMdlCreate(object, 0x210026, 0x41D, 8);
        m237_coinSprMdlTbl[0] = data->unk55;
    } else {
        data->unk55 = Hu3DSprModelLink(m237_coinSprMdlTbl[0], 8);
        object->model[0] = Hu3DSprModelData[data->unk55].modelId;
        Hu3DModelObjAttrSet(object->model[0], 0x70000000, 0x70000000);
    }
    data->unk44 = 0.0f;
    data->unk48 = 40.0f;
    data->unk34 = 50.0f;
    data->unk3C = 0.0f;
    data->unk78 = 0;
    data->unk52 = 3;
    data->unk7C = 2000;
    data->unk50 = 0;
    data->unk40 = 0.0f;
    data->unk58 = 1.2f;
    data->unk56 = 0;
    data->unk54 = 1;
    for (i = 0; i < 9; i++) {
        data->unk84[i] = NULL;
    }
    data->unk84[8] = (void *)m237_CoinGetHook;
    MgObjScaleSet(object, 3.0f, 3.0f, 3.0f);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    object->func = NULL;
}

void m237_PlatObjInit(omObjData *object) {
    MgMapWork *work;

    object->model[0] = -1;
    object->trans.x = object->trans.y = object->trans.z = 250.0f;
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    MgMapBlockSet(object, 50.0f, 100.0f, -50.0f, -50.0f, 50.0f, 50.0f);
    MgMapFrictionSet(object, 1.0f);
    MgMapAccelSet(object, 6.0f);
    work->unk04 = 0;
    object->func = NULL;
}

s16 m237_SprMdlCreate(s32 file, u16 *sprite) {
    void *data = DataRead(file);
    s16 anim = Hu3DAnimDataCreate(data);
    u16 idx;

    HuMemMemoryFreePerm(data);
    *sprite = idx = Hu3DSprModelCreate((void *)-1, 0x6B9, 0);
    Hu3DSprModelData[idx].unk_02 = anim;
    return Hu3DSprModelData[idx].modelId;
}

void m237_MdlObjInit(omObjData *object) {
    s32 sprFiles[4] = { 0x46000A, 0x46000B, 0x46000C, 0x46000D };
    s16 i;
    s16 j;
    s16 k;

    for (i = 0; i < 4; i++) {
        m237_backSprAnimTbl[i] = HuSprAnimDataRead(sprFiles[i]);
        m237_backSprAnimTbl[i] = HuSprAnimDataRead(sprFiles[i]);
        m237_backSprTbl[i] = espEntry(m237_backSprAnimTbl[i], 0, 0);
        espDispOff(m237_backSprTbl[i]);
    }
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 4; i++) {
            s32 modelIdx[3] = { 8, 12, 16 };
            s32 animFiles[3] = { 7, 8, 9 };

            object->model[modelIdx[j] + i] =
                m237_SprMdlCreate(animFiles[j] | 0x460000, &m237_flyerSprTbl[i][j]);
            Hu3DModelAttrSet(object->model[modelIdx[j] + i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelCameraSet(object->model[modelIdx[j] + i], m237_cameraBitTbl[i]);
            if (j < 2) {
                Hu3DModelScaleSet(object->model[modelIdx[j] + i], 6.0525f, 6.0525f, 6.0525f);
            } else {
                Hu3DModelScaleSet(object->model[modelIdx[j] + i], 3.02625f, 3.02625f, 3.02625f);
            }
        }
    }
    for (i = 0; i < 5; i++) {
        f32 posX[5] = { 1.0f, -1.0f, 1.0f, -1.0f, 0.25f };
        f32 posY[5] = { 13.5f, 8.5f, 24.0f, 34.0f, 40.5f };
        MgItemWork *data = m237_coinObjTbl[i]->data;

        m237_coinObjTbl[i]->trans.x = posX[i] * 150.0f;
        m237_coinObjTbl[i]->trans.y = posY[i] * 100.0f + 50.0f;
        m237_coinObjTbl[i]->trans.z = 0.0f;
        data->unk56 = i;
        Hu3DModelAttrSet(m237_coinObjTbl[i]->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
    for (i = 0; i < 3; i++) {
        s32 files[3] = { 2, 3, 4 };

        object->model[i] = Hu3DModelRead(files[i] | 0x460000, 0x4BD);
    }
    object->model[20] = Hu3DModelRead(0x460005, 0x4BD);
    Hu3DModelCameraSet(object->model[20], HU3D_CAM_NONE);
    Hu3DModelScaleSet(object->model[20], 0.666666f, 0.666666f, 0.666666f);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            ((MgMapWork *)m237_platObjTbl[i][j]->data)->unk04 = i * 3 + j + 1;
            for (k = 0; k < 3; k++) {
                m237_platObjTbl[i][j]->model[k + 1] = Hu3DModelLink(m237_mdlObj->model[j]);
                Hu3DModelAttrSet(m237_platObjTbl[i][j]->model[k + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelScaleSet(m237_platObjTbl[i][j]->model[k + 1], 0.666666f, 0.666666f, 0.666666f);
                Hu3DModelCameraSet(m237_platObjTbl[i][j]->model[k + 1], m237_cameraBitTbl[i]);
            }
        }
    }
    object->model[3] = Hu3DModelRead(0xA011A, 0x4BD);
    Hu3DMotionAttrSet(object->model[3], 2, 2);
    Hu3DModelPosSet(object->model[3], 0.0f, 4500.0f, 300.0f);
    Hu3DModelScaleSet(object->model[3], 0.5f, 0.5f, 0.5f);
    for (i = 0; i < 4; i++) {
        if (i == 0 || i == 3) {
            object->model[i + 4] = Hu3DModelRead(i == 3 ? 0x460001 : 0x460000, 0x4B9);
        } else {
            object->model[i + 4] = Hu3DModelLink(object->model[4]);
        }
        Hu3DModelCameraSet(object->model[i + 4], HU3D_CAM0 | HU3D_CAM1 | HU3D_CAM2 | HU3D_CAM3);
        Hu3DMotionAttrSet(object->model[i + 4], 1, 1);
        Hu3DModelPosSet(object->model[i + 4], 0.0f, i * 1120.0 - 9.0, -300.0f);
        Hu3DModelScaleSet(object->model[i + 4], 0.75f, 0.75f, 0.75f);
    }
    object->func = m237_MdlObjMain;
}

void m237_MdlObjMain(omObjData *object) {
    m237_BackDraw();
    if (m237_phase == 3) {
        if (m237_phaseTimer == 1) {
            Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelCameraSet(object->model[3], m237_cameraBitTbl[m237_winner]);
        }
        if (m237_phaseTimer != 0 && m237_phaseTimer < 46) {
            f32 t = m237_phaseTimer / 45.0f;

            t = (1.0f - t) * (1.0f - t);
            Hu3DModelPosSet(object->model[3], 0.0f, t * 700.0f + 4430.0, 300.0f);
        }
    }
    omPauseChk();
}

void m237_BackDraw(void) {
    s32 groups[4] = { 3, 2, 1, 0 };
    s32 lefts[4] = { 0, 93, 161, 229 };
    s32 rights[4] = { 92, 160, 228, 320 };
    s32 texLefts[4] = { 0, 25, 25, 25 };
    s32 zoomLefts[4] = { 0, 0, 0, 0 };
    s32 zoomRights[4] = { 320, 320, 320, 320 };
    s32 zoomTexLefts[4] = { 0, 0, 0, 0 };
    u8 order[4] = { 0, 1, 2, 3 };
    s32 curLefts[4] = { 0, 93, 161, 229 };
    s32 curRights[4] = { 92, 160, 228, 320 };
    HuSprite *sprite;
    HuSprAnimPat *frame;
    f32 t = 0.0f;
    f32 a;
    f32 b;
    f32 scale;
    s32 left;
    s32 right;
    s32 y;
    s32 yEnd;
    s32 offset;
    s32 xl;
    s32 xh;
    s32 yl;
    s32 yh;
    s32 s;
    s32 dsdx;
    s16 player;
    s16 i;
    s16 j;
    s16 k;

    if (m237_winner < 4) {
        for (i = 0, k = 0; i < 4; i++) {
            if (m237_winner == i) {
                if (m237_phase == 4 && m237_phaseTimer < 30) {
                    t = 1.0f - m237_phaseTimer / 29.0f;
                    t = ((1.0f - t) + 1.0f - t * t * t) * 0.5;
                } else if (m237_phase == 7 ||
                           (m237_phase == 4 && m237_phaseTimer >= 30)) {
                    t = 1.0f;
                }
            } else {
                order[k++] = i;
            }
        }
        order[k] = m237_winner;
    }
    if (t > 0.0f) {
        a = 1.0f - t;
        b = 1.0f - a;
        scale = ((a * 160.0f + b * 320.0f) - (a * 93.0f + b * 0.0f)) / (a * 67.0f + b * 113.0f);
        left = curLefts[m237_winner] =
            lefts[m237_winner] * a + zoomLefts[m237_winner] * b;
        right = curRights[m237_winner] =
            rights[m237_winner] * a + zoomRights[m237_winner] * b;
        ScissorSet(m237_winner, left, 0.0f, right, 240.0f);
        ViewportSet(m237_winner, scale * 320.0f * 2.0f, scale * 240.0f * 2.0f, 511.0f,
                    ((m237_winner * 68 + 59) * a + b * 160.0f) * 4.0f, 480.0f, 511.0f);
        CenterM[m237_winner].y = a * m237_cameraYTbl[m237_winner] + b * 4605.0f;
        for (i = 0; i < 4; i++) {
            if (m237_winner != i) {
                if (i < m237_winner) {
                    curLefts[i] = MIN(left, curLefts[i]);
                    curRights[i] = MIN(left, curRights[i]);
                } else {
                    curLefts[i] = MAX(right, curLefts[i]);
                    curRights[i] = MAX(right, curRights[i]);
                }
            }
        }
    }
    gSPDisplayList(gMainGfxPos++, m237_gfxBackInit);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    for (i = 3; i >= 0; i--) {
        sprite = HuSprGet(esprite[m237_backSprTbl[groups[i]]].unk04, 0);
        frame = &sprite->data->pat[sprite->patNo];
        for (j = 0; j < 9; j++) {
            y = j * 16;
            yEnd = (y + 17 > 130) ? 130 : y + 17;
            if (i != 0) {
                gDPLoadTextureTile(gMainGfxPos++, (u8 *)frame->data + y * 114, G_IM_FMT_CI, G_IM_SIZ_8b, 114, 0, 0, 0,
                                   114, yEnd - y, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gDPLoadTLUT_pal256(gMainGfxPos++, sprite->data->pal);
            } else {
                gDPLoadTextureTile_4b(gMainGfxPos++, (u8 *)frame->data + y * 57, G_IM_FMT_CI, 114, 0, 0, 0, 114,
                                      yEnd - y, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                      G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
            }
            for (k = 0; k < 4; k++) {
                player = order[k];
                if (t > 0.0f) {
                    if (curLefts[player] == curRights[player]) {
                        continue;
                    }
                    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, curLefts[player], 0,
                                  curRights[player] - ((player == m237_winner) ? 1 : 0), 240);
                }
                if (player == m237_winner) {
                    a = 1.0f - t;
                    b = 1.0f - a;
                } else {
                    a = 1.0f;
                    b = 0.0f;
                }
                offset = (m237_cameraYTbl[player] - 650.0f) / 3850.0 * -284.0 + 284.0;
                xl = (lefts[player] * a + zoomLefts[player] * b) * 4.0f;
                xh = (rights[player] * a + zoomRights[player] * b) * 4.0f;
                yl = ((y + i * 131 - offset - 120) * (a + b * 2.83185840707964598) + 120.0) * 4.0;
                yh = ((yEnd + 2 + i * 131 - offset - 120) * (a + b * 2.83185840707964598) + 120.0) * 4.0 - 1.0;
                if ((xl > 1280) | (xh < 0)) {
                    continue;
                }
                if ((yl > 960) | (yh < 0)) {
                    continue;
                }
                s = (texLefts[player] * a + zoomTexLefts[player] * b) * 32.0;
                dsdx = (a * 67.0f + b * 113.0f) / ((a * 160.0f + b * 320.0f) - (a * 93.0f + b * 0.0f)) * 1024.0;
                gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, s, 0, dsdx, dsdx);
            }
        }
    }
    for (i = 0; i < 4; i++) {
        ScissorSet(i, curLefts[i], 0.0f, curRights[i], 240.0f);
    }
}

void m237_PlayerInit(omObjData *object, s32 model, s32 motion, u16 group, f32 x, f32 y, f32 z) {
    s32 chrDirs[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
    s32 attr1 = 0x4B9;
    s32 attr2 = 0x49D;
    u16 chr = m237_groupPlayerTbl[group]->chr;
    MgPlayerWork *data;
    s32 i;

    MgPlayerParamReset();
    MgPlayerCreate(object, model, motion, m237_groupPlayerTbl[group]->player, attr1, attr2);
    Hu3DModelCameraSet(object->model[0], m237_cameraBitTbl[group]);
    data = object->data;
    data->unk59 = m237_groupPlayerTbl[group]->player;
    data->unk50 |= 0x400;
    data->unk4C = 1.0f;
    data->unkB4 = 1.0f;
    object->model[6] = Hu3DModelRead(5, 0x80D);
    Hu3DModelCameraSet(object->model[6], m237_cameraBitTbl[group]);
    Hu3DModelCameraSet(object->model[9], m237_cameraBitTbl[group]);
    m237_groupPlayerTbl[group]->unk08 = (rand8() & 1) ? 0x2F : 0x30;
    object->model[10] = Hu3DModelRead(CharMotionDataNumGet(chr, m237_groupPlayerTbl[group]->unk08), attr1 | 4);
    m237_groupPlayerTbl[group]->unk08 |= chrDirs[chr] << 16;
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(chr, 0), 1, 0);
    MgPlayerMotLoad(object, 1, CharMotionDataNumGet(chr, 1), 1, 0);
    MgPlayerMotLoad(object, 2, CharMotionDataNumGet(chr, 2), 1, 0);
    MgPlayerMotLoad(object, 6, CharMotionDataNumGet(chr, 4), 1, 19);
    MgPlayerMotLoad(object, 17, CharMotionDataNumGet(chr, 14), 1, 15);
    MgPlayerMotRead(object, 21, CharMotionDataNumGet(chr, 31), 0, 0);
    MgPlayerMotRead(object, 30, CharMotionDataNumGet(chr, 32), 2, 0);
    MgPlayerMotRead(object, 31, CharMotionDataNumGet(chr, 33), 2, 0);
    MgPlayerMotRead(object, 32, CharMotionDataNumGet(chr, 34), 0, 0);
    MgPlayerMotLoad(object, 14, CharMotionDataNumGet(chr, 58), 1, 120);
    object->trans.x = x;
    object->trans.y = y;
    object->trans.z = z;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    for (i = 0; i < 12; i++) {
        MgPlayerMapAttrSet(object, i + 1, 1);
    }
    MgPlayerMapAttrSet(object, 0, 2);
    MgPlayerMapAttrSet(object, group * 3 + 1, 2);
    MgPlayerMapAttrSet(object, group * 3 + 2, 2);
    MgPlayerMapAttrSet(object, group * 3 + 3, 2);
}

void m237_Player0ObjInit(omObjData *object) {
    s8 chr = m237_groupPlayerTbl[0]->chr;
    s32 motion = omCharModelNoTbl[chr][1];
    s32 model = omCharModelNoTbl[chr][0];

    m237_PlayerInit(object, model, motion, 0, 0.0f, 0.0f, 0.0f);
    object->func = m237_PlayerObjMain;
}

void m237_Player1ObjInit(omObjData *object) {
    s8 chr = m237_groupPlayerTbl[1]->chr;
    s32 motion = omCharModelNoTbl[chr][1];
    s32 model = omCharModelNoTbl[chr][0];

    m237_PlayerInit(object, model, motion, 1, 0.0f, 0.0f, 0.0f);
    object->func = m237_PlayerObjMain;
}

void m237_Player2ObjInit(omObjData *object) {
    s8 chr = m237_groupPlayerTbl[2]->chr;
    s32 motion = omCharModelNoTbl[chr][1];
    s32 model = omCharModelNoTbl[chr][0];

    m237_PlayerInit(object, model, motion, 2, 0.0f, 0.0f, 0.0f);
    object->func = m237_PlayerObjMain;
}

void m237_Player3ObjInit(omObjData *object) {
    s8 chr = m237_groupPlayerTbl[3]->chr;
    s32 motion = omCharModelNoTbl[chr][1];
    s32 model = omCharModelNoTbl[chr][0];

    m237_PlayerInit(object, model, motion, 3, 0.0f, 0.0f, 0.0f);
    object->func = m237_PlayerObjMain;
}

void m237_PlayerObjMain(omObjData *object) {
    AwfulTowerPlayer *player;
    s16 savedBtn;
    u16 savedBtn2;
    u16 savedBtn3;
    s8 savedStickX;
    s8 savedStickY;
    s16 savedStick2;
    s16 savedStick3;
    MgPlayerWork *data = object->data;
    s16 group = m237_playerGroupTbl[data->unk59];
    u8 savedCB70 = 0xFF;
    u8 platTypes[16] = { 0, 2, 1, 1, 0, 0, 2, 1, 2, 2, 1, 0, 1, 2, 2, 0 };
    f32 platBaseY[16] = { 45.0f, 250.0f, 615.0f, 950.0f, 1100.0f, 1350.0f, 1600.0f, 1800.0f,
                          2150.0f, 2450.0f, 2850.0f, 3150.0f, 3400.0f, 3700.0f, 3950.0f, 4500.0f };
    u8 platCols[16] = { 0, 1, 2, 1, 0, 1, 2, 0, 1, 0, 1, 2, 1, 0, 2, 1 };
    u8 nearPlats[7] = { -1, -1, -1, -1, -1, -1, -1 };
    f32 nearDists[7] = { 32000.0f, 32000.0f, 32000.0f, 32000.0f, 32000.0f, 32000.0f, 32000.0f };
    u8 closePlats[3] = { -1, -1, -1 };
    f32 closeDists[3] = { 32000.0f, 32000.0f, 32000.0f };
    u8 coinNear[5];
    MgPlayerWork *work;
    f32 dist;
    f32 vx;
    f32 vy;
    f32 wave;
    s32 i;
    s32 j;
    s32 k;

    player = m237_groupPlayerTbl[group];
    if (m237_phase == 5 && m237_phaseTimer == 1) {
        m237_endPlatNoTbl[group] = m237_platNoTbl[group];
        data->unk3C = 0.0f;
    }
    if (group == 0) {
        s16 periods[3] = { 60, 60, 60 };
        f32 offsets[3];
        f32 amplitudes[3] = { 150.0f, 200.0f, 300.0f };

        if (m237_frameCnt == 40) {
            for (i = 0; i < 15; i++) {
                m237_platMoveTbl[i] = 0.0f;
            }
            for (i = 0; i < 55; i++) {
                m237_waveTbl[i] = -1.0f;
            }
        }
        for (i = 0; i < 3; i++) {
            offsets[i] = ((m237_frameCnt % periods[i] < periods[i] / 2)
                              ? (m237_frameCnt % periods[i]) * 2.0
                              : (periods[i] - m237_frameCnt % periods[i]) * 2.0) /
                         periods[i] * amplitudes[i];
        }
        for (i = 0; i < 15; i++) {
            m237_platYTbl[i] =
                platBaseY[i] + (((i & 1) == 0) ? offsets[platTypes[i]]
                                               : amplitudes[platTypes[i]] - offsets[platTypes[i]]);
            m237_platMoveTbl[i] += m237_platYTbl[i];
        }
    }
    savedBtn = HuPadBtn[player->pad];
    savedBtn2 = HuPadBtnDown[player->pad];
    savedBtn3 = HuPadBtnRep[player->pad];
    savedStickX = HuPadStkX[player->pad];
    savedStickY = HuPadStkY[player->pad];
    savedStick2 = HuPadStkXSum[player->pad];
    savedStick3 = HuPadStkYSum[player->pad];
    HuPadStkY[player->pad] = HuPadStkYSum[player->pad] = 0;
    if (m237_ridePlatTbl[group] != 0 && m237_platMoveTbl[m237_ridePlatTbl[group]] < 0.0f) {
        object->trans.y += m237_platMoveTbl[m237_ridePlatTbl[group]];
        m237_squeezePlatTbl[group] = m237_ridePlatTbl[group];
        if (data->unk38 < 0.0) {
            data->unk38 = 0.25f;
        }
    }
    if (m237_squeezePlatTbl[group] != 0 && m237_ridePushTbl[group] == 0) {
        if (object->trans.y + 155.0f >= m237_platYTbl[m237_squeezePlatTbl[group]] - 50.0f) {
            object->trans.y = -155.0f + m237_platYTbl[m237_squeezePlatTbl[group]] - 50.0f;
        }
    }
    for (i = 0; i < 15; i++) {
        dist = ABS(m237_platYTbl[i] - m237_cameraYTbl[group]);
        for (j = 0; j < 7; j++) {
            if (dist < nearDists[j]) {
                for (k = 5; k >= j; k--) {
                    nearPlats[k + 1] = nearPlats[k];
                    nearDists[k + 1] = nearDists[k];
                }
                nearPlats[j] = i;
                nearDists[j] = dist;
                break;
            }
        }
    }
    for (i = 0; i < 7; i++) {
        dist = ABS(m237_platYTbl[nearPlats[i]] - (object->trans.y + 75.0));
        for (j = 0; j < 3; j++) {
            if (dist < closeDists[j]) {
                for (k = 2; k >= j; k--) {
                    closePlats[k + 1] = closePlats[k];
                    closeDists[k + 1] = closeDists[k];
                }
                closePlats[j] = nearPlats[i];
                closeDists[j] = dist;
                break;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        omSetTra(m237_platObjTbl[group][i], platCols[closePlats[i]] * 150 - 150,
                 m237_platYTbl[closePlats[i]], 0.0f);
        if (closePlats[i] == 0) {
            MgMapBlockSet(m237_platObjTbl[group][i], 50.0f, 300.0f, -150.0f, -50.0f, 50.0f, 50.0f);
        } else {
            MgMapBlockSet(m237_platObjTbl[group][i], 50.0f, 100.0f, -50.0f, -50.0f, 50.0f, 50.0f);
        }
        for (j = 0; j < 3; j++) {
            Hu3DModelAttrSet(m237_platObjTbl[group][i]->model[j + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
        if (group == 0) {
            Hu3DModelAttrSet(m237_mdlObj->model[20], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelCameraSet(m237_mdlObj->model[20], HU3D_CAM_NONE);
        }
    }
    {
        u8 counts[3] = { 0, 0, 0 };

        for (i = 0; i < 7; i++) {
            j = nearPlats[i];
            k = platTypes[j];
            if (counts[k] < 3) {
                if (j == 14) {
                    Hu3DModelPosSet(m237_mdlObj->model[20], platCols[j] * 150 - 150,
                                    m237_platYTbl[j], 0.0f);
                    Hu3DModelAttrSet(m237_mdlObj->model[20], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DData[m237_mdlObj->model[20]].cameraBit |= m237_cameraBitTbl[group];
                } else {
                    Hu3DModelPosSet(m237_platObjTbl[group][k]->model[counts[k] + 1],
                                    platCols[j] * 150 - 150, m237_platYTbl[j], 0.0f);
                    Hu3DModelAttrSet(m237_platObjTbl[group][k]->model[counts[k] + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                }
                counts[k]++;
            }
        }
    }
    if (m237_shotYTbl[group] > -1000.0f) {
        MgPlayerWork *hitData;
        f32 dx;
        f32 dy;

        m237_shotVelYTbl[group] -= 4.0f;
        m237_shotXTbl[group] += m237_shotVelXTbl[group];
        m237_shotYTbl[group] += m237_shotVelYTbl[group];
        m237_shotRotTbl[group] += m237_shotRotSpeedTbl[group];
        Hu3DModelPosSet(m237_mdlObj->model[group + 16], m237_shotXTbl[group],
                        m237_shotYTbl[group], 0.0f);
        Hu3DModelRotSet(m237_mdlObj->model[group + 16], 0.0f, 0.0f, m237_shotRotTbl[group]);
        dx = m237_shotXTbl[group] - object->trans.x;
        dy = (m237_shotYTbl[group] - object->trans.y - 75.0f) / 2.0;
        if (m237_shotActiveTbl[group] != 0.0f && (m237_phase == 2 || m237_phase == 6) &&
            dx * dx + dy * dy < 3600.0f) {
            hitData = object->data;
            hitData->unk3C = (object->trans.y > 3500.0f) ? 90.0f : -90.0f;
            MgPlayerMotSet(object, 30);
            if (hitData->unk38 == 1000.0f) {
                hitData->unk40 = -mgPlayerSpeedMax;
            } else {
                hitData->unk40 = -mgPlayerSpeedMax;
                hitData->unk38 = -mgPlayerJumpPower * 0.6f;
            }
            MgPlayerEffSet(object, 6, (m237_shotXTbl[group] + object->trans.x) / 2.0,
                                   (m237_shotYTbl[group] + object->trans.y + 75.0f) / 2.0, 0.0f, 0.0f,
                                   180.0f);
            PlayerFXPlay(0x286, hitData->unk59);
            MgPlayerSePlay(hitData, 8);
            omVibrate(hitData->unk59, 2, 2, 20);
            m237_shotActiveTbl[group] = 0.0f;
        }
    }
    if (Hu3DData[object->model[6]].motTime >= 10.0f) {
        Hu3DData[object->model[6]].motTime = 0.0f;
        Hu3DModelAttrSet(object->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    if (player->cpuDifficulty != -1 ||
        (m237_winner == group && m237_phase == 3 && m237_phaseTimer >= 50)) {
        u8 chances[4] = { 8, 9, 12, 14 };
        u8 jitters[4] = { 18, 11, 6, 4 };
        u8 chance;

        if (player->cpuDifficulty != -1) {
            chance = chances[player->cpuDifficulty];
        } else {
            chance = 16;
        }
        if (m237_frameCnt % 60 == 0) {
            m237_comJitterTbl[group] =
                (player->cpuDifficulty != -1)
                    ? rand8() % jitters[player->cpuDifficulty] - jitters[player->cpuDifficulty] / 2
                    : 0;
        }
        HuPadBtn[player->pad] = 0;
        HuPadBtnDown[player->pad] = 0;
        HuPadBtnRep[player->pad] = 0;
        HuPadStkX[player->pad] = 0;
        HuPadStkY[player->pad] = 0;
        HuPadStkXSum[player->pad] = 0;
        HuPadStkYSum[player->pad] = 0;
        if (m237_comJumpTimerTbl[group] != 0 && m237_platNoTbl[group] != -1 &&
            m237_platNoTbl[group] != m237_comTargetTbl[group] - 1 &&
            m237_platNoTbl[group] != m237_comTargetTbl[group]) {
            m237_comJumpTimerTbl[group] = 0;
        }
        if (m237_phase == 2) {
            if (m237_frameCnt % 60 ==
                m237_comJumpTimeTbl[m237_platNoTbl[group]] +
                    ((m237_platNoTbl[group] % 2 != 0) ? 20 : 50) + m237_comJitterTbl[group]) {
                if (m237_comJumpTimerTbl[group] == 0 ||
                    m237_platNoTbl[group] == m237_comTargetTbl[group]) {
                    if (m237_platNoTbl[group] != -1) {
                        m237_comMissCntTbl[group] += (m237_comMissCntTbl[group] < 5) ? 1 : 0;
                    }
                }
            }
        }
        if (m237_phase == 2) {
            if ((rand8() & 15) < chance || m237_comMissCntTbl[group] >= 5) {
                if (m237_frameCnt % 60 ==
                    m237_comJumpTimeTbl[m237_platNoTbl[group]] +
                        ((m237_platNoTbl[group] % 2 != 0) ? 20 : 50) + m237_comJitterTbl[group]) {
                    if (m237_comJumpTimerTbl[group] == 0 ||
                        m237_platNoTbl[group] == m237_comTargetTbl[group]) {
                        if (m237_platNoTbl[group] != -1) {
                            m237_comJumpTimerTbl[group] = 1;
                            m237_comTargetTbl[group] = m237_platNoTbl[group] + 1;
                            m237_comMissCntTbl[group] = 0;
                        }
                    }
                }
            }
        }
        if (m237_phase == 3 && m237_winner == group && m237_frameCnt % 60 == 27 &&
            m237_phaseTimer >= 40) {
            if (m237_comJumpTimerTbl[group] == 0 ||
                m237_platNoTbl[group] == m237_comTargetTbl[group]) {
                if (m237_platNoTbl[group] == 15) {
                    m237_comJumpTimerTbl[group] = 1;
                    m237_comTargetTbl[group] = m237_platNoTbl[group] + 1;
                    m237_winCenterTimer = 1;
                    m237_winStartX = object->trans.x;
                }
            }
        }
        if (m237_comJumpTimerTbl[group] == m237_comHoldTbl[m237_comTargetTbl[group] - 1] + 3) {
            HuPadBtn[player->pad] |= A_BUTTON;
            HuPadBtnDown[player->pad] = A_BUTTON;
        } else if (m237_comJumpTimerTbl[group] > m237_comHoldTbl[m237_comTargetTbl[group] - 1] + 3) {
            HuPadBtn[player->pad] |= A_BUTTON;
        }
        if (m237_comJumpTimerTbl[group] != 0) {
            f32 dx = (platCols[m237_comTargetTbl[group] - 1] * 150 - 150) * 1.125 - object->trans.x;

            HuPadStkX[player->pad] = (dx > 30.0f)    ? 60
                                           : (dx > 15.0f)  ? dx / 7.5 - 1.0
                                           : (dx < -30.0f) ? -60
                                           : (dx < -15.0f) ? dx / 7.5 + 1.0
                                                           : 0;
            HuPadStkXSum[player->pad] = HuPadStkX[player->pad] * 2;
            m237_comJumpTimerTbl[group]++;
            m237_comJumpTimerTbl[group] %= 60;
            if (HuPadStkX[player->pad] == 0 && m237_platNoTbl[group] == m237_comTargetTbl[group]) {
                m237_comJumpTimerTbl[group] = 0;
            }
        }
        if (m237_platNoTbl[group] == 0) {
            if (object->trans.x < -40.0f) {
                m237_comJumpTimerTbl[group] = 0;
                HuPadStkX[player->pad] = 60;
                HuPadStkXSum[player->pad] = HuPadStkX[player->pad] * 2;
            }
            if (m237_platNoTbl[group] == 0 && object->trans.x > 20.0f) {
                m237_comJumpTimerTbl[group] = 0;
                HuPadStkX[player->pad] = -60;
                HuPadStkXSum[player->pad] = HuPadStkX[player->pad] * 2;
            }
        }
        if (m237_phase == 3 && m237_winner == group) {
            savedCB70 = m237_mgFlow.state;
            m237_mgFlow.state = MG_STATE_PLAY;
            data->unk4C = 0.5f;
            data->unkB4 = 1.5f;
        }
    }
    if (m237_winner == group &&
        ((m237_phase >= 4 && object->trans.y >= 4550.0f) ||
         (m237_phase == 3 && m237_phaseTimer >= 30))) {
        omSetTra(m237_platObjTbl[m237_winner][2], 0.0f, 4500.0f, 0.0f);
        closePlats[2] = 15;
        closeDists[2] = 4500.0f;
    }
    if (m237_platNoTbl[group] == 15 && (m237_phase != 3 || m237_phaseTimer < 30)) {
        HuPadStkX[player->pad] = 0;
        HuPadStkXSum[player->pad] = 0;
        HuPadBtn[player->pad] &= ~A_BUTTON;
        HuPadBtnDown[player->pad] &= ~A_BUTTON;
        HuPadBtnRep[player->pad] &= ~A_BUTTON;
    }
    if (m237_wallDirTbl[group] != 0) {
        if (m237_wallDirTbl[group] == ((HuPadStkX[player->pad] < 0)   ? -1
                                              : (HuPadStkX[player->pad] > 0) ? 1
                                                                                   : 0)) {
            m237_wallDirTbl[group] = 0;
            HuPadStkX[player->pad] = 0;
            HuPadStkXSum[player->pad] = 0;
        }
    }
    for (i = 0; i < 5; i++) {
        MgItemWork *coin = m237_coinObjTbl[i]->data;

        coinNear[i] = ABS(m237_coinObjTbl[i]->trans.y - (object->trans.y + 160.0)) < 200.0;
        coin->unk54 = m237_coinStatTbl[group][i] && coinNear[i];
        coin->unk48 = (data->unk38 != 1000.0f) ? 59.0f : 40.0f;
        if (i == 0 && object->trans.x > 55.0f && object->trans.y > 1275.0f && object->trans.y < 1425.0f &&
            data->unk38 >= 1.0f && data->unk38 < 1000.0f) {
            coin->unk48 = 90.0f;
        }
        if (i == 2 && object->trans.x > 55.0f && object->trans.y > 2300.0f && object->trans.y < 2450.0f &&
            data->unk38 >= 1.0f && data->unk38 < 1000.0f) {
            coin->unk48 = 90.0f;
        }
        if (i == 3 && object->trans.x < -55.0f && object->trans.y > 3300.0f && object->trans.y < 3500.0f &&
            data->unk38 >= 1.0f && data->unk38 < 1000.0f) {
            coin->unk48 = 90.0f;
        }
    }
    if (m237_squeezePlatTbl[group] != 0) {
        HuPadBtn[player->pad] &= ~A_BUTTON;
    }
    if (!(m237_winner < 4 &&
          (m237_phase == 7 || (m237_phase == 4 && m237_phaseTimer >= 30)))) {
        MgPlayerObjMain(object);
    }
    if (m237_phase == 3 && m237_winCenterTimer >= 12) {
        HuAudFXStop(data->unkC5);
    }
    if (m237_phase == 3 && group == m237_winner && m237_winCenterTimer != 0) {
        f32 scales[18] = { 1.0f, 1.0f, 1.0f, 0.909788f, 0.819576f, 0.729364f,
                           0.639153f, 0.548941f, 0.458729f, 0.368517f, 0.278305f, 0.188094f,
                           0.097882f, 0.00767f, 0.005113f, 0.002557f, 0.0f, 0.0f };

        object->trans.x = m237_winStartX * scales[m237_winCenterTimer - 1];
        m237_winCenterTimer = (m237_winCenterTimer == 18) ? 0 : m237_winCenterTimer + 1;
    }
    if (savedCB70 != 0xFF) {
        m237_mgFlow.state = savedCB70;
    }
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    for (i = 0; i < 3; i++) {
        if (data->unk38 != 1000.0f && ABS(object->trans.x - m237_platObjTbl[group][i]->trans.x) < 110.0f &&
            ABS(object->trans.y + 75.0f - m237_platObjTbl[group][i]->trans.y) < 125.0f) {
            s32 facing = data->unk3C >= 0.0f && data->unk3C < 180.0f;
            s32 side = m237_platObjTbl[group][i]->trans.x < object->trans.x;

            if (facing == side) {
                m237_wallDirTbl[group] = facing * 2 - 1;
            }
        }
    }
    for (i = 0; i < 5; i++) {
        MgItemWork *coin = m237_coinObjTbl[i]->data;
        s32 cameras;

        if (m237_coinStatTbl[group][i] != 0 && coinNear[i] != 0 && coin->unk54 == 0) {
            EffectGroupModel *effect = EffectGroupData[m237_starEffTbl[group]]->models;

            EffectGroupEmit(m237_starEffTbl[group], m237_coinObjTbl[i]->trans.x,
                               m237_coinObjTbl[i]->trans.y, m237_coinObjTbl[i]->trans.z);
            Hu3DModelCameraSet(effect->model, m237_cameraBitTbl[group]);
            m237_coinStatTbl[group][i] = 0;
        } else if (m237_coinStatTbl[group][i] != 0 &&
                   ABS(m237_coinObjTbl[i]->trans.y - m237_cameraYTbl[group]) > 900.0f) {
            m237_coinStatTbl[group][i] = 2;
        } else if (m237_coinStatTbl[group][i] == 2) {
            m237_coinStatTbl[group][i] = 1;
        }
        if (group == 3) {
            cameras = ((m237_coinStatTbl[0][i] == 1) ? m237_cameraBitTbl[0] : 0) |
                      ((m237_coinStatTbl[1][i] == 1) ? m237_cameraBitTbl[1] : 0) |
                      ((m237_coinStatTbl[2][i] == 1) ? m237_cameraBitTbl[2] : 0) |
                      ((m237_coinStatTbl[3][i] == 1) ? m237_cameraBitTbl[3] : 0);
            Hu3DModelAttrSet(m237_coinObjTbl[i]->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelCameraSet(m237_coinObjTbl[i]->model[0], cameras);
        }
    }
    if (m237_endPlatNoTbl[group] > 0 && (u16)MgPlayerMotNoGet(object) == 14) {
        object->trans.y = m237_platYTbl[m237_endPlatNoTbl[group] - 1] + 50.0f;
    }
    work = object->data;
    if (work->unk38 != 1000.0f && work->unk53[3] != 0 && work->unk53[3] != -1 && m237_bonkTbl[group] == -1) {
        HuAudPlayerFXPlay(player->chr + 203, work->unk59);
    }
    m237_bonkTbl[group] = (work->unk53[3] != 0) ? work->unk53[3] - 1 : -1;
    m237_ridePlatTbl[group] =
        (work->unk53[3] != 0 && work->unk53[3] != -1) ? closePlats[(work->unk53[3] - 1) % 3] : 0;
    if (work->unk53[3] >= 0 && work->unk53[0] >= 0 &&
        m237_ridePlatTbl[group] == closePlats[(work->unk53[0] - 1) % 3] && m237_ridePlatTbl[group] < 15) {
        m237_ridePlatTbl[group]++;
        m237_ridePushTbl[group] = 1;
    } else {
        m237_ridePushTbl[group] = 0;
    }
    if (work->unk38 == 1000.0f) {
        m237_squeezePlatTbl[group] = 0;
    }
    work->unk53[3] = -1;
    m237_platNoTbl[group] = -1;
    if (work->unk53[0] >= 0) {
        m237_platNoTbl[group] = (work->unk53[0] != 0) ? closePlats[(work->unk53[0] - 1) % 3] + 1 : 0;
        if (m237_platNoTbl[group] == 16) {
            m237_goalCnt += (m237_goalCnt < 255) ? 1 : 0;
        }
        i = (work->unk53[0] != 0) ? closePlats[(work->unk53[0] - 1) % 3] : 0;
        if (m237_phase == 2 && (m237_flyerStateTbl[group] == 0 || m237_flyerStateTbl[group] == 3) &&
            i % 5 == 2) {
            if (m237_flyerStateTbl[group] == 0) {
                m237_flyerXTbl[group] = 0.0f;
                m237_flyerVelXTbl[group] = 0.0f;
                m237_flyerVelYTbl[group] = -20.0f;
                m237_flyerYTbl[group] = m237_cameraYTbl[group] + 900.0f;
                Hu3DModelAttrSet(m237_mdlObj->model[group + 8], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            m237_flyerStateTbl[group] = 1;
            m237_flyerPosNoTbl[group] = i / 5;
            Hu3DModelScaleSet(m237_mdlObj->model[group + 8],
                              (m237_flyerPosNoTbl[group] != 3) ? -6.0525f : 6.0525f, 6.0525f, 6.0525f);
            Hu3DModelScaleSet(m237_mdlObj->model[group + 12],
                              (m237_flyerPosNoTbl[group] != 3) ? -6.0525f : 6.0525f, 6.0525f, 6.0525f);
        }
        if (m237_flyerStateTbl[group] == 2 && (i % 5 == 0 || i % 5 == 4)) {
            m237_flyerStateTbl[group] = 3;
        }
    }
    if (object->trans.x <= -50.0f && object->trans.y < 15.0f) {
        object->trans.x = -40.0f;
    }
    if (work->unk38 != 1000.0) {
        work->unk4C = (work->unk38 < -0.05) ? 0.5f : 1.0f;
        work->unkB4 = (work->unk38 < -0.05) ? 1.5f : 1.0f;
        m237_groundXTbl[group] = object->trans.x;
    } else {
        work->unk4C = 1.0f;
        work->unkB4 = 1.0f;
        m237_groundXTbl[group] = 32000.0f;
    }
    if (m237_flyerStateTbl[group] != 0) {
        f32 targetY = 0.0f;
        f32 heights[3] = { 1550.0f, 2650.0f, 3850.0f };
        f32 targetX;
        s32 frame;

        targetX = 0.0f;
        switch (m237_flyerStateTbl[group]) {
            case 1:
                targetX = (m237_flyerPosNoTbl[group] != 3) ? 100.0f : -100.0f;
                targetY = heights[m237_flyerPosNoTbl[group]];
                if (m237_phase != 2) {
                    m237_flyerStateTbl[group] = 3;
                } else if (m237_flyerYTbl[group] <= targetY + 100.0f) {
                    m237_flyerStateTbl[group] = 2;
                } else {
                    break;
                }
            case 2:
                targetX = (m237_flyerPosNoTbl[group] != 3) ? 100.0f : -100.0f;
                targetY = heights[m237_flyerPosNoTbl[group]];
                i = ((m237_flyerPosNoTbl[group] == 0)   ? 33
                     : (m237_flyerPosNoTbl[group] == 1) ? 10
                                                            : 41) -
                    m237_flyerDelayTbl[group];
                frame = (i < 0) ? i + 60 : i;
                if (m237_frameCnt % 60 == frame && m237_flyerThrowTbl[group] == 0) {
                    m237_flyerThrowTbl[group] = 1;
                    m237_flyerDelayTbl[group] += (m237_flyerDelayTbl[group] < 30) ? 5 : 0;
                    Hu3DSprModelReset(m237_flyerSprTbl[group][1]);
                    Hu3DModelAttrSet(m237_mdlObj->model[group + 8], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
                if (m237_phase != 2) {
                    m237_flyerStateTbl[group] = 3;
                }
            case 3:
                if (m237_cameraYTbl[group] + 900.0f <= m237_flyerYTbl[group] ||
                    m237_flyerXTbl[group] >= 700.0f || m237_flyerXTbl[group] <= -700.0f) {
                    m237_flyerThrowTbl[group] = 0;
                    m237_flyerStateTbl[group] = 0;
                    m237_flyerDelayTbl[group] = 0;
                    Hu3DModelAttrSet(m237_mdlObj->model[group + 8], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(m237_mdlObj->model[group + 12], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                } else if (m237_flyerStateTbl[group] == 3) {
                    targetX = (m237_flyerPosNoTbl[group] == 2) ? -1000.0f : 1000.0f;
                    targetY = m237_cameraYTbl[group] + 1200.0f;
                }
                break;
        }
        // Bug: tests the array address instead of m237_flyerStateTbl[group], so this is always true.
        if ((u32)m237_flyerStateTbl != 0) {
            wave = m237_waveTbl[m237_frameCnt % 55];
            vx = (targetX - m237_flyerXTbl[group]) / 8.0f;
            vx = (vx < -22.0f) ? -22.0f : (vx > 22.0f) ? 22.0f
                                                       : vx;
            vy = (targetY - m237_flyerYTbl[group]) / 12.0f;
            vy = (vy < -27.0f) ? -27.0f : (vy > 27.0f) ? 27.0f
                                                       : vy;
            m237_flyerVelXTbl[group] = (vx < m237_flyerVelXTbl[group])
                                                ? ((m237_flyerVelXTbl[group] - 2.5 < vx) ? vx : m237_flyerVelXTbl[group] - 2.5)
                                                : ((m237_flyerVelXTbl[group] + 2.5 > vx) ? vx : m237_flyerVelXTbl[group] + 2.5);
            m237_flyerVelYTbl[group] = (vy < m237_flyerVelYTbl[group])
                                                ? ((m237_flyerVelYTbl[group] - 2.5 < vy) ? vy : m237_flyerVelYTbl[group] - 2.5)
                                                : ((m237_flyerVelYTbl[group] + 2.5 > vy) ? vy : m237_flyerVelYTbl[group] + 2.5);
            m237_flyerXTbl[group] += m237_flyerVelXTbl[group];
            m237_flyerYTbl[group] += m237_flyerVelYTbl[group];
            if (wave == -1.0f) {
                wave = m237_waveTbl[m237_frameCnt % 55] =
                    cosdf(m237_frameCnt % 55 / 55.0 * 360.0);
            }
            Hu3DModelPosSet(m237_mdlObj->model[group + 8], m237_flyerXTbl[group],
                            m237_flyerYTbl[group] + wave * 15.0f, 0.0f);
            Hu3DModelPosSet(m237_mdlObj->model[group + 12], m237_flyerXTbl[group],
                            m237_flyerYTbl[group] + wave * 15.0f, 0.0f);
            if (m237_flyerThrowTbl[group] != 0) {
                if (m237_flyerThrowTbl[group] == 12) {
                    m237_flyerThrowTbl[group] = 0;
                    Hu3DSprModelReset(m237_flyerSprTbl[group][0]);
                    Hu3DModelAttrSet(m237_mdlObj->model[group + 12], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                } else {
                    m237_flyerThrowTbl[group]++;
                    if (m237_flyerThrowTbl[group] == 8 && m237_shotYTbl[group] <= -1000.0f) {
                        m237_shotActiveTbl[group] = 1.0f;
                        m237_shotXTbl[group] = m237_flyerXTbl[group];
                        m237_shotYTbl[group] = m237_flyerYTbl[group];
                        m237_shotVelXTbl[group] = m237_shotVelXInitTbl[m237_flyerPosNoTbl[group]];
                        m237_shotVelYTbl[group] = m237_shotVelYInitTbl[m237_flyerPosNoTbl[group]];
                        m237_shotRotTbl[group] = 0.0f;
                        m237_shotRotSpeedTbl[group] = (m237_flyerPosNoTbl[group] != 3) ? 23.0f : -23.0f;
                        Hu3DModelAttrSet(m237_mdlObj->model[group + 16], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        Hu3DModelPosSet(m237_mdlObj->model[group + 16], m237_shotXTbl[group],
                                        m237_shotYTbl[group], 0.0f);
                        Hu3DModelRotSet(m237_mdlObj->model[group + 16], 0.0f, 0.0f,
                                        m237_shotRotTbl[group]);
                    }
                }
            }
        }
    }
    if (m237_ridePlatTbl[group] != 0) {
        if (object->trans.x < 5.0f && object->trans.x > 0.0f) {
            if (object->trans.x - m237_prevXTbl[group] < -20.0f &&
                m237_prevXTbl[group] - m237_prevX2Tbl[group] > 10.0f) {
                object->trans.x = m237_prevXTbl[group];
            }
        }
        if (object->trans.x > -5.0f && object->trans.x < 0.0f) {
            if (object->trans.x - m237_prevXTbl[group] > 20.0f &&
                m237_prevXTbl[group] - m237_prevX2Tbl[group] < -10.0f) {
                object->trans.x = m237_prevXTbl[group];
            }
        }
    }
    m237_prevX2Tbl[group] = m237_prevXTbl[group];
    m237_prevXTbl[group] = object->trans.x;
    object->trans.x = (object->trans.x < -175.0f)  ? -175.0f
                      : (object->trans.x > 175.0f) ? 175.0f
                                                   : object->trans.x;
    if (object->trans.y > m237_cameraYTbl[group]) {
        m237_cameraYTbl[group] = object->trans.y;
    }
    if (object->trans.y < m237_cameraYTbl[group] - 300.0f) {
        m237_cameraYTbl[group] = object->trans.y + 300.0f;
    }
    if (m237_cameraYTbl[group] < 650.0f) {
        m237_cameraYTbl[group] = 650.0f;
    }
    object->trans.z = 0.0f;
    if (m237_phase == 0 && m237_phaseTimer < 91) {
        if (m237_phaseTimer < 76) {
            m237_cameraYTbl[group] = (1.0f - m237_phaseTimer / 75.0f) * 3625.0f + 1025.0f;
        }
        if (m237_phaseTimer >= 76) {
            f32 t = 1.0f - (m237_phaseTimer - 75) / 15.0f;

            m237_cameraYTbl[group] = t * 375.0f * t + 650.0f;
        }
    }
    if (m237_shotYTbl[group] > -1000.0f &&
        (m237_shotYTbl[group] < m237_cameraYTbl[group] - 850.0f ||
         m237_shotYTbl[group] > m237_cameraYTbl[group] + 850.0f)) {
        m237_shotYTbl[group] = -1000.0f;
        Hu3DModelAttrSet(m237_mdlObj->model[group + 16], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    CenterM[group].y = m237_cameraYTbl[group];
    HuPadBtn[player->pad] = savedBtn;
    HuPadBtnDown[player->pad] = savedBtn2;
    HuPadBtnRep[player->pad] = savedBtn3;
    HuPadStkX[player->pad] = savedStickX;
    HuPadStkY[player->pad] = savedStickY;
    HuPadStkXSum[player->pad] = savedStick2;
    HuPadStkYSum[player->pad] = savedStick3;
    if (group == 3) {
        m237_frameCnt++;
        for (i = 0; i < 15; i++) {
            m237_platMoveTbl[i] = -m237_platYTbl[i];
        }
        if (m237_winner == 5) {
            s32 best = -1;
            s32 bestIdx = -1;

            for (i = 0; i < 4; i++) {
                if (m237_platNoTbl[i] == 15 && m237_topXTbl[i] <= m237_playerObjTbl[i]->trans.x) {
                    j = rand8();
                    if (best < j) {
                        bestIdx = i;
                        best = j;
                    }
                }
            }
            if (bestIdx >= 0) {
                m237_winner = bestIdx;
                if (m237_playerObjTbl[m237_winner]->trans.x < 105.0) {
                    m237_playerObjTbl[m237_winner]->trans.x = 105.0f;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            if (m237_platNoTbl[i] == 15) {
                m237_topXTbl[i] = m237_playerObjTbl[i]->trans.x;
            } else {
                m237_topXTbl[i] = 1000.0f;
            }
        }
    }
}

void m237_MdlAnimTimeSet(s16 arg0, s16 arg1) {
    HmfModel *hmfModel = &Hu3DData[arg0];

    hmfModel->hmf->unk98->unk08 = (f32)arg1;
}
