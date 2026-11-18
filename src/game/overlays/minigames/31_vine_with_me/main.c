#include "ultra64.h"
#include "game/overlays/minigame.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/hu3d.h"
#include "game/object.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/wipe.h"
#include "include_asm.h"
#include "game/camsetup.h"
#include "game/hmfspr.h"
#include "game/gamework.h"
#include "macros.h"

// EXTERN

// camsetup

// hmfspr

// 8EA10

// 8EFF0

// 8FB20

// pad
extern u16 HuPadBtnDown[];

// save

// unknown
extern u16 omSysExitReq;

extern Gfx *gMainGfxPos;

// LOCAL

typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ s8 unk03;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ char unk05[1];
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0C */ s32 unk0C;
} VineWithMePlayer; // Size 0x10

// Required to align BSS.
typedef struct {
    s16 unk00[17];
    u8 unk22[8];
} VineWithMeSprWork;

void m249_MainObjInit(omObjData *arg0);
void m249_MainObjMain(omObjData *arg0);
void m249_StageObjInit(omObjData *arg0);
void m249_StageObjMain(omObjData *arg0);
void m249_BackDraw(void);
void m249_HudDraw(Gfx **arg0, s32 arg1, s32 arg2);
void m249_Player0ObjInit(omObjData *arg0);
void m249_Player1ObjInit(omObjData *arg0);
void m249_PlayerInit(omObjData *arg0, s8 arg1, s32 arg2);
void m249_Player0ObjMain(omObjData *arg0);
void m249_Player1ObjMain(omObjData *arg0);
void m249_PlayerUpdate(omObjData *arg0, s8 arg1, s8 arg2);

static f32 m249_swingAngleTbl[2];
static f32 m249_jumpVelXTbl[2];
static f32 m249_jumpVelYTbl[2];
static f32 m249_prevXTbl[2];
static f32 m249_prevYTbl[2];
static f32 m249_fallXTbl[2];
static f32 m249_fallCameraXTbl[2];
static f32 m249_respawnCameraXTbl[2];
static f32 m249_vineXTbl[4][9][14];
static f32 m249_vineYTblBase[4][9][14];
static f32 m249_vineYTbl[4][9][14];
static f32 m249_vineAngleTblBase[4][9][14];
static f32 m249_vineAngleTbl[8][9][14];
static VineWithMePlayer m249_playerTbl[2];
static VineWithMePlayer *m249_playerPtrTbl[4];
static f32 m249_iconPosTbl[2];
static s8 m249_iconMoveTimerTbl[4];
static s32 m249_farTileNoTbl[2];
static s32 m249_ambientSeNo;
static f32 m249_viewScaleInv;
static u8 m249_viewScaleInvPad[4]; // unused?
static s16 m249_sprAnimTbl[17];
static omObjData *m249_playerObjTbl[2];
static s8 m249_winner;
static u8 m249_splashAnimOfsTbl[8];
static u8 m249_splashTypeTbl[8];
static omObjData *m249_stageObj;
static s32 m249_nearTileNoTbl[2];
static f32 m249_viewCenterY;
static u8 m249_exitTimer;
static f32 m249_viewCenterX;
static u16 m249_exitF;
// Original sizes unknown; split to keep each array below the assembler's
// 0x10-byte minimum 8-byte alignment for common symbols.
static u8 m249_exitFPad[0xC]; // unused?
static u8 m249_exitFPadB[8];   // unused?
static s32 m249_seqTimer;
static u8 m249_seqTimerPad[4]; // unused?
static f32 m249_scrollTbl[2][4];
static s8 m249_goalTurnTimerTbl[2];
static s16 m249_fallF;
static f32 m249_iconPosPrevTbl[2];
static f32 m249_viewScale;
static f32 m249_viewOfsX;
static f32 m249_introOfsY;
static f32 m249_splashXTbl[8];
static HmfModelSet *m249_splashMotBakeTbl[2];
static f32 m249_viewOfsY;
static s16 m249_seqNo;
static VineWithMeSprWork m249_sprWork;
static s32 m249_seqTimerPrev;
static u8 m249_groupPlayerTbl[8];
static u32 m249_splashTimerTbl[8];

MinigameFlow m249_mgFlow = { 0 };

u32 m249_seqTimeTbl[] = { 102, 60, -1, -1, -1, -1, 300 };

u32 m249_introTimer = 0;

// TODO: the following arrays work but trigger multiple warnings: "missing braces around initializer"
// Ideally we should use these and remove the u32 arrays below.
/*
Gfx m249_gfxXluInit[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTHI, SCREEN_HEIGHTI),
    gsSPEndDisplayList()
};

Gfx m249_gfxOpaInit[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTHI, SCREEN_HEIGHTI),
    gsSPEndDisplayList()
};
*/

u32 m249_gfxXluInit[] = {
    0xE7000000, 0x00000000, 0xE3000A01, 0x00000000, 0xFCFFFFFF, 0xFFFCF279, 0xE200001C, 0x00504240,
    0xE2001E01, 0x00000000, 0xE3000C00, 0x00000000, 0xE3001201, 0x00002000, 0xED000000, 0x005003C0,
    0xDF000000, 0x00000000
};

u32 m249_gfxOpaInit[] = {
    0xE7000000, 0x00000000, 0xE3000A01, 0x00000000, 0xFCFFFFFF, 0xFFFCF279, 0xE200001C, 0x00552048,
    0xE2001E01, 0x00000000, 0xE3000C00, 0x00000000, 0xE3001201, 0x00002000, 0xED000000, 0x005003C0,
    0xDF000000, 0x00000000
};

u8 m249_hudSkipF = 0;

s8 m249_vineLenTbl[][6] = {
    { 6, 6, 5, 7, 5, 4 },
    { 6, 4, 6, 4, 5, 6 }
};

s8 m249_vineNoTbl[] = { 0, 0, 0, 0 };
s8 m249_playerStateTbl[] = { 1, 1, 0, 0 };
s8 m249_vineParityTbl[] = { 0, 0, 0, 0 };
s8 m249_courseVineTbl[] = { 6, 6, 5, 7, 5, 4, 7, 8, 7, 6, 5, 4, 5, 6, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0 };
s8 m249_vineBaseTbl[] = { 0, 0, 0, 0 };
f32 m249_cameraXTbl[] = { 0.0f, 0.0f };
f32 m249_playerXTbl[] = { 0.0f, 0.0f };
f32 m249_playerYTbl[] = { 0.0f, 0.0f };
f32 m249_vineSegPosTbl[] = { 6.0f, 6.0f };
f32 m249_fallTimerTbl[] = { 0.0f, 0.0f };
u8 m249_goalAssistF = 0;
f32 m249_cameraSpeedTbl[] = { 0.0f, 0.0f };
u8 m249_blinkTimerTbl[] = { 0, 0, 0, 0 };
u8 m249_holdTimeTbl[] = { 0, 0, 0, 0 };
s8 m249_vineEndTbl[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
u32 m249_frameCnt = 0;

const s16 m249_fontMesTbl[] = {
    0x8260, 0x8261, 0x8262, 0x8263, 0x8264, 0x8265, 0x8266, 0x8267,
    0x8268, 0x8269, 0x826A, 0x826B, 0x826C, 0x826D, 0x826E, 0x826F,
    0x8270, 0x8271, 0x8272, 0x8273, 0x8274, 0x8275, 0x8276, 0x8277,
    0x8278, 0x8279, 0x0000, 0x0000
};

void m249_ObjectSetup(void) {
    omObjData *temp_v0;
    omObjData *temp_v0_2;

    Hu3DSprModelInit(0x20);
    omInitObjMan(50, 0);
    omGameSysInit();
    Hu3DScreenClearF = 1;
    CamSetupInit(2);
    CamSetupMapCullAddMulti(2);
    ScissorSet(0, 0.0f, 0.0f, SCREEN_WIDTH, 120.0f);
    ScissorSet(1, 0.0f, 120.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 240.0f, 511.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 640.0f, 720.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 22.619865f, 1000.0f, 22000.0f);
    Hu3DCameraPerspectiveSet(1, 22.619865f, 1000.0f, 22000.0f);
    Hu3DGLightMaxSet(2);
    Hu3DGLightDirSet(0, 0.0f, 0.0f, 90.0f);
    Hu3DGLightColorSet(0, 0x90, 0x90, 0x90);
    Hu3DGLightDirSet(1, 0.0f, 65.0f, 90.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    CenterM[0].x = 0.0f;
    CenterM[0].y = -300.0f;
    CenterM[0].z = 0.0f;
    CRotM[0].x = 0.0f;
    CRotM[0].y = 0.0f;
    CRotM[0].z = 0.0f;
    CZoomM[0] = 3750.0f;
    CenterM[1].x = 0.0f;
    CenterM[1].y = -270.0f;
    CenterM[1].z = 0.0f;
    CRotM[1].x = 0.0f;
    CRotM[1].y = 0.0f;
    CRotM[1].z = 0.0f;
    CZoomM[1] = 3750.0f;
    omAddObj(0, 0, 0, -1, m249_MainObjInit);
    temp_v0 = omAddObj(8, 23, 23, -1, m249_StageObjInit);
    m249_stageObj = temp_v0;
    omSetStatBit(temp_v0, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    m249_playerObjTbl[0] = omAddObj(3, 26, 7, -1, m249_Player0ObjInit);
    m249_playerObjTbl[1] = omAddObj(3, 26, 7, -1, m249_Player1ObjInit);
    temp_v0_2 = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    temp_v0_2->work[0] = 2;
    omSetStatBit(temp_v0_2, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    GMesFontMesCreate(m249_fontMesTbl, 1);
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
    m249_mgFlow.type = MINIGAME_BATTLE;
    m249_mgFlow.startDelay = -1;
    m249_mgFlow.timer = 5400;
    m249_mgFlow.timeDisp = MG_TIME_DISP_NONE;
    m249_mgFlow.timerMode = MG_TIMER_COUNT_DOWN;
    m249_mgFlow.finishDelay = 60;
    m249_mgFlow.resultDelay = 165;
    m249_mgFlow.newRecord = FALSE;
    m249_mgFlow.gauge = MG_GAUGE_NONE;
    m249_mgFlow.timeLimit = -1;
    MgFlowInit(&m249_mgFlow);
}

void m249_MainObjInit(omObjData *arg0) {
    s32 var_s0;

    m249_exitF = 0;
    m249_seqNo = 0;
    m249_seqTimerPrev = 0;
    m249_seqTimer = 0;
    m249_winner = 0;
    m249_exitTimer = 0;
    m249_scrollTbl[0][0] = m249_scrollTbl[1][0] = 1000.0f;
    m249_scrollTbl[0][1] = m249_scrollTbl[1][1] = 700.0f;
    m249_scrollTbl[0][2] = m249_scrollTbl[1][2] = 0.0f;
    m249_scrollTbl[0][3] = m249_scrollTbl[1][3] = 450.0f;
    m249_nearTileNoTbl[0] = m249_nearTileNoTbl[1] = 0;
    m249_farTileNoTbl[0] = m249_farTileNoTbl[1] = 0;
    m249_iconPosTbl[0] = m249_iconPosTbl[1] = 0.0f;
    m249_iconPosPrevTbl[0] = m249_iconPosPrevTbl[1] = 0.0f;
    m249_iconMoveTimerTbl[0] = m249_iconMoveTimerTbl[1] = 0;
    m249_introOfsY = 0.0f;
    m249_goalTurnTimerTbl[0] = m249_goalTurnTimerTbl[1] = 0;
    m249_viewScaleInv = 1.0f;
    m249_viewScale = 1.0f;
    m249_viewCenterY = 0.5f;
    m249_viewCenterX = 0.5f;
    m249_ambientSeNo = -1;
    for (var_s0 = 0; var_s0 < 2; var_s0++) {
        m249_playerPtrTbl[var_s0] = &m249_playerTbl[var_s0];
        bzero(m249_playerPtrTbl[var_s0], sizeof(VineWithMePlayer));
    }
    m249_groupPlayerTbl[0] = m249_groupPlayerTbl[1] = 4;
    for (var_s0 = 0; var_s0 < 4; var_s0++) {
        s32 temp_v1 = GwPlayer[var_s0].group;

        if (temp_v1 < 2) {
            if (m249_groupPlayerTbl[temp_v1] == 4) {
                m249_groupPlayerTbl[temp_v1] = var_s0;
            }
        }
    }
    for (var_s0 = 0; var_s0 < 2; var_s0++) {
        m249_playerPtrTbl[var_s0]->unk00 = var_s0;
        m249_playerPtrTbl[var_s0]->unk02 = GwPlayer[m249_groupPlayerTbl[var_s0]].pad;
        m249_playerPtrTbl[var_s0]->unk03 = GwPlayer[m249_groupPlayerTbl[var_s0]].chr;
        m249_playerPtrTbl[var_s0]->unk01 = var_s0;
        m249_playerPtrTbl[var_s0]->unk04 = (GwPlayer[m249_groupPlayerTbl[var_s0]].stat & 1) ? GwPlayer[m249_groupPlayerTbl[var_s0]].cpu_difficulty : -1;
    }
    Hu3DHookFuncCreate(0, m249_HudDraw, 2);
    arg0->func = m249_MainObjMain;
}

void m249_MainObjMain(omObjData *arg0) {
    s32 temp_s1;
    u8 var_a0;

    m249_seqTimerPrev = m249_seqTimer;
    m249_seqTimer++;
    m249_fallF = 0;
    CenterM[0].x = 0.0f;
    CenterM[0].y = -300.0f;
    CenterM[0].z = 0.0f;
    CenterM[1].x = 0.0f;
    CenterM[1].y = -270.0f;
    CenterM[1].z = 0.0f;
    if (m249_seqTimer >= m249_seqTimeTbl[m249_seqNo]) {
        m249_seqTimer = m249_seqTimer - m249_seqTimeTbl[m249_seqNo];
        m249_seqNo++;
    }
    switch (m249_seqNo) {
        case 1:
        case 5:
            break;
        case 0:
            if (m249_seqTimer == 1 && m249_exitF == 0 && omSysExitReq == 0) {
                m249_ambientSeNo = HuAudFXPlay(0x495);
            }
            if (m249_seqTimer == 28 && m249_exitF == 0 && omSysExitReq == 0) {
                HuAudSeqPlay(0x30);
            }
            if (m249_seqTimer == 30) {
                MgFlowStatNext();
            }
            break;
        case 2:
            if (m249_mgFlow.timer == 900) {
                GMesCreate(GMES_MES_TIMER, 0x1F, 0xA0, 0x18);
                m249_mgFlow.timeDisp = MG_TIME_DISP_COUNTDOWN;
            }
            if (m249_winner == 0) {
                break;
            }
            m249_seqNo = 3;
            m249_seqTimer = 0;
            /* fallthrough */
        case 3:
            if (m249_seqTimer < m249_seqTimerPrev) {
                MgFlowStatNext();
                m249_winner--;
                m249_mgFlow.resultType = MG_RESULT_WIN_1;
                m249_mgFlow.winners[0] = m249_groupPlayerTbl[m249_winner];
            }
            if (m249_seqTimer == 2 && m249_seqTimer != m249_winner) {
                MgFlowResultWaitSet(0x1E);
            }
            if (m249_seqTimer == 15 && m249_ambientSeNo != -1) {
                HuAudFXFadeOut(m249_ambientSeNo, 0xF);
                m249_ambientSeNo = -1;
            }
            break;
        case 4:
            temp_s1 = m249_seqTimer;
            if (temp_s1 == 1) {
                Hu3DData[m249_playerObjTbl[m249_winner]->model[1]].pos.x = m249_playerObjTbl[m249_winner]->trans.x;
                Hu3DData[m249_playerObjTbl[m249_winner]->model[1]].pos.y = m249_playerObjTbl[m249_winner]->trans.y;
                Hu3DData[m249_playerObjTbl[m249_winner]->model[1]].pos.z = m249_playerObjTbl[m249_winner]->trans.z;
                Hu3DData[m249_playerObjTbl[m249_winner]->model[1]].rot.x = m249_playerObjTbl[m249_winner]->rot.x;
                Hu3DData[m249_playerObjTbl[m249_winner]->model[1]].rot.y = m249_playerObjTbl[m249_winner]->rot.y;
                Hu3DData[m249_playerObjTbl[m249_winner]->model[1]].rot.z = m249_playerObjTbl[m249_winner]->rot.z;
                Hu3DModelAttrSet(m249_playerObjTbl[m249_winner]->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelAttrSet(m249_playerObjTbl[m249_winner]->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                GwPlayer[m249_groupPlayerTbl[m249_winner]].bonusCoin = 10;
                if (m249_goalTurnTimerTbl[1 - m249_winner] != 0) {
                    Hu3DMotionModelSet(m249_playerObjTbl[temp_s1 - m249_winner]->model[0], m249_playerObjTbl[temp_s1 - m249_winner]->motion[6]);
                }
            }
            if (m249_seqTimer == 30) {
                s32 sp12[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

                CharAnimSet(m249_playerObjTbl[m249_winner]->model[1], 1, sp12[m249_playerPtrTbl[m249_winner]->unk03], m249_playerPtrTbl[m249_winner]->unk08);
                Hu3DMotionModelSet(m249_playerObjTbl[m249_winner]->model[1], m249_playerObjTbl[m249_winner]->motion[5]);
                HuAudCharVoicePlay(m249_playerPtrTbl[m249_winner]->unk0C);
            }
            break;
    }
    MgFlowMain();
    switch (m249_seqNo) {
        case 2:
            if (m249_winner != 0 || MgFlowStatGet() != MG_STATE_FINISH) {
                break;
            }
            m249_seqNo = 3;
            m249_seqTimer = 0;
            m249_winner = 2;
            m249_mgFlow.resultType = MG_RESULT_DRAW;
            m249_mgFlow.finishDelay = 90;
            m249_mgFlow.resultDelay = 144;
            /* fallthrough */
        case 3:
            if (MgFlowStatGet() == MG_STATE_RESULT) {
                m249_seqNo = (m249_winner == 2) ? 5 : 4;
                m249_seqTimer = 0;
            }
            break;
        case 4:
        case 5:
            if (MgFlowStatGet() != MG_STATE_EXIT) {
                break;
            }
            m249_seqNo = 6;
            m249_seqTimer = 0;
            /* fallthrough */
        case 6:
            if (m249_seqTimer < m249_seqTimerPrev) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 0x14);
            } else if (m249_seqTimer >= 32) {
                m249_exitF = 1;
            }
            break;
    }
    // TODO: why 2U?
    if (_CheckFlag(FLAG_MG_PRACTICE) && omSysExitReq == 0 && m249_exitTimer == 0 && m249_seqNo == 2U) {
        for (var_a0 = 0; var_a0 < 2; var_a0++) {
            if (m249_playerPtrTbl[var_a0]->unk04 == -1 && (HuPadBtnDown[m249_playerPtrTbl[var_a0]->unk02] & R_TRIG)) {
                m249_exitTimer = 1;
            }
        }
    }
    if (m249_exitF == 0 && omSysExitReq == 0 && m249_exitTimer == 0) {
        return;
    }
    if (omSysExitReq != 0 && m249_exitTimer == 0) {
        m249_exitTimer = 1;
    }
    if (m249_exitTimer != 0) {
        if (m249_exitTimer == 1) {
            WipeCreateOut(WIPE_TYPE_NORMAL, 0x14);
            HuAudSeqFadeOut(0x14);
            HuAudFXAllFadeOut(0x14);
        }
        m249_exitTimer++;
        if (m249_exitTimer < 25) {
            return;
        }
    }
    HuAudSeqFadeOut(0x1E);
    Hu3DMotionBakeFree(m249_splashMotBakeTbl[0]);
    Hu3DMotionBakeFree(m249_splashMotBakeTbl[1]);
    omOvlReturnEx(1);
}

void m249_StageObjInit(omObjData *arg0) {
    s32 sp10[] = {
        0x0052000D,
        0x0052000C,
        0x00520009,
        0x0052000A,
        0x0052000B,
        0x0052000E,
        0x00210008,
        0x00210009,
        0x0021000A,
        0x0021000B,
        0x0021000C,
        0x0021000D,
        0x0021000E,
        0x0021000F,
        0x0052000F,
        0x00520010,
        0x00520011
    };
    s16 var_s3;

    for (var_s3 = 0; var_s3 < 17; var_s3++) {
        m249_sprAnimTbl[var_s3] = HuSprAnimDataRead(sp10[var_s3]);
        m249_sprWork.unk00[var_s3] = espEntry(m249_sprAnimTbl[var_s3], 0, 0);
        espDispOff(m249_sprWork.unk00[var_s3]);
    }
    arg0->model[0] = Hu3DModelRead(0x520008, 0x23D);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    omSetTra(arg0, 1950.0f, 172.0f, 0.0f);
    omSetSca(arg0, 1.0f, 0.594f, 0.0f);
    omSetRot(arg0, 0.0f, 0.0f, 5.0f);
    arg0->model[1] = Hu3DModelLink(arg0->model[0]);
    Hu3DModelCameraSet(arg0->model[1], HU3D_CAM1);
    Hu3DModelPosSet(arg0->model[1], 1950.0f, 172.0f, 0.0f);
    Hu3DModelScaleSet(arg0->model[1], 1.0f, 0.594f, 0.0f);
    Hu3DModelRotSet(arg0->model[1], 0.0f, 0.0f, 5.0f);
    arg0->model[6] = Hu3DModelRead(8, 0xA3D);
    Hu3DModelCameraSet(arg0->model[6], HU3D_CAM0);
    Hu3DModelPosSet(arg0->model[6], 300.0f, -350.0f, 0.0f);
    arg0->model[7] = Hu3DModelLink(arg0->model[6]);
    Hu3DModelCameraSet(arg0->model[7], HU3D_CAM1);
    Hu3DModelPosSet(arg0->model[7], 300.0f, -350.0f, 0.0f);
    arg0->model[10] = Hu3DModelRead(0x520007, 0x23D);
    Hu3DModelCameraSet(arg0->model[10], HU3D_CAM0);
    Hu3DModelPosSet(arg0->model[10], 475.0f, -370.0f, 0.0f);
    arg0->model[11] = Hu3DModelLink(arg0->model[10]);
    Hu3DModelCameraSet(arg0->model[11], HU3D_CAM1);
    Hu3DModelPosSet(arg0->model[11], 475.0f, -370.0f, 0.0f);
    arg0->model[2] = Hu3DModelRead(0x520001, 0x619);
    Hu3DModelCameraSet(arg0->model[2], HU3D_CAM0);
    Hu3DModelPosSet(m249_stageObj->model[2], 375.0f, -375.0f, -250.0f);
    Hu3DModelScaleSet(m249_stageObj->model[2], 1.4375f, 1.4375f, 1.0f);
    arg0->model[3] = Hu3DModelLink(arg0->model[2]);
    Hu3DModelCameraSet(arg0->model[3], HU3D_CAM1);
    Hu3DModelPosSet(arg0->model[3], 375.0f, -375.0f, -250.0f);
    Hu3DModelScaleSet(arg0->model[3], 1.4375f, 1.4375f, 1.0f);
    arg0->model[8] = Hu3DModelRead(0x520006, 0x23D);
    Hu3DModelCameraSet(arg0->model[8], HU3D_CAM0);
    Hu3DModelPosSet(arg0->model[8], 475.0f, -300.0f, 0.0f);
    arg0->model[9] = Hu3DModelLink(arg0->model[8]);
    Hu3DModelCameraSet(arg0->model[9], HU3D_CAM1);
    Hu3DModelPosSet(arg0->model[9], 475.0f, -300.0f, 0.0f);
    arg0->model[4] = Hu3DModelRead(0x520002, 0x49D);
    Hu3DModelPosSet(arg0->model[4], 325.0f, -650.0f, 0.0f);
    Hu3DModelScaleSet(arg0->model[4], 0.5f, 0.5f, 1.0f);
    Hu3DMotionAttrSet(arg0->model[4], 3, 0);
    Hu3DModelCameraSet(arg0->model[4], HU3D_CAM0);
    arg0->model[5] = Hu3DModelLink(arg0->model[4]);
    Hu3DModelPosSet(arg0->model[5], 325.0f, -650.0f, 0.0f);
    Hu3DModelScaleSet(arg0->model[5], 0.5f, 0.5f, 1.0f);
    Hu3DMotionAttrSet(arg0->model[5], 3, 0);
    Hu3DModelCameraSet(arg0->model[5], HU3D_CAM1);
    for (var_s3 = 0; var_s3 < 8; var_s3++) {
        m249_splashTimerTbl[var_s3] = 90;
        m249_sprWork.unk22[var_s3] = 0;
        arg0->model[12 + var_s3] = Hu3DModelRead(0x520003, 0x6BD);
        Hu3DModelRotSet(arg0->model[12 + var_s3], 0.0f, 0.0f, 0.0f);
        Hu3DMotionAttrSet(arg0->model[12 + var_s3], 2, 2);
        Hu3DModelCameraSet(arg0->model[12 + var_s3], HU3D_CAM_NONE);
        Hu3DMotionReset(arg0->model[12 + var_s3]);
    }
    for (var_s3 = 0; var_s3 < 2; var_s3++) {
        s32 sp58[] = { 4, 5 };

        omObjMotionRead(arg0, var_s3, sp58[var_s3] | 0x520000);
        Hu3DMotionModelSet(arg0->model[12 + var_s3], arg0->motion[var_s3]);
        m249_splashMotBakeTbl[var_s3] = Hu3DMotionBake(arg0->model[12 + var_s3], 2);
        Hu3DModelKill(arg0->motion[var_s3]);
    }
    for (var_s3 = 0; var_s3 < 8; var_s3++) {
        Hu3DMotionModelSet(arg0->model[12 + var_s3], arg0->motion[0]);
    }
    arg0->func = m249_StageObjMain;
}

// TODO: doesn't work with -Wa,--vr4300mul-off.
void m249_StageObjMain(omObjData *arg0) {
    f32 temp_f12;
    f32 temp_fs1;
    f32 temp_f20;
    f32 temp_f20_4;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 var_f10;
    f32 var_f14;
    f32 var_f16;
    f32 var_f20;
    f32 var_f24;
    s32 temp_s0_4;
    s32 temp_a0_3;
    s32 temp_s2;
    s32 var_s1;

    if (m249_seqNo == 4 && m249_seqTimer < 0x1F) {
        m249_viewScale = (1.0f - m249_seqTimer / 30.0f) * 1.0 + (m249_seqTimer / 30.0f) * 2.375;
        m249_viewCenterX = (1.0f - m249_seqTimer / 30.0f) * 0.5 + (m249_seqTimer / 30.0f) * 0.77200000000000002;
        m249_viewCenterY = (1.0f - m249_seqTimer / 30.0f) * 0.5 + (m249_seqTimer / 30.0f) * (m249_winner != 0 ? 0.780000000000000027 : 0.220000000000000001);
        temp_f26 = m249_viewScale * SCREEN_WIDTH * 2.0f;
        temp_f24 = m249_viewScale * SCREEN_HEIGHT * 2.0f;
        var_f16 = -m249_viewCenterX * m249_viewScale + 0.5;
        var_f10 = -m249_viewCenterY * m249_viewScale + 0.5;
        var_f14 = var_f16 + m249_viewScale * 1.0;
        temp_f12 = var_f10 + m249_viewScale * 0.5;
        temp_fs1 = var_f16 + m249_viewScale * 0.5;
        temp_f20 = var_f10 + m249_viewScale * 0.25;
        var_f16 = (var_f16 < 0.0) ? 0.0f : (var_f16 > 1.0) ? 1.0f
                                                           : var_f16;
        var_f10 = (var_f10 < 0.0) ? 0.0f : (var_f10 > 1.0) ? 1.0f
                                                           : var_f10;
        var_f14 = (var_f14 < 0.0) ? 0.0f : (var_f14 > 1.0) ? 1.0f
                                                           : var_f14;
        temp_f12 = (temp_f12 < 0.0) ? 0.0f : (temp_f12 > 1.0) ? 1.0f
                                                              : temp_f12;
        var_f16 *= SCREEN_WIDTH;
        var_f10 *= SCREEN_HEIGHT;
        var_f14 *= SCREEN_WIDTH;
        temp_f12 *= SCREEN_HEIGHT;
        temp_fs1 *= 1280.0f;
        temp_f20 *= 960.0f;
        ScissorSet(0, var_f16, var_f10, var_f14, temp_f12);
        ViewportSet(0, temp_f26, temp_f24, 511.0f, temp_fs1, temp_f20, 511.0f);
        var_f16 = -m249_viewCenterX * m249_viewScale + 0.5;
        var_f10 = -m249_viewCenterY * m249_viewScale + 0.5;
        var_f14 = var_f16 + m249_viewScale * 1.0;
        temp_f12 = var_f10 + m249_viewScale * 1.0;
        temp_fs1 = var_f16 + m249_viewScale * 0.5;
        temp_f20 = var_f10 + m249_viewScale * 0.75;
        var_f10 += m249_viewScale * 0.5;
        var_f16 = (var_f16 < 0.0) ? 0.0f : (var_f16 > 1.0) ? 1.0f
                                                           : var_f16;
        var_f10 = (var_f10 < 0.0) ? 0.0f : (var_f10 > 1.0) ? 1.0f
                                                           : var_f10;
        var_f14 = (var_f14 < 0.0) ? 0.0f : (var_f14 > 1.0) ? 1.0f
                                                           : var_f14;
        temp_f12 = (temp_f12 < 0.0) ? 0.0f : (temp_f12 > 1.0) ? 1.0f
                                                              : temp_f12;
        var_f16 *= SCREEN_WIDTH;
        var_f10 *= SCREEN_HEIGHT;
        var_f14 *= SCREEN_WIDTH;
        temp_f12 *= SCREEN_HEIGHT;
        temp_fs1 *= 1280.0f;
        temp_f20 *= 960.0f;
        ScissorSet(1, var_f16, var_f10, var_f14, temp_f12);
        ViewportSet(1, temp_f26, temp_f24, 511.0f, temp_fs1, temp_f20, 511.0f);
    }
    m249_viewScaleInv = 1.0f / m249_viewScale;
    m249_viewOfsX = (-m249_viewCenterX * m249_viewScale + 0.5) * 320.0 * 4.0;
    m249_viewOfsY = (-m249_viewCenterY * m249_viewScale + 0.5) * 240.0 * 4.0;
    m249_BackDraw();
    if (omPauseChk() != 0) {
        return;
    }
    var_f20 = -300.0f;
    var_f24 = -375.0f;
    if (m249_seqNo == 0 && m249_seqTimer == 90) {
        m249_introTimer++;
    }
    if (m249_introTimer != 0 && m249_introTimer < 120) {
        Hu3DData[arg0->model[8]].pos.x = Hu3DData[arg0->model[10]].pos.x =
            Hu3DData[arg0->model[9]].pos.x = Hu3DData[arg0->model[11]].pos.x =
                Hu3DData[arg0->model[4]].pos.x = Hu3DData[arg0->model[5]].pos.x = 375.0f;
        Hu3DData[arg0->model[6]].pos.x = Hu3DData[arg0->model[7]].pos.x = 300.0f;
        if (m249_introTimer == 1) {
            Hu3DModelAttrSet(arg0->model[8], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg0->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg0->model[10], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg0->model[11], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        if (m249_introTimer == 4) {
            Hu3DMotionTimeSet(arg0->model[4], 0.0f);
            Hu3DMotionTimeSet(arg0->model[5], 0.0f);
            Hu3DModelAttrSet(arg0->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg0->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelLayerSet(m249_playerObjTbl[0]->model[0], 0x400);
            Hu3DModelLayerSet(m249_playerObjTbl[1]->model[0], 0x400);
        }
        if (m249_introTimer != 0 && m249_introTimer < 0xE) {
            temp_f22 = 1.0 - m249_introTimer / 13.0f;
            temp_f22 = 1.0f - temp_f22 * temp_f22;
            var_f24 = temp_f22 * 600.0 + -975.0;
            Hu3DModelPosSet(arg0->model[10], 375.0f, var_f24, 0.0f);
            Hu3DModelPosSet(arg0->model[11], 375.0f, var_f24, 0.0f);
            if (m249_introTimer != 0 && m249_introTimer < 0xE) {
                temp_f22 = 1.0 - m249_introTimer / 13.0f;
                temp_f22 = 1.0f - temp_f22 * temp_f22;
                var_f20 = temp_f22 * 700.0 + -1000.0;
                Hu3DModelPosSet(arg0->model[8], 375.0f, var_f20, 0.0f);
                Hu3DModelPosSet(arg0->model[9], 375.0f, var_f20, 0.0f);
            }
        }
        if (m249_introTimer >= 12 && m249_introTimer < 21) {
            f32 sp20[9] = { 80.0f, 90.0f, 110.0f, 110.0f, -20.0f, -10.0f, -20.0f, -15.0f, -20.0f };
            f32 sp48[9] = { -5.0f, -15.0f, -35.0f, -35.0f, -20.0f, -10.0f, -20.0f, -15.0f, -20.0f };
            f32 sp70[9] = { 0.0f, 0.0f, 0.0f, 0.0f, -31.0f, -20.0f, -31.0f, -25.0f, -31.0f };

            Hu3DModelPosSet(arg0->model[8], 375.0f, var_f20 - 75.0 + sp20[m249_introTimer - 12], 0.0f);
            Hu3DModelPosSet(arg0->model[9], 375.0f, var_f20 - 75.0 + sp20[m249_introTimer - 12], 0.0f);
            Hu3DModelPosSet(arg0->model[10], 375.0f, var_f24 + sp48[m249_introTimer - 12], 0.0f);
            Hu3DModelPosSet(arg0->model[11], 375.0f, var_f24 + sp48[m249_introTimer - 12], 0.0f);
            m249_introOfsY = sp70[m249_introTimer - 12];
            Hu3DData[arg0->model[2]].pos.y += ((m249_introOfsY + 0.75) / 15.0) * 16.0;
            Hu3DData[arg0->model[3]].pos.y += ((m249_introOfsY + 0.75) / 15.0) * 16.0;
        }
        if (m249_introTimer == 16) {
            Hu3DMotionTimeSet(arg0->model[6], 0.0f);
            Hu3DModelAttrSet(arg0->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(arg0->model[7], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelLayerSet(arg0->model[2], 0);
            Hu3DModelLayerSet(arg0->model[3], 0);
            Hu3DModelLayerSet(arg0->model[10], 0);
            Hu3DModelLayerSet(arg0->model[11], 0);
            HuAudFXPlay(0x491);
            omVibrate(m249_groupPlayerTbl[0], 2, 2, 0x14);
            omVibrate(m249_groupPlayerTbl[1], 2, 2, 0x14);
        }
        if (m249_introTimer >= 21 && m249_introTimer < 46) {
            m249_introOfsY = -31.25f;
            Hu3DData[arg0->model[2]].pos.y += -33.3333333333333357;
            Hu3DData[arg0->model[3]].pos.y += -33.3333333333333357;
        }
        if (m249_introTimer >= 46 && m249_introTimer < 86) {
            temp_f22 = (m249_introTimer - 45) / 40.0;
            temp_f22 = temp_f22 * temp_f22 * 0.75 + temp_f22 * 0.25;
            Hu3DModelPosSet(arg0->model[8], 375.0f, temp_f20_4 = -395.0 - temp_f22 * 600.0, 0.0f);
            Hu3DModelPosSet(arg0->model[9], 375.0f, temp_f20_4, 0.0f);
            Hu3DModelPosSet(arg0->model[10], 375.0f, temp_f20_4, 0.0f);
            Hu3DModelPosSet(arg0->model[11], 375.0f, temp_f20_4, 0.0f);
            m249_introOfsY = -30.0 - temp_f22 * 600.0;
            Hu3DData[arg0->model[2]].pos.y += (m249_introOfsY / 15.0) * 16.0;
            Hu3DData[arg0->model[3]].pos.y += (m249_introOfsY / 15.0) * 16.0;
        }
        if (m249_introTimer == 86) {
            Hu3DModelAttrSet(arg0->model[8], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(arg0->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(arg0->model[10], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(arg0->model[11], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(arg0->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(arg0->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
        if (++m249_introTimer == 120) {
            Hu3DModelAttrSet(arg0->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(arg0->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(arg0->model[7], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
        Hu3DData[arg0->model[8]].pos.x -= m249_iconMoveTimerTbl[2] * 450.0;
        Hu3DData[arg0->model[10]].pos.x -= m249_iconMoveTimerTbl[2] * 450.0;
        Hu3DData[arg0->model[9]].pos.x -= m249_iconMoveTimerTbl[3] * 450.0;
        Hu3DData[arg0->model[11]].pos.x -= m249_iconMoveTimerTbl[3] * 450.0;
        Hu3DData[arg0->model[6]].pos.x -= m249_iconMoveTimerTbl[2] * 450.0;
        Hu3DData[arg0->model[7]].pos.x -= m249_iconMoveTimerTbl[3] * 450.0;
        Hu3DData[arg0->model[4]].pos.x -= m249_iconMoveTimerTbl[2] * 450.0;
        Hu3DData[arg0->model[5]].pos.x -= m249_iconMoveTimerTbl[3] * 450.0;
    }
    for (var_s1 = 0; var_s1 < 8; var_s1++) {
        temp_s2 = m249_splashTimerTbl[var_s1];
        if (temp_s2 == 30) {
            Hu3DModelPosSet(arg0->model[12 + var_s1], m249_splashXTbl[var_s1], -840.0 - m249_sprWork.unk22[var_s1] * 30.0, 0.0f);
            Hu3DModelRotSet(arg0->model[12 + var_s1], 0.0f, ((rand8() & 0xFF) / 256.0) * 96.0 - 48.0 + ((m249_splashTypeTbl[var_s1] + 1) % 3 - 1) * 0.0, 0.0f);
            Hu3DMotionBakeApply(arg0->model[12 + var_s1], m249_splashMotBakeTbl[m249_splashTypeTbl[var_s1] == 3], 0);
            Hu3DMotionAttrSet(arg0->model[12 + var_s1], 2, 2);
            Hu3DModelAttrSet(arg0->model[12 + var_s1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelCameraSet(arg0->model[12 + var_s1], m249_sprWork.unk22[var_s1] != 0 ? HU3D_CAM1 : HU3D_CAM0);
        } else if (temp_s2 == 89) {
            Hu3DModelAttrSet(arg0->model[12 + var_s1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        } else if (temp_s2 >= 31 && temp_s2 < 36) {
            Hu3DModelPosSet(arg0->model[12 + var_s1], m249_splashXTbl[var_s1], -840.0 - m249_sprWork.unk22[var_s1] * 30.0 + (temp_s2 - 0x1E) * 40.0, 0.0f);
        } else if (temp_s2 >= 79) {
            Hu3DModelPosSet(arg0->model[12 + var_s1], m249_splashXTbl[var_s1], -640.0 - m249_sprWork.unk22[var_s1] * 30.0 - (temp_s2 - 79.0) * (temp_s2 - 79.0) - (temp_s2 - 0x4F) * 10.0, 0.0f);
        } else {
            Hu3DModelPosSet(arg0->model[12 + var_s1], m249_splashXTbl[var_s1], -640.0 - m249_sprWork.unk22[var_s1] * 30.0, 0.0f);
            Hu3DMotionTimeSet(arg0->model[12 + var_s1], temp_s2 - 30.0);
        }
        if (temp_s2 >= 31 && temp_s2 < 89) {
            temp_a0_3 = (temp_s2 - 30 + m249_splashAnimOfsTbl[var_s1] / 2) * 2;
            if (m249_splashTypeTbl[var_s1] == 3) {
                temp_s0_4 = temp_a0_3 / 60;
                temp_s0_4 = temp_a0_3 - temp_s0_4 * 60;
            } else {
                temp_s0_4 = temp_a0_3 / 74;
                temp_s0_4 = temp_a0_3 - temp_s0_4 * 74;
            }
            Hu3DMotionBakeApply(arg0->model[12 + var_s1], m249_splashMotBakeTbl[m249_splashTypeTbl[var_s1] == 3], temp_s0_4);
            if (m249_splashTypeTbl[var_s1] != 3 && m249_fallF == 0) {
                if (temp_s0_4 == 18 || temp_s0_4 == 38 || temp_s0_4 == 58) {
                    HuAudFXPlay(0x494);
                }
            }
        }
        m249_splashTimerTbl[var_s1] += (m249_splashTimerTbl[var_s1] < 90);
    }
    m249_iconMoveTimerTbl[0] -= (m249_iconMoveTimerTbl[0] > 0);
    m249_iconMoveTimerTbl[1] -= (m249_iconMoveTimerTbl[1] > 0);
}

void m249_BackDraw(void) {
    s32 widths[4] = { 150, 150, 150, 80 };
    s32 heights[4] = { 100, 100, 119, 119 };
    s32 spacing[4] = { 150, 150, 150, 144 };
    s32 scrollIdx[4] = { 0, 0, 1, 2 };
    s32 yOffsets[4] = { 19, 19, 0, 0 };
    s32 rowHeights[4] = { 12, 12, 12, 15 };
    s32 rowCounts[4] = { 9, 9, 10, 8 };
    s32 goalSide[2] = { 0 };
    f32 xPos[2][4] = { { 0.0f, 0.0f, 0.0f, 12.0f }, { 0.0f, 0.0f, 0.0f, 12.0f } };
    f32 scales[4] = { 0.05f, 0.05f, 0.1f, 0.16f };
    s32 sprites[4] = { 2, 4, 1, 0 };
    HuSprAnimPat *frame;
    HuSprite *sprite;
    s16 i;
    s16 pass;
    s16 row;
    s16 j;
    s16 k;
    s32 y1;
    s32 y2;
    s32 s;
    s32 dsdx;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            if (i != 1) {
                if (m249_scrollTbl[j][scrollIdx[i]] > spacing[i] / scales[i]) {
                    m249_scrollTbl[j][scrollIdx[i]] -= spacing[i] / scales[i];
                    m249_nearTileNoTbl[j] += (i == 3);
                    m249_farTileNoTbl[j] += (i == 0);
                }
                if (m249_scrollTbl[j][scrollIdx[i]] < 0.0) {
                    m249_scrollTbl[j][scrollIdx[i]] += spacing[i] / scales[i];
                    m249_nearTileNoTbl[j] -= (i == 3);
                    m249_farTileNoTbl[j] -= (i == 0);
                }
            }
            xPos[j][i] -= m249_scrollTbl[j][scrollIdx[i]] * scales[i];
        }
    }
    gSPDisplayList(gMainGfxPos++, m249_gfxXluInit);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    for (i = 0, pass = 0; i < 4; i++) {
        sprite = HuSprGet(esprite[m249_sprWork.unk00[(i != 0 || pass != 1) ? sprites[i] : 3]].unk04, 0);
        frame = &sprite->data->pat[sprite->patNo];
        if (i != 20) {
            gDPLoadTLUT_pal256(gMainGfxPos++, sprite->data->pal);
        } else {
            gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
        }
        for (row = 0; row < rowCounts[i]; row++) {
            if (i != 20) {
                gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_CI, G_IM_SIZ_8b, widths[i], 0, 0,
                                   row * rowHeights[i], widths[i], row * rowHeights[i] + rowHeights[i], 0,
                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            } else {
                gDPLoadTextureTile_4b(gMainGfxPos++, frame->data, G_IM_FMT_CI, widths[i], 0, 0, row * rowHeights[i],
                                      widths[i], row * rowHeights[i] + rowHeights[i], 0, G_TX_NOMIRROR | G_TX_WRAP,
                                      G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            }
            for (j = 0; j < 2; j++) {
                y1 = row * rowHeights[i];
                if (y1 > heights[i]) {
                    continue;
                }
                y2 = y1 + rowHeights[i] + 1;
                y2 = (y2 > heights[i]) ? heights[i] : y2;
                for (k = 0; k < 4; k++) {
                    s32 pos;
                    s32 layerIdx;

                    if (i == 0 && k + m249_farTileNoTbl[j] >= 3) {
                        continue;
                    }
                    layerIdx = i;
                    if (layerIdx == 0 && ((k + pass + m249_farTileNoTbl[j] + 16) & 1) == 0) {
                        continue;
                    }
                    if (i == 1 && k + m249_farTileNoTbl[j] < 3) {
                        continue;
                    }
                    if (i == 3) {
                        pos = k + m249_nearTileNoTbl[j];

                        if (pos == 0 || pos == 8) {
                            s32 side;

                            goalSide[j] = side = (pos == 8) ? 2 : 1;
                            continue;
                        }
                    }
                    if ((s32)((k * spacing[i] * 4 + (s32)(xPos[j][i] * 4.0f)) * m249_viewScale + m249_viewOfsX) >= 0xA00) {
                        continue;
                    }
                    if ((s32)((y1 + yOffsets[i] + j * 121) * 4 * m249_viewScale + m249_viewOfsY) >= 0x780) {
                        continue;
                    }
                    gSPScisTextureRectangle(gMainGfxPos++,
                                            (s32)((k * spacing[i] * 4 + (s32)(xPos[j][i] * 4.0f)) * m249_viewScale + m249_viewOfsX),
                                            (s32)((y1 + yOffsets[i] + j * 121) * 4 * m249_viewScale + m249_viewOfsY),
                                            (s32)(((k * spacing[i] + widths[i]) * 4 + (s32)(xPos[j][i] * 4.0f)) * m249_viewScale + m249_viewOfsX),
                                            (s32)((y2 + yOffsets[i] + j * 121) * 4 * m249_viewScale + m249_viewOfsY),
                                            0, 0, row * rowHeights[i] * 32, (s32)(m249_viewScaleInv * 1024.0f), (s32)(m249_viewScaleInv * 1024.0f));
                }
            }
        }
        if (i == 0 && pass == 0) {
            i--;
        } else if (i == 1) {
            gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
            gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 224);
        }
        pass++;
    }
    if (goalSide[0] != 0 || goalSide[1] != 0) {
        i = 3;
        sprite = HuSprGet(esprite[m249_sprWork.unk00[14]].unk04, 0);
        frame = &sprite->data->pat[sprite->patNo];
        gDPLoadTLUT_pal256(gMainGfxPos++, sprite->data->pal);
        for (row = 0; row < rowCounts[i]; row++) {
            gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_CI, G_IM_SIZ_8b, 54, 0, 0, row * rowHeights[i], 54,
                               row * rowHeights[i] + rowHeights[i], 0, G_TX_MIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            for (j = 0; j < 2; j++) {
                y1 = row * rowHeights[i];
                if (y1 > heights[i]) {
                    continue;
                }
                y2 = y1 + rowHeights[i] + 1;
                y2 = (y2 > heights[i]) ? heights[i] : y2;
                k = 0;
                do {
                    if (m249_nearTileNoTbl[j] + k == 0 || m249_nearTileNoTbl[j] + k == 8) {
                        if (goalSide[j] == 1) {
                            s = 0;
                            dsdx = 1024;
                        } else {
                            s = 54;
                            dsdx = -1024;
                        }
                        if ((s32)(((k * spacing[i] + 10 - ((goalSide[j] == 1) ? 12 : 0)) * 4 + (s32)(xPos[j][i] * 4.0f)) * m249_viewScale + m249_viewOfsX) < 0xA00 && (s32)((y1 + yOffsets[i] + j * 125 - 2) * 4 * m249_viewScale + m249_viewOfsY) < 0x780) {
                            gSPScisTextureRectangle(gMainGfxPos++,
                                                    (s32)(((k * spacing[i] + 10 - ((goalSide[j] == 1) ? 12 : 0) + ((goalSide[j] == 1) ? 0 : 1)) * 4 + (s32)(xPos[j][i] * 4.0f)) * m249_viewScale + m249_viewOfsX),
                                                    (s32)((y1 + yOffsets[i] + j * 125 - 2) * 4 * m249_viewScale + m249_viewOfsY),
                                                    (s32)(((k * spacing[i] + 10 - ((goalSide[j] == 1) ? 12 : 0) + ((goalSide[j] != 1) ? 55 : 54)) * 4 + (s32)(xPos[j][i] * 4.0f)) * m249_viewScale + m249_viewOfsX),
                                                    (s32)((y2 + yOffsets[i] + j * 125 - 2) * 4 * m249_viewScale + m249_viewOfsY),
                                                    0, s * 32, row * rowHeights[i] * 32, (s32)(dsdx * m249_viewScaleInv), (s32)(m249_viewScaleInv * 1024.0f));
                        }
                    }
                    k++;
                } while (k < 4);
            }
        }
    }
    if (m249_seqNo < 3 || m249_winner >= 2) {
        s16 layer = 3;

        sprite = HuSprGet(esprite[m249_sprWork.unk00[15]].unk04, 0);
        frame = &sprite->data->pat[sprite->patNo];
        gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
        for (row = 0; row < 4; row++) {
            gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 0, 0, row * 8, 64,
                               row * 8 + 8 + (row != 3), 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            for (j = 0; j < 2; j++) {
                s32 x;
                s32 top;

                if (m249_nearTileNoTbl[j] < 5) {
                    continue;
                }
                x = ((-m249_nearTileNoTbl[j] + 7) * spacing[layer] + 121) * 4 + (s32)(xPos[j][layer] * 4.0);
                top = 57;
                if ((s32)(x * m249_viewScale + m249_viewOfsX) < 0xA00) {
                    if ((s32)((top + j * 125 - 2 + row * 8) * 4 * m249_viewScale + m249_viewOfsY) < 0x780) {
                        gSPScisTextureRectangle(gMainGfxPos++,
                                                (s32)(x * m249_viewScale + m249_viewOfsX),
                                                (s32)((top + j * 125 - 2 + row * 8) * 4 * m249_viewScale + m249_viewOfsY),
                                                (s32)((x + 252) * m249_viewScale + m249_viewOfsX),
                                                (s32)((top + j * 125 - 2 + row * 8 + 7 + ((row != 3) ? 1 : 0)) * 4 * m249_viewScale + m249_viewOfsY),
                                                0, 0, row * 256, (s32)(m249_viewScaleInv * 1024.0f), (s32)(m249_viewScaleInv * 1024.0f));
                    }
                }
            }
        }
    }
}

void m249_HudDraw(Gfx **arg0, s32 arg1, s32 arg2) {
    f32 xOffset[2];
    s16 i;
    s16 k;
    s16 row;
    s16 j;
    s32 signX;
    s32 xPos;
    s32 y2;
    s32 n;
    s32 x2;
    HuSprAnimPat *frame;
    HuSprAnimPat *iconFrame;
    HuSprite *sprite;
    s32 x;

    m249_hudSkipF = (m249_hudSkipF == 0);
    if (m249_hudSkipF != 0) {
        return;
    }
    gSPDisplayList(gMainGfxPos++, m249_gfxOpaInit);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    sprite = HuSprGet(esprite[m249_sprWork.unk00[16]].unk04, 0);
    frame = &sprite->data->pat[sprite->patNo];
    gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 224);
    for (i = 0; i < 2; i++) {
        if (m249_scrollTbl[i][3] > 720.0) {
            m249_scrollTbl[i][3] -= 654.5454545454545;
        }
        if (m249_scrollTbl[i][3] < 0.0) {
            m249_scrollTbl[i][3] += 654.5454545454545;
        }
        xOffset[i] = -m249_scrollTbl[i][3] * 0.22;
    }
    for (row = 0; row < 3; row++) {
        s32 rowHeight = 15;

        gDPLoadTextureTile_4b(gMainGfxPos++, frame->data, G_IM_FMT_CI, 124, 0, 0, row * rowHeight, 124, row * rowHeight + 15, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        for (j = 0; j < 2; j++) {
            s32 y1 = row * rowHeight;

            if (y1 > 28) {
                continue;
            }
            y2 = y1 + rowHeight + 1;
            for (k = 0; k < 4; k++) {
                s32 left = k * 144;

                if ((s32)((k * 144 * 4 + (s32)(xOffset[j] * 4.0f)) * m249_viewScale + m249_viewOfsX) < 0xA00) {
                    if ((s32)((y1 + j * 121) * 4 * m249_viewScale + m249_viewOfsY) < 0x780) {
                        gSPScisTextureRectangle(gMainGfxPos++,
                                                (s32)((k * 144 * 4 + (s32)(xOffset[j] * 4.0f)) * m249_viewScale + m249_viewOfsX),
                                                (s32)((y1 + j * 121) * 4 * m249_viewScale + m249_viewOfsY),
                                                (s32)(((left + 124) * 4 + (s32)(xOffset[j] * 4.0f)) * m249_viewScale + m249_viewOfsX),
                                                (s32)(((y2 > 28) ? (j * 121 * 4 + 110) : ((y2 + j * 121) * 4)) * m249_viewScale + m249_viewOfsY),
                                                0, 0, row * rowHeight * 32, (s32)(m249_viewScaleInv * 1024.0f), (s32)(m249_viewScaleInv * 1024.0f));
                    }
                }
            }
        }
    }
    sprite = HuSprGet(esprite[m249_sprWork.unk00[5]].unk04, 0);
    frame = &sprite->data->pat[sprite->patNo];
    gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);
    gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 0);
    for (k = 0; k < 6; k++) {
        gDPLoadTextureTile_4b(gMainGfxPos++, frame->data, G_IM_FMT_CI, 320, 0,
                              k * 59, 0, k * 59 + 60, 34, 0,
                              G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        x = k * 59;
        x2 = x + 60;
        x2 = MIN(SCREEN_WIDTHI, x2);
        if ((s32)(x * 4 * m249_viewScale + m249_viewOfsX) >= 0xA00) {
            continue;
        }
        if ((s32)(m249_viewScale * 412.0f + m249_viewOfsY) >= 0x780) {
            continue;
        }
        gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
        gSPScisTextureRectangle(gMainGfxPos++,
                                (s32)(x * 4 * m249_viewScale + m249_viewOfsX),
                                (s32)(m249_viewScale * 412.0f + m249_viewOfsY),
                                (s32)(x2 * 4 * m249_viewScale + m249_viewOfsX),
                                (s32)(m249_viewScale * 548.0f + m249_viewOfsY),
                                0, x * 32, 0, (s32)(m249_viewScaleInv * 1024.0f), (s32)(m249_viewScaleInv * 1024.0f));
    }
    gDPSetCombineMode(gMainGfxPos++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 224);
    for (i = 0; i < 2; i++) {
        xPos = (m249_iconPosTbl[i] * (1.0 - m249_iconMoveTimerTbl[i] / 20.0) + m249_iconPosPrevTbl[i] * (m249_iconMoveTimerTbl[i] / 20.0)) * 14.0 + 32.0;
        sprite = HuSprGet(esprite[m249_sprWork.unk00[6 + m249_playerPtrTbl[i]->unk03]].unk04, 0);
        // The extra alias is needed for matching register allocation.
        frame = iconFrame = &sprite->data->pat[sprite->patNo];
        if (m249_playerPtrTbl[i]->unk03 == 7) {
            gDPLoadTLUT_pal256(gMainGfxPos++, sprite->data->pal);
        } else {
            gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
        }
        if ((s32)(xPos * 4 * m249_viewScale + m249_viewOfsX) >= 0xA00) {
            continue;
        }
        if ((s32)((i * 64 + 416) * m249_viewScale + m249_viewOfsY) >= 0x780) {
            continue;
        }
        if (m249_playerPtrTbl[i]->unk03 == 7) {
            gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_CI, G_IM_SIZ_8b, 18, 0, 0, 0, 18, 18, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureTile_4b(gMainGfxPos++, frame->data, G_IM_FMT_CI, 18, 0, 0, 0, 18, 18, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        }
        gSPScisTextureRectangle(gMainGfxPos++,
                                (s32)(xPos * 4 * m249_viewScale + m249_viewOfsX),
                                (s32)((i * 18 + 102) * 4 * m249_viewScale + m249_viewOfsY),
                                (s32)((xPos + 18) * 4 * m249_viewScale + m249_viewOfsX),
                                (s32)(((i * 18 + 120) * 4 - 3) * m249_viewScale + m249_viewOfsY),
                                0, 0, 0, (s32)(m249_viewScaleInv * 1024.0f), (s32)(m249_viewScaleInv * 1024.0f));
    }
    gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
    if (m249_seqNo >= 3 && m249_winner < 2) {
        sprite = HuSprGet(esprite[m249_sprWork.unk00[15]].unk04, 0);
        frame = &sprite->data->pat[sprite->patNo];
        gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
        for (row = 0; row < 4; row++) {
            gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 0,
                               0, row * 8, 64, row * 8 + 8 + (row != 3), 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            for (n = 0; n < 2; n++) {
                s32 top = 55;

                if (m249_nearTileNoTbl[n] < 5) {
                    continue;
                }
                signX = ((-m249_nearTileNoTbl[n] + 7) * 144 + 121) * 4 + (s32)((12.0 - m249_scrollTbl[n][2] * 0.16) * 4.0);
                if ((s32)(signX * m249_viewScale + m249_viewOfsX) >= 0xA00) {
                    continue;
                }
                if ((s32)((n * 125 + (row * 8 + (top - 2))) * 4 * m249_viewScale + m249_viewOfsY) >= 0x780) {
                    continue;
                }
                gSPScisTextureRectangle(gMainGfxPos++,
                                        (s32)(signX * m249_viewScale + m249_viewOfsX),
                                        (s32)((n * 125 + (row * 8 + top)) * 4 * m249_viewScale + m249_viewOfsY),
                                        (s32)((signX + 252) * m249_viewScale + m249_viewOfsX),
                                        (s32)((n * 125 + (row * 8 + top) + 7 + (row != 3 ? 2 : 0)) * 4 * m249_viewScale + m249_viewOfsY),
                                        0, 0, row * 256, (s32)(m249_viewScaleInv * 1024.0f), (s32)(m249_viewScaleInv * 1024.0f));
            }
        }
    }
    gDPPipeSync(gMainGfxPos++);
    gDPSetBlendColor(gMainGfxPos++, 255, 255, 255, 0);
    gDPPipeSync(gMainGfxPos++);
}

void m249_Player0ObjInit(omObjData *arg0) {
    m249_PlayerInit(arg0, 0, 0);
    arg0->func = m249_Player0ObjMain;
}

void m249_Player1ObjInit(omObjData *arg0) {
    m249_PlayerInit(arg0, 1, 1);
    arg0->func = m249_Player1ObjMain;
}

void m249_PlayerInit(omObjData *arg0, s8 arg1, s32 arg2) {
    s32 sp10[] = { 2, 3, 7, 4, 5, 6, 8, 9 };
    s32 sp30[] = { 162, 162, 162, 162, 162, 162, 162, 3 };
    s32 sp50[] = { 160, 160, 160, 160, 160, 160, 160, 0 };
    s32 sp70[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    s32 sp90[][8] = {
        { 164, 164, 164, 164, 164, 164, 164, 27 },
        { 165, 165, 165, 165, 165, 165, 165, 28 }
    };
    u16 temp_v0;
    u16 var_s1;

    temp_v0 = m249_playerPtrTbl[arg1]->unk03;
    arg0->model[0] = Hu3DModelRead((sp10[temp_v0] << 16) | sp30[temp_v0], 0x4B9);
    arg0->model[1] = Hu3DModelRead((sp10[temp_v0] << 16) | sp50[temp_v0], 0x4AD);
    m249_playerPtrTbl[arg1]->unk06 = CharAnimCreate(arg0->model[1], 1, sp70[temp_v0], (sp10[temp_v0] << 16) | sp90[0][temp_v0]);
    m249_playerPtrTbl[arg1]->unk08 = Hu3DAnimDataRead((sp10[temp_v0] << 16) | sp90[1][temp_v0]);
    Hu3DModelDynamicFree(arg0->model[1]);
    m249_playerPtrTbl[arg1]->unk0C = (rand8() & 1) ? 0x2F : 0x30;
    omObjMotionRead(arg0, 0, CharMotionDataNumGet(temp_v0, 0));
    omObjMotionRead(arg0, 1, CharMotionDataNumGet(temp_v0, 0x42));
    omObjMotionRead(arg0, 2, CharMotionDataNumGet(temp_v0, 0x43));
    omObjMotionRead(arg0, 3, CharMotionDataNumGet(temp_v0, (temp_v0 == 5) ? 5 : 0x1F));
    omObjMotionRead(arg0, 4, CharMotionDataNumGet(temp_v0, 0x1F));
    omObjMotionRead(arg0, 5, CharMotionDataNumGet(temp_v0, m249_playerPtrTbl[arg1]->unk0C));
    omObjMotionRead(arg0, 6, CharMotionDataNumGet(temp_v0, 0x3A));
    m249_playerPtrTbl[arg1]->unk0C |= (sp10[temp_v0] << 16);
    Hu3DModelObjAttrSet(arg0->model[0], 0x600, 0x400);
    Hu3DModelObjAttrSet(arg0->model[1], 0x600, 0x400);
    Hu3DMotionModelSet(arg0->model[0], arg0->motion[1]);
    Hu3DMotionAttrSet(arg0->model[0], 2, 2);
    Hu3DModelCameraSet(arg0->model[0], (arg1 != 0) ? HU3D_CAM1 : HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[1], (arg1 != 0) ? HU3D_CAM1 : HU3D_CAM0);
    for (var_s1 = 0; var_s1 < 24; var_s1++) {
        if (var_s1 == 0) {
            arg0->model[2] = Hu3DModelRead(0x520000, 0x4B9);
        } else {
            arg0->model[var_s1 + 2] = Hu3DModelLink(arg0->model[2]);
        }
        Hu3DModelPosSet(arg0->model[var_s1 + 2], 0.0f, var_s1 * -50.0, 0.0f);
        Hu3DModelRotSet(arg0->model[var_s1 + 2], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(arg0->model[var_s1 + 2], 1.0f, 1.0f, 1.0f);
        Hu3DModelCameraSet(arg0->model[var_s1 + 2], (arg1 != 0) ? HU3D_CAM1 : HU3D_CAM0);
    }
    m249_exitF = 0;
}

void m249_Player0ObjMain(omObjData *arg0) {
    m249_PlayerUpdate(arg0, 0, 0);
}

void m249_Player1ObjMain(omObjData *arg0) {
    m249_PlayerUpdate(arg0, 1, 1);
}

// TODO: doesn't work with -Wa,--vr4300mul-off.
void m249_PlayerUpdate(omObjData *arg0, s8 arg1, s8 arg2) {
    f32 sp18[6];
    f32 sp30[6];
    f32 sp48[6];
    f32 sp60[6][9];
    f32 sp138[6][9];
    f32 sp210[6][9];
    VineWithMePlayer *sp3C4;
    f32 sp3CC;
    s8 sp3D7;
    s32 sp3DC;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_5;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f20_3;
    f32 temp_f20_5;
    f32 temp_f2_17;
    f32 temp_f2_4;
    f32 temp_f2_7;
    f32 temp_f4_5;
    f32 temp_f6_3;
    f32 temp_f6_4;
    f32 var_f24;
    f32 var_f26;
    f32 var_f4_2;
    f32 var_f4_3;
    f32 var_f6;
    f32 var_f8;
    f64 var_f4;
    s32 temp_f0_13;
    s32 temp_f0_5;
    s32 temp_s0;
    s32 temp_t1;
    s32 temp_t2;
    s32 temp_t6;
    s32 temp_v1_19;
    s32 var_a0_2;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    s32 var_s7;
    s32 var_t7;
    s32 var_v1_2;
    s8 var_s6;
    u32 temp_fp;

    sp3C4 = m249_playerPtrTbl[arg2];
    sp3CC = m249_cameraXTbl[arg1];
    sp3D7 = 0;
    sp3DC = m249_frameCnt / 14;
    sp3DC = m249_frameCnt % 14;
    if (m249_frameCnt == 0 && arg2 == 0) {
        s32 sp2E8[] = { 2, 4, 3, 4, 2 };

        for (var_s4 = 0; var_s4 < 15; var_s4++) {
            do {
                var_s5 = (rand8() % 5) & 0xFF;
            } while (sp2E8[var_s5] == 0);
            sp2E8[var_s5]--;
            m249_courseVineTbl[var_s4 + 1] = var_s5 + 4;
        }
        for (var_s4 = 0; var_s4 < 2; var_s4++) {
            for (var_s5 = 0; var_s5 < 5; var_s5++) {
                m249_vineLenTbl[var_s4][var_s5 + 1] = m249_courseVineTbl[var_s5 + 1];
            }
        }
    }
    if (m249_frameCnt == 0) {
        sp3CC = 900.0f;
    }
    if (m249_frameCnt == 0x2A) {
        sp3D7 = 1;
    } else if (m249_frameCnt < 0x56 || m249_seqNo >= 3) {
        sp3D7 = -1;
    }
    if (arg2 == 0) {
        for (var_s7 = (m249_frameCnt != 0) * 13; var_s7 < 14; var_s7++) {
            temp_s0 = (var_s7 + m249_frameCnt) % 14;
            temp_fp = var_s7 + m249_frameCnt;
            for (var_s5 = 0; var_s5 < 5; var_s5++) {
                f32 sp300[] = { 8.75f, 7.75f, 6.5f, 5.25f, 4.0f };

                var_f24 = 0.0f;
                var_f26 = 0.0f;
                temp_f0 = sindf(temp_fp * sp300[var_s5] * 0.9375) * -80.0 - 90.0;
                for (var_s4 = 0; var_s4 < var_s5 + 4; var_s4++) {
                    if (temp_f0 > 90.0) {
                        temp_f20 = temp_f0 - 270.0;
                    } else {
                        temp_f20 = temp_f0 + 90.0;
                    }
                    temp_f20 = temp_f20 * ((f32)var_s4 * 0.25 / 10.0 + 0.75) - 90.0;
                    m249_vineXTbl[var_s5][var_s4][temp_s0] = var_f26;
                    m249_vineYTbl[var_s5][var_s4][temp_s0] = var_f24;
                    m249_vineAngleTbl[var_s5][var_s4][temp_s0] = temp_f20;
                    var_f26 += cosdf(temp_f20) * 50.0;
                    var_f24 += sindf(temp_f20) * 50.0;
                }
                m249_vineXTbl[var_s5][var_s4][temp_s0] = var_f26;
                m249_vineYTbl[var_s5][var_s4][temp_s0] = var_f24;
                m249_vineAngleTbl[var_s5][var_s4][temp_s0] = m249_vineAngleTbl[var_s5][var_s4 - 1][temp_s0];
            }
        }
    }
    m249_cameraSpeedTbl[arg1] = (m249_playerXTbl[arg1] > m249_cameraXTbl[arg1])
                                        ? ((m249_playerXTbl[arg1] - m249_cameraXTbl[arg1]) * 0.0625 + 20.0)
                                        : 20.0f;
    if (!(m249_fallTimerTbl[arg1] >= 10.0f) && (m249_seqNo != 0) && (m249_seqNo != 1 || m249_seqTimer >= 5)) {
        if (m249_playerYTbl[arg1] > -550.0) {
            if (m249_playerStateTbl[arg1] == 1) {
                f64 fake_ft0 = m249_vineNoTbl[arg1] * 450.0 + 400.0;

                var_f4 = fake_ft0;
                if (m249_cameraXTbl[arg1] < var_f4 && m249_cameraSpeedTbl[arg1] > 0.0) {
                    m249_cameraXTbl[arg1] = MIN(var_f4, m249_cameraXTbl[arg1] + m249_cameraSpeedTbl[arg1]);
                }
            } else {
                f64 fake_ft0 = m249_playerXTbl[arg1] + 400.0;

                var_f4 = fake_ft0;
                if (m249_cameraXTbl[arg1] < var_f4 && m249_cameraSpeedTbl[arg1] > 0.0) {
                    m249_cameraXTbl[arg1] = MIN(var_f4, m249_cameraXTbl[arg1] + m249_cameraSpeedTbl[arg1]);
                }
            }
        }
    }
    if (m249_vineBaseTbl[arg1] <= 0 && m249_cameraXTbl[arg1] <= 550.0f) {
        m249_cameraXTbl[arg1] += -m249_vineBaseTbl[arg1] * 450.0 - (m249_cameraXTbl[arg1] - 550.0);
    }
    if (m249_vineBaseTbl[arg1] >= 12 && m249_cameraXTbl[arg1] >= 1250.0f) {
        m249_cameraXTbl[arg1] -= (m249_vineBaseTbl[arg1] - 12) * 450.0 + m249_cameraXTbl[arg1] - 1250.0;
    }
    if (m249_cameraXTbl[arg1] > 1375.0) {
        m249_cameraXTbl[arg1] -= 450.0;
        sp3CC -= 450.0;
        m249_playerXTbl[arg1] -= 450.0;
        m249_prevXTbl[arg1] -= 450.0;
        m249_vineBaseTbl[arg1]++;
        if (m249_fallTimerTbl[arg1] > 0.0f) {
            m249_fallXTbl[arg1] -= 450.0;
            m249_fallCameraXTbl[arg1] -= 450.0;
            m249_respawnCameraXTbl[arg1] -= 450.0;
        }
        for (var_s5 = 0; var_s5 < 8; var_s5++) {
            if (m249_sprWork.unk22[var_s5] == arg1) {
                m249_splashXTbl[var_s5] -= 450.0;
            }
        }
        m249_vineNoTbl[arg1]--;
        m249_vineParityTbl[arg1] = (m249_vineParityTbl[arg1] == 0);
        for (var_s5 = 0; var_s5 < 5; var_s5++) {
            m249_vineLenTbl[arg1][var_s5] = m249_vineLenTbl[arg1][var_s5 + 1];
        }
        m249_vineLenTbl[arg1][5] = m249_courseVineTbl[m249_vineBaseTbl[arg1] + 5];
    }
    if (m249_cameraXTbl[arg1] < 875.0 && m249_vineBaseTbl[arg1] > 0 && (m249_seqNo != 0 || m249_playerStateTbl[arg1] != 2)) {
        m249_cameraXTbl[arg1] += 450.0;
        sp3CC += 450.0;
        m249_playerXTbl[arg1] += 450.0;
        m249_prevXTbl[arg1] += 450.0;
        m249_vineBaseTbl[arg1]--;
        if (m249_fallTimerTbl[arg1] > 0.0f) {
            m249_fallXTbl[arg1] += 450.0;
            m249_fallCameraXTbl[arg1] += 450.0;
            m249_respawnCameraXTbl[arg1] += 450.0;
        }
        for (var_s5 = 0; var_s5 < 8; var_s5++) {
            if (m249_sprWork.unk22[var_s5] == arg1) {
                m249_splashXTbl[var_s5] += 450.0;
            }
        }
        m249_vineNoTbl[arg1]++;
        m249_vineParityTbl[arg1] = (m249_vineParityTbl[arg1] == 0);
        for (var_s5 = 5; var_s5 > 0; var_s5--) {
            m249_vineLenTbl[arg1][var_s5] = m249_vineLenTbl[arg1][var_s5 - 1];
        }
        m249_vineLenTbl[arg1][0] = m249_courseVineTbl[m249_vineBaseTbl[arg1]];
    }
    for (var_s5 = 0; var_s5 < 6; var_s5++) {
        for (var_s4 = 0; var_s4 < 4; var_s4++) {
            Hu3DModelAttrSet(arg0->model[2 + var_s5 * 4 + var_s4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
    }
    for (var_s4 = 0; var_s4 < 5; var_s4++) {
        if (m249_seqNo >= 4 && m249_winner != 2 && m249_seqTimer >= 30 && (s32)(-m249_vineAngleTbl[var_s4][0][sp3DC] + 540.0f) % 360 < 271) {
            m249_vineEndTbl[var_s4] = 1;
        }
    }
    for (var_s5 = 0; var_s5 < 6; var_s5++) {
        temp_t1 = (m249_vineParityTbl[arg1] + var_s5) % 2;
        temp_t6 = 1 - ((m249_vineParityTbl[arg1] + var_s5) % 2) * 2;
        var_t7 = (m249_cameraXTbl[arg1] < 900.0f);
        if (m249_vineLenTbl[arg1][var_s5] != 0) {
            sp18[var_s5] = var_s5 * 450.0;
            sp30[var_s5] = 0.0f;
            for (var_s4 = 0; var_s4 < m249_vineLenTbl[arg1][var_s5]; var_s4++) {
                sp60[var_s5][var_s4] = sp18[var_s5] + m249_vineXTbl[m249_vineLenTbl[arg1][var_s5] - 4][var_s4][sp3DC] * temp_t6;
                sp138[var_s5][var_s4] = m249_vineYTblBase[m249_vineLenTbl[arg1][var_s5]][var_s4][sp3DC];
                sp210[var_s5][var_s4 + 1] = (temp_t1 != 0)
                                                ? (-m249_vineAngleTblBase[m249_vineLenTbl[arg1][var_s5]][var_s4][sp3DC] + 540.0f)
                                                : m249_vineAngleTblBase[m249_vineLenTbl[arg1][var_s5]][var_s4][sp3DC];
            }
            sp18[var_s5] += m249_vineXTbl[m249_vineLenTbl[arg1][var_s5] - 4][var_s4][sp3DC] * temp_t6;
            sp60[var_s5][var_s4] = sp18[var_s5];
            sp30[var_s5] = sp138[var_s5][var_s4] = m249_vineYTblBase[m249_vineLenTbl[arg1][var_s5]][var_s4][sp3DC];
            sp210[var_s5][0] = sp210[var_s5][1];
            sp48[var_s5] = (temp_t1 != 0)
                               ? (-m249_vineAngleTblBase[m249_vineLenTbl[arg1][var_s5]][var_s4][sp3DC] + 540.0f)
                               : m249_vineAngleTblBase[m249_vineLenTbl[arg1][var_s5]][var_s4][sp3DC];
            for (var_s4 = 0; var_s4 < m249_vineLenTbl[arg1][var_s5]; var_s4 += 2) {
                var_v1_2 = (var_s4 + 1 == m249_vineLenTbl[arg1][var_s5]) ? 1 : 2;
                temp_f2_4 = sp60[var_s5][var_s4 + var_v1_2] - sp60[var_s5][var_s4];
                temp_f12 = sp138[var_s5][var_s4 + var_v1_2] - sp138[var_s5][var_s4];
                temp_f20_2 = HuSqrtf(temp_f2_4 * temp_f2_4 + temp_f12 * temp_f12);
                Hu3DModelPosSet(arg0->model[2 + var_s5 * 4 + (var_s4 >> 1)], sp60[var_s5][var_s4] - (var_t7 && var_s5 == 5) * 450.0 * 6.0, sp138[var_s5][var_s4], 0.0f);
                Hu3DModelRotSet(arg0->model[2 + var_s5 * 4 + (var_s4 >> 1)], 0.0f, 0.0f, (sp210[var_s5][var_s4 + 1] + sp210[var_s5][var_s4 + var_v1_2]) / 2.0 + 90.0);
                Hu3DModelScaleSet(arg0->model[2 + var_s5 * 4 + (var_s4 >> 1)], 1.0f, temp_f20_2 / 50.0, 1.0f);
                if (m249_vineLenTbl[arg1][var_s5] >= 4 && m249_holdTimeTbl[m249_vineLenTbl[arg1][var_s5]] == 0) {
                    Hu3DModelAttrSet(arg0->model[2 + var_s5 * 4 + (var_s4 >> 1)], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                }
            }
            for (; var_s4 < 8; var_s4 += 2) {
                Hu3DModelAttrSet(arg0->model[2 + var_s5 * 4 + (var_s4 >> 1)], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
        }
    }
    if (m249_playerStateTbl[arg1] == 1) {
        m249_holdTimeTbl[arg1] += (m249_holdTimeTbl[arg1] < 0xFF);
        if (m249_vineSegPosTbl[arg1] < m249_vineLenTbl[arg1][m249_vineNoTbl[arg1]] && m249_vineSegPosTbl[arg1] + 0.4375 >= m249_vineLenTbl[arg1][m249_vineNoTbl[arg1]]) {
            Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[1]].motId, 0, 4, 2);
        }
        m249_vineSegPosTbl[arg1] += 0.4375;
        if (m249_vineLenTbl[arg1][m249_vineNoTbl[arg1]] <= m249_vineSegPosTbl[arg1]) {
            m249_vineSegPosTbl[arg1] = m249_vineLenTbl[arg1][m249_vineNoTbl[arg1]];
            if (m249_blinkTimerTbl[arg1] >= 0xFF) {
                m249_blinkTimerTbl[arg1] = 0xF;
            }
        }
        temp_f2_7 = m249_vineSegPosTbl[arg1];
        temp_f0_5 = temp_f2_7;
        temp_f6_3 = temp_f2_7 - temp_f0_5;
        m249_playerXTbl[arg1] = (temp_f6_3 == 0.0)
                                            ? sp60[m249_vineNoTbl[arg1]][temp_f0_5]
                                            : (sp60[m249_vineNoTbl[arg1]][temp_f0_5] * (1.0 - temp_f6_3) + temp_f6_3 * sp60[m249_vineNoTbl[arg1]][temp_f0_5 + 1]);
        m249_playerYTbl[arg1] = (temp_f6_3 == 0.0)
                                            ? sp138[m249_vineNoTbl[arg1]][temp_f0_5]
                                            : (sp138[m249_vineNoTbl[arg1]][temp_f0_5] * (1.0 - temp_f6_3) + temp_f6_3 * sp138[m249_vineNoTbl[arg1]][temp_f0_5 + 1]);
        m249_swingAngleTbl[arg1] = (temp_f6_3 == 0.0)
                                            ? sp210[m249_vineNoTbl[arg1]][temp_f0_5]
                                            : (sp210[m249_vineNoTbl[arg1]][temp_f0_5] * (1.0 - temp_f6_3) + temp_f6_3 * sp210[m249_vineNoTbl[arg1]][temp_f0_5 + 1]);
        if (m249_blinkTimerTbl[arg1] == 0) {
            if (sp3D7 != -1) {
                if (sp3C4->unk04 != -1) {
                    f32 var_f24_2 = m249_playerXTbl[arg1];
                    f32 var_f20 = m249_playerYTbl[arg1];
                    f32 temp_f28 = (var_f24_2 - m249_prevXTbl[arg1]) * 1.25;
                    f32 var_f26_2 = (var_f20 - m249_prevYTbl[arg1]) * 1.25;
                    f32 sp318[10];
                    f32 sp340[10];
                    f32 sp368[10];
                    u8 sp390[4] = { 4, 4, 6, 9 };
                    u8 sp398[4] = { 0x96, 0x5A, 0x3C, 0x14 };
                    u8 sp3A0[4] = { 14, 6, 3, 2 };

                    if (m249_holdTimeTbl[arg1] >= sp398[sp3C4->unk04]) {
                        if (rand8() % sp3A0[sp3C4->unk04] == 0 || m249_vineNoTbl[arg1] + m249_vineBaseTbl[arg1] == 0xF) {
                            for (var_s6 = 0; var_s6 < 14; var_s6++) {
                                if (var_s6 < sp390[sp3C4->unk04]) {
                                    temp_v1_19 = m249_vineNoTbl[arg1] + 1;
                                    if (temp_v1_19 < 6) {
                                        var_s5 = temp_v1_19;
                                    } else {
                                        var_s5 = 5;
                                    }
                                    for (; var_s5 > m249_vineNoTbl[arg1]; var_s5--) {
                                        temp_t1 = (m249_vineParityTbl[arg1] + var_s5) % 2;
                                        temp_t2 = 1 - ((m249_vineParityTbl[arg1] + var_s5) % 2) * 2;
                                        if (m249_vineLenTbl[arg1][var_s5] != 0) {
                                            temp_f4_5 = var_s5 * 450.0;
                                            for (var_s4 = 0; var_s4 < m249_vineLenTbl[arg1][var_s5]; var_s4++) {
                                                sp318[var_s4] = temp_f4_5 + m249_vineXTbl[m249_vineLenTbl[arg1][var_s5] - 4][var_s4][sp3DC + var_s6] * temp_t2;
                                                sp340[var_s4] = m249_vineYTblBase[m249_vineLenTbl[arg1][var_s5]][var_s4][sp3DC + var_s6];
                                                sp368[var_s4 + 1] = (temp_t1 != 0)
                                                                        ? (-m249_vineAngleTblBase[m249_vineLenTbl[arg1][var_s5]][var_s4][sp3DC + var_s6] + 540.0f)
                                                                        : m249_vineAngleTblBase[m249_vineLenTbl[arg1][var_s5]][var_s4][sp3DC + var_s6];
                                            }
                                            temp_f4_5 += m249_vineXTbl[m249_vineLenTbl[arg1][var_s5] - 4][var_s4][sp3DC + var_s6] * temp_t2;
                                            sp318[var_s4] = temp_f4_5;
                                            temp_f12_2 = m249_vineYTblBase[m249_vineLenTbl[arg1][var_s5]][var_s4][sp3DC + var_s6];
                                            sp340[var_s4] = temp_f12_2;
                                            sp368[0] = sp368[1];
                                            if (HuSqrtf((var_f24_2 - temp_f4_5) * (var_f24_2 - temp_f4_5) + (var_f20 - temp_f12_2) * (var_f20 - temp_f12_2)) < 90.0) {
                                                sp3D7 = 1;
                                                goto block_213c;
                                            }
                                            for (var_s4 = m249_vineLenTbl[arg1][var_s5] - 1; var_s4 >= 0; var_s4--) {
                                                if (HuSqrtf((var_f24_2 - sp318[var_s4]) * (var_f24_2 - sp318[var_s4]) + (var_f20 - sp340[var_s4]) * (var_f20 - sp340[var_s4])) < 40.0) {
                                                    sp3D7 = 1;
                                                    goto block_213c;
                                                }
                                            }
                                        }
                                    }
                                }
                                var_f26_2 -= 2.5;
                                if (m249_holdTimeTbl[arg1] >= sp398[sp3C4->unk04] + 30 && var_f24_2 + temp_f28 < (-m249_vineBaseTbl[arg1] + 12) * 450.0 + 1800.0 + 110.0 && (-m249_vineBaseTbl[arg1] + 12) * 450.0 + 1800.0 - 100.0 < var_f24_2 + temp_f28 && var_f20 + var_f26_2 <= -182.5 && var_f20 > -182.5) {
                                    sp3D7 = 1;
                                    break;
                                }
                                var_f24_2 += temp_f28;
                                var_f20 += var_f26_2;
                            }
                        }
                    }
                } else if (sp3D7 != -1 && (HuPadBtnDown[sp3C4->unk02] & A_BUTTON)) {
                    sp3D7 = 1;
                }
            }
        block_213c:
            if (sp3D7 == 1) {
                m249_playerStateTbl[arg1] = 0;
                m249_jumpVelXTbl[arg1] = m249_cameraSpeedTbl[arg1] = (m249_playerXTbl[arg1] - m249_prevXTbl[arg1]) * 1.25;
                m249_jumpVelYTbl[arg1] = (m249_playerYTbl[arg1] - m249_prevYTbl[arg1]) * 1.25;
                Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[3]].motId, 0, 7, sp3D7);
                var_f4_2 = m249_playerXTbl[arg1];
                var_f8 = m249_playerYTbl[arg1];
                temp_f12_5 = m249_jumpVelXTbl[arg1];
                var_f6 = m249_jumpVelYTbl[arg1];
                for (var_a0_2 = 1; var_a0_2 < 60; var_a0_2++) {
                    var_f6 -= 2.5;
                    if ((-m249_vineBaseTbl[arg1] + 12) * 450.0 + 1800.0 - 165.0 < var_f4_2 + temp_f12_5 && var_f8 + var_f6 <= -182.5 && var_f8 > -182.5) {
                        break;
                    }
                    var_f4_2 += temp_f12_5;
                    var_f8 += var_f6;
                }
                if (m249_goalAssistF != 0 && var_a0_2 < 60 && var_f4_2 + temp_f12_5 >= (-m249_vineBaseTbl[arg1] + 12) * 450.0 + 1800.0 + 70.0) {
                    m249_jumpVelXTbl[arg1] = ((-m249_vineBaseTbl[arg1] + 12) * 450.0 + 1800.0 + 70.0 - m249_playerXTbl[arg1]) / (f32)var_a0_2;
                }
            }
        }
    } else if (m249_playerStateTbl[arg1] == 0) {
        m249_jumpVelYTbl[arg1] -= 2.5;
        m249_playerXTbl[arg1] += m249_jumpVelXTbl[arg1];
        m249_playerYTbl[arg1] += m249_jumpVelYTbl[arg1];
    } else if (m249_playerStateTbl[arg1] == 2 && m249_frameCnt == 0x5C) {
        m249_playerStateTbl[arg1] = 0;
        m249_playerYTbl[arg1] += 1.0;
        m249_jumpVelXTbl[arg1] = 10.0f;
        m249_jumpVelYTbl[arg1] = 30.0f;
        Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[3]].motId, 0, 4, 1);
    }
    if (m249_playerStateTbl[arg1] == 0) {
        if (m249_playerYTbl[arg1] <= -812.5 || m249_fallTimerTbl[arg1] > 0.0f) {
            if (m249_fallTimerTbl[arg1] == 10.0f) {
                m249_fallXTbl[arg1] = m249_playerXTbl[arg1];
                m249_fallCameraXTbl[arg1] = m249_cameraXTbl[arg1];
                m249_respawnCameraXTbl[arg1] = m249_vineNoTbl[arg1] * 450.0 + 400.0;
                if (m249_vineBaseTbl[arg1] <= 0 && m249_respawnCameraXTbl[arg1] <= 900.0f) {
                    m249_respawnCameraXTbl[arg1] += -m249_vineBaseTbl[arg1] * 450.0 - (m249_respawnCameraXTbl[arg1] - 900.0);
                }
                if (m249_vineBaseTbl[arg1] >= 12 && m249_respawnCameraXTbl[arg1] >= 1250.0f) {
                    m249_respawnCameraXTbl[arg1] -= (m249_vineBaseTbl[arg1] - 12) * 450.0 + m249_respawnCameraXTbl[arg1] - 1250.0;
                }
                m249_jumpVelXTbl[arg1] = 0.0f;
                m249_jumpVelYTbl[arg1] = 65.0f;
                if (m249_playerXTbl[arg1] < m249_cameraXTbl[arg1] - 900.0) {
                    m249_fallXTbl[arg1] = m249_cameraXTbl[arg1] - 900.0;
                }
                if (m249_playerXTbl[arg1] > m249_vineNoTbl[arg1] * 450.0 + 800.0) {
                    m249_fallXTbl[arg1] = m249_vineNoTbl[arg1] * 450.0 + 800.0;
                }
                m249_swingAngleTbl[arg1] = atan2df(-m249_jumpVelYTbl[arg1] * 0.5, -(m249_fallXTbl[arg1] * 0.96 + m249_vineNoTbl[arg1] * 450.0 * 0.04 - m249_fallXTbl[arg1]) * 0.5);
                Hu3DMotionModelSet(arg0->model[0], arg0->motion[3]);
                Hu3DMotionTimeSet(arg0->model[0], 0.0f);
                Hu3DMotionAttrSet(arg0->model[0], 1, 1);
            }
            if (m249_fallTimerTbl[arg1] == 20.0f) {
                for (var_s2 = 0, var_s3 = 0; var_s2 < 8; var_s2++) {
                    if (m249_splashTimerTbl[var_s2] == 90) {
                        m249_splashTimerTbl[var_s2] = (rand8() & 0xF) + 15;
                        m249_sprWork.unk22[var_s2] = arg1;
                        m249_splashXTbl[var_s2] = m249_respawnCameraXTbl[arg1] + (var_s3 - 1.5) * 440.0 + (rand8() - 0x80);
                        var_s3++;
                        m249_splashTypeTbl[var_s2] = rand8() & 3;
                        m249_splashAnimOfsTbl[var_s2] = rand8() % 74;
                        if (var_s3 >= 4) {
                            break;
                        }
                    }
                }
            }
            if (m249_fallTimerTbl[arg1] == 35.0f) {
                m249_fallTimerTbl[arg1] = 0.0f;
                m249_blinkTimerTbl[arg1] = 0xFF;
                m249_playerStateTbl[arg1] = 1;
                m249_vineSegPosTbl[arg1] = 0;
                m249_playerXTbl[arg1] = sp18[m249_vineNoTbl[arg1]];
                m249_playerYTbl[arg1] = sp30[m249_vineNoTbl[arg1]];
                m249_swingAngleTbl[arg1] = sp48[m249_vineNoTbl[arg1]];
                Hu3DMotionModelSet(arg0->model[0], arg0->motion[2]);
                Hu3DMotionAttrSet(arg0->model[0], 2, 2);
            } else {
                m249_fallTimerTbl[arg1] += 1.0f;
                if (m249_fallTimerTbl[arg1] == 10.0f && m249_seqNo >= 3) {
                    m249_fallTimerTbl[arg1] -= 1.0f;
                }
                if (m249_fallTimerTbl[arg1] == 1.0f) {
                    PlayerFXPlay(0x286, m249_groupPlayerTbl[arg1]);
                    HuAudPlayerFXPlay(0x493, arg1);
                    omVibrate(m249_groupPlayerTbl[arg1], 0xA, 0, 0xA);
                    m249_fallF = 1;
                }
                if (m249_fallTimerTbl[arg1] < 10.0f) {
                    m249_playerYTbl[arg1] = -812.5f;
                    m249_jumpVelXTbl[arg1] = m249_jumpVelYTbl[arg1] = 0.0f;
                } else if (m249_fallTimerTbl[arg1] > 10.0f) {
                    m249_playerXTbl[arg1] = m249_fallXTbl[arg1] * ((35.0f - m249_fallTimerTbl[arg1]) / 25.0) + m249_vineNoTbl[arg1] * 450.0 * ((m249_fallTimerTbl[arg1] - 10.0f) / 25.0);
                    m249_cameraXTbl[arg1] = m249_fallCameraXTbl[arg1] * ((35.0f - m249_fallTimerTbl[arg1]) / 25.0) + m249_respawnCameraXTbl[arg1] * ((m249_fallTimerTbl[arg1] - 10.0f) / 25.0);
                }
            }
        } else {
            if (m249_vineBaseTbl[arg1] >= 8 || m249_seqNo == 0) {
                if (m249_vineBaseTbl[arg1] < 8) {
                    temp_f20_3 = -m249_vineBaseTbl[arg1] * 450.0 - 75.0 + 435.0;
                } else {
                    temp_f20_3 = (-m249_vineBaseTbl[arg1] + 12) * 450.0 + 1800.0;
                }
                if (m249_vineBaseTbl[arg1] >= 8 && temp_f20_3 + 75.0 - (m249_goalAssistF == 0 ? 10.0 : 0.0) <= m249_playerXTbl[arg1] && m249_prevXTbl[arg1] < temp_f20_3 + 75.0 - (m249_goalAssistF == 0 ? 10.0 : 0.0) && m249_playerYTbl[arg1] > -182.5) {
                    m249_playerXTbl[arg1] = temp_f20_3 + 70.0 - (m249_goalAssistF == 0 ? 10.0 : 0.0);
                    m249_swingAngleTbl[arg1] = 275.0f;
                    m249_jumpVelXTbl[arg1] /= 1.5;
                    Hu3DMotionModelSet(arg0->model[0], arg0->motion[4]);
                    Hu3DMotionTimeSet(arg0->model[0], 8.0f);
                    Hu3DMotionAttrSet(arg0->model[0], 1, 1);
                }
                if (m249_playerXTbl[arg1] < temp_f20_3 + 135.0 && temp_f20_3 - 165.0 < m249_playerXTbl[arg1] && m249_playerYTbl[arg1] <= -182.5 && m249_prevYTbl[arg1] > -182.5) {
                    m249_playerStateTbl[arg1] = 2;
                    m249_playerXTbl[arg1] =
                        (m249_playerXTbl[arg1] > temp_f20_3 + 75.0)   ? (temp_f20_3 + 75.0)
                        : (m249_playerXTbl[arg1] < temp_f20_3 - 95.0) ? (temp_f20_3 - 95.0)
                                                                              : m249_playerXTbl[arg1];
                    m249_playerYTbl[arg1] = (m249_seqNo == 0) ? -176.25f : -182.5f;
                    m249_swingAngleTbl[arg1] = 270.0f;
                    m249_jumpVelXTbl[arg1] = 0.0f;
                    m249_jumpVelYTbl[arg1] = 0;
                    if (m249_vineBaseTbl[arg1] >= 8) {
                        if (m249_winner == 4) {
                            m249_winner = (rand8() & 1) + 1;
                        }
                        if (m249_vineBaseTbl[arg1] >= 8 && m249_seqNo == 2 && m249_winner == 0) {
                            m249_winner = (arg2 != 0) ? (arg1 + 1) : 4;
                        }
                    }
                    Hu3DMotionModelSet(arg0->model[0], arg0->motion[4]);
                    Hu3DMotionTimeSet(arg0->model[0], 8.0f);
                    Hu3DMotionAttrSet(arg0->model[0], 3, 0);
                    Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[0]].motId, 0, 0x14, 2);
                    if (m249_vineBaseTbl[arg1] < 8) {
                        Hu3DModelLayerSet(arg0->model[0], 0);
                    }
                    if (m249_vineBaseTbl[arg1] >= 8 && (m249_seqNo == 2 || (m249_seqNo == 3 && m249_seqTimer < 30))) {
                        m249_goalTurnTimerTbl[arg1] = 1;
                    }
                }
            }
            if (m249_playerStateTbl[arg1] == 0 && m249_frameCnt >= 0x66) {
                for (var_s5 = 5; var_s5 > m249_vineNoTbl[arg1]; var_s5--) {
                    if (m249_vineLenTbl[arg1][var_s5] == 0) {
                        continue;
                    }
                    if (HuSqrtf((m249_playerXTbl[arg1] - sp18[var_s5]) * (m249_playerXTbl[arg1] - sp18[var_s5]) + (m249_playerYTbl[arg1] - sp30[var_s5]) * (m249_playerYTbl[arg1] - sp30[var_s5])) < 90.0) {
                        m249_playerStateTbl[arg1] = 1;
                        m249_vineNoTbl[arg1] = var_s5;
                        m249_vineSegPosTbl[arg1] = m249_vineLenTbl[arg1][var_s5];
                        m249_holdTimeTbl[arg1] = 0;
                        m249_playerXTbl[arg1] = sp18[m249_vineNoTbl[arg1]];
                        m249_playerYTbl[arg1] = sp30[m249_vineNoTbl[arg1]];
                        m249_swingAngleTbl[arg1] = sp48[m249_vineNoTbl[arg1]];
                        Hu3DMotionModelSet(arg0->model[0], arg0->motion[1]);
                        Hu3DMotionAttrSet(arg0->model[0], 2, 2);
                        if (m249_vineNoTbl[arg1] != 1) {
                            HuAudPlayerFXPlay(0x492, arg1);
                        }
                        break;
                    }
                    for (var_s4 = m249_vineLenTbl[arg1][var_s5] - 1; var_s4 >= 0; var_s4--) {
                        if (HuSqrtf((m249_playerXTbl[arg1] - sp60[var_s5][var_s4]) * (m249_playerXTbl[arg1] - sp60[var_s5][var_s4]) + (m249_playerYTbl[arg1] - sp138[var_s5][var_s4]) * (m249_playerYTbl[arg1] - sp138[var_s5][var_s4])) < 40.0) {
                            m249_playerStateTbl[arg1] = 1;
                            m249_vineNoTbl[arg1] = var_s5;
                            m249_vineSegPosTbl[arg1] = var_s4;
                            m249_holdTimeTbl[arg1] = 0;
                            m249_playerXTbl[arg1] = sp18[m249_vineNoTbl[arg1]];
                            m249_playerYTbl[arg1] = sp30[m249_vineNoTbl[arg1]];
                            m249_swingAngleTbl[arg1] = sp48[m249_vineNoTbl[arg1]];
                            Hu3DMotionModelSet(arg0->model[0], arg0->motion[2]);
                            Hu3DMotionAttrSet(arg0->model[0], 2, 2);
                            if (m249_vineNoTbl[arg1] != 1) {
                                HuAudPlayerFXPlay(0x492, arg1);
                            }
                            break;
                        }
                        if (m249_playerStateTbl[arg1] == 1) {
                            break;
                        }
                    }
                }
            }
        }
    }
    if (m249_winner == 4 && arg2 == 1) {
        m249_winner = 2 - arg1;
    }
    if (m249_playerStateTbl[arg1] == 1) {
        temp_f2_17 = m249_vineSegPosTbl[arg1];
        temp_f0_13 = temp_f2_17;
        temp_f6_4 = temp_f2_17 - temp_f0_13;
        m249_playerXTbl[arg1] = (temp_f6_4 == 0.0)
                                            ? sp60[m249_vineNoTbl[arg1]][temp_f0_13]
                                            : (sp60[m249_vineNoTbl[arg1]][temp_f0_13] * (1.0 - temp_f6_4) + temp_f6_4 * sp60[m249_vineNoTbl[arg1]][temp_f0_13 + 1]);
        m249_playerYTbl[arg1] = (temp_f6_4 == 0.0)
                                            ? sp138[m249_vineNoTbl[arg1]][temp_f0_13]
                                            : (sp138[m249_vineNoTbl[arg1]][temp_f0_13] * (1.0 - temp_f6_4) + temp_f6_4 * sp138[m249_vineNoTbl[arg1]][temp_f0_13 + 1]);
        m249_swingAngleTbl[arg1] = (temp_f6_4 == 0.0)
                                            ? sp210[m249_vineNoTbl[arg1]][temp_f0_13]
                                            : (sp210[m249_vineNoTbl[arg1]][temp_f0_13] * (1.0 - temp_f6_4) + temp_f6_4 * sp210[m249_vineNoTbl[arg1]][temp_f0_13 + 1]);
    }
    omSetTra(arg0,
             m249_playerXTbl[arg1] + cosdf(m249_swingAngleTbl[arg1]) * 125.0,
             m249_playerYTbl[arg1] + sindf(m249_swingAngleTbl[arg1]) * 125.0,
             0.0f);
    if (m249_goalTurnTimerTbl[arg1] > 0) {
        var_f4_3 = 90.0f;
        if (m249_goalTurnTimerTbl[arg1] >= 0x33) {
            temp_f20_5 = (m249_goalTurnTimerTbl[arg1] - 50) / 10.0f;
            temp_f20_5 = ((-cosdf(temp_f20_5 * 180.0f) + 1.0f) / 2.0f) * 0.75 + temp_f20_5 * 0.25;
            var_f4_3 = 90.0 - temp_f20_5 * 95.0;
        }
        omSetRot(arg0, 0, var_f4_3, m249_swingAngleTbl[arg1] + 90.0);
        m249_goalTurnTimerTbl[arg1] += (m249_goalTurnTimerTbl[arg1] < 60);
        if (m249_seqNo == 3 && m249_winner != arg1) {
            m249_goalTurnTimerTbl[arg1] = 0;
        }
    } else {
        omSetRot(arg0, 0,
                 (m249_fallTimerTbl[arg1] > 0.0f && m249_swingAngleTbl[arg1] > -90.0) ? -90.0f : 90.0f,
                 m249_swingAngleTbl[arg1] + 90.0);
    }
    m249_blinkTimerTbl[arg1] -= (m249_blinkTimerTbl[arg1] != 0 && m249_blinkTimerTbl[arg1] < 0xFF);
    if (m249_seqNo < 4 || m249_seqNo == 5 || m249_winner != arg1) {
        Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, (m249_blinkTimerTbl[arg1] != 0 && ((arg1 + m249_frameCnt) & 1)) ? HU3D_ATTR_DISPOFF : HU3D_ATTR_NONE);
    }
    m249_prevXTbl[arg1] = m249_playerXTbl[arg1];
    m249_prevYTbl[arg1] = m249_playerYTbl[arg1];
    if (m249_vineBaseTbl[arg1] <= 0 && m249_cameraXTbl[arg1] <= 550.0f) {
        m249_cameraXTbl[arg1] += -m249_vineBaseTbl[arg1] * 450.0 - (m249_cameraXTbl[arg1] - 550.0);
    }
    if (m249_vineBaseTbl[arg1] >= 12 && m249_cameraXTbl[arg1] >= 1250.0f) {
        m249_cameraXTbl[arg1] -= (m249_vineBaseTbl[arg1] - 12) * 450.0 + m249_cameraXTbl[arg1] - 1250.0;
    }
    m249_scrollTbl[arg1][0] += m249_cameraXTbl[arg1] - sp3CC;
    m249_scrollTbl[arg1][1] += m249_cameraXTbl[arg1] - sp3CC;
    m249_scrollTbl[arg1][2] += m249_cameraXTbl[arg1] - sp3CC;
    m249_scrollTbl[arg1][3] += m249_cameraXTbl[arg1] - sp3CC;
    if (m249_vineBaseTbl[arg1] < 8) {
        Hu3DModelPosSet(m249_stageObj->model[arg1 + 2],
                        ((-m249_cameraXTbl[arg1] - m249_vineBaseTbl[arg1] * 450.0 - 75.0) / 15.0) * 16.0 + m249_cameraXTbl[arg1] + 437.5,
                        (arg1 != 0 ? -388.3333333333333 : -361.6666666666667) + (arg1 != 0 ? 23.333333333333332 : 0.0) + 1.0,
                        -250.0f);
        Hu3DModelScaleSet(m249_stageObj->model[arg1 + 2], 1.4375f, 1.4375f, 1.0f);
    } else {
        Hu3DModelAttrSet(m249_stageObj->model[arg1 + 2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(m249_stageObj->model[arg1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        if (arg1 == 0) {
            omSetTra(m249_stageObj, (m249_vineBaseTbl[0] - 8) * -450.0 + 3750.0, 172.0f, 0);
        } else {
            Hu3DModelPosSet(m249_stageObj->model[1], (m249_vineBaseTbl[arg1] - 8) * -450.0 + 3750.0, 172.0f, 0.0f);
        }
    }
    CenterM[arg1].x = m249_cameraXTbl[arg1];
    if (m249_vineNoTbl[arg1] + m249_vineBaseTbl[arg1] != m249_iconPosTbl[arg1]) {
        if (m249_iconPosTbl[arg1] <= 15.0f) {
            m249_iconPosPrevTbl[arg1] = m249_iconPosTbl[arg1] * (1.0 - m249_iconMoveTimerTbl[arg1] / 20.0) + m249_iconPosPrevTbl[arg1] * (m249_iconMoveTimerTbl[arg1] / 20.0);
            m249_iconPosTbl[arg1] = m249_vineNoTbl[arg1] + m249_vineBaseTbl[arg1];
            m249_iconMoveTimerTbl[arg1] = 0x14;
        }
    }
    if (m249_playerStateTbl[arg1] == 2 && m249_seqNo >= 2U // TODO: why 2U?
        && m249_iconPosTbl[arg1] <= 15.0f) {
        m249_iconPosPrevTbl[arg1] = m249_iconPosTbl[arg1] * (1.0 - m249_iconMoveTimerTbl[arg1] / 20.0) + m249_iconPosPrevTbl[arg1] * (m249_iconMoveTimerTbl[arg1] / 20.0);
        m249_iconPosTbl[arg1] = 16.0f;
        m249_iconMoveTimerTbl[arg1] = 0x14;
    }
    if (m249_winner == 2 && m249_iconPosTbl[arg1] > 15.0f && (m249_seqNo == 3 || m249_seqNo == 5 || m249_seqNo == 6)) {
        m249_iconPosTbl[arg1] = m249_iconPosTbl[arg1] * (1.0 - m249_iconMoveTimerTbl[arg1] / 20.0) + m249_iconPosPrevTbl[arg1] * (m249_iconMoveTimerTbl[arg1] / 20.0);
        m249_iconPosPrevTbl[arg1] = m249_iconPosTbl[arg1];
        m249_iconMoveTimerTbl[arg1] = 0;
    }
    m249_iconMoveTimerTbl[2 + arg1] = m249_vineBaseTbl[arg1];
    if (arg2 == 1) {
        m249_frameCnt++;
    }
}
