#include "common.h"
#include "mgmode.h"
#include "game/hmfmath.h"

extern s16 mgmode_exitEvtNo;
extern s16 mgmode_exitOvlNo;
extern s16 mgmode_zClearF;
extern s16 mgmode_teamWinId;
extern MgmodeEsprite *mgmode_teamSprTbl;
extern s16 mgmode_mdlTbl5;
extern u16 *mgmode_teamPosXTbl;
extern s8 mgmode_teamOrderTbl[];
extern char mgmode_strBuf[];
extern s16 mgmode_menuWinId;
extern s16 mgmode_typeUnlockNumTbl[];
extern s16 mgmode_typeMgNumTbl[];
extern s16 mgmode_mgNum;
extern s16 mgmode_mgUnlockNum;
extern u8 mgmode_markMgTbl[][20];
extern u8 mgmode_markMgNumTbl[];
extern u8 mgmode_plainMgTbl[][20];
extern u8 mgmode_plainMgNumTbl[];
extern u8 mgmode_typeMgTbl[][25];
extern s16 mgmode_winId;
extern u8 mgModeMenuNo;
extern Vec mgmode_bookPosTbl[][25];
extern s16 mgmode_mdlTbl7[];
extern s16 mgmode_mdlTbl14;
extern s16 mgmode_padNo;
extern s16 mgmode_mdlTbl6;
extern HuMtx4F mgmode_roomMonitorMtx;
extern HuMtx4F mgmode_roomBattleDoorMtx;
extern HuMtx4F mgmode_roomGambleDoorMtx;
extern s16 mgmode_mdlTbl[];
extern u8 Hu3DBufNum;
extern MgmodeEspriteDef mgmode_teamSprDefTbl[];
extern u8 mgPlayerTeam[];
extern f32 mgmode_cameraFov;
extern f32 mgmode_cameraNear;
extern f32 mgmode_cameraFar;
extern Vec mgmode_cameraRot;
extern Vec mgmode_cameraCenter;
extern f32 mgmode_cameraZoom;
extern u8 mgmode_battleOpenF;
extern u8 mgmode_gambleOpenF;
extern s16 mgmode_playerNo;
extern u8 Hu3DScreenClearF;
extern u8 omSysPauseDisableF;
extern u16 mgModeRecordBak[];
extern u8 storySceneNo;
extern s16 HuSprLayerHookMdl;
extern s16 mgModeCoinBase;
extern s16 mgModeCoinRate;
extern u16 mgBattleCoinPot;
extern u8 mgmode_cameraPresetNo;
extern MgmodeSpaceCoord mgmode_bookCursorPosTbl[];
extern s8 mgModeCursor[];
extern ModeCameraPreset *mgmode_cameraPresetTbl;
extern MgmodeModelEntry mgmode_roomMdlDefTbl[];
extern s16 mgmode_roomSpotNo;
extern s16 mgmode_motTbl16[];

void mgmode_ExitObjMain(omObjData *arg0);
void mgmode_ShelfSelect(s16 arg0);
void mgmode_SprListKill(MgmodeEsprite *arg0);
void mgmode_SprListPosSet(MgmodeEsprite *arg0, s16 index, s16 arg2, s16 arg3);
void mgmode_SprListDispOn(MgmodeEsprite *arg0, s16 index);
void mgmode_SprListDispOff(MgmodeEsprite *arg0, s16 index);
void mgmode_MgPicKill(void);
void mgmode_RecordSave(void);
void mgmode_BookSelect(s16 arg0);
void mgmode_MgRecordExec(s32 dataNum, s16 x, s16 y);
void mgmode_CursorMoveTimeSet(s16 arg0);
void mgmode_CursorSelMove(s16 arg0);
s16 mgmode_CursorPadNextGet(s16 stickX, s16 stickY);
void mgmode_DpadStickSet(void);
MgmodeEsprite *mgmode_SprListCreate(MgmodeEspriteDef *defs);
void mgmode_TeamSprPosSet(s32 arg0, s32 arg1);
void mgmode_TeamArrowPosSet(s32 arg0, s32 arg1);
void mgmode_RoomProc(void);
void mgmode_MgListBuild(s32 arg0);
void mgmode_ZClearHook(Gfx **arg0, s32 arg1, s32 arg2);
void mgmode_CameraProc(void);
void mgmode_ExitCheckObjMain(omObjData *arg0);
void mgmode_BattleRoomProc(void);
void mgmode_GambleRoomProc(void);
s32 mgmode_BattleGoalCheck(void);
void mgmode_CursorProc(void);
void mgmode_CameraPresetSet(s16 arg0);
s16 mgmode_MgPicCreate(void);
void mgmode_MgPicLoad(s16 arg0);
void mgmode_CursorDisableSet(s16 index);
void mgmode_BookMdlSet(s16 arg0, s16 arg1);
void mgmode_BookTakeExec(s16 arg0, s16 arg1);
s16 mgmode_TeamChoice(s16 arg0);
void mgmode_TeamChoiceKill(void);
void mgmode_MdlListCreate(MgmodeModelEntry *entries);
void mgmode_RoomInit(void);
void mgmode_FloatMdlProc(void);
s16 mgmode_MgUnlockExec(void);
void mgmode_MenuExec(s32 arg0);
void mgmode_MenuResume(void);

u8 mgmode_cameraDebugF = 0;
u8 mgmode_exitF = 0;
u8 mgmode_exitSaveF = 0;
s16 mgmode_exitMode = 0;
ModeCameraPreset mgmode_roomCameraPresetTbl[21] = {
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 127.0f, -395.0f }, 1400.0f, 40.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 127.0f, -395.0f }, 330.0f, 40.0f },
    { { 358.0f, 0.0f, 0.0f }, { 0.0f, 217.0f, -384.7f }, 580.0f, 44.0f },
    { { 0.0f, 144.0f, 0.0f }, { -442.7f, 106.2f, 848.7f }, 590.0f, 40.0f },
    { { 4.0f, 218.0f, 0.0f }, { 364.0f, 104.9f, 741.4f }, 450.0f, 40.0f },
    { { 6.0f, 180.0f, 0.0f }, { 0.0f, 151.5f, 888.0f }, 580.0f, 40.0f },
    { { 0.0f, 0.0f, 0.0f }, { 91.0f, 115.0f, -395.0f }, 60.0f, 29.0f },
    { { 0.0f, 38.0f, 0.0f }, { -221.4f, 397.1f, -540.6f }, 280.0f, 24.0f },
    { { 0.0f, 2.0f, 0.0f }, { 8.7f, 425.1f, -506.1f }, 730.0f, 20.0f },
    { { 0.0f, 322.0f, 0.0f }, { 107.8f, 397.1f, -397.5f }, 20.0f, 29.0f },
    { { 0.0f, 38.0f, 0.0f }, { -221.4f, 239.1f, -540.6f }, 280.0f, 24.0f },
    { { 0.0f, 0.0f, 0.0f }, { -111.7f, 237.1f, -430.4f }, 50.0f, 29.0f },
    { { 0.0f, 0.0f, 0.0f }, { 110.3f, 237.1f, -430.4f }, 50.0f, 29.0f },
    { { 0.0f, 322.0f, 0.0f }, { 107.8f, 237.1f, -397.5f }, 20.0f, 29.0f },
    { { 4.0f, 218.0f, 0.0f }, { 364.0f, 104.9f, 741.4f }, 80.0f, 40.0f },
    { { 0.0f, 144.0f, 0.0f }, { -442.7f, 94.2f, 848.7f }, 200.0f, 40.0f },
    { { 10.0f, 180.0f, 0.0f }, { 0.0f, 45.2f, 907.5f }, 20.0f, 40.0f },
    { { 4.0f, 38.0f, 0.0f }, { 363.5f, 92.9f, 740.7f }, 170.0f, 40.0f },
    { { 2.0f, 40.0f, 0.0f }, { 243.7f, 64.7f, 572.9f }, 50.0f, 40.0f },
    { { 4.0f, 322.0f, 0.0f }, { -194.9f, 88.0f, 522.6f }, 490.0f, 40.0f },
    { { 0.0f, 322.0f, 0.0f }, { -194.9f, 88.0f, 522.6f }, 40.0f, 40.0f }
};
MgmodeSpaceCoord mgmode_roomCursorPosTbl[6] = {
    { 160, 97 }, { 234, 133 }, { 157, 109 }, { 157, 118 }, { 157, 106 }, { -1, -1 }
};
MgmodeSpaceCoord mgmode_shelfCursorPosTbl[8] = {
    { 45, 64 }, { 158, 68 }, { 271, 64 }, { 45, 121 }, { 123, 120 }, { 194, 120 }, { 271, 121 }, { -1, -1 }
};
s32 mgmode_shelfMesTbl[21] = {
    0x5718, 0x5714, 0x5719, 0x5715, 0x5716, 0x5717, 0x571A,
    0x571F, 0x571B, 0x5720, 0x571C, 0x571D, 0x571E, 0x5721,
    0x5726, 0x5722, 0x5727, 0x5723, 0x5724, 0x5725, 0x5728
};
s32 mgmode_shelfTypeTbl[7] = {
    4, 0, 5, 2, 1, 3, 7
};
u16 mgmode_mgInfoMesTbl[72] = {
    0x4401, 0x4402, 0x4403, 0x4404, 0x4405, 0x4406, 0x4407, 0x4408,
    0x4409, 0x440A, 0x440B, 0x440C, 0x440D, 0x440E, 0x440F, 0x4410,
    0x4411, 0x4412, 0x4413, 0x4414, 0x4415, 0x4416, 0x4417, 0x4418,
    0x4419, 0x4429, 0x441A, 0x441B, 0x441C, 0x441D, 0x441E, 0x441F,
    0x4420, 0x4421, 0x4422, 0x4423, 0x4424, 0x4425, 0x4426, 0x4427,
    0x442A, 0x442B, 0x442C, 0x4428, 0x442D, 0x442E, 0x442F, 0x4430,
    0x4431, 0x4432, 0x4433, 0x4434, 0x4435, 0x4436, 0x4437, 0x4438,
    0x4439, 0x443A, 0x443B, 0x443C, 0x443D, 0x443E, 0x443F, 0x4440,
    0, 0x4441, 0, 0, 0, 0, 0x4442, 0x4443
};
Gfx mgmode_zClearGfx[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsDPSetFillColor(0xFFFCFFFC),
    gsDPFillRectangle(0, 0, 319, 239),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, 0x02000000),
    gsSPEndDisplayList(),
};

void mgmode_ObjectSetup(void) {
    HmfModel *model;
    s16 i;

    omInitObjMan(20, 10);
    Hu3DCamInit(2);
    HuWinInit();
    Hu3DSprModelInit(20);
    Hu3DBGColorSet(0, 0, 0);
    Hu3DScreenClearF = 1;
    omSysPauseDisableF = 1;
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    ScissorSet(1, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    mgmode_cameraRot.z = 90.0f; // CRot.z is left as-is and copied over this below
    CZoom = 660.0f;
    Center.x = 0.0f;
    Center.y = 181.0f;
    Center.z = -395.0f;
    mgmode_cameraFov = 40.0f;
    mgmode_cameraRot = CRot;
    mgmode_cameraZoom = CZoom;
    mgmode_cameraCenter = Center;
    mgmode_cameraNear = 80.0f;
    mgmode_cameraFar = 1800.0f;
    Hu3DCameraPerspectiveSet(0, mgmode_cameraFov, mgmode_cameraNear, mgmode_cameraFar);
    Hu3DCameraPerspectiveSet(1, mgmode_cameraFov, mgmode_cameraNear, mgmode_cameraFar);
    Hu3DGLightMaxSet(4);
    Hu3DGLightColorSet(1, 64, 64, 64);
    Hu3DGLightDirSet(1, 0.0f, 119.0f, 0.0f);
    Hu3DGLightStatSet(0, 1, 1);
    Hu3DGLightColorSet(2, 150, 150, 110);
    Hu3DGLightDirSet(2, 40.0f, 42.0f, 104.0f);
    Hu3DGLightColorSet(3, 0, 0, 0);
    omAddObj(10000, 0, 0, -1, mgmode_ExitCheckObjMain);
    omPrcSetStatBit(omAddPrcObj(mgmode_CameraProc, 0x1100, 0x1000, 0), 0xA0);
    omAddPrcObj(mgmode_CursorProc, 0x3F00, 0x800, 0);
    mgmode_MgListBuild(0);

    if (omovlevtno == 0 || omovlevtno == 1 || omovlevtno == 6 || omovlevtno == 7) {
        omAddPrcObj(mgmode_RoomProc, 0x3FF6, 0x2000, 0);
        HuAudSeqPlay(8);
    } else if (omovlevtno == 2 || omovlevtno == 4) {
        mgmode_MgListBuild(1);
        Hu3DGLightColorSet(3, 130, 130, 50);
        Hu3DGLightDirSet(3, -17.0f, -101.0f, -61.0f);
        omAddPrcObj(mgmode_BattleRoomProc, 0x3FF6, 0x2000, 0);
        if (omovlevtno == 4) {
            if (mgmode_BattleGoalCheck() == 0) {
                HuAudSeqPlay(76);
            } else {
                HuAudSeqPlay(22);
            }
        } else {
            HuAudSeqPlay(76);
        }
    } else if (omovlevtno == 3 || omovlevtno == 5) {
        omAddPrcObj(mgmode_GambleRoomProc, 0x3FF6, 0x2000, 0);
        if (omovlevtno == 5 && mgModeCoinBase + mgModeCoinRate * GwPlayer[0].bonusCoin >= 1000) {
            HuAudSeqPlay(70);
        } else {
            HuAudSeqPlay(77);
        }
    }

    if (omovlevtno != 0) {
        for (i = 0; i < 10; i++) {
            if (mgModeRecordBak[i] != GwCommon.mgRecord[i]) {
                break;
            }
        }
        if (i != 10) {
            mgmode_RecordSave();
        }
    }
    for (i = 0; i < 10; i++) {
        mgModeRecordBak[i] = GwCommon.mgRecord[i];
    }
    mgmode_padNo = 0;
    mgmode_playerNo = 0;
    _ClearFlag(13);
    _SetFlag(28);
    storySceneNo = 0;
    model = &Hu3DData[HuSprLayerHookMdl];
    model->unk00 = (model->unk00 & 0xF9) | 3;
    Hu3DModelCameraSet(HuSprLayerHookMdl, 1);
    mgmode_gambleOpenF = 0;
    mgmode_battleOpenF = 0;
    for (i = 0; i < 6; i++) {
        if (mgmode_typeUnlockNumTbl[i] >= 3) {
            mgmode_battleOpenF = 1;
            break;
        }
    }
    if (_CheckFlag(29)) {
        mgmode_gambleOpenF = 1;
    }
    mgmode_zClearF = 0;
    Hu3DModelCameraSet(Hu3DHookFuncCreate(0, mgmode_ZClearHook, 0), 2);
    for (i = 0; i < 4; i++) {
        mgPlayerTeam[i] = 0;
    }
    mgBattleCoinPot = 0;
    for (i = 0; i < 4; i++) {
        GwPlayer[i].star = 0;
    }
}

void mgmode_RoomProc(void) {
    s16 size[2];
    HmfMotionNode *node;
    HmfData *hmf;
    s16 i;

    mgmode_cameraPresetTbl = mgmode_roomCameraPresetTbl;
    mgmode_MdlListCreate(mgmode_roomMdlDefTbl);
    mgmode_RoomInit();
    WipeCreateIn(11, 16);
    omAddPrcObj(mgmode_FloatMdlProc, 0x3FF6, 0x1000, 0);
    HuWinMesMaxSizeBetGet(size, 0x5700, 0x570A);
    mgmode_winId = HuWinExCreate(-1, (320 - size[0]) / 2, 224 - size[1], size[0], size[1], 0);
    HuWinActivePlayerSet(mgmode_winId, 1 << mgmode_padNo);
    HuWinInsertMesSizeGet((u32) "00", 0);
    HuWinMesMaxSizeBetGet(size, 0x570B, 0x5728);
    mgmode_menuWinId = HuWinExCreate(-1, (320 - size[0]) / 2, 224 - size[1], size[0], size[1], 0);
    HuWinActivePlayerSet(mgmode_menuWinId, 1 << mgmode_padNo);
    if (omovlevtno == 0 || omovlevtno == 6 || omovlevtno == 7) {
        mgmode_roomSpotNo = 0;
        for (i = 0; i < 10; i++) {
            mgModeCursor[i] = -1;
        }
        Hu3DMotionSet(mgmode_mdlTbl[15], mgmode_motTbl16[0]);
        Hu3DMotionAttrSet(mgmode_mdlTbl[15], 2, 2);
        if (omovlevtno == 0) {
            mgmode_CameraPresetSet(0);
            while (WipeStatGet()) {
                HuPrcVSleep();
            }
            Hu3DMotionShiftSet(mgmode_mdlTbl[15], mgmode_motTbl16[1], 0, 15, 2);
            mgmode_CameraPresetMove(1, 30, 1, (void (*)(s16 *))-1);
            HuAudFXPlay(0x298);
        } else if (omovlevtno == 6) {
            mgmode_CameraPresetSet(17);
            while (WipeStatGet()) {
                HuPrcVSleep();
            }
            node = Hu3DModelObjPtrGet(mgmode_mdlTbl[3], "door_b");
            RepeatVibrator(mgmode_padNo, 5, 0, 5);
            HuAudFXPlay(0x2EB);
            for (i = 0; i < 19; i++) {
                HuPrcVSleep();
                mtxCopy(node->unk58, mgmode_roomBattleDoorMtx);
                mtxRotCat(node->unk58, 0.0f, i * 5, 0.0f);
            }
            mgmode_CameraPresetMove(18, 20, 1, (void (*)(s16 *))-1);
            mtxCopy(node->unk58, mgmode_roomBattleDoorMtx);
            mgmode_CameraPresetMove(1, 30, 1, (void (*)(s16 *))-1);
        } else if (omovlevtno == 7) {
            mgmode_CameraPresetSet(19);
            while (WipeStatGet()) {
                HuPrcVSleep();
            }
            node = Hu3DModelObjPtrGet(mgmode_mdlTbl[3], "door_g");
            RepeatVibrator(mgmode_padNo, 5, 0, 5);
            HuAudFXPlay(0x2EB);
            for (i = 0; i < 19; i++) {
                HuPrcVSleep();
                mtxCopy(node->unk58, mgmode_roomGambleDoorMtx);
                mtxRotCat(node->unk58, 0.0f, -i * 5, 0.0f);
            }
            mgmode_CameraPresetMove(20, 20, 1, (void (*)(s16 *))-1);
            mtxCopy(node->unk58, mgmode_roomGambleDoorMtx);
            mgmode_CameraPresetMove(1, 30, 1, (void (*)(s16 *))-1);
        }
        hmf = Hu3DData[mgmode_mdlTbl[0]].hmf;
        hmf->unk60[SearchObjectIndex(hmf, "fog")].unk24 = 1;
        mgmode_CursorPosTblSet(mgmode_roomCursorPosTbl);
        mgmode_CursorSelSet(0);
        mgmode_MgUnlockExec();
        if (omovlevtno == 0 && !_CheckFlag(17)) {
            _SetFlag(17);
            mgmode_exitSaveF = 1;
            if (mgmode_typeUnlockNumTbl[0] + mgmode_typeUnlockNumTbl[1] + mgmode_typeUnlockNumTbl[2] + mgmode_typeUnlockNumTbl[3] +
                    mgmode_typeUnlockNumTbl[4] + mgmode_typeUnlockNumTbl[5] + mgmode_typeUnlockNumTbl[7] <
                67) {
                HuWinMesSet(mgmode_winId, 0x5700, -1, -1);
            } else {
                HuWinMesSet(mgmode_winId, 0x5701, -1, -1);
            }
            HuWinExAnimIn(mgmode_winId);
            while (HuWinStatGet(mgmode_winId) != 0) {
                HuPrcVSleep();
            }
            mgmode_CursorDispSet(1);
            HuWinMesSet(mgmode_winId, 0x5702, -1, -1);
        } else {
            mgmode_CursorDispSet(1);
            HuWinMesSet(mgmode_winId, 0x5702, -1, -1);
            HuWinExAnimIn(mgmode_winId);
        }
        HuPrcSleep(5);
    } else if (omovlevtno == 1) {
        hmf = Hu3DData[mgmode_mdlTbl[0]].hmf;
        hmf->unk60[SearchObjectIndex(hmf, "fog")].unk24 = 1;
        mgmode_roomSpotNo = 0;
        mgmode_CameraPresetSet(2);
        Hu3DMotionSet(mgmode_mdlTbl[15], mgmode_motTbl16[1]);
        Hu3DMotionAttrSet(mgmode_mdlTbl[15], 2, 2);
        mgmode_MenuResume();
        Hu3DMotionShiftSet(mgmode_mdlTbl[15], mgmode_motTbl16[0], 0, 8, 2);
    }
    if (mgmode_gambleOpenF) {
        hmf = Hu3DData[mgmode_mdlTbl[3]].hmf;
        hmf->unk60[SearchObjectIndex(hmf, "harigami_g")].unk24 = 1;
    }
    if (mgmode_battleOpenF) {
        hmf = Hu3DData[mgmode_mdlTbl[3]].hmf;
        hmf->unk60[SearchObjectIndex(hmf, "harigami_b")].unk24 = 1;
    }
    while (TRUE) {
        HuPrcVSleep();
        mgmode_CursorMoveTimeSet(5);
        switch (mgmode_cameraPresetNo) {
            case 1:
                if (HuPadBtnDown[mgmode_padNo] & A_BUTTON) {
                    HuAudFXPlay(2);
                    mgmode_CursorDispSet(0);
                    Hu3DMotionShiftSet(mgmode_mdlTbl[15], mgmode_motTbl16[1], 0, 8, 2);
                    HuWinExAnimOut(mgmode_winId, 0);
                    mgmode_MenuExec(0);
                    Hu3DMotionShiftSet(mgmode_mdlTbl[15], mgmode_motTbl16[0], 0, 8, 2);
                } else if (ContBtnDown[mgmode_padNo] & L_JPAD) {
                    HuAudFXPlay(1);
                    HuWinExAnimOut(mgmode_winId, 0);
                    mgmode_roomSpotNo = 4;
                    mgmode_CursorMoveTimeSet(20);
                    mgmode_CursorSelMove(4);
                    mgmode_CameraPresetMove(3, 20, 1, (void (*)(s16 *))-1);
                    if (mgmode_gambleOpenF) {
                        HuWinMesSet(mgmode_winId, 0x5703, -1, -1);
                    } else {
                        HuWinMesSet(mgmode_winId, 0x5704, -1, -1);
                    }
                    HuWinExAnimIn(mgmode_winId);
                } else if (ContBtnDown[mgmode_padNo] & R_JPAD) {
                    HuAudFXPlay(1);
                    HuWinExAnimOut(mgmode_winId, 0);
                    mgmode_roomSpotNo = 2;
                    mgmode_CursorMoveTimeSet(20);
                    mgmode_CursorSelMove(2);
                    mgmode_CameraPresetMove(4, 20, 1, (void (*)(s16 *))-1);
                    if (mgmode_battleOpenF) {
                        HuWinMesSet(mgmode_winId, 0x5706, -1, -1);
                    } else {
                        HuWinMesSet(mgmode_winId, 0x5707, -1, -1);
                    }
                    HuWinExAnimIn(mgmode_winId);
                }
                break;
            case 3:
                if (HuPadBtnDown[mgmode_padNo] & A_BUTTON) {
                    if (!mgmode_gambleOpenF) {
                        HuAudFXPlay(2);
                        HuWinMesSet(mgmode_winId, 0x5705, -1, -1);
                        while (HuWinStatGet(mgmode_winId) != 0) {
                            HuPrcVSleep();
                        }
                        HuWinMesSet(mgmode_winId, 0x5704, -1, -1);
                    } else {
                        mgmode_CursorDispSet(0);
                        HuWinExAnimOut(mgmode_winId, 0);
                        node = Hu3DModelObjPtrGet(mgmode_mdlTbl[3], "door_g");
                        RepeatVibrator(mgmode_padNo, 5, 0, 5);
                        HuAudFXPlay(0x2EB);
                        for (i = 0; i < 19; i++) {
                            HuPrcVSleep();
                            mtxCopy(node->unk58, mgmode_roomGambleDoorMtx);
                            mtxRotCat(node->unk58, 0.0f, -i * 5, 0.0f);
                        }
                        mgmode_CameraPresetMove(15, 20, 1, (void (*)(s16 *))-1);
                        omOvlHisChg(0, 0x69, 7, 0x84);
                        mgmode_exitF = 1;
                        mgmode_exitOvlNo = 0x69;
                        mgmode_exitEvtNo = 3;
                        mgmode_exitMode = 0x82;
                        HuAudSeqFadeOut(60);
                        while (TRUE) {
                            HuPrcVSleep();
                        }
                    }
                } else if (ContBtnDown[mgmode_padNo] & R_JPAD) {
                    HuAudFXPlay(1);
                    HuWinExAnimOut(mgmode_winId, 0);
                    mgmode_CursorMoveTimeSet(20);
                    mgmode_roomSpotNo = 0;
                    mgmode_CursorSelMove(0);
                    mgmode_CameraPresetMove(1, 20, 1, (void (*)(s16 *))-1);
                    HuWinMesSet(mgmode_winId, 0x5702, -1, -1);
                    HuWinExAnimIn(mgmode_winId);
                } else if (ContBtnDown[mgmode_padNo] & L_JPAD) {
                    HuAudFXPlay(1);
                    HuWinExAnimOut(mgmode_winId, 0);
                    mgmode_CursorMoveTimeSet(10);
                    mgmode_roomSpotNo = 3;
                    mgmode_CursorSelMove(3);
                    mgmode_CameraPresetMove(5, 10, 1, (void (*)(s16 *))-1);
                    HuWinMesSet(mgmode_winId, 0x5709, -1, -1);
                    HuWinExAnimIn(mgmode_winId);
                }
                break;
            case 4:
                if (HuPadBtnDown[mgmode_padNo] & A_BUTTON) {
                    if (!mgmode_battleOpenF) {
                        HuAudFXPlay(2);
                        HuWinMesSet(mgmode_winId, 0x5708, -1, -1);
                        while (HuWinStatGet(mgmode_winId) != 0) {
                            HuPrcVSleep();
                        }
                        HuWinMesSet(mgmode_winId, 0x5707, -1, -1);
                    } else {
                        mgmode_CursorDispSet(0);
                        HuWinExAnimOut(mgmode_winId, 0);
                        node = Hu3DModelObjPtrGet(mgmode_mdlTbl[3], "door_b");
                        RepeatVibrator(mgmode_padNo, 5, 0, 5);
                        HuAudFXPlay(0x2EB);
                        for (i = 0; i < 19; i++) {
                            HuPrcVSleep();
                            mtxCopy(node->unk58, mgmode_roomBattleDoorMtx);
                            mtxRotCat(node->unk58, 0.0f, i * 5, 0.0f);
                        }
                        mgmode_CameraPresetMove(14, 20, 1, (void (*)(s16 *))-1);
                        omOvlHisChg(0, 0x69, 6, 0x84);
                        mgmode_exitF = 1;
                        mgmode_exitOvlNo = 0x69;
                        mgmode_exitEvtNo = 2;
                        mgmode_exitMode = 0x82;
                        HuAudSeqFadeOut(60);
                        while (TRUE) {
                            HuPrcVSleep();
                        }
                    }
                } else if (ContBtnDown[mgmode_padNo] & L_JPAD) {
                    HuAudFXPlay(1);
                    HuWinExAnimOut(mgmode_winId, 0);
                    mgmode_CursorMoveTimeSet(20);
                    mgmode_roomSpotNo = 0;
                    mgmode_CursorSelMove(0);
                    mgmode_CameraPresetMove(1, 20, 1, (void (*)(s16 *))-1);
                    HuWinMesSet(mgmode_winId, 0x5702, -1, -1);
                    HuWinExAnimIn(mgmode_winId);
                } else if (ContBtnDown[mgmode_padNo] & R_JPAD) {
                    HuAudFXPlay(1);
                    HuWinExAnimOut(mgmode_winId, 0);
                    mgmode_CursorMoveTimeSet(10);
                    mgmode_roomSpotNo = 3;
                    mgmode_CursorSelMove(3);
                    mgmode_CameraPresetMove(5, 10, 1, (void (*)(s16 *))-1);
                    HuWinMesSet(mgmode_winId, 0x5709, -1, -1);
                    HuWinExAnimIn(mgmode_winId);
                }
                break;
            case 5:
                if (HuPadBtnDown[mgmode_padNo] & A_BUTTON) {
                    HuAudFXPlay(2);
                    HuWinMesSet(mgmode_winId, 0x570A, -1, -1);
                    while (HuWinStatGet(mgmode_winId) != 0) {
                        HuPrcVSleep();
                    }
                    if ((s16)HuWinChoiceGet(mgmode_winId, 0, 0) == 0) {
                        HuWinExAnimOut(mgmode_winId, 0);
                        WipeCreateOut(11, 15);
                        HuAudSeqFadeOut(60);
                        mgmode_CameraPresetMove(16, 20, 1, (void (*)(s16 *))-1);
                        mgmode_exitMode = 0x80;
                        mgmode_exitF = 1;
                        mgmode_exitSaveF = 1;
                        while (TRUE) {
                            HuPrcVSleep();
                        }
                    }
                    HuWinMesSet(mgmode_winId, 0x5709, -1, -1);
                } else {
                    mgmode_CursorMoveTimeSet(10);
                    if (ContBtnDown[mgmode_padNo] & L_JPAD) {
                        HuAudFXPlay(1);
                        HuWinExAnimOut(mgmode_winId, 0);
                        mgmode_roomSpotNo = 2;
                        mgmode_CursorSelMove(2);
                        mgmode_CameraPresetMove(4, 10, 1, (void (*)(s16 *))-1);
                        if (mgmode_battleOpenF) {
                            HuWinMesSet(mgmode_winId, 0x5706, -1, -1);
                        } else {
                            HuWinMesSet(mgmode_winId, 0x5707, -1, -1);
                        }
                        HuWinExAnimIn(mgmode_winId);
                    } else if (ContBtnDown[mgmode_padNo] & R_JPAD) {
                        HuAudFXPlay(1);
                        HuWinExAnimOut(mgmode_winId, 0);
                        mgmode_roomSpotNo = 4;
                        mgmode_CursorSelMove(4);
                        mgmode_CameraPresetMove(3, 10, 1, (void (*)(s16 *))-1);
                        if (mgmode_gambleOpenF) {
                            HuWinMesSet(mgmode_winId, 0x5703, -1, -1);
                        } else {
                            HuWinMesSet(mgmode_winId, 0x5704, -1, -1);
                        }
                        HuWinExAnimIn(mgmode_winId);
                    }
                }
                break;
        }
        if ((HuPadBtnDown[mgmode_padNo] & B_BUTTON) && mgmode_cameraPresetNo != 5) {
            HuAudFXPlay(1);
            HuWinExAnimOut(mgmode_winId, 0);
            mgmode_CursorMoveTimeSet(20);
            mgmode_roomSpotNo = 3;
            mgmode_CursorSelMove(3);
            mgmode_CameraPresetMove(5, 20, 1, (void (*)(s16 *))-1);
            HuWinMesSet(mgmode_winId, 0x5709, -1, -1);
            HuWinExAnimIn(mgmode_winId);
        }
    }
}

s16 mgmode_MgUnlockExec(void) {
    s16 count = 0;
    s16 win;
    s16 total;
    s16 remaining;
    s16 size[2];

    if (_CheckFlag(0x1E) && !_CheckFlag(0x2A)) {
        count = 1;
        _SetFlag(0x2A);
    }
    if (mgmode_typeUnlockNumTbl[0] >= 20 && mgmode_typeUnlockNumTbl[1] >= 10 && mgmode_typeUnlockNumTbl[2] >= 10 &&
        mgmode_typeUnlockNumTbl[3] >= 8 && mgmode_typeUnlockNumTbl[4] >= 10 && mgmode_typeUnlockNumTbl[5] >= 6 && !_CheckFlag(0x2B)) {
        count++;
        _SetFlag(0x2B);
    }
    if (_CheckFlag(0x1F) && !_CheckFlag(0x2C)) {
        count++;
        _SetFlag(0x2C);
    }
    if (count == 0) {
        return 0;
    }
    HuWinInsertMesSizeGet((u32) "00", 0);
    HuWinInsertMesSizeGet((u32) "00", 1);
    HuWinMesMaxSizeBetGet(size, 0x570D, 0x5710);
    win = HuWinExCreate(-1, (320 - size[0]) / 2, 224 - size[1], size[0], size[1], 0);
    HuWinActivePlayerSet(win, 1 << mgmode_padNo);
    HuWinMesSet(win, 0x570D, -1, -1);
    HuWinExAnimIn(win);
    while (HuWinStatGet(win) != 0) {
        HuPrcVSleep();
    }
    if (count == 3) {
        HuWinMesSet(win, 0x570F, -1, -1);
    } else {
        sprintf(mgmode_strBuf, "%d", count);
        HuWinInsertMesSet(win, (u32)mgmode_strBuf, 0);
        HuWinMesSet(win, 0x570E, -1, -1);
    }
    while (HuWinStatGet(win) != 0) {
        HuPrcVSleep();
    }
    total = mgmode_typeUnlockNumTbl[0] + mgmode_typeUnlockNumTbl[1] + mgmode_typeUnlockNumTbl[2] + mgmode_typeUnlockNumTbl[3] +
            mgmode_typeUnlockNumTbl[4] + mgmode_typeUnlockNumTbl[5] + mgmode_typeUnlockNumTbl[7];
    remaining = 67 - total;
    if (remaining == 0) {
        HuWinMesSet(win, 0x5711, -1, -1);
    } else {
        sprintf(mgmode_strBuf, "%d", total);
        HuWinInsertMesSet(win, (u32)mgmode_strBuf, 0);
        HuWinMesSet(win, 0x5710, -1, -1);
    }
    while (HuWinStatGet(win) != 0) {
        HuPrcVSleep();
    }
    HuWinExAnimOut(win, 0);
    HuWinKill(win);
    mgmode_RecordSave();
    return count;
}

void mgmode_FloatMdlProc(void) {
    s32 angle = 0;

    Hu3DModelScaleSet(mgmode_mdlTbl5, 0.5f, 0.5f, 0.5f);
    while (TRUE) {
        HuPrcVSleep();
        Hu3DData[mgmode_mdlTbl5].pos.y = sindf(angle) * 20.0f;
        angle += 2;
        if (angle > 360) {
            angle -= 360;
        }
    }
}

char *mgmode_shelfNodeNameTbl[] = { "book_1", "book_2", "book_3", "book_4", "book_5", "book_6", "book_7" };
u8 mgmode_shelfTexOfsTbl[8] = {
    2, 0, 5, 1, 3, 4, 6, 0
};
s8 mgmode_team1vs3OrderTbl[20] = {
    0, 1, 2, 3,
    1, 0, 2, 3,
    2, 0, 1, 3,
    3, 0, 1, 2,
    -1, -1, -1, -1
};
s8 mgmode_team2vs2OrderTbl[16] = {
    0, 1, 2, 3,
    0, 2, 1, 3,
    0, 3, 1, 2,
    -1, -1, -1, -1
};
u16 mgmode_team1vs3PosXTbl[5] = {
    16, 72, 112, 152, 44
};
u16 mgmode_team2vs2PosXTbl[5] = {
    16, 56, 112, 152, 84
};

void mgmode_RoomInit(void) {
    s16 order[20];
    Vec tmpPos;
    HmfData *hmf;
    HmfVertexGroup *group;
    Vtx *verts;
    s16 model;
    s16 node;
    s16 count;
    s16 i;
    s16 j;
    s16 k;
    s16 b;
    s16 tmp;
    f32 x;
    f32 y;
    f32 z;
    void *data;

    mtxCopy(mgmode_roomMonitorMtx,
                       ((HmfMotionNode *)Hu3DModelObjPtrGet(mgmode_mdlTbl[6], "moniter_R"))->unk58);
    mtxCopy(mgmode_roomBattleDoorMtx,
                       ((HmfMotionNode *)Hu3DModelObjPtrGet(mgmode_mdlTbl[3], "door_b"))->unk58);
    mtxCopy(mgmode_roomGambleDoorMtx,
                       ((HmfMotionNode *)Hu3DModelObjPtrGet(mgmode_mdlTbl[3], "door_g"))->unk58);
    model = mgmode_mdlTbl[2];
    Hu3DModelObjAttrSet(model, 0x20000, 0x20000);
    Hu3DModelRemakeStatic(model);
    Hu3DModelVtxBufMake(model);
    Hu3DModelDynamicFree(model);
    hmf = Hu3DData[model].hmf;
    for (i = 0; i < 7; i++) {
        node = SearchObjectIndex(hmf, mgmode_shelfNodeNameTbl[i]);
        group = &hmf->unkB0[hmf->unk60[node].unk2C];
        verts = hmf->unk40;
        count = hmf->unk60[node].unk2E;
        for (j = 0; j < count; j++, group++) {
            x = y = z = 0.0f;
            for (k = 0; k < group->count; k++) {
                x += verts[group->indices[k]].v.ob[0];
                y += verts[group->indices[k]].v.ob[1];
                z += verts[group->indices[k]].v.ob[2];
            }
            mgmode_bookPosTbl[i][j].x = x / group->count;
            mgmode_bookPosTbl[i][j].y = y / group->count;
            mgmode_bookPosTbl[i][j].z = z / group->count;
            order[j] = j;
        }
        for (k = count - 1; k >= 0; k--) {
            for (b = 0; b < k; b++) {
                if (mgmode_bookPosTbl[i][b].x > mgmode_bookPosTbl[i][b + 1].x) {
                    tmpPos = mgmode_bookPosTbl[i][b];
                    mgmode_bookPosTbl[i][b] = mgmode_bookPosTbl[i][b + 1];
                    mgmode_bookPosTbl[i][b + 1] = tmpPos;
                    tmp = order[b];
                    order[b] = order[b + 1];
                    order[b + 1] = tmp;
                }
            }
        }
        for (j = 0; j < count; j++) {
            group = &hmf->unkB0[hmf->unk60[node].unk2C + order[j]];
            for (b = 0; b < Hu3DBufNum; b++) {
                verts = hmf->unk44[b];
                for (k = 0; k < group->count; k++) {
                    if (mgmode_typeMgTbl[mgmode_shelfTypeTbl[i]][j] != 0xFF) {
                        if (i == 6 && j == 0) {
                            verts[group->indices[k]].v.tc[0] += 0x1000;
                        } else {
                            verts[group->indices[k]].v.tc[0] += mgmode_shelfTexOfsTbl[i] << 9;
                        }
                    } else {
                        verts[group->indices[k]].v.tc[0] += 0xE00;
                    }
                }
            }
        }
    }
    model = mgmode_mdlTbl[15];
    data = DataRead(0xA002A);
    Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, "c160n_0_DEF");
    DataClose(data);
    Hu3DModelRemakeStatic(model);
    Hu3DModelDynamicFree(model);
}

void mgmode_MgRecordExec(s32 dataNum, s16 x, s16 y) {
    s16 wins[10];
    u8 buf[32];
    u8 buf2[32];
    u8 buf3[32];
    u8 games[10] = { 0, 1, 2, 4, 3, 5, 6, 7, 9, 8 };
    s8 unlockIds[10] = { 13, 16, 35, 52, 44, 71, 71, 71, 0, -1 };
    s32 names[10] = { 0x4501, 0x4502, 0x4503, 0x4504, 0x4505, 0x4506, 0x4507, 0x4508, 0x4509, 0x450A };
    s16 anim;
    s16 sprite;
    s16 win;
    s16 i;
    s16 j;
    s16 rec;
    f32 scale;

    HuPrcSleep(3);
    anim = HuSprAnimDataRead(dataNum);
    sprite = espEntry(anim, 0, 1);
    espPosSet(sprite, x, y);
    espPriSet(sprite, 0x8000);
    espScaleSet(sprite, 0.0f, 0.0f);
    for (i = 0; i < 10; i++) {
        wins[i] = HuWinExCreate(-1, x - 104, y - 71 + i * 14, 213, 20, 0);
        HuWinBGTPLvlSet(wins[i], 0);
    }
    win = HuWinExCreate(-1, 0, 0, 210, 14, 1);
    HuWinBGColSet(win, 255, 255, 255);
    HuAudFXPlay(0x2E7);
    for (i = 1; i < 11; i++) {
        scale = cosdf(i * 36.0f) * 0.5f + 0.5f;
        espScaleSet(sprite, scale, sindf(i * 9.0f));
        HuPrcVSleep();
    }
    for (i = 0; i < 10; i++) {
        rec = GWMgRecordGet(games[i]);
        if (rec < 0) {
            rec = 0;
        }
        switch (games[i]) {
            case 0:
                sprintf((char *)buf, "%3d", rec);
                HuWinInsertMesSet(wins[i], (u32)buf, 0);
                break;
            case 1:
            case 2:
            case 5:
            case 6:
            case 7:
                sprintf((char *)buf, "%d", (s16)(rec / 3600));
                HuWinInsertMesSet(wins[i], (u32)buf, 0);
                rec %= 3600;
                sprintf((char *)buf2, "%2d", (s16)(rec / 60));
                if (buf2[0] == ' ') {
                    buf2[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)buf2, 1);
                sprintf((char *)buf3, "%2d", (s16)((s16)(rec % 60) / 60.0f * 100.0f));
                if (buf3[0] == ' ') {
                    buf3[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)buf3, 2);
                break;
            case 4:
                sprintf((char *)buf, "%3d", (s16)(rec / 100));
                rec %= 100;
                HuWinInsertMesSet(wins[i], (u32)buf, 0);
                sprintf((char *)buf2, "%2d", rec);
                if (buf2[0] == ' ') {
                    buf2[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)buf2, 1);
                break;
            case 3:
            case 9:
                sprintf((char *)buf, "%d", (s16)(rec / 1800));
                HuWinInsertMesSet(wins[i], (u32)buf, 0);
                rec %= 1800;
                sprintf((char *)buf2, "%2d", (s16)(rec / 30));
                if (buf2[0] == ' ') {
                    buf2[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)buf2, 1);
                sprintf((char *)buf3, "%2d", (s16)((s16)(rec % 30) * (1.0f / 30.0f) * 99.0f));
                if (buf3[0] == ' ') {
                    buf3[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)buf3, 2);
                break;
            case 8:
                sprintf((char *)buf, "%4d", rec);
                HuWinInsertMesSet(wins[i], (u32)buf, 0);
                break;
        }
        HuWinDispOn(wins[i]);
        rec = unlockIds[i] - 1;
        if (rec == 70 && _CheckFlag(0x2B)) {
            HuWinMesSet(wins[i], names[i], -1, -1);
        } else if (rec >= 0 && GWMgUnlockCheck(rec)) {
            HuWinMesSet(wins[i], names[i], -1, -1);
        } else if (rec == -1 && _CheckFlag(0x1E)) {
            HuWinMesSet(wins[i], names[i], -1, -1);
        } else if (rec == -2 && _CheckFlag(0x1F)) {
            HuWinMesSet(wins[i], names[i], -1, -1);
        } else {
            HuWinMesSet(wins[i], 0x4500, -1, -1);
        }
        HuWinPosSet(win, x, y - 62 + i * 14);
        HuWinDispOn(win);
        HuAudFXPlay(0x2E8);
        for (j = 1; j < 4; j++) {
            HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
            HuPrcVSleep();
        }
    }
    HuWinKill(win);
    do {
        HuPrcVSleep();
    } while (!(HuPadBtnDown[0] & (A_BUTTON | B_BUTTON)));
    for (i = 0; i < 10; i++) {
        HuWinDispOff(wins[i]);
    }
    HuAudFXPlay(0x2E9);
    for (i = 1; i < 11; i++) {
        scale = 1.0f - sindf(i * 9.0f);
        espScaleSet(sprite, scale, scale);
        HuPrcVSleep();
    }
    for (i = 0; i < 10; i++) {
        HuWinKill(wins[i]);
    }
    espKill(sprite);
    HuSprAnimKill(anim);
}

void mgmode_MenuExec(s32 arg0) {
    s16 total;
    s16 choice;
    s16 i;
    HmfMotionNode *node;

    total = mgmode_typeUnlockNumTbl[0] + mgmode_typeUnlockNumTbl[1] + mgmode_typeUnlockNumTbl[2] + mgmode_typeUnlockNumTbl[3] +
            mgmode_typeUnlockNumTbl[4] + mgmode_typeUnlockNumTbl[5] + mgmode_typeUnlockNumTbl[7];
    if (total < 0) {
        total = 0;
    }
    sprintf(mgmode_strBuf, "%d", total);
    HuWinInsertMesSet(mgmode_menuWinId, (u32)mgmode_strBuf, 0);
    if (arg0 == 0) {
        HuWinMesSet(mgmode_menuWinId, 0x570B, -1, -1);
        HuWinExAnimIn(mgmode_menuWinId);
        while (HuWinStatGet(mgmode_menuWinId) != 0) {
            HuPrcVSleep();
        }
        HuWinMesSet(mgmode_menuWinId, 0x5712, -1, -1);
        while (HuWinStatGet(mgmode_menuWinId) != 0) {
            HuPrcVSleep();
        }
    } else {
        HuWinMesSet(mgmode_menuWinId, 0x5712, -1, -1);
        HuWinExAnimIn(mgmode_menuWinId);
        while (HuWinStatGet(mgmode_menuWinId) != 0) {
            HuPrcVSleep();
        }
    }
    choice = HuWinChoiceGet(mgmode_menuWinId, 0, 0);
    HuWinExAnimOut(mgmode_menuWinId, 0);
    if (choice == -1) {
        HuWinMesSet(mgmode_winId, 0x5702, -1, -1);
        HuWinExAnimIn(mgmode_winId);
        mgmode_CursorDispSet(1);
        return;
    }
    if (choice == 0) {
        mgmode_CursorDispSet(0);
        mgmode_CameraPresetMove(2, 10, 1, (void (*)(s16 *))-1);
        HuWinMesSet(mgmode_menuWinId, 0x5713, -1, -1);
        HuWinExAnimIn(mgmode_menuWinId);
        while (HuWinStatGet(mgmode_menuWinId) != 0) {
            HuPrcVSleep();
        }
        mgmode_ShelfSelect(0);
    } else if (choice == 1) {
        mgmode_CursorDispSet(0);
        node = Hu3DModelObjPtrGet(mgmode_mdlTbl6, "moniter_R");
        HuAudFXPlay(0x245);
        for (i = 0; i < 11; i++) {
            HuPrcVSleep();
            mtxCopy(node->unk58, mgmode_roomMonitorMtx);
            mtxRotCat(node->unk58, 0.0f, sindf(i * 9) * 117.0f, 0.0f);
        }
        mgmode_CameraPresetMove(6, 10, 1, (void (*)(s16 *))-1);
        mgmode_MgRecordExec(0x12000F, 160, 120);
        mgmode_CameraPresetMove(1, 10, 1, (void (*)(s16 *))-1);
        HuAudFXPlay(0x245);
        for (i = 0; i < 11; i++) {
            HuPrcVSleep();
            mtxCopy(node->unk58, mgmode_roomMonitorMtx);
            mtxRotCat(node->unk58, 0.0f, (1.0f - sindf(i * 9)) * 117.0f, 0.0f);
        }
    }
    mgmode_CursorPosTblSet(mgmode_roomCursorPosTbl);
    mgmode_CursorSelSet(0);
    mgmode_CursorDispSet(1);
    HuWinMesSet(mgmode_winId, 0x5702, -1, -1);
    HuWinExAnimIn(mgmode_winId);
}

void mgmode_MenuResume(void) {
    HuWinDispOn(mgmode_menuWinId);
    mgmode_ShelfSelect(mgModeMenuNo);
    mgmode_CursorPosTblSet(mgmode_roomCursorPosTbl);
    mgmode_CursorSelSet(0);
    mgmode_CursorDispSet(1);
    HuWinMesSet(mgmode_winId, 0x5702, -1, -1);
    HuWinExAnimIn(mgmode_winId);
}

void mgmode_ShelfMesSet(s16 arg0) {
    s32 mesOffset;

    mesOffset = (mgmode_typeUnlockNumTbl[mgmode_shelfTypeTbl[arg0]] != 0) ? 7 : 0;
    if (mgmode_typeUnlockNumTbl[mgmode_shelfTypeTbl[arg0]] == mgmode_typeMgNumTbl[mgmode_shelfTypeTbl[arg0]]) {
        mesOffset = 14;
    }
    sprintf(mgmode_strBuf, "%d", mgmode_typeUnlockNumTbl[mgmode_shelfTypeTbl[arg0]]);
    HuWinInsertMesSet(mgmode_menuWinId, (u32)mgmode_strBuf, 0);
    HuWinMesSet(mgmode_menuWinId, mgmode_shelfMesTbl[mesOffset + arg0], -1, -1);
}

void mgmode_ShelfSelect(s16 arg0) {
    s16 next;

    mgmode_ShelfMesSet(arg0);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    mgmode_CursorPosTblSet(mgmode_shelfCursorPosTbl);
    mgmode_CursorSelSet(arg0);
    mgmode_CursorMoveTimeSet(5);
    mgmode_CursorDispSet(1);
    HuPrcSleep(5);
    while (TRUE) {
        HuPrcVSleep();
        mgmode_DpadStickSet();
        if (ABS(HuPadStkX[mgmode_padNo]) >= 31 || ABS(HuPadStkY[mgmode_padNo]) >= 31) {
            next = mgmode_CursorPadNextGet(-HuPadStkX[mgmode_padNo], HuPadStkY[mgmode_padNo]);
            if (next == -1) {
                continue;
            }
            HuAudFXPlay(1);
            mgmode_CursorSelMove(next);
            HuPrcSleep(5);
            mgmode_ShelfMesSet(next);
            arg0 = next;
        } else if ((HuPadBtnDown[mgmode_padNo] & A_BUTTON) && mgmode_typeUnlockNumTbl[mgmode_shelfTypeTbl[arg0]] != 0) {
            HuAudFXPlay(2);
            mgmode_CursorDispSet(0);
            HuWinExAnimOut(mgmode_menuWinId, 0);
            mgmode_CameraPresetMove(arg0 + 7, 15, 1, (void (*)(s16 *))-1);
            mgmode_BookSelect(arg0);
            mgmode_CameraPresetMove(2, 15, 1, (void (*)(s16 *))-1);
            mgmode_CursorPosTblSet(mgmode_shelfCursorPosTbl);
            mgmode_CursorSelSet(arg0);
            mgmode_CursorMoveTimeSet(5);
            mgmode_CursorDispSet(1);
            mgmode_ShelfMesSet(arg0);
            HuWinExAnimIn(mgmode_menuWinId);
        } else if (HuPadBtnDown[mgmode_padNo] & B_BUTTON) {
            HuAudFXPlay(4);
            mgmode_CursorDispSet(0);
            HuWinExAnimOut(mgmode_menuWinId, 0);
            mgmode_CameraPresetMove(1, 10, 1, (void (*)(s16 *))-1);
            return;
        }
    }
}

void mgmode_BookSelect(s16 arg0) {
    Vec pos;
    Vec2f screen;
    s16 category;
    s16 count;
    s16 i;
    s16 sel;
    s16 next;
    s16 ok;
    s16 win;
    s16 spriteGrp;
    s16 icon;
    s16 badge;

    category = mgmode_shelfTypeTbl[arg0];
    count = mgmode_typeMgNumTbl[category];
    for (i = 0; i < count; i++) {
        pos = mgmode_bookPosTbl[arg0][i];
        Hu3D3Dto2D(0, &pos, &screen);
        mgmode_bookCursorPosTbl[i].x = screen.x;
        mgmode_bookCursorPosTbl[i].y = screen.y;
    }
    mgmode_bookCursorPosTbl[i].x = -1;
    mgmode_bookCursorPosTbl[i].y = -1;
    win = HuWinExCreate(-1, 24, 16, 272, 80, 0);
    HuWinActivePlayerSet(win, 1 << mgmode_padNo);
    icon = mgmode_MgPicCreate();
    espAttrSet(icon, 8);
    espPosSet(icon, 76, 56);
    espScaleSet(icon, 0.75f, 0.75f);
    spriteGrp = HuSprAnimDataRead(0x120013);
    badge = espEntry(spriteGrp, 0, 1);
    espPriSet(badge, 1);
    espDispOff(badge);
    espPosSet(badge, 76, 84);
    mgmode_CursorPosTblSet(mgmode_bookCursorPosTbl);
    sel = mgModeCursor[arg0];
    for (i = 0; i < count; i++) {
        if (mgmode_typeMgTbl[category][i] == 0xFF || mgmode_typeMgTbl[category][i] >= 72) {
            mgmode_CursorDisableSet(i);
        } else if (sel == -1) {
            sel = mgModeCursor[arg0] = i;
        }
    }
    mgmode_CursorSelSet(sel);
    mgmode_CursorDispSet(1);
    mgmode_CursorMoveTimeSet(3);
    if (mgmode_typeMgTbl[category][sel] != 0xFF && mgmode_typeMgTbl[category][sel] < 72) {
        mgmode_BookMdlSet(arg0, sel);
    }
    HuWinInsertMesSet(win, mgmode_typeMgTbl[category][sel] + 0x4700, 0);
    HuWinMesSet(win, mgmode_mgInfoMesTbl[mgmode_typeMgTbl[category][sel]], -1, -1);
    HuWinExAnimIn(win);
    if (mgmode_typeMgTbl[category][sel] != 0xFF && mgmode_typeMgTbl[category][sel] < 72) {
        espDispOn(icon);
        if (mgDataTbl[mgmode_typeMgTbl[category][sel]].flags >> 15) {
            espDispOn(badge);
        } else {
            espDispOff(badge);
        }
        mgmode_MgPicLoad(mgDataTbl[mgmode_typeMgTbl[category][sel]].flags & 0x7FF);
    } else {
        espDispOff(icon);
    }
    while (TRUE) {
        HuPrcVSleep();
        mgmode_DpadStickSet();
        if (ABS(HuPadStkX[mgmode_padNo]) >= 31 || ABS(HuPadStkY[mgmode_padNo]) >= 31) {
            next = mgmode_CursorPadNextGet(-HuPadStkX[mgmode_padNo], HuPadStkY[mgmode_padNo]);
            if (next == -1) {
                continue;
            }
            HuAudFXPlay(1);
            mgmode_CursorSelMove(next);
            sel = next;
            mgModeCursor[arg0] = sel;
            for (i = 0; i < 8; i++) {
                Hu3DModelAttrSet(mgmode_mdlTbl7[i], 4, 4);
            }
            if (mgmode_typeMgTbl[category][sel] != 0xFF && mgmode_typeMgTbl[category][sel] < 72) {
                mgmode_BookMdlSet(arg0, sel);
                espDispOn(icon);
                if (mgDataTbl[mgmode_typeMgTbl[category][sel]].flags >> 15) {
                    espDispOn(badge);
                } else {
                    espDispOff(badge);
                }
                mgmode_MgPicLoad(mgDataTbl[mgmode_typeMgTbl[category][sel]].flags & 0x7FF);
                HuWinInsertMesSet(win, mgmode_typeMgTbl[category][sel] + 0x4700, 0);
                HuWinMesSet(win, mgmode_mgInfoMesTbl[mgmode_typeMgTbl[category][sel]], -1, -1);
            } else {
                espDispOff(icon);
                HuWinMesSet(win, 0x4401, -1, -1);
            }
            HuPrcSleep(3);
        } else if ((HuPadBtnDown[mgmode_padNo] & A_BUTTON) && mgmode_typeMgTbl[category][sel] != 0xFF) {
            HuAudFXPlay(2);
            for (i = 0; i < 4; i++) {
                GwPlayer[i].group = i;
            }
            ok = 1;
            if (category == 1 || category == 2) {
                mgmode_CursorDispSet(0);
                ok = mgmode_TeamChoice(category);
                if (ok == 0) {
                    mgmode_TeamChoiceKill();
                    mgmode_CursorDispSet(1);
                    HuPrcSleep(5);
                }
            }
            if (ok == 0) {
                continue;
            }
            HuWinMesSet(win, 0x4400, -1, -1);
            while (HuWinStatGet(win) != 0) {
                HuPrcVSleep();
            }
            next = HuWinChoiceGet(win, 0, 0);
            if (category == 1 || category == 2) {
                mgmode_TeamChoiceKill();
            }
            if (next == -1) {
                mgmode_CursorDispSet(1);
                HuPrcSleep(2);
                HuWinMesSet(win, mgmode_mgInfoMesTbl[mgmode_typeMgTbl[category][sel]], -1, -1);
                continue;
            }
            mgmode_CursorDispSet(0);
            _SetFlag(13);
            mgmode_BookTakeExec(arg0, sel);
            if (next == 1) {
                GwSystem.show_minigame_explanations = 1;
            } else {
                GwSystem.show_minigame_explanations = 0;
            }
            GwSystem.minigame_index = mgmode_typeMgTbl[category][sel] + 1;
            mgModeMenuNo = arg0;
            omOvlHisChg(0, 0x69, 1, 0x84);
            mgmode_exitF = 1;
            mgmode_exitOvlNo = 0x68;
            if (GwSystem.minigame_index == 0x47 || GwSystem.minigame_index == 0x1F) {
                mgmode_exitEvtNo = 0;
            } else {
                HuAudSeqFadeOut(60);
                mgmode_exitEvtNo = 1;
            }
            mgmode_exitMode = 0x82;
            mgModeCoinBase = 0;
            while (TRUE) {
                HuPrcVSleep();
            }
        } else if (HuPadBtnDown[mgmode_padNo] & B_BUTTON) {
            HuAudFXPlay(4);
            mgmode_CursorDispSet(0);
            break;
        }
    }
    mgmode_MgPicKill();
    espKill(badge);
    HuSprAnimKill(spriteGrp);
    HuWinExAnimOut(win, 0);
    for (i = 0; i < 8; i++) {
        Hu3DModelAttrSet(mgmode_mdlTbl7[i], 4, 4);
    }
    HuWinKill(win);
}

void mgmode_BookMdlSet(s16 arg0, s16 arg1) {
    s16 model;
    f32 x;
    f32 z;
    f32 dist;

    if (arg0 == 6 && arg1 == 0) {
        model = mgmode_mdlTbl14;
    } else {
        model = mgmode_mdlTbl7[arg0];
    }
    Hu3DModelAttrSet(model, 4, 0);
    Hu3DModelRotSet(model, 15.0f, CRot.y, 0.0f);
    x = sindf(CRot.y) * cosdf(CRot.x);
    z = cosdf(CRot.y) * cosdf(CRot.x);
    dist = HuSqrtf(x * x + z * z);
    x = x / dist * 20.0f;
    z = z / dist * 20.0f;
    Hu3DModelPosSet(model, x + mgmode_bookPosTbl[arg0][arg1].x, mgmode_bookPosTbl[arg0][arg1].y - 3.0f,
                    z + mgmode_bookPosTbl[arg0][arg1].z);
}

void mgmode_BookTakeExec(s16 arg0, s16 arg1) {
    s16 model;
    s16 i;
    f32 x;
    f32 z;
    f32 dist;
    f32 startX;
    f32 startY;
    f32 startZ;
    f32 endX;
    f32 endY;
    f32 endZ;
    f32 rotX;
    f32 t;

    if (arg0 == 6 && arg1 == 0) {
        model = mgmode_mdlTbl14;
    } else {
        model = mgmode_mdlTbl7[arg0];
    }
    Hu3DModelRotSet(model, 15.0f, CRot.y, 0.0f);
    x = sindf(CRot.y) * cosdf(CRot.x);
    z = cosdf(CRot.y) * cosdf(CRot.x);
    dist = HuSqrtf(x * x + z * z);
    x = x / dist * 20.0f;
    z = z / dist * 20.0f;
    rotX = 15.0f;
    startX = x + mgmode_bookPosTbl[arg0][arg1].x;
    startY = mgmode_bookPosTbl[arg0][arg1].y - 3.0f;
    startZ = z + mgmode_bookPosTbl[arg0][arg1].z;
    endX = Center.x + sindf(CRot.y) * cosdf(CRot.x) * CZoom - 50.0f;
    endY = Center.y + -sindf(CRot.x) * CZoom;
    endZ = Center.z + cosdf(CRot.y) * cosdf(CRot.x) * CZoom;
    for (i = 0; i < 30; i++) {
        HuPrcVSleep();
        if (i == 20) {
            WipeCreateOut(11, 10);
        }
        t = i / 30.0f * 0.5f;
        Hu3DModelPosSet(model, startX + (endX - startX) * t, startY + (endY - startY) * t,
                        startZ + (endZ - startZ) * t);
        Hu3DModelRotSet(model, rotX, CRot.y - i * 3, 0.0f);
        rotX -= 3.0f;
        if (rotX < 0.0f) {
            rotX = 0.0f;
        }
    }
}

s16 mgmode_TeamChoice(s16 arg0) {
    s8 *orders;
    s16 i;
    s16 timer;
    s16 sel;
    s16 ret = 1;

    if (arg0 == 2) {
        mgmode_teamPosXTbl = mgmode_team1vs3PosXTbl;
    } else {
        mgmode_teamPosXTbl = mgmode_team2vs2PosXTbl;
    }
    if (arg0 == 2) {
        orders = mgmode_team1vs3OrderTbl;
    } else {
        orders = mgmode_team2vs2OrderTbl;
    }
    for (i = 0; i < 4; i++) {
        mgmode_teamOrderTbl[i] = i;
    }
    mgmode_teamWinId = HuWinExCreate(-1, 50, 100, 220, 80, 0);
    HuWinActivePlayerSet(mgmode_teamWinId, 1 << mgmode_padNo);
    HuWinMesSet(mgmode_teamWinId, 0x5729, -2, -1);
    HuWinExAnimIn(mgmode_teamWinId);
    for (i = 0; i < 4; i++) {
        mgmode_teamSprDefTbl[i].dataNum = (GwPlayer[i].chr + 0x36) | 0x130000;
    }
    mgmode_teamSprDefTbl[4].dataNum = 0x120012;
    if (arg0 == 1) {
        mgmode_teamSprDefTbl[5].dataNum = 0x120012;
    } else {
        mgmode_teamSprDefTbl[5].dataNum = 0x120011;
    }
    sel = 0;
    mgmode_teamSprTbl = mgmode_SprListCreate(mgmode_teamSprDefTbl);
    mgmode_TeamSprPosSet(160, 134);
    mgmode_TeamArrowPosSet(160, 134);
    timer = 0;
    while (TRUE) {
        HuPrcVSleep();
        if (timer != 0) {
            timer--;
        }
        mgmode_DpadStickSet();
        if (ABS(HuPadStkX[mgmode_padNo]) >= 31 && timer == 0) {
            HuAudFXPlay(1);
            if (HuPadStkX[mgmode_padNo] >= 31) {
                sel++;
                if (orders[sel * 4] == -1) {
                    sel = 0;
                }
            } else {
                sel--;
                if (sel < 0) {
                    for (i = 0; orders[i * 4] != -1; i++) {
                    }
                    sel = i - 1;
                }
            }
            for (i = 0; i < 4; i++) {
                mgmode_teamOrderTbl[i] = orders[sel * 4 + i];
            }
            mgmode_TeamSprPosSet(160, 134);
            timer = 10;
        } else if (HuPadBtnDown[mgmode_padNo] & A_BUTTON) {
            HuAudFXPlay(2);
            if (arg0 == 2) {
                for (i = 0; i < 4; i++) {
                    GwPlayer[mgmode_teamOrderTbl[i]].group = mgPlayerTeam[mgmode_teamOrderTbl[i]] = (i != 0);
                }
            } else {
                for (i = 0; i < 4; i++) {
                    GwPlayer[mgmode_teamOrderTbl[i]].group = mgPlayerTeam[mgmode_teamOrderTbl[i]] = (i >= 2);
                }
            }
            break;
        } else if (HuPadBtnDown[mgmode_padNo] & B_BUTTON) {
            HuAudFXPlay(4);
            ret = 0;
            break;
        }
    }
    return ret;
}

void mgmode_TeamChoiceKill(void) {
    mgmode_SprListKill(mgmode_teamSprTbl);
    HuWinExAnimOut(mgmode_teamWinId, 0);
    HuWinKill(mgmode_teamWinId);
}

void mgmode_TeamSprPosSet(s32 arg0, s32 arg1) {
    s16 i;

    for (i = 0; i < 4; i++) {
        mgmode_SprListPosSet(mgmode_teamSprTbl, mgmode_teamOrderTbl[i], arg0 + mgmode_teamPosXTbl[i] - 0x54, arg1);
        mgmode_SprListPosSet(mgmode_teamSprTbl, mgmode_teamOrderTbl[i] + 10, arg0 + mgmode_teamPosXTbl[i] - 0x54,
                             arg1 + 0x1E);
        mgmode_SprListPosSet(mgmode_teamSprTbl, i + 4, arg0 + mgmode_teamPosXTbl[i] - 0x54, arg1);
        if (GwPlayer[mgmode_teamOrderTbl[i]].stat & 1) {
            mgmode_SprListDispOn(mgmode_teamSprTbl, i + 14);
            mgmode_SprListPosSet(mgmode_teamSprTbl, i + 14, arg0 + mgmode_teamPosXTbl[i] - 0x54, arg1 + 0xE);
        } else {
            mgmode_SprListDispOff(mgmode_teamSprTbl, i + 14);
        }
    }
}

void mgmode_TeamArrowPosSet(s32 arg0, s32 arg1) {
    s32 offset = 0x54;

    mgmode_SprListPosSet(mgmode_teamSprTbl, 18, mgmode_teamPosXTbl[4] + (arg0 - offset), arg1);
    mgmode_SprListPosSet(mgmode_teamSprTbl, 8, mgmode_teamPosXTbl[0] + arg0 - 0x70, arg1);
    mgmode_SprListPosSet(mgmode_teamSprTbl, 9, mgmode_teamPosXTbl[3] + arg0 - 0x38, arg1);
}

void mgmode_MgListBuild(s32 arg0) {
    s16 i;
    s16 k;
    s16 category;

    mgmode_mgNum = 0;
    mgmode_mgUnlockNum = 0;
    for (i = 0; i < 8; i++) {
        mgmode_typeMgNumTbl[i] = mgmode_typeUnlockNumTbl[i] = mgmode_markMgNumTbl[i] = mgmode_plainMgNumTbl[i] = 0;
    }
    for (i = 0; i < 71; i++) {
        category = mgDataTbl[i].minigameType;
        if (mgDataTbl[i].overlay == 0x70 || mgDataTbl[i].overlay == -1) {
            continue;
        }
        if (arg0 != 0 && (i == 27 || i == 8 || i == 16)) {
            continue;
        }
        if (GWMgUnlockCheck(i)) {
            mgmode_typeUnlockNumTbl[category]++;
            mgmode_mgUnlockNum++;
            if (mgDataTbl[i].flags >> 15) {
                mgmode_markMgTbl[category][mgmode_markMgNumTbl[category]] = i;
                mgmode_markMgNumTbl[category]++;
            } else {
                mgmode_plainMgTbl[category][mgmode_plainMgNumTbl[category]] = i;
                mgmode_plainMgNumTbl[category]++;
            }
            mgmode_typeMgTbl[category][mgmode_typeMgNumTbl[category]] = i;
        } else {
            if (mgDataTbl[i].flags >> 15) {
                mgmode_markMgTbl[category][mgmode_markMgNumTbl[category]] = 0xFF;
                mgmode_markMgNumTbl[category]++;
            } else {
                mgmode_plainMgTbl[category][mgmode_plainMgNumTbl[category]] = 0xFF;
                mgmode_plainMgNumTbl[category]++;
            }
            mgmode_typeMgTbl[category][mgmode_typeMgNumTbl[category]] = 0xFF;
        }
        mgmode_typeMgNumTbl[category]++;
        mgmode_mgNum++;
    }
    for (category = 0; category < 7; category++) {
        k = 0;
        for (i = 0; i < mgmode_markMgNumTbl[category]; i++) {
            mgmode_typeMgTbl[category][k++] = mgmode_markMgTbl[category][i];
        }
        for (i = 0; i < mgmode_plainMgNumTbl[category]; i++) {
            mgmode_typeMgTbl[category][k++] = mgmode_plainMgTbl[category][i];
        }
    }
    mgmode_typeMgNumTbl[7] = 3;
    mgmode_typeUnlockNumTbl[7] = 0;
    if (_CheckFlag(0x1E)) {
        mgmode_typeMgTbl[7][0] = 65;
        mgmode_typeUnlockNumTbl[7]++;
        mgmode_mgUnlockNum++;
    } else {
        mgmode_typeMgTbl[7][0] = 0xFF;
    }
    if (mgmode_typeUnlockNumTbl[0] >= 20 && mgmode_typeUnlockNumTbl[1] >= 10 && mgmode_typeUnlockNumTbl[2] >= 10 &&
        mgmode_typeUnlockNumTbl[3] >= 8 && mgmode_typeUnlockNumTbl[4] >= 10 && mgmode_typeUnlockNumTbl[5] >= 6) {
        mgmode_typeMgTbl[7][1] = 70;
        mgmode_typeUnlockNumTbl[7]++;
        mgmode_mgUnlockNum++;
    } else {
        mgmode_typeMgTbl[7][1] = 0xFF;
    }
    if (_CheckFlag(0x1F)) {
        mgmode_typeMgTbl[7][2] = 71;
        mgmode_typeUnlockNumTbl[7]++;
        mgmode_mgUnlockNum++;
    } else {
        mgmode_typeMgTbl[7][2] = 0xFF;
    }
}

void mgmode_ZClearHook(Gfx **arg0, s32 arg1, s32 arg2) {
    if (mgmode_zClearF != 0) {
        gDPSetDepthImage((*arg0)++, 0x3D0800);
        gDPSetColorImage((*arg0)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, 0x3D0800);
        gSPDisplayList((*arg0)++, mgmode_zClearGfx);
    }
}

void mgmode_CameraProc(void) {
    Vec pos, at, up;
    f32 rotX, rotY, rotZ;
    f32 upX, upY, upZ;
    f32 dx, dy, dz;
    f32 length;

    while (TRUE) {
        rotX = CRot.x;
        rotY = CRot.y;
        rotZ = CRot.z;
        pos.x = sindf(rotY) * cosdf(rotX) * CZoom + Center.x;
        pos.y = -sindf(rotX) * CZoom + Center.y;
        pos.z = cosdf(rotY) * cosdf(rotX) * CZoom + Center.z;
        at.x = Center.x;
        at.y = Center.y;
        at.z = Center.z;
        upX = sindf(rotY) * sindf(rotX);
        upY = cosdf(rotX);
        upZ = cosdf(rotY) * sindf(rotX);
        dx = at.x - pos.x;
        dy = at.y - pos.y;
        dz = at.z - pos.z;
        length = HuSqrtf(dx * dx + dy * dy + dz * dz);
        dx /= length;
        dy /= length;
        dz /= length;
        up.x = upX * (dx * dx + (1.0f - dx * dx) * cosdf(rotZ)) +
               upY * (dx * dy * (1.0f - cosdf(rotZ)) - dz * sindf(rotZ)) +
               upZ * (dx * dz * (1.0f - cosdf(rotZ)) + dy * sindf(rotZ));
        up.y = upX * (dx * dy * (1.0f - cosdf(rotZ)) + dz * sindf(rotZ)) +
               upY * (dy * dy + (1.0f - dy * dy) * cosdf(rotZ)) +
               upZ * (dy * dz * (1.0f - cosdf(rotZ)) - dx * sindf(rotZ));
        up.z = upX * (dx * dz * (1.0f - cosdf(rotZ)) - dy * sindf(rotZ)) +
               upY * (dy * dz * (1.0f - cosdf(rotZ)) + dx * sindf(rotZ)) +
               upZ * (dz * dz + (1.0f - dz * dz) * cosdf(rotZ));
        Hu3DCameraPerspectiveSet(0, mgmode_cameraFov, mgmode_cameraNear, mgmode_cameraFar);
        Hu3DCameraPosSetV(0, &pos, &at, &up);
        Hu3DCamUpdateMtx(0);
        Hu3DCameraPerspectiveSet(1, mgmode_cameraFov, mgmode_cameraNear, mgmode_cameraFar);
        Hu3DCameraPosSetV(1, &pos, &at, &up);
        Hu3DCamUpdateMtx(1);
        HuPrcVSleep();
    }
}

void mgmode_CameraDebugExec(void) {
    char buf[256];
    HmfModel *model;
    f32 rotX;
    f32 rotY;
    f32 speed;
    f32 dirZ;
    f32 inv;

    model = &Hu3DData[mgmode_mdlTbl[15]];
    if (HuPadBtnDown[1] & R_TRIG) {
        mgmode_cameraDebugF ^= 1;
        if (mgmode_cameraDebugF) {
            osSyncPrintf("\t{\n\t{%4.1f,%4.1f,%4.1f},\n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf("\t{%4.1f,%4.1f,%4.1f},\n", Center.x, Center.y, Center.z);
            osSyncPrintf("\t%4.1f,%4.1f\n\t},\n", CZoom, mgmode_cameraFov);
            osSyncPrintf("HMF>%4.1f,%4.1f,%4.1f\n", model->rot.x, model->rot.y, model->rot.z);
        }
    }
    if (HuPadBtn[1] & START_BUTTON) {
        mgmode_CameraPresetSet(mgmode_cameraPresetNo);
    }
    if (HuPadBtn[1] & 8) {
        CZoom = (HuPadBtn[1] & Z_TRIG) ? CZoom + 30.0f : CZoom + 10.0f;
    }
    if ((HuPadBtn[1] & 4) && CZoom - 10.0f != 0.0f) {
        CZoom = (HuPadBtn[1] & Z_TRIG) ? CZoom - 30.0f : CZoom - 10.0f;
    }
    if (HuPadBtn[1] & 2) {
        mgmode_cameraFov += 1.0f;
    }
    if (HuPadBtn[1] & 1) {
        mgmode_cameraFov -= 1.0f;
    }
    Hu3DCameraPerspectiveSet(0, mgmode_cameraFov, mgmode_cameraNear, mgmode_cameraFar);
    rotX = mgmode_cameraRot.x;
    rotY = mgmode_cameraRot.y;
    speed = (HuPadBtn[1] & Z_TRIG) ? 5.0f : 2.0f;
    rotY += (-HuPadStkX[1] / 30) * speed;
    if (rotY >= 360.0f) {
        rotY -= 360.0f;
    } else if (rotY < 0.0f) {
        rotY += 360.0f;
    }
    mgmode_cameraRot.y = rotY;
    rotX += (s8)(HuPadStkY[1] / 30) * speed;
    if (rotX >= 360.0f) {
        rotX -= 360.0f;
    } else if (rotX < 0.0f) {
        rotX += 360.0f;
    }
    mgmode_cameraRot.x = rotX;
    CRot.x = (s16)rotX;
    CRot.y = (s16)mgmode_cameraRot.y;
    speed = (HuPadBtn[1] & Z_TRIG) ? 10.0f : 2.0f;
    if (HuPadBtn[1] & U_JPAD) {
        Center.x += sindf(rotY) * sindf(rotX) * -speed;
        Center.y += cosdf(rotX) * -speed;
        Center.z += cosdf(rotY) * sindf(rotX) * -speed;
    } else if (HuPadBtn[1] & D_JPAD) {
        Center.x += sindf(rotY) * sindf(rotX) * speed;
        Center.y += cosdf(rotX) * speed;
        Center.z += cosdf(rotY) * sindf(rotX) * speed;
    } else if (HuPadBtn[1] & L_JPAD) {
        // rotX is reused here as the X component of the camera direction.
        rotX = gCameraList->pos.z - Center.z;
        dirZ = -(gCameraList->pos.x - Center.x);
        inv = 1.0f / HuSqrtf(rotX * rotX + dirZ * dirZ);
        Center.x += rotX * inv * speed;
        Center.y += 0.0f;
        Center.z += dirZ * inv * speed;
    } else if (HuPadBtn[1] & R_JPAD) {
        rotX = -(gCameraList->pos.z - Center.z);
        dirZ = gCameraList->pos.x - Center.x;
        inv = 1.0f / HuSqrtf(rotX * rotX + dirZ * dirZ);
        Center.x += rotX * inv * speed;
        Center.y += 0.0f;
        Center.z += dirZ * inv * speed;
    }
    if (mgmode_cameraDebugF) {
        sprintf(buf, "CROT %4.1f,%4.1f,%4.1f", CRot.x, CRot.y, CRot.z);
        print8(32, 180, buf);
        sprintf(buf, "INT %4.1f,%4.1f,%4.1f", Center.x, Center.y, Center.z);
        print8(32, 190, buf);
        sprintf(buf, "CZOOM %4.1f  FOVY %4.1f", CZoom, mgmode_cameraFov);
        print8(32, 200, buf);
    }
}

void mgmode_ExitCheckObjMain(omObjData *arg0) {
    if ((mgmode_exitF != 0) || (omSysExitReq != 0)) {
        if ((mgmode_exitMode & 0x80) == 0) {
            WipeCreateOut(0xB, 8);
            HuAudSeqFadeOut(0x3C);
        }
        arg0->func = mgmode_ExitObjMain;
    }
}

void mgmode_ExitObjMain(omObjData *arg0) {
    if (WipeStatGet() != 0) {
        return;
    }
    HuWinAllKill();
    if (mgmode_exitSaveF != 0) {
        mgmode_RecordSave();
    }
    mgmode_MgPicKill();
    mgmode_exitMode &= 0xF;
    _ClearFlag(0x1C);
    if (mgmode_exitMode == 0) {
        omOvlReturnEx(1);
    } else if (mgmode_exitMode == 2) {
        if (mgmode_exitOvlNo == 0x68) {
            _SetFlag(0x1C);
        }
        if (mgmode_exitOvlNo == 0x70) {
            _SetFlag(0x1C);
            omOvlCallEx(mgmode_exitOvlNo, mgmode_exitEvtNo, 0x82);
        } else {
            omOvlCallEx(mgmode_exitOvlNo, mgmode_exitEvtNo, 0x84);
        }
    } else {
        omOvlGotoEx(mgmode_exitOvlNo, mgmode_exitEvtNo, 0x82);
    }
}
