#include "common.h"
#include "gcc/memory.h"
#include "game/overlays/minigame.h"

extern s32 omCharModelNoTbl[][6];
extern u8 Hu3DBufNo;
extern u8 omAllPauseF;
extern f32 Hu3DMatAmbScale;
extern f32 Hu3DMatColScale;
extern omObjData *mgItemObjTbl[];

s32 m221_fireMdlIdx = 0;
u8 m221_playerOutTbl[4] = { 0, 0, 0, 0 };
f32 m221_beltWidthScale = 1.0f;
f32 m221_beltWidthTbl[4] = { 1000.0f, 1000.0f, 1000.0f, 1000.0f };
f32 m221_beltWidthPrevTbl[4] = { 1000.0f, 1000.0f, 1000.0f, 1000.0f };
f32 m221_flameRot = 0.0f;
Vec m221_playerStartPosTbl[4] = {
    { -200.0f, 250.0f, -250.0f },
    { 200.0f, 250.0f, -250.0f },
    { 200.0f, 250.0f, -650.0f },
    { -200.0f, 250.0f, -650.0f }
};
Vec2f m221_fireBeltPosTbl[4] = {
    { 0.0f, -200.0f },
    { 0.0f, -800.0f },
    { 0.0f, -600.0f },
    { 0.0f, -900.0f }
};
Vec m221_firePosTbl[4] = { 0 };
s32 m221_fireHideTbl[3] = { 1, 1, 1 };
MinigameFlow m221_mgFlow = {
    MG_STATE_OPENING, MINIGAME_4P, MG_TIMER_COUNT_DOWN, MG_TIME_DISP_COUNTDOWN, FALSE, MG_GAUGE_NONE, MG_RESULT_WIN_1, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    105, 900, -1, 75, 135
};
f32 m221_flameScaleTbl[13] = {
    0.0f, -0.5f, -1.0f, -1.5f, -2.0f, -2.5f, -3.0f, -3.5f, -4.0f, -4.5f, -5.0f, -5.5f, -6.0f
};
s32 m221_flameSeFTbl[13] = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };
f32 m221_flameSeFTblPad[2] = { 1.3f, 2.0f }; /* Unreferenced. */
s16 m221_dustMdl = -1;
u32 m221_playerMoveStepTbl[4] = { 0, 0, 0, 0 };
f32 m221_comStickScaleTbl[4] = { 0.75f, 0.8f, 0.9f, 1.0f };
s32 m221_comStateTbl[4] = { 0, 0, 0, 0 };
s32 m221_comChanceTbl[4] = { 0xA0, 0xC0, 0xE0, 0xFF };
s32 m221_comTimerTbl[4] = { 0, 0, 0, 0 };
s32 m221_dustTimerTbl[4][4] = {
    { 0, -2, -4, -6 },
    { 0, -2, -4, -6 },
    { 0, -2, -4, -6 },
    { 0, -2, -4, -6 }
};
f32 m221_dustScaleTbl[4] = { 0.5f, 1.0f, 1.5f, 2.0f };
s32 m221_flameNum = 0;
f32 m221_beltAccelTbl[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 m221_beltAccelTblPad[4] = { 0.0f, 0.0f, 0.0f, 0.0f }; /* Unreferenced. */
s32 m221_beltStopTimer = -1;
s32 m221_beltStopTimerPad = 0; /* Unreferenced. */
f32 m221_beltScrollTbl[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 m221_beltSpeedTbl[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 m221_beltSpeedStepTbl[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
s32 m221_beltChangeTimer = 0;
s32 m221_beltSpeedStepCnt = 20;
s32 m221_beltRunTimer = 0;
f32 m221_fireDirTbl[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 m221_fireTurnTbl[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 m221_fireSpeedTbl[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
s32 m221_fireWanderTimerTbl[4] = { 90, 90, 90, 90 };
f32 m221_fireScaleRot = 0.0f;
s32 m221_beltSeTbl[4] = { -1, -1, -1, -1 };
f32 m221_beltSpeedChoiceTbl[6] = { -3.0f, -2.0f, -1.25f, 1.25f, 2.0f, 3.0f };
s16 m221_beltSePitchTbl[6] = { 200, 0, -200, -200, 0, 200 };
s32 m221_beltStopCnt = 0;
f32 m221_wallLeftX = -480.0f;
f32 m221_wallRightX = 480.0f;

s32 m221_comStickSaveTbl[4][2] BSS;
s32 m221_padBtnSave BSS;
s32 m221_padBtnDownSave BSS;
s32 m221_padStkXSave BSS;
s32 m221_padStkYSave BSS;
s16 m221_fireMdlTbl[16] BSS;
Vec m221_flamePathTbl[6] BSS;
Vec m221_flamePosTbl[20] BSS;

void m221_ExitObjMain(omObjData *object);
void m221_MainObjMain(omObjData *object);
void m221_MainObjInit(omObjData *object);
void m221_BeltObjInit(omObjData *object);
void m221_PlayerInit(omObjData *object, s32 model, s32 motion, u16 player, f32 x, f32 y, f32 z);
void m221_PlayerFireHitCheck(omObjData *object);
void m221_PlayerMoveHook(omObjData *object, f32 *x, f32 *y, f32 *z);
void m221_PlayerComInput(omObjData *object);
void m221_Player0ObjInit(omObjData *object);
void m221_Player1ObjInit(omObjData *object);
void m221_Player2ObjInit(omObjData *object);
void m221_Player3ObjInit(omObjData *object);
void m221_FireMdlInit(void);
void m221_PlayerDustUpdate(omObjData *object, f32 x, f32 y, f32 z);
void m221_FlameObjInit(omObjData *object);
void m221_FlameObjMain(omObjData *object);
void m221_FlamePathCalc(omObjData *object);
void m221_BeltObjMain(omObjData *object);
f32 m221_FireDirUpdate(s32 index, omObjData *object);
void m221_FireUpdate(omObjData *object);
void m221_BeltSpeedChange(void);
void m221_BeltStop(void);
void m221_BeltShrink(omObjData *object);
void m221_BeltSpeedUpdate(omObjData *object);
s32 m221_BeltLaneGet(f32 x, f32 z);
s32 m221_LaneGet(f32 z);
void m221_BeltVtxUpdate(omObjData *object);
void m221_BeltTexUpdate(omObjData *object);

void m221_ObjectSetup(void) {
    u8 camIndex;

    MapCollInit(50);
    Hu3DQuadPoolInit(&mgQuadPool, 0x40);
    Hu3DSprModelInit(32);
    omInitObjMan(30, 0);
    omGameSysInit();
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 20.0f, 80.0f, 8000.0f);
    Hu3DGLightDirSet(1, -35.0f, -114.0f, -3.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    MgPlayerParamReset();
    mgPlayerFallInit = 0.0f;
    MgShadowAltSet(0);
    MgMapBaseSet(mgMapObjNum);
    mgMapObjTbl[mgMapObjNum++] = omAddObj(1, 1, 0, -1, m221_MainObjInit);
    mgMapObjTbl[mgMapObjNum++] = omAddObj(1, 16, 0, -1, m221_BeltObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(3, 16, 60, -1, m221_Player0ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(3, 16, 60, -1, m221_Player1ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(3, 16, 60, -1, m221_Player2ObjInit);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(3, 16, 60, -1, m221_Player3ObjInit);
    mgItemObjTbl[mgItemObjNum++] = omAddObj(2, 2, 0, -1, m221_FlameObjInit);
    mgItemObjTbl[mgItemObjNum++] = omAddObj(2, 2, 0, -1, m221_FlameObjInit);
    mgItemObjTbl[mgItemObjNum++] = omAddObj(2, 2, 0, -1, m221_FlameObjInit);
    mgItemObjTbl[mgItemObjNum++] = omAddObj(2, 2, 0, -1, m221_FlameObjInit);
    mgItemObjTbl[mgItemObjNum++] = omAddObj(2, 2, 0, -1, m221_FlameObjInit);
    mgItemObjTbl[mgItemObjNum++] = omAddObj(2, 2, 0, -1, m221_FlameObjInit);
    mgItemObjTbl[mgItemObjNum++] = omAddObj(2, 2, 0, -1, m221_FlameObjInit);
    mgItemObjTbl[mgItemObjNum++] = omAddObj(2, 2, 0, -1, m221_FlameObjInit);
    mgItemObjTbl[mgItemObjNum++] = omAddObj(2, 2, 0, -1, m221_FlameObjInit);
    mgItemObjTbl[mgItemObjNum++] = omAddObj(2, 2, 0, -1, m221_FlameObjInit);
    mgItemObjTbl[mgItemObjNum++] = omAddObj(2, 2, 0, -1, m221_FlameObjInit);
    mgItemObjTbl[mgItemObjNum++] = omAddObj(2, 2, 0, -1, m221_FlameObjInit);
    mgItemObjTbl[mgItemObjNum++] = omAddObj(2, 2, 0, -1, m221_FlameObjInit);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    mgPlayerAccel = 10.0f;
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    MgFlowInit(&m221_mgFlow);
    mgFlowSeqNo = 53;
    mgFlowSeqTime = 20;
    Hu3DGLightDirSet(1, 86.0f, 45.0f, 74.0f);
    m221_FireMdlInit();
}

void m221_ExitObjMain(omObjData *object) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

void m221_FlameIntroUpdate(omObjData *object) {
    omObjData *other;
    f32 scale;
    s32 i;

    if (WipeStatGet() == 0) {
        m221_FlamePathCalc(object);
        for (i = 0; i < mgItemObjNum; i++) {
            other = mgItemObjTbl[i];
            other->trans.x = m221_flamePosTbl[i].x;
            other->trans.y = m221_flamePosTbl[i].y;
            other->trans.z = m221_flamePosTbl[i].z;
            other->rot.y = atan2df(-other->trans.x, -other->trans.z);
            scale = m221_flameScaleTbl[i] += 0.125f;
            if (scale > 2.3f) {
                scale = 2.3f;
            }
            if (scale < 0.0f) {
                scale = 0.0f;
            }
            other->scale.x = other->scale.y = other->scale.z = scale;
            if (scale > 1.0f && m221_flameSeFTbl[i] == 0) {
                HuAudFXPlay(0x39F);
                m221_flameSeFTbl[i]++;
            }
        }
    }
}

void m221_FireFadeUpdate(omObjData *object) {
    f32 scale;
    s32 i;

    for (i = 0; i < 3; i++) {
        scale = Hu3DData[object->model[10 + i]].scale.x;
        scale -= 0.1f;
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        Hu3DModelScaleSet(object->model[10 + i], scale, scale, scale);
        Hu3DModelScaleSet(object->model[13 + i], scale, scale, scale);
    }
}

void m221_MainObjMain(omObjData *object) {
    MgPlayerWork *data;
    omObjData *player;
    s32 last;
    s32 count;
    s32 i;

    last = 0;
    if (omPauseChk() + omAllPauseF != 0) {
        return;
    }
    count = 0;
    for (i = 0; i < mgPlayerObjNum; i++) {
        if (m221_playerOutTbl[i] == 0) {
            count++;
            last = i;
        }
    }
    switch (MgFlowMain()) {
        case 0:
            if (MgFlowStatTimeGet() == 10) {
                HuAudSeqPlay(0);
            }
            break;
        case 2:
            if (count < 2) {
                MgFlowStatSet(MG_STATE_FINISH);
            }
            break;
        case 3:
            if (count != 1) {
                m221_mgFlow.resultType = MG_RESULT_DRAW;
            } else {
                m221_mgFlow.winners[0] = last;
                m221_mgFlow.resultType = MG_RESULT_WIN_1;
            }
            break;
        case 4:
            if (mgFlowResultF == 1) {
                if (m221_mgFlow.resultType == MG_RESULT_DRAW) {
                    for (i = 0; i < 4; i++) {
                        player = mgPlayerObjTbl[i];
                        if (m221_playerOutTbl[i] == 0) {
                            MgPlayerMotForceSet(player, 14);
                        }
                    }
                } else {
                    player = mgPlayerObjTbl[last];
                    MgPlayerMotForceSet(player, 13);
                    data = player->data;
                    GwPlayer[data->unk59].bonusCoin += 10;
                    HuAudCharVoicePlay(omCharModelNoTbl[GwPlayer[data->unk59].chr][0] | 0x2F);
                }
            }
            break;
        case 5:
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            object->func = m221_ExitObjMain;
            break;
    }
    for (i = 0; i < mgPlayerObjNum; i++) {
        ((MgPlayerWork *)mgPlayerObjTbl[i]->data)->unk60 = CRot.y;
    }
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
        object->func = m221_ExitObjMain;
    }
    Center.y = 150.0f;
    Center.z = -350.0f;
}

void m221_MainObjInit(omObjData *object) {
    MgMapWork *work;

    object->model[0] = Hu3DModelRead2(0x360005, 0xA9);
    object->trans.x = 100.0f;
    object->trans.y = 0.0f;
    object->trans.z = -1200.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    object->func = m221_MainObjMain;
    work->unk03 = 1;
    CZoom = 3736.0f;
    CRot.x = 319.0f;
    CRot.y = 0.0f;
    Center.x = 0.0f;
    Center.y = 50.0f;
    Center.z = -350.0f;
    MgMapTiltOn(object);
    MgMapBoxSet(object, 0.0f, -1500.0f, -1500.0f, 1500.0f, 1500.0f);
    MgMapFrictionSet(object, 0.2f);
    MgMapAccelSet(object, mgPlayerAccel);
    MgMapSlideSet(object, 25.0f);
    work->unk04 = 0;
    Hu3DModelObjAttrSet(object->model[0], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(object->model[0]);
    Hu3DModelVtxBufMake(object->model[0]);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

const char m221_fireEyesName[] = "c201_000-eyes";

void m221_BeltObjInit(omObjData *object) {
    MgMapWork *work;

    Hu3DMatAmbScale = 1.0f;
    Hu3DMatColScale = 1.0f;
    object->model[0] = Hu3DModelRead2(0x360000, 0xAA9);
    object->model[1] = Hu3DModelRead2(0x360001, 0xAA9);
    object->model[2] = Hu3DModelRead2(0x360000, 0xAA9);
    object->model[3] = Hu3DModelRead2(0x360001, 0xAA9);
    object->model[4] = Hu3DModelRead2(0x360002, 0xA99);
    object->model[5] = Hu3DModelRead2(0x360003, 0xA99);
    object->model[6] = Hu3DModelRead2(0x360003, 0xA99);
    object->model[7] = Hu3DModelRead2(0x360004, 0xA99);
    object->model[8] = Hu3DModelRead2(0x360004, 0xA99);
    Hu3DMatAmbScale = 1.0f;
    Hu3DMatColScale = 1.0f;
    object->model[9] = Hu3DModelRead2(0x360006, 0x299);
    object->model[10] = m221_fireMdlTbl[m221_fireMdlIdx++];
    object->model[11] = m221_fireMdlTbl[m221_fireMdlIdx++];
    object->model[12] = m221_fireMdlTbl[m221_fireMdlIdx++];
    Hu3DModelObjAttrSet(object->model[10], 0x70000000, 0);
    Hu3DModelObjAttrSet(object->model[11], 0x70000000, 0);
    Hu3DModelObjAttrSet(object->model[12], 0x70000000, 0);
    Hu3DMotionNoMotSet(object->model[10], Hu3DData[object->model[10]].motId, m221_fireEyesName, 0x4C, 0x46);
    Hu3DMotionNoMotSet(object->model[11], Hu3DData[object->model[11]].motId, m221_fireEyesName, 0x4C, 0x46);
    Hu3DMotionNoMotSet(object->model[12], Hu3DData[object->model[12]].motId, m221_fireEyesName, 0x4C, 0x46);
    object->model[13] = Hu3DModelRead2(0x360007, 0xAC9);
    object->model[14] = Hu3DModelLink(object->model[13]);
    object->model[15] = Hu3DModelLink(object->model[13]);
    Hu3DModelObjAttrSet(object->model[13], 0x80000000, 0x80000000);
    Hu3DModelObjAttrSet(object->model[14], 0x80000000, 0x80000000);
    Hu3DModelObjAttrSet(object->model[15], 0x80000000, 0x80000000);
    Hu3DModelRemakeStatic(object->model[13]);
    Hu3DModelRemakeStatic(object->model[14]);
    Hu3DModelRemakeStatic(object->model[15]);
    object->trans.x = 0.0f;
    object->trans.y = 0.0f;
    object->trans.z = 0.0f;
    object->rot.y = 0.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    object->func = m221_BeltObjMain;
    work->unk03 = 1;
    MgMapBlockSet(object, 250.0f, 250.0f, -550.0f, -1050.0f, 550.0f, 150.0f);
    Hu3DModelObjAttrSet(object->model[0], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(object->model[0]);
    Hu3DModelVtxBufMake(object->model[0]);
    Hu3DModelObjAttrSet(object->model[1], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(object->model[1]);
    Hu3DModelVtxBufMake(object->model[1]);
    Hu3DModelObjAttrSet(object->model[2], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(object->model[2]);
    Hu3DModelVtxBufMake(object->model[2]);
    Hu3DModelObjAttrSet(object->model[3], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(object->model[3]);
    Hu3DModelVtxBufMake(object->model[3]);
    Hu3DModelPosSet(object->model[1], 0.0f, 0.0f, -300.0f);
    Hu3DModelPosSet(object->model[2], 0.0f, 0.0f, -600.0f);
    Hu3DModelPosSet(object->model[3], 0.0f, 0.0f, -900.0f);
    MgMapTiltOn(object);
    MgMapFrictionSet(object, 0.3f);
    MgMapSlideSet(object, 15.0f);
    MgObjScaleSet(object, 1.0f, 1.0f, 1.0f);
    work->unk04 = 1;
    Hu3DModelPosSet(object->model[4], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(object->model[5], 480.0f, 150.0f, 165.0f);
    Hu3DModelPosSet(object->model[6], -480.0f, 150.0f, 165.0f);
    Hu3DModelPosSet(object->model[7], 430.0f, 220.0f, 155.0f);
    Hu3DModelPosSet(object->model[8], -430.0f, 220.0f, 155.0f);
    Hu3DModelPosSet(object->model[9], 0.0f, 0.0f, -450.0f);
    Hu3DModelScaleSet(object->model[9], 1.1f, 1.0f, 0.8f);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    m221_BeltTexUpdate(object);
}

void m221_PlayerInit(omObjData *object, s32 model, s32 motion, u16 player, f32 x, f32 y, f32 z) {
    MgPlayerWork *data;
    s32 chr;
    s32 i;
    s32 tag;

    tag = 0xA99;
    Hu3DMatAmbScale = 1.0f;
    Hu3DMatColScale = 1.0f;
    MgPlayerCreate(object, model, motion, player, tag, tag);
    data = object->data;
    chr = GwPlayer[data->unk59].chr;
    Hu3DMatAmbScale = 1.0f;
    Hu3DMatColScale = 1.0f;
    object->model[3] = Hu3DModelRead(3, 0x89D);
    object->model[4] = Hu3DModelRead(4, 0x89D);
    object->model[6] = Hu3DModelRead(5, 0x89D);
    object->model[5] = Hu3DModelRead(6, 0x89D);
    object->model[7] = Hu3DModelRead(8, 0x89D);
    object->model[8] = Hu3DModelRead(7, 0x89D);
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(chr, 0), 1, 0);
    MgPlayerMotLoad(object, 5, CharMotionDataNumGet(chr, 3), 0, 0);
    MgPlayerMotLoad(object, 1, CharMotionDataNumGet(chr, 1), 1, 0);
    MgPlayerMotLoad(object, 2, CharMotionDataNumGet(chr, 2), 1, 0);
    MgPlayerMotLoad(object, 6, CharMotionDataNumGet(chr, 4), 1, 19);
    MgPlayerMotLoad(object, 8, CharMotionDataNumGet(chr, 6), 1, 27);
    MgPlayerMotLoad(object, 17, CharMotionDataNumGet(chr, 14), 1, 15);
    MgPlayerMotLoad(object, 32, CharMotionDataNumGet(chr, 34), 0, 0);
    MgPlayerMotLoad(object, 18, CharMotionDataNumGet(chr, 15), 2, 0);
    MgPlayerMotLoad(object, 21, CharMotionDataNumGet(chr, 31), 0, 0);
    MgPlayerMotLoad(object, 3, CharMotionDataNumGet(chr, 29), 1, 0);
    MgPlayerMotLoad(object, 4, CharMotionDataNumGet(chr, 30), 1, 0);
    MgPlayerMotLoad(object, 30, CharMotionDataNumGet(chr, 32), 2, 0);
    MgPlayerMotLoad(object, 31, CharMotionDataNumGet(chr, 33), 2, 0);
    MgPlayerMotRead(object, 13, CharMotionDataNumGet(chr, 47), 1, 120);
    MgPlayerMotRead(object, 14, CharMotionDataNumGet(chr, 54), 1, 120);
    MgPlayerMotRead(object, 38, CharMotionDataNumGet(chr, 26), 1, 0);
    for (i = 10; i < 14; i++) {
        if (m221_dustMdl < 0) {
            object->model[i] = m221_dustMdl = Hu3DModelRead(0x10014, 0x89D);
        } else {
            object->model[i] = Hu3DModelLink(m221_dustMdl);
        }
    }
    object->trans.x = x;
    object->trans.y = y;
    object->trans.z = z;
    data = object->data;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    MgPlayerMapAttrSet(object, 0, 2);
    MgPlayerMapAttrSet(object, 1, 2);
    MgPlayerHookSet(data, 0, (void *)m221_PlayerComInput);
    MgPlayerHookSet(data, 1, (void *)m221_PlayerFireHitCheck);
    MgPlayerHookSet(data, 20, (void *)m221_PlayerMoveHook);
}

s32 m221_PlayerHitHook(void) {
    return 1;
}

void m221_PlayerFireHitCheck(omObjData *object) {
    MgPlayerWork *data;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 player;
    s32 hit;
    s32 i;

    data = object->data;
    player = data->unk59;
    hit = FALSE;
    if (m221_playerOutTbl[player] == 0) {
        for (i = 0; i < 3; i++) {
            dx = object->trans.x - m221_firePosTbl[i].x;
            dy = object->trans.y - m221_firePosTbl[i].y;
            dz = object->trans.z - m221_firePosTbl[i].z;
            if (HuSqrtf(dx * dx + dy * dy + dz * dz) < data->unk48 + 40.0f) {
                hit = TRUE;
                break;
            }
        }
        if (data->unk53[0] == 0 || hit == TRUE) {
            m221_playerOutTbl[player] = 1;
            MgPlayerMotForceSet(object, 0x26);
            data->unk50 |= 0x400;
            data->unk38 = -mgPlayerJumpPower;
            Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            HuAudPlayerFXPlay(0x39D, data->unk59);
            PlayerFXPlay(0x286, data->unk59);
            omVibrate(data->unk59, 2, 2, 20);
        }
    }
    if (GwPlayer[data->unk59].stat & 1) {
        HuPadBtnDown[data->unk57] = m221_padBtnDownSave;
        HuPadBtn[data->unk57] = m221_padBtnSave;
        HuPadStkX[data->unk57] = m221_padStkXSave;
        HuPadStkY[data->unk57] = m221_padStkYSave;
    }
}

void m221_PlayerMoveHook(omObjData *object, f32 *x, f32 *y, f32 *z) {
    MgPlayerWork *data;
    MgMapWork *stageData;
    omObjData *stage;
    f32 velY;
    s16 seId;

    data = object->data;
    stage = mgMapObjTbl[1];
    if (HuSqrtf(*x * *x + *z * *z) > 2000.0f) {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[10], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[11], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[12], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[13], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        return;
    }
    stageData = stage->data;
    data->unk3C = atan2df(*x - stage->trans.x, *z - stage->trans.z);
    data->unk40 = 25.0f;
    velY = data->unk38;
    if (velY > mgPlayerFallMax) {
        velY = mgPlayerFallMax;
    }
    *y += velY * velY * (data->unk38 >= 0.0f ? -35.0f : 35.0f);
    if (*x > stageData->unkA0 && *x < stageData->unkA8 && *z > stageData->unkA4 && *z < stageData->unkA8) {
        if (*y <= stageData->unk14) {
            data->unk38 = -mgPlayerJumpPower;
            *y = stageData->unk14;
            switch (m221_playerMoveStepTbl[data->unk59]) {
                case 0:
                    seId = 0x39E;
                    break;
                case 1:
                    seId = 0x3A0;
                    break;
                case 2:
                    seId = 0x3A1;
                    break;
                case 3:
                    seId = 0x3A2;
                    break;
                case 4:
                default:
                    seId = 0x3A3;
                    break;
            }
            HuAudPlayerFXPlay(seId, data->unk59);
            m221_playerMoveStepTbl[data->unk59]++;
        }
    } else if (*y <= 0.0f) {
        data->unk38 = -mgPlayerJumpPower;
        *y = 0.0f;
        switch (m221_playerMoveStepTbl[data->unk59]) {
            case 0:
                seId = 0x39E;
                break;
            case 1:
                seId = 0x3A0;
                break;
            case 2:
                seId = 0x3A1;
                break;
            case 3:
                seId = 0x3A2;
                break;
            case 4:
            default:
                seId = 0x3A3;
                break;
        }
        HuAudPlayerFXPlay(seId, data->unk59);
        m221_playerMoveStepTbl[data->unk59]++;
    }
    data->unk38 += mgPlayerGravity * 0.6f;
    m221_PlayerDustUpdate(object, *x, *y, *z);
}

// CPU input logic. minX doubles as the search angle and dist as the lane width third; these reused
// locals and the do-while around the player load are needed for matching register allocation.
void m221_PlayerComInput(omObjData *object) {
    MgPlayerWork *data;
    MgMapWork *stageData;
    omObjData *stage;
    omObjData *other;
    Vec dir;
    s32 difficulty;
    s32 player;
    s32 pad;
    s32 state;
    s32 nearest;
    s32 i;
    f32 candDist;
    f32 x;
    f32 y;
    f32 z;
    f32 minX;
    f32 maxX;
    f32 minZ;
    f32 maxZ;
    f32 dist;
    f32 minDist;
    f32 bestAngle;
    f32 candAngle;
    f32 rotY;

    data = object->data;
    do {
        player = data->unk59;
    } while (0);
    pad = data->unk57;
    if (MgFlowStatGet() == MG_STATE_FINISH) {
        data->unk3C *= 0.8f;
    }
    if (!(GwPlayer[data->unk59].stat & 1)) {
        return;
    }
    m221_padBtnDownSave = HuPadBtnDown[pad];
    m221_padBtnSave = (u16)HuPadBtn[pad];
    m221_padStkXSave = HuPadStkX[pad];
    m221_padStkYSave = HuPadStkY[pad];
    HuPadStkY[pad] = 0;
    HuPadStkX[pad] = 0;
    HuPadBtnDown[pad] = 0;
    HuPadBtn[pad] = 0;
    if (m221_playerOutTbl[player] == 1) {
        return;
    }
    stage = mgMapObjTbl[1];
    stageData = stage->data;
    difficulty = GwPlayer[data->unk59].cpu_difficulty;
    m221_BeltLaneGet(object->trans.x, object->trans.z);
    HuPadStkY[pad] = 0;
    HuPadStkX[pad] = 0;
    HuPadBtnDown[pad] = 0;
    dist = m221_beltWidthTbl[0] / 3.0f;
    if (m221_comStateTbl[player] == 32 && data->unk38 != 1000.0f) {
        HuPadStkX[pad] = m221_comStickSaveTbl[player][0];
        HuPadStkY[pad] = m221_comStickSaveTbl[player][1];
        HuPadBtn[pad] |= A_BUTTON;
        for (i = 0; i < 4; i++) {
            if (m221_playerOutTbl[i] != 1) {
                if (i != player) {
                    other = mgPlayerObjTbl[i];
                    x = other->trans.x - object->trans.x;
                    z = other->trans.z - object->trans.z;
                    if (HuSqrtf(x * x + z * z) < 2.0f * data->unk48) {
                        HuPadBtnDown[pad] |= Z_TRIG;
                    }
                }
            }
        }
        return;
    }
    m221_comTimerTbl[player]++;
    x = object->trans.x;
    z = object->trans.z;
    if (m221_comStateTbl[player] == 4) {
        minX = stage->trans.x + stageData->unkA0 + dist;
        maxX = stage->trans.x + stageData->unkA8 - dist;
        minZ = stage->trans.z + stageData->unkA4 + 200.0f;
        maxZ = stage->trans.z + stageData->unkAC - 200.0f;
    } else if (m221_comStateTbl[player] == 8) {
        minX = stage->trans.x + stageData->unkA0 + dist;
        maxX = stage->trans.x + stageData->unkA8 - dist;
        minZ = stage->trans.z + stageData->unkA4 + 300.0f;
        maxZ = stage->trans.z + stageData->unkAC - 300.0;
    } else {
        minX = stage->trans.x + stageData->unkA0 + 200.0f;
        maxX = stage->trans.x + stageData->unkA8 - 200.0f;
        minZ = stage->trans.z + stageData->unkA4 + 200.0f;
        maxZ = stage->trans.z + stageData->unkAC - 200.0f;
    }
    state = 0;
    if (x < minX) {
        HuPadStkX[pad] = m221_comStickScaleTbl[difficulty] * 60.0f;
        state = 4;
        m221_comStickSaveTbl[player][0] = HuPadStkX[pad];
    } else if (x > maxX) {
        HuPadStkX[pad] = m221_comStickScaleTbl[difficulty] * -60.0f;
        state = 4;
        m221_comStickSaveTbl[player][0] = HuPadStkX[pad];
    }
    if (z < minZ) {
        HuPadStkY[pad] = m221_comStickScaleTbl[difficulty] * -60.0f;
        state = 8;
        m221_comStickSaveTbl[player][1] = HuPadStkY[pad];
    } else if (z > maxZ) {
        HuPadStkY[pad] = m221_comStickScaleTbl[difficulty] * 60.0f;
        state = 8;
        m221_comStickSaveTbl[player][1] = HuPadStkY[pad];
    }
    if (state != 0) {
        m221_comStateTbl[player] = state;
        if (m221_comTimerTbl[player] > 60 && m221_comChanceTbl[difficulty] / 4.0f >= rand8()) {
            HuPadBtnDown[pad] |= A_BUTTON;
            m221_comStateTbl[player] = 32;
            m221_comTimerTbl[player] = 0;
        }
        return;
    }
    minDist = 2000.0f;
    nearest = -1;
    for (i = 0; i < 3; i++) {
        if (m221_fireHideTbl[i] == 0) {
            x = object->trans.x - m221_firePosTbl[i].x;
            y = object->trans.y - m221_firePosTbl[i].y;
            z = object->trans.z - m221_firePosTbl[i].z;
            dist = HuSqrtf(x * x + y * y + z * z);
            if (dist < minDist) {
                minDist = dist;
                nearest = i;
            }
        }
    }
    if (minDist < data->unk48 + 40.0f + 200.0f) {
        bestAngle = -1.0f;
        candAngle = -1.0f;
        minDist = 10.0f;
        candDist = 10.0f;
        for (minX = 0.0f; minX < 360.0f; minX += 60.0f) {
            x = sindf(minX) * (data->unk48 + 40.0f + 200.0f) + object->trans.x;
            z = cosdf(minX) * (data->unk48 + 40.0f + 200.0f) + object->trans.z;
            if (m221_BeltLaneGet(x, z) != -1) {
                for (i = 0; i < 3; i++) {
                    f32 dx;
                    f32 dz;

                    dx = x - m221_firePosTbl[i].x;
                    dz = z - m221_firePosTbl[i].z;
                    dist = HuSqrtf(dx * dx + dz * dz);
                    if (dist < data->unk48 + 40.0f + 200.0f) {
                        candAngle = -1.0f;
                        candDist = 10.0f;
                        break;
                    }
                    if (dist > candDist) {
                        candDist = dist;
                        candAngle = minX;
                    }
                }
                if (candDist > minDist) {
                    minDist = candDist;
                    bestAngle = candAngle;
                }
            }
        }
        if (bestAngle > 0.0f) {
            dir.x = sindf(bestAngle);
            dir.z = cosdf(bestAngle);
        } else {
            dir.x = object->trans.x - m221_firePosTbl[nearest].x;
            dir.y = object->trans.y - m221_firePosTbl[nearest].y;
            dir.z = object->trans.z - m221_firePosTbl[nearest].z;
            MapVecNormalize(&dir);
        }
        HuPadStkX[pad] = dir.x * 60.0f * m221_comStickScaleTbl[difficulty];
        HuPadStkY[pad] = -dir.z * 60.0f * m221_comStickScaleTbl[difficulty];
        m221_comStateTbl[player] = 2;
        return;
    }
    nearest = -1;
    minDist = 2000.0f;
    if (m221_comChanceTbl[difficulty] >= rand8()) {
        for (i = 0; i < 4; i++) {
            if (m221_playerOutTbl[i] != 1) {
                if (i != player) {
                    other = mgPlayerObjTbl[i];
                    x = object->trans.x - other->trans.x;
                    y = object->trans.y - other->trans.y;
                    z = object->trans.z - other->trans.z;
                    dist = HuSqrtf(x * x + y * y + z * z);
                    if (dist < minDist) {
                        minDist = dist;
                        nearest = i;
                    }
                    if (dist < 2.0f * data->unk48 + 80.0f) {
                        rotY = data->unk3C;
                        if (MgDirDot(x, z, sindf(rotY), cosdf(rotY)) < -0.8f) {
                            HuPadBtnDown[pad] = B_BUTTON;
                            m221_comStateTbl[player] = 16;
                            break;
                        }
                    }
                }
            }
        }
        if (nearest != -1 && HuPadBtnDown[pad] == 0) {
            other = mgPlayerObjTbl[nearest];
            dir.x = object->trans.x - other->trans.x;
            dir.y = 0.0f;
            dir.z = object->trans.z - other->trans.z;
            MapVecNormalize(&dir);
            HuPadStkX[pad] = -dir.x * 60.0f * m221_comStickScaleTbl[difficulty];
            HuPadStkY[pad] = dir.z * 60.0f * m221_comStickScaleTbl[difficulty];
            m221_comStateTbl[player] = 16;
        }
    }
    switch (m221_comStateTbl[player]) {
        case 4:
        case 8:
            if (m221_comTimerTbl[player] > 60 && m221_comChanceTbl[difficulty] / 4.0f >= rand8()) {
                HuPadBtnDown[pad] |= A_BUTTON;
                m221_comStateTbl[player] = 32;
                m221_comTimerTbl[player] = 0;
            }
            break;
        default:
            m221_comStickSaveTbl[player][0] = 0;
            m221_comStickSaveTbl[player][1] = 0;
            break;
    }
    m221_comTimerTbl[player]++;
}

void m221_Player0ObjInit(omObjData *object) {
    MgPlayerWork *data;
    s32 motion;
    s32 model;
    s32 i;

    motion = omCharModelNoTbl[GwPlayer[0].chr][1];
    model = omCharModelNoTbl[GwPlayer[0].chr][0];
    m221_PlayerInit(object, model, motion, 0, 0.0f, 250.0f, -500.0f);
    data = object->data;
    i = rand8() & 3;
    object->trans.x = m221_playerStartPosTbl[i].x;
    object->trans.y = m221_playerStartPosTbl[i].y;
    object->trans.z = m221_playerStartPosTbl[i].z;
    m221_playerStartPosTbl[i].x = m221_playerStartPosTbl[i].y = m221_playerStartPosTbl[i].z = 0.0f;
    data->unk3C = i * 90.0f + 135.0f;
}

void m221_Player1ObjInit(omObjData *object) {
    MgPlayerWork *data;
    s32 motion;
    s32 model;
    s32 i;

    motion = omCharModelNoTbl[GwPlayer[1].chr][1];
    model = omCharModelNoTbl[GwPlayer[1].chr][0];
    m221_PlayerInit(object, model, motion, 1, 0.0f, 250.0f, -300.0f);
    data = object->data;
    do {
        i = rand8() & 3;
    } while (m221_playerStartPosTbl[i].x == 0.0f);
    object->trans.x = m221_playerStartPosTbl[i].x;
    object->trans.y = m221_playerStartPosTbl[i].y;
    object->trans.z = m221_playerStartPosTbl[i].z;
    m221_playerStartPosTbl[i].x = m221_playerStartPosTbl[i].y = m221_playerStartPosTbl[i].z = 0.0f;
    data->unk3C = i * 90.0f + 135.0f;
}

void m221_Player2ObjInit(omObjData *object) {
    MgPlayerWork *data;
    s32 motion;
    s32 model;
    s32 i;

    motion = omCharModelNoTbl[GwPlayer[2].chr][1];
    model = omCharModelNoTbl[GwPlayer[2].chr][0];
    m221_PlayerInit(object, model, motion, 2, 0.0f, 250.0f, -300.0f);
    data = object->data;
    do {
        i = rand8() & 3;
    } while (m221_playerStartPosTbl[i].x == 0.0f);
    object->trans.x = m221_playerStartPosTbl[i].x;
    object->trans.y = m221_playerStartPosTbl[i].y;
    object->trans.z = m221_playerStartPosTbl[i].z;
    m221_playerStartPosTbl[i].x = m221_playerStartPosTbl[i].y = m221_playerStartPosTbl[i].z = 0.0f;
    data->unk3C = i * 90.0f + 135.0f;
}

void m221_Player3ObjInit(omObjData *object) {
    MgPlayerWork *data;
    s32 motion;
    s32 model;
    s32 i;

    motion = omCharModelNoTbl[GwPlayer[3].chr][1];
    model = omCharModelNoTbl[GwPlayer[3].chr][0];
    m221_PlayerInit(object, model, motion, 3, 0.0f, 250.0f, -300.0f);
    data = object->data;
    do {
        i = rand8() & 3;
    } while (m221_playerStartPosTbl[i].x == 0.0f);
    object->trans.x = m221_playerStartPosTbl[i].x;
    object->trans.y = m221_playerStartPosTbl[i].y;
    object->trans.z = m221_playerStartPosTbl[i].z;
    m221_playerStartPosTbl[i].x = m221_playerStartPosTbl[i].y = m221_playerStartPosTbl[i].z = 0.0f;
    data->unk3C = i * 90.0f + 135.0f;
}

void m221_FireMdlInit(void) {
    s16 model;
    s32 i;
    void *data;
    s16 anim;

    Hu3DMatAmbScale = 1.0f;
    Hu3DMatColScale = 1.0f;
    data = DataRead(0xA008A);
    m221_fireMdlTbl[0] = Hu3DModelCreate(data, 0xAC1);
    anim = Hu3DAnimRead(Hu3DData[m221_fireMdlTbl[0]].hmf, 0xA008C, "c201n_00_DEF");
    Hu3DModelRemakeStatic(m221_fireMdlTbl[0]);
    Hu3DModelDynamicFree(m221_fireMdlTbl[0]);
    for (i = 1; i < 3; i++) {
        model = Hu3DModelCreate(data, 0xAC1);
        Hu3DAnimLink(Hu3DData[model].hmf, anim, 0, "c201n_00_DEF");
        Hu3DModelRemakeStatic(model);
        Hu3DModelDynamicFree(model);
        m221_fireMdlTbl[i] = model;
    }
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA008A);
    m221_fireMdlTbl[i] = Hu3DModelCreate(data, 0xAC1);
    anim = Hu3DAnimRead(Hu3DData[m221_fireMdlTbl[i]].hmf, 0xA008D, "c201n_00_DEF");
    Hu3DModelRemakeStatic(m221_fireMdlTbl[i]);
    Hu3DModelDynamicFree(m221_fireMdlTbl[i]);
    for (i++; i < 16; i++) {
        model = Hu3DModelCreate(data, 0xAC1);
        Hu3DAnimLink(Hu3DData[model].hmf, anim, 0, "c201n_00_DEF");
        Hu3DModelRemakeStatic(model);
        Hu3DModelDynamicFree(model);
        m221_fireMdlTbl[i] = model;
    }
    HuMemMemoryFreePerm(data);
    Hu3DMatAmbScale = 1.0f;
    Hu3DMatColScale = 1.0f;
}

void m221_PlayerDustUpdate(omObjData *object, f32 x, f32 y, f32 z) {
    s32 player;
    f32 scale;
    s32 i;

    player = ((MgPlayerWork *)object->data)->unk59;
    for (i = 0; i < 4; i++) {
        if (m221_dustTimerTbl[player][i] >= 0) {
            if (m221_dustTimerTbl[player][i] == 0) {
                Hu3DModelPosSet(object->model[10 + i], x, y + 30.0f, z);
                Hu3DModelAttrSet(object->model[10 + i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            if (m221_dustTimerTbl[player][i] < 8) {
                scale = m221_dustScaleTbl[m221_dustTimerTbl[player][i] / 2];
                Hu3DModelScaleSet(object->model[10 + i], scale, scale, 1.0f);
            }
            if (m221_dustTimerTbl[player][i] >= 8) {
                m221_dustTimerTbl[player][i] = -1;
            }
        }
        m221_dustTimerTbl[player][i]++;
    }
}

void m221_FlameObjInit(omObjData *object) {
    MgItemWork *data;
    s32 i;

    object->data = HuMemAllocTag(sizeof(MgItemWork), TAG_OVERLAY);
    memset(object->data, 0, sizeof(MgItemWork));
    data = object->data;
    object->model[1] = 0;
    object->model[0] = m221_fireMdlTbl[m221_fireMdlIdx++];
    object->func = m221_FlameObjMain;
    data->unk44 = 0.3f;
    data->unk48 = 60.0f;
    data->unk34 = 150.0f;
    data->unk3C = 0.0f;
    data->unk78 = 0;
    data->unk52 = 3;
    data->unk7C = 0;
    data->unk50 = 32;
    data->unk40 = 0.0f;
    data->unk74 = 0.8f;
    data->unk54 = 1;
    for (i = 0; i < 9; i++) {
        data->unk84[i] = NULL;
    }
    data->unk56 = m221_flameNum;
    MgPlayerMapAttrSet(object, 0, 2);
    MgPlayerMapAttrSet(object, 1, 2);
    object->trans.x = sindf(m221_flameNum * 36.0f) * 450.0f;
    object->trans.y = 500.0f;
    object->trans.z = cosdf(m221_flameNum * 36.0f) * 450.0f + -512.0f;
    object->scale.x = object->scale.y = object->scale.z = 0.0f;
    m221_flameNum++;
}

void m221_FlameObjMain(omObjData *object) {
    omObjData *stage;
    MgItemWork *data;

    stage = mgMapObjTbl[1];
    data = object->data;
    if (MgFlowStatGet() == MG_STATE_PLAY) {
        object->trans.x = m221_flamePosTbl[data->unk56].x;
        object->trans.y = m221_flamePosTbl[data->unk56].y;
        object->trans.z = m221_flamePosTbl[data->unk56].z;
        object->rot.y = atan2df(stage->trans.x - object->trans.x, stage->trans.z - object->trans.z);
        object->scale.x = object->scale.y = object->scale.z =
            sindf(m221_flameRot * 5.0f + data->unk56 * 30) * 0.3f + 2.2f;
    }
}

void m221_FlamePathCalc(omObjData *object) {
    Vec dir;
    f32 length;
    f32 spacing;
    f32 halfWidth;
    f32 dist;
    f32 t;
    s32 i;
    s32 n;

    n = 0;
    length = 2.0f * (m221_beltWidthTbl[0] + 600.0f) + 2000.0f;
    spacing = length / (mgItemObjNum - 1);
    m221_flamePathTbl[0].x = sindf(m221_flameRot) * (spacing / 2.0f) + object->trans.x + 0.0f;
    m221_flamePathTbl[0].y = 50.0f;
    m221_flamePathTbl[0].z = 350.0f;
    halfWidth = m221_beltWidthTbl[0] / 2.0f;
    m221_flamePathTbl[1].x = halfWidth + object->trans.x + 180.0f;
    m221_flamePathTbl[1].y = 50.0f;
    m221_flamePathTbl[1].z = 350.0f;
    m221_flamePathTbl[2].x = halfWidth + object->trans.x + 180.0f;
    m221_flamePathTbl[2].y = 50.0f;
    m221_flamePathTbl[2].z = -1150.0f;
    m221_flamePathTbl[3].x = object->trans.x - halfWidth - 180.0f;
    m221_flamePathTbl[3].y = 50.0f;
    m221_flamePathTbl[3].z = -1150.0f;
    m221_flamePathTbl[4].x = object->trans.x - halfWidth - 180.0f;
    m221_flamePathTbl[4].y = 50.0f;
    m221_flamePathTbl[4].z = 350.0f;
    m221_flamePathTbl[5].x = m221_flamePathTbl[0].x;
    m221_flamePathTbl[5].y = 50.0f;
    m221_flamePathTbl[5].z = 350.0f;
    t = 0.0f;
    for (i = 0; i < 5; i++) {
        dir.x = m221_flamePathTbl[i + 1].x - m221_flamePathTbl[i].x;
        dir.y = m221_flamePathTbl[i + 1].y - m221_flamePathTbl[i].y;
        dir.z = m221_flamePathTbl[i + 1].z - m221_flamePathTbl[i].z;
        dist = HuSqrtf(dir.x * dir.x + dir.z * dir.z);
        MapVecNormalize(&dir);
        do {
            m221_flamePosTbl[n].x = t * dir.x + m221_flamePathTbl[i].x;
            m221_flamePosTbl[n].y = t * dir.y + m221_flamePathTbl[i].y;
            m221_flamePosTbl[n].z = t * dir.z + m221_flamePathTbl[i].z;
            t += spacing;
            n++;
        } while (t < dist);
        t -= dist;
    }
}

void m221_BeltDummy(omObjData *object, s32 index) {
}

f32 m221_FireDirUpdate(s32 index, omObjData *object) {
    f32 angle;
    f32 speed;

    if (m221_fireBeltPosTbl[index].y < 0.0f && m221_fireBeltPosTbl[index].y > -900.0f) {
        if (m221_fireWanderTimerTbl[index] == 0) {
            m221_fireTurnTbl[index] = rand8() / 100.0f;
            m221_fireSpeedTbl[index] = rand8() / 100.0f + 1.0f;
            m221_fireWanderTimerTbl[index] = (rand8() >> 3) + 90;
        }
        if (m221_fireTurnTbl[index] > 0.0f) {
            m221_fireTurnTbl[index] -= 0.05f;
        }
        m221_fireWanderTimerTbl[index]--;
    } else if (m221_fireBeltPosTbl[index].y >= 0.0f) {
        if (m221_fireDirTbl[index] > 210.0f) {
            m221_fireTurnTbl[index] = -2.0f;
            m221_fireSpeedTbl[index] -= 0.2f;
            if (m221_fireSpeedTbl[index] < 0.0f) {
                m221_fireSpeedTbl[index] = 0.0f;
            }
        } else if (m221_fireDirTbl[index] < 150.0f) {
            m221_fireTurnTbl[index] = 2.0f;
            m221_fireSpeedTbl[index] -= 0.2f;
            if (m221_fireSpeedTbl[index] < 0.0f) {
                m221_fireSpeedTbl[index] = 0.0f;
            }
        } else {
            m221_fireTurnTbl[index] = 0.0f;
            m221_fireSpeedTbl[index] = 2.0f;
        }
    } else if (m221_fireBeltPosTbl[index].y <= -900.0f) {
        if (m221_fireDirTbl[index] < 330.0f && m221_fireDirTbl[index] > 180.0f) {
            m221_fireTurnTbl[index] = 2.0f;
            m221_fireSpeedTbl[index] -= 0.2f;
            if (m221_fireSpeedTbl[index] < 0.0f) {
                m221_fireSpeedTbl[index] = 0.0f;
            }
        } else if (m221_fireDirTbl[index] > 30.0f && m221_fireDirTbl[index] < 180.0f) {
            m221_fireTurnTbl[index] = -2.0f;
            m221_fireSpeedTbl[index] -= 0.2f;
            if (m221_fireSpeedTbl[index] < 0.0f) {
                m221_fireSpeedTbl[index] = 0.0f;
            }
        } else {
            m221_fireTurnTbl[index] = 0.0f;
            m221_fireSpeedTbl[index] = 2.0f;
        }
    }
    m221_fireDirTbl[index] += m221_fireTurnTbl[index];
    angle = m221_fireDirTbl[index] = HuAngleWrap(m221_fireDirTbl[index]);
    speed = m221_fireSpeedTbl[index];
    m221_fireBeltPosTbl[index].x += sindf(angle) * speed;
    m221_fireBeltPosTbl[index].y += cosdf(angle) * speed;
    return angle;
}
void m221_FireUpdate(omObjData *object) {
    HmfMotionNode *node;
    s32 model;
    f32 length;
    f32 end;
    f32 x;
    f32 y;
    f32 rot;
    f32 scale;
    f32 angle;
    s32 i;

    if (MgFlowStatGet() == MG_STATE_PLAY && MgFlowStatTimeGet() < 150) {
        return;
    }
    for (i = 0; i < 3; i++) {
        angle = m221_FireDirUpdate(i, object);
        length = m221_beltWidthTbl[i] + 100.0f + 200.0f + 200.0f;
        m221_fireBeltPosTbl[i].x -=
            m221_beltSpeedTbl[m221_LaneGet(m221_fireBeltPosTbl[i].y)] * 3.125f;
        if (m221_fireBeltPosTbl[i].x > length) {
            m221_fireBeltPosTbl[i].x -= length;
        }
        if (m221_fireBeltPosTbl[i].x < 0.0f) {
            m221_fireBeltPosTbl[i].x += length;
        }
        if (m221_fireBeltPosTbl[i].x < 100.0f) {
            y = 0.0f;
            x = 0.0f;
            rot = 0.0f;
            scale = 1.0f;
            m221_fireHideTbl[i] = 1;
        } else if (m221_fireBeltPosTbl[i].x <= 200.0f) {
            y = m221_fireBeltPosTbl[i].x;
            x = -(m221_beltWidthTbl[i] + 100.0f) / 2.0f;
            rot = 90.0f;
            scale = (m221_fireBeltPosTbl[i].x - 100.0f) / 100.0f;
            m221_fireHideTbl[i] = 1;
        } else if (m221_fireBeltPosTbl[i].x <= 250.0f) {
            rot = 90.0f - (m221_fireBeltPosTbl[i].x - 200.0f) / 50.0f * 90.0f;
            y = 250.0f - sindf(rot) * 50.0f;
            x = -(m221_beltWidthTbl[i] / 2.0f) + sindf(-rot) * 50.0f;
            scale = (m221_fireBeltPosTbl[i].x - 200.0f) / 100.0f + 1.0f;
            m221_fireHideTbl[i] = 0;
        } else if (m221_fireBeltPosTbl[i].x < m221_beltWidthTbl[i] + 250.0f) {
            x = -(m221_beltWidthTbl[i] + 100.0f) / 2.0f + m221_fireBeltPosTbl[i].x - 250.0f;
            y = 250.0f;
            rot = 0.0f;
            scale = 1.5f;
            m221_fireHideTbl[i] = 0;
        } else if (m221_fireBeltPosTbl[i].x < m221_beltWidthTbl[i] + 250.0f + 50.0f) {
            rot = -((m221_fireBeltPosTbl[i].x - (m221_beltWidthTbl[i] + 250.0f)) / 50.0f) * 90.0f;
            y = sindf(rot) * 50.0f + 250.0f;
            x = m221_beltWidthTbl[i] / 2.0f + sindf(-rot) * 50.0f;
            scale = (m221_beltWidthTbl[i] + 250.0f + 50.0f - m221_fireBeltPosTbl[i].x) / 100.0f + 1.0f;
            m221_fireHideTbl[i] = 0;
        } else if (m221_fireBeltPosTbl[i].x < (end = m221_beltWidthTbl[i] + 250.0f + 50.0f + 100.0f)) {
            y = end - m221_fireBeltPosTbl[i].x + 100.0f;
            x = (m221_beltWidthTbl[i] + 100.0f) / 2.0f;
            rot = -90.0f;
            scale = (end - m221_fireBeltPosTbl[i].x) / 100.0f;
            m221_fireHideTbl[i] = 1;
        } else {
            y = 0.0f;
            x = 0.0f;
            rot = 0.0f;
            scale = 1.0f;
            m221_fireHideTbl[i] = 1;
        }
        if (y != 0.0f) {
            model = object->model[10 + i];
            Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelPosSet(model, x + object->trans.x, y, m221_fireBeltPosTbl[i].y);
            Hu3DModelRotSet(model, CRot.x, 0.0f, 0.0f);
            Hu3DModelScaleSet(model, scale, scale, scale);
            HuRotateRPYF(Hu3DData[model].mtx, 0.0f, 0.0f, rot);
            node = Hu3DModelObjPtrGet(model, m221_fireEyesName);
            node->baseRot.y = node->rot.y = angle;
            m221_fireScaleRot += 5.0f;
            m221_fireScaleRot = HuAngleWrap(m221_fireScaleRot);
            scale = scale * 0.5f + sindf(m221_fireScaleRot) * 0.3f;
            model = object->model[13 + i];
            Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelPosSet(model, x + object->trans.x, y - 3.0f, m221_fireBeltPosTbl[i].y);
            Hu3DModelScaleSet(model, scale, scale, scale);
            HuRotateRPYF(Hu3DData[model].mtx, 0.0f, 0.0f, rot);
        } else {
            Hu3DModelAttrSet(object->model[10 + i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(object->model[13 + i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
        m221_firePosTbl[i].x = x + object->trans.x;
        m221_firePosTbl[i].y = y;
        m221_firePosTbl[i].z = m221_fireBeltPosTbl[i].y;
    }
}

void m221_BeltObjMain(omObjData *object) {
    MgPlayerWork *data;
    omObjData *player;
    s32 lane;
    s32 i;

    Hu3DModelTexScroll(object->model[0], m221_beltScrollTbl[0], 0.0f, 32, 64);
    Hu3DModelTexScroll(object->model[1], m221_beltScrollTbl[1], 0.0f, 32, 64);
    Hu3DModelTexScroll(object->model[2], m221_beltScrollTbl[2], 0.0f, 32, 64);
    Hu3DModelTexScroll(object->model[3], m221_beltScrollTbl[3], 0.0f, 32, 64);
    m221_BeltVtxUpdate(object);
    if (omPauseChk() + omAllPauseF != 0) {
        return;
    }
    if (MgFlowStatGet() == MG_STATE_OPENING) {
        m221_FlameIntroUpdate(object);
    } else if (MgFlowStatGet() == MG_STATE_PLAY) {
        Hu3DModelRotSet(object->model[5], 0.0f, 0.0f, m221_beltScrollTbl[0] * 1.2f);
        Hu3DModelRotSet(object->model[6], 0.0f, 0.0f, m221_beltScrollTbl[0] * 1.2f);
        m221_beltScrollTbl[0] += m221_beltSpeedTbl[0];
        m221_beltScrollTbl[1] += m221_beltSpeedTbl[1];
        m221_beltScrollTbl[2] += m221_beltSpeedTbl[2];
        m221_beltScrollTbl[3] += m221_beltSpeedTbl[3];
        m221_FireUpdate(object);
        if (m221_beltStopTimer == -1) {
            m221_BeltSpeedChange();
            m221_beltStopTimer = 0;
            m221_beltSeTbl[0] = HuAudFXPlay(0x397);
            m221_beltSeTbl[1] = HuAudFXPlay(0x398);
            m221_beltSeTbl[2] = HuAudFXPlay(0x399);
            m221_beltSeTbl[3] = HuAudFXPlay(0x39A);
        }
        if (m221_beltStopTimer == 0) {
            if (m221_beltSpeedStepCnt != 0) {
                m221_BeltSpeedUpdate(object);
                m221_beltSpeedStepCnt--;
            }
        } else {
            m221_beltStopTimer--;
            if (m221_beltSpeedStepCnt != 0) {
                m221_BeltSpeedUpdate(object);
                m221_beltSpeedStepCnt--;
            } else {
                m221_BeltShrink(object);
            }
        }
        if (m221_beltStopTimer == 0) {
            if (++m221_beltChangeTimer == 90) {
                m221_BeltSpeedChange();
            }
            if (++m221_beltRunTimer == 300) {
                m221_BeltStop();
                for (i = 0; i < 4; i++) {
                    data = mgPlayerObjTbl[i]->data;
                    if (m221_playerOutTbl[i] == 0) {
                        omVibrate(data->unk59, 20, 0, 20);
                    }
                }
            }
        }
        for (i = 0; i < mgPlayerObjNum; i++) {
            player = mgPlayerObjTbl[i];
            data = player->data;
            if (m221_playerOutTbl[i] == 0 && data->unk53[0] == 1) {
                lane = m221_BeltLaneGet(player->trans.x, player->trans.z);
                switch (lane) {
                    case -1:
                        break;
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        player->trans.x -= m221_beltSpeedTbl[lane] * 3.125f;
                        break;
                }
            }
        }
        m221_flameRot = HuAngleWrap(m221_flameRot + 3.0f);
        m221_FlamePathCalc(object);
    } else if (MgFlowStatGet() == MG_STATE_FINISH) {
        if (m221_beltSeTbl[0] != -1) {
            HuAudFXStop((s16)m221_beltSeTbl[0]);
            m221_beltSeTbl[0] = -1;
        }
        if (m221_beltSeTbl[1] != -1) {
            HuAudFXStop((s16)m221_beltSeTbl[1]);
            m221_beltSeTbl[1] = -1;
        }
        if (m221_beltSeTbl[2] != -1) {
            HuAudFXStop((s16)m221_beltSeTbl[2]);
            m221_beltSeTbl[2] = -1;
        }
        if (m221_beltSeTbl[3] != -1) {
            HuAudFXStop((s16)m221_beltSeTbl[3]);
            m221_beltSeTbl[3] = -1;
        }
        m221_FireFadeUpdate(object);
    }
    m221_beltWidthScale = m221_beltWidthTbl[0] / 1100.0f;
    Hu3DModelScaleSet(object->model[4], m221_beltWidthScale, 1.0f, 1.0f);
    Hu3DModelPosSet(object->model[9], 0.0f, 0.0f, -450.0f);
    Hu3DModelScaleSet(object->model[9], m221_beltWidthScale + 0.1f, 1.0f, 0.8f);
}

void m221_BeltSpeedChange(void) {
    f32 speed;
    s32 index;
    s32 i;

    HuAudFXPlay(0x39C);
    for (i = 0; i < 4; i++) {
        while (m221_beltSpeedTbl[i] == (speed = m221_beltSpeedChoiceTbl[index = (u8)(rand8() % 6)]) * 0.5f) {}
        m221_beltAccelTbl[i] = (speed - m221_beltSpeedTbl[i]) / 20.0f;
        m221_beltSpeedStepTbl[i] = (speed - m221_beltSpeedTbl[i]) / 20.0f;
        if (m221_beltSeTbl[i] >= 0) {
            HuAudFXPitchSet((s16)m221_beltSeTbl[i], m221_beltSePitchTbl[index]);
        }
    }
    m221_beltSpeedStepCnt = 20;
    m221_beltChangeTimer = 0;
}

void m221_BeltStop(void) {
    s32 i;

    if (m221_beltStopCnt++ < 2) {
        m221_beltStopTimer = 50;
        m221_beltRunTimer = 0;
        for (i = 0; i < 4; i++) {
            m221_beltAccelTbl[i] = -m221_beltSpeedTbl[i] / 20.0f;
            m221_beltSpeedStepTbl[i] = -m221_beltSpeedTbl[i] / 20.0f;
        }
        m221_beltSpeedStepCnt = 20;
        m221_beltChangeTimer = 0;
    }
}

void m221_BeltShrink(omObjData *object) {
    f32 minX;
    f32 maxX;
    s32 i;

    for (i = 0; i < 4; i++) {
        m221_beltWidthPrevTbl[i] = m221_beltWidthTbl[i];
        m221_beltWidthTbl[i] -= 10.0f;
    }
    m221_BeltTexUpdate(object);
    if (m221_beltStopTimer == 0) {
        m221_BeltSpeedChange();
    }
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, -300.0f);
    Hu3DModelPosSet(object->model[2], object->trans.x, object->trans.y, -600.0f);
    Hu3DModelPosSet(object->model[3], object->trans.x, object->trans.y, -900.0f);
    m221_wallLeftX += 5.5f;
    m221_wallRightX -= 5.5f;
    Hu3DModelPosSet(object->model[4], object->trans.x, 0.0f, 0.0f);
    Hu3DModelPosSet(object->model[5], object->trans.x + m221_wallLeftX, 150.0f, 165.0f);
    Hu3DModelPosSet(object->model[6], object->trans.x + m221_wallRightX, 150.0f, 165.0f);
    Hu3DModelPosSet(object->model[7], object->trans.x + m221_wallLeftX + 50.0f, 220.0f, 155.0f);
    Hu3DModelPosSet(object->model[8], object->trans.x + m221_wallRightX - 50.0f, 220.0f, 155.0f);
    minX = -m221_beltWidthTbl[0] / 2.0f;
    maxX = m221_beltWidthTbl[0] / 2.0f + 50.0f;
    MgMapBlockSet(object, 250.0f, 250.0f, minX - 50.0f, -1050.0f, maxX, 150.0f);
}

void m221_BeltSpeedUpdate(omObjData *object) {
    s32 i;

    for (i = 0; i < 4; i++) {
        m221_BeltDummy(object, i);
        m221_beltSpeedTbl[i] += m221_beltSpeedStepTbl[i];
    }
}

s32 m221_BeltLaneGet(f32 x, f32 z) {
    s32 lane = -1;

    if (x <= 550.0f && x >= -550.0f) {
        if (z <= 150.0f && z > -150.0f) {
            lane = 0;
        } else if (z <= -150.0f && z > -450.0f) {
            lane = 1;
        } else if (z <= -450.0f && z > -750.0f) {
            lane = 2;
        } else {
            lane = 3;
        }
    }
    return lane;
}

s32 m221_LaneGet(f32 z) {
    if (z <= 150.0f && z > -150.0f) {
        return 0;
    }
    if (z <= -150.0f && z > -450.0f) {
        return 1;
    }
    if (z <= -450.0f && z > -750.0f) {
        return 2;
    }
    return 3;
}

void m221_BeltVtxUpdate(omObjData *object) {
    HmfData *hmf;
    HmfVertexGroup *group;
    Vtx *dst;
    Vtx *src;
    s32 i;
    s32 j;
    s32 k;
    f32 scale;

    for (i = 0; i < 4; i++) {
        hmf = Hu3DData[object->model[i]].hmf;
        scale = m221_beltWidthTbl[i] / 1000.0f;
        for (j = 0; j < hmf->unk1A; j++) {
            group = &hmf->unkB0[j];
            if (group->normal[1] == 127) {
                for (k = 0; k < group->count; k++) {
                    dst = &hmf->unk44[Hu3DBufNo][group->indices[k]];
                    src = &hmf->unk40[group->indices[k]];
                    if (src->v.ob[0] > 0) {
                        dst->v.ob[0] = m221_beltWidthTbl[i] * 0.5f;
                    } else {
                        dst->v.ob[0] = -m221_beltWidthTbl[i] * 0.5f;
                    }
                }
            } else {
                for (k = 0; k < group->count; k++) {
                    dst = &hmf->unk44[Hu3DBufNo][group->indices[k]];
                    src = &hmf->unk40[group->indices[k]];
                    dst->v.ob[0] = src->v.ob[0] * scale;
                }
            }
        }
    }
}

void m221_BeltTexUpdate(omObjData *arg0) {
    HmfData *hmf;
    HmfVertexGroup *group;
    Vtx *vtx;
    s32 i;
    s32 j;
    s32 k;
    f32 scale;

    for (i = 0; i < 4; i++) {
        hmf = Hu3DData[arg0->model[i]].hmf;
        scale = m221_beltWidthTbl[i] / m221_beltWidthPrevTbl[i];
        for (j = 0; j < hmf->unk1A; j++) {
            group = &hmf->unkB0[j];
            for (k = 0; k < group->count; k++) {
                vtx = &hmf->unk40[group->indices[k]];
                vtx->v.tc[0] = (s16)(vtx->v.tc[0] * scale);
            }
        }
    }
}
