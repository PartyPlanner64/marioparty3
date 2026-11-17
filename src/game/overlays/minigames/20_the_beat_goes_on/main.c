#include "common.h"
#include "game/camera.h"
#include "game/audio.h"
#include "game/camsetup.h"
#include "game/gamemes.h"
#include "game/hmfanim.h"
#include "game/hmfspr.h"
#include "game/mallocblock.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/wipe.h"
#include "gcc/memory.h"
#include "math.h"
#include "game/overlays/minigame.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define FABS(x) ((x) > 0.0f ? (x) : 0.0f - (x))

// Grid position of a single marker in the "Beat Goes On" note field.
typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} BeatGoesOnPos; // sizeof 0x4

// Note/scoring state block hanging off omObjData::data for one "Beat Goes On" grid.
typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ u8 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ u8 unk_16;
    /* 0x17 */ u8 unk_17;
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19;
    /* 0x1A */ u8 noteFlags[15];
    /* 0x29 */ u8 unk_29;
    /* 0x2A */ u8 btnA[16];
    /* 0x3A */ u8 btnB[16];
    /* 0x4A */ u8 btnZ[16];
} BeatGoesOnNotes; // sizeof 0x5A

// Work data for each Fire object.
typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ u32 unk_0C;
    /* 0x10 */ u8 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ HmfModelEntry *entry;
    /* 0x1C */ s8 unk_1C;
} BeatGoesOnFireWork; // sizeof 0x20

// Work data hung off MgPlayerWork::unk158 for each player.
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ f32 unk_04;
} BeatGoesOnSpinWork; // sizeof 0x8

// Work data for the conductor object.
typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s8 unk_02;
} BeatGoesOnConductorWork; // sizeof 0x4

// One entry in the sequence of buttons the player must press.
typedef struct {
    /* 0x00 */ u16 button;
    /* 0x02 */ s16 unk_02;
} BeatGoesOnButton; // sizeof 0x4

u8 m232_fireState = 0;
u8 m232_standOrderTbl[24][4] = {
    { 0, 1, 2, 3 }, { 0, 1, 3, 2 }, { 0, 2, 1, 3 }, { 0, 2, 3, 1 }, { 0, 3, 1, 2 }, { 0, 3, 2, 1 }, { 1, 0, 2, 3 }, { 1, 0, 3, 2 }, { 1, 2, 3, 0 }, { 1, 2, 0, 3 }, { 1, 3, 0, 2 }, { 1, 3, 2, 0 }, { 2, 0, 1, 3 }, { 2, 0, 3, 1 }, { 2, 1, 0, 3 }, { 2, 1, 3, 0 }, { 2, 3, 0, 1 }, { 2, 3, 1, 0 }, { 3, 0, 1, 2 }, { 3, 0, 2, 1 }, { 3, 1, 0, 2 }, { 3, 1, 2, 0 }, { 3, 2, 0, 1 }, { 3, 2, 1, 0 }
};
s32 m232_exitTimer = 0;
s32 m232_finishTimer = 0;
s8 m232_exitF = 0;
BeatGoesOnPos m232_fireFramePosTbl[8] = { { 26, 15 }, { 26, 14 }, { 26, 13 }, { 26, 13 }, { 26, 13 }, { 26, 13 }, { 27, 12 }, { 27, 12 } };
u8 m232_cameraState = 0;
s8 m232_playerCreateNo = 0;
f32 m232_outDrumY = -90.0f;
f32 m232_outStageZ = 0.0f;
s8 m232_playerAliveNum = 4;
s8 m232_drumState = 0;
s8 m232_cameraTurnState = 0;
s8 m232_turnF = 0;
s8 m232_musicStopF = 0;
s8 m232_drawF = 0;
s32 m232_turnTimer = 0;
s32 m232_smokeTimerTbl[4][4] = { { 0, -2, -4, -6 }, { 0, -2, -4, -6 }, { 0, -2, -4, -6 }, { 0, -2, -4, -6 } };
f32 m232_smokeScaleTbl[4] = { 0.5f, 1.0f, 1.5f, 2.0f };
f32 m232_cursorX = 20.0f;
f32 m232_noteScaleAngle = 0.0f;
f32 m232_pulseAngle = 0.0f;
s8 m232_pulseTimer = 90;

s16 m232_fireLitMdl BSS;
s16 m232_fireBaseMdl BSS;
s16 m232_fireFlareMdl BSS;
s16 m232_fireCreateNo BSS;
s16 m232_fireAnim BSS;
s8 m232_standNo BSS;
s16 m232_standMdl BSS;
f32 m232_outJumpAngle BSS;
s8 m232_cameraTurnTimer BSS;
s8 m232_noteHitNo BSS;
MinigameFlow m232_mgFlow BSS;
BeatGoesOnButton m232_seqTbl[16] BSS;
omObjData *m232_drummerObj BSS;
omObjData *m232_sheetObj BSS;
s8 m232_seqLen BSS;
s8 m232_seqNo BSS;
u8 m232_standOrderNo BSS;
s16 m232_smokeMdlTbl[4] BSS;
s16 m232_signGrp BSS;
s16 m232_drumAMdl BSS;
s16 m232_drumBMdl BSS;
s16 m232_drumZMdl BSS;
s32 m232_signY BSS;
u16 m232_waterTexSize[2] BSS;
f32 m232_waterScroll BSS;
u16 m232_sheetLineSprTbl[2] BSS;
u16 m232_cursorSpr BSS;
u16 m232_noteMarkSpr BSS;
u16 m232_hitMarkSpr BSS;
u8 m232_hitMarkSprPad[4] BSS; /* Unreferenced. */
u16 m232_noteSprTbl[15] BSS;
u16 m232_noteASprTbl[16] BSS;
u16 m232_noteBSprTbl[16] BSS;
u16 m232_noteZSprTbl[16] BSS;
extern u32 omCharModelNoTbl[][6];
extern s32 omCharMot2Tbl[][6];
extern u8 omAllPauseF;

void m232_FlowInit(MinigameFlow *flow);
void m232_CameraInit(void);
void m232_CameraWideMove(f32 speed);
void m232_MainObjMain(omObjData *object);
void m232_FireObjInit(omObjData *obj);
void m232_FireObjMain(omObjData *obj);
void m232_DrummerObjInit(omObjData *obj);
void m232_DrummerObjMain(omObjData *obj);
void m232_SeqInit(void);
u16 m232_SeqBtnGet(s8 index);
void m232_PlayerObjInit(omObjData *obj);
void m232_PlayerObjMain(omObjData *obj);
u16 m232_PlayerComInput(MgPlayerWork *data);
void m232_SheetBtnSet(u16 button);
void m232_DrumHitUpdate(omObjData *obj, s8 *state);
void m232_CameraTurnUpdate(s8 *state, f32 speed);
void m232_SmokeUpdate(omObjData *obj);
void m232_WaterObjInit(omObjData *obj);
void m232_WaterObjMain(omObjData *obj);
void m232_SheetObjInit(omObjData *obj);
Vec *m232_DirCalc(Vec *out, Vec *from, Vec *to);
void m232_SheetObjMain(omObjData *obj);
void m232_SheetPosGet(BeatGoesOnPos *pos);
void m232_SheetClear(void);

void m232_ObjectSetup(void) {
    s16 model;
    s32 i;

    MapCollInit(0x20);
    Hu3DQuadPoolInit(&mgQuadPool, 0x40);
    Hu3DSprModelInit(0x40);
    omInitObjMan(0x20, 0);
    omGameSysInit();
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    MgFieldStatClear();
    m232_CameraInit();
    m232_FlowInit(&m232_mgFlow);
    MgFlowInit(&m232_mgFlow);
    Hu3DGLightColorSet(1, 0x40, 0x40, 0x40);
    Hu3DGLightDirSet(1, 0.0f, 0.0f, 100.0f);
    omSetStatBit(omAddObj(0, 0, 0, -1, m232_MainObjMain), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omSetStatBit(omAddObj(0, 1, 0, -1, m232_WaterObjInit), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    m232_drummerObj = omAddObj(0, 4, 5, -1, m232_DrummerObjInit);
    model = Hu3DModelRead(0x41000A, 0x819);
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            m232_smokeMdlTbl[i] = model;
        } else {
            m232_smokeMdlTbl[i] = Hu3DModelLink(model);
        }
        Hu3DModelAttrSet(m232_smokeMdlTbl[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    m232_sheetObj = omAddObj(1, 0, 0, -1, m232_SheetObjInit);
    omSetStatBit(m232_sheetObj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    m232_standOrderNo = rand8() * 3U / 32;
    for (i = 0; i < 4; i++) {
        mgPlayerObjTbl[i] = omAddObj(2, 7, 10, -1, m232_PlayerObjInit);
    }
    for (i = 0; i < 5; i++) {
        omSetStatBit(omAddObj(3, 4, 2, -1, m232_FireObjInit), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    }
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
}

void m232_FlowInit(MinigameFlow *flow) {
    s32 i;

    flow->state = MG_STATE_OPENING;
    flow->type = MINIGAME_4P;
    flow->timerMode = MG_TIMER_NONE;
    flow->timeDisp = MG_TIME_DISP_NONE;
    flow->newRecord = FALSE;
    flow->gauge = MG_GAUGE_NONE;
    flow->resultType = MG_RESULT_WIN_1;
    flow->startDelay = 64;
    flow->timer = -1;
    flow->timeLimit = 0;
    flow->finishDelay = -1;
    flow->resultDelay = 150;
    for (i = 0; i < 4; i++) {
        flow->gaugeValue[i] = 0;
        flow->winners[i] = 0xFF;
    }
}

void m232_CameraInit(void) {
    s32 camIndex;

    Center.x = 0.0f;
    Center.y = 110.0f;
    Center.z = 140.0f;
    CRot.x = -40.0f;
    CRot.y = CRot.z = Center.x;
    CZoom = 1060.0f;
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(camIndex, 30.0f, 80.0f, 8000.0f);
}

void m232_CameraOutMove(f32 speed) {
    f32 zoomStep = 1500.0f;
    f32 centerStep = -500.0f;
    f32 rotStep = -20.0f;
    Vec pos;
    Vec2f screenPos;

    CZoom += zoomStep / speed;
    if (CZoom > 2200.0f) {
        CZoom = 2200.0f;
    }
    Center.z += centerStep / speed;
    if (Center.z < 380.0f) {
        Center.z = 380.0f;
    }
    CRot.x += rotStep / speed;
    if (CRot.x < -30.0f) {
        CRot.x = -30.0f;
    }
    pos.x = 0.0f;
    pos.y = -100.0f;
    pos.z = -1794.6355f;
    Hu3DCam3Dto2D(0, &pos, &screenPos);
    HuSprPosSet(m232_signGrp, 0, 160, screenPos.y + -50.0f);
}

void m232_CameraCloseMove(f32 speed) {
    f32 zoomStep = -1500.0f;
    f32 centerStep = 500.0f;
    f32 rotStep = 20.0f;
    Vec pos;
    Vec2f screenPos;

    CZoom += zoomStep / speed;
    if (CZoom < 700.0f) {
        CZoom = 700.0f;
    }
    Center.z += centerStep / speed;
    if (Center.z > 880.0f) {
        Center.z = 880.0f;
    }
    CRot.x += rotStep / speed;
    if (CRot.x > -10.0f) {
        CRot.x = -10.0f;
    }
    pos.x = 0.0f;
    pos.y = -100.0f;
    pos.z = -1794.6355f;
    Hu3DCam3Dto2D(0, &pos, &screenPos);
    HuSprPosSet(m232_signGrp, 0, 160, screenPos.y + -50.0f);
}

void m232_CameraWideMove(f32 speed) {
    f32 zoomStep = 1140.0f;
    f32 centerStep = 240.0f;
    f32 rotStep = 10.0f;
    Vec pos;
    Vec2f screenPos;

    CZoom += zoomStep / speed;
    if (CZoom > 2200.0f) {
        CZoom = 2200.0f;
    }
    Center.z += centerStep / speed;
    if (Center.z > 380.0f) {
        Center.z = 380.0f;
    }
    CRot.x += rotStep / speed;
    if (CRot.x > -30.0f) {
        CRot.x = -30.0f;
    }
    pos.x = 0.0f;
    pos.y = -100.0f;
    pos.z = -1794.6355f;
    Hu3DCam3Dto2D(0, &pos, &screenPos);
    HuSprPosSet(m232_signGrp, 0, 160, screenPos.y + -50.0f);
}

void m232_CameraHomeMove(f32 speed) {
    f32 zoomStep = -1140.0f;
    f32 centerStep = -240.0f;
    f32 rotStep = -10.0f;
    Vec pos;
    Vec2f screenPos;

    CZoom += zoomStep / speed;
    if (CZoom < 1060.0f) {
        CZoom = 1060.0f;
    }
    Center.z += centerStep / speed;
    if (Center.z < 140.0f) {
        Center.z = 140.0f;
    }
    CRot.x += rotStep / speed;
    if (CRot.x < -40.0f) {
        CRot.x = -40.0f;
    }
    pos.x = 0.0f;
    pos.y = -100.0f;
    pos.z = -1794.6355f;
    Hu3DCam3Dto2D(0, &pos, &screenPos);
    HuSprPosSet(m232_signGrp, 0, 160, screenPos.y + -50.0f);
}

void m232_MainObjMain(omObjData *object) {
    omObjData *player;
    s32 i;

    if (omPauseChk() + omAllPauseF == 0) {
        if (m232_exitF == 0 && omSysExitReq == 1) {
            HuAudFXAllStop();
            if (!(HuAudStat & 4)) {
                HuAudSeqFadeOut(30);
            } else {
                HuAudSeqStop();
            }
            MgFlowStatSet(MG_STATE_EXIT);
            m232_exitF = 1;
        }
        MgFieldStatUpdate();
        switch (MgFlowMain()) {
            case 0:
                if (MgFlowStatTimeGet() == 16) {
                    HuAudSeqPlay(0x3F);
                    HuAudFXPlay(0x40B);
                } else if (MgFlowStatTimeGet() >= 27) {
                    m232_CameraWideMove(40.0f);
                }
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                if (m232_finishTimer == 0) {
                    HuAudFXAllFadeOut(30);
                    if (m232_mgFlow.resultType == MG_RESULT_WIN_1) {
                        player = mgPlayerObjTbl[m232_mgFlow.winners[0]];
                        Hu3DModelAttrSet(player->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrSet(player->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrSet(player->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    }
                } else if (m232_finishTimer == 30 && m232_mgFlow.resultType == MG_RESULT_DRAW) {
                    for (i = 0; i < 4; i++) {
                        player = mgPlayerObjTbl[i];
                        if (player->work[0] == 10) {
                            Hu3DModelAttrSet(player->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        } else {
                            MgPlayerEffSet(player, 6, player->trans.x, -50.0f, player->trans.z + 50.0f, 45.0f,
                                                   0.0f);
                            Hu3DModelAttrSet(player->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                            Hu3DModelAttrSet(player->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                            Hu3DModelAttrSet(player->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        }
                    }
                }
                m232_finishTimer++;
                break;
            case 4:
                if (MgFlowStatTimeGet() == 1) {
                    switch (m232_mgFlow.resultType) {
                        case 0:
                            GMesCreate(GMES_MES_MG_WINNER, GwPlayer[m232_mgFlow.winners[0]].chr);
                            HuAudSeqPlay(0x65);
                            break;
                        case 4:
                            GMesCreate(GMES_MES_MG_DRAW);
                            HuAudSeqPlay(0x6C);
                            break;
                    }
                    m232_mgFlow.resultType = MG_RESULT_NONE;
                }
                break;
            case 5:
                if (m232_exitTimer == 0) {
                    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                } else if (WipeStatGet() == 0 && !(HuAudStat & 4)) {
                    omOvlReturnEx(1);
                }
                m232_exitTimer++;
                break;
        }
    }
}

void m232_FireObjInit(omObjData *obj) {
    BeatGoesOnFireWork *work;
    u16 id;

    obj->data = HuMemAllocTag(sizeof(BeatGoesOnFireWork), TAG_OVERLAY);
    memset(obj->data, 0, sizeof(BeatGoesOnFireWork));
    work = obj->data;
    work->unk_1C = m232_fireCreateNo;
    if (work->unk_1C == 4) {
        work->unk_10 = 0;
    } else if (work->unk_1C == 0) {
        work->unk_10 = 20;
    } else {
        work->unk_10 = rand8() % 20;
    }
    work->unk_14 = 0;
    obj->scale.x = obj->scale.y = obj->scale.z = 3.0f;
    if (m232_fireCreateNo == 0) {
        id = m232_fireBaseMdl = SprModelRead(0x410001, 0, 16);
    } else {
        id = Hu3DSprModelLink(m232_fireBaseMdl, 16);
    }
    Hu3DSprModelFrameSet(id, m232_fireCreateNo & 7);
    work->entry = &Hu3DSprModelData[(s16)id];
    obj->model[1] = work->entry->modelId;
    obj->trans.x = sindf(m232_fireCreateNo * 45.0f - 90.0f) * 160.0f;
    obj->trans.y = 40.0f;
    obj->trans.z = cosdf(m232_fireCreateNo * 45.0f - 90.0f) * 160.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    if (m232_fireCreateNo == 0) {
        id = m232_fireLitMdl = SprModelRead(0x410000, 0, 16);
    } else {
        id = Hu3DSprModelLink(m232_fireLitMdl, 16);
    }
    obj->model[0] = Hu3DSprModelData[(s16)id].modelId;
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    if (m232_fireCreateNo == 0) {
        id = m232_fireFlareMdl = SprModelRead(0x410002, 0, 16);
    } else {
        id = Hu3DSprModelLink(m232_fireFlareMdl, 16);
    }
    obj->model[2] = Hu3DSprModelData[(s16)id].modelId;
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    id = obj->model[3] = Hu3DModelRead(0x410003, 0xAA9);
    if (m232_fireCreateNo == 0) {
        m232_fireAnim = Hu3DAnimRead(Hu3DData[(s16)id].hmf, 0xA008C, "c201n_00_DEF");
    } else {
        Hu3DAnimLink(Hu3DData[(s16)id].hmf, m232_fireAnim, 0, "c201n_00_DEF");
        Hu3DAnimLink(Hu3DData[obj->model[3]].hmf, m232_fireAnim, 0, "c201n_00_DEF");
    }
    Hu3DModelRemakeStatic(id);
    Hu3DModelDynamicFree(id);
    Hu3DModelScaleSet(id, 0.6f, 0.6f, 0.6f);
    Hu3DModelPosSet(id, (m232_fireCreateNo - 4) * 25 * obj->scale.x, 0.0f, 0.0f);
    omObjMotionRead(obj, 0, 0x410003);
    omObjMotionRead(obj, 1, 0x410004);
    obj->func = m232_FireObjMain;
    m232_fireCreateNo++;
}

void m232_FirePosUpdate(omObjData *obj) {
    BeatGoesOnFireWork *work = obj->data;
    HmfModelEntry *entry = work->entry;
    u16 modelId = entry->modelId;
    HmfAnimRot *rot;
    s16 frame;
    f32 ox;
    f32 oy;
    f32 oz;
    f32 x;
    f32 y;
    f32 z;

    obj->rot.x = CRot.x;
    obj->rot.y = CRot.y;
    obj->rot.z = CRot.z;
    Hu3DModelRotSet(modelId, obj->rot.x, obj->rot.y, obj->rot.z);
    rot = &Hu3DAnimSetData[(u16)entry->unk_02].rot[entry->pointIdx];
    frame = rot->frames[entry->nodeIdx].unk00;
    ox = m232_fireFramePosTbl[frame].x - 16;
    oy = 16 - m232_fireFramePosTbl[frame].y;
    oz = 0.0f;
    x = ox * cosdf(CRot.y) + sindf(CRot.y) * oz;
    y = oy * cosdf(CRot.x) - sindf(CRot.x) * oz;
    z = oy * sindf(CRot.x) + sindf(CRot.x) * oz - ox * sindf(CRot.y) + cosdf(CRot.y) * oz;
    x *= obj->scale.x;
    y *= obj->scale.y;
    z *= obj->scale.z;
    x += obj->trans.x;
    y += obj->trans.y;
    z += obj->trans.z;
    Hu3DModelPosSet(obj->model[3], x, y, z);
    work->pos.x = x;
    work->pos.y = y;
    work->pos.z = z;
    Hu3DModelRotSet(obj->model[3], CRot.x, CRot.y, CRot.z);
}

void m232_FireObjMain(omObjData *obj) {
    BeatGoesOnFireWork *work = obj->data;
    Vec dir;
    Vec from;
    Vec to;
    s32 i;

    switch (m232_fireState) {
        case 0:
            Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
            Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
            Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            if (Hu3DMotion[Hu3DData[obj->model[3]].motId].unk02 - 2.0f <= Hu3DData[obj->model[3]].motTime) {
                Hu3DMotionShiftSet(obj->model[3], Hu3DData[obj->motion[0]].motId, 0, 1, 2);
            }
            work->unk_0C = 0;
            m232_FirePosUpdate(obj);
            break;
        case 1:
            Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
            Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            if (Hu3DMotion[Hu3DData[obj->model[3]].motId].unk02 - 2.0f <= Hu3DData[obj->model[3]].motTime) {
                Hu3DMotionShiftSet(obj->model[3], Hu3DData[obj->motion[0]].motId, 0, 1, 2);
            }
            m232_FirePosUpdate(obj);
            work->unk_14 = 0.0f;
            break;
        case 2:
            if (omPauseChk() + omAllPauseF == 0) {
                if (work->unk_0C < work->unk_10) {
                    work->unk_0C++;
                } else {
                    if (work->unk_10 == work->unk_0C) {
                        if (work->unk_1C == 4) {
                            HuAudFXPlay(0x408);
                        }
                        Hu3DModelScaleSet(obj->model[2], obj->scale.x, obj->scale.y, obj->scale.z);
                        Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
                        Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        Hu3DMotionShiftSet(obj->model[3], Hu3DData[obj->motion[1]].motId, 0, 1, 2);
                    } else if (work->unk_0C < work->unk_10 + 28) {
                        if (work->pos.y > -90.0f) {
                            from.x = work->pos.x;
                            from.y = work->pos.y;
                            from.z = work->pos.z;
                            to.x = 75 - rand8() % 150;
                            to.y = -100.0f;
                            to.z = 5 - rand8() % 10 + 600.0f;
                            m232_DirCalc(&dir, &from, &to);
                            work->pos.x += dir.x * 25.0f;
                            work->pos.y += dir.y * 25.0f;
                            work->pos.z += dir.z * 25.0f;
                            Hu3DModelPosSet(obj->model[3], work->pos.x, sindf(work->unk_14) * 300.0f + work->pos.y, work->pos.z);
                            work->unk_14 += 8.0f;
                            if (work->unk_14 >= 180.0f) {
                                work->unk_14 = 180.0f;
                            }
                        } else {
                            Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                            Hu3DModelPosSet(obj->model[3], work->pos.x, work->pos.y, work->pos.z);
                        }
                    } else if (work->unk_0C == 28) {
                        work->unk_0C = 29;
                        if (work->unk_1C == 4) {
                            for (i = 0; i < 4; i++) {
                                if (mgPlayerObjTbl[i]->work[0] == 5) {
                                    break;
                                }
                            }
                            mgPlayerObjTbl[i]->work[0] = 6;
                        }
                        break;
                    } else if (work->unk_0C > work->unk_10 + 28) {
                        work->pos.y -= 2.0f;
                        Hu3DModelPosSet(obj->model[3], work->pos.x, work->pos.y, work->pos.z);
                        if (work->pos.y < -90.0f && work->unk_1C == 0) {
                            m232_fireState = 0;
                            work->unk_0C = 0;
                            m232_FirePosUpdate(obj);
                            break;
                        }
                    } else {
                        break;
                    }
                    work->unk_0C++;
                }
            }
            break;
    }
}

void m232_DrummerObjInit(omObjData *obj) {
    BeatGoesOnConductorWork *work;

    obj->func = m232_DrummerObjMain;
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -100.0f;
    obj->work[0] = 0;
    obj->data = HuMemAllocTag(sizeof(BeatGoesOnConductorWork), TAG_OVERLAY);
    memset(obj->data, 0, sizeof(BeatGoesOnConductorWork));
    work = obj->data;
    work->unk_00 = 0;
    work->unk_02 = 0;
    obj->model[0] = Hu3DModelRead(0xA014D, 0x2D9);
    m232_drumAMdl = obj->model[1] = Hu3DModelRead(0x410009, 0x2D9);
    m232_drumBMdl = obj->model[2] = Hu3DModelRead(0x410008, 0x2D9);
    m232_drumZMdl = obj->model[3] = Hu3DModelRead(0x410007, 0x2D9);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DMotionAttrSet(obj->model[1], 2, 1);
    Hu3DMotionAttrSet(obj->model[2], 2, 1);
    Hu3DMotionAttrSet(obj->model[3], 2, 1);
    omObjMotionRead(obj, 4, 0x410009);
    omObjMotionRead(obj, 0, 0xA014F);
    omObjMotionRead(obj, 1, 0xA0150);
    omObjMotionRead(obj, 2, 0xA0151);
    omObjMotionRead(obj, 3, 0xA0152);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DMotionAttrSet(obj->model[2], 2, 2);
    Hu3DMotionAttrSet(obj->model[3], 2, 2);
    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 0, 1, 2);
    m232_SeqInit();
}

void m232_DrummerObjMain(omObjData *obj) {
    BeatGoesOnConductorWork *work = obj->data;
    BeatGoesOnNotes *notes;

    if (Hu3DMotion[Hu3DData[obj->model[1]].motId].unk02 - 2.0f <= Hu3DData[obj->model[1]].motTime) {
        Hu3DMotionAttrSet(obj->model[1], 2, 1);
    }
    if (Hu3DMotion[Hu3DData[obj->model[2]].motId].unk02 - 2.0f <= Hu3DData[obj->model[2]].motTime) {
        Hu3DMotionAttrSet(obj->model[2], 2, 1);
    }
    if (Hu3DMotion[Hu3DData[obj->model[3]].motId].unk02 - 2.0f <= Hu3DData[obj->model[3]].motTime) {
        Hu3DMotionAttrSet(obj->model[3], 2, 1);
    }
    notes = m232_sheetObj->data;
    if (MgFlowStatGet() == MG_STATE_START) {
        if (work->unk_02 >= 73) {
            notes->unk_16 = 1;
            notes->unk_17 = 1;
            work->unk_02 = 0;
        } else {
            work->unk_02++;
        }
    } else if (MgFlowStatGet() == MG_STATE_PLAY) {
        if (obj->work[0] == 6) {
            return;
        }
        if (obj->work[0] == 0) {
            m232_CameraHomeMove(33.0f);
            if (CZoom == 1060.0f && Center.z == 140.0f && CRot.x == -40.0f) {
                obj->work[0] = 1;
            }
        } else if (obj->work[0] == 5) {
            if (work->unk_02 >= 30) {
                HuAudSeqPlay(0x40);
                work->unk_02 = 0;
            } else {
                work->unk_02++;
            }
            switch (m232_cameraState) {
                case 0:
                    m232_CameraWideMove(63.5f);
                    if (CZoom == 2200.0f && Center.z == 380.0f && CRot.x == -30.0f) {
                        m232_cameraState = 1;
                    }
                    break;
                case 1:
                    m232_CameraCloseMove(63.5f);
                    if (CZoom == 700.0f && Center.z == 880.0f && CRot.x == -10.0f) {
                        m232_cameraState = 2;
                        obj->work[0] = 6;
                    }
                    break;
            }
        } else {
            notes->unk_08 = 1;
            if (m232_seqNo < 4 &&
                work->unk_00 >= m232_seqTbl[m232_seqNo].unk_02) {
                if (m232_seqTbl[m232_seqNo].button == A_BUTTON) {
                    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[3]].motId, 0, 1, 2);
                    Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                    obj->work[0] = 4;
                    notes->btnA[m232_seqNo] = 1;
                    notes->unk_0C = 1;
                    notes->unk_0A = A_BUTTON;
                } else if (m232_seqTbl[m232_seqNo].button == B_BUTTON) {
                    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[1]].motId, 0, 1, 2);
                    Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                    obj->work[0] = 2;
                    notes->btnB[m232_seqNo] = 1;
                    notes->unk_0C = 1;
                    notes->unk_0A = B_BUTTON;
                } else if (m232_seqTbl[m232_seqNo].button == Z_TRIG) {
                    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[2]].motId, 0, 1, 2);
                    Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                    obj->work[0] = 3;
                    notes->btnZ[m232_seqNo] = 1;
                    notes->unk_0C = 1;
                    notes->unk_0A = Z_TRIG;
                }
                work->unk_00 = 0;
                m232_seqNo++;
            } else {
                if (obj->work[0] != 1) {
                    if (Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 - 2.0f <= Hu3DData[obj->model[0]].motTime) {
                        Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 10, 1, 2);
                        Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                        obj->work[0] = 1;
                    }
                }
                if (obj->work[0] != 0) {
                    if (m232_seqNo == 3) {
                        HuAudSeqStop();
                    }
                    if (Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 - 2.0f <= Hu3DData[obj->model[0]].motTime) {
                        if (m232_seqNo >= 4) {
                            HuAudFXPlay(0x40A);
                            obj->work[0] = 5;
                            m232_seqLen = 4;
                            m232_seqNo = 0;
                            m232_SheetClear();
                            notes->unk_08 = 0;
                        } else {
                            obj->work[0] = 1;
                        }
                    }
                }
                work->unk_00++;
            }
            if (Hu3DData[obj->model[0]].motTime == Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 / 2.0f) {
                if (obj->work[0] == 4) {
                    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[4]].motId, 0, 1, 2);
                    Hu3DMotionSpeedSet(obj->model[1], 1.0f);
                    HuAudFXPlay(0x405);
                } else if (obj->work[0] == 2) {
                    Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[4]].motId, 0, 1, 2);
                    Hu3DMotionSpeedSet(obj->model[2], 1.0f);
                    HuAudFXPlay(0x406);
                } else if (obj->work[0] == 3) {
                    Hu3DMotionShiftSet(obj->model[3], Hu3DData[obj->motion[4]].motId, 0, 1, 2);
                    Hu3DMotionSpeedSet(obj->model[3], 1.0f);
                    HuAudFXPlay(0x407);
                }
            }
        }
    }
}

void m232_SeqInit(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        m232_seqTbl[i].button = m232_SeqBtnGet(i);
        if (i == 0) {
            m232_seqTbl[i].unk_02 = 26;
        } else {
            m232_seqTbl[i].unk_02 = 22;
        }
    }
    for (i = 4; i < 16; i++) {
        m232_seqTbl[i].button = 0;
        m232_seqTbl[i].unk_02 = 22;
    }
}

u16 m232_SeqBtnGet(s8 index) {
    u16 prev;
    u8 roll;

    if (index == 0) {
        prev = 0;
    } else {
        prev = m232_seqTbl[index - 1].button;
    }
    roll = rand8() % 30;
    if (roll < 10) {
        if (prev == A_BUTTON) {
            roll = rand8() % 20;
            if (roll < 10) {
                return B_BUTTON;
            } else {
                return Z_TRIG;
            }
        }
        return A_BUTTON;
    } else if (roll < 20) {
        if (prev == B_BUTTON) {
            roll = rand8() % 20;
            if (roll < 10) {
                return A_BUTTON;
            } else {
                return Z_TRIG;
            }
        }
        return B_BUTTON;
    } else if (prev == Z_TRIG) {
        roll = rand8() % 20;
        if (roll >= 10) {
            return B_BUTTON;
        }
        return A_BUTTON;
    }
    return Z_TRIG;
}

void m232_PlayerObjInit(omObjData *obj) {
    Vec positions[4] = {
        { 0.0f, -90.0f, 600.0f },
        { 600.0f, -90.0f, 0.0f },
        { 0.0f, -90.0f, -600.0f },
        { -600.0f, -90.0f, 0.0f },
    };
    MgPlayerWork *data;
    BeatGoesOnSpinWork *work;
    s8 chr;
    u32 model;
    s32 motion;

    chr = GwPlayer[m232_playerCreateNo].chr;
    model = omCharModelNoTbl[chr][0];
    motion = omCharMot2Tbl[chr][0];
    MgShadowAltSet(1);
    MgPlayerCreate(obj, model, motion, m232_playerCreateNo, 0x2C9, 0x2D9);
    data = obj->data;
    data->unkE8 = HuMemAllocTag(obj->mtncnt * sizeof(MgMotAttr), TAG_OVERLAY);
    data->unk5A = obj->model[0];
    data->unk5B = 1;
    data->unk158 = HuMemAllocTag(sizeof(BeatGoesOnSpinWork), TAG_OVERLAY);
    memset(data->unk158, 0, sizeof(BeatGoesOnSpinWork));
    work = data->unk158;
    obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
    obj->work[0] = 0;
    m232_standNo = m232_standOrderTbl[m232_standOrderNo][m232_playerCreateNo];
    obj->trans.x = positions[m232_standNo].x;
    obj->trans.y = positions[m232_standNo].y;
    obj->trans.z = positions[m232_standNo].z;
    work->unk_04 = m232_standNo * 90.0f;
    work->unk_00 = 0;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    if (m232_playerCreateNo == 0) {
        m232_standMdl = obj->model[2] = Hu3DModelRead(0x410006, 0x2D9);
    } else {
        obj->model[2] = Hu3DModelLink(m232_standMdl);
    }
    obj->model[3] = Hu3DModelLink(m232_drumAMdl);
    obj->model[4] = Hu3DModelLink(m232_drumBMdl);
    obj->model[5] = Hu3DModelLink(m232_drumZMdl);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[4], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[5], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DMotionAttrSet(obj->model[3], 2, 1);
    Hu3DMotionAttrSet(obj->model[4], 2, 1);
    Hu3DMotionAttrSet(obj->model[5], 2, 1);
    omObjMotionRead(obj, 8, 0x410009);
    obj->work[2] = 0;
    obj->model[6] = Hu3DModelRead(0x41000B, 0x81D);
    Hu3DModelScaleSet(obj->model[6], 1.5f, 1.0f, 1.0f);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0x55));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(obj, 7, CharMotionDataNumGet(chr, 0x33));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 0x3A));
    omObjMotionRead(obj, 9, CharMotionDataNumGet(chr, 0x36));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 0x56));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chr, 0x57));
    omObjMotionRead(obj, 5, CharMotionDataNumGet(chr, 0x58));
    omObjMotionRead(obj, 6, CharMotionDataNumGet(chr, 0x1A));
    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 0, 30, 2);
    obj->work[1] = 0;
    obj->func = m232_PlayerObjMain;
    m232_playerCreateNo++;
}

void m232_PlayerObjMain(omObjData *obj) {
    MgPlayerWork *data = obj->data;
    BeatGoesOnSpinWork *work = data->unk158;
    BeatGoesOnNotes *notes;
    BeatGoesOnPos pos;
    s32 i;
    s32 dir;
    u16 button;

    if (m232_drummerObj->work[0] != 6) {
        return;
    }
    if (mgPlayerObjTbl[0]->work[0] != 7 && mgPlayerObjTbl[1]->work[0] != 7 &&
        mgPlayerObjTbl[2]->work[0] != 7 && mgPlayerObjTbl[3]->work[0] != 7) {
        m232_turnF = 0;
    } else {
        for (i = 0; i < 4; i++) {
            if (mgPlayerObjTbl[i]->work[0] == 7) {
                m232_turnF = 1;
                break;
            }
        }
    }
    if (m232_turnF != 0) {
        if (m232_turnTimer > 120) {
            if (m232_playerAliveNum < 5) {
                if (m232_playerAliveNum >= 2) {
                    m232_CameraTurnUpdate(&m232_cameraTurnState, 348.0f);
                }
            }
        } else {
            m232_turnTimer++;
        }
    } else {
        m232_turnTimer = 0;
    }
    if (obj->trans.z < 600.0f && obj->work[0] != 7 && obj->work[0] != 8 && obj->work[0] != 9) {
        return;
    }
    notes = m232_sheetObj->data;
    switch (obj->work[0]) {
        case 0:
            if (work->unk_00 >= 10) {
                obj->work[0] = 1;
                work->unk_00 = 0;
            } else {
                work->unk_00++;
            }
            break;
        case 1:
            if (work->unk_00 >= 20) {
                obj->work[0] = 2;
                m232_fireState = 1;
                work->unk_00 = 0;
                notes->unk_08 = 1;
            } else {
                if (work->unk_00 == 0) {
                    notes->unk_04 = 20;
                    notes->unk_06 = 30;
                    notes->unk_0E = (s8)(m232_seqLen % 8) * 30 + 55;
                    if (m232_seqLen < 8) {
                        notes->unk_10 = 30;
                    } else {
                        notes->unk_10 = 50;
                    }
                    notes->unk_16 = notes->unk_17 = notes->unk_18 = 1;
                    for (i = 0; i < m232_seqLen; i++) {
                        notes->noteFlags[i] = 1;
                    }
                }
                work->unk_00++;
            }
            break;
        case 2:
            m232_DrumHitUpdate(obj, &m232_drumState);
            if (notes->unk_09 == 1) {
                button = m232_PlayerComInput(data);
                if (obj->work[1] == 0 && (button & (A_BUTTON | B_BUTTON | Z_TRIG))) {
                    if (button == A_BUTTON) {
                        Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[5]].motId, 0, 1, 2);
                        Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                        Hu3DMotionTimeSet(obj->model[0], 0.0f);
                        obj->work[1] = 5;
                        m232_drumState = 1;
                        if (m232_seqNo == m232_seqLen ||
                            m232_seqTbl[m232_seqNo].button == button) {
                            m232_SheetBtnSet(A_BUTTON);
                            obj->work[0] = 3;
                            notes->unk_0C = 1;
                            notes->unk_0A = A_BUTTON;
                        } else if (m232_seqTbl[m232_seqNo].button != A_BUTTON) {
                            m232_SheetBtnSet(A_BUTTON);
                            obj->work[0] = 4;
                            notes->unk_19 = 1;
                            notes->unk_0C = 1;
                            notes->unk_0A = A_BUTTON;
                        }
                    } else if (button == B_BUTTON) {
                        Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[3]].motId, 0, 1, 2);
                        Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                        Hu3DMotionTimeSet(obj->model[0], 0.0f);
                        obj->work[1] = 3;
                        m232_drumState = 2;
                        if (m232_seqNo == m232_seqLen ||
                            m232_seqTbl[m232_seqNo].button == button) {
                            m232_SheetBtnSet(B_BUTTON);
                            obj->work[0] = 3;
                            notes->unk_0C = 1;
                            notes->unk_0A = B_BUTTON;
                        } else if (m232_seqTbl[m232_seqNo].button != B_BUTTON) {
                            m232_SheetBtnSet(B_BUTTON);
                            obj->work[0] = 4;
                            notes->unk_19 = 1;
                            notes->unk_0C = 1;
                            notes->unk_0A = B_BUTTON;
                        }
                    } else if (button == Z_TRIG) {
                        Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[4]].motId, 0, 1, 2);
                        Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                        Hu3DMotionTimeSet(obj->model[0], 0.0f);
                        obj->work[1] = 4;
                        m232_drumState = 3;
                        if (m232_seqNo == m232_seqLen ||
                            m232_seqTbl[m232_seqNo].button == button) {
                            m232_SheetBtnSet(Z_TRIG);
                            obj->work[0] = 3;
                            notes->unk_0C = 1;
                            notes->unk_0A = Z_TRIG;
                        } else if (m232_seqTbl[m232_seqNo].button != Z_TRIG) {
                            m232_SheetBtnSet(Z_TRIG);
                            obj->work[0] = 4;
                            notes->unk_19 = 1;
                            notes->unk_0C = 1;
                            notes->unk_0A = Z_TRIG;
                        }
                    }
                }
            }
            if (obj->work[1] == 5 || obj->work[1] == 3 || obj->work[1] == 4) {
                if (Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 - 2.0f <= Hu3DData[obj->model[0]].motTime) {
                    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 0, 1, 2);
                    Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                    obj->work[1] = 0;
                }
            }
            m232_DrumHitUpdate(obj, &m232_drumState);
            m232_SheetPosGet(&pos);
            if (pos.x + 11 < notes->unk_04 && pos.y == notes->unk_06) {
                obj->work[0] = 4;
                work->unk_00 = 0;
                notes->unk_19 = 1;
                notes->unk_0C = 1;
                if (m232_seqNo == m232_seqLen) {
                    notes->unk_0A = D_JPAD;
                } else {
                    notes->unk_0A = U_JPAD;
                }
            }
            break;
        case 3:
            m232_DrumHitUpdate(obj, &m232_drumState);
            if (Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 - 2.0f <= Hu3DData[obj->model[0]].motTime) {
                Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 0, 1, 2);
                Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                obj->work[1] = 0;
            }
            m232_SheetPosGet(&pos);
            if (pos.y == notes->unk_06 && (pos.x + 11 < notes->unk_04 || notes->unk_04 == 280)) {
                if (m232_seqLen == m232_seqNo) {
                    if (m232_seqLen + 1 == 16) {
                        for (i = 0; i < 4; i++) {
                            if (mgPlayerObjTbl[i]->work[0] != 10) {
                                mgPlayerObjTbl[i]->work[0] = 9;
                                work->unk_00 = 0;
                            }
                        }
                    } else {
                        if (obj->work[1] != 0 &&
                            Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 - 2.0f > Hu3DData[obj->model[0]].motTime) {
                            break;
                        }
                        for (i = 0; i < 4; i++) {
                            if (mgPlayerObjTbl[i]->work[0] != 10) {
                                mgPlayerObjTbl[i]->work[0] = 7;
                                m232_musicStopF = 0;
                                m232_cameraTurnState = 0;
                                HuAudSeqStop();
                            }
                        }
                        Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[7]].motId, 0, 1, 2);
                        Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                        work->unk_00 = 0;
                        m232_seqNo = 0;
                        m232_seqLen++;
                    }
                } else {
                    m232_seqNo++;
                    obj->work[0] = 2;
                }
            }
            break;
        case 4:
            m232_DrumHitUpdate(obj, &m232_drumState);
            MgPlayerEffSet(obj, 6, obj->trans.x, -50.0f, obj->trans.z + 50.0f, 90.0f, 0.0f);
            Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[2]].motId, 0, 1, 2);
            Hu3DMotionSpeedSet(obj->model[0], 1.0f);
            obj->work[1] = 2;
            work->unk_00 = 0;
            m232_seqNo = 0;
            m232_playerAliveNum--;
            obj->work[0] = 5;
            break;
        case 5:
            if (Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 - 2.0f <= Hu3DData[obj->model[0]].motTime) {
                Hu3DMotionAttrSet(obj->model[0], 2, 1);
            } else if (Hu3DData[obj->model[0]].motTime == 10.0f) {
                Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(obj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(obj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                HuAudPlayerFXPlay(0x40C, 0);
            } else if (Hu3DData[obj->model[0]].motTime == 20.0f) {
                notes->unk_08 = 0;
                m232_SheetClear();
            } else if (Hu3DData[obj->model[0]].motTime == 50.0f) {
                m232_fireState = 2;
            }
            m232_DrumHitUpdate(obj, &m232_drumState);
            break;
        case 6:
            if (obj->trans.x < -450.0f) {
                for (i = 0; i < 6; i++) {
                    Hu3DModelAttrSet(obj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
                for (i = 0; i < 4; i++) {
                    Hu3DModelAttrSet(m232_smokeMdlTbl[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
                for (i = 0; i < 4; i++) {
                    if (obj == mgPlayerObjTbl[i]) {
                        obj->work[0] = 10;
                    } else if (mgPlayerObjTbl[i]->work[0] != 10) {
                        mgPlayerObjTbl[i]->work[0] = 7;
                        m232_musicStopF = 1;
                        m232_cameraTurnState = 0;
                        HuAudSeqStop();
                    }
                }
                m232_outDrumY = -90.0f;
                m232_outJumpAngle = 0.0f;
                m232_outStageZ = 0.0f;
            } else {
                m232_SmokeUpdate(obj);
                if (obj->trans.x == 0.0f) {
                    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[6]].motId, 0, 1, 2);
                    Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                    PlayerFXPlay(0x286, data->unk59);
                    HuAudPlayerFXPlay(0x409, 0);
                    omVibrate(data->unk59, 2, 2, 20);
                } else if (obj->trans.x < -200.0f && m232_playerAliveNum == 1) {
                    for (i = 0; i < 4; i++) {
                        if (mgPlayerObjTbl[i]->work[0] == 0) {
                            m232_mgFlow.resultType = MG_RESULT_WIN_1;
                            m232_mgFlow.winners[0] = i;
                            m232_mgFlow.winners[1] = 0xFF;
                            MgFlowStatSet(MG_STATE_FINISH);
                            break;
                        }
                    }
                }
                obj->trans.x -= 15.0f;
                obj->trans.y = sindf(m232_outJumpAngle) * 200.0f + -90.0f;
                m232_outJumpAngle += 5.0f;
                if (m232_outJumpAngle >= 180.0f) {
                    m232_outJumpAngle = 0.0f;
                }
                Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                m232_outDrumY -= 2.0f;
                m232_outStageZ += 15.0f;
                Hu3DModelPosSet(obj->model[2], 0.0f, -90.0f, m232_outStageZ + 600.0f);
                for (i = 3; i < 6; i++) {
                    Hu3DModelPosSet(obj->model[i], 0.0f, m232_outDrumY, 600.0f);
                }
                obj->rot.y -= 15.0f;
                if (obj->rot.y < -90.0f) {
                    obj->rot.y = -90.0f;
                }
            }
            break;
        case 7:
            m232_fireState = 0;
            m232_DrumHitUpdate(obj, &m232_drumState);
            if (work->unk_00 < 30) {
                if (work->unk_00 == 20) {
                    notes->unk_08 = 0;
                    m232_SheetClear();
                }
                if (m232_playerAliveNum == 1) {
                    work->unk_00 = 30;
                } else {
                    work->unk_00++;
                }
            } else if (work->unk_00 == 30) {
                if (m232_playerAliveNum >= 2 && !(HuAudStat & 2)) {
                    HuAudSeqPlay(0x40);
                }
                Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 0, 1, 2);
                Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                obj->work[1] = 0;
                work->unk_00++;
            } else {
                work->unk_00++;
                switch (m232_playerAliveNum) {
                    case 4:
                        work->unk_04 -= 0.92783505f;
                        if (work->unk_04 < 0.0f) {
                            work->unk_04 += 360.0f;
                        }
                        if (work->unk_00 > 20 && ABS((s32)work->unk_04 % 90) < 2) {
                            obj->work[0] = 0;
                            work->unk_00 = 0;
                            if (obj->trans.z > 590.0f) {
                                work->unk_04 = 0.0f;
                            } else if (obj->trans.z < -590.0f) {
                                work->unk_04 = 180.0f;
                            } else if (obj->trans.x < 0.0f) {
                                work->unk_04 = 270.0f;
                            } else {
                                work->unk_04 = 90.0f;
                            }
                        }
                        break;
                    case 3:
                        if (m232_musicStopF == 0) {
                            work->unk_04 -= 1.2371134f;
                        } else {
                            work->unk_04 -= 0.92783505f;
                        }
                        if (work->unk_04 < 0.0f) {
                            work->unk_04 += 360.0f;
                        }
                        if (work->unk_00 > 20 && ABS((s32)work->unk_04 % 120) < 2) {
                            obj->work[0] = 0;
                            work->unk_00 = 0;
                            if (obj->trans.z > 590.0f) {
                                work->unk_04 = 0.0f;
                            } else if (obj->trans.x < 0.0f) {
                                work->unk_04 = 240.0f;
                            } else {
                                work->unk_04 = 120.0f;
                            }
                        }
                        break;
                    case 2:
                        if (m232_musicStopF == 0) {
                            work->unk_04 -= 1.8556701f;
                        } else {
                            work->unk_04 -= 1.2371134f;
                        }
                        if (work->unk_04 < 0.0f) {
                            work->unk_04 += 360.0f;
                        }
                        if (work->unk_00 > 20 && ABS((s32)work->unk_04 % 180) < 2) {
                            obj->work[0] = 0;
                            work->unk_00 = 0;
                            if (obj->trans.z > 590.0f) {
                                work->unk_04 = 0.0f;
                            } else {
                                work->unk_04 = 180.0f;
                            }
                        }
                        break;
                    default:
                        work->unk_04 -= 2.5f;
                        if (work->unk_04 < 0.0f) {
                            work->unk_04 = 0.0f;
                        }
                        if (FABS(obj->trans.x) < 5.0f && FABS(obj->trans.z - 600.0f) < 5.0f) {
                            obj->trans.x = 0.0f;
                            obj->trans.z = 600.0f;
                            obj->work[0] = 8;
                            work->unk_00 = 0;
                            m232_cameraTurnState = 0;
                        }
                        break;
                }
                obj->trans.x = sindf(work->unk_04) * 600.0f;
                obj->trans.z = cosdf(work->unk_04) * 600.0f;
                for (i = 1; i < 6; i++) {
                    Hu3DModelPosSet(obj->model[i], obj->trans.x, obj->trans.y, obj->trans.z);
                }
            }
            break;
        case 8:
            MgFlowStatSet(MG_STATE_RESULT);
            if (mgFlowResultF != 0) {
                CharAnimCreate(obj->model[0], 1, GwPlayer[data->unk59].chr,
                                   CharMotionDataNumGet(GwPlayer[data->unk59].chr, 0xA5));
                switch (GwPlayer[data->unk59].chr) {
                    case 0:
                    default:
                        dir = 2;
                        break;
                    case 1:
                        dir = 3;
                        break;
                    case 2:
                        dir = 7;
                        break;
                    case 3:
                        dir = 4;
                        break;
                    case 4:
                        dir = 5;
                        break;
                    case 5:
                        dir = 6;
                        break;
                    case 6:
                        dir = 8;
                        break;
                    case 7:
                        dir = 9;
                        break;
                }
                HuAudCharVoicePlay((dir << 16) | 0x2F);
                Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[1]].motId, 0, 1, 2);
                Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                obj->work[1] = 1;
                GwPlayer[data->unk59].bonusCoin += 10;
                work->unk_00 = 0;
                obj->work[0] = 11;
            }
            break;
        case 9:
            m232_DrumHitUpdate(obj, &m232_drumState);
            if (obj->work[1] == 3 || obj->work[1] == 4 || obj->work[1] == 5) {
                if (Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 - 2.0f <= Hu3DData[obj->model[0]].motTime) {
                    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 0, 1, 2);
                    Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                    Hu3DMotionTimeSet(obj->model[0], 0.0f);
                    obj->work[1] = 0;
                }
            }
            if (obj->work[1] == 0) {
                m232_drawF = 1;
            }
            if (m232_drawF != 0 && work->unk_00 == 60) {
                for (i = 0; i < 4; i++) {
                    if (mgPlayerObjTbl[i]->work[1] == 0) {
                        Hu3DMotionShiftSet(mgPlayerObjTbl[i]->model[0],
                                           Hu3DData[mgPlayerObjTbl[i]->motion[9]].motId, 0, 1, 2);
                        Hu3DMotionSpeedSet(mgPlayerObjTbl[i]->model[0], 1.0f);
                        mgPlayerObjTbl[i]->work[1] = 2;
                    }
                }
                m232_drawF = 0;
            }
            if (work->unk_00 == 0) {
                m232_SheetClear();
                m232_mgFlow.resultType = MG_RESULT_DRAW;
                MgFlowStatSet(MG_STATE_FINISH);
            } else {
                if (work->unk_00 > 60 &&
                    Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 - 2.0f <= Hu3DData[obj->model[0]].motTime) {
                    Hu3DMotionAttrSet(obj->model[0], 2, 1);
                }
                if (work->unk_00 > 90 && (GMesStatGet() == 0 || (GMesStatGet() & GMES_STAT_TIMEEND))) {
                    MgFlowStatSet(MG_STATE_RESULT);
                }
            }
            work->unk_00++;
            work->unk_04 -= 1.0f;
            if (work->unk_04 < 0.0f) {
                work->unk_04 += 360.0f;
            }
            obj->trans.x = sindf(work->unk_04) * 600.0f;
            obj->trans.z = cosdf(work->unk_04) * 600.0f;
            for (i = 1; i < 6; i++) {
                Hu3DModelPosSet(obj->model[i], obj->trans.x, obj->trans.y, obj->trans.z);
            }
            m232_CameraOutMove(240.0f);
            break;
        case 10:
            break;
        case 11:
            if (Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 - 2.0f <= Hu3DData[obj->model[0]].motTime) {
                Hu3DMotionAttrSet(obj->model[0], 2, 1);
            }
            break;
    }
}

u16 m232_PlayerComInput(MgPlayerWork *data) {
    u16 button = 0;
    u8 roll;
    s32 chance;

    if (!(GwPlayer[data->unk59].stat & 1)) {
        return HuPadBtnDown[data->unk57];
    }
    if (m232_seqNo == m232_seqLen &&
        m232_seqTbl[m232_seqNo].button == 0) {
        button = m232_SeqBtnGet(m232_seqNo);
    } else {
        roll = rand8() * 100U / 256;
        switch (GwPlayer[data->unk59].cpu_difficulty) {
            case 1:
                chance = 65;
                break;
            case 3:
                chance = 95;
                break;
            case 0:
                chance = 50;
                break;
            case 2:
                chance = 85;
                break;
            default:
                chance = 65;
                break;
        }
        if (m232_seqNo < 5) {
            chance = 99;
        } else if (m232_seqNo >= 13) {
            if (GwPlayer[data->unk59].cpu_difficulty == 0) {
                chance = 45;
            } else {
                chance = 50;
            }
        } else if (m232_seqNo >= 9) {
            chance -= 5;
        }
        if (roll < chance) {
            button = m232_seqTbl[m232_seqNo].button;
        } else if (m232_seqTbl[m232_seqNo].button == A_BUTTON) {
            button = Z_TRIG;
            if (rand8() >> 7) {
                button = B_BUTTON;
            }
        } else if (m232_seqTbl[m232_seqNo].button == B_BUTTON) {
            button = A_BUTTON;
            if (rand8() >> 7) {
                button = Z_TRIG;
            }
        } else if (m232_seqTbl[m232_seqNo].button == Z_TRIG) {
            button = B_BUTTON;
            if (rand8() >> 7) {
                button = A_BUTTON;
            }
        }
    }
    return button;
}

void m232_SheetBtnSet(u16 button) {
    BeatGoesOnNotes *notes = (BeatGoesOnNotes *)m232_sheetObj->data;

    if (button == A_BUTTON) {
        notes->btnA[m232_seqNo] = 1;
    } else if (button == B_BUTTON) {
        notes->btnB[m232_seqNo] = 1;
    } else if (button == Z_TRIG) {
        notes->btnZ[m232_seqNo] = 1;
    }
    if (m232_seqNo == m232_seqLen) {
        notes->unk_18 = 0;
        m232_seqTbl[m232_seqNo].button = button;
    } else {
        notes->noteFlags[m232_seqNo] = 0;
    }
}

void m232_DrumHitUpdate(omObjData *obj, s8 *state) {
    MgPlayerWork *data = obj->data;

    if (Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 / 2.0f <= Hu3DData[obj->model[0]].motTime &&
        obj->work[2] == 0) {
        if (obj->work[0] == 3) {
            omVibrate(data->unk59, 5, 0, 5);
        } else if (obj->work[0] == 4) {
            omVibrate(data->unk59, 10, 0, 10);
        }
        switch (*state) {
            case 1:
                if (obj->work[1] == 5) {
                    Hu3DMotionShiftSet(obj->model[3], Hu3DData[obj->motion[8]].motId, 0, 1, 2);
                    Hu3DMotionSpeedSet(obj->model[3], 1.0f);
                    obj->work[2] = 1;
                    HuAudFXPlay(0x405);
                }
                break;
            case 2:
                if (obj->work[1] == 3) {
                    Hu3DMotionShiftSet(obj->model[4], Hu3DData[obj->motion[8]].motId, 0, 1, 2);
                    Hu3DMotionSpeedSet(obj->model[4], 1.0f);
                    obj->work[2] = 1;
                    HuAudFXPlay(0x406);
                }
                break;
            case 3:
                if (obj->work[1] == 4) {
                    Hu3DMotionShiftSet(obj->model[5], Hu3DData[obj->motion[8]].motId, 0, 1, 2);
                    Hu3DMotionSpeedSet(obj->model[5], 1.0f);
                    obj->work[2] = 1;
                    HuAudFXPlay(0x407);
                }
                break;
        }
    }
    if (Hu3DMotion[Hu3DData[obj->model[3]].motId].unk02 - 2.0f <= Hu3DData[obj->model[3]].motTime) {
        Hu3DMotionAttrSet(obj->model[3], 2, 1);
        Hu3DMotionTimeSet(obj->model[3], 0.0f);
        *state = 0;
        obj->work[2] = 0;
    } else if (Hu3DMotion[Hu3DData[obj->model[4]].motId].unk02 - 2.0f <= Hu3DData[obj->model[4]].motTime) {
        Hu3DMotionAttrSet(obj->model[4], 2, 1);
        Hu3DMotionTimeSet(obj->model[4], 0.0f);
        *state = 0;
        obj->work[2] = 0;
    } else if (Hu3DMotion[Hu3DData[obj->model[5]].motId].unk02 - 2.0f <= Hu3DData[obj->model[5]].motTime) {
        Hu3DMotionAttrSet(obj->model[5], 2, 1);
        Hu3DMotionTimeSet(obj->model[5], 0.0f);
        *state = 0;
        obj->work[2] = 0;
    }
}

void m232_CameraTurnUpdate(s8 *state, f32 speed) {
    switch (*state) {
        case 0:
            m232_CameraOutMove(speed / 2.0f);
            if (CZoom == 2200.0f && Center.z == 380.0f && CRot.x == -30.0f) {
                *state = 1;
            }
            break;
        case 1:
            if (m232_cameraTurnTimer > 40) {
                m232_cameraTurnTimer = 0;
                *state = 2;
            } else {
                m232_cameraTurnTimer++;
            }
            break;
        case 2:
            m232_CameraCloseMove(speed / 2.0f);
            if (CZoom == 700.0f && Center.z == 880.0f && CRot.x == -10.0f) {
                *state = 3;
            }
            break;
    }
}

void m232_SmokeUpdate(omObjData *obj) {
    MgPlayerWork *data = obj->data;
    s32 player = data->unk59;
    f32 scale;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (m232_smokeTimerTbl[player][i] >= 0) {
            if (m232_smokeTimerTbl[player][i] == 0) {
                Hu3DModelPosSet(m232_smokeMdlTbl[i], obj->trans.x, obj->trans.y, obj->trans.z);
                Hu3DModelAttrSet(m232_smokeMdlTbl[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            if (m232_smokeTimerTbl[player][i] < 8) {
                scale = m232_smokeScaleTbl[m232_smokeTimerTbl[player][i] / 2];
                Hu3DModelScaleSet(m232_smokeMdlTbl[i], scale, scale, 1.0f);
            }
            if (m232_smokeTimerTbl[player][i] >= 8) {
                m232_smokeTimerTbl[player][i] = -1;
            }
        }
        m232_smokeTimerTbl[player][i]++;
    }
}

void m232_WaterObjInit(omObjData *obj) {
    obj->func = m232_WaterObjMain;
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->model[0] = Hu3DModelRead(0x410005, 0x699);
    Hu3DModelVtxBufMake(obj->model[0]);
    Hu3DTexSizeGet("mizu_DEF", m232_waterTexSize);
    m232_waterScroll = 0.0f;
}

void m232_WaterObjMain(omObjData *obj) {
    if (omPauseChk() + omAllPauseF == 0) {
        m232_waterScroll += 0.2f;
    }
    Hu3DModelObjTexScroll(obj->model[0], 0.0f, m232_waterScroll, m232_waterTexSize[0],
                       m232_waterTexSize[1], "m232_001c-cube7", 0);
}

void m232_SheetObjInit(omObjData *obj) {
    BeatGoesOnNotes *notes;
    s16 sprAnim;
    s16 anim;
    s16 animA;
    s16 animB;
    s16 animZ;
    s32 i;
    s32 j;

    sprAnim = HuSprAnimDataRead(0x41000C);
    HuSprGrpMemberSet(m232_signGrp = HuSprGrpCreate(1, 0), 0, sprAnim, 0);
    HuSprAttrReset(m232_signGrp, 0, 0xFFFF);
    HuSprAttrSet(m232_signGrp, 0, 0x5000);
    m232_signY = 120;
    HuSprPosSet(m232_signGrp, 0, 160, m232_signY);
    obj->data = HuMemAllocTag(sizeof(BeatGoesOnNotes), TAG_OVERLAY);
    memset(obj->data, 0, sizeof(BeatGoesOnNotes));
    notes = obj->data;
    notes->unk_00 = 1.33333f;
    notes->unk_04 = 20;
    notes->unk_06 = 30;
    notes->unk_0E = 265;
    notes->unk_10 = 50;
    anim = HuSprAnimDataRead(0x410011);
    for (i = 0; i < 2; i++) {
        m232_sheetLineSprTbl[i] = espEntry(anim, 0, 1);
        espPriSet(m232_sheetLineSprTbl[i], 0x30);
        espPosSet(m232_sheetLineSprTbl[i], 160, i * 20 + 30);
        espTPLvlSet(m232_sheetLineSprTbl[i], 0x40);
        espDispOff(m232_sheetLineSprTbl[i]);
        notes->unk_16 = 0;
    }
    m232_hitMarkSpr = espEntry(HuSprAnimDataRead(0x410015), 0, 1);
    espPriSet(m232_cursorSpr, 0x10);
    espPosSet(m232_hitMarkSpr, notes->unk_12, notes->unk_14);
    espDispOff(m232_hitMarkSpr);
    notes->unk_19 = 0;
    m232_cursorSpr = espEntry(HuSprAnimDataRead(0x410014), 0, 1);
    espPriSet(m232_cursorSpr, 0x10);
    espPosSet(m232_cursorSpr, notes->unk_04, notes->unk_06);
    espDispOff(m232_cursorSpr);
    notes->unk_17 = 0;
    notes->unk_08 = 0;
    notes->unk_09 = 0;
    notes->unk_0C = 0;
    notes->unk_0A = 0;
    m232_noteMarkSpr = espEntry(HuSprAnimDataRead(0x410012), 0, 1);
    espPriSet(m232_noteMarkSpr, 0x20);
    espPosSet(m232_noteMarkSpr, notes->unk_0E, notes->unk_10);
    espDispOff(m232_noteMarkSpr);
    notes->unk_18 = 0;
    anim = HuSprAnimDataRead(0x410013);
    for (i = 0; i < 15; i++) {
        m232_noteSprTbl[i] = espEntry(anim, 0, 1);
        espPriSet(m232_noteSprTbl[i], 0x20);
        if (i < 8) {
            espPosSet(m232_noteSprTbl[i], i * 30 + 55, 30);
        } else {
            espPosSet(m232_noteSprTbl[i], (i - 8) * 30 + 55, 50);
        }
        espDispOff(m232_noteSprTbl[i]);
        notes->noteFlags[i] = 0;
    }
    animA = HuSprAnimDataRead(0x41000E);
    animB = HuSprAnimDataRead(0x41000F);
    animZ = HuSprAnimDataRead(0x410010);
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 8; i++) {
            m232_noteASprTbl[j * 8 + i] = espEntry(animA, 0, 1);
            espPriSet(m232_noteASprTbl[j * 8 + i], 0x20);
            espPosSet(m232_noteASprTbl[j * 8 + i], i * 30 + 55, j * 20 + 30);
            espDispOff(m232_noteASprTbl[j * 8 + i]);
            notes->btnA[j * 8 + i] = 0;
            m232_noteBSprTbl[j * 8 + i] = espEntry(animB, 0, 1);
            espPriSet(m232_noteBSprTbl[j * 8 + i], 0x20);
            espPosSet(m232_noteBSprTbl[j * 8 + i], i * 30 + 55, j * 20 + 30);
            espDispOff(m232_noteBSprTbl[j * 8 + i]);
            notes->btnB[j * 8 + i] = 0;
            m232_noteZSprTbl[j * 8 + i] = espEntry(animZ, 0, 1);
            espPriSet(m232_noteZSprTbl[j * 8 + i], 0x20);
            espPosSet(m232_noteZSprTbl[j * 8 + i], i * 30 + 55, j * 20 + 30);
            espDispOff(m232_noteZSprTbl[j * 8 + i]);
            notes->btnZ[j * 8 + i] = 0;
        }
    }
    obj->func = m232_SheetObjMain;
}

void m232_SheetObjMain(omObjData *obj) {
    BeatGoesOnNotes *notes;
    BeatGoesOnPos pos;
    f32 scale;
    s32 i;
    s32 j;

    if (omPauseChk() + omAllPauseF != 0) {
        espDispOff(m232_cursorSpr);
        espDispOff(m232_noteMarkSpr);
        espDispOff(m232_hitMarkSpr);
        for (i = 0; i < 2; i++) {
            espDispOff(m232_sheetLineSprTbl[i]);
        }
        for (i = 0; i < 15; i++) {
            espDispOff(m232_noteSprTbl[i]);
        }
        for (j = 0; j < 2; j++) {
            for (i = 0; i < 8; i++) {
                espDispOff(m232_noteASprTbl[j * 8 + i]);
                espDispOff(m232_noteBSprTbl[j * 8 + i]);
                espDispOff(m232_noteZSprTbl[j * 8 + i]);
            }
        }
        return;
    }
    notes = obj->data;
    espPosSet(m232_noteMarkSpr, notes->unk_0E, notes->unk_10);
    for (i = 0; i < 2; i++) {
        if (notes->unk_16 == 1) {
            espPriSet(m232_sheetLineSprTbl[i], 0x30);
            espDispOn(m232_sheetLineSprTbl[i]);
        } else {
            espDispOff(m232_sheetLineSprTbl[i]);
        }
    }
    if (notes->unk_17 == 1) {
        espDispOn(m232_cursorSpr);
    } else {
        espDispOff(m232_cursorSpr);
        m232_cursorX = 20.0f;
    }
    if (notes->unk_18 == 1) {
        espDispOn(m232_noteMarkSpr);
    } else {
        espDispOff(m232_noteMarkSpr);
    }
    if (notes->unk_19 == 1) {
        espDispOn(m232_hitMarkSpr);
    } else {
        espDispOff(m232_hitMarkSpr);
    }
    for (i = 0; i < 15; i++) {
        if (notes->noteFlags[i] == 1) {
            espDispOn(m232_noteSprTbl[i]);
        } else {
            espDispOff(m232_noteSprTbl[i]);
        }
    }
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 8; i++) {
            if (notes->btnA[j * 8 + i] == 1) {
                espDispOn(m232_noteASprTbl[j * 8 + i]);
            } else {
                espDispOff(m232_noteASprTbl[j * 8 + i]);
            }
            if (notes->btnB[j * 8 + i] == 1) {
                espDispOn(m232_noteBSprTbl[j * 8 + i]);
            } else {
                espDispOff(m232_noteBSprTbl[j * 8 + i]);
            }
            if (notes->btnZ[j * 8 + i] == 1) {
                espDispOn(m232_noteZSprTbl[j * 8 + i]);
            } else {
                espDispOff(m232_noteZSprTbl[j * 8 + i]);
            }
        }
    }
    if (notes->unk_08 == 0) {
        m232_pulseTimer = 90;
        espPosSet(m232_cursorSpr, notes->unk_04, notes->unk_06);
        m232_pulseAngle = 0.0f;
        espScaleSet(m232_noteMarkSpr, 1.0f, 1.0f);
        m232_noteScaleAngle = 0.0f;
        for (j = 0; j < 2; j++) {
            for (i = 0; i < 8; i++) {
                espScaleSet(m232_noteASprTbl[j * 8 + i], 1.0f, 1.0f);
                espScaleSet(m232_noteBSprTbl[j * 8 + i], 1.0f, 1.0f);
                espScaleSet(m232_noteZSprTbl[j * 8 + i], 1.0f, 1.0f);
            }
        }
        for (i = 0; i < 15; i++) {
            espScaleSet(m232_noteSprTbl[i], 1.0f, 1.0f);
        }
        return;
    }
    if (m232_seqNo == m232_seqLen) {
        m232_SheetPosGet(&pos);
        if (notes->unk_18 == 1 && ABS(notes->unk_04 - pos.x) <= 0 && pos.y == notes->unk_06 &&
            m232_pulseTimer != 0) {
            f32 pulse;

            m232_pulseTimer--;
            m232_pulseAngle += 30.0f;
            if (m232_pulseAngle >= 180.0f) {
                m232_pulseAngle = 0.0f;
            }
            pulse = sindf(m232_pulseAngle) * 0.5f + 1.0f;
            espScaleSet(m232_noteMarkSpr, pulse, pulse);
        } else {
            m232_cursorX += 1.33333f;
        }
    } else {
        m232_cursorX += 1.33333f;
    }
    if ((notes->unk_04 = m232_cursorX) >= 280) {
        if (notes->unk_06 == 30) {
            if (m232_seqLen + 1 == 8) {
                notes->unk_04 = 280;
                m232_cursorX = 280.0f;
            } else {
                notes->unk_04 = 40;
                m232_cursorX = 40.0f;
                if (m232_seqLen + 1 >= 9) {
                    notes->unk_06 += 20;
                }
            }
        } else {
            notes->unk_04 = 280;
        }
    }
    espPosSet(m232_cursorSpr, notes->unk_04, notes->unk_06);
    if (notes->unk_0C != 0) {
        if (m232_noteScaleAngle == 0.0f) {
            m232_noteHitNo = m232_seqNo;
        }
        if (notes->unk_19 != 0) {
            m232_noteScaleAngle += 36.0f;
            if (m232_noteScaleAngle >= 36.0f) {
                m232_noteScaleAngle = 36.0f;
                notes->unk_0C = 0;
            }
        } else {
            m232_noteScaleAngle += 36.0f;
            if (m232_noteScaleAngle >= 180.0f) {
                m232_noteScaleAngle = 0.0f;
                notes->unk_0C = 0;
            }
        }
        scale = sindf(m232_noteScaleAngle) + 1.0f;
        switch (notes->unk_0A) {
            case 0x8000:
                if (m232_drummerObj->work[0] != 6) {
                    espScaleSet(m232_noteASprTbl[m232_noteHitNo - 1], scale, scale);
                } else {
                    espScaleSet(m232_noteASprTbl[m232_noteHitNo], scale, scale);
                }
                break;
            case 0x4000:
                if (m232_drummerObj->work[0] != 6) {
                    espScaleSet(m232_noteBSprTbl[m232_noteHitNo - 1], scale, scale);
                } else {
                    espScaleSet(m232_noteBSprTbl[m232_noteHitNo], scale, scale);
                }
                break;
            case 0x2000:
                if (m232_drummerObj->work[0] != 6) {
                    espScaleSet(m232_noteZSprTbl[m232_noteHitNo - 1], scale, scale);
                } else {
                    espScaleSet(m232_noteZSprTbl[m232_noteHitNo], scale, scale);
                }
                break;
            case 0x800:
                espScaleSet(m232_noteSprTbl[m232_noteHitNo], scale, scale);
                break;
            case 0x400:
                espScaleSet(m232_noteMarkSpr, scale, scale);
                break;
        }
    }
    if (m232_drummerObj->work[0] == 6) {
        m232_SheetPosGet(&pos);
        if (ABS(notes->unk_04 - pos.x) <= 10 && pos.y == notes->unk_06) {
            notes->unk_09 = 1;
        } else {
            notes->unk_09 = 0;
        }
        if (notes->unk_09 == 1 && notes->unk_19 == 0) {
            notes->unk_12 = pos.x;
            notes->unk_14 = pos.y;
            espPosSet(m232_hitMarkSpr, notes->unk_12, notes->unk_14);
        }
    }
}

void m232_SheetPosGet(BeatGoesOnPos *pos) {
    if (m232_seqNo < 8) {
        pos->x = m232_seqNo * 30 + 55;
        pos->y = 30;
    } else {
        pos->x = (m232_seqNo - 8) * 30 + 55;
        pos->y = 50;
    }
}

void m232_SheetClear(void) {
    BeatGoesOnNotes *notes = (BeatGoesOnNotes *)m232_sheetObj->data;
    s32 i;

    notes->unk_19 = 0;
    notes->unk_18 = 0;
    notes->unk_17 = 0;
    notes->unk_16 = 0;
    for (i = 0; i < 16; i++) {
        // The note field only has 15 slots, but the button arrays have 16.
        if (i < 15) {
            notes->noteFlags[i] = 0;
        }
        notes->btnA[i] = 0;
        notes->btnB[i] = 0;
        notes->btnZ[i] = 0;
    }
}

Vec *m232_DirCalc(Vec *out, Vec *from, Vec *to) {
    Vec dir;
    f32 len;

    dir.x = to->x - from->x;
    dir.y = to->y - from->y;
    dir.z = to->z - from->z;
    len = HuSqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    if (len == 0.0f) {
        dir.x = dir.y = dir.z = 0.0f;
    } else {
        dir.x /= len;
        dir.y /= len;
        dir.z /= len;
    }
    *out = dir;
    return out;
}
