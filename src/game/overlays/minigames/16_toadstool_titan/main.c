#include "common.h"
#include "gcc/memory.h"
#include "game/hmfmath.h"
#include "game/overlays/minigame.h"

typedef struct ToadstoolTitanPlayer {
    /* 0x00 */ s8 chr;
    /* 0x01 */ s8 playerNo;
    /* 0x02 */ s8 group;
    /* 0x03 */ s8 pad;
    /* 0x04 */ s8 cpuDifficulty; // -1 for human players
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0C */ s32 unk_0C;
} ToadstoolTitanPlayer; // sizeof 0x10

typedef struct ToadstoolTitanFlagWork {
    /* 0x00 */ u8 unk00[2];
    /* 0x02 */ u8 unk02[4];
} ToadstoolTitanFlagWork; // sizeof 0x6

typedef struct ToadstoolTitanBlockWork {
    /* 0x00 */ u8 unk00[9];
    /* 0x09 */ u8 unk09[4];
    /* 0x0D */ u8 unk0D[4]; // group of each player
} ToadstoolTitanBlockWork;    // sizeof 0x11

extern s32 omCharModelNoTbl[][6];
extern s16 HuAudMusNo;
extern s16 HuAudSubMusNo;
extern f32 CFanOfs;
extern f32 CFanLen;
extern omObjData *HuAudFadeObj;
extern f32 mgPlayerSpeedMax;
extern f32 mgPlayerSpeedRun;
extern f32 mgPlayerSpeedWalk;
extern f32 mgPlayerSpeedMin;
extern f32 mgPlayerStickDiv;
extern u8 Hu3DCameraNo;
extern s16 Hu3DCamMtxNo;
extern u8 omAllPauseF;
extern Gfx *gMainGfxPos;

u8 m222_blockNum = 0;       // number of Brick Blocks created so far
f32 m222_viewLeft = 0.0f;   // screen rect left
f32 m222_viewTop = 0.0f;   // screen rect top
f32 m222_viewRight = 320.0f; // screen rect right
f32 m222_viewBottom = 240.0f; // screen rect bottom
u8 m222_debrisTimerTbl[14] = { 0 };
u8 m222_blockBreakTimerTbl[9] = { 0 };
u8 m222_puffTimer = 0;
s16 m222_growEffTimer = 0;
s16 m222_growEffDoneF = 0;
f32 m222_growEffHeight = 0.0f;
f32 m222_growEffRot = 0.0f;
f32 m222_growEffScale = 0.0f;
f32 m222_growEffAlpha = 0.0f;
s16 m222_cloudTimer = 0;
s16 m222_cloudTimerTbl[3] = { 0 };

Gfx m222_gfxViewFrameInit[] = {
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

s32 m222_cameraInitF = 0; // set once the camera has been initialized
u8 m222_giantRunF = 0;
u8 m222_comStateTbl[4] = { 0 };
s16 m222_comWaitTbl[4] = { 0 };
s16 m222_comTimerTbl[4] = { 0 };
f32 m222_comOfsXTbl[4] = { 0.0f };
f32 m222_comOfsZTbl[4] = { 0.0f };

f32 m222_debrisXTbl[14] BSS;
f32 m222_debrisYTbl[14] BSS;
f32 m222_debrisZTbl[14] BSS;
f32 m222_debrisVelXTbl[14] BSS;
f32 m222_debrisVelYTbl[14] BSS;
f32 m222_debrisVelZTbl[14] BSS;
f32 m222_giantRunDir BSS;
u8 m222_giantRunDirPad[4] BSS; /* Unreferenced. */
ToadstoolTitanPlayer m222_playerTbl[4] BSS;
ToadstoolTitanPlayer *m222_groupPlayerTbl[4] BSS; // players indexed by group
u8 m222_groupPlayerTblPad[8] BSS;                    /* Unreferenced. */
u32 m222_phaseTimer BSS;
u8 m222_exitTimer BSS;
s16 m222_kinokoPhase BSS;
s16 m222_frameSprTbl[1] BSS;
s8 m222_winGroup BSS;
f32 m222_kinokoVelY BSS;
MinigameFlow m222_mgFlow BSS;
f32 m222_kinokoVelX BSS;
u16 m222_exitF BSS;
Vec m222_cameraTarget BSS;           // camera target
u8 m222_cameraTargetPad[4] BSS;         /* Unreferenced. */
omObjData *m222_blockObjTbl[9] BSS; // Brick Block objects
u8 m222_shakeTimer BSS;
omObjData *m222_stageObj BSS;
s16 m222_phase BSS;
f32 m222_musVol BSS; // music volume
f32 m222_kinokoZ BSS;
f32 m222_kinokoVelZ BSS;
s16 m222_frameSprDataTbl[1] BSS;
s8 m222_giantGroup BSS;
f32 m222_kinokoX BSS;
ToadstoolTitanFlagWork m222_flagWork BSS;
u32 m222_kinokoTimer BSS;
u8 m222_kinokoBlockNo BSS;
f32 m222_cameraFov BSS; // camera fov
Vec m222_cameraPos BSS; // camera position
s16 m222_motTimeTbl[4] BSS;
u8 m222_motTimeTblPad[4] BSS; /* Unreferenced. */
omObjData *m222_playerObjTbl[4] BSS;
ToadstoolTitanBlockWork m222_blockWork BSS;
f32 m222_kinokoY BSS;
u8 m222_startCornerTbl[4] BSS; // start corner of each group
u8 m222_humanNum BSS;    // number of human players
f32 m222_shakeAngle BSS;

/* Fields of m222_flagWork/m222_blockWork, aliased in undefined_syms.txt. */
extern u8 m222_musicFTbl[2];
extern u8 m222_outTimerTbl[4];
extern u8 m222_blockStateTbl[9];
extern u8 m222_outDirTbl[4];
extern u8 m222_playerGroupTbl[4]; // group of each player

const s16 m222_fontMesTbl[] = {
    0x8260, 0x8261, 0x8262, 0x8263, 0x8264, 0x8265, 0x8266, 0x8267, 0x8268, 0x8269, 0x826A, 0x826B, 0x826C,
    0x826D, 0x826E, 0x826F, 0x8270, 0x8271, 0x8272, 0x8273, 0x8274, 0x8275, 0x8276, 0x8277, 0x8278, 0x8279,
    0x824F, 0x8250, 0x8251, 0x8252, 0x8253, 0x8254, 0x8255, 0x8256, 0x8257, 0x8258, 0x0000, 0x0000
};

void m222_MainObjInit(omObjData *object);
void m222_MainObjMain(omObjData *object);
void m222_MusVolSave(void);
void m222_BlockObjInit(omObjData *object);
void m222_StageObjInit(omObjData *object);
void m222_StageObjMain(omObjData *object);
void m222_ViewFrameSet(s16 left, s16 top, s16 right, s16 bottom);
void m222_MotTimeSet(s16 model, s16 time);
void m222_PlayerInit(omObjData *object, s32 model, s32 motion, u16 group, f32 x, f32 y, f32 z);
void m222_Player0ObjInit(omObjData *object);
void m222_Player1ObjInit(omObjData *object);
void m222_Player2ObjInit(omObjData *object);
void m222_Player3ObjInit(omObjData *object);
void m222_CameraObjMain(omObjData *object);
void m222_PlayerObjMain(omObjData *object);

void m222_ObjectSetup(void) {
    omObjData *object;
    s32 i;

    MapCollInit(50);
    Hu3DQuadPoolInit(&mgQuadPool, 0x40);
    Hu3DSprModelInit(0x20);
    omInitObjMan(100, 0);
    omGameSysInit();
    Hu3DScreenClearF = 1;
    CamSetupInit(1);
    Hu3DCameraNo = CamSetupMapCullAdd();
    ScissorSet(Hu3DCameraNo, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(Hu3DCameraNo, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    MgPlayerParamReset();
    mgPlayerAccel = 15.0f;
    mgPlayerSpeedMax = 18.0f;
    mgPlayerSpeedRun = 13.5f;
    mgPlayerSpeedWalk = 9.0f;
    mgPlayerSpeedMin = 4.5f;
    MgShadowAltSet(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightDirSet(0, 0.0f, 73.0f, 95.0f);
    Hu3DGLightColorSet(0, 0x80, 0x80, 0x80);
    Hu3DGLightDirSet(1, 0.0f, 95.0f, 55.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(2, 0.0f, 95.0f, 55.0f);
    Hu3DGLightColorSet(2, 0xFF, 0xFF, 0xFF);
    omAddObj(0, 0, 0, -1, m222_MainObjInit);
    MgMapBaseSet(mgMapObjNum);
    object = omAddObj(4, 58, 58, -1, m222_StageObjInit);
    mgMapObjTbl[mgMapObjNum++] = m222_stageObj = object;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    for (i = 0; i < 9; i++) {
        mgMapObjTbl[mgMapObjNum++] = m222_blockObjTbl[i] = omAddObj(2, 2, 2, -1, m222_BlockObjInit);
    }
    mgPlayerObjTbl[mgPlayerObjNum++] = m222_playerObjTbl[0] = omAddObj(3, 12, 60, -1, m222_Player0ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = m222_playerObjTbl[1] = omAddObj(3, 12, 60, -1, m222_Player1ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = m222_playerObjTbl[2] = omAddObj(3, 12, 60, -1, m222_Player2ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = m222_playerObjTbl[3] = omAddObj(3, 12, 60, -1, m222_Player3ObjInit);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, m222_CameraObjMain), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    WipeCreateIn(0xFF, 30);
    GMesFontMesCreate(m222_fontMesTbl, 1);
    m222_mgFlow.type = MINIGAME_4P;
    m222_mgFlow.startDelay = 45;
    m222_mgFlow.timer = 1800;
    m222_mgFlow.timeDisp = MG_TIME_DISP_COUNTDOWN;
    m222_mgFlow.timerMode = MG_TIMER_COUNT_DOWN;
    m222_mgFlow.finishDelay = 60;
    m222_mgFlow.resultDelay = 165;
    m222_mgFlow.newRecord = FALSE;
    m222_mgFlow.gauge = MG_GAUGE_NONE;
    m222_mgFlow.timeLimit = -1;
    MgFlowInit(&m222_mgFlow);
}

void m222_Dummy(void) {
}

void m222_MainObjInit(omObjData *object) {
    s32 i;
    s32 j;

    m222_exitF = 0;
    m222_phase = 0;
    m222_phaseTimer = 0;
    m222_winGroup = 5;
    m222_exitTimer = 0;
    m222_kinokoPhase = 0;
    m222_kinokoTimer = 0;
    m222_giantGroup = -1;
    m222_outTimerTbl[0] = m222_outTimerTbl[1] = m222_outTimerTbl[2] = m222_outTimerTbl[3] = 0;
    m222_shakeTimer = 0;
    m222_humanNum = 0;
    m222_musicFTbl[0] = m222_musicFTbl[1] = 0;
    m222_musVol = -1.0f;
    for (i = 0; i < 4; i++) {
        m222_groupPlayerTbl[i] = &m222_playerTbl[i];
        bzero(m222_groupPlayerTbl[i], sizeof(ToadstoolTitanPlayer));
    }
    for (i = 0; i < 4; i++) {
        // j holds the player's group here; a separate variable changes the register allocation.
        j = m222_playerGroupTbl[i] = GwPlayer[i].group;
        m222_groupPlayerTbl[j]->playerNo = i;
        m222_groupPlayerTbl[j]->pad = GwPlayer[i].pad;
        m222_groupPlayerTbl[j]->chr = GwPlayer[i].chr;
        m222_groupPlayerTbl[j]->group = j;
        m222_groupPlayerTbl[j]->cpuDifficulty = (GwPlayer[i].stat & 1) ? GwPlayer[i].cpu_difficulty : -1;
        m222_humanNum += (m222_groupPlayerTbl[j]->cpuDifficulty == -1) ? 1 : 0;
    }
    for (i = 0; i < 4; i++) {
        m222_startCornerTbl[i] = rand8() & 3;
        for (j = 0; j < i; j++) {
            if (m222_startCornerTbl[i] == m222_startCornerTbl[j]) {
                i--;
                break;
            }
        }
    }
    object->func = m222_MainObjMain;
}

void m222_MainObjMain(omObjData *object) {
    MgPlayerWork *data;
    s16 i;

    m222_phaseTimer++;
    MgFlowMain();
    switch (m222_phase) {
        case 0:
            if (MgFlowStatGet() == MG_STATE_START) {
                m222_phase = 1;
                m222_phaseTimer = 0;
            }
            break;
        case 1:
            if (m222_phaseTimer == 61 && m222_exitF == 0 && omSysExitReq == 0) {
                HuAudSeqPlay(0x38);
                m222_musicFTbl[0] = 1;
            }
            if (MgFlowStatGet() == MG_STATE_PLAY) {
                m222_phase = 2;
                m222_phaseTimer = 0;
            }
            break;
        case 2:
            if (m222_phaseTimer == 1) {
                m222_MusVolSave();
            }
            if (m222_winGroup != 5 || MgFlowStatGet() == MG_STATE_FINISH) {
                if (m222_winGroup == 5) {
                    m222_phase = 6;
                    m222_winGroup = 4;
                    if (m222_kinokoPhase == 5) {
                        m222_kinokoTimer = 150;
                    }
                } else {
                    m222_phase = 3;
                }
                m222_phaseTimer = 0;
            }
            if (m222_phase != 3) {
                break;
            }
        case 3:
            if (m222_phaseTimer == 0) {
                if (MgFlowStatGet() != MG_STATE_FINISH) {
                    MgFlowStatNext();
                }
                m222_mgFlow.resultType = MG_RESULT_WIN_1;
                m222_mgFlow.winners[0] = m222_groupPlayerTbl[m222_winGroup]->playerNo;
                GwPlayer[m222_groupPlayerTbl[m222_winGroup]->playerNo].bonusCoin = 10;
                m222_musicFTbl[0] = 0;
                if (m222_musicFTbl[1] != 0 && m222_exitF == 0 && omSysExitReq == 0) {
                    HuAudSubSeqVolFadeOut(60);
                    m222_musicFTbl[1] = 0;
                }
            }
            if (m222_phaseTimer == 2) {
                MgFlowResultWaitSet(30);
                m222_mgFlow.finishDelay = 60;
            }
            if (MgFlowStatGet() == MG_STATE_RESULT) {
                m222_phase = 4;
                m222_phaseTimer = 0;
            }
            break;
        case 6:
            if (m222_phaseTimer == 1) {
                m222_mgFlow.resultType = MG_RESULT_DRAW;
                m222_mgFlow.finishDelay = 90;
                m222_mgFlow.resultDelay = 0x90;
                m222_musicFTbl[0] = 0;
                if (m222_musicFTbl[1] != 0 && m222_exitF == 0 && omSysExitReq == 0) {
                    HuAudSubSeqVolFadeOut(60);
                    m222_musicFTbl[1] = 0;
                }
            }
            if (m222_phaseTimer == 64 && m222_exitF == 0 && omSysExitReq == 0) {
                HuAudSeqStop();
            }
            if (m222_phaseTimer == 67 && m222_exitF == 0 && omSysExitReq == 0) {
                HuAudSeqVolFadeIn(3);
            }
            if (MgFlowStatGet() == MG_STATE_RESULT) {
                m222_phase = 5;
                m222_phaseTimer = 0;
            }
            break;
        case 4:
            if (m222_phaseTimer == 24 && m222_exitF == 0 && omSysExitReq == 0) {
                HuAudSeqStop();
            }
            if (m222_phaseTimer == 27 && m222_exitF == 0 && omSysExitReq == 0) {
                HuAudSeqVolFadeIn(3);
            }
            if (m222_phaseTimer == 29) {
                if (m222_kinokoPhase == 9) {
                    s32 slots[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

                    CharAnimSet(m222_playerObjTbl[m222_winGroup]->model[0], 1,
                                       slots[m222_groupPlayerTbl[m222_winGroup]->chr],
                                       m222_groupPlayerTbl[m222_winGroup]->unk_08);
                    MgPlayerMotLoad(
                        m222_playerObjTbl[m222_winGroup], 13,
                        CharMotionDataNumGet(m222_groupPlayerTbl[m222_winGroup]->chr, (rand8() & 1) ? 0x2F : 0x30), 1, 120);
                    HuAudCharVoicePlay(m222_groupPlayerTbl[m222_winGroup]->unk_0C);
                    msmMusStop(HuAudSubMusNo);
                }
            }
            if (m222_phaseTimer == 30 && m222_kinokoPhase == 9) {
                MgPlayerMotSet(m222_playerObjTbl[m222_winGroup], 13);
            }
        case 5:
            if (m222_phase == 5) {
                if (m222_phaseTimer == 1) {
                    for (i = 0; i < 4; i++) {
                        MgPlayerMotLoad(m222_playerObjTbl[i], 14, CharMotionDataNumGet(m222_groupPlayerTbl[i]->chr, 0x3A), 1,
                                               120);
                    }
                    msmMusStop(HuAudSubMusNo);
                }
                if (m222_phase == 5 && m222_phaseTimer >= 2) {
                    for (i = 0; i < 4; i++) {
                        data = m222_playerObjTbl[i]->data;
                        if (data->unk5C != 0x1000 && data->unk38 == 1000.0f) {
                            data->unk3C = 0.0f;
                            MgPlayerMotSet(m222_playerObjTbl[i], 14);
                        }
                    }
                }
            }
            if (MgFlowStatGet() == MG_STATE_EXIT) {
                m222_phase = 7;
                m222_phaseTimer = 0;
            }
            break;
        case 7:
            if (m222_phaseTimer == 1) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            } else if (m222_phaseTimer >= 32) {
                m222_exitF = 1;
            }
            break;
    }
    if (m222_exitF != 0 || omSysExitReq != 0) {
        if (omSysExitReq != 0) {
            if (m222_exitTimer == 0) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                HuAudSeqFadeOut(20);
                HuAudSubSeqVolFadeOut(20);
                HuAudFXAllFadeOut(20);
            }
            m222_exitTimer++;
            if (m222_exitTimer == 21 && HuAudFadeObj != NULL) {
                msmMusStop(HuAudMusNo);
                msmMusStop(HuAudSubMusNo);
            }
            if (m222_exitTimer == 23 && HuAudFadeObj != NULL && m222_musVol != -1.0f) {
                msmMusSetVolume(HuAudMusNo, m222_musVol);
            }
            if (m222_exitTimer < 25) {
                return;
            }
        }
        msmMusStop(HuAudMusNo);
        msmMusStop(HuAudSubMusNo);
        omOvlReturnEx(1);
    }
}

void m222_MusVolSave(void) {
    UnkAudioObjData *data;

    if (HuAudFadeObj != NULL) {
        data = HuAudFadeObj->data;
        m222_musVol = data->unk24 = data->unk2C = msmMusGetVolume(HuAudMusNo);
    }
}

void m222_BlockObjInit(omObjData *object) {
    f32 xs[9] = { 0.0f, 110.0f, 250.0f, 250.0f, 110.0f, -110.0f, -250.0f, -250.0f, -110.0f };
    f32 zs[9] = { 0.0f, -230.0f, -110.0f, 110.0f, 240.0f, 240.0f, 110.0f, -110.0f, -230.0f };
    MgMapWork *work;

    if (m222_blockNum == 0) {
        object->model[0] = Hu3DModelRead(0x370000, 0xBD);
    } else {
        object->model[0] = Hu3DModelLink(m222_blockObjTbl[0]->model[0]);
    }
    omSetTra(object, xs[m222_blockNum] * 1.11, 375.0f, zs[m222_blockNum] * 1.11 + 20.0);
    omSetSca(object, 0.6666667f, 0.6666667f, 0.6666667f);
    if (m222_blockNum == 0) {
        object->model[1] = Hu3DModelRead(0x370001, 0xBD);
    } else {
        object->model[1] = Hu3DModelLink(m222_blockObjTbl[0]->model[1]);
    }
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[1], 0.6666667f, 0.6666667f, 0.6666667f);
    work = object->data = HuMemAllocTag(0xB4, TAG_OVERLAY);
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    MgMapBlockSet(object, 50.0f, 100.0f, -60.0f, -60.0f, 60.0f,
                           (m222_blockNum >= 4 && m222_blockNum < 6) ? 120.0f : 60.0f);
    MgMapFrictionSet(object, 1.0f);
    MgMapAccelSet(object, 6.0f);
    work->unk04 = m222_blockNum + 1;
    m222_blockStateTbl[m222_blockNum] = 0;
    m222_blockNum++;
    object->func = NULL;
}

void m222_StageObjInit(omObjData *object) {
    s32 spriteFiles[1] = { 0x37000C };
    MgMapWork *work;
    s16 i;

    object->model[0] = -1;
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    work = object->data = HuMemAllocTag(0xB4, TAG_OVERLAY);
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    MgMapBoxSet(object, 0.0f, -475.0f, -425.0f, 475.0f, 425.0f);
    MgMapFrictionSet(object, 1.0f);
    MgMapAccelSet(object, 6.0f);
    MgMapNoBumpOn(object);
    work->unk04 = 0;
    for (i = 0; i < 1; i++) {
        m222_frameSprTbl[i] = espEntry(m222_frameSprDataTbl[i] = HuSprAnimDataRead(spriteFiles[i]), 0, 0);
        espDispOff(m222_frameSprTbl[i]);
    }
    object->model[1] = Hu3DModelRead(0x370002, 0x4BD);
    Hu3DModelScaleSet(object->model[1], 0.6666667f, 0.6666667f, 0.6666667f);
    Hu3DModelRotSet(object->model[1], -23.0f, 0.0f, 0.0f);
    object->model[3] = Hu3DModelRead(0x370003, 0x404AD);
    Hu3DModelTPLvlInit(object->model[3]);
    for (i = 1; i < 5; i++) {
        object->model[3 + i] = Hu3DModelLink(object->model[3]);
    }
    object->model[2] = Hu3DModelRead(0x370003, 0x404AD);
    Hu3DModelTPLvlInit(object->model[2]);
    for (i = 0; i < 3; i++) {
        HmfModel *modelP;

        object->model[26 + i] = Hu3DModelRead(0x1001F, 0x8BD);
        Hu3DModelScaleSet(object->model[26 + i], 2.5f, 2.5f, 2.5f);
        Hu3DModelObjAttrSet(object->model[26 + i], 0x70000000, 0x70000000);
        modelP = &Hu3DData[object->model[26 + i]];
        modelP->motSpeed = 1.55f;
    }
    for (i = 0; i < 14; i++) {
        s32 files[6] = { 4, 5, 6, 7, 8, 9 };
        f32 scale = 0.5f;

        if (i < 6) {
            object->model[29 + i] = Hu3DModelRead(files[(s16)(i % 6)] | 0x370000, 0x4BD);
        } else {
            object->model[29 + i] = Hu3DModelLink(object->model[29 + (s16)(i % 6)]);
        }
        Hu3DModelObjAttrSet(object->model[29 + i], 0x70000000, 0x70000000);
        if (i == 0) {
            object->model[43] = Hu3DModelRead(9, 0xBD);
        } else {
            object->model[43 + i] = Hu3DModelLink(object->model[43]);
        }
        Hu3DModelScaleSet(object->model[29 + i], scale, scale, scale);
        scale = 0.875f;
        Hu3DModelScaleSet(object->model[43 + i], scale, scale, scale);
    }
    for (i = 0; i < 9; i++) {
        if (i == 0) {
            object->model[8] = Hu3DModelRead(0x37000A, 0x8BD);
        } else {
            object->model[8 + i] = Hu3DModelLink(object->model[8]);
        }
        Hu3DModelPosSet(object->model[8 + i], m222_blockObjTbl[i]->trans.x, m222_blockObjTbl[i]->trans.y + 25.0f,
                        m222_blockObjTbl[i]->trans.z + 125.0f);
        Hu3DModelRotSet(object->model[8 + i], -23.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(object->model[8 + i], 2.5f, 2.5f, 2.5f);
        object->model[17 + i] = Hu3DModelRead(0x37000B, 0x8BD);
        Hu3DModelPosSet(object->model[17 + i], m222_blockObjTbl[i]->trans.x, m222_blockObjTbl[i]->trans.y - 100.0f,
                        m222_blockObjTbl[i]->trans.z);
        Hu3DModelRotSet(object->model[17 + i], -23.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(object->model[17 + i], 0.75f, 0.75f, 0.75f);
    }
    object->model[57] = Hu3DModelRead(0x37000A, 0x8BD);
    Hu3DModelScaleSet(object->model[57], 2.0f, 2.0f, 2.0f);
    object->func = m222_StageObjMain;
}

void m222_StageObjMain(omObjData *object) {
    MgPlayerWork *data;
    HuCamMtxs *camMtxs;
    f32 t;
    f32 x;
    f32 y;
    f32 z;
    f32 angle;
    s32 count;
    s32 tries;
    s32 i;
    s32 j;
    s32 k;

    i = 0;
    if (m222_phase == 4 && m222_phaseTimer >= 30 && m222_phaseTimer < 50) {
        Vec2f screenMin;
        Vec2f screenMax;
        Vec2f center;
        Vec pos;
        Vec pos2;
        Vec pos3;
        f32 width;
        f32 scale;
        f32 left;
        f32 top;
        f32 right;
        f32 bottom;
        f32 blend;
        f32 inv;
        omObjData *player = m222_playerObjTbl[m222_winGroup];

        pos2.x = player->trans.x;
        pos2.y = player->trans.y + 75.0f;
        pos2.z = player->trans.z;
        pos = pos2;
        pos3.x = player->trans.x + 25.0f;
        pos3.y = player->trans.y + 75.0f;
        pos3.z = player->trans.z;
        pos2 = pos3;
        ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
        Hu3DCam3Dto2D(0, &pos, &screenMin);
        Hu3DCam3Dto2D(0, &pos2, &screenMax);
        width = (screenMax.x - screenMin.x) * 12.0f;
        screenMax.x = width + screenMin.x;
        screenMin.x = screenMin.x - width;
        screenMin.y = screenMin.y - (screenMax.x - screenMin.x) * 0.75 * 0.5;
        screenMax.y = screenMax.y + (screenMax.x - screenMin.x) * 0.75 * 0.5;
        blend = 1.0f - (f32)(m222_phaseTimer - 30) / 20.0f;
        blend = 1.0f - blend * blend * blend * blend;
        inv = 1.0f - blend;
        screenMin.x = blend * screenMin.x + inv * 0.0f;
        screenMin.y = blend * screenMin.y + inv * 0.0f;
        screenMax.x = blend * screenMax.x + inv * 320.0f;
        screenMax.y = blend * screenMax.y + inv * 240.0f;
        scale = 320.0f / (screenMax.x - screenMin.x);
        if (screenMin.x < 0.0f) {
            screenMax.x -= screenMin.x;
            screenMin.x -= screenMin.x;
        }
        if (screenMin.y < 0.0f) {
            screenMax.y -= screenMin.y;
            screenMin.y -= screenMin.y;
        }
        if (screenMax.x > 320.0f) {
            f32 over = screenMax.x - 320.0f;

            screenMin.x -= over;
            screenMax.x -= over;
        }
        if (screenMax.y > 240.0f) {
            f32 over = screenMax.y - 240.0f;

            screenMin.y -= over;
            screenMax.y -= over;
        }
        center.x = (screenMin.x + screenMax.x) * 0.5;
        center.y = (screenMin.y + screenMax.y) * 0.5;
        m222_viewLeft = (s32)((0.0f - center.x) / (screenMin.x - center.x) * (0.0f - center.x) + center.x);
        m222_viewTop = (s32)((0.0f - center.y) / (screenMin.y - center.y) * (0.0f - center.y) + center.y);
        m222_viewRight = (s32)((320.0f - center.x) / (screenMax.x - center.x) * (320.0f - center.x) + center.x);
        m222_viewBottom = (s32)((240.0f - center.y) / (screenMax.y - center.y) * (240.0f - center.y) + center.y);
        left = 0.0f;
        if (screenMin.x != left) {
            left = left - (screenMin.x - left) * scale;
        }
        m222_viewLeft = left;
        top = 0.0f;
        if (screenMin.y != top) {
            top = top - (screenMin.y - top) * scale;
        }
        m222_viewTop = top;
        right = 320.0f;
        if (screenMax.x != right) {
            right = right - (screenMax.x - right) * scale;
        }
        m222_viewRight = right;
        bottom = 240.0f;
        if (screenMax.y != bottom) {
            bottom = bottom - (screenMax.y - bottom) * scale;
        }
        m222_viewBottom = bottom;
        ViewportSet(0, (s32)(scale * 640.0f), (s32)(scale * 480.0f), 511.0f,
                    (s32)((m222_viewLeft + m222_viewRight) / 2.0 * 4.0),
                    (s32)((m222_viewTop + m222_viewBottom) / 2.0 * 4.0), 511.0f);
    } else if (m222_shakeTimer != 0 && m222_shakeTimer < 13) {
        f32 shakeAngle;

        if (omPauseChk() + omAllPauseF == 0) {
            shakeAngle = m222_shakeAngle + rand8() / 255.0 * 30.0 - 15.0;
        } else {
            shakeAngle = m222_shakeAngle;
        }
        m222_viewLeft = (s16)(sindf(shakeAngle) * 0.5 *
                                           ((m222_shakeTimer % 2 == 0) ? m222_shakeTimer : -m222_shakeTimer));
        m222_viewRight = m222_viewLeft + 320.0f;
        m222_viewTop = (s16)(cosdf(shakeAngle) * 0.5 *
                                           ((m222_shakeTimer % 2 == 0) ? m222_shakeTimer : -m222_shakeTimer));
        m222_viewBottom = m222_viewTop + 240.0f;
        m222_shakeTimer -= (omPauseChk() + omAllPauseF == 0) ? 1 : 0;
        ViewportSet(0, 640.0f, 480.0f, 511.0f, (s32)((m222_viewLeft + m222_viewRight) / 2.0 * 4.0),
                    (s32)((m222_viewTop + m222_viewBottom) / 2.0 * 4.0), 511.0f);
    } else if (m222_shakeTimer == 13) {
        m222_shakeTimer -= (omPauseChk() + omAllPauseF == 0) ? 1 : 0;
    }
    m222_ViewFrameSet(m222_viewLeft, m222_viewTop, m222_viewRight,
                                  m222_viewBottom);
    if (omPauseChk() + omAllPauseF != 0) {
        return;
    }
    m222_kinokoTimer++;
    switch (m222_kinokoPhase) {
        case 0:
            if (m222_kinokoTimer >= 47) {
                m222_kinokoPhase = 7;
                m222_kinokoTimer = 0;
                for (j = 0; j < 4; j++) {
                    s16 chr = m222_groupPlayerTbl[j]->chr;

                    m222_playerObjTbl[j]->model[6] = Hu3DModelRead(5, 0x88D);
                    m222_playerObjTbl[j]->model[7] = Hu3DModelRead(8, 0x88D);
                    m222_playerObjTbl[j]->model[8] = Hu3DModelRead(7, 0x88D);
                    MgPlayerMotLoad(m222_playerObjTbl[j], 1, CharMotionDataNumGet(chr, 1), 1, 0);
                    MgPlayerMotLoad(m222_playerObjTbl[j], 18, CharMotionDataNumGet(chr, 15), 2, 0);
                    MgPlayerMotLoad(m222_playerObjTbl[j], 2, CharMotionDataNumGet(chr, 2), 1, 0);
                    MgPlayerMotLoad(m222_playerObjTbl[j], 17, CharMotionDataNumGet(chr, 14), 1, 15);
                    MgPlayerMotRead(m222_playerObjTbl[j], 30, CharMotionDataNumGet(chr, 32), 2, 0);
                    MgPlayerMotRead(m222_playerObjTbl[j], 31, CharMotionDataNumGet(chr, 33), 2, 0);
                    MgPlayerMotRead(m222_playerObjTbl[j], 32, CharMotionDataNumGet(chr, 34), 0, 0);
                    MgPlayerMotLoad(m222_playerObjTbl[j], 5, CharMotionDataNumGet(chr, 3), 0, 0);
                    MgPlayerMotLoad(m222_playerObjTbl[j], 8, CharMotionDataNumGet(chr, 6), 1, 27);
                    MgPlayerMotLoad(m222_playerObjTbl[j], 12, CharMotionDataNumGet(chr, 37), 1, 120);
                }
            }
            break;
        case 1:
        case 2:
            for (tries = 0, i = rand8() & 3; tries < 4; tries++) {
                i++;
                i %= 4;
                data = m222_playerObjTbl[i]->data;
                if (m222_kinokoPhase == 1 && m222_kinokoTimer < 4 && data->unk53[3] >= 1 && data->unk53[3] <= 9 &&
                    m222_blockStateTbl[data->unk53[3] - 1] == 2) {
                    s32 start;
                    s32 n;
                    s32 slot;

                    for (n = 0, start = (u8)(rand8() % 9); n < 9; n++) {
                        slot = (n + start) % 9;
                        if (m222_blockStateTbl[slot] == 1) {
                            m222_blockStateTbl[data->unk53[3] - 1] = 1;
                            m222_blockStateTbl[slot] = 2;
                            break;
                        }
                    }
                }
                if (data->unk53[3] >= 1 && data->unk53[3] <= 9 && m222_blockStateTbl[data->unk53[3] - 1] != 3) {
                    j = data->unk53[3] - 1;
                    if (m222_blockStateTbl[j] == 2) {
                        data->unk38 += 0.5;
                        Hu3DData[m222_playerObjTbl[i]->model[0]].unk0E = Hu3DData[m222_playerObjTbl[i]->model[0]].unk0C;
                        m222_kinokoBlockNo = j;
                        for (k = 0; k < 9; k++) {
                            m222_blockStateTbl[k] = m222_blockStateTbl[k] != 0;
                        }
                        m222_blockStateTbl[j] = 3;
                        m222_kinokoPhase = 2;
                        m222_kinokoTimer = 0;
                        m222_giantGroup = i;
                    } else if (m222_blockStateTbl[j] != 3) {
                        m222_blockStateTbl[j] = 0;
                        data->unkC5 = HuAudPlayerFXPlay(0x3A5, data->unk59);
                        data->unkC4 = -1;
                        for (k = 0; k < 4; k++) {
                            MgPlayerMapAttrSet(m222_playerObjTbl[k], j + 1, 1);
                        }
                        Hu3DModelAttrSet(m222_blockObjTbl[j]->model[0], 4, 4);
                        Hu3DModelAttrSet(m222_blockObjTbl[j]->model[1], 4, 4);
                        Hu3DModelAttrSet(m222_stageObj->model[17 + j], 4, 0);
                        m222_MotTimeSet(m222_stageObj->model[17 + j], 0);
                        m222_blockBreakTimerTbl[j] = 1;
                        count = 0;
                        for (k = 0; count < 4 && k < 14; k++) {
                            if (m222_debrisTimerTbl[k] != 0) {
                                continue;
                            }
                            m222_debrisTimerTbl[k] = 1;
                            m222_debrisXTbl[k] = (count & 1) ? 25.0f : -25.0f;
                            m222_debrisYTbl[k] = (count / 2) ? 25.0f : -25.0f;
                            m222_debrisZTbl[k] = rand8() / 255.0 * 50.0 - 25.0;
                            m222_debrisVelXTbl[k] = rand8() / 255.0 * 15.0;
                            m222_debrisVelYTbl[k] = 30.0 - rand8() / 255.0 * 10.0;
                            m222_debrisVelYTbl[k] = HuSqrtf(m222_debrisVelXTbl[k] * m222_debrisVelXTbl[k] +
                                                                    m222_debrisVelYTbl[k] * m222_debrisVelYTbl[k]);
                            m222_debrisVelZTbl[k] = rand8() / 255.0 * 20.0;
                            m222_debrisVelXTbl[k] =
                                (m222_debrisXTbl[k] < 0.0f) ? -m222_debrisVelXTbl[k] : m222_debrisVelXTbl[k];
                            m222_debrisVelZTbl[k] =
                                (m222_debrisZTbl[k] < 0.0f) ? -m222_debrisVelZTbl[k] : m222_debrisVelZTbl[k];
                            m222_debrisXTbl[k] += m222_blockObjTbl[j]->trans.x;
                            m222_debrisYTbl[k] += m222_blockObjTbl[j]->trans.y;
                            m222_debrisZTbl[k] += m222_blockObjTbl[j]->trans.z;
                            Hu3DModelAttrSet(object->model[29 + k], 4, 0);
                            Hu3DModelAttrSet(object->model[43 + k], 4, 0);
                            count++;
                        }
                    }
                }
            }
            if (m222_kinokoPhase == 1) {
                break;
            }
            if (m222_kinokoTimer >= 55) {
                m222_kinokoPhase = 3;
                m222_kinokoTimer = 0;
                Hu3DModelAttrSet(m222_stageObj->model[1], 4, 4);
                Hu3DModelAttrSet(m222_stageObj->model[56], 4, 4);
                msmMusSetVolume(HuAudMusNo, m222_musVol);
                break;
            }
            if (m222_kinokoTimer == 35) {
                f32 visible = 0.0f;

                for (j = 0; j < 9; j++) {
                    if (m222_blockStateTbl[j] != 0) {
                        visible += 1.0f;
                        Hu3DModelAttrSet(m222_stageObj->model[8 + j], 4, 0);
                        m222_MotTimeSet(m222_stageObj->model[8 + j], 0);
                    }
                }
                m222_puffTimer = 1;
                if (visible > 0.0f) {
                    HuAudFXPlay(0x3A9);
                }
            } else if (m222_kinokoTimer == 42) {
                for (j = 0; j < 9; j++) {
                    m222_blockStateTbl[j] = 0;
                    for (k = 0; k < 4; k++) {
                        MgPlayerMapAttrSet(m222_playerObjTbl[k], j + 1, 1);
                    }
                }
            } else if (m222_kinokoTimer == 45) {
                for (j = 0; j < 9; j++) {
                    Hu3DModelAttrSet(m222_blockObjTbl[j]->model[0], 4, 4);
                    Hu3DModelAttrSet(m222_blockObjTbl[j]->model[1], 4, 4);
                }
            }
            if (m222_kinokoTimer < 7) {
                f32 bounce = (m222_kinokoTimer + 1) / 7.0;

                bounce = 2.0f * bounce - 1.0f;
                bounce = -(bounce * bounce - 1.0f);
                m222_blockObjTbl[m222_kinokoBlockNo]->trans.y = bounce * 25.0f + 375.0f;
                Hu3DData[m222_blockObjTbl[m222_kinokoBlockNo]->model[0]].pos.y = bounce * 25.0f + 375.0f;
            } else if (m222_kinokoTimer >= 12 && m222_kinokoTimer < 45) {
                if (m222_kinokoTimer < 35) {
                    t = (m222_kinokoTimer - 12) / 23.0;
                } else {
                    t = 1.0f;
                }
                Hu3DModelAttrSet(object->model[1], 4, 0);
                Hu3DModelPosSet(object->model[1], m222_blockObjTbl[m222_kinokoBlockNo]->trans.x,
                                t * 75.0f + m222_blockObjTbl[m222_kinokoBlockNo]->trans.y + 12.5,
                                m222_blockObjTbl[m222_kinokoBlockNo]->trans.z - 25.0f);
                if (m222_kinokoTimer == 12) {
                    MgPlayerWork *playerData;
                    s32 n;

                    HuAudFXPlay(0x3A8);
                    for (n = 0; n < 4; n++) {
                        playerData = m222_playerObjTbl[i]->data;
                        playerData->unkC4 = -1;
                        playerData->unkC5 = -1;
                    }
                }
            } else if (m222_kinokoTimer >= 45) {
                f32 dx;
                f32 dy;
                f32 dz;
                f32 dist;
                f32 bestDist;

                bestDist = 32767.0f;
                k = -1;
                if (m222_kinokoTimer == 45) {
                    s32 dir = rand8() / 256.0 * 360.0;

                    m222_kinokoX = Hu3DData[object->model[1]].pos.x;
                    m222_kinokoY = Hu3DData[object->model[1]].pos.y;
                    m222_kinokoZ = Hu3DData[object->model[1]].pos.z;
                    m222_kinokoVelX = cosdf(dir) * 7.0f;
                    m222_kinokoVelZ = -sindf(dir) * 7.0f;
                    m222_kinokoVelY = 0.0f;
                }
                m222_kinokoX += m222_kinokoVelX;
                m222_kinokoY += m222_kinokoVelY;
                m222_kinokoZ += m222_kinokoVelZ;
                m222_kinokoVelY -= 3.0f;
                if (m222_kinokoY < 50.0f) {
                    m222_kinokoY = 50.0f;
                    m222_kinokoVelY = 0.0f;
                }
                if (m222_kinokoX < -450.0f) {
                    m222_kinokoX = -m222_kinokoX - 900.0f;
                    m222_kinokoVelX = -m222_kinokoVelX;
                }
                if (m222_kinokoX > 450.0f) {
                    m222_kinokoX = -m222_kinokoX + 900.0f;
                    m222_kinokoVelX = -m222_kinokoVelX;
                }
                if (m222_kinokoZ < -400.0f) {
                    m222_kinokoZ = -m222_kinokoZ - 800.0f;
                    m222_kinokoVelZ = -m222_kinokoVelZ;
                }
                if (m222_kinokoZ > 400.0f) {
                    m222_kinokoZ = -m222_kinokoZ + 800.0f;
                    m222_kinokoVelZ = -m222_kinokoVelZ;
                }
                Hu3DModelPosSet(object->model[1], m222_kinokoX, m222_kinokoY, m222_kinokoZ);
                Hu3DModelPosSet(object->model[56], m222_kinokoX, 0.0f, m222_kinokoZ);
                Hu3DModelAttrSet(object->model[56], 4, 0);
                for (j = 0; j < 4; j++) {
                    dx = m222_playerObjTbl[j]->trans.x - m222_kinokoX;
                    dy = (m222_playerObjTbl[j]->trans.y + 75.0f - m222_kinokoY) / 1.75;
                    dz = m222_playerObjTbl[j]->trans.z - m222_kinokoZ;
                    dist = HuSqrtf(dx * dx + dy * dy + dz * dz);
                    if (dist <= 100.0f && dist < bestDist) {
                        k = j;
                        bestDist = dist;
                    }
                }
                if (k != -1) {
                    m222_giantGroup = k;
                    m222_kinokoTimer = 54;
                } else {
                    m222_kinokoTimer = 46;
                }
                if (m222_phase == 5 || m222_phase == 6) {
                    m222_kinokoPhase = 9;
                    m222_kinokoTimer = 0;
                    Hu3DModelAttrSet(object->model[1], 4, 4);
                    Hu3DModelAttrSet(object->model[56], 4, 4);
                    Hu3DModelAttrSet(object->model[57], 4, 0);
                    Hu3DModelPosSet(object->model[57], m222_kinokoX, m222_kinokoY, m222_kinokoZ);
                    m222_MotTimeSet(object->model[57], 6);
                }
            }
            break;
        case 3:
            if ((m222_phase == 5 || m222_phase == 6) && m222_kinokoTimer >= 2 &&
                m222_growEffDoneF == 0) {
                m222_kinokoPhase = 9;
                m222_kinokoTimer = 0;
                MgPlayerMotSet(m222_playerObjTbl[m222_giantGroup], 0);
                m222_growEffDoneF = 1;
            }
            if (m222_kinokoTimer == 1) {
                m222_growEffTimer = 1;
                if (m222_exitF == 0 && omSysExitReq == 0) {
                    HuAudSeqVolFadeOut(90);
                    m222_musicFTbl[0] = 0;
                }
                HuAudFXPlay(0x3AB);
                omSetSca(m222_playerObjTbl[m222_giantGroup], 1.0f, 1.0f, 1.0f);
                if (!(m222_phase == 5 || m222_phase == 6)) {
                    MgPlayerMotSet(m222_playerObjTbl[m222_giantGroup], 12);
                }
                Hu3DModelLayerSet(m222_playerObjTbl[m222_giantGroup]->model[0], 0x800);
                for (j = 0; j < 5; j++) {
                    Hu3DModelLayerSet(m222_stageObj->model[3 + j], 0x800);
                }
            } else if (m222_kinokoTimer == 46) {
                MgPlayerMotSet(m222_playerObjTbl[m222_giantGroup], 0);
            } else if (m222_kinokoTimer >= 55) {
                m222_kinokoPhase = 4;
                m222_kinokoTimer = 0;
                for (j = 0; j < 5; j++) {
                    Hu3DModelLayerSet(m222_stageObj->model[3 + j], 0x400);
                }
            }
            break;
        case 4:
            if (m222_kinokoTimer == 3) {
                MgPlayerWork *work = m222_playerObjTbl[m222_giantGroup]->data;

                work->unkC5 = HuAudPlayerFXPlay(0x3A7, work->unk59);
                work->unkC4 = -1;
                omVibrate(m222_groupPlayerTbl[m222_giantGroup]->playerNo, 10, 0, 10);
            }
            Hu3DModelScaleSet(m222_playerObjTbl[m222_giantGroup]->model[1],
                              m222_playerObjTbl[m222_giantGroup]->scale.x,
                              m222_playerObjTbl[m222_giantGroup]->scale.y,
                              m222_playerObjTbl[m222_giantGroup]->scale.z);
            if (m222_kinokoTimer < 24) {
                u8 pulse[8] = { 0, 0, 1, 0, 1, 1, 0, 1 };
                f32 scale;

                scale = pulse[m222_kinokoTimer & 7];
                scale = (m222_kinokoTimer < 12) ? scale * 0.5 + 1.0 : 2.0 - scale * 0.5;
                omSetSca(m222_playerObjTbl[m222_giantGroup], scale, scale, scale);
            } else {
                omSetSca(m222_playerObjTbl[m222_giantGroup], 2.0f, 2.0f, 2.0f);
            }
            if (m222_kinokoTimer >= 35) {
                MgPlayerWork *work = m222_playerObjTbl[m222_giantGroup]->data;

                if (m222_phase == 2) {
                    work->unk50 |= 0x400;
                }
                m222_kinokoPhase = 5;
                m222_kinokoTimer = (m222_phase != 2) ? 150 : 0;
                Hu3DModelLayerSet(m222_playerObjTbl[m222_giantGroup]->model[0], 0x400);
                if (m222_phase == 2 && m222_exitF == 0 && omSysExitReq == 0) {
                    msmMusPause(HuAudMusNo);
                    HuAudSubSeqPlay(0x45);
                    m222_musicFTbl[1] = 1;
                }
            }
            break;
        case 5:
            omSetSca(m222_playerObjTbl[m222_giantGroup], 2.0f, 2.0f, 2.0f);
            if (m222_kinokoTimer >= 150) {
                MgPlayerWork *work = m222_playerObjTbl[m222_giantGroup]->data;

                work->unk50 &= ~0x400;
                m222_kinokoPhase = 6;
                m222_kinokoTimer = 0;
                if (m222_phase == 2 && m222_exitF == 0 && omSysExitReq == 0) {
                    HuAudSubSeqVolFadeOut(40);
                    m222_musicFTbl[1] = 0;
                }
            } else {
                for (i = 0; i < 4; i++) {
                    if (m222_outTimerTbl[i] == 0 && m222_giantGroup != i && m222_phase == 2) {
                        f32 dx;
                        f32 dy;
                        f32 dz;

                        dx = m222_playerObjTbl[i]->trans.x - m222_playerObjTbl[m222_giantGroup]->trans.x;
                        dx *= dx;
                        dy = m222_playerObjTbl[i]->trans.y - m222_playerObjTbl[m222_giantGroup]->trans.y;
                        dy *= 0.5;
                        dy *= dy;
                        dz = m222_playerObjTbl[i]->trans.z - m222_playerObjTbl[m222_giantGroup]->trans.z;
                        dz *= dz;
                        if (dx + dy + dz < 22500.0f && m222_playerObjTbl[i]->trans.y < 270.0f) {
                            MgPlayerWork *work = m222_playerObjTbl[i]->data;

                            work->unk50 |= 0x400;
                            work->unkC5 = HuAudPlayerFXPlay(0x3A6, work->unk59);
                            work->unkC4 = -1;
                            omVibrate(m222_groupPlayerTbl[i]->playerNo, 20, 0, 20);
                            m222_outTimerTbl[i] = 1;
                            m222_outDirTbl[i] =
                                (m222_playerObjTbl[i]->trans.x < m222_playerObjTbl[m222_giantGroup]->trans.x) ? 0 : 1;
                            m222_humanNum -= (m222_groupPlayerTbl[i]->cpuDifficulty == -1) ? 1 : 0;
                            for (j = 0, k = 0; j < 4; j++) {
                                k += m222_outTimerTbl[j] != 0;
                            }
                            if (k == 3) {
                                m222_winGroup = m222_giantGroup;
                                m222_kinokoTimer = 120;
                            }
                        }
                    }
                }
            }
            break;
        case 6:
            if (m222_kinokoTimer < 24) {
                u8 pulse[8] = { 0, 1, 0, 1, 0, 1, 0, 1 };
                f32 scale;

                scale = pulse[m222_kinokoTimer & 7];
                scale = (m222_kinokoTimer < 6) ? scale * 0.5 + 1.5 : 1.5 - scale * 0.5;
                omSetSca(m222_playerObjTbl[m222_giantGroup], scale, scale, scale);
                if (m222_kinokoTimer == 1) {
                    MgPlayerWork *work = m222_playerObjTbl[m222_giantGroup]->data;

                    work->unkC5 = HuAudPlayerFXPlay(0x3A4, work->unk59);
                    work->unkC4 = -1;
                }
            } else {
                omSetSca(m222_playerObjTbl[m222_giantGroup], 1.0f, 1.0f, 1.0f);
            }
            Hu3DModelScaleSet(m222_playerObjTbl[m222_giantGroup]->model[1],
                              m222_playerObjTbl[m222_giantGroup]->scale.x,
                              m222_playerObjTbl[m222_giantGroup]->scale.y,
                              m222_playerObjTbl[m222_giantGroup]->scale.z);
            if (m222_kinokoTimer == 13) {
                if (m222_phase == 2) {
                    m222_kinokoPhase = 7;
                    m222_kinokoTimer = 0;
                } else {
                    m222_kinokoPhase = 9;
                    m222_kinokoTimer = 0;
                    MgPlayerMotLoad(m222_playerObjTbl[m222_giantGroup], 13,
                                           CharMotionDataNumGet(m222_groupPlayerTbl[m222_giantGroup]->chr,
                                                              m222_groupPlayerTbl[i]->unk_0C),
                                           1, 120);
                }
            }
            break;
        case 7:
            if (m222_kinokoTimer == 1) {
                for (j = 0; j < 9; j++) {
                    Hu3DModelAttrSet(m222_stageObj->model[8 + j], 4, 0);
                    m222_MotTimeSet(m222_stageObj->model[8 + j], 0);
                }
                m222_puffTimer = 1;
                HuAudFXPlay(0x3A9);
                if (m222_phase == 2 && m222_exitF == 0 && omSysExitReq == 0 &&
                    m222_musicFTbl[0] == 0) {
                    msmMusStop(HuAudSubMusNo);
                    msmMusResume(HuAudMusNo, 0);
                    HuAudSeqVolFadeIn(35);
                    m222_musicFTbl[0] = 1;
                }
            }
            if (m222_kinokoTimer == 10) {
                m222_kinokoPhase = 1;
                m222_kinokoTimer = 0;
                for (j = 0; j < 9; j++) {
                    m222_blockStateTbl[j] = 1;
                    Hu3DModelAttrSet(m222_blockObjTbl[j]->model[0], 4, 0);
                    Hu3DModelAttrSet(m222_blockObjTbl[j]->model[1], 4, 0);
                    for (k = 0; k < 4; k++) {
                        MgPlayerMapAttrSet(m222_playerObjTbl[k], j + 1, 2);
                    }
                }
                j = (u8)(rand8() % 9);
                k = (u8)(rand8() % 9);
                while (j == k) {
                    k = (u8)(rand8() % 9);
                }
                m222_blockStateTbl[k] = 2;
                m222_blockStateTbl[j] = 2;
            }
            break;
        case 9:
            if (m222_phase >= 3 && m222_winGroup < 4 && m222_kinokoTimer >= 7) {
                MgPlayerWork *winnerData = m222_playerObjTbl[m222_winGroup]->data;

                winnerData->unk3C = (winnerData->unk3C < -10.0f)  ? (winnerData->unk3C + 9.0f) - winnerData->unk3C * 0.1
                                    : (winnerData->unk3C > 10.0f) ? (winnerData->unk3C - 9.0f) - winnerData->unk3C * 0.1
                                                                  : 0.0f;
            }
            break;
    }
    for (i = 0; i < 4; i++) {
        data = m222_playerObjTbl[i]->data;
        data->unk53[3] = 0;
        if (m222_outTimerTbl[i] != 0 && m222_outTimerTbl[i] < 60) {
            MgPlayerMotSet(m222_playerObjTbl[i], 18);
            Hu3DData[m222_playerObjTbl[i]->model[0]].motTime = 0.0f;
            Hu3DData[m222_playerObjTbl[i]->model[0]].motSpeed = 0.0f;
            MgPlayerMotUpdate(m222_playerObjTbl[i]);
            Hu3DData[m222_playerObjTbl[i]->model[0]].unk0E = Hu3DData[m222_playerObjTbl[i]->model[0]].unk0C;
            MgPlayerScaleUpdate(m222_playerObjTbl[i]);
            m222_playerObjTbl[i]->trans.x += sindf(m222_playerObjTbl[i]->rot.z) * -50.0f;
            m222_playerObjTbl[i]->trans.y += cosdf(m222_playerObjTbl[i]->rot.z) * 50.0f;
            m222_playerObjTbl[i]->rot.y += 33.0f;
            m222_playerObjTbl[i]->rot.z += 33.0f;
            m222_playerObjTbl[i]->rot.x = 0.0f;
            m222_playerObjTbl[i]->trans.x += (m222_outDirTbl[i] != 0) ? 30.0f : -30.0f;
            m222_playerObjTbl[i]->trans.y +=
                (m222_outTimerTbl[i] < 14) ? (1.0 - m222_outTimerTbl[i] / 13.0) * 65.0 + 15.0 : 15.0;
            m222_playerObjTbl[i]->trans.x -= sindf(m222_playerObjTbl[i]->rot.z) * -50.0f;
            m222_playerObjTbl[i]->trans.y -= cosdf(m222_playerObjTbl[i]->rot.z) * 50.0f;
            m222_outTimerTbl[i]++;
            if (m222_outTimerTbl[i] == 15) {
                data->unkC5 = PlayerFXPlay(0x286, data->unk59);
                data->unkC4 = -1;
            }
        }
    }
    for (j = 0; j < 9; j++) {
        if (m222_blockBreakTimerTbl[j] != 0) {
            if (m222_blockBreakTimerTbl[j] > 60) {
                m222_blockBreakTimerTbl[j] = 0;
                Hu3DModelAttrSet(object->model[17 + j], 4, 4);
            } else {
                m222_blockBreakTimerTbl[j]++;
            }
        }
    }
    if (m222_puffTimer != 0) {
        if (m222_puffTimer > 18) {
            m222_puffTimer = 0;
            for (j = 0; j < 9; j++) {
                Hu3DModelAttrSet(object->model[8 + j], 4, 4);
            }
        } else {
            m222_puffTimer++;
        }
    }
    for (j = 0; j < 14; j++) {
        if (m222_debrisTimerTbl[j] != 0) {
            if (m222_debrisTimerTbl[j] > 12) {
                m222_debrisTimerTbl[j] = 0;
                Hu3DModelAttrSet(object->model[29 + j], 4, 4);
                Hu3DModelAttrSet(object->model[43 + j], 4, 4);
            } else {
                m222_debrisTimerTbl[j]++;
                m222_debrisVelYTbl[j] -= 5.0f;
                m222_debrisXTbl[j] += m222_debrisVelXTbl[j];
                m222_debrisYTbl[j] += m222_debrisVelYTbl[j];
                m222_debrisZTbl[j] += m222_debrisVelZTbl[j];
                if (m222_debrisYTbl[j] < 0.0f) {
                    m222_debrisYTbl[j] = 0.0f;
                    m222_debrisVelYTbl[j] = -m222_debrisVelYTbl[j] * 0.3;
                }
                Hu3DModelPosSet(object->model[29 + j], m222_debrisXTbl[j], m222_debrisYTbl[j], m222_debrisZTbl[j]);
                Hu3DModelPosSet(object->model[43 + j], m222_debrisXTbl[j], 0.0f, m222_debrisZTbl[j]);
            }
        }
    }
    if (m222_growEffTimer != 0 && m222_growEffDoneF == 0) {
        HuMtx4F mtx;
        HuCamera *camera;
        f32 ease;

        camera = gCameraList;
        camMtxs = &camera->mtxs[Hu3DCamMtxNo];
        m222_growEffHeight = m222_growEffScale = 0.0f;
        if (m222_growEffTimer == 1) {
            Hu3DModelTPLvlSet(object->model[3], 0xFF);
            for (j = 0; j < 5; j++) {
                Hu3DModelAttrSet(m222_stageObj->model[3 + j], 4, 0);
            }
        } else if (m222_growEffTimer == 55) {
            for (j = 0; j < 5; j++) {
                Hu3DModelAttrSet(m222_stageObj->model[3 + j], 4, 4);
            }
        }
        if (m222_growEffTimer >= 1 && m222_growEffTimer < 55) {
            if (m222_growEffTimer < 15) {
                ease = 1.0 - m222_growEffTimer / 15.0;
                ease = 1.0f - ease * ease * ease;
                m222_growEffHeight = ease * 100.0f;
            } else {
                m222_growEffHeight = 90.0f;
            }
            if (m222_growEffTimer < 45) {
                m222_growEffHeight += m222_growEffTimer / 45.0 * 125.0;
            }
            if (m222_growEffTimer >= 45 && m222_growEffTimer <= 55) {
                ease = 1.0 - (m222_growEffTimer - 45) / 10.0;
                ease = 1.0 - (ease * ease * 0.75 + ease * 0.25);
                m222_growEffHeight = 215.0f - ease * 180.0f;
            }
            if (m222_growEffTimer < 55) {
                ease = m222_growEffTimer / 45.0;
                m222_growEffRot += ease * 7.0f + 8.0f;
            }
            if (m222_growEffTimer >= 45 && m222_growEffTimer < 55) {
                ease = 1.0 - (m222_growEffTimer - 45) / 10.0;
                ease = 1.0 - (ease * ease * 0.75 + ease * 0.25);
                m222_growEffRot += ease * 12.0f;
            }
        }
        if (m222_growEffTimer == 55) {
            for (j = 0; j < 5; j++) {
                Hu3DModelAttrSet(m222_stageObj->model[2], 4, 0);
            }
        } else if (m222_growEffTimer == 85) {
            for (j = 0; j < 5; j++) {
                Hu3DModelAttrSet(m222_stageObj->model[2], 4, 4);
            }
        }
        if (m222_growEffTimer >= 55 && m222_growEffTimer < 85) {
            ease = 1.0 - (m222_growEffTimer - 55) / 30.0;
            ease = ease * ease * 0.75 + ease * 0.25;
            m222_growEffScale = 2.0 * (1.0f - ease) + 1.0;
            if (m222_growEffTimer >= 75) {
                m222_growEffRot += 5.0f;
            } else {
                m222_growEffRot += (1.0 - (m222_growEffTimer - 55) / 30.0) * 15.0;
            }
            m222_growEffAlpha = 1.0 - (m222_growEffTimer - 55) / 30.0;
        }
        if (m222_growEffHeight > 0.0f) {
            for (j = 0; j < 5; j++) {
                f32 weight;
                f32 speed;
                f32 halfSpeed;
                f32 invWeight;

                if (m222_growEffTimer >= 45) {
                    weight = (m222_growEffTimer - 45) / 10.0;
                } else {
                    weight = 0.0f;
                }
                invWeight = 1.0f - weight;
                x = weight * m222_playerObjTbl[m222_giantGroup]->trans.x + invWeight * Hu3DData[object->model[1]].pos.x;
                y = (m222_playerObjTbl[m222_giantGroup]->trans.y + 175.0f) * weight +
                    invWeight * Hu3DData[object->model[1]].pos.y;
                z = (m222_playerObjTbl[m222_giantGroup]->trans.z + 85.0f) * weight +
                    invWeight * Hu3DData[object->model[1]].pos.z;
                guMtxL2F(mtx, &camMtxs->lookAtMtx);
                angle = j * 72;
                mtxTransCat(mtx, cosdf(angle + m222_growEffRot) * m222_growEffHeight + x,
                            sindf(angle + m222_growEffRot) * m222_growEffHeight + y, z);
                mtx[0][0] = 0.45f;
                mtx[0][1] = 0.0f;
                mtx[0][2] = 0.0f;
                mtx[1][0] = 0.0f;
                mtx[1][1] = 0.45f;
                mtx[1][2] = 0.0f;
                mtx[2][0] = 0.0f;
                mtx[2][1] = 0.0f;
                mtx[2][2] = 0.45f;
                mtxCopy(Hu3DData[m222_stageObj->model[3 + j]].mtx, mtx);
            }
        }
        if (m222_growEffScale > 0.0f) {
            x = m222_playerObjTbl[m222_giantGroup]->trans.x;
            y = m222_playerObjTbl[m222_giantGroup]->trans.y + 175.0f;
            z = m222_playerObjTbl[m222_giantGroup]->trans.z + 85.0f;
            guMtxL2F(mtx, &camMtxs->lookAtMtx);
            mtxTransCat(mtx, x, y, z);
            mtx[0][0] = -sindf(m222_growEffRot) * m222_growEffScale;
            mtx[0][1] = cosdf(m222_growEffRot) * m222_growEffScale;
            mtx[0][2] = 0.0f;
            mtx[1][0] = cosdf(m222_growEffRot) * m222_growEffScale;
            mtx[1][1] = sindf(m222_growEffRot) * m222_growEffScale;
            mtx[1][2] = 0.0f;
            mtx[2][0] = 0.0f;
            mtx[2][1] = 0.0f;
            mtx[2][2] = m222_growEffScale;
            mtxCopy(Hu3DData[m222_stageObj->model[2]].mtx, mtx);
            Hu3DModelTPLvlSet(object->model[2], m222_growEffAlpha * 255.0f);
        }
        if (++m222_growEffTimer == 90) {
            m222_growEffTimer = 0;
        }
    } else if (m222_growEffDoneF != 0) {
        f32 fade;

        fade = 1.0 - m222_growEffDoneF / 20.0;
        Hu3DModelTPLvlSet(object->model[3], (s32)(fade * fade * 255.0f));
        if (++m222_growEffDoneF == 20) {
            m222_growEffDoneF = 0;
            m222_growEffTimer = 0;
            for (j = 0; j < 5; j++) {
                Hu3DModelAttrSet(m222_stageObj->model[3 + j], 4, 4);
            }
        }
    }
    if (m222_kinokoPhase == 5) {
        m222_cloudTimer = (s16)(m222_cloudTimer + 1) % 51;
        if (m222_cloudTimer % 17 == 0) {
            s32 cloud = m222_cloudTimer / 17;

            m222_cloudTimerTbl[cloud] = 0;
            m222_MotTimeSet(object->model[26 + cloud], 0);
            Hu3DModelAttrSet(object->model[26 + cloud], 4, 0);
            Hu3DModelPosSet(object->model[26 + cloud], m222_playerObjTbl[m222_giantGroup]->trans.x * 0.9, 300.0f,
                            m222_playerObjTbl[m222_giantGroup]->trans.z - 15.0f);
        }
    } else {
        m222_cloudTimer = 0;
    }
    for (j = 0; j < 3; j++) {
        m222_cloudTimerTbl[j] += (m222_cloudTimerTbl[j] >= 55) ? 0 : 1;
        if (m222_cloudTimerTbl[j] >= 55) {
            m222_cloudTimerTbl[j] = 55;
            Hu3DModelAttrSet(object->model[26 + j], 4, 4);
        }
    }
}

void m222_ViewFrameSet(s16 left, s16 top, s16 right, s16 bottom) {
    HuSprAnimPat *frame;
    HuSprite *sprite;
    f32 scaleX;
    f32 scaleY;
    f32 offsetX;
    f32 offsetY;
    f32 s0;
    f32 t0;
    f32 s1;
    f32 t1;
    s32 dsdx;
    s32 dtdy;
    s32 xl;
    s32 yl;
    s32 xh;
    s32 yh;
    s32 i;
    s32 j;

    scaleX = (right - left) / 320.0;
    offsetX = left;
    dsdx = (1.0 / scaleX) * 1024.0;
    scaleY = (bottom - top) / 240.0;
    offsetY = top;
    dtdy = (1.0 / scaleY) * 1024.0;

    gSPDisplayList(gMainGfxPos++, m222_gfxViewFrameInit);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    sprite = HuSprGet(esprite[m222_frameSprTbl[0]].unk04, 0);
    frame = &sprite->data->pat[sprite->patNo];
    gDPLoadTLUT_pal256(gMainGfxPos++, sprite->data->pal);
    for (i = 0; i < 6; i++) {
        t0 = i * 40;
        t1 = t0 + 40.0f + ((i == 5) ? -0.75 : 1.0);
        for (j = 0; j < 8; j++) {
            s0 = j * 40;
            s1 = s0 + 40.0f + ((j < 7) ? 1.0f : 0.0f);
            xl = (scaleX * s0 + offsetX) * 4.0f;
            yl = (scaleY * t0 + offsetY) * 4.0f;
            xh = (scaleX * s1 + offsetX) * 4.0f;
            yh = (scaleY * t1 + offsetY) * 4.0f;
            if (xl > 1280 || yl > 960) {
                continue;
            }
            if (xh < 0 || yh < 0) {
                continue;
            }
            gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 240, (s32)s0, (s32)t0, (s32)s1,
                               (s32)t1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
            gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, s0 * 32.0f, t0 * 32.0f, dsdx, dtdy);
        }
    }
}

void m222_MotTimeSet(s16 model, s16 time) {
    Hu3DMotionTimeSet(model, time);
}

void m222_CameraObjMain(omObjData *object) {
    Vec up;

    if (m222_cameraInitF == 0) {
        m222_cameraInitF = 1;
        m222_cameraPos.x = 0.0f;
        m222_cameraPos.y = 868.0f;
        m222_cameraPos.z = 1561.0f;
        m222_cameraTarget.x = 0.0f;
        m222_cameraTarget.y = -100.0f;
        m222_cameraTarget.z = -485.0f;
        m222_cameraFov = 32.5f;
    }
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    CFanParam[0] = m222_cameraPos.x;
    CFanParam[1] = m222_cameraPos.z;
    CFanParam[-1] = 0.0f;
    CFanParam[2] = gCameraList->fov;
    CFanParam[3] = CFanLen;
    CFanParam[4] = CFanOfs;
    Hu3DCameraPerspectiveSet(0, m222_cameraFov, 800.0f, 2750.0f);
    Hu3DCameraPosSetV(0, &m222_cameraPos, &m222_cameraTarget, &up);
    Hu3DCamUpdateMtx(0);
}

void m222_PlayerInit(omObjData *object, s32 model, s32 motion, u16 group, f32 x, f32 y, f32 z) {
    s32 dirs[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
    s32 slots[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    s32 files[2][8] = { { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B }, { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C } };
    MgPlayerWork *data;
    s32 modelFlags;
    s32 motionFlags;
    u16 chr;

    modelFlags = 0x4A9;
    motionFlags = 0x99;
    chr = m222_groupPlayerTbl[group]->chr;
    MgPlayerParamReset();
    MgPlayerCreate(object, model, motion, m222_groupPlayerTbl[group]->playerNo, modelFlags, motionFlags);
    omSetTra(object, x, y, z);
    Hu3DModelPosSet(object->model[1], x, 0.0f, z);
    data = object->data;
    data->unk59 = m222_groupPlayerTbl[group]->playerNo;
    m222_groupPlayerTbl[group]->unk_0C = (rand8() & 1) ? 0x2F : 0x30;
    m222_groupPlayerTbl[group]->unk_0C |= dirs[chr] << 16;
    m222_groupPlayerTbl[group]->unk_06 = CharAnimCreate(object->model[0], 1, slots[chr], (dirs[chr] << 16) | files[0][chr]);
    m222_groupPlayerTbl[group]->unk_08 = Hu3DAnimDataRead((dirs[chr] << 16) | files[1][chr]);
    Hu3DModelAnimStop(Hu3DData[object->model[0]].hmf);
    Hu3DModelDynamicFree(object->model[0]);
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(chr, 0), 1, 0);
    MgPlayerMotLoad(object, 6, CharMotionDataNumGet(chr, 4), 1, 19);
    MgPlayerMotRead(object, 21, CharMotionDataNumGet(chr, 31), 0, 0);
    MgPlayerMapAttrSet(object, 0, 2);
}

void m222_Player0ObjInit(omObjData *object) {
    s32 motion;
    s32 model;

    motion = omCharModelNoTbl[m222_groupPlayerTbl[0]->chr][3];
    model = omCharModelNoTbl[m222_groupPlayerTbl[0]->chr][0];
    m222_PlayerInit(object, model, motion, 0, (m222_startCornerTbl[0] >> 1) ? -400.0f : 400.0f, 800.0f,
                                  (m222_startCornerTbl[0] & 1) ? -350.0f : 350.0f);
    object->func = m222_PlayerObjMain;
}

void m222_Player1ObjInit(omObjData *object) {
    s32 motion;
    s32 model;

    motion = omCharModelNoTbl[m222_groupPlayerTbl[1]->chr][3];
    model = omCharModelNoTbl[m222_groupPlayerTbl[1]->chr][0];
    m222_PlayerInit(object, model, motion, 1, (m222_startCornerTbl[1] >> 1) ? -400.0f : 400.0f, 800.0f,
                                  (m222_startCornerTbl[1] & 1) ? -350.0f : 350.0f);
    object->func = m222_PlayerObjMain;
}

void m222_Player2ObjInit(omObjData *object) {
    s32 motion;
    s32 model;

    motion = omCharModelNoTbl[m222_groupPlayerTbl[2]->chr][3];
    model = omCharModelNoTbl[m222_groupPlayerTbl[2]->chr][0];
    m222_PlayerInit(object, model, motion, 2, (m222_startCornerTbl[2] >> 1) ? -400.0f : 400.0f, 800.0f,
                                  (m222_startCornerTbl[2] & 1) ? -350.0f : 350.0f);
    object->func = m222_PlayerObjMain;
}

void m222_Player3ObjInit(omObjData *object) {
    s32 motion;
    s32 model;

    motion = omCharModelNoTbl[m222_groupPlayerTbl[3]->chr][3];
    model = omCharModelNoTbl[m222_groupPlayerTbl[3]->chr][0];
    m222_PlayerInit(object, model, motion, 3, (m222_startCornerTbl[3] >> 1) ? -400.0f : 400.0f, 800.0f,
                                  (m222_startCornerTbl[3] & 1) ? -350.0f : 350.0f);
    object->func = m222_PlayerObjMain;
}

// Only differs in the two HuPadStkY stick computations (cases 2/3 and
// 11/12): the target converts the int result of (dist > 33.0f) to double rather
// than loading 1.0. Writing them with the GNU omitted-middle-operand form
// `((dist > 33.0f) ?: dist / 33.0)` gives a full match; standard C forms tried
// (`c ? c : ...`, `(double)` cast, inverted condition, MIN) do not.
#ifdef NON_MATCHING
void m222_PlayerObjMain(omObjData *object) {
    u8 flags[4];
    MgPlayerWork *data;
    u16 savedBtn;
    u16 savedBtn2;
    u16 savedBtn3;
    s8 savedStickX;
    s8 savedStickY;
    s16 savedStick2;
    s16 savedStick3;
    MgPlayerWork *otherData;
    MgPlayerWork *work;
    ToadstoolTitanPlayer *player;
    s16 group;
    s32 i;
    s32 best;
    f32 bestDist;
    f32 dz;
    f32 dx;
    f32 dist;
    f32 dirX;
    f32 dirZ;
    f32 cornerX;
    f32 cornerZ;
    f32 bestScore;
    f32 weight;
    f32 speed;
    f32 halfSpeed;
    f32 sinVal;
    f32 cosVal;
    f32 normX;
    f32 normZ;
    f32 signSin;
    f32 signCos;
    f32 hitX;
    f32 hitZ;
    f32 posX;
    f32 posZ;
    f32 otherX;
    f32 otherZ;
    f32 velX;
    f32 velZ;
    f32 otherVelX;
    f32 otherVelZ;
    s32 range;
    s32 rnd;
    s32 minTime;
    s32 newTime;
    s16 *timer;

    data = object->data;
    group = m222_playerGroupTbl[data->unk59];
    player = m222_groupPlayerTbl[group];
    // Computed but never read in the original.
    if (group == 0) {
        for (i = 0; i < 4; i++) {
            flags[i] = (m222_playerObjTbl[i]->trans.y <= 0.0f) ? 1 : ((m222_outTimerTbl[i] != 0) ? 2 : 0);
        }
    }
    (void)flags;
    savedBtn = HuPadBtn[player->pad];
    savedBtn2 = HuPadBtnDown[player->pad];
    savedBtn3 = HuPadBtnRep[player->pad];
    savedStickX = HuPadStkX[player->pad];
    savedStickY = HuPadStkY[player->pad];
    savedStick2 = HuPadStkXSum[player->pad];
    savedStick3 = HuPadStkYSum[player->pad];
    if (player->cpuDifficulty != -1) {
        s16 params[22][4] = {
            { 0, 0, 0, 0 },
            { 300, 300, 200, 150 },
            { 11, 9, 6, 3 },
            { 6, 6, 6, 6 },
            { 11, 9, 5, 2 },
            { 4, 4, 3, 1 },
            { -30, -40, -40, -200 },
            { 15, 20, 20, 100 },
            { 45, 35, 25, 25 },
            { 1, 1, 1, 15 },
            { 36, 46, 56, 66 },
            { 1, 1, 1, 1 },
            { 20, 20, 15, 15 },
            { 35, 25, 12, 8 },
            { 0, 0, 6, 6 },
            { 1, 8, 4, 5 },
            { 0, 24, 16, 32 },
            { 1, 8, 24, 1 },
            { 14, 9, 6, 0 },
            { 6, 8, 5, 7 },
            { 0, 0, 0, 0 },
            { 1, 1, 1, 1 },
        };

        HuPadBtn[player->pad] = 0;
        HuPadBtnDown[player->pad] = 0;
        HuPadBtnRep[player->pad] = 0;
        HuPadStkX[player->pad] = 0;
        HuPadStkY[player->pad] = 0;
        HuPadStkXSum[player->pad] = 0;
        HuPadStkYSum[player->pad] = 0;
        if (m222_outTimerTbl[group] != 0) {
            m222_comStateTbl[group] = 13;
        }
        if (m222_kinokoPhase == 2) {
            if (m222_kinokoTimer >= ((m222_giantGroup == group) ? 10 : 30)) {
                if (m222_comStateTbl[group] > 0 && m222_comStateTbl[group] < 4) {
                    m222_comStateTbl[group] = 10;
                    m222_comWaitTbl[group] = 0;
                }
            }
        }
        if (m222_kinokoPhase == 3) {
            if ((m222_comStateTbl[group] > 0 && m222_comStateTbl[group] < 4) ||
                (m222_comStateTbl[group] >= 10 && m222_comStateTbl[group] < 13)) {
                m222_comStateTbl[group] = (m222_giantGroup == group) ? 4 : 7;
                m222_comWaitTbl[group] = 0;
            }
        }
        if (m222_kinokoPhase == 7) {
            if ((m222_comStateTbl[group] >= 4 && m222_comStateTbl[group] < 7) ||
                (m222_comStateTbl[group] >= 7 && m222_comStateTbl[group] < 10)) {
                m222_comStateTbl[group] = 1;
                m222_comWaitTbl[group] = params[12][player->cpuDifficulty] + rand8() % params[13][player->cpuDifficulty];
                m222_comTimerTbl[group] = 0;
            }
        }
        switch (m222_comStateTbl[group]) {
            case 0:
                m222_comStateTbl[group] = 1;
                m222_comWaitTbl[group] = 5;
            case 1:
                m222_comWaitTbl[group] -= (m222_comWaitTbl[group] > 0) ? 1 : 0;
                if (m222_comWaitTbl[group] > 0) {
                    break;
                }
                for (i = 0, bestDist = 16777216.0f, best = -1; i < 9; i++) {
                    if (m222_blockStateTbl[i] != 0) {
                        dx = object->trans.x - m222_blockObjTbl[i]->trans.x;
                        dz = object->trans.z - m222_blockObjTbl[i]->trans.z;
                        dist = dx * dx + dz * dz + rand8() / 255.0 * params[1][player->cpuDifficulty] * params[1][player->cpuDifficulty];
                        if (dist < bestDist) {
                            bestDist = dist;
                            best = i;
                        }
                    }
                }
                if (best == -1) {
                    m222_comWaitTbl[group] = 1;
                    break;
                }
                m222_comStateTbl[group] = 2;
                m222_comWaitTbl[group] = best;
                m222_comTimerTbl[group] = 0;
                break;
            case 2:
            case 3:
                dx = m222_blockObjTbl[m222_comWaitTbl[group]]->trans.x - object->trans.x;
                dz = m222_blockObjTbl[m222_comWaitTbl[group]]->trans.z - object->trans.z;
                dist = (dx != 0.0f || dz != 0.0f) ? HuSqrtf(dx * dx + dz * dz) : 16777216.0f;
                HuPadStkX[player->pad] = dx / dist * ((dist > 33.0f) ? 1.0 : dist / 33.0) * params[10][player->cpuDifficulty];
                HuPadStkY[player->pad] = -(dz / dist * ((dist > 33.0f) ? 1.0 : dist / 33.0) * params[10][player->cpuDifficulty]);
                if (object->trans.y > 375.0f && data->unk38 == 1000.0f) {
                    HuPadStkX[player->pad] = 0;
                    HuPadStkY[player->pad] = 66;
                }
                if (m222_comStateTbl[group] == 3 && m222_comTimerTbl[group] == 0 && object->trans.y <= 0.0f) {
                    m222_comStateTbl[group] = 2;
                    m222_comTimerTbl[group] = 0;
                } else if (m222_comStateTbl[group] == 2 && m222_comTimerTbl[group] == 0 && object->trans.y <= 0.0f &&
                           (dist < 50.0f || data->unk53[1] != -1)) {
                    switch ((dist < 50.0f) ? 1 : rand8() % 5 / 2) {
                        case 0:
                            break;
                        case 1:
                            m222_comStateTbl[group] = 3;
                            HuPadBtnDown[player->pad] |= A_BUTTON;
                            m222_comTimerTbl[group] = params[4][player->cpuDifficulty] + rand8() % params[5][player->cpuDifficulty];
                            break;
                        case 2:
                            m222_comStateTbl[group] = 1;
                            m222_comWaitTbl[group] = params[2][player->cpuDifficulty] + rand8() % params[3][player->cpuDifficulty];
                            break;
                    }
                }
                if (m222_comStateTbl[group] == 3) {
                    HuPadBtn[player->pad] |= A_BUTTON;
                }
                m222_comTimerTbl[group] -= (m222_comTimerTbl[group] > 0) ? 1 : 0;
                if (m222_blockStateTbl[m222_comWaitTbl[group]] == 0) {
                    m222_comStateTbl[group] = 1;
                    m222_comWaitTbl[group] = params[2][player->cpuDifficulty] + rand8() % params[3][player->cpuDifficulty];
                }
                break;
            case 4:
                m222_comWaitTbl[group] -= (m222_comWaitTbl[group] > 0) ? 1 : 0;
                work = m222_playerObjTbl[group]->data;
                if (m222_comWaitTbl[group] > 0 || work->unk5C == 0x8000) {
                    break;
                }
                for (i = 0, bestDist = 16777216.0f, best = -1; i < 4; i++) {
                    if (i == group || m222_outTimerTbl[i] != 0) {
                        continue;
                    }
                    dx = object->trans.x - m222_playerObjTbl[i]->trans.x;
                    dz = object->trans.z - m222_playerObjTbl[i]->trans.z;
                    dist = dx * dx + dz * dz + params[6][player->cpuDifficulty] + rand8() % params[7][player->cpuDifficulty];
                    if (dist < bestDist) {
                        bestDist = dist;
                        best = i;
                    }
                }
                if (best == -1) {
                    m222_comWaitTbl[group] = 1;
                    break;
                }
                m222_comStateTbl[group] = 5;
                m222_comWaitTbl[group] = best;
                if (params[14][player->cpuDifficulty] + rand8() % params[15][player->cpuDifficulty] < 8) {
                    break;
                }
                dx = (m222_playerObjTbl[best]->trans.x > 0.0f) ? m222_playerObjTbl[best]->trans.x - 350.0f
                                                                        : -m222_playerObjTbl[best]->trans.x - 350.0f;
                dz = (m222_playerObjTbl[best]->trans.z > 0.0f) ? m222_playerObjTbl[best]->trans.z - 350.0f
                                                                        : -m222_playerObjTbl[best]->trans.z - 350.0f;
                if (dx * dx + dz * dz < 62500.0f) {
                    m222_comWaitTbl[group] += 4;
                    m222_comOfsXTbl[group] = m222_comOfsZTbl[group] = 0.0f;
                    if (((m222_playerObjTbl[best]->trans.x - object->trans.x > 0.0f)
                             ? m222_playerObjTbl[best]->trans.x - object->trans.x
                             : -(m222_playerObjTbl[best]->trans.x - object->trans.x)) <
                        ((m222_playerObjTbl[best]->trans.z - object->trans.z > 0.0f)
                             ? m222_playerObjTbl[best]->trans.z - object->trans.z
                             : -(m222_playerObjTbl[best]->trans.z - object->trans.z))) {
                        m222_comOfsXTbl[group] = rand8() / 255.0 * 200.0 * ((m222_playerObjTbl[best]->trans.x < 0.0f) ? 1 : -1);
                    } else {
                        m222_comOfsZTbl[group] = rand8() / 255.0 * 200.0 * ((m222_playerObjTbl[best]->trans.z < 0.0f) ? 1 : -1);
                    }
                }
                break;
            case 5:
            case 6:
                dx = m222_playerObjTbl[m222_comWaitTbl[group] % 4]->trans.x - object->trans.x +
                     ((m222_comWaitTbl[group] >= 4) ? m222_comOfsXTbl[group] : 0.0f);
                dz = m222_playerObjTbl[m222_comWaitTbl[group] % 4]->trans.z - object->trans.z +
                     ((m222_comWaitTbl[group] >= 4) ? m222_comOfsZTbl[group] : 0.0f);
                dist = (dx != 0.0f || dz != 0.0f) ? HuSqrtf(dx * dx + dz * dz) : 16777216.0f;
                HuPadStkX[player->pad] = dx / dist * ((dist > 33.0f) ? 66.0f : dist * 2);
                HuPadStkY[player->pad] = -(dz / dist * ((dist > 33.0f) ? 66.0f : dist * 2));
                if (m222_comStateTbl[group] == 5 && m222_comTimerTbl[group] <= 0 && m222_giantRunF != 0) {
                    m222_comStateTbl[group] = 6;
                    m222_comTimerTbl[group] = 0;
                }
                m222_comTimerTbl[group] -= (m222_comTimerTbl[group] > 0) ? 1 : 0;
                if (m222_comStateTbl[group] == 6 && m222_giantRunF == 0) {
                    m222_comStateTbl[group] = 4;
                    m222_comWaitTbl[group] = params[8][player->cpuDifficulty] + rand8() % params[9][player->cpuDifficulty];
                }
                break;
            case 7:
                m222_comWaitTbl[group] -= (m222_comWaitTbl[group] > 0) ? 1 : 0;
                if (m222_comWaitTbl[group] <= 0) {
                    m222_comStateTbl[group] = 8;
                    m222_comWaitTbl[group] = -1;
                    m222_comTimerTbl[group] = 0;
                }
                break;
            case 8:
            case 9:
                if (m222_comWaitTbl[group] == -1) {
                    bestScore = 100.0f;
                    dx = m222_playerObjTbl[m222_giantGroup]->trans.x - object->trans.x;
                    dz = m222_playerObjTbl[m222_giantGroup]->trans.z - object->trans.z;
                    dist = (dx != 0.0f || dz != 0.0f) ? 1.0f / HuSqrtf(dx * dx + dz * dz) : 0.000001f;
                    dirX = dx * dist;
                    dirZ = dz * dist;
                    for (i = 0, best = 0; i < 4; i++) {
                        cornerX = (i < 2) ? -400.0f : 400.0f;
                        dx = cornerX - object->trans.x;
                        cornerZ = ((i + 1) % 4 < 2) ? -350.0f : 350.0f;
                        dz = cornerZ - object->trans.z;
                        dist = (dx != 0.0f || dz != 0.0f) ? HuSqrtf(dx * dx + dz * dz) : 16777216.0f;
                        normX = dx / dist;
                        normZ = dz / dist;
                        bestDist = dirX * normX + dirZ * normZ + 1.0f;
                        weight = (dist == 16777216.0f) ? 10.0f : ((dist > 500.0f) ? 0.0f : 1.0 - dist / 500.0);
                        bestDist = bestDist * bestDist + weight * weight * 4.0f;
                        if (m222_comStateTbl[group] == 9) {
                            otherData = m222_playerObjTbl[m222_giantGroup]->data;
                            sinVal = sindf(otherData->unk3C);
                            cosVal = cosdf(otherData->unk3C);
                            dx = (sinVal > 0.0f) ? sinVal : -sinVal;
                            signSin = (sinVal < 0.0f) ? -1.0f : 1.0f;
                            dz = (cosVal > 0.0f) ? cosVal : -cosVal;
                            signCos = (cosVal < 0.0f) ? -1.0f : 1.0f;
                            hitZ = 1000.0f;
                            if (dz < dx) {
                                hitZ = (401.0f - signSin * m222_playerObjTbl[m222_giantGroup]->trans.x) / dx * dz +
                                       signCos * m222_playerObjTbl[m222_giantGroup]->trans.z;
                            }
                            if (hitZ > 351.0f) {
                                hitX = (351.0f - signCos * m222_playerObjTbl[m222_giantGroup]->trans.z) / dz * dx +
                                       signSin * m222_playerObjTbl[m222_giantGroup]->trans.x;
                                if (hitX > 401.0f) {
                                    hitZ = (401.0f - signSin * m222_playerObjTbl[m222_giantGroup]->trans.x) / dx * dz +
                                           signCos * m222_playerObjTbl[m222_giantGroup]->trans.z;
                                    hitX = 401.0f;
                                } else {
                                    hitZ = 351.0f;
                                }
                            } else {
                                hitX = 401.0f;
                            }
                            hitX = hitX * signSin - cornerX;
                            hitZ = hitZ * signCos - cornerZ;
                            dist = (hitX != 0.0f || hitZ != 0.0f) ? HuSqrtf(hitX * hitX + hitZ * hitZ) : 0.0f;
                            bestDist += (dist > 600.0f) ? 0.0 : (1.0 - dist / 600.0) * 8.0;
                        }
                        if ((m222_comStateTbl[group] == 8 || m222_comStateTbl[group] == 9) && bestDist < bestScore) {
                            best = i;
                            bestScore = bestDist;
                        }
                        if (bestScore != 100.0f) {
                            m222_comWaitTbl[group] = best;
                        }
                    }
                }
                dx = ((m222_comWaitTbl[group] < 2) ? -400.0f : 400.0f) - object->trans.x;
                dz = (((m222_comWaitTbl[group] + 1) % 4 < 2) ? -350.0f : 350.0f) - object->trans.z;
                dist = (dx != 0.0f || dz != 0.0f) ? HuSqrtf(dx * dx + dz * dz) : 16777216.0f;
                HuPadStkX[player->pad] = dx / dist * ((dist > 70.0f) ? 70.0f : ((dist > 35.0f) ? dist : 0.0f));
                HuPadStkY[player->pad] = -(dz / dist * ((dist > 70.0f) ? 70.0f : ((dist > 35.0f) ? dist : 0.0f)));
                if (m222_giantRunF != 0) {
                    m222_comTimerTbl[group] -= (m222_comTimerTbl[group] > 0) ? 1 : 0;
                    if (m222_comTimerTbl[group] <= 0) {
                        m222_comStateTbl[group] = 9;
                        m222_comWaitTbl[group] = -1;
                        range = params[19][player->cpuDifficulty];
                        timer = &m222_comTimerTbl[group];
                        rnd = rand8();
                        minTime = params[18][player->cpuDifficulty];
                        if (m222_humanNum == 0) {
                            minTime += 5;
                            newTime = minTime + rnd % (range + 12);
                        } else {
                            newTime = minTime + rnd % range;
                        }
                        *timer = newTime;
                    }
                } else {
                    m222_comTimerTbl[group] -= (m222_comTimerTbl[group] > 0) ? 1 : 0;
                    if (m222_comTimerTbl[group] <= 0) {
                        m222_comStateTbl[group] = 8;
                        m222_comWaitTbl[group] = -1;
                        m222_comTimerTbl[group] = params[18][player->cpuDifficulty] + rand8() % params[19][player->cpuDifficulty];
                    }
                }
                if (data->unk38 != 1000.0f) {
                    HuPadBtn[player->pad] |= A_BUTTON;
                } else if (m222_humanNum != 0) {
                    if (params[16][player->cpuDifficulty] + rand8() % params[17][player->cpuDifficulty] < 32) {
                        break;
                    }
                    posX = object->trans.x;
                    posZ = object->trans.z;
                    otherX = m222_playerObjTbl[m222_giantGroup]->trans.x;
                    otherZ = m222_playerObjTbl[m222_giantGroup]->trans.z;
                    otherData = m222_playerObjTbl[m222_giantGroup]->data;
                    velX = sindf(data->unk3C) * data->unk40;
                    velZ = cosdf(data->unk3C) * data->unk40;
                    otherVelX = sindf(otherData->unk3C) * otherData->unk40;
                    otherVelZ = cosdf(otherData->unk3C) * otherData->unk40;
                    for (i = 0; i < 6; i++) {
                        if ((posX - otherX) * (posX - otherX) + (posZ - otherZ) * (posZ - otherZ) < 22500.0f) {
                            HuPadBtn[player->pad] |= A_BUTTON;
                            HuPadBtnDown[player->pad] |= A_BUTTON;
                            HuPadBtnRep[player->pad] |= A_BUTTON;
                            break;
                        }
                        posX += velX;
                        posZ += velZ;
                        otherX += otherVelX;
                        otherZ += otherVelZ;
                    }
                }
                break;
            case 10:
                m222_comWaitTbl[group] -= (m222_comWaitTbl[group] > 0) ? 1 : 0;
                if (m222_comWaitTbl[group] <= 0) {
                    m222_comStateTbl[group] = 11;
                    m222_comWaitTbl[group] = 0;
                    m222_comTimerTbl[group] = 0;
                }
                break;
            case 11:
            case 12:
                dx = Hu3DData[m222_stageObj->model[1]].pos.x - object->trans.x;
                dz = Hu3DData[m222_stageObj->model[1]].pos.z - object->trans.z;
                dist = (dx != 0.0f || dz != 0.0f) ? HuSqrtf(dx * dx + dz * dz) : 16777216.0f;
                HuPadStkX[player->pad] = dx / dist * ((dist > 33.0f) ? 1.0 : dist / 33.0) * params[10][player->cpuDifficulty];
                HuPadStkY[player->pad] = -(dz / dist * ((dist > 33.0f) ? 1.0 : dist / 33.0) * params[10][player->cpuDifficulty]);
                if (m222_comStateTbl[group] == 12 && m222_comTimerTbl[group] == 0 && object->trans.y <= 0.0f) {
                    m222_comStateTbl[group] = 11;
                    m222_comTimerTbl[group] = 0;
                } else if (m222_comStateTbl[group] == 11 && m222_comTimerTbl[group] == 0 && object->trans.y <= 0.0f &&
                           player->cpuDifficulty > 0 && dist < 50.0f && m222_kinokoTimer >= 42) {
                    switch ((dist < 50.0f) ? 1 : (rand8() & 3) < 3) {
                        case 1:
                            m222_comStateTbl[group] = 12;
                            HuPadBtnDown[player->pad] |= A_BUTTON;
                            m222_comTimerTbl[group] = params[4][player->cpuDifficulty] + rand8() % params[5][player->cpuDifficulty];
                            break;
                    }
                }
                if (m222_comStateTbl[group] == 12) {
                    HuPadBtn[player->pad] |= A_BUTTON;
                }
                m222_comTimerTbl[group] -= (m222_comTimerTbl[group] > 0) ? 1 : 0;
                break;
        }
        HuPadStkXSum[player->pad] = HuPadStkX[player->pad] * 2;
        HuPadStkYSum[player->pad] = HuPadStkY[player->pad] * 2;
    }
    if (m222_kinokoPhase == 3 && m222_giantGroup == group) {
        HuPadBtn[player->pad] = 0;
        HuPadBtnDown[player->pad] = 0;
        HuPadBtnRep[player->pad] = 0;
        HuPadStkX[player->pad] = 0;
        HuPadStkY[player->pad] = 0;
        HuPadStkXSum[player->pad] = 0;
        HuPadStkYSum[player->pad] = 0;
    } else if (m222_kinokoPhase == 5 && m222_giantGroup == group) {
        HuPadBtn[player->pad] = 0;
        HuPadBtnDown[player->pad] = 0;
        HuPadBtnRep[player->pad] = 0;
    }
    if (m222_kinokoPhase == 5 && m222_giantGroup == group) {
        mgPlayerAccel = 30.0f;
        mgPlayerStickDiv = 1.6666666f;
        speed = 18.0f;
        mgPlayerSpeedMax = speed * 2;
        mgPlayerSpeedRun = speed * 1.5f;
        halfSpeed = speed / 2;
        mgPlayerSpeedWalk = speed;
        mgPlayerSpeedMin = halfSpeed;
    }
    if (m222_kinokoPhase == 5 && m222_giantGroup == group) {
        if (m222_giantRunF == 0 && data->unk40 > 9.0f) {
            m222_giantRunF = 1;
            if (HuPadStkX[player->pad] * HuPadStkX[player->pad] + HuPadStkY[player->pad] * HuPadStkY[player->pad] > 1600) {
                data->unk3C = (HuPadStkX[player->pad] == 0) ? ((HuPadStkY[player->pad] >= 0) ? 180.0f : 0.0f)
                                                                  : atan2df(HuPadStkX[player->pad], -HuPadStkY[player->pad]);
            }
            m222_giantRunDir = data->unk3C;
        }
        if (m222_giantRunF != 0) {
            HuPadStkX[player->pad] = sindf(m222_giantRunDir) * 63.0f + HuPadStkX[player->pad] / 6;
            HuPadStkY[player->pad] = cosdf(m222_giantRunDir) * -63.0f + HuPadStkY[player->pad] / 6;
            HuPadStkXSum[player->pad] = HuPadStkX[player->pad] * 2;
            HuPadStkYSum[player->pad] = HuPadStkY[player->pad] * 2;
        }
    } else if (m222_kinokoPhase != 5) {
        m222_giantRunF = 0;
    }
    if ((m222_kinokoPhase == 3 || m222_kinokoPhase == 4 || m222_kinokoPhase == 6) && group != m222_giantGroup) {
        work = m222_playerObjTbl[m222_giantGroup]->data;
        work->unkBE = 1;
        work->unk50 |= 0x200;
    }
    if (m222_phase >= 3 && data->unk53[0] == -1) {
        HuPadStkX[player->pad] = rand8() % 40;
        HuPadStkY[player->pad] = rand8() % 40;
        HuPadStkXSum[player->pad] = HuPadStkX[player->pad] * 2;
        HuPadStkYSum[player->pad] = HuPadStkY[player->pad] * 2;
    }
    if (data->unk53[0] == 5 || data->unk53[0] == 6) {
        if (object->trans.z > 330.0f) {
            object->trans.z = 330.0f;
        }
    }
    if (object->trans.y >= 425.0f) {
        if (object->trans.z > 345.0f) {
            object->trans.z = 345.0f;
        }
    }
    if ((m222_phase != 0 || m222_phaseTimer < 46 || m222_phaseTimer > 54) &&
        ((m222_kinokoPhase != 4 && m222_kinokoPhase != 6) || m222_giantGroup != group) &&
        m222_outTimerTbl[group] == 0) {
        MgPlayerObjMain(object);
        m222_motTimeTbl[group] = -1;
    } else if (m222_motTimeTbl[group] == -1 || m222_motTimeTbl[group] > Hu3DData[object->model[0]].motTime) {
        m222_motTimeTbl[group] = Hu3DData[object->model[0]].motTime;
    } else {
        Hu3DMotionTimeSet(object->model[0], m222_motTimeTbl[group]);
    }
    if (m222_phase == 0 && (m222_phaseTimer < 10 || group != 0)) {
        HuAudFXStop(data->unkC5);
    }
    if ((m222_kinokoPhase == 3 || m222_kinokoPhase == 4 || m222_kinokoPhase == 6) && group != m222_giantGroup) {
        work = m222_playerObjTbl[m222_giantGroup]->data;
        work->unkBE = 0;
        work->unk50 &= ~0x200;
    }
    if (m222_phase == 0 && m222_phaseTimer < 10) {
        data->unk38 = 0.0f;
    }
    if (m222_giantGroup == group && m222_kinokoPhase == 5) {
        omSetSca(object, 2.0f, 2.0f, 2.0f);
        if (m222_giantRunF != 0) {
            if ((data->unk3C > -145.0f && data->unk3C < -35.0f && object->trans.x <= -400.0f) ||
                (data->unk3C > 35.0f && data->unk3C < 145.0f && object->trans.x >= 400.0f) ||
                ((data->unk3C > 125.0f || data->unk3C < -125.0f) && object->trans.z <= -350.0f) ||
                (data->unk3C > -55.0f && data->unk3C < 55.0f && object->trans.z >= 350.0f)) {
                object->trans.x = (object->trans.x <= -400.0f) ? -400.0f : ((object->trans.x >= 400.0f) ? 400.0f : object->trans.x);
                object->trans.z = (object->trans.z <= -350.0f) ? -350.0f : ((object->trans.z >= 350.0f) ? 350.0f : object->trans.z);
                data->unk40 = -mgPlayerSpeedWalk;
                MgPlayerMotSet(object, 30);
                omVibrate(data->unk59, 20, 0, 20);
                for (i = 0; i < 4; i++) {
                    if (m222_outTimerTbl[i] == 0 && m222_groupPlayerTbl[i]->playerNo != data->unk59) {
                        omVibrate(m222_groupPlayerTbl[i]->playerNo, 10, 0, 10);
                    }
                }
                m222_giantRunF = 0;
                m222_shakeTimer = 13;
                m222_shakeAngle = data->unk3C;
                HuAudFXPlay(0x3AA);
            }
        }
    }
    mgPlayerAccel = 15.0f;
    mgPlayerStickDiv = 3.3333333f;
    mgPlayerSpeedMax = 18.0f;
    mgPlayerSpeedRun = 13.5f;
    mgPlayerSpeedWalk = 9.0f;
    mgPlayerSpeedMin = 4.5f;
    HuPadBtn[player->pad] = savedBtn;
    HuPadBtnDown[player->pad] = savedBtn2;
    HuPadBtnRep[player->pad] = savedBtn3;
    HuPadStkX[player->pad] = savedStickX;
    HuPadStkY[player->pad] = savedStickY;
    HuPadStkXSum[player->pad] = savedStick2;
    HuPadStkYSum[player->pad] = savedStick3;
    if (m222_outTimerTbl[group] >= 60) {
        Hu3DModelAttrSet(object->model[0], 4, 4);
    }
    if (m222_outTimerTbl[group] != 0) {
        Hu3DModelAttrSet(object->model[1], 4, 4);
    } else {
        Hu3DModelScaleSet(object->model[1], object->scale.x, object->scale.y, object->scale.z);
    }
}
#else
// Initializer of the CPU params table copied onto the stack in m222_PlayerObjMain.
const s16 m222_comParamTbl[22][4] = {
    { 0, 0, 0, 0 },
    { 300, 300, 200, 150 },
    { 11, 9, 6, 3 },
    { 6, 6, 6, 6 },
    { 11, 9, 5, 2 },
    { 4, 4, 3, 1 },
    { -30, -40, -40, -200 },
    { 15, 20, 20, 100 },
    { 45, 35, 25, 25 },
    { 1, 1, 1, 15 },
    { 36, 46, 56, 66 },
    { 1, 1, 1, 1 },
    { 20, 20, 15, 15 },
    { 35, 25, 12, 8 },
    { 0, 0, 6, 6 },
    { 1, 8, 4, 5 },
    { 0, 24, 16, 32 },
    { 1, 8, 24, 1 },
    { 14, 9, 6, 0 },
    { 6, 8, 5, 7 },
    { 0, 0, 0, 0 },
    { 1, 1, 1, 1 }
};

INCLUDE_ASM("asm/nonmatchings/game/overlays/minigames/16_toadstool_titan/main", m222_PlayerObjMain);
#endif
