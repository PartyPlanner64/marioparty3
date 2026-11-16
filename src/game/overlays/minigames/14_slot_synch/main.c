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
#include "game/gamemes.h"
#include "game/input.h"
#include "game/printfunc.h"

typedef struct SlotSynchPlayerWork { // 0x30 bytes, four entries
    s16 unk_00;
    s16 unk_02; // team
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    f32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    s32 unk_18;
    s16 unk_1C; // player index
    s16 unk_1E; // pad
    s16 unk_20; // character
    s16 unk_22; // CPU flag
    s16 unk_24; // CPU difficulty
    s16 unk_26;
    s16 unk_28;
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
} SlotSynchPlayerWork;

typedef struct SlotSynchTeam { // 0x20 bytes, two entries (one per team)
    omObjData *unk_00;
    omObjData *unk_04;
    SlotSynchPlayerWork *unk_08;
    SlotSynchPlayerWork *unk_0C;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} SlotSynchTeam;

typedef struct SlotSynchBlock { // 0x3C bytes, four entries (one per player)
    s16 unk_00;                 // model
    u8 unk_02;
    u8 unk_03;
    s8 unk_04;
    u8 unk_05;
    u8 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C; // state
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    s32 unk_20;
    f32 unk_24;
    f32 unk_28;
    f32 unk_2C;
    f32 unk_30;
    f32 unk_34;
    f32 unk_38;
} SlotSynchBlock;

typedef struct SlotSynchReelRow { // 0x94 bytes
    u16 unk_00[0x48];           // vertex indices
    s16 unk_90;
    s16 unk_92; // vertex count
} SlotSynchReelRow;

typedef struct SlotSynchReel { // 0x20 bytes, two entries
    s16 unk_00;              // model
    s16 unk_02;
    s16 unk_04;
    char unk_06[0x2];
    f32 unk_08;
    f32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    s16 unk_18; // row count
    char unk_1A[0x2];
    SlotSynchReelRow *unk_1C;
} SlotSynchReel;

typedef union SlotSynchWorkBytes { // packs the top byte of each work word
    u32 word;
    struct {
        u32 byte3 : 8;
        u32 byte2 : 8;
        u32 byte1 : 8;
        u32 byte0 : 8;
    } bytes;
} SlotSynchWorkBytes;

typedef struct SlotSynchLampPos { // 6 bytes
    s16 x;
    s16 y;
    u8 unk_04;
    u8 unk_05;
} SlotSynchLampPos;

typedef struct SlotSynchLamp { // 0x2C bytes, 24 entries
    s16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
    u16 unk_0C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    f32 unk_20;
    f32 unk_24;
    f32 unk_28;
} SlotSynchLamp;

typedef struct SlotSynchLampSys { // 0xC bytes
    omObjData *unk_00;
    s16 unk_04;
    u16 unk_06;
    SlotSynchLamp *unk_08;
} SlotSynchLampSys;

typedef struct SlotSynchScore { // 0x10 bytes, two entries
    s16 unk_00;               // sprite group
    s16 unk_02;               // x
    s16 unk_04;               // y
    s16 unk_06[2];
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
} SlotSynchScore;

typedef union SlotSynchColor {
    u32 word;
    u8 rgba[4];
} SlotSynchColor;

typedef struct SlotSynchEffect { // 0x34 bytes, 8 entries
    u16 active;
    s16 model;
    SlotSynchColor color;
    f32 frame;
    f32 speed;
    Vec pos;
    Vec vel;
    Vec scale;
} SlotSynchEffect;

typedef struct SlotSynchPos {
    s16 x;
    s16 y;
} SlotSynchPos;

typedef struct SlotSynchPrize { // 0x58 bytes, five entries
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    s16 unk_04[4];
    s16 unk_0C[4][3];
    s16 unk_24;
    s16 unk_26;
    s16 unk_28;
    s16 unk_2A;
    f32 unk_2C;
    f32 unk_30;
    f32 unk_34[9];
} SlotSynchPrize;

typedef struct SlotSynchSprPri {
    s16 unk_00;
    u16 unk_02[4]; // sprite priorities, aliased as m220_stageSprPriTbl
} SlotSynchSprPri;

extern s32 omCharModelNoTbl[][6];
extern u8 omAllPauseF;
extern s16 Hu3DModelTag;
extern u8 Hu3DBufNo;

extern u16 m220_stageSprPriTbl[4];

Vec m220_blockPosTbl[4] = {
    { -300.0f, 0.0f, 0.0f },
    { -125.0f, 0.0f, -0.0f },
    { 125.0f, 0.0f, -0.0f },
    { 300.0f, 0.0f, 0.0f }
};
Vec m220_reelPosTbl[2] = {
    { -255.0f, 0.0f, -300.0f },
    { 255.0f, 0.0f, -300.0f }
};
SlotSynchPos m220_scorePosTbl[2] = { { 70, 40 }, { 250, 40 } };
f32 m220_blockFaceRotTbl[5] = { 0.0f, 90.0f, 180.0f, 270.0f, 0.0f };
u8 m220_blockSymbolTbl[2][4] = { { 0, 1, 2, 3 }, { 2, 3, 1, 0 } };
s16 m220_prizePointTbl[4] = { 3, 1, 2, -1 };
SlotSynchColor m220_chipColor = { 0xE9DDA180 };
SlotSynchColor m220_halfWhiteColor = { 0xFFFFFF80 };
SlotSynchColor m220_whiteColor = { 0xFFFFFFFF };
s32 m220_winAnimTbl[8] = {
    0x000200A5, 0x000300A5, 0x000700A5, 0x000400A5,
    0x000500A5, 0x000600A5, 0x000800A5, 0x0009001C
};
s32 m220_loseAnimTbl[8] = {
    0x000200A6, 0x000300A6, 0x000700A6, 0x000400A6,
    0x000500A6, 0x000600A6, 0x000800A6, 0x0009001D
};
s32 m220_exitTimer = 0;
s32 m220_playerOrderTbl[4] = { 0, 1, 2, 3 };
s16 m220_teamPlayerAltTbl[4][2][2] = {
    { { 0, 1 }, { 2, 3 } },
    { { 3, 0 }, { 1, 2 } },
    { { 2, 3 }, { 0, 1 } },
    { { 1, 2 }, { 3, 0 } }
};
s16 m220_playerPrioTbl[4] = { 0x12, 0x13, 0x15, 0x14 };
s32 m220_voiceChrTbl[8] = {
    0x00020000, 0x00030000, 0x00070000, 0x00040000,
    0x00050000, 0x00060000, 0x00080000, 0x00090000
};
s32 m220_voiceNoTbl[4] = { 0x2F, 0x30, 0x36, 0x37 };
u16 m220_comSymbolTbl[6] = { 0, 2, 1, 3, 0, 0 };
u16 m220_comSpinTbl[8] = { 3, 3, 3, 3, 2, 3, 3, 0 };
SlotSynchLampPos m220_lampPos0Tbl[12] = {
    { 16, 92, 0, 0 },
    { 40, 92, 0, 1 },
    { 64, 92, 0, 2 },
    { 88, 92, 0, 3 },
    { 30, 108, 0, 3 },
    { 54, 108, 0, 2 },
    { 78, 108, 0, 1 },
    { 102, 108, 0, 0 },
    { 16, 124, 0, 3 },
    { 40, 124, 0, 0 },
    { 64, 124, 0, 1 },
    { 88, 124, 0, 2 }
};
SlotSynchLampPos m220_lampPos1Tbl[12] = {
    { 304, 92, 0, 0 },
    { 280, 92, 0, 1 },
    { 256, 92, 0, 2 },
    { 232, 92, 0, 3 },
    { 290, 108, 0, 3 },
    { 266, 108, 0, 2 },
    { 242, 108, 0, 1 },
    { 218, 108, 0, 0 },
    { 304, 124, 0, 3 },
    { 280, 124, 0, 0 },
    { 256, 124, 0, 1 },
    { 232, 124, 0, 2 }
};
s16 m220_blockTypeTbl[4] = { 0, 1, 1, 0 };
f32 m220_chrHeightTbl[8] = { 150.0f, 150.0f, 150.0f, 150.0f, 150.0f, 180.0f, 150.0f, 150.0f };
s32 m220_prizeMdlTbl[4] = { 0x000A0000, 0x000A00A5, 0x000A008E, 0x000A00EE };
s32 m220_prizeMot1Tbl[4] = { 0x000A0018, 0x000A00B3, 0x000A00A0, 0x000A00FA };
s32 m220_prizeMot2Tbl[4] = { 0x000A0002, 0x000A00A9, 0x000A0090, 0x000A00F1 };
f32 m220_prizeMotSpeedTbl[4] = { 1.5f, 1.75f, 1.0f, 1.2f };
s32 m220_prizeSeTbl[4] = { 0x393, 0x391, 0x392, 0x394 };
s32 m220_faceSprTbl[8] = {
    0x00210008, 0x00210009, 0x0021000A, 0x0021000B,
    0x0021000C, 0x0021000D, 0x0021000E, 0x0021000F
};
s32 m220_cameraDebugMode = 0;
s32 m220_cameraDebugX = 0;
s32 m220_cameraDebugY = 0;

Gfx m220_gfxRdpInit[] = {
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

Gfx m220_gfxRspInit[] = {
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx m220_gfxInit[] = {
    gsSPDisplayList(m220_gfxRspInit),
    gsSPDisplayList(m220_gfxRdpInit),
    gsSPEndDisplayList(),
};

Gfx m220_gfxBillboardInit[] = {
    gsDPPipeSync(),
    gsSPDisplayList(m220_gfxInit),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPSetGeometryMode(G_ZBUFFER | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x00),
    gsDPSetPrimColor(0, 0, 0x00, 0x00, 0x00, 0xFF),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

omObjData *m220_mainObj BSS;
s32 m220_flag10F BSS;
s32 m220_frameCnt BSS;
s32 m220_phaseTimer BSS;
s32 m220_timer BSS;
s32 m220_phase BSS;
s32 m220_resultWait BSS;
SlotSynchTeam *m220_teamTbl BSS;
SlotSynchPlayerWork *m220_playerWorkTbl BSS;
SlotSynchSprPri m220_winTeamNo BSS;
SlotSynchLampSys m220_lampSys BSS;
SlotSynchBlock *m220_blockTbl BSS;
SlotSynchReel *m220_reelTbl BSS;
omObjData *m220_prizeObj BSS;
SlotSynchPrize *m220_prizeTbl BSS;
s16 *m220_sprTbl BSS;
SlotSynchScore *m220_scoreTbl BSS;
omObjData *m220_smokeObj BSS;
SlotSynchEffect *m220_smokeTbl BSS;
u8 m220_smokeTblPad[4] BSS;            /* Unreferenced. */
MgCameraKey m220_cameraKeyTbl[2] BSS;   // target, origin
s32 m220_cameraMoveTimer BSS;
s32 m220_cameraMoveTime BSS;
s32 m220_cameraMoveF BSS;
u8 m220_cameraMoveFPad[4] BSS; /* Unreferenced. */
MinigameFlow m220_mgFlow BSS;

void m220_MainObjInit(omObjData *object);
void m220_MainObjMain(omObjData *object);
void m220_ExitObjMain(omObjData *object);
void m220_ExitCheck(omObjData *object);
void m220_TeamInit(void);
void m220_PlayerObjInit(omObjData *object);
void m220_TeamObjMain(omObjData *object);
void m220_PlayerObjMain(omObjData *object);
void m220_PlayerComInput(omObjData *object);
void m220_StageObjInit(omObjData *object);
void m220_StageObjMain(omObjData *object);
void m220_LampInit(void);
s16 m220_LampCreate(f32 x, f32 y, u8 arg2, u8 arg3, u16 arg4);
void m220_LampSprInit(void);
void m220_BlockInit(void);
void m220_BlockObjMain(omObjData *object);
void m220_ReelInit(void);
void m220_LampFlash(u8 arg0, u8 arg1);
void m220_BlockSpinStart(s16 arg0);
s16 m220_BlockSymbolGet(s16 arg0);
s16 m220_BlockHitPlayerGet(s16 arg0);
s16 m220_BlockSymbolAheadGet(s16 arg0, s16 arg1);
void m220_BlockTargetSet(s16 arg0, s16 arg1);
s32 m220_SmokeCreate(Vec *pos, Vec *vel, Vec *scale, f32 speed, u8 *color);
s16 m220_BlockFaceSymbolGet(s16 arg0, s16 arg1);
void m220_ReelVtxUpdate(SlotSynchReel *reel);
void m220_ReelObjMain(omObjData *object);
void m220_ReelScrollSet(s16 arg0, f32 arg1, f32 arg2);
void m220_PrizeObjMain(omObjData *object);
s16 m220_MotCreate(s32 file);
void m220_CameraMoveObjMain(omObjData *object);
void m220_CameraKeyStore(s32 arg0);
void m220_CameraPosUpdate(s32 camIndex);
void m220_CameraMoveStart(f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames);
f32 m220_AngleInterpCalc(f32 t, f32 start, f32 end);
void m220_SmokeObjMain(omObjData *object);
void m220_LampObjMain(omObjData *object);
void m220_SprPosSet(s16 arg0, s16 arg1, f32 arg2, f32 arg3);
s32 m220_BillboardColorMdlCreate(HuSprAnimData *sprite, u8 *color);
s32 m220_BillboardColorMdlLink(HuSprAnimData *sprite, u16 model, u8 *color);
void m220_BillboardColorPatSet(u16 model, HuSprAnimData *sprite, u16 frame, u8 *color);
void m220_ScoreObjMain(omObjData *object);
void m220_TeamScoreAdd(s16 arg0, s32 arg1);
void m220_TeamVibrate(s16 arg0, s16 arg1);
f32 m220_AngleStepCalc(f32 target, f32 current, f32 step);
u16 m220_SprAnimRead(s32 file);
void m220_BlockStopStart(s16 arg0);
s16 m220_PrizeCreate(s16 arg0, s16 arg1);
s16 m220_PrizeDoneCheck(s16 arg0);
void m220_ScoreSet(s16 arg0, s16 arg1);
u32 m220_WorkPtrGet(omObjData *arg0);
void m220_ScoreChrSet(s16 team, s16 chr0, s16 chr1, s16 arg3);
void m220_WorkPtrSet(omObjData *arg0, u32 arg1);
s16 m220_TeamStateGet(s16 arg0);
void m220_PrizeClose(void);
void m220_StageInit(void);
void m220_PrizeInit(void);
void m220_ScoreInit(void);
void m220_SmokeInit(void);
void m220_CameraInit(void);
s16 m220_BlockStopCheck(s16 arg0);
f32 m220_AngleDiffCalc(f32 arg0, f32 arg1);
f32 m220_InterpCalc(f32 t, f32 start, f32 end);
f32 m220_AngleStepCalc(f32 target, f32 current, f32 step);
s32 m220_BillboardVtxCreate(HuSprAnimData *sprite, HmfData *data, f32 scale, s16 xOffset, s16 yOffset);

void m220_ObjectSetup(void) {
    omObjData *obj;
    u8 camIndex;

    MapCollInit(50);
    omInitObjMan(50, 0);
    omGameSysInit();
    Hu3DSprModelInit(64);
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
    m220_timer = 900;
    m220_phaseTimer = 0;
    m220_frameCnt = 0;
    m220_phase = 0;
    m220_resultWait = 0;
    m220_winTeamNo.unk_00 = -1;
    m220_sprTbl = HuMemAllocTag(0x40, TAG_OVERLAY);
    m220_mainObj = omAddObj(0x20, 0, 0, -1, m220_MainObjInit);
    memset(&m220_mgFlow, 0, 0x28);
    m220_mgFlow.type = MINIGAME_BATTLE;
    MgFlowInit(&m220_mgFlow);
}

void m220_MainObjInit(omObjData *object) {
    object->func = m220_MainObjMain;
    m220_ScoreInit();
    m220_PrizeInit();
    m220_StageInit();
    m220_SmokeInit();
    m220_TeamInit();
    m220_CameraInit();
    if (_CheckFlag(10)) {
        m220_flag10F = 1;
    }
    WipeCreateIn(0xFF, 16);
}

void m220_MainObjMain(omObjData *object) {
    SlotSynchTeam *team0 = &m220_teamTbl[0];
    SlotSynchTeam *team1 = &m220_teamTbl[1];

    switch (m220_phase) {
        case 0:
            if (WipeStatGet() == 0) {
                GMesCreate(5);
                HuAudFXPlay(0xE);
                m220_phase++;
                m220_phaseTimer = 0;
            }
            break;
        case 1:
            if (m220_phaseTimer == 30) {
                HuAudSeqPlay(0x2E);
            }
            if (GMesStatGet() == 0) {
                GMesCreate(0x1A, (m220_timer + 29) / 30, 156, 32);
                MgFlowStatSet(MG_STATE_PLAY);
                m220_phase++;
            }
            break;
        case 2:
            m220_timer--;
            GMesTimerValueSet((m220_timer + 29) / 30);
            if (m220_timer <= 0) {
                HuAudFXAllStop();
                GMesTimerEnd();
                GMesCreate(0x10);
                MgFlowStatSet(MG_STATE_FINISH);
                HuAudSeqFadeOut(120);
                m220_timer = 0;
                m220_phaseTimer = 0;
                m220_phase++;
            }
            break;
        case 3:
            if (GMesStatGet() == 0 && m220_TeamStateGet(0) == 0 && m220_TeamStateGet(1) == 0) {
                MgFlowStatSet(MG_STATE_RESULT);
                m220_PrizeClose();
                m220_phaseTimer = 0;
                m220_phase++;
            }
            break;
        case 4:
            if (m220_phaseTimer >= 15) {
                if (team0->unk_16 > team1->unk_16) {
                    GMesCreate(0x1E, team0->unk_08->unk_20, team0->unk_0C->unk_20);
                    GwPlayer[team0->unk_08->unk_1C].bonusCoin += 10;
                    GwPlayer[team0->unk_0C->unk_1C].bonusCoin += 10;
                    team0->unk_08->unk_04 = team0->unk_0C->unk_04 = 0;
                    team1->unk_08->unk_04 = team1->unk_0C->unk_04 = 1;
                    HuAudSeqPlay(0x66);
                    m220_resultWait = 140;
                } else if (team0->unk_16 < team1->unk_16) {
                    GMesCreate(0x1E, team1->unk_08->unk_20, team1->unk_0C->unk_20);
                    GwPlayer[team1->unk_08->unk_1C].bonusCoin += 10;
                    GwPlayer[team1->unk_0C->unk_1C].bonusCoin += 10;
                    team0->unk_08->unk_04 = team0->unk_0C->unk_04 = 1;
                    team1->unk_08->unk_04 = team1->unk_0C->unk_04 = 0;
                    HuAudSeqPlay(0x66);
                    m220_resultWait = 140;
                } else {
                    GMesCreate(0x20);
                    team0->unk_08->unk_04 = team0->unk_0C->unk_04 = 1;
                    team1->unk_08->unk_04 = team1->unk_0C->unk_04 = 1;
                    HuAudSeqPlay(0x6C);
                    m220_resultWait = 144;
                }
                m220_phaseTimer = 0;
                m220_phase++;
            }
            break;
        case 5:
            if (GMesStatGet() == 0) {
                m220_phaseTimer = 0;
                m220_phase++;
            }
            break;
        case 6:
            if (m220_phaseTimer >= 15) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 16);
                HuAudSeqFadeOut(16);
                HuAudFXAllFadeOut(16);
                m220_phaseTimer = 0;
                m220_phase++;
            }
            break;
        default:
            if (WipeStatGet() == 0) {
                object->func = m220_ExitObjMain;
            }
            break;
    }
    m220_ExitCheck(object);
    m220_frameCnt++;
    m220_phaseTimer++;
}

void m220_ExitObjMain(omObjData *object) {
    HuAudSeqStop();
    omOvlReturnEx(1);
}

void m220_ExitCheck(omObjData *object) {
    if (m220_exitTimer != 0) {
        if (m220_exitTimer == 1) {
            object->func = m220_ExitObjMain;
        }
        m220_exitTimer--;
    } else if (omSysExitReq == 1 && WipeStatGet() == 0) {
        m220_exitTimer = 16;
        WipeCreateOut(WIPE_TYPE_NORMAL, m220_exitTimer);
        HuAudSeqFadeOut(m220_exitTimer);
        HuAudFXAllFadeOut((s16)m220_exitTimer);
    }
}

void m220_TeamInit(void) {
    s32 playerIds[2][2];
    SlotSynchTeam *team;
    SlotSynchPlayerWork *player;
    omObjData *obj;
    s32 i;
    s32 j;
    s32 invalid;
    s32 group0Count;
    s32 group1Count;
    s32 temp;
    s32 group;

    team = m220_teamTbl = HuMemAllocTag(sizeof(SlotSynchTeam) * 2, TAG_OVERLAY);
    m220_playerWorkTbl = HuMemAllocTag(sizeof(SlotSynchPlayerWork) * 4, TAG_OVERLAY);
    memset(m220_playerWorkTbl, 0, sizeof(SlotSynchPlayerWork) * 4);
    invalid = FALSE;
    group1Count = 0;
    group0Count = 0;
    for (i = 0; i < 4; i++) {
        group = GwPlayer[m220_playerOrderTbl[i]].group;
        switch (group) {
            case 0:
                if (group0Count < 2) {
                    playerIds[group][group0Count] = m220_playerOrderTbl[i];
                    group0Count++;
                } else {
                    invalid = TRUE;
                }
                break;
            case 1:
                if (group1Count < 2) {
                    playerIds[group][group1Count] = m220_playerOrderTbl[i];
                    group1Count++;
                } else {
                    invalid = TRUE;
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
                playerIds[i][j] = m220_teamPlayerAltTbl[group][i][j];
            }
        }
    } else {
        if (rand8() & 1) {
            temp = playerIds[0][0];
            playerIds[0][0] = playerIds[0][1];
            playerIds[0][1] = temp;
        }
        if (rand8() & 1) {
            temp = playerIds[1][0];
            playerIds[1][0] = playerIds[1][1];
            playerIds[1][1] = temp;
        }
    }
    MgShadowAltSet(1);
    MgPlayerParamReset();
    for (i = 0; i < 2; i++, team++) {
        obj = omAddObj(i + 16, 0, 0, -1, m220_TeamObjMain);
        m220_WorkPtrSet(obj, (u32)team);
        team->unk_10 = i;
        team->unk_12 = 0;
        team->unk_14 = 0;
        team->unk_16 = 0;
        team->unk_18 = -1;
        team->unk_1A = -1;
        team->unk_1C = 0;
        team->unk_1E = -1;
        for (j = 0; j < 2; j++) {
            player = &m220_playerWorkTbl[i * 2 + j];
            player->unk_00 = i * 2 + j;
            player->unk_02 = i;
            player->unk_1C = playerIds[i][j];
            obj = mgPlayerObjTbl[mgPlayerObjNum] =
                omAddObj(m220_playerPrioTbl[player->unk_00], 9, 60, -1, m220_PlayerObjInit);
            mgPlayerObjNum++;
            obj->trans.x = m220_blockPosTbl[player->unk_00].x;
            obj->trans.z = m220_blockPosTbl[player->unk_00].z;
            if (j == 0) {
                team->unk_00 = obj;
                team->unk_08 = player;
            } else {
                team->unk_04 = obj;
                team->unk_0C = player;
            }
            m220_WorkPtrSet(obj, (u32)player);
        }
        m220_ScoreChrSet(i, GwPlayer[team->unk_08->unk_1C].chr, GwPlayer[team->unk_0C->unk_1C].chr, 0);
    }
}

void m220_PlayerObjInit(omObjData *object) {
    SlotSynchPlayerWork *player;
    MgPlayerWork *data;
    s16 playerIndex;
    s16 chr;
    s32 index;
    s32 model;
    s32 anim;

    player = (SlotSynchPlayerWork *)m220_WorkPtrGet(object);
    playerIndex = player->unk_1C;
    chr = GwPlayer[playerIndex].chr;
    player->unk_20 = chr;
    player->unk_1E = GwPlayer[playerIndex].pad;
    player->unk_22 = GwPlayer[playerIndex].stat & 1;
    player->unk_24 = GwPlayer[playerIndex].cpu_difficulty;
    player->unk_26 = 0;
    player->unk_28 = 0;
    player->unk_2A = 0;
    player->unk_2C = -1;
    model = omCharModelNoTbl[chr][0];
    anim = omCharModelNoTbl[chr][2];
    MgPlayerCreate(object, model, anim, playerIndex, 0x2A9, 0x299);
    data = object->data;
    data->unk50 &= ~1;
    data->unkEC = NULL;
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(chr, 0), 1, 0);
    MgPlayerMotLoad(object, 1, CharMotionDataNumGet(chr, 1), 1, 0);
    MgPlayerMotLoad(object, 6, CharMotionDataNumGet(chr, 4), 1, 19);
    MgPlayerMotLoad(object, 21, CharMotionDataNumGet(chr, 0x1F), 0, 0);
    MgPlayerMotLoad(object, 38, CharMotionDataNumGet(chr, 0x33), 1, 60);
    MgPlayerMotLoad(object, 39, CharMotionDataNumGet(chr, 0x3A), 1, 60);
    if (chr != 5) {
        index = rand8() & 1;
        MgPlayerMotLoad(object, 13, CharMotionDataNumGet(chr, m220_voiceNoTbl[index]), 1, 120);
        player->unk_18 = m220_voiceChrTbl[chr] | m220_voiceNoTbl[index];
    } else {
        MgPlayerMotLoad(object, 13, CharMotionDataNumGet(chr, m220_voiceNoTbl[1]), 1, 120);
        player->unk_18 = m220_voiceChrTbl[chr] | m220_voiceNoTbl[1];
    }
    MgPlayerMotLoad(object, 14, CharMotionDataNumGet(chr, m220_voiceNoTbl[2]), 1, 120);
    MgPlayerMotSet(object, 0);
    MgPlayerMapAttrSet(object, 0, 2);
    player->unk_04 = -1;
    player->unk_0A = 0;
    player->unk_08 = 0;
    player->unk_0C = player->unk_10 = player->unk_14 = 0.0f;
    object->func = m220_PlayerObjMain;
}

void m220_TeamObjMain(omObjData *object) {
    SlotSynchTeam *team = (SlotSynchTeam *)m220_WorkPtrGet(object);
    SlotSynchBlock *machine;
    MgPlayerWork *data0;
    MgPlayerWork *data1;
    s16 result0;
    s16 result1;

    switch (team->unk_12) {
        case 0:
            if (MgFlowStatGet() == MG_STATE_PLAY) {
                m220_BlockSpinStart(team->unk_08->unk_00);
                m220_BlockSpinStart(team->unk_0C->unk_00);
                machine = &m220_blockTbl[team->unk_08->unk_00];
                if (machine->unk_20 != -1) {
                    HuAudFXStop((s16)machine->unk_20);
                    machine->unk_20 = -1;
                }
                machine->unk_20 = HuAudFXPlay(team->unk_10 == 0 ? 0x38F : 0x395);
                team->unk_14 = 0;
                team->unk_12 = 1;
            } else if (MgFlowStatGet() == MG_STATE_FINISH || MgFlowStatGet() == MG_STATE_RESULT) {
                m220_BlockStopStart(team->unk_08->unk_00);
                m220_BlockStopStart(team->unk_0C->unk_00);
            }
            break;
        case 1:
            if (MgFlowStatGet() != MG_STATE_PLAY) {
                team->unk_1C = 0;
                team->unk_14 = 0;
                team->unk_12 = 0;
            }
            if (team->unk_14 >= 30) {
                team->unk_1C = 1;
                team->unk_14 = 0;
                team->unk_12 = 2;
            }
            break;
        case 2:
            if (m220_BlockStopCheck(team->unk_08->unk_00) && m220_BlockStopCheck(team->unk_0C->unk_00)) {
                if (MgFlowStatGet() == MG_STATE_PLAY) {
                    machine = &m220_blockTbl[team->unk_08->unk_00];
                    if (machine->unk_20 != -1) {
                        HuAudFXStop((s16)machine->unk_20);
                        machine->unk_20 = -1;
                    }
                }
                team->unk_1C = 0;
                result0 = m220_BlockSymbolGet(team->unk_08->unk_00);
                result1 = m220_BlockSymbolGet(team->unk_0C->unk_00);
                if (MgFlowStatGet() == MG_STATE_FINISH) {
                    m220_BlockStopStart(team->unk_08->unk_00);
                    m220_BlockStopStart(team->unk_0C->unk_00);
                }
                if (result0 == result1) {
                    team->unk_1A = result0;
                } else {
                    team->unk_1A = 4;
                }
                team->unk_18 = m220_PrizeCreate(team->unk_10, team->unk_1A);
                team->unk_14 = 0;
                team->unk_12 = 3;
            } else if (MgFlowStatGet() != MG_STATE_PLAY) {
                team->unk_1C = 0;
                data0 = team->unk_00->data;
                data1 = team->unk_04->data;
                if (data0->unk38 == 1000.0f && data1->unk38 == 1000.0f) {
                    if (MgFlowStatGet() == MG_STATE_FINISH) {
                        m220_BlockStopStart(team->unk_08->unk_00);
                        m220_BlockStopStart(team->unk_0C->unk_00);
                    }
                    team->unk_14 = 0;
                    team->unk_12 = 0;
                }
            }
            break;
        case 3:
            if (m220_PrizeDoneCheck(team->unk_18)) {
                if (team->unk_1A != 4) {
                    m220_LampFlash(team->unk_1A, team->unk_10);
                }
                if (team->unk_1A != 3 && team->unk_1A != 4) {
                    MgPlayerMotSet(team->unk_00, 38);
                    MgPlayerMotSet(team->unk_04, 38);
                } else {
                    MgPlayerMotSet(team->unk_00, 39);
                    MgPlayerMotSet(team->unk_04, 39);
                }
                team->unk_14 = 0;
                team->unk_12 = 4;
            }
            break;
        case 4:
            if (team->unk_14 >= 30.0f) {
                MgPlayerMotSet(team->unk_00, 0);
                MgPlayerMotSet(team->unk_04, 0);
                team->unk_14 = 0;
                team->unk_12 = 0;
            }
            break;
    }
    team->unk_14++;
    if (team->unk_16 >= 100) {
        team->unk_16 = 99;
    } else if (team->unk_16 < 0) {
        team->unk_16 = 0;
    }
    m220_ScoreSet(team->unk_10, team->unk_16);
}

void m220_TeamScoreAdd(s16 arg0, s32 arg1) {
    SlotSynchTeam *slot = &m220_teamTbl[arg0];
    slot->unk_16 += arg1;
}

s16 m220_TeamStateGet(s16 arg0) {
    SlotSynchTeam *slot = &m220_teamTbl[arg0];

    return slot->unk_12;
}

void m220_TeamVibrate(s16 arg0, s16 arg1) {
    SlotSynchTeam *team = &m220_teamTbl[arg0];

    switch (arg1) {
        case 1:
            omVibrate(team->unk_08->unk_1C, 5, 0, 5);
            omVibrate(team->unk_0C->unk_1C, 5, 0, 5);
            break;
        case 2:
            omVibrate(team->unk_08->unk_1C, 2, 3, 10);
            omVibrate(team->unk_0C->unk_1C, 2, 3, 10);
            break;
        case 3:
            omVibrate(team->unk_08->unk_1C, 10, 0, 10);
            omVibrate(team->unk_0C->unk_1C, 10, 0, 10);
            break;
        case 4:
            omVibrate(team->unk_08->unk_1C, 2, 2, 20);
            omVibrate(team->unk_0C->unk_1C, 2, 2, 20);
            break;
        case 5:
            omVibrate(team->unk_08->unk_1C, 20, 0, 20);
            omVibrate(team->unk_0C->unk_1C, 20, 0, 20);
            break;
        default:
            omVibrate(team->unk_08->unk_1C, 30, 0, 30);
            omVibrate(team->unk_0C->unk_1C, 30, 0, 30);
            break;
    }
}

void m220_PlayerObjMain(omObjData *object) {
    s16 done = TRUE;
    SlotSynchPlayerWork *player = (SlotSynchPlayerWork *)m220_WorkPtrGet(object);
    SlotSynchTeam *team = &m220_teamTbl[player->unk_02];
    u16 btn;
    u16 btnDown;
    s16 stickX;
    s16 stickY;

    if (player->unk_22 != 0) {
        m220_PlayerComInput(object);
    }
    if (player->unk_04 != -1) {
        switch (player->unk_04) {
            case 0:
                MgPlayerMotSet(object, 13);
                CharAnimCreate(object->model[0], 2, player->unk_20, m220_winAnimTbl[player->unk_20]);
                HuAudCharVoicePlayPlayer(player->unk_18, -1, player->unk_1C);
                break;
            case 1:
                MgPlayerMotSet(object, 14);
                CharAnimCreate(object->model[0], 2, player->unk_20, m220_loseAnimTbl[player->unk_20]);
                break;
        }
        player->unk_04 = -1;
    }
    player->unk_0C = object->trans.x;
    player->unk_10 = object->trans.y;
    player->unk_14 = object->trans.z;
    if (m220_BlockStopCheck(player->unk_00) != 0) {
        done = FALSE;
    }
    if (team->unk_1C == 0 || !done) {
        btn = HuPadBtn[player->unk_1E];
        btnDown = HuPadBtnDown[player->unk_1E];
        HuPadBtn[player->unk_1E] = 0;
        HuPadBtnDown[player->unk_1E] = 0;
    } else {
        btnDown = 0;
        btn = 0;
    }
    stickX = HuPadStkX[player->unk_1E];
    stickY = HuPadStkY[player->unk_1E];
    HuPadStkX[player->unk_1E] = 0;
    HuPadStkY[player->unk_1E] = 0;
    MgPlayerObjMain(object);
    HuPadStkX[player->unk_1E] = stickX;
    HuPadStkY[player->unk_1E] = stickY;
    if (team->unk_1C == 0) {
        HuPadBtn[player->unk_1E] = btn;
        HuPadBtnDown[player->unk_1E] = btnDown;
    }
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    player->unk_0A++;
}

void m220_PlayerComInput(omObjData *object) {
    SlotSynchPlayerWork *player = (SlotSynchPlayerWork *)m220_WorkPtrGet(object);
    SlotSynchTeam *team = &m220_teamTbl[player->unk_02];
    SlotSynchPlayerWork *partner;
    u16 spin;
    s16 result;
    s16 index;

    if (team->unk_08 == player) {
        partner = team->unk_0C;
    } else {
        partner = team->unk_08;
    }
    HuPadBtn[player->unk_1E] = 0;
    HuPadBtnDown[player->unk_1E] = 0;
    spin = m220_comSpinTbl[player->unk_20];
    switch (team->unk_12) {
        case 0:
            if (player->unk_2C != -1) {
                break;
            }
            if (partner->unk_22 == 0) {
                player->unk_2A = 150;
                player->unk_2C = m220_comSymbolTbl[(u8)(rand8() % 3)];
                break;
            }
            if ((u8)(rand8() % 100) < player->unk_24 * 15 + 60) {
                player->unk_28 = 0;
            } else {
                player->unk_28 = 1;
            }
            player->unk_2A = (u8)(rand8() % 30) + 75 - player->unk_24 * 12;
            if (team->unk_1E == -1) {
                index = (u8)(rand8() % 100) * (1.0f - player->unk_24 * 0.075f);
                index /= 25;
                team->unk_1E = player->unk_2C = m220_comSymbolTbl[index];
            } else {
                player->unk_2C = team->unk_1E;
                if (abs(player->unk_2A - partner->unk_2A) < 9.0f) {
                    if (partner->unk_2A < player->unk_2A) {
                        player->unk_2A = player->unk_2A + 9.0f;
                    } else {
                        player->unk_2A = player->unk_2A - 9.0f;
                    }
                }
            }
            break;
        case 1:
            player->unk_0A = 0;
            break;
        case 2:
            if (m220_BlockStopCheck(player->unk_00) == 0) {
                m220_BlockSymbolGet(player->unk_00);
                if (player->unk_0A > player->unk_2A) {
                    if (player->unk_28 == 0) {
                        result = m220_BlockSymbolAheadGet(player->unk_00, spin);
                        if (result == player->unk_2C) {
                            m220_BlockTargetSet(player->unk_00, result);
                            HuPadBtnDown[player->unk_1E] |= A_BUTTON;
                        }
                    } else if (m220_BlockSymbolAheadGet(player->unk_00, spin) != player->unk_2C) {
                        HuPadBtnDown[player->unk_1E] |= A_BUTTON;
                    }
                } else if (partner->unk_22 == 0 && m220_BlockStopCheck(partner->unk_00)) {
                    player->unk_0A = 0;
                    if (m220_BlockSymbolAheadGet(player->unk_00, spin) == m220_BlockSymbolGet(partner->unk_00)) {
                        m220_BlockTargetSet(player->unk_00, m220_BlockSymbolGet(partner->unk_00));
                        HuPadBtnDown[player->unk_1E] |= A_BUTTON;
                    }
                }
            }
            player->unk_26 = m220_BlockSymbolGet(player->unk_00);
            break;
        case 3:
            if (player->unk_2C != -1) {
                player->unk_28 = 0;
                player->unk_2A = 0;
                team->unk_1E = player->unk_2C = -1;
            }
            break;
    }
}

void m220_StageInit(void) {
    s16 i;
    s16 count;
    s32 priority = 0xFFFF;

    m220_LampInit();
    m220_BlockInit();
    m220_ReelInit();
    m220_stageSprPriTbl[0] = priority;
    priority--;
    m220_stageSprPriTbl[1] = priority;
    priority--;
    count = 12;
    for (i = 0; i < count; i++) {
        m220_LampCreate(m220_lampPos0Tbl[i].x, m220_lampPos0Tbl[i].y, m220_lampPos0Tbl[i].unk_05, 0,
                                 priority);
        priority--;
    }
    count = 12;
    for (i = 0; i < count; i++) {
        m220_LampCreate(m220_lampPos1Tbl[i].x, m220_lampPos1Tbl[i].y, m220_lampPos1Tbl[i].unk_05, 1,
                                 priority);
        priority--;
    }
    m220_stageSprPriTbl[2] = priority;
    priority--;
    m220_stageSprPriTbl[3] = priority;
    priority--;
    m220_LampSprInit();
    mgMapObjTbl[mgMapObjNum++] = omAddObj(0x1D, 16, 0, -1, m220_StageObjInit);
    MgMapBaseSet(0);
}

void m220_StageObjInit(omObjData *object) {
    MgMapWork *work;
    s16 group;

    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 0;
    MgMapSlideSet(object, 20.0f);
    MgMapFrictionSet(object, 1.0f);
    MgMapAccelSet(object, 10.0f);
    MgMapBoxSet(object, 0.0f, -2000.0f, -2000.0f, 2000.0f, 2000.0f);
    group = HuSprGrpCreate(4, 0);
    m220_sprTbl[3] = m220_SprAnimRead(0x350007);
    HuSprGrpMemberSet(group, 0, m220_sprTbl[3], 0);
    HuSprPosSet(group, 0, 0, 0);
    HuSprAnimModeSet(group, 0, HUSPR_ANIM_MODE_STOP);
    HuSprPatNoSet(group, 0, 0);
    HuSprAttrSet(group, 0, 0x580C);
    HuSprPriSet(group, 0, m220_stageSprPriTbl[0]);
    m220_sprTbl[8] = m220_SprAnimRead(0x350008);
    HuSprGrpMemberSet(group, 1, m220_sprTbl[8], 0);
    HuSprPosSet(group, 1, 0, 84);
    HuSprAnimModeSet(group, 1, HUSPR_ANIM_MODE_STOP);
    HuSprPatNoSet(group, 1, 0);
    HuSprAttrSet(group, 1, 0x580C);
    HuSprPriSet(group, 1, m220_stageSprPriTbl[1]);
    m220_sprTbl[9] = m220_SprAnimRead(0x350009);
    HuSprGrpMemberSet(group, 2, m220_sprTbl[9], 0);
    HuSprPosSet(group, 2, 160, 0);
    HuSprAnimModeSet(group, 2, HUSPR_ANIM_MODE_STOP);
    HuSprPatNoSet(group, 2, 0);
    HuSprAttrSet(group, 2, 0x580C);
    HuSprPriSet(group, 2, m220_stageSprPriTbl[2]);
    m220_sprTbl[0] = m220_SprAnimRead(0x35000A);
    HuSprGrpMemberSet(group, 3, m220_sprTbl[0], 0);
    HuSprPosSet(group, 3, 0, 138);
    HuSprAnimModeSet(group, 3, HUSPR_ANIM_MODE_STOP);
    HuSprPatNoSet(group, 3, 0);
    HuSprAttrSet(group, 3, 0x580C);
    HuSprPriSet(group, 3, m220_stageSprPriTbl[3]);
    object->func = m220_StageObjMain;
}

void m220_StageObjMain(omObjData *object) {
}

void m220_LampInit(void) {
    memset(&m220_lampSys, 0, sizeof(m220_lampSys));
    m220_lampSys.unk_06 = 0;
    m220_lampSys.unk_08 = HuMemAllocTag(0x420, TAG_OVERLAY);
    memset(m220_lampSys.unk_08, 0, 0x420);
    m220_lampSys.unk_00 = omAddObj(0x1C, 0, 0, -1, NULL);
}

s16 m220_LampCreate(f32 x, f32 y, u8 arg2, u8 arg3, u16 arg4) {
    SlotSynchLamp *sprite;
    s16 index;

    if (m220_lampSys.unk_00->func != NULL || m220_lampSys.unk_06 >= 24) {
        return -1;
    }
    index = m220_lampSys.unk_06;
    sprite = &m220_lampSys.unk_08[index];
    sprite->unk_00 = index;
    sprite->unk_06 = arg2;
    sprite->unk_07 = arg3;
    sprite->unk_02 = arg4;
    sprite->unk_1C = sprite->unk_14 = sprite->unk_24 = x;
    sprite->unk_20 = sprite->unk_18 = sprite->unk_28 = y;
    sprite->unk_08 = 0;
    sprite->unk_0A = 0;
    sprite->unk_09 = 0;
    sprite->unk_0B = 0;
    sprite->unk_0C = 0;
    sprite->unk_10 = 0;
    m220_lampSys.unk_06++;
    return index;
}

void m220_LampSprInit(void) {
    s16 anims[4];
    SlotSynchLamp *sprite;
    s16 i;
    s16 group;

    anims[0] = m220_sprTbl[4] = m220_SprAnimRead(0x350003);
    anims[1] = m220_sprTbl[5] = m220_SprAnimRead(0x350005);
    anims[2] = m220_sprTbl[6] = m220_SprAnimRead(0x350004);
    anims[3] = m220_sprTbl[7] = m220_SprAnimRead(0x350006);
    group = m220_lampSys.unk_04 = HuSprGrpCreate(m220_lampSys.unk_06, 0);
    sprite = m220_lampSys.unk_08;
    for (i = 0; i < m220_lampSys.unk_06; i++, sprite++) {
        HuSprScaleSet(group, sprite->unk_00, 0.75f, 0.75f);
        HuSprGrpMemberSet(group, sprite->unk_00, anims[sprite->unk_06], 0);
        m220_SprPosSet(group, sprite->unk_00, sprite->unk_24, sprite->unk_28);
        HuSprAnimModeSet(group, sprite->unk_00, HUSPR_ANIM_MODE_STOP);
        HuSprPatNoSet(group, sprite->unk_00, 0);
        HuSprAttrSet(group, sprite->unk_00, 0x4000580C);
        HuSprPriSet(group, sprite->unk_00, sprite->unk_02);
    }
    m220_lampSys.unk_00->func = m220_LampObjMain;
}

void m220_LampObjMain(omObjData *object) {
    SlotSynchLamp *sprite = m220_lampSys.unk_08;
    s16 i;
    f32 bounce;

    for (i = 0; i < m220_lampSys.unk_06; i++, sprite++) {
        sprite->unk_1C = sprite->unk_24;
        sprite->unk_20 = sprite->unk_28;
        switch (sprite->unk_08) {
            case 1:
                if (sprite->unk_0B != 0) {
                    sprite->unk_0B--;
                    sprite->unk_04 = 0;
                    break;
                }
                if (sprite->unk_0A & 0x80) {
                    if ((++sprite->unk_0A & 0x7F) >= 2) {
                        sprite->unk_0A = 2;
                    }
                } else if ((--sprite->unk_0A & 0x7F) == 0) {
                    sprite->unk_0A = 0x80;
                }
                HuSprPatNoSet(m220_lampSys.unk_04, sprite->unk_00, (s16)(u8)(sprite->unk_0A & 2));
                bounce = sindf(sprite->unk_04 * 25);
                sprite->unk_24 = sprite->unk_14;
                sprite->unk_28 = sprite->unk_18 - fabs(bounce) * sprite->unk_10;
                sprite->unk_09 = 1;
                if (sprite->unk_04 >= sprite->unk_0C) {
                    sprite->unk_04 = 0;
                    sprite->unk_08++;
                }
                break;
            case 2:
                if (sprite->unk_28 < sprite->unk_18 - 1.0f) {
                    if (sprite->unk_0A & 0x80) {
                        if ((++sprite->unk_0A & 0x7F) >= 2) {
                            sprite->unk_0A = 2;
                        }
                    } else if ((--sprite->unk_0A & 0x7F) == 0) {
                        sprite->unk_0A = 0x80;
                    }
                    HuSprPatNoSet(m220_lampSys.unk_04, sprite->unk_00, (s16)(u8)(sprite->unk_0A & 2));
                    sprite->unk_28 += 1.0f;
                } else {
                    HuSprPatNoSet(m220_lampSys.unk_04, sprite->unk_00, 0);
                    sprite->unk_28 = sprite->unk_18;
                    sprite->unk_04 = 0;
                    sprite->unk_08 = 0;
                }
                sprite->unk_09 = 1;
                break;
        }
        if (sprite->unk_09 != 0) {
            m220_SprPosSet(m220_lampSys.unk_04, sprite->unk_00, sprite->unk_24, sprite->unk_28);
            sprite->unk_09 = 0;
        }
        sprite->unk_04++;
    }
}

void m220_LampFlash(u8 arg0, u8 arg1) {
    SlotSynchLamp *sprite = m220_lampSys.unk_08;
    s16 i;

    for (i = 0; i < m220_lampSys.unk_06; i++, sprite++) {
        if (sprite->unk_06 == arg0 && sprite->unk_07 == arg1 && sprite->unk_08 == 0) {
            sprite->unk_08 = 1;
            sprite->unk_04 = 0;
            sprite->unk_0A = 0x80;
            sprite->unk_0C = (f32)(u8)(rand8() % 100) * 0.01 * 30.0 + 30.0;
            sprite->unk_0B = rand8() % 22;
            sprite->unk_10 = (f32)(u8)(rand8() % 100) * 0.01 * 5.0 + 5.0;
        }
    }
}

void m220_BlockInit(void) {
    SlotSynchBlock *machine;
    s16 i;
    s16 model1 = -1;
    s16 model0 = -1;

    machine = m220_blockTbl = HuMemAllocTag(sizeof(SlotSynchBlock) * 4, TAG_OVERLAY);
    memset(machine, 0, sizeof(SlotSynchBlock) * 4);
    for (i = 0; i < 4; i++, machine++) {
        machine->unk_03 = m220_blockTypeTbl[i];
        if (machine->unk_03 == 0) {
            if (model0 != -1) {
                machine->unk_00 = Hu3DModelLink(model0);
            } else {
                model0 = machine->unk_00 = Hu3DModelRead(0x350000, 0xB9);
            }
        } else {
            if (model1 != -1) {
                machine->unk_00 = Hu3DModelLink(model1);
            } else {
                model1 = machine->unk_00 = Hu3DModelRead(0x350001, 0xB9);
            }
        }
        machine->unk_02 = i;
        machine->unk_04 = i % 2;
        machine->unk_0A = 0;
        machine->unk_05 = 0;
        machine->unk_06 = 0;
        machine->unk_0C = 0;
        machine->unk_10 = 0.0f;
        machine->unk_08 = -1;
        machine->unk_14 = 0.0f;
        machine->unk_18 = 0.5f;
        machine->unk_1C = 14.0f;
        machine->unk_20 = -1;
        machine->unk_24 = m220_blockPosTbl[i].x;
        machine->unk_2C = m220_blockPosTbl[i].z;
        machine->unk_28 = 280.0f;
        machine->unk_30 = 0.0f;
        machine->unk_34 = machine->unk_38 = 0.0f;
    }
    omAddObj(0x1A, 0, 0, -1, m220_BlockObjMain);
}

void m220_BlockObjMain(omObjData *object) {
    SlotSynchBlock *machine = m220_blockTbl;
    Vec pos;
    f32 angle;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++, machine++) {
        switch (machine->unk_0C) {
            case 0:
                break;
            case 1:
                machine->unk_14 += machine->unk_18;
                if (machine->unk_14 >= machine->unk_1C) {
                    machine->unk_14 = machine->unk_1C;
                    machine->unk_0C = 2;
                    machine->unk_0A = 0;
                }
                break;
            case 2:
                break;
            case 3:
                machine->unk_28 += machine->unk_10;
                machine->unk_10 -= 6.0;
                if (machine->unk_28 <= 280.0) {
                    machine->unk_28 = 280.0f;
                    machine->unk_0A = 0;
                    machine->unk_0C = 0;
                }
                break;
            case 4:
                Hu3DModelAttrSet(machine->unk_00, 4, 4);
                pos.x = machine->unk_24;
                pos.y = machine->unk_28;
                pos.z = machine->unk_2C;
                m220_SmokeCreate(&pos, NULL, NULL, 1.0f, m220_whiteColor.rgba);
                machine->unk_0C = 5;
                break;
            case 5:
                break;
        }
        angle = machine->unk_30 + 45.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        } else if (angle < 0.0f) {
            angle += 360.0f;
        }
        machine->unk_05 = angle / 90.0f;
        if (machine->unk_05 >= 4) {
            machine->unk_05 -= 4;
        }
        machine->unk_06 = m220_BlockFaceSymbolGet(machine->unk_02, machine->unk_05);
        machine->unk_30 += machine->unk_14;
        if (machine->unk_30 >= 360.0f) {
            machine->unk_30 -= 360.0f;
        }
        if (m220_BlockHitPlayerGet(machine->unk_02) != -1 && (machine->unk_0C == 1 || machine->unk_0C == 2)) {
            HuAudPlayerFXPlay(0x38E, i);
            if (machine->unk_08 == -1) {
                machine->unk_14 = 0.0f;
                machine->unk_30 = m220_blockFaceRotTbl[machine->unk_05];
            } else {
                machine->unk_14 = 0.0f;
                for (j = 0; j < 4; j++) {
                    machine->unk_30 = j * 90;
                    angle = machine->unk_30 + 45.0f;
                    if (angle > 360.0f) {
                        angle -= 360.0f;
                    } else if (angle < 0.0f) {
                        angle += 360.0f;
                    }
                    machine->unk_05 = angle / 90.0f;
                    if (machine->unk_05 >= 4) {
                        machine->unk_05 -= 4;
                    }
                    machine->unk_06 = m220_BlockFaceSymbolGet(machine->unk_02, machine->unk_05);
                    if (machine->unk_06 == machine->unk_08) {
                        break;
                    }
                }
            }
            machine->unk_28 = 340.0f;
            machine->unk_10 = 0.0f;
            machine->unk_08 = -1;
            machine->unk_0A = 0;
            machine->unk_0C = 3;
        }
        Hu3DModelPosSet(machine->unk_00, machine->unk_24, machine->unk_28, machine->unk_2C);
        Hu3DModelRotSet(machine->unk_00, machine->unk_30, machine->unk_34, machine->unk_38);
        machine->unk_0A++;
    }
}

s16 m220_BlockHitPlayerGet(s16 arg0) {
    SlotSynchBlock *machine = &m220_blockTbl[arg0];
    MgPlayerWork *data;
    SlotSynchPlayerWork *player;
    omObjData *obj;
    f32 height;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = mgPlayerObjTbl[i];
        data = obj->data;
        player = (SlotSynchPlayerWork *)m220_WorkPtrGet(obj);
        // The original checks the x distance twice.
        if (fabs(obj->trans.x - machine->unk_24) > 50.0 || fabs(obj->trans.x - machine->unk_24) > 50.0) {
            continue;
        }
        if (machine->unk_0C == 1 || machine->unk_0C == 2) {
            height = m220_chrHeightTbl[player->unk_20];
        } else {
            height = m220_chrHeightTbl[player->unk_20] + 50.0;
        }
        if (height + obj->trans.y >= machine->unk_28 && height + player->unk_10 <= machine->unk_28) {
            obj->trans.y = machine->unk_28 - m220_chrHeightTbl[player->unk_20] * 1.1;
            data->unk38 = 0.0f;
            return i;
        }
    }
    return -1;
}

void m220_BlockSpinStart(s16 arg0) {
    SlotSynchBlock *machine = &m220_blockTbl[arg0];
    f32 t;

    if (m220_BlockStopCheck(arg0)) {
        t = m220_timer / 900.0f;
        machine->unk_1C = m220_InterpCalc(t, 30.0f, 14.0f);
        machine->unk_0C = 1;
        machine->unk_0A = 0;
    }
}

s16 m220_BlockStopCheck(s16 arg0) {
    SlotSynchBlock *machine = &m220_blockTbl[arg0];

    return machine->unk_0C == 0;
}

s16 m220_BlockSymbolGet(s16 arg0) {
    SlotSynchBlock *machine = &m220_blockTbl[arg0];
    f32 angle = machine->unk_30 + 45.0f;
    s16 quadrant;

    if (angle > 360.0f) {
        angle -= 360.0f;
    } else if (angle < 0.0f) {
        angle += 360.0f;
    }
    quadrant = angle / 90.0f;
    return m220_BlockFaceSymbolGet(arg0, quadrant);
}

s16 m220_BlockSymbolAheadGet(s16 arg0, s16 arg1) {
    SlotSynchBlock *machine = &m220_blockTbl[arg0];
    s16 quadrant;
    f32 angle = machine->unk_30 + arg1 * machine->unk_14 + 45.0f;

    while (angle > 360.0f) {
        angle -= 360.0f;
    }
    while (angle < 0.0f) {
        angle += 360.0f;
    }
    quadrant = angle / 90.0f;
    return m220_BlockFaceSymbolGet(arg0, quadrant);
}

s16 m220_BlockFaceSymbolGet(s16 arg0, s16 arg1) {
    SlotSynchBlock *machine = &m220_blockTbl[arg0];

    return m220_blockSymbolTbl[machine->unk_03][arg1];
}

void m220_BlockStopStart(s16 arg0) {
    SlotSynchBlock *machine = &m220_blockTbl[arg0];

    if (machine->unk_0C != 4 && machine->unk_0C != 5) {
        machine->unk_0C = 4;
        machine->unk_0A = 0;
    }
}

void m220_BlockTargetSet(s16 arg0, s16 arg1) {
    SlotSynchBlock *machine = &m220_blockTbl[arg0];

    machine->unk_08 = arg1;
}

void m220_ReelInit(void) {
    s16 heights[256];
    SlotSynchReel *reel;
    SlotSynchReelRow *row;
    HmfData *hmf;
    Vtx *vtx;
    s16 i;
    s16 j;
    s16 k;
    s16 count;
    s16 temp;

    reel = m220_reelTbl = HuMemAllocTag(sizeof(SlotSynchReel) * 2, TAG_OVERLAY);
    memset(reel, 0, sizeof(SlotSynchReel) * 2);
    for (i = 0; i < 2; i++, reel++) {
        reel->unk_00 = Hu3DModelRead(0x350002, 0xB9);
        Hu3DModelPosSet(reel->unk_00, m220_reelPosTbl[i].x, m220_reelPosTbl[i].y,
                        m220_reelPosTbl[i].z);
        Hu3DModelScaleSet(reel->unk_00, 1.0f, 0.85f, 1.0f);
        Hu3DModelVtxBufMake(reel->unk_00);
        hmf = Hu3DData[reel->unk_00].hmf;
        reel->unk_02 = i;
        reel->unk_04 = 0;
        reel->unk_08 = -75.0f;
        reel->unk_0C = 75.0f;
        reel->unk_10 = 0.75f;
        reel->unk_14 = 0.0f;
        if (i == 0) {
            vtx = hmf->unk40;
            count = 0;
            for (j = 0; j < hmf->unk18; j++, vtx++) {
                for (k = 0; k < count; k++) {
                    if (heights[k] == vtx->v.ob[1]) {
                        break;
                    }
                }
                if (k >= count) {
                    heights[k] = vtx->v.ob[1];
                    count++;
                }
                if (count >= 256) {
                    osSyncPrintf("VTX OVER!! \n");
                }
            }
            for (j = 0; j < count - 1; j++) {
                for (k = j + 1; k < count; k++) {
                    if (heights[j] < heights[k]) {
                        temp = heights[j];
                        heights[j] = heights[k];
                        heights[k] = temp;
                    }
                }
            }
            reel->unk_18 = count;
            row = reel->unk_1C = HuMemAllocTag(count * sizeof(SlotSynchReelRow), TAG_OVERLAY);
            for (j = 0; j < reel->unk_18; j++, row++) {
                row->unk_90 = heights[j];
                row->unk_92 = 0;
            }
            vtx = hmf->unk40;
            for (j = 0; j < hmf->unk18; j++, vtx++) {
                for (k = 0; k < reel->unk_18; k++) {
                    row = &reel->unk_1C[k];
                    if (vtx->v.ob[1] == row->unk_90) {
                        row->unk_00[row->unk_92] = j;
                        row->unk_92++;
                        break;
                    }
                    if (row->unk_92 >= 72) {
                        osSyncPrintf("VTX H OVER!! \n");
                    }
                }
            }
        } else {
            reel->unk_18 = m220_reelTbl->unk_18;
            reel->unk_1C = m220_reelTbl->unk_1C;
        }
    }
    omSetStatBit(omAddObj(0x1B, 0, 0, -1, m220_ReelObjMain), 0xA0);
}

void m220_ReelObjMain(omObjData *object) {
    SlotSynchReel *reel = m220_reelTbl;
    s32 i;

    for (i = 0; i < 2; i++, reel++) {
        if (omPauseChk() + omAllPauseF == 0 && reel->unk_04 == 1) {
            reel->unk_08 += reel->unk_14;
            if (reel->unk_08 >= 359.99999046325684 || reel->unk_08 <= -120.00000476837158) {
                reel->unk_14 = 0.0f;
                reel->unk_04 = 0;
            }
        }
        m220_ReelVtxUpdate(reel);
    }
}

void m220_ReelVtxUpdate(SlotSynchReel *reel) {
    SlotSynchReelRow *row = reel->unk_1C;
    HmfData *hmf = Hu3DData[reel->unk_00].hmf;
    Vtx *src = hmf->unk40;
    Vtx *dst = hmf->unk44[Hu3DBufNo];
    f32 dist;
    f32 scale;
    s32 i;
    s32 j;

    for (i = 0; i < reel->unk_18; i++, row++) {
        dist = fabsf(reel->unk_08 - row->unk_90 * 0.85f);
        if (dist > reel->unk_0C) {
            scale = 0.0f;
        } else {
            scale = 1.0f - dist / reel->unk_0C;
        }
        if (scale >= 1.0f) {
            scale = 1.0f;
        } else if (scale <= 0.0f) {
            scale = 0.0f;
        }
        if (scale != 0.0f) {
            scale = scale * reel->unk_10 + 1.0f;
            for (j = 0; j < row->unk_92; j++) {
                dst[row->unk_00[j]].v.ob[0] = src[row->unk_00[j]].v.ob[0] * scale;
                dst[row->unk_00[j]].v.ob[2] = src[row->unk_00[j]].v.ob[2] * scale;
            }
        } else {
            for (j = 0; j < row->unk_92; j++) {
                dst[row->unk_00[j]].v = src[row->unk_00[j]].v;
            }
        }
    }
}

void m220_ReelScrollSet(s16 arg0, f32 arg1, f32 arg2) {
    SlotSynchReel *reel = &m220_reelTbl[arg0];

    reel->unk_04 = 1;
    reel->unk_08 = arg1;
    reel->unk_14 = arg2;
}

void m220_PrizeInit(void) {
    SlotSynchPrize *spin;
    s32 i;
    s32 j;

    spin = m220_prizeTbl = HuMemAllocTag(sizeof(SlotSynchPrize) * 5, TAG_OVERLAY);
    memset(spin, 0, sizeof(SlotSynchPrize) * 5);
    for (i = 0; i < 5; i++, spin++) {
        spin->unk_00 = 0;
        spin->unk_01 = 0;
        spin->unk_02 = 0;
        spin->unk_03 = 0;
        spin->unk_26 = 0;
        spin->unk_2A = 0;
        spin->unk_28 = 0;
        spin->unk_2C = 0;
        spin->unk_30 = 0;
        if (i == 0) {
            for (j = 0; j < 4; j++) {
                spin->unk_04[j] = Hu3DModelRead(m220_prizeMdlTbl[j], 0x299);
                Hu3DModelAttrSet(spin->unk_04[j], 4, 4);
                spin->unk_0C[j][0] = Hu3DData[spin->unk_04[j]].motId;
                spin->unk_0C[j][1] = m220_MotCreate(m220_prizeMot1Tbl[j]);
                spin->unk_0C[j][2] = m220_MotCreate(m220_prizeMot2Tbl[j]);
            }
            spin->unk_24 = Hu3DModelRead(9, 0x99);
            Hu3DModelAttrSet(spin->unk_24, 4, 4);
        } else {
            for (j = 0; j < 4; j++) {
                spin->unk_04[j] = Hu3DModelLink(m220_prizeTbl->unk_04[j]);
                Hu3DModelAttrSet(spin->unk_04[j], 4, 4);
                spin->unk_0C[j][0] = m220_prizeTbl->unk_0C[j][0];
                spin->unk_0C[j][1] = m220_prizeTbl->unk_0C[j][1];
                spin->unk_0C[j][2] = m220_prizeTbl->unk_0C[j][2];
            }
            spin->unk_24 = Hu3DModelLink(m220_prizeTbl->unk_24);
            Hu3DModelAttrSet(spin->unk_24, 4, 4);
        }
    }
    m220_prizeObj = omAddObj(0x19, 0, 6, -1, m220_PrizeObjMain);
}

void m220_PrizeObjMain(omObjData *object) {
    SlotSynchPrize *spin;
    HmfModel *model;
    Vec pos;
    Vec vel;
    Vec scale;
    f32 baseAngle;
    f32 angle;
    f32 shadowScale;
    s32 modelId;
    s32 i;
    s32 j;

    if (m220_prizeTbl == NULL) {
        return;
    }
    for (spin = m220_prizeTbl, i = 0; i < 5; i++, spin++) {
        if (spin->unk_00 == 0) {
            continue;
        }
        if (spin->unk_26 != 4) {
            modelId = spin->unk_04[spin->unk_26];
            model = &Hu3DData[modelId];
        } else {
            modelId = spin->unk_04[0];
            model = &Hu3DData[modelId];
        }
        switch (spin->unk_28) {
            case 0:
                spin->unk_34[1] += 20.0000002980232239;
                spin->unk_34[6] = spin->unk_34[7] = spin->unk_34[8] = spin->unk_34[1] / 255.000007152557373;
                if (spin->unk_34[1] >= 0.0f) {
                    Hu3DModelAttrSet(modelId, 4, 0);
                    Hu3DModelAttrSet(spin->unk_24, 4, 0);
                }
                if (spin->unk_03 == 0 && spin->unk_34[1] > 204.000008761882867) {
                    baseAngle = (f32)(u8)(rand8() % 100) * 0.01 * 360.0;
                    for (j = 0; j < 4; j++) {
                        pos.x = spin->unk_34[0];
                        pos.y = spin->unk_34[1];
                        pos.z = spin->unk_34[2];
                        angle = baseAngle + j * 90.0f;
                        vel.x = sindf(angle) * 100.0 * 0.100000001490116119;
                        vel.z = cosdf(angle) * 100.0 * 0.100000001490116119;
                        vel.y = 10.0f;
                        scale.x = scale.y = scale.z = 0.5f;
                        m220_SmokeCreate(&pos, &vel, &scale, 1.0f, m220_halfWhiteColor.rgba);
                    }
                    HuAudFXPlay(0x390);
                }
                if (spin->unk_34[1] >= 255.000007152557373) {
                    HuAudPlayerFXPlay(m220_prizeSeTbl[spin->unk_26], spin->unk_01);
                    if (spin->unk_26 == 3) {
                        m220_TeamVibrate(spin->unk_01, 4);
                    } else {
                        m220_TeamVibrate(spin->unk_01, 3);
                    }
                    spin->unk_34[1] = 255.0f;
                    spin->unk_2C = 20.0f;
                    spin->unk_2A = 0;
                    spin->unk_28++;
                }
                break;
            case 1:
                if (model->motSpeed == 0.0f && spin->unk_2C < 0.0f) {
                    model->motSpeed = 1.0f;
                }
                if (spin->unk_01 == 0) {
                    spin->unk_34[0] += 1.49999996647238731;
                } else {
                    spin->unk_34[0] -= 1.49999996647238731;
                }
                spin->unk_34[2] += 10.0000001490116119;
                spin->unk_34[1] += spin->unk_2C;
                spin->unk_2C -= 1.63330006599426269531f;
                if (spin->unk_34[1] <= 0.0f) {
                    pos.x = spin->unk_34[0];
                    pos.y = spin->unk_34[1];
                    pos.z = spin->unk_34[2];
                    m220_SmokeCreate(&pos, NULL, NULL, 1.0f, m220_chipColor.rgba);
                    Hu3DMotionShiftSet(modelId, spin->unk_0C[spin->unk_26][0], 0, 5, 2);
                    m220_TeamScoreAdd(spin->unk_01, m220_prizePointTbl[spin->unk_26]);
                    spin->unk_02 = 1;
                    spin->unk_34[1] = 0.0f;
                    spin->unk_2A = 0;
                    spin->unk_28++;
                }
                break;
            case 2:
                if (spin->unk_2A >= 7.5f) {
                    Hu3DMotionShiftSet(modelId, spin->unk_0C[spin->unk_26][2], 0, 5, 2);
                    model->motSpeed = m220_prizeMotSpeedTbl[spin->unk_26];
                    spin->unk_30 = 0.0f;
                    spin->unk_2A = 0;
                    spin->unk_28++;
                }
                break;
            case 3:
                spin->unk_30 += 3.50000000000000044;
                if (spin->unk_30 > 15.0000005960464478) {
                    spin->unk_30 = 15.000001f;
                }
                if (!(spin->unk_01 & 1)) {
                    spin->unk_34[0] -= spin->unk_30;
                    spin->unk_34[4] = m220_AngleStepCalc(-90.0f, spin->unk_34[4], 15.0f);
                } else {
                    spin->unk_34[0] += spin->unk_30;
                    spin->unk_34[4] = m220_AngleStepCalc(90.0f, spin->unk_34[4], 15.0f);
                }
                if (fabs(spin->unk_34[0]) >= 600.0) {
                    spin->unk_2A = 0;
                    spin->unk_28 = 64;
                }
                break;
            case 16:
                spin->unk_34[1] += 20.0000002980232239;
                if (spin->unk_34[1] >= 205.000007152557373) {
                    pos.x = spin->unk_34[0];
                    pos.y = spin->unk_34[1];
                    pos.z = spin->unk_34[2];
                    vel.x = vel.z = 0.0f;
                    vel.y = 10.0f;
                    m220_SmokeCreate(&pos, &vel, NULL, 1.0f, m220_whiteColor.rgba);
                    spin->unk_34[1] = 255.0f;
                    spin->unk_2C = 20.0f;
                    m220_TeamVibrate(spin->unk_01, 2);
                    m220_TeamScoreAdd(spin->unk_01, 0);
                    spin->unk_02 = 1;
                    spin->unk_2A = 0;
                    spin->unk_28 = 64;
                }
                break;
            case 64:
                spin->unk_00 = 0;
                spin->unk_28 = 0;
                spin->unk_2A = 0;
                Hu3DModelAttrSet(modelId, 4, 4);
                break;
        }
        Hu3DModelPosSet(modelId, spin->unk_34[0], spin->unk_34[1], spin->unk_34[2]);
        Hu3DModelRotSet(modelId, spin->unk_34[3], spin->unk_34[4], spin->unk_34[5]);
        Hu3DModelScaleSet(modelId, spin->unk_34[6], spin->unk_34[7], spin->unk_34[8]);
        shadowScale = 1.0 - spin->unk_34[1] / 765.000021457672119;
        if (shadowScale < 0.5f) {
            shadowScale = 0.5f;
        }
        Hu3DModelPosSet(spin->unk_24, spin->unk_34[0], 0.0f, spin->unk_34[2]);
        Hu3DModelScaleSet(spin->unk_24, shadowScale, 1.0f, shadowScale);
        spin->unk_2A++;
    }
}

s16 m220_PrizeCreate(s16 arg0, s16 arg1) {
    SlotSynchPrize *spin;
    HmfModel *model;
    s16 modelId;
    s32 i;

    if (m220_prizeTbl == NULL) {
        return -1;
    }
    for (spin = m220_prizeTbl, i = 0; i < 5; i++, spin++) {
        if (spin->unk_00 != 0) {
            continue;
        }
        spin->unk_00 = 1;
        spin->unk_01 = arg0;
        spin->unk_02 = 0;
        spin->unk_03 = 0;
        spin->unk_26 = arg1;
        spin->unk_2A = 0;
        spin->unk_2C = 0;
        spin->unk_34[0] = m220_reelPosTbl[spin->unk_01].x;
        spin->unk_34[2] = m220_reelPosTbl[spin->unk_01].z;
        spin->unk_34[1] = m220_reelPosTbl[spin->unk_01].y - 20.0000002980232239;
        spin->unk_34[3] = spin->unk_34[4] = spin->unk_34[5] = 0.0f;
        spin->unk_34[6] = spin->unk_34[7] = spin->unk_34[8] = 0.1f;
        if (spin->unk_26 != 4) {
            spin->unk_28 = 0;
            modelId = spin->unk_04[spin->unk_26];
            Hu3DModelAttrSet(modelId, 4, 4);
            Hu3DData[modelId].motId = spin->unk_0C[spin->unk_26][1];
            model = &Hu3DData[modelId];
            model->motTime = 0.0f;
            model->motSpeed = 0.0f;
            model->motAttr &= ~2;
        } else {
            spin->unk_28 = 16;
        }
        m220_ReelScrollSet(spin->unk_01, spin->unk_34[1], 20.0f);
        return i;
    }
    return -1;
}

s16 m220_PrizeDoneCheck(s16 arg0) {
    SlotSynchPrize *spin;

    if (m220_prizeTbl == NULL) {
        return 1;
    }
    spin = &m220_prizeTbl[arg0];
    if (spin->unk_00 == 0) {
        goto ret_one;
    }
    if (spin->unk_02 == 0) {
        goto ret_zero;
    }
ret_one:
    return 1;
ret_zero:
    return 0;
}

void m220_PrizeClose(void) {
    SlotSynchPrize *spin = m220_prizeTbl;
    s32 i;
    s32 j;

    if (spin != NULL) {
        for (i = 0; i < 5; i++, spin++) {
            for (j = 0; j < 4; j++) {
                Hu3DData[spin->unk_04[j]].motId = 0xFF;
                Hu3DModelKill(spin->unk_04[j]);
                Hu3DMotionKill(spin->unk_0C[j][0]);
                Hu3DMotionKill(spin->unk_0C[j][1]);
                Hu3DMotionKill(spin->unk_0C[j][2]);
            }
            Hu3DModelKill(spin->unk_24);
        }
        HuMemFree(m220_prizeTbl);
        m220_prizeTbl = NULL;
        m220_prizeObj->func = NULL;
    }
}

u16 m220_SprAnimRead(s32 file) {
    void *data = DataRead(file);
    u16 sprite = HuSprAnimRead(data);

    DataClose(data);
    return sprite;
}

void m220_SprPosSet(s16 arg0, s16 arg1, f32 arg2, f32 arg3) {
    HuSprGrp *grp = HuSprGrpData[arg0];
    HuSprite *spr = HuSprGet(arg0, arg1);

    if (spr->pos.x != arg2 || spr->pos.y != arg3) {
        grp->dirty = 1;
        spr->pos.x = arg2;
        spr->pos.y = arg3;
    }
}

void m220_ScoreInit(void) {
    SlotSynchScore *light;
    s32 i;

    m220_sprTbl[10] = m220_SprAnimRead(0x35000C);
    m220_sprTbl[11] = m220_SprAnimRead(0x35000B);
    m220_sprTbl[12] = m220_SprAnimRead(0x2D);
    light = m220_scoreTbl = HuMemAllocTag(sizeof(SlotSynchScore) * 2, TAG_OVERLAY);
    for (i = 0; i < 2; i++, light++) {
        light->unk_00 = -1;
        light->unk_02 = m220_scorePosTbl[i].x;
        light->unk_04 = m220_scorePosTbl[i].y;
        light->unk_06[0] = 0;
        light->unk_06[1] = 0;
        light->unk_0A = 0;
        light->unk_0C = 0;
        light->unk_0E = 0;
    }
    omAddObj(0x1E, 0, 0, -1, m220_ScoreObjMain);
}

void m220_ScoreChrSet(s16 team, s16 chr0, s16 chr1, s16 arg3) {
    SlotSynchScore *light = &m220_scoreTbl[team];
    s32 group;
    s32 i;

    m220_sprTbl[team * 2 + 13] = m220_SprAnimRead(m220_faceSprTbl[chr0]);
    m220_sprTbl[team * 2 + 14] = m220_SprAnimRead(m220_faceSprTbl[chr1]);
    group = HuSprGrpCreate(6, 0);
    light->unk_00 = group;
    light->unk_06[0] = -8;
    light->unk_06[1] = 8;
    light->unk_0A = light->unk_0C = light->unk_0E = 0;
    m220_ScoreSet(team, arg3);
    for (i = 0; i < 6; i++) {
        switch (i) {
            case 0:
                HuSprAttrSet(group, i, HUSPR_ATTR_DISPOFF);
            case 1:
                HuSprGrpMemberSet(group, i, m220_sprTbl[12], 0);
                HuSprPosSet(group, i, light->unk_02 + light->unk_06[i], light->unk_04);
                break;
            case 2:
                HuSprPosSet(group, i, light->unk_02 - 26, light->unk_04 - 9);
                HuSprGrpMemberSet(group, i, m220_sprTbl[team * 2 + 13], 0);
                break;
            case 3:
                HuSprPosSet(group, i, light->unk_02 - 26, light->unk_04 + 8);
                HuSprGrpMemberSet(group, i, m220_sprTbl[team * 2 + 14], 0);
                break;
            case 4:
                HuSprPosSet(group, i, light->unk_02 + 27, light->unk_04);
                HuSprGrpMemberSet(group, i, m220_sprTbl[11], 0);
                break;
            case 5:
                HuSprPosSet(group, i, light->unk_02, light->unk_04);
                HuSprScaleSet(group, i, 1.0f, 1.0f);
                HuSprColorTPLvlSet(group, i, 0, 0, 255, 160);
                HuSprGrpMemberSet(group, i, m220_sprTbl[10], 0);
                break;
        }
        HuSprAnimModeSet(group, i, HUSPR_ANIM_MODE_STOP);
        HuSprPatNoSet(group, i, 0);
        HuSprAttrSet(group, i, 0x1000);
        HuSprPriSet(group, i, i - 16);
    }
}

void m220_ScoreObjMain(omObjData *object) {
    SlotSynchScore *light = m220_scoreTbl;
    u16 digits[2];
    f32 scale;
    s32 i;

    for (i = 0; i < 2; i++, light++) {
        digits[0] = light->unk_0A / 10;
        digits[1] = light->unk_0A - digits[0] * 10;
        if (digits[0] >= 10) {
            digits[0] = 9;
        }
        if (digits[1] >= 10) {
            digits[1] = 9;
        }
        HuSprPatNoSet(light->unk_00, 0, (s16)digits[0]);
        HuSprPatNoSet(light->unk_00, 1, (s16)digits[1]);
        if (light->unk_0A != light->unk_0C && light->unk_0E == 0) {
            light->unk_0E = 15;
            if (light->unk_0A < light->unk_0C) {
                light->unk_0A++;
            } else {
                light->unk_0A--;
            }
            HuSprAttrSet(light->unk_00, 0, 0x838);
            HuSprAttrSet(light->unk_00, 1, 0x838);
            if (light->unk_0A >= 10) {
                HuSprAttrReset(light->unk_00, 0, HUSPR_ATTR_DISPOFF);
            } else {
                HuSprAttrSet(light->unk_00, 0, HUSPR_ATTR_DISPOFF);
            }
        }
        scale = sindf(light->unk_0E / 15.0f * 180.0f) * 0.5f + 1.0f;
        HuSprPosSet(light->unk_00, 0, light->unk_02 + light->unk_06[0] * scale, light->unk_04);
        HuSprPosSet(light->unk_00, 1, light->unk_02 + light->unk_06[1] * scale, light->unk_04);
        HuSprScaleSet(light->unk_00, 0, scale, scale);
        HuSprScaleSet(light->unk_00, 1, scale, scale);
        if (light->unk_0E != 0 && --light->unk_0E == 0) {
            HuSprAttrReset(light->unk_00, 0, 0x838);
            HuSprAttrReset(light->unk_00, 1, 0x838);
        }
    }
}

void m220_ScoreSet(s16 arg0, s16 arg1) {
    SlotSynchScore *light = &m220_scoreTbl[arg0];

    light->unk_0C = arg1;
}

void m220_SmokeInit(void) {
    HuSprAnimData *sprite;
    SlotSynchEffect *effect;
    HmfModel *model;
    s32 i;

    m220_sprTbl[1] = m220_SprAnimRead(11);
    sprite = HuSprAnimDataGet(m220_sprTbl[1]);
    m220_smokeObj = omAddObj(30, 0, 0, -1, m220_SmokeObjMain);
    m220_smokeTbl = effect = HuMemAllocTag(sizeof(SlotSynchEffect) * 8, TAG_OVERLAY);
    for (i = 0; i < 8; i++, effect++) {
        if (i == 0) {
            effect->model = m220_BillboardColorMdlCreate(sprite, m220_halfWhiteColor.rgba);
        } else {
            effect->model = m220_BillboardColorMdlLink(sprite, m220_smokeTbl[0].model, m220_halfWhiteColor.rgba);
        }
        effect->active = 0;
        effect->color = m220_halfWhiteColor;
        effect->frame = effect->speed = 0.0f;
        effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        effect->scale.x = effect->scale.y = effect->scale.z = 0.0f;
        Hu3DModelAttrSet(effect->model, 4, 4);
        model = &Hu3DData[effect->model];
        model->motTime = 0.0f;
    }
}

void m220_SmokeObjMain(omObjData *object) {
    HuSprAnimData *sprite = HuSprAnimDataGet(m220_sprTbl[1]);
    SlotSynchEffect *effect;
    HmfModel *model;
    s32 i;

    for (i = 0, effect = m220_smokeTbl; i < 8; i++, effect++) {
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
        m220_BillboardColorPatSet(effect->model, sprite, (s32)effect->frame, effect->color.rgba);
        effect->frame += effect->speed;
        if ((s32)effect->frame >= sprite->patNum) {
            effect->active = 0;
            effect->frame = 0.0f;
            model->attr |= 4;
        }
    }
}

s32 m220_SmokeCreate(Vec *pos, Vec *vel, Vec *scale, f32 speed, u8 *color) {
    HuSprAnimData *sprite = HuSprAnimDataGet(m220_sprTbl[1]);
    SlotSynchEffect *effect;
    HmfModel *model;
    s32 i;

    for (i = 0, effect = m220_smokeTbl; i < 8; i++, effect++) {
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
        memcpy(effect->color.rgba, color, sizeof(SlotSynchColor));
        effect->speed = speed;
        effect->frame = 0.0f;
        m220_BillboardColorPatSet(effect->model, sprite, 0, effect->color.rgba);
        Hu3DModelAttrSet(effect->model, 4, 0);
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

void m220_CameraInit(void) {
    HuCamera *camera;
    s32 i;

    Center.x = 0.0f;
    Center.y = 184.8f;
    Center.z = -708.8f;
    CRot.x = 354.505f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2000.0f;
    m220_CameraKeyStore(0);
    m220_CameraKeyStore(1);
    m220_cameraMoveF = 0;
    m220_cameraMoveTime = 0;
    m220_cameraMoveTimer = 0;
    omAddObj(31, 0, 0, -1, m220_CameraMoveObjMain);
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

void m220_CameraDebugPad(void) {
    MgCameraKey delta = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed;

    speed = 1.0f;
    switch (m220_cameraDebugMode) {
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
                m220_CameraMoveStart(delta.center.x, delta.center.y, delta.center.z, delta.rot.x,
                                         delta.rot.y, delta.rot.z, delta.zoom, 1);
            }
            sprintf(omDBGStrBuf, "CAMERA TEST_MODE");
            print8((s16)m220_cameraDebugX + 20, (s16)m220_cameraDebugY + 80,
                   omDBGStrBuf);
            sprintf(omDBGStrBuf, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((s16)m220_cameraDebugX + 20, (s16)m220_cameraDebugY + 88,
                   omDBGStrBuf);
            sprintf(omDBGStrBuf, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((s16)m220_cameraDebugX + 20, (s16)m220_cameraDebugY + 96,
                   omDBGStrBuf);
            sprintf(omDBGStrBuf, " ZOOM   %3.3f ", CZoom);
            print8((s16)m220_cameraDebugX + 20, (s16)m220_cameraDebugY + 104,
                   omDBGStrBuf);
            break;
        case 2:
            if ((HuPadBtn[0] & R_JPAD) || (HuPadBtn[0] & R_CBUTTONS)) {
                m220_cameraDebugX++;
            }
            if (HuPadBtn[0] & (L_JPAD | L_CBUTTONS)) {
                m220_cameraDebugX--;
            }
            if (HuPadBtn[0] & (D_JPAD | D_CBUTTONS)) {
                m220_cameraDebugY++;
            }
            if (HuPadBtn[0] & (U_JPAD | U_CBUTTONS)) {
                m220_cameraDebugY--;
            }
            fontcolor = 8;
            sprintf(omDBGStrBuf, "CAMERA TEST_MODE ");
            print8((s16)m220_cameraDebugX + 20, (s16)m220_cameraDebugY + 80,
                   omDBGStrBuf);
            sprintf(omDBGStrBuf, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((s16)m220_cameraDebugX + 20, (s16)m220_cameraDebugY + 88,
                   omDBGStrBuf);
            sprintf(omDBGStrBuf, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((s16)m220_cameraDebugX + 20, (s16)m220_cameraDebugY + 96,
                   omDBGStrBuf);
            sprintf(omDBGStrBuf, " ZOOM   %3.3f ", CZoom);
            print8((s16)m220_cameraDebugX + 20, (s16)m220_cameraDebugY + 104,
                   omDBGStrBuf);
            break;
        case 3:
            m220_cameraDebugMode = 0;
            break;
    }
    if (HuPadBtnDown[0] & R_TRIG) {
        if (m220_cameraDebugMode == 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (m220_cameraDebugMode++ >= 4) {
            m220_cameraDebugMode = 0;
        }
    }
}

void m220_CameraMoveObjMain(omObjData *object) {
    f32 t;

    if (m220_cameraMoveTime <= 0) {
        m220_CameraPosUpdate(0);
        m220_cameraMoveF = 0;
        return;
    }
    if (m220_cameraMoveTimer == 0) {
        Center.x = m220_cameraKeyTbl[0].center.x;
        Center.y = m220_cameraKeyTbl[0].center.y;
        Center.z = m220_cameraKeyTbl[0].center.z;
        CRot.x = m220_cameraKeyTbl[0].rot.x;
        CRot.y = m220_cameraKeyTbl[0].rot.y;
        CRot.z = m220_cameraKeyTbl[0].rot.z;
        CZoom = m220_cameraKeyTbl[0].zoom;
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
        m220_cameraMoveTime = 0;
    } else {
        t = (f32)m220_cameraMoveTimer / (f32)m220_cameraMoveTime;
        Center.x = m220_InterpCalc(t, m220_cameraKeyTbl[0].center.x,
                                            m220_cameraKeyTbl[1].center.x);
        Center.y = m220_InterpCalc(t, m220_cameraKeyTbl[0].center.y,
                                            m220_cameraKeyTbl[1].center.y);
        Center.z = m220_InterpCalc(t, m220_cameraKeyTbl[0].center.z,
                                            m220_cameraKeyTbl[1].center.z);
        CRot.x = m220_AngleInterpCalc(t, m220_cameraKeyTbl[0].rot.x,
                                          m220_cameraKeyTbl[1].rot.x);
        CRot.y = m220_AngleInterpCalc(t, m220_cameraKeyTbl[0].rot.y,
                                          m220_cameraKeyTbl[1].rot.y);
        CRot.z = m220_AngleInterpCalc(t, m220_cameraKeyTbl[0].rot.z,
                                          m220_cameraKeyTbl[1].rot.z);
        CZoom = m220_InterpCalc(t, m220_cameraKeyTbl[0].zoom,
                                         m220_cameraKeyTbl[1].zoom);
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
        if (m220_cameraMoveTimer > 0) {
            m220_cameraMoveTimer--;
        } else {
            m220_cameraMoveTimer++;
        }
    }
    m220_cameraMoveF = 1;
    m220_CameraPosUpdate(0);
}

void m220_CameraKeyStore(s32 arg0) {
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
    m220_cameraKeyTbl[arg0].center.x = Center.x;
    m220_cameraKeyTbl[arg0].center.y = Center.y;
    m220_cameraKeyTbl[arg0].center.z = Center.z;
    m220_cameraKeyTbl[arg0].rot.x = CRot.x;
    m220_cameraKeyTbl[arg0].rot.y = CRot.y;
    m220_cameraKeyTbl[arg0].rot.z = CRot.z;
    m220_cameraKeyTbl[arg0].zoom = CZoom;
    m220_cameraKeyTbl[arg0].unk_1C = m220_cameraKeyTbl[arg0].unk_20 = 0.0f;
}

// Passing CAMERA_KEEP for a component keeps its current value.
void m220_CameraMoveStart(f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames) {
    if (frames > 0) {
        m220_cameraMoveTimer = frames - 1;
        m220_cameraMoveTime = frames;
        if (x != CAMERA_KEEP) {
            m220_cameraKeyTbl[0].center.x = x;
        } else {
            m220_cameraKeyTbl[0].center.x = Center.x;
        }
        if (y != CAMERA_KEEP) {
            m220_cameraKeyTbl[0].center.y = y;
        } else {
            m220_cameraKeyTbl[0].center.y = Center.y;
        }
        if (z != CAMERA_KEEP) {
            m220_cameraKeyTbl[0].center.z = z;
        } else {
            m220_cameraKeyTbl[0].center.z = Center.z;
        }
        if (rotX != CAMERA_KEEP) {
            m220_cameraKeyTbl[0].rot.x = rotX;
        } else {
            m220_cameraKeyTbl[0].rot.x = CRot.x;
        }
        if (rotY != CAMERA_KEEP) {
            m220_cameraKeyTbl[0].rot.y = rotY;
        } else {
            m220_cameraKeyTbl[0].rot.y = CRot.y;
        }
        if (rotZ != CAMERA_KEEP) {
            m220_cameraKeyTbl[0].rot.z = rotZ;
        } else {
            m220_cameraKeyTbl[0].rot.z = CRot.z;
        }
        if (zoom != CAMERA_KEEP) {
            m220_cameraKeyTbl[0].zoom = zoom;
        } else {
            m220_cameraKeyTbl[0].zoom = CZoom;
        }
        m220_CameraKeyStore(1);
    }
}

void m220_CameraPosUpdate(s32 camIndex) {
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

f32 m220_AngleDiffCalc(f32 arg0, f32 arg1) {
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

f32 m220_AngleStepCalc(f32 target, f32 current, f32 step) {
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

f32 m220_InterpCalc(f32 t, f32 start, f32 end) {
    return start + t * (end - start);
}

f32 m220_AngleInterpCalc(f32 arg0, f32 arg1, f32 arg2) {
    return m220_AngleStepCalc(arg2, arg1, fabsf(m220_AngleDiffCalc(arg2, arg1) * arg0));
}

void m220_WorkPtrSet(omObjData *arg0, u32 arg1) {
    arg0->work[0] = arg1 >> 24;
    arg0->work[1] = (arg1 >> 16) & 0xFF;
    arg0->work[2] = (arg1 >> 8) & 0xFF;
    arg0->work[3] = arg1 & 0xFF;
}

u32 m220_WorkPtrGet(omObjData *arg0) {
    SlotSynchWorkBytes packed;

    packed.bytes.byte3 = (u8)arg0->work[0];
    packed.bytes.byte2 = (u8)arg0->work[1];
    packed.bytes.byte1 = (u8)arg0->work[2];
    packed.bytes.byte0 = (u8)arg0->work[3];
    return packed.word;
}

s16 m220_MotCreate(s32 file) {
    s16 motion = Hu3DMotionCreate(DataRead(file), 0x18);

    if (motion >= 0) {
        return motion;
    }
    return -1;
}

s32 m220_BillboardColorMdlCreate(HuSprAnimData *sprite, u8 *color) {
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
    m220_BillboardVtxCreate(sprite, data, 1.0f, 0, 0);
    gSPDisplayList(header, osVirtualToPhysical(m220_gfxBillboardInit));
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
    gDPSetRenderMode(gfx++, G_RM_ZB_CLD_SURF, G_RM_NOOP2);
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

s32 m220_BillboardColorMdlLink(HuSprAnimData *sprite, u16 model, u8 *color) {
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

void m220_BillboardColorPatSet(u16 model, HuSprAnimData *sprite, u16 frame, u8 *color) {
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

s32 m220_BillboardVtxCreate(HuSprAnimData *sprite, HmfData *data, f32 scale, s16 xOffset, s16 yOffset) {
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
