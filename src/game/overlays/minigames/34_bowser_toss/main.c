#include "common.h"
#include "gcc/memory.h"
#include "game/hmfmath.h"
#include "game/mallocblock.h"
#include "math.h"
#include "game/overlays/minigame.h"
#include "game/overlays/mgcamera.h"

typedef struct BowserTossKoopa { // 0x64 bytes, two entries
    omObjData *unk_00;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    s16 unk_20;
    s16 unk_22;
    s16 unk_24;
    char unk_26[2];
    f32 unk_28;
    f32 unk_2C;
    f32 unk_30;
    f32 unk_34;
    f32 unk_38;
    f32 unk_3C;
    f32 unk_40;
    f32 unk_44; // roll
    f32 unk_48;
    f32 unk_4C;
    s32 unk_50;
    char unk_54[8];
    struct BowserTossHookBake *unk_5C;
    f32 (*unk_60)[16]; // per-frame matrices
} BowserTossKoopa;

// Per-player slot of the array allocated in m252_PlayerObjCreateAll
typedef struct BowserTossPlayer { // 0x5C bytes, two entries
    s16 index;                    // player index
    s16 unk_02;
    f32 unk_04; // score
    s32 unk_08;
    s16 unk_0C; // state, 5 when finished
    s16 unk_0E;
    s16 unk_10;
    char unk_12[2];
    s32 unk_14;
    s16 unk_18; // GwPlayer index
    s16 unk_1A; // pad
    s16 unk_1C; // chr
    s16 unk_1E; // cpu flag
    s16 unk_20; // cpu difficulty
    char unk_22[2];
    f32 unk_24;
    f32 unk_28;
    f32 unk_2C;
    s16 unk_30;
    s16 unk_32;
    f32 unk_34;
    f32 unk_38;
    s16 unk_3C;
    char unk_3E[2];
    s32 unk_40;
    f32 unk_44;
    f32 unk_48;
    s16 unk_4C;
    char unk_4E[2];
    s32 unk_50;
    f32 unk_54;
    f32 unk_58;
} BowserTossPlayer;

// Per-player slot of the array allocated in m252_ScoreInit
typedef struct BowserTossScore { // 0x10 bytes, three entries
    s16 spriteId;                 // HuSprGrpCreate handle
    s16 timer;
    s16 state; // toss state, 0x20 once the toss has finished
    char unk_06[2];
    s32 unk_08;
    s32 unk_0C;
} BowserTossScore;

// Item data block returned by m252_HookMtxBake
typedef struct BowserTossHookBake { // 0xC bytes
    s16 frames;                 // motion length
    s16 step;                   // frames between baked matrices
    s16 *nodes;
    HuMtx4F *mtx; // baked hook matrix per sampled frame
} BowserTossHookBake;

// Entry of the array allocated in m252_SmokeInit
typedef struct BowserTossSmoke { // 0x30 bytes, 32 entries
    u16 unk_00;                   // active
    s16 unk_02;                   // model
    f32 unk_04;
    f32 unk_08;
    Vec unk_0C;
    Vec unk_18;
    Vec unk_24;
} BowserTossSmoke;

// Per-camera interpolation state allocated in m252_CameraInit
typedef struct BowserTossCamera { // 0x54 bytes, two entries
    MgCameraKey keys[2];          // target, origin
    s32 frame;                    // frames remaining
    s32 frames;                   // total frames
    s32 active;
} BowserTossCamera;

typedef struct BowserTossScissor {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} BowserTossScissor;

typedef struct BowserTossSprPos {
    s16 x;
    s16 y;
} BowserTossSprPos;

// Background sprite frame table entry
typedef struct BowserTossScrollFrame {
    s16 sprite; // index into m252_sprTbl
    s16 frame;
} BowserTossScrollFrame;

typedef union BowserTossWorkBytes { // packs the low byte of each work word
    u32 word;
    struct {
        u32 byte3 : 8;
        u32 byte2 : 8;
        u32 byte1 : 8;
        u32 byte0 : 8;
    } bytes;
} BowserTossWorkBytes;

extern s32 omCharModelNoTbl[][6];
extern s8 HuPadStkY[];
extern u16 HuPadBtnDown[];
extern s16 HuPadBtn[];
extern const s16 m252_startMesTbl[];
extern const s16 m252_finishMesTbl[];
extern s16 Hu3DModelTag;
extern s16 motionBakeMtxCnt;
extern u8 Hu3DBufNo;
extern s16 *motionBakeNodeMap;
extern HuMtx4F *motionBakeMtx;
extern s16 Hu3DObjMtxStackIdx;
extern HuMtx4F Hu3DObjMtxStack[];

u8 m252_smokeColor[4] = { 0xE9, 0xDD, 0xA1, 0x80 };                                                                          // RGBA
s32 m252_winAnimTbl[8] = { 0x000200A5, 0x000300A5, 0x000700A5, 0x000400A5, 0x000500A5, 0x000600A5, 0x000800A5, 0x0009001C }; // per-character
s32 m252_loseAnimTbl[8] = { 0x000200A6, 0x000300A6, 0x000700A6, 0x000400A6, 0x000500A6, 0x000600A6, 0x000800A6, 0x0009001D }; // per-character
s32 m252_exitTimer = 0;
Vec m252_playerPosTbl[2] = {
    { -0.0f, 100.0f, 0.0f },
    { 0.0f, 100.0f, 0.0f }
};
s32 m252_playerOrderTbl[4] = { 0, 1, 2, 3 };
s32 m252_voiceChrTbl[8] = { 0x00020000, 0x00030000, 0x00070000, 0x00040000, 0x00050000, 0x00060000, 0x00080000, 0x00090000 };
f32 m252_spinSpeedMinTbl[8] = { 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f };
f32 m252_spinSpeedMaxTbl[8] = { 23.0f, 23.0f, 23.0f, 23.0f, 23.0f, 23.0f, 23.0f, 23.0f };
s32 m252_voiceNoTbl[2] = { 0x2F, 0x30 };
s32 m252_loseMotNoTbl[2] = { 0x36, 0x37 };
f32 m252_comPowerTbl[4] = { 0.4f, 0.55f, 0.45f, 0.5f };
f32 m252_comPowerRandTbl[4] = { 0.1f, 0.2f, 0.2f, 0.2f };
f32 m252_comScaleTbl[4] = { 0.5f, 0.6f, 0.7f, 0.8f };
f32 m252_comDistTbl[4] = { 2000.0f, 4000.0f, 5500.0f, 7000.0f };
f32 m252_throwStartPos[2] = { 0.0f, 200.0f };
Vec m252_decoPosTbl[14] = {
    { 0.0f, 0.0f, 0.0f },
    { 955.69507f, 0.0f, 0.0f },
    { 1660.1975f, 0.0f, 0.0f },
    { 2364.7f, 0.0f, 0.0f },
    { 3069.2024f, 0.0f, 0.0f },
    { 100.0f, 0.0f, 0.0f },
    { 200.0f, 0.0f, 0.0f },
    { 300.0f, 0.0f, 0.0f },
    { 400.0f, 0.0f, 0.0f },
    { 100.0f, 0.0f, 0.0f },
    { 200.0f, 0.0f, 0.0f },
    { 300.0f, 0.0f, 0.0f },
    { 400.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }
};
u8 m252_decoColor[4] = { 0xFF, 0xFF, 0xFF, 0xFF }; // RGBA
s16 m252_decoSwapTbl[2][5] = {
    { 0, 1, 2, 3, 4 },
    { 1, 2, 3, 4, 0 }
};
u8 m252_decoAnimColor[4] = { 0xFF, 0xFF, 0xFF, 0xFF }; // RGBA
BowserTossScissor m252_backScissorTbl[2] = {
    { 0, 0, 320, 120 },
    { 0, 120, 320, 240 }
};
f32 m252_backScrollScale = 10.0f;
BowserTossScrollFrame m252_backFrameTbl[10] = {
    { 1, 1 }, { 1, 0 }, { 2, 1 }, { 2, 0 }, { 3, 1 }, { 3, 0 }, { 3, 1 }, { 3, 0 }, { 3, 1 }, { 3, 0 }
};
BowserTossSprPos m252_scoreDigitPosTbl[3][8] = { // score sprite positions per counter
                                                  { { 136, 60 }, { 148, 60 }, { 168, 60 }, { 180, 60 }, { 160, 60 }, { 196, 60 }, { 160, 60 }, { 124, 60 } },
                                                  { { 136, 180 }, { 148, 180 }, { 168, 180 }, { 180, 180 }, { 160, 180 }, { 196, 180 }, { 160, 180 }, { 124, 180 } },
                                                  { { 56, 25 }, { 68, 25 }, { 88, 25 }, { 100, 25 }, { 80, 24 }, { 116, 24 }, { 80, 25 }, { 44, 25 } }
};
s32 m252_digitDivTbl[5] = { 10000, 1000, 100, 10, 1 }; // decimal place divisors
s32 m252_cameraDebugMode = 0;                              // camera test mode
s32 m252_cameraDebugNo = 0;                              // camera test mode camera index
s32 m252_cameraDebugX = 0;                              // camera test mode text x offset
s32 m252_cameraDebugY = 0;                              // camera test mode text y offset

Gfx m252_gfxRdpInit[] = {
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
Gfx m252_gfxRspInit[] = {
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
Gfx m252_gfxInit[] = {
    gsSPDisplayList(m252_gfxRspInit),
    gsSPDisplayList(m252_gfxRdpInit),
    gsSPEndDisplayList(),
};
Gfx m252_gfxBillboardInit[] = {
    gsDPPipeSync(),
    gsSPDisplayList(m252_gfxInit),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPSetGeometryMode(G_ZBUFFER | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x00),
    gsDPSetPrimColor(0, 0, 0x00, 0x00, 0x00, 0xFF),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

omObjData *m252_mainObj BSS;
s32 m252_flag10F BSS;
s32 m252_frameCnt BSS;
s32 m252_phaseTimer BSS;
s32 m252_timer BSS;
s32 m252_phase BSS;
s32 m252_resultWait BSS;
s32 m252_unusedTimer BSS;
s16 m252_scoreSeNo BSS;
s16 m252_newRecordF BSS;
BowserTossPlayer *m252_playerWorkTbl BSS;
s16 m252_winnerNo BSS;
s32 m252_winDist BSS;
s32 m252_recordDist BSS;
s32 m252_spinSeNo BSS;
omObjData *m252_koopaObj BSS;
BowserTossKoopa *m252_koopaTbl BSS;
omObjData *m252_smokeObj BSS;
BowserTossSmoke *m252_smokeTbl BSS;
s16 *m252_sprTbl BSS;
s16 m252_backGrpTbl[2] BSS;
BowserTossScore *m252_scoreTbl BSS;
BowserTossCamera *m252_cameraMoveTbl BSS;
Vec m252_cameraCenterMin BSS;
u8 m252_cameraCenterMinPad[4] BSS; /* Unreferenced. */
MinigameFlow m252_mgFlow BSS;

void m252_MainObjInit(omObjData *object);
void m252_MainObjMain(omObjData *object);
void m252_PlayerObjCreateAll(void);
void m252_KoopaInit(void);
void m252_SmokeInit(void);
void m252_StageObjCreate(void);
void m252_BackInit(void);
void m252_ScoreInit(void);
void m252_CameraInit(void);
void m252_ScoreObjMain(omObjData *object);
void m252_CameraMoveObjMain(omObjData *object);
void m252_CameraKeyStore(s32 camIndex, s32 key);
f32 m252_InterpCalc(f32 t, f32 start, f32 end);
f32 m252_AngleInterpCalc(f32 t, f32 start, f32 end);
f32 m252_AngleDiffCalc(f32 arg0, f32 arg1);
f32 m252_AngleStepCalc(f32 target, f32 current, f32 step);
void m252_CameraPosUpdate(s32 camIndex);
void m252_StageObjInit(omObjData *object);
void m252_ExitObjMain(omObjData *object);
void m252_ExitCheck(omObjData *object);
void m252_PlayerObjInit(omObjData *object);
s16 m252_PlayerAllThrownCheck(void);
s16 m252_PlayerAllEndCheck(void);
void m252_PlayerMdlSwap(omObjData *object, s16 arg1, s16 arg2);
s16 m252_KoopaAllLandCheck(void);
void m252_ScoreSet(s16 index, s32 score);
s16 m252_ScoreAllCountCheck(void);
void m252_ScoreAllEndStart(void);
s16 m252_ScoreAllEndCheck(void);
void m252_CameraMoveStart(s32 camIndex, f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom,
                               s32 frames);
void m252_WorkPtrSet(omObjData *obj, u32 arg1);
void m252_PlayerObjMain(omObjData *object);
void m252_KoopaCreate(s16 arg0);
BowserTossKoopa *m252_KoopaGet(s16 arg0);
f32 m252_ComPowerCalc(f32 arg0, f32 arg1, f32 arg2);
void m252_KoopaObjMain(omObjData *object);
struct BowserTossHookBake *m252_HookMtxBake(s16 model, s16 step, const char *hookName, s16 shape, s16 frame);
void m252_HookMtxBakeNode(s16 model, s16 step, struct BowserTossHookBake *item, s16 node, s16 shape, s16 frame);
void m252_HookMtxFree(struct BowserTossHookBake *item);
void m252_MtxInterpCalc(f32 *arg0, f32 *arg1, f32 *arg2, f32 arg3);
void m252_SmokeObjMain(omObjData *object);
void m252_StageObjMain(omObjData *object);
void m252_BackScrollSet(s16 camera, Vec *pos, Vec *rot);
u16 m252_SprAnimRead(s32 dirAndFile);
s32 m252_BillboardColorMdlCreate(HuSprAnimData *sprite, u8 *color, u8 antialias);
s32 m252_BillboardColorMdlLink(HuSprAnimData *sprite, u16 model, u8 *color);
s32 m252_BillboardVtxCreate(HuSprAnimData *sprite, HmfData *data, f32 scale, s16 xOffset, s16 yOffset);
void m252_PlayerComInput(omObjData *object);
void m252_ObjMtxCalc(omObjData *object, f32 angle, HuMtx4F mtx);
void m252_KoopaHookMtxGet(BowserTossKoopa *bowser, f32 *out, f32 time);
s16 m252_FallTimeCalc(f32 x, f32 y, f32 velX, f32 velY);
s32 m252_SmokeCreate(Vec *pos, Vec *vel, Vec *scale, f32 speed, s16 camera);
void m252_BillboardColorPatSet(u16 model, HuSprAnimData *sprite, u16 frame, u8 *color);
BowserTossPlayer *m252_WorkPtrGet(omObjData *object);

void m252_ObjectSetup(void) {
    omObjData *obj;
    s32 i;

    MapCollInit(50);
    omInitObjMan(50, 0);
    omGameSysInit();
    Hu3DSprModelInit(16);
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    obj->work[0] = 2;
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -56.0f, 50.0f, 56.0f);
    CamSetupInit(2);
    CamSetupMapCullAddMulti(2);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 120.0f);
    ScissorSet(1, 0.0f, 121.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 240.0f, 511.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 640.0f, 720.0f, 511.0f);
    for (i = 0; i < 2; i++) {
        Hu3DCameraPerspectiveSet(i, 45.0f, 80.0f, 4000.0f);
    }
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    mgItemObjNum = 0;
    m252_timer = 300;
    m252_phaseTimer = 0;
    m252_frameCnt = 0;
    m252_phase = 0;
    m252_resultWait = 0;
    m252_unusedTimer = 0;
    m252_winnerNo = -1;
    m252_winDist = 0;
    m252_scoreSeNo = -1;
    m252_spinSeNo = -1;
    m252_recordDist = GWMgRecordGet(4);
    m252_newRecordF = 0;
    m252_mainObj = omAddObj(0x40, 0, 0, -1, m252_MainObjInit);
    memset(&m252_mgFlow, 0, 0x28);
    m252_mgFlow.type = MINIGAME_BATTLE;
    MgFlowInit(&m252_mgFlow);
    m252_sprTbl = HuMemAllocTag(0x20, TAG_OVERLAY);
    memset(m252_sprTbl, 0, 0x20);
    GMesFontMesCreate(m252_startMesTbl, 1);
    GMesFontMesCreate(m252_finishMesTbl, 1);
}

void m252_MainObjInit(omObjData *object) {
    object->func = m252_MainObjMain;
    m252_BackInit();
    m252_ScoreInit();
    m252_SmokeInit();
    m252_StageObjCreate();
    m252_KoopaInit();
    m252_PlayerObjCreateAll();
    m252_CameraInit();
    if (_CheckFlag(10)) {
        m252_flag10F = 1;
    }
}

const s16 m252_startMesTbl[] = { 0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0 };

const s16 m252_finishMesTbl[] = { 0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0 };

void m252_MainObjMain(omObjData *object) {
    BowserTossPlayer *player1;
    BowserTossPlayer *player2;
    BowserTossKoopa *bowser;
    omObjData *obj;
    s32 score1;
    s32 score2;
    f32 x;
    f32 y;
    f32 zoom;

    switch (m252_phase) {
        case 0:
            if (m252_phaseTimer == 2) {
                WipeCreateIn(WIPE_TYPE_PREV, 16);
            }
            if (m252_resultWait > 0) {
                m252_resultWait = 0;
                m252_phase++;
            }
            break;
        case 1:
            GMesCreate(6);
            HuAudFXPlay(0xE);
            HuAudSeqPlay(0x30);
            m252_resultWait = 0;
            m252_phase++;
            break;
        case 2:
            if (GMesStatGet() == 0) {
                GMesCreate(0x1A, (m252_timer + 29) / 30, 156, 32);
                MgFlowStatSet(MG_STATE_PLAY);
                m252_phase++;
            }
            break;
        case 3:
            m252_timer--;
            GMesTimerValueSet((m252_timer + 29) / 30);
            if (m252_timer <= 0) {
                player1 = m252_WorkPtrGet(mgPlayerObjTbl[0]);
                player2 = m252_WorkPtrGet(mgPlayerObjTbl[1]);
                player2->unk_0C = player1->unk_0C = 3;
                GMesTimerEnd();
                m252_phaseTimer = 0;
                m252_phase++;
            }
            break;
        case 4:
            if (m252_KoopaAllLandCheck() && m252_PlayerAllThrownCheck()) {
                GMesCreate(0x11);
                MgFlowStatSet(MG_STATE_FINISH);
                HuAudSeqFadeOut(120);
                m252_PlayerMdlSwap(mgPlayerObjTbl[0], 0, 10);
                m252_PlayerMdlSwap(mgPlayerObjTbl[1], 0, 10);
                m252_phaseTimer = 0;
                m252_phase++;
            }
            break;
        case 5:
            if (GMesStatGet() == 0) {
                m252_phaseTimer = 0;
                m252_phase++;
            }
            break;
        case 6:
            if (m252_phaseTimer >= 15) {
                player1 = m252_WorkPtrGet(mgPlayerObjTbl[0]);
                player2 = m252_WorkPtrGet(mgPlayerObjTbl[1]);
                score1 = player1->unk_04;
                score2 = player2->unk_04;
                if (player1->unk_04 == 0.0f && player2->unk_04 == 0.0f) {
                    m252_winnerNo = -1;
                    m252_winDist = -1;
                    player2->unk_02 = 1;
                    player1->unk_02 = 1;
                } else if (score1 == score2) {
                    if (rand8() & 1) {
                        score1++;
                        player1->unk_04 += 1.0f;
                    } else {
                        score2++;
                        player2->unk_04 += 1.0f;
                    }
                }
                if (score1 > score2) {
                    m252_winnerNo = player1->index;
                    GwPlayer[player1->unk_18].bonusCoin += 10;
                    player1->unk_02 = 0;
                    player2->unk_02 = 1;
                    m252_winDist = score1;
                } else if (score2 > score1) {
                    m252_winnerNo = player2->index;
                    GwPlayer[player2->unk_18].bonusCoin += 10;
                    player1->unk_02 = 1;
                    player2->unk_02 = 0;
                    m252_winDist = score2;
                }
                m252_ScoreSet(player1->index, score1);
                m252_ScoreSet(player2->index, score2);
                m252_phaseTimer = 0;
                m252_phase++;
            }
            break;
        case 7:
            if (m252_ScoreAllCountCheck()) {
                if (m252_scoreSeNo != -1) {
                    HuAudFXPlay(0x4AC);
                    m252_scoreSeNo = -1;
                }
                m252_ScoreAllEndStart();
                m252_phaseTimer = 0;
                m252_phase++;
            }
            break;
        case 8:
            if (m252_PlayerAllEndCheck() && m252_ScoreAllEndCheck()) {
                if (m252_winnerNo == -1) {
                    GMesCreate(0x20);
                    HuAudSeqPlay(0x6C);
                    m252_resultWait = 144;
                    MgFlowStatSet(MG_STATE_RESULT);
                    m252_phase = 11;
                } else {
                    if (m252_winnerNo != 0) {
                        m252_winnerNo = 1;
                    }
                    if (m252_recordDist < m252_winDist) {
                        m252_recordDist = m252_winDist;
                        m252_ScoreSet(2, m252_winDist);
                        GWMgRecordSet(4, (u16)m252_recordDist);
                        GMesCreate(0x1B);
                        m252_newRecordF = 1;
                        m252_resultWait = 99;
                        m252_phase = 9;
                    } else {
                        HuAudSeqPlay(0x67);
                        m252_resultWait = 140;
                        m252_phase = 10;
                    }
                    obj = mgPlayerObjTbl[m252_winnerNo];
                    bowser = &m252_koopaTbl[m252_winnerNo];
                    m252_WorkPtrGet(obj);
                    x = obj->trans.x * 0.5f + bowser->unk_30 * 0.5f;
                    if (obj->trans.x != 0.0f) {
                        y = obj->trans.y * 0.5f + 100.0;
                    } else {
                        y = obj->trans.y * 0.5f + 150.0;
                    }
                    zoom = CZoom * 0.5f;
                    if (m252_winnerNo == 1) {
                        y -= 15.000000596046448;
                    }
                    m252_CameraMoveStart(m252_winnerNo, x, y, CAMERA_KEEP, CAMERA_KEEP, CAMERA_KEEP,
                                              CAMERA_KEEP, zoom, 30);
                    MgFlowStatSet(MG_STATE_RESULT);
                }
                m252_phaseTimer = 0;
            }
            break;
        case 9:
            if (m252_phaseTimer >= 75.0f) {
                m252_phase = 10;
                m252_phaseTimer = 0;
            }
            break;
        case 10:
            GMesCreate(0x16, m252_WorkPtrGet(mgPlayerObjTbl[m252_winnerNo])->unk_1C);
            if (m252_newRecordF != 0) {
                HuAudSeqPlay(0x6A);
            }
            m252_phaseTimer = 0;
            m252_phase++;
            break;
        case 11:
            if (GMesStatGet() == 0) {
                m252_phaseTimer = 0;
                m252_phase++;
            }
            break;
        case 12:
            if (m252_phaseTimer >= 15) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 16);
                HuAudSeqFadeOut(16);
                HuAudFXAllFadeOut(16);
                m252_phaseTimer = 0;
                m252_phase++;
            }
            break;
        default:
            if (WipeStatGet() == 0) {
                object->func = m252_ExitObjMain;
            }
            break;
    }
    m252_ExitCheck(object);
    m252_frameCnt++;
    m252_phaseTimer++;
}

void m252_ExitObjMain(omObjData *object) {
    HuAudSeqStop();
    omOvlReturnEx(1);
}

void m252_ExitCheck(omObjData *object) {
    if (m252_exitTimer != 0) {
        if (m252_exitTimer == 1) {
            object->func = m252_ExitObjMain;
        }
        m252_exitTimer--;
    } else if (omSysExitReq == 1 && WipeStatGet() == 0) {
        m252_exitTimer = 16;
        WipeCreateOut(WIPE_TYPE_NORMAL, (s16)m252_exitTimer);
        HuAudSeqFadeOut((s16)m252_exitTimer);
        HuAudFXAllFadeOut((s16)m252_exitTimer);
    }
}

void m252_PlayerObjCreateAll(void) {
    s32 used[2];
    BowserTossPlayer *player;
    s32 i;
    s32 j;
    s32 k;
    s32 found;
    s32 minGroup;

    used[0] = -1;
    used[1] = -1;
    player = m252_playerWorkTbl = HuMemAllocTag(sizeof(BowserTossPlayer) * 2, TAG_OVERLAY);
    memset(player, 0, sizeof(BowserTossPlayer) * 2);
    for (i = 0; i < 2; i++) {
        for (j = 0, minGroup = 99; j < 4; j++) {
            found = 0;
            for (k = 0; k < i; k++) {
                if (used[k] == m252_playerOrderTbl[j]) {
                    found = 1;
                }
            }
            if (!found && GwPlayer[m252_playerOrderTbl[j]].group < minGroup) {
                minGroup = GwPlayer[m252_playerOrderTbl[j]].group;
                m252_playerWorkTbl[i].unk_18 = m252_playerOrderTbl[j];
            }
        }
        used[i] = m252_playerWorkTbl[i].unk_18;
    }
    MgShadowAltSet(1);
    MgPlayerParamReset();
    for (i = 0; i < 2; i++, player++) {
        player->index = i;
        mgPlayerObjTbl[mgPlayerObjNum] = omAddObj(i + 16, 11, 60, -1, m252_PlayerObjInit);
        mgPlayerObjTbl[mgPlayerObjNum]->trans.x = m252_playerPosTbl[i].x;
        mgPlayerObjTbl[mgPlayerObjNum]->trans.y = m252_playerPosTbl[i].y;
        mgPlayerObjTbl[mgPlayerObjNum]->trans.z = m252_playerPosTbl[i].z;
        mgPlayerObjTbl[mgPlayerObjNum]->rot.y = 90.0f;
        m252_WorkPtrSet(mgPlayerObjTbl[mgPlayerObjNum], (u32)player);
        mgPlayerObjNum++;
    }
}

void m252_PlayerObjInit(omObjData *object) {
    BowserTossPlayer *player;
    MgPlayerWork *data;
    s32 variant;
    s16 gwIndex;
    s16 chr;
    u32 model;
    s32 motionFile;
    s32 linkModel;
    f32 zero;

    player = m252_WorkPtrGet(object);
    gwIndex = player->unk_18;
    chr = GwPlayer[gwIndex].chr;
    player->unk_1C = chr;
    player->unk_1A = GwPlayer[gwIndex].pad;
    player->unk_1E = GwPlayer[gwIndex].stat & 1;
    player->unk_20 = GwPlayer[gwIndex].cpu_difficulty;
    model = omCharModelNoTbl[chr][0];
    motionFile = omCharModelNoTbl[chr][1];
    linkModel = omCharModelNoTbl[chr][2];
    MgPlayerCreate(object, model, motionFile, gwIndex, 0x289, 0x299);
    data = object->data;
    data->unk50 &= ~1;
    data->unkEC = 0;
    object->model[3] = Hu3DModelRead(3, 0x68D);
    object->model[4] = Hu3DModelRead(4, 0x68D);
    object->model[10] = Hu3DModelRead(model | linkModel, 0x2AD);
    Hu3DModelCameraSet(object->model[0], 1 << player->index);
    Hu3DModelCameraSet(object->model[1], 1 << player->index);
    Hu3DModelCameraSet(object->model[10], 1 << player->index);
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(chr, 0), 1, 0);
    MgPlayerMotLoad(object, 3, CharMotionDataNumGet(chr, 4), 1, 0x13);
    MgPlayerMotLoad(object, 4, CharMotionDataNumGet(chr, 0x6D), 1, 0);
    MgPlayerMotLoad(object, 5, CharMotionDataNumGet(chr, 0x64), 1, 0);
    MgPlayerMotLoad(object, 6, CharMotionDataNumGet(chr, 0x65), 1, 30);
    variant = rand8() & 1;
    MgPlayerMotLoad(object, 7, CharMotionDataNumGet(chr, m252_voiceNoTbl[variant]), 1, 120);
    player->unk_14 = m252_voiceChrTbl[chr] | m252_voiceNoTbl[variant];
    MgPlayerMotLoad(object, 8, CharMotionDataNumGet(chr, m252_loseMotNoTbl[rand8() & 1]), 1, 120);
    MgPlayerMotSet(object, 5);
    Hu3DData[object->model[0]].motId = object->motion[5];
    Hu3DMotionShapeSet(object->model[0], object->motion[6], 1);
    Hu3DData[object->model[0]].motShapeSpeed = 0.0f;
    Hu3DData[object->model[0]].motShapeTime = 0.0f;
    player->unk_24 = m252_spinSpeedMinTbl[chr];
    player->unk_28 = m252_spinSpeedMaxTbl[chr];
    player->unk_2C = player->unk_28 - player->unk_24;
    player->unk_30 = player->unk_32 = 0;
    player->unk_3C = 1;
    player->unk_40 = 0;
    player->unk_44 = 0;
    player->unk_04 = 0.0f;
    zero = player->unk_04;
    player->unk_34 = player->unk_38 = zero;
    player->unk_0E = 0;
    player->unk_02 = -1;
    player->unk_08 = 0;
    player->unk_50 = 0;
    player->unk_48 = zero;
    player->unk_0C = 0;
    player->unk_10 = -1;
    player->unk_4C = 0;
    m252_KoopaCreate(player->index);
    m252_KoopaGet(player->index);
    object->func = m252_PlayerObjMain;
}

const Vec m252_zeroVec = { 0.0f, 0.0f, 0.0f };

void m252_PlayerObjMain(omObjData *object) {
    Vec pos = m252_zeroVec;
    Vec vel = m252_zeroVec;
    Vec scale = m252_zeroVec;
    BowserTossPlayer *player;
    BowserTossKoopa *bowser;
    HmfModel *model;
    MgPlayerWork *data;
    s32 stickPos;
    f32 temp;
    f32 stickX;
    f32 stickY;
    f32 power;
    f32 accel;
    f32 angle;
    f32 pitch;

    player = m252_WorkPtrGet(object);
    bowser = m252_KoopaGet(player->index);
    data = object->data;
    model = &Hu3DData[object->model[0]];
    switch (MgFlowStatGet()) {
        case MG_STATE_OPENING:
            if (player->unk_0C == 0) {
                if (player->unk_08 >= 30.0f) {
                    player->unk_08 = 0;
                    player->unk_0C = 1;
                }
            } else if (m252_playerWorkTbl[0].unk_0C > 0 && m252_playerWorkTbl[1].unk_0C > 0 &&
                       m252_resultWait <= 0) {
                m252_resultWait++;
            }
            break;
        case MG_STATE_PLAY:
            if (player->unk_1E) {
                m252_PlayerComInput(object);
            }
            switch (player->unk_0C) {
                case 1:
                    if (HuPadBtnDown[player->unk_1A] & A_BUTTON) {
                        if (MgPlayerMotSet(object, 4)) {
                            player->unk_30 = 10;
                            player->unk_32 = 1;
                            player->unk_44 += 0.5f;
                            if (player->unk_44 >= 45.0f) {
                                player->unk_44 = 45.0f;
                            } else if (player->unk_44 < 3.0f) {
                                player->unk_44 = 3.0f;
                            }
                            player->unk_4C = 1;
                            model->motShapeSpeed = 0.0f;
                            player->unk_0C = 2;
                            player->unk_10 = _HuAudPlayerFXPlay(0x4A6, player->index);
                        } else {
                            player->unk_44 = 0.0f;
                        }
                    }
                    break;
                case 2:
                    stickX = fabs(HuPadStkX[player->unk_1A]);
                    if (fabs(stickX) < 8.0) {
                        stickX = 0.0f;
                    } else if (stickX > 60.0f) {
                        stickX = 60.0f;
                    } else if (stickX < -60.0f) {
                        stickX = -60.0f;
                    }
                    if (stickX >= 8.0f) {
                        stickX -= 8.0f;
                    }
                    stickY = fabs(HuPadStkY[player->unk_1A]);
                    if (fabs(stickY) < 8.0) {
                        stickY = 0.0f;
                    } else if (stickY > 60.0f) {
                        stickY = 60.0f;
                    } else if (stickY < -60.0f) {
                        stickY = -60.0f;
                    }
                    if (stickY >= 8.0f) {
                        stickY -= 8.0f;
                    }
                    stickPos = MgPlayerStickAvgGet(object, stickX, stickY);
                    stickX = stickPos >> 16;
                    stickY = stickPos & 0xFFFF;
                    power = sqrtf(stickX * stickX + stickY * stickY) / 52.0f;
                    if (power < 0.0f) {
                        power = 0.0f;
                    } else if (power > 1.0f) {
                        power = 1.0f;
                    }
                    player->unk_48 = power * player->unk_2C + player->unk_24;
                    if (model->motIdShift == 0xFF) {
                        temp = model->motShapeTime - player->unk_48;
                        if (fabs(temp) < 1.75) {
                            model->motShapeTime = player->unk_48;
                        } else if (temp < 0.0f) {
                            model->motShapeTime += 1.75f;
                        } else {
                            model->motShapeTime -= 1.75f;
                        }
                    } else {
                        model->motShapeTime = 0.0f;
                    }
                    player->unk_44 -= 0.075f;
                    accel = (1.0 - bowser->unk_28) * 2;
                    if (accel < 1.0f) {
                        accel = 1.0f;
                    } else if (accel > 2.0f) {
                        accel = 2.0f;
                    }
                    accel *= 0.5f;
                    if (HuPadBtnDown[player->unk_1A] & A_BUTTON) {
                        player->unk_44 += accel;
                        player->unk_0E++;
                        if (!(player->unk_0E & 1)) {
                            pos.x = object->trans.x;
                            pos.y = object->trans.y + 20.0;
                            pos.z = object->trans.z;
                            vel.x = sindf(object->rot.y) * 20.0 * 0.2f;
                            vel.z = cosdf(object->rot.y) * 20.0 * 0.2f;
                            vel.y = 0.0f;
                            scale.x = scale.y = scale.z = 0.5f;
                            m252_SmokeCreate(&pos, &vel, &scale, 1.0f, player->index);
                        }
                    }
                    if (player->unk_44 >= 45.0f) {
                        player->unk_44 = 45.0f;
                    } else if (player->unk_44 < 3.0f) {
                        player->unk_44 = 3.0f;
                    }
                    model->motSpeed = player->unk_44 * 10.0f / 45.0f;
                    if (player->unk_44 >= 0.5f && model->motSpeed < 0.3f) {
                        model->motSpeed = 0.3f;
                    }
                    if (model->motSpeed >= 1.0f) {
                        model->motSpeed = 1.0f;
                    }
                    object->rot.y += player->unk_44;
                    if (object->rot.y >= 360.0f) {
                        object->rot.y -= 360.0f;
                    }
                    bowser->unk_28 = player->unk_44 / 45.0f;
                    if (bowser->unk_28 >= 1.0f) {
                        bowser->unk_28 = 1.0f;
                    } else if (bowser->unk_28 < 0.0f) {
                        bowser->unk_28 = 0.0f;
                    }
                    if (player->unk_10 != -1) {
                        pitch = (1.0 - bowser->unk_28) * -3600.0;
                        if (object->rot.y <= 180.0f) {
                            angle = object->rot.y - 90.0f;
                        } else {
                            angle = -(object->rot.y - 270.0f);
                        }
                        pitch += angle * (1.0f / 90.0f) * 400.0f;
                        HuAudFXPitchSet(player->unk_10, (s16)pitch);
                    }
                    bowser->unk_2C = (model->motShapeTime - player->unk_24) / player->unk_2C;
                    if (bowser->unk_2C >= 1.0f) {
                        bowser->unk_2C = 1.0f;
                    } else if (bowser->unk_2C < 0.0f) {
                        bowser->unk_2C = 0.0f;
                    }
                    break;
                case 3:
                    if (player->unk_4C) {
                        if (player->unk_48 < player->unk_24) {
                            player->unk_48 = player->unk_24;
                        }
                        if (model->motIdShift == 0xFF) {
                            temp = model->motShapeTime - player->unk_48;
                            if (fabs(temp) < 1.75) {
                                model->motShapeTime = player->unk_48;
                            } else if (temp < 0.0f) {
                                model->motShapeTime += 1.75f;
                            } else {
                                model->motShapeTime -= 1.75f;
                            }
                        } else {
                            model->motShapeTime = 0.0f;
                        }
                        model->motSpeed = player->unk_44 * 10.0f / 45.0f;
                        if (player->unk_44 >= 0.5f && model->motSpeed < 0.3f) {
                            model->motSpeed = 0.3f;
                        }
                        if (model->motSpeed >= 1.0f) {
                            model->motSpeed = 1.0f;
                        }
                        bowser->unk_28 = player->unk_44 / 45.0f;
                        if (bowser->unk_28 >= 1.0f) {
                            bowser->unk_28 = 1.0f;
                        } else if (bowser->unk_28 < 0.0f) {
                            bowser->unk_28 = 0.0f;
                        }
                        bowser->unk_2C = (model->motShapeTime - player->unk_24) / player->unk_2C;
                        if (bowser->unk_2C >= 1.0f) {
                            bowser->unk_2C = 1.0f;
                        } else if (bowser->unk_2C < 0.0f) {
                            bowser->unk_2C = 0.0f;
                        }
                        if (player->unk_44 >= 45.0f) {
                            player->unk_44 = 45.0f;
                        } else if (player->unk_44 < 3.0f) {
                            player->unk_44 = 3.0f;
                        }
                        if (player->unk_10 != -1) {
                            pitch = (1.0 - bowser->unk_28) * -3600.0;
                            if (object->rot.y <= 180.0f) {
                                angle = object->rot.y - 90.0f;
                            } else {
                                angle = -(object->rot.y - 270.0f);
                            }
                            pitch += angle * (1.0f / 90.0f) * 400.0f;
                            HuAudFXPitchSet(player->unk_10, (s16)pitch);
                        }
                        object->rot.y += player->unk_44;
                        if (object->rot.y >= 720.0f) {
                            object->rot.y -= 720.0f;
                        }
                        if (object->rot.y >= 450.0f) {
                            bowser->unk_0A = 1;
                            bowser->unk_0C = model->motShapeTime;
                            if (player->unk_10 != -1) {
                                HuAudFXStop(player->unk_10);
                            }
                            player->unk_10 = -1;
                            HuAudPlayerFXPlay(player->unk_1C + 0xB0, player->index);
                            MgPlayerMotSet(object, 0);
                            Hu3DData[object->model[0]].motIdShape = 0xFF;
                            player->unk_3C = 0;
                            player->unk_0C = 4;
                        }
                    } else {
                        player->unk_0C = 4;
                    }
                    break;
                case 4:
                    if (player->unk_3C) {
                        player->unk_0C = 5;
                        player->unk_08 = 0;
                        break;
                    }
                    object->rot.y += player->unk_44;
                    if (object->rot.y >= 360.0f) {
                        object->rot.y -= 360.0f;
                    }
                    if (player->unk_44 != 0.0f) {
                        player->unk_44 *= 0.9f;
                    }
                    if (player->unk_44 <= 0.1f) {
                        player->unk_44 = 0.0f;
                        player->unk_0C = 5;
                        player->unk_08 = 0;
                    }
                    break;
                case 5:
                    break;
            }
            break;
        case MG_STATE_FINISH:
            switch (player->unk_0C) {
                case 5:
                    if (m252_winnerNo == player->index) {
                        player->unk_0C = 6;
                    } else {
                        player->unk_0C = 9;
                    }
                case 6:
                    if (player->unk_04 < 400.0) {
                        player->unk_0C = 9;
                    } else if (player->unk_04 < 800.0) {
                        MgPlayerMotSet(object, 3);
                        player->unk_34 = 19.0f;
                        player->unk_0C = 7;
                        HuAudPlayerFXPlay(player->unk_1C + 0x3B, player->index);
                        temp = (player->unk_04 - 400.0) / 400.0;
                        player->unk_38 = (temp + 1.0) * 9.000000357627869;
                    } else {
                        object->trans.x = bowser->unk_30 - 500.0;
                        object->trans.y = 700.0f;
                        MgPlayerMotSet(object, 3);
                        player->unk_34 = 0.0f;
                        player->unk_0C = 8;
                        HuAudPlayerFXPlay(player->unk_1C + 0xB9, player->index);
                    }
                    break;
                case 7:
                    object->trans.x += player->unk_38;
                    object->trans.y += player->unk_34;
                    player->unk_34 -= 1.79663f;
                    object->rot.y = m252_AngleStepCalc(90.0f, object->rot.y, 10.0f);
                    if (object->trans.y <= 0.0f) {
                        MgPlayerMotSet(object, 0);
                        HuAudPlayerFXPlay(player->unk_1C + 0x32, player->index);
                        object->trans.y = 0.0f;
                        player->unk_0C = 9;
                    }
                    break;
                case 8:
                    object->trans.x += 9.000000357627869;
                    object->trans.y += player->unk_34;
                    player->unk_34 -= 1.79663f;
                    object->rot.y = m252_AngleStepCalc(90.0f, object->rot.y, 10.0f);
                    if (object->trans.y <= 0.0f) {
                        MgPlayerMotSet(object, 0);
                        HuAudPlayerFXPlay(player->unk_1C + 0x32, player->index);
                        if (m252_spinSeNo == -1) {
                            m252_spinSeNo = HuAudFXPlay(0x4AA);
                        }
                        object->trans.y = 0.0f;
                        player->unk_0C = 9;
                    }
                    break;
                case 9:
                    if (player->unk_3C) {
                        MgPlayerMotSet(object, 0);
                        Hu3DData[object->model[0]].motIdShape = 0xFF;
                        bowser->unk_0A = 3;
                        player->unk_3C = 0;
                    }
                    object->rot.y = m252_AngleStepCalc(0.0f, object->rot.y, 10.0f);
                    if (object->rot.y < 1.0f || object->rot.y >= 359.0f) {
                        player->unk_0C = 10;
                    }
                    break;
                case 10:
                    break;
            }
            break;
        case MG_STATE_RESULT:
            switch (player->unk_02) {
                case 0:
                    if (MgPlayerMotSet(object, 7)) {
                        CharAnimCreate(object->model[0], 2, player->unk_1C, m252_winAnimTbl[player->unk_1C]);
                        HuAudCharVoicePlayPlayer(player->unk_14, -1, player->index);
                        player->unk_02 = -1;
                    }
                    break;
                case 1:
                    if (MgPlayerMotSet(object, 8)) {
                        CharAnimCreate(object->model[0], 2, player->unk_1C, m252_loseAnimTbl[player->unk_1C]);
                        player->unk_02 = -1;
                    }
                    break;
            }
            break;
    }
    MgPlayerMotUpdate(object);
    if ((player->unk_30 != 0 || player->unk_32 != 0) && data->unkD6 == 0) {
        model = &Hu3DData[object->model[0]];
        if (player->unk_30 != 0) {
            model->unk0C = player->unk_30;
        }
        if (player->unk_30 == 1) {
            model->unk0E = player->unk_30;
        }
        if (player->unk_32) {
            model->motSpeed = 0.0f;
            model->motShiftSpeed = 0.0f;
        }
        player->unk_32 = 0;
        player->unk_30 = 0;
    }
    player->unk_08++;
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
}

void m252_PlayerComInput(omObjData *object) {
    BowserTossPlayer *player;
    f32 ratio;

    player = m252_WorkPtrGet(object);
    m252_KoopaGet(player->index);
    HuPadBtn[player->unk_1A] = HuPadBtnDown[player->unk_1A] = HuPadStkY[player->unk_1A] = 0;
    switch (player->unk_0C) {
        case 1:
            player->unk_54 = m252_comPowerTbl[player->unk_20] +
                             m252_comPowerRandTbl[player->unk_20] *
                                 ((0.5 - (f32)(u8)(rand8() % 100) * 0.01) * 2);
            player->unk_58 = m252_ComPowerCalc(
                player->unk_54,
                m252_comDistTbl[player->unk_20] + (f32)(u8)(rand8() % 100) * 0.01 * 1500.0,
                m252_comScaleTbl[player->unk_20]);
            HuPadBtnDown[player->unk_1A] |= A_BUTTON;
            break;
        case 2:
            HuPadStkY[player->unk_1A] = player->unk_54 * 60.0f;
            ratio = player->unk_44 / 45.0f;
            if ((player->unk_08 & 1) && ratio < player->unk_58) {
                HuPadBtnDown[player->unk_1A] |= A_BUTTON;
            }
            break;
    }
}

f32 m252_ComPowerCalc(f32 power, f32 distance, f32 fallback) {
    f32 pos[2];
    f32 vel[2];
    f32 angle;
    f32 scale;

    angle = 360.0f - power * 85.0f;
    for (scale = 0.5f; scale < 1.0f; scale += 0.01f) {
        pos[0] = m252_throwStartPos[0];
        pos[1] = m252_throwStartPos[1];
        vel[0] = fabs(cosdf(angle)) * scale * 75.99999904632568;
        vel[1] = fabs(sindf(angle)) * scale * 75.99999904632568;
        while (pos[1] > 0.0f) {
            pos[0] += vel[0];
            pos[1] += vel[1];
            vel[1] -= 0.65332f;
            if (vel[1] < -250.0) {
                vel[1] = -250.0f;
            }
        }
        if (distance <= pos[0]) {
            return scale;
        }
    }
    for (scale = 0.5f; scale > 0.1f; scale -= 0.01f) {
        pos[0] = m252_throwStartPos[0];
        pos[1] = m252_throwStartPos[1];
        vel[0] = fabs(cosdf(angle)) * scale * 75.99999904632568;
        vel[1] = fabs(sindf(angle)) * scale * 75.99999904632568;
        while (pos[1] > 0.0f) {
            pos[0] += vel[0];
            pos[1] += vel[1];
            vel[1] -= 0.65332f;
            if (vel[1] < -250.0) {
                vel[1] = -250.0f;
            }
        }
        if (distance <= pos[0]) {
            return scale;
        }
    }
    return fallback;
}

s16 m252_PlayerAllThrownCheck(void) {
    s32 i;
    BowserTossPlayer *p;

    for (i = 0, p = m252_playerWorkTbl; i < 2; i++, p++) {
        if (p->unk_0C != 5) {
            return 0;
        }
    }
    return 1;
}

s16 m252_PlayerAllEndCheck(void) {
    s32 i;
    BowserTossPlayer *p;

    for (i = 0, p = m252_playerWorkTbl; i < 2; i++, p++) {
        if (p->unk_0C != 10) {
            return 0;
        }
    }
    return 1;
}

// Swaps the shared HmfData pointer of two of the object's models.
void m252_PlayerMdlSwap(omObjData *object, s16 arg1, s16 arg2) {
    HmfModel *model1 = &Hu3DData[object->model[arg1]];
    HmfModel *model2 = &Hu3DData[object->model[arg2]];
    HmfData *hmf = model1->hmf;

    model1->hmf = model2->hmf;
    model2->hmf = hmf;
}

void m252_KoopaInit(void) {
    BowserTossKoopa *bowser;
    s32 i;

    bowser = m252_koopaTbl = HuMemAllocTag(sizeof(BowserTossKoopa) * 2, TAG_OVERLAY);
    memset(bowser, 0, sizeof(BowserTossKoopa) * 2);
    for (i = 0; i < 2; i++, bowser++) {
        bowser->unk_00 = NULL;
        bowser->unk_5C = NULL;
        bowser->unk_10 = 0.0f;
        bowser->unk_14 = 120.0f;
        bowser->unk_18 = 0.0f;
        bowser->unk_1C = 0.0f;
        bowser->unk_20 = -1;
        bowser->unk_22 = 0;
        bowser->unk_24 = 0;
    }
    m252_koopaObj = omAddObj(0x14, 0, 0, -1, m252_KoopaObjMain);
}

void m252_KoopaCreate(s16 index) {
    BowserTossKoopa *bowser;
    HmfModel *model;
    u8 motId;
    u8 motIdShape;
    s16 frames;
    s32 size;
    s32 modelId;
    HmfModelData_Unk64_Unk8C_Struct *motData;

    bowser = &m252_koopaTbl[index];
    bowser->unk_00 = mgPlayerObjTbl[index];
    bowser->unk_0A = 0;
    m252_WorkPtrGet(bowser->unk_00);
    model = &Hu3DData[bowser->unk_00->model[0]];
    motId = model->motId;
    motIdShape = model->motIdShape;
    model->motId = bowser->unk_00->motion[4];
    model->motIdShape = bowser->unk_00->motion[6];
    bowser->unk_5C = m252_HookMtxBake(bowser->unk_00->model[0], 1, "item_hook", 1, 0);
    model->motId = motId;
    model->motIdShape = motIdShape;
    motData = &Hu3DMotion[bowser->unk_00->motion[6]];
    frames = motData->unk02 + 1;
    size = frames * sizeof(Mtx);
    bowser->unk_60 = HuMemAllocTag(size, TAG_OVERLAY);
    memset(bowser->unk_60, 0, size);
    memcpy(bowser->unk_60, bowser->unk_5C->mtx, size);
    m252_HookMtxFree(bowser->unk_5C);
    bowser->unk_5C = NULL;
    if (index == 0) {
        bowser->unk_04 = Hu3DModelRead(0x550000, 0x299);
        bowser->unk_06 = Hu3DModelRead(0x550005, 0x29D);
        modelId = bowser->unk_08 = Hu3DModelRead(0, 0x299);
    } else {
        bowser->unk_04 = Hu3DModelLink(m252_koopaTbl->unk_04);
        bowser->unk_06 = Hu3DModelLink(m252_koopaTbl->unk_06);
        modelId = bowser->unk_08 = Hu3DModelLink(m252_koopaTbl->unk_08);
    }
    Hu3DModelScaleSet(modelId, 1.3f, 1.3f, 1.3f);
    Hu3DModelAttrSet(bowser->unk_04, 0x4000, 0x4000);
    Hu3DModelHookSet(bowser->unk_04, bowser->unk_00->model[0], "item_hook");
    Hu3DModelCameraSet(bowser->unk_04, 1 << index);
    Hu3DModelCameraSet(bowser->unk_06, 1 << index);
    Hu3DModelCameraSet(bowser->unk_08, 1 << index);
}

BowserTossKoopa *m252_KoopaGet(s16 arg0) {
    return &m252_koopaTbl[arg0];
}

void m252_KoopaObjMain(omObjData *object) {
    HuMtx4F rotMtx;
    HuMtx4F mtx;
    HuMtx4F hookMtx;
    Vec pos;
    Vec vel;
    Vec scale;
    BowserTossPlayer *player;
    BowserTossKoopa *bowser;
    HmfModel *model;
    f32 t;
    f32 ground;
    f32 pitch;
    f32 yaw;
    f32 speed;
    s32 count;
    s32 i;
    s32 j;

    for (i = 0, bowser = m252_koopaTbl; i < 2; i++, bowser++) {
        player = m252_WorkPtrGet(bowser->unk_00);
        model = &Hu3DData[bowser->unk_00->model[0]];
        object->trans.x = bowser->unk_00->trans.x;
        object->trans.y = bowser->unk_00->trans.y;
        object->trans.z = bowser->unk_00->trans.z;
        object->rot.x = bowser->unk_00->rot.x;
        object->rot.y = bowser->unk_00->rot.y;
        object->rot.z = bowser->unk_00->rot.z;
        object->scale.x = bowser->unk_00->scale.x;
        object->scale.y = bowser->unk_00->scale.y;
        object->scale.z = bowser->unk_00->scale.z;
        switch (bowser->unk_0A) {
            case 0:
                if (bowser->unk_60 != NULL) {
                    m252_ObjMtxCalc(object, object->rot.y, rotMtx);
                    m252_KoopaHookMtxGet(bowser, hookMtx[0], model->motShapeTime);
                    if (model->motIdShape != 0xFF) {
                        mtxCat(hookMtx, rotMtx, mtx);
                    } else {
                        mtxCopy(mtx, rotMtx);
                    }
                    mtxTransCat(mtx, 0.0f, 0.0f, 150.0f);
                    bowser->unk_30 = mtx[3][0];
                    bowser->unk_38 = mtx[3][2];
                }
                break;
            case 1:
                Hu3DModelAttrSet(bowser->unk_04, 0x4000, 0);
                m252_ObjMtxCalc(object, 90.0f, rotMtx);
                m252_KoopaHookMtxGet(bowser, hookMtx[0], model->motShapeTime);
                mtxCat(hookMtx, rotMtx, mtx);
                mtxTransCat(mtx, 0.0f, 0.0f, 150.0f);
                bowser->unk_30 = mtx[3][0];
                bowser->unk_34 = mtx[3][1];
                bowser->unk_38 = mtx[3][2];
                bowser->unk_3C = 360.0f - bowser->unk_2C * 85.0f;
                bowser->unk_40 = 90.0f;
                bowser->unk_44 = 0.0f;
                Hu3DModelAttrSet(bowser->unk_04, 4, 4);
                Hu3DModelAttrSet(bowser->unk_06, 4, 0);
                bowser->unk_48 = fabs(cosdf(bowser->unk_3C)) * bowser->unk_28 * 75.99999904632568;
                bowser->unk_4C = fabs(sindf(bowser->unk_3C)) * bowser->unk_28 * 75.99999904632568;
                bowser->unk_50 = 0;
                bowser->unk_30 += bowser->unk_48;
                bowser->unk_34 += bowser->unk_4C;
                bowser->unk_22 = 0;
                bowser->unk_24 = m252_FallTimeCalc(bowser->unk_30, bowser->unk_34, bowser->unk_48, bowser->unk_4C);
                bowser->unk_20 = _HuAudPlayerFXPlay(0x4A7, player->index);
                if (bowser->unk_20 != -1) {
                    HuAudFXPitchSet(bowser->unk_20, bowser->unk_22);
                }
                bowser->unk_0A = 2;
                bowser->unk_0C = 0;
                break;
            case 2:
                bowser->unk_30 += bowser->unk_48;
                bowser->unk_34 += bowser->unk_4C;
                bowser->unk_4C -= 0.65332f;
                if (bowser->unk_4C < -250.0) {
                    bowser->unk_4C = -250.0f;
                }
                if (bowser->unk_0C < 20) {
                    t = bowser->unk_0C / 20.0f;
                    CenterM[i].x = m252_InterpCalc(t, Center.x, bowser->unk_30);
                    CenterM[i].y = m252_InterpCalc(t, Center.y, bowser->unk_34);
                } else {
                    CenterM[i].x = bowser->unk_30;
                    CenterM[i].y = bowser->unk_34;
                }
                if (CenterM[i].x < Center.x) {
                    CenterM[i].x = Center.x;
                }
                if (player->index == 0) {
                    if (CenterM[i].y < Center.y) {
                        CenterM[i].y = Center.y;
                    }
                } else {
                    if (CenterM[i].y < m252_cameraCenterMin.y) {
                        CenterM[i].y = m252_cameraCenterMin.y;
                    }
                }
                bowser->unk_3C = atan2df(-bowser->unk_4C, bowser->unk_48);
                bowser->unk_44 += bowser->unk_28 * 10.0f;
                if (bowser->unk_44 >= 360.0f) {
                    bowser->unk_44 -= 360.0f;
                }
                ground = -(fabs(bowser->unk_4C) / 250.0 * 100.0);
                if (bowser->unk_34 <= ground + 10.0) {
                    bowser->unk_34 = ground + 10.0;
                    bowser->unk_0E = 0;
                    bowser->unk_0C = 0;
                    player->unk_04 = bowser->unk_30;
                    scale.x = scale.y = scale.z = 1.0f;
                    count = fabs(bowser->unk_4C) / 250.0 * 8.0 + 8.0;
                    for (j = 0; j < count; j++) {
                        pos.x = bowser->unk_30 + 100.0f - (f32)(u8)(rand8() % 100) * 0.01 * 200.0;
                        pos.z = bowser->unk_38 + (f32)(u8)(rand8() % 100) * 0.01 * 200.0 * 0.5;
                        pos.y = 0.0f;
                        pitch = -((f32)(u8)(rand8() % 100) * 0.01 * 90.0);
                        yaw = (f32)(u8)(rand8() % 100) * 0.01 * 360.0;
                        speed = (f32)(u8)(rand8() % 100) * 0.01 * 5.000000074505806 + 5.000000074505806;
                        vel.x = sindf(yaw) * cosdf(pitch) * speed;
                        vel.y = -sindf(pitch) * speed;
                        vel.z = cosdf(yaw) * cosdf(pitch) * speed;
                        m252_SmokeCreate(&pos, &vel, &scale, 1.0f, player->index);
                    }
                    if (bowser->unk_20 != -1) {
                        HuAudFXStop(bowser->unk_20);
                    }
                    bowser->unk_20 = -1;
                    _HuAudPlayerFXPlay(0x4A8, player->index);
                    omVibrate(player->unk_18, 20, 0, 20);
                    if (bowser->unk_28 < 0.4f) {
                        bowser->unk_0A = 7;
                    } else {
                        if (fabs(bowser->unk_48) < 2.0 * fabs(bowser->unk_4C)) {
                            bowser->unk_18 = 50.0f;
                        } else {
                            bowser->unk_18 = bowser->unk_28 / 0.4f * 50.0;
                        }
                        bowser->unk_1C = CenterM[i].y;
                        bowser->unk_0A = 6;
                    }
                } else {
                    if (bowser->unk_4C > 0.0f) {
                        bowser->unk_22 += 10;
                    } else {
                        bowser->unk_22 -= 10;
                    }
                    if (bowser->unk_22 > 1200) {
                        bowser->unk_22 = 1200;
                    } else if (bowser->unk_22 < 0) {
                        bowser->unk_22 = 0;
                    }
                    if (bowser->unk_20 != -1) {
                        HuAudFXPitchSet(bowser->unk_20, bowser->unk_22);
                    }
                }
                break;
            case 3:
                Hu3DModelAttrSet(bowser->unk_04, 0x4000, 0);
                m252_ObjMtxCalc(object, 90.0f, rotMtx);
                m252_KoopaHookMtxGet(bowser, hookMtx[0], 0.0f);
                mtxCat(hookMtx, rotMtx, mtx);
                mtxTransCat(mtx, 0.0f, 0.0f, 150.0f);
                bowser->unk_30 = mtx[3][0];
                bowser->unk_34 = mtx[3][1];
                bowser->unk_38 = mtx[3][2];
                bowser->unk_3C = 45.0f;
                bowser->unk_40 = 90.0f;
                bowser->unk_44 = 0.0f;
                Hu3DModelAttrSet(bowser->unk_04, 4, 4);
                Hu3DModelAttrSet(bowser->unk_06, 4, 0);
                bowser->unk_4C = 0.0f;
                bowser->unk_0A = 4;
            case 4:
                bowser->unk_4C -= 1.95996f;
                if (bowser->unk_4C < -250.0) {
                    bowser->unk_4C = -250.0f;
                }
                bowser->unk_34 += bowser->unk_4C;
                ground = -(fabs(bowser->unk_4C) / 250.0 * 100.0);
                if (bowser->unk_34 <= ground + 10.0) {
                    bowser->unk_34 = ground + 10.0;
                    scale.x = scale.y = scale.z = 1.0f;
                    for (j = 0; j < 5; j++) {
                        pos.x = bowser->unk_30 + 100.0f - (f32)(u8)(rand8() % 100) * 0.01 * 200.0;
                        pos.z = bowser->unk_38 + (f32)(u8)(rand8() % 100) * 0.01 * 200.0 * 0.5;
                        pos.y = 0.0f;
                        pitch = -((f32)(u8)(rand8() % 100) * 0.01 * 90.0);
                        yaw = (f32)(u8)(rand8() % 100) * 0.01 * 360.0;
                        speed = (f32)(u8)(rand8() % 100) * 0.01 * 5.000000074505806 + 5.000000074505806;
                        vel.x = sindf(yaw) * cosdf(pitch) * speed;
                        vel.y = -sindf(pitch) * speed;
                        vel.z = cosdf(yaw) * cosdf(pitch) * speed;
                        m252_SmokeCreate(&pos, &vel, &scale, 1.0f, player->index);
                    }
                    _HuAudPlayerFXPlay(0x4A8, player->index);
                    bowser->unk_0A = 9;
                }
                break;
            case 5:
                bowser->unk_3C = m252_AngleStepCalc(0.0f, bowser->unk_3C, 5.0f);
                if (bowser->unk_3C <= 0.0f) {
                    bowser->unk_0A = 9;
                    bowser->unk_0C = 0;
                }
                break;
            case 6:
                bowser->unk_0A = 8;
                bowser->unk_0C = 0;
                break;
            case 7:
                bowser->unk_48 *= 0.8f;
                bowser->unk_30 += bowser->unk_48;
                CenterM[i].x = bowser->unk_30;
                CenterM[i].y = bowser->unk_34;
                if (CenterM[i].x < Center.x) {
                    CenterM[i].x = Center.x;
                }
                if (player->index == 0) {
                    if (CenterM[i].y < Center.y) {
                        CenterM[i].y = Center.y;
                    }
                } else {
                    if (CenterM[i].y < m252_cameraCenterMin.y) {
                        CenterM[i].y = m252_cameraCenterMin.y;
                    }
                }
                pos.x = bowser->unk_30;
                pos.y = 0.0f;
                pos.z = bowser->unk_38;
                pitch = (f32)(u8)(rand8() % 100) * 0.01 * 180.0;
                yaw = (f32)(u8)(rand8() % 100) * 0.01 * 360.0;
                speed = (f32)(u8)(rand8() % 100) * 0.01 * 7.000000029802322 + 7.000000029802322;
                vel.x = sindf(yaw) * cosdf(pitch) * speed;
                vel.y = -sindf(pitch) * speed;
                vel.z = cosdf(yaw) * cosdf(pitch) * speed;
                scale.x = scale.y = scale.z = 1.0f;
                m252_SmokeCreate(&pos, &vel, &scale, 1.0f, player->index);
                if (bowser->unk_48 <= 10.0) {
                    bowser->unk_0A = 9;
                    bowser->unk_0C = 0;
                }
                break;
            case 8:
                // do-while(0) needed to match the scheduling of the 100.0f constant load.
                do {
                    pos.x = bowser->unk_30 + 100.0f - (f32)(u8)(rand8() % 100) * 0.01 * 200.0;
                } while (0);
                pos.z = bowser->unk_38 + (f32)(u8)(rand8() % 100) * 0.01 * 200.0 * 0.5;
                pos.y = 0.0f;
                pitch = -((f32)(u8)(rand8() % 100) * 0.01 * 90.0);
                yaw = (f32)(u8)(rand8() % 100) * 0.01 * 360.0;
                speed = (f32)(u8)(rand8() % 100) * 0.01 * 5.000000074505806 + 5.000000074505806;
                vel.x = sindf(yaw) * cosdf(pitch) * speed;
                vel.y = -sindf(pitch) * speed;
                vel.z = cosdf(yaw) * cosdf(pitch) * speed;
                scale.x = scale.y = scale.z = 1.0f;
                m252_SmokeCreate(&pos, &vel, &scale, 1.0f, player->index);
                if (bowser->unk_0C >= 6.0f) {
                    bowser->unk_0A = 9;
                    bowser->unk_0C = 0;
                }
                break;
            case 9:
                break;
        }
        if (bowser->unk_18 >= 0.1f) {
            CenterM[i].y = bowser->unk_18 * 0.5f + bowser->unk_1C + sindf(bowser->unk_10) * bowser->unk_18;
            bowser->unk_10 += bowser->unk_14;
            if (bowser->unk_10 >= 360.0f) {
                bowser->unk_10 -= 360.0f;
            }
            bowser->unk_18 -= 7.500000298023224;
        }
        Hu3DModelPosSet(bowser->unk_04, bowser->unk_30, bowser->unk_34, bowser->unk_38);
        Hu3DModelRotSet(bowser->unk_04, bowser->unk_3C, bowser->unk_40, 0.0f);
        HuMtxIdentF(Hu3DData[bowser->unk_04].mtx);
        mtxRotCat(Hu3DData[bowser->unk_04].mtx, 0.0f, 0.0f, bowser->unk_44);
        Hu3DModelPosSet(bowser->unk_06, bowser->unk_30, bowser->unk_34, bowser->unk_38);
        Hu3DModelRotSet(bowser->unk_06, bowser->unk_3C, bowser->unk_40, 0.0f);
        HuMtxIdentF(Hu3DData[bowser->unk_06].mtx);
        mtxRotCat(Hu3DData[bowser->unk_06].mtx, 0.0f, 0.0f, bowser->unk_44);
        Hu3DModelPosSet(bowser->unk_08, bowser->unk_30, 0.0f, bowser->unk_38);
        bowser->unk_0C++;
    }
}

void m252_ObjMtxCalc(omObjData *object, f32 angle, HuMtx4F mtx) {
    fmod(object->rot.y + angle, 360.0);
    HuMtxIdentF(mtx);
    mtxTransCat(mtx, object->trans.x, object->trans.y, object->trans.z);
    mtxRotCat(mtx, object->rot.x, angle, object->rot.z);
    mtxScaleCat(mtx, object->scale.x, object->scale.y, object->scale.z);
}

void m252_KoopaHookMtxGet(BowserTossKoopa *bowser, f32 *out, f32 time) {
    s16 frame;
    s16 next;
    f32 frac;

    if ((s16)time >= 29) {
        frame = next = 29;
        frac = 0.0f;
    } else if ((s16)time <= 0) {
        frame = next = 0;
        frac = 0.0f;
    } else {
        frac = time - (s16)time;
        frame = time;
        next = frame + 1;
    }
    m252_MtxInterpCalc(bowser->unk_60[frame], bowser->unk_60[next], out, frac);
}

s16 m252_KoopaAllLandCheck(void) {
    s32 i;
    BowserTossKoopa *pBowser;

    for (i = 0, pBowser = m252_koopaTbl; i < 2; i++, pBowser++) {
        if (pBowser->unk_0A == 0 || pBowser->unk_0A == 9) {
            continue;
        }
        return 0;
    }
    return 1;
}

// Counts the frames until a projectile falls back to the ground.
s16 m252_FallTimeCalc(f32 x, f32 y, f32 velX, f32 velY) {
    s16 frames;
    f32 groundOffset;

    frames = 0;
    groundOffset = 0.0f;
    while (y > groundOffset + 10.0) {
        y += velY;
        velY -= 1.95996f;
        if (velY < -250.0) {
            velY = -250.0f;
        }
        groundOffset = -(fabs(velY) / 250.0 * 100.0);
        frames++;
    }
    return frames;
}

void m252_SmokeInit(void) {
    HuSprAnimData *sprite;
    BowserTossSmoke *effect;
    HmfModel *model;
    s32 i;

    m252_sprTbl[5] = m252_SprAnimRead(11);
    sprite = HuSprAnimDataGet(m252_sprTbl[5]);
    m252_smokeObj = omAddObj(0x1E, 0, 0, -1, m252_SmokeObjMain);
    m252_smokeTbl = effect = HuMemAllocTag(sizeof(BowserTossSmoke) * 32, TAG_OVERLAY);
    for (i = 0; i < 32; i++, effect++) {
        if (i == 0) {
            effect->unk_02 = m252_BillboardColorMdlCreate(sprite, m252_smokeColor, 0);
        } else {
            effect->unk_02 = m252_BillboardColorMdlLink(sprite, m252_smokeTbl->unk_02, m252_smokeColor);
        }
        effect->unk_00 = 0;
        effect->unk_04 = effect->unk_08 = 0.0f;
        effect->unk_0C.x = effect->unk_0C.y = effect->unk_0C.z = 0.0f;
        effect->unk_18.x = effect->unk_18.y = effect->unk_18.z = 0.0f;
        effect->unk_24.x = effect->unk_24.y = effect->unk_24.z = 0.0f;
        Hu3DModelAttrSet(effect->unk_02, 4, 4);
        model = &Hu3DData[effect->unk_02];
        model->motTime = 0.0f;
    }
}

void m252_SmokeObjMain(omObjData *object) {
    HuSprAnimData *sprite;
    BowserTossSmoke *effect;
    HmfModel *model;
    s32 i;

    sprite = HuSprAnimDataGet(m252_sprTbl[5]);
    for (i = 0, effect = m252_smokeTbl; i < 32; i++, effect++) {
        if (effect->unk_00 == 0) {
            continue;
        }
        model = &Hu3DData[effect->unk_02];
        if (model->attr & 4) {
            continue;
        }
        effect->unk_0C.x += effect->unk_18.x;
        effect->unk_0C.y += effect->unk_18.y;
        effect->unk_0C.z += effect->unk_18.z;
        model->pos.x = effect->unk_0C.x;
        model->pos.y = effect->unk_0C.y;
        model->pos.z = effect->unk_0C.z;
        model->scale.x = effect->unk_24.x;
        model->scale.y = effect->unk_24.y;
        model->scale.z = effect->unk_24.z;
        m252_BillboardColorPatSet(effect->unk_02, sprite, (s32)effect->unk_04, m252_smokeColor);
        effect->unk_04 += effect->unk_08;
        if ((s32)effect->unk_04 >= sprite->patNum) {
            effect->unk_00 = 0;
            effect->unk_04 = 0.0f;
            model->attr |= 4;
        }
    }
}

s32 m252_SmokeCreate(Vec *pos, Vec *vel, Vec *scale, f32 speed, s16 camera) {
    HuSprAnimData *sprite;
    BowserTossSmoke *effect;
    HmfModel *model;
    s32 i;

    sprite = HuSprAnimDataGet(m252_sprTbl[5]);
    for (i = 0, effect = m252_smokeTbl; i < 32; i++, effect++) {
        if (effect->unk_00 != 0) {
            continue;
        }
        effect->unk_00 = 1;
        model = &Hu3DData[effect->unk_02];
        if (pos != NULL) {
            effect->unk_0C.x = pos->x;
            effect->unk_0C.y = pos->y;
            effect->unk_0C.z = pos->z;
        } else {
            effect->unk_0C.x = effect->unk_0C.y = effect->unk_0C.z = 0.0f;
        }
        if (vel != NULL) {
            effect->unk_18.x = vel->x;
            effect->unk_18.y = vel->y;
            effect->unk_18.z = vel->z;
        } else {
            effect->unk_18.x = effect->unk_18.y = effect->unk_18.z = 0.0f;
        }
        if (scale != NULL) {
            effect->unk_24.x = scale->x;
            effect->unk_24.y = scale->y;
            effect->unk_24.z = scale->z;
        } else {
            effect->unk_24.x = effect->unk_24.y = effect->unk_24.z = 1.0f;
        }
        effect->unk_08 = speed;
        effect->unk_04 = 0.0f;
        m252_BillboardColorPatSet(effect->unk_02, sprite, 0, m252_smokeColor);
        Hu3DModelAttrSet(effect->unk_02, 4, 0);
        Hu3DModelCameraSet(effect->unk_02, 1 << (u16)camera);
        model->motTime = 0.0f;
        model->pos.x = effect->unk_0C.x;
        model->pos.y = effect->unk_0C.y;
        model->pos.z = effect->unk_0C.z;
        model->scale.x = effect->unk_24.x;
        model->scale.y = effect->unk_24.y;
        model->scale.z = effect->unk_24.z;
        return i;
    }
    return -1;
}

// Appends a new object to the shared minigame object list.
void m252_StageObjCreate(void) {
    omObjData *obj = omAddObj(0x20, 0x1C, 0, -1, m252_StageObjInit);
    u16 index = mgMapObjNum;

    mgMapObjNum = index + 1;
    mgMapObjTbl[index] = obj;
}

void m252_StageObjInit(omObjData *object) {
    HuSprAnimData *sprite;
    s32 i;
    s32 j;
    s32 k;
    s32 base;
    s16 group;

    m252_sprTbl[0] = m252_SprAnimRead(0x550006);
    sprite = HuSprAnimDataGet(m252_sprTbl[0]);
    for (i = 0; i < 2; i++) {
        base = i * 14;
        j = 0;
        if (i == 0) {
            object->model[base + j] = Hu3DModelRead(0x550001, 0xB9);
        } else {
            object->model[base + j] = Hu3DModelLink(object->model[0]);
        }
        j++;
        if (i == 0) {
            object->model[base + j] = Hu3DModelRead(0x550003, 0xB9);
            object->model[base + j + 1] = Hu3DModelRead(0x550004, 0xB9);
        } else {
            object->model[base + j] = Hu3DModelLink(object->model[j]);
            object->model[base + j + 1] = Hu3DModelLink(object->model[j + 1]);
        }
        for (k = 2; k < 5; k++) {
            object->model[base + j + k] = Hu3DModelLink(object->model[j + (k & 1)]);
        }
        j += 5;
        if (i == 0) {
            object->model[base + j] = Hu3DModelRead(0x550002, 0x99);
        } else {
            object->model[base + j] = Hu3DModelLink(object->model[j]);
        }
        for (k = 1; k < 4; k++) {
            object->model[base + j + k] = Hu3DModelLink(object->model[base + j]);
        }
        j += 4;
        if (i == 0) {
            object->model[base + j] = m252_BillboardColorMdlCreate(sprite, m252_decoColor, 0);
        } else {
            object->model[base + j] = m252_BillboardColorMdlLink(sprite, object->model[j], m252_decoColor);
        }
        for (k = 1; k < 4; k++) {
            object->model[base + j + k] = m252_BillboardColorMdlLink(sprite, object->model[j], m252_decoColor);
        }
        for (k = base; k < base + 14; k++) {
            Hu3DModelPosSet(object->model[k], m252_decoPosTbl[k - base].x, m252_decoPosTbl[k - base].y,
                            m252_decoPosTbl[k - base].z);
            Hu3DModelCameraSet(object->model[k], 1 << i);
        }
    }
    m252_sprTbl[4] = m252_SprAnimRead(0x55000A);
    group = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(group, 0, m252_sprTbl[4], 0);
    HuSprPosSet(group, 0, 160, 120);
    HuSprAnimModeSet(group, 0, HUSPR_ANIM_MODE_STOP);
    HuSprPatNoSet(group, 0, 0);
    HuSprAttrSet(group, 0, 0x1000);
    object->func = m252_StageObjMain;
}

void m252_StageObjMain(omObjData *object) {
    HuSprAnimData *sprite;
    s32 i;
    s32 j;
    s32 k;
    s32 base;
    s32 start;
    s32 first;
    s16 parity;
    s32 index;
    s32 frame;

    sprite = HuSprAnimDataGet(m252_sprTbl[0]);
    for (i = 0; i < 2; i++) {
        base = i * 14;
        j = 0;
        start = (CenterM[i].x - 955.695037841796875) / 704.502487182617188 - 2.0;
        if (start < 0) {
            start = 0;
        }
        if (start >= 2) {
            Hu3DModelAttrSet(object->model[base + j], 4, 4);
        } else {
            Hu3DModelAttrSet(object->model[base + j], 4, 0);
        }
        j++;
        for (k = 0; k < 5; k++) {
            parity = (start & 1) ? 1 : 0;
            index = start + k;
            if (CenterM[i].x == Center.x) {
                Hu3DModelAttrSet(object->model[base + j + m252_decoSwapTbl[parity][k]], 4, 4);
            } else {
                Hu3DModelAttrSet(object->model[base + j + m252_decoSwapTbl[parity][k]], 4, 0);
                Hu3DModelPosSet(object->model[base + j + m252_decoSwapTbl[parity][k]],
                                (s16)index * 704.502487182617188 + 955.695037841796875, 0.0f, 0.0f);
            }
        }
        j += 5;
        first = CenterM[i].x / 500.0 - 1.0;
        if (first <= 0) {
            first = 1;
        }
        for (k = 0; k < 4; k++) {
            Hu3DModelPosSet(object->model[base + j + k], (f32)(first + k) * 500.0, 0.0f, 0.0f);
        }
        j += 4;
        for (k = 0; k < 4; k++) {
            Hu3DModelPosSet(object->model[base + j + k], (f32)(first + k) * 500.0, 75.0f, -300.0f);
            frame = first + k - 1;
            if (frame >= 20) {
                frame = 19;
                Hu3DModelAttrSet(object->model[base + j + k], 4, 4);
            } else if (frame < 0) {
                frame = 0;
                Hu3DModelAttrSet(object->model[base + j + k], 4, 0);
            } else {
                Hu3DModelAttrSet(object->model[base + j + k], 4, 0);
            }
            m252_BillboardColorPatSet(object->model[base + j + k], sprite, frame, m252_decoAnimColor);
        }
        m252_BackScrollSet(i, &CenterM[i], &CRotM[i]);
    }
}

u16 m252_SprAnimRead(s32 dirAndFile) {
    void *data;
    u16 sprite;

    data = DataRead(dirAndFile);
    sprite = HuSprAnimRead(data);
    DataClose(data);
    return sprite;
}

void m252_BackInit(void) {
    s32 i;
    s32 j;
    s32 group;

    m252_sprTbl[1] = m252_SprAnimRead(0x550007);
    m252_sprTbl[2] = m252_SprAnimRead(0x550008);
    m252_sprTbl[3] = m252_SprAnimRead(0x550009);
    for (i = 0; i < 2; i++) {
        m252_backGrpTbl[i] = group = (s32)HuSprGrpCreate(4, 0);
        for (j = 0; j < 4; j++) {
            HuSprGrpMemberSet(group, j, m252_sprTbl[1], 0);
            HuSprPosSet(group, j, m252_backScissorTbl[i].x, m252_backScissorTbl[i].y);
            HuSprAnimModeSet(group, j, HUSPR_ANIM_MODE_STOP);
            HuSprPatNoSet(group, j, 0);
            HuSprAttrSet(group, j, 0x483C);
            HuSprScissorSet(group, j, m252_backScissorTbl[i].x, m252_backScissorTbl[i].y,
                            m252_backScissorTbl[i].width, m252_backScissorTbl[i].height);
        }
    }
}

void m252_BackScrollSet(s16 camera, Vec *pos, Vec *rot) {
    s16 group;
    f32 x;
    f32 y;
    f32 scrollY;
    f32 signX;
    f32 signY;
    s16 frame;
    BowserTossScrollFrame *entry;

    group = m252_backGrpTbl[camera];
    x = (pos->x - Center.x) / m252_backScrollScale;
    y = (pos->y - Center.y) / m252_backScrollScale;
    if (x == 0.0f) {
        HuSprDispOff(group, 1);
        HuSprDispOff(group, 3);
    } else {
        HuSprDispOn(group, 1);
        HuSprDispOn(group, 3);
    }
    if (y == 0.0f) {
        HuSprDispOff(group, 2);
        HuSprDispOff(group, 3);
    } else {
        HuSprDispOn(group, 2);
        HuSprDispOn(group, 3);
    }
    frame = y / 120.0f;
    if (camera == 0) {
        x = -fmod(x, 320.0);
        scrollY = fmod(y, 120.0);
    } else {
        x = -fmod(x, 320.0);
        scrollY = fmod(y, 120.0) + 120.0;
    }
    signX = (pos->x >= 0.0f) ? 1.0f : -1.0f;
    signY = (pos->y >= 0.0f) ? 1.0f : -1.0f;

    if (frame >= 8) {
        frame = 7;
    } else if (frame < 0) {
        frame = 0;
    }
    entry = &m252_backFrameTbl[frame];
    HuSprPosSet(group, 0, x, scrollY);
    HuSprGrpMemberSet(group, 0, m252_sprTbl[entry->sprite], entry->frame);
    HuSprPatNoSet(group, 0, entry->frame);
    HuSprPosSet(group, 1, x + signX * 320.0f, scrollY);
    HuSprGrpMemberSet(group, 1, m252_sprTbl[entry->sprite], entry->frame);
    HuSprPatNoSet(group, 1, entry->frame);

    if (signY >= 0.0f) {
        frame++;
    } else {
        frame--;
    }
    if (frame >= 8) {
        frame = 7;
    } else if (frame < 0) {
        frame = 0;
    }
    entry = &m252_backFrameTbl[frame];
    HuSprPosSet(group, 2, x, scrollY - signY * 120.0f);
    HuSprGrpMemberSet(group, 2, m252_sprTbl[entry->sprite], entry->frame);
    HuSprPatNoSet(group, 2, entry->frame);
    HuSprPosSet(group, 3, x + signX * 320.0f, scrollY - signY * 120.0f);
    HuSprGrpMemberSet(group, 3, m252_sprTbl[entry->sprite], entry->frame);
    HuSprPatNoSet(group, 3, entry->frame);
}

void m252_ScoreInit(void) {
    HuSprAnimData *anim;
    BowserTossScore *bowser;
    s32 i;
    s32 j;

    m252_sprTbl[6] = m252_SprAnimRead(0x31);
    m252_sprTbl[7] = m252_SprAnimRead(0x55000B);
    m252_sprTbl[8] = m252_SprAnimRead(0x55000C);
    anim = HuSprAnimDataGet(m252_sprTbl[8]);
    for (i = 0; i < anim->patNum; i++) {
        anim->pat[i].centerX = 8;
        anim->pat[i].centerY = 8;
    }
    m252_sprTbl[9] = m252_SprAnimRead(0x32);
    m252_sprTbl[10] = m252_SprAnimRead(0x55000D);
    anim = HuSprAnimDataGet(m252_sprTbl[10]);
    for (i = 0; i < anim->patNum; i++) {
        anim->pat[i].centerX = 8;
        anim->pat[i].centerY = 8;
    }

    m252_scoreTbl = HuMemAllocTag(sizeof(BowserTossScore) * 3, TAG_OVERLAY);
    for (i = 0, bowser = m252_scoreTbl; i < 3; i++, bowser++) {
        bowser->timer = 0;
        if (i != 2) {
            bowser->state = 0;
            bowser->unk_0C = 0;
            bowser->unk_08 = 0;
        } else {
            bowser->state = 0x10;
            bowser->unk_08 = bowser->unk_0C = m252_recordDist;
        }
        bowser->spriteId = HuSprGrpCreate(8, 0);
        for (j = 0; j < 8; j++) {
            switch (j) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 7:
                    if (i != 2) {
                        HuSprGrpMemberSet(bowser->spriteId, j, m252_sprTbl[6], 0);
                    } else {
                        HuSprGrpMemberSet(bowser->spriteId, j, m252_sprTbl[9], 0);
                    }
                    HuSprScaleSet(bowser->spriteId, j, 1.2f, 1.2f);
                    break;
                case 4:
                case 5:
                    if (i != 2) {
                        HuSprGrpMemberSet(bowser->spriteId, j, m252_sprTbl[8], 0);
                    } else {
                        HuSprGrpMemberSet(bowser->spriteId, j, m252_sprTbl[10], 0);
                    }
                    if ((i != 2) & (j == 5)) {
                        HuSprScaleSet(bowser->spriteId, j, 0.88f, 0.88f);
                    }
                    break;
                case 6:
                default:
                    HuSprGrpMemberSet(bowser->spriteId, j, m252_sprTbl[7], 0);
                    HuSprScaleSet(bowser->spriteId, j, 0.75f, 0.75f);
                    break;
            }
            HuSprAnimModeSet(bowser->spriteId, j, HUSPR_ANIM_MODE_STOP);
            HuSprPatNoSet(bowser->spriteId, j, 0);
            HuSprAttrSet(bowser->spriteId, j, 0x903C);
        }
    }
    omAddObj(0x3F, 0, 0, -1, m252_ScoreObjMain);
}

void m252_ScoreObjMain(omObjData *object) {
    s32 digits[5];
    BowserTossScore *bowser;
    BowserTossScore *other;
    s32 i;
    s32 j;
    s32 done;
    s32 value;
    f32 t;
    f32 center;
    f32 dy;
    f32 dx;

    for (i = 0, bowser = m252_scoreTbl; i < 3; i++, bowser++) {
        done = 0;
        switch (bowser->state) {
            case 1:
                HuSprPosSet(bowser->spriteId, 6, m252_scoreDigitPosTbl[i][6].x, m252_scoreDigitPosTbl[i][6].y);
                HuSprTPLvlSet(bowser->spriteId, 6, 0);
                HuSprDispOn(bowser->spriteId, 6);
                bowser->state = 2;
                bowser->timer = 0;
                break;
            case 2:
                t = bowser->timer / 15.0f;
                HuSprTPLvlSet(bowser->spriteId, 6, (u16)(t * 256.0f));
                if (bowser->timer >= 15.0f) {
                    HuSprTPLvlSet(bowser->spriteId, 6, 256);
                    bowser->state = 0x1F;
                    bowser->timer = 0;
                }
                break;
            case 3:
                for (j = 0; j < 6; j++) {
                    HuSprPosSet(bowser->spriteId, j, m252_scoreDigitPosTbl[i][j].x, m252_scoreDigitPosTbl[i][j].y);
                    HuSprDispOn(bowser->spriteId, j);
                }
                HuSprPosSet(bowser->spriteId, 7, m252_scoreDigitPosTbl[i][7].x, m252_scoreDigitPosTbl[i][7].y);
                HuSprPatNoSet(bowser->spriteId, 4, 1);
                HuSprPatNoSet(bowser->spriteId, 5, 0);
                bowser->state = 4;
                bowser->timer = 0;
                break;
            case 4:
                bowser->unk_0C += 333;
                if (bowser->unk_08 < bowser->unk_0C) {
                    bowser->unk_0C = bowser->unk_08;
                    done = 1;
                }
                value = bowser->unk_0C;
                for (j = 0; j < 5; j++) {
                    digits[j] = value / m252_digitDivTbl[j];
                    value -= digits[j] * m252_digitDivTbl[j];
                    if (digits[j] >= 10) {
                        digits[j] = 9;
                    } else if (digits[j] < 0) {
                        digits[j] = 0;
                    }
                    if (j == 0) {
                        if (digits[0] > 0) {
                            HuSprDispOn(bowser->spriteId, 7);
                        }
                        HuSprPatNoSet(bowser->spriteId, 7, (s16)digits[j]);
                    } else {
                        HuSprPatNoSet(bowser->spriteId, j - 1, (s16)digits[j]);
                    }
                }
                if (done) {
                    if (m252_scoreSeNo != -1) {
                        if (i == 0) {
                            other = &m252_scoreTbl[1];
                        } else {
                            other = &m252_scoreTbl[0];
                        }
                        if (other->state != 3 && other->state != 4) {
                            HuAudFXPlay(0x4AC);
                            m252_scoreSeNo = -1;
                        }
                    }
                    bowser->state = 5;
                    bowser->timer = 0;
                }
                break;
            case 5:
                if (bowser->timer >= 15.0f) {
                    bowser->state = 0x1F;
                    bowser->timer = 0;
                }
                break;
            case 16:
                for (j = 0; j < 6; j++) {
                    HuSprPosSet(bowser->spriteId, j, m252_scoreDigitPosTbl[i][j].x, m252_scoreDigitPosTbl[i][j].y);
                    HuSprDispOn(bowser->spriteId, j);
                }
                HuSprPosSet(bowser->spriteId, 7, m252_scoreDigitPosTbl[i][7].x, m252_scoreDigitPosTbl[i][7].y);
                HuSprPatNoSet(bowser->spriteId, 4, 1);
                HuSprPatNoSet(bowser->spriteId, 5, 0);
                value = bowser->unk_0C;
                for (j = 0; j < 5; j++) {
                    digits[j] = value / m252_digitDivTbl[j];
                    value -= digits[j] * m252_digitDivTbl[j];
                    if (digits[j] >= 10) {
                        digits[j] = 9;
                    } else if (digits[j] < 0) {
                        digits[j] = 0;
                    }
                    if (j == 0) {
                        if (digits[0] > 0) {
                            HuSprDispOn(bowser->spriteId, 7);
                        }
                        HuSprPatNoSet(bowser->spriteId, 7, (s16)digits[j]);
                    } else {
                        HuSprPatNoSet(bowser->spriteId, j - 1, (s16)digits[j]);
                    }
                }
                bowser->state = 0x40;
                bowser->timer = 0;
                break;
            case 18:
                value = bowser->unk_0C;
                for (j = 0; j < 5; j++) {
                    digits[j] = value / m252_digitDivTbl[j];
                    value -= digits[j] * m252_digitDivTbl[j];
                    if (digits[j] >= 10) {
                        digits[j] = 9;
                    } else if (digits[j] < 0) {
                        digits[j] = 0;
                    }
                    if (j == 0) {
                        if (digits[0] > 0) {
                            HuSprDispOn(bowser->spriteId, 7);
                        }
                        HuSprPatNoSet(bowser->spriteId, 7, (s16)digits[j]);
                    } else {
                        HuSprPatNoSet(bowser->spriteId, j - 1, (s16)digits[j]);
                    }
                }
                bowser->state = 0x13;
                bowser->timer = 0;
            case 19:
                center = 0.0f;
                for (j = 0; j < 6; j++) {
                    center += m252_scoreDigitPosTbl[i][j].x;
                }
                center += m252_scoreDigitPosTbl[i][7].x;
                center /= 7.0f;
                t = bowser->timer / 15.0f;
                if (t < 0.0f) {
                    t = 0.0f;
                } else if (t > 1.0f) {
                    t = 1.0f;
                }
                t = sindf(t * 180.0f);
                dx = m252_scoreDigitPosTbl[i][7].x - center;
                HuSprPosSet(bowser->spriteId, 7, center + dx * (t + 1.0f), m252_scoreDigitPosTbl[i][7].y);
                HuSprScaleSet(bowser->spriteId, j, t * 1.2f + 1.2, t * 1.2f + 1.2);
                for (j = 0; j < 6; j++) {
                    dx = m252_scoreDigitPosTbl[i][j].x - center;
                    HuSprPosSet(bowser->spriteId, j, center + dx * (t + 1.0f), m252_scoreDigitPosTbl[i][j].y);
                    if (j < 4) {
                        HuSprScaleSet(bowser->spriteId, j, t * 1.2f + 1.2, t * 1.2f + 1.2);
                    } else {
                        HuSprScaleSet(bowser->spriteId, j, t + 1.0, t + 1.0);
                    }
                }
                if (bowser->timer >= 15.0f) {
                    bowser->state = 0x40;
                    bowser->timer = 0;
                }
                break;
            case 32:
                t = bowser->timer / 15.0f;
                center = m252_InterpCalc(t, 0.0f, 81.0f);
                dy = m252_InterpCalc(t, 0.0f, -35.0f);
                for (j = 0; j < 8; j++) {
                    HuSprPosSet(bowser->spriteId, j, m252_scoreDigitPosTbl[i][j].x + (s16)center,
                                m252_scoreDigitPosTbl[i][j].y + (s16)dy);
                }
                if (bowser->timer >= 15.0f) {
                    bowser->state = 0x40;
                    bowser->timer = 0;
                }
                break;
            case 0x40:
                break;
        }
        bowser->timer++;
    }
}

void m252_ScoreSet(s16 index, s32 score) {
    BowserTossScore *bowser = &m252_scoreTbl[index];

    if (score == 0) {
        bowser->state = 1;
    } else if (index < 2) {
        bowser->state = 3;
        bowser->timer = 0;
        bowser->unk_08 = score;
        bowser->unk_0C = 0;
        if (m252_scoreSeNo == -1) {
            m252_scoreSeNo = HuAudFXPlay(0x4AB);
        }
    } else {
        bowser->state = 0x12;
        bowser->timer = 0;
        bowser->unk_08 = bowser->unk_0C = score;
    }
}

s16 m252_ScoreAllCountCheck(void) {
    s32 i;
    BowserTossScore *p;

    for (i = 0, p = m252_scoreTbl; i < 2; i++, p++) {
        if (p->state < 0x1F) {
            return 0;
        }
    }
    return 1;
}

void m252_ScoreAllEndStart(void) {
    s32 i;
    BowserTossScore *bowser;

    for (i = 0, bowser = m252_scoreTbl; i < 2; i++, bowser++) {
        bowser->state = 0x20;
        bowser->timer = 0;
    }
}

s16 m252_ScoreAllEndCheck(void) {
    s32 i;
    BowserTossScore *p;

    for (i = 0, p = m252_scoreTbl; i < 2; i++, p++) {
        if (p->state < 0x40) {
            return 0;
        }
    }
    return 1;
}

void m252_CameraInit(void) {
    BowserTossCamera *cam;
    HuCamera *camera;
    s32 i;
    s32 j;

    m252_cameraMoveTbl = HuMemAllocTag(sizeof(BowserTossCamera) * 2, TAG_OVERLAY);
    memset(m252_cameraMoveTbl, 0, sizeof(BowserTossCamera) * 2);
    Center.x = 0.0f;
    Center.y = 212.0f;
    Center.z = 0.0f;
    CRot.x = 1.01f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 1222.0f;
    m252_cameraCenterMin.x = 0.0f;
    m252_cameraCenterMin.y = 162.0f;
    m252_cameraCenterMin.z = 0.0f;
    for (i = 0, cam = m252_cameraMoveTbl; i < 2; i++, cam++) {
        CenterM[i].x = Center.x;
        CenterM[i].y = Center.y;
        CenterM[i].z = Center.z;
        CRotM[i].x = CRot.x;
        CRotM[i].y = CRot.y;
        CRotM[i].z = CRot.z;
        CZoomM[i] = CZoom;
        m252_CameraKeyStore(i, 0);
        m252_CameraKeyStore(i, 1);
        cam->frame = cam->frames = cam->active = 0;
        camera = &gCameraList[i];
        for (j = 0; j < Hu3DBufNum; j++) {
            camera->viewports[j].vp.vscale[0] = camera->screenScale.x;
            camera->viewports[j].vp.vscale[1] = camera->screenScale.y;
            camera->viewports[j].vp.vscale[2] = camera->screenScale.z;
            camera->viewports[j].vp.vtrans[0] = camera->screenPos.x;
            camera->viewports[j].vp.vtrans[1] = camera->screenPos.y;
            camera->viewports[j].vp.vtrans[2] = camera->screenPos.z;
        }
    }
    omAddObj(0x1F, 0, 0, -1, m252_CameraMoveObjMain);
}

void m252_CameraDebugPad(void) {
    MgCameraKey delta = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed;
    s32 cam;
    s32 index;
    s32 i;
    Vec *center;
    Vec *rot;

    speed = 1.0f;
    cam = -1;
    switch (m252_cameraDebugMode) {
        case 1:
            if ((u16)HuPadBtn[0] & A_BUTTON) {
                speed = 8.0f;
            }
            if (HuPadBtn[0] & B_BUTTON) {
                speed = 0.5f;
            }
            if (HuPadBtnDown[0] & START_BUTTON) {
                CenterM[m252_cameraDebugNo].x = Center.x;
                CenterM[m252_cameraDebugNo].y = Center.y;
                CenterM[m252_cameraDebugNo].z = Center.z;
                CRotM[m252_cameraDebugNo].x = CRot.x;
                CRotM[m252_cameraDebugNo].y = CRot.y;
                CRotM[m252_cameraDebugNo].z = CRot.z;
                CZoomM[m252_cameraDebugNo] = CZoom;
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
                delta.center.x += CenterM[m252_cameraDebugNo].x;
                delta.center.y += CenterM[m252_cameraDebugNo].y;
                delta.center.z += CenterM[m252_cameraDebugNo].z;
                delta.rot.x += CRotM[m252_cameraDebugNo].x;
                delta.rot.y += CRotM[m252_cameraDebugNo].y;
                delta.rot.z += CRotM[m252_cameraDebugNo].z;
                delta.zoom += CZoomM[m252_cameraDebugNo];
                m252_CameraMoveStart(m252_cameraDebugNo, delta.center.x, delta.center.y, delta.center.z,
                                          delta.rot.x, delta.rot.y, delta.rot.z, delta.zoom, 1);
            }
            index = m252_cameraDebugNo;
            fontcolor = 15;
            cam = index;
            if (HuPadBtnDown[0] & R_TRIG) {
                if (++m252_cameraDebugNo >= 2) {
                    m252_cameraDebugNo = 0;
                    m252_cameraDebugMode++;
                }
                HuPadBtnDown[0] &= ~R_TRIG;
            }
            break;
        case 2:
            if ((HuPadBtn[0] & R_JPAD) || (HuPadBtn[0] & R_CBUTTONS)) {
                m252_cameraDebugX++;
            }
            if (HuPadBtn[0] & (L_JPAD | L_CBUTTONS)) {
                m252_cameraDebugX--;
            }
            if (HuPadBtn[0] & (D_JPAD | D_CBUTTONS)) {
                m252_cameraDebugY++;
            }
            if (HuPadBtn[0] & (U_JPAD | U_CBUTTONS)) {
                m252_cameraDebugY--;
            }
            fontcolor = 8;
            cam = 1;
            break;
        case 3:
            m252_cameraDebugMode = 0;
            break;
    }
    if (cam != -1) {
        center = &CenterM[cam];
        rot = &CRotM[cam];
        sprintf(omDBGStrBuf, "CAMERA TEST_MODE CAM_%d ", cam);
        print8((s16)m252_cameraDebugX + 20, (s16)m252_cameraDebugY + 80, omDBGStrBuf);
        sprintf(omDBGStrBuf, " CENTER X>%3.2f Y>%3.2f Z>%3.2f ", center->x, center->y, center->z);
        print8((s16)m252_cameraDebugX + 20, (s16)m252_cameraDebugY + 88, omDBGStrBuf);
        sprintf(omDBGStrBuf, " ROT    X>%3.2f Y>%3.2f Z>%3.2f ", rot->x, rot->y, rot->z);
        print8((s16)m252_cameraDebugX + 20, (s16)m252_cameraDebugY + 96, omDBGStrBuf);
        sprintf(omDBGStrBuf, " ZOOM   %3.2f ", CZoomM[cam]);
        print8((s16)m252_cameraDebugX + 20, (s16)m252_cameraDebugY + 104, omDBGStrBuf);
    }
    if (HuPadBtnDown[0] & R_TRIG) {
        if (m252_cameraDebugMode == 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            for (i = 0; i < 2; i++) {
                center = &CenterM[i];
                rot = &CRotM[i];
                osSyncPrintf("CAMERA_NO %d \n", i);
                osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", center->x, center->y, center->z);
                osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", rot->x, rot->y, rot->z);
                osSyncPrintf(" ZOOM   %3.3f \n", CZoom);
            }
            osSyncPrintf(" \n");
        }
        if (m252_cameraDebugMode++ >= 4) {
            m252_cameraDebugMode = 0;
        }
    }
}

void m252_CameraMoveObjMain(omObjData *object) {
    BowserTossCamera *cam;
    Vec *center;
    Vec *rot;
    f32 t;
    s32 i;

    for (i = 0, cam = m252_cameraMoveTbl; i < 2; i++, cam++) {
        center = &CenterM[i];
        rot = &CRotM[i];
        if (cam->frames <= 0) {
            m252_CameraPosUpdate(i);
            cam->active = 0;
            continue;
        }
        if (cam->frame == 0) {
            center->x = cam->keys[0].center.x;
            center->y = cam->keys[0].center.y;
            center->z = cam->keys[0].center.z;
            rot->x = cam->keys[0].rot.x;
            rot->y = cam->keys[0].rot.y;
            rot->z = cam->keys[0].rot.z;
            CZoomM[i] = cam->keys[0].zoom;
            cam->frames = 0;
        } else {
            t = 1.0f - (f32)cam->frame / (f32)cam->frames;
            center->x = m252_InterpCalc(t, cam->keys[1].center.x, cam->keys[0].center.x);
            center->y = m252_InterpCalc(t, cam->keys[1].center.y, cam->keys[0].center.y);
            center->z = m252_InterpCalc(t, cam->keys[1].center.z, cam->keys[0].center.z);
            rot->x = m252_AngleInterpCalc(t, cam->keys[1].rot.x, cam->keys[0].rot.x);
            rot->y = m252_AngleInterpCalc(t, cam->keys[1].rot.y, cam->keys[0].rot.y);
            rot->z = m252_AngleInterpCalc(t, cam->keys[1].rot.z, cam->keys[0].rot.z);
            CZoomM[i] = m252_InterpCalc(t, cam->keys[1].zoom, cam->keys[0].zoom);
            if (cam->frame > 0) {
                cam->frame--;
            } else {
                cam->frame++;
            }
        }
        if (rot->x >= 360.0) {
            rot->x -= 360.0;
        } else if (rot->x < 0.0) {
            rot->x += 360.0;
        }
        if (rot->y >= 360.0) {
            rot->y -= 360.0;
        } else if (rot->y < 0.0) {
            rot->y += 360.0;
        }
        if (rot->z >= 360.0) {
            rot->z -= 360.0;
        } else if (rot->z < 0.0) {
            rot->z += 360.0;
        }
        cam->active = 1;
        m252_CameraPosUpdate(i);
    }
}

void m252_CameraKeyStore(s32 camIndex, s32 key) {
    BowserTossCamera *cam = &m252_cameraMoveTbl[camIndex];
    Vec *center = &CenterM[camIndex];
    Vec *rot = &CRotM[camIndex];

    if (rot->x >= 360.0) {
        rot->x -= 360.0;
    } else if (rot->x < 0.0) {
        rot->x += 360.0;
    }
    if (rot->y >= 360.0) {
        rot->y -= 360.0;
    } else if (rot->y < 0.0) {
        rot->y += 360.0;
    }
    if (rot->z >= 360.0) {
        rot->z -= 360.0;
    } else if (rot->z < 0.0) {
        rot->z += 360.0;
    }
    cam->keys[key].center.x = center->x;
    cam->keys[key].center.y = center->y;
    cam->keys[key].center.z = center->z;
    cam->keys[key].rot.x = rot->x;
    cam->keys[key].rot.y = rot->y;
    cam->keys[key].rot.z = rot->z;
    cam->keys[key].zoom = CZoomM[camIndex];
    cam->keys[key].unk_1C = cam->keys[key].unk_20 = 0.0f;
}

// Passing CAMERA_KEEP for a component keeps its current value.
void m252_CameraMoveStart(s32 camIndex, f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames) {
    BowserTossCamera *cam = &m252_cameraMoveTbl[camIndex];
    Vec *center = &CenterM[camIndex];
    Vec *rot = &CRotM[camIndex];

    if (frames > 0) {
        cam->frame = frames - 1;
        cam->frames = frames;
        if (x != CAMERA_KEEP) {
            cam->keys[0].center.x = x;
        } else {
            cam->keys[0].center.x = center->x;
        }
        if (y != CAMERA_KEEP) {
            cam->keys[0].center.y = y;
        } else {
            cam->keys[0].center.y = center->y;
        }
        if (z != CAMERA_KEEP) {
            cam->keys[0].center.z = z;
        } else {
            cam->keys[0].center.z = center->z;
        }
        if (rotX != CAMERA_KEEP) {
            cam->keys[0].rot.x = rotX;
        } else {
            cam->keys[0].rot.x = rot->x;
        }
        if (rotY != CAMERA_KEEP) {
            cam->keys[0].rot.y = rotY;
        } else {
            cam->keys[0].rot.y = rot->y;
        }
        if (rotZ != CAMERA_KEEP) {
            cam->keys[0].rot.z = rotZ;
        } else {
            cam->keys[0].rot.z = rot->z;
        }
        if (zoom != CAMERA_KEEP) {
            cam->keys[0].zoom = zoom;
        } else {
            cam->keys[0].zoom = CZoomM[camIndex];
        }
        m252_CameraKeyStore(camIndex, 1);
    }
}

void m252_CameraPosUpdate(s32 camIndex) {
    HuCamera *camera = &gCameraList[camIndex];
    f32 rotX = CRotM[camIndex].x;
    f32 rotY = CRotM[camIndex].y;

    camera->pos.x = sindf(rotY) * cosdf(rotX) * CZoomM[camIndex] + CenterM[camIndex].x;
    camera->pos.y = -sindf(rotX) * CZoomM[camIndex] + CenterM[camIndex].y;
    camera->pos.z = cosdf(rotY) * cosdf(rotX) * CZoomM[camIndex] + CenterM[camIndex].z;
    camera->at.x = CenterM[camIndex].x;
    camera->at.y = CenterM[camIndex].y;
    camera->at.z = CenterM[camIndex].z;
    camera->up.x = sindf(rotY) * sindf(rotX);
    camera->up.y = cosdf(rotX);
    camera->up.z = cosdf(rotY) * sindf(rotX);
}

f32 m252_AngleDiffCalc(f32 arg0, f32 arg1) {
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

f32 m252_AngleStepCalc(f32 target, f32 current, f32 step) {
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

f32 m252_InterpCalc(f32 t, f32 start, f32 end) {
    return start + t * (end - start);
}

f32 m252_AngleInterpCalc(f32 t, f32 start, f32 end) {
    return m252_AngleStepCalc(end, start, fabsf(m252_AngleDiffCalc(end, start) * t));
}

void m252_MtxInterpCalc(f32 *arg0, f32 *arg1, f32 *arg2, f32 arg3) {
    s32 i;

    for (i = 0; i < 16; i++) {
        arg2[i] = arg0[i] + arg3 * (arg1[i] - arg0[i]);
    }
}

void m252_WorkPtrSet(omObjData *obj, u32 arg1) {
    obj->work[0] = arg1 >> 24;
    obj->work[1] = (arg1 >> 16) & 0xFF;
    obj->work[2] = (arg1 >> 8) & 0xFF;
    obj->work[3] = arg1 & 0xFF;
}

BowserTossPlayer *m252_WorkPtrGet(omObjData *object) {
    BowserTossWorkBytes packed;

    packed.bytes.byte3 = (u8)object->work[0];
    packed.bytes.byte2 = (u8)object->work[1];
    packed.bytes.byte1 = (u8)object->work[2];
    packed.bytes.byte0 = (u8)object->work[3];
    return (BowserTossPlayer *)packed.word;
}

BowserTossHookBake *m252_HookMtxBake(s16 model, s16 step, const char *hookName, s16 shape, s16 frame) {
    HmfModelData_Unk64_Unk8C_Struct *motion;
    HmfData *hmf;
    s16 node;
    BowserTossHookBake *item;

    if (shape) {
        motion = &Hu3DMotion[Hu3DData[model].motIdShape];
    } else {
        motion = &Hu3DMotion[Hu3DData[model].motId];
    }
    hmf = Hu3DData[model].hmf;
    node = SearchObjectIndex(hmf, hookName);
    item = HuMemAlloc(sizeof(BowserTossHookBake));
    item->mtx = HuMemAlloc((motion->unk02 + step) / step * sizeof(HuMtx4F));
    item->nodes = HuMemAlloc(hmf->unk16 * sizeof(s16));
    item->frames = motion->unk02;
    item->step = step;
    m252_HookMtxBakeNode(model, step, item, node, shape, frame);
    return item;
}

void m252_HookMtxBakeNode(s16 model, s16 step, BowserTossHookBake *item, s16 node, s16 shape, s16 frame) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_Unk64_Unk8C_Struct *motion = &Hu3DMotion[Hu3DData[model].motId];
    HmfModelData_Unk64_Unk8C_Struct *shapeMotion = &Hu3DMotion[Hu3DData[model].motIdShape];
    s16 i;

    motionBakeMtx = item->mtx;
    motionBakeNodeMap = item->nodes;
    motionBakeMtxCnt = 0;
    guMtxIdentF(Hu3DObjMtxStack[0]);
    if (shape) {
        for (i = 0; i < shapeMotion->unk02; i += step) {
            Hu3DMotionExec(hmf, frame, motion, 1);
            Hu3DMotionExec(hmf, i, shapeMotion, 0);
            Hu3DObjMtxStackIdx = 0;
            objMtxCalcFrame(hmf, 0, node);
        }
    } else {
        for (i = 0; i < motion->unk02; i += step) {
            Hu3DMotionExec(hmf, i, motion, 1);
            Hu3DMotionExec(hmf, frame, shapeMotion, 0);
            Hu3DObjMtxStackIdx = 0;
            objMtxCalcFrame(hmf, 0, node);
        }
    }
}

void m252_HookMtxFree(BowserTossHookBake *item) {
    HuMemFree(item->mtx);
    HuMemFree(item->nodes);
    HuMemFree(item);
}

s32 m252_BillboardColorMdlCreate(HuSprAnimData *sprite, u8 *color, u8 antialias) {
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
    m252_BillboardVtxCreate(sprite, data, 1.0f, 0, 0);
    gSPDisplayList(header, osVirtualToPhysical(m252_gfxBillboardInit));
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
    if (antialias) {
        gDPSetRenderMode(gfx++, G_RM_AA_ZB_XLU_SURF, G_RM_NOOP2);
    } else {
        gDPSetRenderMode(gfx++, G_RM_ZB_CLD_SURF, G_RM_NOOP2);
    }
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

s32 m252_BillboardColorMdlLink(HuSprAnimData *sprite, u16 model, u8 *color) {
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

void m252_BillboardColorPatSet(u16 model, HuSprAnimData *sprite, u16 frame, u8 *color) {
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

s32 m252_BillboardVtxCreate(HuSprAnimData *sprite, HmfData *data, f32 scale, s16 xOffset, s16 yOffset) {
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
