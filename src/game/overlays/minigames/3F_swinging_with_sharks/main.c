#include "common.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "game/hmfdraw.h"
#include "game/hmfmath.h"
#include "game/pause.h"
#include "game/wipe.h"

typedef struct {
    /* 0x00 */ s32 dataNum;
    /* 0x04 */ s32 attr;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 motAttr;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec rot;
} SharkEntry; // Size 0x24

typedef struct {
    /* 0x00 */ s16 model;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ Vec cur;
    /* 0x14 */ Vec pos;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char unk26[0xA];
} SharkState; // Size 0x30

typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec unk0C;
    /* 0x18 */ f32 dist;
} SharkPathPoint; // Size 0x1C

extern u16 mgInstColumnTbl[];
extern u8 omAllPauseF;

u8 m263_debugPrintF = 0;
u8 m263_exitF = 0;
f32 m263_swingAngle = 0.0f;
f32 m263_swingPhase = 0.0f;

SharkEntry m263_mdlEntryTbl[] = {
    { 0x00600001, 0x00000211, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600000, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600005, 0x00000231, 0, 0, { -700.0f, 600.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600002, 0x00000231, 0, 0, { -230.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600002, 0x00000231, 0, 0, { 0.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600002, 0x00000231, 0, 0, { 230.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600002, 0x00000231, 0, 0, { 460.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600002, 0x00000231, 0, 0, { 690.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600003, 0x00000229, 0, 0, { -300.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600003, 0x00000229, 0, 0, { 0.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600003, 0x00000229, 0, 0, { 300.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600003, 0x00000229, 0, 0, { 600.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600003, 0x00000229, 0, 0, { 900.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600004, 0x00000A51, 0, 0, { -300.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600004, 0x00000A51, 0, 0, { 0.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600004, 0x00000A51, 0, 0, { 300.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600004, 0x00000A51, 0, 0, { 600.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600004, 0x00000A51, 0, 0, { 900.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000B0030, 0x00000A01, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000B0030, 0x00000A01, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000B0030, 0x00000A01, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000B0030, 0x00000A01, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000B0030, 0x00000A01, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00220004, 0x00000A35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00220004, 0x00000A35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00220004, 0x00000A35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00220004, 0x00000A35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00220004, 0x00000A35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600006, 0x00000A51, 0, 0, { -700.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000B0049, 0x00000A35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00220004, 0x00000A35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000B0030, 0x00000A25, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xFFFF00A1, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600008, 0x00000A20, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xFFFF0004, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xFFFF000D, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xFFFF0010, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xFFFF000E, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xFFFF0001, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xFFFF0035, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xFFFF0038, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xFFFF0071, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x0000007F, 0x00000A15, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000B0002, 0x00000A35, 0, 0, { 0.0f, 500.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000A0154, 0x00000231, 0, 2, { 110.0f, 0.0f, -1170.0f }, { -25.0f, -28.0f, 0.0f } },
    { 0x000A0155, 0x00000231, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000B0030, 0x00000A20, 0, 0, { 110.0f, 0.0f, -1170.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000A00EE, 0x00000231, 0, 2, { 110.0f, 60.0f, -1170.0f }, { 0.0f, -28.0f, 0.0f } },
    { 0x000A00F6, 0x00000A35, 0, 0, { 0.0f, 500.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000A00FC, 0x00000A35, 0, 0, { 0.0f, 500.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { -1, 0, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } }
};

u16 m263_comAimRateTbl[] = { 76, 51, 25, 12 };
u8 m263_chrDirTbl[] = { 2, 3, 7, 4, 5, 6, 8, 9 };
s16 m263_splashTimer = 0;
s16 m263_swingState = 0;
s16 m263_swingSeNo = -1;

s32 m263_itemSprFileTbl[] = {
    0x0021002D,
    0x0021002E,
    0x0021002F,
    0x00210030,
    0x00210031,
    0x00210032,
    0x00210033,
    0x00210034,
    0x00210035,
    0x00210036,
    0x00210037,
    0x00210038,
    0x00210039,
    0x0021003A,
    0x0021003B,
    0x0021003C,
    0x0021003D,
    0x0021003E,
    0x0021003F,
    0x00210040,
};

s16 m263_cameraMoveTimer = 0;
f32 m263_degToRad = 0.017453292f;

SharkPathPoint m263_shark0PathTbl[] = {
    { { 110.0f, -75.0f, -790.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 110.0f, -75.0f, -790.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -720.0f, -75.0f, -1230.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -1330.0f, -75.0f, -750.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -780.0f, -75.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 40.0f, -50.0f, 230.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 910.0f, -75.0f, 20.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 1240.0f, -75.0f, -420.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 670.0f, -75.0f, -880.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 110.0f, -75.0f, -790.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 110.0f, -75.0f, -790.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
};

SharkPathPoint m263_shark1PathTbl[] = {
    { { -750.0f, -75.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -750.0f, -75.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -740.0f, -75.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 40.0f, -50.0f, 230.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 910.0f, -75.0f, 20.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 1240.0f, -75.0f, -420.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 670.0f, -75.0f, -880.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 110.0f, -75.0f, -790.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -720.0f, -75.0f, -1230.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -1330.0f, -75.0f, -750.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -790.0f, -75.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -780.0f, -75.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -780.0f, -75.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
};

SharkPathPoint *m263_sharkPathTbl[2] = { m263_shark0PathTbl, m263_shark1PathTbl };
s16 m263_sharkNum = 0;
s16 m263_wakeTimer = 0;
s16 m263_koopaTurnTimer = 0;

HuMtx4F m263_ropeBaseMtx BSS;
HuMtx4F m263_stepBaseMtx BSS;
s16 m263_mdlTbl[50] BSS; // model ids, indexed like m263_mdlEntryTbl
u8 m263_mdlTblPad[4] BSS; /* Unreferenced. */
s16 m263_motTbl[50] BSS; // motion ids, indexed like m263_mdlEntryTbl
Vec m263_jumpVel BSS;
Vec m263_stepPrevPos BSS;
Vec m263_playerPos BSS;
f32 m263_swingAmp BSS;
f32 m263_jumpRotZ BSS;
s16 m263_playerNo BSS;
s16 m263_padNo BSS;
s16 m263_playerChr BSS;
s16 m263_hitFloatNo BSS;
s16 m263_phase BSS;
s16 m263_timer BSS;
s16 m263_phaseTimer BSS;
s16 m263_ambSeNo BSS;
s16 m263_comLevel BSS;
s16 m263_comAimF BSS;
s16 m263_comWait BSS;
s16 m263_comAimAngle BSS;
SharkState m263_floatTbl[5] BSS;
s16 m263_startMesId BSS;
s16 m263_seFadeTimer BSS;
s16 m263_prizeSpr BSS;
s16 m263_prizeEffNo BSS;
f32 m263_seaScroll BSS;
s16 m263_sharkMdl BSS;
s16 m263_sharkMot BSS;
s16 m263_sharkMdlTbl[4] BSS;
s16 m263_wakeTimerTbl[20] BSS;
s16 m263_wakeMdlTbl[20] BSS;
s16 m263_koopaRotY BSS;
s16 m263_koopaRotYPad BSS; /* Unreferenced. */
u8 m263_koopaRotYPadB[4] BSS; /* Unreferenced. */
s16 m263_cameraMoveTime BSS;
Vec m263_cameraMoveRotEnd BSS;
Vec m263_cameraMoveCenterEnd BSS;
Vec m263_cameraMoveCenterStart BSS;
Vec m263_cameraCenterInit BSS;
Vec m263_cameraMoveRotStart BSS;
Vec m263_cameraDebugRot BSS;
f32 m263_cameraZoomInit BSS;
f32 m263_cameraMoveZoomStart BSS;
f32 m263_cameraMoveZoomEnd BSS;
Vec m263_cameraRotInit BSS;
f32 m263_cameraFov BSS;

const s16 m263_fontMesTbl[] = {
    0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0x0000
};

void m263_MainObjMain(omObjData *object);
void m263_PlayerInit(void);
void m263_PlayerSwingObjMain(omObjData *object);
void m263_PlayerJumpObjMain(omObjData *object);
void m263_PlayerFallObjMain(omObjData *object);
void m263_PlayerLandObjMain(omObjData *object);
void m263_PlayerWinObjMain(omObjData *object);
void m263_SwingStartObjMain(omObjData *object);
void m263_SwingInit(void);
void m263_SwingObjMain(omObjData *object);
void m263_SwingStopObjMain(omObjData *object);
void m263_FloatInit(void);
void m263_FloatObjMain(omObjData *object);
void m263_PrizeObjInit(omObjData *object);
void m263_PrizeObjMain(omObjData *object);
void m263_CameraMoveObjMain(omObjData *object);
void m263_CameraDebugReset(void);
void m263_SeaInit(void);
void m263_CameraMoveStart(f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ, f32 zoom,
                                        s16 time);
void m263_SeaObjMain(omObjData *object);
void m263_SwingAngleSet(f32 arg0);
void m263_StepPosGet(Vec *pos);
void m263_MtxRotZCat(HuMtx4F mtx, f32 angle);
void m263_NodePosGet(s16 model, Vec *pos, HuMtx4F mtx);
void m263_MdlEntryCreateAll(SharkEntry *entries);
void m263_ExitCheckObjMain(omObjData *object);
void m263_ExitObjMain(omObjData *object);
void m263_SharkProc(void);
f32 m263_PathTimeCalc(SharkPathPoint *points, f32 speed);
void m263_SharkPathMove(SharkPathPoint *points, s16 model, f32 total);
void m263_KoopaLookUpdate(void);
void m263_ShadowUpdate(void);
void m263_WakeInit(void);
void m263_WakeUpdate(void);
void m263_KoopaInit(void);
void m263_KoopaUpdate(void);

void m263_ObjectSetup(void) {
    s32 index;
    s32 i;

    omInitObjMan(20, 10);
    omGameSysInit();
    Hu3DSprModelInit(20);
    Hu3DBGColorSet(0, 0xFF, 0);
    Hu3DScreenClearF = 1;
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    CRot.x = 334.0f;
    CRot.y = m263_cameraRotInit.z = 0.0f;
    CZoom = 2750.0f;
    Center.x = -698.0f;
    Center.y = 363.0f;
    Center.z = -112.9f;
    m263_cameraFov = 20.0f;
    m263_cameraRotInit = CRot;
    m263_cameraDebugRot = m263_cameraRotInit;
    m263_cameraZoomInit = CZoom;
    m263_cameraCenterInit = Center;
    Hu3DCameraPerspectiveSet(0, m263_cameraFov, 500.0f, 8000.0f);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(0, 0x40, 0x40, 0x60);
    Hu3DGLightDirSet(0, 92.0f, 79.0f, 22.0f);
    Hu3DGLightStatSet(0, 1, 1);
    Hu3DGLightColorSet(2, 100, 0xFF, 0xFF);
    Hu3DGLightDirSet(2, -115.0f, 6.0f, -33.0f);
    Hu3DGLightStatSet(2, 1, 1);
    omAddObj(10000, 0, 0, -1, m263_ExitCheckObjMain);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    m263_phase = 0;
    m263_timer = 0;
    omAddObj(1000, 0, 0, -1, m263_MainObjMain);
    omAddObj(1000, 0, 0, -1, m263_PlayerSwingObjMain);
    omAddObj(900, 0, 0, -1, m263_SwingStartObjMain);
    omAddObj(900, 0, 0, -1, m263_FloatObjMain);
    omSetStatBit(omAddObj(900, 0, 0, -1, m263_SeaObjMain), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omAddObj(900, 0, 0, -1, m263_CameraMoveObjMain);
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    m263_playerNo = i;
    m263_comLevel = GwPlayer[m263_playerNo].stat & 1;
    GwPlayer[m263_playerNo].bonusCoin = -1;
    m263_playerChr = GwPlayer[i].chr;
    m263_padNo = GwPlayer[i].pad;
    m263_MdlEntryCreateAll(m263_mdlEntryTbl);
    if (m263_comLevel != 0) {
        m263_comLevel = GwPlayer[m263_playerNo].cpu_difficulty + 1;
        m263_comAimF =
            rand8() > m263_comAimRateTbl[GwPlayer[m263_playerNo].cpu_difficulty];
        m263_comWait = (u8)(rand8() & 0x1F) + 15;
        if (m263_comAimF != 0) {
            index = (rand8() * 5) >> 8;
            m263_comAimAngle =
                (Hu3DData[m263_mdlTbl[index + 3]].pos.x + 70.0f) / 1000.0f * 70.0f + 10.0f;
        }
    }
    m263_SwingInit();
    m263_FloatInit();
    m263_SeaInit();
    m263_KoopaInit();
    m263_PlayerInit();
    m263_swingAngle = 0;
    m263_swingAmp = 80.0f;
    m263_hitFloatNo = -1;
    m263_SwingAngleSet(0.0f);
    m263_StepPosGet(&m263_stepPrevPos);
    m263_phaseTimer = 0;
    Hu3DModelTPLvlInit(m263_mdlTbl[31]);
    Hu3DModelDynamicFree(m263_mdlTbl[31]);
    GMesFontMesCreate(m263_fontMesTbl, 1);
    m263_WakeInit();
    omAddPrcObj(m263_SharkProc, 0x3F00, 0x2000, 0);
    omAddPrcObj(m263_SharkProc, 0x3F00, 0x2000, 0);
    HuAudSeqPlay(0x44);
    WipeCreateIn(0xFF, 0x10);
}

void m263_MainObjMain(omObjData *object) {
    switch (m263_phase) {
        case 0:
            if (WipeStatGet() != 0) {
                break;
            }
            if (m263_phaseTimer == 0) {
                m263_ambSeNo = HuAudFXPlay(0x4ED);
            }
            if (++m263_phaseTimer == 120) {
                m263_startMesId = GMesCreate(8);
                m263_CameraMoveStart(334.0f, 0.0f, 0.0f, 54.0f, 435.0f, -148.0f, 4340.0f, 30);
            }
            if (m263_phaseTimer > 120 && GMesStatGet() == 0) {
                GMesCreate(0x1A, 10, 160, 120);
                m263_timer = 329;
                m263_phaseTimer = 0;
                m263_phase = 1;
            }
            break;
        case 1:
            if (m263_timer > 0) {
                m263_timer--;
                GMesTimerValueSet(m263_timer / 30);
                if (m263_timer == 0) {
                    GMesTimerEnd();
                    m263_phaseTimer = 0;
                }
            }
            break;
        case 3:
            if (m263_phaseTimer == 0) {
                GMesCreate(0x13);
                HuAudSeqFadeOut(120);
                m263_phaseTimer++;
                m263_seFadeTimer = 0;
            }
            if (++m263_seFadeTimer == 30) {
                HuAudFXFadeOut(m263_ambSeNo, 30);
            }
            if (GMesStatGet() == 0) {
                m263_phaseTimer++;
                if (m263_hitFloatNo == -1) {
                    if (m263_phaseTimer >= 16) {
                        GMesCreate(0x1D);
                        m263_phaseTimer = 0;
                        m263_phase = 4;
                        HuAudSeqPlay(0x6B);
                    }
                } else if (m263_phaseTimer >= 16) {
                    GMesCreate(0x24);
                    m263_phaseTimer = 0;
                    m263_phase = 4;
                    HuAudSeqPlay(0x68);
                }
            }
            break;
        case 4:
            if (++m263_phaseTimer >= 136) {
                m263_phaseTimer = 0;
                m263_exitF = 1;
                m263_phase = 5;
            }
            break;
        case 5:
            break;
    }
    m263_KoopaLookUpdate();
    m263_ShadowUpdate();
    m263_WakeUpdate();
    m263_KoopaUpdate();
}

void m263_PlayerInit(void) {
    Hu3DMotionSet(m263_mdlTbl[32], m263_motTbl[41]);
    Hu3DMotionAttrSet(m263_mdlTbl[32], 1, 1);
    Hu3DMotionTimeSet(m263_mdlTbl[32], 0.0f);
    Hu3DModelTPLvlInit(m263_mdlTbl[33]);
    Hu3DModelDynamicFree(m263_mdlTbl[33]);
}

void m263_PlayerSwingObjMain(omObjData *object) {
    Vec pos;
    s32 jump = FALSE;
    f32 y;
    f32 velY;
    s16 frames;

    m263_StepPosGet(&pos);
    Hu3DModelPosSet(m263_mdlTbl[32], pos.x, pos.y, pos.z);
    Hu3DModelRotSet(m263_mdlTbl[32], 0.0f, 90.0f, m263_swingAngle);
    if (m263_swingPhase < 180.0f) {
        Hu3DMotionTimeSet(m263_mdlTbl[32], m263_swingPhase / 12.0f);
    } else {
        Hu3DMotionTimeSet(m263_mdlTbl[32], (360.0f - m263_swingPhase) / 12.0f);
    }
    if (m263_phase > 0) {
        if (m263_comLevel != 0) {
            if (m263_comWait <= 0) {
                if (m263_comAimF != 0) {
                    if (m263_comAimAngle <= m263_swingAngle &&
                        m263_swingPhase < 90.0f) {
                        jump = TRUE;
                    }
                } else if ((150.0f < m263_swingPhase && m263_swingPhase < 180.0f) ||
                           345.0f < m263_swingPhase) {
                    jump = TRUE;
                }
            } else {
                m263_comWait--;
            }
        } else {
            jump = HuPadBtnDown[m263_padNo] & A_BUTTON;
        }
        if ((m263_timer != 0 && jump) ||
            (m263_timer == 0 &&
             ((150.0f < m263_swingPhase && m263_swingPhase < 180.0f) ||
              345.0f < m263_swingPhase))) {
            HuAudFXPlay(0x4E9);
            if (m263_timer != 0) {
                GMesTimerEnd();
            }
            velY = pos.y - m263_stepPrevPos.y + 10.0f;
            y = pos.y;
            for (frames = 0;; frames++) {
                y += velY;
                velY -= 4.0f;
                if (y <= 0.0f) {
                    break;
                }
            }
            m263_phase = 2;
            m263_playerPos = pos;
            if (10.0f < m263_swingAngle && m263_swingAngle <= 80.0f &&
                m263_swingPhase <= 90.0f) {
                m263_jumpVel.x =
                    ((m263_swingAngle - 10.0f) * 14.285714f - 170.0f - pos.x) / frames;
            } else {
                m263_jumpVel.x = pos.x - m263_stepPrevPos.x;
            }
            m263_jumpVel.y = pos.y - m263_stepPrevPos.y;
            m263_jumpVel.z = 0.0f;
            m263_jumpVel.y += 10.0f;
            m263_swingAmp *= 1.1f;
            m263_jumpRotZ = m263_swingAngle;
            object->work[0] = 0;
            Hu3DMotionShiftSet(m263_mdlTbl[32], m263_motTbl[34], 0, 4, 0);
            object->func = m263_PlayerJumpObjMain;
        }
    }
    m263_stepPrevPos = pos;
}

void m263_PlayerJumpObjMain(omObjData *object) {
    f32 x;
    s16 i;

    m263_playerPos.x += m263_jumpVel.x;
    m263_playerPos.y += m263_jumpVel.y;
    m263_playerPos.z += m263_jumpVel.z;
    m263_jumpVel.y -= 4.0f;
    if (object->work[0] < 6) {
        Hu3DModelRotSet(m263_mdlTbl[32], 0.0f, 90.0f,
                        cosdf(object->work[0] * 18.0f) * m263_jumpRotZ);
        object->work[0]++;
    }
    if (m263_playerPos.y <= 0.0f) {
        CharFXPlay(0x70, m263_playerChr);
        omVibrate(m263_playerNo, 10, 0, 10);
        m263_phase = 3;
        m263_jumpRotZ = 0.0f;
        Hu3DMotionShiftSet(m263_mdlTbl[32], m263_motTbl[35], 0, 8, 2);
        Hu3DMotionShiftSet(m263_mdlTbl[47], m263_motTbl[48], 0, 4, 2);
        Hu3DModelRotSet(m263_mdlTbl[32], 0.0f, 90.0f, 0.0f);
        object->work[0] = 0;
        Hu3DModelAttrSet(m263_mdlTbl[29], 4, 0);
        Hu3DModelPosSet(m263_mdlTbl[29], m263_playerPos.x, 0.0f,
                        m263_playerPos.z);
        Hu3DMotionSpeedSet(m263_mdlTbl[29], 0.5f);
        Hu3DModelScaleSet(m263_mdlTbl[29], 3.0f, 3.0f, 3.0f);
        Hu3DModelAttrSet(m263_mdlTbl[30], 4, 0);
        Hu3DModelPosSet(m263_mdlTbl[30], m263_playerPos.x, -30.0f,
                        m263_playerPos.z + 50.0f);
        Hu3DModelScaleSet(m263_mdlTbl[30], 2.0f, 2.0f, 2.0f);
        HuAudFXPlay(0x4EF);
        object->func = m263_PlayerFallObjMain;
    } else if (m263_playerPos.y < 90.0f) {
        for (i = 0; i < 5; i++) {
            x = Hu3DData[m263_mdlTbl[i + 3]].pos.x;
            if (x - 80.0f < m263_playerPos.x && m263_playerPos.x < x + 80.0f) {
                HuAudFXPlay(0x4EC);
                omVibrate(m263_playerNo, 10, 0, 10);
                m263_phase = 3;
                m263_jumpRotZ = 0.0f;
                if (m263_playerPos.x < x - 40.0f) {
                    Hu3DMotionShiftSet(m263_mdlTbl[32], m263_motTbl[36], 0, 8, 0);
                } else if (x + 40.0f < m263_playerPos.x || 35.0f < m263_jumpVel.x) {
                    Hu3DMotionShiftSet(m263_mdlTbl[32], m263_motTbl[37], 0, 4, 0);
                } else {
                    Hu3DMotionAttrSet(m263_mdlTbl[32], 4, 4);
                }
                Hu3DModelRotSet(m263_mdlTbl[32], 0.0f, 100.0f, 0.0f);
                Hu3DModelPosSet(m263_mdlTbl[32], m263_playerPos.x, 50.0f,
                                m263_playerPos.z);
                m263_hitFloatNo = i;
                Hu3DModelAttrSet(m263_mdlTbl[42], 4, 0);
                Hu3DModelPosSet(m263_mdlTbl[42], m263_playerPos.x, 50.0f,
                                m263_playerPos.z + 30.0f);
                HuAudFXPlay(0x4EF);
                object->func = m263_PlayerLandObjMain;
                break;
            }
        }
    }
    Hu3DModelPosSet(m263_mdlTbl[32], m263_playerPos.x,
                    m263_playerPos.y, m263_playerPos.z);
}

void m263_PlayerFallObjMain(omObjData *object) {
    f32 scale;
    s16 model;

    if (object->work[0] == 8) {
        HuAudFXPlay(m263_playerChr + 0x287);
    }
    if (object->work[0] >= 9) {
        model = m263_mdlTbl[31];
        Hu3DModelAttrSet(model, 4, 0);
        Hu3DModelPosSet(model, m263_playerPos.x, 0.0f, m263_playerPos.z);
        if (m263_splashTimer > 90) {
            if (Hu3DData[m263_mdlTbl[32]].motTime != 0.0f) {
                return;
            }
            m263_splashTimer = 0;
        }
        scale = sindf((s16)(m263_splashTimer % 90)) + 0.5f;
        Hu3DModelScaleSet(model, scale, scale, scale);
        Hu3DModelTPLvlSet(model, 255.0f - m263_splashTimer * 2.8333333f);
        m263_splashTimer += 3;
    } else {
        m263_playerPos.y = sindf(object->work[0] * 18.0f) * m263_jumpVel.y;
        object->work[0]++;
        Hu3DModelPosSet(m263_mdlTbl[32], m263_playerPos.x,
                        m263_playerPos.y, m263_playerPos.z);
        Hu3DData[m263_mdlTbl[32]].rot.y = 90.0f - object->work[0] * 11.25f;
    }
}

void m263_PlayerLandObjMain(omObjData *object) {
    HmfModel *shark;
    s16 model = m263_mdlTbl[32];

    if (Hu3DData[model].motId == m263_motTbl[37] &&
        Hu3DData[model].motTime >= Hu3DMotion[Hu3DData[model].motId].unk02) {
        Hu3DMotionShiftSet(model, m263_motTbl[32], 0, 16, 2);
    }
    shark = &Hu3DData[m263_mdlTbl[m263_hitFloatNo + 3]];
    Hu3DModelPosSet(model, m263_playerPos.x, shark->pos.y + 80.0f, m263_playerPos.z);
    if (++object->work[0] > 20) {
        object->work[0] = 0;
        Hu3DMotionShiftSet(m263_mdlTbl[47], m263_motTbl[49], 0, 4, 0);
        object->func = m263_PlayerWinObjMain;
    }
}

void m263_PlayerWinObjMain(omObjData *object) {
    HmfModel *shark;
    s16 model = m263_mdlTbl[32];

    shark = &Hu3DData[m263_mdlTbl[m263_hitFloatNo + 3]];
    m263_playerPos.x += (shark->pos.x - m263_playerPos.x) / 2.0f;
    Hu3DModelPosSet(model, m263_playerPos.x, shark->pos.y + 80.0f, m263_playerPos.z);
    if (object->work[0] == 0) {
        Hu3DMotionShiftSet(model, m263_motTbl[38], 0, 4, 2);
    }
    if (++object->work[0] == 75) {
        Hu3DMotionShiftSet(model, m263_motTbl[39], 0, 4, 0);
        HuAudCharVoicePlay((m263_chrDirTbl[m263_playerChr] << 16) | 0x35);
    }
    if (object->work[0] < 9) {
        Hu3DData[model].rot.y = 90.0f - object->work[0] * 11.25f;
        if (object->work[0] == 8) {
            Hu3DMotionShiftSet(model, m263_motTbl[32], 0, 8, 2);
        }
    }
}

void m263_SwingInit(void) {
    HmfSkeletonNode *node;

    node = Hu3DModelObjPtrGet(m263_mdlTbl[2], "rope");
    mtxCopy(m263_ropeBaseMtx, node->unk4C);
    node = Hu3DModelObjPtrGet(m263_mdlTbl[2], "step");
    mtxCopy(m263_stepBaseMtx, node->unk4C);
    m263_swingPhase = 0.0f;
}

void m263_SwingStartObjMain(omObjData *object) {
    switch (m263_swingState) {
        case 0:
            if (m263_swingPhase == 0.0f) {
                m263_swingSeNo = HuAudFXPlay(0x4EA);
            }
            m263_swingAngle = sindf(m263_swingPhase) * m263_swingAmp;
            m263_swingPhase += 5.0f;
            if (m263_swingPhase > 360.0f) {
                m263_swingPhase -= 360.0f;
                m263_swingState++;
            }
            break;
        case 1:
            m263_swingAngle = sindf(m263_swingPhase) * 180.0f;
            m263_swingPhase += 5.0f;
            if (m263_swingPhase > 90.0f) {
                m263_swingState++;
                m263_swingAmp = 180.0f;
            }
            break;
        case 2:
            m263_swingAngle = -sindf(m263_swingPhase) * m263_swingAmp;
            m263_swingPhase += 5.0f;
            m263_swingAmp -= 6.0f;
            if (m263_swingPhase > 180.0f) {
                m263_swingAmp = 80.0f;
                m263_swingPhase += 180.0f;
                object->func = m263_SwingObjMain;
            }
            break;
    }
    m263_SwingAngleSet(m263_swingAngle);
}

void m263_SwingObjMain(omObjData *object) {
    m263_swingAngle = sindf(m263_swingPhase) * m263_swingAmp;
    m263_swingPhase += 5.0f;
    if (m263_swingPhase > 360.0f) {
        m263_swingPhase -= 360.0f;
    }
    m263_SwingAngleSet(m263_swingAngle);
    if (m263_phase == 2) {
        object->func = m263_SwingStopObjMain;
    }
}

void m263_SwingStopObjMain(omObjData *object) {
    if (m263_swingAmp > 0.0f) {
        m263_swingAngle = sindf(m263_swingPhase) * m263_swingAmp;
        m263_swingPhase += 5.0f;
        if (m263_swingPhase > 360.0f) {
            m263_swingPhase -= 360.0f;
        }
        m263_swingAmp -= 0.5f;
        if (m263_swingAmp <= 0.0f) {
            m263_swingAmp = 0.0f;
        }
        m263_SwingAngleSet(m263_swingAngle);
    }
}

void m263_FloatInit(void) {
    SharkState *shark;
    s16 i;

    for (i = 0; i < 5; i++) {
        shark = &m263_floatTbl[i];
        shark->model = m263_mdlTbl[i + 3];
        Hu3DModelPosGet(shark->model, &shark->pos);
        shark->unk20 = rand8() & 0xF8;
        shark->unk02 = 0;
        shark->unk04 = 30;
        Hu3DAnimBankSet(Hu3DAnimRead(Hu3DData[m263_mdlTbl[i + 8]].hmf, 0x21002C, "m259_30_000_DEF"),
                        mgInstColumnTbl[i]);
        Hu3DModelRemakeStatic(m263_mdlTbl[i + 8]);
        Hu3DModelDynamicFree(m263_mdlTbl[i + 8]);
        shark->unk24 = rand8() & 0x3F;
        Hu3DModelTPLvlInit(m263_mdlTbl[i + 18]);
        Hu3DModelDynamicFree(m263_mdlTbl[i + 18]);
    }
    m263_prizeEffNo = EffectCreate(0xB0004, 0x2A9);
    Hu3DParticleAttrSet(m263_prizeEffNo, 1, 0);
}

void m263_FloatObjMain(omObjData *object) {
    SharkState *shark;
    HmfModel *model;
    s16 i;
    s16 splash;
    f32 scale;

    if (m263_hitFloatNo != -1) {
        i = m263_hitFloatNo;
        shark = &m263_floatTbl[i];
        model = &Hu3DData[shark->model];
        if (shark->unk02 < 50) {
            shark->cur.y = sindf(shark->unk02 * 30) * shark->unk04 + shark->pos.y - 50.0f;
            Hu3DModelPosSet(shark->model, shark->cur.x, shark->cur.y, shark->cur.z);
            Hu3DData[shark->model].rot.z = 0.0f;
            Hu3DModelPosSet(m263_mdlTbl[i + 8], model->pos.x, model->pos.y,
                            model->pos.z - ((i & 1) * 10 + 80));
            Hu3DData[m263_mdlTbl[i + 8]].rot.z = 0.0f;
            Hu3DModelPosSet(m263_mdlTbl[i + 13], model->pos.x, model->pos.y,
                            model->pos.z - ((i & 1) * 10 + 80));
            Hu3DData[m263_mdlTbl[i + 13]].rot.z = 0.0f;
            shark->unk04--;
            if (++shark->unk02 == 50) {
                shark->unk20 = 500.0f;
                Hu3DModelAttrSet(m263_mdlTbl[43], 4, 0);
                Hu3DModelRotSet(m263_mdlTbl[43], CRot.x, CRot.y, CRot.z);
                Hu3DModelScaleSet(m263_mdlTbl[43], 4.0f, 4.0f, 4.0f);
                Hu3DModelPosSet(m263_mdlTbl[43], model->pos.x, model->pos.y + 300.0f,
                                model->pos.z);
            }
        } else {
            shark->cur.y = sindf(shark->unk20) * 5.0f + shark->pos.y - 50.0f;
            shark->unk20 += 10.0f;
            if (shark->unk20 > 1440.0f) {
                shark->unk20 -= 1440.0f;
            }
            Hu3DModelPosSet(shark->model, shark->cur.x, shark->cur.y, shark->cur.z);
            if (shark->unk02 > 60) {
                Hu3DModelAttrSet(m263_mdlTbl[i + 8], 4, 4);
                Hu3DModelAttrSet(m263_mdlTbl[i + 13], 4, 4);
            } else {
                shark->unk02++;
            }
            if (shark->unk02 == 60) {
                omAddObj(900, 0, 0, -1, m263_PrizeObjInit);
            }
            Hu3DModelPosSet(m263_mdlTbl[i + 8], model->pos.x, model->pos.y,
                            model->pos.z - ((i & 1) * 10 + 80));
            Hu3DModelPosSet(m263_mdlTbl[i + 13], model->pos.x, model->pos.y,
                            model->pos.z - ((i & 1) * 10 + 80));
        }
    }
    if (m263_phase < 3) {
        for (i = 0; i < 5; i++) {
            if (i == m263_hitFloatNo) {
                continue;
            }
            shark = &m263_floatTbl[i];
            shark->cur.x = sindf(shark->unk20 / 4.0f) * 50.0f + shark->pos.x;
            shark->cur.y = sindf(shark->unk20) * 10.0f + shark->pos.y;
            shark->cur.z = shark->pos.z;
            shark->unk20 += 10.0f;
            if (shark->unk20 > 1440.0f) {
                shark->unk20 -= 1440.0f;
            }
            Hu3DModelPosSet(shark->model, shark->cur.x, shark->cur.y, shark->cur.z);
            Hu3DData[shark->model].rot.z = sindf(shark->unk20 / 2.0f) * 5.0f;
            Hu3DModelPosSet(m263_mdlTbl[i + 8], shark->cur.x, shark->cur.y,
                            shark->cur.z - ((i & 1) * 10 + 80));
            Hu3DData[m263_mdlTbl[i + 8]].rot.z = sindf(shark->unk20 / 2.0f) * 5.0f;
            Hu3DModelPosSet(m263_mdlTbl[i + 13], shark->cur.x, shark->cur.y,
                            shark->cur.z - ((i & 1) * 10 + 80));
            Hu3DData[m263_mdlTbl[i + 13]].rot.z = sindf(shark->unk20 / 2.0f) * 5.0f;
        }
    } else {
        for (i = 0; i < 5; i++) {
            shark = &m263_floatTbl[i];
            if (i == m263_hitFloatNo || shark->cur.y < -1500.0f) {
                continue;
            }
            if (shark->cur.y > -80.0f) {
                shark->cur.y -= 4.0f;
                shark->unk20 = 0.0f;
                shark->unk04 = (u8)(rand8() & 0xF) - 8;
                Hu3DData[shark->model].rot.z = 0.0f;
                scale = shark->cur.y * 0.0125f + 1.0f;
                Hu3DModelScaleSet(m263_mdlTbl[i + 13], scale, scale, scale);
                Hu3DModelScaleSet(m263_mdlTbl[i + 8], scale, scale, scale);
                Hu3DModelPosSet(m263_mdlTbl[i + 13], shark->cur.x, 0.0f,
                                shark->cur.z - ((i & 1) * 10 + 80));
                Hu3DData[m263_mdlTbl[i + 13]].rot.z = 0.0f;
                Hu3DModelPosSet(m263_mdlTbl[i + 8], shark->cur.x, shark->cur.y,
                                shark->cur.z - ((i & 1) * 10 + 80));
                Hu3DData[m263_mdlTbl[i + 8]].rot.z = 0.0f;
                if (shark->cur.y <= -80.0f) {
                    Hu3DModelAttrSet(m263_mdlTbl[i + 23], 4, 0);
                    Hu3DModelPosSet(m263_mdlTbl[i + 23], shark->cur.x, 0.0f, shark->cur.z);
                    Hu3DMotionSpeedSet(m263_mdlTbl[i + 23], 1.0f);
                    Hu3DModelScaleSet(m263_mdlTbl[i + 23], 1.0f, 1.0f, 1.0f);
                }
            } else {
                Hu3DModelAttrSet(m263_mdlTbl[i + 8], 4, 4);
                Hu3DModelAttrSet(m263_mdlTbl[i + 13], 4, 4);
                shark->cur.y -= 8.0f;
                shark->unk20 += shark->unk04 / 10.0f;
                Hu3DData[shark->model].rot.z = shark->unk20;
            }
            Hu3DModelPosSet(shark->model, shark->cur.x, shark->cur.y, shark->cur.z);
        }
    }
    for (i = 0; i < 5; i++) {
        shark = &m263_floatTbl[i];
        splash = m263_mdlTbl[i + 18];
        if (shark->unk24 <= 90) {
            Hu3DModelPosSet(splash, shark->cur.x, 0.0f, shark->cur.z);
            scale = sindf((s16)(shark->unk24 % 90)) + 0.8f;
            Hu3DModelScaleSet(splash, scale, scale, scale);
            Hu3DModelTPLvlSet(splash, 255.0f - shark->unk24 * 2.8333333f);
            shark->unk24 += 2;
            if (shark->unk24 > 90) {
                if (shark->cur.y < -50.0f && m263_hitFloatNo != i) {
                    shark->unk24 = 90;
                } else {
                    shark->unk24 = 0;
                }
            }
        }
    }
}

void m263_PrizeObjInit(omObjData *object) {
    HmfModel *shark = &Hu3DData[m263_mdlTbl[m263_hitFloatNo + 3]];
    s16 model;

    m263_prizeSpr =
        SprModelRead(m263_itemSprFileTbl[mgInstColumnTbl[m263_hitFloatNo]], 0xA4, 0x10);
    model = Hu3DSprModelData[m263_prizeSpr].modelId;
    Hu3DModelScaleSet(model, 5.0f, 5.0f, 5.0f);
    Hu3DModelPosSet(model, shark->pos.x, 200.0f, shark->pos.z - 80.0f);
    Hu3DSprModelReset(m263_prizeSpr);
    object->work[0] = 0;
    object->work[1] = 0;
    Hu3DParticleAttrSet(m263_prizeEffNo, 1, 1);
    EffectParamSet(m263_prizeEffNo, 8.0f, 20.0f, 10.0f);
    EffectRangeSet(m263_prizeEffNo, 150.0f);
    EffectPosSet(m263_prizeEffNo, shark->pos.x, 200.0f, shark->pos.z - 80.0f);
    HuAudFXPlay(0x4EE);
    object->func = m263_PrizeObjMain;
}

void m263_PrizeObjMain(omObjData *object) {
    HmfModel *shark = &Hu3DData[m263_mdlTbl[m263_hitFloatNo + 3]];
    s16 model = Hu3DSprModelData[m263_prizeSpr].modelId;
    HmfModel *spr = &Hu3DData[model];

    switch (object->work[0]) {
        case 0:
            Hu3DModelPosSet(model, shark->pos.x, sindf(object->work[1] * 9.0f) * 200.0f + 200.0f, shark->pos.z - (80.0f - sindf(object->work[1] * 9.0f) * 80.0f));
            EffectPosSet(m263_prizeEffNo, spr->pos.x, spr->pos.y - 50.0f, spr->pos.z);
            if (++object->work[1] > 10) {
                GwPlayer[m263_playerNo].bonusCoin = mgInstColumnTbl[m263_hitFloatNo];
                object->work[0] = 1;
                object->work[1] = 0;
                m263_CameraMoveStart(334.0f, 0.0f, 0.0f, shark->pos.x, 300.0f, shark->pos.z, 2500.0f, 20);
            }
            break;
        case 1:
            Hu3DData[model].pos.y = sindf(object->work[1]) * 20.0f + 400.0f;
            EffectPosSet(m263_prizeEffNo, spr->pos.x, spr->pos.y - 50.0f, spr->pos.z);
            object->work[1] += 10;
            break;
    }
}

void m263_CameraMoveStart(f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ, f32 zoom,
                                        s16 time) {
    m263_cameraMoveRotStart = CRot;
    m263_cameraMoveCenterStart = Center;
    m263_cameraMoveZoomStart = CZoom;
    m263_cameraMoveRotEnd.x = rotX;
    m263_cameraMoveRotEnd.y = rotY;
    m263_cameraMoveRotEnd.z = rotZ;
    m263_cameraMoveCenterEnd.x = centerX;
    m263_cameraMoveCenterEnd.y = centerY;
    m263_cameraMoveCenterEnd.z = centerZ;
    m263_cameraMoveZoomEnd = zoom;
    m263_cameraMoveTimer = m263_cameraMoveTime = time;
}

void m263_CameraMoveObjMain(omObjData *object) {
    f32 t;

    if (m263_cameraMoveTimer != 0) {
        m263_cameraMoveTimer--;
        t = sindf((1.0f - (f32)m263_cameraMoveTimer / m263_cameraMoveTime) * 90.0f);
        CRot.x = (-m263_cameraMoveRotStart.x + m263_cameraMoveRotEnd.x) * t +
                 m263_cameraMoveRotStart.x;
        CRot.y = (-m263_cameraMoveRotStart.y + m263_cameraMoveRotEnd.y) * t +
                 m263_cameraMoveRotStart.y;
        CRot.z = (-m263_cameraMoveRotStart.z + m263_cameraMoveRotEnd.z) * t +
                 m263_cameraMoveRotStart.z;
        Center.x = (-m263_cameraMoveCenterStart.x + m263_cameraMoveCenterEnd.x) * t +
                   m263_cameraMoveCenterStart.x;
        Center.y = (-m263_cameraMoveCenterStart.y + m263_cameraMoveCenterEnd.y) * t +
                   m263_cameraMoveCenterStart.y;
        Center.z = (-m263_cameraMoveCenterStart.z + m263_cameraMoveCenterEnd.z) * t +
                   m263_cameraMoveCenterStart.z;
        CZoom = (-m263_cameraMoveZoomStart + m263_cameraMoveZoomEnd) * t + m263_cameraMoveZoomStart;
    }
}

void m263_SeaInit(void) {
    Hu3DModelVtxBufMake(m263_mdlTbl[0]);
    m263_seaScroll = 0;
}

void m263_SeaObjMain(omObjData *object) {
    Hu3DModelObjTexScroll(m263_mdlTbl[0], 0, -m263_seaScroll, 32, 32, "sea", 0);
    if (omPauseChk() + omAllPauseF == 0) {
        m263_seaScroll += 0.3f;
        if (m263_seaScroll > 32.0f) {
            m263_seaScroll = 0.0f;
        }
    }
}

void m263_SwingAngleSet(f32 angle) {
    HmfSkeletonNode *rope;
    HmfSkeletonNode *step;
    s32 deg;
    f32 swing;

    if (m263_swingSeNo != -1) {
        deg = (s32)(angle + 360.0f) % 360;
        if (deg > 180) {
            deg = 360 - deg;
        }
        swing = deg;
        HuAudFXPitchSet(m263_swingSeNo, (s16)(swing * 6.6666665f));
        HuAudFXVolSet(m263_swingSeNo, 127.0f - swing * 0.35f);
    }
    rope = Hu3DModelObjPtrGet(m263_mdlTbl[2], "rope");
    mtxCopy(rope->unk4C, m263_ropeBaseMtx);
    m263_MtxRotZCat(rope->unk4C, angle);
    step = Hu3DModelObjPtrGet(m263_mdlTbl[2], "step");
    mtxCopy(step->unk4C, rope->unk4C);
    mtxTransCat(step->unk4C, step->unk08.x, step->unk08.y, step->unk08.z);
}

void m263_StepPosGet(Vec *pos) {
    HmfSkeletonNode *node = Hu3DModelObjPtrGet(m263_mdlTbl[2], "step");

    m263_NodePosGet(m263_mdlTbl[2], pos, node->unk4C);
}

void m263_RopePosGet(Vec *pos) {
    HmfSkeletonNode *node = Hu3DModelObjPtrGet(m263_mdlTbl[2], "rope");

    m263_NodePosGet(m263_mdlTbl[2], pos, node->unk4C);
}

void m263_MtxRotZCat(HuMtx4F mtx, f32 angle) {
    f32 row[3];
    f32 s;
    f32 c;
    s32 i;

    row[0] = angle * m263_degToRad;
    s = sinf(row[0]);
    c = cosf(row[0]);
    for (i = 0; i < 3; i++) {
        row[i] = mtx[0][i];
    }
    for (i = 0; i < 3; i++) {
        mtx[0][i] = c * row[i] + s * mtx[1][i];
        mtx[1][i] = -row[i] * s + c * mtx[1][i];
    }
}

void m263_NodePosGet(s16 model, Vec *pos, HuMtx4F mtx) {
    HmfModel *hmf = &Hu3DData[model];
    HuMtx4F local;
    HuMtx4F result;

    HuTranslateF(local, hmf->pos.x, hmf->pos.y, hmf->pos.z);
    mtxRotCat(local, hmf->rot.x, hmf->rot.y, hmf->rot.z);
    mtxScaleCat(local, hmf->scale.x, hmf->scale.y, hmf->scale.z);
    mtxCat(mtx, local, result);
    pos->x = result[0][0] + result[1][0] + result[2][0] + result[3][0];
    pos->y = result[0][1] + result[1][1] + result[2][1] + result[3][1];
    pos->z = result[0][2] + result[1][2] + result[2][2] + result[3][2];
}

void m263_CameraDebugPad(void) {
    char buf[256];
    f32 rotX;
    f32 rotY;
    f32 speed;
    f32 dirZ;
    f32 inv;

    if (HuPadBtnDown[0] & R_TRIG) {
        m263_debugPrintF ^= 1;
    }
    if (HuPadBtn[0] & START_BUTTON) {
        m263_CameraDebugReset();
    }
    if (HuPadBtn[0] & 8) {
        CZoom = (HuPadBtn[0] & Z_TRIG) ? CZoom + 30.0f : CZoom + 10.0f;
    }
    if ((HuPadBtn[0] & 4) && CZoom - 10.0f != 0.0f) {
        CZoom = (HuPadBtn[0] & Z_TRIG) ? CZoom - 30.0f : CZoom - 10.0f;
    }
    if (HuPadBtn[0] & 2) {
        m263_cameraFov += 1.0f;
    }
    if (HuPadBtn[0] & 1) {
        m263_cameraFov -= 1.0f;
    }
    Hu3DCameraPerspectiveSet(0, m263_cameraFov, 500.0f, 8000.0f);
    rotX = m263_cameraDebugRot.x;
    rotY = m263_cameraDebugRot.y;
    speed = (HuPadBtn[0] & Z_TRIG) ? 5.0f : 2.0f;
    rotY += (-HuPadStkX[0] / 30) * speed;
    if (rotY >= 360.0f) {
        rotY -= 360.0f;
    } else if (rotY < 0.0f) {
        rotY += 360.0f;
    }
    m263_cameraDebugRot.y = rotY;
    rotX += (s8)(HuPadStkY[0] / 30) * speed;
    if (rotX >= 360.0f) {
        rotX -= 360.0f;
    } else if (rotX < 0.0f) {
        rotX += 360.0f;
    }
    m263_cameraDebugRot.x = rotX;
    CRot.x = (s16)rotX;
    CRot.y = (s16)m263_cameraDebugRot.y;
    speed = (HuPadBtn[0] & Z_TRIG) ? 10.0f : 2.0f;
    if (HuPadBtn[0] & U_JPAD) {
        Center.x += sindf(rotY) * sindf(rotX) * -speed;
        Center.y += cosdf(rotX) * -speed;
        Center.z += cosdf(rotY) * sindf(rotX) * -speed;
    } else if (HuPadBtn[0] & D_JPAD) {
        Center.x += sindf(rotY) * sindf(rotX) * speed;
        Center.y += cosdf(rotX) * speed;
        Center.z += cosdf(rotY) * sindf(rotX) * speed;
    } else if (HuPadBtn[0] & L_JPAD) {
        // rotX is reused here as the X component of the camera direction.
        rotX = gCameraList->pos.z - Center.z;
        dirZ = -(gCameraList->pos.x - Center.x);
        inv = 1.0f / HuSqrtf(rotX * rotX + dirZ * dirZ);
        Center.x += rotX * inv * speed;
        Center.y += 0.0f;
        Center.z += dirZ * inv * speed;
    } else if (HuPadBtn[0] & R_JPAD) {
        rotX = -(gCameraList->pos.z - Center.z);
        dirZ = gCameraList->pos.x - Center.x;
        inv = 1.0f / HuSqrtf(rotX * rotX + dirZ * dirZ);
        Center.x += rotX * inv * speed;
        Center.y += 0.0f;
        Center.z += dirZ * inv * speed;
    }
    if (m263_debugPrintF) {
        sprintf(buf, "CROT %4.1f,%4.1f,%4.1f", CRot.x, CRot.y, CRot.z);
        print8(32, 180, buf);
        sprintf(buf, "INT %4.1f,%4.1f,%4.1f", Center.x, Center.y, Center.z);
        print8(32, 190, buf);
        sprintf(buf, "CZOOM %4.1f  FOVY %4.1f", CZoom, m263_cameraFov);
        print8(32, 200, buf);
    }
}

void m263_CameraDebugReset(void) {
    CRot = m263_cameraRotInit;
    m263_cameraDebugRot = CRot;
    CZoom = m263_cameraZoomInit;
    Center = m263_cameraCenterInit;
}

void m263_MdlEntryPosSet(SharkEntry *arg0, s16 arg1, s16 modelId) {
    SharkEntry *entry = &arg0[arg1];
    Hu3DModelPosSet(modelId, entry->pos.x, entry->pos.y, entry->pos.z);
    Hu3DModelRotSet(modelId, entry->rot.x, entry->rot.y, entry->rot.z);
}

void m263_MdlEntryCreateAll(SharkEntry *entries) {
    SharkEntry *entry = entries;
    s16 i;
    s16 model;

    for (i = 0; entry->dataNum != -1; i++, entry++) {
        if ((entry->dataNum & 0xFFFF0000) == 0xFFFF0000) {
            entry->dataNum = CharMotionDataNumGet(m263_playerChr, (s16)entry->dataNum);
        }
        m263_mdlTbl[i] = Hu3DModelRead(entry->dataNum, entry->attr | 0x288);
        model = m263_mdlTbl[i];
        m263_MdlEntryPosSet(entries, i, model);
        m263_motTbl[i] = Hu3DData[model].motId;
        if (m263_motTbl[i] != -1) {
            Hu3DMotionAttrSet(model, -1, entry->motAttr);
        }
    }
}

void m263_ExitCheckObjMain(omObjData *object) {
    if (m263_exitF != 0 || omSysExitReq != 0) {
        WipeCreateOut(0, 20);
        object->func = m263_ExitObjMain;
        HuAudSeqFadeOut(60);
        HuAudFXAllFadeOut(30);
    }
}

void m263_ExitObjMain(omObjData *object) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

void m263_SharkProc(void) {
    s16 model;
    s16 n;
    s16 path;
    f32 total;

    if (m263_sharkNum == 0) {
        model = m263_sharkMdl = Hu3DModelRead(0xA0154, 0x299);
        m263_sharkMot = Hu3DMotionModelRead(0xA0155);
    } else {
        model = Hu3DModelLink(m263_sharkMdl);
    }
    Hu3DMotionModelSet(model, m263_sharkMot);
    n = m263_sharkNum++;
    m263_sharkMdlTbl[n] = model;
    path = n % 2;
    Hu3DMotionAttrSet(model, 2, 2);
    Hu3DMotionTimeSet(model, n * 10);
    Hu3DModelPosSet(model, 0.0f, -100.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 90.0f, 0.0f);
    total = m263_PathTimeCalc(m263_sharkPathTbl[path], 20.0f);
    while (TRUE) {
        m263_SharkPathMove(m263_sharkPathTbl[path], model, total);
        HuPrcVSleep();
    }
}

f32 m263_PathTimeCalc(SharkPathPoint *points, f32 speed) {
    SharkPathPoint *prev;
    SharkPathPoint *point;
    f32 total;
    f32 dist;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 i;

    prev = NULL;
    total = 0.0f;
    for (i = 0, point = points; point->pos.x != 0.0f || point->pos.y != 0.0f || point->pos.z != 0.0f;
         i++, point = &points[i]) {
        if (i > 0) {
            dx = prev->pos.x - point->pos.x;
            dy = prev->pos.y - point->pos.y;
            dz = prev->pos.z - point->pos.z;
            dist = HuSqrtf(dx * dx + dy * dy + dz * dz);
            if (dist == 0.0f) {
                dist = speed * 10.0f;
            }
            total += dist / speed;
            point->dist = total;
        }
        prev = point;
    }
    return total;
}

void m263_SharkPathMove(SharkPathPoint *points, s16 model, f32 total) {
    f32 values[4];
    f32 times[4];
    Vec prevPos;
    f32 end;
    f32 x;
    f32 y;
    f32 z;
    f32 angle;
    f32 delta;
    s16 sink;
    s16 i;
    s16 t;

    sink = 0;
    while (TRUE) {
        end = total - 10.0f;
        i = 1;
        for (t = 10; t < end; t++) {
            if (t > points[i + 1].dist) {
                i++;
            }
            Hu3DModelPosGet(model, &prevPos);
            times[0] = points[i - 1].dist;
            times[1] = points[i].dist;
            times[2] = points[i + 1].dist;
            times[3] = points[i + 2].dist;
            values[0] = points[i - 1].pos.x;
            values[1] = points[i].pos.x;
            values[2] = points[i + 1].pos.x;
            values[3] = points[i + 2].pos.x;
            x = InterpolateBMLine(values, times, t);
            values[0] = points[i - 1].pos.y;
            values[1] = points[i].pos.y;
            values[2] = points[i + 1].pos.y;
            values[3] = points[i + 2].pos.y;
            y = InterpolateBMLine(values, times, t);
            values[0] = points[i - 1].pos.z;
            values[1] = points[i].pos.z;
            values[2] = points[i + 1].pos.z;
            values[3] = points[i + 2].pos.z;
            z = InterpolateBMLine(values, times, t);
            Hu3DModelPosSet(model, x, y, z);
            x -= prevPos.x;
            z -= prevPos.z;
            if (z != 0.0f || x != 0.0f) {
                Hu3DData[model].rot.y = atan2df(x, z);
            }
            if (m263_phase >= 3) {
                if (m263_hitFloatNo == -1) {
                    if (sink < 20) {
                        sink++;
                        y = Hu3DData[model].pos.y;
                        angle = sink * 4.5f;
                        delta = sindf(angle) * (-30.0f - y);
                        Hu3DData[model].pos.y = y + delta;
                        delta = sindf(angle) * -30.0f;
                        Hu3DData[model].rot.x = delta;
                    } else {
                        Hu3DData[model].pos.y = -30.0f;
                        Hu3DData[model].rot.x = -30.0f;
                    }
                } else {
                    Hu3DData[model].pos.y -= sink * 10;
                    sink++;
                }
            }
            HuPrcVSleep();
        }
    }
}

void m263_KoopaLookUpdate(void) {
    s16 model = m263_mdlTbl[47];
    HmfModel *target;
    HmfModel *self;
    HmfMotionNode *node;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 angle;

    if (Hu3DData[model].motId != m263_motTbl[47]) {
        Hu3DMotionNoMotReset(model, Hu3DData[model].motId, "c162_000-atama", 0x4C, 0x46);
        return;
    }
    target = &Hu3DData[m263_mdlTbl[32]];
    self = &Hu3DData[model];
    dx = target->pos.x - self->pos.x;
    dy = target->pos.y - self->pos.y;
    dz = target->pos.z - self->pos.z;
    angle = atan2df(dx, dz);
    Hu3DMotionNoMotSet(model, Hu3DData[model].motId, "c162_000-atama", 0x4C, 0x46);
    node = Hu3DModelObjPtrGet(model, "c162_000-atama");
    node->baseRot.y = node->rot.y = angle - self->rot.y;
    Hu3DMotionNoMotSet(model, Hu3DData[model].motId, "c162_000-atama", 0x4C, 0x45);
    node->baseRot.x = node->rot.x = -atan2df(dy, dz);
}

void m263_ShadowUpdate(void) {
    s16 model = m263_mdlTbl[33];
    HmfModel *base = &Hu3DData[m263_mdlTbl[32]];
    s16 alpha;
    f32 len;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 t;
    f32 x;
    f32 z;

    if (base->pos.y < 90.0f) {
        alpha = (base->pos.y - 40.0f) / 50.0f * 102.0f;
        if (alpha <= 0) {
            alpha = 0;
            Hu3DModelAttrSet(model, 4, 4);
        }
        Hu3DModelTPLvlSet(model, alpha);
    } else {
        Hu3DModelAttrSet(model, 4, 0);
        Hu3DModelTPLvlSet(model, 102);
    }
    len = HuSqrtf(-1.3f * -1.3f + -1.0f * -1.0f + -1.3f * -1.3f);
    dx = -1.3f / len;
    dy = -1.0f / len;
    dz = -1.3f / len;
    t = 1.0f / dy;
    if (t < 0.0f) {
        t = -t;
    }
    dx *= t;
    dz *= t;
    x = dx * base->pos.y + base->pos.x;
    z = dz * base->pos.y + base->pos.z;
    Hu3DModelPosSet(model, x, 0.0f, z);
}

void m263_WakeInit(void) {
    s16 i;

    Hu3DModelTPLvlInit(m263_mdlTbl[46]);
    Hu3DModelDynamicFree(m263_mdlTbl[46]);
    for (i = 0; i < 20; i++) {
        m263_wakeMdlTbl[i] = Hu3DModelRead(0xB0031, 0xA8C);
        m263_wakeTimerTbl[i] = 90;
        Hu3DModelTPLvlInit(m263_wakeMdlTbl[i]);
        Hu3DModelDynamicFree(m263_wakeMdlTbl[i]);
    }
}

void m263_WakeUpdate(void) {
    HmfModel *source;
    f32 scale;
    s16 model;
    s16 i;
    s16 j;

    for (i = 0; i < 2; i++) {
        if (((m263_wakeTimer + i * 2) & 7) == 0) {
            source = &Hu3DData[m263_sharkMdlTbl[i]];
            if (!(source->pos.y < -100.0f)) {
                for (j = 0; j < 20; j++) {
                    if (m263_wakeTimerTbl[j] >= 90) {
                        m263_wakeTimerTbl[j] = 0;
                        Hu3DModelPosSet(m263_wakeMdlTbl[j], source->pos.x, 0.0f, source->pos.z);
                        Hu3DModelRotSet(m263_wakeMdlTbl[j], 0.0f, source->rot.y, 0.0f);
                        Hu3DModelAttrSet(m263_wakeMdlTbl[j], 4, 0);
                        break;
                    }
                }
            }
        }
    }
    model = m263_mdlTbl[46];
    scale = sindf(m263_wakeTimer % 90) * 1.5f + 0.5f;
    Hu3DModelScaleSet(model, scale, scale, scale);
    Hu3DModelTPLvlSet(model, 255.0f - m263_wakeTimer * (255.0f / 90.0f));
    m263_wakeTimer += 2;
    if (m263_phase >= 3 &&
        Hu3DData[m263_mdlTbl[47]].motId == m263_motTbl[49]) {
        if (m263_wakeTimer > 90) {
            Hu3DModelAttrSet(model, 4, 4);
        }
        if ((m263_wakeTimer & 0xF) == 0) {
            source = &Hu3DData[m263_mdlTbl[44]];
            for (j = 0; j < 20; j++) {
                if (m263_wakeTimerTbl[j] >= 90) {
                    m263_wakeTimerTbl[j] = 0;
                    Hu3DModelPosSet(m263_wakeMdlTbl[j], source->pos.x, 0.0f, source->pos.z);
                    Hu3DModelRotSet(m263_wakeMdlTbl[j], 0.0f, source->rot.y, 0.0f);
                    Hu3DModelAttrSet(m263_wakeMdlTbl[j], 4, 0);
                    break;
                }
            }
        }
    }
    if (m263_wakeTimer > 90) {
        m263_wakeTimer = 0;
    }
    for (i = 0; i < 20; i++) {
        if (m263_wakeTimerTbl[i] >= 90) {
            Hu3DModelAttrSet(m263_wakeMdlTbl[i], 4, 4);
        } else {
            scale = sindf(m263_wakeTimerTbl[i] % 90) * 1.5f;
            Hu3DModelScaleSet(m263_wakeMdlTbl[i], scale, scale, scale);
            Hu3DModelTPLvlSet(m263_wakeMdlTbl[i],
                               128.0f - m263_wakeTimerTbl[i] * (128.0f / 90.0f));
            m263_wakeTimerTbl[i] += 2;
        }
    }
}

void m263_KoopaInit(void) {
    m263_koopaRotY = Hu3DData[m263_mdlTbl[44]].rot.y;
}

void m263_KoopaUpdate(void) {
    s16 model = m263_mdlTbl[44];
    f32 x;
    f32 y;
    f32 z;

    if (m263_phase >= 3 &&
        Hu3DData[m263_mdlTbl[47]].motId == m263_motTbl[49]) {
        if (m263_koopaTurnTimer == 0) {
            Hu3DMotionShiftSet(m263_mdlTbl[model], m263_motTbl[45], 0, 4, 2);
        }
        if (++m263_koopaTurnTimer >= 30) {
            if (m263_koopaRotY < 90) {
                m263_koopaRotY += 1.5f;
            }
            x = Hu3DData[model].pos.x + sindf(m263_koopaRotY) * 10.0f;
            y = Hu3DData[model].pos.y;
            z = Hu3DData[model].pos.z + cosdf(m263_koopaRotY) * 10.0f;
            Hu3DModelPosSet(model, x, y, z);
            Hu3DData[model].rot.y = m263_koopaRotY;
            Hu3DData[m263_mdlTbl[47]].pos.x = x;
            Hu3DData[m263_mdlTbl[47]].pos.z = z;
            Hu3DData[m263_mdlTbl[47]].rot.y = m263_koopaRotY;
        }
    }
}
