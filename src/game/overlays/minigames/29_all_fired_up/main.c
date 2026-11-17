#include "common.h"
#include "game/input.h"
#include "game/mallocblock.h"
#include "game/pause.h"
#include "gcc/memory.h"
#include "game/overlays/minigame.h"

#define ABS(x) ((x) > 0.0f ? (x) : 0.0f - (x))

// Per-object data allocated for each entry of m241_fireObjTbl, stored at omObjData->data
typedef struct {
    /* 0x00 */ s8 unk00; // Index into m241_fireObjTbl
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x20 */ Vec pos;
    /* 0x2C */ Vec unk2C;
    /* 0x38 */ u8 unk38;
} AllFiredUpFireWork; // Size 0x3C

// Per-player work allocated in m241_PlayerObjInit, stored at MgPlayerWork->unk158
typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ u16 unk08;
    /* 0x0C */ f32 unk0C; // Stick angle
} AllFiredUpPlayerWork;   // Size 0x10

typedef struct {
    /* 0x00 */ u8 unk00;
    /* 0x02 */ s16 unk02[4];
} AllFiredUpSetupWork; // Size 0xC

extern s32 omCharModelNoTbl[][6];
extern u8 omAllPauseF;
extern f32 mgPlayerSpeedMin;

u8 m241_startPermTbl[24][4] = {
    { 0, 1, 2, 3 },
    { 0, 1, 3, 2 },
    { 0, 2, 1, 3 },
    { 0, 2, 3, 1 },
    { 0, 3, 1, 2 },
    { 0, 3, 2, 1 },
    { 1, 0, 2, 3 },
    { 1, 0, 3, 2 },
    { 1, 2, 3, 0 },
    { 1, 2, 0, 3 },
    { 1, 3, 0, 2 },
    { 1, 3, 2, 0 },
    { 2, 0, 1, 3 },
    { 2, 0, 3, 1 },
    { 2, 1, 0, 3 },
    { 2, 1, 3, 0 },
    { 2, 3, 0, 1 },
    { 2, 3, 1, 0 },
    { 3, 0, 1, 2 },
    { 3, 0, 2, 1 },
    { 3, 1, 0, 2 },
    { 3, 1, 2, 0 },
    { 3, 2, 0, 1 },
    { 3, 2, 1, 0 }
};
Vec m241_startPosTbl[4] = {
    { 60.0f, 0.0f, -60.0f },
    { 60.0f, 0.0f, 60.0f },
    { -60.0f, 0.0f, 60.0f },
    { -60.0f, 0.0f, -60.0f }
};
u16 m241_outTimeTbl[4] = { 1800, 1800, 1800, 1800 };
s8 m241_firePhase = 0;
s8 m241_fireNum = 15;
f32 m241_ringRadius = 400.0f;
s8 m241_ringMaxF = 0;
u8 m241_patternSeqTbl[6][6] = {
    { 0, 1, 2, 1, 0, 2 },
    { 0, 2, 1, 0, 1, 2 },
    { 0, 2, 0, 1, 2, 1 },
    { 2, 0, 2, 1, 2, 0 },
    { 2, 0, 1, 0, 2, 1 },
    { 2, 1, 0, 2, 0, 1 }
};
s32 m241_exitCnt = 0;
s8 m241_exitReqF = 0;
f32 m241_spinSpeed = 1.0f;
s8 m241_comAliveF = 0;
s8 m241_playerCreateNo = 0;
s8 m241_resultMode = -1;
s32 m241_coinSetFTbl[4] = { 0 };
s32 m241_smokeTimerTbl[4][4] = {
    { 0, -2, -4, -6 },
    { 0, -2, -4, -6 },
    { 0, -2, -4, -6 },
    { 0, -2, -4, -6 }
};
f32 m241_smokeScaleTbl[4] = { 1.0f, 1.5f, 2.0f, 2.5f };

s32 m241_fireCreateNo BSS;
s8 m241_patternNo BSS;
s8 m241_startPosNo BSS;
MinigameFlow m241_mgFlow BSS;
AllFiredUpSetupWork m241_setupWork BSS;
u8 m241_setupWorkPad[4] BSS; /* Unreferenced. */
omObjData *m241_fireObjTbl[21] BSS;
u8 m241_fireObjTblPad[4] BSS; /* Unreferenced. */
Vec m241_fireStartPosTbl[21] BSS;
s8 m241_patternType BSS;
s16 m241_firePhaseTimer BSS;
s8 m241_patternSeqNo BSS;
s8 m241_patternDirF BSS;

/* Fields of m241_setupWork, aliased in undefined_syms.txt. */
extern u8 m241_startPermNo;
extern s16 m241_smokeMdlTbl[];

void m241_FlowInit(MinigameFlow *flow);
void m241_CameraInit(void);
void m241_MainObjMain(omObjData *object);
void m241_FireStartPosInit(void);
void m241_FireObjInit(omObjData *object);
void m241_FireObjMain(omObjData *object);
void m241_FireDropUpdate(omObjData *object);
void m241_FireAdd(void);
void m241_FirePosStore(void);
void m241_FirePhaseUpdate(void);
void m241_FireWanderUpdate(omObjData *object);
void m241_FireGatherUpdate(omObjData *object);
void m241_FirePatternSet(void);
void m241_FireSpreadUpdate(omObjData *object);
void m241_FirePatternUpdate(omObjData *object);
void m241_FireHitCheck(omObjData *object);
void m241_PlayerObjInit(omObjData *object);
void m241_PlayerObjMain(omObjData *object);
void m241_PlayerIntroUpdate(omObjData *object);
void m241_PlayerFlyUpdate(omObjData *object);
void m241_SmokeUpdate(omObjData *object);
void m241_PlayerComInput(omObjData *object);
void m241_ComCircleAngleSet(omObjData *object, f32 dist, s8 arg2);
void m241_MapObjInit(omObjData *object);

void m241_ObjectSetup(void) {
    omObjData *object;
    s32 i;

    MapCollInit(32);
    Hu3DQuadPoolInit(&mgQuadPool, 64);
    Hu3DSprModelInit(64);
    omInitObjMan(32, 0);
    omGameSysInit();
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    MgFieldStatClear();
    m241_CameraInit();
    m241_FlowInit(&m241_mgFlow);
    MgFlowInit(&m241_mgFlow);
    Hu3DGLightColorSet(1, 64, 64, 64);
    Hu3DGLightDirSet(1, 0.0f, 0.0f, 100.0f);
    omSetStatBit(omAddObj(0, 0, 0, -1, m241_MainObjMain), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    MgMapBaseSet(mgMapObjNum);
    object = omAddObj(0, 1, 0, -1, m241_MapObjInit);
    mgMapObjTbl[mgMapObjNum++] = object;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    m241_startPermNo = (rand8() * 24) >> 8;
    for (i = 0; i < 4; i++) {
        mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(1, 2, 60, -1, m241_PlayerObjInit);
    }
    for (i = 0; i < 4; i++) {
        m241_smokeMdlTbl[i] = Hu3DModelRead(0x4A0003, 0x819);
        Hu3DModelAttrSet(m241_smokeMdlTbl[i], 4, 4);
    }
    m241_FireStartPosInit();
    m241_patternSeqNo = (rand8() * 6) >> 8;
    for (i = 0; i < 21; i++) {
        m241_fireObjTbl[i] = omAddObj(1, 2, 0, -1, m241_FireObjInit);
    }
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
}

void m241_FlowInit(MinigameFlow *flow) {
    s32 i;

    mgFlowSeqTime = 0xF;
    flow->state = MG_STATE_OPENING;
    flow->type = MINIGAME_1V1;
    flow->timerMode = MG_TIMER_COUNT_DOWN;
    flow->timeDisp = MG_TIME_DISP_COUNTDOWN;
    flow->newRecord = FALSE;
    flow->gauge = MG_GAUGE_NONE;
    flow->resultType = MG_RESULT_NONE;
    flow->startDelay = 0x5A;
    flow->timer = 0x708;
    flow->timeLimit = -1;
    flow->finishDelay = 0x4B;
    flow->resultDelay = 0x96;
    for (i = 0; i < 4; i++) {
        flow->gaugeValue[i] = 0;
        flow->winners[i] = 0xFF;
    }
}

void m241_CameraInit(void) {
    s32 camIndex;

    Center.x = 0.0f;
    Center.y = 820.0f;
    Center.z = 650.0f;
    CRot.x = -45.0f;
    CRot.y = CRot.z = Center.x;
    CZoom = 2100.0f;
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(camIndex, 30.0f, 80.0f, 8000.0f);
}

void m241_MainObjMain(omObjData *object) {
    if (omPauseChk() + omAllPauseF == 0) {
        if (m241_exitReqF == 0 && omSysExitReq == 1) {
            HuAudFXAllStop();
            if (!(HuAudStat & 4)) {
                HuAudSeqFadeOut(30);
            } else {
                HuAudSeqStop();
            }
            MgFlowStatSet(MG_STATE_EXIT);
            m241_exitReqF = 1;
        }
        MgFieldStatUpdate();
        switch (MgFlowMain()) {
            case 0:
                mgFlowSeqNo = 53;
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                if (m241_exitCnt == 0) {
                    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                } else if (WipeStatGet() == 0 && !(HuAudStat & 4)) {
                    omOvlReturnEx(1);
                }
                m241_exitCnt++;
                break;
        }
    }
}

void m241_FireStartPosInit(void) {
    s32 i;

    for (i = 0; i < 15; i++) {
        m241_fireStartPosTbl[i].y = (rand8() % 200) * 3 + 1200.0f;
    }
    m241_fireStartPosTbl[0].x = m241_fireStartPosTbl[0].z = 0.0f;
    m241_fireStartPosTbl[1].x = sindf(0.0f) * 80.0f;
    m241_fireStartPosTbl[1].z = cosdf(0.0f) * 80.0f;
    m241_fireStartPosTbl[2].x = sindf(60.0f) * 80.0f;
    m241_fireStartPosTbl[2].z = cosdf(60.0f) * 80.0f;
    m241_fireStartPosTbl[3].x = sindf(120.0f) * 80.0f;
    m241_fireStartPosTbl[3].z = cosdf(120.0f) * 80.0f;
    m241_fireStartPosTbl[4].x = sindf(180.0f) * 80.0f;
    m241_fireStartPosTbl[4].z = cosdf(180.0f) * 80.0f;
    m241_fireStartPosTbl[5].x = sindf(240.0f) * 80.0f;
    m241_fireStartPosTbl[5].z = cosdf(240.0f) * 80.0f;
    m241_fireStartPosTbl[6].x = sindf(300.0f) * 80.0f;
    m241_fireStartPosTbl[6].z = cosdf(300.0f) * 80.0f;
    m241_fireStartPosTbl[7].x = sindf(0.0f) * 80.0f * 2;
    m241_fireStartPosTbl[7].z = cosdf(0.0f) * 80.0f * 2;
    m241_fireStartPosTbl[8].x = sindf(45.0f) * 80.0f * 2;
    m241_fireStartPosTbl[8].z = cosdf(45.0f) * 80.0f * 2;
    m241_fireStartPosTbl[9].x = sindf(90.0f) * 80.0f * 2;
    m241_fireStartPosTbl[9].z = cosdf(90.0f) * 80.0f * 2;
    m241_fireStartPosTbl[10].x = sindf(135.0f) * 80.0f * 2;
    m241_fireStartPosTbl[10].z = cosdf(135.0f) * 80.0f * 2;
    m241_fireStartPosTbl[11].x = sindf(180.0f) * 80.0f * 2;
    m241_fireStartPosTbl[11].z = cosdf(180.0f) * 80.0f * 2;
    m241_fireStartPosTbl[12].x = sindf(225.0f) * 80.0f * 2;
    m241_fireStartPosTbl[12].z = cosdf(225.0f) * 80.0f * 2;
    m241_fireStartPosTbl[13].x = sindf(270.0f) * 80.0f * 2;
    m241_fireStartPosTbl[13].z = cosdf(270.0f) * 80.0f * 2;
    m241_fireStartPosTbl[14].x = sindf(315.0f) * 80.0f * 2;
    m241_fireStartPosTbl[14].z = cosdf(315.0f) * 80.0f * 2;
    for (i = 15; i < 21; i++) {
        m241_fireStartPosTbl[i].x = m241_fireStartPosTbl[i].y = m241_fireStartPosTbl[i].z = 0.0f;
    }
}

void m241_FireObjInit(omObjData *object) {
    AllFiredUpFireWork *work;
    s16 model;

    object->func = m241_FireObjMain;
    work = object->data = HuMemAllocTag(sizeof(AllFiredUpFireWork), TAG_OVERLAY);
    memset(work, 0, sizeof(AllFiredUpFireWork));
    work->unk00 = m241_fireCreateNo;
    work->unk04 = 0.0f;
    work->unk08 = 0.0f;
    work->unk1C = 0;
    work->unk0C = 0.0f;
    work->unk14 = 0.0f;
    work->unk10 = 0.0f;
    work->unk18 = 1.0f;
    work->unk38 = 0;
    object->trans.x = m241_fireStartPosTbl[work->unk00].x;
    object->trans.y = m241_fireStartPosTbl[work->unk00].y;
    object->trans.z = m241_fireStartPosTbl[work->unk00].z;
    object->scale.x = object->scale.y = object->scale.z = 1.2f;
    model = object->model[0] = Hu3DModelRead(0xA008A, 0xAA9);
    if (work->unk00 == 0) {
        Hu3DAnimRead(Hu3DData[model].hmf, 0xA008C, "c201n_00_DEF");
    } else {
        Hu3DAnimLink(Hu3DData[model].hmf, 0, 0, "c201n_00_DEF");
    }
    Hu3DModelRemakeStatic(model);
    Hu3DModelDynamicFree(model);
    object->model[1] = Hu3DModelRead(0x4A0004, 0x2D9);
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    if (work->unk00 >= 15) {
        Hu3DModelAttrSet(object->model[0], 4, 4);
        Hu3DModelAttrSet(object->model[1], 4, 4);
    }
    m241_fireCreateNo++;
}

void m241_FireObjMain(omObjData *object) {
    AllFiredUpFireWork *work;

    if (omPauseChk() + omAllPauseF == 0) {
        work = object->data;
        switch (MgFlowStatGet()) {
            case MG_STATE_OPENING:
                m241_FireDropUpdate(object);
                break;
            case MG_STATE_PLAY:
                if (m241_fireNum - 1 >= work->unk00) {
                    m241_FireHitCheck(object);
                }
                if (work->unk00 == 0) {
                    m241_FirePhaseUpdate();
                }
                switch (m241_firePhase) {
                    case 0:
                        m241_FireWanderUpdate(object);
                        break;
                    case 1:
                        m241_FireGatherUpdate(object);
                        break;
                    case 2:
                        m241_FireSpreadUpdate(object);
                        break;
                    case 3:
                        m241_FirePatternUpdate(object);
                        break;
                }
                break;
            case MG_STATE_FINISH:
                object->scale.x -= 0.05f;
                if (object->scale.x < 0.0f) {
                    object->scale.x = 0.0f;
                }
                object->scale.y -= 0.05f;
                if (object->scale.y < 0.0f) {
                    object->scale.y = 0.0f;
                }
                object->scale.z -= 0.05f;
                if (object->scale.z < 0.0f) {
                    object->scale.z = 0.0f;
                }
                work->unk08 -= 0.05f;
                if (work->unk08 < 0.0f) {
                    work->unk08 = 0.0f;
                }
                Hu3DModelScaleSet(object->model[1], work->unk08, work->unk08, work->unk08);
                break;
        }
    }
}

void m241_FireDropUpdate(omObjData *object) {
    AllFiredUpFireWork *work = object->data;

    if (work->unk00 < 15) {
        if (MgFlowStatTimeGet() >= 16) {
            object->trans.y -= work->unk04 + 15.0f;
            work->unk04 += 3.0f;
            if (object->trans.y < 0.0f) {
                object->trans.y = 0.0f;
                if (work->unk38 == 0) {
                    if (!(work->unk00 & 1)) {
                        HuAudFXPlay(0x441);
                    }
                    work->unk38 = 1;
                }
            }
            work->unk08 += 0.05f;
            if (work->unk08 > 1.0f) {
                work->unk08 = 1.0f;
            }
        }
        Hu3DModelScaleSet(object->model[1], work->unk08, work->unk08, work->unk08);
    }
}

void m241_FirePhaseUpdate(void) {
    s32 i;

    switch (m241_firePhase) {
        case 0:
            if (m241_firePhaseTimer == 0) {
                if (m241_patternNo > 0 && m241_fireNum < 21) {
                    m241_FireAdd();
                    for (i = 0; i < 21; i++) {
                        ((AllFiredUpFireWork *)m241_fireObjTbl[i]->data)->unk18 += 0.1f;
                    }
                }
                if (m241_firePhaseTimer == 0) {
                    HuAudFXPlay(0x444);
                }
            }
            if (m241_firePhaseTimer != 90) {
                m241_firePhaseTimer++;
            } else {
                m241_firePhase = 1;
                m241_firePhaseTimer = 0;
                m241_FirePosStore();
            }
            break;
        case 1:
            if (m241_firePhaseTimer == 0) {
                HuAudFXPlay(0x443);
            }
            if (m241_firePhaseTimer != 30) {
                m241_firePhaseTimer++;
            } else {
                m241_firePhase = 2;
                m241_firePhaseTimer = 0;
                m241_FirePosStore();
            }
            break;
        case 2:
            if (m241_firePhaseTimer == 0) {
                m241_patternType = m241_patternSeqTbl[m241_patternSeqNo][m241_patternNo++];
                if (m241_patternNo >= 7) {
                    m241_patternNo = 0;
                }
                m241_FirePatternSet();
                HuAudFXPlay(0x442);
            }
            if (m241_firePhaseTimer != 30) {
                m241_firePhaseTimer++;
            } else {
                m241_firePhase = 3;
                m241_firePhaseTimer = 0;
                m241_ringRadius = 400.0f;
                m241_ringMaxF = 0;
            }
            break;
        case 3:
            if (m241_firePhaseTimer == 0) {
                HuAudFXPlay(0x442);
                m241_firePhaseTimer++;
            } else if (m241_firePhaseTimer != 150) {
                m241_firePhaseTimer++;
            } else {
                m241_firePhase = 0;
                m241_firePhaseTimer = 0;
            }
            break;
    }
}

void m241_FireAdd(void) {
    omObjData *first;
    omObjData *object;
    AllFiredUpFireWork *firstWork;
    AllFiredUpFireWork *work;

    m241_fireNum++;
    first = m241_fireObjTbl[0];
    object = m241_fireObjTbl[m241_fireNum - 1];
    firstWork = first->data;
    work = object->data;
    object->trans.x = first->trans.x;
    object->trans.y = first->trans.y;
    object->trans.z = first->trans.z;
    work->unk08 = firstWork->unk08;
    work->unk0C = firstWork->unk0C;
    work->unk14 = firstWork->unk14;
    work->unk10 = firstWork->unk10;
    Hu3DModelAttrSet(object->model[0], 4, 0);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelScaleSet(object->model[1], work->unk08, work->unk08, work->unk08);
    Hu3DModelAttrSet(object->model[1], 4, 0);
}

void m241_FirePosStore(void) {
    AllFiredUpFireWork *work;
    s32 i;

    for (i = 0; i < m241_fireNum; i++) {
        work = m241_fireObjTbl[i]->data;
        work->pos.x = m241_fireObjTbl[i]->trans.x;
        work->pos.y = m241_fireObjTbl[i]->trans.y;
        work->pos.z = m241_fireObjTbl[i]->trans.z;
    }
}

void m241_FireWanderUpdate(omObjData *object) {
    AllFiredUpFireWork *work = object->data;

    if (m241_fireNum >= work->unk00) {
        if (object->trans.y > 0.0f) {
            object->trans.y -= 10.0f;
            if (object->trans.y < 0.0f) {
                object->trans.y = 0.0f;
            }
            work->unk10 = 0.0f;
            work->unk08 += 0.1f;
            if (work->unk08 > 1.0f) {
                work->unk08 = 1.0f;
            }
            Hu3DModelScaleSet(object->model[1], work->unk08, work->unk08, work->unk08);
        }
        if (MgFlowStatTimeGet() % 15 == 0) {
            work->unk0C = (rand8() % 180) * 2;
        }
        if (HuSqrtf(object->trans.x * object->trans.x + object->trans.z * object->trans.z) >= 700.0f) {
            work->unk0C = atan2df(-object->trans.x, -object->trans.z);
        }
        object->trans.x += sindf(work->unk0C) * 5.0f * work->unk18;
        object->trans.z += cosdf(work->unk0C) * 5.0f * work->unk18;
        Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    }
}

void m241_FireGatherUpdate(omObjData *object) {
    AllFiredUpFireWork *work = object->data;

    if (m241_fireNum >= work->unk00) {
        object->trans.x += (0.0f - work->pos.x) / 30.0f;
        object->trans.y += (0.0f - work->pos.y) / 30.0f;
        object->trans.z += (0.0f - work->pos.z) / 30.0f;
        Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    }
}

void m241_FirePatternSet(void) {
    AllFiredUpFireWork *work;
    f32 step;
    s32 half;
    s32 i;

    switch (m241_patternType) {
        case 0:
            step = 360.0f / m241_fireNum;
            for (i = 0; i < m241_fireNum; i++) {
                work = m241_fireObjTbl[i]->data;
                work->unk0C = step * work->unk00;
                work->unk2C.x = sindf(work->unk0C) * 400.0f;
                work->unk2C.y = 0.0f;
                work->unk2C.z = cosdf(work->unk0C) * 400.0f;
            }
            break;
        case 1:
            half = m241_fireNum / 2;
            if (m241_fireNum % 2 != 0) {
                step = 1400.0f / half;
            } else {
                step = 1400.0f / (half - 1);
            }
            for (i = 0; i < half; i++) {
                work = m241_fireObjTbl[i]->data;
                if (m241_fireNum % 2 != 0) {
                    work->unk2C.x = -700.0f + step * work->unk00 + step / 2.0f;
                } else {
                    work->unk2C.x = -700.0f + step * work->unk00;
                }
                work->unk2C.y = 0.0f;
                work->unk2C.z = 0.0f;
                work->unk0C = atan2df(work->unk2C.x, work->unk2C.z);
                work->unk14 = ABS(work->unk2C.x);
            }
            for (i = half; i < m241_fireNum; i++) {
                work = m241_fireObjTbl[i]->data;
                work->unk2C.x = 0.0f;
                work->unk2C.y = 0.0f;
                work->unk2C.z = -700.0f + step * (work->unk00 - half);
                work->unk0C = atan2df(work->unk2C.x, work->unk2C.z);
                work->unk14 = ABS(work->unk2C.z);
            }
            break;
        case 2:
            step = 1400.0f / (m241_fireNum - 1);
            for (i = 0; i < m241_fireNum; i++) {
                work = m241_fireObjTbl[i]->data;
                work->unk2C.x = -700.0f + step * work->unk00;
                work->unk10 = 360.0f / (m241_fireNum - 1) * work->unk00;
                if (work->unk10 >= 180.0f) {
                    work->unk10 -= 180.0f;
                }
                work->unk2C.y = sindf(work->unk10) * 350.0f + 0.0f;
                work->unk2C.z = 0.0f;
                work->unk0C = atan2df(work->unk2C.x, 0.0f);
                work->unk14 = ABS(work->unk2C.x);
                work->unk08 = 1.0f - sindf(work->unk10) * 0.4f;
            }
            break;
    }
}

void m241_FireSpreadUpdate(omObjData *object) {
    AllFiredUpFireWork *work = object->data;

    if (m241_fireNum >= work->unk00) {
        switch (m241_patternType) {
            case 0:
            case 1:
                object->trans.x += (work->unk2C.x - 0.0f) / 30.0f;
                object->trans.z += (work->unk2C.z - 0.0f) / 30.0f;
                break;
            case 2:
                object->trans.x += (work->unk2C.x - 0.0f) / 30.0f;
                object->trans.y += (work->unk2C.y - 0.0f) / 30.0f;
                object->trans.z += (work->unk2C.z - 0.0f) / 30.0f;
                Hu3DModelScaleSet(object->model[1], work->unk08, work->unk08, work->unk08);
                break;
        }
        Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    }
}

void m241_FirePatternUpdate(omObjData *object) {
    AllFiredUpFireWork *work = object->data;
    MgPlayerWork *data;
    s32 i;

    if (m241_fireNum >= work->unk00) {
        if (work->unk00 == 0) {
            switch (m241_patternType) {
                case 0:
                    for (i = 0; i < 4; i++) {
                        data = mgPlayerObjTbl[i]->data;
                        if ((GwPlayer[data->unk59].stat & 1) && data->unk38 != 1000.0f) {
                            m241_comAliveF = 1;
                            break;
                        }
                    }
                    if (m241_ringRadius == 0.0f || m241_ringRadius == 700.0f) {
                        m241_patternDirF ^= 1;
                    } else if (m241_comAliveF != 0) {
                        if (MgFlowStatTimeGet() % 15 == 0 && (rand8() >> 7)) {
                            m241_patternDirF ^= 1;
                        }
                    }
                    break;
                case 2:
                    m241_patternDirF = 0;
                    break;
                default:
                    if (MgFlowStatTimeGet() % 15 == 0 && (rand8() >> 7)) {
                        m241_patternDirF ^= 1;
                    }
                    break;
            }
        }
        switch (m241_patternType) {
            case 0:
                if (m241_patternDirF == 0 && m241_ringMaxF == 0 && (rand8() & 1)) {
                    m241_patternDirF = 1;
                }
                if (m241_patternDirF != 0) {
                    m241_ringRadius += 0.5f;
                    if (m241_ringRadius > 700.0f) {
                        m241_ringRadius = 700.0f;
                        m241_ringMaxF = 1;
                    }
                } else {
                    m241_ringRadius -= 0.5f;
                    if (m241_ringRadius < 0.0f) {
                        m241_ringRadius = 0.0f;
                    }
                }
                work->unk0C += 1.5f;
                if (work->unk0C >= 360.0f) {
                    work->unk0C -= 360.0f;
                }
                object->trans.x = sindf(work->unk0C) * m241_ringRadius;
                object->trans.z = cosdf(work->unk0C) * m241_ringRadius;
                break;
            case 1:
                if (work->unk00 == 0 && MgFlowStatTimeGet() % 15 == 0) {
                    m241_spinSpeed = (rand8() % 15) / 10.0f + 1.0f;
                }
                if (m241_patternDirF != 0) {
                    work->unk0C += m241_spinSpeed;
                    if (work->unk0C >= 360.0f) {
                        work->unk0C -= 360.0f;
                    }
                } else {
                    work->unk0C -= m241_spinSpeed;
                    if (work->unk0C < 0.0f) {
                        work->unk0C += 360.0f;
                    }
                }
                object->trans.x = sindf(work->unk0C) * work->unk14;
                object->trans.z = cosdf(work->unk0C) * work->unk14;
                break;
            case 2:
                if (work->unk00 == 0 && MgFlowStatTimeGet() % 5 == 0) {
                    m241_spinSpeed = (rand8() % 15) / 10.0f + 1.0f;
                }
                work->unk0C -= m241_spinSpeed;
                if (work->unk0C < 0.0f) {
                    work->unk0C += 360.0f;
                }
                object->trans.x = sindf(work->unk0C) * work->unk14;
                object->trans.z = cosdf(work->unk0C) * work->unk14;
                work->unk10 += 2.0f;
                if (work->unk10 >= 180.0f) {
                    work->unk10 -= 180.0f;
                }
                object->trans.y = sindf(work->unk10) * 350.0f;
                work->unk08 = 1.0f - sindf(work->unk10) * 0.6f;
                Hu3DModelScaleSet(object->model[1], work->unk08, work->unk08, work->unk08);
                break;
        }
        Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    }
}

void m241_FireHitCheck(omObjData *object) {
    MgPlayerWork *data;
    omObjData *player;
    f32 dx;
    f32 dz;
    f32 hitRange = 66.0f;
    s32 i;

    for (i = 0; i < 4; i++) {
        player = mgPlayerObjTbl[i];
        data = player->data;
        if (player->work[0] != 0) {
            continue;
        }
        dx = ABS(player->trans.x - object->trans.x);
        dz = ABS(player->trans.z - object->trans.z);
        if (dx < hitRange && dz < hitRange) {
            if (player->trans.y < object->trans.y + 36.0f && player->trans.y + 150.0f > object->trans.y - 36.0f) {
                player->work[0] = 1;
                m241_outTimeTbl[data->unk59] = MgFlowStatTimeGet();
                HuAudPlayerFXPlay(0x440, data->unk59);
                PlayerFXPlay(0x286, data->unk59);
                omVibrate(data->unk59, 2, 2, 20);
            }
        }
    }
}

void m241_PlayerObjInit(omObjData *object) {
    MgPlayerWork *data;
    AllFiredUpPlayerWork *work;
    s8 chr;
    s32 model;
    s32 motion;

    chr = GwPlayer[m241_playerCreateNo].chr;
    model = omCharModelNoTbl[chr][0];
    motion = omCharModelNoTbl[chr][1];
    MgShadowAltSet(1);
    MgPlayerCreate(object, model, motion, m241_playerCreateNo, 0x2C9, 0x2D9);
    data = object->data;
    data->unk158 = HuMemAllocTag(sizeof(AllFiredUpPlayerWork), TAG_OVERLAY);
    memset(data->unk158, 0, sizeof(AllFiredUpPlayerWork));
    work = data->unk158;
    work->unk04 = 0.0f;
    work->unk00 = 1.0f;
    work->unk08 = 0;
    work->unk0C = 0.0f;
    object->rot.x = object->rot.y = object->rot.z = work->unk0C;
    object->scale.x = object->scale.y = object->scale.z = 1.2f;
    object->work[0] = 0;
    m241_startPosNo = m241_startPermTbl[m241_startPermNo][m241_playerCreateNo];
    object->trans.x = m241_startPosTbl[m241_startPosNo].x;
    object->trans.y = m241_startPosTbl[m241_startPosNo].y;
    object->trans.z = m241_startPosTbl[m241_startPosNo].z;
    MgPlayerMapAttrSet(object, 0, 2);
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[1], object->scale.x, object->scale.y, object->scale.z);
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(chr, 0), 1, 0);
    MgPlayerMotLoad(object, 1, CharMotionDataNumGet(chr, 1), 1, 0);
    MgPlayerMotLoad(object, 2, CharMotionDataNumGet(chr, 2), 1, 0);
    MgPlayerMotLoad(object, 6, CharMotionDataNumGet(chr, 4), 1, 19);
    MgPlayerMotLoad(object, 21, CharMotionDataNumGet(chr, 0x1F), 0, 0);
    MgPlayerMotLoad(object, 14, CharMotionDataNumGet(chr, 0x1A), 1, 0);
    MgPlayerMotLoad(object, 13, CharMotionDataNumGet(chr, 0x2F), 1, 120);
    MgPlayerMotSet(object, 0);
    MgPlayerRadiusSet(object, 60.0f);
    object->func = m241_PlayerObjMain;
    m241_playerCreateNo++;
}

void m241_PlayerObjMain(omObjData *object) {
    MgPlayerWork *data = object->data;
    s32 character;
    s32 i;
    s32 count;
    s32 rank;

    if (omPauseChk() + omAllPauseF == 0) {
        switch (MgFlowStatGet()) {
            case MG_STATE_OPENING:
                m241_PlayerIntroUpdate(object);
                break;
            case MG_STATE_PLAY:
                if (GwPlayer[data->unk59].stat & 1) {
                    m241_PlayerComInput(object);
                }
                MgPlayerObjMain(object);
                if (object->work[0] == 1) {
                    MgPlayerMotSet(object, 14);
                    m241_PlayerFlyUpdate(object);
                    object->work[0] = 2;
                } else if (object->work[0] == 2) {
                    m241_PlayerFlyUpdate(object);
                }
                if (data->unk59 == 3) {
                    count = 0;
                    for (i = 0; i < 4; i++) {
                        count += mgPlayerObjTbl[i]->work[0] != 0;
                    }
                    if (count >= 3) {
                        MgFlowStatSet(MG_STATE_FINISH);
                    }
                }
                break;
            case MG_STATE_FINISH:
                if (m241_coinSetFTbl[data->unk59] == 0) {
                    rank = 0;
                    for (i = 0; i < 4; i++) {
                        if (i != data->unk59 && m241_outTimeTbl[data->unk59] < m241_outTimeTbl[i]) {
                            rank++;
                        }
                    }
                    GwPlayer[data->unk59].bonusCoin = rank;
                    m241_coinSetFTbl[data->unk59] = 1;
                }
                if (object->work[0] == 0) {
                    data->unk3C *= 0.9f;
                }
                MgPlayerObjMain(object);
                if (object->work[0] == 2) {
                    m241_PlayerFlyUpdate(object);
                }
                break;
            case MG_STATE_RESULT:
                if (MgFlowStatTimeGet() == 0) {
                    if (object->work[0] == 0) {
                        switch (GwPlayer[data->unk59].chr) {
                            case 0:
                            default:
                                character = 2;
                                break;
                            case 1:
                                character = 3;
                                break;
                            case 2:
                                character = 7;
                                break;
                            case 3:
                                character = 4;
                                break;
                            case 4:
                                character = 5;
                                break;
                            case 5:
                                character = 6;
                                break;
                            case 6:
                                character = 8;
                                break;
                            case 7:
                                character = 9;
                                break;
                        }
                        HuAudCharVoicePlay((character << 16) | 0x2F);
                        MgPlayerMotSet(object, 13);
                        m241_resultMode = 0;
                    }
                    if (data->unk59 == 3 && m241_resultMode == -1) {
                        m241_resultMode = 1;
                    }
                    switch (m241_resultMode) {
                        case 0:
                            count = 0;
                            for (i = 0; i < 4; i++) {
                                count += GwPlayer[i].bonusCoin == 0;
                            }
                            if (count == 1) {
                                HuAudSeqPlay(0x65);
                            } else {
                                HuAudSeqPlay(0x66);
                            }
                            break;
                        case 1:
                            for (i = 0; i < 3; i++) {
                                if (m241_outTimeTbl[i] != m241_outTimeTbl[i + 1]) {
                                    break;
                                }
                            }
                            if (i == 3) {
                                for (i = 0; i < 4; i++) {
                                    GwPlayer[i].bonusCoin = 3;
                                }
                            }
                            HuAudSeqPlay(0x6C);
                            m241_resultMode = 1;
                            break;
                    }
                } else if ((m241_resultMode == 0 && MgFlowStatTimeGet() >= 100) ||
                           (m241_resultMode == 1 && MgFlowStatTimeGet() > 144)) {
                    MgFlowStatSet(MG_STATE_EXIT);
                }
                MgPlayerObjMain(object);
                break;
            default:
                MgPlayerObjMain(object);
                if (object->work[0] == 2) {
                    m241_PlayerFlyUpdate(object);
                }
                break;
        }
        object->scale.x = object->scale.z = 1.2f;
        if (!(data->unk50 & 6)) {
            object->scale.y = 1.2f;
        }
    }
}

void m241_PlayerIntroUpdate(omObjData *object) {
    MgPlayerWork *data = object->data;

    if (MgFlowStatTimeGet() == 20) {
        data->unk3C = atan2df(object->trans.x, object->trans.z);
    } else if (MgFlowStatTimeGet() > 20) {
        if (HuSqrtf(object->trans.x * object->trans.x + object->trans.z * object->trans.z) < 500.0f) {
            object->trans.x += sindf(data->unk3C) * 10.0f;
            object->trans.z += cosdf(data->unk3C) * 10.0f;
            MgPlayerMotSet(object, 2);
        } else {
            data->unk3C = atan2df(-object->trans.x, -object->trans.z);
            MgPlayerMotSet(object, 0);
        }
        MgPlayerMotUpdate(object);
    }
    HuRotateRPYF(Hu3DData[object->model[0]].mtx, 0.0f, data->unk3C, 0.0f);
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
}

void m241_PlayerFlyUpdate(omObjData *object) {
    AllFiredUpPlayerWork *work;

    m241_SmokeUpdate(object);
    if (object->trans.x > 0.0f) {
        object->trans.x += 28.0f;
    } else {
        object->trans.x -= 28.0f;
    }
    if (object->trans.z > 0.0f) {
        object->trans.z -= 28.0f;
    } else {
        object->trans.z += 28.0f;
    }
    if (ABS(object->trans.x) > 700.0f) {
        MgPlayerMapAttrSet(object, 0, 1);
        Hu3DModelAttrSet(object->model[1], 4, 4);
        if (object->trans.y < -2000.0f) {
            object->work[0] = 3;
        }
    }
    work = ((MgPlayerWork *)object->data)->unk158;
    if (work->unk04 < 270.0f) {
        object->trans.y = sindf(work->unk04) * 400.0f;
        work->unk04 += 6.0f;
    } else {
        object->trans.y -= 50.0f;
    }
    work->unk00 = 1.0f - sindf(work->unk04) * 0.8f;
    Hu3DModelScaleSet(object->model[1], work->unk00, work->unk00, work->unk00);
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
}

void m241_SmokeUpdate(omObjData *object) {
    s32 player = ((MgPlayerWork *)object->data)->unk59;
    f32 scale;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (m241_smokeTimerTbl[player][i] >= 0) {
            if (m241_smokeTimerTbl[player][i] == 0) {
                Hu3DModelPosSet(m241_smokeMdlTbl[i], object->trans.x, object->trans.y, object->trans.z);
                Hu3DModelAttrSet(m241_smokeMdlTbl[i], 4, 0);
            }
            if (m241_smokeTimerTbl[player][i] < 8) {
                scale = m241_smokeScaleTbl[m241_smokeTimerTbl[player][i] / 2];
                Hu3DModelScaleSet(m241_smokeMdlTbl[i], scale, scale, 1.0f);
            }
            if (m241_smokeTimerTbl[player][i] >= 8) {
                m241_smokeTimerTbl[player][i] = -1;
            }
        }
        m241_smokeTimerTbl[player][i]++;
    }
}

void m241_PlayerComInput(omObjData *object) {
    MgPlayerWork *data;
    AllFiredUpPlayerWork *work;
    omObjData *fire;
    f32 nearX;
    f32 nearZ;
    f32 minDist;
    f32 len;
    f32 dist;
    f32 dx;
    f32 dz;
    f32 sinAngle;
    f32 cosAngle;
    f32 range;
    f32 x;
    f32 z;
    s32 tries;
    u16 stick;
    s8 blocked;
    s8 jump;
    s32 i;

    nearX = nearZ = 0.0f;
    blocked = 0;
    jump = 0;
    if (object->work[0] != 0) {
        return;
    }
    data = object->data;
    work = data->unk158;
    switch (GwPlayer[data->unk59].cpu_difficulty) {
        case 3:
            stick = 60;
            break;
        case 2:
            stick = 57;
            break;
        case 1:
        default:
            stick = 54;
            break;
        case 0:
            stick = 51;
            break;
    }
    if (work->unk08 == 0) {
        work->unk0C = (rand8() & 0xF) * 360 / 16;
        work->unk08++;
    } else {
        work->unk08++;
        if (work->unk08 >= 15) {
            work->unk08 = 0;
        }
    }
    minDist = 1400.0f * 1400.0f;
    for (i = 0; i < m241_fireNum; i++) {
        fire = m241_fireObjTbl[i];
        dx = fire->trans.x - object->trans.x;
        dz = fire->trans.z - object->trans.z;
        len = dx * dx + dz * dz;
        if (len < minDist) {
            nearX = fire->trans.x;
            nearZ = fire->trans.z;
            minDist = len;
        }
    }
    dist = HuSqrtf(object->trans.x * object->trans.x + object->trans.z * object->trans.z);
    tries = 0;
    do {
        if (work->unk0C >= 360.0f) {
            work->unk0C -= 360.0f;
        }
        sinAngle = sindf(work->unk0C);
        cosAngle = cosdf(work->unk0C);
        for (i = 0; i < m241_fireNum; i++) {
            fire = m241_fireObjTbl[i];
            blocked = 0;
            if (m241_patternType == 0 && m241_firePhase == 3) {
                if (m241_patternDirF != 0) {
                    if (ABS(m241_ringRadius - dist) < 120.0f) {
                        jump = 1;
                    }
                } else {
                    if (ABS(m241_ringRadius - dist) < 140.0f) {
                        jump = 1;
                    }
                }
            } else {
                if (m241_firePhase == 2) {
                    range = 250.0f;
                } else if (m241_firePhase == 1) {
                    range = 200.0f;
                } else {
                    range = 100.0f;
                    if (m241_firePhase == 3) {
                        range = 150.0f;
                    }
                }
                dx = fire->trans.x - object->trans.x;
                dz = fire->trans.z - object->trans.z;
                if (HuSqrtf(dx * dx + dz * dz) < range) {
                    if (jump == 1) {
                        if (fire->trans.y > 0.0f) {
                            jump = 0;
                        }
                    } else if (fire->trans.y == 0.0f) {
                        jump = 1;
                    }
                }
            }
            if (m241_firePhase == 3) {
                range = 400.0f;
            } else {
                range = 200.0f;
                if (m241_firePhase == 2) {
                    range = 400.0f;
                }
            }
            x = object->trans.x + sinAngle * range;
            z = object->trans.z + cosAngle * range;
            dx = fire->trans.x - x;
            dz = fire->trans.z - z;
            if (HuSqrtf(dx * dx + dz * dz) < range) {
                blocked = 1;
                break;
            }
        }
        if (blocked == 0) {
            x = object->trans.x + sinAngle * 50.0f;
            z = object->trans.z + cosAngle * 50.0f;
            if (!(x * x + z * z > 700.0f * 700.0f)) {
                break;
            }
        }
        tries++;
        work->unk0C += 0.022222222222222223;
    } while (tries < 8);
    len = HuSqrtf(object->trans.x * object->trans.x + object->trans.x * object->trans.x);
    if (m241_firePhase == 1) {
        if (m241_firePhaseTimer < 21) {
            work->unk0C = atan2df(object->trans.x, object->trans.z);
        } else {
            work->unk0C = atan2df(object->trans.x - nearX, object->trans.z - nearZ);
        }
    } else if (m241_patternType == 0 && m241_firePhase == 3) {
        if (m241_patternDirF != 0) {
            if (m241_ringRadius > 350.0f) {
                if (ABS(object->trans.x) < 150.0f && ABS(object->trans.z) < 150.0f) {
                    stick = 0;
                    data->unk3C = atan2df(object->trans.x, object->trans.z);
                } else {
                    data->unk3C = work->unk0C = atan2df(-object->trans.x, -object->trans.z);
                }
            } else {
                data->unk3C = work->unk0C = atan2df(object->trans.x, object->trans.z);
            }
        } else if (m241_ringRadius < 350.0f) {
            data->unk3C = work->unk0C = atan2df(object->trans.x, object->trans.z);
        } else if (ABS(object->trans.x) < 150.0f && ABS(object->trans.z) < 150.0f) {
            stick = 0;
            data->unk3C = atan2df(object->trans.x, object->trans.z);
        } else {
            data->unk3C = work->unk0C = atan2df(-object->trans.x, -object->trans.z);
        }
    } else if (m241_firePhase == 2) {
        if (m241_patternType == 1 || m241_patternType == 2) {
            if (ABS(object->trans.z) < 200.0f) {
                if (object->trans.z < 0.0f) {
                    work->unk0C = 180.0f;
                } else {
                    work->unk0C = 0.0f;
                }
            } else if (ABS(object->trans.x) < 200.0f) {
                if (object->trans.x < 0.0f) {
                    work->unk0C = 270.0f;
                } else {
                    work->unk0C = 90.0f;
                }
            } else {
                work->unk0C = atan2df(object->trans.x - nearX, object->trans.z - nearZ);
            }
        }
    } else if (m241_firePhase == 3) {
        if (m241_patternType == 1 || m241_patternType == 2) {
            m241_ComCircleAngleSet(object, len, jump);
            if (mgPlayerSpeedMin <= data->unk40) {
                x = object->trans.x + sindf(data->unk3C) * 200.0f - nearX;
                z = object->trans.z + cosdf(data->unk3C) * 200.0f - nearZ;
                if (x * x + z * z < 200.0f * 200.0f) {
                    stick = 0;
                }
            }
        }
    } else {
        if (blocked == 1) {
            work->unk0C = atan2df(object->trans.x - nearX, object->trans.z - nearZ);
        }
        stick *= 0.8f;
    }
    HuPadStkX[data->unk57] = sindf(work->unk0C) * stick;
    HuPadStkY[data->unk57] = -cosdf(work->unk0C) * stick;
    if (jump == 1) {
        HuPadBtnDown[data->unk57] |= 0x8000;
    } else {
        HuPadBtnDown[data->unk57] &= 0x7FFF;
    }
}

void m241_ComCircleAngleSet(omObjData *object, f32 dist, s8 arg2) {
    AllFiredUpPlayerWork *work = ((MgPlayerWork *)object->data)->unk158;

    if (m241_patternDirF != 0) {
        if (arg2 == 0) {
            if (dist > 600.0f) {
                work->unk0C = atan2df(-object->trans.x, -object->trans.z) - 60.0f;
            } else {
                work->unk0C = atan2df(-object->trans.x, -object->trans.z) - 90.0f;
            }
        } else {
            work->unk0C = atan2df(-object->trans.x, -object->trans.z) + 90.0f;
        }
    } else if (arg2 != 0) {
        work->unk0C = atan2df(-object->trans.x, -object->trans.z) - 90.0f;
    } else if (dist > 600.0f) {
        work->unk0C = atan2df(-object->trans.x, -object->trans.z) + 60.0f;
    } else {
        work->unk0C = atan2df(-object->trans.x, -object->trans.z) + 90.0f;
    }
}

void m241_MapObjInit(omObjData *object) {
    MgMapWork *work;
    u16 sprite1;
    s16 group1;
    u16 sprite2;
    s16 group2;

    object->func = NULL;
    sprite1 = HuSprAnimDataRead(0x4A0001);
    group1 = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(group1, 0, sprite1, 0);
    HuSprAttrReset(group1, 0, 0xFFFF);
    HuSprAttrSet(group1, 0, 0x5000);
    HuSprPosSet(group1, 0, 160, 120);
    sprite2 = HuSprAnimDataRead(0x4A0002);
    group2 = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(group2, 0, sprite2, 0);
    HuSprAttrReset(group2, 0, 0xFFFF);
    HuSprAttrSet(group2, 0, 0x1000);
    HuSprPosSet(group2, 0, 160, 180);
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    object->model[0] = Hu3DModelRead2(0x4A0000, 0x29D);
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 0;
    work->unk08 = 0.5f;
}
