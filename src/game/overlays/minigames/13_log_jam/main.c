#include "common.h"
#include "game/overlays/minigame.h"
#include "game/overlays/mgcamera.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"
#include "game/hmfmath.h"
#include "game/wipe.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/gamework.h"
#include "math.h"
#include "game/hmfdraw.h"
#include "game/hmfspr.h"
#include "game/input.h"
#include "game/printfunc.h"
#include "game/gamemes.h"

typedef struct LogJamScore { // 0xC bytes, two entries
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
} LogJamScore;

typedef struct LogJamLogWork LogJamLogWork;

struct LogJamLogWork { // 0x78 bytes, 0x20 entries allocated by m219_LogInit
    s16 unk_00;
    s16 unk_02[3]; // model ids
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    f32 unk_10; // position
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C; // rotation
    f32 unk_20;
    f32 unk_24;
    f32 unk_28; // velocity
    f32 unk_2C;
    f32 unk_30;
    s16 unk_34[0x0F];
    s16 unk_52;
    f32 unk_54[8]; // callback work
    void (*unk_74)(LogJamLogWork *work);
};

typedef struct LogJamPlayerWork { // 0x38 bytes, 4 entries allocated by m219_TeamInit
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08; // state
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    f32 unk_10;
    s32 unk_14; // motion id
    s16 unk_18; // player index
    s16 unk_1A; // pad index
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20; // CPU difficulty
    s16 unk_22;
    s16 unk_24;
    s16 unk_26;
    s16 unk_28;
    s16 unk_2A;
    u16 unk_2C; // CPU buttons
    s16 unk_2E;
    s16 unk_30;
    s16 unk_32;
    s16 unk_34;
    s16 unk_36;
} LogJamPlayerWork;

typedef struct LogJamTeam { // 0x48 bytes, 2 entries allocated by m219_TeamInit
    omObjData *unk_00;
    omObjData *unk_04;
    LogJamPlayerWork *unk_08;
    LogJamPlayerWork *unk_0C;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    f32 unk_24; // position
    f32 unk_28;
    f32 unk_2C;
    f32 unk_30; // rotation
    f32 unk_34;
    f32 unk_38;
    f32 unk_3C; // velocity
    f32 unk_40;
    f32 unk_44;
} LogJamTeam;

typedef union LogJamColor {
    u32 word;
    u8 rgba[4];
} LogJamColor;

typedef struct LogJamEffect { // 0x34 bytes, 8 entries per effect set
    u16 active;
    s16 model;
    LogJamColor color;
    f32 frame;
    f32 speed;
    Vec pos;
    Vec vel;
    Vec scale;
} LogJamEffect;

typedef struct LogJamCloud { // 0x24 bytes, 5 entries
    s16 index;
    s16 group;
    s16 angle;
    f32 base;
    Vec2f pos;
    Vec2f scale;
    f32 speed;
    s32 unk_20;
} LogJamCloud;

typedef union LogJamWorkBytes { // packs the top byte of each work word
    u32 word;
    struct {
        u32 byte3 : 8;
        u32 byte2 : 8;
        u32 byte1 : 8;
        u32 byte0 : 8;
    } bytes;
} LogJamWorkBytes;

Vec m219_playerPosTbl[4] = { { -233.0f, 0.0f, 70.0f }, { -131.0f, 0.0f, -5.0f }, { 131.0f, 0.0f, -5.0f }, { 233.0f, 0.0f, 70.0f } };
Vec m219_playerSetPosTbl[4] = { { -170.0f, 0.0f, 40.0f }, { -128.0f, 0.0f, 20.0f }, { 128.0f, 0.0f, 20.0f }, { 170.0f, 0.0f, 40.0f } };
Vec m219_playerWinPosTbl[4] = { { -70.0f, 0.0f, 200.0f }, { -190.0f, 0.0f, 250.0f }, { 190.0f, 0.0f, 250.0f }, { 70.0f, 0.0f, 200.0f } };
f32 m219_playerRotTbl[4] = { 45.0f, 15.0f, -15.0f, -45.0f };
Vec m219_stumpPosTbl[2] = { { -100.0f, 50.0f, 115.0f }, { 100.0f, 50.0f, 115.0f } };
LogJamColor m219_chipColor = { 0xE9DDA180 };
LogJamColor m219_whiteColor = { 0xFFFFFFFF };
s32 m219_winAnimTbl[8] = { 0x000200A5, 0x000300A5, 0x000700A5, 0x000400A5, 0x000500A5, 0x000600A5, 0x000800A5, 0x0009001C };
s32 m219_loseAnimTbl[8] = { 0x000200A6, 0x000300A6, 0x000700A6, 0x000400A6, 0x000500A6, 0x000600A6, 0x000800A6, 0x0009001D };
s32 m219_exitTimer = 0;
s32 m219_playerOrderTbl[4] = { 0, 1, 2, 3 };
s16 m219_teamPlayerAltTbl[4][2][2] = { { { 0, 1 }, { 2, 3 } }, { { 3, 0 }, { 1, 2 } }, { { 2, 3 }, { 0, 1 } }, { { 1, 2 }, { 3, 0 } } };
s16 m219_roleTbl[4] = { 0, 1, 1, 0 };
s16 m219_playerPrioTbl[4] = { 18, 19, 21, 20 };
s32 m219_voiceChrTbl[8] = { 0x00020000, 0x00030000, 0x00070000, 0x00040000, 0x00050000, 0x00060000, 0x00080000, 0x00090000 };
s32 m219_voiceNoTbl[4] = { 0x2F, 0x30, 0x36, 0x37 };
s32 m219_heldLogMdlIdxTbl[3] = { 3, 4, 5 };
f32 m219_chrHeightTbl[8] = { 200.0f, 200.0f, 200.0f, 200.0f, 200.0f, 250.0f, 200.0f, 200.0f };
s32 m219_logMdlFileTbl[9] = { 0x00340003, 0x00340004, 0x00340005, 0x00340006, 0x00340007, 0x00340008, 0x00340009, 0x0034000A, 0x0034000B };
Vec2f m219_cloudPosTbl[5] = { { 120.0f, 30.0f }, { 360.0f, 45.0f }, { 0.0f, 52.0f }, { 240.0f, 60.0f }, { 480.0f, 75.0f } };
f32 m219_cloudScaleTbl[5] = { 0.7f, 0.6f, 0.55f, 0.47f, 0.4f };
s16 m219_scoreXTbl[2] = { 38, 282 };
s32 m219_cameraDebugMode = 0;
s32 m219_cameraDebugX = 0;
s32 m219_cameraDebugY = 0;

Gfx m219_gfxRdpInit[] = {
    gsSPSegment(0x00, 0x00000000),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipelineMode(G_PM_1PRIMITIVE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x0000, 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPNoOp(),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx m219_gfxRspInit[] = {
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx m219_gfxInit[] = {
    gsSPDisplayList(m219_gfxRspInit),
    gsSPDisplayList(m219_gfxRdpInit),
    gsSPEndDisplayList(),
};

Gfx m219_gfxBillboardInit[] = {
    gsDPPipeSync(),
    gsSPDisplayList(m219_gfxInit),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPSetGeometryMode(G_ZBUFFER | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x00),
    gsDPSetPrimColor(0, 0, 0x00, 0x00, 0x00, 0xFF),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

omObjData *m219_mainObj BSS;
s32 m219_flag10F BSS;
s32 m219_frameCnt BSS;
s32 m219_phaseTimer BSS;
s32 m219_timer BSS;
s32 m219_phase BSS;
s32 m219_resultWait BSS;
LogJamTeam *m219_teamTbl BSS;
omObjData *m219_teamObjTbl[2] BSS;
LogJamPlayerWork *m219_playerWorkTbl BSS;
s16 m219_winTeamNo BSS;
omObjData *m219_logObj BSS;
LogJamLogWork *m219_logTbl BSS;
s16 *m219_logMdlTbl BSS;
s16 *m219_sprTbl BSS;
LogJamScore *m219_scoreTbl BSS;
LogJamCloud *m219_cloudTbl BSS;
omObjData *m219_smokeObj BSS;
LogJamEffect *m219_smokeTbl BSS;
omObjData *m219_missObj BSS;
LogJamEffect *m219_missTbl BSS;
MgCameraKey m219_cameraKeyTbl[2] BSS; // target, origin
s32 m219_cameraMoveTimer BSS;
s32 m219_cameraMoveTime BSS;
s32 m219_cameraMoveF BSS;
u8 m219_cameraMoveFPad[4] BSS; /* Unreferenced. */
MinigameFlow m219_mgFlow BSS;
extern s32 omCharModelNoTbl[][6];
extern s16 motionBakeMtxCnt;
extern u8 omAllPauseF;
extern s16 Hu3DModelTag;
extern u8 Hu3DBufNo;
extern s16 *motionBakeNodeMap;
extern HuMtx4F *motionBakeMtx;
extern s16 Hu3DObjMtxStackIdx;
extern HuMtx4F Hu3DObjMtxStack[];

void m219_MainObjInit(omObjData *object);
void m219_MainObjMain(omObjData *object);
void m219_ExitObjMain(omObjData *object);
void m219_ExitCheck(omObjData *object);
void m219_TeamInit(void);
void m219_PlayerObjMain(omObjData *object);
void m219_PlayerHeldLogKill(void);
void m219_TeamObjMain(omObjData *object);
void m219_PlayerObjInit(omObjData *object);
void m219_SetterUpdate(omObjData *object, LogJamTeam *team);
void m219_ChopperUpdate(omObjData *object, LogJamTeam *team);
void m219_SetterComInput(omObjData *object, LogJamTeam *team);
void m219_ChopperComInput(omObjData *object, LogJamTeam *team);
s16 m219_JumpTimeCalc(f32 arg0, f32 arg1);
void m219_LogInit(void);
s16 m219_LogCreate(s16 arg0, s16 arg1);
void m219_LogPosSet(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void m219_LogRotSet(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void m219_LogSplit(s16 arg0);
void m219_LogObjMain(omObjData *object);
s16 m219_PlayerAllStateCheck(s16 arg0);
void m219_LogClose(void);
LogJamLogWork *m219_LogGet(s16 arg0);
void m219_LogKill(s16 arg0);
void m219_LogHalfMove(LogJamLogWork *work);
void m219_LogMdlInit(void);
s16 m219_LogMdlLink(s16 arg0, s16 arg1);
void m219_LogMdlClose(void);
void m219_StageObjCreate(void);
void m219_StageObjInit(omObjData *object);
void m219_StageObjMain(omObjData *object);
u16 m219_SprAnimRead(s32 file);
void m219_ScoreInit(void);
s32 m219_SmokeCreate(Vec *pos, Vec *vel, Vec *scale, f32 speed, u8 *color);
void m219_ScoreObjMain(omObjData *object);
void m219_ScoreSet(s16 arg0, s16 arg1);
void m219_SmokeInit(void);
void m219_SmokeObjMain(omObjData *object);
void m219_MissInit(void);
void m219_MissObjMain(omObjData *object);
s32 m219_MissCreate(Vec *pos, Vec *vel, Vec *scale, f32 speed, u8 *color);
void m219_CameraInit(void);
void m219_CameraMoveObjMain(omObjData *object);
void m219_CameraKeyStore(s32 arg0);
void m219_CameraMoveStart(f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames);
void m219_CameraPosUpdate(s32 camIndex);
f32 m219_AngleDiffCalc(f32 arg0, f32 arg1);
f32 m219_AngleStepCalc(f32 target, f32 current, f32 step);
f32 m219_InterpCalc(f32 t, f32 start, f32 end);
f32 m219_AngleInterpCalc(f32 t, f32 start, f32 end);
void m219_WorkPtrSet(omObjData *object, u32 arg1);
u32 m219_WorkPtrGet(omObjData *object);
f32 m219_StepCalc(f32 arg0, f32 arg1, f32 arg2);
void m219_MotShiftSet(omObjData *object, s16 motion, s16 shift);
void m219_MotShiftTimeSet(omObjData *object, s16 motion, s16 time);
void m219_MotSet(omObjData *object, s16 motion, s16 time);
void m219_MotStop(omObjData *object);
void m219_MotShiftUpdate(omObjData *object);
void m219_EffMdlUpdate(omObjData *object);
void m219_NodeMtxCalc(s16 model, const char *name, HuMtx4F *out);
void m219_NodeWorldMtxCalc(omObjData *object, const char *name, HuMtx4F out);
s32 m219_BillboardColorMdlCreate(HuSprAnimData *sprite, u8 *color);
s32 m219_BillboardColorMdlLink(HuSprAnimData *sprite, u16 model, u8 *color);
void m219_BillboardColorPatSet(u16 model, HuSprAnimData *sprite, u16 frame, u8 *color);
s32 m219_BillboardVtxCreate(HuSprAnimData *sprite, HmfData *data, f32 scale, s16 xOffset, s16 yOffset);

void m219_ObjectSetup(void) {
    omObjData *obj;
    u8 camIndex;

    MapCollInit(50);
    omInitObjMan(50, 0);
    omGameSysInit();
    Hu3DSprModelInit(16);
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -56.0f, 50.0f, 56.0f);
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 30.0f, 80.0f, 4000.0f);
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    mgItemObjNum = 0;
    m219_timer = 900;
    m219_phaseTimer = 0;
    m219_frameCnt = 0;
    m219_phase = -1;
    m219_resultWait = 0;
    m219_winTeamNo = -1;
    m219_sprTbl = HuMemAllocTag(0x40, TAG_OVERLAY);
    m219_mainObj = omAddObj(0x20, 0, 0, -1, m219_MainObjInit);
    memset(&m219_mgFlow, 0, 0x28);
    m219_mgFlow.type = MINIGAME_BATTLE;
    MgFlowInit(&m219_mgFlow);
}

void m219_MainObjInit(omObjData *object) {
    object->func = m219_MainObjMain;
    m219_StageObjCreate();
    m219_ScoreInit();
    m219_SmokeInit();
    m219_MissInit();
    m219_LogMdlInit();
    m219_TeamInit();
    m219_LogInit();
    m219_CameraInit();
    if (_CheckFlag(10)) {
        m219_flag10F = 1;
    }
}

void m219_MainObjMain(omObjData *object) {
    LogJamTeam *team0;
    LogJamTeam *team1;

    switch (m219_phase) {
        case -1:
            if (m219_phaseTimer >= 2) {
                WipeCreateIn(WIPE_TYPE_PREV, 16);
                m219_phase = 0;
                m219_phaseTimer = 0;
            }
            break;
        case 0:
            if (WipeStatGet() == 0) {
                GMesCreate(5);
                HuAudFXPlay(0xE);
                m219_phase++;
                m219_phaseTimer = 0;
            }
            break;
        case 1:
            if (m219_phaseTimer == 30) {
                HuAudSeqPlay(0x2E);
            }
            if (GMesStatGet() == 0) {
                GMesCreate(0x1A, (m219_timer + 29) / 30, 156, 32);
                MgFlowStatSet(MG_STATE_PLAY);
                m219_phase++;
            }
            break;
        case 2:
            m219_timer--;
            GMesTimerValueSet((m219_timer + 29) / 30);
            if (m219_timer <= 0) {
                GMesTimerEnd();
                GMesCreate(0x10);
                MgFlowStatSet(MG_STATE_FINISH);
                HuAudSeqFadeOut(120);
                m219_timer = 0;
                m219_phaseTimer = 0;
                m219_phase++;
            }
            break;
        case 3:
            if (m219_PlayerAllStateCheck(14) && GMesStatGet() == 0) {
                MgFlowStatSet(MG_STATE_RESULT);
                m219_LogClose();
                m219_PlayerHeldLogKill();
                m219_LogMdlClose();
                m219_phaseTimer = 0;
                m219_phase++;
            }
            break;
        case 4:
            if (m219_PlayerAllStateCheck(17)) {
                team0 = (LogJamTeam *)m219_WorkPtrGet(m219_teamObjTbl[0]);
                team1 = (LogJamTeam *)m219_WorkPtrGet(m219_teamObjTbl[1]);
                if (team0->unk_12 > team1->unk_12) {
                    GMesCreate(0x1E, team0->unk_08->unk_1C, team0->unk_0C->unk_1C);
                    GwPlayer[team0->unk_08->unk_18].bonusCoin += 10;
                    GwPlayer[team0->unk_0C->unk_18].bonusCoin += 10;
                    team0->unk_08->unk_06 = team0->unk_0C->unk_06 = 0;
                    team1->unk_08->unk_06 = team1->unk_0C->unk_06 = 1;
                    HuAudSeqPlay(0x66);
                    m219_resultWait = 140;
                } else if (team0->unk_12 < team1->unk_12) {
                    GMesCreate(0x1E, team1->unk_08->unk_1C, team1->unk_0C->unk_1C);
                    GwPlayer[team1->unk_08->unk_18].bonusCoin += 10;
                    GwPlayer[team1->unk_0C->unk_18].bonusCoin += 10;
                    team0->unk_08->unk_06 = team0->unk_0C->unk_06 = 1;
                    team1->unk_08->unk_06 = team1->unk_0C->unk_06 = 0;
                    HuAudSeqPlay(0x66);
                    m219_resultWait = 140;
                } else {
                    GMesCreate(0x20);
                    team0->unk_08->unk_06 = team0->unk_0C->unk_06 = 1;
                    team1->unk_08->unk_06 = team1->unk_0C->unk_06 = 1;
                    HuAudSeqPlay(0x6C);
                    m219_resultWait = 144;
                }
                m219_phaseTimer = 0;
                m219_phase++;
            }
            break;
        case 5:
            if (GMesStatGet() == 0) {
                m219_phaseTimer = 0;
                m219_phase++;
            }
            break;
        case 6:
            if (m219_phaseTimer >= 16) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 16);
                HuAudSeqFadeOut(16);
                HuAudFXAllFadeOut(16);
                m219_phaseTimer = 0;
                m219_phase++;
            }
            break;
        default:
            if (WipeStatGet() == 0) {
                object->func = m219_ExitObjMain;
            }
            break;
    }
    m219_ExitCheck(object);
    m219_frameCnt++;
    m219_phaseTimer++;
}

void m219_ExitObjMain(omObjData *object) {
    HuAudSeqStop();
    omOvlReturnEx(1);
}

void m219_ExitCheck(omObjData *object) {
    if (m219_exitTimer != 0) {
        if (m219_exitTimer == 1) {
            object->func = m219_ExitObjMain;
        }
        m219_exitTimer--;
    } else if (omSysExitReq == 1 && WipeStatGet() == 0) {
        m219_exitTimer = 16;
        WipeCreateOut(WIPE_TYPE_NORMAL, m219_exitTimer);
        HuAudSeqFadeOut(m219_exitTimer);
        HuAudFXAllFadeOut((s16)m219_exitTimer);
    }
}

void m219_TeamInit(void) {
    s32 playerIds[2][2];
    LogJamTeam *team;
    LogJamPlayerWork *work;
    omObjData *obj;
    s32 i;
    s32 j;
    s32 invalid;
    s32 group0Count;
    s32 group1Count;
    s32 group2Count;
    s32 group3Count;
    s32 group;

    m219_teamTbl = HuMemAllocTag(sizeof(LogJamTeam) * 2, TAG_OVERLAY);
    team = m219_teamTbl;
    memset(team, 0, sizeof(LogJamTeam) * 2);
    m219_playerWorkTbl = HuMemAllocTag(sizeof(LogJamPlayerWork) * 4, TAG_OVERLAY);
    memset(m219_playerWorkTbl, 0, sizeof(LogJamPlayerWork) * 4);
    invalid = FALSE;
    group3Count = 0;
    group2Count = 0;
    group1Count = 0;
    group0Count = 0;
    for (i = 0; i < 4; i++) {
        switch (group = GwPlayer[m219_playerOrderTbl[i]].group) {
            case 0:
                if (group0Count > 0) {
                    invalid = TRUE;
                } else {
                    playerIds[0][1] = m219_playerOrderTbl[i];
                    group0Count++;
                }
                break;
            case 1:
                if (group1Count > 0) {
                    invalid = TRUE;
                } else {
                    playerIds[0][0] = m219_playerOrderTbl[i];
                    group1Count++;
                }
                break;
            case 2:
                if (group2Count > 0) {
                    invalid = TRUE;
                } else {
                    playerIds[1][0] = m219_playerOrderTbl[i];
                    group2Count++;
                }
                break;
            case 3:
                if (group3Count > 0) {
                    invalid = TRUE;
                } else {
                    playerIds[1][1] = m219_playerOrderTbl[i];
                    group3Count++;
                }
                break;
            default:
                invalid = TRUE;
                break;
        }
        if (invalid) {
            break;
        }
    }
    if (invalid) {
        group = rand8() & 3;
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                playerIds[i][j] = m219_teamPlayerAltTbl[group][i][j];
            }
        }
    }
    MgShadowAltSet(1);
    MgPlayerParamReset();
    for (i = 0; i < 2; i++, team++) {
        team->unk_10 = i;
        team->unk_12 = 0;
        team->unk_14 = 0;
        team->unk_16 = -1;
        team->unk_18 = -1;
        team->unk_1A = 0;
        team->unk_1C = -1;
        team->unk_1E = 0;
        team->unk_20 = 0;
        team->unk_24 = team->unk_28 = team->unk_2C = 0.0f;
        team->unk_30 = team->unk_34 = team->unk_38 = 0.0f;
        team->unk_3C = 0.0f;
        team->unk_40 = team->unk_44 = 0.0f;
        m219_teamObjTbl[i] = omAddObj(i + 16, 0, 0, -1, m219_TeamObjMain);
        m219_WorkPtrSet(m219_teamObjTbl[i], (u32)team);
        for (j = 0; j < 2; j++) {
            work = &m219_playerWorkTbl[i * 2 + j];
            work->unk_00 = i * 2 + j;
            work->unk_04 = i;
            work->unk_02 = m219_roleTbl[work->unk_00];
            work->unk_18 = playerIds[i][j];
            obj = mgPlayerObjTbl[mgPlayerObjNum] =
                omAddObj(m219_playerPrioTbl[work->unk_00], 8, 11, -1, m219_PlayerObjInit);
            mgPlayerObjNum++;
            obj->trans.x = m219_playerPosTbl[work->unk_00].x;
            obj->trans.z = m219_playerPosTbl[work->unk_00].z;
            obj->rot.y = m219_playerRotTbl[work->unk_00];
            m219_WorkPtrSet(obj, (u32)work);
            if (work->unk_02 == 0) {
                team->unk_00 = obj;
                team->unk_08 = work;
            } else {
                team->unk_04 = obj;
                team->unk_0C = work;
            }
        }
    }
}

void m219_TeamObjMain(omObjData *object) {
    Vec pos;
    Vec scale = { 0.7f, 0.7f, 0.7f };
    LogJamTeam *team;
    LogJamLogWork *player;
    s16 done = FALSE;

    team = (LogJamTeam *)m219_WorkPtrGet(object);
    m219_SetterUpdate(team->unk_00, team);
    m219_ChopperUpdate(team->unk_04, team);
    if (team->unk_12 >= 30) {
        team->unk_12 = 29;
    }
    m219_ScoreSet(team->unk_10, team->unk_12);
    if (MgFlowStatGet() == MG_STATE_FINISH && team->unk_16 != -1) {
        player = m219_LogGet(team->unk_16);
        pos.x = player->unk_10;
        pos.z = player->unk_18;
        pos.y = player->unk_14 + 40.0000005960464478;
        m219_SmokeCreate(&pos, NULL, &scale, 1.0f, m219_whiteColor.rgba);
        m219_LogKill(team->unk_16);
        team->unk_16 = team->unk_18 = -1;
    }
    if (team->unk_1C != -1) {
        team->unk_30 += team->unk_40;
        team->unk_34 += team->unk_44;
        team->unk_28 += team->unk_3C;
        team->unk_3C -= 1.6333001f;
        team->unk_24 = m219_StepCalc(m219_stumpPosTbl[team->unk_10 ^ 1].x, team->unk_24, 7.0f);
        team->unk_2C = m219_StepCalc(m219_stumpPosTbl[team->unk_10 ^ 1].z, team->unk_2C, 7.0f);
        if (team->unk_28 < 184.0000033378601 && team->unk_3C <= 0.0f) {
            done = TRUE;
            team->unk_30 = -225.0f;
            team->unk_28 = 184.0f;
        }
        Hu3DModelPosSet(team->unk_1C, team->unk_24, team->unk_28, team->unk_2C);
        Hu3DModelRotSet(team->unk_1C, 0.0f, team->unk_34, 0.0f);
        if (team->unk_20 >= 0) {
            pos.x = team->unk_24;
            pos.z = team->unk_2C;
            pos.y = team->unk_28 - 50.0;
            m219_SmokeCreate(&pos, NULL, &scale, 1.0f, m219_whiteColor.rgba);
            Hu3DModelAttrSet(team->unk_1C, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            done = TRUE;
        }
        HuMtxIdentF(Hu3DData[team->unk_1C].mtx);
        mtxTransCat(Hu3DData[team->unk_1C].mtx, 0.0f, -50.0f, 0.0f);
        mtxRotCat(Hu3DData[team->unk_1C].mtx, team->unk_30, 0.0f, 0.0f);
        team->unk_20++;
        if (done) {
            team->unk_1C = -1;
        }
    }
    team->unk_1A++;
}

void m219_PlayerObjInit(omObjData *object) {
    LogJamPlayerWork *work;
    MgPlayerWork *data;
    s16 player;
    s16 chr;
    s32 model;
    s32 motion;
    s16 i;
    s32 index;

    work = (LogJamPlayerWork *)m219_WorkPtrGet(object);
    player = work->unk_18;
    chr = GwPlayer[player].chr;
    work->unk_1C = chr;
    work->unk_1A = GwPlayer[player].pad;
    work->unk_1E = GwPlayer[player].stat & 1;
    work->unk_20 = GwPlayer[player].cpu_difficulty;
    model = omCharModelNoTbl[chr][0];
    motion = omCharModelNoTbl[chr][2];
    MgPlayerCreate(object, model, motion, player, 0x6A9, 0x299);
    data = object->data;
    data->unk50 &= ~1;
    data->unkEC = NULL;
    if (work->unk_02 == 1) {
        object->model[2] = Hu3DModelRead(0x340000, 0xB9);
        Hu3DModelAttrSet(object->model[2], 0x4000, 0x4000);
        Hu3DModelHookSet(object->model[2], object->model[0], "item_hook");
        for (i = 0; i < 3; i++) {
            object->model[i + 3] = m219_LogMdlLink(i, 0);
            Hu3DModelAttrSet(object->model[i + 3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(object->model[i + 3], 0x4000, 0x4000);
            Hu3DModelHookSet(object->model[i + 3], object->model[2], "m219-item-f");
        }
    } else {
        for (i = 0; i < 3; i++) {
            object->model[i + 3] = m219_LogMdlLink(i, 0);
            Hu3DModelAttrSet(object->model[i + 3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(object->model[i + 3], 0x4000, 0x4000);
            Hu3DModelHookSet(object->model[i + 3], object->model[0], "item_hook");
        }
    }
    object->model[6] = Hu3DModelRead(8, 0x68D);
    Hu3DModelScaleSet(object->model[6], 0.5f, 0.5f, 0.5f);
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(chr, 0), 1, 0);
    MgPlayerMotLoad(object, 1, CharMotionDataNumGet(chr, 4), 1, 19);
    MgPlayerMotLoad(object, 2, CharMotionDataNumGet(chr, 6), 1, 27);
    if (work->unk_02 == 1) {
        MgPlayerMotLoad(object, 3, CharMotionDataNumGet(chr, 0x74), 0, 20);
        MgPlayerMotLoad(object, 4, CharMotionDataNumGet(chr, 0x75), 0, 10);
        MgPlayerMotLoad(object, 5, CharMotionDataNumGet(chr, 0x81), 0, 8);
        MgPlayerMotLoad(object, 6, CharMotionDataNumGet(chr, 0x76), 1, 0);
    } else {
        MgPlayerMotLoad(object, 7, CharMotionDataNumGet(chr, 0x77), 0, 30);
        MgPlayerMotLoad(object, 8, CharMotionDataNumGet(chr, 0x78), 0, 40);
    }
    if (chr == 5) {
        MgPlayerMotLoad(object, 9, CharMotionDataNumGet(5, 0x31), 1, 120);
        work->unk_14 = m219_voiceChrTbl[5] | 0x31;
    } else if (chr == 1 || chr == 6) {
        MgPlayerMotLoad(object, 9, CharMotionDataNumGet(chr, m219_voiceNoTbl[0]), 1, 120);
        work->unk_14 = m219_voiceChrTbl[chr] | m219_voiceNoTbl[0];
    } else {
        index = rand8() & 1;
        MgPlayerMotLoad(object, 9, CharMotionDataNumGet(chr, m219_voiceNoTbl[index]), 1, 120);
        work->unk_14 = m219_voiceChrTbl[chr] | m219_voiceNoTbl[index];
    }
    MgPlayerMotLoad(object, 10, CharMotionDataNumGet(chr, m219_voiceNoTbl[2]), 1, 120);
    work->unk_06 = -1;
    work->unk_0C = 0;
    work->unk_0A = 0;
    work->unk_22 = -1;
    work->unk_24 = -1;
    work->unk_26 = -1;
    work->unk_10 = 0.0f;
    work->unk_0E = 0;
    work->unk_28 = 0;
    work->unk_2A = 10;
    work->unk_2C = 0;
    work->unk_2E = 0;
    work->unk_30 = 4 - work->unk_20;
    if (work->unk_02 == 0) {
        work->unk_08 = 0;
        m219_MotShiftSet(object, 0, 5);
        work->unk_32 = 0;
    } else {
        work->unk_08 = 5;
        m219_MotSet(object, 4, 7);
        work->unk_32 = 4;
    }
    work->unk_34 = 0;
    object->func = m219_PlayerObjMain;
}

void m219_PlayerObjMain(omObjData *object) {
    LogJamPlayerWork *work = (LogJamPlayerWork *)m219_WorkPtrGet(object);

    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    work->unk_0C++;
    m219_MotShiftUpdate(object);
    m219_EffMdlUpdate(object);
}

void m219_PlayerHeldLogKill(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            if (mgPlayerObjTbl[i]->model[m219_heldLogMdlIdxTbl[j]] != -1) {
                Hu3DModelKill(mgPlayerObjTbl[i]->model[m219_heldLogMdlIdxTbl[j]]);
                mgPlayerObjTbl[i]->model[m219_heldLogMdlIdxTbl[j]] = -1;
            }
        }
    }
}

void m219_SetterUpdate(omObjData *object, LogJamTeam *team) {
    HuMtx4F mtx;
    Vec scale = { 0.7f, 0.7f, 0.7f };
    Vec pos;
    LogJamPlayerWork *work;
    LogJamPlayerWork *partner;
    HmfModel *model;
    s32 dir;
    f32 t = 0.0f;

    work = (LogJamPlayerWork *)m219_WorkPtrGet(object);
    model = &Hu3DData[object->model[0]];
    partner = team->unk_0C;
    if (work->unk_1E != 0) {
        m219_SetterComInput(object, team);
    }
    if (MgFlowStatGet() == MG_STATE_FINISH && work->unk_08 < 13) {
        work->unk_08 = 13;
        work->unk_0C = 0;
    }
    if (!(work->unk_08 == 1 && work->unk_0A == 0) && work->unk_08 < 13) {
        object->rot.y = m219_AngleStepCalc(m219_playerRotTbl[work->unk_00], object->rot.y, 10.0f);
    }
    switch (work->unk_08) {
        case 0:
            if (work->unk_0C >= 3.0f && MgFlowStatGet() == MG_STATE_PLAY) {
                m219_MotShiftSet(object, 7, 5);
                HuAudPlayerFXPlay(0x38A, work->unk_18);
                work->unk_08 = 1;
                work->unk_0A = 0;
                work->unk_0C = 0;
            }
            break;
        case 1:
            if (work->unk_0A == 0) {
                t = work->unk_0C / 14.0f;
                if (t < 0.0f) {
                    t = 0.0f;
                } else if (t > 1.0f) {
                    t = 1.0f;
                }
                object->rot.y = m219_AngleInterpCalc(m219_playerRotTbl[work->unk_00], 0.0f, t);
                if (model->motIdShift == 0xFF && model->motTime >= 14.0f && model->motId == object->motion[7]) {
                    work->unk_24 = (u8)(rand8() % 3);
                    Hu3DModelAttrSet(object->model[work->unk_24 + 3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    work->unk_0A++;
                    work->unk_0C = 0;
                }
            } else {
                if (model->motIdShift == 0xFF && model->motTime >= 29.0f && model->motId == object->motion[7]) {
                    work->unk_08 = 2;
                    work->unk_0A = 0;
                    work->unk_0C = 0;
                }
            }
            break;
        case 2:
            if ((HuPadBtnDown[work->unk_1A] & (A_BUTTON | B_BUTTON | Z_TRIG)) && team->unk_16 == -1 && partner->unk_22 == -1 &&
                (partner->unk_08 == 6 || partner->unk_08 == 7)) {
                switch (HuPadBtnDown[work->unk_1A]) {
                    case 0x8000:
                        dir = 0;
                        break;
                    case 0x4000:
                        dir = 1;
                        break;
                    case 0x2000:
                        dir = 2;
                        break;
                    default:
                        dir = 3;
                        break;
                }
                if (dir == work->unk_24) {
                    m219_MotShiftSet(object, 8, 5);
                    work->unk_08 = 3;
                } else {
                    m219_MotSet(object, 8, 0);
                    model->motTime = 0.0f;
                    model->motSpeed = 0.0f;
                    omVibrate(work->unk_18, 2, 3, 10);
                    work->unk_08 = 4;
                }
                work->unk_0A = 0;
                work->unk_0C = 0;
            }
            break;
        case 4:
            if (work->unk_0A == 0) {
                model->motTime += 2.0f;
                if (model->motTime >= 10.0f) {
                    pos.x = object->trans.x;
                    pos.y = object->trans.y + m219_chrHeightTbl[work->unk_1C];
                    pos.z = object->trans.z;
                    m219_MissCreate(&pos, NULL, NULL, 1.0f, NULL);
                    work->unk_0A++;
                }
            } else if (!(work->unk_0A & 1)) {
                model->motTime += 2.0f;
                if (model->motTime >= 6.0f) {
                    work->unk_0A++;
                }
            } else {
                model->motTime -= 2.0f;
                if (model->motTime <= 0.0f) {
                    if (work->unk_0A == 1 || work->unk_0A == 5 || work->unk_0A == 9) {
                        pos.x = object->trans.x;
                        pos.y = object->trans.y + m219_chrHeightTbl[work->unk_1C];
                        pos.z = object->trans.z;
                        m219_MissCreate(&pos, NULL, NULL, 1.0f, NULL);
                    }
                    work->unk_0A++;
                }
            }
            if (work->unk_0A >= 9) {
                m219_MotStop(object);
                model->motTime = 0.0f;
                work->unk_08 = 2;
                work->unk_0A = 0;
                work->unk_0C = 0;
            }
            break;
        case 3:
            if (work->unk_0A == 0) {
                if (model->motIdShift == 0xFF && model->motId == object->motion[8]) {
                    t = model->motTime / 20.0f;
                }
                if (t < 0.0f) {
                    t = 0.0f;
                } else if (t > 1.0f) {
                    t = 1.0f;
                }
                object->trans.x =
                    m219_InterpCalc(t, m219_playerPosTbl[work->unk_00].x, m219_playerSetPosTbl[work->unk_00].x);
                object->trans.z =
                    m219_InterpCalc(t, m219_playerPosTbl[work->unk_00].z, m219_playerSetPosTbl[work->unk_00].z);
                if (model->motIdShift == 0xFF && model->motTime >= 19.0f && model->motId == object->motion[8]) {
                    Hu3DModelAttrSet(object->model[work->unk_24 + 3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    work->unk_22 = m219_LogCreate(work->unk_24, 0);
                    m219_LogPosSet(work->unk_22, m219_stumpPosTbl[team->unk_10].x,
                                          m219_stumpPosTbl[team->unk_10].y, m219_stumpPosTbl[team->unk_10].z);
                    m219_LogRotSet(work->unk_22, 0.0f, 0.0f, 0.0f);
                    team->unk_16 = work->unk_22;
                    team->unk_18 = work->unk_24;
                    team->unk_1A = 0;
                    work->unk_22 = work->unk_24 = -1;
                    omVibrate(work->unk_18, 10, 0, 10);
                    work->unk_0A++;
                    work->unk_0C = 0;
                }
            } else {
                if (model->motIdShift == 0xFF && model->motId == object->motion[8]) {
                    t = (model->motTime - 19.0f) / 20.0f;
                }
                if (t < 0.0f) {
                    t = 0.0f;
                } else if (t > 1.0f) {
                    t = 1.0f;
                }
                object->trans.x =
                    m219_InterpCalc(t, m219_playerSetPosTbl[work->unk_00].x, m219_playerPosTbl[work->unk_00].x);
                object->trans.z =
                    m219_InterpCalc(t, m219_playerSetPosTbl[work->unk_00].z, m219_playerPosTbl[work->unk_00].z);
                if (model->motIdShift == 0xFF && model->motTime >= 39.0f && model->motId == object->motion[8]) {
                    m219_MotShiftSet(object, 0, 5);
                    work->unk_08 = 0;
                    work->unk_0A = 0;
                    work->unk_0C = 0;
                }
            }
            break;
        case 13:
            if (work->unk_24 != -1) {
                Hu3DModelAttrSet(object->model[work->unk_24 + 3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                m219_NodeWorldMtxCalc(object, "item_hook", mtx);
                m219_SmokeCreate((Vec *)mtx[3], NULL, &scale, 1.0f, m219_whiteColor.rgba);
                work->unk_22 = work->unk_24 = -1;
            }
            m219_MotShiftSet(object, 0, 5);
            work->unk_08 = 14;
            // fallthrough
        case 14:
            object->rot.y = m219_AngleStepCalc(0.0f, object->rot.y, 10.0f);
            object->trans.x = m219_StepCalc(m219_playerPosTbl[work->unk_00].x, object->trans.x, 10.0f);
            object->trans.z = m219_StepCalc(m219_playerPosTbl[work->unk_00].z, object->trans.z, 10.0f);
            if (MgFlowStatGet() == MG_STATE_RESULT) {
                m219_MotShiftSet(object, 1, 5);
                work->unk_10 = 32.0f;
                work->unk_0E = m219_JumpTimeCalc(32.0f, 1.6333001f);
                work->unk_08 = 15;
                work->unk_0C = 0;
            }
            break;
        case 15:
            t = (f32)work->unk_0C / work->unk_0E;
            if (t > 1.0f) {
                t = 1.0f;
            } else if (t < 0.0f) {
                t = 0.0f;
            }
            if (work->unk_0C == 6) {
                m219_MotShiftSet(object, 2, 6);
            } else if (work->unk_0C == work->unk_0E - 10) {
                m219_MotShiftSet(object, 1, 7);
            }
            object->trans.x =
                m219_InterpCalc(t, m219_playerPosTbl[work->unk_00].x, m219_playerWinPosTbl[work->unk_00].x);
            object->trans.z =
                m219_InterpCalc(t, m219_playerPosTbl[work->unk_00].z, m219_playerWinPosTbl[work->unk_00].z);
            object->trans.y += work->unk_10;
            work->unk_10 -= 1.6333001f;
            if (object->trans.y <= 0.0f) {
                m219_MotShiftSet(object, 0, 5);
                object->trans.y = 0.0f;
                work->unk_08 = 16;
                work->unk_0C = 0;
            }
            break;
        case 16:
            work->unk_08 = 17;
            work->unk_0C = 0;
            break;
        case 17:
            if (work->unk_06 != -1) {
                switch (work->unk_06) {
                    case 0:
                        m219_MotShiftSet(object, 9, 5);
                        CharAnimCreate(object->model[0], 2, work->unk_1C, m219_winAnimTbl[work->unk_1C]);
                        HuAudCharVoicePlayPlayer(work->unk_14, -1, work->unk_18);
                        break;
                    case 1:
                        m219_MotShiftSet(object, 10, 5);
                        CharAnimCreate(object->model[0], 2, work->unk_1C, m219_loseAnimTbl[work->unk_1C]);
                        break;
                }
                work->unk_06 = -1;
            }
            break;
    }
}

void m219_ChopperUpdate(omObjData *object, LogJamTeam *team) {
    HuMtx4F mtx;
    Vec scale = { 0.7f, 0.7f, 0.7f };
    LogJamPlayerWork *work;
    LogJamPlayerWork *partner;
    HmfModel *model;
    s32 dir;
    f32 time;
    f32 t;

    work = (LogJamPlayerWork *)m219_WorkPtrGet(object);
    model = &Hu3DData[object->model[0]];
    partner = team->unk_08;
    if (work->unk_1E != 0) {
        m219_ChopperComInput(object, team);
    }
    if (MgFlowStatGet() == MG_STATE_FINISH && work->unk_08 < 13) {
        work->unk_08 = 13;
        work->unk_0C = 0;
    }
    switch (work->unk_08) {
        case 5:
            if (MgFlowStatGet() == MG_STATE_PLAY) {
                m219_MotShiftSet(object, 3, 7);
                work->unk_08 = 6;
                work->unk_0A = 0;
                work->unk_0C = 0;
            }
            break;
        case 6:
            if (model->motIdShift == 0xFF && model->motTime >= 19.0f && model->motId == object->motion[3]) {
                work->unk_08 = 7;
                work->unk_0A = 0;
                work->unk_0C = 0;
            }
            break;
        case 7:
            if ((HuPadBtnDown[work->unk_1A] & (A_BUTTON | B_BUTTON | Z_TRIG)) && !(partner->unk_08 == 3 && partner->unk_0A == 0)) {
                if (HuPadBtnDown[work->unk_1A] == A_BUTTON) {
                    work->unk_26 = 0;
                } else if (HuPadBtnDown[work->unk_1A] == B_BUTTON) {
                    work->unk_26 = 1;
                } else if (HuPadBtnDown[work->unk_1A] == Z_TRIG) {
                    work->unk_26 = 2;
                } else {
                    work->unk_26 = 3;
                }
                if (work->unk_22 == 0x20) {
                    dir = work->unk_24;
                } else {
                    dir = team->unk_18;
                }
                HuAudPlayerFXPlay(0x38D, work->unk_18);
                if (dir == -1 || dir == work->unk_26) {
                    m219_MotShiftSet(object, 4, 2);
                    work->unk_08 = 8;
                    work->unk_0A = 0;
                    work->unk_0C = 0;
                } else {
                    m219_MotShiftSet(object, 5, 2);
                    work->unk_08 = 9;
                    work->unk_0A = 0;
                    work->unk_0C = 0;
                }
            }
            break;
        case 8:
            if (work->unk_22 == 0x20) {
                dir = work->unk_24;
            } else {
                dir = team->unk_18;
            }
            time = 9.0f;
            if (model->motIdShift == 0xFF && model->motTime >= time && model->motId == object->motion[4]) {
                if (dir == -1) {
                    HuAudPlayerFXPlay(0x38C, work->unk_18);
                    work->unk_08 = 12;
                    work->unk_0A = 0;
                    work->unk_0C = 0;
                    m219_MotShiftSet(object, 6, 5);
                    MgPlayerEffSet(object, 6, m219_stumpPosTbl[team->unk_10].x,
                                           m219_stumpPosTbl[team->unk_10].y, m219_stumpPosTbl[team->unk_10].z, 0.0f,
                                           0.0f);
                } else {
                    HuAudPlayerFXPlay(0x38B, work->unk_18);
                    omVibrate(work->unk_18, 10, 0, 10);
                    work->unk_08 = 10;
                    work->unk_0A = 0;
                    work->unk_0C = 0;
                    if (team->unk_16 != -1) {
                        work->unk_22 = team->unk_16;
                        team->unk_16 = team->unk_18 = -1;
                        team->unk_1A = 0;
                    } else {
                        Hu3DModelAttrSet(object->model[work->unk_24 + 3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        work->unk_24 = work->unk_22 = -1;
                        work->unk_22 = m219_LogCreate(dir, 0);
                        m219_LogPosSet(work->unk_22, m219_stumpPosTbl[team->unk_10].x,
                                              m219_stumpPosTbl[team->unk_10].y, m219_stumpPosTbl[team->unk_10].z);
                        m219_LogRotSet(work->unk_22, 0.0f, 0.0f, 0.0f);
                    }
                    if (work->unk_22 != -1) {
                        m219_LogSplit(work->unk_22);
                        work->unk_22 = work->unk_24 = -1;
                    }
                    if (MgFlowStatGet() == MG_STATE_PLAY) {
                        team->unk_12++;
                    }
                }
            }
            break;
        case 9:
            if (model->motIdShift == 0xFF && model->motTime >= 8.0f && model->motId == object->motion[5]) {
                HuAudPlayerFXPlay(0x38C, work->unk_18);
                work->unk_08 = 11;
                work->unk_0A = 0;
                work->unk_0C = 0;
                if (team->unk_16 != -1) {
                    work->unk_22 = 0x20;
                    work->unk_24 = team->unk_18;
                    Hu3DModelAttrSet(object->model[work->unk_24 + 3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    m219_LogKill(team->unk_16);
                    team->unk_16 = team->unk_18 = -1;
                    team->unk_1A = 0;
                    MgPlayerEffSet(object, 6, m219_stumpPosTbl[team->unk_10].x,
                                           m219_stumpPosTbl[team->unk_10].y + 50.0,
                                           m219_stumpPosTbl[team->unk_10].z, 0.0f, 0.0f);
                } else {
                    MgPlayerEffSet(object, 6, m219_stumpPosTbl[team->unk_10].x,
                                           m219_stumpPosTbl[team->unk_10].y, m219_stumpPosTbl[team->unk_10].z, 0.0f,
                                           0.0f);
                }
                omVibrate(work->unk_18, 2, 2, 20);
                m219_MotStop(object);
            }
            break;
        case 10:
            if (work->unk_0C >= 9.0f) {
                work->unk_08 = 5;
                work->unk_0A = 0;
                work->unk_0C = 0;
                m219_MotShiftSet(object, 3, 5);
            }
            break;
        case 11:
            if (work->unk_0C >= 15.0f) {
                work->unk_08 = 6;
                work->unk_0A = 0;
                work->unk_0C = 0;
                m219_MotShiftTimeSet(object, 3, 12);
            }
            break;
        case 12:
            if (work->unk_0C >= 90.0f) {
                m219_MotShiftSet(object, 3, 7);
                work->unk_08 = 5;
                work->unk_0A = 0;
                work->unk_0C = 0;
            }
            break;
        case 13:
            m219_NodeWorldMtxCalc(object, "item_hook", mtx);
            team->unk_1C = object->model[2];
            if (team->unk_1C != -1) {
                HuMtxIdentF(Hu3DData[team->unk_1C].mtx);
                mtxTransCat(Hu3DData[team->unk_1C].mtx, 0.0f, -50.0f, 0.0f);
                Hu3DModelAttrSet(team->unk_1C, 0x4000, 0);
                team->unk_20 = 0;
                team->unk_24 = mtx[3][0];
                team->unk_2C = mtx[3][2];
                team->unk_28 = mtx[3][1] + 50.0;
                team->unk_3C = 30.000002f;
                team->unk_40 = (u8)(rand8() % 10) + 40;
                team->unk_44 = 3 - (u8)(rand8() % 6);
            }
            if (work->unk_24 != -1) {
                Hu3DModelAttrSet(object->model[work->unk_24 + 3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                m219_SmokeCreate((Vec *)mtx[3], NULL, &scale, 1.0f, m219_whiteColor.rgba);
                work->unk_22 = work->unk_24 = -1;
            }
            m219_MotShiftSet(object, 0, 5);
            work->unk_08 = 14;
            // fallthrough
        case 14:
            object->rot.y = m219_AngleStepCalc(0.0f, object->rot.y, 10.0f);
            object->trans.x = m219_StepCalc(m219_playerPosTbl[work->unk_00].x, object->trans.x, 10.0f);
            object->trans.z = m219_StepCalc(m219_playerPosTbl[work->unk_00].z, object->trans.z, 10.0f);
            if (MgFlowStatGet() == MG_STATE_RESULT) {
                m219_MotShiftSet(object, 1, 5);
                work->unk_10 = 25.0f;
                work->unk_0E = m219_JumpTimeCalc(25.0f, 1.6333001f);
                work->unk_08 = 15;
                work->unk_0C = 0;
            }
            break;
        case 15:
            t = (f32)work->unk_0C / work->unk_0E;
            if (t > 1.0f) {
                t = 1.0f;
            } else if (t < 0.0f) {
                t = 0.0f;
            }
            if (work->unk_0C == 6) {
                m219_MotShiftSet(object, 2, 6);
            } else if (work->unk_0C == work->unk_0E - 6) {
                m219_MotShiftSet(object, 1, 6);
            }
            object->trans.x =
                m219_InterpCalc(t, m219_playerPosTbl[work->unk_00].x, m219_playerWinPosTbl[work->unk_00].x);
            object->trans.z =
                m219_InterpCalc(t, m219_playerPosTbl[work->unk_00].z, m219_playerWinPosTbl[work->unk_00].z);
            object->trans.y += work->unk_10;
            work->unk_10 -= 1.6333001f;
            if (object->trans.y <= 0.0f) {
                m219_MotShiftSet(object, 0, 5);
                object->trans.y = 0.0f;
                work->unk_08 = 16;
                work->unk_0C = 0;
            }
            break;
        case 16:
            work->unk_08 = 17;
            work->unk_0C = 0;
            break;
        case 17:
            if (work->unk_06 != -1) {
                switch (work->unk_06) {
                    case 0:
                        m219_MotShiftSet(object, 9, 5);
                        CharAnimCreate(object->model[0], 2, work->unk_1C, m219_winAnimTbl[work->unk_1C]);
                        HuAudCharVoicePlayPlayer(work->unk_14, -1, work->unk_18);
                        break;
                    case 1:
                        m219_MotShiftSet(object, 10, 5);
                        CharAnimCreate(object->model[0], 2, work->unk_1C, m219_loseAnimTbl[work->unk_1C]);
                        break;
                }
                work->unk_06 = -1;
            }
            break;
    }
}

void m219_SetterComInput(omObjData *object, LogJamTeam *team) {
    LogJamPlayerWork *work = (LogJamPlayerWork *)m219_WorkPtrGet(object);
    LogJamPlayerWork *partner = team->unk_0C;

    HuPadBtnDown[work->unk_1A] = 0;
    switch (work->unk_08) {
        case 1:
        case 3:
        case 4:
            work->unk_2C = 0;
            break;
        case 2:
            if (work->unk_2C != 0) {
                HuPadBtnDown[work->unk_1A] |= work->unk_2C;
            } else if (work->unk_28 > work->unk_2A) {
                if ((u8)(rand8() % 100) < work->unk_20 * 13 + 50 || work->unk_2E >= work->unk_30 ||
                    partner->unk_1E == 0) {
                    switch (work->unk_24) {
                        case 0:
                            work->unk_2C |= 0x8000;
                            break;
                        case 1:
                            work->unk_2C |= 0x4000;
                            break;
                        default:
                            work->unk_2C |= 0x2000;
                            break;
                    }
                    work->unk_2E = 0;
                } else {
                    switch (work->unk_24) {
                        case 0:
                            work->unk_2C |= 0x2000;
                            break;
                        case 1:
                            work->unk_2C |= 0x8000;
                            break;
                        default:
                            work->unk_2C |= 0x4000;
                            break;
                    }
                    work->unk_2E++;
                }
                work->unk_28 = 0;
                work->unk_2A = (u8)(rand8() % 3) + (6 - work->unk_20 * 2) * 2;
            }
            break;
    }
    work->unk_28++;
}

void m219_ChopperComInput(omObjData *object, LogJamTeam *team) {
    LogJamPlayerWork *work = (LogJamPlayerWork *)m219_WorkPtrGet(object);
    LogJamPlayerWork *partner = team->unk_08;
    s16 dir;

    HuPadBtnDown[work->unk_1A] = 0;
    if (team->unk_16 != -1) {
        dir = team->unk_18;
    } else {
        dir = work->unk_24;
    }
    switch (work->unk_08) {
        case 7:
            if (work->unk_2C & 0xE000) {
                HuPadBtnDown[work->unk_1A] |= work->unk_2C;
            } else if (work->unk_28 > work->unk_2A && dir != -1) {
                if ((u8)(rand8() % 100) < work->unk_20 * 13 + 50 || work->unk_2E >= work->unk_30 ||
                    partner->unk_1E == 0) {
                    switch (dir) {
                        case 0:
                            work->unk_2C |= 0x8000;
                            break;
                        case 1:
                            work->unk_2C |= 0x4000;
                            break;
                        default:
                            work->unk_2C |= 0x2000;
                            break;
                    }
                    work->unk_2E = 0;
                } else {
                    switch (dir) {
                        case 0:
                            work->unk_2C |= 0x2000;
                            break;
                        case 1:
                            work->unk_2C |= 0x8000;
                            break;
                        default:
                            work->unk_2C |= 0x4000;
                            break;
                    }
                    work->unk_2E++;
                }
                work->unk_28 = 0;
                work->unk_2A = (u8)(rand8() % 10) + 16 - work->unk_20 * 2;
            }
            break;
        case 8:
        case 9:
            work->unk_2C = 0;
            break;
    }
    work->unk_28++;
}

s16 m219_PlayerAllStateCheck(s16 arg0) {
    s32 i = 0;
    LogJamPlayerWork *work = m219_playerWorkTbl;

    do {
        if (work->unk_08 != arg0) {
            return 0;
        }
        work++;
    } while (++i < 4);

    return 1;
}

s16 m219_JumpTimeCalc(f32 arg0, f32 arg1) {
    f32 total = 0.0f;
    s16 frames = 0;
    f32 speed = arg0;

    do {
        total += speed;
        speed -= arg1;
        frames++;
    } while (0.0f < total);

    return frames;
}

void m219_LogInit(void) {
    s32 i;
    LogJamLogWork *work;

    m219_logTbl = HuMemAllocTag(0xF00, TAG_OVERLAY);
    work = m219_logTbl;
    for (i = 0; i < 0x20; i++) {
        work->unk_00 = i;
        work->unk_02[0] = -1;
        work->unk_02[1] = -1;
        work->unk_02[2] = -1;
        work->unk_08 = 0;
        work->unk_0A = 0;
        work->unk_0C = 0;
        work->unk_0E = 0;
        work->unk_10 = work->unk_14 = work->unk_18 = 0.0f;
        work->unk_1C = work->unk_20 = work->unk_24 = 0.0f;
        work->unk_28 = work->unk_2C = work->unk_30 = 0.0f;
        memset(&work->unk_34, 0, 0x20);
        memset(&work->unk_54, 0, 0x20);
        work->unk_74 = NULL;
        work++;
    }
    m219_logObj = omAddObj(0x18, 0, 0, -1, m219_LogObjMain);
    omSetStatBit(m219_logObj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void m219_LogObjMain(omObjData *object) {
    LogJamLogWork *work;
    s32 i;
    s32 j;

    for (i = 0, work = m219_logTbl; i < 0x20; i++, work++) {
        if (work->unk_08 == 0) {
            continue;
        }
        switch (work->unk_0C) {
            case 0:
                break;
            case 1:
                if ((work->unk_0E & 1) || omPauseChk() + omAllPauseF != 0) {
                    for (j = 0; j < 3; j++) {
                        if (work->unk_02[j] != -1) {
                            Hu3DModelAttrSet(work->unk_02[j], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        }
                    }
                } else {
                    for (j = 0; j < 3; j++) {
                        if (work->unk_02[j] != -1) {
                            Hu3DModelAttrSet(work->unk_02[j], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        }
                    }
                }
                if (work->unk_0E >= 30.0f) {
                    work->unk_0E = 0;
                    work->unk_0C++;
                }
                break;
            default:
                m219_LogKill(work->unk_00);
                continue;
        }
        if (work->unk_74 != NULL && omPauseChk() + omAllPauseF == 0) {
            work->unk_74(work);
        }
        if (work->unk_08 == 0) {
            continue;
        }
        if (work->unk_02[0] != -1) {
            Hu3DModelPosSet(work->unk_02[0], work->unk_10, work->unk_14, work->unk_18);
            Hu3DModelRotSet(work->unk_02[0], work->unk_1C, work->unk_20, work->unk_24);
        }
        if (omPauseChk() + omAllPauseF == 0) {
            work->unk_0E++;
        }
    }
}

s16 m219_LogCreate(s16 arg0, s16 arg1) {
    s32 i;
    LogJamLogWork *work;

    if (m219_logTbl == NULL) {
        return -1;
    }
    for (i = 0, work = m219_logTbl; i < 0x20; i++, work++) {
        if (work->unk_08 == 0) {
            work->unk_02[0] = m219_LogMdlLink(arg0, arg1);
            if (work->unk_02[0] != -1) {
                Hu3DModelAttrSet(work->unk_02[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            work->unk_08 = 1;
            work->unk_0A = arg0;
            work->unk_0C = 0;
            work->unk_0E = 0;
            return i;
        }
    }
    return -1;
}

LogJamLogWork *m219_LogGet(s16 arg0) {
    if (m219_logTbl == NULL) {
        return NULL;
    }

    return &m219_logTbl[arg0];
}

void m219_LogPosSet(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (m219_logTbl != NULL) {
        LogJamLogWork *work = &m219_logTbl[arg0];

        if (work->unk_08 != 0) {
            work->unk_10 = arg1;
            work->unk_14 = arg2;
            work->unk_18 = arg3;
        }
    }
}

void m219_LogRotSet(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (m219_logTbl != NULL) {
        LogJamLogWork *work = &m219_logTbl[arg0];

        if (work->unk_08 != 0) {
            work->unk_1C = arg1;
            work->unk_20 = arg2;
            work->unk_24 = arg1;
        }
    }
}

void m219_LogClose(void) {
    s32 i;
    LogJamLogWork *work;

    if (m219_logTbl != NULL) {
        for (i = 0, work = m219_logTbl; i < 0x20; i++, work++) {
            if (work->unk_08 != 0) {
                m219_LogKill(i);
            }
        }
        HuMemFree(m219_logTbl);
        m219_logTbl = NULL;
        m219_logObj->func = NULL;
    }
}

void m219_LogKill(s16 arg0) {
    s32 i;
    LogJamLogWork *work;

    if (m219_logTbl != NULL) {
        work = &m219_logTbl[arg0];
        if (work->unk_08 != 0) {
            for (i = 0; i < 3; i++) {
                if (work->unk_02[i] != -1) {
                    Hu3DModelKill(work->unk_02[i]);
                    work->unk_02[i] = -1;
                }
            }
            work->unk_08 = 0;
            work->unk_0A = work->unk_0C = work->unk_0E = 0;
            work->unk_10 = work->unk_14 = work->unk_18 = 0.0f;
            work->unk_1C = work->unk_20 = work->unk_24 = 0.0f;
            work->unk_28 = work->unk_2C = work->unk_30 = 0.0f;
            memset(&work->unk_34, 0, 0x20);
            memset(&work->unk_54, 0, 0x20);
            work->unk_74 = NULL;
        }
    }
}

void m219_LogSplit(s16 arg0) {
    Vec pos = { 0.0f, 0.0f, 0.0f };
    Vec scale = { 0.5f, 0.5f, 0.5f };
    LogJamLogWork *work;
    f32 x;
    f32 y;
    f32 z;
    s32 type;
    s32 i;
    s16 id;

    if (m219_logTbl == NULL) {
        return;
    }
    work = &m219_logTbl[arg0];
    if (work->unk_08 == 0) {
        return;
    }
    type = work->unk_0A;
    x = work->unk_10;
    y = work->unk_14;
    z = work->unk_18;
    pos.x = work->unk_10;
    pos.y = work->unk_14;
    pos.z = work->unk_18;
    m219_SmokeCreate(&pos, NULL, &scale, 1.0f, m219_chipColor.rgba);
    m219_LogKill(arg0);
    for (i = 0; i < 2; i++) {
        id = m219_LogCreate(type, i + 1);
        if (id != -1) {
            work = &m219_logTbl[id];
            work->unk_10 = x;
            work->unk_14 = y;
            work->unk_18 = z;
            work->unk_34[0] = i;
            work->unk_52 = 0;
            work->unk_74 = m219_LogHalfMove;
            work->unk_74(work);
        }
    }
}

void m219_LogHalfMove(LogJamLogWork *work) {
    Vec pos = { 0.0f, 0.0f, 0.0f };
    Vec scale = { 0.5f, 0.5f, 0.5f };
    f32 amplitude;

    switch (work->unk_52) {
        case 0:
            if (work->unk_34[0] == 0) {
                work->unk_28 = ((f32)(u8)(rand8() % 100) * 0.01 * 0.02 + 0.03f) * 100.0;
                work->unk_54[0] = -((f32)(u8)(rand8() % 100) * 0.01 * 0.75 + 4.0);
                work->unk_54[5] = -90.0f;
            } else {
                work->unk_28 = -(((f32)(u8)(rand8() % 100) * 0.01 * 0.02 + 0.03f) * 100.0);
                work->unk_54[0] = (f32)(u8)(rand8() % 100) * 0.01 * 0.75 + 4.0;
                work->unk_54[5] = 90.0f;
            }
            work->unk_2C = (f32)(u8)(rand8() % 100) * 0.01 * 2.0 + 10.999999940395355;
            work->unk_30 = (f32)(u8)(rand8() % 100) * 0.01 * 1.2500000186264515 + 0.6250000093132257;
            work->unk_52++;
            break;
        case 1:
            work->unk_24 += work->unk_54[0];
            work->unk_2C -= 1.6333001f;
            if (work->unk_14 <= 0.0f) {
                work->unk_14 = 0.0f;
                work->unk_28 = work->unk_2C = work->unk_30 = 0.0f;
                work->unk_54[1] = 20.0f;
                work->unk_54[2] = 1.0f;
                work->unk_54[3] = 0.0f;
                work->unk_54[4] = 55.0f;
                work->unk_52++;
                pos.x = work->unk_10;
                pos.y = work->unk_14;
                pos.z = work->unk_18;
                m219_SmokeCreate(&pos, NULL, &scale, 1.0f, m219_chipColor.rgba);
            }
            break;
        case 2:
            work->unk_54[3] += work->unk_54[4];
            if (work->unk_54[3] >= 360.0f) {
                work->unk_54[3] -= 360.0f;
            }
            amplitude = work->unk_54[1] - work->unk_54[2];
            if (amplitude > 0.0f) {
                work->unk_54[1] = amplitude;
            } else {
                work->unk_54[1] = 0.0f;
            }
            work->unk_24 = sindf(work->unk_54[3]) * work->unk_54[1] + work->unk_54[5];
            if (work->unk_0C == 0) {
                work->unk_0C = 1;
            }
            break;
    }
    work->unk_10 += work->unk_28;
    work->unk_14 += work->unk_2C;
    work->unk_18 += work->unk_30;
}

void m219_LogMdlInit(void) {
    s32 i;

    m219_logMdlTbl = HuMemAllocTag(0x12, TAG_OVERLAY);

    for (i = 0; i < 9; i++) {
        m219_logMdlTbl[i] = Hu3DModelRead(m219_logMdlFileTbl[i], 0xBD);
    }
}

s16 m219_LogMdlLink(s16 arg0, s16 arg1) {
    if (m219_logMdlTbl == NULL) {
        return -1;
    }

    return Hu3DModelLink(m219_logMdlTbl[arg0 * 3 + arg1]);
}

void m219_LogMdlClose(void) {
    s32 i;

    for (i = 0; i < 9; i++) {
        Hu3DModelKill(m219_logMdlTbl[i]);
    }
    HuMemFree(m219_logMdlTbl);
    m219_logMdlTbl = NULL;
}

// Appends a new object to the shared minigame object list.
void m219_StageObjCreate(void) {
    omObjData *obj = omAddObj(1, 0x10, 0, -1, m219_StageObjInit);
    u16 index = mgMapObjNum;

    mgMapObjNum = index + 1;
    mgMapObjTbl[index] = obj;
}

void m219_StageObjInit(omObjData *object) {
    s16 model;
    s16 group;
    LogJamCloud *cloud;
    s16 i;
    s16 j;

    model = object->model[1] = Hu3DModelRead(0x340001, 0xA9);
    Hu3DModelPosSet(model, -100.0f, 0.0f, 115.0f);
    Hu3DModelPosSet(object->model[2] = Hu3DModelLink(model), 100.0f, 0.0f, 115.0f);
    model = object->model[3] = Hu3DModelRead(0x340002, 0x89);
    Hu3DModelPosSet(model, -230.0f, 0.0f, 195.0f);
    Hu3DModelPosSet(object->model[4] = Hu3DModelLink(model), 230.0f, 0.0f, 195.0f);

    m219_sprTbl[0] = m219_SprAnimRead(0x34000C);
    group = HuSprGrpCreate(3, 0);
    HuSprGrpMemberSet(group, 0, m219_sprTbl[0], 0);
    HuSprPosSet(group, 0, 160, 120);
    HuSprAnimModeSet(group, 0, HUSPR_ANIM_MODE_STOP);
    HuSprPatNoSet(group, 0, 0);
    HuSprAttrSet(group, 0, 0x4000580C);
    HuSprPriSet(group, 0, 0xFF00);
    m219_sprTbl[4] = m219_SprAnimRead(0x340010);
    HuSprGrpMemberSet(group, 1, m219_sprTbl[4], 0);
    HuSprPosSet(group, 1, 0, 40);
    HuSprAnimModeSet(group, 1, HUSPR_ANIM_MODE_STOP);
    HuSprPatNoSet(group, 1, 0);
    HuSprAttrSet(group, 1, 0x4000580C);
    HuSprPriSet(group, 1, 0xFF01);
    HuSprTPLvlSet(group, 1, 200);
    m219_sprTbl[1] = m219_SprAnimRead(0x34000D);
    HuSprGrpMemberSet(group, 2, m219_sprTbl[1], 0);
    HuSprPosSet(group, 2, 0, 0);
    HuSprAnimModeSet(group, 2, HUSPR_ANIM_MODE_STOP);
    HuSprPatNoSet(group, 2, 0);
    HuSprAttrSet(group, 2, 0x403C);
    HuSprPriSet(group, 2, 0xFFFF);

    m219_sprTbl[2] = m219_SprAnimRead(0x34000E);
    m219_sprTbl[5] = m219_SprAnimRead(0x340011);
    m219_cloudTbl = HuMemAllocTag(sizeof(LogJamCloud) * 5, TAG_OVERLAY);
    cloud = m219_cloudTbl;
    for (i = 0; i < 5; i++, cloud++) {
        cloud->index = i;
        cloud->group = HuSprGrpCreate(2, 0);
        cloud->angle = rand8() % 360;
        cloud->base = m219_cloudScaleTbl[i];
        cloud->pos.x = m219_cloudPosTbl[i].x;
        cloud->pos.y = m219_cloudPosTbl[i].y;
        cloud->scale.x = cloud->scale.y = 1.0f;
        cloud->speed = -0.5f;
        cloud->unk_20 = 0;
        for (j = 0; j < 2; j++) {
            if (j == 0) {
                HuSprGrpMemberSet(cloud->group, 0, m219_sprTbl[2], 0);
            } else {
                HuSprGrpMemberSet(cloud->group, j, m219_sprTbl[5], 0);
                HuSprTPLvlSet(cloud->group, j, 190);
            }
            HuSprAnimModeSet(cloud->group, j, HUSPR_ANIM_MODE_STOP);
            HuSprPatNoSet(cloud->group, j, 0);
            HuSprAttrSet(cloud->group, j, 0x2000583C);
            HuSprPosSet(cloud->group, j, cloud->pos.x, cloud->pos.y);
            HuSprScaleSet(cloud->group, j, cloud->scale.x, cloud->scale.y);
            HuSprPriSet(cloud->group, j, j + i * 2 - 241);
        }
    }
    object->func = m219_StageObjMain;
}

void m219_StageObjMain(omObjData *object) {
    LogJamCloud *cloud;
    HuSprite *sprite;
    f32 wobble;
    s16 i;

    for (i = 0, cloud = m219_cloudTbl; i < 5; i++, cloud++) {
        wobble = sindf(cloud->angle);
        cloud->pos.x += cloud->speed * ((f32)(u8)(rand8() % 100) * 0.01 * 0.4f + 0.6f);
        cloud->scale.x = cloud->base + 0.075f + wobble * 0.075f;
        cloud->scale.y = cloud->base + 0.075f - wobble * 0.075f;
        if (cloud->pos.x <= -64.0f) {
            cloud->pos.x += 416.0f;
        } else if (cloud->pos.x > 384.0f) {
            cloud->pos.x -= 320.0f;
        }
        HuSprScaleSet(cloud->group, 0, cloud->scale.x, cloud->scale.y);
        HuSprScaleSet(cloud->group, 1, cloud->scale.x, cloud->scale.y);
        sprite = HuSprGet(cloud->group, 0);
        sprite->pos.x = cloud->pos.x;
        sprite->pos.y = cloud->pos.y;
        sprite = HuSprGet(cloud->group, 1);
        sprite->pos.x = cloud->pos.x;
        sprite->pos.y = cloud->pos.y;
        cloud->angle += (u8)(rand8() % 7) + 2;
        if (cloud->angle >= 360) {
            cloud->angle -= 360;
        }
    }
}

u16 m219_SprAnimRead(s32 file) {
    void *data = DataRead(file);
    u16 sprite = HuSprAnimRead(data);

    DataClose(data);
    return sprite;
}

void m219_ScoreInit(void) {
    LogJamScore *sprites;
    s32 i;
    s32 j;
    s32 x;

    m219_sprTbl[3] = m219_SprAnimRead(0x34000F);
    m219_scoreTbl = HuMemAllocTag(sizeof(LogJamScore) * 2, TAG_OVERLAY);
    sprites = m219_scoreTbl;
    for (i = 0; i < 2; i++, sprites++) {
        x = m219_scoreXTbl[i];
        memset(sprites, 0, sizeof(LogJamScore));
        sprites->unk_00 = i;
        sprites->unk_02 = HuSprGrpCreate(10, 0);
        for (j = 0; j < 10; j++) {
            HuSprGrpMemberSet(sprites->unk_02, j, m219_sprTbl[3], 0);
            HuSprAnimModeSet(sprites->unk_02, j, HUSPR_ANIM_MODE_STOP);
            HuSprPatNoSet(sprites->unk_02, j, 0);
            HuSprTPLvlSet(sprites->unk_02, j, 0x100);
            HuSprAttrSet(sprites->unk_02, j, 0x9000);
            HuSprPosSet(sprites->unk_02, j, x, 28);
            if (i == 0) {
                x += 16;
            } else {
                x -= 16;
            }
        }
    }
    omAddObj(30, 0, 0, -1, m219_ScoreObjMain);
}

void m219_ScoreObjMain(omObjData *object) {
    LogJamScore *sprites;
    s32 i;
    s32 j;
    s32 fives;
    s32 count;
    f32 t;

    for (i = 0, sprites = m219_scoreTbl; i < 2; i++, sprites++) {
        fives = (s16)(sprites->unk_08 / 5);
        count = fives + (s16)(sprites->unk_08 % 5);
        if (sprites->unk_0A != sprites->unk_08) {
            for (j = 0; j < 10; j++) {
                HuSprTPLvlSet(sprites->unk_02, j, 0x100);
                HuSprScaleSet(sprites->unk_02, j, 1.0f, 1.0f);
            }
            sprites->unk_04 = 15;
            if (count != 0) {
                sprites->unk_06 = count - 1;
            }
        }
        if (sprites->unk_04 > 0) {
            if (sprites->unk_04 == 1) {
                t = 0.0f;
            } else {
                t = sprites->unk_04 / 15.0f;
            }
            HuSprTPLvlSet(sprites->unk_02, sprites->unk_06, (s32)((1.0f - t) * 256.0f));
            HuSprScaleSet(sprites->unk_02, sprites->unk_06, t + 1.0f, t + 1.0f);
            sprites->unk_04--;
        }
        for (j = 0; j < 10; j++) {
            if (j < fives) {
                HuSprPatNoSet(sprites->unk_02, j, 1);
            } else {
                HuSprPatNoSet(sprites->unk_02, j, 0);
            }
            if (j < count) {
                HuSprAttrReset(sprites->unk_02, j, HUSPR_ATTR_DISPOFF);
            } else {
                HuSprAttrSet(sprites->unk_02, j, HUSPR_ATTR_DISPOFF);
            }
        }
        sprites->unk_0A = sprites->unk_08;
    }
}

void m219_ScoreSet(s16 arg0, s16 arg1) {
    LogJamScore *sprites = &m219_scoreTbl[arg0];

    sprites->unk_08 = arg1;
}

void m219_SmokeInit(void) {
    HuSprAnimData *sprite;
    LogJamEffect *effect;
    HmfModel *model;
    s32 i;

    m219_sprTbl[6] = m219_SprAnimRead(11);
    sprite = HuSprAnimDataGet(m219_sprTbl[6]);
    m219_smokeObj = omAddObj(30, 0, 0, -1, m219_SmokeObjMain);
    m219_smokeTbl = effect = HuMemAllocTag(sizeof(LogJamEffect) * 8, TAG_OVERLAY);
    for (i = 0; i < 8; i++, effect++) {
        if (i == 0) {
            effect->model = m219_BillboardColorMdlCreate(sprite, m219_chipColor.rgba);
        } else {
            effect->model = m219_BillboardColorMdlLink(sprite, m219_smokeTbl[0].model, m219_chipColor.rgba);
        }
        effect->active = 0;
        effect->color = m219_chipColor;
        effect->frame = effect->speed = 0.0f;
        effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        effect->scale.x = effect->scale.y = effect->scale.z = 0.0f;
        Hu3DModelAttrSet(effect->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        model = &Hu3DData[effect->model];
        model->motTime = 0.0f;
    }
}

void m219_SmokeObjMain(omObjData *object) {
    HuSprAnimData *sprite = HuSprAnimDataGet(m219_sprTbl[6]);
    LogJamEffect *effect;
    HmfModel *model;
    s32 i;

    for (i = 0, effect = m219_smokeTbl; i < 8; i++, effect++) {
        if (effect->active == 0) {
            continue;
        }
        model = &Hu3DData[effect->model];
        if (model->attr & 4) {
            continue;
        }
        effect->pos.x += effect->vel.x;
        effect->pos.y += effect->vel.y;
        effect->pos.z += effect->vel.z;
        model->pos.x = effect->pos.x;
        model->pos.y = effect->pos.y;
        model->pos.z = effect->pos.z;
        model->scale.x = effect->scale.x;
        model->scale.y = effect->scale.y;
        model->scale.z = effect->scale.z;
        m219_BillboardColorPatSet(effect->model, sprite, (s32)effect->frame, effect->color.rgba);
        effect->frame += effect->speed;
        if ((s32)effect->frame >= sprite->patNum) {
            effect->active = 0;
            effect->frame = 0.0f;
            model->attr |= 4;
        }
    }
}

s32 m219_SmokeCreate(Vec *pos, Vec *vel, Vec *scale, f32 speed, u8 *color) {
    HuSprAnimData *sprite = HuSprAnimDataGet(m219_sprTbl[6]);
    LogJamEffect *effect;
    HmfModel *model;
    s32 i;

    for (i = 0, effect = m219_smokeTbl; i < 8; i++, effect++) {
        if (effect->active != 0) {
            continue;
        }
        effect->active = 1;
        model = &Hu3DData[effect->model];
        if (pos != NULL) {
            effect->pos.x = pos->x;
            effect->pos.y = pos->y;
            effect->pos.z = pos->z;
        } else {
            effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        }
        if (vel != NULL) {
            effect->vel.x = vel->x;
            effect->vel.y = vel->y;
            effect->vel.z = vel->z;
        } else {
            effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        }
        if (scale != NULL) {
            effect->scale.x = scale->x;
            effect->scale.y = scale->y;
            effect->scale.z = scale->z;
        } else {
            effect->scale.x = effect->scale.y = effect->scale.z = 1.0f;
        }
        memcpy(effect->color.rgba, color, sizeof(LogJamColor));
        effect->speed = speed;
        effect->frame = 0.0f;
        m219_BillboardColorPatSet(effect->model, sprite, 0, effect->color.rgba);
        Hu3DModelAttrSet(effect->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        model->motTime = 0.0f;
        model->pos.x = effect->pos.x;
        model->pos.y = effect->pos.y;
        model->pos.z = effect->pos.z;
        model->scale.x = effect->scale.x;
        model->scale.y = effect->scale.y;
        model->scale.z = effect->scale.z;
        return i;
    }
    return -1;
}

void m219_MissInit(void) {
    HuSprAnimData *sprite;
    LogJamEffect *effect;
    HmfModel *model;
    s32 i;

    m219_sprTbl[7] = m219_SprAnimRead(0x340012);
    sprite = HuSprAnimDataGet(m219_sprTbl[7]);
    m219_missObj = omAddObj(30, 0, 0, -1, m219_MissObjMain);
    m219_missTbl = effect = HuMemAllocTag(sizeof(LogJamEffect) * 8, TAG_OVERLAY);
    for (i = 0; i < 8; i++, effect++) {
        if (i == 0) {
            effect->model = m219_BillboardColorMdlCreate(sprite, m219_chipColor.rgba);
        } else {
            effect->model = m219_BillboardColorMdlLink(sprite, m219_missTbl[0].model, m219_chipColor.rgba);
        }
        effect->active = 0;
        effect->color = m219_chipColor;
        effect->frame = effect->speed = 0.0f;
        effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        effect->scale.x = effect->scale.y = effect->scale.z = 0.0f;
        Hu3DModelAttrSet(effect->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        model = &Hu3DData[effect->model];
        model->motTime = 0.0f;
    }
}

void m219_MissObjMain(omObjData *object) {
    HuSprAnimData *sprite = HuSprAnimDataGet(m219_sprTbl[7]);
    LogJamEffect *effect;
    HmfModel *model;
    s32 i;

    for (i = 0, effect = m219_missTbl; i < 8; i++, effect++) {
        if (effect->active == 0) {
            continue;
        }
        model = &Hu3DData[effect->model];
        if (model->attr & 4) {
            continue;
        }
        effect->pos.x += effect->vel.x;
        effect->pos.y += effect->vel.y;
        effect->pos.z += effect->vel.z;
        model->pos.x = effect->pos.x;
        model->pos.y = effect->pos.y;
        model->pos.z = effect->pos.z;
        model->scale.x = effect->scale.x;
        model->scale.y = effect->scale.y;
        model->scale.z = effect->scale.z;
        m219_BillboardColorPatSet(effect->model, sprite, (s32)effect->frame, effect->color.rgba);
        effect->frame += effect->speed;
        if ((s32)effect->frame >= sprite->patNum) {
            effect->active = 0;
            effect->frame = 0.0f;
            model->attr |= 4;
        }
    }
}

s32 m219_MissCreate(Vec *pos, Vec *vel, Vec *scale, f32 speed, u8 *color) {
    HuSprAnimData *sprite = HuSprAnimDataGet(m219_sprTbl[7]);
    LogJamEffect *effect;
    HmfModel *model;
    s32 i;

    for (i = 0, effect = m219_missTbl; i < 8; i++, effect++) {
        if (effect->active != 0) {
            continue;
        }
        effect->active = 1;
        model = &Hu3DData[effect->model];
        if (pos != NULL) {
            effect->pos.x = pos->x;
            effect->pos.y = pos->y;
            effect->pos.z = pos->z;
        } else {
            effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        }
        if (vel != NULL) {
            effect->vel.x = vel->x;
            effect->vel.y = vel->y;
            effect->vel.z = vel->z;
        } else {
            effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        }
        if (scale != NULL) {
            effect->scale.x = scale->x;
            effect->scale.y = scale->y;
            effect->scale.z = scale->z;
        } else {
            effect->scale.x = effect->scale.y = effect->scale.z = 1.0f;
        }
        if (color != NULL) {
            memcpy(effect->color.rgba, color, sizeof(LogJamColor));
        } else {
            memset(effect->color.rgba, 0xFF, sizeof(LogJamColor));
        }
        effect->speed = speed;
        effect->frame = 0.0f;
        m219_BillboardColorPatSet(effect->model, sprite, 0, effect->color.rgba);
        Hu3DModelAttrSet(effect->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        model->motTime = 0.0f;
        model->pos.x = effect->pos.x;
        model->pos.y = effect->pos.y;
        model->pos.z = effect->pos.z;
        model->scale.x = effect->scale.x;
        model->scale.y = effect->scale.y;
        model->scale.z = effect->scale.z;
        return i;
    }
    return -1;
}

void m219_CameraInit(void) {
    HuCamera *camera;
    s32 i;

    Center.x = 0.0f;
    Center.y = 126.8f;
    Center.z = -0.8f;
    CRot.x = 350.505f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 1062.0f;
    m219_CameraKeyStore(0);
    m219_CameraKeyStore(1);
    m219_cameraMoveF = 0;
    m219_cameraMoveTime = 0;
    m219_cameraMoveTimer = 0;
    omAddObj(31, 0, 0, -1, m219_CameraMoveObjMain);
    camera = gCameraList;
    for (i = 1; i < Hu3DBufNum; i++) {
        camera->viewports[i].vp.vscale[0] = camera->viewports[0].vp.vscale[0];
        camera->viewports[i].vp.vscale[1] = camera->viewports[0].vp.vscale[1];
        camera->viewports[i].vp.vscale[2] = camera->viewports[0].vp.vscale[2];
        camera->viewports[i].vp.vtrans[0] = camera->viewports[0].vp.vtrans[0];
        camera->viewports[i].vp.vtrans[1] = camera->viewports[0].vp.vtrans[1];
        camera->viewports[i].vp.vtrans[2] = camera->viewports[0].vp.vtrans[2];
    }
}

void m219_CameraDebugPad(void) {
    MgCameraKey delta = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed;

    speed = 1.0f;
    switch (m219_cameraDebugMode) {
        case 1:
            if ((u16)HuPadBtn[0] & A_BUTTON) {
                speed = 8.0f;
            }
            if (HuPadBtn[0] & B_BUTTON) {
                speed = 0.5f;
            }
            if (HuPadBtnDown[0] & START_BUTTON) {
                Center.x = 0.0f;
                Center.y = 191.2f;
                Center.z = 0.2f;
                CRot.x = -14.5f;
                CRot.y = 0.0f;
                CRot.z = 0.0f;
                CZoom = 1069.0f;
            } else {
                delta.rot.x = (f32)HuPadStkY[0] * 0.125 * speed;
                delta.rot.y = (f32)HuPadStkX[0] * 0.125 * speed;
                if (HuPadBtn[0] & L_JPAD) {
                    delta.center.x = speed * 2.0;
                }
                if (HuPadBtn[0] & R_JPAD) {
                    delta.center.x = -(speed * 2.0);
                }
                if (HuPadBtn[0] & U_JPAD) {
                    delta.center.z = -(speed * 2.0);
                }
                if (HuPadBtn[0] & D_JPAD) {
                    delta.center.z = speed * 2.0;
                }
                if (HuPadBtn[0] & U_CBUTTONS) {
                    delta.center.y = speed * 2.0;
                }
                if (HuPadBtn[0] & D_CBUTTONS) {
                    delta.center.y = -(speed * 2.0);
                }
                if (HuPadBtn[0] & R_CBUTTONS) {
                    delta.zoom = speed * 2.0;
                }
                if (HuPadBtn[0] & L_CBUTTONS) {
                    delta.zoom = -(speed * 2.0);
                }
                delta.center.x += Center.x;
                delta.center.y += Center.y;
                delta.center.z += Center.z;
                delta.rot.x += CRot.x;
                delta.rot.y += CRot.y;
                delta.rot.z += CRot.z;
                delta.zoom += CZoom;
                m219_CameraMoveStart(delta.center.x, delta.center.y, delta.center.z, delta.rot.x,
                                      delta.rot.y, delta.rot.z, delta.zoom, 1);
            }
            sprintf(omDBGStrBuf, "CAMERA TEST_MODE");
            print8((s16)m219_cameraDebugX + 20, (s16)m219_cameraDebugY + 80,
                   omDBGStrBuf);
            sprintf(omDBGStrBuf, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((s16)m219_cameraDebugX + 20, (s16)m219_cameraDebugY + 88,
                   omDBGStrBuf);
            sprintf(omDBGStrBuf, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((s16)m219_cameraDebugX + 20, (s16)m219_cameraDebugY + 96,
                   omDBGStrBuf);
            sprintf(omDBGStrBuf, " ZOOM   %3.3f ", CZoom);
            print8((s16)m219_cameraDebugX + 20, (s16)m219_cameraDebugY + 104,
                   omDBGStrBuf);
            break;
        case 2:
            if ((HuPadBtn[0] & R_JPAD) || (HuPadBtn[0] & R_CBUTTONS)) {
                m219_cameraDebugX++;
            }
            if (HuPadBtn[0] & (L_JPAD | L_CBUTTONS)) {
                m219_cameraDebugX--;
            }
            if (HuPadBtn[0] & (D_JPAD | D_CBUTTONS)) {
                m219_cameraDebugY++;
            }
            if (HuPadBtn[0] & (U_JPAD | U_CBUTTONS)) {
                m219_cameraDebugY--;
            }
            fontcolor = 8;
            sprintf(omDBGStrBuf, "CAMERA TEST_MODE ");
            print8((s16)m219_cameraDebugX + 20, (s16)m219_cameraDebugY + 80,
                   omDBGStrBuf);
            sprintf(omDBGStrBuf, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((s16)m219_cameraDebugX + 20, (s16)m219_cameraDebugY + 88,
                   omDBGStrBuf);
            sprintf(omDBGStrBuf, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((s16)m219_cameraDebugX + 20, (s16)m219_cameraDebugY + 96,
                   omDBGStrBuf);
            sprintf(omDBGStrBuf, " ZOOM   %3.3f ", CZoom);
            print8((s16)m219_cameraDebugX + 20, (s16)m219_cameraDebugY + 104,
                   omDBGStrBuf);
            break;
        case 3:
            m219_cameraDebugMode = 0;
            break;
    }
    if (HuPadBtnDown[0] & R_TRIG) {
        if (m219_cameraDebugMode == 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (m219_cameraDebugMode++ >= 4) {
            m219_cameraDebugMode = 0;
        }
    }
}

void m219_CameraMoveObjMain(omObjData *object) {
    f32 t;

    if (m219_cameraMoveTime <= 0) {
        m219_CameraPosUpdate(0);
        m219_cameraMoveF = 0;
        return;
    }
    if (m219_cameraMoveTimer == 0) {
        Center.x = m219_cameraKeyTbl[0].center.x;
        Center.y = m219_cameraKeyTbl[0].center.y;
        Center.z = m219_cameraKeyTbl[0].center.z;
        CRot.x = m219_cameraKeyTbl[0].rot.x;
        CRot.y = m219_cameraKeyTbl[0].rot.y;
        CRot.z = m219_cameraKeyTbl[0].rot.z;
        CZoom = m219_cameraKeyTbl[0].zoom;
        if (CRot.x >= 360.0) {
            CRot.x -= 360.0;
        } else if (CRot.x < 0.0) {
            CRot.x += 360.0;
        }
        if (CRot.y >= 360.0) {
            CRot.y -= 360.0;
        } else if (CRot.y < 0.0) {
            CRot.y += 360.0;
        }
        if (CRot.z >= 360.0) {
            CRot.z -= 360.0;
        } else if (CRot.z < 0.0) {
            CRot.z += 360.0;
        }
        m219_cameraMoveTime = 0;
    } else {
        t = (f32)m219_cameraMoveTimer / (f32)m219_cameraMoveTime;
        Center.x = m219_InterpCalc(t, m219_cameraKeyTbl[0].center.x,
                                         m219_cameraKeyTbl[1].center.x);
        Center.y = m219_InterpCalc(t, m219_cameraKeyTbl[0].center.y,
                                         m219_cameraKeyTbl[1].center.y);
        Center.z = m219_InterpCalc(t, m219_cameraKeyTbl[0].center.z,
                                         m219_cameraKeyTbl[1].center.z);
        CRot.x = m219_AngleInterpCalc(t, m219_cameraKeyTbl[0].rot.x,
                                       m219_cameraKeyTbl[1].rot.x);
        CRot.y = m219_AngleInterpCalc(t, m219_cameraKeyTbl[0].rot.y,
                                       m219_cameraKeyTbl[1].rot.y);
        CRot.z = m219_AngleInterpCalc(t, m219_cameraKeyTbl[0].rot.z,
                                       m219_cameraKeyTbl[1].rot.z);
        CZoom = m219_InterpCalc(t, m219_cameraKeyTbl[0].zoom,
                                      m219_cameraKeyTbl[1].zoom);
        if (CRot.x >= 360.0) {
            CRot.x -= 360.0;
        } else if (CRot.x < 0.0) {
            CRot.x += 360.0;
        }
        if (CRot.y >= 360.0) {
            CRot.y -= 360.0;
        } else if (CRot.y < 0.0) {
            CRot.y += 360.0;
        }
        if (CRot.z >= 360.0) {
            CRot.z -= 360.0;
        } else if (CRot.z < 0.0) {
            CRot.z += 360.0;
        }
        if (m219_cameraMoveTimer > 0) {
            m219_cameraMoveTimer--;
        } else {
            m219_cameraMoveTimer++;
        }
    }
    m219_cameraMoveF = 1;
    m219_CameraPosUpdate(0);
}

void m219_CameraKeyStore(s32 arg0) {
    if (CRot.x >= 360.0) {
        CRot.x -= 360.0;
    } else if (CRot.x < 0.0) {
        CRot.x += 360.0;
    }
    if (CRot.y >= 360.0) {
        CRot.y -= 360.0;
    } else if (CRot.y < 0.0) {
        CRot.y += 360.0;
    }
    if (CRot.z >= 360.0) {
        CRot.z -= 360.0;
    } else if (CRot.z < 0.0) {
        CRot.z += 360.0;
    }
    m219_cameraKeyTbl[arg0].center.x = Center.x;
    m219_cameraKeyTbl[arg0].center.y = Center.y;
    m219_cameraKeyTbl[arg0].center.z = Center.z;
    m219_cameraKeyTbl[arg0].rot.x = CRot.x;
    m219_cameraKeyTbl[arg0].rot.y = CRot.y;
    m219_cameraKeyTbl[arg0].rot.z = CRot.z;
    m219_cameraKeyTbl[arg0].zoom = CZoom;
    m219_cameraKeyTbl[arg0].unk_1C = m219_cameraKeyTbl[arg0].unk_20 = 0.0f;
}

// Passing CAMERA_KEEP for a component keeps its current value.
void m219_CameraMoveStart(f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames) {
    if (frames > 0) {
        m219_cameraMoveTimer = frames - 1;
        m219_cameraMoveTime = frames;
        if (x != CAMERA_KEEP) {
            m219_cameraKeyTbl[0].center.x = x;
        } else {
            m219_cameraKeyTbl[0].center.x = Center.x;
        }
        if (y != CAMERA_KEEP) {
            m219_cameraKeyTbl[0].center.y = y;
        } else {
            m219_cameraKeyTbl[0].center.y = Center.y;
        }
        if (z != CAMERA_KEEP) {
            m219_cameraKeyTbl[0].center.z = z;
        } else {
            m219_cameraKeyTbl[0].center.z = Center.z;
        }
        if (rotX != CAMERA_KEEP) {
            m219_cameraKeyTbl[0].rot.x = rotX;
        } else {
            m219_cameraKeyTbl[0].rot.x = CRot.x;
        }
        if (rotY != CAMERA_KEEP) {
            m219_cameraKeyTbl[0].rot.y = rotY;
        } else {
            m219_cameraKeyTbl[0].rot.y = CRot.y;
        }
        if (rotZ != CAMERA_KEEP) {
            m219_cameraKeyTbl[0].rot.z = rotZ;
        } else {
            m219_cameraKeyTbl[0].rot.z = CRot.z;
        }
        if (zoom != CAMERA_KEEP) {
            m219_cameraKeyTbl[0].zoom = zoom;
        } else {
            m219_cameraKeyTbl[0].zoom = CZoom;
        }
        m219_CameraKeyStore(1);
    }
}

void m219_CameraPosUpdate(s32 camIndex) {
    HuCamera *camera = &gCameraList[camIndex];
    f32 rotX = CRot.x;
    f32 rotY = CRot.y;

    camera->pos.x = Center.x + sindf(rotY) * cosdf(rotX) * CZoom;
    camera->pos.y = -sindf(rotX) * CZoom + Center.y;
    camera->pos.z = cosdf(rotY) * cosdf(rotX) * CZoom + Center.z;
    camera->at.x = Center.x;
    camera->at.y = Center.y;
    camera->at.z = Center.z;
    camera->up.x = sindf(rotY) * sindf(rotX);
    camera->up.y = cosdf(rotX);
    camera->up.z = cosdf(rotY) * sindf(rotX);
}

f32 m219_AngleDiffCalc(f32 arg0, f32 arg1) {
    if (arg0 >= 360.0f) {
        arg0 -= 360.0f;
    } else if (arg0 < 0.0f) {
        arg0 += 360.0f;
    }
    if (arg1 >= 360.0f) {
        arg1 -= 360.0f;
    } else if (arg1 < 0.0f) {
        arg1 += 360.0f;
    }
    arg0 = arg0 - arg1;
    if (arg0 <= -180.0f) {
        arg0 += 360.0f;
    } else if (arg0 >= 180.0f) {
        arg0 -= 360.0f;
    }
    return arg0;
}

f32 m219_AngleStepCalc(f32 target, f32 current, f32 step) {
    f32 diff;
    f32 delta;

    if (target >= 360.0) {
        target -= 360.0;
    } else if (target < 0.0) {
        target += 360.0;
    }
    if (current >= 360.0) {
        current -= 360.0;
    } else if (current < 0.0) {
        current += 360.0;
    }
    diff = fmod(target - current + 360.0, 360.0);
    if (diff < 180.0) {
        if (diff <= step) {
            delta = diff;
        } else {
            delta = step;
        }
    } else if (360.0 - diff <= step) {
        delta = -(360.0 - diff);
    } else {
        delta = -step;
    }
    delta += current;
    if (delta >= 360.0) {
        delta -= 360.0;
    } else if (delta < 0.0) {
        delta += 360.0;
    }
    return delta;
}

f32 m219_InterpCalc(f32 t, f32 start, f32 end) {
    return start + t * (end - start);
}

f32 m219_AngleInterpCalc(f32 arg0, f32 arg1, f32 arg2) {
    return m219_AngleStepCalc(arg2, arg1, fabsf(m219_AngleDiffCalc(arg2, arg1) * arg0));
}

f32 m219_StepCalc(f32 arg0, f32 arg1, f32 arg2) {
    if (__builtin_fabs((f64)(arg0 - arg1)) < arg2) {
        return arg0;
    }

    if (arg0 < arg1) {
        arg2 = -arg2;
    }

    return arg1 + arg2;
}

void m219_WorkPtrSet(omObjData *object, u32 arg1) {
    object->work[0] = arg1 >> 24;
    object->work[1] = (arg1 >> 16) & 0xFF;
    object->work[2] = (arg1 >> 8) & 0xFF;
    object->work[3] = arg1 & 0xFF;
}

u32 m219_WorkPtrGet(omObjData *object) {
    LogJamWorkBytes packed;

    packed.bytes.byte3 = (u8)object->work[0];
    packed.bytes.byte2 = (u8)object->work[1];
    packed.bytes.byte1 = (u8)object->work[2];
    packed.bytes.byte0 = (u8)object->work[3];
    return packed.word;
}

void m219_MotShiftSet(omObjData *object, s16 motion, s16 shift) {
    HmfModel *model = &Hu3DData[object->model[0]];
    MgMotAttr *anim;

    Hu3DMotionShiftSet(object->model[0], object->motion[motion], 0, shift, 0);
    anim = &((MgPlayerWork *)object->data)->unkE8[motion];
    if (anim->unk00 & 1) {
        model->motShiftAttr = 2;
    } else {
        model->motShiftAttr = 0;
    }
    model->unk54 = (u16)anim->unk02;
}

void m219_MotShiftTimeSet(omObjData *object, s16 motion, s16 time) {
    HmfModel *model = &Hu3DData[object->model[0]];

    m219_MotShiftSet(object, motion, 5);
    model->motShiftTime = time;
}

void m219_MotSet(omObjData *object, s16 motion, s16 time) {
    HmfModel *model = &Hu3DData[object->model[0]];
    MgMotAttr *anim;

    model->motId = object->motion[motion];
    model->unk48 = model->motTime = model->motSpeed = 1.0f;
    model->motIdShift = 0xFF;
    model->motTime = time;
    anim = &((MgPlayerWork *)object->data)->unkE8[motion];
    if (anim->unk00 & 1) {
        model->motAttr = 2;
    } else {
        model->motAttr = 0;
    }
    model->unk48 = (u16)anim->unk02;
}

void m219_MotStop(omObjData *object) {
    HmfModel *model = &Hu3DData[object->model[0]];

    model->motSpeed = 0.0f;
}

void m219_MotShiftUpdate(omObjData *object) {
    f32 frame = 0.0f;
    HmfModel *model = &Hu3DData[object->model[0]];

    if (model->motIdShift != 0xFF) {
        if (Hu3DPauseF == 0) {
            frame = model->unk0E + 2;
        }
        if (model->unk0C <= frame) {
            model->motId = model->motIdShift;
            model->motTime = model->motShiftTime;
            model->motAttr = model->motShiftAttr;
            model->unk48 = model->unk54;
            model->motIdShift = 0xFF;
            model->motSpeed = 1.0f;
        }
    }
}

void m219_EffMdlUpdate(omObjData *object) {
    if (object->model[6] != -1) {
        MgEffMdlUpdate((u8)object->model[6]);
    }
}

void m219_NodeMtxCalc(s16 model, const char *name, HuMtx4F *out) {
    s16 nodeMap[4];
    HmfModel *mdl = &Hu3DData[model];
    HmfData *hmf = mdl->hmf;
    s16 node = SearchObjectIndex(hmf, name);
    HmfModelData_Unk64_Unk8C_Struct *motion = &Hu3DMotion[Hu3DData[model].motId];

    motionBakeMtx = out;
    motionBakeNodeMap = nodeMap;
    motionBakeMtxCnt = 0;
    if (mdl->motIdShape != 0xFF) {
        hmf->unk94 = &Hu3DMotion[mdl->motIdShape];
        hmf->unkAC = mdl->motShapeTime;
    } else {
        hmf->unk94 = NULL;
    }
    if (mdl->motIdShift != 0xFF && mdl->unk0C != 0) {
        hmf->unk90 = &Hu3DMotion[mdl->motIdShift];
        hmf->unkA4 = mdl->motShiftTime;
        hmf->unkA8 = (f32)mdl->unk0E / mdl->unk0C;
    } else {
        hmf->unk90 = NULL;
    }
    guMtxIdentF(Hu3DObjMtxStack[0]);
    Hu3DMotionExec(hmf, mdl->motTime, motion, 1);
    if (hmf->unk90 != NULL) {
        Hu3DSubMotionExec(hmf, hmf->unkA4, hmf->unkA8);
    }
    if (hmf->unk94 != NULL) {
        Hu3DMotionExec(hmf, hmf->unkAC, hmf->unk94, 0);
    }
    Hu3DObjMtxStackIdx = 0;
    objMtxCalcFrame(hmf, 0, node);
    if (motionBakeMtxCnt >= 2) {
        osSyncPrintf("Mtx Made Over\n");
    }
}

void m219_NodeWorldMtxCalc(omObjData *object, const char *name, HuMtx4F out) {
    HuMtx4F mtx;
    HuMtx4F local;

    HuMtxIdentF(mtx);
    mtxTransCat(mtx, object->trans.x, object->trans.y, object->trans.z);
    mtxRotCat(mtx, object->rot.x, object->rot.y, object->rot.z);
    mtxScaleCat(mtx, object->scale.x, object->scale.y, object->scale.z);
    m219_NodeMtxCalc(object->model[0], name, &local);
    mtxCat(local, mtx, out);
}

s32 m219_BillboardColorMdlCreate(HuSprAnimData *sprite, u8 *color) {
    u8 *buffer;
    Gfx *gfx;
    Gfx *header;
    HmfData *data;
    u16 format;
    s32 i;
    s32 model;
    s32 size;

    gfx = HuMemAlloc(0x10000);
    header = gfx;
    buffer = (u8 *)gfx;
    model = Hu3DModelDLCreate(0x8C1, gfx, 4);
    data = Hu3DData[model].hmf;
    data->unk60->unk50 |= 0x1010000;
    gfx++;
    HuMemFree(data->unk3C);
    data->unk3C = HuMemAllocTag(sizeof(HmfModelData_Unk64_Unk3C_Struct), Hu3DModelTag);
    m219_BillboardVtxCreate(sprite, data, 1.0f, 0, 0);
    gSPDisplayList(header, osVirtualToPhysical(m219_gfxBillboardInit));
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_CULL_FRONT | G_TEXTURE_GEN_LINEAR);
    gDPSetColorDither(gfx++, G_CD_NOISE);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetTextureConvert(gfx++, G_TC_FILT);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 1, 1, 1, 1);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_AA_ZB_XLU_SURF, G_RM_NOOP2);
    if (sprite->pixelBits & 0x8000) {
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    } else {
        gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    }
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u8 *)gfx - buffer;
    data->unk3C->unk10 = HuMemAllocTag(size, data->unk0E);
    bcopy(buffer, data->unk3C->unk10, size);
    HuMemFree(buffer);
    gfx = HuMemAlloc(0x10000);
    {
        Gfx *textureHeader = gfx;
        buffer = (u8 *)gfx;
        gfx++;
        gSPTexture(textureHeader, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    }
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    if (sprite->palNum >= 2) {
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
        if (sprite->pixelBits == 4) {
            gDPLoadTLUT_pal16(gfx++, 0, sprite->pal);
        } else {
            gDPLoadTLUT_pal256(gfx++, sprite->pal);
        }
        gDPPipeSync(gfx++);
        format = G_IM_FMT_CI;
    } else {
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        gDPPipeSync(gfx++);
        format = sprite->pixelBits;
        format = ((u32)format / 0x8000) * 4;
    }
    switch (sprite->pixelBits & 0xFFF) {
        case 4:
            gDPLoadTextureBlock_4b(gfx++, 0x02000000, format, sprite->pat->sizeX, sprite->pat->sizeY, 0,
                                   G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 8:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_8b, sprite->pat->sizeX, sprite->pat->sizeY, 0,
                                G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 16:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_16b, sprite->pat->sizeX, sprite->pat->sizeY, 0,
                                G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
    gDPPipeSync(gfx++);
    gSPSegment(gfx++, 1, osVirtualToPhysical(data->unk44[0]));
    gSPVertex(gfx++, 0x01000000, 4, 0);
    gSP2Triangles(gfx++, 0, 1, 2, 0, 1, 3, 2, 0);
    gSPClearGeometryMode(gfx++, -1);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u8 *)gfx - buffer;
    data->unk3C->unk14 = HuMemAllocTag(size, data->unk0E);
    bcopy(buffer, data->unk3C->unk14, size);
    HuMemFree(buffer);
    for (i = 0; i < Hu3DBufNum; i++) {
        gfx = (data->unk3C->unk00 + 1)[i] = HuMemAllocTag(0x100, data->unk0E);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 2, osVirtualToPhysical(sprite->pat->data));
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk10));
        gDPSetPrimColor(gfx++, 0, 0, color[0], color[1], color[2], color[3]);
        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk14));
        gDPPipeSync(gfx++);
        gSPEndDisplayList(gfx++);
    }
    data->unk3C->unk00[0] = data->unk3C->unk00[Hu3DBufNo + 1];
    return model;
}

s32 m219_BillboardColorMdlLink(HuSprAnimData *sprite, u16 model, u8 *color) {
    HmfModel *srcModel = Hu3DData + model;
    HmfData *srcData = srcModel->hmf;
    HmfData *data;
    Gfx *gfx;
    s32 newModel;
    s32 i;

    newModel = Hu3DModelDLCreate(srcModel->attr, NULL, 4);
    data = Hu3DData[newModel].hmf;
    data->unk60->unk50 = srcData->unk60->unk50;
    HuMemFree(data->unk3C);
    data->unk3C = HuMemAllocTag(sizeof(HmfModelData_Unk64_Unk3C_Struct), Hu3DModelTag);
    data->unk3C->unk10 = srcData->unk3C->unk10;
    data->unk3C->unk14 = srcData->unk3C->unk14;
    for (i = 0; i < Hu3DBufNum; i++) {
        gfx = (data->unk3C->unk00 + 1)[i] = HuMemAllocTag(0x100, data->unk0E);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 2, osVirtualToPhysical(sprite->pat->data));
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk10));
        gDPSetPrimColor(gfx++, 0, 0, color[0], color[1], color[2], color[3]);
        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk14));
        gDPPipeSync(gfx++);
        gSPEndDisplayList(gfx++);
    }
    data->unk3C->unk00[0] = data->unk3C->unk00[Hu3DBufNo + 1];
    return newModel;
}

void m219_BillboardColorPatSet(u16 model, HuSprAnimData *sprite, u16 frame, u8 *color) {
    HmfModel *modelData = Hu3DData + model;
    HmfData *data = modelData->hmf;
    Gfx *gfx = data->unk3C->unk00[Hu3DBufNo + 1];

    data->unk3C->unk00[0] = gfx;
    gDPPipeSync(gfx);
    gSPSegment(gfx + 1, 2, osVirtualToPhysical(sprite->pat[frame].data));
    gSPDisplayList(gfx + 2, osVirtualToPhysical(data->unk3C->unk10));
    gDPSetPrimColor(gfx + 3, 0, 0, color[0], color[1], color[2], color[3]);
    gDPPipeSync(gfx + 4);
    gSPDisplayList(gfx + 5, osVirtualToPhysical(data->unk3C->unk14));
    gDPPipeSync(gfx + 6);
    gSPEndDisplayList(gfx + 7);
}

s32 m219_BillboardVtxCreate(HuSprAnimData *sprite, HmfData *data, f32 scale, s16 xOffset, s16 yOffset) {
    s32 capacity = 0x1000;
    s32 width, height, scaledWidth, scaledHeight;
    s32 size, slices, textureHeight, sliceHeight, vertexCount;
    s32 i, j;
    Vtx_t *vertices, *start;

    if (sprite->palNum >= 2) {
        capacity = 0x800;
    }
    width = sprite->pat->sizeX;
    height = sprite->pat->sizeY;
    scaledWidth = width * 100.0 * scale / 32.0;
    scaledHeight = height * 100.0 * scale / 32.0;
    if ((sprite->pixelBits & 0xFFF) == 4) {
        size = ((width + 1) & 0xFFFE) * height * 4;
    } else {
        size = width * height * sprite->pixelBits;
    }
    size /= 8;
    slices = size / capacity;
    if (slices <= 0) {
        slices = 1;
    }
    textureHeight = height / slices;
    sliceHeight = scaledHeight / slices;
    vertexCount = slices * 4;
    size = slices * 4 * sizeof(Vtx_t);
    start = vertices = HuMemAllocTag(size, data->unk0E);
    memset(start, 0, size);
    for (i = 0; i < slices; i++, vertices += 4) {
        vertices[0].ob[0] = scaledWidth * 0.5;
        vertices[0].ob[1] = scaledHeight * 0.5 - sliceHeight * i;
        vertices[0].tc[0] = (width - 1) << 6;
        vertices[0].tc[1] = 0;
        vertices[1].ob[0] = scaledWidth * 0.5;
        vertices[1].ob[1] = scaledHeight * 0.5 - sliceHeight * (i + 1);
        vertices[1].tc[0] = (width - 1) << 6;
        vertices[1].tc[1] = (textureHeight - 1) << 6;
        vertices[2].ob[0] = -(scaledWidth * 0.5);
        vertices[2].ob[1] = scaledHeight * 0.5 - sliceHeight * i;
        vertices[2].tc[0] = 0;
        vertices[2].tc[1] = 0;
        vertices[3].ob[0] = -(scaledWidth * 0.5);
        vertices[3].ob[1] = scaledHeight * 0.5 - sliceHeight * (i + 1);
        vertices[3].tc[0] = 0;
        vertices[3].tc[1] = (textureHeight - 1) << 6;
        for (j = 0; j < 4; j++) {
            vertices[j].ob[0] += xOffset;
            vertices[j].ob[1] += yOffset;
            vertices[j].ob[2] = 0;
            vertices[j].flag = 0;
            vertices[j].cn[3] = 255;
            vertices[j].cn[0] = vertices[j].cn[1] = vertices[j].cn[2] = 0;
        }
    }
    vertices = start;
    for (i = 0; i < Hu3DBufNum; i++) {
        Vtx_t *destination;
        Vtx_t *source;
        data->unk44[i] = HuMemAllocTag(vertexCount * sizeof(Vtx_t), data->unk0E);
        destination = (Vtx_t *)data->unk44[i];
        source = vertices;
        for (j = 0; j < vertexCount; j++) {
            *destination++ = *source++;
        }
    }
    HuMemFree(start);
    return slices;
}
