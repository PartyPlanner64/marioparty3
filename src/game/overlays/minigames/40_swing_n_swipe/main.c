#include "common.h"
#include "game/overlays/minigame.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "game/pause.h"
#include "game/wipe.h"

typedef struct SwingNSwipeGroupOrder {
    s16 order[4];
} SwingNSwipeGroupOrder;

typedef struct SwingNSwipeCpuOffsets {
    s16 offsets[4];
} SwingNSwipeCpuOffsets;

typedef struct SwingNSwipeCpuSpeeds {
    f32 speeds[4];
} SwingNSwipeCpuSpeeds;

typedef struct SwingNSwipeCarrierWork {
    /* 0x00 */ s16 unk00; // m264_carrierPhase
    /* 0x02 */ s16 unk02[5]; // m264_carrierMotNoTbl
} SwingNSwipeCarrierWork; // sizeof 0xC

extern u16 mgInstColumnTbl[];
extern s32 omCharModelNoTbl[][6];
extern u16 mgInstSlotTbl[];
extern s16 m264_carrierPhase; // m264_carrierWork.unk00
extern s16 m264_carrierMotNoTbl[5]; // m264_carrierWork.unk02
f32 m264_areaMinX = -400.0f; // min x
f32 m264_areaMinZ = -275.0f; // min z
f32 m264_areaMaxX = 400.0f; // max x
f32 m264_areaMaxZ = 600.0f; // max z
s16 m264_phase = 0; // state
s16 m264_phaseTimer = 0; // timer
s16 m264_introPhase = 0;
s16 m264_introTimer = 0;
s16 m264_timer = 301;
s16 m264_resultPhase = 0;
s16 m264_resultTimer = 0;
s16 m264_playerActPhase = 0;
s16 m264_playerActTimer = 0;
s16 m264_playerReturnTime = 0;
s16 m264_playerJumpF = 0;
f32 m264_playerJumpVel = -1.47f;
s16 m264_swingF = 0;
f32 m264_comAimTimer = 99.0f;
s16 m264_swingTimer = 0;
Vec2f m264_stickHistTbl[10] = { 0 };
s16 m264_stickHistNo = 0;
s16 m264_swingSeF = 0;
s16 m264_carrierMotNoPrevTbl[5] = { 999, 999, 999, 999, 999 };
s16 m264_carrierEnterPhaseTbl[5] = { 0 };
s16 m264_carrierEnterTimerTbl[5] = { 0 };
s16 m264_carrierRunPhaseTbl[5] = { 0 };
Vec2f m264_carrierRunVelTbl[5] = { 0 };
s16 m264_carrierFleePhaseTbl[5] = { 0 };
s16 m264_carrierFleeTimerTbl[5] = { 1, 1, 1, 1, 1 };
f32 m264_carrierFleeVelY = 0.0f;
f32 m264_carrierFleeRotY = 0.0f;
s16 m264_carrierGatherPhaseTbl[5] = { 0 };
s16 m264_carrierGatherTimerTbl[5] = { 1, 1, 1, 1, 1 };
s16 m264_carrierGatherRankTbl[5] = { 0 };

Vec m264_boxPosTbl[5] = {
    { 0.0f, 0.0f, -150.0f },
    { -190.0f, 0.0f, 100.0f },
    { -370.0f, 0.0f, 325.0f },
    { 190.0f, 0.0f, 100.0f },
    { 370.0f, 0.0f, 325.0f },
};

s32 m264_itemSprFileTbl[] = {
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

s16 m264_boxShowPhase = 0;
s16 m264_boxShowTimer = 0;
s16 m264_prizePhase = 0;
s16 m264_prizeTimer = 0;
s32 m264_unusedNum = 0; /* Unreferenced. */
SwingNSwipeGroupOrder m264_playerNoTbl = { { 0, 1, 2, 3 } };
SwingNSwipeCpuOffsets m264_comAimWaitTbl = { { 45, 30, 15, 5 } };
SwingNSwipeCpuSpeeds m264_comSpeedTbl = { { 10.0f, 11.0f, 12.0f, 13.0f } };

f32 m264_playerPrevX BSS;
f32 m264_playerPrevZ BSS;
Vec m264_playerReturnPos BSS;
f32 m264_swingPosX BSS;
f32 m264_swingPosZ BSS;
f32 m264_swingDistX BSS;
f32 m264_swingDistZ BSS;
f32 m264_comDirX BSS;
f32 m264_comDirZ BSS;
f32 m264_comAngle BSS;
Vec m264_carrierFleePosTbl[5] BSS;
u8 m264_carrierFleePosTblPad[4] BSS; /* Unreferenced. */
Vec m264_carrierGatherPosTbl[5] BSS;
s16 m264_missF BSS;
omObjData *m264_playerObj BSS;
s16 m264_playerNo BSS;
s16 m264_playerActNo BSS;
SwingNSwipeCarrierWork m264_carrierWork BSS;
s16 m264_boxState BSS;
s16 m264_smokeState BSS;
s16 m264_prizeSmokeState BSS;
s16 m264_playerEffState BSS;
s16 m264_hitEffState BSS;
s16 m264_hitCarrierNo BSS;
s16 m264_comTargetNo BSS;
s16 m264_comAimWait BSS;
s16 m264_comSpeed BSS;
s16 m264_batMdl BSS;
s16 m264_walkSeF BSS;
s16 m264_walkSeFPad BSS; /* Unreferenced. */
u8 m264_walkSeFPadB[4] BSS; /* Unreferenced. */
s16 m264_carrierMdlTbl[5][2] BSS;
s16 m264_carrierMotTbl[5] BSS;
s16 m264_boxMdlTbl[5][4] BSS;
s16 m264_prizeEffTbl[4] BSS;
s16 m264_smokeMdlTbl[5] BSS;
s16 m264_effMdlTbl[2] BSS;
s16 m264_effMotTbl[3] BSS;

void m264_ObjectSetup(void);
void m264_MainObjInit(omObjData *object);
void m264_ComInit(void);
void m264_MainObjMain(omObjData *object);
void m264_IntroObjMain(omObjData *object);
void m264_PlayObjMain(omObjData *object);
void m264_ResultObjMain(omObjData *object);
void m264_PlayerObjInit(omObjData *object);
void m264_PlayerObjMain(omObjData *object);
void m264_PlayerActUpdate(void);
void m264_PlayerInputUpdate(void);
void m264_CarrierObjInit(omObjData *object);
void m264_CarrierObjMain(omObjData *object);
void m264_CarrierEnterUpdate(void);
void m264_BoxObjInit(omObjData *object);
void m264_BoxObjMain(omObjData *object);
void m264_EffObjInit(omObjData *object);
void m264_EffObjMain(omObjData *object);
void m264_CarrierRunUpdate(void);
void m264_CarrierFleeUpdate(void);
void m264_CarrierGatherUpdate(void);
void m264_BoxShowUpdate(void);
void m264_BoxCarryUpdate(void);
void m264_BoxDropUpdate(void);
void m264_PrizeUpdate(void);
s16 m264_EspCreate(s32 dataNum, u16 attr, u16 pri, s16 x, s16 y);
s16 m264_MotMdlRead(s32 arg0);
s16 m264_PlayerHitCheck(void);
s16 m264_CarrierPlayerHitCheck(s16 index);
s16 m264_CarrierHitCheck(s16 index);
void m264_ExitStartObjMain(omObjData *object);
void m264_ExitObjMain(omObjData *object);
void m264_ExitCheckObjMain(omObjData *object);

void m264_Executor(void) {
    m264_ObjectSetup();
}

void m264_ObjectSetup(void) {
    SwingNSwipeGroupOrder groupOrder = m264_playerNoTbl;
    omObjData *obj;
    s32 camIndex;
    s16 i;

    MapCollInit(0x40);
    Hu3DSprModelInit(0x40);
    omInitObjMan(0x40, 0x40);
    omGameSysInit();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(camIndex, 30.0f, 80.0f, 8000.0f);
    CZoom = 1800.0f;
    CRot.x = -15.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 174.5f;
    Center.z = 150.0f;
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    if (i < 4) {
        m264_playerNo = groupOrder.order[i];
    } else {
        m264_playerNo = groupOrder.order[0];
    }
    omAddObj(1000, 0, 0, -1, m264_MainObjInit);
    omAddObj(2000, 0, 0, -1, m264_ExitCheckObjMain);
}

void m264_MainObjInit(omObjData *object) {
    m264_ComInit();
    m264_EspCreate(0x610000, 0x4000, 10, 160, 120);
    m264_playerObj = omAddObj(10, 20, 20, -1, m264_PlayerObjInit);
    omAddObj(20, 20, 20, -1, m264_CarrierObjInit);
    omAddObj(30, 20, 20, -1, m264_BoxObjInit);
    omAddObj(40, 20, 20, -1, m264_EffObjInit);
    object->func = m264_MainObjMain;
}

void m264_ComInit(void) {
    s16 thresholds[5];
    SwingNSwipeCpuOffsets offsets = m264_comAimWaitTbl;
    SwingNSwipeCpuSpeeds speeds = m264_comSpeedTbl;
    s16 i;
    s16 roll;

    m264_missF = 1;
    GwPlayer[m264_playerNo].bonusCoin = -1;
    if (GwPlayer[m264_playerNo].stat & 1) {
        thresholds[0] = mgInstSlotTbl[0];
        for (i = 1; i < 5; i++) {
            thresholds[i] = thresholds[i - 1] + mgInstSlotTbl[i];
        }
        roll = (u8)(rand8() % 100);
        for (i = 0; i < 5; i++) {
            if (roll < thresholds[i]) {
                break;
            }
        }
        if (i <= 0) {
            i = 0;
        }
        if (i >= 4) {
            i = 4;
        }
        m264_comTargetNo = i;
        m264_comAimWait = offsets.offsets[GwPlayer[m264_playerNo].cpu_difficulty];
        m264_comSpeed = speeds.speeds[GwPlayer[m264_playerNo].cpu_difficulty];
    }
}

void m264_MainObjMain(omObjData *object) {
    switch (m264_phase) {
        case 0:
            WipeCreateIn(WIPE_TYPE_PREV, 16);
            m264_phase++;
            break;
        case 1:
            object->func = m264_IntroObjMain;
            m264_phase++;
            break;
        case 2:
            if (++m264_phaseTimer == 1) {
                GMesCreate(GMES_MES_8);
            } else if (GMesStatGet() == 0) {
                m264_phaseTimer = 0;
                m264_phase++;
            }
            break;
        case 3:
            object->func = m264_PlayObjMain;
            m264_phase++;
            break;
        case 4:
            if (++m264_phaseTimer == 1) {
                GMesCreate(GMES_MES_19);
                HuAudSeqFadeOut(120);
            } else if (GMesStatGet() == 0) {
                m264_phaseTimer = 0;
                m264_phase++;
            }
            break;
        case 5:
            object->func = m264_ResultObjMain;
            m264_phase++;
            break;
        case 6:
            if (++m264_phaseTimer == 1) {
                switch (m264_missF) {
                    case 0:
                        HuAudSeqPlay(0x68);
                        GMesTimeMaxSet(GMesCreate(GMES_MES_36), 120);
                        GwPlayer[m264_playerNo].bonusCoin = mgInstColumnTbl[m264_hitCarrierNo];
                        break;
                    case 1:
                        HuAudSeqPlay(0x6B);
                        GMesTimeMaxSet(GMesCreate(GMES_MES_29), 120);
                        GwPlayer[m264_playerNo].bonusCoin = -1;
                        break;
                }
            } else if (m264_phaseTimer >= 135) {
                m264_phaseTimer = 0;
                m264_phase++;
            }
            break;
        case 7:
            object->func = m264_ExitStartObjMain;
            break;
    }
    m264_CarrierFleeUpdate();
    m264_CarrierGatherUpdate();
    m264_BoxDropUpdate();
    m264_PrizeUpdate();
}

void m264_IntroObjMain(omObjData *object) {
    switch (m264_introPhase) {
        case 0:
            if (WipeStatGet() == 1) {
                return;
            }
            HuAudSeqPlay(0x44);
            m264_introPhase++;
            break;
        case 1:
            m264_boxState = 1;
            if (m264_introTimer++ >= 30) {
                m264_introTimer = 0;
                m264_introPhase++;
            }
            break;
        case 2:
            m264_carrierPhase = 1;
            m264_introPhase++;
            break;
        case 3:
            if (m264_introTimer++ >= 60) {
                m264_introTimer = 0;
                m264_introPhase++;
            }
            break;
        case 4:
            m264_playerActNo = 1;
            m264_introPhase++;
            break;
        case 5:
            if (m264_playerActNo == 0) {
                object->func = m264_MainObjMain;
            }
            break;
    }
    m264_PlayerActUpdate();
    m264_CarrierEnterUpdate();
    m264_BoxShowUpdate();
}

void m264_PlayObjMain(omObjData *object) {
    s16 i;

    if (--m264_timer == 300) {
        m264_carrierPhase = 2;
        GMesCreate(GMES_MES_TIMER, 10, 160, 56);
    } else if (m264_timer >= 0) {
        GMesTimerValueSet((m264_timer + 29) / 30);
        m264_PlayerInputUpdate();
        m264_CarrierRunUpdate();
    } else {
        m264_missF = 1;
        GMesTimerEnd();
        m264_smokeState = 1;
        m264_playerEffState = 1;
        m264_playerActNo = 0;
        m264_carrierPhase = 0;
        Hu3DData[m264_playerObj->model[0]].motIdShape = 0xFF;
        MgPlayerMotSet(m264_playerObj, 0);
        for (i = 0; i < 5; i++) {
            m264_carrierMotNoTbl[i] = 0;
        }
        object->func = m264_MainObjMain;
    }
    if (m264_missF == 0) {
        m264_missF = 0;
        GMesTimerEnd();
        m264_smokeState = 1;
        m264_playerActNo = 0;
        m264_carrierPhase = 4;
        for (i = 0; i < 5; i++) {
            m264_carrierMotNoTbl[i] = 0;
        }
        object->func = m264_MainObjMain;
    }
    m264_CarrierFleeUpdate();
    m264_CarrierGatherUpdate();
    m264_BoxCarryUpdate();
}

void m264_ResultObjMain(omObjData *object) {
    s16 i;

    switch (m264_resultPhase) {
        case 0:
            if (m264_missF == 0) {
                m264_boxState = 4;
            } else if (m264_missF == 1) {
                m264_playerActNo = 3;
                m264_carrierPhase = 3;
            }
            m264_resultPhase++;
            break;
        case 1:
            if (m264_resultTimer++ >= 90) {
                m264_resultPhase++;
            }
            break;
        case 2:
            if (m264_missF == 0) {
                MgPlayerMotSet(m264_playerObj, 6);
                HuAudCharVoicePlay(omCharModelNoTbl[GwPlayer[m264_playerNo].chr][0] | 0x35);
            } else if (m264_missF == 1) {
                HuAudFXPlay(0x4F6);
                MgPlayerMotSet(m264_playerObj, 7);
                HuAudCharVoicePlay(omCharModelNoTbl[GwPlayer[m264_playerNo].chr][0] | 0x38);
                for (i = 0; i < 5; i++) {
                    m264_carrierMotNoTbl[i] = 4;
                }
            }
            object->func = m264_MainObjMain;
            break;
    }
    m264_PlayerActUpdate();
    m264_CarrierFleeUpdate();
    m264_CarrierGatherUpdate();
    m264_PrizeUpdate();
}

void m264_ExitStartObjMain(omObjData *object) {
    WipeCreateOut(WIPE_TYPE_NORMAL, 16);
    HuAudSeqFadeOut(30);
    HuAudFXAllFadeOut(30);
    object->func = m264_ExitObjMain;
}

void m264_ExitObjMain(omObjData *object) {
    if (WipeStatGet() != 1) {
        osViBlack(FALSE);
        omOvlReturnEx(1);
    }
}

void m264_ExitCheckObjMain(omObjData *object) {
    if (omSysExitReq == 1) {
        object->func = m264_ExitStartObjMain;
    }
}

void m264_PlayerObjInit(omObjData *object) {
    s32 chr;
    s32 model;
    s32 motion;

    MgPlayerParamReset();
    chr = GwPlayer[m264_playerNo].chr;
    model = omCharModelNoTbl[chr][0];
    motion = omCharModelNoTbl[chr][1];
    MgPlayerCreate(object, model, motion, m264_playerNo, 0x2B9, 0x2B9);
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(chr, 0), 1, 0);
    MgPlayerMotLoad(object, 1, CharMotionDataNumGet(chr, 1), 1, 0);
    MgPlayerMotLoad(object, 2, CharMotionDataNumGet(chr, 2), 1, 0);
    MgPlayerMotLoad(object, 4, CharMotionDataNumGet(chr, 0x18), 1, 0);
    MgPlayerMotLoad(object, 3, CharMotionDataNumGet(chr, 4), 0, 0);
    MgPlayerMotLoad(object, 5, CharMotionDataNumGet(chr, 0x91), 0, 0);
    MgPlayerMotLoad(object, 6, CharMotionDataNumGet(chr, 0x35), 0, 0);
    MgPlayerMotLoad(object, 7, CharMotionDataNumGet(chr, 0x38), 0, 0);
    MgPlayerMotSet(object, 4);
    omSetTra(object, 0.0f, 0.0f, 1500.0f);
    object->model[1] = Hu3DModelRead(9, 0x2B9);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelScaleSet(object->model[1], 1.5f, 1.0f, 1.5f);
    m264_batMdl = Hu3DModelRead(0x610002, 0x2B9);
    Hu3DModelAttrSet(m264_batMdl, 0x4000, 0x4000);
    Hu3DModelHookSet(m264_batMdl, object->model[0], "item_hook");
    object->func = m264_PlayerObjMain;
}

void m264_PlayerObjMain(omObjData *object) {
    f32 scale = 1.5f - object->trans.y * 0.003f;

    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[1], scale, 1.0f, scale);
    if (m264_walkSeF == 1 && Hu3DData[object->model[0]].motTime == 0.0f) {
        CharFXPlay(0x1F, GwPlayer[m264_playerNo].chr);
    }
    MgPlayerMotUpdate(object);
}

void m264_PlayerActUpdate(void) {
    omObjData *obj = m264_playerObj;

    if (m264_playerActNo == 0) {
        m264_playerReturnTime = 0;
        m264_playerActTimer = 0;
        m264_playerActPhase = 0;
    }
    if (m264_playerActNo == 1) {
        switch (m264_playerActPhase) {
            case 0:
                obj->trans.z = 1500.0f;
                obj->rot.y = 180.0f;
                Hu3DMotionShapeSet(obj->model[0], obj->motion[4], 0);
                MgPlayerMotSet(obj, 1);
                m264_playerActPhase++;
                break;
            case 1:
                m264_walkSeF = 1;
                obj->trans.z -= 13.5f;
                if (obj->trans.z <= 550.0f) {
                    obj->trans.z = 550.0f;
                    m264_playerActPhase++;
                }
                break;
            case 2:
                obj->rot.y -= 13.5f;
                if (obj->rot.y <= 0.0f) {
                    obj->rot.y = 0.0f;
                    m264_playerActPhase++;
                }
                break;
            case 3:
                m264_walkSeF = 0;
                Hu3DMotionShapeSet(obj->model[0], obj->motion[4], 0);
                MgPlayerMotSet(obj, 0);
                m264_playerActPhase++;
                break;
            case 4:
                if (m264_playerActTimer++ >= 10) {
                    m264_playerActTimer = 0;
                    m264_playerActPhase++;
                }
                break;
            case 5:
            case 8:
                HuAudFXPlay(0x4F8);
                Hu3DMotionShapeSet(obj->model[0], obj->motion[5], 0);
                MgPlayerMotSet(obj, 5);
                m264_playerActPhase++;
                break;
            case 6:
            case 9:
                if (m264_playerActTimer++ >= 10) {
                    m264_playerActTimer = 0;
                    m264_playerActPhase++;
                }
                break;
            case 7:
            case 10:
                if (Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 == Hu3DData[obj->model[0]].motTime) {
                    m264_playerActPhase++;
                }
                break;
            case 11:
                Hu3DMotionShapeSet(obj->model[0], obj->motion[4], 0);
                MgPlayerMotSet(obj, 0);
                m264_playerActTimer = 0;
                m264_playerActPhase = 0;
                m264_playerActNo = 0;
                break;
        }
    }
    if (m264_playerActNo == 3) {
        switch (m264_playerActPhase) {
            case 0:
                m264_playerReturnPos.x = obj->trans.x;
                m264_playerReturnPos.z = obj->trans.z;
                m264_playerReturnTime = 1;
                m264_playerJumpVel = -1.47f;
                Hu3DData[obj->model[0]].motIdShape = 0xFF;
                MgPlayerMotSet(obj, 1);
                m264_playerActPhase++;
                break;
            case 1:
                if (m264_playerJumpF == 0) {
                    m264_walkSeF = 1;
                    if (m264_PlayerHitCheck() == 1) {
                        m264_playerJumpF = 1;
                        MgPlayerMotSet(obj, 3);
                        CharFXPlay(0x3A, GwPlayer[m264_playerNo].chr);
                        m264_walkSeF = 0;
                        break;
                    }
                }
                if (m264_playerJumpF == 1) {
                    obj->trans.y += m264_playerJumpVel * m264_playerJumpVel *
                                    ((m264_playerJumpVel >= 0.0f) ? -17.0f : 17.0f);
                    if (m264_playerJumpVel >= 1.7f) {
                        m264_playerJumpVel = 1.7f;
                    } else {
                        m264_playerJumpVel += 0.11f;
                    }
                    if (m264_playerJumpVel >= 0.0f && obj->trans.y < 0.0f) {
                        obj->trans.y = 0.0f;
                        m264_playerJumpVel = -1.47f;
                        m264_walkSeF = 1;
                        m264_playerJumpF = 0;
                        CharFXPlay(0x31, GwPlayer[m264_playerNo].chr);
                        MgPlayerMotSet(obj, 1);
                    }
                }
                m264_playerPrevX = obj->trans.x;
                m264_playerPrevZ = obj->trans.z;
                obj->trans.x = m264_playerReturnPos.x - sindf(m264_playerReturnTime * 1.5f) * m264_playerReturnPos.x;
                obj->trans.z = m264_playerReturnPos.z - sindf(m264_playerReturnTime * 1.5f) * (m264_playerReturnPos.z - 400.0f);
                obj->rot.y = -atan2df(m264_playerPrevZ - obj->trans.z, m264_playerPrevX - obj->trans.x) + 270.0f;
                if (sindf(m264_playerReturnTime++ * 1.5f) == 1.0f || (obj->trans.x == 0.0f && obj->trans.z == 350.0f)) {
                    m264_playerActPhase++;
                }
                break;
            case 2:
                if (obj->rot.y >= 360.0f) {
                    obj->rot.y -= 360.0f;
                }
                if (obj->rot.y < 0.0f) {
                    obj->rot.y += 360.0f;
                }
                if (obj->rot.y >= 180.0f) {
                    obj->rot.y += 15.0f;
                    if (obj->rot.y >= 360.0f) {
                        obj->rot.y = 0;
                        m264_playerActPhase++;
                    }
                } else if (obj->rot.y > 0.0f) {
                    obj->rot.y -= 15.0f;
                    if (obj->rot.y <= 0.0f) {
                        obj->rot.y = 0.0f;
                        m264_playerActPhase++;
                    }
                } else if (obj->rot.y == 0.0f) {
                    m264_playerActPhase++;
                }
                break;
            case 3:
                m264_walkSeF = 0;
                MgPlayerMotSet(obj, 0);
                m264_playerActPhase++;
                break;
        }
    }
}

void m264_PlayerInputUpdate(void) {
    omObjData *obj = m264_playerObj;
    s16 modelId;
    f32 moveZ = 0.0f;
    f32 moveX = moveZ;
    s16 i = 0;
    s16 pad;

    if (!(GwPlayer[m264_playerNo].stat & 1)) {
        pad = GwPlayer[m264_playerNo].pad;
        if ((HuPadBtnDown[pad] & A_BUTTON) && m264_swingF == 0) {
            m264_swingF = 1;
            for (i = 0; i < 10; i++) {
                m264_stickHistTbl[i].x = m264_stickHistTbl[i].y = 0.0f;
            }
            Hu3DMotionShapeSet(obj->model[0], obj->motion[5], 0);
            MgPlayerMotSet(obj, 5);
        }
        if (m264_swingF == 0) {
            m264_stickHistTbl[m264_stickHistNo].x = HuPadStkX[pad];
            m264_stickHistTbl[m264_stickHistNo++].y = HuPadStkY[pad];
            for (i = 0; i < 10; i++) {
                moveX += m264_stickHistTbl[i].x;
                moveZ += m264_stickHistTbl[i].y;
            }
            moveX /= 100.0f;
            moveZ /= 100.0f;
        }
    } else {
        if (m264_swingF == 0) {
            m264_swingPosX = cosdf(obj->rot.y - 90.0f) * 100.0f + obj->trans.x;
            m264_swingPosZ = obj->trans.z - sindf(obj->rot.y - 90.0f) * 100.0f;
            modelId = m264_carrierMdlTbl[m264_comTargetNo][0];
            m264_swingDistX = m264_swingPosX - Hu3DData[modelId].pos.x;
            m264_swingDistZ = m264_swingPosZ - Hu3DData[modelId].pos.z;
            if (HuSqrtf(m264_swingDistX * m264_swingDistX +
                        m264_swingDistZ * m264_swingDistZ) <= 100.0f) {
                m264_swingF = 1;
                for (i = 0; i < 10; i++) {
                    m264_stickHistTbl[i].x = m264_stickHistTbl[i].y = 0.0f;
                }
                Hu3DMotionShapeSet(obj->model[0], obj->motion[5], 0);
                MgPlayerMotSet(obj, 5);
            }
        }
        if (m264_comAimWait <= m264_comAimTimer++ && m264_swingF == 0) {
            m264_comAimTimer = 0.0f;
            m264_comDirX =
                obj->trans.x - Hu3DData[m264_carrierMdlTbl[m264_comTargetNo][0]].pos.x;
            m264_comDirZ =
                obj->trans.z - Hu3DData[m264_carrierMdlTbl[m264_comTargetNo][0]].pos.z;
            m264_comAngle = -atan2df(m264_comDirX, -m264_comDirZ) + 270.0f;
        }
        m264_stickHistTbl[m264_stickHistNo].x =
            (m264_comSpeed / 2) * cosdf(m264_comAngle);
        m264_stickHistTbl[m264_stickHistNo++].y =
            (m264_comSpeed / 2) * sindf(m264_comAngle);
        for (i = 0; i < 10; i++) {
            moveX += m264_stickHistTbl[i].x;
            moveZ += m264_stickHistTbl[i].y;
        }
        moveX /= 10.0f;
        moveZ /= 10.0f;
    }
    if (m264_stickHistNo >= 10) {
        m264_stickHistNo = 0;
    }
    if (m264_swingF == 1) {
        if (m264_swingSeF == 0) {
            HuAudFXPlay(0x4F8);
            m264_swingSeF = 1;
        }
        if (m264_swingTimer >= 7 && Hu3DData[obj->model[0]].motTime == 16.0f) {
            m264_swingTimer = 0;
            m264_swingPosX = cosdf(obj->rot.y - 90.0f) * 100.0f + obj->trans.x;
            m264_swingPosZ = obj->trans.z - sindf(obj->rot.y - 90.0f) * 100.0f;
            for (i = 0; i < 5; i++) {
                modelId = m264_carrierMdlTbl[i][0];
                m264_swingDistX = m264_swingPosX - Hu3DData[modelId].pos.x;
                m264_swingDistZ = m264_swingPosZ - Hu3DData[modelId].pos.z;
                if (HuSqrtf(m264_swingDistX * m264_swingDistX +
                            m264_swingDistZ * m264_swingDistZ) <= 125.0f) {
                    m264_hitCarrierNo = i;
                    m264_carrierPhase = 5;
                    m264_boxState = 3;
                    m264_hitEffState = 1;
                    m264_missF = 0;
                    omVibrate(m264_playerNo, 2, 2, 20);
                    HuAudFXPlay(0x4F4);
                    HuAudFXPlay(0x4F5);
                    break;
                }
            }
        } else {
            m264_swingTimer++;
        }
        if (Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 == Hu3DData[obj->model[0]].motTime &&
            m264_swingTimer >= 7) {
            m264_swingF = 0;
            m264_swingTimer = 0;
            m264_swingSeF = 0;
        }
    } else if (m264_swingF == 0) {
        obj->trans.x += moveX;
        obj->trans.z -= moveZ;
        if (m264_PlayerHitCheck() == 1) {
            obj->trans.x -= moveX;
            obj->trans.z += moveZ;
        }
        if (obj->trans.z > m264_areaMaxZ) {
            obj->trans.z = m264_areaMaxZ;
        } else if (obj->trans.z < m264_areaMinZ) {
            obj->trans.z = m264_areaMinZ;
        }
        if (obj->trans.x > m264_areaMaxX) {
            obj->trans.x = m264_areaMaxX;
        } else if (obj->trans.x < m264_areaMinX) {
            obj->trans.x = m264_areaMinX;
        }
    }
    if (moveX != 0.0f || moveZ != 0.0f) {
        if (m264_swingF == 0) {
            if (Hu3DData[obj->model[0]].motTime == 0.0f) {
                CharFXPlay(0x1F, GwPlayer[m264_playerNo].chr);
            }
            Hu3DMotionShapeSet(obj->model[0], obj->motion[4], 0);
            MgPlayerMotSet(obj, 1);
            obj->rot.y = -atan2df(-moveX, -moveZ);
        }
    } else if (m264_swingF == 0) {
        Hu3DMotionShapeSet(obj->model[0], obj->motion[4], 0);
        MgPlayerMotSet(obj, 0);
    }
}

void m264_CarrierObjInit(omObjData *object) {
    s16 i;

    m264_carrierMdlTbl[0][0] = Hu3DModelRead(0xA0109, 0x2B9);
    m264_carrierMdlTbl[0][1] = Hu3DModelRead(9, 0x2B9);
    for (i = 1; i < 5; i++) {
        m264_carrierMdlTbl[i][0] = Hu3DModelLink(m264_carrierMdlTbl[0][0]);
        m264_carrierMdlTbl[i][1] = Hu3DModelLink(m264_carrierMdlTbl[0][1]);
    }
    for (i = 0; i < 5; i++) {
        Hu3DModelCameraSet(m264_carrierMdlTbl[i][0], HU3D_CAM_NONE);
        Hu3DModelScaleSet(m264_carrierMdlTbl[i][1], 1.5f, 1.0f, 1.5f);
        Hu3DModelCameraSet(m264_carrierMdlTbl[i][1], HU3D_CAM_NONE);
    }
    m264_carrierMotTbl[0] = m264_MotMdlRead(0xA0102);
    m264_carrierMotTbl[1] = m264_MotMdlRead(0xA0103);
    m264_carrierMotTbl[2] = m264_MotMdlRead(0xA010A);
    m264_carrierMotTbl[3] = m264_MotMdlRead(0xA010B);
    m264_carrierMotTbl[4] = m264_MotMdlRead(0xA010C);
    for (i = 0; i < 5; i++) {
        Hu3DMotionShiftSet(m264_carrierMdlTbl[i][0], Hu3DData[m264_carrierMotTbl[0]].motId, 0, 30, 2);
    }
    m264_carrierPhase = 0;
    object->func = m264_CarrierObjMain;
}

void m264_CarrierObjMain(omObjData *object) {
    f32 scale;
    s16 i;

    for (i = 0; i < 5; i++) {
        if (m264_carrierMotNoPrevTbl[i] != m264_carrierMotNoTbl[i]) {
            m264_carrierMotNoPrevTbl[i] = m264_carrierMotNoTbl[i];
            switch (m264_carrierMotNoPrevTbl[i]) {
                case 0:
                case 1:
                case 3:
                case 4:
                    Hu3DMotionShiftSet(m264_carrierMdlTbl[i][0],
                                       Hu3DData[m264_carrierMotTbl[m264_carrierMotNoPrevTbl[i]]].motId, 0, 30, 2);
                    break;
                case 2:
                    Hu3DMotionModelSet(m264_carrierMdlTbl[i][0],
                                       m264_carrierMotTbl[m264_carrierMotNoPrevTbl[i]]);
                    break;
            }
        }
    }
    for (i = 0; i < 5; i++) {
        scale = 1.5f - Hu3DData[m264_carrierMdlTbl[i][0]].pos.y * 0.00375f;
        if (scale <= 0.0f) {
            scale = 0.0f;
        }
        Hu3DModelPosSet(m264_carrierMdlTbl[i][1], Hu3DData[m264_carrierMdlTbl[i][0]].pos.x, 0.0f,
                        Hu3DData[m264_carrierMdlTbl[i][0]].pos.z);
        Hu3DModelScaleSet(m264_carrierMdlTbl[i][1], scale, 1.0f, scale);
    }
}

void m264_CarrierEnterUpdate(void) {
    Vec startPos[5] = {
        { -575.0f, 0.0f, 600.0f },
        { -625.0f, 0.0f, 800.0f },
        { -675.0f, 0.0f, 1000.0f },
        { 625.0f, 0.0f, 800.0f },
        { 675.0f, 0.0f, 1000.0f },
    };
    Vec endPos[5] = {
        { 0.0f, 0.0f, -250.0f },
        { -190.0f, 0.0f, -50.0f },
        { -370.0f, 0.0f, 200.0f },
        { 190.0f, 0.0f, -50.0f },
        { 370.0f, 0.0f, 200.0f },
    };
    s16 model;
    s16 shadow;
    s16 other;
    f32 x;
    f32 z;
    s16 i;

    if (m264_carrierPhase != 1) {
        return;
    }
    for (i = 0; i < 5; i++) {
        model = m264_carrierMdlTbl[i][0];
        shadow = m264_carrierMdlTbl[i][1];
        other = m264_boxMdlTbl[i][0];
        switch (m264_carrierEnterPhaseTbl[i]) {
            case 0:
                Hu3DModelPosSet(model, startPos[i].x, 0.0f, startPos[i].z);
                Hu3DModelPosSet(shadow, Hu3DData[model].pos.x, 0.0f, Hu3DData[model].pos.z);
                m264_carrierMotNoTbl[i] = 1;
                Hu3DModelCameraSet(model, HU3D_CAM0);
                Hu3DModelCameraSet(shadow, HU3D_CAM0);
                m264_carrierEnterPhaseTbl[i]++;
                break;
            case 1:
                x = Hu3DData[model].pos.x;
                z = Hu3DData[model].pos.z;
                if (i < 3) {
                    Hu3DData[model].pos.x += 2.5f;
                } else {
                    Hu3DData[model].pos.x -= 2.5f;
                }
                Hu3DData[model].pos.z -= 10.0f;
                Hu3DData[model].rot.y = -atan2df(z - Hu3DData[model].pos.z, x - Hu3DData[model].pos.x) + 270.0f;
                if (endPos[i].z >= Hu3DData[model].pos.z) {
                    Hu3DData[model].pos.z = endPos[i].z;
                    m264_carrierEnterPhaseTbl[i]++;
                }
                break;
            case 2:
                if (i < 3) {
                    Hu3DData[model].rot.y -= 6.75f;
                    if (Hu3DData[model].rot.y <= 90.0f) {
                        Hu3DData[model].rot.y = 90.0f;
                        m264_carrierEnterPhaseTbl[i]++;
                    }
                } else {
                    Hu3DData[model].rot.y += 6.75f;
                    if (Hu3DData[model].rot.y >= 270.0f) {
                        Hu3DData[model].rot.y = 270.0f;
                        m264_carrierEnterPhaseTbl[i]++;
                    }
                }
                break;
            case 3:
                x = Hu3DData[model].pos.x;
                z = Hu3DData[model].pos.z;
                if (i < 3) {
                    Hu3DData[model].pos.x += 10.0f;
                } else {
                    Hu3DData[model].pos.x -= 10.0f;
                }
                Hu3DData[model].rot.y = -atan2df(z - Hu3DData[model].pos.z, x - Hu3DData[model].pos.x) + 270.0f;
                if (i < 3) {
                    if (endPos[i].x <= Hu3DData[model].pos.x) {
                        Hu3DData[model].pos.x = endPos[i].x;
                        m264_carrierEnterPhaseTbl[i]++;
                    }
                } else if (endPos[i].x >= Hu3DData[model].pos.x) {
                    Hu3DData[model].pos.x = endPos[i].x;
                    m264_carrierEnterPhaseTbl[i]++;
                }
                break;
            case 4:
                if (i < 3) {
                    Hu3DData[model].rot.y -= 6.75f;
                    if (Hu3DData[model].rot.y <= 0.0f) {
                        Hu3DData[model].rot.y = 0.0f;
                        m264_carrierMotNoTbl[i] = 2;
                        m264_carrierEnterPhaseTbl[i]++;
                    }
                } else {
                    Hu3DData[model].rot.y += 6.75f;
                    if (Hu3DData[model].rot.y >= 360.0f) {
                        Hu3DData[model].rot.y = 0;
                        m264_carrierMotNoTbl[i] = 2;
                        m264_carrierEnterPhaseTbl[i]++;
                    }
                }
                break;
            case 5:
                Hu3DData[other].pos.y = (1.0f - cosdf(m264_carrierEnterTimerTbl[i] * 4.5f)) * 140.0f;
                if (m264_carrierEnterTimerTbl[i] > 10.0f) {
                    Hu3DData[other].pos.z =
                        (endPos[i].z + 100.0f) - sindf((m264_carrierEnterTimerTbl[i] - 10.0f) * 9.0f) * 50.0f;
                }
                if (sindf(m264_carrierEnterTimerTbl[i]++ * 4.5f) == 1.0f) {
                    m264_carrierEnterTimerTbl[i] = 0;
                    m264_carrierEnterPhaseTbl[i]++;
                }
                break;
            case 6:
                if (i == 0) {
                    m264_carrierPhase = 0;
                    m264_boxState = 2;
                }
                break;
        }
    }
}

void m264_CarrierRunUpdate(void) {
    s16 work[5][5];
    f32 x;
    f32 z;
    f32 dx;
    f32 dz;
    s16 model;
    s16 i;

    if (m264_carrierPhase == 2) {
        for (i = 0; i < 5; i++) {
            model = m264_carrierMdlTbl[i][0];
            switch (m264_carrierRunPhaseTbl[i]) {
                case 0:
                    m264_carrierMotNoTbl[i] = 3;
                    work[i][0] = (s16)((u8)(rand8() % 180) + 90.0f) % 360;
                    work[i][1] = rand8() % 2;
                    m264_carrierRunPhaseTbl[i]++;
                    break;
                case 1:
                    if (work[i][1] == 0) {
                        Hu3DData[model].rot.y += 10.0f;
                        if ((u8)(rand8() % 10) == 0) {
                            if (Hu3DData[model].rot.y <= 360.0f) {
                                Hu3DData[model].rot.y -= 360.0f;
                            }
                            m264_carrierRunPhaseTbl[i]++;
                        }
                    } else {
                        Hu3DData[model].rot.y -= 10.0f;
                        if ((u8)(rand8() % 10) == 0) {
                            if (Hu3DData[model].rot.y < 0.0f) {
                                Hu3DData[model].rot.y += 360.0f;
                            }
                            m264_carrierRunPhaseTbl[i]++;
                        }
                    }
                    m264_carrierRunVelTbl[i].x = m264_carrierRunVelTbl[i].y = 0.0f;
                    break;
                case 2:
                    x = Hu3DData[model].pos.x;
                    z = Hu3DData[model].pos.z;
                    dx = cosdf(Hu3DData[model].rot.y + 270.0f) * 10.0f;
                    dz = sindf(Hu3DData[model].rot.y + 270.0f) * 10.0f;
                    Hu3DData[model].pos.x += dx;
                    Hu3DData[model].pos.z -= dz;
                    Hu3DData[model].rot.y = -atan2df(z - Hu3DData[model].pos.z, x - Hu3DData[model].pos.x) + 270.0f;
                    if (m264_CarrierPlayerHitCheck(i) == 1 || m264_CarrierHitCheck(i) == 1) {
                        Hu3DData[model].pos.x -= dx;
                        Hu3DData[model].pos.z += dz;
                        m264_carrierRunPhaseTbl[i]++;
                        work[i][0] = (u8)(rand8() % 180) + 90.0f;
                    } else if (Hu3DData[model].pos.x > m264_areaMaxX) {
                        Hu3DData[model].pos.x = m264_areaMaxX;
                        m264_carrierRunPhaseTbl[i]++;
                        work[i][0] = 270;
                    } else if (Hu3DData[model].pos.x < m264_areaMinX) {
                        Hu3DData[model].pos.x = m264_areaMinX;
                        m264_carrierRunPhaseTbl[i]++;
                        work[i][0] = 90;
                    } else if (Hu3DData[model].pos.z > m264_areaMaxZ) {
                        Hu3DData[model].pos.z = m264_areaMaxZ;
                        m264_carrierRunPhaseTbl[i]++;
                        work[i][0] = 0;
                    } else if (Hu3DData[model].pos.z < m264_areaMinZ) {
                        Hu3DData[model].pos.z = m264_areaMinZ;
                        m264_carrierRunPhaseTbl[i]++;
                        work[i][0] = 180;
                    }
                    break;
                case 3:
                    work[i][0] %= 360;
                    work[i][1] = rand8() % 2;
                    m264_carrierRunPhaseTbl[i] = 1;
                    break;
            }
        }
    }
    for (i = 0; i < 5; i++) {
        model = m264_carrierMdlTbl[i][0];
        if (m264_carrierRunPhaseTbl[i] == 2) {
            if (m264_carrierRunVelTbl[i].y < 0.0f) {
                Hu3DData[model].rot.y += 3.0f;
                m264_carrierRunVelTbl[i].y += 1.0f;
            } else if (m264_carrierRunVelTbl[i].y > 0.0f) {
                Hu3DData[model].rot.y -= 3.0f;
                m264_carrierRunVelTbl[i].y -= 1.0f;
            } else {
                m264_carrierRunVelTbl[i].y = (u8)(rand8() % 80) - 40;
            }
        }
    }
}

void m264_CarrierFleeUpdate(void) {
    omObjData *obj = m264_playerObj;
    f32 x;
    f32 z;
    s16 model;
    s16 shadow;
    s16 i;

    if (m264_carrierPhase == 4) {
        for (i = 0; i < 5; i++) {
            if (i == m264_hitCarrierNo) {
                continue;
            }
            model = m264_carrierMdlTbl[i][0];
            shadow = m264_carrierMdlTbl[i][1];
            switch (m264_carrierFleePhaseTbl[i]) {
                case 0:
                    m264_carrierFleePosTbl[i].x = Hu3DData[model].pos.x;
                    m264_carrierFleePosTbl[i].y = Hu3DData[model].pos.y;
                    m264_carrierMotNoTbl[i] = 1;
                    Hu3DMotionSpeedSet(model, 2.0f);
                    m264_carrierFleeTimerTbl[i] = 1;
                    m264_carrierFleePhaseTbl[i]++;
                    break;
                case 1:
                    x = Hu3DData[model].pos.x;
                    z = Hu3DData[model].pos.z;
                    if (obj->trans.x <= x) {
                        Hu3DData[model].pos.x += 10.0f;
                    } else {
                        Hu3DData[model].pos.x -= 10.0f;
                    }
                    Hu3DData[model].pos.z += 27.0f;
                    Hu3DData[model].rot.y = -atan2df(z - Hu3DData[model].pos.z, x - Hu3DData[model].pos.x) + 270.0f;
                    if (Hu3DData[model].pos.x <= -1200.0f) {
                        m264_carrierFleePhaseTbl[i]++;
                    }
                    break;
                case 2:
                    Hu3DModelCameraSet(model, HU3D_CAM_NONE);
                    Hu3DModelCameraSet(shadow, HU3D_CAM_NONE);
                    m264_carrierFleePhaseTbl[i]++;
                    break;
            }
        }
    }
    if (m264_carrierPhase == 4 || m264_carrierPhase == 5) {
        for (i = 0; i < 5; i++) {
            if (i != m264_hitCarrierNo) {
                continue;
            }
            model = m264_carrierMdlTbl[i][0];
            shadow = m264_carrierMdlTbl[i][1];
            switch (m264_carrierFleePhaseTbl[i]) {
                case 0:
                    m264_carrierFleeRotY = m264_playerObj->rot.y + 270.0f;
                    m264_carrierFleeVelY = -2.0f;
                    Hu3DData[model].rot.y = m264_carrierFleeRotY;
                    m264_carrierMotNoTbl[i] = 3;
                    m264_carrierFleePhaseTbl[i]++;
                    break;
                case 1:
                    Hu3DData[model].pos.x -= cosdf(m264_carrierFleeRotY + 270.0f) * 100.0f;
                    Hu3DData[model].pos.z += sindf(m264_carrierFleeRotY + 270.0f) * 100.0f;
                    Hu3DData[model].pos.y += m264_carrierFleeVelY * m264_carrierFleeVelY *
                                             ((m264_carrierFleeVelY <= 0.0f) ? 17.5f : -17.5f);
                    if (Hu3DData[model].pos.z <= -4000.0f && Hu3DData[model].scale.x > 0.0f) {
                        Hu3DData[model].scale.x = Hu3DData[model].scale.y = Hu3DData[model].scale.z -= 0.025f;
                    }
                    if (m264_carrierFleeVelY <= 0.0f) {
                        m264_carrierFleeVelY += 0.11f;
                    } else {
                        m264_carrierFleeVelY = 0.0f;
                    }
                    if (sindf(m264_carrierFleeTimerTbl[i] * 3.0f) != 1.0f) {
                        Hu3DData[model].rot.x = 0.0f - sindf(m264_carrierFleeTimerTbl[i]++ * 3.0f) * 90.0f;
                    } else {
                        Hu3DData[model].rot.x = -90.0f;
                    }
                    if (Hu3DData[model].pos.x >= 5000.0f || Hu3DData[model].pos.x <= -5000.0f ||
                        Hu3DData[model].pos.z >= 5000.0f || Hu3DData[model].pos.z <= -6000.0f) {
                        m264_carrierFleePhaseTbl[i]++;
                    }
                    break;
                case 2:
                    Hu3DModelCameraSet(model, HU3D_CAM_NONE);
                    Hu3DModelCameraSet(shadow, HU3D_CAM_NONE);
                    m264_carrierFleePhaseTbl[i]++;
                    break;
            }
            break;
        }
    }
}

void m264_CarrierGatherUpdate(void) {
    Vec targetPos[5] = {
        { -370.0f, 0.0f, 325.0f },
        { -190.0f, 0.0f, 100.0f },
        { 0.0f, 0.0f, -150.0f },
        { 190.0f, 0.0f, 100.0f },
        { 370.0f, 0.0f, 325.0f },
    };
    f32 x;
    f32 z;
    s16 model;
    s16 rank;
    s16 i;
    s16 j;

    if (m264_carrierGatherPhaseTbl[0] == 0) {
        rank = 0;
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                if (i != j && Hu3DData[m264_carrierMdlTbl[i][0]].pos.x >
                                  Hu3DData[m264_carrierMdlTbl[j][0]].pos.x) {
                    rank++;
                }
            }
            m264_carrierGatherRankTbl[i] = rank;
            rank = 0;
        }
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                if (i != j && m264_carrierGatherRankTbl[i] == m264_carrierGatherRankTbl[j]) {
                    m264_carrierGatherRankTbl[j]++;
                    i = 0;
                    break;
                }
            }
        }
    }
    if (m264_carrierPhase == 3) {
        for (i = 0; i < 5; i++) {
            model = m264_carrierMdlTbl[i][0];
            switch (m264_carrierGatherPhaseTbl[i]) {
                case 0:
                    m264_carrierGatherPosTbl[i].x = Hu3DData[model].pos.x;
                    m264_carrierGatherPosTbl[i].z = Hu3DData[model].pos.z;
                    m264_carrierMotNoTbl[i] = 1;
                    m264_carrierGatherPhaseTbl[i]++;
                    break;
                case 1:
                    x = Hu3DData[model].pos.x;
                    z = Hu3DData[model].pos.z;
                    Hu3DData[model].pos.x =
                        m264_carrierGatherPosTbl[i].x -
                        sindf(m264_carrierGatherTimerTbl[i] * 1.5f) *
                            (m264_carrierGatherPosTbl[i].x - targetPos[m264_carrierGatherRankTbl[i]].x);
                    Hu3DData[model].pos.z =
                        m264_carrierGatherPosTbl[i].z -
                        sindf(m264_carrierGatherTimerTbl[i] * 1.5f) *
                            (m264_carrierGatherPosTbl[i].z - targetPos[m264_carrierGatherRankTbl[i]].z);
                    Hu3DData[model].rot.y = -atan2df(z - Hu3DData[model].pos.z, x - Hu3DData[model].pos.x) + 270.0f;
                    if (sindf(m264_carrierGatherTimerTbl[i]++ * 1.5f) == 1.0f) {
                        Hu3DData[model].pos.x = targetPos[m264_carrierGatherRankTbl[i]].x;
                        Hu3DData[model].pos.z = targetPos[m264_carrierGatherRankTbl[i]].z;
                        m264_carrierGatherTimerTbl[i] = 0;
                        m264_carrierGatherPhaseTbl[i]++;
                    }
                    break;
                case 2:
                    if (Hu3DData[model].rot.y >= 360.0f) {
                        Hu3DData[model].rot.y -= 360.0f;
                    }
                    if (Hu3DData[model].rot.y < 0.0f) {
                        Hu3DData[model].rot.y += 360.0f;
                    }
                    if (Hu3DData[model].rot.y >= 180.0f) {
                        Hu3DData[model].rot.y += 6.75f;
                        if (Hu3DData[model].rot.y >= 360.0f) {
                            Hu3DData[model].rot.y = 0;
                            m264_carrierGatherPhaseTbl[i]++;
                        }
                    } else if (Hu3DData[model].rot.y > 0.0f) {
                        Hu3DData[model].rot.y -= 6.75f;
                        if (Hu3DData[model].rot.y <= 0.0f) {
                            Hu3DData[model].rot.y = 0.0f;
                            m264_carrierGatherPhaseTbl[i]++;
                        }
                    } else if (Hu3DData[model].rot.y == 0.0f) {
                        Hu3DData[model].pos.y = 0.0f;
                        m264_carrierGatherPhaseTbl[i]++;
                    }
                    break;
                case 3:
                    m264_carrierMotNoTbl[i] = 0;
                    m264_carrierGatherPhaseTbl[i]++;
                    break;
            }
        }
    }
}

void m264_BoxObjInit(omObjData *object) {
    s16 i;

    m264_boxMdlTbl[0][0] = Hu3DModelRead(0x610001, 0x2B9);
    m264_boxMdlTbl[0][2] = Hu3DModelRead(9, 0x2B9);
    for (i = 1; i < 5; i++) {
        m264_boxMdlTbl[i][0] = Hu3DModelLink(m264_boxMdlTbl[0][0]);
        m264_boxMdlTbl[i][2] = Hu3DModelLink(m264_boxMdlTbl[0][2]);
    }
    for (i = 0; i < 5; i++) {
        Hu3DModelPosSet(m264_boxMdlTbl[i][0], m264_boxPosTbl[i].x, m264_boxPosTbl[i].y,
                        m264_boxPosTbl[i].z);
        Hu3DModelScaleSet(m264_boxMdlTbl[i][0], 1.5f, 1.5f, 1.5f);
        Hu3DMotionSpeedSet(m264_boxMdlTbl[i][0], 0.0f);
        m264_boxMdlTbl[i][1] =
            Hu3DSprModelData[(s16)SprModelRead(m264_itemSprFileTbl[mgInstColumnTbl[i]], 0xA0, 0x10)].modelId;
        Hu3DModelPosSet(m264_boxMdlTbl[i][1], Hu3DData[m264_boxMdlTbl[i][0]].pos.x, 1000.0f,
                        Hu3DData[m264_boxMdlTbl[i][0]].pos.z);
        Hu3DModelScaleSet(m264_boxMdlTbl[i][1], 3.0f, 3.0f, 3.0f);
        Hu3DModelCameraSet(m264_boxMdlTbl[i][1], HU3D_CAM_NONE);
        Hu3DModelPosSet(m264_boxMdlTbl[i][2], Hu3DData[m264_boxMdlTbl[i][0]].pos.x, 0.0f,
                        Hu3DData[m264_boxMdlTbl[i][0]].pos.z);
        Hu3DModelScaleSet(m264_boxMdlTbl[i][2], 1.5f, 1.0f, 1.5f);
    }
    m264_prizeEffTbl[0] = EffectCreate(0xB0004, 0x2A9);
    Hu3DParticleAttrSet(m264_prizeEffTbl[0], 1, 0);
    m264_prizeEffTbl[1] = Hu3DModelRead(9, 0x2B9);
    Hu3DModelScaleSet(m264_prizeEffTbl[1], 1.0f, 1.0f, 1.0f);
    Hu3DModelCameraSet(m264_prizeEffTbl[1], HU3D_CAM_NONE);
    m264_boxState = 0;
    object->func = m264_BoxObjMain;
}

void m264_BoxShowUpdate(void) {
    s16 i;

    if (m264_boxState == 1) {
        switch (m264_boxShowPhase) {
            case 0:
                for (i = 0; i < 5; i++) {
                    Hu3DMotionSpeedSet(m264_boxMdlTbl[i][0], 1.0f);
                    Hu3DModelCameraSet(m264_boxMdlTbl[i][1], HU3D_CAM0);
                }
                HuAudFXPlay(0x4F1);
                m264_boxShowPhase++;
                break;
            case 1:
                for (i = 0; i < 5; i++) {
                    Hu3DData[m264_boxMdlTbl[i][1]].pos.y =
                        1000.0f - sindf(m264_boxShowTimer * 0.75f) * 960.0f;
                    if (m264_boxShowTimer >= 100 && Hu3DData[m264_boxMdlTbl[i][1]].scale.x > 2.0f) {
                        Hu3DData[m264_boxMdlTbl[i][1]].scale.x =
                            Hu3DData[m264_boxMdlTbl[i][1]].scale.y =
                                Hu3DData[m264_boxMdlTbl[i][1]].scale.z -= 0.1f;
                    }
                }
                if (sindf(m264_boxShowTimer++ * 0.75f) == 1.0f) {
                    m264_boxShowPhase++;
                    HuAudFXPlay(0x4F0);
                }
                break;
            case 2:
                for (i = 0; i < 5; i++) {
                    Hu3DMotionSpeedSet(m264_boxMdlTbl[i][0], -1.0f);
                }
                if (Hu3DData[m264_boxMdlTbl[0][0]].motTime <= 0.0f) {
                    for (i = 0; i < 5; i++) {
                        Hu3DMotionSpeedSet(m264_boxMdlTbl[i][0], 0.0f);
                        Hu3DMotionTimeSet(m264_boxMdlTbl[i][0], 0.0f);
                        Hu3DModelCameraSet(m264_boxMdlTbl[i][1], HU3D_CAM_NONE);
                    }
                    m264_boxShowPhase++;
                }
                break;
            case 3:
                m264_boxShowTimer = 0;
                m264_boxShowPhase = 0;
                m264_boxState = 0;
                break;
        }
    }
}

void m264_BoxCarryUpdate(void) {
    s16 i;

    if (m264_boxState == 2) {
        for (i = 0; i < 5; i++) {
            Hu3DData[m264_boxMdlTbl[i][0]].pos.x =
                Hu3DData[m264_carrierMdlTbl[i][0]].pos.x +
                cosdf(Hu3DData[m264_carrierMdlTbl[i][0]].rot.y + 270.0f) * 50.0f;
            Hu3DData[m264_boxMdlTbl[i][0]].pos.y = Hu3DData[m264_carrierMdlTbl[i][0]].pos.y + 140.0f;
            Hu3DData[m264_boxMdlTbl[i][0]].pos.z =
                Hu3DData[m264_carrierMdlTbl[i][0]].pos.z -
                sindf(Hu3DData[m264_carrierMdlTbl[i][0]].rot.y + 270.0f) * 50.0f;
            Hu3DData[m264_boxMdlTbl[i][0]].rot.y = Hu3DData[m264_carrierMdlTbl[i][0]].rot.y;
        }
    }
}

void m264_BoxDropUpdate(void) {
    s16 index = m264_hitCarrierNo;

    if (m264_boxState == 3) {
        Hu3DData[m264_boxMdlTbl[index][0]].pos.y -= 10.0f;
        if (Hu3DData[m264_boxMdlTbl[index][0]].pos.y <= 0.0f) {
            Hu3DData[m264_boxMdlTbl[index][0]].pos.y = 0.0f;
            m264_boxState = 0;
        }
    }
}

void m264_PrizeUpdate(void) {
    s16 index;

    if (m264_boxState == 4) {
        index = m264_hitCarrierNo;
        switch (m264_prizePhase) {
            case 0:
                Hu3DModelPosSet(m264_boxMdlTbl[index][1], Hu3DData[m264_boxMdlTbl[index][0]].pos.x,
                                40.0f, Hu3DData[m264_boxMdlTbl[index][0]].pos.z);
                Hu3DModelCameraSet(m264_boxMdlTbl[index][1], HU3D_CAM0);
                Hu3DMotionSpeedSet(m264_boxMdlTbl[index][0], 1.0f);
                HuAudFXPlay(0x4F7);
                m264_prizePhase++;
                break;
            case 1:
                if (Hu3DMotion[Hu3DData[m264_boxMdlTbl[index][0]].motId].unk02 ==
                    Hu3DData[m264_boxMdlTbl[index][0]].motTime) {
                    HuAudFXPlay(0x4F3);
                    Hu3DParticleAttrSet(m264_prizeEffTbl[0], 1, 1);
                    EffectParamSet(m264_prizeEffTbl[0], 5.0f, 20.0f, 10.0f);
                    EffectRangeSet(m264_prizeEffTbl[0], 100.0f);
                    EffectPosSet(m264_prizeEffTbl[0], Hu3DData[m264_boxMdlTbl[index][1]].pos.x,
                                       Hu3DData[m264_boxMdlTbl[index][1]].pos.y,
                                       Hu3DData[m264_boxMdlTbl[index][1]].pos.z);
                    Hu3DModelCameraSet(m264_prizeEffTbl[1], HU3D_CAM0);
                    Hu3DModelPosSet(m264_prizeEffTbl[1], Hu3DData[m264_boxMdlTbl[index][1]].pos.x,
                                    0.0f, Hu3DData[m264_boxMdlTbl[index][1]].pos.z);
                    m264_prizeSmokeState = 1;
                    m264_prizePhase++;
                }
                break;
            case 2:
                Hu3DData[m264_boxMdlTbl[index][1]].pos.y =
                    40.0f - sindf(m264_prizeTimer * 3.0f) * -310.0f;
                if (m264_prizeTimer >= 10 && Hu3DData[m264_boxMdlTbl[index][1]].scale.x < 3.0f) {
                    Hu3DData[m264_boxMdlTbl[index][1]].scale.x =
                        Hu3DData[m264_boxMdlTbl[index][1]].scale.y =
                            Hu3DData[m264_boxMdlTbl[index][1]].scale.z += 0.1f;
                }
                if (sindf(m264_prizeTimer++ * 3.0f) == 1.0f) {
                    m264_prizeTimer = 0;
                    m264_prizePhase++;
                }
                break;
            case 3:
                Hu3DData[m264_boxMdlTbl[index][1]].pos.x =
                    Hu3DData[m264_boxMdlTbl[index][0]].pos.x -
                    sindf(m264_prizeTimer * 3.0f) * Hu3DData[m264_boxMdlTbl[index][0]].pos.x;
                Hu3DData[m264_boxMdlTbl[index][1]].pos.z =
                    Hu3DData[m264_boxMdlTbl[index][0]].pos.z -
                    sindf(m264_prizeTimer * 3.0f) *
                        (Hu3DData[m264_boxMdlTbl[index][0]].pos.z - 400.0f);
                if (sindf(m264_prizeTimer++ * 3.0f) == 1.0f) {
                    m264_prizeTimer = 0;
                    m264_prizePhase++;
                }
                break;
            case 4:
                Hu3DData[m264_boxMdlTbl[index][1]].pos.y =
                    sindf(m264_prizeTimer * 6.0f) * 10.0f + 350.0f;
                if (m264_prizeTimer++ >= 60) {
                    m264_prizeTimer = 0;
                }
                break;
        }
        EffectPosSet(m264_prizeEffTbl[0], Hu3DData[m264_boxMdlTbl[index][1]].pos.x,
                           Hu3DData[m264_boxMdlTbl[index][1]].pos.y,
                           Hu3DData[m264_boxMdlTbl[index][1]].pos.z);
        Hu3DModelPosSet(m264_prizeEffTbl[1], Hu3DData[m264_boxMdlTbl[index][1]].pos.x, 0.0f,
                        Hu3DData[m264_boxMdlTbl[index][1]].pos.z);
    }
}

void m264_BoxObjMain(omObjData *object) {
    f32 scale;
    s16 i;

    for (i = 0; i < 5; i++) {
        scale = 1.5f - Hu3DData[m264_boxMdlTbl[i][0]].pos.y * 0.010714286f;
        Hu3DModelPosSet(m264_boxMdlTbl[i][2], Hu3DData[m264_boxMdlTbl[i][0]].pos.x, 0.0f,
                        Hu3DData[m264_boxMdlTbl[i][0]].pos.z);
        Hu3DModelScaleSet(m264_boxMdlTbl[i][2], scale, 1.0f, scale);
    }
}

void m264_EffObjInit(omObjData *object) {
    s16 i;

    for (i = 0; i < 5; i++) {
        m264_smokeMdlTbl[i] = Hu3DModelRead(0x610005, 0x2B9);
        Hu3DModelScaleSet(m264_smokeMdlTbl[i], 1.5f, 1.5f, 1.0f);
        Hu3DModelCameraSet(m264_smokeMdlTbl[i], HU3D_CAM_NONE);
    }
    m264_effMotTbl[0] = m264_MotMdlRead(0x610005);
    m264_effMdlTbl[0] = Hu3DModelRead(0xB0006, 0x2B9);
    m264_effMotTbl[1] = m264_MotMdlRead(0xB0006);
    Hu3DModelCameraSet(m264_effMdlTbl[0], HU3D_CAM_NONE);
    m264_effMdlTbl[1] = Hu3DModelRead(0x610004, 0x2B9);
    m264_effMotTbl[2] = m264_MotMdlRead(0x610004);
    Hu3DModelCameraSet(m264_effMdlTbl[1], HU3D_CAM_NONE);
    object->func = m264_EffObjMain;
}

void m264_EffObjMain(omObjData *object) {
    s16 i;
    s16 skip;
    s16 index;
    s16 model;
    f32 x;
    f32 y;
    f32 z;

    if (m264_smokeState == 1) {
        skip = (m264_missF == 0) ? m264_hitCarrierNo : -1;
        for (i = 0; i < 5; i++) {
            if (i != skip) {
                x = Hu3DData[m264_carrierMdlTbl[i][0]].pos.x;
                y = Hu3DData[m264_carrierMdlTbl[i][0]].pos.y + 125.0f;
                z = Hu3DData[m264_carrierMdlTbl[i][0]].pos.z + 50.0f;
                Hu3DModelPosSet(m264_smokeMdlTbl[i], x, y, z);
                Hu3DModelCameraSet(m264_smokeMdlTbl[i], HU3D_CAM0);
                Hu3DMotionModelSet(m264_smokeMdlTbl[i], m264_effMotTbl[0]);
                Hu3DModelCameraSet(m264_boxMdlTbl[i][0], HU3D_CAM_NONE);
                Hu3DModelCameraSet(m264_boxMdlTbl[i][1], HU3D_CAM_NONE);
                Hu3DModelCameraSet(m264_boxMdlTbl[i][2], HU3D_CAM_NONE);
            }
        }
        HuAudFXPlay(0x4F2);
        m264_smokeState = 2;
    }
    if (m264_smokeState == 2 &&
        Hu3DMotion[Hu3DData[m264_smokeMdlTbl[0]].motId].unk02 ==
            Hu3DData[m264_smokeMdlTbl[0]].motTime) {
        do {
            for (i = 0; i < 5; i++) {
                if (i != m264_hitCarrierNo) {
                    Hu3DModelCameraSet(m264_smokeMdlTbl[i], HU3D_CAM_NONE);
                }
            }
        } while (0); // TODO: required to match (loop depth affects i register allocation)
    }
    if (m264_prizeSmokeState == 1) {
        index = m264_hitCarrierNo;
        z = Hu3DData[m264_boxMdlTbl[index][0]].pos.z + 50.0f;
        Hu3DModelPosSet(m264_smokeMdlTbl[index], Hu3DData[m264_boxMdlTbl[index][0]].pos.x, 10.0f, z);
        Hu3DModelCameraSet(m264_smokeMdlTbl[index], HU3D_CAM0);
        Hu3DMotionModelSet(m264_smokeMdlTbl[index], m264_effMotTbl[0]);
        Hu3DModelCameraSet(m264_boxMdlTbl[index][0], HU3D_CAM_NONE);
        Hu3DModelCameraSet(m264_boxMdlTbl[index][2], HU3D_CAM_NONE);
        m264_playerActNo = 3;
        m264_playerEffState = 1;
        m264_prizeSmokeState = 2;
    } else if (m264_prizeSmokeState == 2) {
        model = m264_smokeMdlTbl[m264_hitCarrierNo];
        if (Hu3DMotion[Hu3DData[model].motId].unk02 == Hu3DData[model].motTime) {
            Hu3DModelCameraSet(model, HU3D_CAM_NONE);
        }
    }
    if (m264_playerEffState == 1) {
        Hu3DModelPosSet(m264_effMdlTbl[0], m264_playerObj->trans.x, 100.0f,
                        m264_playerObj->trans.z + 150.0f);
        Hu3DModelCameraSet(m264_effMdlTbl[0], HU3D_CAM0);
        Hu3DMotionModelSet(m264_effMdlTbl[0], m264_effMotTbl[1]);
        Hu3DModelCameraSet(m264_batMdl, HU3D_CAM_NONE);
        m264_playerEffState = 2;
    }
    if (m264_playerEffState == 2) {
        model = m264_effMdlTbl[0];
        if (Hu3DMotion[Hu3DData[model].motId].unk02 == Hu3DData[model].motTime) {
            Hu3DModelCameraSet(model, HU3D_CAM_NONE);
        }
    }
    if (m264_hitEffState == 1) {
        x = m264_playerObj->trans.x + cosdf(m264_playerObj->rot.y - 90.0f) * 100.0f;
        Hu3DModelPosSet(m264_effMdlTbl[1], x, 50.0f,
                        m264_playerObj->trans.z + sindf(m264_playerObj->rot.y - 90.0f) * 100.0f);
        Hu3DModelCameraSet(m264_effMdlTbl[1], HU3D_CAM0);
        Hu3DMotionModelSet(m264_effMdlTbl[1], m264_effMotTbl[2]);
        m264_hitEffState = 2;
    }
    if (m264_hitEffState == 2) {
        model = m264_effMdlTbl[1];
        if (Hu3DMotion[Hu3DData[model].motId].unk02 == Hu3DData[model].motTime) {
            Hu3DModelCameraSet(model, HU3D_CAM_NONE);
        }
    }
}

s16 m264_EspCreate(s32 dataNum, u16 attr, u16 pri, s16 x, s16 y) {
    s16 sprite = espEntry(HuSprAnimDataRead(dataNum), 0, 0);

    espAttrSet(sprite, attr);
    espPriSet(sprite, pri);
    espPosSet(sprite, x, y);
    return sprite;
}

s16 m264_MotMdlRead(s32 arg0) {
    s16 temp = Hu3DMotionModelRead(arg0);

    if (temp < 0) {
        temp = -1;
    }
    return temp;
}

s16 m264_PlayerHitCheck(void) {
    omObjData *obj = m264_playerObj;
    f32 x;
    f32 z;
    f32 dx;
    f32 dz;
    f32 px;
    f32 pz;
    s16 i;
    s16 j;

    x = obj->trans.x + cosdf(obj->rot.y - 90.0f) * 50.0f;
    pz = obj->trans.z - sindf(obj->rot.y - 90.0f) * 50.0f;
    z = pz;
    j = 3;
    for (i = 0; i < 5; i++) {
        // TODO: `j` is an otherwise unused variable that the original code
        // keeps live (dead `li s1, 3`); `i + j - j` is an unknown stand-in.
        px = Hu3DData[m264_carrierMdlTbl[i + j - j][0]].pos.x;
        pz = Hu3DData[m264_carrierMdlTbl[i + j - j][0]].pos.z;
        dx = x - px;
        dz = z - pz;
        // The do-while(0) raises the loop depth weighting of the 100.0f
        // constant use, needed to match float register allocation.
        do {
            if (HuSqrtf(dx * dx + dz * dz) < 100.0f) {
                return 1;
            }
        } while (0);
    }
    return 0;
}

s16 m264_CarrierPlayerHitCheck(s16 index) {
    omObjData *obj = m264_playerObj;
    f32 x;
    f32 z;
    f32 dx;
    f32 dz;

    x = Hu3DData[m264_carrierMdlTbl[index][0]].pos.x +
        cosdf(Hu3DData[m264_carrierMdlTbl[index][0]].rot.y - 90.0f) * 50.0f;
    z = Hu3DData[m264_carrierMdlTbl[index][0]].pos.z -
        sindf(Hu3DData[m264_carrierMdlTbl[index][0]].rot.y - 90.0f) * 50.0f;
    dx = obj->trans.x;
    dz = obj->trans.z;
    dx -= x;
    dz -= z;
    if (HuSqrtf(dx * dx + dz * dz) < 150.0f) {
        return 1;
    }
    return 0;
}

s16 m264_CarrierHitCheck(s16 index) {
    f32 x;
    f32 z;
    f32 dx;
    f32 dz;
    s16 i;

    x = Hu3DData[m264_carrierMdlTbl[index][0]].pos.x +
        cosdf(Hu3DData[m264_carrierMdlTbl[index][0]].rot.y - 90.0f) * 50.0f;
    z = Hu3DData[m264_carrierMdlTbl[index][0]].pos.z -
        sindf(Hu3DData[m264_carrierMdlTbl[index][0]].rot.y - 90.0f) * 50.0f;
    for (i = 0; i < 5; i++) {
        if (index == i) {
            continue;
        }
        dx = Hu3DData[m264_carrierMdlTbl[i][0]].pos.x;
        dz = Hu3DData[m264_carrierMdlTbl[i][0]].pos.z;
        dx -= x;
        dz -= z;
        if (HuSqrtf(dx * dx + dz * dz) < 150.0f) {
            return 1;
        }
    }
    return 0;
}
