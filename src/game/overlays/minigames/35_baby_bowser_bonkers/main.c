#include "common.h"
#include "game/overlays/minigame.h"
#include "game/overlays/mgcamera.h"
#include "gcc/memory.h"
#include "game/mallocblock.h"
#include "game/pause.h"
#include "game/input.h"
#include "math.h"
#include "game/data.h"
#include "game/sprite.h"

typedef struct BabyBowserBonkersScore { // 0x12 bytes
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08[2]; // digit x offsets
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
} BabyBowserBonkersScore;

typedef struct BabyBowserBonkersPlayer { // 0x50 bytes, 2 entries
    s16 unk_00;                          // player index
    s16 unk_02;                          // steps taken
    s16 unk_04;                          // whose turn
    s16 unk_06;
    f32 unk_08;
    s32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    Vec unk_1C;
    s16 unk_28; // GwPlayer index
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
    s16 unk_32;
    s16 unk_34;
    s16 unk_36;
    f32 unk_38;
    s16 unk_3C;
    s16 unk_3E;
    s16 unk_40;
    s16 unk_42;
    f32 unk_44;
    f32 unk_48;
    s16 unk_4C;
} BabyBowserBonkersPlayer;

typedef struct BabyBowserBonkersKoopaJr { // 0x30 bytes, 0xE entries
    s16 unk_00;
    s16 unk_02; // model index
    s16 unk_04;
    s16 unk_06; // state
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    f32 unk_14; // wobble amplitude
    f32 unk_18; // timer
    f32 unk_1C;
    f32 unk_20;
    f32 unk_24;
    void (*unk_28)(struct BabyBowserBonkersKoopaJr *); // previous callback
    void (*unk_2C)(struct BabyBowserBonkersKoopaJr *); // callback
} BabyBowserBonkersKoopaJr;

typedef struct BabyBowserBonkersStageWork {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xAF];
} BabyBowserBonkersStageWork; // sizeof 0xB4

typedef struct BabyBowserBonkersSpawn {
    s16 unk_00; // time
    s16 unk_02; // actor index
} BabyBowserBonkersSpawn;

typedef struct BabyBowserBonkersPattern {
    s16 unk_00; // duration
    s16 unk_02;
    s16 unk_04;
    s16 unk_06; // spawn count
    BabyBowserBonkersSpawn *unk_08;
} BabyBowserBonkersPattern;

typedef union BabyBowserBonkersBytes { // packs the top byte of each work word
    u32 word;
    struct {
        u32 byte3 : 8;
        u32 byte2 : 8;
        u32 byte1 : 8;
        u32 byte0 : 8;
    } bytes;
} BabyBowserBonkersBytes;

extern const s16 m253_startMesTbl[];
extern const s16 m253_finishMesTbl[];
extern s32 omCharModelNoTbl[][6];
extern u8 omAllPauseF;
extern f32 mgPlayerSpeedMax;

Vec m253_holePosTbl[14] = {
    { -312.25f, 39.1f, -276.95f },
    { -105.35f, 39.1f, -276.95f },
    { 105.35f, 39.1f, -276.95f },
    { 312.25f, 39.1f, -276.95f },
    { -202.8f, 39.1f, -75.6f },
    { 3.05f, 39.1f, -75.6f },
    { 208.8f, 39.1f, -75.6f },
    { -302.8f, 39.1f, 127.8f },
    { -104.7f, 39.1f, 127.8f },
    { 104.7f, 39.1f, 127.8f },
    { 302.8f, 39.1f, 127.8f },
    { -202.8f, 39.1f, 321.5f },
    { 3.05f, 39.1f, 321.5f },
    { 208.8f, 39.1f, 321.5f }
};

BabyBowserBonkersSpawn m253_spawn00Tbl[6] = { { 6, 4 }, { 12, 5 }, { 18, 6 }, { 6, 13 }, { 12, 12 }, { 18, 11 } };
BabyBowserBonkersPattern m253_pattern00Param = { 30, 60, 1, 6, m253_spawn00Tbl };
BabyBowserBonkersSpawn m253_spawn01Tbl[6] = { { 6, 0 }, { 12, 4 }, { 18, 1 }, { 6, 10 }, { 12, 13 }, { 18, 9 } };
BabyBowserBonkersPattern m253_pattern01Param = { 30, 60, 1, 6, m253_spawn01Tbl };
BabyBowserBonkersSpawn m253_spawn02Tbl[6] = { { 6, 3 }, { 12, 6 }, { 18, 2 }, { 6, 7 }, { 12, 11 }, { 18, 8 } };
BabyBowserBonkersPattern m253_pattern02Param = { 30, 60, 1, 6, m253_spawn02Tbl };
BabyBowserBonkersSpawn m253_spawn03Tbl[6] = { { 6, 1 }, { 12, 5 }, { 18, 2 }, { 6, 9 }, { 12, 12 }, { 18, 8 } };
BabyBowserBonkersPattern m253_pattern03Param = { 30, 60, 1, 6, m253_spawn03Tbl };
BabyBowserBonkersSpawn m253_spawn10Tbl[8] = { { 6, 0 }, { 12, 2 }, { 18, 1 }, { 24, 3 }, { 6, 10 }, { 12, 8 }, { 18, 9 }, { 24, 7 } };
BabyBowserBonkersPattern m253_pattern10Param = { 60, 54, 1, 14, m253_spawn10Tbl };
BabyBowserBonkersSpawn m253_spawn11Tbl[8] = { { 6, 3 }, { 12, 1 }, { 18, 2 }, { 24, 0 }, { 6, 7 }, { 12, 9 }, { 18, 8 }, { 24, 10 } };
BabyBowserBonkersPattern m253_pattern11Param = { 60, 54, 1, 14, m253_spawn11Tbl };
BabyBowserBonkersSpawn m253_spawn12Tbl[8] = { { 6, 0 }, { 12, 4 }, { 18, 8 }, { 24, 12 }, { 6, 13 }, { 12, 9 }, { 18, 5 }, { 24, 1 } };
BabyBowserBonkersPattern m253_pattern12Param = { 60, 54, 1, 14, m253_spawn12Tbl };
BabyBowserBonkersSpawn m253_spawn13Tbl[8] = { { 6, 3 }, { 12, 6 }, { 18, 10 }, { 24, 13 }, { 6, 11 }, { 12, 7 }, { 18, 4 }, { 24, 0 } };
BabyBowserBonkersPattern m253_pattern13Param = { 60, 54, 1, 14, m253_spawn13Tbl };
BabyBowserBonkersSpawn m253_spawn20Tbl[14] = { { 6, 0 }, { 12, 1 }, { 18, 2 }, { 24, 3 }, { 30, 6 }, { 36, 5 }, { 42, 4 }, { 6, 13 }, { 12, 12 }, { 18, 11 }, { 24, 7 }, { 30, 8 }, { 36, 9 }, { 42, 10 } };
BabyBowserBonkersPattern m253_pattern20Param = { 60, 45, 1, 14, m253_spawn20Tbl };
BabyBowserBonkersSpawn m253_spawn21Tbl[14] = { { 6, 0 }, { 12, 1 }, { 18, 2 }, { 24, 3 }, { 30, 6 }, { 36, 10 }, { 42, 13 }, { 42, 12 }, { 36, 11 }, { 30, 7 }, { 24, 4 }, { 18, 5 }, { 12, 9 }, { 6, 8 } };
BabyBowserBonkersPattern m253_pattern21Param = { 60, 45, 1, 14, m253_spawn21Tbl };
BabyBowserBonkersSpawn m253_spawn22Tbl[14] = { { 6, 0 }, { 12, 4 }, { 18, 1 }, { 24, 5 }, { 30, 2 }, { 36, 6 }, { 42, 3 }, { 6, 10 }, { 12, 13 }, { 18, 9 }, { 24, 12 }, { 30, 8 }, { 36, 11 }, { 42, 7 } };
BabyBowserBonkersPattern m253_pattern22Param = { 60, 45, 1, 14, m253_spawn22Tbl };
BabyBowserBonkersSpawn m253_spawn23Tbl[14] = { { 6, 13 }, { 12, 12 }, { 18, 11 }, { 24, 7 }, { 30, 4 }, { 36, 2 }, { 42, 1 }, { 42, 12 }, { 36, 3 }, { 30, 6 }, { 24, 10 }, { 18, 9 }, { 12, 8 }, { 6, 5 } };
BabyBowserBonkersPattern m253_pattern23Param = { 60, 45, 1, 14, m253_spawn23Tbl };
BabyBowserBonkersSpawn m253_spawn30Tbl[14] = { { 6, 13 }, { 12, 12 }, { 18, 11 }, { 6, 7 }, { 12, 4 }, { 18, 2 }, { 6, 1 }, { 12, 12 }, { 18, 3 }, { 6, 6 }, { 12, 10 }, { 18, 9 }, { 6, 8 }, { 12, 5 } };
BabyBowserBonkersPattern m253_pattern30Param = { 21, 45, 0, 14, m253_spawn30Tbl };
BabyBowserBonkersSpawn m253_spawn31Tbl[14] = { { 6, 0 }, { 12, 1 }, { 18, 2 }, { 6, 3 }, { 12, 4 }, { 18, 5 }, { 6, 6 }, { 12, 7 }, { 18, 8 }, { 6, 9 }, { 12, 10 }, { 18, 11 }, { 6, 12 }, { 12, 13 } };
BabyBowserBonkersPattern m253_pattern31Param = { 21, 45, 0, 14, m253_spawn31Tbl };
BabyBowserBonkersSpawn m253_spawn32Tbl[14] = { { 18, 0 }, { 12, 1 }, { 6, 2 }, { 18, 3 }, { 12, 4 }, { 6, 5 }, { 18, 6 }, { 12, 7 }, { 6, 8 }, { 18, 9 }, { 12, 10 }, { 6, 11 }, { 18, 12 }, { 12, 13 } };
BabyBowserBonkersPattern m253_pattern32Param = { 27, 45, 0, 14, m253_spawn32Tbl };
BabyBowserBonkersSpawn m253_spawn33Tbl[14] = { { 18, 13 }, { 12, 12 }, { 6, 11 }, { 18, 7 }, { 12, 4 }, { 6, 2 }, { 18, 1 }, { 12, 12 }, { 6, 3 }, { 6, 6 }, { 12, 10 }, { 6, 9 }, { 18, 8 }, { 12, 5 } };
BabyBowserBonkersPattern m253_pattern33Param = { 27, 45, 0, 14, m253_spawn33Tbl };
BabyBowserBonkersPattern *m253_patternGrp0Tbl[4] = { &m253_pattern00Param, &m253_pattern01Param, &m253_pattern02Param, &m253_pattern03Param };
BabyBowserBonkersPattern *m253_patternGrp1Tbl[4] = { &m253_pattern10Param, &m253_pattern11Param, &m253_pattern12Param, &m253_pattern13Param };
BabyBowserBonkersPattern *m253_patternGrp2Tbl[4] = { &m253_pattern20Param, &m253_pattern21Param, &m253_pattern22Param, &m253_pattern23Param };
BabyBowserBonkersPattern *m253_patternGrp3Tbl[4] = { &m253_pattern30Param, &m253_pattern31Param, &m253_pattern32Param, &m253_pattern33Param };
s32 m253_winAnimTbl[8] = { 0x000200A5, 0x000300A5, 0x000700A5, 0x000400A5, 0x000500A5, 0x000600A5, 0x000800A5, 0x0009001C };
s32 m253_loseAnimTbl[8] = { 0x000200A6, 0x000300A6, 0x000700A6, 0x000400A6, 0x000500A6, 0x000600A6, 0x000800A6, 0x0009001D };
BabyBowserBonkersPattern *m253_patternCur = NULL;
s16 m253_unusedNo = 0;
s32 m253_exitTimer = 0;
s32 m253_playerOrderTbl[4] = { 0, 1, 2, 3 };
Vec m253_playerPosTbl[2] = {
    { -352.8f, 39.1f, -75.6f },
    { 352.8f, 39.1f, -75.6f }
};
s32 m253_voiceChrTbl[8] = { 0x00020000, 0x00030000, 0x00070000, 0x00040000, 0x00050000, 0x00060000, 0x00080000, 0x00090000 };
s32 m253_voiceNoTbl[2] = { 0x2F, 0x30 };
s32 m253_loseMotNoTbl[2] = { 0x36, 0x37 };
f32 m253_lavaScrollX = 0.0f;
f32 m253_lavaScrollY = 0.0f;
f32 m253_lavaGlowAngle = 180.0f;
BabyBowserBonkersPattern **m253_patternGrpTbl[4] = { m253_patternGrp0Tbl, m253_patternGrp1Tbl, m253_patternGrp2Tbl, m253_patternGrp3Tbl };
s32 m253_patternNumTbl[4] = { 4, 4, 4, 4 };
s32 m253_chrIconFileTbl[8] = { 0x00210008, 0x00210009, 0x0021000A, 0x0021000B, 0x0021000C, 0x0021000D, 0x0021000E, 0x0021000F };
s32 m253_cameraDebugMode = 0;
s32 m253_cameraDebugX = 0;
s32 m253_cameraDebugY = 0;

BabyBowserBonkersKoopaJr *m253_koopaJrSortTbl[14] BSS;
omObjData *m253_mainObj BSS;
s32 m253_flag10F BSS;
s32 m253_frameCnt BSS;
s32 m253_phaseTimer BSS;
s32 m253_timer BSS;
s32 m253_phase BSS;
s32 m253_resultWait BSS;
s32 m253_ambientSeNo BSS;
BabyBowserBonkersPlayer *m253_playerWorkTbl BSS;
s16 m253_winnerChr BSS;
BabyBowserBonkersKoopaJr *m253_koopaJrTbl BSS;
u8 m253_koopaJrTblPad[4] BSS; /* Unreferenced. */
BabyBowserBonkersPattern *m253_patternOrderTbl[4][4] BSS;
s16 *m253_sprTbl BSS;
BabyBowserBonkersScore *m253_scoreTbl BSS;
MgCameraKey m253_cameraKeyTbl[2] BSS; // target, origin
s32 m253_cameraMoveTimer BSS;
s32 m253_cameraMoveTime BSS;
s32 m253_cameraMoveF BSS;
u8 m253_cameraMoveFPad[4] BSS; /* Unreferenced. */
MinigameFlow m253_mgFlow BSS;

BabyBowserBonkersPlayer *m253_WorkPtrGet(omObjData *object);
void m253_ScoreSet(s32, s16);
void m253_KoopaJrDropUpdate(BabyBowserBonkersKoopaJr *);
void m253_MainObjInit(omObjData *object);
void m253_MainObjMain(omObjData *object);
void m253_ExitObjMain(omObjData *object);
void m253_ExitCheck(omObjData *object);
void m253_PlayerObjInit(omObjData *object);
void m253_PlayerObjMain(omObjData *object);
void m253_PlayerComInput(omObjData *object);
f32 m253_AngleStepCalc(f32 target, f32 current, f32 step);
s32 m253_PlayerAirCheck(omObjData *object);
BabyBowserBonkersKoopaJr *m253_KoopaJrGet(s32 arg0);
void m253_KoopaJrDistSort(f32 x, f32 z, BabyBowserBonkersKoopaJr **list);
s32 m253_KoopaJrTimeLeftGet(s32 arg0);
s32 m253_KoopaJrStandCheck(BabyBowserBonkersKoopaJr *arg0, s32 arg1);
s32 m253_QuadrantGet(f32 arg0, f32 arg1);
s32 m253_ComTargetGet(BabyBowserBonkersKoopaJr **list, s32 count, s32 playerIndex);
s32 m253_ComStompTargetGet(BabyBowserBonkersKoopaJr **list, s32 count, s32 playerIndex);
void m253_WorkPtrSet(omObjData *arg0, u32 arg1);
void m253_PlayerPushCalc(omObjData *obj1, omObjData *obj2, Vec *vel1, Vec *vel2, s16 recursed);
void m253_PlayerMdlSwap(omObjData *arg0, s32 arg1, s32 arg2);
s32 m253_KoopaJrRiseStart(s32 arg0, s16 arg1, s16 arg2);
s32 m253_KoopaJrAllHiddenCheck(void);
void m253_CameraMoveStart(f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames);
void m253_PlayerObjCreateAll(void);
void m253_StageObjCreate(void);
void m253_StageObjInit(omObjData *object);
void m253_StageObjMain(omObjData *object);
void m253_KoopaJrInit(void);
void m253_KoopaJrObjInit(omObjData *object);
void m253_KoopaJrObjMain(omObjData *object);
void m253_KoopaJrHide(BabyBowserBonkersKoopaJr *actor);
s16 m253_KoopaJrStompCheck(BabyBowserBonkersKoopaJr *actor);
void m253_KoopaJrSquashUpdate(BabyBowserBonkersKoopaJr *actor);
void m253_KoopaJrWaitUpdate(BabyBowserBonkersKoopaJr *actor);
void m253_KoopaJrSinkUpdate(BabyBowserBonkersKoopaJr *actor);
void m253_KoopaJrRiseUpdate(BabyBowserBonkersKoopaJr *actor);
void m253_PatternOrderInit(void);
void m253_ScoreInit(void);
void m253_ScoreObjMain(omObjData *object);
void m253_ScoreCreate(s32 index, s32 chr);
void m253_CameraInit(void);
void m253_CameraMoveObjMain(omObjData *object);
void m253_CameraKeyStore(s32 arg0);
void m253_CameraPosUpdate(s32 camIndex);
f32 m253_InterpCalc(f32 t, f32 start, f32 end);
f32 m253_AngleInterpCalc(f32 t, f32 start, f32 end);

void m253_ObjectSetup(void) {
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
    m253_timer = 900;
    m253_phaseTimer = 0;
    m253_frameCnt = 0;
    m253_phase = -1;
    m253_resultWait = 0;
    m253_ambientSeNo = -1;
    m253_winnerChr = -1;
    m253_mainObj = omAddObj(0x20, 0, 0, -1, m253_MainObjInit);
    memset(&m253_mgFlow, 0, 0x28);
    m253_mgFlow.type = MINIGAME_BATTLE;
    MgFlowInit(&m253_mgFlow);
    GMesFontMesCreate(m253_startMesTbl, 1);
    GMesFontMesCreate(m253_finishMesTbl, 1);
}

void m253_MainObjInit(omObjData *object) {
    object->func = m253_MainObjMain;
    m253_StageObjCreate();
    m253_KoopaJrInit();
    m253_PlayerObjCreateAll();
    m253_ScoreInit();
    m253_CameraInit();
    if (_CheckFlag(10)) {
        m253_flag10F = 1;
    }
}

const s16 m253_startMesTbl[] = { 0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0 };

const s16 m253_finishMesTbl[] = { 0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0 };

void m253_MainObjMain(omObjData *object) {
    BabyBowserBonkersPlayer *player1;
    BabyBowserBonkersPlayer *player2;
    s32 i;
    s32 done;
    s32 group;

    done = 0;
    switch (m253_phase) {
        case -1:
            if (m253_phaseTimer > 0) {
                m253_ambientSeNo = HuAudFXPlay(0x4AE);
                WipeCreateIn(WIPE_TYPE_PREV, 16);
                m253_phaseTimer = 0;
                m253_phase++;
            }
            break;
        case 0:
            if (WipeStatGet() == 0) {
                GMesCreate(GMES_MES_MG_START);
                HuAudFXPlay(0xE);
                HuAudSeqPlay(0x36);
                m253_phase++;
            }
            break;
        case 1:
            if (GMesStatGet() == 0) {
                GMesCreate(0x1A, (m253_timer + 29) / 30, 156, 32);
                MgFlowStatSet(MG_STATE_PLAY);
                if (m253_patternCur == NULL) {
                    m253_phaseTimer = 3;
                    m253_patternCur = m253_patternOrderTbl[0][0];
                }
                m253_phase++;
            }
            break;
        case 2:
            m253_timer--;
            GMesTimerValueSet((m253_timer + 29) / 30);
            if (m253_timer <= 0) {
                m253_timer = 0;
            }
            if (m253_timer >= 60) {
                for (i = 0; i < m253_patternCur->unk_06; i++) {
                    if (m253_phaseTimer == m253_patternCur->unk_08[i].unk_00) {
                        m253_KoopaJrRiseStart(m253_patternCur->unk_08[i].unk_02, 12,
                                                          m253_patternCur->unk_02);
                    }
                }
            }
            if (m253_patternCur->unk_04 == 0 || m253_KoopaJrAllHiddenCheck() != 0) {
                done = 1;
            }
            if (m253_phaseTimer >= m253_patternCur->unk_00 && done) {
                if (m253_timer >= 600) {
                    group = 0;
                } else if (m253_timer >= 450) {
                    group = 1;
                } else {
                    group = (m253_timer < 300) ? 3 : 2;
                }
                if (++m253_resultWait >= 4) {
                    m253_resultWait = 0;
                }
                m253_phaseTimer = 0;
                m253_patternCur = m253_patternOrderTbl[group][m253_resultWait];
            }
            if (m253_timer <= 0) {
                GMesTimerEnd();
                GMesCreate(0x11);
                MgFlowStatSet(MG_STATE_FINISH);
                m253_PlayerMdlSwap(mgPlayerObjTbl[0], 0, 13);
                m253_PlayerMdlSwap(mgPlayerObjTbl[1], 0, 13);
                HuAudSeqFadeOut(120);
                m253_phaseTimer = 0;
                m253_phase++;
            }
            break;
        case 3:
            if (m253_phaseTimer == 15) {
                if (m253_ambientSeNo != -1) {
                    HuAudFXFadeOut((s16)m253_ambientSeNo, 15);
                }
                m253_ambientSeNo = -1;
            }
            if (GMesStatGet() == 0) {
                m253_phaseTimer = 0;
                m253_phase++;
            }
            break;
        case 4:
            if (m253_phaseTimer >= 15) {
                player1 = m253_WorkPtrGet(mgPlayerObjTbl[0]);
                player2 = m253_WorkPtrGet(mgPlayerObjTbl[1]);
                if (player1->unk_02 > player2->unk_02) {
                    GMesCreate(0x16, player1->unk_2C);
                    GwPlayer[player1->unk_28].bonusCoin += 10;
                    m253_winnerChr = player1->unk_2C;
                    m253_resultWait = 140;
                    player1->unk_04 = 0;
                    player2->unk_04 = 1;
                    HuAudSeqPlay(0x67);
                    m253_CameraMoveStart(mgPlayerObjTbl[0]->trans.x, mgPlayerObjTbl[0]->trans.y + 50.0,
                                                      mgPlayerObjTbl[0]->trans.z, CAMERA_KEEP, CAMERA_KEEP, CAMERA_KEEP,
                                                      600.0f, 30);
                } else if (player1->unk_02 < player2->unk_02) {
                    GMesCreate(0x16, player2->unk_2C);
                    GwPlayer[player2->unk_28].bonusCoin += 10;
                    m253_winnerChr = player2->unk_2C;
                    m253_resultWait = 140;
                    player1->unk_04 = 1;
                    player2->unk_04 = 0;
                    HuAudSeqPlay(0x67);
                    m253_CameraMoveStart(mgPlayerObjTbl[1]->trans.x, mgPlayerObjTbl[1]->trans.y + 50.0,
                                                      mgPlayerObjTbl[1]->trans.z, CAMERA_KEEP, CAMERA_KEEP, CAMERA_KEEP,
                                                      600.0f, 30);
                } else {
                    GMesCreate(0x20);
                    m253_resultWait = 144;
                    HuAudSeqPlay(0x6C);
                    player2->unk_04 = 1;
                    player1->unk_04 = 1;
                }
                MgFlowStatSet(MG_STATE_RESULT);
                m253_phaseTimer = 0;
                m253_phase++;
            }
            break;
        case 5:
            if (GMesStatGet() == 0) {
                m253_phaseTimer = 0;
                m253_phase++;
            }
            break;
        case 6:
            if (m253_phaseTimer >= 15) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 16);
                HuAudSeqFadeOut(16);
                HuAudFXAllFadeOut(16);
                m253_phaseTimer = 0;
                m253_phase++;
            }
            break;
        default:
            if (WipeStatGet() == 0) {
                object->func = m253_ExitObjMain;
            }
            break;
    }
    player1 = m253_WorkPtrGet(mgPlayerObjTbl[m253_unusedNo]);
    player2 = m253_WorkPtrGet(mgPlayerObjTbl[m253_unusedNo ^ 1]);
    m253_PlayerPushCalc(mgPlayerObjTbl[m253_unusedNo],
                                      mgPlayerObjTbl[m253_unusedNo ^ 1], &player1->unk_1C,
                                      &player2->unk_1C, 0);
    m253_unusedNo ^= 1;
    m253_ExitCheck(object);
    m253_frameCnt++;
    m253_phaseTimer++;
}

void m253_ExitObjMain(omObjData *object) {
    HuAudSeqStop();
    omOvlReturnEx(1);
}

void m253_ExitCheck(omObjData *object) {
    if (m253_exitTimer != 0) {
        if (m253_exitTimer == 1) {
            object->func = m253_ExitObjMain;
        }
        m253_exitTimer--;
        return;
    }
    if (omSysExitReq == 1 && WipeStatGet() == 0) {
        m253_exitTimer = 16;
        WipeCreateOut(WIPE_TYPE_NORMAL, (s16)m253_exitTimer);
        HuAudSeqFadeOut((s16)m253_exitTimer);
        HuAudFXAllFadeOut((s16)m253_exitTimer);
    }
}

void m253_PlayerObjCreateAll(void) {
    s32 used[2];
    BabyBowserBonkersPlayer *player;
    s32 i;
    s32 j;
    s32 k;
    s32 found;
    s32 minGroup;

    used[0] = -1;
    used[1] = -1;
    m253_playerWorkTbl = HuMemAllocTag(sizeof(BabyBowserBonkersPlayer) * 2, TAG_OVERLAY);
    player = m253_playerWorkTbl;
    memset(player, 0, sizeof(BabyBowserBonkersPlayer) * 2);
    for (i = 0; i < 2; i++) {
        for (j = 0, minGroup = 99; j < 4; j++) {
            found = 0;
            for (k = 0; k < i; k++) {
                if (used[k] == m253_playerOrderTbl[j]) {
                    found = 1;
                }
            }
            if (!found && GwPlayer[m253_playerOrderTbl[j]].group < minGroup) {
                minGroup = GwPlayer[m253_playerOrderTbl[j]].group;
                m253_playerWorkTbl[i].unk_28 = m253_playerOrderTbl[j];
            }
        }
        used[i] = m253_playerWorkTbl[i].unk_28;
    }
    MgShadowAltSet(1);
    MgPlayerParamReset();
    mgPlayerJumpPower = 1.4f;
    mgPlayerGravity = 0.14f;
    mgPlayerFallMax = 1.46f;
    for (i = 0; i < 2; i++, player++) {
        player->unk_00 = i;
        mgPlayerObjTbl[mgPlayerObjNum] = omAddObj(0x10, 14, 60, -1, m253_PlayerObjInit);
        mgPlayerObjTbl[mgPlayerObjNum]->trans.x = m253_playerPosTbl[i].x;
        mgPlayerObjTbl[mgPlayerObjNum]->trans.z = m253_playerPosTbl[i].z;
        mgPlayerObjTbl[mgPlayerObjNum]->trans.y = 39.100002f;
        m253_WorkPtrSet(mgPlayerObjTbl[mgPlayerObjNum], (u32)player);
        mgPlayerObjNum++;
    }
}

void m253_PlayerObjInit(omObjData *object) {
    BabyBowserBonkersPlayer *player;
    MgPlayerWork *data;
    s32 variant;
    s16 gwIndex;
    s16 chr;
    s16 i;
    u32 model;
    s32 motionFile;
    s32 linkModel;

    player = m253_WorkPtrGet(object);
    gwIndex = player->unk_28;
    chr = GwPlayer[gwIndex].chr;
    player->unk_2C = chr;
    player->unk_2A = GwPlayer[gwIndex].pad;
    player->unk_2E = GwPlayer[gwIndex].stat & 1;
    player->unk_30 = GwPlayer[gwIndex].cpu_difficulty;
    model = omCharModelNoTbl[chr][0];
    motionFile = omCharModelNoTbl[chr][1];
    linkModel = omCharModelNoTbl[chr][2];
    MgPlayerCreate(object, model, motionFile, gwIndex, 0x289, 0x299);
    data = object->data;
    data->unk50 &= ~1;
    data->unkEC = 0;
    object->model[3] = Hu3DModelRead(3, 0x68D);
    object->model[4] = Hu3DModelRead(4, 0x68D);
    for (i = 0; i < 3; i++) {
        object->model[7 + i] = Hu3DModelRead(8, 0x68D);
    }
    object->model[13] = Hu3DModelRead(model | linkModel, 0x28D);
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(chr, 0), 1, 0);
    MgPlayerMotLoad(object, 1, CharMotionDataNumGet(chr, 1), 1, 0);
    MgPlayerMotLoad(object, 2, CharMotionDataNumGet(chr, 2), 1, 0);
    MgPlayerMotLoad(object, 6, CharMotionDataNumGet(chr, 4), 1, 0x13);
    MgPlayerMotLoad(object, 0x11, CharMotionDataNumGet(chr, 0xE), 0, 0);
    MgPlayerMotLoad(object, 0x12, CharMotionDataNumGet(chr, 0xF), 2, 0);
    MgPlayerMotLoad(object, 0x15, CharMotionDataNumGet(chr, 0x1F), 0, 0);
    MgPlayerMotLoad(object, 0x14, CharMotionDataNumGet(chr, 0x1D), 0, 0);
    MgPlayerMotLoad(object, 4, CharMotionDataNumGet(chr, 0x1E), 1, 0);
    MgPlayerMotLoad(object, 0x20, CharMotionDataNumGet(chr, 0x22), 0, 0);
    MgPlayerMotRead(object, 0x21, CharMotionDataNumGet(chr, 0x23), 2, 0);
    MgPlayerMotLoad(object, 0x22, CharMotionDataNumGet(chr, 0x24), 2, 0);
    variant = rand8() & 1;
    MgPlayerMotLoad(object, 0xD, CharMotionDataNumGet(chr, m253_voiceNoTbl[variant]), 1, 120);
    player->unk_0C = m253_voiceChrTbl[chr] | m253_voiceNoTbl[variant];
    MgPlayerMotLoad(object, 0xE, CharMotionDataNumGet(chr, m253_loseMotNoTbl[rand8() & 1]), 1, 120);
    MgPlayerMotSet(object, 0);
    MgPlayerMapAttrSet(object, 0, 2);
    player->unk_10 = player->unk_1C.x = 0.0f;
    player->unk_02 = 0;
    player->unk_04 = -1;
    player->unk_32 = -1;
    player->unk_34 = 0;
    player->unk_36 = 0;
    player->unk_38 = 1000.0 - player->unk_30 * 225.0;
    player->unk_08 = 0.0f;
    player->unk_3C = player->unk_30 * 6 + ((rand8() & 3) + 4);
    player->unk_3E = 0;
    player->unk_40 = 0;
    player->unk_42 = 0;
    player->unk_44 = player->unk_48 = 0.0f;
    object->func = m253_PlayerObjMain;
}

void m253_PlayerObjMain(omObjData *object) {
    BabyBowserBonkersPlayer *player;
    MgPlayerWork *data;
    f32 prevRot;

    player = m253_WorkPtrGet(object);
    data = object->data;
    player->unk_10 = object->trans.x;
    player->unk_14 = object->trans.y;
    player->unk_18 = object->trans.z;
    data->unk50 |= 0x8000;
    switch (MgFlowStatGet()) {
        case MG_STATE_PLAY:
            if (data->unk38 != 1000.0f) {
                object->trans.y -= 1.5000000596046448;
            }
            if (player->unk_2E != 0) {
                m253_PlayerComInput(object);
            }
            break;
        case MG_STATE_FINISH:
            data->unk3C = m253_AngleStepCalc(0.0f, data->unk3C, 15.0f);
            break;
        case MG_STATE_RESULT:
            switch (player->unk_04) {
                case 0:
                    if (MgPlayerMotSet(object, 0xD) != 0) {
                        CharAnimCreate(object->model[0], 2, player->unk_2C,
                                           m253_winAnimTbl[player->unk_2C]);
                        HuAudCharVoicePlayPlayer(player->unk_0C, -1, player->unk_00);
                        player->unk_04 = -1;
                    }
                    break;
                case 1:
                    if (MgPlayerMotSet(object, 0xE) != 0) {
                        CharAnimCreate(object->model[0], 2, player->unk_2C,
                                           m253_loseAnimTbl[player->unk_2C]);
                        player->unk_04 = -1;
                    }
                    break;
            }
            break;
    }
    prevRot = data->unk3C;
    MgPlayerObjMain(object);
    player->unk_1C.x = object->trans.x - player->unk_10;
    player->unk_1C.y = object->trans.y - player->unk_14;
    player->unk_1C.z = object->trans.z - player->unk_18;
    data->unk3C = m253_AngleStepCalc(data->unk3C, prevRot, 30.0f);
    HuRotateRPYF(Hu3DData[object->model[0]].mtx, 0.0f, data->unk3C, 0.0f);
}

void m253_PlayerComInput(omObjData *object) {
    BabyBowserBonkersPlayer *player;
    MgPlayerWork *data;
    BabyBowserBonkersKoopaJr *actor;
    HmfModel *model;
    f32 dist;
    f32 dz;
    f32 dx;
    f32 scale;
    f32 dx2;
    f32 dz2;
    s32 ready;
    s32 count;
    s32 i;

    player = m253_WorkPtrGet(object);
    data = object->data;
    HuPadBtn[player->unk_2A] = HuPadBtnDown[player->unk_2A] = 0;
    HuPadStkX[player->unk_2A] = 0;
    HuPadStkY[player->unk_2A] = 0;
    if (m253_timer >= 450) {
        ready = player->unk_3C / 2 <= player->unk_02;
    } else {
        ready = player->unk_3C <= player->unk_02;
    }
    if (data->unk38 != 1000.0f) {
        player->unk_42 = player->unk_02;
    }
    if (player->unk_42 < player->unk_02 && (ready || player->unk_30 == 0)) {
        dx = player->unk_44 - object->trans.x;
        dz = player->unk_44 - object->trans.z;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist != 0.0f) {
            dx /= dist;
            dz /= dist;
        } else {
            dx = dz = 0.0f;
        }
        scale = dist / 100.0;
        if (scale >= 1.0f) {
            scale = 1.0f;
        }
        HuPadStkX[player->unk_2A] = dx * 64.0f * scale;
        HuPadStkY[player->unk_2A] = -(dz * 64.0f * scale);
        HuPadBtn[player->unk_2A] |= A_BUTTON;
        HuPadBtnDown[player->unk_2A] = 0;
        return;
    }
    if (ready) {
        if (player->unk_3E != 0) {
            HuPadStkX[player->unk_2A] = 0;
            HuPadStkY[player->unk_2A] = 0;
            if (!(player->unk_3E & 7) && player->unk_32 != -1) {
                HuPadBtnDown[player->unk_2A] |= A_BUTTON;
                HuPadBtn[player->unk_2A] |= A_BUTTON;
            }
            if (--player->unk_3E <= 0) {
                player->unk_40 = (u8)(rand8() % 15) + 15.0f + player->unk_30 * 5;
                player->unk_3E = 0;
            }
            return;
        }
        if (--player->unk_40 <= 0) {
            player->unk_3E = (u8)(rand8() % 15) + 15.0f - player->unk_30 * 5;
            player->unk_40 = 0;
        }
    }
    if (player->unk_32 != -1) {
        actor = m253_KoopaJrGet(player->unk_32);
        if (actor == NULL) {
            player->unk_32 = -1;
            return;
        }
        model = &Hu3DData[actor->unk_02];
        dx = model->pos.x - object->trans.x;
        dz = model->pos.z - object->trans.z;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist < 150.0 && dist > 50.0 && player->unk_34 >= 12 - player->unk_30 * 2 &&
            m253_PlayerAirCheck(object) == 0 && actor->unk_04 != 0) {
            HuPadBtnDown[player->unk_2A] |= A_BUTTON;
        }
        if (data->unk38 != 1000.0f) {
            HuPadBtn[player->unk_2A] |= A_BUTTON;
        } else if ((m253_KoopaJrTimeLeftGet(actor->unk_00) < 15.0f && player->unk_34 >= player->unk_36 &&
                    player->unk_38 <= dist) ||
                   (ready && !(rand8() & 0xF))) {
            m253_KoopaJrDistSort(object->trans.x, object->trans.z, m253_koopaJrSortTbl);
            for (i = 0; i < 14; i++) {
                if (m253_KoopaJrTimeLeftGet(m253_koopaJrSortTbl[i]->unk_00) >= 225) {
                    model = &Hu3DData[m253_koopaJrSortTbl[i]->unk_02];
                    dx2 = model->pos.x - object->trans.x;
                    dz2 = model->pos.z - object->trans.z;
                    if (sqrtf(dx2 * dx2 + dz2 * dz2) <= player->unk_38) {
                        player->unk_32 = i;
                        return;
                    }
                }
            }
        }
        if (actor->unk_06 != 4 && actor->unk_06 != 5 &&
            (actor->unk_04 != 0 || m253_PlayerAirCheck(object) != 0)) {
            if (dist != 0.0f) {
                dx /= dist;
                dz /= dist;
            } else {
                dx = dz = 0.0f;
            }
            scale = dist / 100.0;
            if (scale >= 1.0f) {
                scale = 1.0f;
            }
            HuPadStkX[player->unk_2A] = dx * 64.0f * scale;
            HuPadStkY[player->unk_2A] = -(dz * 64.0f * scale);
        } else if (player->unk_34 >= player->unk_36) {
            player->unk_32 = -1;
        } else {
            if (dist != 0.0f) {
                dx /= dist;
                dz /= dist;
            } else {
                dx = dz = 0.0f;
            }
            scale = dist / 100.0;
            if (scale >= 1.0f) {
                scale = 1.0f;
            }
            HuPadStkX[player->unk_2A] = dx * 64.0f * scale;
            HuPadStkY[player->unk_2A] = -(dz * 64.0f * scale);
        }
    } else {
        m253_KoopaJrDistSort(object->trans.x, object->trans.z, m253_koopaJrSortTbl);
        count = 7 - (s32)(player->unk_30 * 1.5f);
        if (count <= 0) {
            count = 1;
        }
        player->unk_32 = m253_ComTargetGet(m253_koopaJrSortTbl, count, player->unk_00 ^ 1);
        if (player->unk_32 == -1) {
            player->unk_32 =
                m253_ComStompTargetGet(m253_koopaJrSortTbl, count, player->unk_00 ^ 1);
        }
        player->unk_36 = 39.0f - player->unk_30 * 7.5f;
        player->unk_34 = 0;
    }
    player->unk_34++;
}

void m253_PlayerHopAdd(omObjData *arg0, f32 arg1, f32 arg2) {
    BabyBowserBonkersPlayer *player = m253_WorkPtrGet(arg0);

    player->unk_02++;
    player->unk_44 = arg1;
    player->unk_48 = arg2;
    m253_ScoreSet(player->unk_00, player->unk_02);
}

s32 m253_PlayerAirCheck(omObjData *object) {
    return object->trans.y >= 44.1000009328126907;
}

void m253_PlayerMdlSwap(omObjData *arg0, s32 arg1, s32 arg2) {
    HmfModel *model;
    HmfModel *otherModel;
    HmfData *temp;

    model = &Hu3DData[arg0->model[(s16)arg1]];
    otherModel = &Hu3DData[arg0->model[(s16)arg2]];

    temp = model->hmf;
    model->hmf = otherModel->hmf;
    otherModel->hmf = temp;
}

void m253_PlayerPushCalc(omObjData *obj1, omObjData *obj2, Vec *vel1, Vec *vel2, s16 recursed) {
    omObjData *mover;
    omObjData *other;
    MgPlayerWork *moverData;
    MgPlayerWork *otherData;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 minDist;
    f32 scale;
    f32 limit;
    f32 pushX;
    f32 pushZ;
    u16 pushed;

    pushed = 0;
    if (recursed == 0) {
        if ((vel1->x != 0.0f || vel1->z != 0.0f) && vel2->x == 0.0f && vel2->z == 0.0f) {
            mover = obj1;
            other = obj2;
        } else if ((vel2->x != 0.0f || vel2->z != 0.0f) && vel1->x == 0.0f && vel1->z == 0.0f) {
            mover = obj2;
            other = obj1;
        } else if (obj1->trans.y > obj2->trans.y) {
            mover = obj1;
            other = obj2;
        } else if (obj2->trans.y > obj1->trans.y) {
            mover = obj2;
            other = obj1;
        } else {
            mover = obj1;
            other = obj2;
        }
    } else {
        mover = obj1;
        other = obj2;
    }
    moverData = mover->data;
    otherData = other->data;
    dx = mover->trans.x - other->trans.x;
    dz = mover->trans.z - other->trans.z;
    dist = sqrtf(dx * dx + dz * dz);
    minDist = (moverData->unk48 + otherData->unk48) * 0.75f;
    if (dist < minDist && mover->trans.y >= other->trans.y &&
        mover->trans.y <= other->trans.y + otherData->unk34) {
        if (dist != 0.0f) {
            scale = minDist / dist;
        } else {
            if (minDist == 0.0f) {
                dx = dz = 0.0f;
            } else {
                if (other->trans.x >= 0.0f) {
                    dx = minDist / 1.4142f;
                } else {
                    dx = -minDist / 1.4142f;
                }
                if (other->trans.z >= 0.0f) {
                    dz = minDist / 1.4142f;
                } else {
                    dz = -minDist / 1.4142f;
                }
            }
            scale = 1.0f;
        }
        mover->trans.x = dx * scale + other->trans.x;
        mover->trans.z = dz * scale + other->trans.z;
        pushed = 1;
    }
    pushZ = 0.0f;
    pushX = 0.0f;
    limit = 469.999980926513672 - moverData->unk48;
    if (mover->trans.x > limit) {
        pushX = limit - mover->trans.x;
        mover->trans.x = limit;
    } else if (mover->trans.x < -limit) {
        pushX = -limit - mover->trans.x;
        mover->trans.x = -limit;
    }
    if (mover->trans.z > limit) {
        pushZ = limit - mover->trans.x;
        mover->trans.z = limit;
    } else if (mover->trans.z < -limit) {
        pushZ = -limit - mover->trans.x;
        mover->trans.z = -limit;
    }
    limit = 469.999980926513672 - otherData->unk48;
    if (other->trans.x > limit) {
        other->trans.x = limit;
    } else if (other->trans.x < -limit) {
        other->trans.x = -limit;
    }
    if (other->trans.z > limit) {
        other->trans.z = limit;
    } else if (other->trans.z < -limit) {
        other->trans.z = -limit;
    }
    if (pushX == 0.0f && pushZ == 0.0f) {
        return;
    }
    if (pushed) {

        dx = mover->trans.x - other->trans.x;
        dz = mover->trans.z - other->trans.z;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist < minDist && mover->trans.y >= other->trans.y &&

            mover->trans.y <= otherData->unk34 * 0.5f + other->trans.y) {
            other->trans.x += pushX;
            other->trans.z += pushZ;
            if (other->trans.x > limit) {
                other->trans.x = limit;
            } else if (other->trans.x < -limit) {
                other->trans.x = -limit;
            }
            if (other->trans.z > limit) {
                other->trans.z = limit;
            } else if (other->trans.z < -limit) {
                other->trans.z = -limit;
            }
        }
        if (recursed == 0) {
            m253_PlayerPushCalc(other, mover, NULL, NULL, 1);
        }
    }
}

void m253_StageObjCreate(void) {
    mgMapObjTbl[mgMapObjNum++] = omAddObj(1, 16, 0, -1, m253_StageObjInit);
    MgMapBaseSet(0);
}

void m253_StageObjInit(omObjData *object) {
    BabyBowserBonkersStageWork *work;

    work = HuMemAllocTag(sizeof(BabyBowserBonkersStageWork), TAG_OVERLAY);
    object->data = work;
    memset(work, 0, sizeof(BabyBowserBonkersStageWork));
    work->unk03 = 1;
    work->unk04 = 0;
    MgMapSlideSet(object, 20.0f);
    MgMapFrictionSet(object, 1.0f);
    MgMapAccelSet(object, 10.0f);
    MgMapBoxSet(object, 39.100002f, -939.99994f, -939.99994f, 939.99994f, 939.99994f);
    object->model[0] = Hu3DModelRead2(0x560000, 0x10099);
    Hu3DModelVtxBufMake(object->model[0]);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    object->model[1] = Hu3DModelRead2(0x560001, 0x99);
    object->model[2] = Hu3DModelRead2(0x560002, 0x99);
    object->func = m253_StageObjMain;
}

void m253_StageObjMain(omObjData *object) {
    Hu3DModelTexScroll(object->model[0], sindf(m253_lavaScrollX) * 15.0f,
                       -m253_lavaScrollY, 64, 64);
    Hu3DModelPrimColorSet(object->model[0], (u8)(cosdf(m253_lavaGlowAngle) * 32.0f + 32.0f), 0, 0,
                       (u8)(cosdf(m253_lavaGlowAngle) * 32.0f + 32.0f));
    Hu3DModelEnvColorSet(object->model[0], 64, 32, 32, 0);
    if (omPauseChk() + omAllPauseF == 0) {
        m253_lavaScrollX += 0.5f;
        if (m253_lavaScrollX >= 360.0f) {
            m253_lavaScrollX -= 360.0f;
        }
        m253_lavaScrollY += 0.2f;
        if (m253_lavaScrollY >= 64.0f) {
            m253_lavaScrollY -= 64.0f;
        }
        m253_lavaGlowAngle += 2.4f;
        if (m253_lavaGlowAngle >= 360.0f) {
            m253_lavaGlowAngle -= 360.0f;
        }
    }
}

s32 m253_QuadrantGet(f32 arg0, f32 arg1) {
    if (__builtin_fabs((f64)arg0) < 200.0 && __builtin_fabs((f64)arg1) < 200.0) {
        return 0;
    }
    if (arg0 > 0.0f) {
        if (arg1 > 0.0f) {
            return 1;
        }
        return 2;
    }
    if (arg1 > 0.0f) {
        return 3;
    }
    return 4;
}

void m253_KoopaJrInit(void) {
    m253_koopaJrTbl = HuMemAllocTag(sizeof(BabyBowserBonkersKoopaJr) * 14, TAG_OVERLAY);
    memset(m253_koopaJrTbl, 0, sizeof(BabyBowserBonkersKoopaJr) * 14);
    omAddObj(2, 8, 0, -1, m253_KoopaJrObjInit);
    m253_PatternOrderInit();
}

void m253_KoopaJrObjInit(omObjData *object) {
    s32 i;
    BabyBowserBonkersKoopaJr *actor;

    object->func = m253_KoopaJrObjMain;
    for (actor = m253_koopaJrTbl, i = 0; i < 14; i++, actor++) {
        if (i == 0) {
            actor->unk_02 = Hu3DModelRead2(0x560003, 0x299);
        } else {
            actor->unk_02 = Hu3DModelLink(m253_koopaJrTbl->unk_02);
        }
        actor->unk_00 = i;
        actor->unk_04 = -1;
        actor->unk_08 = 0;
        actor->unk_06 = actor->unk_0A = actor->unk_0C = actor->unk_0E = 0;
        actor->unk_10 = 0;
        actor->unk_12 = 0;
        actor->unk_14 = 0.0f;
        actor->unk_18 = 0.0f;
        actor->unk_1C = m253_holePosTbl[i].y - 110.000002384185791;
        actor->unk_20 = 65.0f;
        actor->unk_24 = 70.0f;
        actor->unk_28 = m253_KoopaJrHide;
        actor->unk_2C = m253_KoopaJrHide;
        Hu3DModelPosSet(actor->unk_02, m253_holePosTbl[i].x, m253_holePosTbl[i].y,
                        m253_holePosTbl[i].z - 20.0000002980232239);
    }
}

void m253_KoopaJrObjMain(omObjData *object) {
    s32 i;
    BabyBowserBonkersKoopaJr *actor;
    HmfModel *model;

    for (actor = m253_koopaJrTbl, i = 0; i < 14; i++, actor++) {
        model = Hu3DData + actor->unk_02;
        if (actor->unk_2C != NULL) {
            actor->unk_2C(actor);
        }
        model->pos.y = actor->unk_1C + actor->unk_18;
        if (actor->unk_04 != 0) {
            actor->unk_08 = m253_KoopaJrStompCheck(actor);
            if (actor->unk_08 != -1) {
                HuAudFXPlay(0x4AD);
                actor->unk_2C = m253_KoopaJrSquashUpdate;
            }
        }
        if (model->motSpeed < 0.0f && model->motTime + model->motSpeed <= 0.0f) {
            model->motSpeed = 0.0f;
        }
        if (actor->unk_28 == actor->unk_2C) {
            actor->unk_0A++;
        } else {
            actor->unk_28 = actor->unk_2C;
            actor->unk_0A = 0;
        }
    }
}

s16 m253_KoopaJrStompCheck(BabyBowserBonkersKoopaJr *actor) {
    s16 order[4];
    s16 i;
    HmfModel *model;
    omObjData *obj;
    MgPlayerWork *data;
    BabyBowserBonkersPlayer *player;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 radius;
    f32 speed;
    s16 stickX;
    s16 stickY;
    s16 pad;

    if (m253_frameCnt & 1) {
        for (i = 0; i < mgPlayerObjNum; i++) {
            order[i] = i;
        }
    } else {
        for (i = 0; i < mgPlayerObjNum; i++) {
            order[i] = mgPlayerObjNum - i - 1;
        }
    }
    model = Hu3DData + actor->unk_02;
    for (i = 0; i < mgPlayerObjNum; i++) {
        obj = mgPlayerObjTbl[order[i]];
        data = obj->data;
        player = m253_WorkPtrGet(obj);
        dx = obj->trans.x - model->pos.x;
        dz = obj->trans.z - model->pos.z;
        dist = sqrtf(dx * dx + dz * dz);
        radius = data->unk48 + actor->unk_20;
        if (!(obj->trans.y + data->unk34 < model->pos.y) &&
            !(actor->unk_24 * model->scale.y + model->pos.y < obj->trans.y) && dist < radius) {
            if (data->unk38 == 1000.0f) {
                obj->trans.y = actor->unk_24 * 1.2f + model->pos.y;
                MgPlayerMotForceSet(obj, 6);
                data->unk38 = -mgPlayerJumpPower;
                data->unk50 &= ~0x80;
                data->unk40 = 0.0f;
                MgPlayerEffSet(obj, player->unk_4C + 7, obj->trans.x, obj->trans.y, obj->trans.z, 0.0f, 0.0f);
                omVibrate(player->unk_28, 10, 0, 10);
                if (++player->unk_4C >= 3) {
                    player->unk_4C = 0;
                }
                m253_PlayerHopAdd(obj, model->pos.x, model->pos.z);
                return order[i];
            } else {
                obj->trans.y = actor->unk_24 * 1.2f + model->pos.y;
                pad = GwPlayer[order[i]].pad;
                stickX = HuPadStkX[pad];
                if (abs(stickX) < 9) {
                    stickX = 0;
                }
                stickY = HuPadStkY[pad];
                if (abs(stickY) < 9) {
                    stickY = 0;
                }
                if ((stickX != 0) | (stickY != 0)) {
                    if (stickX > 60) {
                        stickX = 60;
                    } else if (stickX < -60) {
                        stickX = -60;
                    }
                    if (stickY > 60) {
                        stickY = 60;
                    } else if (stickY < -60) {
                        stickY = -60;
                    }
                    data->unk3C = atan2df(stickX, -stickY) + data->unk60;
                    speed = mgPlayerSpeedMax * 0.5f;
                    data->unk40 = speed * (sqrtf(stickX * stickX + stickY * stickY) / 60.0f);
                }
                MgPlayerMotForceSet(obj, 6);
                data->unk50 &= ~0x80;
                if ((u16)HuPadBtn[pad] & A_BUTTON) {
                    data->unk38 = -mgPlayerJumpPower;
                } else {
                    data->unk38 = -mgPlayerJumpPower * 0.75f;
                }
                MgPlayerEffSet(obj, player->unk_4C + 7, obj->trans.x, obj->trans.y, obj->trans.z, 0.0f, 0.0f);
                omVibrate(player->unk_28, 10, 0, 10);
                if (++player->unk_4C >= 3) {
                    player->unk_4C = 0;
                }
                m253_PlayerHopAdd(obj, model->pos.x, model->pos.z);
                return order[i];
            }
        }
    }
    return -1;
}

void m253_KoopaJrHide(BabyBowserBonkersKoopaJr *actor) {
    HmfModel *model = Hu3DData + actor->unk_02;

    actor->unk_06 = 0;
    actor->unk_04 = 0;
    actor->unk_08 = -1;
    actor->unk_18 = 0;
    model->attr |= HU3D_ATTR_DISPOFF;
}

void m253_KoopaJrRiseUpdate(BabyBowserBonkersKoopaJr *actor) {
    HmfModel *model = Hu3DData + actor->unk_02;
    f32 t;
    f32 scale;

    actor->unk_06 = 1;
    if (actor->unk_0C != 0) {
        t = (f32)actor->unk_0A / (f32)actor->unk_0C;
    } else {
        t = 1.0f;
    }
    actor->unk_18 = t * 110.0f;
    scale = t * 0.8f + 0.2f;
    model->scale.x = scale;
    model->scale.y = scale;
    model->scale.z = scale;
    if (t > 0.3f) {
        actor->unk_04 = 0;
    } else {
        actor->unk_04 = 1;
    }
    if (actor->unk_10 != 0 && actor->unk_0A >= 7 && model->motSpeed == 0.0f) {
        if (--actor->unk_10 <= 0) {
            model->motSpeed = 1.0f;
            model->motTime = 0.0f;
        } else {
            actor->unk_0A--;
        }
    }
    if (t >= 1.0f) {
        actor->unk_0A = 0;
        actor->unk_2C = m253_KoopaJrWaitUpdate;
    }
}

void m253_KoopaJrWaitUpdate(BabyBowserBonkersKoopaJr *actor) {
    HmfModel *model = Hu3DData + actor->unk_02;

    actor->unk_06 = 2;
    actor->unk_04 = 1;
    switch (actor->unk_12) {
        case 1:
            if (actor->unk_14 < 20.0f) {
                actor->unk_14 += 2.5f;
            }
            model->rot.y = sindf((f32)actor->unk_0A / (f32)actor->unk_0E * 720.0f) * actor->unk_14;
            break;
        case 2:
        case 3:
            if (actor->unk_14 < 20.0f) {
                actor->unk_14 += 2.5f;
            }
            model->rot.y = -(sindf((f32)actor->unk_0A / (f32)actor->unk_0E * 720.0f) * actor->unk_14);
            break;
    }
    if (actor->unk_0A >= actor->unk_0E - 7 && model->motSpeed >= 0.0f) {
        model->motSpeed = -1.5f;
        model->motTime = 30.0f;
    }
    if (actor->unk_0A >= actor->unk_0E) {
        actor->unk_0A = 0;
        actor->unk_2C = m253_KoopaJrSinkUpdate;
    }
}

void m253_KoopaJrSinkUpdate(BabyBowserBonkersKoopaJr *actor) {
    HmfModel *model = Hu3DData + actor->unk_02;
    f32 t;
    f32 scale;

    actor->unk_06 = 3;
    if (actor->unk_0C != 0) {
        t = (f32)actor->unk_0A / (f32)actor->unk_0C;
    } else {
        t = 1.0f;
    }
    actor->unk_18 = (1.0f - t) * 110.0f;
    scale = (1.0f - t) * 0.8f + 0.2f;
    model->scale.x = scale;
    model->scale.y = scale;
    model->scale.z = scale;
    if (t < 0.3f) {
        actor->unk_04 = 0;
    } else {
        actor->unk_04 = 1;
    }
    if (t >= 1.0f) {
        model->attr |= HU3D_ATTR_DISPOFF;
        actor->unk_0A = 0;
        actor->unk_2C = m253_KoopaJrHide;
    }
}

void m253_KoopaJrSquashUpdate(BabyBowserBonkersKoopaJr *actor) {
    HmfModel *model = Hu3DData + actor->unk_02;
    f32 scale;

    actor->unk_06 = 4;
    actor->unk_04 = 0;
    actor->unk_18 = 110.0f;
    scale = 1.0f - (f32)actor->unk_0A / 5.0f;
    if (scale <= 0.0f) {
        scale = 0.0f;
    }
    model->scale.x = 1.0f;
    model->scale.z = 1.0f;
    model->scale.y = 0.4f - scale * 0.35f;
    model->motSpeed = 0.0f;
    if (15.0f <= (f32)actor->unk_0A) {
        actor->unk_0A = 0;
        actor->unk_2C = m253_KoopaJrDropUpdate;
    }
}

void m253_KoopaJrDropUpdate(BabyBowserBonkersKoopaJr *actor) {
    HmfModel *model = Hu3DData + actor->unk_02;
    f32 scale;

    actor->unk_06 = 5;
    actor->unk_04 = 0;
    actor->unk_18 -= 9.166667f;
    scale = model->scale.z - 0.2f;
    model->scale.z = scale;
    model->scale.x = scale;
    if (scale <= 0.1f) {
        model->scale.x = model->scale.z = 0.0f;
    }
    if (actor->unk_18 <= 0.0f) {
        model->attr |= HU3D_ATTR_DISPOFF;
        model->scale.y = 1.0f;
        actor->unk_0A = 0;
        actor->unk_2C = m253_KoopaJrHide;
    }
}

s32 m253_KoopaJrRiseStart(s32 arg0, s16 arg1, s16 arg2) {
    BabyBowserBonkersKoopaJr *actor;
    HmfModel *model;

    if (arg0 >= 14) {
        return -1;
    }
    if (arg0 < 0) {
        return -1;
    }
    actor = &m253_koopaJrTbl[arg0];
    model = Hu3DData + actor->unk_02;
    if (actor->unk_06 != 0) {
        return -1;
    }
    actor->unk_0C = arg1;
    actor->unk_0E = arg2;
    actor->unk_0A = 0;
    actor->unk_10 = 15;
    actor->unk_14 = 0.0f;
    if (!(rand8() & 3)) {
        actor->unk_12 = rand8() % 3 + 1;
    } else {
        actor->unk_12 = 0;
    }
    actor->unk_2C = m253_KoopaJrRiseUpdate;
    model->attr &= ~HU3D_ATTR_DISPOFF;
    model->rot.x = model->rot.y = model->rot.z = 0.0f;
    model->motTime = model->motSpeed = 0.0f;
    return arg0;
}

BabyBowserBonkersKoopaJr *m253_KoopaJrGet(s32 arg0) {
    if (arg0 < 14) {
        if (arg0 >= 0) {
            return &m253_koopaJrTbl[arg0];
        }
    }
    return NULL;
}

void m253_KoopaJrDistSort(f32 x, f32 z, BabyBowserBonkersKoopaJr **list) {
    s32 i;
    s32 j;
    HmfModel *model1;
    HmfModel *model2;
    f32 dx;
    f32 dz;
    f32 dist;
    BabyBowserBonkersKoopaJr *temp;

    for (i = 0; i < 14; i++) {
        list[i] = &m253_koopaJrTbl[i];
    }
    for (i = 0; i < 13; i++) {
        for (j = i + 1; j < 14; j++) {
            model1 = Hu3DData + list[i]->unk_02;
            model2 = Hu3DData + list[j]->unk_02;
            dx = model1->pos.x - x;
            dz = model1->pos.z - z;
            dist = sqrtf(dx * dx + dz * dz);
            dx = model2->pos.x - x;
            dz = model2->pos.z - z;
            if (sqrtf(dx * dx + dz * dz) < dist) {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}

s32 m253_KoopaJrStandCheck(BabyBowserBonkersKoopaJr *arg0, s32 arg1) {
    if (arg0->unk_08 == 0) {
        return 0;
    }
    switch (arg0->unk_06) {
        case 1:
            return 1;
        case 2:
            if (arg0->unk_0A > arg0->unk_0E - arg1) {
                return 1;
            }
            break;
    }
    return 0;
}

s32 m253_KoopaJrTimeLeftGet(s32 arg0) {
    BabyBowserBonkersKoopaJr *actor = &m253_koopaJrTbl[arg0];

    if (actor->unk_08 != 0) {
        switch (actor->unk_06) {
            case 1:
                return actor->unk_0E;
            case 2:
                return actor->unk_0E - actor->unk_0A;
        }
    }
    return 0;
}

s32 m253_ComTargetGet(BabyBowserBonkersKoopaJr **list, s32 count, s32 playerIndex) {
    s32 candidates[16];
    s32 i;
    s32 n;
    s32 quadrant;
    HmfModel *model;

    quadrant = m253_QuadrantGet(mgPlayerObjTbl[playerIndex]->trans.x,
                                                 mgPlayerObjTbl[playerIndex]->trans.z);
    for (i = 0, n = 0; i < 14; i++) {
        model = Hu3DData + list[i]->unk_02;
        if (m253_KoopaJrStandCheck(list[i], 9) == 0) {
            continue;
        }
        if (m253_QuadrantGet(model->pos.x, model->pos.z) != quadrant) {
            candidates[n] = list[i]->unk_00;
            n++;
            if (n >= count) {
                break;
            }
        }
    }
    if (n == 0) {
        return -1;
    }
    return candidates[rand8() % n];
}

s32 m253_ComStompTargetGet(BabyBowserBonkersKoopaJr **list, s32 count, s32 playerIndex) {
    s32 candidates[16];
    s32 i;
    s32 n;
    s32 quadrant;
    HmfModel *model;

    quadrant = m253_QuadrantGet(mgPlayerObjTbl[playerIndex]->trans.x,
                                                 mgPlayerObjTbl[playerIndex]->trans.z);
    for (i = 0, n = 0; i < 14; i++) {
        model = Hu3DData + list[i]->unk_02;
        if (list[i]->unk_04 == 0) {
            continue;
        }
        if (m253_QuadrantGet(model->pos.x, model->pos.z) != quadrant) {
            candidates[n] = list[i]->unk_00;
            n++;
            if (n >= count) {
                break;
            }
        }
    }
    if (n == 0) {
        return -1;
    }
    return candidates[rand8() % n];
}

s32 m253_KoopaJrAllHiddenCheck(void) {
    s32 i;
    BabyBowserBonkersKoopaJr *actor;

    for (i = 0, actor = m253_koopaJrTbl; i < 14; i++, actor++) {
        if (actor->unk_06 != 0) {
            return 0;
        }
    }
    return 1;
}

void m253_PatternOrderInit(void) {
    s32 i;
    s32 j;
    s32 a;
    s32 b;
    BabyBowserBonkersPattern *temp;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            m253_patternOrderTbl[i][j] = m253_patternGrpTbl[i][j % m253_patternNumTbl[i]];
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 255; j++) {
            a = rand8() & 3;
            b = rand8() & 3;
            if (a != b) {
                temp = m253_patternOrderTbl[i][a];
                m253_patternOrderTbl[i][a] = m253_patternOrderTbl[i][b];
                m253_patternOrderTbl[i][b] = temp;
            }
        }
    }
}

u16 m253_SprAnimRead(s32 dirAndFile) {
    void *data;
    u16 sprite;

    data = DataRead(dirAndFile);
    sprite = HuSprAnimRead(data);
    DataClose(data);
    return sprite;
}

void m253_ScoreInit(void) {
    s32 i;
    BabyBowserBonkersScore *entry;

    m253_sprTbl = HuMemAllocTag(0x20, TAG_OVERLAY);
    m253_scoreTbl = HuMemAllocTag(sizeof(BabyBowserBonkersScore) * 2, TAG_OVERLAY);
    m253_sprTbl[0] = m253_SprAnimRead(0x31);
    m253_sprTbl[1] = m253_SprAnimRead(0x560004);
    for (i = 0, entry = m253_scoreTbl; i < 2; i++, entry++) {
        memset(entry, 0, sizeof(BabyBowserBonkersScore));
        m253_ScoreCreate(i, GwPlayer[m253_playerWorkTbl[i].unk_28].chr);
    }
    omAddObj(30, 0, 0, -1, m253_ScoreObjMain);
}

void m253_ScoreObjMain(omObjData *object) {
    s16 i;
    BabyBowserBonkersScore *entry;
    u16 digits[2];
    f32 scale;

    for (i = 0, entry = m253_scoreTbl; i < 2; i++, entry++) {
        digits[0] = entry->unk_0C / 10;
        digits[1] = entry->unk_0C - digits[0] * 10;
        if (digits[0] >= 10) {
            digits[0] = 9;
        }
        if (digits[1] >= 10) {
            digits[1] = 9;
        }
        HuSprPatNoSet(entry->unk_02, 0, (s16)digits[0]);
        HuSprPatNoSet(entry->unk_02, 1, (s16)digits[1]);
        if (entry->unk_0C < entry->unk_0E && entry->unk_10 == 0) {
            entry->unk_10 = 12;
            if (++entry->unk_0C == 10) {
                HuSprAttrReset(entry->unk_02, 0, HUSPR_ATTR_DISPOFF);
            }
        }
        scale = sindf(entry->unk_10 / 12.0f * 180.0f) * 0.5f + 1.0f;
        HuSprPosSet(entry->unk_02, 0, entry->unk_04 + entry->unk_08[0] * scale, entry->unk_06);
        HuSprPosSet(entry->unk_02, 1, entry->unk_04 + entry->unk_08[1] * scale, entry->unk_06);
        HuSprScaleSet(entry->unk_02, 0, scale, scale);
        HuSprScaleSet(entry->unk_02, 1, scale, scale);
        if (entry->unk_10 != 0) {
            entry->unk_10--;
        }
    }
}

void m253_ScoreCreate(s32 index, s32 chr) {
    BabyBowserBonkersScore *entry;
    s32 group;
    s32 x;
    s32 y;
    s32 i;

    entry = &m253_scoreTbl[index];
    entry->unk_00 = m253_SprAnimRead(m253_chrIconFileTbl[chr]);
    group = HuSprGrpCreate(4, 0);
    entry->unk_02 = group;
    x = 266;
    if (index == 0) {
        x = 56;
    }
    y = 30;
    entry->unk_04 = x + 8;
    entry->unk_06 = y;
    entry->unk_08[0] = -6;
    entry->unk_08[1] = 6;
    entry->unk_0C = entry->unk_0E = entry->unk_10 = 0;
    for (i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                HuSprDispOff(group, i);
            case 1:
                HuSprGrpMemberSet(group, i, m253_sprTbl[0], 0);
                HuSprPosSet(group, i, entry->unk_04 + entry->unk_08[i], y);
                break;
            case 2:
                HuSprGrpMemberSet(group, i, entry->unk_00, 0);
                HuSprPosSet(group, i, x - 18, y);
                break;
            case 3:
                HuSprGrpMemberSet(group, i, m253_sprTbl[1], 0);
                HuSprPosSet(group, i, x, y);
                HuSprScaleSet(group, i, 1.0f, 1.0f);
                HuSprColorTPLvlSet(group, i, 0, 0, 255, 160);
                break;
        }
        HuSprAnimModeSet(group, i, HUSPR_ANIM_MODE_STOP);
        HuSprPatNoSet(group, i, 0);
        HuSprAttrSet(group, i, 0x1000);
        HuSprPriSet(group, i, i - 16);
    }
}

void m253_ScoreSet(s32 arg0, s16 arg1) {
    s16 *field = &m253_scoreTbl[arg0].unk_0E;

    *field = arg1;
}

void m253_CameraInit(void) {
    HuCamera *camera;
    s32 i;

    Center.x = 0.0f;
    Center.y = -708.8f;
    Center.z = -781.8f;
    CRot.x = 318.38f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2938.0f;
    m253_CameraKeyStore(0);
    m253_CameraKeyStore(1);
    m253_cameraMoveF = 0;
    m253_cameraMoveTime = 0;
    m253_cameraMoveTimer = 0;
    omAddObj(31, 0, 0, -1, m253_CameraMoveObjMain);
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

void m253_CameraDebugPad(void) {
    MgCameraKey delta = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed;

    speed = 1.0f;
    switch (m253_cameraDebugMode) {
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
                m253_CameraMoveStart(delta.center.x, delta.center.y, delta.center.z, delta.rot.x,
                                                  delta.rot.y, delta.rot.z, delta.zoom, 1);
            }
            sprintf(omDBGStrBuf, "CAMERA TEST_MODE");
            print8((s16)m253_cameraDebugX + 20, (s16)m253_cameraDebugY + 80,
                   omDBGStrBuf);
            sprintf(omDBGStrBuf, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((s16)m253_cameraDebugX + 20, (s16)m253_cameraDebugY + 88,
                   omDBGStrBuf);
            sprintf(omDBGStrBuf, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((s16)m253_cameraDebugX + 20, (s16)m253_cameraDebugY + 96,
                   omDBGStrBuf);
            sprintf(omDBGStrBuf, " ZOOM   %3.3f ", CZoom);
            print8((s16)m253_cameraDebugX + 20, (s16)m253_cameraDebugY + 104,
                   omDBGStrBuf);
            break;
        case 2:
            if ((HuPadBtn[0] & R_JPAD) || (HuPadBtn[0] & R_CBUTTONS)) {
                m253_cameraDebugX++;
            }
            if (HuPadBtn[0] & (L_JPAD | L_CBUTTONS)) {
                m253_cameraDebugX--;
            }
            if (HuPadBtn[0] & (D_JPAD | D_CBUTTONS)) {
                m253_cameraDebugY++;
            }
            if (HuPadBtn[0] & (U_JPAD | U_CBUTTONS)) {
                m253_cameraDebugY--;
            }
            fontcolor = 8;
            sprintf(omDBGStrBuf, "CAMERA TEST_MODE ");
            print8((s16)m253_cameraDebugX + 20, (s16)m253_cameraDebugY + 80,
                   omDBGStrBuf);
            sprintf(omDBGStrBuf, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((s16)m253_cameraDebugX + 20, (s16)m253_cameraDebugY + 88,
                   omDBGStrBuf);
            sprintf(omDBGStrBuf, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((s16)m253_cameraDebugX + 20, (s16)m253_cameraDebugY + 96,
                   omDBGStrBuf);
            sprintf(omDBGStrBuf, " ZOOM   %3.3f ", CZoom);
            print8((s16)m253_cameraDebugX + 20, (s16)m253_cameraDebugY + 104,
                   omDBGStrBuf);
            break;
        case 3:
            m253_cameraDebugMode = 0;
            break;
    }
    if (HuPadBtnDown[0] & R_TRIG) {
        if (m253_cameraDebugMode == 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (m253_cameraDebugMode++ >= 4) {
            m253_cameraDebugMode = 0;
        }
    }
}

void m253_CameraMoveObjMain(omObjData *object) {
    f32 t;

    if (m253_cameraMoveTime <= 0) {
        m253_CameraPosUpdate(0);
        m253_cameraMoveF = 0;
        return;
    }
    if (m253_cameraMoveTimer == 0) {
        Center.x = m253_cameraKeyTbl[0].center.x;
        Center.y = m253_cameraKeyTbl[0].center.y;
        Center.z = m253_cameraKeyTbl[0].center.z;
        CRot.x = m253_cameraKeyTbl[0].rot.x;
        CRot.y = m253_cameraKeyTbl[0].rot.y;
        CRot.z = m253_cameraKeyTbl[0].rot.z;
        CZoom = m253_cameraKeyTbl[0].zoom;
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
        m253_cameraMoveTime = 0;
    } else {
        t = (f32)m253_cameraMoveTimer / (f32)m253_cameraMoveTime;
        Center.x = m253_InterpCalc(t, m253_cameraKeyTbl[0].center.x,
                                                     m253_cameraKeyTbl[1].center.x);
        Center.y = m253_InterpCalc(t, m253_cameraKeyTbl[0].center.y,
                                                     m253_cameraKeyTbl[1].center.y);
        Center.z = m253_InterpCalc(t, m253_cameraKeyTbl[0].center.z,
                                                     m253_cameraKeyTbl[1].center.z);
        CRot.x = m253_AngleInterpCalc(t, m253_cameraKeyTbl[0].rot.x,
                                                   m253_cameraKeyTbl[1].rot.x);
        CRot.y = m253_AngleInterpCalc(t, m253_cameraKeyTbl[0].rot.y,
                                                   m253_cameraKeyTbl[1].rot.y);
        CRot.z = m253_AngleInterpCalc(t, m253_cameraKeyTbl[0].rot.z,
                                                   m253_cameraKeyTbl[1].rot.z);
        CZoom = m253_InterpCalc(t, m253_cameraKeyTbl[0].zoom,
                                                  m253_cameraKeyTbl[1].zoom);
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
        if (m253_cameraMoveTimer > 0) {
            m253_cameraMoveTimer--;
        } else {
            m253_cameraMoveTimer++;
        }
    }
    m253_cameraMoveF = 1;
    m253_CameraPosUpdate(0);
}

void m253_CameraKeyStore(s32 arg0) {
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
    m253_cameraKeyTbl[arg0].center.x = Center.x;
    m253_cameraKeyTbl[arg0].center.y = Center.y;
    m253_cameraKeyTbl[arg0].center.z = Center.z;
    m253_cameraKeyTbl[arg0].rot.x = CRot.x;
    m253_cameraKeyTbl[arg0].rot.y = CRot.y;
    m253_cameraKeyTbl[arg0].rot.z = CRot.z;
    m253_cameraKeyTbl[arg0].zoom = CZoom;
    m253_cameraKeyTbl[arg0].unk_1C = m253_cameraKeyTbl[arg0].unk_20 = 0.0f;
}

// Passing CAMERA_KEEP for a component keeps its current value.
void m253_CameraMoveStart(f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames) {
    if (frames > 0) {
        m253_cameraMoveTimer = frames - 1;
        m253_cameraMoveTime = frames;
        if (x != CAMERA_KEEP) {
            m253_cameraKeyTbl[0].center.x = x;
        } else {
            m253_cameraKeyTbl[0].center.x = Center.x;
        }
        if (y != CAMERA_KEEP) {
            m253_cameraKeyTbl[0].center.y = y;
        } else {
            m253_cameraKeyTbl[0].center.y = Center.y;
        }
        if (z != CAMERA_KEEP) {
            m253_cameraKeyTbl[0].center.z = z;
        } else {
            m253_cameraKeyTbl[0].center.z = Center.z;
        }
        if (rotX != CAMERA_KEEP) {
            m253_cameraKeyTbl[0].rot.x = rotX;
        } else {
            m253_cameraKeyTbl[0].rot.x = CRot.x;
        }
        if (rotY != CAMERA_KEEP) {
            m253_cameraKeyTbl[0].rot.y = rotY;
        } else {
            m253_cameraKeyTbl[0].rot.y = CRot.y;
        }
        if (rotZ != CAMERA_KEEP) {
            m253_cameraKeyTbl[0].rot.z = rotZ;
        } else {
            m253_cameraKeyTbl[0].rot.z = CRot.z;
        }
        if (zoom != CAMERA_KEEP) {
            m253_cameraKeyTbl[0].zoom = zoom;
        } else {
            m253_cameraKeyTbl[0].zoom = CZoom;
        }
        m253_CameraKeyStore(1);
    }
}

void m253_CameraPosUpdate(s32 camIndex) {
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

f32 m253_AngleDiffCalc(f32 arg0, f32 arg1) {
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

f32 m253_AngleStepCalc(f32 target, f32 current, f32 step) {
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

f32 m253_InterpCalc(f32 t, f32 start, f32 end) {
    return start + t * (end - start);
}

f32 m253_AngleInterpCalc(f32 t, f32 start, f32 end) {
    return m253_AngleStepCalc(end, start, fabsf(m253_AngleDiffCalc(end, start) * t));
}

void m253_WorkPtrSet(omObjData *arg0, u32 arg1) {
    arg0->work[0] = arg1 >> 24;
    arg0->work[1] = (arg1 >> 16) & 0xFF;
    arg0->work[2] = (arg1 >> 8) & 0xFF;
    arg0->work[3] = arg1 & 0xFF;
}

BabyBowserBonkersPlayer *m253_WorkPtrGet(omObjData *arg0) {
    BabyBowserBonkersBytes packed;

    packed.bytes.byte3 = (u8)arg0->work[0];
    packed.bytes.byte2 = (u8)arg0->work[1];
    packed.bytes.byte1 = (u8)arg0->work[2];
    packed.bytes.byte0 = (u8)arg0->work[3];
    return (BabyBowserBonkersPlayer *)packed.word;
}
